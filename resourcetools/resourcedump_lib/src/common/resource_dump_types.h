/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
