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

#ifdef ESS
#define MREAD4(offs, val)       \
    do                          \
    {                           \
        *val = READ_WORD(offs); \
    } while (0)
#define MWRITE4(offs, val)     \
    do                         \
    {                          \
        WRITE_WORD(offs, val); \
    } while (0)
#else
#define MREAD4(offs, val)                                                                                  \
    do                                                                                                     \
    {                                                                                                      \
        if (mread4(mfl->mf, offs, val) != 4)                                                               \
        {                                                                                                  \
            /*fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), \
             * (u_int32_t)errno);*/                                                                        \
            return 2;                                                                                      \
        } /*printf("-D- %s:%d mread4: offs = %#x, val = %#x\n", __FUNCTION__, __LINE__, offs, val);*/      \
    } while (0)

#define MWRITE4(offs, val)                                                                                           \
    do                                                                                                               \
    {                                                                                                                \
        if (mwrite4(mfl->mf, offs, val) != 4)                                                                        \
        {                                                                                                            \
            /*fprintf(stderr, "-E- Cr write (0x%08x, 0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), (u_int32_t)(val), \
             * strerror(errno), (u_int32_t)errno);*/                                                                 \
            return 2;                                                                                                \
        } /*printf("-D- %s:%d mwrite4: offs = %#x, val = %#x\n",   __FUNCTION__, __LINE__, offs, val);*/             \
    } while (0)
#endif

enum FlashConstant
{
    // All time values are in usecs
    WRITE_BLOCK_INIT_DELAY = 10,
    WRITE_ADDITIONAL_BYTE_DELAY = 1,
    WRITE_BLOCK_RETRY_DELAY = 10,
    WRITE_BLOCK_RETRIES = 30000,

    ERASE_SUBSECTOR_INIT_DELAY = 20000,
    ERASE_SUBSECTOR_RETRY_DELAY = 300,
    ERASE_SUBSECTOR_RETRIES = 10000,

    FLASH_CMD_CNT = 5000, // Number of reads till flash cmd is zeroed

    GPIO_SEM_TRIES = 1024, // Number of tries to obtain a GPIO sem.

    MAX_WRITE_BUFFER_SIZE = 256, // Max buffer size for buffer write devices

    WRITE_STATUS_REGISTER_DELAY_CYPRESS = 750,
    WRITE_STATUS_REGISTER_DELAY_MICRON = 1000,
    WRITE_STATUS_REGISTER_DELAY_MIN = 40,

    DUMMY_CYCLES_OFFSET_ST = 12,
    DUMMY_CYCLES_OFFSET_MACRONIX_MX25UXXX = 5,
    DUMMY_CYCLES_OFFSET_MX25U51245G = 6,
    DUMMY_CYCLES_BIT_LEN_MACRONIX_MX25UXXX = 2,

    QUAD_EN_OFFSET_WINBOND_CYPRESS = 1,
    QUAD_EN_OFFSET_MICRON = 3,
    QUAD_EN_OFFSET_ISSI_MACRONIX = 6,
    QUAD_EN_OFFSET_GIGABYTE = 1,
    COMPLEMENT_PROTECT_OFFSET_WINBOND_MACRONIX  = 6,
    DRIVER_STRENGTH_OFFSET_MICRON = 6,
    DRIVER_STRENGTH_OFFSET_MACRONIX_MX25UXXX = 0,
    DRIVER_STRENGTH_BIT_LEN_MICRON = 3,
    DRIVER_STRENGTH_BIT_LEN_MACRONIX = 3,
    DRIVER_STRENGTH_OFFSET_WINBOND = 5,
    DRIVER_STRENGTH_BIT_LEN_WINBOND = 2,
    DRIVER_STRENGTH_VAL_100_WINBOND = 0,
    DRIVER_STRENGTH_VAL_75_WINBOND = 1,
    DRIVER_STRENGTH_VAL_50_WINBOND = 2,
    DRIVER_STRENGTH_VAL_25_WINBOND = 3,
    DRIVER_STRENGTH_VAL_90_MICRON = 1,
    DRIVER_STRENGTH_VAL_45_MICRON = 3,
    DRIVER_STRENGTH_VAL_30_MICRON = 7,
    DRIVER_STRENGTH_VAL_20_MICRON = 5,
     DRIVER_STRENGTH_BIT_LEN_ISSI = 3,
    DRIVER_STRENGTH_OFFSET_ISSI = 5,
    DRIVER_STRENGTH_VAL_15_ISSI = 6,
    DRIVER_STRENGTH_VAL_20_ISSI = 5,
    DRIVER_STRENGTH_VAL_30_ISSI = 7,
    DRIVER_STRENGTH_VAL_45_ISSI = 3,
    DRIVER_STRENGTH_VAL_60_ISSI = 2,
    DRIVER_STRENGTH_VAL_90_ISSI = 1,
    DRIVER_STRENGTH_VAL_120_MACRONIX_MX25K16XXX = 0,
    DRIVER_STRENGTH_VAL_100_MACRONIX_MX25K16XXX = 1,
    DRIVER_STRENGTH_VAL_85_MACRONIX_MX25K16XXX = 2,
    DRIVER_STRENGTH_VAL_50_MACRONIX_MX25K16XXX = 3,
    DRIVER_STRENGTH_VAL_146_MACRONIX_MX25UXXX = 0,
    DRIVER_STRENGTH_VAL_76_MACRONIX_MX25UXXX = 1,
    DRIVER_STRENGTH_VAL_52_MACRONIX_MX25UXXX = 2,
    DRIVER_STRENGTH_VAL_41_MACRONIX_MX25UXXX = 3,
    DRIVER_STRENGTH_VAL_34_MACRONIX_MX25UXXX = 4,
    DRIVER_STRENGTH_VAL_30_MACRONIX_MX25UXXX = 5,
    DRIVER_STRENGTH_VAL_26_MACRONIX_MX25UXXX = 6,
    DRIVER_STRENGTH_VAL_24_MACRONIX_MX25UXXX = 7,
    DRIVER_STRENGTH_BIT_LEN_MACRONIX_MX25K16XXX = 2,
    DRIVER_STRENGTH_OFFSET_MACRONIX_MX25K16XXX = 5,
    TB_OFFSET_MACRONIX = 3,
    SEC_OFFSET = 6,
    TB_OFFSET = 5,
    TB_OFFSET_ISSI = 1,
    TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256 = 6,
    BP_OFFSET = 2,
    BP_4TH_BIT_OFFSET_MICRON = 6,
    SRWD_OFFSET_ISSI = 7,
    SRP_OFFSET_WINBOND = 7,
    BP_SIZE = 3,
    PROTECT_BITS_SIZE = 5
};

int check_access_type(mflash* mfl);
int sx_get_flash_info_by_type(mflash* mfl, flash_info_t* type_index, int* log2size, u_int8_t* no_flash);
int sx_block_read_by_type(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data);
int sx_block_write_by_type(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data);
int sx_flash_lock_by_type(mflash* mfl, int lock_state);
int sx_erase_sect_by_type(mflash* mfl, u_int32_t addr, u_int32_t erase_size);
int mf_update_boot_addr_by_type(mflash* mfl, u_int32_t boot_addr);
int mfl_com_lock(mflash* mfl);
flash_access_commands_t gen_4byte_address_access_commands();
flash_access_commands_t gen_3byte_address_access_commands();
int release_semaphore(mflash* mfl, int ignore_writer_lock);
int sx_set_quad_en(mflash* mfl, u_int8_t quad_en);
int sx_get_quad_en(mflash* mfl, u_int8_t* quad_en);
int sx_set_driver_strength(mflash* mfl, u_int8_t driver_strength);
int sx_get_driver_strength(mflash* mfl, u_int8_t* driver_strength);
int sx_set_write_protect(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info);
int sx_get_write_protect(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info);
uint8_t sx_get_bp_val(mflash* mfl, write_protect_info_t* protect_info);
int sx_set_dummy_cycles(mflash* mfl, u_int8_t num_of_cycles);
int sx_get_dummy_cycles(mflash* mfl, u_int8_t* num_of_cycles);
int gw_wait_ready(mflash* mfl, const char* msg);

#endif /* MFLASH_ACCESS_LAYER_H_ */
