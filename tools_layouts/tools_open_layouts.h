
/* Copyright (c) 2013-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef TOOLS_OPEN_LAYOUTS_H
#define TOOLS_OPEN_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 4 */
struct tools_open_bmc_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.12 */
	u_int16_t param_idx;
	/* Description -  */
	/* 0x0.13 - 0x0.17 */
	u_int8_t channel;
	/* Description -  */
	/* 0x0.18 - 0x0.23 */
	u_int8_t host;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_configuration_item_type_class_module {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.13 */
	u_int16_t parameter_index;
	/* Description - Module Index */
	/* 0x0.14 - 0x0.23 */
	u_int16_t module_index;
	/* Description - type_class = 0x9 */
	/* 0x0.24 - 0x0.31 */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_eswitch_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t param_idx;
	/* Description -  */
	/* 0x0.16 - 0x0.17 */
	u_int8_t port;
	/* Description -  */
	/* 0x0.18 - 0x0.23 */
	u_int8_t host;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_global_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	u_int32_t param_idx;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_host_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.17 */
	u_int32_t param_idx;
	/* Description -  */
	/* 0x0.18 - 0x0.23 */
	u_int8_t host;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_per_host_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.9 */
	u_int16_t param_idx;
	/* Description -  */
	/* 0x0.10 - 0x0.17 */
	u_int8_t function;
	/* Description -  */
	/* 0x0.18 - 0x0.23 */
	u_int8_t host;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_per_port_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t param_idx;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t port;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t param_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_tlv_type_dw {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t tlv_type_dw;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_fw_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - fw_version_major */
	/* 0x0.16 - 0x0.31 */
	u_int16_t fw_ver_major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - fw version subminor */
	/* 0x4.0 - 0x4.15 */
	u_int16_t fw_ver_subminor;
	/* Description - fw_version_minor */
	/* 0x4.16 - 0x4.31 */
	u_int16_t fw_ver_minor;
};

/* Description -   */
/* Size in bytes - 4 */
union tools_open_tlv_type {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_global_type global;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_eswitch_type eswitch;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_per_host_type per_host;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_bmc_type bmc;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_per_port_type per_port;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_configuration_item_type_class_module per_module;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_host_type host;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_tlv_type_dw tlv_type_dw;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_ts_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Timestamp day     - 2 packed BCD */
	/* 0x0.0 - 0x0.7 */
	u_int8_t ts_day;
	/* Description - Timestamp month   - 2 packed BCD */
	/* 0x0.8 - 0x0.15 */
	u_int8_t ts_month;
	/* Description - Timestamp year    - 4 packed BCD */
	/* 0x0.16 - 0x0.31 */
	u_int16_t ts_year;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Timestamp seconds - 2 packed BCD */
	/* 0x4.8 - 0x4.15 */
	u_int8_t ts_seconds;
	/* Description - Timestamp minotes - 2 packed BCD */
	/* 0x4.16 - 0x4.23 */
	u_int8_t ts_minutes;
	/* Description - Timestamp hour    - 2 packed BCD */
	/* 0x4.24 - 0x4.31 */
	u_int8_t ts_hour;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_nv_hdr_fifth_gen {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Size of configuration item data in bytes between 0..256 */
	/* 0x0.0 - 0x0.8 */
	u_int16_t length;
	/* Description - tlv writer host index */
	/* 0x0.9 - 0x0.11 */
	u_int8_t writer_host_id;
	/* Description - Configuration item version */
	/* 0x0.12 - 0x0.15 */
	u_int8_t version;
	/* Description - Writer ID */
	/* 0x0.16 - 0x0.20 */
	u_int8_t writer_id;
	/* Description - Choose - read current values or user defined values: 0x0 - u ser defined values
 0x1 - current values ( values that are loaded in last boot)
 */
	/* 0x0.22 - 0x0.22 */
	u_int8_t read_current;
	/* Description - when set in query , will display the default configuration */
	/* 0x0.23 - 0x0.23 */
	u_int8_t default_;
	/* Description - enables reading the TLV by lower priorities
0 - TLV can be read by the subsequent lifecycle priorities.
1 - TLV cannot be read by the subsequent lifecycle priorities.
 */
	/* 0x0.24 - 0x0.24 */
	u_int8_t rd_en;
	/* Description - enables overwriting the TLV by lower priorities

0 - Can only be overwritten by the current lifecycle priority
1 - Allowed to be overwritten by subsequent lifecycle priorities
 */
	/* 0x0.25 - 0x0.25 */
	u_int8_t over_en;

/*The priority is set by either:
1. When using MNVDA, the TLV will have user priority
2. When using NVCONFIG, each TLV has its own priority */
	/* 0x0.28 - 0x0.29 */
	u_int8_t priority;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	union tools_open_tlv_type type;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_timestamp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - fw_version */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_fw_version fw_version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Timestamp */
	/* 0x8.0 - 0xc.31 */
	struct tools_open_ts_entry ts_entry;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_aux_tlv_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t minor_version;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	u_int8_t major_version;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t type;
	/* Description -  */
	/* 0x0.28 - 0x0.31 */
	u_int8_t header_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t length;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	u_int16_t crc;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t reserved0;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t reserved1;
};

/* Description -   */
/* Size in bytes - 172 */
struct tools_open_mgnle {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Pointer to the log entry (see description above for more 
information) */
	/* 0x0.0 - 0x0.31 */
	u_int32_t le_pointer;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The number of events that the system failed to log since the 
previous log entry.
15 should be interpreted as '15 or more events were lost' */
	/* 0x4.24 - 0x4.27 */
	u_int8_t lost_events;
	/* Description - 0x0: Boot - time is measured since NIC bootup.
0x1: Synced - time was synced by the host. */
	/* 0x4.31 - 0x4.31 */
	u_int8_t synced_time;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The 32 MSB of the 64bit timestamp. In microseconds
When "time_synced" bit is set this is the time passed since the 
1/1/1970 epoch.
When "time_synced" is cleared this is the NIC uptime. */
	/* 0x8.0 - 0x8.31 */
	u_int32_t time_h;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The 32 LSB of the 64bit timestamp. In microseconds */
	/* 0xc.0 - 0xc.31 */
	u_int32_t time_l;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x18.31 */
	struct tools_open_nv_hdr_fifth_gen nv_hdr;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.24 - 0xac.23 */
	u_int8_t log_data[128];
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_mlock {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - operation: 0  unlocked, 1  locked, other  RESERVED.  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t operation;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Key */
	/* 0x8.0 - 0xc.31 */
	u_int64_t key;
};

/* Description -   */
/* Size in bytes - 268 */
struct tools_open_mnvda {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_nv_hdr_fifth_gen nv_hdr;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.24 - 0x10c.23 */
	u_int8_t data[256];
};

/* Description -   */
/* Size in bytes - 156 */
struct tools_open_mnvgn {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Pointer to the NV parameter */
	/* 0x0.0 - 0x0.31 */
	u_int32_t nv_pointer;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x18.31 */
	struct tools_open_nv_hdr_fifth_gen nv_hdr;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.24 - 0x9c.23 */
	u_int8_t nv_data[128];
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_mvts {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - A SET operation with this flag set will only check if the new timestamp can be configured without upda ting NVRAM */
	/* 0x0.29 - 0x0.29 */
	u_int8_t check_timestamp_flag;
	/* Description - A GET operation with this flag set, will return the running FW version instead */
	/* 0x0.30 - 0x0.30 */
	u_int8_t running_flag;
	/* Description - A SET operation with this flag on will clear the running and other bank timestamps */
	/* 0x0.31 - 0x0.31 */
	u_int8_t clear_all_ts_flag;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Timestamp entry */
	/* 0x4.0 - 0x10.31 */
	struct tools_open_timestamp timestamp;
};

/* Description -   */
/* Size in bytes - 256 */
struct tools_open_aux_tlv {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct tools_open_aux_tlv_header aux_tlv_header;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - tlv data */
	/* 0x14.24 - 0x94.23 */
	u_int8_t data[128];
};

/* Description -   */
/* Size in bytes - 1024 */
struct tools_open_image_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IMAGE_INFO section minor version */
	/* 0x0.16 - 0x0.23 */
	u_int8_t minor_version;
	/* Description - IMAGE_INFO section major version */
	/* 0x0.24 - 0x0.31 */
	u_int8_t major_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.24 - 0x34.23 */
	char psid[17];
/*---------------- DWORD[116] (Offset 0x1d0) ----------------*/
	/* Description - Product description */
	/* 0x1d0.24 - 0x2d0.23 */
	char description[257];
/*---------------- DWORD[208] (Offset 0x340) ----------------*/
	/* Description - Product name */
	/* 0x340.24 - 0x380.23 */
	char name[65];
/*---------------- DWORD[224] (Offset 0x380) ----------------*/
	/* Description - PRS used to generate the FW binary */
	/* 0x380.24 - 0x3e0.23 */
	char prs_name[97];
};

/* Description -   */
/* Size in bytes - 320 */
struct tools_open_mfg_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	char psid[17];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - MFG_INFO section minor version */
	/* 0x1c.16 - 0x1c.23 */
	u_int8_t minor_version;
	/* Description - MFG_INFO section major version */
	/* 0x1c.24 - 0x1c.31 */
	u_int8_t major_version;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - original PRS used to generate the FW binary */
	/* 0x60.24 - 0xc0.23 */
	char orig_prs_name[97];
};

/* Description -   */
/* Size in bytes - 364 */
union tools_open_mnv_cfg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct tools_open_mvts mvts;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_mlock mlock;
	/* Description -  */
	/* 0x0.0 - 0x108.31 */
	struct tools_open_mnvda mnvda;
	/* Description -  */
	/* 0x0.0 - 0x98.31 */
	struct tools_open_mnvgn mnvgn;
	/* Description -  */
	/* 0x0.0 - 0xa8.31 */
	struct tools_open_mgnle mgnle;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_nv_base_mac_guid {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int32_t base_mac[2];
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	u_int32_t base_guid[2];
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_nv_base_mac_guid_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.30 - 0x0.30 */
	u_int8_t guid_en;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	u_int8_t mac_en;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	u_int16_t num_of_allocated_macs;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t num_of_allocated_guids;
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_query_def_params_global {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, indicating mapping of internal clock to user space can be configured by CX3_GLOBAL_CONF.clock_map_to_user */
	/* 0x0.14 - 0x0.14 */
	u_int8_t nv_config_clock_map_to_user;
	/* Description - When set, PHY parameters mode can be configured by GLOBAL_CONF.phy_param_mode */
	/* 0x0.15 - 0x0.15 */
	u_int8_t nv_config_phy_param_mode;
	/* Description - When set, CX3_GLOBAL_CONF.steer_force_vlan bit is supported */
	/* 0x0.16 - 0x0.16 */
	u_int8_t nv_steer_force_vlan_supported;
	/* Description - When set, CX3_GLOBAL_CONF.cq_timestamp bit is supported */
	/* 0x0.17 - 0x0.17 */
	u_int8_t nv_cq_timestamp_supported;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t fw_default_config_payload_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - default number of virtual functions */
	/* 0x4.0 - 0x4.7 */
	u_int8_t num_vfs;
	/* Description - default uar bar size (log2 format) */
	/* 0x4.8 - 0x4.11 */
	u_int8_t uar_bar_size;
	/* Description - maximum value allowed for the uar bar size (log2 base) */
	/* 0x4.12 - 0x4.15 */
	u_int8_t max_uar_bar_size;
	/* Description -  */
	/* 0x4.21 - 0x4.21 */
	u_int8_t boot_ip_ver;
	/* Description - default value of phy_param_mode in GLOBAL_CONF */
	/* 0x4.22 - 0x4.23 */
	u_int8_t default_phy_param_mode;
	/* Description - default value for clock_map_to_user in CX3_GLOBAL_CONF */
	/* 0x4.27 - 0x4.27 */
	u_int8_t default_clock_map_to_user;
	/* Description - The value reported by QUERY_DEV_CAP.steer_force_vlan when a CX3_GLOBAL_CONF TLV is not present */
	/* 0x4.28 - 0x4.28 */
	u_int8_t default_steer_force_vlan;
	/* Description - The value reported by QUERY_DEV_CAP.cq_timestamp when a CX3_GLOBAL_CONF TLV is not present */
	/* 0x4.29 - 0x4.29 */
	u_int8_t default_cq_timestamp;
	/* Description - default value of sriov (enabled or disabled) */
	/* 0x4.31 - 0x4.31 */
	u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 28 */
struct tools_open_query_def_params_per_port {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.17 - 0x0.17 */
	u_int8_t nv_config_vpi_force_mode;
	/* Description - Firmware supports NV config settings 0x12 on the given port. */
	/* 0x0.18 - 0x0.18 */
	u_int8_t nv_config_vpi;
	/* Description - Firmware supports NV config settings 0x10 on the given port. */
	/* 0x0.19 - 0x0.19 */
	u_int8_t nv_config_wol;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t fw_default_config_payload_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.11 */
	u_int16_t default_boot_vlan;
	/* Description -  */
	/* 0x4.16 - 0x4.19 */
	u_int8_t default_boot_protocol;
	/* Description -  */
	/* 0x4.20 - 0x4.23 */
	u_int8_t default_boot_retry_cnt;
	/* Description -  */
	/* 0x4.25 - 0x4.26 */
	u_int8_t default_network_link_type;
	/* Description -  */
	/* 0x4.27 - 0x4.27 */
	u_int8_t default_en_wol_magic;
	/* Description -  */
	/* 0x4.28 - 0x4.28 */
	u_int8_t default_boot_vlan_en;
	/* Description -  */
	/* 0x4.29 - 0x4.29 */
	u_int8_t default_boot_option_rom_en;
	/* Description -  */
	/* 0x4.30 - 0x4.30 */
	u_int8_t default_pprx;
	/* Description -  */
	/* 0x4.31 - 0x4.31 */
	u_int8_t default_pptx;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	u_int16_t default_boot_pkey;
	/* Description -  */
	/* 0x8.24 - 0x8.25 */
	u_int8_t boot_ip_ver;
	/* Description - Legacy option ROM supports NV config setting 0x2023. */
	/* 0x8.27 - 0x8.27 */
	u_int8_t nv_config_infiniband_dhcp_settings;
	/* Description - Legacy option ROM supports NV config setting 0x2022. */
	/* 0x8.28 - 0x8.28 */
	u_int8_t nv_config_infiniband_boot_settings;
	/* Description -  */
	/* 0x8.29 - 0x8.29 */
	u_int8_t nv_config_dhcp_iscsi_parameters;
	/* Description -  */
	/* 0x8.30 - 0x8.30 */
	u_int8_t nv_config_iscsi_parameters;
	/* Description -  */
	/* 0x8.31 - 0x8.31 */
	u_int8_t nv_config_boot_parameters;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.9 - 0xc.9 */
	u_int8_t default_vpi_force_mode;
	/* Description -  */
	/* 0xc.10 - 0xc.11 */
	u_int8_t default_vpi_xfi_mode;
	/* Description -  */
	/* 0xc.12 - 0xc.13 */
	u_int8_t default_vpi_phy_type;
	/* Description -  */
	/* 0xc.22 - 0xc.23 */
	u_int8_t iscsi_boot_to_target;
	/* Description -  */
	/* 0xc.26 - 0xc.26 */
	u_int8_t iscsi_vlan_en;
	/* Description -  */
	/* 0xc.27 - 0xc.27 */
	u_int8_t iscsi_tcp_timestamps_en;
	/* Description -  */
	/* 0xc.28 - 0xc.28 */
	u_int8_t iscsi_chap_mutual_auth_en;
	/* Description -  */
	/* 0xc.29 - 0xc.29 */
	u_int8_t iscsi_chap_auth_en;
	/* Description -  */
	/* 0xc.30 - 0xc.30 */
	u_int8_t iscsi_dhcp_params_en;
	/* Description -  */
	/* 0xc.31 - 0xc.31 */
	u_int8_t iscsi_ipv4_dhcp_en;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.7 */
	u_int8_t iscsi_lun_busy_retry_cnt;
	/* Description -  */
	/* 0x10.8 - 0x10.15 */
	u_int8_t iscsi_link_up_delay_time;
};

/* Description -   */
/* Size in bytes - 512 */
union tools_open_access_registers {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Misc NV Registers, this is temporary untill we integrate with fw db */
	/* 0x0.0 - 0x168.31 */
	union tools_open_mnv_cfg MNVReg;
};

/* Description -   */
/* Size in bytes - 256 */
union tools_open_aux_img_data {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - image tlv entry */
	/* 0x0.0 - 0xfc.31 */
	struct tools_open_aux_tlv aux_tlv;
};

/* Description -   */
/* Size in bytes - 264 */
union tools_open_hcr_cmds {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct tools_open_query_def_params_global query_def_params_global;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct tools_open_query_def_params_per_port query_def_params_per_port;
};

/* Description -   */
/* Size in bytes - 36 */
struct tools_open_mcdd_descriptor {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Update handle registered when the FSM was activated. */
	/* 0x0.0 - 0x0.23 */
	u_int32_t update_handle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Offset of accessed address relative to component start. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the data accessed, given in bytes */
	/* 0x8.0 - 0x8.15 */
	u_int16_t size;
	/* Description - Reserved */
	/* 0x8.16 - 0x8.31 */
	u_int16_t reserved1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Reserved */
	/* 0xc.0 - 0xc.31 */
	u_int32_t reserved2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x10.0 - 0x10.31 */
	u_int32_t data_page_phys_addr_msb;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x14.0 - 0x14.31 */
	u_int32_t data_page_phys_addr_lsb;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x18.0 - 0x18.31 */
	u_int32_t mailbox_page_phys_addr_msb;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t mailbox_page_phys_addr_lsb;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Status of current operation that FW sends to host. */
	/* 0x20.0 - 0x20.7 */
	u_int8_t status;
	/* Description - Last error index, if occured. */
	/* 0x20.8 - 0x20.15 */
	u_int8_t error;
	/* Description - Reserved. */
	/* 0x20.16 - 0x20.31 */
	u_int16_t reserved3;
};

/* Description -   */
/* Size in bytes - 32 */
struct tools_open_mcdd_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Update handle registered when the FSM was activated. */
	/* 0x0.0 - 0x0.23 */
	u_int32_t update_handle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Offset of accessed address relative to component start. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the data accessed, given in bytes */
	/* 0x8.0 - 0x8.15 */
	u_int16_t size;
	/* Description - Reserved */
	/* 0x8.16 - 0x8.31 */
	u_int16_t reserved1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Reserved */
	/* 0xc.0 - 0xc.31 */
	u_int32_t reserved2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x10.0 - 0x10.31 */
	u_int32_t data_page_phys_addr_msb;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x14.0 - 0x14.31 */
	u_int32_t data_page_phys_addr_lsb;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x18.0 - 0x18.31 */
	u_int32_t mailbox_page_phys_addr_msb;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Physical address of the FW component data page */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t mailbox_page_phys_addr_lsb;
};

/* Description -  MIRC register */
/* Size in bytes - 8 */
struct tools_open_mirc_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Statuses: 0  success, 1  busy, etc.  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t status_code;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t reserved;
};

/* Description -   */
/* Size in bytes - 1024 */
union tools_open_misc_structs {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3fc.31 */
	struct tools_open_image_info image_info;
	/* Description -  */
	/* 0x0.0 - 0x13c.31 */
	struct tools_open_mfg_info mfg_info;
};

/* Description -   */
/* Size in bytes - 256 */
union tools_open_nv_cfg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_nv_base_mac_guid nv_base_mac_guid;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nv_base_mac_guid_cap nv_base_mac_guid_cap;
};

/* Description -   */
/* Size in bytes - 1048576 */
union tools_open_tools_open {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Non-Volatile Cfg Tlvs */
	/* 0x0.0 - 0xfc.31 */
	union tools_open_nv_cfg NVConfig;
	/* Description - various registers in specific use by the tools */
	/* 0x0.0 - 0x1fc.31 */
	union tools_open_access_registers AceessRegisters;
	/* Description - Tools HCR commands structs */
	/* 0x0.0 - 0x104.31 */
	union tools_open_hcr_cmds HcrCmds;
	/* Description - aux image data layout */
	/* 0x0.0 - 0xfc.31 */
	union tools_open_aux_img_data AuxImgData;
	/* Description - Misc structs needed for integration on new FW features */
	/* 0x0.0 - 0x3fc.31 */
	union tools_open_misc_structs MiscStructs;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_mcdd_reg mcdd_reg;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	struct tools_open_mcdd_descriptor mcdd_descriptor;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_mirc_reg mirc_reg;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* bmc_type */
void tools_open_bmc_type_pack(const struct tools_open_bmc_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_bmc_type_unpack(struct tools_open_bmc_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_bmc_type_print(const struct tools_open_bmc_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_bmc_type_size(void);
#define TOOLS_OPEN_BMC_TYPE_SIZE    (0x4)
void tools_open_bmc_type_dump(const struct tools_open_bmc_type *ptr_struct, FILE *fd);
/* configuration_item_type_class_module */
void tools_open_configuration_item_type_class_module_pack(const struct tools_open_configuration_item_type_class_module *ptr_struct, u_int8_t *ptr_buff);
void tools_open_configuration_item_type_class_module_unpack(struct tools_open_configuration_item_type_class_module *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_configuration_item_type_class_module_print(const struct tools_open_configuration_item_type_class_module *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_configuration_item_type_class_module_size(void);
#define TOOLS_OPEN_CONFIGURATION_ITEM_TYPE_CLASS_MODULE_SIZE    (0x4)
void tools_open_configuration_item_type_class_module_dump(const struct tools_open_configuration_item_type_class_module *ptr_struct, FILE *fd);
/* eswitch_type */
void tools_open_eswitch_type_pack(const struct tools_open_eswitch_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_eswitch_type_unpack(struct tools_open_eswitch_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_eswitch_type_print(const struct tools_open_eswitch_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_eswitch_type_size(void);
#define TOOLS_OPEN_ESWITCH_TYPE_SIZE    (0x4)
void tools_open_eswitch_type_dump(const struct tools_open_eswitch_type *ptr_struct, FILE *fd);
/* global_type */
void tools_open_global_type_pack(const struct tools_open_global_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_global_type_unpack(struct tools_open_global_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_global_type_print(const struct tools_open_global_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_global_type_size(void);
#define TOOLS_OPEN_GLOBAL_TYPE_SIZE    (0x4)
void tools_open_global_type_dump(const struct tools_open_global_type *ptr_struct, FILE *fd);
/* host_type */
void tools_open_host_type_pack(const struct tools_open_host_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_host_type_unpack(struct tools_open_host_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_host_type_print(const struct tools_open_host_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_host_type_size(void);
#define TOOLS_OPEN_HOST_TYPE_SIZE    (0x4)
void tools_open_host_type_dump(const struct tools_open_host_type *ptr_struct, FILE *fd);
/* per_host_type */
void tools_open_per_host_type_pack(const struct tools_open_per_host_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_per_host_type_unpack(struct tools_open_per_host_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_per_host_type_print(const struct tools_open_per_host_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_per_host_type_size(void);
#define TOOLS_OPEN_PER_HOST_TYPE_SIZE    (0x4)
void tools_open_per_host_type_dump(const struct tools_open_per_host_type *ptr_struct, FILE *fd);
/* per_port_type */
void tools_open_per_port_type_pack(const struct tools_open_per_port_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_per_port_type_unpack(struct tools_open_per_port_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_per_port_type_print(const struct tools_open_per_port_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_per_port_type_size(void);
#define TOOLS_OPEN_PER_PORT_TYPE_SIZE    (0x4)
void tools_open_per_port_type_dump(const struct tools_open_per_port_type *ptr_struct, FILE *fd);
/* tlv_type_dw */
void tools_open_tlv_type_dw_pack(const struct tools_open_tlv_type_dw *ptr_struct, u_int8_t *ptr_buff);
void tools_open_tlv_type_dw_unpack(struct tools_open_tlv_type_dw *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_tlv_type_dw_print(const struct tools_open_tlv_type_dw *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_tlv_type_dw_size(void);
#define TOOLS_OPEN_TLV_TYPE_DW_SIZE    (0x4)
void tools_open_tlv_type_dw_dump(const struct tools_open_tlv_type_dw *ptr_struct, FILE *fd);
/* fw_version */
void tools_open_fw_version_pack(const struct tools_open_fw_version *ptr_struct, u_int8_t *ptr_buff);
void tools_open_fw_version_unpack(struct tools_open_fw_version *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_fw_version_print(const struct tools_open_fw_version *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_fw_version_size(void);
#define TOOLS_OPEN_FW_VERSION_SIZE    (0x8)
void tools_open_fw_version_dump(const struct tools_open_fw_version *ptr_struct, FILE *fd);
/* tlv_type */
void tools_open_tlv_type_pack(const union tools_open_tlv_type *ptr_struct, u_int8_t *ptr_buff);
void tools_open_tlv_type_unpack(union tools_open_tlv_type *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_tlv_type_print(const union tools_open_tlv_type *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_tlv_type_size(void);
#define TOOLS_OPEN_TLV_TYPE_SIZE    (0x4)
void tools_open_tlv_type_dump(const union tools_open_tlv_type *ptr_struct, FILE *fd);
/* ts_entry */
void tools_open_ts_entry_pack(const struct tools_open_ts_entry *ptr_struct, u_int8_t *ptr_buff);
void tools_open_ts_entry_unpack(struct tools_open_ts_entry *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_ts_entry_print(const struct tools_open_ts_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_ts_entry_size(void);
#define TOOLS_OPEN_TS_ENTRY_SIZE    (0x8)
void tools_open_ts_entry_dump(const struct tools_open_ts_entry *ptr_struct, FILE *fd);
/* nv_hdr_fifth_gen */
void tools_open_nv_hdr_fifth_gen_pack(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_hdr_fifth_gen_unpack(struct tools_open_nv_hdr_fifth_gen *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_hdr_fifth_gen_print(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_hdr_fifth_gen_size(void);
#define TOOLS_OPEN_NV_HDR_FIFTH_GEN_SIZE    (0xc)
void tools_open_nv_hdr_fifth_gen_dump(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd);
/* timestamp */
void tools_open_timestamp_pack(const struct tools_open_timestamp *ptr_struct, u_int8_t *ptr_buff);
void tools_open_timestamp_unpack(struct tools_open_timestamp *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_timestamp_print(const struct tools_open_timestamp *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_timestamp_size(void);
#define TOOLS_OPEN_TIMESTAMP_SIZE    (0x10)
void tools_open_timestamp_dump(const struct tools_open_timestamp *ptr_struct, FILE *fd);
/* uint64 */
void tools_open_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void tools_open_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_uint64_size(void);
#define TOOLS_OPEN_UINT64_SIZE    (0x8)
void tools_open_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* aux_tlv_header */
void tools_open_aux_tlv_header_pack(const struct tools_open_aux_tlv_header *ptr_struct, u_int8_t *ptr_buff);
void tools_open_aux_tlv_header_unpack(struct tools_open_aux_tlv_header *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_aux_tlv_header_print(const struct tools_open_aux_tlv_header *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_aux_tlv_header_size(void);
#define TOOLS_OPEN_AUX_TLV_HEADER_SIZE    (0x14)
void tools_open_aux_tlv_header_dump(const struct tools_open_aux_tlv_header *ptr_struct, FILE *fd);
/* mgnle */
void tools_open_mgnle_pack(const struct tools_open_mgnle *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mgnle_unpack(struct tools_open_mgnle *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mgnle_print(const struct tools_open_mgnle *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mgnle_size(void);
#define TOOLS_OPEN_MGNLE_SIZE    (0xac)
void tools_open_mgnle_dump(const struct tools_open_mgnle *ptr_struct, FILE *fd);
/* mlock */
void tools_open_mlock_pack(const struct tools_open_mlock *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mlock_unpack(struct tools_open_mlock *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mlock_print(const struct tools_open_mlock *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mlock_size(void);
#define TOOLS_OPEN_MLOCK_SIZE    (0x10)
void tools_open_mlock_dump(const struct tools_open_mlock *ptr_struct, FILE *fd);
/* mnvda */
void tools_open_mnvda_pack(const struct tools_open_mnvda *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnvda_unpack(struct tools_open_mnvda *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnvda_print(const struct tools_open_mnvda *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnvda_size(void);
#define TOOLS_OPEN_MNVDA_SIZE    (0x10c)
void tools_open_mnvda_dump(const struct tools_open_mnvda *ptr_struct, FILE *fd);
/* mnvgn */
void tools_open_mnvgn_pack(const struct tools_open_mnvgn *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnvgn_unpack(struct tools_open_mnvgn *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnvgn_print(const struct tools_open_mnvgn *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnvgn_size(void);
#define TOOLS_OPEN_MNVGN_SIZE    (0x9c)
void tools_open_mnvgn_dump(const struct tools_open_mnvgn *ptr_struct, FILE *fd);
/* mvts */
void tools_open_mvts_pack(const struct tools_open_mvts *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mvts_unpack(struct tools_open_mvts *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mvts_print(const struct tools_open_mvts *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mvts_size(void);
#define TOOLS_OPEN_MVTS_SIZE    (0x14)
void tools_open_mvts_dump(const struct tools_open_mvts *ptr_struct, FILE *fd);
/* aux_tlv */
void tools_open_aux_tlv_pack(const struct tools_open_aux_tlv *ptr_struct, u_int8_t *ptr_buff);
void tools_open_aux_tlv_unpack(struct tools_open_aux_tlv *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_aux_tlv_print(const struct tools_open_aux_tlv *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_aux_tlv_size(void);
#define TOOLS_OPEN_AUX_TLV_SIZE    (0x100)
void tools_open_aux_tlv_dump(const struct tools_open_aux_tlv *ptr_struct, FILE *fd);
/* image_info */
void tools_open_image_info_pack(const struct tools_open_image_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_image_info_unpack(struct tools_open_image_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_image_info_print(const struct tools_open_image_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_image_info_size(void);
#define TOOLS_OPEN_IMAGE_INFO_SIZE    (0x400)
void tools_open_image_info_dump(const struct tools_open_image_info *ptr_struct, FILE *fd);
/* mfg_info */
void tools_open_mfg_info_pack(const struct tools_open_mfg_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mfg_info_unpack(struct tools_open_mfg_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mfg_info_print(const struct tools_open_mfg_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mfg_info_size(void);
#define TOOLS_OPEN_MFG_INFO_SIZE    (0x140)
void tools_open_mfg_info_dump(const struct tools_open_mfg_info *ptr_struct, FILE *fd);
/* mnv_cfg */
void tools_open_mnv_cfg_pack(const union tools_open_mnv_cfg *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnv_cfg_size(void);
#define TOOLS_OPEN_MNV_CFG_SIZE    (0x16c)
void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE *fd);
/* nv_base_mac_guid */
void tools_open_nv_base_mac_guid_pack(const struct tools_open_nv_base_mac_guid *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_base_mac_guid_unpack(struct tools_open_nv_base_mac_guid *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_base_mac_guid_print(const struct tools_open_nv_base_mac_guid *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_base_mac_guid_size(void);
#define TOOLS_OPEN_NV_BASE_MAC_GUID_SIZE    (0x10)
void tools_open_nv_base_mac_guid_dump(const struct tools_open_nv_base_mac_guid *ptr_struct, FILE *fd);
/* nv_base_mac_guid_cap */
void tools_open_nv_base_mac_guid_cap_pack(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_base_mac_guid_cap_unpack(struct tools_open_nv_base_mac_guid_cap *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_base_mac_guid_cap_print(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_base_mac_guid_cap_size(void);
#define TOOLS_OPEN_NV_BASE_MAC_GUID_CAP_SIZE    (0x8)
void tools_open_nv_base_mac_guid_cap_dump(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, FILE *fd);
/* query_def_params_global */
void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t *ptr_buff);
void tools_open_query_def_params_global_unpack(struct tools_open_query_def_params_global *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_query_def_params_global_print(const struct tools_open_query_def_params_global *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_query_def_params_global_size(void);
#define TOOLS_OPEN_QUERY_DEF_PARAMS_GLOBAL_SIZE    (0x14)
void tools_open_query_def_params_global_dump(const struct tools_open_query_def_params_global *ptr_struct, FILE *fd);
/* query_def_params_per_port */
void tools_open_query_def_params_per_port_pack(const struct tools_open_query_def_params_per_port *ptr_struct, u_int8_t *ptr_buff);
void tools_open_query_def_params_per_port_unpack(struct tools_open_query_def_params_per_port *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_query_def_params_per_port_print(const struct tools_open_query_def_params_per_port *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_query_def_params_per_port_size(void);
#define TOOLS_OPEN_QUERY_DEF_PARAMS_PER_PORT_SIZE    (0x1c)
void tools_open_query_def_params_per_port_dump(const struct tools_open_query_def_params_per_port *ptr_struct, FILE *fd);
/* access_registers */
void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t *ptr_buff);
void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_access_registers_size(void);
#define TOOLS_OPEN_ACCESS_REGISTERS_SIZE    (0x200)
void tools_open_access_registers_dump(const union tools_open_access_registers *ptr_struct, FILE *fd);
/* aux_img_data */
void tools_open_aux_img_data_pack(const union tools_open_aux_img_data *ptr_struct, u_int8_t *ptr_buff);
void tools_open_aux_img_data_unpack(union tools_open_aux_img_data *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_aux_img_data_print(const union tools_open_aux_img_data *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_aux_img_data_size(void);
#define TOOLS_OPEN_AUX_IMG_DATA_SIZE    (0x100)
void tools_open_aux_img_data_dump(const union tools_open_aux_img_data *ptr_struct, FILE *fd);
/* hcr_cmds */
void tools_open_hcr_cmds_pack(const union tools_open_hcr_cmds *ptr_struct, u_int8_t *ptr_buff);
void tools_open_hcr_cmds_unpack(union tools_open_hcr_cmds *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_hcr_cmds_print(const union tools_open_hcr_cmds *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_hcr_cmds_size(void);
#define TOOLS_OPEN_HCR_CMDS_SIZE    (0x108)
void tools_open_hcr_cmds_dump(const union tools_open_hcr_cmds *ptr_struct, FILE *fd);
/* mcdd_descriptor */
void tools_open_mcdd_descriptor_pack(const struct tools_open_mcdd_descriptor *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mcdd_descriptor_unpack(struct tools_open_mcdd_descriptor *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mcdd_descriptor_print(const struct tools_open_mcdd_descriptor *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mcdd_descriptor_size(void);
#define TOOLS_OPEN_MCDD_DESCRIPTOR_SIZE    (0x24)
void tools_open_mcdd_descriptor_dump(const struct tools_open_mcdd_descriptor *ptr_struct, FILE *fd);
/* mcdd_reg */
void tools_open_mcdd_reg_pack(const struct tools_open_mcdd_reg *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mcdd_reg_unpack(struct tools_open_mcdd_reg *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mcdd_reg_print(const struct tools_open_mcdd_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mcdd_reg_size(void);
#define TOOLS_OPEN_MCDD_REG_SIZE    (0x20)
void tools_open_mcdd_reg_dump(const struct tools_open_mcdd_reg *ptr_struct, FILE *fd);
/* mirc_reg */
void tools_open_mirc_reg_pack(const struct tools_open_mirc_reg *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mirc_reg_unpack(struct tools_open_mirc_reg *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mirc_reg_print(const struct tools_open_mirc_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mirc_reg_size(void);
#define TOOLS_OPEN_MIRC_REG_SIZE    (0x8)
void tools_open_mirc_reg_dump(const struct tools_open_mirc_reg *ptr_struct, FILE *fd);
/* misc_structs */
void tools_open_misc_structs_pack(const union tools_open_misc_structs *ptr_struct, u_int8_t *ptr_buff);
void tools_open_misc_structs_unpack(union tools_open_misc_structs *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_misc_structs_print(const union tools_open_misc_structs *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_misc_structs_size(void);
#define TOOLS_OPEN_MISC_STRUCTS_SIZE    (0x400)
void tools_open_misc_structs_dump(const union tools_open_misc_structs *ptr_struct, FILE *fd);
/* nv_cfg */
void tools_open_nv_cfg_pack(const union tools_open_nv_cfg *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_cfg_size(void);
#define TOOLS_OPEN_NV_CFG_SIZE    (0x100)
void tools_open_nv_cfg_dump(const union tools_open_nv_cfg *ptr_struct, FILE *fd);
/* tools_open */
void tools_open_tools_open_pack(const union tools_open_tools_open *ptr_struct, u_int8_t *ptr_buff);
void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_tools_open_print(const union tools_open_tools_open *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_tools_open_size(void);
#define TOOLS_OPEN_TOOLS_OPEN_SIZE    (0x100000)
void tools_open_tools_open_dump(const union tools_open_tools_open *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // TOOLS_OPEN_LAYOUTS_H
