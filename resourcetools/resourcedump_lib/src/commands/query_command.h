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
