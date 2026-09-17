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

#include "LinuxDynamicLinking.h"

#include <dlfcn.h>

#include <stdexcept>

#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"

LinuxDynamicLinking::~LinuxDynamicLinking()
{
    if (m_pvLibraryHandle)
    {
        FreeDynamicLibrary();
    }
}

int LinuxDynamicLinking::LoadDynamicLibrary(const std::string& poLibraryName)
{
    // The function dlopen() loads the dynamic library file named by
    //   the null-terminated string filename and returns
    //   an "handle" for the dynamic library.
    LOG.Info("dlopen function called, library name: " + poLibraryName);

    m_pvLibraryHandle = dlopen(poLibraryName.c_str(), RTLD_LAZY);

    if (!m_pvLibraryHandle)
    {
        const char* pcReturnError = dlerror();
        LOG_AND_THROW_MFT_ERROR("Failed to load the shared library: " + poLibraryName +
                                ", dlerror: " + std::string(pcReturnError));
    }

    LOG.Info("Dynamic library loaded successfully: " + poLibraryName);
    return 0;
}

void LinuxDynamicLinking::FreeDynamicLibrary()
{
    const char* pcReturnError;

    if (m_pvLibraryHandle)
    {
        // Decrements the reference count on the dynamic library handle.
        dlclose(m_pvLibraryHandle);

        if ((pcReturnError = dlerror()) != NULL)
        {
            throw std::invalid_argument("Failed to free the dynamic linking library.");
        }

        m_pvLibraryHandle = NULL;
    }
}

void* LinuxDynamicLinking::GetFunctionAddress(const std::string& poFunctionName, bool bIgnoreFailure)
{
    void* pvFunctionAddress = NULL;
    const char* pcReturnError;

    // The function dlsym() takes a "handle" of a dynamic
    //   library returned by dlopen(), and the null-terminated symbol name.
    // The return value will be the address where that symbol is loaded into memory.
    pvFunctionAddress = dlsym(m_pvLibraryHandle, poFunctionName.c_str());

    LOG.Info("dlsym function called, function name: " + poFunctionName);
    if ((pcReturnError = dlerror()) != NULL)
    {
        if (bIgnoreFailure)
        {
            LOG.Info("Failed to get the function address: " + poFunctionName);
        }
        else
        {
            throw std::invalid_argument("Failed to get the function " + poFunctionName);
        }
    }

    return pvFunctionAddress;
}
