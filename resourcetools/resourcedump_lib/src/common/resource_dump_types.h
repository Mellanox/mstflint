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

#ifndef RESDUMP_TYPES_H
#define RESDUMP_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
namespace mft
{
namespace resource_dump
{
#endif

enum arg_require_t
{
    NA = 0,
    OPT,
    REQUIRED
};

enum arg_attr_t
{
    ANA = 0,
    ALL,
    ACTIVE
};

#ifdef __cplusplus
constexpr const char* AUTO_RDMA_NAME = "__AUTO__";
constexpr uint8_t NUM_INLINE_DATA_DWORDS = 52;
constexpr uint16_t DEFAULT_VHCA = (uint16_t)-1;
#else
#define AUTO_RDMA_NAME "__AUTO__"
#define NUM_INLINE_DATA_DWORDS 52
#define DEFAULT_VHCA ((uint16_t)-1)
#endif

typedef struct device_attributes
{
    const char* device_name; // MST or PCI format
    uint16_t vhca;
    const char* rdma_name; // RDMA for mkey. If given the resource will be dumped im memory mode.
} device_attributes_t;

typedef struct dump_request
{
    uint16_t resource_id;
    uint32_t index1;
    uint32_t index2;
    uint16_t num_of_obj1;
    uint16_t num_of_obj2;
} dump_request_t;

typedef enum endianess_t_
#ifdef __cplusplus
    : uint8_t
#endif
{
    NATIVE = 0,
    RD_BIG_ENDIAN,
    RD_LITTLE_ENDIAN
} endianess_t;

#ifdef __cplusplus
} // namespace resource_dump
} // namespace mft
#endif

#endif // RESDUMP_TYPES_H
