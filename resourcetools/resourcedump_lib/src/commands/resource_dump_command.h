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

#ifndef RESOURCE_DUMP_COMMAND_H
#define RESOURCE_DUMP_COMMAND_H

#include <iostream>
#include <memory>
#include <vector>

#include "resource_dump_types.h"
#include "fetcher.h"

struct mfile_t;

namespace mft
{
namespace resource_dump
{
struct device_attributes;
struct dump_request;

class ResourceDumpCommand
{
public:
    virtual void execute() final;
    const size_t get_dumped_size() const;
    const bool data_fetched() const;
    const std::vector<size_t>& get_segment_offsets() const;

    std::istream& get_native_stream();

protected:
    ResourceDumpCommand() = default;
    ResourceDumpCommand(device_attributes device_attrs, dump_request dump_request, uint32_t depth, bool is_textual);
    virtual ~ResourceDumpCommand();

    virtual bool validate() = 0;
    virtual void parse_data();
    friend std::ostream& operator<<(std::ostream& out, const ResourceDumpCommand& command);
    virtual const std::string to_string() const;

    mfile_t* _mf;
    std::unique_ptr<fetchers::Fetcher> _fetcher;
    std::shared_ptr<std::ostream> _ostream;
    std::shared_ptr<std::istream> _istream;
    bool _is_textual{false};

    bool _data_fetched{false};

    size_t _dumped_size{0};

    std::vector<size_t> _segment_offsets;
};
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_COMMAND_H
