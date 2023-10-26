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
