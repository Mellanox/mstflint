/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 *
 * mlxcfg_db_items.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: Ahmad Soboh
 */

#include <string>
#include "mlxcfg_db_items.h"

using namespace std;
using namespace DB;

ByteBitString::ByteBitString(const string& str)
{
    size_t pos = str.find('.');
    if (pos == string::npos) { //No bits part in this case (e.g. 0x0)
        _bitsPart = 0x0;
        _bytesPart = strtol(str.c_str(), NULL, 0);
    } else {
        _bitsPart = atoi(str.substr(pos + 1).c_str());
        _bytesPart = strtol(str.substr(0, pos).c_str(), NULL, 0);
    }
}

u_int32_t Offset::toBigEndian(u_int32_t sizeInBits, u_int32_t withBitsPart) const
{
    if (!withBitsPart) {
        return 8 * _bytesPart;
    }

    u_int32_t offsetLE  = 8 * _bytesPart + _bitsPart;
    return 32 - (offsetLE % 32) - sizeInBits + ((offsetLE >> 5) << 5);
}
