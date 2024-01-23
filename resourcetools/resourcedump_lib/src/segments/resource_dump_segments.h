/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#ifndef RESOURCE_DUMP_SEGMENT_H
#define RESOURCE_DUMP_SEGMENT_H

#include <common/compatibility.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#include "resource_dump_segments_be.h"
#else
#include "resource_dump_segments_le.h"
#endif

#ifdef __cplusplus
namespace mft
{
namespace resource_dump
{
#endif

#ifdef __cplusplus
constexpr
#else
inline
#endif
  uint32_t
  to_segment_data_size(uint16_t length_dw)
{
    return length_dw * 4 - (sizeof(resource_dump_segment_header_t) + sizeof(resource_segment_sub_header_t));
}

#ifdef __cplusplus
} // namespace resource_dump
} // namespace mft
#endif

#endif // RESOURCE_DUMP_SEGMENT_H
