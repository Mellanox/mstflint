
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
 

/***
         *** This file was generated at "2021-11-23 23:46:24"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/hca/int/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_ --no-adb-utils
         ***/
#include "reg_access_hca_layouts.h"

void reg_access_hca_lock_source_general_semaphore_pack(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_toggle_cycle);
}

void reg_access_hca_lock_source_general_semaphore_unpack(struct reg_access_hca_lock_source_general_semaphore *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->log_toggle_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_lock_source_general_semaphore_print(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lock_source_general_semaphore ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("QPC_GW") : ((ptr_struct->type == 1 ? ("CQE_GW") : ((ptr_struct->type == 2 ? ("EQE_GW") : ((ptr_struct->type == 3 ? ("MEM_GW") : ((ptr_struct->type == 4 ? ("IPC") : ("unknown")))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_toggle_cycle     : " UH_FMT "\n", ptr_struct->log_toggle_cycle);
}

unsigned int reg_access_hca_lock_source_general_semaphore_size(void)
{
	return REG_ACCESS_HCA_LOCK_SOURCE_GENERAL_SEMAPHORE_SIZE;
}

void reg_access_hca_lock_source_general_semaphore_dump(const struct reg_access_hca_lock_source_general_semaphore *ptr_struct, FILE *fd)
{
	reg_access_hca_lock_source_general_semaphore_print(ptr_struct, fd, 0);
}

void reg_access_hca_lock_source_icm_resource_pack(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->gvmi);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_toggle_cycle);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->index);
}

void reg_access_hca_lock_source_icm_resource_unpack(struct reg_access_hca_lock_source_icm_resource *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->gvmi = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->log_toggle_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_hca_lock_source_icm_resource_print(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lock_source_icm_resource ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gvmi                 : " UH_FMT "\n", ptr_struct->gvmi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_toggle_cycle     : " UH_FMT "\n", ptr_struct->log_toggle_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index                : " UH_FMT "\n", ptr_struct->index);
}

unsigned int reg_access_hca_lock_source_icm_resource_size(void)
{
	return REG_ACCESS_HCA_LOCK_SOURCE_ICM_RESOURCE_SIZE;
}

void reg_access_hca_lock_source_icm_resource_dump(const struct reg_access_hca_lock_source_icm_resource *ptr_struct, FILE *fd)
{
	reg_access_hca_lock_source_icm_resource_print(ptr_struct, fd, 0);
}

void reg_access_hca_lock_source_uapp_resource_pack(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->gvmi);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_toggle_cycle);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->index);
}

void reg_access_hca_lock_source_uapp_resource_unpack(struct reg_access_hca_lock_source_uapp_resource *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->gvmi = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->log_toggle_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_hca_lock_source_uapp_resource_print(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lock_source_uapp_resource ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("UAPP_QP") : ((ptr_struct->type == 1 ? ("SRQ") : ((ptr_struct->type == 2 ? ("UAPP_SRQ_META") : ((ptr_struct->type == 3 ? ("UAPP_RES_CQ") : ((ptr_struct->type == 4 ? ("UAPP_REQ_CQ") : ((ptr_struct->type == 5 ? ("UAPP_EQ") : ((ptr_struct->type == 6 ? ("NSQ") : ((ptr_struct->type == 7 ? ("NCQ") : ("unknown")))))))))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gvmi                 : " UH_FMT "\n", ptr_struct->gvmi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_toggle_cycle     : " UH_FMT "\n", ptr_struct->log_toggle_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index                : " UH_FMT "\n", ptr_struct->index);
}

unsigned int reg_access_hca_lock_source_uapp_resource_size(void)
{
	return REG_ACCESS_HCA_LOCK_SOURCE_UAPP_RESOURCE_SIZE;
}

void reg_access_hca_lock_source_uapp_resource_dump(const struct reg_access_hca_lock_source_uapp_resource *ptr_struct, FILE *fd)
{
	reg_access_hca_lock_source_uapp_resource_print(ptr_struct, fd, 0);
}

void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_pack(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_lock_source_general_semaphore_pack(&(ptr_struct->lock_source_general_semaphore), ptr_buff);
}

void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_unpack(union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_lock_source_general_semaphore_unpack(&(ptr_struct->lock_source_general_semaphore), ptr_buff);
}

void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_print(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock_source_general_semaphore:\n");
	reg_access_hca_lock_source_general_semaphore_print(&(ptr_struct->lock_source_general_semaphore), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock_source_icm_resource:\n");
	reg_access_hca_lock_source_icm_resource_print(&(ptr_struct->lock_source_icm_resource), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock_source_uapp_resource:\n");
	reg_access_hca_lock_source_uapp_resource_print(&(ptr_struct->lock_source_uapp_resource), fd, indent_level + 1);
}

unsigned int reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_size(void)
{
	return REG_ACCESS_HCA_LOCK_SOURCE_STOP_TOGGLE_MODIFIER_CATEGORY_MODIFIER_AUTO_SIZE;
}

void reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_dump(const union reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto *ptr_struct, FILE *fd)
{
	reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_print(ptr_struct, fd, 0);
}

void reg_access_hca_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void reg_access_hca_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int reg_access_hca_uint64_size(void)
{
	return REG_ACCESS_HCA_UINT64_SIZE;
}

void reg_access_hca_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	reg_access_hca_uint64_print(ptr_struct, fd, 0);
}

void reg_access_hca_irisc_hang_mini_flow_modifier_pack(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->irisc_hang_mask);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->irisc_hang_cap_mask);
}

void reg_access_hca_irisc_hang_mini_flow_modifier_unpack(struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->irisc_hang_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->irisc_hang_cap_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_irisc_hang_mini_flow_modifier_print(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_irisc_hang_mini_flow_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "irisc_hang_mask      : " U32H_FMT "\n", ptr_struct->irisc_hang_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "irisc_hang_cap_mask  : " U32H_FMT "\n", ptr_struct->irisc_hang_cap_mask);
}

unsigned int reg_access_hca_irisc_hang_mini_flow_modifier_size(void)
{
	return REG_ACCESS_HCA_IRISC_HANG_MINI_FLOW_MODIFIER_SIZE;
}

void reg_access_hca_irisc_hang_mini_flow_modifier_dump(const struct reg_access_hca_irisc_hang_mini_flow_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_irisc_hang_mini_flow_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_lock_source_stop_toggle_modifier_pack(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->category);
	offset = 32;
	reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_pack(&(ptr_struct->category_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_lock_source_stop_toggle_modifier_unpack(struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->category = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_unpack(&(ptr_struct->category_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_lock_source_stop_toggle_modifier_print(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lock_source_stop_toggle_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "category             : %s (" UH_FMT ")\n", (ptr_struct->category == 0 ? ("GENERAL_SEMAPHORE") : ((ptr_struct->category == 1 ? ("ICM_RESOURCE") : ((ptr_struct->category == 2 ? ("UAPP_RESOURCE") : ("unknown")))))), ptr_struct->category);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "category_modifier:\n");
	reg_access_hca_lock_source_stop_toggle_modifier_category_modifier_auto_print(&(ptr_struct->category_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_lock_source_stop_toggle_modifier_size(void)
{
	return REG_ACCESS_HCA_LOCK_SOURCE_STOP_TOGGLE_MODIFIER_SIZE;
}

void reg_access_hca_lock_source_stop_toggle_modifier_dump(const struct reg_access_hca_lock_source_stop_toggle_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_lock_source_stop_toggle_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_activation_method_pack(const struct reg_access_hca_mcqi_activation_method *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->all_hosts_sync);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->auto_activate);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_fw_reset);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_reboot);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_dc_power_cycle);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_ac_power_cycle);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->self_activation);
}

void reg_access_hca_mcqi_activation_method_unpack(struct reg_access_hca_mcqi_activation_method *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->all_hosts_sync = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->auto_activate = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->pending_fw_reset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 28;
	ptr_struct->pending_server_reboot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 27;
	ptr_struct->pending_server_dc_power_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->pending_server_ac_power_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->self_activation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mcqi_activation_method_print(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_activation_method ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "all_hosts_sync       : " UH_FMT "\n", ptr_struct->all_hosts_sync);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "auto_activate        : " UH_FMT "\n", ptr_struct->auto_activate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_fw_reset     : " UH_FMT "\n", ptr_struct->pending_fw_reset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_server_reboot : " UH_FMT "\n", ptr_struct->pending_server_reboot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_server_dc_power_cycle : " UH_FMT "\n", ptr_struct->pending_server_dc_power_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_server_ac_power_cycle : " UH_FMT "\n", ptr_struct->pending_server_ac_power_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "self_activation      : " UH_FMT "\n", ptr_struct->self_activation);
}

unsigned int reg_access_hca_mcqi_activation_method_size(void)
{
	return REG_ACCESS_HCA_MCQI_ACTIVATION_METHOD_SIZE;
}

void reg_access_hca_mcqi_activation_method_dump(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_activation_method_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_cap_pack(const struct reg_access_hca_mcqi_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_info_bitmask);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_component_size);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->mcda_max_write_size);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_mcda_word_size);
	offset = 133;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_base_guid_mac);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->check_user_timestamp);
	offset = 131;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_psid);
	offset = 130;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_chip_id);
	offset = 129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_updates_only);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rd_en);
}

void reg_access_hca_mcqi_cap_unpack(struct reg_access_hca_mcqi_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->supported_info_bitmask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->max_component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 112;
	ptr_struct->mcda_max_write_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->log_mcda_word_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 133;
	ptr_struct->match_base_guid_mac = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 132;
	ptr_struct->check_user_timestamp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 131;
	ptr_struct->match_psid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 130;
	ptr_struct->match_chip_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 129;
	ptr_struct->signed_updates_only = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	ptr_struct->rd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mcqi_cap_print(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported_info_bitmask : " U32H_FMT "\n", ptr_struct->supported_info_bitmask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_size       : " U32H_FMT "\n", ptr_struct->component_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_component_size   : " U32H_FMT "\n", ptr_struct->max_component_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcda_max_write_size  : " UH_FMT "\n", ptr_struct->mcda_max_write_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_mcda_word_size   : " UH_FMT "\n", ptr_struct->log_mcda_word_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "match_base_guid_mac  : " UH_FMT "\n", ptr_struct->match_base_guid_mac);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "check_user_timestamp : " UH_FMT "\n", ptr_struct->check_user_timestamp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "match_psid           : " UH_FMT "\n", ptr_struct->match_psid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "match_chip_id        : " UH_FMT "\n", ptr_struct->match_chip_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_updates_only  : " UH_FMT "\n", ptr_struct->signed_updates_only);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rd_en                : " UH_FMT "\n", ptr_struct->rd_en);
}

unsigned int reg_access_hca_mcqi_cap_size(void)
{
	return REG_ACCESS_HCA_MCQI_CAP_SIZE;
}

void reg_access_hca_mcqi_cap_dump(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_cap_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_linkx_properties_pack(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_image_status_bitmap);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_image_info_bitmap);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_a_minor);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_a_major);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->image_a_subminor);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_b_minor);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_b_major);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->image_b_subminor);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->factory_image_minor);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->factory_image_major);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->factory_image_subminor);
	offset = 250;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->management_interface_protocol);
	offset = 242;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->activation_type);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vendor_sn);
}

void reg_access_hca_mcqi_linkx_properties_unpack(struct reg_access_hca_mcqi_linkx_properties *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->fw_image_status_bitmap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->fw_image_info_bitmap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->image_a_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->image_a_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->image_a_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 120;
	ptr_struct->image_b_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->image_b_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->image_b_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 184;
	ptr_struct->factory_image_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 176;
	ptr_struct->factory_image_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 208;
	ptr_struct->factory_image_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 250;
	ptr_struct->management_interface_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 242;
	ptr_struct->activation_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 272;
	ptr_struct->vendor_sn = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_hca_mcqi_linkx_properties_print(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_linkx_properties ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_image_status_bitmap : " UH_FMT "\n", ptr_struct->fw_image_status_bitmap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_image_info_bitmap : " UH_FMT "\n", ptr_struct->fw_image_info_bitmap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_a_minor        : " UH_FMT "\n", ptr_struct->image_a_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_a_major        : " UH_FMT "\n", ptr_struct->image_a_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_a_subminor     : " UH_FMT "\n", ptr_struct->image_a_subminor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_b_minor        : " UH_FMT "\n", ptr_struct->image_b_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_b_major        : " UH_FMT "\n", ptr_struct->image_b_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_b_subminor     : " UH_FMT "\n", ptr_struct->image_b_subminor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "factory_image_minor  : " UH_FMT "\n", ptr_struct->factory_image_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "factory_image_major  : " UH_FMT "\n", ptr_struct->factory_image_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "factory_image_subminor : " UH_FMT "\n", ptr_struct->factory_image_subminor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "management_interface_protocol : " UH_FMT "\n", ptr_struct->management_interface_protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "activation_type      : " UH_FMT "\n", ptr_struct->activation_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vendor_sn            : " UH_FMT "\n", ptr_struct->vendor_sn);
}

unsigned int reg_access_hca_mcqi_linkx_properties_size(void)
{
	return REG_ACCESS_HCA_MCQI_LINKX_PROPERTIES_SIZE;
}

void reg_access_hca_mcqi_linkx_properties_dump(const struct reg_access_hca_mcqi_linkx_properties *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_linkx_properties_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_version_pack(const struct reg_access_hca_mcqi_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_string_length);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->user_defined_time_valid);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->build_time_valid);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->build_time);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->user_defined_time);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->build_tool_version);
	for (i = 0; i < 92; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 992, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_string[i]);
	}
}

void reg_access_hca_mcqi_version_unpack(struct reg_access_hca_mcqi_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->version_string_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 3;
	ptr_struct->user_defined_time_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->build_time_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->build_time = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->user_defined_time = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 192;
	ptr_struct->build_tool_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 92; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 992, 1);
		ptr_struct->version_string[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_mcqi_version_print(const struct reg_access_hca_mcqi_version *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_string_length : " UH_FMT "\n", ptr_struct->version_string_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "user_defined_time_valid : " UH_FMT "\n", ptr_struct->user_defined_time_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build_time_valid     : " UH_FMT "\n", ptr_struct->build_time_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " U32H_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build_time           : " U64H_FMT "\n", ptr_struct->build_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "user_defined_time    : " U64H_FMT "\n", ptr_struct->user_defined_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build_tool_version   : " U32H_FMT "\n", ptr_struct->build_tool_version);
	for (i = 0; i < 92; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "version_string_%03d  : " UH_FMT "\n", i, ptr_struct->version_string[i]);
	}
}

unsigned int reg_access_hca_mcqi_version_size(void)
{
	return REG_ACCESS_HCA_MCQI_VERSION_SIZE;
}

void reg_access_hca_mcqi_version_dump(const struct reg_access_hca_mcqi_version *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_version_print(ptr_struct, fd, 0);
}

void reg_access_hca_packet_drop_mini_flow_modifier_pack(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_packets);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_number);
}

void reg_access_hca_packet_drop_mini_flow_modifier_unpack(struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->num_packets = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->port_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_packet_drop_mini_flow_modifier_print(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_packet_drop_mini_flow_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_packets          : " UH_FMT "\n", ptr_struct->num_packets);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_number          : %s (" UH_FMT ")\n", (ptr_struct->port_number == 1 ? ("port_number1") : ((ptr_struct->port_number == 2 ? ("port_number2") : ("unknown")))), ptr_struct->port_number);
}

unsigned int reg_access_hca_packet_drop_mini_flow_modifier_size(void)
{
	return REG_ACCESS_HCA_PACKET_DROP_MINI_FLOW_MODIFIER_SIZE;
}

void reg_access_hca_packet_drop_mini_flow_modifier_dump(const struct reg_access_hca_packet_drop_mini_flow_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_packet_drop_mini_flow_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_pause_tx_stop_toggle_modifier_pack(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sl_prio_mask);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_number);
}

void reg_access_hca_pause_tx_stop_toggle_modifier_unpack(struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->sl_prio_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->port_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_pause_tx_stop_toggle_modifier_print(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pause_tx_stop_toggle_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sl_prio_mask         : %s (" UH_FMT ")\n", (ptr_struct->sl_prio_mask == 1 ? ("SL_PRIO_0") : ((ptr_struct->sl_prio_mask == 2 ? ("SL_PRIO_1") : ((ptr_struct->sl_prio_mask == 4 ? ("SL_PRIO_2") : ((ptr_struct->sl_prio_mask == 8 ? ("SL_PRIO_3") : ((ptr_struct->sl_prio_mask == 16 ? ("SL_PRIO_4") : ((ptr_struct->sl_prio_mask == 32 ? ("SL_PRIO_5") : ((ptr_struct->sl_prio_mask == 64 ? ("SL_PRIO_6") : ((ptr_struct->sl_prio_mask == 128 ? ("SL_PRIO_7") : ("unknown")))))))))))))))), ptr_struct->sl_prio_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_number          : %s (" UH_FMT ")\n", (ptr_struct->port_number == 1 ? ("port_number1") : ((ptr_struct->port_number == 2 ? ("port_number2") : ("unknown")))), ptr_struct->port_number);
}

unsigned int reg_access_hca_pause_tx_stop_toggle_modifier_size(void)
{
	return REG_ACCESS_HCA_PAUSE_TX_STOP_TOGGLE_MODIFIER_SIZE;
}

void reg_access_hca_pause_tx_stop_toggle_modifier_dump(const struct reg_access_hca_pause_tx_stop_toggle_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_pause_tx_stop_toggle_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_rom_version_pack(const struct reg_access_hca_rom_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->build);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
}

void reg_access_hca_rom_version_unpack(struct reg_access_hca_rom_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->build = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_rom_version_print(const struct reg_access_hca_rom_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_rom_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build                : " UH_FMT "\n", ptr_struct->build);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
}

unsigned int reg_access_hca_rom_version_size(void)
{
	return REG_ACCESS_HCA_ROM_VERSION_SIZE;
}

void reg_access_hca_rom_version_dump(const struct reg_access_hca_rom_version *ptr_struct, FILE *fd)
{
	reg_access_hca_rom_version_print(ptr_struct, fd, 0);
}

void reg_access_hca_rxb_hang_stop_toggle_modifier_pack(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vl_tc_mask);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_number);
}

void reg_access_hca_rxb_hang_stop_toggle_modifier_unpack(struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->vl_tc_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->port_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_rxb_hang_stop_toggle_modifier_print(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_rxb_hang_stop_toggle_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_tc_mask           : %s (" UH_FMT ")\n", (ptr_struct->vl_tc_mask == 1 ? ("VL_TC_0") : ((ptr_struct->vl_tc_mask == 2 ? ("VL_TC_1") : ((ptr_struct->vl_tc_mask == 4 ? ("VL_TC_2") : ((ptr_struct->vl_tc_mask == 8 ? ("VL_TC_3") : ((ptr_struct->vl_tc_mask == 16 ? ("VL_TC_4") : ((ptr_struct->vl_tc_mask == 32 ? ("VL_TC_5") : ((ptr_struct->vl_tc_mask == 64 ? ("VL_TC_6") : ((ptr_struct->vl_tc_mask == 128 ? ("VL_TC_7") : ((ptr_struct->vl_tc_mask == 32768 ? ("VL_TC_15") : ("unknown")))))))))))))))))), ptr_struct->vl_tc_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_number          : %s (" UH_FMT ")\n", (ptr_struct->port_number == 1 ? ("port_number1") : ((ptr_struct->port_number == 2 ? ("port_number2") : ("unknown")))), ptr_struct->port_number);
}

unsigned int reg_access_hca_rxb_hang_stop_toggle_modifier_size(void)
{
	return REG_ACCESS_HCA_RXB_HANG_STOP_TOGGLE_MODIFIER_SIZE;
}

void reg_access_hca_rxb_hang_stop_toggle_modifier_dump(const struct reg_access_hca_rxb_hang_stop_toggle_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_rxb_hang_stop_toggle_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_rxp_hang_stop_toggle_modifier_pack(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vl_tc_mask);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_number);
}

void reg_access_hca_rxp_hang_stop_toggle_modifier_unpack(struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->vl_tc_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 14;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->port_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_rxp_hang_stop_toggle_modifier_print(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_rxp_hang_stop_toggle_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_tc_mask           : %s (" UH_FMT ")\n", (ptr_struct->vl_tc_mask == 1 ? ("VL_TC_0") : ((ptr_struct->vl_tc_mask == 2 ? ("VL_TC_1") : ((ptr_struct->vl_tc_mask == 4 ? ("VL_TC_2") : ((ptr_struct->vl_tc_mask == 8 ? ("VL_TC_3") : ((ptr_struct->vl_tc_mask == 16 ? ("VL_TC_4") : ((ptr_struct->vl_tc_mask == 32 ? ("VL_TC_5") : ((ptr_struct->vl_tc_mask == 64 ? ("VL_TC_6") : ((ptr_struct->vl_tc_mask == 128 ? ("VL_TC_7") : ((ptr_struct->vl_tc_mask == 32768 ? ("VL_TC_15") : ("unknown")))))))))))))))))), ptr_struct->vl_tc_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_number          : %s (" UH_FMT ")\n", (ptr_struct->port_number == 1 ? ("port_number1") : ((ptr_struct->port_number == 2 ? ("port_number2") : ("unknown")))), ptr_struct->port_number);
}

unsigned int reg_access_hca_rxp_hang_stop_toggle_modifier_size(void)
{
	return REG_ACCESS_HCA_RXP_HANG_STOP_TOGGLE_MODIFIER_SIZE;
}

void reg_access_hca_rxp_hang_stop_toggle_modifier_dump(const struct reg_access_hca_rxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_rxp_hang_stop_toggle_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_sxp_hang_stop_toggle_modifier_pack(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_number);
}

void reg_access_hca_sxp_hang_stop_toggle_modifier_unpack(struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->port_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_sxp_hang_stop_toggle_modifier_print(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_sxp_hang_stop_toggle_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_number          : %s (" UH_FMT ")\n", (ptr_struct->port_number == 1 ? ("port_number1") : ((ptr_struct->port_number == 2 ? ("port_number2") : ("unknown")))), ptr_struct->port_number);
}

unsigned int reg_access_hca_sxp_hang_stop_toggle_modifier_size(void)
{
	return REG_ACCESS_HCA_SXP_HANG_STOP_TOGGLE_MODIFIER_SIZE;
}

void reg_access_hca_sxp_hang_stop_toggle_modifier_dump(const struct reg_access_hca_sxp_hang_stop_toggle_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_sxp_hang_stop_toggle_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_diagnostic_cntr_layout_pack(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->counter_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sync);
}

void reg_access_hca_diagnostic_cntr_layout_unpack(struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->counter_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->sync = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_diagnostic_cntr_layout_print(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_diagnostic_cntr_layout ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "counter_id           : " UH_FMT "\n", ptr_struct->counter_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync                 : " UH_FMT "\n", ptr_struct->sync);
}

unsigned int reg_access_hca_diagnostic_cntr_layout_size(void)
{
	return REG_ACCESS_HCA_DIAGNOSTIC_CNTR_LAYOUT_SIZE;
}

void reg_access_hca_diagnostic_cntr_layout_dump(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd)
{
	reg_access_hca_diagnostic_cntr_layout_print(ptr_struct, fd, 0);
}

void reg_access_hca_fpga_shell_caps_pack(const struct reg_access_hca_fpga_shell_caps *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->total_rcv_credits);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_qps);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rc);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->uc);
	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ud);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dc);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rre);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rwe);
	offset = 53;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rae);
	offset = 46;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->qp_type);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_ddr_size);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_fpga_qp_msg_size);
}

void reg_access_hca_fpga_shell_caps_unpack(struct reg_access_hca_fpga_shell_caps *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->total_rcv_credits = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->max_num_qps = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 63;
	ptr_struct->rc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->uc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 61;
	ptr_struct->ud = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 60;
	ptr_struct->dc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 55;
	ptr_struct->rre = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->rwe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 53;
	ptr_struct->rae = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 46;
	ptr_struct->qp_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 90;
	ptr_struct->log_ddr_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 96;
	ptr_struct->max_fpga_qp_msg_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_fpga_shell_caps_print(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_fpga_shell_caps ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_rcv_credits    : " UH_FMT "\n", ptr_struct->total_rcv_credits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_qps          : " UH_FMT "\n", ptr_struct->max_num_qps);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rc                   : " UH_FMT "\n", ptr_struct->rc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uc                   : " UH_FMT "\n", ptr_struct->uc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ud                   : " UH_FMT "\n", ptr_struct->ud);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dc                   : " UH_FMT "\n", ptr_struct->dc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rre                  : " UH_FMT "\n", ptr_struct->rre);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rwe                  : " UH_FMT "\n", ptr_struct->rwe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rae                  : " UH_FMT "\n", ptr_struct->rae);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qp_type              : %s (" UH_FMT ")\n", (ptr_struct->qp_type == 1 ? ("Shell_qp") : ((ptr_struct->qp_type == 2 ? ("Sandbox_qp") : ("unknown")))), ptr_struct->qp_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_ddr_size         : " UH_FMT "\n", ptr_struct->log_ddr_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_fpga_qp_msg_size : " U32H_FMT "\n", ptr_struct->max_fpga_qp_msg_size);
}

unsigned int reg_access_hca_fpga_shell_caps_size(void)
{
	return REG_ACCESS_HCA_FPGA_SHELL_CAPS_SIZE;
}

void reg_access_hca_fpga_shell_caps_dump(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE *fd)
{
	reg_access_hca_fpga_shell_caps_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_reg_data_auto_pack(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_mcqi_cap_pack(&(ptr_struct->mcqi_cap), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_unpack(union reg_access_hca_mcqi_reg_data_auto *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_mcqi_cap_unpack(&(ptr_struct->mcqi_cap), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_print(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_reg_data_auto ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap:\n");
	reg_access_hca_mcqi_cap_print(&(ptr_struct->mcqi_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version:\n");
	reg_access_hca_mcqi_version_print(&(ptr_struct->mcqi_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method:\n");
	reg_access_hca_mcqi_activation_method_print(&(ptr_struct->mcqi_activation_method), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties:\n");
	reg_access_hca_mcqi_linkx_properties_print(&(ptr_struct->mcqi_linkx_properties), fd, indent_level + 1);
}

unsigned int reg_access_hca_mcqi_reg_data_auto_size(void)
{
	return REG_ACCESS_HCA_MCQI_REG_DATA_AUTO_SIZE;
}

void reg_access_hca_mcqi_reg_data_auto_dump(const union reg_access_hca_mcqi_reg_data_auto *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_reg_data_auto_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_dev_info_pack(const struct reg_access_hca_mgir_dev_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->dev_branch_tag[i]);
	}
}

void reg_access_hca_mgir_dev_info_unpack(struct reg_access_hca_mgir_dev_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		ptr_struct->dev_branch_tag[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_mgir_dev_info_print(const struct reg_access_hca_mgir_dev_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_dev_info ========\n");

	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dev_branch_tag_%03d  : " UH_FMT "\n", i, ptr_struct->dev_branch_tag[i]);
	}
}

unsigned int reg_access_hca_mgir_dev_info_size(void)
{
	return REG_ACCESS_HCA_MGIR_DEV_INFO_SIZE;
}

void reg_access_hca_mgir_dev_info_dump(const struct reg_access_hca_mgir_dev_info *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_dev_info_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_fw_info_pack(const struct reg_access_hca_mgir_fw_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sub_minor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secured);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_fw);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->debug);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->string_tlv);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev_sc);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->build_id);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->year);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->day);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->month);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hour);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ini_file_version);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_major);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_minor);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_sub_minor);
	offset = 400;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->isfu_major);
	offset = 384;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->disabled_tiles_bitmap);
	offset = 446;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->life_cycle);
	offset = 445;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sec_boot);
	offset = 444;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->encryption);
}

void reg_access_hca_mgir_fw_info_unpack(struct reg_access_hca_mgir_fw_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->sub_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 7;
	ptr_struct->secured = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->signed_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->debug = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->dev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->string_tlv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->dev_sc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->build_id = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->hour = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 512, 1);
		ptr_struct->psid[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 256;
	ptr_struct->ini_file_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->extended_major = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->extended_minor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->extended_sub_minor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 400;
	ptr_struct->isfu_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 384;
	ptr_struct->disabled_tiles_bitmap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 446;
	ptr_struct->life_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 445;
	ptr_struct->sec_boot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 444;
	ptr_struct->encryption = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mgir_fw_info_print(const struct reg_access_hca_mgir_fw_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_fw_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_minor            : " UH_FMT "\n", ptr_struct->sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secured              : " UH_FMT "\n", ptr_struct->secured);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_fw            : " UH_FMT "\n", ptr_struct->signed_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug                : " UH_FMT "\n", ptr_struct->debug);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev                  : " UH_FMT "\n", ptr_struct->dev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_tlv           : " UH_FMT "\n", ptr_struct->string_tlv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_sc               : " UH_FMT "\n", ptr_struct->dev_sc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build_id             : " U32H_FMT "\n", ptr_struct->build_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "year                 : " UH_FMT "\n", ptr_struct->year);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "day                  : " UH_FMT "\n", ptr_struct->day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "month                : " UH_FMT "\n", ptr_struct->month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hour                 : " UH_FMT "\n", ptr_struct->hour);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "psid_%03d            : " UH_FMT "\n", i, ptr_struct->psid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_version     : " U32H_FMT "\n", ptr_struct->ini_file_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_major       : " U32H_FMT "\n", ptr_struct->extended_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_minor       : " U32H_FMT "\n", ptr_struct->extended_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_sub_minor   : " U32H_FMT "\n", ptr_struct->extended_sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "isfu_major           : " UH_FMT "\n", ptr_struct->isfu_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "disabled_tiles_bitmap : " UH_FMT "\n", ptr_struct->disabled_tiles_bitmap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "life_cycle           : " UH_FMT "\n", ptr_struct->life_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sec_boot             : " UH_FMT "\n", ptr_struct->sec_boot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "encryption           : " UH_FMT "\n", ptr_struct->encryption);
}

unsigned int reg_access_hca_mgir_fw_info_size(void)
{
	return REG_ACCESS_HCA_MGIR_FW_INFO_SIZE;
}

void reg_access_hca_mgir_fw_info_dump(const struct reg_access_hca_mgir_fw_info *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_fw_info_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_hardware_info_pack(const struct reg_access_hca_mgir_hardware_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_hw_revision);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->technology);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_ports);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_dev_id);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->manufacturing_base_mac_47_32);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->manufacturing_base_mac_31_0);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uptime);
}

void reg_access_hca_mgir_hardware_info_unpack(struct reg_access_hca_mgir_hardware_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->device_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->device_hw_revision = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 59;
	ptr_struct->pvs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 48;
	ptr_struct->technology = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 40;
	ptr_struct->num_ports = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->hw_dev_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->manufacturing_base_mac_47_32 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->manufacturing_base_mac_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->uptime = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mgir_hardware_info_print(const struct reg_access_hca_mgir_hardware_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_hardware_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_id            : " UH_FMT "\n", ptr_struct->device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_hw_revision   : " UH_FMT "\n", ptr_struct->device_hw_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs                  : " UH_FMT "\n", ptr_struct->pvs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "technology           : " UH_FMT "\n", ptr_struct->technology);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_ports            : " UH_FMT "\n", ptr_struct->num_ports);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_dev_id            : " UH_FMT "\n", ptr_struct->hw_dev_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_47_32 : " UH_FMT "\n", ptr_struct->manufacturing_base_mac_47_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_31_0 : " U32H_FMT "\n", ptr_struct->manufacturing_base_mac_31_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uptime               : " U32H_FMT "\n", ptr_struct->uptime);
}

unsigned int reg_access_hca_mgir_hardware_info_size(void)
{
	return REG_ACCESS_HCA_MGIR_HARDWARE_INFO_SIZE;
}

void reg_access_hca_mgir_hardware_info_dump(const struct reg_access_hca_mgir_hardware_info *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_hardware_info_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_sw_info_pack(const struct reg_access_hca_mgir_sw_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sub_minor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom3_type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom3_arch);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom2_type);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom2_arch);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom1_type);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom1_arch);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom0_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom0_arch);
	offset = 64;
	reg_access_hca_rom_version_pack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_hca_rom_version_pack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_rom_version_pack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_rom_version_pack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_sw_info_unpack(struct reg_access_hca_mgir_sw_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->sub_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->rom3_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->rom3_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->rom2_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->rom2_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 44;
	ptr_struct->rom1_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->rom1_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->rom0_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->rom0_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	reg_access_hca_rom_version_unpack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_hca_rom_version_unpack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_rom_version_unpack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_rom_version_unpack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_sw_info_print(const struct reg_access_hca_mgir_sw_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_sw_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_minor            : " UH_FMT "\n", ptr_struct->sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_type            : " UH_FMT "\n", ptr_struct->rom3_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_arch            : " UH_FMT "\n", ptr_struct->rom3_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_type            : " UH_FMT "\n", ptr_struct->rom2_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_arch            : " UH_FMT "\n", ptr_struct->rom2_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_type            : " UH_FMT "\n", ptr_struct->rom1_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_arch            : " UH_FMT "\n", ptr_struct->rom1_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_type            : " UH_FMT "\n", ptr_struct->rom0_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_arch            : " UH_FMT "\n", ptr_struct->rom0_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_version:\n");
	reg_access_hca_rom_version_print(&(ptr_struct->rom0_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_version:\n");
	reg_access_hca_rom_version_print(&(ptr_struct->rom1_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_version:\n");
	reg_access_hca_rom_version_print(&(ptr_struct->rom2_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_version:\n");
	reg_access_hca_rom_version_print(&(ptr_struct->rom3_version), fd, indent_level + 1);
}

unsigned int reg_access_hca_mgir_sw_info_size(void)
{
	return REG_ACCESS_HCA_MGIR_SW_INFO_SIZE;
}

void reg_access_hca_mgir_sw_info_dump(const struct reg_access_hca_mgir_sw_info *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_sw_info_print(ptr_struct, fd, 0);
}

void reg_access_hca_smbus_failed_fault_inject_modifier_pack(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->smbus_gw);
}

void reg_access_hca_smbus_failed_fault_inject_modifier_unpack(struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->smbus_gw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_smbus_failed_fault_inject_modifier_print(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_smbus_failed_fault_inject_modifier ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "smbus_gw             : " UH_FMT "\n", ptr_struct->smbus_gw);
}

unsigned int reg_access_hca_smbus_failed_fault_inject_modifier_size(void)
{
	return REG_ACCESS_HCA_SMBUS_FAILED_FAULT_INJECT_MODIFIER_SIZE;
}

void reg_access_hca_smbus_failed_fault_inject_modifier_dump(const struct reg_access_hca_smbus_failed_fault_inject_modifier *ptr_struct, FILE *fd)
{
	reg_access_hca_smbus_failed_fault_inject_modifier_print(ptr_struct, fd, 0);
}

void reg_access_hca_string_db_parameters_pack(const struct reg_access_hca_string_db_parameters *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_base_address);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->string_db_size);
}

void reg_access_hca_string_db_parameters_unpack(struct reg_access_hca_string_db_parameters *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->string_db_base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->string_db_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_hca_string_db_parameters_print(const struct reg_access_hca_string_db_parameters *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_string_db_parameters ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_base_address : " U32H_FMT "\n", ptr_struct->string_db_base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_size       : " UH_FMT "\n", ptr_struct->string_db_size);
}

unsigned int reg_access_hca_string_db_parameters_size(void)
{
	return REG_ACCESS_HCA_STRING_DB_PARAMETERS_SIZE;
}

void reg_access_hca_string_db_parameters_dump(const struct reg_access_hca_string_db_parameters *ptr_struct, FILE *fd)
{
	reg_access_hca_string_db_parameters_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_pack(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_irisc_hang_mini_flow_modifier_pack(&(ptr_struct->irisc_hang_mini_flow_modifier), ptr_buff);
}

void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_unpack(union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_irisc_hang_mini_flow_modifier_unpack(&(ptr_struct->irisc_hang_mini_flow_modifier), ptr_buff);
}

void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_print(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "irisc_hang_mini_flow_modifier:\n");
	reg_access_hca_irisc_hang_mini_flow_modifier_print(&(ptr_struct->irisc_hang_mini_flow_modifier), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "packet_drop_mini_flow_modifier:\n");
	reg_access_hca_packet_drop_mini_flow_modifier_print(&(ptr_struct->packet_drop_mini_flow_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_size(void)
{
	return REG_ACCESS_HCA_STRS_MINI_FLOW_REG_PER_TYPE_MODIFIER_AUTO_SIZE;
}

void reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_dump(const union reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_pack(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_rxb_hang_stop_toggle_modifier_pack(&(ptr_struct->rxb_hang_stop_toggle_modifier), ptr_buff);
}

void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_unpack(union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_rxb_hang_stop_toggle_modifier_unpack(&(ptr_struct->rxb_hang_stop_toggle_modifier), ptr_buff);
}

void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_print(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rxb_hang_stop_toggle_modifier:\n");
	reg_access_hca_rxb_hang_stop_toggle_modifier_print(&(ptr_struct->rxb_hang_stop_toggle_modifier), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock_source_stop_toggle_modifier:\n");
	reg_access_hca_lock_source_stop_toggle_modifier_print(&(ptr_struct->lock_source_stop_toggle_modifier), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sxp_hang_stop_toggle_modifier:\n");
	reg_access_hca_sxp_hang_stop_toggle_modifier_print(&(ptr_struct->sxp_hang_stop_toggle_modifier), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rxp_hang_stop_toggle_modifier:\n");
	reg_access_hca_rxp_hang_stop_toggle_modifier_print(&(ptr_struct->rxp_hang_stop_toggle_modifier), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pause_tx_stop_toggle_modifier:\n");
	reg_access_hca_pause_tx_stop_toggle_modifier_print(&(ptr_struct->pause_tx_stop_toggle_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_size(void)
{
	return REG_ACCESS_HCA_STRS_STOP_TOGGLE_REG_PER_TYPE_MODIFIER_AUTO_SIZE;
}

void reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_dump(const union reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_print(ptr_struct, fd, 0);
}

void reg_access_hca_debug_cap_pack(const struct reg_access_hca_debug_cap *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_debug_cap_unpack(struct reg_access_hca_debug_cap *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_debug_cap_print(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_debug_cap ========\n");

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

unsigned int reg_access_hca_debug_cap_size(void)
{
	return REG_ACCESS_HCA_DEBUG_CAP_SIZE;
}

void reg_access_hca_debug_cap_dump(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd)
{
	reg_access_hca_debug_cap_print(ptr_struct, fd, 0);
}

void reg_access_hca_fpga_cap_pack(const struct reg_access_hca_fpga_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->fpga_device);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fpga_id);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->register_file_ver);
	offset = 78;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->access_reg_modify_mode);
	offset = 70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->access_reg_query_mode);
	offset = 66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->disconnect_fpga);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flash_gw_lock);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpga_ctrl_modify);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_version);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_date);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_time);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->shell_version);
	offset = 384;
	reg_access_hca_fpga_shell_caps_pack(&(ptr_struct->shell_caps), ptr_buff + offset / 8);
	offset = 904;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->ieee_vendor_id);
	offset = 944;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_product_id);
	offset = 928;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_product_version);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sandbox_basic_caps);
	offset = 1008;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_extended_caps_len);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->sandbox_extended_caps_addr);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->fpga_ddr_start_addr);
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->fpga_cr_space_start_addr);
	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fpga_ddr_size);
	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fpga_cr_space_size);
}

void reg_access_hca_fpga_cap_unpack(struct reg_access_hca_fpga_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->fpga_device = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->fpga_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->register_file_ver = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 78;
	ptr_struct->access_reg_modify_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 70;
	ptr_struct->access_reg_query_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 66;
	ptr_struct->disconnect_fpga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 65;
	ptr_struct->flash_gw_lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->fpga_ctrl_modify = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	ptr_struct->image_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->image_date = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->image_time = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->shell_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	reg_access_hca_fpga_shell_caps_unpack(&(ptr_struct->shell_caps), ptr_buff + offset / 8);
	offset = 904;
	ptr_struct->ieee_vendor_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 944;
	ptr_struct->sandbox_product_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 928;
	ptr_struct->sandbox_product_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 960;
	ptr_struct->sandbox_basic_caps = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1008;
	ptr_struct->sandbox_extended_caps_len = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1024;
	ptr_struct->sandbox_extended_caps_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 1088;
	ptr_struct->fpga_ddr_start_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 1152;
	ptr_struct->fpga_cr_space_start_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 1216;
	ptr_struct->fpga_ddr_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1248;
	ptr_struct->fpga_cr_space_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_fpga_cap_print(const struct reg_access_hca_fpga_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_fpga_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_device          : %s (" UH_FMT ")\n", (ptr_struct->fpga_device == 0 ? ("UNKNOWN_DEVICE") : ((ptr_struct->fpga_device == 1 ? ("KU040") : ((ptr_struct->fpga_device == 2 ? ("KU060") : ((ptr_struct->fpga_device == 3 ? ("KU060_2") : ("unknown")))))))), ptr_struct->fpga_device);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_id              : %s (" UH_FMT ")\n", (ptr_struct->fpga_id == 0 ? ("Newton_X") : ((ptr_struct->fpga_id == 1 ? ("Edison") : ("unknown")))), ptr_struct->fpga_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "register_file_ver    : " U32H_FMT "\n", ptr_struct->register_file_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_modify_mode : %s (" UH_FMT ")\n", (ptr_struct->access_reg_modify_mode == 0 ? ("Not_allowed") : ((ptr_struct->access_reg_modify_mode == 1 ? ("All_range_allowed") : ("unknown")))), ptr_struct->access_reg_modify_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_query_mode : %s (" UH_FMT ")\n", (ptr_struct->access_reg_query_mode == 0 ? ("Not_allowed") : ((ptr_struct->access_reg_query_mode == 1 ? ("All_range_allowed") : ("unknown")))), ptr_struct->access_reg_query_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "disconnect_fpga      : " UH_FMT "\n", ptr_struct->disconnect_fpga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_gw_lock        : " UH_FMT "\n", ptr_struct->flash_gw_lock);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_ctrl_modify     : " UH_FMT "\n", ptr_struct->fpga_ctrl_modify);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_version        : " U32H_FMT "\n", ptr_struct->image_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_date           : " U32H_FMT "\n", ptr_struct->image_date);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_time           : " U32H_FMT "\n", ptr_struct->image_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "shell_version        : " U32H_FMT "\n", ptr_struct->shell_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "shell_caps:\n");
	reg_access_hca_fpga_shell_caps_print(&(ptr_struct->shell_caps), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ieee_vendor_id       : " UH_FMT "\n", ptr_struct->ieee_vendor_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sandbox_product_id   : %s (" UH_FMT ")\n", (ptr_struct->sandbox_product_id == 0 ? ("unknown") : ((ptr_struct->sandbox_product_id == 1 ? ("example") : ((ptr_struct->sandbox_product_id == 2 ? ("IPsec") : ((ptr_struct->sandbox_product_id == 3 ? ("TLS") : ("unknown")))))))), ptr_struct->sandbox_product_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sandbox_product_version : " UH_FMT "\n", ptr_struct->sandbox_product_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sandbox_basic_caps   : " U32H_FMT "\n", ptr_struct->sandbox_basic_caps);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sandbox_extended_caps_len : " UH_FMT "\n", ptr_struct->sandbox_extended_caps_len);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sandbox_extended_caps_addr : " U64H_FMT "\n", ptr_struct->sandbox_extended_caps_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_ddr_start_addr  : " U64H_FMT "\n", ptr_struct->fpga_ddr_start_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_cr_space_start_addr : " U64H_FMT "\n", ptr_struct->fpga_cr_space_start_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_ddr_size        : " U32H_FMT "\n", ptr_struct->fpga_ddr_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_cr_space_size   : " U32H_FMT "\n", ptr_struct->fpga_cr_space_size);
}

unsigned int reg_access_hca_fpga_cap_size(void)
{
	return REG_ACCESS_HCA_FPGA_CAP_SIZE;
}

void reg_access_hca_fpga_cap_dump(const struct reg_access_hca_fpga_cap *ptr_struct, FILE *fd)
{
	reg_access_hca_fpga_cap_print(ptr_struct, fd, 0);
}

void reg_access_hca_fpga_ctrl_pack(const struct reg_access_hca_fpga_ctrl *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_select_oper);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_select_admin);
}

void reg_access_hca_fpga_ctrl_unpack(struct reg_access_hca_fpga_ctrl *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->error_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->flash_select_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->flash_select_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_fpga_ctrl_print(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_fpga_ctrl ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : %s (" UH_FMT ")\n", (ptr_struct->status == 0 ? ("Success") : ((ptr_struct->status == 1 ? ("Failure") : ((ptr_struct->status == 2 ? ("In_progress") : ((ptr_struct->status == 3 ? ("DISCONNECTED") : ("unknown")))))))), ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : %s (" UH_FMT ")\n", (ptr_struct->operation == 1 ? ("LOAD") : ((ptr_struct->operation == 2 ? ("RESET") : ((ptr_struct->operation == 3 ? ("FLASH_SELECT") : ((ptr_struct->operation == 4 ? ("Sandbox_Bypass_On") : ((ptr_struct->operation == 5 ? ("Sandbox_Bypass_Off") : ((ptr_struct->operation == 6 ? ("Reset_Sandbox") : ((ptr_struct->operation == 7 ? ("Flash_GW_Lock") : ((ptr_struct->operation == 8 ? ("Flash_GW_Unlock") : ((ptr_struct->operation == 9 ? ("DISCONNECT") : ((ptr_struct->operation == 10 ? ("CONNECT") : ("unknown")))))))))))))))))))), ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type           : %s (" UH_FMT ")\n", (ptr_struct->error_type == 0 ? ("Error_unknown") : ((ptr_struct->error_type == 1 ? ("fpga_done_timeout") : ((ptr_struct->error_type == 2 ? ("gpio_sig_mismatch") : ((ptr_struct->error_type == 3 ? ("ddr_bist_timeout") : ((ptr_struct->error_type == 4 ? ("sadb_reset_done_timeout") : ((ptr_struct->error_type == 5 ? ("sadb_reset_success_timeout") : ((ptr_struct->error_type == 6 ? ("ips_flush_done_timeout") : ((ptr_struct->error_type == 7 ? ("flash_gw_lock_timeout") : ((ptr_struct->error_type == 8 ? ("flash_gw_unlock_error") : ((ptr_struct->error_type == 9 ? ("i2c_access_during_fpga_load") : ((ptr_struct->error_type == 10 ? ("fpga_user_img_done_timeout") : ("unknown")))))))))))))))))))))), ptr_struct->error_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_select_oper    : %s (" UH_FMT ")\n", (ptr_struct->flash_select_oper == 0 ? ("User") : ((ptr_struct->flash_select_oper == 1 ? ("Factory_default") : ((ptr_struct->flash_select_oper == 2 ? ("Factory_failover") : ("unknown")))))), ptr_struct->flash_select_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_select_admin   : %s (" UH_FMT ")\n", (ptr_struct->flash_select_admin == 0 ? ("User") : ((ptr_struct->flash_select_admin == 1 ? ("Factory_default") : ("unknown")))), ptr_struct->flash_select_admin);
}

unsigned int reg_access_hca_fpga_ctrl_size(void)
{
	return REG_ACCESS_HCA_FPGA_CTRL_SIZE;
}

void reg_access_hca_fpga_ctrl_dump(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE *fd)
{
	reg_access_hca_fpga_ctrl_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcc_reg_pack(const struct reg_access_hca_mcc_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->instruction);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->activation_delay_sec);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->time_elapsed_since_last_cmd);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->auto_update);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->control_state);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_code);
	offset = 105;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->control_progress);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->handle_owner_host_id);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->handle_owner_type);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_size);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type);
	offset = 164;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index_size);
	offset = 196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->rejected_device_index);
}

void reg_access_hca_mcc_reg_unpack(struct reg_access_hca_mcc_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->instruction = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->activation_delay_sec = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->time_elapsed_since_last_cmd = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 48;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 64;
	ptr_struct->auto_update = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 124;
	ptr_struct->control_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 112;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 105;
	ptr_struct->control_progress = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 100;
	ptr_struct->handle_owner_host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->handle_owner_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 184;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 164;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 212;
	ptr_struct->device_index_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 196;
	ptr_struct->rejected_device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void reg_access_hca_mcc_reg_print(const struct reg_access_hca_mcc_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcc_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "instruction          : %s (" UH_FMT ")\n", (ptr_struct->instruction == 1 ? ("LOCK_UPDATE_HANDLE") : ((ptr_struct->instruction == 2 ? ("RELEASE_UPDATE_HANDLE") : ((ptr_struct->instruction == 3 ? ("UPDATE_COMPONENT") : ((ptr_struct->instruction == 4 ? ("VERIFY_COMPONENT") : ((ptr_struct->instruction == 5 ? ("ACTIVATE_COMPONENET") : ((ptr_struct->instruction == 6 ? ("ACTIVATE") : ((ptr_struct->instruction == 7 ? ("READ_COMPONENT") : ((ptr_struct->instruction == 8 ? ("CANCEL") : ((ptr_struct->instruction == 9 ? ("CHECK_UPDATE_HANDLE") : ((ptr_struct->instruction == 10 ? ("FORCE_HANDLE_RELEASE") : ((ptr_struct->instruction == 11 ? ("READ_PENDING_COMPONENT") : ((ptr_struct->instruction == 12 ? ("DOWNSRTEAM_DEVICE_TRANSFER") : ("unknown")))))))))))))))))))))))), ptr_struct->instruction);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "activation_delay_sec : " UH_FMT "\n", ptr_struct->activation_delay_sec);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_elapsed_since_last_cmd : " UH_FMT "\n", ptr_struct->time_elapsed_since_last_cmd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "auto_update          : " UH_FMT "\n", ptr_struct->auto_update);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "control_state        : %s (" UH_FMT ")\n", (ptr_struct->control_state == 0 ? ("IDLE") : ((ptr_struct->control_state == 1 ? ("LOCKED") : ((ptr_struct->control_state == 2 ? ("INITIALIZE") : ((ptr_struct->control_state == 3 ? ("DOWNLOAD") : ((ptr_struct->control_state == 4 ? ("VERIFY") : ((ptr_struct->control_state == 5 ? ("APPLY") : ((ptr_struct->control_state == 6 ? ("ACTIVATE") : ((ptr_struct->control_state == 7 ? ("UPLOAD") : ((ptr_struct->control_state == 8 ? ("UPLOAD_PENDING") : ((ptr_struct->control_state == 9 ? ("DOWNSRTEAM_DEVICE_TRANSFER") : ("unknown")))))))))))))))))))), ptr_struct->control_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code           : " UH_FMT "\n", ptr_struct->error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "control_progress     : " UH_FMT "\n", ptr_struct->control_progress);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "handle_owner_host_id : " UH_FMT "\n", ptr_struct->handle_owner_host_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "handle_owner_type    : " UH_FMT "\n", ptr_struct->handle_owner_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_size       : " U32H_FMT "\n", ptr_struct->component_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : %s (" UH_FMT ")\n", (ptr_struct->device_type == 0 ? ("Switch_or_NIC") : ((ptr_struct->device_type == 1 ? ("Gearbox") : ("unknown")))), ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index_size    : " UH_FMT "\n", ptr_struct->device_index_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rejected_device_index : " UH_FMT "\n", ptr_struct->rejected_device_index);
}

unsigned int reg_access_hca_mcc_reg_size(void)
{
	return REG_ACCESS_HCA_MCC_REG_SIZE;
}

void reg_access_hca_mcc_reg_dump(const struct reg_access_hca_mcc_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mcc_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcda_reg_pack(const struct reg_access_hca_mcda_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1152, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_hca_mcda_reg_unpack(struct reg_access_hca_mcda_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 32;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1152, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mcda_reg_print(const struct reg_access_hca_mcda_reg *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcda_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_hca_mcda_reg_size(void)
{
	return REG_ACCESS_HCA_MCDA_REG_SIZE;
}

void reg_access_hca_mcda_reg_dump(const struct reg_access_hca_mcda_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mcda_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_reg_pack(const struct reg_access_hca_mcqi_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->read_pending_component);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type);
	offset = 91;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->info_type);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->info_size);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data_size);
	offset = 192;
	switch (ptr_struct->info_type) {
	case 0x0:
		offset = 192;
		reg_access_hca_mcqi_cap_pack(&(ptr_struct->data.mcqi_cap), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_pack(&(ptr_struct->data.mcqi_version), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_pack(&(ptr_struct->data.mcqi_activation_method), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_pack(&(ptr_struct->data.mcqi_linkx_properties), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_mcqi_reg_unpack(struct reg_access_hca_mcqi_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 4;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->read_pending_component = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 91;
	ptr_struct->info_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 96;
	ptr_struct->info_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 176;
	ptr_struct->data_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	switch (ptr_struct->info_type) {
	case 0x0:
		offset = 192;
		reg_access_hca_mcqi_cap_unpack(&(ptr_struct->data.mcqi_cap), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_unpack(&(ptr_struct->data.mcqi_version), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_unpack(&(ptr_struct->data.mcqi_activation_method), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_unpack(&(ptr_struct->data.mcqi_linkx_properties), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_mcqi_reg_print(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_pending_component : " UH_FMT "\n", ptr_struct->read_pending_component);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_type            : %s (" UH_FMT ")\n", (ptr_struct->info_type == 0 ? ("CAPABILITIES") : ((ptr_struct->info_type == 1 ? ("VERSION") : ((ptr_struct->info_type == 5 ? ("ACTIVATION_METHOD") : ((ptr_struct->info_type == 6 ? ("LINKX_PROPERTIES") : ("unknown")))))))), ptr_struct->info_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_size            : " U32H_FMT "\n", ptr_struct->info_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_size            : " UH_FMT "\n", ptr_struct->data_size);
	switch (ptr_struct->info_type) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_cap:\n");
		reg_access_hca_mcqi_cap_print(&(ptr_struct->data.mcqi_cap), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_version:\n");
		reg_access_hca_mcqi_version_print(&(ptr_struct->data.mcqi_version), fd, indent_level + 1);
		break;
	case 0x5:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_activation_method:\n");
		reg_access_hca_mcqi_activation_method_print(&(ptr_struct->data.mcqi_activation_method), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_linkx_properties:\n");
		reg_access_hca_mcqi_linkx_properties_print(&(ptr_struct->data.mcqi_linkx_properties), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_hca_mcqi_reg_size(void)
{
	return REG_ACCESS_HCA_MCQI_REG_SIZE;
}

void reg_access_hca_mcqi_reg_dump(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqs_reg_pack(const struct reg_access_hca_mcqs_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->last_index_flag);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->identifier);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_update_state);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->component_status);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->progress);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_update_state_changer_host_id);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_update_state_changer_type);
}

void reg_access_hca_mcqs_reg_unpack(struct reg_access_hca_mcqs_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 4;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->last_index_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 92;
	ptr_struct->component_update_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 87;
	ptr_struct->component_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->progress = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 120;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 100;
	ptr_struct->last_update_state_changer_host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->last_update_state_changer_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mcqs_reg_print(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqs_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_index_flag      : " UH_FMT "\n", ptr_struct->last_index_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "identifier           : %s (" UH_FMT ")\n", (ptr_struct->identifier == 1 ? ("BOOT_IMG") : ((ptr_struct->identifier == 4 ? ("OEM_NVCONFIG") : ((ptr_struct->identifier == 5 ? ("MLNX_NVCONFIG") : ((ptr_struct->identifier == 6 ? ("CS_TOKEN") : ((ptr_struct->identifier == 7 ? ("DBG_TOKEN") : ((ptr_struct->identifier == 10 ? ("Gearbox") : ((ptr_struct->identifier == 11 ? ("CC_ALGO") : ((ptr_struct->identifier == 12 ? ("LINKX_IMG") : ((ptr_struct->identifier == 13 ? ("CRYPTO_TO_COMMISSIONING") : ((ptr_struct->identifier == 14 ? ("RMCS_TOKEN") : ((ptr_struct->identifier == 15 ? ("RMDT_TOKEN") : ("unknown")))))))))))))))))))))), ptr_struct->identifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_update_state : %s (" UH_FMT ")\n", (ptr_struct->component_update_state == 0 ? ("IDLE") : ((ptr_struct->component_update_state == 1 ? ("IN_PROGRESS") : ((ptr_struct->component_update_state == 2 ? ("APPLIED") : ((ptr_struct->component_update_state == 3 ? ("ACTIVE") : ((ptr_struct->component_update_state == 4 ? ("ACTIVE_PENDING_RESET") : ((ptr_struct->component_update_state == 5 ? ("FAILED") : ((ptr_struct->component_update_state == 6 ? ("CANCELED") : ((ptr_struct->component_update_state == 7 ? ("BUSY") : ("unknown")))))))))))))))), ptr_struct->component_update_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_status     : %s (" UH_FMT ")\n", (ptr_struct->component_status == 0 ? ("NOT_PRESENT") : ((ptr_struct->component_status == 1 ? ("PRESENT") : ((ptr_struct->component_status == 2 ? ("IN_USE") : ("unknown")))))), ptr_struct->component_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "progress             : " UH_FMT "\n", ptr_struct->progress);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_update_state_changer_host_id : " UH_FMT "\n", ptr_struct->last_update_state_changer_host_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_update_state_changer_type : %s (" UH_FMT ")\n", (ptr_struct->last_update_state_changer_type == 0 ? ("unspecified") : ((ptr_struct->last_update_state_changer_type == 1 ? ("Chassis_BMC") : ((ptr_struct->last_update_state_changer_type == 2 ? ("MAD") : ((ptr_struct->last_update_state_changer_type == 3 ? ("BMC") : ((ptr_struct->last_update_state_changer_type == 4 ? ("command_interface") : ((ptr_struct->last_update_state_changer_type == 5 ? ("ICMD") : ("unknown")))))))))))), ptr_struct->last_update_state_changer_type);
}

unsigned int reg_access_hca_mcqs_reg_size(void)
{
	return REG_ACCESS_HCA_MCQS_REG_SIZE;
}

void reg_access_hca_mcqs_reg_dump(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqs_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfrl_reg_ext_pack(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_trigger);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_type);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->rst_type_sel);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pci_sync_for_fw_update_resp);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_sync_for_fw_update_start);
}

void reg_access_hca_mfrl_reg_ext_unpack(struct reg_access_hca_mfrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->reset_trigger = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->reset_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 37;
	ptr_struct->rst_type_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 35;
	ptr_struct->pci_sync_for_fw_update_resp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 34;
	ptr_struct->pci_sync_for_fw_update_start = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mfrl_reg_ext_print(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_trigger        : " UH_FMT "\n", ptr_struct->reset_trigger);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_type           : " UH_FMT "\n", ptr_struct->reset_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst_type_sel         : " UH_FMT "\n", ptr_struct->rst_type_sel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_resp : %s (" UH_FMT ")\n", (ptr_struct->pci_sync_for_fw_update_resp == 1 ? ("Acknowledgment") : ((ptr_struct->pci_sync_for_fw_update_resp == 2 ? ("Dis") : ((ptr_struct->pci_sync_for_fw_update_resp == 3 ? ("Reserved") : ("unknown")))))), ptr_struct->pci_sync_for_fw_update_resp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_start : " UH_FMT "\n", ptr_struct->pci_sync_for_fw_update_start);
}

unsigned int reg_access_hca_mfrl_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFRL_REG_EXT_SIZE;
}

void reg_access_hca_mfrl_reg_ext_dump(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfrl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfsv_reg_pack(const struct reg_access_hca_mfsv_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->efuses_prog_en);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fw_sec_ver_stat);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->efuses_prog_method);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->img_sec_ver);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->efuses_sec_ver);
}

void reg_access_hca_mfsv_reg_unpack(struct reg_access_hca_mfsv_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->efuses_prog_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->fw_sec_ver_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 28;
	ptr_struct->efuses_prog_method = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->img_sec_ver = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->efuses_sec_ver = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mfsv_reg_print(const struct reg_access_hca_mfsv_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfsv_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "efuses_prog_en       : " UH_FMT "\n", ptr_struct->efuses_prog_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_sec_ver_stat      : " UH_FMT "\n", ptr_struct->fw_sec_ver_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "efuses_prog_method   : " UH_FMT "\n", ptr_struct->efuses_prog_method);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "img_sec_ver          : " U32H_FMT "\n", ptr_struct->img_sec_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "efuses_sec_ver       : " U32H_FMT "\n", ptr_struct->efuses_sec_ver);
}

unsigned int reg_access_hca_mfsv_reg_size(void)
{
	return REG_ACCESS_HCA_MFSV_REG_SIZE;
}

void reg_access_hca_mfsv_reg_dump(const struct reg_access_hca_mfsv_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mfsv_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_pack(const struct reg_access_hca_mgir *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_mgir_hardware_info_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_mgir_fw_info_pack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_hca_mgir_sw_info_pack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_hca_mgir_dev_info_pack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_unpack(struct reg_access_hca_mgir *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_mgir_hardware_info_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_mgir_fw_info_unpack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_hca_mgir_sw_info_unpack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_hca_mgir_dev_info_unpack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_print(const struct reg_access_hca_mgir *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	reg_access_hca_mgir_hardware_info_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info:\n");
	reg_access_hca_mgir_fw_info_print(&(ptr_struct->fw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_info:\n");
	reg_access_hca_mgir_sw_info_print(&(ptr_struct->sw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_info:\n");
	reg_access_hca_mgir_dev_info_print(&(ptr_struct->dev_info), fd, indent_level + 1);
}

unsigned int reg_access_hca_mgir_size(void)
{
	return REG_ACCESS_HCA_MGIR_SIZE;
}

void reg_access_hca_mgir_dump(const struct reg_access_hca_mgir *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_print(ptr_struct, fd, 0);
}

void reg_access_hca_mmdio_pack(const struct reg_access_hca_mmdio *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mdio_index);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->reg_adr);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->phy_adr);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->address);
}

void reg_access_hca_mmdio_unpack(struct reg_access_hca_mmdio *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 22;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->mdio_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 59;
	ptr_struct->reg_adr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 51;
	ptr_struct->phy_adr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->data = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->address = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_hca_mmdio_print(const struct reg_access_hca_mmdio *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mmdio ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : " UH_FMT "\n", ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clause               : " UH_FMT "\n", ptr_struct->clause);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdio_index           : " UH_FMT "\n", ptr_struct->mdio_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reg_adr              : " UH_FMT "\n", ptr_struct->reg_adr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_adr              : " UH_FMT "\n", ptr_struct->phy_adr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data                 : " UH_FMT "\n", ptr_struct->data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " UH_FMT "\n", ptr_struct->address);
}

unsigned int reg_access_hca_mmdio_size(void)
{
	return REG_ACCESS_HCA_MMDIO_SIZE;
}

void reg_access_hca_mmdio_dump(const struct reg_access_hca_mmdio *ptr_struct, FILE *fd)
{
	reg_access_hca_mmdio_print(ptr_struct, fd, 0);
}

void reg_access_hca_mpcir_ext_pack(const struct reg_access_hca_mpcir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->all);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ports);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ports_stat);
}

void reg_access_hca_mpcir_ext_unpack(struct reg_access_hca_mpcir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 62;
	ptr_struct->ports = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 126;
	ptr_struct->ports_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_hca_mpcir_ext_print(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpcir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "all                  : " UH_FMT "\n", ptr_struct->all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ports                : " UH_FMT "\n", ptr_struct->ports);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ports_stat           : " UH_FMT "\n", ptr_struct->ports_stat);
}

unsigned int reg_access_hca_mpcir_ext_size(void)
{
	return REG_ACCESS_HCA_MPCIR_EXT_SIZE;
}

void reg_access_hca_mpcir_ext_dump(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mpcir_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mpegc_reg_pack(const struct reg_access_hca_mpegc_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->field_select);
	offset = 94;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_lossy_overflow_oper);
	offset = 66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mark_cnp);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mark_cqe);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_overflow_sense);
	offset = 121;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->outbound_stalled_writes_th);
	offset = 113;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->outbound_stalled_reads_th);
	offset = 140;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->operation);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
}

void reg_access_hca_mpegc_reg_unpack(struct reg_access_hca_mpegc_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 48;
	ptr_struct->field_select = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 94;
	ptr_struct->tx_lossy_overflow_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 66;
	ptr_struct->mark_cnp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 65;
	ptr_struct->mark_cqe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->tx_overflow_sense = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 121;
	ptr_struct->outbound_stalled_writes_th = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 113;
	ptr_struct->outbound_stalled_reads_th = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 140;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mpegc_reg_print(const struct reg_access_hca_mpegc_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpegc_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "field_select         : " UH_FMT "\n", ptr_struct->field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lossy_overflow_oper : " UH_FMT "\n", ptr_struct->tx_lossy_overflow_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mark_cnp             : " UH_FMT "\n", ptr_struct->mark_cnp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mark_cqe             : " UH_FMT "\n", ptr_struct->mark_cqe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_overflow_sense    : " UH_FMT "\n", ptr_struct->tx_overflow_sense);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "outbound_stalled_writes_th : " UH_FMT "\n", ptr_struct->outbound_stalled_writes_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "outbound_stalled_reads_th : " UH_FMT "\n", ptr_struct->outbound_stalled_reads_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : " UH_FMT "\n", ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
}

unsigned int reg_access_hca_mpegc_reg_size(void)
{
	return REG_ACCESS_HCA_MPEGC_REG_SIZE;
}

void reg_access_hca_mpegc_reg_dump(const struct reg_access_hca_mpegc_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mpegc_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mqis_reg_pack(const struct reg_access_hca_mqis_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->info_type);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->info_length);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->read_length);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->read_offset);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->info_string[i]);
	}
}

void reg_access_hca_mqis_reg_unpack(struct reg_access_hca_mqis_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->info_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->info_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->read_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->read_offset = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 192, 1);
		ptr_struct->info_string[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_mqis_reg_print(const struct reg_access_hca_mqis_reg *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mqis_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_type            : %s (" UH_FMT ")\n", (ptr_struct->info_type == 1 ? ("MODEL_NAME") : ((ptr_struct->info_type == 2 ? ("MODEL_DESCRIPTION") : ((ptr_struct->info_type == 3 ? ("IMAGE_VSD") : ((ptr_struct->info_type == 4 ? ("DEVICE_VSD") : ((ptr_struct->info_type == 5 ? ("ROM_INFO") : ("unknown")))))))))), ptr_struct->info_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_length          : " UH_FMT "\n", ptr_struct->info_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_length          : " UH_FMT "\n", ptr_struct->read_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_offset          : " UH_FMT "\n", ptr_struct->read_offset);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "info_string_%03d     : " UH_FMT "\n", i, ptr_struct->info_string[i]);
	}
}

unsigned int reg_access_hca_mqis_reg_size(void)
{
	return REG_ACCESS_HCA_MQIS_REG_SIZE;
}

void reg_access_hca_mqis_reg_dump(const struct reg_access_hca_mqis_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mqis_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtrc_cap_reg_pack(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_string_db);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->trc_ver);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->trace_to_memory);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->trace_owner);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_string_trace);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_string_trace);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_max_trace_buffer_size);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1056, 1);
		reg_access_hca_string_db_parameters_pack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_mtrc_cap_reg_unpack(struct reg_access_hca_mtrc_cap_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	ptr_struct->num_string_db = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 6;
	ptr_struct->trc_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->trace_to_memory = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->trace_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 40;
	ptr_struct->num_string_trace = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->first_string_trace = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->log_max_trace_buffer_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1056, 1);
		reg_access_hca_string_db_parameters_unpack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_mtrc_cap_reg_print(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_cap_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_string_db        : " UH_FMT "\n", ptr_struct->num_string_db);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trc_ver              : " UH_FMT "\n", ptr_struct->trc_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_to_memory      : " UH_FMT "\n", ptr_struct->trace_to_memory);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_owner          : " UH_FMT "\n", ptr_struct->trace_owner);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_string_trace     : " UH_FMT "\n", ptr_struct->num_string_trace);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_string_trace   : " UH_FMT "\n", ptr_struct->first_string_trace);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_trace_buffer_size : " UH_FMT "\n", ptr_struct->log_max_trace_buffer_size);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "string_db_param_%03d:\n", i);
		reg_access_hca_string_db_parameters_print(&(ptr_struct->string_db_param[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_hca_mtrc_cap_reg_size(void)
{
	return REG_ACCESS_HCA_MTRC_CAP_REG_SIZE;
}

void reg_access_hca_mtrc_cap_reg_dump(const struct reg_access_hca_mtrc_cap_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_cap_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtrc_stdb_reg_pack(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->read_size);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_index);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->start_offset);
}

void reg_access_hca_mtrc_stdb_reg_unpack(struct reg_access_hca_mtrc_stdb_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->read_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->string_db_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->start_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtrc_stdb_reg_print(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_stdb_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_size            : " UH_FMT "\n", ptr_struct->read_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_index      : " UH_FMT "\n", ptr_struct->string_db_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "start_offset         : " U32H_FMT "\n", ptr_struct->start_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "unlimited array: (string_db_data)\n");
}

unsigned int reg_access_hca_mtrc_stdb_reg_size(void)
{
	return REG_ACCESS_HCA_MTRC_STDB_REG_SIZE;
}

void reg_access_hca_mtrc_stdb_reg_dump(const struct reg_access_hca_mtrc_stdb_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_stdb_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_pcnr_reg_pack(const struct reg_access_hca_pcnr_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tuning_override);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_fast_link_up);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->keep_phy_setting);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flot_cap);
	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flot_invalidation);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flu_disable);
}

void reg_access_hca_pcnr_reg_unpack(struct reg_access_hca_pcnr_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->tuning_override = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->force_fast_link_up = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 63;
	ptr_struct->keep_phy_setting = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->flot_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 61;
	ptr_struct->flot_invalidation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 60;
	ptr_struct->flu_disable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_pcnr_reg_print(const struct reg_access_hca_pcnr_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pcnr_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tuning_override      : " UH_FMT "\n", ptr_struct->tuning_override);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_fast_link_up   : " UH_FMT "\n", ptr_struct->force_fast_link_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "keep_phy_setting     : " UH_FMT "\n", ptr_struct->keep_phy_setting);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flot_cap             : " UH_FMT "\n", ptr_struct->flot_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flot_invalidation    : " UH_FMT "\n", ptr_struct->flot_invalidation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flu_disable          : " UH_FMT "\n", ptr_struct->flu_disable);
}

unsigned int reg_access_hca_pcnr_reg_size(void)
{
	return REG_ACCESS_HCA_PCNR_REG_SIZE;
}

void reg_access_hca_pcnr_reg_dump(const struct reg_access_hca_pcnr_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_pcnr_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_resource_dump_pack(const struct reg_access_hca_resource_dump *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->segment_type);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->seq_num);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vhca_id_valid);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->inline_dump);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->more_dump);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vhca_id);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index1);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index2);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_obj2);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_obj1);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->device_opaque);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mkey);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->size);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->address);
	for (i = 0; i < 52; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 2048, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->inline_data[i]);
	}
}

void reg_access_hca_resource_dump_unpack(struct reg_access_hca_resource_dump *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->segment_type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 12;
	ptr_struct->seq_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 2;
	ptr_struct->vhca_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->inline_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->more_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->vhca_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->index1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->index2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->num_of_obj2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->num_of_obj1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->device_opaque = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 256;
	ptr_struct->mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->address = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 52; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 2048, 1);
		ptr_struct->inline_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_resource_dump_print(const struct reg_access_hca_resource_dump *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_resource_dump ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_type         : " UH_FMT "\n", ptr_struct->segment_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seq_num              : " UH_FMT "\n", ptr_struct->seq_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vhca_id_valid        : " UH_FMT "\n", ptr_struct->vhca_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "inline_dump          : " UH_FMT "\n", ptr_struct->inline_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "more_dump            : " UH_FMT "\n", ptr_struct->more_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vhca_id              : " UH_FMT "\n", ptr_struct->vhca_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index1               : " U32H_FMT "\n", ptr_struct->index1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index2               : " U32H_FMT "\n", ptr_struct->index2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_obj2          : " UH_FMT "\n", ptr_struct->num_of_obj2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_obj1          : " UH_FMT "\n", ptr_struct->num_of_obj1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_opaque        : " U64H_FMT "\n", ptr_struct->device_opaque);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkey                 : " U32H_FMT "\n", ptr_struct->mkey);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " U32H_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U64H_FMT "\n", ptr_struct->address);
	for (i = 0; i < 52; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "inline_data_%03d     : " U32H_FMT "\n", i, ptr_struct->inline_data[i]);
	}
}

unsigned int reg_access_hca_resource_dump_size(void)
{
	return REG_ACCESS_HCA_RESOURCE_DUMP_SIZE;
}

void reg_access_hca_resource_dump_dump(const struct reg_access_hca_resource_dump *ptr_struct, FILE *fd)
{
	reg_access_hca_resource_dump_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_fault_inject_reg_pack(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->past_active);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->supported);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_skip);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_repeat);
	offset = 128;
	reg_access_hca_smbus_failed_fault_inject_modifier_pack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_fault_inject_reg_unpack(struct reg_access_hca_strs_fault_inject_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->past_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->num_skip = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->num_repeat = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	reg_access_hca_smbus_failed_fault_inject_modifier_unpack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_fault_inject_reg_print(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_fault_inject_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "past_active          : " UH_FMT "\n", ptr_struct->past_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported            : " UH_FMT "\n", ptr_struct->supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("ICM_ALLOC_REFUSE") : ((ptr_struct->type == 1 ? ("ICM_ALLOC_BUSY") : ((ptr_struct->type == 2 ? ("EQE_GW_BUSY") : ((ptr_struct->type == 3 ? ("CQE_GW_BUSY") : ((ptr_struct->type == 4 ? ("RX_FENCE_BUSY") : ((ptr_struct->type == 5 ? ("SX_FENCE_BUSY") : ((ptr_struct->type == 6 ? ("RXT_SLICE_FENCE_BUSY") : ((ptr_struct->type == 7 ? ("SXD_SLICE_FENCE_BUSY") : ((ptr_struct->type == 8 ? ("GENERAL_FENCE_BUSY") : ((ptr_struct->type == 9 ? ("SMBUS_FAILED") : ("unknown")))))))))))))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_skip             : " UH_FMT "\n", ptr_struct->num_skip);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_repeat           : " UH_FMT "\n", ptr_struct->num_repeat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_type_modifier:\n");
	reg_access_hca_smbus_failed_fault_inject_modifier_print(&(ptr_struct->per_type_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_strs_fault_inject_reg_size(void)
{
	return REG_ACCESS_HCA_STRS_FAULT_INJECT_REG_SIZE;
}

void reg_access_hca_strs_fault_inject_reg_dump(const struct reg_access_hca_strs_fault_inject_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_fault_inject_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_mini_flow_reg_pack(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->past_active);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->supported);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->freq);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_repeat);
	offset = 128;
	reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_pack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_mini_flow_reg_unpack(struct reg_access_hca_strs_mini_flow_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->past_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->freq = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->num_repeat = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_unpack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_mini_flow_reg_print(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_mini_flow_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "past_active          : " UH_FMT "\n", ptr_struct->past_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported            : " UH_FMT "\n", ptr_struct->supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("SX_FLICK_THROTTLE") : ((ptr_struct->type == 1 ? ("INVALIDATE_STEERING_CACHE") : ((ptr_struct->type == 2 ? ("INVALIDATE_RXT_QP_L0_CACHE") : ((ptr_struct->type == 3 ? ("INVALIDATE_DCT_L0_CACHE") : ((ptr_struct->type == 4 ? ("INVALIDATE_LDB_REQSL_CACHE") : ((ptr_struct->type == 5 ? ("INVALIDATE_RXC_CACHE") : ((ptr_struct->type == 6 ? ("INVALIDATE_SXDC_CACHE") : ((ptr_struct->type == 7 ? ("RECONSTRUCT_STEERING_BYPASS") : ((ptr_struct->type == 8 ? ("INVALIDATE_LDB_CACHE") : ((ptr_struct->type == 9 ? ("PCI_READ_ERROR") : ((ptr_struct->type == 10 ? ("INVALIDATE_ALL_RO_CACHES") : ((ptr_struct->type == 11 ? ("INVALIDATE_PKEY_CACHE") : ((ptr_struct->type == 12 ? ("INVALIDATE_GUID_CACHE") : ((ptr_struct->type == 13 ? ("INVALIDATE_PORT_INFO_CACHE") : ((ptr_struct->type == 14 ? ("INVALIDATE_QP_CACHE") : ((ptr_struct->type == 15 ? ("IRISC_HANG") : ((ptr_struct->type == 16 ? ("PACKET_DROP") : ("unknown")))))))))))))))))))))))))))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "freq                 : " UH_FMT "\n", ptr_struct->freq);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_repeat           : " UH_FMT "\n", ptr_struct->num_repeat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_type_modifier:\n");
	reg_access_hca_strs_mini_flow_reg_per_type_modifier_auto_print(&(ptr_struct->per_type_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_strs_mini_flow_reg_size(void)
{
	return REG_ACCESS_HCA_STRS_MINI_FLOW_REG_SIZE;
}

void reg_access_hca_strs_mini_flow_reg_dump(const struct reg_access_hca_strs_mini_flow_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_mini_flow_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_resource_reg_pack(const struct reg_access_hca_strs_resource_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->past_active);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->supported);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reduce_percentage);
}

void reg_access_hca_strs_resource_reg_unpack(struct reg_access_hca_strs_resource_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->past_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->reduce_percentage = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_strs_resource_reg_print(const struct reg_access_hca_strs_resource_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_resource_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "past_active          : " UH_FMT "\n", ptr_struct->past_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported            : " UH_FMT "\n", ptr_struct->supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("SX_SLICE") : ((ptr_struct->type == 1 ? ("RX_SLICE") : ("unknown")))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reduce_percentage    : " U32H_FMT "\n", ptr_struct->reduce_percentage);
}

unsigned int reg_access_hca_strs_resource_reg_size(void)
{
	return REG_ACCESS_HCA_STRS_RESOURCE_REG_SIZE;
}

void reg_access_hca_strs_resource_reg_dump(const struct reg_access_hca_strs_resource_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_resource_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_strs_stop_toggle_reg_pack(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->past_active);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->supported);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 91;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_stressor);
	offset = 83;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_duty_cycle);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->polarity);
	offset = 128;
	reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_pack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_stop_toggle_reg_unpack(struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->past_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 91;
	ptr_struct->log_stressor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 83;
	ptr_struct->log_duty_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 64;
	ptr_struct->polarity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_unpack(&(ptr_struct->per_type_modifier), ptr_buff + offset / 8);
}

void reg_access_hca_strs_stop_toggle_reg_print(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_strs_stop_toggle_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "past_active          : " UH_FMT "\n", ptr_struct->past_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported            : " UH_FMT "\n", ptr_struct->supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("DC_CNAK") : ((ptr_struct->type == 1 ? ("RXT_CHECKS") : ((ptr_struct->type == 2 ? ("TIMEOUT") : ((ptr_struct->type == 3 ? ("SX_ERROR") : ((ptr_struct->type == 4 ? ("RX_ERROR") : ((ptr_struct->type == 5 ? ("MX_ERROR") : ((ptr_struct->type == 6 ? ("MAD_TRAP") : ((ptr_struct->type == 7 ? ("RXT_SLICE") : ((ptr_struct->type == 8 ? ("QOS_ARBITER") : ((ptr_struct->type == 9 ? ("RXB_HANG") : ((ptr_struct->type == 10 ? ("FW_SCHED_Q") : ((ptr_struct->type == 11 ? ("LOCK_RESOURCE") : ((ptr_struct->type == 12 ? ("IRISC_HANG") : ((ptr_struct->type == 13 ? ("SXW_SLICE") : ((ptr_struct->type == 14 ? ("RXC_CQE") : ((ptr_struct->type == 15 ? ("RXC_EQE") : ((ptr_struct->type == 16 ? ("SXP_HANG") : ((ptr_struct->type == 17 ? ("SX_EXT_DB") : ((ptr_struct->type == 18 ? ("SX_INT_DB") : ((ptr_struct->type == 19 ? ("QPC_SLICE") : ((ptr_struct->type == 20 ? ("RXB_HOST_HANG") : ((ptr_struct->type == 21 ? ("PAUSE_TX") : ("unknown")))))))))))))))))))))))))))))))))))))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_stressor         : " UH_FMT "\n", ptr_struct->log_stressor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_duty_cycle       : " UH_FMT "\n", ptr_struct->log_duty_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "polarity             : %s (" UH_FMT ")\n", (ptr_struct->polarity == 0 ? ("FLOW_STOPPED") : ((ptr_struct->polarity == 1 ? ("FLOW_ACTIVE") : ("unknown")))), ptr_struct->polarity);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_type_modifier:\n");
	reg_access_hca_strs_stop_toggle_reg_per_type_modifier_auto_print(&(ptr_struct->per_type_modifier), fd, indent_level + 1);
}

unsigned int reg_access_hca_strs_stop_toggle_reg_size(void)
{
	return REG_ACCESS_HCA_STRS_STOP_TOGGLE_REG_SIZE;
}

void reg_access_hca_strs_stop_toggle_reg_dump(const struct reg_access_hca_strs_stop_toggle_reg *ptr_struct, FILE *fd)
{
	reg_access_hca_strs_stop_toggle_reg_print(ptr_struct, fd, 0);
}

void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_resource_dump_pack(&(ptr_struct->resource_dump), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_resource_dump_unpack(&(ptr_struct->resource_dump), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_reg_access_hca_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqs_reg:\n");
	reg_access_hca_mcqs_reg_print(&(ptr_struct->mcqs_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties:\n");
	reg_access_hca_mcqi_linkx_properties_print(&(ptr_struct->mcqi_linkx_properties), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method:\n");
	reg_access_hca_mcqi_activation_method_print(&(ptr_struct->mcqi_activation_method), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_stdb_reg:\n");
	reg_access_hca_mtrc_stdb_reg_print(&(ptr_struct->mtrc_stdb_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "strs_fault_inject_reg:\n");
	reg_access_hca_strs_fault_inject_reg_print(&(ptr_struct->strs_fault_inject_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_dump:\n");
	reg_access_hca_resource_dump_print(&(ptr_struct->resource_dump), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcnr_reg:\n");
	reg_access_hca_pcnr_reg_print(&(ptr_struct->pcnr_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmdio:\n");
	reg_access_hca_mmdio_print(&(ptr_struct->mmdio), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfsv_reg:\n");
	reg_access_hca_mfsv_reg_print(&(ptr_struct->mfsv_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcda_reg:\n");
	reg_access_hca_mcda_reg_print(&(ptr_struct->mcda_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_ctrl:\n");
	reg_access_hca_fpga_ctrl_print(&(ptr_struct->fpga_ctrl), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_cap_reg:\n");
	reg_access_hca_mtrc_cap_reg_print(&(ptr_struct->mtrc_cap_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpegc_reg:\n");
	reg_access_hca_mpegc_reg_print(&(ptr_struct->mpegc_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpga_cap:\n");
	reg_access_hca_fpga_cap_print(&(ptr_struct->fpga_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfrl_reg_ext:\n");
	reg_access_hca_mfrl_reg_ext_print(&(ptr_struct->mfrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_reg:\n");
	reg_access_hca_mcqi_reg_print(&(ptr_struct->mcqi_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcc_reg:\n");
	reg_access_hca_mcc_reg_print(&(ptr_struct->mcc_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "strs_mini_flow_reg:\n");
	reg_access_hca_strs_mini_flow_reg_print(&(ptr_struct->strs_mini_flow_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap:\n");
	reg_access_hca_mcqi_cap_print(&(ptr_struct->mcqi_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mqis_reg:\n");
	reg_access_hca_mqis_reg_print(&(ptr_struct->mqis_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpcir_ext:\n");
	reg_access_hca_mpcir_ext_print(&(ptr_struct->mpcir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "strs_resource_reg:\n");
	reg_access_hca_strs_resource_reg_print(&(ptr_struct->strs_resource_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug_cap:\n");
	reg_access_hca_debug_cap_print(&(ptr_struct->debug_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir:\n");
	reg_access_hca_mgir_print(&(ptr_struct->mgir), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version:\n");
	reg_access_hca_mcqi_version_print(&(ptr_struct->mcqi_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "strs_stop_toggle_reg:\n");
	reg_access_hca_strs_stop_toggle_reg_print(&(ptr_struct->strs_stop_toggle_reg), fd, indent_level + 1);
}

unsigned int reg_access_hca_reg_access_hca_Nodes_size(void)
{
	return REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE;
}

void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd)
{
	reg_access_hca_reg_access_hca_Nodes_print(ptr_struct, fd, 0);
}

