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
 

/***
         *** This file was generated at "2020-10-08 16:57:28"
         *** by:
         ***    > /mswg/release/tools/a-me/nightly/1.0.122/a-me-1.0.122_2019-07-14/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_
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

void tools_open_cap_mask_pack(const struct tools_open_cap_mask *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_sm);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_notice_sup);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_trap_sup);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_optional_ipd_sup);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_automatic_migration_sup);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_sl_mapping_sup);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_mkey_nvram);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_pkey_nvram);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_led_info_sup);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_sm_disabled);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_system_image_guid_sup);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_pkey_switch_external_port_trap_sup);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_extended_speed_sup);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_communication_management_sup);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_snmp_tunneling_sup);
	offset = 13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_reinit_sup);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_device_management_sup);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_vendor_class_sup);
	offset = 10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_dr_notice_sup);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_capability_mask_notice_sup);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_boot_management_sup);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_link_round_trip_latency_sup);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_client_reregistration_sup);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_other_local_changes_notice_supported);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_link_speed_width_pairs_table_supported);
}

void tools_open_cap_mask_unpack(struct tools_open_cap_mask *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->is_sm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->is_notice_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 28;
	ptr_struct->is_trap_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 27;
	ptr_struct->is_optional_ipd_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->is_automatic_migration_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->is_sl_mapping_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->is_mkey_nvram = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 23;
	ptr_struct->is_pkey_nvram = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->is_led_info_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 21;
	ptr_struct->is_sm_disabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->is_system_image_guid_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->is_pkey_switch_external_port_trap_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->is_extended_speed_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 15;
	ptr_struct->is_communication_management_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 14;
	ptr_struct->is_snmp_tunneling_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 13;
	ptr_struct->is_reinit_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 12;
	ptr_struct->is_device_management_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 11;
	ptr_struct->is_vendor_class_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 10;
	ptr_struct->is_dr_notice_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 9;
	ptr_struct->is_capability_mask_notice_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->is_boot_management_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 7;
	ptr_struct->is_link_round_trip_latency_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->is_client_reregistration_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->is_other_local_changes_notice_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->is_link_speed_width_pairs_table_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_cap_mask_print(const struct tools_open_cap_mask *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_cap_mask ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_sm                : " UH_FMT "\n", ptr_struct->is_sm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_notice_sup        : " UH_FMT "\n", ptr_struct->is_notice_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_trap_sup          : " UH_FMT "\n", ptr_struct->is_trap_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_optional_ipd_sup  : " UH_FMT "\n", ptr_struct->is_optional_ipd_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_automatic_migration_sup : " UH_FMT "\n", ptr_struct->is_automatic_migration_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_sl_mapping_sup    : " UH_FMT "\n", ptr_struct->is_sl_mapping_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_mkey_nvram        : " UH_FMT "\n", ptr_struct->is_mkey_nvram);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_pkey_nvram        : " UH_FMT "\n", ptr_struct->is_pkey_nvram);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_led_info_sup      : " UH_FMT "\n", ptr_struct->is_led_info_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_sm_disabled       : " UH_FMT "\n", ptr_struct->is_sm_disabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_system_image_guid_sup : " UH_FMT "\n", ptr_struct->is_system_image_guid_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_pkey_switch_external_port_trap_sup : " UH_FMT "\n", ptr_struct->is_pkey_switch_external_port_trap_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_extended_speed_sup : " UH_FMT "\n", ptr_struct->is_extended_speed_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_communication_management_sup : " UH_FMT "\n", ptr_struct->is_communication_management_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_snmp_tunneling_sup : " UH_FMT "\n", ptr_struct->is_snmp_tunneling_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_reinit_sup        : " UH_FMT "\n", ptr_struct->is_reinit_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_device_management_sup : " UH_FMT "\n", ptr_struct->is_device_management_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_vendor_class_sup  : " UH_FMT "\n", ptr_struct->is_vendor_class_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_dr_notice_sup     : " UH_FMT "\n", ptr_struct->is_dr_notice_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_capability_mask_notice_sup : " UH_FMT "\n", ptr_struct->is_capability_mask_notice_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_boot_management_sup : " UH_FMT "\n", ptr_struct->is_boot_management_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_link_round_trip_latency_sup : " UH_FMT "\n", ptr_struct->is_link_round_trip_latency_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_client_reregistration_sup : " UH_FMT "\n", ptr_struct->is_client_reregistration_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_other_local_changes_notice_supported : " UH_FMT "\n", ptr_struct->is_other_local_changes_notice_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_link_speed_width_pairs_table_supported : " UH_FMT "\n", ptr_struct->is_link_speed_width_pairs_table_supported);
}

unsigned int tools_open_cap_mask_size(void)
{
	return TOOLS_OPEN_CAP_MASK_SIZE;
}

void tools_open_cap_mask_dump(const struct tools_open_cap_mask *ptr_struct, FILE *fd)
{
	tools_open_cap_mask_print(ptr_struct, fd, 0);
}

void tools_open_capability_mask_smp_pack(const struct tools_open_capability_mask_smp *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsPrivateLinearForwardingSupported);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsAdaptiveRoutingSupported);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsAdaptiveRoutingRev1Supported);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsRemotePortMirroringSupported);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsTemperatureSensingSupported);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsConfigSpaceAccessSupported);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsCableInfoSupported);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsSMPEyeOpenSupported);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsLossyVLConfigSupported);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsExtendedPortInfoSupported);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsAccessRegisterSupported);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsInterProcessCommunicationSupported);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsPortSLToPrivateLFTMapSupported);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsExtendedSwitchInfoSupported);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->IsASlaveVirtualSwitch);
}

void tools_open_capability_mask_smp_unpack(struct tools_open_capability_mask_smp *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->IsPrivateLinearForwardingSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->IsAdaptiveRoutingSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->IsAdaptiveRoutingRev1Supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 28;
	ptr_struct->IsRemotePortMirroringSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 27;
	ptr_struct->IsTemperatureSensingSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->IsConfigSpaceAccessSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->IsCableInfoSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->IsSMPEyeOpenSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 23;
	ptr_struct->IsLossyVLConfigSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->IsExtendedPortInfoSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 21;
	ptr_struct->IsAccessRegisterSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->IsInterProcessCommunicationSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->IsPortSLToPrivateLFTMapSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->IsExtendedSwitchInfoSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->IsASlaveVirtualSwitch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_capability_mask_smp_print(const struct tools_open_capability_mask_smp *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_capability_mask_smp ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsPrivateLinearForwardingSupported : " UH_FMT "\n", ptr_struct->IsPrivateLinearForwardingSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsAdaptiveRoutingSupported : " UH_FMT "\n", ptr_struct->IsAdaptiveRoutingSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsAdaptiveRoutingRev1Supported : " UH_FMT "\n", ptr_struct->IsAdaptiveRoutingRev1Supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsRemotePortMirroringSupported : " UH_FMT "\n", ptr_struct->IsRemotePortMirroringSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsTemperatureSensingSupported : " UH_FMT "\n", ptr_struct->IsTemperatureSensingSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsConfigSpaceAccessSupported : " UH_FMT "\n", ptr_struct->IsConfigSpaceAccessSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsCableInfoSupported : " UH_FMT "\n", ptr_struct->IsCableInfoSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsSMPEyeOpenSupported : " UH_FMT "\n", ptr_struct->IsSMPEyeOpenSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsLossyVLConfigSupported : " UH_FMT "\n", ptr_struct->IsLossyVLConfigSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsExtendedPortInfoSupported : " UH_FMT "\n", ptr_struct->IsExtendedPortInfoSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsAccessRegisterSupported : " UH_FMT "\n", ptr_struct->IsAccessRegisterSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsInterProcessCommunicationSupported : " UH_FMT "\n", ptr_struct->IsInterProcessCommunicationSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsPortSLToPrivateLFTMapSupported : " UH_FMT "\n", ptr_struct->IsPortSLToPrivateLFTMapSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsExtendedSwitchInfoSupported : " UH_FMT "\n", ptr_struct->IsExtendedSwitchInfoSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IsASlaveVirtualSwitch : " UH_FMT "\n", ptr_struct->IsASlaveVirtualSwitch);
}

unsigned int tools_open_capability_mask_smp_size(void)
{
	return TOOLS_OPEN_CAPABILITY_MASK_SMP_SIZE;
}

void tools_open_capability_mask_smp_dump(const struct tools_open_capability_mask_smp *ptr_struct, FILE *fd)
{
	tools_open_capability_mask_smp_print(ptr_struct, fd, 0);
}

void tools_open_fw_info_pack(const struct tools_open_fw_info *ptr_struct, u_int8_t *ptr_buff)
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
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secure_fw);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_fw);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->debug_fw);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev_fw);
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
}

void tools_open_fw_info_unpack(struct tools_open_fw_info *ptr_struct, const u_int8_t *ptr_buff)
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
	ptr_struct->secure_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->signed_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->debug_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->dev_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
}

void tools_open_fw_info_print(const struct tools_open_fw_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_fw_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_minor            : " UH_FMT "\n", ptr_struct->sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secure_fw            : " UH_FMT "\n", ptr_struct->secure_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_fw            : " UH_FMT "\n", ptr_struct->signed_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug_fw             : " UH_FMT "\n", ptr_struct->debug_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_fw               : " UH_FMT "\n", ptr_struct->dev_fw);
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
}

unsigned int tools_open_fw_info_size(void)
{
	return TOOLS_OPEN_FW_INFO_SIZE;
}

void tools_open_fw_info_dump(const struct tools_open_fw_info *ptr_struct, FILE *fd)
{
	tools_open_fw_info_print(ptr_struct, fd, 0);
}

void tools_open_hw_info_pack(const struct tools_open_hw_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_hw_revision);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_dev_id);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->manufacturing_base_mac_47_32);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->manufacturing_base_mac_31_0);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uptime);
}

void tools_open_hw_info_unpack(struct tools_open_hw_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->device_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->device_hw_revision = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 59;
	ptr_struct->pvs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->hw_dev_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->manufacturing_base_mac_47_32 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->manufacturing_base_mac_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->uptime = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_hw_info_print(const struct tools_open_hw_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_hw_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_id            : " UH_FMT "\n", ptr_struct->device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_hw_revision   : " UH_FMT "\n", ptr_struct->device_hw_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs                  : " UH_FMT "\n", ptr_struct->pvs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_dev_id            : " UH_FMT "\n", ptr_struct->hw_dev_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_47_32 : " UH_FMT "\n", ptr_struct->manufacturing_base_mac_47_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_31_0 : " U32H_FMT "\n", ptr_struct->manufacturing_base_mac_31_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uptime               : " U32H_FMT "\n", ptr_struct->uptime);
}

unsigned int tools_open_hw_info_size(void)
{
	return TOOLS_OPEN_HW_INFO_SIZE;
}

void tools_open_hw_info_dump(const struct tools_open_hw_info *ptr_struct, FILE *fd)
{
	tools_open_hw_info_print(ptr_struct, fd, 0);
}

void tools_open_nv_hdr_pack(const struct tools_open_nv_hdr *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_nv_hdr_unpack(struct tools_open_nv_hdr *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_nv_hdr_print(const struct tools_open_nv_hdr *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_hdr ========\n");

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

unsigned int tools_open_nv_hdr_size(void)
{
	return TOOLS_OPEN_NV_HDR_SIZE;
}

void tools_open_nv_hdr_dump(const struct tools_open_nv_hdr *ptr_struct, FILE *fd)
{
	tools_open_nv_hdr_print(ptr_struct, fd, 0);
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

void tools_open_pmdio_addr_data_pack(const struct tools_open_pmdio_addr_data *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->addr);
}

void tools_open_pmdio_addr_data_unpack(struct tools_open_pmdio_addr_data *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->data = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->addr = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tools_open_pmdio_addr_data_print(const struct tools_open_pmdio_addr_data *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_pmdio_addr_data ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data                 : " UH_FMT "\n", ptr_struct->data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "addr                 : " UH_FMT "\n", ptr_struct->addr);
}

unsigned int tools_open_pmdio_addr_data_size(void)
{
	return TOOLS_OPEN_PMDIO_ADDR_DATA_SIZE;
}

void tools_open_pmdio_addr_data_dump(const struct tools_open_pmdio_addr_data *ptr_struct, FILE *fd)
{
	tools_open_pmdio_addr_data_print(ptr_struct, fd, 0);
}

void tools_open_sw_info_pack(const struct tools_open_sw_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->subminor);
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
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom0_version);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom1_version);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom2_version);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom3_version);
}

void tools_open_sw_info_unpack(struct tools_open_sw_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->subminor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
	ptr_struct->rom0_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->rom1_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->rom2_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->rom3_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_sw_info_print(const struct tools_open_sw_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_sw_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subminor             : " UH_FMT "\n", ptr_struct->subminor);
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
	fprintf(fd, "rom0_version         : " U32H_FMT "\n", ptr_struct->rom0_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_version         : " U32H_FMT "\n", ptr_struct->rom1_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_version         : " U32H_FMT "\n", ptr_struct->rom2_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_version         : " U32H_FMT "\n", ptr_struct->rom3_version);
}

unsigned int tools_open_sw_info_size(void)
{
	return TOOLS_OPEN_SW_INFO_SIZE;
}

void tools_open_sw_info_dump(const struct tools_open_sw_info *ptr_struct, FILE *fd)
{
	tools_open_sw_info_print(ptr_struct, fd, 0);
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

void tools_open_extended_ib_port_info_pack(const struct tools_open_extended_ib_port_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->StateChangeEnable);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->LinkSpeedSupported);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->LinkSpeedEnabled);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->LinkSpeedActive);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->CapMask);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ActiveCell);
}

void tools_open_extended_ib_port_info_unpack(struct tools_open_extended_ib_port_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->StateChangeEnable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->LinkSpeedSupported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->LinkSpeedEnabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->LinkSpeedActive = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->CapMask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->ActiveCell = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_extended_ib_port_info_print(const struct tools_open_extended_ib_port_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_extended_ib_port_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "StateChangeEnable    : " UH_FMT "\n", ptr_struct->StateChangeEnable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "LinkSpeedSupported   : " UH_FMT "\n", ptr_struct->LinkSpeedSupported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "LinkSpeedEnabled     : " UH_FMT "\n", ptr_struct->LinkSpeedEnabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "LinkSpeedActive      : " UH_FMT "\n", ptr_struct->LinkSpeedActive);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "CapMask              : " UH_FMT "\n", ptr_struct->CapMask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ActiveCell           : " UH_FMT "\n", ptr_struct->ActiveCell);
}

unsigned int tools_open_extended_ib_port_info_size(void)
{
	return TOOLS_OPEN_EXTENDED_IB_PORT_INFO_SIZE;
}

void tools_open_extended_ib_port_info_dump(const struct tools_open_extended_ib_port_info *ptr_struct, FILE *fd)
{
	tools_open_extended_ib_port_info_print(ptr_struct, fd, 0);
}

void tools_open_ib_port_info_pack(const struct tools_open_ib_port_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->m_key_hi);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->m_key_lo);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->gid_prefix_hi);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->gid_prefix_lo);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->master_sm_lid);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lid);
	offset = 160;
	tools_open_cap_mask_pack(&(ptr_struct->cap_mask), ptr_buff + offset / 8);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->m_key_lease);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->diag_code);
	offset = 248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_act);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_sup);
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_ena);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port_num);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_speed_ena);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_speed_act);
	offset = 277;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lmc);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->m_key_protec);
	offset = 268;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->down_def_state);
	offset = 264;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_state);
	offset = 260;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_state);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_speed_sup);
	offset = 312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vl_arb_high_cap);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vl_high_limit);
	offset = 300;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->init_type);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vl_cap);
	offset = 292;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->master_sm_sl);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->neighbor_mtu);
	offset = 351;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->filter_raw_out);
	offset = 350;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->filter_raw_in);
	offset = 349;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->Part_enforce_out);
	offset = 348;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->Part_enforce_in);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->operational_vl);
	offset = 339;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->HOQLife);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->vl_stall_cnt);
	offset = 332;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mtu_cap);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vl_arb_low_cap);
	offset = 368;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->p_key_violations);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->m_key_violations);
	offset = 411;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->subnet_to);
	offset = 408;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->client_reregister);
	offset = 400;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->guid_cap);
	offset = 384;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->q_key_violations);
	offset = 428;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->overrun_err);
	offset = 424;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->local_phy_err);
	offset = 419;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->resp_time_value);
	offset = 507;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->link_speed_ext_ena);
	offset = 500;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_speed_ext_sup);
	offset = 496;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_speed_ext_act);
}

void tools_open_ib_port_info_unpack(struct tools_open_ib_port_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->m_key_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->m_key_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->gid_prefix_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->gid_prefix_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->master_sm_lid = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->lid = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	tools_open_cap_mask_unpack(&(ptr_struct->cap_mask), ptr_buff + offset / 8);
	offset = 208;
	ptr_struct->m_key_lease = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->diag_code = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 248;
	ptr_struct->link_width_act = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 240;
	ptr_struct->link_width_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 232;
	ptr_struct->link_width_ena = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->local_port_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 284;
	ptr_struct->link_speed_ena = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->link_speed_act = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 277;
	ptr_struct->lmc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 272;
	ptr_struct->m_key_protec = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 268;
	ptr_struct->down_def_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 264;
	ptr_struct->phy_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 260;
	ptr_struct->port_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->link_speed_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 312;
	ptr_struct->vl_arb_high_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 304;
	ptr_struct->vl_high_limit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 300;
	ptr_struct->init_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->vl_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 292;
	ptr_struct->master_sm_sl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->neighbor_mtu = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 351;
	ptr_struct->filter_raw_out = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 350;
	ptr_struct->filter_raw_in = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 349;
	ptr_struct->Part_enforce_out = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 348;
	ptr_struct->Part_enforce_in = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 344;
	ptr_struct->operational_vl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 339;
	ptr_struct->HOQLife = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 336;
	ptr_struct->vl_stall_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 332;
	ptr_struct->mtu_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->vl_arb_low_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 368;
	ptr_struct->p_key_violations = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 352;
	ptr_struct->m_key_violations = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 411;
	ptr_struct->subnet_to = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 408;
	ptr_struct->client_reregister = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 400;
	ptr_struct->guid_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 384;
	ptr_struct->q_key_violations = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 428;
	ptr_struct->overrun_err = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 424;
	ptr_struct->local_phy_err = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 419;
	ptr_struct->resp_time_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 507;
	ptr_struct->link_speed_ext_ena = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 500;
	ptr_struct->link_speed_ext_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 496;
	ptr_struct->link_speed_ext_act = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_ib_port_info_print(const struct tools_open_ib_port_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_ib_port_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_key_hi             : " U32H_FMT "\n", ptr_struct->m_key_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_key_lo             : " U32H_FMT "\n", ptr_struct->m_key_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gid_prefix_hi        : " U32H_FMT "\n", ptr_struct->gid_prefix_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gid_prefix_lo        : " U32H_FMT "\n", ptr_struct->gid_prefix_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "master_sm_lid        : " UH_FMT "\n", ptr_struct->master_sm_lid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lid                  : " UH_FMT "\n", ptr_struct->lid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_mask:\n");
	tools_open_cap_mask_print(&(ptr_struct->cap_mask), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_key_lease          : " UH_FMT "\n", ptr_struct->m_key_lease);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "diag_code            : " UH_FMT "\n", ptr_struct->diag_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_act       : " UH_FMT "\n", ptr_struct->link_width_act);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_sup       : " UH_FMT "\n", ptr_struct->link_width_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_ena       : " UH_FMT "\n", ptr_struct->link_width_ena);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port_num       : " UH_FMT "\n", ptr_struct->local_port_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_ena       : " UH_FMT "\n", ptr_struct->link_speed_ena);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_act       : " UH_FMT "\n", ptr_struct->link_speed_act);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lmc                  : " UH_FMT "\n", ptr_struct->lmc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_key_protec         : " UH_FMT "\n", ptr_struct->m_key_protec);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_def_state       : " UH_FMT "\n", ptr_struct->down_def_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_state            : " UH_FMT "\n", ptr_struct->phy_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_state           : " UH_FMT "\n", ptr_struct->port_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_sup       : " UH_FMT "\n", ptr_struct->link_speed_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_arb_high_cap      : " UH_FMT "\n", ptr_struct->vl_arb_high_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_high_limit        : " UH_FMT "\n", ptr_struct->vl_high_limit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "init_type            : " UH_FMT "\n", ptr_struct->init_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_cap               : " UH_FMT "\n", ptr_struct->vl_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "master_sm_sl         : " UH_FMT "\n", ptr_struct->master_sm_sl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "neighbor_mtu         : " UH_FMT "\n", ptr_struct->neighbor_mtu);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "filter_raw_out       : " UH_FMT "\n", ptr_struct->filter_raw_out);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "filter_raw_in        : " UH_FMT "\n", ptr_struct->filter_raw_in);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Part_enforce_out     : " UH_FMT "\n", ptr_struct->Part_enforce_out);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Part_enforce_in      : " UH_FMT "\n", ptr_struct->Part_enforce_in);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operational_vl       : " UH_FMT "\n", ptr_struct->operational_vl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "HOQLife              : " UH_FMT "\n", ptr_struct->HOQLife);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_stall_cnt         : " UH_FMT "\n", ptr_struct->vl_stall_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtu_cap              : " UH_FMT "\n", ptr_struct->mtu_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_arb_low_cap       : " UH_FMT "\n", ptr_struct->vl_arb_low_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p_key_violations     : " UH_FMT "\n", ptr_struct->p_key_violations);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_key_violations     : " UH_FMT "\n", ptr_struct->m_key_violations);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subnet_to            : " UH_FMT "\n", ptr_struct->subnet_to);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "client_reregister    : " UH_FMT "\n", ptr_struct->client_reregister);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guid_cap             : " UH_FMT "\n", ptr_struct->guid_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "q_key_violations     : " UH_FMT "\n", ptr_struct->q_key_violations);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "overrun_err          : " UH_FMT "\n", ptr_struct->overrun_err);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_phy_err        : " UH_FMT "\n", ptr_struct->local_phy_err);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resp_time_value      : " UH_FMT "\n", ptr_struct->resp_time_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_ext_ena   : " UH_FMT "\n", ptr_struct->link_speed_ext_ena);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_ext_sup   : " UH_FMT "\n", ptr_struct->link_speed_ext_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_ext_act   : " UH_FMT "\n", ptr_struct->link_speed_ext_act);
}

unsigned int tools_open_ib_port_info_size(void)
{
	return TOOLS_OPEN_IB_PORT_INFO_SIZE;
}

void tools_open_ib_port_info_dump(const struct tools_open_ib_port_info *ptr_struct, FILE *fd)
{
	tools_open_ib_port_info_print(ptr_struct, fd, 0);
}

void tools_open_mcam_pack(const struct tools_open_mcam *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->feature_group);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 576, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(344, 8, i, 576, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mng_feature_cap_mask[i]);
	}
}

void tools_open_mcam_unpack(struct tools_open_mcam *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->feature_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 576, 1);
		ptr_struct->mng_access_reg_cap_mask[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(344, 8, i, 576, 1);
		ptr_struct->mng_feature_cap_mask[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_mcam_print(const struct tools_open_mcam *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mcam ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : " UH_FMT "\n", ptr_struct->access_reg_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "feature_group        : " UH_FMT "\n", ptr_struct->feature_group);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_access_reg_cap_mask_%03d : " UH_FMT "\n", i, ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_feature_cap_mask_%03d : " UH_FMT "\n", i, ptr_struct->mng_feature_cap_mask[i]);
	}
}

unsigned int tools_open_mcam_size(void)
{
	return TOOLS_OPEN_MCAM_SIZE;
}

void tools_open_mcam_dump(const struct tools_open_mcam *ptr_struct, FILE *fd)
{
	tools_open_mcam_print(ptr_struct, fd, 0);
}

void tools_open_mfmc_pack(const struct tools_open_mfmc *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_mfmc_unpack(struct tools_open_mfmc *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_mfmc_print(const struct tools_open_mfmc *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mfmc ========\n");

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

unsigned int tools_open_mfmc_size(void)
{
	return TOOLS_OPEN_MFMC_SIZE;
}

void tools_open_mfmc_dump(const struct tools_open_mfmc *ptr_struct, FILE *fd)
{
	tools_open_mfmc_print(ptr_struct, fd, 0);
}

void tools_open_mfpa_pack(const struct tools_open_mfpa *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);
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
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_allignment);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_size);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->capability_mask);
}

void tools_open_mfpa_unpack(struct tools_open_mfpa *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	ptr_struct->block_allignment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 192;
	ptr_struct->block_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->capability_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_mfpa_print(const struct tools_open_mfpa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mfpa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
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
	fprintf(fd, "block_allignment     : " UH_FMT "\n", ptr_struct->block_allignment);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_size           : " UH_FMT "\n", ptr_struct->block_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_mask      : " U32H_FMT "\n", ptr_struct->capability_mask);
}

unsigned int tools_open_mfpa_size(void)
{
	return TOOLS_OPEN_MFPA_SIZE;
}

void tools_open_mfpa_dump(const struct tools_open_mfpa *ptr_struct, FILE *fd)
{
	tools_open_mfpa_print(ptr_struct, fd, 0);
}

void tools_open_mgir_pack(const struct tools_open_mgir *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_hw_info_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	tools_open_fw_info_pack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	tools_open_sw_info_pack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
}

void tools_open_mgir_unpack(struct tools_open_mgir *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_hw_info_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	tools_open_fw_info_unpack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	tools_open_sw_info_unpack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
}

void tools_open_mgir_print(const struct tools_open_mgir *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mgir ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	tools_open_hw_info_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info:\n");
	tools_open_fw_info_print(&(ptr_struct->fw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_info:\n");
	tools_open_sw_info_print(&(ptr_struct->sw_info), fd, indent_level + 1);
}

unsigned int tools_open_mgir_size(void)
{
	return TOOLS_OPEN_MGIR_SIZE;
}

void tools_open_mgir_dump(const struct tools_open_mgir *ptr_struct, FILE *fd)
{
	tools_open_mgir_print(ptr_struct, fd, 0);
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

void tools_open_mnva_pack(const struct tools_open_mnva *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 2048, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}
}

void tools_open_mnva_unpack(struct tools_open_mnva *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(88, 8, i, 2048, 1);
		ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_mnva_print(const struct tools_open_mnva *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnva ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 128; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " UH_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int tools_open_mnva_size(void)
{
	return TOOLS_OPEN_MNVA_SIZE;
}

void tools_open_mnva_dump(const struct tools_open_mnva *ptr_struct, FILE *fd)
{
	tools_open_mnva_print(ptr_struct, fd, 0);
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

void tools_open_mnvi_pack(const struct tools_open_mnvi *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_mnvi_unpack(struct tools_open_mnvi *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_mnvi_print(const struct tools_open_mnvi *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnvi ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
}

unsigned int tools_open_mnvi_size(void)
{
	return TOOLS_OPEN_MNVI_SIZE;
}

void tools_open_mnvi_dump(const struct tools_open_mnvi *ptr_struct, FILE *fd)
{
	tools_open_mnvi_print(ptr_struct, fd, 0);
}

void tools_open_mnvia_pack(const struct tools_open_mnvia *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_mnvia_unpack(struct tools_open_mnvia *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_mnvia_print(const struct tools_open_mnvia *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnvia ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
}

unsigned int tools_open_mnvia_size(void)
{
	return TOOLS_OPEN_MNVIA_SIZE;
}

void tools_open_mnvia_dump(const struct tools_open_mnvia *ptr_struct, FILE *fd)
{
	tools_open_mnvia_print(ptr_struct, fd, 0);
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

void tools_open_node_info_pack(const struct tools_open_node_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_ports);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node_type);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->class_version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->base_version);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->system_image_guid_hi);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->system_image_guid_lo);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->node_guid_hi);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->node_guid_lo);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_guid_hi);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_guid_lo);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_id);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->partition_cap);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->revision);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->vendor_id);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port_num);
}

void tools_open_node_info_unpack(struct tools_open_node_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->num_of_ports = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->node_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->class_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->base_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->system_image_guid_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->system_image_guid_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->node_guid_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->node_guid_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->port_guid_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->port_guid_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 240;
	ptr_struct->device_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->partition_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 256;
	ptr_struct->revision = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->vendor_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 288;
	ptr_struct->local_port_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_node_info_print(const struct tools_open_node_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_node_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_ports         : " UH_FMT "\n", ptr_struct->num_of_ports);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node_type            : " UH_FMT "\n", ptr_struct->node_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "class_version        : " UH_FMT "\n", ptr_struct->class_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_version         : " UH_FMT "\n", ptr_struct->base_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "system_image_guid_hi : " U32H_FMT "\n", ptr_struct->system_image_guid_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "system_image_guid_lo : " U32H_FMT "\n", ptr_struct->system_image_guid_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node_guid_hi         : " U32H_FMT "\n", ptr_struct->node_guid_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node_guid_lo         : " U32H_FMT "\n", ptr_struct->node_guid_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_guid_hi         : " U32H_FMT "\n", ptr_struct->port_guid_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_guid_lo         : " U32H_FMT "\n", ptr_struct->port_guid_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_id            : " UH_FMT "\n", ptr_struct->device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partition_cap        : " UH_FMT "\n", ptr_struct->partition_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "revision             : " U32H_FMT "\n", ptr_struct->revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vendor_id            : " UH_FMT "\n", ptr_struct->vendor_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port_num       : " UH_FMT "\n", ptr_struct->local_port_num);
}

unsigned int tools_open_node_info_size(void)
{
	return TOOLS_OPEN_NODE_INFO_SIZE;
}

void tools_open_node_info_dump(const struct tools_open_node_info *ptr_struct, FILE *fd)
{
	tools_open_node_info_print(ptr_struct, fd, 0);
}

void tools_open_nvda_pack(const struct tools_open_nvda *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_nvda_unpack(struct tools_open_nvda *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_nvda_print(const struct tools_open_nvda *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nvda ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
	for (i = 0; i < 256; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " UH_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int tools_open_nvda_size(void)
{
	return TOOLS_OPEN_NVDA_SIZE;
}

void tools_open_nvda_dump(const struct tools_open_nvda *ptr_struct, FILE *fd)
{
	tools_open_nvda_print(ptr_struct, fd, 0);
}

void tools_open_nvdi_pack(const struct tools_open_nvdi *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_nvdi_unpack(struct tools_open_nvdi *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset / 8);
}

void tools_open_nvdi_print(const struct tools_open_nvdi *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nvdi ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), fd, indent_level + 1);
}

unsigned int tools_open_nvdi_size(void)
{
	return TOOLS_OPEN_NVDI_SIZE;
}

void tools_open_nvdi_dump(const struct tools_open_nvdi *ptr_struct, FILE *fd)
{
	tools_open_nvdi_print(ptr_struct, fd, 0);
}

void tools_open_nvia_pack(const struct tools_open_nvia *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->target);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->writer_id);
}

void tools_open_nvia_unpack(struct tools_open_nvia *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 23;
	ptr_struct->writer_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void tools_open_nvia_print(const struct tools_open_nvia *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nvia ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "target               : " UH_FMT "\n", ptr_struct->target);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "writer_id            : " UH_FMT "\n", ptr_struct->writer_id);
}

unsigned int tools_open_nvia_size(void)
{
	return TOOLS_OPEN_NVIA_SIZE;
}

void tools_open_nvia_dump(const struct tools_open_nvia *ptr_struct, FILE *fd)
{
	tools_open_nvia_print(ptr_struct, fd, 0);
}

void tools_open_nvqc_pack(const struct tools_open_nvqc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_tlv_type_pack(&(ptr_struct->type), ptr_buff + offset / 8);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_rd);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_wr);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
}

void tools_open_nvqc_unpack(struct tools_open_nvqc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	tools_open_tlv_type_unpack(&(ptr_struct->type), ptr_buff + offset / 8);
	offset = 63;
	ptr_struct->support_rd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->support_wr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_nvqc_print(const struct tools_open_nvqc *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nvqc ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type:\n");
	tools_open_tlv_type_print(&(ptr_struct->type), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "support_rd           : " UH_FMT "\n", ptr_struct->support_rd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "support_wr           : " UH_FMT "\n", ptr_struct->support_wr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
}

unsigned int tools_open_nvqc_size(void)
{
	return TOOLS_OPEN_NVQC_SIZE;
}

void tools_open_nvqc_dump(const struct tools_open_nvqc *ptr_struct, FILE *fd)
{
	tools_open_nvqc_print(ptr_struct, fd, 0);
}

void tools_open_nvqgc_pack(const struct tools_open_nvqgc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->read_factory_settings_support);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nvda_read_current_settings);
}

void tools_open_nvqgc_unpack(struct tools_open_nvqgc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->read_factory_settings_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->nvda_read_current_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_nvqgc_print(const struct tools_open_nvqgc *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nvqgc ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_factory_settings_support : " UH_FMT "\n", ptr_struct->read_factory_settings_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvda_read_current_settings : " UH_FMT "\n", ptr_struct->nvda_read_current_settings);
}

unsigned int tools_open_nvqgc_size(void)
{
	return TOOLS_OPEN_NVQGC_SIZE;
}

void tools_open_nvqgc_dump(const struct tools_open_nvqgc *ptr_struct, FILE *fd)
{
	tools_open_nvqgc_print(ptr_struct, fd, 0);
}

void tools_open_pmdic_pack(const struct tools_open_pmdic *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation_cap);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mdio_preset);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->misc_cap);
}

void tools_open_pmdic_unpack(struct tools_open_pmdic *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->operation_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 38;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	ptr_struct->mdio_preset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 88;
	ptr_struct->misc_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_pmdic_print(const struct tools_open_pmdic *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_pmdic ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation_cap        : " UH_FMT "\n", ptr_struct->operation_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clause               : " UH_FMT "\n", ptr_struct->clause);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdio_preset          : " UH_FMT "\n", ptr_struct->mdio_preset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "misc_cap             : " UH_FMT "\n", ptr_struct->misc_cap);
}

unsigned int tools_open_pmdic_size(void)
{
	return TOOLS_OPEN_PMDIC_SIZE;
}

void tools_open_pmdic_dump(const struct tools_open_pmdic *ptr_struct, FILE *fd)
{
	tools_open_pmdic_print(ptr_struct, fd, 0);
}

void tools_open_pmdio_pack(const struct tools_open_pmdio *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lock);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->reg_adr_mmd);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_op_idx);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_ops_done);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 2112, 1);
		tools_open_pmdio_addr_data_pack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset / 8);
	}
}

void tools_open_pmdio_unpack(struct tools_open_pmdio *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 29;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 22;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 59;
	ptr_struct->reg_adr_mmd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 48;
	ptr_struct->last_op_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->num_ops_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 2112, 1);
		tools_open_pmdio_addr_data_unpack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset / 8);
	}
}

void tools_open_pmdio_print(const struct tools_open_pmdio *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_pmdio ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : " UH_FMT "\n", ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clause               : " UH_FMT "\n", ptr_struct->clause);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lock                 : " UH_FMT "\n", ptr_struct->lock);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reg_adr_mmd          : " UH_FMT "\n", ptr_struct->reg_adr_mmd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_op_idx          : " UH_FMT "\n", ptr_struct->last_op_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_ops_done         : " UH_FMT "\n", ptr_struct->num_ops_done);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mdio_trans_%03d:\n", i);
		tools_open_pmdio_addr_data_print(&(ptr_struct->mdio_trans[i]), fd, indent_level + 1);
	}
}

unsigned int tools_open_pmdio_size(void)
{
	return TOOLS_OPEN_PMDIO_SIZE;
}

void tools_open_pmdio_dump(const struct tools_open_pmdio *ptr_struct, FILE *fd)
{
	tools_open_pmdio_print(ptr_struct, fd, 0);
}

void tools_open_smp_vsp_general_info_pack(const union tools_open_smp_vsp_general_info *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_capability_mask_smp_pack(&(ptr_struct->capability_mask_smp), ptr_buff);
}

void tools_open_smp_vsp_general_info_unpack(union tools_open_smp_vsp_general_info *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_capability_mask_smp_unpack(&(ptr_struct->capability_mask_smp), ptr_buff);
}

void tools_open_smp_vsp_general_info_print(const union tools_open_smp_vsp_general_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_smp_vsp_general_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	tools_open_hw_info_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info:\n");
	tools_open_fw_info_print(&(ptr_struct->fw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_info:\n");
	tools_open_sw_info_print(&(ptr_struct->sw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_mask_smp:\n");
	tools_open_capability_mask_smp_print(&(ptr_struct->capability_mask_smp), fd, indent_level + 1);
}

unsigned int tools_open_smp_vsp_general_info_size(void)
{
	return TOOLS_OPEN_SMP_VSP_GENERAL_INFO_SIZE;
}

void tools_open_smp_vsp_general_info_dump(const union tools_open_smp_vsp_general_info *ptr_struct, FILE *fd)
{
	tools_open_smp_vsp_general_info_print(ptr_struct, fd, 0);
}

void tools_open_aux_data_hdr_pack(const struct tools_open_aux_data_hdr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature0);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature1);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature2);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature3);
}

void tools_open_aux_data_hdr_unpack(struct tools_open_aux_data_hdr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_aux_data_hdr_print(const struct tools_open_aux_data_hdr *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_aux_data_hdr ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);
}

unsigned int tools_open_aux_data_hdr_size(void)
{
	return TOOLS_OPEN_AUX_DATA_HDR_SIZE;
}

void tools_open_aux_data_hdr_dump(const struct tools_open_aux_data_hdr *ptr_struct, FILE *fd)
{
	tools_open_aux_data_hdr_print(ptr_struct, fd, 0);
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

void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_uar_bar_size);
}

void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->log_uar_bar_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_bar_size ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_uar_bar_size     : " U32H_FMT "\n", ptr_struct->log_uar_bar_size);
}

unsigned int tools_open_bar_size_size(void)
{
	return TOOLS_OPEN_BAR_SIZE_SIZE;
}

void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE *fd)
{
	tools_open_bar_size_print(ptr_struct, fd, 0);
}

void tools_open_boot_settings_pack(const struct tools_open_boot_settings *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_boot_settings_unpack(struct tools_open_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_boot_settings_print(const struct tools_open_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_boot_settings ========\n");

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

unsigned int tools_open_boot_settings_size(void)
{
	return TOOLS_OPEN_BOOT_SETTINGS_SIZE;
}

void tools_open_boot_settings_dump(const struct tools_open_boot_settings *ptr_struct, FILE *fd)
{
	tools_open_boot_settings_print(ptr_struct, fd, 0);
}

void tools_open_boot_settings_ext_pack(const struct tools_open_boot_settings_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ip_ver);
}

void tools_open_boot_settings_ext_unpack(struct tools_open_boot_settings_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void tools_open_boot_settings_ext_print(const struct tools_open_boot_settings_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_boot_settings_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ip_ver               : " UH_FMT "\n", ptr_struct->ip_ver);
}

unsigned int tools_open_boot_settings_ext_size(void)
{
	return TOOLS_OPEN_BOOT_SETTINGS_EXT_SIZE;
}

void tools_open_boot_settings_ext_dump(const struct tools_open_boot_settings_ext *ptr_struct, FILE *fd)
{
	tools_open_boot_settings_ext_print(ptr_struct, fd, 0);
}

void tools_open_common_header_pack(const struct tools_open_common_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->length);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);
}

void tools_open_common_header_unpack(struct tools_open_common_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_common_header_print(const struct tools_open_common_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_common_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
}

unsigned int tools_open_common_header_size(void)
{
	return TOOLS_OPEN_COMMON_HEADER_SIZE;
}

void tools_open_common_header_dump(const struct tools_open_common_header *ptr_struct, FILE *fd)
{
	tools_open_common_header_print(ptr_struct, fd, 0);
}

void tools_open_component_desciptor_pack(const struct tools_open_component_desciptor *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->identifier);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pldm_classification);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset_h);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset_l);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->size);
}

void tools_open_component_desciptor_unpack(struct tools_open_component_desciptor *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->pldm_classification = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->cb_offset_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->cb_offset_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_component_desciptor_print(const struct tools_open_component_desciptor *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_component_desciptor ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "identifier           : " UH_FMT "\n", ptr_struct->identifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pldm_classification  : " UH_FMT "\n", ptr_struct->pldm_classification);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_offset_h          : " U32H_FMT "\n", ptr_struct->cb_offset_h);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_offset_l          : " U32H_FMT "\n", ptr_struct->cb_offset_l);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " U32H_FMT "\n", ptr_struct->size);
}

unsigned int tools_open_component_desciptor_size(void)
{
	return TOOLS_OPEN_COMPONENT_DESCIPTOR_SIZE;
}

void tools_open_component_desciptor_dump(const struct tools_open_component_desciptor *ptr_struct, FILE *fd)
{
	tools_open_component_desciptor_print(ptr_struct, fd, 0);
}

void tools_open_component_ptr_pack(const struct tools_open_component_ptr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->storage_id);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->storage_address);
}

void tools_open_component_ptr_unpack(struct tools_open_component_ptr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->storage_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->storage_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_component_ptr_print(const struct tools_open_component_ptr *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_component_ptr ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "storage_id           : " UH_FMT "\n", ptr_struct->storage_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "storage_address      : " U32H_FMT "\n", ptr_struct->storage_address);
}

unsigned int tools_open_component_ptr_size(void)
{
	return TOOLS_OPEN_COMPONENT_PTR_SIZE;
}

void tools_open_component_ptr_dump(const struct tools_open_component_ptr *ptr_struct, FILE *fd)
{
	tools_open_component_ptr_print(ptr_struct, fd, 0);
}

void tools_open_external_port_pack(const struct tools_open_external_port *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->port_owner);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->allow_rd_counters);
}

void tools_open_external_port_unpack(struct tools_open_external_port *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->port_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->allow_rd_counters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_external_port_print(const struct tools_open_external_port *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_external_port ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_owner           : " UH_FMT "\n", ptr_struct->port_owner);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "allow_rd_counters    : " UH_FMT "\n", ptr_struct->allow_rd_counters);
}

unsigned int tools_open_external_port_size(void)
{
	return TOOLS_OPEN_EXTERNAL_PORT_SIZE;
}

void tools_open_external_port_dump(const struct tools_open_external_port *ptr_struct, FILE *fd)
{
	tools_open_external_port_print(ptr_struct, fd, 0);
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

void tools_open_infiniband_boot_settings_pack(const struct tools_open_infiniband_boot_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->boot_pkey);
}

void tools_open_infiniband_boot_settings_unpack(struct tools_open_infiniband_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void tools_open_infiniband_boot_settings_print(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_infiniband_boot_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_pkey            : " UH_FMT "\n", ptr_struct->boot_pkey);
}

unsigned int tools_open_infiniband_boot_settings_size(void)
{
	return TOOLS_OPEN_INFINIBAND_BOOT_SETTINGS_SIZE;
}

void tools_open_infiniband_boot_settings_dump(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE *fd)
{
	tools_open_infiniband_boot_settings_print(ptr_struct, fd, 0);
}

void tools_open_infiniband_dc_capabilities_pack(const struct tools_open_infiniband_dc_capabilities *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_log_dcr_hash_table_size);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_log_dcr_hash_table_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_dcr_lifo_size);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_dcr_lifo_size);
}

void tools_open_infiniband_dc_capabilities_unpack(struct tools_open_infiniband_dc_capabilities *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->min_log_dcr_hash_table_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->max_log_dcr_hash_table_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->min_dcr_lifo_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->max_dcr_lifo_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_infiniband_dc_capabilities_print(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_infiniband_dc_capabilities ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_log_dcr_hash_table_size : " U32H_FMT "\n", ptr_struct->min_log_dcr_hash_table_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_log_dcr_hash_table_size : " U32H_FMT "\n", ptr_struct->max_log_dcr_hash_table_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_dcr_lifo_size    : " U32H_FMT "\n", ptr_struct->min_dcr_lifo_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_dcr_lifo_size    : " U32H_FMT "\n", ptr_struct->max_dcr_lifo_size);
}

unsigned int tools_open_infiniband_dc_capabilities_size(void)
{
	return TOOLS_OPEN_INFINIBAND_DC_CAPABILITIES_SIZE;
}

void tools_open_infiniband_dc_capabilities_dump(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE *fd)
{
	tools_open_infiniband_dc_capabilities_print(ptr_struct, fd, 0);
}

void tools_open_infiniband_dc_settings_pack(const struct tools_open_infiniband_dc_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_dcr_hash_table_size);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->dcr_lifo_size);
}

void tools_open_infiniband_dc_settings_unpack(struct tools_open_infiniband_dc_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->log_dcr_hash_table_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 40;
	ptr_struct->dcr_lifo_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void tools_open_infiniband_dc_settings_print(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_infiniband_dc_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_dcr_hash_table_size : " UH_FMT "\n", ptr_struct->log_dcr_hash_table_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dcr_lifo_size        : " UH_FMT "\n", ptr_struct->dcr_lifo_size);
}

unsigned int tools_open_infiniband_dc_settings_size(void)
{
	return TOOLS_OPEN_INFINIBAND_DC_SETTINGS_SIZE;
}

void tools_open_infiniband_dc_settings_dump(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE *fd)
{
	tools_open_infiniband_dc_settings_print(ptr_struct, fd, 0);
}

void tools_open_iscsi_settings_pack(const struct tools_open_iscsi_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->target_as_first_hdd_en);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->boot_to_target);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv6_auto_config_en);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vlan_en);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tcp_timestamps_en);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_mutual_auth_en);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_auth_en);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dhcp_iscsi_en);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv4_dhcp_en);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->vlan);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lun_busy_retry_count);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_up_delay_time);
}

void tools_open_iscsi_settings_unpack(struct tools_open_iscsi_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 10;
	ptr_struct->target_as_first_hdd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 7;
	ptr_struct->ipv6_auto_config_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->dhcp_iscsi_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 52;
	ptr_struct->vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 88;
	ptr_struct->lun_busy_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_iscsi_settings_print(const struct tools_open_iscsi_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_iscsi_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "target_as_first_hdd_en : " UH_FMT "\n", ptr_struct->target_as_first_hdd_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_to_target       : " UH_FMT "\n", ptr_struct->boot_to_target);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipv6_auto_config_en  : " UH_FMT "\n", ptr_struct->ipv6_auto_config_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vlan_en              : " UH_FMT "\n", ptr_struct->vlan_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tcp_timestamps_en    : " UH_FMT "\n", ptr_struct->tcp_timestamps_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "chap_mutual_auth_en  : " UH_FMT "\n", ptr_struct->chap_mutual_auth_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "chap_auth_en         : " UH_FMT "\n", ptr_struct->chap_auth_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dhcp_iscsi_en        : " UH_FMT "\n", ptr_struct->dhcp_iscsi_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipv4_dhcp_en         : " UH_FMT "\n", ptr_struct->ipv4_dhcp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vlan                 : " UH_FMT "\n", ptr_struct->vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lun_busy_retry_count : " UH_FMT "\n", ptr_struct->lun_busy_retry_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_up_delay_time   : " UH_FMT "\n", ptr_struct->link_up_delay_time);
}

unsigned int tools_open_iscsi_settings_size(void)
{
	return TOOLS_OPEN_ISCSI_SETTINGS_SIZE;
}

void tools_open_iscsi_settings_dump(const struct tools_open_iscsi_settings *ptr_struct, FILE *fd)
{
	tools_open_iscsi_settings_print(ptr_struct, fd, 0);
}

void tools_open_lldp_client_settings_pack(const struct tools_open_lldp_client_settings *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_dcbx);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lldp_nb_rx_mode);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lldp_nb_tx_mode);
}

void tools_open_lldp_client_settings_unpack(struct tools_open_lldp_client_settings *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	ptr_struct->lldp_nb_dcbx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->lldp_nb_rx_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->lldp_nb_tx_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void tools_open_lldp_client_settings_print(const struct tools_open_lldp_client_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_lldp_client_settings ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_dcbx         : " UH_FMT "\n", ptr_struct->lldp_nb_dcbx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_rx_mode      : " UH_FMT "\n", ptr_struct->lldp_nb_rx_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_tx_mode      : " UH_FMT "\n", ptr_struct->lldp_nb_tx_mode);
}

unsigned int tools_open_lldp_client_settings_size(void)
{
	return TOOLS_OPEN_LLDP_CLIENT_SETTINGS_SIZE;
}

void tools_open_lldp_client_settings_dump(const struct tools_open_lldp_client_settings *ptr_struct, FILE *fd)
{
	tools_open_lldp_client_settings_print(ptr_struct, fd, 0);
}

void tools_open_lldp_nb_pack(const struct tools_open_lldp_nb *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_rx_en);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_tx_en);
	offset = 84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->lldp_msg_tx_interval);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 224, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lldp_tx_tlv_mask[i]);
	}
}

void tools_open_lldp_nb_unpack(struct tools_open_lldp_nb *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 1;
	ptr_struct->lldp_nb_rx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->lldp_nb_tx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 84;
	ptr_struct->lldp_msg_tx_interval = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 224, 1);
		ptr_struct->lldp_tx_tlv_mask[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void tools_open_lldp_nb_print(const struct tools_open_lldp_nb *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_lldp_nb ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_rx_en        : " UH_FMT "\n", ptr_struct->lldp_nb_rx_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_tx_en        : " UH_FMT "\n", ptr_struct->lldp_nb_tx_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_msg_tx_interval : " UH_FMT "\n", ptr_struct->lldp_msg_tx_interval);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "lldp_tx_tlv_mask_%03d : " UH_FMT "\n", i, ptr_struct->lldp_tx_tlv_mask[i]);
	}
}

unsigned int tools_open_lldp_nb_size(void)
{
	return TOOLS_OPEN_LLDP_NB_SIZE;
}

void tools_open_lldp_nb_dump(const struct tools_open_lldp_nb *ptr_struct, FILE *fd)
{
	tools_open_lldp_nb_print(ptr_struct, fd, 0);
}

void tools_open_lldp_nb_cap_pack(const struct tools_open_lldp_nb_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_dcbx_en);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lldp_nb_rx_cap);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lldp_nb_tx_cap);
}

void tools_open_lldp_nb_cap_unpack(struct tools_open_lldp_nb_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	ptr_struct->lldp_nb_dcbx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->lldp_nb_rx_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->lldp_nb_tx_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void tools_open_lldp_nb_cap_print(const struct tools_open_lldp_nb_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_lldp_nb_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_dcbx_en      : " UH_FMT "\n", ptr_struct->lldp_nb_dcbx_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_rx_cap       : " UH_FMT "\n", ptr_struct->lldp_nb_rx_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_tx_cap       : " UH_FMT "\n", ptr_struct->lldp_nb_tx_cap);
}

unsigned int tools_open_lldp_nb_cap_size(void)
{
	return TOOLS_OPEN_LLDP_NB_CAP_SIZE;
}

void tools_open_lldp_nb_cap_dump(const struct tools_open_lldp_nb_cap *ptr_struct, FILE *fd)
{
	tools_open_lldp_nb_cap_print(ptr_struct, fd, 0);
}

void tools_open_lldp_nb_dcbx_pack(const struct tools_open_lldp_nb_dcbx *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ieee_dcbx_en);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cee_dcbx_en);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dcbx_willing);
}

void tools_open_lldp_nb_dcbx_unpack(struct tools_open_lldp_nb_dcbx *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->ieee_dcbx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->cee_dcbx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->dcbx_willing = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_lldp_nb_dcbx_print(const struct tools_open_lldp_nb_dcbx *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_lldp_nb_dcbx ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ieee_dcbx_en         : " UH_FMT "\n", ptr_struct->ieee_dcbx_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cee_dcbx_en          : " UH_FMT "\n", ptr_struct->cee_dcbx_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dcbx_willing         : " UH_FMT "\n", ptr_struct->dcbx_willing);
}

unsigned int tools_open_lldp_nb_dcbx_size(void)
{
	return TOOLS_OPEN_LLDP_NB_DCBX_SIZE;
}

void tools_open_lldp_nb_dcbx_dump(const struct tools_open_lldp_nb_dcbx *ptr_struct, FILE *fd)
{
	tools_open_lldp_nb_dcbx_print(ptr_struct, fd, 0);
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
	tools_open_mlock_pack(&(ptr_struct->mlock), ptr_buff);
}

void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_mlock_unpack(&(ptr_struct->mlock), ptr_buff);
}

void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mnv_cfg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnva:\n");
	tools_open_mnva_print(&(ptr_struct->mnva), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvi:\n");
	tools_open_mnvi_print(&(ptr_struct->mnvi), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvia:\n");
	tools_open_mnvia_print(&(ptr_struct->mnvia), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvqc:\n");
	tools_open_nvqc_print(&(ptr_struct->nvqc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvia:\n");
	tools_open_nvia_print(&(ptr_struct->nvia), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvda:\n");
	tools_open_nvda_print(&(ptr_struct->nvda), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvdi:\n");
	tools_open_nvdi_print(&(ptr_struct->nvdi), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvqgc:\n");
	tools_open_nvqgc_print(&(ptr_struct->nvqgc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mvts:\n");
	tools_open_mvts_print(&(ptr_struct->mvts), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mnvgn:\n");
	tools_open_mnvgn_print(&(ptr_struct->mnvgn), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfmc:\n");
	tools_open_mfmc_print(&(ptr_struct->mfmc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfpa:\n");
	tools_open_mfpa_print(&(ptr_struct->mfpa), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir:\n");
	tools_open_mgir_print(&(ptr_struct->mgir), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcam:\n");
	tools_open_mcam_print(&(ptr_struct->mcam), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgnle:\n");
	tools_open_mgnle_print(&(ptr_struct->mgnle), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mlock:\n");
	tools_open_mlock_print(&(ptr_struct->mlock), fd, indent_level + 1);
}

unsigned int tools_open_mnv_cfg_size(void)
{
	return TOOLS_OPEN_MNV_CFG_SIZE;
}

void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE *fd)
{
	tools_open_mnv_cfg_print(ptr_struct, fd, 0);
}

void tools_open_multi_part_pack(const struct tools_open_multi_part *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_length);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->number_of_extensions);
}

void tools_open_multi_part_unpack(struct tools_open_multi_part *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->total_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->number_of_extensions = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_multi_part_print(const struct tools_open_multi_part *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_multi_part ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_length         : " UH_FMT "\n", ptr_struct->total_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "number_of_extensions : " UH_FMT "\n", ptr_struct->number_of_extensions);
}

unsigned int tools_open_multi_part_size(void)
{
	return TOOLS_OPEN_MULTI_PART_SIZE;
}

void tools_open_multi_part_dump(const struct tools_open_multi_part *ptr_struct, FILE *fd)
{
	tools_open_multi_part_print(ptr_struct, fd, 0);
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

void tools_open_nv_cx3_global_conf_pack(const struct tools_open_nv_cx3_global_conf *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->phy_param_mode);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->steer_force_vlan);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cq_timestamp);
}

void tools_open_nv_cx3_global_conf_unpack(struct tools_open_nv_cx3_global_conf *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->phy_param_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->steer_force_vlan = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->cq_timestamp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_nv_cx3_global_conf_print(const struct tools_open_nv_cx3_global_conf *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_cx3_global_conf ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_param_mode       : " UH_FMT "\n", ptr_struct->phy_param_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "steer_force_vlan     : " UH_FMT "\n", ptr_struct->steer_force_vlan);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cq_timestamp         : " UH_FMT "\n", ptr_struct->cq_timestamp);
}

unsigned int tools_open_nv_cx3_global_conf_size(void)
{
	return TOOLS_OPEN_NV_CX3_GLOBAL_CONF_SIZE;
}

void tools_open_nv_cx3_global_conf_dump(const struct tools_open_nv_cx3_global_conf *ptr_struct, FILE *fd)
{
	tools_open_nv_cx3_global_conf_print(ptr_struct, fd, 0);
}

void tools_open_option_rom_capability_pack(const struct tools_open_option_rom_capability *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ip_ver);
}

void tools_open_option_rom_capability_unpack(struct tools_open_option_rom_capability *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_option_rom_capability_print(const struct tools_open_option_rom_capability *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_option_rom_capability ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ip_ver               : " UH_FMT "\n", ptr_struct->ip_ver);
}

unsigned int tools_open_option_rom_capability_size(void)
{
	return TOOLS_OPEN_OPTION_ROM_CAPABILITY_SIZE;
}

void tools_open_option_rom_capability_dump(const struct tools_open_option_rom_capability *ptr_struct, FILE *fd)
{
	tools_open_option_rom_capability_print(ptr_struct, fd, 0);
}

void tools_open_package_descriptor_pack(const struct tools_open_package_descriptor *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_devices);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_components);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_archive_size);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_size_h);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_size_l);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cb_compression);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->user_data_offset);
}

void tools_open_package_descriptor_unpack(struct tools_open_package_descriptor *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->num_of_devices = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->num_of_components = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->cb_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->cb_archive_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->cb_size_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->cb_size_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->cb_compression = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 192;
	ptr_struct->user_data_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_package_descriptor_print(const struct tools_open_package_descriptor *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_package_descriptor ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_devices       : " UH_FMT "\n", ptr_struct->num_of_devices);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_components    : " UH_FMT "\n", ptr_struct->num_of_components);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_offset            : " U32H_FMT "\n", ptr_struct->cb_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_archive_size      : " U32H_FMT "\n", ptr_struct->cb_archive_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_size_h            : " U32H_FMT "\n", ptr_struct->cb_size_h);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_size_l            : " U32H_FMT "\n", ptr_struct->cb_size_l);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cb_compression       : " UH_FMT "\n", ptr_struct->cb_compression);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "user_data_offset     : " U32H_FMT "\n", ptr_struct->user_data_offset);
}

unsigned int tools_open_package_descriptor_size(void)
{
	return TOOLS_OPEN_PACKAGE_DESCRIPTOR_SIZE;
}

void tools_open_package_descriptor_dump(const struct tools_open_package_descriptor *ptr_struct, FILE *fd)
{
	tools_open_package_descriptor_print(ptr_struct, fd, 0);
}

void tools_open_pci_capabilities_pack(const struct tools_open_pci_capabilities *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pf_bar_size_supported);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_bar_size_supported);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pf_msix_supported);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_vf_msix_supported);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_supported);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_total_bar_valid);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_total_msix_valid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_vfs_per_pf_valid);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_vfs_per_pf);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_num_pfs);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_support);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_qos_control_support);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_support);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_max_pf_uar_bar_size1);
	offset = 84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_max_vf_uar_bar_size);
	offset = 74;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->max_num_pf_msix);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->max_num_vf_msix);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_total_msix);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_total_bar);
}

void tools_open_pci_capabilities_unpack(struct tools_open_pci_capabilities *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 7;
	ptr_struct->pf_bar_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->vf_bar_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->num_pf_msix_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->num_vf_msix_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->num_pfs_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->max_total_bar_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->max_total_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->max_vfs_per_pf_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->max_vfs_per_pf = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 44;
	ptr_struct->max_num_pfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 34;
	ptr_struct->fpp_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->vf_qos_control_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->sriov_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 90;
	ptr_struct->log_max_pf_uar_bar_size1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 84;
	ptr_struct->log_max_vf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 74;
	ptr_struct->max_num_pf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 64;
	ptr_struct->max_num_vf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 96;
	ptr_struct->max_total_msix = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->max_total_bar = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void tools_open_pci_capabilities_print(const struct tools_open_pci_capabilities *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_pci_capabilities ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pf_bar_size_supported : " UH_FMT "\n", ptr_struct->pf_bar_size_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vf_bar_size_supported : " UH_FMT "\n", ptr_struct->vf_bar_size_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pf_msix_supported : " UH_FMT "\n", ptr_struct->num_pf_msix_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_vf_msix_supported : " UH_FMT "\n", ptr_struct->num_vf_msix_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pfs_supported    : " UH_FMT "\n", ptr_struct->num_pfs_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_total_bar_valid  : " UH_FMT "\n", ptr_struct->max_total_bar_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_total_msix_valid : " UH_FMT "\n", ptr_struct->max_total_msix_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_vfs_per_pf_valid : " UH_FMT "\n", ptr_struct->max_vfs_per_pf_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_vfs_per_pf       : " UH_FMT "\n", ptr_struct->max_vfs_per_pf);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_pfs          : " UH_FMT "\n", ptr_struct->max_num_pfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpp_support          : " UH_FMT "\n", ptr_struct->fpp_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vf_qos_control_support : " UH_FMT "\n", ptr_struct->vf_qos_control_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_support        : " UH_FMT "\n", ptr_struct->sriov_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_pf_uar_bar_size1 : " UH_FMT "\n", ptr_struct->log_max_pf_uar_bar_size1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_vf_uar_bar_size : " UH_FMT "\n", ptr_struct->log_max_vf_uar_bar_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_pf_msix      : " UH_FMT "\n", ptr_struct->max_num_pf_msix);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_vf_msix      : " UH_FMT "\n", ptr_struct->max_num_vf_msix);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_total_msix       : " U32H_FMT "\n", ptr_struct->max_total_msix);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_total_bar        : " U32H_FMT "\n", ptr_struct->max_total_bar);
}

unsigned int tools_open_pci_capabilities_size(void)
{
	return TOOLS_OPEN_PCI_CAPABILITIES_SIZE;
}

void tools_open_pci_capabilities_dump(const struct tools_open_pci_capabilities *ptr_struct, FILE *fd)
{
	tools_open_pci_capabilities_print(ptr_struct, fd, 0);
}

void tools_open_pci_configuration_pack(const struct tools_open_pci_configuration *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pf_bar_size_valid);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_bar_size_valid);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_msix_valid);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_vfs_msix_valid);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_valid);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_valid);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->full_vf_qos_valid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_valid);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_pfs);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_en);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->full_vf_qos);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_pf_uar_bar_size);
	offset = 84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_vf_uar_bar_size);
	offset = 74;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->num_pf_msix);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->num_vf_msix);
}

void tools_open_pci_configuration_unpack(struct tools_open_pci_configuration *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 7;
	ptr_struct->pf_bar_size_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->vf_bar_size_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->num_pfs_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->num_vfs_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->num_pfs_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->fpp_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->full_vf_qos_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->sriov_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 44;
	ptr_struct->num_pfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 34;
	ptr_struct->fpp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->full_vf_qos = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 90;
	ptr_struct->log_pf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 84;
	ptr_struct->log_vf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 74;
	ptr_struct->num_pf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 64;
	ptr_struct->num_vf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
}

void tools_open_pci_configuration_print(const struct tools_open_pci_configuration *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_pci_configuration ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pf_bar_size_valid    : " UH_FMT "\n", ptr_struct->pf_bar_size_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vf_bar_size_valid    : " UH_FMT "\n", ptr_struct->vf_bar_size_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pfs_msix_valid   : " UH_FMT "\n", ptr_struct->num_pfs_msix_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_vfs_msix_valid   : " UH_FMT "\n", ptr_struct->num_vfs_msix_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pfs_valid        : " UH_FMT "\n", ptr_struct->num_pfs_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpp_valid            : " UH_FMT "\n", ptr_struct->fpp_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "full_vf_qos_valid    : " UH_FMT "\n", ptr_struct->full_vf_qos_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_valid          : " UH_FMT "\n", ptr_struct->sriov_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_vfs            : " UH_FMT "\n", ptr_struct->total_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pfs              : " UH_FMT "\n", ptr_struct->num_pfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fpp_en               : " UH_FMT "\n", ptr_struct->fpp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "full_vf_qos          : " UH_FMT "\n", ptr_struct->full_vf_qos);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_en             : " UH_FMT "\n", ptr_struct->sriov_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_pf_uar_bar_size  : " UH_FMT "\n", ptr_struct->log_pf_uar_bar_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_vf_uar_bar_size  : " UH_FMT "\n", ptr_struct->log_vf_uar_bar_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_pf_msix          : " UH_FMT "\n", ptr_struct->num_pf_msix);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_vf_msix          : " UH_FMT "\n", ptr_struct->num_vf_msix);
}

unsigned int tools_open_pci_configuration_size(void)
{
	return TOOLS_OPEN_PCI_CONFIGURATION_SIZE;
}

void tools_open_pci_configuration_dump(const struct tools_open_pci_configuration *ptr_struct, FILE *fd)
{
	tools_open_pci_configuration_print(ptr_struct, fd, 0);
}

void tools_open_phy_reg_pack(const union tools_open_phy_reg *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_pmdio_pack(&(ptr_struct->pmdio), ptr_buff);
}

void tools_open_phy_reg_unpack(union tools_open_phy_reg *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_pmdio_unpack(&(ptr_struct->pmdio), ptr_buff);
}

void tools_open_phy_reg_print(const union tools_open_phy_reg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_phy_reg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmdic:\n");
	tools_open_pmdic_print(&(ptr_struct->pmdic), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmdio:\n");
	tools_open_pmdio_print(&(ptr_struct->pmdio), fd, indent_level + 1);
}

unsigned int tools_open_phy_reg_size(void)
{
	return TOOLS_OPEN_PHY_REG_SIZE;
}

void tools_open_phy_reg_dump(const union tools_open_phy_reg *ptr_struct, FILE *fd)
{
	tools_open_phy_reg_print(ptr_struct, fd, 0);
}

void tools_open_port_boot_state_pack(const struct tools_open_port_boot_state *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->aux_power_indication_gpio);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->aux_power_indication_gpio_en);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->standby_on_aux);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->power_up_on_aux);
}

void tools_open_port_boot_state_unpack(struct tools_open_port_boot_state *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->aux_power_indication_gpio = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->aux_power_indication_gpio_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->standby_on_aux = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->power_up_on_aux = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_port_boot_state_print(const struct tools_open_port_boot_state *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_port_boot_state ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aux_power_indication_gpio : " UH_FMT "\n", ptr_struct->aux_power_indication_gpio);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aux_power_indication_gpio_en : " UH_FMT "\n", ptr_struct->aux_power_indication_gpio_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "standby_on_aux       : " UH_FMT "\n", ptr_struct->standby_on_aux);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "power_up_on_aux      : " UH_FMT "\n", ptr_struct->power_up_on_aux);
}

unsigned int tools_open_port_boot_state_size(void)
{
	return TOOLS_OPEN_PORT_BOOT_STATE_SIZE;
}

void tools_open_port_boot_state_dump(const struct tools_open_port_boot_state *ptr_struct, FILE *fd)
{
	tools_open_port_boot_state_print(ptr_struct, fd, 0);
}

void tools_open_preboot_boot_settings_pack(const struct tools_open_preboot_boot_settings *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_preboot_boot_settings_unpack(struct tools_open_preboot_boot_settings *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_preboot_boot_settings_print(const struct tools_open_preboot_boot_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_preboot_boot_settings ========\n");

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

unsigned int tools_open_preboot_boot_settings_size(void)
{
	return TOOLS_OPEN_PREBOOT_BOOT_SETTINGS_SIZE;
}

void tools_open_preboot_boot_settings_dump(const struct tools_open_preboot_boot_settings *ptr_struct, FILE *fd)
{
	tools_open_preboot_boot_settings_print(ptr_struct, fd, 0);
}

void tools_open_preboot_flow_ctrl_pack(const struct tools_open_preboot_flow_ctrl *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfcrx);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfctx);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pfc_willing);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pprx);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pptx);
}

void tools_open_preboot_flow_ctrl_unpack(struct tools_open_preboot_flow_ctrl *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->pfcrx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->pfctx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->pfc_willing = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_preboot_flow_ctrl_print(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_preboot_flow_ctrl ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pfcrx                : " UH_FMT "\n", ptr_struct->pfcrx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pfctx                : " UH_FMT "\n", ptr_struct->pfctx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pfc_willing          : " UH_FMT "\n", ptr_struct->pfc_willing);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pprx                 : " UH_FMT "\n", ptr_struct->pprx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pptx                 : " UH_FMT "\n", ptr_struct->pptx);
}

unsigned int tools_open_preboot_flow_ctrl_size(void)
{
	return TOOLS_OPEN_PREBOOT_FLOW_CTRL_SIZE;
}

void tools_open_preboot_flow_ctrl_dump(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE *fd)
{
	tools_open_preboot_flow_ctrl_print(ptr_struct, fd, 0);
}

void tools_open_qos_pack(const struct tools_open_qos *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_of_vl);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_of_tc);
}

void tools_open_qos_unpack(struct tools_open_qos *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->num_of_vl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->num_of_tc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_qos_print(const struct tools_open_qos *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_qos ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_vl            : " UH_FMT "\n", ptr_struct->num_of_vl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_tc            : " UH_FMT "\n", ptr_struct->num_of_tc);
}

unsigned int tools_open_qos_size(void)
{
	return TOOLS_OPEN_QOS_SIZE;
}

void tools_open_qos_dump(const struct tools_open_qos *ptr_struct, FILE *fd)
{
	tools_open_qos_print(ptr_struct, fd, 0);
}

void tools_open_qos_cap_pack(const struct tools_open_qos_cap *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_num_of_vl);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_num_of_tc);
}

void tools_open_qos_cap_unpack(struct tools_open_qos_cap *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->max_num_of_vl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->max_num_of_tc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_qos_cap_print(const struct tools_open_qos_cap *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_qos_cap ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_of_vl        : " UH_FMT "\n", ptr_struct->max_num_of_vl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_num_of_tc        : " UH_FMT "\n", ptr_struct->max_num_of_tc);
}

unsigned int tools_open_qos_cap_size(void)
{
	return TOOLS_OPEN_QOS_CAP_SIZE;
}

void tools_open_qos_cap_dump(const struct tools_open_qos_cap *ptr_struct, FILE *fd)
{
	tools_open_qos_cap_print(ptr_struct, fd, 0);
}

void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

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

void tools_open_roce_cc_pack(const struct tools_open_roce_cc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->roce_cc_enable_priority);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->roce_cc_algorithm);
}

void tools_open_roce_cc_unpack(struct tools_open_roce_cc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->roce_cc_enable_priority = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->roce_cc_algorithm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_roce_cc_print(const struct tools_open_roce_cc *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_roce_cc ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_cc_enable_priority : " UH_FMT "\n", ptr_struct->roce_cc_enable_priority);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_cc_algorithm    : " UH_FMT "\n", ptr_struct->roce_cc_algorithm);
}

unsigned int tools_open_roce_cc_size(void)
{
	return TOOLS_OPEN_ROCE_CC_SIZE;
}

void tools_open_roce_cc_dump(const struct tools_open_roce_cc *ptr_struct, FILE *fd)
{
	tools_open_roce_cc_print(ptr_struct, fd, 0);
}

void tools_open_roce_cc_ecn_pack(const struct tools_open_roce_cc_ecn *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clamp_tgt_rate_after_time_inc);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clamp_tgt_rate);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_time_reset);
	offset = 81;
	adb2c_push_bits_to_buff(ptr_buff, offset, 15, (u_int32_t)ptr_struct->rpg_byte_reset);
	offset = 123;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->rpg_threshold);
	offset = 129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 31, (u_int32_t)ptr_struct->rpg_max_rate);
	offset = 175;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_ai_rate);
	offset = 207;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_hai_rate);
	offset = 252;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rpg_gd);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rpg_min_dec_fac);
	offset = 303;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_min_rate);
	offset = 335;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rate_to_set_on_first_cnp);
	offset = 374;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->dce_tcp_g);
	offset = 399;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->dce_tcp_rtt);
	offset = 431;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rate_reduce_monitor_period);
	offset = 470;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->initial_alpha_value);
	offset = 495;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->min_time_between_cnps);
	offset = 541;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->cnp_802p_prio);
	offset = 530;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->cnp_dscp);
}

void tools_open_roce_cc_ecn_unpack(struct tools_open_roce_cc_ecn *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 1;
	ptr_struct->clamp_tgt_rate_after_time_inc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->clamp_tgt_rate = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 47;
	ptr_struct->rpg_time_reset = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 81;
	ptr_struct->rpg_byte_reset = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 15);
	offset = 123;
	ptr_struct->rpg_threshold = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 129;
	ptr_struct->rpg_max_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 31);
	offset = 175;
	ptr_struct->rpg_ai_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 207;
	ptr_struct->rpg_hai_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 252;
	ptr_struct->rpg_gd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->rpg_min_dec_fac = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 303;
	ptr_struct->rpg_min_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 335;
	ptr_struct->rate_to_set_on_first_cnp = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 374;
	ptr_struct->dce_tcp_g = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 399;
	ptr_struct->dce_tcp_rtt = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 431;
	ptr_struct->rate_reduce_monitor_period = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 470;
	ptr_struct->initial_alpha_value = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 495;
	ptr_struct->min_time_between_cnps = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);
	offset = 541;
	ptr_struct->cnp_802p_prio = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 530;
	ptr_struct->cnp_dscp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
}

void tools_open_roce_cc_ecn_print(const struct tools_open_roce_cc_ecn *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_roce_cc_ecn ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clamp_tgt_rate_after_time_inc : " UH_FMT "\n", ptr_struct->clamp_tgt_rate_after_time_inc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clamp_tgt_rate       : " UH_FMT "\n", ptr_struct->clamp_tgt_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_time_reset       : " UH_FMT "\n", ptr_struct->rpg_time_reset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_byte_reset       : " UH_FMT "\n", ptr_struct->rpg_byte_reset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_threshold        : " UH_FMT "\n", ptr_struct->rpg_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_max_rate         : " UH_FMT "\n", ptr_struct->rpg_max_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_ai_rate          : " UH_FMT "\n", ptr_struct->rpg_ai_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_hai_rate         : " UH_FMT "\n", ptr_struct->rpg_hai_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_gd               : " UH_FMT "\n", ptr_struct->rpg_gd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_min_dec_fac      : " UH_FMT "\n", ptr_struct->rpg_min_dec_fac);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rpg_min_rate         : " UH_FMT "\n", ptr_struct->rpg_min_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rate_to_set_on_first_cnp : " UH_FMT "\n", ptr_struct->rate_to_set_on_first_cnp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dce_tcp_g            : " UH_FMT "\n", ptr_struct->dce_tcp_g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dce_tcp_rtt          : " UH_FMT "\n", ptr_struct->dce_tcp_rtt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rate_reduce_monitor_period : " UH_FMT "\n", ptr_struct->rate_reduce_monitor_period);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "initial_alpha_value  : " UH_FMT "\n", ptr_struct->initial_alpha_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_time_between_cnps : " UH_FMT "\n", ptr_struct->min_time_between_cnps);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnp_802p_prio        : " UH_FMT "\n", ptr_struct->cnp_802p_prio);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnp_dscp             : " UH_FMT "\n", ptr_struct->cnp_dscp);
}

unsigned int tools_open_roce_cc_ecn_size(void)
{
	return TOOLS_OPEN_ROCE_CC_ECN_SIZE;
}

void tools_open_roce_cc_ecn_dump(const struct tools_open_roce_cc_ecn *ptr_struct, FILE *fd)
{
	tools_open_roce_cc_ecn_print(ptr_struct, fd, 0);
}

void tools_open_roce_v_1_5_next_protocol_pack(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->roce_over_ip_next_protocol);
}

void tools_open_roce_v_1_5_next_protocol_unpack(struct tools_open_roce_v_1_5_next_protocol *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->roce_over_ip_next_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_roce_v_1_5_next_protocol_print(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_roce_v_1_5_next_protocol ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_over_ip_next_protocol : " UH_FMT "\n", ptr_struct->roce_over_ip_next_protocol);
}

unsigned int tools_open_roce_v_1_5_next_protocol_size(void)
{
	return TOOLS_OPEN_ROCE_V_1_5_NEXT_PROTOCOL_SIZE;
}

void tools_open_roce_v_1_5_next_protocol_dump(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE *fd)
{
	tools_open_roce_v_1_5_next_protocol_print(ptr_struct, fd, 0);
}

void tools_open_smp_data_pack(const union tools_open_smp_data *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_extended_ib_port_info_pack(&(ptr_struct->extended_port_info), ptr_buff);
}

void tools_open_smp_data_unpack(union tools_open_smp_data *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_extended_ib_port_info_unpack(&(ptr_struct->extended_port_info), ptr_buff);
}

void tools_open_smp_data_print(const union tools_open_smp_data *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_smp_data ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "general_info:\n");
	tools_open_smp_vsp_general_info_print(&(ptr_struct->general_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_info:\n");
	tools_open_ib_port_info_print(&(ptr_struct->port_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node_info:\n");
	tools_open_node_info_print(&(ptr_struct->node_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_port_info:\n");
	tools_open_extended_ib_port_info_print(&(ptr_struct->extended_port_info), fd, indent_level + 1);
}

unsigned int tools_open_smp_data_size(void)
{
	return TOOLS_OPEN_SMP_DATA_SIZE;
}

void tools_open_smp_data_dump(const union tools_open_smp_data *ptr_struct, FILE *fd)
{
	tools_open_smp_data_print(ptr_struct, fd, 0);
}

void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);
}

void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_sriov ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_vfs            : " UH_FMT "\n", ptr_struct->total_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov_en             : " UH_FMT "\n", ptr_struct->sriov_en);
}

unsigned int tools_open_sriov_size(void)
{
	return TOOLS_OPEN_SRIOV_SIZE;
}

void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE *fd)
{
	tools_open_sriov_print(ptr_struct, fd, 0);
}

void tools_open_tpt_capabilities_pack(const struct tools_open_tpt_capabilities *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->log_max_payload_size_supported);
}

void tools_open_tpt_capabilities_unpack(struct tools_open_tpt_capabilities *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->log_max_payload_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void tools_open_tpt_capabilities_print(const struct tools_open_tpt_capabilities *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_tpt_capabilities ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_payload_size_supported : " UH_FMT "\n", ptr_struct->log_max_payload_size_supported);
}

unsigned int tools_open_tpt_capabilities_size(void)
{
	return TOOLS_OPEN_TPT_CAPABILITIES_SIZE;
}

void tools_open_tpt_capabilities_dump(const struct tools_open_tpt_capabilities *ptr_struct, FILE *fd)
{
	tools_open_tpt_capabilities_print(ptr_struct, fd, 0);
}

void tools_open_tpt_configuration_pack(const struct tools_open_tpt_configuration *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_max_payload_size);
}

void tools_open_tpt_configuration_unpack(struct tools_open_tpt_configuration *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->log_max_payload_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void tools_open_tpt_configuration_print(const struct tools_open_tpt_configuration *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_tpt_configuration ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_payload_size : " UH_FMT "\n", ptr_struct->log_max_payload_size);
}

unsigned int tools_open_tpt_configuration_size(void)
{
	return TOOLS_OPEN_TPT_CONFIGURATION_SIZE;
}

void tools_open_tpt_configuration_dump(const struct tools_open_tpt_configuration *ptr_struct, FILE *fd)
{
	tools_open_tpt_configuration_print(ptr_struct, fd, 0);
}

void tools_open_version_pack(const struct tools_open_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->version_sub_minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_major);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->day);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->month);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->year);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->seconds);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minutes);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hour);
}

void tools_open_version_unpack(struct tools_open_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->version_sub_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->version_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->version_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void tools_open_version_print(const struct tools_open_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_sub_minor    : " UH_FMT "\n", ptr_struct->version_sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_minor        : " UH_FMT "\n", ptr_struct->version_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_major        : " UH_FMT "\n", ptr_struct->version_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "day                  : " UH_FMT "\n", ptr_struct->day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "month                : " UH_FMT "\n", ptr_struct->month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "year                 : " UH_FMT "\n", ptr_struct->year);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seconds              : " UH_FMT "\n", ptr_struct->seconds);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minutes              : " UH_FMT "\n", ptr_struct->minutes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hour                 : " UH_FMT "\n", ptr_struct->hour);
}

unsigned int tools_open_version_size(void)
{
	return TOOLS_OPEN_VERSION_SIZE;
}

void tools_open_version_dump(const struct tools_open_version *ptr_struct, FILE *fd)
{
	tools_open_version_print(ptr_struct, fd, 0);
}

void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_vpi_settings ========\n");

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

unsigned int tools_open_vpi_settings_size(void)
{
	return TOOLS_OPEN_VPI_SETTINGS_SIZE;
}

void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE *fd)
{
	tools_open_vpi_settings_print(ptr_struct, fd, 0);
}

void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t *ptr_buff)
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

void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t *ptr_buff)
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

void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_wol ========\n");

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

unsigned int tools_open_wol_size(void)
{
	return TOOLS_OPEN_WOL_SIZE;
}

void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE *fd)
{
	tools_open_wol_print(ptr_struct, fd, 0);
}

void tools_open_IbMads_pack(const union tools_open_IbMads *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_smp_data_pack(&(ptr_struct->smp), ptr_buff);
}

void tools_open_IbMads_unpack(union tools_open_IbMads *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_smp_data_unpack(&(ptr_struct->smp), ptr_buff);
}

void tools_open_IbMads_print(const union tools_open_IbMads *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_IbMads ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "smp:\n");
	tools_open_smp_data_print(&(ptr_struct->smp), fd, indent_level + 1);
}

unsigned int tools_open_IbMads_size(void)
{
	return TOOLS_OPEN_IBMADS_SIZE;
}

void tools_open_IbMads_dump(const union tools_open_IbMads *ptr_struct, FILE *fd)
{
	tools_open_IbMads_print(ptr_struct, fd, 0);
}

void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_phy_reg_pack(&(ptr_struct->PhyReg), ptr_buff);
}

void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_phy_reg_unpack(&(ptr_struct->PhyReg), ptr_buff);
}

void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_access_registers ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MNVReg:\n");
	tools_open_mnv_cfg_print(&(ptr_struct->MNVReg), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PhyReg:\n");
	tools_open_phy_reg_print(&(ptr_struct->PhyReg), fd, indent_level + 1);
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
	fprintf(fd, "aux_data_hdr:\n");
	tools_open_aux_data_hdr_print(&(ptr_struct->aux_data_hdr), fd, indent_level + 1);
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

void tools_open_mfa2_pack(const union tools_open_mfa2 *ptr_struct, u_int8_t *ptr_buff)
{
	tools_open_component_ptr_pack(&(ptr_struct->component_ptr), ptr_buff);
}

void tools_open_mfa2_unpack(union tools_open_mfa2 *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_component_ptr_unpack(&(ptr_struct->component_ptr), ptr_buff);
}

void tools_open_mfa2_print(const union tools_open_mfa2 *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_mfa2 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "common_header:\n");
	tools_open_common_header_print(&(ptr_struct->common_header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "multi_part:\n");
	tools_open_multi_part_print(&(ptr_struct->multi_part), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "package_descriptor:\n");
	tools_open_package_descriptor_print(&(ptr_struct->package_descriptor), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_desciptor:\n");
	tools_open_component_desciptor_print(&(ptr_struct->component_desciptor), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version:\n");
	tools_open_version_print(&(ptr_struct->version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_ptr:\n");
	tools_open_component_ptr_print(&(ptr_struct->component_ptr), fd, indent_level + 1);
}

unsigned int tools_open_mfa2_size(void)
{
	return TOOLS_OPEN_MFA2_SIZE;
}

void tools_open_mfa2_dump(const union tools_open_mfa2 *ptr_struct, FILE *fd)
{
	tools_open_mfa2_print(ptr_struct, fd, 0);
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
	tools_open_mfg_info_pack(&(ptr_struct->mfg_info), ptr_buff);
}

void tools_open_misc_structs_unpack(union tools_open_misc_structs *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_mfg_info_unpack(&(ptr_struct->mfg_info), ptr_buff);
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
	tools_open_nv_cx3_global_conf_pack(&(ptr_struct->nv_cx3_global_conf), ptr_buff);
}

void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_nv_cx3_global_conf_unpack(&(ptr_struct->nv_cx3_global_conf), ptr_buff);
}

void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== tools_open_nv_cfg ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wol:\n");
	tools_open_wol_print(&(ptr_struct->wol), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "infiniband_dc_capabilities:\n");
	tools_open_infiniband_dc_capabilities_print(&(ptr_struct->infiniband_dc_capabilities), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "infiniband_dc_settings:\n");
	tools_open_infiniband_dc_settings_print(&(ptr_struct->infiniband_dc_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tpt_capabilities:\n");
	tools_open_tpt_capabilities_print(&(ptr_struct->tpt_capabilities), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tpt_configuration:\n");
	tools_open_tpt_configuration_print(&(ptr_struct->tpt_configuration), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_capabilities:\n");
	tools_open_pci_capabilities_print(&(ptr_struct->pci_capabilities), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_configuration:\n");
	tools_open_pci_configuration_print(&(ptr_struct->pci_configuration), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_boot_state:\n");
	tools_open_port_boot_state_print(&(ptr_struct->port_boot_state), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iscsi_settings:\n");
	tools_open_iscsi_settings_print(&(ptr_struct->iscsi_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "infiniband_boot_settings:\n");
	tools_open_infiniband_boot_settings_print(&(ptr_struct->infiniband_boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_settings:\n");
	tools_open_boot_settings_print(&(ptr_struct->boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "preboot_boot_settings:\n");
	tools_open_preboot_boot_settings_print(&(ptr_struct->preboot_boot_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "preboot_flow_ctrl:\n");
	tools_open_preboot_flow_ctrl_print(&(ptr_struct->preboot_flow_ctrl), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sriov:\n");
	tools_open_sriov_print(&(ptr_struct->sriov), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bar_size:\n");
	tools_open_bar_size_print(&(ptr_struct->bar_size), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vpi_settings:\n");
	tools_open_vpi_settings_print(&(ptr_struct->vpi_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_v_1_5_next_protocol:\n");
	tools_open_roce_v_1_5_next_protocol_print(&(ptr_struct->roce_v_1_5_next_protocol), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_cc:\n");
	tools_open_roce_cc_print(&(ptr_struct->roce_cc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "roce_cc_ecn:\n");
	tools_open_roce_cc_ecn_print(&(ptr_struct->roce_cc_ecn), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb:\n");
	tools_open_lldp_nb_print(&(ptr_struct->lldp_nb), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "external_port:\n");
	tools_open_external_port_print(&(ptr_struct->external_port), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_settings_ext:\n");
	tools_open_boot_settings_ext_print(&(ptr_struct->boot_settings_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "option_rom_capability:\n");
	tools_open_option_rom_capability_print(&(ptr_struct->option_rom_capability), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qos:\n");
	tools_open_qos_print(&(ptr_struct->qos), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qos_cap:\n");
	tools_open_qos_cap_print(&(ptr_struct->qos_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_client_settings:\n");
	tools_open_lldp_client_settings_print(&(ptr_struct->lldp_client_settings), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_cap:\n");
	tools_open_lldp_nb_cap_print(&(ptr_struct->lldp_nb_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lldp_nb_dcbx:\n");
	tools_open_lldp_nb_dcbx_print(&(ptr_struct->lldp_nb_dcbx), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_base_mac_guid:\n");
	tools_open_nv_base_mac_guid_print(&(ptr_struct->nv_base_mac_guid), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_base_mac_guid_cap:\n");
	tools_open_nv_base_mac_guid_cap_print(&(ptr_struct->nv_base_mac_guid_cap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_cx3_global_conf:\n");
	tools_open_nv_cx3_global_conf_print(&(ptr_struct->nv_cx3_global_conf), fd, indent_level + 1);
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
	tools_open_mirc_reg_pack(&(ptr_struct->mirc_reg), ptr_buff);
}

void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t *ptr_buff)
{
	tools_open_mirc_reg_unpack(&(ptr_struct->mirc_reg), ptr_buff);
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
	fprintf(fd, "IbMads:\n");
	tools_open_IbMads_print(&(ptr_struct->IbMads), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfa2:\n");
	tools_open_mfa2_print(&(ptr_struct->mfa2), fd, indent_level + 1);
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

