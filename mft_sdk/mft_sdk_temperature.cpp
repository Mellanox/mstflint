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

#include "mft_sdk/mft_sdk_temperature.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "small_utils/mget_temp_lib.h"

#include <string>

namespace
{
// mget_temp's return codes carry the whole device-path decision (GPU driver, livefish,
// GPU ASIC, failed sensor read); the SDK only has to name each one.
MstStatus translateReadError(int rc)
{
    switch (rc)
    {
        case MGET_TEMP_ERR_LIVEFISH:
        case MGET_TEMP_ERR_GPU_ASIC:
            return MST_ERROR_NOT_SUPPORTED;
        default:
            return MST_ERROR_UNKNOWN;
    }
}

std::string readErrorMessage(int rc, const char* readError)
{
    switch (rc)
    {
        case MGET_TEMP_ERR_LIVEFISH:
            return "Temperature is not available in livefish mode";
        case MGET_TEMP_ERR_GPU_ASIC:
            return "Temperature is not supported over a GPU device";
        case MGET_TEMP_ERR_GPU_READ:
            return "Failed to read the GPU driver temperature";
        case MGET_TEMP_ERR_DIODE_READ:
            return std::string("Failed to read the thermal diodes: ") + readError;
        case MGET_TEMP_ERR_MODULE_READ:
            return std::string("Failed to read the module sensors: ") + readError;
        default:
            return "Failed to read the temperature";
    }
}
} // namespace

MstStatus MftSdk::getDeviceTemperature(int32_t* temperature)
{
    if (!_mf || !temperature)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }

    int maxTemperature = MGET_TEMP_INVALID_TEMP;
    // The reader copies the thermal library's message here as it fails; fetching it
    // afterwards would race with any other thread that failed in the meantime.
    char readError[MGET_TEMP_MAX_ERR_LEN] = {0};
    int rc = mget_temp_read_max_temperature(_mf, /*no_modules=*/false, &maxTemperature, readError, sizeof(readError));
    if (rc != MGET_TEMP_OK)
    {
        setLastError(translateReadError(rc), readErrorMessage(rc, readError) + " for device " + _deviceIdentifier);
        return _lastError.status;
    }

    // The device answered but every sensor is inactive or unreadable - distinct from a
    // failed read, and what mget_temp reports as "No valid temperature were measured".
    if (maxTemperature <= MGET_TEMP_INVALID_TEMP)
    {
        setLastError(
          MST_ERROR_TEMPERATURE_NOT_AVAILABLE,
          "No valid temperature was measured on device " + _deviceIdentifier + "; please check device configuration");
        return _lastError.status;
    }

    *temperature = maxTemperature;
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstGetDeviceTemperature(MstDevice mstDevice, int32_t* temperature)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getDeviceTemperature(temperature);
    }

} // extern "C"
