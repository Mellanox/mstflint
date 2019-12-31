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

#ifndef __XZ_H__
#define __XZ_H__

#include <common/compatibility.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    XZ_ERR_UNKNOWN              = -1,
    XZ_ERR_MEM_EXCEEDED         = -2,
    XZ_ERR_INTERNAL_MEM         = -3,
    XZ_ERR_PRESET_NO_SUPP       = -4,
    XZ_ERR_INTEGRITY_NOT_SUPP   = -5,
    XZ_ERR_ENCODE_FAULT         = -6
};

int32_t   xz_compress(u_int32_t preset, u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz);
int32_t   xz_decompress(u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz);
int32_t   xz_compress_crc32(u_int32_t preset, u_int8_t* inbuf, u_int32_t insz, u_int8_t* outbuf, u_int32_t outsz);
int32_t   xz_decompress_crc32(u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz);
const char* xz_get_error(int32_t error);
#ifdef __cplusplus
}
#endif

#endif
