/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "LinuxDynamicLinking.h"

#include <dlfcn.h>

#include <stdexcept>

#include "mft_logger/mft_logger.h"
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
    MFT_LOG_INFO(mft_logger::Layer::MFT_CORE, ("dlopen function called, library name: " + poLibraryName).c_str());

    m_pvLibraryHandle = dlopen(poLibraryName.c_str(), RTLD_LAZY);

    if (!m_pvLibraryHandle)
    {
        const char* pcReturnError = dlerror();
        LOG_AND_THROW_MFT_ERROR("Failed to load the shared library: " + poLibraryName +
                                ", dlerror: " + std::string(pcReturnError));
    }

    MFT_LOG_INFO(mft_logger::Layer::MFT_CORE, ("Dynamic library loaded successfully: " + poLibraryName).c_str());
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

    MFT_LOG_INFO(mft_logger::Layer::MFT_CORE, ("dlsym function called, function name: " + poFunctionName).c_str());
    if ((pcReturnError = dlerror()) != NULL)
    {
        if (bIgnoreFailure)
        {
            MFT_LOG_INFO(mft_logger::Layer::MFT_CORE, ("Failed to get the function address: " + poFunctionName).c_str());
        }
        else
        {
            throw std::invalid_argument("Failed to get the function " + poFunctionName);
        }
    }

    return pvFunctionAddress;
}
