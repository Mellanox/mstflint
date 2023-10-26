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
