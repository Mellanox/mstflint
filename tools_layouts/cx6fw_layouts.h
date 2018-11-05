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
         *** This file was generated at "2018-08-29 13:02:13"
         *** by:
         ***    > /mswg/release/tools/a-me/a-me-1.0.110/adabe_plugins/adb2c/adb2pack.py --input adb/cx6fw/cx6fw.adb --file-prefix cx6fw --prefix cx6fw_
         ***/
#ifndef CX6FW_LAYOUTS_H
#define CX6FW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct cx6fw_hw_pointer_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - pointer */
	/* 0x0.0 - 0x0.31 */
	 u_int32_t ptr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - crc16 as calculated by HW */
	/* 0x4.0 - 0x4.15 */
	 u_int16_t crc;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct cx6fw_hw_pointers {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct cx6fw_hw_pointer_entry boot_record_ptr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 struct cx6fw_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	 struct cx6fw_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 struct cx6fw_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	 struct cx6fw_hw_pointer_entry authentication_start_ptr;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	 struct cx6fw_hw_pointer_entry authentication_end_ptr;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	 struct cx6fw_hw_pointer_entry digest_mdk_ptr;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	 struct cx6fw_hw_pointer_entry digest_recovery_key_ptr;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr8;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr9;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr10;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr11;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr12;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr13;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr14;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	 struct cx6fw_hw_pointer_entry reserved_ptr15;
};

/* Description -   */
/* Size in bytes - 512 */
union cx6fw_cx6fw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	 struct cx6fw_hw_pointers hw_pointers;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* hw_pointer_entry */
void cx6fw_hw_pointer_entry_pack(const struct cx6fw_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff);
void cx6fw_hw_pointer_entry_unpack(struct cx6fw_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff);
void cx6fw_hw_pointer_entry_print(const struct cx6fw_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int cx6fw_hw_pointer_entry_size(void);
#define CX6FW_HW_POINTER_ENTRY_SIZE    (0x8)
void cx6fw_hw_pointer_entry_dump(const struct cx6fw_hw_pointer_entry *ptr_struct, FILE *fd);
/* hw_pointers */
void cx6fw_hw_pointers_pack(const struct cx6fw_hw_pointers *ptr_struct, u_int8_t *ptr_buff);
void cx6fw_hw_pointers_unpack(struct cx6fw_hw_pointers *ptr_struct, const u_int8_t *ptr_buff);
void cx6fw_hw_pointers_print(const struct cx6fw_hw_pointers *ptr_struct, FILE *fd, int indent_level);
unsigned int cx6fw_hw_pointers_size(void);
#define CX6FW_HW_POINTERS_SIZE    (0x80)
void cx6fw_hw_pointers_dump(const struct cx6fw_hw_pointers *ptr_struct, FILE *fd);
/* cx6fw_Nodes */
void cx6fw_cx6fw_Nodes_pack(const union cx6fw_cx6fw_Nodes *ptr_struct, u_int8_t *ptr_buff);
void cx6fw_cx6fw_Nodes_unpack(union cx6fw_cx6fw_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void cx6fw_cx6fw_Nodes_print(const union cx6fw_cx6fw_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int cx6fw_cx6fw_Nodes_size(void);
#define CX6FW_CX6FW_NODES_SIZE    (0x200)
void cx6fw_cx6fw_Nodes_dump(const union cx6fw_cx6fw_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // CX6FW_LAYOUTS_H
