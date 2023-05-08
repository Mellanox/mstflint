/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
         *** This file was generated at "2023-01-24 14:29:07"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/cx4fw/cx4fw.adb --file-prefix cx4fw --prefix cx4fw_ --no-adb-utils
         ***/
#ifndef CX4FW_LAYOUTS_H
#define CX4FW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 8 */
struct cx4fw_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 16 */
struct cx4fw_uid_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of allocated UIDs in this entry */
	/* 0x0.0 - 0x0.7 */
	u_int8_t num_allocated;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Step size by which to derive the UIDs for this entry
See struct description */
	/* 0x0.8 - 0x0.15 */
	u_int8_t step;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For MACs, the upper 16 bits in the 'hi' dword are reserved */
	/* 0x8.0 - 0xc.31 */
	u_int64_t uid;
};

/* Description -   */
/* Size in bytes - 64 */
struct cx4fw_guids {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids, is used for system GUID, node GUID and port GUID of port 0. ;/Multiple UIDs can be assigned to a single port, to be used for multiple virtual guests, multi host and managment */
	/* 0x0.0 - 0xc.31 */
	struct cx4fw_uid_entry guids;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	struct cx4fw_uid_entry macs;
};

/* Description -   */
/* Size in bytes - 16 */
struct cx4fw_operation_key {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t key_modifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	u_int64_t key;
};

/* Description -   */
/* Size in bytes - 512 */
struct cx4fw_device_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 0x10.0 - 0x10.7 */
	u_int8_t minor_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 0x10.8 - 0x10.16 */
	u_int16_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct cx4fw_guids guids;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 0x6c.0 - 0x6c.15 */
	u_int16_t vsd_vendor_id;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.24 - 0x140.23 */
	char vsd[209];
/*---------------- DWORD[88] (Offset 0x160) ----------------*/
	/* Description -  */
	/* 0x160.0 - 0x19c.31 */
	struct cx4fw_operation_key keys[4];
};

/* Description -   */
/* Size in bytes - 320 */
struct cx4fw_mfg_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	char psid[17];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - When this bit is set, the GUIDs should be taken from the device_info node.
When this bit is cleared, the GUIDs should be taken from the mfg_info node. */
	/* 0x1c.0 - 0x1c.0 */
	u_int8_t guids_override_en;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - MFG_INFO section minor version */
	/* 0x1c.16 - 0x1c.23 */
	u_int8_t minor_version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - MFG_INFO section major version */
	/* 0x1c.24 - 0x1c.31 */
	u_int8_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct cx4fw_guids guids;
};

/* Description -   */
/* Size in bytes - 512 */
union cx4fw_cx4fw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x13c.31 */
	struct cx4fw_mfg_info mfg_info;
	/* Description -  */
	/* 0x0.0 - 0x1fc.31 */
	struct cx4fw_device_info device_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct cx4fw_guids guids;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* uint64 */
void cx4fw_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_uint64_size(void);
#define CX4FW_UINT64_SIZE    (0x8)
void cx4fw_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* uid_entry */
void cx4fw_uid_entry_pack(const struct cx4fw_uid_entry *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_uid_entry_unpack(struct cx4fw_uid_entry *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_uid_entry_print(const struct cx4fw_uid_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_uid_entry_size(void);
#define CX4FW_UID_ENTRY_SIZE    (0x10)
void cx4fw_uid_entry_dump(const struct cx4fw_uid_entry *ptr_struct, FILE *fd);
/* guids */
void cx4fw_guids_pack(const struct cx4fw_guids *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_guids_unpack(struct cx4fw_guids *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_guids_print(const struct cx4fw_guids *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_guids_size(void);
#define CX4FW_GUIDS_SIZE    (0x40)
void cx4fw_guids_dump(const struct cx4fw_guids *ptr_struct, FILE *fd);
/* operation_key */
void cx4fw_operation_key_pack(const struct cx4fw_operation_key *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_operation_key_unpack(struct cx4fw_operation_key *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_operation_key_print(const struct cx4fw_operation_key *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_operation_key_size(void);
#define CX4FW_OPERATION_KEY_SIZE    (0x10)
void cx4fw_operation_key_dump(const struct cx4fw_operation_key *ptr_struct, FILE *fd);
/* device_info */
void cx4fw_device_info_pack(const struct cx4fw_device_info *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_device_info_unpack(struct cx4fw_device_info *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_device_info_print(const struct cx4fw_device_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_device_info_size(void);
#define CX4FW_DEVICE_INFO_SIZE    (0x200)
void cx4fw_device_info_dump(const struct cx4fw_device_info *ptr_struct, FILE *fd);
/* mfg_info */
void cx4fw_mfg_info_pack(const struct cx4fw_mfg_info *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_mfg_info_unpack(struct cx4fw_mfg_info *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_mfg_info_print(const struct cx4fw_mfg_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_mfg_info_size(void);
#define CX4FW_MFG_INFO_SIZE    (0x140)
void cx4fw_mfg_info_dump(const struct cx4fw_mfg_info *ptr_struct, FILE *fd);
/* cx4fw_Nodes */
void cx4fw_cx4fw_Nodes_pack(const union cx4fw_cx4fw_Nodes *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_cx4fw_Nodes_unpack(union cx4fw_cx4fw_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_cx4fw_Nodes_print(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_cx4fw_Nodes_size(void);
#define CX4FW_CX4FW_NODES_SIZE    (0x200)
void cx4fw_cx4fw_Nodes_dump(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // CX4FW_LAYOUTS_H

