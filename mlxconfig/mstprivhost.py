# Copyright (c) 2004-2021 Mellanox Technologies LTD. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --


from __future__ import print_function

import argparse
import os
import subprocess
import sys
import tempfile
import re
import tools_version

PROG = 'mstprivhost'
TOOL_VERSION = "1.0.0"

DEV_HELP = """\
Perform operation for a specified mst device.
"""

CMD_HELP = """\
restrict:  Set external hosts restricted.
privilege: Set external hosts privileged.
query:     From external HOST: query the status of the host
           From Embedded ARM CPU: query the status of all external hosts.
"""

QUERY_FULL_HELP = """\
Run with query command for high verbosity level - valid from embedded ARM CPU only.
"""

DESCRIPTION = """\
restrict or privilege host
Note: New configurations takes effect immediately.
Note: privileged host - host has all supported privileges.
      restricted host - host capabilities are limited.
"""

DISABLE_RSHIM_HELP = """\
When TRUE, the host does not have an RSHIM function to access the embedded CPU
registers (power cycle is required to apply changes)
"""

DISABLE_TRACER_HELP = """\
When TRUE, the host will not be allowed to own the Tracer
(requires FW reset to be applied)
"""

DISABLE_COUNTER_RD_HELP = """\
When TRUE, the host will not be allowed to read Physical port counters
(requires FW reset to be applied)
"""

DISABLE_PORT_OWNER_HELP = """\
When TRUE, the host will not be allowed to be Port Owner
(requires FW reset to be applied)
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
    CONFIG_CMD_LINE = "mlxconfig -d %s -f %s --yes set_raw"
    QUERY_CMD_LINE = "mlxconfig -d %s -f %s --yes get_raw"
    QUERY_MMHI_CMD_LINE = "mlxreg -d %s --reg_name MMHI --get"
    QUERY_NVGC_CMD_LINE = "mlxreg -d %s --reg_name MNVGC --get"
    QUERY_HW_ACCESS_STATUS = "mlxreg -d %s --reg_id 0x402d --reg_len 0x4 --get"
    MCRA_CMD_LINE = "mcra %s 0xf0014.0:16"
    TLV_DATA_RE = re.compile(r'Data\s*:\s*(.+)\n', flags=re.MULTILINE)

    BLUE_FIELD_DEV_ID = 0x211
    BLUE_FIELD2_DEV_ID = 0x214
    BLUE_FIELD3_DEV_ID = 0x21c

    PRIVILEGE = 0
    RESTRICT = 1

    TITLE = "MLNX_RAW_TLV_FILE"
    TLV_HEADER = 0x03000204
    CRC = 0x0
    TLV_TYPE = 0x07000083

    LIMITED = 0x10000000
    DISABLE_PORT_OWNER = 0x01
    DISABLE_COUNTER_RD = 0x02
    DISABLE_TRACER = 0x04
    DISABLE_RSHIM = 0x08

    def __init__(self, device, query, q_full, level, port_functions):
        self._requested_level = level
        self._device = device
        self._query = query
        self._q_full = q_full
        self._port_function = port_functions
        self._file_p = tempfile.NamedTemporaryFile(suffix='.raw',
                                                   prefix="nvconfig_setting_")
        self._file_name = self._file_p.name
        self._nv_host_priv_conf = 0
        self._current_conf = None
        self._current_host = 0
        self._total_hosts = 1
        self._isMH = False
        self._isARM = False
        self._disable_out = False

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

    def run(self):
        self.validate()
        self.initParams()
        if self._query:
            return self.getConf()
        else:
            return self.setConf()

    def initParams(self):
        priv_other_host = False
        cmd = self.QUERY_NVGC_CMD_LINE % (self._device)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if not exit_code:
            priv_other_host = self.getFieldFromReg(
                stdout, "priv_nv_other_host")
            if priv_other_host == 1:
                self._isARM = True
                cmd = self.QUERY_MMHI_CMD_LINE % (self._device)
                exit_code, stdout, stderr = self._exec_cmd(cmd)
                if not exit_code:
                    self._current_host = self.getFieldFromReg(
                        stdout, "host_number")
                    host_en_mask = self.getFieldFromReg(stdout, "host_en")
                    # don't count the ARM index (last bit)
                    self._total_hosts = bin(host_en_mask).count("1") - 1
                self._isMH = self._total_hosts > 1
        elif self.isHwAccessDisabled():
            raise PrivilegeException("Secure host enabled on the device")
        else:
            raise PrivilegeException(stderr.replace("-E- ", ""))

    def isHwAccessDisabled(self):
        hw_disable = 0
        cmd = self.QUERY_HW_ACCESS_STATUS % (self._device)
        exit_code, stdout, _ = self._exec_cmd(cmd)
        if not exit_code:
            hw_disable = int(stdout.splitlines()[4].split('|')[1], 16) & 0xff
        return hw_disable

    def getFieldFromReg(self, reg_output, field_name):
        field_value = None
        for line in reg_output.splitlines():
            if line.startswith(field_name):
                field_value = int(line.split()[2], 16)
                break
        return field_value

    def updateTlvFile(self, host_index, disable_info=False):
        self.TLV_TYPE |= (host_index << 18)
        raw_bytes = "%s\n0x%08x 0x%08x 0x%08x" % (self.TITLE,
                                                  self.TLV_HEADER,
                                                  self.TLV_TYPE,
                                                  self.CRC)
        if not disable_info:
            info(
                "preparing configuration file...",
                end='',
                hide=self._disable_out)
        # use encode for compatibility with python 2/3
        priv_conf_data = '0x%08x' % self._nv_host_priv_conf
        conf_bytes = " ".join((raw_bytes, priv_conf_data))
        self._file_p.seek(0)
        self._file_p.write(conf_bytes.encode())
        self._file_p.flush()
        if not disable_info:
            self.printCmd("Done!")

    def printTitle(self, title):
        print(title)
        print("-" * len(title))

    def printCmd(self, msg):
        if not self._disable_out:
            print(msg)

    def printConfOut(self, priv_conf):
        self.printTitle("Host configurations")
        if self._q_full:
            self.printCmd(
                "%-30s: %s" %
                ("host index", priv_conf["host index"]))
        self.printCmd("%-30s: %s" % ("level", priv_conf["level"]))
        self.printTitle("\nPort functions status:")
        self.printCmd(
            "%-30s: %s" %
            ("disable_rshim", priv_conf["disable_rshim"]))
        self.printCmd(
            "%-30s: %s" %
            ("disable_tracer", priv_conf["disable_tracer"]))
        self.printCmd(
            "%-30s: %s" %
            ("disable_port_owner",
             priv_conf["disable_port_owner"]))
        self.printCmd(
            "%-30s: %s\n" %
            ("disable_counter_rd",
             priv_conf["disable_counter_rd"]))

    def getConf(self):
        if self._q_full and not self._isARM:
            raise PrivilegeException(
                "Query command with verbose option is not valid from host")
        current_conf = self.queryConf(0)
        # Get all host's status if (full) flag provided
        if self._q_full:
            for host in range(self._total_hosts):
                # Skip the first host info, it's already collected above in
                # current_conf
                if host == 0:
                    continue
                host_conf = self.queryConf(host)
                current_conf.update({"host index": "%-13s%-13s" %
                                     (current_conf["host index"], host_conf["host index"])})
                current_conf.update({"level": "%-13s%-13s" %
                                     (current_conf["level"], host_conf["level"])})
                current_conf.update({"disable_rshim": "%-13s%-13s" %
                                     (current_conf["disable_rshim"], host_conf["disable_rshim"])})
                current_conf.update({"disable_tracer": "%-13s%-13s" %
                                     (current_conf["disable_tracer"], host_conf["disable_tracer"])})
                current_conf.update(
                    {
                        "disable_port_owner": "%-13s%-13s" %
                        (current_conf["disable_port_owner"],
                         host_conf["disable_port_owner"])})
                current_conf.update(
                    {
                        "disable_counter_rd": "%-13s%-13s" %
                        (current_conf["disable_counter_rd"],
                         host_conf["disable_counter_rd"])})
        self.printConfOut(current_conf)
        # If no configuration queried, then return error code 1
        return len(current_conf) == 0

    def parseRawTlv(self, host_index, data, valid):
        tlv = {"host index": host_index, "level": "PRIVILEGED",
               "disable_rshim": "FALSE", "disable_tracer": "FALSE",
               "disable_port_owner": "FALSE", "disable_counter_rd": "FALSE"}
        if valid:
            conf_data = int(self.TLV_DATA_RE.search(data).group(1), 16)
            level = int((conf_data & self.LIMITED) / self.LIMITED)
            disable_rshim = (conf_data & self.DISABLE_RSHIM) / \
                self.DISABLE_RSHIM
            disable_tracer = (
                conf_data & self.DISABLE_TRACER) / self.DISABLE_TRACER
            disable_port_owner = (
                conf_data & self.DISABLE_PORT_OWNER) / self.DISABLE_PORT_OWNER
            disable_counter_rd = (
                conf_data & self.DISABLE_COUNTER_RD) / self.DISABLE_COUNTER_RD
            tlv.update({"level": ("PRIVILEGED", "RESTRICTED")[level]})
            tlv.update({"disable_rshim": str(bool(disable_rshim)).upper()})
            tlv.update({"disable_tracer": str(bool(disable_tracer)).upper()})
            tlv.update({"disable_port_owner": str(
                bool(disable_port_owner)).upper()})
            tlv.update({"disable_counter_rd": str(
                bool(disable_counter_rd)).upper()})
        return tlv

    def queryConf(self, host_index):
        # UpdateTlvFile file for query
        self.updateTlvFile(host_index, True)
        # Run query operation
        cmd = self.QUERY_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, _ = self._exec_cmd(cmd)
        return self.parseRawTlv(host_index, stdout, not exit_code)

    def setPrivilegeConf(self, host_index, disable_info=False):
        self._nv_host_priv_conf = 0
        self.updateTlvFile(host_index, disable_info)
        if not disable_info:
            info("configuring device...", end='', hide=self._disable_out)
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if not disable_info:
            if not exit_code:
                self.printCmd("Done!")
            else:
                self.printCmd("Failed")
        return exit_code

    def setRestrictConf(self, host_index):
        current_conf = self.queryConf(host_index)
        # If host is restricted, remove the restiction to applay the new
        # restrict command
        if current_conf["level"] == "RESTRICTED":
            self.setPrivilegeConf(host_index, disable_info=True)
        # Update the TLV with the restriction bytes and port function
        # configuration
        self._nv_host_priv_conf = self.LIMITED
        for pf in self._port_function:
            self._nv_host_priv_conf |= self._port_function[pf]
        self.updateTlvFile(host_index)
        # Send the new configuration by mlxconfig
        info("configuring device...", end='', hide=self._disable_out)
        cmd = self.CONFIG_CMD_LINE % (self._device, self._file_name)
        exit_code, stdout, stderr = self._exec_cmd(cmd)
        if not exit_code:
            self.printCmd("Done!")
        else:
            self.printCmd("Failed")
        return exit_code

    def setConf(self):
        exit_code = 0
        if self._isARM:
            for host in range(self._total_hosts):
                if self._requested_level == self.RESTRICT:
                    exit_code = self.setRestrictConf(host)
                elif self._requested_level == self.PRIVILEGE:
                    exit_code = self.setPrivilegeConf(host)
                self._disable_out = True
        else:
            error("Operation is not permitted (refer to the DPU user manual)")
            exit_code = 1
        return exit_code

    def validate(self):
        # get device ID
        cmd_line = self.MCRA_CMD_LINE % self._device
        exit_code, stdout, _ = self._exec_cmd(cmd_line)
        if exit_code != 0:
            raise PrivilegeException("Unknown device '%s'!" % self._device)
        dev_id = int(stdout, 16)
        if dev_id not in (self.BLUE_FIELD_DEV_ID,
                          self.BLUE_FIELD2_DEV_ID,
                          self.BLUE_FIELD3_DEV_ID):
            raise PrivilegeException(
                "Device '%s' is not supported, "
                "only BlueField devices are supported!" %
                self._device)

    def cleanup(self):
        self._file_p.close()
        if os.path.isfile(self._file_name):
            os.remove(self._file_name)


def parse_args():
    parser = argparse.ArgumentParser(
        prog=PROG,
        description=DESCRIPTION,
        formatter_class=argparse.RawTextHelpFormatter)
    version = tools_version.GetVersionString(PROG, TOOL_VERSION)
    parser.add_argument("-v", "--version", action="version", version=version,
                        help="show program's version number and exit")
    # options arguments
    options_group = parser.add_argument_group('Options')
    options_group.add_argument(
        '-d',
        '--device',
        required=True,
        metavar='<dev>',
        help=DEV_HELP)
    restrict_options_group = parser.add_argument_group('Restrict Options')
    restrict_options_group.add_argument('--disable_rshim', action="store_true",
                                        help=DISABLE_RSHIM_HELP)
    restrict_options_group.add_argument(
        '--disable_tracer',
        action="store_true",
        help=DISABLE_TRACER_HELP)
    restrict_options_group.add_argument(
        '--disable_counter_rd',
        action="store_true",
        help=DISABLE_COUNTER_RD_HELP)
    restrict_options_group.add_argument(
        '--disable_port_owner',
        action="store_true",
        help=DISABLE_PORT_OWNER_HELP)
    query_options_group = parser.add_argument_group('Query Options')
    query_options_group.add_argument('--full', '-f', action="store_true",
                                     help=QUERY_FULL_HELP)
    # command arguments
    command_group = parser.add_argument_group('Commands')
    command_group.add_argument(
        'command',
        nargs='?',
        choices=[
            "r",
            "restrict",
            "p",
            "privilege",
            "q",
            "query"],
        help=CMD_HELP)

    args = parser.parse_args()

    if args.command is None:
        parser.error(
            "Please provide a command to execute, check the help menu")

    disable_flags = args.disable_rshim or args.disable_tracer or \
        args.disable_counter_rd or args.disable_port_owner
    q_full_flag = args.full
    rest_flags = args.command in ("r", "restrict")
    priv_flags = args.command in ("p", "privilege")
    query_flags = args.command in ("q", "query")
    if priv_flags and disable_flags:
        parser.error("disable flags are not allowed in privilege mode")
    if query_flags and (priv_flags or rest_flags or disable_flags):
        parser.error(
            "privilege or restrict commands are not allowed with query")
    if q_full_flag and not query_flags:
        parser.error("The verbose option is allowed with query only")

    return args


def main():
    args = parse_args()
    device = args.device
    command = args.command
    query = False
    level = PrivilegeMgr.PRIVILEGE
    rc = 0
    if command in ("r", "restrict"):
        level = PrivilegeMgr.RESTRICT
    elif command in ("q", "query"):
        query = True
    port_functions = {
        "disable_rshim": (0, PrivilegeMgr.DISABLE_RSHIM)[args.disable_rshim],
        "disable_tracer": (0, PrivilegeMgr.DISABLE_TRACER)[args.disable_tracer],
        "disable_counter_rd": (0, PrivilegeMgr.DISABLE_COUNTER_RD)[args.disable_counter_rd],
        "disable_port_owner": (0, PrivilegeMgr.DISABLE_PORT_OWNER)[args.disable_port_owner]}
    mgr = PrivilegeMgr(device, query, args.full, level, port_functions)
    try:
        rc = mgr.run()
    except PrivilegeException as exc:
        error(str(exc))
        rc = 1
    except Exception as exc:
        error("-E- %s", str(exc))
        rc = 1
    except(KeyboardInterrupt, SystemExit):
        print("\nInterrupted!\nExiting")
        rc = 1
    finally:
        mgr.cleanup()
    return rc


if __name__ == "__main__":
    sys.exit(main())
