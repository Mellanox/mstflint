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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <bit_slice.h>
#include <common/tools_utils.h>
#include "mtcr_icmd_cif.h"
#include "mtcr_ib_res_mgt.h"

//#define _DEBUG_MODE   // un-comment this to enable debug prints

#define IN
#define OUT
#define INOUT

#define STAT_CFG_NOT_DONE_ADDR_CIB   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_CX4   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_SW_IB   0x80010
#define STAT_CFG_NOT_DONE_BITOFF_CIB   31
#define STAT_CFG_NOT_DONE_BITOFF_CX4   31
#define STAT_CFG_NOT_DONE_BITOFF_SW_IB 0
#define BUSY_BITOFF         0
#define BUSY_BITLEN         1
#define OPCODE_BITOFF       16
#define OPCODE_BITLEN       16
#define STATUS_BITOFF       8
#define STATUS_BITLEN       8
#define VCR_CTRL_ADDR       0x0
#define VCR_SEMAPHORE62     0x0 // semaphore Domain
#define VCR_CMD_ADDR        0x100000 // mailbox addr
#define VCR_CMD_SIZE_ADDR   0x1000 // mailbox size

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

#define MWRITE4_ICMD(mf, offset, value, action_on_fail)\
    do {\
        SET_SPACE_FOR_ICMD_ACCESS(mf);\
        if (mwrite4(mf, offset, value) != 4) {\
            mset_addr_space(mf, AS_CR_SPACE);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

#define MREAD4_ICMD(mf, offset, ptr, action_on_fail)\
    do {\
        SET_SPACE_FOR_ICMD_ACCESS(mf);\
        if (mread4(mf, offset, ptr) != 4) {\
            RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

#define MWRITE_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)\
    do {\
        SET_SPACE_FOR_ICMD_ACCESS(mf);\
        if ((unsigned)mwrite_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) {\
            RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

#define MREAD_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)\
    do {\
        SET_SPACE_FOR_ICMD_ACCESS(mf);\
        if ((unsigned)mread_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) {\
            RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

/*
 * Macros for accessing semaphore space
 */
#define MWRITE4_SEMAPHORE(mf, offset, value, action_on_fail)\
        do {\
        SET_SPACE_FOR_SEMAPHORE_ACCESS(mf);\
        if (mwrite4(mf, offset, value) != 4) {\
           RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)


#define MREAD4_SEMAPHORE(mf, offset, ptr, action_on_fail)\
    do {\
        SET_SPACE_FOR_SEMAPHORE_ACCESS(mf);\
        if (mread4(mf, offset, ptr) != 4) {\
            RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)


#ifdef _DEBUG_MODE
#define DBG_PRINTF(...) fprintf(stderr, __VA_ARGS__)
#else
#define DBG_PRINTF(...)
#endif

enum {
    RW_READ  = 0x1,
    RW_WRITE = 0x0
};

/***********************************************
 *
 *  get correct addresses for : STAT_CCFG_NOT_DONE_ADDR, SEMAPHORE_ADDR, HCR_ADDR, CMD_PTR_ADDR
 *  according to Hw devid
 */

#define HW_ID_ADDR 0xf0014
#define CIB_HW_ID 511
#define CX4_HW_ID 521
#define CX4LX_HW_ID 523
#define CX5_HW_ID 525
#define SW_IB_HW_ID 583
#define SW_EN_HW_ID 585
#define SW_IB2_HW_ID 587

#define GET_ADDR(mf, addr_cib, addr_cx4, addr_sw_ib, addr)\
    do {\
        u_int32_t _hw_id;\
        MREAD4((mf), (HW_ID_ADDR), &(_hw_id));\
        switch (_hw_id & 0xffff) {\
        case (CX4_HW_ID):\
        case (CX4LX_HW_ID):\
        case (CX5_HW_ID):\
            addr = addr_cx4;\
            break;\
        case (SW_IB_HW_ID):\
        case (SW_EN_HW_ID):\
        case (SW_IB2_HW_ID):\
            addr = addr_sw_ib;\
            break;\
        default:\
            addr = addr_cib;\
            break;\
        }\
	} while(0)

/*
 * go - Sets the busy bit to 1, wait untill it is 0 again.
 */
static int go(mfile *mf) {
    u_int32_t reg,
              busy;
    int i, wait;

    DBG_PRINTF("Go()\n");

    MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
    busy = EXTRACT(reg, BUSY_BITOFF, BUSY_BITLEN);
    if (busy)
        return ME_ICMD_STATUS_IFC_BUSY;

    reg = MERGE(reg, 1, BUSY_BITOFF, BUSY_BITLEN);
    MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, reg, return ME_ICMD_STATUS_CR_FAIL);

    DBG_PRINTF("Busy-bit raised. Waiting for command to exec...\n");

    // wait for command to execute
    i = 0; wait = 1;
    do {
        if (++i > 1024) {  // this number of iterations should take ~~30sec, which is the defined command t/o
            DBG_PRINTF("Execution timed-out\n");
            return ME_ICMD_STATUS_EXECUTE_TO;
        }

        DBG_PRINTF("Waiting for busy-bit to clear (iteration #%d)...\n", i);

        if (i > 5) { // after some iteration put sleeps bwtween busy-wait
            msleep(wait);  // don't hog the cpu with busy-wait
            if (wait < 8) wait *= 2;    // exponential backoff - up-to 8ms between polls
        }
        MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
        busy = EXTRACT(reg, BUSY_BITOFF, BUSY_BITLEN);

    } while (busy);

    DBG_PRINTF("Command completed!\n");

    return ME_OK;
}

/*
 * set_opcode
 */
static int set_opcode(mfile *mf, u_int16_t opcode) {
    u_int32_t reg;

    MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
    reg = MERGE(reg, opcode, OPCODE_BITOFF, OPCODE_BITLEN);
    MWRITE4_ICMD(mf, mf->icmd.ctrl_addr, reg, return ME_ICMD_STATUS_CR_FAIL);

    return ME_OK;
}

/*
 * get_status
 */

static int translate_status(int status) {
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
static int get_status(mfile *mf) {
    u_int32_t reg;

    MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
    return translate_status(EXTRACT(reg, STATUS_BITOFF, STATUS_BITLEN));
}

/*
 * icmd_is_cmd_ifc_ready
 */
static int icmd_is_cmd_ifc_ready(mfile *mf) {
    u_int32_t reg;
    if (MREAD4(mf, mf->icmd.static_cfg_not_done_addr, &reg)) return ME_ICMD_STATUS_CR_FAIL;
    u_int32_t bit_val = EXTRACT(reg, mf->icmd.static_cfg_not_done_offs, 1);
    /* adrianc: for SWITCHIB the polarity of this bit is opposite than CONNECTIB/CONNECTX4
       i.e for CONNECTIB/CONNECTX4: this bit is 1 while fw is loading(indicating configuration is not done), then this bit is set to 0 by fw when the configurations
       are finished.
       for SWITCHIB: this bit indicates "configuration done" i.e when 0 the fw is not ready and when 1 we are ready*/
    // atm the polarity hasnt changed
    // ugly Hack to save code: we use the same macro as GET_ADDR (use a block to avoid compilation errors)
    u_int32_t expected_val;

    {
        //          CIB  CX4  SW-IB
        GET_ADDR(mf, 0,   0,    0, expected_val); // we expect the bit_val to be : 0- CIB , 1- CX4/SWIB
    }
    return (bit_val == expected_val) ?  ME_OK: ME_ICMD_STATUS_ICMD_NOT_READY;
}

#define SMP_ICMD_SEM_ADDR 0x0

/*
 * icmd_clear_semaphore
 */
int icmd_clear_semaphore(mfile *mf)
{
    DBG_PRINTF("Clearing semaphore\n");
    // open icmd interface by demand
    int ret;
    if ((ret = icmd_open(mf))) {
        return ret;
    }
    MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, 0, return ME_ICMD_STATUS_CR_FAIL);
    mf->icmd.took_semaphore = 0;
    return ME_OK;
}

/*
 * icmd_take_semaphore
 */

static int icmd_take_semaphore_com(mfile *mf, u_int32_t expected_read_val)
{
    u_int32_t read_val;
    unsigned retries = 0;

    DBG_PRINTF("Taking semaphore...\n");
     do {    // loop while the semaphore is taken by someone else
         if (++retries > 256) {
             return ME_ICMD_STATUS_SEMAPHORE_TO;
         }

         if (mf->vsec_supp) {
             //write expected val before reading it
             MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, expected_read_val, return ME_ICMD_STATUS_CR_FAIL);
         }
         MREAD4_SEMAPHORE(mf, mf->icmd.semaphore_addr, &read_val, return ME_ICMD_STATUS_CR_FAIL);
         if (read_val == expected_read_val)
             break;
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
    if ((ret = icmd_open(mf))) {
        return ret;
    }

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
                      IN    int     opcode,
                      INOUT void*   data,
                      IN    int     data_size,
                      IN    int     skip_write)
{
    return icmd_send_command_int(mf, opcode, data, data_size, data_size, skip_write);
}

/*
 * icmd_send_command
 */
int icmd_send_command_int(mfile    *mf,
                      IN    int     opcode,
                      INOUT void*   data,
                      IN    int     write_data_size,
                      IN    int     read_data_size,
                      IN    int     skip_write)
{

    int ret;
    // open icmd interface by demand
    if ((ret = icmd_open(mf))) {
        return ret;
    }
    // check data size does not exceed mailbox size
    if (write_data_size > (int)mf->icmd.max_cmd_size || \
         read_data_size > (int)mf->icmd.max_cmd_size ) {
        return ME_ICMD_SIZE_EXCEEDS_LIMIT;
    }

    if ((ret = icmd_is_cmd_ifc_ready(mf)))
    {
        return ret;
    }

    if ((ret = icmd_take_semaphore(mf))) {
        return ret;
    }

    if ((ret = set_opcode(mf, opcode))) {
        goto cleanup;
    }

    if (!skip_write)
    {
        DBG_PRINTF("-D- Writing command to mailbox");
        MWRITE_BUF_ICMD(mf, mf->icmd.cmd_addr, data, write_data_size, ret=ME_ICMD_STATUS_CR_FAIL; goto cleanup;);
    }

    if ((ret = go(mf))) {
        goto cleanup;
    }

    if ((ret = get_status(mf))) {
        goto cleanup;
    }
    DBG_PRINTF("-D- Reading command from mailbox");
    MREAD_BUF_ICMD(mf, mf->icmd.cmd_addr, data, read_data_size, ret=ME_ICMD_STATUS_CR_FAIL; goto cleanup;);

    ret = ME_OK;
cleanup:
    icmd_clear_semaphore(mf);
    return ret;
}

static int icmd_init_vcr(mfile* mf)
{
     mf->icmd.cmd_addr = VCR_CMD_ADDR;
     mf->icmd.ctrl_addr = VCR_CTRL_ADDR;
     mf->icmd.semaphore_addr = VCR_SEMAPHORE62;

     // get max command size
     MREAD4_ICMD(mf,VCR_CMD_SIZE_ADDR, &(mf->icmd.max_cmd_size), return ME_ICMD_STATUS_CR_FAIL;);

     // adrianc: they should provide this bit as well in virtual cr-space atm get from cr-space
     GET_ADDR(mf,STAT_CFG_NOT_DONE_ADDR_CIB, STAT_CFG_NOT_DONE_ADDR_CX4, STAT_CFG_NOT_DONE_ADDR_SW_IB, mf->icmd.static_cfg_not_done_addr);
     GET_ADDR(mf, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_SW_IB, mf->icmd.static_cfg_not_done_offs);
     mf->icmd.icmd_opened = 1;
     DBG_PRINTF("-D- iCMD command addr: 0x%x\n", mf->icmd.cmd_addr);
     DBG_PRINTF("-D- iCMD ctrl addr: 0x%x\n", mf->icmd.ctrl_addr);
     DBG_PRINTF("-D- iCMD semaphore addr(semaphore space): 0x%x\n", mf->icmd.semaphore_addr);
     DBG_PRINTF("-D- iCMD max mailbox size: 0x%x\n", mf->icmd.max_cmd_size);
     DBG_PRINTF("-D- iCMD stat_cfg_not_done addr: 0x%x:%d\n", mf->icmd.static_cfg_not_done_addr, mf->icmd.static_cfg_not_done_offs);
     return ME_OK;
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
    return ME_ICMD_NOT_SUPPORTED;
#else
    if (mf->vsec_supp) {
        return icmd_init_vcr(mf);
    } else {
        return icmd_init_cr(mf);
    }
#endif
}

/*
 * icmd_close
 */
void icmd_close(mfile *mf) {
    if (mf) {
        if (mf->icmd.took_semaphore)
            icmd_clear_semaphore(mf);
        mf->icmd.icmd_opened = 0;
    }
}

