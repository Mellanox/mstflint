
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
         *** This file was generated at "2024-12-09 08:55:25"
         *** by:
         ***    > /auto/mswg/release/tools/a-me/a-me-1.2.7/a-me-1.2.7-44/adabe_plugins/adb2c/adb2pack.py --input /images/redesign/mft/user/tools_layouts/adb/prm/gpu/ext/reg_access_gpu.adb --file-prefix reg_access_gpu --prefix reg_access_gpu_ --no-adb-utils -o /images/redesign/mft/user/tools_layouts
         ***/
#ifndef REG_ACCESS_GPU_LAYOUTS_H
#define REG_ACCESS_GPU_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols admin state: see PTYS.ext_eth_proto_admin */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t core_to_phy_link_eth_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ib link enabled speed:
Bit 0: SDR
Bit 1: DDR
Bit 2: QDR
Bit 3: FDR10
Bit 4: FDR
Bit 5: EDR
Bit 6: HDR
Bit 7: NDR
Bit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t core_to_phy_link_proto_enabled;
	/* Description - ib link enabled width:
Bit 0: 1x
Bit 1: 2x
Bit 2: 4x

Other - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t core_to_phy_link_width_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_cable_cap_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is supported, use for opcode definition PTYS.ext_eth_proto_capIf PTYS.ext_eth_proto_capability mask is empty, use For opcode definition PTYS.eth_proto_cap. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t cable_ext_eth_proto_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_cable_cap_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Cable support IB speed:
Bit 0: SDR
Bit 1: DDR
Bit 2: QDR
Bit 3: FDR10
Bit 4: FDR
Bit 5: EDR
Bit 6: HDR
Bit 7: NDR
Bit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t cable_link_speed_cap;
	/* Description - Cable support IB width:
Bit 0: 1x
Bit 1: 2x
Bit 2: 4x

Other - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t cable_link_width_cap;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_link_active_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols active : see PTYS.ext_eth_proto_oper */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t link_eth_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_link_active_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ib link active speed:
Bit 0: SDR
Bit 1: DDR
Bit 2: QDR
Bit 3: FDR10
Bit 4: FDR
Bit 5: EDR
Bit 6: HDR
Bit 7: NDR
Bit 8: XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - ib link active width:
Bit 0: 1x
Bit 1: 2x
Bit 2: 4x

Other - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t link_width_active;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_monitor_opcode_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Status opcode: 

PHY FW indication (0 - 1023):
0 - No issue observed
1 - Port is close by command (see PAOS).
2,3,4,38,39 - AN failure 
5,6,7,8 - Link training failure. 
9,10,11,12,13 - Logical mismatch between link partners
14 - Remote fault received
15,42,17,48,49,52, - Bad signal integrity 
16,24-32 - Cable compliance code mismatch (protocol mismatch between cable and port) 
23,22,19,18,50,55- Internal error
34,35 - Speed degradation
56 - module_lanes_frequency_not_synced
57 - signal not detected
60 - no partner detected for long time
128 - Troubleshooting in process
1023- Info not available

MNG FW issues (1024 - 2047):
1024 - Cable is unplugged
1025 - Long Range for non Mellanox cable/module .
1026 - Bus stuck (I2C Data or clock shorted) 
1027 - Bad/unsupported EEPROM 
1028 - Part number list
1029 - Unsupported cable.
1030 - Module temperature shutdown
1031 - Shorted cable
1032 - Power budget exceeded
1033 - Management forced down the port
1034 - Module is disabled by command
1035 - System Power is Exceeded therefore the module is powered off.
1036 - Module's PMD type is not enabled (see PMTPS).
1040 - pcie system power slot Exceeded
1042 - Module state machine fault
1043,1044,1045,1046 - Module's stamping speed degeneration
1047, 1048 - Modules DataPath FSM fault
1050, 1051, 1052, 1053- Module Boot Error
1054 - Module Forced to Low Power by command
Core/Driver (2048 - 3071): */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t monitor_opcode;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet protocols admin state: see PTYS.ext_eth_proto_admin */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t phy_manager_link_eth_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ib link enabled speed:
Bit 0 - SDR
Bit 1 - DDR
Bit 2 - QDR
Bit 3 - FDR10
Bit 4 - FDR
Bit 5 - EDR
Bit 6 - HDR
Bit 7 - NDR
Bit 8 - XDR */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t phy_manager_link_proto_enabled;
	/* Description - ib link enabled width:
Bit 0 - 1x
Bit 1 - 2x
Bit 2 - 4x
Other - reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t phy_manager_link_width_enabled;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_cable_cap_eth_ext pddr_cable_cap_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_cable_cap_ib_ext pddr_cable_cap_ib_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext pddr_c2p_link_enabed_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext pddr_c2p_link_enabed_ib_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_link_active_eth_ext pddr_link_active_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_link_active_ib_ext pddr_link_active_ib_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext pddr_phy_manager_link_enabed_eth_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext pddr_phy_manager_link_enabed_ib_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_monitor_opcode_ext pddr_monitor_opcode_ext;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t symbol_error_counter_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t symbol_error_counter_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t link_error_recovery_counter_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t link_error_recovery_counter_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t link_downed_counter_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t link_downed_counter_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t port_rcv_errors_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t port_rcv_errors_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t port_rcv_remote_physical_errors_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t port_rcv_remote_physical_errors_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t port_rcv_switch_relay_errors_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t port_rcv_switch_relay_errors_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t port_xmit_discards_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t port_xmit_discards_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t port_xmit_constraint_errors_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t port_xmit_constraint_errors_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t port_rcv_constraint_errors_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t port_rcv_constraint_errors_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t local_link_integrity_errors_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t local_link_integrity_errors_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t excessive_buffer_overrun_errors_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t excessive_buffer_overrun_errors_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t vl_15_dropped_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t vl_15_dropped_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t port_xmit_data_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t port_xmit_data_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t port_rcv_data_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t port_rcv_data_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t port_xmit_pkts_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t port_xmit_pkts_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t port_rcv_pkts_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t port_rcv_pkts_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t port_xmit_wait_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t port_xmit_wait_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t qp1_dropped_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t qp1_dropped_low;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x90.0 - 0x90.31 */
	/* access: RO */
	u_int32_t port_unicast_xmit_pkts_high;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x94.0 - 0x94.31 */
	/* access: RO */
	u_int32_t port_unicast_xmit_pkts_low;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x98.0 - 0x98.31 */
	/* access: RO */
	u_int32_t port_multicast_xmit_pkts_high;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0x9c.0 - 0x9c.31 */
	/* access: RO */
	u_int32_t port_multicast_xmit_pkts_low;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0xa0.0 - 0xa0.31 */
	/* access: RO */
	u_int32_t port_unicast_rcv_pkts_high;
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0xa4.0 - 0xa4.31 */
	/* access: RO */
	u_int32_t port_unicast_rcv_pkts_low;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0xa8.0 - 0xa8.31 */
	/* access: RO */
	u_int32_t port_multicast_rcv_pkts_high;
/*---------------- DWORD[43] (Offset 0xac) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification */
	/* 0xac.0 - 0xac.31 */
	/* access: RO */
	u_int32_t port_multicast_rcv_pkts_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t link_downed_counter;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t link_error_recovery_counter;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t symbol_error_counter;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t port_rcv_remote_physical_errors;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t port_rcv_errors;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t port_xmit_discards;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t port_rcv_switch_relay_errors;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0xc.0 - 0xc.3 */
	/* access: RO */
	u_int8_t excessive_buffer_overrun_errors;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0xc.4 - 0xc.7 */
	/* access: RO */
	u_int8_t local_link_integrity_errors;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t port_rcv_constraint_errors;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t port_xmit_constraint_errors;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t vl_15_dropped;
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t qp1_dropped;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t port_xmit_data;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t port_rcv_data;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t port_xmit_pkts;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t port_rcv_pkts;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - For counter description please refer to the InfiniBand specification
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t port_xmit_wait;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_MRFV_CVB_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - CVB Data
Process Sigma = -4 + 0.5 * cvb_data_index
cvb_data_index valid values 0 .. 15
For Retimer
Process Sigma <-> DVDD (mV)
-4.0: 856.00
-3.5: 847.75
-3.0: 839.50
-2.5: 831.25
-2.0: 823.00
-1.5: 814.75
-1.0: 806.50
-0.5: 798.25
0 (nominal): 790.00
0.5: 781.75
1.0: 773.50
1.5: 765.25
2.0: 757.00
2.5: 748.75
3.0: 740.50
3.5: 732.25
4.0: 724.00 */
	/* 0x0.0 - 0x0.4 */
	/* access: RO */
	u_int8_t cvb_data_index;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_MRFV_PVS_MAIN_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PVS Data
Range 0.675 - 0.75
Vdd = 750mV - (fuse value - 1)*5mV */
	/* 0x0.0 - 0x0.4 */
	/* access: RO */
	u_int8_t pvs_main_data;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_MRFV_PVS_TILE_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PVS tile Data
Range 0.675 - 0.72
Vdd = 750mV - (fuse value - 1)*5mV */
	/* 0x0.0 - 0x0.4 */
	/* access: RO */
	u_int8_t pvs_tile_data;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_MRFV_ULT_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t ult_lot_digit_1;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t ult_lot_digit_2;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t ult_lot_digit_3;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t ult_lot_digit_4;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t ult_lot_digit_5;
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ult_lot_digit_6;
	/* Description -  */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t ult_lot_digit_7;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t ult_lot_digit_8;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t ult_y;
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t ult_x;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t ult_wafer_number;
	/* Description -  */
	/* 0x8.29 - 0x8.31 */
	/* access: RO */
	u_int8_t ult_err_detection;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of events in which packets were dropped by the probe due to lack of resources.
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t ether_stats_drop_events_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The total number of events in which packets were dropped by the probe due to lack of resources.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t ether_stats_drop_events_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The total number of octets of data (including those in bad packets) received (excluding framing bits but including FCS octets).
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ether_stats_octets_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The total number of octets of data (including those in bad packets) received (excluding framing bits but including FCS octets).
 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t ether_stats_octets_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The total number of packets (including bad packets, broadcast packets, and multicast packets) received.
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The total number of packets (including bad packets, broadcast packets, and multicast packets) received.
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The total number of good packets received that were directed to the broadcast address. 
Note: This does not include multicast packets.
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t ether_stats_broadcast_pkts_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The total number of good packets received that were directed to the broadcast address. 
Note: This does not include multicast packets.
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t ether_stats_broadcast_pkts_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The total number of good packets received that were directed to a multicast MAC address. 
Note: This number does not include packets directed to the broadcast address.
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t ether_stats_multicast_pkts_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The total number of good packets received that were directed to a multicast MAC address. 
Note: This number does not include packets directed to the broadcast address.
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t ether_stats_multicast_pkts_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The total number of packets received that had a length (excluding framing bits, but including FCS octets) of between 64 and MTU octets, inclusive, but had either a bad frame check sequence (FCS) with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t ether_stats_crc_align_errors_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The total number of packets received that had a length (excluding framing bits, but including FCS octets) of between 64 and MTU octets, inclusive, but had either a bad frame check sequence (FCS) with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t ether_stats_crc_align_errors_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The total number of packets received that were less than 64 octets long (excluding framing bits, but including FCS octets) and were otherwise well formed.
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t ether_stats_undersize_pkts_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The total number of packets received that were less than 64 octets long (excluding framing bits, but including FCS octets) and were otherwise well formed.
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t ether_stats_undersize_pkts_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets) but were otherwise well formed.
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t ether_stats_oversize_pkts_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets) but were otherwise well formed.
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t ether_stats_oversize_pkts_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - The total number of packets received that were less than 64 octets in length (excluding framing bits but including FCS octets) and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t ether_stats_fragments_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - The total number of packets received that were less than 64 octets in length (excluding framing bits but including FCS octets) and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t ether_stats_fragments_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets), and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t ether_stats_jabbers_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets), and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t ether_stats_jabbers_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - The best estimate of the total number of collisions on this Ethernet segment.
 */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t ether_stats_collisions_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - The best estimate of the total number of collisions on this Ethernet segment.
 */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t ether_stats_collisions_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were 64 octets in length (excluding framing bits but including FCS octets). */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts64octets_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were 64 octets in length (excluding framing bits but including FCS octets). */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts64octets_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 65 and 127 octets in length (excluding framing bits but including FCS octets). */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts65to127octets_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 65 and 127 octets in length (excluding framing bits but including FCS octets). */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts65to127octets_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 128 and 255 octets in length (excluding framing bits but including FCS octets). */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts128to255octets_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 128 and 255 octets in length (excluding framing bits but including FCS octets). */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts128to255octets_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 256 and 511 octets in length (excluding framing bits but including FCS octets). */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts256to511octets_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 256 and 511 octets in length (excluding framing bits but including FCS octets). */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts256to511octets_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets). */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts512to1023octets_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets). */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts512to1023octets_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets). */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts1024to1518octets_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets). */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts1024to1518octets_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets). */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts1519to2047octets_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets). */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts1519to2047octets_low;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets). */
	/* 0x90.0 - 0x90.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts2048to4095octets_high;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets). */
	/* 0x94.0 - 0x94.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts2048to4095octets_low;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets). */
	/* 0x98.0 - 0x98.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts4096to8191octets_high;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets). */
	/* 0x9c.0 - 0x9c.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts4096to8191octets_low;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).
 */
	/* 0xa0.0 - 0xa0.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts8192to10239octets_high;
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - The total number of packets (including bad packets) received that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).
 */
	/* 0xa4.0 - 0xa4.31 */
	/* access: RO */
	u_int32_t ether_stats_pkts8192to10239octets_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of octets received, including framing characters. Including MAC control frames.

 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t if_in_octets_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The total number of octets received, including framing characters. Including MAC control frames.

 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t if_in_octets_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The number of packets successfully received, which were not addressed to a multicast or broadcast MAC address.
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t if_in_ucast_pkts_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The number of packets successfully received, which were not addressed to a multicast or broadcast MAC address.
 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t if_in_ucast_pkts_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.




 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t if_in_discards_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.




 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t if_in_discards_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The number of inbound packets that contained errors preventing them from being deliverable to a higher-layer protocol. 
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t if_in_errors_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The number of inbound packets that contained errors preventing them from being deliverable to a higher-layer protocol. 
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t if_in_errors_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The number of packets received via the interface which were discarded because of an unknown or unsupported protocol.
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t if_in_unknown_protos_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The number of packets received via the interface which were discarded because of an unknown or unsupported protocol.
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t if_in_unknown_protos_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The total number of octets transmitted out of the interface, including framing characters.
 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t if_out_octets_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The total number of octets transmitted out of the interface, including framing characters.
 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t if_out_octets_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted and were not addressed to a multicast or broadcast MAC address, including those that were discarded or not sent.
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t if_out_ucast_pkts_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted and were not addressed to a multicast or broadcast MAC address, including those that were discarded or not sent.
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t if_out_ucast_pkts_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - The number of outbound packets which were chosen to be discarded, even though no errors had been detected to prevent their being transmitted. 
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t if_out_discards_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - The number of outbound packets which were chosen to be discarded, even though no errors had been detected to prevent their being transmitted. 
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t if_out_discards_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - The number of outbound packets that could not be transmitted because of errors.
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t if_out_errors_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - The number of outbound packets that could not be transmitted because of errors.
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t if_out_errors_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - The number of packets successfully received, which were addressed to a multicast MAC address.
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t if_in_multicast_pkts_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - The number of packets successfully received, which were addressed to a multicast MAC address.
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t if_in_multicast_pkts_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - The number of packets successfully received, which were addressed to a broadcast MAC address.
 */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t if_in_broadcast_pkts_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - The number of packets successfully received, which were addressed to a broadcast MAC address.
 */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t if_in_broadcast_pkts_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a multicast MAC address, including those that were discarded or not sent.
 */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t if_out_multicast_pkts_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a multicast MAC address, including those that were discarded or not sent.
 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t if_out_multicast_pkts_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a broadcast MAC address, including those that were discarded or not sent.
 */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t if_out_broadcast_pkts_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a broadcast MAC address, including those that were discarded or not sent.
 */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t if_out_broadcast_pkts_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - A count of frames received that are not an integral number of octets in length and do not pass the FCS check.
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t dot3stats_alignment_errors_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - A count of frames received that are not an integral number of octets in length and do not pass the FCS check.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t dot3stats_alignment_errors_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - A count of frames received that are an integral number of octets in length but do not pass the FCS check. This count does not include frames received with frame-too-long or frame-too-short errors.
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t dot3stats_fcs_errors_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - A count of frames received that are an integral number of octets in length but do not pass the FCS check. This count does not include frames received with frame-too-long or frame-too-short errors.
 */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t dot3stats_fcs_errors_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - A count of frames that are involved in a single collision, and are subsequently transmitted successfully.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	u_int32_t dot3stats_single_collision_frames_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - A count of frames that are involved in a single collision, and are subsequently transmitted successfully.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t dot3stats_single_collision_frames_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - A count of frames that are involved in more than one collision and are subsequently transmitted successfully. 
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t dot3stats_multiple_collision_frames_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - A count of frames that are involved in more than one collision and are subsequently transmitted successfully. 
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RW */
	u_int32_t dot3stats_multiple_collision_frames_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - A count of times that the SQE TEST ERROR is received on a particular interface.
This counter does not increment on interfaces operating at speeds greater than 10 Mb/s, or on interfaces operating in full-duplex mode. 
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RW */
	u_int32_t dot3stats_sqe_test_errors_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - A count of times that the SQE TEST ERROR is received on a particular interface.
This counter does not increment on interfaces operating at speeds greater than 10 Mb/s, or on interfaces operating in full-duplex mode. 
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RW */
	u_int32_t dot3stats_sqe_test_errors_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - A count of frames for which the first transmission attempt on a particular interface is delayed because the medium is busy. 
This counter does not increment when the interface is operating in full-duplex mode. 
 */
	/* 0x28.0 - 0x28.31 */
	/* access: RW */
	u_int32_t dot3stats_deferred_transmissions_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - A count of frames for which the first transmission attempt on a particular interface is delayed because the medium is busy. 
This counter does not increment when the interface is operating in full-duplex mode. 
 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RW */
	u_int32_t dot3stats_deferred_transmissions_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The number of times that a collision is detected on a particular interface later than one slotTime into the transmission of a packet.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RW */
	u_int32_t dot3stats_late_collisions_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The number of times that a collision is detected on a particular interface later than one slotTime into the transmission of a packet.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RW */
	u_int32_t dot3stats_late_collisions_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - A count of frames for which transmission on a particular interface fails due to excessive collisions.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RW */
	u_int32_t dot3stats_excessive_collisions_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - A count of frames for which transmission on a particular interface fails due to excessive collisions.
This counter does not increment when the interface is operating in full-duplex mode.
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RW */
	u_int32_t dot3stats_excessive_collisions_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - A count of frames for which transmission failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RW */
	u_int32_t dot3stats_internal_mac_transmit_errors_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - A count of frames for which transmission failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RW */
	u_int32_t dot3stats_internal_mac_transmit_errors_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - The number of times that the carrier sense condition was lost or never asserted when attempting to transmit a frame on a particular interface. 
This counter does not increment when the interface is operating in full-duplex mode. 
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RW */
	u_int32_t dot3stats_carrier_sense_errors_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - The number of times that the carrier sense condition was lost or never asserted when attempting to transmit a frame on a particular interface. 
This counter does not increment when the interface is operating in full-duplex mode. 
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RW */
	u_int32_t dot3stats_carrier_sense_errors_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - A count of frames received that exceed the maximum permitted frame size.
 */
	/* 0x50.0 - 0x50.31 */
	/* access: RW */
	u_int32_t dot3stats_frame_too_longs_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - A count of frames received that exceed the maximum permitted frame size.
 */
	/* 0x54.0 - 0x54.31 */
	/* access: RW */
	u_int32_t dot3stats_frame_too_longs_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - A count of frames for which reception failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.
 */
	/* 0x58.0 - 0x58.31 */
	/* access: RW */
	u_int32_t dot3stats_internal_mac_receive_errors_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - A count of frames for which reception failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.
 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RW */
	u_int32_t dot3stats_internal_mac_receive_errors_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate "Receive Error".

 */
	/* 0x60.0 - 0x60.31 */
	/* access: RW */
	u_int32_t dot3stats_symbol_errors_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate "Receive Error".

 */
	/* 0x64.0 - 0x64.31 */
	/* access: RW */
	u_int32_t dot3stats_symbol_errors_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - A count of MAC Control frames received that contain an opcode that is not supported.
 */
	/* 0x68.0 - 0x68.31 */
	/* access: RW */
	u_int32_t dot3control_in_unknown_opcodes_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - A count of MAC Control frames received that contain an opcode that is not supported.
 */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RW */
	u_int32_t dot3control_in_unknown_opcodes_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - A count of MAC Control frames received with an opcode indicating the PAUSE operation.

 */
	/* 0x70.0 - 0x70.31 */
	/* access: RW */
	u_int32_t dot3in_pause_frames_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - A count of MAC Control frames received with an opcode indicating the PAUSE operation.

 */
	/* 0x74.0 - 0x74.31 */
	/* access: RW */
	u_int32_t dot3in_pause_frames_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - A count of MAC Control frames transmitted with an opcode indicating the PAUSE operation.

 */
	/* 0x78.0 - 0x78.31 */
	/* access: RW */
	u_int32_t dot3out_pause_frames_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - A count of MAC Control frames transmitted with an opcode indicating the PAUSE operation.

 */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RW */
	u_int32_t dot3out_pause_frames_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - A count of frames that are successfully transmitted. 
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t a_frames_transmitted_ok_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - A count of frames that are successfully transmitted. 
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t a_frames_transmitted_ok_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - A count of frames that are successfully received. This does not include frames received with frame-too-long, frame check sequence (FCS), length or alignment errors, or frames lost due to other MAC errors.

 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t a_frames_received_ok_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - A count of frames that are successfully received. This does not include frames received with frame-too-long, frame check sequence (FCS), length or alignment errors, or frames lost due to other MAC errors.

 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t a_frames_received_ok_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - A count of receive frames that are an integral number of octets in length and do not pass the FCS check. This does not include frames received with frame-too-long, or frame-too-short (frame fragment) errors.
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t a_frame_check_sequence_errors_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - A count of receive frames that are an integral number of octets in length and do not pass the FCS check. This does not include frames received with frame-too-long, or frame-too-short (frame fragment) errors.
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t a_frame_check_sequence_errors_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - A count of frames that are not an integral number of octets in length and do not pass the FCS check.
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t a_alignment_errors_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - A count of frames that are not an integral number of octets in length and do not pass the FCS check.
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t a_alignment_errors_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - A count of data and padding octets of frames that are successfully transmitted.
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t a_octets_transmitted_ok_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - A count of data and padding octets of frames that are successfully transmitted.
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t a_octets_transmitted_ok_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - A count of data and padding octets in frames that are successfully received. This does not include octets in frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to other MAC errors.
 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t a_octets_received_ok_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - A count of data and padding octets in frames that are successfully received. This does not include octets in frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to other MAC errors.
 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t a_octets_received_ok_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - A count of frames that are successfully transmitted to a group destination address other than broadcast.
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t a_multicast_frames_xmitted_ok_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - A count of frames that are successfully transmitted to a group destination address other than broadcast.
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t a_multicast_frames_xmitted_ok_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded.
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t a_broadcast_frames_xmitted_ok_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded.
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t a_broadcast_frames_xmitted_ok_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - A count of frames that are successfully received and directed to an active nonbroadcast group address. This does not include frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to internal MAC sublayer error. 
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t a_multicast_frames_received_ok_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - A count of frames that are successfully received and directed to an active nonbroadcast group address. This does not include frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to internal MAC sublayer error. 
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t a_multicast_frames_received_ok_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded. 
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t a_broadcast_frames_received_ok_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded. 
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t a_broadcast_frames_received_ok_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - A count of frames with a length/type field value between the minimum unpadded MAC client data size and the maximum allowed MAC client data size, inclusive, that does not match the number of MAC client data octets received. The counter also increments for frames whose length/type field value is less than the minimum allowed unpadded MAC client data size and the number of MAC client data octets received is greater than the minimum unpadded MAC client data size.
 */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t a_in_range_length_errors_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - A count of frames with a length/type field value between the minimum unpadded MAC client data size and the maximum allowed MAC client data size, inclusive, that does not match the number of MAC client data octets received. The counter also increments for frames whose length/type field value is less than the minimum allowed unpadded MAC client data size and the number of MAC client data octets received is greater than the minimum unpadded MAC client data size.
 */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t a_in_range_length_errors_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - A count of frames with a length field value greater than the maximum allowed LLC data size. 
 */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t a_out_of_range_length_field_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - A count of frames with a length field value greater than the maximum allowed LLC data size. 
 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t a_out_of_range_length_field_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - A count of frames received that exceed the maximum permitted frame size by IEEE 802.3 (MTU size).
 */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t a_frame_too_long_errors_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - A count of frames received that exceed the maximum permitted frame size by IEEE 802.3 (MTU size).
 */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t a_frame_too_long_errors_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - For full duplex operation at 1000 Mb/s, it is a count of the number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate "Data reception error".
For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a count of the number of times the receiving media is non-idle for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate
Error.
 */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t a_symbol_error_during_carrier_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - For full duplex operation at 1000 Mb/s, it is a count of the number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate "Data reception error".
For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a count of the number of times the receiving media is non-idle for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate
Error.
 */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t a_symbol_error_during_carrier_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - A count of MAC Control frames passed to the MAC sublayer for transmission.
 */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t a_mac_control_frames_transmitted_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - A count of MAC Control frames passed to the MAC sublayer for transmission.
 */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t a_mac_control_frames_transmitted_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - A count of MAC Control frames passed by the MAC sublayer to the MAC Control sublayer.
 */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t a_mac_control_frames_received_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - A count of MAC Control frames passed by the MAC sublayer to the MAC Control sublayer.
 */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t a_mac_control_frames_received_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - A count of MAC Control frames received that contain an opcode that is not supported by the device.
 */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t a_unsupported_opcodes_received_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - A count of MAC Control frames received that contain an opcode that is not supported by the device.
 */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t a_unsupported_opcodes_received_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - A count of MAC PAUSE frames passed by the MAC sublayer to the MAC Control sublayer.
 */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t a_pause_mac_ctrl_frames_received_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - A count of MAC PAUSE frames passed by the MAC sublayer to the MAC Control sublayer.
 */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t a_pause_mac_ctrl_frames_received_low;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - A count of PAUSE frames passed to the MAC sublayer for transmission.
 */
	/* 0x90.0 - 0x90.31 */
	/* access: RO */
	u_int32_t a_pause_mac_ctrl_frames_transmitted_high;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - A count of PAUSE frames passed to the MAC sublayer for transmission.
 */
	/* 0x94.0 - 0x94.31 */
	/* access: RO */
	u_int32_t a_pause_mac_ctrl_frames_transmitted_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_discard_cntrs_grp_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ingress general 

 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t ingress_general_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Ingress general 

 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t ingress_general_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Ingress policy engine discards */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ingress_policy_engine_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Ingress policy engine discards */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t ingress_policy_engine_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Ingress VLAN membership filter discards */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t ingress_vlan_membership_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Ingress VLAN membership filter discards */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t ingress_vlan_membership_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Ingress VLAN tag allowance (tagged, untagged and prio-tagged) filter discards */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t ingress_tag_frame_type_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Ingress VLAN tag allowance (tagged, untagged and prio-tagged) filter discards */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t ingress_tag_frame_type_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Egress VLAN membership filter discards */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t egress_vlan_membership_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Egress VLAN membership filter discards */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t egress_vlan_membership_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Loop-back filter discards */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t loopback_filter_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Loop-back filter discards */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t loopback_filter_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Egress general discards
 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t egress_general_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Egress general discards
 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t egress_general_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Head-of-Queue time-out discards */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t egress_hoq_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Head-of-Queue time-out discards */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t egress_hoq_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Port isolation filter discards
[IInternal] Not supported due to HW bug. */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t port_isolation_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - Port isolation filter discards
[IInternal] Not supported due to HW bug. */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t port_isolation_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - Egress policy engine discards */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t egress_policy_engine_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - Egress policy engine discards */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t egress_policy_engine_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - Per ingress port count dropped packets due to egress link down */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t ingress_tx_link_down_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - Per ingress port count dropped packets due to egress link down */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t ingress_tx_link_down_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Egress spanning tree filter */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t egress_stp_filter_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - Egress spanning tree filter */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t egress_stp_filter_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state 

Reserved for Switches */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t egress_hoq_stall_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state 

Reserved for Switches */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t egress_hoq_stall_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - Number of packets dropped, because the Switch Lifetime Limit was exceeded. 

Applies for switches only. Reserved for HCAs */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t egress_sll_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Number of packets dropped, because the Switch Lifetime Limit was exceeded. 

Applies for switches only. Reserved for HCAs */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t egress_sll_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - Number of packets dropped for of any reason.
 Note: see description in the description area for limitations of this counter.
Applies for switches only. Reserved for HCAs

Note: deprecated for all Ethernet devices */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t ingress_discard_all_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - Number of packets dropped for of any reason.
 Note: see description in the description area for limitations of this counter.
Applies for switches only. Reserved for HCAs

Note: deprecated for all Ethernet devices */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t ingress_discard_all_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.
time = port_transmit_wait*4 [ns]

 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t port_transmit_wait_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.
time = port_transmit_wait*4 [ns]

 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t port_transmit_wait_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - A count of packets marked as ECN or potentially marked as ECN.
ECN Counting enable/disable is configurable. 
Valid only for Spectrum family.

 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ecn_marked_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - A count of packets marked as ECN or potentially marked as ECN.
ECN Counting enable/disable is configurable. 
Valid only for Spectrum family.

 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t ecn_marked_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The number of multicast packets dropped due to lack of egress buffer resources.
Valid only for Spectrum.
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t no_buffer_discard_mc_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The number of multicast packets dropped due to lack of egress buffer resources.
Valid only for Spectrum.
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t no_buffer_discard_mc_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The number of received EBP packets.
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t rx_ebp_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The number of received EBP packets.
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t rx_ebp_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The number of transmitted EBP packets.
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t tx_ebp_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The number of transmitted EBP packets.
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t tx_ebp_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The number of events where the port rx buffer has passed a fullness threshold 

Reserved for Switches. */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t rx_buffer_almost_full_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The number of events where the port rx buffer has passed a fullness threshold 

Reserved for Switches. */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t rx_buffer_almost_full_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The number of events where the port rx buffer has reached 100% fullness 

Reserved for Switches. */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t rx_buffer_full_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The number of events where the port rx buffer has reached 100% fullness 

Reserved for Switches. */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t rx_buffer_full_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - The number of roce packets with ICRC error

Reserved for Switches. */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t rx_icrc_encapsulated_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - The number of roce packets with ICRC error

Reserved for Switches. */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t rx_icrc_encapsulated_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were 64 octets in length (excluding framing bits but including FCS octets). */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts64octets_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were 64 octets in length (excluding framing bits but including FCS octets). */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts64octets_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 65 and 127 octets in length (excluding framing bits but including FCS octets). */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts65to127octets_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 65 and 127 octets in length (excluding framing bits but including FCS octets). */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts65to127octets_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 128 and 255 octets in length (excluding framing bits but including FCS octets). */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts128to255octets_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 128 and 255 octets in length (excluding framing bits but including FCS octets). */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts128to255octets_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 256 and 511 octets in length (excluding framing bits but including FCS octets). */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts256to511octets_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 256 and 511 octets in length (excluding framing bits but including FCS octets). */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts256to511octets_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets). */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts512to1023octets_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets). */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts512to1023octets_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets). */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts1024to1518octets_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets). */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts1024to1518octets_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets). */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts1519to2047octets_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets). */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts1519to2047octets_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets). */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts2048to4095octets_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets). */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts2048to4095octets_low;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets). */
	/* 0x90.0 - 0x90.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts4096to8191octets_high;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets). */
	/* 0x94.0 - 0x94.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts4096to8191octets_low;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).transmitted
 */
	/* 0x98.0 - 0x98.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts8192to10239octets_high;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - The total number of packets (including bad packets) transmitted that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).transmitted
 */
	/* 0x9c.0 - 0x9c.31 */
	/* access: RO */
	u_int32_t tx_stats_pkts8192to10239octets_low;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - A count of packets marked as ECE or potentially marked as ECE. */
	/* 0xa0.0 - 0xa0.31 */
	/* access: RO */
	u_int32_t ece_marked_high;
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - A count of packets marked as ECE or potentially marked as ECE. */
	/* 0xa4.0 - 0xa4.31 */
	/* access: RO */
	u_int32_t ece_marked_low;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - Counter is incremented upon packet payload internal checksum error */
	/* 0xa8.0 - 0xa8.31 */
	/* access: RO */
	u_int32_t tx_int_cksm_err_high;
/*---------------- DWORD[43] (Offset 0xac) ----------------*/
	/* Description - Counter is incremented upon packet payload internal checksum error */
	/* 0xac.0 - 0xac.31 */
	/* access: RO */
	u_int32_t tx_int_cksm_err_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_per_prio_grp_data_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The total number of octets received, including framing characters.
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t rx_octets_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The total number of octets received, including framing characters.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t rx_octets_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The total number of packets received for this priority (not including pause frames).
 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t rx_frames_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The total number of packets received for this priority (not including pause frames).
 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t rx_frames_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The total number of octets transmitted, including framing characters.


 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t tx_octets_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The total number of octets transmitted, including framing characters.


 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t tx_octets_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - The total number of packets transmitted.


 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t tx_frames_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - The total number of packets transmitted.


 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t tx_frames_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - The total number of PAUSE frames received from the far-end port.
 */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t rx_pause_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - The total number of PAUSE frames received from the far-end port.
 */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t rx_pause_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - The total time in microseconds that transmission of packets to the far-end port have been paused.
Note that if pause is global then tclass "0" will increment

 */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t rx_pause_duration_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - The total time in microseconds that transmission of packets to the far-end port have been paused.
Note that if pause is global then tclass "0" will increment

 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t rx_pause_duration_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - The total number of PAUSE or PFC frames sent to the far-end port.


 */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t tx_pause_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - The total number of PAUSE or PFC frames sent to the far-end port.


 */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t tx_pause_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - The total time in microseconds that the far-end port have been requested to pause.

 */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t tx_pause_duration_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - The total time in microseconds that the far-end port have been requested to pause.

 */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t tx_pause_duration_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - Counts the number of transitions from Xoff to Xon.

 */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t rx_pause_transition_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Counts the number of transitions from Xoff to Xon.

 */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t rx_pause_transition_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.



 */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t rx_discards_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.



 */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t rx_discards_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark
The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause). */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t device_stall_minor_watermark_cnt_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark
The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause). */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t device_stall_minor_watermark_cnt_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark
The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause).
 */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t device_stall_critical_watermark_cnt_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark
The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause).
 */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t device_stall_critical_watermark_cnt_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t wred_discard_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t wred_discard_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - A count of packets marked as ECN or potentially marked as ECN.
ECN Counting enable/disable is configurable. 

 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ecn_marked_tc_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - A count of packets marked as ECN or potentially marked as ECN.
ECN Counting enable/disable is configurable. 

 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t ecn_marked_tc_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_eth_per_traffic_class_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.

 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t transmit_queue_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.

 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t transmit_queue_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The number of unicast packets dropped due to lack of shared buffer resources.
Valid only for Spectrum.
Valid for HCA when ppcnt_no_buffer_uc is set in PCAM. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t no_buffer_discard_uc_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The number of unicast packets dropped due to lack of shared buffer resources.
Valid only for Spectrum.
Valid for HCA when ppcnt_no_buffer_uc is set in PCAM. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t no_buffer_discard_uc_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_module_latched_flag_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - when set, indicates modules supports rx los indication */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t rx_los_cap;
	/* Description - Valid for CMIS based modules only
Latched modules Datapath fw fault flag */
	/* 0x0.22 - 0x0.22 */
	/* access: RO */
	u_int8_t dp_fw_fault;
	/* Description - Valid for CMIS based modules only
Latched module fw fault flag */
	/* 0x0.23 - 0x0.23 */
	/* access: RO */
	u_int8_t mod_fw_fault;
	/* Description - Latched VCC flags of module
Bit 0: high_vcc_alarm
Bit 1: low_vcc_alarm
Bit 2: high_vcc_warning
Bit 3: low_vcc_warning */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t vcc_flags;
	/* Description - Latched temperature flags of module
Bit 0: high_temp_alarm
Bit 1: low_temp_alarm
Bit 2: high_temp_warning
Bit 3: low_temp_warning */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t temp_flags;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reserved for SFP
Bitmask for latched Tx adaptive equalization fault flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t tx_ad_eq_fault;
	/* Description - Bitmask for latched Tx cdr loss of lock flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t tx_cdr_lol;
	/* Description - Reserved for SFP
Bitmask for latched Tx loss of signal flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t tx_los;
	/* Description - Bitmask for latched Tx fault flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t tx_fault;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bitmask for latched Tx power low warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t tx_power_lo_war;
	/* Description - Bitmask for latched Tx power high warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t tx_power_hi_war;
	/* Description - Bitmask for latched Tx power low alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t tx_power_lo_al;
	/* Description - Bitmask for latched Tx power high alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t tx_power_hi_al;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Bitmask for latched Tx bias low warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t tx_bias_lo_war;
	/* Description - Bitmask for latched Tx bias high warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t tx_bias_hi_war;
	/* Description - Bitmask for latched Tx bias low alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t tx_bias_lo_al;
	/* Description - Bitmask for latched Tx bias high alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t tx_bias_hi_al;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bitmask for latched Rx cdr loss of lock flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x10.16 - 0x10.23 */
	/* access: RO */
	u_int8_t rx_cdr_lol;
	/* Description - Bitmask for latched Rx loss of signal flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t rx_los;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Bitmask for latched Rx power low warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x14.0 - 0x14.7 */
	/* access: RO */
	u_int8_t rx_power_lo_war;
	/* Description - Bitmask for latched Rx power high warning flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x14.8 - 0x14.15 */
	/* access: RO */
	u_int8_t rx_power_hi_war;
	/* Description - Bitmask for latched Rx power low alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x14.16 - 0x14.23 */
	/* access: RO */
	u_int8_t rx_power_lo_al;
	/* Description - Bitmask for latched Rx power high alarm flag per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x14.24 - 0x14.31 */
	/* access: RO */
	u_int8_t rx_power_hi_al;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Bitmask for latched rx output valid change per lane.
Bit 0 - lane 0 ... Bit 7 - lane 7 */
	/* 0x18.0 - 0x18.7 */
	/* access: RO */
	u_int8_t rx_output_valid_change;
};

/* Description -   */
/* Size in bytes - 244 */
struct reg_access_gpu_pddr_link_down_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Which receiver caused last link down: 
0: Unknown
1: Local_phy
2: Remote_phy */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t down_blame;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Opcde of link down reason for local / remote side: 
0: No_link_down_indication
1: Unknown_reason
2: Hi_SER_or_Hi_BER
3: Block_Lock_loss
4: Alignment_loss
5: FEC_sync_loss
6: PLL_lock_loss
7: FIFO_overflow
8: false_SKIP_condition
9: Minor_Error_threshold_exceeded
10: Physical_layer_retransmission_timeout
11: Heartbeat_errors
12: Link_Layer_credit_monitoring_watchdog
13: Link_Layer_integrity_threshold_exceeded
14: Link_Layer_buffer_overrun
15: Down_by_outband_command_with_healthy_link
16: Down_by_outband_command_for_link_with_hi_ber
17: Down_by_inband_command_with_healthy_link
18: Down_by_inband_command_for_link_with_hi_ber
19: Down_by_verification_GW
20: Received_Remote_Fault 
21: Received_TS1
22: Down_by_management_command
23: Cable_was_unplugged
24: Cable_access_issue 
25: Thermal_shutdown 
26: Current_issue 
27: Power_budget
28: Fast_recovery_raw_ber
29: Fast_recovery_effective_ber
30: Fast_recovery_symbol_ber
31: Fast_recovery_credit_watchdog
32: Peer_side_down_to_sleep_state
33: Peer_side_down_to_disable_state
34: Peer_side_down_to_disable_and_port_lock
35: Peer_side_down_due_to_thermal_event
36: Peer_side_down_due_to_force_event
37: Peer_side_down_due_to_reset_event */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t local_reason_opcode;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Opcde of link down reason for local / remote side: 
0: No_link_down_indication
1: Unknown_reason
2: Hi_SER_or_Hi_BER
3: Block_Lock_loss
4: Alignment_loss
5: FEC_sync_loss
6: PLL_lock_loss
7: FIFO_overflow
8: false_SKIP_condition
9: Minor_Error_threshold_exceeded
10: Physical_layer_retransmission_timeout
11: Heartbeat_errors
12: Link_Layer_credit_monitoring_watchdog
13: Link_Layer_integrity_threshold_exceeded
14: Link_Layer_buffer_overrun
15: Down_by_outband_command_with_healthy_link
16: Down_by_outband_command_for_link_with_hi_ber
17: Down_by_inband_command_with_healthy_link
18: Down_by_inband_command_for_link_with_hi_ber
19: Down_by_verification_GW
20: Received_Remote_Fault 
21: Received_TS1
22: Down_by_management_command
23: Cable_was_unplugged
24: Cable_access_issue 
25: Thermal_shutdown 
26: Current_issue 
27: Power_budget
28: Fast_recovery_raw_ber
29: Fast_recovery_effective_ber
30: Fast_recovery_symbol_ber
31: Fast_recovery_credit_watchdog
32: Peer_side_down_to_sleep_state
33: Peer_side_down_to_disable_state
34: Peer_side_down_to_disable_and_port_lock
35: Peer_side_down_due_to_thermal_event
36: Peer_side_down_due_to_force_event
37: Peer_side_down_due_to_reset_event */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t remote_reason_opcode;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - see local_reason_opcode for local reason opcode
for remote reason opcode: local_reason_opcode+100 */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t e2e_reason_opcode;
	/* Description - TS1 opcode describes the reason the peer requested to ramp down the link:
0x8: TS1.Sleep
0x9: TS1.Disable
0xA: TS1.PortLock
0xB: TS1.Thermal
0xC: TS1.Clean 
0xD  : TS1.Force
0xE: TS1.reset_req

Note: This field is valid in case the local_reason_opcode = 21 or 32-38 */
	/* 0xc.12 - 0xc.15 */
	/* access: RO */
	u_int8_t ts1_opcode;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Minimal estimated effective BER window measured.

Estimated_Effective_BER = min_est_eff_ber_coef*10^(-min_esteff_ber_magnitude) */
	/* 0x30.0 - 0x30.7 */
	/* access: RO */
	u_int8_t min_est_eff_ber_magnitude;
	/* Description - Minimal estimated effective BER window measured.

Estimated_Effective_BER = min_est_eff_ber_coef*10^(-min_esteff_ber_magnitude) */
	/* 0x30.8 - 0x30.11 */
	/* access: RO */
	u_int8_t min_est_eff_ber_coef;
	/* Description - Mean estimated effective BER window measured.

Estimated_Effective_BER = mean_est_eff_ber_coef*10^(-mean_est_eff_ber_magnitude) */
	/* 0x30.16 - 0x30.23 */
	/* access: RO */
	u_int8_t mean_est_eff_ber_magnitude;
	/* Description - Mean estimated effective BER window measured.

Estimated_Effective_BER = mean_est_eff_ber_coef*10^(-mean_est_eff_ber_magnitude) */
	/* 0x30.24 - 0x30.27 */
	/* access: RO */
	u_int8_t mean_est_eff_ber_coef;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Maximal estimated effective BER window measured.

Estimated_Effective_BER = max_est_eff_ber_coef*10^(-max_est_eff_ber_magnitude) */
	/* 0x34.0 - 0x34.7 */
	/* access: RO */
	u_int8_t max_est_eff_ber_magnitude;
	/* Description - Maximal estimated effective BER window measured.

Estimated_Effective_BER = max_est_eff_ber_coef*10^(-max_est_eff_ber_magnitude) */
	/* 0x34.8 - 0x34.11 */
	/* access: RO */
	u_int8_t max_est_eff_ber_coef;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Number of Estimated Effective BER Windows that crossed alarm threshold */
	/* 0x38.0 - 0x38.15 */
	/* access: RO */
	u_int16_t num_of_est_eff_ber_alarms;
	/* Description - Number of Estimated Effective BER Windows that crossed warning threshold
 */
	/* 0x38.16 - 0x38.31 */
	/* access: RO */
	u_int16_t num_of_est_eff_ber_warnings;
};

/* Description -   */
/* Size in bytes - 216 */
struct reg_access_gpu_pddr_module_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - QSFP:
Ethernet Compliance Codes bit mask (10/40G/100G)
Byte131 per SFF-8636 
Bit 7 - Extended Specification Compliance valid
Bit 6 - 10GBASE-LRM
Bit 5 - 10GBASE-LR
Bit 4 - 10GBASE-SR
Bit 3 - 40GBASE-CR4
Bit 2 - 40GBASE-SR4
Bit 1 - 40GBASE-LR4
Bit 0 - 40G Active Cable (XLPPI)

SFP : 
10G Ethernet Compliance Codes
Byte3 per SFF-8472:
Bit 7 - 10G Base-ER 
Bit 6 - 10G Base-LRM 
Bit 5 - 10G Base-LR 
Bit 4 - 10G Base-SR

CMIS based (QSFP-DD/ SFP-DD / OSFP)
Byte 87 - Module Media Interface */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t ethernet_compliance_code;
	/* Description - Extended Specification Compliance Codes 
for SFP:
byte 36 per SFF-8472

for QSFP:
byte192 per SFF-8636 (QSFP28) 

for CMIS (SFP-DD / QSFP-DD/ OSFP):
Byte 86 - Host Electrical Interface */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t ext_ethernet_compliance_code;
	/* Description - Reserved for SFP. 

For QSFP:
Byte113 per SFF-8636

For CMIS based modules:

XX naming is according to cable_identifier name
For example: if cable_identifier = ,6 XX string is QSFP-DD

0 - Unspecified
1 - XX to XX
2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)
3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)
4 - XX to 8xSFP
5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)
6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or 2xSFP-DD
7 - XX (depopulated / 4 lanes) to 4xSFP
8 - XX(/ 2 lane module) to XX
9 - XX(/ 2 lane module) to 2xSFP */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t cable_breakout;
	/* Description - QSFP: 
Byte 147 per SFF-8636.

SFP:
SFP+ Cable Technology: 
byte8 per SFF-8472:
Bit 3 - Active Cable
Bit 2 - Passive Cable

CMIS based (QSFP-DD / OSFP/ SFP-DD):
Byte 212 */
	/* 0x0.24 - 0x0.31 */
	/* access: RW */
	u_int8_t cable_technology;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module maximum power consumption for SFP/QSFP:
0: Power_Class_0 - (1.0 W max)
1: Power_Class_1 - (1.5 W max)
2: Power_Class_2 - (2.0 W max)
3: Power_Class_3 - (2.5 W max)
4: Power_Class_4 - (3.5 W max)
5: Power_Class_5 - (4.0 W max)
6: Power_Class_6 - (4.5 W max)
7: Power_Class_7 - (5.0 W max)
8: Power_Class_8 - (power from max_power field)

Module maximum power consumption for SFP-DD:
0: Power_Class_0 - (0.5 W max)
1: Power_Class_1 - (1.0 W max)
2: Power_Class_2 - (1.5 W max)
3: Power_Class_3 - (2.0 W max)
4: Power_Class_4 - (3.5 W max)
5: Power_Class_5 - (5.0 W max)
6: reserved
7: reserved
8: Power_Class_8 - (power from max_power field)

Module maximum power consumption for QSFP-DD/OSFP:
1 - Power_Class_1 - (1.5 W max)
2 - Power_Class_2 - (3.5 W max)
3 - Power_Class_3 - (7.0 W max)
4 - Power_Class_4 - (8.0 W max)
5 - Power_Class_5 - (10 W max)
6 - Power_Class_6 - (12 W max)
7 - Power_Class_7 - (14 W max)
8 - Power_Class_8 - (power from max_power field) */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t cable_power_class;
	/* Description - 0: QSFP28
1: QSFP_Plus
2: SFP28_or_SFP_Plus
3: QSA - (QSFP->SFP)
4: Backplane
5: SFP_DD
6: QSFP_DD
7: QSFP_CMIS
8: OSFP
9: C2C
10: DSFP
11: QSFP_Split_Cable

identifiers that are CMIS compliant are: 5,6,7,8,10 */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t cable_identifier;
	/* Description - Cable length in 1m units.

For CMIS modules:
bits 6:7 represent cable_length_multiplier for calculating cable length
00 - 0.1 multiplier (0.1 to 6.3m)
01- 1 multiplier (1 to 63m)
10 - 10 multiplier (10 to 630m)
11 - 100 multiplier (100 to 6300m)

bits 0:5 represent cable_length_value for calculating cable length.
length is calculated with cable_length_value * cable_length_multiplier */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t cable_length;
	/* Description - Cable vendor:
0: Other
1: Mellanox
2: Known_OUI
3: NVIDIA
 */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t cable_vendor;
	/* Description - Cable/module type:
0: Unidentified
1: Active_cable - (active copper / optics)
2: Optical_Module - (separated)
3: Passive_copper_cable
4: Cable_unplugged
5: Twisted_pair
 */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t cable_type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 
 */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t cable_tx_equalization;
	/* Description - 
For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-emphasis. */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t cable_rx_emphasis;
	/* Description - Reserved for SFP
 */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t cable_rx_amp;
	/* Description - Reserved for SFP, QSFP
Byte 201 for CMIS (QSFP-DD/ SFP-DD/ OSFP)
Other Cable ignore field. */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t max_power;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Reserved for SFP */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t cable_attenuation_5g;
	/* Description - Reserved for SFP */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t cable_attenuation_7g;
	/* Description - Reserved for SFP */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t cable_attenuation_12g;
	/* Description - Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)
Other Cable ignore field. */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t cable_attenuation_25g;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Reserved for SFP

Bit 0 - TX CDR on/off on channel 0 
Bit 1 - TX CDR on/off on channel 1 
Bit 2 - TX CDR on/off on channel 2 
Bit 3 - TX CDR on/off on channel 3 
Bit 4 - TX CDR on/off on channel 4 
Bit 5 - TX CDR on/off on channel 5 
Bit 6 - TX CDR on/off on channel 6 
Bit 7 - TX CDR on/off on channel 7 

CDR on - when bit is set.
CDR off - when bit is clear.
 */
	/* 0x10.0 - 0x10.7 */
	/* access: RO */
	u_int8_t tx_cdr_state;
	/* Description - Reserved for SFP

Bit 0 - RX CDR on/off on channel 0 
Bit 1 - RX CDR on/off on channel 1 
Bit 2 - RX CDR on/off on channel 2 
Bit 3 - RX CDR on/off on channel 3
Bit 4 - RX CDR on/off on channel 4 
Bit 5 - RX CDR on/off on channel 5 
Bit 6 - RX CDR on/off on channel 6 
Bit 7 - RX CDR on/off on channel 7 

CDR on - when bit is set.
CDR off - when bit is clear.
 */
	/* 0x10.8 - 0x10.15 */
	/* access: RO */
	u_int8_t rx_cdr_state;
	/* Description - 0 - No CDR
1 - Build-in CDR with on/off control 
2 - Build-in CDR without on/off control */
	/* 0x10.16 - 0x10.19 */
	/* access: RO */
	u_int8_t tx_cdr_cap;
	/* Description - 0 - No CDR
1 - Build-in CDR with on/off control 
2 - Build-in CDR without on/off control */
	/* 0x10.20 - 0x10.23 */
	/* access: RO */
	u_int8_t rx_cdr_cap;
	/* Description - Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)
Rx post-emphasis. */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t cable_rx_post_emphasis;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - ASCII Vendor name left-aligned and padded on the right with
ASCII spaces (20h) */
	/* 0x14.0 - 0x20.31 */
	/* access: RO */
	u_int32_t vendor_name[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Vendor Part Number left-aligned and padded on the right with ASCII spaces (20h) */
	/* 0x24.0 - 0x30.31 */
	/* access: RO */
	u_int32_t vendor_pn[4];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - ASCII Vendor revision aligned to right padded with 0h on the left */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t vendor_rev;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - If information is not available by the module: set to 0 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t fw_version;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Vendor Serial Number */
	/* 0x3c.0 - 0x48.31 */
	/* access: RO */
	u_int32_t vendor_sn[4];
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - Internally measured supply voltage in 100uV */
	/* 0x4c.0 - 0x4c.15 */
	/* access: RO */
	u_int16_t voltage;
	/* Description - module temperature in 1/256 C */
	/* 0x4c.16 - 0x4c.31 */
	/* access: RO */
	u_int16_t temperature;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - RX measured power channel 1.
measured in dBm/uW according to module_info_ext value */
	/* 0x50.0 - 0x50.15 */
	/* access: RO */
	u_int16_t rx_power_lane1;
	/* Description - RX measured power channel 0.
measured in dBm/uW according to module_info_ext value */
	/* 0x50.16 - 0x50.31 */
	/* access: RO */
	u_int16_t rx_power_lane0;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - RX measured power channel 3.
measured in dBm/uW according to module_info_ext value */
	/* 0x54.0 - 0x54.15 */
	/* access: RO */
	u_int16_t rx_power_lane3;
	/* Description - RX measured power channel 2.
measured in dBm/uW according to module_info_ext value */
	/* 0x54.16 - 0x54.31 */
	/* access: RO */
	u_int16_t rx_power_lane2;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - RX measured power channel 5.
measured in dBm/uW according to module_info_ext value */
	/* 0x58.0 - 0x58.15 */
	/* access: RO */
	u_int16_t rx_power_lane5;
	/* Description - RX measured power channel 4.
measured in dBm/uW according to module_info_ext value */
	/* 0x58.16 - 0x58.31 */
	/* access: RO */
	u_int16_t rx_power_lane4;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - RX measured power channel 7.
measured in dBm/uW according to module_info_ext value */
	/* 0x5c.0 - 0x5c.15 */
	/* access: RO */
	u_int16_t rx_power_lane7;
	/* Description - RX measured power channel 6.
measured in dBm/uW according to module_info_ext value */
	/* 0x5c.16 - 0x5c.31 */
	/* access: RO */
	u_int16_t rx_power_lane6;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - TX measured power channel 1.
measured in dBm/uW according to module_info_ext value */
	/* 0x60.0 - 0x60.15 */
	/* access: RO */
	u_int16_t tx_power_lane1;
	/* Description - TX measured power channel 0.
measured in dBm/uW according to module_info_ext value */
	/* 0x60.16 - 0x60.31 */
	/* access: RO */
	u_int16_t tx_power_lane0;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - TX measured power channel 3.
measured in dBm/uW according to module_info_ext value */
	/* 0x64.0 - 0x64.15 */
	/* access: RO */
	u_int16_t tx_power_lane3;
	/* Description - TX measured power channel 2.
measured in dBm/uW according to module_info_ext value */
	/* 0x64.16 - 0x64.31 */
	/* access: RO */
	u_int16_t tx_power_lane2;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - TX measured power channel 5.
measured in dBm/uW according to module_info_ext value */
	/* 0x68.0 - 0x68.15 */
	/* access: RO */
	u_int16_t tx_power_lane5;
	/* Description - TX measured power channel 4.
measured in dBm/uW according to module_info_ext value */
	/* 0x68.16 - 0x68.31 */
	/* access: RO */
	u_int16_t tx_power_lane4;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - TX measured power channel 7.
measured in dBm/uW according to module_info_ext value */
	/* 0x6c.0 - 0x6c.15 */
	/* access: RO */
	u_int16_t tx_power_lane7;
	/* Description - TX measured power channel 6.
measured in dBm/uW according to module_info_ext value */
	/* 0x6c.16 - 0x6c.31 */
	/* access: RO */
	u_int16_t tx_power_lane6;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x70.0 - 0x70.15 */
	/* access: RO */
	u_int16_t tx_bias_lane1;
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x70.16 - 0x70.31 */
	/* access: RO */
	u_int16_t tx_bias_lane0;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x74.0 - 0x74.15 */
	/* access: RO */
	u_int16_t tx_bias_lane3;
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x74.16 - 0x74.31 */
	/* access: RO */
	u_int16_t tx_bias_lane2;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x78.0 - 0x78.15 */
	/* access: RO */
	u_int16_t tx_bias_lane5;
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x78.16 - 0x78.31 */
	/* access: RO */
	u_int16_t tx_bias_lane4;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x7c.0 - 0x7c.15 */
	/* access: RO */
	u_int16_t tx_bias_lane7;
	/* Description - TX measured bias current on channel [i] in 2uA unit.

The real sample value in uA units should be calculated as follows:
tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x7c.16 - 0x7c.31 */
	/* access: RO */
	u_int16_t tx_bias_lane6;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Alarm low temperature threshold in 1/256 C */
	/* 0x80.0 - 0x80.15 */
	/* access: RO */
	u_int16_t temperature_low_th;
	/* Description - Alarm high temperature threshold in 1/256 C */
	/* 0x80.16 - 0x80.31 */
	/* access: RO */
	u_int16_t temperature_high_th;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - Alarm low Voltage threshold in 100uV */
	/* 0x84.0 - 0x84.15 */
	/* access: RO */
	u_int16_t voltage_low_th;
	/* Description - Alarm high Voltage threshold in 100uV */
	/* 0x84.16 - 0x84.31 */
	/* access: RO */
	u_int16_t voltage_high_th;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Alarm low RX Power threshold in dBm. 
Taking only from channel 0. */
	/* 0x88.0 - 0x88.15 */
	/* access: RO */
	u_int16_t rx_power_low_th;
	/* Description - Alarm high RX Power threshold in dBm. 
Taking only from channel 0. */
	/* 0x88.16 - 0x88.31 */
	/* access: RO */
	u_int16_t rx_power_high_th;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - Alarm low TX Power threshold in dBm. 
Taking only from channel 0. */
	/* 0x8c.0 - 0x8c.15 */
	/* access: RO */
	u_int16_t tx_power_low_th;
	/* Description - Alarm high TX Power threshold in dBm. 
Taking only from channel 0. */
	/* 0x8c.16 - 0x8c.31 */
	/* access: RO */
	u_int16_t tx_power_high_th;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - Alarm low TX Bias current threshold in 2 uA. 

The real threshold value in uA units should be calculated as follows:
tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x90.0 - 0x90.15 */
	/* access: RO */
	u_int16_t tx_bias_low_th;
	/* Description - Alarm high TX Bias current threshold in 2 uA.

The real threshold value in uA units should be calculated as follows:
tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value] */
	/* 0x90.16 - 0x90.31 */
	/* access: RO */
	u_int16_t tx_bias_high_th;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - Nominal laser wavelength in nm */
	/* 0x94.0 - 0x94.15 */
	/* access: RO */
	u_int16_t wavelength;
	/* Description - SMF link length
SFP per byte 14,15.
QSFP per byte 142
for CMIS based modules, per byte 132

bit 9:8 - 00 length base in 1 km units
bit 9:8 - 01 length base in 100m units
bits 7:0 - length base */
	/* 0x94.16 - 0x94.25 */
	/* access: RO */
	u_int16_t smf_length;
	/* Description - when set, indicates rx_output_valid is supported by the module */
	/* 0x94.26 - 0x94.26 */
	/* access: RW */
	u_int8_t rx_output_valid_cap;
	/* Description - set in case of Linear Direct Drive module */
	/* 0x94.27 - 0x94.27 */
	/* access: RO */
	u_int8_t did_cap;
	/* Description - rx power measurement type
0: OMA
1: Average_power */
	/* 0x94.28 - 0x94.28 */
	/* access: RO */
	u_int8_t rx_power_type;
	/* Description - Valid for CMIS modules only.
Module state:
0: reserved
1: LowPwr_state
2: PwrUp_state
3: Ready_state
4: PwrDn_state
5: Fault_state */
	/* 0x94.29 - 0x94.31 */
	/* access: RO */
	u_int8_t module_st;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - Byte 164 of SFF-8636
For CMIS modules IB Protocols. */
	/* 0x98.0 - 0x98.7 */
	/* access: RO */
	u_int8_t ib_compliance_code;
	/* Description - Valid for CMIS modules only.
This field is relevant for the following fields: tx_bias_lane[7:0], tx_bias_high_th and tx_bias_low_th.
The value of the above fields should be multiplied according to the tx_bias_scaling_factor value.
0: multiply_1x
1: multiply_2x
2: multiply_4x
 */
	/* 0x98.10 - 0x98.11 */
	/* access: RW */
	u_int8_t tx_bias_scaling_factor;
	/* Description - Valid for CMIS modules only.
According to current Active set, value of Module Media Interface byte */
	/* 0x98.16 - 0x98.23 */
	/* access: RO */
	u_int8_t active_set_media_compliance_code;
	/* Description - Valid for CMIS modules only.
According to current Active set, value of Host Electrical Interface byte */
	/* 0x98.24 - 0x98.31 */
	/* access: RO */
	u_int8_t active_set_host_compliance_code;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - Bitmask of width of IB Protocols */
	/* 0x9c.0 - 0x9c.5 */
	/* access: RO */
	u_int8_t ib_width;
	/* Description - monitoring capabilities mask
Bit 0 - temperature monitoring implemented
Bit 1 - voltage monitoring implemented
Bit 2 - tx power monitoring implemented
Bit 3 - rx power monitoring implemented
Bit 4 - tx bias monitoring implemented */
	/* 0x9c.8 - 0x9c.15 */
	/* access: RO */
	u_int8_t monitor_cap_mask;
	/* Description - Nominal bit rate in units of 100Mb/s */
	/* 0x9c.16 - 0x9c.23 */
	/* access: RO */
	u_int8_t nbr100;
	/* Description - Nominal bit rate in units of 250Mb/s */
	/* 0x9c.24 - 0x9c.31 */
	/* access: RO */
	u_int8_t nbr250;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - DataPath state for lane<i>
1: DPDeactivated
2: DPInit
3: DPDeinit
4: DPActivated
5: DPTxTurnOn
6: DPTxTurnOff
7: DPInitialized */
	/* 0xa0.28 - 0xa4.27 */
	/* access: RO */
	u_int8_t dp_st_lane[8];
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - OM5 fiber length supported in units of 2m */
	/* 0xa4.0 - 0xa4.7 */
	/* access: RO */
	u_int8_t length_om5;
	/* Description - OM4 fiber length supported in units of 2m
SFP in units of 10m */
	/* 0xa4.8 - 0xa4.15 */
	/* access: RO */
	u_int8_t length_om4;
	/* Description - OM3 fiber length supported in units of 2m
SFP in units of 10m */
	/* 0xa4.16 - 0xa4.23 */
	/* access: RO */
	u_int8_t length_om3;
	/* Description - OM2 fiber length supported in units of 1m
SFP in units of 10m */
	/* 0xa4.24 - 0xa4.31 */
	/* access: RO */
	u_int8_t length_om2;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - memory map revision */
	/* 0xa8.0 - 0xa8.7 */
	/* access: RO */
	u_int8_t memory_map_rev;
	/* Description - 16-bit integer value for the laser wavelength tolerance in nm divided by 200 (units of 0.005nm). */
	/* 0xa8.8 - 0xa8.23 */
	/* access: RO */
	u_int16_t wavelength_tolerance;
	/* Description - OM1 fiber length supported in units of 10m */
	/* 0xa8.24 - 0xa8.31 */
	/* access: RO */
	u_int8_t length_om1;
/*---------------- DWORD[43] (Offset 0xac) ----------------*/
	/* Description - memory map compliance in ASCII.
SFF-8472 / SFF-8636/ CMIS */
	/* 0xac.0 - 0xac.31 */
	/* access: RO */
	u_int32_t memory_map_compliance;
/*---------------- DWORD[44] (Offset 0xb0) ----------------*/
	/* Description - ASCII code for vendor's date code.
63:48- 2 digit for date code year, 00 = year 2000
47:32 - 2 digit for date code month.
31:16 - 2 digit for day of the month code.
15:0 - 2 digit LOT code. */
	/* 0xb0.0 - 0xb4.31 */
	/* access: RO */
	u_int64_t date_code;
/*---------------- DWORD[46] (Offset 0xb8) ----------------*/
	/* Description - vendor oui */
	/* 0xb8.0 - 0xb8.23 */
	/* access: RO */
	u_int32_t vendor_oui;
	/* Description - connector type based on SFF-8024 */
	/* 0xb8.24 - 0xb8.31 */
	/* access: RO */
	u_int8_t connector_type;
/*---------------- DWORD[47] (Offset 0xbc) ----------------*/
	/* Description - Rx output status indication per lane */
	/* 0xbc.0 - 0xbc.7 */
	/* access: RO */
	u_int8_t rx_output_valid;
	/* Description - cable attenuation at 53GHz */
	/* 0xbc.8 - 0xbc.15 */
	/* access: RO */
	u_int8_t cable_attenuation_53g;
	/* Description - Defines which Tx input lanes must be frequency synchronous.
0: Tx_input_lanes_1_8
1: Tx_input_lanes_1_4_and_5-8
2: Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8
3: Lanes_may_be_asynchronous_in_frequency */
	/* 0xbc.16 - 0xbc.17 */
	/* access: RO */
	u_int8_t tx_input_freq_sync;
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description - Relevant for CMIS modules only
Error Code response for ConrolSet configuration of DataPath.
0x0: ConfigUndefined
0x1: ConfigSuccess
0x2: ConfigRejected
0x3: ConfigRejectedInvalidAppSel
0x4: ConfigRejectedInvalidDataPath
0x5: ConfigRejectedInvalidSI
0x6: ConfigRejectedLanesInUse
0x7: ConfigRejectedPartialDataPath
0xC: ConfigInProgress */
	/* 0xc0.0 - 0xc0.3 */
	/* access: RO */
	u_int8_t error_code;
	/* Description - Maximum length of allowed fiber in meters */
	/* 0xc0.16 - 0xc0.31 */
	/* access: RO */
	u_int16_t max_fiber_length;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_pddr_operation_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: protocol_was_not_negotiated - (force mode)
1: MLPN_rev0_negotiated
2: CL73_Ethernet_negotiated
3: Protocol_according_to_Parallel_detect - (remote port in force mode)
4: Standard_IB_negotiated
8: NLPN_rev2_negotiated
9: HS_NLPN_rev2_negotiated_ */
	/* 0x0.16 - 0x0.19 */
	/* access: RO */
	u_int8_t neg_mode_active;
	/* Description - Active protocol:
Bit 0: InfiniBand
Bit 2: Ethernet
Bit 3: NVLink */
	/* 0x0.20 - 0x0.23 */
	/* access: RO */
	u_int8_t proto_active;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - FW IB state machine:
0x0: IB_AN_FSM_DISABLED
0x1: IB_AN_FSM_INITIALY
0x2: IB_AN_FSM_RCVR_CFG
0x3: IB_AN_FSM_CFG_TEST
0x4: IB_AN_FSM_WAIT_RMT_TEST
0x5: IB_AN_FSM_WAIT_CFG_ENHANCED
0x6: IB_AN_FSM_CFG_IDLE
0x7: IB_AN_FSM_LINK_UP
0x8: IB_AN_FSM_POLLING */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ib_phy_fsm_state;
	/* Description - Ethernet (CL73) Auto-negotiation FSM state:
0x0: ETH_AN_FSM_ENABLE
0x1: ETH_AN_FSM_XMIT_DISABLE
0x2: ETH_AN_FSM_ABILITY_DETECT
0x3: ETH_AN_FSM_ACK_DETECT
0x4: ETH_AN_FSM_COMPLETE_ACK
0x5: ETH_AN_FSM_AN_GOOD_CHECK
0x6: ETH_AN_FSM_AN_GOOD
0x7: ETH_AN_FSM_NEXT_PAGE_WAIT */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t eth_an_fsm_state;
	/* Description - FW Phy Manager FSM state:
0: Disabled 
1: Open_port
2: Polling
3: Active
4: Close_port
5: Phy_up
6: Sleep
7: Rx_disable
8: Signal_detect
9: Receiver_detect
10: Sync_peer
11: Negotiation
12: Training
13: SubFSM_active */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t phy_mngr_fsm_state;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For IB: Table 671, "PDDR - Phy manager link enabled IB layout," on page 703
For Ethernet: Table 673, "PDDR - Phy manager link enabled Eth layout," on page 703
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext phy_manager_link_enabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For IB: Table 675, "PDDR - core2phy link enabled IB layout," on page 704
For Ethernet: Table 677, "PDDR - Core2Phy link enabled Eth layout," on page 705 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext core_to_phy_link_enabled;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - For IB: Table 679, "PDDR - cable cap IB layout," on page 706
For Ethernet: Table 681, "PDDR - cable cap Eth layout," on page 707
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext cable_proto_cap;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - For IB: Table 683, "PDDR - Link Active IB layout," on page 708
For Ethernet: Table 685, "PDDR - Link Active Eth layout," on page 708 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext link_active;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - 0: No_loopback_active
1: Phy_remote_loopback 
2: Phy_local_loopback -When set the port's egress traffic is looped back to the receiver and the port transmitter is disabled. 
4: External_local_loopback -Enables the port's transmitter to link with the port's receiver using an external loopback connector. */
	/* 0x18.0 - 0x18.11 */
	/* access: RO */
	u_int16_t loopback_mode;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - FEC mode request
See fec_mode_active
for supported retransmission mode see PPLM.fec_mode_capability */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t fec_mode_request;
	/* Description - FEC mode active
0: No_FEC
1: Firecode_FEC
2: Standard_RS_FEC - RS(528,514)
3: Standard_LL_RS_FEC - RS(271,257)
6: Interleaved_Standard_RS-FEC - (544,514)
7: Standard_RS-FEC - (544,514)
9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)
10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1) */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t fec_mode_active;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - FEC 100G (25Gb/s per lane) supported FEC include override masking , should reflect current phy configuration after link is up

Bit 0 - No FEC
Bit 2 - Standard RS-FEC - RS(528,514)
 */
	/* 0x20.0 - 0x20.3 */
	/* access: RO */
	u_int8_t eth_100g_fec_support;
	/* Description - FEC 25G/50G (25Gb/s per lane) supported FEC include override masking , should reflect current phy configuration after link is up
Bit 0 - No FEC
Bit 1 - Firecode FEC
Bit 2 - Standard RS-FEC - RS(528,514)
 */
	/* 0x20.4 - 0x20.7 */
	/* access: RO */
	u_int8_t eth_25g_50g_fec_support;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - For IB: Table 695, "PDDR - ETH AN Link Enabled Eth Layout," on page 711 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t eth_an_link_enabled;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_pddr_phy_info_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port notifications bit mask
Bit 0 - Link partner advertised capabilities 
Bit 1 - Speed degradation */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t port_notifications;
	/* Description - Bit 0: eth_base_page
Bit 1: ib_base_page
Bit 2: ib_base_page_rev2 - XDR onwards
Bit 3: Consurtium
Bit 4: MLPN_rev0
Bit 5: MLPN_rev1
Bit 6: NLPN_rev2 */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t negotiation_mask;
	/* Description - Remote device type: 
0 - Unknown (3rd party , Force , legacy MLPN)  
1 - CX4
2 - CX4_LX
3 - CX5
4 - CX5_LX
5 - CX6
6 - CX6_LX
7 - CX6_DX
8 - CX7
9 - Bluefield-2
10 - CX8
11 - Bluefield-3
12-99 Reserved

100 - SwitchIB
101 - Spectrum 
102 - SwitchIB-2
103 - Quantum
104 - Spectrum-2
105 - Spectrum-3
106 - Quantum-2
107 - Spectrum-4
108 -Quantum-3
109-199 -Reserved

200 - GBxxx (GB100/102/200)
201-255 - reserved */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t remote_device_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Link partner IB TS revision 

 */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t lp_ib_revision;
	/* Description - IB TS revision 
 */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t ib_revision;
	/* Description - Negotiation attempt counter */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t num_of_negotiation_attempts;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Phy manager disable bit mask: 
Bit 0 - Module not present (module absence/cage power off)
Bit 1 - PAOS command
Bit 2 - MAD IB PortInfo down command
Bit 3 - Long range cable (Non Mellanox) 
Bit 4 - Verification command
Bit 5 - ekey command
Bit 6 - High power - cable require higher power than allowed.
Bit 7 - Unknown Identifier (Module)
Bit 8 - PAOS up once 
Bit 9 - Stamping failure
Bit 10 - Calibration not done
Bit 11 - Module Locking
Bit 13 - Power budget exceeded
Bit 14 - Interrupt Event / Module Temp
Bit 15 - TEC flow / module bring up issue */
	/* 0x8.0 - 0x8.23 */
	/* access: RO */
	u_int32_t phy_manager_disable_mask;
	/* Description - IBP HW FSM Reflected State:
0x10: sleeping_delay
0x11: sleeping_quiet
0x20: polling_active
0x21: polling_quiet
0x30: disable
0x40: config_debounce
0x41: config_receiver
0x42: config_wait_remote
0x43: config_tx_reverse_lanes
0x44: config_enhanced    
0x45: config_test
0x46: confg_wait_remote_test
0x47: config_wait_cfg_enhanced
0x48: config_idle
0x50: linkup
0x51: Linkup_Tx_Idle
0x52: Linkup_Tx_Empty
0x60: recover_retrain
0x61: recover_wait_remote
0x62: recover_idle
0x70: test
- Force Modes
0x80: Force_send_ts1 - command may be given only on disable state
0x90: Force_send_ts2
0xA0: Force_Sent_Idle
0xB0: Force_send_ts_Mlnx
0xC0: Force_send_ts3
0xD0: Force_LinkUp
- L1
0xE0: Go_To_Quiet
0xE1: Retimer_Align
0xE2: Quiet_Entry
0xE3: Quiet
0xE4: Wake
0xE5: Wake_Tx_Sleep0
0xE6: Send_Announce
0xE7: Tx_HS
0xE8: Wait_For_Cdr_Lock */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t hw_link_phy_state;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - PCS HW state:
Bits 0-7: Block lock
Bits 8-15: AM lock
Bits 16-23: FEC lock
Bits 24: Align_status
Bits 25: Hi_BER
Bits 26: Hi_SER */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t pcs_phy_state;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - IB ports : 
Link partner advertised speeds (first TS3)
See ib_link_speed_enabled encoding.

Ethernet ports:
Link partner advertised Ethernet protocols active state: see PTYS.lp_advertise */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t lp_proto_enabled;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Reserved when negotiation wasn't performed according to port_notifications.Link partner advertised capabilities value.
Advertised link partner FEC mode request */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t lp_fec_mode_request;
	/* Description - Reserved when negotiation wasn't performed according to port_notifications.Link partner advertised capabilities value.

Advertised link partner FEC mode support
Bit 0 - No FEC
Bit 1 - Firecode FEC
Bit 2 - Standard RS-FEC - RS(528,514)
Bit 3 - Standard LL RS-FEC - RS(271,257)
Bit 4 - Mellanox Strong RS-FEC - RS(277,257)
Bit 5 - Mellanox LL RS-FEC - RS(163,155)
Bit 6 - Reserved
Bit 7 - Standard RS-FEC (544,514)
Bit 8 - Zero Latency FEC
Bit 12 - RS-FEC (544,514) + PLR
Bit 13 - LL-FEC (271,257) + PLR

 */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t lp_fec_mode_support;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Bit 0 - heartbeat_ack_received
Bit 1 - heartbeat_send_received
Bit 2 - heartbeat_err
Bit 3 - tx_width_reduction_done_1x
Bit 4 - tx_width_reduction_done_full
Bit 5 - rx_width_reduction_done_1x
Bit 6 - rx_width_reduction_done_full
Bit 7 - width_reduction_timeout
Bit 8 - ibl_link_retrain
Bit 9 - rx_comskp_timeout
Bit 10 - fifo_full_err
Bit 11 - ts_at_linkup
Bit 12 - minor_threshold_reached
Bit 13 - link_fail
Bit 14 - rx_eb_full_r
Bit 15 - rx_8_10_lane_err
Bit 16 - llr_link_retrain_set
Bit 17 - fc_timeout
Bit 18 - phy_error
Bit 19 - lli_err
Bit 20 - excessive_buffer_err
Bit 21 - remote_init
Bit 22 - plr_retry_expired
Bit 23 - port_didnt_exit_plr_sync
Bit 24 - eq_failed
Bits 31-24 - Reserved */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t ib_last_link_down_reason;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Bit 0 - block_lock_failed
Bit 1 - skip_detected
Bit 2 - fec_sync_failed
Bit 3 - fec_block_sync
Bit 4 - fec_block_sync_lost */
	/* 0x1c.24 - 0x20.23 */
	/* access: RO */
	u_int8_t eth_last_link_down_lane[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Bit 0 - Speed degradation database Valid
Bit 1 - Speed degradation Serdes Rx database valid
BIts 3-2 - reserved
Bit 4 - rx_reversal
Bit 5 - tx_reversal
Bit 7-6 - reserved
Bits 11:8 - failed_qdr/fdr10 - bit per lane.
Bits 15:12 - failed_fdr - bit per lane.
Bits 19:16- failed_edr - bit per lane.
Bits 24:20 - peer_failed_test
Bits 26-25 - reserved
Bit 27 - first_test_speed */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t speed_deg_db;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Valid only when port_notifications.Speed degradation is asserted 
 */
	/* 0x28.0 - 0x28.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane0;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Valid only when port_notifications.Speed degradation is asserted 
 */
	/* 0x2c.0 - 0x2c.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane1;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Valid only when port_notifications.Speed degradation is asserted 
 */
	/* 0x30.0 - 0x30.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane2;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Valid only when port_notifications.Speed degradation is asserted 
 */
	/* 0x34.0 - 0x34.23 */
	/* access: RO */
	u_int32_t degrade_grade_lane3;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x38.0 - 0x38.4 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane7;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x38.8 - 0x38.12 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane6;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x38.16 - 0x38.20 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane5;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x38.24 - 0x38.28 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane4;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x3c.0 - 0x3c.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_5;
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x3c.16 - 0x3c.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_4;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x40.0 - 0x40.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_7;
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x40.16 - 0x40.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_6;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x44.0 - 0x44.4 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane3;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x44.8 - 0x44.12 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane2;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x44.16 - 0x44.20 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane1;
	/* Description - presets tested in TX tuning flow counter or in KR Startup */
	/* 0x44.24 - 0x44.28 */
	/* access: RO */
	u_int8_t num_of_presets_tested_lane0;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Per lane KR startup state:
0: KR_FSM_INITIALIZE
1: KR_FSM_SEND_TRAINING
2: KR_FSM_TRAIN_LOCAL_TX
3: KR_FSM_TRAIN_LOCAL_RX
4: KR_FSM_TRAIN_REMOTE
5: KR_FSM_LINK_READY
6: KR_FSM_SEND_DATA
7: KR_FSM_NVLT
8: KR_ABORT
9: KR_TIMEOUT
10: KR_FSM_IN_IDLE */
	/* 0x48.24 - 0x50.23 */
	/* access: RO */
	u_int8_t kr_startup_fsm_lane[8];
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - eth_an_debug bit mask:
Bit 0 - Force link up
Bit 1 - No HCD
Bit 2 - Entered ACK_detect
Bit 3 - Entered Good
Bit 4 - Entered Good_Check
Bit 5 - Entered Extra_tune
Bit 6 - Entered Fix_Reversals
Bit 7 - Entered Next_Page
Bit 8 - Entered Sub-FSM Fail
Bit 9 - Tuning timeout
Bit 10 - No markers detected (during Good check)
Bit 11 - Do KR-startup
Bits 15:18 - KR startup failure mask */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t eth_an_debug_indication;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - FW IB state machine:
HDR Gen
Bit 0 - entered IB_AN_FSM_DISABLED
Bit 1 - entered IB_AN_FSM_INITIALY
Bit 2 - entered IB_AN_FSM_RCVR_CFG
Bit 3 - entered IB_AN_FSM_CFG_TEST
Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST
Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED
Bit 6 - entered IB_AN_FSM_CFG_IDLE
Bit 7 - entered IB_AN_FSM_LINK_UP
Bit 8 - Failed from CFG_IDLE

NDR Gen:
Bit 0 - entered IB_AN_FSM_DISABLED
Bit 1 - entered IB_AN_FSM_POLLING
Bit 2 - entered IB_AN_FSM_INITIALY
Bit 3 - entered IB_AN_FSM_CFG_TEST
Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST
Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED
Bit 6 - entered IB_AN_FSM_CFG_IDLE
Bit 7 - entered IB_AN_FSM_SYNC_CHECK
Bit 8 - entered IB_AN_FSM_LINK_UP
Bit 9 - Failed from CFG_IDLE
Bit 10 - peer requested KR
Bit 11 - speed degradation needed - "best_grade" didn"t reach threshold

 */
	/* 0x54.0 - 0x54.15 */
	/* access: RO */
	u_int16_t ib_phy_fsm_state_trace;
	/* Description -  */
	/* 0x54.16 - 0x54.20 */
	/* access: RO */
	u_int8_t rounds_waited_for_peer_to_end_test;
	/* Description - counts ETH Watchdog was performed (and closed the IB fsm). */
	/* 0x54.21 - 0x54.22 */
	/* access: RO */
	u_int8_t eth_an_watchdog_cnt;
	/* Description - count falls from Cfg_idle (before linkup) due cdr not lock */
	/* 0x54.23 - 0x54.25 */
	/* access: RO */
	u_int8_t fall_from_cfg_idle_cdr_cnt;
	/* Description - count falls from Cfg_idle (before linkup) due amps lock on PLU */
	/* 0x54.26 - 0x54.28 */
	/* access: RO */
	u_int8_t fall_from_cfg_idle_cnt;
	/* Description - count the cdr not locked after EQ */
	/* 0x54.29 - 0x54.31 */
	/* access: RO */
	u_int8_t cdr_not_locked_cnt;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x58.0 - 0x58.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_1;
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x58.16 - 0x58.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_0;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x5c.0 - 0x5c.15 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_3;
	/* Description - kr_stratup_debug_indication_<i> bit mask:
Bit 0 - Local_frame_lock
Bit 1 - Remote_frame_lock
Bit 2 - Local_Frame_lock_timer_expired
Bit 3 - Remote_Frame_lock_timer_expired 
Bit 4 - Local_receiver_ready
Bit 5 - Remote_receiver_ready
Bit 6 - max_wait_timer_expired 
Bit 7 - Wait_timer_done
Bit 8 - Hold_off_timer_expired
Bit 9 - link_fail_inhibit_timer _expired */
	/* 0x5c.16 - 0x5c.31 */
	/* access: RO */
	u_int16_t kr_startup_debug_indications_2;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Stages mask per lane:
Bit 0 - Single preset stage
Bit 1 - multiple preset stage
Bit 2 - LMS */
	/* 0x60.28 - 0x64.27 */
	/* access: RO */
	u_int8_t tx_tuning_stages_lane[8];
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - PLU power up status per lane */
	/* 0x64.0 - 0x64.7 */
	/* access: RO */
	u_int8_t plu_tx_pwrup;
	/* Description - PLU power up status per lane */
	/* 0x64.8 - 0x64.15 */
	/* access: RO */
	u_int8_t plu_rx_pwrup;
	/* Description - Configured PLU polarity per lane */
	/* 0x64.16 - 0x64.23 */
	/* access: RO */
	u_int8_t plu_tx_polarity;
	/* Description - Configured PLU polarity per lane */
	/* 0x64.24 - 0x64.31 */
	/* access: RO */
	u_int8_t plu_rx_polarity;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x68.3 */
	/* access: RO */
	u_int8_t irisc_status;
	/* Description - 0 - Default as defined in IB Spec.
1 - Override default with 64msec timeout for all speeds.
2 - Reserved
3 - Reserved */
	/* 0x68.4 - 0x68.5 */
	/* access: RO */
	u_int8_t ib_cfg_delay_timeout;
	/* Description - when set, signal_detected has valid value. */
	/* 0x68.6 - 0x68.6 */
	/* access: RO */
	u_int8_t sd_valid;
	/* Description - PLU configured speed:
 */
	/* 0x68.8 - 0x68.11 */
	/* access: RO */
	u_int8_t plu_tx_speed;
	/* Description - PLU configured speed:
 */
	/* 0x68.12 - 0x68.15 */
	/* access: RO */
	u_int8_t plu_rx_speed;
	/* Description -  */
	/* 0x68.16 - 0x68.23 */
	/* access: RO */
	u_int8_t plr_outstanding_cells;
	/* Description - valid only when sd_valid is set
Bitmask per lane.
When set signal has been detected on the lane */
	/* 0x68.24 - 0x68.31 */
	/* access: RO */
	u_int8_t signal_detected;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - Bit 0 - com_codes_is_zero 
Bit 1- rx_cdr_check_force_mode 
Bit 2- com_code_complaince 
Bit 3- eth_56g_stamped
Bit 4- non_mlx_qsfp_tranciver
Bit 5- non_mlx_sfp_tranciver
Bit 6-ib_comp_codes
Bit 7-edr_comp
Bit 8-fdr_comp */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t stamping_reason;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - Number of times that fast tuning (50ms) for KR lock failed to achieve frame lock. */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t kr_frame_lock_tuning_failure_events_count;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Number of times that full tuning (0.5sec/3sec) for KR full tuning flow failed to achieve desire SI performance */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t kr_full_tuning_failure_count;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - Bit 0: phy_test_mode
Bit 1: force_mode_en */
	/* 0x78.0 - 0x78.15 */
	/* access: RO */
	u_int16_t pm_debug_indication;
	/* Description - Bit 0: cause_plr_tx_max_outstanding_cells */
	/* 0x78.16 - 0x78.31 */
	/* access: RO */
	u_int16_t ib_debug_indication;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - Phy Manager catastrophic enum */
	/* 0x7c.0 - 0x7c.6 */
	/* access: RO */
	u_int8_t pm_catastrophic_enum;
	/* Description - When set, indicates the pm_catastrophic_enum is valid */
	/* 0x7c.7 - 0x7c.7 */
	/* access: RO */
	u_int8_t pm_cat_val;
	/* Description - Auto-neg catastrophic enum */
	/* 0x7c.8 - 0x7c.14 */
	/* access: RO */
	u_int8_t an_catastrophic_enum;
	/* Description - When set, indicates the an_catastrophic_enum is valid */
	/* 0x7c.15 - 0x7c.15 */
	/* access: RO */
	u_int8_t an_cat_val;
	/* Description - HST catastrophic enum */
	/* 0x7c.16 - 0x7c.22 */
	/* access: RO */
	u_int8_t hst_catastrophic_enum;
	/* Description - When set, indicates the hst_catastrophic_enum is valid */
	/* 0x7c.23 - 0x7c.23 */
	/* access: RO */
	u_int8_t hst_cat_val;
	/* Description - Parallel Detect catastrophic enum */
	/* 0x7c.24 - 0x7c.30 */
	/* access: RO */
	u_int8_t pd_catastrophic_enum;
	/* Description - When set, indicates the pd_catastrophic_enum is valid */
	/* 0x7c.31 - 0x7c.31 */
	/* access: RO */
	u_int8_t pd_cat_val;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Bit 0: speed_change_high_speed_module
Bit 1: False_positive_signal_detect
Bit 2: Nv2nv_force
Bit 3: bad_kr_mask 
Bit 4: kr_mlx_peer
Bit 5: entered_signal_detect
Bit 6: entered_rate_config
Bit 7: entered_activate_sunfsm
Bit 8: entered_done
Bit 9: entered_subfsm_fail */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t pd_debug_indication;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - Parallel detect cycles counter */
	/* 0x84.0 - 0x84.5 */
	/* access: RO */
	u_int8_t pd_count;
	/* Description - False Positive signal detect count */
	/* 0x84.8 - 0x84.13 */
	/* access: RO */
	u_int8_t fp_signal_detect_count;
	/* Description - 0: speed
1: FEC
2: precoding
3: Gray coding */
	/* 0x84.16 - 0x84.17 */
	/* access: RO */
	u_int8_t hst_mismatch_reason;
	/* Description - FSM 2 to call sub fsm of PSI that caused collision
see fsm_mask in debug page for FSM numbering */
	/* 0x84.22 - 0x84.26 */
	/* access: RO */
	u_int8_t psi_collision2;
	/* Description - FSM 1 to call sub fsm of PSI that caused collision
see fsm_mask in debug page for FSM numbering */
	/* 0x84.27 - 0x84.31 */
	/* access: RO */
	u_int8_t psi_collision1;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Bit 0: nonce_match_fail
Bit 1: timeout - rst cause idle in npln
Bit 2: hs_neg
Bit 3: dme_neg */
	/* 0x88.0 - 0x88.7 */
	/* access: RO */
	u_int8_t nlpn_debug_ind_mask;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - phy 2 module requested speed, aka speed_apsel_value
bitmask according to PTYS.ext_ethernet_protocl for ETH speeds
or ib_ext_protocols for IB speeds */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t phy2mod_speed_req;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - Bitmask per lane for phy2mod deactivate request status.
0 - allow DP activation
1 - Deactivate module DP */
	/* 0x90.0 - 0x90.7 */
	/* access: RO */
	u_int8_t phy2mod_deactivate_lanes;
	/* Description - Bitmask per lane for phy2mod request status.
0 - ack
1 - nack */
	/* 0x90.8 - 0x90.15 */
	/* access: RO */
	u_int8_t phy2mod_ack_lanes;
	/* Description - indicates module has one pll for all lanes of the module. */
	/* 0x90.29 - 0x90.29 */
	/* access: RO */
	u_int8_t one_pll_mod;
	/* Description - no_dme_module indicates module doesn't support low speed signaling such as 312.5 MB/s for DME ETH AN signaling or SDR (2.5 GB/s) for IB low speed AN. */
	/* 0x90.30 - 0x90.30 */
	/* access: RO */
	u_int8_t no_dme_mod;
	/* Description - eeprom present indication */
	/* 0x90.31 - 0x90.31 */
	/* access: RO */
	u_int8_t eeprom_prsnt;
/*---------------- DWORD[37] (Offset 0x94) ----------------*/
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.0 - 0x94.1 */
	/* access: RO */
	u_int8_t rx_bypass_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.2 - 0x94.3 */
	/* access: RO */
	u_int8_t rx_bypass_mux_plt1;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.4 - 0x94.5 */
	/* access: RO */
	u_int8_t tx_bypass_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.6 - 0x94.7 */
	/* access: RO */
	u_int8_t tx_bypass_mux_plt1;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.8 - 0x94.9 */
	/* access: RO */
	u_int8_t reconciliation_mux_plt0;
	/* Description - 1 bit per each split; 1-enabled; 0-Bypass (No MacSec) */
	/* 0x94.10 - 0x94.11 */
	/* access: RO */
	u_int8_t reconciliation_mux_plt1;
	/* Description - MacSec enabled plt0 split 0 */
	/* 0x94.12 - 0x94.12 */
	/* access: RO */
	u_int8_t macsec_en_plt0_s0;
	/* Description - MacSec enabled plt0 split 1 */
	/* 0x94.13 - 0x94.13 */
	/* access: RO */
	u_int8_t macsec_en_plt0_s1;
	/* Description - MacSec enabled plt1 split 0 */
	/* 0x94.14 - 0x94.14 */
	/* access: RO */
	u_int8_t macsec_en_plt1_s0;
	/* Description - MacSec enabled plt1 split 1 */
	/* 0x94.15 - 0x94.15 */
	/* access: RO */
	u_int8_t macsec_en_plt1_s1;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.16 - 0x94.19 */
	/* access: RO */
	u_int8_t cnt_rx_frame_received_ok_s0;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.20 - 0x94.23 */
	/* access: RO */
	u_int8_t cnt_rx_frame_received_ok_s1;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.24 - 0x94.27 */
	/* access: RO */
	u_int8_t port_xmit_pkts_inc_s0;
	/* Description - MacSec Engine Wrapper, debug counter */
	/* 0x94.28 - 0x94.31 */
	/* access: RO */
	u_int8_t port_xmit_pkts_inc_s1;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - rtt threshold in 1 ns units for NDR speeds
 */
	/* 0x98.0 - 0x98.15 */
	/* access: RO */
	u_int16_t plr_rtt_ndr_threshold;
	/* Description - rtt threshold in 1 ns units for HDR speeds */
	/* 0x98.16 - 0x98.31 */
	/* access: RO */
	u_int16_t plr_rtt_hdr_threshold;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - rtt threshold in 1 ns units for XDR speeds
 */
	/* 0x9c.16 - 0x9c.31 */
	/* access: RO */
	u_int16_t plr_rtt_xdr_threshold;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_pddr_troubleshooting_page_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Monitor_opcodes */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t group_opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Status opcode described in:
Table 707, "PDDR - Monitor opcodes layout," on page 747 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext status_opcode;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ASCII code message
All Messages are terminated by a Null character '\0' */
	/* 0xc.0 - 0xf4.31 */
	/* access: RO */
	u_int32_t status_message[59];
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_phys_layer_cntrs_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The time passed since the last counters clear event in msec. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The time passed since the last counters clear event in msec. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Perf.PortCounters(SymbolErrorCounter) = Perf.PortCounters(UnknownSymbol) */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t symbol_errors_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Perf.PortCounters(SymbolErrorCounter) = Perf.PortCounters(UnknownSymbol) */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t symbol_errors_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(SynchHeaderErrorCounter) */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t sync_headers_errors_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(SynchHeaderErrorCounter) */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t sync_headers_errors_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane0Counter) / BIP error counter, lane 0
In PRBS test mode, indicates the number of PRBS errors
on lane 0 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane0_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane0Counter) / BIP error counter, lane 0
In PRBS test mode, indicates the number of PRBS errors
on lane 0 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane0_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane1Counter) / BIP error counter, lane 1
In PRBS test mode, indicates the number of PRBS errors
on lane 1 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane1_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane1Counter) / BIP error counter, lane 1
In PRBS test mode, indicates the number of PRBS errors
on lane 1 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane1_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane2Counter) / BIP error counter, lane 2
In PRBS test mode, indicates the number of PRBS errors
on lane 2 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane2_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane2Counter) / BIP error counter, lane 2
In PRBS test mode, indicates the number of PRBS errors
on lane 2 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane2_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane3Counter) / BIP error counter, lane 3
In PRBS test mode, indicates the number of PRBS errors
on lane 3 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane3_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane3Counter) / BIP error counter, lane 3
In PRBS test mode, indicates the number of PRBS errors
on lane 3 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t edpl_bip_errors_lane3_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0) */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane0_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0) */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane0_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1) */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane1_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1) */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane1_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2) */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane2_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2) */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane2_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3) */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane3_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3) */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t fc_fec_corrected_blocks_lane3_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0) */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane0_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0) */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane0_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1) */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane1_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1) */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane1_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2) */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane2_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2) */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane2_low;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3) */
	/* 0x70.0 - 0x70.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane3_high;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3) */
	/* 0x74.0 - 0x74.31 */
	/* access: RO */
	u_int32_t fc_fec_uncorrectable_blocks_lane3_low;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrecableBlockCounter) */
	/* 0x78.0 - 0x78.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_blocks_high;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FECCorrecableBlockCounter) */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_blocks_low;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FEUncorrecableBlockCounter) */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t rs_fec_uncorrectable_blocks_high;
/*---------------- DWORD[33] (Offset 0x84) ----------------*/
	/* Description - Perf.PortExtendedSpeedsCounters(FEUncorrecableBlockCounter) */
	/* 0x84.0 - 0x84.31 */
	/* access: RO */
	u_int32_t rs_fec_uncorrectable_blocks_low;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - The number of RS-FEC blocks received that had no errors.
Note: Total rs_fec blocks received = rs_fec_corrected_blocks + rs_fec_uncorrectable_blocks + rs_fec_no_errors_blocks */
	/* 0x88.0 - 0x88.31 */
	/* access: RO */
	u_int32_t rs_fec_no_errors_blocks_high;
/*---------------- DWORD[35] (Offset 0x8c) ----------------*/
	/* Description - The number of RS-FEC blocks received that had no errors.
Note: Total rs_fec blocks received = rs_fec_corrected_blocks + rs_fec_uncorrectable_blocks + rs_fec_no_errors_blocks */
	/* 0x8c.0 - 0x8c.31 */
	/* access: RO */
	u_int32_t rs_fec_no_errors_blocks_low;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(PortFECCorrectedSymbolCounter) */
	/* 0x98.0 - 0x98.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_total_high;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(PortFECCorrectedSymbolCounter) */
	/* 0x9c.0 - 0x9c.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_total_low;
/*---------------- DWORD[40] (Offset 0xa0) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane0) */
	/* 0xa0.0 - 0xa0.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane0_high;
/*---------------- DWORD[41] (Offset 0xa4) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane0) */
	/* 0xa4.0 - 0xa4.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane0_low;
/*---------------- DWORD[42] (Offset 0xa8) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane1) */
	/* 0xa8.0 - 0xa8.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane1_high;
/*---------------- DWORD[43] (Offset 0xac) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane1) */
	/* 0xac.0 - 0xac.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane1_low;
/*---------------- DWORD[44] (Offset 0xb0) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane2) */
	/* 0xb0.0 - 0xb0.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane2_high;
/*---------------- DWORD[45] (Offset 0xb4) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane2) */
	/* 0xb4.0 - 0xb4.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane2_low;
/*---------------- DWORD[46] (Offset 0xb8) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane3) */
	/* 0xb8.0 - 0xb8.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane3_high;
/*---------------- DWORD[47] (Offset 0xbc) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane3) */
	/* 0xbc.0 - 0xbc.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane3_low;
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description - Perf.PortCounters(LinkDownedCounter) */
	/* 0xc0.0 - 0xc0.31 */
	/* access: RO */
	u_int32_t link_down_events;
/*---------------- DWORD[49] (Offset 0xc4) ----------------*/
	/* Description - Perf.PortCounters(LinkErrorRecoveryCounter)
Note: This counter is valid only for IB. */
	/* 0xc4.0 - 0xc4.31 */
	/* access: RO */
	u_int32_t successful_recovery_events;
/*---------------- DWORD[50] (Offset 0xc8) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4) */
	/* 0xc8.0 - 0xc8.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane4_high;
/*---------------- DWORD[51] (Offset 0xcc) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4) */
	/* 0xcc.0 - 0xcc.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane4_low;
/*---------------- DWORD[52] (Offset 0xd0) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5) */
	/* 0xd0.0 - 0xd0.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane5_high;
/*---------------- DWORD[53] (Offset 0xd4) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5) */
	/* 0xd4.0 - 0xd4.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane5_low;
/*---------------- DWORD[54] (Offset 0xd8) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6) */
	/* 0xd8.0 - 0xd8.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane6_high;
/*---------------- DWORD[55] (Offset 0xdc) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6) */
	/* 0xdc.0 - 0xdc.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane6_low;
/*---------------- DWORD[56] (Offset 0xe0) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7) */
	/* 0xe0.0 - 0xe0.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane7_high;
/*---------------- DWORD[57] (Offset 0xe4) ----------------*/
	/* Description - Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7) */
	/* 0xe4.0 - 0xe4.31 */
	/* access: RO */
	u_int32_t rs_fec_corrected_symbols_lane7_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_phys_layer_stat_cntrs_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The time passed since the last counters clear event in msec.
 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The time passed since the last counters clear event in msec.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - This counter provides information on the total amount of traffic (bits) received.
 */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t phy_received_bits_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - This counter provides information on the total amount of traffic (bits) received.
 */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t phy_received_bits_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t phy_symbol_errors_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t phy_symbol_errors_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Corrected bits by FEC engine. 
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t phy_corrected_bits_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Corrected bits by FEC engine. 
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t phy_corrected_bits_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 0. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 0


 */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane0_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 0. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 0


 */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane0_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 1. 
When FEC is enabled this induction corresponds to corrected errors
In PRBS test mode, indicates the number of PRBS errors
on lane 1

 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane1_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 1. 
When FEC is enabled this induction corresponds to corrected errors
In PRBS test mode, indicates the number of PRBS errors
on lane 1

 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane1_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 2. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 2



 */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane2_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 2. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 2



 */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane2_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 3. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 3
 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane3_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 3. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 3
 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane3_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 4. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 4
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane4_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 4. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 4
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane4_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 5. 
When FEC is enabled this induction corresponds to corrected errors
In PRBS test mode, indicates the number of PRBS errors
on lane 5
 */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane5_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 5. 
When FEC is enabled this induction corresponds to corrected errors
In PRBS test mode, indicates the number of PRBS errors
on lane 5
 */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane5_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 6. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 6 */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane6_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 6. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 6 */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane6_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 7. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 7 */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane7_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - This counter provides information on error bits that were identified on lane 7. 
When FEC is enabled this induction corresponds to corrected errors.
In PRBS test mode, indicates the number of PRBS errors
on lane 7 */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t phy_raw_errors_lane7_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Raw_BER = raw_ber_coef  *10^(-raw_ber_magnitude)
 */
	/* 0x60.0 - 0x60.3 */
	/* access: RO */
	u_int8_t raw_ber_coef;
	/* Description - Raw_BER = raw_ber_coef  *10^(-raw_ber_magnitude)
 */
	/* 0x60.8 - 0x60.15 */
	/* access: RO */
	u_int8_t raw_ber_magnitude;
	/* Description - Valid for links with RS FEC histograms only.
First histogram bin with value of 0 while all higher bins are only with 0 value as well.
0 - No histogram active / N/A value */
	/* 0x60.16 - 0x60.25 */
	/* access: RO */
	u_int16_t fc_zero_hist;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - effective_fec_BER = effective_fec_ber_coef *10^(-effective_fec_ber_magnitude)
 */
	/* 0x64.0 - 0x64.3 */
	/* access: RO */
	u_int8_t effective_ber_coef;
	/* Description - effective_fec_BER = effective_fec_ber_coef *10^(-effective_fec_ber_magnitude)
 */
	/* 0x64.8 - 0x64.15 */
	/* access: RO */
	u_int8_t effective_ber_magnitude;
	/* Description - estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)
 */
	/* 0x64.16 - 0x64.19 */
	/* access: RO */
	u_int8_t estimated_effective_ber_coef;
	/* Description - estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)
 */
	/* 0x64.20 - 0x64.23 */
	/* access: RO */
	u_int8_t estimated_effective_ber_coef_float;
	/* Description - estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)
 */
	/* 0x64.24 - 0x64.31 */
	/* access: RO */
	u_int8_t estimated_effective_ber_magnitude;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude) */
	/* 0x68.0 - 0x68.3 */
	/* access: RO */
	u_int8_t symbol_ber_coef;
	/* Description - Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude) */
	/* 0x68.8 - 0x68.15 */
	/* access: RO */
	u_int8_t symbol_ber_magnitude;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.
 */
	/* 0x7c.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t phy_effective_errors_high;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.
 */
	/* 0x80.0 - 0x80.31 */
	/* access: RO */
	u_int32_t phy_effective_errors_low;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Host Electrical compliance code per CMIS byte 86 based on SFF-8024 table 4-5
0 - unspecified
1- 1000BASE - CX
2 - XAUI
3 - XFI
4 - SFI
5 - 25GAUI C2M
6 - XLAUI C2M
7 - XLPPI
8 - LAUI-2 C2M
9 - 50GAUI-2 C2M
10 - 50GAUI-1 C2M
11 - CAUI-4 C2M
13 - 100GAUI-2 C2M
15 - 200GAUI-4 C2M
17 - 400GAUI-8 C2M
20 - 25GBASE-CR CA-L
21 - 25GBASE-CR CA-S
22 - 25GBASE-CR CA-N
23 - 40GBASE-CR4
24 - 50GBASE-CR
26 - 100GBASE-CR4
27 - 100GBASE-CR2
28 - 200GBASE-CR4
29 - 400GBASE-CR8

65 - CAUI-4 C2M no FEC
66 - CAUI-4 C2M RS FEC
67 - 50GBASE-CR2 RS FEC
68 - 50GBASE-CR2 FC FEC
69 - 50GBASE-CR2 no FEC */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t host_electrical_compliance;
	/* Description - bits 7-0 as per byte 210 in CMIS, Near-End implementation
Bit 0 - Channel 1 implementation 
Bit 1 - Channel 2 implementation
Bit 2 - Channel 3 implementation
Bit 3 - Channel 4 implementation
Bit 4- Channel 5 implementation 
Bit 5- Channel 6 implementation
Bit 6- Channel 7 implementation
Bit 7- Channel 8 implementation

for each channel:
0 - Channel implemented 
1 - Channel not - implemented

bit 12-8 as per byte 211 4-0 in CMIS, Far-End implementation
 */
	/* 0x0.8 - 0x0.20 */
	/* access: RW */
	u_int16_t cable_breakout;
	/* Description - Byte 85 in CMIS. Media type encoding override
0: undefined
1: Optical_MMF
2: Optical_SMF
3: Passive_copper
4: Active_cables
5: BASE_T */
	/* 0x0.21 - 0x0.24 */
	/* access: RW */
	u_int8_t media_type_encoding;
	/* Description - Module transition to high power maximum duration. coded according to table 8-29 of CMIS. */
	/* 0x0.28 - 0x0.31 */
	/* access: RW */
	u_int8_t mod_pwrup_maxduration;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module media interface compliance for CMIS, per byte 87.
Values taken according to module_media_type from SFF-8024:

If MMF - SFF-8024 table 4-6, MM media interface codes
If SMF - SFF-8024 table 4-7, SM media interface code

If Active cable- SFF-8024 table 4-9 Active cable assembly code:
0 -unspecified
1 - Active cable assembly with BER < 1e-12
2 - Active cable assembly with BER < 5e-5
3 - Active cable assembly with BER < 2.6e-4
4 - Active cable assembly with BER < 1e-6 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t media_compliance;
	/* Description - Module media type encoding, per byte 85 of CMIS:
0 - undefined
1 - MMF
2 - SMF
3 - passive Copper
4 - Active cables
5 - Base-T */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t module_media_type;
	/* Description - Data path turn off maximum duration. coded according to table 8-29 of CMIS 4.0. */
	/* 0x4.16 - 0x4.19 */
	/* access: RW */
	u_int8_t dp_tx_off_maxduration;
	/* Description - Data path turn on maximum duration. coded according to table 8-29 of CMIS 4.0. */
	/* 0x4.20 - 0x4.23 */
	/* access: RW */
	u_int8_t dp_tx_on_maxduration;
	/* Description - Data path init maximum duration. coded according to table 8-29 of CMIS 4.0. */
	/* 0x4.28 - 0x4.31 */
	/* access: RW */
	u_int8_t dp_init_maxduration;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - bitmask of override from CMIS protocol bytes page.
Relevant only when Bit 9 is set in eeprom_override field.
inverse polarity.
0 - override
1 - don't override

Bit 0 - cable_breakout
Bit 1 -host_electrical_compliance
Bit 2 - module_media_type
Bit 3 - media_compliance
Bit 4 - mod_pwrup_maxDuration
Bit 5 - dp_init_maxDuration
Bit 6 - dp_tx_on_maxDuration
Bit 7 - dp_tx_off_maxDuration
Bit 9 - media_type_encoding */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t cmis_override_mask;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ethernet Compliance Codes bit mask (10/40G/100G)
Override byte131 per SFF-8636:
Bit 7 - Extended Specification Compliance valid
Bit 6 - 10GBASE-LRM
Bit 5 - 10GBASE-LR
Bit 4 - 10GBASE-SR
Bit 3 - 40GBASE-CR4
Bit 2 - 40GBASE-SR4
Bit 1 - 40GBASE-LR4
Bit 0 - 40G Active Cable (XLPPI) */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t ethernet_compliance_code;
	/* Description - Override of byte113 per SFF-8636:
Bit 6-4 (Far End):
0 - Far end is unspecified
1 - Cable with single far end with 4 channels implemented, or separable module with 4-channel connector
2 - Cable with single far end with 2 channels implemented, or separable module with 2-channel connector
3 - Cable with single far end with 1 channel implemented, or separable module with 1-channel connector
4 - 4 far ends with 1 channel implemented in each (i.e. 4x1 break out)
5 - 2 far ends with 2 channels implemented in each (i.e. 2x2 break out)
6 - 2 far ends with 1 channel implemented in each (i.e. 2x1 break out)

Bit 3-0 (Near End)
Bit 0 - Channel 1 implementation 
Bit 1 - Channel 2 implementation
Bit 2 - Channel 3 implementation
Bit 3 - Channel 4 implementation

for each channel:
0 - Channel implemented 
1 - Channel not - implemented
 */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t cable_breakout;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Gigabit Ethernet Compliance Codes 
Override byte134 per SFF-8636:
Bit 3 - 1000BASE-T
Bit 2 - 1000BASE-CX
Bit 1 - 1000BASE-LX
Bit 0 - 1000BASE-SX */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t giga_ethernet_compliance_code;
	/* Description - Extended Specification Compliance Codes 
Override byte192 per SFF-8636:
0 - Unspecified
1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC
2 - 100GBASE-SR4 or 25GBASE-SR
3 - 100GBASE-LR4 or 25GBASE-LR
4 - 100GBASE-ER4 or 25GBASE-ER
5 - 100GBASE-SR10
6 - 100G CWDM4
7 - 100G PSM4 Parallel SMF
8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC
11 - 100GBASE-CR4 or 25GBASE-CR CA-L
12 - 25GBASE-CR CA-S
13 - 25GBASE-CR CA-N
16 - 40GBASE-ER4
17 - 4 x 10GBASE-SR
18 - 40G PSM4 Parallel SMF
19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)
20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)
21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)
22 - 10GBASE-T with SFI electrical interface
23 - 100G CLR4
24 - 100G AOC or 25GAUI C2M AOC. No FEC
25 - 100G ACC or 25GAUI C2M ACC. No FEC */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t ext_ethernet_compliance_code;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 10G Ethernet Compliance Codes
Override byte3 per SFF-8472:
Bit 7 - 10G Base-ER 
Bit 6 - 10G Base-LRM 
Bit 5 - 10G Base-LR 
Bit 4 - 10G Base-SR
 */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t tengig_ethernet_compliance_code;
	/* Description - SFP+ Cable Technology
Override byte8 per SFF-8472:
Bit 3 - Active Cable
Bit 2 - Passive Cable */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t cable_technology;
	/* Description - Override byte12 per SFF-8472
The nominal bit (signaling) rate (BR, nominal) is specified in units of 100 MBd, rounded off to the nearest 100 MBd.
A value of FFh indicates the bit rate is greater than 25.0Gb/s */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t bit_rate;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Ethernet Compliance Codes 
Override byte6 per SFF-8472:
Bit 7 - BASE-PX 
Bit 6 - BASE-BX10 
Bit 5 - 100BASE-FX 
Bit 4 - 100BASE-LX/LX10 
Bit 3 - 1000BASE-T 
Bit 2 - 1000BASE-CX 
Bit 1 - 1000BASE-LX 
Bit 0 - 1000BASE-SX
 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t ethernet_compliance_code;
	/* Description - Extended Specification Compliance Codes (25GE) 
Override byte36 per SFF-8472:
0 - Unspecified
1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC
2 - 100GBASE-SR4 or 25GBASE-SR
3 - 100GBASE-LR4 or 25GBASE-LR
4 - 100GBASE-ER4 or 25GBASE-ER
5 - 100GBASE-SR10
6 - 100G CWDM4
7 - 100G PSM4 Parallel SMF
8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC
11 - 100GBASE-CR4 or 25GBASE-CR CA-L
12 - 25GBASE-CR CA-S
13 - 25GBASE-CR CA-N
16 - 40GBASE-ER4
17 - 4 x 10GBASE-SR
18 - 40G PSM4 Parallel SMF
19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)
20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)
21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)
22 - 10GBASE-T with SFI electrical interface
23 - 100G CLR4
24 - 100G AOC or 25GAUI C2M AOC. No FEC
25 - 100G ACC or 25GAUI C2M ACC. No FEC */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t ext_ethernet_compliance_code;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_ppcnt_infiniband_general_counter_ext {
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The total number of packets that were dropped since it contained errors. Reasons for this include:
1. dropped due to MPR mismatch.
Supported only when indicated by PCAM.
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t rq_general_error_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The total number of packets that were dropped since it contained errors. Reasons for this include:
1. dropped due to MPR mismatch.
Supported only when indicated by PCAM.
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t rq_general_error_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The time passed since the last counters clear event in msec. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The time passed since the last counters clear event in msec. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t time_since_last_clear_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t port_unicast_xmit_pkts_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t port_unicast_xmit_pkts_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t port_unicast_rcv_pkts_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t port_unicast_rcv_pkts_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t sync_header_error_counter_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t sync_header_error_counter_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t port_local_physical_errors_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t port_local_physical_errors_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t port_malformed_packet_errors_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t port_malformed_packet_errors_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t port_buffer_overrun_errors_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t port_buffer_overrun_errors_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t port_dlid_mapping_errors_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t port_dlid_mapping_errors_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t port_vl_mapping_errors_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t port_vl_mapping_errors_low;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x48.0 - 0x48.31 */
	/* access: RO */
	u_int32_t port_looping_errors_high;
/*---------------- DWORD[19] (Offset 0x4c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x4c.0 - 0x4c.31 */
	/* access: RO */
	u_int32_t port_looping_errors_low;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x50.0 - 0x50.31 */
	/* access: RO */
	u_int32_t port_inactive_discards_high;
/*---------------- DWORD[21] (Offset 0x54) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x54.0 - 0x54.31 */
	/* access: RO */
	u_int32_t port_inactive_discards_low;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x58.0 - 0x58.31 */
	/* access: RO */
	u_int32_t port_neighbor_mtu_discards_high;
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - For counter description please refer to the InfiniBand  Specification */
	/* 0x5c.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t port_neighbor_mtu_discards_low;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Total number of packets received on the port with ICRC error. */
	/* 0x60.0 - 0x60.31 */
	/* access: RO */
	u_int32_t port_llu_rx_icrc_error_high;
/*---------------- DWORD[25] (Offset 0x64) ----------------*/
	/* Description - Total number of packets received on the port with ICRC error. */
	/* 0x64.0 - 0x64.31 */
	/* access: RO */
	u_int32_t port_llu_rx_icrc_error_low;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Total number of packets with parity error detected on the switch. */
	/* 0x68.0 - 0x68.31 */
	/* access: RO */
	u_int32_t port_tx_parity_error_high;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description - Total number of packets with parity error detected on the switch. */
	/* 0x6c.0 - 0x6c.31 */
	/* access: RO */
	u_int32_t port_tx_parity_error_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_ppcnt_plr_counters_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of received PLR codewords

 */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t plr_rcv_codes_high;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of received PLR codewords

 */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t plr_rcv_codes_low;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The total number of rejected codewords received */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t plr_rcv_code_err_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The total number of rejected codewords received */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t plr_rcv_code_err_low;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The number of uncorrectable codewords received
 */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t plr_rcv_uncorrectable_code_high;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The number of uncorrectable codewords received
 */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t plr_rcv_uncorrectable_code_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Number of transmitted PLR codewords */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t plr_xmit_codes_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Number of transmitted PLR codewords */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t plr_xmit_codes_low;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The total number of codewords retransmitted. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_codes_high;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - The total number of codewords retransmitted. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_codes_low;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - The total number of retransmitted event. 

 */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_events_high;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The total number of retransmitted event. 

 */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_events_low;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - The number of sync events */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t plr_sync_events_high;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - The number of sync events */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	u_int32_t plr_sync_events_low;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Recieved bandwidth loss due to codes retransmission. calculated in resolution of 
(plr_rcv_code_err / plr_rcv_codes) * 10^10

BW Loss % = (plr_codes_loss / 10^10 ) *100 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t plr_codes_loss_high;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Recieved bandwidth loss due to codes retransmission. calculated in resolution of 
(plr_rcv_code_err / plr_rcv_codes) * 10^10

BW Loss % = (plr_codes_loss / 10^10 ) *100 */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RO */
	u_int32_t plr_codes_loss_low;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - The maximum number of retransmitted events in t sec window
 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_events_within_t_sec_max_high;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - The maximum number of retransmitted events in t sec window
 */
	/* 0x44.0 - 0x44.31 */
	/* access: RO */
	u_int32_t plr_xmit_retry_events_within_t_sec_max_low;
};

/* Description -   */
/* Size in bytes - 248 */
struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Value of RS-hist
In order to know bin errors distribution use PPHCR reg. */
	/* 0x0.0 - 0xa4.31 */
	/* access: RO */
	u_int64_t hist[21];
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_gpu_pter_phy_page_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Error Type to generate
0 - No Error
---- Physical Errors ----
1 - Raw BER
2 - Effective BER
16 - PCS link fault */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t error_type_admin;
	/* Description - Error injection capabilities 
Bit 0 - Raw BER
Bit 1 - Effective BER

Bit 4 - PCS link fault */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t error_type_cap;
	/* Description - Error injection opertional status
0x0 - No error injection
0x1 - Performing error injection */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t error_type_oper;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - BER for injection.
BER = ber_mantissa * 10^(-ber_exp) */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t ber_exp;
	/* Description - BER for injection.
BER = ber_mantissa * 10^(-ber_exp) */
	/* 0x4.8 - 0x4.11 */
	/* access: RW */
	u_int8_t ber_mantissa;
	/* Description - Duration in 10 msec the port will generate errors.
Reading this field will return the time left for errors to inject in msec


0x0000 indicates no generation of errors.
When set to 0xFFFF - No decremental operation, meaning the errors will be injected continuously without stop condition. */
	/* 0x4.12 - 0x4.27 */
	/* access: RW */
	u_int16_t error_injection_time;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_gpu_pter_port_page_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Error Type to generate
0 - No Error
---- Port Errors ----
1 - Corrupt data packet ICRC
2 - Corrupt data packet VCRC
4- Corrupt credit packet LPCRC */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t error_type_admin;
	/* Description - Error injection capabilities 
Bit 0- Corrupt data packet ICRC
Bit 1- Corrupt data packet VCRC
Bit 2- Corrupt credit packet LPCRC
 */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t error_type_cap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Error Count
Number of times the port will generate the configured error.
0 indicates not to generate error.
Reading error_count will return the number of left errors to inject. When 0, all requested errors has been injected. */
	/* 0x4.12 - 0x4.16 */
	/* access: RW */
	u_int8_t error_count;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_rom_version_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Build version */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t build;
	/* Description - Minor version */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major version */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t major;
};

/* Description -   */
/* Size in bytes - 36 */
struct reg_access_gpu_slrg_16nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The lane speed on which the grade was measured:
0 - SDR / PCIe Gen 1
1 - DDR / PCIe Gen 2
2 - QDR / PCIe Gen 3
3 - FDR10 (10GE / 40GE)
4 - FDR (56GE) / PCIe Gen 4
5 - EDR (25GE / 50GE / 100GE) / PCIe Gen 5
6 - HDR (50GE / 200GE / 400GE)
7- 9 - reserved
10 - 1GE
11 - 2.5GE (XAUI)
12 - 50GE-KR4
13 - 15 - reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t grade_lane_speed;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The grade that the lane received based on a specific configuration.
 */
	/* 0x4.0 - 0x4.23 */
	/* access: RO */
	u_int32_t grade;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t grade_version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Voltage offset from eye center to the negative side of the upper eye. Only applicable for PAM4 signal. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t height_eo_neg_up;
	/* Description - Voltage offset from eye center to the positive side of the upper eye.
Only applicable for PAM4 signal. */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t height_eo_pos_up;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Voltage offset from eye center to the positive side of the middle eye. */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t height_eo_pos_mid;
	/* Description - The offset from the eye center to the negative (left) side of the upper eye. Only applicable for PAM4 signal. */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t phase_eo_neg_up;
	/* Description - The offset from the eye center to the positive (right) side of the upper eye. Only applicable for PAM4 signal. */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t phase_eo_pos_up;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The offset from the eye center to the negative (left) side of the middle eye. */
	/* 0x10.0 - 0x10.7 */
	/* access: RO */
	u_int8_t phase_eo_neg_mid;
	/* Description - The offset from the eye center to the positive (right) side of the middle eye. */
	/* 0x10.8 - 0x10.15 */
	/* access: RO */
	u_int8_t phase_eo_pos_mid;
	/* Description - Voltage offset from eye center to the negative side of the middle eye. */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t height_eo_neg_mid;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Voltage offset from eye center to the negative side of the lower eye. Only applicable for PAM4 signal. */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t height_eo_neg_low;
	/* Description - Voltage offset from eye center to the positive side of the lower eye. Only applicable for PAM4 signal. */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t height_eo_pos_low;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The offset from the eye center to the negative (left) side of the lower eye. Only applicable for PAM4 signal. */
	/* 0x18.16 - 0x18.23 */
	/* access: RO */
	u_int8_t phase_eo_neg_low;
	/* Description - The offset from the eye center to the positive (right) side of the lower eye. Only applicable for PAM4 signal. */
	/* 0x18.24 - 0x18.31 */
	/* access: RO */
	u_int8_t phase_eo_pos_low;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - upper eye grade */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t up_eye_grade;
	/* Description - middle eye grade */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t mid_eye_grade;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - lower eye grade */
	/* 0x20.0 - 0x20.15 */
	/* access: RO */
	u_int16_t dn_eye_grade;
};

/* Description -   */
/* Size in bytes - 36 */
struct reg_access_gpu_slrg_40nm_28nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The lane speed on which the grade was measured:
0 - SDR
1 - DDR
2 - QDR
3 - FDR10 (10GE / 40GE)
4 - FDR (56GE)
5 - EDR (25GE / 50GE / 100GE)
6 - 9 - reserved
10 - 1GE
11 - 2.5GE (XAUI)
12 - 50GE-KR4
13 - 15 - reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t grade_lane_speed;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.23 */
	/* access: RO */
	u_int32_t grade;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t grade_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Voltage offset from eye center to the negative side. */
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t height_eo_neg;
	/* Description - Voltage offset from eye center to the positive side. */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t height_eo_pos;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The offset from the eye center to the negative side. */
	/* 0x1c.0 - 0x1c.7 */
	/* access: RO */
	u_int8_t phase_eo_neg;
	/* Description - The offset from the eye center to the positive side. */
	/* 0x1c.16 - 0x1c.23 */
	/* access: RO */
	u_int8_t phase_eo_pos;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_gpu_slrg_5nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask for measurement activation
Bit 0 - Upper eye
Bit 1 - Middle eye
Bit 2 - Lower eye
Bit 3- Composite eye
Note: NRZ only Bit 3 is valid */
	/* 0x0.0 - 0x0.3 */
	/* access: OP */
	u_int8_t fom_measurment;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - measured EOM status after FEQ.
valid only when SLRG.status is '1' */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t initial_fom;
	/* Description - fom mode:
FOM eye mode to search
0x0: FOM_MODE_EYE_OPEN
0x1: FOM_MODE_EYEO_SNR
0x2: FOM_MODE_NORM_SNR
0x3: FOM_MODE_EYE_LVLN
0x4: FOM_MODE_EYE_LVLP
0x5: FOM_MODE_THRES_NERR
0x6: FOM_MODE_CDR_NERR
0x7: FOM_MODE_CSDET_NERR
0x8: FOM_MODE_MLSE_NERR
0x9: FOM_MODE_SFEC_NERR


 */
	/* 0x4.16 - 0x4.19 */
	/* access: RW */
	u_int8_t fom_mode;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - last measured EOM-FOM status of upper eye.
valid only if fom_measurment bit '0' is set */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t upper_eye;
	/* Description - last measured EOM-FOM status of composite eye.
valid only if fom_measurment bit '3' is set */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t last_fom;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - last measured EOM-FOM status of lower eye.
valid only if fom_measurment bit '2' is set */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t lower_eye;
	/* Description - last measured EOM-FOM status of middle eye.
valid only if fom_measurment bit '1' is set */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t mid_eye;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_gpu_slrg_7nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask for measurement activation
Bit 0 - Upper eye
Bit 1 - Middle eye
Bit 2 - Lower eye
Bit 3- Composite eye
Note: NRZ only Bit 3 is valid */
	/* 0x0.0 - 0x0.3 */
	/* access: OP */
	u_int8_t fom_measurment;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - measured EOM status after FEQ.
valid only when SLRG.status is '1' */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t initial_fom;
	/* Description - fom mode:
FOM eye mode to search
0x0: FOM_MODE_EYEC
0x1: FOM_MODE_EYEO
0x2: FOM_MODE_EYEM
0x3: FOM_MODE_BER
0x4:FOM_MODE_EYEC_VN
0x5:FOM_MODE_EYEC_VP
0x6:FOM_MODE_EYEM_VN
0x7:FOM_MODE_EYEM_VP

 */
	/* 0x4.16 - 0x4.18 */
	/* access: RW */
	u_int8_t fom_mode;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - last measured EOM-FOM status of lower eye.
valid only if fom_measurment bit '2' is set */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t lower_eye;
	/* Description - last measured EOM-FOM status of middle eye.
valid only if fom_measurment bit '1' is set */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t mid_eye;
	/* Description - last measured EOM-FOM status of upper eye.
valid only if fom_measurment bit '0' is set */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t upper_eye;
	/* Description - last measured EOM-FOM status of composite eye.
valid only if fom_measurment bit '3' is set */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t last_fom;
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_gpu_slrg_all_lanes_5nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - FOM type measurement
0: SNR - bit scale of 1/256 dB.
The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values. */
	/* 0x0.0 - 0x0.3 */
	/* access: OP */
	u_int8_t fom_mode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t fom_lane1;
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t fom_lane0;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t fom_lane3;
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t fom_lane2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t fom_lane5;
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t fom_lane4;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t fom_lane7;
	/* Description - FOM value on the media lane <i> According to fom_mode value */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t fom_lane6;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_gpu_sltp_16nm_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Value of each tap is between -96 to 96

NOTE: The total sum of all absolute taps values should be 96 or smaller.
 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t post_tap;
	/* Description - Value of each tap is between -96 to 96

NOTE: The total sum of all absolute taps values should be 96 or smaller.
 */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t main_tap;
	/* Description - Value of each tap is between -96 to 96

NOTE: The total sum of all absolute taps values should be 96 or smaller.
 */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t pre_tap;
	/* Description - Value of each tap is between -96 to 96

NOTE: The total sum of all absolute taps values should be 96 or smaller.
 */
	/* 0x4.24 - 0x4.31 */
	/* access: RW */
	u_int8_t pre_2_tap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Output common mode. Values can be set in the range of (0-30) */
	/* 0x8.0 - 0x8.4 */
	/* access: RW */
	u_int8_t ob_alev_out;
	/* Description - Output amplitude. Values can be set in the range of (10-100). */
	/* 0x8.8 - 0x8.14 */
	/* access: RW */
	u_int8_t ob_amp;
	/* Description - MSB to LSB proportion. 
Values can be set between -10 to 50. 

MSB emphasis achieved when value is between -10 to -1 
LSB emphasis achieved when value is between 1 to 50. 
When set to 0 - equal proportion. */
	/* 0x8.25 - 0x8.31 */
	/* access: RW */
	u_int8_t ob_m2lp;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Bitmask for bad 'set' status:
0: configuration_warning - taps values can't be set to serdes due to internal limitations. Actual TX configuration is modify internally with the same sum of taps weight.
11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev is in legal range each, but the total combination can't be set to serdes due to internal limitations, the Set command is ignored.
12: Illegal_ob_m2lp
13: Illegal_ob_amp
14: Illegal_ob_alev_out
15: Illegal_taps

Bit 12-0 - Reserved /Unknown */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t ob_bad_stat;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Values can be set in the range of (0-200). */
	/* 0x10.0 - 0x10.7 */
	/* access: RW */
	u_int8_t regp_bfm1n;
	/* Description - Values can be set in the range of (0-200). */
	/* 0x10.8 - 0x10.15 */
	/* access: RW */
	u_int8_t regn_bfm1p;
	/* Description - Values can be set in the range of (0-200). */
	/* 0x10.16 - 0x10.23 */
	/* access: RW */
	u_int8_t obnlev;
	/* Description - Values can be set in the range of (0-200). */
	/* 0x10.24 - 0x10.31 */
	/* access: RW */
	u_int8_t obplev;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_gpu_sltp_28nm_40nm_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 
 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t ob_tap2;
	/* Description - 
 */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t ob_tap1;
	/* Description - 
 */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t ob_tap0;
	/* Description - Tx lane polarity */
	/* 0x4.24 - 0x4.24 */
	/* access: RW */
	u_int8_t polarity;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t ob_bias;
	/* Description - (ref_txcml100_reg) */
	/* 0x8.8 - 0x8.15 */
	/* access: RW */
	u_int8_t ob_reg;
	/* Description - Concatenation of taps polarity + preemp_sel */
	/* 0x8.16 - 0x8.19 */
	/* access: RW */
	u_int8_t ob_preemp_mode;
	/* Description -  */
	/* 0x8.20 - 0x8.23 */
	/* access: RW */
	u_int8_t ob_leva;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Bitmask for bad SET status:
Bit 0 - Illegal ob_bais value
Bit 1 - Illegal ob taps polarity (distance between taps) */
	/* 0xc.29 - 0xc.30 */
	/* access: RO */
	u_int8_t ob_bad_stat;
	/* Description - OB Normalization status:
0 - No Normalization was done
1 - Normalization performed */
	/* 0xc.31 - 0xc.31 */
	/* access: RO */
	u_int8_t ob_norm;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_gpu_sltp_5nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask for bad 'set' status:
Bit 0: tap0_is_out_of_range
Bit 1: tap1_is_out_of_range
Bit 2: tap2_is_out_of_range
Bit 3: tap3_is_out_of_range
Bit 4: tap4_is_out_of_range
Bit 5: tap5_is_out_of_range
Bit 6: tap6_is_out_of_range
Bit 7: tap7_is_out_of_range
Bit 8: tap8_is_out_of_range
Bit 9: tap9_is_out_of_range
Bit 10: tap10_is_out_of_range
Bit 11: tap11_is_out_of_range
Bit 9: sum_of_taps_is_out_of_range */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t ob_bad_stat;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t tap0;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t tap1;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t tap2;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.24 - 0x4.31 */
	/* access: RW */
	u_int8_t tap3;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t tap4;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x8.8 - 0x8.15 */
	/* access: RW */
	u_int8_t tap5;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x8.16 - 0x8.23 */
	/* access: RW */
	u_int8_t tap6;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x8.24 - 0x8.31 */
	/* access: RW */
	u_int8_t tap7;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0xc.0 - 0xc.7 */
	/* access: RW */
	u_int8_t tap8;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0xc.8 - 0xc.15 */
	/* access: RW */
	u_int8_t tap9;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0xc.16 - 0xc.23 */
	/* access: RW */
	u_int8_t tap10;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
For 200G per lane 12 taps. taps0-2/3 -> pre; tap3/4 -> main tap; 
taps4/5-11 -> post
Main tap can be chosen as tap3 or tap4 while other taps will be considered pre / post taps accordingly.
In order to determine the main tap, tap should be configured with main tap valid values

Valid values for taps:
main [32,63]
taps 2-5 that are not main [-31,31]
tap 1 pre [-8,8]
taps 6-12 post [-8,8]

for 100G per lane 5 taps (tap0 (pre3), tap1(pre2), tap2(pre1), tap3(main), tap4(post1) )
For 50G per lane 4 taps are used (no pre3)
For 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63. And Also:
|tap0| + | tap1| <8
|tap6| + | tap7| + | tap8|<8
|tap9| + | tap10| + | tap11| <8
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0xc.24 - 0xc.31 */
	/* access: RW */
	u_int8_t tap11;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_gpu_sltp_7nm_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
for 100G per lane 5 taps, 
for 50G per lane 4 taps are used (no pre3),
or 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63.
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t fir_pre2;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
for 100G per lane 5 taps, 
for 50G per lane 4 taps are used (no pre3),
or 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63.
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t fir_pre3;
	/* Description - Bitmask for bad 'set' status:
Bit 0: pre3_is_out_of_range
Bit 1: pre2_is_out_of_range
Bit 2: pre1_is_out_of_range
Bit 3: main_tap_is_out_of_range
Bit 4: post1_is_out_of_range
Bit 5: sum_of_taps_is_out_of_range
Bit 6: taps_not_alinged_with_speed */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t ob_bad_stat;
	/* Description - High speed output driver amplitude settings, default = 6"d63.
 amplitude scaling = (AMP+1) / 64 */
	/* 0x0.24 - 0x0.29 */
	/* access: RW */
	u_int8_t drv_amp;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
for 100G per lane 5 taps, 
for 50G per lane 4 taps are used (no pre3),
or 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63.
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t fir_post1;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
for 100G per lane 5 taps, 
for 50G per lane 4 taps are used (no pre3),
or 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63.
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t fir_main;
	/* Description - Signed value for TX FIR taps.
tap scaling = fir_tap/63.
for 100G per lane 5 taps, 
for 50G per lane 4 taps are used (no pre3),
or 25G per lane 3 taps are used (no pre3,pre2)
Valid values for taps:
fir_main [34,63]
fir_pre1 [-23,0]
fir_pre2 [0,8]
fir_pre3 [-5,0]
fir_post1 [-21,0]

Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| <= 63.
NRZ speeds must guarantee sum|c(i)| = 63
Note: Configured taps may get effective value of +/-1 from the value that has been set. */
	/* 0x4.24 - 0x4.31 */
	/* access: RW */
	u_int8_t fir_pre1;
};

/* Description -   */
/* Size in bytes - 12 */
union reg_access_gpu_MRFV_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_MRFV_CVB_ext MRFV_CVB_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_MRFV_PVS_MAIN_ext MRFV_PVS_MAIN_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_gpu_MRFV_PVS_TILE_ext MRFV_PVS_TILE_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_MRFV_ULT_ext MRFV_ULT_ext;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_lane_2_module_mapping_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module number */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t module;
	/* Description - Reserved for HCA 
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t slot_index;
	/* Description - TX lane. 
When m_lane_m field is set, this field is ignored (Reserved). 
When rxtx field is cleared, this field is used for RX as well. */
	/* 0x0.16 - 0x0.19 */
	/* access: RW */
	u_int8_t tx_lane;
	/* Description - RX lane.
When m_lane_m field is set, this field is ignored (Reserved). 
When rxtx field is cleared, this field is ignored and RX lane is equal to TX lane. */
	/* 0x0.24 - 0x0.27 */
	/* access: RW */
	u_int8_t rx_lane;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_gpu_mgir_dev_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The format of the string represented by ASCII. */
	/* 0x0.24 - 0x1c.23 */
	/* access: RO */
	u_int8_t dev_branch_tag[28];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_gpu_mgir_fw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_sub_minor. */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t sub_minor;
	/* Description - Minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_minor. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major firmware version number.
Deprecated and returns '0'. 
Refer to extended_major. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t major;
	/* Description - When set, the device is running firmware with secure-firmware updates capabilities. */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t secured;
	/* Description - When set the device is running a signed FW binaries. */
	/* 0x0.25 - 0x0.25 */
	/* access: RO */
	u_int8_t signed_fw;
	/* Description - When set, the device is running a debug firmware. 'debug' binary can only be installed on specific devices (identified by their 'Factory base MAC'), which currently run a specific firmware version. These restrictions are expressed by a signed 'debug' token that must be loaded to the device before installing the debug binary. */
	/* 0x0.26 - 0x0.26 */
	/* access: RO */
	u_int8_t debug;
	/* Description - *NOTE* this field has diff meaning for Switch vs. NIC 



 */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t dev;
	/* Description - When set, string-TLV is supported.
For Retimer - always return 0 (not supported). */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t string_tlv;
	/* Description - *NOTE* for NICs same as dev field
Development-secure:
The device is running:
0: a regular-secure firmware version
1: a development-secure firmware version */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t dev_sc;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Firmware Build ID. Optional. 
Note: Deprecated for switches and returns '0'. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t build_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t year;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t day;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Firmware installation hour.
For example 17:43 will be coded as 0x1743 */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t hour;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - FW PSID */
	/* 0x10.24 - 0x20.23 */
	/* access: RO */
	u_int8_t psid[16];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - User-configured version number of the current INI file. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t ini_file_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - FW version's Major field in extended (32b) format. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t extended_major;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - FW version's Minor field in extended (32b) format. */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t extended_minor;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - FW version's SubMinor field in extended (32b) format. */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t extended_sub_minor;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - incremented by one when version is not ISSUable */
	/* 0x30.0 - 0x30.15 */
	/* access: RO */
	u_int16_t isfu_major;
	/* Description - Bitmap representing the disabled tiles in the ASIC. Tile '0' is represented by the msb bit. 
0: tile is enabled
1: tile is disabled

The total number of tiles can be derived through MGPIR register. */
	/* 0x30.16 - 0x30.31 */
	/* access: RO */
	u_int16_t disabled_tiles_bitmap;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - 0: Production
1: GA Secured
2: GA Non-Secured
3: RMA
4: Pre Production
Note: has also msb bits in life_cycle_msb.
 */
	/* 0x34.0 - 0x34.1 */
	/* access: RO */
	u_int8_t life_cycle;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.2 - 0x34.2 */
	/* access: RO */
	u_int8_t sec_boot;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.3 - 0x34.3 */
	/* access: RO */
	u_int8_t encryption;
	/* Description - [DWIP]
MSB of the life cycle.
Supported in QM3, CX8 and on. */
	/* 0x34.4 - 0x34.6 */
	/* access: RO */
	u_int8_t life_cycle_msb;
	/* Description - [DWIP]
ISSU-able:
0: not ISSUable
1: ISSUable
Supported from Quantum-3 and on
Supported for Retimers
Based on FW decisions: fuse, INI, NV and version on flash vs. running version */
	/* 0x34.13 - 0x34.13 */
	/* access: RO */
	u_int8_t issu_able;
	/* Description - [DWIP]
0: PSC is not PDS mode
1: PSC in PDS mode
Supported in QM3,CX8 and on. */
	/* 0x34.14 - 0x34.14 */
	/* access: RO */
	u_int8_t pds;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_mgir_hardware_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PCI device ID. */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t device_id;
	/* Description - See Table 258, "Device HW Revision Descriptions," on page 227 */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t device_hw_revision;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Process Voltage Scaling
Supported nominal V_CORE voltage (in 50mV units) for the device. */
	/* 0x4.0 - 0x4.4 */
	/* access: RO */
	u_int8_t pvs;
	/* Description - Process technology
0: N/A
1: 40nm
2: 28nm
3: 16nm
4: 7nm
5: 5nm
6-31: Reserved */
	/* 0x4.11 - 0x4.15 */
	/* access: RO */
	u_int8_t technology;
	/* Description - Number of physical port the device supports.
For Retimer: returns the number of data path 
 */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t num_ports;
	/* Description - [DWIP]
IB MAD Protocol. Based on value from ConfigProfile
0: IBg1
1: IBg2
2-7: Reserved */
	/* 0x4.28 - 0x4.30 */
	/* access: RO */
	u_int8_t ib_mad_gen;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The PCI device-ID of the NIC/HCA in recovery (Livefish) mode. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t hw_dev_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - [DWIP]
The device is running:
0: a regular-secure firmware version
1: a development-secure firmware version

Supported in QM3,CX8 and on. */
	/* 0xc.30 - 0xc.30 */
	/* access: RO */
	u_int8_t development;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - MSB of the "base" MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not supported. */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t manufacturing_base_mac_47_32;
	/* Description - [DWIP]
Geographical Address
0: ASIC 0
1: ASIC 1
2: ASIC 2
3: ASIC 3
Valid for multi ASIC platforms only */
	/* 0x10.16 - 0x10.21 */
	/* access: RO */
	u_int8_t ga;
	/* Description - [DWIP]
Chip Type
0: Real chip
1: Emulation
2: ChipSim
3: SimX 
Supported from Quantum-3 and ArcusE */
	/* 0x10.24 - 0x10.27 */
	/* access: RO */
	u_int8_t chip_type;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - LSB of the "base" MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not supported. */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t manufacturing_base_mac_31_0;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in secs.) since last reset0 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t uptime;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_mgir_sw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor Driver version number.
 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t sub_minor;
	/* Description - Minor Driver version number.
 */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major Driver version number.
 */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - ROM 3 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t rom3_type;
	/* Description - Arch type of ROM 3:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t rom3_arch;
	/* Description - ROM 2type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t rom2_type;
	/* Description - Arch type of ROM 2:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.12 - 0x4.15 */
	/* access: RO */
	u_int8_t rom2_arch;
	/* Description - ROM 1type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t rom1_type;
	/* Description - Arch type of ROM 1:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.20 - 0x4.23 */
	/* access: RO */
	u_int8_t rom1_arch;
	/* Description - ROM 0 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t rom0_type;
	/* Description - Arch type of ROM 0:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t rom0_arch;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - ROM 0 version. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	struct reg_access_gpu_rom_version_ext rom0_version;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ROM 1 version. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	struct reg_access_gpu_rom_version_ext rom1_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - ROM 2version. */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	struct reg_access_gpu_rom_version_ext rom2_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - ROM 3 version. */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	struct reg_access_gpu_rom_version_ext rom3_version;
};

/* Description -   */
/* Size in bytes - 248 */
union reg_access_gpu_pddr_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_module_latched_flag_info_ext module_latched_flag_info_ext;
	/* Description -  */
	/* 0x0.0 - 0xf0.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_link_down_info_page_ext pddr_link_down_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xd4.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_module_info_ext pddr_module_info_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_operation_info_page_ext pddr_operation_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_phy_info_page_ext pddr_phy_info_page_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_troubleshooting_page_ext pddr_troubleshooting_page_ext;
};

/* Description -   */
/* Size in bytes - 12 */
union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext pmmp_cmis_protocol_override_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext pmmp_qsfp_protocol_override_layout_ext;
};

/* Description -   */
/* Size in bytes - 12 */
union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext pmmp_sfp_protocol_bytes_override_ext;
};

/* Description -   */
/* Size in bytes - 248 */
union reg_access_gpu_ppcnt_reg_counter_set_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext IB_long_portcntrs_attribute_grp_data_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext IB_portcntrs_attribute_grp_data_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext eth_2819_cntrs_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext eth_2863_cntrs_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext eth_3635_cntrs_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext eth_802_3_cntrs_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_discard_cntrs_grp_ext eth_discard_cntrs_grp_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext eth_extended_cntrs_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_per_prio_grp_data_layout_ext eth_per_prio_grp_data_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext eth_per_traffic_class_cong_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_eth_per_traffic_class_layout_ext eth_per_traffic_class_layout_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_phys_layer_cntrs_ext phys_layer_cntrs_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_phys_layer_stat_cntrs_ext phys_layer_stat_cntrs_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_ppcnt_infiniband_general_counter_ext ppcnt_infiniband_general_counter_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext ppcnt_infiniband_packets_counter_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_ppcnt_plr_counters_ext ppcnt_plr_counters_ext;
	/* Description -  */
	/* 0x0.0 - 0xf4.31 */
	/* access: RW */
	struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext ppcnt_rs_fec_histograms_counters_ext;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_gpu_pphcr_bin_range_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - low range of bin's measurement */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t low_val;
	/* Description - high range of bin's measurement */
	/* 0x0.16 - 0x0.19 */
	/* access: RW */
	u_int8_t high_val;
};

/* Description -   */
/* Size in bytes - 28 */
union reg_access_gpu_pter_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_gpu_pter_phy_page_reg_ext pter_phy_page_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_gpu_pter_port_page_reg_ext pter_port_page_reg_ext;
};

/* Description -   */
/* Size in bytes - 36 */
union reg_access_gpu_slrg_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_16nm_ext slrg_16nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_40nm_28nm_ext slrg_40nm_28nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_5nm_ext slrg_5nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_7nm_ext slrg_7nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_all_lanes_5nm_ext slrg_all_lanes_5nm_ext;
};

/* Description -   */
/* Size in bytes - 72 */
union reg_access_gpu_sltp_reg_page_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_gpu_sltp_16nm_ext sltp_16nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_gpu_sltp_28nm_40nm_ext sltp_28nm_40nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_gpu_sltp_5nm_ext sltp_5nm_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_gpu_sltp_7nm_ext sltp_7nm_ext;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_stat_bufferx_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Watermark in cells (max buffer usage since last clear)
For stat_shared_headroom_pool, this field is reserved. */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t watermark;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of used buffer cells.
For stat_port_shared_headroom_pool this field is reserved. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t used_buffer;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_string_db_parameters_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Offset of the first string of the section, relative to the entire string data base, given in bytes. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t string_db_base_address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Size of string database section, given in bytes */
	/* 0x4.0 - 0x4.23 */
	/* access: RO */
	u_int32_t string_db_size;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_gpu_MLPC_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - port MSB
Used to identify the L1 controller associated to the desired HW counters. */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - port
Used to identify the L1 controller associated to the desired HW counters. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit mask to configure extended 64 bits long counters.
Bit per even HW counter. When bit [i] is set, counter[2i] and counter[2i+1] will be used to form a 64-bit counter.
The odd counter cnt_sel[2i+1], will serve as the selector to configure the 64 bit counter.
The odd counter cnt_val[2i+1], will serve as the LSB of the counter.
The even counter cnt_val[2i], will serve as the MSB of the counter. */
	/* 0x4.0 - 0x4.3 */
	/* access: RW */
	u_int8_t cnt_64bit;
	/* Description - When set, when one of the perf counters reaches FFs, all the counters will stop counting. */
	/* 0x4.29 - 0x4.29 */
	/* access: RW */
	u_int8_t stop_at_ff;
	/* Description - Force reset for all the counters */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t counter_rst;
	/* Description - Enable for the HW counters */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t counter_en;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Force count bit mask, when bit[i] is set, pref_counter<i> will count with no consideration of any enable/reset/stop signals. */
	/* 0xc.0 - 0xc.7 */
	/* access: RW */
	u_int8_t force_count_mask;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - See Table 203, "L1 Performance Counter Type," on page 184 */
	/* 0x10.28 - 0x14.27 */
	/* access: RW */
	u_int8_t cnt_type[8];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - HW counter value.
The counter value can be configured to an initial value before enabling the feature. */
	/* 0x20.0 - 0x3c.31 */
	/* access: RW */
	u_int32_t cnt_val[8];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_gpu_MRFV_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Fuse Index
0: cvb - CVB Main Die, used for Retimer
1: ULT - used for Retimer
2: pvs_main_die - (used for SPC-4)
3: pvs_tile_0 - (used for SPC-4)
4: pvs_tile_1 - (used for SPC-4)
5: pvs_tile_2 - (used for SPC-4)
6: pvs_tile_3 - (used for SPC-4)
7: pvs_tile_4 - (used for SPC-4)
8: pvs_tile_5 - (used for SPC-4)
9: pvs_tile_6 - (used for SPC-4)
10: pvs_tile_7 - (used for SPC-4)
Other values reserved
Reserved when fm = 1 */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t fuse_id;
	/* Description - Fuse Mismatch
0: No fuse mismatch
1: Fuse mismatch found
2-3: Reserved */
	/* 0x0.24 - 0x0.25 */
	/* access: RO */
	u_int8_t fm;
	/* Description - Valid bit
0: Fuse reading is not supported for this system
1: Response is valid
2-3: Reserved
Reserved when fm = 1 */
	/* 0x0.30 - 0x0.31 */
	/* access: RO */
	u_int8_t v;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Data
See Table 289, "MRFV entry - CVB Layout," on page 247
See Table 291, "MRFV entry - ULT Layout," on page 248
See Table 293, "MRFV entry - PVS_MAIN Layout," on page 249
See Table 295, "MRFV entry - PVS_Tile Layout," on page 250
Reserved when fm = 1 */
	/* 0x10.0 - 0x18.31 */
	/* access: RO */
	union reg_access_gpu_MRFV_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_MTSR_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Normal
1: Warning
2: Critical
3-7: Reserved */
	/* 0x0.0 - 0x0.2 */
	/* access: RO */
	u_int8_t mode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Num of normal thermal events triggered */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t normal_events_cnt;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Num of warning thermal events triggered */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t warning_events_cnt;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Num of critical thermal events triggered */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t critical_events_cnt;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_ghpkt_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Trap IDs
See Section 1197, "GPUNet Trap IDs", on page 1292 */
	/* 0x0.0 - 0x0.9 */
	/* access: INDEX */
	u_int16_t trap_id;
	/* Description - Action to perform on trap_id
0: NOP 
1: TRAP */
	/* 0x0.20 - 0x0.23 */
	/* access: RW */
	u_int8_t action;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_gpgb_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local Port */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - FIFO buffer size between the TLW and the GTXS that is configured
within the GTXS.
Units of 8B. */
	/* 0x4.0 - 0x4.9 */
	/* access: RO */
	u_int16_t buffer_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - RX pipe0 TLW to GRXB request initial credits. */
	/* 0x8.0 - 0x8.9 */
	/* access: RW */
	u_int16_t grxb_p0_req_credits;
	/* Description - RX pipe0 TLW to GRXB response initial credits. */
	/* 0x8.16 - 0x8.25 */
	/* access: RW */
	u_int16_t grxb_p0_rsp_credits;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - RX pipe1 TLW to GRXB request initial credits. */
	/* 0xc.0 - 0xc.9 */
	/* access: RW */
	u_int16_t grxb_p1_req_credits;
	/* Description - RX pipe1 TLW to GRXB response initial credits. */
	/* 0xc.16 - 0xc.25 */
	/* access: RW */
	u_int16_t grxb_p1_rsp_credits;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_gplid {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local Port */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The Port LID configured to the GPU Port. 
[Internal] Notice: the port LID has 20 bits for future compatibility, but only the 16 LSBs are being used. */
	/* 0x4.0 - 0x4.19 */
	/* access: RO */
	u_int32_t lid;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_gsguid_ext {
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The system GUID of the device. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t system_guid_h;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The system GUID of the device. */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t system_guid_l;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_gpu_mcam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups 
0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)
1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).
2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).
3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF). */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t access_reg_group;
	/* Description - Feature list mask index: 
0: enhanced_features */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t feature_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported management's access register bitmask. Based on access_reg_group index. 
When bit is set, the register is supported in the device. 
For example:
Bit 1: MFCR_0x9001
Bit 2: MFSC_0x9002
Bit 3: MFSM_0x9003
Bit 4: MFSL_0x9004
Bit 58: MGCR_0x903A
Bit 73: MPPF_0x9049
Bit 127: MCAP_0x907F */
	/* 0x8.0 - 0x14.31 */
	/* access: RO */
	u_int32_t mng_access_reg_cap_mask[4];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Supported port's enhanced features.Based on feature_group index.
When bit is set, The feature is supported in the device: 
Bit 0: MPCNT counter group- PCIE performance counters supported
Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.
Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_adjustment field in MTPPS register is supported.
Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.
Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.
Bit 5: Management pass through is supported
Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.
Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register is supported. 
Bit 8: beacon_capability_disable - If set, beacon feature, as appears in MLCR register, in not supported by the device. 
Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. 
Bit 10: mark_tx_action_cqe is supported if set to '1'.
Bit 11: mark_tx_action_cnp is supported if set to '1'.
Bit 12: dev_info is supported in  register is set to '1'.
Bit 13: sensor_count field is 12bit size in MTMP and MTBR
Bit 14: cs_tokens_supported is supported 
Bit 15: debug_fw_tokens_supported
Bit 16: long_keys is supported 
Bit 17: pwr_status and pci_power are supported in MPEIN
Bit 18: If set, accessing through device_type and device_index is supported in MCC, MCQI and MCQS
Bit 19: pcie_sync_for_fw_update_supported is set to '1'
Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is supported
Bit 21: If set to '1', reset_state in MFRL is supported
Bit 22: If set to '1', link_peer_max_speed is supported in MPEIN Register
Bit 23: If set to '1', slot_index field is supported in: MCIA, MCAS, MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.
Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and MCQS.
Bit 26: If set, progress field is supported in MCQS
Bit 28: If set, number_of_slots field is supported in MGPIR.
Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.
Bit 30: If set, my_pf_number is supported in MPPF.
Bit 31: If set, sdee is supported in MTMP
Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.
Bit 35: If set, MGIR.hw_info.technology is supported. 
Bit 37: If set, lp_msb is supported for MLCR, MPIR 
Bit 39: If set, MRCS and RMDT tokens are supported in MCQS
Bit 40: If set, 'encryption' field in MGIR is supported
Bit 43: If set, MFCR supports tacho_active_msb field
Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields
Bit 45: If set, MFRL.pci_rescan_required is supported
Bit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment range is extended to -200,000 to +200,000
Bit 47: If set, MTUTC.freq_adj_units=1 is supported
Bit 48: If set, MRSR.command=6 is supported
Bit 49: If set, MCQS.identifier support CRCS and CRDT tokens
Bit 51: If set, MTUTC.freq_adj_units=2 is supported
Bit 53: If set, Mlx mlxfwreset with downstream port is supported by FW [Internal]: NIC only, FW rejects reset till user committed that traffic is disabled
Bit 59: If set, MCC.component_specific_error_code is valid for LinkX devices
Bit 60: If set, MGNLE.clr is supported
Bit 61: If set, MGIR supports life_cycle_msb and pds fields in FW info and development field in HW info.


Bit 65: If set, MVCR support current_sensor_value_msb
Bit 66: If set. MFRL supports pci_reset_req_method, pci_switch_exist fields. [DWIP]
Bit 67: If set, MRSR.cmd = 6 works with SBR */
	/* 0x28.0 - 0x34.31 */
	/* access: RO */
	u_int32_t mng_feature_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 148 */
struct reg_access_gpu_mcia_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module Status
0: SUCCESS
1: NO_EEPROM_MODULE. No response from module's EEPROM.
2: MODULE_NOT_SUPPORTED. Module type not supported by the device. 3: MODULE_NOT_CONNECTED. No module present indication. 
4: MODULE_TYPE_INVALID - module is not supported by INI. 

9: I2C_ERROR. Error occurred while trying to access the module's EEPROM using I2C.
16: MODULE_DISABLED - module is disabled 
 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t status;
	/* Description - Slot index
0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module number

 */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - [DWIP]:
Page Number Valid
0: write page number
1: don't write page number
Valid only if module is in SW control */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t pnv;
	/* Description - Lock Page bit. 
When bit is set, FW can access the last accessed page.
After boot and ISSU, default value is 0.

 */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t l;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Device address */
	/* 0x4.0 - 0x4.15 */
	/* access: INDEX */
	u_int16_t device_address;
	/* Description - Page number
Reserved when MCIA.l = 1 or when MCIA.pnv = 1 */
	/* 0x4.16 - 0x4.23 */
	/* access: INDEX */
	u_int8_t page_number;
	/* Description - I2C device address
 */
	/* 0x4.24 - 0x4.31 */
	/* access: INDEX */
	u_int8_t i2c_device_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes to read/write (up to 128 bytes) */
	/* 0x8.0 - 0x8.15 */
	/* access: INDEX */
	u_int16_t size;
	/* Description - Bank number */
	/* 0x8.16 - 0x8.23 */
	/* access: INDEX */
	u_int8_t bank_number;
	/* Description - 0: password length is 4B (password_msb is reserved)
1: password length is 8B (password_msb is used) */
	/* 0x8.28 - 0x8.28 */
	/* access: OP */
	u_int8_t passwd_length;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The password that is written to the module password field.
This field is reserved when passwd_cap is not set to 1. 
Reserved when module is in SW control. */
	/* 0xc.0 - 0xc.31 */
	/* access: OP */
	u_int32_t password;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bytes to read/write
Note: some FW versions support only 12*4B
See MCAM bit34 */
	/* 0x10.0 - 0x8c.31 */
	/* access: RW */
	u_int32_t dword[32];
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - password msb
Supported only when MCAM bit34 is set
Supported only when passwd_cap is set
Reserved when passwd_length = 0 */
	/* 0x90.0 - 0x90.31 */
	/* access: RW */
	u_int32_t password_msb;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_mcion_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index
0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module number

 */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module IO status, as defined by SFF and CMIS:
Bit 0: Present
Bit 1: RX_LOS
Bit 2: TX_Fault
Bit 6: LPMode
[DWIP] Bit 7: Interrupt (IntL)
Bit 8: Low Power Mode Status 
[DWIP] Bit 9: Power Good
If bit 0 (Present) is clear, all other bits are reserved. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t module_status_bits;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - [DWIP][SwitchOnly]
Module inputs: 
Bit 0: ResetL - low polarity
Bit 1: LPMode
Bit 2: Power Enable
Reserved when module is controlled by FW */
	/* 0xc.0 - 0xc.3 */
	/* access: RW */
	u_int8_t module_inputs;
	/* Description - [DWIP][SwitchOnly]
Module Inputs Valid Bitmask
Bitmask which mentions the validity of module_inputs fields.
For each bit, 0 means valid, 1 means not valid.
For example:
Bit 0: if set, present bit value is ignored. If cleared, value is valid.
Bit 1: if set, rx loss value is ignored. when cleared, value is valid and so on for all bits mentioned in module_inputs.
Reserved when module is controlled by FW */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t module_status_bits_valid;
};

/* Description -   */
/* Size in bytes - 80 */
struct reg_access_gpu_mcsr {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Base CrSpace address */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t base_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of CrSpace consecutive accesses.
Each access is 4B (DWord)
Range 1..16 DWORDs */
	/* 0x8.0 - 0x8.8 */
	/* access: OP */
	u_int16_t num_addresses;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The CrSpace data */
	/* 0x10.0 - 0x4c.31 */
	/* access: RW */
	u_int32_t data[16];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_gpu_mdrcr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Peripheral device type
1: Gearbox
 */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t device_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Device number 
For gearboxes, the index represents the gearbox die. */
	/* 0x4.0 - 0x4.11 */
	/* access: INDEX */
	u_int16_t device_index;
	/* Description - All devices are selected and device_index is ignored
When set to '1', the rst_status should represent the worst case of any of the devices. */
	/* 0x4.31 - 0x4.31 */
	/* access: INDEX */
	u_int8_t all;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Reset Operation.
0: Query of the reset status which is displayed through rst_status.
1: Full Reset of the selected device(s).
2-8: Reserved. */
	/* 0xc.0 - 0xc.2 */
	/* access: RW */
	u_int8_t rst_op;
	/* Description - Reset status.
0: Reset completed successfully. 1: Reset operation has not finished yet. */
	/* 0xc.16 - 0xc.19 */
	/* access: RO */
	u_int8_t rst_status;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_gpu_mgir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see Table 256, "Hardware Info Layout," on page 225 */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_mgir_hardware_info_ext hw_info;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Firmware Information, see Table 259, "Firmware Info Layout," on page 228 */
	/* 0x20.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_gpu_mgir_fw_info_ext fw_info;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Software Information, see Table 261, "Software Info Layout," on page 231
This field indicates the oldest software version compatible with the current firmware */
	/* 0x60.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_gpu_mgir_sw_info_ext sw_info;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Development Information, see Table 265, "Development Info Layout," on page 234 */
	/* 0x80.0 - 0x98.31 */
	/* access: RW */
	struct reg_access_gpu_mgir_dev_info_ext dev_info;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_mmdio_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - NOP
1 - Address (reserved for Clause 22)
2 - Read
3 - Write
4 - Post Read Increment Address (reserved for Clause 22)
6 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
7 - Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22) */
	/* 0x0.0 - 0x0.2 */
	/* access: WO */
	u_int8_t operation;
	/* Description - MDIO Definition:
0 - Clause 22
1 - Clause 45 */
	/* 0x0.8 - 0x0.9 */
	/* access: WO */
	u_int8_t clause;
	/* Description - Selection of the MDIO interface */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t mdio_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reg Address (Clause 22) / Dev Type (Clause 45) */
	/* 0x4.0 - 0x4.4 */
	/* access: RW */
	u_int8_t reg_adr;
	/* Description - PHY Address (PHYAD) */
	/* 0x4.8 - 0x4.12 */
	/* access: RW */
	u_int8_t phy_adr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Data (Clause 22) / Address/Data (Clause 45) */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t data;
	/* Description - Address (Clause 45)
This field is only valid for Address + Read and Address + Write operations, providing the address. For other Clause 45 operations the data field provides the address when appropriate. */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t address;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_mpscr_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Thermal Throttling (FW mode) warning inactive time
Each unit is equivalent to 100uSec
Reserved for Switch.
 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t warning_inactive_time;
	/* Description - Thermal Throttling (FW mode) warning active time
Each unit is equivalent to 100uSec
Reserved for Switch.
 */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t warning_active_time;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Thermal Throttling (FW mode) critical inactive time
Each unit is equivalent to 100uSec
Reserved for Switch.
 */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t critical_inactive_time;
	/* Description - Thermal Throttling (FW mode) critical active time
Each unit is equivalent to 100uSec
Reserved for Switch.
 */
	/* 0x8.16 - 0x8.23 */
	/* access: RW */
	u_int8_t critical_active_time;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Clear Counters
0: Don't clear MTSR counters
1: Clear MTSR counters
Reserved for Switch. */
	/* 0x10.0 - 0x10.0 */
	/* access: OP */
	u_int8_t cc;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_mtcap_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of ASIC+platform sensors supported by the device 
This includes the ASIC and the ambient sensors. Module sensors are not included.
This actually is equal to sum of all '1' in sensor_map
Range 1..64

Known sensors:
0: current asic temp, FW exposes current max(all diode temp sensors)
1..63: ambient, supported only for unmanaged switch, defined by ini
64..127: modules (not exposed by this field) */
	/* 0x0.0 - 0x0.6 */
	/* access: RO */
	u_int8_t sensor_count;
	/* Description - Slot index
0: Main board */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of sensors supported by the device that are on the ASIC.
Exposes how many ASIC diodes exist. 
The FW exposes all of them as sensor[0] */
	/* 0x4.0 - 0x4.6 */
	/* access: RO */
	u_int8_t internal_sensor_count;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Mapping of system sensors supported by the device. Only ASIC and ambient sensors are supported. Each bit represents a sensor.
Per bit:
0: Not_connected_or_not_supported
1: Supports_temperature_measurements */
	/* 0x8.0 - 0xc.31 */
	/* access: RO */
	u_int64_t sensor_map;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_gpu_mtecr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of sensors supported by the ASIC+platform
This includes the ASIC, ambient sensors, module sensors, Gearboxes etc. 
This actually is equal to sum of all '1' in sensor_map

Known sensors:
0: current asic temp, FW exposes current max(all diode temp sensors)
1..62: ambient, supported only for unmanaged switch, defined by ini
64..255: modules
256..288: Gearbox
289..704: reserved for future */
	/* 0x0.0 - 0x0.11 */
	/* access: RO */
	u_int16_t sensor_count;
	/* Description - Last sensor index that is available in the system to read from.
e.g. when 32modules: 64+32-1 = 95 */
	/* 0x0.16 - 0x0.27 */
	/* access: RO */
	u_int16_t last_sensor;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of sensors supported by the device that are on the ASIC. 
Exposes how many ASIC diodes exist. 
The FW exposes all of them as sensor[0] */
	/* 0x4.0 - 0x4.6 */
	/* access: RO */
	u_int8_t internal_sensor_count;
	/* Description - Slot index
0: Main board */
	/* 0x4.28 - 0x4.31 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Mapping of system sensors supported by the device. Each bit represents a sensor.
This field is size variable based on the last_sensor field and in granularity of 32bits.
Per bit:
0: Not connected or not supported
1: Supports temperature measurements

In case of last_sensor = 704 (22*32):
sensor_warning[0] bit31 is sensor_warning[703]
sensor_warning[0] bit0 is sensor_warning[703-31]
sensor_warning[21] bit31 is sensor_warning[31]
sensor_warning[21] bit0 is sensor_warning[0]

In case if last_sensor = 259 (22*32):
Note: roundup(259,32)=288
sensor_warning[0] bit31 is sensor_warning[287]
sensor_warning[0] bit0 is sensor_warning[287-31=256]
sensor_warning[8] bit31 is sensor_warning[31]
sensor_warning[8] bit0 is sensor_warning[0]
sensor_warning[9..21] are not used

64-192 of sensor_index are mapped to the modules sequentially (module 0 is mapped to sensor_index 64, module 1 to sensor_index 65 and so on). */
	/* 0x8.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t sensor_map[22];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_gpu_mteim_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of processors per tile ASIC. */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t cap_core_tile;
	/* Description - Number of processors in the main ASIC. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t cap_core_main;
	/* Description - Number of processors in the DPA unit. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t cap_core_dpa;
	/* Description - Number of tiles per device. For devices without tiles (only main ASIC), this field should be '0'. */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t cap_num_of_tile;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t type_core_tile;
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t type_core_main;
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t type_core_dpa;
	/* Description - Indicates wether Phy_UC tracers mapping are supported by the device FW. 
When set, The event_id of the Phy UC of the instance will be calculated by first_tile/main _core _event_id[i] + cap_core_tile/main.
When clear the Phy UC will be ignored. */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t is_phy_uc_supported;
	/* Description - When set to '1', the device supports dwsn_msb bit within the FW trace layout. */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t is_dwsn_msb_supported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The mapping for the rest of the DPA ASIC processors are sequential and the mapping is defined as:
processor[x]=first_dpacore_event_id+x */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t first_dpa_core_event_id;
	/* Description - The mapping for the rest of the main ASIC processors are sequential and the mapping is defined as:
processor[x]=first_main_core_event_id+x */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t first_main_core_event_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The mapping for the rest of the tile[y] ASIC processors are sequential and the mapping is defined as:
processor[x]=first_tile_core_event_id[y]+x */
	/* 0xc.24 - 0x14.23 */
	/* access: RO */
	u_int8_t first_tile_core_event_id[8];
};

/* Description -   */
/* Size in bytes - 92 */
struct reg_access_gpu_mtewe_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of sensors supported by the device
This includes the ASIC, ambient sensors, Gearboxes etc.

Known sensors:
0: current asic temp, FW exposes current max(all diode temp sensors)
1..62: ambient, supported only for unmanaged switch, defined by ini
64..255: modules
256..288: Gearbox
289..704: reserved for future */
	/* 0x0.0 - 0x0.11 */
	/* access: RO */
	u_int16_t sensor_count;
	/* Description - Slot index
0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Last sensor index that is available in the system to read from. */
	/* 0x0.16 - 0x0.27 */
	/* access: RO */
	u_int16_t last_sensor;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit vector indicating which of the sensor reading is above threshold.
This field is size dependent and based on last_sensor field and in granularity of 32bits.

In case of last_sensor = 704 (22*32):
sensor_warning[0] bit31 is sensor_warning[703]
sensor_warning[0] bit0 is sensor_warning[703-31]
sensor_warning[21] bit31 is sensor_warning[31]
sensor_warning[21] bit0 is sensor_warning[0]

In case if last_sensor = 259 (22*32):
Note: roundup(259,32)=288
sensor_warning[0] bit31 is sensor_warning[287]
sensor_warning[0] bit0 is sensor_warning[287-31=256]
sensor_warning[8] bit31 is sensor_warning[31]
sensor_warning[8] bit0 is sensor_warning[0]
sensor_warning[9..21] are not used */
	/* 0x4.0 - 0x58.31 */
	/* access: RO */
	u_int32_t sensor_warning[22];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_gpu_mtie_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable/Disable all FW tracer initiator and ignore mask.
Starts from bit 0.
0: Use bit mask
1: Enable all
2: Disable all */
	/* 0x0.0 - 0x0.1 */
	/* access: OP */
	u_int8_t enable_all;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Adding delay to log events in usecs
 */
	/* 0x4.0 - 0x4.15 */
	/* access: RW */
	u_int16_t log_delay;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bit mask of all the possible tracer initiators.
Reserved when enable_all != 0.
The mapping of source id to HW unit is unique per device and can be fetched from FW code.
 */
	/* 0x10.0 - 0x2c.31 */
	/* access: RW */
	u_int32_t source_id_bitmask[8];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_mtim_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The verbosity of the log. 
0: LOG_DEBUG
1: LOG_INFO
2: LOG_WARNING
3: LOG_ERROR

The lower value reflects higher verbosity than higher value.
e.g: LOG_INFO contains LOG_WARNING and LOG_ERROR */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t log_level;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit mask of the different FW units that can be activated for the FW log.
The mapping of source id to FW unit is unique per device and can be fetched from FW code.
 */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t log_bit_mask;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_mtmp_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sensors index
0: current asic temp, FW exposes current max(all diode temp sensors)
1..62: ambient, supported only for unmanaged switch, defined by ini
64..255: modules 256..288: Gearbox
Others up to 704 are reserved */
	/* 0x0.0 - 0x0.11 */
	/* access: INDEX */
	u_int16_t sensor_index;
	/* Description - Slot index
0: Main board */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Temperature reading from the sensor. 
Units of 0.125 Celsius degrees.
For negative values 2's complement is used (for example: -3.25 Celsius will read as 0xFFE6) */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t temperature;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The highest measured temperature from the sensor.
Reserved when mte = 0
Cleared by mtr = 1
Valid only when i = 0
 */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t max_temperature;
	/* Description - Shut Down Events Modify Set Enable:
0: all fields are set
1: only sdee field is set, all other fields reserved */
	/* 0x8.28 - 0x8.28 */
	/* access: OP */
	u_int8_t sdme;
	/* Description - Warning Events Modify Set Enable:
0: all fields are set
1: only tee field is set, all other fields reserved */
	/* 0x8.29 - 0x8.29 */
	/* access: OP */
	u_int8_t weme;
	/* Description - Max Temperature Reset:
0: do not modify the value of the max temperature register
1: clear the value of the max temperature register */
	/* 0x8.30 - 0x8.30 */
	/* access: OP */
	u_int8_t mtr;
	/* Description - Max Temperature Enable:
0: disable measuring the max temperature on a sensor
1: enables measuring the max temperature on a sensor */
	/* 0x8.31 - 0x8.31 */
	/* access: RW */
	u_int8_t mte;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - temperature_threshold_hi refers to the high threshold of Warning Event. 
If the sensor temperature measurement is above the threshold (and events are enabled), an event will be generated.
threshold_hi and threshold_lo implements hysteresis mechanism of the threshold preventing toggling of the indication.
Note that temperature_threshold_hi must be equal or lower than the system requirement.
System requirement for module is the module warning temperature.
System requirement for board/silicon sensors is according to product information parameters
Note that the temperature threshold can be used to generate an event message or an interrupt using GPIO */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t temperature_threshold_hi;
	/* Description - Temperature Shut Down Event Enable (MTSDE Register)
0: do_not_generate_event
1: generate_event
2: generate_single_event

Supported in downstream devices (devices on slots). */
	/* 0xc.28 - 0xc.29 */
	/* access: RW */
	u_int8_t sdee;
	/* Description - Temperature Warning Event Enable (MTEWE Register)
0: do_not_generate_event
1: generate_event
2: generate_single_event

 */
	/* 0xc.30 - 0xc.31 */
	/* access: RW */
	u_int8_t tee;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - temperature_threshold_lo refers to the low threshold of Warning Event. 
The offset threshold_lo implements the lower threshold for the hysteresis mechanism of over temperature alert. Once alert is set, if the temperature goes below this threshold, the alert is cleared.
Note that temperature_threshold_lo must be at least 5 degrees lower than temperature_threshold_hi */
	/* 0x10.0 - 0x10.15 */
	/* access: RW */
	u_int16_t temperature_threshold_lo;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Sensor Name
8 character long sensor name
 */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t sensor_name_hi;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Sensor Name
8 character long sensor name
 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t sensor_name_lo;
};

/* Description -   */
/* Size in bytes - 132 */
struct reg_access_gpu_mtrc_cap_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of different string sections building the database */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t num_string_db;
	/* Description - Indicates the version of the tracing mechanism.
0x0: VER_0
0x1: VER_1
Other values are reserved.
Reserved in Switch */
	/* 0x0.24 - 0x0.25 */
	/* access: RO */
	u_int8_t trc_ver;
	/* Description - When set the device supports logging traces to memory
0: FIFO Mode
1: Host Memory Mode */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t trace_to_memory;
	/* Description - Write 0x1 to register for tracer ownership, write 0x0 to de-register.
Read value 0x1 indicates tracer ownership is granted.
 */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t trace_owner;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The number of consecutive event_id that should be interpreted as a string trace */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t num_string_trace;
	/* Description - The lowest event_id that should be interpreted as a string trace */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t first_string_trace;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log 2 of the maximal size of the trace buffer given in units of 4KB */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t log_max_trace_buffer_size;
	/* Description - Tracer suppported capbailities bitmask:
0: FIFO.
1: MEM mode.
else, reserved. */
	/* 0x8.30 - 0x8.31 */
	/* access: RO */
	u_int8_t tracer_capabilities;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - String DB section parameters. */
	/* 0x10.0 - 0x4c.31 */
	/* access: RO */
	struct reg_access_gpu_string_db_parameters_ext string_db_param[8];
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_gpu_mtrc_conf_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tracing mode
0x0: FIFO
0x1: TRACE_TO_MEMORY
Other values are reserved. */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t trace_mode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Log 2 of the Size of the trace buffer, given in units of 4KB.
Value should not exceed log_max_trace_buffer_size.
Valid only for trace_mode TRACE_TO_MEMORY.
Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t log_trace_buffer_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - MKey registered for the trace buffer access.
Valid only for trace_mode TRACE_TO_MEMORY.
Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace.
Reserved for Switches. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t trace_mkey;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_gpu_mtrc_ctrl_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Field select indicated which writable fields to modify
bit 0: trace_status
Other bits are reserved. */
	/* 0x0.0 - 0x0.15 */
	/* access: WO */
	u_int16_t modify_field_select;
	/* Description - When set, an event will be generated if new Tracer events were logged since last event.
Reserved in Switches. */
	/* 0x0.27 - 0x0.27 */
	/* access: WO */
	u_int8_t arm_event;
	/* Description - Current status of the tracer
0x0: DISABLED - logging traces is stopped
0x1: ACTIVE - logging traces is active */
	/* 0x0.30 - 0x0.31 */
	/* access: RW */
	u_int8_t trace_status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - MSB of the current timesatmp counter */
	/* 0x8.0 - 0x8.20 */
	/* access: RO */
	u_int32_t current_timestamp_52_32;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - LSB of the current timesatmp counter */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t current_timestamp_31_0;
};

/* Description -   */
/* Size in bytes - 92 */
struct reg_access_gpu_mtsde {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of sensors supported by the device
This includes the ASIC, ambient sensors, Gearboxes etc. QSFP module sensors are not included. */
	/* 0x0.0 - 0x0.9 */
	/* access: RO */
	u_int16_t sensor_count;
	/* Description - Slot index
0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Last sensor index that is available in the system to read from. */
	/* 0x0.16 - 0x0.25 */
	/* access: RO */
	u_int16_t last_sensor;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit vector indicating which sensors were shut down due to critical temperature. This field is size dependent and based on last_sensor field and in granularity of 32bits.

See alignment note in MTEWE.sensor_warning */
	/* 0x4.0 - 0x58.31 */
	/* access: RO */
	u_int32_t sensor_shut_down_map[22];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_mtwe_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bit vector indicating which of the sensor reading is above threshold.
Address 00h bit31 is sensor_warning[127]
Address 0Ch bit0 is sensor_warning[0] */
	/* 0x0.0 - 0xc.31 */
	/* access: RO */
	u_int32_t sensor_warning[4];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_paos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port operational state:
1: up
2: down
4: down_by_port_failure - (transitioned by the hardware)
  
 */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Port administrative state (the desired state of the interface):
1: up
2: down_by_configuration
4: disabled_by_system - this mode cannot be set by the software, only by the hardware.
6: sleep - can be configured only if sleep_cap is set. Note that a sleep setting will cause the port to transition immediately into sleep state regardless of previous admin_status.


 */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t admin_status;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - For HCA: must always be 0.
Switch partition ID with which to associate the port.
Switch partitions are numbered from 0 to 7 inclusively.
The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query. */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t swid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event generation on operational state change (oper_status):
0: Do_not_generate_event
1: Generate_Event 
2: Generate_Single_Event

Not Supported for HCA. */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t e;
	/* Description - IB Port Physical link state:
0: N/A
1: Sleep
2: Polling
3: Disabled
4: PortConfigurationTraining
5: LinkUp
6-15: reserved
Note that physical state of 1,2,3,4 will all be reflected as oper_status = down.
[internal] Note: Supported from XDR devices onwards
LinkUp for Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready. */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t physical_state_status;
	/* Description - Force down.
Supported only when indicated in PCAM
Can be set only with admin_status = 2 ('down_by_configuration'), will force link to be down. 
 */
	/* 0x4.8 - 0x4.8 */
	/* access: RW */
	u_int8_t fd;
	/* Description - Sleep capability:
0: Sleep state is not supported
1: Sleep state supported */
	/* 0x4.9 - 0x4.9 */
	/* access: RO */
	u_int8_t sleep_cap;
	/* Description - Event generation for physical state.
On set operation, will be ignored if ee_ps is not set.
When bit is set, will generate an event for transition into state.
Bit 0: Sleep
Bit 2: Disabled
Bit 3: PortConfigurationTraining
Not Supported for HCA. */
	/* 0x4.12 - 0x4.15 */
	/* access: RW */
	u_int8_t ps_e;
	/* Description - IB or NVLink Port Logical link state:
0: N/A
1: Down
2: Init
3: Arm
4: Active */
	/* 0x4.16 - 0x4.18 */
	/* access: RO */
	u_int8_t logical_state_status;
	/* Description - event generation mask for logical state.
On set operation, will be ignored when ee_ls is not set.
When bit is set, will generate event for transition into state.
Bit 0: Down
Bit 1: Init
Bit 2: Arm
Bit 3: Active
Not Supported for HCA. */
	/* 0x4.20 - 0x4.23 */
	/* access: RW */
	u_int8_t ls_e;
	/* Description - Event update enable for physical state. If this bit is set, event generation will be updated based on the ps_e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.28 - 0x4.28 */
	/* access: WO */
	u_int8_t ee_ps;
	/* Description - Event update enable for logical state. If this bit is set, event generation will be updated based on the ls_e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.29 - 0x4.29 */
	/* access: WO */
	u_int8_t ee_ls;
	/* Description - Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t ee;
	/* Description - Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t ase;
};

/* Description -   */
/* Size in bytes - 100 */
struct reg_access_gpu_pbsr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Valid only for 8x port setting (see PMLP): 
1: Main buffer
2: Secondary buffer */
	/* 0x0.0 - 0x0.1 */
	/* access: INDEX */
	u_int8_t buffer_type;
	/* Description - Local port[9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Each bit represents a stat_buffer
per bit:
0: do not clear watermark
1: clear watermark
Reserved when clear_wm = 1 */
	/* 0x4.0 - 0x4.9 */
	/* access: OP */
	u_int16_t clear_wm_buff_mask;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of currently used shared headroom buffer cells. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t used_shared_headroom_buffer;
	/* Description - Clear watermarks for all PGs */
	/* 0x8.31 - 0x8.31 */
	/* access: OP */
	u_int8_t clear_wm;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - status per-buffer parameters. i=0..9
 */
	/* 0xc.0 - 0x58.31 */
	/* access: RO */
	struct reg_access_gpu_stat_bufferx_reg_ext stat_buffer[10];
/*---------------- DWORD[23] (Offset 0x5c) ----------------*/
	/* Description - status of shared headroom pool parameters. Using the same layout as in stat_BufferX, for details see Table 942, "stat_bufferX Register Layout," on page 1019.
Not supported in SwitchX and SwitchX-2
Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit). 
Not supported in GPUNet */
	/* 0x5c.0 - 0x60.31 */
	/* access: RO */
	struct reg_access_gpu_stat_bufferx_reg_ext stat_shared_headroom_pool;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_pbwc_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Log time interval.
This field determine the time between measurements T:
T = (2^log_time_interval) * 64uSec
Range is dependent on the port's rate:
800Gbps: 0..10
400Gbps: 0..10
200Gbps: 0..11
100Gbps: 0..12
50Gbps: 0..13
25Gbps: 0..14
10Gbps: 0..15
Default is 7, means that T = (2^7) * 64uSec = 8mSec
 */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t log_time_interval;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Alpha for the exponential moving average formula.
Alpha = 1/(2^alpha_factor)
Range 0..7

Default is 2 */
	/* 0x4.0 - 0x4.2 */
	/* access: RW */
	u_int8_t alpha_factor;
};

/* Description -   */
/* Size in bytes - 144 */
struct reg_access_gpu_pbwr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port
Each bit represents a local port. Refer to Section 9.3, "Port Numbering", on page 1710 for port numbering scheme.
Ports order in the bitmask is from bottom to top. e.g for setting local port 1, bit 1 in the last DWORD (offset 0x7Ch) should be set.
CPU port is not supported.
Router port is not supported */
	/* 0x0.0 - 0x7c.31 */
	/* access: INDEX */
	u_int32_t local_port_bitmap[32];
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Number of records.
Range 0..1024.
Range 1025..2047 is reserved. */
	/* 0x80.0 - 0x80.10 */
	/* access: OP */
	u_int16_t num_rec;
	/* Description - Direction:
0: ingress
1: egress */
	/* 0x80.31 - 0x80.31 */
	/* access: OP */
	u_int8_t dir;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - BW of the corresponding local port. Valid only if the corresponding bit at local_port_bitmap is set (1).
The units of the BW are determined by Table 986, "PBWC - Port BW Configuration Register Layout," on page 1059.

 */
	/* 0x90.0 - 0x90.31 */
	/* access: RO */
	u_int32_t *bw_record;
};

/* Description -   */
/* Size in bytes - 80 */
struct reg_access_gpu_pcam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups
0: RegID_0x5000_to_0x507F
1: RegID_0x5080_to_50FF
Values 2-255 are Reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t access_reg_group;
	/* Description - Reserved for non-planarized port.
Features and access regs will be presented according to:
0: aggregated_port_access
1: plane_port_access */
	/* 0x0.8 - 0x0.8 */
	/* access: OP */
	u_int8_t pl_op;
	/* Description - Feature list mask index: 
0: enhanced_features 
Values 1 - 255 are Reserved */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t feature_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported port's access register bitmaks. Based on access_reg_group index.
When bit is set , The register is supported in the device. 
When access_reg_group == 0 :
Bit_0: 0x5000 
Bit_1: 0x5001 (PCAP)
Bit_2: 0x5002 (PMLP)
Bit_3: 0x5003 (PMTU)
Bit_4: 0x5004 (PTYS)
Bit_127: 0x507F (PCAM)
 */
	/* 0x8.0 - 0x14.31 */
	/* access: RO */
	u_int32_t port_access_reg_cap_mask[4];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Supported port's enhanced features. Based on feature_group index.
When bit is set, The feature is supported in the device:
Bit 0: PPCNT_counter_group_Phy_statistical_counter_group 
Bit 1 - PPCNT_counter_group_Discard_counter_group
Bit 9: PFCC - support of stall mask and global rx,tx mask. 
Bit 10: PMCR - support of tx_disable override.
Bit 11: PPCNT_counter_group - IB Extended port counter group
Bit 12: PPCNT_Extended_Ethernet_group - tx packet size histograms
Bit 13: PTYS_extended_Ethernet_support
Bit 14: PMAOS_reset_toggle_support
Bit 15: Set_Module_low_power_supported 
Bit 16: Module_power_optimization_is_supported_in_PPSC
Bit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)
Bit 18: PPCNT_Extended_Ethernet_group_icrc_counter
Bit 19: cm2_en_is_supported_in_PCAP
Bit 20: time_tolink_up_is_supported_in_PDDR
Bit 21: gearbox_die_num_field_is_supported_in_PMDR
Bit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability bits are supported in PCMR
Bit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLM
Bit 25: PTYS_allow_both_extended_and_legacy_protocol_masks
Bit 26: PPCNT_eth_per_tc_cong_group_supported
Bit 27: pnat_sup_host - the device supports pnat = 2 (host) when set to '1'
Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in PPCNT when set to '1'
Bit 29: pbmc_port_shared_buffer - supported in PBMC.
Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per window
Bit 32: PDDR_ext_eth_proto_support
Bit 41: PMAOS - support of "opertional_notifcation" field
Bit 42: PRBS_polarity_support - support of polarity bits in PPTT and PPRT
Bit 43: PDDR_register_is_supported
Bit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported.
Bit 45: force_down - supported in PAOS reg.
Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP.
Bit 51: ppcnt_symobl_ber
Bit 52: shp_pbmc_pbsr_support
Bit 54: ppcnt_effective_error_counter
Bit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLM
Bit 57: PMECR_option_to_not_generate_events_upon_PMLP_set
Bit 64: Local_port_MSB - bits [9:8] supported
Bit 65: PDDR_moule_latched_info_page_supported
Bit 66: PDDR_module_info_ext_supported
Bit 70: SLTP_tx_policy_supported
Bit 71: pmcr_capability_bits_supported
Bit 72: pmtu_max_admin_mtu_supported
Bit 73: PPCNT_grp_profile_supported
Bit 77: PPCNT.physical_layer_counters_RS_FEC_8_lanes_supported
Bit 85: PPCNT.counters_cap
Bit 86: SLTP.lane_broadcast_supported
Bit 87: PMMP.apply_im_supported
Bit 91: SLRG.all_lanes_supported
Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported
Bit 93: PPBMP_clr_supported
Bit 94: PIPG.dic1_1g_supported
Other bits are reserved */
	/* 0x28.0 - 0x34.31 */
	/* access: RO */
	u_int32_t feature_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_gpu_pcap_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - port_capability_mask[95:80] is supported if set to '1'. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t cm2_en;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Sets the PortInfoCapabilityMask:
Specifies the supported capabilities of this node. A bit set to 1 for affirmation of supported capability.
port_capability_mask[127:96] is mapped to CapabilityMask in PortInfo MAD.
port_capability_mask[95:80] is mapped to CapabilityMask2 in PortInfo MAD.


 */
	/* 0x4.0 - 0x10.31 */
	/* access: RW */
	u_int32_t port_capability_mask[4];
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_gpu_pddr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Supported only when indicated by PCAM 
0: Network_port
1: Near_End_Port - (For Retimer/Gearbox - Host side)
2: Internal_IC_LR_Port 
3: Far_End_Port - (For Retimer/Gearbox - Line side)
Other values are reserved. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0: Local_port_number
1: IB_port_number
3: Out_of_band_or_PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - page select index:
0: Operational_info_page
1: Troubleshooting_info_page
2: Phy_info_page
3: Module_info_page
6: link_down_info
9: Module_latched_flag_info_page */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t page_select;
	/* Description - Module info extended configurations.
resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power, tx_power_high_th, tx_power_low_th in module info page
0: dbm
1: uW */
	/* 0x4.29 - 0x4.30 */
	/* access: OP */
	u_int8_t module_info_ext;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Table 669, "Operation Info Page Layout," on page 695
Table 705, "Troubleshooting info Page layout," on page 746
Table 697, "Phy Info Page Layout," on page 712
Table 703, "Module Info Page Layout," on page 733
Table 699, "Link Down Info Page layout," on page 727
Table 717, "Module Latched Flag Info Page Layout," on page 764
 */
	/* 0x8.0 - 0xfc.31 */
	/* access: RO */
	union reg_access_gpu_pddr_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_pevnt_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The local_port RX is contained.
RX containd - When a packet had a corruption, and is discarded. the port which detect the error 'contains' it by stopping the traffic. */
	/* 0x4.0 - 0x4.0 */
	/* access: RO */
	u_int8_t rx_cont;
	/* Description - The local_port TX is contained.
TX containd - When a packet had a corruption, and is discarded. the port which detect the error 'contains' it by stopping the traffic. */
	/* 0x4.1 - 0x4.1 */
	/* access: RO */
	u_int8_t tx_cont;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_gpu_pguid_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - System GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x4.0 - 0x10.31 */
	/* access: RO */
	u_int32_t sys_guid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Node GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x14.0 - 0x20.31 */
	/* access: RO */
	u_int32_t node_guid[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Port GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x24.0 - 0x30.31 */
	/* access: RO */
	u_int32_t port_guid[4];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Allocated GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x34.0 - 0x40.31 */
	/* access: RO */
	u_int32_t allocated_guid[4];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_plib_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - In IB port: InfiniBand port remapping for local_port
In Ethernet port: Label port remapping for local_port
Note: ib_port number can only be updated when a port admin state is DISABLED. */
	/* 0x0.0 - 0x0.9 */
	/* access: RW */
	u_int16_t ib_port;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Valid only for Ethernet Switches. 
Label split mapping for local_port */
	/* 0x4.0 - 0x4.3 */
	/* access: RW */
	u_int8_t split_num;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pltc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - for set operation, lane bitmask
for query operation, one-hot key */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t lane_mask;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0: Local_port_number
1: IB_port_number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0x0 - no tx precoding available / no override capabilty

Bit 0- tx precoding override possible via local_tx_precoding_admin field
Bit 1- rx precoding override possible via local_rx_precoding_admin field */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t precoding_cap_mask;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 0 - auto
1 - force Tx precoding
2 - force Tx without precoding */
	/* 0x8.0 - 0x8.1 */
	/* access: RW */
	u_int8_t local_tx_precoding_admin;
	/* Description - Rx configuration override for 100g Pam4 per lane protocols.
0 - auto
1 - Rx precoding enabled. 
if negotiated, request Tx precoding from peer.
2 - Rx precoding disabled. 
if negotiated, request no Tx precoding from peer */
	/* 0x8.16 - 0x8.17 */
	/* access: RW */
	u_int8_t local_rx_precoding_admin;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - 0 - unknown / no active link
1 - Tx precoding enabled.
2 - Tx precoding disabled. */
	/* 0xc.0 - 0xc.1 */
	/* access: RO */
	u_int8_t local_tx_precoding_oper;
	/* Description - Rx precoding operational mode
0 - unknown / no active link
1 - Rx precoding enabled. 
2 - Rx precoding disabled. */
	/* 0xc.16 - 0xc.17 */
	/* access: RO */
	u_int8_t local_rx_precoding_oper;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pmaos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module state (reserved while admin_status is disabled):
0: initializing
1: plugged_enabled
2: unplugged
3: module_plugged_with_error - (details in error_type).
5: unknown */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - Module administrative state (the desired state of the module):
1: enabled
2: disabled_by_configuration
3: enabled_once - if the module is active and then unplugged, or module experienced an error event, the operational status should go to "disabled" and can only be enabled upon explicit enable command.

Note - To disable a module, all ports associated with the port must be disabled first.
 */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t admin_status;
	/* Description - Module number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module Reset toggle
NOTE: setting reset while module is plugged-in will result in transition of oper_status to initialization. */
	/* 0x0.31 - 0x0.31 */
	/* access: OP */
	u_int8_t rst;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event Generation on operational state change:
0: Do_not_generate_event
1: Generate_Event
2: Generate_Single_Event
Not supported by secondary ASICs. */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t e;
	/* Description - Module error details:
0x0: Power_Budget_Exceeded
0x1: Long_Range_for_non_MLNX_cable_or_module
0x2: Bus_stuck - (I2C Data or clock shorted)
0x3: bad_or_unsupported_EEPROM
0x4: Enforce_part_number_list
0x5: unsupported_cable
0x6: High_Temperature
0x7: bad_cable - (Module/Cable is shorted)
0x8: PMD_type_is_not_enabled - (see PMTPS)
0xc: pcie_system_power_slot_Exceeded

[DWIP] 0xf: Boot_error
[DWIP] 0x10: Recovery_error
[DWIP] 0x11: Submodule_failure
Valid only when oper_status = 4'b0011 */
	/* 0x4.8 - 0x4.12 */
	/* access: RO */
	u_int8_t error_type;
	/* Description - This notification can occur only if module passed initialization process
0x0: No notifications.
0x1: Speed degradation - the module is not enabled in its full speed due to incompatible transceiver/cable 
Valid only when oper_status = 4'b0001. */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t operational_notification;
	/* Description - When in multi ASIC module sharing systems,
This flag will be asserted in case primary and secondary FW versions are not compatible. */
	/* 0x4.28 - 0x4.28 */
	/* access: RO */
	u_int8_t rev_incompatible;
	/* Description - Indicates whether the ASIC serves as a the modules secondary (=1) or primary (=0) device. */
	/* 0x4.29 - 0x4.29 */
	/* access: RO */
	u_int8_t secondary;
	/* Description - Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.
Not supported by secondary ASICs. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t ee;
	/* Description - Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t ase;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_pmcr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Valid for CMIS modules.
error code response on override values.
0x0: ConfigUndefined
0x1: ConfigSuccess
0x2: ConfigRejected
0x3: ConfigRejectedInvalidAppSel
0x4: ConfigRejectedInvalidDataPath
0x5: ConfigRejectedInvalidSI
0x6: ConfigRejectedLanesInUse
0x7: ConfigRejectedPartialDataPath
0xC: ConfigInProgress */
	/* 0x0.8 - 0x0.11 */
	/* access: RO */
	u_int8_t error_code_response;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Valid only for CMIS (QSFP-DD / SFP-DD / OSFP) compliant modules.
If Control Set 1 not implemented or non CMIS module ignore field.
0 - Auto (default)
1 - Use Control Set 0
2 - Use Control Set 1 */
	/* 0x0.24 - 0x0.25 */
	/* access: INDEX */
	u_int8_t cs_sel;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module CDR override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t cdr_override_cntl;
	/* Description - Module TX and RX override control capability.
Bit 0 - RX CDR control is possible
Bit 0 - TX CDR control is possible */
	/* 0x4.2 - 0x4.3 */
	/* access: RO */
	u_int8_t cdr_override_cap;
	/* Description - Valid only in case CDR is configured to override mode by cdr_override_cntl: 
0 - RX OFF, TX OFF
1 - RX ON , TX OFF
2 - RX OFF, TX ON
3 - RX ON, TX ON */
	/* 0x4.8 - 0x4.11 */
	/* access: RW */
	u_int8_t cdr_override_value;
	/* Description - In HCA, valid based on PCAM feature capabilities. 
Module TX_DISABLE override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0x4.16 - 0x4.17 */
	/* access: RW */
	u_int8_t tx_disable_override_cntl;
	/* Description - Valid only in case TX_DISABLE is configured to override mode by tx_disable_override_cntl: 
0 - TX_DISABLE is low (i.e. TX is enabled)
1 - TX_DISABLE is high (i.e. TX is disabled) */
	/* 0x4.24 - 0x4.25 */
	/* access: RW */
	u_int8_t tx_disable_override_value;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Module RX amplitude override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0x8.0 - 0x8.1 */
	/* access: RW */
	u_int8_t rx_amp_override_cntl;
	/* Description - Module rx_amp override control capability. */
	/* 0x8.2 - 0x8.2 */
	/* access: RO */
	u_int8_t rx_amp_override_cap;
	/* Description - Valid only in case RX amplitude is configured to override mode by rx_amp_override_cntl */
	/* 0x8.8 - 0x8.11 */
	/* access: RW */
	u_int8_t rx_amp_override_value;
	/* Description - Module rx_amp bitmask of allowed values. */
	/* 0x8.12 - 0x8.15 */
	/* access: RO */
	u_int8_t rx_amp_override_value_cap;
	/* Description - Valid only in case RX _LOS is configured to override mode by rx_los_override_admin */
	/* 0x8.16 - 0x8.17 */
	/* access: RW */
	u_int8_t rx_los_override_cntl;
	/* Description - Module RX_LOS override control capability. */
	/* 0x8.18 - 0x8.18 */
	/* access: RO */
	u_int8_t rx_los_override_cap;
	/* Description - Module RX _LOS override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0x8.24 - 0x8.25 */
	/* access: RW */
	u_int8_t rx_los_override_admin;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Module RX emphasis override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0xc.0 - 0xc.1 */
	/* access: RW */
	u_int8_t rx_emp_override_cntl;
	/* Description - Module rx_emp override control capability. */
	/* 0xc.2 - 0xc.2 */
	/* access: RO */
	u_int8_t rx_emp_override_cap;
	/* Description - For CMIS modules, pre emphasis equalization value.
For SFF modules, emphasis equalization value.
Valid only in case RX emphasis is configured to override mode by rx_emp_override_cntl */
	/* 0xc.8 - 0xc.11 */
	/* access: RW */
	u_int8_t rx_emp_override_value;
	/* Description - Module rx_emp max allowed values. */
	/* 0xc.12 - 0xc.15 */
	/* access: RO */
	u_int8_t rx_emp_override_value_cap;
	/* Description - Module RX emphasis override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0xc.16 - 0xc.17 */
	/* access: RW */
	u_int8_t rx_post_emp_override_cntl;
	/* Description - Module rx_post_emp override control capability. */
	/* 0xc.18 - 0xc.18 */
	/* access: RO */
	u_int8_t rx_post_emp_override_cap;
	/* Description - Valid for CMIS modules only.
Post emphasis equalization value.
Valid only in case RX emphasis is configured to override mode by rx_post_emp_override_cntl */
	/* 0xc.24 - 0xc.27 */
	/* access: RW */
	u_int8_t rx_post_emp_override_value;
	/* Description - Module rx_post_emp max allowed values. */
	/* 0xc.28 - 0xc.31 */
	/* access: RO */
	u_int8_t rx_post_emp_override_value_cap;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Module TX equalization override control:
0 - Auto (default)
1 - Keep the module configuration
2 - Override */
	/* 0x10.0 - 0x10.1 */
	/* access: RW */
	u_int8_t tx_equ_override_cntl;
	/* Description - Module TX equalization override control capability. */
	/* 0x10.2 - 0x10.2 */
	/* access: RO */
	u_int8_t tx_equ_override_cap;
	/* Description - Valid only in case TX equalization is configured to override mode by tx_equ_override_cntl. */
	/* 0x10.8 - 0x10.11 */
	/* access: RW */
	u_int8_t tx_equ_override_value;
	/* Description - Module tx_eq max allowed values. */
	/* 0x10.12 - 0x10.15 */
	/* access: RO */
	u_int8_t tx_equ_override_value_cap;
	/* Description - 0 - disable adaptive Tx Equailization
1 - enable adaptive Tx equalization
Valid only in case TX equalization is configured to override mode by tx_adaptive_override_cntrl. */
	/* 0x10.17 - 0x10.17 */
	/* access: RW */
	u_int8_t tx_adaptive_override_value;
	/* Description - Module adaptive tuning flow override control:
0 - Auto (default)
1 - Keep the module configuration
2 - override */
	/* 0x10.24 - 0x10.25 */
	/* access: RW */
	u_int8_t tx_adaptive_override_cntrl;
	/* Description - Module TX adaptive tuning flow override control capability. */
	/* 0x10.26 - 0x10.26 */
	/* access: RO */
	u_int8_t tx_adaptive_override_cap;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Module Application select override control:
0 - Auto (default)
1 - Use Module's Default application value
2 - Override */
	/* 0x18.0 - 0x18.1 */
	/* access: RW */
	u_int8_t ap_sel_override_cntrl;
	/* Description - Application Select from the applications list advertised by the module. Up to 15 applications available.

Values range from 1 to 15.

Note: application can be set with default SI values defined by the module or SI defined by the host */
	/* 0x18.8 - 0x18.11 */
	/* access: RW */
	u_int8_t ap_sel_override_value;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_gpu_pmlp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: unmap_local_port
1: x1 - lane 0 is used
2: x2 - lanes 0,1 are used
4: x4 - lanes 0,1,2 and 3 are used
8: x8 - lanes 0-7 are used

Other - reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t width;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Module lane mapping: 
0 - Local to Module mapping include module lanes mapping
1 - Local to Module mapping only, without lane mapping

When this operational is set ('1'), the following fields are ignored in SET command and should return the value "0" in GET commands: 
PMLP.rxtx
PMLP.lane<i>_module_mapping.tx_lane
PMLP.lane<i>_module_mapping.rx_lane */
	/* 0x0.28 - 0x0.28 */
	/* access: OP */
	u_int8_t m_lane_m;
	/* Description - Use different configuration for RX and TX.
If this bit is cleared, the TX value is used for both RX and TX. When set, the RX configuration is taken from the separate field. This is to enable backward compatible implementation. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t rxtx;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module SerDes for lane <i>
Up to 8 SerDeses in a module can be mapped to a local port. */
	/* 0x4.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_gpu_lane_2_module_mapping_ext lane_module_mapping[8];
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_gpu_pmmp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set will keep eeprom_override values after plug out event */
	/* 0x0.0 - 0x0.0 */
	/* access: RW */
	u_int8_t sticky;
	/* Description - When set, override will be configured immediately without PMAOS toggle requirement if supported.
for list supported overrides see eeprom_override description.
supported if PCAM.bit 87 set */
	/* 0x0.1 - 0x0.1 */
	/* access: WO */
	u_int8_t apply_im;
	/* Description - Module number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Override/ignore EEPROM advertisement properties bitmask: 
Bit 0: Override_cable_protocols_and_technology_for_QSFP
Bit 1: Override_cable_protocols_and_technology_for_SFP
Bit 2: Ignore_Power_Class - set high power
Bit 3: Override_Cable_Length 
Bit 4: Override_Attenuation
Bit 8: Set_Module_to_Low_Power
Bit 9: Override_cable_protocols_and_technology_for_CMIS - based modules QSFP-DD/ OSFP/ DSFP/ SFP-DD
Bit 11: Override_module_type

Supported overrides with apply_im is Bit 8.
rest of overrides will be applied only after PMAOS toggle. */
	/* 0x4.0 - 0x4.15 */
	/* access: RW */
	u_int16_t eeprom_override;
	/* Description - Write Mask bit (negative polarity):
0 - allow write
1 - ignore write
On write commands, indicates which of the bits from eeprom_override field are updated.
Reserved on read operations. */
	/* 0x4.16 - 0x4.31 */
	/* access: WO */
	u_int16_t eeprom_override_mask;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Protocol technology override for QSFP cable or CMIS based cable (QSFP-DD/OSFP)
Valid only when the protocols and technology for QSFP is overridden as indicated by eeprom_override
Table 529, "PMMP - QSFP Protocol Bytes Override Layout," on page 544
Table 533, "PMMP - CMIS Protocol Bytes Override Layout," on page 549 */
	/* 0x8.0 - 0x10.31 */
	/* access: RW */
	union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext qsfp_cable_protocol_technology;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Valid only when the protocols and technology is overridden as indicated by eeprom_override
Table 531, "PMMP - SFP Protocol Bytes Override Layout," on page 547 */
	/* 0x14.0 - 0x1c.31 */
	/* access: RW */
	union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext sfp_cable_protocol_technology;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Length of cable assembly, units of 1 m for non CMIS cables.

for CMIS cables, represents cable length field:
bits 6:7 represent cable_length_multiplier for calculating cable length
00 - 0.1 multiplier (0.1 to 6.3m)
01- 1 multiplier (1 to 63m)
10 - 10 multiplier (10 to 630m)
11 - 100 multiplier (100 to 6300m)

Valid only when the cable length is overridden as indicated by eeprom_override. */
	/* 0x20.0 - 0x20.7 */
	/* access: RW */
	u_int8_t cable_length;
	/* Description - 0: passive_copper_cable
1: active_copper_cable
2: Liner_far_end_equlized_copper
3: Linear_full_equlized_copper
4: Linear_optical_module - Direct Drive
5: active_optical_module
6: on_board_retimer_over_transceiver */
	/* 0x20.8 - 0x20.11 */
	/* access: RW */
	u_int8_t module_type;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Valid only when the attenuation is overridden as indicated by eeprom_override.
Attenuation - total channel attenuation @ 5GHz in db. */
	/* 0x24.0 - 0x24.7 */
	/* access: RW */
	u_int8_t attenuation_5g;
	/* Description - Valid only when the attenuation is overridden as indicated by eeprom_override.
Attenuation - total channel attenuation @ 7GHz in db. */
	/* 0x24.8 - 0x24.15 */
	/* access: RW */
	u_int8_t attenuation_7g;
	/* Description - Valid only when the attenuation is overridden as indicated by eeprom_override.
Attenuation - total channel attenuation @ 12GHz in db. */
	/* 0x24.16 - 0x24.23 */
	/* access: RW */
	u_int8_t attenuation_12g;
	/* Description - Valid only when the attenuation is overridden as indicated by eeprom_override.
Attenuation - total channel attenuation @ 25GHz in db. */
	/* 0x24.24 - 0x24.31 */
	/* access: RW */
	u_int8_t attenuation_25g;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Valid only when the attenuation is overridden as indicated by eeprom_override.
Attenuation - total channel attenuation @ 53GHz in db. */
	/* 0x28.8 - 0x28.15 */
	/* access: RW */
	u_int8_t attenuation_53g;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_gpu_pmpd_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - Diagnostic data not supported
1 - Normal mission mode. 
2 - PRBS checker is not locked. 
3 - PRBS checker is locked. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - clear counters */
	/* 0x0.4 - 0x0.4 */
	/* access: OP */
	u_int8_t cl;
	/* Description - Module lane number */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane;
	/* Description - Host or Media lanes
0 - Media lanes
1 - Host lanes */
	/* 0x0.12 - 0x0.12 */
	/* access: INDEX */
	u_int8_t host_media;
	/* Description - module to access */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Bits Errors count capability */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t errors_cap;
	/* Description - BER measure capability */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t ber_cap;
	/* Description - SNR measure capability */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t snr_cap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This counter provides information on the total amount of prbs traffic (bits) received on module's side. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t prbs_bits_high;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - This counter provides information on the total amount of prbs traffic (bits) received on module's side. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t prbs_bits_low;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - This counter provides information on the total amount of prbs errors detected on module's side. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t prbs_errors_high;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - This counter provides information on the total amount of prbs errors detected on module's side. */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t prbs_errors_low;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - SNR in dB
0 - not supported. */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t measured_snr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - BER = raw_ber_coef*10^(-raw_ber_magnitude) */
	/* 0x18.0 - 0x18.3 */
	/* access: RO */
	u_int8_t ber_coef;
	/* Description - BER = raw_ber_coef*10^(-raw_ber_magnitude) */
	/* 0x18.8 - 0x18.15 */
	/* access: RO */
	u_int8_t ber_magnitude;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pmpr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA 
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Attenuation - total channel attenuation @ 5GHz in db. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t attenuation_5g;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Attenuation - total channel attenuation @ 7GHz in db. 
A 0 value implies that attenuation_5g is used also for 7GHz */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t attenuation_7g;
	/* Description - Attenuation - total channel attenuation @ 53GHz in db.
A 0 value implies that attenuation_5g is used also for 25GHz */
	/* 0x8.16 - 0x8.23 */
	/* access: RW */
	u_int8_t attenuation_53g;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Attenuation - total channel attenuation @ 12GHz in db.
A 0 value implies that attenuation_5g is used also for 12GHz */
	/* 0xc.0 - 0xc.7 */
	/* access: RW */
	u_int8_t attenuation_12g;
	/* Description - Attenuation - total channel attenuation @ 25GHz in db.
A 0 value implies that attenuation_5g is used also for 25GHz */
	/* 0xc.16 - 0xc.23 */
	/* access: RW */
	u_int8_t attenuation_25g;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_gpu_pmpt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - Normal mission mode. 
1 - Module is not connected OR module doesn't support PRBS and diagnostics data
2 - unsupported configuration setting
3 - PRBS Generator only
4 - PRBS Checker only 
5 - PRBS traffic both Checker and Generator
Note: For lock status on PRBS data see PMPD.status */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - Reserved when (le=0 or ls = 0)
Logical lane number mask.
For Get operation One-Hot key (Only one bit set) */
	/* 0x0.4 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane_mask;
	/* Description - Host or Media lanes
0 - Media lanes
1 - Host lanes */
	/* 0x0.12 - 0x0.12 */
	/* access: INDEX */
	u_int8_t host_media;
	/* Description - PRBS inversion is supported */
	/* 0x0.13 - 0x0.13 */
	/* access: RO */
	u_int8_t invt_cap;
	/* Description - PAM4 MSB<-> LSB swapping is supported by the module */
	/* 0x0.14 - 0x0.14 */
	/* access: RO */
	u_int8_t swap_cap;
	/* Description - module index */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Per Lane configuration enable (can be set only if ls = 1):
0 - No per lane configuration
1 - Per lane configurations
When le is cleared, lane index is reserved and all PMPT configurations are taking place on all lanes.
When le is set, configurations are taking place per lane based on lane index
Affects lane indexing for set operations only, ignored for get operations */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t le;
	/* Description - Per Lane configuration support/capability: 
0 - No support of per lane configuration
1 - Support of per lane configuration */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t ls;
	/* Description - Enable PRBS test mode bit:
0 - PRBS is disabled.
1 - PRBS is enabled. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t e;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Supported module's PRBS capability (bitmask)
Bit 0 - PRBS31 (x^31 + x^28 + 1)
Bit 1 - PRBS23 (x^23 + x^18 + 1)
Bit 5 - PRBS7 (x^7 + x^6 + 1)
Bit 6 - PRBS11 (x^11 + x^9 + 1)
Bit 11 - PRBS9 (x^9 + x^5 + 1)
Bit 17 - PRBS13 (x^13 + x^12 + x^2+ x + 1)
Bit 21 - SSPR
Bit 22 - SSPRQ */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t prbs_modes_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Reserved for speeds below 53.125Gb/s (lane_rate_admin < 7):
0 - NRZ test pattern
1 - PAM4 encoding */
	/* 0x8.0 - 0x8.3 */
	/* access: INDEX */
	u_int8_t modulation;
	/* Description - 0 - Access is for both Checker and Generator (Can be used for Set operations only)
1 - Access is for Generator
2 - Access if for Checker
Note: Checker and Generator must be in same rate */
	/* 0x8.4 - 0x8.5 */
	/* access: INDEX */
	u_int8_t ch_ge;
	/* Description - PRBS inversion enable bit, see ivnt_cap:
0 - NO PRBS inversion
1 - PRBS inversion */
	/* 0x8.8 - 0x8.8 */
	/* access: RW */
	u_int8_t invt_admin;
	/* Description - PAM4 MSB<-> LSB swapping enable bit, see swap_cap. 
0 - NO MSB<-> LSB swapping 
1 - MSB <-> LSB swapping */
	/* 0x8.9 - 0x8.9 */
	/* access: RW */
	u_int8_t swap_admin;
	/* Description - See prbs_mode_cap: 
0x0 - PRBS31 (x^31 + x^28 + 1)
0x1 - PRBS23 (x^23 + x^18 + 1)
0x5 - PRBS7 (x^7 + x^6 + 1)
0x6 - PRBS11 (x^11 + x^9 + 1)
0xB - PRBS9 (x^9 + x^5 + 1)
0x11 - PRBS13 (x^13 + x^12 + x^2+ x + 1)
0x15 - SSPR
0x16 - SSPRQ */
	/* 0x8.24 - 0x8.31 */
	/* access: RW */
	u_int8_t prbs_mode_admin;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Per lane rate capability (bitmask)
Bit 0 - 1GE (1.25 Gb/s)
Bit 1 - SDR (2.5 Gb/s) 
Bit 2 - Reserved
Bit 3- 10GE/40GE (10.3125 Gb/s) 
Bit 4- FDR (14.0625 Gb/s) 
Bit 5- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) 
Bit 6- Reserved 
Bit 7- HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) 
Bit 8- NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
Bit 9 - XDR (106.25 Gbd / 212.5Gb/s) */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t lane_rate_cap;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Lane rate be used in PRBS, see lane_rate_cap:
0 - Non selected. 
1 - 1GE (1.25 Gb/s)
2 - SDR (2.5 Gb/s) 
8 - 10GE/40GE (10.3125 Gb/s) 
16 - FDR (14.0625 Gb/s) 
32 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) 
128 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) 
256 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
512 - XDR (106.25 Gbd / 212.5Gb/s)
 */
	/* 0x10.16 - 0x10.31 */
	/* access: RW */
	u_int16_t lane_rate_admin;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pmtm_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - module number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - module_type: 
0: Backplane_with_4_lanes
1: QSFP
2: SFP
3: No_Cage
4: Backplane_with_single_lane
8: Backplane_with_two_lanes
10: Chip2Chip4x
11: Chip2Chip2x 
12: Chip2Chip1x
14: QSFP_DD 
15: OSFP
16: SFP_DD
17: DSFP 
18: Chip2Chip8x
19: Twisted_Pair
20: Backplane_with_8_lanes */
	/* 0x4.0 - 0x4.4 */
	/* access: RW */
	u_int8_t module_type;
	/* Description - Number of module's electrical lanes

NOTE: For SET command, this value should match the module type width in module_type field */
	/* 0x4.8 - 0x4.12 */
	/* access: RW */
	u_int8_t module_width;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pmtu_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Ingress Truncation enable, the admin_mtu is used as truncation:
0: disable
1: enable
Reserved when NICs (NICs use only '0')
Reserved when SwitchX/-2 and IB Switches (use only '0')
Reserved when i_e = 0 or 2
Reserved when GPUNet */
	/* 0x0.0 - 0x0.0 */
	/* access: RW */
	u_int8_t itre;
	/* Description - Ingress/Egress:
0: applies for both ingress and for egress, read from egress
1: applies only for ingress
2: applies only for egress
Reserved when NICs (NICs use only '0')
Reserved when SwitchX/-2 and IB Switches (use only '0')
Reserved when GPUNet */
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t i_e;
	/* Description - Local port[9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number
Not including CPU port */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - [DWIP]:
The protocol which the MTU is applied to. 
0: All protocols that are supported by the device. On get, it will return the value for IBg1
1: IB (gen 1) 
2: NVLink
3: IBg2
4-15: Reserved
Reserved when Eth switches
Reserved when NIC
Note: for GB100 IBg2 is not PoR, Nov 2023 */
	/* 0x0.28 - 0x0.31 */
	/* access: INDEX */
	u_int8_t protocol;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Maximum MTU supported on the port (Read Only).
MTU depends on the port type. When port type (Eth/IB/FC) is configured, the relevant MTU is reported. When the port type is not configured, the minimum between the max_mtu for the different types (Eth/IB/FC) is reported.
Informative:- For GPUNet: IB is used for MADs, thus max MTU is 768B
- NVLink max MTU is 320B */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_mtu;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Administratively configured MTU on the port. Must be smaller or equal to max_mtu.
When IB: configuration is allowed only when port state is down.
When itre=1 then must be at least 128B and granularity is 8B */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t admin_mtu;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Operational MTU. This is the actual MTU configured on the ports. Packets exceeding this size will be dropped.
Note: For NICs and for IB the actual operational MTU is reported which may be smaller than admin_mtu.
For NICs: when PCAM.max_admin_mtu capability is set then oper_mtu will be the max of all admin_mtu */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t oper_mtu;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_ppaos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port extended down status:
0: regular_operation - (port down/up according to PAOS) 
1: phy_test_mode
phy test mode can be valid only when PAOS.admin_status=2 and PAOS.oper_status=2 (i.e port is down). */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t phy_test_mode_status;
	/* Description - For HCA supported only when indicated by PCAM 
0 - Network Port
1 - Near-End Port (For Retimer/Gearbox - Host side)
2 - Internal IC LR Port 
3 - Far-End Port (For Retimer/Gearbox - Line side)
Other values are reserved. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Port extended administrative down status:
0: regular_operation (port down/up according to PAOS) 
1: phy_test_mode 

The phy test mode (1) can be set only when PAOS.admin_status=2 (i.e port configuration is down). */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t phy_test_mode_admin;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - For HCA: must always be 0.
Switch partition ID with which to associate the port.
Switch partitions are numbered from 0 to 7 inclusively.
The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query. */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t swid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - rx phy status:
0: rx_phy_down
1: rx_phy_up
2: rx_phy_down_by_command

Note: The phy up indication is according to protocol (up == align_status=true)
i.g. In PRBS test mode phy up is when PRB is lock (up== prbs lock) */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t phy_status;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x4.4 - 0x4.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - rx phy port admin. Controls phy entities operational port status.
valid for port_type <> '0'.
to operate link status for port_type '0' use PAOS.admin_status.
0: rx_phy_down
1: rx_phy_up
 */
	/* 0x4.8 - 0x4.11 */
	/* access: RW */
	u_int8_t phy_status_admin;
	/* Description - When set, indicates that ports trace is DC coupled.
Enabling test mode in case of DC coupled port is allowed only when setting dc_cpl_allow and printing warning to user as specified in the description. */
	/* 0x4.28 - 0x4.28 */
	/* access: RO */
	u_int8_t dc_cpl_port;
	/* Description - Relevant only for DC couple ports, Ignored otherwise.
Field must be set when entering test mode, otherwise command is ignored.
When entering test mode in DC couple system the following message must be presented to user:
"Warning: DC couple system must be powered on both sides of the physical link prior to enabling test mode. System may be harmed and product lifetime may be shortened if not ensured." */
	/* 0x4.29 - 0x4.29 */
	/* access: WO */
	u_int8_t dc_cpl_allow;
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_gpu_ppcnt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Performance counter group.
Group 63 indicates all groups (include all per priority/TC/Receive Buffer counters). Only valid on Set() operation with clr bit set.
0x0: IEEE_802_3_Counters
0x1: RFC_2863_Counters
0x2: RFC_2819_Counters
0x3: RFC_3635_Counters
0x5: Ethernet_Extended_Counters
0x6: Ethernet_Discard_Counters 
0x10: Per_Priority_Counters - 
0x11: Per_Traffic_Class_Counters - 
0x12: Physical_Layer_Counters
0x13: Per_Traffic_Class_Congestion_Counters
0x16: Physical_Layer_Statistical_Counters
0x20: InfiniBand_Port_Counters
0x21: InfiniBand_Extended_Port_Counters
0x22: PLR_counters_group
0x23: RS_FEC_Histogram_group
0x25: InfiniBand_pkts_counters
0x26: InfiniBand_General_Counters
0x27: L1_General_Counters */
	/* 0x0.0 - 0x0.5 */
	/* access: INDEX */
	u_int8_t grp;
	/* Description - Supported only when indicated by PCAM on FPGA based NICs:
0 - Network Port
1 - Near-End Port (For Retimer/Gearbox - Host side)
2 - Internal IC LR Port 
3 - Far-End Port (For Retimer/Gearbox - Line side) */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type:
0: Local_port_number
1: IB_port_number
2: host_port_number

Note - pnat=2 is supported for "Per Traffic Class Congestion Counters" and "Per Traffic Class Counters" groups. */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number. 
Note:
when lp_gl = 0, 255 indicates all ports on the device, and is only allowed for Set() operation.
when lp_gl = 1, the index is a global port number
Note: for HCA this bit is not supported, ignored by device */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - For HCA: must be always 0.
Switch partition ID to associate port with.
Switch partitions are numbered from 0 to 7 inclusively.
Switch partition 254 indicates stacking ports.
Switch partition 255 indicates all switch partitions.
Only valid on Set() operation with local_port=255. */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t swid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Priority index for per priority counter sets, valid values: 0-7
For Spectrum-2 and on at tx side range can be 0 .. cap_max_tclass_data-1, see QGCR.tx_cnt_tclass

Traffic class index for per traffic class counter set, valid values: 
For Switches, valid values: 0 .. cap_max_tclass_data-1 

For HCA, valid values: 0.. HCA_CAP.max_tc

Otherwise must be 0.
 */
	/* 0x4.0 - 0x4.4 */
	/* access: INDEX */
	u_int8_t prio_tc;
	/* Description - Supported only when indicated by PCAM: PPCNT_grp_profile_supported (bit 73).
The group profile index. Relevant only if the clr bit is set.
0: Will reset the counter value for all counters in the counter group.
Else: Will point to the corresponding bit-map profile in the PPCGP register. The bit map will return the specific counters that will be reset in the group.

NOTE: The grp_profile index is not supported for the following counters groups:
1. 0x12: Physical_Layer_Counters
2. 0x16: Physical_Layer_Statistical_Counters
3. 0x22: PLR_counters_group
 */
	/* 0x4.5 - 0x4.7 */
	/* access: INDEX */
	u_int8_t grp_profile;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x4.8 - 0x4.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - counters_cap is supported if PCAM.feature_cap_mask bit 85 is set.
When set, each counter in the group will show in bit 0 if the counter is supported.
'0' - not supported
'1' - supported
Note: To know which PPCNT groups are supported per device, listed in table TBD or PCAM fields with PPCNT can be queried. */
	/* 0x4.29 - 0x4.29 */
	/* access: OP */
	u_int8_t counters_cap;
	/* Description - Local Port global variable
0: local_port port 255 = all ports of the device.
1: local_port index indicates Local port number.
for HCA this bit is not supported, ignored by device */
	/* 0x4.30 - 0x4.30 */
	/* access: INDEX */
	u_int8_t lp_gl;
	/* Description - Clear counters. Setting the clr bit will reset the counter value for all counters in the counter group. This bit can be set for both Set() and Get() operation.

NOTE: Clearing a certain group's counters can influence another group's counters value. */
	/* 0x4.31 - 0x4.31 */
	/* access: OP */
	u_int8_t clr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Counter set as described in
Table 441, "Ethernet IEEE 802.3 Counters Group Data Layout," on page 435
Table 443, "Ethernet RFC 2863 Counter Group Data Layout," on page 440
Table 445, "Ethernet RFC 2819 Counter Group Data Layout," on page 443
Table 447, "Ethernet RFC 3635 Counter Group Data Layout," on page 448
Table 449, "Ethernet Extended Counter Group Data Layout," on page 452
Table 452, "Ethernet Discard Counter Group Fields," on page 457
Table 453, "Ethernet Per Priority Group Data Layout," on page 459
Table 457, "Ethernet Per Traffic Class Group data layout," on page 467
Table 469, "Physical Layer Counters Data Layout," on page 478
Table 459, "Ethernet Per Traffic Class Congestion Group data layout," on page 468
Table 473, "Physical Layer Statistical Counters Data Layout," on page 488
Table 465, "InfiniBand PortCounters Attribute Group Data Layout," on page 472
Table 467, "InfiniBand Extended PortCounters Attribute Group Data Layout," on page 474
Table 475, "PLR Counters Data Layout," on page 493 
Table 477, "RS-Histograms Data Layout," on page 495
Table 479, "InfiniBand Packets Counters Data Layout," on page 496
Table 481, "InfiniBand General Counters Data Layout," on page 499 */
	/* 0x8.0 - 0xfc.31 */
	/* access: RO */
	union reg_access_gpu_ppcnt_reg_counter_set_auto_ext counter_set;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_gpu_ppdfd_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of times to transmit the error
Note that by HW the event is triggered 1 time. So FW will trigger the event again and again as fast as possible (roughly every 1uSec).
On a read access, the FW should return ntimes originally configured. */
	/* 0x4.0 - 0x4.15 */
	/* access: RW */
	u_int16_t ntimes;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Poison will set a Phy EBP signal (different type than stomp). 
Reserved when stomp_en = 1.
On a read access, FW should return poison_en originally configured. */
	/* 0x8.0 - 0x8.0 */
	/* access: RW */
	u_int8_t poison_en;
	/* Description - Stomp will set a Phy EBP signal.
On a read access, FW should return stomp_en originally configured. */
	/* 0x8.1 - 0x8.1 */
	/* access: RW */
	u_int8_t stomp_en;
};

/* Description -   */
/* Size in bytes - 80 */
struct reg_access_gpu_pphcr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Support of histogram bins configuration. 
In case this bit is cleared, the port doesn't support configuration of the histogram bins, for the specific hist_type. */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t we;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - 0 - Network Port
1 - Near-End Port (For Retimer/Gearbox - Host side)
3 - Far-End Port (For Retimer/Gearbox - Line side)
Other values are reserved. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type:
0: Local_port_number
1: IB_port_number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port or DataPath number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - 0 - Invalid (Link down / unsupported) 
1 - KP4 RS-FEC (544,514) errors 
2 - LL RS-FEC (271,257) / (272,257+1) errors
3 - KR4 RS-FEC (528,514) errors
4 - PRBS errors */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t active_hist_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: According to active link */
	/* 0x4.0 - 0x4.3 */
	/* access: INDEX */
	u_int8_t hist_type;
	/* Description - Available number of bins 
 */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t num_of_bins;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Lowest measurement/low limit of the histogram 
Example:
In case of hist_type = 1, represent KP4 RS FEC symbol errors(= 0)
In case of hist_type = 2, represent LL RS FEC symbol errors ( = 0)
 */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t hist_min_measurement;
	/* Description - Highest measurement/high limit of the histogram:
Example:
In case of hist_type = 1, represent KP4 RS FEC symbol errors ( = 15)
In case of hist_type = 2, represent LL RS FEC symbol errors ( = 7) */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t hist_max_measurement;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Valid only if we (write enable) = 1 
Ignored on GET 
Write mask for the bin_range array. 
If bit X is set, bin_range [X] write should be execute
Else if bit X is clear, ignored value in written to bin_range [X] */
	/* 0xc.0 - 0xc.15 */
	/* access: WO */
	u_int16_t bin_range_write_mask;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Write to bin_range[x] is applicable only if we = 1 & the corresponding bits in bin_range_write_mask is set.
Mapping of measurement units to a bin.
See Table 753, "PPHCR - Port Phy Bin Range Histogram Configuration Layout," on page 826 */
	/* 0x10.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_gpu_pphcr_bin_range_ext bin_range[16];
};

/* Description -   */
/* Size in bytes - 80 */
struct reg_access_gpu_pplm_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Mission_mode_configuration_and_capabilities
1: Test_mode_configuration_and_capabilities */
	/* 0x0.1 - 0x0.1 */
	/* access: INDEX */
	u_int8_t test_mode;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Supported only when indicated by PCAM 
0: Network_Port
1: Near_End_Port - For Gearbox - Host side
2: Internal_IC_Port 
3: Far_End_Port - For Gearbox - Line side

Other values are reserved.

Using port_type '0' will override all different parts of the link structure.
Using port_type '1' will configure also port_type '2' accordingly and vise versa. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. 
0: Local_port_number
1: IB_port_number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Active FEC (bitmask)
For each enum, a short prefix for tools is presented in the row below.
0: No_FEC 
1: Firecode_FEC
FC_FEC
2: Standard_RS_FEC - RS(528,514)
KR4_FEC
3: Standard_LL_RS_FEC - RS(271,257)
LL_FEC
5: reserved - [Internal]
6: Interleaved_Standard_RS-FEC - (544,514)
Int_KP4_FEC
7: Standard_RS-FEC - (544,514)
KP4_FEC
9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)
ELL_FEC
10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)
Int_ELL_FEC
12: RS-FEC - (544,514) + PLR
13: LL-FEC - (271,257) + PLR
14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] 
15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]
 */
	/* 0xc.0 - 0xc.23 */
	/* access: RO */
	u_int32_t fec_mode_active;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - 10GE/40GE Ethernet FEC override capability bitmask:
Bit 0: No-FEC
Bit 1: Firecode_FEC
Bit 2: Reserved2
Bit 3: Reserved3

 */
	/* 0x10.0 - 0x10.3 */
	/* access: RO */
	u_int8_t fec_override_cap_10g_40g;
	/* Description - 25GE Ethernet FEC override capability bitmask:
Bit 0: No-FEC
Bit 1: Firecode_FEC
Bit 2: RS-FEC
Bit 3: Reserved */
	/* 0x10.4 - 0x10.7 */
	/* access: RO */
	u_int8_t fec_override_cap_25g;
	/* Description - 50GE (2 lanes) Ethernet FEC override capability bitmask:
Bit 0: No-FEC
Bit 1: Firecode_FEC
Bit 2: RS-FEC
Bit 3: Reserved */
	/* 0x10.8 - 0x10.11 */
	/* access: RO */
	u_int8_t fec_override_cap_50g;
	/* Description - 100GE (4 lanes) Ethernet FEC override capability bitmask:
Bit 0: No-FEC
Bit 1: Reserved1
Bit 2: RS-FEC - (528,514)
Bit 3: Reserved3 */
	/* 0x10.12 - 0x10.15 */
	/* access: RO */
	u_int8_t fec_override_cap_100g;
	/* Description - 56GE Ethernet FEC override capability bitmask:
Bit 0: No-FEC
Bit 1: Firecode_FEC
Bit 2: Reserved2
Bit 3: Reserved3 */
	/* 0x10.16 - 0x10.19 */
	/* access: RO */
	u_int8_t fec_override_cap_56g;
	/* Description - RS-FEC correction bypass override capability:
0: NO_correction_bypass
1: RS-FEC_correction_bypass */
	/* 0x10.28 - 0x10.31 */
	/* access: RO */
	u_int8_t rs_fec_correction_bypass_cap;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - 10GE/40GE Ethernet FEC override admin, see 10g_40g_fec_override_cap.
(one-hot setting): 
0: auto_mode - no override
Bit 0: No_FEC
Bit 1: Firecode_FEC

 */
	/* 0x14.0 - 0x14.3 */
	/* access: RW */
	u_int8_t fec_override_admin_10g_40g;
	/* Description - 25GE Ethernet FEC override admin, see 25g_fec_override_cap. (one-hot setting): 
0: auto_mode - no override
Bit 0: No_FEC
Bit 1: Firecode_FEC
Bit 2: RS-FEC

Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value. */
	/* 0x14.4 - 0x14.7 */
	/* access: RW */
	u_int8_t fec_override_admin_25g;
	/* Description - 50GE Ethernet FEC override admin, see 50g_fec_override_cap. (one-hot setting): 
0: auto_mode - no override
Bit 0: No_FEC
Bit 1: Firecode_FEC
Bit 2: RS-FEC

Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value. */
	/* 0x14.8 - 0x14.11 */
	/* access: RW */
	u_int8_t fec_override_admin_50g;
	/* Description - 100GE Ethernet FEC override admin, see 100g_fec_override_cap. (one-hot setting): 
0: auto_mode - no override
Bit 0: No_FEC
Bit 2: RS-FEC */
	/* 0x14.12 - 0x14.15 */
	/* access: RW */
	u_int8_t fec_override_admin_100g;
	/* Description - 56GE Ethernet FEC override admin, see 56g_fec_override_cap. (one-hot setting): 
0: auto_mode - no override
Bit 0: No_FEC
Bit 1: Firecode_FEC */
	/* 0x14.16 - 0x14.19 */
	/* access: RW */
	u_int8_t fec_override_admin_56g;
	/* Description - RS-FEC correction bypass override admin: (one-hot setting): 
0: auto_mode - no override 
1: NO_correction_bypass
2: RS-FEC_correction_bypass */
	/* 0x14.28 - 0x14.31 */
	/* access: RW */
	u_int8_t rs_fec_correction_bypass_admin;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - 200GE FEC override capability bitmask:
Bit 8: Zero_Latency_FEC
Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1
Others bits reserved */
	/* 0x18.0 - 0x18.15 */
	/* access: RO */
	u_int16_t fec_override_cap_200g_4x;
	/* Description - 400GE FEC override capability bitmask:
Bit 8: Zero_Latency_FEC
Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1
All others are reserved */
	/* 0x18.16 - 0x18.31 */
	/* access: RO */
	u_int16_t fec_override_cap_400g_8x;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - 50GE single lane override capability bitmask:
Bit 8: Zero_Latency_FEC
Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1
All others are reserved */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t fec_override_cap_50g_1x;
	/* Description - 100GE over 2 lanes, FEC override capability bitmask:
Bit 8: Zero_Latency_FEC
Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1
All others are reserved */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t fec_override_cap_100g_2x;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - 200GE FEC override admin bitmask (one-hot setting) 
0: Auto_mode
Bit 7: RS_FEC_544_514 - (544,514)
Bit 9: RS_FEC_272_257_plus_1 - (272,257+1) */
	/* 0x20.0 - 0x20.15 */
	/* access: RW */
	u_int16_t fec_override_admin_200g_4x;
	/* Description - 400GE FEC override admin bitmast (one-hot setting): 
0: Auto_mode
Bit7: RS_FEC_544_514
Bit 9: RS_FEC_272_257_plus_1 - (272,257+1) */
	/* 0x20.16 - 0x20.31 */
	/* access: RW */
	u_int16_t fec_override_admin_400g_8x;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - 50GE, 1lanes FEC override admin bitmask (one-hot setting)
0: Auto_mode
Bit 7: RS_FEC_544_514 - (544,514)
Bit 9: RS_FEC_272_257_plus_1 - (272,257+1) */
	/* 0x24.0 - 0x24.15 */
	/* access: RW */
	u_int16_t fec_override_admin_50g_1x;
	/* Description - 100GE, 2 lanes FEC override admin bitmask (one-hot setting):
0: Auto_mode
Bit 7: RS_FEC_544_514 - (544,514)
Bit 9: RS_FEC_272_257_plus_1 - (272,257+1) */
	/* 0x24.16 - 0x24.31 */
	/* access: RW */
	u_int16_t fec_override_admin_100g_2x;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - 400GE, 4 lanes FEC override capability bitmask:
Bit 7: RS_FEC_544_514 - (544,514)
Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1 - (272,257+1)
Other bits Reserved */
	/* 0x28.0 - 0x28.15 */
	/* access: RO */
	u_int16_t fec_override_cap_400g_4x;
	/* Description - 800GE, 8 lanes FEC override capability bitmask:
Bit 7: RS_FEC_544_514 - RS-FEC (544,514)
Bit 8: Reserved
Bit 9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)
Other bits Reserved */
	/* 0x28.16 - 0x28.31 */
	/* access: RO */
	u_int16_t fec_override_cap_800g_8x;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - 100GE, 1 lane FEC override capability bitmask:
Bit 6: Interleaved_RS_FEC_544_514
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1
Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1
Other bits reserved */
	/* 0x2c.0 - 0x2c.15 */
	/* access: RO */
	u_int16_t fec_override_cap_100g_1x;
	/* Description - 200GE, 2 lanes FEC override capability bitmask:
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1
Other bits Reserved */
	/* 0x2c.16 - 0x2c.31 */
	/* access: RO */
	u_int16_t fec_override_cap_200g_2x;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - 400GE, 4 lanes FEC override admin bitmask (one-hot setting):
0: Auto_mode
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1
Other bits Reserved */
	/* 0x44.0 - 0x44.15 */
	/* access: RW */
	u_int16_t fec_override_admin_400g_4x;
	/* Description - 800GE, 8 lanes FEC override admin bitmask (one-hot setting):
0: Auto_mode
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1
Other bits Reserved */
	/* 0x44.16 - 0x44.31 */
	/* access: RW */
	u_int16_t fec_override_admin_800g_8x;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - 100GE, 1 lane FEC override admin bitmask (one-hot setting):
0: Auto_mode
Bit 6: Interleaved_RS_FEC_544_514
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1
Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1
Other bits Reserved */
	/* 0x48.0 - 0x48.15 */
	/* access: RW */
	u_int16_t fec_override_admin_100g_1x;
	/* Description - 200GE, 2 lanes FEC override admin bitmask (one-hot setting):
0: Auto_mode
Bit 7: RS_FEC_544_514
Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1
Other bits Reserved */
	/* 0x48.16 - 0x48.31 */
	/* access: RW */
	u_int16_t fec_override_admin_200g_2x;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_pplr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - For HCA supported only when indicated by PCAM 
0: Network_Port
1: Near-End_Port- (For Retimer/Gearbox - Host side)
2: Internal_IC_LR_Port 
3: Far-End_Port - (For Retimer/Gearbox - Line side)
Other values are reserved. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - operational mode for link configurations for phy_ local_loopback mode.
0 - link will operate in optimal latency performance mode
1 - link will operate in same configurations as operational port.

Note: for FEC override via PPLM register, chosen FEC will be according to the PPLM configuration that was set and this bit will be ignored for FEC purposes */
	/* 0x0.8 - 0x0.8 */
	/* access: OP */
	u_int8_t op_mod;
	/* Description - Apply immediate: When set, the enabled/disabled loopback will be set immediately even if link is active.
Note: Currently supported only for Bit 7: LL_local_loopback. in other loopbacks will be ignored */
	/* 0x0.9 - 0x0.9 */
	/* access: OP */
	u_int8_t apply_im;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Loopback enable - One-hot key.
Bit 0: Phy_remote_loopback
Bit 1: Phy_local_loopback
Bit 2: External_local_loopback
Bit 7: LL_local_loopback


 */
	/* 0x4.0 - 0x4.11 */
	/* access: RW */
	u_int16_t lb_en;
	/* Description - Loopback capability - bitmask
Bit 0: Phy_remote_loopback
Bit 1: Phy_local_loopback - When set the port's egress traffic is looped back to the receiver and the port transmitter is disabled.
Bit 2: External_local_loopback - Enables the port's transmitter to link with the port's receiver using an external loopback connector.
Bit 4: Near_end_digital_loopback - [Internal]
Bit 7: LL_local_loopback - When set the port's egress Link layer traffic is looped back to the receiver. Physical port in this loopback mode is down.

Note - Phy remote loopback can be supported only for lane rate higher than 25Gbuad in the 16nm devices.

 */
	/* 0x4.16 - 0x4.27 */
	/* access: RO */
	u_int16_t lb_cap;
};

/* Description -   */
/* Size in bytes - 36 */
struct reg_access_gpu_pprt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Per Lane configuration enable (can be set only if ls = 1):
0 - No per lane configuration
1 - Per lane configurations
When le is cleared, lane index is reserved and all PPRT configurations are taking place on all lanes.
When le is set, configurations are taking place per lane based on lane index
Affects lane indexing for set operations only, ignored for get operations. */
	/* 0x0.0 - 0x0.0 */
	/* access: OP */
	u_int8_t le;
	/* Description - Per Lane configuration support: 
0 - No support of per lane configuration
1 - Support of per lane configuration */
	/* 0x0.1 - 0x0.1 */
	/* access: RO */
	u_int8_t ls;
	/* Description - Supported only when indicated by PCAM 
0 - Network Port
1 - Near-End Port (For Retimer/Gearbox - Host side)
2 - Internal IC LR Port 
3 - Far-End Port (For Retimer/Gearbox - Line side)
Other values are reserved.
 */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Reserved when (le=0 or ls = 0)
Logical lane number */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number
3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - PRBS MSB <->LSB Swap for PAM4 symbols support
if this bit is cleared - bit 25 ('s') is ignored */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t sw_c;
	/* Description - PRBS MSB <->LSB Swap for PAM4 symbols
0 - No Swap.
1 - Swap MSB <-> LSB. */
	/* 0x0.25 - 0x0.25 */
	/* access: RW */
	u_int8_t sw;
	/* Description - disable mask ignore
If set to 1, the port"s and the cable"s capabilities won"t affect tuning */
	/* 0x0.26 - 0x0.26 */
	/* access: OP */
	u_int8_t dm_ig;
	/* Description - PRBS RX polarity support indication
if this bit is cleared - bit 28 ('p') is ignored */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t p_c;
	/* Description - PRBS RX polarity - NOT gate in PRBS (not Physical lane Polarity)

0 - No polarity inversion.
1 - PRBS RX polarity inversion. */
	/* 0x0.28 - 0x0.28 */
	/* access: RW */
	u_int8_t p;
	/* Description - start tuning:
1 - start RX_tuning based on PRBS pattern 
Note: assuming peer transmitting PRBS. 
cannot be set when prbs_rx_tuning_status = 1 (during tuning) */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t s;
	/* Description - Enable PRBS test mode bit:
0 - PRBS RX is disabled.
1 - PRBS RX is enabled. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t e;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - PRBS capability (bitmask)
Bit 0 - PRBS31 (x^31 + x^28 + 1)
Bit 1 - PRBS23A (x^23 + x^18 + 1)
Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)
Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)
Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)
Bit 5 - PRBS7 (x^7 + x^6 + 1)
Bit 6 - PRBS11 (x^11 + x^9 + 1)
Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)
Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)
Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)
Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)
Bit 11 - PRBS9 (x^9 + x^5 + 1)
Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)
Bit 13 - Square_wave : Non error based tune
Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)
Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)
Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)
Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)
Bit 21- SSPR
Bit 22- SSPRQ
Bit 23- LT frames (KR-startup frames)
Bit 24 - PRBS15 - x^15 + x^14 + 1
Bit 25 - PRBS28 - x^28 + x^25 + 1
Bit 26 - Square wave3 (3ones, 3zeros)
Bit 27 - Square wave13 (13ones, 13zeros)
Bit 28 - Square wave30 (30ones, 30zeros) */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t prbs_modes_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Reserved for speeds below 53.125Gb/s (lane_rate_admin < 13):
0 - NRZ test pattern
1 - PAM4 encoding [interlnal] with gray no precoding
2 - PAM4 with precoding [internal] with gray
3 - PAM4 without gray no precoding
 */
	/* 0x8.0 - 0x8.3 */
	/* access: RW */
	u_int8_t modulation;
	/* Description - See prbs_mode_cap: 
0x0 - PRBS31 (x^31 + x^28 + 1)
0x1 - PRBS23A (x^23 + x^18 + 1)
0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)
0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)
0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)
0x5 - PRBS7 (x^7 + x^6 + 1)
0x6 - PRBS11 (x^11 + x^9 + 1)
0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)
0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)
0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)
0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)
0xB - PRBS9 (x^9 + x^5 + 1)
0xC - IDLEs using scramble58 (x^58+ x^39 + 1)
0xD - Square_wave : Non error based tune 
0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)
0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)
0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)
0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)
0x15 - SSPR
0x16 - SSPRQ
0x17 - LT frames (KR-startup frames)
0x18 - PRBS15 - x^15 + x^14 + 1
0x19 - PRBS28 - x^28 + x^25 + 1
0x1A - Square wave3 (3ones, 3zeros)
0x1B - Square wave13 (13ones, 13zeros)
0x1C - Square wave30 (30ones, 30zeros) */
	/* 0x8.24 - 0x8.31 */
	/* access: RW */
	u_int8_t prbs_mode_admin;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Per lane rate capability (bitmask)
Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)
Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)
Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)
Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)
Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)
Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)
Bit 6- FDR (14.0625 Gb/s) 
Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) 
Bit 8 - 50GE-KR4 (12.89 Gb/s) 
Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) 
Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
Bit 11 - XDR (106.25Gbd / 212.5Gb/s)

Note: PCIe speeds are relevant when pnat = 3 only */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t lane_rate_cap;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Lane rate to be used in PRBS, see lane_rate_cap:
0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)
1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)
2 - QDR (10 Gb/s)
3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)
4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)
5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)
6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)
7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s) 
8 - XDR (106.25Gbd / 212.5Gb/s)
9 - reserved
10 - 1GE (1.25 Gb/s)
11 - XAUI/2.5GE (3.125 Gb/s)
12 - 50GE-KR4 (12.89 Gb/s) 

Note: All lanes must be set to the same rate
Note: PCIe speeds are relevant when pnat = 3 only */
	/* 0x10.16 - 0x10.31 */
	/* access: RW */
	u_int16_t lane_rate_oper;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - PRBS lock on PRBS pattern status for lanes 7-4: 
0 - Not locked
1 - Locked

Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked) */
	/* 0x14.20 - 0x14.23 */
	/* access: RO */
	u_int8_t prbs_lock_status_ext;
	/* Description - PRBS lock on PRBS pattern status for lanes 3-0: 
0 - Not locked
1 - Locked

Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked) */
	/* 0x14.24 - 0x14.27 */
	/* access: RO */
	u_int8_t prbs_lock_status;
	/* Description - Tuning status: 
0 - PRBS mode tuning was not performed.
1 - Performing PRBS mode tuning.
2 - PRBS mode tuning completed.
3 - Signal Detect in progress

Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0. */
	/* 0x14.28 - 0x14.31 */
	/* access: RO */
	u_int8_t prbs_rx_tuning_status;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_gpu_ppsc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - See PCAM.feature_cap_mask bit 16 for support indication: 
Transceiver power optimization:
0 - Disable
1 - Enable */
	/* 0x4.0 - 0x4.0 */
	/* access: RW */
	u_int8_t mod_pwr_opt;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Width reduction power save admin state:
0000: Disable Width Reduction - Force link to full width (Default)
0001: Force Width Reduction - Force link to single lane
0010: Auto - Automatic Width Reduction (based on traffic). */
	/* 0x10.0 - 0x10.3 */
	/* access: RW */
	u_int8_t wrps_admin;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Link actual width:
0000: Full width
0001: Single lane
1111: In transition */
	/* 0x14.0 - 0x14.3 */
	/* access: RO */
	u_int8_t wrps_status;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Link width down threshold, Values: 1%-100%
The BW (In percent) before the link width is moved to single lane */
	/* 0x18.0 - 0x18.7 */
	/* access: RW */
	u_int8_t down_threshold;
	/* Description - Link width up threshold, Values: 1-5 (default 3)
how aggressive/smoothed in response to high BW.
1 - means aggressive response to every BW increase
5 - means smoothened response to every BW increase */
	/* 0x18.16 - 0x18.23 */
	/* access: RW */
	u_int8_t up_threshold;
	/* Description - Valid bit to update the down threshold
if '1' update down_threshold */
	/* 0x18.30 - 0x18.30 */
	/* access: WO */
	u_int8_t down_th_vld;
	/* Description - Valid bit to update the up threshold
if '1' update up_threshold */
	/* 0x18.31 - 0x18.31 */
	/* access: WO */
	u_int8_t up_th_vld;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Speed reduction power save admin state:
0000: Disable Speed Reduction - force link to full speed (Default)
0001: Force Speed Reduction - force link to low speed */
	/* 0x20.0 - 0x20.3 */
	/* access: RW */
	u_int8_t srps_admin;
};

/* Description -   */
/* Size in bytes - 52 */
struct reg_access_gpu_ppslc_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Enable L1 Request
0: L1 Request is disabled on this port
1: L1 Request is enabled on this port
 */
	/* 0x4.0 - 0x4.0 */
	/* access: RW */
	u_int8_t l1_req_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Enable L1 FW Request
0: Only L1 HW mode is supported (thermal throttling is disabled) 
1: support thermal throttling on this port 
Reserved for Switch. */
	/* 0x8.0 - 0x8.0 */
	/* access: RW */
	u_int8_t l1_fw_req_en;
	/* Description - L1 Capability Advertisement
0: Port doesn't support L1
1: Port supports L1 advertisement */
	/* 0x8.4 - 0x8.4 */
	/* access: RW */
	u_int8_t l1_cap_adv;
	/* Description - L1 FW Capability Advertisement
0: Port doesn't support L1 FW
1: Port supports L1 FW advertisement
Reserved for Switch. */
	/* 0x8.8 - 0x8.8 */
	/* access: RW */
	u_int8_t l1_fw_cap_adv;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - [DWIP] [SwitchOnly]:
Ignore Predictor Post Mistake
If the predictor decision is to move to L1 idle, but no traffic arrives, we will ignore the predictor until traffic arrives again
0: don't ignore predictor
1: ignore predictor */
	/* 0xc.30 - 0xc.30 */
	/* access: RW */
	u_int8_t ignore_pred_pm;
	/* Description - [DWIP] [SwitchOnly]:
Predictive Algo Enable
0: Predictive Algo' is disabled
1: Predictive Algo' is enabled

Relevant for Switch Only */
	/* 0xc.31 - 0xc.31 */
	/* access: RW */
	u_int8_t pred_algo_en;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - High Priority Queues Bitmap
for each queue, 
0: Normal queue
1: High priority queue

Note: High priority queues can move to L1 active only when queue is fully empty. Normal queues can move to L1 active as long as the number of bytes within the queue is lower than MPSCR.queue_depth_th

bits 17-31 are reserved */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	u_int32_t hp_queues_bitmap;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - [DWIP]
units of 50 usec minimum value of 50 usec
 */
	/* 0x18.0 - 0x18.9 */
	/* access: RW */
	u_int16_t l1_hw_active_time;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - [DWIP]
units of 50 usec. minimum value of 50 usec
 */
	/* 0x1c.0 - 0x1c.9 */
	/* access: RW */
	u_int16_t l1_hw_inactive_time;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Queue Desire (state) Exit Mode upon traffic arrival
0: Move to L1 Idle immediately 
1: Wait for desire window completion before moving to L1 idle
2: Ignore traffic arrival 

Note: 
For GB100, only index 0-7 are valid. 
For QM-3 only index 0-16 are valid. */
	/* 0x20.24 - 0x34.23 */
	/* access: RW */
	u_int8_t qem[20];
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_gpu_ppsls_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: Port doesn't support L1 fw mode
1: Port supports L1 fw mode
 */
	/* 0x4.16 - 0x4.16 */
	/* access: RO */
	u_int8_t l1_fw_mode_cap;
	/* Description - 0: Port doesn't support L1
1: Port supports L1 
 */
	/* 0x4.18 - 0x4.18 */
	/* access: RO */
	u_int8_t l1_cap;
	/* Description - FW mode remote indication
0: N/A
1: L1 fw mode remote capability is set 
2: L1 fw mode remote request is set 
3: L1 fw mode remote request and capability are set 
Valid only is l1_neg_status = 1 
Reserved when link is down */
	/* 0x4.27 - 0x4.28 */
	/* access: RO */
	u_int8_t fw_mode_remote;
	/* Description - Actual Mode 
0: HW mode
1: FW mode
Valid only is l1_neg_status = 1 
Reserved when link is down
Reserved for Switch. */
	/* 0x4.29 - 0x4.29 */
	/* access: RO */
	u_int8_t fw_mode_act;
	/* Description - FW mode negotiation status
0: L1 fw mode negotiation failed
1: L1 fw mode negotiation succeeded 
Valid only if l1_neg_status = 1 
Reserved when link is down */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t fw_mode_neg_status;
	/* Description - L1 negotiation status
0: L1 negotiation failed (L1 is not supported by both sides)
1: L1 negotiation succeeded (supported on both sides)
Reserved when link is down */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t l1_neg_status;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_gpu_pptt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Per Lane configuration enable (can be set only if ls = 1):
0 - No per lane configuration
1 - Per lane configurations
When le is cleared, lane index is reserved and all PPTT configurations are taking place on all lanes.
When le is set, configurations are taking place per lane based on lane index
Affects lane indexing for set operations only, ignored for get operations */
	/* 0x0.0 - 0x0.0 */
	/* access: OP */
	u_int8_t le;
	/* Description - Per Lane configuration support/capability: 
0 - No support of per lane configuration
1 - Support of per lane configuration */
	/* 0x0.1 - 0x0.1 */
	/* access: RO */
	u_int8_t ls;
	/* Description - For HCA supported only when indicated by PCAM 
0 - Network Port
1 - Near-End Port (For Retimer/Gearbox - Host side)
2 - Internal IC LR Port 
3 - Far-End Port (For Retimer/Gearbox - Line side)
Other values are reserved.
Note: PRBS can be enabled only for two entities that directly connected to each other.
For non MCM and no Retimer/Gearbox only 0 allowed.
For non MCM and with Retimer/Gearbox 2-1 or 3 or 0.
For MCM without Retimer/Gearbox 4-5 or 2 or 0.
For MCM with Retimer/Gearbox 4-5 or 2-1 or 3 or 0.
all the port will be in test mode when PRBS is enabled. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Reserved when (le=0 or ls = 0)
Logical lane number */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number
3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - PRBS MSB <->LSB Swap for PAM4 symbols support
if this bit is cleared - bit 25 ('s') is ignored */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t sw_c;
	/* Description - PRBS MSB <->LSB Swap for PAM4 symbols
0 - No Swap.
1 - Swap MSB <-> LSB. */
	/* 0x0.25 - 0x0.25 */
	/* access: RW */
	u_int8_t sw;
	/* Description - disable mask ignore
If set to 1, the port"s and the cable"s capabilities won"t affect tuning */
	/* 0x0.26 - 0x0.26 */
	/* access: OP */
	u_int8_t dm_ig;
	/* Description - PRBS TX polarity support indication.
if this bit is cleared - bit 28 ('p') is been ignored */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t p_c;
	/* Description - PRBS TX polarity - NOT gate in PRBS (not Physical lane Polarity)
0 - No polarity inversion.
1 - PRBS TX polarity inversion. */
	/* 0x0.28 - 0x0.28 */
	/* access: RW */
	u_int8_t p;
	/* Description - Enable PRBS test mode bit:
0 - PRBS TX is disabled.
1 - PRBS TX is enabled. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t e;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - PRBS capability (bitmask)
Bit 0 - PRBS31 (x^31 + x^28 + 1)
Bit 1 - PRBS23A (x^23 + x^18 + 1)
Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)
Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)
Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)
Bit 5 - PRBS7 (x^7 + x^6 + 1)
Bit 6 - PRBS11 (x^11 + x^9 + 1)
Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)
Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)
Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)
Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)
Bit 11 - PRBS9 (x^9 + x^5 + 1)
Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)
Bit 13 - Square_wave8 (8 ones , 8 zeros)
Bit 14 - Square_wave4 (4 ones , 4zeros)
Bit 15 - Square_wave2 (2 ones , 2zeros)
Bit 16 - Square_wave1 (one , zero)
Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)
Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)
Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)
Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)
Bit 21- SSPR
Bit 22- SSPRQ
Bit 23- LT frames (KR-startup frames)
Bit 24 - PRBS15 - x^15 + x^14 + 1
Bit 25 - PRBS28 - x^28 + x^25 + 1
Bit 26 - Square wave3 (3ones, 3zeros)
Bit 27 - Square wave13 (13ones, 13zeros)
Bit 28 - Square wave30 (30ones, 30zeros)
Bit 29 - PRBS58 (x^58+ x^39 + 1) */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t prbs_modes_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Reserved for speeds below 53.125Gb/s (lane_rate_admin < 13):
0 - NRZ test pattern
1 - PAM4 encoding [interlnal] with gray no precoding
2 - PAM4 with precoding [internal] with gray
3 - PAM4 without gray no precoding
 */
	/* 0x8.0 - 0x8.3 */
	/* access: RW */
	u_int8_t modulation;
	/* Description - See prbs_mode_cap: 
0x0 - PRBS31 (x^31 + x^28 + 1)
0x1 - PRBS23A (x^23 + x^18 + 1)
0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)
0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)
0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)
0x5 - PRBS7 (x^7 + x^6 + 1)
0x6 - PRBS11 (x^11 + x^9 + 1)
0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)
0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)
0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)
0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)
0xB - PRBS9 (x^9 + x^5 + 1)
0xC - IDLEs using scramble58 (x^58+ x^39 + 1)
0xD - Square_wave8 (8 ones , 8 zeros)
0xE - Square_wave4 (4 ones , 4zeros)
0xF - Square_wave2 (2 ones , 2zeros)
0x10 - Square_wave1 (one , zero)
0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)
0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)
0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)
0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)
0x15 - SSPR
0x16 - SSPRQ
0x17 - LT frames (KR-startup frames)
0x18 - PRBS15 - x^15 + x^14 + 1
0x19 - PRBS28 - x^28 + x^25 + 1
0x1A - Square wave3 (3ones, 3zeros)
0x1B - Square wave13 (13ones, 13zeros)
0x1C - Square wave30 (30ones, 30zeros)
0x1D - PRBS58 (x^58+ x^39 + 1) */
	/* 0x8.24 - 0x8.31 */
	/* access: RW */
	u_int8_t prbs_mode_admin;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - When set, PRBS over FEC is supported.
Note: Feature is enabled on all lanes of port */
	/* 0xc.0 - 0xc.0 */
	/* access: RO */
	u_int8_t prbs_fec_cap;
	/* Description - Per lane rate capability (bitmask)
Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)
Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)
Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)
Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)
Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)
Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)
Bit 6- FDR (14.0625 Gb/s) 
Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) 
Bit 8 - 50GE-KR4 (12.89 Gb/s) 
Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) 
Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
Bit 11 - XDR (106.25Gbd / 212.5Gb/s)

Note: PCIe speeds are relevant when pnat = 3 only */
	/* 0xc.16 - 0xc.31 */
	/* access: RO */
	u_int16_t lane_rate_cap;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - When set, PRBS over FEC is enabled for port.
For FEC configuration, set PPLM.test_mode */
	/* 0x10.0 - 0x10.0 */
	/* access: RW */
	u_int8_t prbs_fec_admin;
	/* Description - Lane rate be used in PRBS, see lane_rate_cap:
0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)
1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)
2 - QDR (10 Gb/s)
3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)
4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)
5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)
6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)
7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
8 - XDR (106.25Gbd / 212.5Gb/s)
9 - reserved
10 - 1GE (1.25 Gb/s)
11 - XAUI/2.5GE (3.125 Gb/s)
12 - 50GE-KR4 (12.89 Gb/s)

Note: All lanes must be set to the same rate
Note: PCIe speeds are relevant when pnat = 3 only */
	/* 0x10.16 - 0x10.31 */
	/* access: RW */
	u_int16_t lane_rate_admin;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_prtl_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0: Local_port_number
1: IB_port_number
3: Out_of_band */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number [7:0] */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Support of RTT measurement */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t rtt_support;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Latency measurement accuracy (i,e. max error size). 
accuracy is relative to specific device implementation. 
This field returns the accuracy in nsec resolution. 
 */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t latency_accuracy;
	/* Description - Latency resolution in nsec of round_trip_latency 
 */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t latency_res;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Shall be 0 if not implemented (rtt_support = 0). 
This value represents the intra-ASIC pipeline latency of the physical layer. It is an unsigned 16-bit integer in nsec. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t local_phy_latency;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Shall be 0 if not implemented (rtt_support = 0), if the module is not plugged in or if the information is not available on the plugged module. 
This value represents the module's Datapath pipeline latency.It It is an unsigned 16-bit integer in nsec. */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t local_mod_dp_latency;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Shall be 0 if not implemented (rtt_support = 0). 
This value represents a measurement of the round-trip latency of the link attached to this port. 
It is an unsigned 24-bit integer counting latency_res nsec. 
intervals. 
This value might not be accurate to better than +/- latency_accuracy nsec. 
A value of 0 is valid when implemented, and indicates a latency of up to latency_accuracy nsec. 
round_trip_latency is reset to 0xFFFFFF whenever this port transitions to PAOS.Oper_status = Down. */
	/* 0x10.0 - 0x10.23 */
	/* access: RO */
	u_int32_t round_trip_latency;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_pter_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Error injection status: 
0x0 -Good status
0x2 - No available sources for Error injection
0x3 - Error injection configuration when port is in non operational state (port is neither in UP or TEST MODE)
0x4 - out of range BER setting */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number
 */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Error_page selection: 
0: Injection_of_Phy_Errors
1: Injection_of_Port_Errors */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t error_page;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - error injection page data: 
Table 501, "PTER- Port Transmit Errors Register Phy Level Layout," on page 526
Table 503, "PTER- Port Transmit Errors Register Port Level Fields," on page 527 */
	/* 0x4.0 - 0x1c.31 */
	/* access: RW */
	union reg_access_gpu_pter_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_ptsb_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - SL
For GB100: allowed 0..3
Reserved when type = 0 */
	/* 0x4.0 - 0x4.3 */
	/* access: INDEX */
	u_int8_t sl;
	/* Description - VC (Virtual Channel)
For GB100: allowed 0,1
Reserved when type = 1 */
	/* 0x4.4 - 0x4.7 */
	/* access: INDEX */
	u_int8_t vc;
	/* Description - Pipe
For GB100: allowed 0,1
Reserved when type = 1 */
	/* 0x4.8 - 0x4.11 */
	/* access: INDEX */
	u_int8_t pipe;
	/* Description - Type:
0: NVLink
1: IB */
	/* 0x4.12 - 0x4.15 */
	/* access: INDEX */
	u_int8_t type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Burst send:
Send up to burst_send consecutive packets.
Value of 0 is not supported.
FW will send 1 packet after each other, typically time of 100's of nSec between every 2 packets.
Note that this "allows sending". If there are no packets or no credits then the packets will not be transmitted but the counter will be incremented */
	/* 0x8.0 - 0x8.9 */
	/* access: OP */
	u_int16_t burst_send;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_gpu_ptsr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Tx suspend:
0: Tx enabled (default)
1: Tx disabled */
	/* 0x4.0 - 0x4.0 */
	/* access: RW */
	u_int8_t ts;
};

/* Description -   */
/* Size in bytes - 68 */
struct reg_access_gpu_ptys_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Protocol Mask. Indicates which of the protocol data is valid
Bit 0: InfiniBand
Bit 2: Ethernet */
	/* 0x0.0 - 0x0.2 */
	/* access: INDEX */
	u_int8_t proto_mask;
	/* Description - Valid only when port is mapped to SW controlled module, otherwise ignored. module control can be queried via MMCR register.

0: transmit_not_allowed - Transmitter is not allowed to transmit signal on output
1: transmit_allowed - Transmitter is allowed to transmit signal on output. for enabling transmitter, PAOS.admin_status must be up as well. */
	/* 0x0.3 - 0x0.3 */
	/* access: RW */
	u_int8_t transmit_allowed;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Supported only when indicated by PCAM 
0: Network_Port
1: Near-End_Port - (For Gearbox - Host side)
2: Internal_IC_Port 
3: Far-End_Port - (For Gearbox - Line side)

Other values are reserved. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Valid only when ee_tx_ready is set, otherwise field is ignored.
0: do_not_generate_event
Bit 0: generate_tx_ready_event - When set, PTSE register will generate event when Transmitter is generating valid signal on the line
Bit 1: generate_tx_not_ready_event - when set, PTSE will generate event when the transmitter stopped transmitting after Tx_ready was set.
Note: if both tx_not_ready and tx_ready are set, one toggle event may be received instead of 2 consecutive events of not ready --> ready. */
	/* 0x0.26 - 0x0.27 */
	/* access: RW */
	u_int8_t tx_ready_e;
	/* Description - Event Enable for tx_ready_e.
when bit is not set, tx_teady_e write value will be ignored */
	/* 0x0.28 - 0x0.28 */
	/* access: WO */
	u_int8_t ee_tx_ready;
	/* Description - Auto Negotiation disable capability:
0 - Device does not support AN disable
1 - Device Supports  AN disable */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t an_disable_cap;
	/* Description - Auto Negotiation disable:
0 - Normal operation 
1 - Disable AN.
Note: In Ethernet port, when Disabling AN, the "eth_proto_admin" bit mask must comply to single speed rate set.
In IB port, when Disabling AN, the "ib_proto_admin" bit mask must comply to single speed rate set.
It's recommended to validate the FEC override bits in PPLM when operating with AN. 

 */
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t an_disable_admin;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Port data rate in resolution of 100 Mb/s (data_rate_oper * 100 Mb/s)
Value 0x0 indicates this field is not supported.
 */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t data_rate_oper;
	/* Description - Port maxium data rate in resolution of 1 Gb/s (data_rate_oper * 1 Gb/s)
Value 0x0 indicates this field is not supported.

 */
	/* 0x4.16 - 0x4.27 */
	/* access: RO */
	u_int16_t max_port_rate;
	/* Description - Auto Negotiation status: 
0: Status_is_unavailable
1: AN_completed_successfully 
2: AN_performed_but_failed
3: AN_was_not_performed_link_is_up 
4: AN_was_not_performed_link_is_down */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t an_status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ethernet protocol support.
Extended Ethernet port speed/protocols supported (bitmask):
Bit 0: SGMII_100M
Bit 1: 1000BASE-X / SGMII
Bit 3: 5GBASE-R
Bit 4: XFI / XAUI-1 // 10G
Bit 5: XLAUI-4/XLPPI-4 // 40G 
Bit 6: 25GAUI-1/ 25GBASE-CR / KR 
Bit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 
Bit 8: 50GAUI-1 /50GBASE-CR / KR
Bit 9: CAUI-4 / 100GBASE-CR4 / KR4
Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2 
Bit 11: 100GAUI-1 / 100GBASE-CR / KR
Bit 12: 200GAUI-4 / 200GBASE-CR4/KR4
Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2
Bit 14: Reserved [internal] Placeholder for 200GAUI-1
Bit 15: 400GAUI-8/ 400GBASE-CR8
Bit 16: 400GAUI-4/ 400GBASE-CR4
Bit 17: Reserved [internal] Placeholder for 400GAUI-2
Bit 18: Reserved [internal] Placeholder for 400GAUI-1
Bit 19: 800GAUI-8 / 800GBASE-CR8 / KR8
Bit 31: SGMII_10M
Other - Reserved */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ext_eth_proto_capability;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Ethernet port speed/protocols supported (bitmask)
Bit 31 - 50GBase-KR2
Bit 30 - 50GBase-CR2
Bit 29 - 25GBase-SR
Bit 28 - 25GBase-KR
Bit 27 - 25GBase-CR
Bit 26 - 10GBase-T 
Bit 25 - 1000Base-T
Bit 24 - 100Base-TX
Bit 23 - 100GBase LR4/ER4
Bit 22 - 100GBase KR4
Bit 21 - 100GBase SR4
Bit 20 - 100GBase CR4
Bit 18 - 50GBase-SR2
Bit 16 - 40GBase LR4/ER4
Bit 15 - 40GBase SR4
Bit 14 - 10GBase ER/LR
Bit 13 - 10GBase SR
Bit 12 - 10GBase CR
Bit 10 - 10Base-T
Bit 9 - SGMII_100Base
Bit 7 - 40GBase KR4
Bit 6 - 40GBase CR4
Bit 4 - 10GBase KR
Bit 3 - 10GBase KX4
Bit 2 - 10GBase-CX4
Bit 1 - 1000Base KX
Bit 0 - SGMII */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t eth_proto_capability;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - InfiniBand port speed supported (bitmask)
Bit 0: SDR
Bit 1: DDR
Bit 2: QDR
Bit 3: FDR10
Bit 4: FDR
Bit 5: EDR
Bit 6: HDR
Bit 7: NDR
Bit 8: XDR */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t ib_proto_capability;
	/* Description - ib_link_width <= ib_proto_capability
Bit 0 - 1x
Bit 1 - 2x
Bit 2 - 4x
 */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t ib_link_width_capability;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Ethernet port extended speed/protocols bitmask
NOTE: This field and "eth_proto_admin" are mutual exclusive, meaning that only one of the field can be set on write command. */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t ext_eth_proto_admin;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Ethernet port speed/protocols bitmask */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t eth_proto_admin;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - InfiniBand port speed bitmask */
	/* 0x1c.0 - 0x1c.15 */
	/* access: RW */
	u_int16_t ib_proto_admin;
	/* Description - InfiniBand port link width bitmask
 */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RW */
	u_int16_t ib_link_width_admin;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Ethernet port extended speed/protocols bitmask */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t ext_eth_proto_oper;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Ethernet port speed/protocols bitmask */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t eth_proto_oper;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - InfiniBand port speed bitmask */
	/* 0x28.0 - 0x28.15 */
	/* access: RO */
	u_int16_t ib_proto_oper;
	/* Description - InfiniBand port link width bitmask
 */
	/* 0x28.16 - 0x28.31 */
	/* access: RO */
	u_int16_t ib_link_width_oper;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Connector type indication
0: No_connector_or_unknown 
1: PORT_NONE - None
2: PORT_TP - Twisted Pair
3: PORT_AUI - AUI
4: PORT_BNC - BNC
5: PORT_MII - MII
6: PORT_FIBRE - FIBRE
7: PORT_DA - Direct Attach Copper
8: PORT_OTHER - Other */
	/* 0x2c.0 - 0x2c.3 */
	/* access: RO */
	u_int8_t connector_type;
	/* Description - For active link, Indicates the lane data rate passed per physical lane including the overhead due to FEC.
resolution of 10 Mb/s (lane_rate_oper * 10Mb/s). */
	/* 0x2c.4 - 0x2c.23 */
	/* access: RO */
	u_int32_t lane_rate_oper;
	/* Description - When set and link active, indicates link speed is xdr_2x slow. */
	/* 0x2c.24 - 0x2c.24 */
	/* access: RO */
	u_int8_t xdr_2x_slow_active;
	/* Description - When set, along with ib protocol xdr_2x, XDR_2x slow will be allowed instead of xdr_2x.
Note: in GB100, set by default only with ini and cannot be changed. */
	/* 0x2c.25 - 0x2c.25 */
	/* access: RW */
	u_int8_t xdr_2x_slow_admin;
	/* Description - Ethernet Force mode options when AN disable is set.
0 - auto, keep normal operation
1 - Do Force LT (KR Startup) flow
2 - Do not do LT (KR Startup) flow

Note: Ignored when an_disable_admin is not set
In Ethernet port, when setting force LT flow, the "eth_proto_ext_admin" bit mask must comply to single speed rate set. */
	/* 0x2c.28 - 0x2c.29 */
	/* access: RW */
	u_int8_t force_lt_frames_admin;
	/* Description - 0 - device does not support Force LT (KR Startup) flow
1 - device supports Force LT (KR Startup) flow

Note: Ignored when an_disable_admin is not set */
	/* 0x2c.30 - 0x2c.30 */
	/* access: RO */
	u_int8_t force_lt_frames_cap;
	/* Description - capability for XDR_2x slow is support (200G) */
	/* 0x2c.31 - 0x2c.31 */
	/* access: RO */
	u_int8_t xdr_2x_slow_cap;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_gpu_pude_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port operational state:
0001 - up
0010 - down
0100 - down by port failure (transitioned by the hardware)
 */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - Port administrative state (the desired state of the interface):
0001 - up
0010 - down by configuration
0011 - up once - if the port goes up and then down, the operational status should go to "down by port failure" and can only go back up upon explicit command
0100 - disabled by system 
0110 - sleep */
	/* 0x0.8 - 0x0.11 */
	/* access: RO */
	u_int8_t admin_status;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - For HCA: must  always be 0.
Switch partition ID with which to associate the port.
Switch partitions are numbered from 0 to 7 inclusively.
Switch partition 254 indicates stacking ports.
Switch partition 255 indicates all switch partitions.
Note: While external ports uses unique local port numbers (and thus swid is redundant), router ports use the same local port number where swid is the only indication for the relevant port. */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t swid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - IB Port Physical link state:
0: N/A
1: Sleep
2: Polling
3: Disabled
4: PortConfigurationTraining
5: LinkUp

6-15: reserved
[internal] Note: Supported from XDR devices onwards */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t physical_state_status;
	/* Description - IB or NVLink Port Logical link state:
0: N/A
1: Down
2: Init
3: Arm
4: Active */
	/* 0x4.16 - 0x4.18 */
	/* access: RO */
	u_int8_t logical_state_status;
	/* Description - Opcde of link down reason for local
0: No_link_down_indication
1: Unknown_reason
2: Hi_SER_or_Hi_BER
3: Block_Lock_loss
4: Alignment_loss
5: FEC_sync_loss
6: PLL_lock_loss
7: FIFO_overflow
8: false_SKIP_condition
9: Minor_Error_threshold_exceeded
10: Physical_layer_retransmission_timeout
11: Heartbeat_errors
12: Link_Layer_credit_monitoring_watchdog
13: Link_Layer_integrity_threshold_exceeded
14: Link_Layer_buffer_overrun
15: Down_by_outband_command_with_healthy_link
16: Down_by_outband_command_for_link_with_hi_ber
17: Down_by_inband_command_with_healthy_link
18: Down_by_inband_command_for_link_with_hi_ber
19: Down_by_verification_GW
20: Received_Remote_Fault 
21: Received_TS1
22: Down_by_management_command
23: Cable_was_unplugged
24: Cable_access_issue 
25: Thermal_shutdown 
26: Current_issue 
27: Power_budget
28: Fast_recovery_raw_ber
29: Fast_recovery_effective_ber
30: Fast_recovery_symbol_ber
31: Fast_recovery_credit_watchdog
32: Peer_side_down_to_sleep_state
33: Peer_side_down_to_disable_state
34: Peer_side_down_to_disable_and_port_lock
35: Peer_side_down_due_to_thermal_event
36: Peer_side_down_due_to_force_event
37: Peer_side_down_due_to_reset_event */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t local_reason_opcode;
};

/* Description -   */
/* Size in bytes - 200 */
struct reg_access_gpu_resource_dump_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - See Resource Dump section in the Adapters PRM. */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t segment_type;
	/* Description - Sequence number. 0 on first call of dump and incremented on each more dump. */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t seq_num;
	/* Description - If set, then vhca_id field is valid. Otherwise dump resources on my vhca_id.
Not supported in Switch. */
	/* 0x0.29 - 0x0.29 */
	/* access: WO */
	u_int8_t vhca_id_valid;
	/* Description - If set, data is dumped in the register in inline_data field. otherwise dump to mkey.
Supports only inline dump = 1 */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t inline_dump;
	/* Description - If set, the device has additional information that has not been dumped yet. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t more_dump;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - vhca_id where the resource is allocated.
Not supported in Switch. */
	/* 0x4.0 - 0x4.15 */
	/* access: WO */
	u_int16_t vhca_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - First object index to be dumped when supported by the object.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. */
	/* 0x8.0 - 0x8.31 */
	/* access: INDEX */
	u_int32_t index1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Second object index to be dumped when supported by the object.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. */
	/* 0xc.0 - 0xc.31 */
	/* access: INDEX */
	u_int32_t index2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The amount of objects to dump starting for index 2.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_obj2_supports_all is set, the special value of 0xffff represents "all". When the segment's num_of_objx_supports_active is set, the special value of 0xfffe represents "active". The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj2 is "0". */
	/* 0x10.0 - 0x10.15 */
	/* access: INDEX */
	u_int16_t num_of_obj2;
	/* Description - The amount of objects to dump starting for index 1
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_obj1_supports_all is set, the special value of 0xffff represents "all". When the segment's num_of_objx_supports_active is set, the special value of 0xfffe represents "active". The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj1 is "0". */
	/* 0x10.16 - 0x10.31 */
	/* access: INDEX */
	u_int16_t num_of_obj1;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - An opaque provided by the device. SW shall read the device_opaque upon command done and shall provide it on the next call in case dump_more==1. On first call, device_opaque shall be 0.
 */
	/* 0x18.0 - 0x1c.31 */
	/* access: INDEX */
	u_int64_t device_opaque;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Memory key to dump to. 
Valid when inline_dump==0.
Not supported in Switch. */
	/* 0x20.0 - 0x20.31 */
	/* access: WO */
	u_int32_t mkey;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - In write, the size of maximum allocated buffer that the device can use.
In read, the actual written size.
In granularity of Bytes.
Not supported in Switch. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t size;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - VA address (absolute address) of memory where to start dumping. 
Valid when inline_dump==0.
Not supported in Switch. */
	/* 0x28.0 - 0x2c.31 */
	/* access: WO */
	u_int64_t address;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Data that is dumped in case of inline mode.
Valid when inline_dump==1. */
	/* 0x30.0 - 0xc4.31 */
	/* access: RO */
	u_int32_t inline_data[38];
};

/* Description -   */
/* Size in bytes - 40 */
struct reg_access_gpu_slrg_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - set 1 all lanes measurement page
Supported if PCAM.feature_cap_mask bit 91 is set. 
Relevant only for 5nm
0: per_lane_measurement
1: all_lane_measurement */
	/* 0x0.1 - 0x0.1 */
	/* access: INDEX */
	u_int8_t all_lanes;
	/* Description - For HCA supported only when indicated by PCAM 
0: Network_Port
1: NearEnd_Port - (For Retimer/Gearbox - Host side)
2: Internal_IC_LR_Port 
3: FarEnd_Port - (For Retimer/Gearbox - Line side)

 */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Logical lane number */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. 
0 - Local port number
1 - IB port number
3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number.
 */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - 0: prod_40nm
1: prod_28nm
3: prod_16nm
4: prod_7nm
5: prod_5nm */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t version;
	/* Description - 0 - Invalid
1 - Valid
 */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Table 613, "SLRG - Serdes Lane Receive Grade Register Layout for 40nm and 28nm," on page 652
Table 615, "SLRG - Serdes Lane Receive Grade Register Layout for 16nm," on page 654
Table 617, "SLRG - Serdes Lane Receive Grade Register Layout for 7nm," on page 656
Table 619, "SLRG - Serdes Lane Receive Grade Register Layout for 5nm," on page 657
Table 627, "SLRG all lanes FOM for 5nm- Layout," on page 661 */
	/* 0x4.0 - 0x24.31 */
	/* access: RO */
	union reg_access_gpu_slrg_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 76 */
struct reg_access_gpu_sltp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - copy transmitter parameters to Data Base. 
 */
	/* 0x0.0 - 0x0.0 */
	/* access: OP */
	u_int8_t c_db;
	/* Description - For HCA supported only when indicated by PCAM 
0: Network_Port
1: NearEnd_Port - (For Retimer/Gearbox - Host side)
2: Internal_IC_LR_Port 
3: FarEnd_Port - (For Retimer/Gearbox - Line side) */
	/* 0x0.1 - 0x0.3 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Reserved for PCIe.
The lane speed for TX settings:
0 - SDR / Gen1 (PCIe)
1 - DDR / Gen2 (PCIe) / 5GBASE-R
2 - QDR / Gen3 (PCIe)
3 - FDR10 (10GE / 40GE)
4 - FDR (56GE) / Gen4 (PCIe)
5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)
6 - HDR (50GE / 200GE / 400GE)
7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)
8 - XDR (106.25 Gbd / 212.5Gb/s)
9 - Reserved
10 - 1GE
11 - 2.5GE (XAUI)
12 - 50GE-KR4
13-15 - Reserved */
	/* 0x0.4 - 0x0.7 */
	/* access: RW */
	u_int8_t lane_speed;
	/* Description - Logical lane number */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t lane;
	/* Description - Configures Tx parameter set policy
0 - Tx parameters will be set according to best possible configuration chosen by the system
1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup) */
	/* 0x0.13 - 0x0.13 */
	/* access: RW */
	u_int8_t tx_policy;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number
3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - Local port number [7:0] */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - 0: prod_40nm
1: prod_28nm
3: prod_16nm
4: prod_7nm
5: prod_5nm */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t version;
	/* Description - Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).
For links without AN/LT, valid will be set when Tx is enabled.

0 - Invalid
1 - Valid

Note: Get and Set operations can be set when status = invalid. */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t status;
	/* Description - Local port number [9:8] */
	/* 0x0.30 - 0x0.31 */
	/* access: INDEX */
	u_int8_t lp_msb;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Table 595, "SLTP - Serdes Lane Transmit Parameters Register Layout for 28nm and 40nm," on page 637
Table 597, "SLTP - Serdes Lane Transmit Parameters Register Layout for 16nm," on page 638
Table 601, "SLTP - Serdes Lane Transmit Parameters Register Layout for 7nm," on page 640
Table 605, "SLTP - Serdes Lane Transmit Parameters Register Layout for 5nm," on page 645 */
	/* 0x4.0 - 0x48.31 */
	/* access: RW */
	union reg_access_gpu_sltp_reg_page_data_auto_ext page_data;
};

/* Description -   */
/* Size in bytes - 256 */
union reg_access_gpu_reg_access_gpu_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_gpu_pcam_reg_ext pcam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pmaos_reg_ext pmaos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_gpu_pplr_reg_ext pplr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_ppdfd_ext ppdfd_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_gpu_MLPC_ext MLPC_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pude_reg_ext pude_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pmpr_reg_ext pmpr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_gpu_MRFV_ext MRFV_ext;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	/* access: RW */
	struct reg_access_gpu_pddr_reg_ext pddr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_ptsr_ext ptsr_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_gpgb_ext gpgb_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_gpu_mcam_reg_ext mcam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	/* access: RW */
	struct reg_access_gpu_ppcnt_reg_ext ppcnt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_gpu_mteim_reg_ext mteim_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	/* access: RW */
	struct reg_access_gpu_pcap_reg_ext pcap_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pltc_reg_ext pltc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_gpu_pplm_reg_ext pplm_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_mpscr_ext mpscr_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_gpu_pguid_reg_ext pguid_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pmtm_reg_ext pmtm_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_gpu_mtecr_ext mtecr_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_gpu_mtrc_ctrl_reg_ext mtrc_ctrl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_gpu_ptys_reg_ext ptys_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_paos_reg_ext paos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_gpu_pmlp_reg_ext pmlp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	/* access: RW */
	struct reg_access_gpu_pmmp_reg_ext pmmp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x60.31 */
	/* access: RW */
	struct reg_access_gpu_pbsr_reg_ext pbsr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_gpu_mmdio_ext mmdio_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_mtmp_ext mtmp_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_plib_reg_ext plib_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_gpu_pmpt_reg_ext pmpt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x24.31 */
	/* access: RW */
	struct reg_access_gpu_slrg_reg_ext slrg_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_gpu_mcsr mcsr;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_gsguid_ext gsguid_ext;
	/* Description -  */
	/* 0x0.0 - 0x4c.31 */
	/* access: RW */
	struct reg_access_gpu_pphcr_ext pphcr_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_mtim_ext mtim_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_gplid gplid;
	/* Description -  */
	/* 0x0.0 - 0x48.31 */
	/* access: RW */
	struct reg_access_gpu_sltp_reg_ext sltp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x30.31 */
	/* access: RW */
	struct reg_access_gpu_ppslc_ext ppslc_ext;
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	/* access: RW */
	struct reg_access_gpu_pbwr_ext pbwr_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_mtwe_ext mtwe_ext;
	/* Description -  */
	/* 0x0.0 - 0x58.31 */
	/* access: RW */
	struct reg_access_gpu_mtewe_ext mtewe_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_gpu_mtie_ext mtie_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_gpu_pptt_reg_ext pptt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_gpu_pprt_reg_ext pprt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_ghpkt_ext ghpkt_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_gpu_mdrcr_ext mdrcr_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_gpu_pbwc_ext pbwc_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_mtcap_ext mtcap_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_mcion_ext mcion_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_MTSR_ext MTSR_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_pter_reg_ext pter_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_gpu_mtrc_conf_reg_ext mtrc_conf_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_prtl_reg_ext prtl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_gpu_ppsls_ext ppsls_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_ptsb_ext ptsb_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_gpu_pmpd_reg_ext pmpd_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x58.31 */
	/* access: RW */
	struct reg_access_gpu_mtsde mtsde;
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	/* access: RW */
	struct reg_access_gpu_mcia_ext mcia_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_gpu_ppsc_reg_ext ppsc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc4.31 */
	/* access: RW */
	struct reg_access_gpu_resource_dump_ext resource_dump_ext;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	/* access: RW */
	struct reg_access_gpu_mgir_ext mgir_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_pmtu_reg_ext pmtu_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	/* access: RW */
	struct reg_access_gpu_mtrc_cap_reg_ext mtrc_cap_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_gpu_ppaos_reg_ext ppaos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_gpu_pevnt_ext pevnt_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_gpu_pmcr_reg_ext pmcr_reg_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* pddr_c2p_link_enabed_eth_ext */
void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_pack(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_unpack(struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_print(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_c2p_link_enabed_eth_ext_size(void);
#define REG_ACCESS_GPU_PDDR_C2P_LINK_ENABED_ETH_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_dump(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, FILE *fd);
/* pddr_c2p_link_enabed_ib_ext */
void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_pack(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_unpack(struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_print(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_c2p_link_enabed_ib_ext_size(void);
#define REG_ACCESS_GPU_PDDR_C2P_LINK_ENABED_IB_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_dump(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, FILE *fd);
/* pddr_cable_cap_eth_ext */
void reg_access_gpu_pddr_cable_cap_eth_ext_pack(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_cable_cap_eth_ext_unpack(struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_cable_cap_eth_ext_print(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_cable_cap_eth_ext_size(void);
#define REG_ACCESS_GPU_PDDR_CABLE_CAP_ETH_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_cable_cap_eth_ext_dump(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd);
/* pddr_cable_cap_ib_ext */
void reg_access_gpu_pddr_cable_cap_ib_ext_pack(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_cable_cap_ib_ext_unpack(struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_cable_cap_ib_ext_print(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_cable_cap_ib_ext_size(void);
#define REG_ACCESS_GPU_PDDR_CABLE_CAP_IB_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_cable_cap_ib_ext_dump(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd);
/* pddr_link_active_eth_ext */
void reg_access_gpu_pddr_link_active_eth_ext_pack(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_active_eth_ext_unpack(struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_active_eth_ext_print(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_link_active_eth_ext_size(void);
#define REG_ACCESS_GPU_PDDR_LINK_ACTIVE_ETH_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_link_active_eth_ext_dump(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, FILE *fd);
/* pddr_link_active_ib_ext */
void reg_access_gpu_pddr_link_active_ib_ext_pack(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_active_ib_ext_unpack(struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_active_ib_ext_print(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_link_active_ib_ext_size(void);
#define REG_ACCESS_GPU_PDDR_LINK_ACTIVE_IB_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_link_active_ib_ext_dump(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, FILE *fd);
/* pddr_monitor_opcode_ext */
void reg_access_gpu_pddr_monitor_opcode_ext_pack(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_monitor_opcode_ext_unpack(struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_monitor_opcode_ext_print(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_monitor_opcode_ext_size(void);
#define REG_ACCESS_GPU_PDDR_MONITOR_OPCODE_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_monitor_opcode_ext_dump(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, FILE *fd);
/* pddr_phy_manager_link_enabed_eth_ext */
void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_pack(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_unpack(struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_print(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_size(void);
#define REG_ACCESS_GPU_PDDR_PHY_MANAGER_LINK_ENABED_ETH_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_dump(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, FILE *fd);
/* pddr_phy_manager_link_enabed_ib_ext */
void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_pack(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_unpack(struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_print(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_size(void);
#define REG_ACCESS_GPU_PDDR_PHY_MANAGER_LINK_ENABED_IB_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_dump(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_cable_proto_cap_auto_ext */
void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_CABLE_PROTO_CAP_AUTO_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_core_to_phy_link_enabled_auto_ext */
void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_CORE_TO_PHY_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_link_active_auto_ext */
void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_LINK_ACTIVE_AUTO_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_phy_manager_link_enabled_auto_ext */
void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_PHY_MANAGER_LINK_ENABLED_AUTO_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd);
/* pddr_troubleshooting_page_status_opcode_auto_ext */
void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_pack(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_unpack(union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_print(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_TROUBLESHOOTING_PAGE_STATUS_OPCODE_AUTO_EXT_SIZE    (0x4)
void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_dump(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_gpu_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_uint64_size(void);
#define REG_ACCESS_GPU_UINT64_SIZE    (0x8)
void reg_access_gpu_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* IB_long_portcntrs_attribute_grp_data_ext */
void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_pack(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_unpack(struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_print(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_size(void);
#define REG_ACCESS_GPU_IB_LONG_PORTCNTRS_ATTRIBUTE_GRP_DATA_EXT_SIZE    (0xf8)
void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_dump(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd);
/* IB_portcntrs_attribute_grp_data_ext */
void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_pack(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_unpack(struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_print(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_size(void);
#define REG_ACCESS_GPU_IB_PORTCNTRS_ATTRIBUTE_GRP_DATA_EXT_SIZE    (0xf8)
void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_dump(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd);
/* MRFV_CVB_ext */
void reg_access_gpu_MRFV_CVB_ext_pack(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_CVB_ext_unpack(struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_CVB_ext_print(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_CVB_ext_size(void);
#define REG_ACCESS_GPU_MRFV_CVB_EXT_SIZE    (0x4)
void reg_access_gpu_MRFV_CVB_ext_dump(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, FILE *fd);
/* MRFV_PVS_MAIN_ext */
void reg_access_gpu_MRFV_PVS_MAIN_ext_pack(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_PVS_MAIN_ext_unpack(struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_PVS_MAIN_ext_print(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_PVS_MAIN_ext_size(void);
#define REG_ACCESS_GPU_MRFV_PVS_MAIN_EXT_SIZE    (0x4)
void reg_access_gpu_MRFV_PVS_MAIN_ext_dump(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd);
/* MRFV_PVS_TILE_ext */
void reg_access_gpu_MRFV_PVS_TILE_ext_pack(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_PVS_TILE_ext_unpack(struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_PVS_TILE_ext_print(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_PVS_TILE_ext_size(void);
#define REG_ACCESS_GPU_MRFV_PVS_TILE_EXT_SIZE    (0x4)
void reg_access_gpu_MRFV_PVS_TILE_ext_dump(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd);
/* MRFV_ULT_ext */
void reg_access_gpu_MRFV_ULT_ext_pack(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_ULT_ext_unpack(struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_ULT_ext_print(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_ULT_ext_size(void);
#define REG_ACCESS_GPU_MRFV_ULT_EXT_SIZE    (0xc)
void reg_access_gpu_MRFV_ULT_ext_dump(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, FILE *fd);
/* eth_2819_cntrs_grp_data_layout_ext */
void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_2819_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_2863_cntrs_grp_data_layout_ext */
void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_2863_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_3635_cntrs_grp_data_layout_ext */
void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_3635_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_802_3_cntrs_grp_data_layout_ext */
void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_802_3_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_discard_cntrs_grp_ext */
void reg_access_gpu_eth_discard_cntrs_grp_ext_pack(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_discard_cntrs_grp_ext_unpack(struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_discard_cntrs_grp_ext_print(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_discard_cntrs_grp_ext_size(void);
#define REG_ACCESS_GPU_ETH_DISCARD_CNTRS_GRP_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_discard_cntrs_grp_ext_dump(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, FILE *fd);
/* eth_extended_cntrs_grp_data_layout_ext */
void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_EXTENDED_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_per_prio_grp_data_layout_ext */
void reg_access_gpu_eth_per_prio_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_prio_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_prio_grp_data_layout_ext_print(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_per_prio_grp_data_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_PER_PRIO_GRP_DATA_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_per_prio_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, FILE *fd);
/* eth_per_traffic_class_cong_layout_ext */
void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_pack(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_unpack(struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_print(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_per_traffic_class_cong_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_PER_TRAFFIC_CLASS_CONG_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_dump(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, FILE *fd);
/* eth_per_traffic_class_layout_ext */
void reg_access_gpu_eth_per_traffic_class_layout_ext_pack(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_traffic_class_layout_ext_unpack(struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_eth_per_traffic_class_layout_ext_print(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_eth_per_traffic_class_layout_ext_size(void);
#define REG_ACCESS_GPU_ETH_PER_TRAFFIC_CLASS_LAYOUT_EXT_SIZE    (0xf8)
void reg_access_gpu_eth_per_traffic_class_layout_ext_dump(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, FILE *fd);
/* module_latched_flag_info_ext */
void reg_access_gpu_module_latched_flag_info_ext_pack(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_module_latched_flag_info_ext_unpack(struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_module_latched_flag_info_ext_print(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_module_latched_flag_info_ext_size(void);
#define REG_ACCESS_GPU_MODULE_LATCHED_FLAG_INFO_EXT_SIZE    (0xf8)
void reg_access_gpu_module_latched_flag_info_ext_dump(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, FILE *fd);
/* pddr_link_down_info_page_ext */
void reg_access_gpu_pddr_link_down_info_page_ext_pack(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_down_info_page_ext_unpack(struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_link_down_info_page_ext_print(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_link_down_info_page_ext_size(void);
#define REG_ACCESS_GPU_PDDR_LINK_DOWN_INFO_PAGE_EXT_SIZE    (0xf4)
void reg_access_gpu_pddr_link_down_info_page_ext_dump(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, FILE *fd);
/* pddr_module_info_ext */
void reg_access_gpu_pddr_module_info_ext_pack(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_module_info_ext_unpack(struct reg_access_gpu_pddr_module_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_module_info_ext_print(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_module_info_ext_size(void);
#define REG_ACCESS_GPU_PDDR_MODULE_INFO_EXT_SIZE    (0xd8)
void reg_access_gpu_pddr_module_info_ext_dump(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, FILE *fd);
/* pddr_operation_info_page_ext */
void reg_access_gpu_pddr_operation_info_page_ext_pack(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_ext_unpack(struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_operation_info_page_ext_print(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_operation_info_page_ext_size(void);
#define REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_gpu_pddr_operation_info_page_ext_dump(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, FILE *fd);
/* pddr_phy_info_page_ext */
void reg_access_gpu_pddr_phy_info_page_ext_pack(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_info_page_ext_unpack(struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_phy_info_page_ext_print(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_phy_info_page_ext_size(void);
#define REG_ACCESS_GPU_PDDR_PHY_INFO_PAGE_EXT_SIZE    (0xf8)
void reg_access_gpu_pddr_phy_info_page_ext_dump(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, FILE *fd);
/* pddr_troubleshooting_page_ext */
void reg_access_gpu_pddr_troubleshooting_page_ext_pack(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_troubleshooting_page_ext_unpack(struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_troubleshooting_page_ext_print(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_troubleshooting_page_ext_size(void);
#define REG_ACCESS_GPU_PDDR_TROUBLESHOOTING_PAGE_EXT_SIZE    (0xf8)
void reg_access_gpu_pddr_troubleshooting_page_ext_dump(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd);
/* phys_layer_cntrs_ext */
void reg_access_gpu_phys_layer_cntrs_ext_pack(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_phys_layer_cntrs_ext_unpack(struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_phys_layer_cntrs_ext_print(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_phys_layer_cntrs_ext_size(void);
#define REG_ACCESS_GPU_PHYS_LAYER_CNTRS_EXT_SIZE    (0xf8)
void reg_access_gpu_phys_layer_cntrs_ext_dump(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, FILE *fd);
/* phys_layer_stat_cntrs_ext */
void reg_access_gpu_phys_layer_stat_cntrs_ext_pack(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_phys_layer_stat_cntrs_ext_unpack(struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_phys_layer_stat_cntrs_ext_print(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_phys_layer_stat_cntrs_ext_size(void);
#define REG_ACCESS_GPU_PHYS_LAYER_STAT_CNTRS_EXT_SIZE    (0xf8)
void reg_access_gpu_phys_layer_stat_cntrs_ext_dump(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, FILE *fd);
/* pmmp_cmis_protocol_override_layout_ext */
void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_pack(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_unpack(struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_print(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_size(void);
#define REG_ACCESS_GPU_PMMP_CMIS_PROTOCOL_OVERRIDE_LAYOUT_EXT_SIZE    (0xc)
void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_dump(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, FILE *fd);
/* pmmp_qsfp_protocol_override_layout_ext */
void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_pack(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_unpack(struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_print(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_size(void);
#define REG_ACCESS_GPU_PMMP_QSFP_PROTOCOL_OVERRIDE_LAYOUT_EXT_SIZE    (0xc)
void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_dump(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, FILE *fd);
/* pmmp_sfp_protocol_bytes_override_ext */
void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_pack(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_unpack(struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_print(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_size(void);
#define REG_ACCESS_GPU_PMMP_SFP_PROTOCOL_BYTES_OVERRIDE_EXT_SIZE    (0xc)
void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_dump(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, FILE *fd);
/* ppcnt_infiniband_general_counter_ext */
void reg_access_gpu_ppcnt_infiniband_general_counter_ext_pack(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_infiniband_general_counter_ext_unpack(struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_infiniband_general_counter_ext_print(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_infiniband_general_counter_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_INFINIBAND_GENERAL_COUNTER_EXT_SIZE    (0xf8)
void reg_access_gpu_ppcnt_infiniband_general_counter_ext_dump(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, FILE *fd);
/* ppcnt_infiniband_packets_counter_ext */
void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_pack(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_unpack(struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_print(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_infiniband_packets_counter_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_INFINIBAND_PACKETS_COUNTER_EXT_SIZE    (0xf8)
void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_dump(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, FILE *fd);
/* ppcnt_plr_counters_ext */
void reg_access_gpu_ppcnt_plr_counters_ext_pack(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_plr_counters_ext_unpack(struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_plr_counters_ext_print(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_plr_counters_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_PLR_COUNTERS_EXT_SIZE    (0xf8)
void reg_access_gpu_ppcnt_plr_counters_ext_dump(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, FILE *fd);
/* ppcnt_rs_fec_histograms_counters_ext */
void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_pack(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_unpack(struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_print(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_RS_FEC_HISTOGRAMS_COUNTERS_EXT_SIZE    (0xf8)
void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_dump(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, FILE *fd);
/* pter_phy_page_reg_ext */
void reg_access_gpu_pter_phy_page_reg_ext_pack(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pter_phy_page_reg_ext_unpack(struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pter_phy_page_reg_ext_print(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pter_phy_page_reg_ext_size(void);
#define REG_ACCESS_GPU_PTER_PHY_PAGE_REG_EXT_SIZE    (0x1c)
void reg_access_gpu_pter_phy_page_reg_ext_dump(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, FILE *fd);
/* pter_port_page_reg_ext */
void reg_access_gpu_pter_port_page_reg_ext_pack(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pter_port_page_reg_ext_unpack(struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pter_port_page_reg_ext_print(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pter_port_page_reg_ext_size(void);
#define REG_ACCESS_GPU_PTER_PORT_PAGE_REG_EXT_SIZE    (0x1c)
void reg_access_gpu_pter_port_page_reg_ext_dump(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, FILE *fd);
/* rom_version_ext */
void reg_access_gpu_rom_version_ext_pack(const struct reg_access_gpu_rom_version_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_rom_version_ext_unpack(struct reg_access_gpu_rom_version_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_rom_version_ext_print(const struct reg_access_gpu_rom_version_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_rom_version_ext_size(void);
#define REG_ACCESS_GPU_ROM_VERSION_EXT_SIZE    (0x4)
void reg_access_gpu_rom_version_ext_dump(const struct reg_access_gpu_rom_version_ext *ptr_struct, FILE *fd);
/* slrg_16nm_ext */
void reg_access_gpu_slrg_16nm_ext_pack(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_16nm_ext_unpack(struct reg_access_gpu_slrg_16nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_16nm_ext_print(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_16nm_ext_size(void);
#define REG_ACCESS_GPU_SLRG_16NM_EXT_SIZE    (0x24)
void reg_access_gpu_slrg_16nm_ext_dump(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, FILE *fd);
/* slrg_40nm_28nm_ext */
void reg_access_gpu_slrg_40nm_28nm_ext_pack(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_40nm_28nm_ext_unpack(struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_40nm_28nm_ext_print(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_40nm_28nm_ext_size(void);
#define REG_ACCESS_GPU_SLRG_40NM_28NM_EXT_SIZE    (0x24)
void reg_access_gpu_slrg_40nm_28nm_ext_dump(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, FILE *fd);
/* slrg_5nm_ext */
void reg_access_gpu_slrg_5nm_ext_pack(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_5nm_ext_unpack(struct reg_access_gpu_slrg_5nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_5nm_ext_print(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_5nm_ext_size(void);
#define REG_ACCESS_GPU_SLRG_5NM_EXT_SIZE    (0x18)
void reg_access_gpu_slrg_5nm_ext_dump(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, FILE *fd);
/* slrg_7nm_ext */
void reg_access_gpu_slrg_7nm_ext_pack(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_7nm_ext_unpack(struct reg_access_gpu_slrg_7nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_7nm_ext_print(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_7nm_ext_size(void);
#define REG_ACCESS_GPU_SLRG_7NM_EXT_SIZE    (0x18)
void reg_access_gpu_slrg_7nm_ext_dump(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, FILE *fd);
/* slrg_all_lanes_5nm_ext */
void reg_access_gpu_slrg_all_lanes_5nm_ext_pack(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_all_lanes_5nm_ext_unpack(struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_all_lanes_5nm_ext_print(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_all_lanes_5nm_ext_size(void);
#define REG_ACCESS_GPU_SLRG_ALL_LANES_5NM_EXT_SIZE    (0x14)
void reg_access_gpu_slrg_all_lanes_5nm_ext_dump(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, FILE *fd);
/* sltp_16nm_ext */
void reg_access_gpu_sltp_16nm_ext_pack(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_16nm_ext_unpack(struct reg_access_gpu_sltp_16nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_16nm_ext_print(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_16nm_ext_size(void);
#define REG_ACCESS_GPU_SLTP_16NM_EXT_SIZE    (0x48)
void reg_access_gpu_sltp_16nm_ext_dump(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, FILE *fd);
/* sltp_28nm_40nm_ext */
void reg_access_gpu_sltp_28nm_40nm_ext_pack(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_28nm_40nm_ext_unpack(struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_28nm_40nm_ext_print(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_28nm_40nm_ext_size(void);
#define REG_ACCESS_GPU_SLTP_28NM_40NM_EXT_SIZE    (0x48)
void reg_access_gpu_sltp_28nm_40nm_ext_dump(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, FILE *fd);
/* sltp_5nm_ext */
void reg_access_gpu_sltp_5nm_ext_pack(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_5nm_ext_unpack(struct reg_access_gpu_sltp_5nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_5nm_ext_print(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_5nm_ext_size(void);
#define REG_ACCESS_GPU_SLTP_5NM_EXT_SIZE    (0x48)
void reg_access_gpu_sltp_5nm_ext_dump(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, FILE *fd);
/* sltp_7nm_ext */
void reg_access_gpu_sltp_7nm_ext_pack(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_7nm_ext_unpack(struct reg_access_gpu_sltp_7nm_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_7nm_ext_print(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_7nm_ext_size(void);
#define REG_ACCESS_GPU_SLTP_7NM_EXT_SIZE    (0x48)
void reg_access_gpu_sltp_7nm_ext_dump(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, FILE *fd);
/* MRFV_data_auto_ext */
void reg_access_gpu_MRFV_data_auto_ext_pack(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_data_auto_ext_unpack(union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_data_auto_ext_print(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_data_auto_ext_size(void);
#define REG_ACCESS_GPU_MRFV_DATA_AUTO_EXT_SIZE    (0xc)
void reg_access_gpu_MRFV_data_auto_ext_dump(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, FILE *fd);
/* lane_2_module_mapping_ext */
void reg_access_gpu_lane_2_module_mapping_ext_pack(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_lane_2_module_mapping_ext_unpack(struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_lane_2_module_mapping_ext_print(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_lane_2_module_mapping_ext_size(void);
#define REG_ACCESS_GPU_LANE_2_MODULE_MAPPING_EXT_SIZE    (0x4)
void reg_access_gpu_lane_2_module_mapping_ext_dump(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, FILE *fd);
/* mgir_dev_info_ext */
void reg_access_gpu_mgir_dev_info_ext_pack(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mgir_dev_info_ext_unpack(struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mgir_dev_info_ext_print(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mgir_dev_info_ext_size(void);
#define REG_ACCESS_GPU_MGIR_DEV_INFO_EXT_SIZE    (0x1c)
void reg_access_gpu_mgir_dev_info_ext_dump(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, FILE *fd);
/* mgir_fw_info_ext */
void reg_access_gpu_mgir_fw_info_ext_pack(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mgir_fw_info_ext_unpack(struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mgir_fw_info_ext_print(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mgir_fw_info_ext_size(void);
#define REG_ACCESS_GPU_MGIR_FW_INFO_EXT_SIZE    (0x40)
void reg_access_gpu_mgir_fw_info_ext_dump(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, FILE *fd);
/* mgir_hardware_info_ext */
void reg_access_gpu_mgir_hardware_info_ext_pack(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mgir_hardware_info_ext_unpack(struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mgir_hardware_info_ext_print(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mgir_hardware_info_ext_size(void);
#define REG_ACCESS_GPU_MGIR_HARDWARE_INFO_EXT_SIZE    (0x20)
void reg_access_gpu_mgir_hardware_info_ext_dump(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, FILE *fd);
/* mgir_sw_info_ext */
void reg_access_gpu_mgir_sw_info_ext_pack(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mgir_sw_info_ext_unpack(struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mgir_sw_info_ext_print(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mgir_sw_info_ext_size(void);
#define REG_ACCESS_GPU_MGIR_SW_INFO_EXT_SIZE    (0x20)
void reg_access_gpu_mgir_sw_info_ext_dump(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, FILE *fd);
/* pddr_reg_page_data_auto_ext */
void reg_access_gpu_pddr_reg_page_data_auto_ext_pack(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_reg_page_data_auto_ext_unpack(union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_reg_page_data_auto_ext_print(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_GPU_PDDR_REG_PAGE_DATA_AUTO_EXT_SIZE    (0xf8)
void reg_access_gpu_pddr_reg_page_data_auto_ext_dump(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* pmmp_reg_qsfp_cable_protocol_technology_auto_ext */
void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_pack(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_unpack(union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_print(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_size(void);
#define REG_ACCESS_GPU_PMMP_REG_QSFP_CABLE_PROTOCOL_TECHNOLOGY_AUTO_EXT_SIZE    (0xc)
void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_dump(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd);
/* pmmp_reg_sfp_cable_protocol_technology_auto_ext */
void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_pack(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_unpack(union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_print(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_size(void);
#define REG_ACCESS_GPU_PMMP_REG_SFP_CABLE_PROTOCOL_TECHNOLOGY_AUTO_EXT_SIZE    (0xc)
void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_dump(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd);
/* ppcnt_reg_counter_set_auto_ext */
void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_pack(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_unpack(union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_print(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_reg_counter_set_auto_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_REG_COUNTER_SET_AUTO_EXT_SIZE    (0xf8)
void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_dump(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, FILE *fd);
/* pphcr_bin_range_ext */
void reg_access_gpu_pphcr_bin_range_ext_pack(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pphcr_bin_range_ext_unpack(struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pphcr_bin_range_ext_print(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pphcr_bin_range_ext_size(void);
#define REG_ACCESS_GPU_PPHCR_BIN_RANGE_EXT_SIZE    (0x4)
void reg_access_gpu_pphcr_bin_range_ext_dump(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, FILE *fd);
/* pter_reg_page_data_auto_ext */
void reg_access_gpu_pter_reg_page_data_auto_ext_pack(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pter_reg_page_data_auto_ext_unpack(union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pter_reg_page_data_auto_ext_print(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pter_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_GPU_PTER_REG_PAGE_DATA_AUTO_EXT_SIZE    (0x1c)
void reg_access_gpu_pter_reg_page_data_auto_ext_dump(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* slrg_reg_page_data_auto_ext */
void reg_access_gpu_slrg_reg_page_data_auto_ext_pack(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_reg_page_data_auto_ext_unpack(union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_reg_page_data_auto_ext_print(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_GPU_SLRG_REG_PAGE_DATA_AUTO_EXT_SIZE    (0x24)
void reg_access_gpu_slrg_reg_page_data_auto_ext_dump(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* sltp_reg_page_data_auto_ext */
void reg_access_gpu_sltp_reg_page_data_auto_ext_pack(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_reg_page_data_auto_ext_unpack(union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_reg_page_data_auto_ext_print(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_reg_page_data_auto_ext_size(void);
#define REG_ACCESS_GPU_SLTP_REG_PAGE_DATA_AUTO_EXT_SIZE    (0x48)
void reg_access_gpu_sltp_reg_page_data_auto_ext_dump(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, FILE *fd);
/* stat_bufferx_reg_ext */
void reg_access_gpu_stat_bufferx_reg_ext_pack(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_stat_bufferx_reg_ext_unpack(struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_stat_bufferx_reg_ext_print(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_stat_bufferx_reg_ext_size(void);
#define REG_ACCESS_GPU_STAT_BUFFERX_REG_EXT_SIZE    (0x8)
void reg_access_gpu_stat_bufferx_reg_ext_dump(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, FILE *fd);
/* string_db_parameters_ext */
void reg_access_gpu_string_db_parameters_ext_pack(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_string_db_parameters_ext_unpack(struct reg_access_gpu_string_db_parameters_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_string_db_parameters_ext_print(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_string_db_parameters_ext_size(void);
#define REG_ACCESS_GPU_STRING_DB_PARAMETERS_EXT_SIZE    (0x8)
void reg_access_gpu_string_db_parameters_ext_dump(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, FILE *fd);
/* MLPC_ext */
void reg_access_gpu_MLPC_ext_pack(const struct reg_access_gpu_MLPC_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MLPC_ext_unpack(struct reg_access_gpu_MLPC_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MLPC_ext_print(const struct reg_access_gpu_MLPC_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MLPC_ext_size(void);
#define REG_ACCESS_GPU_MLPC_EXT_SIZE    (0x40)
void reg_access_gpu_MLPC_ext_dump(const struct reg_access_gpu_MLPC_ext *ptr_struct, FILE *fd);
/* MRFV_ext */
void reg_access_gpu_MRFV_ext_pack(const struct reg_access_gpu_MRFV_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_ext_unpack(struct reg_access_gpu_MRFV_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MRFV_ext_print(const struct reg_access_gpu_MRFV_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MRFV_ext_size(void);
#define REG_ACCESS_GPU_MRFV_EXT_SIZE    (0x40)
void reg_access_gpu_MRFV_ext_dump(const struct reg_access_gpu_MRFV_ext *ptr_struct, FILE *fd);
/* MTSR_ext */
void reg_access_gpu_MTSR_ext_pack(const struct reg_access_gpu_MTSR_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_MTSR_ext_unpack(struct reg_access_gpu_MTSR_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_MTSR_ext_print(const struct reg_access_gpu_MTSR_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_MTSR_ext_size(void);
#define REG_ACCESS_GPU_MTSR_EXT_SIZE    (0x10)
void reg_access_gpu_MTSR_ext_dump(const struct reg_access_gpu_MTSR_ext *ptr_struct, FILE *fd);
/* ghpkt_ext */
void reg_access_gpu_ghpkt_ext_pack(const struct reg_access_gpu_ghpkt_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ghpkt_ext_unpack(struct reg_access_gpu_ghpkt_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ghpkt_ext_print(const struct reg_access_gpu_ghpkt_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ghpkt_ext_size(void);
#define REG_ACCESS_GPU_GHPKT_EXT_SIZE    (0x10)
void reg_access_gpu_ghpkt_ext_dump(const struct reg_access_gpu_ghpkt_ext *ptr_struct, FILE *fd);
/* gpgb_ext */
void reg_access_gpu_gpgb_ext_pack(const struct reg_access_gpu_gpgb_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_gpgb_ext_unpack(struct reg_access_gpu_gpgb_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_gpgb_ext_print(const struct reg_access_gpu_gpgb_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_gpgb_ext_size(void);
#define REG_ACCESS_GPU_GPGB_EXT_SIZE    (0x10)
void reg_access_gpu_gpgb_ext_dump(const struct reg_access_gpu_gpgb_ext *ptr_struct, FILE *fd);
/* gplid */
void reg_access_gpu_gplid_pack(const struct reg_access_gpu_gplid *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_gplid_unpack(struct reg_access_gpu_gplid *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_gplid_print(const struct reg_access_gpu_gplid *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_gplid_size(void);
#define REG_ACCESS_GPU_GPLID_SIZE    (0x10)
void reg_access_gpu_gplid_dump(const struct reg_access_gpu_gplid *ptr_struct, FILE *fd);
/* gsguid_ext */
void reg_access_gpu_gsguid_ext_pack(const struct reg_access_gpu_gsguid_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_gsguid_ext_unpack(struct reg_access_gpu_gsguid_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_gsguid_ext_print(const struct reg_access_gpu_gsguid_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_gsguid_ext_size(void);
#define REG_ACCESS_GPU_GSGUID_EXT_SIZE    (0x10)
void reg_access_gpu_gsguid_ext_dump(const struct reg_access_gpu_gsguid_ext *ptr_struct, FILE *fd);
/* mcam_reg_ext */
void reg_access_gpu_mcam_reg_ext_pack(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mcam_reg_ext_unpack(struct reg_access_gpu_mcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mcam_reg_ext_print(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mcam_reg_ext_size(void);
#define REG_ACCESS_GPU_MCAM_REG_EXT_SIZE    (0x48)
void reg_access_gpu_mcam_reg_ext_dump(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, FILE *fd);
/* mcia_ext */
void reg_access_gpu_mcia_ext_pack(const struct reg_access_gpu_mcia_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mcia_ext_unpack(struct reg_access_gpu_mcia_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mcia_ext_print(const struct reg_access_gpu_mcia_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mcia_ext_size(void);
#define REG_ACCESS_GPU_MCIA_EXT_SIZE    (0x94)
void reg_access_gpu_mcia_ext_dump(const struct reg_access_gpu_mcia_ext *ptr_struct, FILE *fd);
/* mcion_ext */
void reg_access_gpu_mcion_ext_pack(const struct reg_access_gpu_mcion_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mcion_ext_unpack(struct reg_access_gpu_mcion_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mcion_ext_print(const struct reg_access_gpu_mcion_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mcion_ext_size(void);
#define REG_ACCESS_GPU_MCION_EXT_SIZE    (0x10)
void reg_access_gpu_mcion_ext_dump(const struct reg_access_gpu_mcion_ext *ptr_struct, FILE *fd);
/* mcsr */
void reg_access_gpu_mcsr_pack(const struct reg_access_gpu_mcsr *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mcsr_unpack(struct reg_access_gpu_mcsr *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mcsr_print(const struct reg_access_gpu_mcsr *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mcsr_size(void);
#define REG_ACCESS_GPU_MCSR_SIZE    (0x50)
void reg_access_gpu_mcsr_dump(const struct reg_access_gpu_mcsr *ptr_struct, FILE *fd);
/* mdrcr_ext */
void reg_access_gpu_mdrcr_ext_pack(const struct reg_access_gpu_mdrcr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mdrcr_ext_unpack(struct reg_access_gpu_mdrcr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mdrcr_ext_print(const struct reg_access_gpu_mdrcr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mdrcr_ext_size(void);
#define REG_ACCESS_GPU_MDRCR_EXT_SIZE    (0x30)
void reg_access_gpu_mdrcr_ext_dump(const struct reg_access_gpu_mdrcr_ext *ptr_struct, FILE *fd);
/* mgir_ext */
void reg_access_gpu_mgir_ext_pack(const struct reg_access_gpu_mgir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mgir_ext_unpack(struct reg_access_gpu_mgir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mgir_ext_print(const struct reg_access_gpu_mgir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mgir_ext_size(void);
#define REG_ACCESS_GPU_MGIR_EXT_SIZE    (0xa0)
void reg_access_gpu_mgir_ext_dump(const struct reg_access_gpu_mgir_ext *ptr_struct, FILE *fd);
/* mmdio_ext */
void reg_access_gpu_mmdio_ext_pack(const struct reg_access_gpu_mmdio_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mmdio_ext_unpack(struct reg_access_gpu_mmdio_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mmdio_ext_print(const struct reg_access_gpu_mmdio_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mmdio_ext_size(void);
#define REG_ACCESS_GPU_MMDIO_EXT_SIZE    (0xc)
void reg_access_gpu_mmdio_ext_dump(const struct reg_access_gpu_mmdio_ext *ptr_struct, FILE *fd);
/* mpscr_ext */
void reg_access_gpu_mpscr_ext_pack(const struct reg_access_gpu_mpscr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mpscr_ext_unpack(struct reg_access_gpu_mpscr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mpscr_ext_print(const struct reg_access_gpu_mpscr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mpscr_ext_size(void);
#define REG_ACCESS_GPU_MPSCR_EXT_SIZE    (0x20)
void reg_access_gpu_mpscr_ext_dump(const struct reg_access_gpu_mpscr_ext *ptr_struct, FILE *fd);
/* mtcap_ext */
void reg_access_gpu_mtcap_ext_pack(const struct reg_access_gpu_mtcap_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtcap_ext_unpack(struct reg_access_gpu_mtcap_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtcap_ext_print(const struct reg_access_gpu_mtcap_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtcap_ext_size(void);
#define REG_ACCESS_GPU_MTCAP_EXT_SIZE    (0x10)
void reg_access_gpu_mtcap_ext_dump(const struct reg_access_gpu_mtcap_ext *ptr_struct, FILE *fd);
/* mtecr_ext */
void reg_access_gpu_mtecr_ext_pack(const struct reg_access_gpu_mtecr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtecr_ext_unpack(struct reg_access_gpu_mtecr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtecr_ext_print(const struct reg_access_gpu_mtecr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtecr_ext_size(void);
#define REG_ACCESS_GPU_MTECR_EXT_SIZE    (0x60)
void reg_access_gpu_mtecr_ext_dump(const struct reg_access_gpu_mtecr_ext *ptr_struct, FILE *fd);
/* mteim_reg_ext */
void reg_access_gpu_mteim_reg_ext_pack(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mteim_reg_ext_unpack(struct reg_access_gpu_mteim_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mteim_reg_ext_print(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mteim_reg_ext_size(void);
#define REG_ACCESS_GPU_MTEIM_REG_EXT_SIZE    (0x30)
void reg_access_gpu_mteim_reg_ext_dump(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, FILE *fd);
/* mtewe_ext */
void reg_access_gpu_mtewe_ext_pack(const struct reg_access_gpu_mtewe_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtewe_ext_unpack(struct reg_access_gpu_mtewe_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtewe_ext_print(const struct reg_access_gpu_mtewe_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtewe_ext_size(void);
#define REG_ACCESS_GPU_MTEWE_EXT_SIZE    (0x5c)
void reg_access_gpu_mtewe_ext_dump(const struct reg_access_gpu_mtewe_ext *ptr_struct, FILE *fd);
/* mtie_ext */
void reg_access_gpu_mtie_ext_pack(const struct reg_access_gpu_mtie_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtie_ext_unpack(struct reg_access_gpu_mtie_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtie_ext_print(const struct reg_access_gpu_mtie_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtie_ext_size(void);
#define REG_ACCESS_GPU_MTIE_EXT_SIZE    (0x30)
void reg_access_gpu_mtie_ext_dump(const struct reg_access_gpu_mtie_ext *ptr_struct, FILE *fd);
/* mtim_ext */
void reg_access_gpu_mtim_ext_pack(const struct reg_access_gpu_mtim_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtim_ext_unpack(struct reg_access_gpu_mtim_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtim_ext_print(const struct reg_access_gpu_mtim_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtim_ext_size(void);
#define REG_ACCESS_GPU_MTIM_EXT_SIZE    (0x10)
void reg_access_gpu_mtim_ext_dump(const struct reg_access_gpu_mtim_ext *ptr_struct, FILE *fd);
/* mtmp_ext */
void reg_access_gpu_mtmp_ext_pack(const struct reg_access_gpu_mtmp_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtmp_ext_unpack(struct reg_access_gpu_mtmp_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtmp_ext_print(const struct reg_access_gpu_mtmp_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtmp_ext_size(void);
#define REG_ACCESS_GPU_MTMP_EXT_SIZE    (0x20)
void reg_access_gpu_mtmp_ext_dump(const struct reg_access_gpu_mtmp_ext *ptr_struct, FILE *fd);
/* mtrc_cap_reg_ext */
void reg_access_gpu_mtrc_cap_reg_ext_pack(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_cap_reg_ext_unpack(struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_cap_reg_ext_print(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtrc_cap_reg_ext_size(void);
#define REG_ACCESS_GPU_MTRC_CAP_REG_EXT_SIZE    (0x84)
void reg_access_gpu_mtrc_cap_reg_ext_dump(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, FILE *fd);
/* mtrc_conf_reg_ext */
void reg_access_gpu_mtrc_conf_reg_ext_pack(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_conf_reg_ext_unpack(struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_conf_reg_ext_print(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtrc_conf_reg_ext_size(void);
#define REG_ACCESS_GPU_MTRC_CONF_REG_EXT_SIZE    (0x80)
void reg_access_gpu_mtrc_conf_reg_ext_dump(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, FILE *fd);
/* mtrc_ctrl_reg_ext */
void reg_access_gpu_mtrc_ctrl_reg_ext_pack(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_ctrl_reg_ext_unpack(struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtrc_ctrl_reg_ext_print(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtrc_ctrl_reg_ext_size(void);
#define REG_ACCESS_GPU_MTRC_CTRL_REG_EXT_SIZE    (0x40)
void reg_access_gpu_mtrc_ctrl_reg_ext_dump(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd);
/* mtsde */
void reg_access_gpu_mtsde_pack(const struct reg_access_gpu_mtsde *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtsde_unpack(struct reg_access_gpu_mtsde *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtsde_print(const struct reg_access_gpu_mtsde *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtsde_size(void);
#define REG_ACCESS_GPU_MTSDE_SIZE    (0x5c)
void reg_access_gpu_mtsde_dump(const struct reg_access_gpu_mtsde *ptr_struct, FILE *fd);
/* mtwe_ext */
void reg_access_gpu_mtwe_ext_pack(const struct reg_access_gpu_mtwe_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_mtwe_ext_unpack(struct reg_access_gpu_mtwe_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_mtwe_ext_print(const struct reg_access_gpu_mtwe_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_mtwe_ext_size(void);
#define REG_ACCESS_GPU_MTWE_EXT_SIZE    (0x10)
void reg_access_gpu_mtwe_ext_dump(const struct reg_access_gpu_mtwe_ext *ptr_struct, FILE *fd);
/* paos_reg_ext */
void reg_access_gpu_paos_reg_ext_pack(const struct reg_access_gpu_paos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_paos_reg_ext_unpack(struct reg_access_gpu_paos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_paos_reg_ext_print(const struct reg_access_gpu_paos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_paos_reg_ext_size(void);
#define REG_ACCESS_GPU_PAOS_REG_EXT_SIZE    (0x10)
void reg_access_gpu_paos_reg_ext_dump(const struct reg_access_gpu_paos_reg_ext *ptr_struct, FILE *fd);
/* pbsr_reg_ext */
void reg_access_gpu_pbsr_reg_ext_pack(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pbsr_reg_ext_unpack(struct reg_access_gpu_pbsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pbsr_reg_ext_print(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pbsr_reg_ext_size(void);
#define REG_ACCESS_GPU_PBSR_REG_EXT_SIZE    (0x64)
void reg_access_gpu_pbsr_reg_ext_dump(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, FILE *fd);
/* pbwc_ext */
void reg_access_gpu_pbwc_ext_pack(const struct reg_access_gpu_pbwc_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pbwc_ext_unpack(struct reg_access_gpu_pbwc_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pbwc_ext_print(const struct reg_access_gpu_pbwc_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pbwc_ext_size(void);
#define REG_ACCESS_GPU_PBWC_EXT_SIZE    (0x8)
void reg_access_gpu_pbwc_ext_dump(const struct reg_access_gpu_pbwc_ext *ptr_struct, FILE *fd);
/* pbwr_ext */
void reg_access_gpu_pbwr_ext_pack(const struct reg_access_gpu_pbwr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pbwr_ext_unpack(struct reg_access_gpu_pbwr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pbwr_ext_print(const struct reg_access_gpu_pbwr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pbwr_ext_size(void);
#define REG_ACCESS_GPU_PBWR_EXT_SIZE    (0x90)
void reg_access_gpu_pbwr_ext_dump(const struct reg_access_gpu_pbwr_ext *ptr_struct, FILE *fd);
/* pcam_reg_ext */
void reg_access_gpu_pcam_reg_ext_pack(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pcam_reg_ext_unpack(struct reg_access_gpu_pcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pcam_reg_ext_print(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pcam_reg_ext_size(void);
#define REG_ACCESS_GPU_PCAM_REG_EXT_SIZE    (0x50)
void reg_access_gpu_pcam_reg_ext_dump(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, FILE *fd);
/* pcap_reg_ext */
void reg_access_gpu_pcap_reg_ext_pack(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pcap_reg_ext_unpack(struct reg_access_gpu_pcap_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pcap_reg_ext_print(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pcap_reg_ext_size(void);
#define REG_ACCESS_GPU_PCAP_REG_EXT_SIZE    (0x14)
void reg_access_gpu_pcap_reg_ext_dump(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, FILE *fd);
/* pddr_reg_ext */
void reg_access_gpu_pddr_reg_ext_pack(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pddr_reg_ext_unpack(struct reg_access_gpu_pddr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pddr_reg_ext_print(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pddr_reg_ext_size(void);
#define REG_ACCESS_GPU_PDDR_REG_EXT_SIZE    (0x100)
void reg_access_gpu_pddr_reg_ext_dump(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, FILE *fd);
/* pevnt_ext */
void reg_access_gpu_pevnt_ext_pack(const struct reg_access_gpu_pevnt_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pevnt_ext_unpack(struct reg_access_gpu_pevnt_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pevnt_ext_print(const struct reg_access_gpu_pevnt_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pevnt_ext_size(void);
#define REG_ACCESS_GPU_PEVNT_EXT_SIZE    (0x8)
void reg_access_gpu_pevnt_ext_dump(const struct reg_access_gpu_pevnt_ext *ptr_struct, FILE *fd);
/* pguid_reg_ext */
void reg_access_gpu_pguid_reg_ext_pack(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pguid_reg_ext_unpack(struct reg_access_gpu_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pguid_reg_ext_print(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pguid_reg_ext_size(void);
#define REG_ACCESS_GPU_PGUID_REG_EXT_SIZE    (0x60)
void reg_access_gpu_pguid_reg_ext_dump(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, FILE *fd);
/* plib_reg_ext */
void reg_access_gpu_plib_reg_ext_pack(const struct reg_access_gpu_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_plib_reg_ext_unpack(struct reg_access_gpu_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_plib_reg_ext_print(const struct reg_access_gpu_plib_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_plib_reg_ext_size(void);
#define REG_ACCESS_GPU_PLIB_REG_EXT_SIZE    (0x10)
void reg_access_gpu_plib_reg_ext_dump(const struct reg_access_gpu_plib_reg_ext *ptr_struct, FILE *fd);
/* pltc_reg_ext */
void reg_access_gpu_pltc_reg_ext_pack(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pltc_reg_ext_unpack(struct reg_access_gpu_pltc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pltc_reg_ext_print(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pltc_reg_ext_size(void);
#define REG_ACCESS_GPU_PLTC_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pltc_reg_ext_dump(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, FILE *fd);
/* pmaos_reg_ext */
void reg_access_gpu_pmaos_reg_ext_pack(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmaos_reg_ext_unpack(struct reg_access_gpu_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmaos_reg_ext_print(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmaos_reg_ext_size(void);
#define REG_ACCESS_GPU_PMAOS_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pmaos_reg_ext_dump(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, FILE *fd);
/* pmcr_reg_ext */
void reg_access_gpu_pmcr_reg_ext_pack(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmcr_reg_ext_unpack(struct reg_access_gpu_pmcr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmcr_reg_ext_print(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmcr_reg_ext_size(void);
#define REG_ACCESS_GPU_PMCR_REG_EXT_SIZE    (0x20)
void reg_access_gpu_pmcr_reg_ext_dump(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, FILE *fd);
/* pmlp_reg_ext */
void reg_access_gpu_pmlp_reg_ext_pack(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmlp_reg_ext_unpack(struct reg_access_gpu_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmlp_reg_ext_print(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmlp_reg_ext_size(void);
#define REG_ACCESS_GPU_PMLP_REG_EXT_SIZE    (0x40)
void reg_access_gpu_pmlp_reg_ext_dump(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, FILE *fd);
/* pmmp_reg_ext */
void reg_access_gpu_pmmp_reg_ext_pack(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_ext_unpack(struct reg_access_gpu_pmmp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmmp_reg_ext_print(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmmp_reg_ext_size(void);
#define REG_ACCESS_GPU_PMMP_REG_EXT_SIZE    (0x2c)
void reg_access_gpu_pmmp_reg_ext_dump(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, FILE *fd);
/* pmpd_reg_ext */
void reg_access_gpu_pmpd_reg_ext_pack(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmpd_reg_ext_unpack(struct reg_access_gpu_pmpd_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmpd_reg_ext_print(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmpd_reg_ext_size(void);
#define REG_ACCESS_GPU_PMPD_REG_EXT_SIZE    (0x30)
void reg_access_gpu_pmpd_reg_ext_dump(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, FILE *fd);
/* pmpr_reg_ext */
void reg_access_gpu_pmpr_reg_ext_pack(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmpr_reg_ext_unpack(struct reg_access_gpu_pmpr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmpr_reg_ext_print(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmpr_reg_ext_size(void);
#define REG_ACCESS_GPU_PMPR_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pmpr_reg_ext_dump(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, FILE *fd);
/* pmpt_reg_ext */
void reg_access_gpu_pmpt_reg_ext_pack(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmpt_reg_ext_unpack(struct reg_access_gpu_pmpt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmpt_reg_ext_print(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmpt_reg_ext_size(void);
#define REG_ACCESS_GPU_PMPT_REG_EXT_SIZE    (0x1c)
void reg_access_gpu_pmpt_reg_ext_dump(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, FILE *fd);
/* pmtm_reg_ext */
void reg_access_gpu_pmtm_reg_ext_pack(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmtm_reg_ext_unpack(struct reg_access_gpu_pmtm_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmtm_reg_ext_print(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmtm_reg_ext_size(void);
#define REG_ACCESS_GPU_PMTM_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pmtm_reg_ext_dump(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, FILE *fd);
/* pmtu_reg_ext */
void reg_access_gpu_pmtu_reg_ext_pack(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pmtu_reg_ext_unpack(struct reg_access_gpu_pmtu_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pmtu_reg_ext_print(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pmtu_reg_ext_size(void);
#define REG_ACCESS_GPU_PMTU_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pmtu_reg_ext_dump(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, FILE *fd);
/* ppaos_reg_ext */
void reg_access_gpu_ppaos_reg_ext_pack(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppaos_reg_ext_unpack(struct reg_access_gpu_ppaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppaos_reg_ext_print(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppaos_reg_ext_size(void);
#define REG_ACCESS_GPU_PPAOS_REG_EXT_SIZE    (0x10)
void reg_access_gpu_ppaos_reg_ext_dump(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, FILE *fd);
/* ppcnt_reg_ext */
void reg_access_gpu_ppcnt_reg_ext_pack(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_reg_ext_unpack(struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppcnt_reg_ext_print(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppcnt_reg_ext_size(void);
#define REG_ACCESS_GPU_PPCNT_REG_EXT_SIZE    (0x100)
void reg_access_gpu_ppcnt_reg_ext_dump(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, FILE *fd);
/* ppdfd_ext */
void reg_access_gpu_ppdfd_ext_pack(const struct reg_access_gpu_ppdfd_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppdfd_ext_unpack(struct reg_access_gpu_ppdfd_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppdfd_ext_print(const struct reg_access_gpu_ppdfd_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppdfd_ext_size(void);
#define REG_ACCESS_GPU_PPDFD_EXT_SIZE    (0xc)
void reg_access_gpu_ppdfd_ext_dump(const struct reg_access_gpu_ppdfd_ext *ptr_struct, FILE *fd);
/* pphcr_ext */
void reg_access_gpu_pphcr_ext_pack(const struct reg_access_gpu_pphcr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pphcr_ext_unpack(struct reg_access_gpu_pphcr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pphcr_ext_print(const struct reg_access_gpu_pphcr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pphcr_ext_size(void);
#define REG_ACCESS_GPU_PPHCR_EXT_SIZE    (0x50)
void reg_access_gpu_pphcr_ext_dump(const struct reg_access_gpu_pphcr_ext *ptr_struct, FILE *fd);
/* pplm_reg_ext */
void reg_access_gpu_pplm_reg_ext_pack(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pplm_reg_ext_unpack(struct reg_access_gpu_pplm_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pplm_reg_ext_print(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pplm_reg_ext_size(void);
#define REG_ACCESS_GPU_PPLM_REG_EXT_SIZE    (0x50)
void reg_access_gpu_pplm_reg_ext_dump(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, FILE *fd);
/* pplr_reg_ext */
void reg_access_gpu_pplr_reg_ext_pack(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pplr_reg_ext_unpack(struct reg_access_gpu_pplr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pplr_reg_ext_print(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pplr_reg_ext_size(void);
#define REG_ACCESS_GPU_PPLR_REG_EXT_SIZE    (0x8)
void reg_access_gpu_pplr_reg_ext_dump(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, FILE *fd);
/* pprt_reg_ext */
void reg_access_gpu_pprt_reg_ext_pack(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pprt_reg_ext_unpack(struct reg_access_gpu_pprt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pprt_reg_ext_print(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pprt_reg_ext_size(void);
#define REG_ACCESS_GPU_PPRT_REG_EXT_SIZE    (0x24)
void reg_access_gpu_pprt_reg_ext_dump(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, FILE *fd);
/* ppsc_reg_ext */
void reg_access_gpu_ppsc_reg_ext_pack(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppsc_reg_ext_unpack(struct reg_access_gpu_ppsc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppsc_reg_ext_print(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppsc_reg_ext_size(void);
#define REG_ACCESS_GPU_PPSC_REG_EXT_SIZE    (0x30)
void reg_access_gpu_ppsc_reg_ext_dump(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, FILE *fd);
/* ppslc_ext */
void reg_access_gpu_ppslc_ext_pack(const struct reg_access_gpu_ppslc_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppslc_ext_unpack(struct reg_access_gpu_ppslc_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppslc_ext_print(const struct reg_access_gpu_ppslc_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppslc_ext_size(void);
#define REG_ACCESS_GPU_PPSLC_EXT_SIZE    (0x34)
void reg_access_gpu_ppslc_ext_dump(const struct reg_access_gpu_ppslc_ext *ptr_struct, FILE *fd);
/* ppsls_ext */
void reg_access_gpu_ppsls_ext_pack(const struct reg_access_gpu_ppsls_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ppsls_ext_unpack(struct reg_access_gpu_ppsls_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ppsls_ext_print(const struct reg_access_gpu_ppsls_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ppsls_ext_size(void);
#define REG_ACCESS_GPU_PPSLS_EXT_SIZE    (0x8)
void reg_access_gpu_ppsls_ext_dump(const struct reg_access_gpu_ppsls_ext *ptr_struct, FILE *fd);
/* pptt_reg_ext */
void reg_access_gpu_pptt_reg_ext_pack(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pptt_reg_ext_unpack(struct reg_access_gpu_pptt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pptt_reg_ext_print(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pptt_reg_ext_size(void);
#define REG_ACCESS_GPU_PPTT_REG_EXT_SIZE    (0x1c)
void reg_access_gpu_pptt_reg_ext_dump(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, FILE *fd);
/* prtl_reg_ext */
void reg_access_gpu_prtl_reg_ext_pack(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_prtl_reg_ext_unpack(struct reg_access_gpu_prtl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_prtl_reg_ext_print(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_prtl_reg_ext_size(void);
#define REG_ACCESS_GPU_PRTL_REG_EXT_SIZE    (0x20)
void reg_access_gpu_prtl_reg_ext_dump(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, FILE *fd);
/* pter_reg_ext */
void reg_access_gpu_pter_reg_ext_pack(const struct reg_access_gpu_pter_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pter_reg_ext_unpack(struct reg_access_gpu_pter_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pter_reg_ext_print(const struct reg_access_gpu_pter_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pter_reg_ext_size(void);
#define REG_ACCESS_GPU_PTER_REG_EXT_SIZE    (0x20)
void reg_access_gpu_pter_reg_ext_dump(const struct reg_access_gpu_pter_reg_ext *ptr_struct, FILE *fd);
/* ptsb_ext */
void reg_access_gpu_ptsb_ext_pack(const struct reg_access_gpu_ptsb_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ptsb_ext_unpack(struct reg_access_gpu_ptsb_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ptsb_ext_print(const struct reg_access_gpu_ptsb_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ptsb_ext_size(void);
#define REG_ACCESS_GPU_PTSB_EXT_SIZE    (0x20)
void reg_access_gpu_ptsb_ext_dump(const struct reg_access_gpu_ptsb_ext *ptr_struct, FILE *fd);
/* ptsr_ext */
void reg_access_gpu_ptsr_ext_pack(const struct reg_access_gpu_ptsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ptsr_ext_unpack(struct reg_access_gpu_ptsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ptsr_ext_print(const struct reg_access_gpu_ptsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ptsr_ext_size(void);
#define REG_ACCESS_GPU_PTSR_EXT_SIZE    (0x20)
void reg_access_gpu_ptsr_ext_dump(const struct reg_access_gpu_ptsr_ext *ptr_struct, FILE *fd);
/* ptys_reg_ext */
void reg_access_gpu_ptys_reg_ext_pack(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_ptys_reg_ext_unpack(struct reg_access_gpu_ptys_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_ptys_reg_ext_print(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_ptys_reg_ext_size(void);
#define REG_ACCESS_GPU_PTYS_REG_EXT_SIZE    (0x44)
void reg_access_gpu_ptys_reg_ext_dump(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, FILE *fd);
/* pude_reg_ext */
void reg_access_gpu_pude_reg_ext_pack(const struct reg_access_gpu_pude_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_pude_reg_ext_unpack(struct reg_access_gpu_pude_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_pude_reg_ext_print(const struct reg_access_gpu_pude_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_pude_reg_ext_size(void);
#define REG_ACCESS_GPU_PUDE_REG_EXT_SIZE    (0x10)
void reg_access_gpu_pude_reg_ext_dump(const struct reg_access_gpu_pude_reg_ext *ptr_struct, FILE *fd);
/* resource_dump_ext */
void reg_access_gpu_resource_dump_ext_pack(const struct reg_access_gpu_resource_dump_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_resource_dump_ext_unpack(struct reg_access_gpu_resource_dump_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_resource_dump_ext_print(const struct reg_access_gpu_resource_dump_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_resource_dump_ext_size(void);
#define REG_ACCESS_GPU_RESOURCE_DUMP_EXT_SIZE    (0xc8)
void reg_access_gpu_resource_dump_ext_dump(const struct reg_access_gpu_resource_dump_ext *ptr_struct, FILE *fd);
/* slrg_reg_ext */
void reg_access_gpu_slrg_reg_ext_pack(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_slrg_reg_ext_unpack(struct reg_access_gpu_slrg_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_slrg_reg_ext_print(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_slrg_reg_ext_size(void);
#define REG_ACCESS_GPU_SLRG_REG_EXT_SIZE    (0x28)
void reg_access_gpu_slrg_reg_ext_dump(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, FILE *fd);
/* sltp_reg_ext */
void reg_access_gpu_sltp_reg_ext_pack(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_sltp_reg_ext_unpack(struct reg_access_gpu_sltp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_sltp_reg_ext_print(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_sltp_reg_ext_size(void);
#define REG_ACCESS_GPU_SLTP_REG_EXT_SIZE    (0x4c)
void reg_access_gpu_sltp_reg_ext_dump(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, FILE *fd);
/* reg_access_gpu_Nodes */
void reg_access_gpu_reg_access_gpu_Nodes_pack(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_gpu_reg_access_gpu_Nodes_unpack(union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_gpu_reg_access_gpu_Nodes_print(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_gpu_reg_access_gpu_Nodes_size(void);
#define REG_ACCESS_GPU_REG_ACCESS_GPU_NODES_SIZE    (0x100)
void reg_access_gpu_reg_access_gpu_Nodes_dump(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_GPU_LAYOUTS_H
