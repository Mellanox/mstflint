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

#ifndef FACTORY_DYNAMIC_LINKING_H
#define FACTORY_DYNAMIC_LINKING_H

#include <memory>

#include "DynamicLinking.h"

class FactoryDynamicLinking
{
private:
    FactoryDynamicLinking(){};
    virtual ~FactoryDynamicLinking(){};

public:
    // Get the OS instance.
    static std::unique_ptr<DynamicLinking> GetInstance();
};

#endif // FACTORY_DYNAMIC_LINKING_H
