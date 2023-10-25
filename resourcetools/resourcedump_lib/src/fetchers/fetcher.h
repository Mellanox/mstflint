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

#ifndef RESOURCE_DUMP_FETCHER_S
#define RESOURCE_DUMP_FETCHER_S

#include <iostream>
#include <memory>
#include <type_traits>

namespace mft
{
namespace resource_dump
{
namespace fetchers
{
using namespace std;

class Fetcher
{
public:
    virtual ~Fetcher() = default;
    virtual void set_streams(std::shared_ptr<std::ostream> os, std::shared_ptr<std::istream> is)
    {
        static_assert(true, "Abstract class, unimplemented");
    };
    virtual void fetch_data() { static_assert(true, "Abstract class, unimplemented"); };
    virtual void pre_parse_process(){};
    virtual void post_parse_process(){};
};
} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_FETCHER_S
