/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
    static void OpenVFIODevices(const std::string& dbdf, int& deviceFD, uint64_t& vsecOffset);
    static void CloseVFIODevices(int deviceFD);
    static bool CheckifKernelLockdownIsEnabled();

private:
    static void GetVSECStartOffset(int deviceFD, uint64_t& vsecOffset);
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

    void InsertDeviceInfo(const std::string& dbdf, int fd, uint64_t vsecOffset)
    {
        deviceMap[dbdf] = {fd, vsecOffset};
    }

private:
    VFIODeviceRegistry() = default;
    ~VFIODeviceRegistry() = default;

    std::unordered_map < std::string, VFIODeviceInfo > deviceMap;
};
