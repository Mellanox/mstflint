# Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# --

import regaccess
from mlxfwresetlib.cmd_reg_mfrl import ResetReqMethod
from mlxfwresetlib.cmd_reg_mcam import CmdRegMcam


class CmdNotSupported(Exception):
    pass


class CmdRegMroq():

    LEGACY_FLOW, SYNCED_DRIVER_FLOW, SYNCED_TOOL_FLOW = 0, 1, 2
    pci_sync_db = [
        {'flow': LEGACY_FLOW, 'description': 'Tool is the owner', 'mask': 0b1},
        {'flow': SYNCED_DRIVER_FLOW, 'description': 'NIC Driver is the owner', 'mask': 0b10},
        {'flow': SYNCED_TOOL_FLOW, 'description': 'FW is the owner', 'mask': 0b100},
    ]

    pci_reset_method_db = [
        {'method': ResetReqMethod.LINK_DISABLE, 'description': 'Link Disable method', 'mask': 0b1},
        {'method': ResetReqMethod.HOT_RESET, 'description': 'Hot reset (SBR)', 'mask': 0b10},
    ]

    def __init__(self, reset_type, reg_access, mcam, logger):
        self._reg_access = reg_access
        self._logger = logger
        self._mroq_is_supported = False
        if mcam.is_mroq_supported():
            try:
                reg = self._read_reg(reset_type)
                self._mroq_is_supported = True
                self._pci_sync_for_fw_update_start = reg['pci_sync_for_fw_update_start']
                self._pci_reset_req_method = reg['pci_reset_req_method']
            except BaseException:
                pass

    def _read_reg(self, reset_type):
        try:
            self._logger.debug("sending MROQ with reset_type={}".format(reset_type))
            pci_sync_for_fw_update_start, pci_reset_req_method = self._reg_access.sendMROQ(reset_type)

        except regaccess.RegAccException as e:
            raise e

        self._logger.debug("pci_sync_for_fw_update_start={}, pci_reset_req_method={}".format(pci_sync_for_fw_update_start, pci_reset_req_method))
        return {
            'pci_reset_req_method': pci_reset_req_method,
            'pci_sync_for_fw_update_start': pci_sync_for_fw_update_start,
        }

    def print_query_text(self, tool_owner_support, is_pcie_switch):
        if self._mroq_is_supported is False:
            return

        result = ""
        result += "Reset sync (relevant only for reset-level 3):"
        result += "\n"
        default_found = False
        for field in CmdRegMroq.pci_sync_db:
            pci_sync_supported = (field["mask"] & self._pci_sync_for_fw_update_start) != 0
            if field["flow"] is CmdRegMroq.LEGACY_FLOW and tool_owner_support is False:
                result += "{0}: {1:<62}-{2:<14}\n".format(field["flow"], field["description"], "Not Supported")
                continue
            if pci_sync_supported is True:
                result += "{0}: {1:<62}-{2:<14}{3}\n".format(field["flow"], field["description"], "Supported", "(default)" if not default_found else "")
                default_found = True
            else:
                result += "{0}: {1:<62}-{2:<14}\n".format(field["flow"], field["description"], "Not Supported")
        print(result)

        result = ""
        result += "Reset request method (relevant only for reset-level 3):"
        result += "\n"
        # Determine default method based on conditions
        default_method = None

        if is_pcie_switch:
            # If PCIe switch and HOT_RESET is supported, make it default
            for field in CmdRegMroq.pci_reset_method_db:
                if field["method"] == ResetReqMethod.HOT_RESET and (field["mask"] & self._pci_reset_req_method) != 0:
                    default_method = ResetReqMethod.HOT_RESET
                    break

            # If PCIe switch but HOT_RESET is not supported, fallback to LINK_DISABLE if supported
            if default_method is None:
                for field in CmdRegMroq.pci_reset_method_db:
                    if field["method"] == ResetReqMethod.LINK_DISABLE and (field["mask"] & self._pci_reset_req_method) != 0:
                        default_method = ResetReqMethod.LINK_DISABLE
                        break
        else:
            # Not a PCIe switch, set the lowest supported value as default
            for field in CmdRegMroq.pci_reset_method_db:
                if (field["mask"] & self._pci_reset_req_method) != 0:
                    default_method = field["method"]
                    break

        for field in CmdRegMroq.pci_reset_method_db:
            pci_sync_supported = (field["mask"] & self._pci_reset_req_method) != 0
            is_default = field["method"] == default_method

            result += "{0}: {1:<62}-{2:<14}{3}\n".format(
                field["method"],
                field["description"],
                "Supported" if pci_sync_supported else "Not Supported",
                "(default)" if is_default else ""
            )

        print(result)

    def is_hot_reset_supported(self):
        if self._mroq_is_supported is False:
            return False

        return True if (self._pci_reset_req_method & ResetReqMethod.HOT_RESET) else False

    def mroq_is_supported(self):
        return self._mroq_is_supported

    def get_default_method(self, is_pcie_switch):
        default = ResetReqMethod.LINK_DISABLE

        if is_pcie_switch and self.is_hot_reset_supported():
            default = ResetReqMethod.HOT_RESET

        return default
