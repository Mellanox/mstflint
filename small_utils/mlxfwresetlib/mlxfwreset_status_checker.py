# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
#--

"""
* $Id           : fwreset_status_checker.py 2017-11-28
* $Authors      : Ahmad Soboh (ahmads@mellanox.com)
"""

######################################################################
# Description:  FirmwareResetStatusChecker
# OS Support :  Linux/Windows.
######################################################################


class FirmwareResetStatusChecker(object):

    FirmwareUptimeStatusInit = 0x0
    FirmwareUptimeStatusBeforeDone = 0x1
    FirmwareUptimeStatusAfterDone = 0x2
    FirmwareUptimeStatusError = 0x3

    FirmwareResetStatusDone = 0x0
    FirmwareResetStatusFailed = 0x1
    FirmwareResetStatusUnknown = 0x2

    def __init__(self, regAccessObj):
        self._RegAccessObj = regAccessObj
        self._UptimeBeforeReset = 0x0
        self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusInit
        self._UptimeAfterReset = 0x0
        self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusInit

    def UpdateUptimeBeforeReset(self):
        try:
            self._UptimeBeforeReset = self._RegAccessObj.getFWUptime()
            self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusBeforeDone
        except Exception as e:
            self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusError

    def UpdateUptimeAfterReset(self):
        try:
            self._UptimeAfterReset = self._RegAccessObj.getFWUptime()
            self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusAfterDone
        except Exception as e:
            self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusError

    def GetStatus(self):
        if self._UptimeBeforeStatus == FirmwareResetStatusChecker.FirmwareUptimeStatusBeforeDone and\
                        self._UptimeAfterStatus == FirmwareResetStatusChecker.FirmwareUptimeStatusAfterDone:
            if self._UptimeAfterReset < self._UptimeBeforeReset:
                return FirmwareResetStatusChecker.FirmwareResetStatusDone
            else:
                if self._UptimeBeforeReset > 5: #5 seconds
                    return FirmwareResetStatusChecker.FirmwareResetStatusFailed
                else:
                    return FirmwareResetStatusChecker.FirmwareResetStatusUnknown
        return FirmwareResetStatusChecker.FirmwareResetStatusUnknown
