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

#include <dlfcn.h>
#include <nvml.h>
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "NvmlLibWrapper.h"

NvmlLibWrapper::NvmlLibWrapper(const string libPath) : _libPath(libPath)
{
    LoadDynamicLib();
    LoadDynamicFuncs();
    InitNvmlSDK();
}

NvmlLibWrapper::~NvmlLibWrapper()
{
    nvmlShutdown();
    m_poDynamicHandle->FreeDynamicLibrary();
}

void NvmlLibWrapper::InitNvmlSDK()
{
    nvmlReturn_t error = nvmlInit();

    if (error)
    {
        LOG_AND_THROW_MFT_ERROR("Error initializing NVML SDK: " + std::string(nvmlErrorString(error)));
    }
}

void NvmlLibWrapper::LoadDynamicLib()
{
    m_poDynamicHandle = FactoryDynamicLinking::GetInstance();
    if (m_poDynamicHandle->LoadDynamicLibrary(_libPath))
    {
        LOG_AND_THROW_MFT_ERROR("Failed to load libnvidia-ml.so from path: " + _libPath + ": " + std::string(dlerror()));
    }
}

void NvmlLibWrapper::LoadDynamicFuncs()
{
    try
    {
        nvmlInit = (f_nvmlInit_v2)m_poDynamicHandle->GetFunctionAddress("nvmlInit_v2");
        nvmlShutdown = (f_nvmlShutdown)m_poDynamicHandle->GetFunctionAddress("nvmlShutdown");
        nvmlDeviceGetCount = (f_nvmlDeviceGetCount_v2)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetCount_v2");
        nvmlDeviceGetHandleByIndex =
          (f_nvmlDeviceGetHandleByIndex_v2)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetHandleByIndex_v2");
        nvmlDeviceGetPciInfo =
          (f_nvmlDeviceGetPciInfo_v3)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetPciInfo_v3");
        nvmlErrorString = (f_nvmlErrorString)m_poDynamicHandle->GetFunctionAddress("nvmlErrorString");
        nvmlDeviceReadWritePRM =
          (f_nvmlDeviceReadWritePRM)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceReadWritePRM_v1");
        nvmlDeviceGetHandleByPciBusId =
          (f_nvmlDeviceGetHandleByPciBusId_v2)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetHandleByPciBusId_v2");
        nvmlDeviceGetTemperatureV =
          (f_nvmlDeviceGetTemperatureV)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetTemperatureV");
        nvmlDeviceGetMinorNumber =
          (f_nvmlDeviceGetMinorNumber)m_poDynamicHandle->GetFunctionAddress("nvmlDeviceGetMinorNumber");
    }
    catch (const std::exception& e)
    {
        LOG_AND_THROW_MFT_ERROR(e.what() + string("\nPlease make sure you are using an up to date version of NVML lib."))
    }
}
