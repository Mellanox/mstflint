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

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include "mft_sdk/mft_sdk_class.hpp"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"

using namespace mft_core;

MftSdk::MftSdk(const std::string& deviceIdentifier) : _deviceIdentifier(deviceIdentifier)
{
    clearError();
    _mf = mopen(_deviceIdentifier.c_str());
    if (!_mf)
    {
        std::string errorMessage = "Failed to open device " + _deviceIdentifier + ": " + strerror(errno);
        setInitError(MST_ERROR_FAILED_TO_OPEN_DEVICE, errorMessage.c_str());
        throw MftGeneralException(errorMessage);
    }
    _mfiles.push_back(_mf);
}

MftSdk::~MftSdk()
{
    if (_mf)
    {
        mclose(_mf);
    }
}

std::vector<std::string> MftSdk::split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
