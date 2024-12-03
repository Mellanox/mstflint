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
         *** This file was generated at "2024-12-03 14:42:17"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input [REDACTED]/user/tools_layouts/adb/prm/switch/ext/reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils -o [REDACTED]/user/tools_layouts
         ***/
#include "reg_access_switch_layouts.h"

void reg_access_switch_command_payload_ext_pack(const struct reg_access_switch_command_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 65; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_command_payload_ext_unpack(struct reg_access_switch_command_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 65; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 2080, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_command_payload_ext_print(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_command_payload_ext ========\n");

	for (i = 0; i < 65; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_command_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_COMMAND_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_command_payload_ext_dump(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_command_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_crspace_access_payload_ext_pack(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_crspace_access_payload_ext_unpack(struct reg_access_switch_crspace_access_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_crspace_access_payload_ext_print(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_crspace_access_payload_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_crspace_access_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_CRSPACE_ACCESS_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_crspace_access_payload_ext_dump(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_crspace_access_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_device_info_ext_pack(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_id);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lc_pwr_on);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->thermal_sd);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flash_owner);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->uses_flash);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_major);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_sub_minor);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_minor);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_cmd_write_size_supp);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_cmd_read_size_supp);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type_name[i]);
	}
}

void reg_access_switch_mddq_device_info_ext_unpack(struct reg_access_switch_mddq_device_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->flash_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 3;
	ptr_struct->lc_pwr_on = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->thermal_sd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->flash_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->uses_flash = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->device_type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->fw_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->fw_sub_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->fw_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 120;
	ptr_struct->max_cmd_write_size_supp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->max_cmd_read_size_supp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 256, 1);
		ptr_struct->device_type_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_mddq_device_info_ext_print(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_device_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_id             : " UH_FMT "\n", ptr_struct->flash_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lc_pwr_on            : " UH_FMT "\n", ptr_struct->lc_pwr_on);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "thermal_sd           : " UH_FMT "\n", ptr_struct->thermal_sd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_owner          : " UH_FMT "\n", ptr_struct->flash_owner);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uses_flash           : " UH_FMT "\n", ptr_struct->uses_flash);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_major             : " UH_FMT "\n", ptr_struct->fw_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_sub_minor         : " UH_FMT "\n", ptr_struct->fw_sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_minor             : " UH_FMT "\n", ptr_struct->fw_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cmd_write_size_supp : " UH_FMT "\n", ptr_struct->max_cmd_write_size_supp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cmd_read_size_supp : " UH_FMT "\n", ptr_struct->max_cmd_read_size_supp);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "device_type_name_%03d : " UH_FMT "\n", i, ptr_struct->device_type_name[i]);
	}
}

unsigned int reg_access_switch_mddq_device_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_DEVICE_INFO_EXT_SIZE;
}

void reg_access_switch_mddq_device_info_ext_dump(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_device_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_slot_info_ext_pack(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lc_ready);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sr_valid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->provisioned);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ini_file_version);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_revision);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->card_type);
}

void reg_access_switch_mddq_slot_info_ext_unpack(struct reg_access_switch_mddq_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->lc_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->sr_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->provisioned = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->ini_file_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->hw_revision = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 88;
	ptr_struct->card_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_mddq_slot_info_ext_print(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_slot_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lc_ready             : " UH_FMT "\n", ptr_struct->lc_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sr_valid             : " UH_FMT "\n", ptr_struct->sr_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "provisioned          : " UH_FMT "\n", ptr_struct->provisioned);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_version     : " UH_FMT "\n", ptr_struct->ini_file_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_revision          : " UH_FMT "\n", ptr_struct->hw_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "card_type            : " UH_FMT "\n", ptr_struct->card_type);
}

unsigned int reg_access_switch_mddq_slot_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_SLOT_INFO_EXT_SIZE;
}

void reg_access_switch_mddq_slot_info_ext_dump(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_slot_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_slot_name_ext_pack(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->slot_ascii_name[i]);
	}
}

void reg_access_switch_mddq_slot_name_ext_unpack(struct reg_access_switch_mddq_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->slot_ascii_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_mddq_slot_name_ext_print(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_slot_name_ext ========\n");

	for (i = 0; i < 20; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_ascii_name_%03d : " UH_FMT "\n", i, ptr_struct->slot_ascii_name[i]);
	}
}

unsigned int reg_access_switch_mddq_slot_name_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_SLOT_NAME_EXT_SIZE;
}

void reg_access_switch_mddq_slot_name_ext_dump(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_slot_name_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_prm_register_payload_ext_pack(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->register_id);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->method);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->register_data[i]);
	}
}

void reg_access_switch_prm_register_payload_ext_unpack(struct reg_access_switch_prm_register_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->register_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->method = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		ptr_struct->register_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_prm_register_payload_ext_print(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_prm_register_payload_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "register_id          : " UH_FMT "\n", ptr_struct->register_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "method               : " UH_FMT "\n", ptr_struct->method);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "register_data_%03d   : " U32H_FMT "\n", i, ptr_struct->register_data[i]);
	}
}

unsigned int reg_access_switch_prm_register_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_PRM_REGISTER_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_prm_register_payload_ext_dump(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_prm_register_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_lane_2_module_mapping_ext_pack(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_lane_2_module_mapping_ext_unpack(struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_lane_2_module_mapping_ext_print(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_lane_2_module_mapping_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lane              : " UH_FMT "\n", ptr_struct->tx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_lane              : " UH_FMT "\n", ptr_struct->rx_lane);
}

unsigned int reg_access_switch_lane_2_module_mapping_ext_size(void)
{
	return REG_ACCESS_SWITCH_LANE_2_MODULE_MAPPING_EXT_SIZE;
}

void reg_access_switch_lane_2_module_mapping_ext_dump(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_lane_2_module_mapping_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_mddq_slot_name_ext_pack(&(ptr_struct->mddq_slot_name_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_mddq_slot_name_ext_unpack(&(ptr_struct->mddq_slot_name_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_device_info_ext:\n");
	reg_access_switch_mddq_device_info_ext_print(&(ptr_struct->mddq_device_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_slot_info_ext:\n");
	reg_access_switch_mddq_slot_info_ext_print(&(ptr_struct->mddq_slot_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_slot_name_ext:\n");
	reg_access_switch_mddq_slot_name_ext_print(&(ptr_struct->mddq_slot_name_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_mddq_data_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_DATA_AUTO_EXT_SIZE;
}

void reg_access_switch_mddq_data_auto_ext_dump(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddt_reg_payload_auto_ext_pack(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_prm_register_payload_ext_pack(&(ptr_struct->prm_register_payload_ext), ptr_buff);
}

void reg_access_switch_mddt_reg_payload_auto_ext_unpack(union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_prm_register_payload_ext_unpack(&(ptr_struct->prm_register_payload_ext), ptr_buff);
}

void reg_access_switch_mddt_reg_payload_auto_ext_print(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddt_reg_payload_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "command_payload_ext:\n");
	reg_access_switch_command_payload_ext_print(&(ptr_struct->command_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crspace_access_payload_ext:\n");
	reg_access_switch_crspace_access_payload_ext_print(&(ptr_struct->crspace_access_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prm_register_payload_ext:\n");
	reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->prm_register_payload_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_mddt_reg_payload_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDT_REG_PAYLOAD_AUTO_EXT_SIZE;
}

void reg_access_switch_mddt_reg_payload_auto_ext_dump(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddt_reg_payload_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void reg_access_switch_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int reg_access_switch_uint64_size(void)
{
	return REG_ACCESS_SWITCH_UINT64_SIZE;
}

void reg_access_switch_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	reg_access_switch_uint64_print(ptr_struct, fd, 0);
}

void reg_access_switch_PPCR_ext_pack(const struct reg_access_switch_PPCR_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->aggregated_port);
	offset = 77;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->plane);
	offset = 69;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->split);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_planes);
	offset = 109;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->p_type);
}

void reg_access_switch_PPCR_ext_unpack(struct reg_access_switch_PPCR_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->aggregated_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 77;
	ptr_struct->plane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 69;
	ptr_struct->split = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 120;
	ptr_struct->num_of_planes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 109;
	ptr_struct->p_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_switch_PPCR_ext_print(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_PPCR_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aggregated_port      : " UH_FMT "\n", ptr_struct->aggregated_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane                : " UH_FMT "\n", ptr_struct->plane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split                : " UH_FMT "\n", ptr_struct->split);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_planes        : " UH_FMT "\n", ptr_struct->num_of_planes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p_type               : " UH_FMT "\n", ptr_struct->p_type);
}

unsigned int reg_access_switch_PPCR_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCR_EXT_SIZE;
}

void reg_access_switch_PPCR_ext_dump(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_PPCR_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_icam_reg_ext_pack(const struct reg_access_switch_icam_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 192, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->infr_access_reg_cap_mask[i]);
	}
}

void reg_access_switch_icam_reg_ext_unpack(struct reg_access_switch_icam_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 192, 1);
		ptr_struct->infr_access_reg_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_icam_reg_ext_print(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_icam_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : " UH_FMT "\n", ptr_struct->access_reg_group);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "infr_access_reg_cap_mask_%03d : " U32H_FMT "\n", i, ptr_struct->infr_access_reg_cap_mask[i]);
	}
}

unsigned int reg_access_switch_icam_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_ICAM_REG_EXT_SIZE;
}

void reg_access_switch_icam_reg_ext_dump(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_icam_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_icsr_ext_pack(const struct reg_access_switch_icsr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->base_address);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->num_reads);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 8320, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_icsr_ext_unpack(struct reg_access_switch_icsr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	ptr_struct->base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 87;
	ptr_struct->num_reads = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 8320, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_icsr_ext_print(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_icsr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_address         : " U32H_FMT "\n", ptr_struct->base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_reads            : " UH_FMT "\n", ptr_struct->num_reads);
	for (i = 0; i < 256; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_icsr_ext_size(void)
{
	return REG_ACCESS_SWITCH_ICSR_EXT_SIZE;
}

void reg_access_switch_icsr_ext_dump(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_icsr_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_ext_pack(const struct reg_access_switch_mddq_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->query_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sie);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->request_message_sequence);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->response_message_sequence);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->query_index);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->data_valid);
	offset = 128;
	switch (ptr_struct->query_type) {
	case 0x2:
		offset = 128;
		reg_access_switch_mddq_device_info_ext_pack(&(ptr_struct->data.mddq_device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_mddq_slot_info_ext_pack(&(ptr_struct->data.mddq_slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_mddq_slot_name_ext_pack(&(ptr_struct->data.mddq_slot_name_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddq_ext_unpack(struct reg_access_switch_mddq_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->query_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->sie = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->request_message_sequence = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->response_message_sequence = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->query_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->data_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	switch (ptr_struct->query_type) {
	case 0x2:
		offset = 128;
		reg_access_switch_mddq_device_info_ext_unpack(&(ptr_struct->data.mddq_device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_mddq_slot_info_ext_unpack(&(ptr_struct->data.mddq_slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_mddq_slot_name_ext_unpack(&(ptr_struct->data.mddq_slot_name_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddq_ext_print(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_type           : %s (" UH_FMT ")\n", (ptr_struct->query_type == 0 ? ("Reserved") : ((ptr_struct->query_type == 1 ? ("slot_info") : ((ptr_struct->query_type == 2 ? ("device_info") : ((ptr_struct->query_type == 3 ? ("slot_name") : ("unknown")))))))), ptr_struct->query_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sie                  : " UH_FMT "\n", ptr_struct->sie);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "request_message_sequence : " UH_FMT "\n", ptr_struct->request_message_sequence);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "response_message_sequence : " UH_FMT "\n", ptr_struct->response_message_sequence);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_index          : " UH_FMT "\n", ptr_struct->query_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_valid           : " UH_FMT "\n", ptr_struct->data_valid);
	switch (ptr_struct->query_type) {
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_device_info_ext:\n");
		reg_access_switch_mddq_device_info_ext_print(&(ptr_struct->data.mddq_device_info_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_slot_info_ext:\n");
		reg_access_switch_mddq_slot_info_ext_print(&(ptr_struct->data.mddq_slot_info_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_slot_name_ext:\n");
		reg_access_switch_mddq_slot_name_ext_print(&(ptr_struct->data.mddq_slot_name_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_mddq_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_EXT_SIZE;
}

void reg_access_switch_mddq_ext_dump(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddt_reg_ext_pack(const struct reg_access_switch_mddt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_index);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->type);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->write_size);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->read_size);
	offset = 96;
	switch (ptr_struct->type) {
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_pack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_pack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_pack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddt_reg_ext_unpack(struct reg_access_switch_mddt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 62;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 40;
	ptr_struct->write_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->read_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	switch (ptr_struct->type) {
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_unpack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_unpack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_unpack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddt_reg_ext_print(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("PRM_Register") : ((ptr_struct->type == 1 ? ("Command") : ((ptr_struct->type == 2 ? ("CrSpace_access") : ("unknown")))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "write_size           : " UH_FMT "\n", ptr_struct->write_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_size            : " UH_FMT "\n", ptr_struct->read_size);
	switch (ptr_struct->type) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "command_payload_ext:\n");
		reg_access_switch_command_payload_ext_print(&(ptr_struct->payload.command_payload_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "crspace_access_payload_ext:\n");
		reg_access_switch_crspace_access_payload_ext_print(&(ptr_struct->payload.crspace_access_payload_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "prm_register_payload_ext:\n");
		reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->payload.prm_register_payload_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_mddt_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDT_REG_EXT_SIZE;
}

void reg_access_switch_mddt_reg_ext_dump(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mdsr_reg_ext_pack(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->additional_info);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_of_token);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->end);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_left);
}

void reg_access_switch_mdsr_reg_ext_unpack(struct reg_access_switch_mdsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->additional_info = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->type_of_token = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->end = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->time_left = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mdsr_reg_ext_print(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mdsr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "additional_info      : " UH_FMT "\n", ptr_struct->additional_info);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_of_token        : " UH_FMT "\n", ptr_struct->type_of_token);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "end                  : " UH_FMT "\n", ptr_struct->end);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_left            : " U32H_FMT "\n", ptr_struct->time_left);
}

unsigned int reg_access_switch_mdsr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDSR_REG_EXT_SIZE;
}

void reg_access_switch_mdsr_reg_ext_dump(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mdsr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mfmc_reg_ext_pack(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_mfmc_reg_ext_unpack(struct reg_access_switch_mfmc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_mfmc_reg_ext_print(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mfmc_reg_ext ========\n");

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

unsigned int reg_access_switch_mfmc_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MFMC_REG_EXT_SIZE;
}

void reg_access_switch_mfmc_reg_ext_dump(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mfmc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mkdc_reg_ext_pack(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_code);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->session_id);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->current_keep_alive_counter);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->next_keep_alive_counter);
}

void reg_access_switch_mkdc_reg_ext_unpack(struct reg_access_switch_mkdc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->session_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->current_keep_alive_counter = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->next_keep_alive_counter = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mkdc_reg_ext_print(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mkdc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code           : %s (" UH_FMT ")\n", (ptr_struct->error_code == 0 ? ("OK") : ((ptr_struct->error_code == 1 ? ("BAD_SESSION_ID") : ((ptr_struct->error_code == 2 ? ("BAD_KEEP_ALIVE_COUNTER") : ((ptr_struct->error_code == 3 ? ("BAD_SOURCE_ADDRESS") : ((ptr_struct->error_code == 4 ? ("SESSION_TIMEOUT") : ("unknown")))))))))), ptr_struct->error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "session_id           : " UH_FMT "\n", ptr_struct->session_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_keep_alive_counter : " U32H_FMT "\n", ptr_struct->current_keep_alive_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "next_keep_alive_counter : " U32H_FMT "\n", ptr_struct->next_keep_alive_counter);
}

unsigned int reg_access_switch_mkdc_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MKDC_REG_EXT_SIZE;
}

void reg_access_switch_mkdc_reg_ext_dump(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mkdc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mpir_ext_pack(const struct reg_access_switch_mpir_ext *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sdm);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->subordinate_bus);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->secondary_bus);
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
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->slot_cap);
}

void reg_access_switch_mpir_ext_unpack(struct reg_access_switch_mpir_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 0;
	ptr_struct->sdm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->subordinate_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->secondary_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
	offset = 96;
	ptr_struct->slot_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_mpir_ext_print(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mpir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_buses           : " UH_FMT "\n", ptr_struct->host_buses);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdm                  : " UH_FMT "\n", ptr_struct->sdm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subordinate_bus      : " UH_FMT "\n", ptr_struct->subordinate_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary_bus        : " UH_FMT "\n", ptr_struct->secondary_bus);
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
	fprintf(fd, "slot_cap             : " UH_FMT "\n", ptr_struct->slot_cap);
}

unsigned int reg_access_switch_mpir_ext_size(void)
{
	return REG_ACCESS_SWITCH_MPIR_EXT_SIZE;
}

void reg_access_switch_mpir_ext_dump(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mpir_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mrsr_ext_pack(const struct reg_access_switch_mrsr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->command);
}

void reg_access_switch_mrsr_ext_unpack(struct reg_access_switch_mrsr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->command = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mrsr_ext_print(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mrsr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "command              : " UH_FMT "\n", ptr_struct->command);
}

unsigned int reg_access_switch_mrsr_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRSR_EXT_SIZE;
}

void reg_access_switch_mrsr_ext_dump(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mrsr_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_msgi_ext_pack(const struct reg_access_switch_msgi_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_msgi_ext_unpack(struct reg_access_switch_msgi_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_msgi_ext_print(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_msgi_ext ========\n");

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

unsigned int reg_access_switch_msgi_ext_size(void)
{
	return REG_ACCESS_SWITCH_MSGI_EXT_SIZE;
}

void reg_access_switch_msgi_ext_dump(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_msgi_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mspmer_ext_pack(const struct reg_access_switch_mspmer_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_index);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clr);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->prev_en);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_physical_monitor);
	offset = 188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fmon_ctr);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vmon_ctr);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->scpm_ctr);
	offset = 179;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->general_err);
}

void reg_access_switch_mspmer_ext_unpack(struct reg_access_switch_mspmer_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 47;
	ptr_struct->clr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 39;
	ptr_struct->prev_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->supported_physical_monitor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 188;
	ptr_struct->fmon_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 184;
	ptr_struct->vmon_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 180;
	ptr_struct->scpm_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 179;
	ptr_struct->general_err = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_mspmer_ext_print(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mspmer_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr                  : " UH_FMT "\n", ptr_struct->clr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prev_en              : " UH_FMT "\n", ptr_struct->prev_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported_physical_monitor : " U32H_FMT "\n", ptr_struct->supported_physical_monitor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fmon_ctr             : " UH_FMT "\n", ptr_struct->fmon_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vmon_ctr             : " UH_FMT "\n", ptr_struct->vmon_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "scpm_ctr             : " UH_FMT "\n", ptr_struct->scpm_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "general_err          : " UH_FMT "\n", ptr_struct->general_err);
}

unsigned int reg_access_switch_mspmer_ext_size(void)
{
	return REG_ACCESS_SWITCH_MSPMER_EXT_SIZE;
}

void reg_access_switch_mspmer_ext_dump(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mspmer_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mtcq_reg_ext_pack(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->token_opcode);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->keypair_uuid[i]);
	}
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->base_mac);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(224, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 376;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_version_39_32);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_version_31_0);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->source_address[i]);
	}
	offset = 560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->session_id);
	offset = 544;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->challenge_version);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->challenge[i]);
	}
}

void reg_access_switch_mtcq_reg_ext_unpack(struct reg_access_switch_mtcq_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 8;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->token_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 896, 1);
		ptr_struct->keypair_uuid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 160;
	ptr_struct->base_mac = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(224, 32, i, 896, 1);
		ptr_struct->psid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 376;
	ptr_struct->fw_version_39_32 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 384;
	ptr_struct->fw_version_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 896, 1);
		ptr_struct->source_address[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 560;
	ptr_struct->session_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 544;
	ptr_struct->challenge_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 896, 1);
		ptr_struct->challenge[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_mtcq_reg_ext_print(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mtcq_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "token_opcode         : " UH_FMT "\n", ptr_struct->token_opcode);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "keypair_uuid_%03d    : " U32H_FMT "\n", i, ptr_struct->keypair_uuid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_mac             : " U64H_FMT "\n", ptr_struct->base_mac);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "psid_%03d            : " U32H_FMT "\n", i, ptr_struct->psid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version_39_32     : " UH_FMT "\n", ptr_struct->fw_version_39_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version_31_0      : " U32H_FMT "\n", ptr_struct->fw_version_31_0);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "source_address_%03d  : " U32H_FMT "\n", i, ptr_struct->source_address[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "session_id           : " UH_FMT "\n", ptr_struct->session_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "challenge_version    : " UH_FMT "\n", ptr_struct->challenge_version);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "challenge_%03d       : " U32H_FMT "\n", i, ptr_struct->challenge[i]);
	}
}

unsigned int reg_access_switch_mtcq_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MTCQ_REG_EXT_SIZE;
}

void reg_access_switch_mtcq_reg_ext_dump(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mtcq_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pguid_reg_ext_pack(const struct reg_access_switch_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_pguid_reg_ext_unpack(struct reg_access_switch_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_pguid_reg_ext_print(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pguid_reg_ext ========\n");

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

unsigned int reg_access_switch_pguid_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PGUID_REG_EXT_SIZE;
}

void reg_access_switch_pguid_reg_ext_dump(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pguid_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_plib_reg_ext_pack(const struct reg_access_switch_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->ib_port);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_num);
}

void reg_access_switch_plib_reg_ext_unpack(struct reg_access_switch_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->ib_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->split_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_plib_reg_ext_print(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_plib_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_port              : " UH_FMT "\n", ptr_struct->ib_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_num            : " UH_FMT "\n", ptr_struct->split_num);
}

unsigned int reg_access_switch_plib_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PLIB_REG_EXT_SIZE;
}

void reg_access_switch_plib_reg_ext_dump(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_plib_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pllp_reg_ext_pack(const struct reg_access_switch_pllp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->label_port);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_num);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ipil_num);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_stat);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ipil_stat);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_num);
	offset = 125;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->conn_type);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rmt_id);
	offset = 111;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_fnm);
	offset = 110;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->maf);
	offset = 157;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->protocol);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->resource_label_port);
}

void reg_access_switch_pllp_reg_ext_unpack(struct reg_access_switch_pllp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->label_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->split_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->ipil_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 44;
	ptr_struct->split_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->ipil_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->slot_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 125;
	ptr_struct->conn_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 112;
	ptr_struct->rmt_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 111;
	ptr_struct->is_fnm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 110;
	ptr_struct->maf = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 157;
	ptr_struct->protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 176;
	ptr_struct->resource_label_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pllp_reg_ext_print(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pllp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "label_port           : " UH_FMT "\n", ptr_struct->label_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_num            : " UH_FMT "\n", ptr_struct->split_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipil_num             : " UH_FMT "\n", ptr_struct->ipil_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_stat           : " UH_FMT "\n", ptr_struct->split_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipil_stat            : " UH_FMT "\n", ptr_struct->ipil_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_num             : " UH_FMT "\n", ptr_struct->slot_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "conn_type            : " UH_FMT "\n", ptr_struct->conn_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rmt_id               : " UH_FMT "\n", ptr_struct->rmt_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_fnm               : " UH_FMT "\n", ptr_struct->is_fnm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "maf                  : " UH_FMT "\n", ptr_struct->maf);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "protocol             : " UH_FMT "\n", ptr_struct->protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_label_port  : " UH_FMT "\n", ptr_struct->resource_label_port);
}

unsigned int reg_access_switch_pllp_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PLLP_REG_EXT_SIZE;
}

void reg_access_switch_pllp_reg_ext_dump(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pllp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmaos_reg_ext_pack(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_pmaos_reg_ext_unpack(struct reg_access_switch_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_pmaos_reg_ext_print(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmaos_reg_ext ========\n");

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

unsigned int reg_access_switch_pmaos_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMAOS_REG_EXT_SIZE;
}

void reg_access_switch_pmaos_reg_ext_dump(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmlp_reg_ext_pack(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
		reg_access_switch_lane_2_module_mapping_ext_pack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pmlp_reg_ext_unpack(struct reg_access_switch_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
		reg_access_switch_lane_2_module_mapping_ext_unpack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pmlp_reg_ext_print(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmlp_reg_ext ========\n");

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
		reg_access_switch_lane_2_module_mapping_ext_print(&(ptr_struct->lane_module_mapping[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_pmlp_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMLP_REG_EXT_SIZE;
}

void reg_access_switch_pmlp_reg_ext_dump(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmlp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_reg_access_switch_Nodes_pack(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_icsr_ext_pack(&(ptr_struct->icsr_ext), ptr_buff);
}

void reg_access_switch_reg_access_switch_Nodes_unpack(union reg_access_switch_reg_access_switch_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_icsr_ext_unpack(&(ptr_struct->icsr_ext), ptr_buff);
}

void reg_access_switch_reg_access_switch_Nodes_print(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_reg_access_switch_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfmc_reg_ext:\n");
	reg_access_switch_mfmc_reg_ext_print(&(ptr_struct->mfmc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_switch_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mrsr_ext:\n");
	reg_access_switch_mrsr_ext_print(&(ptr_struct->mrsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mspmer_ext:\n");
	reg_access_switch_mspmer_ext_print(&(ptr_struct->mspmer_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PPCR_ext:\n");
	reg_access_switch_PPCR_ext_print(&(ptr_struct->PPCR_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plib_reg_ext:\n");
	reg_access_switch_plib_reg_ext_print(&(ptr_struct->plib_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcq_reg_ext:\n");
	reg_access_switch_mtcq_reg_ext_print(&(ptr_struct->mtcq_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpir_ext:\n");
	reg_access_switch_mpir_ext_print(&(ptr_struct->mpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icam_reg_ext:\n");
	reg_access_switch_icam_reg_ext_print(&(ptr_struct->icam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pguid_reg_ext:\n");
	reg_access_switch_pguid_reg_ext_print(&(ptr_struct->pguid_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkdc_reg_ext:\n");
	reg_access_switch_mkdc_reg_ext_print(&(ptr_struct->mkdc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_ext:\n");
	reg_access_switch_mddq_ext_print(&(ptr_struct->mddq_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdsr_reg_ext:\n");
	reg_access_switch_mdsr_reg_ext_print(&(ptr_struct->mdsr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "msgi_ext:\n");
	reg_access_switch_msgi_ext_print(&(ptr_struct->msgi_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pllp_reg_ext:\n");
	reg_access_switch_pllp_reg_ext_print(&(ptr_struct->pllp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icsr_ext:\n");
	reg_access_switch_icsr_ext_print(&(ptr_struct->icsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddt_reg_ext:\n");
	reg_access_switch_mddt_reg_ext_print(&(ptr_struct->mddt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_switch_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_reg_access_switch_Nodes_size(void)
{
	return REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE;
}

void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd)
{
	reg_access_switch_reg_access_switch_Nodes_print(ptr_struct, fd, 0);
}

