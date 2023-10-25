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

#ifndef RESOURCE_DUMP_DUMP_COMMAND_H
#define RESOURCE_DUMP_DUMP_COMMAND_H

#include "resource_dump_command.h"

namespace mft
{
namespace resource_dump
{
class DumpCommand : public ResourceDumpCommand
{
public:
    // File Stream c'tor
    DumpCommand(device_attributes device_attrs,
                dump_request segment_params,
                uint32_t depth,
                const std::string bin_filename,
                bool is_textual = false);

    // Buffer Stream c'tor
    DumpCommand(device_attributes device_attrs, dump_request segment_params, uint32_t depth, bool is_textual = false);

    std::string get_big_endian_string();
    void reverse_fstream_endianess();

    bool validate() override;

    const std::string to_string() const override;

private:
    bool _allocated_ostream{false};
};
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_DUMP_COMMAND_H
