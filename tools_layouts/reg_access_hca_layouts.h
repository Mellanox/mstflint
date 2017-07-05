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
         *** This file was generated at "2017-05-04 07:31:40"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/hca/int/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_
         ***/
#ifndef REG_ACCESS_HCA_LAYOUTS_H
#define REG_ACCESS_HCA_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_fpga_ctrl {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Status of the last operation.
0x0: Success
0x1: Failure
0x2: In_progress
Valid only for query operation. */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t status;
	/* Description - Indicates the control operation to be performed. Allowed only when 
FPGA_CAP.fpga_ctrl_modify==1. 
 See Table  494, "
FPGA_CAP Regis
ter Layout
," on page  720
.
0x1: LOAD - when set, the FPGA will be forced to reload the image 
from flash according to 
image_select_admin
 value.
0x2: RESET - when set, the FPGA internal logic state (BRAMs, 
FFs, etc.) will be reset to the original state at loading time.
0x3: FLASH_SELECT - when set, map the flash GW according to 
flash_select_admin
 value.
0x4: Sandbox_Bypass_On - If set, sandbox logic is inactive until 
Sandbox_Bypass_Off is set. Packets will skip the sandbox logic.
0x5: Sandbox_Bypass_Off - If set, sandbox logic is active. Packets 
will be processed by the sandbox logic.
0x6: Reset_Sandbox - If set, the FPGA sandbox logic state 
(BRAMs, FFs, etc.) will be reset to the original state at loading time 
(no shell state is affected). */
	/* 0x0.16 - 0x0.23 */
	 u_int8_t operation;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Current flashthat is used to loadimages to FPGA.
0x0: Factory_default
0x1: User
Valid only if status is ok. */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t flash_select_oper;
	/* Description - Used to select next flash to be usedto load the images.
0x0: Factory_default
0x1: User
Valid only for FLASH_SELECT and LOAD operations. */
	/* 0x4.16 - 0x4.23 */
	 u_int8_t flash_select_admin;
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
	/* Description - The maximum size of message size supported by FPGA Shell QP. */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t max_fpga_qp_msg_size;
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
Other values are reserved. Applicable for write operation 
only. */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t instruction;
	/* Description - The number of seconds elapsed since the update_handle 
owner last issued a command. The time saturates at 0xFFF. */
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
	/* Description - Token representing the current flow executed by the FSM.
See 
"Update Handle" on page 468 */
	/* 0x8.0 - 0x8.23 */
	 u_int32_t update_handle;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Current Update FSM state, See 
"FSM States" on page 471
0x0: IDLE
0x1: LOCKED
0x2: INITIALIZE
0x3: DOWNLOAD
0x4: VERIFY
0x5: APPLY
0x6: ACTIVATE
0x7: UPLOAD
0x8: UPLOAD_PENDING
Other values are reserved */
	/* 0xc.0 - 0xc.3 */
	 u_int8_t control_state;
	/* Description - Indicates the successful completion of the 
instruction
, or 
the reason it failed. See 
"Error Handling" on page 470
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
Other values should be treated as an unknown error. */
	/* 0xc.8 - 0xc.15 */
	 u_int8_t error_code;
	/* Description - Indicates the estimated progress status of the current opera
tion executed by the FSM. Valid values are 0..100.
101 indicates that progress reporting is not supported for 
this update state. */
	/* 0xc.16 - 0xc.22 */
	 u_int8_t control_progress;
	/* Description - For 
handle_owner_type
 BMC, command-interface and 
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
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_hca_mcda_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Update handle registered when the FSM was activated. */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t update_handle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Offset of accessed address relative to component start. 
Accesses must be in accordance to 
log_mcda_word_size
 in 
Table 796, "MCQI CAPABILITIES Info Layout," on 
page 935 */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the data accessed, given in bytes */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Data block accessed */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t* data;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_mcqi_activation_method {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, the operation needed to move the component 
form ACTIVE_PENDING_RESET to ACTIVE should 
happen simultaneously on all hosts. */
	/* 0x0.26 - 0x0.26 */
	 u_int8_t all_hosts_sync;
	/* Description - This component will be ACTIVE or ACTIVE_PEND
ING_RESET after the APPLY state. */
	/* 0x0.27 - 0x0.27 */
	 u_int8_t auto_activate;
	/* Description - This component goes to ACTIVE_PENDING_RESET after 
activation.
A FW reset will move it to ACTIVE state. */
	/* 0x0.28 - 0x0.28 */
	 u_int8_t pending_fw_reset;
	/* Description - This component goes to ACTIVE_PENDING_RESET state 
after activation.
A server reset (PCIe PERST#), will move it ACTIVE state. */
	/* 0x0.29 - 0x0.29 */
	 u_int8_t pending_server_reboot;
	/* Description - This component goes to ACTIVE_PENDING_RESET state 
after activation.
DC power cycle (power cycle of PCI power rails), will 
move it ACTIVE state. */
	/* 0x0.30 - 0x0.30 */
	 u_int8_t pending_server_dc_power_cycle;
	/* Description - This component goes to ACTIVE_PENDING_RESET state 
after activation.
AC power cycle (power cycle for both PCI power rails and 
AUX power), will move it ACTIVE state. */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t pending_server_ac_power_cycle;
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_hca_mcqi_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask indicating which info_type(s) are supported for 
this component. Set bit indicates the property set is sup
ported
bit 1: VERSION
bit 5: ACTIVATION_METHOD
Other bits are reserved. CAPABILITIES set is always sup
ported. */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t supported_info_bitmask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The size of the component given in bytes. Value 0x0 indi
cates that the size in unknown.
For some components, size may only be available in the 
READ_COMPONENT state. */
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
Read and write access must be aligned to the word size. 
Write access must be done for an integer number of words. */
	/* 0xc.28 - 0xc.31 */
	 u_int8_t log_mcda_word_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The device only accepts updates for this component that 
explicitly lists its base MAC and/or base GUID */
	/* 0x10.26 - 0x10.26 */
	 u_int8_t match_base_guid_mac;
	/* Description - A user defined timestamp (MVTS) is active for this compo
nent. */
	/* 0x10.27 - 0x10.27 */
	 u_int8_t check_user_timestamp;
	/* Description - PSID is validated for this component update. */
	/* 0x10.28 - 0x10.28 */
	 u_int8_t match_psid;
	/* Description - Chip ID (
device_hw_revision
) is validated for this compo
nent update. */
	/* 0x10.29 - 0x10.29 */
	 u_int8_t match_chip_id;
	/* Description - Only signed components are accepted. */
	/* 0x10.30 - 0x10.30 */
	 u_int8_t signed_updates_only;
	/* Description - When set, this components may be read, see 
"Read Flow" 
on page 470 */
	/* 0x10.31 - 0x10.31 */
	 u_int8_t rd_en;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_mcqi_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component index gathered by 
"MCQS - Management 
Component Query Status" */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t component_index;
	/* Description - When set, the register will return information about the 
pending component (if available) */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t read_pending_component;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component properties set.
0x0: CAPABILITIES
0x1: VERSION
0x5: ACTIVATION_METHOD
Other values are reserved */
	/* 0x8.0 - 0x8.4 */
	 u_int8_t info_type;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Properties set structure size, given in bytes. */
	/* 0xc.0 - 0xc.31 */
	 u_int32_t info_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The requested/returned data offset from the section start, 
given in bytes.
Must be DWORD aligned. */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t offset;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The requested/returned data size, given in bytes. 
If 
data_size
 is not DWORD aligned, the last bytes are zero 
padded. */
	/* 0x14.0 - 0x14.15 */
	 u_int16_t data_size;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Properties set structure according to 
info_type
.
CAPABILITIES - See 
Table 796, "MCQI CAPABILITIES 
Info Layout," on page 935
VERSION - See 
Table 798, "MCQI VERSION Info Lay
out," on page 937
ACTIVATION_METHOD - See 
Table 802, "MCQI ACTI
VATION_METHOD Info Layout," on page 938 */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t* data;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mcqs_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component Index. Values range from 1 to the last compo
nent indicated by 
last_index_flag
. */
	/* 0x0.0 - 0x0.15 */
	 u_int16_t component_index;
	/* Description - When set, this component is the last component (highest 
component_index
). */
	/* 0x0.31 - 0x0.31 */
	 u_int8_t last_index_flag;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field uniquely identifies a specific component type. 
0x1: BOOT_IMG
0x2: RUNTIME_IMG
0x3: USER_NVCONFIG
0x4: OEM_NVCONFIG
0x5: MLNX_NVCONFIG
0x6: CS_TOKEN
0x7: DBG_TOKEN
0x8: DEV_INFO
0x9: PACKAGE_INFO
Other values are reserved */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t identifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component statue in update flow, see 
"Component Update 
State" on page 467
:
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
0x0: NOT_PRESENT - The component is supported by the 
device but, currently not present
0x1: PRESENT - This component is present.
0x2: IN_USE - The component is present and currently in 
use.
Other values are reserved */
	/* 0x8.4 - 0x8.8 */
	 u_int8_t component_status;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - For 
last_update_state_changer_type
 BMC, command-
interface and ICMD, indicates the identifier of the host of 
the handle owner. Otherwise reserved. */
	/* 0xc.24 - 0xc.27 */
	 u_int8_t last_update_state_changer_host_id;
	/* Description - Indicates which entity was the last to change the 
compo
nent_update_state
 of this component.
0x0: unspecified
0x1: Chassis BMC
0x2: MAD
0x3: BMC
0x4: command interface
0x5: ICMD
Other values are reserved */
	/* 0xc.28 - 0xc.31 */
	 u_int8_t last_update_state_changer_type;
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_hca_mgir {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see 
Table 715, "Hardware Info Layout," 
on page 892 */
	/* 0x0.24 - 0x20.23 */
	 u_int8_t hw_info[32];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Firmware Information, see 
Table 717, "Firmware Info Layout," 
on page 893 */
	/* 0x20.24 - 0x60.23 */
	 u_int8_t fw_info[64];
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Software Information, see 
Table 719, "Software Info Layout," on 
page 894
This field indicates 
the oldest software version compatible 
with the current firmware */
	/* 0x60.24 - 0x80.23 */
	 u_int8_t sw_info[32];
};

/* Description -   */
/* Size in bytes - 20 */
struct reg_access_hca_mqis_reg {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Type of information string to be queried:
0x0: VPD
0x1: MODEL_NAME
0x2: MODEL_DESCRIPTION
other values are reserved. */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t info_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Total size of the information string, according to 
info_type
. 
Value given in bytes. */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t info_length;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes requested. The device returns the number 
of bytes actually read. */
	/* 0x8.0 - 0x8.15 */
	 u_int16_t read_length;
	/* Description - Offset in bytes of the first byte requested to read. */
	/* 0x8.16 - 0x8.31 */
	 u_int16_t read_offset;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Information string accessed, according to 
info_type
. If the 
information is not available, a NULL string is returned. */
	/* 0x10.0 - 0x10.31 */
	 u_int32_t* info_string;
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_hca_fpga_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - FPGA device type.
0x0: KU040
0x1: KU060 */
	/* 0x0.0 - 0x0.23 */
	 u_int32_t fpga_device;
	/* Description - FPGA identifier.
0x0: unknown
0x1: Newton_X */
	/* 0x0.24 - 0x0.31 */
	 u_int8_t fpga_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Shell registers space file version. */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t register_file_ver;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Indicates the MODIFY operation's permissions of FPGA_AC
CESS_REG.
0x0: Not_allowed - modify registers by FPGA_ACCESS_REG not 
allowed.
0x1: All_range_allowed- modify registers by FPGA_AC
CESS_REG allowed for all addresses. */
	/* 0x8.16 - 0x8.17 */
	 u_int8_t access_reg_modify_mode;
	/* Description - Indicates the QUERY operation's permissions of FPGA_AC
CESS_REG.
0x0: Not_allowed - Query registers by FPGA_ACCESS_REG not 
allowed.
0x1: All_range_allowed- Query registers by FPGA_ACCESS_REG 
allowed for all addresses. */
	/* 0x8.24 - 0x8.25 */
	 u_int8_t access_reg_query_mode;
	/* Description - If set, SW is allowed to modify FPGA_CTRL register. See
 Table  498, 
"
FPGA_CTRL Register Layout
," on page  724 */
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
For Mellanox sandbox products, see
 Table  455, "
IPsec_Basic_Capabili
ties Structure Layout
," on page  687
. */
	/* 0x78.0 - 0x78.31 */
	 u_int32_t sandbox_basic_caps;
/*---------------- DWORD[31] (Offset 0x7c) ----------------*/
	/* Description - The length (in DWORDs) of sandbox extended capability (equals 0 
when such capability is not present). */
	/* 0x7c.0 - 0x7c.15 */
	 u_int16_t sandbox_extended_caps_len;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Extended capabilities address.
For Mellanox sandbox products, see
 Table  457, "
IPsec_Extended_Capa
bilities Structure Layout
," on page  687
. */
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
/* Size in bytes - 36 */
struct reg_access_hca_mcqi_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t version_string_length;
	/* Description - When set, the component has a valid user-defined version 
time-stamp in 
user_defined_time */
	/* 0x0.28 - 0x0.28 */
	 u_int8_t user_defined_time_valid;
	/* Description - When set, the component has a valid creation time-stamp in 
build_time */
	/* 0x0.29 - 0x0.29 */
	 u_int8_t build_time_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Version number */
	/* 0x4.0 - 0x4.31 */
	 u_int32_t version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time of component creation. Valid only if 
build_time_valid
 
is set. See 
Table 800, "Date-Time Layout," on page 938 */
	/* 0x8.0 - 0xc.31 */
	 u_int64_t build_time;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - User-defined time assigned to the component version. Valid 
only if 
user_defined_time_valid
 is set. See 
Table 800, 
"Date-Time Layout," on page 938 */
	/* 0x10.0 - 0x14.31 */
	 u_int64_t user_defined_time;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Build tool version number.
Valid only when not equal to 0 */
	/* 0x18.0 - 0x18.31 */
	 u_int32_t build_tool_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - NULL terminated string representing the version. */
	/* 0x20.0 - 0x20.31 */
	 u_int32_t* version_string;
};

/* Description -   */
/* Size in bytes - 256 */
union reg_access_hca_reg_access_hca_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	 struct reg_access_hca_mcda_reg mcda_reg;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct reg_access_hca_mcqs_reg mcqs_reg;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	 struct reg_access_hca_fpga_ctrl fpga_ctrl;
	/* Description -  */
	/* 0x0.0 - 0x20.31 */
	 struct reg_access_hca_mcqi_version mcqi_version;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	 struct reg_access_hca_mgir mgir;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	 struct reg_access_hca_mcqi_activation_method mcqi_activation_method;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	 struct reg_access_hca_fpga_cap fpga_cap;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	 struct reg_access_hca_mqis_reg mqis_reg;
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	 struct reg_access_hca_mcqi_cap mcqi_cap;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	 struct reg_access_hca_mcqi_reg mcqi_reg;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	 struct reg_access_hca_mcc_reg mcc_reg;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* fpga_ctrl */
void reg_access_hca_fpga_ctrl_pack(const struct reg_access_hca_fpga_ctrl *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_fpga_ctrl_unpack(struct reg_access_hca_fpga_ctrl *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_fpga_ctrl_print(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_fpga_ctrl_size(void);
#define REG_ACCESS_HCA_FPGA_CTRL_SIZE    (0x10)
void reg_access_hca_fpga_ctrl_dump(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE* file);
/* fpga_shell_caps */
void reg_access_hca_fpga_shell_caps_pack(const struct reg_access_hca_fpga_shell_caps *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_fpga_shell_caps_unpack(struct reg_access_hca_fpga_shell_caps *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_fpga_shell_caps_print(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_fpga_shell_caps_size(void);
#define REG_ACCESS_HCA_FPGA_SHELL_CAPS_SIZE    (0x40)
void reg_access_hca_fpga_shell_caps_dump(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE* file);
/* mcc_reg */
void reg_access_hca_mcc_reg_pack(const struct reg_access_hca_mcc_reg *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcc_reg_unpack(struct reg_access_hca_mcc_reg *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcc_reg_print(const struct reg_access_hca_mcc_reg *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcc_reg_size(void);
#define REG_ACCESS_HCA_MCC_REG_SIZE    (0x20)
void reg_access_hca_mcc_reg_dump(const struct reg_access_hca_mcc_reg *ptr_struct, FILE* file);
/* mcda_reg */
void reg_access_hca_mcda_reg_pack(const struct reg_access_hca_mcda_reg *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcda_reg_unpack(struct reg_access_hca_mcda_reg *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcda_reg_print(const struct reg_access_hca_mcda_reg *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcda_reg_size(void);
#define REG_ACCESS_HCA_MCDA_REG_SIZE    (0x14)
void reg_access_hca_mcda_reg_dump(const struct reg_access_hca_mcda_reg *ptr_struct, FILE* file);
/* mcqi_activation_method */
void reg_access_hca_mcqi_activation_method_pack(const struct reg_access_hca_mcqi_activation_method *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcqi_activation_method_unpack(struct reg_access_hca_mcqi_activation_method *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcqi_activation_method_print(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcqi_activation_method_size(void);
#define REG_ACCESS_HCA_MCQI_ACTIVATION_METHOD_SIZE    (0x4)
void reg_access_hca_mcqi_activation_method_dump(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE* file);
/* mcqi_cap */
void reg_access_hca_mcqi_cap_pack(const struct reg_access_hca_mcqi_cap *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcqi_cap_unpack(struct reg_access_hca_mcqi_cap *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcqi_cap_print(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcqi_cap_size(void);
#define REG_ACCESS_HCA_MCQI_CAP_SIZE    (0x14)
void reg_access_hca_mcqi_cap_dump(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE* file);
/* mcqi_reg */
void reg_access_hca_mcqi_reg_pack(const struct reg_access_hca_mcqi_reg *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcqi_reg_unpack(struct reg_access_hca_mcqi_reg *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcqi_reg_print(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcqi_reg_size(void);
#define REG_ACCESS_HCA_MCQI_REG_SIZE    (0x1c)
void reg_access_hca_mcqi_reg_dump(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE* file);
/* mcqs_reg */
void reg_access_hca_mcqs_reg_pack(const struct reg_access_hca_mcqs_reg *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcqs_reg_unpack(struct reg_access_hca_mcqs_reg *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcqs_reg_print(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcqs_reg_size(void);
#define REG_ACCESS_HCA_MCQS_REG_SIZE    (0x10)
void reg_access_hca_mcqs_reg_dump(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE* file);
/* mgir */
void reg_access_hca_mgir_pack(const struct reg_access_hca_mgir *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mgir_unpack(struct reg_access_hca_mgir *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mgir_print(const struct reg_access_hca_mgir *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mgir_size(void);
#define REG_ACCESS_HCA_MGIR_SIZE    (0x80)
void reg_access_hca_mgir_dump(const struct reg_access_hca_mgir *ptr_struct, FILE* file);
/* mqis_reg */
void reg_access_hca_mqis_reg_pack(const struct reg_access_hca_mqis_reg *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mqis_reg_unpack(struct reg_access_hca_mqis_reg *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mqis_reg_print(const struct reg_access_hca_mqis_reg *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mqis_reg_size(void);
#define REG_ACCESS_HCA_MQIS_REG_SIZE    (0x14)
void reg_access_hca_mqis_reg_dump(const struct reg_access_hca_mqis_reg *ptr_struct, FILE* file);
/* fpga_cap */
void reg_access_hca_fpga_cap_pack(const struct reg_access_hca_fpga_cap *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_fpga_cap_unpack(struct reg_access_hca_fpga_cap *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_fpga_cap_print(const struct reg_access_hca_fpga_cap *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_fpga_cap_size(void);
#define REG_ACCESS_HCA_FPGA_CAP_SIZE    (0x100)
void reg_access_hca_fpga_cap_dump(const struct reg_access_hca_fpga_cap *ptr_struct, FILE* file);
/* mcqi_version */
void reg_access_hca_mcqi_version_pack(const struct reg_access_hca_mcqi_version *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_mcqi_version_unpack(struct reg_access_hca_mcqi_version *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_mcqi_version_print(const struct reg_access_hca_mcqi_version *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_mcqi_version_size(void);
#define REG_ACCESS_HCA_MCQI_VERSION_SIZE    (0x24)
void reg_access_hca_mcqi_version_dump(const struct reg_access_hca_mcqi_version *ptr_struct, FILE* file);
/* reg_access_hca_Nodes */
void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t* ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE* file, int indent_level);
int reg_access_hca_reg_access_hca_Nodes_size(void);
#define REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE    (0x100)
void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_HCA_LAYOUTS_H
