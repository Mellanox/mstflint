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
 * mflash_inband.h
 *
 *  Created on: Jul 6, 2011
 *      Author: mohammad
 */

#ifndef MFLASH_ACCESS_LAYER_H_
#define MFLASH_ACCESS_LAYER_H_


#include <compatibility.h>

#include "mflash_common_structs.h"
#define MAX_FLASH_PROG_SEM_RETRY_CNT 40

int sx_get_flash_info_by_type(mflash *mfl, flash_info_t *type_index, int *log2size, u_int8_t *no_flash);
int sx_block_read_by_type(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data);
int sx_block_write_by_type(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data);
int sx_flash_lock_by_type(mflash *mfl, int lock_state);
int sx_erase_sect_by_type(mflash *mfl, u_int32_t addr, u_int32_t erase_size);
int mf_update_boot_addr_by_type(mflash *mfl, u_int32_t boot_addr);
int     sx_set_quad_en(mflash *mfl, u_int8_t quad_en);
int     sx_get_quad_en(mflash *mfl, u_int8_t *quad_en);
int     sx_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);
int     sx_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);
int     sx_set_dummy_cycles(mflash *mfl, u_int8_t num_of_cycles);
int     sx_get_dummy_cycles(mflash *mfl, u_int8_t *num_of_cycles);


#endif /* MFLASH_ACCESS_LAYER_H_ */
