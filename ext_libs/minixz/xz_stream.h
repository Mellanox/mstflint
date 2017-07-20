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
 *
 * Definitions for handling the .xz file format
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put into the public domain.
 * You can do whatever you want with this file.
 */

#ifndef XZ_STREAM_H
#define XZ_STREAM_H

#if defined(__KERNEL__) && !XZ_INTERNAL_CRC32
#	include <linux/crc32.h>
#	undef crc32
#	define xz_crc32(buf, size, crc) \
		(~crc32_le(~(uint32_t)(crc), buf, size))
#endif

/*
 * See the .xz file format specification at
 * http://tukaani.org/xz/xz-file-format.txt
 * to understand the container format.
 */

#define STREAM_HEADER_SIZE 12

#define HEADER_MAGIC "\3757zXZ"
#define HEADER_MAGIC_SIZE 6

#define FOOTER_MAGIC "YZ"
#define FOOTER_MAGIC_SIZE 2

/*
 * Variable-length integer can hold a 63-bit unsigned integer or a special
 * value indicating that the value is unknown.
 *
 * Experimental: vli_type can be defined to uint32_t to save a few bytes
 * in code size (no effect on speed). Doing so limits the uncompressed and
 * compressed size of the file to less than 256 MiB and may also weaken
 * error detection slightly.
 */
typedef uint64_t vli_type;

#define VLI_MAX ((vli_type)-1 / 2)
#define VLI_UNKNOWN ((vli_type)-1)

/* Maximum encoded size of a VLI */
#define VLI_BYTES_MAX (sizeof(vli_type) * 8 / 7)

/* Integrity Check types */
enum xz_check {
	XZ_CHECK_NONE = 0,
	XZ_CHECK_CRC32 = 1,
	XZ_CHECK_CRC64 = 4,
	XZ_CHECK_SHA256 = 10
};

/* Maximum possible Check ID */
#define XZ_CHECK_MAX 15

#endif
