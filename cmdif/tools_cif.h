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
 *
 *  Created on: Nov 5, 2014
 *      Author: adrianc
 */

#ifndef TOOLS_CIF_H
#define TOOLS_CIF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mtcr.h>
#include <tools_layouts/tools_open_layouts.h>


/**
 * tcif_query_dev_cap:
 * @param[in]  dev           A pointer to a device context.
 * @param[in]  offs          offset in even dword to read from the DEV_CAP vector
 * @param[out] data          Quad-word read from the device capabilities vector from offset: offs

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_dev_cap(mfile *dev, u_int32_t offs, u_int64_t *data);

/**
 * tcif_query_global_def_params:
 * @param[in]     dev           A pointer to a device context.
 * @param[in/out] global_params pointer to global params struct

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_global_def_params(mfile *dev, struct tools_open_query_def_params_global *global_params);

/**
 * tcif_query_per_port_def_params:
 * @param[in]     dev           A pointer to a device context.
 * @param[in]     port          Port that the query will be performed on (1 or 2)
 * @param[in/out] port_params   Pointer to port params struct

 * @return     One of the MError* values, or a raw
 **/
MError tcif_query_per_port_def_params(mfile *dev, u_int8_t port, struct tools_open_query_def_params_per_port *port_params);

/**
 * tcif_qpc_context_read:
 * @param[in]     dev           A pointer to a device context.
 * @param[in]     qpn           QP Number
 * @param[in]     source        QP Source
 * @param[in]     data          Data that was read
 *
 * @return     One of the MError* values, or a raw
 **/
MError tcif_qpc_context_read(mfile *dev, u_int32_t qpn, u_int32_t source, u_int8_t *data, u_int32_t len);

/**
 * tcif_qpc_context_write:
 * @param[in]     dev           A pointer to a device context.
 * @param[in]     qpn           QP Number
 * @param[in]     source        QP Source
 * @param[in]     data          Data to be written
 *
 * @return     One of the MError* values, or a raw
 **/
MError tcif_qpc_context_write(mfile *dev, u_int32_t qpn, u_int32_t source, u_int8_t *data, u_int32_t len);


/**
 * tcif_hw_access:
 * @param[in]  dev           A pointer to a device context.
 * @param[in]  key           key with which we attempt to lock/unlock the cr-space (should be 0 for locking)
 * @param[out] lock_unlock   1-lock , 0-unlock

 * @return     One of the MError* values, or a raw
 **/
MError tcif_hw_access(mfile *dev, u_int64_t key, int lock_unlock);

/**
 * tcif_cr_mailbox_supported:
 * @param[in]  dev           A pointer to a device context.

 * @return     ME_OK                - cr mailbox supported
 *             ME_SEM_LOCKED        - tools HCR semaphore locked
 *             ME_CMDIF_NOT_SUPP    - cr mailbox not supported
 **/
MError tcif_cr_mbox_supported(mfile *dev);

/**
 * tcif_err2str:
 * @param[in]  rc            return code from one of the above functions

 * @return     string describing the error occurred.
 **/
const char* tcif_err2str(MError rc);

#ifdef __cplusplus
}
#endif

#endif /* TOOLS_CIF_H */
