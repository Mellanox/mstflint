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
 ***    and modified to fit mtcr needs
 ***/

#ifndef PACKETS_LAYOUT_H
#define PACKETS_LAYOUT_H

#include <stdlib.h>
#include <stdio.h>
#include "compatibility.h"

/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */

struct reg_tlv {
    u_int16_t   reserved0;    /* bit_offset:0 */    /* element_size: 16 */
    u_int16_t   len;    /* bit_offset:16 */    /* element_size: 11 */
    u_int8_t    Type;    /* bit_offset:27 */    /* element_size: 5 */    /* TX - 0, RX - ignore */
};

/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */

struct OperationTlv {
    u_int8_t	reserved0;    /* bit_offset:0 */    /* element_size: 8 */
    u_int8_t	status;    /* bit_offset:8 */    /* element_size: 7 */
    u_int8_t	dr;    /* bit_offset:15 */    /* element_size: 1 */
    u_int16_t	len;    /* bit_offset:16 */    /* element_size: 11 */
    u_int8_t	Type;    /* bit_offset:27 */    /* element_size: 5 */    /* TX - 0, RX - ignore */
    u_int8_t	class;    /* bit_offset:32 */    /* element_size: 8 */
    u_int8_t	method;    /* bit_offset:40 */    /* element_size: 7 */
    u_int8_t	r;    /* bit_offset:47 */    /* element_size: 1 */
    u_int16_t	register_id;    /* bit_offset:48 */    /* element_size: 16 */
    u_int64_t	tid;    /* bit_offset:64 */    /* element_size: 64 */
};

/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */

u_int32_t reg_tlv_pack(struct reg_tlv *data_to_pack, u_int8_t *packed_buffer);
void reg_tlv_unpack(struct reg_tlv *unpacked_data, u_int8_t *buffer_to_unpack);
void reg_tlv_dump(struct reg_tlv *data_to_print, FILE *out_port);



/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */

u_int32_t OperationTlv_pack(struct OperationTlv *data_to_pack, u_int8_t *packed_buffer);
void OperationTlv_unpack(struct OperationTlv *unpacked_data, u_int8_t *buffer_to_unpack);
void OperationTlv_dump(struct OperationTlv *data_to_print, FILE *out_port);


#endif /* internal_packets_functions_H */
