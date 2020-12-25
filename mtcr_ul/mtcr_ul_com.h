/*
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *
 * mtcr_ul_com.h
 *
 *  Created on: Feb 16, 2016
 *      Author: adham
 */

#ifndef USER_MTCR_MTCR_UL_COM_H_
#define USER_MTCR_MTCR_UL_COM_H_

#include "mtcr_com_defs.h"
#include "mtcr_mf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4_ul(mfile *mf, unsigned int offset, u_int32_t *value);

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4_ul(mfile *mf, unsigned int offset, u_int32_t value);


int mread4_block_ul(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len);
int mwrite4_block_ul(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len);

int msw_reset_ul(mfile *mf);
int mhca_reset_ul(mfile *mf);

/*
 * Get list of MST_ul(Mellanox Software Tools) devices.
 * Put all device names as null-terminated strings to buf.
 *
 * Return number of devices found or -1 if buf overflow
 */
int mdevices_ul(char *buf, int len, int mask);

/*
 * Get list of MST_ul(Mellanox Software Tools) devices.
 * Put all device names as null-terminated strings to buf.
 *
 * Return number of devices found or -1 if buf overflow
 */
int mdevices_v_ul(char *buf, int len, int mask, int verbosity);

/*
 * Get list of MST_ul(Mellanox Software Tools) devices info records.
 * Return a dynamic allocated array of dev_info records.
 * len will be updated to hold the array length
 *
 */
dev_info* mdevices_info_ul(int mask, int *len);

/*
 *  * Get list of MST (Mellanox Software Tools) devices info records.
 *  * Return a dynamic allocated array of dev_info records.
 *  * len will be updated to hold the array length
 *  * Verbosity will decide whether to get all the Physical functions or not.
 */
dev_info* mdevices_info_v_ul(int mask, int *len, int verbosity);

/*
 * Open Mellanox Software tools_ul(mst) driver. Device type==INFINIHOST
 * Return valid void ptr or 0 on failure
 */
mfile* mopen_ul(const char *name);

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose_ul(mfile *mf);

int maccess_reg_mad_ul(mfile *mf, u_int8_t *data);

int maccess_reg_ul(mfile *mf,
                   u_int16_t reg_id,
                   maccess_reg_method_t reg_method,
                   void *reg_data,
                   u_int32_t reg_size,
                   u_int32_t r_size_reg, // used when sending via icmd interface_ul(how much data should be read back to the user)
                   u_int32_t w_size_reg, // used when sending via icmd interface_ul(how much data should be written to the scratchpad)
                                         // if you dont know what you are doing then r_size_reg = w_size_reg = your_register_size
                   int       *reg_status);



int tools_cmdif_send_inline_cmd_ul(mfile *mf, u_int64_t in_param, u_int64_t *out_param,
                                   u_int32_t input_modifier, u_int16_t opcode, u_int8_t opcode_modifier);

int tools_cmdif_send_mbox_command_ul(mfile *mf, u_int32_t input_modifier, u_int16_t opcode, u_int8_t opcode_modifier,
                                     int data_offs_in_mbox, void *data, int data_size, int skip_write);

int tools_cmdif_unlock_semaphore_ul(mfile *mf);


int mget_max_reg_size_ul(mfile *mf, maccess_reg_method_t reg_method);
int supports_reg_access_gmp_ul(mfile *mf, maccess_reg_method_t reg_method);

int mread_buffer_ul(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len);
int mwrite_buffer_ul(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len);

int mclear_pci_semaphore_ul(const char *name);

int mvpd_read4_ul(mfile *mf, unsigned int offset, u_int8_t value[4]);

int space_to_cap_offset(int space);

#ifdef __cplusplus
}
#endif

#endif /* USER_MTCR_MTCR_UL_COM_H_ */
