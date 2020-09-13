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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#if !defined(_MSC_VER)
#include <unistd.h>
#endif
#include <bit_slice.h>
//#include <common/tools_utils.h>
#include "mtcr_icmd_cif.h"
#include "packets_common.h"
#ifndef __FreeBSD__
#include "mtcr_ib_res_mgt.h"
#endif

#include "mtcr_mem_ops.h"

#define ICMD_QUERY_CAP_CMD_ID 0x8400
#define ICMD_QUERY_CAP_CMD_SZ 0x8
#define ICMD_QUERY_CAP_EXMB_ICMD_OFF 0x8

// _DEBUG_MODE   // un-comment this to enable debug prints


#define STAT_CFG_NOT_DONE_ADDR_CIB   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_CX4   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_SW_IB   0x80010
#define STAT_CFG_NOT_DONE_ADDR_QUANTUM   0x100010
#define STAT_CFG_NOT_DONE_ADDR_CX5   0xb5e04
#define STAT_CFG_NOT_DONE_ADDR_CX6   0xb5f04
#define STAT_CFG_NOT_DONE_BITOFF_CIB   31
#define STAT_CFG_NOT_DONE_BITOFF_CX4   31
#define STAT_CFG_NOT_DONE_BITOFF_SW_IB 0
#define STAT_CFG_NOT_DONE_BITOFF_CX5   31
#define SEMAPHORE_ADDR_CIB   0xe27f8 //sem62
#define SEMAPHORE_ADDR_CX4   0xe250c // sem67 bit31 is the semaphore bit here (only one semaphore in this dword)
#define SEMAPHORE_ADDR_SW_IB 0xa24f8 // sem 62
#define SEMAPHORE_ADDR_QUANTUM 0xa68f8
#define SEMAPHORE_ADDR_CX5   0xe74e0
#define HCR_ADDR_CIB         0x0
#define HCR_ADDR_CX4         HCR_ADDR_CIB
#define HCR_ADDR_CX5         HCR_ADDR_CIB
#define HCR_ADDR_SW_IB       0x80000
#define HCR_ADDR_QUANTUM       0x100000
#define ICMD_VERSION_BITOFF 24
#define ICMD_VERSION_BITLEN 8
#define CMD_PTR_ADDR_CIB        0x0
#define CMD_PTR_ADDR_SW_IB      0x80000
#define CMD_PTR_ADDR_QUANTUM      0x100000
#define CMD_PTR_ADDR_CX4        CMD_PTR_ADDR_CIB
#define CMD_PTR_ADDR_CX5        CMD_PTR_ADDR_CIB
#define CMD_PTR_BITOFF      0
#define CMD_PTR_BITLEN      24
#define CTRL_OFFSET         0x3fc
#define BUSY_BITOFF         0
#define BUSY_BITLEN         1
#define EXMB_BITOFF         1
#define EXMB_BITLEN         1
#define OPCODE_BITOFF       16
#define OPCODE_BITLEN       16
#define STATUS_BITOFF       8
#define STATUS_BITLEN       8
#define VCR_CTRL_ADDR       0x0
#define VCR_SEMAPHORE62     0x0 // semaphore Domain
#define VCR_CMD_ADDR        0x100000 // mailbox addr
#define VCR_CMD_SIZE_ADDR   0x1000 // mailbox size

#define EXT_MBOX_DMA_OFF    0x8

/*
 * General Macros
 */
#define CHECK_RC(rc) if ((rc)) {return (rc); }
#define CHECK_RC_GO_TO(rc, lable) if ((rc)) {goto lable; }
#define DBG_PRINTF(...) if (getenv("MFT_DEBUG")) {fprintf(stderr, __VA_ARGS__); }
/*
 * Macros for accessing CR-Space
 */
#define MWRITE_BUF(mf, offset, data, byte_len)                                             \
    (((unsigned)(mwrite_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))  \
     ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD_BUF(mf, offset, data, byte_len)                                              \
    (((unsigned)(mread_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))   \
     ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

#define MWRITE4(mf, offset, value)                             \
    (((unsigned)(mwrite4((mf), (offset), (value))) != 4U)      \
     ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD4(mf, offset, ptr)                                \
    (((unsigned)(mread4((mf), (offset), (ptr))) != 4U)         \
     ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

/*
 * Macros for accessing Icmd Space
 */
#define SET_SPACE_FOR_ICMD_ACCESS(mf)   \
    if (mf->vsec_supp) {               \
        mset_addr_space(mf, AS_ICMD);   \
    }
#define SET_SPACE_FOR_SEMAPHORE_ACCESS(mf)   \
    if (mf->vsec_supp) {               \
        mset_addr_space(mf, AS_SEMAPHORE);   \
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

#define MWRITE_BUF_ICMD(mf, offset, data, byte_len, action_on_fail) \
    do { \
        DBG_PRINTF("-D- MWRITE_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space); \
        SET_SPACE_FOR_ICMD_ACCESS(mf); \
        if ((unsigned)mwrite_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) { \
            RESTORE_SPACE(mf); \
            action_on_fail; \
        } \
        RESTORE_SPACE(mf); \
    } while (0)

#define MREAD_BUF_ICMD(mf, offset, data, byte_len, action_on_fail) \
    do { \
        DBG_PRINTF("-D- MREAD_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space); \
        SET_SPACE_FOR_ICMD_ACCESS(mf); \
        if ((unsigned)mread_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) { \
            RESTORE_SPACE(mf); \
            action_on_fail; \
        } \
        RESTORE_SPACE(mf); \
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
#define CX7_HW_ID       538
#define BF_HW_ID        529
#define BF2_HW_ID       532
#define SW_IB_HW_ID     583
#define SW_EN_HW_ID     585
#define SW_IB2_HW_ID    587
#define QUANTUM_HW_ID   589
#define SPECTRUM2_HW_ID 590
#define SPECTRUM3_HW_ID 592

/***** GLOBALS *****/
static int increase_poll_time = 0;
void  set_increase_poll_time(int new_value) { increase_poll_time = new_value; }
/***** GLOBALS *****/

/*************************************************************************************/
/*
 * get_version
 */
static int get_version(mfile *mf, u_int32_t hcr_address)
{
    u_int32_t reg = 0x0;
    if (MREAD4(mf, hcr_address, &reg)) {
        return ME_ICMD_STATUS_CR_FAIL;
    }
    reg = EXTRACT(reg, ICMD_VERSION_BITOFF, ICMD_VERSION_BITLEN);
    return reg;
}

/*
 * go - Sets the busy bit to 1, wait untill it is 0 again.
 */
static int go(mfile *mf)
{
    u_int32_t reg = 0x0, busy;
    int i, wait;

    DBG_PRINTF("Go()\n");

    int rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg);
    CHECK_RC(rc);
    busy = EXTRACT(reg, BUSY_BITOFF, BUSY_BITLEN);
    if (busy) {
        return ME_ICMD_STATUS_IFC_BUSY;
    }

    reg = MERGE(reg, 1, BUSY_BITOFF, BUSY_BITLEN);
    rc = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, reg);
    CHECK_RC(rc);

    DBG_PRINTF("Busy-bit raised. Waiting for command to exec...\n");
    char *icmd_sleep_env;
    if (increase_poll_time) {
        // increase_poll_time is set by low_cpu flag. To reduce CPU utilization
        icmd_sleep_env = "10\0";
    }
    else {
        icmd_sleep_env = getenv("MFT_CMD_SLEEP");
    }
    int icmd_sleep = -1;
    if (icmd_sleep_env) {
        char *endptr;
        icmd_sleep = strtol(icmd_sleep_env, &endptr, 10);
        if (*endptr != '\0') {
            icmd_sleep = -1;
        }
    }

    // wait for command to execute
    i = 0; wait = 1;
    do {
        if (++i > 5120) {
            // this number of iterations should take ~~30sec, which is the defined command t/o
            DBG_PRINTF("Execution timed-out\n");
            return ME_ICMD_STATUS_EXECUTE_TO;
        }

        DBG_PRINTF("Waiting for busy-bit to clear (iteration #%d)...\n", i);
        if (icmd_sleep > 0) {
            if (i == 3) {
                msleep(icmd_sleep);
            } else if (i > 3) {
                msleep(wait);
                if (wait < 8) {
                    wait *= 2;              // exponential backoff - up-to 8ms between polls
                }
            }
            if(increase_poll_time) {
                // adding msleep to reduce the CPU utilization (low_cpu flag)
                msleep(10);
            }
        } else {
            if (i > 5) {
                // after some iteration put sleeps bwtween busy-wait
                msleep(wait);  // don't hog the cpu with busy-wait
                if (wait < 8) {
                    wait *= 2;              // exponential backoff - up-to 8ms between polls
                }
            }
        }
        rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg);
        CHECK_RC(rc);
        busy = EXTRACT(reg, BUSY_BITOFF, BUSY_BITLEN);

    } while (busy);
    DBG_PRINTF("Command completed!\n");

    return ME_OK;
}

/*
 * set_opcode
 */
static int set_opcode(mfile *mf, u_int16_t opcode)
{
    u_int32_t reg = 0x0;
    u_int8_t exmb = mf->icmd.dma_icmd;
    int rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg);
    CHECK_RC(rc);
    reg = MERGE(reg, opcode, OPCODE_BITOFF, OPCODE_BITLEN);
    reg = MERGE(reg, exmb, EXMB_BITOFF, EXMB_BITLEN);
    rc = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, reg);
    CHECK_RC(rc);
    return ME_OK;
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
static int get_status(mfile *mf)
{
    u_int32_t reg = 0x0;
    int rc = MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg);
    CHECK_RC(rc);
    return translate_status(EXTRACT(reg, STATUS_BITOFF, STATUS_BITLEN));
}

/*
 * icmd_is_cmd_ifc_ready
 */
static int icmd_is_cmd_ifc_ready(mfile *mf)
{
    u_int32_t reg = 0x0;
    if (MREAD4(mf, mf->icmd.static_cfg_not_done_addr, &reg)) {
        return ME_ICMD_STATUS_CR_FAIL;
    }
    u_int32_t bit_val = EXTRACT(reg, mf->icmd.static_cfg_not_done_offs, 1);
    return (bit_val == 0) ?  ME_OK : ME_ICMD_STATUS_ICMD_NOT_READY;
}

#define SMP_ICMD_SEM_ADDR 0x0

static int icmd_clear_semaphore_com(mfile *mf)
{
#ifndef __FreeBSD__
    int is_leaseable;
    u_int8_t lease_exp;
    if ((mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CIB  ||
         mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CX4) &&
        mf->icmd.ib_semaphore_lock_supported) {
        if (!mf->icmd.lock_key) {
            return ME_OK;
        }
        DBG_PRINTF("VS_MAD SEM Release .. ");
        if (mib_semaphore_lock_vs_mad(mf, SMP_SEM_RELEASE, SMP_ICMD_SEM_ADDR, mf->icmd.lock_key,
                                      &(mf->icmd.lock_key), &is_leaseable, &lease_exp, SEM_LOCK_SET)) {
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
int icmd_clear_semaphore(mfile *mf)
{
    DBG_PRINTF("Clearing semaphore\n");
    // open icmd interface by demand
    int ret = icmd_open(mf);
    CHECK_RC(ret);
    return icmd_clear_semaphore_com(mf);
}

/*
 * icmd_take_semaphore
 */
/*
 * icmd_take_semaphore
 */

static int icmd_take_semaphore_com(mfile *mf, u_int32_t expected_read_val)
{
    u_int32_t read_val = 0x0;
    unsigned retries = 0;

    DBG_PRINTF("Taking semaphore...\n");
    do {     // loop while the semaphore is taken by someone else
        if (++retries > 256) {
            return ME_ICMD_STATUS_SEMAPHORE_TO;
        }
#ifndef __FreeBSD__
        int is_leaseable;
        u_int8_t lease_exp;
        if ((mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CIB  ||
             mf->icmd.semaphore_addr == SEMAPHORE_ADDR_CX4) &&
            mf->icmd.ib_semaphore_lock_supported) {
            DBG_PRINTF("VS_MAD SEM LOCK .. ");
            read_val = mib_semaphore_lock_vs_mad(mf, SMP_SEM_LOCK, SMP_ICMD_SEM_ADDR, 0,
                                                 &(mf->icmd.lock_key), &is_leaseable, &lease_exp, SEM_LOCK_SET);
            if (read_val && read_val != ME_MAD_BUSY) {
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
            if (mf->vsec_supp) {
                //write expected val before reading it
                MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, expected_read_val);
            }
            MREAD4_SEMAPHORE(mf, mf->icmd.semaphore_addr, &read_val);
            if (read_val == expected_read_val) {
                break;
            }
        }
        msleep(rand() % 20);
    } while (read_val != expected_read_val);

    mf->icmd.took_semaphore = 1;
    DBG_PRINTF("Semaphore taken successfully...\n");

    return ME_OK;
}

int icmd_take_semaphore(mfile *mf)
{
    // open icmd interface by demand
    int ret;
    static u_int32_t pid = 0;
    ret = icmd_open(mf);
    CHECK_RC(ret);

    if (mf->vsec_supp) {
        if (!pid) {
            pid = getpid();
        }
        return icmd_take_semaphore_com(mf, pid);
    } else {
        return icmd_take_semaphore_com(mf, 0);
    }
}

int icmd_send_command(mfile    *mf,
                      IN int opcode,
                      INOUT void *data,
                      IN int data_size,
                      IN int skip_write)
{
    return icmd_send_command_int(mf, opcode, data, data_size, data_size, skip_write);
}

/*
 * icmd_send_command
 */
int icmd_send_command_int(mfile    *mf,
                          IN int opcode,
                          INOUT void *data,
                          IN int write_data_size,
                          IN int read_data_size,
                          IN int skip_write)
{

    int ret;
    // open icmd interface by demand
    ret = icmd_open(mf);
    CHECK_RC(ret);
    // check data size does not exceed mailbox size
    if (write_data_size > (int)mf->icmd.max_cmd_size || \
        read_data_size > (int)mf->icmd.max_cmd_size) {
        DBG_PRINTF("write_data_size <%x-%x> mf->icmd.max_cmd_size .. ", write_data_size, mf->icmd.max_cmd_size);
        DBG_PRINTF("read_data_size <%x-%x> mf->icmd.max_cmd_size\n", read_data_size, mf->icmd.max_cmd_size);
        return ME_ICMD_SIZE_EXCEEDS_LIMIT;
    }

    ret = icmd_is_cmd_ifc_ready(mf);
    CHECK_RC(ret);

    ret = icmd_take_semaphore(mf);
    CHECK_RC(ret);

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
            MWRITE_BUF_ICMD(mf, mf->icmd.cmd_addr, data, write_data_size, ret = ME_ICMD_STATUS_CR_FAIL; goto cleanup;);
        }
    }

    if (mf->icmd.dma_icmd) {
        ret = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr + EXT_MBOX_DMA_OFF, EXTRACT64(mf->icmd.dma_pa, 32, 32));
        CHECK_RC(ret);
        ret = MWRITE4_ICMD(mf, mf->icmd.ctrl_addr + EXT_MBOX_DMA_OFF + 4, EXTRACT64(mf->icmd.dma_pa, 0, 32));
        CHECK_RC(ret);
    }

    ret = go(mf);
    CHECK_RC_GO_TO(ret, cleanup);

    ret = get_status(mf);
    CHECK_RC_GO_TO(ret, cleanup);

    DBG_PRINTF("-D- Reading command from mailbox");

    if (mf->icmd.dma_icmd) {
        if (mtcr_memaccess(mf, 0, read_data_size, data, 0, MEM_ICMD)) {
            ret = ME_ICMD_STATUS_CR_FAIL;
            goto cleanup;
        }
    } else {
        MREAD_BUF_ICMD(mf, mf->icmd.cmd_addr, data, read_data_size, ret = ME_ICMD_STATUS_CR_FAIL; goto cleanup;);
    }

    ret = ME_OK;
cleanup:
    (void) icmd_clear_semaphore(mf);
    return ret;
}


static int icmd_init_cr(mfile *mf)
{
    int icmd_ver;
    u_int32_t hcr_address;
    u_int32_t cmd_ptr_addr;
    u_int32_t reg = 0x0;
    u_int32_t hw_id = 0x0;
#ifndef __FreeBSD__
    u_int32_t dev_type = 0;
#endif

    // get device specific addresses
    MREAD4((mf), (HW_ID_ADDR), &(hw_id));
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

    case (CX6_HW_ID):
    case (CX6DX_HW_ID):
    case (CX6LX_HW_ID):
    case (BF2_HW_ID):
    case (CX7_HW_ID):
        cmd_ptr_addr = CMD_PTR_ADDR_CX5;
        hcr_address = HCR_ADDR_CX5;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_CX5;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX6;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5;
        break;

    default:
        return ME_ICMD_NOT_SUPPORTED;
    }
    mf->icmd.max_cmd_size = ICMD_MAX_CMD_SIZE;
    icmd_ver = get_version(mf, hcr_address);
    // get command and control addresses
    switch (icmd_ver) {
    case 1:
        if (MREAD4(mf, cmd_ptr_addr, &reg)) {
            return ME_ICMD_STATUS_CR_FAIL;
        }
        mf->icmd.cmd_addr  = EXTRACT(reg, CMD_PTR_BITOFF, CMD_PTR_BITLEN);
        mf->icmd.ctrl_addr = mf->icmd.cmd_addr + CTRL_OFFSET;
        break;

    case ME_ICMD_STATUS_CR_FAIL:
        return ME_ICMD_STATUS_CR_FAIL;

    default:
        return ME_ICMD_UNSUPPORTED_ICMD_VERSION;
    }
    // if IB check if we support locking via MAD
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

    // get device specific addresses
    MREAD4((mf), (HW_ID_ADDR), &(hw_id));
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
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;

    case (CX6_HW_ID):
    case (CX6DX_HW_ID):
    case (CX6LX_HW_ID):
    case (BF2_HW_ID):
    case (CX7_HW_ID):
            mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_CX6;
            mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_CX5; // same bit offset as CX5
            break;

    default:
        return ME_ICMD_NOT_SUPPORTED;
    }
    return ME_OK;
}

static int icmd_init_vcr(mfile *mf)
{
    int rc = ME_OK;
    static u_int32_t pid = 0;
    static u_int32_t size = 0;
    if (!pid) {
        pid = getpid();
    }

    mf->icmd.cmd_addr = VCR_CMD_ADDR;
    mf->icmd.ctrl_addr = VCR_CTRL_ADDR;
    mf->icmd.semaphore_addr = VCR_SEMAPHORE62;
    DBG_PRINTF("-D- Getting VCR_CMD_SIZE_ADDR\n");
    
    icmd_take_semaphore_com(mf, pid);
    // get max command size
    rc = MREAD4_ICMD(mf, VCR_CMD_SIZE_ADDR, &mf->icmd.max_cmd_size);
    size = mf->icmd.max_cmd_size;
    icmd_clear_semaphore_com(mf);
    CHECK_RC(rc);
    // adrianc: they should provide this bit as well in virtual cr-space atm get from cr-space
    icmd_take_semaphore_com(mf, pid);
    rc = icmd_init_vcr_crspace_addr(mf);
    icmd_clear_semaphore_com(mf);
    CHECK_RC(rc);

    mf->icmd.icmd_opened = 1;
    DBG_PRINTF("-D- iCMD command addr: 0x%x\n", mf->icmd.cmd_addr);
    DBG_PRINTF("-D- iCMD ctrl addr: 0x%x\n", mf->icmd.ctrl_addr);
    DBG_PRINTF("-D- iCMD semaphore addr(semaphore space): 0x%x\n", mf->icmd.semaphore_addr);
    DBG_PRINTF("-D- iCMD max mailbox size: 0x%x  size %d\n", mf->icmd.max_cmd_size, size);
    DBG_PRINTF("-D- iCMD stat_cfg_not_done addr: 0x%x:%d\n", mf->icmd.static_cfg_not_done_addr, mf->icmd.static_cfg_not_done_offs);
    return ME_OK;
}

void icmd_get_dma_support(mfile *mf)
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
    int rc = icmd_send_command(mf, ICMD_QUERY_CAP_CMD_ID, dev_cap_data, ICMD_QUERY_CAP_CMD_SZ, 0);
    if (!rc) {
        mf->icmd.dma_icmd = pop_from_buff(dev_cap_data, ICMD_QUERY_CAP_EXMB_ICMD_OFF, 1);
    }

}

int icmd_open(mfile *mf)
{
    if (mf->icmd.icmd_opened) {
        return ME_OK;
    }

    mf->icmd.took_semaphore = 0;
    mf->icmd.ib_semaphore_lock_supported = 0;
    // attempt to open via CR-Space
#if defined(MST_UL) && !defined(MST_UL_ICMD)
    if (mf->vsec_supp) {
        return icmd_init_vcr(mf);
    }
    // ugly hack avoid compiler warrnings
    if (0) {
        icmd_init_cr(mf);
    }
    return ME_ICMD_NOT_SUPPORTED;
#else
    if (mf->vsec_supp) {
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
void icmd_close(mfile *mf)
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

