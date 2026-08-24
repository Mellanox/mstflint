/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#pragma once
#include <stdint.h>
#include <string.h>

#define MASK_SIZE 64
typedef struct mstQueryHeader_t
{
    unsigned int size;
    uint64_t valid_fields_mask;
    uint64_t extended_valid_fields_mask;
} mstQueryHeader;
#define MST_QUERY_HDR(a) ((mstQueryHeader*)(a))
#define MST_QUERY_HAS(a, BIT)                                                      \
    ((BIT) < MASK_SIZE ? (MST_QUERY_HDR(a)->valid_fields_mask & (1ULL << (BIT))) : \
                         (MST_QUERY_HDR(a)->extended_valid_fields_mask & (1ULL << ((BIT)-MASK_SIZE))))
#define MST_QUERY_INIT(a)                      \
    do                                         \
    {                                          \
        memset((a), 0, sizeof(*(a)));          \
        MST_QUERY_HDR(a)->size = sizeof(*(a)); \
    } while (0)

#define MST_QUERY_CLEAR(a)                                                                 \
    do                                                                                     \
    {                                                                                      \
        unsigned int _qsz = MST_QUERY_HDR(a)->size;                                        \
        memset((char*)(a) + sizeof(unsigned int), 0, sizeof(*(a)) - sizeof(unsigned int)); \
        MST_QUERY_HDR(a)->size = _qsz;                                                     \
    } while (0)
