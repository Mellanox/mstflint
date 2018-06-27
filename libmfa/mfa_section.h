/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
 */
#ifndef _MFA_SECTION_H_
#define _MFA_SECTION_H_

#include <compatibility.h>
#include "xz_io_ops.h"


enum {
    MFA_SEC_OK = 0,
    MFA_SEC_ERR_GENERIC = 1,
    MFA_SEC_ERR_MEM_ALLOC,
    MFA_SEC_ERR_TAR_OPEN,
    MFA_SEC_ERR_DECODER_INIT,
    MFA_SEC_ERR_READ_BUF,
    MFA_SEC_ERR_FILE_NOT_FOUND,
    MFA_SEC_ERR_EXTRACT_FILE
};


enum mfa_section_types {
    MFA_MAP_SECTION =  1,
    MFA_TOC_SECTION =  2,
    MFA_DATA_SECTION = 3,
    MFA_NUM_SECTIONS
};


enum image_types {
    IT_FW_IMAGE = 1,
    IT_N_IMAGE_TYPES
};


enum subimage_types {
    SIT_PADDING = 0,
    SIT_FW = 1,

    SIT_CLP = 0x101,
    SIT_PXE = 0x110,
    SIT_UEFI = 0x111,
    SIT_FCODE = 0x121
};


enum section_flags {
    SFLAG_XZ_COMPRESSED = 1
};


typedef struct section_hdr {
    u_int8_t type;
    u_int8_t reserved[2];
    u_int8_t flags;
    u_int32_t size;
} section_hdr;


typedef struct map_entry_hdr {
    char board_type_id[32];
    u_int8_t nimages;
    u_int8_t reserved;
    u_int16_t metadata_size;
} map_entry_hdr;
// This struct is followed by the metadata unless metadata_size is zero


typedef struct map_image_entry {
    u_int32_t toc_offset;
    u_int16_t image_type;
    u_int8_t reserved;
    u_int8_t group_id;
    char select_tag[32];
} map_image_entry;


typedef struct toc_entry {
    u_int32_t data_offset;
    u_int32_t data_size;
    u_int16_t subimage_type;
    u_int8_t reserved0;
    u_int8_t num_ver_fields;
    u_int16_t version[4];
    u_int16_t reserved1;
    u_int16_t metadata_size;
} toc_entry;


enum metadata_type {
    MDT_RAW = 0,
    MDT_KEY_VALUE_PAIR = 1
};

//MDT_KEY_VALUE_PAIR => modifier is number of pairs
typedef struct metadata_hdr {
    u_int8_t type;
    u_int8_t reserved;
    u_int16_t modifier;
} metadata_hdr;


void      mfasec_init();
u_int32_t mfasec_crc32(const u_int8_t *buf, size_t size, u_int32_t crc);
ssize_t   mfasec_get_map(u_int8_t *inbuf, size_t inbufsz, u_int8_t **outbuf);
ssize_t   mfasec_get_toc(u_int8_t *inbuf, size_t inbufsz, u_int8_t **outbuf);
int       mfasec_get_data_chunk(u_int8_t *data_sec_ptr, size_t data_sec_len, size_t chunk_offset, size_t length, u_int8_t *outbuf);
char*     mfasec_get_sub_image_type_str(int t);
#endif

