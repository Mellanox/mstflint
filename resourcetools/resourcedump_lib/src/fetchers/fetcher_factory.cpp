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
