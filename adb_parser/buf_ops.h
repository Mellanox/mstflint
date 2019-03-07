
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

#ifndef BIT_OPS_H
#define BIT_OPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <common/compatibility.h>
#include <common/bit_slice.h>
#include <common/tools_utils.h>

/************************************/
/************************************/
/************************************/
void print_raw(FILE *file, void *buff, int buff_len);
u_int64_t pop_from_buf(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size);
void push_to_buf(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value);
#endif // BIT_OPS_H
