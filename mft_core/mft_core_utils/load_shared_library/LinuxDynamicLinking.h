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

#ifndef LINUX_DYNAMIC_LINKING_H
#define LINUX_DYNAMIC_LINKING_H

#include <string>
#include <vector>

#include "DynamicLinking.h"

class LinuxDynamicLinking : public DynamicLinking
{
public:
    // Load the dynamic library.
    virtual int LoadDynamicLibrary(const std::string& poLibraryName);

    // Free the dynamic library.
    virtual void FreeDynamicLibrary();

    // Get the symbol function address.
    virtual void* GetFunctionAddress(const std::string& poFunctionName, bool bIgnoreFailure = false);

private:
    LinuxDynamicLinking(){};
    virtual ~LinuxDynamicLinking();
    friend class FactoryDynamicLinking;

    // Shared library handle.
    void* m_pvLibraryHandle;
};

#endif // LINUX_DYNAMIC_LINKING_H
