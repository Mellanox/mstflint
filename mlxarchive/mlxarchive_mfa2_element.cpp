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
 * mlxarchive_mfa2_element.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include "mlxarchive_mfa2_element.h"

using namespace mfa2;

CommonHeader Element::buildCommonHeader(u_int8_t version, MFA2Type type,
        u_int32_t length)
{
    CommonHeader commonHeader(version, type, length);
    return commonHeader;
}

Element::Element(u_int8_t version, MFA2Type type, u_int32_t length) :
        _commonHeader(buildCommonHeader(version, type, length))
{

}

