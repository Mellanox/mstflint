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

#ifdef ESS
#define MREAD4(offs, val)  do {*val = READ_WORD(offs);} while (0)
#define MWRITE4(offs, val) do {WRITE_WORD(offs, val);} while (0)
#else
#define MREAD4(offs, val)  do { if (mread4(mfl->mf, offs, val) != 4) { \
/*fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), (u_int32_t)errno);*/ \
                                    return 2; } /*printf("-D- %s:%d mread4: offs = %#x, val = %#x\n", __FUNCTION__, __LINE__, offs, val);*/ \
} while (0)

#define MWRITE4(offs, val) do { if (mwrite4(mfl->mf, offs, val) != 4) { \
/*fprintf(stderr, "-E- Cr write (0x%08x, 0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), (u_int32_t)(val), strerror(errno), (u_int32_t)errno);*/ \
                                    return 2; } /*printf("-D- %s:%d mwrite4: offs = %#x, val = %#x\n",   __FUNCTION__, __LINE__, offs, val);*/ \
} while (0)
#endif

enum FlashConstant {
    // All time values are in usecs
    WRITE_BLOCK_INIT_DELAY = 10,
    WRITE_ADDITIONAL_BYTE_DELAY = 1,
    WRITE_BLOCK_RETRY_DELAY = 10,
    WRITE_BLOCK_RETRIES = 30000,

    ERASE_SUBSECTOR_INIT_DELAY = 20000,
    ERASE_SUBSECTOR_RETRY_DELAY = 300,
    ERASE_SUBSECTOR_RETRIES = 10000,

    FLASH_CMD_CNT = 5000,      // Number of reads till flash cmd is zeroed

    GPIO_SEM_TRIES = 1024,     // Number of tries to obtain a GPIO sem.

    MAX_WRITE_BUFFER_SIZE = 256, // Max buffer size for buffer write devices

    WRITE_STATUS_REGISTER_DELAY_CYPRESS = 750,
    WRITE_STATUS_REGISTER_DELAY_MICRON = 1000,
    WRITE_STATUS_REGISTER_DELAY_MIN = 40,

    DUMMY_CYCLES_OFFSET_ST = 12,

    QUAD_EN_OFFSET_WINBOND_CYPRESS = 1,
    QUAD_EN_OFFSET_MICRON = 3,
    QUAD_EN_OFFSET_ISSI_MACRONIX = 6,

    TB_OFFSET_MACRONIX = 3,
    SEC_OFFSET = 6,
    TB_OFFSET = 5,
    TB_OFFSET_ISSI = 1,
    TB_OFFSET_CYPRESS_WINBOND_256 = 6,
    BP_OFFSET = 2,
    BP_4TH_BIT_OFFSET_MICRON = 6,
    BP_SIZE = 3,
    PROTECT_BITS_SIZE = 5
};
//
// Relevant CR addresses, Bit offset and bit size
//

enum CrConstans {
    CR_FLASH_GW = 0xf0400,
    CR_FLASH_ADDR = 0xf0404,
    CR_FLASH_ADDR_7NM = 0xf0420,
    //CR_FLASH_DATA = 0xf0408,
    CR_FLASH_CS = 0xf0418,
    CR_GPIO_LOCK = 0xf00ec,
    BO_READ_OP = 0,
    BO_ADDR_INCR = 1,
    BO_LPC_STOP = 3,
    BO_SPI_NO_DATA = 4,
    BO_SPI_NO_ADDR = 5,
    BO_SPI_SPECIAL = 6,
    BO_MSIZE = 8,
    BS_MSIZE = 3,
    BO_STATUS = 26,
    BS_STATUS = 4,
    BO_BUSY = 30,
    BO_SPI_ADDR = 0,
    BS_SPI_ADDR = 24,
    BO_SPI_CMD = 24,
    BS_SPI_CMD = 8,
    BO_SPI_GPIO = 25,
    BS_SPI_GPIO = 4
};


int sx_get_flash_info_by_type(mflash *mfl, flash_info_t *type_index, int *log2size, u_int8_t *no_flash);
int sx_block_read_by_type(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data);
int sx_block_write_by_type(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data);
int sx_flash_lock_by_type(mflash *mfl, int lock_state);
int sx_erase_sect_by_type(mflash *mfl, u_int32_t addr, u_int32_t erase_size);
int mf_update_boot_addr_by_type(mflash *mfl, u_int32_t boot_addr);
int mfl_com_lock(mflash *mfl);
flash_access_commands_t gen_4byte_address_access_commands();
flash_access_commands_t gen_3byte_address_access_commands();
int release_semaphore(mflash *mfl, int ignore_writer_lock);
int     sx_set_quad_en(mflash *mfl, u_int8_t quad_en);
int     sx_get_quad_en(mflash *mfl, u_int8_t *quad_en);
int     sx_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);
int     sx_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);
int     sx_set_dummy_cycles(mflash *mfl, u_int8_t num_of_cycles);
int     sx_get_dummy_cycles(mflash *mfl, u_int8_t *num_of_cycles);
int     gw_wait_ready(mflash *mfl, const char *msg);

#endif /* MFLASH_ACCESS_LAYER_H_ */
