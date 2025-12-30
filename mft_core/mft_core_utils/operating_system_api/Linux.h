/*
 * Copyright (c) 2020-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
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
