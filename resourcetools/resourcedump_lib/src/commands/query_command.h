/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */

#ifndef RESOURCE_DUMP_QUERY_COMMAND_H
#define RESOURCE_DUMP_QUERY_COMMAND_H

#include "resource_dump_command.h"

#include <sstream>

namespace mft
{
namespace resource_dump
{
struct menu_record_data;
class RecordList
{
public:
    RecordList(std::string&& retrieved_data);
    RecordList() = default;
    const menu_record_data& operator*();
    const menu_record_data& operator[](const uint16_t idx);
    const uint16_t size();

private:
    uint16_t _size;
    std::string _full_data;
    menu_record_data* _record_data;
};

class QueryCommand : public ResourceDumpCommand
{
public:
    QueryCommand(device_attributes device_attrs);

    std::string get_big_endian_string();

    RecordList menu_records;

protected:
    uint16_t _vhca;
    std::shared_ptr<std::stringstream> _sstream;

    bool validate() override;
    void parse_data() override;
    const std::string to_string() const override;

private:
};
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_QUERY_COMMAND_H
