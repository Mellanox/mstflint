/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 *  Version: $Id$
 *
 */

/***
 *** This file was generated at "2025-12-18 14:56:49"
 *** by:
 ***    > /auto/mswg/release/tools/a-me/a-me-1.2.11/a-me-1.2.11-16/adabe_plugins/adb2c/adb2pack.py --input
 * /user/tools_layouts/adb/tokens_layout/tokens_layout.adb --file-prefix tokens_layout --prefix tokens_layout_
 *--no-adb-utils -o /user/tools_layouts
 ***/
#ifndef TOKENS_LAYOUT_LAYOUTS_H
#define TOKENS_LAYOUT_LAYOUTS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "adb_to_c_utils.h"
/* Description -  TLV Header (Type + Length) */
/* Size in bytes - 4 */
struct tokens_layout_nbu_debug_token_tlv_header {
    /*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - TLV Length */
    /* 0x0.0 - 0x0.15 */
    /* access: RW */
    u_int16_t tlv_length;
    /* Description - TLV Type */
    /* 0x0.16 - 0x0.31 */
    /* access: RW */
    u_int16_t tlv_type;
};

/* Description -   */
/* Size in bytes - 16 */
struct tokens_layout_uuid {
    /*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0x0.24 - 0x10.23 */
    /* access: RW */
    u_int8_t data[16];
};

/* Description -  get_measurment_index_50 */
/* Size in bytes - 168 */
struct tokens_layout_get_measurment_index_50 {
    /*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - ID of fixed header, should be 'TLV1' */
    /* 0x0.0 - 0x0.31 */
    /* access: RW */
    u_int32_t header_identifier;
    /*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - Header format version (major.minor), set to 1 */
    /* 0x4.0 - 0x4.31 */
    /* access: RW */
    u_int32_t header_version;
    /*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description - Size of entire token structure in bytes */
    /* 0x8.0 - 0x8.31 */
    /* access: RW */
    u_int32_t structure_size;
    /*---------------- DWORD[3] (Offset 0xc) ----------------*/
    /* Description - Reserved, set to 0 */
    /* 0xc.0 - 0x1c.31 */
    /* access: RW */
    u_int32_t reserved_header[5];
    /*---------------- DWORD[8] (Offset 0x20) ----------------*/
    /* Description - TLV Header (Type 0x0008) */
    /* 0x20.0 - 0x20.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header token_identifier_hdr;
    /*---------------- DWORD[9] (Offset 0x24) ----------------*/
    /* Description - Token identifier, should be 'NBTR' */
    /* 0x24.0 - 0x24.31 */
    /* access: RW */
    u_int32_t token_identifier;
    /*---------------- DWORD[10] (Offset 0x28) ----------------*/
    /* Description - TLV Header (Type 0x0001) */
    /* 0x28.0 - 0x28.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header device_type_hdr;
    /*---------------- DWORD[11] (Offset 0x2c) ----------------*/
    /* Description - Device type: 0x3=NVSwitch, 0x4=CX7, 0x6=NIC, 0x7=SOC, 0x8=Arcus, 0x9=Eth switch */
    /* 0x2c.0 - 0x2c.31 */
    /* access: RW */
    u_int32_t device_type;
    /*---------------- DWORD[12] (Offset 0x30) ----------------*/
    /* Description - TLV Header (Type 0x000D) */
    /* 0x30.0 - 0x30.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header status_hdr;
    /*---------------- DWORD[13] (Offset 0x34) ----------------*/
    /* Description -  */
    /* 0x34.0 - 0x34.31 */
    /* access: RW */
    u_int32_t status;
    /*---------------- DWORD[14] (Offset 0x38) ----------------*/
    /* Description - TLV Header (Type 0x4400) */
    /* 0x38.0 - 0x38.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header keypair_uuid_hdr;
    /*---------------- DWORD[15] (Offset 0x3c) ----------------*/
    /* Description - UUID of key used for token signing and verification */
    /* 0x3c.0 - 0x48.31 */
    /* access: RW */
    struct tokens_layout_uuid keypair_uuid;
    /*---------------- DWORD[19] (Offset 0x4c) ----------------*/
    /* Description - TLV Header (Type 0x4401) */
    /* 0x4c.0 - 0x4c.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header ecid_hdr;
    /*---------------- DWORD[20] (Offset 0x50) ----------------*/
    /* Description -  */
    /* 0x50.0 - 0x54.31 */
    /* access: RW */
    u_int32_t ecid[2];
    /*---------------- DWORD[22] (Offset 0x58) ----------------*/
    /* Description - TLV Header (Type 0x4401) */
    /* 0x58.0 - 0x58.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header psid_hdr;
    /*---------------- DWORD[23] (Offset 0x5c) ----------------*/
    /* Description - Device PSID (16B) */
    /* 0x5c.0 - 0x68.31 */
    /* access: RW */
    u_int32_t psid[4];
    /*---------------- DWORD[27] (Offset 0x6c) ----------------*/
    /* Description - TLV Header (Type 0x0005) */
    /* 0x6c.0 - 0x6c.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header fw_version_hdr;
    /*---------------- DWORD[28] (Offset 0x70) ----------------*/
    /* Description - FW version: NIC/Arcus XX.XX.XXXX, Switch XX.XXXX.XXXX */
    /* 0x70.0 - 0x74.31 */
    /* access: RW */
    u_int32_t fw_version[2];
    /*---------------- DWORD[30] (Offset 0x78) ----------------*/
    /* Description - TLV Header (Type 0x4402) */
    /* 0x78.0 - 0x78.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header nonce_hdr;
    /*---------------- DWORD[31] (Offset 0x7c) ----------------*/
    /* Description -  */
    /* 0x7c.0 - 0x98.31 */
    /* access: RW */
    u_int32_t nonce[8];
    /*---------------- DWORD[39] (Offset 0x9c) ----------------*/
    /* Description - TLV Header (Type 0x0011) */
    /* 0x9c.0 - 0x9c.31 */
    /* access: RW */
    struct tokens_layout_nbu_debug_token_tlv_header ratchet_hdr;
    /*---------------- DWORD[40] (Offset 0xa0) ----------------*/
    /* Description - Token ratchet value to compare with fuse value */
    /* 0xa0.0 - 0xa4.31 */
    /* access: RW */
    u_int32_t ratchet[2];
};

/* Description -   */
/* Size in bytes - 168 */
union tokens_layout_tokens_layout_Nodes {
    /*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description -  */
    /* 0x0.0 - 0xa4.31 */
    /* access: RW */
    struct tokens_layout_get_measurment_index_50 get_measurment_index_50;
};

/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* nbu_debug_token_tlv_header */
void tokens_layout_nbu_debug_token_tlv_header_pack(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                   u_int8_t                                             * ptr_buff);
void tokens_layout_nbu_debug_token_tlv_header_unpack(struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                     const u_int8_t                                 * ptr_buff);
void tokens_layout_nbu_debug_token_tlv_header_print(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                    FILE                                                 * fd,
                                                    int                                                    indent_level);
unsigned int tokens_layout_nbu_debug_token_tlv_header_size(void);
#define TOKENS_LAYOUT_NBU_DEBUG_TOKEN_TLV_HEADER_SIZE (0x4)
void tokens_layout_nbu_debug_token_tlv_header_dump(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                   FILE                                                 * fd);
/* uuid */
void tokens_layout_uuid_pack(const struct tokens_layout_uuid* ptr_struct, u_int8_t* ptr_buff);
void tokens_layout_uuid_unpack(struct tokens_layout_uuid* ptr_struct, const u_int8_t* ptr_buff);
void tokens_layout_uuid_print(const struct tokens_layout_uuid* ptr_struct, FILE* fd, int indent_level);
unsigned int tokens_layout_uuid_size(void);
#define TOKENS_LAYOUT_UUID_SIZE (0x10)
void tokens_layout_uuid_dump(const struct tokens_layout_uuid* ptr_struct, FILE* fd);
/* get_measurment_index_50 */
void tokens_layout_get_measurment_index_50_pack(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                u_int8_t                                          * ptr_buff);
void tokens_layout_get_measurment_index_50_unpack(struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                  const u_int8_t                              * ptr_buff);
void tokens_layout_get_measurment_index_50_print(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                 FILE                                              * fd,
                                                 int                                                 indent_level);
unsigned int tokens_layout_get_measurment_index_50_size(void);
#define TOKENS_LAYOUT_GET_MEASURMENT_INDEX_50_SIZE (0xa8)
void tokens_layout_get_measurment_index_50_dump(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                FILE                                              * fd);
/* tokens_layout_Nodes */
void tokens_layout_tokens_layout_Nodes_pack(const union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                            u_int8_t                                     * ptr_buff);
void tokens_layout_tokens_layout_Nodes_unpack(union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                              const u_int8_t                         * ptr_buff);
void tokens_layout_tokens_layout_Nodes_print(const union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                             FILE                                         * fd,
                                             int                                            indent_level);
unsigned int tokens_layout_tokens_layout_Nodes_size(void);
#define TOKENS_LAYOUT_TOKENS_LAYOUT_NODES_SIZE (0xa8)
void tokens_layout_tokens_layout_Nodes_dump(const union tokens_layout_tokens_layout_Nodes* ptr_struct, FILE* fd);

#ifdef __cplusplus
}
#endif

#endif /* TOKENS_LAYOUT_LAYOUTS_H */
