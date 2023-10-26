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
