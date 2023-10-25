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
