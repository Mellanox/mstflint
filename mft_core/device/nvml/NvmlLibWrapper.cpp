/*
 * Copyright (c) 2023-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
