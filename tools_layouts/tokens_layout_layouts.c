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
#include "tokens_layout_layouts.h"

void tokens_layout_nbu_debug_token_tlv_header_pack(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                   u_int8_t                                             * ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tlv_length);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tlv_type);
}

void tokens_layout_nbu_debug_token_tlv_header_unpack(struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                     const u_int8_t                                 * ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->tlv_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 0;
    ptr_struct->tlv_type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tokens_layout_nbu_debug_token_tlv_header_print(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                    FILE                                                 * fd,
                                                    int                                                    indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== tokens_layout_nbu_debug_token_tlv_header ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "tlv_length           : " UH_FMT "\n", ptr_struct->tlv_length);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "tlv_type             : " UH_FMT "\n", ptr_struct->tlv_type);
}

unsigned int tokens_layout_nbu_debug_token_tlv_header_size(void)
{
    return TOKENS_LAYOUT_NBU_DEBUG_TOKEN_TLV_HEADER_SIZE;
}

void tokens_layout_nbu_debug_token_tlv_header_dump(const struct tokens_layout_nbu_debug_token_tlv_header* ptr_struct,
                                                   FILE                                                 * fd)
{
    tokens_layout_nbu_debug_token_tlv_header_print(ptr_struct, fd, 0);
}

void tokens_layout_uuid_pack(const struct tokens_layout_uuid* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int       i;

    for (i = 0; i < 16; ++i) {
        offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
    }
}

void tokens_layout_uuid_unpack(struct tokens_layout_uuid* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int       i;

    for (i = 0; i < 16; ++i) {
        offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
        ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
}

void tokens_layout_uuid_print(const struct tokens_layout_uuid* ptr_struct, FILE* fd, int indent_level)
{
    int i;

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== tokens_layout_uuid ========\n");

    for (i = 0; i < 16; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "data_%03d            : " UH_FMT "\n", i, ptr_struct->data[i]);
    }
}

unsigned int tokens_layout_uuid_size(void)
{
    return TOKENS_LAYOUT_UUID_SIZE;
}

void tokens_layout_uuid_dump(const struct tokens_layout_uuid* ptr_struct, FILE* fd)
{
    tokens_layout_uuid_print(ptr_struct, fd, 0);
}

void tokens_layout_get_measurment_index_50_pack(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                u_int8_t                                          * ptr_buff)
{
    u_int32_t offset;
    int       i;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->header_identifier);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->header_version);
    offset = 64;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->structure_size);
    for (i = 0; i < 5; ++i) {
        offset = adb2c_calc_array_field_address(96, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved_header[i]);
    }
    offset = 256;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->token_identifier_hdr), ptr_buff + offset / 8);
    offset = 288;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->token_identifier);
    offset = 320;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->device_type_hdr), ptr_buff + offset / 8);
    offset = 352;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_type);
    offset = 384;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->status_hdr), ptr_buff + offset / 8);
    offset = 416;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
    offset = 448;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->keypair_uuid_hdr), ptr_buff + offset / 8);
    offset = 480;
    tokens_layout_uuid_pack(&(ptr_struct->keypair_uuid), ptr_buff + offset / 8);
    offset = 608;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->ecid_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(640, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ecid[i]);
    }
    offset = 704;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->psid_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 4; ++i) {
        offset = adb2c_calc_array_field_address(736, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->psid[i]);
    }
    offset = 864;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->fw_version_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(896, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_version[i]);
    }
    offset = 960;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->nonce_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 8; ++i) {
        offset = adb2c_calc_array_field_address(992, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->nonce[i]);
    }
    offset = 1248;
    tokens_layout_nbu_debug_token_tlv_header_pack(&(ptr_struct->ratchet_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(1280, 32, i, 1344, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ratchet[i]);
    }
}

void tokens_layout_get_measurment_index_50_unpack(struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                  const u_int8_t                              * ptr_buff)
{
    u_int32_t offset;
    int       i;

    offset = 0;
    ptr_struct->header_identifier = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->header_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 64;
    ptr_struct->structure_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    for (i = 0; i < 5; ++i) {
        offset = adb2c_calc_array_field_address(96, 32, i, 1344, 1);
        ptr_struct->reserved_header[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 256;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->token_identifier_hdr), ptr_buff + offset / 8);
    offset = 288;
    ptr_struct->token_identifier = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 320;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->device_type_hdr), ptr_buff + offset / 8);
    offset = 352;
    ptr_struct->device_type = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 384;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->status_hdr), ptr_buff + offset / 8);
    offset = 416;
    ptr_struct->status = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 448;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->keypair_uuid_hdr), ptr_buff + offset / 8);
    offset = 480;
    tokens_layout_uuid_unpack(&(ptr_struct->keypair_uuid), ptr_buff + offset / 8);
    offset = 608;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->ecid_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(640, 32, i, 1344, 1);
        ptr_struct->ecid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 704;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->psid_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 4; ++i) {
        offset = adb2c_calc_array_field_address(736, 32, i, 1344, 1);
        ptr_struct->psid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 864;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->fw_version_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(896, 32, i, 1344, 1);
        ptr_struct->fw_version[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 960;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->nonce_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 8; ++i) {
        offset = adb2c_calc_array_field_address(992, 32, i, 1344, 1);
        ptr_struct->nonce[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 1248;
    tokens_layout_nbu_debug_token_tlv_header_unpack(&(ptr_struct->ratchet_hdr), ptr_buff + offset / 8);
    for (i = 0; i < 2; ++i) {
        offset = adb2c_calc_array_field_address(1280, 32, i, 1344, 1);
        ptr_struct->ratchet[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
}

void tokens_layout_get_measurment_index_50_print(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                 FILE                                              * fd,
                                                 int                                                 indent_level)
{
    int i;

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== tokens_layout_get_measurment_index_50 ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "header_identifier    : " U32H_FMT "\n", ptr_struct->header_identifier);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "header_version       : " U32H_FMT "\n", ptr_struct->header_version);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "structure_size       : " U32H_FMT "\n", ptr_struct->structure_size);
    for (i = 0; i < 5; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "reserved_header_%03d : " U32H_FMT "\n", i, ptr_struct->reserved_header[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "token_identifier_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->token_identifier_hdr), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "token_identifier     : " U32H_FMT "\n", ptr_struct->token_identifier);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "device_type_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->device_type_hdr), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "device_type          : " U32H_FMT "\n", ptr_struct->device_type);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "status_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->status_hdr), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "status               : " U32H_FMT "\n", ptr_struct->status);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "keypair_uuid_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->keypair_uuid_hdr), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "keypair_uuid:\n");
    tokens_layout_uuid_print(&(ptr_struct->keypair_uuid), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "ecid_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->ecid_hdr), fd, indent_level + 1);
    for (i = 0; i < 2; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "ecid_%03d            : " U32H_FMT "\n", i, ptr_struct->ecid[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "psid_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->psid_hdr), fd, indent_level + 1);
    for (i = 0; i < 4; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "psid_%03d            : " U32H_FMT "\n", i, ptr_struct->psid[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "fw_version_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->fw_version_hdr), fd, indent_level + 1);
    for (i = 0; i < 2; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "fw_version_%03d      : " U32H_FMT "\n", i, ptr_struct->fw_version[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "nonce_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->nonce_hdr), fd, indent_level + 1);
    for (i = 0; i < 8; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "nonce_%03d           : " U32H_FMT "\n", i, ptr_struct->nonce[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "ratchet_hdr:\n");
    tokens_layout_nbu_debug_token_tlv_header_print(&(ptr_struct->ratchet_hdr), fd, indent_level + 1);
    for (i = 0; i < 2; ++i) {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "ratchet_%03d         : " U32H_FMT "\n", i, ptr_struct->ratchet[i]);
    }
}

unsigned int tokens_layout_get_measurment_index_50_size(void)
{
    return TOKENS_LAYOUT_GET_MEASURMENT_INDEX_50_SIZE;
}

void tokens_layout_get_measurment_index_50_dump(const struct tokens_layout_get_measurment_index_50* ptr_struct,
                                                FILE                                              * fd)
{
    tokens_layout_get_measurment_index_50_print(ptr_struct, fd, 0);
}

void tokens_layout_tokens_layout_Nodes_pack(const union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                            u_int8_t                                     * ptr_buff)
{
    tokens_layout_get_measurment_index_50_pack(&(ptr_struct->get_measurment_index_50), ptr_buff);
}

void tokens_layout_tokens_layout_Nodes_unpack(union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                              const u_int8_t                         * ptr_buff)
{
    tokens_layout_get_measurment_index_50_unpack(&(ptr_struct->get_measurment_index_50), ptr_buff);
}

void tokens_layout_tokens_layout_Nodes_print(const union tokens_layout_tokens_layout_Nodes* ptr_struct,
                                             FILE                                         * fd,
                                             int                                            indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== tokens_layout_tokens_layout_Nodes ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "get_measurment_index_50:\n");
    tokens_layout_get_measurment_index_50_print(&(ptr_struct->get_measurment_index_50), fd, indent_level + 1);
}

unsigned int tokens_layout_tokens_layout_Nodes_size(void)
{
    return TOKENS_LAYOUT_TOKENS_LAYOUT_NODES_SIZE;
}

void tokens_layout_tokens_layout_Nodes_dump(const union tokens_layout_tokens_layout_Nodes* ptr_struct, FILE* fd)
{
    tokens_layout_tokens_layout_Nodes_print(ptr_struct, fd, 0);
}
