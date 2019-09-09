
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
 */

/*
 * mlxarchive_mfa2_common_header.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <tools_layouts/tools_open_layouts.h>
#include "mlxarchive_mfa2_common_header.h"

using namespace mfa2;

CommonHeader::CommonHeader(u_int8_t version, MFA2Type type, u_int16_t length) :
    _version(version), _type(type), _length(length)
{
};

void CommonHeader::pack(vector<u_int8_t>& buff) const
{
    vector<u_int8_t> tmpBuff;
    struct tools_open_common_header commonHeader;

    //padding buff if it is not DW aligned:
    for (unsigned int i = 0; i < (buff.size() % 4); i++) {
        buff.push_back(0x0);
    }
    /*switch () {
        case 3:
            buff.push_back(0x0);
        case 2:
            buff.push_back(0x0);
        case 1:
            buff.push_back(0x0);
            break;
        default:
            break;
    }*/

    tmpBuff.resize(tools_open_common_header_size(), 0x0);

    memset(&commonHeader, 0x0, sizeof(commonHeader));
    commonHeader.version    = _version;
    commonHeader.type       = (u_int8_t) _type;
    commonHeader.length     = _length;

    tools_open_common_header_pack(&commonHeader, tmpBuff.data());
    packBytesArray(tmpBuff.data(), tmpBuff.size(), buff);
}

bool CommonHeader::unpack(Mfa2Buffer & buff) {
    //align header
    long pos = buff.tell();
    if(pos % 4 != 0) {
        buff.seek(4-(pos%4), SEEK_CUR);
    }
    int arr_size = tools_open_common_header_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    struct tools_open_common_header commonHeader;
    memset(&commonHeader, 0x0, sizeof(commonHeader));
    tools_open_common_header_unpack(&commonHeader, arr);
    delete[] arr;
    arr = NULL;
    _version = commonHeader.version;
    _type = (MFA2Type)commonHeader.type;
    _length = commonHeader.length;
    return true;
}
