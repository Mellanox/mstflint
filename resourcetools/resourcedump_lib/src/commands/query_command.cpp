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

#include "query_command.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"
#include "resource_dump_segments.h"
#include "utils.h"

#include <common/compatibility.h>

#include <cstring>
#include <memory>

namespace mft
{
namespace resource_dump
{
using namespace std;

QueryCommand::QueryCommand(device_attributes device_attrs) :
    ResourceDumpCommand{device_attrs, dump_request{static_cast<uint16_t>(SegmentType::menu)}, 0, false},
    _sstream{make_shared<stringstream>()}
{
    _ostream = _sstream;
    _istream = _sstream;
}

string QueryCommand::get_big_endian_string()
{
    return get_big_endian_string_impl<stringstream>(*(static_pointer_cast<stringstream>(_sstream)));
}

bool QueryCommand::validate()
{
    // TODO: go through capability fetcher, also not available in the python version
    return true;
}

void QueryCommand::parse_data()
{
    menu_records = RecordList(_sstream->str());
}

const string QueryCommand::to_string() const
{
    auto str = string{"PRINT FUNCTION NOT IMPLEMENTED"};
    return str;
}

RecordList::RecordList(string&& retrieved_data) : _full_data(move(retrieved_data))
{
    uint16_t prefix_size_bytes = sizeof(resource_dump_segment_header) + sizeof(info_segment_data) +
                                 sizeof(resource_dump_segment_header) + sizeof(command_segment_data) +
                                 sizeof(resource_dump_segment_header);
    _size = (reinterpret_cast<menu_segment_sub_header*>(&_full_data[prefix_size_bytes]))->num_of_records;

    prefix_size_bytes += sizeof(menu_segment_sub_header);
    _record_data = reinterpret_cast<menu_record_data*>(&_full_data[prefix_size_bytes]);

    // Switch endianness of char* to represent strings
}

const uint16_t RecordList::size()
{
    return _size;
}

const menu_record_data& RecordList::operator*()
{
    return operator[](0);
}

const menu_record_data& RecordList::operator[](const uint16_t idx)
{
    if (idx >= _size)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::DATA_OVERFLOW);
    }
    return _record_data[idx];
}
} // namespace resource_dump
} // namespace mft
