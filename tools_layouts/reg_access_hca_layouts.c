
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
         *** This file was generated at "2023-03-30 13:00:24"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/prm/hca/ext/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_ --no-adb-utils
         ***/
#include "reg_access_hca_layouts.h"

void reg_access_hca_configuration_item_type_class_file_ext_pack(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_file_ext_unpack(struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->parameter_index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_file_ext_print(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_file_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_file_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_FILE_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_file_ext_dump(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_file_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_global_ext_pack(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_global_ext_unpack(struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->parameter_index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_global_ext_print(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_global_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_global_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_GLOBAL_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_global_ext_dump(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_global_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_host_ext_pack(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 18, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_host_ext_unpack(struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	ptr_struct->parameter_index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 18);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_host_ext_print(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_host_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_host_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_HOST_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_host_ext_dump(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_host_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_log_ext_pack(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_log_ext_unpack(struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->parameter_index = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_log_ext_print(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_log_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_log_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_LOG_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_log_ext_dump(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_log_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_module_ext_pack(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 14, (u_int32_t)ptr_struct->parameter_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->module_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_module_ext_unpack(struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 14);
	offset = 8;
	ptr_struct->module_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_module_ext_print(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_module_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_index         : " UH_FMT "\n", ptr_struct->module_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_module_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_MODULE_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_module_ext_dump(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_module_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_pack(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_unpack(struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_print(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_per_host_pf_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_per_host_pf_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_PER_HOST_PF_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_dump(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_per_host_pf_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_physical_port_ext_pack(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->parameter_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_physical_port_ext_unpack(struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_physical_port_ext_print(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_physical_port_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port                 : " UH_FMT "\n", ptr_struct->port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_physical_port_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_PHYSICAL_PORT_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_physical_port_ext_dump(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_physical_port_ext_print(ptr_struct, fd, 0);
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

void reg_access_hca_config_item_type_auto_ext_pack(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_configuration_item_type_class_module_ext_pack(&(ptr_struct->configuration_item_type_class_module_ext), ptr_buff);
}

void reg_access_hca_config_item_type_auto_ext_unpack(union reg_access_hca_config_item_type_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_configuration_item_type_class_module_ext_unpack(&(ptr_struct->configuration_item_type_class_module_ext), ptr_buff);
}

void reg_access_hca_config_item_type_auto_ext_print(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_config_item_type_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_global_ext:\n");
	reg_access_hca_configuration_item_type_class_global_ext_print(&(ptr_struct->configuration_item_type_class_global_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_physical_port_ext:\n");
	reg_access_hca_configuration_item_type_class_physical_port_ext_print(&(ptr_struct->configuration_item_type_class_physical_port_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_per_host_pf_ext:\n");
	reg_access_hca_configuration_item_type_class_per_host_pf_ext_print(&(ptr_struct->configuration_item_type_class_per_host_pf_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_log_ext:\n");
	reg_access_hca_configuration_item_type_class_log_ext_print(&(ptr_struct->configuration_item_type_class_log_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_file_ext:\n");
	reg_access_hca_configuration_item_type_class_file_ext_print(&(ptr_struct->configuration_item_type_class_file_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_host_ext:\n");
	reg_access_hca_configuration_item_type_class_host_ext_print(&(ptr_struct->configuration_item_type_class_host_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_module_ext:\n");
	reg_access_hca_configuration_item_type_class_module_ext_print(&(ptr_struct->configuration_item_type_class_module_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_config_item_type_auto_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIG_ITEM_TYPE_AUTO_EXT_SIZE;
}

void reg_access_hca_config_item_type_auto_ext_dump(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_config_item_type_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_activation_method_ext_pack(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_activation_method_ext_unpack(struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_activation_method_ext_print(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_activation_method_ext ========\n");

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

unsigned int reg_access_hca_mcqi_activation_method_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_ACTIVATION_METHOD_EXT_SIZE;
}

void reg_access_hca_mcqi_activation_method_ext_dump(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_activation_method_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_cap_ext_pack(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_cap_ext_unpack(struct reg_access_hca_mcqi_cap_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_cap_ext_print(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_cap_ext ========\n");

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

unsigned int reg_access_hca_mcqi_cap_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_CAP_EXT_SIZE;
}

void reg_access_hca_mcqi_cap_ext_dump(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_cap_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_clock_source_properties_ext_pack(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_version_minor);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_version_major);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vendor_id);
}

void reg_access_hca_mcqi_clock_source_properties_ext_unpack(struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->image_version_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->image_version_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->vendor_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mcqi_clock_source_properties_ext_print(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_clock_source_properties_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_version_minor  : " UH_FMT "\n", ptr_struct->image_version_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_version_major  : " UH_FMT "\n", ptr_struct->image_version_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vendor_id            : " UH_FMT "\n", ptr_struct->vendor_id);
}

unsigned int reg_access_hca_mcqi_clock_source_properties_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_CLOCK_SOURCE_PROPERTIES_EXT_SIZE;
}

void reg_access_hca_mcqi_clock_source_properties_ext_dump(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_clock_source_properties_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_linkx_properties_ext_pack(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_linkx_properties_ext_unpack(struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_linkx_properties_ext_print(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_linkx_properties_ext ========\n");

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

unsigned int reg_access_hca_mcqi_linkx_properties_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_LINKX_PROPERTIES_EXT_SIZE;
}

void reg_access_hca_mcqi_linkx_properties_ext_dump(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_linkx_properties_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_version_ext_pack(const struct reg_access_hca_mcqi_version_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_version_ext_unpack(struct reg_access_hca_mcqi_version_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcqi_version_ext_print(const struct reg_access_hca_mcqi_version_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_version_ext ========\n");

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

unsigned int reg_access_hca_mcqi_version_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_VERSION_EXT_SIZE;
}

void reg_access_hca_mcqi_version_ext_dump(const struct reg_access_hca_mcqi_version_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_version_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_rom_version_ext_pack(const struct reg_access_hca_rom_version_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->build);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
}

void reg_access_hca_rom_version_ext_unpack(struct reg_access_hca_rom_version_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->build = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_rom_version_ext_print(const struct reg_access_hca_rom_version_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_rom_version_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build                : " UH_FMT "\n", ptr_struct->build);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
}

unsigned int reg_access_hca_rom_version_ext_size(void)
{
	return REG_ACCESS_HCA_ROM_VERSION_EXT_SIZE;
}

void reg_access_hca_rom_version_ext_dump(const struct reg_access_hca_rom_version_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_rom_version_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_config_item_ext_pack(const struct reg_access_hca_config_item_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->length);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->host_id_valid);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->writer_id);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->access_mode);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rd_en);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ovr_en);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->priority);
	offset = 32;
	reg_access_hca_config_item_type_auto_ext_pack(&(ptr_struct->type), ptr_buff + offset / 8);
}

void reg_access_hca_config_item_ext_unpack(struct reg_access_hca_config_item_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 23;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	offset = 22;
	ptr_struct->host_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 11;
	ptr_struct->writer_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 8;
	ptr_struct->access_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 7;
	ptr_struct->rd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->ovr_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->priority = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	reg_access_hca_config_item_type_auto_ext_unpack(&(ptr_struct->type), ptr_buff + offset / 8);
}

void reg_access_hca_config_item_ext_print(const struct reg_access_hca_config_item_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_config_item_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_id_valid        : " UH_FMT "\n", ptr_struct->host_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "writer_id            : %s (" UH_FMT ")\n", (ptr_struct->writer_id == 0 ? ("UNSPECIFIED") : ((ptr_struct->writer_id == 1 ? ("CHASSIS_BMC") : ((ptr_struct->writer_id == 2 ? ("MAD") : ((ptr_struct->writer_id == 3 ? ("BMC") : ((ptr_struct->writer_id == 4 ? ("COMMAND_INTERFACE") : ((ptr_struct->writer_id == 5 ? ("ICMD") : ((ptr_struct->writer_id == 6 ? ("ICMD_UEFI_HII") : ((ptr_struct->writer_id == 7 ? ("ICMD_UEFI_CLP") : ((ptr_struct->writer_id == 8 ? ("ICMD_Flexboot") : ((ptr_struct->writer_id == 9 ? ("ICMD_mlxconfig") : ((ptr_struct->writer_id == 10 ? ("ICMD_USER1") : ((ptr_struct->writer_id == 11 ? ("ICMD_USER2") : ((ptr_struct->writer_id == 12 ? ("ICMD_MLXCONFIG_SET_RAW") : ((ptr_struct->writer_id == 13 ? ("ICMD_FLEXBOOT_CLP") : ((ptr_struct->writer_id == 16 ? ("BMC_APP1") : ((ptr_struct->writer_id == 17 ? ("BMC_APP2") : ((ptr_struct->writer_id == 18 ? ("BMP_APP3") : ((ptr_struct->writer_id == 31 ? ("OTHER") : ("unknown")))))))))))))))))))))))))))))))))))), ptr_struct->writer_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_mode          : %s (" UH_FMT ")\n", (ptr_struct->access_mode == 0 ? ("NEXT") : ("unknown")), ptr_struct->access_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rd_en                : " UH_FMT "\n", ptr_struct->rd_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ovr_en               : " UH_FMT "\n", ptr_struct->ovr_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "priority             : " UH_FMT "\n", ptr_struct->priority);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type:\n");
	reg_access_hca_config_item_type_auto_ext_print(&(ptr_struct->type), fd, indent_level + 1);
}

unsigned int reg_access_hca_config_item_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIG_ITEM_EXT_SIZE;
}

void reg_access_hca_config_item_ext_dump(const struct reg_access_hca_config_item_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_config_item_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_default_timeout_ext_pack(const struct reg_access_hca_default_timeout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->to_value);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->to_multiplier);
}

void reg_access_hca_default_timeout_ext_unpack(struct reg_access_hca_default_timeout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	ptr_struct->to_value = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
	offset = 0;
	ptr_struct->to_multiplier = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_hca_default_timeout_ext_print(const struct reg_access_hca_default_timeout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_default_timeout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "to_value             : " UH_FMT "\n", ptr_struct->to_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "to_multiplier        : " UH_FMT "\n", ptr_struct->to_multiplier);
}

unsigned int reg_access_hca_default_timeout_ext_size(void)
{
	return REG_ACCESS_HCA_DEFAULT_TIMEOUT_EXT_SIZE;
}

void reg_access_hca_default_timeout_ext_dump(const struct reg_access_hca_default_timeout_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_default_timeout_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_lane_2_module_mapping_ext_pack(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_lane);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_lane);
}

void reg_access_hca_lane_2_module_mapping_ext_unpack(struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 12;
	ptr_struct->tx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->rx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_lane_2_module_mapping_ext_print(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_lane_2_module_mapping_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lane              : " UH_FMT "\n", ptr_struct->tx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_lane              : " UH_FMT "\n", ptr_struct->rx_lane);
}

unsigned int reg_access_hca_lane_2_module_mapping_ext_size(void)
{
	return REG_ACCESS_HCA_LANE_2_MODULE_MAPPING_EXT_SIZE;
}

void reg_access_hca_lane_2_module_mapping_ext_dump(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_lane_2_module_mapping_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_reg_data_auto_ext_pack(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_mcqi_cap_ext_pack(&(ptr_struct->mcqi_cap_ext), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_ext_unpack(union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_mcqi_cap_ext_unpack(&(ptr_struct->mcqi_cap_ext), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_ext_print(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_reg_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap_ext:\n");
	reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->mcqi_cap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version_ext:\n");
	reg_access_hca_mcqi_version_ext_print(&(ptr_struct->mcqi_version_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method_ext:\n");
	reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->mcqi_activation_method_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties_ext:\n");
	reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->mcqi_linkx_properties_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_clock_source_properties_ext:\n");
	reg_access_hca_mcqi_clock_source_properties_ext_print(&(ptr_struct->mcqi_clock_source_properties_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_mcqi_reg_data_auto_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_REG_DATA_AUTO_EXT_SIZE;
}

void reg_access_hca_mcqi_reg_data_auto_ext_dump(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_reg_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_dev_info_ext_pack(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->dev_branch_tag[i]);
	}
}

void reg_access_hca_mgir_dev_info_ext_unpack(struct reg_access_hca_mgir_dev_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		ptr_struct->dev_branch_tag[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_mgir_dev_info_ext_print(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_dev_info_ext ========\n");

	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dev_branch_tag_%03d  : " UH_FMT "\n", i, ptr_struct->dev_branch_tag[i]);
	}
}

unsigned int reg_access_hca_mgir_dev_info_ext_size(void)
{
	return REG_ACCESS_HCA_MGIR_DEV_INFO_EXT_SIZE;
}

void reg_access_hca_mgir_dev_info_ext_dump(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_dev_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_fw_info_ext_pack(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mgir_fw_info_ext_unpack(struct reg_access_hca_mgir_fw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mgir_fw_info_ext_print(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_fw_info_ext ========\n");

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

unsigned int reg_access_hca_mgir_fw_info_ext_size(void)
{
	return REG_ACCESS_HCA_MGIR_FW_INFO_EXT_SIZE;
}

void reg_access_hca_mgir_fw_info_ext_dump(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_fw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_hardware_info_ext_pack(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mgir_hardware_info_ext_unpack(struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mgir_hardware_info_ext_print(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_hardware_info_ext ========\n");

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

unsigned int reg_access_hca_mgir_hardware_info_ext_size(void)
{
	return REG_ACCESS_HCA_MGIR_HARDWARE_INFO_EXT_SIZE;
}

void reg_access_hca_mgir_hardware_info_ext_dump(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_hardware_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_sw_info_ext_pack(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, u_int8_t *ptr_buff)
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
	reg_access_hca_rom_version_ext_pack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_hca_rom_version_ext_pack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_rom_version_ext_pack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_rom_version_ext_pack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_sw_info_ext_unpack(struct reg_access_hca_mgir_sw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	reg_access_hca_rom_version_ext_unpack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_hca_rom_version_ext_unpack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_rom_version_ext_unpack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_rom_version_ext_unpack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_sw_info_ext_print(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_sw_info_ext ========\n");

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
	reg_access_hca_rom_version_ext_print(&(ptr_struct->rom0_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_version:\n");
	reg_access_hca_rom_version_ext_print(&(ptr_struct->rom1_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_version:\n");
	reg_access_hca_rom_version_ext_print(&(ptr_struct->rom2_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_version:\n");
	reg_access_hca_rom_version_ext_print(&(ptr_struct->rom3_version), fd, indent_level + 1);
}

unsigned int reg_access_hca_mgir_sw_info_ext_size(void)
{
	return REG_ACCESS_HCA_MGIR_SW_INFO_EXT_SIZE;
}

void reg_access_hca_mgir_sw_info_ext_dump(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_sw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_string_db_parameters_ext_pack(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_base_address);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->string_db_size);
}

void reg_access_hca_string_db_parameters_ext_unpack(struct reg_access_hca_string_db_parameters_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->string_db_base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->string_db_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_hca_string_db_parameters_ext_print(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_string_db_parameters_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_base_address : " U32H_FMT "\n", ptr_struct->string_db_base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_size       : " UH_FMT "\n", ptr_struct->string_db_size);
}

unsigned int reg_access_hca_string_db_parameters_ext_size(void)
{
	return REG_ACCESS_HCA_STRING_DB_PARAMETERS_EXT_SIZE;
}

void reg_access_hca_string_db_parameters_ext_dump(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_string_db_parameters_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_dtor_reg_ext_pack(const struct reg_access_hca_dtor_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 32;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->PCIE_TOGGLE_TO), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->HEALTH_POLL_TO), ptr_buff + offset / 8);
	offset = 192;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->FULL_CRDUMP_TO), ptr_buff + offset / 8);
	offset = 224;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->FW_RESET_TO), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->FLUSH_ON_ERR_TO), ptr_buff + offset / 8);
	offset = 288;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->PCI_SYNC_UPDATE_TO), ptr_buff + offset / 8);
	offset = 320;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->TEAR_DOWN_TO), ptr_buff + offset / 8);
	offset = 352;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->FSM_REACTIVATE_TO), ptr_buff + offset / 8);
	offset = 384;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->RECLAIM_PAGES_TO), ptr_buff + offset / 8);
	offset = 416;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->RECLAIM_VFS_PAGES_TO), ptr_buff + offset / 8);
	offset = 448;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->DRIVER_UNLOAD_AND_RESET_TO), ptr_buff + offset / 8);
}

void reg_access_hca_dtor_reg_ext_unpack(struct reg_access_hca_dtor_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 32;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->PCIE_TOGGLE_TO), ptr_buff + offset / 8);
	offset = 160;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->HEALTH_POLL_TO), ptr_buff + offset / 8);
	offset = 192;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->FULL_CRDUMP_TO), ptr_buff + offset / 8);
	offset = 224;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->FW_RESET_TO), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->FLUSH_ON_ERR_TO), ptr_buff + offset / 8);
	offset = 288;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->PCI_SYNC_UPDATE_TO), ptr_buff + offset / 8);
	offset = 320;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->TEAR_DOWN_TO), ptr_buff + offset / 8);
	offset = 352;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->FSM_REACTIVATE_TO), ptr_buff + offset / 8);
	offset = 384;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->RECLAIM_PAGES_TO), ptr_buff + offset / 8);
	offset = 416;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->RECLAIM_VFS_PAGES_TO), ptr_buff + offset / 8);
	offset = 448;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->DRIVER_UNLOAD_AND_RESET_TO), ptr_buff + offset / 8);
}

void reg_access_hca_dtor_reg_ext_print(const struct reg_access_hca_dtor_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_dtor_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PCIE_TOGGLE_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->PCIE_TOGGLE_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "HEALTH_POLL_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->HEALTH_POLL_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FULL_CRDUMP_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->FULL_CRDUMP_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_RESET_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->FW_RESET_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FLUSH_ON_ERR_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->FLUSH_ON_ERR_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PCI_SYNC_UPDATE_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->PCI_SYNC_UPDATE_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "TEAR_DOWN_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->TEAR_DOWN_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FSM_REACTIVATE_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->FSM_REACTIVATE_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "RECLAIM_PAGES_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->RECLAIM_PAGES_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "RECLAIM_VFS_PAGES_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->RECLAIM_VFS_PAGES_TO), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DRIVER_UNLOAD_AND_RESET_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->DRIVER_UNLOAD_AND_RESET_TO), fd, indent_level + 1);
}

unsigned int reg_access_hca_dtor_reg_ext_size(void)
{
	return REG_ACCESS_HCA_DTOR_REG_EXT_SIZE;
}

void reg_access_hca_dtor_reg_ext_dump(const struct reg_access_hca_dtor_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_dtor_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcam_reg_ext_pack(const struct reg_access_hca_mcam_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 576, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 576, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mng_feature_cap_mask[i]);
	}
}

void reg_access_hca_mcam_reg_ext_unpack(struct reg_access_hca_mcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->feature_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 576, 1);
		ptr_struct->mng_access_reg_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 576, 1);
		ptr_struct->mng_feature_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mcam_reg_ext_print(const struct reg_access_hca_mcam_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcam_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : %s (" UH_FMT ")\n", (ptr_struct->access_reg_group == 0 ? ("First_128_REG_ID") : ((ptr_struct->access_reg_group == 1 ? ("Register_IDs_0x9080") : ((ptr_struct->access_reg_group == 2 ? ("Register_IDs_0x9100") : ("unknown")))))), ptr_struct->access_reg_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "feature_group        : %s (" UH_FMT ")\n", (ptr_struct->feature_group == 0 ? ("enhanced_features") : ("unknown")), ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_access_reg_cap_mask_%03d : %s (" U32H_FMT ")\n", i, (ptr_struct->mng_access_reg_cap_mask[i] == 2 ? ("MFCR_0x9001") : ((ptr_struct->mng_access_reg_cap_mask[i] == 4 ? ("MFSC_0x9002") : ((ptr_struct->mng_access_reg_cap_mask[i] == 8 ? ("MFSM_0x9003") : ((ptr_struct->mng_access_reg_cap_mask[i] == 16 ? ("MFSL_0x9004") : ((ptr_struct->mng_access_reg_cap_mask[i] == 67108864 ? ("MGCR_0x903A") : ((ptr_struct->mng_access_reg_cap_mask[i] == 512 ? ("MPPF_0x9049") : ((ptr_struct->mng_access_reg_cap_mask[i] == 2147483648 ? ("MCAP_0x907F") : ("unknown")))))))))))))), ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_feature_cap_mask_%03d : " U32H_FMT "\n", i, ptr_struct->mng_feature_cap_mask[i]);
	}
}

unsigned int reg_access_hca_mcam_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MCAM_REG_EXT_SIZE;
}

void reg_access_hca_mcam_reg_ext_dump(const struct reg_access_hca_mcam_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcam_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcc_reg_ext_pack(const struct reg_access_hca_mcc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcc_reg_ext_unpack(struct reg_access_hca_mcc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcc_reg_ext_print(const struct reg_access_hca_mcc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "instruction          : %s (" UH_FMT ")\n", (ptr_struct->instruction == 1 ? ("LOCK_UPDATE_HANDLE") : ((ptr_struct->instruction == 2 ? ("RELEASE_UPDATE_HANDLE") : ((ptr_struct->instruction == 3 ? ("UPDATE_COMPONENT") : ((ptr_struct->instruction == 4 ? ("VERIFY_COMPONENT") : ((ptr_struct->instruction == 6 ? ("ACTIVATE") : ((ptr_struct->instruction == 7 ? ("READ_COMPONENT") : ((ptr_struct->instruction == 8 ? ("CANCEL") : ((ptr_struct->instruction == 9 ? ("CHECK_UPDATE_HANDLE") : ((ptr_struct->instruction == 10 ? ("FORCE_HANDLE_RELEASE") : ((ptr_struct->instruction == 11 ? ("READ_PENDING_COMPONENT") : ((ptr_struct->instruction == 12 ? ("DOWNSRTEAM_DEVICE_TRANSFER") : ("unknown")))))))))))))))))))))), ptr_struct->instruction);
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

unsigned int reg_access_hca_mcc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MCC_REG_EXT_SIZE;
}

void reg_access_hca_mcc_reg_ext_dump(const struct reg_access_hca_mcc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcda_reg_ext_pack(const struct reg_access_hca_mcda_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcda_reg_ext_unpack(struct reg_access_hca_mcda_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcda_reg_ext_print(const struct reg_access_hca_mcda_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcda_reg_ext ========\n");

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

unsigned int reg_access_hca_mcda_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MCDA_REG_EXT_SIZE;
}

void reg_access_hca_mcda_reg_ext_dump(const struct reg_access_hca_mcda_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcda_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcia_ext_pack(const struct reg_access_hca_mcia_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_address);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->page_number);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->i2c_device_address);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bank_number);
	offset = 67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->passwd_length);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->password);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1184, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dword[i]);
	}
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->password_msb);
}

void reg_access_hca_mcia_ext_unpack(struct reg_access_hca_mcia_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->l = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->device_address = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 40;
	ptr_struct->page_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->i2c_device_address = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->bank_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 67;
	ptr_struct->passwd_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->password = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1184, 1);
		ptr_struct->dword[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 1152;
	ptr_struct->password_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mcia_ext_print(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcia_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l                    : " UH_FMT "\n", ptr_struct->l);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_address       : " UH_FMT "\n", ptr_struct->device_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_number          : " UH_FMT "\n", ptr_struct->page_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "i2c_device_address   : " UH_FMT "\n", ptr_struct->i2c_device_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bank_number          : " UH_FMT "\n", ptr_struct->bank_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "passwd_length        : " UH_FMT "\n", ptr_struct->passwd_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "password             : " U32H_FMT "\n", ptr_struct->password);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dword_%03d           : " U32H_FMT "\n", i, ptr_struct->dword[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "password_msb         : " U32H_FMT "\n", ptr_struct->password_msb);
}

unsigned int reg_access_hca_mcia_ext_size(void)
{
	return REG_ACCESS_HCA_MCIA_EXT_SIZE;
}

void reg_access_hca_mcia_ext_dump(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcia_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_reg_ext_pack(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
		reg_access_hca_mcqi_cap_ext_pack(&(ptr_struct->data.mcqi_cap_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_ext_pack(&(ptr_struct->data.mcqi_version_ext), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_ext_pack(&(ptr_struct->data.mcqi_activation_method_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_ext_pack(&(ptr_struct->data.mcqi_linkx_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x7:
		offset = 192;
		reg_access_hca_mcqi_clock_source_properties_ext_pack(&(ptr_struct->data.mcqi_clock_source_properties_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_mcqi_reg_ext_unpack(struct reg_access_hca_mcqi_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
		reg_access_hca_mcqi_cap_ext_unpack(&(ptr_struct->data.mcqi_cap_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_ext_unpack(&(ptr_struct->data.mcqi_version_ext), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_ext_unpack(&(ptr_struct->data.mcqi_activation_method_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_ext_unpack(&(ptr_struct->data.mcqi_linkx_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x7:
		offset = 192;
		reg_access_hca_mcqi_clock_source_properties_ext_unpack(&(ptr_struct->data.mcqi_clock_source_properties_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_mcqi_reg_ext_print(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_pending_component : " UH_FMT "\n", ptr_struct->read_pending_component);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_type            : %s (" UH_FMT ")\n", (ptr_struct->info_type == 0 ? ("CAPABILITIES") : ((ptr_struct->info_type == 1 ? ("VERSION") : ((ptr_struct->info_type == 5 ? ("ACTIVATION_METHOD") : ((ptr_struct->info_type == 6 ? ("LINKX_PROPERTIES") : ((ptr_struct->info_type == 7 ? ("CLOCK_SOURCE_PROPERTIES") : ("unknown")))))))))), ptr_struct->info_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_size            : " U32H_FMT "\n", ptr_struct->info_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_size            : " UH_FMT "\n", ptr_struct->data_size);
	switch (ptr_struct->info_type) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_cap_ext:\n");
		reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->data.mcqi_cap_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_version_ext:\n");
		reg_access_hca_mcqi_version_ext_print(&(ptr_struct->data.mcqi_version_ext), fd, indent_level + 1);
		break;
	case 0x5:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_activation_method_ext:\n");
		reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->data.mcqi_activation_method_ext), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_linkx_properties_ext:\n");
		reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->data.mcqi_linkx_properties_ext), fd, indent_level + 1);
		break;
	case 0x7:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_clock_source_properties_ext:\n");
		reg_access_hca_mcqi_clock_source_properties_ext_print(&(ptr_struct->data.mcqi_clock_source_properties_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_hca_mcqi_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_REG_EXT_SIZE;
}

void reg_access_hca_mcqi_reg_ext_dump(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqs_reg_ext_pack(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mcqs_reg_ext_unpack(struct reg_access_hca_mcqs_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mcqs_reg_ext_print(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqs_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_index_flag      : " UH_FMT "\n", ptr_struct->last_index_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "identifier           : %s (" UH_FMT ")\n", (ptr_struct->identifier == 1 ? ("BOOT_IMG") : ((ptr_struct->identifier == 4 ? ("OEM_NVCONFIG") : ((ptr_struct->identifier == 5 ? ("MLNX_NVCONFIG") : ((ptr_struct->identifier == 6 ? ("CS_TOKEN") : ((ptr_struct->identifier == 7 ? ("DBG_TOKEN") : ((ptr_struct->identifier == 10 ? ("Gearbox") : ((ptr_struct->identifier == 11 ? ("CC_ALGO") : ((ptr_struct->identifier == 12 ? ("LINKX_IMG") : ((ptr_struct->identifier == 13 ? ("CRYPTO_TO_COMMISSIONING") : ((ptr_struct->identifier == 14 ? ("RMCS_TOKEN") : ((ptr_struct->identifier == 15 ? ("RMDT_TOKEN") : ((ptr_struct->identifier == 16 ? ("CRCS_TOKEN_") : ((ptr_struct->identifier == 17 ? ("CRDT_TOKEN_") : ((ptr_struct->identifier == 18 ? ("CLOCK_SYNC_EEPROM_") : ("unknown")))))))))))))))))))))))))))), ptr_struct->identifier);
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

unsigned int reg_access_hca_mcqs_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MCQS_REG_EXT_SIZE;
}

void reg_access_hca_mcqs_reg_ext_dump(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqs_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfba_reg_ext_pack(const struct reg_access_hca_mfba_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->add_cap_32b);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 2144, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_hca_mfba_reg_ext_unpack(struct reg_access_hca_mfba_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->add_cap_32b = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 55;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	offset = 64;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 2144, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mfba_reg_ext_print(const struct reg_access_hca_mfba_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfba_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "add_cap_32b          : " UH_FMT "\n", ptr_struct->add_cap_32b);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_hca_mfba_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFBA_REG_EXT_SIZE;
}

void reg_access_hca_mfba_reg_ext_dump(const struct reg_access_hca_mfba_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfba_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfbe_reg_ext_pack(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_64kb_erase);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_32kb_erase);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->add_cap_32b);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
}

void reg_access_hca_mfbe_reg_ext_unpack(struct reg_access_hca_mfbe_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 2;
	ptr_struct->bulk_64kb_erase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->bulk_32kb_erase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->add_cap_32b = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mfbe_reg_ext_print(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfbe_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_64kb_erase      : " UH_FMT "\n", ptr_struct->bulk_64kb_erase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_32kb_erase      : " UH_FMT "\n", ptr_struct->bulk_32kb_erase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "add_cap_32b          : " UH_FMT "\n", ptr_struct->add_cap_32b);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
}

unsigned int reg_access_hca_mfbe_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFBE_REG_EXT_SIZE;
}

void reg_access_hca_mfbe_reg_ext_dump(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfbe_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfmc_reg_ext_pack(const struct reg_access_hca_mfmc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->wrp_block_count);
	offset = 46;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->block_size);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wrp_en);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->sub_sector_protect_size);
	offset = 82;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->sector_protect_size);
	offset = 135;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->quad_en);
	offset = 220;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dummy_clock_cycles);
}

void reg_access_hca_mfmc_reg_ext_unpack(struct reg_access_hca_mfmc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->wrp_block_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 46;
	ptr_struct->block_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	ptr_struct->wrp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 90;
	ptr_struct->sub_sector_protect_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 82;
	ptr_struct->sector_protect_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 135;
	ptr_struct->quad_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 220;
	ptr_struct->dummy_clock_cycles = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mfmc_reg_ext_print(const struct reg_access_hca_mfmc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfmc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrp_block_count      : " UH_FMT "\n", ptr_struct->wrp_block_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_size           : " UH_FMT "\n", ptr_struct->block_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrp_en               : " UH_FMT "\n", ptr_struct->wrp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_sector_protect_size : " UH_FMT "\n", ptr_struct->sub_sector_protect_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sector_protect_size  : " UH_FMT "\n", ptr_struct->sector_protect_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "quad_en              : " UH_FMT "\n", ptr_struct->quad_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dummy_clock_cycles   : " UH_FMT "\n", ptr_struct->dummy_clock_cycles);
}

unsigned int reg_access_hca_mfmc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFMC_REG_EXT_SIZE;
}

void reg_access_hca_mfmc_reg_ext_dump(const struct reg_access_hca_mfmc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfmc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfpa_reg_ext_pack(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->add_cap_32b);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->boot_address);
	offset = 156;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->flash_num);
	offset = 143;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sub_sector_wrp_en);
	offset = 142;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sector_wrp_en);
	offset = 130;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_64kb_erase_en);
	offset = 129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_32kb_erase_en);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wip);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->jedec_id);
	offset = 214;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->sector_size);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_alignment);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_size);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->capability_mask);
}

void reg_access_hca_mfpa_reg_ext_unpack(struct reg_access_hca_mfpa_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->add_cap_32b = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->boot_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 156;
	ptr_struct->flash_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 143;
	ptr_struct->sub_sector_wrp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 142;
	ptr_struct->sector_wrp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 130;
	ptr_struct->bulk_64kb_erase_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 129;
	ptr_struct->bulk_32kb_erase_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	ptr_struct->wip = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 168;
	ptr_struct->jedec_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 214;
	ptr_struct->sector_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 200;
	ptr_struct->block_alignment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 192;
	ptr_struct->block_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->capability_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mfpa_reg_ext_print(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfpa_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "add_cap_32b          : " UH_FMT "\n", ptr_struct->add_cap_32b);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_address         : " U32H_FMT "\n", ptr_struct->boot_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_num            : " UH_FMT "\n", ptr_struct->flash_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_sector_wrp_en    : " UH_FMT "\n", ptr_struct->sub_sector_wrp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sector_wrp_en        : " UH_FMT "\n", ptr_struct->sector_wrp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_64kb_erase_en   : " UH_FMT "\n", ptr_struct->bulk_64kb_erase_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_32kb_erase_en   : " UH_FMT "\n", ptr_struct->bulk_32kb_erase_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wip                  : " UH_FMT "\n", ptr_struct->wip);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "jedec_id             : " UH_FMT "\n", ptr_struct->jedec_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sector_size          : " UH_FMT "\n", ptr_struct->sector_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_alignment      : " UH_FMT "\n", ptr_struct->block_alignment);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_size           : " UH_FMT "\n", ptr_struct->block_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_mask      : " U32H_FMT "\n", ptr_struct->capability_mask);
}

unsigned int reg_access_hca_mfpa_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFPA_REG_EXT_SIZE;
}

void reg_access_hca_mfpa_reg_ext_dump(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfpa_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfrl_reg_ext_pack(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_trigger);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_type);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reset_state);
	offset = 43;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_leaf_dsp_exist);
	offset = 42;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_leaf_dsp_traffic_dis_commited);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->rst_type_sel);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pci_sync_for_fw_update_resp);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_sync_for_fw_update_start);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_rescan_required);
}

void reg_access_hca_mfrl_reg_ext_unpack(struct reg_access_hca_mfrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->reset_trigger = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->reset_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 44;
	ptr_struct->reset_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 43;
	ptr_struct->pci_leaf_dsp_exist = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 42;
	ptr_struct->pci_leaf_dsp_traffic_dis_commited = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 37;
	ptr_struct->rst_type_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 35;
	ptr_struct->pci_sync_for_fw_update_resp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 34;
	ptr_struct->pci_sync_for_fw_update_start = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->pci_rescan_required = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "reset_state          : " UH_FMT "\n", ptr_struct->reset_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_leaf_dsp_exist   : " UH_FMT "\n", ptr_struct->pci_leaf_dsp_exist);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_leaf_dsp_traffic_dis_commited : " UH_FMT "\n", ptr_struct->pci_leaf_dsp_traffic_dis_commited);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst_type_sel         : " UH_FMT "\n", ptr_struct->rst_type_sel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_resp : %s (" UH_FMT ")\n", (ptr_struct->pci_sync_for_fw_update_resp == 1 ? ("Acknowledgment") : ((ptr_struct->pci_sync_for_fw_update_resp == 2 ? ("Dis") : ((ptr_struct->pci_sync_for_fw_update_resp == 3 ? ("Reserved") : ("unknown")))))), ptr_struct->pci_sync_for_fw_update_resp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_start : " UH_FMT "\n", ptr_struct->pci_sync_for_fw_update_start);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_rescan_required  : " UH_FMT "\n", ptr_struct->pci_rescan_required);
}

unsigned int reg_access_hca_mfrl_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFRL_REG_EXT_SIZE;
}

void reg_access_hca_mfrl_reg_ext_dump(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfrl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mfsv_reg_ext_pack(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mfsv_reg_ext_unpack(struct reg_access_hca_mfsv_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mfsv_reg_ext_print(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfsv_reg_ext ========\n");

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

unsigned int reg_access_hca_mfsv_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MFSV_REG_EXT_SIZE;
}

void reg_access_hca_mfsv_reg_ext_dump(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mfsv_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mgir_ext_pack(const struct reg_access_hca_mgir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_mgir_hardware_info_ext_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_mgir_fw_info_ext_pack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_hca_mgir_sw_info_ext_pack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_hca_mgir_dev_info_ext_pack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_ext_unpack(struct reg_access_hca_mgir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_mgir_hardware_info_ext_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_hca_mgir_fw_info_ext_unpack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_hca_mgir_sw_info_ext_unpack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_hca_mgir_dev_info_ext_unpack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_hca_mgir_ext_print(const struct reg_access_hca_mgir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mgir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	reg_access_hca_mgir_hardware_info_ext_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info:\n");
	reg_access_hca_mgir_fw_info_ext_print(&(ptr_struct->fw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_info:\n");
	reg_access_hca_mgir_sw_info_ext_print(&(ptr_struct->sw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_info:\n");
	reg_access_hca_mgir_dev_info_ext_print(&(ptr_struct->dev_info), fd, indent_level + 1);
}

unsigned int reg_access_hca_mgir_ext_size(void)
{
	return REG_ACCESS_HCA_MGIR_EXT_SIZE;
}

void reg_access_hca_mgir_ext_dump(const struct reg_access_hca_mgir_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mgir_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mmdio_ext_pack(const struct reg_access_hca_mmdio_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mmdio_ext_unpack(struct reg_access_hca_mmdio_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mmdio_ext_print(const struct reg_access_hca_mmdio_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mmdio_ext ========\n");

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

unsigned int reg_access_hca_mmdio_ext_size(void)
{
	return REG_ACCESS_HCA_MMDIO_EXT_SIZE;
}

void reg_access_hca_mmdio_ext_dump(const struct reg_access_hca_mmdio_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mmdio_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mnvdi_reg_ext_pack(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_config_item_ext_pack(&(ptr_struct->configuration_item_header), ptr_buff + offset / 8);
}

void reg_access_hca_mnvdi_reg_ext_unpack(struct reg_access_hca_mnvdi_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_hca_config_item_ext_unpack(&(ptr_struct->configuration_item_header), ptr_buff + offset / 8);
}

void reg_access_hca_mnvdi_reg_ext_print(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mnvdi_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_header:\n");
	reg_access_hca_config_item_ext_print(&(ptr_struct->configuration_item_header), fd, indent_level + 1);
}

unsigned int reg_access_hca_mnvdi_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MNVDI_REG_EXT_SIZE;
}

void reg_access_hca_mnvdi_reg_ext_dump(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mnvdi_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mnvgc_reg_ext_pack(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nvda_read_factory_settings);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nvda_read_current_settings);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->priv_nv_other_host);
}

void reg_access_hca_mnvgc_reg_ext_unpack(struct reg_access_hca_mnvgc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->nvda_read_factory_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->nvda_read_current_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->priv_nv_other_host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mnvgc_reg_ext_print(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mnvgc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvda_read_factory_settings : " UH_FMT "\n", ptr_struct->nvda_read_factory_settings);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvda_read_current_settings : " UH_FMT "\n", ptr_struct->nvda_read_current_settings);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "priv_nv_other_host   : " UH_FMT "\n", ptr_struct->priv_nv_other_host);
}

unsigned int reg_access_hca_mnvgc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MNVGC_REG_EXT_SIZE;
}

void reg_access_hca_mnvgc_reg_ext_dump(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mnvgc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mnvia_reg_ext_pack(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->target);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->writer_id);
}

void reg_access_hca_mnvia_reg_ext_unpack(struct reg_access_hca_mnvia_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 23;
	ptr_struct->writer_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_hca_mnvia_reg_ext_print(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mnvia_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "target               : " UH_FMT "\n", ptr_struct->target);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "writer_id            : " UH_FMT "\n", ptr_struct->writer_id);
}

unsigned int reg_access_hca_mnvia_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MNVIA_REG_EXT_SIZE;
}

void reg_access_hca_mnvia_reg_ext_dump(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mnvia_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mnvqc_reg_ext_pack(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_rd);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_wr);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
}

void reg_access_hca_mnvqc_reg_ext_unpack(struct reg_access_hca_mnvqc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->type = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 63;
	ptr_struct->support_rd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->support_wr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mnvqc_reg_ext_print(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mnvqc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " U32H_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "support_rd           : " UH_FMT "\n", ptr_struct->support_rd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "support_wr           : " UH_FMT "\n", ptr_struct->support_wr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
}

unsigned int reg_access_hca_mnvqc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MNVQC_REG_EXT_SIZE;
}

void reg_access_hca_mnvqc_reg_ext_dump(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mnvqc_reg_ext_print(ptr_struct, fd, 0);
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

void reg_access_hca_mpegc_reg_ext_pack(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mpegc_reg_ext_unpack(struct reg_access_hca_mpegc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mpegc_reg_ext_print(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpegc_reg_ext ========\n");

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

unsigned int reg_access_hca_mpegc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MPEGC_REG_EXT_SIZE;
}

void reg_access_hca_mpegc_reg_ext_dump(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mpegc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mqis_reg_ext_pack(const struct reg_access_hca_mqis_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_mqis_reg_ext_unpack(struct reg_access_hca_mqis_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_mqis_reg_ext_print(const struct reg_access_hca_mqis_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mqis_reg_ext ========\n");

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

unsigned int reg_access_hca_mqis_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MQIS_REG_EXT_SIZE;
}

void reg_access_hca_mqis_reg_ext_dump(const struct reg_access_hca_mqis_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mqis_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mrsi_ext_pack(const struct reg_access_hca_mrsi_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reset_reason);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->crts);
}

void reg_access_hca_mrsi_ext_unpack(struct reg_access_hca_mrsi_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->device = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->reset_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->crts = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mrsi_ext_print(const struct reg_access_hca_mrsi_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mrsi_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device               : " UH_FMT "\n", ptr_struct->device);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_reason         : " UH_FMT "\n", ptr_struct->reset_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crts                 : " U64H_FMT "\n", ptr_struct->crts);
}

unsigned int reg_access_hca_mrsi_ext_size(void)
{
	return REG_ACCESS_HCA_MRSI_EXT_SIZE;
}

void reg_access_hca_mrsi_ext_dump(const struct reg_access_hca_mrsi_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mrsi_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_msgi_ext_pack(const struct reg_access_hca_msgi_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 6; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->serial_number[i]);
	}
	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->part_number[i]);
	}
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->revision);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->product_name[i]);
	}
}

void reg_access_hca_msgi_ext_unpack(struct reg_access_hca_msgi_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 6; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1024, 1);
		ptr_struct->serial_number[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 1024, 1);
		ptr_struct->part_number[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 448;
	ptr_struct->revision = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 1024, 1);
		ptr_struct->product_name[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_msgi_ext_print(const struct reg_access_hca_msgi_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_msgi_ext ========\n");

	for (i = 0; i < 6; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "serial_number_%03d   : " U32H_FMT "\n", i, ptr_struct->serial_number[i]);
	}
	for (i = 0; i < 5; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "part_number_%03d     : " U32H_FMT "\n", i, ptr_struct->part_number[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "revision             : " U32H_FMT "\n", ptr_struct->revision);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "product_name_%03d    : " U32H_FMT "\n", i, ptr_struct->product_name[i]);
	}
}

unsigned int reg_access_hca_msgi_ext_size(void)
{
	return REG_ACCESS_HCA_MSGI_EXT_SIZE;
}

void reg_access_hca_msgi_ext_dump(const struct reg_access_hca_msgi_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_msgi_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtcap_ext_pack(const struct reg_access_hca_mtcap_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->sensor_count);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 57;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->internal_sensor_count);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->sensor_map);
}

void reg_access_hca_mtcap_ext_unpack(struct reg_access_hca_mtcap_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	ptr_struct->sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 12;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 57;
	ptr_struct->internal_sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 64;
	ptr_struct->sensor_map = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mtcap_ext_print(const struct reg_access_hca_mtcap_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtcap_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_count         : " UH_FMT "\n", ptr_struct->sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "internal_sensor_count : " UH_FMT "\n", ptr_struct->internal_sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_map           : " U64H_FMT "\n", ptr_struct->sensor_map);
}

unsigned int reg_access_hca_mtcap_ext_size(void)
{
	return REG_ACCESS_HCA_MTCAP_EXT_SIZE;
}

void reg_access_hca_mtcap_ext_dump(const struct reg_access_hca_mtcap_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtcap_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtmp_ext_pack(const struct reg_access_hca_mtmp_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_index);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_temperature);
	offset = 67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sdme);
	offset = 66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->weme);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtr);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mte);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_hi);
	offset = 98;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->sdee);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tee);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_lo);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_name_hi);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_name_lo);
}

void reg_access_hca_mtmp_ext_unpack(struct reg_access_hca_mtmp_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->sensor_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 12;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->max_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 67;
	ptr_struct->sdme = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 66;
	ptr_struct->weme = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 65;
	ptr_struct->mtr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->mte = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 112;
	ptr_struct->temperature_threshold_hi = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 98;
	ptr_struct->sdee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 96;
	ptr_struct->tee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 144;
	ptr_struct->temperature_threshold_lo = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->sensor_name_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->sensor_name_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtmp_ext_print(const struct reg_access_hca_mtmp_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtmp_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_index         : " UH_FMT "\n", ptr_struct->sensor_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_temperature      : " UH_FMT "\n", ptr_struct->max_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdme                 : " UH_FMT "\n", ptr_struct->sdme);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "weme                 : " UH_FMT "\n", ptr_struct->weme);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtr                  : " UH_FMT "\n", ptr_struct->mtr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mte                  : " UH_FMT "\n", ptr_struct->mte);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_hi : " UH_FMT "\n", ptr_struct->temperature_threshold_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdee                 : " UH_FMT "\n", ptr_struct->sdee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tee                  : %s (" UH_FMT ")\n", (ptr_struct->tee == 0 ? ("do_not_generate_event") : ((ptr_struct->tee == 1 ? ("generate_event") : ((ptr_struct->tee == 2 ? ("generate_single_event") : ("unknown")))))), ptr_struct->tee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_lo : " UH_FMT "\n", ptr_struct->temperature_threshold_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_name_hi       : " U32H_FMT "\n", ptr_struct->sensor_name_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_name_lo       : " U32H_FMT "\n", ptr_struct->sensor_name_lo);
}

unsigned int reg_access_hca_mtmp_ext_size(void)
{
	return REG_ACCESS_HCA_MTMP_EXT_SIZE;
}

void reg_access_hca_mtmp_ext_dump(const struct reg_access_hca_mtmp_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtmp_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtrc_cap_reg_ext_pack(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
		reg_access_hca_string_db_parameters_ext_pack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_mtrc_cap_reg_ext_unpack(struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
		reg_access_hca_string_db_parameters_ext_unpack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_mtrc_cap_reg_ext_print(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_cap_reg_ext ========\n");

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
		reg_access_hca_string_db_parameters_ext_print(&(ptr_struct->string_db_param[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_hca_mtrc_cap_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MTRC_CAP_REG_EXT_SIZE;
}

void reg_access_hca_mtrc_cap_reg_ext_dump(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_cap_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtrc_stdb_reg_ext_pack(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->read_size);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_index);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->start_offset);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->read_size / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, (item_size_in_bytes * num_of_items_in_array) + (reg_access_hca_mtrc_stdb_reg_ext_size() * 8), 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_data[i]);
	}
}

void reg_access_hca_mtrc_stdb_reg_ext_unpack(struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	ptr_struct->read_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->string_db_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->start_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->read_size / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, (item_size_in_bytes * num_of_items_in_array) + (reg_access_hca_mtrc_stdb_reg_ext_size() * 8), 1);
		ptr_struct->string_db_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mtrc_stdb_reg_ext_print(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_stdb_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_size            : " UH_FMT "\n", ptr_struct->read_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_index      : " UH_FMT "\n", ptr_struct->string_db_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "start_offset         : " U32H_FMT "\n", ptr_struct->start_offset);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->read_size / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "string_db_data_%03d  : " U32H_FMT "\n", i, ptr_struct->string_db_data[i]);
	}
}

unsigned int reg_access_hca_mtrc_stdb_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MTRC_STDB_REG_EXT_SIZE;
}

void reg_access_hca_mtrc_stdb_reg_ext_dump(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_stdb_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_nic_cap_ext_reg_ext_pack(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cap_group);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cap_data[i]);
	}
}

void reg_access_hca_nic_cap_ext_reg_ext_unpack(struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->cap_group = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1024, 1);
		ptr_struct->cap_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_nic_cap_ext_reg_ext_print(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_cap_ext_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_group            : %s (" UH_FMT ")\n", (ptr_struct->cap_group == 1 ? ("DPA_CAP") : ("unknown")), ptr_struct->cap_group);
	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "cap_data_%03d        : " U32H_FMT "\n", i, ptr_struct->cap_data[i]);
	}
}

unsigned int reg_access_hca_nic_cap_ext_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_CAP_EXT_REG_EXT_SIZE;
}

void reg_access_hca_nic_cap_ext_reg_ext_dump(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_cap_ext_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_nic_dpa_eu_partition_reg_ext_pack(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->eu_partition_id);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modify_field_select);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_eug);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_vhca_id);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 6144, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->member_mask[i]);
	}
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(1552, 16, i, 6144, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vhca_id[i]);
	}
}

void reg_access_hca_nic_dpa_eu_partition_reg_ext_unpack(struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->eu_partition_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->modify_field_select = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->max_num_eug = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->num_vhca_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 6144, 1);
		ptr_struct->member_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(1552, 16, i, 6144, 1);
		ptr_struct->vhca_id[i] = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	}
}

void reg_access_hca_nic_dpa_eu_partition_reg_ext_print(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_dpa_eu_partition_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eu_partition_id      : " UH_FMT "\n", ptr_struct->eu_partition_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : %s (" UH_FMT ")\n", (ptr_struct->operation == 0 ? ("CRETAE") : ((ptr_struct->operation == 1 ? ("MODIFY") : ((ptr_struct->operation == 2 ? ("DESTROY") : ("unknown")))))), ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modify_field_select  : %s (" U32H_FMT ")\n", (ptr_struct->modify_field_select == 1 ? ("member_mask") : ((ptr_struct->modify_field_select == 2 ? ("max_num_eug") : ((ptr_struct->modify_field_select == 4 ? ("num_vhca_id_and_vhca_id") : ("unknown")))))), ptr_struct->modify_field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_eug          : " UH_FMT "\n", ptr_struct->max_num_eug);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_vhca_id          : " UH_FMT "\n", ptr_struct->num_vhca_id);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "member_mask_%03d     : " U32H_FMT "\n", i, ptr_struct->member_mask[i]);
	}
	for (i = 0; i < 256; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "vhca_id_%03d         : " UH_FMT "\n", i, ptr_struct->vhca_id[i]);
	}
}

unsigned int reg_access_hca_nic_dpa_eu_partition_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_DPA_EU_PARTITION_REG_EXT_SIZE;
}

void reg_access_hca_nic_dpa_eu_partition_reg_ext_dump(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_dpa_eu_partition_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_nic_dpa_eug_reg_ext_pack(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->eug_id);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modify_field_select);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 2048, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eug_name[i]);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 2048, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->member_mask[i]);
	}
}

void reg_access_hca_nic_dpa_eug_reg_ext_unpack(struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->eug_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->modify_field_select = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 2048, 1);
		ptr_struct->eug_name[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 2048, 1);
		ptr_struct->member_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_nic_dpa_eug_reg_ext_print(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_dpa_eug_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eug_id               : " UH_FMT "\n", ptr_struct->eug_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : %s (" UH_FMT ")\n", (ptr_struct->operation == 0 ? ("CRETAE") : ((ptr_struct->operation == 1 ? ("MODIFY") : ((ptr_struct->operation == 2 ? ("DESTROY") : ("unknown")))))), ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modify_field_select  : %s (" U32H_FMT ")\n", (ptr_struct->modify_field_select == 1 ? ("member_mask") : ("unknown")), ptr_struct->modify_field_select);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eug_name_%03d        : " U32H_FMT "\n", i, ptr_struct->eug_name[i]);
	}
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "member_mask_%03d     : " U32H_FMT "\n", i, ptr_struct->member_mask[i]);
	}
}

unsigned int reg_access_hca_nic_dpa_eug_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_DPA_EUG_REG_EXT_SIZE;
}

void reg_access_hca_nic_dpa_eug_reg_ext_dump(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_dpa_eug_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_pack(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_process_handle);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->count_state);
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_unpack(struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->dpa_process_handle = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->count_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_dpa_perf_ctrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_process_handle   : " U32H_FMT "\n", ptr_struct->dpa_process_handle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "count_state          : " UH_FMT "\n", ptr_struct->count_state);
}

unsigned int reg_access_hca_nic_dpa_perf_ctrl_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_DPA_PERF_CTRL_REG_EXT_SIZE;
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_dump(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_nic_dpa_perf_reg_ext_pack(const struct reg_access_hca_nic_dpa_perf_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_process_num);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_timer_frequency);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mkey);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->size);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->address);
}

void reg_access_hca_nic_dpa_perf_reg_ext_unpack(struct reg_access_hca_nic_dpa_perf_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->dpa_process_num = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->dpa_timer_frequency = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->address = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_nic_dpa_perf_reg_ext_print(const struct reg_access_hca_nic_dpa_perf_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_dpa_perf_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_process_num      : " U32H_FMT "\n", ptr_struct->dpa_process_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_timer_frequency  : " U32H_FMT "\n", ptr_struct->dpa_timer_frequency);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkey                 : " U32H_FMT "\n", ptr_struct->mkey);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " U32H_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U64H_FMT "\n", ptr_struct->address);
}

unsigned int reg_access_hca_nic_dpa_perf_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_DPA_PERF_REG_EXT_SIZE;
}

void reg_access_hca_nic_dpa_perf_reg_ext_dump(const struct reg_access_hca_nic_dpa_perf_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_dpa_perf_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_paos_reg_ext_pack(const struct reg_access_hca_paos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->e);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fd);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sleep_cap);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lock_mode);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
}

void reg_access_hca_paos_reg_ext_unpack(struct reg_access_hca_paos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 62;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 55;
	ptr_struct->fd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->sleep_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 36;
	ptr_struct->lock_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_paos_reg_ext_print(const struct reg_access_hca_paos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_paos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 1 ? ("up") : ((ptr_struct->oper_status == 2 ? ("down") : ((ptr_struct->oper_status == 4 ? ("down_by_port_failure") : ("unknown")))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("up") : ((ptr_struct->admin_status == 2 ? ("down_by_configuration") : ((ptr_struct->admin_status == 3 ? ("up_once") : ((ptr_struct->admin_status == 4 ? ("disabled_by_system") : ((ptr_struct->admin_status == 6 ? ("sleep") : ("unknown")))))))))), ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : %s (" UH_FMT ")\n", (ptr_struct->e == 0 ? ("Do_not_generate_event") : ((ptr_struct->e == 1 ? ("Generate_Event") : ((ptr_struct->e == 2 ? ("Generate_Single_Event") : ("unknown")))))), ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fd                   : " UH_FMT "\n", ptr_struct->fd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sleep_cap            : " UH_FMT "\n", ptr_struct->sleep_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock_mode            : %s (" UH_FMT ")\n", (ptr_struct->lock_mode == 1 ? ("Force_down_by_fuse") : ((ptr_struct->lock_mode == 2 ? ("Force_down_by_hard_wire") : ((ptr_struct->lock_mode == 4 ? ("Force_down_by_config") : ((ptr_struct->lock_mode == 8 ? ("Locked_after_down") : ("unknown")))))))), ptr_struct->lock_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
}

unsigned int reg_access_hca_paos_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PAOS_REG_EXT_SIZE;
}

void reg_access_hca_paos_reg_ext_dump(const struct reg_access_hca_paos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_paos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_pcnr_reg_ext_pack(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tuning_override);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->keep_phy_setting);
}

void reg_access_hca_pcnr_reg_ext_unpack(struct reg_access_hca_pcnr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->tuning_override = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->keep_phy_setting = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_pcnr_reg_ext_print(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pcnr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tuning_override      : " UH_FMT "\n", ptr_struct->tuning_override);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "keep_phy_setting     : " UH_FMT "\n", ptr_struct->keep_phy_setting);
}

unsigned int reg_access_hca_pcnr_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PCNR_REG_EXT_SIZE;
}

void reg_access_hca_pcnr_reg_ext_dump(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_pcnr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_pmaos_reg_ext_pack(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rst);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->e);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->error_type);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->operational_notification);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rev_incompatible);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secondary);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
}

void reg_access_hca_pmaos_reg_ext_unpack(struct reg_access_hca_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->rst = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 51;
	ptr_struct->error_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 44;
	ptr_struct->operational_notification = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 35;
	ptr_struct->rev_incompatible = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->secondary = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_pmaos_reg_ext_print(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pmaos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 0 ? ("initializing") : ((ptr_struct->oper_status == 1 ? ("plugged_enabled") : ((ptr_struct->oper_status == 2 ? ("unplugged") : ((ptr_struct->oper_status == 3 ? ("module_plugged_with_error") : ((ptr_struct->oper_status == 5 ? ("unknown") : ("unknown")))))))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("enabled") : ((ptr_struct->admin_status == 2 ? ("disabled_by_configuration") : ((ptr_struct->admin_status == 3 ? ("enabled_once") : ("unknown")))))), ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst                  : " UH_FMT "\n", ptr_struct->rst);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : %s (" UH_FMT ")\n", (ptr_struct->e == 0 ? ("Do_not_generate_event") : ((ptr_struct->e == 1 ? ("Generate_Event") : ((ptr_struct->e == 2 ? ("Generate_Single_Event") : ("unknown")))))), ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type           : %s (" UH_FMT ")\n", (ptr_struct->error_type == 0 ? ("Power_Budget_Exceeded") : ((ptr_struct->error_type == 1 ? ("Long_Range_for_non_MLNX_cable_or_module") : ((ptr_struct->error_type == 2 ? ("Bus_stuck") : ((ptr_struct->error_type == 3 ? ("bad_or_unsupported_EEPROM") : ((ptr_struct->error_type == 4 ? ("Enforce_part_number_list") : ((ptr_struct->error_type == 5 ? ("unsupported_cable") : ((ptr_struct->error_type == 6 ? ("High_Temperature") : ((ptr_struct->error_type == 7 ? ("bad_cable") : ((ptr_struct->error_type == 8 ? ("PMD_type_is_not_enabled") : ((ptr_struct->error_type == 12 ? ("pcie_system_power_slot_Exceeded") : ("unknown")))))))))))))))))))), ptr_struct->error_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operational_notification : " UH_FMT "\n", ptr_struct->operational_notification);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rev_incompatible     : " UH_FMT "\n", ptr_struct->rev_incompatible);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary            : " UH_FMT "\n", ptr_struct->secondary);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
}

unsigned int reg_access_hca_pmaos_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PMAOS_REG_EXT_SIZE;
}

void reg_access_hca_pmaos_reg_ext_dump(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_pmaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_pmlp_reg_ext_pack(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->width);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->m_lane_m);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rxtx);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_hca_lane_2_module_mapping_ext_pack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_pmlp_reg_ext_unpack(struct reg_access_hca_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 3;
	ptr_struct->m_lane_m = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->rxtx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_hca_lane_2_module_mapping_ext_unpack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_hca_pmlp_reg_ext_print(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pmlp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "width                : %s (" UH_FMT ")\n", (ptr_struct->width == 0 ? ("unmap_local_port") : ((ptr_struct->width == 1 ? ("x1") : ((ptr_struct->width == 2 ? ("x2") : ((ptr_struct->width == 4 ? ("x4") : ((ptr_struct->width == 8 ? ("x8") : ("unknown")))))))))), ptr_struct->width);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_lane_m             : " UH_FMT "\n", ptr_struct->m_lane_m);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rxtx                 : " UH_FMT "\n", ptr_struct->rxtx);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "lane_module_mapping_%03d:\n", i);
		reg_access_hca_lane_2_module_mapping_ext_print(&(ptr_struct->lane_module_mapping[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_hca_pmlp_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PMLP_REG_EXT_SIZE;
}

void reg_access_hca_pmlp_reg_ext_dump(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_pmlp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_reg_ext_pack(const struct reg_access_hca_ptys_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->proto_mask);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->transmit_allowed);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_tx_aba_param);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_ready_e);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_tx_ready);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_cap);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_admin);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved_high);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data_rate_oper);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->max_port_rate);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->an_status);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_capability);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_capability);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_capability);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_capability);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_admin);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_admin);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_admin);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_admin);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_oper);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_oper);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_oper);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_oper);
	offset = 380;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->connector_type);
	offset = 360;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->lane_rate_oper);
	offset = 359;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_active);
	offset = 358;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_admin);
	offset = 354;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->force_lt_frames_admin);
	offset = 353;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_lt_frames_cap);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_cap);
}

void reg_access_hca_ptys_reg_ext_unpack(struct reg_access_hca_ptys_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->proto_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 27;
	ptr_struct->transmit_allowed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 7;
	ptr_struct->force_tx_aba_param = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->tx_ready_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 3;
	ptr_struct->ee_tx_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->an_disable_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->an_disable_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->reserved_high = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->data_rate_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 36;
	ptr_struct->max_port_rate = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 32;
	ptr_struct->an_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ext_eth_proto_capability = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->eth_proto_capability = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->ib_proto_capability = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->ib_link_width_capability = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->ext_eth_proto_admin = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->eth_proto_admin = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 240;
	ptr_struct->ib_proto_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->ib_link_width_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 256;
	ptr_struct->ext_eth_proto_oper = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->eth_proto_oper = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 336;
	ptr_struct->ib_proto_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 320;
	ptr_struct->ib_link_width_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 380;
	ptr_struct->connector_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 360;
	ptr_struct->lane_rate_oper = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
	offset = 359;
	ptr_struct->xdr_2x_slow_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 358;
	ptr_struct->xdr_2x_slow_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 354;
	ptr_struct->force_lt_frames_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 353;
	ptr_struct->force_lt_frames_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 352;
	ptr_struct->xdr_2x_slow_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_ptys_reg_ext_print(const struct reg_access_hca_ptys_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "proto_mask           : %s (" UH_FMT ")\n", (ptr_struct->proto_mask == 1 ? ("InfiniBand") : ((ptr_struct->proto_mask == 4 ? ("Ethernet") : ("unknown")))), ptr_struct->proto_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "transmit_allowed     : " UH_FMT "\n", ptr_struct->transmit_allowed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("Near") : ((ptr_struct->port_type == 2 ? ("Internal_IC_Port") : ((ptr_struct->port_type == 3 ? ("Far") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_tx_aba_param   : " UH_FMT "\n", ptr_struct->force_tx_aba_param);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ready_e           : " UH_FMT "\n", ptr_struct->tx_ready_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_tx_ready          : " UH_FMT "\n", ptr_struct->ee_tx_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_cap       : " UH_FMT "\n", ptr_struct->an_disable_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_admin     : " UH_FMT "\n", ptr_struct->an_disable_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_high        : " UH_FMT "\n", ptr_struct->reserved_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_rate_oper       : " UH_FMT "\n", ptr_struct->data_rate_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_port_rate        : " UH_FMT "\n", ptr_struct->max_port_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_status            : %s (" UH_FMT ")\n", (ptr_struct->an_status == 0 ? ("Status_is_unavailable") : ((ptr_struct->an_status == 1 ? ("AN_completed_successfully") : ((ptr_struct->an_status == 2 ? ("AN_performed_but_failed") : ((ptr_struct->an_status == 3 ? ("AN_was_not_performed_link_is_up") : ((ptr_struct->an_status == 4 ? ("AN_was_not_performed_link_is_down") : ("unknown")))))))))), ptr_struct->an_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_capability : " U32H_FMT "\n", ptr_struct->ext_eth_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_capability : " U32H_FMT "\n", ptr_struct->eth_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_capability  : %s (" UH_FMT ")\n", (ptr_struct->ib_proto_capability == 1 ? ("SDR") : ((ptr_struct->ib_proto_capability == 2 ? ("DDR") : ((ptr_struct->ib_proto_capability == 4 ? ("QDR") : ((ptr_struct->ib_proto_capability == 8 ? ("FDR10") : ((ptr_struct->ib_proto_capability == 16 ? ("FDR") : ((ptr_struct->ib_proto_capability == 32 ? ("EDR") : ((ptr_struct->ib_proto_capability == 64 ? ("HDR") : ((ptr_struct->ib_proto_capability == 128 ? ("NDR") : ((ptr_struct->ib_proto_capability == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->ib_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_capability : " UH_FMT "\n", ptr_struct->ib_link_width_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_admin  : " U32H_FMT "\n", ptr_struct->ext_eth_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_admin      : " U32H_FMT "\n", ptr_struct->eth_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_admin       : " UH_FMT "\n", ptr_struct->ib_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_admin  : " UH_FMT "\n", ptr_struct->ib_link_width_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_oper   : " U32H_FMT "\n", ptr_struct->ext_eth_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_oper       : " U32H_FMT "\n", ptr_struct->eth_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_oper        : " UH_FMT "\n", ptr_struct->ib_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_oper   : " UH_FMT "\n", ptr_struct->ib_link_width_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "connector_type       : %s (" UH_FMT ")\n", (ptr_struct->connector_type == 0 ? ("No_connector_or_unknown") : ((ptr_struct->connector_type == 1 ? ("PORT_NONE") : ((ptr_struct->connector_type == 2 ? ("PORT_TP") : ((ptr_struct->connector_type == 3 ? ("PORT_AUI") : ((ptr_struct->connector_type == 4 ? ("PORT_BNC") : ((ptr_struct->connector_type == 5 ? ("PORT_MII") : ((ptr_struct->connector_type == 6 ? ("PORT_FIBRE") : ((ptr_struct->connector_type == 7 ? ("PORT_DA") : ((ptr_struct->connector_type == 8 ? ("PORT_OTHER") : ("unknown")))))))))))))))))), ptr_struct->connector_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_oper       : " UH_FMT "\n", ptr_struct->lane_rate_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_active   : " UH_FMT "\n", ptr_struct->xdr_2x_slow_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_admin    : " UH_FMT "\n", ptr_struct->xdr_2x_slow_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_lt_frames_admin : " UH_FMT "\n", ptr_struct->force_lt_frames_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_lt_frames_cap  : " UH_FMT "\n", ptr_struct->force_lt_frames_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_cap      : " UH_FMT "\n", ptr_struct->xdr_2x_slow_cap);
}

unsigned int reg_access_hca_ptys_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_REG_EXT_SIZE;
}

void reg_access_hca_ptys_reg_ext_dump(const struct reg_access_hca_ptys_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_resource_dump_ext_pack(const struct reg_access_hca_resource_dump_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_hca_resource_dump_ext_unpack(struct reg_access_hca_resource_dump_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_hca_resource_dump_ext_print(const struct reg_access_hca_resource_dump_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_resource_dump_ext ========\n");

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

unsigned int reg_access_hca_resource_dump_ext_size(void)
{
	return REG_ACCESS_HCA_RESOURCE_DUMP_EXT_SIZE;
}

void reg_access_hca_resource_dump_ext_dump(const struct reg_access_hca_resource_dump_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_resource_dump_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_nic_dpa_eu_partition_reg_ext_pack(&(ptr_struct->nic_dpa_eu_partition_reg_ext), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_nic_dpa_eu_partition_reg_ext_unpack(&(ptr_struct->nic_dpa_eu_partition_reg_ext), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_reg_access_hca_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mqis_reg_ext:\n");
	reg_access_hca_mqis_reg_ext_print(&(ptr_struct->mqis_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_reg_ext:\n");
	reg_access_hca_ptys_reg_ext_print(&(ptr_struct->ptys_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties_ext:\n");
	reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->mcqi_linkx_properties_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfsv_reg_ext:\n");
	reg_access_hca_mfsv_reg_ext_print(&(ptr_struct->mfsv_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfbe_reg_ext:\n");
	reg_access_hca_mfbe_reg_ext_print(&(ptr_struct->mfbe_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcam_reg_ext:\n");
	reg_access_hca_mcam_reg_ext_print(&(ptr_struct->mcam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_stdb_reg_ext:\n");
	reg_access_hca_mtrc_stdb_reg_ext_print(&(ptr_struct->mtrc_stdb_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_cap_ext_reg_ext:\n");
	reg_access_hca_nic_cap_ext_reg_ext_print(&(ptr_struct->nic_cap_ext_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcnr_reg_ext:\n");
	reg_access_hca_pcnr_reg_ext_print(&(ptr_struct->pcnr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_hca_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_cap_reg_ext:\n");
	reg_access_hca_mtrc_cap_reg_ext_print(&(ptr_struct->mtrc_cap_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvdi_reg_ext:\n");
	reg_access_hca_mnvdi_reg_ext_print(&(ptr_struct->mnvdi_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_reg_ext:\n");
	reg_access_hca_mcqi_reg_ext_print(&(ptr_struct->mcqi_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_dump_ext:\n");
	reg_access_hca_resource_dump_ext_print(&(ptr_struct->resource_dump_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcda_reg_ext:\n");
	reg_access_hca_mcda_reg_ext_print(&(ptr_struct->mcda_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvgc_reg_ext:\n");
	reg_access_hca_mnvgc_reg_ext_print(&(ptr_struct->mnvgc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmdio_ext:\n");
	reg_access_hca_mmdio_ext_print(&(ptr_struct->mmdio_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "paos_reg_ext:\n");
	reg_access_hca_paos_reg_ext_print(&(ptr_struct->paos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dtor_reg_ext:\n");
	reg_access_hca_dtor_reg_ext_print(&(ptr_struct->dtor_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvia_reg_ext:\n");
	reg_access_hca_mnvia_reg_ext_print(&(ptr_struct->mnvia_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_hca_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcap_ext:\n");
	reg_access_hca_mtcap_ext_print(&(ptr_struct->mtcap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfmc_reg_ext:\n");
	reg_access_hca_mfmc_reg_ext_print(&(ptr_struct->mfmc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqs_reg_ext:\n");
	reg_access_hca_mcqs_reg_ext_print(&(ptr_struct->mcqs_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap_ext:\n");
	reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->mcqi_cap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method_ext:\n");
	reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->mcqi_activation_method_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtmp_ext:\n");
	reg_access_hca_mtmp_ext_print(&(ptr_struct->mtmp_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpegc_reg_ext:\n");
	reg_access_hca_mpegc_reg_ext_print(&(ptr_struct->mpegc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_eu_partition_reg_ext:\n");
	reg_access_hca_nic_dpa_eu_partition_reg_ext_print(&(ptr_struct->nic_dpa_eu_partition_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_eug_reg_ext:\n");
	reg_access_hca_nic_dpa_eug_reg_ext_print(&(ptr_struct->nic_dpa_eug_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpegc_reg:\n");
	reg_access_hca_mpegc_reg_print(&(ptr_struct->mpegc_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfpa_reg_ext:\n");
	reg_access_hca_mfpa_reg_ext_print(&(ptr_struct->mfpa_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfba_reg_ext:\n");
	reg_access_hca_mfba_reg_ext_print(&(ptr_struct->mfba_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_perf_ctrl_reg_ext:\n");
	reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(&(ptr_struct->nic_dpa_perf_ctrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir_ext:\n");
	reg_access_hca_mgir_ext_print(&(ptr_struct->mgir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version_ext:\n");
	reg_access_hca_mcqi_version_ext_print(&(ptr_struct->mcqi_version_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpcir_ext:\n");
	reg_access_hca_mpcir_ext_print(&(ptr_struct->mpcir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcia_ext:\n");
	reg_access_hca_mcia_ext_print(&(ptr_struct->mcia_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvqc_reg_ext:\n");
	reg_access_hca_mnvqc_reg_ext_print(&(ptr_struct->mnvqc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "msgi_ext:\n");
	reg_access_hca_msgi_ext_print(&(ptr_struct->msgi_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcc_reg_ext:\n");
	reg_access_hca_mcc_reg_ext_print(&(ptr_struct->mcc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_perf_reg_ext:\n");
	reg_access_hca_nic_dpa_perf_reg_ext_print(&(ptr_struct->nic_dpa_perf_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfrl_reg_ext:\n");
	reg_access_hca_mfrl_reg_ext_print(&(ptr_struct->mfrl_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_reg_access_hca_Nodes_size(void)
{
	return REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE;
}

void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd)
{
	reg_access_hca_reg_access_hca_Nodes_print(ptr_struct, fd, 0);
}
