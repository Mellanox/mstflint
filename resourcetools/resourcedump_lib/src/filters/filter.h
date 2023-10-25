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

#ifndef RESOURCE_DUMP_FILTER_S
#define RESOURCE_DUMP_FILTER_S

#include <iostream>

namespace mft
{
namespace resource_dump
{
class ResourceDumpCommand;
namespace filters
{

class Filter
{
public:
    struct FilteredView
    {
        FilteredView(std::istream&);
        std::istream& filtered_stream;
        size_t size{0};
    };

    Filter(ResourceDumpCommand& command);

    FilteredView apply();

protected:
    virtual FilteredView _apply() = 0;

    ResourceDumpCommand& _command;

public:
};
} // namespace filters
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_FILTER_S
