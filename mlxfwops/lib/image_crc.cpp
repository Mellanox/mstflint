/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "image_crc.h"

namespace std
{
};
using namespace std;

void ImageCrc::add(u_int8_t v)
{
    for (u_int32_t i = 0; i < 8; i++)
    {
        u_int16_t carry = _crc & 0x8000;
        _crc = (_crc << 1) | ((v >> 7) & 0x1);
        if (carry)
        {
            _crc ^= 0x100b;
        }
        v <<= 1;
    }
}

void ImageCrc::operator<<(u_int32_t v)
{
    add(v >> 24);
    add(v >> 16);
    add(v >> 8);
    add(v);
}

void ImageCrc::operator<<(const vector<u_int8_t> v)
{
    for (u_int32_t i = 0; i < v.size(); i++)
        add(v[i]);
}

u_int16_t ImageCrc::get()
{
    u_int16_t OldCrc = _crc;

    // add 2B of 0's // TODO: this is ugly, compatabily required for the ROM and other FWs
    add(0);
    add(0);
    u_int16_t result = _crc;
    _crc = OldCrc;

    // revert
    return (result & 0xffff) ^ 0xffff;
}
