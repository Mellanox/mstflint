
/*
* Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
*
*  Version: $Id$
*
*/
 

/***
         *** This file was generated at "2025-12-18 11:34:54"
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

void reg_access_hca_configuration_item_type_class_multi_instance_ext_pack(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->parameter_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_multi_instance_ext_unpack(struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_configuration_item_type_class_multi_instance_ext_print(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_configuration_item_type_class_multi_instance_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int reg_access_hca_configuration_item_type_class_multi_instance_ext_size(void)
{
	return REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_MULTI_INSTANCE_EXT_SIZE;
}

void reg_access_hca_configuration_item_type_class_multi_instance_ext_dump(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_configuration_item_type_class_multi_instance_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_pack(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->parameter_index);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pf_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void reg_access_hca_configuration_item_type_class_per_host_pf_ext_unpack(struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 14;
	ptr_struct->pf_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
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
	fprintf(fd, "pf_index             : " UH_FMT "\n", ptr_struct->pf_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_id              : " UH_FMT "\n", ptr_struct->host_id);
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

void reg_access_hca_date_time_layout_ext_pack(const struct reg_access_hca_date_time_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hours);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minutes);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->seconds);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->day);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->month);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->year);
}

void reg_access_hca_date_time_layout_ext_unpack(struct reg_access_hca_date_time_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->hours = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_hca_date_time_layout_ext_print(const struct reg_access_hca_date_time_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_date_time_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hours                : " UH_FMT "\n", ptr_struct->hours);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minutes              : " UH_FMT "\n", ptr_struct->minutes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seconds              : " UH_FMT "\n", ptr_struct->seconds);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "day                  : " UH_FMT "\n", ptr_struct->day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "month                : " UH_FMT "\n", ptr_struct->month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "year                 : " UH_FMT "\n", ptr_struct->year);
}

unsigned int reg_access_hca_date_time_layout_ext_size(void)
{
	return REG_ACCESS_HCA_DATE_TIME_LAYOUT_EXT_SIZE;
}

void reg_access_hca_date_time_layout_ext_dump(const struct reg_access_hca_date_time_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_date_time_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mcqi_dpa_metadata_ext_pack(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->subtype);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->length);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_app_version);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_os_api_version);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_fw_api_version);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 832, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_app_uuid[i]);
	}
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 832, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_app_description_string[i]);
	}
}

void reg_access_hca_mcqi_dpa_metadata_ext_unpack(struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->subtype = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->dpa_app_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->dpa_os_api_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->dpa_fw_api_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 832, 1);
		ptr_struct->dpa_app_uuid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 832, 1);
		ptr_struct->dpa_app_description_string[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mcqi_dpa_metadata_ext_print(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_dpa_metadata_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subtype              : " UH_FMT "\n", ptr_struct->subtype);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_app_version      : " U32H_FMT "\n", ptr_struct->dpa_app_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_os_api_version   : " U32H_FMT "\n", ptr_struct->dpa_os_api_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_fw_api_version   : " U32H_FMT "\n", ptr_struct->dpa_fw_api_version);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dpa_app_uuid_%03d    : " U32H_FMT "\n", i, ptr_struct->dpa_app_uuid[i]);
	}
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dpa_app_description_string_%03d : " U32H_FMT "\n", i, ptr_struct->dpa_app_description_string[i]);
	}
}

unsigned int reg_access_hca_mcqi_dpa_metadata_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE;
}

void reg_access_hca_mcqi_dpa_metadata_ext_dump(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_dpa_metadata_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_MRSV_CX_7_Value_ext_pack(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->disable_inband_recovery);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->primary_is_pcore1);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->two_p_core_active);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->socket_direct);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_reversal);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_partition_1);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_partition_0);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->osc_freq_1);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->osc_freq_0);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->core_bypass_n);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fnp);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->straps_mask);
}

void reg_access_hca_MRSV_CX_7_Value_ext_unpack(struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 10;
	ptr_struct->disable_inband_recovery = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 9;
	ptr_struct->primary_is_pcore1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->two_p_core_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 7;
	ptr_struct->socket_direct = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->pci_reversal = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->pci_partition_1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->pci_partition_0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->osc_freq_1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->osc_freq_0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->core_bypass_n = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->fnp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->straps_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_MRSV_CX_7_Value_ext_print(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_MRSV_CX_7_Value_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "disable_inband_recovery : " UH_FMT "\n", ptr_struct->disable_inband_recovery);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "primary_is_pcore1    : " UH_FMT "\n", ptr_struct->primary_is_pcore1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "two_p_core_active    : " UH_FMT "\n", ptr_struct->two_p_core_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "socket_direct        : " UH_FMT "\n", ptr_struct->socket_direct);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_reversal         : " UH_FMT "\n", ptr_struct->pci_reversal);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_partition_1      : " UH_FMT "\n", ptr_struct->pci_partition_1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_partition_0      : " UH_FMT "\n", ptr_struct->pci_partition_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "osc_freq_1           : " UH_FMT "\n", ptr_struct->osc_freq_1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "osc_freq_0           : " UH_FMT "\n", ptr_struct->osc_freq_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_bypass_n        : " UH_FMT "\n", ptr_struct->core_bypass_n);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fnp                  : " UH_FMT "\n", ptr_struct->fnp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "straps_mask          : " U32H_FMT "\n", ptr_struct->straps_mask);
}

unsigned int reg_access_hca_MRSV_CX_7_Value_ext_size(void)
{
	return REG_ACCESS_HCA_MRSV_CX_7_VALUE_EXT_SIZE;
}

void reg_access_hca_MRSV_CX_7_Value_ext_dump(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_MRSV_CX_7_Value_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_config_item_type_auto_ext_pack(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_configuration_item_type_class_physical_port_ext_pack(&(ptr_struct->configuration_item_type_class_physical_port_ext), ptr_buff);
}

void reg_access_hca_config_item_type_auto_ext_unpack(union reg_access_hca_config_item_type_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_configuration_item_type_class_physical_port_ext_unpack(&(ptr_struct->configuration_item_type_class_physical_port_ext), ptr_buff);
}

void reg_access_hca_config_item_type_auto_ext_print(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_config_item_type_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_file_ext:\n");
	reg_access_hca_configuration_item_type_class_file_ext_print(&(ptr_struct->configuration_item_type_class_file_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_global_ext:\n");
	reg_access_hca_configuration_item_type_class_global_ext_print(&(ptr_struct->configuration_item_type_class_global_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_host_ext:\n");
	reg_access_hca_configuration_item_type_class_host_ext_print(&(ptr_struct->configuration_item_type_class_host_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_log_ext:\n");
	reg_access_hca_configuration_item_type_class_log_ext_print(&(ptr_struct->configuration_item_type_class_log_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_module_ext:\n");
	reg_access_hca_configuration_item_type_class_module_ext_print(&(ptr_struct->configuration_item_type_class_module_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_multi_instance_ext:\n");
	reg_access_hca_configuration_item_type_class_multi_instance_ext_print(&(ptr_struct->configuration_item_type_class_multi_instance_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_per_host_pf_ext:\n");
	reg_access_hca_configuration_item_type_class_per_host_pf_ext_print(&(ptr_struct->configuration_item_type_class_per_host_pf_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "configuration_item_type_class_physical_port_ext:\n");
	reg_access_hca_configuration_item_type_class_physical_port_ext_print(&(ptr_struct->configuration_item_type_class_physical_port_ext), fd, indent_level + 1);
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

void reg_access_hca_mcqi_dpa_apps_info_ext_pack(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->total_number_of_entries);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);
	offset = 64;
	reg_access_hca_mcqi_dpa_metadata_ext_pack(&(ptr_struct->dpa_app_metadata), ptr_buff + offset / 8);
}

void reg_access_hca_mcqi_dpa_apps_info_ext_unpack(struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->total_number_of_entries = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	reg_access_hca_mcqi_dpa_metadata_ext_unpack(&(ptr_struct->dpa_app_metadata), ptr_buff + offset / 8);
}

void reg_access_hca_mcqi_dpa_apps_info_ext_print(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_dpa_apps_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_number_of_entries : " UH_FMT "\n", ptr_struct->total_number_of_entries);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_app_metadata:\n");
	reg_access_hca_mcqi_dpa_metadata_ext_print(&(ptr_struct->dpa_app_metadata), fd, indent_level + 1);
}

unsigned int reg_access_hca_mcqi_dpa_apps_info_ext_size(void)
{
	return REG_ACCESS_HCA_MCQI_DPA_APPS_INFO_EXT_SIZE;
}

void reg_access_hca_mcqi_dpa_apps_info_ext_dump(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mcqi_dpa_apps_info_ext_print(ptr_struct, fd, 0);
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
	reg_access_hca_date_time_layout_ext_pack(&(ptr_struct->build_time), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_date_time_layout_ext_pack(&(ptr_struct->user_defined_time), ptr_buff + offset / 8);
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
	reg_access_hca_date_time_layout_ext_unpack(&(ptr_struct->build_time), ptr_buff + offset / 8);
	offset = 128;
	reg_access_hca_date_time_layout_ext_unpack(&(ptr_struct->user_defined_time), ptr_buff + offset / 8);
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
	fprintf(fd, "build_time:\n");
	reg_access_hca_date_time_layout_ext_print(&(ptr_struct->build_time), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "user_defined_time:\n");
	reg_access_hca_date_time_layout_ext_print(&(ptr_struct->user_defined_time), fd, indent_level + 1);
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

void reg_access_hca_nic_cap_ext_dpa_cap_ext_pack(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_dpa_eug);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_dpa_eu);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_dpa_eu_partition);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_dpa_eu_per_group);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->dpa_perf_sample_type);
	offset = 71;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->max_num_partition_vhca_id);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->process_perf_cnt);
}

void reg_access_hca_nic_cap_ext_dpa_cap_ext_unpack(struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->max_num_dpa_eug = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->max_num_dpa_eu = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->max_num_dpa_eu_partition = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->max_num_dpa_eu_per_group = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->dpa_perf_sample_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 71;
	ptr_struct->max_num_partition_vhca_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	offset = 65;
	ptr_struct->process_perf_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_nic_cap_ext_dpa_cap_ext_print(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_cap_ext_dpa_cap_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_dpa_eug      : " UH_FMT "\n", ptr_struct->max_num_dpa_eug);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_dpa_eu       : " UH_FMT "\n", ptr_struct->max_num_dpa_eu);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_dpa_eu_partition : " UH_FMT "\n", ptr_struct->max_num_dpa_eu_partition);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_dpa_eu_per_group : " UH_FMT "\n", ptr_struct->max_num_dpa_eu_per_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_perf_sample_type : %s (" UH_FMT ")\n", (ptr_struct->dpa_perf_sample_type == 1 ? ("CUMMULATIVE_EVENT") : ((ptr_struct->dpa_perf_sample_type == 2 ? ("EVENT_TRACER") : ("unknown")))), ptr_struct->dpa_perf_sample_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_partition_vhca_id : " UH_FMT "\n", ptr_struct->max_num_partition_vhca_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "process_perf_cnt     : " UH_FMT "\n", ptr_struct->process_perf_cnt);
}

unsigned int reg_access_hca_nic_cap_ext_dpa_cap_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_CAP_EXT_DPA_CAP_EXT_SIZE;
}

void reg_access_hca_nic_cap_ext_dpa_cap_ext_dump(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_cap_ext_dpa_cap_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_ext_proto_ib_admin_ext_pack(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_proto_ib);
}

void reg_access_hca_ptys_ext_proto_ib_admin_ext_unpack(struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ext_proto_ib = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_ptys_ext_proto_ib_admin_ext_print(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_ext_proto_ib_admin_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_proto_ib         : %s (" U32H_FMT ")\n", (ptr_struct->ext_proto_ib == 1 ? ("SDR_1x") : ((ptr_struct->ext_proto_ib == 2 ? ("SDR_2x") : ((ptr_struct->ext_proto_ib == 4 ? ("SDR_4x") : ((ptr_struct->ext_proto_ib == 4096 ? ("FDR_4x") : ((ptr_struct->ext_proto_ib == 16384 ? ("EDR_2x") : ((ptr_struct->ext_proto_ib == 32768 ? ("EDR_4x") : ((ptr_struct->ext_proto_ib == 65536 ? ("HDR_1x") : ((ptr_struct->ext_proto_ib == 131072 ? ("HDR_2x") : ((ptr_struct->ext_proto_ib == 262144 ? ("HDR_4x") : ((ptr_struct->ext_proto_ib == 1048576 ? ("NDR_1x") : ((ptr_struct->ext_proto_ib == 2097152 ? ("NDR_2x") : ((ptr_struct->ext_proto_ib == 4194304 ? ("NDR_4x") : ((ptr_struct->ext_proto_ib == 16777216 ? ("XDR_1x") : ((ptr_struct->ext_proto_ib == 33554432 ? ("XDR_2x") : ((ptr_struct->ext_proto_ib == 67108864 ? ("XDR_4x") : ("unknown")))))))))))))))))))))))))))))), ptr_struct->ext_proto_ib);
}

unsigned int reg_access_hca_ptys_ext_proto_ib_admin_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_EXT_PROTO_IB_ADMIN_EXT_SIZE;
}

void reg_access_hca_ptys_ext_proto_ib_admin_ext_dump(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_ext_proto_ib_admin_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_pack(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_proto_ib);
}

void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_unpack(struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ext_proto_ib = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_ext_proto_ib_cap_oper_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_proto_ib         : %s (" U32H_FMT ")\n", (ptr_struct->ext_proto_ib == 1 ? ("SDR_1x") : ((ptr_struct->ext_proto_ib == 2 ? ("SDR_2x") : ((ptr_struct->ext_proto_ib == 4 ? ("SDR_4x") : ((ptr_struct->ext_proto_ib == 4096 ? ("FDR_4x") : ((ptr_struct->ext_proto_ib == 16384 ? ("EDR_2x") : ((ptr_struct->ext_proto_ib == 32768 ? ("EDR_4x") : ((ptr_struct->ext_proto_ib == 65536 ? ("HDR_1x") : ((ptr_struct->ext_proto_ib == 131072 ? ("HDR_2x") : ((ptr_struct->ext_proto_ib == 262144 ? ("HDR_4x") : ((ptr_struct->ext_proto_ib == 1048576 ? ("NDR_1x") : ((ptr_struct->ext_proto_ib == 2097152 ? ("NDR_2x") : ((ptr_struct->ext_proto_ib == 4194304 ? ("NDR_4x") : ((ptr_struct->ext_proto_ib == 16777216 ? ("XDR_1x") : ((ptr_struct->ext_proto_ib == 33554432 ? ("XDR_2x") : ((ptr_struct->ext_proto_ib == 67108864 ? ("XDR_4x") : ("unknown")))))))))))))))))))))))))))))), ptr_struct->ext_proto_ib);
}

unsigned int reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_EXT_PROTO_IB_CAP_OPER_EXT_SIZE;
}

void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_dump(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_pack(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_proto_nvlink);
}

void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_unpack(struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ext_proto_nvlink = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_print(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_ext_proto_nvlink_admin_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_proto_nvlink     : " U32H_FMT "\n", ptr_struct->ext_proto_nvlink);
}

unsigned int reg_access_hca_ptys_ext_proto_nvlink_admin_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_EXT_PROTO_NVLINK_ADMIN_EXT_SIZE;
}

void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_dump(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_ext_proto_nvlink_admin_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_proto_nvlink);
}

void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ext_proto_nvlink = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_proto_nvlink     : " U32H_FMT "\n", ptr_struct->ext_proto_nvlink);
}

unsigned int reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_EXT_PROTO_NVLINK_CAP_OPER_EXT_SIZE;
}

void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_dump(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(ptr_struct, fd, 0);
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

void reg_access_hca_MRSV_data_auto_ext_pack(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_MRSV_CX_7_Value_ext_pack(&(ptr_struct->MRSV_CX_7_Value_ext), ptr_buff);
}

void reg_access_hca_MRSV_data_auto_ext_unpack(union reg_access_hca_MRSV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_MRSV_CX_7_Value_ext_unpack(&(ptr_struct->MRSV_CX_7_Value_ext), ptr_buff);
}

void reg_access_hca_MRSV_data_auto_ext_print(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_MRSV_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRSV_CX_7_Value_ext:\n");
	reg_access_hca_MRSV_CX_7_Value_ext_print(&(ptr_struct->MRSV_CX_7_Value_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_MRSV_data_auto_ext_size(void)
{
	return REG_ACCESS_HCA_MRSV_DATA_AUTO_EXT_SIZE;
}

void reg_access_hca_MRSV_data_auto_ext_dump(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_MRSV_data_auto_ext_print(ptr_struct, fd, 0);
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
	fprintf(fd, "access_mode          : %s (" UH_FMT ")\n", (ptr_struct->access_mode == 0 ? ("NEXT") : ((ptr_struct->access_mode == 1 ? ("CURRENT") : ((ptr_struct->access_mode == 2 ? ("FACTORY") : ("unknown")))))), ptr_struct->access_mode);
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
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mode_b_map);
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
	offset = 1;
	ptr_struct->mode_b_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode_b_map           : " UH_FMT "\n", ptr_struct->mode_b_map);
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
	reg_access_hca_mcqi_version_ext_pack(&(ptr_struct->mcqi_version_ext), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_ext_unpack(union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_mcqi_version_ext_unpack(&(ptr_struct->mcqi_version_ext), ptr_buff);
}

void reg_access_hca_mcqi_reg_data_auto_ext_print(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mcqi_reg_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method_ext:\n");
	reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->mcqi_activation_method_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap_ext:\n");
	reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->mcqi_cap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_clock_source_properties_ext:\n");
	reg_access_hca_mcqi_clock_source_properties_ext_print(&(ptr_struct->mcqi_clock_source_properties_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_dpa_apps_info_ext:\n");
	reg_access_hca_mcqi_dpa_apps_info_ext_print(&(ptr_struct->mcqi_dpa_apps_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties_ext:\n");
	reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->mcqi_linkx_properties_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version_ext:\n");
	reg_access_hca_mcqi_version_ext_print(&(ptr_struct->mcqi_version_ext), fd, indent_level + 1);
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
	offset = 441;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->life_cycle_msb);
	offset = 436;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev_state);
	offset = 434;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->issu_able);
	offset = 433;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pds);
	offset = 432;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ec_offload_engine_disabled);
	offset = 427;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->dev_counter);
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
	offset = 441;
	ptr_struct->life_cycle_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 436;
	ptr_struct->dev_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 434;
	ptr_struct->issu_able = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 433;
	ptr_struct->pds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 432;
	ptr_struct->ec_offload_engine_disabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 427;
	ptr_struct->dev_counter = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "life_cycle_msb       : " UH_FMT "\n", ptr_struct->life_cycle_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_state            : " UH_FMT "\n", ptr_struct->dev_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_able            : " UH_FMT "\n", ptr_struct->issu_able);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pds                  : " UH_FMT "\n", ptr_struct->pds);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ec_offload_engine_disabled : " UH_FMT "\n", ptr_struct->ec_offload_engine_disabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_counter          : " UH_FMT "\n", ptr_struct->dev_counter);
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
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->num_ports);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->ib_mad_gen);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_dev_id);
	offset = 110;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->module_master_fw_default);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cpo_indication);
	offset = 99;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ga_valid);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->development);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pci_switch_only_mode);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->manufacturing_base_mac_47_32);
	offset = 138;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->ga);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->chip_type);
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
	offset = 36;
	ptr_struct->num_ports = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 33;
	ptr_struct->ib_mad_gen = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 80;
	ptr_struct->hw_dev_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 110;
	ptr_struct->module_master_fw_default = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 100;
	ptr_struct->cpo_indication = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 99;
	ptr_struct->ga_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 97;
	ptr_struct->development = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->pci_switch_only_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 144;
	ptr_struct->manufacturing_base_mac_47_32 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 138;
	ptr_struct->ga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 132;
	ptr_struct->chip_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
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
	fprintf(fd, "ib_mad_gen           : " UH_FMT "\n", ptr_struct->ib_mad_gen);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_dev_id            : " UH_FMT "\n", ptr_struct->hw_dev_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_master_fw_default : " UH_FMT "\n", ptr_struct->module_master_fw_default);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cpo_indication       : " UH_FMT "\n", ptr_struct->cpo_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ga_valid             : " UH_FMT "\n", ptr_struct->ga_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "development          : " UH_FMT "\n", ptr_struct->development);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_switch_only_mode : " UH_FMT "\n", ptr_struct->pci_switch_only_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_47_32 : " UH_FMT "\n", ptr_struct->manufacturing_base_mac_47_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ga                   : " UH_FMT "\n", ptr_struct->ga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "chip_type            : " UH_FMT "\n", ptr_struct->chip_type);
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

void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_pack(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_nic_cap_ext_dpa_cap_ext_pack(&(ptr_struct->nic_cap_ext_dpa_cap_ext), ptr_buff);
}

void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_unpack(union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_nic_cap_ext_dpa_cap_ext_unpack(&(ptr_struct->nic_cap_ext_dpa_cap_ext), ptr_buff);
}

void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_print(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_cap_ext_dpa_cap_ext:\n");
	reg_access_hca_nic_cap_ext_dpa_cap_ext_print(&(ptr_struct->nic_cap_ext_dpa_cap_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_CAP_EXT_REG_CAP_DATA_AUTO_EXT_SIZE;
}

void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_dump(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_admin_ext_pack(&(ptr_struct->ptys_ext_proto_nvlink_admin_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_admin_ext_unpack(&(ptr_struct->ptys_ext_proto_nvlink_admin_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_ib_admin_ext:\n");
	reg_access_hca_ptys_ext_proto_ib_admin_ext_print(&(ptr_struct->ptys_ext_proto_ib_admin_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_nvlink_admin_ext:\n");
	reg_access_hca_ptys_ext_proto_nvlink_admin_ext_print(&(ptr_struct->ptys_ext_proto_nvlink_admin_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_ADMIN_AUTO_EXT_SIZE;
}

void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_ib_cap_oper_ext:\n");
	reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(&(ptr_struct->ptys_ext_proto_ib_cap_oper_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_nvlink_cap_oper_ext:\n");
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_CAP_AUTO_EXT_SIZE;
}

void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff);
}

void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_ib_cap_oper_ext:\n");
	reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(&(ptr_struct->ptys_ext_proto_ib_cap_oper_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_ext_proto_nvlink_cap_oper_ext:\n");
	reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(&(ptr_struct->ptys_ext_proto_nvlink_cap_oper_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_size(void)
{
	return REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_OPER_AUTO_EXT_SIZE;
}

void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_print(ptr_struct, fd, 0);
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
	*ptr_struct = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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

void reg_access_hca_MRSV_ext_pack(const struct reg_access_hca_MRSV_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ssid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->v);
	offset = 128;
	switch (ptr_struct->ssid) {
	case 0x0:
		offset = 128;
		reg_access_hca_MRSV_CX_7_Value_ext_pack(&(ptr_struct->data.MRSV_CX_7_Value_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_MRSV_ext_unpack(struct reg_access_hca_MRSV_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->ssid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->v = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	switch (ptr_struct->ssid) {
	case 0x0:
		offset = 128;
		reg_access_hca_MRSV_CX_7_Value_ext_unpack(&(ptr_struct->data.MRSV_CX_7_Value_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_MRSV_ext_print(const struct reg_access_hca_MRSV_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_MRSV_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ssid                 : %s (" UH_FMT ")\n", (ptr_struct->ssid == 0 ? ("bf3") : ("unknown")), ptr_struct->ssid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "v                    : " UH_FMT "\n", ptr_struct->v);
	switch (ptr_struct->ssid) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRSV_CX_7_Value_ext:\n");
		reg_access_hca_MRSV_CX_7_Value_ext_print(&(ptr_struct->data.MRSV_CX_7_Value_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_hca_MRSV_ext_size(void)
{
	return REG_ACCESS_HCA_MRSV_EXT_SIZE;
}

void reg_access_hca_MRSV_ext_dump(const struct reg_access_hca_MRSV_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_MRSV_ext_print(ptr_struct, fd, 0);
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
	offset = 480;
	reg_access_hca_default_timeout_ext_pack(&(ptr_struct->EMBEDDED_CPU_OS_SHUTDOWN_TO), ptr_buff + offset / 8);
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
	offset = 480;
	reg_access_hca_default_timeout_ext_unpack(&(ptr_struct->EMBEDDED_CPU_OS_SHUTDOWN_TO), ptr_buff + offset / 8);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "EMBEDDED_CPU_OS_SHUTDOWN_TO:\n");
	reg_access_hca_default_timeout_ext_print(&(ptr_struct->EMBEDDED_CPU_OS_SHUTDOWN_TO), fd, indent_level + 1);
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
	fprintf(fd, "access_reg_group     : %s (" UH_FMT ")\n", (ptr_struct->access_reg_group == 0 ? ("First_128_REG_ID") : ((ptr_struct->access_reg_group == 1 ? ("Register_IDs_0x9080") : ((ptr_struct->access_reg_group == 2 ? ("Register_IDs_0x9100") : ((ptr_struct->access_reg_group == 3 ? ("Register_IDs_0x9180") : ("unknown")))))))), ptr_struct->access_reg_group);
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
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->warning_code);
	offset = 164;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index_size);
	offset = 196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->rejected_device_index);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_specific_err_code);
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
	offset = 176;
	ptr_struct->warning_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 164;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 212;
	ptr_struct->device_index_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 196;
	ptr_struct->rejected_device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 224;
	ptr_struct->component_specific_err_code = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
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
	fprintf(fd, "warning_code         : " UH_FMT "\n", ptr_struct->warning_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index_size    : " UH_FMT "\n", ptr_struct->device_index_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rejected_device_index : " UH_FMT "\n", ptr_struct->rejected_device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_specific_err_code : " U32H_FMT "\n", ptr_struct->component_specific_err_code);
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
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pnv);
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
	offset = 68;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bg_mode);
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
	offset = 2;
	ptr_struct->pnv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	offset = 68;
	ptr_struct->bg_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "pnv                  : " UH_FMT "\n", ptr_struct->pnv);
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
	fprintf(fd, "bg_mode              : " UH_FMT "\n", ptr_struct->bg_mode);
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
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_ext_pack(&(ptr_struct->data.mcqi_activation_method_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 192;
		reg_access_hca_mcqi_cap_ext_pack(&(ptr_struct->data.mcqi_cap_ext), ptr_buff + offset / 8);
		break;
	case 0x7:
		offset = 192;
		reg_access_hca_mcqi_clock_source_properties_ext_pack(&(ptr_struct->data.mcqi_clock_source_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x9:
		offset = 192;
		reg_access_hca_mcqi_dpa_apps_info_ext_pack(&(ptr_struct->data.mcqi_dpa_apps_info_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_ext_pack(&(ptr_struct->data.mcqi_linkx_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_ext_pack(&(ptr_struct->data.mcqi_version_ext), ptr_buff + offset / 8);
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
	case 0x5:
		offset = 192;
		reg_access_hca_mcqi_activation_method_ext_unpack(&(ptr_struct->data.mcqi_activation_method_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 192;
		reg_access_hca_mcqi_cap_ext_unpack(&(ptr_struct->data.mcqi_cap_ext), ptr_buff + offset / 8);
		break;
	case 0x7:
		offset = 192;
		reg_access_hca_mcqi_clock_source_properties_ext_unpack(&(ptr_struct->data.mcqi_clock_source_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x9:
		offset = 192;
		reg_access_hca_mcqi_dpa_apps_info_ext_unpack(&(ptr_struct->data.mcqi_dpa_apps_info_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 192;
		reg_access_hca_mcqi_linkx_properties_ext_unpack(&(ptr_struct->data.mcqi_linkx_properties_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 192;
		reg_access_hca_mcqi_version_ext_unpack(&(ptr_struct->data.mcqi_version_ext), ptr_buff + offset / 8);
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
	fprintf(fd, "info_type            : %s (" UH_FMT ")\n", (ptr_struct->info_type == 0 ? ("CAPABILITIES") : ((ptr_struct->info_type == 1 ? ("VERSION") : ((ptr_struct->info_type == 5 ? ("ACTIVATION_METHOD") : ((ptr_struct->info_type == 6 ? ("LINKX_PROPERTIES") : ((ptr_struct->info_type == 7 ? ("CLOCK_SOURCE_PROPERTIES") : ((ptr_struct->info_type == 9 ? ("DPA_APPS_INFO") : ("unknown")))))))))))), ptr_struct->info_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_size            : " U32H_FMT "\n", ptr_struct->info_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_size            : " UH_FMT "\n", ptr_struct->data_size);
	switch (ptr_struct->info_type) {
	case 0x5:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_activation_method_ext:\n");
		reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->data.mcqi_activation_method_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_cap_ext:\n");
		reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->data.mcqi_cap_ext), fd, indent_level + 1);
		break;
	case 0x7:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_clock_source_properties_ext:\n");
		reg_access_hca_mcqi_clock_source_properties_ext_print(&(ptr_struct->data.mcqi_clock_source_properties_ext), fd, indent_level + 1);
		break;
	case 0x9:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_dpa_apps_info_ext:\n");
		reg_access_hca_mcqi_dpa_apps_info_ext_print(&(ptr_struct->data.mcqi_dpa_apps_info_ext), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_linkx_properties_ext:\n");
		reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->data.mcqi_linkx_properties_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mcqi_version_ext:\n");
		reg_access_hca_mcqi_version_ext_print(&(ptr_struct->data.mcqi_version_ext), fd, indent_level + 1);
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
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->component_not_supported);
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
	offset = 1;
	ptr_struct->component_not_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "component_not_supported : " UH_FMT "\n", ptr_struct->component_not_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_index_flag      : " UH_FMT "\n", ptr_struct->last_index_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "identifier           : %s (" UH_FMT ")\n", (ptr_struct->identifier == 1 ? ("BOOT_IMG") : ((ptr_struct->identifier == 4 ? ("OEM_NVCONFIG") : ((ptr_struct->identifier == 5 ? ("MLNX_NVCONFIG") : ((ptr_struct->identifier == 6 ? ("CS_TOKEN") : ((ptr_struct->identifier == 7 ? ("DBG_TOKEN") : ((ptr_struct->identifier == 10 ? ("Gearbox") : ((ptr_struct->identifier == 11 ? ("CC_ALGO") : ((ptr_struct->identifier == 12 ? ("LINKX_IMG") : ((ptr_struct->identifier == 13 ? ("CRYPTO_TO_COMMISSIONING") : ((ptr_struct->identifier == 14 ? ("RMCS_TOKEN") : ((ptr_struct->identifier == 15 ? ("RMDT_TOKEN") : ((ptr_struct->identifier == 16 ? ("CRCS_TOKEN") : ((ptr_struct->identifier == 17 ? ("CRDT_TOKEN") : ((ptr_struct->identifier == 18 ? ("CLOCK_SYNC_EEPROM") : ((ptr_struct->identifier == 21 ? ("DIGITAL_CACERT") : ((ptr_struct->identifier == 32 ? ("PSC_TOKEN") : ((ptr_struct->identifier == 28 ? ("DPA_COMPONENT") : ((ptr_struct->identifier == 29 ? ("DPA_COMPONENT_REMOVAL") : ((ptr_struct->identifier == 30 ? ("MTDT_TOKEN") : ("unknown")))))))))))))))))))))))))))))))))))))), ptr_struct->identifier);
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
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pci_reset_req_method);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->rst_type_sel);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pci_sync_for_fw_update_resp);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pci_sync_for_fw_update_start);
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
	offset = 40;
	ptr_struct->pci_reset_req_method = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 37;
	ptr_struct->rst_type_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 35;
	ptr_struct->pci_sync_for_fw_update_resp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 33;
	ptr_struct->pci_sync_for_fw_update_start = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	ptr_struct->pci_rescan_required = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mfrl_reg_ext_print(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mfrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_trigger        : %s (" UH_FMT ")\n", (ptr_struct->reset_trigger == 1 ? ("TRIGGER0") : ((ptr_struct->reset_trigger == 2 ? ("TRIGGER1") : ((ptr_struct->reset_trigger == 8 ? ("TRIGGER3") : ((ptr_struct->reset_trigger == 64 ? ("TRIGGER6") : ("unknown")))))))), ptr_struct->reset_trigger);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_type           : %s (" UH_FMT ")\n", (ptr_struct->reset_type == 1 ? ("Full_Chip_Reset") : ((ptr_struct->reset_type == 2 ? ("Keep_Network_Port_Active_During_Reset") : ((ptr_struct->reset_type == 8 ? ("ARM_Only_Reset") : ((ptr_struct->reset_type == 16 ? ("ARM_OS_Shutdown") : ((ptr_struct->reset_type == 32 ? ("Network_Reset") : ("unknown")))))))))), ptr_struct->reset_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_state          : %s (" UH_FMT ")\n", (ptr_struct->reset_state == 0 ? ("IDLE") : ((ptr_struct->reset_state == 1 ? ("Negotiation_In_Progress") : ((ptr_struct->reset_state == 2 ? ("Reset_In_Progress") : ((ptr_struct->reset_state == 3 ? ("Error_Negotiation_Timeout") : ((ptr_struct->reset_state == 4 ? ("Error_Negotiation_Dis_Acknowledgment") : ((ptr_struct->reset_state == 5 ? ("Error_Driver_Unload_Timeout") : ((ptr_struct->reset_state == 6 ? ("Error") : ((ptr_struct->reset_state == 7 ? ("ARM_OS_Shut_Down_In_Progress") : ((ptr_struct->reset_state == 8 ? ("Waiting_For_Reset_Trigger") : ("unknown")))))))))))))))))), ptr_struct->reset_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_reset_req_method : %s (" UH_FMT ")\n", (ptr_struct->pci_reset_req_method == 0 ? ("Link_Disable") : ((ptr_struct->pci_reset_req_method == 1 ? ("Hot_Reset") : ("unknown")))), ptr_struct->pci_reset_req_method);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst_type_sel         : " UH_FMT "\n", ptr_struct->rst_type_sel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_resp : %s (" UH_FMT ")\n", (ptr_struct->pci_sync_for_fw_update_resp == 1 ? ("Acknowledgment") : ((ptr_struct->pci_sync_for_fw_update_resp == 2 ? ("Dis_acknowledgment") : ((ptr_struct->pci_sync_for_fw_update_resp == 3 ? ("Reserved") : ("unknown")))))), ptr_struct->pci_sync_for_fw_update_resp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_start : %s (" UH_FMT ")\n", (ptr_struct->pci_sync_for_fw_update_start == 0 ? ("Legacy_Flow") : ((ptr_struct->pci_sync_for_fw_update_start == 1 ? ("Synced_Driver_Flow") : ((ptr_struct->pci_sync_for_fw_update_start == 2 ? ("Synced_Tool_Flow") : ("unknown")))))), ptr_struct->pci_sync_for_fw_update_start);
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
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->revoke_efuse_prog);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_efuse_prog);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dummy_ratchet_prog_en);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fuse_failure);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index);
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
	offset = 27;
	ptr_struct->revoke_efuse_prog = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->pending_efuse_prog = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->dummy_ratchet_prog_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->fuse_failure = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
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
	fprintf(fd, "revoke_efuse_prog    : " UH_FMT "\n", ptr_struct->revoke_efuse_prog);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_efuse_prog   : " UH_FMT "\n", ptr_struct->pending_efuse_prog);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dummy_ratchet_prog_en : " UH_FMT "\n", ptr_struct->dummy_ratchet_prog_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fuse_failure         : " UH_FMT "\n", ptr_struct->fuse_failure);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index                : " UH_FMT "\n", ptr_struct->index);
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

void reg_access_hca_misoc_reg_ext_pack(const struct reg_access_hca_misoc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->query_pending);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->query_not_available);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 2304, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version[i]);
	}
}

void reg_access_hca_misoc_reg_ext_unpack(struct reg_access_hca_misoc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1;
	ptr_struct->query_pending = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->query_not_available = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 2304, 1);
		ptr_struct->version[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_misoc_reg_ext_print(const struct reg_access_hca_misoc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_misoc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("ARM_ATF") : ((ptr_struct->type == 1 ? ("ARM_UEFI") : ((ptr_struct->type == 2 ? ("DPU_BMC") : ((ptr_struct->type == 3 ? ("CEC") : ((ptr_struct->type == 5 ? ("BF_BUNDLE") : ((ptr_struct->type == 7 ? ("BSP") : ((ptr_struct->type == 8 ? ("NIC_GOLDEN") : ((ptr_struct->type == 9 ? ("ARM_GOLDEN") : ("unknown")))))))))))))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_pending        : " UH_FMT "\n", ptr_struct->query_pending);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_not_available  : " UH_FMT "\n", ptr_struct->query_not_available);
	for (i = 0; i < 256; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "version_%03d         : " UH_FMT "\n", i, ptr_struct->version[i]);
	}
}

unsigned int reg_access_hca_misoc_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MISOC_REG_EXT_SIZE;
}

void reg_access_hca_misoc_reg_ext_dump(const struct reg_access_hca_misoc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_misoc_reg_ext_print(ptr_struct, fd, 0);
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

void reg_access_hca_mmhi_reg_ext_pack(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->host_number);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->host_en);
}

void reg_access_hca_mmhi_reg_ext_unpack(struct reg_access_hca_mmhi_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->host_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->host_en = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_hca_mmhi_reg_ext_print(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mmhi_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_number          : " UH_FMT "\n", ptr_struct->host_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_en              : " UH_FMT "\n", ptr_struct->host_en);
}

unsigned int reg_access_hca_mmhi_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MMHI_REG_EXT_SIZE;
}

void reg_access_hca_mmhi_reg_ext_dump(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mmhi_reg_ext_print(ptr_struct, fd, 0);
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

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->instance);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_entity);
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

	offset = 16;
	ptr_struct->instance = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->fw_entity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
	fprintf(fd, "instance             : " UH_FMT "\n", ptr_struct->instance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_entity            : " UH_FMT "\n", ptr_struct->fw_entity);
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

void reg_access_hca_mpegc_reg_ext_pack(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->field_select);
	offset = 94;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_lossy_overflow_oper);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->segment_base);
	offset = 71;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->seg_valid);
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
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->field_select = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 94;
	ptr_struct->tx_lossy_overflow_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 72;
	ptr_struct->segment_base = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 71;
	ptr_struct->seg_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "field_select         : " UH_FMT "\n", ptr_struct->field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lossy_overflow_oper : " UH_FMT "\n", ptr_struct->tx_lossy_overflow_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_base         : " UH_FMT "\n", ptr_struct->segment_base);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seg_valid            : " UH_FMT "\n", ptr_struct->seg_valid);
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

void reg_access_hca_mpein_reg_ext_pack(const struct reg_access_hca_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_enabled);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_enabled);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_active);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane0_physical_position);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_vfs);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_pfs);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->bdf0);
	offset = 223;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lane_reversal);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 205;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pwr_status);
	offset = 196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_payload_size);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_read_request_size);
	offset = 244;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->pci_power);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_peer_max_speed);
	offset = 287;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flit_sup);
	offset = 286;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->precode_sup);
	offset = 279;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flit_active);
	offset = 278;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->precode_active);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_status);
}

void reg_access_hca_mpein_reg_ext_unpack(struct reg_access_hca_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 80;
	ptr_struct->link_speed_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->link_width_enabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 104;
	ptr_struct->link_width_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->lane0_physical_position = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->num_of_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->num_of_pfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->bdf0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 223;
	ptr_struct->lane_reversal = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 208;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 205;
	ptr_struct->pwr_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 196;
	ptr_struct->max_payload_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->max_read_request_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 244;
	ptr_struct->pci_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 224;
	ptr_struct->link_peer_max_speed = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 287;
	ptr_struct->flit_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 286;
	ptr_struct->precode_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 279;
	ptr_struct->flit_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 278;
	ptr_struct->precode_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 288;
	ptr_struct->device_status = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_hca_mpein_reg_ext_print(const struct reg_access_hca_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpein_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_enabled   : " UH_FMT "\n", ptr_struct->link_speed_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_enabled   : " UH_FMT "\n", ptr_struct->link_width_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : " UH_FMT "\n", ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_position : " UH_FMT "\n", ptr_struct->lane0_physical_position);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_vfs           : " UH_FMT "\n", ptr_struct->num_of_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_pfs           : " UH_FMT "\n", ptr_struct->num_of_pfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bdf0                 : " UH_FMT "\n", ptr_struct->bdf0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_reversal        : " UH_FMT "\n", ptr_struct->lane_reversal);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pwr_status           : " UH_FMT "\n", ptr_struct->pwr_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_payload_size     : " UH_FMT "\n", ptr_struct->max_payload_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_read_request_size : " UH_FMT "\n", ptr_struct->max_read_request_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_power            : " UH_FMT "\n", ptr_struct->pci_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_peer_max_speed  : " UH_FMT "\n", ptr_struct->link_peer_max_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flit_sup             : " UH_FMT "\n", ptr_struct->flit_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "precode_sup          : " UH_FMT "\n", ptr_struct->precode_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flit_active          : " UH_FMT "\n", ptr_struct->flit_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "precode_active       : " UH_FMT "\n", ptr_struct->precode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_status        : %s (" UH_FMT ")\n", (ptr_struct->device_status == 1 ? ("Correctable_error") : ((ptr_struct->device_status == 2 ? ("Non_Fatal_Error_detection") : ((ptr_struct->device_status == 4 ? ("Fatal_Error_detected") : ((ptr_struct->device_status == 8 ? ("Unsupported_request_detected") : ((ptr_struct->device_status == 16 ? ("AUX_power") : ((ptr_struct->device_status == 32 ? ("Transaction_Pending") : ("unknown")))))))))))), ptr_struct->device_status);
}

unsigned int reg_access_hca_mpein_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MPEIN_REG_EXT_SIZE;
}

void reg_access_hca_mpein_reg_ext_dump(const struct reg_access_hca_mpein_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mpein_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mpir_ext_pack(const struct reg_access_hca_mpir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->host_buses);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sdm);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->subordinate_bus);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->secondary_bus);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->segment_base);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->seg_valid);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->seg_cap);
	offset = 93;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->sd_group);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->device);
	offset = 82;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bus);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 115;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->slot_number);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_con_devices);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->host_index);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->slot_cap);
}

void reg_access_hca_mpir_ext_unpack(struct reg_access_hca_mpir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->host_buses = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->sdm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->subordinate_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->secondary_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->segment_base = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 39;
	ptr_struct->seg_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 38;
	ptr_struct->seg_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 93;
	ptr_struct->sd_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 88;
	ptr_struct->device = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 82;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 72;
	ptr_struct->bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 115;
	ptr_struct->slot_number = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);
	offset = 104;
	ptr_struct->num_con_devices = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 97;
	ptr_struct->host_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 96;
	ptr_struct->slot_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_hca_mpir_ext_print(const struct reg_access_hca_mpir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_buses           : " UH_FMT "\n", ptr_struct->host_buses);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdm                  : " UH_FMT "\n", ptr_struct->sdm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subordinate_bus      : " UH_FMT "\n", ptr_struct->subordinate_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary_bus        : " UH_FMT "\n", ptr_struct->secondary_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_base         : " UH_FMT "\n", ptr_struct->segment_base);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seg_valid            : " UH_FMT "\n", ptr_struct->seg_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seg_cap              : " UH_FMT "\n", ptr_struct->seg_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sd_group             : " UH_FMT "\n", ptr_struct->sd_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device               : " UH_FMT "\n", ptr_struct->device);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bus                  : " UH_FMT "\n", ptr_struct->bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_number          : " UH_FMT "\n", ptr_struct->slot_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_con_devices      : " UH_FMT "\n", ptr_struct->num_con_devices);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_index           : " UH_FMT "\n", ptr_struct->host_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_cap             : " UH_FMT "\n", ptr_struct->slot_cap);
}

unsigned int reg_access_hca_mpir_ext_size(void)
{
	return REG_ACCESS_HCA_MPIR_EXT_SIZE;
}

void reg_access_hca_mpir_ext_dump(const struct reg_access_hca_mpir_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mpir_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mpqd_reg_ext_pack(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->requester_pcie_index);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_valid_pcie_index);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_exist_depth);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_internal);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->number_of_nodes);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->node_phy);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->valid_index);
	offset = 127;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->valid_node);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DSP_node);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->parent_node_number);
}

void reg_access_hca_mpqd_reg_ext_unpack(struct reg_access_hca_mpqd_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->requester_pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->max_valid_pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->max_exist_depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->is_internal = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 88;
	ptr_struct->number_of_nodes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 87;
	ptr_struct->node_phy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->valid_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 127;
	ptr_struct->valid_node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 126;
	ptr_struct->DSP_node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 112;
	ptr_struct->parent_node_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mpqd_reg_ext_print(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mpqd_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "requester_pcie_index : " UH_FMT "\n", ptr_struct->requester_pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_valid_pcie_index : " UH_FMT "\n", ptr_struct->max_valid_pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_exist_depth      : " UH_FMT "\n", ptr_struct->max_exist_depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_internal          : " UH_FMT "\n", ptr_struct->is_internal);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "number_of_nodes      : " UH_FMT "\n", ptr_struct->number_of_nodes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node_phy             : " UH_FMT "\n", ptr_struct->node_phy);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "valid_index          : " UH_FMT "\n", ptr_struct->valid_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "valid_node           : " UH_FMT "\n", ptr_struct->valid_node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DSP_node             : " UH_FMT "\n", ptr_struct->DSP_node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parent_node_number   : " UH_FMT "\n", ptr_struct->parent_node_number);
}

unsigned int reg_access_hca_mpqd_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MPQD_REG_EXT_SIZE;
}

void reg_access_hca_mpqd_reg_ext_dump(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mpqd_reg_ext_print(ptr_struct, fd, 0);
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

void reg_access_hca_mroq_ext_pack(const struct reg_access_hca_mroq_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_trigger);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_type);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->query_is_valid);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pci_sync_for_fw_update_start);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pci_reset_req_method);
}

void reg_access_hca_mroq_ext_unpack(struct reg_access_hca_mroq_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->reset_trigger = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->reset_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 15;
	ptr_struct->query_is_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 11;
	ptr_struct->pci_sync_for_fw_update_start = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->pci_reset_req_method = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_hca_mroq_ext_print(const struct reg_access_hca_mroq_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mroq_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_trigger        : %s (" UH_FMT ")\n", (ptr_struct->reset_trigger == 1 ? ("TRIGGER0") : ((ptr_struct->reset_trigger == 2 ? ("Immediate_Action") : ((ptr_struct->reset_trigger == 8 ? ("TRIGGER3") : ((ptr_struct->reset_trigger == 64 ? ("TRIGGER6") : ("unknown")))))))), ptr_struct->reset_trigger);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_type           : %s (" UH_FMT ")\n", (ptr_struct->reset_type == 0 ? ("Full_Chip_Reset") : ((ptr_struct->reset_type == 1 ? ("Keep_Network_Port_Active_During_Reset") : ((ptr_struct->reset_type == 2 ? ("NIC_Only_Rset") : ((ptr_struct->reset_type == 3 ? ("ARM_Only_Reset") : ((ptr_struct->reset_type == 4 ? ("ARM_OS_Shutdown") : ((ptr_struct->reset_type == 5 ? ("Network_Reset") : ((ptr_struct->reset_type == 255 ? ("InService_SW_Update") : ("unknown")))))))))))))), ptr_struct->reset_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_is_valid       : " UH_FMT "\n", ptr_struct->query_is_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sync_for_fw_update_start : %s (" UH_FMT ")\n", (ptr_struct->pci_sync_for_fw_update_start == 1 ? ("Legacy_Flow") : ((ptr_struct->pci_sync_for_fw_update_start == 2 ? ("Synced_Driver_Flow") : ((ptr_struct->pci_sync_for_fw_update_start == 4 ? ("Synced_Tool_Flow") : ((ptr_struct->pci_sync_for_fw_update_start == 8 ? ("Reserved") : ("unknown")))))))), ptr_struct->pci_sync_for_fw_update_start);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_reset_req_method : %s (" UH_FMT ")\n", (ptr_struct->pci_reset_req_method == 1 ? ("Link_Disable") : ((ptr_struct->pci_reset_req_method == 2 ? ("Hot_Reset") : ("unknown")))), ptr_struct->pci_reset_req_method);
}

unsigned int reg_access_hca_mroq_ext_size(void)
{
	return REG_ACCESS_HCA_MROQ_EXT_SIZE;
}

void reg_access_hca_mroq_ext_dump(const struct reg_access_hca_mroq_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mroq_ext_print(ptr_struct, fd, 0);
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
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ecos);
}

void reg_access_hca_mrsi_ext_unpack(struct reg_access_hca_mrsi_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->device = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->reset_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->crts = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 184;
	ptr_struct->ecos = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecos                 : " UH_FMT "\n", ptr_struct->ecos);
}

unsigned int reg_access_hca_mrsi_ext_size(void)
{
	return REG_ACCESS_HCA_MRSI_EXT_SIZE;
}

void reg_access_hca_mrsi_ext_dump(const struct reg_access_hca_mrsi_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mrsi_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtcap_ext_pack(const struct reg_access_hca_mtcap_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->sensor_count);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->internal_sensor_count);
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
	offset = 56;
	ptr_struct->internal_sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->sensor_map = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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

void reg_access_hca_mtdc_ext_pack(const struct reg_access_hca_mtdc_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tracer_limit_en);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tlb_addr_msb);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->tlb_addr_lsb);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hw_pointer);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sw_pointer);
}

void reg_access_hca_mtdc_ext_unpack(struct reg_access_hca_mtdc_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->tracer_limit_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 64;
	ptr_struct->tlb_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->tlb_addr_lsb = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
	offset = 128;
	ptr_struct->hw_pointer = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->sw_pointer = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtdc_ext_print(const struct reg_access_hca_mtdc_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtdc_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tracer_limit_en      : " UH_FMT "\n", ptr_struct->tracer_limit_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tlb_addr_msb         : " U32H_FMT "\n", ptr_struct->tlb_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tlb_addr_lsb         : " UH_FMT "\n", ptr_struct->tlb_addr_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointer           : " U32H_FMT "\n", ptr_struct->hw_pointer);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_pointer           : " U32H_FMT "\n", ptr_struct->sw_pointer);
}

unsigned int reg_access_hca_mtdc_ext_size(void)
{
	return REG_ACCESS_HCA_MTDC_EXT_SIZE;
}

void reg_access_hca_mtdc_ext_dump(const struct reg_access_hca_mtdc_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtdc_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mteim_reg_ext_pack(const struct reg_access_hca_mteim_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_tile);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_main);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_dpa);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_num_of_tile);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_tile);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_main);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_dpa);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_phy_uc_supported);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_dwsn_msb_supported);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_dpa_core_event_id);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_main_core_event_id);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 384, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_tile_core_event_id[i]);
	}
}

void reg_access_hca_mteim_reg_ext_unpack(struct reg_access_hca_mteim_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->cap_core_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->cap_core_main = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->cap_core_dpa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->cap_num_of_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->type_core_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->type_core_main = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->type_core_dpa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 33;
	ptr_struct->is_phy_uc_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->is_dwsn_msb_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 72;
	ptr_struct->first_dpa_core_event_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->first_main_core_event_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 384, 1);
		ptr_struct->first_tile_core_event_id[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_hca_mteim_reg_ext_print(const struct reg_access_hca_mteim_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mteim_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_tile        : " UH_FMT "\n", ptr_struct->cap_core_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_main        : " UH_FMT "\n", ptr_struct->cap_core_main);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_dpa         : " UH_FMT "\n", ptr_struct->cap_core_dpa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_num_of_tile      : " UH_FMT "\n", ptr_struct->cap_num_of_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_tile       : " UH_FMT "\n", ptr_struct->type_core_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_main       : " UH_FMT "\n", ptr_struct->type_core_main);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_dpa        : " UH_FMT "\n", ptr_struct->type_core_dpa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_phy_uc_supported  : " UH_FMT "\n", ptr_struct->is_phy_uc_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_dwsn_msb_supported : " UH_FMT "\n", ptr_struct->is_dwsn_msb_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_dpa_core_event_id : " UH_FMT "\n", ptr_struct->first_dpa_core_event_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_main_core_event_id : " UH_FMT "\n", ptr_struct->first_main_core_event_id);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "first_tile_core_event_id_%03d : " UH_FMT "\n", i, ptr_struct->first_tile_core_event_id[i]);
	}
}

unsigned int reg_access_hca_mteim_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MTEIM_REG_EXT_SIZE;
}

void reg_access_hca_mteim_reg_ext_dump(const struct reg_access_hca_mteim_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mteim_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtie_ext_pack(const struct reg_access_hca_mtie_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->enable_all);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->log_delay);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->source_id_bitmask[i]);
	}
}

void reg_access_hca_mtie_ext_unpack(struct reg_access_hca_mtie_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	ptr_struct->enable_all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 48;
	ptr_struct->log_delay = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		ptr_struct->source_id_bitmask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_mtie_ext_print(const struct reg_access_hca_mtie_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtie_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "enable_all           : " UH_FMT "\n", ptr_struct->enable_all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_delay            : " UH_FMT "\n", ptr_struct->log_delay);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "source_id_bitmask_%03d : " U32H_FMT "\n", i, ptr_struct->source_id_bitmask[i]);
	}
}

unsigned int reg_access_hca_mtie_ext_size(void)
{
	return REG_ACCESS_HCA_MTIE_EXT_SIZE;
}

void reg_access_hca_mtie_ext_dump(const struct reg_access_hca_mtie_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtie_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtim_ext_pack(const struct reg_access_hca_mtim_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_level);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_bit_mask);
}

void reg_access_hca_mtim_ext_unpack(struct reg_access_hca_mtim_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->log_level = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->log_bit_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtim_ext_print(const struct reg_access_hca_mtim_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtim_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_level            : " UH_FMT "\n", ptr_struct->log_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_bit_mask         : " U32H_FMT "\n", ptr_struct->log_bit_mask);
}

unsigned int reg_access_hca_mtim_ext_size(void)
{
	return REG_ACCESS_HCA_MTIM_EXT_SIZE;
}

void reg_access_hca_mtim_ext_dump(const struct reg_access_hca_mtim_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtim_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtmp_ext_pack(const struct reg_access_hca_mtmp_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_index);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->asic_index);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ig);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->i);
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
	offset = 3;
	ptr_struct->asic_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1;
	ptr_struct->ig = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->i = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "asic_index           : " UH_FMT "\n", ptr_struct->asic_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ig                   : " UH_FMT "\n", ptr_struct->ig);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "i                    : " UH_FMT "\n", ptr_struct->i);
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
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tracer_capabilities);
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
	offset = 64;
	ptr_struct->tracer_capabilities = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tracer_capabilities  : " UH_FMT "\n", ptr_struct->tracer_capabilities);
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

void reg_access_hca_mtrc_conf_reg_ext_pack(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->trace_mode);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_trace_buffer_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->trace_mkey);
}

void reg_access_hca_mtrc_conf_reg_ext_unpack(struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->trace_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->log_trace_buffer_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->trace_mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtrc_conf_reg_ext_print(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_conf_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_mode           : " UH_FMT "\n", ptr_struct->trace_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_trace_buffer_size : " UH_FMT "\n", ptr_struct->log_trace_buffer_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_mkey           : " U32H_FMT "\n", ptr_struct->trace_mkey);
}

unsigned int reg_access_hca_mtrc_conf_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MTRC_CONF_REG_EXT_SIZE;
}

void reg_access_hca_mtrc_conf_reg_ext_dump(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_conf_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_mtrc_ctrl_reg_ext_pack(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->modify_field_select);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->arm_event);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->trace_status);
	offset = 75;
	adb2c_push_bits_to_buff(ptr_buff, offset, 21, (u_int32_t)ptr_struct->current_timestamp_52_32);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->current_timestamp_31_0);
}

void reg_access_hca_mtrc_ctrl_reg_ext_unpack(struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->modify_field_select = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 4;
	ptr_struct->arm_event = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->trace_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 75;
	ptr_struct->current_timestamp_52_32 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 21);
	offset = 96;
	ptr_struct->current_timestamp_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_hca_mtrc_ctrl_reg_ext_print(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_mtrc_ctrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modify_field_select  : " UH_FMT "\n", ptr_struct->modify_field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "arm_event            : " UH_FMT "\n", ptr_struct->arm_event);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_status         : " UH_FMT "\n", ptr_struct->trace_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_timestamp_52_32 : " UH_FMT "\n", ptr_struct->current_timestamp_52_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_timestamp_31_0 : " U32H_FMT "\n", ptr_struct->current_timestamp_31_0);
}

unsigned int reg_access_hca_mtrc_ctrl_reg_ext_size(void)
{
	return REG_ACCESS_HCA_MTRC_CTRL_REG_EXT_SIZE;
}

void reg_access_hca_mtrc_ctrl_reg_ext_dump(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_mtrc_ctrl_reg_ext_print(ptr_struct, fd, 0);
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

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cap_group);
	offset = 128;
	reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_pack(&(ptr_struct->cap_data), ptr_buff + offset / 8);
}

void reg_access_hca_nic_cap_ext_reg_ext_unpack(struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->cap_group = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_unpack(&(ptr_struct->cap_data), ptr_buff + offset / 8);
}

void reg_access_hca_nic_cap_ext_reg_ext_print(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_cap_ext_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_group            : %s (" UH_FMT ")\n", (ptr_struct->cap_group == 1 ? ("DPA_CAP") : ("unknown")), ptr_struct->cap_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_data:\n");
	reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_print(&(ptr_struct->cap_data), fd, indent_level + 1);
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
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->partition_id_valid);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modify_field_select);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->partition_id);
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
	offset = 4;
	ptr_struct->partition_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->modify_field_select = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 112;
	ptr_struct->partition_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
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
	fprintf(fd, "partition_id_valid   : " UH_FMT "\n", ptr_struct->partition_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : %s (" UH_FMT ")\n", (ptr_struct->operation == 0 ? ("CREATE") : ((ptr_struct->operation == 1 ? ("MODIFY") : ((ptr_struct->operation == 2 ? ("DESTROY") : ("unknown")))))), ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modify_field_select  : %s (" U32H_FMT ")\n", (ptr_struct->modify_field_select == 1 ? ("member_mask") : ("unknown")), ptr_struct->modify_field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partition_id         : " UH_FMT "\n", ptr_struct->partition_id);
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
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dpa_process_id);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->other_vhca_id);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->sample_type);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->other_vhca_id_valid);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->count_state);
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_unpack(struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->dpa_process_id = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->other_vhca_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 37;
	ptr_struct->sample_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 36;
	ptr_struct->other_vhca_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->count_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_nic_dpa_perf_ctrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dpa_process_id       : " U32H_FMT "\n", ptr_struct->dpa_process_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "other_vhca_id        : " UH_FMT "\n", ptr_struct->other_vhca_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sample_type          : %s (" UH_FMT ")\n", (ptr_struct->sample_type == 0 ? ("CUMMULATIVE_EVENT") : ((ptr_struct->sample_type == 1 ? ("EVENT_TRACER") : ("unknown")))), ptr_struct->sample_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "other_vhca_id_valid  : " UH_FMT "\n", ptr_struct->other_vhca_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "count_state          : %s (" UH_FMT ")\n", (ptr_struct->count_state == 0 ? ("UNCHANGED") : ((ptr_struct->count_state == 1 ? ("ACTIVE") : ((ptr_struct->count_state == 2 ? ("INACTIVE") : ((ptr_struct->count_state == 3 ? ("RESET_COUNTERS") : ("unknown")))))))), ptr_struct->count_state);
}

unsigned int reg_access_hca_nic_dpa_perf_ctrl_reg_ext_size(void)
{
	return REG_ACCESS_HCA_NIC_DPA_PERF_CTRL_REG_EXT_SIZE;
}

void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_dump(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_paos_reg_ext_pack(const struct reg_access_hca_paos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
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
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->physical_state_status);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fd);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sleep_cap);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ps_e);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->logical_state_status);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ls_e);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_nmxas);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_ps);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_ls);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
	offset = 93;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->nmx_adminstate_status);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->nmxas_e);
	offset = 82;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ps_e_ext);
	offset = 77;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->last_oper_status);
}

void reg_access_hca_paos_reg_ext_unpack(struct reg_access_hca_paos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
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
	offset = 56;
	ptr_struct->physical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 55;
	ptr_struct->fd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->sleep_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->ps_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 45;
	ptr_struct->logical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 40;
	ptr_struct->ls_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->ee_nmxas = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 35;
	ptr_struct->ee_ps = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->ee_ls = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 93;
	ptr_struct->nmx_adminstate_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 88;
	ptr_struct->nmxas_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 82;
	ptr_struct->ps_e_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 77;
	ptr_struct->last_oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_hca_paos_reg_ext_print(const struct reg_access_hca_paos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_paos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 1 ? ("up") : ((ptr_struct->oper_status == 2 ? ("down") : ((ptr_struct->oper_status == 4 ? ("down_by_port_failure") : ("unknown")))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
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
	fprintf(fd, "physical_state_status : %s (" UH_FMT ")\n", (ptr_struct->physical_state_status == 0 ? ("N_A") : ((ptr_struct->physical_state_status == 1 ? ("Sleep") : ((ptr_struct->physical_state_status == 2 ? ("Polling") : ((ptr_struct->physical_state_status == 3 ? ("Disabled") : ((ptr_struct->physical_state_status == 4 ? ("PortConfigurationTraining") : ((ptr_struct->physical_state_status == 5 ? ("LinkUp") : ((ptr_struct->physical_state_status == 6 ? ("LinkErrorRecovery") : ("unknown")))))))))))))), ptr_struct->physical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fd                   : " UH_FMT "\n", ptr_struct->fd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sleep_cap            : " UH_FMT "\n", ptr_struct->sleep_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ps_e                 : %s (" UH_FMT ")\n", (ptr_struct->ps_e == 1 ? ("Sleep") : ((ptr_struct->ps_e == 2 ? ("LinkUp") : ((ptr_struct->ps_e == 4 ? ("Disabled") : ((ptr_struct->ps_e == 8 ? ("PortConfigurationTraining") : ("unknown")))))))), ptr_struct->ps_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "logical_state_status : %s (" UH_FMT ")\n", (ptr_struct->logical_state_status == 0 ? ("N_A") : ((ptr_struct->logical_state_status == 1 ? ("Down") : ((ptr_struct->logical_state_status == 2 ? ("Init") : ((ptr_struct->logical_state_status == 3 ? ("Arm") : ((ptr_struct->logical_state_status == 4 ? ("Active") : ("unknown")))))))))), ptr_struct->logical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ls_e                 : %s (" UH_FMT ")\n", (ptr_struct->ls_e == 1 ? ("Down") : ((ptr_struct->ls_e == 2 ? ("Init") : ((ptr_struct->ls_e == 4 ? ("Arm") : ((ptr_struct->ls_e == 8 ? ("Active") : ("unknown")))))))), ptr_struct->ls_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_nmxas             : " UH_FMT "\n", ptr_struct->ee_nmxas);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_ps                : " UH_FMT "\n", ptr_struct->ee_ps);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_ls                : " UH_FMT "\n", ptr_struct->ee_ls);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nmx_adminstate_status : %s (" UH_FMT ")\n", (ptr_struct->nmx_adminstate_status == 0 ? ("N_A") : ((ptr_struct->nmx_adminstate_status == 1 ? ("Up") : ((ptr_struct->nmx_adminstate_status == 2 ? ("Down") : ((ptr_struct->nmx_adminstate_status == 3 ? ("Diag") : ("unknown")))))))), ptr_struct->nmx_adminstate_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nmxas_e              : %s (" UH_FMT ")\n", (ptr_struct->nmxas_e == 1 ? ("Up") : ((ptr_struct->nmxas_e == 2 ? ("Down") : ((ptr_struct->nmxas_e == 4 ? ("Diag") : ("unknown")))))), ptr_struct->nmxas_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ps_e_ext             : %s (" UH_FMT ")\n", (ptr_struct->ps_e_ext == 1 ? ("Polling") : ((ptr_struct->ps_e_ext == 2 ? ("Reserved") : ("unknown")))), ptr_struct->ps_e_ext);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_oper_status     : %s (" UH_FMT ")\n", (ptr_struct->last_oper_status == 1 ? ("up") : ((ptr_struct->last_oper_status == 2 ? ("down") : ((ptr_struct->last_oper_status == 4 ? ("down_by_port_failure") : ("unknown")))))), ptr_struct->last_oper_status);
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
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flua_cap);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->flua_we_mask);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->keep_phy_setting);
	offset = 58;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->flua_en);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->flua_oper);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flua_allowed_ber);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flua_polling_sec);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->flua_guar_sec);
}

void reg_access_hca_pcnr_reg_ext_unpack(struct reg_access_hca_pcnr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->tuning_override = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->flua_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->flua_we_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->keep_phy_setting = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 58;
	ptr_struct->flua_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->flua_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 48;
	ptr_struct->flua_allowed_ber = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->flua_polling_sec = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 35;
	ptr_struct->flua_guar_sec = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_hca_pcnr_reg_ext_print(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pcnr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tuning_override      : " UH_FMT "\n", ptr_struct->tuning_override);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_cap             : " UH_FMT "\n", ptr_struct->flua_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_we_mask         : %s (" UH_FMT ")\n", (ptr_struct->flua_we_mask == 1 ? ("flua_en") : ((ptr_struct->flua_we_mask == 2 ? ("flua_allowed_ber") : ((ptr_struct->flua_we_mask == 4 ? ("flua_polling_sec") : ((ptr_struct->flua_we_mask == 8 ? ("flua_guar_sec") : ("unknown")))))))), ptr_struct->flua_we_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "keep_phy_setting     : " UH_FMT "\n", ptr_struct->keep_phy_setting);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_en              : %s (" UH_FMT ")\n", (ptr_struct->flua_en == 0 ? ("device_default_behavior") : ((ptr_struct->flua_en == 1 ? ("enable_fast_linkup_always") : ((ptr_struct->flua_en == 2 ? ("disable_fast_linkup_always") : ("unknown")))))), ptr_struct->flua_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_oper            : %s (" UH_FMT ")\n", (ptr_struct->flua_oper == 0 ? ("fast_linkup_always_was_not_performed") : ((ptr_struct->flua_oper == 1 ? ("fast_linkup_always_was_performed") : ("unknown")))), ptr_struct->flua_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_allowed_ber     : " UH_FMT "\n", ptr_struct->flua_allowed_ber);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_polling_sec     : " UH_FMT "\n", ptr_struct->flua_polling_sec);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flua_guar_sec        : " UH_FMT "\n", ptr_struct->flua_guar_sec);
}

unsigned int reg_access_hca_pcnr_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PCNR_REG_EXT_SIZE;
}

void reg_access_hca_pcnr_reg_ext_dump(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_pcnr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_hca_pguid_reg_ext_pack(const struct reg_access_hca_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sys_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->node_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->allocated_guid[i]);
	}
}

void reg_access_hca_pguid_reg_ext_unpack(struct reg_access_hca_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 768, 1);
		ptr_struct->sys_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 768, 1);
		ptr_struct->node_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 768, 1);
		ptr_struct->port_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 768, 1);
		ptr_struct->allocated_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_hca_pguid_reg_ext_print(const struct reg_access_hca_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_pguid_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sys_guid_%03d        : " U32H_FMT "\n", i, ptr_struct->sys_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "node_guid_%03d       : " U32H_FMT "\n", i, ptr_struct->node_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "port_guid_%03d       : " U32H_FMT "\n", i, ptr_struct->port_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "allocated_guid_%03d  : " U32H_FMT "\n", i, ptr_struct->allocated_guid[i]);
	}
}

unsigned int reg_access_hca_pguid_reg_ext_size(void)
{
	return REG_ACCESS_HCA_PGUID_REG_EXT_SIZE;
}

void reg_access_hca_pguid_reg_ext_dump(const struct reg_access_hca_pguid_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_hca_pguid_reg_ext_print(ptr_struct, fd, 0);
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
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("enabled") : ((ptr_struct->admin_status == 2 ? ("disabled_by_configuration") : ((ptr_struct->admin_status == 3 ? ("enabled_once") : ((ptr_struct->admin_status == 14 ? ("disconnect_cable") : ("unknown")))))))), ptr_struct->admin_status);
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
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
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
	offset = 20;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
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
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
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
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->transmit_allowed);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_ready_e);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_tx_ready);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_cap);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_admin);
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
	offset = 448;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 448;
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_pack(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_ib_cap_oper_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 448;
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 480;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 480;
		reg_access_hca_ptys_ext_proto_ib_admin_ext_pack(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_ib_admin_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 480;
		reg_access_hca_ptys_ext_proto_nvlink_admin_ext_pack(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_nvlink_admin_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 512;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 512;
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_pack(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_ib_cap_oper_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 512;
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_ptys_reg_ext_unpack(struct reg_access_hca_ptys_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->proto_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 28;
	ptr_struct->transmit_allowed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->tx_ready_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 3;
	ptr_struct->ee_tx_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->an_disable_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->an_disable_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	offset = 448;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 448;
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_unpack(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_ib_cap_oper_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 448;
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 480;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 480;
		reg_access_hca_ptys_ext_proto_ib_admin_ext_unpack(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_ib_admin_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 480;
		reg_access_hca_ptys_ext_proto_nvlink_admin_ext_unpack(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_nvlink_admin_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 512;
	switch (ptr_struct->proto_mask) {
	case 0x1:
		offset = 512;
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_unpack(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_ib_cap_oper_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 512;
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_nvlink_cap_oper_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_hca_ptys_reg_ext_print(const struct reg_access_hca_ptys_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_hca_ptys_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "proto_mask           : %s (" UH_FMT ")\n", (ptr_struct->proto_mask == 1 ? ("InfiniBand") : ((ptr_struct->proto_mask == 2 ? ("NVLink") : ((ptr_struct->proto_mask == 4 ? ("Ethernet") : ("unknown")))))), ptr_struct->proto_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "transmit_allowed     : %s (" UH_FMT ")\n", (ptr_struct->transmit_allowed == 0 ? ("transmit_not_allowed") : ((ptr_struct->transmit_allowed == 1 ? ("transmit_allowed") : ("unknown")))), ptr_struct->transmit_allowed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("Near") : ((ptr_struct->port_type == 2 ? ("Internal_IC_Port") : ((ptr_struct->port_type == 3 ? ("Far") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ready_e           : " UH_FMT "\n", ptr_struct->tx_ready_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_tx_ready          : " UH_FMT "\n", ptr_struct->ee_tx_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_cap       : " UH_FMT "\n", ptr_struct->an_disable_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_admin     : " UH_FMT "\n", ptr_struct->an_disable_admin);
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
	switch (ptr_struct->proto_mask) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_ib_cap_oper_ext:\n");
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_ib_cap_oper_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_nvlink_cap_oper_ext:\n");
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(&(ptr_struct->ext_ib_proto_cap.ptys_ext_proto_nvlink_cap_oper_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_mask) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_ib_admin_ext:\n");
		reg_access_hca_ptys_ext_proto_ib_admin_ext_print(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_ib_admin_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_nvlink_admin_ext:\n");
		reg_access_hca_ptys_ext_proto_nvlink_admin_ext_print(&(ptr_struct->ext_ib_proto_admin.ptys_ext_proto_nvlink_admin_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_mask) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_ib_cap_oper_ext:\n");
		reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_ib_cap_oper_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ptys_ext_proto_nvlink_cap_oper_ext:\n");
		reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(&(ptr_struct->ext_ib_proto_oper.ptys_ext_proto_nvlink_cap_oper_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
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
	ptr_struct->device_opaque = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 256;
	ptr_struct->mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->address = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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
	fprintf(fd, "mteim_reg_ext:\n");
	reg_access_hca_mteim_reg_ext_print(&(ptr_struct->mteim_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_stdb_reg_ext:\n");
	reg_access_hca_mtrc_stdb_reg_ext_print(&(ptr_struct->mtrc_stdb_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug_cap:\n");
	reg_access_hca_debug_cap_print(&(ptr_struct->debug_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_cap_ext:\n");
	reg_access_hca_mcqi_cap_ext_print(&(ptr_struct->mcqi_cap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_hca_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dtor_reg_ext:\n");
	reg_access_hca_dtor_reg_ext_print(&(ptr_struct->dtor_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "misoc_reg_ext:\n");
	reg_access_hca_misoc_reg_ext_print(&(ptr_struct->misoc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_ctrl_reg_ext:\n");
	reg_access_hca_mtrc_ctrl_reg_ext_print(&(ptr_struct->mtrc_ctrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mqis_reg_ext:\n");
	reg_access_hca_mqis_reg_ext_print(&(ptr_struct->mqis_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcc_reg_ext:\n");
	reg_access_hca_mcc_reg_ext_print(&(ptr_struct->mcc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfsv_reg_ext:\n");
	reg_access_hca_mfsv_reg_ext_print(&(ptr_struct->mfsv_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfpa_reg_ext:\n");
	reg_access_hca_mfpa_reg_ext_print(&(ptr_struct->mfpa_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_activation_method_ext:\n");
	reg_access_hca_mcqi_activation_method_ext_print(&(ptr_struct->mcqi_activation_method_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcam_reg_ext:\n");
	reg_access_hca_mcam_reg_ext_print(&(ptr_struct->mcam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_version_ext:\n");
	reg_access_hca_mcqi_version_ext_print(&(ptr_struct->mcqi_version_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pguid_reg_ext:\n");
	reg_access_hca_pguid_reg_ext_print(&(ptr_struct->pguid_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtim_ext:\n");
	reg_access_hca_mtim_ext_print(&(ptr_struct->mtim_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mrsi_ext:\n");
	reg_access_hca_mrsi_ext_print(&(ptr_struct->mrsi_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvgc_reg_ext:\n");
	reg_access_hca_mnvgc_reg_ext_print(&(ptr_struct->mnvgc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_reg_ext:\n");
	reg_access_hca_mcqi_reg_ext_print(&(ptr_struct->mcqi_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpcir_ext:\n");
	reg_access_hca_mpcir_ext_print(&(ptr_struct->mpcir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvqc_reg_ext:\n");
	reg_access_hca_mnvqc_reg_ext_print(&(ptr_struct->mnvqc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_eug_reg_ext:\n");
	reg_access_hca_nic_dpa_eug_reg_ext_print(&(ptr_struct->nic_dpa_eug_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtdc_ext:\n");
	reg_access_hca_mtdc_ext_print(&(ptr_struct->mtdc_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_perf_ctrl_reg_ext:\n");
	reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(&(ptr_struct->nic_dpa_perf_ctrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_cap_ext_reg_ext:\n");
	reg_access_hca_nic_cap_ext_reg_ext_print(&(ptr_struct->nic_cap_ext_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir_ext:\n");
	reg_access_hca_mgir_ext_print(&(ptr_struct->mgir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmdio_ext:\n");
	reg_access_hca_mmdio_ext_print(&(ptr_struct->mmdio_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcia_ext:\n");
	reg_access_hca_mcia_ext_print(&(ptr_struct->mcia_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtie_ext:\n");
	reg_access_hca_mtie_ext_print(&(ptr_struct->mtie_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "paos_reg_ext:\n");
	reg_access_hca_paos_reg_ext_print(&(ptr_struct->paos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nic_dpa_eu_partition_reg_ext:\n");
	reg_access_hca_nic_dpa_eu_partition_reg_ext_print(&(ptr_struct->nic_dpa_eu_partition_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcnr_reg_ext:\n");
	reg_access_hca_pcnr_reg_ext_print(&(ptr_struct->pcnr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpegc_reg_ext:\n");
	reg_access_hca_mpegc_reg_ext_print(&(ptr_struct->mpegc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfba_reg_ext:\n");
	reg_access_hca_mfba_reg_ext_print(&(ptr_struct->mfba_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_reg_ext:\n");
	reg_access_hca_ptys_reg_ext_print(&(ptr_struct->ptys_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfrl_reg_ext:\n");
	reg_access_hca_mfrl_reg_ext_print(&(ptr_struct->mfrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRSV_ext:\n");
	reg_access_hca_MRSV_ext_print(&(ptr_struct->MRSV_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmhi_reg_ext:\n");
	reg_access_hca_mmhi_reg_ext_print(&(ptr_struct->mmhi_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mroq_ext:\n");
	reg_access_hca_mroq_ext_print(&(ptr_struct->mroq_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcda_reg_ext:\n");
	reg_access_hca_mcda_reg_ext_print(&(ptr_struct->mcda_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_conf_reg_ext:\n");
	reg_access_hca_mtrc_conf_reg_ext_print(&(ptr_struct->mtrc_conf_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpqd_reg_ext:\n");
	reg_access_hca_mpqd_reg_ext_print(&(ptr_struct->mpqd_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvdi_reg_ext:\n");
	reg_access_hca_mnvdi_reg_ext_print(&(ptr_struct->mnvdi_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvia_reg_ext:\n");
	reg_access_hca_mnvia_reg_ext_print(&(ptr_struct->mnvia_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpein_reg_ext:\n");
	reg_access_hca_mpein_reg_ext_print(&(ptr_struct->mpein_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_hca_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqs_reg_ext:\n");
	reg_access_hca_mcqs_reg_ext_print(&(ptr_struct->mcqs_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_cap_reg_ext:\n");
	reg_access_hca_mtrc_cap_reg_ext_print(&(ptr_struct->mtrc_cap_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_dump_ext:\n");
	reg_access_hca_resource_dump_ext_print(&(ptr_struct->resource_dump_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcqi_linkx_properties_ext:\n");
	reg_access_hca_mcqi_linkx_properties_ext_print(&(ptr_struct->mcqi_linkx_properties_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpir_ext:\n");
	reg_access_hca_mpir_ext_print(&(ptr_struct->mpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcap_ext:\n");
	reg_access_hca_mtcap_ext_print(&(ptr_struct->mtcap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfbe_reg_ext:\n");
	reg_access_hca_mfbe_reg_ext_print(&(ptr_struct->mfbe_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtmp_ext:\n");
	reg_access_hca_mtmp_ext_print(&(ptr_struct->mtmp_ext), fd, indent_level + 1);
}

unsigned int reg_access_hca_reg_access_hca_Nodes_size(void)
{
	return REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE;
}

void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd)
{
	reg_access_hca_reg_access_hca_Nodes_print(ptr_struct, fd, 0);
}

