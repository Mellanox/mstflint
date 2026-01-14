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
#include <tools_layouts/reg_access_hca_layouts.h>
#include <tools_layouts/reg_access_switch_layouts.h>
#include <tools_layouts/tools_open_layouts.h>
#include <tools_layouts/cibfw_layouts.h>

#define REG_ID_PCNR          0x5050
#define REG_ID_PAOS          0x5006
#define REG_ID_PTYS          0x5004
#define REG_ID_PMAOS         0x5012
#define REG_ID_MTMP          0x900a
#define REG_ID_MTCAP         0x9009
#define REG_ID_MIRC          0x9162
#define REG_ID_MGIR          0x9020
#define REG_ID_MMHI 		 0x904A
#define REG_ID_PMLP          0x5002
#define REG_ID_MFPA          0x9010
#define REG_ID_MFBA          0x9011
#define REG_ID_MFBE          0x9012
#define REG_ID_MFMC          0x9013
#define REG_ID_MMDIO         0x9017
#define REG_ID_MJTAG         0x901F
#define REG_ID_PMDIC         0x9021
#define REG_ID_MNVDA         0x9024
#define REG_ID_MNVDI         0x9025
#define REG_ID_MVTS          0x902c
#define REG_ID_MNVGC         0x9034
#define REG_ID_MNVIA_4TH_GEN 0x9029
#define REG_ID_MNVQC         0x9030
#define REG_ID_MNVGN         0x9035
#define REG_ID_MNVIA         0x9033
#define REG_ID_MGNLE         0x9036
#define REG_ID_MPQD          0x9700
#define REG_ID_MLCOK         0x402D
#define REG_ID_RITR          0x8002
#define REG_ID_RICNT         0x800b
#define REG_ID_PPCNT         0x5008
#define REG_ID_SBPR          0xb001
#define REG_ID_SBCM          0xb002
#define REG_ID_SBPM          0xb003
#define REG_ID_SBMM          0xb004

#define REG_ID_MTRC_CAP  0x9040
#define REG_ID_MTRC_CONF 0x9041
#define REG_ID_MTRC_STDB 0x9042
#define REG_ID_MTRC_CTRL 0x9043
#define REG_ID_DEBUG_CAP 0x8400
#define REG_ID_MCDD      0x905C
#define REG_ID_MCQS      0x9060
#define REG_ID_MCQI      0x9061
#define REG_ID_MCC       0x9062
#define REG_ID_MCDA      0x9063
#define REG_ID_MQIS      0x9064
#define REG_ID_MTCQ      0x9065
#define REG_ID_MKDC      0x9066
#define REG_ID_MCAM      0x907f
/* TODO: get correct register ID for mfrl mfai */
#define REG_ID_MFRL  0x9028
#define REG_ID_MFAI  0x9029
#define REG_ID_MPCIR 0x905a

#define REG_ID_MGPIR 0x9100
#define REG_ID_MDFCR 0x9101
#define REG_ID_MDRCR 0x9102
#define REG_ID_MDSR  0x9110
#define REG_ID_MFSV  0x9115
#define REG_ID_MTEIM 0x9118
#define REG_ID_MTIE  0x911b
#define REG_ID_MTIM  0x911c
#define REG_ID_MTDC  0x911d
#define REG_ID_PLIB  0x500a
#define REG_ID_MRSR  0x9023
#define REG_ID_DTOR  0xC00E
#define REG_ID_MRSI  0x912A

#define REG_ID_MDDT  0x9160
#define REG_ID_MDDQ  0x9161
#define REG_ID_PGUID 0x5066
#define REG_ID_MROQ  0x902F
#define REG_ID_MPIR  0x9059
#define REG_ID_MRSV  0x9164
#define REG_ID_MISOC 0x9026
#define REG_ID_MPEIN 0x9050


/* For mstdump oob feature: */
#define REG_ID_ICAM 0x387F
#define REG_ID_ICSR 0x38F0

/*================================== */
/* RESOURCE DUMP FEATURE */
#define REG_ID_RES_DUMP 0xC000
#define REG_ID_MORD     0x9153
/*================================== */
#define REG_ID_MPEGC                0x9056
#define REG_ID_NIC_CAP_EXT          0xC011
#define REG_ID_NIC_DPA_PERF         0xC013
#define REG_ID_NIC_DPA_PERF_CTRL    0xC014
#define REG_ID_NIC_DPA_EUG          0xC012
#define REG_ID_NIC_DPA_EU_PARTITION 0xC015

#define DWORD_SIZE 4
/* For MLNXOS, MGIR still limited with 44 bytes */
#define INBAND_MAX_REG_SIZE 44

#define MAX_DYNAMIC_ARRAY_SIZE_IN_BYTES 704 /* as defined by FW MAD communication */

reg_access_status_t reg_access_mddt(mfile                                * mf,
                                    reg_access_method_t                    method,
                                    struct reg_access_switch_mddt_reg_ext* switch_mddt_reg)
{
    REG_ACCCESS(mf, method, REG_ID_MDDT, switch_mddt_reg, switch_mddt_reg_ext, reg_access);
}

reg_access_status_t reg_access_mddq(mfile* mf, reg_access_method_t method, struct reg_access_switch_mddq_ext* mddq)
{
    REG_ACCCESS(mf, method, REG_ID_MDDQ, mddq, mddq_ext, reg_access_switch);
}

/************************************
* Function: reg_access_pcnr
************************************/
reg_access_status_t reg_access_pcnr(mfile* mf, reg_access_method_t method, struct reg_access_hca_pcnr_reg_ext* pcnr)
{
    REG_ACCCESS(mf, method, REG_ID_PCNR, pcnr, pcnr_reg_ext, reg_access_hca);
}


/************************************
* Function: reg_access_plib
************************************/
reg_access_status_t reg_access_plib(mfile* mf, reg_access_method_t method, struct reg_access_switch_plib_reg_ext* plib)
{
    REG_ACCCESS(mf, method, REG_ID_PLIB, plib, plib_reg_ext, reg_access_switch);
}

/************************************
* Function: reg_access_mteim
************************************/
reg_access_status_t reg_access_mteim(mfile* mf, reg_access_method_t method, struct reg_access_hca_mteim_reg_ext* mteim)
{
    REG_ACCCESS(mf, method, REG_ID_MTEIM, mteim, mteim_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtie
************************************/
reg_access_status_t reg_access_mtie(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtie_ext* mtie)
{
    REG_ACCCESS(mf, method, REG_ID_MTIE, mtie, mtie_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtim
************************************/
reg_access_status_t reg_access_mtim(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtim_ext* mtim)
{
    REG_ACCCESS(mf, method, REG_ID_MTIM, mtim, mtim_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtdc
************************************/
reg_access_status_t reg_access_mtdc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtdc_ext* mtdc)
{
    REG_ACCCESS(mf, method, REG_ID_MTDC, mtdc, mtdc_ext, reg_access_hca);
}

/************************************
* Function: reg_access_debug_cap
************************************/
reg_access_status_t reg_access_debug_cap(mfile                          * mf,
                                         reg_access_method_t              method,
                                         struct reg_access_hca_debug_cap* debug_cap)
{
    REG_ACCCESS(mf, method, REG_ID_DEBUG_CAP, debug_cap, debug_cap, reg_access_hca);
}


/************************************
* Function: reg_access_pmaos
************************************/
reg_access_status_t reg_access_pmaos(mfile                                 * mf,
                                     reg_access_method_t                     method,
                                     struct reg_access_switch_pmaos_reg_ext* pmaos_reg_ext)
{
    REG_ACCCESS(mf, method, REG_ID_PMAOS, pmaos_reg_ext, pmaos_reg_ext, reg_access_switch);
}

/************************************
* Function: reg_access_ptys
************************************/
reg_access_status_t reg_access_ptys(mfile* mf, reg_access_method_t method, struct reg_access_hca_ptys_reg_ext* ptys)
{
    REG_ACCCESS(mf, method, REG_ID_PTYS, ptys, ptys_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtmp
************************************/
reg_access_status_t reg_access_mtmp(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtmp_ext* mtmp)
{
    REG_ACCCESS(mf, method, REG_ID_MTMP, mtmp, mtmp_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtcap
************************************/
reg_access_status_t reg_access_mtcap(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtcap_ext* mtcap)
{
    REG_ACCCESS(mf, method, REG_ID_MTCAP, mtcap, mtcap_ext, reg_access_hca);
}

/************************************
* Function: reg_access_pmlp
************************************/
reg_access_status_t reg_access_pmlp(mfile* mf, reg_access_method_t method, struct reg_access_hca_pmlp_reg_ext* pmlp)
{
    REG_ACCCESS(mf, method, REG_ID_PMLP, pmlp, pmlp_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_paos
************************************/
reg_access_status_t reg_access_paos(mfile* mf, reg_access_method_t method, struct reg_access_hca_paos_reg_ext* paos)
{
    REG_ACCCESS(mf, method, REG_ID_PAOS, paos, paos_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mnvgc
************************************/
reg_access_status_t reg_access_mnvgc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mnvgc_reg_ext* mnvgc)
{
    if (method != REG_ACCESS_METHOD_GET) { /* this register supports only get method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVGC, mnvgc, mnvgc_reg_ext, reg_access_hca);
}

reg_access_status_t reg_access_mnvdi(mfile* mf, reg_access_method_t method, struct tools_open_mnvdi* mnvdi)
{
    u_int32_t reg_size = mnvdi->nv_hdr.length + tools_open_nv_hdr_fifth_gen_size();
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg = reg_size;

    if (method != REG_ACCESS_METHOD_SET) { /* this register supports only set method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS_VAR(mf, method, REG_ID_MNVDI, mnvdi, mnvdi, reg_size, r_size_reg, w_size_reg, tools_open);
}

/************************************
* Function: reg_access_nvdia
************************************/
reg_access_status_t reg_access_mnvia(mfile* mf, reg_access_method_t method, struct reg_access_hca_mnvia_reg_ext* mnvia)
{
    if (method != REG_ACCESS_METHOD_SET) { /* this register supports only set method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVIA, mnvia, mnvia_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mnvqc
************************************/
reg_access_status_t reg_access_mnvqc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mnvqc_reg_ext* mnvqc)
{
    if (method != REG_ACCESS_METHOD_GET) { /* this register supports only get method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MNVQC, mnvqc, mnvqc_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mnvgn
************************************/
reg_access_status_t reg_access_mnvgn(mfile* mf, reg_access_method_t method, struct tools_open_mnvgn* mnvgn,
                                     int* status)
{
    int data_size = tools_open_mnvgn_size();

    if (method != REG_ACCESS_METHOD_GET) { /* this register supports only get method */
        return ME_REG_ACCESS_BAD_METHOD;
    }

    REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, method, REG_ID_MNVGN, mnvgn, mnvgn, data_size, data_size, data_size,
                                       tools_open_mnvgn_pack, tools_open_mnvgn_unpack, tools_open_mnvgn_size,
                                       tools_open_mnvgn_print, status, 0);

    if (rc || *status) {
        return (reg_access_status_t)rc;
    }
    return ME_OK;
}

/************************************
* Function: reg_access_mgnle
************************************/
reg_access_status_t reg_access_mgnle(mfile* mf, reg_access_method_t method, struct tools_open_mgnle* mgnle,
                                     int* status)
{
    int data_size = tools_open_mgnle_size();

    if (method != REG_ACCESS_METHOD_GET) { /* this register supports only get method */
        return ME_REG_ACCESS_BAD_METHOD;
    }

    REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, method, REG_ID_MGNLE, mgnle, mgnle, data_size, data_size, data_size,
                                       tools_open_mgnle_pack, tools_open_mgnle_unpack, tools_open_mgnle_size,
                                       tools_open_mgnle_print, status, 0);

    if (rc || *status) {
        return (reg_access_status_t)rc;
    }

    return ME_OK;
}

/************************************
* Function: reg_access_mmdio
************************************/
reg_access_status_t reg_access_mmdio(mfile* mf, reg_access_method_t method, struct reg_access_hca_mmdio_ext* mmdio)
{
    if (method != REG_ACCESS_METHOD_SET) { /* this register supports only set method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MMDIO, mmdio, mmdio_ext, reg_access_hca);
}

/*================================================================================================================================= */
/************************************
 * * Function: reg_access_resource_dump
 * ************************************/

/***********************************************************/
/*********************** ATTENTION *************************/
/** The registers below must be same (except for the ID) ***/
/** Changes in them should be made both in switch and nic **/

reg_access_status_t reg_access_res_dump(mfile                                  * mf,
                                        reg_access_method_t                      method,
                                        struct reg_access_hca_resource_dump_ext* resource_dump)
{
    char* path_env = getenv("DUMP_DEBUG");

    if (path_env != NULL) {
        reg_access_hca_resource_dump_ext_dump(resource_dump, stdout);
    }
    REG_ACCCESS(mf, method, REG_ID_RES_DUMP, resource_dump, resource_dump_ext, reg_access_hca);
}

reg_access_status_t reg_access_mord(mfile                                  * mf,
                                    reg_access_method_t                      method,
                                    struct reg_access_hca_resource_dump_ext* resource_dump)
{
    REG_ACCCESS(mf, method, REG_ID_MORD, resource_dump, resource_dump_ext, reg_access_hca);
}
/*================================================================================================================================= */

reg_access_status_t reg_access_mnvda(mfile* mf, reg_access_method_t method, struct tools_open_mnvda* mnvda)
{
    /* reg_size is in bytes */
    u_int32_t reg_size = mnvda->nv_hdr.length + tools_open_nv_hdr_fifth_gen_size();
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg = reg_size;

    if (method == REG_ACCESS_METHOD_GET) {
        w_size_reg -= mnvda->nv_hdr.length;
    } else {
        r_size_reg -= mnvda->nv_hdr.length;
    }
    REG_ACCCESS_VAR(mf, method, REG_ID_MNVDA, mnvda, mnvda, reg_size, r_size_reg, w_size_reg, tools_open);
}

/************************************
* Function: reg_access_mgir
************************************/
reg_access_status_t reg_access_mgir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mgir_ext* mgir)
{
    if (!mf) {
        return ME_UNSUPPORTED_DEVICE;
    } else if (mf->tp == MST_MLNXOS) {
        /* Reg max size initialization according to current method. */
        mget_max_reg_size(mf, (maccess_reg_method_t)method);
        /* Get the minimum between max reg size and MGIR size. */
        u_int32_t mgir_register_size =
            (u_int32_t)mf->acc_reg_params.max_reg_size[method] > (u_int32_t)reg_access_hca_mgir_ext_size() ?
            (u_int32_t)reg_access_hca_mgir_ext_size() :
            (u_int32_t)mf->acc_reg_params.max_reg_size[method];
        REG_ACCCESS_VAR(mf, method, REG_ID_MGIR, mgir, mgir_ext, mgir_register_size, mgir_register_size,
                        mgir_register_size, reg_access_hca);
    } else {
        REG_ACCCESS(mf, method, REG_ID_MGIR, mgir, mgir_ext, reg_access_hca);
    }
}

/************************************
 * Function: reg_access_mmhi
 ************************************/
reg_access_status_t reg_access_mmhi(mfile* mf, reg_access_method_t method, struct reg_access_hca_mmhi_reg_ext* mmhi)
{
    REG_ACCCESS(mf, method, REG_ID_MMHI, mmhi, mmhi_reg_ext, reg_access_hca);
}

/************************************
 * Function: reg_access_mpqd
 ************************************/
reg_access_status_t reg_access_mpqd(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpqd_reg_ext* mpqd)
{
    REG_ACCCESS(mf, method, REG_ID_MPQD, mpqd, mpqd_reg_ext, reg_access_hca);
}

/************************************
 * Function: reg_access_mirc
 ************************************/
reg_access_status_t reg_access_mirc(mfile* mf, reg_access_method_t method, struct tools_open_mirc_reg* mirc)
{
    REG_ACCCESS(mf, method, REG_ID_MIRC, mirc, mirc_reg, tools_open);
}

/************************************
* Function: reg_access_mfba
************************************/
reg_access_status_t reg_access_mfba(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfba_reg_ext* mfba)
{
    u_int32_t reg_size = mfba->size + REG_ACCESS_MFBA_HEADER_LEN;
    /* the r/w_size_reg is for improved performance for when we send the register */
    /* via icmd , since its relatively slow si no need to write the data array from mfba struct to the device when */
    /* reading from the device and no need for reading the data array from the device when writing to the device (we */
    /* just care about the status) */
    u_int32_t r_size_reg = reg_size;
    u_int32_t w_size_reg = reg_size;

    if (method == REG_ACCESS_METHOD_GET) {
        w_size_reg -= mfba->size;
    } else {
        r_size_reg -= mfba->size;
    }
    /* printf("-D- MFBA: data size: %d, reg_size: %d, r_size_reg: %d, w_size_reg: */
    /* %d\n",mfba->size,reg_size,r_size_reg,w_size_reg); */
    REG_ACCCESS_VAR(mf, method, REG_ID_MFBA, mfba, mfba_reg_ext, reg_size, r_size_reg, w_size_reg, reg_access_hca);
}

/************************************
* Function: reg_access_mcam
************************************/
reg_access_status_t reg_access_mcam(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcam_reg_ext* mcam)
{
    REG_ACCCESS(mf, method, REG_ID_MCAM, mcam, mcam_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mcda
************************************/
reg_access_status_t reg_access_mcda(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcda_reg_ext* mcda)
{
    REG_ACCCESS(mf, method, REG_ID_MCDA, mcda, mcda_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mqis
************************************/
reg_access_status_t reg_access_mqis(mfile* mf, reg_access_method_t method, struct reg_access_hca_mqis_reg_ext* mqis)
{
    REG_ACCCESS(mf, method, REG_ID_MQIS, mqis, mqis_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtrc_cap
************************************/
reg_access_status_t reg_access_mtrc_cap(mfile                                 * mf,
                                        reg_access_method_t                     method,
                                        struct reg_access_hca_mtrc_cap_reg_ext* mtrc_cap)
{
    REG_ACCCESS(mf, method, REG_ID_MTRC_CAP, mtrc_cap, mtrc_cap_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtrc_conf
************************************/
reg_access_status_t reg_access_mtrc_conf(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_conf_reg_ext* mtrc_conf)
{
    REG_ACCCESS(mf, method, REG_ID_MTRC_CONF, mtrc_conf, mtrc_conf_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mtrc_stdb
************************************/
reg_access_status_t reg_access_mtrc_stdb(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_stdb_reg_ext* mtrc_stdb,
                                         int                                      data_array_size)
{
    REG_ACCCESS_VAR_DYNAMIC_ARR(mf, method, REG_ID_MTRC_STDB, mtrc_stdb, mtrc_stdb_reg_ext, reg_access_hca,
                                data_array_size);
}

reg_access_status_t reg_access_mtrc_stdb_wrapper(mfile* mf, u_int32_t read_size, u_int8_t string_db_index,
                                                 char* buffer)
{
    int max_num_of_bytes = 704;
    int iterations = read_size / max_num_of_bytes;
    int read_bytes = 0;
    int index = 0;
    int num_bytes_to_read = max_num_of_bytes;

    if (read_size % 64 != 0) {
        return ME_BAD_PARAMS;
    }

    for (index = 0; index < iterations + 1; index++) {
        struct reg_access_hca_mtrc_stdb_reg_ext mtrc_stdb;
        if (index == iterations) {
            num_bytes_to_read = read_size % max_num_of_bytes;
            if (num_bytes_to_read == 0) {
                break;
            }
        }
        mtrc_stdb.read_size = num_bytes_to_read;
        mtrc_stdb.string_db_index = string_db_index;
        mtrc_stdb.start_offset = max_num_of_bytes * index;
        mtrc_stdb.string_db_data = (u_int32_t*)malloc(num_bytes_to_read);
        if (!mtrc_stdb.string_db_data) {
            fprintf(stderr, "Failed to allocate memory\n");
            return ME_MEM_ERROR;
        }
        memset(mtrc_stdb.string_db_data, 0, num_bytes_to_read);
        reg_access_status_t rc = reg_access_mtrc_stdb(mf, REG_ACCESS_METHOD_GET, &mtrc_stdb, num_bytes_to_read);

        if (rc) {
            free(mtrc_stdb.string_db_data);
            return rc;
        }
        memcpy(&buffer[read_bytes], mtrc_stdb.string_db_data, num_bytes_to_read);
        free(mtrc_stdb.string_db_data);
        read_bytes += num_bytes_to_read;
    }
    return 0;
}

/************************************
* Function: reg_access_mtrc_ctrl
************************************/
reg_access_status_t reg_access_mtrc_ctrl(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_ctrl_reg_ext* mtrc_ctrl)
{
    REG_ACCCESS(mf, method, REG_ID_MTRC_CTRL, mtrc_ctrl, mtrc_ctrl_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mcc
************************************/
reg_access_status_t reg_access_mcc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcc_reg_ext* mcc)
{
    REG_ACCCESS(mf, method, REG_ID_MCC, mcc, mcc_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mcqs
************************************/
reg_access_status_t reg_access_mcqs_inner(mfile                             * mf,
                                          reg_access_method_t                 method,
                                          struct reg_access_hca_mcqs_reg_ext* mcqs)
{
    REG_ACCCESS(mf, method, REG_ID_MCQS, mcqs, mcqs_reg_ext, reg_access_hca);
}

reg_access_status_t reg_access_mcqs(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcqs_reg_ext* mcqs)
{
    reg_access_status_t ret = reg_access_mcqs_inner(mf, method, mcqs);
    char              * path_env = getenv("MCQS_DEBUG");

    if (path_env != NULL) {
        printf("-I- MCQS: Recieved data --\n");
        reg_access_hca_mcqs_reg_ext_dump(mcqs, stdout);
    }

    return ret;
}
/************************************
* Function: reg_access_mcqi
************************************/
reg_access_status_t reg_access_mcqi_inner(mfile                             * mf,
                                          reg_access_method_t                 method,
                                          struct reg_access_hca_mcqi_reg_ext* mcqi)
{
    REG_ACCCESS(mf, method, REG_ID_MCQI, mcqi, mcqi_reg_ext, reg_access_hca);
}

reg_access_status_t reg_access_mcqi(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcqi_reg_ext* mcqi)
{
    reg_access_status_t ret = reg_access_mcqi_inner(mf, method, mcqi);
    char              * path_env = getenv("MCQI_DEBUG");

    if (path_env != NULL) {
        printf("-I- MCQI: Recieved data --\n");
        reg_access_hca_mcqi_reg_ext_dump(mcqi, stdout);
    }
    return ret;
}

/************************************
* Function: reg_access_mfbe
************************************/
reg_access_status_t reg_access_mfbe(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfbe_reg_ext* mfbe)
{
    REG_ACCCESS(mf, method, REG_ID_MFBE, mfbe, mfbe_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mfpa
************************************/
reg_access_status_t reg_access_mfpa(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfpa_reg_ext* mfpa)
{
    REG_ACCCESS(mf, method, REG_ID_MFPA, mfpa, mfpa_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mfsv
************************************/
reg_access_status_t reg_access_mfsv(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfsv_reg_ext* mfsv)
{
    REG_ACCCESS(mf, method, REG_ID_MFSV, mfsv, mfsv_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mfrl
************************************/
reg_access_status_t reg_access_mfrl(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfrl_reg_ext* mfrl)
{
    REG_ACCCESS(mf, method, REG_ID_MFRL, mfrl, mfrl_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mpcir
************************************/
reg_access_status_t reg_access_mpcir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpcir_ext* mpcir)
{
    REG_ACCCESS(mf, method, REG_ID_MPCIR, mpcir, mpcir_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mfai
************************************/
reg_access_status_t reg_access_mfai(mfile* mf, reg_access_method_t method, struct cibfw_register_mfai* mfai)
{
    if (method != REG_ACCESS_METHOD_SET) { /* this register supports only set method */
        return ME_REG_ACCESS_BAD_METHOD;
    }
    REG_ACCCESS(mf, method, REG_ID_MFAI, mfai, mfai, cibfw_register);
}

/************************************
* Function: reg_access_mvts
************************************/
reg_access_status_t reg_access_mvts(mfile* mf, reg_access_method_t method, struct tools_open_mvts* mvts)
{
    REG_ACCCESS(mf, method, REG_ID_MVTS, mvts, mvts, tools_open);
}

/************************************
* Function: reg_access_mfmc
************************************/
reg_access_status_t reg_access_mfmc(mfile* mf, reg_access_method_t method, struct reg_access_switch_mfmc_reg_ext* mfmc)
{
    REG_ACCCESS(mf, method, REG_ID_MFMC, mfmc, mfmc_reg_ext, reg_access_switch);
}

/************************************
* Function: reg_access_mfmc
************************************/
reg_access_status_t reg_access_mcdd(mfile* mf, reg_access_method_t method, struct tools_open_mcdd_reg* mcdd)
{
    REG_ACCCESS(mf, method, REG_ID_MCDD, mcdd, mcdd_reg, tools_open);
}
/************************************
* Function: reg_access_mfpa_new
************************************/
reg_access_status_t reg_access_mfpa_new(mfile* mf, reg_access_method_t method,
                                        struct reg_access_hca_mfpa_reg_ext* mfpa)
{
    REG_ACCCESS(mf, method, REG_ID_MFPA, mfpa, mfpa_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_secure_host
************************************/
reg_access_status_t reg_access_secure_host(mfile* mf, reg_access_method_t method, struct tools_open_mlock* mlock)
{
    REG_ACCCESS(mf, method, REG_ID_MLCOK, mlock, mlock, tools_open);
}
/************************************
* Function: reg_access_err2str
************************************/
const char* reg_access_err2str(reg_access_status_t status)
{
    return m_err2str(status);
}
/************************************
* Function: reg_access_mtcq
************************************/
reg_access_status_t reg_access_mtcq(mfile* mf, reg_access_method_t method, struct reg_access_switch_mtcq_reg_ext* mtcq)
{
    REG_ACCCESS(mf, method, REG_ID_MTCQ, mtcq, mtcq_reg_ext, reg_access_switch);
}
/************************************
* Function: reg_access_mdsr
************************************/
reg_access_status_t reg_access_mdsr(mfile* mf, reg_access_method_t method, struct reg_access_switch_mdsr_reg_ext* mdsr)
{
    REG_ACCCESS(mf, method, REG_ID_MDSR, mdsr, mdsr_reg_ext, reg_access_switch);
}
/************************************
* Function: reg_access_mkdc
************************************/
reg_access_status_t reg_access_mkdc(mfile* mf, reg_access_method_t method, struct reg_access_switch_mkdc_reg_ext* mkdc)
{
    REG_ACCCESS(mf, method, REG_ID_MKDC, mkdc, mkdc_reg_ext, reg_access_switch);
}
/************************************
* Function: reg_access_nic_cap_ext
************************************/
reg_access_status_t reg_access_nic_cap_ext(mfile                                    * mf,
                                           reg_access_method_t                        method,
                                           struct reg_access_hca_nic_cap_ext_reg_ext* nic_cap_ext)
{
    REG_ACCCESS(mf, method, REG_ID_NIC_CAP_EXT, nic_cap_ext, nic_cap_ext_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_nic_dpa_eug
************************************/
reg_access_status_t reg_access_nic_dpa_eug(mfile                                    * mf,
                                           reg_access_method_t                        method,
                                           struct reg_access_hca_nic_dpa_eug_reg_ext* nic_dpa_eug)
{
    REG_ACCCESS(mf, method, REG_ID_NIC_DPA_EUG, nic_dpa_eug, nic_dpa_eug_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_nic_dpa_perf_ctrl
************************************/
reg_access_status_t reg_access_nic_dpa_perf_ctrl(mfile                                          * mf,
                                                 reg_access_method_t                              method,
                                                 struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext* nic_dpa_perf_ctrl)
{
    REG_ACCCESS(mf, method, REG_ID_NIC_DPA_PERF_CTRL, nic_dpa_perf_ctrl, nic_dpa_perf_ctrl_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mpegc
************************************/
reg_access_status_t reg_access_mpegc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpegc_reg_ext* mpegc)
{
    /*    reg_access_hca_mpegc_reg_dump(mpegc, stdout)s; */
    REG_ACCCESS(mf, method, REG_ID_MPEGC, mpegc, mpegc_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_nic_dpa_eu_partition
************************************/
reg_access_status_t reg_access_nic_dpa_eu_partition(mfile                                             * mf,
                                                    reg_access_method_t                                 method,
                                                    struct reg_access_hca_nic_dpa_eu_partition_reg_ext* nic_dpa_eu_partition)
{
    REG_ACCCESS(mf, method, REG_ID_NIC_DPA_EU_PARTITION, nic_dpa_eu_partition, nic_dpa_eu_partition_reg_ext,
                reg_access_hca);
}

/************************************
* Function: reg_access_mrsr
************************************/
reg_access_status_t reg_access_mrsr(mfile* mf, reg_access_method_t method, struct reg_access_switch_mrsr_ext* mrsr)
{
    REG_ACCCESS(mf, method, REG_ID_MRSR, mrsr, mrsr_ext, reg_access_switch);
}

/************************************
* Function: reg_access_dtor
************************************/
reg_access_status_t reg_access_dtor(mfile* mf, reg_access_method_t method, struct reg_access_hca_dtor_reg_ext* dtor)
{
    REG_ACCCESS(mf, method, REG_ID_DTOR, dtor, dtor_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mrsi
************************************/
reg_access_status_t reg_access_mrsi(mfile* mf, reg_access_method_t method, struct reg_access_hca_mrsi_ext* mrsi)
{
    REG_ACCCESS(mf, method, REG_ID_MRSI, mrsi, mrsi_ext, reg_access_hca);
}

/************************************
* Function: reg_access_pguid
************************************/
reg_access_status_t reg_access_pguid(mfile* mf, reg_access_method_t method, struct reg_access_hca_pguid_reg_ext* pguid)
{
    REG_ACCCESS(mf, method, REG_ID_PGUID, pguid, pguid_reg_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mroq
************************************/
reg_access_status_t reg_access_mroq(mfile* mf, reg_access_method_t method, struct reg_access_hca_mroq_ext* mroq)
{
    REG_ACCCESS(mf, method, REG_ID_MROQ, mroq, mroq_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mpir
************************************/
reg_access_status_t reg_access_mpir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpir_ext* mpir)
{
    REG_ACCCESS(mf, method, REG_ID_MPIR, mpir, mpir_ext, reg_access_hca);
}

/************************************
* Function: reg_access_mrsv
************************************/
reg_access_status_t reg_access_mrsv(mfile* mf, reg_access_method_t method, struct reg_access_hca_MRSV_ext* mrsv)
{
    REG_ACCCESS(mf, method, REG_ID_MRSV, mrsv, MRSV_ext, reg_access_hca);
}

/************************************
* Function: reg_access_misoc
************************************/
reg_access_status_t reg_access_misoc(mfile* mf, reg_access_method_t method, struct reg_access_hca_misoc_reg_ext* misoc)
{
    REG_ACCCESS(mf, method, REG_ID_MISOC, misoc, misoc_reg_ext, reg_access_hca);
}

reg_access_status_t reg_access_mpein(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpein_reg_ext* mpein)
{
    REG_ACCCESS(mf, method, REG_ID_MPEIN, mpein, mpein_reg_ext, reg_access_hca);
}
