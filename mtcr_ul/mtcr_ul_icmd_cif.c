
/*
               - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bit_slice.h>
#include <common/tools_utils.h>
#include "mtcr_icmd_cif.h"

//#define _DEBUG_MODE   // un-comment this to enable debug prints

#define IN
#define OUT
#define INOUT

#define STAT_CFG_NOT_DONE_ADDR_CIB   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_CX4   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_SW_IB   0x80010
#define STAT_CFG_NOT_DONE_BITOFF_CIB 31
#define STAT_CFG_NOT_DONE_BITOFF_CX4 31
#define STAT_CFG_NOT_DONE_BITOFF_SW_IB 0
#define BUSY_BITOFF         0
#define BUSY_BITLEN         1
#define OPCODE_BITOFF       16
#define OPCODE_BITLEN       16
#define STATUS_BITOFF       8
#define STATUS_BITLEN       8

/*
 * Virtual CR-Space ICMD addresses
 */

#define VCR_CTRL_ADDR   0x6404010
#define VCR_SEMAPHORE62 0x6406000
#define VCR_CAP_ADDR    0x6405000
#define VCR_MODE_ADDR   0x6405008
#define VCR_MAGIC_PAT   "virtiCMD"
#define VCR_CMD_ADDR   0x6400000
#define VCR_CMD_SIZE   0x4000



#define MWRITE_BUF(mf, offset, data, byte_len)                                             \
    (((unsigned)(mwrite_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))  \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD_BUF(mf, offset, data, byte_len)                                              \
    (((unsigned)(mread_buffer((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))   \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

#define MWRITE4_BLOCK(mf, offset, data, byte_len)                                             \
    (((unsigned)(mwrite4_block((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))  \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD4_BLOCK(mf, offset, data, byte_len)                                              \
    (((unsigned)(mread4_block((mf), (offset), (data), (byte_len))) != (unsigned)(byte_len))   \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

#define MWRITE4(mf, offset, value)                             \
    (((unsigned)(mwrite4((mf), (offset), (value))) != 4U)      \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)
#define MREAD4(mf, offset, ptr)                                \
    (((unsigned)(mread4((mf), (offset), (ptr))) != 4U)         \
        ? ME_ICMD_STATUS_CR_FAIL : ME_OK)

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
#define SW_IB_HW_ID 583
#define SW_EN_HW_ID 585

#define GET_ADDR(mf, addr_cib, addr_cx4, addr_sw_ib, addr)\
    do {\
        u_int32_t _hw_id;\
        MREAD4((mf), (HW_ID_ADDR), &(_hw_id));\
        switch (_hw_id & 0xffff) {\
        case (CX4_HW_ID):\
            addr = addr_cx4;\
            break;\
        case (SW_IB_HW_ID):\
        case (SW_EN_HW_ID):\
            addr = addr_sw_ib;\
            break;\
        default:\
            addr = addr_cib;\
            break;\
        }\
	} while(0)

/*************************************************************************************/

/*
 * go - Sets the busy bit to 1, wait untill it is 0 again.
 */
static int go(mfile *mf) {
    u_int32_t reg,
              busy;
    int i, wait;

    DBG_PRINTF("Go()\n");

    if (MREAD4(mf, mf->icmd.ctrl_addr, &reg)) return ME_ICMD_STATUS_CR_FAIL;
    busy = EXTRACT(reg, BUSY_BITOFF, BUSY_BITLEN);
    if (busy)
        return ME_ICMD_STATUS_IFC_BUSY;

    reg = MERGE(reg, 1, BUSY_BITOFF, BUSY_BITLEN);
    if (MWRITE4(mf, mf->icmd.ctrl_addr, reg)) return ME_ICMD_STATUS_CR_FAIL;

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
        if (MREAD4(mf, mf->icmd.ctrl_addr, &reg)) return ME_ICMD_STATUS_CR_FAIL;
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

    if (MREAD4(mf, mf->icmd.ctrl_addr, &reg)) return ME_ICMD_STATUS_CR_FAIL;
    reg = MERGE(reg, opcode, OPCODE_BITOFF, OPCODE_BITLEN);
    if (MWRITE4(mf, mf->icmd.ctrl_addr, reg)) return ME_ICMD_STATUS_CR_FAIL;

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

    if (MREAD4(mf, mf->icmd.ctrl_addr, &reg)) return ME_ICMD_STATUS_CR_FAIL;
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

/*
 * icmd_clear_semaphore
 */
int icmd_clear_semaphore(mfile *mf) {
    DBG_PRINTF("Clearing semaphore\n");
    // open icmd interface by demand
	int ret;
	if ((ret = icmd_open(mf))) {
		return ret;
	}

    if (MWRITE4(mf, mf->icmd.semaphore_addr, 0)) return ME_ICMD_STATUS_CR_FAIL;
    mf->icmd.took_semaphore = 0;
    return ME_OK;
}

/*
 * icmd_take_semaphore
 */
int icmd_take_semaphore(mfile *mf) {
	// open icmd interface by demand
	int ret;
	if ((ret = icmd_open(mf))) {
		return ret;
	}
    u_int32_t r;
    unsigned retries = 0;

    DBG_PRINTF("Taking semaphore...\n");

    do {    // loop while the semaphore is taken by someone else
        if (++retries > 256) {
            return ME_ICMD_STATUS_SEMAPHORE_TO;
        }
        if (MREAD4(mf, mf->icmd.semaphore_addr, &r)) return ME_ICMD_STATUS_CR_FAIL;
        if (! r)
            break;
        msleep(rand() % 20);
    } while (r);

    mf->icmd.took_semaphore = 1;
    DBG_PRINTF("Semaphore taken successfully...\n");

    return ME_OK;
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
        if ((ret = MWRITE_BUF(mf, mf->icmd.cmd_addr, data, write_data_size))) {
            goto cleanup;
        }
    }

    if ((ret = go(mf))) {
        goto cleanup;
    }

    if ((ret = get_status(mf))) {
        goto cleanup;
    }

    if ((ret = MREAD_BUF(mf, mf->icmd.cmd_addr, data, read_data_size))) {
        goto cleanup;
    }

    ret = ME_OK;
cleanup:
    icmd_clear_semaphore(mf);
    return ret;
}

static int icmd_init_vcr(mfile* mf)
{
    // check signature
     char sig[sizeof(VCR_MAGIC_PAT) + 1] = {0};
     if (mread_buffer(mf, VCR_CAP_ADDR, (u_int8_t*)sig, 4) != 4) {
         return ME_CR_ERROR;
     }

     if (strncmp(VCR_MAGIC_PAT, sig, sizeof(VCR_MAGIC_PAT))) {
         return ME_ICMD_BAD_SIGNATURE;
     }
     // we support iCMD via virtual cr-space , update addressess accordingly
     mf->icmd.cmd_addr = VCR_CMD_ADDR;
     mf->icmd.ctrl_addr = VCR_CTRL_ADDR;
     mf->icmd.semaphore_addr = VCR_SEMAPHORE62;
     // adrianc: they should provide this bit as well in virtual cr-space atm get from cr-space
     GET_ADDR(mf,STAT_CFG_NOT_DONE_ADDR_CIB, STAT_CFG_NOT_DONE_ADDR_CX4, STAT_CFG_NOT_DONE_ADDR_SW_IB, mf->icmd.static_cfg_not_done_addr);
     GET_ADDR(mf, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_SW_IB, mf->icmd.static_cfg_not_done_offs);
     mf->icmd.icmd_opened = 1;
     return ME_OK;
}

int icmd_open(mfile *mf)
{
    u_int32_t access_type;
    int ret;

    if (mf->icmd.icmd_opened) {
        return ME_OK;
    }
    mf->icmd.took_semaphore = 0;
    // check if we support icmd in virtual CR-Space
    if (mget_mdevs_type(mf, &access_type)) {
        return ME_ICMD_BAD_PARAM;
    }

    if (access_type == MTCR_ACCESS_CONFIG) {
        // check signature
        ret = icmd_init_vcr(mf);
        if (ret != ME_ICMD_BAD_SIGNATURE) {
            return ret;
        }
    }
    return ME_ICMD_NOT_SUPPORTED;
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

