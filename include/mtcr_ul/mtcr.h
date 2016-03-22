/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright(C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#ifndef MTCR_H
#define MTCR_H


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include "mtcr_com_defs.h"

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


int mread4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);
int mwrite4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);

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
dev_info* mdevices_info(int mask, int* len);

void mdevice_info_destroy(dev_info* dev_info, int len);
void mdevices_info_destroy(dev_info* dev_info, int len);

int mget_mdevs_type(mfile *mf, u_int32_t *mtype);

/*
 * Open Mellanox Software tools (mst) driver. Device type==INFINIHOST
 * Return valid mfile ptr or 0 on failure
 */
mfile *mopen(const char *name);

mfile *mopend(const char *name, int type);

mfile *mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func, void* extra_data);

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
                u_int16_t  reg_id,
                maccess_reg_method_t reg_method,
                void*      reg_data,
                u_int32_t  reg_size,
                u_int32_t	r_size_reg, // used when sending via icmd interface (how much data should be read back to the user)
                u_int32_t	w_size_reg, // used when sending via icmd interface (how much data should be written to the scratchpad)
                         	 	 	    // if you dont know what you are doing then r_size_reg = w_size_reg = your_register_size
                int       *reg_status);

int icmd_send_command(mfile *mf, int opcode, void* data, int data_size, int skip_write);

int icmd_clear_semaphore(mfile *mf);


int tools_cmdif_send_inline_cmd(mfile* mf, u_int64_t in_param, u_int64_t* out_param,
                                u_int32_t input_modifier, u_int16_t opcode, u_int8_t  opcode_modifier);

int tools_cmdif_send_mbox_command(mfile* mf, u_int32_t input_modifier, u_int16_t opcode, u_int8_t  opcode_modifier,
                                  int data_offs_in_mbox, void* data, int data_size, int skip_write);

int tools_cmdif_unlock_semaphore(mfile *mf);


int mget_max_reg_size(mfile *mf);

const char* m_err2str(MError status);

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);
int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);

int mget_vsec_supp(mfile* mf);

int mget_addr_space(mfile* mf);
int mset_addr_space(mfile* mf, int space);

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "mlx4_0"
#define DEV_MST_EXAMPLE2 "03:00.0"

#endif
