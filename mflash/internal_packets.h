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
 ***/

#ifndef internal_packets_functions_H
#define internal_packets_functions_H

#include "internal_packets_types.h"
#include <stdlib.h>

/*************************************/
/* Name: mfbe
 * Size: 96 bits
 * Description: mfbe */

u_int32_t mfbe_pack(struct mfbe *data_to_pack, u_int8_t *packed_buffer);
void mfbe_unpack(struct mfbe *unpacked_data, u_int8_t *buffer_to_unpack);
void mfbe_dump(struct mfbe *data_to_print, FILE *out_port);


/*************************************/
/* Name: mfpa
 * Size: 256 bits
 * Description: mfpa */

u_int32_t mfpa_pack(struct mfpa *data_to_pack, u_int8_t *packed_buffer);
void mfpa_unpack(struct mfpa *unpacked_data, u_int8_t *buffer_to_unpack);
void mfpa_dump(struct mfpa *data_to_print, FILE *out_port);


/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */

u_int32_t reg_tlv_pack(struct reg_tlv *data_to_pack, u_int8_t *packed_buffer);
void reg_tlv_unpack(struct reg_tlv *unpacked_data, u_int8_t *buffer_to_unpack);
void reg_tlv_dump(struct reg_tlv *data_to_print, FILE *out_port);

/*************************************/
/* Name: mfba_mad
 * Size: 352 bits
 * Description: mfba_mad */

u_int32_t mfba_mad_pack(struct mfba_mad *data_to_pack, u_int8_t *packed_buffer);
void mfba_mad_unpack(struct mfba_mad *unpacked_data, u_int8_t *buffer_to_unpack);
void mfba_mad_dump(struct mfba_mad *data_to_print, FILE *out_port);


/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */

u_int32_t OperationTlv_pack(struct OperationTlv *data_to_pack, u_int8_t *packed_buffer);
void OperationTlv_unpack(struct OperationTlv *unpacked_data, u_int8_t *buffer_to_unpack);
void OperationTlv_dump(struct OperationTlv *data_to_print, FILE *out_port);


#endif /* internal_packets_functions_H */
