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

#ifndef TOOLS_RESOURCE_MGMT_H
#define TOOLS_RESOURCE_MGMT_H

#include <mtcr.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TRM_STS_OK = 0,
    TRM_STS_RES_BUSY,
    TRM_STS_IFC_NA,
    TRM_STS_DEV_NOT_SUPPORTED,
    TRM_STS_RES_NOT_SUPPORTED,
    TRM_STS_CR_ACCESS_ERR,
    TRM_STS_MEM_ERROR
} trm_sts;

typedef enum {
    // vsec semaphores
    TRM_RES_ICMD = 0x0,
    TRM_RES_FLASH_PROGRAMING     = 0x1,
    // hw semaphores
    TRM_RES_MAIN_SEM             = 0x10,
    TRM_RES_HW_TRACER            = TRM_RES_MAIN_SEM,
    TRM_RES_TOOLS_HCR            = TRM_RES_MAIN_SEM,
    TRM_RES_HCR_FLASH_PROGRAMING = 0x11,
    TRM_RES_ALL                  = 0xffff,
} trm_resourse;

typedef struct trm_t*trm_ctx;


/*
 * Create tools resource context
 * trm_p: trm_ctx pointer to be allocated
 * Parameter (mf)  - an opened mst device handler
 * Return TOOLS_STS_OK on success of creating the context, otherwise any other error code.
 */
trm_sts trm_create(trm_ctx *trm_p, mfile *mf);


/*
 * Destroy the context
 * trm: trm_ctx to be destroyed
 * Return TOOLS_STS_OK on success of destroying the context, otherwise any other error code.
 */
trm_sts trm_destroy(trm_ctx trm);

/*
 * Lock tools resource
 * Parameter (mf)  - an opened mst device handler
 * Parameter (res) - resource to acquire.
 * Parameter (max_retry) - max retry count before declaring resource busy.
 * Return TOOLS_STS_OK on success of locking all the desired resources, otherwise any other error code.
 */
trm_sts trm_lock(trm_ctx trm, trm_resourse res, unsigned int max_retry);

/*
 * Try to lock tools resource (returns immediately if resource busy)
 * Parameter (mf)  - an opened mst device handler
 * Parameter (res) - resource to acquire.
 * Return TOOLS_STS_OK on success of locking all the desired resources, otherwise any other error code.
 */
trm_sts trm_try_lock(trm_ctx trm, trm_resourse res);

/*
 * Unlock tools resource
 * Parameter (mf)  - an opened mst device handler
 * Parameter (res) - resource to release.
 * Return TOOLS_STS_OK if all given resources were unlocked successfully.
 */
trm_sts trm_unlock(trm_ctx trm, trm_resourse res);

/*
 * Translate tools_sem_mgmt_sts status code to a human readable string.
 * Parameter (status) - status code to translate.
 * Return descriptive string.
 */
const char* trm_sts2str(trm_sts status);

#ifdef __cplusplus
}
#endif

#endif // TOOLS_RESOURCE_MGMT_H
