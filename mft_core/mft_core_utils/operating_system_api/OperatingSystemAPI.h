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

#include <cstdint>
#include <string>

#include "OperatingSystemAPIDefs.h"

class OperatingSystemAPI
{
public:
    OperatingSystemAPI() = default;
    virtual ~OperatingSystemAPI() = default;

    // These pure virtual functions should be implemented
    // by the specific OS API.
    virtual int GetPID() = 0;
    virtual int SuppressStderr();
    virtual const std::string GetFilePath(const std::string& oDirName, const std::string& oFileName) = 0;
    virtual const std::string GetExecutableName() = 0;
    virtual const std::string GetExecutableDir() = 0;
    virtual const std::string GetLogDirectory() = 0;
    virtual void RestoreStderr(const int iFd);
    virtual void LittleToBig32(uint32_t& uLittleEndianBuffer, const int iLength) = 0;
    virtual void CreateDirectoryIfNotExist(const std::string& oNewDirectory) = 0;
    virtual void MilliSecondsSleep(int iMilliseconds) = 0;
    virtual void GetHostName(char* pcHostName) = 0;
    virtual void InputPassword(char* pcPass, unsigned int uMaxLen) = 0;
    virtual bool FileExists(const std::string& sFilePath);
    virtual uint32_t get_page_size() = 0;
    virtual std::pair<int, std::string> execCommand(const std::string& cmd) = 0;
};
