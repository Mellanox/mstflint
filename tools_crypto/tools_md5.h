
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
 */

#ifndef TOOLS_MD5_H
#define TOOLS_MD5_H

#ifdef __cplusplus
extern "C" {
#endif

#include <common/compatibility.h>
u_int8_t *tools_md5(const u_int8_t* src, u_int32_t src_len, u_int8_t dst[16]);

#ifdef __cplusplus
}
#endif

#endif // TOOLS_MD5_H
