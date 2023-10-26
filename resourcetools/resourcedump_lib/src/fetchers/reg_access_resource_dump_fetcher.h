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

#ifndef RESOURCE_DUMP_REGACCESS_RESDUMP_H
#define RESOURCE_DUMP_REGACCESS_RESDUMP_H

#include "fetcher.h"
#include "resource_dump_segments.h"

#include "tools_layouts/reg_access_hca_layouts.h"

#include <iostream>
#include <memory>

struct mfile_t;

namespace mft
{
namespace resource_dump
{
struct dump_request;
struct device_attributes;
namespace fetchers
{
class RegAccessResourceDumpFetcher : public Fetcher
{
public:
    RegAccessResourceDumpFetcher(mfile_t* mfile,
                                 device_attributes device_attrs,
                                 dump_request segment_params,
                                 uint32_t depth = (uint32_t)-1);

    virtual ~RegAccessResourceDumpFetcher() = default;
    void set_streams(std::shared_ptr<std::ostream> os,
                     std::shared_ptr<std::istream> is) override; // TODO: find a way to integrate into c'tor

    void fetch_data() override;

protected:
    virtual void init_reg_access_layout();

    virtual void reset_reg_access_layout();

    virtual void write_payload_data_to_ostream();

    mfile_t* _mf;
    uint16_t _vhca;

    shared_ptr<std::ostream> _ostream;
    shared_ptr<std::istream> _istream;

    reference_segment_data _segment_params;
    reg_access_hca_resource_dump_ext _reg_access_layout{0};

private:
    void retrieve_from_reg_access();

    void validate_reply();

    void enable_streams_exceptions();

    void restore_streams_exceptions();

    static uint32_t calculate_segment_data_size(uint16_t full_size_dw);

    std::ios::iostate _orig_os_exceptions;
    std::ios::iostate _orig_is_exceptions;
    uint32_t _depth;

protected:
    uint8_t _current_seq_num{0};
};

} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_REGACCESS_RESDUMP_H
