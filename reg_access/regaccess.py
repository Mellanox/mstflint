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


    class RES_DUMP_ST(Structure):
        _fields_ = [
            ("segment_type",c_uint16),
            ("seq_num",c_uint8),
            ("vhca_id_valid",c_uint8),
            ("inline_dump",c_uint8),
            ("more_dump",c_uint8),
            ("vhca_id",c_uint16),
            ("index_1",c_uint32),
            ("index_2",c_uint32),
            ("num_of_obj_2",c_uint16),
            ("num_of_obj_1",c_uint16),
            ("device_opaque",c_uint64),
            ("mkey",c_uint32),
            ("size",c_uint32),
            ("address",c_uint64),
            ("inline_data",c_uint32 * 52)
        ]


    class DIAGNOSTIC_CNTR_ST(Structure):
        _fields_ = [
            ("counter_id",c_uint16),
            ("sync",c_uint8)
        ]


    class DIAGNOSTIC_CNTR_ST_ARR(Array):
        _type_ = DIAGNOSTIC_CNTR_ST
        _length_ = 10


    class DEBUG_CUP_ST(Structure):
        _fields_ = [
            ("log_max_samples",c_uint8),
            ("resource_dump",c_uint8),
            ("log_cr_dump_to_mem_size",c_uint8),
            ("core_dump_qp",c_uint8),
            ("core_dump_general",c_uint8),
            ("log_min_sample_period",c_uint8),
            ("diag_counter_tracer_dump",c_uint8),
            ("health_mon_rx_activity",c_uint8),
            ("repetitive",c_uint8),
            ("single",c_uint8),
            #("diagnostic_counter",POINTER(DIAGNOSTIC_CNTR_ST))
            ("diagnostic_counter",POINTER(DIAGNOSTIC_CNTR_ST_ARR))
        ]


    class PCNR_ST(Structure):
        _fields_ = [
            ("tuning_override",c_uint8),
            ("local_port",c_uint8)
        ]

    class MFRL_ST(Structure):
        _fields_ = [
            ("reset_level", c_uint8),
            ("reset_type", c_uint8),
            ("rst_type_sel", c_uint8),
            ("pci_sync_for_fw_update_resp", c_uint8),
            ("pci_sync_for_fw_update_start", c_uint8)
        ]

    class MPCIR_ST(Structure):
        _fields_ = [
            ("all", c_uint8),
            ("ports", c_uint8),
            ("ports_stat", c_uint8)
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


    class MGIR_ST(Structure):
        _fields_ = [("device_id", c_uint16),
                    ("device_hw_revision", c_uint16),
                    ("pvs", c_uint8),
                    ("num_ports",c_uint8),
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
                    ("string_tlv", c_uint8),
                    ("build_id", c_uint32),
                    ("year", c_uint16),
                    ("day", c_uint8),
                    ("month", c_uint8),
                    ("hour", c_uint16),
                    ("psid", c_uint8 * 16),
                    ("ini_file_version", c_uint32),
                    ("extended_major", c_uint32),
                    ("extended_minor", c_uint32),
                    ("extended_sub_minor", c_uint32),
                    ("isfu_major", c_uint16),
                    ("fw_subminor", c_uint8),
                    ("fw_minor", c_uint8),
                    ("fw_major", c_uint8),
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
                    ("rom3_version", c_uint32),
                    ("dev_branch_tag", c_uint8 * 28)]

    class MDDQ_SLOT_INFO(Structure):
        _fields_ = [("active", c_uint8),
                    ("ready", c_uint8),
                    ("sr_valid", c_uint8),
                    ("provisioned", c_uint8),
                    ("minor_ini_file_version", c_uint16),
                    ("major_ini_file_version", c_uint16),
                    ("card_type", c_uint8)]

    class MDDQ_DEVICE_INFO(Structure):
        _fields_ = [("device_index", c_uint8),
                    ("flash_id", c_uint8),
                    ("thermal_sd", c_uint8),
                    ("flash_owner", c_uint8),
                    ("uses_flash", c_uint8),
                    ("device_type", c_uint16),
                    ("fw_major", c_uint16),
                    ("fw_sub_minor", c_uint16),
                    ("fw_minor", c_uint16)]

    class MDDQ_DATA_UN(Union):
        _fields_ = [("mddq_slot_info", MDDQ_SLOT_INFO),
                    ("mddq_device_info", MDDQ_DEVICE_INFO)]

    class MDDQ_ST(Structure):
        _fields_ = [("slot_index", c_uint8),
                    ("query_type", c_uint8),
                    ("sie", c_uint8),
                    ("request_message_sequence", c_uint8),
                    ("response_message_sequence", c_uint8),
                    ("query_index", c_uint8),
                    ("frst", c_uint8),
                    ("mid", c_uint8),
                    ("lst", c_uint8),
                    ("data", MDDQ_DATA_UN)]

    class RegAccess:
        GET = REG_ACCESS_METHOD_GET
        SET = REG_ACCESS_METHOD_SET

        ##########################
        def __init__(self, dev=None, pci_device=None):
            self._mstDev = dev
            if pci_device is not None:
                self._mstDev = mtcr.MstDevice(pci_device)
            self._reg_access_mcam = REG_ACCESS.reg_access_mcam
            self._reg_access_mtrc_cap = REG_ACCESS.reg_access_mtrc_cap
            self._reg_access_mgir = REG_ACCESS.reg_access_mgir
            self._reg_access_mfrl = REG_ACCESS.reg_access_mfrl
            self._reg_access_pcnr = REG_ACCESS.reg_access_pcnr
            self._reg_access_mpcir = REG_ACCESS.reg_access_mpcir
            self._reg_access_res_dump = REG_ACCESS.reg_access_res_dump
            self._reg_access_debug_cap = REG_ACCESS.reg_access_debug_cap
            self._reg_access_mddq = REG_ACCESS.reg_access_mddq

        def _err2str(self, rc):
            err2str = REG_ACCESS.reg_access_err2str
            err2str.restype = c_char_p
            return err2str(rc).decode("utf-8")

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


        def sendResDump(self, segment_type, seq_num, inline_mode, more_dump, vhca_id, vhca_id_valid, index1, index2, num_of_obj2, num_of_obj1, device_opaque, mkey, size, address):
            resDumpRegP = pointer(RES_DUMP_ST())
            resDumpRegP.contents.segment_type = c_uint16(segment_type)
            resDumpRegP.contents.seq_num = c_uint8(seq_num)
            resDumpRegP.contents.inline_dump = c_uint8(inline_mode)
            resDumpRegP.contents.more_dump = c_uint8(more_dump)
            resDumpRegP.contents.vhca_id = c_uint16(vhca_id)
            resDumpRegP.contents.vhca_id_valid = c_uint8(vhca_id_valid)
            resDumpRegP.contents.index_1 = c_uint32(index1)
            resDumpRegP.contents.index_2 = c_uint32(index2)
            resDumpRegP.contents.num_of_obj_2 = c_uint16(num_of_obj2)
            resDumpRegP.contents.num_of_obj_1 = c_uint16(num_of_obj1)
            resDumpRegP.contents.device_opaque = c_uint64(device_opaque)
            resDumpRegP.contents.mkey = c_uint32(mkey)
            resDumpRegP.contents.size = c_uint32(size)
            resDumpRegP.contents.address = c_uint64(address)
            rc = self._reg_access_res_dump(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), resDumpRegP)
            if rc:
                raise RegAccException("Failed to send Register RESOURCE DUMP with rc: %d" % rc)
            #return (resDumpRegP.contents.segment_type, resDumpRegP.contents.seq_num, resDumpRegP.contents.inline_data[0])
            return ({"segment_type": resDumpRegP.contents.segment_type,
                     "seq_num": resDumpRegP.contents.seq_num,
                     "inline_dump": resDumpRegP.contents.inline_dump,
                     "more_dump": resDumpRegP.contents.more_dump,
                     "vhca_id": resDumpRegP.contents.vhca_id,
                     "vhca_id_valid": resDumpRegP.contents.vhca_id_valid,
                     "index_1": resDumpRegP.contents.index_1,
                     "index_2": resDumpRegP.contents.index_2,
                     "num_of_obj_2": resDumpRegP.contents.num_of_obj_2,
                     "num_of_obj_1": resDumpRegP.contents.num_of_obj_1,
                     "device_opaque": resDumpRegP.contents.device_opaque,
                     "mkey": resDumpRegP.contents.mkey,
                     "size": resDumpRegP.contents.size,
                     "address": resDumpRegP.contents.address,
                     "inline_data": resDumpRegP.contents.inline_data})


        def sendDebugCap(self):
            debugCapRegP = pointer(DEBUG_CUP_ST())
            debugCapRegP.contents.log_max_samples = c_uint8(0)
            debugCapRegP.contents.resource_dump = c_uint8(0)
            debugCapRegP.contents.log_cr_dump_to_mem_size = c_uint8(0)
            debugCapRegP.contents.core_dump_qp = c_uint8(0)
            debugCapRegP.contents.core_dump_general = c_uint8(0)
            debugCapRegP.contents.log_min_sample_period = c_uint8(0)
            debugCapRegP.contents.diag_counter_tracer_dump = c_uint8(0)
            debugCapRegP.contents.health_mon_rx_activity = c_uint8(0)
            debugCapRegP.contents.repetitive = c_uint8(0)
            debugCapRegP.contents.single = c_uint8(0)
            tmp = pointer(DIAGNOSTIC_CNTR_ST())
            tmp.contents.counter_id = c_uint16(0)
            tmp.contents.sync = c_uint8(0)
            debugCapRegP.contents.diagnostic_counter = pointer(DIAGNOSTIC_CNTR_ST_ARR())
            rc = self._reg_access_debug_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), debugCapRegP)
            if rc:
                raise RegAccException("Failed to send Register DEBUG CAP with rc: %d" % rc)
            return debugCapRegP.contents.resource_dump


        def sendPcnr(self, tuning_override, local_port): # Requirments : new FW version + burn with allow_pcnr

            pcnrRegisterP = pointer(PCNR_ST())
            pcnrRegisterP.contents.tuning_override = c_uint8(tuning_override)
            pcnrRegisterP.contents.local_port = c_uint8(local_port)

            rc = self._reg_access_pcnr(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), pcnrRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))


        def sendMpcir(self, command):
            
            # 2 operations (both executed with 'set' register):
            #   (1) Start perperations for FW upgrade
            #   (2) Query operation #1 (idle/done)
            CMD_START = 1
            CMD_GET_STATUS = 3

            if command == "start":
                command = CMD_START
            elif command == "status":
                command = CMD_GET_STATUS
            else:
                raise ValueError("command {0} is illegal".format(command))

            mpcirRegisterP = pointer(MPCIR_ST(ports=command))
            rc = self._reg_access_mpcir(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mpcirRegisterP)
            if rc != 0:
                raise RegAccException("Failed to send Command Register MPCIR")
            if command == CMD_GET_STATUS:
                return mpcirRegisterP.contents.ports_stat


        ##########################
        def sendMFRL(self, method, resetLevel=None, reset_type=None, reset_sync=None):

            mfrlRegisterP = pointer(MFRL_ST())
            
            if method == REG_ACCESS_METHOD_SET:
                if resetLevel is None or reset_type is None or reset_sync is None:
                    raise RegAccException("Failed to sendMFRL (reset level/type/sync is None for SET command)")
                mfrlRegisterP.contents.reset_level = c_uint8(resetLevel)
                mfrlRegisterP.contents.rst_type_sel = c_uint8(reset_type)
                mfrlRegisterP.contents.pci_sync_for_fw_update_start = c_uint8(reset_sync)

            c_method = c_uint(method)
            rc = self._reg_access_mfrl(self._mstDev.mf, c_method, mfrlRegisterP)
            # FW bug first mfrl register might fail
            if rc:
                rc = self._reg_access_mfrl(self._mstDev.mf, c_method, mfrlRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            if method == REG_ACCESS_METHOD_GET:
                return mfrlRegisterP.contents.reset_level, mfrlRegisterP.contents.reset_type

        ##########################
        def getMCAM(self):

            def to_bits(list_of_bytes):
                list_of_bits = []
                for byte_ in list_of_bytes:
                    # print("{0:08b}".format(byte_))
                    for ii in range(7,-1,-1):
                        val = 0 if byte_ & (1<<ii) == 0 else 1
                        list_of_bits.append(val)
                return list_of_bits[::-1]

            mcamRegP = pointer(MCAM_REG_ST())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)            
            if rc:
                raise RegAccException("Failed to send Register MCAM (rc: {0})".format(rc))
            
            return {
                "access_reg_group" :mcamRegP.contents.access_reg_group,
                "feature_group":mcamRegP.contents.feature_group,
                "mng_access_reg_cap_mask": to_bits(mcamRegP.contents.mng_access_reg_cap_mask),
                "mng_feature_cap_mask": to_bits(mcamRegP.contents.mng_feature_cap_mask)
            }


        ##########################
        def getFwVersion(self):

            mgirRegisterP = pointer(MGIR_ST())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                info_ver = ""
            else:
                # get dev branch tag
                info_ver = "".join(chr(val) for val in mgirRegisterP.contents.dev_branch_tag if val != 0)

                # if dev branch is empty, try to get the master version
                if info_ver == "":
                    if mgirRegisterP.contents.fw_major != 0:
                        info_ver = "{0}.{1}.{2}".format(mgirRegisterP.contents.fw_major,
                                                        mgirRegisterP.contents.fw_minor,
                                                        mgirRegisterP.contents.fw_subminor)
                    elif mgirRegisterP.contents.extended_major != 0:
                        info_ver = "{0}.{1}.{2}".format(mgirRegisterP.contents.extended_major,
                                                        mgirRegisterP.contents.extended_minor,
                                                        mgirRegisterP.contents.extended_sub_minor)

            return info_ver

        def getFWUptime(self):

            mgirRegisterP = pointer(MGIR_ST())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            return mgirRegisterP.contents.uptime


        def getManufacturingBaseMac(self):

            mgirRegisterP = pointer(MGIR_ST())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)

            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))


            lsp = mgirRegisterP.contents.manufacturing_base_mac_31_0
            msp = mgirRegisterP.contents.manufacturing_base_mac_47_32

            return msp*(2**32)+lsp

        def getSecureFWStatus(self):
            """ Returns True if the FW is secured, False otherwise.
            """
            mgirRegisterP = pointer(MGIR_ST())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            result = mgirRegisterP.contents.secure_fw
            result = True if result else False
            return result

        def sendMddq(self, query_type, request_message_sequence, slot_index, query_index=0):
            mddqRegisterP = pointer(MDDQ_ST())
            mddqRegisterP.contents.query_type = c_uint8(query_type)
            mddqRegisterP.contents.slot_index = c_uint8(slot_index)
            mddqRegisterP.contents.request_message_sequence = c_uint8(request_message_sequence)
            mddqRegisterP.contents.query_index = c_uint8(query_index)
            rc = self._reg_access_mddq(self._mstDev.mf, REG_ACCESS_METHOD_GET, mddqRegisterP)
            if rc:
                raise RegAccException("Failed to send Register: %s (%d)" % (self._err2str(rc), rc))

            data = {}
            if query_type == 1:
                data.update({
                    "active": mddqRegisterP.contents.data.mddq_slot_info.active,
                    "ready": mddqRegisterP.contents.data.mddq_slot_info.ready,
                    "sr_valid": mddqRegisterP.contents.data.mddq_slot_info.sr_valid,
                    "provisioned": mddqRegisterP.contents.data.mddq_slot_info.provisioned,
                    "minor_ini_file_version": mddqRegisterP.contents.data.mddq_slot_info.minor_ini_file_version,
                    "major_ini_file_version": mddqRegisterP.contents.data.mddq_slot_info.major_ini_file_version
                })
            elif query_type == 2:
                data.update({
                    "device_index": mddqRegisterP.contents.data.mddq_device_info.device_index,
                    "flash_id": mddqRegisterP.contents.data.mddq_device_info.flash_id,
                    "flash_owner": mddqRegisterP.contents.data.mddq_device_info.flash_owner,
                    "uses_flash": mddqRegisterP.contents.data.mddq_device_info.uses_flash,
                    "device_type": mddqRegisterP.contents.data.mddq_device_info.device_type,
                    "fw_major": mddqRegisterP.contents.data.mddq_device_info.fw_major,
                    "fw_sub_minor": mddqRegisterP.contents.data.mddq_device_info.fw_sub_minor,
                    "fw_minor": mddqRegisterP.contents.data.mddq_device_info.fw_minor
                })
            return ({"slot_index": mddqRegisterP.contents.slot_index,
                     "query_type": mddqRegisterP.contents.query_type,
                     "request_message_sequence": mddqRegisterP.contents.request_message_sequence,
                     "response_message_sequence": mddqRegisterP.contents.response_message_sequence,
                     "frst": mddqRegisterP.contents.frst,
                     "mid": mddqRegisterP.contents.mid,
                     "lst": mddqRegisterP.contents.lst},
                     data)

else:
    raise RegAccException("Failed to load rreg_access.so/libreg_access.dll")


####################################################################################
