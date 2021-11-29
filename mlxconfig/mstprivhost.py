#copyright (c) 2004-2021 Mellanox Technologies LTD. All rights reserved.   
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
restrict:  Set all external hosts restricted except the one that called the command.
privilege: Set all external hosts privileged except the one that called the command.
query:     From external host: query the status of the host
           From Embedded Arm CPU: query if all external hosts are restricted.
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
Reboot is required to apply changes
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
    if kw.get('hide') is None or kw.get('hide') is False:
        _log("-I-", msg, *args, **kw)


def error(msg, *args, **kw):
    if kw.get('hide') is None or kw.get('hide') is False:
        _log("-E-", msg, *args, **kw)


class PrivilegeException(Exception):
    pass


class PrivilegeMgr(object):
    CONFIG_CMD_LINE = "mstconfig -d %s -f %s --yes set_raw"
    QUERY_CMD_LINE = "mstconfig -d %s -f %s --yes get_raw"
    QUERY_MMHI_CMD_LINE = "mstreg -d %s --reg_name MMHI --get"
    QUERY_SECURE_FW_STATUS = "mlxreg -d %s --reg_name MGIR --get"
    QUERY_HW_ACCESS_STATUS = "flint -d %s -ocr hw query"

    MMHI_HOST_EN_FIELD = "host_en"
    MMHI_HOST_NUMBER_FIELD = "host_number"
    MCRA_CMD_LINE = "mstmcra %s 0xf0014.0:16"
    BLUE_FIELD_DEV_ID = 0x211
    BLUE_FIELD2_DEV_ID = 0x214
    BLUE_FIELD3_DEV_ID = 0x21c
    TITLE = "MLNX_RAW_TLV_FILE\n"

    TLV_HEADER = "0x03000204"
    CRC = "0x00000000"
    TLV_TYPE = 0x07000083

    LIMITED = 0x10000000
    DISABLE_PORT_OWNER = 0x01
    DISABLE_COUNTER_RD = 0x02
    DISABLE_TRACER = 0x04
    DISABLE_RSHIM = 0x08

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
        self._current_host, self._total_hosts = self.getNumberOfHosts()
        self._isMH = self._total_hosts > 1
        self._isARM = self._current_host == self._total_hosts;
        self._disable_out = False
        self._oldFw = False  # Fw has invalid MMHi register

    def updateTlvFile(self, host_number, print_info_msgs=False):
        tlv_type = self.TLV_TYPE
        tlv_type |= (host_number << 18)
        raw_bytes = "%s 0x%08x %s" % (self.TLV_HEADER, tlv_type, self.CRC)
        if print_info_msgs:
            info("preparing configuration file...", end='', hide=self._disable_out)
        # use encode for compatibility with python 2/3
        self._file_p.seek(0)
        self._file_p.write(self.TITLE.encode())
        nv_host_priv_conf_str = '0x%08x' % self._nv_host_priv_conf
        conf_bytes = " ".join((raw_bytes, nv_host_priv_conf_str))
        self._file_p.write(conf_bytes.encode())
        self._file_p.flush()
        if print_info_msgs:
            self.printCmd("Done!")

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

    def printCmd(self, msg):
        if not self._disable_out:
            print(msg)

    def printConfOut(self, priv_conf):
        self.printTitle("Host configurations")
        self.printCmd("%-30s: %s" % ("level", priv_conf["level"]))
        self.printTitle("\nPort functions status:")
        self.printCmd("%-30s: %s" % ("disable_rshim", priv_conf["disable_rshim"]))
        self.printCmd("%-30s: %s" % ("disable_tracer", priv_conf["disable_tracer"]))
        self.printCmd("%-30s: %s" % ("disable_port_owner", priv_conf["disable_port_owner"]))
        self.printCmd("%-30s: %s\n" % ("disable_counter_rd", priv_conf["disable_counter_rd"]))

    def getConf(self):
        current_conf = self.queryConf(self._current_host)
        if current_conf is not None and current_conf["level"] == "PRIVILEGED":
            for host in range(self._total_hosts):
                current_conf = self.queryConf(host)
                if current_conf["level"] == "PRIVILEGED":
                    break
        if current_conf is not None:
            self.printConfOut(current_conf)
        return current_conf is None

    def isHwAccessDisabled(self):
        cmd = self.QUERY_HW_ACCESS_STATUS % (self._device)
        exit_code, _, _ = self._exec_cmd(cmd)
        return exit_code != 0

    def isFWSecured(self):
        is_secured = False
        cmd = self.QUERY_SECURE_FW_STATUS % (self._device)
        exit_code, stdout, stderr  = self._exec_cmd(cmd)
        mgir_out = stdout.split("\n")
        if exit_code == 0:
            for line in mgir_out:
                if line.startswith("secured"):
                    is_secured = int(line.split()[2], 16)
        return is_secured

    def getNumberOfHosts(self):
        total_host_num = 1
        host_number = 0
        cmd = self.QUERY_MMHI_CMD_LINE % (self._device)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if exit_code != 0:
            self._oldFw = True
            return host_number, total_host_num

        # parsing MMHI from mlxreg out
        mmhi_out_lines = stdout.split("\n")
        for line in mmhi_out_lines:
            if line.startswith(self.MMHI_HOST_NUMBER_FIELD):
                host_number = int(line.split()[2], 16)
            elif line.startswith(self.MMHI_HOST_EN_FIELD):
                host_en = int(line.split()[2], 16)
                if host_en == 0xff and host_number == 0:
                    self._oldFw = True
                    return host_number, total_host_num
                total_host_num = bin(host_en).count("1")
                if total_host_num > 16:
                    raise Exception("Failed to parse MMHI register")
        return host_number, total_host_num

    def queryConf(self, host_number, hide=False):
        current_conf = {"host_number":host_number, "level": "PRIVILEGED",
                        "disable_rshim": "FALSE", "disable_tracer": "FALSE",
                        "disable_port_owner": "FALSE", "disable_counter_rd": "FALSE"}
        # UpdateTlvFile file for query
        self.updateTlvFile(host_number)
        # Run query operation
        cmd = self.QUERY_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)

        if exit_code != 0:
            error("Failed to query device configurations", hide=self._disable_out or hide)
            if self.isHwAccessDisabled():
                error("Secure host enabled on the device", hide=self._disable_out or hide)
            return current_conf if self._disable_out else None
        else:
            indexOfData = stdout.index('Data') + 6
            conf_data = int(stdout[indexOfData:indexOfData + 13], 16)
            level = (conf_data & self.LIMITED) >> int(math.log(self.LIMITED, 2))
            disable_rshim = (conf_data & self.DISABLE_RSHIM) >> \
                                    int(math.log(self.DISABLE_RSHIM, 2))
            disable_tracer = (conf_data & self.DISABLE_TRACER) >> \
                                    int(math.log(self.DISABLE_TRACER, 2))
            disable_port_owner = (conf_data & self.DISABLE_PORT_OWNER) >> \
                                    int(math.log(self.DISABLE_PORT_OWNER, 2))
            disable_counter_rd = (conf_data & self.DISABLE_COUNTER_RD) >> \
                                    int(math.log(self.DISABLE_COUNTER_RD, 2))
            current_conf.update({"level": "RESTRICTED" if level else "PRIVILEGED"})
            current_conf.update({"disable_rshim": "TRUE" if disable_rshim else "FALSE"})
            current_conf.update({"disable_tracer": "TRUE" if disable_tracer else "FALSE"})
            current_conf.update({"disable_port_owner": "TRUE" if disable_port_owner else "FALSE"})
            current_conf.update({"disable_counter_rd": "TRUE" if disable_counter_rd else "FALSE"})
        return current_conf

    def setPrivConf(self, re_restrict, host_number):
        self._nv_host_priv_conf = 0
        self.updateTlvFile(host_number, not re_restrict)
        if not re_restrict:
            info("configuring device...", end='', hide=self._disable_out)
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if exit_code != 0 and not re_restrict:
            current_conf = self.queryConf(host_number, True)
            self.printCmd("Failed")
            if current_conf is None:
                error("Secure host enabled on the device", hide=self._disable_out)
            else:
                error("Removing the restriction only effective on the ARM side", hide=self._disable_out)
        if exit_code == 0 and not re_restrict:
            self.printCmd("Done!")
        return exit_code

    def setRestrictConf(self, host_number):
        self._nv_host_priv_conf = self.LIMITED
        if self._disable_rshim:
            self._nv_host_priv_conf |= self.DISABLE_RSHIM
        if self._disable_tracer:
            self._nv_host_priv_conf |= self.DISABLE_TRACER
        if self._disable_counter_rd:
            self._nv_host_priv_conf |= self.DISABLE_COUNTER_RD
        if self._disable_port_owner:
            self._nv_host_priv_conf |= self.DISABLE_PORT_OWNER
        self.updateTlvFile(host_number, True)
        info("configuring device...", end='', hide=self._disable_out)
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if exit_code != 0:
            self.printCmd("Failed")
            if self.isHwAccessDisabled():
                error("Secure host enabled on the device", hide=self._disable_out)
            else:
                error("Host is already restricted", hide=self._disable_out)
            exit_code = 0
        else:
            self.printCmd("Done!")
        return exit_code

    def setConf(self):
        exit_code = 0
        for host in range(self._total_hosts):
            if host == self._current_host and self._isMH:
                continue
            current_conf = self.queryConf(host, True)
            if current_conf and (not self._privilege) and (current_conf["level"] == "RESTRICTED"):
                # If current state is restricted and user tried to do re-restriction
                rc = self.setPrivConf(True, host)
                if rc == 0:
                    self.setRestrictConf(host)
                else:
                    # If user tried to do re-restrction from host, it will fail
                    # it should be done from ARM only
                    error("Host is already restricted", hide=self._disable_out)
            elif not self._privilege:
                # Execute restrict command with flag r
                if not self._isMH and not self._isARM:
                    error("There is only a single host, it cannot restrict itself", hide=self._disable_out)
                    exit_code = 1
                else:
                    exit_code = self.setRestrictConf(host)
            elif self._privilege:
                # Excute privlidge command with flag p
                exit_code = self.setPrivConf(False, host)
            # All other hosts are having the same output
            if not self._disable_out:
                self._disable_out = True
        if self._oldFw:
            info("Notice, you are using old FW version. In order of Multi-Host system FW must be updated")
        return exit_code

    def configure(self):
        if self._query:
            return self.getConf()
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
        if dev_id not in (self.BLUE_FIELD_DEV_ID, self.BLUE_FIELD2_DEV_ID, self.BLUE_FIELD3_DEV_ID):
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
    mgr = PrivilegeMgr(device, query, privilege, args.disable_rshim,
                       args.disable_tracer, args.disable_counter_rd,
                       args.disable_port_owner)
    try:
        mgr.validate()
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
