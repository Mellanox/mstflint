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
#    This file was generated at "2023-07-20 15:41:50"
#    by:
#      > gen_adb_data.py -g hca_prm_projects
###############################################################################

import os
import sys
import ctypes
import platform

import mtcr


class DEFAULT_TIMEOUT(ctypes.Structure):
    _fields_ = [
        ("to_value", ctypes.c_uint32),
        ("to_multiplier", ctypes.c_uint8)
    ]

class DTOR_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("PCIE_TOGGLE_TO", DEFAULT_TIMEOUT),
        ("HEALTH_POLL_TO", DEFAULT_TIMEOUT),
        ("FULL_CRDUMP_TO", DEFAULT_TIMEOUT),
        ("FW_RESET_TO", DEFAULT_TIMEOUT),
        ("FLUSH_ON_ERR_TO", DEFAULT_TIMEOUT),
        ("PCI_SYNC_UPDATE_TO", DEFAULT_TIMEOUT),
        ("TEAR_DOWN_TO", DEFAULT_TIMEOUT),
        ("FSM_REACTIVATE_TO", DEFAULT_TIMEOUT),
        ("RECLAIM_PAGES_TO", DEFAULT_TIMEOUT),
        ("RECLAIM_VFS_PAGES_TO", DEFAULT_TIMEOUT),
        ("DRIVER_UNLOAD_AND_RESET_TO", DEFAULT_TIMEOUT)
    ]

class MRSI_EXT(ctypes.Structure):
    _fields_ = [
        ("device", ctypes.c_uint8),
        ("reset_reason", ctypes.c_uint8),
        ("crts", ctypes.c_uint64)
    ]

class PCNR_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("tuning_override", ctypes.c_uint8),
        ("lp_msb", ctypes.c_uint8),
        ("local_port", ctypes.c_uint8),
        ("keep_phy_setting", ctypes.c_uint8)
    ]

class STRING_DB_PARAMETERS_EXT(ctypes.Structure):
    _fields_ = [
        ("string_db_base_address", ctypes.c_uint32),
        ("string_db_size", ctypes.c_uint32)
    ]

class MTRC_CAP_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("num_string_db", ctypes.c_uint8),
        ("trc_ver", ctypes.c_uint8),
        ("trace_to_memory", ctypes.c_uint8),
        ("trace_owner", ctypes.c_uint8),
        ("num_string_trace", ctypes.c_uint8),
        ("first_string_trace", ctypes.c_uint8),
        ("log_max_trace_buffer_size", ctypes.c_uint8),
        ("string_db_param", STRING_DB_PARAMETERS_EXT * 8)
    ]

class MGIR_HARDWARE_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("device_id", ctypes.c_uint16),
        ("device_hw_revision", ctypes.c_uint16),
        ("pvs", ctypes.c_uint8),
        ("technology", ctypes.c_uint8),
        ("num_ports", ctypes.c_uint8),
        ("hw_dev_id", ctypes.c_uint16),
        ("manufacturing_base_mac_47_32", ctypes.c_uint16),
        ("manufacturing_base_mac_31_0", ctypes.c_uint32),
        ("uptime", ctypes.c_uint32)
    ]

class MGIR_FW_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("sub_minor", ctypes.c_uint8),
        ("minor", ctypes.c_uint8),
        ("major", ctypes.c_uint8),
        ("secured", ctypes.c_uint8),
        ("signed_fw", ctypes.c_uint8),
        ("debug", ctypes.c_uint8),
        ("dev", ctypes.c_uint8),
        ("string_tlv", ctypes.c_uint8),
        ("dev_sc", ctypes.c_uint8),
        ("build_id", ctypes.c_uint32),
        ("year", ctypes.c_uint16),
        ("day", ctypes.c_uint8),
        ("month", ctypes.c_uint8),
        ("hour", ctypes.c_uint16),
        ("psid", ctypes.c_uint8 * 16),
        ("ini_file_version", ctypes.c_uint32),
        ("extended_major", ctypes.c_uint32),
        ("extended_minor", ctypes.c_uint32),
        ("extended_sub_minor", ctypes.c_uint32),
        ("isfu_major", ctypes.c_uint16),
        ("disabled_tiles_bitmap", ctypes.c_uint16),
        ("life_cycle", ctypes.c_uint8),
        ("sec_boot", ctypes.c_uint8),
        ("encryption", ctypes.c_uint8)
    ]

class ROM_VERSION_EXT(ctypes.Structure):
    _fields_ = [
        ("build", ctypes.c_uint16),
        ("minor", ctypes.c_uint8),
        ("major", ctypes.c_uint8)
    ]

class MGIR_SW_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("sub_minor", ctypes.c_uint8),
        ("minor", ctypes.c_uint8),
        ("major", ctypes.c_uint8),
        ("rom3_type", ctypes.c_uint8),
        ("rom3_arch", ctypes.c_uint8),
        ("rom2_type", ctypes.c_uint8),
        ("rom2_arch", ctypes.c_uint8),
        ("rom1_type", ctypes.c_uint8),
        ("rom1_arch", ctypes.c_uint8),
        ("rom0_type", ctypes.c_uint8),
        ("rom0_arch", ctypes.c_uint8),
        ("rom0_version", ROM_VERSION_EXT),
        ("rom1_version", ROM_VERSION_EXT),
        ("rom2_version", ROM_VERSION_EXT),
        ("rom3_version", ROM_VERSION_EXT)
    ]

class MGIR_DEV_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("dev_branch_tag", ctypes.c_uint8 * 28)
    ]

class MGIR_EXT(ctypes.Structure):
    _fields_ = [
        ("hw_info", MGIR_HARDWARE_INFO_EXT),
        ("fw_info", MGIR_FW_INFO_EXT),
        ("sw_info", MGIR_SW_INFO_EXT),
        ("dev_info", MGIR_DEV_INFO_EXT)
    ]

class RESOURCE_DUMP_EXT(ctypes.Structure):
    _fields_ = [
        ("segment_type", ctypes.c_uint16),
        ("seq_num", ctypes.c_uint8),
        ("vhca_id_valid", ctypes.c_uint8),
        ("inline_dump", ctypes.c_uint8),
        ("more_dump", ctypes.c_uint8),
        ("vhca_id", ctypes.c_uint16),
        ("index1", ctypes.c_uint32),
        ("index2", ctypes.c_uint32),
        ("num_of_obj2", ctypes.c_uint16),
        ("num_of_obj1", ctypes.c_uint16),
        ("device_opaque", ctypes.c_uint64),
        ("mkey", ctypes.c_uint32),
        ("size", ctypes.c_uint32),
        ("address", ctypes.c_uint64),
        ("inline_data", ctypes.c_uint32 * 52)
    ]

class DIAGNOSTIC_CNTR_LAYOUT(ctypes.Structure):
    _fields_ = [
        ("counter_id", ctypes.c_uint16),
        ("sync", ctypes.c_uint8)
    ]

class MFRL_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("reset_trigger", ctypes.c_uint8),
        ("reset_type", ctypes.c_uint8),
        ("reset_state", ctypes.c_uint8),
        ("pci_leaf_dsp_exist", ctypes.c_uint8),
        ("pci_leaf_dsp_traffic_dis_commited", ctypes.c_uint8),
        ("rst_type_sel", ctypes.c_uint8),
        ("pci_sync_for_fw_update_resp", ctypes.c_uint8),
        ("pci_sync_for_fw_update_start", ctypes.c_uint8),
        ("pci_rescan_required", ctypes.c_uint8)
    ]

class MPCIR_EXT(ctypes.Structure):
    _fields_ = [
        ("all", ctypes.c_uint8),
        ("ports", ctypes.c_uint8),
        ("ports_stat", ctypes.c_uint8)
    ]

class MCAM_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("access_reg_group", ctypes.c_uint8),
        ("feature_group", ctypes.c_uint8),
        ("mng_access_reg_cap_mask", ctypes.c_uint32 * 4),
        ("mng_feature_cap_mask", ctypes.c_uint32 * 4)
    ]

class MTRC_STDB_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("read_size", ctypes.c_uint32),
        ("string_db_index", ctypes.c_uint8),
        ("start_offset", ctypes.c_uint32),
        ("string_db_data", ctypes.c_uint32)
    ]

class MTEIM_REG(ctypes.Structure):
    _fields_ = [
        ("cap_core_tile", ctypes.c_uint8),
        ("cap_core_main", ctypes.c_uint8),
        ("cap_core_dpa", ctypes.c_uint8),
        ("cap_num_of_tile", ctypes.c_uint8),
        ("type_core_tile", ctypes.c_uint8),
        ("type_core_main", ctypes.c_uint8),
        ("type_core_dpa", ctypes.c_uint8),
        ("is_phy_uc_supported", ctypes.c_uint8),
        ("is_dwsn_msb_supported", ctypes.c_uint8),
        ("first_dpa_core_event_id", ctypes.c_uint8),
        ("first_main_core_event_id", ctypes.c_uint8),
        ("first_tile_core_event_id", ctypes.c_uint8 * 8)
    ]

class SLOT_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("active", ctypes.c_uint8),
        ("lc_ready", ctypes.c_uint8),
        ("sr_valid", ctypes.c_uint8),
        ("provisioned", ctypes.c_uint8),
        ("ini_file_version", ctypes.c_uint16),
        ("hw_revision", ctypes.c_uint16),
        ("card_type", ctypes.c_uint8)
    ]

class DEVICE_INFO_EXT(ctypes.Structure):
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

class SLOT_NAME_EXT(ctypes.Structure):
    _fields_ = [
        ("slot_ascii_name", ctypes.c_uint8 * 20)
    ]

class MDDQ_DATA_AUTO_EXT(ctypes.Union):
    _fields_ = [
        ("slot_info_ext", SLOT_INFO_EXT),
        ("device_info_ext", DEVICE_INFO_EXT),
        ("slot_name_ext", SLOT_NAME_EXT)
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
        ("end", ctypes.c_uint8),
        ("time_left", ctypes.c_uint32)
    ]

class NIC_DPA_EUG_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("eug_id", ctypes.c_uint16),
        ("operation", ctypes.c_uint8),
        ("modify_field_select", ctypes.c_uint32),
        ("eug_name", ctypes.c_uint32 * 4),
        ("member_mask", ctypes.c_uint32 * 32)
    ]

class NIC_DPA_PERF_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("dpa_process_num", ctypes.c_uint32),
        ("dpa_timer_frequency", ctypes.c_uint32),
        ("mkey", ctypes.c_uint32),
        ("size", ctypes.c_uint32),
        ("address", ctypes.c_uint64)
    ]

class NIC_DPA_PERF_CTRL_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("dpa_process_handle", ctypes.c_uint32),
        ("count_state", ctypes.c_uint8)
    ]

class NIC_CAP_EXT_REG(ctypes.Structure):
    _fields_ = [
        ("cap_group", ctypes.c_uint16),
        ("cap_data", ctypes.c_uint32 * 28)
    ]

class MRSR_EXT(ctypes.Structure):
    _fields_ = [
        ("command", ctypes.c_uint8)
    ]

