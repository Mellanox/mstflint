/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
         *** This file was generated at "2021-11-07 16:02:35"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/switch/ext/reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils
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

void reg_access_switch_device_info_ext_pack(const struct reg_access_switch_device_info_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_device_info_ext_unpack(struct reg_access_switch_device_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_device_info_ext_print(const struct reg_access_switch_device_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_device_info_ext ========\n");

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

unsigned int reg_access_switch_device_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_DEVICE_INFO_EXT_SIZE;
}

void reg_access_switch_device_info_ext_dump(const struct reg_access_switch_device_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_device_info_ext_print(ptr_struct, fd, 0);
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

void reg_access_switch_slot_info_ext_pack(const struct reg_access_switch_slot_info_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_slot_info_ext_unpack(struct reg_access_switch_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_slot_info_ext_print(const struct reg_access_switch_slot_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_slot_info_ext ========\n");

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

unsigned int reg_access_switch_slot_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_SLOT_INFO_EXT_SIZE;
}

void reg_access_switch_slot_info_ext_dump(const struct reg_access_switch_slot_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_slot_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_slot_name_ext_pack(const struct reg_access_switch_slot_name_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->slot_ascii_name[i]);
	}
}

void reg_access_switch_slot_name_ext_unpack(struct reg_access_switch_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->slot_ascii_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_slot_name_ext_print(const struct reg_access_switch_slot_name_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_slot_name_ext ========\n");

	for (i = 0; i < 20; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_ascii_name_%03d : " UH_FMT "\n", i, ptr_struct->slot_ascii_name[i]);
	}
}

unsigned int reg_access_switch_slot_name_ext_size(void)
{
	return REG_ACCESS_SWITCH_SLOT_NAME_EXT_SIZE;
}

void reg_access_switch_slot_name_ext_dump(const struct reg_access_switch_slot_name_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_slot_name_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_slot_info_ext_pack(&(ptr_struct->slot_info_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_slot_info_ext_unpack(&(ptr_struct->slot_info_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_info_ext:\n");
	reg_access_switch_slot_info_ext_print(&(ptr_struct->slot_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_info_ext:\n");
	reg_access_switch_device_info_ext_print(&(ptr_struct->device_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_name_ext:\n");
	reg_access_switch_slot_name_ext_print(&(ptr_struct->slot_name_ext), fd, indent_level + 1);
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
	fprintf(fd, "prm_register_payload_ext:\n");
	reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->prm_register_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "command_payload_ext:\n");
	reg_access_switch_command_payload_ext_print(&(ptr_struct->command_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crspace_access_payload_ext:\n");
	reg_access_switch_crspace_access_payload_ext_print(&(ptr_struct->crspace_access_payload_ext), fd, indent_level + 1);
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
	case 0x1:
		offset = 128;
		reg_access_switch_slot_info_ext_pack(&(ptr_struct->data.slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_switch_device_info_ext_pack(&(ptr_struct->data.device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_slot_name_ext_pack(&(ptr_struct->data.slot_name_ext), ptr_buff + offset / 8);
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
	case 0x1:
		offset = 128;
		reg_access_switch_slot_info_ext_unpack(&(ptr_struct->data.slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_switch_device_info_ext_unpack(&(ptr_struct->data.device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_slot_name_ext_unpack(&(ptr_struct->data.slot_name_ext), ptr_buff + offset / 8);
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
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_info_ext:\n");
		reg_access_switch_slot_info_ext_print(&(ptr_struct->data.slot_info_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "device_info_ext:\n");
		reg_access_switch_device_info_ext_print(&(ptr_struct->data.device_info_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_name_ext:\n");
		reg_access_switch_slot_name_ext_print(&(ptr_struct->data.slot_name_ext), fd, indent_level + 1);
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
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_pack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_pack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_pack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
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
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_unpack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_unpack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_unpack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
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
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "prm_register_payload_ext:\n");
		reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->payload.prm_register_payload_ext), fd, indent_level + 1);
		break;
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
	fprintf(fd, "mddt_reg_ext:\n");
	reg_access_switch_mddt_reg_ext_print(&(ptr_struct->mddt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icam_reg_ext:\n");
	reg_access_switch_icam_reg_ext_print(&(ptr_struct->icam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdsr_reg_ext:\n");
	reg_access_switch_mdsr_reg_ext_print(&(ptr_struct->mdsr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkdc_reg_ext:\n");
	reg_access_switch_mkdc_reg_ext_print(&(ptr_struct->mkdc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcq_reg_ext:\n");
	reg_access_switch_mtcq_reg_ext_print(&(ptr_struct->mtcq_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_ext:\n");
	reg_access_switch_mddq_ext_print(&(ptr_struct->mddq_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icsr_ext:\n");
	reg_access_switch_icsr_ext_print(&(ptr_struct->icsr_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_reg_access_switch_Nodes_size(void)
{
	return REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE;
}

void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd)
{
	reg_access_switch_reg_access_switch_Nodes_print(ptr_struct, fd, 0);
}

