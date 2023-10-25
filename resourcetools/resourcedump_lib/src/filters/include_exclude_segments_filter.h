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

#ifndef RESOURCE_DUMP_INCLUDE_EXCLUDE_FETCHER_H
#define RESOURCE_DUMP_INCLUDE_EXCLUDE_FETCHER_H

#include "filter.h"

#include <memory>
#include <vector>
#include <sstream>

namespace mft
{
namespace resource_dump
{
namespace filters
{
class IncludeExcludeSegmentsFilter : public Filter
{
public:
    IncludeExcludeSegmentsFilter(ResourceDumpCommand& command,
                                 const std::vector<uint16_t> selected_segment_ids,
                                 bool include = true);

    std::string get_big_endian_string();

protected:
    FilteredView _apply() override;

    const std::vector<uint16_t> _selected_segment_ids;
    bool _include;
    std::stringstream _filtered_stream;
};

} // namespace filters
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_INCLUDE_EXCLUDE_FETCHER_H
