/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef __MTCR_MF__
#define __MTCR_MF__
#include "mtcr_com_defs.h"
#ifdef __FreeBSD__
#include <sys/pciio.h>
#endif

struct mft_core_wrapper
{
    void* config_space_access;
    void* reg_access;
    void* reset_access;
};

#ifdef __FreeBSD__
struct page_list_fbsd
{
    // User space buffer page aligned.
    char* page_list[MAX_PAGES_SIZE];
    int page_amount;
};
#endif

/*  All fields in follow structure are not supposed to be used */
/*  or modified by user programs. Except i2c_slave that may be */
/*  modified before each access to target I2C slave address */
struct mfile_t
{
    MType tp; /*  type of driver */
    MType orig_tp;
    MType res_tp;         /*  Will be used with HCR if need */
    DType dtype;          /*  target device to access to */
    DType itype;          /*  interface device to access via */
    u_int32_t device_hw_id;
    int is_i2cm;          /*  use device as I2C master */
    int is_vm;            /*  if the machine is VM    */
    int cr_access;        /* If cr access is allowed in MLNXOS devices */
    cables_info ext_info; /*keeps info for calculate the correct slave address (0x50 + offset) */
    unsigned char i2c_slave;
    int gpio_en;
    io_region* iorw_regions; /* For LPC devices */
    int regions_num;
    char* dev_name;
    int fd;
    int res_fd;          /*  Will be used with HCR if need*/
    int sock;            /*  in not -1 - remote interface */
    int is_mtserver_req; // request came from mtServer - means came from remote client
    void* bar_virtual_addr;
    unsigned int map_size;
    unsigned int bar0_gw_offset; // for MST_BAR0_GW_PCI devices, offset from BAR0 - gateway - for R/W operations
    int file_lock_descriptor; // file descriptor to the lock file aka semaphore in order to protect parallel read/write
                              // GW operations
    unsigned long long start_idx;
    /************************ FPGA DDR3 *********************************/
    void* ddr3_ptr;
    unsigned long long ddr3_start_idx;
    unsigned int ddr3_map_size;
    /********************************************************************/
    MIB_Private mib; /*  Data for IB interface (if relevant) */
    void* ctx;
    void* fallback_mf;
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

    // for ICMD access
    icmd_params icmd;
    // for UEFI
    ctx_params context;
    // for mst driver compatibility
    int old_mst;
    unsigned short mst_version_major;
    unsigned int mst_version_minor;
    int vsec_supp;
    mtcr_status_e icmd_support;
    unsigned int vsec_addr;
    u_int32_t vsec_cap_mask;
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
    unsigned int linkx_chip_devid;
    void* cable_chip_ctx; // TODO change the name
    f_mpci_change mpci_change;
    // Amos gear-box
    gearbox_info gb_info;
#ifdef __FreeBSD__
    struct pcisel sel;
    unsigned int vpd_cap_addr;
    int wo_addr;
    int connectx_flush;
    int fdlock;
    struct page_list_fbsd user_page_list;
    void* ptr;
#else
    struct page_list user_page_list;
#endif

    // For dma purpose
    void* dma_props;

    // MFT core wrapper objects.
    struct mft_core_wrapper mft_core_object;
    char* fwctl_env_var_debug;
    int is_remote;
    int is_zombiefish;
    int vsc_recovery_space_flash_control_vld;
};

#endif
