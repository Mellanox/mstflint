 #
 # Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 #


###############################################################################
#    This file was generated at "2025-12-21 15:54:42"
#    by:
#      > /tmp/jenkins/workspace/automatic_prm_update/scripts/prm_update.py --project switch
###############################################################################

import os
import sys
import ctypes
import platform

import mtcr


class MMAM_EXT(ctypes.Structure):
    _fields_ = [
        ("module", ctypes.c_uint8),
        ("ga", ctypes.c_uint8),
        ("local_module", ctypes.c_uint8),
        ("module_type", ctypes.c_uint8)
    ]

class MGPIR_HW_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("num_of_devices", ctypes.c_uint8),
        ("num_of_modules_per_system", ctypes.c_uint8),
        ("devices_per_flash", ctypes.c_uint8),
        ("device_type", ctypes.c_uint8),
        ("slot_index", ctypes.c_uint8),
        ("num_of_modules", ctypes.c_uint8),
        ("num_of_slots", ctypes.c_uint8),
        ("max_modules_per_slot", ctypes.c_uint8),
        ("num_of_resource_modules", ctypes.c_uint8),
        ("num_lanes_per_sub_module", ctypes.c_uint8),
        ("max_sub_modules_index", ctypes.c_uint8)
    ]

class MGPIR_EXT(ctypes.Structure):
    _fields_ = [
        ("hw_info", MGPIR_HW_INFO_EXT)
    ]

class MPIR_EXT(ctypes.Structure):
    _fields_ = [
        ("host_buses", ctypes.c_uint8),
        ("node", ctypes.c_uint8),
        ("pcie_index", ctypes.c_uint8),
        ("depth", ctypes.c_uint8),
        ("DPNv", ctypes.c_uint8),
        ("sdm", ctypes.c_uint8),
        ("subordinate_bus", ctypes.c_uint8),
        ("secondary_bus", ctypes.c_uint8),
        ("segment_base", ctypes.c_uint8),
        ("segment_valid", ctypes.c_uint8),
        ("segment_cap", ctypes.c_uint8),
        ("device", ctypes.c_uint8),
        ("lp_msb", ctypes.c_uint8),
        ("bus", ctypes.c_uint8),
        ("local_port", ctypes.c_uint8),
        ("slot_number", ctypes.c_uint16),
        ("num_con_devices", ctypes.c_uint8),
        ("host_index", ctypes.c_uint8),
        ("slot_cap", ctypes.c_uint8)
    ]

class MDDQ_SLOT_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("active", ctypes.c_uint8),
        ("lc_ready", ctypes.c_uint8),
        ("sr_valid", ctypes.c_uint8),
        ("provisioned", ctypes.c_uint8),
        ("ini_file_version", ctypes.c_uint16),
        ("hw_revision", ctypes.c_uint16),
        ("card_type", ctypes.c_uint8)
    ]

class MDDQ_DEVICE_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("device_index", ctypes.c_uint8),
        ("flash_id", ctypes.c_uint8),
        ("lc_pwr_on", ctypes.c_uint8),
        ("thermal_sd", ctypes.c_uint8),
        ("flash_owner", ctypes.c_uint8),
        ("uses_flash", ctypes.c_uint8),
        ("device_type", ctypes.c_uint16),
        ("fw_major", ctypes.c_uint16),
        ("fw_sub_minor", ctypes.c_uint16),
        ("fw_minor", ctypes.c_uint16),
        ("max_cmd_write_size_supp", ctypes.c_uint8),
        ("max_cmd_read_size_supp", ctypes.c_uint8),
        ("device_type_name", ctypes.c_uint8 * 8)
    ]

class MDDQ_SLOT_NAME_EXT(ctypes.Structure):
    _fields_ = [
        ("slot_ascii_name", ctypes.c_uint8 * 20)
    ]

class MDDQ_DATA_AUTO_EXT(ctypes.Union):
    _fields_ = [
        ("mddq_slot_info_ext", MDDQ_SLOT_INFO_EXT),
        ("mddq_device_info_ext", MDDQ_DEVICE_INFO_EXT),
        ("mddq_slot_name_ext", MDDQ_SLOT_NAME_EXT)
    ]

class MDDQ_EXT(ctypes.Structure):
    _fields_ = [
        ("slot_index", ctypes.c_uint8),
        ("query_type", ctypes.c_uint8),
        ("sie", ctypes.c_uint8),
        ("request_message_sequence", ctypes.c_uint8),
        ("response_message_sequence", ctypes.c_uint8),
        ("query_index", ctypes.c_uint8),
        ("data_valid", ctypes.c_uint8),
        ("data", MDDQ_DATA_AUTO_EXT)
    ]

class MDSR_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("status", ctypes.c_uint8),
        ("additional_info", ctypes.c_uint8),
        ("type_of_token", ctypes.c_uint8),
        ("revoke_version", ctypes.c_uint8),
        ("end", ctypes.c_uint8),
        ("time_left", ctypes.c_uint32)
    ]

class MRSR_EXT(ctypes.Structure):
    _fields_ = [
        ("command", ctypes.c_uint8)
    ]

class MFMC_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("fs", ctypes.c_uint8),
        ("wrp_block_count", ctypes.c_uint8),
        ("block_size", ctypes.c_uint8),
        ("wrp_en", ctypes.c_uint8),
        ("sub_sector_protect_size", ctypes.c_uint8),
        ("sector_protect_size", ctypes.c_uint8),
        ("quad_en", ctypes.c_uint8),
        ("dummy_clock_cycles", ctypes.c_uint8)
    ]

class MPEIN_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("node", ctypes.c_uint8),
        ("pcie_index", ctypes.c_uint8),
        ("depth", ctypes.c_uint8),
        ("DPNv", ctypes.c_uint8),
        ("link_speed_enabled", ctypes.c_uint16),
        ("link_width_enabled", ctypes.c_uint8),
        ("link_speed_active", ctypes.c_uint16),
        ("link_width_active", ctypes.c_uint8),
        ("lane0_physical_position", ctypes.c_uint8),
        ("num_of_vfs", ctypes.c_uint16),
        ("num_of_pfs", ctypes.c_uint16),
        ("bdf0", ctypes.c_uint16),
        ("lane_reversal", ctypes.c_uint8),
        ("cmn_clk_mode", ctypes.c_uint8),
        ("port_type", ctypes.c_uint8),
        ("pwr_status", ctypes.c_uint8),
        ("max_payload_size", ctypes.c_uint8),
        ("max_read_request_size", ctypes.c_uint8),
        ("pci_power", ctypes.c_uint16),
        ("link_peer_max_speed", ctypes.c_uint16),
        ("flit_sup", ctypes.c_uint8),
        ("precode_sup", ctypes.c_uint8),
        ("flit_active", ctypes.c_uint8),
        ("precode_active", ctypes.c_uint8),
        ("device_status", ctypes.c_uint16)
    ]

