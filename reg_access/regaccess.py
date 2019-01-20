
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
except Exception as exp:
    raise RegAccException("Failed to load shared library rreg_access.so/libreg_access-1.dll: %s" % exp)

if REG_ACCESS:

    class ownershipEnum:
        REG_ACCESS_OWNERSHIP_TAKEN_SUCCESSFULLY = 0
        REG_ACCESS_FAILED_TO_AQUIRE_OWNERSHIP   = 1
        REG_ACCESS_NO_OWNERSHIP_REQUIRED        = 2

    class PCNR_ST(Structure):
        _fields_ = [
            ("tuning_override",c_uint8),
            ("local_port",c_uint8)
        ]


    class MCAM_REG_ST(Structure):
        _fields_ = [("access_reg_group", c_uint8),
                     ("feature_group", c_uint8),
                     ("mng_access_reg_cap_mask", c_uint8 * 16),
                     ("mng_feature_cap_mask", c_uint8 * 16)]


    class MTRC_CAP_REG_ST(Structure):
        _fields_ = [("num_string_db", c_uint8),
                    ("trc_ver", c_uint8),
                    ("trace_to_memory", c_uint8),
                    ("trace_owner", c_uint8),
                    ("num_string_trace", c_uint8),
                    ("first_string_trace", c_uint8),
                    ("log_max_trace_buffer_size", c_uint8),
                    ("reg_access_hca_string_db_parameters", c_uint8 * 64)]


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
        def __init__(self, dev=None, pci_device=None):
            self._mstDev = dev
            if pci_device is not None:
                self._mstDev = mtcr.MstDevice(pci_device)
            self._err2str = REG_ACCESS.reg_access_err2str
            self._err2str.restype = c_char_p
            self._sendMFRL = REG_ACCESS.reg_access_mfrl
            self._mgir = REG_ACCESS.reg_access_mgir
            self._reg_access_pcnr = REG_ACCESS.reg_access_pcnr
            self._reg_access_mcam = REG_ACCESS.reg_access_mcam
            self._reg_access_mtrc_cap = REG_ACCESS.reg_access_mtrc_cap

        ##########################
        def close(self):
            self._mstDev = None

        ##########################
        def __del__(self):
            if self._mstDev:
                self.close()

        def sendMtrcCapTakeOwnership(self):
            
            mcamRegP = pointer(MCAM_REG_ST())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                # in case of failure to get capability assume taking ownership is not required, same as in mlxtrace.
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED
            mtcrCapSupported = extractField(mcamRegP.contents.mng_access_reg_cap_mask[7], 0, 1)
            if mtcrCapSupported == 0:
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED

            maxIterations = 30
            mtrcaCapRegisterP = pointer(MTRC_CAP_REG_ST())

            iter = 0
            while iter < maxIterations:
                mtrcaCapRegisterP.contents.trace_owner = c_uint8(1)
                rc = self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), mtrcaCapRegisterP)
                if rc:
                    raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))
                mtrcaCapRegisterP.contents.trace_owner = c_uint8(0)
                mtrcaCapRegisterPquery = pointer(MTRC_CAP_REG_ST())
                rc = self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mtrcaCapRegisterPquery)
                if rc:
                    raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))
                if mtrcaCapRegisterPquery.contents.trace_owner == 1:
                    return 0
                iter += 1

        def sendPcnr(self, tuning_override, local_port): # Requirments : new FW version + burn with allow_pcnr

            pcnrRegisterP = pointer(PCNR_ST())
            pcnrRegisterP.contents.tuning_override = c_uint8(tuning_override)
            pcnrRegisterP.contents.local_port = c_uint8(local_port)

            rc = self._reg_access_pcnr(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), pcnrRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))


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

        def getSecureFWStatus(self):
            """ Returns True if the FW is secured, False otherwise.
            """
            mgirRegisterP = pointer(MGIR_ST())

            rc = self._mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            result = mgirRegisterP.contents.secure_fw
            result = True if result else False
            return result

else:
    raise RegAccException("Failed to load rreg_access.so/libreg_access.dll")


####################################################################################
