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
 *** This file was generated at "2014-03-11 10:10:14"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/tools/tools.adb --file-prefix tools --prefix tools_
 ***    and modified to fit the needs of mstflint.
 ***/
#ifndef TOOLS_LAYOUTS_H
#define TOOLS_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"

/* Description -   */
/* Size in bytes - 8 */
struct tools_mnv_hdr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - Tlv type */
    /* 0.0 - 0.15 */
     u_int16_t type;
    /* Description - size of tlv data in dwords (not including header) */
    /* 0.18 - 0.29 */
     u_int16_t length;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - Type Modifier. E.G.: Port number when the config is port related */
    /* 4.16 - 4.23 */
     u_int8_t type_mod;
    /* Description - Shadow: i.e if set the Fw will not update the tlv immediately but wait for a command */
    /* 4.24 - 4.24 */
     u_int8_t shadow;
    /* Description - Pad count: for non dword alligned tlvs */
    /* 4.25 - 4.26 */
     u_int8_t pad_cnt;
    /* Description - Data version can be set by caller or left as 0. */
    /* 4.28 - 8.31 */
     u_int8_t version;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_mnvia {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0.0 - 8.31 */
     struct tools_mnv_hdr mnv_hdr;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_mnvi {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0.0 - 8.31 */
     struct tools_mnv_hdr mnv_hdr;
};

/* Description -   */
/* Size in bytes - 256 */
struct tools_mnva {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0.0 - 8.31 */
     struct tools_mnv_hdr mnv_hdr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description -  */
    /* 8.24 - 136.23 */
     u_int8_t data[128];
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_sriov {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - The total number of VFs that can be supported. */
    /* 0.0 - 0.15 */
     u_int16_t total_vfs;
    /* Description - 1 when SRIOV is enabled: SRIOV capability will appear on the PCI configuration header. */
    /* 0.31 - 4.31 */
     u_int8_t sriov_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_bar_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - Base 2 log of the size of the physical functions first BAR, in MBs. E.g. for 8MB the value is 3. */
    /* 0.0 - 4.31 */
     u_int32_t log_uar_bar_size;
};

/* Description -   */
/* Size in bytes - 4 */
struct tools_vpi_settings {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - Default link type:
0  InfiniBand
1  Ethernet
 */
    /* 0.0 - 0.1 */
     u_int8_t network_link_type;
};

/* Description -   */
/* Size in bytes - 8 */
struct tools_wol {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* 0.9 - 0.9 */
     u_int8_t reserved0;
    /* Description - Enable Wake on magic packet */
    /* 0.10 - 0.10 */
     u_int8_t en_wol_magic;
    /* 0.11 - 0.11 */
     u_int8_t reserved1;
    /* 0.12 - 0.12 */
     u_int8_t reserved2;
    /* 0.13 - 0.13 */
     u_int8_t reserved3;
    /* 0.14 - 0.14 */
     u_int8_t reserved4;
    /* 0.15 - 0.15 */
     u_int8_t reserved5;
};
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/

/* mnv_hdr */
void tools_mnv_hdr_pack(const struct tools_mnv_hdr *ptr_struct, u_int8_t* ptr_buff);
void tools_mnv_hdr_unpack(struct tools_mnv_hdr *ptr_struct, const u_int8_t* ptr_buff);
void tools_mnv_hdr_print(const struct tools_mnv_hdr *ptr_struct, FILE* file, int indent_level);
int tools_mnv_hdr_size();
#define TOOLS_MNV_HDR_SIZE    (0x8)
void tools_mnv_hdr_dump(const struct tools_mnv_hdr *ptr_struct, FILE* file);
/* mnvia */
void tools_mnvia_pack(const struct tools_mnvia *ptr_struct, u_int8_t* ptr_buff);
void tools_mnvia_unpack(struct tools_mnvia *ptr_struct, const u_int8_t* ptr_buff);
void tools_mnvia_print(const struct tools_mnvia *ptr_struct, FILE* file, int indent_level);
int tools_mnvia_size();
#define TOOLS_MNVIA_SIZE    (0x8)
void tools_mnvia_dump(const struct tools_mnvia *ptr_struct, FILE* file);
/* mnvi */
void tools_mnvi_pack(const struct tools_mnvi *ptr_struct, u_int8_t* ptr_buff);
void tools_mnvi_unpack(struct tools_mnvi *ptr_struct, const u_int8_t* ptr_buff);
void tools_mnvi_print(const struct tools_mnvi *ptr_struct, FILE* file, int indent_level);
int tools_mnvi_size();
#define TOOLS_MNVI_SIZE    (0x8)
void tools_mnvi_dump(const struct tools_mnvi *ptr_struct, FILE* file);
/* mnva */
void tools_mnva_pack(const struct tools_mnva *ptr_struct, u_int8_t* ptr_buff);
void tools_mnva_unpack(struct tools_mnva *ptr_struct, const u_int8_t* ptr_buff);
void tools_mnva_print(const struct tools_mnva *ptr_struct, FILE* file, int indent_level);
int tools_mnva_size();
#define TOOLS_MNVA_SIZE    (0x100)
void tools_mnva_dump(const struct tools_mnva *ptr_struct, FILE* file);
/* sriov */
void tools_sriov_pack(const struct tools_sriov *ptr_struct, u_int8_t* ptr_buff);
void tools_sriov_unpack(struct tools_sriov *ptr_struct, const u_int8_t* ptr_buff);
void tools_sriov_print(const struct tools_sriov *ptr_struct, FILE* file, int indent_level);
int tools_sriov_size();
#define TOOLS_SRIOV_SIZE    (0x4)
void tools_sriov_dump(const struct tools_sriov *ptr_struct, FILE* file);
/* bar_size */
void tools_bar_size_pack(const struct tools_bar_size *ptr_struct, u_int8_t* ptr_buff);
void tools_bar_size_unpack(struct tools_bar_size *ptr_struct, const u_int8_t* ptr_buff);
void tools_bar_size_print(const struct tools_bar_size *ptr_struct, FILE* file, int indent_level);
int tools_bar_size_size();
#define TOOLS_BAR_SIZE_SIZE    (0x4)
void tools_bar_size_dump(const struct tools_bar_size *ptr_struct, FILE* file);
/* vpi_settings */
void tools_vpi_settings_pack(const struct tools_vpi_settings *ptr_struct, u_int8_t* ptr_buff);
void tools_vpi_settings_unpack(struct tools_vpi_settings *ptr_struct, const u_int8_t* ptr_buff);
void tools_vpi_settings_print(const struct tools_vpi_settings *ptr_struct, FILE* file, int indent_level);
int tools_vpi_settings_size();
#define TOOLS_VPI_SETTINGS_SIZE    (0x4)
void tools_vpi_settings_dump(const struct tools_vpi_settings *ptr_struct, FILE* file);
/* wol */
void tools_wol_pack(const struct tools_wol *ptr_struct, u_int8_t* ptr_buff);
void tools_wol_unpack(struct tools_wol *ptr_struct, const u_int8_t* ptr_buff);
void tools_wol_print(const struct tools_wol *ptr_struct, FILE* file, int indent_level);
int tools_wol_size();
#define TOOLS_WOL_SIZE    (0x8)
void tools_wol_dump(const struct tools_wol *ptr_struct, FILE* file);

#ifdef __cplusplus
}
#endif

#endif // TOOLS_LAYOUTS_H
