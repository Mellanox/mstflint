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

#ifndef MAD_IFC_H
#define MAD_IFC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <mtcr.h>
#ifndef NO_INBAND
#include "mtcr_ib.h"
#endif
#include <tools_layouts/tools_open_layouts.h>
#include <tools_layouts/reg_access_hca_layouts.h>

typedef enum {
    MAD_IFC_METHOD_GET = MACCESS_REG_METHOD_GET,
    MAD_IFC_METHOD_SET = MACCESS_REG_METHOD_SET
} mad_ifc_method_t;

// we use the same error messages as mtcr
typedef MError mad_ifc_status_t;

const char* mad_ifc_err2str(mad_ifc_status_t status);
mad_ifc_status_t mad_ifc_port_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_ib_port_info *port_info);
mad_ifc_status_t mad_ifc_node_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_node_info *node_info);
mad_ifc_status_t mad_ifc_extended_port_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_extended_ib_port_info *ext_port_info);
mad_ifc_status_t mad_ifc_general_info_smp(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, union tools_open_smp_vsp_general_info *general_info);
mad_ifc_status_t mad_ifc_general_info_hw(mfile *mf,
        struct reg_access_hca_mgir_hardware_info *hw_info);
mad_ifc_status_t mad_ifc_general_info_fw(mfile *mf,
        struct reg_access_hca_mgir_fw_info *fw_info);
mad_ifc_status_t mad_ifc_general_info_sw(mfile *mf,
        struct reg_access_hca_mgir_sw_info *sw_info);
#ifdef __cplusplus
}
#endif

#endif // MAD_IFC_H
