/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MTCR_INT_DEFS
#define MTCR_INT_DEFS

#include "mtcr_com_defs.h"

typedef int (*f_mread4)(mfile* mf, unsigned int offset, u_int32_t* value);
typedef int (*f_mwrite4)(mfile* mf, unsigned int offset, u_int32_t value);
typedef int (*f_mread4_block)(mfile* mf, unsigned int offset, void* data, int byte_len);
typedef int (*f_mwrite4_block)(mfile* mf, unsigned int offset, void* data, int byte_len);
typedef int (*f_maccess_reg)(mfile* mf, u_int8_t* data);
typedef int (*f_mclose)(mfile* mf);

typedef struct ul_ctx
{
    int fdlock;
    /* Hermon WA */
    int connectx_flush; /* For ConnectX A0 */
    int need_flush;     /* For ConnectX A0 */

    f_mread4 mread4;
    f_mwrite4 mwrite4;
    f_mread4_block mread4_block;
    f_mwrite4_block mwrite4_block;
    f_maccess_reg maccess_reg;
    f_mclose mclose;
    int wo_addr; /* Is write Only Addr GW */
    /******** RESERVED FIELDS FOR SWITCHING METHOD IF NEEDED ******/
    int res_access_type;
    int res_fdlock;
    f_mread4 res_mread4;
    f_mwrite4 res_mwrite4;
    f_mread4_block res_mread4_block;
    f_mwrite4_block res_mwrite4_block;
    /*************************************************************/
    int via_driver;
} ul_ctx_t;
#endif
