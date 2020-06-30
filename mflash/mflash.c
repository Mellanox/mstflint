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

#ifdef IRISC

#define NULL 0

#else

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <common/bit_slice.h>
#include <mtcr.h>
#include <reg_access.h>

#ifndef UEFI_BUILD
#include <tools_cif.h>
#endif

#include "mflash_pack_layer.h"
#include "mflash_access_layer.h"
#include "mflash.h"
#include "flash_int_defs.h"
#include "mflash_dev_capability.h"

#define ICMD_MAX_BLOCK_WRITE   128
#define INBAND_MAX_BLOCK_WRITE 32

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#ifndef __WIN__

#if defined __DJGPP__
//
// DJGPP - GCC PORT TO MS DOS
//
#include <netinet/in.h>
#include <unistd.h>

#define bswap_32(x) ntohl(x)

#endif // __DJGPP__

#define OP_NOT_SUPPORTED EOPNOTSUPP

#else // __WIN__

//
// Windows (Under DDK)
//
#define OP_NOT_SUPPORTED EINVAL
#define usleep(x) Sleep(((x + 999) / 1000))

#endif // __WIN__
#endif

#ifndef zero
#define zero 0
#endif

// Timer definitions (needed when polling flash semaphore in windows)
#ifndef __WIN__
#define TIMER_INIT(...)
#define TIMER_STOP(...)
#define TIMER_PRINT(...)
#define TIMER_GET_DIFF(...)
#define TIMER_INIT_AND_START(...)
#define TIMER_STOP_GET_DIFF(...)
#define TIMER_CHECK(...)
#else
#include <windows.h>
#define TIMER_INIT() \
    SYSTEMTIME _start, _end; \
    int _diff_in_sec, _diff_in_ms; \
    (void)_diff_in_sec; \
    (void)_diff_in_ms
#define TIMER_START() \
    GetSystemTime(&_start)
#define TIMER_STOP() \
    GetSystemTime(&_end)
#define TIMER_PRINT(...) \
    _diff_in_sec = _end.wSecond - _start.wSecond; \
    _diff_in_ms = (_end.wMilliseconds - _start.wMilliseconds; \
                   printf(__VA_ARGS__); \
                   printf("it took %d sec %d and ms to run.\n", _diff_in_sec, _diff_in_ms)
#define TIMER_GET_DIFF(diff_in_sec, diff_in_ms) \
    diff_in_sec = _end.wSecond - _start.wSecond; \
    diff_in_ms = _end.wMilliseconds - _start.wMilliseconds
#define TIMER_INIT_AND_START() \
    TIMER_INIT(); \
    TIMER_START()
#define TIMER_STOP_GET_DIFF(diff_in_sec, diff_in_ms) \
    TIMER_STOP(); \
    TIMER_GET_DIFF(diff_in_sec, diff_in_ms)
#define TIMER_CHECK(max_sec, max_ms, action_on_tout) \
    TIMER_STOP(); \
    _diff_in_sec = _end.wSecond - _start.wSecond; \
    _diff_in_ms = _end.wMilliseconds - _start.wMilliseconds; \
    if (_diff_in_sec >= max_sec && _diff_in_ms > max_ms) { \
        action_on_tout; \
    }
#endif

//
// Mellanox Technologies LTD Devices naming/abbreviation convention in this file:
//
// ConnectX         cntx
// ConnectIB        cib

/*
 *  Low level operations
 */

/* Flash Functions: */

// This is an interface function when running in IRISC
int mf_open_fw(mflash *mfl, flash_params_t *flash_params, int num_of_banks);
int cntx_int_spi_get_status_data(mflash *mfl, u_int8_t op_type, u_int32_t *status, u_int8_t data_num);

// forward decl:
int mfl_com_lock(mflash *mfl);
int release_semaphore(mflash *mfl, int ignore_writer_lock);
int mf_get_secure_host(mflash *mfl, int *mode);
int mf_secure_host_op(mflash *mfl, u_int64_t key, int op);

// NOTE: This macro returns ... not nice.
#define CHECK_RC(rc) do {if (rc) {return rc;}} while (0)
#define CHECK_RC_REL_SEM(mfl, rc) do {if (rc) {release_semaphore(mfl, 0); return rc;}} while (0)

#define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

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

// Constants:

// General:
#define GPIO_DIR_L       0xf008c
#define GPIO_POL_L       0xf0094
#define GPIO_MOD_L       0xf009c
#define GPIO_DAT_L       0xf0084
#define GPIO_DATACLEAR_L 0xf00d4
#define GPIO_DATASET_L   0xf00dc

#define SEMAP63          0xf03fc

// InfiniHost specific
#define IDLE           0
#define READ4          (1 << 29)
#define WRITE1         (2 << 29)

#define CR_FLASH       0xf01a4
#define ADDR_MSK       0x7ffffUL
#define CMD_MASK       0xe0000000UL

#define SST_STATUS_REG_VAL   0x80
#define ATMEL_STATUS_REG_VAL 0x0

#define MAX_FLASH_PROG_SEM_RETRY_CNT 40

#define CPUMODE_MSK    0xc0000000UL
#define CPUMODE_SHIFT  30
#define CPUMODE        0xf0150

#define IS4_HW_ID        0x1b3
#define SWITCHX_HW_ID    0x245
#define CONNECTX_HW_ID   0x190
#define CX3_PRO_HW_ID    0x1F7
#define CX3_HW_ID        0x1F5
#define CX4_HW_ID        0x209
#define CX4LX_HW_ID      0x20b
#define CX5_HW_ID        0x20d
#define CX6_HW_ID        0x20f
#define CX6DX_HW_ID      0x212
#define CX6LX_HW_ID      0x216
#define BLUEFIELD_HW_ID  0x211
#define BLUEFIELD2_HW_ID 0x214
#define CONNECT_IB_HW_ID 0x1FF
#define SWITCH_IB_HW_ID  0x247
#define SPECTRUM_HW_ID   0x249
#define SWITCH_IB2_HW_ID 0x24b
#define QUANTUM_HW_ID    0x24d
#define SPECTRUM2_HW_ID  0x24e
#define SPECTRUM3_HW_ID  0x250

/*
 * Device IDs Macros:
 */
#define IS_CONNECTX_4TH_GEN_FAMILY(dev_id) \
    (((dev_id) == CONNECTX_HW_ID) || ((dev_id) == CX3_HW_ID) || ((dev_id) == CX3_PRO_HW_ID))
#define IS_IS4_FAMILY(dev_id) \
    (((dev_id) == IS4_HW_ID))
#define IS_SX(dev_id) \
    ((dev_id) == SWITCHX_HW_ID)
#define IS_SIB(dev_id) \
    ((dev_id) == SWITCH_IB_HW_ID)
#define IS_SIB2(dev_id) \
    ((dev_id) == SWITCH_IB2_HW_ID)
#define IS_SEN(dev_id) \
    ((dev_id) == SPECTRUM_HW_ID)
#define IS_SPECTRUM2(dev_id) \
    ((dev_id) == SPECTRUM2_HW_ID)
#define IS_CONNECT_IB(dev_id) \
    ((dev_id) == CONNECT_IB_HW_ID)
#define IS_CONNECTX4(dev_id) \
    ((dev_id) == CX4_HW_ID)
#define IS_CONNECTX4LX(dev_id) \
    ((dev_id) == CX4LX_HW_ID)
#define IS_CONNECTX5(dev_id) \
    ((dev_id) == CX5_HW_ID)
#define IS_CONNECTX6(dev_id) \
    ((dev_id) == CX6_HW_ID)
#define IS_CONNECTX6DX(dev_id) \
    ((dev_id) == CX6DX_HW_ID)
#define IS_CONNECTX6LX(dev_id) \
    ((dev_id) == CX6LX_HW_ID)
#define IS_SPECTRUM3(dev_id) \
    ((dev_id) == SPECTRUM3_HW_ID)
#define IS_BLUEFIELD(dev_id) \
    ((dev_id) == BLUEFIELD_HW_ID)
#define IS_QUANTUM(dev_id) \
    ((dev_id) == QUANTUM_HW_ID)
#define IS_SPECTRUM(dev_id) \
    ((dev_id) == SPECTRUM_HW_ID)
#define IS_BLUEFEILD(dev_id) \
    ((dev_id) == BLUEFIELD_HW_ID)
#define IS_BLUEFEILD2(dev_id) \
    ((dev_id) == BLUEFIELD2_HW_ID)

#define HAS_TOOLS_CMDIF(dev_id) \
    ((((dev_id) == CX3_HW_ID) || ((dev_id) == CX3_PRO_HW_ID)))


#define COMMAND_MASK 0x00ff0000

// Write/Erase delays
// ------------------
// The below delays improve CPU utilization when doing long operations by
// sleeping instead of full throtle polling.
// Their values are set so they will not lenghen burn time (at least not by a meaningfull duration)
// and will save cpu. The delays are divided to an initial_delay, and then retry num_of_retries times waiting retry_delay.
// The initial delay is set according to the fastest flash we currently support (W25QxxBV).
// The retry_delay*num_of_retries is set according to the slowest flash maximum AC timing.
//
// To test there's no performance degradation by these delay: set DELAYS to 0 and RETRIES to infinity, and compare perf.

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

enum IntelFlashCommand {
    FC_ReadID = 0x90,
    FC_Read = 0xFF,
    FC_Erase = 0x20,
    FC_Confirm = 0xD0,
    FC_Clear = 0x50,
    FC_Write = 0x40,
    FC_LoadPB = 0xE0,
    FC_PBWrite = 0x0C,
    FC_Status = 0x70,
    FC_Suspend = 0xB0,
    FC_Resume = 0xD0,
    FC_ReadESR = 0x71,
    FC_QueryCFI = 0x98,
    FC_SCSErase = 0x28,
    FC_SCSWrite = 0xE8
};

enum IntelFlashStatus {
    FS_Ready = 0x80, FS_Suspended = 0x40, FS_Error = 0x3E, FS_BlockError = 0x3F
};

//static inline
static u_int32_t log2up(u_int32_t in)
{
    u_int32_t i = 0;
    for (i = 0; i < 32; i++) {
        if (in <= (u_int32_t)(1 << i)) {
            break;
        }
    }

    return i;
}

// ConnectX SPI interface:
int cntx_flash_init(mflash *mfl, flash_params_t *flash_params);
int cntx_flash_init_direct_access(mflash *mfl, flash_params_t *flash_params);

int cntx_st_spi_reset(mflash *mfl);
int cntx_st_spi_erase_sect(mflash *mfl, u_int32_t addr);

int cntx_st_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, u_int8_t is_first,
                               u_int8_t is_last, u_int32_t total_size);

int cntx_sst_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data);

int cntx_st_spi_block_read_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, u_int8_t is_first,
                              u_int8_t is_last, bool verbose);

int cntx_spi_get_type(mflash *mfl, u_int8_t op_type, u_int8_t *vendor, u_int8_t *type, u_int8_t *density);

int cntx_spi_write_status_reg(mflash *mfl, u_int32_t status_reg, u_int8_t write_cmd, u_int8_t bytes_num);

int spi_get_num_of_flashes(int prev_num_of_flashes);

int mf_get_write_protect_direct_access(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);

int mf_set_write_protect_direct_access(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);

int mf_get_quad_en_direct_access(mflash *mfl, u_int8_t *quad_en_p);

int mf_set_quad_en_direct_access(mflash *mfl, u_int8_t quad_en);

int mf_get_dummy_cycles_direct_access(mflash *mfl, u_int8_t *dummy_cycles_p);

int mf_set_dummy_cycles_direct_access(mflash *mfl, u_int8_t num_of_cycles);

#ifndef UEFI_BUILD
static int trm2mfe_err(trm_sts rc);
#endif

int my_memset(void *dst, u_int8_t data, u_int32_t len)
{
    u_int32_t i = 0;
    u_int8_t *bytes = (u_int8_t*) dst;

    for (i = 0; i < len; i++) {
        bytes[i] = data;
    }

    return 0;
}

int my_memcpy(void *dst, void *src, u_int32_t len)
{
    u_int32_t i = 0;
    u_int8_t *dbytes = (u_int8_t*) dst;
    u_int8_t *sbytes = (u_int8_t*) src;

    for (i = 0; i < len; i++) {
        dbytes[i] = sbytes[i];
    }

    return 0;
}

#if 0 // TODO: Currently the polling is in max throttle - no sleep is done
int usleep(u_int32_t usecs)
{
    u_int32_t i = 0;
    u_int32_t stub = 0;
    // TODO: Some more intelegent /accurate way to do it, or remove T.Os completely.
    u_int32_t loops = (usecs << 9);
    for (i = 0; i < loops; i++) {
        stub++;
    }

    return stub;
}
#endif

int write_chunks(mflash *mfl, u_int32_t addr, u_int32_t len, u_int8_t *data)
{
    int rc = 0;
    u_int8_t *p = (u_int8_t*) data;

    int all_ffs = 0;

    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t tmp_buff[MAX_WRITE_BUFFER_SIZE];

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    //printf("-D- write_chunks(addr=%x, size=%x)\n", addr, len);

    while (len) {
        u_int32_t i = 0;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;

        u_int32_t block_size = mfl->attr.block_write;
        u_int32_t block_mask = ~(block_size - 1);

        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size = block_size;

        u_int8_t *block_data = p;

        //
        // To keep things simple, we always write full blocks.
        // (there's an option to write partial buffer, but Intel reference code always
        // writes full buffer, with pads if needed. I do the same ...)
        //
        // The First and last cycles (can be the same one) may not be block aligned.
        // If this is the case, copy the block data to a 0xFF padded temp buffer (writing 0xFF
        // does not effect the flash)
        //

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask)) {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size) {
            my_memset(tmp_buff, 0xff, block_size);

            data_size -= prefix_pad_size;
            data_size -= suffix_pad_size;

            my_memcpy(tmp_buff + prefix_pad_size, p, data_size);

            block_data = tmp_buff;
        } else if (mfl->attr.page_write) {
            // current write is aligned to block size,
            // write data to next page, or to last full block (if we're in the last block in a page)
            u_int32_t page_mask = ~(mfl->attr.page_write - 1);
            u_int32_t next_page_addr = (addr + mfl->attr.page_write + 1) & page_mask;
            u_int32_t size_to_page_boundary = next_page_addr - addr;
            if (len > size_to_page_boundary) {
                block_size = size_to_page_boundary;
            } else {
                block_size = len & block_mask;
            }
            data_size = block_size;
        }

        //
        // Check to see if there's something to do
        //
        all_ffs = 1;
        for (i = 0; i < block_size; i++) {
            if (block_data[i] != 0xff) {
                all_ffs = 0;
                break;
            }
        }

        if (!all_ffs) {
            rc = mfl->f_write_blk(mfl, block_addr, block_size, block_data);
            CHECK_RC(rc);

            if (mfl->opts[MFO_NO_VERIFY] == 0) {
                u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE];
                rc = mfl->f_reset(mfl);
                CHECK_RC(rc);
                rc = mfl->f_read(mfl, addr, data_size, verify_buffer, false);
                CHECK_RC(rc);
                // Verify data
                for (i = 0; i < data_size; i++) {
                    // printf("-D- Verify: addr = %#x, verify_buffer[%d] = %#x, block_data[%d] = %#x\n",
                    //         addr, i, verify_buffer[i], i + prefix_pad_size, block_data[i + prefix_pad_size]);
                    if (verify_buffer[i] != block_data[i + prefix_pad_size]) {
                        //return _f.errmsg("Write verification failed. Addr %08x - exp:%02x act:%02x\n",
                        //       addr + i,
                        //       block_data[i + prefix_pad_size] ,
                        //       verify_buffer[i]);
                        return MFE_VERIFY_ERROR;
                    }
                }
            }
        }

        //
        // loop advance
        //

        addr += data_size;
        p += data_size;
        len -= data_size;
    }

    rc = mfl->f_reset(mfl);
    CHECK_RC(rc);

    return MFE_OK;
}

#define FD_LEGACY (1 << FD_8) | (1 << FD_16) | (1 << FD_32) | (1 << FD_64) | (1 << FD_128)

flash_info_t g_flash_info_arr[] = { { "M25PXxx", FV_ST, FMT_ST_M25PX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 0, 0, 0, 0 },
                                    { "M25Pxx", FV_ST, FMT_ST_M25P, FD_LEGACY, MCS_STSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0 },
                                    { "N25Q0XX", FV_ST, FMT_N25QXXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 1 },
                                    //{ MICRON_3V_NAME, FV_ST, FMT_N25QXXX, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 1 },
                                    { SST_FLASH_NAME, FV_SST, FMT_SST_25, FD_LEGACY, MCS_SSTSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0 },
                                    { WINBOND_NAME, FV_WINBOND, FMT_WINBOND, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0 },
                                    { WINBOND_W25X, FV_WINBOND, FMT_WINBOND_W25X, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 0, 0, 0, 0, 0 },
                                    { WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_3V, 1 << FD_128, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0 },
                                    { WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_3V, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB,  1, 1, 1, 0, 0 },
                                    { ATMEL_NAME, FV_ATMEL, FMT_ATMEL, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 0, 0, 0, 0, 0 },
                                    { S25FLXXXP_NAME, FV_S25FLXXXX, FMT_S25FLXXXP, FD_LEGACY, MCS_STSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0 },
                                    { S25FL116K_NAME, FV_S25FLXXXX, FMT_S25FL116K, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0 },
                                    { MACRONIX_NAME, FV_MX25K16XXX, FMT_MX25K16XXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0 },
                                    { MACRONIX_3V_NAME, FV_MX25K16XXX, FMT_MX25K16XXX, (1 << FD_256), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0 },
                                    { CYPRESS_3V_NAME, FV_S25FLXXXX, FMT_S25FLXXXL, 1 << FD_128, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0 },
                                    //{ CYPRESS_3V_NAME, FV_S25FLXXXX, FMT_S25FLXXXL, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB,  1, 1, 1, 0, 0 },
                                    { ISSI_3V_NAME, FV_IS25LPXXX, FMT_IS25LPXXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0 },

                                    { MACRONIX_1V8_NAME, FV_MX25K16XXX, FMT_SST_25, (1 << FD_256), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0 },
                                    //{ ISSI_3V_NAME, FV_IS25LPXXX, FMT_IS25LPXXX, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0 }
};

int cntx_sst_get_log2size(u_int8_t density, int *log2spi_size)
{
    switch (density) {
    case 0x41:
        *log2spi_size = 0x15;
        break;

    case 0x4A:
        *log2spi_size = 0x16;
        break;

    case 0x8D:
        *log2spi_size = 0x13;
        break;

    case 0x8E:
        *log2spi_size = 0x14;
        break;

    default:
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    return 0;
}

int get_log2size_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t density, int *log2size)
{

    if (type == FMT_SST_25 && vendor == FV_SST) {
        return cntx_sst_get_log2size(density, log2size);
    } else {
        *log2size = density;
    }
    return MFE_OK;
}

int get_type_index_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t density, unsigned *type_index)
{
    unsigned i = 0, arr_size = 0;
    arr_size = ARR_SIZE(g_flash_info_arr);

    for (i = 0; i < arr_size; i++) {
        flash_info_t *flash_info = &g_flash_info_arr[i];
        if (flash_info->vendor == vendor && flash_info->type == type && ((flash_info->densities & (1 << density)) != 0)) {
            *type_index = i;
            return MFE_OK;
        }
    }
    return MFE_UNSUPPORTED_FLASH_TYPE;
}

void mf_flash_list(char *flash_arr, int flash_arr_size)
{
    int i = 0;
    int arr_index = 0;
    int arr_size = ARR_SIZE(g_flash_info_arr);

    if (!flash_arr || flash_arr_size < 1) {
        return;
    }

    for (i = 0; i < arr_size; i++) {
        flash_info_t *flash_info = &g_flash_info_arr[i];
        int name_len = strlen(flash_info->name);
        if (flash_arr_size - name_len <= 2) {
            // Out of space, append \0 and return
            break;
        }
        strcpy(&flash_arr[arr_index], flash_info->name);
        arr_index += name_len;
        flash_arr_size -= name_len;
        if (i != arr_size - 1) {
            flash_arr[arr_index++] = ',';
            flash_arr[arr_index++] = ' ';
            flash_arr_size -= 2;
        }
    }
    flash_arr[arr_index] = '\0';
    return;
}

int get_type_index_by_name(const char *type_name, unsigned *type_index)
{
    unsigned i = 0, arr_size = 0;
    arr_size = ARR_SIZE(g_flash_info_arr);
    for (i = 0; i < arr_size; i++) {
        flash_info_t *flash_info = &g_flash_info_arr[i];
        if (!strcmp(type_name, flash_info->name)) {
            *type_index = i;
            return MFE_OK;
        }
    }
    printf("-E- The flash name \"%s\" is unknown\n.", type_name);
    return MFE_UNSUPPORTED_FLASH_TYPE;
}

int is_no_flash_detected(u_int8_t type, u_int8_t vendor, u_int8_t capacity)
{
    if ((type == 0xff && vendor == 0xff && capacity == 0xff) || (type == 0x0 && vendor == 0x0 && capacity == 0x0)) {
        return 1;
    }
    return 0;
}

int get_flash_info_by_res(mflash *mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash, unsigned char *es_p)
{
    int rc = 0;

    *no_flash = 0;

    rc = mfl->f_spi_status(mfl, SFC_RES, es_p);
    CHECK_RC(rc);
    // printf("-D- get_flash_info_by_res: es = %#x\n", *es_p);
    if ((*es_p >= 0x10 && *es_p < 0x17)) {
        *log2size = *es_p + 1;
        // This should return the same result for any FD value from [FD_8..FD_128].
        // This is just to catch the FD_LEGACY bitmask.
        return get_type_index_by_vendor_type_density(FV_ST, FMT_ST_M25P, *log2size, type_index);
    } else if (*es_p == 0xff || *es_p == 0x0) {
        *no_flash = 1;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }
    return MFE_OK;
}

int cntx_get_flash_info(mflash *mfl, flash_info_t *f_info, int *log2size, u_int8_t *no_flash)
{
    int rc = 0;
    u_int8_t type = 0, capacity = 0, vendor = 0, no_flash_res = 0, no_flash_rdid = 0;
    unsigned char es = 0;
    unsigned type_index = 0;
    // Assume there is a flash.
    *no_flash = 0;

    rc = cntx_spi_get_type(mfl, SFC_JEDEC, &vendor, &type, &capacity);
    CHECK_RC(rc);
    no_flash_rdid = is_no_flash_detected(type, vendor, capacity);
    // printf("-D- cntx_spi_get_type: rc: %#x, vendor=%#x, type=%#x, capacity=%#x\n", rc, vendor, type, capacity);
    // printf("-D- rc = %d, no_flash_rdid = %d\n", rc, no_flash_rdid);

    if (no_flash_rdid) {
        // printf("-D- no support for rdid\n");
        // RDID Failed due to:
        // 1- RDID is not supported but RES is - Old flashes.
        // 2- There is no Flash
        // 3- Flash is not supported

        // Trying RES
        rc = get_flash_info_by_res(mfl, &type_index, log2size, &no_flash_res, &es);
        if (rc == 0 && no_flash_res == 1) {
            // RES Succeeded due to: no flash, unsupported flash or old flash.
            *no_flash = 1;
            // when no_flash_rdid == 0 then "1- RDID is not supported but RES is - Old flashes."
        }
    } else {
        //  RDID Succeded.
        rc = MFE_OK;
        if ( get_log2size_by_vendor_type_density(vendor, type, capacity, log2size) != MFE_OK ) {
            printf("-E- SST SPI flash #%d (vendor: %#x, type: %#x, capacity:%#x) is not supported.\n", get_bank_int(mfl), vendor, type, capacity);
            rc = MFE_UNSUPPORTED_FLASH_TOPOLOGY;
        } else if (get_type_index_by_vendor_type_density(vendor, type, *log2size, &type_index) != MFE_OK) {
            rc = MFE_UNSUPPORTED_FLASH_TYPE;
        }
        // found supported flash if rc == MFE_OK at this point.
    }

    if (rc == MFE_UNSUPPORTED_FLASH_TYPE) {
        printf("-E- SPI flash #%d (vendor: %#x, memory type: %#x, es: %#x) is not supported.\n", get_bank_int(mfl), vendor, type, es);
    }
    // printf("-D- rc = %d, no_flash_res = %d, type_index = %d.\n", rc, no_flash_res, *type_index);
    if (rc == MFE_OK && *no_flash == 0) {
        memcpy(f_info, &g_flash_info_arr[type_index], sizeof(flash_info_t));
    }
    return rc;
}

int compare_flash_params(flash_params_t *flash_params, int bank_num, const char *type_name, int log2size)
{
    if (strcmp(flash_params->type_name, type_name) != 0) {
        printf("-E- SPI flash #%d (type: %s)differs in type from SPI flash #%d(type: %s). "
               "All flash devices must be of the same type.\n", bank_num, type_name, bank_num - 1, flash_params->type_name);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    if (flash_params->log2size != log2size) {
        printf("-E- SPI flash #%d (log2size: %#x) differs in size from SPI flash #%d (log2size: %#x). "
               "All flash devices must be of the same size.\n", bank_num, log2size, bank_num - 1, flash_params->log2size);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;

    }
    return MFE_OK;
}

int cntx_st_spi_get_status(mflash *mfl, u_int8_t op_type, u_int8_t *status)
{
    u_int32_t flash_data = 0;
    int rc = 0;

    rc = cntx_int_spi_get_status_data(mfl, op_type, &flash_data, 1);
    CHECK_RC(rc);
    *status = EXTRACT(flash_data, 0, 8);
    return MFE_OK;
}

int get_num_of_banks_int(mflash *mfl)
{
    int num = 0;
    if ((mfl->opts[MFO_USER_BANKS_NUM] == 0) && (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_NO) && ((num = get_num_of_banks(mfl->mf)) != -1)) {
        return num; // if mfpa register is supported get the exact number of flash banks
    }
    return mfl->opts[MFO_NUM_OF_BANKS];
}

int get_flash_params(mflash *mfl, flash_params_t *flash_params, flash_info_t *flash_info)
{
    int num_of_flashes = get_num_of_banks_int(mfl);
    int spi_sel = 0, rc = 0;
    int params_were_set = 0;
    flash_info_t tmp_flash_info;
    memset(flash_params, 0, sizeof(flash_params_t));
    memset(flash_info, 0, sizeof(flash_info_t));
    memset(&tmp_flash_info, 0, sizeof(flash_info_t));

    // if number of flash banks is zero exit with error
    if (num_of_flashes == 0) {
        return MFE_NO_FLASH_DETECTED;
    }

    for (spi_sel = 0; spi_sel < num_of_flashes; spi_sel++) {
        int log2size;
        u_int8_t no_flash = 0;
        const char *type_name;
        rc = set_bank(mfl, spi_sel);
        CHECK_RC(rc);
        rc = mfl->f_get_info(mfl, &tmp_flash_info, &log2size, &no_flash);
        CHECK_RC(rc);

        //printf("-D- spi_sel = %d, num_of_flashes = %d, rc = %d, no_flash = %d\n", spi_sel, num_of_flashes, rc, no_flash);
        if (no_flash == 1) {
            // This bank is empty and also the following banks will be empty.
            if (flash_params->num_of_flashes == 0) {
                // if we haven't detected any 'supported' flash, return an error.
                return MFE_NO_FLASH_DETECTED;
            }
            break;
        }

        type_name = tmp_flash_info.name;
        if (params_were_set == 0) {
            flash_params->type_name = type_name;
            flash_params->log2size = log2size;
            memcpy(flash_info, &tmp_flash_info, sizeof(flash_info_t));
            params_were_set = 1;
        } else {
            rc = compare_flash_params(flash_params, spi_sel, type_name, log2size);
            CHECK_RC(rc);
        }
        // Init SST flash.
        if (mfl->access_type == MFAT_MFILE) {
            if (flash_info->vendor == FV_SST && flash_info->type == FMT_SST_25) {
                rc = cntx_spi_write_status_reg(mfl, SST_STATUS_REG_VAL, SFC_WRSR, 1);
                CHECK_RC(rc);
            } else if (flash_info->vendor == FV_ATMEL && flash_info->type == FMT_ATMEL) {
                rc = cntx_spi_write_status_reg(mfl, ATMEL_STATUS_REG_VAL, SFC_WRSR, 1);
                CHECK_RC(rc);
            }
        }

        flash_params->num_of_flashes++;
    }
    return MFE_OK;
}

flash_access_commands_t gen_4byte_address_access_commands()
{
    flash_access_commands_t flash_command;
    memset(&flash_command, 0, sizeof(flash_command));
    flash_command.sfc_sector_erase = SFC_4SE;
    flash_command.sfc_subsector_erase = SFC_4SSE;
    flash_command.sfc_page_program = SFC_4PP;
    flash_command.sfc_read = SFC_4READ;
    flash_command.sfc_fast_read = SFC_4FAST_READ;
    return flash_command;
}

flash_access_commands_t gen_3byte_address_access_commands()
{
    flash_access_commands_t flash_command;
    memset(&flash_command, 0, sizeof(flash_command));
    flash_command.sfc_sector_erase = SFC_SE;
    flash_command.sfc_subsector_erase = SFC_SSE;
    flash_command.sfc_page_program = SFC_PP;
    flash_command.sfc_read = SFC_READ;
    flash_command.sfc_fast_read = SFC_FAST_READ;
    return flash_command;
}

// @input: mfl
// @output: access_commands
// @return: MfError status
MfError gen_access_commands(mflash *mfl, flash_access_commands_t *access_commands)
{
    MfError status;

    if (!mfl || !access_commands) {
        return MFE_BAD_PARAMS;
    }
    memset(access_commands, 0, sizeof(*access_commands));
    int four_byte_address_needed = is_four_byte_address_needed(mfl, &status);
    if (status != MFE_OK) {
        return status;
    }
    *access_commands = ((mfl->attr.log2_bank_size >= FD_256 && four_byte_address_needed) ?
            gen_4byte_address_access_commands() : gen_3byte_address_access_commands());
    return MFE_OK;
}

bool is_x_byte_address_access_commands(mflash *mfl, int x)
{
    if (x != 3 && x != 4) {
        return false;
    }

    flash_access_commands_t compared_to_access_commands =
        x == 4 ? gen_4byte_address_access_commands() : gen_3byte_address_access_commands();
    flash_access_commands_t cur = mfl->attr.access_commands;

    return (compared_to_access_commands.sfc_sector_erase == cur.sfc_sector_erase && compared_to_access_commands.sfc_subsector_erase == cur.sfc_subsector_erase && compared_to_access_commands.sfc_page_program == cur.sfc_page_program && compared_to_access_commands.sfc_read == cur.sfc_read && compared_to_access_commands.sfc_fast_read == cur.sfc_fast_read);
}

int spi_fill_attr_from_params(mflash *mfl, flash_params_t *flash_params, flash_info_t *flash_info)
{
    mfl->attr.log2_bank_size = flash_params->log2size;
    flash_access_commands_t access_commands;
    int rc = gen_access_commands(mfl, &access_commands);
    CHECK_RC(rc);
    mfl->attr.access_commands = access_commands;
    mfl->attr.bank_size = 1 << flash_params->log2size;
    mfl->attr.size = mfl->attr.bank_size * flash_params->num_of_flashes;
    mfl->attr.block_write = 16; // In SPI context, this is the transaction size. Max is 16.

    mfl->attr.sector_size = flash_info->sector_size;
    mfl->attr.support_sub_and_sector = flash_info->support_sub_and_sector;
    mfl->attr.command_set = flash_info->command_set;
    mfl->attr.erase_command = flash_info->erase_command;
    mfl->attr.type_str = flash_info->name;

    mfl->attr.quad_en_support = flash_info->quad_en_support;
    mfl->attr.dummy_cycles_support = flash_info->dummy_cycles_support;

    mfl->attr.write_protect_support = flash_info->write_protected_support;
    mfl->attr.protect_sub_and_sector = flash_info->protect_sub_and_sector;
    mfl->attr.banks_num = flash_params->num_of_flashes;
    mfl->attr.vendor = flash_info->vendor;
    mfl->attr.type = flash_info->type;
    return MFE_OK;
}

#define GET_FLASH_RETRY 2
int st_spi_fill_attr(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;
    flash_params_t *cur_flash_params, tmp_flash_params;
    flash_info_t flash_info;
    unsigned type_index = 0;

    // printf("-D- st_spi_fill_attr: ignore_detect = %d, log2size = %#x.\n", mfl->ignore_flash_detect, mfl->user_attr.log2size);
    if (flash_params == NULL) {
        int i = 0;
        // Get flash params from the flash itself
        cur_flash_params = &tmp_flash_params;

        while (i < GET_FLASH_RETRY) {
            rc = get_flash_params(mfl, cur_flash_params, &flash_info);
            if (rc != MFE_NO_FLASH_DETECTED) {
                break;
            }
            i++;
        }
        CHECK_RC(rc);

    } else {
        // Get the flash params from the user.
        rc = get_type_index_by_name(flash_params->type_name, &type_index);
        CHECK_RC(rc);
        memcpy(&flash_info, &(g_flash_info_arr[type_index]), sizeof(flash_info_t));
        cur_flash_params = flash_params;
    }
    // Init the flash attr according to the flash parameters (which was wither given by the user or read from the flash)
    rc = spi_fill_attr_from_params(mfl, cur_flash_params, &flash_info);
    CHECK_RC(rc);
    // printf("-D- spi_size = %#x,  log2spi_size = %#x, bank_size = %#x, flashes_num = %d\n", mfl->attr.size, mfl->attr.log2_bank_size,
    //       mfl->attr.bank_size, cur_flash_params->num_of_flashes);
    return MFE_OK;
}

int st_spi_wait_wip(mflash *mfl, u_int32_t init_delay_us, u_int32_t retry_delay_us,
                    u_int32_t num_of_retries)
{

    int rc = 0;
    u_int8_t status = 0;
    u_int32_t i = 0;

    usleep(init_delay_us);

    for (i = 0; i < num_of_retries; ++i) {
        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
        CHECK_RC(rc);
        if ((status & 1) == 0) {
            return MFE_OK;
        }
        usleep(retry_delay_us);
    }

    return MFE_WRITE_TIMEOUT;
}

int read_chunks(mflash *mfl, u_int32_t addr, u_int32_t len, u_int8_t *data, bool verbose)
{

    int rc = 0;
    u_int8_t *p = (u_int8_t*) data;

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }
    u_int32_t original_len = len;
    // Note:
    // Assuming read block is the same as write block size.
    // This is true for current Mellanox devices SPI flash access implementation.
    // Check for future devices.
    u_int32_t block_size = mfl->attr.block_write;
    u_int32_t block_mask = 0;

    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t tmp_buff[MAX_WRITE_BUFFER_SIZE];

    block_mask = ~(block_size - 1);
    u_int32_t perc = 0xffffffff;
    if (verbose) {
        printf("\33[2K\r");//clear the current line
    }
    while (len) {
        u_int32_t i = 0;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;

        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size = block_size;

        u_int8_t *block_data = p;

        //
        // First and last cycles (can be the same one) may not be block aligned.
        // Check the status, and copy data to a padded temp bufer if not aligned.
        // (there's an option to write partial buffer, but Intel reference code always
        // writes full buffer, with pads if needed. I do the dame ...)
        //

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask)) {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size) {
            // block exceeds given buffer - read to a temp bufer and
            // copy the required data to user's bufer.
            data_size -= suffix_pad_size;
            data_size -= prefix_pad_size;
            block_data = tmp_buff;
        }
        rc = mfl->f_read_blk(mfl, block_addr, block_size, block_data, false);
        CHECK_RC(rc);

        if (suffix_pad_size || prefix_pad_size) {
            for (i = 0; i < data_size; i++) {
                p[i] = tmp_buff[prefix_pad_size + i];
            }
        }

        //
        // loop advance
        //

        addr += data_size;
        p += data_size;
        len -= data_size;

        if (verbose) {
            u_int32_t new_perc = 100 - 100*(1.0*len/original_len);
            if (new_perc != perc) {
                printf("\r%s%d%c", "Reading flash section: ", new_perc, '%');
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    return MFE_OK;
}

////////////////////////////////////////
//
// InfiniHostIIILx spi  access functions
//
////////////////////////////////////////

//
// Relevant CR addresses, Bit offset and bit size
//

enum CrConstans {
    CR_FLASH_GW = 0xf0400,
    CR_FLASH_ADDR = 0xf0404,
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

int gw_wait_ready(mflash *mfl, const char *msg)
{
    u_int32_t gw_cmd = 0;
    u_int32_t cnt = 0;
    (void) msg; // NOT USED FOR NOW
    do {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT) {
            //return errmsg("Flash gateway timeout: %s.", msg);
            return MFE_TIMEOUT;
        }

        MREAD4(CR_FLASH_GW, &gw_cmd);

    } while (EXTRACT(gw_cmd, BO_BUSY, 1));

    return MFE_OK;
}

int empty_reset(mflash *mfl)
{
    (void) mfl; /* avoid compiler warning */
    return MFE_OK;
}

//////////////////////////////////////////
//
// ConnectX functions implementation
//
//////////////////////////////////////////
enum CntxCrConstants {
    HCR_FLASH_CMD = 0xf0400,
    HCR_FLASH_ADDR = 0xf0404,

    HCR_FLASH_DATA = 0xf0410,

    HBO_READ_OP = 0,
    HBO_ADDR_AUTO_INC = 1,
    HBO_CMD_PHASE = 2,
    HBO_ADDR_PHASE = 3,
    HBO_DATA_PHASE = 4,
    HBO_CS_HOLD = 5,

    HBO_MSIZE = 8,
    HBS_MSIZE = 3,

    HBO_CHIP_SELECT = 11,
    HBS_CHIP_SELECT = 2,

    HBO_FLASH_ENABLE = 13, //In old devices

    HBO_ADDR_SIZE = 14,

    HBO_CMD = 16,
    HBS_CMD = 8,

    HBO_BUSY = 30,
    HBO_LOCK = 31,

    HBO_ADDR = 0,

    // GPIOs
    HCR_GPIO_LOCK = 0xf0048,
    HCR_GPIO_LOCK_VAL = 0xd42f,

    HCR_GPIO_DATA_OUT = 0xf0040,
    HCR_GPIO_MODE0 = 0xf0050,
    HCR_GPIO_MODE1 = 0xf004c,

    HBO_GPIO_CS = 25,
    HBS_GPIO_CS = 4
};

int empty_set_bank(mflash *mfl, u_int32_t bank)
{
    // NULL function - No actual work here - in ConnectX the curr_bank is written in the command word.
    (void) mfl; // Avoid Compiler warning
    (void) bank;   // Avoid Compiler warning
    return MFE_OK;
}

int cntx_exec_cmd(mflash *mfl, u_int32_t gw_cmd, char *msg)
{
    if (!IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id)) {
        // for old devices lock bit is separate from the flash HW ifc
        //for new devices need to make sure this bit remains locked when writing the dword
        gw_cmd = MERGE(gw_cmd, 1, 31, 1);
    }
    if ((gw_cmd & (1 << HBO_ADDR_PHASE)) != 0) { // This is an access command
        if (is_x_byte_address_access_commands(mfl, 4)) {
            gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_SIZE, 1);
        } else if (!is_x_byte_address_access_commands(mfl, 3)) {
            return MFE_ACCESS_COMMANDS_NOT_INITIALIZED;
        }
    }
    gw_cmd = MERGE(gw_cmd, 1, HBO_BUSY, 1);

    MfError status;
    int flash_enable_needed = is_flash_enable_needed(mfl, &status);
    if (status != MFE_OK) {
        return status;
    }
    if (flash_enable_needed) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_FLASH_ENABLE, 1);
    }

    gw_cmd = MERGE(gw_cmd, (u_int32_t )mfl->curr_bank, HBO_CHIP_SELECT, HBS_CHIP_SELECT);
    //  printf("-D- cntx_exec_cmd: %s, gw_cmd = %#x\n", msg, gw_cmd);
    MWRITE4(CR_FLASH_GW, gw_cmd);
    return gw_wait_ready(mfl, msg);
}

/*
 * execute a flash GW command and get the output: data0...data3 from the flash interface
 *
 * mfl - pointer to an initilized mflash obj
 * gw_cmd - the flash gateway command to execute
 * buff - pointer to a buffer where the output data from the flash GW will be written to
 * buff_dword_sz - size for buff in dwords
 * addr - if != NULL *addr will be written to the addr bits of the flash GW. (for commands that read from flash)
 * msg - optional string that describes the action for debug purposes, not used ATM however its recommended to put usefull
 *        data for future dubugabillity.
 * return : MFE_OK (0) upon success or a value != 0 upon error accroding to mlfash error code.
 */
int cntx_exec_cmd_get(mflash *mfl, u_int32_t gw_cmd, u_int32_t *buff, int buff_dword_sz,
                      u_int32_t *addr, char *msg)
{
    int rc = 0;
    if (!mfl || !buff || !buff_dword_sz) {
        return MFE_BAD_PARAMS;
    }

    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);

    // write GW addr if needed
    if (addr) {
        if (mwrite4(mfl->mf, HCR_FLASH_ADDR, *addr) != 4) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }
    // execute gw command
    rc = cntx_exec_cmd(mfl, gw_cmd, msg);
    CHECK_RC_REL_SEM(mfl, rc);
    // copy data from CR-space to buff
    if (mread4_block(mfl->mf, HCR_FLASH_DATA, buff, (buff_dword_sz << 2)) != (buff_dword_sz << 2)) {
        release_semaphore(mfl, 0);
        return MFE_CR_ERROR;
    }
    //release semaphore
    release_semaphore(mfl, 0);
    return MFE_OK;
}

/*
 * Set input in: data0...data3 from the flash interface and execute a flash GW command
 *
 * mfl - pointer to an initilized mflash obj
 * gw_cmd - the flash gateway command to execute
 * buff - if != NULL pointer to a buffer to the input data for the flash GW.
 * buff_dword_sz - size for buff in dwords
 * addr - if != NULL *addr will be written to the addr bits of the flash GW. (for commands that write from flash)
 * msg - optional string that describes the action for debug purposes, not used ATM however its recommended to put usefull
 *        data for future dubugabillity.
 * return : MFE_OK (0) upon success or a value != 0 upon error accroding to mlfash error code.
 */
int cntx_exec_cmd_set(mflash *mfl, u_int32_t gw_cmd, u_int32_t *buff, int buff_dword_sz,
                      u_int32_t *addr, char *msg)
{
    int rc = 0;
    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);

    // write data from buff to CR-space
    if (buff && buff_dword_sz) {
        if (mwrite4_block(mfl->mf, HCR_FLASH_DATA, buff, (buff_dword_sz << 2)) != (buff_dword_sz << 2)) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }

    // write GW addr if needed
    if (addr) {
        if (mwrite4(mfl->mf, HCR_FLASH_ADDR, *addr) != 4) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }
    // execute gw command
    rc = cntx_exec_cmd(mfl, gw_cmd, msg);
    CHECK_RC_REL_SEM(mfl, rc);

    //release semaphore
    release_semaphore(mfl, 0);
    return MFE_OK;
}

int cntx_int_spi_get_status_data(mflash *mfl, u_int8_t op_type, u_int32_t *status, u_int8_t bytes_num)
{
    int rc = 0;

    u_int32_t gw_cmd = 0;
    u_int32_t flash_data = 0;
    //TODO: adrianc: update msize from log2(bytes_num)
    gw_cmd = MERGE(gw_cmd, 1, HBO_READ_OP, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 2, HBO_MSIZE, HBS_MSIZE);

    gw_cmd = MERGE(gw_cmd, op_type, HBO_CMD, HBS_CMD);

    if (bytes_num > 4) {
        return MFE_BAD_PARAMS;
    }
    rc = cntx_exec_cmd_get(mfl, gw_cmd, &flash_data, 1, (u_int32_t*) NULL, "Read id");
    CHECK_RC(rc);

    // printf("-D- cntx_int_spi_get_status_data: op=%02x status=%08x\n", op_type, flash_data);
    *status = (flash_data >> 8 * (4 - bytes_num));
    return MFE_OK;
}

int cntx_st_spi_write_enable(mflash *mfl)
{
    u_int32_t gw_cmd = 0;
    int rc = 0;
    // Write enable:
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, SFC_WREN, HBO_CMD, HBS_CMD);

    rc = cntx_exec_cmd_set(mfl, gw_cmd, (u_int32_t*) NULL, 0, (u_int32_t*) NULL, "WREN command");
    CHECK_RC(rc);

    //gw_cmd =  MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);

    //MWRITE4(CR_FLASH_GW,   gw_cmd);

    return MFE_OK;
}

/*
 * Consts needed to extract the needed data for the jedec ID
 *  from various flash types.
 */
enum {
    JEDEC_ATMEL_CAPACITY_BITOFF = 16,
    JEDEC_ATMEL_CAPACITY_BITLEN = 5,
    JEDEC_ATMEL_TYPE_BITOFF = 21,
    JEDEC_ATMEL_TYPE_BITLEN = 3,

    JEDEC_VENDOR_ID_BITOFF = 24,
    JEDEC_VENDOR_ID_BITLEN = 8,

    JEDEC_CAPACITY_BITOFF = 8,
    JEDEC_CAPACITY_BITLEN = 8,

    JEDEC_TYPE_BITOFF = 16,
    JEDEC_TYPE_BITLEN = 8
};

int get_flash_info_for_atmel(u_int32_t jedec_id, u_int8_t *type, u_int8_t *density)
{
    u_int8_t tmp_cap = 0;

    tmp_cap = EXTRACT(jedec_id, JEDEC_ATMEL_CAPACITY_BITOFF, JEDEC_ATMEL_CAPACITY_BITLEN);
    *type = EXTRACT(jedec_id, JEDEC_ATMEL_TYPE_BITOFF, JEDEC_ATMEL_TYPE_BITLEN);
    switch (tmp_cap) {
    case 0x4:
        *density = 0x13;
        break;

    case 0x5:
        *density = 0x14;
        break;

    case 0x6:
        *density = 0x15;
        break;

    case 0x7:
        *density = 0x16;
        break;

    default:
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }

    return MFE_OK;

}
int get_info_from_jededc_id(u_int32_t jedec_id, u_int8_t *vendor, u_int8_t *type, u_int8_t *density)
{
    int rc = 0;
    *vendor = EXTRACT(jedec_id, JEDEC_VENDOR_ID_BITOFF, JEDEC_VENDOR_ID_BITLEN);
    if (*vendor == FV_ATMEL) {
        rc = get_flash_info_for_atmel(jedec_id, type, density);
        CHECK_RC(rc);
    } else {
        *type = EXTRACT(jedec_id, JEDEC_TYPE_BITOFF, JEDEC_TYPE_BITLEN);
        *density = EXTRACT(jedec_id, JEDEC_CAPACITY_BITOFF, JEDEC_CAPACITY_BITLEN);
    }

    return MFE_OK;
}

int cntx_spi_get_type(mflash *mfl, u_int8_t op_type, u_int8_t *vendor, u_int8_t *type,
                      u_int8_t *density)
{
    u_int32_t flash_data = 0;
    int rc = 0;

    rc = cntx_int_spi_get_status_data(mfl, op_type, &flash_data, 4);
    CHECK_RC(rc);
    //printf("-D- jedec_info = %#x\n", flash_data);
    // Get type and some other info from jededc_id
    get_info_from_jededc_id(flash_data, vendor, type, density);
    // printf("-D- cntx_spi_get_type: vendor = %#x, type = %#x, capacity = %#x\n", *vendor, *type, *capacity);
    return MFE_OK;
}
int cntx_spi_write_status_reg(mflash *mfl, u_int32_t status_reg, u_int8_t write_cmd, u_int8_t bytes_num)
{
    int rc = 0;
    u_int32_t gw_cmd = 0;
    // TODO: adrianc: add support for dynamic writes of power of 2 bytes_num not just 1,2 bytes
    rc = cntx_st_spi_write_enable(mfl);
    CHECK_RC(rc);
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);

    gw_cmd = MERGE(gw_cmd, write_cmd, HBO_CMD, HBS_CMD);

    if (bytes_num != 1 && bytes_num != 2) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    // push status reg to upper bytes
    status_reg = status_reg << ((bytes_num == 2) ? 16 : 24);
    if (bytes_num == 2) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_MSIZE, 1);
    }
    rc = cntx_exec_cmd_set(mfl, gw_cmd, &status_reg, 1, (u_int32_t*) NULL, "Write-Status-Register");
    // wait for flash to write the register
    if (mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL) { // New CYPRESS
        msleep(WRITE_STATUS_REGISTER_DELAY_CYPRESS);
    } else if (mfl->attr.vendor == FV_ST && mfl->attr.type == FMT_N25QXXX) { // New MICRON
        msleep(WRITE_STATUS_REGISTER_DELAY_MICRON);
    } else {
        msleep(WRITE_STATUS_REGISTER_DELAY_MIN); // Some can sleep only 30 or even 15. We should consider optimize this.
    }
    return rc;
}

int cntx_init_gpios(mflash *mfl)
{
    //
    // Set Multi SPI CS to output and with value of 1 (inactive)
    // Assuming 4 flashes. If there are less than 4 flashes and there's
    // an access to a void flash, the access will fail.
    //

    u_int32_t spi_en = 0xf;

    u_int32_t mode0 = 0;
    u_int32_t mode1 = 0;
    u_int32_t data = 0;

    // Set 4 Chip selects to 1
    MREAD4(HCR_GPIO_DATA_OUT, &data);
    data = MERGE(data, spi_en, BO_SPI_GPIO, BS_SPI_GPIO);
    MWRITE4(HCR_GPIO_DATA_OUT, data);

    MREAD4(HCR_GPIO_MODE0, &mode0);
    MREAD4(HCR_GPIO_MODE1, &mode1);

    // Set 4 Chip selects to outputs
    if (EXTRACT(mode0, HBO_GPIO_CS, HBS_GPIO_CS) != spi_en ||
        EXTRACT(mode1, HBO_GPIO_CS, HBS_GPIO_CS) != 0) {
        mode0 = MERGE(mode0, spi_en, BO_SPI_GPIO, BS_SPI_GPIO);
        mode1 = MERGE(mode1, ~spi_en, BO_SPI_GPIO, BS_SPI_GPIO);

        // unlock gpio
        MWRITE4(HCR_GPIO_LOCK, HCR_GPIO_LOCK_VAL);

        MWRITE4(HCR_GPIO_MODE0, mode0);
        MWRITE4(HCR_GPIO_MODE1, mode1);

        // re-lock
        MWRITE4(HCR_GPIO_LOCK, 0);
    }

    return MFE_OK;
}

#define MFLASH_ENV "MFLASH_BANKS"

int spi_get_num_of_flashes(int prev_num_of_flashes)
{
    char *mflash_env;
    int num = 0;

    if (prev_num_of_flashes != -1) {
        return prev_num_of_flashes;
    }

    mflash_env = getenv(MFLASH_ENV);
    if (mflash_env) {
        num = atol(mflash_env);
        // make sure the value makes sense
        num = (num > 16 || num <= 0) ? -1 : num;
        return num;
    }

    return -1;
}

int spi_update_num_of_banks(mflash *mfl, int prev_num_of_flashes)
{
    int num_of_banks = 0;

    num_of_banks = spi_get_num_of_flashes(prev_num_of_flashes);
    if (num_of_banks == -1) {
        if (IS_SX(mfl->attr.hw_dev_id) || IS_SIB(mfl->attr.hw_dev_id) || IS_SEN(mfl->attr.hw_dev_id) || IS_SIB2(mfl->attr.hw_dev_id)) {
            mfl->opts[MFO_NUM_OF_BANKS] = 2;
        } else {
            mfl->opts[MFO_NUM_OF_BANKS] = 1;
        }
        mfl->opts[MFO_USER_BANKS_NUM] = 0;
    } else {
        mfl->opts[MFO_NUM_OF_BANKS] = num_of_banks;
        mfl->opts[MFO_USER_BANKS_NUM] = 1;
    }
    return MFE_OK;
}

int cntx_st_spi_reset(mflash *mfl)
{
    (void) mfl;
    return MFE_OK;
}

int cntx_st_spi_page_read(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data, bool verbose)
{
    (void)verbose;
    int rc = 0;

    u_int32_t last_blk_addr = 0;
    u_int32_t last_addr = 0;
    u_int8_t is_first = 1;
    u_int8_t is_last = 0;
    u_int8_t *p = data;

    if (addr & ((u_int32_t) mfl->attr.block_write - 1)) {
        return MFE_BAD_ALIGN;
    }

    if (size & ((u_int32_t) mfl->attr.block_write - 1)) {
        return MFE_BAD_ALIGN;
    }

    //printf("-D- cntx_st_spi_page_read(addr=%05x, u_int32_t size=%03x)\n", addr, size);

    last_addr = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr) {
        if (addr == last_blk_addr) {
            is_last = 1;
        }

        rc = cntx_st_spi_block_read_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last, false);
        CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p += mfl->attr.block_write;
    }

    return MFE_OK;
}

/*
         int get_flash_offset(u_int32_t addr, int log2_bank_size, u_int32_t *flash_addr_p)
         {
 * flash_addr_p = addr & ONES32(log2_bank_size);
         return MFE_OK;
         }
 */

int cntx_st_spi_block_read_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data,
                              u_int8_t is_first, u_int8_t is_last, bool verbose)
{
    (void)verbose;
    int rc = 0;
    u_int32_t i = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;

    //printf("-D- cntx_st_spi_block_read_ex(addr=%05x, u_int32_t size=%03x, first=%d, last=%d)\n", blk_addr, blk_size, (u_int32_t) is_first, (u_int32_t) is_last);
    COM_CHECK_ALIGN(blk_addr, blk_size);

    if (blk_size > (u_int32_t) mfl->attr.block_write || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    if (is_first) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, mfl->attr.access_commands.sfc_read, HBO_CMD, HBS_CMD);

        rc = get_flash_offset(blk_addr, mfl->attr.log2_bank_size, &gw_addr);
        CHECK_RC(rc);
    }
    //printf("-D- gw_addr = %#x, gw_cmd = %#x, blk_addr = %#x, mfl->attr.log2_bank_size = %#x\n", gw_addr, gw_cmd, blk_addr, mfl->attr.log2_bank_size);
    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_CS_HOLD, 1);
    }

    // Read the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_READ_OP, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), BO_MSIZE, BS_MSIZE);

    rc = cntx_exec_cmd_get(mfl, gw_cmd, (u_int32_t*) data, (blk_size >> 2), &gw_addr, "Read");
    CHECK_RC(rc);

    ////if (mread_by_chunks(mfl->mf, HCR_FLASH_DATA, data, blk_size) != (int)blk_size) {
    //if (mread4_block(mfl->mf, HCR_FLASH_DATA, (u_int32_t*)data, blk_size) != (int)blk_size) {
    //    return 2;
    //fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", HCR_FLASH_DATA, strerror(errno), (u_int32_t)errno);
    //exit(2);
    //}

    for (i = 0; i < blk_size; i += 4) {
        *(u_int32_t*) (data + i) = __be32_to_cpu(*(u_int32_t*) (data + i));
    }
    return MFE_OK;
}

int cntx_st_spi_block_read(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, bool verbose)
{
    (void)verbose;
    return cntx_st_spi_block_read_ex(mfl, blk_addr, blk_size, data, 1, 1, false);
}

int cntx_st_spi_block_read_old(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data)
{
    int rc = 0;
    u_int32_t offs = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;

    COM_CHECK_ALIGN(blk_addr, blk_size);

    if (blk_size > (u_int32_t) mfl->attr.block_write || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    // Read the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_READ_OP, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), BO_MSIZE, BS_MSIZE);
    gw_cmd = MERGE(gw_cmd, SFC_READ, HBO_CMD, HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);

    rc = cntx_exec_cmd_get(mfl, gw_cmd, (u_int32_t*) data, (blk_size >> 2), &gw_addr, "Read");
    CHECK_RC(rc);

    // Data:
    for (offs = 0; offs < blk_size; offs += 4) {
        *((u_int32_t*) (data + offs)) = __cpu_to_be32(*((u_int32_t*) (data + offs)));
    }

    return MFE_OK;
}

int cntx_st_spi_page_write(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data)
{
    int rc = 0;

    u_int32_t last_blk_addr = 0;
    u_int32_t last_addr = 0;
    u_int8_t is_first = 1;
    u_int8_t is_last = 0;
    u_int8_t *p = data;

    WRITE_CHECK_ALIGN(addr, mfl->attr.block_write, size);

    last_addr = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr) {
        if (addr == last_blk_addr) {
            is_last = 1;
        }
        rc = cntx_st_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last, size);
        CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p += mfl->attr.block_write;

    }

    return MFE_OK;
}

int cntx_sst_spi_byte_write(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data)
{
    int rc = 0;

    u_int32_t last_addr = 0;
    u_int8_t *p = data;

    WRITE_CHECK_ALIGN(addr, mfl->attr.block_write, size);

    last_addr = addr + size;

    while (addr < last_addr) {
        rc = cntx_sst_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p);
        CHECK_RC(rc);
        addr++;
        p++;
    }

    return MFE_OK;
}

int cntx_st_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data,
                               u_int8_t is_first, u_int8_t is_last, u_int32_t total_size)
{
    int rc = 0;
    u_int32_t offs = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    u_int32_t buff[4];

    if (blk_addr & ((u_int32_t) mfl->attr.block_write - 1)) {
        return MFE_BAD_ALIGN;
    }

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t) mfl->attr.block_write) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), HBO_MSIZE, HBS_MSIZE);

    if (is_first) {
        rc = cntx_st_spi_write_enable(mfl);
        CHECK_RC(rc);

        // Write the data block
        gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, mfl->attr.access_commands.sfc_page_program, HBO_CMD, HBS_CMD);
        gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);
        //printf("-D- gw_addr = %#x, blk_addr = %#x\n", gw_addr, blk_addr);
    }

    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_CS_HOLD, 1);
    }

    // Data:
    for (offs = 0; offs < blk_size; offs += 4) {
        u_int32_t word = zero;

        word = MERGE(word, data[offs + 0], 24, 8);
        word = MERGE(word, data[offs + 1], 16, 8);
        word = MERGE(word, data[offs + 2], 8, 8);
        word = MERGE(word, data[offs + 3], 0, 8);
        //MWRITE4(HCR_FLASH_DATA + offs, word );
        buff[offs / 4] = word;
        //printf("-D- word = %#x, %d\n", word, HBS_CMD);
    }

    rc = cntx_exec_cmd_set(mfl, gw_cmd, buff, (blk_size >> 2), &gw_addr, "PP command");
    CHECK_RC(rc);

    //
    // Wait for end of write in flash (WriteInProgress = 0):
    //

    if (is_last) {
        rc = st_spi_wait_wip(mfl, WRITE_BLOCK_INIT_DELAY + WRITE_ADDITIONAL_BYTE_DELAY * total_size, WRITE_BLOCK_RETRY_DELAY, WRITE_BLOCK_RETRIES);
        CHECK_RC(rc);
    }

    return MFE_OK;
}

int cntx_sst_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data)
{
    int rc = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    u_int32_t word = zero;

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t) mfl->attr.block_write) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0, HBO_MSIZE, HBS_MSIZE);

    rc = cntx_st_spi_write_enable(mfl);
    CHECK_RC(rc);

    // Write the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0x02, HBO_CMD, HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);

    //gw_cmd = MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);

    word = MERGE(word, data[0], 24, 8);

    //printf("-D- data[0] = %#x, gw_addr = %#x, word = %#x, gw_cmd = %#x\n", data[0], gw_addr, word, gw_cmd);

    rc = cntx_exec_cmd_set(mfl, gw_cmd, &word, 1, &gw_addr, "PB command");
    CHECK_RC(rc);

    rc = st_spi_wait_wip(mfl, 0, 0, 50000);
    CHECK_RC(rc); // Full throttle polling - no cpu optimization for this flash

    return MFE_OK;
}

int cntx_st_spi_block_write(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data)
{
    return cntx_st_spi_block_write_ex(mfl, blk_addr, blk_size, data, 1, 1, blk_size);
}

int cntx_st_spi_erase_sect(mflash *mfl, u_int32_t addr)
{
    int rc = 0;

    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    rc = set_bank(mfl, addr);
    CHECK_RC(rc);

    rc = cntx_st_spi_write_enable(mfl);
    CHECK_RC(rc);

    // Erase sector command:
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, mfl->attr.erase_command, HBO_CMD, HBS_CMD);

    gw_addr = addr & ONES32(mfl->attr.log2_bank_size);

    // printf("-D- cntx_st_spi_erase_sect: addr = %#x, gw_cmd = %#x.\n", addr, gw_cmd);

    rc = cntx_exec_cmd_set(mfl, gw_cmd, (u_int32_t*) NULL, 0, &gw_addr, "ES");
    CHECK_RC(rc);

    // Wait for erase completion
    rc = st_spi_wait_wip(mfl, ERASE_SUBSECTOR_INIT_DELAY, ERASE_SUBSECTOR_RETRY_DELAY, ERASE_SUBSECTOR_RETRIES);
    CHECK_RC(rc);
    return MFE_OK;
}

f_mf_write get_write_blk_func(int command_set)
{
    if (command_set == MCS_STSPI) {
        return cntx_st_spi_page_write;
    }
    return cntx_sst_spi_byte_write;
}

int old_flash_lock(mflash *mfl, int lock_state)
{

    // Obtain GPIO Semaphore
    static u_int32_t cnt;
    u_int32_t word = 0;
#if !defined(UEFI_BUILD)
    if (IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id) && mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_NO) {
        int rc = 0;
        if (lock_state) {
            if (!mfl->flash_prog_locked) {
                rc = trm_lock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING, MAX_FLASH_PROG_SEM_RETRY_CNT);
                if (!rc) {
                    mfl->flash_prog_locked = 1;
                }
            }
        } else {
            if (mfl->unlock_flash_prog_allowed) {
                rc = trm_unlock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING);
                if (!rc) {
                    mfl->flash_prog_locked = 0;
                }
            }
        }
        if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
            return MFE_SEM_LOCKED;
        }
    }
#endif // !defined(UEFI)
    // timeout at 5 seconds
    TIMER_INIT_AND_START();

    if (lock_state) {
        if (mfl->is_locked) {
            return MFE_OK;
        }
        do {
            if (++cnt > GPIO_SEM_TRIES) {
                cnt = 0;
                //printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(SEMAP63, &word);
            if (word) {
                msleep(1);
            }
            TIMER_CHECK(5, 0, cnt = 0; return MFE_SEM_LOCKED);
        } while (word);
    } else {
        MWRITE4(SEMAP63, 0);
        if (cnt > 1) {
            // we are not alone...
            msleep(1);
        }
        cnt = 0;
    }
    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}

int cntx_flash_init_direct_access(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;
    u_int32_t tmp = 0;

    // Without too much details:
    // When the ConnectX boots up without a valid FW , the PCIE link may be unstable.
    // In that case, turn off the auto reset on link down, so we'll be able to burn the device.
    MREAD4(0x41270, &tmp);
    if (tmp > 0xfff00000) {
        //we are in livefish.
        u_int32_t tmp1 = 0;
        MREAD4(0xf3834, &tmp1);
        tmp1 = MERGE(tmp1, 2, 27, 2);
        MWRITE4(0xf3834, tmp1);

    }

    //TODO: Enable page_read (slightly better perf)
    //mfl->f_read           = cntx_st_spi_page_read;
    mfl->f_read = read_chunks;
    mfl->f_read_blk = cntx_st_spi_block_read;
    mfl->f_lock = old_flash_lock; // Flash lock has same address and functionality as in InfiniHost.
    mfl->f_set_bank = empty_set_bank;
    mfl->f_get_info = cntx_get_flash_info;
    mfl->unlock_flash_prog_allowed = 0;
    //if (is_life_fish) {
    //    rc = cntx_init_gpios(mfl);  CHECK_RC(rc);
    //}

    mfl->f_spi_status = cntx_st_spi_get_status;
    mfl->supp_sr_mod = 1;

    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);

    if (mfl->attr.command_set == MCS_STSPI || mfl->attr.command_set == MCS_SSTSPI) {
        mfl->f_reset = empty_reset; // Null func
        mfl->f_write_blk = get_write_blk_func(mfl->attr.command_set);

        mfl->attr.page_write = 256;
        mfl->f_write = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    // flash parameter access methods:
    mfl->f_get_quad_en = mf_get_quad_en_direct_access;
    mfl->f_set_quad_en = mf_set_quad_en_direct_access;
    mfl->f_get_dummy_cycles = mf_get_dummy_cycles_direct_access;
    mfl->f_set_dummy_cycles = mf_set_dummy_cycles_direct_access;
    mfl->f_get_write_protect = mf_get_write_protect_direct_access;
    mfl->f_set_write_protect = mf_set_write_protect_direct_access;
    rc = mfl->f_reset(mfl);
    return MFE_OK;
}

// InfiniScale 4 (IS4) functions:

int is4_init_gpios(mflash *mfl)
{
    (void) mfl;
    return MFE_NOT_IMPLEMENTED;
}

int is4_flash_lock(mflash *mfl, int lock_state)
{
    // Obtain GPIO Semaphore
    static u_int32_t cnt;
    u_int32_t word = 0;
    u_int32_t lock_status = 0;

    // timeout at 5 seconds
    TIMER_INIT_AND_START();

    if (lock_state) {
        do {
            if (++cnt > GPIO_SEM_TRIES) {
                cnt = 0;
                //printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(HCR_FLASH_CMD, &word);
            lock_status = EXTRACT(word, HBO_LOCK, 1);
            if (lock_status) {
                msleep(1);
            }
            TIMER_CHECK(5, 0, cnt = 0; return MFE_SEM_LOCKED);
        } while (lock_status);
    } else {
        MWRITE4(HCR_FLASH_CMD, 0);
        if (cnt > 1) {
            // we are not alone
            msleep(1);
        }
        cnt = 0;
    }

    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}

#define CACHE_REPLACEMNT_EN_ADDR 0xf0420
int disable_cache_replacement(mflash *mfl)
{
    u_int32_t data = 0;
    MREAD4(CACHE_REPLACEMNT_EN_ADDR, &data);
    data = MERGE(data, 0, 0, 1); // We put 0 in the first bit of the read data
    MWRITE4(CACHE_REPLACEMNT_EN_ADDR, data);

    return 0;
}

int restore_cache_replacemnt(mflash *mfl)
{
    u_int32_t data = 0;
    MREAD4(CACHE_REPLACEMNT_EN_ADDR, &data);
    data = MERGE(data, 1, 0, 1); // We put 1 in the first bit of the read data
    MWRITE4(CACHE_REPLACEMNT_EN_ADDR, data);
    return MFE_OK;
}

int connectib_flash_lock(mflash *mfl, int lock_state)
{
    int rc = 0;
    if (lock_state == 1) { // lock the flash
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
        rc = disable_cache_replacement(mfl);
        CHECK_RC(rc);
        rc = gw_wait_ready(mfl, "WAIT TO BUSY");
        CHECK_RC(rc);
    } else { // unlock the flash
        rc = restore_cache_replacemnt(mfl);
        CHECK_RC(rc);
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

#define SX_CS_SUPPORT_ADDR 0xF0420

int sx_init_cs_support(mflash *mfl)
{
    if (IS_SX(mfl->attr.hw_dev_id)) {
        u_int8_t cs_support_mask = 0;
        u_int32_t data = 0;
        if (mfl->opts[MFO_USER_BANKS_NUM] == 0) {
            // We assume we have only 2 flashes on SX
            mfl->opts[MFO_NUM_OF_BANKS] = 2;
        }
        // Prepare the bit mask of the banks number
        cs_support_mask = (1 << mfl->opts[MFO_NUM_OF_BANKS]) - 1;

        // Read Modify write the cs support field
        MREAD4(SX_CS_SUPPORT_ADDR, &data);
        data = MERGE(data, cs_support_mask, 0, 4);
        MWRITE4(SX_CS_SUPPORT_ADDR, data);
    }
    return 0;
}

#define HW_DEV_ID      0xf0014
#define CACHE_REP_OFF  0xf0408
#define CASHE_REP_CMD  0xf040c
#define CX5_EFUSE_ADDR 0xf0c0c

#define CACHE_REP_OFF_RAVEN  0xf0440
#define CACHE_REP_CMD_RAVEN  0xf0448
int check_cache_replacement_guard(mflash *mfl, u_int8_t *needs_cache_replacement)
{

    *needs_cache_replacement = 0;

    // When we access via command interface, we assume there is a cache replacement!
    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF) {
        if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD]) {
            // dont allow overidding cache replacement in mellanox OS env
            return MFE_OCR_NOT_SUPPORTED;
        }
        *needs_cache_replacement = 1;
        return MFE_OK;
    }

    if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0) {
        u_int32_t off = 0, cmd = 0, data = 0;
        dm_dev_id_t devid_t = DeviceUnknown;
        u_int32_t devid = 0;
        u_int32_t revid = 0;
        int rc = dm_get_device_id(mfl->mf, &devid_t, &devid, &revid);
        if (rc) {
            return rc;
        }
        
        // Read the Cache replacement offset
        if (!dm_dev_is_raven_family_switch(devid_t)) {
        MREAD4(CACHE_REP_OFF, &data);
        off = EXTRACT(data, 0, 26);
        // Read the Cache replacement cmd
        MREAD4(CASHE_REP_CMD, &data);
        cmd = EXTRACT(data, 16, 8);
        }
        else {//RAVEN switches
            MREAD4(CACHE_REP_OFF_RAVEN, &data);
            off = EXTRACT(data, 0, 26);
            MREAD4(CACHE_REP_CMD_RAVEN, &data);
            cmd = EXTRACT(data, 16, 8);
        }
        // Check if the offset and cmd are zero in order to continue burning.
        if (cmd != 0 || off != 0) {
            *needs_cache_replacement = 1;
        }
    } else {
        // Here we ignore the cache replacement check
        // We need to execute a write in order to do any needed cache replacement
        // Reset the HW ID which is read only register.
        MWRITE4(HW_DEV_ID, 0);
    }

    return MFE_OK;
}

int mfl_com_lock(mflash *mfl)
{
    int rc = 0;
    // if we already locked the semaphore we dont want to re-lock it
    if (mfl->is_locked && (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_INBAND || mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 1)) { // on inband w/o ocr we need to extend the lock
        return MFE_OK;
    }
    rc = mfl->f_lock(mfl, 1);
    if (!mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        CHECK_RC(rc);
    } else {
        mfl->is_locked = 1;
        mfl->unlock_flash_prog_allowed = 1;
    }
    return MFE_OK;
}

int mf_release_semaphore(mflash *mfl)
{
    return release_semaphore(mfl, 1);
}

int release_semaphore(mflash *mfl, int ignore_writer_lock)
{
    int rc = 0;
    if ((mfl->is_locked || mfl->flash_prog_locked) && mfl->f_lock && (!mfl->writer_lock || ignore_writer_lock)) {
        rc = mfl->f_lock(mfl, 0);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

// ConnectX and Is4 flash interfaces are identical (except lock function)
// Use same functions
//
// TODO: Unify fith ConnectX inif function

int gen4_flash_init_com(mflash *mfl, flash_params_t *flash_params, u_int8_t init_cs_support)
{

    int rc = 0;

    //TODO: Enable page_read (slightly better perf)
    //mfl->f_read           = cntx_st_spi_page_read;
    mfl->f_read = read_chunks;
    mfl->f_read_blk = cntx_st_spi_block_read;
    mfl->f_set_bank = empty_set_bank;
    mfl->f_get_info = cntx_get_flash_info;

    if (init_cs_support) {
        // Update the chip_select_support according to the banks number of cs.
        rc = sx_init_cs_support(mfl);
        CHECK_RC(rc);
    }

    mfl->f_spi_status = cntx_st_spi_get_status;
    mfl->supp_sr_mod = 1;
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);

    if (mfl->attr.command_set == MCS_STSPI || mfl->attr.command_set == MCS_SSTSPI) {
        mfl->f_reset = empty_reset; // Null func
        //mfl->f_write_blk  = cntx_st_spi_block_write;

        mfl->f_write_blk = get_write_blk_func(mfl->attr.command_set);

        mfl->attr.page_write = 256;
        mfl->f_write = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    // flash parameter access methods:
    mfl->f_get_quad_en = mf_get_quad_en_direct_access;
    mfl->f_set_quad_en = mf_set_quad_en_direct_access;
    mfl->f_get_dummy_cycles = mf_get_dummy_cycles_direct_access;
    mfl->f_set_dummy_cycles = mf_set_dummy_cycles_direct_access;
    mfl->f_get_write_protect = mf_get_write_protect_direct_access;
    mfl->f_set_write_protect = mf_set_write_protect_direct_access;

    rc = mfl->f_reset(mfl);

    return MFE_OK;
}

int is4_flash_init(mflash *mfl, flash_params_t *flash_params)
{
    mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
    mfl->f_lock = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 0);
}

int sx_flash_init_direct_access(mflash *mfl, flash_params_t *flash_params)
{
    mfl->f_lock = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 1);
}

int fifth_gen_init_direct_access(mflash *mfl, flash_params_t *flash_params)
{
    mfl->f_lock = connectib_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 0);
}

/*
         typedef int (*f_sx_flash_lock)      (mflash* mfl, int lock_state);
         typedef int (*f_sx_erase_sect)      (mflash* mfl, u_int32_t addr);
         typedef int (*f_sx_block_access)    (mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data);
         typedef int (*f_sx_get_flash_info)  (mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash);
 */

int sx_get_flash_info(mflash *mfl, flash_info_t *f_info, int *log2size, u_int8_t *no_flash)
{
    int rc = 0;
    int sem_rc = 0;
    sem_rc = mfl_com_lock(mfl);
    CHECK_RC(sem_rc);
    rc = sx_get_flash_info_by_type(mfl, f_info, log2size, no_flash);
    sem_rc = release_semaphore(mfl, 0);
    CHECK_RC(sem_rc);
    return rc;
}

int sx_block_read(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data, bool verbose)
{
    (void)verbose;
    int rc = 0;
    int sem_rc = 0;
    sem_rc = mfl_com_lock(mfl);
    CHECK_RC(sem_rc);
    rc = sx_block_read_by_type(mfl, blk_addr, blk_size, data);
    sem_rc = release_semaphore(mfl, 0);
    CHECK_RC(sem_rc);
    return rc;
}

int sx_block_write(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data)
{
    int rc = 0;
    int sem_rc = 0;
    sem_rc = mfl_com_lock(mfl);
    CHECK_RC(sem_rc);
    rc = sx_block_write_by_type(mfl, addr, size, data);
    sem_rc = release_semaphore(mfl, 0);
    CHECK_RC(sem_rc);
    return rc;
}

int sx_flash_lock(mflash *mfl, int lock_state)
{
    return sx_flash_lock_by_type(mfl, lock_state);
}

int sx_erase_sect(mflash *mfl, u_int32_t addr)
{
    int rc = 0;
    int sem_rc = 0;
    sem_rc = mfl_com_lock(mfl);
    CHECK_RC(sem_rc);
    rc = sx_erase_sect_by_type(mfl, addr, mfl->attr.sector_size);
    sem_rc = release_semaphore(mfl, 0);
    CHECK_RC(sem_rc);
    return rc;
}

int empty_get_status(mflash *mfl, u_int8_t op_type, u_int8_t *status)
{
    // Avoid warnings
    (void) mfl;
    (void) op_type;
    (void) status;

    return MFE_NOT_SUPPORTED_OPERATION;
}

#define MAX_BLOCK_SIZE(hw_dev_id) \
    (((hw_dev_id) == CX3_HW_ID || hw_dev_id == CX3_PRO_HW_ID) ? MAX_WRITE_BUFFER_SIZE : 128)

static int update_max_write_size(mflash *mfl)
{
    u_int32_t max_reg_size = mget_max_reg_size(mfl->mf, MACCESS_REG_METHOD_SET);
    u_int32_t max_block_size = MAX_BLOCK_SIZE(mfl->attr.hw_dev_id);
    if (!max_reg_size) {
        return MFE_BAD_PARAMS;
    }
    max_reg_size = NEAREST_POW2(max_reg_size);
    // limit maximal write to max_block_size
    max_block_size = max_reg_size < max_block_size ? max_reg_size : max_block_size;
    mfl->attr.block_write = max_block_size;
    mfl->attr.page_write = max_block_size;
    return ME_OK;
}

// access flash via FW using Flash Access Registers (either by INBAND/ICMD/TOOLS_HCR)
int flash_init_inband_access(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;

    mfl->f_read = read_chunks;
    mfl->f_write = write_chunks;
    mfl->f_reset = empty_reset;
    mfl->f_set_bank = empty_set_bank;

    mfl->f_get_info = sx_get_flash_info;
    mfl->f_lock = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk = sx_block_write;
    mfl->f_read_blk = sx_block_read;
    mfl->f_spi_status = empty_get_status;

    mfl->supp_sr_mod = 0;

    // flash parameter access methods:
    mfl->f_get_quad_en = sx_get_quad_en;
    mfl->f_set_quad_en = sx_set_quad_en;
    mfl->f_get_dummy_cycles = sx_get_dummy_cycles;
    mfl->f_set_dummy_cycles = sx_set_dummy_cycles;
    mfl->f_get_write_protect = sx_get_write_protect;
    mfl->f_set_write_protect = sx_set_write_protect;

    // Get the flash attribute
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);
    update_max_write_size(mfl);
    CHECK_RC(rc);
    return MFE_OK;
}

int uefi_flash_init(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;

    mfl->f_read = read_chunks;
    mfl->f_write = write_chunks;
    mfl->f_reset = empty_reset;
    mfl->f_set_bank = empty_set_bank;

    mfl->f_get_info = sx_get_flash_info;
    mfl->f_lock = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk = sx_block_write;
    mfl->f_read_blk = sx_block_read;
    mfl->f_spi_status = empty_get_status;

    mfl->supp_sr_mod = 0;

    // flash parameter access methods:
    mfl->f_get_quad_en = sx_get_quad_en;
    mfl->f_set_quad_en = sx_set_quad_en;
    mfl->f_get_dummy_cycles = sx_get_dummy_cycles;
    mfl->f_set_dummy_cycles = sx_set_dummy_cycles;
    mfl->f_get_write_protect = sx_get_write_protect;
    mfl->f_set_write_protect = sx_set_write_protect;
    // Get the flash attribute

    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);
    update_max_write_size(mfl);
    CHECK_RC(rc);
    return MFE_OK;
}

int flash_init_fw_access(mflash *mfl, flash_params_t *flash_params)
{
    // This function checks the access type in order to select the access functions

    int rc = 0;
    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_NO) {
        rc = flash_init_inband_access(mfl, flash_params);
        CHECK_RC(rc);
    } else {
        return MFE_DIRECT_FW_ACCESS_DISABLED;
    }

    if (mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        rc = mfl->f_lock(mfl, 0);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int sx_flash_init(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;
    u_int8_t needs_cache_replacement = 0;

    rc = check_cache_replacement_guard(mfl, &needs_cache_replacement);
    CHECK_RC(rc);

    if (needs_cache_replacement) {
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    } else {
        rc = sx_flash_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int icmd_init(mflash *mfl)
{
    // Clear  semaphore when asked to by flint or any tool using mflash
    if (mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        if (icmd_clear_semaphore(mfl->mf) != ME_OK) {
            return MFE_CR_ERROR;
        }
    }
    return MFE_OK;
}

int tools_cmdif_init(mflash *mfl)
{
    // Clear  semaphore when asked to by flint or any tool using mflash
    if (mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        if (tools_cmdif_unlock_semaphore(mfl->mf) != ME_OK) {
            return MFE_CR_ERROR;
        }
    }
    return MFE_OK;
}

int fifth_gen_flash_init(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;
    u_int8_t needs_cache_replacement = 0;

    rc = check_cache_replacement_guard(mfl, &needs_cache_replacement);
    CHECK_RC(rc);

    if (needs_cache_replacement) {
        if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD) {
            rc = icmd_init(mfl);
            CHECK_RC(rc);
        }
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    } else {
        rc = fifth_gen_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int cntx_flash_init(mflash *mfl, flash_params_t *flash_params)
{
    int rc = 0;

    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_TOOLS_CMDIF && mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0 && mfl->opts[MFO_CX3_FW_ACCESS_EN]) {
#ifdef UEFI_BUILD
        // tools CMDIF not supported in UEFI
        rc = ME_NOT_IMPLEMENTED;
#else
        rc = tcif_cr_mbox_supported(mfl->mf);
#endif
        // init with direct access if not supported
        if (rc == ME_NOT_IMPLEMENTED || rc == ME_CMDIF_NOT_SUPP) {
            mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
            return cntx_flash_init_direct_access(mfl, flash_params);
        }
        if (rc == ME_SEM_LOCKED && !mfl->opts[MFO_IGNORE_SEM_LOCK]) {
            return MFE_SEM_LOCKED;
        }
        rc = tools_cmdif_init(mfl);
        CHECK_RC(rc);
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    } else {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
        rc = cntx_flash_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

//
// Interface functions:
//

#define CHECK_OUT_OF_RANGE(addr, len, size) { \
        if (addr > size || addr + len > size) { \
            return MFE_OUT_OF_RANGE; \
        } \
}

int mf_read(mflash *mfl, u_int32_t addr, u_int32_t len, u_int8_t *data, bool verbose)
{
    // printf("mfl->attr.size = %#x, addr = %#x, len = %d\n", mfl->attr.size, addr, len);

    CHECK_OUT_OF_RANGE(addr, len, mfl->attr.size);
    //printf("-D- mf_read:  addr: %#x, len: %d\n", addr, len);
    return mfl->f_read(mfl, addr, len, data, verbose);
}

int mf_write(mflash *mfl, u_int32_t addr, u_int32_t len, u_int8_t *data)
{
    CHECK_OUT_OF_RANGE(addr, len, mfl->attr.size);
    // Locking semaphore for the entire existence of the mflash obj for write and erase only.
    int rc = mfl_com_lock(mfl);
    CHECK_RC(rc);
    mfl->writer_lock = 1;
    return mfl->f_write(mfl, addr, len, data);
}

static int erase_com(mflash *mfl, u_int32_t addr, unsigned int sector_size, int erase_cmd)
{
    int rc = 0;
    u_int32_t backup_sector_size = 0;
    int backup_erase_command = 0;
    if (addr >= mfl->attr.size) {
        return MFE_OUT_OF_RANGE;
    }
    // Locking semaphore for the entire existence of the mflash obj for write and erase only.
    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);
    mfl->writer_lock = 1;
    backup_sector_size = mfl->attr.sector_size;
    backup_erase_command = mfl->attr.erase_command;
    mfl->attr.sector_size = sector_size;
    mfl->attr.erase_command = erase_cmd;
    rc = mfl->f_erase_sect(mfl, addr);
    mfl->attr.sector_size = backup_sector_size;
    mfl->attr.erase_command = backup_erase_command;
    return rc;
}

int mf_erase(mflash *mfl, u_int32_t addr)
{
    return erase_com(mfl, addr, mfl->attr.sector_size, mfl->attr.erase_command);
}

int mf_erase_64k_sector(mflash *mfl, u_int32_t addr)
{
    if (!mfl->attr.support_sub_and_sector) {
        return MFE_UNSUPPORTED_ERASE_OPERATION;
    }
    return erase_com(mfl, addr, FSS_64KB, mfl->attr.access_commands.sfc_sector_erase);
}

int mf_erase_4k_sector(mflash *mfl, u_int32_t addr)
{
    if (!mfl->attr.support_sub_and_sector) {
        return MFE_UNSUPPORTED_ERASE_OPERATION;
    }
    return erase_com(mfl, addr, FSS_4KB, mfl->attr.access_commands.sfc_subsector_erase);
}

int mf_open_ignore_lock(mflash *mfl)
{
    mfl->opts[MFO_IGNORE_SEM_LOCK] = 1;
    return mf_open_fw(mfl, (flash_params_t*) NULL, -1);
}

#define CR_LOCK_HW_ID 0xbad0cafe

#ifndef MST_UL
#define IS_PCI_DEV(access_type) (access_type == MST_PCICONF || access_type == MST_PCI)
#else
#define IS_PCI_DEV(access_type) (access_type == MTCR_ACCESS_CONFIG || access_type == MTCR_ACCESS_MEMORY)
#endif

BinIdT get_bin_id(mflash *mfl, u_int32_t hw_dev_id)
{
    u_int32_t dword = 0;
    if (hw_dev_id == CX5_HW_ID) {
        if (mread4(mfl->mf, CX5_EFUSE_ADDR, &dword) == 4) {
            u_int8_t bin_speed = EXTRACT(dword, 30, 2);
            if (bin_speed == 0) {
                return CX5_LOW_BIN;
            } else if (bin_speed == 1) {
                return CX5_HIGH_BIN;
            }
        }
    }
    return UNKNOWN_BIN;
}

int get_dev_info(mflash *mfl)
{
    u_int32_t dev_flags = 0;
    u_int32_t access_type = 0;
    int rc = 0;
    u_int32_t dev_id = 0;
    mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
    rc = mget_mdevs_flags(mfl->mf, &dev_flags);
    CHECK_RC(rc);
    rc = mget_mdevs_type(mfl->mf, &access_type);
    CHECK_RC(rc);

    MfError status;
    int icmdif_supported = is_icmdif_supported(mfl, &status);
    if (status != MFE_OK) {
        return status;
    }

    mfl->attr.bin_id = UNKNOWN_BIN;
    // get hw id
    // Special case for MLNX OS getting dev_id using REG MGIR
    if (dev_flags & MDEVS_MLNX_OS) {
#ifndef UEFI_BUILD
        reg_access_status_t rc;
        struct reg_access_hca_mgir mgir;
        memset(&mgir, 0, sizeof(mgir));
        rc = reg_access_mgir(mfl->mf, REG_ACCESS_METHOD_GET, &mgir);
        //printf("-D- RC[%s] -- REVID: %d -- DEVID: %d hw_dev_id: %d\n", m_err2str(rc), mgir.HWInfo.REVID, mgir.HWInfo.DEVID, mgir.HWInfo.hw_dev_id);
        if (rc) {
            dev_id = SWITCHX_HW_ID;
            mfl->attr.rev_id = 0;
            mfl->attr.hw_dev_id = SWITCHX_HW_ID;
        } else {
            dev_id = mgir.hw_info.hw_dev_id;
            if (dev_id == 0) {
                dev_id = SWITCHX_HW_ID;
                mfl->attr.hw_dev_id = SWITCHX_HW_ID;
                mfl->attr.rev_id = mgir.hw_info.device_hw_revision & 0xf;
            } else {
                mfl->attr.hw_dev_id = dev_id;
                mfl->attr.rev_id = 0; //WA: MGIR should have also hw_rev_id and then we can use it.
            }
        }
#else
        // no MLNX_OS in UEFI, no mgir register in UEFI package
        // we should never reach here
        return MFE_UNKOWN_ACCESS_TYPE;
#endif
    } else {
        MREAD4(HW_DEV_ID, &dev_id);
        if (dev_id == CR_LOCK_HW_ID) {
            return MFE_LOCKED_CRSPACE;
        }
        mfl->attr.rev_id = (dev_id & 0xff0000) >> 16;
        mfl->attr.hw_dev_id = dev_id & 0xffff;
        mfl->attr.bin_id = get_bin_id(mfl, mfl->attr.hw_dev_id);

        if (icmdif_supported) {
            int mode = 0;
            if (!mf_get_secure_host(mfl, &mode) && mode) {
                return MFE_LOCKED_CRSPACE;
            }
        }
    }

    if (dev_flags & MDEVS_MLNX_OS) {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_MLNXOS_CMDIF;
    } else if (dev_flags & MDEVS_IB) {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_INBAND;
    } else { // not mlnxOS or IB device - check HW ID to determine Access type
        if (icmdif_supported) {
            if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0) {
                mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_ICMD;
            }
        } else if (HAS_TOOLS_CMDIF(mfl->attr.hw_dev_id) && (IS_PCI_DEV(access_type))) {
            if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0) {
                mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_TOOLS_CMDIF;
            }
        }
    }
    return MFE_OK;

}
//Caller must zero the mflash struct before calling this func.
int mf_open_fw(mflash *mfl, flash_params_t *flash_params, int num_of_banks)
{
    int rc = 0;
    if (!mfl) {
        return MFE_BAD_PARAMS;
    }
    rc = set_bank_int(mfl, -1);
    CHECK_RC(rc);
    if (mfl->access_type == MFAT_MFILE) {
        rc = get_dev_info(mfl);
        CHECK_RC(rc);

#ifndef UEFI_BUILD
        trm_sts trm_rc;
        trm_rc = trm_create(&(mfl->trm), mfl->mf);
        if (trm_rc) {
            return trm2mfe_err(trm_rc);
        }
#endif

        mfl->opts[MFO_NUM_OF_BANKS] = spi_get_num_of_flashes(num_of_banks);
        rc = spi_update_num_of_banks(mfl, num_of_banks);
        CHECK_RC(rc);

        MfError status;
        int icmdif_supported = is_icmdif_supported(mfl, &status);
        if (status != MFE_OK) {
            return status;
        }

        if (IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id)) {
            rc = cntx_flash_init(mfl, flash_params);
        } else if (IS_IS4_FAMILY(mfl->attr.hw_dev_id)) {
            rc = is4_flash_init(mfl, flash_params);
        } else if (IS_SX(mfl->attr.hw_dev_id)) {
            rc = sx_flash_init(mfl, flash_params);
        } else if (icmdif_supported) {
            rc = fifth_gen_flash_init(mfl, flash_params);
        } else if (mfl->attr.hw_dev_id == 0xffff) {
            rc = MFE_HW_DEVID_ERROR;
        } else {
            rc = MFE_UNSUPPORTED_DEVICE;
        }
        CHECK_RC(rc);
    } else if (mfl->access_type == MFAT_UEFI) {
        mfl->opts[MFO_NUM_OF_BANKS] = 1; // We have only one flash in ConnectIB and ConnectX-3 - Need to specify it better!
        rc = uefi_flash_init(mfl, flash_params);
        CHECK_RC(rc);
    } else {
        return MFE_UNKOWN_ACCESS_TYPE;
    }
    mfl->f_set_bank(mfl, 0);
    return MFE_OK;
}

int mf_opend_int(mflash **pmfl, void *access_dev, int num_of_banks, flash_params_t *flash_params,
                 int ignore_cache_rep_guard, u_int8_t access_type, void *dev_extra, int cx3_fw_access)
{
    int rc = 0;
    *pmfl = (mflash*) malloc(sizeof(mflash));
    if (!*pmfl) {
        return MFE_NOMEM;
    }

    memset(*pmfl, 0, sizeof(mflash));

    (*pmfl)->opts[MFO_IGNORE_CASHE_REP_GUARD] = ignore_cache_rep_guard;
    (*pmfl)->opts[MFO_CX3_FW_ACCESS_EN] = cx3_fw_access;
    (*pmfl)->access_type = access_type;
    if (access_type == MFAT_MFILE) {
        (*pmfl)->mf = (mfile*) access_dev;
        u_int32_t dev_id;
        u_int32_t chip_rev;
        rc = dm_get_device_id((*pmfl)->mf, &((*pmfl)->dm_dev_id), &dev_id, &chip_rev);
        CHECK_RC(rc);
    } 
    else if (access_type == MFAT_UEFI) {
        // open mfile as uefi
        if (!((*pmfl)->mf = mopen_fw_ctx(access_dev, ((uefi_dev_extra_t*) dev_extra)->fw_cmd_func, &((uefi_dev_extra_t*) dev_extra)->dev_info))) {
            return MFE_NOMEM;
        }
        // fill some device information
        if (&((uefi_dev_extra_t*) dev_extra)->dev_info) {
            (*pmfl)->attr.hw_dev_id = ((uefi_dev_extra_t*) dev_extra)->dev_info.hw_dev_id;
            (*pmfl)->attr.rev_id = ((uefi_dev_extra_t*) dev_extra)->dev_info.rev_id;
            rc = dm_get_device_id_offline((*pmfl)->attr.hw_dev_id, (*pmfl)->attr.rev_id, &((*pmfl)->dm_dev_id));
            CHECK_RC(rc);
        } else {
            (*pmfl)->dm_dev_id = DeviceUnknown;
        }
    }
    rc = mf_open_fw(*pmfl, flash_params, num_of_banks);
    return rc;
}

//int mf_opend(mflash **pmfl, struct mfile_t *mf, int num_of_banks, flash_params_t *flash_params,
//             int ignore_cache_rep_guard)
//{
//    return mf_opend_int(pmfl, mf, num_of_banks, flash_params, ignore_cache_rep_guard, MFAT_MFILE, NULL, 0);
//}

int mf_open_uefi(mflash **pmfl, uefi_Dev_t *uefi_dev, uefi_dev_extra_t *uefi_dev_extra)
{

    return mf_opend_int(pmfl, (void*)uefi_dev, 4, (flash_params_t*) NULL, 0, MFAT_UEFI, (void*)uefi_dev_extra, 0);
}

int mf_open_int(mflash **pmfl, const char *dev, int num_of_banks, flash_params_t *flash_params,
                int ignore_cache_rep_guard, int cx3_fw_access)
{
    mfile *mf;

    int rc = 0;

    if (!dev) {
        return MFE_BAD_PARAMS;
    }

    mf = mopen(dev);

    if (!mf) {
        return MFE_CR_ERROR;
    }

    rc = mf_opend_int(pmfl, (struct mfile_t*) mf, num_of_banks, flash_params, ignore_cache_rep_guard, MFAT_MFILE, NULL, cx3_fw_access);
    if ((*pmfl)) {
        (*pmfl)->opts[MFO_CLOSE_MF_ON_EXIT] = 1;
    }
    CHECK_RC(rc);
    return MFE_OK;
}

int mf_open_adv(mflash **pmfl, const char *dev, int num_of_banks, flash_params_t *flash_params,
                int ignore_cache_rep_guard, int cx3_fw_access)
{
    return mf_open_int(pmfl, dev, num_of_banks, flash_params, ignore_cache_rep_guard, cx3_fw_access);
}

int mf_open(mflash **pmfl, const char *dev, int num_of_banks, flash_params_t *flash_params,
            int ignore_cache_rep_guard)
{
    return mf_open_int(pmfl, dev, num_of_banks, flash_params, ignore_cache_rep_guard, 0);
}

void mf_close(mflash *mfl)
{
    if (!mfl) {
        return;
    }

    if (mfl->f_reset) {
        mfl->f_reset(mfl);
    }

    if (mfl->f_set_bank) {
        (void) set_bank(mfl, 0);
    }
    mfl->unlock_flash_prog_allowed = 1;
    // we release if we have writer_lock or not doesnt matter on close ...
    release_semaphore(mfl, 1);

    if (mfl->mf && (mfl)->opts[MFO_CLOSE_MF_ON_EXIT]) {
        mclose(mfl->mf);
    }
#ifndef UEFI_BUILD
    if (mfl->trm) {
        trm_destroy(mfl->trm);
        mfl->trm = (trm_ctx) NULL;
    }
#endif
    free(mfl);
    return;
}

int mf_get_attr(mflash *mfl, flash_attr *attr)
{
    *attr = mfl->attr;
    return MFE_OK;
}

int mf_sw_reset(mflash *mfl)
{
    MfError status;
    int supports_sw_reset = is_supports_sw_reset(mfl, &status);
    if (status != MFE_OK) {
        return status;
    }
    if (!supports_sw_reset) {
        return MFE_UNSUPPORTED_DEVICE;
    }
    if (msw_reset(mfl->mf)) {
        if (errno == EPERM) {
            return MFE_CMD_SUPPORTED_INBAND_ONLY;
        } else if (errno == OP_NOT_SUPPORTED) {
            return MFE_MANAGED_SWITCH_NOT_SUPPORTED;
        } else {

            return MFE_ERROR;
        }
    }

    return MFE_OK;
}

const char* mf_err2str(int err_code)
{

    switch (err_code) {
    case MFE_OK:
        return "MFE_OK";

    case MFE_ERROR:
        return "MFE_GENERAL_ERROR";

    case MFE_BAD_PARAMS:
        return "MFE_BAD_PARAMS";

    case MFE_CR_ERROR:
        return "MFE_CR_ERROR";

    case MFE_HW_DEVID_ERROR:
        return "Read a corrupted device id (0xffff). Probably HW/PCI access problem.";

    case MFE_INVAL:
        return "MFE_INVAL";

    case MFE_NOT_IMPLEMENTED:
        return "MFE_NOT_IMPLEMENTED";

    case MFE_UNSUPPORTED_FLASH_TOPOLOGY:
        return "MFE_UNSUPPORTED_FLASH_TOPOLOGY";

    case MFE_UNSUPPORTED_FLASH_TYPE:
        return "MFE_UNSUPPORTED_FLASH_TYPE";

    case MFE_CFI_FAILED:
        return "MFE_CFI_FAILED";

    case MFE_TIMEOUT:
        return "MFE_TIMEOUT";

    case MFE_ERASE_TIMEOUT:
        return "MFE_ERASE_TIMEOUT";

    case MFE_WRITE_TIMEOUT:
        return "MFE_WRITE_TIMEOUT";

    case MFE_ERASE_ERROR:
        return "MFE_ERASE_ERROR";

    case MFE_WRITE_ERROR:
        return "MFE_WRITE_ERROR";

    case MFE_BAD_ALIGN:
        return "MFE_BAD_ALIGN";

    case MFE_SEM_LOCKED:
        return "MFE_SEM_LOCKED";

    case MFE_VERIFY_ERROR:
        return "MFE_VERIFY_ERROR";

    case MFE_NOMEM:
        return "MFE_NOMEM";

    case MFE_OUT_OF_RANGE:
        return "MFE_OUT_OF_RANGE";

    case MFE_CMD_SUPPORTED_INBAND_ONLY:
        return "Command supported over IB interface only.";

    case MFE_NO_FLASH_DETECTED:
        return "MFE_NO_FLASH_DETECTED";

    case MFE_LOCKED_CRSPACE:
        return "MFE_HW_ACCESS_DISABLED";

    case MFE_CMDIF_BAD_STATUS_ERR:
        return "MFE_CMDIF_BAD_STATUS_ERR";

    case MFE_CMDIF_TIMEOUT_ERR:
        return "MFE_CMDIF_TIMEOUT_ERR";

    case MFE_CMDIF_NOT_READY:
        return "MFE_CMDIF_NOT_READY";

    case MFE_CMDIF_BAD_OP:
        return "MFE_CMDIF_BAD_OP";

    case MFE_MISSING_KEY:
        return "No key was set";

    case MFE_MISMATCH_KEY:
        return "The given key is incorrect";

    case MFE_UNKNOWN_REG:
        return "MFE_UNKNOWN_REG";

    case MFE_DIRECT_FW_ACCESS_DISABLED:
        return "MFE_DIRECT_FW_ACCESS_DISABLED";

    case MFE_MANAGED_SWITCH_NOT_SUPPORTED:
        return "MFE_MANAGED_SWITCH_NOT_SUPPORTED";

    case MFE_NOT_SUPPORTED_OPERATION:
        return "MFE_NOT_SUPPORTED_OPERATION";

    case MFE_FLASH_NOT_EXIST:
        return "MFE_FLASH_NOT_EXIST";

    case MFE_MISMATCH_PARAM:
        return "MFE_MISMATCH_PARAM";

    case MFE_EXCEED_SUBSECTORS_MAX_NUM:
        return "MFE_EXCEED_SUBSECTORS_MAX_NUM";

    case MFE_EXCEED_SECTORS_MAX_NUM:
        return "MFE_EXCEED_SECTORS_MAX_NUM";

    case MFE_SECTORS_NUM_NOT_POWER_OF_TWO:
        return "MFE_SECTORS_NUM_NOT_POWER_OF_TWO";

    case MFE_SECTORS_NUM_MORE_THEN_0_LESS_THEN_4:
        return "Can not protect 1 or 2 blocks in this flash. Minimum is 4.";

    case MFE_UNKOWN_ACCESS_TYPE:
        return "MFE_UNKOWN_ACCESS_TYPE";

    case MFE_UNSUPPORTED_DEVICE:
        return "MFE_UNSUPPORTED_DEVICE";

    case MFE_UNSUPPORTED_ERASE_OPERATION:
        return "MFE_UNSUPPORTED_ERASE_OPERATION";

    case MFE_OLD_DEVICE_TYPE:
        return "MFE_OLD_DEVICE_TYPE";

    case MFE_ICMD_INIT_FAILED:
        return "MFE_ICMD_INIT_FAILED";

    case MFE_ICMD_NOT_SUPPORTED:
        return "MFE_ICMD_NOT_SUPPORTED";

    case MFE_HW_ACCESS_NOT_SUPP:
        return "Secure host mode is not enabled in this FW.";

    case MFE_MAD_SEND_ERR:
        return "MFE_MAD_SEND_ERR";

    case MFE_ICMD_BAD_PARAM:
        return "MFE_ICMD_BAD_PARAM";

    case MFE_ICMD_INVALID_OPCODE:
        return "MFE_ICMD_INVALID_OPCODE";

    case MFE_ICMD_INVALID_CMD:
        return "MFE_ICMD_INVALID_CMD";

    case MFE_ICMD_OPERATIONAL_ERROR:
        return "MFE_ICMD_OPERATIONAL_ERROR";

    case MFE_DATA_IS_OTP:
        return "The data you are trying to write is OTP and have already been programmed.";

    case MFE_REG_ACCESS_BAD_METHOD:
        return "MFE_REG_ACCESS_BAD_METHOD";

    case MFE_REG_ACCESS_NOT_SUPPORTED:
        return "MFE_REG_ACCESS_NOT_SUPPORTED";

    case MFE_REG_ACCESS_DEV_BUSY:
        return "MFE_REG_ACCESS_DEV_BUSY";

    case MFE_REG_ACCESS_VER_NOT_SUPP:
        return "MFE_REG_ACCESS_VER_NOT_SUPP";

    case MFE_REG_ACCESS_UNKNOWN_TLV:
        return "MFE_REG_ACCESS_UNKNOWN_TLV";

    case MFE_REG_ACCESS_REG_NOT_SUPP:
        return "MFE_REG_ACCESS_REG_NOT_SUPP";

    case MFE_REG_ACCESS_CLASS_NOT_SUPP:
        return "MFE_REG_ACCESS_CLASS_NOT_SUPP";

    case MFE_REG_ACCESS_METHOD_NOT_SUPP:
        return "MFE_REG_ACCESS_METHOD_NOT_SUPP";

    case MFE_REG_ACCESS_BAD_PARAM:
        return "MFE_REG_ACCESS_BAD_PARAM";

    case MFE_REG_ACCESS_RES_NOT_AVLBL:
        return "MFE_REG_ACCESS_RESOURCE_NOT_AVAILABLE";

    case MFE_REG_ACCESS_MSG_RECPT_ACK:
        return "MFE_REG_ACCESS_MSG_RECPT_ACK";

    case MFE_REG_ACCESS_UNKNOWN_ERR:
        return "MFE_REG_ACCESS_UNKNOWN_ERR";

    case MFE_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
        return "MFE_REG_ACCESS_SIZE_EXCCEEDS_LIMIT";

    case MFE_PCICONF:
        return "Access to device should be through configuration cycles.";

    case MFE_ILLEGAL_BANK_NUM:
        return "MFE_ILLEGAL_BANK_NUM";

    case MFE_OCR_NOT_SUPPORTED:
        return "Direct flash access is not supported.";

    default:
        return "Unknown error";
    }
}

#ifndef UEFI_BUILD
int trm2mfe_err(trm_sts rc)
{
    switch (rc) {
    case TRM_STS_DEV_NOT_SUPPORTED:
        return MFE_UNSUPPORTED_DEVICE;

    case TRM_STS_CR_ACCESS_ERR:
        return MFE_CR_ERROR;

    case TRM_STS_MEM_ERROR:
        return MFE_NOMEM;

    default:
        return MFE_ERROR;
    }
}
#endif

int mf_set_opt(mflash *mfl, MfOpt opt, int val)
{
    if ((int) opt < 0 || opt >= MFO_LAST) {
        return MFE_BAD_PARAMS;
    }
    mfl->opts[opt] = val;
    return MFE_OK;
}

int mf_get_opt(mflash *mfl, MfOpt opt, int *val)
{
    if ((int) opt < 0 || opt >= MFO_LAST) {
        return MFE_BAD_PARAMS;
    }
    *val = mfl->opts[opt];
    return MFE_OK;
}

int mf_cr_read(mflash *mfl, u_int32_t cr_addr, u_int32_t *data)
{
    if (mread4(mfl->mf, cr_addr, data) != 4) {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

int mf_cr_write(mflash *mfl, u_int32_t cr_addr, u_int32_t data)
{
    if (mwrite4(mfl->mf, cr_addr, data) != 4) {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

int mf_set_reset_flash_on_warm_reboot(mflash *mfl)
{
    int rc;
    u_int32_t set_reset_bit_dword_addr;
    int set_reset_bit_offset;
    u_int32_t set_reset_bit_dword;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceSwitchX:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceSwitchIB2:
        return MFE_OK;
    case DeviceSpectrum:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceQuantum:
        set_reset_bit_dword_addr = 0xf0204;
        set_reset_bit_offset = 1;
        break;
    case DeviceConnectX6:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceBlueField2:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
        set_reset_bit_dword_addr = 0xf0c28;
        set_reset_bit_offset = 2;
        break;
    default:
        return MFE_UNSUPPORTED_DEVICE;
    }

    rc = mf_cr_read(mfl, set_reset_bit_dword_addr, &set_reset_bit_dword);
    CHECK_RC(rc);
    set_reset_bit_dword = MERGE(set_reset_bit_dword, 1, set_reset_bit_offset, 1);

    return mf_cr_write(mfl, set_reset_bit_dword_addr, set_reset_bit_dword);
}

int mf_update_boot_addr(mflash *mfl, u_int32_t boot_addr)
{
    int rc;
    u_int32_t boot_cr_space_address;
    int offset_in_address;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceSwitchX:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceSpectrum:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceSwitchIB2:
        boot_cr_space_address = 0xf0000;
        offset_in_address = 8;
        break;
    case DeviceConnectX5:
    case DeviceBlueField:
        boot_cr_space_address = 0xf00c0;
        offset_in_address = 0;
        break;
    case DeviceConnectX6:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceQuantum:
    case DeviceBlueField2:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
        boot_cr_space_address = 0xf0080;
        offset_in_address = 0;
        break;
    default:
        return MFE_UNSUPPORTED_DEVICE;
    }

    if (mfl->access_type != MFAT_UEFI && mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_MLNXOS_CMDIF) {
        // the boot addr will be updated directly via cr-space
        rc = mf_cr_write(mfl, boot_cr_space_address, boot_addr << offset_in_address);
        CHECK_RC(rc);
        return mf_set_reset_flash_on_warm_reboot(mfl);
    } else {
        // the boot addr will be updated via reg
        return mf_update_boot_addr_by_type(mfl, boot_addr);
    }
}

int mf_read_modify_status_winbond(mflash *mfl, u_int8_t bank_num, u_int8_t is_first_status_reg,
                                  u_int8_t param, u_int8_t offset, u_int8_t size)
{
    u_int8_t status1 = 0, status2 = 0, use_rdsr2 = 0;
    u_int32_t status = 0;
    u_int8_t bytes_to_write = 1;
    int rc = 0;

    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    if ((mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND) || (mfl->attr.vendor == FV_S25FLXXXX && (mfl->attr.type == FMT_S25FL116K || mfl->attr.type == FMT_S25FLXXXL)) || (mfl->attr.vendor == FV_MX25K16XXX && mfl->attr.type == FMT_MX25K16XXX)) {
        /*
         * if we have 2 status registers, winbond are allowing us to write both of them
         * in a single command WRSR  status_reg1 located in MSB, status_reg2 after status_reg1
         */
        use_rdsr2 = 1;
    }

    // Read register status
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status1);
    CHECK_RC(rc);
    if (use_rdsr2) {
        if (mfl->attr.vendor == FV_MX25K16XXX) {
            rc = mfl->f_spi_status(mfl, SFC_RDCR, &status2);
            CHECK_RC(rc);
        } else {
            rc = mfl->f_spi_status(mfl, SFC_RDSR2, &status2);
            CHECK_RC(rc);
        }
        status = MERGE(0, status2, 0, 8);
        bytes_to_write = 2;
    }
    // Prepare the read status word
    status = MERGE(status, status1, 8, 8);
    // Modify the status according to the function arguments
    status = MERGE(status, param, offset + is_first_status_reg * 8, size);
    // fix status register in case we dont need to write status register 2
    if (bytes_to_write == 1) {
        status = status >> 8;
    }
    // Write register status
    rc = cntx_spi_write_status_reg(mfl, status, SFC_WRSR, bytes_to_write);
    CHECK_RC(rc);
    return MFE_OK;
}

int mf_read_modify_status_new(mflash *mfl, u_int8_t bank_num, u_int8_t read_cmd, u_int8_t write_cmd,
                              u_int8_t val, u_int8_t offset, u_int8_t size, u_int8_t bytes_num)
{
    int rc = 0;
    u_int32_t status = 0;

    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    rc = cntx_int_spi_get_status_data(mfl, read_cmd, &status, bytes_num);
    CHECK_RC(rc);
    status = MERGE(status, val, offset, size);
    rc = cntx_spi_write_status_reg(mfl, status, write_cmd, bytes_num);
    CHECK_RC(rc);
    return MFE_OK;
}

int mf_get_param_int(mflash *mfl, u_int8_t *param_p, u_int8_t cmd, u_int8_t offset, u_int8_t bit_size,
                     u_int8_t bytes_num, u_int8_t enabled_val)
{
    u_int32_t status = 0, is_first = 1, bank = 0;
    int rc = 0;
    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        u_int8_t curr_val;
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        rc = cntx_int_spi_get_status_data(mfl, cmd, &status, bytes_num);
        CHECK_RC(rc);

        curr_val = EXTRACT(status, offset, bit_size);
        if (bit_size == 1) {
            curr_val = (curr_val == enabled_val);
        }

        if (is_first) {
            *param_p = curr_val;
            is_first = 0;
        } else {
            if (*param_p != curr_val) {
                return MFE_MISMATCH_PARAM;
            }
        }
    }
    return MFE_OK;
}

int mf_set_dummy_cycles_direct_access(mflash *mfl, u_int8_t num_of_cycles)
{
    if (!mfl || num_of_cycles < 1 || num_of_cycles > 15) {
        return MFE_BAD_PARAMS;
    }
    int bank = 0, rc = 0;
    if (!(mfl->attr.dummy_cycles_support && mfl->supp_sr_mod)) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = mf_read_modify_status_new(mfl, bank, SFC_RDNVR, SFC_WRNVR, num_of_cycles, DUMMY_CYCLES_OFFSET_ST, 4, 2);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int mf_get_dummy_cycles_direct_access(mflash *mfl, u_int8_t *dummy_cycles_p)
{
    if (!mfl || !dummy_cycles_p) {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.dummy_cycles_support && mfl->supp_sr_mod)) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    return mf_get_param_int(mfl, dummy_cycles_p, SFC_RDNVR, DUMMY_CYCLES_OFFSET_ST, 4, 2, 0);
    return MFE_OK;
}

int mf_set_quad_en_direct_access(mflash *mfl, u_int8_t quad_en)
{
    if (!mfl) {
        return MFE_BAD_PARAMS;
    }
    int bank = 0, rc = 0;
    if (!(mfl->attr.quad_en_support && mfl->supp_sr_mod)) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        if (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V) {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR2, SFC_WRSR2, quad_en, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1, 1);
            CHECK_RC(rc);
        } else if (mfl->attr.vendor == FV_WINBOND || mfl->attr.vendor == FV_S25FLXXXX) {
            rc = mf_read_modify_status_winbond(mfl, bank, 0, quad_en, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1);
            CHECK_RC(rc);
        } else if (mfl->attr.vendor == FV_ST) {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDNVR, SFC_WRNVR, !quad_en, QUAD_EN_OFFSET_MICRON, 1, 2);
            CHECK_RC(rc);
        } else if (mfl->attr.vendor == FV_IS25LPXXX || mfl->attr.vendor == FV_MX25K16XXX) {
            rc = mf_read_modify_status_winbond(mfl, bank, 1, quad_en, QUAD_EN_OFFSET_ISSI_MACRONIX, 1);
            CHECK_RC(rc);
        }
    }
    return MFE_OK;
}

int mf_get_quad_en_direct_access(mflash *mfl, u_int8_t *quad_en_p)
{
    if (!mfl || !quad_en_p) {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.quad_en_support && mfl->supp_sr_mod)) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    if (mfl->attr.vendor == FV_WINBOND || mfl->attr.vendor == FV_S25FLXXXX) {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDSR2, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1, 1, 1);
    } else if (mfl->attr.vendor == FV_ST) {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDNVR, QUAD_EN_OFFSET_MICRON, 1, 2, 0);
    } else if (mfl->attr.vendor == FV_IS25LPXXX || mfl->attr.vendor == FV_MX25K16XXX) {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDSR, QUAD_EN_OFFSET_ISSI_MACRONIX, 1, 1, 1);
    }
    return MFE_NOT_SUPPORTED_OPERATION;
}

int mf_set_write_protect_direct_access(mflash *mfl, u_int8_t bank_num,
                                       write_protect_info_t *protect_info)
{
    u_int32_t protect_mask = 0, log2_sect_num;
    u_int32_t sectors_num = protect_info->sectors_num;
    int rc;
    write_protect_info_t cur_protect_info;
    memset(&cur_protect_info, 0x0, sizeof(cur_protect_info));

    //printf("-D- mf_set_write_protect: bank_num = %#x, subsec: %#x, bottom: %#x, sectors_num=%#x\n", bank_num,
    //       protect_info->is_subsector, protect_info->is_bottom, protect_info->sectors_num);

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    if (((protect_info->sectors_num - 1) & protect_info->sectors_num) != 0) {
        return MFE_SECTORS_NUM_NOT_POWER_OF_TWO;
    }
    if (protect_info->sectors_num > MAX_SECTORS_NUM) {
        return MFE_EXCEED_SECTORS_MAX_NUM;
    }
    if ((mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_128) || (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_128)) {
        if (!protect_info->is_subsector && (protect_info->sectors_num == 1 || protect_info->sectors_num == 2)) {
            return MFE_SECTORS_NUM_MORE_THEN_0_LESS_THEN_4;
        }
    }
    if (protect_info->is_subsector && !mfl->attr.protect_sub_and_sector) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    if (mfl->attr.protect_sub_and_sector && protect_info->is_subsector) {
        if (protect_info->sectors_num > MAX_SUBSECTOR_NUM) {
            return MFE_EXCEED_SUBSECTORS_MAX_NUM;
        }
    }
    if (mfl->attr.vendor == FV_MX25K16XXX || mfl->attr.vendor == FV_IS25LPXXX) {
        rc = mf_get_write_protect(mfl, bank_num, &cur_protect_info);
        CHECK_RC(rc);
        if (cur_protect_info.is_bottom && !protect_info->is_bottom) {
            if (protect_info->sectors_num) {
                return MFE_DATA_IS_OTP;
            } else {
                protect_info->is_bottom = cur_protect_info.is_bottom; // write protect is disabled, so we don't really care about top/bottom bit.
            }
        }
    }

    for (log2_sect_num = 0; log2_sect_num < 8; log2_sect_num++) {
        if (sectors_num == 0) {
            break;
        }
        sectors_num >>= 1;
    }
    // adrianc: at this point log2_sect_num is actually  bigger by 1(if sectors_num!=0) to fit the BP bit values in the flash spec

    if (log2_sect_num != 0 && !protect_info->is_subsector && ((mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_128) || (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_128))) {
        log2_sect_num -= 2; // spec alignment
    }

    if (mfl->attr.vendor == FV_ST && mfl->attr.type == FMT_N25QXXX) {
        protect_mask = MERGE(protect_mask, log2_sect_num & 0x7, 0, BP_SIZE);
        protect_mask = MERGE(protect_mask, protect_info->is_bottom, BP_SIZE, 1);
        protect_mask = MERGE(protect_mask, (log2_sect_num & 0x8) >> 3, BP_SIZE + 1, 1);
        return mf_read_modify_status_winbond(mfl, bank_num, 1, protect_mask, BP_OFFSET, PROTECT_BITS_SIZE);
    } else if (mfl->attr.vendor == FV_MX25K16XXX || mfl->attr.vendor == FV_IS25LPXXX || (mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_256) || (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_256)) {
        if (mfl->attr.vendor == FV_MX25K16XXX) {
            rc = mf_read_modify_status_winbond(mfl, bank_num, 0, protect_info->is_bottom, TB_OFFSET_MACRONIX, 1);
            CHECK_RC(rc);
        } else if (mfl->attr.vendor == FV_IS25LPXXX) {
            rc = mf_read_modify_status_new(mfl, bank_num, SFC_RDFR, SFC_WRFR, protect_info->is_bottom, TB_OFFSET_ISSI, 1, 1);
            CHECK_RC(rc);
        } else { // vendor == FV_S25FLXXXX or vendor == FV_WINBOND
            rc = mf_read_modify_status_winbond(mfl, bank_num, 1, protect_info->is_bottom, TB_OFFSET_CYPRESS_WINBOND_256, 1);
            CHECK_RC(rc);
        }
        return mf_read_modify_status_winbond(mfl, bank_num, 1, log2_sect_num, BP_OFFSET, 4);
    } else {
        u_int8_t modify_size = 0;

        protect_mask = MERGE(protect_mask, log2_sect_num, 0, BP_SIZE);
        modify_size += BP_SIZE;

        protect_mask = MERGE(protect_mask, protect_info->is_bottom, BP_SIZE, 1);
        modify_size += 1;
        if (mfl->attr.protect_sub_and_sector) {
            protect_mask = MERGE(protect_mask, protect_info->is_subsector, BP_SIZE + 1, 1);
            modify_size += 1;
        }
        return mf_read_modify_status_winbond(mfl, bank_num, 1, protect_mask, BP_OFFSET, modify_size);
    }
}

int mf_get_write_protect_direct_access(mflash *mfl, u_int8_t bank_num,
                                       write_protect_info_t *protect_info)
{
    int rc = 0;
    u_int8_t status = 0;
    u_int8_t tb_offset = TB_OFFSET;
    int spec_alignment_factor;

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    protect_info->is_subsector = 0; // Defaultly no support for subsector protection
    if (mfl->attr.vendor == FV_MX25K16XXX) {
        rc = mfl->f_spi_status(mfl, SFC_RDCR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, TB_OFFSET_MACRONIX, 1);
    } else if (mfl->attr.vendor == FV_IS25LPXXX) {
        rc = mfl->f_spi_status(mfl, SFC_RDFR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, TB_OFFSET_ISSI, 1);
    } else {
        if ((mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_256) || (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_256)) {
            tb_offset = TB_OFFSET_CYPRESS_WINBOND_256;
        }
        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, tb_offset, 1);
        if (mfl->attr.protect_sub_and_sector) {
            protect_info->is_subsector = EXTRACT(status, SEC_OFFSET, 1);
        } else {
            protect_info->is_subsector = 0;
        }
    }
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
    CHECK_RC(rc);
    if (EXTRACT(status, BP_OFFSET, BP_SIZE) == 0) {
        protect_info->sectors_num = 0;
    } else {
        spec_alignment_factor =
            ((mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_128) || (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_128)) && !protect_info->is_subsector ?
            1 : -1;
        protect_info->sectors_num = 1 << (EXTRACT(status, BP_OFFSET, BP_SIZE) + spec_alignment_factor);
    }

    return MFE_OK;
}

int mf_is_fifth_gen(mflash *mfl)
{
    MfError status;
    int icmdif_supported = is_icmdif_supported(mfl, &status);
    if (status != MFE_OK) {
        return status;
    }
    return icmdif_supported;
}

int mf_enable_hw_access(mflash *mfl, u_int64_t key)
{
#ifndef UEFI_BUILD
    int rc = 0;
    if (mf_is_fifth_gen(mfl)) {
        return mf_secure_host_op(mfl, key, 0);
    } else {
        rc = tcif_hw_access(mfl->mf, key, 0 /* Unlock */);
        return (rc == ME_CMDIF_UNKN_TLV) ? MFE_MISMATCH_KEY : MError2MfError((MError) rc);
    }
    #else
    (void)mfl;
    (void)key;
    return MFE_NOT_SUPPORTED_OPERATION;
#endif
}
/*
 * Op:
 * 0 - disable
 * 1 - enable
 */
int mf_secure_host_op(mflash *mfl, u_int64_t key, int op)
{
    struct tools_open_mlock mlock;
    memset(&mlock, 0, sizeof(mlock));
    mlock.operation = op;
    mlock.key = key;
    int rc = ME_OK;
    if (IS_CONNECT_IB(mfl->attr.hw_dev_id)) {
        rc = ME_REG_ACCESS_REG_NOT_SUPP;
    } else {
        rc = (int) reg_access_secure_host(mfl->mf, REG_ACCESS_METHOD_SET, &mlock);
    }
    switch (rc) {
    case ME_REG_ACCESS_REG_NOT_SUPP:
        rc = MFE_NOT_SUPPORTED_OPERATION;
        break;

    case ME_REG_ACCESS_BAD_PARAM:
        rc = MFE_MISMATCH_KEY;
        break;

    default:
        rc = MError2MfError((MError) rc);
        break;
    }
    return rc;
}

int mf_get_secure_host(mflash *mfl, int *mode)
{
    struct tools_open_mlock mlock;
    memset(&mlock, 0, sizeof(mlock));
    int rc = (int) reg_access_secure_host(mfl->mf, REG_ACCESS_METHOD_GET, &mlock);
    *mode = mlock.operation;
    return rc;
}

int mf_disable_hw_access(mflash *mfl)
{
#ifndef UEFI_BUILD
    int rc = 0;
    // We need to release the semaphore because we will not have any access to semaphore after disabling the HW access
    mfl->unlock_flash_prog_allowed = 1;
    rc = release_semaphore(mfl, 1);
    CHECK_RC(rc);

    rc = tcif_hw_access(mfl->mf, 0, 1 /* Lock */);
    // translate to operation specific errors
    switch (rc) {
    case ME_CMDIF_UNKN_TLV:
        rc = MFE_MISMATCH_KEY;
        break;

    case ME_CMDIF_BAD_OP:
        rc = MFE_MISSING_KEY;
        break;

    default:
        rc = MError2MfError((MError) rc);
        break;
    }
    return rc;
#else
    (void)mfl;
    return MFE_NOT_SUPPORTED_OPERATION;
#endif
}

int mf_disable_hw_access_with_key(mflash *mfl, u_int64_t key)
{

    if (!mf_is_fifth_gen(mfl)) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    return mf_secure_host_op(mfl, key, 1);
}

mfile* mf_get_mfile(mflash *mfl)
{
    return mfl->mf;
}

int mf_set_quad_en(mflash *mfl, u_int8_t quad_en)
{
    return mfl->f_set_quad_en(mfl, quad_en);
}

int mf_get_quad_en(mflash *mfl, u_int8_t *quad_en)
{
    return mfl->f_get_quad_en(mfl, quad_en);
}

int mf_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    return mfl->f_set_write_protect(mfl, bank_num, protect_info);
}

int mf_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    return mfl->f_get_write_protect(mfl, bank_num, protect_info);
}

int mf_set_dummy_cycles(mflash *mfl, u_int8_t num_of_cycles)
{
    return mfl->f_set_dummy_cycles(mfl, num_of_cycles);
}

int mf_get_dummy_cycles(mflash *mfl, u_int8_t *num_of_cycles)
{
    return mfl->f_get_dummy_cycles(mfl, num_of_cycles);
}

