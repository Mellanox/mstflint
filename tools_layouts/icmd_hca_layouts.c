
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2010-2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
 

/***
         *** This file was generated at "2023-01-09 15:12:36"
         *** by:
         ***    > /.autodirect/swgwork/astrutsovsky/work/4Dan/a-me_dev/adabe_plugins/adb2c/adb2pack.py --input adb/tools/icmd_hca.adb --file-prefix icmd_hca --prefix icmd_hca_ --no-adb-utils
         ***/
#include "icmd_hca_layouts.h"

void icmd_hca_counter_id_pack(const struct icmd_hca_counter_id *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->counter_id);
}

void icmd_hca_counter_id_unpack(struct icmd_hca_counter_id *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->counter_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void icmd_hca_counter_id_print(const struct icmd_hca_counter_id *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_counter_id ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "counter_id           : " UH_FMT "\n", ptr_struct->counter_id);
}

unsigned int icmd_hca_counter_id_size(void)
{
	return ICMD_HCA_COUNTER_ID_SIZE;
}

void icmd_hca_counter_id_dump(const struct icmd_hca_counter_id *ptr_struct, FILE *fd)
{
	icmd_hca_counter_id_print(ptr_struct, fd, 0);
}


void icmd_hca_debug_cap_pack(const struct icmd_hca_debug_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_max_samples);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_min_resource_dump_eq);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->resource_dump);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_cr_dump_to_mem_size);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->core_dump_qp);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->core_dump_general);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_min_sample_period);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->diag_counter_tracer_dump);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->health_mon_rx_activity);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->repetitive);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->single);
}

void icmd_hca_debug_cap_unpack(struct icmd_hca_debug_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->log_max_samples = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 11;
	ptr_struct->log_min_resource_dump_eq = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 9;
	ptr_struct->resource_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->log_cr_dump_to_mem_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 1;
	ptr_struct->core_dump_qp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->core_dump_general = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->log_min_sample_period = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 35;
	ptr_struct->diag_counter_tracer_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->health_mon_rx_activity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->repetitive = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->single = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void icmd_hca_debug_cap_print(const struct icmd_hca_debug_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_debug_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_samples      : " UH_FMT "\n", ptr_struct->log_max_samples);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_min_resource_dump_eq : " UH_FMT "\n", ptr_struct->log_min_resource_dump_eq);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_dump        : " UH_FMT "\n", ptr_struct->resource_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_cr_dump_to_mem_size : " UH_FMT "\n", ptr_struct->log_cr_dump_to_mem_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_dump_qp         : " UH_FMT "\n", ptr_struct->core_dump_qp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_dump_general    : " UH_FMT "\n", ptr_struct->core_dump_general);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_min_sample_period : " UH_FMT "\n", ptr_struct->log_min_sample_period);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "diag_counter_tracer_dump : " UH_FMT "\n", ptr_struct->diag_counter_tracer_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "health_mon_rx_activity : " UH_FMT "\n", ptr_struct->health_mon_rx_activity);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "repetitive           : " UH_FMT "\n", ptr_struct->repetitive);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "single               : " UH_FMT "\n", ptr_struct->single);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "unlimited array subnode: (diagnostic_counter)\n");
}

unsigned int icmd_hca_debug_cap_size(void)
{
	return ICMD_HCA_DEBUG_CAP_SIZE;
}

void icmd_hca_debug_cap_dump(const struct icmd_hca_debug_cap *ptr_struct, FILE *fd)
{
	icmd_hca_debug_cap_print(ptr_struct, fd, 0);
}

void icmd_hca_icmd_mh_sync_in_pack(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->state);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sync_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ignore_inactive_host);
}

void icmd_hca_icmd_mh_sync_in_unpack(struct icmd_hca_icmd_mh_sync_in *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 16;
	ptr_struct->sync_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->ignore_inactive_host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void icmd_hca_icmd_mh_sync_in_print(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_icmd_mh_sync_in ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "state                : " UH_FMT "\n", ptr_struct->state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_type            : " UH_FMT "\n", ptr_struct->sync_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ignore_inactive_host : " UH_FMT "\n", ptr_struct->ignore_inactive_host);
}

unsigned int icmd_hca_icmd_mh_sync_in_size(void)
{
	return ICMD_HCA_ICMD_MH_SYNC_IN_SIZE;
}

void icmd_hca_icmd_mh_sync_in_dump(const struct icmd_hca_icmd_mh_sync_in *ptr_struct, FILE *fd)
{
	icmd_hca_icmd_mh_sync_in_print(ptr_struct, fd, 0);
}

void icmd_hca_icmd_mh_sync_out_pack(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->state);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sync_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ignore_inactive_host);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->host_ready);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->start_uptime);
}

void icmd_hca_icmd_mh_sync_out_unpack(struct icmd_hca_icmd_mh_sync_out *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 16;
	ptr_struct->sync_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->ignore_inactive_host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 60;
	ptr_struct->host_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->start_uptime = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void icmd_hca_icmd_mh_sync_out_print(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_icmd_mh_sync_out ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "state                : " UH_FMT "\n", ptr_struct->state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_type            : " UH_FMT "\n", ptr_struct->sync_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ignore_inactive_host : " UH_FMT "\n", ptr_struct->ignore_inactive_host);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_ready           : %s (" UH_FMT ")\n", (ptr_struct->host_ready == 0 ? ("IDLE") : ((ptr_struct->host_ready == 1 ? ("READY") : ((ptr_struct->host_ready == 15 ? ("GO") : ("unknown")))))), ptr_struct->host_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "start_uptime         : " U32H_FMT "\n", ptr_struct->start_uptime);
}

unsigned int icmd_hca_icmd_mh_sync_out_size(void)
{
	return ICMD_HCA_ICMD_MH_SYNC_OUT_SIZE;
}

void icmd_hca_icmd_mh_sync_out_dump(const struct icmd_hca_icmd_mh_sync_out *ptr_struct, FILE *fd)
{
	icmd_hca_icmd_mh_sync_out_print(ptr_struct, fd, 0);
}

void icmd_hca_icmd_query_cap_general_pack(const struct icmd_hca_icmd_query_cap_general *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nic_cap_reg);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->port_state_behavior);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->virt_node_guid);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ncfg_reg);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cwcam_reg);
	offset = 13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sbcam_reg);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->capability_groups);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->virtual_link_down);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->icmd_exmb);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->capi);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->qcam_reg);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mcam_reg);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pcam_reg);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mh_sync);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->allow_icmd_access_reg_on_all_registers);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fw_info_psid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_access);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_p);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_u);
	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_m);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_b);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_a);
	offset = 58;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_g);
	offset = 57;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wol_s);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rol_g);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rol_s);
	offset = 53;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpga);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_diagnostic_counters);
}

void icmd_hca_icmd_query_cap_general_unpack(struct icmd_hca_icmd_query_cap_general *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->nic_cap_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->port_state_behavior = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->virt_node_guid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 15;
	ptr_struct->ncfg_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 14;
	ptr_struct->cwcam_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 13;
	ptr_struct->sbcam_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 11;
	ptr_struct->capability_groups = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 9;
	ptr_struct->virtual_link_down = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->icmd_exmb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 7;
	ptr_struct->capi = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->qcam_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->mcam_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->pcam_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->mh_sync = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->allow_icmd_access_reg_on_all_registers = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->fw_info_psid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->nv_access = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 63;
	ptr_struct->wol_p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->wol_u = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 61;
	ptr_struct->wol_m = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 60;
	ptr_struct->wol_b = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 59;
	ptr_struct->wol_a = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 58;
	ptr_struct->wol_g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 57;
	ptr_struct->wol_s = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 55;
	ptr_struct->rol_g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->rol_s = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 53;
	ptr_struct->fpga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->num_of_diagnostic_counters = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void icmd_hca_icmd_query_cap_general_print(const struct icmd_hca_icmd_query_cap_general *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_icmd_query_cap_general ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_cap_reg          : " UH_FMT "\n", ptr_struct->nic_cap_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_state_behavior  : " UH_FMT "\n", ptr_struct->port_state_behavior);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "virt_node_guid       : " UH_FMT "\n", ptr_struct->virt_node_guid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncfg_reg             : " UH_FMT "\n", ptr_struct->ncfg_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cwcam_reg            : " UH_FMT "\n", ptr_struct->cwcam_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sbcam_reg            : " UH_FMT "\n", ptr_struct->sbcam_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_groups    : " UH_FMT "\n", ptr_struct->capability_groups);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "virtual_link_down    : " UH_FMT "\n", ptr_struct->virtual_link_down);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icmd_exmb            : " UH_FMT "\n", ptr_struct->icmd_exmb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capi                 : " UH_FMT "\n", ptr_struct->capi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qcam_reg             : " UH_FMT "\n", ptr_struct->qcam_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcam_reg             : " UH_FMT "\n", ptr_struct->mcam_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcam_reg             : " UH_FMT "\n", ptr_struct->pcam_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mh_sync              : " UH_FMT "\n", ptr_struct->mh_sync);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "allow_icmd_access_reg_on_all_registers : " UH_FMT "\n", ptr_struct->allow_icmd_access_reg_on_all_registers);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info_psid         : " UH_FMT "\n", ptr_struct->fw_info_psid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_access            : " UH_FMT "\n", ptr_struct->nv_access);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_p                : " UH_FMT "\n", ptr_struct->wol_p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_u                : " UH_FMT "\n", ptr_struct->wol_u);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_m                : " UH_FMT "\n", ptr_struct->wol_m);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_b                : " UH_FMT "\n", ptr_struct->wol_b);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_a                : " UH_FMT "\n", ptr_struct->wol_a);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_g                : " UH_FMT "\n", ptr_struct->wol_g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol_s                : " UH_FMT "\n", ptr_struct->wol_s);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rol_g                : " UH_FMT "\n", ptr_struct->rol_g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rol_s                : " UH_FMT "\n", ptr_struct->rol_s);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga                 : " UH_FMT "\n", ptr_struct->fpga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_diagnostic_counters : " UH_FMT "\n", ptr_struct->num_of_diagnostic_counters);
}

unsigned int icmd_hca_icmd_query_cap_general_size(void)
{
	return ICMD_HCA_ICMD_QUERY_CAP_GENERAL_SIZE;
}

void icmd_hca_icmd_query_cap_general_dump(const struct icmd_hca_icmd_query_cap_general *ptr_struct, FILE *fd)
{
	icmd_hca_icmd_query_cap_general_print(ptr_struct, fd, 0);
}

void icmd_hca_icmd_query_cap_in_pack(const struct icmd_hca_icmd_query_cap_in *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->capability_group);
}

void icmd_hca_icmd_query_cap_in_unpack(struct icmd_hca_icmd_query_cap_in *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->capability_group = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void icmd_hca_icmd_query_cap_in_print(const struct icmd_hca_icmd_query_cap_in *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_icmd_query_cap_in ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_group     : %s (" UH_FMT ")\n", (ptr_struct->capability_group == 0 ? ("General_capability") : ((ptr_struct->capability_group == 1 ? ("Debug_Capability") : ("unknown")))), ptr_struct->capability_group);
}

unsigned int icmd_hca_icmd_query_cap_in_size(void)
{
	return ICMD_HCA_ICMD_QUERY_CAP_IN_SIZE;
}

void icmd_hca_icmd_query_cap_in_dump(const struct icmd_hca_icmd_query_cap_in *ptr_struct, FILE *fd)
{
	icmd_hca_icmd_query_cap_in_print(ptr_struct, fd, 0);
}

void icmd_hca_icmd_hca_Nodes_print(const union icmd_hca_icmd_hca_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== icmd_hca_icmd_hca_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icmd_query_cap_general:\n");
	icmd_hca_icmd_query_cap_general_print(&(ptr_struct->icmd_query_cap_general), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icmd_query_cap_in:\n");
	icmd_hca_icmd_query_cap_in_print(&(ptr_struct->icmd_query_cap_in), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);

	fprintf(fd, "debug_cap:\n");
	icmd_hca_debug_cap_print(&(ptr_struct->debug_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);

	fprintf(fd, "icmd_mh_sync_out:\n");
	icmd_hca_icmd_mh_sync_out_print(&(ptr_struct->icmd_mh_sync_out), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icmd_mh_sync_in:\n");
	icmd_hca_icmd_mh_sync_in_print(&(ptr_struct->icmd_mh_sync_in), fd, indent_level + 1);
}

unsigned int icmd_hca_icmd_hca_Nodes_size(void)
{
	return ICMD_HCA_ICMD_HCA_NODES_SIZE;
}

void icmd_hca_icmd_hca_Nodes_dump(const union icmd_hca_icmd_hca_Nodes *ptr_struct, FILE *fd)
{
	icmd_hca_icmd_hca_Nodes_print(ptr_struct, fd, 0);
}

