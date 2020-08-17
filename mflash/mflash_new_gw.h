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

/*
 * mflash_gw.h
 *
 *  Created on: Jul 8, 2020
 *      Author: edwardg
 */


#ifndef _MFLASH_NEW_GW_H_
#define _MFLASH_NEW_GW_H_
#include "mflash_pack_layer.h"
// ConnectX SPI interface:
int new_gw_st_spi_erase_sect(mflash *mfl, u_int32_t addr);
int new_gw_int_spi_get_status_data(mflash *mfl, u_int8_t op_type, u_int32_t *status, u_int8_t data_num);
int new_gw_st_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, u_int8_t is_first, u_int8_t is_last, u_int32_t total_size);
int new_gw_sst_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data);
int new_gw_st_spi_block_read_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, u_int8_t is_first, u_int8_t is_last, bool verbose);
int new_gw_spi_write_status_reg(mflash *mfl, u_int32_t status_reg, u_int8_t write_cmd, u_int8_t bytes_num);
#endif
