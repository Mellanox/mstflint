/*
 * Copyright (c) 2023-2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#include <nvml.h>
#include "mft_core/mft_core_utils/load_shared_library/FactoryDynamicLinking.h"

using std::string;

typedef nvmlReturn_t (*f_nvmlDeviceGetCount_v2)(unsigned int*);
typedef nvmlReturn_t (*f_nvmlDeviceGetHandleByIndex_v2)(unsigned int, nvmlDevice_t*);
typedef nvmlReturn_t (*f_nvmlDeviceGetPciInfo_v3)(nvmlDevice_t, nvmlPciInfo_t*);
typedef const char* (*f_nvmlErrorString)(nvmlReturn_t);
typedef nvmlReturn_t (*f_nvmlInit_v2)(void);
typedef nvmlReturn_t (*f_nvmlShutdown)(void);
typedef nvmlReturn_t (*f_nvmlDeviceReadWritePRM)(nvmlDevice_t, nvmlPRMTLV_v1_t*);
typedef nvmlReturn_t (*f_nvmlDeviceGetHandleByPciBusId_v2)(const char* pciBusId, nvmlDevice_t* device);
typedef nvmlReturn_t (*f_nvmlDeviceGetTemperatureV)(nvmlDevice_t device, nvmlTemperature_t* temperature);
typedef nvmlReturn_t (*f_nvmlDeviceGetMinorNumber)(nvmlDevice_t device, unsigned int* minorNumber);

class NvmlLibWrapper
{
public:
    NvmlLibWrapper(const string libPath = "libnvidia-ml.so.1");
    ~NvmlLibWrapper();
    /* Dynamic functions */
    f_nvmlDeviceGetHandleByIndex_v2 nvmlDeviceGetHandleByIndex;
    f_nvmlDeviceGetPciInfo_v3 nvmlDeviceGetPciInfo;
    f_nvmlErrorString nvmlErrorString;
    f_nvmlInit_v2 nvmlInit;
    f_nvmlShutdown nvmlShutdown;
    f_nvmlDeviceReadWritePRM nvmlDeviceReadWritePRM;
    f_nvmlDeviceGetCount_v2 nvmlDeviceGetCount;
    f_nvmlDeviceGetHandleByPciBusId_v2 nvmlDeviceGetHandleByPciBusId;
    f_nvmlDeviceGetTemperatureV nvmlDeviceGetTemperatureV;
    f_nvmlDeviceGetMinorNumber nvmlDeviceGetMinorNumber;

private:
    void InitNvmlSDK();
    void LoadDynamicFuncs();
    void LoadDynamicLib();

    const string _libPath;
    std::unique_ptr<DynamicLinking> m_poDynamicHandle;
};
