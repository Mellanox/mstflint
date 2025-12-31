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

#include "OperatingSystemAPI.h"

class Linux : public OperatingSystemAPI
{
public:
    Linux() = default;
    virtual ~Linux() = default;
    virtual int GetPID() override;
    virtual const std::string GetExecutableName() override;
    virtual const std::string GetExecutablePath();
    virtual const std::string GetExecutableDir() override;
    virtual const std::string GetLogDirectory() override;
    virtual const std::string GetFilePath(const std::string& oDirName, const std::string& oFileName) override;
    virtual void LittleToBig32(uint32_t& uLittleEndianBuffer, const int iLength) override;
    virtual void CreateDirectoryIfNotExist(const std::string& poNewDirectory) override;
    virtual void MilliSecondsSleep(int iMilliseconds) override;
    virtual void GetHostName(char* pcHostName) override;
    virtual void InputPassword(char* pcPass, unsigned int uMaxLen) override;
    virtual uint32_t get_page_size() override;
    virtual std::pair<int, std::string> execCommand(const std::string& cmd);
    class FactoryOperatingSystemAPI;
};
