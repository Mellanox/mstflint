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
#    This file was generated at "2026-01-07 11:57:16"
#    by:
#      > prm_update.py --project Nic
###############################################################################

import os
import sys
import ctypes
import platform

import mtcr


class MPQD_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("node", ctypes.c_uint8),
        ("pcie_index", ctypes.c_uint8),
        ("depth", ctypes.c_uint8),
        ("DPNv", ctypes.c_uint8),
        ("requester_pcie_index", ctypes.c_uint8),
        ("max_valid_pcie_index", ctypes.c_uint8),
        ("max_exist_depth", ctypes.c_uint8),
        ("is_internal", ctypes.c_uint8),
        ("number_of_nodes", ctypes.c_uint8),
        ("node_phy", ctypes.c_uint8),
        ("valid_index", ctypes.c_uint8),
        ("valid_node", ctypes.c_uint8),
        ("DSP_node", ctypes.c_uint8),
        ("parent_node_number", ctypes.c_uint8)
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
        ("sd_group", ctypes.c_uint8),
        ("device", ctypes.c_uint8),
        ("lp_msb", ctypes.c_uint8),
        ("bus", ctypes.c_uint8),
        ("local_port", ctypes.c_uint8),
        ("slot_number", ctypes.c_uint16),
        ("num_con_devices", ctypes.c_uint8),
        ("host_index", ctypes.c_uint8),
        ("slot_cap", ctypes.c_uint8)
    ]

class MRSI_EXT(ctypes.Structure):
    _fields_ = [
        ("device", ctypes.c_uint8),
        ("reset_reason", ctypes.c_uint8),
        ("crts", ctypes.c_uint64),
        ("ecos", ctypes.c_uint8)
    ]

class DIAGNOSTIC_CNTR_LAYOUT(ctypes.Structure):
    _fields_ = [
        ("counter_id", ctypes.c_uint16),
        ("sync", ctypes.c_uint8)
    ]

class DEBUG_CAP(ctypes.Structure):
    _fields_ = [
        ("log_max_samples", ctypes.c_uint8),
        ("log_min_resource_dump_eq", ctypes.c_uint8),
        ("resource_dump", ctypes.c_uint8),
        ("log_cr_dump_to_mem_size", ctypes.c_uint8),
        ("core_dump_qp", ctypes.c_uint8),
        ("core_dump_general", ctypes.c_uint8),
        ("log_min_sample_period", ctypes.c_uint8),
        ("diag_counter_tracer_dump", ctypes.c_uint8),
        ("health_mon_rx_activity", ctypes.c_uint8),
        ("repetitive", ctypes.c_uint8),
        ("single", ctypes.c_uint8),
        ("diagnostic_counter", DIAGNOSTIC_CNTR_LAYOUT)
    ]

class DEFAULT_TIMEOUT_EXT(ctypes.Structure):
    _fields_ = [
        ("to_value", ctypes.c_uint32),
        ("to_multiplier", ctypes.c_uint8)
    ]

class DTOR_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("PCIE_TOGGLE_TO", DEFAULT_TIMEOUT_EXT),
        ("HEALTH_POLL_TO", DEFAULT_TIMEOUT_EXT),
        ("FULL_CRDUMP_TO", DEFAULT_TIMEOUT_EXT),
        ("FW_RESET_TO", DEFAULT_TIMEOUT_EXT),
        ("FLUSH_ON_ERR_TO", DEFAULT_TIMEOUT_EXT),
        ("PCI_SYNC_UPDATE_TO", DEFAULT_TIMEOUT_EXT),
        ("TEAR_DOWN_TO", DEFAULT_TIMEOUT_EXT),
        ("FSM_REACTIVATE_TO", DEFAULT_TIMEOUT_EXT),
        ("RECLAIM_PAGES_TO", DEFAULT_TIMEOUT_EXT),
        ("RECLAIM_VFS_PAGES_TO", DEFAULT_TIMEOUT_EXT),
        ("DRIVER_UNLOAD_AND_RESET_TO", DEFAULT_TIMEOUT_EXT),
        ("EMBEDDED_CPU_OS_SHUTDOWN_TO", DEFAULT_TIMEOUT_EXT)
    ]

class PCNR_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("tuning_override", ctypes.c_uint8),
        ("flua_cap", ctypes.c_uint8),
        ("flua_we_mask", ctypes.c_uint8),
        ("lp_msb", ctypes.c_uint8),
        ("local_port", ctypes.c_uint8),
        ("keep_phy_setting", ctypes.c_uint8),
        ("flua_en", ctypes.c_uint8),
        ("flua_oper", ctypes.c_uint8),
        ("flua_allowed_ber", ctypes.c_uint8),
        ("flua_polling_sec", ctypes.c_uint8),
        ("flua_guar_sec", ctypes.c_uint8)
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
        ("tracer_capabilities", ctypes.c_uint8),
        ("string_db_param", STRING_DB_PARAMETERS_EXT * 8)
    ]

class MTIM_EXT(ctypes.Structure):
    _fields_ = [
        ("log_level", ctypes.c_uint8),
        ("log_bit_mask", ctypes.c_uint32)
    ]

class MGIR_HARDWARE_INFO_EXT(ctypes.Structure):
    _fields_ = [
        ("device_id", ctypes.c_uint16),
        ("device_hw_revision", ctypes.c_uint16),
        ("pvs", ctypes.c_uint8),
        ("technology", ctypes.c_uint8),
        ("num_ports", ctypes.c_uint16),
        ("ib_mad_gen", ctypes.c_uint8),
        ("hw_dev_id", ctypes.c_uint16),
        ("module_master_fw_default", ctypes.c_uint8),
        ("cpo_indication", ctypes.c_uint8),
        ("ga_valid", ctypes.c_uint8),
        ("development", ctypes.c_uint8),
        ("pci_switch_only_mode", ctypes.c_uint8),
        ("manufacturing_base_mac_47_32", ctypes.c_uint16),
        ("ga", ctypes.c_uint8),
        ("chip_type", ctypes.c_uint8),
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
        ("encryption", ctypes.c_uint8),
        ("life_cycle_msb", ctypes.c_uint8),
        ("dev_state", ctypes.c_uint8),
        ("issu_able", ctypes.c_uint8),
        ("pds", ctypes.c_uint8),
        ("ec_offload_engine_disabled", ctypes.c_uint8),
        ("dev_counter", ctypes.c_uint8)
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

class MFRL_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("reset_trigger", ctypes.c_uint8),
        ("reset_type", ctypes.c_uint8),
        ("reset_state", ctypes.c_uint8),
        ("pci_reset_req_method", ctypes.c_uint8),
        ("rst_type_sel", ctypes.c_uint8),
        ("pci_sync_for_fw_update_resp", ctypes.c_uint8),
        ("pci_sync_for_fw_update_start", ctypes.c_uint8),
        ("pci_rescan_required", ctypes.c_uint8)
    ]

class MPCIR_EXT(ctypes.Structure):
    _fields_ = [
        ("instance", ctypes.c_uint16),
        ("fw_entity", ctypes.c_uint8),
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

class MTEIM_REG_EXT(ctypes.Structure):
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

class NIC_DPA_EUG_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("eug_id", ctypes.c_uint16),
        ("partition_id_valid", ctypes.c_uint8),
        ("operation", ctypes.c_uint8),
        ("modify_field_select", ctypes.c_uint32),
        ("partition_id", ctypes.c_uint16),
        ("eug_name", ctypes.c_uint32 * 4),
        ("member_mask", ctypes.c_uint32 * 32)
    ]

class NIC_DPA_PERF_CTRL_REG_EXT(ctypes.Structure):
    _fields_ = [
        ("dpa_process_id", ctypes.c_uint32),
        ("other_vhca_id", ctypes.c_uint16),
        ("sample_type", ctypes.c_uint8),
        ("other_vhca_id_valid", ctypes.c_uint8),
        ("count_state", ctypes.c_uint8)
    ]

class NIC_CAP_EXT_DPA_CAP(ctypes.Structure):
    _fields_ = [
        ("max_num_dpa_eug", ctypes.c_uint16),
        ("max_num_dpa_eu", ctypes.c_uint16),
        ("max_num_dpa_eu_partition", ctypes.c_uint16),
        ("max_num_dpa_eu_per_group", ctypes.c_uint16),
        ("dpa_perf_sample_type", ctypes.c_uint8),
        ("max_num_partition_vhca_id", ctypes.c_uint16),
        ("nic_dpa_self_host_app_mgmt", ctypes.c_uint8),
        ("dpa_partition_eug", ctypes.c_uint8),
        ("process_perf_cnt", ctypes.c_uint8)
    ]

class NIC_CAP_EXT_DIAG_DATA_CAP(ctypes.Structure):
    _fields_ = [
        ("producer_sample_id", ctypes.c_uint8),
        ("sample_mode_on_demand", ctypes.c_uint8),
        ("sample_mode_repetitive", ctypes.c_uint8),
        ("sample_mode_single", ctypes.c_uint8),
        ("tracer_dump", ctypes.c_uint8),
        ("sync_start", ctypes.c_uint8),
        ("data_clear", ctypes.c_uint8),
        ("max_log_num_sample", ctypes.c_uint8),
        ("log_max_num_data_id", ctypes.c_uint8),
        ("data_timestamp_source", ctypes.c_uint8),
        ("diag_data_domain_max", ctypes.c_uint8)
    ]

class NIC_CAP_EXT_REG_CAP_DATA_AUTO(ctypes.Union):
    _fields_ = [
        ("nic_cap_ext_dpa_cap", NIC_CAP_EXT_DPA_CAP),
        ("nic_cap_ext_diag_data_cap", NIC_CAP_EXT_DIAG_DATA_CAP)
    ]

class NIC_CAP_EXT_REG(ctypes.Structure):
    _fields_ = [
        ("cap_group", ctypes.c_uint16),
        ("cap_data", NIC_CAP_EXT_REG_CAP_DATA_AUTO)
    ]

class MROQ_EXT(ctypes.Structure):
    _fields_ = [
        ("reset_trigger", ctypes.c_uint8),
        ("reset_type", ctypes.c_uint8),
        ("query_is_valid", ctypes.c_uint8),
        ("pci_sync_for_fw_update_start", ctypes.c_uint8),
        ("pci_reset_req_method", ctypes.c_uint8)
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

