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
import platform
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
                if platform.system() == "Windows":
                    self._pci_reset_req_method = self._pci_reset_req_method & ~CmdRegMroq.pci_reset_method_db[ResetReqMethod.HOT_RESET]['mask']
                    self._pci_sync_for_fw_update_start = self._pci_sync_for_fw_update_start & ~CmdRegMroq.pci_sync_db[CmdRegMroq.SYNCED_TOOL_FLOW]['mask']

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

    def print_query_text(self, is_pcie_switch, tool_owner_support):
        if self._mroq_is_supported is False:
            return

        result = ""
        result += "Reset sync (relevant only for reset-level 3):"
        result += "\n"
        default_found = False
        for field in CmdRegMroq.pci_sync_db:
            pci_sync_supported = (field["mask"] & self._pci_sync_for_fw_update_start) != 0
            if field["flow"] is CmdRegMroq.LEGACY_FLOW and tool_owner_support is False:
                pci_sync_supported = False

            if pci_sync_supported is True:
                result += "{0}: {1:<62}-{2:<14}{3}\n".format(field["flow"], field["description"], "Supported", "(default)" if not default_found else "")
                default_found = True
            else:
                result += "{0}: {1:<62}-{2:<14}\n".format(field["flow"], field["description"], "Not Supported")
        print(result)

        result = ""
        result += "Reset request method (relevant only for reset-level 3):"
        result += "\n"

        default_method = self.get_default_method(is_pcie_switch)

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

    def get_default_method(self, is_pcie_switch):
        if self._mroq_is_supported is False:
            return ResetReqMethod.LINK_DISABLE

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
            is_sync_2_only_supported = False
            # Reset sync 2 is the only supproted sync.
            for sync in CmdRegMroq.pci_sync_db:
                if sync["flow"] == CmdRegMroq.SYNCED_TOOL_FLOW:
                    is_synced_tool_flow_supported = self._pci_sync_for_fw_update_start & sync["mask"]
                    no_other_syncs_supported = self._pci_sync_for_fw_update_start & ~sync["mask"] == 0
                    if is_synced_tool_flow_supported and no_other_syncs_supported:
                        is_sync_2_only_supported = True
                    break
            if is_sync_2_only_supported:
                default_method = ResetReqMethod.HOT_RESET
            else:
                # Set the lowest supported value as default
                for field in CmdRegMroq.pci_reset_method_db:
                    if (field["mask"] & self._pci_reset_req_method) != 0:
                        default_method = field["method"]
                        break

        return default_method

    def is_hot_reset_supported(self):
        if self._mroq_is_supported is False:
            return False

        return bool(self._pci_reset_req_method & CmdRegMroq.pci_reset_method_db[ResetReqMethod.HOT_RESET]['mask'])

    def mroq_is_supported(self):
        return self._mroq_is_supported
    def is_sync_supported(self, reset_sync, logger):
        if self.mroq_is_supported() is False:
            raise Exception("MROQ is not supported")

        for sync_entry in self.pci_sync_db:
            if sync_entry['flow'] == reset_sync:
                if self._pci_sync_for_fw_update_start & sync_entry['mask']:
                    break
        else:
            logger.debug("Requested reset sync '{0}' is NOT supported".format(reset_sync))
            return False
        logger.debug("Requested reset sync '{0}' is supported".format(reset_sync))
        return True

    def get_default_sync(self):
        if self.mroq_is_supported() is False:
            raise Exception("MROQ is not supported")

        reset_sync = CmdRegMroq.LEGACY_FLOW
        for field in CmdRegMroq.pci_sync_db:
            if field["mask"] & self._pci_sync_for_fw_update_start:
                reset_sync = field["flow"]
                break

        return reset_sync
