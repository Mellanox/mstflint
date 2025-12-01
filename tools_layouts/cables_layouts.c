
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
 


#include "cables_layouts.h"


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