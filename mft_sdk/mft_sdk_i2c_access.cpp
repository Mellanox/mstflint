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

#include "mft_sdk/mft_sdk_i2c_access.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mtcr.h"

#ifdef ENABLE_MST_DEV_I2C

MstStatus MftSdk::setI2cSecondary(uint8_t newI2cSecondaryAddress)
{
    if (_mfiles.empty())
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    // mset_i2c_secondary returns the previous value, 0xff on null mf
    for (auto mf : _mfiles)
    {
        unsigned char rc = mset_i2c_secondary(mf, newI2cSecondaryAddress);
        if (rc == 0xff)
        {
            std::string errorMessage = "Failed to set I2C secondary address for device " + _deviceIdentifier;
            setLastError(MST_ERROR_FAILED_TO_SET_I2C_SECONDARY, errorMessage);
            return _lastError.status;
        }
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getI2cSecondary(uint8_t* i2cSecondaryAddress)
{
    if (!_mf || !i2cSecondaryAddress)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    *i2cSecondaryAddress = mget_i2c_secondary(_mf);
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstSetI2cSecondary(MstDevice mstDevice, uint8_t newI2cSecondaryAddress)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->setI2cSecondary(newI2cSecondaryAddress);
    }

    MstStatus mstGetI2cSecondary(MstDevice mstDevice, uint8_t* i2cSecondaryAddress)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getI2cSecondary(i2cSecondaryAddress);
    }

} // extern "C"

#endif /* ENABLE_MST_DEV_I2C */
