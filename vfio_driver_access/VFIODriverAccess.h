/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */


#pragma once

#include <string>
#include <map>
#include <string>
#include <utility>
#include <unordered_map>
#include "VFIODriverAccessDefs.h"

class VFIODriverAccess
{
public:
    static void OpenVFIODevices(const std::string& dbdf, int& deviceFD, uint64_t& vsecOffset, uint64_t& addressRegionOffset);
    static void CloseVFIODevices(int deviceFD);
    static bool CheckifKernelLockdownIsEnabled();

private:
    static std::string getDeviceId(const std::string& dbdf);
    static void GetStartOffsets(int deviceFD, uint64_t& vsecOffset, uint64_t& addressRegionOffset);
    static bool isDeviceBoundToVfioPci(const std::string& dbdf);
    static void bindDeviceToVfioPciDriver(const std::string& dbdf);
    static void CreateJsonDevice(const std::string& dbdf);
    static std::string FindIOMMUGroupByDBDF(const std::string& dbdf);
    static void CleanupVFIODevice(const std::string& dbdf, const int iommuGroup);
    static int OpenVFIODevice();
    static int OpenVFIOGroup(const std::string& iommuGroup);
    static void CheckVFIOGroupViability(int groupID);
    static void AttachGroupToContainer(int groupID, int vfioID);
    static void EnableIOMMU(int vfioID);
    static int GetDeviceFD(int groupID, const std::string& dbdf);
};

class VFIODeviceRegistry
{
public:
    static VFIODeviceRegistry& GetInstance()
    {
        static VFIODeviceRegistry inst;

        return inst;
    }

    bool Contains(const std::string& dbdf) const
    {
        return deviceMap.count(dbdf) > 0;
    }

    VFIODeviceInfo GetDeviceInfo(const std::string& dbdf) const
    {
        return deviceMap.at(dbdf);
    }

    void InsertDeviceInfo(const std::string& dbdf, int fd, uint64_t vsecOffset, uint64_t addressRegionOffset)
    {
        deviceMap[dbdf] = {fd, vsecOffset, addressRegionOffset};
    }

private:
    VFIODeviceRegistry() = default;
    ~VFIODeviceRegistry() = default;

    std::unordered_map < std::string, VFIODeviceInfo > deviceMap;
};
