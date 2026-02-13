
/*
* Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
*
*  Version: $Id$
*
*/
 

/***
         *** This file was generated at "2025-12-18 11:34:59"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/tools/icmd_hca.adb --file-prefix icmd_hca --prefix icmd_hca_ --no-adb-utils
         ***/
#ifndef ICMD_HCA_LAYOUTS_H
#define ICMD_HCA_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 4 */
struct icmd_hca_counter_id {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t counter_id;
};

/* Description -   */
/* Size in bytes - 4 */
struct icmd_hca_diagnostic_cntr_layout {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Diagnostic counter identifier. */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t counter_id;
	/* Description - The counter might be used as Synced Start Diagnostics Counters */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t sync;
};

/* Description -   */
/* Size in bytes - 24 */
struct icmd_hca_diagnostic_params_context {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of samples to store on the device's sampling buffer is 2^ log_number_of_samples. Range is 1   floor(DIAG_CNT_CAP. log_max_samples_mul_counters /DIAG_CNT_SET. num_of_counters)
Note that modifying this field will cause resetting the sampling buffer.
	*/
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t log_num_of_samples;
	/* Description - Number of valid counters to be captured in the list below. */
	/* 0x0.16 - 0x0.31 */
	/* access: RW */
	u_int16_t num_of_counters;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The sample_period is 2^ log_sample_period in device clocks. Range is diagnostic Capabilities Layout.Min_sample_period   35 (85 sec in 400 MHz clock) */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t log_sample_period;
	/* Description - If set, the diagnostic counter report will be logged in the tracer buffer. */
	/* 0x4.25 - 0x4.25 */
	/* access: RW */
	u_int8_t tracer_dump;
	/* Description - 0x1: Enable - enables diagnostic counting.
0x0: Disable - disables diagnostic counting. */
	/* 0x4.26 - 0x4.26 */
	/* access: RW */
	u_int8_t enable;
	/* Description - If set, the device does not collect samples. Upon QUERY_DIAGNOSTIC command, the device will fetch current sample. "on demand" mode is mutually exclusive with "repetitive", "clear" and "sync" modes and cannot be set together */
	/* 0x4.27 - 0x4.27 */
	/* access: RW */
	u_int8_t on_demand;
	/* Description - Clear counters at the beginning of each period. Valid only for Synched Start Diagnostic Counters, only when sync is set to '1'.
Clear is mutually exclusive with "on demand". */
	/* 0x4.28 - 0x4.28 */
	/* access: RW */
	u_int8_t clear;
	/* Description - Use Synched Start counting on Diagnostics Counters that support sync operation. 
Sync is mutually exclusive with "on demand". */
	/* 0x4.29 - 0x4.29 */
	/* access: RW */
	u_int8_t sync;
	/* Description - Repetitive sampling mode. Available only when HCA-CAP.repetitive is '1'
Mutually exclusive with "single" mode and on_demand mode. */
	/* 0x4.30 - 0x4.30 */
	/* access: RW */
	u_int8_t repetitive;
	/* Description - Single sampling mode. Available only when HCA_CAP.single is '1'.
Mutually exclusive with "repetitive" mode. */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t single;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Counter ids to capture. */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	struct icmd_hca_counter_id *counter_id;
};

/* Description -   */
/* Size in bytes - 64 */
struct icmd_hca_debug_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The maximum number of samples that can be stored on the device's sampling buffer is 2^ log_max_samples in counters unit (i.e. 100 will represent the ability to store 100 samples of single counter, 50 samples of 2 counters, etc). */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t log_max_samples;
	/* Description - Log(base 2) of the the recommended minimal size of eq to handle the resource_dump_event */
	/* 0x0.16 - 0x0.20 */
	/* access: RW */
	u_int8_t log_min_resource_dump_eq;
	/* Description - If set, Resource_dump register is supported.
See Table  1797, "RESOURCE_DUMP Register Layout," on page  2124 */
	/* 0x0.22 - 0x0.22 */
	/* access: RW */
	u_int8_t resource_dump;
	/* Description - Log(base 2) of the size in granularity of 4KB to be allocated by host in order to accommodate cr_dump.
0 means feature is not supported.
See Table  1795, "CORE_DUMP Register Layout," on page  2122 */
	/* 0x0.23 - 0x0.27 */
	/* access: RW */
	u_int8_t log_cr_dump_to_mem_size;
	/* Description - If set, Core dump of type of specific QP is supported.
	*/
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t core_dump_qp;
	/* Description - If set, Core dump of type "General" is supported. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t core_dump_general;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The minimal sample period is 2^ log_min_smaple_period in device clocks. Clock rate of the device is reported by HCA_CAP.device_frequency_khz. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t log_min_sample_period;
	/* Description - If set, the device supports dumping the diagnostic counters reports into the tracer buffer. */
	/* 0x4.28 - 0x4.28 */
	/* access: RW */
	u_int8_t diag_counter_tracer_dump;
	/* Description - If set, health monitoring for rx path activity is supported.
See Table  29.5.1, "RX Path Activity," on page  2011 */
	/* 0x4.29 - 0x4.29 */
	/* access: RW */
	u_int8_t health_mon_rx_activity;
	/* Description - Repetitive sampling mode is supported */
	/* 0x4.30 - 0x4.30 */
	/* access: RW */
	u_int8_t repetitive;
	/* Description - Single sampling mode is supported */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t single;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - List of counters supported. Number of counters reported by num_of_counters. */
	/* 0x40.0 - 0x40.31 */
	/* access: RW */
	struct icmd_hca_diagnostic_cntr_layout *diagnostic_counter;
};

/* Description -   */
/* Size in bytes - 4 */
struct icmd_hca_icmd_mh_sync_in {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Next state for the synchronization state machine:
0x0: IDLE
0x1: GET_READY
0x2: GO
Other values are reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t state;
	/* Description - The operation currently being synchronized:
0x1: FW_RESET
other values are reserved */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t sync_type;
	/* Description - When set, hosts in reset state (PERST# low) are ignored (not synchronized) */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t ignore_inactive_host;
};

/* Description -   */
/* Size in bytes - 12 */
struct icmd_hca_icmd_mh_sync_out {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Current state of the synchronization state machine:
0x0: IDLE
0x1: GET_READY
0x2: GO
Other values are reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t state;
	/* Description - The operation currently being synchronized:
0x1: FW_RESET
other values are reserved */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t sync_type;
	/* Description - When set, hosts in reset state (PERST# low) are ignored (not synchronized) */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t ignore_inactive_host;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Current state of the host acknowledgement process
0x0: IDLE - no host ack
0x1: READY - sync in progress
0xF: GO - all hosts ack
Other values are reserved */
	/* 0x4.0 - 0x4.3 */
	/* access: RW */
	u_int8_t host_ready;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - NIC uptime (time since last reset) in microseconds, at the moment the synchronization state machine entered the GET_READY state. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t start_uptime;
};

/* Description -   */
/* Size in bytes - 8 */
struct icmd_hca_icmd_query_cap_general {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, NIC_CAP_REG register is supported. */
	/* 0x0.13 - 0x0.13 */
	/* access: RW */
	u_int8_t nic_cap_reg;
	/* Description - If set, port_state_behavior register is supported.
See Section 30.2.27, "PORT_STATE_BEHAVIOR Register", on page 2135 */
	/* 0x0.14 - 0x0.14 */
	/* access: RW */
	u_int8_t port_state_behavior;
	/* Description - When set, virtual node GUID can be set/queried using ICMD_SET/QUERY_VIRTUAL_MAC */
	/* 0x0.15 - 0x0.15 */
	/* access: RW */
	u_int8_t virt_node_guid;
	/* Description - If set, NCFG register is supported. */
	/* 0x0.16 - 0x0.16 */
	/* access: RW */
	u_int8_t ncfg_reg;
	/* Description - If set, CWCAM register is supported. Table 2643, "CWCAM - Congestion WRED Capabilities Mask Register Layout," on page 3118 */
	/* 0x0.17 - 0x0.17 */
	/* access: RW */
	u_int8_t cwcam_reg;
	/* Description - If set, SBCAM register is supported. See Table 2660, "SBCAM - Shared Buffer Capabilities Mask Register Layout," on page 3138 */
	/* 0x0.18 - 0x0.18 */
	/* access: RW */
	u_int8_t sbcam_reg;
	/* Description - When set, the command supports capability groups in addition to the General Capability group */
	/* 0x0.20 - 0x0.20 */
	/* access: RW */
	u_int8_t capability_groups;
	/* Description - When set, the device supports emulating link down for all the associated functions using "ICMD_SET_VIRTUAL_PARAMETERS - Set Device Virtual Parameters" */
	/* 0x0.22 - 0x0.22 */
	/* access: RW */
	u_int8_t virtual_link_down;
	/* Description - When set, the device supports using a memory buffer as a mailbox for the ICMD, instead of the normal ICMD Mailbox. */
	/* 0x0.23 - 0x0.23 */
	/* access: RW */
	u_int8_t icmd_exmb;
	/* Description - If set, CAPI is supported. */
	/* 0x0.24 - 0x0.24 */
	/* access: RW */
	u_int8_t capi;
	/* Description - If set, QCAM register is supported. Table  1248, "QCAM - QoS Capabilities Mask Register Layout," on page  1573. */
	/* 0x0.25 - 0x0.25 */
	/* access: RW */
	u_int8_t qcam_reg;
	/* Description - If set, MCAM register is supported. Table  3004, "MCAM - Management Capabilities Mask Register Layout," on page  3424. */
	/* 0x0.26 - 0x0.26 */
	/* access: RW */
	u_int8_t mcam_reg;
	/* Description - If set, PCAM register is supported. Table  1854, "PCAM - Ports Capabilities Mask Register Layout," on page  2174 */
	/* 0x0.27 - 0x0.27 */
	/* access: RW */
	u_int8_t pcam_reg;
	/* Description - When set, multi-host synchronization through the device is supported. Section  32.4.3, "ICMD_MH_SYNC - Multi-Host Synchronization," on page  4408. */
	/* 0x0.28 - 0x0.28 */
	/* access: RW */
	u_int8_t mh_sync;
	/* Description - If set, ICMD_ACCESS_REGISTER supports every register. (in the past it supported some of them). */
	/* 0x0.29 - 0x0.29 */
	/* access: RW */
	u_int8_t allow_icmd_access_reg_on_all_registers;
	/* Description -  */
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t fw_info_psid;
	/* Description - When set, ICMD_ACCESS_REGISTER supports the following registers:
MNVDA
MNVDI
MNVIA
MNVQC */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t nv_access;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If set, wake on phy activity is supported. */
	/* 0x4.0 - 0x4.0 */
	/* access: RW */
	u_int8_t wol_p;
	/* Description - If set, wake on unicast packet is supported. */
	/* 0x4.1 - 0x4.1 */
	/* access: RW */
	u_int8_t wol_u;
	/* Description - If set, wake on multicast packet is supported. */
	/* 0x4.2 - 0x4.2 */
	/* access: RW */
	u_int8_t wol_m;
	/* Description - If set, wake on broadcast packet is supported. */
	/* 0x4.3 - 0x4.3 */
	/* access: RW */
	u_int8_t wol_b;
	/* Description - If set, wake on ARP is supported. */
	/* 0x4.4 - 0x4.4 */
	/* access: RW */
	u_int8_t wol_a;
	/* Description - If set, wake on magic packet is supported. */
	/* 0x4.5 - 0x4.5 */
	/* access: RW */
	u_int8_t wol_g;
	/* Description - If set, wake on secured magic packet is supported. */
	/* 0x4.6 - 0x4.6 */
	/* access: RW */
	u_int8_t wol_s;
	/* Description - If set, reset on magic packet is supported. */
	/* 0x4.8 - 0x4.8 */
	/* access: RW */
	u_int8_t rol_g;
	/* Description - If set, reset on secured magic packet is supported. */
	/* 0x4.9 - 0x4.9 */
	/* access: RW */
	u_int8_t rol_s;
	/* Description - If set, FPGA device is supported by the device. See TBD */
	/* 0x4.10 - 0x4.10 */
	/* access: RW */
	u_int8_t fpga;
	/* Description - Indicates number of diagnostic counters supported by device. See Debug Capabilities for more information */
	/* 0x4.16 - 0x4.31 */
	/* access: RW */
	u_int16_t num_of_diagnostic_counters;
};

/* Description -   */
/* Size in bytes - 4 */
struct icmd_hca_icmd_query_cap_in {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Group of capabilities.
0x0: General_capability
0x1: Debug_Capability
other values are reserved. */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t capability_group;
};

/* Description -   */
/* Size in bytes - 16 */
struct icmd_hca_icmd_query_diagnostic_cntrs_in {
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The sample_index is the first sample index. The sample index shall be in the range of 0    2^HCA_CAP.log_number_of_samples. See Section  31.3.4.11, "Debug Capabilities," on page  3735. */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t sample_index;
	/* Description - The number of samples to return. 
Device might return up to the configured value HCA_CAP.log_number_of_samples. (See Section  31.3.4.11, "Debug Capabilities," on page  3735).
Note that the device can perform roll over when reaching number_of_samples. For example: if the user asks for 256 samples starting from index 128, the result will be: 128,   ,255,0,   ,127. */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t num_of_samples;
};

/* Description -   */
/* Size in bytes - 36 */
struct icmd_hca_icmd_query_diagnostic_params_out {
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Diagnostic parameters context.
Table  4429, "DIAGNOSTIC_PARAMS_CONTEXT Input Structure Layout," on page  4323 */
	/* 0x8.0 - 0x20.31 */
	/* access: RW */
	struct icmd_hca_diagnostic_params_context diagnostic_params_context;
};

/* Description -   */
/* Size in bytes - 36 */
struct icmd_hca_icmd_set_diagnostic_params_in {
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Diagnostic parameters context.
Table  4429, "DIAGNOSTIC_PARAMS_CONTEXT Input Structure Layout," on page  4323 */
	/* 0x8.0 - 0x20.31 */
	/* access: RW */
	struct icmd_hca_diagnostic_params_context diagnostic_params_context;
};

/* Description -   */
/* Size in bytes - 68 */
union icmd_hca_icmd_hca_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct icmd_hca_icmd_mh_sync_out icmd_mh_sync_out;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct icmd_hca_icmd_mh_sync_in icmd_mh_sync_in;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	/* access: RW */
	struct icmd_hca_icmd_query_diagnostic_params_out icmd_query_diagnostic_params_out;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	/* access: RW */
	struct icmd_hca_debug_cap debug_cap;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct icmd_hca_icmd_query_cap_in icmd_query_cap_in;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct icmd_hca_icmd_query_cap_general icmd_query_cap_general;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct icmd_hca_icmd_query_diagnostic_cntrs_in icmd_query_diagnostic_cntrs_in;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	/* access: RW */
	struct icmd_hca_icmd_set_diagnostic_params_in icmd_set_diagnostic_params_in;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* counter_id */
void icmd_hca_counter_id_pack(const struct icmd_hca_counter_id *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_counter_id_unpack(struct icmd_hca_counter_id *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_counter_id_print(const struct icmd_hca_counter_id *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_counter_id_size(void);
#define ICMD_HCA_COUNTER_ID_SIZE    (0x4)
void icmd_hca_counter_id_dump(const struct icmd_hca_counter_id *ptr_struct, FILE *fd);
/* diagnostic_cntr_layout */
void icmd_hca_diagnostic_cntr_layout_pack(const struct icmd_hca_diagnostic_cntr_layout *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_diagnostic_cntr_layout_unpack(struct icmd_hca_diagnostic_cntr_layout *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_diagnostic_cntr_layout_print(const struct icmd_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_diagnostic_cntr_layout_size(void);
#define ICMD_HCA_DIAGNOSTIC_CNTR_LAYOUT_SIZE    (0x4)
void icmd_hca_diagnostic_cntr_layout_dump(const struct icmd_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd);
/* diagnostic_params_context */
void icmd_hca_diagnostic_params_context_pack(const struct icmd_hca_diagnostic_params_context *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_diagnostic_params_context_unpack(struct icmd_hca_diagnostic_params_context *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_diagnostic_params_context_print(const struct icmd_hca_diagnostic_params_context *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_diagnostic_params_context_size(void);
#define ICMD_HCA_DIAGNOSTIC_PARAMS_CONTEXT_SIZE    (0x18)
void icmd_hca_diagnostic_params_context_dump(const struct icmd_hca_diagnostic_params_context *ptr_struct, FILE *fd);
/* debug_cap */
void icmd_hca_debug_cap_pack(const struct icmd_hca_debug_cap *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_debug_cap_unpack(struct icmd_hca_debug_cap *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_debug_cap_print(const struct icmd_hca_debug_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_debug_cap_size(void);
#define ICMD_HCA_DEBUG_CAP_SIZE    (0x40)
void icmd_hca_debug_cap_dump(const struct icmd_hca_debug_cap *ptr_struct, FILE *fd);
/* icmd_mh_sync_in */
void icmd_hca_icmd_mh_sync_in_pack(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_mh_sync_in_unpack(struct icmd_hca_icmd_mh_sync_in *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_mh_sync_in_print(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_mh_sync_in_size(void);
#define ICMD_HCA_ICMD_MH_SYNC_IN_SIZE    (0x4)
void icmd_hca_icmd_mh_sync_in_dump(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, FILE *fd);
/* icmd_mh_sync_out */
void icmd_hca_icmd_mh_sync_out_pack(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_mh_sync_out_unpack(struct icmd_hca_icmd_mh_sync_out *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_mh_sync_out_print(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_mh_sync_out_size(void);
#define ICMD_HCA_ICMD_MH_SYNC_OUT_SIZE    (0xc)
void icmd_hca_icmd_mh_sync_out_dump(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, FILE *fd);
/* icmd_query_cap_general */
void icmd_hca_icmd_query_cap_general_pack(const struct icmd_hca_icmd_query_cap_general *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_query_cap_general_unpack(struct icmd_hca_icmd_query_cap_general *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_query_cap_general_print(const struct icmd_hca_icmd_query_cap_general *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_query_cap_general_size(void);
#define ICMD_HCA_ICMD_QUERY_CAP_GENERAL_SIZE    (0x8)
void icmd_hca_icmd_query_cap_general_dump(const struct icmd_hca_icmd_query_cap_general *ptr_struct, FILE *fd);
/* icmd_query_cap_in */
void icmd_hca_icmd_query_cap_in_pack(const struct icmd_hca_icmd_query_cap_in *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_query_cap_in_unpack(struct icmd_hca_icmd_query_cap_in *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_query_cap_in_print(const struct icmd_hca_icmd_query_cap_in *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_query_cap_in_size(void);
#define ICMD_HCA_ICMD_QUERY_CAP_IN_SIZE    (0x4)
void icmd_hca_icmd_query_cap_in_dump(const struct icmd_hca_icmd_query_cap_in *ptr_struct, FILE *fd);
/* icmd_query_diagnostic_cntrs_in */
void icmd_hca_icmd_query_diagnostic_cntrs_in_pack(const struct icmd_hca_icmd_query_diagnostic_cntrs_in *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_query_diagnostic_cntrs_in_unpack(struct icmd_hca_icmd_query_diagnostic_cntrs_in *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_query_diagnostic_cntrs_in_print(const struct icmd_hca_icmd_query_diagnostic_cntrs_in *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_query_diagnostic_cntrs_in_size(void);
#define ICMD_HCA_ICMD_QUERY_DIAGNOSTIC_CNTRS_IN_SIZE    (0x10)
void icmd_hca_icmd_query_diagnostic_cntrs_in_dump(const struct icmd_hca_icmd_query_diagnostic_cntrs_in *ptr_struct, FILE *fd);
/* icmd_query_diagnostic_params_out */
void icmd_hca_icmd_query_diagnostic_params_out_pack(const struct icmd_hca_icmd_query_diagnostic_params_out *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_query_diagnostic_params_out_unpack(struct icmd_hca_icmd_query_diagnostic_params_out *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_query_diagnostic_params_out_print(const struct icmd_hca_icmd_query_diagnostic_params_out *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_query_diagnostic_params_out_size(void);
#define ICMD_HCA_ICMD_QUERY_DIAGNOSTIC_PARAMS_OUT_SIZE    (0x24)
void icmd_hca_icmd_query_diagnostic_params_out_dump(const struct icmd_hca_icmd_query_diagnostic_params_out *ptr_struct, FILE *fd);
/* icmd_set_diagnostic_params_in */
void icmd_hca_icmd_set_diagnostic_params_in_pack(const struct icmd_hca_icmd_set_diagnostic_params_in *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_set_diagnostic_params_in_unpack(struct icmd_hca_icmd_set_diagnostic_params_in *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_set_diagnostic_params_in_print(const struct icmd_hca_icmd_set_diagnostic_params_in *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_set_diagnostic_params_in_size(void);
#define ICMD_HCA_ICMD_SET_DIAGNOSTIC_PARAMS_IN_SIZE    (0x24)
void icmd_hca_icmd_set_diagnostic_params_in_dump(const struct icmd_hca_icmd_set_diagnostic_params_in *ptr_struct, FILE *fd);
/* icmd_hca_Nodes */
void icmd_hca_icmd_hca_Nodes_pack(const union icmd_hca_icmd_hca_Nodes *ptr_struct, u_int8_t *ptr_buff);
void icmd_hca_icmd_hca_Nodes_unpack(union icmd_hca_icmd_hca_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void icmd_hca_icmd_hca_Nodes_print(const union icmd_hca_icmd_hca_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int icmd_hca_icmd_hca_Nodes_size(void);
#define ICMD_HCA_ICMD_HCA_NODES_SIZE    (0x44)
void icmd_hca_icmd_hca_Nodes_dump(const union icmd_hca_icmd_hca_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // ICMD_HCA_LAYOUTS_H
