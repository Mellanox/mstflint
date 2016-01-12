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

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

typedef struct tt_ctx {
    time_t now;
} tt_ctx_t;

// update context with the current time
void tt_get_time(tt_ctx_t* tt);
// get diff in ms between the time t1 was created and t2
double tt_diff_in_ms(tt_ctx_t t1, tt_ctx_t t2);

#ifdef __cplusplus
}
#endif
