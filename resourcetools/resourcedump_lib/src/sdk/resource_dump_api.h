/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#ifndef RESOURCE_DUMP_API_H
#define RESOURCE_DUMP_API_H

#include "resource_dump_types.h"

#include <string>

namespace mft
{
namespace resource_dump
{
class DumpCommand;
class QueryCommand;

/**
 * @brief Returns an executed dump command's data in the requested byte order.
 * Shared by the resource dump C SDK and the MFT SDK so the two cannot report different data for the
 * same dump.
 * @param dump_command An already executed dump command.
 * @param strip_control_segments Whether the control segments are filtered out of the data.
 * @param endianess The byte order of the returned data.
 * @throws ResourceDumpException if the control segment filter fails.
 */
std::string get_dump_data(DumpCommand& dump_command, bool strip_control_segments, endianess_t endianess);

/**
 * @brief Returns an executed query command's menu records in the requested byte order.
 * The records are returned as they come off the wire, so their name fields carry the byte order the
 * caller asked for and are not decoded.
 * @param query_command An already executed query command.
 * @param endianess The byte order of the returned records.
 */
std::string get_menu_data(QueryCommand& query_command, endianess_t endianess);
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_API_H
