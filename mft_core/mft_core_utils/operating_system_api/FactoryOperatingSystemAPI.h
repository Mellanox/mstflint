/*
 * Copyright (c) 2020-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#pragma once

#include <memory>
#include "OperatingSystemAPI.h"

class FactoryOperatingSystemAPI
{
private:
    // Singleton.
    FactoryOperatingSystemAPI(){};
    virtual ~FactoryOperatingSystemAPI(){};

public:
    // Get the OS instance.
    static std::unique_ptr<OperatingSystemAPI> GetInstance();
};