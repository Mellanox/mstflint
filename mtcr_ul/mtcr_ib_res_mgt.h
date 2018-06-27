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
 *
 */

#ifndef _MTCR_IB_RES_MGT_H_
#define _MTCR_IB_RES_MGT_H_

#include <mtcr.h>

typedef enum {
    SMP_SEM_LOCK = 1,
    SMP_SEM_EXTEND,
    SMP_SEM_RELEASE
} sem_op_t;

typedef enum {
    SEM_LOCK_GET = 0x0,
    SEM_LOCK_SET = 0x1
} sem_lock_method_t;

MTCR_API int mib_semaphore_lock_vs_mad(
    mfile *mf,
    sem_op_t op,
    u_int32_t sem_addr,
    u_int32_t lock_key,
    u_int32_t *res,
    int *is_leaseable,
    u_int8_t *lease_time_exp,
    sem_lock_method_t method);

MTCR_API int mib_semaphore_lock_is_supported(mfile *mf);

#endif
