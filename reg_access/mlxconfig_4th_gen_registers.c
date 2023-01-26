/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "reg_access.h"
#include "reg_access_macros.h"
#include "common/compatibility.h"

#include <tools_layouts/mlxconfig_4th_gen_layouts.h>

#define REG_ID_MNVA 0x9024
#define REG_ID_MNVIA_4TH_GEN 0x9029

reg_access_status_t reg_access_mnva(mfile* mf, reg_access_method_t method, struct mlxconfig_4th_gen_mnva* mnva)
{
    // reg_size is in bytes
    u_int32_t reg_size = (mnva->nv_hdr.length << 2) + mlxconfig_4th_gen_nv_hdr_size();
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg = reg_size;
    if (method == REG_ACCESS_METHOD_GET)
    {
        w_size_reg -= mnva->nv_hdr.length << 2;
    }
    else
    {
        r_size_reg -= mnva->nv_hdr.length << 2;
    }
    REG_ACCCESS_VAR(mf, method, REG_ID_MNVA, mnva, mnva, reg_size, r_size_reg, w_size_reg, mlxconfig_4th_gen);
}

reg_access_status_t
  reg_access_mnvia_4th_gen(mfile* mf, reg_access_method_t method, struct mlxconfig_4th_gen_mnvia* mnvia)
{
    if (method != REG_ACCESS_METHOD_SET)
    { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVIA_4TH_GEN, mnvia, mnvia, mlxconfig_4th_gen);
}
