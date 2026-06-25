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

#include <mft_sdk/mft_sdk_types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_ERROR_MESSAGE_LENGTH 256

    typedef enum MstStatus
    {
        MST_SUCCESS,
        MST_ERROR_UNINITIALIZED,
        MST_ERROR_INVALID_ARGUMENT,
        MST_ERROR_NOT_SUPPORTED,
        MST_ERROR_NO_PERMISSION,
        MST_ERROR_NO_AVAILABLE_DEVICES,
        MST_ERROR_DEVICE_NOT_FOUND,
        MST_ERROR_INTERFACE_NOT_AVAILABLE,
        MST_ERROR_MST_DRIVER_NOT_LOADED,
        MST_ERROR_FAILED_TO_ALLOCATE_MEMORY,
        MST_ERROR_FAILED_TO_OPEN_DEVICE,
        MST_ERROR_FAILED_TO_SEND_ACCESS_REG,
        MST_ERROR_FAILED_TO_GET_TELEMETRY,
        MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES,
        MST_ERROR_FAILED_TO_READ_CR_SPACE,
        MST_ERROR_FAILED_TO_WRITE_CR_SPACE,
        MST_ERROR_FAILED_TO_SET_I2C_SECONDARY,
        MST_ERROR_UNKNOWN,
    } MstStatus;

    typedef struct MstErrorInfo_t
    {
        MstStatus status;
        char errorMessage[MAX_ERROR_MESSAGE_LENGTH];
    } MstErrorInfo;

    /**
     * @brief Gets the last error string for a given MstDevice.
     * @param mstDevice The MstDevice to get the last error string for.
     * @return The last error string.
     */
    const char* mstGetLastErrorString(MstDevice mstDevice);

    /**
     * @brief Gets an error in case of mstDevice initialization failed.
     * @return The initialization error string.
     */
    const char* mstGetInitErrorString(void);

    /**
     * @brief Gets the syndrome code for a given MstDevice.
     * @param mstDevice The MstDevice to get the syndrome code for.
     * @return The syndrome code.
     */
    uint32_t mstGetSyndrome(MstDevice mstDevice);

#ifdef __cplusplus
}
#endif