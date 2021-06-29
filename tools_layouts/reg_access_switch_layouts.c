/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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
#include "reg_access_switch_layouts.h"

void reg_access_switch_device_info_pack(const struct reg_access_switch_device_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

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
}

void reg_access_switch_device_info_unpack(struct reg_access_switch_device_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

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
}

void reg_access_switch_slot_info_pack(const struct reg_access_switch_slot_info *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_switch_slot_info_unpack(struct reg_access_switch_slot_info *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_switch_slot_name_pack(const struct reg_access_switch_slot_name *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->slot_ascii_name[i]);
	}
}

void reg_access_switch_slot_name_unpack(struct reg_access_switch_slot_name *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->slot_ascii_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_slot_name_print(const struct reg_access_switch_slot_name *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_slot_name ========\n");

	for (i = 0; i < 20; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_ascii_name_%03d : " UH_FMT "\n", i, ptr_struct->slot_ascii_name[i]);
	}
}

unsigned int reg_access_switch_slot_name_size(void)
{
	return REG_ACCESS_SWITCH_SLOT_NAME_SIZE;
}

void reg_access_switch_slot_name_dump(const struct reg_access_switch_slot_name *ptr_struct, FILE *fd)
{
	reg_access_switch_slot_name_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_pack(const struct reg_access_switch_mddq *ptr_struct, u_int8_t *ptr_buff)
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
		reg_access_switch_slot_info_pack(&(ptr_struct->data.slot_info), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_switch_device_info_pack(&(ptr_struct->data.device_info), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_slot_name_pack(&(ptr_struct->data.slot_name), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddq_unpack(struct reg_access_switch_mddq *ptr_struct, const u_int8_t *ptr_buff)
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
		reg_access_switch_slot_info_unpack(&(ptr_struct->data.slot_info), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_switch_device_info_unpack(&(ptr_struct->data.device_info), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_slot_name_unpack(&(ptr_struct->data.slot_name), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_mddq_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_SIZE;
}
