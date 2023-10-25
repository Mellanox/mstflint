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

struct mfile_t;

namespace mft
{
namespace resource_dump
{
struct device_attributes;
struct dump_request;

namespace fetchers
{
class Fetcher;

unique_ptr<Fetcher>
  create_fetcher(mfile_t* mf, device_attributes device_attrs, dump_request dump_request, uint32_t depth);

} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_FETCHER_FACTORY_S
