/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "WindowsDynamicLinking.h"

#include <stdexcept>

#include "mft_core/mft_core_utils/logger/Logger.h"

WindowsDynamicLinking::~WindowsDynamicLinking()
{
    if (m_poLibraryHandle)
    {
        FreeDynamicLibrary();
    }
}

void* WindowsDynamicLinking::GetFunctionAddress(const std::string& oFunctionName, bool bIgnoreFailure)
{
    void* pvFunctionAddress = NULL;
    if (!m_poLibraryHandle)
    {
        LOG.Error("No dynamic library loaded");
    }

    else
    {
        pvFunctionAddress = (void*)GetProcAddress(m_poLibraryHandle, oFunctionName.c_str());
        if (!pvFunctionAddress)
        {
            if (!bIgnoreFailure)
            {
                LOG.Error("Failed to load dynamic function " + oFunctionName);
            }
        }
    }

    return pvFunctionAddress;
}

int WindowsDynamicLinking::LoadDynamicLibrary(const std::string& poLibraryName)
{
    LOG.Info("Loading dynamic library: " + poLibraryName);

    m_poLibraryHandle = LoadLibrary(poLibraryName.c_str());

    if (!m_poLibraryHandle)
    {
        LOG.Error("Failed to load the dynamic library: " + poLibraryName);
        return -1;
    }

    LOG.Info("Dynamic library loaded successfully: " + poLibraryName);

    return 0;
}

void WindowsDynamicLinking::FreeDynamicLibrary()
{
    if (m_poLibraryHandle)
    {
        // Decrements the reference count on the dynamic library handle.
        if (!FreeLibrary(m_poLibraryHandle))
        {
            throw std::invalid_argument("Failed to free the dynamic linking library.");
        }

        m_poLibraryHandle = NULL;
    }
}