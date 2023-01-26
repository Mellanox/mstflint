/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef REG_ACCESS_H
#define REG_ACCESS_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "reg_access_common.h"

enum { /* header lengths in bytes */
    REG_ACCESS_MFBA_HEADER_LEN = 12,
};

typedef enum {
    MDDT_PRM_REGISTER_CMD_TYPE   = 0,
    MDDT_COMMAND_CMD_TYPE        = 1,
    MDDT_CRSPACE_ACCESS_CMD_TYPE = 2
} mddt_command_type_t;

/* we use the same error messages as mtcr */
typedef MError reg_access_status_t;


struct reg_access_switch_pmaos_reg_ext;
reg_access_status_t reg_access_pmaos(mfile                                 * mf,
                                     reg_access_method_t                     method,
                                     struct reg_access_switch_pmaos_reg_ext* pmaos);
struct reg_access_hca_mnvgc_reg_ext;
reg_access_status_t reg_access_mnvgc(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mnvgc_reg_ext* mnvgc);
struct reg_access_hca_mmdio_ext;
reg_access_status_t reg_access_mmdio(mfile* mf, reg_access_method_t method, struct reg_access_hca_mmdio_ext* mmdio);
struct tools_open_mnvda;
reg_access_status_t reg_access_mnvda(mfile* mf, reg_access_method_t method, struct tools_open_mnvda* mnvda);
struct reg_access_hca_mnvdi_reg_ext;
reg_access_status_t reg_access_mnvdi(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mnvdi_reg_ext* mnvdi);
struct reg_access_hca_mnvia_reg_ext;
reg_access_status_t reg_access_mnvia(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mnvia_reg_ext* mnvia);
struct reg_access_hca_mnvqc_reg_ext;
reg_access_status_t reg_access_mnvqc(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mnvqc_reg_ext* mnvqc);
struct tools_open_mnvgn;
reg_access_status_t reg_access_mnvgn(mfile* mf, reg_access_method_t method, struct tools_open_mnvgn* mnvgn,
                                     int* status);
struct tools_open_mgnle;
reg_access_status_t reg_access_mgnle(mfile                  * mf,
                                     reg_access_method_t      method,
                                     struct tools_open_mgnle* mngnle,
                                     int                    * status);
struct reg_access_hca_resource_dump_ext;
reg_access_status_t reg_access_res_dump(mfile                                  * mf,
                                        reg_access_method_t                      method,
                                        struct reg_access_hca_resource_dump_ext* res_dump);


struct reg_access_hca_mfba_reg_ext;
reg_access_status_t reg_access_mfba(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfba_reg_ext* mfba);
struct reg_access_hca_mfbe_reg_ext;
reg_access_status_t reg_access_mfbe(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfbe_reg_ext* mfbe);
struct reg_access_hca_mfpa_reg_ext;
reg_access_status_t reg_access_mfpa(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfpa_reg_ext* mfpa);
struct reg_access_hca_mfsv_reg_ext;
reg_access_status_t reg_access_mfsv(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfsv_reg_ext* mfsv);
struct reg_access_hca_mfrl_reg_ext;
reg_access_status_t reg_access_mfrl(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfrl_reg_ext* mfrl);
struct reg_access_hca_mpcir_ext;
reg_access_status_t reg_access_mpcir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpcir_ext* mpcir);
struct cibfw_register_mfai;
reg_access_status_t reg_access_mfai(mfile* mf, reg_access_method_t method, struct cibfw_register_mfai* mfai);
struct tools_open_mvts;
reg_access_status_t reg_access_mvts(mfile* mf, reg_access_method_t method, struct tools_open_mvts* mvts);
struct reg_access_hca_mfmc_reg_ext;
reg_access_status_t reg_access_mfmc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mfmc_reg_ext* mfmc);
struct reg_access_hca_mfpa_reg_ext;
reg_access_status_t reg_access_mfpa_new(mfile* mf, reg_access_method_t method,
                                        struct reg_access_hca_mfpa_reg_ext* mfpa);
struct reg_access_hca_mcam_reg_ext;
reg_access_status_t reg_access_mcam(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcam_reg_ext* mcam);
struct tools_open_mlock;
reg_access_status_t reg_access_secure_host(mfile* mf, reg_access_method_t method, struct tools_open_mlock* mlock);
/*
 * MCXX new burn commands
 */
struct reg_access_hca_mcda_reg_ext;
reg_access_status_t reg_access_mcda(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcda_reg_ext* mcda);
struct reg_access_hca_mqis_reg_ext;
reg_access_status_t reg_access_mqis(mfile* mf, reg_access_method_t method, struct reg_access_hca_mqis_reg_ext* mqis);
struct reg_access_hca_mcc_reg_ext;
reg_access_status_t reg_access_mcc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcc_reg_ext* mcc);
struct reg_access_hca_mcqs_reg_ext;
reg_access_status_t reg_access_mcqs(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcqs_reg_ext* mcqs);
struct reg_access_hca_mcqi_reg_ext;
reg_access_status_t reg_access_mcqi(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcqi_reg_ext* mcqi);
struct reg_access_hca_mgir_ext;
reg_access_status_t reg_access_mgir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mgir_ext* mgir);
struct reg_access_hca_mtrc_cap_reg_ext;
reg_access_status_t reg_access_mtrc_cap(mfile                                 * mf,
                                        reg_access_method_t                     method,
                                        struct reg_access_hca_mtrc_cap_reg_ext* mtrc_cap);
struct reg_access_hca_mtrc_stdb_reg_ext;
reg_access_status_t reg_access_mtrc_stdb(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_stdb_reg_ext* mtrc_stdb);
struct tools_open_mcdd_reg;
reg_access_status_t reg_access_mcdd(mfile* mf, reg_access_method_t method, struct tools_open_mcdd_reg* mcdd);
const char* reg_access_err2str(reg_access_status_t status);
struct tools_open_mirc_reg;
reg_access_status_t reg_access_mirc(mfile* mf, reg_access_method_t method, struct tools_open_mirc_reg* mirc);

struct reg_access_switch_mkdc_reg_ext;
reg_access_status_t reg_access_mkdc(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mkdc_reg_ext* mkdc);
struct reg_access_switch_mtcq_reg_ext;
reg_access_status_t reg_access_mtcq(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mtcq_reg_ext* mtcq);
struct reg_access_switch_mdsr_reg_ext;
reg_access_status_t reg_access_mdsr(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mdsr_reg_ext* mtcq);
struct reg_access_hca_mpegc_reg;
reg_access_status_t reg_access_mpegc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpegc_reg* mpegc);

struct reg_access_hca_pcnr_reg_ext;
reg_access_status_t reg_access_pcnr(mfile* mf, reg_access_method_t method, struct reg_access_hca_pcnr_reg_ext* pcnr);


#ifdef __cplusplus
}
#endif

#endif /* REG_ACCESS_H */
