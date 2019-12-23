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


#include "mad_ifc.h"

#define MAD_ATTR_PORT_INFO          0x15
#define MAD_ATTR_NODE_INFO          0x11
#define MAD_ATTR_GENERAL_INFO_SMP   0xff17

#define MAX_DATA_SIZE               64

// for debug:
// #define _ENABLE_DEBUG_
#ifdef _ENABLE_DEBUG_
# define DEBUG_PRINT_SEND(data_struct, struct_name, method) \
    printf("-I- Data Sent (Method: %s):\n", method == MAD_IFC_METHOD_SET ? "SET" : "GET"); \
    tools_open_##struct_name##_print(data_struct, stdout, 1)
# define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method) \
    printf("-I- Data Received (Mehtod: %s):\n", method == MAD_IFC_METHOD_SET ? "SET" : "GET"); \
    tools_open_##struct_name##_print(data_struct, stdout, 1)
#else
# define DEBUG_PRINT_SEND(data_struct, struct_name, method)
# define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method)
#endif

/***************************************************/
#if !defined(DISABLE_OFED) && !defined(NO_INBAND)
    // register access for variable size registers (like mfba)
    #define MAD_IFC_ACCESS(mf, method, attr_id, attr_mod, data_struct, struct_name, prefix) \
        int status = 0; \
        u_int8_t data[MAX_DATA_SIZE] = {0}; \
        prefix##_##struct_name##_pack(data_struct, data); \
        if (method != MAD_IFC_METHOD_GET && method != MAD_IFC_METHOD_SET) { \
            return ME_ERROR; \
        } \
        DEBUG_PRINT_SEND(data_struct, struct_name, method); \
        if (method == MAD_IFC_METHOD_GET) { \
            status = mib_smp_get(mf, data, attr_id, attr_mod); \
        } else { \
            status = mib_smp_set(mf, data, attr_id, attr_mod); \
        } \
        prefix##_##struct_name##_unpack(data_struct, data); \
        DEBUG_PRINT_RECEIVE(data_struct, struct_name, method); \
        if (status) { \
            return (mad_ifc_status_t)status; \
        } \
        return ME_OK
#else
    #define MAD_IFC_ACCESS(mf, method, attr_id, attr_mod, data_struct, struct_name, prefix) \
        (void) mf; \
        (void) method; \
        (void) attr_id; \
        (void) attr_mod; \
        (void) data_struct; \
        return ME_NOT_IMPLEMENTED
#endif

/************************************
* Function: mad_ifc_port_info
************************************/
mad_ifc_status_t mad_ifc_port_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_ib_port_info *ib_port_info)
{
    MAD_IFC_ACCESS(mf, method, MAD_ATTR_PORT_INFO, attr_mod, ib_port_info,
            ib_port_info, tools_open);
}

/************************************
* Function: mad_ifc_node_info
************************************/
mad_ifc_status_t mad_ifc_node_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_node_info *node_info)
{
    MAD_IFC_ACCESS(mf, method, MAD_ATTR_NODE_INFO, attr_mod, node_info,
            node_info, tools_open);
}

/************************************
* Function: mad_ifc_extended_port_info
************************************/
mad_ifc_status_t mad_ifc_extended_port_info(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, struct tools_open_extended_ib_port_info *extended_ib_port_info)
{
    MAD_IFC_ACCESS(mf, method, MAD_ATTR_NODE_INFO, attr_mod, extended_ib_port_info,
            extended_ib_port_info, tools_open);
}

/************************************
* Function: mad_ifc_general_info_smp
************************************/
mad_ifc_status_t mad_ifc_general_info_smp(mfile *mf, mad_ifc_method_t method, u_int16_t attr_mod, union tools_open_smp_vsp_general_info *smp_vsp_general_info)
{
    MAD_IFC_ACCESS(mf, method, MAD_ATTR_GENERAL_INFO_SMP, attr_mod,
            smp_vsp_general_info, smp_vsp_general_info, tools_open);
}

/************************************
* Function: mad_ifc_general_info_hw
************************************/
mad_ifc_status_t mad_ifc_general_info_hw(mfile *mf,
        struct reg_access_hca_mgir_hardware_info *mgir_hardware_info) {
    MAD_IFC_ACCESS(mf, MAD_IFC_METHOD_GET, MAD_ATTR_GENERAL_INFO_SMP, 0, mgir_hardware_info,
            mgir_hardware_info, reg_access_hca);
}

/************************************
* Function: mad_ifc_general_info_fw
************************************/
mad_ifc_status_t mad_ifc_general_info_fw(mfile *mf,
        struct reg_access_hca_mgir_fw_info *mgir_fw_info) {
    MAD_IFC_ACCESS(mf, MAD_IFC_METHOD_GET, MAD_ATTR_GENERAL_INFO_SMP, 1, mgir_fw_info,
            mgir_fw_info, reg_access_hca);
}

/************************************
* Function: mad_ifc_general_info_sw
************************************/
mad_ifc_status_t mad_ifc_general_info_sw(mfile *mf,
        struct reg_access_hca_mgir_sw_info *mgir_sw_info) {
    MAD_IFC_ACCESS(mf, MAD_IFC_METHOD_GET, MAD_ATTR_GENERAL_INFO_SMP, 2, mgir_sw_info,
            mgir_sw_info, reg_access_hca);
}
/************************************
* Function: mad_ifc_err2str
************************************/

const char* mad_ifc_err2str(mad_ifc_status_t status)
{
    return m_err2str(status);
}
