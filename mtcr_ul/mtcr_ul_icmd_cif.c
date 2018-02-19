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
#include <unistd.h>

#include <bit_slice.h>
#include <common/tools_utils.h>
#include "mtcr_icmd_cif.h"

#ifndef __FreeBSD__
#include "mtcr_ib_res_mgt.h"
#endif
//#define _DEBUG_MODE   // un-comment this to enable debug prints

#if !defined(__WIN__) && !defined(DISABLE_OFED) && !defined(__FreeBSD__) && !defined(NO_INBAND)
#include <dlfcn.h>
#include <infiniband/verbs.h>
#endif

// _DEBUG_MODE   // un-comment this to enable debug prints

#define IN
#define OUT
#define INOUT

#define STAT_CFG_NOT_DONE_ADDR_CIB   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_CX4   0xb0004
#define STAT_CFG_NOT_DONE_ADDR_SW_IB   0x80010
#define STAT_CFG_NOT_DONE_ADDR_QUANTUM   0x100010
#define STAT_CFG_NOT_DONE_ADDR_CX5   0xb5e04
#define STAT_CFG_NOT_DONE_BITOFF_CIB   31
#define STAT_CFG_NOT_DONE_BITOFF_CX4   31
#define STAT_CFG_NOT_DONE_BITOFF_SW_IB 0
#define STAT_CFG_NOT_DONE_BITOFF_CX5   31
#define STAT_CFG_NOT_DONE_BITOFF_CX5 31
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

#define EXT_MBOX_MKEY_OFF   0x8

struct dma_lib_hdl_t {
    void*               lib_handle;
#if !defined(__WIN__) && !defined(DISABLE_OFED) && !defined(__FreeBSD__) && !defined(NO_INBAND)
    struct ibv_device** (*ibv_get_device_list)(int *num_devices);
    const char *        (*ibv_get_device_name)(struct ibv_device *device);
    void                (*ibv_free_device_list)(struct ibv_device **list);
    struct ibv_context* (*ibv_open_device)(struct ibv_device *device);
    int                 (*ibv_close_device)(struct ibv_context *context);
    struct ibv_pd*      (*ibv_alloc_pd)(struct ibv_context *context);
    int                 (*ibv_dealloc_pd)(struct ibv_pd *pd);
    struct ibv_mr*      (*ibv_reg_mr)(struct ibv_pd *pd, void *addr, size_t length, int access);
    int                 (*ibv_dereg_mr)(struct ibv_mr *mr);

    struct ibv_device       **dev_list;
    struct ibv_context      *ib_ctx;
    struct ibv_pd           *pd;
    struct ibv_mr           *mr;
#endif
};

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
        DBG_PRINTF("-D- MWRITE4_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space);\
        if (mwrite4(mf, offset, value) != 4) {\
            mset_addr_space(mf, AS_CR_SPACE);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

#define MREAD4_ICMD(mf, offset, ptr, action_on_fail)\
    do {\
        SET_SPACE_FOR_ICMD_ACCESS(mf);\
        DBG_PRINTF("-D- MREAD4_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space);\
        if (mread4(mf, offset, ptr) != 4) {\
            RESTORE_SPACE(mf);\
            action_on_fail;\
        }\
        RESTORE_SPACE(mf);\
    }while(0)

#define MWRITE_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)\
    do {\
        if (mf->icmd.dma_mbox) { \
            memcpy(mf->icmd.dma_mbox, data, byte_len);\
        } else {\
            SET_SPACE_FOR_ICMD_ACCESS(mf);\
            DBG_PRINTF("-D- MWRITE_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space);\
            if ((unsigned)mwrite_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) {\
                RESTORE_SPACE(mf);\
                action_on_fail;\
            }\
            RESTORE_SPACE(mf);\
        }\
    }while(0)

#define MREAD_BUF_ICMD(mf, offset, data, byte_len, action_on_fail)\
    do {\
        if (mf->icmd.dma_mbox) { \
            memcpy(data, mf->icmd.dma_mbox, byte_len);\
        } else {\
            SET_SPACE_FOR_ICMD_ACCESS(mf);\
            DBG_PRINTF("-D- MREAD_BUF_ICMD: off: %x, addr_space: %x\n", offset, mf->address_space);\
            if ((unsigned)mread_buffer(mf, offset, data, byte_len) != (unsigned)byte_len) {\
                RESTORE_SPACE(mf);\
                action_on_fail;\
            }\
            RESTORE_SPACE(mf);\
        }\
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



#define DBG_PRINTF(...) if (getenv("MFT_DEBUG")) fprintf(stderr, __VA_ARGS__)


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
#define BF_HW_ID        529
#define SW_IB_HW_ID     583
#define SW_EN_HW_ID     585
#define SW_IB2_HW_ID    587
#define QUANTUM_HW_ID   589
#define SPECTRUM2_HW_ID 591

#define GET_ADDR(mf, addr_cib, addr_cx4, addr_sw_ib, addr_cx5, addr_quantum, addr)\
    do {\
        u_int32_t _hw_id = 0x0;\
        MREAD4((mf), (HW_ID_ADDR), &(_hw_id));\
        switch (_hw_id & 0xffff) {\
        case (CX4_HW_ID):\
        case (CX4LX_HW_ID):\
            addr = addr_cx4;\
            break;\
        case (SW_IB_HW_ID):\
        case (SW_EN_HW_ID):\
        case (SW_IB2_HW_ID):\
            addr = addr_sw_ib;\
            break;\
        case (QUANTUM_HW_ID):\
        case (SPECTRUM2_HW_ID):\
            addr = addr_quantum;\
            break;\
        case (CX5_HW_ID):\
        case (BF_HW_ID):\
            addr = addr_cx5;\
            break;\
        default:\
            addr = addr_cib;\
            break;\
        }\
	} while(0)

/*************************************************************************************/
/*
 * get_version
 */
static int get_version(mfile *mf, u_int32_t hcr_address) {
    u_int32_t reg = 0x0;
    if (MREAD4(mf, hcr_address, &reg)) return ME_ICMD_STATUS_CR_FAIL;
    reg = EXTRACT(reg, ICMD_VERSION_BITOFF, ICMD_VERSION_BITLEN);
    return reg;
}

/*
 * go - Sets the busy bit to 1, wait untill it is 0 again.
 */
static int go(mfile *mf) {
    u_int32_t reg = 0x0,
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
        if (++i > 5120) {  // this number of iterations should take ~~30sec, which is the defined command t/o
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
    u_int32_t reg = 0x0;
    u_int8_t exmb = (mf->icmd.dma_mbox != NULL) ? 1 : 0;
    MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
    reg = MERGE(reg, opcode, OPCODE_BITOFF, OPCODE_BITLEN);
    reg = MERGE(reg, exmb, EXMB_BITOFF, EXMB_BITLEN);
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
    u_int32_t reg = 0x0;

    MREAD4_ICMD(mf, mf->icmd.ctrl_addr, &reg, return ME_ICMD_STATUS_CR_FAIL);
    return translate_status(EXTRACT(reg, STATUS_BITOFF, STATUS_BITLEN));
}

/*
 * icmd_is_cmd_ifc_ready
 */
static int icmd_is_cmd_ifc_ready(mfile *mf) {
    u_int32_t reg = 0x0;
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
        //          CIB  CX4  SW-IB CX5
        GET_ADDR(mf, 0,   0,    0, 0, 0, expected_val); // we expect the bit_val to be : 0- CIB , 1- CX4/SWIB
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
        MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, 0, return ME_ICMD_STATUS_CR_FAIL);
    }
    mf->icmd.took_semaphore = 0;
    return ME_OK;
}

/*
 * icmd_take_semaphore
 */
static int icmd_take_semaphore_com(mfile *mf, u_int32_t expected_read_val)
{
    u_int32_t read_val = 0x0;
    unsigned retries = 0;

    DBG_PRINTF("Taking semaphore...\n");
     do {    // loop while the semaphore is taken by someone else
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
                 MWRITE4_SEMAPHORE(mf, mf->icmd.semaphore_addr, expected_read_val, return ME_ICMD_STATUS_CR_FAIL);
             }
             MREAD4_SEMAPHORE(mf, mf->icmd.semaphore_addr, &read_val, return ME_ICMD_STATUS_CR_FAIL);
             if (read_val == expected_read_val)
                 break;
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
        DBG_PRINTF("write_data_size <%x-%x> mf->icmd.max_cmd_size .. ", write_data_size, mf->icmd.max_cmd_size);
        DBG_PRINTF("read_data_size <%x-%x> mf->icmd.max_cmd_size \n", read_data_size, mf->icmd.max_cmd_size);
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

    if (mf->icmd.dma_icmd) {
        MWRITE4_ICMD(mf, mf->icmd.ctrl_addr + EXT_MBOX_MKEY_OFF, mf->icmd.mbox_mkey, return ME_ICMD_STATUS_CR_FAIL;);
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
    ret = icmd_clear_semaphore(mf);
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
        cmd_ptr_addr = CMD_PTR_ADDR_QUANTUM;
        hcr_address = HCR_ADDR_QUANTUM;
        mf->icmd.semaphore_addr = SEMAPHORE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_addr = STAT_CFG_NOT_DONE_ADDR_QUANTUM;
        mf->icmd.static_cfg_not_done_offs = STAT_CFG_NOT_DONE_BITOFF_SW_IB;
        break;
    default:
        return ME_ICMD_NOT_SUPPORTED;
    }
    mf->icmd.max_cmd_size = ICMD_MAX_CMD_SIZE;
    icmd_ver = get_version(mf, hcr_address);
    // get command and control addresses
    switch (icmd_ver) {
    case 1:
        if (MREAD4(mf, cmd_ptr_addr, &reg)){
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

#if !defined(__WIN__) && !defined(DISABLE_OFED) && !defined(__FreeBSD__) && !defined(NO_INBAND)
char* libs[] = {"libibverbs.so.1"};

#define MY_DLSYM(lib_ctx, func_name) do { \
      const char* dl_error; \
      lib_ctx->func_name = dlsym(lib_ctx->lib_handle, #func_name); \
      if ((dl_error = dlerror()) != NULL)  {\
          DBG_PRINTF("-E- %s", dl_error);\
          return ME_ERROR;\
      } \
} while(0)

static int init_lib_hdl(mfile* mf)
{
    unsigned i = 0;
    for (i = 0; i < sizeof(libs)/sizeof(libs[0]) ; i++) {
        mf->icmd.dma_lib_ctx->lib_handle = dlopen (libs[i], RTLD_LAZY);
        if (mf->icmd.dma_lib_ctx->lib_handle) {
            break;
        }
    }
    if (!mf->icmd.dma_lib_ctx->lib_handle) {
        DBG_PRINTF("-E- Ib verbs lib open failure: %s", dlerror());
        return ME_ERROR;
    }
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_get_device_list);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_get_device_name);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_free_device_list);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_open_device);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_close_device);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_alloc_pd);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_dealloc_pd);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_reg_mr);
    MY_DLSYM(mf->icmd.dma_lib_ctx, ibv_dereg_mr);
    return ME_OK;
}
#endif

static int mailbox_alloc(mfile* mf)
{
    TOOLS_UNUSED(mf);
#if !defined(__WIN__) && !defined(DISABLE_OFED) && !defined(__FreeBSD__) && !defined(NO_INBAND)
    size_t i;
    int num_devices = 0;
    int mr_flags = IBV_ACCESS_LOCAL_WRITE;
    struct ibv_device *ib_dev = 0;
    char ibdev_name[16] = {0};

    if (mf->dinfo->pci.ib_devs == NULL) {
        return ME_ERROR;
    }
    strncpy(ibdev_name, mf->dinfo->pci.ib_devs[0], sizeof(ibdev_name)/sizeof(ibdev_name[0]) - 1);
    if (posix_memalign ((void**)&(mf->icmd.dma_mbox), 0x1000, VCR_CMD_SIZE_ADDR)) {
        DBG_PRINTF("-E- Failed to align memory\n");
        return ME_MEM_ERROR;
    }
    if (!mf->icmd.dma_mbox) {
        DBG_PRINTF("-E- Failed to allocate mailbox\n");
        return ME_MEM_ERROR;
    }
    memset(mf->icmd.dma_mbox, 0, VCR_CMD_SIZE_ADDR);
    mf->icmd.dma_lib_ctx = malloc (sizeof(dma_lib_hdl));
    if (!mf->icmd.dma_lib_ctx) {
        free(mf->icmd.dma_mbox);
        DBG_PRINTF("-E- Failed to allocate lib hdl struct\n");
        return ME_MEM_ERROR;
    }
    memset(mf->icmd.dma_lib_ctx, 0, sizeof(dma_lib_hdl));
    if(init_lib_hdl(mf)) {
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        DBG_PRINTF("-E- Failed to initialize DMA functions\n");
        return ME_ERROR;
    }
    mf->icmd.dma_lib_ctx->dev_list = mf->icmd.dma_lib_ctx->ibv_get_device_list(&num_devices);
    if (!mf->icmd.dma_lib_ctx->dev_list) {
        DBG_PRINTF("-E- failed to get IB devices list\n");
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    /* if there isn't any IB device in host */
    if (!num_devices) {
        DBG_PRINTF("-E- found %d ib device(s)\n", num_devices);
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    for (i = 0; i < (size_t)num_devices; i ++) {
        if (!strcmp(mf->icmd.dma_lib_ctx->ibv_get_device_name(mf->icmd.dma_lib_ctx->dev_list[i]), ibdev_name))
        {
            ib_dev = mf->icmd.dma_lib_ctx->dev_list[i];
            break;
        }
    }

    if (!ib_dev) {
        DBG_PRINTF("-E- IB device %s wasn't found\n", ibdev_name);
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    mf->icmd.dma_lib_ctx->ib_ctx = mf->icmd.dma_lib_ctx->ibv_open_device(ib_dev);
    if (!mf->icmd.dma_lib_ctx->ib_ctx) {
        DBG_PRINTF("-E- failed to open IB device %s\n", ibdev_name);
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    mf->icmd.dma_lib_ctx->pd = mf->icmd.dma_lib_ctx->ibv_alloc_pd(mf->icmd.dma_lib_ctx->ib_ctx);
    if (!mf->icmd.dma_lib_ctx->pd) {
        DBG_PRINTF("-E- ibv_alloc_pd failed\n");
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    mf->icmd.dma_lib_ctx->mr = mf->icmd.dma_lib_ctx->ibv_reg_mr(mf->icmd.dma_lib_ctx->pd, mf->icmd.dma_mbox,
                                                                    VCR_CMD_SIZE_ADDR, mr_flags);
    if (!mf->icmd.dma_lib_ctx->mr) {
        DBG_PRINTF("-E- ibv_reg_mr failed with mr_flags=0x%x\n", mr_flags);
        free(mf->icmd.dma_lib_ctx);
        free(mf->icmd.dma_mbox);
        return ME_ERROR;
    }

    mf->icmd.mbox_mkey = mf->icmd.dma_lib_ctx->mr->lkey;
#endif
    return ME_OK;
}

static void mailbox_dealloc(mfile* mf)
{
    TOOLS_UNUSED(mf);
#if !defined(__WIN__) && !defined(DISABLE_OFED) && !defined(__FreeBSD__) && !defined(NO_INBAND)
    if (mf->icmd.dma_lib_ctx->dev_list && mf->icmd.dma_lib_ctx->ibv_free_device_list) {
        mf->icmd.dma_lib_ctx->ibv_free_device_list(mf->icmd.dma_lib_ctx->dev_list);
    }
    if (mf->icmd.dma_lib_ctx->mr && mf->icmd.dma_lib_ctx->ibv_dereg_mr) {
        mf->icmd.dma_lib_ctx->ibv_dereg_mr(mf->icmd.dma_lib_ctx->mr);
    }
    if (mf->icmd.dma_lib_ctx->pd && mf->icmd.dma_lib_ctx->ibv_dealloc_pd) {
        mf->icmd.dma_lib_ctx->ibv_dealloc_pd(mf->icmd.dma_lib_ctx->pd);
    }
    if (mf->icmd.dma_lib_ctx->ib_ctx && mf->icmd.dma_lib_ctx->ibv_close_device) {
    }
    if (mf->icmd.dma_lib_ctx->lib_handle) {
        dlclose(mf->icmd.dma_lib_ctx->lib_handle);
    }
    free(mf->icmd.dma_lib_ctx);
    free(mf->icmd.dma_mbox);
#endif
}

static int icmd_init_vcr(mfile* mf)
{
     mf->icmd.cmd_addr = VCR_CMD_ADDR;
     mf->icmd.ctrl_addr = VCR_CTRL_ADDR;
     mf->icmd.semaphore_addr = VCR_SEMAPHORE62;
     DBG_PRINTF("-D- Getting VCR_CMD_SIZE_ADDR\n");
     // get max command size
     MREAD4_ICMD(mf,VCR_CMD_SIZE_ADDR, &(mf->icmd.max_cmd_size), return ME_ICMD_STATUS_CR_FAIL;);

     // adrianc: they should provide this bit as well in virtual cr-space atm get from cr-space
     // macro is getting ugly as more devices are added...
     GET_ADDR(mf,STAT_CFG_NOT_DONE_ADDR_CIB, STAT_CFG_NOT_DONE_ADDR_CX4, STAT_CFG_NOT_DONE_ADDR_SW_IB, STAT_CFG_NOT_DONE_ADDR_CX5, STAT_CFG_NOT_DONE_ADDR_QUANTUM, mf->icmd.static_cfg_not_done_addr);
     GET_ADDR(mf, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_CIB, STAT_CFG_NOT_DONE_BITOFF_SW_IB, STAT_CFG_NOT_DONE_BITOFF_CX5, STAT_CFG_NOT_DONE_BITOFF_SW_IB, mf->icmd.static_cfg_not_done_offs);
     mf->icmd.icmd_opened = 1;
     DBG_PRINTF("-D- iCMD command addr: 0x%x\n", mf->icmd.cmd_addr);
     DBG_PRINTF("-D- iCMD ctrl addr: 0x%x\n", mf->icmd.ctrl_addr);
     DBG_PRINTF("-D- iCMD semaphore addr(semaphore space): 0x%x\n", mf->icmd.semaphore_addr);
     DBG_PRINTF("-D- iCMD max mailbox size: 0x%x\n", mf->icmd.max_cmd_size);
     DBG_PRINTF("-D- iCMD stat_cfg_not_done addr: 0x%x:%d\n", mf->icmd.static_cfg_not_done_addr, mf->icmd.static_cfg_not_done_offs);
     if (mf->icmd.dma_icmd) {
         if (mailbox_alloc(mf)) {
             mf->icmd.dma_icmd = 0;
             mf->icmd.dma_mbox = NULL;
             DBG_PRINTF("-W- Failed to allocate DMA mailbox\n");
         }
     }
     return ME_OK;
}


int icmd_open(mfile *mf)
{
    if (mf->icmd.icmd_opened) {
        return ME_OK;
    }

    mf->icmd.took_semaphore = 0;
    mf->icmd.ib_semaphore_lock_supported = 0;
    mf->icmd.dma_icmd = 0;
    if (getenv("ENABLE_DMA_ICMD")) {
        mf->icmd.dma_icmd = 1;
    }
    // attempt to open via CR-Space
#if defined(MST_UL) && !defined(MST_UL_ICMD)
    if (mf->vsec_supp) {
        return icmd_init_vcr(mf);
    }
    // ugly hack avoid compiler warrnings
    if (0) icmd_init_cr(mf);
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
        if (mf->icmd.took_semaphore) {
            if (icmd_clear_semaphore(mf)) {
                DBG_PRINTF("Failed to clear semaphore!\n");
            }
        }
        mf->icmd.icmd_opened = 0;
    }
    if (mf->icmd.dma_lib_ctx) {
        mailbox_dealloc(mf);
    }
}

