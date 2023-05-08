
/* Copyright (c) 2013-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
         *** This file was generated at "2023-01-17 10:38:00"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/tools_open/mlxconfig_4th_gen.adb --file-prefix mlxconfig_4th_gen --prefix mlxconfig_4th_gen_ --no-adb-utils
         ***/
#include "mlxconfig_4th_gen_layouts.h"

void mlxconfig_4th_gen_nv_hdr_pack(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->type);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->length);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_mod);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->shadow);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pad_cnt);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
}

void mlxconfig_4th_gen_nv_hdr_unpack(struct mlxconfig_4th_gen_nv_hdr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 2;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 40;
	ptr_struct->type_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 39;
	ptr_struct->shadow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 37;
	ptr_struct->pad_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void mlxconfig_4th_gen_nv_hdr_print(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_nv_hdr ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_mod             : " UH_FMT "\n", ptr_struct->type_mod);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "shadow               : " UH_FMT "\n", ptr_struct->shadow);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pad_cnt              : " UH_FMT "\n", ptr_struct->pad_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
}

unsigned int mlxconfig_4th_gen_nv_hdr_size(void)
{
	return MLXCONFIG_4TH_GEN_NV_HDR_SIZE;
}

void mlxconfig_4th_gen_nv_hdr_dump(const struct mlxconfig_4th_gen_nv_hdr *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_nv_hdr_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_bar_size_pack(const struct mlxconfig_4th_gen_bar_size *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_uar_bar_size);
}

void mlxconfig_4th_gen_bar_size_unpack(struct mlxconfig_4th_gen_bar_size *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->log_uar_bar_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void mlxconfig_4th_gen_bar_size_print(const struct mlxconfig_4th_gen_bar_size *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_bar_size ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_uar_bar_size     : " U32H_FMT "\n", ptr_struct->log_uar_bar_size);
}

unsigned int mlxconfig_4th_gen_bar_size_size(void)
{
	return MLXCONFIG_4TH_GEN_BAR_SIZE_SIZE;
}

void mlxconfig_4th_gen_bar_size_dump(const struct mlxconfig_4th_gen_bar_size *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_bar_size_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_boot_settings_pack(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->legacy_boot_protocol);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->boot_retry_conut);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);
}

void mlxconfig_4th_gen_boot_settings_unpack(struct mlxconfig_4th_gen_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 8;
	ptr_struct->legacy_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 5;
	ptr_struct->boot_retry_conut = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_boot_settings_print(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_boot_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_vlan            : " UH_FMT "\n", ptr_struct->boot_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "legacy_boot_protocol : " UH_FMT "\n", ptr_struct->legacy_boot_protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_retry_conut     : " UH_FMT "\n", ptr_struct->boot_retry_conut);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_vlan_en         : " UH_FMT "\n", ptr_struct->boot_vlan_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_option_rom_en   : " UH_FMT "\n", ptr_struct->boot_option_rom_en);
}

unsigned int mlxconfig_4th_gen_boot_settings_size(void)
{
	return MLXCONFIG_4TH_GEN_BOOT_SETTINGS_SIZE;
}

void mlxconfig_4th_gen_boot_settings_dump(const struct mlxconfig_4th_gen_boot_settings *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_boot_settings_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_boot_settings_ext_pack(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ip_ver);
}

void mlxconfig_4th_gen_boot_settings_ext_unpack(struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void mlxconfig_4th_gen_boot_settings_ext_print(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_boot_settings_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ip_ver               : " UH_FMT "\n", ptr_struct->ip_ver);
}

unsigned int mlxconfig_4th_gen_boot_settings_ext_size(void)
{
	return MLXCONFIG_4TH_GEN_BOOT_SETTINGS_EXT_SIZE;
}

void mlxconfig_4th_gen_boot_settings_ext_dump(const struct mlxconfig_4th_gen_boot_settings_ext *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_boot_settings_ext_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_infiniband_boot_settings_pack(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->boot_pkey);
}

void mlxconfig_4th_gen_infiniband_boot_settings_unpack(struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void mlxconfig_4th_gen_infiniband_boot_settings_print(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_infiniband_boot_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_pkey            : " UH_FMT "\n", ptr_struct->boot_pkey);
}

unsigned int mlxconfig_4th_gen_infiniband_boot_settings_size(void)
{
	return MLXCONFIG_4TH_GEN_INFINIBAND_BOOT_SETTINGS_SIZE;
}

void mlxconfig_4th_gen_infiniband_boot_settings_dump(const struct mlxconfig_4th_gen_infiniband_boot_settings *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_infiniband_boot_settings_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_mnva_pack(const struct mlxconfig_4th_gen_mnva *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	mlxconfig_4th_gen_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 2048, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}
}

void mlxconfig_4th_gen_mnva_unpack(struct mlxconfig_4th_gen_mnva *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	mlxconfig_4th_gen_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 2048, 1);
		ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void mlxconfig_4th_gen_mnva_print(const struct mlxconfig_4th_gen_mnva *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_mnva ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	mlxconfig_4th_gen_nv_hdr_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 128; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " UH_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int mlxconfig_4th_gen_mnva_size(void)
{
	return MLXCONFIG_4TH_GEN_MNVA_SIZE;
}

void mlxconfig_4th_gen_mnva_dump(const struct mlxconfig_4th_gen_mnva *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_mnva_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_mnvia_pack(const struct mlxconfig_4th_gen_mnvia *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	mlxconfig_4th_gen_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void mlxconfig_4th_gen_mnvia_unpack(struct mlxconfig_4th_gen_mnvia *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	mlxconfig_4th_gen_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void mlxconfig_4th_gen_mnvia_print(const struct mlxconfig_4th_gen_mnvia *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_mnvia ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	mlxconfig_4th_gen_nv_hdr_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
}

unsigned int mlxconfig_4th_gen_mnvia_size(void)
{
	return MLXCONFIG_4TH_GEN_MNVIA_SIZE;
}

void mlxconfig_4th_gen_mnvia_dump(const struct mlxconfig_4th_gen_mnvia *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_mnvia_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_nv_cx3_global_conf_pack(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clock_map_to_user);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->phy_param_mode);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->steer_force_vlan);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cq_timestamp);
}

void mlxconfig_4th_gen_nv_cx3_global_conf_unpack(struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	ptr_struct->clock_map_to_user = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->phy_param_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->steer_force_vlan = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->cq_timestamp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_nv_cx3_global_conf_print(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_nv_cx3_global_conf ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clock_map_to_user    : " UH_FMT "\n", ptr_struct->clock_map_to_user);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_param_mode       : " UH_FMT "\n", ptr_struct->phy_param_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "steer_force_vlan     : " UH_FMT "\n", ptr_struct->steer_force_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cq_timestamp         : " UH_FMT "\n", ptr_struct->cq_timestamp);
}

unsigned int mlxconfig_4th_gen_nv_cx3_global_conf_size(void)
{
	return MLXCONFIG_4TH_GEN_NV_CX3_GLOBAL_CONF_SIZE;
}

void mlxconfig_4th_gen_nv_cx3_global_conf_dump(const struct mlxconfig_4th_gen_nv_cx3_global_conf *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_nv_cx3_global_conf_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_preboot_boot_settings_pack(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->legacy_boot_protocol);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->boot_retry_count);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);
}

void mlxconfig_4th_gen_preboot_boot_settings_unpack(struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 8;
	ptr_struct->legacy_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 5;
	ptr_struct->boot_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_preboot_boot_settings_print(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_preboot_boot_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_vlan            : " UH_FMT "\n", ptr_struct->boot_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "legacy_boot_protocol : " UH_FMT "\n", ptr_struct->legacy_boot_protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_retry_count     : " UH_FMT "\n", ptr_struct->boot_retry_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_vlan_en         : " UH_FMT "\n", ptr_struct->boot_vlan_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_option_rom_en   : " UH_FMT "\n", ptr_struct->boot_option_rom_en);
}

unsigned int mlxconfig_4th_gen_preboot_boot_settings_size(void)
{
	return MLXCONFIG_4TH_GEN_PREBOOT_BOOT_SETTINGS_SIZE;
}

void mlxconfig_4th_gen_preboot_boot_settings_dump(const struct mlxconfig_4th_gen_preboot_boot_settings *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_preboot_boot_settings_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_sriov_pack(const struct mlxconfig_4th_gen_sriov *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);
}

void mlxconfig_4th_gen_sriov_unpack(struct mlxconfig_4th_gen_sriov *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_sriov_print(const struct mlxconfig_4th_gen_sriov *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_sriov ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_vfs            : " UH_FMT "\n", ptr_struct->total_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_en             : " UH_FMT "\n", ptr_struct->sriov_en);
}

unsigned int mlxconfig_4th_gen_sriov_size(void)
{
	return MLXCONFIG_4TH_GEN_SRIOV_SIZE;
}

void mlxconfig_4th_gen_sriov_dump(const struct mlxconfig_4th_gen_sriov *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_sriov_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_vpi_settings_pack(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->network_link_type);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_link_type);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->phy_type);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->xfi_mode);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_mode);
}

void mlxconfig_4th_gen_vpi_settings_unpack(struct mlxconfig_4th_gen_vpi_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 28;
	ptr_struct->default_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 26;
	ptr_struct->phy_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 24;
	ptr_struct->xfi_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 23;
	ptr_struct->force_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_vpi_settings_print(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_vpi_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "network_link_type    : " UH_FMT "\n", ptr_struct->network_link_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_link_type    : " UH_FMT "\n", ptr_struct->default_link_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_type             : " UH_FMT "\n", ptr_struct->phy_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xfi_mode             : " UH_FMT "\n", ptr_struct->xfi_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_mode           : " UH_FMT "\n", ptr_struct->force_mode);
}

unsigned int mlxconfig_4th_gen_vpi_settings_size(void)
{
	return MLXCONFIG_4TH_GEN_VPI_SETTINGS_SIZE;
}

void mlxconfig_4th_gen_vpi_settings_dump(const struct mlxconfig_4th_gen_vpi_settings *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_vpi_settings_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_wol_pack(const struct mlxconfig_4th_gen_wol *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_psswd_magic);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_magic);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_arp);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_bc);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_mc);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_uc);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_phy);
}

void mlxconfig_4th_gen_wol_unpack(struct mlxconfig_4th_gen_wol *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->en_wol_psswd_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 21;
	ptr_struct->en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->en_wol_arp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->en_wol_bc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->en_wol_mc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->en_wol_uc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->en_wol_phy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void mlxconfig_4th_gen_wol_print(const struct mlxconfig_4th_gen_wol *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_wol ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_psswd_magic   : " UH_FMT "\n", ptr_struct->en_wol_psswd_magic);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_magic         : " UH_FMT "\n", ptr_struct->en_wol_magic);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_arp           : " UH_FMT "\n", ptr_struct->en_wol_arp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_bc            : " UH_FMT "\n", ptr_struct->en_wol_bc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_mc            : " UH_FMT "\n", ptr_struct->en_wol_mc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_uc            : " UH_FMT "\n", ptr_struct->en_wol_uc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "en_wol_phy           : " UH_FMT "\n", ptr_struct->en_wol_phy);
}

unsigned int mlxconfig_4th_gen_wol_size(void)
{
	return MLXCONFIG_4TH_GEN_WOL_SIZE;
}

void mlxconfig_4th_gen_wol_dump(const struct mlxconfig_4th_gen_wol *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_wol_print(ptr_struct, fd, 0);
}

void mlxconfig_4th_gen_mlxconfig_nodes_pack(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, u_int8_t *ptr_buff)
{
	mlxconfig_4th_gen_mnva_pack(&(ptr_struct->mnva), ptr_buff);
}

void mlxconfig_4th_gen_mlxconfig_nodes_unpack(union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	mlxconfig_4th_gen_mnva_unpack(&(ptr_struct->mnva), ptr_buff);
}

void mlxconfig_4th_gen_mlxconfig_nodes_print(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== mlxconfig_4th_gen_mlxconfig_nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnva:\n");
	mlxconfig_4th_gen_mnva_print(&(ptr_struct->mnva), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvia:\n");
	mlxconfig_4th_gen_mnvia_print(&(ptr_struct->mnvia), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol:\n");
	mlxconfig_4th_gen_wol_print(&(ptr_struct->wol), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "infiniband_boot_settings:\n");
	mlxconfig_4th_gen_infiniband_boot_settings_print(&(ptr_struct->infiniband_boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_settings:\n");
	mlxconfig_4th_gen_boot_settings_print(&(ptr_struct->boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "preboot_boot_settings:\n");
	mlxconfig_4th_gen_preboot_boot_settings_print(&(ptr_struct->preboot_boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov:\n");
	mlxconfig_4th_gen_sriov_print(&(ptr_struct->sriov), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bar_size:\n");
	mlxconfig_4th_gen_bar_size_print(&(ptr_struct->bar_size), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vpi_settings:\n");
	mlxconfig_4th_gen_vpi_settings_print(&(ptr_struct->vpi_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_settings_ext:\n");
	mlxconfig_4th_gen_boot_settings_ext_print(&(ptr_struct->boot_settings_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_cx3_global_conf:\n");
	mlxconfig_4th_gen_nv_cx3_global_conf_print(&(ptr_struct->nv_cx3_global_conf), fd, indent_level + 1);
}

unsigned int mlxconfig_4th_gen_mlxconfig_nodes_size(void)
{
	return MLXCONFIG_4TH_GEN_MLXCONFIG_NODES_SIZE;
}

void mlxconfig_4th_gen_mlxconfig_nodes_dump(const union mlxconfig_4th_gen_mlxconfig_nodes *ptr_struct, FILE *fd)
{
	mlxconfig_4th_gen_mlxconfig_nodes_print(ptr_struct, fd, 0);
}

