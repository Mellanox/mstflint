
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
         *** This file was generated at "2023-01-15 15:00:18"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_ --no-adb-utils
         ***/
#include "tools_open_layouts.h"

void tools_open_bmc_type_pack(const struct tools_open_bmc_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->param_idx);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->channel);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_bmc_type_unpack(struct tools_open_bmc_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 19;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);
	offset = 14;
	ptr_struct->channel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_bmc_type_print(const struct tools_open_bmc_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_bmc_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "channel              : " UH_FMT "\n", ptr_struct->channel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host                 : " UH_FMT "\n", ptr_struct->host);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_bmc_type_size(void)
{
	return TOOLS_OPEN_BMC_TYPE_SIZE;
}

void tools_open_bmc_type_dump(const struct tools_open_bmc_type *ptr_struct, FILE *fd)
{
	tools_open_bmc_type_print(ptr_struct, fd, 0);
}

void tools_open_configuration_item_type_class_module_pack(const struct tools_open_configuration_item_type_class_module *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 14, (u_int32_t)ptr_struct->parameter_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->module_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_class);
}

void tools_open_configuration_item_type_class_module_unpack(struct tools_open_configuration_item_type_class_module *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->parameter_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 14);
	offset = 8;
	ptr_struct->module_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 0;
	ptr_struct->type_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_configuration_item_type_class_module_print(const struct tools_open_configuration_item_type_class_module *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_configuration_item_type_class_module ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "parameter_index      : " UH_FMT "\n", ptr_struct->parameter_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_index         : " UH_FMT "\n", ptr_struct->module_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_class           : " UH_FMT "\n", ptr_struct->type_class);
}

unsigned int tools_open_configuration_item_type_class_module_size(void)
{
	return TOOLS_OPEN_CONFIGURATION_ITEM_TYPE_CLASS_MODULE_SIZE;
}

void tools_open_configuration_item_type_class_module_dump(const struct tools_open_configuration_item_type_class_module *ptr_struct, FILE *fd)
{
	tools_open_configuration_item_type_class_module_print(ptr_struct, fd, 0);
}

void tools_open_eswitch_type_pack(const struct tools_open_eswitch_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->param_idx);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->port);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_eswitch_type_unpack(struct tools_open_eswitch_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 14;
	ptr_struct->port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_eswitch_type_print(const struct tools_open_eswitch_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_eswitch_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port                 : " UH_FMT "\n", ptr_struct->port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host                 : " UH_FMT "\n", ptr_struct->host);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_eswitch_type_size(void)
{
	return TOOLS_OPEN_ESWITCH_TYPE_SIZE;
}

void tools_open_eswitch_type_dump(const struct tools_open_eswitch_type *ptr_struct, FILE *fd)
{
	tools_open_eswitch_type_print(ptr_struct, fd, 0);
}

void tools_open_global_type_pack(const struct tools_open_global_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->param_idx);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_global_type_unpack(struct tools_open_global_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->param_idx = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_global_type_print(const struct tools_open_global_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_global_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_global_type_size(void)
{
	return TOOLS_OPEN_GLOBAL_TYPE_SIZE;
}

void tools_open_global_type_dump(const struct tools_open_global_type *ptr_struct, FILE *fd)
{
	tools_open_global_type_print(ptr_struct, fd, 0);
}

void tools_open_host_type_pack(const struct tools_open_host_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 18, (u_int32_t)ptr_struct->param_idx);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_host_type_unpack(struct tools_open_host_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	ptr_struct->param_idx = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 18);
	offset = 8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_host_type_print(const struct tools_open_host_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_host_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host                 : " UH_FMT "\n", ptr_struct->host);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_host_type_size(void)
{
	return TOOLS_OPEN_HOST_TYPE_SIZE;
}

void tools_open_host_type_dump(const struct tools_open_host_type *ptr_struct, FILE *fd)
{
	tools_open_host_type_print(ptr_struct, fd, 0);
}

void tools_open_per_host_type_pack(const struct tools_open_per_host_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->param_idx);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->function);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_per_host_type_unpack(struct tools_open_per_host_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 14;
	ptr_struct->function = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_per_host_type_print(const struct tools_open_per_host_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_per_host_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "function             : " UH_FMT "\n", ptr_struct->function);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host                 : " UH_FMT "\n", ptr_struct->host);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_per_host_type_size(void)
{
	return TOOLS_OPEN_PER_HOST_TYPE_SIZE;
}

void tools_open_per_host_type_dump(const struct tools_open_per_host_type *ptr_struct, FILE *fd)
{
	tools_open_per_host_type_print(ptr_struct, fd, 0);
}

void tools_open_per_port_type_pack(const struct tools_open_per_port_type *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->param_idx);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);
}

void tools_open_per_port_type_unpack(struct tools_open_per_port_type *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_per_port_type_print(const struct tools_open_per_port_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_per_port_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_idx            : " UH_FMT "\n", ptr_struct->param_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port                 : " UH_FMT "\n", ptr_struct->port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param_class          : " UH_FMT "\n", ptr_struct->param_class);
}

unsigned int tools_open_per_port_type_size(void)
{
	return TOOLS_OPEN_PER_PORT_TYPE_SIZE;
}

void tools_open_per_port_type_dump(const struct tools_open_per_port_type *ptr_struct, FILE *fd)
{
	tools_open_per_port_type_print(ptr_struct, fd, 0);
}

void tools_open_tlv_type_dw_pack(const struct tools_open_tlv_type_dw *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tlv_type_dw);
}

void tools_open_tlv_type_dw_unpack(struct tools_open_tlv_type_dw *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->tlv_type_dw = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_tlv_type_dw_print(const struct tools_open_tlv_type_dw *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_tlv_type_dw ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tlv_type_dw          : " U32H_FMT "\n", ptr_struct->tlv_type_dw);
}

unsigned int tools_open_tlv_type_dw_size(void)
{
	return TOOLS_OPEN_TLV_TYPE_DW_SIZE;
}

void tools_open_tlv_type_dw_dump(const struct tools_open_tlv_type_dw *ptr_struct, FILE *fd)
{
	tools_open_tlv_type_dw_print(ptr_struct, fd, 0);
}

void tools_open_fw_version_pack(const struct tools_open_fw_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_major);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_subminor);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_minor);
}

void tools_open_fw_version_unpack(struct tools_open_fw_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->fw_ver_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->fw_ver_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->fw_ver_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tools_open_fw_version_print(const struct tools_open_fw_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_fw_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_ver_major         : " UH_FMT "\n", ptr_struct->fw_ver_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_ver_subminor      : " UH_FMT "\n", ptr_struct->fw_ver_subminor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_ver_minor         : " UH_FMT "\n", ptr_struct->fw_ver_minor);
}

unsigned int tools_open_fw_version_size(void)
{
	return TOOLS_OPEN_FW_VERSION_SIZE;
}

void tools_open_fw_version_dump(const struct tools_open_fw_version *ptr_struct, FILE *fd)
{
	tools_open_fw_version_print(ptr_struct, fd, 0);
}

void tools_open_tlv_type_pack(const union tools_open_tlv_type *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_tlv_type_dw_pack(&(ptr_struct->tlv_type_dw), ptr_buff);
}

void tools_open_tlv_type_unpack(union tools_open_tlv_type *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_tlv_type_dw_unpack(&(ptr_struct->tlv_type_dw), ptr_buff);
}

void tools_open_tlv_type_print(const union tools_open_tlv_type *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_tlv_type ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "global:\n");
	tools_open_global_type_print(&(ptr_struct->global), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eswitch:\n");
	tools_open_eswitch_type_print(&(ptr_struct->eswitch), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_host:\n");
	tools_open_per_host_type_print(&(ptr_struct->per_host), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bmc:\n");
	tools_open_bmc_type_print(&(ptr_struct->bmc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_port:\n");
	tools_open_per_port_type_print(&(ptr_struct->per_port), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "per_module:\n");
	tools_open_configuration_item_type_class_module_print(&(ptr_struct->per_module), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host:\n");
	tools_open_host_type_print(&(ptr_struct->host), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tlv_type_dw:\n");
	tools_open_tlv_type_dw_print(&(ptr_struct->tlv_type_dw), fd, indent_level + 1);
}

unsigned int tools_open_tlv_type_size(void)
{
	return TOOLS_OPEN_TLV_TYPE_SIZE;
}

void tools_open_tlv_type_dump(const union tools_open_tlv_type *ptr_struct, FILE *fd)
{
	tools_open_tlv_type_print(ptr_struct, fd, 0);
}

void tools_open_ts_entry_pack(const struct tools_open_ts_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_day);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_month);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ts_year);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_seconds);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_minutes);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_hour);
}

void tools_open_ts_entry_unpack(struct tools_open_ts_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->ts_day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->ts_month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->ts_year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->ts_seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->ts_minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->ts_hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_ts_entry_print(const struct tools_open_ts_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_ts_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_day               : " UH_FMT "\n", ptr_struct->ts_day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_month             : " UH_FMT "\n", ptr_struct->ts_month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_year              : " UH_FMT "\n", ptr_struct->ts_year);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_seconds           : " UH_FMT "\n", ptr_struct->ts_seconds);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_minutes           : " UH_FMT "\n", ptr_struct->ts_minutes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_hour              : " UH_FMT "\n", ptr_struct->ts_hour);
}

unsigned int tools_open_ts_entry_size(void)
{
	return TOOLS_OPEN_TS_ENTRY_SIZE;
}

void tools_open_ts_entry_dump(const struct tools_open_ts_entry *ptr_struct, FILE *fd)
{
	tools_open_ts_entry_print(ptr_struct, fd, 0);
}

void tools_open_nv_hdr_fifth_gen_pack(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->length);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->writer_host_id);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->writer_id);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->read_current);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rd_en);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->over_en);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->priority);
	offset = 32;
	tools_open_tlv_type_pack(&(ptr_struct->type), ptr_buff + offset / 8);
}

void tools_open_nv_hdr_fifth_gen_unpack(struct tools_open_nv_hdr_fifth_gen *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 23;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	offset = 20;
	ptr_struct->writer_host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 16;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 11;
	ptr_struct->writer_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 9;
	ptr_struct->read_current = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->default_ = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 7;
	ptr_struct->rd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->over_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->priority = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	tools_open_tlv_type_unpack(&(ptr_struct->type), ptr_buff + offset / 8);
}

void tools_open_nv_hdr_fifth_gen_print(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_hdr_fifth_gen ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "writer_host_id       : " UH_FMT "\n", ptr_struct->writer_host_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "writer_id            : %s (" UH_FMT ")\n", (ptr_struct->writer_id == 0 ? ("NV_WRITER_ID_UNSPECIFIED") : ((ptr_struct->writer_id == 1 ? ("NV_WRITER_ID_CHASSIS_BMC") : ((ptr_struct->writer_id == 2 ? ("NV_WRITER_ID_MAD") : ((ptr_struct->writer_id == 3 ? ("NV_WRITER_ID_BMC") : ((ptr_struct->writer_id == 4 ? ("NV_WRITER_ID_CMD_IF") : ((ptr_struct->writer_id == 5 ? ("NV_WRITER_ID_ICMD") : ((ptr_struct->writer_id == 6 ? ("NV_WRITER_ID_ICMD_UEFI_HII") : ((ptr_struct->writer_id == 7 ? ("NV_WRITER_ID_ICMD_UEFI_CLP") : ((ptr_struct->writer_id == 8 ? ("NV_WRITER_ID_ICMD_FLEXBOOT") : ((ptr_struct->writer_id == 9 ? ("NV_WRITER_ID_ICMD_MLXCONFIG") : ((ptr_struct->writer_id == 10 ? ("NV_WRITER_ID_ICMD_USER1") : ((ptr_struct->writer_id == 11 ? ("NV_WRITER_ID_ICMD_USER2") : ((ptr_struct->writer_id == 31 ? ("NV_WRITER_ID_OTHER") : ("unknown")))))))))))))))))))))))))), ptr_struct->writer_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_current         : " UH_FMT "\n", ptr_struct->read_current);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_             : " UH_FMT "\n", ptr_struct->default_);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rd_en                : " UH_FMT "\n", ptr_struct->rd_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "over_en              : " UH_FMT "\n", ptr_struct->over_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "priority             : " UH_FMT "\n", ptr_struct->priority);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type:\n");
	tools_open_tlv_type_print(&(ptr_struct->type), fd, indent_level + 1);
}

unsigned int tools_open_nv_hdr_fifth_gen_size(void)
{
	return TOOLS_OPEN_NV_HDR_FIFTH_GEN_SIZE;
}

void tools_open_nv_hdr_fifth_gen_dump(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE *fd)
{
	tools_open_nv_hdr_fifth_gen_print(ptr_struct, fd, 0);
}

void tools_open_timestamp_pack(const struct tools_open_timestamp *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_fw_version_pack(&(ptr_struct->fw_version), ptr_buff + offset / 8);
	offset = 64;
	tools_open_ts_entry_pack(&(ptr_struct->ts_entry), ptr_buff + offset / 8);
}

void tools_open_timestamp_unpack(struct tools_open_timestamp *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_fw_version_unpack(&(ptr_struct->fw_version), ptr_buff + offset / 8);
	offset = 64;
	tools_open_ts_entry_unpack(&(ptr_struct->ts_entry), ptr_buff + offset / 8);
}

void tools_open_timestamp_print(const struct tools_open_timestamp *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_timestamp ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version:\n");
	tools_open_fw_version_print(&(ptr_struct->fw_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts_entry:\n");
	tools_open_ts_entry_print(&(ptr_struct->ts_entry), fd, indent_level + 1);
}

unsigned int tools_open_timestamp_size(void)
{
	return TOOLS_OPEN_TIMESTAMP_SIZE;
}

void tools_open_timestamp_dump(const struct tools_open_timestamp *ptr_struct, FILE *fd)
{
	tools_open_timestamp_print(ptr_struct, fd, 0);
}

void tools_open_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void tools_open_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void tools_open_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int tools_open_uint64_size(void)
{
	return TOOLS_OPEN_UINT64_SIZE;
}

void tools_open_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	tools_open_uint64_print(ptr_struct, fd, 0);
}

void tools_open_aux_tlv_header_pack(const struct tools_open_aux_tlv_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->header_type);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->length);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved0);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved1);
}

void tools_open_aux_tlv_header_unpack(struct tools_open_aux_tlv_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->header_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->length = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->reserved0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->reserved1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_aux_tlv_header_print(const struct tools_open_aux_tlv_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_aux_tlv_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "header_type          : " UH_FMT "\n", ptr_struct->header_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " U32H_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved0            : " U32H_FMT "\n", ptr_struct->reserved0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " U32H_FMT "\n", ptr_struct->reserved1);
}

unsigned int tools_open_aux_tlv_header_size(void)
{
	return TOOLS_OPEN_AUX_TLV_HEADER_SIZE;
}

void tools_open_aux_tlv_header_dump(const struct tools_open_aux_tlv_header *ptr_struct, FILE *fd)
{
	tools_open_aux_tlv_header_print(ptr_struct, fd, 0);
}

void tools_open_mgnle_pack(const struct tools_open_mgnle *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->le_pointer);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lost_events);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->synced_time);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_h);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_l);
	offset = 128;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(376, 8, i, 1376, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_data[i]);
	}
}

void tools_open_mgnle_unpack(struct tools_open_mgnle *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->le_pointer = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->lost_events = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->synced_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->time_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->time_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(376, 8, i, 1376, 1);
		ptr_struct->log_data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_mgnle_print(const struct tools_open_mgnle *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mgnle ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "le_pointer           : " U32H_FMT "\n", ptr_struct->le_pointer);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lost_events          : " UH_FMT "\n", ptr_struct->lost_events);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "synced_time          : " UH_FMT "\n", ptr_struct->synced_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_h               : " U32H_FMT "\n", ptr_struct->time_h);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_l               : " U32H_FMT "\n", ptr_struct->time_l);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 128; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "log_data_%03d        : " UH_FMT "\n", i, ptr_struct->log_data[i]);
	}
}

unsigned int tools_open_mgnle_size(void)
{
	return TOOLS_OPEN_MGNLE_SIZE;
}

void tools_open_mgnle_dump(const struct tools_open_mgnle *ptr_struct, FILE *fd)
{
	tools_open_mgnle_print(ptr_struct, fd, 0);
}

void tools_open_mlock_pack(const struct tools_open_mlock *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);
}

void tools_open_mlock_unpack(struct tools_open_mlock *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void tools_open_mlock_print(const struct tools_open_mlock *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mlock ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : " UH_FMT "\n", ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "key                  : " U64H_FMT "\n", ptr_struct->key);
}

unsigned int tools_open_mlock_size(void)
{
	return TOOLS_OPEN_MLOCK_SIZE;
}

void tools_open_mlock_dump(const struct tools_open_mlock *ptr_struct, FILE *fd)
{
	tools_open_mlock_print(ptr_struct, fd, 0);
}

void tools_open_mnvda_pack(const struct tools_open_mnvda *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 2144, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}
}

void tools_open_mnvda_unpack(struct tools_open_mnvda *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 2144, 1);
		ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_mnvda_print(const struct tools_open_mnvda *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnvda ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 256; i += 4) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d\t: " U8H_FMT "\t",   i, ptr_struct->data[i]);
		fprintf(fd, "data_%03d\t: " U8H_FMT "\t",   i+1, ptr_struct->data[i+1]);
		fprintf(fd, "data_%03d\t: " U8H_FMT "\t",   i+2, ptr_struct->data[i+2]);
		fprintf(fd, "data_%03d\t: " U8H_FMT "\n",   i+3, ptr_struct->data[i+3]);
	}
}

unsigned int tools_open_mnvda_size(void)
{
	return TOOLS_OPEN_MNVDA_SIZE;
}

void tools_open_mnvda_dump(const struct tools_open_mnvda *ptr_struct, FILE *fd)
{
	tools_open_mnvda_print(ptr_struct, fd, 0);
}

void tools_open_mnvdi_pack(const struct tools_open_mnvdi *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	offset = 0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);	
}
void tools_open_mnvdi_unpack(struct tools_open_mnvdi *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	offset = 0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}
void tools_open_mnvdi_print(const struct tools_open_mnvdi *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnvdi ========\n");
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
}
unsigned int tools_open_mnvdi_size(void)
{
	return TOOLS_OPEN_MNVDI_SIZE;
}
void tools_open_mnvgn_pack(const struct tools_open_mnvgn *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->nv_pointer);
	offset = 128;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(248, 8, i, 1248, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->nv_data[i]);
	}
}

void tools_open_mnvgn_unpack(struct tools_open_mnvgn *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->nv_pointer = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(248, 8, i, 1248, 1);
		ptr_struct->nv_data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_mnvgn_print(const struct tools_open_mnvgn *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnvgn ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_pointer           : " U32H_FMT "\n", ptr_struct->nv_pointer);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 128; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "nv_data_%03d         : " UH_FMT "\n", i, ptr_struct->nv_data[i]);
	}
}

unsigned int tools_open_mnvgn_size(void)
{
	return TOOLS_OPEN_MNVGN_SIZE;
}

void tools_open_mnvgn_dump(const struct tools_open_mnvgn *ptr_struct, FILE *fd)
{
	tools_open_mnvgn_print(ptr_struct, fd, 0);
}

void tools_open_mvts_pack(const struct tools_open_mvts *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->check_timestamp_flag);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->running_flag);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clear_all_ts_flag);
	offset = 32;
	tools_open_timestamp_pack(&(ptr_struct->timestamp), ptr_buff + offset / 8);
}

void tools_open_mvts_unpack(struct tools_open_mvts *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->check_timestamp_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->running_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->clear_all_ts_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	tools_open_timestamp_unpack(&(ptr_struct->timestamp), ptr_buff + offset / 8);
}

void tools_open_mvts_print(const struct tools_open_mvts *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mvts ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "check_timestamp_flag : " UH_FMT "\n", ptr_struct->check_timestamp_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "running_flag         : " UH_FMT "\n", ptr_struct->running_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clear_all_ts_flag    : " UH_FMT "\n", ptr_struct->clear_all_ts_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "timestamp:\n");
	tools_open_timestamp_print(&(ptr_struct->timestamp), fd, indent_level + 1);
}

unsigned int tools_open_mvts_size(void)
{
	return TOOLS_OPEN_MVTS_SIZE;
}

void tools_open_mvts_dump(const struct tools_open_mvts *ptr_struct, FILE *fd)
{
	tools_open_mvts_print(ptr_struct, fd, 0);
}

void tools_open_aux_tlv_pack(const struct tools_open_aux_tlv *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_aux_tlv_header_pack(&(ptr_struct->aux_tlv_header), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(184, 8, i, 2048, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}
}

void tools_open_aux_tlv_unpack(struct tools_open_aux_tlv *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_aux_tlv_header_unpack(&(ptr_struct->aux_tlv_header), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(184, 8, i, 2048, 1);
		ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_aux_tlv_print(const struct tools_open_aux_tlv *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_aux_tlv ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aux_tlv_header:\n");
	tools_open_aux_tlv_header_print(&(ptr_struct->aux_tlv_header), fd, indent_level + 1);
	for (i = 0; i < 128; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " UH_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int tools_open_aux_tlv_size(void)
{
	return TOOLS_OPEN_AUX_TLV_SIZE;
}

void tools_open_aux_tlv_dump(const struct tools_open_aux_tlv *ptr_struct, FILE *fd)
{
	tools_open_aux_tlv_print(ptr_struct, fd, 0);
}

void tools_open_image_info_pack(const struct tools_open_image_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->description[i]);
	}
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->name[i]);
	}
	for (i = 0; i < 96; ++i) {
		offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prs_name[i]);
	}
}

void tools_open_image_info_unpack(struct tools_open_image_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 8;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
		ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->psid[16] = '\0';
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
		ptr_struct->description[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->description[256] = '\0';
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
		ptr_struct->name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->name[64] = '\0';
	for (i = 0; i < 96; ++i) {
		offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
		ptr_struct->prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->prs_name[96] = '\0';
}

void tools_open_image_info_print(const struct tools_open_image_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_image_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
		fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
		fprintf(fd, "description          : \"%s\"\n", ptr_struct->description);
		fprintf(fd, "name                 : \"%s\"\n", ptr_struct->name);
		fprintf(fd, "prs_name             : \"%s\"\n", ptr_struct->prs_name);
}

unsigned int tools_open_image_info_size(void)
{
	return TOOLS_OPEN_IMAGE_INFO_SIZE;
}

void tools_open_image_info_dump(const struct tools_open_image_info *ptr_struct, FILE *fd)
{
	tools_open_image_info_print(ptr_struct, fd, 0);
}

void tools_open_mfg_info_pack(const struct tools_open_mfg_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);
	for (i = 0; i < 96; ++i) {
		offset = adb2c_calc_array_field_address(792, 8, i, 2560, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->orig_prs_name[i]);
	}
}

void tools_open_mfg_info_unpack(struct tools_open_mfg_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
		ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->psid[16] = '\0';
	offset = 232;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 96; ++i) {
		offset = adb2c_calc_array_field_address(792, 8, i, 2560, 1);
		ptr_struct->orig_prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->orig_prs_name[96] = '\0';
}

void tools_open_mfg_info_print(const struct tools_open_mfg_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mfg_info ========\n");

		fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
		fprintf(fd, "orig_prs_name        : \"%s\"\n", ptr_struct->orig_prs_name);
}

unsigned int tools_open_mfg_info_size(void)
{
	return TOOLS_OPEN_MFG_INFO_SIZE;
}

void tools_open_mfg_info_dump(const struct tools_open_mfg_info *ptr_struct, FILE *fd)
{
	tools_open_mfg_info_print(ptr_struct, fd, 0);
}

void tools_open_mnv_cfg_pack(const union tools_open_mnv_cfg *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_mnvda_pack(&(ptr_struct->mnvda), ptr_buff);
}

void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_mnvda_unpack(&(ptr_struct->mnvda), ptr_buff);
}

void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnv_cfg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mvts:\n");
	tools_open_mvts_print(&(ptr_struct->mvts), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mlock:\n");
	tools_open_mlock_print(&(ptr_struct->mlock), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvda:\n");
	tools_open_mnvda_print(&(ptr_struct->mnvda), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvgn:\n");
	tools_open_mnvgn_print(&(ptr_struct->mnvgn), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgnle:\n");
	tools_open_mgnle_print(&(ptr_struct->mgnle), fd, indent_level + 1);
}

unsigned int tools_open_mnv_cfg_size(void)
{
	return TOOLS_OPEN_MNV_CFG_SIZE;
}

void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE *fd)
{
	tools_open_mnv_cfg_print(ptr_struct, fd, 0);
}

void tools_open_nv_base_mac_guid_pack(const struct tools_open_nv_base_mac_guid *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->base_mac[i]);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 128, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->base_guid[i]);
	}
}

void tools_open_nv_base_mac_guid_unpack(struct tools_open_nv_base_mac_guid *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		ptr_struct->base_mac[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 128, 1);
		ptr_struct->base_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void tools_open_nv_base_mac_guid_print(const struct tools_open_nv_base_mac_guid *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_base_mac_guid ========\n");

	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "base_mac_%03d        : " U32H_FMT "\n", i, ptr_struct->base_mac[i]);
	}
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "base_guid_%03d       : " U32H_FMT "\n", i, ptr_struct->base_guid[i]);
	}
}

unsigned int tools_open_nv_base_mac_guid_size(void)
{
	return TOOLS_OPEN_NV_BASE_MAC_GUID_SIZE;
}

void tools_open_nv_base_mac_guid_dump(const struct tools_open_nv_base_mac_guid *ptr_struct, FILE *fd)
{
	tools_open_nv_base_mac_guid_print(ptr_struct, fd, 0);
}

void tools_open_nv_base_mac_guid_cap_pack(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->guid_en);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mac_en);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_allocated_macs);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_allocated_guids);
}

void tools_open_nv_base_mac_guid_cap_unpack(struct tools_open_nv_base_mac_guid_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 1;
	ptr_struct->guid_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->mac_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->num_of_allocated_macs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->num_of_allocated_guids = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tools_open_nv_base_mac_guid_cap_print(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_base_mac_guid_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guid_en              : " UH_FMT "\n", ptr_struct->guid_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mac_en               : " UH_FMT "\n", ptr_struct->mac_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_allocated_macs : " UH_FMT "\n", ptr_struct->num_of_allocated_macs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_allocated_guids : " UH_FMT "\n", ptr_struct->num_of_allocated_guids);
}

unsigned int tools_open_nv_base_mac_guid_cap_size(void)
{
	return TOOLS_OPEN_NV_BASE_MAC_GUID_CAP_SIZE;
}

void tools_open_nv_base_mac_guid_cap_dump(const struct tools_open_nv_base_mac_guid_cap *ptr_struct, FILE *fd)
{
	tools_open_nv_base_mac_guid_cap_print(ptr_struct, fd, 0);
}

void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_clock_map_to_user);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_phy_param_mode);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_steer_force_vlan_supported);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_cq_timestamp_supported);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_vfs);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uar_bar_size);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_uar_bar_size);
	offset = 42;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_ip_ver);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_phy_param_mode);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_clock_map_to_user);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_steer_force_vlan);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_cq_timestamp);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);
}

void tools_open_query_def_params_global_unpack(struct tools_open_query_def_params_global *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 17;
	ptr_struct->nv_config_clock_map_to_user = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->nv_config_phy_param_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 15;
	ptr_struct->nv_steer_force_vlan_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 14;
	ptr_struct->nv_cq_timestamp_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->num_vfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 52;
	ptr_struct->uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->max_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 42;
	ptr_struct->boot_ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 40;
	ptr_struct->default_phy_param_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 36;
	ptr_struct->default_clock_map_to_user = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 35;
	ptr_struct->default_steer_force_vlan = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->default_cq_timestamp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_query_def_params_global_print(const struct tools_open_query_def_params_global *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_query_def_params_global ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_clock_map_to_user : " UH_FMT "\n", ptr_struct->nv_config_clock_map_to_user);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_phy_param_mode : " UH_FMT "\n", ptr_struct->nv_config_phy_param_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_steer_force_vlan_supported : " UH_FMT "\n", ptr_struct->nv_steer_force_vlan_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_cq_timestamp_supported : " UH_FMT "\n", ptr_struct->nv_cq_timestamp_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_default_config_payload_version : " UH_FMT "\n", ptr_struct->fw_default_config_payload_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_vfs              : " UH_FMT "\n", ptr_struct->num_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uar_bar_size         : " UH_FMT "\n", ptr_struct->uar_bar_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_uar_bar_size     : " UH_FMT "\n", ptr_struct->max_uar_bar_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_ip_ver          : " UH_FMT "\n", ptr_struct->boot_ip_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_phy_param_mode : " UH_FMT "\n", ptr_struct->default_phy_param_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_clock_map_to_user : " UH_FMT "\n", ptr_struct->default_clock_map_to_user);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_steer_force_vlan : " UH_FMT "\n", ptr_struct->default_steer_force_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_cq_timestamp : " UH_FMT "\n", ptr_struct->default_cq_timestamp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_en             : " UH_FMT "\n", ptr_struct->sriov_en);
}

unsigned int tools_open_query_def_params_global_size(void)
{
	return TOOLS_OPEN_QUERY_DEF_PARAMS_GLOBAL_SIZE;
}

void tools_open_query_def_params_global_dump(const struct tools_open_query_def_params_global *ptr_struct, FILE *fd)
{
	tools_open_query_def_params_global_print(ptr_struct, fd, 0);
}

void tools_open_query_def_params_per_port_pack(const struct tools_open_query_def_params_per_port *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_vpi_force_mode);
	offset = 13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_vpi);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_wol);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->default_boot_vlan);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->default_boot_protocol);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->default_boot_retry_cnt);
	offset = 37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_network_link_type);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_en_wol_magic);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_boot_vlan_en);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_boot_option_rom_en);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_pprx);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_pptx);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->default_boot_pkey);
	offset = 70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->boot_ip_ver);
	offset = 68;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_infiniband_dhcp_settings);
	offset = 67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_infiniband_boot_settings);
	offset = 66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_dhcp_iscsi_parameters);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_iscsi_parameters);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_boot_parameters);
	offset = 118;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_vpi_force_mode);
	offset = 116;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_vpi_xfi_mode);
	offset = 114;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_vpi_phy_type);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->iscsi_boot_to_target);
	offset = 101;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_vlan_en);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_tcp_timestamps_en);
	offset = 99;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_mutual_auth_en);
	offset = 98;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_auth_en);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_dhcp_params_en);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_ipv4_dhcp_en);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_lun_busy_retry_cnt);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_link_up_delay_time);
}

void tools_open_query_def_params_per_port_unpack(struct tools_open_query_def_params_per_port *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 14;
	ptr_struct->nv_config_vpi_force_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 13;
	ptr_struct->nv_config_vpi = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 12;
	ptr_struct->nv_config_wol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 52;
	ptr_struct->default_boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 44;
	ptr_struct->default_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->default_boot_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 37;
	ptr_struct->default_network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 36;
	ptr_struct->default_en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 35;
	ptr_struct->default_boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->default_boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->default_pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->default_pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 80;
	ptr_struct->default_boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 70;
	ptr_struct->boot_ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 68;
	ptr_struct->nv_config_infiniband_dhcp_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 67;
	ptr_struct->nv_config_infiniband_boot_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 66;
	ptr_struct->nv_config_dhcp_iscsi_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 65;
	ptr_struct->nv_config_iscsi_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->nv_config_boot_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 118;
	ptr_struct->default_vpi_force_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 116;
	ptr_struct->default_vpi_xfi_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 114;
	ptr_struct->default_vpi_phy_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 104;
	ptr_struct->iscsi_boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 101;
	ptr_struct->iscsi_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 100;
	ptr_struct->iscsi_tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 99;
	ptr_struct->iscsi_chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 98;
	ptr_struct->iscsi_chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 97;
	ptr_struct->iscsi_dhcp_params_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->iscsi_ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 152;
	ptr_struct->iscsi_lun_busy_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->iscsi_link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_query_def_params_per_port_print(const struct tools_open_query_def_params_per_port *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_query_def_params_per_port ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_vpi_force_mode : " UH_FMT "\n", ptr_struct->nv_config_vpi_force_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_vpi        : " UH_FMT "\n", ptr_struct->nv_config_vpi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_wol        : " UH_FMT "\n", ptr_struct->nv_config_wol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_default_config_payload_version : " UH_FMT "\n", ptr_struct->fw_default_config_payload_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_vlan    : " UH_FMT "\n", ptr_struct->default_boot_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_protocol : " UH_FMT "\n", ptr_struct->default_boot_protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_retry_cnt : " UH_FMT "\n", ptr_struct->default_boot_retry_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_network_link_type : " UH_FMT "\n", ptr_struct->default_network_link_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_en_wol_magic : " UH_FMT "\n", ptr_struct->default_en_wol_magic);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_vlan_en : " UH_FMT "\n", ptr_struct->default_boot_vlan_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_option_rom_en : " UH_FMT "\n", ptr_struct->default_boot_option_rom_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_pprx         : " UH_FMT "\n", ptr_struct->default_pprx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_pptx         : " UH_FMT "\n", ptr_struct->default_pptx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_boot_pkey    : " UH_FMT "\n", ptr_struct->default_boot_pkey);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_ip_ver          : " UH_FMT "\n", ptr_struct->boot_ip_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_infiniband_dhcp_settings : " UH_FMT "\n", ptr_struct->nv_config_infiniband_dhcp_settings);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_infiniband_boot_settings : " UH_FMT "\n", ptr_struct->nv_config_infiniband_boot_settings);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_dhcp_iscsi_parameters : " UH_FMT "\n", ptr_struct->nv_config_dhcp_iscsi_parameters);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_iscsi_parameters : " UH_FMT "\n", ptr_struct->nv_config_iscsi_parameters);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_config_boot_parameters : " UH_FMT "\n", ptr_struct->nv_config_boot_parameters);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_vpi_force_mode : " UH_FMT "\n", ptr_struct->default_vpi_force_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_vpi_xfi_mode : " UH_FMT "\n", ptr_struct->default_vpi_xfi_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "default_vpi_phy_type : " UH_FMT "\n", ptr_struct->default_vpi_phy_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_boot_to_target : " UH_FMT "\n", ptr_struct->iscsi_boot_to_target);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_vlan_en        : " UH_FMT "\n", ptr_struct->iscsi_vlan_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_tcp_timestamps_en : " UH_FMT "\n", ptr_struct->iscsi_tcp_timestamps_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_chap_mutual_auth_en : " UH_FMT "\n", ptr_struct->iscsi_chap_mutual_auth_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_chap_auth_en   : " UH_FMT "\n", ptr_struct->iscsi_chap_auth_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_dhcp_params_en : " UH_FMT "\n", ptr_struct->iscsi_dhcp_params_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_ipv4_dhcp_en   : " UH_FMT "\n", ptr_struct->iscsi_ipv4_dhcp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_lun_busy_retry_cnt : " UH_FMT "\n", ptr_struct->iscsi_lun_busy_retry_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_link_up_delay_time : " UH_FMT "\n", ptr_struct->iscsi_link_up_delay_time);
}

unsigned int tools_open_query_def_params_per_port_size(void)
{
	return TOOLS_OPEN_QUERY_DEF_PARAMS_PER_PORT_SIZE;
}

void tools_open_query_def_params_per_port_dump(const struct tools_open_query_def_params_per_port *ptr_struct, FILE *fd)
{
	tools_open_query_def_params_per_port_print(ptr_struct, fd, 0);
}

void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_mnv_cfg_pack(&(ptr_struct->MNVReg), ptr_buff);
}

void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_mnv_cfg_unpack(&(ptr_struct->MNVReg), ptr_buff);
}

void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_access_registers ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MNVReg:\n");
	tools_open_mnv_cfg_print(&(ptr_struct->MNVReg), fd, indent_level + 1);
}

unsigned int tools_open_access_registers_size(void)
{
	return TOOLS_OPEN_ACCESS_REGISTERS_SIZE;
}

void tools_open_access_registers_dump(const union tools_open_access_registers *ptr_struct, FILE *fd)
{
	tools_open_access_registers_print(ptr_struct, fd, 0);
}

void tools_open_aux_img_data_pack(const union tools_open_aux_img_data *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_aux_tlv_pack(&(ptr_struct->aux_tlv), ptr_buff);
}

void tools_open_aux_img_data_unpack(union tools_open_aux_img_data *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_aux_tlv_unpack(&(ptr_struct->aux_tlv), ptr_buff);
}

void tools_open_aux_img_data_print(const union tools_open_aux_img_data *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_aux_img_data ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aux_tlv:\n");
	tools_open_aux_tlv_print(&(ptr_struct->aux_tlv), fd, indent_level + 1);
}

unsigned int tools_open_aux_img_data_size(void)
{
	return TOOLS_OPEN_AUX_IMG_DATA_SIZE;
}

void tools_open_aux_img_data_dump(const union tools_open_aux_img_data *ptr_struct, FILE *fd)
{
	tools_open_aux_img_data_print(ptr_struct, fd, 0);
}

void tools_open_hcr_cmds_pack(const union tools_open_hcr_cmds *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_query_def_params_per_port_pack(&(ptr_struct->query_def_params_per_port), ptr_buff);
}

void tools_open_hcr_cmds_unpack(union tools_open_hcr_cmds *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_query_def_params_per_port_unpack(&(ptr_struct->query_def_params_per_port), ptr_buff);
}

void tools_open_hcr_cmds_print(const union tools_open_hcr_cmds *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_hcr_cmds ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_def_params_global:\n");
	tools_open_query_def_params_global_print(&(ptr_struct->query_def_params_global), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_def_params_per_port:\n");
	tools_open_query_def_params_per_port_print(&(ptr_struct->query_def_params_per_port), fd, indent_level + 1);
}

unsigned int tools_open_hcr_cmds_size(void)
{
	return TOOLS_OPEN_HCR_CMDS_SIZE;
}

void tools_open_hcr_cmds_dump(const union tools_open_hcr_cmds *ptr_struct, FILE *fd)
{
	tools_open_hcr_cmds_print(ptr_struct, fd, 0);
}

void tools_open_mcdd_descriptor_pack(const struct tools_open_mcdd_descriptor *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->reserved1);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved2);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data_page_phys_addr_msb);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data_page_phys_addr_lsb);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mailbox_page_phys_addr_msb);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mailbox_page_phys_addr_lsb);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->reserved3);
}

void tools_open_mcdd_descriptor_unpack(struct tools_open_mcdd_descriptor *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 32;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->reserved1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->reserved2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->data_page_phys_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->data_page_phys_addr_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->mailbox_page_phys_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->mailbox_page_phys_addr_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 272;
	ptr_struct->error = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 256;
	ptr_struct->reserved3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tools_open_mcdd_descriptor_print(const struct tools_open_mcdd_descriptor *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mcdd_descriptor ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " UH_FMT "\n", ptr_struct->reserved1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved2            : " U32H_FMT "\n", ptr_struct->reserved2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_page_phys_addr_msb : " U32H_FMT "\n", ptr_struct->data_page_phys_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_page_phys_addr_lsb : " U32H_FMT "\n", ptr_struct->data_page_phys_addr_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mailbox_page_phys_addr_msb : " U32H_FMT "\n", ptr_struct->mailbox_page_phys_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mailbox_page_phys_addr_lsb : " U32H_FMT "\n", ptr_struct->mailbox_page_phys_addr_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error                : " UH_FMT "\n", ptr_struct->error);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved3            : " UH_FMT "\n", ptr_struct->reserved3);
}

unsigned int tools_open_mcdd_descriptor_size(void)
{
	return TOOLS_OPEN_MCDD_DESCRIPTOR_SIZE;
}

void tools_open_mcdd_descriptor_dump(const struct tools_open_mcdd_descriptor *ptr_struct, FILE *fd)
{
	tools_open_mcdd_descriptor_print(ptr_struct, fd, 0);
}

void tools_open_mcdd_reg_pack(const struct tools_open_mcdd_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->reserved1);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved2);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data_page_phys_addr_msb);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data_page_phys_addr_lsb);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mailbox_page_phys_addr_msb);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mailbox_page_phys_addr_lsb);
}

void tools_open_mcdd_reg_unpack(struct tools_open_mcdd_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 32;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->reserved1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->reserved2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->data_page_phys_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->data_page_phys_addr_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->mailbox_page_phys_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->mailbox_page_phys_addr_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_mcdd_reg_print(const struct tools_open_mcdd_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mcdd_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "offset               : " U32H_FMT "\n", ptr_struct->offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " UH_FMT "\n", ptr_struct->reserved1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved2            : " U32H_FMT "\n", ptr_struct->reserved2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_page_phys_addr_msb : " U32H_FMT "\n", ptr_struct->data_page_phys_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_page_phys_addr_lsb : " U32H_FMT "\n", ptr_struct->data_page_phys_addr_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mailbox_page_phys_addr_msb : " U32H_FMT "\n", ptr_struct->mailbox_page_phys_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mailbox_page_phys_addr_lsb : " U32H_FMT "\n", ptr_struct->mailbox_page_phys_addr_lsb);
}

unsigned int tools_open_mcdd_reg_size(void)
{
	return TOOLS_OPEN_MCDD_REG_SIZE;
}

void tools_open_mcdd_reg_dump(const struct tools_open_mcdd_reg *ptr_struct, FILE *fd)
{
	tools_open_mcdd_reg_print(ptr_struct, fd, 0);
}

void tools_open_mirc_reg_pack(const struct tools_open_mirc_reg *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status_code);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved);
}

void tools_open_mirc_reg_unpack(struct tools_open_mirc_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->status_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->reserved = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_mirc_reg_print(const struct tools_open_mirc_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mirc_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status_code          : " UH_FMT "\n", ptr_struct->status_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " U32H_FMT "\n", ptr_struct->reserved);
}

unsigned int tools_open_mirc_reg_size(void)
{
	return TOOLS_OPEN_MIRC_REG_SIZE;
}

void tools_open_mirc_reg_dump(const struct tools_open_mirc_reg *ptr_struct, FILE *fd)
{
	tools_open_mirc_reg_print(ptr_struct, fd, 0);
}

void tools_open_misc_structs_pack(const union tools_open_misc_structs *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_image_info_pack(&(ptr_struct->image_info), ptr_buff);
}

void tools_open_misc_structs_unpack(union tools_open_misc_structs *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_image_info_unpack(&(ptr_struct->image_info), ptr_buff);
}

void tools_open_misc_structs_print(const union tools_open_misc_structs *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_misc_structs ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info:\n");
	tools_open_image_info_print(&(ptr_struct->image_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfg_info:\n");
	tools_open_mfg_info_print(&(ptr_struct->mfg_info), fd, indent_level + 1);
}

unsigned int tools_open_misc_structs_size(void)
{
	return TOOLS_OPEN_MISC_STRUCTS_SIZE;
}

void tools_open_misc_structs_dump(const union tools_open_misc_structs *ptr_struct, FILE *fd)
{
	tools_open_misc_structs_print(ptr_struct, fd, 0);
}

void tools_open_nv_cfg_pack(const union tools_open_nv_cfg *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_nv_base_mac_guid_pack(&(ptr_struct->nv_base_mac_guid), ptr_buff);
}

void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_nv_base_mac_guid_unpack(&(ptr_struct->nv_base_mac_guid), ptr_buff);
}

void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_cfg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_base_mac_guid:\n");
	tools_open_nv_base_mac_guid_print(&(ptr_struct->nv_base_mac_guid), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_base_mac_guid_cap:\n");
	tools_open_nv_base_mac_guid_cap_print(&(ptr_struct->nv_base_mac_guid_cap), fd, indent_level + 1);
}

unsigned int tools_open_nv_cfg_size(void)
{
	return TOOLS_OPEN_NV_CFG_SIZE;
}

void tools_open_nv_cfg_dump(const union tools_open_nv_cfg *ptr_struct, FILE *fd)
{
	tools_open_nv_cfg_print(ptr_struct, fd, 0);
}

void tools_open_tools_open_pack(const union tools_open_tools_open *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_misc_structs_pack(&(ptr_struct->MiscStructs), ptr_buff);
}

void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_misc_structs_unpack(&(ptr_struct->MiscStructs), ptr_buff);
}

void tools_open_tools_open_print(const union tools_open_tools_open *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_tools_open ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "NVConfig:\n");
	tools_open_nv_cfg_print(&(ptr_struct->NVConfig), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "AceessRegisters:\n");
	tools_open_access_registers_print(&(ptr_struct->AceessRegisters), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "HcrCmds:\n");
	tools_open_hcr_cmds_print(&(ptr_struct->HcrCmds), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "AuxImgData:\n");
	tools_open_aux_img_data_print(&(ptr_struct->AuxImgData), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MiscStructs:\n");
	tools_open_misc_structs_print(&(ptr_struct->MiscStructs), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcdd_reg:\n");
	tools_open_mcdd_reg_print(&(ptr_struct->mcdd_reg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcdd_descriptor:\n");
	tools_open_mcdd_descriptor_print(&(ptr_struct->mcdd_descriptor), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mirc_reg:\n");
	tools_open_mirc_reg_print(&(ptr_struct->mirc_reg), fd, indent_level + 1);
}

unsigned int tools_open_tools_open_size(void)
{
	return TOOLS_OPEN_TOOLS_OPEN_SIZE;
}

void tools_open_tools_open_dump(const union tools_open_tools_open *ptr_struct, FILE *fd)
{
	tools_open_tools_open_print(ptr_struct, fd, 0);
}

