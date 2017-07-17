
#--
#                 - Mellanox Confidential and Proprietary -
#
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
#
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

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

class RegAccException(Exception):
    pass

# Constants
REG_ACCESS_METHOD_GET = 1
REG_ACCESS_METHOD_SET = 2

##########################
REG_ACCESS = None
try:
    from ctypes import *
    if platform.system() == "Windows" or os.name == "nt":
        REG_ACCESS = CDLL("libreg_access-1.dll")
    else:
        try:
            REG_ACCESS = CDLL("rreg_access.so")
        except:
            REG_ACCESS = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "rreg_access.so"))
except Exception, exp:
    raise RegAccException("Failed to load shared library rreg_access.so/libreg_access-1.dll: %s" % exp)

if REG_ACCESS:
    class RegAccess:
        ##########################
        def __init__(self, dev):
            self._mstDev = dev
            self._err2str = REG_ACCESS.reg_access_err2str
            self._err2str.restype = c_char_p
            self._sendMFRL = REG_ACCESS.reg_access_mfrl

        ##########################
        def close(self):
            self._mstDev = None

        ##########################
        def __del__(self):
            if self._mstDev:
                self.close()
        
        ##########################
        def sendMFRL(self, resetLevel, method):
            class MFRL_ST(Structure):
                _fields_ = [("reset_level", c_uint8)]
            
            mfrlRegisterP = pointer(MFRL_ST())
            
            if method == REG_ACCESS_METHOD_SET:
                mfrlRegisterP.contents.reset_level = c_uint8(resetLevel)
            
            c_method = c_uint(method)
            rc = self._sendMFRL(self._mstDev.mf, c_method, mfrlRegisterP)
            # FW bug first mfrl register might fail
            if rc:
                rc = self._sendMFRL(self._mstDev.mf, c_method, mfrlRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))
            
            if method == REG_ACCESS_METHOD_GET:
                return mfrlRegisterP.contents.reset_level
else:
    raise RegAccException("Failed to load rreg_access.so/libreg_access.dll")

####################################################################################
if __name__ == "__main__":
    mstdev = mtcr.MstDevice("/dev/mst/mt4113_pciconf0")
    regAc = RegAcc(mstdev)
    print regAc.sendMFRL(0, REG_ACCESS_METHOD_GET)
