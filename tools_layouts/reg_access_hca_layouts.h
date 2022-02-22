
/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
         *** This file was generated at "2022-01-26 16:01:32"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/hca/int/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_ --no-adb-utils
         ***/
#ifndef REG_ACCESS_HCA_LAYOUTS_H
#define REG_ACCESS_HCA_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_lock_source_general_semaphore {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Resource type
0x0: QPC_GW
0x1: CQE_GW
0x2: EQE_GW
0x3: MEM_GW
0x4: IPC
Other values are reserved */
	/* 0x0.0 - 0x0.7 */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - While the stressor locks the resource, it will release it 
shortly every 2^log_toggle_cycle, given in usec. Maximal 
value is 1 sec (0x14) */
	/* 0x4.24 - 0x4.31 */
	u_int8_t log_toggle_cycle;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_lock_source_icm_resource {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - ICM resource GVMI */
	/* 0x4.0 - 0x4.15 */
	u_int16_t gvmi;
	/* Description - While the stressor locks the resource, it will release it 
shortly every 2^log_toggle_cycle, given in usec. Maximal 
value is 1 sec (0x14) */
	/* 0x4.24 - 0x4.31 */
	u_int8_t log_toggle_cycle;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - ICM resource index */
	/* 0x8.0 - 0x8.23 */
	u_int32_t index;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_lock_source_uapp_resource {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0x0: UAPP_QP
0x1: SRQ
0x2: UAPP_SRQ_META
0x3: UAPP_RES_CQ
0x4: UAPP_REQ_CQ
0x5: UAPP_EQ
0x6: NSQ
0x7: NCQ
Other values are reserved */
	/* 0x0.0 - 0x0.7 */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - uApp resource GVMI */
	/* 0x4.0 - 0x4.15 */
	u_int16_t gvmi;
	/* Description - While the stressor locks the resource, it will release it 
shortly every 2^log_toggle_cycle, given in usec. Maximal 
value is 1 sec (0x14) */
	/* 0x4.24 - 0x4.31 */
	u_int8_t log_toggle_cycle;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - uApp resource index:
for uapp QP enter QPN.
for uapp SRQ, uapp SRQ meta, UAPP CQ enter the srq index
for nvme SQ, nvme CQ enter the backend controller id */
	/* 0x8.0 - 0x8.23 */
	u_int32_t index;
};

/* Description -   */
/* Size in bytes - 28 */
union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct reg_access_hca_lock_source_general_semaphore lock_source_general_semaphore;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct reg_access_hca_lock_source_icm_resource lock_source_icm_resource;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	struct reg_access_hca_lock_source_uapp_resource lock_source_uapp_resource;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_irisc_hang_mini_flow_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bit per Irisc. When set, IRISC will hang (The miniflow does 
not release the Irisc when done) */
	/* 0x0.0 - 0x0.31 */
	u_int32_t irisc_hang_mask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit per Irisc. When set, the device supports causing the 
respective Irisc to hang using this miniflow. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t irisc_hang_cap_mask;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_lock_source_stop_toggle_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Resource type category
0x0: GENERAL_SEMAPHORE
0x1: ICM_RESOURCE
0x2: UAPP_RESOURCE
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t category;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - LOCK_RESOURCE Modifier according to category field
For GENERAL_SEMAPHORE Table  1091, "GENERAL_SEMA
PHORE Category Layout," on page  1358
For ICM_RESOURCE Table  1093, "ICM_RESOURCE Category 
Layout," on page  1359
For UAPP_RESOURCE Table  1095, "UAPP_RESOURCE Cate
gory Layout," on page  1359 */
	/* 0x4.0 - 0x1c.31 */
	union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto category_modifier;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_activation_method {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, the operation needed to move the compo
nent form ACTIVE_PENDING_RESET to ACTIVE should 
happen simultaneously on all hosts. */
	/* 0x0.0 - 0x0.0 */
	u_int8_t all_hosts_sync;
	/* Description - This component will be ACTIVE or ACTIVE_PEND
ING_RESET after the APPLY state. */
	/* 0x0.1 - 0x0.1 */
	u_int8_t auto_activate;
	/* Description - This component goes to ACTIVE_PENDING_RESET 
after activation.
A FW reset will move it to ACTIVE state. */
	/* 0x0.2 - 0x0.2 */
	u_int8_t pending_fw_reset;
	/* Description - This component goes to ACTIVE_PENDING_RESET 
state after activation.
A server reset (PCIe PERST#), will move it ACTIVE 
state. */
	/* 0x0.3 - 0x0.3 */
	u_int8_t pending_server_reboot;
	/* Description - This component goes to ACTIVE_PENDING_RESET 
state after activation.
DC power cycle (power cycle of PCI power rails), will 
move it ACTIVE state. */
	/* 0x0.4 - 0x0.4 */
	u_int8_t pending_server_dc_power_cycle;
	/* Description - This component goes to ACTIVE_PENDING_RESET 
state after activation.
AC power cycle (power cycle for both PCI power rails 
and AUX power), will move it ACTIVE state. */
	/* 0x0.5 - 0x0.5 */
	u_int8_t pending_server_ac_power_cycle;
	/* Description - When set, the component supports self activation. For 
cables, please refer to activation_type in LINKX_PROP
ERTIES data for more details. */
	/* 0x0.6 - 0x0.6 */
	u_int8_t self_activation;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask indicating which info_type(s) are supported 
for this component. Set bit indicates the property set is 
supported
bit 1: VERSION
bit 5: ACTIVATION_METHOD
Other bits are reserved. CAPABILITIES set is always 
supported. */
	/* 0x0.0 - 0x0.31 */
	u_int32_t supported_info_bitmask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The size of the component given in bytes. Value 0x0 
indicates that the size in unknown.
For some components, size may only be available in 
the READ_COMPONENT state. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t component_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Maximum size for this component, given in bytes. */
	/* 0x8.0 - 0x8.31 */
	u_int32_t max_component_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximal write size for MCDA */
	/* 0xc.0 - 0xc.15 */
	u_int16_t mcda_max_write_size;
	/* Description - Log 2 of the access word size in bytes.
Read and write access must be aligned to the word 
size. Write access must be done for an integer number 
of words. */
	/* 0xc.28 - 0xc.31 */
	u_int8_t log_mcda_word_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The device only accepts updates for this component 
that explicitly lists its base MAC and/or base GUID */
	/* 0x10.26 - 0x10.26 */
	u_int8_t match_base_guid_mac;
	/* Description - A user defined timestamp (MVTS) is active for this 
component. */
	/* 0x10.27 - 0x10.27 */
	u_int8_t check_user_timestamp;
	/* Description - PSID is validated for this component update. */
	/* 0x10.28 - 0x10.28 */
	u_int8_t match_psid;
	/* Description - Chip ID (device_hw_revision) is validated for this com
ponent update. */
	/* 0x10.29 - 0x10.29 */
	u_int8_t match_chip_id;
	/* Description - Only signed components are accepted. */
	/* 0x10.30 - 0x10.30 */
	u_int8_t signed_updates_only;
	/* Description - When set, this components may be read, see 
Section 10.3.4, "Read Flow", on page 803. */
	/* 0x10.31 - 0x10.31 */
	u_int8_t rd_en;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_linkx_properties {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bit 0: Image A is running
Bit 1: Image A is committed, module boots from image 
A
Bit 2: Image A is erased / empty
Bit 3: Reserved
Bit 4: Image B is running
Bit 5: Image B is committed, module boots from image 
B
Bit 6: Image B is erased / empty
Bit 7: Reserved */
	/* 0x0.0 - 0x0.7 */
	u_int8_t fw_image_status_bitmap;
	/* Description - Bit 0: FW image A is present 
Bit 1: FW image B is present
Bit 2: Factory / boot image is present
Bits 3-7: Reserved */
	/* 0x0.16 - 0x0.23 */
	u_int8_t fw_image_info_bitmap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Image A FW minor version */
	/* 0x4.0 - 0x4.7 */
	u_int8_t image_a_minor;
	/* Description - Image A FW major version */
	/* 0x4.8 - 0x4.15 */
	u_int8_t image_a_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Image A FW subminor number */
	/* 0x8.0 - 0x8.15 */
	u_int16_t image_a_subminor;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Image B FW minor version */
	/* 0xc.0 - 0xc.7 */
	u_int8_t image_b_minor;
	/* Description - Image B FW major version */
	/* 0xc.8 - 0xc.15 */
	u_int8_t image_b_major;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Image B FW subminor number */
	/* 0x10.0 - 0x10.15 */
	u_int16_t image_b_subminor;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Factory / boot image FW minor version */
	/* 0x14.0 - 0x14.7 */
	u_int8_t factory_image_minor;
	/* Description - Factory / boot image FW major version */
	/* 0x14.8 - 0x14.15 */
	u_int8_t factory_image_major;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Factory / boot image FW subminor number */
	/* 0x18.0 - 0x18.15 */
	u_int16_t factory_image_subminor;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - 0: Does not support either one of the FW update proce
dures defined below
1: SFF-8636 management interface and pseudo-CMIS 
FW. Update is supported
2: CMIS 4.0 is implemented */
	/* 0x1c.0 - 0x1c.5 */
	u_int8_t management_interface_protocol;
	/* Description - 0: HW reset is required. Host should be prepared to 
power cycle a cable after sending a RunFWImage com
mand.
1: Self-activation with HW reset contained in the RunF
WImage command. No additional actions required 
from the host.
2:Self-activation with hitless reset contained in the 
RunFWImage command. No additional actions 
required from the host.
3-15: Reserved */
	/* 0x1c.10 - 0x1c.13 */
	u_int8_t activation_type;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Vendor Serial Number */
	/* 0x20.0 - 0x20.15 */
	u_int16_t vendor_sn;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t version_string_length;
	/* Description - When set, the component has a valid user-defined ver
sion time-stamp in user_defined_time */
	/* 0x0.28 - 0x0.28 */
	u_int8_t user_defined_time_valid;
	/* Description - When set, the component has a valid creation time-
stamp in build_time */
	/* 0x0.29 - 0x0.29 */
	u_int8_t build_time_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Version number */
	/* 0x4.0 - 0x4.31 */
	u_int32_t version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time of component creation. Valid only if build_
time_valid is set. See Table 1847, "Date-Time Lay
out," on page 2078 */
	/* 0x8.0 - 0xc.31 */
	u_int64_t build_time;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - User-defined time assigned to the component version. 
Valid only if user_defined_time_valid is set. See 
Table 1847, "Date-Time Layout," on page 2078 */
	/* 0x10.0 - 0x14.31 */
	u_int64_t user_defined_time;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Build tool version number.
Valid only when not equal to 0 */
	/* 0x18.0 - 0x18.31 */
	u_int32_t build_tool_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - NULL terminated string representing the version. */
	/* 0x20.24 - 0x7c.23 */
	u_int8_t version_string[92];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_packet_drop_mini_flow_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of dropped packets when the Miniflow is acti
vated */
	/* 0x0.0 - 0x0.3 */
	u_int8_t num_packets;
	/* Description - Physical Port Number
1: port_number1
2: port_number2
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t port_number;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_pause_tx_stop_toggle_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - bitmap per Virtual Lane/Traffic Class
bit 0: SL_PRIO_0
bit 1: SL_PRIO_1
bit 2: SL_PRIO_2
bit 3: SL_PRIO_3
bit 4: SL_PRIO_4
bit 5: SL_PRIO_5
bit 6: SL_PRIO_6
bit 7: SL_PRIO_7
Other bits are reserved */
	/* 0x0.0 - 0x0.15 */
	u_int16_t sl_prio_mask;
	/* Description - Physical Port Number
1: port_number1
2: port_number2
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t port_number;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_rom_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Build version */
	/* 0x0.0 - 0x0.15 */
	u_int16_t build;
	/* Description - Minor version */
	/* 0x0.16 - 0x0.23 */
	u_int8_t minor;
	/* Description - Major version */
	/* 0x0.24 - 0x0.31 */
	u_int8_t major;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_rxb_hang_stop_toggle_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - bitmap per Virtual Lane/Traffic Class
bit 0: VL_TC_0
bit 1: VL_TC_1
bit 2: VL_TC_2
bit 3: VL_TC_3
bit 4: VL_TC_4
bit 5: VL_TC_5
bit 6: VL_TC_6
bit 7: VL_TC_7
bit 15: VL_TC_15
Other bits are reserved */
	/* 0x0.0 - 0x0.15 */
	u_int16_t vl_tc_mask;
	/* Description - Physical Port Number
1: port_number1
2: port_number2
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t port_number;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_rxp_hang_stop_toggle_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - bitmap per Virtual Lane/Traffic Class
bit 0: VL_TC_0
bit 1: VL_TC_1
bit 2: VL_TC_2
bit 3: VL_TC_3
bit 4: VL_TC_4
bit 5: VL_TC_5
bit 6: VL_TC_6
bit 7: VL_TC_7
bit 15: VL_TC_15
Other bits are reserved */
	/* 0x0.0 - 0x0.15 */
	u_int16_t vl_tc_mask;
	/* Description - Port number access type. must be set to 0x2  */
	/* 0x0.16 - 0x0.17 */
	u_int8_t pnat;
	/* Description - Physical Port Number
1: port_number1
2: port_number2
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t port_number;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_sxp_hang_stop_toggle_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Physical Port Number
1: port_number1
2: port_number2
Other values are reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t port_number;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_diagnostic_cntr_layout {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Diagnostic counter identifier. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t counter_id;
	/* Description - The counter might be used as Synced Start Diagnostics 
Counters */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sync;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_fpga_shell_caps {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Total size of shared QP buffer size in granularity of 2 KB. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t total_rcv_credits;
	/* Description - Maximum number of supported QPs. */
	/* 0x0.16 - 0x0.31 */
	u_int16_t max_num_qps;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If set, RC transport service is supported. */
	/* 0x4.0 - 0x4.0 */
	u_int8_t rc;
	/* Description - If set, UC transport service is supported. */
	/* 0x4.1 - 0x4.1 */
	u_int8_t uc;
	/* Description - If set, UD transport service is supported. */
	/* 0x4.2 - 0x4.2 */
	u_int8_t ud;
	/* Description - If set, DC transport service is supported. */
	/* 0x4.3 - 0x4.3 */
	u_int8_t dc;
	/* Description - If set, RDMA READ operation is supported. */
	/* 0x4.8 - 0x4.8 */
	u_int8_t rre;
	/* Description - If set, RDMA WRITE operation is supported. */
	/* 0x4.9 - 0x4.9 */
	u_int8_t rwe;
	/* Description - If set, RDMA atomic operation is supported. */
	/* 0x4.10 - 0x4.10 */
	u_int8_t rae;
	/* Description - Bit mask indicates which QP types are supported
Bit 0: Shell_qp - Shell QP supported
Bit 1: Sandbox_qp - Sandbox QP supported */
	/* 0x4.16 - 0x4.17 */
	u_int8_t qp_type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log (base 2) of the DDR size in granularity of GB. */
	/* 0x8.0 - 0x8.5 */
	u_int8_t log_ddr_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The maximum size of message size supported by FPGA 
Shell QP. */
	/* 0xc.0 - 0xc.31 */
	u_int32_t max_fpga_qp_msg_size;
};

/* Description -   */
/* Size in bytes - 124 */
union reg_access_hca_mcqi_reg_data_auto {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_cap mcqi_cap;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_version mcqi_version;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_activation_method mcqi_activation_method;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_linkx_properties mcqi_linkx_properties;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_mgir_dev_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [Internal]: The tag for the dev branch should be <fea
ture>_YYYY.
The format of the string represented by ASCII. */
	/* 0x0.24 - 0x1c.23 */
	u_int8_t dev_branch_tag[28];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_mgir_fw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_sub_minor. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t sub_minor;
	/* Description - Minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_minor. */
	/* 0x0.8 - 0x0.15 */
	u_int8_t minor;
	/* Description - Major firmware version number.
Deprecated and returns '0'. 
Refer to extended_major. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t major;
	/* Description - When set, the device is running firmware with 
secure-firmware updates capabilities. */
	/* 0x0.24 - 0x0.24 */
	u_int8_t secured;
	/* Description - When set the device is running a signed FW binaries. */
	/* 0x0.25 - 0x0.25 */
	u_int8_t signed_fw;
	/* Description - When set, the device is running a debug firmware. 
'debug' binary can only be installed on specific 
devices (identified by their 'Factory base MAC'), 
which currently run a specific firmware version. 
These restrictions are expressed by a signed 'debug' 
token that must be loaded to the device before 
installing the debug binary. */
	/* 0x0.26 - 0x0.26 */
	u_int8_t debug;
	/* Description - When set, the device is running a development firm
ware version. */
	/* 0x0.27 - 0x0.27 */
	u_int8_t dev;
	/* Description - When set, string-TLV is supported. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t string_tlv;
	u_int8_t dev_sc;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Firmware Build ID. Optional. . */
	/* 0x4.0 - 0x4.31 */
	u_int32_t build_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 
0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.0 - 0x8.15 */
	u_int16_t year;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 
0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.16 - 0x8.23 */
	u_int8_t day;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 
0x05, Day= 0x03, and Year= 0x04 */
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
	/* Description - User-configured version number of the current INI 
file. */
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
	/* Description - FW version's SubMinor field in extended (32b) for
mat. */
	/* 0x2c.0 - 0x2c.31 */
	u_int32_t extended_sub_minor;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x30.15 */
	u_int16_t isfu_major;
	/* Description - Bitmap representing the disabled tiles in the ASIC. 
Tile '0' is represented by the msb bit. 
If a bit is set to '1', the corresponding tile is disabled. 
The total number of tiles can be derived through 
MGPIR register. */
	/* 0x30.16 - 0x30.31 */
	u_int16_t disabled_tiles_bitmap;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - 0: Production
1: GA Secured
2: GA Non-Secured
3: RMA */
	/* 0x34.0 - 0x34.1 */
	u_int8_t life_cycle;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.2 - 0x34.2 */
	u_int8_t sec_boot;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.3 - 0x34.3 */
	u_int8_t encryption;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mgir_hardware_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PCI device ID. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t device_id;
	/* Description - 
SwitchX Devices:
0x00A0: Device step A0, FCC package
0x00A1: Device step A1, FCC package
0x00A2: Device step A2, FCC package

Switch-IB Devices:
0x00A0: Switch-IB device step A0, FCC package
0x0000 is a valid value for some devices not included 
in PRM. */
	/* 0x0.16 - 0x0.31 */
	u_int16_t device_hw_revision;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Process Voltage Scaling
Supported nominal V_CORE voltage (in 50mV units) 
for the device. */
	/* 0x4.0 - 0x4.4 */
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
	u_int8_t technology;
	/* Description - Number of physical port the device supports. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t num_ports;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The PCI device-ID of the NIC/HCA in recovery (Live
fish) mode. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t hw_dev_id;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - MSB of the "base" MAC address of the NIC that was 
allocate during manufacturing. The NIC derives the 
MAC addresses for the different PCI PFs from this 
MAC address. This parameter can be used as a 
canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not 
supported. */
	/* 0x10.0 - 0x10.15 */
	u_int16_t manufacturing_base_mac_47_32;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - LSB of the "base" MAC address of the NIC that was 
allocate during manufacturing. The NIC derives the 
MAC addresses for the different PCI PFs from this 
MAC address. This parameter can be used as a 
canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not 
supported. */
	/* 0x14.0 - 0x14.31 */
	u_int32_t manufacturing_base_mac_31_0;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in secs.) since last reset0 */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t uptime;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mgir_sw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor Driver version number.
 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t sub_minor;
	/* Description - Minor Driver version number.
 */
	/* 0x0.8 - 0x0.15 */
	u_int8_t minor;
	/* Description - Major Driver version number.
 */
	/* 0x0.16 - 0x0.23 */
	u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - ROM 3 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP */
	/* 0x4.0 - 0x4.3 */
	u_int8_t rom3_type;
	/* Description - Arch type of ROM 3:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting 
both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.4 - 0x4.7 */
	u_int8_t rom3_arch;
	/* Description - ROM 2type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP */
	/* 0x4.8 - 0x4.11 */
	u_int8_t rom2_type;
	/* Description - Arch type of ROM 2:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting 
both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.12 - 0x4.15 */
	u_int8_t rom2_arch;
	/* Description - ROM 1type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP */
	/* 0x4.16 - 0x4.19 */
	u_int8_t rom1_type;
	/* Description - Arch type of ROM 1:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting 
both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.20 - 0x4.23 */
	u_int8_t rom1_arch;
	/* Description - ROM 0 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP */
	/* 0x4.24 - 0x4.27 */
	u_int8_t rom0_type;
	/* Description - Arch type of ROM 0:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting 
both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.28 - 0x4.31 */
	u_int8_t rom0_arch;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - ROM 0 version. */
	/* 0x8.0 - 0x8.31 */
	struct reg_access_hca_rom_version rom0_version;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ROM 1 version. */
	/* 0xc.0 - 0xc.31 */
	struct reg_access_hca_rom_version rom1_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - ROM 2version. */
	/* 0x10.0 - 0x10.31 */
	struct reg_access_hca_rom_version rom2_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - ROM 3 version. */
	/* 0x14.0 - 0x14.31 */
	struct reg_access_hca_rom_version rom3_version;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_smbus_failed_fault_inject_modifier {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - SMBUS GW identifier */
	/* 0x0.0 - 0x0.7 */
	u_int8_t smbus_gw;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_string_db_parameters {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Offset of the first string of the section, relative to the entire 
string data base, given in bytes. */
	/* 0x0.0 - 0x0.31 */
	u_int32_t string_db_base_address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Size of string database section, given in bytes */
	/* 0x4.0 - 0x4.23 */
	u_int32_t string_db_size;
};

/* Description -   */
/* Size in bytes - 32 */
union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_irisc_hang_mini_flow_modifier irisc_hang_mini_flow_modifier;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_packet_drop_mini_flow_modifier packet_drop_mini_flow_modifier;
};

/* Description -   */
/* Size in bytes - 32 */
union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_rxb_hang_stop_toggle_modifier rxb_hang_stop_toggle_modifier;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_lock_source_stop_toggle_modifier lock_source_stop_toggle_modifier;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_sxp_hang_stop_toggle_modifier sxp_hang_stop_toggle_modifier;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_rxp_hang_stop_toggle_modifier rxp_hang_stop_toggle_modifier;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_pause_tx_stop_toggle_modifier pause_tx_stop_toggle_modifier;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_debug_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The maximum number of samples that can be stored on 
the device's sampling buffer is 2^ log_max_samples in 
counters unit (i.e. 100 will represent the ability to store 
100 samples of single counter, 50 samples of 2 counters, 
etc). */
	/* 0x0.0 - 0x0.7 */
	u_int8_t log_max_samples;
	/* Description - Log(base 2) of the the recommended minimal size of eq to 
handle the resource_dump_event */
	/* 0x0.16 - 0x0.20 */
	u_int8_t log_min_resource_dump_eq;
	/* Description - If set, Resource_dump register is supported.
See Table 1115, "RESOURCE_DUMP Register Layout," on 
page 1369 */
	/* 0x0.22 - 0x0.22 */
	u_int8_t resource_dump;
	/* Description - Log(base 2) of the size in granularity of 4KB to be allo
cated by host in order to accommodate cr_dump.
0 means feature is not supported.
See Table 1113, "CORE_DUMP Register Layout," on 
page 1367 */
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
	/* Description - The minimal sample period is 2^ log_min_smaple_period 
in device clocks. Clock rate of the device is reported by 
HCA_CAP.device_frequency_khz. */
	/* 0x4.0 - 0x4.7 */
	u_int8_t log_min_sample_period;
	/* Description - If set, the device supports dumping the diagnostic count
ers reports into the tracer buffer. */
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
	/* Description - List of counters supported. Number of counters reported 
by num_of_counters. */
	/* 0x40.0 - 0x40.31 */
	struct reg_access_hca_diagnostic_cntr_layout *diagnostic_counter;
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_hca_fpga_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - FPGA device type
0x0: UNKNOWN_DEVICE
0x1: KU040
0x2: KU060
0x3: KU060_2 */
	/* 0x0.0 - 0x0.23 */
	u_int32_t fpga_device;
	/* Description - FPGA identifier.
0x0: Newton_X
0x1: Edison */
	/* 0x0.24 - 0x0.31 */
	u_int8_t fpga_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Shell registers space file version. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t register_file_ver;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Indicates the MODIFY operation's permissions of FPGA_AC
CESS_REG.
0x0: Not_allowed - modify registers by FPGA_ACCESS_REG 
not allowed.
0x1: All_range_allowed- modify registers by FPGA_AC
CESS_REG allowed for all addresses. */
	/* 0x8.16 - 0x8.17 */
	u_int8_t access_reg_modify_mode;
	/* Description - Indicates the QUERY operation's permissions of FPGA_AC
CESS_REG.
0x0: Not_allowed - Query registers by FPGA_ACCESS_REG 
not allowed.
0x1: All_range_allowed- Query registers by FPGA_AC
CESS_REG allowed for all addresses. */
	/* 0x8.24 - 0x8.25 */
	u_int8_t access_reg_query_mode;
	/* Description - If set, DISCONNECT and CONNECT operations in FPGA_C
TRL are supported. */
	/* 0x8.29 - 0x8.29 */
	u_int8_t disconnect_fpga;
	/* Description - If set, Flash_GW_Lock and Flash_GW_UnLock operations in 
FPGA_CTRL are supported. */
	/* 0x8.30 - 0x8.30 */
	u_int8_t flash_gw_lock;
	/* Description - If set, SW is allowed to modify FPGA_CTRL register. See 
Table  1073, "FPGA_CTRL Register Layout," on page  1346 */
	/* 0x8.31 - 0x8.31 */
	u_int8_t fpga_ctrl_modify;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Image version. */
	/* 0x10.0 - 0x10.31 */
	u_int32_t image_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Creation date of current running image.
Format: DDMMYYYY.
For example:
0x12011995 means 12/01/1995 in DD/MM/YY. */
	/* 0x14.0 - 0x14.31 */
	u_int32_t image_date;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Creation time of current running image.
Format: 00HHMMSS.
For example:
0x00015324 means 01:53:24 in HH:MM:SS */
	/* 0x18.0 - 0x18.31 */
	u_int32_t image_time;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Shell image version. */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t shell_version;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Shell capabilities. */
	/* 0x30.0 - 0x6c.31 */
	struct reg_access_hca_fpga_shell_caps shell_caps;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - IEEE Vendor ID of sandbox user.
0x2C9: Mellanox */
	/* 0x70.0 - 0x70.23 */
	u_int32_t ieee_vendor_id;
/*---------------- DWORD[29] (Offset 0x74) ----------------*/
	/* Description - Sandbox product ID.
For Mellanox sandbox products
0x0: unknown
0x1: example
0x2: IPsec
0x3: TLS */
	/* 0x74.0 - 0x74.15 */
	u_int16_t sandbox_product_id;
	/* Description - Sandbox version. */
	/* 0x74.16 - 0x74.31 */
	u_int16_t sandbox_product_version;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description - Sandbox basic capabilities per sandbox product ID.
For Mellanox sandbox products, see Table  965, "IPsec_Basic_Ca
pabilities Structure Layout," on page  1236. */
	/* 0x78.0 - 0x78.31 */
	u_int32_t sandbox_basic_caps;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - The length (in DWORDs) of sandbox extended capability 
(equals 0 when such capability is not present). */
	/* 0x7c.0 - 0x7c.15 */
	u_int16_t sandbox_extended_caps_len;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Extended capabilities address.
For Mellanox sandbox products, see Table  967, "IPsec_Extend
ed_Capabilities Structure Layout," on page  1236. */
	/* 0x80.0 - 0x84.31 */
	u_int64_t sandbox_extended_caps_addr;
/*---------------- DWORD[34] (Offset 0x88) ----------------*/
	/* Description - Start address of DDR */
	/* 0x88.0 - 0x8c.31 */
	u_int64_t fpga_ddr_start_addr;
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - Start address of cr-space */
	/* 0x90.0 - 0x94.31 */
	u_int64_t fpga_cr_space_start_addr;
/*---------------- DWORD[38] (Offset 0x98) ----------------*/
	/* Description - Size of DDR in a granularity of 1KB */
	/* 0x98.0 - 0x98.31 */
	u_int32_t fpga_ddr_size;
/*---------------- DWORD[39] (Offset 0x9c) ----------------*/
	/* Description - Size of cr-space in a granularity of 1KB */
	/* 0x9c.0 - 0x9c.31 */
	u_int32_t fpga_cr_space_size;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_fpga_ctrl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Status of the last operation.
0x0: Success
0x1: Failure
0x2: In_progress
0x3: DISCONNECTED - FPGA is disconnect by DOSCONNECT 
operation.
Valid only for query operation. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t status;
	/* Description - Indicates the control operation to be performed. Allowed 
only when FPGA_CAP.fpga_ctrl_modify==1. Table  1069, 
"FPGA_CAP Register Layout," on page  1341.
0x1: LOAD - when set, the FPGA will be forced to reload the 
image from flash according to image_select_admin value.
0x2: RESET - when set, the FPGA internal logic state 
(BRAMs, FFs, etc.) will be reset to the original state at load
ing time.
0x3: FLASH_SELECT - when set, map the flash GW accord
ing to flash_select_admin value.
0x4: Sandbox_Bypass_On - If set, sandbox logic is inactive 
until Sandbox_Bypass_Off is set. Packets will skip the sand
box logic.
0x5: Sandbox_Bypass_Off - If set, sandbox logic is active. 
Packets will be processed by the sandbox logic.
0x6: Reset_Sandbox - If set, the FPGA sandbox logic state 
(BRAMs, FFs, etc.) will be reset to the original state at load
ing time (no shell state is affected).
0x7: Flash_GW_Lock - lock the flash gateway. Users must 
take this lock before attempting to reads/writes to flash. 
Supported only when FPGA_CAP.flash_gw_lock==1.
0x8: Flash_GW_Unlock - Unlock flash gateway. Users must 
release this lock after completing their reads/writes to flash. 
Supported only when FPGA_CAP.flash_gw_lock==1.
0x9: DISCONNECT - Disable the ConnectX to FPGA manage
ment interface. This mode is useful when upgrading the 
FPGA via JTAG. supported only when FPGA_CAP.discon
nect_fpga==1. Note that on this mode no other operation can 
be performed on the FPGA.
0xA: CONNECT - Enable the ConnectX to FPGA management 
interface.supported only when FPGA_CAP.disconnect_f
pga==1. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t operation;
	/* Description - Error type. Valid only when status = failure(0x1)
0x0: Error_unknown
0x1: fpga_done_timeout
0x2: gpio_sig_mismatch
0x3: ddr_bist_timeout
0x4: sadb_reset_done_timeout
0x5: sadb_reset_success_timeout
0x6: ips_flush_done_timeout
0x7: flash_gw_lock_timeout
0x8: flash_gw_unlock_error
0x9: i2c_access_during_fpga_load
0xA: fpga_user_img_done_timeout */
	/* 0x0.24 - 0x0.31 */
	u_int8_t error_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Current flashthat is used to loadimages to FPGA.
0x0: User
0x1: Factory_default
0x2: Factory_failover - The device tried to load the user 
image, but due to a failure loaded the factory image.
Valid only if status is ok. */
	/* 0x4.0 - 0x4.7 */
	u_int8_t flash_select_oper;
	/* Description - Used to select next flash to be usedto load the images.
0x0: User
0x1: Factory_default
Valid only for FLASH_SELECT and LOAD operations. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t flash_select_admin;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mcc_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Command to be executed by the FSM
0x1: LOCK_UPDATE_HANDLE
0x2: RELEASE_UPDATE_HANDLE 
0x3: UPDATE_COMPONENT
0x4: VERIFY_COMPONENT
0x5: ACTIVATE_COMPONENET 
0x6: ACTIVATE
0x7: READ_COMPONENT
0x8: CANCEL
0x9: CHECK_UPDATE_HANDLE
0xA: FORCE_HANDLE_RELEASE
0xB: READ_PENDING_COMPONENT
0xC: DOWNSRTEAM_DEVICE_TRANSFER
Other values are reserved. Applicable for write opera
tion only. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t instruction;
	/* Description - This is a configuration that delays the activation of the 
component in seconds. Relevant only for activate com
mand.
This configuration is volatile. */
	/* 0x0.8 - 0x0.15 */
	u_int8_t activation_delay_sec;
	/* Description - The number of seconds elapsed since the update_han
dle owner last issued a command. The time saturates 
at 0xFFF. */
	/* 0x0.16 - 0x0.27 */
	u_int16_t time_elapsed_since_last_cmd;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Index of the accessed component. Valid for 
UPDATE_COMPONENT, ACTIVATE_COMPONENET, 
READ_COMPONENT and READ_PENDING_COMPO
NENT instructions. Otherwise, this field is reserved. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t component_index;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Token representing the current flow executed by the 
FSM.
See Section 10.2.1, "Component Update State", on 
page 800. */
	/* 0x8.0 - 0x8.23 */
	u_int32_t update_handle;
	/* Description - Auto-update to all matching downstream devices is 
requested. */
	/* 0x8.31 - 0x8.31 */
	u_int8_t auto_update;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Current Update FSM state, See Section 10.3.8, "FSM 
States", on page 804
0x0: IDLE
0x1: LOCKED
0x2: INITIALIZE
0x3: DOWNLOAD
0x4: VERIFY
0x5: APPLY
0x6: ACTIVATE
0x7: UPLOAD
0x8: UPLOAD_PENDING
0x9: DOWNSRTEAM_DEVICE_TRANSFER
Other values are reserved */
	/* 0xc.0 - 0xc.3 */
	u_int8_t control_state;
	/* Description - Indicates the successful completion of the instruction, 
or the reason it failed. See Section 10.3.7, "Error 
Handling", on page 803
0x0: OK
0x1: ERROR
0x2: REJECTED_DIGEST_ERR
0x3: REJECTED_NOT_APPLICABLE
0x4: REJECTED_UNKNOWN_KEY
0x5: REJECTED_AUTH_FAILED
0x6: REJECTED_UNSIGNED
0x7: REJECTED_KEY_NOT_APPLICABLE
0x8: REJECTED_BAD_FORMAT
0x9: BLOCKED_PENDING_RESET
0xA: REJECTED_NOT_A_SECURED_FW
0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED
0xC: REJECTED_NO_DEBUG_TOKEN
0xD: REJECTED_VERSION_NUM_MISMATCH
0xE: REJECTED_USER_TIMESTAMP_MISMATCH
0xF: REJECTED_FORBIDDEN_VERSION
0x10: FLASH_ERASE_ERROR
0x11: REJECTED_REBURN_RUNNING_AND_RETRY
0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED
0x13: REJECTED_HOST_STORAGE_IN_USE
0x14: REJECTED_LINKX_TRANSFER (see module 
index in rejected_device_index)
0x15: REJECTED_LINKX_ACTIVATE (see module index 
in rejected_device_index)
0x16: REJECTED_TOKEN_ALREADY_APPLIED
Other values should be treated as an unknown error. */
	/* 0xc.8 - 0xc.15 */
	u_int8_t error_code;
	/* Description - Indicates the estimated progress status of the current 
operation executed by the FSM. Valid values are 0..100.
101 indicates that progress reporting is not supported 
for this update state. */
	/* 0xc.16 - 0xc.22 */
	u_int8_t control_progress;
	/* Description - For handle_owner_type BMC, command-interface and 
ICMD, indicates the identifier of the host of the handle 
owner.
Otherwise reserved */
	/* 0xc.24 - 0xc.27 */
	u_int8_t handle_owner_host_id;
	/* Description - Type of entity holding the update handle:
0x0: unspecified
0x1: Chassis BMC
0x2: MAD
0x3: BMC
0x4: command interface
0x5: ICMD 
Other values are reserved. */
	/* 0xc.28 - 0xc.31 */
	u_int8_t handle_owner_type;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Component size in bytes. 
Valid for UPDATE_COMPONENT instruction. Specifying 
the size may shorten the update time.
Value 0x0 means that size is unspecified. */
	/* 0x10.0 - 0x10.31 */
	u_int32_t component_size;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Peripheral device type:
0: Switch_or_NIC
1: Gearbox */
	/* 0x14.0 - 0x14.7 */
	u_int8_t device_type;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index 
starting at index 1. Index 0 indicates the host device. */
	/* 0x14.16 - 0x14.27 */
	u_int16_t device_index;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - In multiple downstream devices action, the action will 
be executed starting on device_index and ending on 
device_index + device_index_size - 1. */
	/* 0x18.0 - 0x18.11 */
	u_int16_t device_index_size;
	/* Description - The device index that the action has been rejected to. */
	/* 0x18.16 - 0x18.27 */
	u_int16_t rejected_device_index;
};

/* Description -   */
/* Size in bytes - 144 */
struct reg_access_hca_mcda_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Update handle registered when the FSM was activated. */
	/* 0x0.0 - 0x0.23 */
	u_int32_t update_handle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Offset of accessed address relative to component start. 
Accesses must be in accordance to log_mcda_word_
size in Table 1843, "MCQI CAPABILITIES Info Lay
out," on page 2075 */
	/* 0x4.0 - 0x4.31 */
	u_int32_t offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the data accessed, given in bytes */
	/* 0x8.0 - 0x8.15 */
	u_int16_t size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Data block accessed */
	/* 0x10.0 - 0x8c.31 */
	u_int32_t data[32];
};

/* Description -   */
/* Size in bytes - 148 */
struct reg_access_hca_mcqi_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component index gathered by "MCQS - Management 
Component Query Status" */
	/* 0x0.0 - 0x0.15 */
	u_int16_t component_index;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index 
starting at index 1. Index 0 indicates the host device. */
	/* 0x0.16 - 0x0.27 */
	u_int16_t device_index;
	/* Description - When set, the register will return information about 
the pending component (if available) */
	/* 0x0.31 - 0x0.31 */
	u_int8_t read_pending_component;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Peripheral device type:
0: Switch / NIC
1: Gearbox */
	/* 0x4.0 - 0x4.7 */
	u_int8_t device_type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component properties set.
0x0: CAPABILITIES
0x1: VERSION
0x5: ACTIVATION_METHOD
0x6: LINKX_PROPERTIES
Other values are reserved */
	/* 0x8.0 - 0x8.4 */
	u_int8_t info_type;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Properties set structure size, given in bytes. */
	/* 0xc.0 - 0xc.31 */
	u_int32_t info_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The requested/returned data offset from the section 
start, given in bytes.
Must be DWORD aligned. */
	/* 0x10.0 - 0x10.31 */
	u_int32_t offset;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The requested/returned data size, given in bytes.
If data_size is not DWORD aligned, the last bytes are 
zero padded. */
	/* 0x14.0 - 0x14.15 */
	u_int16_t data_size;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Properties set structure according to info_type.
CAPABILITIES - See Table 1843, "MCQI CAPABILI
TIES Info Layout," on page 2075
VERSION - See Table 1845, "MCQI VERSION Info 
Layout," on page 2077
ACTIVATION_METHOD - See Table 1849, "MCQI 
ACTIVATION_METHOD Info Layout," on page 2079
LINKX_PREPERTIES - See Table 1851, "MCQI 
LINKX_PROPERTIES Info Layout," on page 2080 */
	/* 0x18.0 - 0x90.31 */
	union reg_access_hca_mcqi_reg_data_auto data;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mcqs_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component Index. Values range from 1 to the last 
component indicated by last_index_flag. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t component_index;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index 
starting at index 1. Index 0 indicates the host device. */
	/* 0x0.16 - 0x0.27 */
	u_int16_t device_index;
	/* Description - When set, this component is the last component (high
est component_index). */
	/* 0x0.31 - 0x0.31 */
	u_int8_t last_index_flag;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field uniquely identifies a specific component type. 
0x1: BOOT_IMG
0x4: OEM_NVCONFIG
0x5: MLNX_NVCONFIG
0x6: CS_TOKEN
0x7: DBG_TOKEN
0xA: Gearbox
0xB: CC_ALGO - Congestion Control Algorithm
0xC: LINKX_IMG
0xD: CRYPTO_TO_COMMISSIONING
0xE: RMCS_TOKEN
0xF: RMDT_TOKEN
Other values are reserved */
	/* 0x4.0 - 0x4.15 */
	u_int16_t identifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component state in update flow, see Section 10.2.1, 
"Component Update State", on page 800:
0x0: IDLE
0x1: IN_PROGRESS
0x2: APPLIED
0x3: ACTIVE 
0x4: ACTIVE_PENDING_RESET
0x5: FAILED
0x6: CANCELED
0x7: BUSY

Other values are reserved */
	/* 0x8.0 - 0x8.3 */
	u_int8_t component_update_state;
	/* Description - The status of the component:
0x0: NOT_PRESENT - The component is supported by 
the device but, currently not present
0x1: PRESENT - This component is present. For down
stream devices link LinkX component, this is an indica
tion that the binary image is present at the host device 
memory.
0x2: IN_USE - The component is present and currently 
in use. */
	/* 0x8.4 - 0x8.8 */
	u_int8_t component_status;
	/* Description - Progress in percentage (from 0 to 100). This field is 
only relevant for cables. */
	/* 0x8.9 - 0x8.15 */
	u_int8_t progress;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Peripheral device type:
0: Switch_or_NIC
1: Gearbox */
	/* 0xc.0 - 0xc.7 */
	u_int8_t device_type;
	/* Description - For last_update_state_changer_type BMC, command-
interface and ICMD, indicates the identifier of the host 
of the handle owner. Otherwise reserved. */
	/* 0xc.24 - 0xc.27 */
	u_int8_t last_update_state_changer_host_id;
	/* Description - Indicates which entity was the last to change the com
ponent_update_state of this component.
0x0: unspecified
0x1: Chassis_BMC
0x2: MAD
0x3: BMC
0x4: command_interface
0x5: ICMD

Other values are reserved */
	/* 0xc.28 - 0xc.31 */
	u_int8_t last_update_state_changer_type;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mfrl_reg_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The firmware reset trigger. 
Only a single bit may be set.
Bit 0: TRIGGER0 (live-patch)
Bit 3: TRIGGER3 (PCIe link toggle)
Bit 6: TRIGGER6 (PERST)
Other bits are reserved. */
	/* 0x4.0 - 0x4.7 */
	u_int8_t reset_trigger;
	/* Description - Each bit represents a chip reset type.
If set to '1', the reset is supported. 
Bit 0: Full chip reset
Bit 1: Keep network port active during reset
 */
	/* 0x4.8 - 0x4.15 */
	u_int8_t reset_type;
	/* Description - The requested reset type. */
	/* 0x4.24 - 0x4.26 */
	u_int8_t rst_type_sel;
	/* Description - Response of the driver for the reset request.
1: Acknowledgment
2: Dis-acknowledgment
3: Reserved */
	/* 0x4.27 - 0x4.28 */
	u_int8_t pci_sync_for_fw_update_resp;
	/* Description - Setting this bit to '1' will request a synced driver flow and '0' 
for the legacy flow.
Synced driver flow will not require to issue MFRL command 
from other hosts (x86 / ARM for SoC) */
	/* 0x4.29 - 0x4.29 */
	u_int8_t pci_sync_for_fw_update_start;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_hca_mfsv_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When this bit is set, it indicates that it is allowed for the boot 
FW to program the FW security version related EFUSEs if 
needed. This bit is not relevant in case the FW operates in an 
automatically EFUSEs programming approach (set in the INI 
file). Once set to 1, this configuration will be relevant only for 
the upcoming boot, thus this configuration will be set back to 
0 upon next boot. In addition, once this bit was set to 1 there 
is no option to clear it. option to clear it. In addition, once this 
bit was set to 1, there is no option to clear it. */
	/* 0x0.0 - 0x0.0 */
	u_int8_t efuses_prog_en;
	/* Description - Firmware security version status.
0: EFUSEs value is equal to the currently running FW image 
value. No change is needed.
1: EFUSEs value is smaller than the currently running FW 
image value. An update to the EFUSEs is required.
2-3: Reserved */
	/* 0x0.1 - 0x0.2 */
	u_int8_t fw_sec_ver_stat;
	/* Description - EFUSEs programming method.
0: manually. Upon boot, if FW indicates that 
FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will 
program the EFUSEs as needed.
1: automatically. Upon boot, if FW indicates that 
FW_sec_ver_stat is 1, it will program the EFUSEs as needed. */
	/* 0x0.3 - 0x0.3 */
	u_int8_t efuses_prog_method;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Image security version value */
	/* 0x4.0 - 0x4.31 */
	u_int32_t img_sec_ver;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - EFUSEs security version value */
	/* 0x8.0 - 0x8.31 */
	u_int32_t efuses_sec_ver;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_hca_mgir {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see Table 1732, "Hardware Info 
Layout," on page 1994 */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_mgir_hardware_info hw_info;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Firmware Information, see Table 1734, "Firmware Info 
Layout," on page 1996 */
	/* 0x20.0 - 0x5c.31 */
	struct reg_access_hca_mgir_fw_info fw_info;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Software Information, see Table 1736, "Software Info Lay
out," on page 1998
This field indicates the oldest software version compati
ble with the current firmware */
	/* 0x60.0 - 0x7c.31 */
	struct reg_access_hca_mgir_sw_info sw_info;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description -  */
	/* 0x80.0 - 0x98.31 */
	struct reg_access_hca_mgir_dev_info dev_info;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_mmdio {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - NOP
1 - Address (reserved for Clause 22)
2 - Read
3 - Write
4 - Post Read Increment Address (reserved for Clause 22)
6 - Address + Read - Generates Address cycle and then 
Read cycle in Clause 45 (reserved for Clause 22)
7 - Address + Write - Generates Address cycle and then 
Write cycle in Clause 45 (reserved for Clause 22) */
	/* 0x0.0 - 0x0.2 */
	u_int8_t operation;
	/* Description - MDIO Definition:
0 - Clause 22
1 - Clause 45 */
	/* 0x0.8 - 0x0.9 */
	u_int8_t clause;
	/* Description - Selection of the MDIO interface */
	/* 0x0.16 - 0x0.19 */
	u_int8_t mdio_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reg Address (Clause 22) / Dev Type (Clause 45) */
	/* 0x4.0 - 0x4.4 */
	u_int8_t reg_adr;
	/* Description - PHY Address (PHYAD) */
	/* 0x4.8 - 0x4.12 */
	u_int8_t phy_adr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Data (Clause 22) / Address/Data (Clause 45) */
	/* 0x8.0 - 0x8.15 */
	u_int16_t data;
	/* Description - Address (Clause 45)
This field is only valid for Address + Read and Address + 
Write operations, providing the address. For other Clause 45 
operations the data field provides the address when appro
priate. */
	/* 0x8.16 - 0x8.31 */
	u_int16_t address;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mpcir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set to '01', activates the flow of preparation for FW ISSU, on 
all services. The values in op-codes for "per-service" are 
ignored.
If set to '10', returns to operational state on all services. The 
values in op-codes for "per-service" are ignored.
11 - Reserved */
	/* 0x0.30 - 0x0.31 */
	u_int8_t all;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - For each of the services, the following operations are avail
able:
0: N/A (no action)
1: start preparation flow for FW ISSU 
2: return to operational service (end of FW ISSU flow)
3: get status

When set to '3', the current status will appear in correspond
ing _stat fields. */
	/* 0x4.0 - 0x4.1 */
	u_int8_t ports;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Status for each of the services. 
0: not in FW ISSU flow state (FW ISSU flow is not initiated) 
1: done with preparations for FW ISSU flow
2: Preparation for FW ISSU flow started but FW still not done 
service handling [Internal]: busy with some other critical 
flow).
For not implemented services on a particular system, the 
status should be '1'. */
	/* 0xc.0 - 0xc.1 */
	u_int8_t ports_stat;
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_hca_mpegc_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	u_int8_t node;
	/* Description - PCIe index number (Internal domain index)
Reserved when access is from the host */
	/* 0x0.16 - 0x0.23 */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	u_int8_t depth;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Field select indicated which writable fields to modify.
Bit 0: tx_lossy_overflow_oper
Bit 1 : outbound_stalled_reads_th
Bit 2 :outbound_stalled_writes_th
Bit 3 : tx_overflow_sense
Bit 4 : mark_tx_action_cqe
Bit 5 : mark_tx_action_cnp
Bit 6: virtual_hot_plug_unplug (supported only for internal 
host) */
	/* 0x4.0 - 0x4.15 */
	u_int16_t field_select;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - When overflow encountered for lossy packets, it will be 
dropped or marked and will be counted in "tx_over
flow_buffer_dropped_pkt" or "tx_over
flow_buffer_marked_pkt" counter.
00 - Disabled
01 - drop - overflow traffic will be dropped.  
10 - mark - overflow traffic will be marked in the CE field in the 
CqE.  Supported only when MCAM.mark_tx_action_cqe or 
MCAM.mark_tx_action_cnp are '1'. 
 */
	/* 0x8.0 - 0x8.1 */
	u_int8_t tx_lossy_overflow_oper;
	/* Description - When this bit is set, the marking action will be generating a 
CNP for RoCE traffic. Supported only when MCAM.mark_tx
_action_cnp is '1'. */
	/* 0x8.29 - 0x8.29 */
	u_int8_t mark_cnp;
	/* Description - When this bit is set, the marking action will be set in the CqE 
for TCP traffic. Supported only when MCAM.mark_tx_ac
tion_cqe is '1'. */
	/* 0x8.30 - 0x8.30 */
	u_int8_t mark_cqe;
	/* Description - Set the sensibility level of the tx overflow mechanism. 
0 - Aggressive 1 - Dynamic adjustment. When tx_lossy_over
flow_oper is disabled, tx_overflow_sense must be disabled. 
Supported only when MCAM.dynamic_tx_oveflow is '1'. */
	/* 0x8.31 - 0x8.31 */
	u_int8_t tx_overflow_sense;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Each time that the counter outbound_stalled_writes will 
exceed this threshold, will be counted in the counter out
bound_stalled_writes_events - range 0   100. */
	/* 0xc.0 - 0xc.6 */
	u_int8_t outbound_stalled_writes_th;
	/* Description - Each time that the counter outbound_stalled_reads will 
exceed this threshold, will be counted in the counter out
bound_stalled_reads_events - range 0   100. */
	/* 0xc.8 - 0xc.14 */
	u_int8_t outbound_stalled_reads_th;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Operation to perform
0: Idle - no operation required (default)
1: Emulate hot removal
2: Emulate hot insertion
3-15: Reserved */
	/* 0x10.16 - 0x10.19 */
	u_int8_t operation;
	/* Description - Operation completion status
0: Operation in process
1: Unplugged
2: Plugged
3: Warning - disconnecting an already disconnected bus can
not be performed
4: Warning - connecting an already connected bus cannot be 
performed
5: Error - unknown bus number or no device installed on 
selected bus */
	/* 0x10.24 - 0x10.31 */
	u_int8_t status;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_hca_mqis_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Type of information string to be queried:
0x0: VPD - Read the PCI Vital Product Data capability 
content.
0x1: MODEL_NAME
0x2: MODEL_DESCRIPTION
0x3: IMAGE_VSD
0x4: DEVICE_VSD
0x5: ROM_INFO
other values are reserved. */
	/* 0x0.0 - 0x0.7 */
	u_int8_t info_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Total size of the information string, according to info_
type. Value given in bytes. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t info_length;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes requested. The device returns the 
number of bytes actually read. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t read_length;
	/* Description - Offset in bytes of the first byte requested to read. */
	/* 0x8.16 - 0x8.31 */
	u_int16_t read_offset;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Information string accessed, according to info_type. If 
the information is not available, a NULL string is 
returned. */
	/* 0x10.24 - 0x18.23 */
	u_int8_t info_string[8];
};

/* Description -   */
/* Size in bytes - 132 */
struct reg_access_hca_mtrc_cap_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of different string sections building the database */
	/* 0x0.0 - 0x0.3 */
	u_int8_t num_string_db;
	/* Description - Indicates the version of the tracing mechanism.
See, Section 27.3.4.1, "Timestamp Event Traces", on 
page 1283
0x0: VER_0
0x1: VER_1
other values are reserved */
	/* 0x0.24 - 0x0.25 */
	u_int8_t trc_ver;
	/* Description - When set the device supports logging traces to memory */
	/* 0x0.30 - 0x0.30 */
	u_int8_t trace_to_memory;
	/* Description - Write 0x1 to register for tracer ownership, write 0x0 to de-
register.
Read value 0x1 indicates tracer ownership is granted */
	/* 0x0.31 - 0x0.31 */
	u_int8_t trace_owner;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The number of consecutive event_id that should be inter
preted as a string trace */
	/* 0x4.16 - 0x4.23 */
	u_int8_t num_string_trace;
	/* Description - The lowest event_id that should be interpreted as a string 
trace */
	/* 0x4.24 - 0x4.31 */
	u_int8_t first_string_trace;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log 2 of the maximal size of the trace buffer given in units of 
4KB */
	/* 0x8.0 - 0x8.7 */
	u_int8_t log_max_trace_buffer_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - String DB section parameters. */
	/* 0x10.0 - 0x4c.31 */
	struct reg_access_hca_string_db_parameters string_db_param[8];
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mtrc_stdb_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of bytes to read from the String DB. The num
ber of bytes must:
Be a multiple of 64B
Not exceed the String DB section (with start_offset)
Not exceed the limitations defined by the medium carrying the 
Register. */
	/* 0x0.0 - 0x0.23 */
	u_int32_t read_size;
	/* Description - The section of the String DB being accessed */
	/* 0x0.28 - 0x0.31 */
	u_int8_t string_db_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The offset in the String DB to read from, given in Bytes. The 
offset must:
Be a multiple of 64B
Not exceed the String DB section (with read_size) */
	/* 0x4.0 - 0x4.31 */
	u_int32_t start_offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Strings from the database. The size of this field is defined by 
read_size */
	/* 0x8.0 - 0x8.31 */
	u_int32_t *string_db_data;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_pcnr_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When Set, port will override tuning process upon fol
lowing link-up command (PAOS.admin_status = UP)
Cleared by FW once PAOS.admin_status = UP com
mand is set.

The register can be set only when port operational 
status is UP (PAOS.oper_status=0x1) 

NOTE: if physical environment was changed (i.e. 
replacement of module, temp change, etc) there is a 
possibility that link won't be established or will be 
established with high BER */
	/* 0x0.0 - 0x0.0 */
	u_int8_t tuning_override;
	/* Description - When set, a toggle of the link will force a fast link-up 
flow and no reset of the chip will be needed. The pur
pose of that feature is for debug. */
	/* 0x0.1 - 0x0.1 */
	u_int8_t force_fast_link_up;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t local_port;
	/* Description - 0 - Ready
1 - Phy characteristics store flow in progress */
	/* 0x0.28 - 0x0.31 */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - When Set, The port will keep the same phy setting 
upon link down event that occurs only upon link down 
command of peer port. In the event of Down com
mand/cable disconnect, entire link up flow will be ini
tialized.

NOTE: This mode can be configured only when 
PTYS.an_disable_admin is set (i.e. AN is disabled). 
NOTE: if physical environment was changed (i.e. 
replacement of module, temp change, etc) there is a 
possibility that link won't be established or will be 
established with high BER */
	/* 0x4.0 - 0x4.0 */
	u_int8_t keep_phy_setting;
	/* Description - Fast Link-up On Toggle capability.
When set to '1', the system supports fast link-up (less 
than 1 sec) in case of link toggle without unplugging 
the cable. The enabling of that feature is possible 
through NV-Config. */
	/* 0x4.1 - 0x4.1 */
	u_int8_t flot_cap;
	/* Description - Fast Link-up On Toggle Invalidation. 
When set, on the next link toggle, the value in the NV-
Config bit of Fast Link-up On Toggle feature will be 
neglected and a regular (long) link-up will be per
formed. Used for debug. */
	/* 0x4.2 - 0x4.2 */
	u_int8_t flot_invalidation;
	/* Description - Disable Force Fast Link-Up */
	/* 0x4.3 - 0x4.3 */
	u_int8_t flu_disable;
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_hca_resource_dump {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - See Section 24.8, "Resource Dump", on page 1299. */
	/* 0x0.0 - 0x0.15 */
	u_int16_t segment_type;
	/* Description - Sequence number. 0 on first call of dump and incre
mented on each more dump. */
	/* 0x0.16 - 0x0.19 */
	u_int8_t seq_num;
	/* Description - If set, then vhca_id field is valid. Otherwise dump 
resources on my vhca_id. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t vhca_id_valid;
	/* Description - If set, data is dumped in the register in inline_data 
field. otherwise dump to mkey. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t inline_dump;
	/* Description - If set, the device has additional information that has 
not been dumped yet. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t more_dump;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - vhca_id where the resource is allocated. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t vhca_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - First object index to be dumped when supported by 
the object.
SW shall read this field upon command done and 
shall provide it on the next call in case 
dump_more==1. */
	/* 0x8.0 - 0x8.31 */
	u_int32_t index1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Second object index to be dumped when supported 
by the object.
SW shall read this field upon command done and 
shall provide it on the next call in case 
dump_more==1. */
	/* 0xc.0 - 0xc.31 */
	u_int32_t index2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The amount of objects to dump starting for index 2.
SW shall read this field upon command done and 
shall provide it on the next call in case 
dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_
obj2_supports_all is set, the special value of 0xffff 
represents "all". When the segment's num_of_objx_
supports_active is set, the special value of 0xfffe rep
resents "active". The  value of 0x0 and 0x1 are 
allowed even if the supported_num_of_obj2 is "0". */
	/* 0x10.0 - 0x10.15 */
	u_int16_t num_of_obj2;
	/* Description - The amount of objects to dump starting for index 1
SW shall read this field upon command done and 
shall provide it on the next call in case 
dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_
obj1_supports_all is set, the special value of 0xffff 
represents "all". When the segment's num_of_objx_
supports_active is set, the special value of 0xfffe rep
resents "active". The  value of 0x0 and 0x1 are 
allowed even if the supported_num_of_obj1 is "0". */
	/* 0x10.16 - 0x10.31 */
	u_int16_t num_of_obj1;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - An opaque provided by the device. SW shall read the 
device_opaque upon command done and shall pro
vide it on the next call in case dump_more==1. On 
first call, device_opaque shall be 0. */
	/* 0x18.0 - 0x1c.31 */
	u_int64_t device_opaque;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Memory key to dump to. 
Valid when inline_dump==0. */
	/* 0x20.0 - 0x20.31 */
	u_int32_t mkey;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - In write, the size of maximum allocated buffer that 
the device can use.
In read, the actual written size.
In granularity of Bytes. */
	/* 0x24.0 - 0x24.31 */
	u_int32_t size;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - VA address (absolute address) of memory where to 
start dumping. 
Valid when inline_dump==0. */
	/* 0x28.0 - 0x2c.31 */
	u_int64_t address;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Data that is dumped in case of inline mode.
Valid when inline_dump==1. */
	/* 0x30.0 - 0xfc.31 */
	u_int32_t inline_data[52];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_strs_fault_inject_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Stesser of this type is was active at some point in history */
	/* 0x0.29 - 0x0.29 */
	u_int8_t past_active;
	/* Description - Stesser of this type is currently active */
	/* 0x0.30 - 0x0.30 */
	u_int8_t active;
	/* Description - Stesser of this type is supported */
	/* 0x0.31 - 0x0.31 */
	u_int8_t supported;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type of fault to activate
0x0: ICM_ALLOC_REFUSE - cause FW to return FAIL on ICM 
allocation requests
0x1: ICM_ALLOC_BUSY - cause FW to return BUSY on ICM 
allocation request
0x2: EQE_GW_BUSY - cause FW to return busy when trying 
to access EQE GW
0x3: CQE_GW_BUSY - cause FW to return busy when trying 
to access CQE GW
0x4: RX_FENCE_BUSY - cause FW to return busy when 
checking RX fences done
0x5: SX_FENCE_BUSY - cause FW to return busy when 
checking SX fences done
0x6: RXT_SLICE_FENCE_BUSY - cause FW to return busy 
when checking RXT fences done
0x7: SXD_SLICE_FENCE_BUSY - cause FW to return busy 
when checking SXD fences done
0x8: GENERAL_FENCE_BUSY - cause FW to return busy 
when checking other fences done
0x9: SMBUS_FAILED - cause FW to indicate failure upon ini
tiating SMBus transaction
Other values are reserved */
	/* 0x4.0 - 0x4.7 */
	u_int8_t type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The fault will be injected num_repeat consecutive times the 
relevant flow is called, and will not be injected for the follow
ing num_skip calls to the relevant flow.
Value 0x0 for num_repeat indicates the Fault will not be 
injected. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t num_skip;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The fault will be injected num_repeat consecutive times the 
relevant flow is called, and will not be injected for the follow
ing num_skip calls to the relevant flow.
Value 0x0 for num_repeat indicates the Fault will not be 
injected. */
	/* 0xc.0 - 0xc.15 */
	u_int16_t num_repeat;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - stressor Modifier according to type field.
For SMBUS_FAILED,Table  1101, "SMBUS_FAILED Fault 
Inject Modifier Layout," on page  1363 */
	/* 0x10.0 - 0x2c.31 */
	struct reg_access_hca_smbus_failed_fault_inject_modifier per_type_modifier;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_strs_mini_flow_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Stesser of this type is was active at some point in history */
	/* 0x0.29 - 0x0.29 */
	u_int8_t past_active;
	/* Description - Stesser of this type is currently active */
	/* 0x0.30 - 0x0.30 */
	u_int8_t active;
	/* Description - Stesser of this type is supported */
	/* 0x0.31 - 0x0.31 */
	u_int8_t supported;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type of Mini Flow to activate
0x0: SX_FLICK_THROTTLE - enable / disable the SX flick 
mechanism
0x1: INVALIDATE_STEERING_CACHE
0x2: INVALIDATE_RXT_QP_L0_CACHE
0x3: INVALIDATE_DCT_L0_CACHE
0x4: INVALIDATE_LDB_REQSL_CACHE
0x5: INVALIDATE_RXC_CACHE
0x6: INVALIDATE_SXDC_CACHE
0x7: RECONSTRUCT_STEERING_BYPASS
0x8: INVALIDATE_LDB_CACHE
0x9: PCI_READ_ERROR - simulate a PCI error on Px polling 
machine read
0xA: INVALIDATE_ALL_RO_CACHES
0xB: INVALIDATE_PKEY_CACHE
0xC: INVALIDATE_GUID_CACHE
0xD: INVALIDATE_PORT_INFO_CACHE
0xE: INVALIDATE_QP_CACHE
0xF: IRISC_HANG
0x10: PACKET_DROP
Other values are reserved */
	/* 0x4.0 - 0x4.7 */
	u_int8_t type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The Mini flow will be injected num_repeat times, every 50 
usec * freq.
Value 0x0 for freq indicates the Mini Flow will not be injected. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t freq;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The Mini flow will be injected num_repeat times, every 50 
usec * freq.
Value 0x0 for freq indicates the Mini Flow will not be injected. */
	/* 0xc.0 - 0xc.15 */
	u_int16_t num_repeat;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - stressor Modifier according to type field.
For IRISC_HANG Table  1105, "IRISC_HANG Mini-Flow Modi
fier Layout," on page  1364
For PACKET_DROP Table  1107, "PACKET_DROP Mini-Flow 
Modifier Layout," on page  1365 */
	/* 0x10.0 - 0x2c.31 */
	union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto per_type_modifier;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_strs_resource_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Stesser of this type is was active at some point in history */
	/* 0x0.29 - 0x0.29 */
	u_int8_t past_active;
	/* Description - Stesser of this type is currently active */
	/* 0x0.30 - 0x0.30 */
	u_int8_t active;
	/* Description - Stesser of this type is supported */
	/* 0x0.31 - 0x0.31 */
	u_int8_t supported;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type of resource to limit
0x0: SX_SLICE
0x1: RX_SLICE
Other values are reserved */
	/* 0x4.0 - 0x4.7 */
	u_int8_t type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Limit as a percentage of the available resources
Value of 100 (0x64) indicates return to full utilization */
	/* 0x8.0 - 0x8.31 */
	u_int32_t reduce_percentage;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_strs_stop_toggle_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Stesser of this type is was active at some point in history */
	/* 0x0.29 - 0x0.29 */
	u_int8_t past_active;
	/* Description - Stesser of this type is currently active */
	/* 0x0.30 - 0x0.30 */
	u_int8_t active;
	/* Description - Stesser of this type is supported */
	/* 0x0.31 - 0x0.31 */
	u_int8_t supported;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Type of mechanism to toggle
0x0: DC_CNAK - stop FW machine which sends DC CNAK 
packets on DC LIFO empty
0x1: RXT_CHECKS - stop FW machine which handles RX 
transport check traps
0x2: TIMEOUT - stop FW machine which handles QP trans
port timeout events
0x3: SX_ERROR - stop FW machine which handles SX WQE 
or data gather errors
0x4: RX_ERROR - stop FW machine which handles all RX 
errors apart from RXT checks
0x5: MX_ERROR - stop FW machine which handles other 
transport errors, such as data signature error
0x6: MAD_TRAP - stop FW machine which sends MAD trap 
packets
0x7: RXT_SLICE - stop HW which loads RXT unit from RX 
buffers
0x8: QOS_ARBITER - stop HW which servers schedule queue 
pops / flicks
0x9: RXB_HANG - stop HW which loads RX buffers - per port 
/ VL configuration
0xA: FW_SCHED_Q - stop FW machine which empties the 
FW schedule queue
0xB: LOCK_RESOURCE - stop FW machines attempting to 
take semaphores
0xC: IRISC_HANG - stop all FW processing
0xD: SXW_SLICE - stop HW SXW slices from executing WQE 
requests
0xE: RXC_CQE - stop HW posting CQEs
0xF: RXC_EQE - stop HW posting EQEs
0x10: SXP_HANG - stop HW SX from transmitting packets
0x11: SX_EXT_DB - stop HW processing of external door
bells (schedule queue push)
0x12: SX_INT_DB - stop HW processing of internal doorbells 
(responder ack / read response requests)
0x13: QPC_SLICE - stop HW QP context read requests
Other values are reserved
0x14: RXB_HOST_HANG - Stop HW which loads RX buffers - 
per host / VL configuration. When supported deprecates 
RXB_HANG
0x15 : PAUSE_TX - generates pause frames toward the net
work - per port & SL/priority configuration. */
	/* 0x4.0 - 0x4.7 */
	u_int8_t type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The Stressor will be active for 50usec * 2^log_stressor 
period, once every 50usec * 2^log_duty_cycle. */
	/* 0x8.0 - 0x8.4 */
	u_int8_t log_stressor;
	/* Description - The Stressor will be active for 50usec * 2^log_stressor 
period, once every 50usec * 2^log_duty_cycle. */
	/* 0x8.8 - 0x8.12 */
	u_int8_t log_duty_cycle;
	/* Description - Indicates how the Stressor affects the device during the 
Stressor active time. 
0x0: FLOW_STOPPED - HW/FW flow is stressed
0x1: FLOW_ACTIVE - HW/FW is flow is working normally
The Stressor will have the opposite behavior when it is not 
active. */
	/* 0x8.31 - 0x8.31 */
	u_int8_t polarity;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - stressor Modifier according to type field.
For RXB_HANG Table  1083, "RXB_HANG Stop Toggle Modi
fier Layout," on page  1355
For LOCK_RESOURCE Table  1089, "LOCK_RESOURCE Stop 
Toggle Modifier Layout," on page  1357
For SXP_HANG Table  1085, "SXP_HANG Stop Toggle Modi
fier Layout," on page  1356
For RXB_HOST_HANG Table  1087, "RXB_HOST_HANG Stop 
Toggle Modifier Layout," on page  1357
For PAUSE_TX See Table Table  1097, "PAUSE_TX Stop Tog
gle Modifier Layout," on page  1360 */
	/* 0x10.0 - 0x2c.31 */
	union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto per_type_modifier;
};

/* Description -   */
/* Size in bytes - 256 */
union reg_access_hca_reg_access_hca_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct reg_access_hca_mcqs_reg mcqs_reg;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_linkx_properties mcqi_linkx_properties;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_activation_method mcqi_activation_method;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct reg_access_hca_mtrc_stdb_reg mtrc_stdb_reg;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct reg_access_hca_strs_fault_inject_reg strs_fault_inject_reg;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	struct reg_access_hca_resource_dump resource_dump;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct reg_access_hca_pcnr_reg pcnr_reg;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct reg_access_hca_mmdio mmdio;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	struct reg_access_hca_mfsv_reg mfsv_reg;
	/* Description -  */
	/* 0x0.0 - 0x8c.31 */
	struct reg_access_hca_mcda_reg mcda_reg;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct reg_access_hca_fpga_ctrl fpga_ctrl;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	struct reg_access_hca_mtrc_cap_reg mtrc_cap_reg;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	struct reg_access_hca_mpegc_reg mpegc_reg;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	struct reg_access_hca_fpga_cap fpga_cap;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct reg_access_hca_mfrl_reg_ext mfrl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	struct reg_access_hca_mcqi_reg mcqi_reg;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_hca_mcc_reg mcc_reg;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct reg_access_hca_strs_mini_flow_reg strs_mini_flow_reg;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_cap mcqi_cap;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	struct reg_access_hca_mqis_reg mqis_reg;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct reg_access_hca_mpcir_ext mpcir_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct reg_access_hca_strs_resource_reg strs_resource_reg;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	struct reg_access_hca_debug_cap debug_cap;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	struct reg_access_hca_mgir mgir;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	struct reg_access_hca_mcqi_version mcqi_version;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct reg_access_hca_strs_stop_toggle_reg strs_stop_toggle_reg;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* lock_source_general_semaphore */
void reg_access_hca_lock_source_general_semaphore_pack(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lock_source_general_semaphore_unpack(struct reg_access_hca_lock_source_general_semaphore *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lock_source_general_semaphore_print(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lock_source_general_semaphore_size(void);
#define REG_ACCESS_HCA_LOCK_SOURCE_GENERAL_SEMAPHORE_SIZE    (0x1c)
void reg_access_hca_lock_source_general_semaphore_dump(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, FILE *fd);
/* lock_source_icm_resource */
void reg_access_hca_lock_source_icm_resource_pack(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lock_source_icm_resource_unpack(struct reg_access_hca_lock_source_icm_resource *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lock_source_icm_resource_print(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lock_source_icm_resource_size(void);
#define REG_ACCESS_HCA_LOCK_SOURCE_ICM_RESOURCE_SIZE    (0x1c)
void reg_access_hca_lock_source_icm_resource_dump(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, FILE *fd);
/* lock_source_uapp_resource */
void reg_access_hca_lock_source_uapp_resource_pack(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lock_source_uapp_resource_unpack(struct reg_access_hca_lock_source_uapp_resource *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lock_source_uapp_resource_print(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lock_source_uapp_resource_size(void);
#define REG_ACCESS_HCA_LOCK_SOURCE_UAPP_RESOURCE_SIZE    (0x1c)
void reg_access_hca_lock_source_uapp_resource_dump(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, FILE *fd);
/* lock_source_stop_toggle_modifier_category_modifier_auto */
void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_pack(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_unpack(union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_print(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_size(void);
#define REG_ACCESS_HCA_LOCK_SOURCE_STOP_TOGGLE_MODIFIER_CATEGORY_MODIFIER_AUTO_SIZE    (0x1c)
void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_dump(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_hca_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_uint64_size(void);
#define REG_ACCESS_HCA_UINT64_SIZE    (0x8)
void reg_access_hca_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* irisc_hang_mini_flow_modifier */
void reg_access_hca_irisc_hang_mini_flow_modifier_pack(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_irisc_hang_mini_flow_modifier_unpack(struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_irisc_hang_mini_flow_modifier_print(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_irisc_hang_mini_flow_modifier_size(void);
#define REG_ACCESS_HCA_IRISC_HANG_MINI_FLOW_MODIFIER_SIZE    (0x20)
void reg_access_hca_irisc_hang_mini_flow_modifier_dump(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, FILE *fd);
/* lock_source_stop_toggle_modifier */
void reg_access_hca_lock_source_stop_toggle_modifier_pack(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lock_source_stop_toggle_modifier_unpack(struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lock_source_stop_toggle_modifier_print(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lock_source_stop_toggle_modifier_size(void);
#define REG_ACCESS_HCA_LOCK_SOURCE_STOP_TOGGLE_MODIFIER_SIZE    (0x20)
void reg_access_hca_lock_source_stop_toggle_modifier_dump(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, FILE *fd);
/* mcqi_activation_method */
void reg_access_hca_mcqi_activation_method_pack(const struct reg_access_hca_mcqi_activation_method *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_activation_method_unpack(struct reg_access_hca_mcqi_activation_method *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_activation_method_print(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_activation_method_size(void);
#define REG_ACCESS_HCA_MCQI_ACTIVATION_METHOD_SIZE    (0x7c)
void reg_access_hca_mcqi_activation_method_dump(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE *fd);
/* mcqi_cap */
void reg_access_hca_mcqi_cap_pack(const struct reg_access_hca_mcqi_cap *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_cap_unpack(struct reg_access_hca_mcqi_cap *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_cap_print(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_cap_size(void);
#define REG_ACCESS_HCA_MCQI_CAP_SIZE    (0x7c)
void reg_access_hca_mcqi_cap_dump(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE *fd);
/* mcqi_linkx_properties */
void reg_access_hca_mcqi_linkx_properties_pack(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_linkx_properties_unpack(struct reg_access_hca_mcqi_linkx_properties *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_linkx_properties_print(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_linkx_properties_size(void);
#define REG_ACCESS_HCA_MCQI_LINKX_PROPERTIES_SIZE    (0x7c)
void reg_access_hca_mcqi_linkx_properties_dump(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, FILE *fd);
/* mcqi_version */
void reg_access_hca_mcqi_version_pack(const struct reg_access_hca_mcqi_version *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_version_unpack(struct reg_access_hca_mcqi_version *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_version_print(const struct reg_access_hca_mcqi_version *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_version_size(void);
#define REG_ACCESS_HCA_MCQI_VERSION_SIZE    (0x7c)
void reg_access_hca_mcqi_version_dump(const struct reg_access_hca_mcqi_version *ptr_struct, FILE *fd);
/* packet_drop_mini_flow_modifier */
void reg_access_hca_packet_drop_mini_flow_modifier_pack(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_packet_drop_mini_flow_modifier_unpack(struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_packet_drop_mini_flow_modifier_print(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_packet_drop_mini_flow_modifier_size(void);
#define REG_ACCESS_HCA_PACKET_DROP_MINI_FLOW_MODIFIER_SIZE    (0x20)
void reg_access_hca_packet_drop_mini_flow_modifier_dump(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, FILE *fd);
/* pause_tx_stop_toggle_modifier */
void reg_access_hca_pause_tx_stop_toggle_modifier_pack(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pause_tx_stop_toggle_modifier_unpack(struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pause_tx_stop_toggle_modifier_print(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pause_tx_stop_toggle_modifier_size(void);
#define REG_ACCESS_HCA_PAUSE_TX_STOP_TOGGLE_MODIFIER_SIZE    (0x20)
void reg_access_hca_pause_tx_stop_toggle_modifier_dump(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, FILE *fd);
/* rom_version */
void reg_access_hca_rom_version_pack(const struct reg_access_hca_rom_version *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_rom_version_unpack(struct reg_access_hca_rom_version *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_rom_version_print(const struct reg_access_hca_rom_version *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_rom_version_size(void);
#define REG_ACCESS_HCA_ROM_VERSION_SIZE    (0x4)
void reg_access_hca_rom_version_dump(const struct reg_access_hca_rom_version *ptr_struct, FILE *fd);
/* rxb_hang_stop_toggle_modifier */
void reg_access_hca_rxb_hang_stop_toggle_modifier_pack(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_rxb_hang_stop_toggle_modifier_unpack(struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_rxb_hang_stop_toggle_modifier_print(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_rxb_hang_stop_toggle_modifier_size(void);
#define REG_ACCESS_HCA_RXB_HANG_STOP_TOGGLE_MODIFIER_SIZE    (0x20)
void reg_access_hca_rxb_hang_stop_toggle_modifier_dump(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, FILE *fd);
/* rxp_hang_stop_toggle_modifier */
void reg_access_hca_rxp_hang_stop_toggle_modifier_pack(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_rxp_hang_stop_toggle_modifier_unpack(struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_rxp_hang_stop_toggle_modifier_print(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_rxp_hang_stop_toggle_modifier_size(void);
#define REG_ACCESS_HCA_RXP_HANG_STOP_TOGGLE_MODIFIER_SIZE    (0x20)
void reg_access_hca_rxp_hang_stop_toggle_modifier_dump(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd);
/* sxp_hang_stop_toggle_modifier */
void reg_access_hca_sxp_hang_stop_toggle_modifier_pack(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_sxp_hang_stop_toggle_modifier_unpack(struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_sxp_hang_stop_toggle_modifier_print(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_sxp_hang_stop_toggle_modifier_size(void);
#define REG_ACCESS_HCA_SXP_HANG_STOP_TOGGLE_MODIFIER_SIZE    (0x20)
void reg_access_hca_sxp_hang_stop_toggle_modifier_dump(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd);
/* diagnostic_cntr_layout */
void reg_access_hca_diagnostic_cntr_layout_pack(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_diagnostic_cntr_layout_unpack(struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_diagnostic_cntr_layout_print(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_diagnostic_cntr_layout_size(void);
#define REG_ACCESS_HCA_DIAGNOSTIC_CNTR_LAYOUT_SIZE    (0x4)
void reg_access_hca_diagnostic_cntr_layout_dump(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd);
/* fpga_shell_caps */
void reg_access_hca_fpga_shell_caps_pack(const struct reg_access_hca_fpga_shell_caps *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_fpga_shell_caps_unpack(struct reg_access_hca_fpga_shell_caps *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_fpga_shell_caps_print(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_fpga_shell_caps_size(void);
#define REG_ACCESS_HCA_FPGA_SHELL_CAPS_SIZE    (0x40)
void reg_access_hca_fpga_shell_caps_dump(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE *fd);
/* mcqi_reg_data_auto */
void reg_access_hca_mcqi_reg_data_auto_pack(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_data_auto_unpack(union reg_access_hca_mcqi_reg_data_auto *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_data_auto_print(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_reg_data_auto_size(void);
#define REG_ACCESS_HCA_MCQI_REG_DATA_AUTO_SIZE    (0x7c)
void reg_access_hca_mcqi_reg_data_auto_dump(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, FILE *fd);
/* mgir_dev_info */
void reg_access_hca_mgir_dev_info_pack(const struct reg_access_hca_mgir_dev_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_dev_info_unpack(struct reg_access_hca_mgir_dev_info *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_dev_info_print(const struct reg_access_hca_mgir_dev_info *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_dev_info_size(void);
#define REG_ACCESS_HCA_MGIR_DEV_INFO_SIZE    (0x1c)
void reg_access_hca_mgir_dev_info_dump(const struct reg_access_hca_mgir_dev_info *ptr_struct, FILE *fd);
/* mgir_fw_info */
void reg_access_hca_mgir_fw_info_pack(const struct reg_access_hca_mgir_fw_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_fw_info_unpack(struct reg_access_hca_mgir_fw_info *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_fw_info_print(const struct reg_access_hca_mgir_fw_info *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_fw_info_size(void);
#define REG_ACCESS_HCA_MGIR_FW_INFO_SIZE    (0x40)
void reg_access_hca_mgir_fw_info_dump(const struct reg_access_hca_mgir_fw_info *ptr_struct, FILE *fd);
/* mgir_hardware_info */
void reg_access_hca_mgir_hardware_info_pack(const struct reg_access_hca_mgir_hardware_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_hardware_info_unpack(struct reg_access_hca_mgir_hardware_info *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_hardware_info_print(const struct reg_access_hca_mgir_hardware_info *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_hardware_info_size(void);
#define REG_ACCESS_HCA_MGIR_HARDWARE_INFO_SIZE    (0x20)
void reg_access_hca_mgir_hardware_info_dump(const struct reg_access_hca_mgir_hardware_info *ptr_struct, FILE *fd);
/* mgir_sw_info */
void reg_access_hca_mgir_sw_info_pack(const struct reg_access_hca_mgir_sw_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_sw_info_unpack(struct reg_access_hca_mgir_sw_info *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_sw_info_print(const struct reg_access_hca_mgir_sw_info *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_sw_info_size(void);
#define REG_ACCESS_HCA_MGIR_SW_INFO_SIZE    (0x20)
void reg_access_hca_mgir_sw_info_dump(const struct reg_access_hca_mgir_sw_info *ptr_struct, FILE *fd);
/* smbus_failed_fault_inject_modifier */
void reg_access_hca_smbus_failed_fault_inject_modifier_pack(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_smbus_failed_fault_inject_modifier_unpack(struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_smbus_failed_fault_inject_modifier_print(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_smbus_failed_fault_inject_modifier_size(void);
#define REG_ACCESS_HCA_SMBUS_FAILED_FAULT_INJECT_MODIFIER_SIZE    (0x20)
void reg_access_hca_smbus_failed_fault_inject_modifier_dump(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, FILE *fd);
/* string_db_parameters */
void reg_access_hca_string_db_parameters_pack(const struct reg_access_hca_string_db_parameters *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_string_db_parameters_unpack(struct reg_access_hca_string_db_parameters *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_string_db_parameters_print(const struct reg_access_hca_string_db_parameters *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_string_db_parameters_size(void);
#define REG_ACCESS_HCA_STRING_DB_PARAMETERS_SIZE    (0x8)
void reg_access_hca_string_db_parameters_dump(const struct reg_access_hca_string_db_parameters *ptr_struct, FILE *fd);
/* strs_mini_flow_reg_per_type_modifier_auto */
void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_pack(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_unpack(union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_print(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_size(void);
#define REG_ACCESS_HCA_STRS_MINI_FLOW_REG_PER_TYPE_MODIFIER_AUTO_SIZE    (0x20)
void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_dump(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, FILE *fd);
/* strs_stop_toggle_reg_per_type_modifier_auto */
void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_pack(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_unpack(union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_print(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_size(void);
#define REG_ACCESS_HCA_STRS_STOP_TOGGLE_REG_PER_TYPE_MODIFIER_AUTO_SIZE    (0x20)
void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_dump(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, FILE *fd);
/* debug_cap */
void reg_access_hca_debug_cap_pack(const struct reg_access_hca_debug_cap *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_debug_cap_unpack(struct reg_access_hca_debug_cap *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_debug_cap_print(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_debug_cap_size(void);
#define REG_ACCESS_HCA_DEBUG_CAP_SIZE    (0x40)
void reg_access_hca_debug_cap_dump(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd);
/* fpga_cap */
void reg_access_hca_fpga_cap_pack(const struct reg_access_hca_fpga_cap *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_fpga_cap_unpack(struct reg_access_hca_fpga_cap *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_fpga_cap_print(const struct reg_access_hca_fpga_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_fpga_cap_size(void);
#define REG_ACCESS_HCA_FPGA_CAP_SIZE    (0x100)
void reg_access_hca_fpga_cap_dump(const struct reg_access_hca_fpga_cap *ptr_struct, FILE *fd);
/* fpga_ctrl */
void reg_access_hca_fpga_ctrl_pack(const struct reg_access_hca_fpga_ctrl *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_fpga_ctrl_unpack(struct reg_access_hca_fpga_ctrl *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_fpga_ctrl_print(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_fpga_ctrl_size(void);
#define REG_ACCESS_HCA_FPGA_CTRL_SIZE    (0x10)
void reg_access_hca_fpga_ctrl_dump(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE *fd);
/* mcc_reg */
void reg_access_hca_mcc_reg_pack(const struct reg_access_hca_mcc_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcc_reg_unpack(struct reg_access_hca_mcc_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcc_reg_print(const struct reg_access_hca_mcc_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcc_reg_size(void);
#define REG_ACCESS_HCA_MCC_REG_SIZE    (0x20)
void reg_access_hca_mcc_reg_dump(const struct reg_access_hca_mcc_reg *ptr_struct, FILE *fd);
/* mcda_reg */
void reg_access_hca_mcda_reg_pack(const struct reg_access_hca_mcda_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcda_reg_unpack(struct reg_access_hca_mcda_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcda_reg_print(const struct reg_access_hca_mcda_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcda_reg_size(void);
#define REG_ACCESS_HCA_MCDA_REG_SIZE    (0x90)
void reg_access_hca_mcda_reg_dump(const struct reg_access_hca_mcda_reg *ptr_struct, FILE *fd);
/* mcqi_reg */
void reg_access_hca_mcqi_reg_pack(const struct reg_access_hca_mcqi_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_unpack(struct reg_access_hca_mcqi_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_print(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_reg_size(void);
#define REG_ACCESS_HCA_MCQI_REG_SIZE    (0x94)
void reg_access_hca_mcqi_reg_dump(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE *fd);
/* mcqs_reg */
void reg_access_hca_mcqs_reg_pack(const struct reg_access_hca_mcqs_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqs_reg_unpack(struct reg_access_hca_mcqs_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqs_reg_print(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqs_reg_size(void);
#define REG_ACCESS_HCA_MCQS_REG_SIZE    (0x10)
void reg_access_hca_mcqs_reg_dump(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE *fd);
/* mfrl_reg_ext */
void reg_access_hca_mfrl_reg_ext_pack(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfrl_reg_ext_unpack(struct reg_access_hca_mfrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfrl_reg_ext_print(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfrl_reg_ext_size(void);
#define REG_ACCESS_HCA_MFRL_REG_EXT_SIZE    (0x8)
void reg_access_hca_mfrl_reg_ext_dump(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd);
/* mfsv_reg */
void reg_access_hca_mfsv_reg_pack(const struct reg_access_hca_mfsv_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfsv_reg_unpack(struct reg_access_hca_mfsv_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfsv_reg_print(const struct reg_access_hca_mfsv_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfsv_reg_size(void);
#define REG_ACCESS_HCA_MFSV_REG_SIZE    (0x30)
void reg_access_hca_mfsv_reg_dump(const struct reg_access_hca_mfsv_reg *ptr_struct, FILE *fd);
/* mgir */
void reg_access_hca_mgir_pack(const struct reg_access_hca_mgir *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_unpack(struct reg_access_hca_mgir *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_print(const struct reg_access_hca_mgir *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_size(void);
#define REG_ACCESS_HCA_MGIR_SIZE    (0xa0)
void reg_access_hca_mgir_dump(const struct reg_access_hca_mgir *ptr_struct, FILE *fd);
/* mmdio */
void reg_access_hca_mmdio_pack(const struct reg_access_hca_mmdio *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mmdio_unpack(struct reg_access_hca_mmdio *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mmdio_print(const struct reg_access_hca_mmdio *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mmdio_size(void);
#define REG_ACCESS_HCA_MMDIO_SIZE    (0xc)
void reg_access_hca_mmdio_dump(const struct reg_access_hca_mmdio *ptr_struct, FILE *fd);
/* mpcir_ext */
void reg_access_hca_mpcir_ext_pack(const struct reg_access_hca_mpcir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpcir_ext_unpack(struct reg_access_hca_mpcir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpcir_ext_print(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpcir_ext_size(void);
#define REG_ACCESS_HCA_MPCIR_EXT_SIZE    (0x10)
void reg_access_hca_mpcir_ext_dump(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd);
/* mpegc_reg */
void reg_access_hca_mpegc_reg_pack(const struct reg_access_hca_mpegc_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpegc_reg_unpack(struct reg_access_hca_mpegc_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpegc_reg_print(const struct reg_access_hca_mpegc_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpegc_reg_size(void);
#define REG_ACCESS_HCA_MPEGC_REG_SIZE    (0x2c)
void reg_access_hca_mpegc_reg_dump(const struct reg_access_hca_mpegc_reg *ptr_struct, FILE *fd);
/* mqis_reg */
void reg_access_hca_mqis_reg_pack(const struct reg_access_hca_mqis_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mqis_reg_unpack(struct reg_access_hca_mqis_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mqis_reg_print(const struct reg_access_hca_mqis_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mqis_reg_size(void);
#define REG_ACCESS_HCA_MQIS_REG_SIZE    (0x18)
void reg_access_hca_mqis_reg_dump(const struct reg_access_hca_mqis_reg *ptr_struct, FILE *fd);
/* mtrc_cap_reg */
void reg_access_hca_mtrc_cap_reg_pack(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_cap_reg_unpack(struct reg_access_hca_mtrc_cap_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_cap_reg_print(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_cap_reg_size(void);
#define REG_ACCESS_HCA_MTRC_CAP_REG_SIZE    (0x84)
void reg_access_hca_mtrc_cap_reg_dump(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, FILE *fd);
/* mtrc_stdb_reg */
void reg_access_hca_mtrc_stdb_reg_pack(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_stdb_reg_unpack(struct reg_access_hca_mtrc_stdb_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_stdb_reg_print(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_stdb_reg_size(void);
#define REG_ACCESS_HCA_MTRC_STDB_REG_SIZE    (0x8)
void reg_access_hca_mtrc_stdb_reg_dump(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, FILE *fd);
/* pcnr_reg */
void reg_access_hca_pcnr_reg_pack(const struct reg_access_hca_pcnr_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pcnr_reg_unpack(struct reg_access_hca_pcnr_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pcnr_reg_print(const struct reg_access_hca_pcnr_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pcnr_reg_size(void);
#define REG_ACCESS_HCA_PCNR_REG_SIZE    (0xc)
void reg_access_hca_pcnr_reg_dump(const struct reg_access_hca_pcnr_reg *ptr_struct, FILE *fd);
/* resource_dump */
void reg_access_hca_resource_dump_pack(const struct reg_access_hca_resource_dump *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_resource_dump_unpack(struct reg_access_hca_resource_dump *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_resource_dump_print(const struct reg_access_hca_resource_dump *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_resource_dump_size(void);
#define REG_ACCESS_HCA_RESOURCE_DUMP_SIZE    (0x100)
void reg_access_hca_resource_dump_dump(const struct reg_access_hca_resource_dump *ptr_struct, FILE *fd);
/* strs_fault_inject_reg */
void reg_access_hca_strs_fault_inject_reg_pack(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_fault_inject_reg_unpack(struct reg_access_hca_strs_fault_inject_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_fault_inject_reg_print(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_fault_inject_reg_size(void);
#define REG_ACCESS_HCA_STRS_FAULT_INJECT_REG_SIZE    (0x40)
void reg_access_hca_strs_fault_inject_reg_dump(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, FILE *fd);
/* strs_mini_flow_reg */
void reg_access_hca_strs_mini_flow_reg_pack(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_mini_flow_reg_unpack(struct reg_access_hca_strs_mini_flow_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_mini_flow_reg_print(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_mini_flow_reg_size(void);
#define REG_ACCESS_HCA_STRS_MINI_FLOW_REG_SIZE    (0x40)
void reg_access_hca_strs_mini_flow_reg_dump(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, FILE *fd);
/* strs_resource_reg */
void reg_access_hca_strs_resource_reg_pack(const struct reg_access_hca_strs_resource_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_resource_reg_unpack(struct reg_access_hca_strs_resource_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_resource_reg_print(const struct reg_access_hca_strs_resource_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_resource_reg_size(void);
#define REG_ACCESS_HCA_STRS_RESOURCE_REG_SIZE    (0x40)
void reg_access_hca_strs_resource_reg_dump(const struct reg_access_hca_strs_resource_reg *ptr_struct, FILE *fd);
/* strs_stop_toggle_reg */
void reg_access_hca_strs_stop_toggle_reg_pack(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_strs_stop_toggle_reg_unpack(struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_strs_stop_toggle_reg_print(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_strs_stop_toggle_reg_size(void);
#define REG_ACCESS_HCA_STRS_STOP_TOGGLE_REG_SIZE    (0x40)
void reg_access_hca_strs_stop_toggle_reg_dump(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, FILE *fd);
/* reg_access_hca_Nodes */
void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_reg_access_hca_Nodes_size(void);
#define REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE    (0x100)
void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_HCA_LAYOUTS_H
