/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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
#ifndef REG_ACCESS_SWITCH_LAYOUTS_H
#define REG_ACCESS_SWITCH_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_device_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index
The first device should number 0 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t device_index;
	/* Description - The flash ID that the device is using. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t flash_id;
	/* Description - Thermal Shutdown. If set, the device was shut down due to thermal 
event. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t thermal_sd;
	/* Description - If set to '1', the device is the flash owner. Otherwise, a shared flash 
is used by this device (another device is the flash owner). */
	/* 0x0.30 - 0x0.30 */
	u_int8_t flash_owner;
	/* Description - If set, the device uses a flash */
	/* 0x0.31 - 0x0.31 */
	u_int8_t uses_flash;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: Amos Gearbox
1: Ofek Gearbox */
	/* 0x4.0 - 0x4.15 */
	u_int16_t device_type;
	/* Description - Major FW version number. */
	/* 0x4.16 - 0x4.31 */
	u_int16_t fw_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Sub-minor FW version number. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t fw_sub_minor;
	/* Description - Minor FW version number. */
	/* 0x8.16 - 0x8.31 */
	u_int16_t fw_minor;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_slot_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the GBs are reset, FW is burnt / upgraded */
	/* 0x0.28 - 0x0.28 */
	u_int8_t active;
	/* Description - If set, the LC is Ready (after being reset and Shift Register is valid) 
and a new FW version can be burnt (if necessary) */
	/* 0x0.29 - 0x0.29 */
	u_int8_t ready;
	/* Description - If set, Shift Register is valid (after being provisioned) */
	/* 0x0.30 - 0x0.30 */
	u_int8_t sr_valid;
	/* Description - If set, the INI file is applied and the card is provisioned */
	/* 0x0.31 - 0x0.31 */
	u_int8_t provisioned;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Minor user-configured version number of the current INI file.
Valid only when active or ready are '1'. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t minor_ini_file_version;
	/* Description - Major user-configured version number of the current INI file.
Valid only when active or ready are '1'. */
	/* 0x4.16 - 0x4.31 */
	u_int16_t major_ini_file_version;
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
union reg_access_switch_mddq_data_auto {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_switch_slot_info slot_info;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct reg_access_switch_device_info device_info;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mddq {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index
0: Reserved */
	/* 0x0.0 - 0x0.3 */
	u_int8_t slot_index;
	/* Description - 1: slot_info
2: device_info - If there are no devices on the slot, lst, mid, frst will 
be '0'. */
	/* 0x0.16 - 0x0.23 */
	u_int8_t query_type;
	/* Description - Slot info event enable
When set to '1', each change in the MDDQ.slot_info.provisioned / 
sr_valid / active / ready will generate an event. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t sie;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Request message sequential number. 
The first message number should be 0 (when frst is '1') */
	/* 0x4.0 - 0x4.7 */
	u_int8_t request_message_sequence;
	/* Description - Response message sequential number. 
For a specific request, the response message sequential number is 
the following one. 
In addition, the last message (when lst is '1') should be 0. */
	/* 0x4.16 - 0x4.23 */
	u_int8_t response_message_sequence;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Index related to the specific query_type. 
For query_type = 1,2 this field is neglected. */
	/* 0x8.0 - 0x8.7 */
	u_int8_t query_index;
	/* Description - First. If set to '1', this is the first message */
	/* 0x8.29 - 0x8.29 */
	u_int8_t frst;
	/* Description - More data available */
	/* 0x8.30 - 0x8.30 */
	u_int8_t mid;
	/* Description - Last. If set to '1', this is the last message */
	/* 0x8.31 - 0x8.31 */
	u_int8_t lst;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Properties of that field are based on query_type.
For slot information query_type data - See Table 498, "slot_info 
Register Layout," on page 599
For devices on slot query_type data- See Table 500, "device_info 
Register Layout," on page 600 */
	/* 0x10.0 - 0x2c.31 */
	union reg_access_switch_mddq_data_auto data;
};

/* device_info */
void reg_access_switch_device_info_pack(const struct reg_access_switch_device_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_device_info_unpack(struct reg_access_switch_device_info *ptr_struct, const u_int8_t *ptr_buff);
/* slot_info */
void reg_access_switch_slot_info_pack(const struct reg_access_switch_slot_info *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_slot_info_unpack(struct reg_access_switch_slot_info *ptr_struct, const u_int8_t *ptr_buff);
/* mddq */
void reg_access_switch_mddq_pack(const struct reg_access_switch_mddq *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_unpack(struct reg_access_switch_mddq *ptr_struct, const u_int8_t *ptr_buff);
unsigned int reg_access_switch_mddq_size(void);
#define REG_ACCESS_SWITCH_MDDQ_SIZE    (0x30)

#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_SWITCH_LAYOUTS_H
