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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "tools_time.h"



void tt_get_time(tt_ctx_t* tt)
{
    if (!tt) {
        return;
    }
    time(&(tt->now));
    return;
}

double tt_diff_in_ms(tt_ctx_t t1, tt_ctx_t t2)
{
    return difftime(t2.now, t1.now) * 1000;
}



