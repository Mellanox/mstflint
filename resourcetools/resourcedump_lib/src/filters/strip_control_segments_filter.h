/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef RESOURCE_DUMP_STRIPT_CONTROL_SEGMENTS_FILTER_H
#define RESOURCE_DUMP_STRIPT_CONTROL_SEGMENTS_FILTER_H

#include "include_exclude_segments_filter.h"

#include <iostream>
#include <memory>

namespace mft
{
namespace resource_dump
{
namespace filters
{
class StripControlSegmentsFilter : public IncludeExcludeSegmentsFilter
{
public:
    StripControlSegmentsFilter(ResourceDumpCommand& command);
};

} // namespace filters
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_STRIPT_CONTROL_SEGMENTS_FILTER_H
