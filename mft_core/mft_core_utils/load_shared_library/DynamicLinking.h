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

#ifndef DYNAMIC_LINKING_H
#define DYNAMIC_LINKING_H

#include <string>
#include <vector>

class DynamicLinking
{
public:
    virtual ~DynamicLinking(){};

    // Load the dynamic library (Should be implemented by the derived OS).
    virtual int LoadDynamicLibrary(const std::string& poLibraryName) = 0;

    // Free the dynamic library (Should be implemented by the derived OS).
    virtual void FreeDynamicLibrary() = 0;

    // Get the symbol function address (Should be implemented by the derived OS).
    virtual void* GetFunctionAddress(const std::string& poFunctionName, bool bIgnoreFailure = false) = 0;
};

#endif // DYNAMIC_LINKING_H
