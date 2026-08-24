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

#include "mft_sdk/mft_sdk_errors.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include <cstdarg>
#include <cstdio>

static thread_local MstErrorInfo g_initError;

const char* MftSdk::getLastError() const
{
    return _lastError.errorMessage;
}

void MftSdk::setInitError(MstStatus status, const std::string& errorMessage)
{
    g_initError.status = status;
    strncpy(g_initError.errorMessage, errorMessage.c_str(), sizeof(g_initError.errorMessage));
    g_initError.errorMessage[sizeof(g_initError.errorMessage) - 1] = '\0';
}

void MftSdk::setLastError(MstStatus status, const std::string& errorMessage)
{
    _lastError.status = status;
    strncpy(_lastError.errorMessage, errorMessage.c_str(), sizeof(_lastError.errorMessage));
    _lastError.errorMessage[sizeof(_lastError.errorMessage) - 1] = '\0';
}

void MftSdk::clearError()
{
    _lastError.status = MST_SUCCESS;
    _lastError.errorMessage[0] = '\0';
    _syndromeCode = 0;
}

uint32_t MftSdk::getSyndromeCode() const
{
    return _syndromeCode;
}

// Pure C API Functions:
extern "C"
{
    const char* mstGetLastErrorString(MstDevice mstDevice)
    {
        if (!mstDevice)
        {
            return "MST Device was not initialized";
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getLastError();
    }

    const char* mstGetInitErrorString(void)
    {
        return g_initError.errorMessage;
    }

    uint32_t mstGetSyndrome(MstDevice mstDevice)
    {
        if (!mstDevice)
        {
            return 0;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getSyndromeCode();
    }
}
