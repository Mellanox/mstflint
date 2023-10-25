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

#include "resource_dump_error_handling.h"
#include <string>

namespace mft
{
namespace resource_dump
{
using namespace std;

ResourceDumpException::ResourceDumpException(Reason r, uint32_t m) : reason{r}, minor{m}
{
    switch (reason)
    {
        case Reason::OPEN_DEVICE_FAILED:
            message = "Failed openning device.";
            break;
        case Reason::TEXT_DATA_UNAVAILABLE:
            message = "Command is not in textual mode or data has not fetched.";
            break;
        case Reason::STREAMS_UNINITIALIZED:
            message = "Fetch data operation was executed, before initializing fetcher streams.";
            break;
        case Reason::OPEN_FILE_FAILED:
            message = "Failed to create the binary file in the provided path.";
            break;
        case Reason::DATA_NOT_FETCHED:
            message = "This operation can only be done, after fetching data.";
            break;
        case Reason::OPERATION_INVALID_BUFFER_MODE:
            message = "This operation is not eligible for dump to a buffer (only to a file).";
            break;
        case Reason::OS_NOT_SUPPORTED:
            message = "This operation is not supported for this OS.";
            break;
        case Reason::SEND_REG_ACCESS_FAILED:
            message = "Access register request to device failed. FW error code: " + to_string(minor);
            break;
        case Reason::WRONG_SEQUENCE_NUMBER:
            message = "Wrong sequence number received from device, or packet lost.";
            break;
        case Reason::REGISTER_DATA_SIZE_TOO_LONG:
            message = "RD/MORD size field is too long.";
            break;
        case Reason::SEGMENT_DATA_TOO_SHORT:
            message =
              "Segment data is shorter than segment size field, or segment header is too short, or reference segment is too short.";
            break;
        case Reason::DATA_OVERFLOW:
            message = "Illegal access to dumped data.";
            break;
        case Reason::BUFFER_TOO_SMALL:
            message = "Not enough memory was allocated to retrieve the dump.";
            break;
        case Reason::MKEY_FETCHER_GET_DEVICE_LIST_FAILED:
            message = "ibv_get_device_list failed.";
            break;
        case Reason::MKEY_FETCHER_MLX5DV_OPEN_FAILED:
            message = "mlx5dv_open_device failed.";
            break;
        case Reason::MKEY_FETCHER_RDMA_NAME_INVALID:
            message = "rdma_name provided is invalid or not found by driver.";
            break;
        case Reason::MKEY_FETCHER_ALLOC_PD_FAILED:
            message = "ibv_alloc_pd failed.";
            break;
        case Reason::MKEY_ALLIGNED_ALLOC_FAILED:
            message = "posix_memalign failed.";
            break;
        case Reason::MKEY_UMEM_REG_FAILED:
            message = "mlx5dv_devx_umem_reg failed.";
            break;
        case Reason::DEVX_OBJ_CREATE_FAILED:
            message = "mlx5dv_devx_obj_create failed.";
            break;
        default:
            message = "Unknown error has occured.";
            break;
    }
}

const char* ResourceDumpException::what() const noexcept
{
    return message.c_str();
}
} // namespace resource_dump
} // namespace mft
