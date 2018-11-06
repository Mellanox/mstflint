/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
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
