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
 * mlxcfg_db_items.h
 *
 *  Created on: Nov 15, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXCFG_DB_ITEMS_H_
#define MLXCFG_DB_ITEMS_H_

#include <string>

#include <common/compatibility.h>
#include <common/tools_version.h>

using namespace std;

namespace DB {

class ByteBitString {
public:
    explicit ByteBitString(const string& str);
    u_int32_t getBytesPart() const { return _bytesPart;}
protected:
    u_int32_t _bytesPart;     //describes the bytes part of the offset string ("0x51.3", the bytes part is 0x51)
    u_int32_t _bitsPart;     //describes the bits part of the offset string ("0x51.3", the bits part is 3)
};

class Offset : public ByteBitString {
public:
    explicit Offset(const string& offset) : ByteBitString(offset) {};
    u_int32_t toBigEndian(u_int32_t sizeInBits,
                            u_int32_t withBitsPart = true) const;
};

class Size : public ByteBitString {
public:
    explicit Size(const string& size) : ByteBitString(size) {};
    unsigned int toBits() const { return _bytesPart * 8 + _bitsPart;};
};

};
#endif
