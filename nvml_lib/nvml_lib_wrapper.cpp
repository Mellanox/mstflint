/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <dlfcn.h>
#include <nvml.h>

#include "nvml_exception.h"
#include "nvml_lib_wrapper.h"


NvmlLibWrapper::NvmlLibWrapper(const string libPath) : _libPath(libPath)
{
    LoadDynamicLib();
    LoadDynamicFuncs();
    InitNvmlSDK();
}

NvmlLibWrapper::~NvmlLibWrapper()
{
    nvmlShutdown();
    FreeDynamicLib();
}


void NvmlLibWrapper::InitNvmlSDK()
{
    nvmlReturn_t error = nvmlInit_v2();

    if (error)
    {
        throw NvmlException("Error initializing NVML SDK: %s\n", nvmlErrorString(error));
    }
}

void NvmlLibWrapper::LoadDynamicLib()
{
    _libraryHandle = dlopen(_libPath.c_str(), RTLD_LAZY);
    if (!_libraryHandle) {
        throw NvmlException("Failed to load %s, %s\n", _libPath.c_str(), dlerror());
    }
}

void NvmlLibWrapper::FreeDynamicLib()
{
    if (_libraryHandle) {
        dlclose(_libraryHandle);
        _libraryHandle = nullptr;
    }
}

void* NvmlLibWrapper::LoadDynamicFunc(const std::string& functionName)
{
    const char* error;
    void      * funcPointer = nullptr;

    funcPointer = dlsym(_libraryHandle, functionName.c_str());

    if ((error = dlerror()) != nullptr) {
        throw NvmlException("Failed to load dynamic function: %s. error: %s\n", functionName, error);
    }

    return funcPointer;
}

void NvmlLibWrapper::LoadDynamicFuncs()
{
    try
    {
        nvmlInit = (f_nvmlInit_v2)LoadDynamicFunc("nvmlInit_v2");
        nvmlShutdown = (f_nvmlShutdown)LoadDynamicFunc("nvmlShutdown");
        nvmlDeviceGetCount = (f_nvmlDeviceGetCount_v2)LoadDynamicFunc("nvmlDeviceGetCount_v2");
        nvmlDeviceGetHandleByIndex =
          (f_nvmlDeviceGetHandleByIndex_v2)LoadDynamicFunc("nvmlDeviceGetHandleByIndex_v2");
        nvmlDeviceGetPciInfo =
          (f_nvmlDeviceGetPciInfo_v3)LoadDynamicFunc("nvmlDeviceGetPciInfo_v3");
        nvmlErrorString = (f_nvmlErrorString)LoadDynamicFunc("nvmlErrorString");
        nvmlDeviceReadWritePRM =
          (f_nvmlDeviceReadWritePRM)LoadDynamicFunc("nvmlDeviceReadWritePRM_v1");
    }
    catch (const std::exception& e)
    {
         throw NvmlException(e.what() + string("\nPlease make sure you are using an up to date version of NVML lib."));
    }
}
