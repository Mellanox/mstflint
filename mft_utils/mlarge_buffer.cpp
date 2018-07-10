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
 * mlarge_buffer.cpp
 *
 *  Created on: Mar 9, 2016
 *      Author: adrianc
 */

#include <string.h>

#include "mlarge_buffer.h"


#define MFT_MIN(x, y) ((x) < (y) ? (x) : (y))
#define MFT_MAX(x, y) ((x) > (y) ? (x) : (y))

#ifdef _DEBUG_MODE
#define DBG_PRINTF(...) fprintf(stderr, __VA_ARGS__)
#else
#define DBG_PRINTF(...)
#endif

MBufferUnit& operator <<(MBufferUnit& a, MBufferUnit& b)
{
    if (!a.intersects(b) ) {
        return a;
    }
    u_int32_t newSize = MFT_MAX(a.offset() + a.size(), b.offset() + b.size()) - MFT_MIN(a.offset(), b.offset());
    u_int32_t newOffset = MFT_MIN(a.offset(), b.offset());
    std::vector<u_int8_t> newData(newSize, 0);

    // merge b onto a
    u_int32_t relativeOffsInBuffer = a.offset() - newOffset;
    memcpy(&newData[0] + relativeOffsInBuffer, &(a.data()[0]), a.size());
    relativeOffsInBuffer = b.offset() - newOffset;
    memcpy(&newData[0] + relativeOffsInBuffer, &(b.data()[0]), b.size());
    a = MBufferUnit(newData, newOffset);
    return a;
}

MBufferUnit& MBufferUnit::operator=(const MBufferUnit& other)
{
    if (this != &other) {
        this->_data = other._data;
        this->_offset = other._offset;
    }
    return *this;
}

bool MBufferUnit::intersects( const MBufferUnit& other) const
{
    if (this->offset() > (other.offset() + other.size()) || (this->offset() + this->size()) < other.offset() ) {
        return false;
    }
    return true;
}

void MlargeBuffer::add(const std::vector<u_int8_t>& data, u_int32_t offset)
{
    if (data.size() == 0) {
        return;
    }
    DBG_PRINTF("-D- adding chunk: 0x%08x - 0x%08x (0x%08x)\n", offset, (unsigned)data.size() + offset, (unsigned)data.size());
    // create MBufferUnit
    MBufferUnit bufferUnit(data, offset);
    bool unitInserted = false;
    bool unitIntersects = false;
    unsigned intersecIdx = 0;
    unsigned bSize = _bData.size();
    for (unsigned idx = 0; idx < bSize; idx++) {
        if (unitIntersects) {
            if (_bData[idx].intersects(_bData[intersecIdx])) {
                // merge element in intersecIdx onto it
                _bData[idx] << _bData[intersecIdx];
                _bData.erase(_bData.begin() + intersecIdx);
                intersecIdx = --idx;
                bSize--;
            } else {
                break; // done :)
            }
        } else if (bufferUnit.offset() + bufferUnit.size() < _bData[idx].offset()) {  // check if we can insert before
            _bData.insert(_bData.begin() + idx, bufferUnit);
            unitInserted = true;
            break;
        } else if (bufferUnit.intersects(_bData[idx])) {
            unitIntersects = true;
            unitInserted = true;
            _bData[idx] << bufferUnit;
            intersecIdx = idx;
            continue;
        }
    }

    if (!unitInserted) {
        _bData.push_back(bufferUnit);
    }
    DBG_PRINTF("-D- bData size: %d\n", (int)_bData.size());

#ifdef _DEBUG_MODE
    std::vector<MBufferUnit>::iterator it = _bData.begin();
    for (; it != _bData.end(); it++) {
        DBG_PRINTF("-D- chunk : 0x%08x - 0x%08x (0x%08x)\n", it->offset(), it->size() + it->offset(), it->size());
    }
#endif
}
void MlargeBuffer::add(const u_int8_t *data, u_int32_t offset, u_int32_t size)
{
    std::vector<u_int8_t> dataVec(data, data + size);
    return add(dataVec, offset);
}

u_int8_t MlargeBuffer::operator[](const u_int32_t offset)
{
    u_int8_t data;
    get(&data, offset, 1);
    return data;
}
void MlargeBuffer::get(std::vector<u_int8_t>& data, u_int32_t offset, u_int32_t size)
{
    if (data.size() < size) {
        data.resize(size);
    }
    return get(&data[0], offset, size);
}

void MlargeBuffer::get(u_int8_t *data, u_int32_t offset, u_int32_t size)
{
    DBG_PRINTF("-D- get request on offset: 0x%08x with size 0x%x\n", offset, size);
    if (!data || size == 0) {
        return;
    }
    memset(data, _defaultValue, size);
    u_int8_t *ptr = data;
    for (std::vector<MBufferUnit>::iterator it = _bData.begin(); it != _bData.end(); it++) {
        if (offset < (it->offset() + it->size()) && (offset + size) > it->offset()) {
            // intersects with current MBufferUnit
            u_int32_t offsetInBuffer = ((long int)it->offset() - (long int)offset) < 0 ? 0 :  it->offset() - offset;
            u_int32_t copySize = MFT_MIN(offset + size,  it->offset() + it->size()) - MFT_MAX(offset, it->offset());
            u_int32_t offsetInData = ((long int)offset - (long int)it->offset()) < 0 ? 0 : offset - it->offset();
            DBG_PRINTF("-D- getting from chunk at offset 0x%08x , size: 0x%x\n",  it->offset(), (unsigned)it->size() );
            DBG_PRINTF("-D- integrating at buffer offset : 0x%08x size: 0x%x, offset in data: 0x%08x\n", offsetInBuffer, copySize, offsetInData);
            memcpy(ptr + offsetInBuffer, &(it->data())[0] + offsetInData, copySize);
        }
    }
    return;
}
