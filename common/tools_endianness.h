/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#pragma once

#include <stdint.h>

/*
 * The swaps are plain shift/mask arithmetic rather than a libc byte-swap header,
 * so the same source yields the same conversion on every toolchain and no target
 * has to ship <byteswap.h> or <sys/endian.h>. Functions rather than macros, so
 * the argument is evaluated exactly once and the result has a fixed width.
 */
static inline uint16_t mft_bswap16(uint16_t val)
{
    return (uint16_t)(((val & 0x00ffU) << 8) | ((val & 0xff00U) >> 8));
}

static inline uint32_t mft_bswap32(uint32_t val)
{
    return ((val & 0x000000ffUL) << 24) | ((val & 0x0000ff00UL) << 8) | ((val & 0x00ff0000UL) >> 8) |
           ((val & 0xff000000UL) >> 24);
}

static inline uint64_t mft_bswap64(uint64_t val)
{
    return ((uint64_t)mft_bswap32((uint32_t)(val & 0xffffffffULL)) << 32) |
           (uint64_t)mft_bswap32((uint32_t)(val >> 32));
}

#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
#define MFT_HOST_IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#else
#error "tools_endianness.h: cannot determine host byte order"
#endif

#if MFT_HOST_IS_BIG_ENDIAN

#define mft_be16_to_cpu(val) (val)
#define mft_be32_to_cpu(val) (val)
#define mft_be64_to_cpu(val) (val)
#define mft_cpu_to_be16(val) (val)
#define mft_cpu_to_be32(val) (val)
#define mft_cpu_to_be64(val) (val)
#define mft_le16_to_cpu(val) mft_bswap16(val)
#define mft_le32_to_cpu(val) mft_bswap32(val)
#define mft_le64_to_cpu(val) mft_bswap64(val)
#define mft_cpu_to_le16(val) mft_bswap16(val)
#define mft_cpu_to_le32(val) mft_bswap32(val)
#define mft_cpu_to_le64(val) mft_bswap64(val)

#else

#define mft_be16_to_cpu(val) mft_bswap16(val)
#define mft_be32_to_cpu(val) mft_bswap32(val)
#define mft_be64_to_cpu(val) mft_bswap64(val)
#define mft_cpu_to_be16(val) mft_bswap16(val)
#define mft_cpu_to_be32(val) mft_bswap32(val)
#define mft_cpu_to_be64(val) mft_bswap64(val)
#define mft_le16_to_cpu(val) (val)
#define mft_le32_to_cpu(val) (val)
#define mft_le64_to_cpu(val) (val)
#define mft_cpu_to_le16(val) (val)
#define mft_cpu_to_le32(val) (val)
#define mft_cpu_to_le64(val) (val)

#endif
