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

#ifndef RESDUMP_UTILS_H
#define RESDUMP_UTILS_H

#include <common/compatibility.h>

#include <string>
#include <iostream>
#include <sstream>

namespace mft
{
namespace resource_dump
{

using namespace std;

template<typename ISTREAM, typename OSTREAM>
std::string get_big_endian_string_impl(ISTREAM& is, OSTREAM& os)
{
    stringstream be_stream;
    is.seekg(0);
    union
    {
        char as_bytes[4];
        uint32_t as_int;
    } dword;

    for (typename OSTREAM::pos_type i = 0; i < os.tellp() / 4; i += 1)
    {
        is.read(dword.as_bytes, 4);
        if (__BYTE_ORDER != __BIG_ENDIAN)
        {
            dword.as_int = __cpu_to_be32(dword.as_int);
        }
        be_stream.write(dword.as_bytes, 4);
    }
    return be_stream.str();
}

template<typename STREAM>
std::string get_big_endian_string_impl(STREAM& str)
{
    return get_big_endian_string_impl<STREAM, STREAM>(str, str);
}

} // namespace resource_dump
} // namespace mft

#endif // RESDUMP_UTILS_H
