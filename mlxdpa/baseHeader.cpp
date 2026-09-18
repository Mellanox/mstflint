/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */
#include "baseHeader.h"
#include "mft_utils/mft_utils.h"
#include <iostream>

BaseHeader::BaseHeader()
{
    _priority = StructPriority::Unknown;
}

BaseHeader::BaseHeader(StructPriority priority)
{
    _priority = priority;
}

void BaseHeader::SetPriority(StructPriority priority)
{
    _priority = priority;
}

BaseHeader::StructPriority BaseHeader::ToStructPriority(string priority)
{
    mft_utils::to_lowercase(priority);
    if (priority == "user")
    {
        return StructPriority::User;
    }
    else if (priority == "vendor" || priority == "oem")
    {
        return StructPriority::Vendor;
    }
    else if (priority == "nvidia")
    {
        return StructPriority::Nvidia;
    }
    else
    {
        return StructPriority::Unknown;
    }
}

std::string BaseHeader::ToStringPriority(StructPriority priority)
{
    switch (priority)
    {
        case StructPriority::User:
            return "user";
        case StructPriority::Vendor:
            return "vendor";
        case StructPriority::Nvidia:
            return "nvidia";
        default:
            return "unknown";
    }
}