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

#include "strip_control_segments_filter.h"
#include "resource_dump_segments.h"

#include <vector>

namespace mft
{
namespace resource_dump
{
namespace filters
{
using namespace std;

StripControlSegmentsFilter::StripControlSegmentsFilter(ResourceDumpCommand& command) :
    IncludeExcludeSegmentsFilter{
      command,
      vector<uint16_t>{static_cast<uint16_t>(SegmentType::notice), static_cast<uint16_t>(SegmentType::command),
                       static_cast<uint16_t>(SegmentType::terminate), static_cast<uint16_t>(SegmentType::error),
                       static_cast<uint16_t>(SegmentType::info)},
      false}
{
}

} // namespace filters
} // namespace resource_dump
} // namespace mft
