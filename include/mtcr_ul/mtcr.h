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

#ifndef MTCR_H
#define MTCR_H


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include "mtcr_com_defs.h"
#include "mtcr_mf.h"
#if defined(MTCR_UL) && !defined(NO_INBAND)
#include <mtcr_ul/mtcr_ib.h>
#endif

#define SLV_ADDRS_NUM 128

typedef enum mtcr_access_method {
    MTCR_ACCESS_ERROR  = MST_ERROR,
    MTCR_ACCESS_MEMORY = MST_PCI,
    MTCR_ACCESS_CONFIG = MST_PCICONF,
    MTCR_ACCESS_INBAND = MST_IB
} mtcr_access_method_t;
/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4(mfile *mf, unsigned int offset, u_int32_t *value);

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4(mfile *mf, unsigned int offset, u_int32_t value);


int mread4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len);
int mwrite4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len);

int msw_reset(mfile *mf);
int mhca_reset(mfile *mf);

/*
 * Get list of MST (Mellanox Software Tools) devices.
 * Put all device names as null-terminated strings to buf.
 *
 * Return number of devices found or -1 if buf overflow
 */
int mdevices(char *buf, int len, int mask);


/*
 * Get list of MST (Mellanox Software Tools) devices info records.
 * Return a dynamic allocated array of dev_info records.
 * len will be updated to hold the array length
 *
 */
dev_info* mdevices_info(int mask, int *len);

/*
 *  * Get list of MST (Mellanox Software Tools) devices info records.
 *  * Return a dynamic allocated array of dev_info records.
 *  * len will be updated to hold the array length
 *  * Verbosity will decide whether to get all the Physical functions or not.
 */

dev_info* mdevices_info_v(int mask, int *len, int verbosity);

void mdevice_info_destroy(dev_info *dev_info, int len);
void mdevices_info_destroy(dev_info *dev_info, int len);

int mget_mdevs_type(mfile *mf, u_int32_t *mtype);

/*
 * Open Mellanox Software tools (mst) driver. Device type==INFINIHOST
 * Return valid mfile ptr or 0 on failure
 */
mfile* mopen(const char *name);

mfile* mopend(const char *name, DType dtype);

//mfile* mopen_fw_ctx(void *fw_cmd_context, void *fw_cmd_func, void *extra_data);

mfile* mopen_adv(const char *name, MType mtype);

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf);

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave);

int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags);

int maccess_reg_mad(mfile *mf, u_int8_t *data);

int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type);

int maccess_reg_cmdif(mfile *mf, reg_access_t reg_access, void *reg_data, u_int32_t cmd_type);

int maccess_reg(mfile     *mf,
                u_int16_t reg_id,
                maccess_reg_method_t reg_method,
                void *reg_data,
                u_int32_t reg_size,
                u_int32_t r_size_reg,   // used when sending via icmd interface (how much data should be read back to the user)
                u_int32_t w_size_reg,   // used when sending via icmd interface (how much data should be written to the scratchpad)
                                        // if you dont know what you are doing then r_size_reg = w_size_reg = your_register_size
                int       *reg_status);

int icmd_send_command(mfile *mf, int opcode, void *data, int data_size, int skip_write);

int icmd_clear_semaphore(mfile *mf);


int tools_cmdif_send_inline_cmd(mfile *mf, u_int64_t in_param, u_int64_t *out_param,
                                u_int32_t input_modifier, u_int16_t opcode, u_int8_t opcode_modifier);

int tools_cmdif_send_mbox_command(mfile *mf, u_int32_t input_modifier, u_int16_t opcode, u_int8_t opcode_modifier,
                                  int data_offs_in_mbox, void *data, int data_size, int skip_write);

int tools_cmdif_unlock_semaphore(mfile *mf);


int mget_max_reg_size(mfile *mf, maccess_reg_method_t reg_method);
int supports_reg_access_gmp(mfile *mf, maccess_reg_method_t reg_method);

const char* m_err2str(MError status);

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len);
int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len);

int mget_vsec_supp(mfile *mf);

int mget_addr_space(mfile *mf);
int mset_addr_space(mfile *mf, int space);

int mclear_pci_semaphore(const char *name);

int mvpd_read4(mfile *mf, unsigned int offset, u_int8_t value[4]);

int mvpd_write4(mfile *mf, unsigned int offset, u_int8_t value[4]);

MTCR_API int MWRITE4_SEMAPHORE(mfile* mf, int offset, int value);

MTCR_API int MREAD4_SEMAPHORE(mfile* mf, int offset, u_int32_t* ptr);

int allocate_kernel_memory_page(mfile *mf, mtcr_alloc_page* user_alloc_page);

void set_increase_poll_time(int new_value);

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "mlx4_0"
#define DEV_MST_EXAMPLE2 "03:00.0"

#endif
