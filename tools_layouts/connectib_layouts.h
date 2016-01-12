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

#ifndef CONNECTIB_LAYOUTS_H
#define CONNECTIB_LAYOUTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"

/* Description -   */
/* Size in bytes - 16 */
struct connectib_FW_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0.16 - 4.31 */
     u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description -  */
    /* 4.0 - 4.15 */
     u_int16_t SUBMINOR;
    /* Description -  */
    /* 4.16 - 8.31 */
     u_int16_t MINOR;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description -  */
    /* 8.8 - 8.15 */
     u_int8_t Hour;
    /* Description -  */
    /* 8.16 - 8.23 */
     u_int8_t Minutes;
    /* Description -  */
    /* 8.24 - 12.31 */
     u_int8_t Seconds;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
    /* Description -  */
    /* 12.0 - 12.7 */
     u_int8_t Day;
    /* Description -  */
    /* 12.8 - 12.15 */
     u_int8_t Month;
    /* Description -  */
    /* 12.16 - 16.31 */
     u_int16_t Year;
};

/* Description -   */
/* Size in bytes - 32 */
struct connectib_icmd_get_fw_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0.0 - 16.31 */
     struct connectib_FW_VERSION fw_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
    /* Description - Hash gen file signature */
    /* 16.0 - 16.15 */
     u_int16_t hash_signature;
};

/* FW_VERSION */
void connectib_FW_VERSION_pack(const struct connectib_FW_VERSION *ptr_struct, u_int8_t* ptr_buff);
void connectib_FW_VERSION_unpack(struct connectib_FW_VERSION *ptr_struct, const u_int8_t* ptr_buff);
void connectib_FW_VERSION_print(const struct connectib_FW_VERSION *ptr_struct, FILE* file, int indent_level);
int connectib_FW_VERSION_size(void);
#define CONNECTIB_FW_VERSION_SIZE    (0x10)
/* icmd_get_fw_info */
void connectib_icmd_get_fw_info_pack(const struct connectib_icmd_get_fw_info *ptr_struct, u_int8_t* ptr_buff);
void connectib_icmd_get_fw_info_unpack(struct connectib_icmd_get_fw_info *ptr_struct, const u_int8_t* ptr_buff);
void connectib_icmd_get_fw_info_print(const struct connectib_icmd_get_fw_info *ptr_struct, FILE* file, int indent_level);
int connectib_icmd_get_fw_info_size(void);
#define CONNECTIB_ICMD_GET_FW_INFO_SIZE    (0x20)

#ifdef __cplusplus
}
#endif

#endif // CONNECTIB_LAYOUTS_H
