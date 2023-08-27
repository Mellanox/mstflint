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


class CmdRegMrsi():

    ECOS_VALS = [
        {0, 'Reset/Boot-ROM'},
        {1, 'BL2'},
        {2, 'BL31'},
        {3, 'UEFI'},
        {4, 'OS starting'},
        {5, 'OS is running'},
        {6, 'Low - Power standby'},
        {7, 'Firmware update in progress'},
        {8, 'OS Crash Dump in progress'},
        {9, 'OS Crash Dump is complete'},
        {10, 'FW Fault Crash Dump in progress'},
        {11, 'FW Fault Crash Dump is complete'}
    ]

    def __init__(self, reg_access):
        self._reg_access = reg_access
        self._mrsi_get_result = None

    def get_mrsi(self):
        if self._mrsi_get_result is None:
            self._mrsi_get_result = self._reg_access.getMRSI()
        return self._mrsi_get_result  # returns {"reset_reason":value of reset_reason, "crts":value of crts, "ecos":value of ecos}

    def is_warm_reset(self):
        mrsi_get_result = self.get_mrsi()
        if mrsi_get_result["reset_reason"] == 1:
            return True
        return False

    def get_crts(self):
        mrsi_get_result = self.get_mrsi()
        return mrsi_get_result["crts"]

    def get_ecos(self):
        mrsi_get_result = self.get_mrsi()
        return mrsi_get_result["ecos"]

    def query_text(self, is_bluefield):
        try:
            warm_reset = self.is_warm_reset()
            timestamp = self.get_crts()
            reset_reason = "Warm reset" if warm_reset else "Cold reset"
        except Exception as e:
            reset_reason = "Unknown. Please check driver is up."
            timestamp = "Unknown. Please check driver is up."

        result = ""
        result += "{0}: {1:<51}{2:<14}\n".format("Reset-reason", "", reset_reason)
        result += "{0}: {1:<7}{2:<14}\n".format("Timestamp (number of clock cycles) since last cold reset", "", timestamp)

        # if is_bluefield:  # will be uncommented when FW will implement their support.
        #     ecos_result = self.ecos_query_text()
        #     result += ecos_result

        return result

    def ecos_query_text(self):
        state = self.get_ecos()
        description = CmdRegMrsi.ecos_vals[state]

        result = ""
        result = "Embedded CPU OS state:\n"
        result += "{0}: {1:<62}-{2:<14}{3}\n".format(state, description, "", "")
        return result
