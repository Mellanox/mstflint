/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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
 * pldm_utils.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#ifndef _MFA2_BUFF_H_
#define _MFA2_BUFF_H_
#include <string>
#include "common/compatibility.h"

class Mfa2Buffer {
public:
    Mfa2Buffer();
    virtual ~Mfa2Buffer();

    bool loadFile(const std::string& fname);

    void read(u_int8_t & val);
    void read(u_int16_t & val);
    void read(u_int32_t & val);
    void read(std::string& str, size_t str_size);
    void read(u_int8_t *arr, size_t arr_size);

    int seek(long offset, int whence);
    long tell();
    void rewind();
    u_int8_t* getBuffer() const {
        return m_buff;
    }

    long getSize() const {
        return m_size;
    }

private:
    u_int8_t * m_buff;
    long m_pos;
    long m_size;
};

#endif /* _MFA2_BUFF_H_ */

