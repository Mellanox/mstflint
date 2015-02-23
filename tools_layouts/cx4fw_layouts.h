
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
 *** This file was generated at "2015-02-05 17:00:26"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/connectx4/connectx4.adb --file-prefix cx4fw --prefix cx4fw_
 ***/
#ifndef CX4FW_LAYOUTS_H
#define CX4FW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"/* Description -   */
/* Size in bytes - 8 */
struct cx4fw_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 4.31 */
	 u_int32_t hi;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 8.31 */
	 u_int32_t lo;
};

/* Description -   */
/* Size in bytes - 16 */
struct cx4fw_uid_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of allocated UIDs in this entry */
	/* 0.0 - 0.7 */
	 u_int8_t num_allocated;
	/* Description - Step size by which to derive the UIDs for this entry
See struct description */
	/* 0.8 - 0.15 */
	 u_int8_t step;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For MACs, the upper 16 bits in the 'hi' dword are reserved */
	/* 8.0 - 16.31 */
	 u_int64_t uid;
};

/* Description -   */
/* Size in bytes - 64 */
struct cx4fw_guids {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids, is used for system GUID, node GUID and port GUID of port 0. ;/Multiple UIDs can be assigned to a single port, to be used for multiple virtual guests, multi host and managment */
	/* 0.0 - 16.31 */
	 struct cx4fw_uid_entry guids;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 16.0 - 32.31 */
	 struct cx4fw_uid_entry macs;
};

/* Description -   */
/* Size in bytes - 16 */
struct cx4fw_operation_key {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 0.15 */
	 u_int16_t key_modifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.0 - 16.31 */
	 u_int64_t key;
};

/* Description -   */
/* Size in bytes - 320 */
struct cx4fw_mfg_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.24 - 16.23 */
	 char psid[17];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - When this bit is set, the GUIDs should be taken from the device_info node.
When this bit is cleared, the GUIDs should be taken from the mfg_info node. */
	/* 28.0 - 28.0 */
	 u_int8_t guids_override_en;
	/* Description - MFG_INFO section minor version */
	/* 28.16 - 28.23 */
	 u_int8_t minor_version;
	/* Description - MFG_INFO section major version */
	/* 28.24 - 32.31 */
	 u_int8_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 32.0 - 96.31 */
	 struct cx4fw_guids guids;
};

/* Description -   */
/* Size in bytes - 512 */
struct cx4fw_device_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 4.31 */
	 u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 8.31 */
	 u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.0 - 12.31 */
	 u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 12.0 - 16.31 */
	 u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 16.0 - 16.7 */
	 u_int8_t minor_version;
	/* Description - Format version for this struct */
	/* 16.8 - 16.16 */
	 u_int16_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 32.0 - 96.31 */
	 struct cx4fw_guids guids;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 108.0 - 108.15 */
	 u_int16_t vsd_vendor_id;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 112.24 - 320.23 */
	 char vsd[209];
/*---------------- DWORD[88] (Offset 0x160) ----------------*/
	/* Description -  */
	/* 352.0 - 416.31 */
	 struct cx4fw_operation_key keys[4];
};

/* Description -   */
/* Size in bytes - 512 */
union cx4fw_cx4fw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 512.31 */
	 struct cx4fw_device_info device_info;
	/* Description -  */
	/* 0.0 - 320.31 */
	 struct cx4fw_mfg_info mfg_info;
	/* Description -  */
	/* 0.0 - 64.31 */
	 struct cx4fw_guids guids;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* uint64 */
void cx4fw_uint64_pack(const struct cx4fw_uint64 *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_uint64_unpack(struct cx4fw_uint64 *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_uint64_print(const struct cx4fw_uint64 *ptr_struct, FILE* file, int indent_level);
int cx4fw_uint64_size(void);
#define CX4FW_UINT64_SIZE    (0x8)
void cx4fw_uint64_dump(const struct cx4fw_uint64 *ptr_struct, FILE* file);
;
/* uid_entry */
void cx4fw_uid_entry_pack(const struct cx4fw_uid_entry *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_uid_entry_unpack(struct cx4fw_uid_entry *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_uid_entry_print(const struct cx4fw_uid_entry *ptr_struct, FILE* file, int indent_level);
int cx4fw_uid_entry_size(void);
#define CX4FW_UID_ENTRY_SIZE    (0x10)
void cx4fw_uid_entry_dump(const struct cx4fw_uid_entry *ptr_struct, FILE* file);
;
/* guids */
void cx4fw_guids_pack(const struct cx4fw_guids *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_guids_unpack(struct cx4fw_guids *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_guids_print(const struct cx4fw_guids *ptr_struct, FILE* file, int indent_level);
int cx4fw_guids_size(void);
#define CX4FW_GUIDS_SIZE    (0x40)
void cx4fw_guids_dump(const struct cx4fw_guids *ptr_struct, FILE* file);
;
/* operation_key */
void cx4fw_operation_key_pack(const struct cx4fw_operation_key *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_operation_key_unpack(struct cx4fw_operation_key *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_operation_key_print(const struct cx4fw_operation_key *ptr_struct, FILE* file, int indent_level);
int cx4fw_operation_key_size(void);
#define CX4FW_OPERATION_KEY_SIZE    (0x10)
void cx4fw_operation_key_dump(const struct cx4fw_operation_key *ptr_struct, FILE* file);
;
/* mfg_info */
void cx4fw_mfg_info_pack(const struct cx4fw_mfg_info *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_mfg_info_unpack(struct cx4fw_mfg_info *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_mfg_info_print(const struct cx4fw_mfg_info *ptr_struct, FILE* file, int indent_level);
int cx4fw_mfg_info_size(void);
#define CX4FW_MFG_INFO_SIZE    (0x140)
void cx4fw_mfg_info_dump(const struct cx4fw_mfg_info *ptr_struct, FILE* file);
;
/* device_info */
void cx4fw_device_info_pack(const struct cx4fw_device_info *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_device_info_unpack(struct cx4fw_device_info *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_device_info_print(const struct cx4fw_device_info *ptr_struct, FILE* file, int indent_level);
int cx4fw_device_info_size(void);
#define CX4FW_DEVICE_INFO_SIZE    (0x200)
void cx4fw_device_info_dump(const struct cx4fw_device_info *ptr_struct, FILE* file);
;
/* cx4fw_Nodes */
void cx4fw_cx4fw_Nodes_pack(const union cx4fw_cx4fw_Nodes *ptr_struct, u_int8_t* ptr_buff);
void cx4fw_cx4fw_Nodes_unpack(union cx4fw_cx4fw_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void cx4fw_cx4fw_Nodes_print(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE* file, int indent_level);
int cx4fw_cx4fw_Nodes_size(void);
#define CX4FW_CX4FW_NODES_SIZE    (0x200)
void cx4fw_cx4fw_Nodes_dump(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE* file);
;


#ifdef __cplusplus
}
#endif

#endif // CX4FW_LAYOUTS_H
