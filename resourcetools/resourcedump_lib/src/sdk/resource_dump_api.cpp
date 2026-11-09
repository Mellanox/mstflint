/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "resource_dump_api.h"
#include "dump_command.h"
#include "query_command.h"
#include "strip_control_segments_filter.h"
#include "resource_dump_segments.h"

#include <common/compatibility.h>

#include <istream>

namespace mft
{
namespace resource_dump
{
using namespace std;

string get_dump_data(DumpCommand& dump_command, bool strip_control_segments, endianess_t endianess)
{
    string data;

    if (strip_control_segments)
    {
        filters::StripControlSegmentsFilter filter{dump_command};
        auto filtered_view = filter.apply();

        if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
        {
            data = filter.get_big_endian_string();
            data.resize(filtered_view.size);
        }
        else
        {
            data.resize(filtered_view.size);
            filtered_view.filtered_stream.read(&data[0], filtered_view.size);
        }
    }
    else
    {
        const size_t parsed_size = dump_command.get_dumped_size();

        if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
        {
            data = dump_command.get_big_endian_string();
            data.resize(parsed_size);
        }
        else
        {
            istream& parsed_stream = dump_command.get_native_stream();
            data.resize(parsed_size);
            parsed_stream.read(&data[0], parsed_size);
        }
    }

    return data;
}

string get_menu_data(QueryCommand& query_command, endianess_t endianess)
{
    string data;

    auto record_data_count = query_command.menu_records.size();

    // An empty menu is a valid answer, and dereferencing the record list would throw on it.
    if (record_data_count == 0)
    {
        return data;
    }

    auto record_data_size = sizeof(menu_record_data) * record_data_count;

    if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
    {
        data = query_command.get_big_endian_string();
        data.resize(record_data_size);
    }
    else
    {
        data.assign(reinterpret_cast<const char*>(&(*query_command.menu_records)), record_data_size);
    }

    return data;
}
} // namespace resource_dump
} // namespace mft
