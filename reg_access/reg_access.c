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

#include "reg_access.h"

#define REG_ID_MFPA  0x9010
#define REG_ID_MFBA  0x9011
#define REG_ID_MFBE  0x9012
#define REG_ID_MFMC  0x9013
#define REG_ID_PMDIO 0x9017
#define REG_ID_MGIR  0x9020
#define REG_ID_PMDIC 0x9021
#define REG_ID_MNVA  0x9024
#define REG_ID_MNVI  0x9025
#define REG_ID_MNVIA 0x9029 // 4th gen
#define REG_ID_MVTS  0x902c
#define REG_ID_NVQC  0x9030
#define REG_ID_NVIA  0x9033 // 5th gen
#define REG_ID_NVQGC 0x9034
#define REG_ID_MNVGN 0x9035

// TODO: get correct register ID for mfrl mfai
#define REG_ID_MFRL 0x9028
#define REG_ID_MFAI 0x9029

// WA for MGIR: the reg size is too big so we limit it to INBAND_MAX_REG_SIZE
#define INBAND_MAX_REG_SIZE 44
#define MGIR_REG_SIZE INBAND_MAX_REG_SIZE
// End of WA

// for debug:
//#define _ENABLE_DEBUG_
#ifdef _ENABLE_DEBUG_
# define DEBUG_PRINT_SEND(data_struct, struct_name, method, prefix)\
	printf("-I- Data Sent (Method: %s):\n", method == REG_ACCESS_METHOD_SET ? "SET" : "GET");\
	prefix##_##struct_name##_print(data_struct, stdout, 1)
# define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, prefix)\
	printf("-I- Data Received (Mehtod: %s):\n", method == REG_ACCESS_METHOD_SET ? "SET" : "GET");\
	prefix##_##struct_name##_print(data_struct, stdout, 1)
#else
# define DEBUG_PRINT_SEND(data_struct, struct_name, method, prefix)
# define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, prefix)
#endif

/***************************************************/

// register access for variable size registers (like mfba)

#define REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, methdod, reg_id, data_struct, struct_name, reg_size , r_reg_size, w_reg_size, pack_func,\
        unpack_func, size_func, print_func, status)\
    int rc;\
    int max_data_size = size_func();\
    u_int8_t data[max_data_size];\
    memset(data, 0, max_data_size);\
    pack_func(data_struct, data);\
    if (method != REG_ACCESS_METHOD_GET && method != REG_ACCESS_METHOD_SET) {\
        return ME_REG_ACCESS_BAD_METHOD;\
    }\
    DEBUG_PRINT_SEND(data_struct, struct_name, method, print_func);\
    rc = maccess_reg(mf, reg_id, (maccess_reg_method_t)method, data, reg_size, r_reg_size, w_reg_size, status);\
    unpack_func(data_struct, data);\
    DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, print_func);

#define REG_ACCESS_GENERIC_VAR(mf, methdod, reg_id, data_struct, struct_name, reg_size , r_reg_size, w_reg_size, pack_func,\
        unpack_func, size_func, print_func)\
    int status = 0;\
    REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, methdod, reg_id, data_struct, struct_name, reg_size , r_reg_size, w_reg_size, pack_func,\
        unpack_func, size_func, print_func, &status)\
    if (rc || status) {\
        return (reg_access_status_t)rc;\
    }\
    return ME_OK

#define REG_ACCCESS_VAR(mf, methdod, reg_id, data_struct, struct_name, reg_size , r_reg_size, w_reg_size, prefix)\
    REG_ACCESS_GENERIC_VAR(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size, w_reg_size,\
            prefix##_##struct_name##_pack, prefix##_##struct_name##_unpack, prefix##_##struct_name##_size,\
            prefix##_##struct_name##_print)

// register access for static sized registers
#define REG_ACCCESS(mf, methdod, reg_id, data_struct, struct_name, prefix)\
    int data_size = prefix##_##struct_name##_size();\
    REG_ACCCESS_VAR(mf, methdod, reg_id, data_struct, struct_name, data_size, data_size, data_size, prefix)

/************************************
 * Function: reg_access_mfba
 ************************************/
reg_access_status_t reg_access_mfba(mfile* mf, reg_access_method_t method, struct register_access_mfba* mfba)
{
    u_int32_t reg_size = mfba->size + REG_ACCESS_MFBA_HEADER_LEN;
    // the r/w_size_reg is for improved performance for when we send the register
    // via icmd , since its relatively slow si no need to write the data array from mfba struct to the device when reading from the device
    // and no need for reading the data array from the device when writing to the device (we just care about the status)
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg= reg_size;
    if (method == REG_ACCESS_METHOD_GET) {
        w_size_reg -= mfba->size;
    } else {
        r_size_reg -= mfba->size;
    }
    //printf("-D- MFBA: data size: %d, reg_size: %d, r_size_reg: %d, w_size_reg: %d\n",mfba->size,reg_size,r_size_reg,w_size_reg);
    REG_ACCCESS_VAR(mf, method, REG_ID_MFBA, mfba, mfba, reg_size, r_size_reg, w_size_reg, register_access);
}

/************************************
 * Function: reg_access_mfbe
 ************************************/
reg_access_status_t reg_access_mfbe(mfile* mf, reg_access_method_t method, struct register_access_mfbe* mfbe)
{
    REG_ACCCESS(mf, method, REG_ID_MFBE, mfbe, mfbe, register_access);
}

/************************************
 * Function: reg_access_mfpa
 ************************************/
reg_access_status_t reg_access_mfpa(mfile* mf, reg_access_method_t method, struct register_access_mfpa* mfpa)
{
    REG_ACCCESS(mf, method, REG_ID_MFPA, mfpa, mfpa, register_access);
}

/************************************
 * Function: reg_access_mnva
 ************************************/
reg_access_status_t reg_access_mnva (mfile* mf, reg_access_method_t method, struct tools_open_mnva* mnva)
{
    // reg_size is in bytes
    u_int32_t reg_size = (mnva->nv_hdr.length << 2) + tools_open_nv_hdr_size();
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg= reg_size;
    if (method == REG_ACCESS_METHOD_GET) {
        w_size_reg -= mnva->nv_hdr.length << 2;
    } else {
        r_size_reg -= mnva->nv_hdr.length << 2;
    }
    REG_ACCCESS_VAR(mf, method, REG_ID_MNVA, mnva, mnva, reg_size , r_size_reg, w_size_reg, tools_open);
}

/************************************
 * Function: reg_access_mnvi
 ************************************/
reg_access_status_t reg_access_mnvi (mfile* mf, reg_access_method_t method, struct tools_open_mnvi* mnvi)
{
    if (method != REG_ACCESS_METHOD_SET ) { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVI, mnvi, mnvi, tools_open);
}

/************************************
 * Function: reg_access_mnvia
 ************************************/
reg_access_status_t reg_access_mnvia (mfile* mf, reg_access_method_t method, struct tools_open_mnvia* mnvia)
{
    if (method != REG_ACCESS_METHOD_SET ) { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVIA, mnvia, mnvia, tools_open);
}


/************************************
 *  * Function: reg_access_mgir
 *************************************/
reg_access_status_t reg_access_mgir(mfile* mf, reg_access_method_t method, struct register_access_sib_mgir* mgir)
{
    REG_ACCCESS_VAR(mf, method, REG_ID_MGIR, mgir, mgir, MGIR_REG_SIZE, MGIR_REG_SIZE, MGIR_REG_SIZE, register_access_sib);
    //REG_ACCCESS(mf, method, REG_ID_MGIR, mgir, mgir, register_access_sib);
    //}
}

/************************************
 * Function: reg_access_mfrl
 ************************************/
reg_access_status_t reg_access_mfrl (mfile* mf, reg_access_method_t method, struct cibfw_register_mfrl* mfrl)
{
    REG_ACCCESS(mf, method, REG_ID_MFRL, mfrl, mfrl, cibfw_register);
}

/************************************
 * Function: reg_access_mfai
 ************************************/
reg_access_status_t reg_access_mfai (mfile* mf, reg_access_method_t method, struct cibfw_register_mfai* mfai)
{
    if (method != REG_ACCESS_METHOD_SET) { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MFAI, mfai, mfai, cibfw_register);
}

/************************************
 * Function: reg_access_nvda
 ************************************/
reg_access_status_t reg_access_nvda (mfile* mf, reg_access_method_t method, struct tools_open_nvda* nvda)
{
    // reg_size is in bytes
    u_int32_t reg_size = nvda->nv_hdr.length + tools_open_nv_hdr_fifth_gen_size();
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg= reg_size;
    if (method == REG_ACCESS_METHOD_GET) {
        w_size_reg -= nvda->nv_hdr.length;
    } else {
        r_size_reg -= nvda->nv_hdr.length;
    }
    REG_ACCCESS_VAR(mf, method, REG_ID_MNVA, nvda, nvda, reg_size , r_size_reg, w_size_reg, tools_open);
}

/************************************
 * Function: reg_access_nvdi
 ************************************/
reg_access_status_t reg_access_nvdi (mfile* mf, reg_access_method_t method, struct tools_open_nvdi* nvdi)
{
    if (method != REG_ACCESS_METHOD_SET ) { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVI, nvdi, nvdi, tools_open);
}

/************************************
 * Function: reg_access_nvia
 ************************************/
reg_access_status_t reg_access_nvia (mfile* mf, reg_access_method_t method, struct tools_open_nvia* nvia)
{
    if (method != REG_ACCESS_METHOD_SET ) { // this register supports only set method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_NVIA, nvia, nvia, tools_open);
}

/************************************
 * Function: reg_access_nvqc
 ************************************/
reg_access_status_t reg_access_nvqc (mfile* mf, reg_access_method_t method, struct tools_open_nvqc* nvqc)
{
    if (method != REG_ACCESS_METHOD_GET ) { // this register supports only get method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_NVQC, nvqc, nvqc, tools_open);
}

/************************************
 * Function: reg_access_nvqgc
 ************************************/
reg_access_status_t reg_access_nvqgc (mfile* mf, reg_access_method_t method, struct tools_open_nvqgc* nvqgc)
{
    if (method != REG_ACCESS_METHOD_GET ) { // this register supports only get method
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_NVQGC, nvqgc, nvqgc, tools_open);
}

/************************************
 * Function: reg_access_mvts
 ************************************/
reg_access_status_t reg_access_mvts (mfile* mf, reg_access_method_t method, struct tools_open_mvts* mvts)
{
    REG_ACCCESS(mf, method, REG_ID_MVTS, mvts, mvts, tools_open);
}

/************************************
 * Function: reg_access_mnvgn
 ************************************/
reg_access_status_t reg_access_mnvgn (mfile* mf, reg_access_method_t method, struct tools_open_mnvgn* mnvgn, int *status)
{
    int data_size = tools_open_mnvgn_size();
    if (method != REG_ACCESS_METHOD_GET ) { // this register supports only get method
        return ME_REG_ACCESS_BAD_METHOD;
    }

    REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, method, REG_ID_MNVGN, mnvgn, mnvgn, data_size, data_size, data_size,\
                tools_open_mnvgn_pack, tools_open_mnvgn_unpack, tools_open_mnvgn_size,\
                tools_open_mnvgn_print, status);

    if (rc || *status) {\
        return (reg_access_status_t)rc;\
    }\
    return ME_OK;
}

/************************************
 * Function: reg_access_mfmc
 ************************************/
reg_access_status_t reg_access_mfmc (mfile* mf, reg_access_method_t method, struct tools_open_mfmc* mfmc)
{
    REG_ACCCESS(mf, method, REG_ID_MFMC, mfmc, mfmc, tools_open);
}

/************************************
 * Function: reg_access_mfpa_new
 ************************************/
reg_access_status_t reg_access_mfpa_new(mfile* mf, reg_access_method_t method, struct tools_open_mfpa* mfpa)
{
    REG_ACCCESS(mf, method, REG_ID_MFPA, mfpa, mfpa, tools_open);
}

/************************************
 * Function: reg_access_err2str
 ************************************/

const char* reg_access_err2str(reg_access_status_t status)
{
	return m_err2str(status);
}
