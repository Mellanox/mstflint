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
