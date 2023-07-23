/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

         *** This file was generated at "2023-06-01 20:24:55"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/fs5_image_layout/fs5_image_layout.adb --file-prefix fs5_image_layout --prefix fs5_image_layout_ --no-adb-utils
         ***/
#ifndef FS5_IMAGE_LAYOUT_LAYOUTS_H
#define FS5_IMAGE_LAYOUT_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct fs5_image_layout_hw_pointer_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - pointer */
	/* 0x0.0 - 0x0.31 */
	u_int32_t ptr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - crc16 as calculated by HW */
	/* 0x4.0 - 0x4.15 */
	u_int16_t crc;
};

/* Description -  BCH - boot component header */
/* Size in bytes - 8192 */
struct fs5_image_layout_boot_component_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t component_digest;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t component_security_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t component_metadata;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	u_int32_t signature;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	u_int32_t public_key;
/*---------------- DWORD[1977] (Offset 0x1ee4) ----------------*/
	/* Description -  */
	/* 0x1ee4.0 - 0x1ee4.31 */
	u_int32_t length;
/*---------------- DWORD[1978] (Offset 0x1ee8) ----------------*/
	/* Description -  */
	/* 0x1ee8.0 - 0x1ee8.31 */
	u_int32_t load_offset;
/*---------------- DWORD[1979] (Offset 0x1eec) ----------------*/
	/* Description -  */
	/* 0x1eec.0 - 0x1eec.31 */
	u_int32_t hash_offset;
/*---------------- DWORD[1980] (Offset 0x1ef0) ----------------*/
	/* Description -  */
	/* 0x1ef0.0 - 0x1ef0.31 */
	u_int32_t branch_offset;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct fs5_image_layout_hw_pointers_gilboa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct fs5_image_layout_hw_pointer_entry psc_bct_pointer;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	struct fs5_image_layout_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	struct fs5_image_layout_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	struct fs5_image_layout_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_bch_pointer;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_pointer;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	struct fs5_image_layout_hw_pointer_entry ncore_bch_pointer;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	struct fs5_image_layout_hw_pointer_entry reserved;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	struct fs5_image_layout_hw_pointer_entry psc_fw_bch_pointer;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	struct fs5_image_layout_hw_pointer_entry psc_fw_pointer;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	struct fs5_image_layout_hw_pointer_entry image_info_section_pointer;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	struct fs5_image_layout_hw_pointer_entry image_signature_pointer;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	struct fs5_image_layout_hw_pointer_entry public_key_pointer;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	struct fs5_image_layout_hw_pointer_entry fw_security_version_pointer;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	struct fs5_image_layout_hw_pointer_entry gcm_iv_delta_pointer;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	struct fs5_image_layout_hw_pointer_entry ncore_hashes_pointer;
};

/* Description -   */
/* Size in bytes - 8192 */
union fs5_image_layout_fs5_image_layout_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	struct fs5_image_layout_hw_pointers_gilboa hw_pointers_gilboa;
	/* Description -  */
	/* 0x0.0 - 0x1ffc.31 */
	struct fs5_image_layout_boot_component_header boot_component_header;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* hw_pointer_entry */
void fs5_image_layout_hw_pointer_entry_pack(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_unpack(struct fs5_image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_print(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_hw_pointer_entry_size(void);
#define FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE    (0x8)
void fs5_image_layout_hw_pointer_entry_dump(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd);
/* boot_component_header */
void fs5_image_layout_boot_component_header_pack(const struct fs5_image_layout_boot_component_header *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_unpack(struct fs5_image_layout_boot_component_header *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_print(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_header_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE    (0x2000)
void fs5_image_layout_boot_component_header_dump(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd);
/* hw_pointers_gilboa */
void fs5_image_layout_hw_pointers_gilboa_pack(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointers_gilboa_unpack(struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointers_gilboa_print(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_hw_pointers_gilboa_size(void);
#define FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE    (0x80)
void fs5_image_layout_hw_pointers_gilboa_dump(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd);
/* fs5_image_layout_Nodes */
void fs5_image_layout_fs5_image_layout_Nodes_pack(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_fs5_image_layout_Nodes_unpack(union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_fs5_image_layout_Nodes_print(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_fs5_image_layout_Nodes_size(void);
#define FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE    (0x2000)
void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // FS5_IMAGE_LAYOUT_LAYOUTS_H

