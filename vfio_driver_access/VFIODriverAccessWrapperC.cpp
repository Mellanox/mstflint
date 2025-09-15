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

#include "VFIODriverAccessWrapperC.h"
#include "VFIODriverAccess.h"
#include <string>
#include <iomanip>
#include <sstream>

int GetStartOffsets(unsigned domain, unsigned bus, unsigned dev, unsigned func, int* deviceFD, uint64_t* vsecOffset, uint64_t* addressRegionOffset)
{
    try
    {
        std::ostringstream oss;
        oss << std::hex << std::setw(4) << std::setfill('0') << domain << ":" << std::setw(2) << std::setfill('0')
            << bus << ":" << std::setw(2) << std::setfill('0') << dev << "." << func;

        std::string dbdf = oss.str();
        VFIODriverAccess::OpenVFIODevices(dbdf, *deviceFD, *vsecOffset, *addressRegionOffset);
    }
    catch(const std::exception& e)
    {
        return -1;
    }
    return 0;
}

bool CheckifKernelLockdownIsEnabled()
{
    return VFIODriverAccess::CheckifKernelLockdownIsEnabled();
}

bool CheckifVfioPciDriverIsLoaded()
{
    return VFIODriverAccess::CheckifVfioPciDriverIsLoaded();
}

int CloseVFIODevices(int deviceFD)
{
    try
    {
        VFIODriverAccess::CloseVFIODevices(deviceFD);
    }
    catch(const std::exception& e)
    {
        return -1;
    }
    return 0;
}
