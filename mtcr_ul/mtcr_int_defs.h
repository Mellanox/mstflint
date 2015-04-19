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

#ifndef MTCR_INT_DEFS
#define MTCR_INT_DEFS

#include <mtcr.h>

typedef int (*f_mread4)        (mfile *mf, unsigned int offset, u_int32_t *value);
typedef int (*f_mwrite4)       (mfile *mf, unsigned int offset, u_int32_t  value);
typedef int (*f_mread4_block)  (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);
typedef int (*f_mwrite4_block) (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);
typedef int (*f_maccess_reg)   (mfile *mf, u_int8_t *data);
typedef int (*f_mclose)        (mfile* mf);


typedef struct icmd_params_t {
    int icmd_opened;
    int took_semaphore;
    int ctrl_addr;
    int cmd_addr;
    u_int32_t max_cmd_size;
    int semaphore_addr;
    int static_cfg_not_done_addr;
    int static_cfg_not_done_offs;
}icmd_params;

typedef struct tools_hcr_params_t {
    int supp_cr_mbox; // 1: mbox supported , -1: mbox not supported
}tools_hcr_params;

typedef struct access_reg_params_t {
    int max_reg_size;
}access_reg_params;

struct mfile_t {
    char*            dev_name;
    void            *ctx; // Access method context
    int              access_type;
    int              fdlock;

    f_mread4         mread4;
    f_mwrite4        mwrite4;
    f_mread4_block   mread4_block;
    f_mwrite4_block  mwrite4_block;
    f_maccess_reg    maccess_reg;
    f_mclose         mclose;

    /******** RESERVED FIELDS FOR SWITCHING METHOD IF NEEDED ******/
    void            *res_ctx; // Reserved access method context
    int              res_access_type;
    int              res_fdlock;
    f_mread4         res_mread4;
    f_mwrite4        res_mwrite4;
    f_mread4_block   res_mread4_block;
    f_mwrite4_block  res_mwrite4_block;
    /*************************************************************/

    //for ICMD access
    icmd_params icmd;
    // for vendor specific pci capability
    int vsec_supp;
    u_int32_t vsec_addr;
    int address_space;
    // for tools HCR access
    tools_hcr_params hcr_params;
    // for sending access registers
    access_reg_params acc_reg_params;
};
#endif



