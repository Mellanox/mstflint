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
 *** This file was generated at "2016-02-23 00:12:07"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/register_access_open/register_access_open.adb --file-prefix register_access_open --prefix register_access_
 ***/
#ifndef REGISTER_ACCESS_OPEN_LAYOUTS_H
#define REGISTER_ACCESS_OPEN_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"/* Description -   */
/* Size in bytes - 268 */
struct register_access_mfba {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash Select */
	/* 0.4 - 0.5 */
	 u_int8_t fs;
	/* Description - Parallel */
	/* 0.8 - 0.8 */
	 u_int8_t p;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Transaction size */
	/* 4.0 - 4.8 */
	 u_int16_t size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - address in bytes */
	/* 8.0 - 8.23 */
	 u_int32_t address;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - data */
	/* 12.0 - 268.31 */
	 u_int32_t data[64];
};

/* Description -   */
/* Size in bytes - 36 */
struct register_access_mfpa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash Select */
	/* 0.4 - 0.5 */
	 u_int8_t fs;
	/* Description - Parallel */
	/* 0.8 - 0.8 */
	 u_int8_t p;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - address in bytes */
	/* 4.0 - 4.23 */
	 u_int32_t boot_address;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - number of flash devices connected */
	/* 16.0 - 16.3 */
	 u_int8_t flash_num;
	/* Description -  */
	/* 16.29 - 16.29 */
	 u_int8_t bulk_64kb_erase_en;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Flash JEDEC ID */
	/* 20.0 - 20.23 */
	 u_int32_t jedec_id;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Flash sectore size */
	/* 24.0 - 24.9 */
	 u_int16_t sector_size;
	/* Description -  */
	/* 24.16 - 24.23 */
	 u_int8_t block_allignment;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - capability mask ;bit 0:Parallel flash Support;else:Reserved  */
	/* 28.0 - 32.31 */
	 u_int32_t capability_mask;
};

/* Description -   */
/* Size in bytes - 12 */
struct register_access_mfbe {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash Select */
	/* 0.4 - 0.5 */
	 u_int8_t fs;
	/* Description - Parallel */
	/* 0.8 - 0.8 */
	 u_int8_t p;
	/* Description - erase 64KB flash area */
	/* 0.29 - 0.29 */
	 u_int8_t bulk_64kb_erase;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - address in bytes */
	/* 8.0 - 8.23 */
	 u_int32_t address;
};

/* Description -   */
/* Size in bytes - 268 */
union register_access_register_access_open_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 12.31 */
	 struct register_access_mfbe mfbe;
	/* Description -  */
	/* 0.0 - 36.31 */
	 struct register_access_mfpa mfpa;
	/* Description -  */
	/* 0.0 - 268.31 */
	 struct register_access_mfba mfba;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* mfba */
void register_access_mfba_pack(const struct register_access_mfba *ptr_struct, u_int8_t* ptr_buff);
void register_access_mfba_unpack(struct register_access_mfba *ptr_struct, const u_int8_t* ptr_buff);
void register_access_mfba_print(const struct register_access_mfba *ptr_struct, FILE* file, int indent_level);
int register_access_mfba_size(void);
#define REGISTER_ACCESS_MFBA_SIZE    (0x10c)
void register_access_mfba_dump(const struct register_access_mfba *ptr_struct, FILE* file);
/* mfpa */
void register_access_mfpa_pack(const struct register_access_mfpa *ptr_struct, u_int8_t* ptr_buff);
void register_access_mfpa_unpack(struct register_access_mfpa *ptr_struct, const u_int8_t* ptr_buff);
void register_access_mfpa_print(const struct register_access_mfpa *ptr_struct, FILE* file, int indent_level);
int register_access_mfpa_size(void);
#define REGISTER_ACCESS_MFPA_SIZE    (0x24)
void register_access_mfpa_dump(const struct register_access_mfpa *ptr_struct, FILE* file);
/* mfbe */
void register_access_mfbe_pack(const struct register_access_mfbe *ptr_struct, u_int8_t* ptr_buff);
void register_access_mfbe_unpack(struct register_access_mfbe *ptr_struct, const u_int8_t* ptr_buff);
void register_access_mfbe_print(const struct register_access_mfbe *ptr_struct, FILE* file, int indent_level);
int register_access_mfbe_size(void);
#define REGISTER_ACCESS_MFBE_SIZE    (0xc)
void register_access_mfbe_dump(const struct register_access_mfbe *ptr_struct, FILE* file);
/* register_access_open_Nodes */
void register_access_register_access_open_Nodes_pack(const union register_access_register_access_open_Nodes *ptr_struct, u_int8_t* ptr_buff);
void register_access_register_access_open_Nodes_unpack(union register_access_register_access_open_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void register_access_register_access_open_Nodes_print(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file, int indent_level);
int register_access_register_access_open_Nodes_size(void);
#define REGISTER_ACCESS_REGISTER_ACCESS_OPEN_NODES_SIZE    (0x10c)
void register_access_register_access_open_Nodes_dump(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // REGISTER_ACCESS_OPEN_LAYOUTS_H
