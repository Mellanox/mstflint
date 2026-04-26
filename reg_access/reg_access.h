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

#include <stdbool.h>

/* #include <tools_layouts/reg_access_hca_layouts.h> */
/* #include <tools_layouts/reg_access_switch_layouts.h> */
#include "reg_access_common.h"
#include "common/bit_slice.h"

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

/* Add new methods here */
struct reg_access_switch_mddq_ext;
reg_access_status_t reg_access_mddq(mfile* mf, reg_access_method_t method, struct reg_access_switch_mddq_ext* mddq);
struct reg_access_switch_mddt_reg_ext;
reg_access_status_t reg_access_mddt(mfile                                * mf,
                                    reg_access_method_t                    method,
                                    struct reg_access_switch_mddt_reg_ext* switch_mddt_reg);
struct reg_access_hca_paos_reg_ext;
reg_access_status_t reg_access_paos(mfile* mf, reg_access_method_t method, struct reg_access_hca_paos_reg_ext* paos);

struct reg_access_hca_ptys_reg_ext;
reg_access_status_t reg_access_ptys(mfile* mf, reg_access_method_t method, struct reg_access_hca_ptys_reg_ext* ptys);
struct reg_access_hca_mtmp_ext;
reg_access_status_t reg_access_mtmp(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtmp_ext* mtmp);
struct reg_access_hca_mtcap_ext;
reg_access_status_t reg_access_mtcap(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtcap_ext* mtcap);
    struct reg_access_hca_mmhi_reg_ext;
    reg_access_status_t reg_access_mmhi(mfile* mf, reg_access_method_t method, struct reg_access_hca_mmhi_reg_ext* mmhi);
struct reg_access_switch_pmaos_reg_ext;
reg_access_status_t reg_access_pmaos(mfile                                 * mf,
                                     reg_access_method_t                     method,
                                     struct reg_access_switch_pmaos_reg_ext* pmaos);
struct reg_access_hca_pmlp_reg_ext;
reg_access_status_t reg_access_pmlp(mfile* mf, reg_access_method_t method, struct reg_access_hca_pmlp_reg_ext* pmlp);
struct reg_access_hca_mnvgc_reg_ext;
reg_access_status_t reg_access_mnvgc(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mnvgc_reg_ext* mnvgc);
struct reg_access_hca_mmdio_ext;
reg_access_status_t reg_access_mmdio(mfile* mf, reg_access_method_t method, struct reg_access_hca_mmdio_ext* mmdio);
struct reg_access_hca_mpqd_reg_ext;
reg_access_status_t reg_access_mpqd(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpqd_reg_ext* mpqd);
struct tools_mjtag;
reg_access_status_t reg_access_mjtag(mfile* mf, reg_access_method_t method, struct tools_mjtag* mjtag);
struct tools_open_mnvda;
reg_access_status_t reg_access_mnvda(mfile* mf, reg_access_method_t method, struct tools_open_mnvda* mnvda);
struct tools_open_mnvdi;
reg_access_status_t reg_access_mnvdi(mfile* mf, reg_access_method_t method, struct tools_open_mnvdi* mnvdi);
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
struct switchen_ritr;
reg_access_status_t reg_access_ritr(mfile* mf, reg_access_method_t method, struct switchen_ritr* ritr);
struct switchen_ricnt;
reg_access_status_t reg_access_ricnt(mfile* mf, reg_access_method_t method, struct switchen_ricnt* ricnt);
struct switchen_sbpr;
reg_access_status_t reg_access_sbpr(mfile* mf, reg_access_method_t method, struct switchen_sbpr* sbpr);
struct switchen_sbmm;
reg_access_status_t reg_access_sbmm(mfile* mf, reg_access_method_t method, struct switchen_sbmm* sbmm);
struct switchen_sbcm;
reg_access_status_t reg_access_sbcm(mfile* mf, reg_access_method_t method, struct switchen_sbcm* sbcm);
struct switchen_sbpm;
reg_access_status_t reg_access_sbpm(mfile* mf, reg_access_method_t method, struct switchen_sbpm* sbpm);
struct reg_access_hca_resource_dump_ext;
/***********************************************************/
/*********************** ATTENTION *************************/
/** The registers below must be same (except for the ID) ***/
/** Changes in them should be made both in switch and nic **/
reg_access_status_t reg_access_res_dump(mfile                                  * mf,
                                        reg_access_method_t                      method,
                                        struct reg_access_hca_resource_dump_ext* res_dump);
reg_access_status_t reg_access_mord(mfile                                  * mf,
                                    reg_access_method_t                      method,
                                    struct reg_access_hca_resource_dump_ext* res_dump);

struct switchen_ppcnt_reg;
reg_access_status_t reg_access_ppcnt(mfile* mf, reg_access_method_t method, struct switchen_ppcnt_reg* ricnt);
struct reg_access_hca_pcnr_reg_ext;
reg_access_status_t reg_access_pcnr(mfile* mf, reg_access_method_t method, struct reg_access_hca_pcnr_reg_ext* pcnr);
struct tools_mgpir;
reg_access_status_t reg_access_mgpir(mfile* mf, reg_access_method_t method, struct tools_mgpir* mgpir);
struct tools_mdfcr;
reg_access_status_t reg_access_mdfcr(mfile* mf, reg_access_method_t method, struct tools_mdfcr* mdfcr);
struct tools_mdrcr;
reg_access_status_t reg_access_mdrcr(mfile* mf, reg_access_method_t method, struct tools_mdrcr* mdrcr);

struct reg_access_switch_icam_reg_ext;
reg_access_status_t reg_access_icam(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_icam_reg_ext* icam);
struct reg_access_switch_icsr_ext;
reg_access_status_t reg_access_icsr(mfile* mf, reg_access_method_t method, struct reg_access_switch_icsr_ext* icsr);

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
struct reg_access_switch_mfmc_reg_ext;
reg_access_status_t reg_access_mfmc(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mfmc_reg_ext* mfmc);
struct reg_access_hca_mfpa_reg_ext;
reg_access_status_t reg_access_mfpa_new(mfile* mf, reg_access_method_t method,
                                        struct reg_access_hca_mfpa_reg_ext* mfpa);
struct reg_access_hca_mcam_reg_ext;
reg_access_status_t reg_access_mcam(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcam_reg_ext* mcam);
struct reg_access_hca_mroq_ext;
reg_access_status_t reg_access_mroq(mfile* mf, reg_access_method_t method, struct reg_access_hca_mroq_ext* mroq);
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
struct reg_access_hca_mtrc_conf_reg_ext;
reg_access_status_t reg_access_mtrc_conf(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_conf_reg_ext* mtrc_conf);
struct reg_access_hca_mtrc_stdb_reg_ext;
reg_access_status_t reg_access_mtrc_stdb_wrapper(mfile* mf, u_int32_t read_size, u_int8_t string_db_index,
                                                 char* buffer);
struct reg_access_hca_mtrc_ctrl_reg_ext;
reg_access_status_t reg_access_mtrc_ctrl(mfile                                  * mf,
                                         reg_access_method_t                      method,
                                         struct reg_access_hca_mtrc_ctrl_reg_ext* mtrc_ctrl);
struct tools_open_mcdd_reg;
reg_access_status_t reg_access_mcdd(mfile* mf, reg_access_method_t method, struct tools_open_mcdd_reg* mcdd);
const char* reg_access_err2str(reg_access_status_t status);
struct tools_open_mirc_reg;
reg_access_status_t reg_access_mirc(mfile* mf, reg_access_method_t method, struct tools_open_mirc_reg* mirc);

struct reg_access_switch_plib_reg_ext;
reg_access_status_t reg_access_plib(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_plib_reg_ext* plib);

struct reg_access_hca_mteim_reg_ext;
reg_access_status_t reg_access_mteim(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mteim_reg_ext* mteim);

struct reg_access_hca_mtie_ext;
reg_access_status_t reg_access_mtie(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtie_ext* mtie);
struct reg_access_hca_mtim_ext;
reg_access_status_t reg_access_mtim(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtim_ext* mtim);
struct reg_access_hca_mtdc_ext;
reg_access_status_t reg_access_mtdc(mfile* mf, reg_access_method_t method, struct reg_access_hca_mtdc_ext* mtdc);

struct reg_access_hca_debug_cap;
reg_access_status_t reg_access_debug_cap(mfile                          * mf,
                                         reg_access_method_t              method,
                                         struct reg_access_hca_debug_cap* debug_cap);

struct reg_access_switch_mkdc_reg_ext;
reg_access_status_t reg_access_mkdc(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mkdc_reg_ext* mkdc);
struct reg_access_switch_mtcq_reg_ext;
reg_access_status_t reg_access_mtcq(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mtcq_reg_ext* mtcq);
struct reg_access_switch_mdsr_reg_ext;
reg_access_status_t reg_access_mdsr(mfile* mf, reg_access_method_t method,
                                    struct reg_access_switch_mdsr_reg_ext* mtcq);
struct reg_access_hca_nic_cap_ext_reg_ext;
reg_access_status_t reg_access_nic_cap_ext(mfile                                    * mf,
                                           reg_access_method_t                        method,
                                           struct reg_access_hca_nic_cap_ext_reg_ext* nic_cap_ext);
struct reg_access_switch_mrsr_ext;
reg_access_status_t reg_access_mrsr(mfile* mf, reg_access_method_t method, struct reg_access_switch_mrsr_ext* mrsr);

struct reg_access_hca_dtor_reg_ext;
reg_access_status_t reg_access_dtor(mfile* mf, reg_access_method_t method, struct reg_access_hca_dtor_reg_ext* dtor);

struct reg_access_hca_nic_dpa_eug_reg_ext;
reg_access_status_t reg_access_nic_dpa_eug(mfile                                    * mf,
                                           reg_access_method_t                        method,
                                           struct reg_access_hca_nic_dpa_eug_reg_ext* nic_dpa_eug);
struct reg_access_hca_mpegc_reg_ext;
reg_access_status_t reg_access_mpegc(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_mpegc_reg_ext* mpegc);

struct reg_access_hca_nic_dpa_perf_reg_ext;
reg_access_status_t reg_access_nic_dpa_perf(mfile                                     * mf,
                                            reg_access_method_t                         method,
                                            struct reg_access_hca_nic_dpa_perf_reg_ext* nic_dpa_perf);
struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext;
reg_access_status_t reg_access_nic_dpa_perf_ctrl(mfile                                          * mf,
                                                 reg_access_method_t                              method,
                                                 struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext* nic_dpa_perf_ctrl);
struct reg_access_hca_nic_dpa_eu_partition_reg_ext;
reg_access_status_t reg_access_nic_dpa_eu_partition(mfile                                             * mf,
                                                    reg_access_method_t                                 method,
                                                    struct reg_access_hca_nic_dpa_eu_partition_reg_ext* nic_dpa_eu_partition);
struct reg_access_hca_pguid_reg_ext;
reg_access_status_t reg_access_pguid(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_pguid_reg_ext* pguid);

struct reg_access_hca_mroq_ext;
reg_access_status_t reg_access_mroq(mfile* mf, reg_access_method_t method, struct reg_access_hca_mroq_ext* mroq);

struct reg_access_hca_mpir_ext;
reg_access_status_t reg_access_mpir(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpir_ext* mpir);

struct reg_access_hca_MRSV_ext;
reg_access_status_t reg_access_mrsv(mfile* mf, reg_access_method_t method, struct reg_access_hca_MRSV_ext* mrsv);

struct reg_access_hca_misoc_reg_ext;
reg_access_status_t reg_access_misoc(mfile* mf, reg_access_method_t method,
                                     struct reg_access_hca_misoc_reg_ext* misoc);

struct reg_access_hca_mpein_reg_ext;
reg_access_status_t
reg_access_mpein(mfile* mf, reg_access_method_t method, struct reg_access_hca_mpein_reg_ext* mpein);

#ifdef __cplusplus
}
#endif

#endif /* REG_ACCESS_H */
