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

#ifndef RESOURCE_DUMP_FETCHER_FACTORY_S
#define RESOURCE_DUMP_FETCHER_FACTORY_S

#include "reg_access_resource_dump_fetcher.h"
#ifndef NO_RDMEM
#include "reg_access_resource_dump_mkey_fetcher.h"
#endif
#include "resource_dump_types.h"
#include "resource_dump_error_handling.h"

#include <memory>

namespace mft
{
namespace resource_dump
{
namespace fetchers
{

unique_ptr<Fetcher>
  create_fetcher(mfile_t* mf, device_attributes device_attrs, dump_request dump_request, uint32_t depth)
{
    if (!device_attrs.rdma_name || std::string(device_attrs.rdma_name).size() == 0)
    {
        return unique_ptr<Fetcher>{new RegAccessResourceDumpFetcher(mf, device_attrs, dump_request, depth)};
    }
    else
    {
#ifndef NO_RDMEM
        return unique_ptr<Fetcher>{new RegAccessResourceDumpMkeyFetcher(mf, device_attrs, dump_request, depth)};
#else
        throw ResourceDumpException(ResourceDumpException::Reason::OS_NOT_SUPPORTED);
#endif
    }
}

} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_FETCHER_FACTORY_S
