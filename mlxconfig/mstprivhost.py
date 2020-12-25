#copyright (c) 2004-2020 Mellanox Technologies LTD. All rights reserved.   
#                                                                           
# This software is available to you under a choice of one of two            
# licenses.  You may choose to be licensed under the terms of the GNU       
# General Public License (GPL) Version 2, available from the file           
# COPYING in the main directory of this source tree, or the                 
# OpenIB.org BSD license below:                                             
#                                                                           
#     Redistribution and use in source and binary forms, with or            
#     without modification, are permitted provided that the following       
#     conditions are met:                                                   
#                                                                           
#      - Redistributions of source code must retain the above               
#        copyright notice, this list of conditions and the following        
#        disclaimer.                                                        
#                                                                           
#      - Redistributions in binary form must reproduce the above            
#        copyright notice, this list of conditions and the following        
#        disclaimer in the documentation and/or other materials             
#        provided with the distribution.                                    
#                                                                           
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,         
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE OF                   
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS       
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN        
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN         
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE          
# SOFTWARE.                                                                 
#--                                                                         


from __future__ import print_function

import argparse
import os
import subprocess
import sys
import tempfile
import math

import tools_version

PROG = 'mstprivhost'
TOOL_VERSION = "1.0.0"

CMD_HELP = """\
restrict:  Set host 1 (ARM) privileged, host 0 (x86_64) restricted.
privilege: Set host 1 (ARM) privileged, host 0 (x86_64) privileged
           (back to default).
query:     Query current host configuration.
"""

DESCRIPTION = """\
restrict or privilege host
Note: New configurations takes effect immediately.
Note: privileged host - host has all supported privileges.
      restricted host - host is not allowed to modify global
      per port/parameters or access other hosts parametersis.

"""

DISABLE_RSHIM_HELP = """\
When TRUE, the host does not have an RSHIM function
to access the embedded CPU registers
"""

DISABLE_TRACER_HELP = """\
When TRUE, the host will not be allowed to own the Tracer
"""

DISABLE_COUNTER_RD_HELP = """\
When TRUE, the host will not be allowed to read Physical port counters
"""

DISABLE_PORT_OWNER_HELP = """\
When TRUE, the host will not be allowed to be Port Owner
"""

def _log(level, msg, *args, **kw):
    if args:
        msg = msg % args
    print(level, msg, end=kw.get('end', '\n'))


def info(msg, *args, **kw):
    _log("-I-", msg, *args, **kw)


def error(msg, *args, **kw):
    _log("-E-", msg, *args, **kw)


class PrivilegeException(Exception):
    pass


class PrivilegeMgr(object):
    CONFIG_CMD_LINE = "mstconfig -d %s -f %s --yes set_raw"
    QUERY_CMD_LINE = "mstconfig -d %s -f %s --yes get_raw"
    MCRA_CMD_LINE = "mstmcra %s 0xf0014.0:16"
    BLUE_FIELD_DEV_ID = 0x211
    BLUE_FIELD2_DEV_ID = 0x214
    TITLE = "MLNX_RAW_TLV_FILE\n"
    RAW_BYTES = "0x03000204 0x07000083 0x00000000"

    LIMITED = 0x10000000
    DISABLE_PORT_OWNER = 0x01
    DISABLE_COUNTER_RD = 0x02
    DISABLE_TRACER = 0x04
    DISABLE_RSHIM = 0x08

    RESTRICT_BYTES = "0x03000204 0x07000083 0x00000000 0x1000000f"
    PRIVILEGE_BYTES = "0x03000204 0x07000083 0x00000000 0x00000000"

    def __init__(self, device, query, privilege, disable_rshim, disable_tracer,
                 disable_counter_rd, disable_port_owner):
        self._privilege = privilege
        self._device = device
        self._query = query
        self._disable_rshim = disable_rshim
        self._disable_tracer = disable_tracer
        self._disable_counter_rd = disable_counter_rd
        self._disable_port_owner = disable_port_owner
        self._file_p = tempfile.NamedTemporaryFile(
            suffix='.raw', prefix="nvconfig_setting_")
        self._file_name = self._file_p.name
        self._nv_host_priv_conf = 0
        self._current_conf = None

    def updateTlvFile(self, print_info_msgs = False):
        if print_info_msgs:
            info("preparing configuration file...", end='')
        # use encode for compatibility with python 2/3
        self._file_p.seek(0)
        self._file_p.write(self.TITLE.encode())
        nv_host_priv_conf_str = '0x%08x' % self._nv_host_priv_conf
        conf_bytes = " ".join((self.RAW_BYTES, nv_host_priv_conf_str))
        self._file_p.write(conf_bytes.encode())
        self._file_p.flush()
        if print_info_msgs:
            print("Done!")

    @staticmethod
    def _exec_cmd(cmd):
        p = subprocess.Popen(cmd,
                             stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             universal_newlines=True,
                             shell=True)
        stdout, stderr = p.communicate()
        exit_code = p.wait()

        return (exit_code, stdout, stderr)

    def printTitle(self, title):
        print(title)
        print("-"*len(title))

    def printConfInfo(self):
        current_conf = self.queryConf()
        if current_conf is not None:
            self.printTitle("Current device configurations:")
            print("%-30s: %s"%("level", current_conf["level"]))
            self.printTitle("\nPort functions status:")
            print("%-30s: %s"%("disable_rshim", current_conf["disable_rshim"]))
            print("%-30s: %s"%("disable_tracer", current_conf["disable_tracer"]))
            print("%-30s: %s"%("disable_port_owner", current_conf["disable_port_owner"]))
            print("%-30s: %s\n"%("disable_counter_rd", current_conf["disable_counter_rd"]))
        return current_conf is None

    def queryConf(self):
        current_conf = {"level" : "PRIVILEGED", "disable_rshim": "FALSE",
                        "disable_tracer" : "FALSE", "disable_port_owner" : "FALSE",
                        "disable_counter_rd" : "FALSE"}
        # updateTlvFile file for query
        self.updateTlvFile()
        # run query operation
        cmd = self.QUERY_CMD_LINE % (self._device,self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)

        if exit_code != 0:
            error("Failed to query device configurations")
            return None
        else :
            indexOfData = stdout.index('Data') + 6
            conf_data = int(stdout[indexOfData:indexOfData+13], 16)
            level =  (conf_data & self.LIMITED) >> int(math.log(self.LIMITED, 2))
            disable_rshim = (conf_data & self.DISABLE_RSHIM) >>\
                                    int(math.log(self.DISABLE_RSHIM, 2))
            disable_tracer = (conf_data & self.DISABLE_TRACER) >>\
                                    int(math.log(self.DISABLE_TRACER, 2))
            disable_port_owner = (conf_data & self.DISABLE_PORT_OWNER) >>\
                                    int(math.log(self.DISABLE_PORT_OWNER, 2))
            disable_counter_rd = (conf_data & self.DISABLE_COUNTER_RD) >>\
                                    int(math.log(self.DISABLE_COUNTER_RD, 2))
            current_conf.update({"level": "RESTRICTED" if level else "PRIVILEGED"}) 
            current_conf.update({"disable_rshim": "TRUE" if disable_rshim else "FALSE"})
            current_conf.update({"disable_tracer": "TRUE" if disable_tracer else "FALSE"})
            current_conf.update({"disable_port_owner": "TRUE" if disable_port_owner else "FALSE"})
            current_conf.update({"disable_counter_rd": "TRUE" if disable_counter_rd else "FALSE"})
        return current_conf


    def setPrivConf(self, re_restrict):
        self._nv_host_priv_conf = 0
        self.updateTlvFile(not re_restrict)
        if not re_restrict:
            info("configuring device...", end='')
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if exit_code != 0 and not re_restrict:
            print("Failed")
            error("Removing the restriction only effective on the ARM side")
        if exit_code == 0 and not re_restrict:
            print("Done!")
        return exit_code

    def setRestrictConf(self):
        self._nv_host_priv_conf = self.LIMITED
        if self._disable_rshim:
            self._nv_host_priv_conf |= self.DISABLE_RSHIM
        if self._disable_tracer:
            self._nv_host_priv_conf |= self.DISABLE_TRACER
        if self._disable_counter_rd:
            self._nv_host_priv_conf |= self.DISABLE_COUNTER_RD
        if self._disable_port_owner:
            self._nv_host_priv_conf |= self.DISABLE_PORT_OWNER
        self.updateTlvFile(True)
        info("configuring device...", end='')
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if exit_code != 0:
            print("Failed")
            info("Host is already restricted")
            exit_code = 0
        else:
            print("Done!")
        return exit_code

    def setConf(self):
        current_conf = self.queryConf()
        exit_code = 0
        if (not self._privilege) and current_conf and (current_conf["level"] == "RESTRICTED"):
            self.setPrivConf(True)
            self.setRestrictConf()
        elif not self._privilege:
            self.setRestrictConf()
        elif self._privilege:
            exit_code = self.setPrivConf(False)
        return exit_code

    def configure(self):
        if self._query:
            return self.printConfInfo()
        else:
            return self.setConf()

    def cleanup(self):
        self._file_p.close()
        if os.path.isfile(self._file_name):
            os.remove(self._file_name)

    def validate(self):
        # get device ID
        cmd_line = self.MCRA_CMD_LINE % self._device
        exit_code, stdout, _ = self._exec_cmd(cmd_line)
        if exit_code != 0:
            raise PrivilegeException("Unknown device '%s'!" % self._device)
        dev_id = int(stdout, 16)
        if dev_id not in (self.BLUE_FIELD_DEV_ID, self.BLUE_FIELD2_DEV_ID):
            raise PrivilegeException(
                "Device '%s' is not supported, "
                "only BlueField devices are supported!" % self._device)


def parse_args():
    parser = argparse.ArgumentParser(
        prog=PROG, description=DESCRIPTION,
        formatter_class=argparse.RawTextHelpFormatter)
    version = tools_version.GetVersionString(PROG, TOOL_VERSION)
    parser.add_argument("-v", "--version", action="version", version=version,
                        help="show program's version number and exit")
    # options arguments
    options_group = parser.add_argument_group('Options')
    options_group.add_argument(
        '--device',
        '-d',
        required=True,
        help='Device to work with.')

    # command arguments
    command_group = parser.add_argument_group('Commands')
    command_group.add_argument(
        'command',
        nargs=1,
        choices=["r", "restrict", "p", "privilege", "q", "query"],
        help=CMD_HELP)
    options_group.add_argument('--disable_rshim', action="store_true",
                               help=DISABLE_RSHIM_HELP)
    options_group.add_argument('--disable_tracer', action="store_true",
                               help=DISABLE_TRACER_HELP)
    options_group.add_argument('--disable_counter_rd', action="store_true",
                               help=DISABLE_COUNTER_RD_HELP)
    options_group.add_argument('--disable_port_owner', action="store_true",
                               help=DISABLE_PORT_OWNER_HELP)
    args = parser.parse_args()
    
    disable_flags = args.disable_rshim or args.disable_tracer or \
                args.disable_counter_rd or args.disable_port_owner
    rest_flags = args.command[0] in ("r", "restrict")
    priv_flags = args.command[0] in ("p", "privilege")
    query_flags = args.command[0] in ("q", "query")
    if priv_flags and disable_flags:
        parser.error("disable flags are not allowed in privilege mode")
    if query_flags and (priv_flags or rest_flags or disable_flags):
        parser.error("privilege or restrict commands are not allowed with query")
    return args


def main():
    args = parse_args()
    device = args.device
    command = args.command[0]
    query = False
    privilege = False
    if command in ("p", "privilege"):
        privilege = True
    elif command in ("r", "restrict"):
        privilege = False
    elif command in ("q", "query"):
        query = True
    retcode = 0
    mgr = PrivilegeMgr(device,query, privilege, args.disable_rshim,
                       args.disable_tracer, args.disable_counter_rd,
                       args.disable_port_owner)
    try:
        mgr.validate()
        mgr.updateTlvFile()
        retcode = mgr.configure()
    except PrivilegeException as exc:
        error(str(exc))
        retcode = 1
    except Exception as exc:
        error("got an error: %s", str(exc))
        retcode = 1
    except(KeyboardInterrupt, SystemExit):
        print("\nInterrupted!\nExiting")
        retcode = 1
    finally:
        mgr.cleanup()
    return retcode


if __name__ == "__main__":
    sys.exit(main())
