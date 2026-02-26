/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "common/bit_slice.h"
#include "common/tools_time.h"
#include <mtcr.h>
#include <reg_access.h>
#include <tools_layouts/reg_access_hca_layouts.h>
#ifndef UEFI_BUILD
#include <tools_cif.h>
#endif
#include "mflash_pack_layer.h"
#include "mflash_access_layer.h"
#include "mflash.h"

#include "mflash_dev_capability.h"
#include "mflash_common_structs.h"
#include "mflash_gw.h"
#include "mflash_new_gw.h"
#define ICMD_MAX_BLOCK_WRITE 128
#define INBAND_MAX_BLOCK_WRITE 32

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#ifndef __WIN__

#if defined __DJGPP__
/* */
/* DJGPP - GCC PORT TO MS DOS */
/* */
#include <netinet/in.h>
#include <unistd.h>

#define bswap_32(x) ntohl(x)

#endif /* __DJGPP__ */

#define OP_NOT_SUPPORTED EOPNOTSUPP

#else /* __WIN__ */

/* */
/* Windows (Under DDK) */
/* */
#define OP_NOT_SUPPORTED EINVAL
#define usleep(x) Sleep(((x + 999) / 1000))

#endif /* __WIN__ */
#endif /* ifdef IRISC */

/* Timer definitions (needed when polling flash semaphore in windows) */
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
#define TIMER_INIT()               \
    SYSTEMTIME _start, _end;       \
    int _diff_in_sec, _diff_in_ms; \
    (void)_diff_in_sec;            \
    (void)_diff_in_ms
#define TIMER_START() GetSystemTime(&_start)
#define TIMER_STOP() GetSystemTime(&_end)
#define TIMER_PRINT(...)                                      \
    _diff_in_sec = _end.wSecond - _start.wSecond;             \
    _diff_in_ms = (_end.wMilliseconds - _start.wMilliseconds; \
                   printf(__VA_ARGS__);                       \
                   printf("it took %d sec %d and ms to run.\n", _diff_in_sec, _diff_in_ms)
#define TIMER_GET_DIFF(diff_in_sec, diff_in_ms)  \
    diff_in_sec = _end.wSecond - _start.wSecond; \
    diff_in_ms = _end.wMilliseconds - _start.wMilliseconds
#define TIMER_INIT_AND_START() \
    TIMER_INIT();              \
    TIMER_START()
#define TIMER_STOP_GET_DIFF(diff_in_sec, diff_in_ms) \
    TIMER_STOP();                                    \
    TIMER_GET_DIFF(diff_in_sec, diff_in_ms)
#define TIMER_CHECK(max_sec, max_ms, action_on_tout)         \
    TIMER_STOP();                                            \
    _diff_in_sec = _end.wSecond - _start.wSecond;            \
    _diff_in_ms = _end.wMilliseconds - _start.wMilliseconds; \
    if (_diff_in_sec >= max_sec && _diff_in_ms > max_ms)     \
    {                                                        \
        action_on_tout;                                      \
    }
#endif
/* Flash Functions: */
/* This is an interface function when running in IRISC */
int mf_open_fw(mflash* mfl, flash_params_t* flash_params, int num_of_banks);
int cntx_flash_init(mflash* mfl, flash_params_t* flash_params);
int cntx_flash_init_direct_access(mflash* mfl, flash_params_t* flash_params);
int spi_get_num_of_flashes(int prev_num_of_flashes);
int cntx_spi_get_type(mflash* mfl, u_int8_t op_type, u_int8_t* vendor, u_int8_t* type, u_int8_t* density);
/* forward decl: */
int icmd_init(mflash* mfl);
int flash_init_fw_access(mflash* mfl, flash_params_t* flash_params);
int mf_get_secure_host(mflash* mfl, int* mode);
int mf_secure_host_op(mflash* mfl, u_int64_t key, int op);
int cntx_sst_get_log2size(u_int8_t density, int* log2spi_size);
int cntx_mx25k16xxx_get_log2size(u_int8_t density, int* log2spi_size);
/* NOTE: This macro returns ... not nice. */
#define CHECK_RC(rc)   \
    do                 \
    {                  \
        if (rc)        \
        {              \
            return rc; \
        }              \
    } while (0)

#define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* Constants: */

/* General: */
#define GPIO_DIR_L 0xf008c
#define GPIO_POL_L 0xf0094
#define GPIO_MOD_L 0xf009c
#define GPIO_DAT_L 0xf0084
#define GPIO_DATACLEAR_L 0xf00d4
#define GPIO_DATASET_L 0xf00dc

#define SEMAP63 0xf03fc

#define SECTOR_NUM_60MB_SPECIAL_CASE 960
#define BP_ISSI_60MB_SPECIAL_CASE 13
#define BP_WINBOND_MACRONIX_60MB_SPECIAL_CASE 7

/* InfiniHost specific */
#define IDLE 0
#define READ4 (1 << 29)
#define WRITE1 (2 << 29)

#define CR_FLASH 0xf01a4
#define ADDR_MSK 0x7ffffUL
#define CMD_MASK 0xe0000000UL

#define SST_STATUS_REG_VAL 0x80
#define ATMEL_STATUS_REG_VAL 0x0

#define MAX_FLASH_PROG_SEM_RETRY_CNT 40

#define CPUMODE_MSK 0xc0000000UL
#define CPUMODE_SHIFT 30
#define CPUMODE 0xf0150

#define COMMAND_MASK 0x00ff0000

static mfile* mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func, void* dma_func, void* extra_data)
{
    if ((fw_cmd_context == NULL) || (fw_cmd_func == NULL) || (extra_data == NULL))
    {
        errno = EINVAL;
        return NULL;
    }

    mfile* mf = malloc(sizeof(mfile));

    if (!mf)
    {
        errno = ENOMEM;
        return NULL;
    }

    memset(mf, 0, sizeof(mfile));
    mf->flags = MDEVS_FWCTX;
    mf->tp = MST_FWCTX;
    mf->context.fw_cmd_context = fw_cmd_context;
    mf->context.fw_cmd_func = fw_cmd_func;
    mf->context.fw_cmd_dma = dma_func;
    mf->sock = -1; /* we are not opening remotely */
    return mf;
}

/* Write/Erase delays */
/* ------------------ */
/* The below delays improve CPU utilization when doing long operations by */
/* sleeping instead of full throtle polling. */
/* Their values are set so they will not lenghen burn time (at least not by a meaningfull duration) */
/* and will save cpu. The delays are divided to an initial_delay, and then retry num_of_retries times waiting */
/* retry_delay. The initial delay is set according to the fastest flash we currently support (W25QxxBV). The */
/* retry_delay*num_of_retries is set according to the slowest flash maximum AC timing. */
/* */
/* To test there's no performance degradation by these delay: set DELAYS to 0 and RETRIES to infinity, and compare perf.
 */

enum IntelFlashCommand
{
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

enum IntelFlashStatus
{
    FS_Ready = 0x80,
    FS_Suspended = 0x40,
    FS_Error = 0x3E,
    FS_BlockError = 0x3F
};

#ifndef UEFI_BUILD
static int trm2mfe_err(trm_sts rc);
#endif

int my_memset(void* dst, u_int8_t data, u_int32_t len)
{
    u_int32_t i = 0;
    u_int8_t* bytes = (u_int8_t*)dst;

    for (i = 0; i < len; i++)
    {
        bytes[i] = data;
    }

    return 0;
}

int my_memcpy(void* dst, void* src, u_int32_t len)
{
    u_int32_t i = 0;
    u_int8_t* dbytes = (u_int8_t*)dst;
    u_int8_t* sbytes = (u_int8_t*)src;

    for (i = 0; i < len; i++)
    {
        dbytes[i] = sbytes[i];
    }

    return 0;
}

int write_chunks(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data)
{
    static bool env_vars_evaluated = false;
    static bool erase_verification_enable = false;
    static int retries_num = 0;
    int rc = 0;

    if (!env_vars_evaluated)
    {
        erase_verification_enable = getenv("MFLASH_ERASE_VERIFY") ? true : false;
        const char* retries_num_str = getenv("MFLASH_WRITE_RETRIES");
        retries_num = retries_num_str ? atoi(retries_num_str) : 0;
        env_vars_evaluated = true;
    }
    u_int8_t* p = (u_int8_t*)data;
    int all_ffs = 0;

    /* TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here) */
    u_int8_t tmp_buff[MAX_WRITE_BUFFER_SIZE];

    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }

    /* printf("-D- write_chunks(addr=%x, size=%x)\n", addr, len); */

    while (len)
    {
        u_int32_t i = 0;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;
        u_int32_t block_size = mfl->attr.block_write;
        u_int32_t block_mask = ~(block_size - 1);
        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size = block_size;
        u_int8_t* block_data = p;

        /* */
        /* To keep things simple, we always write full blocks. */
        /* (there's an option to write partial buffer, but Intel reference code always */
        /* writes full buffer, with pads if needed. I do the same ...) */
        /* */
        /* The First and last cycles (can be the same one) may not be block aligned. */
        /* If this is the case, copy the block data to a 0xFF padded temp buffer (writing 0xFF */
        /* does not effect the flash) */
        /* */

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask))
        {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size)
        {
            my_memset(tmp_buff, 0xff, block_size);

            data_size -= prefix_pad_size;
            data_size -= suffix_pad_size;

            my_memcpy(tmp_buff + prefix_pad_size, p, data_size);

            block_data = tmp_buff;
        }
        else if (mfl->attr.page_write)
        {
            /* current write is aligned to block size, */
            /* write data to next page, or to last full block (if we're in the last block in a page) */
            u_int32_t page_mask = ~(mfl->attr.page_write - 1);
            u_int32_t next_page_addr = (addr + mfl->attr.page_write + 1) & page_mask;
            u_int32_t size_to_page_boundary = next_page_addr - addr;
            if (len > size_to_page_boundary)
            {
                block_size = size_to_page_boundary;
            }
            else
            {
                block_size = len & block_mask;
            }
            data_size = block_size;
        }

        /* */
        /* Check to see if there's something to do */
        /* */
        all_ffs = 1;
        for (i = 0; i < block_size; i++)
        {
            if (block_data[i] != 0xff)
            {
                all_ffs = 0;
                break;
            }
        }

        if (!all_ffs)
        {
            if (erase_verification_enable)
            {
                u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE] = {0};
                rc = mfl->f_reset(mfl);
                CHECK_RC(rc);
                rc = mfl->f_read(mfl, addr, data_size, verify_buffer, false);
                CHECK_RC(rc);
                /* Verify erase */
                for (i = 0; i < data_size; i++)
                {
                    if (verify_buffer[i] != 0xff)
                    {
                        printf("Erase verification failed. Address 0x%08x - expected:0x%02x actual: 0x%02x\n", addr + i, 0xff, verify_buffer[i]);
                        return MFE_VERIFY_ERROR;
                    }
                }
            }

            bool write_block_passed = false;
            int retries_counter = 0;
            while (!write_block_passed)
            {
                rc = mfl->f_write_blk(mfl, block_addr, block_size, block_data);
                CHECK_RC(rc);

                if (mfl->opts[MFO_NO_VERIFY] == 0)
                {
                    u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE] = {0};
                    rc = mfl->f_reset(mfl);
                    CHECK_RC(rc);
                    rc = mfl->f_read(mfl, addr, data_size, verify_buffer, false);
                    CHECK_RC(rc);
                    /* Verify data */
                    bool verify_pass = true;
                    for (i = 0; i < data_size; i++)
                    {
                        if (verify_buffer[i] != block_data[i + prefix_pad_size])
                        {
                            verify_pass = false;
                            FLASH_DPRINTF(("Write verification failed. Address 0x%08x - expected:0x%02x actual: 0x%02x\n", addr + i, block_data[i + prefix_pad_size], verify_buffer[i]));

                            if (retries_counter >= retries_num)
                            {
                                return MFE_VERIFY_ERROR;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    if (!verify_pass)
                    {
                        retries_counter++;
                        FLASH_DPRINTF(("Retry number %d\n", retries_counter));
                        continue;
                    }
                }
                write_block_passed = true;
            }
        }

        /* */
        /* loop advance */
        /* */

        addr += data_size;
        p += data_size;
        len -= data_size;
    }

    rc = mfl->f_reset(mfl);
    CHECK_RC(rc);

    return MFE_OK;
}

#define FD_LEGACY (1 << FD_8) | (1 << FD_16) | (1 << FD_32) | (1 << FD_64) | (1 << FD_128)

flash_info_t g_flash_info_arr[] = {{"M25PXxx", FV_ST, FMT_ST_M25PX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 0, 0, 0, 0, 0, 0, 0},
                                   {"M25Pxx", FV_ST, FMT_ST_M25P, FD_LEGACY, MCS_STSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {"N25Q0XX", FV_ST, FMT_N25QXXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 1, 0, 0, 0},
                                   /*{MICRON_3V_NAME, FV_ST, FMT_N25QXXX, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 1, 0, 0, 0}, */
                                   {MICRON_3V_NAME, FV_ST, FMT_N25QXXX, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 1, 1, 0, 0},
                                   {MICRON_1V8_NAME, FV_ST, FMT_N25QUXXX, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 1, 1, 0, 0},
                                   {SST_FLASH_NAME, FV_SST, FMT_SST_25, FD_LEGACY, MCS_SSTSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {WINBOND_NAME, FV_WINBOND, FMT_WINBOND, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0, 0, 0, 0},
                                   {WINBOND_W25X, FV_WINBOND, FMT_WINBOND_W25X, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_3V, 1 << FD_128, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_3V, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_IQ, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_IM, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_IQ, 1 << FD_32, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {WINBOND_3V_NAME, FV_WINBOND, FMT_WINBOND_IM, 1 << FD_32, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},
                                   {ATMEL_NAME, FV_ATMEL, FMT_ATMEL, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {S25FLXXXP_NAME, FV_S25FLXXXX, FMT_S25FLXXXP, FD_LEGACY, MCS_STSPI, SFC_SE, FSS_64KB, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {S25FL116K_NAME, FV_S25FLXXXX, FMT_S25FL116K, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0, 0, 0, 0},
                                   {MACRONIX_NAME, FV_MX25K16XXX, FMT_MX25K16XXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {MACRONIX_3V_NAME, FV_MX25K16XXX, FMT_MX25K16XXX, (1 << FD_256), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {CYPRESS_3V_NAME, FV_S25FLXXXX, FMT_S25FLXXXL, 1 << FD_128, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 0, 0, 0, 0},
                                   /*{CYPRESS_3V_NAME, FV_S25FLXXXX, FMT_S25FLXXXL, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB,  1, 1, 1, 0, 0, 0, 0, 0}, */
                                   {ISSI_3V_NAME, FV_IS25LPXXX, FMT_IS25LPXXX, FD_LEGACY, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {MACRONIX_1V8_NAME, FV_MX25K16XXX, FMT_SST_25, (1 << FD_32), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {MACRONIX_1V8_NAME, FV_MX25K16XXX, FMT_SST_28, (1 << FD_32), MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {MACRONIX_1V8_NAME, FV_MX25K16XXX, FMT_SST_25, (1 << FD_256), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},

                                   // MX25U51294GXDI08 (MX25U51294G) and MX25U51245G both have jedec id 0x3a25c2 so they support SFDP Series Code
                                   // capability to tell them apart.
                                   {MACRONIX_1V8_NAME, FV_MX25K16XXX, FMT_SST_25, (1 << FD_512), MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 0, 1, 1, 1, 0},
                                   /* added by edwardg 06/09/2020 */
                                   {ISSI_HUAWEY_NAME, FV_IS25LPXXX, FMT_IS25LPXXX, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 1, 1, 0, 0, 0},

                                   // There are 2 ISSI flashes with same JEDEC ID 16709d (IS25WP032D, IS25WJ032F), but with different reg layout
                                   // according to vendor - we can't tell them apart. requested to not use IS25WP032D  in emulation anymore (the only use
                                   // case for it) the support for IS25WJ032F is added here but we don't this flash in-house for verification
                                   {ISSI_NAME, FV_IS25LPXXX, FMT_IS25WPXXX, 1 << FD_32, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 0, 0, 1, 0, 0},

                                   /* https://www.issi.com/WW/pdf/25LP-WP512MG.pdf */
                                   {ISSI_NAME, FV_IS25LPXXX, FMT_IS25WPXXX, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 1, 1, 1, 0, 0},

                                   {GIGA_3V_NAME, FV_GD25QXXX, FVT_GD25QXXX, 1 << FD_256, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 1, 1, 0, 0, 0},
                                   {GIGA_3V_NAME, FV_GD25QXXX, FVT_GD25QXXX, 1 << FD_128, MCS_STSPI, SFC_SSE, FSS_4KB, 1, 1, 1, 1, 1, 0, 0, 0},
                                   /* https://www.gigadevice.com.cn/Public/Uploads/uploadfile/files/20231213/DS-01012-GD25LB512MF-Rev1.0.pdf */
                                   {GIGA_1V8_NAME, FV_GD25QXXX, FVT_GD25LBXXX, 1 << FD_512, MCS_STSPI, SFC_4SSE, FSS_4KB, 1, 1, 1, 1, 1, 0, 0, 0}};

int cntx_sst_get_log2size(u_int8_t density, int* log2spi_size)
{
    switch (density)
    {
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

int cntx_mx25k16xxx_get_log2size(u_int8_t density, int* log2spi_size)
{
    switch (density)
    {
        case 0x3a:
        case 0x20:
            *log2spi_size = 0x1a;
            break;

        default:
            *log2spi_size = density;
            break;
    }
    return MFE_OK;
}

int get_log2size_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t density, int* log2size)
{
    if ((type == FMT_SST_25) && (vendor == FV_SST))
    {
        return cntx_sst_get_log2size(density, log2size);
    }
    if (type == FMT_SST_25 && vendor == FV_MX25K16XXX)
    {
        return cntx_mx25k16xxx_get_log2size(density, log2size);
    }
    // In some flashes, the value is 20, but the correct value should be 0x1A. It cannot be 0x20 because 2^20 would overflow an integer.
    if (density == 0x20)
    {
        *log2size = 0x1a;
    }
    else
    {
        *log2size = density;
    }
    return MFE_OK;
}

int get_type_index_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t density, unsigned* type_index)
{
    unsigned i = 0, arr_size = 0;

    arr_size = ARR_SIZE(g_flash_info_arr);

    for (i = 0; i < arr_size; i++)
    {
        flash_info_t* flash_info = &g_flash_info_arr[i];

        if ((flash_info->vendor == vendor) && (flash_info->type == type))
        {
            if (density == 0x20)
            {
                density = 0x1a;
            }
        }
        if ((flash_info->vendor == vendor) && (flash_info->type == type) && ((flash_info->densities & (1 << density)) != 0))
        {
            *type_index = i;
            return MFE_OK;
        }
    }
    return MFE_UNSUPPORTED_FLASH_TYPE;
}

void mf_flash_list(char* flash_arr, int flash_arr_size)
{
    int i = 0;
    int arr_index = 0;
    int arr_size = ARR_SIZE(g_flash_info_arr);

    if (!flash_arr || (flash_arr_size < 1))
    {
        return;
    }

    for (i = 0; i < arr_size; i++)
    {
        flash_info_t* flash_info = &g_flash_info_arr[i];
        int name_len = strlen(flash_info->name);
        if (flash_arr_size - name_len <= 2)
        {
            /* Out of space, append \0 and return */
            break;
        }
        strcpy(&flash_arr[arr_index], flash_info->name);
        arr_index += name_len;
        flash_arr_size -= name_len;
        if (i != arr_size - 1)
        {
            flash_arr[arr_index++] = ',';
            flash_arr[arr_index++] = ' ';
            flash_arr_size -= 2;
        }
    }
    flash_arr[arr_index] = '\0';
    return;
}

int get_type_index_by_name(const char* type_name, unsigned* type_index)
{
    unsigned i = 0, arr_size = 0;

    arr_size = ARR_SIZE(g_flash_info_arr);
    for (i = 0; i < arr_size; i++)
    {
        flash_info_t* flash_info = &g_flash_info_arr[i];
        if (!strcmp(type_name, flash_info->name))
        {
            *type_index = i;
            return MFE_OK;
        }
    }
    printf("-E- The flash name \"%s\" is unknown\n.", type_name);
    return MFE_UNSUPPORTED_FLASH_TYPE;
}

int is_no_flash_detected(u_int8_t type, u_int8_t vendor, u_int8_t capacity)
{
    if (((type == 0xff) && (vendor == 0xff) && (capacity == 0xff)) || ((type == 0x0) && (vendor == 0x0) && (capacity == 0x0)))
    {
        return 1;
    }
    return 0;
}

int get_flash_info_by_res(mflash* mfl, unsigned* type_index, int* log2size, u_int8_t* no_flash, unsigned char* es_p)
{
    int rc = 0;

    *no_flash = 0;

    rc = mfl->f_spi_status(mfl, SFC_RES, es_p);
    CHECK_RC(rc);
    FLASH_DPRINTF(("get_flash_info_by_res: es = %#x\n", *es_p));
    if (((*es_p >= 0x10) && (*es_p < 0x17)))
    {
        *log2size = *es_p + 1;
        /* This should return the same result for any FD value from [FD_8..FD_128]. */
        /* This is just to catch the FD_LEGACY bitmask. */
        return get_type_index_by_vendor_type_density(FV_ST, FMT_ST_M25P, *log2size, type_index);
    }
    else if ((*es_p == 0xff) || (*es_p == 0x0))
    {
        *no_flash = 1;
    }
    else
    {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }
    return MFE_OK;
}

int cntx_get_flash_info(mflash* mfl, flash_info_t* f_info, int* log2size, u_int8_t* no_flash)
{
    int rc = 0;
    u_int8_t type = 0, capacity = 0, vendor = 0, no_flash_res = 0, no_flash_rdid = 0;
    unsigned char es = 0;
    unsigned type_index = 0;

    /* Assume there is a flash. */
    *no_flash = 0;

    rc = cntx_spi_get_type(mfl, SFC_JEDEC, &vendor, &type, &capacity);
    CHECK_RC(rc);
    no_flash_rdid = is_no_flash_detected(type, vendor, capacity);
    FLASH_DPRINTF(("cntx_spi_get_type: rc: %#x, vendor=%#x, type=%#x, capacity=%#x\n", rc, vendor, type, capacity));
    FLASH_DPRINTF(("rc = %d, no_flash_rdid = %d\n", rc, no_flash_rdid));

    if (no_flash_rdid)
    {
        FLASH_DPRINTF(("no support for rdid\n"));
        /* RDID Failed due to: */
        /* 1- RDID is not supported but RES is - Old flashes. */
        /* 2- There is no Flash */
        /* 3- Flash is not supported */

        /* Trying RES */
        rc = get_flash_info_by_res(mfl, &type_index, log2size, &no_flash_res, &es);
        if ((rc == 0) && (no_flash_res == 1))
        {
            /* RES Succeeded due to: no flash, unsupported flash or old flash. */
            *no_flash = 1;
            /* when no_flash_rdid == 0 then "1- RDID is not supported but RES is - Old flashes." */
        }
    }
    else
    {
        /*  RDID Succeded. */
        rc = MFE_OK;
        if (get_log2size_by_vendor_type_density(vendor, type, capacity, log2size) != MFE_OK)
        {
            printf("-E- SST SPI flash #%d (vendor: %#x, type: %#x, capacity:%#x) is not supported.\n", get_bank_int(mfl), vendor, type, capacity);
            rc = MFE_UNSUPPORTED_FLASH_TOPOLOGY;
        }
        else if (get_type_index_by_vendor_type_density(vendor, type, *log2size, &type_index) != MFE_OK)
        {
            rc = MFE_UNSUPPORTED_FLASH_TYPE;
        }
        /* found supported flash if rc == MFE_OK at this point. */
    }

    if (rc == MFE_UNSUPPORTED_FLASH_TYPE)
    {
        printf("-E- SPI flash #%d (vendor: %#x, memory type: %#x, es: %#x) is not supported.\n", get_bank_int(mfl), vendor, type, es);
    }
    FLASH_DPRINTF(("rc = %d, no_flash_res = %d, type_index = %d.\n", rc, no_flash_res, type_index));
    if ((rc == MFE_OK) && (*no_flash == 0))
    {
        memcpy(f_info, &g_flash_info_arr[type_index], sizeof(flash_info_t));
    }

    /* FR #2742089 - we are requested to support Gigadevice GD25B256DFIGR flash of 32MB on CX4LX and CX5 */
    /* These devices support 16MB flash types only, meaning they work in 3-bytes addr mode. */
    /* So in that case we override the erase command matching 4-bytes addr (32MB) to */
    /* erase command of 3-bytes addr */
    if (((mfl->dm_dev_id == DeviceConnectX4LX) || (mfl->dm_dev_id == DeviceConnectX5)) && (f_info->vendor == FV_GD25QXXX))
    {
        f_info->erase_command = SFC_SSE;
    }

    if (f_info->series_code_support)
    {
        rc = modify_flash_info_if_needed(mfl, f_info);
    }

    return rc;
}

int cntx_get_jedec_id_direct_access(mflash* mfl, u_int32_t* jedec_id_p)
{
    int rc = 0;

    rc = mfl->f_int_spi_get_status_data(mfl, SFC_JEDEC, jedec_id_p, 4);
    *jedec_id_p = ___my_swab32(*jedec_id_p);
    FLASH_DPRINTF(("jedec_id = %#x\n", *jedec_id_p));

    return rc;
}

int compare_flash_params(flash_params_t* flash_params, int bank_num, const char* type_name, int log2size)
{
    if (strcmp(flash_params->type_name, type_name) != 0)
    {
        printf("-E- SPI flash #%d (type: %s)differs in type from SPI flash #%d(type: %s). "
               "All flash devices must be of the same type.\n",
               bank_num, type_name, bank_num - 1, flash_params->type_name);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    if (flash_params->log2size != log2size)
    {
        printf("-E- SPI flash #%d (log2size: %#x) differs in size from SPI flash #%d (log2size: %#x). "
               "All flash devices must be of the same size.\n",
               bank_num, log2size, bank_num - 1, flash_params->log2size);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    return MFE_OK;
}

int cntx_st_spi_get_status(mflash* mfl, u_int8_t op_type, u_int8_t* status)
{
    u_int32_t flash_data = 0;
    int rc = 0;

    rc = mfl->f_int_spi_get_status_data(mfl, op_type, &flash_data, 1);
    CHECK_RC(rc);
    *status = EXTRACT(flash_data, 0, 8);
    return MFE_OK;
}

int get_num_of_banks_int(mflash* mfl)
{
    int num = 0;

    if ((mfl->opts[MFO_USER_BANKS_NUM] == 0) && (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_NO) && ((num = get_num_of_banks(mfl->mf)) != -1))
    {
        return num; /* if mfpa register is supported get the exact number of flash banks */
    }
    return mfl->opts[MFO_NUM_OF_BANKS];
}

int get_flash_params(mflash* mfl, flash_params_t* flash_params, flash_info_t* flash_info)
{
    int num_of_flashes = get_num_of_banks_int(mfl);
    int spi_sel = 0, rc = 0;
    int params_were_set = 0;
    flash_info_t tmp_flash_info;

    memset(flash_params, 0, sizeof(flash_params_t));
    memset(flash_info, 0, sizeof(flash_info_t));
    memset(&tmp_flash_info, 0, sizeof(flash_info_t));

    /* if number of flash banks is zero exit with error */
    if (num_of_flashes == 0)
    {
        return MFE_NO_FLASH_DETECTED;
    }

    for (spi_sel = 0; spi_sel < num_of_flashes; spi_sel++)
    {
        int log2size = 0;
        u_int8_t no_flash = 0;
        const char* type_name;
        rc = set_bank(mfl, spi_sel);
        CHECK_RC(rc);
        rc = mfl->f_get_info(mfl, &tmp_flash_info, &log2size, &no_flash);
        CHECK_RC(rc);

        FLASH_DPRINTF(("spi_sel = %d, num_of_flashes = %d, rc = %d, no_flash = %d\n", spi_sel, num_of_flashes, rc, no_flash));
        if (no_flash == 1)
        {
            /* This bank is empty and also the following banks will be empty. */
            if (flash_params->num_of_flashes == 0)
            {
                /* if we haven't detected any 'supported' flash, return an error. */
                return MFE_NO_FLASH_DETECTED;
            }
            rc = set_bank(mfl, spi_sel - 1); /* set the last flash (flash_params->num_of_flashes >= 1) */
            CHECK_RC(rc);
            break;
        }

        type_name = tmp_flash_info.name;
        if (params_were_set == 0)
        {
            memset(flash_params->type_name, 0, MAX_FLASH_NAME);
            strncpy(flash_params->type_name, type_name, MAX_FLASH_NAME - 1);
            flash_params->log2size = log2size;
            memcpy(flash_info, &tmp_flash_info, sizeof(flash_info_t));
            params_were_set = 1;
        }
        else
        {
            rc = compare_flash_params(flash_params, spi_sel, type_name, log2size);
            CHECK_RC(rc);
        }
        /* Init SST flash. */
        if (mfl->access_type == MFAT_MFILE)
        {
            if ((flash_info->vendor == FV_SST) && (flash_info->type == FMT_SST_25))
            {
                rc = mfl->f_spi_write_status_reg(mfl, SST_STATUS_REG_VAL, SFC_WRSR, 1);
                CHECK_RC(rc);
            }
            else if ((flash_info->vendor == FV_ATMEL) && (flash_info->type == FMT_ATMEL))
            {
                rc = mfl->f_spi_write_status_reg(mfl, ATMEL_STATUS_REG_VAL, SFC_WRSR, 1);
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

/* @input: mfl */
/* @output: access_commands */
/* @return: MfError status */
MfError gen_access_commands(mflash* mfl, flash_access_commands_t* access_commands)
{
    MfError status;

    if (!mfl || !access_commands)
    {
        return MFE_BAD_PARAMS;
    }
    memset(access_commands, 0, sizeof(*access_commands));
    int four_byte_address_needed = is_four_byte_address_needed(mfl, &status);

    if (status != MFE_OK)
    {
        return status;
    }
    *access_commands = ((mfl->attr.log2_bank_size >= FD_256 && four_byte_address_needed) ? gen_4byte_address_access_commands() : gen_3byte_address_access_commands());
    return MFE_OK;
}

int is_srwd_supported_by_flash(u_int8_t vendor, u_int8_t type)
{
    return (vendor == FV_IS25LPXXX && type == FMT_IS25WPXXX);
}

int is_srp_supported_by_flash(uint8_t vendor, uint8_t type, u_int32_t log2_bank_size, MacronixSeriesCode series_code)
{
    if (vendor == FV_WINBOND && type == FMT_WINBOND_IM && (1 << log2_bank_size & (1 << FD_512)) != 0)
    {
        return 1;
    }
    if (is_macronix_mx25u51294g_mx25u51294gxdi08(vendor, type, log2_bank_size, series_code))
    {
        return 1;
    }
    return 0;
}

int is_srl_supported_by_flash(uint8_t vendor, uint8_t type, u_int32_t log2_bank_size, MacronixSeriesCode series_code)
{
    if (vendor == FV_WINBOND && type == FMT_WINBOND_IM && (1 << log2_bank_size & (1 << FD_512)) != 0)
    {
        return 1;
    }
    if (is_macronix_mx25u51294g_mx25u51294gxdi08(vendor, type, log2_bank_size, series_code))
    {
        return 1;
    }
    return 0;
}

int spi_fill_attr_from_params(mflash* mfl, flash_params_t* flash_params, flash_info_t* flash_info)
{
    mfl->attr.log2_bank_size = flash_params->log2size;
    flash_access_commands_t access_commands;
    int rc = gen_access_commands(mfl, &access_commands);

    CHECK_RC(rc);
    mfl->attr.access_commands = access_commands;
    mfl->attr.bank_size = 1 << flash_params->log2size;
    mfl->attr.size = mfl->attr.bank_size * flash_params->num_of_flashes;
    mfl->attr.block_write = 16; /* In SPI context, this is the transaction size. Max is 16. */

    mfl->attr.sector_size = flash_info->sector_size;
    mfl->attr.support_sub_and_sector = flash_info->support_sub_and_sector;
    mfl->attr.command_set = flash_info->command_set;
    mfl->attr.erase_command = flash_info->erase_command;
    mfl->attr.type_str = flash_info->name;

    mfl->attr.quad_en_support = flash_info->quad_en_support;
    mfl->attr.srwd_support = is_srwd_supported_by_flash(flash_info->vendor, flash_info->type);
    mfl->attr.srp_support = is_srp_supported_by_flash(flash_info->vendor, flash_info->type, mfl->attr.log2_bank_size,
        flash_info->series_code);
    mfl->attr.srl_support = is_srl_supported_by_flash(flash_info->vendor, flash_info->type, mfl->attr.log2_bank_size,
        flash_info->series_code);
    mfl->attr.driver_strength_support = flash_info->driver_strength_support;
    mfl->attr.dummy_cycles_support = flash_info->dummy_cycles_support;

    mfl->attr.series_code_support = flash_info->series_code_support;
    mfl->attr.series_code = flash_info->series_code;

    mfl->attr.cmp_support = ((flash_info->vendor == FV_WINBOND && flash_info->type == FMT_WINBOND_IM && ((flash_info->densities & (1 << FD_512)) != 0)) ||
                             is_macronix_mx25u51294g_mx25u51294gxdi08(flash_info->vendor, flash_info->type, mfl->attr.log2_bank_size, flash_info->series_code));

    mfl->attr.write_protect_support = flash_info->write_protected_support;
    mfl->attr.protect_sub_and_sector = flash_info->protect_sub_and_sector;
    mfl->attr.banks_num = flash_params->num_of_flashes;
    mfl->attr.vendor = flash_info->vendor;
    mfl->attr.type = flash_info->type;
    return MFE_OK;
}

#define GET_FLASH_RETRY 2
int st_spi_fill_attr(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;
    flash_params_t* cur_flash_params;
    flash_params_t tmp_flash_params;
    flash_info_t flash_info;
    unsigned type_index = 0;

    if (flash_params == NULL)
    {
        int i = 0;
        /* Get flash params from the flash itself */
        cur_flash_params = &tmp_flash_params;

        while (i < GET_FLASH_RETRY)
        {
            rc = get_flash_params(mfl, cur_flash_params, &flash_info);
            if (rc != MFE_NO_FLASH_DETECTED)
            {
                break;
            }
            i++;
        }
        CHECK_RC(rc);
    }
    else
    {
        /* Get the flash params from the user. */
        rc = get_type_index_by_name(flash_params->type_name, &type_index);
        CHECK_RC(rc);
        memcpy(&flash_info, &(g_flash_info_arr[type_index]), sizeof(flash_info_t));
        cur_flash_params = flash_params;
    }
    /* Init the flash attr according to the flash parameters (which was wither given by the user or read from the flash)
     */
    rc = spi_fill_attr_from_params(mfl, cur_flash_params, &flash_info);
    CHECK_RC(rc);
    FLASH_DPRINTF(("spi_size = %#x,  log2spi_size = %#x, bank_size = %#x, flashes_num = %d\n", mfl->attr.size, mfl->attr.log2_bank_size, mfl->attr.bank_size, cur_flash_params->num_of_flashes));
    return MFE_OK;
}

int read_chunks(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data, bool verbose)
{
    int rc = 0;
    u_int8_t* p = (u_int8_t*)data;

    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    u_int32_t original_len = len;
    /* Note: */
    /* Assuming read block is the same as write block size. */
    /* This is true for current Mellanox devices SPI flash access implementation. */
    /* Check for future devices. */
    u_int32_t block_size = mfl->attr.block_write;
    u_int32_t block_mask = 0;

    /* TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here) */
    u_int8_t tmp_buff[MAX_WRITE_BUFFER_SIZE] = {0};

    block_mask = ~(block_size - 1);
    u_int32_t perc = 0xffffffff;

    if (verbose)
    {
        printf("\33[2K\r"); /* clear the current line */
    }
    while (len)
    {
        u_int32_t i = 0;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;
        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size = block_size;
        u_int8_t* block_data = p;

        /* */
        /* First and last cycles (can be the same one) may not be block aligned. */
        /* Check the status, and copy data to a padded temp bufer if not aligned. */
        /* (there's an option to write partial buffer, but Intel reference code always */
        /* writes full buffer, with pads if needed. I do the dame ...) */
        /* */

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask))
        {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size)
        {
            /* block exceeds given buffer - read to a temp bufer and */
            /* copy the required data to user's bufer. */
            data_size -= suffix_pad_size;
            data_size -= prefix_pad_size;
            block_data = tmp_buff;
        }
        rc = mfl->f_read_blk(mfl, block_addr, block_size, block_data, false);
        CHECK_RC(rc);

        if (suffix_pad_size || prefix_pad_size)
        {
            for (i = 0; i < data_size; i++)
            {
                p[i] = tmp_buff[prefix_pad_size + i];
            }
        }

        /* */
        /* loop advance */
        /* */

        addr += data_size;
        p += data_size;
        len -= data_size;

        if (verbose)
        {
            u_int32_t new_perc = 100 - 100 * (1.0 * len / original_len);
            if (new_perc != perc)
            {
                printf("\r%s%d%c", "Reading flash section: ", new_perc, '%');
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    return MFE_OK;
}

/*////////////////////////////////////// */
/* */
/* InfiniHostIIILx spi  access functions */
/* */
/*////////////////////////////////////// */

int gw_wait_ready(mflash* mfl, const char* msg)
{
    if (mfl->mf->tp == MST_DEV_I2C) // Avoid polling on FlashGW busy bit when the flint interface is i2c.
    { // We can assume that FlashGW HW sends the SPI command much faster than it takes the next transaction on i2c bus
        DPRINTF(("gw_wait_ready: skip polling on FlashGW busy bit for i2c interface\n"));
        return MFE_OK;
    }
    if (mfl->mf->is_zombiefish)
    {
        if (!mfl->mf->vsc_recovery_space_flash_control_vld)
        {
            return MFE_VSC_RECOVERY_SPACE_FLASH_CONTROL_NOT_VALID;
        }
        mset_addr_space(mfl->mf, AS_RECOVERY);
    }
    u_int32_t gw_cmd = 0;
    u_int32_t cnt = 0;

    (void)msg; /* NOT USED FOR NOW */
    do
    {
        /* Timeout checks */
        if (++cnt > FLASH_CMD_CNT)
        {
            /* return errmsg("Flash gateway timeout: %s.", msg); */
            return MFE_TIMEOUT;
        }

        MREAD4(mfl->gw_cmd_register_addr, &gw_cmd);
    } while (EXTRACT(gw_cmd, HBO_BUSY, 1));

    return MFE_OK;
}

int empty_reset(mflash* mfl)
{
    (void)mfl; /* avoid compiler warning */
    return MFE_OK;
}

/*//////////////////////////////////////// */
/* */
/* ConnectX functions implementation */
/* */
/*//////////////////////////////////////// */

int empty_set_bank(mflash* mfl, u_int32_t bank)
{
    /* NULL function - No actual work here - in ConnectX the curr_bank is written in the command word. */
    (void)mfl;  /* Avoid Compiler warning */
    (void)bank; /* Avoid Compiler warning */
    return MFE_OK;
}

/*
 * Consts needed to extract the needed data for the jedec ID
 *  from various flash types.
 */
enum
{
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

int get_flash_info_for_atmel(u_int32_t jedec_id, u_int8_t* type, u_int8_t* density)
{
    u_int8_t tmp_cap = 0;

    tmp_cap = EXTRACT(jedec_id, JEDEC_ATMEL_CAPACITY_BITOFF, JEDEC_ATMEL_CAPACITY_BITLEN);
    *type = EXTRACT(jedec_id, JEDEC_ATMEL_TYPE_BITOFF, JEDEC_ATMEL_TYPE_BITLEN);
    switch (tmp_cap)
    {
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
int get_info_from_jededc_id(u_int32_t jedec_id, u_int8_t* vendor, u_int8_t* type, u_int8_t* density)
{
    int rc = 0;

    *vendor = EXTRACT(jedec_id, JEDEC_VENDOR_ID_BITOFF, JEDEC_VENDOR_ID_BITLEN);
    if (*vendor == FV_ATMEL)
    {
        rc = get_flash_info_for_atmel(jedec_id, type, density);
        CHECK_RC(rc);
    }
    else
    {
        *type = EXTRACT(jedec_id, JEDEC_TYPE_BITOFF, JEDEC_TYPE_BITLEN);
        *density = EXTRACT(jedec_id, JEDEC_CAPACITY_BITOFF, JEDEC_CAPACITY_BITLEN);
    }

    return MFE_OK;
}

int mf_check_spi_channel(mfile* mf)
{
    int retVal = 1;
    u_int32_t value = 0;

    if (mread4(mf, 0x21e4, &value) != sizeof(u_int32_t))
    {
        printf("-E- Cannot get SPI value.\n");
        retVal = 0;
    }
    else
    {
        value = (value >> 8) & 3;
        if ((value != 0x1) && (value != 2))
        {
            retVal = 0;
        }
    }
    printf("-D- Get SPI channel value %u.\n", value);
    return retVal;
}
int cntx_spi_get_type(mflash* mfl, u_int8_t op_type, u_int8_t* vendor, u_int8_t* type, u_int8_t* density)
{
    u_int32_t flash_data = 0;
    int rc = 0;

    rc = mfl->f_int_spi_get_status_data(mfl, op_type, &flash_data, 4);
    CHECK_RC(rc);
    FLASH_DPRINTF(("jedec_info = %#x\n", flash_data));
    /* Get type and some other info from jededc_id */
    get_info_from_jededc_id(flash_data, vendor, type, density);
    FLASH_DPRINTF(("cntx_spi_get_type: vendor = %#x, type = %#x, capacity = %#x\n", *vendor, *type, *density));
    return MFE_OK;
}

#define MFLASH_ENV "MFLASH_BANKS"

int spi_get_num_of_flashes(int prev_num_of_flashes)
{
    char* mflash_env;
    int num = 0;

    if (prev_num_of_flashes != -1)
    {
        return prev_num_of_flashes;
    }

    mflash_env = getenv(MFLASH_ENV);
    if (mflash_env)
    {
        num = atol(mflash_env);
        /* make sure the value makes sense */
        num = (num > 16 || num <= 0) ? -1 : num;
        return num;
    }

    return -1;
}

int spi_update_num_of_banks(mflash* mfl, int prev_num_of_flashes)
{
    int num_of_banks = 0;

    num_of_banks = spi_get_num_of_flashes(prev_num_of_flashes);
    if (num_of_banks == -1)
    {
        if (IS_SIB(mfl->attr.hw_dev_id) || IS_SEN(mfl->attr.hw_dev_id) || IS_SIB2(mfl->attr.hw_dev_id))
        {
            mfl->opts[MFO_NUM_OF_BANKS] = 2;
        }
        else
        {
            mfl->opts[MFO_NUM_OF_BANKS] = 1;
        }
        mfl->opts[MFO_USER_BANKS_NUM] = 0;
    }
    else
    {
        mfl->opts[MFO_NUM_OF_BANKS] = num_of_banks;
        mfl->opts[MFO_USER_BANKS_NUM] = 1;
    }
    return MFE_OK;
}
int cntx_st_spi_page_read(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data, bool verbose)
{
    (void)verbose;
    int rc = 0;
    u_int32_t last_blk_addr = 0;
    u_int32_t last_addr = 0;
    u_int8_t is_first = 1;
    u_int8_t is_last = 0;
    u_int8_t* p = data;

    if (addr & ((u_int32_t)mfl->attr.block_write - 1))
    {
        return MFE_BAD_ALIGN;
    }

    if (size & ((u_int32_t)mfl->attr.block_write - 1))
    {
        return MFE_BAD_ALIGN;
    }

    /* printf("-D- cntx_st_spi_page_read(addr=%05x, u_int32_t size=%03x)\n", addr, size); */

    last_addr = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr)
    {
        if (addr == last_blk_addr)
        {
            is_last = 1;
        }

        rc = mfl->f_st_spi_block_read_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last, false);
        CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p += mfl->attr.block_write;
    }

    return MFE_OK;
}

int cntx_st_spi_block_read(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data, bool verbose)
{
    (void)verbose;
    return mfl->f_st_spi_block_read_ex(mfl, blk_addr, blk_size, data, 1, 1, false);
}
int cntx_st_spi_page_write(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    int rc = 0;
    u_int32_t last_blk_addr = 0;
    u_int32_t last_addr = 0;
    u_int8_t is_first = 1;
    u_int8_t is_last = 0;
    u_int8_t* p = data;

    WRITE_CHECK_ALIGN(addr, mfl->attr.block_write, size);

    last_addr = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr)
    {
        if (addr == last_blk_addr)
        {
            is_last = 1;
        }
        rc = mfl->f_st_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last, size);
        CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p += mfl->attr.block_write;
    }

    return MFE_OK;
}

int cntx_sst_spi_byte_write(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    int rc = 0;
    u_int32_t last_addr = 0;
    u_int8_t* p = data;

    WRITE_CHECK_ALIGN(addr, mfl->attr.block_write, size);

    last_addr = addr + size;

    while (addr < last_addr)
    {
        rc = mfl->f_sst_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p);
        CHECK_RC(rc);
        addr++;
        p++;
    }

    return MFE_OK;
}

int cntx_st_spi_block_write(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data)
{
    return mfl->f_st_spi_block_write_ex(mfl, blk_addr, blk_size, data, 1, 1, blk_size);
}

f_mf_write get_write_blk_func(int command_set)
{
    if (command_set == MCS_STSPI)
    {
        return cntx_st_spi_page_write;
    }
    return cntx_sst_spi_byte_write;
}

int old_flash_lock(mflash* mfl, int lock_state)
{
    /* Obtain GPIO Semaphore */
    static u_int32_t cnt;
    u_int32_t word = 0;

#if !defined(UEFI_BUILD)
    if (IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id) && (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_NO))
    {
        int rc = 0;
        if (lock_state)
        {
            if (!mfl->flash_prog_locked)
            {
                rc = trm_lock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING, MAX_FLASH_PROG_SEM_RETRY_CNT);
                if (!rc)
                {
                    mfl->flash_prog_locked = 1;
                }
            }
        }
        else
        {
            if (mfl->unlock_flash_prog_allowed)
            {
                rc = trm_unlock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING);
                if (!rc)
                {
                    mfl->flash_prog_locked = 0;
                }
            }
        }
        if (rc && (rc != TRM_STS_RES_NOT_SUPPORTED))
        {
            return MFE_SEM_LOCKED;
        }
    }
#endif /* !defined(UEFI) */
    /* timeout at 5 seconds */
    TIMER_INIT_AND_START();

    if (lock_state)
    {
        if (mfl->is_locked)
        {
            return MFE_OK;
        }
        do
        {
            if (++cnt > GPIO_SEM_TRIES)
            {
                cnt = 0;
                printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(SEMAP63, &word);
            if (word)
            {
                msleep(1);
            }
            TIMER_CHECK(5, 0, cnt = 0; return MFE_SEM_LOCKED);
        } while (word);
    }
    else
    {
        MWRITE4(SEMAP63, 0);
        if (cnt > 1)
        {
            /* we are not alone... */
            msleep(1);
        }
        cnt = 0;
    }
    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}

int cntx_flash_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;
    u_int32_t tmp = 0;

    FLASH_ACCESS_DPRINTF(("cntx_flash_init_direct_access(): Flash init to use direct-access\n"));

    /* Without too much details: */
    /* When the ConnectX boots up without a valid FW , the PCIE link may be unstable. */
    /* In that case, turn off the auto reset on link down, so we'll be able to burn the device. */
    MREAD4(0x41270, &tmp);
    if (tmp > 0xfff00000)
    {
        /* we are in livefish. */
        u_int32_t tmp1 = 0;
        MREAD4(0xf3834, &tmp1);
        tmp1 = MERGE(tmp1, 2, 27, 2);
        MWRITE4(0xf3834, tmp1);
    }
    mfl->f_read = read_chunks;
    mfl->f_read_blk = cntx_st_spi_block_read;
    mfl->f_lock = old_flash_lock; /* Flash lock has same address and functionality as in InfiniHost. */
    mfl->f_set_bank = empty_set_bank;
    mfl->f_get_info = cntx_get_flash_info;
    mfl->f_get_jedec_id = cntx_get_jedec_id_direct_access;
    mfl->unlock_flash_prog_allowed = 0;
    mfl->f_spi_status = cntx_st_spi_get_status;
    mfl->supp_sr_mod = 1;
    mfl->f_st_spi_erase_sect = cntx_st_spi_erase_sect;
    mfl->f_int_spi_get_status_data = cntx_int_spi_get_status_data;
    mfl->f_st_spi_block_write_ex = cntx_st_spi_block_write_ex;
    mfl->f_sst_spi_block_write_ex = cntx_sst_spi_block_write_ex;
    mfl->f_st_spi_block_read_ex = cntx_st_spi_block_read_ex;
    mfl->f_spi_write_status_reg = cntx_spi_write_status_reg;
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);

    if ((mfl->attr.command_set == MCS_STSPI) || (mfl->attr.command_set == MCS_SSTSPI))
    {
        mfl->f_reset = empty_reset; /* Null func */
        mfl->f_write_blk = get_write_blk_func(mfl->attr.command_set);

        mfl->attr.page_write = 256;
        mfl->f_write = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    }
    else
    {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    /* flash parameter access methods: */
    mfl->f_get_quad_en = mf_get_quad_en_direct_access;
    mfl->f_set_quad_en = mf_set_quad_en_direct_access;
    mfl->f_get_driver_strength = mf_get_driver_strength_direct_access;
    mfl->f_set_driver_strength = mf_set_driver_strength_direct_access;
    mfl->f_get_dummy_cycles = mf_get_dummy_cycles_direct_access;
    mfl->f_set_dummy_cycles = mf_set_dummy_cycles_direct_access;
    mfl->f_get_write_protect = mf_get_write_protect_direct_access;
    mfl->f_set_write_protect = mf_set_write_protect_direct_access;

    mfl->unlock_blocked = 0;
    rc = mfl->f_reset(mfl);
    return MFE_OK;
}

/* InfiniScale 4 (IS4) functions: */

int is4_init_gpios(mflash* mfl)
{
    (void)mfl;
    return MFE_NOT_IMPLEMENTED;
}

int is4_flash_lock(mflash* mfl, int lock_state)
{
    if (mfl->mf->is_zombiefish)
    {
        if (!mfl->mf->vsc_recovery_space_flash_control_vld)
        {
            return MFE_VSC_RECOVERY_SPACE_FLASH_CONTROL_NOT_VALID;
        }
        mset_addr_space(mfl->mf, AS_RECOVERY);
    }
    /* Obtain GPIO Semaphore */
    static u_int32_t cnt;
    uint32_t badacce6 = 3134901478; // this is the return value of gw_cmd_register when trying to read CR space on a secured device
    u_int32_t word = 0;
    u_int32_t lock_status = 0;

    /* timeout at 5 seconds */
    TIMER_INIT_AND_START();

    if (lock_state)
    {
        do
        {
            if (++cnt > GPIO_SEM_TRIES)
            {
                cnt = 0;
                printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(mfl->gw_cmd_register_addr, &word);

            if (badacce6 == word)
            {
                return MFE_NO_FLASH_DETECTED;
            }

            lock_status = EXTRACT(word, HBO_LOCK, 1);
            if (lock_status)
            {
                msleep(1);
            }
            TIMER_CHECK(5, 0, cnt = 0; return MFE_SEM_LOCKED);
        } while (lock_status);
    }
    else
    {
        MWRITE4(mfl->gw_cmd_register_addr, 0);
        if (cnt > 1)
        {
            /* we are not alone */
            msleep(1);
        }
        cnt = 0;
    }

    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}

int disable_gcm(mflash* mfl)
{
    if (mfl->mf->is_zombiefish)
    {
        if (!mfl->mf->vsc_recovery_space_flash_control_vld)
        {
            return MFE_VSC_RECOVERY_SPACE_FLASH_CONTROL_NOT_VALID;
        }
        mset_addr_space(mfl->mf, AS_RECOVERY);
    }
    u_int32_t data = 0;

    MREAD4(mfl->gcm_en_addr, &data);
    data = MERGE(data, 0, 0, 1);
    MWRITE4(mfl->gcm_en_addr, data);

    return 0;
}

int disable_cache_replacement(mflash* mfl)
{
    u_int32_t data = 0;

    MREAD4(mfl->cache_repacement_en_addr, &data);
    data = MERGE(data, 0, 0, 1); /* We put 0 in the first bit of the read data */
    MWRITE4(mfl->cache_repacement_en_addr, data);

    return 0;
}

int restore_cache_replacemnt(mflash* mfl)
{
    u_int32_t data = 0;

    MREAD4(mfl->cache_repacement_en_addr, &data);
    data = MERGE(data, 1, 0, 1); /* We put 1 in the first bit of the read data */
    MWRITE4(mfl->cache_repacement_en_addr, data);
    return MFE_OK;
}

void init_freq_configuration_fields(mflash* mfl)
{
    switch (mfl->dm_dev_id)
    {
        case DeviceConnectX7:
            mfl->is_freq_handle_required = true;
            mfl->core_clocks_per_usec_addr = 0x7f4;
            mfl->flash_div_addr = 0xfe804;
            break;

        case DeviceBlueField3:
            mfl->is_freq_handle_required = true;
            mfl->core_clocks_per_usec_addr = 0x7f4;
            mfl->flash_div_addr = 0xff804;
            break;

        default:
            break;
    }
}

int read_freq_configurations(mflash* mfl)
{
    if (!mfl->core_clocks_per_usec)
    { /* If field was already read then we skip */
        if (mread4(mfl->mf, mfl->core_clocks_per_usec_addr, &(mfl->core_clocks_per_usec)) != 4)
        {
            printf("-E- Failed to read core_clocks_per_usec\n");
            return MFE_CR_ERROR;
        }
    }
    if (!mfl->orig_flash_div_reg)
    { /* If field was already read then we skip */
        if (mread4(mfl->mf, mfl->flash_div_addr, &(mfl->orig_flash_div_reg)) != 4)
        {
            printf("-E- Failed to read flash_div_register\n");
            return MFE_CR_ERROR;
        }
    }
    return MFE_OK;
}

int get_flash_freq(mflash* mfl, u_int32_t* freq)
{
    int rc = read_freq_configurations(mfl);

    CHECK_RC(rc);
    u_int32_t flash_div = EXTRACT(mfl->orig_flash_div_reg, 0, 4); /* flash_div field is 4bits */

    *freq = mfl->core_clocks_per_usec / (2 * (flash_div + 1));
    return MFE_OK;
}

int write_flash_div(mflash* mfl, u_int32_t new_flash_div)
{
    u_int32_t new_flash_div_register = MERGE(mfl->orig_flash_div_reg, new_flash_div, 0, 4);

    FLASH_DPRINTF(("Setting new flash_div = %d\n", new_flash_div));
    if (mwrite4(mfl->mf, mfl->flash_div_addr, new_flash_div_register) != 4)
    {
        printf("-E- Writing 0x%08x to flash_div register failed\n", new_flash_div_register);
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

int decrease_flash_freq(mflash* mfl)
{
    int rc = MFE_OK;

    if (mfl->is_freq_handle_required)
    {
        u_int32_t freq = 0;
        rc = get_flash_freq(mfl, &freq);
        CHECK_RC(rc);
        if (freq <= MAX_FLASH_FREQ)
        {
            /* Flash freq is already in a valid range for OCR operation */
            mfl->is_freq_handle_required = false; /* Setting this will skip this logic next time we're here */
        }
        else
        {
            /* Calculate new flash_div value to decrease flash frequency to valid value for OCR operation */
            u_int32_t new_flash_div = EXTRACT(mfl->orig_flash_div_reg, 0, 4); /* flash_div field is 4bits */
            FLASH_DPRINTF(
              ("Flash freq (%dMHz) higher than allowed (%dMHz) for OCR operation: core_clocks_per_usec = %d, flash_div = %d\n", freq, MAX_FLASH_FREQ, mfl->core_clocks_per_usec, new_flash_div));
            while (freq > MAX_FLASH_FREQ)
            {
                new_flash_div++; /* Reducing freq by incrementing flash_div (incrementing by 1 should to be enough) */
                freq = mfl->core_clocks_per_usec / (2 * (new_flash_div + 1));
            }
            FLASH_DPRINTF(("Reducing flash freq to %dMHz, using new flash_div = %d\n", freq, new_flash_div));
            rc = write_flash_div(mfl, new_flash_div);
            CHECK_RC(rc);
            mfl->is_freq_changed = true;
        }
    }
    return rc;
}

int restore_flash_freq(mflash* mfl)
{
    int rc = MFE_OK;

    if (mfl->is_freq_changed)
    {
        u_int32_t orig_flash_div = EXTRACT(mfl->orig_flash_div_reg, 0, 4); /* flash_div field is 4bits */
        FLASH_DPRINTF(("Restoring original flash_div = %d\n", orig_flash_div));
        rc = write_flash_div(mfl, orig_flash_div);
        CHECK_RC(rc);
        mfl->is_freq_changed = false;
    }
    return rc;
}

int seventh_gen_flash_lock(mflash* mfl, int lock_state)
{
    int rc = 0;

    if (lock_state == 1)
    { /* lock the flash */
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
        rc = disable_gcm(mfl);
        CHECK_RC(rc);
        rc = gw_wait_ready(mfl, "WAIT TO BUSY");
        CHECK_RC(rc);
    }
    else
    { /* unlock the flash */
        /* Restoring GCM is handled by FW */
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int sixth_gen_flash_lock(mflash* mfl, int lock_state)
{
    int rc = 0;

    if (lock_state == 1)
    { /* lock the flash */
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
        rc = disable_gcm(mfl);
        CHECK_RC(rc);
        rc = disable_cache_replacement(mfl);
        CHECK_RC(rc);
        rc = decrease_flash_freq(mfl);
        CHECK_RC(rc);
        rc = gw_wait_ready(mfl, "WAIT TO BUSY");
        CHECK_RC(rc);
    }
    else
    { /* unlock the flash */
        rc = restore_flash_freq(mfl);
        CHECK_RC(rc);
        rc = restore_cache_replacemnt(mfl);
        CHECK_RC(rc);
        /* Restoring GCM is handled by FW */
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int connectib_flash_lock(mflash* mfl, int lock_state)
{
    int rc = 0;

    if (lock_state == 1)
    { /* lock the flash */
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
        rc = disable_cache_replacement(mfl);
        CHECK_RC(rc);
        rc = gw_wait_ready(mfl, "WAIT TO BUSY");
        CHECK_RC(rc);
    }
    else
    { /* unlock the flash */
        rc = restore_cache_replacemnt(mfl);
        CHECK_RC(rc);
        rc = is4_flash_lock(mfl, lock_state);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

#define SX_CS_SUPPORT_ADDR 0xF0420

#define HW_DEV_ID 0xf0014
#define CX5_EFUSE_ADDR 0xf0c0c

#define CACHE_REP_OFF_RAVEN 0xf0440
#define CACHE_REP_CMD_RAVEN 0xf0448
#define CACHE_REP_OFF_NEW_GW_ADDR 0xf0484
#define CACHE_REP_CMD_NEW_GW_ADDR 0xf0488
int check_cache_replacement_guard(mflash* mfl, u_int8_t* needs_cache_replacement)
{
    *needs_cache_replacement = 0;

    /* When we access via command interface, we assume there is a cache replacement! */
    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF)
    {
        if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD])
        {
            /* dont allow overidding cache replacement in mellanox OS env */
            return MFE_OCR_NOT_SUPPORTED;
        }
        *needs_cache_replacement = 1;
        return MFE_OK;
    }

    if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0)
    {
        u_int32_t off = 0, cmd = 0, data = 0;
        dm_dev_id_t devid_t = DeviceUnknown;
        u_int32_t devid = 0;
        u_int32_t revid = 0;
        int rc = dm_get_device_id(mfl->mf, &devid_t, &devid, &revid);
        if (rc)
        {
            return rc;
        }

        /* TODO - fix for QTM3/CX8/ArcusE/BF4 */
        /* Read the Cache replacement offset and cmd fields */
        if ((devid_t == DeviceQuantum2) || (devid_t == DeviceQuantum3) || (devid_t == DeviceNVLink6_Switch) || (devid_t == DeviceSpectrum4) || (devid_t == DeviceSpectrum5) ||
            (devid_t == DeviceSpectrum6) || (devid_t == DeviceConnectX7) || (devid_t == DeviceConnectX8) || (devid_t == DeviceConnectX8_Pure_PCIe_Switch) || (devid_t == DeviceConnectX9) ||
            (devid_t == DeviceConnectX9_Pure_PCIe_Switch))
        {
            MREAD4(CACHE_REP_OFF_NEW_GW_ADDR, &data);
            off = data;
            MREAD4(CACHE_REP_CMD_NEW_GW_ADDR, &data);
            cmd = EXTRACT(data, 24, 8);
        }
        else if (!dm_dev_is_raven_family_switch(devid_t))
        {
            MREAD4(mfl->cache_rep_offset_field_addr, &data);
            off = EXTRACT(data, 0, 26);
            MREAD4(mfl->cache_rep_cmd_field_addr, &data);
            cmd = EXTRACT(data, 16, 8);
        }
        else
        { /* switches */
            MREAD4(CACHE_REP_OFF_RAVEN, &data);
            off = EXTRACT(data, 0, 26);
            MREAD4(CACHE_REP_CMD_RAVEN, &data);
            cmd = EXTRACT(data, 16, 8);
        }
        FLASH_ACCESS_DPRINTF(("check_cache_replacement_guard(): off=%d, cmd=%d\n", off, cmd));

        /* Check if the offset and cmd are zero in order to continue burning. */
        if ((cmd != 0) || (off != 0))
        {
            *needs_cache_replacement = 1;
        }
    }
    else
    {
        /* Here we ignore the cache replacement check */
        /* We need to execute a write in order to do any needed cache replacement */
        /* Reset the HW ID which is read only register. */
        MWRITE4(HW_DEV_ID, 0);
    }

    return MFE_OK;
}

int mf_acquire_persistent_lock(mflash* mfl)
{
    int rc = 0;
    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);

    mfile* mf = mf_get_mfile(mfl);
    if (mf && dm_is_livefish_mode(mf))
    {
        mfl->unlock_blocked = 1;
    }

    return MFE_OK;
}

int mf_release_persistent_lock(mflash* mfl)
{
    mfl->unlock_blocked = 0;
    return release_semaphore(mfl, 0);
}

int mfl_com_lock(mflash* mfl)
{
    int rc = 0;

    /* if we already locked the semaphore we dont want to re-lock it */
    if (mfl->is_locked && ((mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_INBAND) || (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 1)))
    { /* on inband w/o ocr we need to extend the lock */
        return MFE_OK;
    }
    rc = mfl->f_lock(mfl, 1);
    if (!mfl->opts[MFO_IGNORE_SEM_LOCK])
    {
        CHECK_RC(rc);
    }
    else
    {
        mfl->is_locked = 1;
        mfl->unlock_flash_prog_allowed = 1;
    }
    return MFE_OK;
}

int mf_release_semaphore(mflash* mfl)
{
    mfl->unlock_flash_prog_allowed = 1;
    return release_semaphore(mfl, 1);
}

int release_semaphore(mflash* mfl, int ignore_writer_lock)
{
    int rc = 0;

    if ((mfl->is_locked || mfl->flash_prog_locked) && mfl->f_lock && (!mfl->writer_lock || ignore_writer_lock) && !mfl->unlock_blocked)
    {
        rc = mfl->f_lock(mfl, 0);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int gen6_flash_init_com(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;

    FLASH_ACCESS_DPRINTF(("gen6_flash_init_com(): Flash init to use direct-access\n"));

    /* TODO: Enable page_read (slightly better perf) */
    mfl->f_read = read_chunks;
    mfl->f_read_blk = cntx_st_spi_block_read; /* need fix */
    mfl->f_set_bank = empty_set_bank;
    mfl->f_get_info = cntx_get_flash_info; /* need fix */
    mfl->f_get_jedec_id = cntx_get_jedec_id_direct_access;
    mfl->f_get_quad_en = mf_get_quad_en_direct_access;
    mfl->f_set_quad_en = mf_set_quad_en_direct_access;
    mfl->f_get_driver_strength = mf_get_driver_strength_direct_access;
    mfl->f_set_driver_strength = mf_set_driver_strength_direct_access;
    mfl->f_get_dummy_cycles = mf_get_dummy_cycles_direct_access;
    mfl->f_set_dummy_cycles = mf_set_dummy_cycles_direct_access;
    mfl->f_get_write_protect = mf_get_write_protect_direct_access;
    mfl->f_set_write_protect = mf_set_write_protect_direct_access;

    mfl->f_st_spi_erase_sect = new_gw_st_spi_erase_sect;
    mfl->f_int_spi_get_status_data = new_gw_int_spi_get_status_data;
    mfl->f_st_spi_block_write_ex = new_gw_st_spi_block_write_ex;
    mfl->f_sst_spi_block_write_ex = new_gw_sst_spi_block_write_ex;
    mfl->f_st_spi_block_read_ex = new_gw_st_spi_block_read_ex;
    mfl->f_spi_write_status_reg = new_gw_spi_write_status_reg;

    mfl->f_spi_status = cntx_st_spi_get_status; /* need fix */
    mfl->supp_sr_mod = 1;
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);

    if ((mfl->attr.command_set == MCS_STSPI) || (mfl->attr.command_set == MCS_SSTSPI))
    {
        mfl->f_reset = empty_reset; /* Null func */
        mfl->f_write_blk = get_write_blk_func(mfl->attr.command_set);
        mfl->attr.page_write = 256;
        mfl->f_write = write_chunks;
        mfl->f_erase_sect = new_gw_st_spi_erase_sect;
    }
    else
    {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    /* flash parameter access methods: */

    mfl->unlock_blocked = 0;
    rc = mfl->f_reset(mfl);
    return MFE_OK;
}
/* ConnectX and Is4 flash interfaces are identical (except lock function) */
/* Use same functions */
/* */
/* TODO: Unify fith ConnectX inif function */

int gen4_flash_init_com(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;

    FLASH_ACCESS_DPRINTF(("gen4_flash_init_com(): Flash init to use direct-access\n"));

    /* TODO: Enable page_read (slightly better perf) */
    /* mfl->f_read           = cntx_st_spi_page_read; */
    mfl->f_read = read_chunks;
    mfl->f_read_blk = cntx_st_spi_block_read;
    mfl->f_set_bank = empty_set_bank;
    mfl->f_get_info = cntx_get_flash_info;
    mfl->f_st_spi_erase_sect = cntx_st_spi_erase_sect;
    mfl->f_get_jedec_id = cntx_get_jedec_id_direct_access;
    mfl->f_int_spi_get_status_data = cntx_int_spi_get_status_data;
    mfl->f_st_spi_block_write_ex = cntx_st_spi_block_write_ex;
    mfl->f_sst_spi_block_write_ex = cntx_sst_spi_block_write_ex;
    mfl->f_st_spi_block_read_ex = cntx_st_spi_block_read_ex;
    mfl->f_spi_write_status_reg = cntx_spi_write_status_reg;
    mfl->f_spi_status = cntx_st_spi_get_status;
    mfl->supp_sr_mod = 1;
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);

    if ((mfl->attr.command_set == MCS_STSPI) || (mfl->attr.command_set == MCS_SSTSPI))
    {
        mfl->f_reset = empty_reset; /* Null func */
        /* mfl->f_write_blk  = cntx_st_spi_block_write; */

        mfl->f_write_blk = get_write_blk_func(mfl->attr.command_set);

        mfl->attr.page_write = 256;
        mfl->f_write = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    }
    else
    {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    /* flash parameter access methods: */
    mfl->f_get_quad_en = mf_get_quad_en_direct_access;
    mfl->f_set_quad_en = mf_set_quad_en_direct_access;
    mfl->f_get_driver_strength = mf_get_driver_strength_direct_access;
    mfl->f_set_driver_strength = mf_set_driver_strength_direct_access;
    mfl->f_get_dummy_cycles = mf_get_dummy_cycles_direct_access;
    mfl->f_set_dummy_cycles = mf_set_dummy_cycles_direct_access;
    mfl->f_get_write_protect = mf_get_write_protect_direct_access;
    mfl->f_set_write_protect = mf_set_write_protect_direct_access;
    
    mfl->unlock_blocked = 0;
    rc = mfl->f_reset(mfl);

    return MFE_OK;
}

int is4_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
    mfl->f_lock = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params);
}

static void flash_update_amos_gearbox_gw(mflash* mfl)
{
    FLASH_ACCESS_DPRINTF(("flash_update_amos_gearbox_gw()\n"));
    mfl->gw_data_field_addr = HCR_FLASH_GEARBOX_DATA;
    mfl->gw_cmd_register_addr = HCR_FLASH_GEARBOX_CMD;
    mfl->gw_addr_field_addr = HCR_FLASH_GEARBOX_ADDR;
    mfl->cache_repacement_en_addr = HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_EN_ADDR;
    mfl->cache_rep_cmd_field_addr = HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_CMD;
    mfl->cache_rep_offset_field_addr = HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_OFFSET;
}

int sx_flash_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    mfl->f_lock = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params);
}

void update_seventh_gen_addrs(mflash* mfl)
{
    /* Registers addresses */
    if (mfl->dm_dev_id == DeviceQuantum3 || mfl->dm_dev_id == DeviceNVLink6_Switch || mfl->dm_dev_id == DeviceSpectrum5 || mfl->dm_dev_id == DeviceSpectrum6)
    {
        mfl->gw_cmd_register_addr = HCR_7GEN_QTM3_FLASH_CMD;
        mfl->gw_data_field_addr = HCR_7GEN_QTM3_FLASH_DATA;
        mfl->gcm_en_addr = HCR_7GEN_QTM3_GCM_EN_ADDR;
        mfl->gw_addr_field_addr = HCR_7GEN_QTM3_FLASH_ADDR;
        mfl->gw_data_size_register_addr = HCR_7GEN_QTM3_FLASH_DATA_SIZE;
        if (is_zombiefish_device(mfl->mf))
        {
            mfl->gw_cmd_register_addr = mfl->gw_cmd_register_addr - HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_field_addr = mfl->gw_data_field_addr - HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gcm_en_addr = mfl->gcm_en_addr - HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_addr_field_addr = mfl->gw_addr_field_addr - HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_size_register_addr = mfl->gw_data_size_register_addr - HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        }
    }
    else if (mfl->dm_dev_id == DeviceConnectX8 || mfl->dm_dev_id == DeviceConnectX8_Pure_PCIe_Switch)
    {
        mfl->gw_cmd_register_addr = HCR_7GEN_CX8_FLASH_CMD;
        mfl->gw_data_field_addr = HCR_7GEN_CX8_FLASH_DATA;
        mfl->gcm_en_addr = HCR_7GEN_CX8_GCM_EN_ADDR;
        mfl->gw_addr_field_addr = HCR_7GEN_CX8_FLASH_ADDR;
        mfl->gw_data_size_register_addr = HCR_7GEN_CX8_FLASH_DATA_SIZE;
        if (is_zombiefish_device(mfl->mf))
        {
            mfl->gw_cmd_register_addr = mfl->gw_cmd_register_addr - HCR_7GEN_CX8_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_field_addr = mfl->gw_data_field_addr - HCR_7GEN_CX8_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gcm_en_addr = mfl->gcm_en_addr - HCR_7GEN_CX8_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_addr_field_addr = mfl->gw_addr_field_addr - HCR_7GEN_CX8_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_size_register_addr = mfl->gw_data_size_register_addr - HCR_7GEN_CX8_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        }
    }
    else if (mfl->dm_dev_id == DeviceConnectX9 || mfl->dm_dev_id == DeviceConnectX9_Pure_PCIe_Switch)
    {
        mfl->gw_cmd_register_addr = HCR_7GEN_CX9_FLASH_CMD;
        mfl->gw_data_field_addr = HCR_7GEN_CX9_FLASH_DATA;
        mfl->gcm_en_addr = HCR_7GEN_CX9_GCM_EN_ADDR;
        mfl->gw_addr_field_addr = HCR_7GEN_CX9_FLASH_ADDR;
        mfl->gw_data_size_register_addr = HCR_7GEN_CX9_FLASH_DATA_SIZE;
        if (is_zombiefish_device(mfl->mf))
        {
            mfl->gw_cmd_register_addr = mfl->gw_cmd_register_addr - HCR_7GEN_CX9_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_field_addr = mfl->gw_data_field_addr - HCR_7GEN_CX9_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gcm_en_addr = mfl->gcm_en_addr - HCR_7GEN_CX9_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_addr_field_addr = mfl->gw_addr_field_addr - HCR_7GEN_CX9_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_size_register_addr = mfl->gw_data_size_register_addr - HCR_7GEN_CX9_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        }
    }
    else if (mfl->dm_dev_id == DeviceArcusE)
    {
        mfl->gw_cmd_register_addr = HCR_7GEN_ARCUSE_FLASH_CMD;
        mfl->gw_data_field_addr = HCR_7GEN_ARCUSE_FLASH_DATA;
        mfl->gcm_en_addr = HCR_7GEN_ARCUSE_GCM_EN_ADDR;
        mfl->gw_addr_field_addr = HCR_7GEN_ARCUSE_FLASH_ADDR;
        mfl->gw_data_size_register_addr = HCR_7GEN_ARCUSE_FLASH_DATA_SIZE;
    }
    else if (mfl->dm_dev_id == DeviceSpectrum6)
    {
        mfl->gw_cmd_register_addr = HCR_7GEN_QTM3_FLASH_CMD;
        mfl->gw_data_field_addr = HCR_7GEN_QTM3_FLASH_DATA;
        mfl->gcm_en_addr = HCR_7GEN_QTM3_GCM_EN_ADDR;
        mfl->gw_addr_field_addr = HCR_7GEN_QTM3_FLASH_ADDR;
        mfl->gw_data_size_register_addr = HCR_7GEN_QTM3_FLASH_DATA_SIZE;
        if (is_zombiefish_device(mfl->mf))
        {
            mfl->gw_cmd_register_addr = mfl->gw_cmd_register_addr - HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_field_addr = mfl->gw_data_field_addr - HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gcm_en_addr = mfl->gcm_en_addr - HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_addr_field_addr = mfl->gw_addr_field_addr - HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
            mfl->gw_data_size_register_addr = mfl->gw_data_size_register_addr - HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        }
    }

    /* Fields bit offsets and lengths */
    mfl->gw_rw_bit_offset = HBO_7GEN_RW;
    mfl->gw_cmd_phase_bit_offset = HBO_7GEN_CMD_PHASE;
    mfl->gw_addr_phase_bit_offset = HBO_7GEN_ADDR_PHASE;
    mfl->gw_data_phase_bit_offset = HBO_7GEN_DATA_PHASE;
    mfl->gw_cs_hold_bit_offset = HBO_7GEN_CS_HOLD;
    mfl->gw_chip_select_bit_offset = HBO_7GEN_CHIP_SELECT;
    mfl->gw_addr_size_bit_offset = HBO_7GEN_ADDR_SIZE;
    mfl->gw_cmd_bit_offset = HBO_7GEN_CMD;
    mfl->gw_cmd_bit_len = HBS_7GEN_CMD;
    mfl->gw_busy_bit_offset = HBO_7GEN_BUSY;
}

void update_sixth_gen_addrs(mflash* mfl)
{
    mfl->gw_addr_field_addr = HCR_NEW_GW_FLASH_ADDR;
    mfl->gw_addr_phase_bit_offset = HBO_ADDR_PHASE;
    mfl->gw_addr_size_bit_offset = HBO_NEW_GW_ADDR_SIZE;
    mfl->gw_busy_bit_offset = HBO_BUSY;
    mfl->gw_chip_select_bit_offset = HBO_NEW_GW_CHIP_SELECT;
    mfl->gw_rw_bit_offset = HBO_READ_OP;
    mfl->gw_cmd_phase_bit_offset = HBO_CMD_PHASE;
    mfl->gw_data_phase_bit_offset = HBO_DATA_PHASE;
    mfl->gw_data_size_bit_offset = HBO_DATA_SIZE;
    mfl->gw_data_size_bit_len = HBS_NEW_GW_DATA_SIZE;
    mfl->gw_cmd_bit_offset = HBO_CMD;
    mfl->gw_cmd_bit_len = HBS_CMD;
    mfl->gw_cs_hold_bit_offset = HBO_CS_HOLD;
    mfl->cache_repacement_en_addr = HCR_NEW_GW_CACHE_REPLACEMNT_EN_ADDR;
    mfl->gcm_en_addr = HCR_NEW_GW_GCM_EN_ADDR;
    init_freq_configuration_fields(mfl);

    if (is_zombiefish_device(mfl->mf))
    {
        mfl->gw_addr_field_addr = mfl->gw_addr_field_addr - HCR_NEW_GW_FLASH_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        mfl->cache_repacement_en_addr = mfl->cache_repacement_en_addr - HCR_NEW_GW_FLASH_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
        mfl->gcm_en_addr = mfl->gcm_en_addr - HCR_NEW_GW_FLASH_ADDR + VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS;
    }
}

int seventh_gen_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    update_seventh_gen_addrs(mfl);

    mfl->f_lock = seventh_gen_flash_lock;
    return gen6_flash_init_com(mfl, flash_params);
}

int sixth_gen_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    update_sixth_gen_addrs(mfl);

    mfl->f_lock = sixth_gen_flash_lock;
    return gen6_flash_init_com(mfl, flash_params);
}

int fifth_gen_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    mfl->f_lock = connectib_flash_lock;
    return gen4_flash_init_com(mfl, flash_params);
}

int sx_get_flash_info(mflash* mfl, flash_info_t* f_info, int* log2size, u_int8_t* no_flash)
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

int sx_get_jedec_id(mflash* mfl, u_int32_t* jedec_id_p)
{
    int rc = 0;
    mfpa_command_args mfpa_args;

    memset(&mfpa_args, 0, sizeof(mfpa_args));
    mfpa_args.flash_bank = get_bank_int(mfl);

    rc = check_access_type(mfl);
    CHECK_RC(rc);

    rc = com_get_jedec(mfl->mf, &mfpa_args);
    *jedec_id_p = mfpa_args.jedec_id;
    *jedec_id_p = ___my_swab32(*jedec_id_p);
    FLASH_DPRINTF(("jedec_id = %#x\n", *jedec_id_p));

    return rc;
}

int sx_block_read(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data, bool verbose)
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

int sx_block_write(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
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

int sx_flash_lock(mflash* mfl, int lock_state)
{
    return sx_flash_lock_by_type(mfl, lock_state);
}

int sx_erase_sect(mflash* mfl, u_int32_t addr)
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

int empty_get_status(mflash* mfl, u_int8_t op_type, u_int8_t* status)
{
    /* Avoid warnings */
    (void)mfl;
    (void)op_type;
    (void)status;

    return MFE_NOT_SUPPORTED_OPERATION;
}

#define MAX_BLOCK_SIZE(hw_dev_id) (((hw_dev_id) == CX3_HW_ID || hw_dev_id == CX3_PRO_HW_ID) ? MAX_WRITE_BUFFER_SIZE : 128)

static int get_the_max_reg_size(mfile* mf, maccess_reg_method_t reg_method)
{
    u_int32_t max_reg_size = mget_max_reg_size(mf, reg_method);

    if (mf->flags & MDEVS_IB && (reg_method == MACCESS_REG_METHOD_SET) && (max_reg_size > INBAND_MAX_REG_SIZE))
    {
        max_reg_size = INBAND_MAX_REG_SIZE;
    }
    return max_reg_size;
}

static int update_max_write_size(mflash* mfl)
{
    u_int32_t max_reg_size = get_the_max_reg_size(mfl->mf, MACCESS_REG_METHOD_SET);
    u_int32_t max_block_size = MAX_BLOCK_SIZE(mfl->attr.hw_dev_id);

    if (!max_reg_size)
    {
        return MFE_BAD_PARAMS;
    }
    max_reg_size = NEAREST_POW2(max_reg_size);
    /* limit maximal write to max_block_size */
    max_block_size = max_reg_size < max_block_size ? max_reg_size : max_block_size;
    mfl->attr.block_write = max_block_size;
    mfl->attr.page_write = max_block_size;
    return ME_OK;
}

/* access flash via FW using Flash Access Registers (either by INBAND/ICMD/TOOLS_HCR) */
int flash_init_inband_access(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;

    FLASH_ACCESS_DPRINTF(("flash_init_inband_access(): Flash init to use MFBA\n"));

    mfl->f_read = read_chunks;
    mfl->f_write = write_chunks;
    mfl->f_reset = empty_reset;
    mfl->f_set_bank = empty_set_bank;

    mfl->f_get_info = sx_get_flash_info;
    mfl->f_get_jedec_id = sx_get_jedec_id;
    mfl->f_lock = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk = sx_block_write;
    mfl->f_read_blk = sx_block_read;
    mfl->f_spi_status = empty_get_status;

    mfl->supp_sr_mod = 0;

    /* flash parameter access methods: */
    mfl->f_get_quad_en = sx_get_quad_en;
    mfl->f_set_quad_en = sx_set_quad_en;
    mfl->f_get_driver_strength = sx_get_driver_strength;
    mfl->f_set_driver_strength = sx_set_driver_strength;
    mfl->f_get_dummy_cycles = sx_get_dummy_cycles;
    mfl->f_set_dummy_cycles = sx_set_dummy_cycles;
    mfl->f_get_write_protect = sx_get_write_protect;
    mfl->f_set_write_protect = sx_set_write_protect;
    mfl->f_st_spi_erase_sect = cntx_st_spi_erase_sect;
    mfl->f_int_spi_get_status_data = cntx_int_spi_get_status_data;
    mfl->f_st_spi_block_write_ex = cntx_st_spi_block_write_ex;
    mfl->f_sst_spi_block_write_ex = cntx_sst_spi_block_write_ex;
    mfl->f_st_spi_block_read_ex = cntx_st_spi_block_read_ex;
    mfl->f_spi_write_status_reg = cntx_spi_write_status_reg;

    /* Get the flash attribute */
    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);
    update_max_write_size(mfl);
    CHECK_RC(rc);
    return MFE_OK;
}

int uefi_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;

    FLASH_ACCESS_DPRINTF(("uefi_flash_init(): Flash init to use MFBA\n"));

    mfl->f_read = read_chunks;
    mfl->f_write = write_chunks;
    mfl->f_reset = empty_reset;
    mfl->f_set_bank = empty_set_bank;

    mfl->f_get_info = sx_get_flash_info;
    mfl->f_get_jedec_id = sx_get_jedec_id;
    mfl->f_lock = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk = sx_block_write;
    mfl->f_read_blk = sx_block_read;
    mfl->f_spi_status = empty_get_status;

    mfl->supp_sr_mod = 0;

    /* flash parameter access methods: */
    mfl->f_get_quad_en = sx_get_quad_en;
    mfl->f_set_quad_en = sx_set_quad_en;
    mfl->f_get_driver_strength = sx_get_driver_strength;
    mfl->f_set_driver_strength = sx_set_driver_strength;
    mfl->f_get_dummy_cycles = sx_get_dummy_cycles;
    mfl->f_set_dummy_cycles = sx_set_dummy_cycles;
    mfl->f_get_write_protect = sx_get_write_protect;
    mfl->f_set_write_protect = sx_set_write_protect;
    mfl->f_st_spi_erase_sect = cntx_st_spi_erase_sect;
    mfl->f_int_spi_get_status_data = cntx_int_spi_get_status_data;
    mfl->f_st_spi_block_write_ex = cntx_st_spi_block_write_ex;
    mfl->f_sst_spi_block_write_ex = cntx_sst_spi_block_write_ex;
    mfl->f_st_spi_block_read_ex = cntx_st_spi_block_read_ex;
    mfl->f_spi_write_status_reg = cntx_spi_write_status_reg;

    /* Get the flash attribute */

    rc = st_spi_fill_attr(mfl, flash_params);
    CHECK_RC(rc);
    update_max_write_size(mfl);
    CHECK_RC(rc);
    return MFE_OK;
}

int flash_init_fw_access(mflash* mfl, flash_params_t* flash_params)
{
    /* This function checks the access type in order to select the access functions */

    int rc = 0;

    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_NO)
    {
        rc = flash_init_inband_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        return MFE_DIRECT_FW_ACCESS_DISABLED;
    }

    if (mfl->opts[MFO_IGNORE_SEM_LOCK])
    {
        rc = mfl->f_lock(mfl, 0);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int sx_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;
    u_int8_t needs_cache_replacement = 0;

    rc = check_cache_replacement_guard(mfl, &needs_cache_replacement);
    CHECK_RC(rc);

    if (needs_cache_replacement)
    {
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        rc = sx_flash_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int icmd_init(mflash* mfl)
{
    /* Clear  semaphore when asked to by flint or any tool using mflash */
    if (mfl->opts[MFO_IGNORE_SEM_LOCK])
    {
        if (icmd_clear_semaphore(mfl->mf) != ME_OK)
        {
            return MFE_CR_ERROR;
        }
    }
    return MFE_OK;
}

int tools_cmdif_init(mflash* mfl)
{
    /* Clear  semaphore when asked to by flint or any tool using mflash */
    if (mfl->opts[MFO_IGNORE_SEM_LOCK])
    {
        if (tools_cmdif_unlock_semaphore(mfl->mf) != ME_OK)
        {
            return MFE_CR_ERROR;
        }
    }
    return MFE_OK;
}

int seven_gen_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = MFE_OK;

    if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0)
    {
        if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD)
        {
            rc = icmd_init(mfl);
            CHECK_RC(rc);
        }
        rc = flash_init_fw_access(mfl, flash_params);
    }
    else
    {
        if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF)
        {
            /* dont allow overidding cache replacement in mellanox OS env */
            return MFE_OCR_NOT_SUPPORTED;
        }
        rc = seventh_gen_init_direct_access(mfl, flash_params);
    }
    return rc;
}

int six_gen_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;
    u_int8_t needs_cache_replacement = 0;

    rc = check_cache_replacement_guard(mfl, &needs_cache_replacement);
    CHECK_RC(rc);

    if (needs_cache_replacement)
    {
        if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD)
        {
            rc = icmd_init(mfl);
            CHECK_RC(rc);
        }
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        rc = sixth_gen_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int fifth_gen_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;
    u_int8_t needs_cache_replacement = 0;

    if (mfl->mf->gb_info.is_gb_mngr)
    {
        /* need to update GW offsets before calling to the check_cache_replacement_guard */
        flash_update_amos_gearbox_gw(mfl);
    }
    else if (mfl->mf->gb_info.is_gearbox)
    {
        return MFE_OCR_NOT_SUPPORTED; /* Accessing flash GW of GB that's not manager is not possible */
    }
    rc = check_cache_replacement_guard(mfl, &needs_cache_replacement);
    CHECK_RC(rc);

    if (needs_cache_replacement)
    {
        if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD)
        {
            rc = icmd_init(mfl);
            CHECK_RC(rc);
        }
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        rc = fifth_gen_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int cntx_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc = 0;

    if ((mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_TOOLS_CMDIF) && (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0) && mfl->opts[MFO_CX3_FW_ACCESS_EN])
    {
#ifdef UEFI_BUILD
        /* tools CMDIF not supported in UEFI */
        rc = ME_NOT_IMPLEMENTED;
#else
        rc = tcif_cr_mbox_supported(mfl->mf);
#endif
        /* init with direct access if not supported */
        if ((rc == ME_NOT_IMPLEMENTED) || (rc == ME_CMDIF_NOT_SUPP))
        {
            mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
            return cntx_flash_init_direct_access(mfl, flash_params);
        }
        if ((rc == ME_SEM_LOCKED) && !mfl->opts[MFO_IGNORE_SEM_LOCK])
        {
            return MFE_SEM_LOCKED;
        }
        rc = tools_cmdif_init(mfl);
        CHECK_RC(rc);
        rc = flash_init_fw_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_NO;
        rc = cntx_flash_init_direct_access(mfl, flash_params);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

/* */
/* Interface functions: */
/* */

#define CHECK_OUT_OF_RANGE(addr, len, size)   \
    {                                         \
        if (addr > size || addr + len > size) \
        {                                     \
            return MFE_OUT_OF_RANGE;          \
        }                                     \
    }

int is_spc5_flash_resize_needed(mflash* mfl)
{
    if (mfl->dm_dev_id == DeviceSpectrum5 && mfl->attr.vendor == FV_IS25LPXXX)
    {
        return true;
    }
    return false;
}

int mf_read(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data, bool verbose)
{
    u_int32_t size = mfl->attr.size;

    if (((mfl->dm_dev_id == DeviceConnectX4LX) || (mfl->dm_dev_id == DeviceConnectX5)) && (mfl->attr.vendor == FV_GD25QXXX))
    {
        size = 1 << FD_128; /* 16MB */
    }
    else if (is_spc5_flash_resize_needed(mfl))
    {
        size = 1 << FD_256; // 32MB
    }
    /* printf("size = %#x, addr = %#x, len = %d\n", size, addr, len); */
    CHECK_OUT_OF_RANGE(addr, len, size);
    /* printf("-D- mf_read:  addr: %#x, len: %d\n", addr, len); */
    return mfl->f_read(mfl, addr, len, data, verbose);
}

int mf_write(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data)
{
    u_int32_t size = mfl->attr.size;

    if (((mfl->dm_dev_id == DeviceConnectX4LX) || (mfl->dm_dev_id == DeviceConnectX5)) && (mfl->attr.vendor == FV_GD25QXXX))
    {
        size = 1 << FD_128; /* 16MB */
    }
    else if (is_spc5_flash_resize_needed(mfl))
    {
        size = 1 << FD_256; // 32MB
    }
    CHECK_OUT_OF_RANGE(addr, len, size);
    /* Locking semaphore for the entire existence of the mflash obj for write and erase only. */
    int rc = mfl_com_lock(mfl);

    CHECK_RC(rc);
    mfl->writer_lock = 1;
    return mfl->f_write(mfl, addr, len, data);
}
void mf_set_cpu_utilization(mflash* mfl, int cpuPercent)
{
    mfl->cputUtilizationApplied = 1;
    mfl->cpuPercent = cpuPercent;
}

static int erase_com(mflash* mfl, u_int32_t addr, unsigned int sector_size, int erase_cmd)
{
    int rc = 0;
    u_int32_t backup_sector_size = 0;
    int backup_erase_command = 0;

    if (addr >= mfl->attr.size)
    {
        return MFE_OUT_OF_RANGE;
    }
    /* Locking semaphore for the entire existence of the mflash obj for write and erase only. */
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

int mf_erase(mflash* mfl, u_int32_t addr)
{
    return erase_com(mfl, addr, mfl->attr.sector_size, mfl->attr.erase_command);
}

int mf_erase_64k_sector(mflash* mfl, u_int32_t addr)
{
    if (!mfl->attr.support_sub_and_sector)
    {
        return MFE_UNSUPPORTED_ERASE_OPERATION;
    }
    return erase_com(mfl, addr, FSS_64KB, mfl->attr.access_commands.sfc_sector_erase);
}

int mf_erase_4k_sector(mflash* mfl, u_int32_t addr)
{
    if (!mfl->attr.support_sub_and_sector)
    {
        return MFE_UNSUPPORTED_ERASE_OPERATION;
    }
    return erase_com(mfl, addr, FSS_4KB, mfl->attr.access_commands.sfc_subsector_erase);
}

int mf_open_ignore_lock(mflash* mfl)
{
    mfl->opts[MFO_IGNORE_SEM_LOCK] = 1;
    return mf_open_fw(mfl, (flash_params_t*)NULL, -1);
}

#define CR_LOCK_HW_ID 0xbad0cafe

#ifndef MST_UL
#define IS_PCI_DEV(access_type) (access_type == MST_PCICONF || access_type == MST_PCI)
#else
#define IS_PCI_DEV(access_type) (access_type == MTCR_ACCESS_CONFIG || access_type == MTCR_ACCESS_MEMORY)
#endif

BinIdT get_bin_id(mflash* mfl, u_int32_t hw_dev_id)
{
    u_int32_t dword = 0;

    if (hw_dev_id == CX5_HW_ID)
    {
        if (mread4(mfl->mf, CX5_EFUSE_ADDR, &dword) == 4)
        {
            u_int8_t bin_speed = EXTRACT(dword, 30, 2);
            if (bin_speed == 0)
            {
                return CX5_LOW_BIN;
            }
            else if (bin_speed == 1)
            {
                return CX5_HIGH_BIN;
            }
        }
    }
    return UNKNOWN_BIN;
}

int get_dev_info(mflash* mfl)
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

    if (status != MFE_OK)
    {
        return status;
    }

    mfl->attr.bin_id = UNKNOWN_BIN;
    /* get hw id */
    /* Special case for MLNX OS getting dev_id using REG MGIR */
    if (dev_flags & MDEVS_MLNX_OS)
    {
#ifndef UEFI_BUILD
        reg_access_status_t rc;
        struct reg_access_hca_mgir_ext mgir;
        memset(&mgir, 0, sizeof(mgir));
        rc = reg_access_mgir(mfl->mf, REG_ACCESS_METHOD_GET, &mgir);
        /* printf("-D- RC[%s] -- REVID: %d -- DEVID: %d hw_dev_id: %d\n", m_err2str(rc), mgir.HWInfo.REVID, */
        /* mgir.HWInfo.DEVID, mgir.HWInfo.hw_dev_id); */
        if (rc)
        {
            dev_id = DeviceSwitchIB_HwId;
            mfl->attr.rev_id = 0;
            mfl->attr.hw_dev_id = DeviceSwitchIB_HwId;
        }
        else
        {
            dev_id = mgir.hw_info.hw_dev_id;
            if (dev_id == 0)
            {
                dev_id = DeviceSwitchIB_HwId;
                mfl->attr.hw_dev_id = DeviceSwitchIB_HwId;
                mfl->attr.rev_id = mgir.hw_info.device_hw_revision & 0xf;
            }
            else
            {
                mfl->attr.hw_dev_id = dev_id;
                mfl->attr.rev_id = 0; /* WA: MGIR should have also hw_rev_id and then we can use it. */
            }
        }
#else
        /* no MLNX_OS in UEFI, no mgir register in UEFI package */
        /* we should never reach here */
        return MFE_UNKOWN_ACCESS_TYPE;
#endif
    }
    else
    {
        MREAD4(HW_DEV_ID, &dev_id);
        if (dev_id == CR_LOCK_HW_ID)
        {
            return MFE_LOCKED_CRSPACE;
        }
        mfl->attr.rev_id = (dev_id & 0xff0000) >> 16;
        mfl->attr.hw_dev_id = dev_id & 0xffff;
        mfl->attr.bin_id = get_bin_id(mfl, mfl->attr.hw_dev_id);

        if (icmdif_supported)
        {
            int mode = 0;
            if (!mf_get_secure_host(mfl, &mode) && mode)
            {
                return MFE_LOCKED_CRSPACE;
            }
        }
    }

    if (dev_flags & MDEVS_MLNX_OS)
    {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_MLNXOS_CMDIF;
    }
    else if (dev_flags & MDEVS_IB)
    {
        mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_INBAND;
    }
    else
    { /* not mlnxOS or IB device - check HW ID to determine Access type */
        if (icmdif_supported)
        {
            if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0)
            {
                mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_ICMD;
            }
        }
        else if (HAS_TOOLS_CMDIF(mfl->attr.hw_dev_id) && (IS_PCI_DEV(access_type)))
        {
            if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0)
            {
                mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] = ATBM_TOOLS_CMDIF;
            }
        }
    }
    return MFE_OK;
}

void set_gpio_toggle_conf_cx6(gpio_toggle_conf_cx6* conf)
{
    conf->lock_addr = 0xf1004;
    conf->functional_enable0_addr = 0xfc028;
    conf->functional_enable1_addr = 0xfc024;
    conf->mode1_set_addr = 0xfc04c;
    conf->mode0_set_addr = 0xfc054;
    conf->dataset_addr = 0xfc014;
}

void set_gpio_toggle_conf_bf2(gpio_toggle_conf_cx6* conf)
{
    conf->lock_addr = 0xf1084;
    conf->functional_enable0_addr = 0xfa028;
    conf->functional_enable1_addr = 0xfa024;
    conf->mode1_set_addr = 0xfa04c;
    conf->mode0_set_addr = 0xfa054;
    conf->dataset_addr = 0xfa014;
}

void set_gpio_toggle_conf_cx7(gpio_toggle_conf_cx7* conf)
{
    conf->select_synced_data_out_addr = 0xf1078;
    conf->fw_control_set_addr = 0xf1100;
    conf->hw_data_in_addr = 0xf1078;
    conf->fw_output_enable_set_addr = 0xf1104;
    conf->fw_data_out_set_addr = 0xf1108;
}

bool toggle_flash_io3_gpio_cx6(mfile* mf, gpio_toggle_conf_cx6 conf)
{
    FLASH_DPRINTF(("toggle_flash_io3_gpio_cx6\n"));
    /* Enable lock */
    if (mwrite4(mf, conf.lock_addr, 0xd42f) != 4)
    {
        printf("-E- failed to enable GPIO lock\n");
        return MFE_CR_ERROR;
    }

    /** Make sure GPIO 29 is controlled by FW (for our usage) instead of HW */
    /* Enable functional_enable0 */
    u_int32_t functional_enable0 = 0;

    if (mread4(mf, conf.functional_enable0_addr, &functional_enable0) != 4)
    {
        printf("-E- failed to read functional_enable0\n");
        return MFE_CR_ERROR;
    }
    functional_enable0 = functional_enable0 & 0xdfffffff;
    if (mwrite4(mf, conf.functional_enable0_addr, functional_enable0) != 4)
    {
        printf("-E- failed to enable GPIO functional_enable0\n");
        return MFE_CR_ERROR;
    }
    /* Enable functional_enable1 */
    u_int32_t functional_enable1 = 0;

    if (mread4(mf, conf.functional_enable1_addr, &functional_enable1) != 4)
    {
        printf("-E- failed to read functional_enable1\n");
        return MFE_CR_ERROR;
    }
    functional_enable1 = functional_enable1 & 0xdfffffff;
    if (mwrite4(mf, conf.functional_enable1_addr, functional_enable1) != 4)
    {
        printf("-E- failed to enable GPIO functional_enable1\n");
        return MFE_CR_ERROR;
    }

    /* Write to mode1_set */
    u_int32_t mode1_set = 0;

    if (mread4(mf, conf.mode1_set_addr, &mode1_set) != 4)
    {
        printf("-E- failed to read mode1_set\n");
        return MFE_CR_ERROR;
    }
    mode1_set = mode1_set | 0x20000000;
    if (mwrite4(mf, conf.mode1_set_addr, mode1_set) != 4)
    {
        printf("-E- failed to write to mode1_set\n");
        return MFE_CR_ERROR;
    }

    /** Write to GPIO 29 */
    /* Write to mode0_set */
    u_int32_t mode0_set = 0;

    if (mread4(mf, conf.mode0_set_addr, &mode0_set) != 4)
    {
        printf("-E- failed to read mode0_set\n");
        return MFE_CR_ERROR;
    }
    mode0_set = mode0_set | 0x20000000;
    if (mwrite4(mf, conf.mode0_set_addr, mode0_set) != 4)
    {
        printf("-E- failed to write to mode0_set\n");
        return MFE_CR_ERROR;
    }

    /* Write to dataset */
    if (mwrite4(mf, conf.dataset_addr, 0x20000000) != 4)
    {
        printf("-E- failed to write to dataset\n");
        return MFE_CR_ERROR;
    }

    return true;
}

bool toggle_flash_io3_gpio_cx7(mfile* mf, gpio_toggle_conf_cx7 conf)
{
    FLASH_DPRINTF(("toggle_flash_io3_gpio_cx7\n"));
    /* write 0x0 to select_synced_data_out.16:1 */
    u_int32_t select_synced_data_out = 0;

    if (mread4(mf, conf.select_synced_data_out_addr, &select_synced_data_out) != 4)
    {
        printf("-E- failed to read select_synced_data_out\n");
        return MFE_CR_ERROR;
    }
    select_synced_data_out = select_synced_data_out & 0xfffeffff;
    if (mwrite4(mf, conf.select_synced_data_out_addr, select_synced_data_out) != 4)
    {
        printf("-E- failed to write 0x0 to select_synced_data_out.16:1\n");
        return MFE_CR_ERROR;
    }

    /* write 0x3 to fw_control_set.28:2 */
    u_int32_t fw_control_set = 0;

    if (mread4(mf, conf.fw_control_set_addr, &fw_control_set) != 4)
    {
        printf("-E- failed to read fw_control_set\n");
        return MFE_CR_ERROR;
    }
    fw_control_set = fw_control_set | 0x30000000;
    if (mwrite4(mf, conf.fw_control_set_addr, fw_control_set) != 4)
    {
        printf("-E- failed to write 0x3 to fw_control_set.28:2\n");
        return MFE_CR_ERROR;
    }

    /* write 0x3 to hw_data_in.4:2 */
    u_int32_t hw_data_in = 0;

    if (mread4(mf, conf.hw_data_in_addr, &hw_data_in) != 4)
    {
        printf("-E- failed to read hw_data_in\n");
        return MFE_CR_ERROR;
    }
    hw_data_in = hw_data_in | 0x00000030;
    if (mwrite4(mf, conf.hw_data_in_addr, hw_data_in) != 4)
    {
        printf("-E- failed to write 0x3 to hw_data_in.4:2\n");
        return MFE_CR_ERROR;
    }

    /* write 0x3 to fw_output_enable_set.28:2 */
    u_int32_t fw_output_enable_set = 0;

    if (mread4(mf, conf.fw_output_enable_set_addr, &fw_output_enable_set) != 4)
    {
        printf("-E- failed to read fw_output_enable_set\n");
        return MFE_CR_ERROR;
    }
    fw_output_enable_set = fw_output_enable_set | 0x30000000;
    if (mwrite4(mf, conf.fw_output_enable_set_addr, fw_output_enable_set) != 4)
    {
        printf("-E- failed to write 0x3 to fw_output_enable_set.28:2\n");
        return MFE_CR_ERROR;
    }

    /* write 0x3 to fw_data_out_set.28:2 */
    u_int32_t fw_data_out_set = 0;

    if (mread4(mf, conf.fw_data_out_set_addr, &fw_data_out_set) != 4)
    {
        printf("-E- failed to read fw_data_out_set\n");
        return MFE_CR_ERROR;
    }
    fw_data_out_set = fw_data_out_set | 0x30000000;
    if (mwrite4(mf, conf.fw_data_out_set_addr, fw_data_out_set) != 4)
    {
        printf("-E- failed to write 0x3 to fw_data_out_set.28:2\n");
        return MFE_CR_ERROR;
    }

    return true;
}

bool force_flash_out_of_hold_state(mflash* mfl)
{
    bool res = true;

    if ((getenv("FORCE_GPIO_TOGGLE") != NULL) || dm_is_livefish_mode(mfl->mf))
    {
        switch (mfl->dm_dev_id)
        {
            case DeviceConnectX6:
            case DeviceConnectX6DX:
            {
                gpio_toggle_conf_cx6 gpio_toggle_conf = {0};
                set_gpio_toggle_conf_cx6(&gpio_toggle_conf);
                res = toggle_flash_io3_gpio_cx6(mfl->mf, gpio_toggle_conf);
                break;
            }

            case DeviceBlueField2:
            {
                gpio_toggle_conf_cx6 gpio_toggle_conf = {0};
                set_gpio_toggle_conf_bf2(&gpio_toggle_conf);
                res = toggle_flash_io3_gpio_cx6(mfl->mf, gpio_toggle_conf);
                break;
            }

            case DeviceConnectX7:
            case DeviceBlueField3:
            {
                gpio_toggle_conf_cx7 gpio_toggle_conf = {0};
                set_gpio_toggle_conf_cx7(&gpio_toggle_conf);
                res = toggle_flash_io3_gpio_cx7(mfl->mf, gpio_toggle_conf);
                break;
            }

            default:
                break;
        }
    }

    return res;
}

/* Caller must zero the mflash struct before calling this func. */
int mf_open_fw(mflash* mfl, flash_params_t* flash_params, int num_of_banks)
{
    int rc = 0;

    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    rc = set_bank_int(mfl, -1);
    CHECK_RC(rc);
    mfl->gw_data_field_addr = HCR_FLASH_DATA;
    mfl->gw_cmd_register_addr = HCR_FLASH_CMD;
    mfl->gw_addr_field_addr = HCR_FLASH_ADDR;
    mfl->cache_repacement_en_addr = HCR_CACHE_REPLACEMNT_EN_ADDR;
    mfl->gcm_en_addr = 0xffffffff; /* Relevant to devices with new flash GW only */
    mfl->cache_rep_offset_field_addr = HCR_FLASH_CACHE_REPLACEMENT_OFFSET;
    mfl->cache_rep_cmd_field_addr = HCR_FLASH_CACHE_REPLACEMENT_CMD;
    if (mfl->access_type == MFAT_MFILE)
    {
        rc = get_dev_info(mfl);
        CHECK_RC(rc);

#ifndef UEFI_BUILD
        trm_sts trm_rc;
        trm_rc = trm_create(&(mfl->trm), mfl->mf);
        if (trm_rc)
        {
            return trm2mfe_err(trm_rc);
        }
#endif

        mfl->opts[MFO_NUM_OF_BANKS] = spi_get_num_of_flashes(num_of_banks);
        rc = spi_update_num_of_banks(mfl, num_of_banks);
        CHECK_RC(rc);

        /** Before initializing flash methods (which including accessing the flash) */
        /** we need to toggle GPIO to get flash out of HOLD state (relevant to second source flash Winbond W25Q256JV) */
        rc = force_flash_out_of_hold_state(mfl);

        MfError status;
        int icmdif_supported = is_icmdif_supported(mfl, &status);
        if (status != MFE_OK)
        {
            return status;
        }
        if (IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id))
        {
            rc = cntx_flash_init(mfl, flash_params);
        }
        else if (icmdif_supported)
        {
            FlashGen flash_gen = get_flash_gen(mfl);
            if (flash_gen == LEGACY_FLASH)
            {
                rc = fifth_gen_flash_init(mfl, flash_params);
            }
            else if (flash_gen == SIX_GEN_FLASH)
            {
                rc = six_gen_flash_init(mfl, flash_params);
            }
            else if (flash_gen == SEVEN_GEN_FLASH)
            {
                rc = seven_gen_flash_init(mfl, flash_params);
            }
            else
            {
                rc = MFE_ERROR;
            }
        }
        else if (mfl->attr.hw_dev_id == 0xffff)
        {
            rc = MFE_HW_DEVID_ERROR;
        }
        else
        {
            rc = MFE_UNSUPPORTED_DEVICE;
        }
        CHECK_RC(rc);
    }
    else if (mfl->access_type == MFAT_UEFI)
    {
        mfl->opts[MFO_NUM_OF_BANKS] = 1; /* We have only one flash in ConnectIB and ConnectX-3 - Need to specify it better! */
        rc = uefi_flash_init(mfl, flash_params);
        CHECK_RC(rc);
    }
    else
    {
        return MFE_UNKOWN_ACCESS_TYPE;
    }
    mfl->f_set_bank(mfl, 0);
    return MFE_OK;
}

int mf_opend_int(mflash** pmfl, void* access_dev, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard, u_int8_t access_type, void* dev_extra, int cx3_fw_access)
{
    int rc = 0;

    *pmfl = (mflash*)malloc(sizeof(mflash));
    if (!*pmfl)
    {
        return MFE_NOMEM;
    }

    memset(*pmfl, 0, sizeof(mflash));

    (*pmfl)->opts[MFO_IGNORE_CASHE_REP_GUARD] = ignore_cache_rep_guard;
    (*pmfl)->opts[MFO_CX3_FW_ACCESS_EN] = cx3_fw_access;
    (*pmfl)->access_type = access_type;
    if (access_type == MFAT_MFILE)
    {
        (*pmfl)->mf = (mfile*)access_dev;
        u_int32_t dev_id;
        u_int32_t chip_rev;
        rc = dm_get_device_id((*pmfl)->mf, &((*pmfl)->dm_dev_id), &dev_id, &chip_rev);
        CHECK_RC(rc);
    }
    else if (access_type == MFAT_UEFI)
    {
        /* open mfile as uefi */
        if (!((*pmfl)->mf = mopen_fw_ctx(access_dev, ((uefi_dev_extra_t*)dev_extra)->fw_cmd_func, ((uefi_dev_extra_t*)dev_extra)->dma_func, &((uefi_dev_extra_t*)dev_extra)->dev_info)))
        {
            return MFE_NOMEM;
        }
        /* fill some device information */
        (*pmfl)->attr.hw_dev_id = ((uefi_dev_extra_t*)dev_extra)->dev_info.hw_dev_id;
        (*pmfl)->attr.rev_id = ((uefi_dev_extra_t*)dev_extra)->dev_info.rev_id;
        rc = dm_get_device_id_offline((*pmfl)->attr.hw_dev_id, (*pmfl)->attr.rev_id, &((*pmfl)->dm_dev_id));
        CHECK_RC(rc);
    }
    rc = mf_open_fw(*pmfl, flash_params, num_of_banks);
    return rc;
}

int mf_open_uefi(mflash** pmfl, uefi_Dev_t* uefi_dev, uefi_dev_extra_t* uefi_dev_extra)
{
    return mf_opend_int(pmfl, (void*)uefi_dev, 4, (flash_params_t*)NULL, 0, MFAT_UEFI, (void*)uefi_dev_extra, 0);
}

int mf_open_int(mflash** pmfl, const char* dev, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard, int cx3_fw_access)
{
    mfile* mf;
    int rc = MFE_OK;

    if (!dev)
    {
        return MFE_BAD_PARAMS;
    }

    mf = mopen(dev);

    if (!mf)
    {
        return MFE_CR_ERROR;
    }

    if (ignore_cache_rep_guard)
    { /* relevant only if working with -ocr flag */
        if (mf->gb_info.is_gb_mngr == 1)
        {
            if (mf_check_spi_channel(mf) != 1)
            {
                mclose(mf);
                printf("-E- Can not continue - SPI channel is not OK.\n");
                return MFE_CR_ERROR;
            }
        }
    }
    rc = mf_opend_int(pmfl, (struct mfile_t*)mf, num_of_banks, flash_params, ignore_cache_rep_guard, MFAT_MFILE, NULL, cx3_fw_access);
    if ((*pmfl))
    {
        (*pmfl)->opts[MFO_CLOSE_MF_ON_EXIT] = 1;
    }
    else
    {
        mclose(mf);
    }
    return rc;
}

int mf_open_adv(mflash** pmfl, const char* dev, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard, int cx3_fw_access)
{
    return mf_open_int(pmfl, dev, num_of_banks, flash_params, ignore_cache_rep_guard, cx3_fw_access);
}

int mf_open(mflash** pmfl, const char* dev, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard)
{
    return mf_open_int(pmfl, dev, num_of_banks, flash_params, ignore_cache_rep_guard, 0);
}

void mf_close(mflash* mfl)
{
    if (!mfl)
    {
        return;
    }

    if (mfl->f_reset)
    {
        mfl->f_reset(mfl);
    }

    if (mfl->f_set_bank)
    {
        (void)set_bank(mfl, 0);
    }
    mfl->unlock_flash_prog_allowed = 1;
    /* we release if we have writer_lock or not doesnt matter on close ... */
    release_semaphore(mfl, 1);

    if (mfl->mf && (mfl)->opts[MFO_CLOSE_MF_ON_EXIT])
    {
        mclose(mfl->mf);
    }
#ifndef UEFI_BUILD
    if (mfl->trm)
    {
        trm_destroy(mfl->trm);
        mfl->trm = (trm_ctx)NULL;
    }
#endif
    free(mfl);
    return;
}

int mf_get_attr(mflash* mfl, flash_attr* attr)
{
    *attr = mfl->attr;
    return MFE_OK;
}

const char* mf_err2str(int err_code)
{
    switch (err_code)
    {
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
            return "ICMD interface is not supported for this device";

        case MFE_HW_ACCESS_NOT_SUPP:
            return "Secure host mode is not enabled in this FW.";

        case MFE_MAD_SEND_ERR:
            return "Failed to send MAD";

        case MFE_ICMD_BAD_PARAM:
            return "ICMD bad parameter given";

        case MFE_ICMD_INVALID_OPCODE:
            return "Invalid ICMD opcode used";

        case MFE_ICMD_INVALID_CMD:
            return "Invalid ICMD command used";

        case MFE_ICMD_OPERATIONAL_ERROR:
            return "ICMD operational error";

        case MFE_DATA_IS_OTP:
            return "The data you are trying to write is OTP and have already been programmed.";

        case MFE_REG_ACCESS_BAD_METHOD:
            return "Bad Reg Access method";

        case MFE_REG_ACCESS_NOT_SUPPORTED:
            return "Register access is not supported by the device";

        case MFE_REG_ACCESS_DEV_BUSY:
            return "Register access failed, device is busy";

        case MFE_REG_ACCESS_VER_NOT_SUPP:
            return "Register access Version not supported";

        case MFE_REG_ACCESS_UNKNOWN_TLV:
            return "Register access Unknown TLV";

        case MFE_REG_ACCESS_REG_NOT_SUPP:
            return "Register not supported";

        case MFE_REG_ACCESS_CLASS_NOT_SUPP:
            return "Register access class not supported";

        case MFE_REG_ACCESS_METHOD_NOT_SUPP:
            return "Register access method not supported";

        case MFE_REG_ACCESS_BAD_PARAM:
            return "Register access bad parameter";

        case MFE_REG_ACCESS_RES_NOT_AVLBL:
            return "Register access Resource unavailable";

        case MFE_REG_ACCESS_MSG_RECPT_ACK:
            return "Message receipt ack";

        case MFE_REG_ACCESS_UNKNOWN_ERR:
            return "Unknown register error";

        case MFE_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
            return "Register is too large";

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
    switch (rc)
    {
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

int mf_set_opt(mflash* mfl, MfOpt opt, int val)
{
    if (((int)opt < 0) || (opt >= MFO_LAST))
    {
        return MFE_BAD_PARAMS;
    }
    mfl->opts[opt] = val;
    return MFE_OK;
}

int mf_get_opt(mflash* mfl, MfOpt opt, int* val)
{
    if (((int)opt < 0) || (opt >= MFO_LAST))
    {
        return MFE_BAD_PARAMS;
    }
    *val = mfl->opts[opt];
    return MFE_OK;
}

int mf_cr_read(mflash* mfl, u_int32_t cr_addr, u_int32_t* data)
{
    if (mread4(mfl->mf, cr_addr, data) != 4)
    {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

int mf_cr_write(mflash* mfl, u_int32_t cr_addr, u_int32_t data)
{
    if (mwrite4(mfl->mf, cr_addr, data) != 4)
    {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

int mf_set_reset_flash_on_warm_reboot(mflash* mfl)
{
    int rc;
    u_int32_t set_reset_bit_dword_addr = 0;
    int set_reset_bit_offset;
    u_int32_t set_reset_bit_dword = 0;

    switch (mfl->dm_dev_id)
    {
        case DeviceConnectX3:
        case DeviceConnectX3Pro:
        case DeviceConnectIB:
        case DeviceSwitchIB:
        case DeviceSwitchIB2:
        case DeviceQuantum:
        case DeviceQuantum2:
        case DeviceQuantum3:
        case DeviceNVLink6_Switch:
        case DeviceConnectX7:
        case DeviceBlueField3:
        case DeviceConnectX8:
        case DeviceConnectX9:
        case DeviceConnectX8_Pure_PCIe_Switch:
        case DeviceConnectX9_Pure_PCIe_Switch:
        case DeviceBlueField4:
        case DeviceSpectrum4:
        case DeviceSpectrum5:
        case DeviceSpectrum6:
        case DeviceAbirGearBox:
            return MFE_OK;

        case DeviceSpectrum:
        case DeviceConnectX4:
        case DeviceConnectX4LX:
        case DeviceConnectX5:
        case DeviceBlueField:
            set_reset_bit_dword_addr = 0xf0204;
            set_reset_bit_offset = 1;
            break;

        case DeviceConnectX6:
        case DeviceConnectX6DX:
        case DeviceConnectX6LX:
        case DeviceBlueField2:
        case DeviceSpectrum2:
        case DeviceSpectrum3:
        case DeviceGearBox:
        case DeviceGearBoxManager:
            set_reset_bit_dword_addr = 0xf0c28;
            set_reset_bit_offset = 2;
            break;

        default:
            return MFE_UNSUPPORTED_DEVICE;
    }
    FLASH_DPRINTF(("mflash::mf_set_reset_flash_on_warm_reboot setting power_boot_partial_reset at addr 0x%x.%d\n", set_reset_bit_dword_addr, set_reset_bit_offset));
    rc = mf_cr_read(mfl, set_reset_bit_dword_addr, &set_reset_bit_dword);
    CHECK_RC(rc);
    set_reset_bit_dword = MERGE(set_reset_bit_dword, 1, set_reset_bit_offset, 1);
    return mf_cr_write(mfl, set_reset_bit_dword_addr, set_reset_bit_dword);
}

int mf_update_boot_addr(mflash* mfl, u_int32_t boot_addr)
{
    int rc;
    u_int32_t boot_cr_space_address;
    int offset_in_address;

    switch (mfl->dm_dev_id)
    {
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
        case DeviceGearBox:
        case DeviceGearBoxManager:
            boot_cr_space_address = 0xf0080;
            offset_in_address = 0;
            break;

        case DeviceAbirGearBox:
            boot_cr_space_address = 0xf1400;
            offset_in_address = 0;
            break;

        case DeviceQuantum2:
            boot_cr_space_address = 0xf1000;
            offset_in_address = 0;
            break;

        case DeviceConnectX7:
        case DeviceBlueField3:
            boot_cr_space_address = 0xf2000;
            offset_in_address = 0;
            break;

        case DeviceQuantum3:
        case DeviceNVLink6_Switch:
            boot_cr_space_address = 0xfc000;
            offset_in_address = 0;
            break;

        case DeviceConnectX8:
        case DeviceConnectX8_Pure_PCIe_Switch:
        case DeviceConnectX9:
        case DeviceConnectX9_Pure_PCIe_Switch:
        case DeviceBlueField4:
            boot_cr_space_address = 0xf8008;
            offset_in_address = 0;
            break;

        case DeviceSpectrum4:
        case DeviceSpectrum5:
        case DeviceSpectrum6:
        case DeviceSpectrum6IB:
            boot_cr_space_address = 0xf1800;
            offset_in_address = 0;
            break;

        default:
            return MFE_UNSUPPORTED_DEVICE;
    }

    if ((mfl->access_type != MFAT_UEFI) && (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] != ATBM_MLNXOS_CMDIF))
    {
        /* the boot addr will be updated directly via cr-space */
        FLASH_DPRINTF(("mflash::mf_update_boot_addr setting boot_start_address at addr 0x%x to 0x%x\n", boot_cr_space_address, boot_addr << offset_in_address));
        rc = mf_cr_write(mfl, boot_cr_space_address, boot_addr << offset_in_address);
        CHECK_RC(rc);
        return mf_set_reset_flash_on_warm_reboot(mfl);
    }
    else
    {
        /* the boot addr will be updated via reg */
        return mf_update_boot_addr_by_type(mfl, boot_addr);
    }
}

int is_macronix_special_case_for_driver_strength(uint8_t vendor, uint16_t type, uint8_t log2_bank_size)
{
    if (vendor == FV_MX25K16XXX && type == FMT_SST_25 && (((1 << FD_256) & (1 << log2_bank_size)) != 0))
    {
        return 1;
    }
    return 0;
}

int is_macronix_special_case_for_dummy_cycles(mflash* mfl)
{
    if (mfl->attr.vendor == FV_MX25K16XXX && mfl->attr.type == FMT_SST_25 && (((1 << FD_512) & (1 << mfl->attr.log2_bank_size)) != 0))
    {
        return 1;
    }
    return 0;
}

int is_ISSI_is25wj032f(mflash* mfl)
{
    if (mfl->attr.vendor == FV_IS25LPXXX && mfl->attr.type == FMT_IS25WPXXX && mfl->attr.log2_bank_size == FD_32)
    {
        return 1;
    }
    return 0;
}

int is_ISSI_is25wj032f_by_jedec_id(uint32_t jedec_id)
{
    // Construct JEDEC ID from constants in the format: density | type | vendor (24-bit)
    // FD_32=0x16, FMT_IS25WPXXX=0x70, FV_IS25LPXXX=0x9d
    const uint32_t expected_jedec_id = (FD_32 << 16) |        // Density in upper byte
                                       (FMT_IS25WPXXX << 8) | // Type in middle byte
                                       (FV_IS25LPXXX);        // Vendor in lower byte

    if (jedec_id == expected_jedec_id) // This will equal 0x16709d
    {
        return 1;
    }
    return 0;
}

int is_macronix_mx25u51245g(mflash* mfl)
{
    if (mfl->attr.vendor == FV_MX25K16XXX && mfl->attr.type == FMT_SST_25 && (((1 << FD_512) & (1 << mfl->attr.log2_bank_size)) != 0))
    {
        if (mfl->attr.series_code == MACRONIX_MX25U51245G)
        {
            return 1;
        }
    }
    return 0;
}

int is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mflash* mfl)
{
    return is_macronix_mx25u51294g_mx25u51294gxdi08(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size, mfl->attr.series_code);
}

int is_macronix_mx25u51294g_mx25u51294gxdi08(uint8_t vendor, uint16_t type, uint32_t log2_bank_size, MacronixSeriesCode series_code)
{
    if (vendor == FV_MX25K16XXX && type == FMT_SST_25 && (((1 << FD_512) & (1 << log2_bank_size)) != 0))
    {
        if (series_code == MACRONIX_MX25U51294G_MX25U51294GXDI08)
        {
            return 1;
        }
    }
    return 0;
}

int mf_read_modify_status_winbond(mflash* mfl, u_int8_t bank_num, u_int8_t is_first_status_reg, u_int8_t param, u_int8_t offset, u_int8_t size)
{
    u_int8_t status1 = 0, status2 = 0, use_rdsr2 = 0;
    u_int32_t status = 0;
    u_int8_t bytes_to_write = 1;
    int rc = 0;

    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    if (((mfl->attr.vendor == FV_WINBOND) && (mfl->attr.type == FMT_WINBOND)) || ((mfl->attr.vendor == FV_S25FLXXXX) && ((mfl->attr.type == FMT_S25FL116K) || (mfl->attr.type == FMT_S25FLXXXL))) ||
        ((mfl->attr.vendor == FV_MX25K16XXX) && (mfl->attr.type == FMT_MX25K16XXX)) || (is_macronix_special_case_for_driver_strength(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size)) ||
        (is_macronix_mx25u51245g(mfl)))
    {
        /*
         * if we have 2 status registers, winbond are allowing us to write both of them
         * in a single command WRSR  status_reg1 located in MSB, status_reg2 after status_reg1
         */
        use_rdsr2 = 1;
    }

    /* Read register status */
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status1);
    CHECK_RC(rc);
    if (use_rdsr2)
    {
        if (mfl->attr.vendor == FV_MX25K16XXX)
        {
            rc = mfl->f_spi_status(mfl, SFC_RDCR, &status2);
            CHECK_RC(rc);
        }
        else
        {
            rc = mfl->f_spi_status(mfl, SFC_RDSR2, &status2);
            CHECK_RC(rc);
        }
        status = MERGE(0, status2, 0, 8);
        bytes_to_write = 2;
    }
    /* Prepare the read status word */
    status = MERGE(status, status1, 8, 8);
    /* Modify the status according to the function arguments */
    status = MERGE(status, param, offset + is_first_status_reg * 8, size);
    /* fix status register in case we dont need to write status register 2 */
    if (bytes_to_write == 1)
    {
        status = status >> 8;
    }
    /* Write register status */
    if (mfl->attr.vendor == FV_GD25QXXX)
    {
        rc = mfl->f_spi_write_status_reg(mfl, status, SFC_WRSR_GIGA, bytes_to_write);
    }
    else
    {
        rc = mfl->f_spi_write_status_reg(mfl, status, SFC_WRSR, bytes_to_write);
    }

    CHECK_RC(rc);
    return MFE_OK;
}

u_int32_t mf_change_status_endianness(mflash* mfl, u_int32_t status, u_int8_t bytes_num)
{
    if (mfl->attr.vendor == FV_ST)
    {
        if (bytes_num == 2)
        {
            status = ___my_swab16(status);
        }
    }
    return status;
}

/* read/write_cmd - command value for reading/writing from/to status register 1/2/3 */
/* val - new value to be written */
/* offset - destination bit offset */
/* size - bit length */
/* bytes_num - status register size in bytes */
int mf_read_modify_status_new(mflash* mfl, u_int8_t bank_num, u_int8_t read_cmd, u_int8_t write_cmd, u_int8_t val, u_int8_t offset, u_int8_t size, u_int8_t bytes_num)
{
    int rc = 0;
    u_int32_t status = 0;

    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    rc = mfl->f_int_spi_get_status_data(mfl, read_cmd, &status, bytes_num);
    CHECK_RC(rc);
    status = mf_change_status_endianness(mfl, status, bytes_num);
    status = MERGE(status, val, offset, size);
    status = mf_change_status_endianness(mfl, status, bytes_num);
    rc = mfl->f_spi_write_status_reg(mfl, status, write_cmd, bytes_num);
    CHECK_RC(rc);
    return MFE_OK;
}

int mf_get_param_int(mflash* mfl, u_int8_t* param_p, u_int8_t cmd, u_int8_t offset, u_int8_t bit_size, u_int8_t bytes_num, u_int8_t enabled_val)
{
    u_int32_t status = 0, is_first = 1, bank = 0;
    int rc = 0;

    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        u_int8_t curr_val;
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        rc = mfl->f_int_spi_get_status_data(mfl, cmd, &status, bytes_num);
        CHECK_RC(rc);
        status = mf_change_status_endianness(mfl, status, bytes_num);
        curr_val = EXTRACT(status, offset, bit_size);
        if (bit_size == 1)
        {
            curr_val = (curr_val == enabled_val);
        }

        if (is_first)
        {
            *param_p = curr_val;
            is_first = 0;
        }
        else
        {
            if (*param_p != curr_val)
            {
                return MFE_MISMATCH_PARAM;
            }
        }
    }
    return MFE_OK;
}

int get_tb_for_ISSI_is25wj032f(mflash* mfl, u_int8_t* tb_p, u_int8_t* is_subsector_p)
{
    // we don't support setting subsector protection but user can still set it independenetly and therefore we need to
    // take it into account
    u_int8_t status = 0;
    int rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
    CHECK_RC(rc);
    int tb_selector = EXTRACT(status, TB_OFFSET, 2);

    switch (tb_selector)
    {
        case 0:
            *tb_p = 0;
            *is_subsector_p = 0;
            break;
        case 1:
            *tb_p = 1;
            *is_subsector_p = 0;
            break;
        case 2:
            *tb_p = 0;
            *is_subsector_p = 1;
            break;
        case 3:
            *tb_p = 1;
            *is_subsector_p = 1;
            break;
        default:
            return MFE_BAD_PARAMS;
    }

    return MFE_OK;
}

int set_tb_for_ISSI_is25wj032(mflash* mfl, u_int8_t tb, u_int8_t bank_num)
{
    // no subsector protection -> the cases for subsector protection are not supported
    int bp_msb_bits = tb ? 1 : 0;

    return mf_read_modify_status_winbond(mfl, bank_num, 1, bp_msb_bits, BP_OFFSET + BP_SIZE, 2);
}

int mf_set_dummy_cycles_direct_access(mflash* mfl, u_int8_t num_of_cycles)
{
    u_int8_t lower_bound = is_macronix_special_case_for_dummy_cycles(mfl) ? MIN_NUM_OF_CYCLES_FOR_MX25UXXX : MIN_NUM_OF_CYCLES;
    u_int8_t upper_bound = is_macronix_special_case_for_dummy_cycles(mfl) ? MAX_NUM_OF_CYCLES_FOR_MX25UXXX : MAX_NUM_OF_CYCLES;
    if (!mfl || num_of_cycles < lower_bound || num_of_cycles > upper_bound)
    {
        return MFE_BAD_PARAMS;
    }
    int bank = 0, rc = 0;

    if (!(mfl->attr.dummy_cycles_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        if (is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR4_MACRONIX_MX25UXXX, SFC_WRSR4_MACRONIX_MX25UXXX, num_of_cycles, DUMMY_CYCLES_OFFSET_MACRONIX_MX25UXXX,
                                           DUMMY_CYCLES_BIT_LEN_MACRONIX_MX25UXXX, 1);
            CHECK_RC(rc);
        }
        else if (is_macronix_mx25u51245g(mfl))
        {
            rc = mf_read_modify_status_winbond(mfl, bank, 0, num_of_cycles, DUMMY_CYCLES_OFFSET_MX25U51245G, DUMMY_CYCLES_BIT_LEN_MACRONIX_MX25UXXX);
            CHECK_RC(rc);
        }
        else
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDNVR, SFC_WRNVR, num_of_cycles, DUMMY_CYCLES_OFFSET_ST, 4, 2);
            CHECK_RC(rc);
        }
    }
    return MFE_OK;
}

int mf_get_dummy_cycles_direct_access(mflash* mfl, u_int8_t* dummy_cycles_p)
{
    if (!mfl || !dummy_cycles_p)
    {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.dummy_cycles_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    int rc = ME_OK;
    if (is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
    {
        rc = mf_get_param_int(mfl, dummy_cycles_p, SFC_RDSR4_MACRONIX_MX25UXXX, DUMMY_CYCLES_OFFSET_MACRONIX_MX25UXXX, DUMMY_CYCLES_BIT_LEN_MACRONIX_MX25UXXX, 1, 0);
    }
    else if (is_macronix_mx25u51245g(mfl))
    {
        u_int8_t status = 0;
        rc = mfl->f_spi_status(mfl, SFC_RDCR, &status);
        CHECK_RC(rc);
        *dummy_cycles_p = EXTRACT(status, DUMMY_CYCLES_OFFSET_MX25U51245G, DUMMY_CYCLES_BIT_LEN_MACRONIX_MX25UXXX);
    }
    else
    {
        rc = mf_get_param_int(mfl, dummy_cycles_p, SFC_RDNVR, DUMMY_CYCLES_OFFSET_ST, 4, 2, 0);
    }

    return rc;
}

int mf_set_driver_strength_direct_access(mflash* mfl, u_int8_t driver_strength)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.driver_strength_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    int bank = 0, rc = MFE_OK;

    for (; bank < mfl->attr.banks_num; bank++)
    {
        if (mfl->attr.vendor == FV_WINBOND)
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR3_WINBOND,        /* mflash, bank num, status-register-3 read cmd */
                                           SFC_WRSR3_WINBOND, driver_strength,  /* status-register-3 write cmd, driver-strength new val */
                                           DRIVER_STRENGTH_OFFSET_WINBOND,      /* driver-strength bit offset */
                                           DRIVER_STRENGTH_BIT_LEN_WINBOND, 1); /* driver-strength bit length, status-register byte len */
            CHECK_RC(rc);
        }
        else if (mfl->attr.vendor == FV_ST)
        {                                                                      /* micron */
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDNVR,               /* mflash, bank num, nonvolatile-configuration-register read cmd */
                                           SFC_WRNVR, driver_strength,         /* nonvolatile-configuration-register write cmd, driver-strength new val */
                                           DRIVER_STRENGTH_OFFSET_MICRON,      /* driver-strength bit offset */
                                           DRIVER_STRENGTH_BIT_LEN_MICRON, 2); /* driver-strength bit length, status-register byte len */
            CHECK_RC(rc);
        }
        else if (mfl->attr.vendor == FV_MX25K16XXX)
        {
            if (is_macronix_special_case_for_driver_strength(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size) || is_macronix_mx25u51245g(mfl))
            {
                rc = mf_read_modify_status_winbond(mfl, bank, 0, driver_strength, DRIVER_STRENGTH_OFFSET_MACRONIX_MX25UXXX, DRIVER_STRENGTH_BIT_LEN_MACRONIX);
                CHECK_RC(rc);
            }
            else
            {
                rc = mf_read_modify_status_new(mfl, bank,
                                               SFC_RDSR3_MACRONIX_MX25K16XXX, // mflash, bank num, nonvolatile-configuration-register read cmd
                                               SFC_WRSR3_MACRONIX_MX25K16XXX,
                                               driver_strength,                            // nonvolatile-configuration-register write cmd, driver-strength new val
                                               DRIVER_STRENGTH_OFFSET_MACRONIX_MX25K16XXX, // driver-strength bit offset
                                               DRIVER_STRENGTH_BIT_LEN_MACRONIX_MX25K16XXX,
                                               1); // driver-strength bit length, status-register byte len
                CHECK_RC(rc);
            }
        }
        else if (mfl->attr.vendor == FV_IS25LPXXX && // issi
            !is_ISSI_is25wj032f(mfl))                // issi for arcus2 only supports reading driver_strength, not
                                                     // setting it)
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDERP_ISSI,        /* mflash, bank num, nonvolatile-configuration-register read cmd */
                                           SFC_SERPNV_ISSI, driver_strength, /* nonvolatile-configuration-register write cmd, driver-strength new val */
                                           DRIVER_STRENGTH_OFFSET_ISSI,      /* driver-strength bit offset */
                                           DRIVER_STRENGTH_BIT_LEN_ISSI, 1); /* driver-strength bit length, status-register byte len */
            CHECK_RC(rc);
        }
        else
        {
            return MFE_NOT_IMPLEMENTED;
        }
    }
    return MFE_OK;
}

int mf_get_driver_strength_direct_access(mflash* mfl, u_int8_t* driver_strength_p)
{
    if (!mfl || !driver_strength_p)
    {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.driver_strength_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    int rc = MFE_OK;

    if (mfl->attr.vendor == FV_WINBOND)
    {
        rc = mf_get_param_int(mfl, driver_strength_p, SFC_RDSR3_WINBOND, /* mflash, output pointer, status-register-3 read cmd */
                              DRIVER_STRENGTH_OFFSET_WINBOND,            /* driver-strength bit offset */
                              DRIVER_STRENGTH_BIT_LEN_WINBOND,           /* driver-strength bit length */
                              1, 0);                                     /* status-register byte len, don't-care */
    }
    else if (mfl->attr.vendor == FV_ST)
    {                                                         /* micron */
        rc = mf_get_param_int(mfl, driver_strength_p,         /* mflash, output pointer, */
                              SFC_RDNVR,                      /* nonvolatile-configuration-register read cmd */
                              DRIVER_STRENGTH_OFFSET_MICRON,  /* driver-strength bit offset */
                              DRIVER_STRENGTH_BIT_LEN_MICRON, /* driver-strength bit length */
                              2, 0);                          /* status-register byte len, don't-care */
    }
    else if (mfl->attr.vendor == FV_MX25K16XXX) // macronix
    {
        if (is_macronix_special_case_for_driver_strength(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size) || is_macronix_mx25u51245g(mfl))
        {
            u_int8_t status = 0;
            rc = mfl->f_spi_status(mfl, SFC_RDCR, &status);
            CHECK_RC(rc);
            *driver_strength_p = EXTRACT(status, DRIVER_STRENGTH_OFFSET_MACRONIX_MX25UXXX, DRIVER_STRENGTH_BIT_LEN_MACRONIX);
        }
        else
        {
            rc = mf_get_param_int(mfl, driver_strength_p,                      // mflash, output pointer,
                                  SFC_RDSR3_MACRONIX_MX25K16XXX,               // nonvolatile-configuration-register read cmd
                                  DRIVER_STRENGTH_OFFSET_MACRONIX_MX25K16XXX,  // driver-strength bit offset
                                  DRIVER_STRENGTH_BIT_LEN_MACRONIX_MX25K16XXX, // driver-strength bit length
                                  1, 0);                                       // status-register byte len, don't-care
        }                                                                      /* status-register byte len, don't-care */
    }
    else if (mfl->attr.vendor == FV_IS25LPXXX && // issi
        !is_ISSI_is25wj032f(mfl))               // issi for arcus2 only supports reading driver_strength, not
                                                // setting it, therefore no driver strength support)
    {
        rc = mf_get_param_int(mfl, driver_strength_p,       // mflash, output pointer,
                              SFC_RDERP_ISSI,               // nonvolatile-configuration-register read cmd
                              DRIVER_STRENGTH_OFFSET_ISSI,  // driver-strength bit offset
                              DRIVER_STRENGTH_BIT_LEN_ISSI, // driver-strength bit length
                              1, 0);                        /* status-register byte len, don't-care */
    }
    else
    {
        rc = MFE_NOT_IMPLEMENTED;
    }

    return rc;
}

int mf_set_quad_en_direct_access(mflash* mfl, u_int8_t quad_en)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    int bank = 0, rc = 0;

    if (!(mfl->attr.quad_en_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        if ((mfl->attr.vendor == FV_WINBOND) && ((mfl->attr.type == FMT_WINBOND_3V) || (mfl->attr.type == FMT_WINBOND_IQ) || (mfl->attr.type == FMT_WINBOND_IM) || is_ISSI_is25wj032f(mfl)))
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR2, SFC_WRSR2, quad_en, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1, 1);
            CHECK_RC(rc);
        }
        else if ((mfl->attr.vendor == FV_WINBOND) || (mfl->attr.vendor == FV_S25FLXXXX))
        {
            rc = mf_read_modify_status_winbond(mfl, bank, 0, quad_en, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1);
            CHECK_RC(rc);
        }
        else if (mfl->attr.vendor == FV_ST)
        {
            rc = mf_read_modify_status_new(mfl, bank, SFC_RDNVR, SFC_WRNVR, !quad_en, QUAD_EN_OFFSET_MICRON, 1, 2);
            CHECK_RC(rc);
        }
        else if ((mfl->attr.vendor == FV_IS25LPXXX) || (mfl->attr.vendor == FV_MX25K16XXX && !is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl)))
        {
            rc = mf_read_modify_status_winbond(mfl, bank, 1, quad_en, QUAD_EN_OFFSET_ISSI_MACRONIX, 1);
            CHECK_RC(rc);
        }
        else if (mfl->attr.vendor == FV_GD25QXXX)
        {
            rc = mf_read_modify_status_winbond(mfl, bank, 1, quad_en, QUAD_EN_OFFSET_GIGABYTE, 1);
            CHECK_RC(rc);
        }
        else
        {
            return MFE_NOT_IMPLEMENTED;
        }
    }
    return MFE_OK;
}

int mf_get_quad_en_direct_access(mflash* mfl, u_int8_t* quad_en_p)
{
    if (!mfl || !quad_en_p)
    {
        return MFE_BAD_PARAMS;
    }
    if (!(mfl->attr.quad_en_support && mfl->supp_sr_mod))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    if ((mfl->attr.vendor == FV_WINBOND) || (mfl->attr.vendor == FV_S25FLXXXX) || is_ISSI_is25wj032f(mfl))
    {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDSR2, QUAD_EN_OFFSET_WINBOND_CYPRESS, 1, 1, 1);
    }
    else if (mfl->attr.vendor == FV_ST)
    {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDNVR, QUAD_EN_OFFSET_MICRON, 1, 2, 0);
    }
    else if ((mfl->attr.vendor == FV_IS25LPXXX) || (mfl->attr.vendor == FV_MX25K16XXX && !is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl)))
    {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDSR, QUAD_EN_OFFSET_ISSI_MACRONIX, 1, 1, 1);
    }
    else if (mfl->attr.vendor == FV_GD25QXXX)
    {
        return mf_get_param_int(mfl, quad_en_p, SFC_RDSR2, QUAD_EN_OFFSET_GIGABYTE, 1, 2, 1);
    }
    return MFE_NOT_SUPPORTED_OPERATION;
}

int is_60MB_bottom_protection_supported_wrapper(mflash* mfl)
{
    return is_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size, mfl->attr.series_code);
}

int is_60MB_bottom_protection_supported(uint8_t vendor, uint8_t type, uint8_t log2_bank_size, uint8_t series_code)
{
    if (is_ISSI_60MB_bottom_protection_supported(vendor, type, log2_bank_size) || is_WINBOND_60MB_bottom_protection_supported(vendor, type, log2_bank_size) ||
        is_macronix_mx25u51294g_mx25u51294gxdi08(vendor, type, log2_bank_size, series_code))
    {
        return 1;
    }
    return 0;
}

int is_60MB_bottom_protection_supported_using_cmp(mflash* mfl)
{
    return is_WINBOND_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size) || is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl);
}

int is_ISSI_60MB_bottom_protection_supported(uint8_t vendor, uint8_t type, uint8_t log2_bank_size)
{
    if ((vendor == FV_IS25LPXXX) && ((type == FMT_IS25LPXXX) || (type == FMT_IS25WPXXX)) && (log2_bank_size == FD_512))
    {
        return 1;
    }
    return 0;
}

int is_WINBOND_60MB_bottom_protection_supported(uint8_t vendor, uint8_t type, uint8_t log2_bank_size)
{
    if ((vendor == FV_WINBOND) && (type == FMT_WINBOND_IM) && (log2_bank_size == FD_512))
    {
        return 1;
    }
    return 0;
}

int is_60MB_bottom_protection_params(write_protect_info_t* protect_info)
{
    if ((protect_info->sectors_num != SECTOR_NUM_60MB_SPECIAL_CASE) || !protect_info->is_bottom || protect_info->is_subsector)
    {
        return 0;
    }
    return 1;
}

int get_sectors_num_for_WINBOND_MACRONIX_60MB_bottom_protection_supported(u_int8_t bp_val, uint8_t cmp, int spec_alignment_factor)
{
    int all_protected = 1024;
    int none_protected = 0;

    if (((cmp == 0) && (bp_val == 11 || bp_val == 12 || bp_val == 13 || bp_val == 14 || bp_val == 15)) ||
        (cmp == 1 && bp_val == 0))
    {
        return all_protected;
    }
    if ((cmp && (bp_val == 11 || bp_val == 12 || bp_val == 13 || bp_val == 14 || bp_val == 15)) ||
        (cmp == 0 && bp_val == 0))
    {
        return none_protected;
    }
    if (!cmp)
    {
        return (1 << (bp_val + spec_alignment_factor));
    }
    /* -> cmp == 1 */
    return all_protected - (1 << (bp_val + spec_alignment_factor));
}

int update_protect_info_for_cmp_flashes(mflash* mfl, write_protect_info_t* protect_info, int spec_alignment_factor)
{
    int rc = MFE_OK;
    uint8_t status = 0;
    int is_bottom = EXTRACT(status, TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256, 1);
    uint8_t cmp = 0;
    rc = mf_get_cmp(mfl, &cmp); // protect_info->bp_val == BP_WINBOND_MACRONIX_60MB_SPECIAL_CASE && !is_bottom
                                // -> happens for CMP=1 and CMP=0, when CMP is set, it's the special 60MB
                                // protection mode, and the one we're looking for
    CHECK_RC(rc);
    protect_info->sectors_num = get_sectors_num_for_WINBOND_MACRONIX_60MB_bottom_protection_supported(
      protect_info->bp_val, cmp, spec_alignment_factor);
    if (cmp)
    {
        protect_info->tbs_bit = is_bottom;
        protect_info->is_bottom = !(protect_info->tbs_bit); // CMP =1 -> if tbs_bit==1(Bottom), top part is protected
        // else (tbs_bit==0) -> Bottom part is protected
    }
    return rc;
}

int mf_set_write_protect_direct_access(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info)
{
    u_int32_t protect_mask = 0, log2_sect_num;
    u_int32_t sectors_num = protect_info->sectors_num;
    int rc;
    write_protect_info_t cur_protect_info;

    memset(&cur_protect_info, 0x0, sizeof(cur_protect_info));

    /* printf("-D- mf_set_write_protect: bank_num = %#x, subsec: %#x, bottom: %#x, sectors_num=%#x\n", bank_num, */
    /*       protect_info->is_subsector, protect_info->is_bottom, protect_info->sectors_num); */

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    if (((protect_info->sectors_num - 1) & protect_info->sectors_num) != 0)
    {
        if (!is_60MB_bottom_protection_supported_wrapper(mfl))
        {
            return MFE_SECTORS_NUM_NOT_POWER_OF_TWO;
        }
        if (!is_60MB_bottom_protection_params(protect_info))
        {
            return MFE_SECTORS_NUM_NOT_POWER_OF_TWO;
        }
    }
    if (protect_info->sectors_num > MAX_SECTORS_NUM)
    {
        if (!is_60MB_bottom_protection_supported_wrapper(mfl))
        {
            return MFE_EXCEED_SECTORS_MAX_NUM;
        }
        if (!is_60MB_bottom_protection_params(protect_info))
        {
            return MFE_EXCEED_SECTORS_MAX_NUM;
        }
    }
    if (((mfl->attr.vendor == FV_S25FLXXXX) && (mfl->attr.type == FMT_S25FLXXXL) && (mfl->attr.log2_bank_size == FD_128)) ||
        ((mfl->attr.vendor == FV_WINBOND) && (mfl->attr.type == FMT_WINBOND_3V) && (mfl->attr.log2_bank_size == FD_128)))
    {
        if (!protect_info->is_subsector && ((protect_info->sectors_num == 1) || (protect_info->sectors_num == 2)))
        {
            return MFE_SECTORS_NUM_MORE_THEN_0_LESS_THEN_4;
        }
    }
    if (protect_info->is_subsector && !mfl->attr.protect_sub_and_sector)
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    if (mfl->attr.protect_sub_and_sector && protect_info->is_subsector)
    {
        if (protect_info->sectors_num > MAX_SUBSECTOR_NUM)
        {
            return MFE_EXCEED_SUBSECTORS_MAX_NUM;
        }
    }
    if ((mfl->attr.vendor == FV_MX25K16XXX && !is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl)) || mfl->attr.vendor == FV_IS25LPXXX)
    {
        rc = mf_get_write_protect(mfl, bank_num, &cur_protect_info);
        CHECK_RC(rc);
        if (cur_protect_info.is_bottom && !protect_info->is_bottom)
        {
            if (protect_info->sectors_num)
            {
                return MFE_DATA_IS_OTP;
            }
            else
            {
                protect_info->is_bottom = cur_protect_info.is_bottom; /* write protect is disabled, so we don't really */
                                                                      /* care about top/bottom bit. */
            }
        }
    }

    for (log2_sect_num = 0; log2_sect_num < 8; log2_sect_num++)
    {
        if (sectors_num == 0)
        {
            break;
        }
        sectors_num >>= 1;
    }
    /* adrianc: at this point log2_sect_num is actually  bigger by 1(if sectors_num!=0) to fit the BP bit values in the */
    /* flash spec */

    if ((log2_sect_num != 0) && !protect_info->is_subsector &&
        (((mfl->attr.vendor == FV_S25FLXXXX) && (mfl->attr.type == FMT_S25FLXXXL) && (mfl->attr.log2_bank_size == FD_128)) ||
         ((mfl->attr.vendor == FV_WINBOND) && (mfl->attr.type == FMT_WINBOND_3V) && (mfl->attr.log2_bank_size == FD_128))))
    {
        log2_sect_num -= 2; /* spec alignment */
    }

    if ((mfl->attr.vendor == FV_ST) && (mfl->attr.type == FMT_N25QXXX))
    {
        protect_mask = MERGE(protect_mask, log2_sect_num & 0x7, 0, BP_SIZE);
        protect_mask = MERGE(protect_mask, protect_info->is_bottom, BP_SIZE, 1);
        protect_mask = MERGE(protect_mask, (log2_sect_num & 0x8) >> 3, BP_SIZE + 1, 1);
        return mf_read_modify_status_winbond(mfl, bank_num, 1, protect_mask, BP_OFFSET, PROTECT_BITS_SIZE);
    }
    else if ((mfl->attr.vendor == FV_MX25K16XXX) || (mfl->attr.vendor == FV_IS25LPXXX) ||
             ((mfl->attr.vendor == FV_S25FLXXXX) && (mfl->attr.type == FMT_S25FLXXXL) && (mfl->attr.log2_bank_size == FD_256)) ||
             ((mfl->attr.vendor == FV_WINBOND) && (mfl->attr.type == FMT_WINBOND_3V) && (mfl->attr.log2_bank_size == FD_256)) ||
             (is_WINBOND_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size)))
    {
        if (mfl->attr.vendor == FV_MX25K16XXX && !is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
        {
            rc = mf_read_modify_status_winbond(mfl, bank_num, 0, protect_info->is_bottom, TB_OFFSET_MACRONIX, 1);
            CHECK_RC(rc);
        }
        else if (mfl->attr.vendor == FV_IS25LPXXX)
        {
            if (is_ISSI_is25wj032f(mfl))
            {
                rc = set_tb_for_ISSI_is25wj032(mfl, protect_info->is_bottom, bank_num);
                CHECK_RC(rc);
            }
            else
            {
                rc = mf_read_modify_status_new(mfl, bank_num, SFC_RDFR, SFC_WRFR, protect_info->is_bottom,
                                               TB_OFFSET_ISSI, 1, 1);
                CHECK_RC(rc);

                // to support 60MB bottom protection for ISSI - we have to protect a number of sectors that is not a
                // power of 2, and there isn't any straightforward mapping between the number of sectors and the BP
                // bits, therefore we make sure to set BP bits manually
                if (is_ISSI_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size))
                {
                    if (is_60MB_bottom_protection_params(protect_info))
                    {
                        return mf_read_modify_status_winbond(mfl, bank_num, 1, BP_ISSI_60MB_SPECIAL_CASE, BP_OFFSET,
                                                             BP_SIZE + 1);
                    }
                }
            }
        }
        /* to support 60MB bottom protection for WINBOND - we have to protect a number of sectors that is not a power */
        /* of 2. For WINBOND the workaround is by setting protection for 4MB from the top, and then set CMP bit to 1 */
        /* -which will protect the complement from the bottom (bottom 60MB) */
        else if (is_60MB_bottom_protection_supported_using_cmp(mfl))
        {
            if (is_60MB_bottom_protection_params(protect_info))
            {
                rc = mf_set_cmp(mfl, 1); /* triggering 60MB protection for WINBOND */
                CHECK_RC(rc);
                uint8_t is_bottom = 0; /* CMP is set, so we need to set the bottom bit to 0 (=Top), this way when the */
                                       /* complement is protected, it'd be from the Bottom, not Top */
                rc = mf_read_modify_status_winbond(mfl, bank_num, 1, is_bottom, TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256, 1);
                CHECK_RC(rc);
                return mf_read_modify_status_winbond(mfl, bank_num, 1, BP_WINBOND_MACRONIX_60MB_SPECIAL_CASE, BP_OFFSET, BP_SIZE + 1);
            }
            else
            {
                rc = mf_set_cmp(mfl, 0); /* shutting down 60MB protection for WINBOND */
                CHECK_RC(rc);
                rc = mf_read_modify_status_winbond(mfl, bank_num, 1, protect_info->is_bottom, TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256, 1);
                CHECK_RC(rc);
            }
        }
        else
        { /* vendor == FV_S25FLXXXX or vendor == FV_WINBOND */
            rc = mf_read_modify_status_winbond(mfl, bank_num, 1, protect_info->is_bottom, TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256, 1);
            CHECK_RC(rc);
        }

        int bp_size = is_ISSI_is25wj032f(mfl) ? BP_SIZE : BP_SIZE + 1;
        return mf_read_modify_status_winbond(mfl, bank_num, 1, log2_sect_num, BP_OFFSET, bp_size);
    }
    else
    {
        u_int8_t modify_size = 0;

        protect_mask = MERGE(protect_mask, log2_sect_num, 0, BP_SIZE);
        modify_size += BP_SIZE;

        protect_mask = MERGE(protect_mask, protect_info->is_bottom, BP_SIZE, 1);
        modify_size += 1;
        if (mfl->attr.protect_sub_and_sector)
        {
            protect_mask = MERGE(protect_mask, protect_info->is_subsector, BP_SIZE + 1, 1);
            modify_size += 1;
        }
        return mf_read_modify_status_winbond(mfl, bank_num, 1, protect_mask, BP_OFFSET, modify_size);
    }
}

int mf_get_write_protect_direct_access(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info)
{
    int rc = 0;
    u_int8_t status = 0;
    u_int8_t tb_offset = TB_OFFSET;
    int spec_alignment_factor;

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);
    protect_info->is_subsector = 0; /* Defaultly no support for subsector protection */
    if (mfl->attr.vendor == FV_MX25K16XXX && !is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
    {
        rc = mfl->f_spi_status(mfl, SFC_RDCR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, TB_OFFSET_MACRONIX, 1);
        protect_info->tbs_bit = protect_info->is_bottom;
    }
    else if (is_ISSI_is25wj032f(mfl))
    {
        rc = get_tb_for_ISSI_is25wj032f(mfl, &protect_info->is_bottom, &protect_info->is_subsector);
        CHECK_RC(rc);
    }
    else if (mfl->attr.vendor == FV_IS25LPXXX)
    {
        rc = mfl->f_spi_status(mfl, SFC_RDFR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, TB_OFFSET_ISSI, 1);
        protect_info->tbs_bit = protect_info->is_bottom;
    }
    else
    {
        if (((mfl->attr.vendor == FV_S25FLXXXX) && (mfl->attr.type == FMT_S25FLXXXL) && (mfl->attr.log2_bank_size == FD_256)) ||
            ((mfl->attr.vendor == FV_WINBOND) && (mfl->attr.type == FMT_WINBOND_3V) && (mfl->attr.log2_bank_size == FD_256)) ||
            (is_WINBOND_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size)) || (is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl)))
        {
            tb_offset = TB_OFFSET_CYPRESS_WINBOND_MACRONIX_256;
        }
        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
        CHECK_RC(rc);
        protect_info->is_bottom = EXTRACT(status, tb_offset, 1);
        protect_info->tbs_bit = protect_info->is_bottom;
        if (mfl->attr.protect_sub_and_sector)
        {
            protect_info->is_subsector = EXTRACT(status, SEC_OFFSET, 1);
        }
        else
        {
            protect_info->is_subsector = 0;
        }
    }
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
    CHECK_RC(rc);

    // determine BP_SIZE since in some flashes it's 3 bits and in some it's 4
    uint8_t flash_specific_bp_size = BP_SIZE;
    if (mfl->attr.vendor == FV_MX25K16XXX || mfl->attr.vendor == FV_IS25LPXXX || (mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_256) ||
        (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_256) ||
        (is_WINBOND_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size)))
    {
        flash_specific_bp_size = BP_SIZE + 1;
    }

    spec_alignment_factor =
      ((mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL && mfl->attr.log2_bank_size == FD_128) ||
       (mfl->attr.vendor == FV_WINBOND && mfl->attr.type == FMT_WINBOND_3V && mfl->attr.log2_bank_size == FD_128)) &&
          !protect_info->is_subsector ?
        1 :
        -1;
    if (EXTRACT(status, BP_OFFSET, flash_specific_bp_size) == 0)
    {
        if (is_60MB_bottom_protection_supported_using_cmp(mfl))
        {
            rc = update_protect_info_for_cmp_flashes(mfl, protect_info, spec_alignment_factor);
            CHECK_RC(rc);
        }
        else
        {
            protect_info->sectors_num = 0;
            protect_info->bp_val = 0;
        }
    }
    else
    {
        protect_info->bp_val = EXTRACT(status, BP_OFFSET, flash_specific_bp_size);

        if (is_ISSI_60MB_bottom_protection_supported(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size))
        {
            if ((protect_info->bp_val == BP_ISSI_60MB_SPECIAL_CASE) && protect_info->is_bottom && !protect_info->is_subsector)
            {
                protect_info->sectors_num = SECTOR_NUM_60MB_SPECIAL_CASE;
            }
            else
            {
                protect_info->sectors_num = 1 << (protect_info->bp_val + spec_alignment_factor);
                if (protect_info->is_subsector && protect_info->sectors_num > MAX_SUBSECTOR_NUM &&
                    is_ISSI_is25wj032f(mfl))
                {
                    protect_info->sectors_num = MAX_SUBSECTOR_NUM;
                }
            }
        }
        else if (is_60MB_bottom_protection_supported_using_cmp(mfl)) // WINBOND and Macronix 60MB WP support
        {
            rc = update_protect_info_for_cmp_flashes(mfl, protect_info, spec_alignment_factor);
            CHECK_RC(rc);
        }
        else
        {
            protect_info->sectors_num = 1 << (protect_info->bp_val + spec_alignment_factor);
        }
    }

    return MFE_OK;
}

int mf_is_fifth_gen(mflash* mfl)
{
    MfError status;
    int icmdif_supported = is_icmdif_supported(mfl, &status);

    if (status != MFE_OK)
    {
        return status;
    }
    return icmdif_supported;
}

int mf_enable_hw_access(mflash* mfl, u_int64_t key)
{
#ifndef UEFI_BUILD
    int rc = 0;
    if (mf_is_fifth_gen(mfl))
    {
        return mf_secure_host_op(mfl, key, 0);
    }
    else
    {
        rc = tcif_hw_access(mfl->mf, key, 0 /* Unlock */);
        return (rc == ME_CMDIF_UNKN_TLV) ? MFE_MISMATCH_KEY : MError2MfError((MError)rc);
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
int mf_secure_host_op(mflash* mfl, u_int64_t key, int op)
{
    struct tools_open_mlock mlock;

    memset(&mlock, 0, sizeof(mlock));
    mlock.operation = op;
    mlock.key = key;
    int rc = ME_OK;

    if (IS_CONNECT_IB(mfl->attr.hw_dev_id))
    {
        rc = ME_REG_ACCESS_REG_NOT_SUPP;
    }
    else
    {
        rc = (int)reg_access_secure_host(mfl->mf, REG_ACCESS_METHOD_SET, &mlock);
    }
    switch (rc)
    {
        case ME_REG_ACCESS_REG_NOT_SUPP:
            rc = MFE_NOT_SUPPORTED_OPERATION;
            break;

        case ME_REG_ACCESS_BAD_PARAM:
            rc = MFE_MISMATCH_KEY;
            break;

        default:
            rc = MError2MfError((MError)rc);
            break;
    }
    return rc;
}

int mf_get_secure_host(mflash* mfl, int* mode)
{
    struct tools_open_mlock mlock;

    memset(&mlock, 0, sizeof(mlock));
    int rc = (int)reg_access_secure_host(mfl->mf, REG_ACCESS_METHOD_GET, &mlock);

    *mode = mlock.operation;
    return rc;
}

int mf_disable_hw_access(mflash* mfl)
{
#ifndef UEFI_BUILD
    int rc = 0;
    /* We need to release the semaphore because we will not have any access to semaphore after disabling the HW access
     */
    mfl->unlock_flash_prog_allowed = 1;
    rc = release_semaphore(mfl, 1);
    CHECK_RC(rc);

    rc = tcif_hw_access(mfl->mf, 0, 1 /* Lock */);
    /* translate to operation specific errors */
    switch (rc)
    {
        case ME_CMDIF_UNKN_TLV:
            rc = MFE_MISMATCH_KEY;
            break;

        case ME_CMDIF_BAD_OP:
            rc = MFE_MISSING_KEY;
            break;

        default:
            rc = MError2MfError((MError)rc);
            break;
    }
    return rc;
#else
    (void)mfl;
    return MFE_NOT_SUPPORTED_OPERATION;
#endif
}

int mf_disable_hw_access_with_key(mflash* mfl, u_int64_t key)
{
    if (!mf_is_fifth_gen(mfl))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    return mf_secure_host_op(mfl, key, 1);
}

mfile* mf_get_mfile(mflash* mfl)
{
    return mfl->mf;
}

dm_dev_id_t mf_get_dm_dev_id(mflash* mfl)
{
    return mfl->dm_dev_id;
}

int mf_get_jedec_id(mflash* mfl, u_int32_t* jedec_id)
{
    return mfl->f_get_jedec_id(mfl, jedec_id);
}

int mf_set_quad_en(mflash* mfl, u_int8_t quad_en)
{
    if ((quad_en == 0) && (getenv("FORCE_RESET_QUAD_EN") == NULL))
    {
        /* If flash HOLD state issue is relevant for given device, we'll block disabling Quad mode */
        if (mfl->attr.vendor == FV_WINBOND)
        {
            switch (mfl->dm_dev_id)
            {
                case DeviceConnectX6:
                case DeviceConnectX6DX:
                case DeviceBlueField2:
                case DeviceConnectX7:
                case DeviceBlueField3:
                    printf("-E- Disable QuadEn for given device is not allowed.\n");
                    return MFE_ERROR;

                default:
                    break;
            }
        }
    }
    return mfl->f_set_quad_en(mfl, quad_en);
}

int mf_set_cmp(mflash* mfl, u_int8_t cmp)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (!is_60MB_bottom_protection_supported_using_cmp(mfl))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    int bank = 0, rc = 0;

    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR2, SFC_WRSR2, cmp, COMPLEMENT_PROTECT_OFFSET_WINBOND_MACRONIX, 1, 1);
        CHECK_RC(rc);
    }

    return MFE_OK;
}

int mf_get_cmp(mflash* mfl, u_int8_t* cmp)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (is_60MB_bottom_protection_supported_using_cmp(mfl))
    {
        return mf_get_param_int(mfl, cmp, SFC_RDSR2, COMPLEMENT_PROTECT_OFFSET_WINBOND_MACRONIX, 1, 1, 1);
    }
    return MFE_NOT_SUPPORTED_OPERATION;
}

int mf_get_srl(mflash* mfl, u_int8_t* srl)
{
    if (!mfl || !srl)
    {
        return MFE_BAD_PARAMS;
    }
    return mf_get_param_int(mfl, srl, SFC_RDSR2, SRL_OFFSET_ISSI_MACRONIX, 1, 1, 1);
}

int mf_set_srl(mflash* mfl, u_int8_t srl)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    int bank = 0, rc = 0;
    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        rc = mf_read_modify_status_new(mfl, bank, SFC_RDSR2, SFC_WRSR2, srl, SRL_OFFSET_ISSI_MACRONIX, 1, 1);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int mf_disable_cmp_if_supported(mflash* mfl)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (is_60MB_bottom_protection_supported_using_cmp(mfl))
    {
        return mf_set_cmp(mfl, 0);
    }
    return MFE_OK;
}

int mf_get_quad_en(mflash* mfl, u_int8_t* quad_en)
{
    return mfl->f_get_quad_en(mfl, quad_en);
}

int mf_set_srwd(mflash* mfl, u_int8_t srwd)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (!is_srwd_supported_by_flash(mfl->attr.vendor, mfl->attr.type))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    int bank = 0, rc = 0;

    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        rc = mf_read_modify_status_winbond(mfl, bank, 1, srwd, SRWD_OFFSET_ISSI, 1);
        CHECK_RC(rc);
    }

    return MFE_OK;
}

int mf_get_srwd(mflash* mfl, u_int8_t* srwd)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }
    if (is_srwd_supported_by_flash(mfl->attr.vendor, mfl->attr.type))
    {
        return mf_get_param_int(mfl, srwd, SFC_RDSR, SRWD_OFFSET_ISSI, 1, 1, 1);
    }
    return MFE_NOT_SUPPORTED_OPERATION;
}

int mf_set_srp(mflash* mfl, u_int8_t srp)
{
    if (!mfl)
    {
        return MFE_BAD_PARAMS;
    }

    if (!is_srp_supported_by_flash(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size, mfl->attr.series_code))
    {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    int bank = 0, rc = 0;
    for (bank = 0; bank < mfl->attr.banks_num; bank++)
    {
        rc = mf_read_modify_status_winbond(mfl, bank, 1, srp, SRP_OFFSET_WINBOND, 1);
        CHECK_RC(rc);
    }

    return MFE_OK;
}

int mf_get_srp(mflash* mfl, u_int8_t* srp)
{
    int rc = MFE_OK;
    if (!mfl || !srp)
    {
        rc = MFE_BAD_PARAMS;
    }
    else if (!is_srp_supported_by_flash(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size,
        mfl->attr.series_code))
    {
        rc = MFE_NOT_SUPPORTED_OPERATION;
    }
    else
    {
        u_int8_t status = 0;
        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
        CHECK_RC(rc);
        *srp = EXTRACT(status, SRP_OFFSET_WINBOND, 1);
    }
    return rc;
}

int mf_to_vendor_driver_strength(u_int8_t vendor, u_int8_t value, u_int8_t* driver_strength)
{
    if (vendor == FV_ST)
    {
        switch (value)
        {
            case 100:
                *driver_strength = DRIVER_STRENGTH_VAL_20_MICRON;
                break;

            case 66:
                *driver_strength = DRIVER_STRENGTH_VAL_30_MICRON;
                break;

            case 44:
                *driver_strength = DRIVER_STRENGTH_VAL_45_MICRON;
                break;

            case 22:
                *driver_strength = DRIVER_STRENGTH_VAL_90_MICRON;
                break;

            default:
                return MFE_BAD_PARAMS;
        }
    }
    else if (vendor == FV_MX25K16XXX)
    {
        switch (value)
        {
            case 100:
                *driver_strength = DRIVER_STRENGTH_VAL_120_MACRONIX_MX25K16XXX;
                break;

            case 83:
                *driver_strength = DRIVER_STRENGTH_VAL_100_MACRONIX_MX25K16XXX;
                break;

            case 70:
                *driver_strength = DRIVER_STRENGTH_VAL_85_MACRONIX_MX25K16XXX;
                break;

            case 41:
                *driver_strength = DRIVER_STRENGTH_VAL_50_MACRONIX_MX25K16XXX;
                break;

            default:
                return MFE_BAD_PARAMS;
        }
    }
    else if (vendor == FV_IS25LPXXX)
    {
        switch (value)
        {
            case 100:
                *driver_strength = DRIVER_STRENGTH_VAL_15_ISSI;
                break;

            case 75:
                *driver_strength = DRIVER_STRENGTH_VAL_20_ISSI;
                break;

            case 50:
                *driver_strength = DRIVER_STRENGTH_VAL_30_ISSI;
                break;

            case 33:
                *driver_strength = DRIVER_STRENGTH_VAL_45_ISSI;
                break;

            case 25:
                *driver_strength = DRIVER_STRENGTH_VAL_60_ISSI;
                break;

            case 16:
                *driver_strength = DRIVER_STRENGTH_VAL_90_ISSI;
                break;

            default:
                return MFE_BAD_PARAMS;
        }
    }
    else
    {
        switch (value)
        {
            case 25:
                *driver_strength = DRIVER_STRENGTH_VAL_25_WINBOND;
                break;

            case 50:
                *driver_strength = DRIVER_STRENGTH_VAL_50_WINBOND;
                break;

            case 75:
                *driver_strength = DRIVER_STRENGTH_VAL_75_WINBOND;
                break;

            case 100:
                *driver_strength = DRIVER_STRENGTH_VAL_100_WINBOND;
                break;

            default:
                return MFE_BAD_PARAMS;
        }
    }
    return MFE_OK;
}

int mf_from_vendor_driver_strength(u_int8_t vendor, u_int8_t vendor_driver_strength, u_int8_t* value)
{
    if (vendor == FV_ST)
    {
        switch (vendor_driver_strength)
        {
            case DRIVER_STRENGTH_VAL_20_MICRON:
                *value = 20;
                break;

            case DRIVER_STRENGTH_VAL_30_MICRON:
                *value = 30;
                break;

            case DRIVER_STRENGTH_VAL_45_MICRON:
                *value = 45;
                break;

            case DRIVER_STRENGTH_VAL_90_MICRON:
                *value = 90;
                break;

            default:
                *value = 0xff;
        }
        if (*value != 0xff)
        {
            *value = (20 * 100) / *value;
        }
    }
    else if (vendor == FV_IS25LPXXX)
    {
        switch (vendor_driver_strength)
        {
            case DRIVER_STRENGTH_VAL_15_ISSI:
                *value = 15;
                break;

            case DRIVER_STRENGTH_VAL_20_ISSI:
                *value = 20;
                break;

            case DRIVER_STRENGTH_VAL_30_ISSI:
                *value = 30;
                break;

            case DRIVER_STRENGTH_VAL_45_ISSI:
                *value = 45;
                break;

            case DRIVER_STRENGTH_VAL_60_ISSI:
                *value = 60;
                break;

            case DRIVER_STRENGTH_VAL_90_ISSI:
                *value = 90;
                break;

            default:
                *value = 0xff;
        }
        if (*value != 0xff)
        {
            *value = (15 * 100) / *value;
        }
    }
    else if (vendor == FV_MX25K16XXX)
    {
        switch (vendor_driver_strength)
        {
            case DRIVER_STRENGTH_VAL_120_MACRONIX_MX25K16XXX:
                *value = 100;
                break;

            case DRIVER_STRENGTH_VAL_100_MACRONIX_MX25K16XXX:
                *value = 83;
                break;

            case DRIVER_STRENGTH_VAL_85_MACRONIX_MX25K16XXX:
                *value = 70;
                break;

            case DRIVER_STRENGTH_VAL_50_MACRONIX_MX25K16XXX:
                *value = 41;
                break;

            default:
                return MFE_BAD_PARAMS;
        }
    }
    else
    {
        switch (vendor_driver_strength)
        {
            case DRIVER_STRENGTH_VAL_25_WINBOND:
                *value = 25;
                break;

            case DRIVER_STRENGTH_VAL_50_WINBOND:
                *value = 50;
                break;

            case DRIVER_STRENGTH_VAL_75_WINBOND:
                *value = 75;
                break;

            case DRIVER_STRENGTH_VAL_100_WINBOND:
                *value = 100;
                break;

            default:
                *value = 0xff;
        }
    }
    return MFE_OK;
}

int mf_from_vendor_driver_strength_for_mx25uxxx(u_int8_t vendor_driver_strength, u_int8_t* value)
{
    switch (vendor_driver_strength)
    {
        case DRIVER_STRENGTH_VAL_146_MACRONIX_MX25UXXX:
            *value = 146;
            break;
        case DRIVER_STRENGTH_VAL_76_MACRONIX_MX25UXXX:
            *value = 76;
            break;
        case DRIVER_STRENGTH_VAL_52_MACRONIX_MX25UXXX:
            *value = 52;
            break;
        case DRIVER_STRENGTH_VAL_41_MACRONIX_MX25UXXX:
            *value = 41;
            break;
        case DRIVER_STRENGTH_VAL_34_MACRONIX_MX25UXXX:
            *value = 34;
            break;
        case DRIVER_STRENGTH_VAL_30_MACRONIX_MX25UXXX:
            *value = 30;
            break;
        case DRIVER_STRENGTH_VAL_26_MACRONIX_MX25UXXX:
            *value = 26;
            break;
        case DRIVER_STRENGTH_VAL_24_MACRONIX_MX25UXXX:
            *value = 24;
            break;
        default:
            return MFE_BAD_PARAMS;
    }
    return MFE_OK;
}

int mf_from_vendor_driver_strength_for_mx25u51294g_mx25u51294gxdi08(u_int8_t value, u_int8_t* driver_strength)
{
    switch (value)
    {
        case DRIVER_STRENGTH_VAL_120_MACRONIX_MX25K16XXX:
            *driver_strength = 120;
            break;
        case DRIVER_STRENGTH_VAL_100_MACRONIX_MX25K16XXX:
            *driver_strength = 100;
            break;
        case DRIVER_STRENGTH_VAL_85_MACRONIX_MX25K16XXX:
            *driver_strength = 85;
            break;
        case DRIVER_STRENGTH_VAL_50_MACRONIX_MX25K16XXX:
            *driver_strength = 50;
            break;
        default:
            return MFE_BAD_PARAMS;
    }
    return MFE_OK;
}

int mf_to_vendor_driver_strength_for_mx25u51294g_mx25u51294gxdi08(u_int8_t value, u_int8_t* driver_strength)
{
    switch (value)
    {
        case 120:
            *driver_strength = DRIVER_STRENGTH_VAL_120_MACRONIX_MX25K16XXX;
            break;
        case 100:
            *driver_strength = DRIVER_STRENGTH_VAL_100_MACRONIX_MX25K16XXX;
            break;
        case 85:
            *driver_strength = DRIVER_STRENGTH_VAL_85_MACRONIX_MX25K16XXX;
            break;
        case 50:
            *driver_strength = DRIVER_STRENGTH_VAL_50_MACRONIX_MX25K16XXX;
            break;
        default:
            return MFE_BAD_PARAMS;
    }
    return MFE_OK;
}

int mf_to_vendor_driver_strength_for_mx25uxxx(u_int8_t value, u_int8_t* driver_strength)
{
    switch (value)
    {
        case 146:
            *driver_strength = DRIVER_STRENGTH_VAL_146_MACRONIX_MX25UXXX;
            break;
        case 76:
            *driver_strength = DRIVER_STRENGTH_VAL_76_MACRONIX_MX25UXXX;
            break;
        case 52:
            *driver_strength = DRIVER_STRENGTH_VAL_52_MACRONIX_MX25UXXX;
            break;
        case 41:
            *driver_strength = DRIVER_STRENGTH_VAL_41_MACRONIX_MX25UXXX;
            break;
        case 34:
            *driver_strength = DRIVER_STRENGTH_VAL_34_MACRONIX_MX25UXXX;
            break;
        case 30:
            *driver_strength = DRIVER_STRENGTH_VAL_30_MACRONIX_MX25UXXX;
            break;
        case 26:
            *driver_strength = DRIVER_STRENGTH_VAL_26_MACRONIX_MX25UXXX;
            break;
        case 24:
            *driver_strength = DRIVER_STRENGTH_VAL_24_MACRONIX_MX25UXXX;
            break;
        default:
            return MFE_BAD_PARAMS;
    }
    return MFE_OK;
}

int mf_set_driver_strength(mflash* mfl, u_int8_t driver_strength)
{
    u_int8_t vendor_driver_strength = 0;
    int rc = MFE_OK;
    if (is_macronix_special_case_for_driver_strength(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size) || is_macronix_mx25u51245g(mfl))
    {
        rc = mf_to_vendor_driver_strength_for_mx25uxxx(driver_strength, &vendor_driver_strength);
    }
    else if (is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
    {
        rc = mf_to_vendor_driver_strength_for_mx25u51294g_mx25u51294gxdi08(driver_strength, &vendor_driver_strength);
    }
    else
    {
        rc = mf_to_vendor_driver_strength(mfl->attr.vendor, driver_strength, &vendor_driver_strength);
    }
    CHECK_RC(rc);
    return mfl->f_set_driver_strength(mfl, vendor_driver_strength);
}

int mf_get_driver_strength(mflash* mfl, u_int8_t* driver_strength)
{
    u_int8_t value = 0;
    int rc = mfl->f_get_driver_strength(mfl, &value);
    CHECK_RC(rc);
    if ((is_macronix_special_case_for_driver_strength(mfl->attr.vendor, mfl->attr.type, mfl->attr.log2_bank_size) || is_macronix_mx25u51245g(mfl)))
    {
        rc = mf_from_vendor_driver_strength_for_mx25uxxx(value, driver_strength);
    }
    else if (is_macronix_mx25u51294g_mx25u51294gxdi08_wrapper(mfl))
    {
        rc = mf_from_vendor_driver_strength_for_mx25u51294g_mx25u51294gxdi08(value, driver_strength);
    }
    else
    {
        rc = mf_from_vendor_driver_strength(mfl->attr.vendor, value, driver_strength);
    }
    return rc;
}

int mf_set_write_protect(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info)
{
    return mfl->f_set_write_protect(mfl, bank_num, protect_info);
}

int mf_get_write_protect(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info)
{
    return mfl->f_get_write_protect(mfl, bank_num, protect_info);
}

int mf_set_dummy_cycles(mflash* mfl, u_int8_t num_of_cycles)
{
    return mfl->f_set_dummy_cycles(mfl, num_of_cycles);
}

int mf_get_dummy_cycles(mflash* mfl, u_int8_t* num_of_cycles)
{
    return mfl->f_get_dummy_cycles(mfl, num_of_cycles);
}

int modify_flash_info_if_needed(mflash* mfl, flash_info_t* f_info) // TODO: add seriesCode capability support for the
                                                                   // supported flashes
{
    MacronixSeriesCode series_code = MACRONIX_UNKNOWN;
    int rc = identify_macronix_flash(mfl, &series_code);
    CHECK_RC(rc);

    switch (series_code)
    {
        case MACRONIX_MX25U51245G:
            break;
        case MACRONIX_MX25U51294G_MX25U51294GXDI08:
            DPRINTF(("for this series code, quad enable is non-configurable setting\n"));
            f_info->quad_en_support = 0;
            break;
        default:
            DPRINTF(("Unknown Macronix series code: 0x%02X\n", series_code));
            rc = MFE_UNSUPPORTED_FLASH_TYPE;
            break;
    }
    CHECK_RC(rc);

    f_info->series_code = series_code;
    return rc;
}

/**
 * Identify Macronix flash using SFDP Series Code at address 0x1F2
 */
int identify_macronix_flash(mflash* mfl, MacronixSeriesCode* series_code)
{
    int rc = MFE_OK;

    if (!mfl || !series_code)
    {
        return MFE_BAD_PARAMS;
    }

    // check if SFDP is supported by the flash
    uint32_t sfdp_signature = 0;
    rc = mf_read_sfdp_table(mfl, 0x00, 4, false, &sfdp_signature);
    if (rc != MFE_OK)
    {
        DPRINTF(("Failed to read SFDP signature: %s", mf_err2str(rc)));
        return MFE_ERROR;
    }
    DPRINTF(("SFDP Signature: 0x%08X (should be 0x50444653)\n", sfdp_signature));
    if (sfdp_signature == 0x50444653) // SFDP is supported by the flash
    {
        // get series code from SFDP, this differentiates flashes that have same JEDEC id
        *series_code = MACRONIX_UNKNOWN;
        rc = mf_read_sfdp_table(mfl, 0x1F2, 1, false, (uint32_t*)series_code);
        if (rc != MFE_OK)
        {
            DPRINTF(("Failed to read Series Code SFDP: %s", mf_err2str(rc)));
            return MFE_ERROR;
        }
        DPRINTF(("Series Code SFDP: 0x%02X\n", *series_code));
    }

    // check if the series code is supported
    switch (*series_code)
    {
        case MACRONIX_MX25U51294G_MX25U51294GXDI08:
        case MACRONIX_MX25U51245G:
            break;
        default:
            DPRINTF(("Unknown Macronix series code: 0x%02X\n", *series_code));
            rc = MFE_UNSUPPORTED_FLASH_TYPE;
            break;
    }

    return rc;
}

// wrapper for reading byte_num bytes from the given address in the SFDP table
int mf_read_sfdp_table(mflash* mfl, uint32_t address, uint8_t bytes_num, bool swap, uint32_t* data)
{
    int rc = MFE_OK;
    if (!mfl || bytes_num == 0 || bytes_num > 4)
    {
        return MFE_BAD_PARAMS;
    }

    uint8_t data_buffer[4] = {0};

    rc = new_gw_spi_read_sfdp(mfl, address, data_buffer, bytes_num);
    if (rc != MFE_OK)
    {
        return rc;
    }

    memcpy(data, data_buffer, bytes_num);

    if (swap)
    {
        // Endian swap
        uint32_t swapped = 0;
        int i = 0;
        for (; i < (int)bytes_num; i++)
        {
            ((uint8_t*)&swapped)[bytes_num - 1 - i] = data_buffer[i];
        }
        *data = swapped;
    }

    return rc;
}