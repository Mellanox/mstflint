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
 * mlarge_buffer.h
 *
 *  Created on: Mar 9, 2016
 *      Author: adrianc
 */

#ifndef USER_MFT_UTILS_MLARGE_BUFFER_H_
#define USER_MFT_UTILS_MLARGE_BUFFER_H_

#include <vector>

#include <compatibility.h>

class MBufferUnit {
public:
    MBufferUnit(const std::vector<u_int8_t>& data, u_int32_t offset) : _data(data), _offset(offset) {}
    u_int32_t size() const {return (u_int32_t)_data.size();}
    u_int32_t offset() const {return _offset;}
    std::vector<u_int8_t>& data() { return _data; }
    u_int8_t& operator[](const u_int32_t idx) { return _data[idx]; }
    MBufferUnit& operator=(const MBufferUnit& other);
    bool intersects( const MBufferUnit& other) const;
private:
    std::vector<u_int8_t> _data;
    u_int32_t _offset;
};

MBufferUnit& operator<<(MBufferUnit& a, MBufferUnit& b);

/*
 * Large buffer with minimal memory footprint
 */
class MlargeBuffer {
public:
    MlargeBuffer(u_int8_t defaultVal = 0x0) : _defaultValue(defaultVal){}
    void add(const std::vector<u_int8_t>& data, u_int32_t offset);
    void add(const u_int8_t *data, u_int32_t offset, u_int32_t size);
    u_int8_t operator[](const u_int32_t offset);  // for read only
    void get(std::vector<u_int8_t>& data, u_int32_t offset, u_int32_t size);
    void get(std::vector<u_int8_t>& data, u_int32_t size) {return get(data, 0, size);}
    void get(u_int8_t *data, u_int32_t offset, u_int32_t size);
    void get(u_int8_t *data, u_int32_t size) {return get(data, 0, size);}
    void clear() {_bData.clear();}
private:
    u_int8_t _defaultValue;
    std::vector<MBufferUnit> _bData;
};

#endif /* USER_MFT_UTILS_MLARGE_BUFFER_H_ */
