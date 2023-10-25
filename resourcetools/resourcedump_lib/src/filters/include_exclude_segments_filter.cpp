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

#include "include_exclude_segments_filter.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_segments.h"
#include "resource_dump_command.h"
#include "utils.h"

#include <algorithm>
#include <iterator>

namespace mft
{
namespace resource_dump
{
namespace filters
{
using namespace std;

IncludeExcludeSegmentsFilter::IncludeExcludeSegmentsFilter(ResourceDumpCommand& command,
                                                           const vector<uint16_t> selected_segment_ids,
                                                           bool include) :
    Filter{command}, _selected_segment_ids{selected_segment_ids}, _include{include}, _filtered_stream()
{
}

string IncludeExcludeSegmentsFilter::get_big_endian_string()
{
    return get_big_endian_string_impl<stringstream>(_filtered_stream);
}

Filter::FilteredView IncludeExcludeSegmentsFilter::_apply()
{
    resource_dump_segment_header header_buffer{0};
    istream& parsed_istream = _command.get_native_stream();
    bool include;

    for (auto segment_offset : _command.get_segment_offsets())
    {
        parsed_istream.seekg(segment_offset);
        parsed_istream.read(reinterpret_cast<char*>(&header_buffer), sizeof(resource_dump_segment_header));
        include = find(_selected_segment_ids.cbegin(), _selected_segment_ids.cend(), header_buffer.segment_type) !=
                  _selected_segment_ids.cend();
        include = _include ? include : !include;

        if (include)
        {
            _filtered_stream.write(reinterpret_cast<char*>(&header_buffer), sizeof(resource_dump_segment_header));
            uint16_t segment_payload_size = 4 * header_buffer.length_dw - sizeof(resource_dump_segment_header);
            copy_n(istreambuf_iterator<char>(parsed_istream),
                   segment_payload_size,
                   ostreambuf_iterator<char>(_filtered_stream));
        }
    }
    Filter::FilteredView ret{_filtered_stream};
    ret.size = _filtered_stream.tellp();
    return ret;
}

} // namespace filters
} // namespace resource_dump
} // namespace mft
