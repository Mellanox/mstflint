
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

#include "mtcr_mem_ops.h"

#if defined(__WIN__) || defined(MST_UL) || defined(__FreeBSD__) || defined(__VMKERNEL_UW_VMKLINUX__) || defined(__VMKERNEL_UW_NATIVE__)
#else
#include "mst_pciconf.h"
#include <sys/ioctl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int mtcr_memaccess(mfile* mf, unsigned int offset, unsigned int size, unsigned char *data, int rw, mem_type_t type)
{
#if defined(__WIN__) || defined(MST_UL) || defined(__FreeBSD__) || defined(__VMKERNEL_UW_VMKLINUX__) || defined(__VMKERNEL_UW_NATIVE__)
    (void)type;
    (void)mf;
    (void)offset;
    (void)size;
    (void)data;
    (void)rw;
    return ME_UNSUPPORTED_OPERATION;
#else
    if (mf->ul_ctx) {
        return ME_UNSUPPORTED_OPERATION;
    }
    unsigned int iterator = 0;
    while (iterator < size) {
        unsigned int op_size = ((size - iterator) > PCICONF_MAX_MEMACCESS_SIZE) ? PCICONF_MAX_MEMACCESS_SIZE : (size - iterator);
        struct mst_mem_access_st mem_access;
        memset(&mem_access, 0, sizeof(mem_access));
        mem_access._rw = rw;
        mem_access.offset = offset + iterator;
        mem_access.size = op_size;
        mem_access.mem_type = type;
        if (rw) {
            /*
             * Write OP
             */
            memcpy(mem_access.data, data + iterator, op_size);
        }
        if (ioctl(mf->fd, PCICONF_MEM_ACCESS, &mem_access) < 0) {
            return ME_ERROR;
        }
        if (!rw) {
            /*
             * Read OP
             */
            memcpy(data + iterator, mem_access.data, op_size);
        }
        iterator += op_size;
    }
    return ME_OK;
#endif
}


int get_mem_props(mfile *mf, mem_type_t type, mem_props_t *props)
{
#if defined(__WIN__) || defined(MST_UL) || defined(__FreeBSD__) || defined(__VMKERNEL_UW_VMKLINUX__) || defined(__VMKERNEL_UW_NATIVE__)
    (void)mf;
    (void)type;
    (void)props;
    return ME_UNSUPPORTED_OPERATION;
#else
    if (!mf || !mf->dma_props) {
        return ME_UNSUPPORTED_OPERATION;
    }
    if (type >= MEM_END) {
        return ME_BAD_PARAMS;
    }
    struct dma_prop *dma_props_p = (struct dma_prop*)mf->dma_props + (int)type;
    props->dma_pa = dma_props_p->dma_pa;
    props->mem_size = dma_props_p->mem_size;
    return ME_OK;
#endif
}

void init_mem_ops(mfile *mf)
{
#if defined(__WIN__) || defined(MST_UL) || defined(__FreeBSD__) || defined(__VMKERNEL_UW_VMKLINUX__) || defined(__VMKERNEL_UW_NATIVE__)
    (void)mf;
#else
    if (!mf || mf->ul_ctx) {
        return;
    }
    struct mst_dma_props_st dma_props_params;
    memset(&dma_props_params, 0, sizeof(dma_props_params));
    if (ioctl(mf->fd, PCICONF_DMA_PROPS, &dma_props_params) < 0) {
        mf->dma_props = NULL;
    } else {
        mf->dma_props = malloc(sizeof(dma_props_params.dma_props));
        if (mf->dma_props) {
            memcpy(mf->dma_props, &dma_props_params.dma_props, sizeof(dma_props_params.dma_props));
        }
    }
#endif
}

void close_mem_ops(mfile *mf)
{
    if (mf->dma_props) {
        free(mf->dma_props);
        mf->dma_props = NULL;
    }
}

