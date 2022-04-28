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
         *** This file was generated at "2021-10-26 16:49:12"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/switch/ext/reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils
         ***/
#ifndef REG_ACCESS_SWITCH_LAYOUTS_H
#define REG_ACCESS_SWITCH_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_command_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Command data. It may be a request or a response data. */
	/* 0x0.0 - 0x100.31 */
	u_int32_t data[65];
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_crspace_access_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Starting address */
	/* 0x0.0 - 0x0.31 */
	u_int32_t address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - CrSpace data */
	/* 0x4.0 - 0x100.31 */
	u_int32_t data[64];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_device_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index
The first device should number 0 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t device_index;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The flash ID that the device is using. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t flash_id;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set to '1', the fields related to the device are valid since the 
line-card is powered on and plugged and matching the INI ver
sion. 
Note: this bit is not an indication to validity of the fields related 
to the specific FW capabilities and version. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t lc_pwr_on;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Thermal Shutdown. If set, the device was shut down due to 
thermal event. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t thermal_sd;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set to '1', the device is the flash owner. Otherwise, a shared 
flash is used by this device (another device is the flash owner). */
	/* 0x0.30 - 0x0.30 */
	u_int8_t flash_owner;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the device uses a flash */
	/* 0x0.31 - 0x0.31 */
	u_int8_t uses_flash;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: Amos Gearbox
1: Abir Gearbox */
	/* 0x4.0 - 0x4.15 */
	u_int16_t device_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Major FW version number. Valid only after the FW is burnt. Oth
erwise, the value should be '0'. */
	/* 0x4.16 - 0x4.31 */
	u_int16_t fw_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Sub-minor FW version number. Valid only after the FW is 
burnt. Otherwise, the value should be '0'. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t fw_sub_minor;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Minor FW version number. Valid only after the FW is burnt. 
Otherwise, the value should be '0'. */
	/* 0x8.16 - 0x8.31 */
	u_int16_t fw_minor;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximum write size (in D-Words) that the device supports for 
its PRM commands. */
	/* 0xc.0 - 0xc.7 */
	u_int8_t max_cmd_write_size_supp;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximum read size (in D-Words) that the device supports for 
its PRM commands. */
	/* 0xc.8 - 0xc.15 */
	u_int8_t max_cmd_read_size_supp;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Device type ASCII name. Up to 8 chars
 */
	/* 0x10.24 - 0x18.23 */
	u_int8_t device_type_name[8];
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_prm_register_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Register ID */
	/* 0x0.0 - 0x0.15 */
	u_int16_t register_id;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Query
1: Write */
	/* 0x0.22 - 0x0.23 */
	u_int8_t method;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Return code of the Downstream Device to the register 
that was sent.
0x0: OK - Operation was successfully executed
0x1: BUSY 
0x4: NOT_SUPP_REG - The Switch register requested 
is not supported on that device
0x7: BAD_PARAM - Incomplete or erroneous parameter 
set
0x70: INTERNAL_ERR - Internal error */
	/* 0x0.24 - 0x0.31 */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Register data */
	/* 0x4.0 - 0x100.31 */
	u_int32_t register_data[64];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_slot_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the FW has completed the MDDC.device_enable com
mand */
	/* 0x0.27 - 0x0.27 */
	u_int8_t active;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the LC is powered on, matching the INI version and a 
new FW version can be burnt (if necessary)
0: Not ready
1: Ready
2: Error
3: Reserved */
	/* 0x0.28 - 0x0.29 */
	u_int8_t lc_ready;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, Shift Register is valid (after being provisioned) and data 
can be sent from the switch ASIC to the line-card CPLD over 
Shift-Register. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t sr_valid;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the INI file is ready and the card is provisioned */
	/* 0x0.31 - 0x0.31 */
	u_int8_t provisioned;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - User-configured version number of the current INI file.
Valid only when active or lc_ready are '1'. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t ini_file_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - HW revision of the line-card as it appears in the current INI file.
Valid only when active or lc_ready are '1'. */
	/* 0x4.16 - 0x4.31 */
	u_int16_t hw_revision;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Card type
0x00: Buffalo 4x400G
0x01: Buffalo 8x200G
0x02: Buffalo 16x100G */
	/* 0x8.0 - 0x8.7 */
	u_int8_t card_type;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_slot_name_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot's ASCII name. Up to 20 chars
 */
	/* 0x0.24 - 0x14.23 */
	u_int8_t slot_ascii_name[20];
};

/* Description -   */
/* Size in bytes - 32 */
union reg_access_switch_mddq_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_switch_slot_info_ext slot_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_switch_device_info_ext device_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_switch_slot_name_ext slot_name_ext;
};

/* Description -   */
/* Size in bytes - 260 */
union reg_access_switch_mddt_reg_payload_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	struct reg_access_switch_prm_register_payload_ext prm_register_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	struct reg_access_switch_command_payload_ext command_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	struct reg_access_switch_crspace_access_payload_ext crspace_access_payload_ext;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_icam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups 
0: REG_IDs 0x3800 to 0x387F
1: REG_IDs 0x3880 to 0x38FF */
	/* 0x0.0 - 0x0.7 */
	u_int8_t access_reg_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported infrastructure's access register bitmask. Based on 
access_reg_group index. 
When bit is set to '1', The register is supported in the device. 
For example, when access_reg_group == 1:
Bit 112: ICSR
Bit0 is at 08h.bit0
Bit 127 is at 14h.bit31 */
	/* 0x8.0 - 0x14.31 */
	u_int32_t infr_access_reg_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 1040 */
struct reg_access_switch_icsr_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Base cr-space address for reading */
	/* 0x4.0 - 0x4.31 */
	u_int32_t base_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of cr-space consecutive reads.
Each read is 4B (DWord)
Range 1..256 */
	/* 0x8.0 - 0x8.8 */
	u_int16_t num_reads;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The cr-space read data */
	/* 0x10.0 - 0x40c.31 */
	u_int32_t data[256];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mddq_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index
0: Reserved */
	/* 0x0.0 - 0x0.3 */
	u_int8_t slot_index;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: Reserved
1: slot_info
2: device_info - If there are no devices on the slot, data_valid 
will be '0'.
3: slot_name - Name of the slot (string) */
	/* 0x0.16 - 0x0.23 */
	u_int8_t query_type;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot info event enable
When set to '1', each change in the MDDQ.slot_info.provi
sioned / sr_valid / active / ready will generate an event. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sie;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Request message sequential number. 
The first message number should be 0 */
	/* 0x4.0 - 0x4.7 */
	u_int8_t request_message_sequence;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Response message sequential number. 
For a specific request, the response message sequential num
ber is the following one. 
In addition, the last message should be 0. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t response_message_sequence;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Index related to the specific query_type. 
For query_type = 1,2,3 this field is neglected. */
	/* 0x8.0 - 0x8.7 */
	u_int8_t query_index;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - If set, the data in the data field is valid and contain the informa
tion for the queried index. 
Note: This field is not reflecting any validity of the data while 
accessing a non-existing query entity. Querying with an out of 
range index will lead to BAD_PARAM status of the register. */
	/* 0x8.31 - 0x8.31 */
	u_int8_t data_valid;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Properties of that field are based on query_type.
For slot information query_type data - see Table 539, 
"slot_info Register Layout," on page 753
For devices on slot query_type data - see Table 541, 
"device_info Register Layout," on page 754
For slot name query_type data - see Table 543, "slot_name 
Register Layout," on page 755 */
	/* 0x10.0 - 0x2c.31 */
	union reg_access_switch_mddq_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 272 */
struct reg_access_switch_mddt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index */
	/* 0x0.0 - 0x0.7 */
	u_int8_t device_index;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index */
	/* 0x0.8 - 0x0.11 */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: PRM_Register
1: Command
2: CrSpace_access - [Internal] */
	/* 0x4.0 - 0x4.1 */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Write size in D-Words. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t write_size;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Read size in D-Words. */
	/* 0x4.24 - 0x4.31 */
	u_int8_t read_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Payload
For PRM Register type payload- See Table 531, "PRM 
Register Payload Layout," on page 750
For Command type payload - See Table 533, "Com
mand Payload Layout," on page 750
For CrSpace type payload - See Table 535, "CrSpace 
access Payload Layout," on page 751 */
	/* 0xc.0 - 0x10c.31 */
	union reg_access_switch_mddt_reg_payload_auto_ext payload;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mdsr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: The debug session ended successfully
1: Failed to execute the operation. See additional_info for 
more details.
2: Debug session active. See type_of_token for more details.
3: No token applied
4: Challenge provided, no token installed yet, see type_of_to
ken for details.
5: Timeout before token installed, see type_of_token for 
details
6: Timeout of active token.
7-15: Reserved

Note: Status might be '0' even when debug query is not 
allowed and additional_info field will expose the reason. */
	/* 0x0.0 - 0x0.3 */
	u_int8_t status;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: No additional information available 
1: There is no debug session in progress
2: FW is not secured, debug session cannot be ended
3: Fail - Debug end request cannot be accepted. 
4: Fail - Host is not allowed to query debug session
5: Debug session active */
	/* 0x0.8 - 0x0.13 */
	u_int8_t additional_info;
	/* Description - 0: Debug FW token 1: CS token 
2: FRC token 
3: RMCS token
4: RMDS token 
5: CRCS token 
6: CRDT token */
	/* 0x0.24 - 0x0.31 */
	u_int8_t type_of_token;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Set to '1' to end debug session.
Setting to '0' will not trigger any operation. */
	/* 0x4.31 - 0x4.31 */
	u_int8_t end;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time left in seconds.
In case that status is 2 (debug session active) - time left for 
token operation
In case that status is 4 (challenge provided, no token 
installed yet) - time left for token installation
For any other status, field should be zero */
	/* 0x8.0 - 0x8.31 */
	u_int32_t time_left;
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_switch_mkdc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates the successful completion of the instruction 
or the reason it failed:
0: OK
1: BAD_SESSION_ID
2: BAD_KEEP_ALIVE_COUNTER
3: BAD_SOURCE_ADDRESS
4: SESSION_TIMEOUT
Other values are Reserved. */
	/* 0x0.0 - 0x0.3 */
	u_int8_t error_code;
	/* Description - Unique debug session identifier. */
	/* 0x0.16 - 0x0.31 */
	u_int16_t session_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Running counter that states the current sequence 
number of each keep-alive session. */
	/* 0x4.0 - 0x4.31 */
	u_int32_t current_keep_alive_counter;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Running counter that states the expected next 
sequence number of each keep-alive session. */
	/* 0x8.0 - 0x8.31 */
	u_int32_t next_keep_alive_counter;
};

/* Description -   */
/* Size in bytes - 112 */
struct reg_access_switch_mtcq_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device number.
For gearboxes, the index represents the gearbox die.
For cables, the index represents the module index 
starting at index 1 while index 0 indicates the host 
device. */
	/* 0x0.0 - 0x0.11 */
	u_int16_t device_index;
	/* Description - Indicates the status of the desired token we are gener
ating the challenge for.
0x0 - OK
0x1 - TOKEN_ALREADY_APPLIED
0x2 - TOKEN_NOT_SUPPORTED
0x3 - NO_KEY_CONFIGURED (there is no public_key 
that can be used for this token) 
0x4 - INTERFACE_NOT_ALLOWED (asking for local 
token from remote interface, or remote token from 
local interface) */
	/* 0x0.16 - 0x0.23 */
	u_int8_t status;
	/* Description - The token which a challenge is generated for.
0: RMCS
1: RMDT

Other: Reserved */
	/* 0x0.24 - 0x0.31 */
	u_int8_t token_opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The UUID of the key used to generate the challenge. */
	/* 0x4.0 - 0x10.31 */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Device base MAC address / unique identifier. */
	/* 0x14.0 - 0x18.31 */
	u_int64_t base_mac;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Device PSID */
	/* 0x1c.0 - 0x28.31 */
	u_int32_t psid[4];
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Device FW version */
	/* 0x2c.0 - 0x2c.7 */
	u_int8_t fw_version_39_32;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Device FW version */
	/* 0x30.0 - 0x30.31 */
	u_int32_t fw_version_31_0;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Source address of debug requester. DLID for Infini
band, ETH / IBg2 - TBD.
Valid only for RMCS/RMDT. */
	/* 0x34.0 - 0x40.31 */
	u_int32_t source_address[4];
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Unique debug session identifier. 
See details in REMOTE_DEBUG_KEEP_ALIVE.
Valid only for RMCS. */
	/* 0x44.0 - 0x44.15 */
	u_int16_t session_id;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Version of the challenge format. */
	/* 0x44.24 - 0x44.31 */
	u_int8_t challenge_version;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Random generated field. Used for randomness and 
replay-protection. */
	/* 0x48.0 - 0x64.31 */
	u_int32_t challenge[8];
};

/* Description -   */
/* Size in bytes - 1040 */
union reg_access_switch_reg_access_switch_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10c.31 */
	struct reg_access_switch_mddt_reg_ext mddt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	struct reg_access_switch_icam_reg_ext icam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	struct reg_access_switch_mdsr_reg_ext mdsr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	struct reg_access_switch_mkdc_reg_ext mkdc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	struct reg_access_switch_mtcq_reg_ext mtcq_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	struct reg_access_switch_mddq_ext mddq_ext;
	/* Description -  */
	/* 0x0.0 - 0x40c.31 */
	struct reg_access_switch_icsr_ext icsr_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* command_payload_ext */
void reg_access_switch_command_payload_ext_pack(const struct reg_access_switch_command_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_unpack(struct reg_access_switch_command_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_print(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_command_payload_ext_size(void);
#define REG_ACCESS_SWITCH_COMMAND_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_command_payload_ext_dump(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd);
/* crspace_access_payload_ext */
void reg_access_switch_crspace_access_payload_ext_pack(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_unpack(struct reg_access_switch_crspace_access_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_print(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_crspace_access_payload_ext_size(void);
#define REG_ACCESS_SWITCH_CRSPACE_ACCESS_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_crspace_access_payload_ext_dump(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd);
/* device_info_ext */
void reg_access_switch_device_info_ext_pack(const struct reg_access_switch_device_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_device_info_ext_unpack(struct reg_access_switch_device_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_device_info_ext_print(const struct reg_access_switch_device_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_device_info_ext_size(void);
#define REG_ACCESS_SWITCH_DEVICE_INFO_EXT_SIZE    (0x20)
void reg_access_switch_device_info_ext_dump(const struct reg_access_switch_device_info_ext *ptr_struct, FILE *fd);
/* prm_register_payload_ext */
void reg_access_switch_prm_register_payload_ext_pack(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_unpack(struct reg_access_switch_prm_register_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_print(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_prm_register_payload_ext_size(void);
#define REG_ACCESS_SWITCH_PRM_REGISTER_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_prm_register_payload_ext_dump(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd);
/* slot_info_ext */
void reg_access_switch_slot_info_ext_pack(const struct reg_access_switch_slot_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_slot_info_ext_unpack(struct reg_access_switch_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_slot_info_ext_print(const struct reg_access_switch_slot_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_slot_info_ext_size(void);
#define REG_ACCESS_SWITCH_SLOT_INFO_EXT_SIZE    (0x20)
void reg_access_switch_slot_info_ext_dump(const struct reg_access_switch_slot_info_ext *ptr_struct, FILE *fd);
/* slot_name_ext */
void reg_access_switch_slot_name_ext_pack(const struct reg_access_switch_slot_name_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_slot_name_ext_unpack(struct reg_access_switch_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_slot_name_ext_print(const struct reg_access_switch_slot_name_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_slot_name_ext_size(void);
#define REG_ACCESS_SWITCH_SLOT_NAME_EXT_SIZE    (0x20)
void reg_access_switch_slot_name_ext_dump(const struct reg_access_switch_slot_name_ext *ptr_struct, FILE *fd);
/* mddq_data_auto_ext */
void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_DATA_AUTO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_data_auto_ext_dump(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd);
/* mddt_reg_payload_auto_ext */
void reg_access_switch_mddt_reg_payload_auto_ext_pack(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_unpack(union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_print(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_payload_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_PAYLOAD_AUTO_EXT_SIZE    (0x104)
void reg_access_switch_mddt_reg_payload_auto_ext_dump(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_switch_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_uint64_size(void);
#define REG_ACCESS_SWITCH_UINT64_SIZE    (0x8)
void reg_access_switch_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* icam_reg_ext */
void reg_access_switch_icam_reg_ext_pack(const struct reg_access_switch_icam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_unpack(struct reg_access_switch_icam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_print(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icam_reg_ext_size(void);
#define REG_ACCESS_SWITCH_ICAM_REG_EXT_SIZE    (0x18)
void reg_access_switch_icam_reg_ext_dump(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd);
/* icsr_ext */
void reg_access_switch_icsr_ext_pack(const struct reg_access_switch_icsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_unpack(struct reg_access_switch_icsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_print(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icsr_ext_size(void);
#define REG_ACCESS_SWITCH_ICSR_EXT_SIZE    (0x410)
void reg_access_switch_icsr_ext_dump(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd);
/* mddq_ext */
void reg_access_switch_mddq_ext_pack(const struct reg_access_switch_mddq_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_unpack(struct reg_access_switch_mddq_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_print(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_EXT_SIZE    (0x30)
void reg_access_switch_mddq_ext_dump(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd);
/* mddt_reg_ext */
void reg_access_switch_mddt_reg_ext_pack(const struct reg_access_switch_mddt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_unpack(struct reg_access_switch_mddt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_print(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_EXT_SIZE    (0x110)
void reg_access_switch_mddt_reg_ext_dump(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd);
/* mdsr_reg_ext */
void reg_access_switch_mdsr_reg_ext_pack(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_unpack(struct reg_access_switch_mdsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_print(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mdsr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDSR_REG_EXT_SIZE    (0x30)
void reg_access_switch_mdsr_reg_ext_dump(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd);
/* mkdc_reg_ext */
void reg_access_switch_mkdc_reg_ext_pack(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_unpack(struct reg_access_switch_mkdc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_print(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mkdc_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MKDC_REG_EXT_SIZE    (0x2c)
void reg_access_switch_mkdc_reg_ext_dump(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd);
/* mtcq_reg_ext */
void reg_access_switch_mtcq_reg_ext_pack(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_unpack(struct reg_access_switch_mtcq_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_print(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mtcq_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MTCQ_REG_EXT_SIZE    (0x70)
void reg_access_switch_mtcq_reg_ext_dump(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd);
/* reg_access_switch_Nodes */
void reg_access_switch_reg_access_switch_Nodes_pack(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_unpack(union reg_access_switch_reg_access_switch_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_print(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_reg_access_switch_Nodes_size(void);
#define REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE    (0x410)
void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_SWITCH_LAYOUTS_H
