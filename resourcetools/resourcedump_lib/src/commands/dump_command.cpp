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

#include "dump_command.h"
#include "resource_dump_types.h"
#include "resource_dump_error_handling.h"
#include "utils.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

namespace mft
{
namespace resource_dump
{
using namespace std;

DumpCommand::DumpCommand(device_attributes device_attrs,
                         dump_request segment_params,
                         uint32_t depth,
                         const string bin_filename,
                         bool is_textual) :
    ResourceDumpCommand{device_attrs, segment_params, depth, is_textual}
{
    _ostream = make_shared<ofstream>(bin_filename, ofstream::binary);
    if (_ostream->fail())
    {
        throw ResourceDumpException(ResourceDumpException::Reason::OPEN_FILE_FAILED);
    }
    _istream = make_shared<ifstream>(bin_filename, ifstream::binary);
    _istream->tie(_ostream.get());
    _allocated_ostream = true;
}

DumpCommand::DumpCommand(device_attributes device_attrs, dump_request segment_params, uint32_t depth, bool is_textual) :
    ResourceDumpCommand{device_attrs, segment_params, depth, is_textual}
{
    auto ss = make_shared<stringstream>();
    _ostream = ss;
    _istream = ss;
}

string DumpCommand::get_big_endian_string()
{
    return _allocated_ostream ?
             get_big_endian_string_impl<ifstream, ofstream>(*(static_pointer_cast<ifstream>(_istream)),
                                                            *(static_pointer_cast<ofstream>(_ostream))) :
             get_big_endian_string_impl<stringstream>(*(static_pointer_cast<stringstream>(_istream)));
}

void DumpCommand::reverse_fstream_endianess()
{
    if (!_allocated_ostream)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::OPERATION_INVALID_BUFFER_MODE);
    }
    auto reversed_string = get_big_endian_string();
    _ostream->seekp(0);
    _ostream->write(reversed_string.c_str(), reversed_string.size());
}

bool DumpCommand::validate()
{
    return true; // TODO: go through capability fetcher
}

const string DumpCommand::to_string() const
{
    auto str = string{"PRINT FUNCTION NOT IMPLEMENTED"};
    return str;
}

} // namespace resource_dump
} // namespace mft
