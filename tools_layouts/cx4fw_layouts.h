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
         *** This file was generated at "2018-02-13 10:20:32"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/cx4fw/cx4fw.adb --file-prefix cx4fw --prefix cx4fw_
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
struct cx4fw_image_signature_256 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - time based UUID for this signature */
	/* 0x0.0 - 0xc.31 */
	u_int32_t signature_uuid[4];
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The UUID of the keypair used for signing this file */
	/* 0x10.0 - 0x1c.31 */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The signature itself */
	/* 0x20.0 - 0x11c.31 */
	u_int32_t signature[64];
};

/* Description -   */
/* Size in bytes - 576 */
struct cx4fw_image_signature_512 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - time based UUID for this signature */
	/* 0x0.0 - 0xc.31 */
	u_int32_t signature_uuid[4];
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The UUID of the keypair used for signing this file */
	/* 0x10.0 - 0x1c.31 */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - The signature itself */
	/* 0x20.0 - 0x21c.31 */
	u_int32_t signature[128];
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
	/* Description - MFG_INFO section minor version */
	/* 0x1c.16 - 0x1c.23 */
	u_int8_t minor_version;
	/* Description - MFG_INFO section major version */
	/* 0x1c.24 - 0x1c.31 */
	u_int8_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct cx4fw_guids guids;
};

/* Description -   */
/* Size in bytes - 288 */
struct cx4fw_public_key_2048 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The authentication mechanism used with this key
0x0: INVALID_ENTRY
0x1: SHA256
_
DIGEST
0x3: _2048BIT_RSASSA_PKCS1_v1_5_WITH_SHA256 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t auth_type;
	/* Description - This key can be used for authenticating Factory Re Configuration responses. */
	/* 0x0.27 - 0x0.27 */
	u_int8_t frc_en;
	/* Description - This key can be used for authenticating NVCONFIG files at MLLNX level. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t mlnx_nvconf_en;
	/* Description - This key can be used for authenticating NVCONFIG files at OEM level. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t vendor_nvconf_en;
	/* Description - This key can be used for authenticating CS tokens at OEM level. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t cs_token_en;
	/* Description - This key can be used for authenticating firmware, DBG_FW and DBG tokens */
	/* 0x0.31 - 0x0.31 */
	u_int8_t fw_en;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The public key exponent.In most cases, the standard exponent (65537) will be used (per RFC4871). */
	/* 0xc.0 - 0xc.31 */
	u_int32_t public_key_exp;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - UUID of this key.The UUID is created by the sign server when it generates a new RSA key-pair. */
	/* 0x10.24 - 0x20.23 */
	u_int8_t keypair_uuid[16];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - A 2048 bit public-key  (0x100 bytes) */
	/* 0x20.24 - 0x120.23 */
	u_int8_t key[256];
};

/* Description -   */
/* Size in bytes - 544 */
struct cx4fw_public_key_4096 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The authentication mechanism used with this key
0x0: INVALID_ENTRY
0x1: SHA256
_
DIGEST
0x3: _2048BIT_RSASSA_PKCS1_v1_5_WITH_SHA256 */
	/* 0x0.0 - 0x0.7 */
	u_int8_t auth_type;
	/* Description - This key can be used for authenticating Factory Re Configuration responses. */
	/* 0x0.27 - 0x0.27 */
	u_int8_t frc_en;
	/* Description - This key can be used for authenticating NVCONFIG files at MLLNX level. */
	/* 0x0.28 - 0x0.28 */
	u_int8_t mlnx_nvconf_en;
	/* Description - This key can be used for authenticating NVCONFIG files at OEM level. */
	/* 0x0.29 - 0x0.29 */
	u_int8_t vendor_nvconf_en;
	/* Description - This key can be used for authenticating CS tokens at OEM level. */
	/* 0x0.30 - 0x0.30 */
	u_int8_t cs_token_en;
	/* Description - This key can be used for authenticating firmware, DBG_FW and DBG tokens */
	/* 0x0.31 - 0x0.31 */
	u_int8_t fw_en;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The public key exponent.In most cases, the standard exponent (65537) will be used (per RFC4871). */
	/* 0xc.0 - 0xc.31 */
	u_int32_t public_key_exp;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - UUID of this key.The UUID is created by the sign server when it generates a new RSA key-pair. */
	/* 0x10.24 - 0x20.23 */
	u_int8_t keypair_uuid[16];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - A 2048 bit public-key  (0x100 bytes) */
	/* 0x20.24 - 0x220.23 */
	u_int16_t key[256];
};

/* Description -   */
/* Size in bytes - 576 */
union cx4fw_cx4fw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x13c.31 */
	struct cx4fw_image_signature_256 image_signature_256;
	/* Description -  */
	/* 0x0.0 - 0x23c.31 */
	struct cx4fw_image_signature_512 image_signature_512;
	/* Description -  */
	/* 0x0.0 - 0x1fc.31 */
	struct cx4fw_device_info device_info;
	/* Description -  */
	/* 0x0.0 - 0x13c.31 */
	struct cx4fw_mfg_info mfg_info;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct cx4fw_guids guids;
	/* Description -  */
	/* 0x0.0 - 0x11c.31 */
	struct cx4fw_public_key_2048 public_key_2048;
	/* Description -  */
	/* 0x0.0 - 0x21c.31 */
	struct cx4fw_public_key_4096 public_key_4096;
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
/* image_signature_256 */
void cx4fw_image_signature_256_pack(const struct cx4fw_image_signature_256 *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_image_signature_256_unpack(struct cx4fw_image_signature_256 *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_image_signature_256_print(const struct cx4fw_image_signature_256 *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_image_signature_256_size(void);
#define CX4FW_IMAGE_SIGNATURE_256_SIZE    (0x140)
void cx4fw_image_signature_256_dump(const struct cx4fw_image_signature_256 *ptr_struct, FILE *fd);
/* image_signature_512 */
void cx4fw_image_signature_512_pack(const struct cx4fw_image_signature_512 *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_image_signature_512_unpack(struct cx4fw_image_signature_512 *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_image_signature_512_print(const struct cx4fw_image_signature_512 *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_image_signature_512_size(void);
#define CX4FW_IMAGE_SIGNATURE_512_SIZE    (0x240)
void cx4fw_image_signature_512_dump(const struct cx4fw_image_signature_512 *ptr_struct, FILE *fd);
/* mfg_info */
void cx4fw_mfg_info_pack(const struct cx4fw_mfg_info *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_mfg_info_unpack(struct cx4fw_mfg_info *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_mfg_info_print(const struct cx4fw_mfg_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_mfg_info_size(void);
#define CX4FW_MFG_INFO_SIZE    (0x140)
void cx4fw_mfg_info_dump(const struct cx4fw_mfg_info *ptr_struct, FILE *fd);
/* public_key_2048 */
void cx4fw_public_key_2048_pack(const struct cx4fw_public_key_2048 *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_public_key_2048_unpack(struct cx4fw_public_key_2048 *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_public_key_2048_print(const struct cx4fw_public_key_2048 *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_public_key_2048_size(void);
#define CX4FW_PUBLIC_KEY_2048_SIZE    (0x120)
void cx4fw_public_key_2048_dump(const struct cx4fw_public_key_2048 *ptr_struct, FILE *fd);
/* public_key_4096 */
void cx4fw_public_key_4096_pack(const struct cx4fw_public_key_4096 *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_public_key_4096_unpack(struct cx4fw_public_key_4096 *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_public_key_4096_print(const struct cx4fw_public_key_4096 *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_public_key_4096_size(void);
#define CX4FW_PUBLIC_KEY_4096_SIZE    (0x220)
void cx4fw_public_key_4096_dump(const struct cx4fw_public_key_4096 *ptr_struct, FILE *fd);
/* cx4fw_Nodes */
void cx4fw_cx4fw_Nodes_pack(const union cx4fw_cx4fw_Nodes *ptr_struct, u_int8_t *ptr_buff);
void cx4fw_cx4fw_Nodes_unpack(union cx4fw_cx4fw_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void cx4fw_cx4fw_Nodes_print(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int cx4fw_cx4fw_Nodes_size(void);
#define CX4FW_CX4FW_NODES_SIZE    (0x240)
void cx4fw_cx4fw_Nodes_dump(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // CX4FW_LAYOUTS_H
