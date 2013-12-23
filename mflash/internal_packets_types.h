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

#ifndef internal_packets_structs_H
#define internal_packets_structs_H

#include <stdlib.h>
#include <sys/types.h>

/*************************************/
/* Name: mfbe
 * Size: 96 bits
 * Description: mfbe */

struct mfbe {
    u_int8_t    reserved0;    /* bit_offset:0 */    /* element_size: 4 */
    u_int8_t    fs;    /* bit_offset:4 */    /* element_size: 2 */    /* Flash Select */
    u_int8_t    reserved1;    /* bit_offset:6 */    /* element_size: 2 */
    u_int8_t    p;    /* bit_offset:8 */    /* element_size: 1 */    /* Parallel */
    u_int32_t   reserved2;    /* bit_offset:9 */    /* element_size: 23 */
    u_int32_t   reserved3;    /* bit_offset:32 */    /* element_size: 32 */
    u_int32_t   address;    /* bit_offset:64 */    /* element_size: 24 */    /* address in bytes */
    u_int8_t    reserved4;    /* bit_offset:88 */    /* element_size: 8 */
};


/*************************************/
/* Name: mfba
 * Size: 2144 bits
 * Description: mfba */

struct mfba {
    u_int8_t    reserved0;    /* bit_offset:0 */    /* element_size: 4 */
    u_int8_t    fs;    /* bit_offset:4 */    /* element_size: 2 */    /* Flash Select */
    u_int8_t    reserved1;    /* bit_offset:6 */    /* element_size: 2 */
    u_int8_t    p;    /* bit_offset:8 */    /* element_size: 1 */    /* Parallel */
    u_int32_t   reserved2;    /* bit_offset:9 */    /* element_size: 23 */
    u_int16_t   size;    /* bit_offset:32 */    /* element_size: 9 */    /* Transaction size */
    u_int32_t   reserved3;    /* bit_offset:41 */    /* element_size: 23 */
    u_int32_t   address;    /* bit_offset:64 */    /* element_size: 24 */    /* address in bytes */
    u_int8_t    reserved4;    /* bit_offset:88 */    /* element_size: 8 */
    u_int32_t   data[64];    /* bit_offset:96 */    /* element_size: 32 */    /* data */
};


/*************************************/
/* Name: mfpa
 * Size: 288 bits
 * Description: mfpa */

struct mfpa {
    u_int8_t    reserved0;    /* bit_offset:0 */    /* element_size: 4 */
    u_int8_t    fs;    /* bit_offset:4 */    /* element_size: 2 */    /* Flash Select */
    u_int8_t    reserved1;    /* bit_offset:6 */    /* element_size: 2 */
    u_int8_t    p;    /* bit_offset:8 */    /* element_size: 1 */    /* Parallel */
    u_int32_t   reserved2;    /* bit_offset:9 */    /* element_size: 23 */
    u_int32_t   boot_address;    /* bit_offset:32 */    /* element_size: 24 */    /* address in bytes */
    u_int8_t    reserved3;    /* bit_offset:56 */    /* element_size: 8 */
    u_int32_t   reserved4;    /* bit_offset:64 */    /* element_size: 64 */
    u_int8_t    flash_num;    /* bit_offset:128 */    /* element_size: 4 */    /* number of flash devices connected */
    u_int32_t   reserved5;    /* bit_offset:132 */    /* element_size: 28 */
    u_int32_t   jedec_id;    /* bit_offset:160 */    /* element_size: 24 */    /* Flash JEDEC ID */
    u_int8_t    reserved6;    /* bit_offset:184 */    /* element_size: 8 */
    u_int16_t   sector_size;    /* bit_offset:192 */    /* element_size: 10 */    /* Flash sectore size */
    u_int8_t    reserved7;    /* bit_offset:202 */    /* element_size: 6 */
    u_int8_t    block_allighment;    /* bit_offset:208 */    /* element_size: 8 */
    u_int8_t    reserved8;    /* bit_offset:216 */    /* element_size: 8 */
    u_int32_t   capability_mask;    /* bit_offset:224 */    /* element_size: 32 */    /* capability mask ;bit 0:Parallel flash Support;else:Reserved */
    u_int32_t   reserved9;    /* bit_offset:256 */    /* element_size: 32 */
};



/*************************************/
/* Name: REG_Mfpa
 * Size: 384 bits
 * Description:  */

struct REG_Mfpa {
    u_int16_t	reserved0;    /* bit_offset:0 */    /* element_size: 16 */
    u_int16_t	len;    /* bit_offset:16 */    /* element_size: 11 */
    u_int8_t	type;    /* bit_offset:27 */    /* element_size: 5 */
    u_int8_t	reserved1;    /* bit_offset:32 */    /* element_size: 4 */
    u_int8_t	fs;    /* bit_offset:36 */    /* element_size: 2 */    /* Flash Select */
    u_int8_t	reserved2;    /* bit_offset:38 */    /* element_size: 2 */
    u_int8_t	p;    /* bit_offset:40 */    /* element_size: 1 */    /* parallel - Index */
    u_int32_t	reserved3;    /* bit_offset:41 */    /* element_size: 23 */
    u_int32_t	boot_address;    /* bit_offset:64 */    /* element_size: 24 */    /* Boot address points to the FW image in the flash - R/W */
    u_int8_t	reserved4;    /* bit_offset:88 */    /* element_size: 8 */
    u_int32_t	reserved5;    /* bit_offset:96 */    /* element_size: 64 */
    u_int8_t	flash_num;    /* bit_offset:160 */    /* element_size: 4 */    /* Number of Flash Devices connected */
    u_int32_t	reserved6;    /* bit_offset:164 */    /* element_size: 28 */
    u_int32_t	jedec_id;    /* bit_offset:192 */    /* element_size: 24 */    /* Flash JEDEC ID */
    u_int8_t	reserved7;    /* bit_offset:216 */    /* element_size: 8 */
    u_int16_t	sector_size;    /* bit_offset:224 */    /* element_size: 10 */    /* Flash Sector Size */
    u_int8_t	reserved8;    /* bit_offset:234 */    /* element_size: 6 */
    u_int8_t	block_allignment;    /* bit_offset:240 */    /* element_size: 8 */    /* Required allignment for block access */
    u_int8_t	reserved9;    /* bit_offset:248 */    /* element_size: 8 */
    u_int32_t	capcability_mask;    /* bit_offset:256 */    /* element_size: 32 */
    u_int32_t	reserved10;    /* bit_offset:288 */    /* element_size: 96 */
};

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
/* Name: mfba_mad
 * Size: 352 bits
 * Description: mfba_mad */

struct mfba_mad {
    u_int8_t    reserved0;    /* bit_offset:0 */    /* element_size: 4 */
    u_int8_t    fs;    /* bit_offset:4 */    /* element_size: 2 */    /* Flash Select */
    u_int8_t    reserved1;    /* bit_offset:6 */    /* element_size: 2 */
    u_int8_t    p;    /* bit_offset:8 */    /* element_size: 1 */    /* Parallel */
    u_int32_t   reserved2;    /* bit_offset:9 */    /* element_size: 23 */
    u_int16_t   size;    /* bit_offset:32 */    /* element_size: 9 */    /* Transaction size */
    u_int32_t   reserved3;    /* bit_offset:41 */    /* element_size: 23 */
    u_int32_t   address;    /* bit_offset:64 */    /* element_size: 24 */    /* address in bytes */
    u_int8_t    reserved4;    /* bit_offset:88 */    /* element_size: 8 */
    u_int32_t   data[64];    /* bit_offset:96 */    /* element_size: 32 */    /* data */
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
/* Name: SMP_RegAccessMfpa
 * Size: 512 bits
 * Description:  */

struct SMP_RegAccessMfpa {
    struct OperationTlv	OperationTlv;    /* bit_offset:0 */    /* element_size: 128 */
    struct REG_Mfpa	REG_Mfpa;    /* bit_offset:128 */    /* element_size: 384 */
};

#endif /* internal_packets_structs_H */
