
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
         *** This file was generated at "2025-12-21 15:54:24"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/prm/switch/ext/reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils
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
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->sub_module);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_lane);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_lane);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mode_b_map);
}

void reg_access_switch_lane_2_module_mapping_ext_unpack(struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->tx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->rx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1;
	ptr_struct->mode_b_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lane              : " UH_FMT "\n", ptr_struct->tx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_lane              : " UH_FMT "\n", ptr_struct->rx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode_b_map           : " UH_FMT "\n", ptr_struct->mode_b_map);
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

void reg_access_switch_mgpir_hw_info_ext_pack(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_devices);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules_per_system);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->devices_per_flash);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_slots);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_modules_per_slot);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_resource_modules);
	offset = 76;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_lanes_per_sub_module);
	offset = 68;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_sub_modules_index);
}

void reg_access_switch_mgpir_hw_info_ext_unpack(struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->num_of_devices = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->num_of_modules_per_system = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->devices_per_flash = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->num_of_modules = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->num_of_slots = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->max_modules_per_slot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->num_of_resource_modules = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 76;
	ptr_struct->num_lanes_per_sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 68;
	ptr_struct->max_sub_modules_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mgpir_hw_info_ext_print(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mgpir_hw_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_devices       : " UH_FMT "\n", ptr_struct->num_of_devices);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules_per_system : " UH_FMT "\n", ptr_struct->num_of_modules_per_system);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "devices_per_flash    : " UH_FMT "\n", ptr_struct->devices_per_flash);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules       : " UH_FMT "\n", ptr_struct->num_of_modules);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_slots         : " UH_FMT "\n", ptr_struct->num_of_slots);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_modules_per_slot : " UH_FMT "\n", ptr_struct->max_modules_per_slot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_resource_modules : " UH_FMT "\n", ptr_struct->num_of_resource_modules);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_lanes_per_sub_module : " UH_FMT "\n", ptr_struct->num_lanes_per_sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_sub_modules_index : " UH_FMT "\n", ptr_struct->max_sub_modules_index);
}

unsigned int reg_access_switch_mgpir_hw_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MGPIR_HW_INFO_EXT_SIZE;
}

void reg_access_switch_mgpir_hw_info_ext_dump(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mgpir_hw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mmta_tec_power_ext_pack(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cooling_level);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->temp_unit);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtpr);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtpe);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_tec_power);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_warning_low);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_warning_high);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_alarm_low);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_alarm_high);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_set_point_temperature);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_warning_low);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_warning_high);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_alarm_low);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_alarm_high);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->min_cooling_level);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_cooling_level);
}

void reg_access_switch_mmta_tec_power_ext_unpack(struct reg_access_switch_mmta_tec_power_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 2;
	ptr_struct->temp_unit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->mtpr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->mtpe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->tec_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->max_tec_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->tec_power_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->tec_power_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->tec_power_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->tec_power_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->set_point_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->max_set_point_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 176;
	ptr_struct->set_point_temperature_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->set_point_temperature_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 208;
	ptr_struct->set_point_temperature_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->set_point_temperature_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 240;
	ptr_struct->min_cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->max_cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mmta_tec_power_ext_print(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_tec_power_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cooling_level        : " UH_FMT "\n", ptr_struct->cooling_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temp_unit            : " UH_FMT "\n", ptr_struct->temp_unit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtpr                 : " UH_FMT "\n", ptr_struct->mtpr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtpe                 : " UH_FMT "\n", ptr_struct->mtpe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power            : " UH_FMT "\n", ptr_struct->tec_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_tec_power        : " UH_FMT "\n", ptr_struct->max_tec_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_warning_low : " UH_FMT "\n", ptr_struct->tec_power_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_warning_high : " UH_FMT "\n", ptr_struct->tec_power_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_alarm_low  : " UH_FMT "\n", ptr_struct->tec_power_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_alarm_high : " UH_FMT "\n", ptr_struct->tec_power_alarm_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature : " UH_FMT "\n", ptr_struct->set_point_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_set_point_temperature : " UH_FMT "\n", ptr_struct->max_set_point_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_warning_low : " UH_FMT "\n", ptr_struct->set_point_temperature_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_warning_high : " UH_FMT "\n", ptr_struct->set_point_temperature_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_alarm_low : " UH_FMT "\n", ptr_struct->set_point_temperature_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_alarm_high : " UH_FMT "\n", ptr_struct->set_point_temperature_alarm_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_cooling_level    : " UH_FMT "\n", ptr_struct->min_cooling_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cooling_level    : " UH_FMT "\n", ptr_struct->max_cooling_level);
}

unsigned int reg_access_switch_mmta_tec_power_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_TEC_POWER_EXT_SIZE;
}

void reg_access_switch_mmta_tec_power_ext_dump(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_tec_power_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mmta_temprature_ext_pack(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->temp_unit);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->twee);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->twe);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtr);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mte);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_temperature);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_warning_low);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_warning_high);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_alarm_low);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_alarm_high);
}

void reg_access_switch_mmta_temprature_ext_unpack(struct reg_access_switch_mmta_temprature_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 5;
	ptr_struct->temp_unit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->twee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 2;
	ptr_struct->twe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->mtr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->mte = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->max_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->temperature_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->temperature_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->temperature_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->temperature_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mmta_temprature_ext_print(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_temprature_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temp_unit            : " UH_FMT "\n", ptr_struct->temp_unit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "twee                 : %s (" UH_FMT ")\n", (ptr_struct->twee == 0 ? ("do_not_generate_event") : ((ptr_struct->twee == 1 ? ("generate_events") : ((ptr_struct->twee == 2 ? ("generate_single_event") : ("unknown")))))), ptr_struct->twee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "twe                  : " UH_FMT "\n", ptr_struct->twe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtr                  : " UH_FMT "\n", ptr_struct->mtr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mte                  : " UH_FMT "\n", ptr_struct->mte);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_temperature      : " UH_FMT "\n", ptr_struct->max_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_warning_low : " UH_FMT "\n", ptr_struct->temperature_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_warning_high : " UH_FMT "\n", ptr_struct->temperature_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_alarm_low : " UH_FMT "\n", ptr_struct->temperature_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_alarm_high : " UH_FMT "\n", ptr_struct->temperature_alarm_high);
}

unsigned int reg_access_switch_mmta_temprature_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_TEMPRATURE_EXT_SIZE;
}

void reg_access_switch_mmta_temprature_ext_dump(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_temprature_ext_print(ptr_struct, fd, 0);
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
	*ptr_struct = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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

void reg_access_switch_MMAM_ext_pack(const struct reg_access_switch_MMAM_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ga);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_module);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_type);
}

void reg_access_switch_MMAM_ext_unpack(struct reg_access_switch_MMAM_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->ga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 88;
	ptr_struct->local_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->module_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_MMAM_ext_print(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MMAM_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ga                   : " UH_FMT "\n", ptr_struct->ga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_module         : " UH_FMT "\n", ptr_struct->local_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_type          : " UH_FMT "\n", ptr_struct->module_type);
}

unsigned int reg_access_switch_MMAM_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMAM_EXT_SIZE;
}

void reg_access_switch_MMAM_ext_dump(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MMAM_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_PPCR_ext_pack(const struct reg_access_switch_PPCR_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->asymmetry_enable);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->asymmetry_enable_supported);
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
	offset = 33;
	ptr_struct->asymmetry_enable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->asymmetry_enable_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "asymmetry_enable     : " UH_FMT "\n", ptr_struct->asymmetry_enable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "asymmetry_enable_supported : " UH_FMT "\n", ptr_struct->asymmetry_enable_supported);
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
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->revoke_version);
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
	offset = 33;
	ptr_struct->revoke_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "revoke_version       : " UH_FMT "\n", ptr_struct->revoke_version);
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

void reg_access_switch_mgpir_ext_pack(const struct reg_access_switch_mgpir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_mgpir_hw_info_ext_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
}

void reg_access_switch_mgpir_ext_unpack(struct reg_access_switch_mgpir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_mgpir_hw_info_ext_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
}

void reg_access_switch_mgpir_ext_print(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mgpir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	reg_access_switch_mgpir_hw_info_ext_print(&(ptr_struct->hw_info), fd, indent_level + 1);
}

unsigned int reg_access_switch_mgpir_ext_size(void)
{
	return REG_ACCESS_SWITCH_MGPIR_EXT_SIZE;
}

void reg_access_switch_mgpir_ext_dump(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mgpir_ext_print(ptr_struct, fd, 0);
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

void reg_access_switch_mmta_reg_ext_pack(const struct reg_access_switch_mmta_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_measurements);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_name_hi);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_name_lo);
	offset = 96;
	reg_access_switch_mmta_temprature_ext_pack(&(ptr_struct->module_temperature), ptr_buff + offset / 8);
	offset = 288;
	reg_access_switch_mmta_tec_power_ext_pack(&(ptr_struct->module_tec_power), ptr_buff + offset / 8);
	offset = 544;
	reg_access_switch_mmta_temprature_ext_pack(&(ptr_struct->module_second_temperature), ptr_buff + offset / 8);
}

void reg_access_switch_mmta_reg_ext_unpack(struct reg_access_switch_mmta_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->supported_measurements = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->module_name_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->module_name_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	reg_access_switch_mmta_temprature_ext_unpack(&(ptr_struct->module_temperature), ptr_buff + offset / 8);
	offset = 288;
	reg_access_switch_mmta_tec_power_ext_unpack(&(ptr_struct->module_tec_power), ptr_buff + offset / 8);
	offset = 544;
	reg_access_switch_mmta_temprature_ext_unpack(&(ptr_struct->module_second_temperature), ptr_buff + offset / 8);
}

void reg_access_switch_mmta_reg_ext_print(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported_measurements : " UH_FMT "\n", ptr_struct->supported_measurements);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_name_hi       : " U32H_FMT "\n", ptr_struct->module_name_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_name_lo       : " U32H_FMT "\n", ptr_struct->module_name_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_temperature:\n");
	reg_access_switch_mmta_temprature_ext_print(&(ptr_struct->module_temperature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_tec_power:\n");
	reg_access_switch_mmta_tec_power_ext_print(&(ptr_struct->module_tec_power), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_second_temperature:\n");
	reg_access_switch_mmta_temprature_ext_print(&(ptr_struct->module_second_temperature), fd, indent_level + 1);
}

unsigned int reg_access_switch_mmta_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_REG_EXT_SIZE;
}

void reg_access_switch_mmta_reg_ext_dump(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mpein_reg_ext_pack(const struct reg_access_switch_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 222;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cmn_clk_mode);
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

void reg_access_switch_mpein_reg_ext_unpack(struct reg_access_switch_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 222;
	ptr_struct->cmn_clk_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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

void reg_access_switch_mpein_reg_ext_print(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mpein_reg_ext ========\n");

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
	fprintf(fd, "cmn_clk_mode         : " UH_FMT "\n", ptr_struct->cmn_clk_mode);
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

unsigned int reg_access_switch_mpein_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MPEIN_REG_EXT_SIZE;
}

void reg_access_switch_mpein_reg_ext_dump(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mpein_reg_ext_print(ptr_struct, fd, 0);
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
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->segment_valid);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->segment_cap);
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
	ptr_struct->segment_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 38;
	ptr_struct->segment_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
	fprintf(fd, "segment_valid        : " UH_FMT "\n", ptr_struct->segment_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_cap          : " UH_FMT "\n", ptr_struct->segment_cap);
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
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->token_ratchet);
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
	ptr_struct->base_mac = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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
	offset = 832;
	ptr_struct->token_ratchet = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "token_ratchet        : " U64H_FMT "\n", ptr_struct->token_ratchet);
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
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->resource_label_port);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_identifier);
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
	offset = 136;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 176;
	ptr_struct->resource_label_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->oe_identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
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
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_label_port  : " UH_FMT "\n", ptr_struct->resource_label_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_identifier        : " UH_FMT "\n", ptr_struct->oe_identifier);
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

unsigned int reg_access_switch_pmaos_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMAOS_REG_EXT_SIZE;
}

void reg_access_switch_pmaos_reg_ext_dump(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmdr_reg_ext_pack(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->width_valid);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mcm_tile_valid);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->gb_valid);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pport_msb);
	offset = 49;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->cluster);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pport);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_port);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_lane_mask);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 69;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->split);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->gb_dp_num);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_query_msb);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lbp_query_msb);
	offset = 122;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tile_pport_msb);
	offset = 118;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_width);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port_query);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->label_port_query);
	offset = 153;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->gearbox_die_num);
	offset = 147;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->tile_pport);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pll_cnt_rx);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mcm_tile_num);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tile_cluster);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 189;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane0_physical_rx);
	offset = 186;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane1_physical_rx);
	offset = 183;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane2_physical_rx);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane3_physical_rx);
	offset = 177;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane4_physical_rx);
	offset = 174;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane5_physical_rx);
	offset = 171;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane6_physical_rx);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane7_physical_rx);
	offset = 165;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pll_cnt_tx);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->vl_num);
	offset = 221;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane0_physical_tx);
	offset = 218;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane1_physical_tx);
	offset = 215;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane2_physical_tx);
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane3_physical_tx);
	offset = 209;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane4_physical_tx);
	offset = 206;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane5_physical_tx);
	offset = 203;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane6_physical_tx);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane7_physical_tx);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pll_index);
	offset = 252;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL0_lane_map);
	offset = 248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL1_lane_map);
	offset = 244;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL2_lane_map);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL3_lane_map);
	offset = 236;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL4_lane_map);
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL5_lane_map);
	offset = 228;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL6_lane_map);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL7_lane_map);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL8_lane_map);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL9_lane_map);
	offset = 276;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL10_lane_map);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL11_lane_map);
	offset = 268;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL12_lane_map);
	offset = 264;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL13_lane_map);
	offset = 260;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL14_lane_map);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL15_lane_map);
	offset = 316;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL16_lane_map);
	offset = 312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL17_lane_map);
	offset = 308;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL18_lane_map);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL19_lane_map);
	offset = 300;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL20_lane_map);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL21_lane_map);
	offset = 292;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL22_lane_map);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL23_lane_map);
	offset = 348;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL24_lane_map);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL25_lane_map);
	offset = 340;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL26_lane_map);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL27_lane_map);
	offset = 332;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL28_lane_map);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL29_lane_map);
	offset = 324;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL30_lane_map);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL31_lane_map);
	offset = 480;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 540;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane7_to_els_logical_laser);
	offset = 536;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane6_to_els_logical_laser);
	offset = 532;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane5_to_els_logical_laser);
	offset = 528;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane4_to_els_logical_laser);
	offset = 524;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane3_to_els_logical_laser);
	offset = 520;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane2_to_els_logical_laser);
	offset = 516;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane1_to_els_logical_laser);
	offset = 512;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane0_to_els_logical_laser);
	offset = 568;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_module_index);
	offset = 560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->els_index);
	offset = 545;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->oe_mcu_index);
	offset = 544;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cpo_indication);
}

void reg_access_switch_pmdr_reg_ext_unpack(struct reg_access_switch_pmdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 21;
	ptr_struct->width_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->mcm_tile_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->gb_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->pport_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 49;
	ptr_struct->cluster = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 40;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->pport = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->ib_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->module_lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 69;
	ptr_struct->split = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 64;
	ptr_struct->gb_dp_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 126;
	ptr_struct->lp_query_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 124;
	ptr_struct->lbp_query_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 122;
	ptr_struct->tile_pport_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 118;
	ptr_struct->port_width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 104;
	ptr_struct->local_port_query = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->label_port_query = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 153;
	ptr_struct->gearbox_die_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 147;
	ptr_struct->tile_pport = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 144;
	ptr_struct->pll_cnt_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 136;
	ptr_struct->mcm_tile_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 132;
	ptr_struct->tile_cluster = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 189;
	ptr_struct->lane0_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 186;
	ptr_struct->lane1_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 183;
	ptr_struct->lane2_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 180;
	ptr_struct->lane3_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 177;
	ptr_struct->lane4_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 174;
	ptr_struct->lane5_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 171;
	ptr_struct->lane6_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 168;
	ptr_struct->lane7_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 165;
	ptr_struct->pll_cnt_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 160;
	ptr_struct->vl_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 221;
	ptr_struct->lane0_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 218;
	ptr_struct->lane1_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 215;
	ptr_struct->lane2_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 212;
	ptr_struct->lane3_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 209;
	ptr_struct->lane4_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 206;
	ptr_struct->lane5_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 203;
	ptr_struct->lane6_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 200;
	ptr_struct->lane7_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 192;
	ptr_struct->pll_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 252;
	ptr_struct->VL0_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 248;
	ptr_struct->VL1_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 244;
	ptr_struct->VL2_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 240;
	ptr_struct->VL3_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 236;
	ptr_struct->VL4_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 232;
	ptr_struct->VL5_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 228;
	ptr_struct->VL6_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->VL7_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 284;
	ptr_struct->VL8_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->VL9_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 276;
	ptr_struct->VL10_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 272;
	ptr_struct->VL11_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 268;
	ptr_struct->VL12_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 264;
	ptr_struct->VL13_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 260;
	ptr_struct->VL14_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->VL15_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 316;
	ptr_struct->VL16_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 312;
	ptr_struct->VL17_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 308;
	ptr_struct->VL18_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 304;
	ptr_struct->VL19_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 300;
	ptr_struct->VL20_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->VL21_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 292;
	ptr_struct->VL22_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->VL23_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 348;
	ptr_struct->VL24_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 344;
	ptr_struct->VL25_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 340;
	ptr_struct->VL26_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 336;
	ptr_struct->VL27_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 332;
	ptr_struct->VL28_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 328;
	ptr_struct->VL29_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 324;
	ptr_struct->VL30_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->VL31_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 540;
	ptr_struct->oe_lane7_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 536;
	ptr_struct->oe_lane6_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 532;
	ptr_struct->oe_lane5_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 528;
	ptr_struct->oe_lane4_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 524;
	ptr_struct->oe_lane3_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 520;
	ptr_struct->oe_lane2_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 516;
	ptr_struct->oe_lane1_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->oe_lane0_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 568;
	ptr_struct->els_module_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 560;
	ptr_struct->els_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 545;
	ptr_struct->oe_mcu_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 544;
	ptr_struct->cpo_indication = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_pmdr_reg_ext_print(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmdr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "width_valid          : " UH_FMT "\n", ptr_struct->width_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcm_tile_valid       : " UH_FMT "\n", ptr_struct->mcm_tile_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gb_valid             : " UH_FMT "\n", ptr_struct->gb_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pport_msb            : " UH_FMT "\n", ptr_struct->pport_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cluster              : " UH_FMT "\n", ptr_struct->cluster);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pport                : " UH_FMT "\n", ptr_struct->pport);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_port              : " UH_FMT "\n", ptr_struct->ib_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_lane_mask     : " UH_FMT "\n", ptr_struct->module_lane_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split                : " UH_FMT "\n", ptr_struct->split);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gb_dp_num            : " UH_FMT "\n", ptr_struct->gb_dp_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_query_msb         : " UH_FMT "\n", ptr_struct->lp_query_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lbp_query_msb        : " UH_FMT "\n", ptr_struct->lbp_query_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_pport_msb       : " UH_FMT "\n", ptr_struct->tile_pport_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_width           : " UH_FMT "\n", ptr_struct->port_width);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port_query     : " UH_FMT "\n", ptr_struct->local_port_query);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "label_port_query     : " UH_FMT "\n", ptr_struct->label_port_query);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gearbox_die_num      : " UH_FMT "\n", ptr_struct->gearbox_die_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_pport           : " UH_FMT "\n", ptr_struct->tile_pport);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_cnt_rx           : " UH_FMT "\n", ptr_struct->pll_cnt_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcm_tile_num         : " UH_FMT "\n", ptr_struct->mcm_tile_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_cluster         : " UH_FMT "\n", ptr_struct->tile_cluster);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_rx    : " UH_FMT "\n", ptr_struct->lane0_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane1_physical_rx    : " UH_FMT "\n", ptr_struct->lane1_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane2_physical_rx    : " UH_FMT "\n", ptr_struct->lane2_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane3_physical_rx    : " UH_FMT "\n", ptr_struct->lane3_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane4_physical_rx    : " UH_FMT "\n", ptr_struct->lane4_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane5_physical_rx    : " UH_FMT "\n", ptr_struct->lane5_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane6_physical_rx    : " UH_FMT "\n", ptr_struct->lane6_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane7_physical_rx    : " UH_FMT "\n", ptr_struct->lane7_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_cnt_tx           : " UH_FMT "\n", ptr_struct->pll_cnt_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_num               : " UH_FMT "\n", ptr_struct->vl_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_tx    : " UH_FMT "\n", ptr_struct->lane0_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane1_physical_tx    : " UH_FMT "\n", ptr_struct->lane1_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane2_physical_tx    : " UH_FMT "\n", ptr_struct->lane2_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane3_physical_tx    : " UH_FMT "\n", ptr_struct->lane3_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane4_physical_tx    : " UH_FMT "\n", ptr_struct->lane4_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane5_physical_tx    : " UH_FMT "\n", ptr_struct->lane5_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane6_physical_tx    : " UH_FMT "\n", ptr_struct->lane6_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane7_physical_tx    : " UH_FMT "\n", ptr_struct->lane7_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_index            : " UH_FMT "\n", ptr_struct->pll_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL0_lane_map         : " UH_FMT "\n", ptr_struct->VL0_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL1_lane_map         : " UH_FMT "\n", ptr_struct->VL1_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL2_lane_map         : " UH_FMT "\n", ptr_struct->VL2_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL3_lane_map         : " UH_FMT "\n", ptr_struct->VL3_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL4_lane_map         : " UH_FMT "\n", ptr_struct->VL4_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL5_lane_map         : " UH_FMT "\n", ptr_struct->VL5_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL6_lane_map         : " UH_FMT "\n", ptr_struct->VL6_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL7_lane_map         : " UH_FMT "\n", ptr_struct->VL7_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL8_lane_map         : " UH_FMT "\n", ptr_struct->VL8_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL9_lane_map         : " UH_FMT "\n", ptr_struct->VL9_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL10_lane_map        : " UH_FMT "\n", ptr_struct->VL10_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL11_lane_map        : " UH_FMT "\n", ptr_struct->VL11_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL12_lane_map        : " UH_FMT "\n", ptr_struct->VL12_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL13_lane_map        : " UH_FMT "\n", ptr_struct->VL13_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL14_lane_map        : " UH_FMT "\n", ptr_struct->VL14_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL15_lane_map        : " UH_FMT "\n", ptr_struct->VL15_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL16_lane_map        : " UH_FMT "\n", ptr_struct->VL16_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL17_lane_map        : " UH_FMT "\n", ptr_struct->VL17_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL18_lane_map        : " UH_FMT "\n", ptr_struct->VL18_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL19_lane_map        : " UH_FMT "\n", ptr_struct->VL19_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL20_lane_map        : " UH_FMT "\n", ptr_struct->VL20_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL21_lane_map        : " UH_FMT "\n", ptr_struct->VL21_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL22_lane_map        : " UH_FMT "\n", ptr_struct->VL22_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL23_lane_map        : " UH_FMT "\n", ptr_struct->VL23_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL24_lane_map        : " UH_FMT "\n", ptr_struct->VL24_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL25_lane_map        : " UH_FMT "\n", ptr_struct->VL25_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL26_lane_map        : " UH_FMT "\n", ptr_struct->VL26_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL27_lane_map        : " UH_FMT "\n", ptr_struct->VL27_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL28_lane_map        : " UH_FMT "\n", ptr_struct->VL28_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL29_lane_map        : " UH_FMT "\n", ptr_struct->VL29_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL30_lane_map        : " UH_FMT "\n", ptr_struct->VL30_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL31_lane_map        : " UH_FMT "\n", ptr_struct->VL31_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane7_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane7_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane6_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane6_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane5_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane5_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane4_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane4_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane3_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane3_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane2_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane2_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane1_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane1_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane0_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane0_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_module_index     : " UH_FMT "\n", ptr_struct->els_module_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_index            : " UH_FMT "\n", ptr_struct->els_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_mcu_index         : " UH_FMT "\n", ptr_struct->oe_mcu_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cpo_indication       : " UH_FMT "\n", ptr_struct->cpo_indication);
}

unsigned int reg_access_switch_pmdr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMDR_REG_EXT_SIZE;
}

void reg_access_switch_pmdr_reg_ext_dump(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmdr_reg_ext_print(ptr_struct, fd, 0);
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
	fprintf(fd, "mspmer_ext:\n");
	reg_access_switch_mspmer_ext_print(&(ptr_struct->mspmer_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_ext:\n");
	reg_access_switch_mddq_ext_print(&(ptr_struct->mddq_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_switch_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icsr_ext:\n");
	reg_access_switch_icsr_ext_print(&(ptr_struct->icsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmta_reg_ext:\n");
	reg_access_switch_mmta_reg_ext_print(&(ptr_struct->mmta_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmdr_reg_ext:\n");
	reg_access_switch_pmdr_reg_ext_print(&(ptr_struct->pmdr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icam_reg_ext:\n");
	reg_access_switch_icam_reg_ext_print(&(ptr_struct->icam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdsr_reg_ext:\n");
	reg_access_switch_mdsr_reg_ext_print(&(ptr_struct->mdsr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pllp_reg_ext:\n");
	reg_access_switch_pllp_reg_ext_print(&(ptr_struct->pllp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfmc_reg_ext:\n");
	reg_access_switch_mfmc_reg_ext_print(&(ptr_struct->mfmc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddt_reg_ext:\n");
	reg_access_switch_mddt_reg_ext_print(&(ptr_struct->mddt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgpir_ext:\n");
	reg_access_switch_mgpir_ext_print(&(ptr_struct->mgpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "msgi_ext:\n");
	reg_access_switch_msgi_ext_print(&(ptr_struct->msgi_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpein_reg_ext:\n");
	reg_access_switch_mpein_reg_ext_print(&(ptr_struct->mpein_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_switch_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpir_ext:\n");
	reg_access_switch_mpir_ext_print(&(ptr_struct->mpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plib_reg_ext:\n");
	reg_access_switch_plib_reg_ext_print(&(ptr_struct->plib_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pguid_reg_ext:\n");
	reg_access_switch_pguid_reg_ext_print(&(ptr_struct->pguid_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkdc_reg_ext:\n");
	reg_access_switch_mkdc_reg_ext_print(&(ptr_struct->mkdc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mrsr_ext:\n");
	reg_access_switch_mrsr_ext_print(&(ptr_struct->mrsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MMAM_ext:\n");
	reg_access_switch_MMAM_ext_print(&(ptr_struct->MMAM_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PPCR_ext:\n");
	reg_access_switch_PPCR_ext_print(&(ptr_struct->PPCR_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcq_reg_ext:\n");
	reg_access_switch_mtcq_reg_ext_print(&(ptr_struct->mtcq_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_reg_access_switch_Nodes_size(void)
{
	return REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE;
}

void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd)
{
	reg_access_switch_reg_access_switch_Nodes_print(ptr_struct, fd, 0);
}

