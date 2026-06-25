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

#include "FactoryDynamicLinking.h"

#if defined(__WIN__)

#include "WindowsDynamicLinking.h"

#else //__WIN__

#include "LinuxDynamicLinking.h"

#endif //__WIN__

std::unique_ptr<DynamicLinking> FactoryDynamicLinking::GetInstance()
{
#if defined(__WIN__)

    return std::unique_ptr<DynamicLinking>(new WindowsDynamicLinking());

#else //__WIN__

    return std::unique_ptr<DynamicLinking>(new LinuxDynamicLinking());

#endif //__WIN__
}
