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
 * tools_cif.c
 *
 *  Created on: Nov 5, 2014
 *      Author: adrianc
 */

#include <common/compatibility.h>
#include <common/bit_slice.h>

#if !defined(__FreeBSD__) && !defined(UEFI_BUILD)
#include <mtcr_tools_cif.h>
#endif

#include "tools_cif.h"

#define TOOLS_HCR_MAX_MBOX 288
#define QUERY_DEV_CAP_OP 0x3
#define QUERY_DEF_PARAMS_OP 0x73
#define HW_ACCESS_OP 0x60

#define QPC_READ_OP 0x67
#define QPC_WRITE_OP 0x69

#define CHECK_RC(rc) \
    if (rc) {return (MError)rc;}

#define BE32_TO_CPU(s, n) do {                                          \
        u_int32_t i;                                                   \
        u_int32_t *p = (u_int32_t*)(s);                               \
        for (i = 0; i < (n); i++, p++)                                      \
            *p = __be32_to_cpu(*p);                                    \
} while (0)

#if __BYTE_ORDER == __BIG_ENDIAN

#define SWAP_DW_BE(uint64_num) \
    (((uint64_num) & 0xffffffffULL) << 32) | (((uint64_num) >> 32) & 0xffffffffULL)

#else
#define SWAP_DW_BE(uint64_num) (uint64_num)
#endif

//TODO: adrianc: if we find ourselves adding more and more commands consider using a macro to save code.
//TODO: adrianc: when library expands consider returning its own error code

MError tcif_query_dev_cap(mfile *dev, u_int32_t offset, u_int64_t *data)
{
    int rc = tools_cmdif_send_mbox_command(dev, 0, QUERY_DEV_CAP_OP, 0, offset, (u_int32_t*)data, 8, 1); CHECK_RC(rc);
    BE32_TO_CPU(data, 2);
    *data = SWAP_DW_BE(*data);
    return ME_OK;
}


MError tcif_query_global_def_params(mfile *dev, struct tools_open_query_def_params_global *global_params)
{
    u_int8_t data[TOOLS_OPEN_QUERY_DEF_PARAMS_GLOBAL_SIZE] = {0};
    int rc = tools_cmdif_send_mbox_command(dev, 0, QUERY_DEF_PARAMS_OP, 0, 0, data, sizeof(data), 0); CHECK_RC(rc);
    tools_open_query_def_params_global_unpack(global_params, data);
    return ME_OK;
}


MError tcif_query_per_port_def_params(mfile *dev, u_int8_t port, struct tools_open_query_def_params_per_port *port_params)
{
    u_int8_t data[TOOLS_OPEN_QUERY_DEF_PARAMS_PER_PORT_SIZE] = {0};
    int rc = tools_cmdif_send_mbox_command(dev, 0, QUERY_DEF_PARAMS_OP, port, 0, data, sizeof(data), 0); CHECK_RC(rc);
    tools_open_query_def_params_per_port_unpack(port_params, data);
    return ME_OK;
}


MError tcif_qpc_context_read(mfile *dev, u_int32_t qpn, u_int32_t source, u_int8_t *data, u_int32_t len)
{
    u_int32_t input_mod = 0;
    input_mod = MERGE(input_mod, source, 24,  8);
    input_mod = MERGE(input_mod, qpn,  0, 24);
    int rc = tools_cmdif_send_mbox_command(dev, input_mod, QPC_READ_OP, 0, 0, data, len, 1);
    CHECK_RC(rc);
    return ME_OK;
}


MError tcif_qpc_context_write(mfile *dev, u_int32_t qpn, u_int32_t source, u_int8_t *data, u_int32_t len)
{
    u_int32_t input_mod = 0;
    input_mod = MERGE(input_mod, source, 24,  8);
    input_mod = MERGE(input_mod, qpn,  0, 24);
    int rc = tools_cmdif_send_mbox_command(dev, input_mod, QPC_WRITE_OP, 0, 0, data, len, 0);
    CHECK_RC(rc);
    return ME_OK;
}


MError tcif_hw_access(mfile *dev, u_int64_t key, int lock_unlock)
{
    return (MError)tools_cmdif_send_inline_cmd(dev, key, NULL, 0, HW_ACCESS_OP, lock_unlock);
}
const char* tcif_err2str(MError rc)
{
    return m_err2str(rc);
}


MError tcif_cr_mbox_supported(mfile *dev)
{
#if defined(__FreeBSD__) || defined(UEFI_BUILD)
    (void)dev;
    return ME_NOT_IMPLEMENTED;
#else
    return (MError)tools_cmdif_is_cr_mbox_supported(dev);
#endif

}
