
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
 * mlxarchive_mfa2_common_header.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_COMMON_HEADER_H_
#define MLXARCHIVE_MFA2_COMMON_HEADER_H_

#include <string>
#include <vector>

#include <compatibility.h>

#include "mlxarchive_mfa2_utils.h"
#include "mfa2_buff.h"

using namespace std;

namespace mfa2 {

class CommonHeader {

private:
    u_int8_t    _version;
    MFA2Type    _type;
    u_int16_t   _length;

public:
    CommonHeader(u_int8_t version, MFA2Type type, u_int16_t length);

    //inline void setLength(u_int16_t length) { _length = length; }
    void pack(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);
    const u_int16_t & getLength() const {return _length;}
};

}
#endif
