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

#include "mft_sdk/mft_sdk.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mtcr.h"

MstStatus MftSdk::readCRSpace(uint32_t address, uint32_t* data, int byteLength)
{
    if (!_mf || !data)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    int rc = mread4_block(_mf, address, data, byteLength);
    if (rc != byteLength)
    {
        std::string errorMessage = "Failed to read CR space";
        setLastError(MST_ERROR_FAILED_TO_READ_CR_SPACE, errorMessage);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::writeCRSpace(uint32_t address, uint32_t* data, int byteLength)
{
    if (!_mf || !data)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    int rc = mwrite4_block(_mf, address, data, byteLength);
    if (rc != byteLength)
    {
        std::string errorMessage = "Failed to write CR space";
        setLastError(MST_ERROR_FAILED_TO_WRITE_CR_SPACE, errorMessage);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstReadCRSpace(MstDevice mstDevice, uint32_t address, uint32_t* data, int byteLength)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->readCRSpace(address, data, byteLength);
    }

    MstStatus mstWriteCRSpace(MstDevice mstDevice, uint32_t address, uint32_t* data, int byteLength)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->writeCRSpace(address, data, byteLength);
    }
} // extern "C"