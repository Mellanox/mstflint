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

#ifndef RESOURCE_DUMP_ERROR_HANDLING_H
#define RESOURCE_DUMP_ERROR_HANDLING_H

#include <exception>
#include <cstdint>
#include <string>

namespace mft
{
namespace resource_dump
{
class ResourceDumpException : public std::exception
{
public:
    enum struct Reason
    {
        TEXT_DATA_UNAVAILABLE = 0x100,
        STREAMS_UNINITIALIZED,
        OPEN_FILE_FAILED,
        DATA_NOT_FETCHED,
        OPERATION_INVALID_BUFFER_MODE,
        OS_NOT_SUPPORTED,

        OPEN_DEVICE_FAILED = 0x200,
        SEND_REG_ACCESS_FAILED,
        WRONG_SEQUENCE_NUMBER,

        REGISTER_DATA_SIZE_TOO_LONG = 0x300,
        SEGMENT_DATA_TOO_SHORT,

        DATA_OVERFLOW = 0x400,
        BUFFER_TOO_SMALL,

        MKEY_FETCHER_GET_DEVICE_LIST_FAILED = 0x500,
        MKEY_FETCHER_MLX5DV_OPEN_FAILED,
        MKEY_FETCHER_RDMA_NAME_INVALID,
        MKEY_FETCHER_ALLOC_PD_FAILED,
        MKEY_ALLIGNED_ALLOC_FAILED,
        MKEY_UMEM_REG_FAILED,
        DEVX_OBJ_CREATE_FAILED,

        UNKNOWN = (uint16_t)-1
    };

    const Reason reason;
    const uint32_t minor;
    std::string message;
    ResourceDumpException(Reason r = Reason::UNKNOWN, uint32_t minor = 0);

    const char* what() const noexcept override;
};

} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_ERROR_HANDLING_H
