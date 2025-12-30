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

#include "FactoryOperatingSystemAPI.h"
#include "Linux.h"

std::unique_ptr<OperatingSystemAPI> FactoryOperatingSystemAPI::GetInstance()
{
    return std::unique_ptr<OperatingSystemAPI>(new Linux());
}
