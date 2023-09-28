/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 *  Version: $Id$
 */

#include "adb_xmlCreator.h"
#include <boost/algorithm/string.hpp>

string xmlCreator::indentString(int i)
{
    string s;
    while (i--)
    {
        s += "\t";
    }
    return s;
}

int xmlCreator::dword(int bits)
{
    if (bits < 0)
    {
        bits -= 31;
    }

    return (bits / 32) * 4;
}

int xmlCreator::startBit(int bits)
{
    return bits % 32;
}

string xmlCreator::formatAddr(u_int32_t offs, u_int32_t size)
{
    char str[64];
    sprintf(str, "0x%x.%u:%u", dword(offs), startBit(offs), size);
    return str;
}

/*template <class AdbInstance>
bool xmlCreator::compareFieldsPtr(AdbInstance *f1, AdbInstance *f2)
{
  return (*f1) < (*f2);
}*/

string xmlCreator::encodeXml(const string& data)
{
    std::string buffer;
    buffer.reserve(data.size());
    for (size_t pos = 0; pos != data.size(); ++pos)
    {
        switch (data[pos])
        {
            case '&':
                buffer.append("&amp;");
                break;

            case '\"':
                buffer.append("&quot;");
                break;

            case '\'':
                buffer.append("&apos;");
                break;

            case '<':
                buffer.append("&lt;");
                break;

            case '>':
                buffer.append("&gt;");
                break;

            default:
                buffer.append(1, data.at(pos));
                break;
        }
    }

    return buffer;
}

string xmlCreator::descNativeToXml(const string& desc)
{
    return boost::replace_all_copy(desc, "\n", "\\;");
}
