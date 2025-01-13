/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#pragma once

#include "json/reader.h"

namespace mstflint
{
namespace common
{
class JSON_API ReaderWrapper
{
public:
    ReaderWrapper();
    ~ReaderWrapper();

    Json::Reader* getReader();

private:
    Json::Reader* reader;
};

} // namespace common
} // namespace mstflint