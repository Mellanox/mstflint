/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 

/***
         *** This file was generated at "2020-10-08 16:57:28"
         *** by:
         ***    > /mswg/release/tools/a-me/nightly/1.0.122/a-me-1.0.122_2019-07-14/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_
         ***/
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
/* Size in bytes - 4 */
struct tools_open_cap_mask {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	u_int8_t is_sm;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	u_int8_t is_notice_sup;
	/* Description -  */
	/* 0x0.3 - 0x0.3 */
	u_int8_t is_trap_sup;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	u_int8_t is_optional_ipd_sup;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	u_int8_t is_automatic_migration_sup;
	/* Description -  */
	/* 0x0.6 - 0x0.6 */
	u_int8_t is_sl_mapping_sup;
	/* Description -  */
	/* 0x0.7 - 0x0.7 */
	u_int8_t is_mkey_nvram;
	/* Description -  */
	/* 0x0.8 - 0x0.8 */
	u_int8_t is_pkey_nvram;
	/* Description -  */
	/* 0x0.9 - 0x0.9 */
	u_int8_t is_led_info_sup;
	/* Description -  */
	/* 0x0.10 - 0x0.10 */
	u_int8_t is_sm_disabled;
	/* Description -  */
	/* 0x0.11 - 0x0.11 */
	u_int8_t is_system_image_guid_sup;
	/* Description -  */
	/* 0x0.12 - 0x0.12 */
	u_int8_t is_pkey_switch_external_port_trap_sup;
	/* Description -  */
	/* 0x0.14 - 0x0.14 */
	u_int8_t is_extended_speed_sup;
	/* Description -  */
	/* 0x0.16 - 0x0.16 */
	u_int8_t is_communication_management_sup;
	/* Description -  */
	/* 0x0.17 - 0x0.17 */
	u_int8_t is_snmp_tunneling_sup;
	/* Description -  */
	/* 0x0.18 - 0x0.18 */
	u_int8_t is_reinit_sup;
	/* Description -  */
	/* 0x0.19 - 0x0.19 */
	u_int8_t is_device_management_sup;
	/* Description -  */
	/* 0x0.20 - 0x0.20 */
	u_int8_t is_vendor_class_sup;
	/* Description -  */
	/* 0x0.21 - 0x0.21 */
	u_int8_t is_dr_notice_sup;
	/* Description -  */
	/* 0x0.22 - 0x0.22 */
	u_int8_t is_capability_mask_notice_sup;
	/* Description -  */
	/* 0x0.23 - 0x0.23 */
	u_int8_t is_boot_management_sup;
	/* Description -  */
	/* 0x0.24 - 0x0.24 */
	u_int8_t is_link_round_trip_latency_sup;
	/* Description -  */
	/* 0x0.25 - 0x0.25 */
	u_int8_t is_client_reregistration_sup;
	/* Description -  */
	/* 0x0.26 - 0x0.26 */
	u_int8_t is_other_local_changes_notice_supported;
	/* Description -  */
	/* 0x0.27 - 0x0.27 */
	u_int8_t is_link_speed_width_pairs_table_supported;
};

/* Description -  CapabilityMaskSMP */
/* Size in bytes - 64 */
struct tools_open_capability_mask_smp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Attributes PrivateLFTInfo, PrivateLFTDef, PrivateLFTMap, PrivateLFT are all supported */
	/* 0x0.0 - 0x0.0 */
	u_int8_t IsPrivateLinearForwardingSupported;
	/* Description - Includes AdaptiveRoutingInfo, AdaptiveRoutingGroupTable, AdaptiveRoutingLinearForwardingTable attributes. Mutex with bit 2 */
	/* 0x0.1 - 0x0.1 */
	u_int8_t IsAdaptiveRoutingSupported;
	/* Description - Support for SwitchX style AR. Includes AdaptiveRoutingInfo, AdaptiveRoutingGroupTable, AdaptiveRoutingLinearForwardingTableRev1. Mutex with bit 1 */
	/* 0x0.2 - 0x0.2 */
	u_int8_t IsAdaptiveRoutingRev1Supported;
	/* Description - Includes PortMirrorRoute, PortMirrorFilter, PortMirrorPorts attributes */
	/* 0x0.3 - 0x0.3 */
	u_int8_t IsRemotePortMirroringSupported;
	/* Description -  */
	/* 0x0.4 - 0x0.4 */
	u_int8_t IsTemperatureSensingSupported;
	/* Description -  */
	/* 0x0.5 - 0x0.5 */
	u_int8_t IsConfigSpaceAccessSupported;
	/* Description -  */
	/* 0x0.6 - 0x0.6 */
	u_int8_t IsCableInfoSupported;
	/* Description -  */
	/* 0x0.7 - 0x0.7 */
	u_int8_t IsSMPEyeOpenSupported;
	/* Description -  */
	/* 0x0.8 - 0x0.8 */
	u_int8_t IsLossyVLConfigSupported;
	/* Description -  */
	/* 0x0.9 - 0x0.9 */
	u_int8_t IsExtendedPortInfoSupported;
	/* Description -  */
	/* 0x0.10 - 0x0.10 */
	u_int8_t IsAccessRegisterSupported;
	/* Description -  */
	/* 0x0.11 - 0x0.11 */
	u_int8_t IsInterProcessCommunicationSupported;
	/* Description -  */
	/* 0x0.12 - 0x0.12 */
	u_int8_t IsPortSLToPrivateLFTMapSupported;
	/* Description -  */
	/* 0x0.13 - 0x0.13 */
	u_int8_t IsExtendedSwitchInfoSupported;
	/* Description -  */
	/* 0x0.14 - 0x0.14 */
	u_int8_t IsASlaveVirtualSwitch;
};

/* Description -   */
/* Size in bytes - 64 */
struct tools_open_fw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor firmware version number. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t sub_minor;
	/* Description - Minor firmware version number. */
	/* 0x0.8 - 0x0.15 */
	u_int8_t minor;
	/* Description - Major firmware version number. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t major;
	/* Description -  */
	/* 0x0.24 - 0x0.24 */
	u_int8_t secure_fw;
	/* Description -  */
	/* 0x0.25 - 0x0.25 */
	u_int8_t signed_fw;
	/* Description -  */
	/* 0x0.26 - 0x0.26 */
	u_int8_t debug_fw;
	/* Description -  */
	/* 0x0.27 - 0x0.27 */
	u_int8_t dev_fw;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Firmware Build ID. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t build_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Firmware installation date. 
For example: 3 May 2004 will be coded as Month= 0x05, 
Day= 0x03, and Year= 0x04 */
	/* 0x8.0 - 0x8.15 */
	u_int16_t year;
	/* Description - Firmware installation date. 
For example: 3 May 2004 will be coded as Month= 0x05, 
Day= 0x03, and Year= 0x04 */
	/* 0x8.16 - 0x8.23 */
	u_int8_t day;
	/* Description - Firmware installation date. 
For example: 3 May 2004 will be coded as Month= 0x05, 
Day= 0x03, and Year= 0x04 */
	/* 0x8.24 - 0x8.31 */
	u_int8_t month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Firmware installation hour.
For example 17:43 will be coded as 0x1743 */
	/* 0xc.0 - 0xc.15 */
	u_int16_t hour;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - To be defined later. */
	/* 0x10.24 - 0x20.23 */
	u_int8_t psid[16];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - User-configured version number of the current INI file. */
	/* 0x20.0 - 0x20.31 */
	u_int32_t ini_file_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - FW version's Major field in extended (32b) format. */
	/* 0x24.0 - 0x24.31 */
	u_int32_t extended_major;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - FW version's Minor field in extended (32b) format. */
	/* 0x28.0 - 0x28.31 */
	u_int32_t extended_minor;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - FW version's SubMinor field in extended (32b) format. */
	/* 0x2c.0 - 0x2c.31 */
	u_int32_t extended_sub_minor;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - isfu_major. */
	/* 0x30.0 - 0x30.15 */
	u_int16_t isfu_major;
};

/* Description -   */
/* Size in bytes - 32 */
struct tools_open_hw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - For specific device IDs, see 
Table 12, "Switch Supported 
PCI Device IDs," on page 94 */
	/* 0x0.0 - 0x0.15 */
	u_int16_t device_id;
	/* Description - SwitchX Devices:
0x00A0: Device step A0, FCC package
0x00A1: Device step A1, FCC package
0x00A2: Device step A2, FCC package
Switch-IB Devices:
0x00A0: Switch-IB device step A0, FCC package */
	/* 0x0.16 - 0x0.31 */
	u_int16_t device_hw_revision;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Process Voltage Scaling
Maximum supported V_CODE voltage (in 50mV incre
ments) for the device. */
	/* 0x4.0 - 0x4.4 */
	u_int8_t pvs;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The PCI device-ID of the NIC/HCA in recovery (Live
fish) mode. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t hw_dev_id;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - MSB of the "base" MAC address of the NIC that was allo
cate during manufacturing. The NIC derives the MAC 
addresses for the different PCI PFs from this MAC 
address. This parameter can be used as a canonical unique 
identifier of the NIC.
manufacturing_base_mac of value 
0 means field is not sup
ported. */
	/* 0x10.0 - 0x10.15 */
	u_int16_t manufacturing_base_mac_47_32;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - LSB of the "base" MAC address of the NIC that was allo
cate during manufacturing. The NIC derives the MAC 
addresses for the different PCI PFs from this MAC 
address. This parameter can be used as a canonical unique 
identifier of the NIC.
manufacturing_base_mac of value 
0 means field is not sup
ported. */
	/* 0x14.0 - 0x14.31 */
	u_int32_t manufacturing_base_mac_31_0;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in secs.) since last reset0 */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t uptime;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_nv_hdr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tlv type */
	/* 0x0.0 - 0x0.15 */
	u_int16_t type;
	/* Description - size of tlv data in dwords (not including header) */
	/* 0x0.18 - 0x0.29 */
	u_int16_t length;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type Modifier. E.G.: Port number when the config is port related */
	/* 0x4.16 - 0x4.23 */
	u_int8_t type_mod;
	/* Description - Shadow: i.e if set the Fw will not update the tlv immediately but wait for a command */
	/* 0x4.24 - 0x4.24 */
	u_int8_t shadow;
	/* Description - Pad count: for non dword alligned tlvs */
	/* 0x4.25 - 0x4.26 */
	u_int8_t pad_cnt;
	/* Description - Data version can be set by caller or left as 0. */
	/* 0x4.28 - 0x4.31 */
	u_int8_t version;
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
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	union tools_open_tlv_type type;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_pmdio_addr_data {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Data (Clause 22) / Address/Data (Clause 45) */
	/* 0x0.0 - 0x0.15 */
	u_int16_t data;
	/* Description - Address (Clause 45)
This field is only valid for Address + Read and Address + Write operations, providing the address. For other Clause 45 operations the data field provides the address when appropriate.
 */
	/* 0x0.16 - 0x0.31 */
	u_int16_t addr;
};

/* Description -   */
/* Size in bytes - 32 */
struct tools_open_sw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t subminor;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	u_int8_t minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.3 */
	u_int8_t rom3_type;
	/* Description -  */
	/* 0x4.4 - 0x4.7 */
	u_int8_t rom3_arch;
	/* Description -  */
	/* 0x4.8 - 0x4.11 */
	u_int8_t rom2_type;
	/* Description -  */
	/* 0x4.12 - 0x4.15 */
	u_int8_t rom2_arch;
	/* Description -  */
	/* 0x4.16 - 0x4.19 */
	u_int8_t rom1_type;
	/* Description -  */
	/* 0x4.20 - 0x4.23 */
	u_int8_t rom1_arch;
	/* Description -  */
	/* 0x4.24 - 0x4.27 */
	u_int8_t rom0_type;
	/* Description -  */
	/* 0x4.28 - 0x4.31 */
	u_int8_t rom0_arch;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t rom0_version;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t rom1_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t rom2_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	u_int32_t rom3_version;
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
/* Size in bytes - 60 */
struct tools_open_extended_ib_port_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t StateChangeEnable;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	u_int8_t LinkSpeedSupported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	u_int8_t LinkSpeedEnabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	u_int8_t LinkSpeedActive;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	u_int16_t CapMask;
	/* Description -  */
	/* 0x10.28 - 0x10.31 */
	u_int8_t ActiveCell;
};

/* Description -   */
/* Size in bytes - 64 */
struct tools_open_ib_port_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t m_key_hi;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t m_key_lo;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t gid_prefix_hi;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t gid_prefix_lo;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	u_int16_t master_sm_lid;
	/* Description -  */
	/* 0x10.16 - 0x10.31 */
	u_int16_t lid;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	struct tools_open_cap_mask cap_mask;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	u_int16_t m_key_lease;
	/* Description -  */
	/* 0x18.16 - 0x18.31 */
	u_int16_t diag_code;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.7 */
	u_int8_t link_width_act;
	/* Description -  */
	/* 0x1c.8 - 0x1c.15 */
	u_int8_t link_width_sup;
	/* Description -  */
	/* 0x1c.16 - 0x1c.23 */
	u_int8_t link_width_ena;
	/* Description -  */
	/* 0x1c.24 - 0x1c.31 */
	u_int8_t local_port_num;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.3 */
	u_int8_t link_speed_ena;
	/* Description -  */
	/* 0x20.4 - 0x20.7 */
	u_int8_t link_speed_act;
	/* Description -  */
	/* 0x20.8 - 0x20.10 */
	u_int8_t lmc;
	/* Description -  */
	/* 0x20.14 - 0x20.15 */
	u_int8_t m_key_protec;
	/* Description -  */
	/* 0x20.16 - 0x20.19 */
	u_int8_t down_def_state;
	/* Description -  */
	/* 0x20.20 - 0x20.23 */
	u_int8_t phy_state;
	/* Description -  */
	/* 0x20.24 - 0x20.27 */
	u_int8_t port_state;
	/* Description -  */
	/* 0x20.28 - 0x20.31 */
	u_int8_t link_speed_sup;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.7 */
	u_int8_t vl_arb_high_cap;
	/* Description -  */
	/* 0x24.8 - 0x24.15 */
	u_int8_t vl_high_limit;
	/* Description -  */
	/* 0x24.16 - 0x24.19 */
	u_int8_t init_type;
	/* Description -  */
	/* 0x24.20 - 0x24.23 */
	u_int8_t vl_cap;
	/* Description -  */
	/* 0x24.24 - 0x24.27 */
	u_int8_t master_sm_sl;
	/* Description -  */
	/* 0x24.28 - 0x24.31 */
	u_int8_t neighbor_mtu;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.0 */
	u_int8_t filter_raw_out;
	/* Description -  */
	/* 0x28.1 - 0x28.1 */
	u_int8_t filter_raw_in;
	/* Description -  */
	/* 0x28.2 - 0x28.2 */
	u_int8_t Part_enforce_out;
	/* Description -  */
	/* 0x28.3 - 0x28.3 */
	u_int8_t Part_enforce_in;
	/* Description -  */
	/* 0x28.4 - 0x28.7 */
	u_int8_t operational_vl;
	/* Description -  */
	/* 0x28.8 - 0x28.12 */
	u_int8_t HOQLife;
	/* Description -  */
	/* 0x28.13 - 0x28.15 */
	u_int8_t vl_stall_cnt;
	/* Description -  */
	/* 0x28.16 - 0x28.19 */
	u_int8_t mtu_cap;
	/* Description -  */
	/* 0x28.24 - 0x28.31 */
	u_int8_t vl_arb_low_cap;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.15 */
	u_int16_t p_key_violations;
	/* Description -  */
	/* 0x2c.16 - 0x2c.31 */
	u_int16_t m_key_violations;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.4 */
	u_int8_t subnet_to;
	/* Description -  */
	/* 0x30.7 - 0x30.7 */
	u_int8_t client_reregister;
	/* Description -  */
	/* 0x30.8 - 0x30.15 */
	u_int8_t guid_cap;
	/* Description -  */
	/* 0x30.16 - 0x30.31 */
	u_int16_t q_key_violations;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.16 - 0x34.19 */
	u_int8_t overrun_err;
	/* Description -  */
	/* 0x34.20 - 0x34.23 */
	u_int8_t local_phy_err;
	/* Description -  */
	/* 0x34.24 - 0x34.28 */
	u_int8_t resp_time_value;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - 0: No State Change; valid only on Set(); 1: 14.0625 Gbps (FDR); 2: 25.78125 Gbps (EDR); 3: 14.0625 Gbps (FDR) or 25.78125 Gbps (EDR); 4-29: Reserved; 30: Disable extended link speeds/Extended link speeds disabled; 31: Set to LinkSpeedExtSupported value; response contains actual LinkSpeedExtSupported; */
	/* 0x3c.0 - 0x3c.4 */
	u_int8_t link_speed_ext_ena;
	/* Description - 0: Reserved; 1: 14.0625 Gbps (FDR); 2: 25.78125 Gbps (EDR); 3: 14.0625 Gbps (FDR) or 25.78125 Gbps (EDR); 4-15: Reserved */
	/* 0x3c.8 - 0x3c.11 */
	u_int8_t link_speed_ext_sup;
	/* Description - 0: No extended speed active; 1: 14.0625 Gbps (FDR); 2: 25.78125 Gbps (EDR); 3-15: Reserved */
	/* 0x3c.12 - 0x3c.15 */
	u_int8_t link_speed_ext_act;
};

/* Description -   */
/* Size in bytes - 72 */
struct tools_open_mcam {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups 
0 - First 128 REG_ID */
	/* 0x0.0 - 0x0.7 */
	u_int8_t access_reg_group;
	/* Description - Feature list mask index : 
0 - enhanced features */
	/* 0x0.16 - 0x0.23 */
	u_int8_t feature_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported management's access register bitmaks.
Based on 
access_reg_group 
index.
 
When bit is set , The register is supported in the device. 
For example:
Bit 1 - MFCR (0x9001)
Bit 2 - MFSC (0x9002)
Bit 3 - MFSM (0x9003)
Bit 4 - MFSL (0x9004)
Bit 73 - MPPF (0x9049)
Bit 127- MCAP (0x907F) */
	/* 0x8.24 - 0x18.23 */
	u_int8_t mng_access_reg_cap_mask[16];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Supported port's enhanced features.
Based on 
feature_group
 
index.
When bit is set , The feature is supported in the device: 
Bit 0 - 
MPCNT counter group: 
PCIE performance counters supported */
	/* 0x28.24 - 0x38.23 */
	u_int8_t mng_feature_cap_mask[16];
};

/* Description -   */
/* Size in bytes - 28 */
struct tools_open_mfmc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash Select */
	/* 0x0.4 - 0x0.5 */
	u_int8_t fs;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Power of 2 of the write protect block count
0: 1 block
1: 2 blocks
2: 4 blocks, etc.
Range 0..5
Reserved when wrp_en = 0 */
	/* 0x4.0 - 0x4.7 */
	u_int8_t wrp_block_count;
	/* Description - Block size
0: write protect 4Kbyte blocks
1: write protect 64Kbyte blocks.
Reserved when wrp_en = 0
Note that not all block sizes are supported on all flash device, need to check MFPA capabilities */
	/* 0x4.16 - 0x4.17 */
	u_int8_t block_size;
	/* Description - Write protect enable
Set write protect of flash device */
	/* 0x4.31 - 0x4.31 */
	u_int8_t wrp_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Power of 2 for sub_sector size in 4Kbytes.
0: 4KB. 1: 8KB. 2: 16KB. 3: 32KB. 4:64KB. Etc.
Reserved when MFPA.sub_sector_wrp_en = 0 */
	/* 0x8.0 - 0x8.5 */
	u_int8_t sub_sector_protect_size;
	/* Description - Power of 2 for sector size in 4Kbytes.
0: 4KB. 1: 8KB. 2: 16KB. 3: 32KB. 4:64KB. Etc.\Reserved when MFPA.sector_wrp_en = 0 */
	/* 0x8.8 - 0x8.13 */
	u_int8_t sector_protect_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Quad enable IO bit in the device status register */
	/* 0x10.24 - 0x10.24 */
	u_int8_t quad_en;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The number of dummy clock cycles subsequent to all FAST READ commands.
Reserved if not supported by the device */
	/* 0x18.0 - 0x18.3 */
	u_int8_t dummy_clock_cycles;
};

/* Description -   */
/* Size in bytes - 32 */
struct tools_open_mfpa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash Select */
	/* 0x0.4 - 0x0.5 */
	u_int8_t fs;
	/* Description - Parallel */
	/* 0x0.8 - 0x0.8 */
	u_int8_t p;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - address in bytes */
	/* 0x4.0 - 0x4.31 */
	u_int32_t boot_address;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - number of flash devices connected */
	/* 0x10.0 - 0x10.3 */
	u_int8_t flash_num;
	/* Description - If set, MFMC register supports setting write protect of subsector granularity  */
	/* 0x10.16 - 0x10.16 */
	u_int8_t sub_sector_wrp_en;
	/* Description - If set, MFMC register supports setting write protect with sector granularity */
	/* 0x10.17 - 0x10.17 */
	u_int8_t sector_wrp_en;
	/* Description - supports 64KB bulk erase operation */
	/* 0x10.29 - 0x10.29 */
	u_int8_t bulk_64kb_erase_en;
	/* Description - supports 32KB bulk erase operation */
	/* 0x10.30 - 0x10.30 */
	u_int8_t bulk_32kb_erase_en;
	/* Description - reflection of wip bit from flash */
	/* 0x10.31 - 0x10.31 */
	u_int8_t wip;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Flash JEDEC ID */
	/* 0x14.0 - 0x14.23 */
	u_int32_t jedec_id;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Flash sectore size */
	/* 0x18.0 - 0x18.9 */
	u_int16_t sector_size;
	/* Description -  */
	/* 0x18.16 - 0x18.23 */
	u_int8_t block_allignment;
	/* Description -  */
	/* 0x18.24 - 0x18.31 */
	u_int8_t block_size;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Bitmask indicates which capabilities are supported.
Bit 0: Set write protect supported (register MFMC supports setting write protection)
Bit 1: quad enable read write is supported (register MFMC supports setting quad enable)
Bit 2: set dummy cycle supported (register MFMC supports setting dummy cycles) */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t capability_mask;
};

/* Description -   */
/* Size in bytes - 128 */
struct tools_open_mgir {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see 
Table 693, "
Hardware Info Layout
," 
on page 746 */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_hw_info hw_info;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Firmware Information, see 
Table 695, "
Firmware Info Layout
," 
on page 747 */
	/* 0x20.0 - 0x5c.31 */
	struct tools_open_fw_info fw_info;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x7c.31 */
	struct tools_open_sw_info sw_info;
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
	/* Description - operation: 0 – unlocked, 1 – locked, other – RESERVED.  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t operation;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Key */
	/* 0x8.0 - 0xc.31 */
	u_int64_t key;
};

/* Description -   */
/* Size in bytes - 256 */
struct tools_open_mnva {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nv_hdr nv_hdr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.24 - 0x88.23 */
	u_int8_t data[128];
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
/* Size in bytes - 8 */
struct tools_open_mnvi {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nv_hdr nv_hdr;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_mnvia {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nv_hdr nv_hdr;
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
/* Size in bytes - 64 */
struct tools_open_node_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t num_of_ports;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	u_int8_t node_type;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t class_version;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t base_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t system_image_guid_hi;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t system_image_guid_lo;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t node_guid_hi;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t node_guid_lo;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	u_int32_t port_guid_hi;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	u_int32_t port_guid_lo;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t device_id;
	/* Description -  */
	/* 0x1c.16 - 0x1c.31 */
	u_int16_t partition_cap;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	u_int32_t revision;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.23 */
	u_int32_t vendor_id;
	/* Description -  */
	/* 0x24.24 - 0x24.31 */
	u_int8_t local_port_num;
};

/* Description -   */
/* Size in bytes - 268 */
struct tools_open_nvda {
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
/* Size in bytes - 12 */
struct tools_open_nvdi {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_nv_hdr_fifth_gen nv_hdr;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_nvia {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Information targeted for invalidation
0: ALL - all NVRAM parameters.
 
All other values are reserved. */
	/* 0x0.0 - 0x0.2 */
	u_int8_t target;
	/* Description - The entity which perform the invalidate.
The encoding same as writer_id in Configuration Item reg
ister (See       
Table 872, "
Configuration Item Layout
," on 
page 1027
). */
	/* 0x0.4 - 0x0.8 */
	u_int8_t writer_id;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_nvqc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	union tools_open_tlv_type type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - the configuration item is supported and can be read */
	/* 0x4.0 - 0x4.0 */
	u_int8_t support_rd;
	/* Description - the configuration item is supported and can be updated */
	/* 0x4.1 - 0x4.1 */
	u_int8_t support_wr;
	/* Description - The maximum version of the configuration item currently supported by the firmware. */
	/* 0x4.4 - 0x4.7 */
	u_int8_t version;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_nvqgc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVDA read factory settings. 0: Unsupported. 1: Supported. */
	/* 0x0.0 - 0x0.0 */
	u_int8_t read_factory_settings_support;
	/* Description - NVDA read current settings, 0=unsupported, 1=supported */
	/* 0x0.1 - 0x0.1 */
	u_int8_t nvda_read_current_settings;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_pmdic {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit 0 - NOP
Bit 1 - Address (reserved for Clause 22)
Bit 2 - Read
Bit 3 - Write
Bit 4 - Post Read Increment Address (reserved for Clause 22)
Bit 6 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
Bit 7- Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22)
 */
	/* 0x4.0 - 0x4.7 */
	u_int8_t operation_cap;
	/* Description - MDIO I/F definition:
00 - Clause 22
01 - Clause 45
 */
	/* 0x4.24 - 0x4.25 */
	u_int8_t clause;
	/* Description - MDIO present:
00 - MDIO not present
01 - External MDIO present
 */
	/* 0x4.30 - 0x4.31 */
	u_int8_t mdio_preset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bit 0 External Phy FW master
Used for external Phy FW burning. When set, the MDIO I/F is used for an external phy FW burn
 */
	/* 0x8.0 - 0x8.7 */
	u_int8_t misc_cap;
};

/* Description -   */
/* Size in bytes - 264 */
struct tools_open_pmdio {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 000 - NOP
001 - Address (reserved for Clause 22)
010 - Read
011 - Write
100 - Post Read Increment Address (reserved for Clause 22)
110 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
111 - Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22)
 */
	/* 0x0.0 - 0x0.2 */
	u_int8_t operation;
	/* Description - MDIO I/F definition:
00 - Clause 22
01 - Clause 45
 */
	/* 0x0.8 - 0x0.9 */
	u_int8_t clause;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	u_int8_t local_port;
	/* Description - Lock bit. Setting this bit will lock the access to port's MDIO
Used for operations that requires continuous MDIO accesses.

In order to guarantee atomicity of some operations, the port MDIO interface can be locked to a specific interface.
When the lock bit is set, no MDIO accesses through another interface (FW/driver/tools) are allowed on the port.
An attempt to set the lock bit while it is locked by another interface should return a RESOURCE/_BUSY status.
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t lock;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reg Address (Clause 22) / MDIO Manageable Device address (Clause 45) */
	/* 0x4.0 - 0x4.4 */
	u_int8_t reg_adr_mmd;
	/* Description - Index of last entry in the operations list. 0 means single operation (backward compatible).
Valid values are 0..63
 */
	/* 0x4.8 - 0x4.15 */
	u_int8_t last_op_idx;
	/* Description - Number of operations actually executed by FW. Driver write 0 to this field. FW increment the field with any execution of an entry in the operations list. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t num_ops_done;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - addr/data entry */
	/* 0x8.0 - 0x104.31 */
	struct tools_open_pmdio_addr_data mdio_trans[64];
};

/* Description -   */
/* Size in bytes - 64 */
union tools_open_smp_vsp_general_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_hw_info hw_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct tools_open_fw_info fw_info;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_sw_info sw_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct tools_open_capability_mask_smp capability_mask_smp;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_aux_data_hdr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0x544c563a : ascii for "TLV:"
 */
	/* 0x0.0 - 0x0.31 */
	u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0x6548bc86 */
	/* 0x4.0 - 0x4.31 */
	u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 0x01020305 */
	/* 0x8.0 - 0x8.31 */
	u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - 0x080d1522 */
	/* 0xc.0 - 0xc.31 */
	u_int32_t signature3;
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
/* Size in bytes - 4 */
struct tools_open_bar_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Base 2 log of the size of the physical function��s first BAR, in MBs. E.g. for 8MB the value is 3. */
	/* 0x0.0 - 0x0.31 */
	u_int32_t log_uar_bar_size;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VLAN ID for network boot. */
	/* 0x0.0 - 0x0.11 */
	u_int16_t boot_vlan;
	/* Description - 0 �� None �� disable legacy boot.
1 �� PXE (DHCP/TFTP boot).
2 �� iSCSI
3 �� PXE + iSCSI
4-255 �� Reserved
 */
	/* 0x0.16 - 0x0.23 */
	u_int8_t legacy_boot_protocol;
	/* Description - Number of retries to attempt in case of boot failure.
7 indicate indefinite retries.
 */
	/* 0x0.24 - 0x0.26 */
	u_int8_t boot_retry_conut;
	/* Description - 1 �� Enable VLAN mode for network boot. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t boot_vlan_en;
	/* Description - 0 �� disable boot option ROM: disables installation of the UNDI/16 driver. The option ROM is still required to expose CLP, UEFI and so on.
1 �� enable boot option ROM
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t boot_option_rom_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_boot_settings_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Select which IP protocol version will be used by flexboot */
	/* 0x0.8 - 0x0.9 */
	u_int8_t ip_ver;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_common_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t length;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t type;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t version;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_component_desciptor {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t identifier;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t pldm_classification;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t cb_offset_h;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t cb_offset_l;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t size;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_component_ptr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t component_index;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t storage_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t storage_address;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_external_port {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	u_int8_t port_owner;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	u_int8_t allow_rd_counters;
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
/* Size in bytes - 4 */
struct tools_open_infiniband_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - P_key to be used by PXE boot. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t boot_pkey;
};

/* Description -   */
/* Size in bytes - 16 */
struct tools_open_infiniband_dc_capabilities {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t min_log_dcr_hash_table_size;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t max_log_dcr_hash_table_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t min_dcr_lifo_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t max_dcr_lifo_size;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_infiniband_dc_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hash table size minus one */
	/* 0x0.0 - 0x0.4 */
	u_int8_t log_dcr_hash_table_size;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The amount of total DCRs available to join linked-lists after hash DCRs. This is a dynamic pool of DCRs that can be used to connect all incoming connections. */
	/* 0x4.0 - 0x4.23 */
	u_int32_t dcr_lifo_size;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_iscsi_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable or disable whether the iSCSI target will appear as the first hard disk drive in the system. Currently not supported. */
	/* 0x0.21 - 0x0.21 */
	u_int8_t target_as_first_hdd_en;
	/* Description - Boot to iSCSI target after connection. 
�� 0 �� Enabled
�� 1 �� Disabled
�� 2 - One time disabled
�� 3 - Invalid setting
 */
	/* 0x0.22 - 0x0.23 */
	u_int8_t boot_to_target;
	/* Description - Enable IPv6 auto-configuration through DHCP. Currently not supported. */
	/* 0x0.24 - 0x0.24 */
	u_int8_t ipv6_auto_config_en;
	/* Description - Enable VLAN mode for iSCSI. */
	/* 0x0.26 - 0x0.26 */
	u_int8_t vlan_en;
	/* Description - Enable the TCP timestamps option for iSCSI TCP connections. */
	/* 0x0.27 - 0x0.27 */
	u_int8_t tcp_timestamps_en;
	/* Description - Authenticate the target to the initiator using CHAP. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t chap_mutual_auth_en;
	/* Description - Authenticate the initiator to the target using CHAP. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t chap_auth_en;
	/* Description - Retrieve iSCSI parameters through DHCP. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t dhcp_iscsi_en;
	/* Description - Retrieve IPv4 configuration for iSCSI through DHCP. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t ipv4_dhcp_en;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - VLAN number. Only valid when vlan_en is 1 */
	/* 0x4.0 - 0x4.11 */
	u_int16_t vlan;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of connection attempts to make if the iSCSI target is busy. Valid values are between 0 and 60. */
	/* 0x8.0 - 0x8.7 */
	u_int8_t lun_busy_retry_count;
	/* Description - Number of seconds to wait after the link comes up before sending packets over the network. */
	/* 0x8.8 - 0x8.15 */
	u_int8_t link_up_delay_time;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_lldp_client_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.27 - 0x0.27 */
	u_int8_t lldp_nb_dcbx;
	/* Description -  */
	/* 0x0.28 - 0x0.29 */
	u_int8_t lldp_nb_rx_mode;
	/* Description -  */
	/* 0x0.30 - 0x0.31 */
	u_int8_t lldp_nb_tx_mode;
};

/* Description -   */
/* Size in bytes - 28 */
struct tools_open_lldp_nb {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable processing of incoming LLDB NB BPDUs
Default: Disable
 */
	/* 0x0.30 - 0x0.30 */
	u_int8_t lldp_nb_rx_en;
	/* Description - Enable transmission of LLDP Next Bridge BPDUs
Default: Enabled
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t lldp_nb_tx_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Interval for sending LLDP NB PDUs in seconds
Default: 30
 */
	/* 0x8.0 - 0x8.11 */
	u_int16_t lldp_msg_tx_interval;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - A bitmask saying which of the LLDP-TLV to send
Default: b1111  (only TLVs 0..3) �� according to the standard these are mandatory TLVs that must always be enabled

An enabled TLV will not be send if a corresponding TLV is not defined
 */
	/* 0xc.24 - 0x1c.23 */
	u_int8_t lldp_tx_tlv_mask[16];
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_lldp_nb_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.27 - 0x0.27 */
	u_int8_t lldp_nb_dcbx_en;
	/* Description -  */
	/* 0x0.28 - 0x0.29 */
	u_int8_t lldp_nb_rx_cap;
	/* Description -  */
	/* 0x0.30 - 0x0.31 */
	u_int8_t lldp_nb_tx_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_lldp_nb_dcbx {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.0 */
	u_int8_t ieee_dcbx_en;
	/* Description -  */
	/* 0x0.1 - 0x0.1 */
	u_int8_t cee_dcbx_en;
	/* Description -  */
	/* 0x0.2 - 0x0.2 */
	u_int8_t dcbx_willing;
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
	/* 0x0.0 - 0xfc.31 */
	struct tools_open_mnva mnva;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_mnvi mnvi;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_mnvia mnvia;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nvqc nvqc;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nvia nvia;
	/* Description -  */
	/* 0x0.0 - 0x108.31 */
	struct tools_open_nvda nvda;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_nvdi nvdi;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_nvqgc nvqgc;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct tools_open_mvts mvts;
	/* Description -  */
	/* 0x0.0 - 0x98.31 */
	struct tools_open_mnvgn mnvgn;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct tools_open_mfmc mfmc;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_mfpa mfpa;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	struct tools_open_mgir mgir;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	struct tools_open_mcam mcam;
	/* Description -  */
	/* 0x0.0 - 0xa8.31 */
	struct tools_open_mgnle mgnle;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_mlock mlock;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_multi_part {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t total_length;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t number_of_extensions;
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
/* Size in bytes - 32 */
struct tools_open_nv_cx3_global_conf {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Defines the Port PHY parameters mode. 0x0: DEVICE_DEFAULT, 0x1: LEGACY, 0x2: ADVANCED */
	/* 0x0.28 - 0x0.29 */
	u_int8_t phy_param_mode;
	/* Description - Force vlan steering, ignoring driver configuraiton. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t steer_force_vlan;
	/* Description - When set, IEE1588 (PTP) HW timestamping capability is reported to the device driver. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t cq_timestamp;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_option_rom_capability {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - flexboot supports configuration of PXE boot IP version defined in boot settings ext parameter */
	/* 0x0.31 - 0x0.31 */
	u_int8_t ip_ver;
};

/* Description -   */
/* Size in bytes - 28 */
struct tools_open_package_descriptor {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t num_of_devices;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t num_of_components;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t cb_offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t cb_archive_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t cb_size_h;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t cb_size_l;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.24 - 0x14.31 */
	u_int8_t cb_compression;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	u_int32_t user_data_offset;
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_pci_capabilities {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 when max_pf_uar_bar_size field is configurable and the log_max_pf_uar_bar_size field is valid */
	/* 0x0.24 - 0x0.24 */
	u_int8_t pf_bar_size_supported;
	/* Description - 1 when max_vf_uar_bar_size field is configurable and the log_max_vf_uar_bar_size field is valid */
	/* 0x0.25 - 0x0.25 */
	u_int8_t vf_bar_size_supported;
	/* Description - 1 when num_pf_msix field is configurable and the max_num_pf_msix field is valid */
	/* 0x0.26 - 0x0.26 */
	u_int8_t num_pf_msix_supported;
	/* Description - 1 when the num_vf_msix field is configurable and max_num_pfs is valid */
	/* 0x0.27 - 0x0.27 */
	u_int8_t num_vf_msix_supported;
	/* Description - 1 when the num_pfs field is configurable and max_num_pfs is valid */
	/* 0x0.28 - 0x0.28 */
	u_int8_t num_pfs_supported;
	/* Description - 1 when the max_total_bar field is valid */
	/* 0x0.29 - 0x0.29 */
	u_int8_t max_total_bar_valid;
	/* Description - 1 when the total_msix field is valid */
	/* 0x0.30 - 0x0.30 */
	u_int8_t max_total_msix_valid;
	/* Description - 1 when max_vfs_per_pf fields is valid. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t max_vfs_per_pf_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The maximum number of VFs that can be set in the total_vfs settings (per PF) */
	/* 0x4.0 - 0x4.15 */
	u_int16_t max_vfs_per_pf;
	/* Description - Maximum number of PFs per port */
	/* 0x4.16 - 0x4.19 */
	u_int8_t max_num_pfs;
	/* Description - 1 - function per port settings is configurable */
	/* 0x4.29 - 0x4.29 */
	u_int8_t fpp_support;
	/* Description - 1 - the device supports controlling the VF QoS setting */
	/* 0x4.30 - 0x4.30 */
	u_int8_t vf_qos_control_support;
	/* Description - 1 when SRIOV is configurable */
	/* 0x4.31 - 0x4.31 */
	u_int8_t sriov_support;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log 2 of the maximum size of a PF's UAR BAR */
	/* 0x8.0 - 0x8.5 */
	u_int8_t log_max_pf_uar_bar_size1;
	/* Description - Log 2 of the maximum size of a VF's UAR BAR */
	/* 0x8.6 - 0x8.11 */
	u_int8_t log_max_vf_uar_bar_size;
	/* Description - Maximum number of MSI-X vectors and EQs per PF */
	/* 0x8.12 - 0x8.21 */
	u_int16_t max_num_pf_msix;
	/* Description - Maximum number of MSI-X vectors and EQs per VF */
	/* 0x8.22 - 0x8.31 */
	u_int16_t max_num_vf_msix;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximum number of MSI-X for the aggregat of all PF and VFs */
	/* 0xc.0 - 0xc.31 */
	u_int32_t max_total_msix;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Maximum total of the MMIO space for all PFs and VFs combined, in megabytes. */
	/* 0x10.0 - 0x10.31 */
	u_int32_t max_total_bar;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_pci_configuration {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 1 when log_pf_uar_bar_size field is valid */
	/* 0x0.24 - 0x0.24 */
	u_int8_t pf_bar_size_valid;
	/* Description - 1 when log_vf_uar_bar_size field is valid */
	/* 0x0.25 - 0x0.25 */
	u_int8_t vf_bar_size_valid;
	/* Description - 1 when num_pfs_msix field is valid */
	/* 0x0.26 - 0x0.26 */
	u_int8_t num_pfs_msix_valid;
	/* Description - 1 when num_vfs_msix field is valid */
	/* 0x0.27 - 0x0.27 */
	u_int8_t num_vfs_msix_valid;
	/* Description - 1 when num_pfs field is valid */
	/* 0x0.28 - 0x0.28 */
	u_int8_t num_pfs_valid;
	/* Description - 1 when fpp_en field is valid */
	/* 0x0.29 - 0x0.29 */
	u_int8_t fpp_valid;
	/* Description - 1 when the full_vf_qos field below is valid */
	/* 0x0.30 - 0x0.30 */
	u_int8_t full_vf_qos_valid;
	/* Description - 1 when the sriov_en and total_vfs field below are valid. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sriov_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The total number of VFs that can be supported */
	/* 0x4.0 - 0x4.15 */
	u_int16_t total_vfs;
	/* Description - Number of PFs per port */
	/* 0x4.16 - 0x4.19 */
	u_int8_t num_pfs;
	/* Description - 0 - single PF for both ports
1 - function per-port */
	/* 0x4.29 - 0x4.29 */
	u_int8_t fpp_en;
	/* Description - 0 - Use reduced QoS support level on VFs
1 - Support full QoS on VFs */
	/* 0x4.30 - 0x4.30 */
	u_int8_t full_vf_qos;
	/* Description - 1 when SRIOV is enabled: SRIOV capability will appear in the PCI configuration header */
	/* 0x4.31 - 0x4.31 */
	u_int8_t sriov_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log 2 of the size of a PF's UAR BAR */
	/* 0x8.0 - 0x8.5 */
	u_int8_t log_pf_uar_bar_size;
	/* Description - Log 2 of the size of a VF's UAR BAR */
	/* 0x8.6 - 0x8.11 */
	u_int8_t log_vf_uar_bar_size;
	/* Description - Number of MSI-X vectors and EQs per PF */
	/* 0x8.12 - 0x8.21 */
	u_int16_t num_pf_msix;
	/* Description - Number of MSI-X vectors and EQs per VF */
	/* 0x8.22 - 0x8.31 */
	u_int16_t num_vf_msix;
};

/* Description -   */
/* Size in bytes - 264 */
union tools_open_phy_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_pmdic pmdic;
	/* Description -  */
	/* 0x0.0 - 0x104.31 */
	struct tools_open_pmdio pmdio;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_port_boot_state {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of the GPIO that is connected to the AUX power setting circuitry */
	/* 0x0.0 - 0x0.7 */
	u_int8_t aux_power_indication_gpio;
	/* Description - 0  not present
 1 present
 if the NIC has a circuitry that can indicate when the device is working on AUX power. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t aux_power_indication_gpio_en;
	/* Description - 0  disabled
 1 enabled
 When enabled, the device will response to standby indication from PCI or GPIO (if configured) and reduce power consumption while keeping the SMBUS on. To meet the power requirement, the NIC will disable the network ports and cage power on standby mode (indicate with PCIe L2/L3 message sequence of with the GPIO */
	/* 0x0.30 - 0x0.30 */
	u_int8_t standby_on_aux;
	/* Description - 0 Normal (admin-on)
 1 low power
 When set to low-power the device will boot with minimal power until the GPIO detects that the PCIe power rails are active. The low power mode is effective ONLY when there is a circuitry to detect AUX power condition (with GPIO indication) */
	/* 0x0.31 - 0x0.31 */
	u_int8_t power_up_on_aux;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_preboot_boot_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - VLAN ID for network boot. */
	/* 0x0.0 - 0x0.11 */
	u_int16_t boot_vlan;
	/* Description - 0  None disable legacy boot.
1  PXE (DHCP/TFTP boot).
2  iSCSI

3  PXE + iSCSI
4-255  Reserved
 */
	/* 0x0.16 - 0x0.23 */
	u_int8_t legacy_boot_protocol;
	/* Description - Number of retries to attempt in case of boot failure.
7 indicate indefinite retries.
 */
	/* 0x0.24 - 0x0.26 */
	u_int8_t boot_retry_count;
	/* Description - 1 Enable VLAN mode for network boot */
	/* 0x0.30 - 0x0.30 */
	u_int8_t boot_vlan_en;
	/* Description - 0 disable boot option ROM: disables installation of the UNDI/16 driver. The option ROM is still required to expose CLP, UEFI and so on.
1 enable boot option ROM
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t boot_option_rom_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_preboot_flow_ctrl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Per priority bit mask. For each priority:
0 �� ignore incoming PFC frames regarding this priority.
1 �� respect incoming PFC frames on this priority.
 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t pfcrx;
	/* Description - Per priority bit mask. For each priority:

0 �� no PFC pause frames generation for this priority.
1 �� generate PFC pause frames for this priority.
PFC and global pauses are mutually exclusive.
 */
	/* 0x0.8 - 0x0.15 */
	u_int8_t pfctx;
	/* Description - For future DCBX support. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t pfc_willing;
	/* Description - 0 �� ignore received pause frames
1 �� respect received pause frames
 */
	/* 0x0.30 - 0x0.30 */
	u_int8_t pprx;
	/* Description - 0 �� no pause frame generation.
1 �� generate pause frames.
PFC and global pauses are mutually exclusive.
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t pptx;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_qos {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	u_int8_t num_of_vl;
	/* Description -  */
	/* 0x0.4 - 0x0.7 */
	u_int8_t num_of_tc;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_qos_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.3 */
	u_int8_t max_num_of_vl;
	/* Description -  */
	/* 0x0.4 - 0x0.7 */
	u_int8_t max_num_of_tc;
};

/* Description -   */
/* Size in bytes - 20 */
struct tools_open_query_def_params_global {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
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
/* Size in bytes - 4 */
struct tools_open_roce_cc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Per priority enable disable (0..7)
Default: False
 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t roce_cc_enable_priority;
	/* Description - 0 = ECN
1 = QCN
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t roce_cc_algorithm;
};

/* Description -   */
/* Size in bytes - 68 */
struct tools_open_roce_cc_ecn {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Default: True
When receiving an CNP, the target rate should be updated if the transmission rate was increased due to the timer, and not only due to the byte counter
 */
	/* 0x0.30 - 0x0.30 */
	u_int8_t clamp_tgt_rate_after_time_inc;
	/* Description - default - False
 */
	/* 0x0.31 - 0x0.31 */
	u_int8_t clamp_tgt_rate;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Time between rate increases if no CNPs are received. Given in u-seconds.
Default: 2
 */
	/* 0x4.0 - 0x4.16 */
	u_int32_t rpg_time_reset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Transmitted data between rate increases if no CNPs are received. Given in Bytes.
  0 == disabled  TBD: update the PRM
Default: 150
 */
	/* 0x8.0 - 0x8.14 */
	u_int16_t rpg_byte_reset;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The number of times rpByteStage or rpTimeStage can count before the RP rate control state machine advances states.
Default: 5
 */
	/* 0xc.0 - 0xc.4 */
	u_int8_t rpg_threshold;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The maximum rate, in Mbits per second, at which an RP can transmit. Once this limit is reached, the RP rate limited is released and the flow is not rate limited any more.
Default: 0 (Full port speed) �� TBD update PRM
 */
	/* 0x10.0 - 0x10.30 */
	u_int32_t rpg_max_rate;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The rate, in Mbits per second, used to increase rpTargetRate in the RPR_ACTIVE_INCREASE.
Default:  10
 */
	/* 0x14.0 - 0x14.16 */
	u_int32_t rpg_ai_rate;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The rate, in Mbits per second, used to increase rpTargetRate in the RPR_HYPER_INCREASE state
Default: 50
 */
	/* 0x18.0 - 0x18.16 */
	u_int32_t rpg_hai_rate;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - -  If a CNP is received, the flow rate is reduced at the beginning of the next rate_reduce_monitor_period interval to (1-Alpha/Gd)*CurrentRate. rpg_gd is given as log2(Gd), where Gd may only be powers of 2.
Default: 7 
 */
	/* 0x1c.0 - 0x1c.3 */
	u_int8_t rpg_gd;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The minimum factor by which the current transmit rate can be changed when processing a CNP. Value is given as a percentage (1-100).
Default: 50
 */
	/* 0x20.0 - 0x20.7 */
	u_int8_t rpg_min_dec_fac;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The minimum value, in Mb per second, for rate to limit.
Default: 2000
 */
	/* 0x24.0 - 0x24.16 */
	u_int32_t rpg_min_rate;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The rate that is set for the flow when a rate limiter is allocated to it upon first CNP received, in Mbps
Default: 0 Port speed (TBD update PRM)
 */
	/* 0x28.0 - 0x28.16 */
	u_int32_t rate_to_set_on_first_cnp;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Used to update the congestion estimator (alpha) once every dce_tcp_rtt microseconds, according to the equation:
Alpha = (cnp_received * dceTcpG) + (1 - dceTcpG) * alpha .
dceTcpG is divided by 2^10.
cnp_received is set to one if a CNP was received for this flow during period since the previous update and the current update
Default: 64
 */
	/* 0x2c.0 - 0x2c.9 */
	u_int16_t dce_tcp_g;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The time between updates of the alpha value, in microseconds.
Default: 2
 */
	/* 0x30.0 - 0x30.16 */
	u_int32_t dce_tcp_rtt;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The minimum time between 2 consecutive rate reductions for a single flow. Rate reduction will occur only if a CNP is received during the relevant time interval.
Default: 2
 */
	/* 0x34.0 - 0x34.16 */
	u_int32_t rate_reduce_monitor_period;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - The initial value of alpha to use when receiving the first CNP for a flow. Expressed in a fixed point fraction of 2^10.
Default: TBD
 */
	/* 0x38.0 - 0x38.9 */
	u_int16_t initial_alpha_value;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Minimum time between sending cnps from the port, in microseconds.
Default: 0 
 */
	/* 0x3c.0 - 0x3c.16 */
	u_int32_t min_time_between_cnps;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - The 802.1p priority value of the generated CNP for this port
Default: 7
 */
	/* 0x40.0 - 0x40.2 */
	u_int8_t cnp_802p_prio;
	/* Description - The DiffServ Code Point of the generated CNP for this port
Default: 0
 */
	/* 0x40.8 - 0x40.13 */
	u_int8_t cnp_dscp;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_roce_v_1_5_next_protocol {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - the next protocol value set in the IPv4/IPv6
packets for RoCE v1.5
default = 0xfe
 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t roce_over_ip_next_protocol;
};

/* Description -   */
/* Size in bytes - 64 */
union tools_open_smp_data {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	union tools_open_smp_vsp_general_info general_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct tools_open_ib_port_info port_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct tools_open_node_info node_info;
	/* Description -  */
	/* 0x0.0 - 0x38.31 */
	struct tools_open_extended_ib_port_info extended_port_info;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_sriov {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of VFs that can be supported. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t total_vfs;
	/* Description - 1 when SRIOV is enabled: SRIOV capability will appear on the PCI configuration header. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_tpt_capabilities {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - value is R/O
1 - value is R/W */
	/* 0x0.31 - 0x0.31 */
	u_int8_t log_max_payload_size_supported;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_tpt_configuration {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Log2 of the maximum supported PCI burns size for TPT accesses to host memory

0 - Automatically choose the burst length according to PCIe packet lenght
12 - Burst length of 4KB

Others - Reserved */
	/* 0x0.0 - 0x0.3 */
	u_int8_t log_max_payload_size;
};

/* Description -   */
/* Size in bytes - 12 */
struct tools_open_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t version_sub_minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t version_minor;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	u_int8_t version_major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	u_int8_t day;
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	u_int8_t month;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t year;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	u_int8_t seconds;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	u_int8_t minutes;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	u_int8_t hour;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_open_vpi_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Network link type:
0 - Reserved
1 - InfiniBand
2 - Ethernet
 */
	/* 0x0.0 - 0x0.1 */
	u_int8_t network_link_type;
	/* Description - 0 - Reserved
1 - Infiniband
2 - Ethernet
Valid for CX4 and above only
when VPI network link type is selcted this field determines
the default link type when no cable is connected */
	/* 0x0.2 - 0x0.3 */
	u_int8_t default_link_type;
	/* Description -  */
	/* 0x0.4 - 0x0.5 */
	u_int8_t phy_type;
	/* Description -  */
	/* 0x0.6 - 0x0.7 */
	u_int8_t xfi_mode;
	/* Description -  */
	/* 0x0.8 - 0x0.8 */
	u_int8_t force_mode;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_open_wol {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable Wake on secure on password magic packet */
	/* 0x0.9 - 0x0.9 */
	u_int8_t en_wol_psswd_magic;
	/* Description - Enable Wake on magic packet */
	/* 0x0.10 - 0x0.10 */
	u_int8_t en_wol_magic;
	/* Description - Enable Wake on ARP */
	/* 0x0.11 - 0x0.11 */
	u_int8_t en_wol_arp;
	/* Description - Enable Wake on broadcast message */
	/* 0x0.12 - 0x0.12 */
	u_int8_t en_wol_bc;
	/* Description - Enable Wake on multicast message */
	/* 0x0.13 - 0x0.13 */
	u_int8_t en_wol_mc;
	/* Description - Enable Wake on unicast message */
	/* 0x0.14 - 0x0.14 */
	u_int8_t en_wol_uc;
	/* Description - Enable Wake on PHY activity */
	/* 0x0.15 - 0x0.15 */
	u_int8_t en_wol_phy;
};

/* Description -   */
/* Size in bytes - 192 */
union tools_open_IbMads {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	union tools_open_smp_data smp;
};

/* Description -   */
/* Size in bytes - 512 */
union tools_open_access_registers {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Misc NV Registers, this is temporary untill we integrate with fw db */
	/* 0x0.0 - 0x168.31 */
	union tools_open_mnv_cfg MNVReg;
	/* Description - Register for accessing FW managed external PHY */
	/* 0x0.0 - 0x104.31 */
	union tools_open_phy_reg PhyReg;
};

/* Description -   */
/* Size in bytes - 256 */
union tools_open_aux_img_data {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - image aux data section header */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_aux_data_hdr aux_data_hdr;
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

/* Description -  Mellanox Firmware Archiver 2 */
/* Size in bytes - 32 */
union tools_open_mfa2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_common_header common_header;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_multi_part multi_part;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct tools_open_package_descriptor package_descriptor;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_component_desciptor component_desciptor;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_version version;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_component_ptr component_ptr;
};

/* Description -  MIRC register */
/* Size in bytes - 8 */
struct tools_open_mirc_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Statuses: 0 – success, 1 – busy, etc.  */
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
	/* 0x0.0 - 0x4.31 */
	struct tools_open_wol wol;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_infiniband_dc_capabilities infiniband_dc_capabilities;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_infiniband_dc_settings infiniband_dc_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_tpt_capabilities tpt_capabilities;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_tpt_configuration tpt_configuration;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct tools_open_pci_capabilities pci_capabilities;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_pci_configuration pci_configuration;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_port_boot_state port_boot_state;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_iscsi_settings iscsi_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_infiniband_boot_settings infiniband_boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_boot_settings boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_preboot_boot_settings preboot_boot_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_preboot_flow_ctrl preboot_flow_ctrl;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_sriov sriov;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_bar_size bar_size;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_vpi_settings vpi_settings;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_roce_v_1_5_next_protocol roce_v_1_5_next_protocol;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_roce_cc roce_cc;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	struct tools_open_roce_cc_ecn roce_cc_ecn;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct tools_open_lldp_nb lldp_nb;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_external_port external_port;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_boot_settings_ext boot_settings_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_option_rom_capability option_rom_capability;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_qos qos;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_qos_cap qos_cap;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_lldp_client_settings lldp_client_settings;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct tools_open_lldp_nb_cap lldp_nb_cap;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct tools_open_lldp_nb_dcbx lldp_nb_dcbx;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct tools_open_nv_base_mac_guid nv_base_mac_guid;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct tools_open_nv_base_mac_guid_cap nv_base_mac_guid_cap;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct tools_open_nv_cx3_global_conf nv_cx3_global_conf;
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
	/* Description - Ib Mads */
	/* 0x0.0 - 0xbc.31 */
	union tools_open_IbMads IbMads;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	union tools_open_mfa2 mfa2;
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
/* cap_mask */
void tools_open_cap_mask_pack(const struct tools_open_cap_mask *ptr_struct, u_int8_t *ptr_buff);
void tools_open_cap_mask_unpack(struct tools_open_cap_mask *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_cap_mask_print(const struct tools_open_cap_mask *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_cap_mask_size(void);
#define TOOLS_OPEN_CAP_MASK_SIZE    (0x4)
void tools_open_cap_mask_dump(const struct tools_open_cap_mask *ptr_struct, FILE *fd);
/* capability_mask_smp */
void tools_open_capability_mask_smp_pack(const struct tools_open_capability_mask_smp *ptr_struct, u_int8_t *ptr_buff);
void tools_open_capability_mask_smp_unpack(struct tools_open_capability_mask_smp *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_capability_mask_smp_print(const struct tools_open_capability_mask_smp *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_capability_mask_smp_size(void);
#define TOOLS_OPEN_CAPABILITY_MASK_SMP_SIZE    (0x40)
void tools_open_capability_mask_smp_dump(const struct tools_open_capability_mask_smp *ptr_struct, FILE *fd);
/* fw_info */
void tools_open_fw_info_pack(const struct tools_open_fw_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_fw_info_unpack(struct tools_open_fw_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_fw_info_print(const struct tools_open_fw_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_fw_info_size(void);
#define TOOLS_OPEN_FW_INFO_SIZE    (0x40)
void tools_open_fw_info_dump(const struct tools_open_fw_info *ptr_struct, FILE *fd);
/* hw_info */
void tools_open_hw_info_pack(const struct tools_open_hw_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_hw_info_unpack(struct tools_open_hw_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_hw_info_print(const struct tools_open_hw_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_hw_info_size(void);
#define TOOLS_OPEN_HW_INFO_SIZE    (0x20)
void tools_open_hw_info_dump(const struct tools_open_hw_info *ptr_struct, FILE *fd);
/* nv_hdr */
void tools_open_nv_hdr_pack(const struct tools_open_nv_hdr *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_hdr_unpack(struct tools_open_nv_hdr *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_hdr_print(const struct tools_open_nv_hdr *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_hdr_size(void);
#define TOOLS_OPEN_NV_HDR_SIZE    (0x8)
void tools_open_nv_hdr_dump(const struct tools_open_nv_hdr *ptr_struct, FILE *fd);
/* nv_hdr_fifth_gen */
void tools_open_nv_hdr_fifth_gen_pack(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_hdr_fifth_gen_unpack(struct tools_open_nv_hdr_fifth_gen *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_hdr_fifth_gen_print(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_hdr_fifth_gen_size(void);
#define TOOLS_OPEN_NV_HDR_FIFTH_GEN_SIZE    (0xc)
void tools_open_nv_hdr_fifth_gen_dump(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd);
/* pmdio_addr_data */
void tools_open_pmdio_addr_data_pack(const struct tools_open_pmdio_addr_data *ptr_struct, u_int8_t *ptr_buff);
void tools_open_pmdio_addr_data_unpack(struct tools_open_pmdio_addr_data *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_pmdio_addr_data_print(const struct tools_open_pmdio_addr_data *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_pmdio_addr_data_size(void);
#define TOOLS_OPEN_PMDIO_ADDR_DATA_SIZE    (0x4)
void tools_open_pmdio_addr_data_dump(const struct tools_open_pmdio_addr_data *ptr_struct, FILE *fd);
/* sw_info */
void tools_open_sw_info_pack(const struct tools_open_sw_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_sw_info_unpack(struct tools_open_sw_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_sw_info_print(const struct tools_open_sw_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_sw_info_size(void);
#define TOOLS_OPEN_SW_INFO_SIZE    (0x20)
void tools_open_sw_info_dump(const struct tools_open_sw_info *ptr_struct, FILE *fd);
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
/* extended_ib_port_info */
void tools_open_extended_ib_port_info_pack(const struct tools_open_extended_ib_port_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_extended_ib_port_info_unpack(struct tools_open_extended_ib_port_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_extended_ib_port_info_print(const struct tools_open_extended_ib_port_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_extended_ib_port_info_size(void);
#define TOOLS_OPEN_EXTENDED_IB_PORT_INFO_SIZE    (0x3c)
void tools_open_extended_ib_port_info_dump(const struct tools_open_extended_ib_port_info *ptr_struct, FILE *fd);
/* ib_port_info */
void tools_open_ib_port_info_pack(const struct tools_open_ib_port_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_ib_port_info_unpack(struct tools_open_ib_port_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_ib_port_info_print(const struct tools_open_ib_port_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_ib_port_info_size(void);
#define TOOLS_OPEN_IB_PORT_INFO_SIZE    (0x40)
void tools_open_ib_port_info_dump(const struct tools_open_ib_port_info *ptr_struct, FILE *fd);
/* mcam */
void tools_open_mcam_pack(const struct tools_open_mcam *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mcam_unpack(struct tools_open_mcam *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mcam_print(const struct tools_open_mcam *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mcam_size(void);
#define TOOLS_OPEN_MCAM_SIZE    (0x48)
void tools_open_mcam_dump(const struct tools_open_mcam *ptr_struct, FILE *fd);
/* mfmc */
void tools_open_mfmc_pack(const struct tools_open_mfmc *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mfmc_unpack(struct tools_open_mfmc *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mfmc_print(const struct tools_open_mfmc *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mfmc_size(void);
#define TOOLS_OPEN_MFMC_SIZE    (0x1c)
void tools_open_mfmc_dump(const struct tools_open_mfmc *ptr_struct, FILE *fd);
/* mfpa */
void tools_open_mfpa_pack(const struct tools_open_mfpa *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mfpa_unpack(struct tools_open_mfpa *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mfpa_print(const struct tools_open_mfpa *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mfpa_size(void);
#define TOOLS_OPEN_MFPA_SIZE    (0x20)
void tools_open_mfpa_dump(const struct tools_open_mfpa *ptr_struct, FILE *fd);
/* mgir */
void tools_open_mgir_pack(const struct tools_open_mgir *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mgir_unpack(struct tools_open_mgir *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mgir_print(const struct tools_open_mgir *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mgir_size(void);
#define TOOLS_OPEN_MGIR_SIZE    (0x80)
void tools_open_mgir_dump(const struct tools_open_mgir *ptr_struct, FILE *fd);
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
/* mnva */
void tools_open_mnva_pack(const struct tools_open_mnva *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnva_unpack(struct tools_open_mnva *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnva_print(const struct tools_open_mnva *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnva_size(void);
#define TOOLS_OPEN_MNVA_SIZE    (0x100)
void tools_open_mnva_dump(const struct tools_open_mnva *ptr_struct, FILE *fd);
/* mnvgn */
void tools_open_mnvgn_pack(const struct tools_open_mnvgn *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnvgn_unpack(struct tools_open_mnvgn *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnvgn_print(const struct tools_open_mnvgn *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnvgn_size(void);
#define TOOLS_OPEN_MNVGN_SIZE    (0x9c)
void tools_open_mnvgn_dump(const struct tools_open_mnvgn *ptr_struct, FILE *fd);
/* mnvi */
void tools_open_mnvi_pack(const struct tools_open_mnvi *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnvi_unpack(struct tools_open_mnvi *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnvi_print(const struct tools_open_mnvi *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnvi_size(void);
#define TOOLS_OPEN_MNVI_SIZE    (0x8)
void tools_open_mnvi_dump(const struct tools_open_mnvi *ptr_struct, FILE *fd);
/* mnvia */
void tools_open_mnvia_pack(const struct tools_open_mnvia *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mnvia_unpack(struct tools_open_mnvia *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mnvia_print(const struct tools_open_mnvia *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mnvia_size(void);
#define TOOLS_OPEN_MNVIA_SIZE    (0x8)
void tools_open_mnvia_dump(const struct tools_open_mnvia *ptr_struct, FILE *fd);
/* mvts */
void tools_open_mvts_pack(const struct tools_open_mvts *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mvts_unpack(struct tools_open_mvts *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mvts_print(const struct tools_open_mvts *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mvts_size(void);
#define TOOLS_OPEN_MVTS_SIZE    (0x14)
void tools_open_mvts_dump(const struct tools_open_mvts *ptr_struct, FILE *fd);
/* node_info */
void tools_open_node_info_pack(const struct tools_open_node_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_node_info_unpack(struct tools_open_node_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_node_info_print(const struct tools_open_node_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_node_info_size(void);
#define TOOLS_OPEN_NODE_INFO_SIZE    (0x40)
void tools_open_node_info_dump(const struct tools_open_node_info *ptr_struct, FILE *fd);
/* nvda */
void tools_open_nvda_pack(const struct tools_open_nvda *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nvda_unpack(struct tools_open_nvda *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nvda_print(const struct tools_open_nvda *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nvda_size(void);
#define TOOLS_OPEN_NVDA_SIZE    (0x10c)
void tools_open_nvda_dump(const struct tools_open_nvda *ptr_struct, FILE *fd);
/* nvdi */
void tools_open_nvdi_pack(const struct tools_open_nvdi *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nvdi_unpack(struct tools_open_nvdi *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nvdi_print(const struct tools_open_nvdi *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nvdi_size(void);
#define TOOLS_OPEN_NVDI_SIZE    (0xc)
void tools_open_nvdi_dump(const struct tools_open_nvdi *ptr_struct, FILE *fd);
/* nvia */
void tools_open_nvia_pack(const struct tools_open_nvia *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nvia_unpack(struct tools_open_nvia *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nvia_print(const struct tools_open_nvia *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nvia_size(void);
#define TOOLS_OPEN_NVIA_SIZE    (0x8)
void tools_open_nvia_dump(const struct tools_open_nvia *ptr_struct, FILE *fd);
/* nvqc */
void tools_open_nvqc_pack(const struct tools_open_nvqc *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nvqc_unpack(struct tools_open_nvqc *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nvqc_print(const struct tools_open_nvqc *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nvqc_size(void);
#define TOOLS_OPEN_NVQC_SIZE    (0x8)
void tools_open_nvqc_dump(const struct tools_open_nvqc *ptr_struct, FILE *fd);
/* nvqgc */
void tools_open_nvqgc_pack(const struct tools_open_nvqgc *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nvqgc_unpack(struct tools_open_nvqgc *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nvqgc_print(const struct tools_open_nvqgc *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nvqgc_size(void);
#define TOOLS_OPEN_NVQGC_SIZE    (0x10)
void tools_open_nvqgc_dump(const struct tools_open_nvqgc *ptr_struct, FILE *fd);
/* pmdic */
void tools_open_pmdic_pack(const struct tools_open_pmdic *ptr_struct, u_int8_t *ptr_buff);
void tools_open_pmdic_unpack(struct tools_open_pmdic *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_pmdic_print(const struct tools_open_pmdic *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_pmdic_size(void);
#define TOOLS_OPEN_PMDIC_SIZE    (0xc)
void tools_open_pmdic_dump(const struct tools_open_pmdic *ptr_struct, FILE *fd);
/* pmdio */
void tools_open_pmdio_pack(const struct tools_open_pmdio *ptr_struct, u_int8_t *ptr_buff);
void tools_open_pmdio_unpack(struct tools_open_pmdio *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_pmdio_print(const struct tools_open_pmdio *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_pmdio_size(void);
#define TOOLS_OPEN_PMDIO_SIZE    (0x108)
void tools_open_pmdio_dump(const struct tools_open_pmdio *ptr_struct, FILE *fd);
/* smp_vsp_general_info */
void tools_open_smp_vsp_general_info_pack(const union tools_open_smp_vsp_general_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_smp_vsp_general_info_unpack(union tools_open_smp_vsp_general_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_smp_vsp_general_info_print(const union tools_open_smp_vsp_general_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_smp_vsp_general_info_size(void);
#define TOOLS_OPEN_SMP_VSP_GENERAL_INFO_SIZE    (0x40)
void tools_open_smp_vsp_general_info_dump(const union tools_open_smp_vsp_general_info *ptr_struct, FILE *fd);
/* aux_data_hdr */
void tools_open_aux_data_hdr_pack(const struct tools_open_aux_data_hdr *ptr_struct, u_int8_t *ptr_buff);
void tools_open_aux_data_hdr_unpack(struct tools_open_aux_data_hdr *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_aux_data_hdr_print(const struct tools_open_aux_data_hdr *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_aux_data_hdr_size(void);
#define TOOLS_OPEN_AUX_DATA_HDR_SIZE    (0x10)
void tools_open_aux_data_hdr_dump(const struct tools_open_aux_data_hdr *ptr_struct, FILE *fd);
/* aux_tlv */
void tools_open_aux_tlv_pack(const struct tools_open_aux_tlv *ptr_struct, u_int8_t *ptr_buff);
void tools_open_aux_tlv_unpack(struct tools_open_aux_tlv *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_aux_tlv_print(const struct tools_open_aux_tlv *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_aux_tlv_size(void);
#define TOOLS_OPEN_AUX_TLV_SIZE    (0x100)
void tools_open_aux_tlv_dump(const struct tools_open_aux_tlv *ptr_struct, FILE *fd);
/* bar_size */
void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t *ptr_buff);
void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_bar_size_size(void);
#define TOOLS_OPEN_BAR_SIZE_SIZE    (0x4)
void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE *fd);
/* boot_settings */
void tools_open_boot_settings_pack(const struct tools_open_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_boot_settings_unpack(struct tools_open_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_boot_settings_print(const struct tools_open_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_boot_settings_size(void);
#define TOOLS_OPEN_BOOT_SETTINGS_SIZE    (0x4)
void tools_open_boot_settings_dump(const struct tools_open_boot_settings *ptr_struct, FILE *fd);
/* boot_settings_ext */
void tools_open_boot_settings_ext_pack(const struct tools_open_boot_settings_ext *ptr_struct, u_int8_t *ptr_buff);
void tools_open_boot_settings_ext_unpack(struct tools_open_boot_settings_ext *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_boot_settings_ext_print(const struct tools_open_boot_settings_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_boot_settings_ext_size(void);
#define TOOLS_OPEN_BOOT_SETTINGS_EXT_SIZE    (0x4)
void tools_open_boot_settings_ext_dump(const struct tools_open_boot_settings_ext *ptr_struct, FILE *fd);
/* common_header */
void tools_open_common_header_pack(const struct tools_open_common_header *ptr_struct, u_int8_t *ptr_buff);
void tools_open_common_header_unpack(struct tools_open_common_header *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_common_header_print(const struct tools_open_common_header *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_common_header_size(void);
#define TOOLS_OPEN_COMMON_HEADER_SIZE    (0x4)
void tools_open_common_header_dump(const struct tools_open_common_header *ptr_struct, FILE *fd);
/* component_desciptor */
void tools_open_component_desciptor_pack(const struct tools_open_component_desciptor *ptr_struct, u_int8_t *ptr_buff);
void tools_open_component_desciptor_unpack(struct tools_open_component_desciptor *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_component_desciptor_print(const struct tools_open_component_desciptor *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_component_desciptor_size(void);
#define TOOLS_OPEN_COMPONENT_DESCIPTOR_SIZE    (0x10)
void tools_open_component_desciptor_dump(const struct tools_open_component_desciptor *ptr_struct, FILE *fd);
/* component_ptr */
void tools_open_component_ptr_pack(const struct tools_open_component_ptr *ptr_struct, u_int8_t *ptr_buff);
void tools_open_component_ptr_unpack(struct tools_open_component_ptr *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_component_ptr_print(const struct tools_open_component_ptr *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_component_ptr_size(void);
#define TOOLS_OPEN_COMPONENT_PTR_SIZE    (0x8)
void tools_open_component_ptr_dump(const struct tools_open_component_ptr *ptr_struct, FILE *fd);
/* external_port */
void tools_open_external_port_pack(const struct tools_open_external_port *ptr_struct, u_int8_t *ptr_buff);
void tools_open_external_port_unpack(struct tools_open_external_port *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_external_port_print(const struct tools_open_external_port *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_external_port_size(void);
#define TOOLS_OPEN_EXTERNAL_PORT_SIZE    (0x8)
void tools_open_external_port_dump(const struct tools_open_external_port *ptr_struct, FILE *fd);
/* image_info */
void tools_open_image_info_pack(const struct tools_open_image_info *ptr_struct, u_int8_t *ptr_buff);
void tools_open_image_info_unpack(struct tools_open_image_info *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_image_info_print(const struct tools_open_image_info *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_image_info_size(void);
#define TOOLS_OPEN_IMAGE_INFO_SIZE    (0x400)
void tools_open_image_info_dump(const struct tools_open_image_info *ptr_struct, FILE *fd);
/* infiniband_boot_settings */
void tools_open_infiniband_boot_settings_pack(const struct tools_open_infiniband_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_infiniband_boot_settings_unpack(struct tools_open_infiniband_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_infiniband_boot_settings_print(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_infiniband_boot_settings_size(void);
#define TOOLS_OPEN_INFINIBAND_BOOT_SETTINGS_SIZE    (0x4)
void tools_open_infiniband_boot_settings_dump(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE *fd);
/* infiniband_dc_capabilities */
void tools_open_infiniband_dc_capabilities_pack(const struct tools_open_infiniband_dc_capabilities *ptr_struct, u_int8_t *ptr_buff);
void tools_open_infiniband_dc_capabilities_unpack(struct tools_open_infiniband_dc_capabilities *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_infiniband_dc_capabilities_print(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_infiniband_dc_capabilities_size(void);
#define TOOLS_OPEN_INFINIBAND_DC_CAPABILITIES_SIZE    (0x10)
void tools_open_infiniband_dc_capabilities_dump(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE *fd);
/* infiniband_dc_settings */
void tools_open_infiniband_dc_settings_pack(const struct tools_open_infiniband_dc_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_infiniband_dc_settings_unpack(struct tools_open_infiniband_dc_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_infiniband_dc_settings_print(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_infiniband_dc_settings_size(void);
#define TOOLS_OPEN_INFINIBAND_DC_SETTINGS_SIZE    (0x8)
void tools_open_infiniband_dc_settings_dump(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE *fd);
/* iscsi_settings */
void tools_open_iscsi_settings_pack(const struct tools_open_iscsi_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_iscsi_settings_unpack(struct tools_open_iscsi_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_iscsi_settings_print(const struct tools_open_iscsi_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_iscsi_settings_size(void);
#define TOOLS_OPEN_ISCSI_SETTINGS_SIZE    (0xc)
void tools_open_iscsi_settings_dump(const struct tools_open_iscsi_settings *ptr_struct, FILE *fd);
/* lldp_client_settings */
void tools_open_lldp_client_settings_pack(const struct tools_open_lldp_client_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_lldp_client_settings_unpack(struct tools_open_lldp_client_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_lldp_client_settings_print(const struct tools_open_lldp_client_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_lldp_client_settings_size(void);
#define TOOLS_OPEN_LLDP_CLIENT_SETTINGS_SIZE    (0xc)
void tools_open_lldp_client_settings_dump(const struct tools_open_lldp_client_settings *ptr_struct, FILE *fd);
/* lldp_nb */
void tools_open_lldp_nb_pack(const struct tools_open_lldp_nb *ptr_struct, u_int8_t *ptr_buff);
void tools_open_lldp_nb_unpack(struct tools_open_lldp_nb *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_lldp_nb_print(const struct tools_open_lldp_nb *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_lldp_nb_size(void);
#define TOOLS_OPEN_LLDP_NB_SIZE    (0x1c)
void tools_open_lldp_nb_dump(const struct tools_open_lldp_nb *ptr_struct, FILE *fd);
/* lldp_nb_cap */
void tools_open_lldp_nb_cap_pack(const struct tools_open_lldp_nb_cap *ptr_struct, u_int8_t *ptr_buff);
void tools_open_lldp_nb_cap_unpack(struct tools_open_lldp_nb_cap *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_lldp_nb_cap_print(const struct tools_open_lldp_nb_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_lldp_nb_cap_size(void);
#define TOOLS_OPEN_LLDP_NB_CAP_SIZE    (0xc)
void tools_open_lldp_nb_cap_dump(const struct tools_open_lldp_nb_cap *ptr_struct, FILE *fd);
/* lldp_nb_dcbx */
void tools_open_lldp_nb_dcbx_pack(const struct tools_open_lldp_nb_dcbx *ptr_struct, u_int8_t *ptr_buff);
void tools_open_lldp_nb_dcbx_unpack(struct tools_open_lldp_nb_dcbx *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_lldp_nb_dcbx_print(const struct tools_open_lldp_nb_dcbx *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_lldp_nb_dcbx_size(void);
#define TOOLS_OPEN_LLDP_NB_DCBX_SIZE    (0x4)
void tools_open_lldp_nb_dcbx_dump(const struct tools_open_lldp_nb_dcbx *ptr_struct, FILE *fd);
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
/* multi_part */
void tools_open_multi_part_pack(const struct tools_open_multi_part *ptr_struct, u_int8_t *ptr_buff);
void tools_open_multi_part_unpack(struct tools_open_multi_part *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_multi_part_print(const struct tools_open_multi_part *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_multi_part_size(void);
#define TOOLS_OPEN_MULTI_PART_SIZE    (0x4)
void tools_open_multi_part_dump(const struct tools_open_multi_part *ptr_struct, FILE *fd);
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
/* nv_cx3_global_conf */
void tools_open_nv_cx3_global_conf_pack(const struct tools_open_nv_cx3_global_conf *ptr_struct, u_int8_t *ptr_buff);
void tools_open_nv_cx3_global_conf_unpack(struct tools_open_nv_cx3_global_conf *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_nv_cx3_global_conf_print(const struct tools_open_nv_cx3_global_conf *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_nv_cx3_global_conf_size(void);
#define TOOLS_OPEN_NV_CX3_GLOBAL_CONF_SIZE    (0x20)
void tools_open_nv_cx3_global_conf_dump(const struct tools_open_nv_cx3_global_conf *ptr_struct, FILE *fd);
/* option_rom_capability */
void tools_open_option_rom_capability_pack(const struct tools_open_option_rom_capability *ptr_struct, u_int8_t *ptr_buff);
void tools_open_option_rom_capability_unpack(struct tools_open_option_rom_capability *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_option_rom_capability_print(const struct tools_open_option_rom_capability *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_option_rom_capability_size(void);
#define TOOLS_OPEN_OPTION_ROM_CAPABILITY_SIZE    (0x4)
void tools_open_option_rom_capability_dump(const struct tools_open_option_rom_capability *ptr_struct, FILE *fd);
/* package_descriptor */
void tools_open_package_descriptor_pack(const struct tools_open_package_descriptor *ptr_struct, u_int8_t *ptr_buff);
void tools_open_package_descriptor_unpack(struct tools_open_package_descriptor *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_package_descriptor_print(const struct tools_open_package_descriptor *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_package_descriptor_size(void);
#define TOOLS_OPEN_PACKAGE_DESCRIPTOR_SIZE    (0x1c)
void tools_open_package_descriptor_dump(const struct tools_open_package_descriptor *ptr_struct, FILE *fd);
/* pci_capabilities */
void tools_open_pci_capabilities_pack(const struct tools_open_pci_capabilities *ptr_struct, u_int8_t *ptr_buff);
void tools_open_pci_capabilities_unpack(struct tools_open_pci_capabilities *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_pci_capabilities_print(const struct tools_open_pci_capabilities *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_pci_capabilities_size(void);
#define TOOLS_OPEN_PCI_CAPABILITIES_SIZE    (0x14)
void tools_open_pci_capabilities_dump(const struct tools_open_pci_capabilities *ptr_struct, FILE *fd);
/* pci_configuration */
void tools_open_pci_configuration_pack(const struct tools_open_pci_configuration *ptr_struct, u_int8_t *ptr_buff);
void tools_open_pci_configuration_unpack(struct tools_open_pci_configuration *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_pci_configuration_print(const struct tools_open_pci_configuration *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_pci_configuration_size(void);
#define TOOLS_OPEN_PCI_CONFIGURATION_SIZE    (0xc)
void tools_open_pci_configuration_dump(const struct tools_open_pci_configuration *ptr_struct, FILE *fd);
/* phy_reg */
void tools_open_phy_reg_pack(const union tools_open_phy_reg *ptr_struct, u_int8_t *ptr_buff);
void tools_open_phy_reg_unpack(union tools_open_phy_reg *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_phy_reg_print(const union tools_open_phy_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_phy_reg_size(void);
#define TOOLS_OPEN_PHY_REG_SIZE    (0x108)
void tools_open_phy_reg_dump(const union tools_open_phy_reg *ptr_struct, FILE *fd);
/* port_boot_state */
void tools_open_port_boot_state_pack(const struct tools_open_port_boot_state *ptr_struct, u_int8_t *ptr_buff);
void tools_open_port_boot_state_unpack(struct tools_open_port_boot_state *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_port_boot_state_print(const struct tools_open_port_boot_state *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_port_boot_state_size(void);
#define TOOLS_OPEN_PORT_BOOT_STATE_SIZE    (0x4)
void tools_open_port_boot_state_dump(const struct tools_open_port_boot_state *ptr_struct, FILE *fd);
/* preboot_boot_settings */
void tools_open_preboot_boot_settings_pack(const struct tools_open_preboot_boot_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_preboot_boot_settings_unpack(struct tools_open_preboot_boot_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_preboot_boot_settings_print(const struct tools_open_preboot_boot_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_preboot_boot_settings_size(void);
#define TOOLS_OPEN_PREBOOT_BOOT_SETTINGS_SIZE    (0x4)
void tools_open_preboot_boot_settings_dump(const struct tools_open_preboot_boot_settings *ptr_struct, FILE *fd);
/* preboot_flow_ctrl */
void tools_open_preboot_flow_ctrl_pack(const struct tools_open_preboot_flow_ctrl *ptr_struct, u_int8_t *ptr_buff);
void tools_open_preboot_flow_ctrl_unpack(struct tools_open_preboot_flow_ctrl *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_preboot_flow_ctrl_print(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_preboot_flow_ctrl_size(void);
#define TOOLS_OPEN_PREBOOT_FLOW_CTRL_SIZE    (0x4)
void tools_open_preboot_flow_ctrl_dump(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE *fd);
/* qos */
void tools_open_qos_pack(const struct tools_open_qos *ptr_struct, u_int8_t *ptr_buff);
void tools_open_qos_unpack(struct tools_open_qos *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_qos_print(const struct tools_open_qos *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_qos_size(void);
#define TOOLS_OPEN_QOS_SIZE    (0xc)
void tools_open_qos_dump(const struct tools_open_qos *ptr_struct, FILE *fd);
/* qos_cap */
void tools_open_qos_cap_pack(const struct tools_open_qos_cap *ptr_struct, u_int8_t *ptr_buff);
void tools_open_qos_cap_unpack(struct tools_open_qos_cap *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_qos_cap_print(const struct tools_open_qos_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_qos_cap_size(void);
#define TOOLS_OPEN_QOS_CAP_SIZE    (0xc)
void tools_open_qos_cap_dump(const struct tools_open_qos_cap *ptr_struct, FILE *fd);
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
/* roce_cc */
void tools_open_roce_cc_pack(const struct tools_open_roce_cc *ptr_struct, u_int8_t *ptr_buff);
void tools_open_roce_cc_unpack(struct tools_open_roce_cc *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_roce_cc_print(const struct tools_open_roce_cc *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_roce_cc_size(void);
#define TOOLS_OPEN_ROCE_CC_SIZE    (0x4)
void tools_open_roce_cc_dump(const struct tools_open_roce_cc *ptr_struct, FILE *fd);
/* roce_cc_ecn */
void tools_open_roce_cc_ecn_pack(const struct tools_open_roce_cc_ecn *ptr_struct, u_int8_t *ptr_buff);
void tools_open_roce_cc_ecn_unpack(struct tools_open_roce_cc_ecn *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_roce_cc_ecn_print(const struct tools_open_roce_cc_ecn *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_roce_cc_ecn_size(void);
#define TOOLS_OPEN_ROCE_CC_ECN_SIZE    (0x44)
void tools_open_roce_cc_ecn_dump(const struct tools_open_roce_cc_ecn *ptr_struct, FILE *fd);
/* roce_v_1_5_next_protocol */
void tools_open_roce_v_1_5_next_protocol_pack(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, u_int8_t *ptr_buff);
void tools_open_roce_v_1_5_next_protocol_unpack(struct tools_open_roce_v_1_5_next_protocol *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_roce_v_1_5_next_protocol_print(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_roce_v_1_5_next_protocol_size(void);
#define TOOLS_OPEN_ROCE_V_1_5_NEXT_PROTOCOL_SIZE    (0x4)
void tools_open_roce_v_1_5_next_protocol_dump(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE *fd);
/* smp_data */
void tools_open_smp_data_pack(const union tools_open_smp_data *ptr_struct, u_int8_t *ptr_buff);
void tools_open_smp_data_unpack(union tools_open_smp_data *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_smp_data_print(const union tools_open_smp_data *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_smp_data_size(void);
#define TOOLS_OPEN_SMP_DATA_SIZE    (0x40)
void tools_open_smp_data_dump(const union tools_open_smp_data *ptr_struct, FILE *fd);
/* sriov */
void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t *ptr_buff);
void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_sriov_size(void);
#define TOOLS_OPEN_SRIOV_SIZE    (0x4)
void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE *fd);
/* tpt_capabilities */
void tools_open_tpt_capabilities_pack(const struct tools_open_tpt_capabilities *ptr_struct, u_int8_t *ptr_buff);
void tools_open_tpt_capabilities_unpack(struct tools_open_tpt_capabilities *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_tpt_capabilities_print(const struct tools_open_tpt_capabilities *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_tpt_capabilities_size(void);
#define TOOLS_OPEN_TPT_CAPABILITIES_SIZE    (0x4)
void tools_open_tpt_capabilities_dump(const struct tools_open_tpt_capabilities *ptr_struct, FILE *fd);
/* tpt_configuration */
void tools_open_tpt_configuration_pack(const struct tools_open_tpt_configuration *ptr_struct, u_int8_t *ptr_buff);
void tools_open_tpt_configuration_unpack(struct tools_open_tpt_configuration *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_tpt_configuration_print(const struct tools_open_tpt_configuration *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_tpt_configuration_size(void);
#define TOOLS_OPEN_TPT_CONFIGURATION_SIZE    (0x4)
void tools_open_tpt_configuration_dump(const struct tools_open_tpt_configuration *ptr_struct, FILE *fd);
/* version */
void tools_open_version_pack(const struct tools_open_version *ptr_struct, u_int8_t *ptr_buff);
void tools_open_version_unpack(struct tools_open_version *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_version_print(const struct tools_open_version *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_version_size(void);
#define TOOLS_OPEN_VERSION_SIZE    (0xc)
void tools_open_version_dump(const struct tools_open_version *ptr_struct, FILE *fd);
/* vpi_settings */
void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t *ptr_buff);
void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_vpi_settings_size(void);
#define TOOLS_OPEN_VPI_SETTINGS_SIZE    (0x4)
void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE *fd);
/* wol */
void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t *ptr_buff);
void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_wol_size(void);
#define TOOLS_OPEN_WOL_SIZE    (0x8)
void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE *fd);
/* IbMads */
void tools_open_IbMads_pack(const union tools_open_IbMads *ptr_struct, u_int8_t *ptr_buff);
void tools_open_IbMads_unpack(union tools_open_IbMads *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_IbMads_print(const union tools_open_IbMads *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_IbMads_size(void);
#define TOOLS_OPEN_IBMADS_SIZE    (0xc0)
void tools_open_IbMads_dump(const union tools_open_IbMads *ptr_struct, FILE *fd);
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
/* mfa2 */
void tools_open_mfa2_pack(const union tools_open_mfa2 *ptr_struct, u_int8_t *ptr_buff);
void tools_open_mfa2_unpack(union tools_open_mfa2 *ptr_struct, const u_int8_t *ptr_buff);
void tools_open_mfa2_print(const union tools_open_mfa2 *ptr_struct, FILE *fd, int indent_level);
unsigned int tools_open_mfa2_size(void);
#define TOOLS_OPEN_MFA2_SIZE    (0x20)
void tools_open_mfa2_dump(const union tools_open_mfa2 *ptr_struct, FILE *fd);
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
