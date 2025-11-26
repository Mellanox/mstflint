# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --

from __future__ import print_function
import os
import sys
import platform
import ctypes
import mtcr
import struct
from ctypes import memset
from regaccess_hca_ext_structs import *
from regaccess_switch_ext_structs import *


def ones(n):
    return (1 << n) - 1


def extractField(val, start, size):
    return (val & (ones(size) << start)) >> start


def insertField(val1, start1, val2, start2, size):
    return val1 & ~(ones(size) << start1) | (extractField(val2, start2, size) << start1)


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
        try:
            REG_ACCESS = CDLL("libreg_access-1.dll")
        except BaseException:
            REG_ACCESS = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "libreg_access-1.dll"))
    else:
        try:
            REG_ACCESS = CDLL("rreg_access.so")
        except BaseException:
            REG_ACCESS = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "rreg_access.so"))
except Exception as exp:
    raise RegAccException("Failed to load shared library rreg_access.so/libreg_access-1.dll: %s" % exp)

if REG_ACCESS:

    class ownershipEnum:
        REG_ACCESS_OWNERSHIP_TAKEN_SUCCESSFULLY = 0
        REG_ACCESS_FAILED_TO_AQUIRE_OWNERSHIP = 1
        REG_ACCESS_NO_OWNERSHIP_REQUIRED = 2

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
            self._reg_access_mtrc_stdb_warpper = REG_ACCESS.reg_access_mtrc_stdb_wrapper
            self._reg_access_mgir = REG_ACCESS.reg_access_mgir
            self._reg_access_mfrl = REG_ACCESS.reg_access_mfrl
            self._reg_access_mroq = REG_ACCESS.reg_access_mroq
            self._reg_access_pcnr = REG_ACCESS.reg_access_pcnr
            self._reg_access_mpcir = REG_ACCESS.reg_access_mpcir
            self._reg_access_res_dump = REG_ACCESS.reg_access_res_dump
            self._reg_access_debug_cap = REG_ACCESS.reg_access_debug_cap
            self._reg_access_mddq = REG_ACCESS.reg_access_mddq
            self._reg_access_mdsr = REG_ACCESS.reg_access_mdsr
            self._reg_access_mteim = REG_ACCESS.reg_access_mteim
            self._reg_access_nic_dpa_eug = REG_ACCESS.reg_access_nic_dpa_eug
            self._reg_access_nic_cap_ext = REG_ACCESS.reg_access_nic_cap_ext
            self._reg_access_nic_dpa_perf_ctrl = REG_ACCESS.reg_access_nic_dpa_perf_ctrl
            self._reg_access_mrsr = REG_ACCESS.reg_access_mrsr
            self._reg_access_dtor = REG_ACCESS.reg_access_dtor
            self._reg_access_mrsi = REG_ACCESS.reg_access_mrsi
            self._reg_access_mpir = REG_ACCESS.reg_access_mpir
            self._reg_access_mpein = REG_ACCESS.reg_access_mpein

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

        def isCsTokenApplied(self):
            mdsrRegP = pointer(MDSR_REG_EXT())
            mdsrRegP.contents.type_of_token == 0  # index for CS token (changed on PRM 0.58)
            rc = self._reg_access_mdsr(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mdsrRegP)
            if rc:
                return False  # if mdsr not support (or other fail), assume no token

            return (mdsrRegP.contents.status == 2)  # session active - tokem is applied

        def sendMtrcCapTakeOwnership(self):

            mcamRegP = pointer(MCAM_REG_EXT())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                # in case of failure to get capability assume taking ownership is not required, same as in mlxtrace.
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED
            mtcrCapSupported = extractField(mcamRegP.contents.mng_access_reg_cap_mask[3 - 2], 0, 1)
            if mtcrCapSupported == 0:
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED

            mtrcaCapRegisterPquery = pointer(MTRC_CAP_REG_EXT())
            rc = self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mtrcaCapRegisterPquery)
            if rc:
                raise RegAccException("Failed to send Register MTRC (case 1): %s (%d)" % (self._err2str(rc), rc))
            if mtrcaCapRegisterPquery.contents.trace_owner == 1:
                return 0  # already have ownership from last run

            maxIterations = 30
            mtrcaCapRegisterP = pointer(MTRC_CAP_REG_EXT())

            iter = 0
            while iter < maxIterations:
                mtrcaCapRegisterP.contents.trace_owner = c_uint8(1)
                rc = self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), mtrcaCapRegisterP)
                if rc:
                    raise RegAccException("Failed to send Register MTRC (case 2): %s (%d)" % (self._err2str(rc), rc))
                mtrcaCapRegisterP.contents.trace_owner = c_uint8(0)
                mtrcaCapRegisterPquery = pointer(MTRC_CAP_REG_EXT())
                rc = self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mtrcaCapRegisterPquery)
                if rc:
                    raise RegAccException("Failed to send Register MTRC (case 3): %s (%d)" % (self._err2str(rc), rc))
                if mtrcaCapRegisterPquery.contents.trace_owner == 1:
                    return 0
                iter += 1

        def sendMtrcCapReleaseOwnership(self):
            mcamRegP = pointer(MCAM_REG_EXT())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                # in case of failure to get capability assume taking ownership is not required, same as in mlxtrace.
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED
            mtcrCapSupported = extractField(mcamRegP.contents.mng_access_reg_cap_mask[3 - 2], 0, 1)
            if mtcrCapSupported == 0:
                return ownershipEnum.REG_ACCESS_NO_OWNERSHIP_REQUIRED

            mtrcaCapRegisterP = pointer(MTRC_CAP_REG_EXT())
            mtrcaCapRegisterP.contents.trace_owner = c_uint8(0)
            self._reg_access_mtrc_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), mtrcaCapRegisterP)
            return 0

        def sendResDump(self, segment_type, seq_num, inline_mode, more_dump, vhca_id, vhca_id_valid, index1, index2, num_of_obj2, num_of_obj1, device_opaque, mkey, size, address):
            resDumpRegP = pointer(RESOURCE_DUMP_EXT())
            resDumpRegP.contents.segment_type = c_uint16(segment_type)
            resDumpRegP.contents.seq_num = c_uint8(seq_num)
            resDumpRegP.contents.inline_dump = c_uint8(inline_mode)
            resDumpRegP.contents.more_dump = c_uint8(more_dump)
            resDumpRegP.contents.vhca_id = c_uint16(vhca_id)
            resDumpRegP.contents.vhca_id_valid = c_uint8(vhca_id_valid)
            resDumpRegP.contents.index1 = c_uint32(index1)
            resDumpRegP.contents.index2 = c_uint32(index2)
            resDumpRegP.contents.num_of_obj2 = c_uint16(num_of_obj2)
            resDumpRegP.contents.num_of_obj1 = c_uint16(num_of_obj1)
            resDumpRegP.contents.device_opaque = c_uint64(device_opaque)
            resDumpRegP.contents.mkey = c_uint32(mkey)
            resDumpRegP.contents.size = c_uint32(size)
            resDumpRegP.contents.address = c_uint64(address)
            rc = self._reg_access_res_dump(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), resDumpRegP)
            if rc:
                raise RegAccException("Failed to send Register RESOURCE DUMP with rc: %d" % rc)
            # return (resDumpRegP.contents.segment_type, resDumpRegP.contents.seq_num, resDumpRegP.contents.inline_data[0])
            return ({"segment_type": resDumpRegP.contents.segment_type,
                     "seq_num": resDumpRegP.contents.seq_num,
                     "inline_dump": resDumpRegP.contents.inline_dump,
                     "more_dump": resDumpRegP.contents.more_dump,
                     "vhca_id": resDumpRegP.contents.vhca_id,
                     "vhca_id_valid": resDumpRegP.contents.vhca_id_valid,
                     "index1": resDumpRegP.contents.index1,
                     "index2": resDumpRegP.contents.index2,
                     "num_of_obj2": resDumpRegP.contents.num_of_obj2,
                     "num_of_obj1": resDumpRegP.contents.num_of_obj1,
                     "device_opaque": resDumpRegP.contents.device_opaque,
                     "mkey": resDumpRegP.contents.mkey,
                     "size": resDumpRegP.contents.size,
                     "address": resDumpRegP.contents.address,
                     "inline_data": resDumpRegP.contents.inline_data})

        def sendDebugCap(self):
            debugCapRegP = pointer(DEBUG_CAP())
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
            tmp = pointer(DIAGNOSTIC_CNTR_LAYOUT())
            tmp.contents.counter_id = c_uint16(0)
            tmp.contents.sync = c_uint8(0)
            debugCapRegP.contents.diagnostic_counter = pointer(DIAGNOSTIC_CNTR_ST_ARR())
            rc = self._reg_access_debug_cap(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), debugCapRegP)
            if rc:
                raise RegAccException("Failed to send Register DEBUG CAP with rc: %d" % rc)
            return debugCapRegP.contents.resource_dump

        def sendPcnr(self, tuning_override, local_port):  # Requirments : new FW version + burn with allow_pcnr

            pcnrRegisterP = pointer(PCNR_REG_EXT())
            pcnrRegisterP.contents.tuning_override = c_uint8(tuning_override)
            pcnrRegisterP.contents.local_port = c_uint8(local_port)

            rc = self._reg_access_pcnr(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), pcnrRegisterP)
            if rc:
                raise RegAccException("Failed to send Register PCNR: %s (%d)" % (self._err2str(rc), rc))

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

            mpcirRegisterP = pointer(MPCIR_EXT(ports=command))
            rc = self._reg_access_mpcir(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mpcirRegisterP)
            if rc != 0:
                raise RegAccException("Failed to send Command Register MPCIR")
            if command == CMD_GET_STATUS:
                return mpcirRegisterP.contents.ports_stat

        def sendMRSR(self, command):

            mrsrRegisterP = pointer(MRSR_EXT(command=command))
            rc = self._reg_access_mrsr(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_SET), mrsrRegisterP)
            if rc != 0:
                raise RegAccException("Failed to send Command Register MRSR")

        def getDTOR(self):
            dtorRegisterP = pointer(DTOR_REG_EXT())
            rc = self._reg_access_dtor(self._mstDev.mf, REG_ACCESS_METHOD_GET, dtorRegisterP)
            if rc:
                raise RegAccException("Failed to send Register DTOR")

            return {
                "DRIVER_UNLOAD_AND_RESET_TO": dtorRegisterP.contents.DRIVER_UNLOAD_AND_RESET_TO,
                "PCI_SYNC_UPDATE_TO": dtorRegisterP.contents.PCI_SYNC_UPDATE_TO,
                "PCIE_TOGGLE_TO": dtorRegisterP.contents.PCIE_TOGGLE_TO,
                "EMBEDDED_CPU_OS_SHUTDOWN_TO": dtorRegisterP.contents.EMBEDDED_CPU_OS_SHUTDOWN_TO
            }

        def getMRSI(self, device=0):
            mrsiRegisterP = pointer(MRSI_EXT(device=device))
            rc = self._reg_access_mrsi(self._mstDev.mf, REG_ACCESS_METHOD_GET, mrsiRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MRSI")

            return {
                "reset_reason": mrsiRegisterP.contents.reset_reason,
                "crts": mrsiRegisterP.contents.crts,
                "ecos": mrsiRegisterP.contents.ecos
            }

        ##########################
        def sendMFRL(self, method, resetLevel=None, reset_type=None, reset_sync=None, pci_reset_request_method=None):  

            mfrlRegisterP = pointer(MFRL_REG_EXT())

            if method == REG_ACCESS_METHOD_SET:
                if resetLevel is None or reset_type is None or reset_sync is None or pci_reset_request_method is None:
                    raise RegAccException("Failed to sendMFRL (reset level/type/sync/pci_reset_request_method is None for SET command)")
                mfrlRegisterP.contents.reset_trigger = c_uint8(resetLevel)
                mfrlRegisterP.contents.rst_type_sel = c_uint8(reset_type)
                mfrlRegisterP.contents.pci_sync_for_fw_update_start = c_uint8(reset_sync)
                mfrlRegisterP.contents.pci_reset_req_method = c_uint8(pci_reset_request_method)
                
            c_method = c_uint(method)
            rc = self._reg_access_mfrl(self._mstDev.mf, c_method, mfrlRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MFRL: %s (%d)" % (self._err2str(rc), rc))
            
            if method == REG_ACCESS_METHOD_GET:
                return mfrlRegisterP.contents.reset_trigger, mfrlRegisterP.contents.reset_type, mfrlRegisterP.contents.pci_rescan_required, mfrlRegisterP.contents.reset_state

        ##########################
        def sendMPIR(self, depth, pcie_index, node):
            from regaccess_hca_ext_structs import MPIR_EXT as MPIR_EXT_HCA
            mpirRegisterP = pointer(MPIR_EXT_HCA())
            mpirRegisterP.contents.depth = depth
            mpirRegisterP.contents.pcie_index = pcie_index
            mpirRegisterP.contents.node = node
            rc = self._reg_access_mpir(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mpirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MPIR: %s (%d)" % (self._err2str(rc), rc))

            return mpirRegisterP.contents.bus, mpirRegisterP.contents.device, mpirRegisterP.contents.sdm
        
        ##########################
        def sendMPEIN(self, depth, pcie_index, node):
            mpeinRegisterP = pointer(MPEIN_REG_EXT())
            mpeinRegisterP.contents.depth = depth
            mpeinRegisterP.contents.pcie_index = pcie_index
            mpeinRegisterP.contents.node = node
            rc = self._reg_access_mpein(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mpeinRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MPEIN: %s (%d)" % (self._err2str(rc), rc))

            return mpeinRegisterP.contents.port_type

        
         ##########################
        # [ConnectX FW PCI - Design] Bug SW #4739922: [Access Registers] MPQD Returns a Syndrome for Invalid PCIe Indexes
        # the above bug causes this read to fail if pcie_index=0 is one the querying host in not privileged to - once it's solve this read will succeed ALWAYS
        def sendMPQD(self, depth, node, DPNv, pcie_index):
            mpqdRegisterP = pointer(MPQD_REG_EXT())
            mpqdRegisterP.contents.depth = depth
            mpqdRegisterP.contents.pcie_index = pcie_index
            mpqdRegisterP.contents.node = node
            mpqdRegisterP.contents.DPNv = DPNv

            rc = self._reg_access_mpqd(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mpqdRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MPQD: %s (%d)" % (self._err2str(rc), rc))

            return mpqdRegisterP.contents.requester_pcie_index

        ##########################
        def sendMROQ(self, reset_type):
            mroqRegisterP = pointer(MROQ_EXT())
            mroqRegisterP.contents.reset_type = c_uint8(reset_type)

            c_method = c_uint(REG_ACCESS_METHOD_GET)
            rc = self._reg_access_mroq(self._mstDev.mf, c_method, mroqRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MROQ:  %s (%d)" % (self._err2str(rc), rc))

            return mroqRegisterP.contents.pci_sync_for_fw_update_start, mroqRegisterP.contents.pci_reset_req_method
        ##########################
        def getMCAM(self, access_reg_group=0):

            mcamRegP = pointer(MCAM_REG_EXT())
            mcamRegP.contents.access_reg_group = c_uint8(access_reg_group)

            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                raise RegAccException("Failed to send Register MCAM (rc: {0})".format(rc))

            return {
                "access_reg_group": mcamRegP.contents.access_reg_group,
                "feature_group": mcamRegP.contents.feature_group,
                "mng_access_reg_cap_mask": mcamRegP.contents.mng_access_reg_cap_mask,
                "mng_feature_cap_mask": mcamRegP.contents.mng_feature_cap_mask
            }

        ##########################
        def getFwVersion(self):

            mgirRegisterP = pointer(MGIR_EXT())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                info_ver = ""
            else:
                # get dev branch tag
                info_ver = "".join(chr(val) for val in mgirRegisterP.contents.dev_info.dev_branch_tag if val != 0)

                # if dev branch is empty, try to get the primary version
                if info_ver == "":
                    if mgirRegisterP.contents.fw_info.major != 0:
                        info_ver = "{0}.{1}.{2}".format(mgirRegisterP.contents.fw_info.major,
                                                        mgirRegisterP.contents.fw_info.minor,
                                                        mgirRegisterP.contents.fw_info.sub_minor)
                    elif mgirRegisterP.contents.fw_info.extended_major != 0:
                        info_ver = "{0}.{1}.{2}".format(mgirRegisterP.contents.fw_info.extended_major,
                                                        mgirRegisterP.contents.fw_info.extended_minor,
                                                        mgirRegisterP.contents.fw_info.extended_sub_minor)

            return info_ver

        def getFWUptime(self):

            mgirRegisterP = pointer(MGIR_EXT())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MGIR (case 1): %s (%d)" % (self._err2str(rc), rc))

            return mgirRegisterP.contents.hw_info.uptime

        def getMtrcCap(self):
            mcamRegP = pointer(MCAM_REG_EXT())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                # in case of failure to get capability assume taking ownership is not required, same as in mlxtrace.
                return False
            mtcrCapSupported = extractField(mcamRegP.contents.mng_access_reg_cap_mask[3 - 2], 0, 1)
            if mtcrCapSupported == 0:
                return False
            mtrcCapRegisterP = pointer(MTRC_CAP_REG_EXT())
            rc = self._reg_access_mtrc_cap(self._mstDev.mf, REG_ACCESS_METHOD_GET, mtrcCapRegisterP)
            if rc:
                raise RegAccException("Failed to send Register Mtrc_Cap (case 1): %s (%d)" % (self._err2str(rc), rc))

            string_db_parameters_list = []
            for i in range(0, 8):
                string_db_parameters_list.append(
                    {
                        "string_db_base_address": mtrcCapRegisterP.contents.string_db_param[i].string_db_base_address,
                        "string_db_size": mtrcCapRegisterP.contents.string_db_param[i].string_db_size
                    }
                )

            return {
                "num_string_db": mtrcCapRegisterP.contents.num_string_db,
                "trc_ver": mtrcCapRegisterP.contents.trc_ver,
                "trace_to_memory": mtrcCapRegisterP.contents.trace_to_memory,
                "trace_owner": mtrcCapRegisterP.contents.trace_owner,
                "num_string_trace": mtrcCapRegisterP.contents.num_string_trace,
                "first_string_trace": mtrcCapRegisterP.contents.first_string_trace,
                "log_max_trace_buffer_size": mtrcCapRegisterP.contents.log_max_trace_buffer_size,
                "string_db_param": string_db_parameters_list,
            }

        def isMtrcStdbSupported(self):
            mcamRegP = pointer(MCAM_REG_EXT())
            rc = self._reg_access_mcam(self._mstDev.mf, c_uint(REG_ACCESS_METHOD_GET), mcamRegP)
            if rc:
                # in case of failure to get capability assume taking ownership is not required, same as in mlxtrace.
                return False
            mtcrStdbSupported = extractField(mcamRegP.contents.mng_access_reg_cap_mask[3 - 2], 2, 1)
            if mtcrStdbSupported == 0:
                return False
            return True

        def getMtrcStdbStringDbData(self, string_db_index, read_size):
            c_string_db_index = c_uint8(string_db_index)
            c_read_size = c_uint32(read_size)
            byte_buffer = (c_uint8 * read_size)()
            rc = self._reg_access_mtrc_stdb_warpper(self._mstDev.mf, c_read_size, c_string_db_index, byte_buffer)
            if rc:
                raise RegAccException("Failed to send Register Mtrc_Stdb (case 1): {}".format(rc))

            uint32_buffer = ctypes.cast(byte_buffer, ctypes.POINTER(ctypes.c_uint32))
            data = b"".join([struct.pack('>I', uint32_buffer[i]) for i in range(read_size // 4)])
            return data

        def getManufacturingBaseMac(self):

            mgirRegisterP = pointer(MGIR_EXT())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)

            if rc:
                raise RegAccException("Failed to send Register MGIR (case 2): %s (%d)" % (self._err2str(rc), rc))

            lsp = mgirRegisterP.contents.hw_info.manufacturing_base_mac_31_0
            msp = mgirRegisterP.contents.hw_info.manufacturing_base_mac_47_32

            return msp * (2**32) + lsp

        def getSecureFWStatus(self):
            """ Returns True if the FW is secured, False otherwise.
            """
            mgirRegisterP = pointer(MGIR_EXT())

            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MGIR (case 3): %s (%d)" % (self._err2str(rc), rc))

            result = mgirRegisterP.contents.fw_info.secured
            result = True if result else False
            return result

        def getPSID(self):
            mgirRegisterP = pointer(MGIR_EXT())
            rc = self._reg_access_mgir(self._mstDev.mf, REG_ACCESS_METHOD_GET, mgirRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MGIR (case 4): %s (%d)" % (self._err2str(rc), rc))

            psid = "".join(chr(val) for val in mgirRegisterP.contents.fw_info.psid if val != 0)
            return psid

        def sendMddq(self, query_type, request_message_sequence, slot_index, query_index=0):
            mddqRegisterP = pointer(MDDQ_EXT())
            mddqRegisterP.contents.query_type = c_uint8(query_type)
            mddqRegisterP.contents.slot_index = c_uint8(slot_index)
            mddqRegisterP.contents.request_message_sequence = c_uint8(request_message_sequence)
            mddqRegisterP.contents.query_index = c_uint8(query_index)
            rc = self._reg_access_mddq(self._mstDev.mf, REG_ACCESS_METHOD_GET, mddqRegisterP)
            if rc:
                raise RegAccException("Failed to send Register MDDQ: %s (%d)" % (self._err2str(rc), rc))

            data = {}
            if query_type == 1:
                data.update({
                    "active": mddqRegisterP.contents.data.slot_info_ext.active,
                    "lc_ready": mddqRegisterP.contents.data.slot_info_ext.lc_ready,
                    "sr_valid": mddqRegisterP.contents.data.slot_info_ext.sr_valid,
                    "provisioned": mddqRegisterP.contents.data.slot_info_ext.provisioned,
                    "ini_file_version": mddqRegisterP.contents.data.slot_info_ext.ini_file_version,
                    "hw_revision": mddqRegisterP.contents.data.slot_info_ext.hw_revision,
                    "card_type": mddqRegisterP.contents.data.slot_info_ext.card_type
                })
            elif query_type == 2:
                device_type_name = "".join(chr(val) for val in mddqRegisterP.contents.data.device_info_ext.device_type_name if val != 0)
                data.update({
                    "device_index": mddqRegisterP.contents.data.device_info_ext.device_index,
                    "flash_id": mddqRegisterP.contents.data.device_info_ext.flash_id,
                    "flash_owner": mddqRegisterP.contents.data.device_info_ext.flash_owner,
                    "uses_flash": mddqRegisterP.contents.data.device_info_ext.uses_flash,
                    "device_type": mddqRegisterP.contents.data.device_info_ext.device_type,
                    "fw_major": mddqRegisterP.contents.data.device_info_ext.fw_major,
                    "fw_sub_minor": mddqRegisterP.contents.data.device_info_ext.fw_sub_minor,
                    "fw_minor": mddqRegisterP.contents.data.device_info_ext.fw_minor,
                    "max_cmd_write_size_supp": mddqRegisterP.contents.data.device_info_ext.max_cmd_write_size_supp,
                    "max_cmd_read_size_supp": mddqRegisterP.contents.data.device_info_ext.max_cmd_read_size_supp,
                    "device_type_name": device_type_name
                })
            return ({"slot_index": mddqRegisterP.contents.slot_index,
                     "query_type": mddqRegisterP.contents.query_type,
                     "request_message_sequence": mddqRegisterP.contents.request_message_sequence,
                     "response_message_sequence": mddqRegisterP.contents.response_message_sequence,
                     "data_valid": mddqRegisterP.contents.data_valid},
                    data)

        def sendMTEIM(self):
            mteimRegisterP = pointer(MTEIM_REG_EXT())
            rc = self._reg_access_mteim(self._mstDev.mf, REG_ACCESS_METHOD_GET, mteimRegisterP)
            if rc:
                return None  # done raise error, could be old FW / Device
                # raise RegAccException("Failed to send Register MTEIM: %s (%d)" % (self._err2str(rc), rc))

            return ({"cap_core_tile": mteimRegisterP.contents.cap_core_tile,
                    "cap_core_main": mteimRegisterP.contents.cap_core_main,
                     "cap_core_dpa": mteimRegisterP.contents.cap_core_dpa,
                     "cap_num_of_tile": mteimRegisterP.contents.cap_num_of_tile,
                     "type_core_tile": mteimRegisterP.contents.type_core_tile,
                     "type_core_main": mteimRegisterP.contents.type_core_main,
                     "type_core_dpa": mteimRegisterP.contents.type_core_dpa,
                     "is_phy_uc_supported": mteimRegisterP.contents.is_phy_uc_supported,
                     "is_dwsn_msb_supported": mteimRegisterP.contents.is_dwsn_msb_supported,
                     "first_dpa_core_event_id": mteimRegisterP.contents.first_dpa_core_event_id,
                     "first_main_core_event_id": mteimRegisterP.contents.first_main_core_event_id,
                     "first_tile_core_event_id": mteimRegisterP.contents.first_tile_core_event_id
                     })


else:
    raise RegAccException("Failed to load rreg_access.so/libreg_access.dll")

####################################################################################
