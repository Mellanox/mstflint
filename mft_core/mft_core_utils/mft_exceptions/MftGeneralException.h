/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "mft_core/mft_core_utils/logger/Logger.h"

namespace mft_core
{
class MftGeneralException : public std::exception
{
public:
    virtual const char* what() const throw();
    MftGeneralException(const std::string& oExceptionMessage, int iErrorCode = 0);
    virtual ~MftGeneralException() throw(){};
    int GetErrorCode() const throw();

private:
    std::string m_oExceptionMessage;
    int m_iErrorCode;
};

#define LOG_AND_THROW_MFT_ERROR(oMessage) \
    std::stringstream oBuffer;            \
    oBuffer << oMessage << std::endl;     \
    LOG.Error(oBuffer.str());             \
    throw mft_core::MftGeneralException(oBuffer.str());

}; // namespace mft_core
