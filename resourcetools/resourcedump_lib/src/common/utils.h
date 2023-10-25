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
