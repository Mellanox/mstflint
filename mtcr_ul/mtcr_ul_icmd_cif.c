/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/bit_slice.h"
#include "common/tools_time.h"
#include "mtcr_icmd_cif.h"
#include "packets_common.h"
#include "mtcr_gpu.h"
#ifndef __FreeBSD__
#include "mtcr_ib_res_mgt.h"
#endif
#include "tools_dev_types.h"

#include "mtcr_mem_ops.h"
#include "mtcr_ul_com.h"

#define ICMD_QUERY_CAP_CMD_ID        0x8400
#define ICMD_QUERY_CAP_CMD_SZ        0x8
#define ICMD_QUERY_CAP_EXMB_ICMD_OFF 0x8
#define SEMAPHORE_62_LOCKED_INDICATOR 0x1


/* _DEBUG_MODE   // un-comment this to enable debug prints */

#define ICMD_DEFAULT_TIMEOUT           5120
#define STAT_CFG_NOT_DONE_ADDR_CIB     0xb0004
#define STAT_CFG_NOT_DONE_ADDR_CX4     0xb0004
#define STAT_CFG_NOT_DONE_ADDR_SW_IB   0x80010
#define STAT_CFG_NOT_DONE_ADDR_QUANTUM 0x100010
#define STAT_CFG_NOT_DONE_ADDR_CX5     0xb5e04
#define STAT_CFG_NOT_DONE_ADDR_CX6     0xb5f04
#define STAT_CFG_NOT_DONE_ADDR_CX7     0xb5f04
#define STAT_CFG_NOT_DONE_ADDR_CX8     656132
#define STAT_CFG_NOT_DONE_ADDR_GPU     0x3100010
#define STAT_CFG_NOT_DONE_BITOFF_CIB   31
#define STAT_CFG_NOT_DONE_BITOFF_CX4   31
#define STAT_CFG_NOT_DONE_BITOFF_SW_IB 0
#define STAT_CFG_NOT_DONE_BITOFF_CX5   31
#define STAT_CFG_NOT_DONE_BITOFF_CX7   31
#define SEMAPHORE_ADDR_CIB             0xe27f8 /* sem62 */
#define SEMAPHORE_ADDR_CX4             0xe250c /* sem67 bit31 is the semaphore bit here (only one semaphore in this dword) */
#define SEMAPHORE_ADDR_SW_IB           0xa24f8 /* sem 62 */
#define SEMAPHORE_ADDR_QUANTUM         0xa68f8
#define SEMAPHORE_ADDR_QUANTUM2        0xa52f8
#define SEMAPHORE_ADDR_QUANTUM3        0xa52f8 /* 0x25b */
#define SEMAPHORE_ADDR_GB100           0xa52f8
#define SEMAPHORE_ADDR_CX5             0xe74e0
#define SEMAPHORE_ADDR_CX7             0xe5660
#define SEMAPHORE_ADDR_CX8             358016
#define SEMAPHORE_ADDR_GPU             0x308F4F8
#define SEMAPHORE_ADDR_GR100           0x30938F8
#define HCR_ADDR_CIB                   0x0
#define HCR_ADDR_CX4                   HCR_ADDR_CIB
#define HCR_ADDR_CX5                   HCR_ADDR_CIB
#define HCR_ADDR_CX7                   HCR_ADDR_CIB
#define HCR_ADDR_SW_IB                 0x80000
#define HCR_ADDR_QUANTUM               0x100000
#define HCR_ADDR_GPU                   0x3100044
#define ICMD_VERSION_BITOFF            24
#define ICMD_VERSION_BITOFF_GPU        0
#define ICMD_VERSION_BITLEN            8
#define ICMD_VERSION_BITLEN_CX8        4
#define CMD_PTR_ADDR_CIB               0x0
#define CMD_PTR_ADDR_SW_IB             0x80000
#define CMD_PTR_ADDR_QUANTUM           0x100000
#define CMD_PTR_ADDR_CX4               CMD_PTR_ADDR_CIB
#define CMD_PTR_ADDR_CX5               CMD_PTR_ADDR_CIB
#define CMD_PTR_ADDR_CX7               CMD_PTR_ADDR_CIB
#define CMD_PTR_ADDR_CX8               27262976
#define CMD_PTR_ADDR_GPU               0x3100000
#define CMD_PTR_BITOFF                 0
#define CMD_PTR_BITLEN                 24
#define CMD_PTR_BITLEN_CX8             28
#define CMD_PTR_BITLEN_GPU             32
#define CTRL_OFFSET                    0x3fc
#define BUSY_BITOFF                    0
#define BUSY_BITLEN                    1
#define BUSY_BIT_DOWN 0
#define EXMB_BITOFF                    1
#define EXMB_BITLEN                    1
#define OPCODE_BITOFF                  16
#define OPCODE_BITLEN                  16
#define STATUS_BITOFF                  8
#define STATUS_BITLEN                  8
#define VCR_CTRL_ADDR                  0x0
#define VCR_SEMAPHORE62                0x0 /* semaphore Domain */
#define VCR_CMD_ADDR                   0x100000 /* mailbox addr */
#define VCR_CMD_SIZE_ADDR              0x1000 /* mailbox size */
#define VCR_SYNDROME_OFFSET            0x1008
#define SYNDROME_OFFSET                0x3f8
#define SYNDROME_BITOFF                0
#define SYNDROME_BITLEN                24


#define EXT_MBOX_DMA_OFF 0x8

#define SEMAPHORE_ADDR_GBOX                0xa6850
#define CMD_PTR_ADDR_GBOX                  0x90010
#define GBOX_GW_OPCODE_OFFSET              256
#define GBOX_GW_REG_OPCODE_OFFSET          252
#define GBOX_GW_REQUEST_DATA_BLOCK_OFFSET  0
#define GBOX_GW_RESPONSE_DATA_BLOCK_OFFSET 260
#define GBOX_MAX_DATA_SIZE                 256
#define GBOX_STAT_CFG_NOT_DONE_ADDR        0x90000
#define GBOX_REG_ACCESS_CMD_OPCODE         0x0ff
#define GBOX_BUSY_BITOFF                   31
#define GBOX_OPCODE_BITOFF                 16
#define GBOX_OPCODE_BITLEN                 10
#define GBOX_REG_ACC_W_SIZE_BITOFF         0
#define GBOX_REG_ACC_W_SIZE_BITLEN         8
#define GBOX_STATUS_BITOFF                 28
#define GBOX_STATUS_BITLEN                 3
#define GBOX_STATUS1_BITOFF                8
#define GBOX_STATUS1_BITLEN                7
#define GBOX_READ_SIZE_BITOFF              0
#define GBOX_READ_SIZE_BITLEN              8
/*
 * General Macros
 */
#define CHECK_RC(rc) \
    if ((rc))        \
    {                \
        return (rc); \
    }
#define CHECK_RC_GO_TO(rc, lable) \
    if ((rc))                     \
    {                             \
        goto lable;               \
    }
#define DBG_PRINTF(...)                   \
    do                                    \
    {                                     \
        if (getenv("MFT_DEBUG") != NULL)  \
        {                                 \
            fprintf(stderr, __VA_ARGS__); \
        }                                 \
    } while (0)
/*
 * Macros for accessing CR-Space
 */
#define MWRITE_BUF(mf, offset, data, byte_len)                                                 \
    (((unsigned)(mwrite_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len)) ? \
     ME_ICMD_STATUS_CR_FAIL :                                                                  \
     ME_OK)
#define MREAD_BUF(mf, offset, data, byte_len)                                                                          \
    (((unsigned)(mread_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len)) ? ME_ICMD_STATUS_CR_FAIL : \
     ME_OK)

#define MWRITE4(mf, offset, value) \
    (((unsigned)(mwrite4((mf), (offset), (value))) != 4U) ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD4(mf, offset, ptr) (((unsigned)(mread4((mf), (offset), (ptr))) != 4U) ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

/*
 * Macros for accessing Icmd Space
 */
#define SET_SPACE_FOR_ICMD_ACCESS(mf) \
    if (mf->functional_vsec_supp)     \
    {                                 \
        mset_addr_space(mf, AS_ICMD); \
    }
#define SET_SPACE_FOR_SEMAPHORE_ACCESS(mf) \
    if (mf->functional_vsec_supp)          \
    {                                      \
        mset_addr_space(mf, AS_SEMAPHORE); \
    }
#define RESTORE_SPACE(mf) mset_addr_space(mf, AS_CR_SPACE)

static int MWRITE4_ICMD(mfile* mf, int offset, u_int32_t value)
{
    SET_SPACE_FOR_ICMD_ACCESS(mf);
    DBG_PRINTF("-D- MWRITE4_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space);
    if (mwrite4(mf, offset, value) != 4) {
        mset_addr_space(mf, AS_CR_SPACE);
        return ME_ICMD_STATUS_CR_FAIL;
    }
    RESTORE_SPACE(mf);
    return ME_OK;
}

static int MREAD4_ICMD(mfile* mf, int offset, u_int32_t* ptr)
{
    SET_SPACE_FOR_ICMD_ACCESS(mf);
    DBG_PRINTF("-D- MREAD4_ICMD: off: %x, addr_space: %x\r\n", offset, mf->address_space);
    if (mread4(mf, offset, ptr) != 4) {
        RESTORE_SPACE(mf);
        return ME_ICMD_STATUS_CR_FAIL;
    }
    RESTORE_SPACE(mf);
    return ME_OK;
}

#define MWRITE_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)                              \
    do                                                                                           \
    {                                                                                            \
        DBG_PRINTF("-D- MWRITE_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space); \
        SET_SPACE_FOR_ICMD_ACCESS(mf);                                                           \
        if ((unsigned)mwrite_buffer(mf, offset, data, byte_len) != (unsigned)byte_len)           \
        {                                                                                        \
            RESTORE_SPACE(mf);                                                                   \
            action_on_fail;                                                                      \
        }                                                                                        \
        RESTORE_SPACE(mf);                                                                       \
    } while (0)

#define MREAD_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)                              \
    do                                                                                          \
    {                                                                                           \
        DBG_PRINTF("-D- MREAD_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space); \
        SET_SPACE_FOR_ICMD_ACCESS(mf);                                                          \
        if ((unsigned)mread_buffer(mf, offset, data, byte_len) != (unsigned)byte_len)           \
        {                                                                                       \
            RESTORE_SPACE(mf);                                                                  \
            action_on_fail;                                                                     \
        }                                                                                       \
        RESTORE_SPACE(mf);                                                                      \
    } while (0)

/*
 * Macros for accessing semaphore space
 */
int MWRITE4_SEMAPHORE(mfile* mf, int offset, int value)
{
    SET_SPACE_FOR_SEMAPHORE_ACCESS(mf);
    if (mwrite4(mf, offset, value) != 4) {
        RESTORE_SPACE(mf);
        return ME_ICMD_STATUS_CR_FAIL;
    }
    RESTORE_SPACE(mf);
    return ME_OK;
}

int MREAD4_SEMAPHORE(mfile* mf, int offset, u_int32_t* ptr)
{
    SET_SPACE_FOR_SEMAPHORE_ACCESS(mf);
    if (mread4(mf, offset, ptr) != 4) {
        RESTORE_SPACE(mf);
        return ME_ICMD_STATUS_CR_FAIL;
    }
    RESTORE_SPACE(mf);

    // When accessing directly to the device configuration space, the semaphore lock is the last bit in the DWORD.
    // When accessing via VSC GW or BAR0 GW, the semaphore lock is the whole dword.
    if (!is_gw_access(mf))
    {
        *ptr = EXTRACT(*ptr, 31, 1);
    }

    return ME_OK;
}

enum {
    RW_READ  = 0x1,
    RW_WRITE = 0x0
};

/***********************************************
 *
 *  get correct addresses for : STAT_CCFG_NOT_DONE_ADDR, SEMAPHORE_ADDR, HCR_ADDR, CMD_PTR_ADDR
 *  according to Hw devid
 */

#define HW_ID_ADDR      0xf0014
#define CIB_HW_ID       511
#define CX4_HW_ID       521
#define CX4LX_HW_ID     523
#define CX5_HW_ID       525
#define CX6_HW_ID       527
#define CX6DX_HW_ID     530
#define CX6LX_HW_ID     534
#define CX7_HW_ID       536
#define CX8_HW_ID       542
#define CX9_HW_ID       548
#define CX8_PURE_PCIE_SWITCH_HW_ID       546
#define CX9_PURE_PCIE_SWITCH_HW_ID       552
#define BF_HW_ID        529
#define BF2_HW_ID       532
#define BF3_HW_ID       540
#define BF4_HW_ID       544
#define SW_IB_HW_ID     583
#define SW_EN_HW_ID     585
#define SW_IB2_HW_ID    587
#define QUANTUM_HW_ID   589
#define SPECTRUM2_HW_ID 590
#define SPECTRUM3_HW_ID 592
#define QUANTUM2_HW_ID  599
#define QUANTUM3_HW_ID  603 /* 0x25b */
#define GB100_HW_ID     0x2900
#define GR100_HW_ID     0x3000
#define SPECTRUM4_HW_ID 596
#define SPECTRUM5_HW_ID 624
#define SPECTRUM6_HW_ID 628
#define AMOS_GBOX_HW_ID 594

/***** GLOBALS *****/
int increase_poll_time = 0;
void set_increase_poll_time(int new_value)
{
    increase_poll_time = new_value;
}

u_int32_t gbox_gw_start_addr = 0xffff;
/***** GLOBALS *****/

/*************************************************************************************/
/*
 * get_version
 */
static int get_version(mfile* mf, u_int32_t hcr_address)
{
    u_int32_t reg = 0x0;

    if (MREAD4(mf, hcr_address, &reg)) {
        return ME_ICMD_STATUS_CR_FAIL;
    }
    reg = EXTRACT(reg, mf->icmd.version_bit_offset, ICMD_VERSION_BITLEN);
    return reg;
}

static int check_busy_bit(mfile* mf, int busy_bit_offset, u_int32_t* reg)
{
    DBG_PRINTF("Check Go bit\n");
    int rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, reg);
    CHECK_RC(rc);
    int busy_bit = EXTRACT((*reg), busy_bit_offset, BUSY_BITLEN);
    return busy_bit;
}

static MError set_busy_bit(mfile* mf, u_int32_t* reg, int busy_bit_offset)
{
    *reg = MERGE(*reg, 1, busy_bit_offset, BUSY_BITLEN);
    return MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, *reg);
}

static MError get_syndrome(mfile* mf, u_int32_t* reg, int syndrome_bit_offset, int syndrome_bit_len)
{
    DBG_PRINTF("Reading syndrome from addr=0x%x\n", mf->icmd.syndrome_addr);
    int rc = MREAD4_ICMD(mf, mf->icmd.syndrome_addr, reg);
    CHECK_RC(rc);

    return EXTRACT((*reg), syndrome_bit_offset, syndrome_bit_len);
}

static int set_sleep()
{
    char* icmd_sleep_env;
    int   icmd_sleep = -1;

    if (increase_poll_time) {
        /* increase_poll_time is set by low_cpu flag. To reduce CPU utilization */
        icmd_sleep_env = "10\0";
    } else {
        icmd_sleep_env = getenv("MFT_CMD_SLEEP");
    }

    if (icmd_sleep_env) {
        char* endptr;
        icmd_sleep = strtol(icmd_sleep_env, &endptr, 10);
        if (*endptr != '\0') {
            icmd_sleep = -1;
        }
    }

    return icmd_sleep;
}

static int set_icmd_timeout()
{
    char* icmd_timeout_env;
    int   icmd_timeout = ICMD_DEFAULT_TIMEOUT;

    icmd_timeout_env = getenv("MFT_ICMD_TIMEOUT");

    if (icmd_timeout_env) {
        char* endptr;
        icmd_timeout = strtol(icmd_timeout_env, &endptr, 10);
        if ((endptr != NULL) && (*endptr != '\0')) {
            icmd_timeout = ICMD_DEFAULT_TIMEOUT;
        }
    }

    return icmd_timeout;
}

/*
 * get_status
 */
static int translate_status(int status)
{
    switch (status) {
    case 0x0:
        return ME_OK;

    case 0x1:
        return ME_ICMD_INVALID_OPCODE;

    case 0x2:
        return ME_ICMD_INVALID_CMD;

    case 0x3:
        return ME_ICMD_OPERATIONAL_ERROR;

    case 0x4:
        return ME_ICMD_BAD_PARAM;

    case 0x5:
        return ME_ICMD_BUSY;

    case 0x6:
        return ME_ICMD_ICM_NOT_AVAIL;

    case 0x7:
        return ME_ICMD_WRITE_PROTECT;

    default:
        return ME_ICMD_UNKNOWN_STATUS;
    }
}

static int translate_gbox_icmd_status(int status)
{
    switch (status) {
    case 0x0:
        return ME_OK;

    case 0x1:
        return ME_ERROR;

    case 0x2:
        return ME_UNKOWN_ACCESS_TYPE;

    case 0x3:
        return ME_ICMD_BAD_PARAM;

    case 0x6:
        return ME_TIMEOUT;

    case 0x7:
        return ME_ICMD_NOT_SUPPORTED;

    default:
        return ME_ICMD_UNKNOWN_STATUS;
    }
}

/*
 * set_and_poll_on_busy_bit - Sets the busy bit to 1, wait untill it is 0 again.
 */
static int set_and_poll_on_busy_bit(mfile* mf, int enhanced, int busy_bit_offset, u_int32_t* reg)
{
    u_int32_t busy;
    int       i, wait;
    MError    rc;

    /* set go bit */
    rc = set_busy_bit(mf, reg, busy_bit_offset);
    CHECK_RC(rc);
    DBG_PRINTF("Busy-bit raised. Waiting for command to exec...\n");

    /* set sleep time if needed */
    int icmd_sleep = set_sleep();
    int icmd_timeout = set_icmd_timeout();

    /* wait for command to execute */
    i = 0;
    wait = 1;
    do{
        if (++i > icmd_timeout) {
            /* this number of iterations should take ~~30sec, which is the defined command t/o */
            DBG_PRINTF("Execution timed-out\n");
            return ME_ICMD_STATUS_EXECUTE_TO;
        }

        if ((i < 100) || (i % 100 == 0)) {
            DBG_PRINTF("Waiting for busy-bit to clear (iteration #%d)...\n", i);
        }

        if (icmd_sleep > 0) {
            if (i == 3) {
                msleep(icmd_sleep);
            } else if (i > 3) {
                msleep(wait);
                if (wait < 8) {
                    wait *= 2; /* exponential backoff - up-to 8ms between polls */
                }
            }
            if (increase_poll_time) {
                /* adding msleep to reduce the CPU utilization (low_cpu flag) */
                msleep(10);
            }
        } else {
            if (!enhanced) {
                if (i > 5) {
                    /* after some iteration put sleeps between busy-wait */
                    msleep(wait); /* don't hog the cpu with busy-wait */
                    if (wait < 8) {
                        wait *= 2; /* exponential backoff - up-to 8ms between polls */
                    }
                }
            } else {
                mft_usleep(1);
            }
        }

        busy = check_busy_bit(mf, busy_bit_offset, reg);
    } while (busy);

    DBG_PRINTF("Command completed!\n");

    return ME_OK;
}

/*
 * set_opcode
 */
static int set_opcode(mfile* mf, u_int16_t opcode)
{
    u_int32_t reg = 0x0;
    u_int8_t  exmb = mf->icmd.dma_icmd;
    int       rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg);

    CHECK_RC(rc);

    reg = MERGE(reg, opcode, OPCODE_BITOFF, OPCODE_BITLEN);
    reg = MERGE(reg, exmb, EXMB_BITOFF, EXMB_BITLEN);
    rc = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, reg);

    CHECK_RC(rc);
    return ME_OK;
}

/*
 * icmd_is_cmd_ifc_ready
 */
static int icmd_is_cmd_ifc_ready(mfile* mf, int enhanced)
{
    u_int32_t reg = 0x0;

    if (!enhanced || (mf->icmd.icmd_ready == MTCR_STATUS_UNKNOWN)) {
        u_int32_t bit_val = 0;
        if (MREAD4(mf, mf->icmd.static_cfg_not_done_addr, &reg)) {
            return ME_ICMD_STATUS_CR_FAIL;
        }
        bit_val = EXTRACT(reg, mf->icmd.static_cfg_not_done_offs, 1);
        mf->icmd.icmd_ready = (bit_val == 0) ? MTCR_STATUS_TRUE : MTCR_STATUS_FALSE;
    }
    return (mf->icmd.icmd_ready == MTCR_STATUS_TRUE) ? ME_OK : ME_ICMD_STATUS_ICMD_NOT_READY;
}

#define SMP_ICMD_SEM_ADDR 0x0

static int icmd_clear_semaphore_com(mfile* mf)
{
#ifndef __FreeBSD__
    int      is_leaseable;
    u_int8_t lease_exp;
    if (((mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CIB) || (mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CX4)) &&
        mf->icmd.ib_semaphore_lock_supported) {
        if (!mf->icmd.lock_key) {
            return ME_OK;
        }
        DBG_PRINTF("VS_MAD SEM Release .. ");
        if (mib_semaphore_lock_vs_mad(mf, SMP_SEM_RELEASE, SMP_ICMD_SEM_ADDR, mf->icmd.lock_key, &(mf->icmd.lock_key),
                                      &is_leaseable, &lease_exp, SEM_LOCK_SET)) {
            DBG_PRINTF("Failed!\n");
            return ME_ICMD_STATUS_CR_FAIL;
        }
        if (mf->icmd.lock_key != 0) {
            return ME_ICMD_STATUS_CR_FAIL;
        }
        DBG_PRINTF("Succeeded!\n");
    } else
#endif
    {
        MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, 0);
    }
    mf->icmd.took_semaphore = 0;
    return ME_OK;
}

/*
 * icmd_clear_semaphore
 */
int icmd_clear_semaphore(mfile* mf)
{
    DBG_PRINTF("Clearing semaphore\n");
    /* open icmd interface by demand */
    int ret = icmd_open(mf);

    CHECK_RC(ret);
    return icmd_clear_semaphore_com(mf);
}

bool device_supports_sem_lock_verify(unsigned int hw_dev_id)
{
    switch (hw_dev_id)
    {
        case DeviceConnectX3_HwId:
        case DeviceConnectIB_HwId:
        case DeviceConnectX3Pro_HwId:
        case DeviceSwitchIB_HwId:
        case DeviceSpectrum_HwId:
        case DeviceConnectX4_HwId:
        case DeviceConnectX4LX_HwId:
        case DeviceConnectX5_HwId:
        case DeviceConnectX6_HwId:
        case DeviceConnectX6DX_HwId:
        case DeviceConnectX6LX_HwId:
        case DeviceConnectX7_HwId:
        case DeviceBlueField_HwId:
        case DeviceBlueField2_HwId:
        case DeviceBlueField3_HwId:
        case DeviceSwitchIB2_HwId:
        case DeviceQuantum_HwId:
        case DeviceQuantum2_HwId:
        case DeviceQuantum3_HwId:
        case DeviceGB100_HwId:
        case DeviceSpectrum2_HwId:
        case DeviceSpectrum3_HwId:
        case DeviceSpectrum4_HwId:
        case DeviceSpectrum5_HwId:
        case DeviceSpectrum6_HwId:
        case DeviceArcusE_HwId:
            return false;
    }
    return true;
}

static int icmd_take_semaphore_com(mfile* mf, u_int32_t expected_read_val)
{
    u_int32_t read_val = 0x0;
    unsigned  retries = 0;

    DBG_PRINTF("Taking semaphore...\n");
    do{ /* loop while the semaphore is taken by someone else */
        if (++retries > 256) {
            return ME_ICMD_STATUS_SEMAPHORE_TO;
        }
#ifndef __FreeBSD__
        int      is_leaseable;
        u_int8_t lease_exp;
        if (((mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CIB) || (mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CX4)) &&
            mf->icmd.ib_semaphore_lock_supported) {
            DBG_PRINTF("VS_MAD SEM LOCK .. ");
            read_val = mib_semaphore_lock_vs_mad(mf, SMP_SEM_LOCK, SMP_ICMD_SEM_ADDR, 0, &(mf->icmd.lock_key),
                                                 &is_leaseable, &lease_exp, SEM_LOCK_SET);
            if (read_val && (read_val != ME_MAD_BUSY)) {
                DBG_PRINTF("Failed!\n");
                return ME_ICMD_STATUS_ICMD_NOT_READY;
            }
            /* Fail to obtain the lock */
            if (mf->icmd.lock_key == 0) {
                read_val = 1;
            }
            DBG_PRINTF("Succeeded!\n");
        } else
#endif
        {
            if (mf->functional_vsec_supp)
            {
                DBG_PRINTF("ICMD_SEMAPHORE: Writing expected_read_val=0x%x to semaphore\n", expected_read_val);
                MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr,
                                  expected_read_val); // Attempt to take the semaphore by writing the PID
            }
            MREAD4_SEMAPHORE(mf, mf->icmd.semaphore_addr, &read_val);
            DBG_PRINTF("ICMD_SEMAPHORE: read_val=0x%x expected_read_val=0x%x\n", read_val, expected_read_val);
            if (read_val == expected_read_val) // Semaphore was free (PID if VSC, 0 if non-VSC)
            {
                if (!is_gw_access(mf))
                {
                    // Verify HW has set the semaphore to locked state
                    MREAD4_SEMAPHORE(mf, mf->icmd.semaphore_addr, &read_val);
                    if (read_val != SEMAPHORE_62_LOCKED_INDICATOR)
                    {
                        DBG_PRINTF("Failed to take ICMD semaphore (semaphore 62). "
                                   "Semaphore was free (0) but HW failed to set it to locked state when we took it."
                                   "This might indicate a FW or HW issue.\n");
                        if (device_supports_sem_lock_verify(mf->hw_dev_id))
                        {
                            return ME_ICMD_UNABLE_TO_TAKE_SEMAOHORE;
                        }
                    }
                }
                break;
            }
        }
        msleep(rand() % 50);
    } while (read_val != expected_read_val);

    mf->icmd.took_semaphore = 1;
    DBG_PRINTF("Semaphore taken successfully...\n");

    return ME_OK;
}

int icmd_take_semaphore(mfile* mf)
{
    /* open icmd interface by demand */
    int              ret;
    static u_int32_t pid = 0;

    ret = icmd_open(mf);
    CHECK_RC(ret);

    if (mf->functional_vsec_supp) {
        if (!pid) {
            pid = getpid();
        }
        return icmd_take_semaphore_com(mf, pid);
    } else {
        return icmd_take_semaphore_com(mf, 0);
    }
}

static int check_msg_size(mfile* mf, int write_data_size, int read_data_size)
{
    /* check data size does not exceed mailbox size */
    if ((write_data_size > (int)mf->icmd.max_cmd_size) || (read_data_size > (int)mf->icmd.max_cmd_size)) {
        DBG_PRINTF("write_data_size <%x-%x> mf->icmd.max_cmd_size .. ", write_data_size, mf->icmd.max_cmd_size);
        DBG_PRINTF("read_data_size <%x-%x> mf->icmd.max_cmd_size\n", read_data_size, mf->icmd.max_cmd_size);
        return ME_ICMD_SIZE_EXCEEDS_LIMIT;
    }
    return ME_OK;
}

static int icmd_send_command_com(mfile     * mf,
                                 IN int      opcode,
                                 INOUT void* data,
                                 IN int      write_data_size,
                                 IN int      read_data_size,
                                 IN int      skip_write,
                                 IN int      enhanced)
{
    int  ret;
    bool rollback_byte_order_conversion = false;

    /* open icmd interface by demand */
    ret = icmd_open(mf);
    CHECK_RC(ret);

    ret = check_msg_size(mf, write_data_size, read_data_size);
    CHECK_RC(ret);

    ret = icmd_is_cmd_ifc_ready(mf, enhanced);
    CHECK_RC(ret);
    if (!enhanced) {
        ret = icmd_take_semaphore(mf);
        CHECK_RC(ret);
    }

    ret = set_opcode(mf, opcode);
    CHECK_RC_GO_TO(ret, cleanup);

    if (!skip_write) {
        DBG_PRINTF("-D- Writing command to mailbox\n");
        if (mf->icmd.dma_icmd) {
            if (mtcr_memaccess(mf, 0, read_data_size, data, 1, MEM_ICMD)) {
                ret = ME_ICMD_STATUS_CR_FAIL;
                goto cleanup;
            }
        } else {
            rollback_byte_order_conversion = true; /* rollback byte order conversion on MWRITE_BUF_ICMD failure */
            MWRITE_BUF_ICMD(mf, mf->icmd.cmd_addr, data, write_data_size, ret = ME_ICMD_STATUS_CR_FAIL;
                            goto cleanup;
                            );
        }
    }

    if (mf->icmd.dma_icmd) {
        ret = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr + EXT_MBOX_DMA_OFF, EXTRACT64(mf->icmd.dma_pa, 32, 32));
        CHECK_RC(ret);
        ret = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr + EXT_MBOX_DMA_OFF + 4, EXTRACT64(mf->icmd.dma_pa, 0, 32));
        CHECK_RC(ret);
    }

    u_int32_t reg = 0x0;

    /* check go bit down */
    int busy_bit = check_busy_bit(mf, BUSY_BITOFF, &reg);
    ret = (busy_bit == BUSY_BIT_DOWN) ? ME_OK : ME_ICMD_STATUS_IFC_BUSY;
    CHECK_RC(ret);

    /* set go bit + poll + returned status */
    ret = set_and_poll_on_busy_bit(mf, enhanced, BUSY_BITOFF, &reg);
    CHECK_RC_GO_TO(ret, cleanup);

    /* get status */
    ret = translate_status(EXTRACT(reg, STATUS_BITOFF, STATUS_BITLEN));

    if (ret != ME_OK)
    {
        mf->icmd.syndrome = get_syndrome(mf, &reg, SYNDROME_BITOFF, SYNDROME_BITLEN);
    }

    CHECK_RC_GO_TO(ret, cleanup);

    DBG_PRINTF("-D- Reading command from mailbox");

    if (mf->icmd.dma_icmd) {
        if (mtcr_memaccess(mf, 0, read_data_size, data, 0, MEM_ICMD)) {
            ret = ME_ICMD_STATUS_CR_FAIL;
            goto cleanup;
        }
    } else {
        rollback_byte_order_conversion = false; /* MREAD_BUF_ICMD takes care of byte order conversion */
        MREAD_BUF_ICMD(mf, mf->icmd.cmd_addr, data, read_data_size, ret = ME_ICMD_STATUS_CR_FAIL;
                       goto cleanup;
                       );
    }

    ret = ME_OK;
cleanup:
    if (!enhanced) {
        (void)icmd_clear_semaphore(mf);
    }
    if (rollback_byte_order_conversion) {
        mtcr_fix_endianness((u_int32_t*)data, write_data_size);
    }
    return ret;
}

/*
 * set_gbox_gw_opcode_block
 */
static u_int32_t set_gbox_gw_opcode_block(u_int16_t opcode, int size)
{
    u_int32_t reg = 0x0;

    reg = MERGE(reg, (u_int32_t)(size / 4), GBOX_REG_ACC_W_SIZE_BITOFF, GBOX_REG_ACC_W_SIZE_BITLEN);
    reg = MERGE(reg, opcode, GBOX_OPCODE_BITOFF, GBOX_OPCODE_BITLEN);
    return reg;
}

static MError get_gbox_gw_start_addr(mfile* mf, u_int32_t* start_addr)
{
    /* get gbox_gw_start_addr by reading cr-space only once */
    if (gbox_gw_start_addr == 0xffff) {
        if (MREAD4(mf, CMD_PTR_ADDR_GBOX, &gbox_gw_start_addr)) {
            return ME_ICMD_STATUS_CR_FAIL;
        }
        /* no need to /4 */
        /* gw_addr = gw_addr >> 2; */
        *start_addr = gbox_gw_start_addr;
    }
    return ME_OK;
}

static int icmd_send_gbox_command_com(mfile     * mf,
                                      INOUT void* data,
                                      IN int      write_data_size,
                                      IN int      read_data_size,
                                      IN int      enhanced)
{
    int       ret;
    u_int32_t data_start_off = 0x0;
    u_int8_t  buffer[GBOX_MAX_DATA_SIZE + 4] = {0};
    u_int32_t reg = 0x0;

    if (mf->gb_info.gb_conn_type != GEARBPX_OVER_MTUSB) {
        /* wasn't supposed to get here */
        return ME_ERROR;
    }

    /* init icmd */
    ret = icmd_open(mf);
    CHECK_RC(ret);

    ret = check_msg_size(mf, write_data_size, read_data_size);
    CHECK_RC(ret);

    ret = icmd_is_cmd_ifc_ready(mf, enhanced);
    CHECK_RC(ret);
    if (!enhanced) {
        ret = icmd_take_semaphore(mf);
        CHECK_RC(ret);
    }

    /* check go bit down */
    ret = check_busy_bit(mf, GBOX_BUSY_BITOFF, &reg);
    CHECK_RC(ret);

    /* write to data request section */
    DBG_PRINTF("-D- Setting command GW");
    data_start_off = mf->gb_info.data_req_addr + GBOX_MAX_DATA_SIZE - write_data_size;
    MWRITE_BUF_ICMD(mf, data_start_off, data, write_data_size, ret = ME_ICMD_STATUS_CR_FAIL;
                    goto sem_cleanup;
                    );

    int orig_reg_size = write_data_size - 4;

    /* set opcode block - size is original register size = means without register vlock ()-4 bytes */
    reg = set_gbox_gw_opcode_block(GBOX_REG_ACCESS_CMD_OPCODE, orig_reg_size);

    /* set busy bit and write msg, than, poll + return status */
    ret = set_and_poll_on_busy_bit(mf, enhanced, GBOX_BUSY_BITOFF, &reg);
    CHECK_RC_GO_TO(ret, sem_cleanup);

    /* get status */
    ret = translate_gbox_icmd_status(EXTRACT(reg, GBOX_STATUS_BITOFF, GBOX_STATUS_BITLEN));
    CHECK_RC_GO_TO(ret, sem_cleanup);
    ret = EXTRACT(reg, GBOX_STATUS1_BITOFF, GBOX_STATUS1_BITLEN);

    /* read response */
    DBG_PRINTF("-D- Reading command from mailbox");
    /* no need to read size, it is the same (fw dont change this field) - uncommnet if logic will change */
    /* int read_size = EXTRACT(reg, GBOX_READ_SIZE_BITOFF, GBOX_READ_SIZE_BITLEN); */
    /* read_size = read_size * 4; */

    /* reset buffer */
    memset(buffer, 0, GBOX_MAX_DATA_SIZE);
    /* put register status in first 4 bytes */
    memcpy(buffer, &ret, 4);
    /* get response data (into buffer+4) */
    MREAD_BUF_ICMD(mf, mf->gb_info.data_res_addr, buffer + 4, orig_reg_size, ret = ME_ICMD_STATUS_CR_FAIL;
                   goto sem_cleanup;
                   );
    memcpy(data, buffer, read_data_size); /* read_data_size is same as orig size + 4 */

    ret = ME_OK;
sem_cleanup:
    if (!enhanced) {
        (void)icmd_clear_semaphore(mf);
    }
    return ret;
}

int icmd_send_command(mfile* mf, IN int opcode, INOUT void* data, IN int data_size, IN int skip_write)
{
    return icmd_send_command_int(mf, opcode, data, data_size, data_size, skip_write);
}

/*
 * icmd_send_command
 */
int icmd_send_command_int(mfile     * mf,
                          IN int      opcode,
                          INOUT void* data,
                          IN int      write_data_size,
                          IN int      read_data_size,
                          IN int      skip_write)
{
    if ((mf->gb_info.is_gb_mngr || mf->gb_info.is_gearbox) && (mf->gb_info.gb_conn_type == GEARBPX_OVER_MTUSB)) {
        return icmd_send_gbox_command_com(mf, data, write_data_size, read_data_size, 0);
    } else {
        return icmd_send_command_com(mf, opcode, data, write_data_size, read_data_size, skip_write, 0);
    }
}

int icmd_send_command_enhanced(mfile     * mf,
                               IN int      opcode,
                               INOUT void* data,
                               IN int      write_data_size,
                               IN int      read_data_size,
                               IN int      skip_write)
{
    if ((mf->gb_info.is_gb_mngr || mf->gb_info.is_gearbox) && (mf->gb_info.gb_conn_type == GEARBPX_OVER_MTUSB)) {
        return icmd_send_gbox_command_com(mf, data, write_data_size, read_data_size, 1);
    } else {
        return icmd_send_command_com(mf, opcode, data, write_data_size, read_data_size, skip_write, 1);
    }
}

static int icmd_init_cr(mfile* mf)
{
    int       icmd_ver;
    u_int32_t hcr_address;
    u_int32_t cmd_ptr_addr;
    u_int32_t reg = 0x0;
    u_int32_t hw_id = 0x0;
    mf->icmd.syndrome = 0;

#ifndef __FreeBSD__
    u_int32_t dev_type = 0;
#endif

    /* get device specific addresses */
    if (read_device_id(mf, &hw_id) != 4) {
        DBG_PRINTF("icmd_init_cr: failed to read device ID.\n");
        return ME_ICMD_NOT_SUPPORTED;
    }

    mf->icmd.cmd_ptr_bitlen = CMD_PTR_BITLEN;
    mf->icmd.version_bit_offset = ICMD_VERSION_BITOFF;
    switch (hw_id & 0xffff) {
    case (CIB_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CIB;
        hcr_address = HCR_ADDR_CIB;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CIB;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CIB;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (CX4LX_HW_ID):
    case (CX4_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX4;
        hcr_address = HCR_ADDR_CX4;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX4;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX4;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (CX5_HW_ID):
    case (BF_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX5;
        hcr_address = HCR_ADDR_CX5;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX5;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX5;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (SW_IB_HW_ID):
    case (SW_EN_HW_ID):
    case (SW_IB2_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_SW_IB;
        hcr_address = HCR_ADDR_SW_IB;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_SW_IB;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_SW_IB;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (QUANTUM_HW_ID):
    case (SPECTRUM2_HW_ID):
    case (SPECTRUM3_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_QUANTUM;
        hcr_address = HCR_ADDR_QUANTUM;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (QUANTUM2_HW_ID):
    case (SPECTRUM4_HW_ID):
    case (SPECTRUM5_HW_ID):
    case (SPECTRUM6_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_QUANTUM;
        hcr_address = HCR_ADDR_QUANTUM;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_QUANTUM2;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (QUANTUM3_HW_ID):
        cmd_ptr_addr = 0x200000;
        hcr_address = 0x200000;
        mf->icmd.semaphore_addr = 0x1550f8;
        mf->icmd.static_cfg_not_done_addr = 0x200010;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (GB100_HW_ID):
    case (GR100_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_GPU;
        hcr_address = HCR_ADDR_GPU;
        mf->icmd.semaphore_addr = hw_id == GR100_HW_ID ? SEMAPHORE_ADDR_GR100 : SEMAPHORE_ADDR_GPU;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_GPU;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        mf->icmd.cmd_ptr_bitlen = CMD_PTR_BITLEN_GPU;
        mf->icmd.version_bit_offset = ICMD_VERSION_BITOFF_GPU;
        break;

    case (CX6_HW_ID):
    case (CX6DX_HW_ID):
    case (CX6LX_HW_ID):
    case (BF2_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX5;
        hcr_address = HCR_ADDR_CX5;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX5;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX6;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5;
        break;

    case (CX7_HW_ID):
    case (BF3_HW_ID):
    case (BF4_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX7;
        hcr_address = HCR_ADDR_CX7;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX7;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX7;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX7;
        break;

    case (CX8_HW_ID):
    case (CX9_HW_ID):
    case (CX8_PURE_PCIE_SWITCH_HW_ID):
    case (CX9_PURE_PCIE_SWITCH_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX8;
        mf->icmd.cmd_ptr_bitlen = CMD_PTR_BITLEN_CX8;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX8;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX8;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX7;
        mf->icmd.version_bit_offset = CMD_PTR_BITLEN_CX8;
        mf->icmd.version_bitlen = ICMD_VERSION_BITLEN_CX8;
        hcr_address = CMD_PTR_ADDR_CX8; /* hcr_address is "version address" */
        break;

    case (AMOS_GBOX_HW_ID):
        mf->icmd.ctrl_addr = GBOX_MAX_DATA_SIZE;

        u_int32_t start_addr = 0x0;
        MError    rc = get_gbox_gw_start_addr(mf, &start_addr);
        if (rc) {
            return ME_ERROR;
        }

        mf->icmd.ctrl_addr += start_addr;
        mf->icmd.cmd_addr = start_addr + GBOX_GW_OPCODE_OFFSET;
        mf->gb_info.data_req_addr = start_addr + GBOX_GW_REQUEST_DATA_BLOCK_OFFSET;
        mf->gb_info.data_res_addr = start_addr + GBOX_GW_RESPONSE_DATA_BLOCK_OFFSET;

        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_GBOX;
        mf->icmd.static_cfg_not_done_addr = GBOX_STAT_CFG_NOT_DONE_ADDR;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5;
        mf->icmd.max_cmd_size = GBOX_MAX_DATA_SIZE;
        mf->icmd.icmd_opened = 1;

        return ME_OK;
        break;

    default:
        return ME_ICMD_NOT_SUPPORTED;
    }
    mf->icmd.max_cmd_size = ICMD_MAX_CMD_SIZE;
    icmd_ver = get_version(mf, hcr_address);
    /* get command and control addresses */
    switch (icmd_ver) {
    case 1:
        if (MREAD4(mf, cmd_ptr_addr, &reg)) {
            return ME_ICMD_STATUS_CR_FAIL;
        }

        mf->icmd.cmd_addr = EXTRACT(reg, CMD_PTR_BITOFF, mf->icmd.cmd_ptr_bitlen);
        mf->icmd.ctrl_addr = mf->icmd.cmd_addr + CTRL_OFFSET;
        mf->icmd.syndrome_addr = mf->icmd.cmd_addr + SYNDROME_OFFSET;
        DBG_PRINTF("-D- iCMD syndrom addr: 0x%x\n", mf->icmd.syndrome_addr);
        break;

    case ME_ICMD_STATUS_CR_FAIL:
        return ME_ICMD_STATUS_CR_FAIL;

    default:
        return ME_ICMD_UNSUPPORTED_ICMD_VERSION;
    }
    /* if IB check if we support locking via MAD */
#ifndef __FreeBSD__
    if (mget_mdevs_flags(mf, &dev_type)) {
        dev_type = 0;
    }
    if ((dev_type & MDEVS_IB) && (mib_semaphore_lock_is_supported(mf))) {
        mf->icmd.ib_semaphore_lock_supported = 1;
    }
#endif
    mf->icmd.icmd_opened = 1;
    return ME_OK;
}

static int icmd_init_vcr_crspace_addr(mfile* mf)
{
    u_int32_t hw_id = 0x0;

    /* get device specific addresses */
    if (read_device_id(mf, &hw_id) != 4) {
        return ME_ICMD_NOT_SUPPORTED;
    }

    switch (hw_id & 0xffff) {
    case (CIB_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CIB;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (CX4LX_HW_ID):
    case (CX4_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX4;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (CX5_HW_ID):
    case (BF_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX5;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CIB;
        break;

    case (SW_IB_HW_ID):
    case (SW_EN_HW_ID):
    case (SW_IB2_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_SW_IB;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (QUANTUM_HW_ID):
    case (SPECTRUM2_HW_ID):
    case (SPECTRUM3_HW_ID):
    case (QUANTUM2_HW_ID):
    case (QUANTUM3_HW_ID):
    case (GB100_HW_ID):
    case (SPECTRUM4_HW_ID):
    case (SPECTRUM5_HW_ID):
    case (SPECTRUM6_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (CX6_HW_ID):
    case (CX6DX_HW_ID):
    case (CX6LX_HW_ID):
    case (BF2_HW_ID):
    case (BF3_HW_ID):
    case (CX7_HW_ID):
    case (BF4_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX6;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5;     /* same bit offset as CX5 */
        break;

    case (CX8_HW_ID):
    case (CX8_PURE_PCIE_SWITCH_HW_ID):
    case (CX9_HW_ID):
    case (CX9_PURE_PCIE_SWITCH_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX8;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX7;
        break;

    case (AMOS_GBOX_HW_ID):
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX6;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5;     /* same bit offset as CX5 */
        break;

    default:
        return ME_ICMD_NOT_SUPPORTED;
    }
    return ME_OK;
}

static int icmd_init_vcr(mfile* mf)
{
    int              rc = ME_OK;
    static u_int32_t pid = 0;
    static u_int32_t size = 0;

    if (!pid) {
        pid = getpid();
    }

    mf->icmd.cmd_addr = VCR_CMD_ADDR;
    mf->icmd.ctrl_addr = VCR_CTRL_ADDR;
    mf->icmd.semaphore_addr = VCR_SEMAPHORE62;
    mf->icmd.syndrome_addr = VCR_SYNDROME_OFFSET;
    mf->icmd.syndrome = 0;
    DBG_PRINTF("-D- Getting VCR_CMD_SIZE_ADDR\n");

    rc = icmd_take_semaphore_com(mf, pid);
    CHECK_RC(rc);
    /* get max command size */
    rc = MREAD4_ICMD(mf, VCR_CMD_SIZE_ADDR, &mf->icmd.max_cmd_size);
    size = mf->icmd.max_cmd_size;
    icmd_clear_semaphore_com(mf);
    CHECK_RC(rc);
    /* adrianc: they should provide this bit as well in virtual cr-space atm get from cr-space */
    rc = icmd_take_semaphore_com(mf, pid);
    CHECK_RC(rc);
    rc = icmd_init_vcr_crspace_addr(mf);
    icmd_clear_semaphore_com(mf);
    CHECK_RC(rc);

    mf->icmd.icmd_opened = 1;
    DBG_PRINTF("-D- iCMD command addr: 0x%x\n", mf->icmd.cmd_addr);
    DBG_PRINTF("-D- iCMD ctrl addr: 0x%x\n", mf->icmd.ctrl_addr);
    DBG_PRINTF("-D- iCMD syndrom addr: 0x%x\n", mf->icmd.syndrome_addr);
    DBG_PRINTF("-D- iCMD semaphore addr(semaphore space): 0x%x\n", mf->icmd.semaphore_addr);
    DBG_PRINTF("-D- iCMD max mailbox size: 0x%x  size %d\n", mf->icmd.max_cmd_size, size);
    DBG_PRINTF("-D- iCMD stat_cfg_not_done addr: 0x%x:%d\n", mf->icmd.static_cfg_not_done_addr,
               mf->icmd.static_cfg_not_done_offs);
    return ME_OK;
}

void icmd_get_dma_support(mfile* mf)
{
    mf->icmd.dma_icmd = 0;
    mem_props_t mem_p;

    if (get_mem_props(mf, MEM_ICMD, &mem_p)) {
        return;
    }
    mf->icmd.dma_pa = mem_p.dma_pa;
    mf->icmd.dma_size = mem_p.mem_size;
    if (getenv("ENABLE_DMA_ICMD") == NULL) {
        return;
    }
    if (!mf->icmd.dma_pa) {
        return;
    }
    u_int8_t dev_cap_data[ICMD_QUERY_CAP_CMD_SZ] = {0};
    int      rc = icmd_send_command(mf, ICMD_QUERY_CAP_CMD_ID, dev_cap_data, ICMD_QUERY_CAP_CMD_SZ, 0);

    if (!rc) {
        mf->icmd.dma_icmd = pop_from_buff(dev_cap_data, ICMD_QUERY_CAP_EXMB_ICMD_OFF, 1);
    }
}

#ifndef __FreeBSD__
static int is_pci_device(mfile* mf)
{
    return (mf->flags & MDEVS_I2CM) || (mf->flags & (MDEVS_CABLE | MDEVS_LINKX_CHIP)) || (mf->flags & MDEVS_SOFTWARE);
}
#endif /* ifndef __FreeBSD__ */

int is_livefish_device(mfile* mf)
{
    if (!mf || !mf->dinfo) {
        return 0;
    }

    unsigned int hwdevid = 0;

    if (mf->tp == MST_SOFTWARE) {
        return 1;
    }
    int rc = read_device_id(mf, &hwdevid);

    if (rc == 4) {
        return ((!is_gpu_pci_device(mf->dinfo->pci.dev_id)) && (mf->dinfo->pci.dev_id == hwdevid));
    }
    return 0;
}

int icmd_open(mfile* mf)
{
    if (mf->icmd.icmd_opened) {
        return ME_OK;
    }

#ifndef __FreeBSD__
    /* Currently livefish check is supported for PCI devices & devices that map to CR. */
    /* ICMD is not supported while in livefish (GW is locked). */
    if ((is_pci_device(mf) || (mf->flags & MDEVS_TAVOR_CR)) && (is_livefish_device(mf) || is_zombiefish_device(mf))) {
        return ME_ICMD_NOT_SUPPORTED;
    }
#endif

    mf->icmd.took_semaphore = 0;
    mf->icmd.ib_semaphore_lock_supported = 0;
    /* attempt to open via CR-Space */
#if defined(MST_UL) && !defined(MST_UL_ICMD)
    if (mf->functional_vsec_supp) {
        return icmd_init_vcr(mf);
    }

#ifdef ENABLE_MST_DEV_I2C
    if (mf->tp == MST_DEV_I2C) {
        return icmd_init_cr(mf);
    }
#endif

    if ((mf->tp == MST_IB) || is_gpu_pci_device(mf->dinfo->pci.dev_id)) {
        return icmd_init_cr(mf);
    }
    return ME_ICMD_NOT_SUPPORTED;
#else
    /*if (mf->gb_info.is_gearbox){
     *   return icmd_init_cr(mf);
     *  }*/
    if (mf->functional_vsec_supp) {
        int rc = icmd_init_vcr(mf);
        if (rc == ME_OK) {
            icmd_get_dma_support(mf);
        }
        return rc;
    } else {
        return icmd_init_cr(mf);
    }

#endif
}

/*
 * icmd_close
 */
void icmd_close(mfile* mf)
{
    if (mf) {
        if (mf->icmd.took_semaphore) {
            if (icmd_clear_semaphore(mf)) {
                DBG_PRINTF("Failed to clear semaphore!\n");
            }
        }
        mf->icmd.icmd_opened = 0;
    }
}
