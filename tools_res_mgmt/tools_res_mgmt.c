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

#include <stdlib.h>

#include <common/tools_utils.h>
#include <common/bit_slice.h>
#include <common/compatibility.h>
#include <dev_mgt/tools_dev_types.h>
#include "tools_res_mgmt.h"

#ifdef __WIN__
#include <process.h>
#define getpid() _getpid()
#endif

#define VSEC_SEM_NUM 10
#define HW_SEM_NUM VSEC_SEM_NUM

/*
 * Macros:
 */

/*
 * VSEC semaphore space macros
 */

#define SET_SPACE_FOR_SEMAPHORE_ACCESS(mf)   \
    if (mget_vsec_supp(mf)) {               \
        mset_addr_space(mf, AS_SEMAPHORE);   \
    }

#define RESTORE_SPACE(mf) mset_addr_space(mf, AS_CR_SPACE)

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

/***********************/

static const char* status_to_str[] =
{
        "Ok",
        "Resource is busy",
        "Tools resource management interface not available",
        "Device not supported",
        "Resource not supported",
        "CR-Space access error"
};

struct device_sem_info
{
    dm_dev_id_t dev_id;
    u_int32_t hw_sem_addr[HW_SEM_NUM]; // if semaphore entry supported: value != 0 , main semaphore is at [0]
    int vsec_sem_supported;
};

static u_int32_t g_vsec_sem_addr[VSEC_SEM_NUM] = {0x0, 0x10};

#define HW_SEM_ADDR_MASK 0xf

static struct device_sem_info g_dev_sem_info_db[] = {
        {
                DeviceConnectX,             // dev_id
                {0xf03bc},                  // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceConnectX2,            // dev_id
                {0xf03bc},                  // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceConnectX3,            // dev_id
                {0xf03bc, 0xf03a0},         // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceConnectX3Pro,         // dev_id
                {0xf03bc, 0xf03a0},         // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceInfiniScaleIV,        // dev_id
                {0},                        // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceSwitchX,              // dev_id
                {0},                        // hw_sem_addr
                0,                          // vsec_sem_supported
        },
        {
                DeviceConnectIB, // dev_id
                {0xe27f8},       // hw_sem_addr
                1,               // vsec_sem_supported
        },
        {
                DeviceConnectX4, // dev_id
                {0xe250c},       // hw_sem_addr
                1,               // vsec_sem_supported
        },
        {
                DeviceSwitchIB,  // dev_id
                {0xa24f8},       // hw_sem_addr
                0,               // vsec_sem_supported
        },
        {
                DeviceSpectrum,  // dev_id
                {0xa24f8},       // hw_sem_addr
                0,               // vsec_sem_supported
        },
        {
                DeviceConnectX4LX, // dev_id
                {0xe250c},       // hw_sem_addr
                1,               // vsec_sem_supported
        },
};

/************************************
 * Function: lock_hw_semaphore
 ************************************/
static trm_sts lock_hw_semaphore(mfile* mf, u_int32_t addr, unsigned int max_retries)
{
    u_int32_t val;
    unsigned int cnt = 0;
    int rc;

    while (((rc = mread4(mf, addr, &val)) == 4) && val == 1 && cnt < max_retries) {
        cnt ++;
        msleep(((rand() % 5) + 1));
    }

    if (rc != 4) {
        return TRM_STS_CR_ACCESS_ERR;
    } else if (val == 0) {
        return TRM_STS_OK;
    } else {
        return TRM_STS_RES_BUSY;
    }
}

/************************************
 * Function: unlock_hw_semaphore
 ************************************/
static trm_sts unlock_hw_semaphore(mfile* mf, u_int32_t addr)
{
    int rc = mwrite4(mf, addr, 0) == 4 ? TRM_STS_OK : TRM_STS_CR_ACCESS_ERR;
    // give up the rest of the time slice
    msleep(0);
    return rc;
}

/************************************
 * Function: lock_vsec_semaphore()
 ************************************/
static trm_sts lock_vsec_semaphore(mfile* mf, u_int32_t addr, unsigned int max_retries)
{
    static u_int32_t pid = 0;
    u_int32_t read_val;
    unsigned cnt = 0;

    if (!pid) {
        pid = getpid();
    }
    do {    // loop while the semaphore is taken by someone else
        if (cnt++ > max_retries) {
            return TRM_STS_RES_BUSY;
        }
        //write pid to semaphore
        MWRITE4_SEMAPHORE(mf, addr, pid, return TRM_STS_CR_ACCESS_ERR);
        // Read back
        MREAD4_SEMAPHORE(mf, addr, &read_val, return TRM_STS_CR_ACCESS_ERR);
        if (read_val == pid)
            break;
        msleep(((rand() % 5) + 1));
    } while (read_val != pid);
    return TRM_STS_OK;
}

/************************************
 * Function: unlock_vsec_semaphore()
 ************************************/
static trm_sts unlock_vsec_semaphore(mfile* mf, u_int32_t addr)
{
    MWRITE4_SEMAPHORE(mf, addr, 0, return TRM_STS_CR_ACCESS_ERR);
    return TRM_STS_OK;
}

/************************************
 * Function: get_device_sem_info
 ************************************/
static struct device_sem_info* get_device_sem_info(dm_dev_id_t dev_id)
{
    size_t i;
    for (i = 0; i < sizeof(g_dev_sem_info_db)/sizeof(g_dev_sem_info_db[0]); i++) {
        if (g_dev_sem_info_db[i].dev_id == dev_id) {
            return &g_dev_sem_info_db[i];
        }
    }

    return NULL;
}

/************************************
 * Function: trm_lock
 ************************************/
trm_sts trm_lock(mfile* mf, trm_resourse res, unsigned int max_retries)
{
    dm_dev_id_t dev_id;
    u_int32_t hw_dev_id;
    u_int32_t chip_rev;
    struct device_sem_info* dev_sem_info;

    if (dm_get_device_id(mf, &dev_id, &hw_dev_id, &chip_rev)) {
        return TRM_STS_CR_ACCESS_ERR;
    }

    dev_sem_info = get_device_sem_info(dev_id);

    // Not supported device
    if (!dev_sem_info) {
        return TRM_STS_DEV_NOT_SUPPORTED;
    }

    // lock resource on appropriate ifc if supported
    switch ((int)res) {
    case TRM_RES_ICMD:
        if (dev_sem_info->vsec_sem_supported && mget_vsec_supp(mf)) {
            return lock_vsec_semaphore(mf, g_vsec_sem_addr[TRM_RES_ICMD], max_retries);
        } else if (dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return lock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK], max_retries);
        }
        break;
    case TRM_RES_FLASH_PROGRAMING:
        if (dev_sem_info->vsec_sem_supported && mget_vsec_supp(mf)) {
            return lock_vsec_semaphore(mf, g_vsec_sem_addr[TRM_RES_FLASH_PROGRAMING], max_retries);
        }
        break;
    case TRM_RES_HCR_FLASH_PROGRAMING:
        if (dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return lock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK], max_retries);
        }
        break;
    case TRM_RES_HW_TRACER:
        if (dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return lock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK], max_retries);
        }
    break;
    default:
        break;
    }
    return TRM_STS_RES_NOT_SUPPORTED;
}

/************************************
 * Function: trm_try_lock
 ************************************/
trm_sts trm_try_lock(mfile* mf, trm_resourse res)
{
    return trm_lock(mf, res, 1);
}

/************************************
 * Function: trm_unlock
 ************************************/
trm_sts trm_unlock(mfile* mf, trm_resourse res)
{
    dm_dev_id_t dev_id;
    u_int32_t hw_dev_id;
    u_int32_t chip_rev;
    struct device_sem_info* dev_sem_info;

    if (dm_get_device_id(mf, &dev_id, &hw_dev_id, &chip_rev)) {
        return TRM_STS_CR_ACCESS_ERR;
    }

    dev_sem_info = get_device_sem_info(dev_id);

    // Not supported device
    if (!dev_sem_info) {
        return TRM_STS_DEV_NOT_SUPPORTED;
    }

    // lock resource on appropriate ifc if supported
    switch ((int)res) {
    case TRM_RES_ICMD:
        if (dev_sem_info->vsec_sem_supported && mget_vsec_supp(mf)) {
            return unlock_vsec_semaphore(mf, g_vsec_sem_addr[TRM_RES_ICMD]);
        } else if (dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return unlock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]);
        }
        break;
    case TRM_RES_FLASH_PROGRAMING:
        if (dev_sem_info->vsec_sem_supported && mget_vsec_supp(mf)) {
                   return unlock_vsec_semaphore(mf, g_vsec_sem_addr[TRM_RES_FLASH_PROGRAMING]);
        }
        break;
    case TRM_RES_HCR_FLASH_PROGRAMING:
        if (dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return unlock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]);
        }
        break;
    case TRM_RES_HW_TRACER:
        if (dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]){ // lock hw semaphore
            return unlock_hw_semaphore(mf, dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]);
        }
    break;
    default:
        break;
    }
    return TRM_STS_RES_NOT_SUPPORTED;
}

/************************************
 * Function: trm_sts2str
 ************************************/
const char* trm_sts2str(trm_sts status)
{
    size_t num_of_sts = sizeof(status_to_str)/sizeof(status_to_str[0]);

    if ((size_t)status >= num_of_sts) {
        return "Unknown status code";
    }

    return status_to_str[status];
}
