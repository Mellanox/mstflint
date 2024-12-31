/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#include "crc16.h"
#include <stdlib.h>
void Crc16::add(u_int32_t o)
{
    if (_debug)
    {
        printf("Crc16::add(%08x)\n", o);
    }
    for (int i = 0; i < 32; i++)
    {
        if (_crc & 0x8000)
        {
            _crc = (u_int16_t)((((_crc << 1) | (o >> 31)) ^ 0x100b) & 0xffff);
        }
        else
        {
            _crc = (u_int16_t)(((_crc << 1) | (o >> 31)) & 0xffff);
        }
        o = (o << 1) & 0xffffffff;
    }
} // Crc16::add
////////////////////////////////////////////////////////////////////////
void Crc16::finish()
{
    for (int i = 0; i < 16; i++)
    {
        if (_crc & 0x8000)
        {
            _crc = ((_crc << 1) ^ 0x100b) & 0xffff;
        }
        else
        {
            _crc = (_crc << 1) & 0xffff;
        }
    }
    // Revert 16 low bits
    _crc = _crc ^ 0xffff;
} // Crc16::finish
////////////////////////////////////////////////////////////////////////
void Crc16::operator<<(std::vector<u_int8_t> v)
{
    if (v.size() % 4)
    {
        fprintf(stderr, "Internal error: Image section size should be 4-bytes aligned");
        exit(1);
    }
    for (u_int32_t i = 0; i < v.size(); i += 4)
    {
        u_int32_t dw_be = __cpu_to_be32(*((u_int32_t*)(&v[i])));
        add(dw_be);
    }
}
