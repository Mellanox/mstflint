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

#include <stdlib.h>
#include <string.h>

#include <common/tools_utils.h>
#include <common/bit_slice.h>
#include <common/compatibility.h>
#include <dev_mgt/tools_dev_types.h>

#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
#include <mtcr_ib_res_mgt.h>
#endif

#ifdef __WIN__
#include <process.h>
#define getpid() _getpid()
#endif

#include "tools_res_mgmt.h"
#include "tools_time.h"

#define VSEC_SEM_NUM 10
#define HW_SEM_NUM VSEC_SEM_NUM
static const char *status_to_str[] =
{
    "Ok",
    "Resource is busy",
    "Tools resource management interface not available",
    "Device not supported",
    "Resource not supported",
    "CR-Space access error",
    "Memory allocation failed"
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
        DeviceConnectX2,                    // dev_id
        {0xf03bc},                          // hw_sem_addr
        0,                                  // vsec_sem_supported
    },
    {
        DeviceConnectX3,                    // dev_id
        {0xf03bc, 0xf03a0},                 // hw_sem_addr
        0,                                  // vsec_sem_supported
    },
    {
        DeviceConnectX3Pro,                 // dev_id
        {0xf03bc, 0xf03a0},                 // hw_sem_addr
        0,                                  // vsec_sem_supported
    },
    {
        DeviceInfiniScaleIV,                // dev_id
        {0},                                // hw_sem_addr
        0,                                  // vsec_sem_supported
    },
    {
        DeviceSwitchX,                      // dev_id
        {0},                                // hw_sem_addr
        0,                                  // vsec_sem_supported
    },
    {
        DeviceConnectIB,         // dev_id
        {0xe27f8},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceConnectX4,         // dev_id
        {0xe250c},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceSwitchIB,          // dev_id
        {0xa24f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    },
    {
        DeviceSpectrum,          // dev_id
        {0xa24f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    },
    {
        DeviceConnectX4LX,         // dev_id
        {0xe250c},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceSwitchIB2,          // dev_id
        {0xa24f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    },
    {
        DeviceConnectX5,         // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceBlueField,         // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceBlueField2,        // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceQuantum,          // dev_id
        {0xa68f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    },
    {
        DeviceSpectrum2,          // dev_id
        {0xa68f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    },
    {
        DeviceConnectX6,         // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceConnectX6DX,       // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceConnectX6LX,       // dev_id
        {0xe74e0},               // hw_sem_addr
        1,                       // vsec_sem_supported
    },
    {
        DeviceSpectrum3,          // dev_id
        {0xa68f8},               // hw_sem_addr
        0,                       // vsec_sem_supported
    }
};

#define MAX_SEMAPHORE_ADDRES 8
#define FLASH_SEM_SLEEP      500


struct mad_lock_info {
    u_int32_t lock_key;
    u_int32_t lease_time_ms;
    tt_ctx_t start_time;
};

struct trm_t {
    mfile *mf;
    const struct device_sem_info *dev_sem_info;
    struct mad_lock_info mad_lock[MAX_SEMAPHORE_ADDRES];
    int ib_semaphore_lock_is_supported;
};

/************************************
* Function: lock_hw_semaphore
************************************/
static trm_sts lock_hw_semaphore(mfile *mf, u_int32_t addr, unsigned int max_retries, int sleep_t)
{
    u_int32_t val = 0;
    unsigned int cnt = 0;
    int rc;

    while (((rc = mread4(mf, addr, &val)) == 4) && val == 1 && cnt < max_retries) {
        cnt++;
        int sleep_time = sleep_t != 0 ? sleep_t : ((rand() % 5) + 1);
        msleep(sleep_time);
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
static trm_sts unlock_hw_semaphore(mfile *mf, u_int32_t addr)
{
    int rc = mwrite4(mf, addr, 0) == 4 ? TRM_STS_OK : TRM_STS_CR_ACCESS_ERR;
    // give up the rest of the time slice
    msleep(0);
    return rc;
}

/************************************
* Function: lock_icommand_gateway_semaphore()
************************************/
static trm_sts lock_icommand_gateway_semaphore(mfile *mf, u_int32_t addr, unsigned int max_retries)
{
    static u_int32_t pid = 0;
    u_int32_t read_val = 0;
    unsigned cnt = 0;

    if (!pid) {
        pid = getpid();
    }
    do {    // loop while the semaphore is taken by someone else
        if (cnt++ > max_retries) {
            return TRM_STS_RES_BUSY;
        }
        //write pid to semaphore
        if(MWRITE4_SEMAPHORE(mf, addr, pid)) {
            return TRM_STS_CR_ACCESS_ERR;
        }
        // Read back
        if(MREAD4_SEMAPHORE(mf, addr, &read_val)) {
            return TRM_STS_CR_ACCESS_ERR;
        }
        if (read_val == pid) {
            break;
        }
        msleep(((rand() % 5) + 1));
    } while (read_val != pid);
    return TRM_STS_OK;
}

/************************************
* Function: unlock_icommand_gateway_semaphore()
************************************/
static trm_sts unlock_icommand_gateway_semaphore(mfile *mf, u_int32_t addr)
{
    if(MWRITE4_SEMAPHORE(mf, addr, 0)) {
        return TRM_STS_CR_ACCESS_ERR;
    }
    return TRM_STS_OK;
}

#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
/************************************
* Function: release_vs_mad_semaphore()
************************************/
#define GET_LEASE_TIME_MS(is_leaseable, lease_time_exp) ((is_leaseable) ? (50 * (1 << (lease_time_exp))) : 0)

static trm_sts release_vs_mad_semaphore(trm_ctx trm, trm_resourse resource)
{
    u_int32_t lock_key = 0;
    u_int8_t new_lease_exponent = 0;
    int is_leaseable = 0;

    int rc = TRM_STS_OK;
    if (!trm->mad_lock[resource].lock_key) {
        return TRM_STS_OK;
    }
    if (trm->ib_semaphore_lock_is_supported == 0) {
        return TRM_STS_RES_NOT_SUPPORTED;
    }
    rc = mib_semaphore_lock_vs_mad(trm->mf, SMP_SEM_RELEASE, g_vsec_sem_addr[resource],
                                   trm->mad_lock[resource].lock_key, &lock_key, &is_leaseable, &new_lease_exponent, SEM_LOCK_SET);
    if (rc == (int)ME_MAD_BUSY) {
        return TRM_STS_RES_BUSY;
    } else if (rc) {
        return TRM_STS_RES_NOT_SUPPORTED;
    } else if (lock_key != 0) {
        return TRM_STS_CR_ACCESS_ERR;
    }
    trm->mad_lock[resource].lock_key = 0;
    trm->mad_lock[resource].lease_time_ms = 0;
    return TRM_STS_OK;
}

/************************************
* Function: lock_vs_mad_semaphore()
************************************/


static trm_sts lock_vs_mad_semaphore(trm_ctx trm, trm_resourse resource, unsigned int max_retries)
{
    u_int32_t new_lock_key = 0;
    u_int8_t new_lease_exponent = 0;
    int is_leaseable = 0;
    tt_ctx_t curr_time;
    int rc = TRM_STS_OK;
    unsigned int cnt = 0;

    if (trm->ib_semaphore_lock_is_supported == 0) {
        return TRM_STS_RES_NOT_SUPPORTED;
    }

    // check if we got lock_key
    if (trm->mad_lock[resource].lock_key) {
        // TODO: use threads to extend lock every ~20 seconds untill releasing the lock
        // check if extension is needed
        if (trm->mad_lock[resource].lease_time_ms == 0) {
            // no need to extend lease is untill device reboot
            return TRM_STS_OK;
        }

        tt_get_time(&curr_time);
        double diff = tt_diff_in_ms(trm->mad_lock[resource].start_time, curr_time);
        if (diff <= trm->mad_lock[resource].lease_time_ms * 0.6) {
            return TRM_STS_OK;
        }
        // extension needed try to extend
        rc = mib_semaphore_lock_vs_mad(trm->mf, SMP_SEM_EXTEND, g_vsec_sem_addr[resource],
                                       trm->mad_lock[resource].lock_key, &new_lock_key, &is_leaseable, &new_lease_exponent, SEM_LOCK_SET);
        if (rc == ME_OK && new_lock_key == trm->mad_lock[resource].lock_key) {
            // extend OK
            trm->mad_lock[resource].lease_time_ms = GET_LEASE_TIME_MS(is_leaseable, new_lease_exponent);
            trm->mad_lock[resource].start_time = curr_time;
            return TRM_STS_OK;
        } else {
            // extend failed try to re-lock the semaphore
            trm->mad_lock[resource].lock_key = 0;
            trm->mad_lock[resource].lease_time_ms = 0;
            new_lock_key = 0;
        }
    }
    // if not or extend failed try to lock
    do {
        if (cnt++ > max_retries) {
            return TRM_STS_RES_BUSY;
        }
        rc = mib_semaphore_lock_vs_mad(trm->mf, SMP_SEM_LOCK, g_vsec_sem_addr[resource],
                                       0, &new_lock_key, &is_leaseable, &new_lease_exponent, SEM_LOCK_SET);
        if (rc == (int)ME_MAD_BUSY || new_lock_key == 0) {
            msleep(((rand() % 5) + 1));
        }
    } while (rc == (int)ME_MAD_BUSY || new_lock_key == 0);

    if (rc) {
        return TRM_STS_RES_NOT_SUPPORTED;
    }
    trm->mad_lock[resource].lock_key = new_lock_key;
    trm->mad_lock[resource].lease_time_ms = GET_LEASE_TIME_MS(is_leaseable, new_lease_exponent);
    tt_get_time(&(trm->mad_lock[resource].start_time));
    return TRM_STS_OK;
}
#endif
/************************************
* Function: get_device_sem_info
************************************/
static struct device_sem_info* get_device_sem_info(dm_dev_id_t dev_id)
{
    size_t i;
    for (i = 0; i < sizeof(g_dev_sem_info_db) / sizeof(g_dev_sem_info_db[0]); i++) {
        if (g_dev_sem_info_db[i].dev_id == dev_id) {
            return &g_dev_sem_info_db[i];
        }
    }

    return NULL;
}

/************************************
* Function: trm_create
************************************/
trm_sts trm_create(trm_ctx *trm_p, mfile *mf)
{
    dm_dev_id_t dev_id = DeviceStartMarker;
    u_int32_t hw_dev_id;
    u_int32_t chip_rev;

    *trm_p = (trm_ctx) malloc(sizeof(struct trm_t));
    if (!(*trm_p)) {
        return TRM_STS_MEM_ERROR;
    }
    memset((*trm_p), 0, sizeof(struct trm_t));
    (*trm_p)->mf = mf;

#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
    u_int32_t dev_flags = 0;
    if (!mget_mdevs_flags(mf, &dev_flags)) {
        if ((dev_flags & MDEVS_IB) && mib_semaphore_lock_is_supported(mf) == 1) {
            (*trm_p)->ib_semaphore_lock_is_supported = 1;
        }
    }
#endif

    if (dm_get_device_id((*trm_p)->mf, &dev_id, &hw_dev_id, &chip_rev)) {
        free(*trm_p);
        *trm_p = (trm_ctx)NULL;
        return dev_id == DeviceUnknown ? TRM_STS_DEV_NOT_SUPPORTED : TRM_STS_CR_ACCESS_ERR;
    }

    (*trm_p)->dev_sem_info = get_device_sem_info(dev_id);

    // Not supported device
    if (!((*trm_p)->dev_sem_info)) {
        free(*trm_p);
        *trm_p = (trm_ctx)NULL;
        return TRM_STS_DEV_NOT_SUPPORTED;
    }

    return TRM_STS_OK;
}

/************************************
* Function: trm_destroy
************************************/
trm_sts trm_destroy(trm_ctx trm)
{
    if (trm) {
        free(trm);
    }
    return TRM_STS_OK;
}

/************************************
* Function: trm_lock
************************************/
trm_sts trm_lock(trm_ctx trm, trm_resourse res, unsigned int max_retries)
{
    u_int32_t dev_type = 0;
    if (mget_mdevs_flags(trm->mf, &dev_type)) {
        return TRM_STS_DEV_NOT_SUPPORTED;
    }
    // lock resource on appropriate ifc if supported
    switch ((int)res) {
    case TRM_RES_ICMD:
        if (trm->dev_sem_info->vsec_sem_supported && mget_vsec_supp(trm->mf)) {
            return lock_icommand_gateway_semaphore(trm->mf, g_vsec_sem_addr[TRM_RES_ICMD], max_retries);
#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
        } else if (trm->dev_sem_info->vsec_sem_supported && (dev_type & MDEVS_IB)) {
            return lock_vs_mad_semaphore(trm, TRM_RES_ICMD, max_retries);
#endif
        } else if (trm->dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return lock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK], max_retries, 0);
        }
        break;

    case TRM_RES_FLASH_PROGRAMING:
        if (trm->dev_sem_info->vsec_sem_supported && mget_vsec_supp(trm->mf)) {
            return lock_icommand_gateway_semaphore(trm->mf, g_vsec_sem_addr[TRM_RES_FLASH_PROGRAMING], max_retries);
#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
        } else if (trm->dev_sem_info->vsec_sem_supported && (dev_type & MDEVS_IB)) {
            return lock_vs_mad_semaphore(trm, TRM_RES_FLASH_PROGRAMING, max_retries);
#endif
        }
        break;

    case TRM_RES_HCR_FLASH_PROGRAMING:
        if (trm->dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return lock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK], max_retries, FLASH_SEM_SLEEP);
        }
        break;

    case TRM_RES_HW_TRACER:
        if (trm->dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return lock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK], max_retries, 0);
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
trm_sts trm_try_lock(trm_ctx trm, trm_resourse res)
{
    return trm_lock(trm, res, 1);
}

/************************************
* Function: trm_unlock
************************************/
trm_sts trm_unlock(trm_ctx trm, trm_resourse res)
{
    u_int32_t dev_type = 0;
    if (mget_mdevs_flags(trm->mf, &dev_type)) {
        return TRM_STS_DEV_NOT_SUPPORTED;
    }

    // lock resource on appropriate ifc if supported
    switch ((int)res) {
    case TRM_RES_ICMD:
        if (trm->dev_sem_info->vsec_sem_supported && mget_vsec_supp(trm->mf)) {
            return unlock_icommand_gateway_semaphore(trm->mf, g_vsec_sem_addr[TRM_RES_ICMD]);
#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
        } else if (trm->dev_sem_info->vsec_sem_supported && (dev_type & MDEVS_IB)) {
            return release_vs_mad_semaphore(trm, TRM_RES_ICMD);
#endif
        } else if (trm->dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return unlock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_MAIN_SEM & HW_SEM_ADDR_MASK]);
        }
        break;

    case TRM_RES_FLASH_PROGRAMING:
        if (trm->dev_sem_info->vsec_sem_supported && mget_vsec_supp(trm->mf)) {
            return unlock_icommand_gateway_semaphore(trm->mf, g_vsec_sem_addr[TRM_RES_FLASH_PROGRAMING]);
#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
        } else if (trm->dev_sem_info->vsec_sem_supported && (dev_type & MDEVS_IB)) {
            return release_vs_mad_semaphore(trm, TRM_RES_FLASH_PROGRAMING);
#endif
        }
        break;

    case TRM_RES_HCR_FLASH_PROGRAMING:
        if (trm->dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return unlock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_HCR_FLASH_PROGRAMING & HW_SEM_ADDR_MASK]);
        }
        break;

    case TRM_RES_HW_TRACER:
        if (trm->dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]) { // lock hw semaphore
            return unlock_hw_semaphore(trm->mf, trm->dev_sem_info->hw_sem_addr[TRM_RES_HW_TRACER & HW_SEM_ADDR_MASK]);
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
    size_t num_of_sts = sizeof(status_to_str) / sizeof(status_to_str[0]);

    if ((size_t)status >= num_of_sts) {
        return "Unknown status code";
    }

    return status_to_str[status];
}
