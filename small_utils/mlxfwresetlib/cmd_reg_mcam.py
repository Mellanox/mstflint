# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
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
# --

import sys
try:
    from regaccess import RegAccException, extractField
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)


class CmdRegMcam():

    def __init__(self, reg_access):

        self._reg_access = reg_access
        self._mcam_get_results = [None] * 3

    def get_mcam(self, access_reg_group=0):
        try:
            if self._mcam_get_results[access_reg_group] is None:
                self._mcam_get_results[access_reg_group] = self._reg_access.getMCAM(access_reg_group)
            return self._mcam_get_results[access_reg_group]
        except IndexError as ie:
            raise Exception("get_mcam() was called with invalid access_reg_group=%s\n" % str(access_reg_group))
        except Exception as e:
            raise e

    def is_pci_rescan_required_supported(self):
        """
        Read MCAM and check if the feature "PCI rescan required" is supported
        """
        try:
            mcam_get_result = self.get_mcam()
        except BaseException:
            pci_rescan_required_sup = 0
        else:
            # bit 45 is bit 13 in 2nd DWORD.
            # due to FW bug, MCAM mng_feature_cap_mask dwords are set in reversed order
            # so we actually access the 3rd DWORD (index 2)
            pci_rescan_required_sup = extractField(mcam_get_result["mng_feature_cap_mask"][3 - 1], 13, 1)
        return True if pci_rescan_required_sup == 1 else False

    def is_reset_by_fw_driver_sync_supported(self):
        """
        Read MCAM and check if the feature "reset by fw-driver sync" is supported
        """
        try:
            mcam_get_result = self.get_mcam()
        except RegAccException as e:
            pci_sync_for_fw_update_sup = 0
        else:
            # bit 19 in 1st DWORD.
            # due to FW bug, MCAM mng_feature_cap_mask dwords are set in reversed order
            # so we actually access the 4th DWORD (index 3)
            pci_sync_for_fw_update_sup = extractField(mcam_get_result["mng_feature_cap_mask"][3 - 0], 19, 1)
        return True if pci_sync_for_fw_update_sup == 1 else False

    def is_mrsi_supported(self):
        """
        send MCAM access_reg_group=2
        and then read mng_access_reg_cap_mask (bit 10 in 2nd DWORD) to see if MRSI is supported.
        """
        try:
            mcam_get_result = self.get_mcam(2)
        except RegAccException as e:
            mrsi_sup = 0
        else:
            # bit 42 is bit 10 in 2nd DWORD.
            # due to FW bug, MCAM mng_feature_cap_mask dwords are set in reversed order
            # so we actually access the 3rd DWORD (index 2)
            mrsi_sup = extractField(mcam_get_result["mng_access_reg_cap_mask"][3 - 1], 10, 1)
        return True if mrsi_sup == 1 else False

    def reset_sync_query_text(self, tool_owner_support):
        result = ""
        result += "Reset-sync (relevant only for reset-level 3):\n"
        result += "{0}: {1:<62}-{2:<14}{3}\n".format(0, "Tool is the owner", "Supported" if tool_owner_support else "Not supported", "(default)" if tool_owner_support else "")

        is_supported = self.is_reset_by_fw_driver_sync_supported()
        supported_text = "Supported" if is_supported is True else "Not supported"
        result += "{0}: {1:<62}-{2:<14}{3}\n".format(1, "Driver is the owner", supported_text, "" if tool_owner_support else "(default)")

        return result
