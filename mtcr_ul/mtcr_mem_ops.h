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

#include "mtcr.h"

typedef enum {
    MEM_ICMD,
    MEM_END
} mem_type_t;

typedef struct {
    unsigned long long int dma_pa;
    unsigned int mem_size;
} mem_props_t;

void init_mem_ops(mfile *mf);

void close_mem_ops(mfile *mf);

int mtcr_memaccess(mfile* mf, unsigned int offset, unsigned int size, unsigned char *data, int rw, mem_type_t type);

int get_mem_props(mfile *mf, mem_type_t type, mem_props_t *props);

