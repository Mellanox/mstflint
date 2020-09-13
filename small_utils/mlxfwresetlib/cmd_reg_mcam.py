# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
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

import sys
try:
    from regaccess import RegAccException
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)

class CmdRegMcam():

    def __init__(self, reg_access):

        self._reg_access = reg_access


    def is_reset_by_fw_driver_sync_supported(self):
        """
        Read MCAM and check if the feature "reset by fw-driver sync" is supported
        """
        try:
            mcam_get_result = self._reg_access.getMCAM()
        except RegAccException as e:
            pci_sync_for_fw_update_sup = 0
        else:
            # print(mcam_get_result)
            pci_sync_for_fw_update_sup = mcam_get_result["mng_feature_cap_mask"][19]
        return True if pci_sync_for_fw_update_sup == 1 else False

    def reset_sync_query_text(self):
        result = ""
        result += "Reset-sync (relevant only for reset-level 3):\n"
        result += "{0}: {1:<62}-{2:<14}{3}\n".format(0, "Tool is the owner", "Supported", "(default)")

        is_supported = self.is_reset_by_fw_driver_sync_supported()
        supported_text = "Supported" if is_supported is True else "Not supported"
        result += "{0}: {1:<62}-{2:<14}{3}\n".format(1, "Driver is the owner", supported_text, "")

        return result