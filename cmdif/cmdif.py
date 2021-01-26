
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

from __future__ import print_function
import os
import sys
import platform
import ctypes
import mtcr

def ones(n):
    return (1 << n) - 1

def extractField(val, start, size):
    return (val & (ones(size)<<start)) >> start

def insertField(val1, start1, val2, start2, size):
    return val1 & ~(ones(size)<<start1) | (extractField(val2, start2, size) << start1)

class CmdIfException(Exception):
    pass

##########################
CMDIF = None
try:
    from ctypes import *
    if platform.system() == "Windows" or os.name == "nt":
        CMDIF = CDLL("libcmdif-1.dll")
    else:
        try:
            CMDIF = CDLL("ccmdif.so")
        except:
            CMDIF = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "ccmdif.so"))
except Exception as exp:
    raise CmdIfException("Failed to load shared library ccmdif.so/libcmdif-1.dll: %s" % exp)

if CMDIF:
    class CmdIf:
        ##########################
        def __init__(self, dev):
            self.mstDev = dev
            self.getLastErrFunc = CMDIF.gcif_get_last_err
            self.getLastErrFunc.restype = c_char_p
            self.setItraceFunc = CMDIF.gcif_set_itrace
            self.getFwInfoFunc = CMDIF.gcif_get_fw_info
            self.multiHostSyncFunc = CMDIF.gcif_mh_sync
            self.multiHostSyncStatusFunc = CMDIF.gcif_mh_sync_status
            self.getIcmdQueryCap = CMDIF.get_icmd_query_cap

        def errStrFunc(self, rc):
            errStrFunc_ = CMDIF.gcif_err_str
            errStrFunc_.restype = c_char_p
            return errStrFunc_(rc).decode("utf-8")

        ##########################
        def close(self):
            self.mstDev = None

        ##########################
        def __del__(self):
            if self.mstDev:
                self.close()

        ##########################
        def sendCmd(self, opcode, data, skipWrite):
            self.mstDev.icmdSendCmd(opcode, data, skipWrite)
        
        ##########################
        def setItrace(self, mask, level, log_delay=0):
            class ITRACE_ST(Structure):
                _fields_ = [("unit_mask", c_uint32), ("log_level", c_uint8), ("log_delay", c_uint16)]
                
            setItraceStruct = pointer(ITRACE_ST(mask, level, log_delay))
            rc = self.setItraceFunc(self.mstDev.mf, setItraceStruct)
            if rc:
                raise CmdIfException("Failed to set itrace mask: %s (%d)" % (self.errStrFunc(rc), rc))
            
        ##########################
        def getFwInfo(self):
            class FW_INFO_ST(Structure):
                _fields_ = [("MAJOR", c_uint16), ("SUBMINOR", c_uint16),
                            ("MINOR", c_uint16), ("Hour", c_uint8),
                            ("Minutes", c_uint8), ("Seconds", c_uint8),
                            ("Day", c_uint8), ("Month", c_uint8),
                            ("Year", c_uint16), ("hash_signature", c_uint16),
                            ("psid", c_char_p * 17)]
            getFwInfoStruct = FW_INFO_ST()
            getFwInfoStructPtr = pointer(getFwInfoStruct)
            rc = self.getFwInfoFunc(self.mstDev.mf, getFwInfoStructPtr)
            if rc:
                raise CmdIfException("Failed to get FW INFO: %s, device maybe in livefish mode." % (self.errStrFunc(rc)))
            return getFwInfoStruct

        ##########################
        class MH_SYNC_ST(Structure):
            _fields_ = [("input_state",                 c_uint8),
                        ("input_sync_type",             c_uint8),
                        ("input_ignore_inactive_host",  c_uint8),
                        ("fsm_state",                   c_uint8),
                        ("fsm_sync_type",               c_uint8),
                        ("fsm_ignore_inactive_host",    c_uint8),
                        ("fsm_host_ready",              c_uint8),
                        ("fsm_start_uptime",            c_uint32)]

        ##########################
        def multiHostSync(self, state, syncType, ignoreInactiveHost = 0x0):
            multiHostSyncOutStruct = self.MH_SYNC_ST()
            multiHostSyncOutStructPtr = pointer(multiHostSyncOutStruct)
            multiHostSyncOutStructPtr.contents.input_ignore_inactive_host = c_uint8(ignoreInactiveHost)
            multiHostSyncOutStructPtr.contents.input_state = c_uint8(state)
            multiHostSyncOutStructPtr.contents.input_sync_type = c_uint8(syncType)
            rc = self.multiHostSyncFunc(self.mstDev.mf, multiHostSyncOutStructPtr)
            if rc:
                raise CmdIfException("Failed to run multi host icmd: %s (%d)" % (self.errStrFunc(rc), rc))
            return multiHostSyncOutStruct

        ##########################
        def multiHostSyncStatus(self):
            multiHostSyncOutStruct = self.MH_SYNC_ST()
            multiHostSyncOutStructPtr = pointer(multiHostSyncOutStruct)
            rc = self.multiHostSyncStatusFunc(self.mstDev.mf, multiHostSyncOutStructPtr)
            if rc:
                raise CmdIfException("Failed to run multi host icmd: %s (%d)" % (self.errStrFunc(rc), rc))
            return multiHostSyncOutStruct

        ##########################
        class QUERY_CAP_ST(Structure):
            _fields_ = [("golden_tlv_version",                     c_uint8),
                        ("cwcam_reg",                              c_uint8),
                        ("capability_groups",                      c_uint8),
                        ("virtual_link_down",                      c_uint8),
                        ("icmd_exmb",                              c_uint8),
                        ("capi",                                   c_uint8),
                        ("qcam_reg",                               c_uint8),
                        ("mcam_reg",                               c_uint8),
                        ("pcam_reg",                               c_uint8),
                        ("mh_sync",                                c_uint8),
                        ("allow_icmd_access_reg_on_all_registers", c_uint8),
                        ("fw_info_psid",                           c_uint8),
                        ("nv_access",                              c_uint8),
                        ("wol_p",                                  c_uint8),
                        ("wol_u",                                  c_uint8),
                        ("wol_m",                                  c_uint8),
                        ("wol_b",                                  c_uint8),
                        ("wol_a",                                  c_uint8),
                        ("wol_g",                                  c_uint8),
                        ("wol_s",                                  c_uint8),
                        ("rol_g",                                  c_uint8),
                        ("rol_s",                                  c_uint8),
                        ("fpga",                                   c_uint8),
                        ("num_of_diagnostic_counters",             c_uint16)]

        ##########################
        def isMultiHostSyncSupported(self):
            queryCapStruct = self.QUERY_CAP_ST()
            queryCapStructPtr = pointer(queryCapStruct)
            rc = self.getIcmdQueryCap(self.mstDev.mf, queryCapStructPtr)
            if rc:
                raise CmdIfException("Failed to run query cap icmd: %s (%d)" % (self.errStrFunc(rc), rc))
            return (queryCapStruct.mh_sync == 0x1)

else:
    raise CmdIfException("Failed to load cmdif.so/cmdif.dll")

####################################################################################
if __name__ == "__main__":
    mstdev = mtcr.MstDevice("/dev/mst/mt4113_pciconf0")
    cmdif = CmdIf(mstdev)
    
    cmdif.setItrace(0x1001, 8)
