
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
         *** This file was generated at "2023-02-06 14:12:04"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/fs5_image_layout/fs5_image_layout.adb --file-prefix fs5_image_layout --prefix fs5_image_layout_ --no-adb-utils
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

/* Description -  Boot2 header */
/* Size in bytes - 20 */
struct fs5_image_layout_boot2_header_gilboa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t load_addr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t dw_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t branch_addr_lsb;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t branch_addr_msb;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	u_int32_t crc;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct fs5_image_layout_hw_pointers_gilboa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct fs5_image_layout_hw_pointer_entry toc_ptr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	struct fs5_image_layout_hw_pointer_entry tool2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	struct fs5_image_layout_hw_pointer_entry image_info_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_bch_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_ptr;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	struct fs5_image_layout_hw_pointer_entry ncore_bch_ptr;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	struct fs5_image_layout_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	struct fs5_image_layout_hw_pointer_entry ncore_hashes_ptr;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	struct fs5_image_layout_hw_pointer_entry psc_fw_bch_ptr;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	struct fs5_image_layout_hw_pointer_entry psc_fw_ptr;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr10;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr11;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr12;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr13;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr14;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	struct fs5_image_layout_hw_pointer_entry reserved_ptr15;
};

/* Description -   */
/* Size in bytes - 128 */
union fs5_image_layout_fs5_image_layout_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x10.31 */
	struct fs5_image_layout_boot2_header_gilboa boot2_header_gilboa;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	struct fs5_image_layout_hw_pointers_gilboa hw_pointers_gilboa;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* hw_pointer_entry */
void fs5_image_layout_hw_pointer_entry_pack(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_unpack(struct fs5_image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_print(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_hw_pointer_entry_size(void);
#define FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE    (0x8)
void fs5_image_layout_hw_pointer_entry_dump(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd);
/* boot2_header_gilboa */
void fs5_image_layout_boot2_header_gilboa_pack(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot2_header_gilboa_unpack(struct fs5_image_layout_boot2_header_gilboa *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot2_header_gilboa_print(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot2_header_gilboa_size(void);
#define FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE    (0x14)
void fs5_image_layout_boot2_header_gilboa_dump(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, FILE *fd);
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
#define FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE    (0x80)
void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // FS5_IMAGE_LAYOUT_LAYOUTS_H

