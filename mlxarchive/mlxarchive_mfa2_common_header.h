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
};

}
#endif
