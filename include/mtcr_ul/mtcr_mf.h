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

#ifndef __MTCR_MF__
#define __MTCR_MF__

typedef struct icmd_params_t {
        int icmd_opened;
        int took_semaphore;
        int ctrl_addr;
        int cmd_addr;
        u_int32_t max_cmd_size;
        int semaphore_addr;
        int static_cfg_not_done_addr;
        int static_cfg_not_done_offs;
        u_int32_t lock_key;
        int ib_semaphore_lock_supported;
} icmd_params;

typedef struct ctx_params_t {
        void *fw_cmd_context;
        void *fw_cmd_func;
} ctx_params;

typedef struct io_region_t {
        unsigned int start;
        unsigned int end;
} io_region;

typedef struct tools_hcr_params_t {
        int supp_cr_mbox; // 1: mbox supported , -1: mbox not supported
} tools_hcr_params;

typedef struct access_reg_params_t {
        int max_reg_size;
} access_reg_params;

typedef void (*f_mpci_change)        (mfile *mf);

/*  All fields in follow structure are not supposed to be used */
/*  or modified by user programs. Except i2c_slave that may be */
/*  modified before each access to target I2C slave address */
struct mfile_t {
        MType tp; /*  type of driver */
        MType res_tp; /*  Will be used with HCR if need */
        DType dtype; /*  target device to access to */
        DType itype; /*  interface device to access via */
        int is_i2cm; /*  use device as I2C master */
        int is_vm; /*  if the machine is VM    */
        int cr_access; /* If cr access is allowed in MLNXOS devices */
        unsigned char i2c_slave;
        int           gpio_en;
        io_region* iorw_regions; /* For LPC devices */
        int regions_num;
        char* dev_name;
        int fd;
        int res_fd; /*  Will be used with HCR if need*/
        int sock; /*  in not -1 - remote interface */
        void *ptr;
        unsigned int map_size;
        unsigned long long start_idx;
        /************************ FPGA DDR3 *********************************/
        void *ddr3_ptr;
        unsigned long long ddr3_start_idx;
        unsigned int ddr3_map_size;
        /********************************************************************/
        MIB_Private mib; /*  Data for IB interface (if relevant) */
        void *ctx;
        unsigned int i2c_RESERVED; /*  Reserved for internal usage (i2c internal) */
        int i2c_smbus;
        enum Mdevs_t flags;
        u_int32_t connectx_wa_slot; /* apply connectx cr write workaround */
        int connectx_wa_last_op_write;
        u_int32_t connectx_wa_stat;
        u_int64_t connectx_wa_max_retries;
        u_int64_t connectx_wa_num_of_writes;
        u_int64_t connectx_wa_num_of_retry_writes;
        int server_ver_major;
        int server_ver_minor;
        unsigned int proto_type;
        dev_info* dinfo;

        //for ICMD access
        icmd_params icmd;
        // for UEFI
        ctx_params context;
        // for new pci capability
        int old_mst;
        int vsec_supp;
        unsigned int vsec_addr;
        int address_space;
        int multifunction;
        // for tools HCR access
        tools_hcr_params hcr_params;
        // for sending access registers
        access_reg_params acc_reg_params;
        // UL
        void* ul_ctx;
        // Dynamic libs Ctx
        void* dl_context;
        // Cables CTX
        int is_cable;
        void* cable_ctx;
        f_mpci_change mpci_change;
};

#endif
