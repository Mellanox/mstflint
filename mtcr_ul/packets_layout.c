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
 *** This file was generated at "Mon May 30 15:06:41 2011"
 *** by:
 ***    % csp_pack_unpack.pm ../xml_files/packets_st.csp
 ***    and modified to fit the needs of mtcr
 ***/

#include <stdlib.h>
#include "packets_layout.h"
#include "packets_common.h"

/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */


u_int32_t OperationTlv_pack(struct OperationTlv *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 24, 8, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 17, 7, data_to_pack->status);
    push_to_buff(packed_buffer, 16, 1, data_to_pack->dr);
    push_to_buff(packed_buffer, 5, 11, data_to_pack->len);
    push_to_buff(packed_buffer, 0, 5, data_to_pack->Type);
    push_to_buff(packed_buffer, 56, 8, data_to_pack->class);
    push_to_buff(packed_buffer, 49, 7, data_to_pack->method);
    push_to_buff(packed_buffer, 48, 1, data_to_pack->r);
    push_to_buff(packed_buffer, 32, 16, data_to_pack->register_id);
    push_to_buff_64(packed_buffer, 64, data_to_pack->tid);
    return 16;
}

void OperationTlv_unpack(struct OperationTlv *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 24, 8);
    unpacked_data->status = pop_from_buff(buffer_to_unpack, 17, 7);
    unpacked_data->dr = pop_from_buff(buffer_to_unpack, 16, 1);
    unpacked_data->len = pop_from_buff(buffer_to_unpack, 5, 11);
    unpacked_data->Type = pop_from_buff(buffer_to_unpack, 0, 5);
    unpacked_data->class = pop_from_buff(buffer_to_unpack, 56, 8);
    unpacked_data->method = pop_from_buff(buffer_to_unpack, 49, 7);
    unpacked_data->r = pop_from_buff(buffer_to_unpack, 48, 1);
    unpacked_data->register_id = pop_from_buff(buffer_to_unpack, 32, 16);
    unpacked_data->tid = pop_from_buff_64(buffer_to_unpack, 64);
}

void OperationTlv_dump(struct OperationTlv *data_to_print, FILE *out_port) {
    fprintf(out_port, "OperationTlv::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "OperationTlv::status: "U32D_FMT"\n", data_to_print->status);
    fprintf(out_port, "OperationTlv::dr: "U32D_FMT"\n", data_to_print->dr);
    fprintf(out_port, "OperationTlv::len: "U32D_FMT"\n", data_to_print->len);
    fprintf(out_port, "OperationTlv::Type: "U32D_FMT"\n", data_to_print->Type);
    fprintf(out_port, "OperationTlv::class: "U32D_FMT"\n", data_to_print->class);
    fprintf(out_port, "OperationTlv::method: "U32D_FMT"\n", data_to_print->method);
    fprintf(out_port, "OperationTlv::r: "U32D_FMT"\n", data_to_print->r);
    fprintf(out_port, "OperationTlv::register_id: "U32D_FMT"\n", data_to_print->register_id);
    fprintf(out_port, "OperationTlv::tid: "U64D_FMT"\n", data_to_print->tid);
}

/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */


u_int32_t reg_tlv_pack(struct reg_tlv *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 16, 16, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 5, 11, data_to_pack->len);
    push_to_buff(packed_buffer, 0, 5, data_to_pack->Type);
    return 4;
}

void reg_tlv_unpack(struct reg_tlv *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 16, 16);
    unpacked_data->len = pop_from_buff(buffer_to_unpack, 5, 11);
    unpacked_data->Type = pop_from_buff(buffer_to_unpack, 0, 5);
}

void reg_tlv_dump(struct reg_tlv *data_to_print, FILE *out_port) {
    fprintf(out_port, "reg_tlv::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "reg_tlv::len: "U32D_FMT"\n", data_to_print->len);
    fprintf(out_port, "reg_tlv::Type: "U32D_FMT"\n", data_to_print->Type);
}
