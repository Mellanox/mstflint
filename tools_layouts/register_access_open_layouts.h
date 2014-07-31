
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
 *** This file was generated at "2014-07-08 14:00:34"
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
int register_access_mfba_size();
#define REGISTER_ACCESS_MFBA_SIZE    (0x10c)
void register_access_mfba_dump(const struct register_access_mfba *ptr_struct, FILE* file);
/* mfpa */
void register_access_mfpa_pack(const struct register_access_mfpa *ptr_struct, u_int8_t* ptr_buff);
void register_access_mfpa_unpack(struct register_access_mfpa *ptr_struct, const u_int8_t* ptr_buff);
void register_access_mfpa_print(const struct register_access_mfpa *ptr_struct, FILE* file, int indent_level);
int register_access_mfpa_size();
#define REGISTER_ACCESS_MFPA_SIZE    (0x24)
void register_access_mfpa_dump(const struct register_access_mfpa *ptr_struct, FILE* file);
/* mfbe */
void register_access_mfbe_pack(const struct register_access_mfbe *ptr_struct, u_int8_t* ptr_buff);
void register_access_mfbe_unpack(struct register_access_mfbe *ptr_struct, const u_int8_t* ptr_buff);
void register_access_mfbe_print(const struct register_access_mfbe *ptr_struct, FILE* file, int indent_level);
int register_access_mfbe_size();
#define REGISTER_ACCESS_MFBE_SIZE    (0xc)
void register_access_mfbe_dump(const struct register_access_mfbe *ptr_struct, FILE* file);
/* register_access_open_Nodes */
void register_access_register_access_open_Nodes_pack(const union register_access_register_access_open_Nodes *ptr_struct, u_int8_t* ptr_buff);
void register_access_register_access_open_Nodes_unpack(union register_access_register_access_open_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void register_access_register_access_open_Nodes_print(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file, int indent_level);
int register_access_register_access_open_Nodes_size();
#define REGISTER_ACCESS_REGISTER_ACCESS_OPEN_NODES_SIZE    (0x10c)
void register_access_register_access_open_Nodes_dump(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // REGISTER_ACCESS_OPEN_LAYOUTS_H
