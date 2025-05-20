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

class VFIODriverAccess
{
public:
    static void OpenVFIODevices(const std::string& dbdf, int& deviceFD);
    static void CloseVFIODevices(int deviceFD);
    static void GetVSECStartOffset(int deviceFD, uint64_t& vsecOffset);
    static bool CheckifKernelLockdownIsEnabled();

private:
    static void bindDeviceToVfioPciDriver(const std::string& hwDevId);
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