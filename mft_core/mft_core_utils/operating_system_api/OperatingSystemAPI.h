/*
 * Copyright (c) 2020-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
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
