
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

    class MFRL_ST(Structure):
        _fields_ = [("reset_level", c_uint8)]


    class MGIR_ST(Structure):
        _fields_ = [("device_id", c_uint16),
                    ("device_hw_revision", c_uint16),
                    ("pvs", c_uint8),
                    ("hw_dev_id", c_uint16),
                    ("manufacturing_base_mac_47_32", c_uint16),
                    ("manufacturing_base_mac_31_0", c_uint32),
                    ("uptime", c_uint32),
                    ("sub_minor", c_uint8),
                    ("minor", c_uint8),
                    ("major", c_uint8),
                    ("secure_fw", c_uint8),
                    ("signed_fw", c_uint8),
                    ("debug_fw", c_uint8),
                    ("dev_fw", c_uint8),
                    ("build_id", c_uint32),
                    ("year", c_uint16),
                    ("day", c_uint8),
                    ("month", c_uint8),
                    ("hour", c_uint16),
                    ("psid1", c_uint32),
                    ("psid2", c_uint32),
                    ("psid3", c_uint32),
                    ("psid4", c_uint32),
                    ("ini_file_version", c_uint32),
                    ("extended_major", c_uint32),
                    ("extended_minor", c_uint32),
                    ("extended_sub_minor", c_uint32),
                    ("subminor", c_uint8),
                    ("minor", c_uint8),
                    ("major", c_uint8),
                    ("rom3_type", c_uint8),
                    ("rom3_arch", c_uint8),
                    ("rom2_type", c_uint8),
                    ("rom2_arch", c_uint8),
                    ("rom1_type", c_uint8),
                    ("rom1_arch", c_uint8),
                    ("rom0_type", c_uint8),
                    ("rom0_arch", c_uint8),
                    ("rom0_version", c_uint32),
                    ("rom1_version", c_uint32),
                    ("rom2_version", c_uint32),
                    ("rom3_version", c_uint32)]

    class RegAccess:

        ##########################
        def __init__(self, dev):
            self._mstDev = dev
            self._err2str = REG_ACCESS.reg_access_err2str
            self._err2str.restype = c_char_p
            self._sendMFRL = REG_ACCESS.reg_access_mfrl
            self._mgir = REG_ACCESS.reg_access_mgir

        ##########################
        def close(self):
            self._mstDev = None

        ##########################
        def __del__(self):
            if self._mstDev:
                self.close()

        ##########################
        def sendMFRL(self, resetLevel, method):

            
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

        ##########################
        def getFWUptime(self):

            mgirRegisterP = pointer(MGIR_ST())

            rc = self._mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            return mgirRegisterP.contents.uptime


        def getManufacturingBaseMac(self):

            mgirRegisterP = pointer(MGIR_ST())

            rc = self._mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)

            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))


            lsp = mgirRegisterP.contents.manufacturing_base_mac_31_0
            msp = mgirRegisterP.contents.manufacturing_base_mac_47_32

            return msp*(2**32)+lsp


else:
    raise RegAccException("Failed to load rreg_access.so/libreg_access.dll")

####################################################################################
if __name__ == "__main__":
    # mstdev = mtcr.MstDevice("/dev/mst/mt4119_pciconf1")
    # regAc = RegAccess(mstdev)
    #
    # reset_level = regAc.sendMFRL(0, REG_ACCESS_METHOD_GET)
    # print "reset level is 0x{0:x}".format(reset_level)
    #
    # uptime = regAc.getFWUptime()
    # print "uptime is {0}".format(uptime)
    #
    # manufacturing_base_mac = regAc.getManufacturingBaseMac()
    # print 'manufacturing_base_mac : 0x{0:x}'.format(manufacturing_base_mac)

    pci_devices = ['0e:00.1', '08:00.1', '0e:00.0', '08:00.0']

    pci_devices = ['81:00.0', '02:00.0', '82:00.0']
    for pci_device in pci_devices:

        print "pci device {0}".format(pci_device)
        mstdev = mtcr.MstDevice(pci_device)
        regAc = RegAccess(mstdev)

        reset_level = regAc.sendMFRL(0, REG_ACCESS_METHOD_GET)
        print "reset level is 0x{0:x}".format(reset_level)

        uptime = regAc.getFWUptime()
        print "uptime is {0}".format(uptime)

        manufacturing_base_mac = regAc.getManufacturingBaseMac()
        print 'manufacturing_base_mac : 0x{0:x}'.format(manufacturing_base_mac)




