/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#pragma once

#include <string>
#include <nvml.h>

using std::string;

typedef nvmlReturn_t (*f_nvmlDeviceGetCount_v2)(unsigned int*);
typedef nvmlReturn_t (*f_nvmlDeviceGetHandleByIndex_v2)(unsigned int, nvmlDevice_t*);
typedef nvmlReturn_t (*f_nvmlDeviceGetPciInfo_v3)(nvmlDevice_t, nvmlPciInfo_t*);
typedef const char* (*f_nvmlErrorString)(nvmlReturn_t);
typedef nvmlReturn_t (*f_nvmlInit_v2)(void);
typedef nvmlReturn_t (*f_nvmlShutdown)(void);
typedef nvmlReturn_t (*f_nvmlDeviceReadWritePRM)(nvmlDevice_t, nvmlPRMTLV_v1_t*);

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


private:
    void InitNvmlSDK();
    void LoadDynamicFuncs();
    void* LoadDynamicFunc(const std::string& functionName);
    void LoadDynamicLib();
    void FreeDynamicLib();

    const string _libPath;
    void       * _libraryHandle;
};
