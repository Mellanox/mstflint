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
 *
 *  mtcr_ib.h - Mellanox Software tools (mst) IB related driver definitions
 *
 */

#ifndef _MTCR_IB_H
#define _MTCR_IB_H

#ifdef __WIN__
    #include <mtcr.h>
#endif

int mib_open(const char *name, mfile *mf, int mad_init);
int mib_close(mfile *mf);
int mib_read4(mfile *mf, unsigned int offset, u_int32_t *value);
int mib_write4(mfile *mf, unsigned int offset, u_int32_t value);
int mib_read64(mfile *mf, unsigned int offset, void *data, int length);
int mib_write64(mfile *mf, unsigned int offset, void *data, int length);

int mib_readblock(mfile *mf, unsigned int offset, u_int32_t *data, int length);
int mib_writeblock(mfile *mf, unsigned int offset, u_int32_t *data, int length);
int mib_swreset(mfile *mf);
int mib_get_chunk_size(mfile *mf);
int mib_acces_reg_mad(mfile *mf, u_int8_t *data);

int mib_smp_set(mfile* mf, u_int8_t* data, u_int16_t attr_id, u_int32_t attr_mod);
int mib_smp_get(mfile* mf, u_int8_t* data, u_int16_t attr_id, u_int32_t attr_mod);

#endif
