
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
         *** This file was generated at "2018-05-12 08:07:49"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/register_access_open/register_access_open.adb --file-prefix register_access_open --prefix register_access_
         ***/
#include "register_access_open_layouts.h"

void register_access_mfba_pack(const struct register_access_mfba *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 2144, 0);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void register_access_mfba_unpack(struct register_access_mfba *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 55;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	offset = 64;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 2144, 0);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void register_access_mfba_print(const struct register_access_mfba *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_mfba ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int register_access_mfba_size(void)
{
	return REGISTER_ACCESS_MFBA_SIZE;
}

void register_access_mfba_dump(const struct register_access_mfba *ptr_struct, FILE *fd)
{
	register_access_mfba_print(ptr_struct, fd, 0);
}

void register_access_mfbe_pack(const struct register_access_mfbe *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_64kb_erase);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_32kb_erase);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
}

void register_access_mfbe_unpack(struct register_access_mfbe *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->bulk_64kb_erase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->bulk_32kb_erase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void register_access_mfbe_print(const struct register_access_mfbe *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_mfbe ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_64kb_erase      : " UH_FMT "\n", ptr_struct->bulk_64kb_erase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_32kb_erase      : " UH_FMT "\n", ptr_struct->bulk_32kb_erase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
}

unsigned int register_access_mfbe_size(void)
{
	return REGISTER_ACCESS_MFBE_SIZE;
}

void register_access_mfbe_dump(const struct register_access_mfbe *ptr_struct, FILE *fd)
{
	register_access_mfbe_print(ptr_struct, fd, 0);
}

void register_access_mfpa_pack(const struct register_access_mfpa *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 130;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_64kb_erase_en);
	offset = 129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bulk_32kb_erase_en);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->jedec_id);
	offset = 214;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->sector_size);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_allignment);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->capability_mask);
}

void register_access_mfpa_unpack(struct register_access_mfpa *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 130;
	ptr_struct->bulk_64kb_erase_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 129;
	ptr_struct->bulk_32kb_erase_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 168;
	ptr_struct->jedec_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 214;
	ptr_struct->sector_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 200;
	ptr_struct->block_allignment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->capability_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void register_access_mfpa_print(const struct register_access_mfpa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_mfpa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_address         : " U32H_FMT "\n", ptr_struct->boot_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_num            : " UH_FMT "\n", ptr_struct->flash_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_64kb_erase_en   : " UH_FMT "\n", ptr_struct->bulk_64kb_erase_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bulk_32kb_erase_en   : " UH_FMT "\n", ptr_struct->bulk_32kb_erase_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "jedec_id             : " UH_FMT "\n", ptr_struct->jedec_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sector_size          : " UH_FMT "\n", ptr_struct->sector_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_alignment      : " UH_FMT "\n", ptr_struct->block_allignment);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "capability_mask      : " U32H_FMT "\n", ptr_struct->capability_mask);
}

unsigned int register_access_mfpa_size(void)
{
	return REGISTER_ACCESS_MFPA_SIZE;
}

void register_access_mfpa_dump(const struct register_access_mfpa *ptr_struct, FILE *fd)
{
	register_access_mfpa_print(ptr_struct, fd, 0);
}

void register_access_register_access_open_Nodes_pack(const union register_access_register_access_open_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	register_access_mfba_pack(&(ptr_struct->mfba), ptr_buff);
}

void register_access_register_access_open_Nodes_unpack(union register_access_register_access_open_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	register_access_mfba_unpack(&(ptr_struct->mfba), ptr_buff);
}

void register_access_register_access_open_Nodes_print(const union register_access_register_access_open_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_register_access_open_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfbe:\n");
	register_access_mfbe_print(&(ptr_struct->mfbe), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfpa:\n");
	register_access_mfpa_print(&(ptr_struct->mfpa), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfba:\n");
	register_access_mfba_print(&(ptr_struct->mfba), fd, indent_level + 1);
}

unsigned int register_access_register_access_open_Nodes_size(void)
{
	return REGISTER_ACCESS_REGISTER_ACCESS_OPEN_NODES_SIZE;
}

void register_access_register_access_open_Nodes_dump(const union register_access_register_access_open_Nodes *ptr_struct, FILE *fd)
{
	register_access_register_access_open_Nodes_print(ptr_struct, fd, 0);
}

