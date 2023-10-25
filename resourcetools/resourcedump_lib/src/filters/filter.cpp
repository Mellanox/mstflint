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

#include "filter.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_command.h"

namespace mft
{
namespace resource_dump
{
namespace filters
{
using namespace std;

Filter::Filter(ResourceDumpCommand& command) : _command(command) {}

Filter::FilteredView Filter::apply()
{
    if (!_command.data_fetched())
    {
        throw ResourceDumpException(ResourceDumpException::Reason::DATA_NOT_FETCHED);
    }
    return _apply();
}

Filter::FilteredView::FilteredView(istream& is) : filtered_stream(is) {}

} // namespace filters
} // namespace resource_dump
} // namespace mft