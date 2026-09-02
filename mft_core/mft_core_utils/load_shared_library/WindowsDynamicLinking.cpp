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

#include "WindowsDynamicLinking.h"

#include <stdexcept>

#include "nvtoolslogger/NvToolsLogger.h"

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
        MFT_LOG_ERROR(nvtoolslogger::Layer::MFT_CORE, "No dynamic library loaded");
    }

    else
    {
        pvFunctionAddress = (void*)GetProcAddress(m_poLibraryHandle, oFunctionName.c_str());
        if (!pvFunctionAddress)
        {
            if (!bIgnoreFailure)
            {
                MFT_LOG_ERROR(nvtoolslogger::Layer::MFT_CORE, ("Failed to load dynamic function " + oFunctionName).c_str());
            }
        }
    }

    return pvFunctionAddress;
}

int WindowsDynamicLinking::LoadDynamicLibrary(const std::string& poLibraryName)
{
    MFT_LOG_INFO(nvtoolslogger::Layer::MFT_CORE, ("Loading dynamic library: " + poLibraryName).c_str());

    m_poLibraryHandle = LoadLibrary(poLibraryName.c_str());

    if (!m_poLibraryHandle)
    {
        MFT_LOG_ERROR(nvtoolslogger::Layer::MFT_CORE, ("Failed to load the dynamic library: " + poLibraryName).c_str());
        return -1;
    }

    MFT_LOG_INFO(nvtoolslogger::Layer::MFT_CORE, ("Dynamic library loaded successfully: " + poLibraryName).c_str());

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