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
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Gets the current device temperature, equivalent to `mget_temp -d <device>`.
     * @param mstDevice mstDevice handle.
     * @param temperature Output parameter for the highest sensor reading, in whole degrees Celsius.
     * @return The status of the operation. MST_ERROR_TEMPERATURE_NOT_AVAILABLE if the
     *         device answered but no sensor produced a valid reading;
     *         MST_ERROR_NOT_SUPPORTED for a device in livefish mode or a GPU ASIC;
     *         MST_ERROR_INVALID_ARGUMENT if either argument is NULL;
     *         MST_ERROR_UNKNOWN if a sensor or GPU driver read failed - call
     *         mstGetLastErrorString for which read it was and why.
     */
    MstStatus mstGetDeviceTemperature(MstDevice mstDevice, int32_t* temperature);
#ifdef __cplusplus
}
#endif
