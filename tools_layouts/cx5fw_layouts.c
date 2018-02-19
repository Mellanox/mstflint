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
         *** This file was generated at "2017-05-28 21:03:29"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/cx5fw/cx5fw.adb --file-prefix cx5fw --prefix cx5fw_
         ***/
#include "cx5fw_layouts.h"

void cx5fw_hw_pointer_entry_pack(const struct cx5fw_hw_pointer_entry *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ptr);

	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);

}

void cx5fw_hw_pointer_entry_unpack(struct cx5fw_hw_pointer_entry *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	ptr_struct->ptr = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 48;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cx5fw_hw_pointer_entry_print(const struct cx5fw_hw_pointer_entry *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_hw_pointer_entry ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ptr                  : " U32H_FMT "\n", ptr_struct->ptr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "crc                  : " UH_FMT "\n", ptr_struct->crc);

}

int cx5fw_hw_pointer_entry_size(void)
{
	 return 8;
}

void cx5fw_hw_pointer_entry_dump(const struct cx5fw_hw_pointer_entry *ptr_struct, FILE* file)
{
	cx5fw_hw_pointer_entry_print(ptr_struct, file, 0);
}

void cx5fw_itoc_entry_pack(const struct cx5fw_itoc_entry *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 22, (u_int32_t)ptr_struct->size);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);

	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 30, (u_int32_t)ptr_struct->param0);

	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cache_line_crc);

	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->zipped_image);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->param1);

	offset = 161;
	adb2c_push_bits_to_buff(ptr_buff, offset, 29, (u_int32_t)ptr_struct->flash_addr);

	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->section_crc);

	offset = 205;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->crc);

	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);

}

void cx5fw_itoc_entry_unpack(struct cx5fw_itoc_entry *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	ptr_struct->size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 22);

	offset = 0;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 34;
	ptr_struct->param0 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 30);

	offset = 33;
	ptr_struct->cache_line_crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 32;
	ptr_struct->zipped_image = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 64;
	ptr_struct->param1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 161;
	ptr_struct->flash_addr = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 29);

	offset = 208;
	ptr_struct->section_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 205;
	ptr_struct->crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cx5fw_itoc_entry_print(const struct cx5fw_itoc_entry *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_itoc_entry ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "size                 : " UH_FMT "\n", ptr_struct->size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type                 : " UH_FMT "\n", ptr_struct->type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param0               : " UH_FMT "\n", ptr_struct->param0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "cache_line_crc       : " UH_FMT "\n", ptr_struct->cache_line_crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "zipped_image         : " UH_FMT "\n", ptr_struct->zipped_image);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param1               : " U32H_FMT "\n", ptr_struct->param1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_addr           : " UH_FMT "\n", ptr_struct->flash_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "section_crc          : " UH_FMT "\n", ptr_struct->section_crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "crc                  : " UH_FMT "\n", ptr_struct->crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);

}

int cx5fw_itoc_entry_size(void)
{
	 return 32;
}

void cx5fw_itoc_entry_dump(const struct cx5fw_itoc_entry *ptr_struct, FILE* file)
{
	cx5fw_itoc_entry_print(ptr_struct, file, 0);
}

void cx5fw_itoc_header_pack(const struct cx5fw_itoc_header *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature0);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature1);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature2);

	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature3);

	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);

	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_layout_version);

	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);

}

void cx5fw_itoc_header_unpack(struct cx5fw_itoc_header *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 152;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 128;
	ptr_struct->flash_layout_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cx5fw_itoc_header_print(const struct cx5fw_itoc_header *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_itoc_header ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : " UH_FMT "\n", ptr_struct->version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_layout_version : " UH_FMT "\n", ptr_struct->flash_layout_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);

}

int cx5fw_itoc_header_size(void)
{
	 return 32;
}

void cx5fw_itoc_header_dump(const struct cx5fw_itoc_header *ptr_struct, FILE* file)
{
	cx5fw_itoc_header_print(ptr_struct, file, 0);
}

void cx5fw_tools_area_pack(const struct cx5fw_tools_area *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bin_ver_minor);

	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bin_ver_major);

	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->log2_img_slot_size);

	offset = 496;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);

}

void cx5fw_tools_area_unpack(struct cx5fw_tools_area *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 16;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 56;
	ptr_struct->bin_ver_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 48;
	ptr_struct->bin_ver_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 32;
	ptr_struct->log2_img_slot_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 496;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cx5fw_tools_area_print(const struct cx5fw_tools_area *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_tools_area ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor                : " UH_FMT "\n", ptr_struct->minor);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major                : " UH_FMT "\n", ptr_struct->major);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "bin_ver_minor        : " UH_FMT "\n", ptr_struct->bin_ver_minor);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "bin_ver_major        : " UH_FMT "\n", ptr_struct->bin_ver_major);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log2_img_slot_size   : " UH_FMT "\n", ptr_struct->log2_img_slot_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "crc                  : " UH_FMT "\n", ptr_struct->crc);

}

int cx5fw_tools_area_size(void)
{
	 return 64;
}

void cx5fw_tools_area_dump(const struct cx5fw_tools_area *ptr_struct, FILE* file)
{
	cx5fw_tools_area_print(ptr_struct, file, 0);
}

void cx5fw_hw_pointers_pack(const struct cx5fw_hw_pointers *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->boot_record_ptr), ptr_buff + offset/8);

	offset = 64;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset/8);

	offset = 128;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset/8);

	offset = 192;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->tools_ptr), ptr_buff + offset/8);

	offset = 256;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->reserved0_ptr), ptr_buff + offset/8);

	offset = 320;
	cx5fw_hw_pointer_entry_pack(&(ptr_struct->reserved1_ptr), ptr_buff + offset/8);

}

void cx5fw_hw_pointers_unpack(struct cx5fw_hw_pointers *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->boot_record_ptr), ptr_buff + offset/8);

	offset = 64;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset/8);

	offset = 128;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset/8);

	offset = 192;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->tools_ptr), ptr_buff + offset/8);

	offset = 256;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->reserved0_ptr), ptr_buff + offset/8);

	offset = 320;
	cx5fw_hw_pointer_entry_unpack(&(ptr_struct->reserved1_ptr), ptr_buff + offset/8);

}

void cx5fw_hw_pointers_print(const struct cx5fw_hw_pointers *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_hw_pointers ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_record_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->boot_record_ptr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot2_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "toc_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->toc_ptr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tools_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->tools_ptr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reserved0_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->reserved0_ptr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reserved1_ptr:\n");
	cx5fw_hw_pointer_entry_print(&(ptr_struct->reserved1_ptr), file, indent_level + 1);

}

int cx5fw_hw_pointers_size(void)
{
	 return 48;
}

void cx5fw_hw_pointers_dump(const struct cx5fw_hw_pointers *ptr_struct, FILE* file)
{
	cx5fw_hw_pointers_print(ptr_struct, file, 0);
}

void cx5fw_operation_key_pack(const struct cx5fw_operation_key *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->key_modifier);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);

}

void cx5fw_operation_key_unpack(struct cx5fw_operation_key *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	ptr_struct->key_modifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cx5fw_operation_key_print(const struct cx5fw_operation_key *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_operation_key ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key_modifier         : " UH_FMT "\n", ptr_struct->key_modifier);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key                  : " U64H_FMT "\n", ptr_struct->key);

}

int cx5fw_operation_key_size(void)
{
	 return 16;
}

void cx5fw_operation_key_dump(const struct cx5fw_operation_key *ptr_struct, FILE* file)
{
	cx5fw_operation_key_print(ptr_struct, file, 0);
}

void cx5fw_uid_entry_pack(const struct cx5fw_uid_entry *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->uid);

}

void cx5fw_uid_entry_unpack(struct cx5fw_uid_entry *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 16;
	ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 64;
	ptr_struct->uid = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cx5fw_uid_entry_print(const struct cx5fw_uid_entry *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_uid_entry ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_allocated        : " UH_FMT "\n", ptr_struct->num_allocated);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "step                 : " UH_FMT "\n", ptr_struct->step);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uid                  : " U64H_FMT "\n", ptr_struct->uid);

}

int cx5fw_uid_entry_size(void)
{
	 return 16;
}

void cx5fw_uid_entry_dump(const struct cx5fw_uid_entry *ptr_struct, FILE* file)
{
	cx5fw_uid_entry_print(ptr_struct, file, 0);
}

void cx5fw_guids_pack(const struct cx5fw_guids *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx5fw_uid_entry_pack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 128;
	cx5fw_uid_entry_pack(&(ptr_struct->macs), ptr_buff + offset/8);

}

void cx5fw_guids_unpack(struct cx5fw_guids *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx5fw_uid_entry_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 128;
	cx5fw_uid_entry_unpack(&(ptr_struct->macs), ptr_buff + offset/8);

}

void cx5fw_guids_print(const struct cx5fw_guids *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_guids ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx5fw_uid_entry_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "macs:\n");
	cx5fw_uid_entry_print(&(ptr_struct->macs), file, indent_level + 1);

}

int cx5fw_guids_size(void)
{
	 return 64;
}

void cx5fw_guids_dump(const struct cx5fw_guids *ptr_struct, FILE* file)
{
	cx5fw_guids_print(ptr_struct, file, 0);
}

void cx5fw_device_info_pack(const struct cx5fw_device_info *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature0);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature1);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature2);

	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature3);

	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset = 143;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->major_version);

	offset = 256;
	cx5fw_guids_pack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);

	for (i = 0; i < 208; i++) {
	offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cx5fw_operation_key_pack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

	offset = 4080;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);

}

void cx5fw_device_info_unpack(struct cx5fw_device_info *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 152;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 143;
	ptr_struct->major_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);

	offset = 256;
	cx5fw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 880;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	for (i = 0; i < 208; i++) {
	offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->vsd[208] = '\0';
	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cx5fw_operation_key_unpack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

	offset = 4080;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cx5fw_device_info_print(const struct cx5fw_device_info *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_device_info ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : " UH_FMT "\n", ptr_struct->major_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx5fw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);

	fprintf(file, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i = 0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "keys_%03d:\n", i);
	cx5fw_operation_key_print(&(ptr_struct->keys[i]), file, indent_level + 1);
	}

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "crc                  : " UH_FMT "\n", ptr_struct->crc);

}

int cx5fw_device_info_size(void)
{
	 return 512;
}

void cx5fw_device_info_dump(const struct cx5fw_device_info *ptr_struct, FILE* file)
{
	cx5fw_device_info_print(ptr_struct, file, 0);
}

void cx5fw_cx5fw_Nodes_pack(const union cx5fw_cx5fw_Nodes *ptr_struct, u_int8_t* ptr_buff)
{
	cx5fw_hw_pointers_pack(&(ptr_struct->hw_pointers), ptr_buff);
}

void cx5fw_cx5fw_Nodes_unpack(union cx5fw_cx5fw_Nodes *ptr_struct, const u_int8_t* ptr_buff)
{
	cx5fw_hw_pointers_unpack(&(ptr_struct->hw_pointers), ptr_buff);
}

void cx5fw_cx5fw_Nodes_print(const union cx5fw_cx5fw_Nodes *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx5fw_cx5fw_Nodes ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "device_info:\n");
	cx5fw_device_info_print(&(ptr_struct->device_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_header:\n");
	cx5fw_itoc_header_print(&(ptr_struct->itoc_header), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tools_area:\n");
	cx5fw_tools_area_print(&(ptr_struct->tools_area), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry:\n");
	cx5fw_itoc_entry_print(&(ptr_struct->itoc_entry), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "hw_pointers:\n");
	cx5fw_hw_pointers_print(&(ptr_struct->hw_pointers), file, indent_level + 1);

}

int cx5fw_cx5fw_Nodes_size(void)
{
	 return 512;
}

void cx5fw_cx5fw_Nodes_dump(const union cx5fw_cx5fw_Nodes *ptr_struct, FILE* file)
{
	cx5fw_cx5fw_Nodes_print(ptr_struct, file, 0);
}

