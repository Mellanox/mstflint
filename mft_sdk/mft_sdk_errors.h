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

/** Size of the error message buffer in MstErrorInfo, including the terminator. */
#define MAX_ERROR_MESSAGE_LENGTH 256

    /**
     * @brief The status returned by every MFT SDK function.
     *
     * The numeric values are part of the API: an existing code keeps its value across SDK versions and
     * a new code takes the next free number, so a caller built against an older SDK keeps working
     * against a newer shared object.
     */
    typedef enum MstStatus
    {
        MST_SUCCESS = 0,                               /**< The operation completed successfully. */
        MST_ERROR_UNINITIALIZED = 1,                   /**< The device handle has no open device. */
        MST_ERROR_INVALID_ARGUMENT = 2,                /**< An argument was NULL, zero or out of range. */
        MST_ERROR_NOT_SUPPORTED = 3,                   /**< The device cannot do this. */
        MST_ERROR_NO_PERMISSION = 4,                   /**< The caller lacks the required privileges. */
        MST_ERROR_NO_AVAILABLE_DEVICES = 5,            /**< Discovery found no matching device. */
        MST_ERROR_DEVICE_NOT_FOUND = 6,                /**< The requested device does not exist. */
        MST_ERROR_INTERFACE_NOT_AVAILABLE = 7,         /**< The access interface is absent on this host. */
        MST_ERROR_MST_DRIVER_NOT_LOADED = 8,           /**< The mst_pci/mst_pciconf module is not loaded. */
        MST_ERROR_FAILED_TO_ALLOCATE_MEMORY = 9,       /**< The SDK could not allocate a buffer. */
        MST_ERROR_FAILED_TO_OPEN_DEVICE = 10,          /**< Opening the device failed. */
        MST_ERROR_FAILED_TO_SEND_ACCESS_REG = 11,      /**< An access register command failed. */
        MST_ERROR_FAILED_TO_GET_TELEMETRY = 12,        /**< A telemetry query failed. */
        MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES = 13, /**< An HCA capability query failed. */
        MST_ERROR_FAILED_TO_READ_CR_SPACE = 14,        /**< A CR space read failed. */
        MST_ERROR_FAILED_TO_WRITE_CR_SPACE = 15,       /**< A CR space write failed. */
        MST_ERROR_FAILED_TO_SET_I2C_SECONDARY = 16,    /**< Setting the I2C secondary address failed. */
        MST_ERROR_UNKNOWN = 17,                        /**< Catch-all; the codes below it are newer. */
        MST_ERROR_FAILED_TO_SEND_ICMD = 18,            /**< An ICMD failed; mstGetSyndrome has the
                                                            firmware syndrome. */
        MST_ERROR_TEMPERATURE_NOT_AVAILABLE = 19,      /**< No sensor produced a valid reading. */
    } MstStatus;

    /**
     * @brief A failure status paired with the message describing it.
     */
    typedef struct MstErrorInfo_t
    {
        MstStatus status;                            /**< The status of the failed operation. */
        char errorMessage[MAX_ERROR_MESSAGE_LENGTH]; /**< Human readable description of the failure. */
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