
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2010-2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
 

/***
         *** This file was generated at "2023-01-09 15:12:36"
         *** by:
         ***    > /.autodirect/swgwork/astrutsovsky/work/4Dan/a-me_dev/adabe_plugins/adb2c/adb2pack.py --input adb/tools/icmd_hca.adb --file-prefix icmd_hca --prefix icmd_hca_ --no-adb-utils
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
	u_int16_t counter_id;
};

/* Description -   */
/* Size in bytes - 4 */
struct icmd_hca_diagnostic_cntr_layout {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Diagnostic counter identifier. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t counter_id;
	/* Description - The counter might be used as Synced Start Diagnostics Counters */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sync;
};



/* Description -   */
/* Size in bytes - 64 */
struct icmd_hca_debug_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The maximum number of samples that can be stored on the device's sampling buffer is 2^ log_max_samples in counters unit (i.e. 100 will represent the ability to store 100 samples of single counter, 50 samples of 2 counters, etc). */
	/* 0x0.0 - 0x0.7 */
	u_int8_t log_max_samples;
	/* Description - Log(base 2) of the the recommended minimal size of eq to handle the resource_dump_event */
	/* 0x0.16 - 0x0.20 */
	u_int8_t log_min_resource_dump_eq;
	/* Description - If set, Resource_dump register is supported.
See Table 1224, "RESOURCE_DUMP Register Layout," on page 1585 */
	/* 0x0.22 - 0x0.22 */
	u_int8_t resource_dump;
	/* Description - Log(base 2) of the size in granularity of 4KB to be allocated by host in order to accommodate cr_dump.
0 means feature is not supported.
See Table 1222, "CORE_DUMP Register Layout," on page 1583 */
	/* 0x0.23 - 0x0.27 */
	u_int8_t log_cr_dump_to_mem_size;
	/* Description - If set, Core dump of type of specific QP is supported.
 */
	/* 0x0.30 - 0x0.30 */
	u_int8_t core_dump_qp;
	/* Description - If set, Core dump of type "General" is supported. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t core_dump_general;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The minimal sample period is 2^ log_min_smaple_period in device clocks. Clock rate of the device is reported by HCA_CAP.device_frequency_khz. */
	/* 0x4.0 - 0x4.7 */
	u_int8_t log_min_sample_period;
	/* Description - If set, the device supports dumping the diagnostic counters reports into the tracer buffer. */
	/* 0x4.28 - 0x4.28 */
	u_int8_t diag_counter_tracer_dump;
	/* Description - If set, health monitoring for rx path activity is supported.
See Section  26.5.1, "RX Path Activity," on page  988 */
	/* 0x4.29 - 0x4.29 */
	u_int8_t health_mon_rx_activity;
	/* Description - Repetitive sampling mode is supported */
	/* 0x4.30 - 0x4.30 */
	u_int8_t repetitive;
	/* Description - Single sampling mode is supported */
	/* 0x4.31 - 0x4.31 */
	u_int8_t single;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - List of counters supported. Number of counters reported by num_of_counters. */
	/* 0x40.0 - 0x40.31 */
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
	u_int8_t state;
	/* Description - The operation currently being synchronized:
0x1: FW_RESET
other values are reserved */
	/* 0x0.8 - 0x0.15 */
	u_int8_t sync_type;
	/* Description - When set, hosts in reset state (PERST# low) are ignored (not synchronized) */
	/* 0x0.31 - 0x0.31 */
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
	u_int8_t state;
	/* Description - The operation currently being synchronized:
0x1: FW_RESET
other values are reserved */
	/* 0x0.8 - 0x0.15 */
	u_int8_t sync_type;
	/* Description - When set, hosts in reset state (PERST# low) are ignored (not synchronized) */
	/* 0x0.31 - 0x0.31 */
	u_int8_t ignore_inactive_host;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Current state of the host acknowledgement process
0x0: IDLE - no host ack
0x1: READY - sync in progress
0xF: GO - all hosts ack
Other values are reserved */
	/* 0x4.0 - 0x4.3 */
	u_int8_t host_ready;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - NIC uptime (time since last reset) in microseconds, at the moment the synchronization state machine entered the GET_READY state. */
	/* 0x8.0 - 0x8.31 */
	u_int32_t start_uptime;
};

/* Description -   */
/* Size in bytes - 8 */
struct icmd_hca_icmd_query_cap_general {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, NIC_CAP_REG register is supported. */
	/* 0x0.13 - 0x0.13 */
	u_int8_t nic_cap_reg;
	/* Description - If set, port_state_behavior register is supported.
See Section 28.17, "PORT_STATE_BEHAVIOR Register", on page 1596 */
	/* 0x0.14 - 0x0.14 */
	u_int8_t port_state_behavior;
	/* Description - When set, virtual node GUID can be set/queried using ICMD_SET/QUERY_VIRTUAL_MAC */
	/* 0x0.15 - 0x0.15 */
	u_int8_t virt_node_guid;
	/* Description - If set, NCFG register is supported. */
	/* 0x0.16 - 0x0.16 */
	u_int8_t ncfg_reg;
	/* Description - If set, CWCAM register is supported. Table 1774, "CWCAM - Congestion WRED Capabilities Mask Register Layout," on page 2180 */
	/* 0x0.17 - 0x0.17 */
	u_int8_t cwcam_reg;
	/* Description - If set, SBCAM register is supported. See Table 1832, "SBCAM - Shared Buffer Capabilities Mask Register Layout," on page 2227 */
	/* 0x0.18 - 0x0.18 */
	u_int8_t sbcam_reg;
	/* Description - When set, the command supports capability groups in addition to the General Capability group */
	/* 0x0.20 - 0x0.20 */
	u_int8_t capability_groups;
	/* Description - When set, the device supports emulating link down for all the associated functions using "ICMD_SET_VIRTUAL_PARAMETERS - Set Device Virtual Parameters" */
	/* 0x0.22 - 0x0.22 */
	u_int8_t virtual_link_down;
	/* Description - When set, the device supports using a memory buffer as a mailbox for the ICMD, instead of the normal ICMD Mailbox. */
	/* 0x0.23 - 0x0.23 */
	u_int8_t icmd_exmb;
	/* Description - If set, CAPI is supported. */
	/* 0x0.24 - 0x0.24 */
	u_int8_t capi;
	/* Description - If set, QCAM register is supported. Table  1044, "QCAM - QoS Capabilities Mask Register Layout," on page  1358. */
	/* 0x0.25 - 0x0.25 */
	u_int8_t qcam_reg;
	/* Description - If set, MCAM register is supported. Table  2023, "MCAM - Management Capabilities Mask Register Layout," on page  2386. */
	/* 0x0.26 - 0x0.26 */
	u_int8_t mcam_reg;
	/* Description - If set, PCAM register is supported. Table  1279, "PCAM - Ports Capabilities Mask Register Layout," on page  1632 */
	/* 0x0.27 - 0x0.27 */
	u_int8_t pcam_reg;
	/* Description - When set, multi-host synchronization through the device is supported. Section  30.4.3, "ICMD_MH_SYNC - Multi-Host Synchronization," on page  3318. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t mh_sync;
	/* Description - If set, ICMD_ACCESS_REGISTER supports every register. (in the past it supported some of them). */
	/* 0x0.29 - 0x0.29 */
	u_int8_t allow_icmd_access_reg_on_all_registers;
	/* Description -  */
	/* 0x0.30 - 0x0.30 */
	u_int8_t fw_info_psid;
	/* Description - When set, ICMD_ACCESS_REGISTER supports the following registers:
NVDA
NVDI
NVIA
NVQC */
	/* 0x0.31 - 0x0.31 */
	u_int8_t nv_access;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If set, wake on phy activity is supported. */
	/* 0x4.0 - 0x4.0 */
	u_int8_t wol_p;
	/* Description - If set, wake on unicast packet is supported. */
	/* 0x4.1 - 0x4.1 */
	u_int8_t wol_u;
	/* Description - If set, wake on multicast packet is supported. */
	/* 0x4.2 - 0x4.2 */
	u_int8_t wol_m;
	/* Description - If set, wake on broadcast packet is supported. */
	/* 0x4.3 - 0x4.3 */
	u_int8_t wol_b;
	/* Description - If set, wake on ARP is supported. */
	/* 0x4.4 - 0x4.4 */
	u_int8_t wol_a;
	/* Description - If set, wake on magic packet is supported. */
	/* 0x4.5 - 0x4.5 */
	u_int8_t wol_g;
	/* Description - If set, wake on secured magic packet is supported. */
	/* 0x4.6 - 0x4.6 */
	u_int8_t wol_s;
	/* Description - If set, reset on magic packet is supported. */
	/* 0x4.8 - 0x4.8 */
	u_int8_t rol_g;
	/* Description - If set, reset on secured magic packet is supported. */
	/* 0x4.9 - 0x4.9 */
	u_int8_t rol_s;
	/* Description - If set, FPGA device is supported by the device. See TBD */
	/* 0x4.10 - 0x4.10 */
	u_int8_t fpga;
	/* Description - Indicates number of diagnostic counters supported by device. See Debug Capabilities for more information */
	/* 0x4.16 - 0x4.31 */
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
	u_int16_t capability_group;
};





/* Description -   */
/* Size in bytes - 68 */
union icmd_hca_icmd_hca_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct icmd_hca_icmd_query_cap_general icmd_query_cap_general;
	/* Description -  */

	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct icmd_hca_icmd_query_cap_in icmd_query_cap_in;

	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	struct icmd_hca_debug_cap debug_cap;

	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct icmd_hca_icmd_mh_sync_out icmd_mh_sync_out;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct icmd_hca_icmd_mh_sync_in icmd_mh_sync_in;
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
