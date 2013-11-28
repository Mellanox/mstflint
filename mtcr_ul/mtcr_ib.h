
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

/*
 *
 *  mtcr_ib.h - Mellanox Software tools (mst) IB related driver definitions
 *
 */

#ifndef _MTCR_IB_H
#define _MTCR_IB_H

MTCR_API int mib_open(const char *name, mfile *mf, int mad_init);
MTCR_API int mib_close(mfile *mf);
MTCR_API int mib_read4(mfile *mf, unsigned int offset, u_int32_t *value);
MTCR_API int mib_write4(mfile *mf, unsigned int offset, u_int32_t value);
MTCR_API int mib_read64(mfile *mf, unsigned int offset, void *data, int length);
MTCR_API int mib_write64(mfile *mf, unsigned int offset, void *data, int length);

MTCR_API int mib_readblock(mfile *mf, unsigned int offset, u_int32_t *data, int length);
MTCR_API int mib_writeblock(mfile *mf, unsigned int offset, u_int32_t *data, int length);

MTCR_API int mib_swreset(mfile *mf);
MTCR_API int mib_get_chunk_size(mfile *mf);
MTCR_API int mib_acces_reg_mad(mfile *mf, u_int8_t *data);


#endif
