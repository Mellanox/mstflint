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

#include "VFIODriverAccessWrapperC.h"
#include "VFIODriverAccess.h"
#include <string>
#include <iomanip>
#include <sstream>

int GetVSECStartOffset(unsigned domain, unsigned bus, unsigned dev, unsigned func, uint64_t* vsecOffset, int* vfioFD)
{
    try
    {
        std::ostringstream oss;
        oss << std::hex << std::setw(4) << std::setfill('0') << domain << ":" << std::setw(2) << std::setfill('0')
            << bus << ":" << std::setw(2) << std::setfill('0') << dev << "." << func;

        std::string dbdf = oss.str();
        VFIODriverAccess::GetVSECStartOffset(dbdf, *vsecOffset, *vfioFD);
    }
    catch (const std::exception& e)
    {
        return -1;
    }
    return 0;
}
