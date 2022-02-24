/*
 * Copyright (c) 2010-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
         *** This file was generated at "2022-02-06 17:27:46"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/image_layout/image_layout.adb --file-prefix image_layout --prefix image_layout_ --no-adb-utils
         ***/
#include "image_layout_layouts.h"

void image_layout_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void image_layout_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void image_layout_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int image_layout_uint64_size(void)
{
	return IMAGE_LAYOUT_UINT64_SIZE;
}

void image_layout_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	image_layout_uint64_print(ptr_struct, fd, 0);
}

void image_layout_htoc_entry_pack(const struct image_layout_htoc_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hash_offset);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->section_type);
}

void image_layout_htoc_entry_unpack(struct image_layout_htoc_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->hash_offset = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->section_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void image_layout_htoc_entry_print(const struct image_layout_htoc_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_htoc_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_offset          : " UH_FMT "\n", ptr_struct->hash_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "section_type         : " UH_FMT "\n", ptr_struct->section_type);
}

unsigned int image_layout_htoc_entry_size(void)
{
	return IMAGE_LAYOUT_HTOC_ENTRY_SIZE;
}

void image_layout_htoc_entry_dump(const struct image_layout_htoc_entry *ptr_struct, FILE *fd)
{
	image_layout_htoc_entry_print(ptr_struct, fd, 0);
}

void image_layout_htoc_header_pack(const struct image_layout_htoc_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_entries);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hash_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hash_size);
}

void image_layout_htoc_header_unpack(struct image_layout_htoc_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->num_of_entries = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->hash_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->hash_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_htoc_header_print(const struct image_layout_htoc_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_htoc_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " U32H_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_entries       : " UH_FMT "\n", ptr_struct->num_of_entries);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_type            : " UH_FMT "\n", ptr_struct->hash_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_size            : " UH_FMT "\n", ptr_struct->hash_size);
}

unsigned int image_layout_htoc_header_size(void)
{
	return IMAGE_LAYOUT_HTOC_HEADER_SIZE;
}

void image_layout_htoc_header_dump(const struct image_layout_htoc_header *ptr_struct, FILE *fd)
{
	image_layout_htoc_header_print(ptr_struct, fd, 0);
}

void image_layout_module_version_pack(const struct image_layout_module_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->branch);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->major);
}

void image_layout_module_version_unpack(struct image_layout_module_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->branch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 12;
	ptr_struct->minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void image_layout_module_version_print(const struct image_layout_module_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_module_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch               : " UH_FMT "\n", ptr_struct->branch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
}

unsigned int image_layout_module_version_size(void)
{
	return IMAGE_LAYOUT_MODULE_VERSION_SIZE;
}

void image_layout_module_version_dump(const struct image_layout_module_version *ptr_struct, FILE *fd)
{
	image_layout_module_version_print(ptr_struct, fd, 0);
}

void image_layout_reset_capabilities_pack(const struct image_layout_reset_capabilities *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reset_ver_en);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_vector_ver);
}

void image_layout_reset_capabilities_unpack(struct image_layout_reset_capabilities *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->reset_ver_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->version_vector_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void image_layout_reset_capabilities_print(const struct image_layout_reset_capabilities *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_reset_capabilities ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_ver_en         : " UH_FMT "\n", ptr_struct->reset_ver_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_vector_ver   : " UH_FMT "\n", ptr_struct->version_vector_ver);
}

unsigned int image_layout_reset_capabilities_size(void)
{
	return IMAGE_LAYOUT_RESET_CAPABILITIES_SIZE;
}

void image_layout_reset_capabilities_dump(const struct image_layout_reset_capabilities *ptr_struct, FILE *fd)
{
	image_layout_reset_capabilities_print(ptr_struct, fd, 0);
}

void image_layout_reset_version_pack(const struct image_layout_reset_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->major);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->branch);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
}

void image_layout_reset_version_unpack(struct image_layout_reset_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 12;
	ptr_struct->branch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void image_layout_reset_version_print(const struct image_layout_reset_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_reset_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch               : " UH_FMT "\n", ptr_struct->branch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
}

unsigned int image_layout_reset_version_size(void)
{
	return IMAGE_LAYOUT_RESET_VERSION_SIZE;
}

void image_layout_reset_version_dump(const struct image_layout_reset_version *ptr_struct, FILE *fd)
{
	image_layout_reset_version_print(ptr_struct, fd, 0);
}

void image_layout_uid_entry_pack(const struct image_layout_uid_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->uid);
}

void image_layout_uid_entry_unpack(struct image_layout_uid_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->uid = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void image_layout_uid_entry_print(const struct image_layout_uid_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_uid_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_allocated        : " UH_FMT "\n", ptr_struct->num_allocated);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "step                 : " UH_FMT "\n", ptr_struct->step);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uid                  : " U64H_FMT "\n", ptr_struct->uid);
}

unsigned int image_layout_uid_entry_size(void)
{
	return IMAGE_LAYOUT_UID_ENTRY_SIZE;
}

void image_layout_uid_entry_dump(const struct image_layout_uid_entry *ptr_struct, FILE *fd)
{
	image_layout_uid_entry_print(ptr_struct, fd, 0);
}

void image_layout_FW_VERSION_pack(const struct image_layout_FW_VERSION *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Hour);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Minutes);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Seconds);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Day);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Month);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->Year);
}

void image_layout_FW_VERSION_unpack(struct image_layout_FW_VERSION *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->Hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->Minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->Seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->Day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->Month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->Year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_FW_VERSION_print(const struct image_layout_FW_VERSION *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_FW_VERSION ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MAJOR                : " UH_FMT "\n", ptr_struct->MAJOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "SUBMINOR             : " UH_FMT "\n", ptr_struct->SUBMINOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MINOR                : " UH_FMT "\n", ptr_struct->MINOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Hour                 : " UH_FMT "\n", ptr_struct->Hour);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Minutes              : " UH_FMT "\n", ptr_struct->Minutes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Seconds              : " UH_FMT "\n", ptr_struct->Seconds);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Day                  : " UH_FMT "\n", ptr_struct->Day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Month                : " UH_FMT "\n", ptr_struct->Month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Year                 : " UH_FMT "\n", ptr_struct->Year);
}

unsigned int image_layout_FW_VERSION_size(void)
{
	return IMAGE_LAYOUT_FW_VERSION_SIZE;
}

void image_layout_FW_VERSION_dump(const struct image_layout_FW_VERSION *ptr_struct, FILE *fd)
{
	image_layout_FW_VERSION_print(ptr_struct, fd, 0);
}

void image_layout_TRIPPLE_VERSION_pack(const struct image_layout_TRIPPLE_VERSION *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);
}

void image_layout_TRIPPLE_VERSION_unpack(struct image_layout_TRIPPLE_VERSION *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_TRIPPLE_VERSION_print(const struct image_layout_TRIPPLE_VERSION *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_TRIPPLE_VERSION ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MAJOR                : " UH_FMT "\n", ptr_struct->MAJOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "SUBMINOR             : " UH_FMT "\n", ptr_struct->SUBMINOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MINOR                : " UH_FMT "\n", ptr_struct->MINOR);
}

unsigned int image_layout_TRIPPLE_VERSION_size(void)
{
	return IMAGE_LAYOUT_TRIPPLE_VERSION_SIZE;
}

void image_layout_TRIPPLE_VERSION_dump(const struct image_layout_TRIPPLE_VERSION *ptr_struct, FILE *fd)
{
	image_layout_TRIPPLE_VERSION_print(ptr_struct, fd, 0);
}

void image_layout_guids_pack(const struct image_layout_guids *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_uid_entry_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 128;
	image_layout_uid_entry_pack(&(ptr_struct->macs), ptr_buff + offset / 8);
}

void image_layout_guids_unpack(struct image_layout_guids *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_uid_entry_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 128;
	image_layout_uid_entry_unpack(&(ptr_struct->macs), ptr_buff + offset / 8);
}

void image_layout_guids_print(const struct image_layout_guids *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_guids ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guids:\n");
	image_layout_uid_entry_print(&(ptr_struct->guids), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "macs:\n");
	image_layout_uid_entry_print(&(ptr_struct->macs), fd, indent_level + 1);
}

unsigned int image_layout_guids_size(void)
{
	return IMAGE_LAYOUT_GUIDS_SIZE;
}

void image_layout_guids_dump(const struct image_layout_guids *ptr_struct, FILE *fd)
{
	image_layout_guids_print(ptr_struct, fd, 0);
}

void image_layout_hashes_table_header_pack(const struct image_layout_hashes_table_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->load_address);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dw_size);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void image_layout_hashes_table_header_unpack(struct image_layout_hashes_table_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->load_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->dw_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_hashes_table_header_print(const struct image_layout_hashes_table_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_hashes_table_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "load_address         : " U32H_FMT "\n", ptr_struct->load_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dw_size              : " U32H_FMT "\n", ptr_struct->dw_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int image_layout_hashes_table_header_size(void)
{
	return IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE;
}

void image_layout_hashes_table_header_dump(const struct image_layout_hashes_table_header *ptr_struct, FILE *fd)
{
	image_layout_hashes_table_header_print(ptr_struct, fd, 0);
}

void image_layout_htoc_pack(const struct image_layout_htoc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	image_layout_htoc_header_pack(&(ptr_struct->header), ptr_buff + offset / 8);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1920, 1);
		image_layout_htoc_entry_pack(&(ptr_struct->entry[i]), ptr_buff + offset / 8);
	}
}

void image_layout_htoc_unpack(struct image_layout_htoc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	image_layout_htoc_header_unpack(&(ptr_struct->header), ptr_buff + offset / 8);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1920, 1);
		image_layout_htoc_entry_unpack(&(ptr_struct->entry[i]), ptr_buff + offset / 8);
	}
}

void image_layout_htoc_print(const struct image_layout_htoc *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_htoc ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "header:\n");
	image_layout_htoc_header_print(&(ptr_struct->header), fd, indent_level + 1);
	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "entry_%03d:\n", i);
		image_layout_htoc_entry_print(&(ptr_struct->entry[i]), fd, indent_level + 1);
	}
}

unsigned int image_layout_htoc_size(void)
{
	return IMAGE_LAYOUT_HTOC_SIZE;
}

void image_layout_htoc_dump(const struct image_layout_htoc *ptr_struct, FILE *fd)
{
	image_layout_htoc_print(ptr_struct, fd, 0);
}

void image_layout_htoc_hash_pack(const struct image_layout_htoc_hash *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 512, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hash_val[i]);
	}
}

void image_layout_htoc_hash_unpack(struct image_layout_htoc_hash *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 512, 1);
		ptr_struct->hash_val[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void image_layout_htoc_hash_print(const struct image_layout_htoc_hash *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_htoc_hash ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hash_val_%03d        : " U32H_FMT "\n", i, ptr_struct->hash_val[i]);
	}
}

unsigned int image_layout_htoc_hash_size(void)
{
	return IMAGE_LAYOUT_HTOC_HASH_SIZE;
}

void image_layout_htoc_hash_dump(const struct image_layout_htoc_hash *ptr_struct, FILE *fd)
{
	image_layout_htoc_hash_print(ptr_struct, fd, 0);
}

void image_layout_hw_pointer_entry_pack(const struct image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ptr);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void image_layout_hw_pointer_entry_unpack(struct image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ptr = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_hw_pointer_entry_print(const struct image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_hw_pointer_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptr                  : " U32H_FMT "\n", ptr_struct->ptr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int image_layout_hw_pointer_entry_size(void)
{
	return IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE;
}

void image_layout_hw_pointer_entry_dump(const struct image_layout_hw_pointer_entry *ptr_struct, FILE *fd)
{
	image_layout_hw_pointer_entry_print(ptr_struct, fd, 0);
}

void image_layout_image_size_pack(const struct image_layout_image_size *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_step);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->run_from_any);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_size);
}

void image_layout_image_size_unpack(struct image_layout_image_size *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->log_step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->run_from_any = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->max_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void image_layout_image_size_print(const struct image_layout_image_size *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_image_size ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_step             : " UH_FMT "\n", ptr_struct->log_step);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "run_from_any         : " UH_FMT "\n", ptr_struct->run_from_any);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_size             : " U32H_FMT "\n", ptr_struct->max_size);
}

unsigned int image_layout_image_size_size(void)
{
	return IMAGE_LAYOUT_IMAGE_SIZE_SIZE;
}

void image_layout_image_size_dump(const struct image_layout_image_size *ptr_struct, FILE *fd)
{
	image_layout_image_size_print(ptr_struct, fd, 0);
}

void image_layout_module_versions_pack(const struct image_layout_module_versions *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_module_version_pack(&(ptr_struct->core), ptr_buff + offset / 8);
	offset = 32;
	image_layout_module_version_pack(&(ptr_struct->phy), ptr_buff + offset / 8);
	offset = 64;
	image_layout_module_version_pack(&(ptr_struct->kernel), ptr_buff + offset / 8);
	offset = 96;
	image_layout_module_version_pack(&(ptr_struct->iron_image), ptr_buff + offset / 8);
	offset = 128;
	image_layout_module_version_pack(&(ptr_struct->host_management), ptr_buff + offset / 8);
	offset = 160;
	image_layout_module_version_pack(&(ptr_struct->mad), ptr_buff + offset / 8);
}

void image_layout_module_versions_unpack(struct image_layout_module_versions *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_module_version_unpack(&(ptr_struct->core), ptr_buff + offset / 8);
	offset = 32;
	image_layout_module_version_unpack(&(ptr_struct->phy), ptr_buff + offset / 8);
	offset = 64;
	image_layout_module_version_unpack(&(ptr_struct->kernel), ptr_buff + offset / 8);
	offset = 96;
	image_layout_module_version_unpack(&(ptr_struct->iron_image), ptr_buff + offset / 8);
	offset = 128;
	image_layout_module_version_unpack(&(ptr_struct->host_management), ptr_buff + offset / 8);
	offset = 160;
	image_layout_module_version_unpack(&(ptr_struct->mad), ptr_buff + offset / 8);
}

void image_layout_module_versions_print(const struct image_layout_module_versions *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_module_versions ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core:\n");
	image_layout_module_version_print(&(ptr_struct->core), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy:\n");
	image_layout_module_version_print(&(ptr_struct->phy), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kernel:\n");
	image_layout_module_version_print(&(ptr_struct->kernel), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "iron_image:\n");
	image_layout_module_version_print(&(ptr_struct->iron_image), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_management:\n");
	image_layout_module_version_print(&(ptr_struct->host_management), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mad:\n");
	image_layout_module_version_print(&(ptr_struct->mad), fd, indent_level + 1);
}

unsigned int image_layout_module_versions_size(void)
{
	return IMAGE_LAYOUT_MODULE_VERSIONS_SIZE;
}

void image_layout_module_versions_dump(const struct image_layout_module_versions *ptr_struct, FILE *fd)
{
	image_layout_module_versions_print(ptr_struct, fd, 0);
}

void image_layout_operation_key_pack(const struct image_layout_operation_key *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->key_modifier);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);
}

void image_layout_operation_key_unpack(struct image_layout_operation_key *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->key_modifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void image_layout_operation_key_print(const struct image_layout_operation_key *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_operation_key ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "key_modifier         : " UH_FMT "\n", ptr_struct->key_modifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "key                  : " U64H_FMT "\n", ptr_struct->key);
}

unsigned int image_layout_operation_key_size(void)
{
	return IMAGE_LAYOUT_OPERATION_KEY_SIZE;
}

void image_layout_operation_key_dump(const struct image_layout_operation_key *ptr_struct, FILE *fd)
{
	image_layout_operation_key_print(ptr_struct, fd, 0);
}

void image_layout_version_vector_pack(const struct image_layout_version_vector *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_reset_capabilities_pack(&(ptr_struct->reset_capabilities), ptr_buff + offset / 8);
	offset = 32;
	image_layout_reset_version_pack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
	offset = 64;
	image_layout_reset_version_pack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
	offset = 96;
	image_layout_reset_version_pack(&(ptr_struct->pci), ptr_buff + offset / 8);
	offset = 128;
	image_layout_reset_version_pack(&(ptr_struct->phy), ptr_buff + offset / 8);
	offset = 160;
	image_layout_reset_version_pack(&(ptr_struct->ini), ptr_buff + offset / 8);
	offset = 192;
	image_layout_reset_version_pack(&(ptr_struct->reserved1), ptr_buff + offset / 8);
	offset = 224;
	image_layout_reset_version_pack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
	offset = 256;
	image_layout_reset_version_pack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
	offset = 288;
	image_layout_reset_version_pack(&(ptr_struct->reserved4), ptr_buff + offset / 8);
	offset = 320;
	image_layout_reset_version_pack(&(ptr_struct->reserved5), ptr_buff + offset / 8);
	offset = 352;
	image_layout_reset_version_pack(&(ptr_struct->reserved6), ptr_buff + offset / 8);
}

void image_layout_version_vector_unpack(struct image_layout_version_vector *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_reset_capabilities_unpack(&(ptr_struct->reset_capabilities), ptr_buff + offset / 8);
	offset = 32;
	image_layout_reset_version_unpack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
	offset = 64;
	image_layout_reset_version_unpack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
	offset = 96;
	image_layout_reset_version_unpack(&(ptr_struct->pci), ptr_buff + offset / 8);
	offset = 128;
	image_layout_reset_version_unpack(&(ptr_struct->phy), ptr_buff + offset / 8);
	offset = 160;
	image_layout_reset_version_unpack(&(ptr_struct->ini), ptr_buff + offset / 8);
	offset = 192;
	image_layout_reset_version_unpack(&(ptr_struct->reserved1), ptr_buff + offset / 8);
	offset = 224;
	image_layout_reset_version_unpack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
	offset = 256;
	image_layout_reset_version_unpack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
	offset = 288;
	image_layout_reset_version_unpack(&(ptr_struct->reserved4), ptr_buff + offset / 8);
	offset = 320;
	image_layout_reset_version_unpack(&(ptr_struct->reserved5), ptr_buff + offset / 8);
	offset = 352;
	image_layout_reset_version_unpack(&(ptr_struct->reserved6), ptr_buff + offset / 8);
}

void image_layout_version_vector_print(const struct image_layout_version_vector *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_version_vector ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_capabilities:\n");
	image_layout_reset_capabilities_print(&(ptr_struct->reset_capabilities), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "scratchpad:\n");
	image_layout_reset_version_print(&(ptr_struct->scratchpad), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icm_context:\n");
	image_layout_reset_version_print(&(ptr_struct->icm_context), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci:\n");
	image_layout_reset_version_print(&(ptr_struct->pci), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy:\n");
	image_layout_reset_version_print(&(ptr_struct->phy), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini:\n");
	image_layout_reset_version_print(&(ptr_struct->ini), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved2:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved3:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved3), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved4:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved4), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved5:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved5), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved6:\n");
	image_layout_reset_version_print(&(ptr_struct->reserved6), fd, indent_level + 1);
}

unsigned int image_layout_version_vector_size(void)
{
	return IMAGE_LAYOUT_VERSION_VECTOR_SIZE;
}

void image_layout_version_vector_dump(const struct image_layout_version_vector *ptr_struct, FILE *fd)
{
	image_layout_version_vector_print(ptr_struct, fd, 0);
}

void image_layout_device_info_pack(const struct image_layout_device_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

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
	image_layout_guids_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
		image_layout_operation_key_pack(&(ptr_struct->keys[i]), ptr_buff + offset / 8);
	}
	offset = 4080;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void image_layout_device_info_unpack(struct image_layout_device_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

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
	image_layout_guids_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 880;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
		ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->vsd[208] = '\0';
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
		image_layout_operation_key_unpack(&(ptr_struct->keys[i]), ptr_buff + offset / 8);
	}
	offset = 4080;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_device_info_print(const struct image_layout_device_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_device_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guids:\n");
	image_layout_guids_print(&(ptr_struct->guids), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);
		fprintf(fd, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "keys_%03d:\n", i);
		image_layout_operation_key_print(&(ptr_struct->keys[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int image_layout_device_info_size(void)
{
	return IMAGE_LAYOUT_DEVICE_INFO_SIZE;
}

void image_layout_device_info_dump(const struct image_layout_device_info *ptr_struct, FILE *fd)
{
	image_layout_device_info_print(ptr_struct, fd, 0);
}

void image_layout_hashes_table_pack(const struct image_layout_hashes_table *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	image_layout_hashes_table_header_pack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 96;
	image_layout_htoc_pack(&(ptr_struct->htoc), ptr_buff + offset / 8);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(2016, 512, i, 16416, 1);
		image_layout_htoc_hash_pack(&(ptr_struct->hash[i]), ptr_buff + offset / 8);
	}
	offset = 16400;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void image_layout_hashes_table_unpack(struct image_layout_hashes_table *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	image_layout_hashes_table_header_unpack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 96;
	image_layout_htoc_unpack(&(ptr_struct->htoc), ptr_buff + offset / 8);
	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(2016, 512, i, 16416, 1);
		image_layout_htoc_hash_unpack(&(ptr_struct->hash[i]), ptr_buff + offset / 8);
	}
	offset = 16400;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_hashes_table_print(const struct image_layout_hashes_table *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_hashes_table ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "header:\n");
	image_layout_hashes_table_header_print(&(ptr_struct->header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "htoc:\n");
	image_layout_htoc_print(&(ptr_struct->htoc), fd, indent_level + 1);
	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hash_%03d:\n", i);
		image_layout_htoc_hash_print(&(ptr_struct->hash[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int image_layout_hashes_table_size(void)
{
	return IMAGE_LAYOUT_HASHES_TABLE_SIZE;
}

void image_layout_hashes_table_dump(const struct image_layout_hashes_table *ptr_struct, FILE *fd)
{
	image_layout_hashes_table_print(ptr_struct, fd, 0);
}

void image_layout_hw_pointers_carmel_pack(const struct image_layout_hw_pointers_carmel *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->boot_record_ptr), ptr_buff + offset / 8);
	offset = 64;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->authentication_start_pointer), ptr_buff + offset / 8);
	offset = 320;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->authentication_end_pointer), ptr_buff + offset / 8);
	offset = 384;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->digest_pointer), ptr_buff + offset / 8);
	offset = 448;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->digest_recovery_key_pointer), ptr_buff + offset / 8);
	offset = 512;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->fw_window_start_pointer), ptr_buff + offset / 8);
	offset = 576;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->fw_window_end_pointer), ptr_buff + offset / 8);
	offset = 640;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->hmac_end_pointer), ptr_buff + offset / 8);
	offset = 768;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->fw_security_version_pointer), ptr_buff + offset / 8);
	offset = 896;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	image_layout_hw_pointer_entry_pack(&(ptr_struct->hashes_table_pointer), ptr_buff + offset / 8);
}

void image_layout_hw_pointers_carmel_unpack(struct image_layout_hw_pointers_carmel *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->boot_record_ptr), ptr_buff + offset / 8);
	offset = 64;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->authentication_start_pointer), ptr_buff + offset / 8);
	offset = 320;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->authentication_end_pointer), ptr_buff + offset / 8);
	offset = 384;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->digest_pointer), ptr_buff + offset / 8);
	offset = 448;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->digest_recovery_key_pointer), ptr_buff + offset / 8);
	offset = 512;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->fw_window_start_pointer), ptr_buff + offset / 8);
	offset = 576;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->fw_window_end_pointer), ptr_buff + offset / 8);
	offset = 640;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->hmac_end_pointer), ptr_buff + offset / 8);
	offset = 768;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->fw_security_version_pointer), ptr_buff + offset / 8);
	offset = 896;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	image_layout_hw_pointer_entry_unpack(&(ptr_struct->hashes_table_pointer), ptr_buff + offset / 8);
}

void image_layout_hw_pointers_carmel_print(const struct image_layout_hw_pointers_carmel *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_hw_pointers_carmel ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_record_ptr:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->boot_record_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_ptr:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "toc_ptr:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->toc_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tools_ptr:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->tools_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "authentication_start_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->authentication_start_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "authentication_end_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->authentication_end_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "digest_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->digest_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "digest_recovery_key_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->digest_recovery_key_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_window_start_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->fw_window_start_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_window_end_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->fw_window_end_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info_section_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->image_info_section_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hmac_end_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->hmac_end_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "public_key_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->public_key_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_security_version_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->fw_security_version_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gcm_iv_delta_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->gcm_iv_delta_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hashes_table_pointer:\n");
	image_layout_hw_pointer_entry_print(&(ptr_struct->hashes_table_pointer), fd, indent_level + 1);
}

unsigned int image_layout_hw_pointers_carmel_size(void)
{
	return IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE;
}

void image_layout_hw_pointers_carmel_dump(const struct image_layout_hw_pointers_carmel *ptr_struct, FILE *fd)
{
	image_layout_hw_pointers_carmel_print(ptr_struct, fd, 0);
}

void image_layout_image_info_pack(const struct image_layout_image_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secure_boot);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->encrypted_fw);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->windbond_flash_support);
	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->long_keys);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->debug_fw_tokens_supported);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mcc_en);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_vendor_nvconfig_files);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_mlnx_nvconfig_files);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->frc_supported);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cs_tokens_supported);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->debug_fw);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_fw);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secure_fw);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);
	offset = 32;
	image_layout_FW_VERSION_pack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
	offset = 160;
	image_layout_TRIPPLE_VERSION_pack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pci_vendor_id);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pci_device_id);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pci_sub_vendor_id);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pci_subsystem_id);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 432;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(472, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}
	offset = 2112;
	image_layout_image_size_pack(&(ptr_struct->image_size), ptr_buff + offset / 8);
	offset = 2200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->synced_reset_downtime);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_hw_id[i]);
	}
	offset = 2368;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ini_file_num);
	offset = 2400;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->burn_image_size);
	offset = 3200;
	image_layout_version_vector_pack(&(ptr_struct->version_vector), ptr_buff + offset / 8);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prod_ver[i]);
	}
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->description[i]);
	}
	offset = 6144;
	image_layout_module_versions_pack(&(ptr_struct->module_versions), ptr_buff + offset / 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->name[i]);
	}
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prs_name[i]);
	}
}

void image_layout_image_info_unpack(struct image_layout_image_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 29;
	ptr_struct->secure_boot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 27;
	ptr_struct->encrypted_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 26;
	ptr_struct->windbond_flash_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 25;
	ptr_struct->long_keys = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->debug_fw_tokens_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 23;
	ptr_struct->mcc_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->signed_vendor_nvconfig_files = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 21;
	ptr_struct->signed_mlnx_nvconfig_files = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->frc_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->cs_tokens_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->debug_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->signed_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->secure_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	image_layout_FW_VERSION_unpack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
	offset = 160;
	image_layout_TRIPPLE_VERSION_unpack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
	offset = 240;
	ptr_struct->pci_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->pci_device_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 272;
	ptr_struct->pci_sub_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 256;
	ptr_struct->pci_subsystem_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
		ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->psid[16] = '\0';
	offset = 432;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(472, 8, i, 8192, 1);
		ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->vsd[208] = '\0';
	offset = 2112;
	image_layout_image_size_unpack(&(ptr_struct->image_size), ptr_buff + offset / 8);
	offset = 2200;
	ptr_struct->synced_reset_downtime = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
		ptr_struct->supported_hw_id[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 2368;
	ptr_struct->ini_file_num = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 2400;
	ptr_struct->burn_image_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 3200;
	image_layout_version_vector_unpack(&(ptr_struct->version_vector), ptr_buff + offset / 8);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
		ptr_struct->prod_ver[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->prod_ver[16] = '\0';
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
		ptr_struct->description[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->description[256] = '\0';
	offset = 6144;
	image_layout_module_versions_unpack(&(ptr_struct->module_versions), ptr_buff + offset / 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
		ptr_struct->name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->name[64] = '\0';
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
		ptr_struct->prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->prs_name[128] = '\0';
}

void image_layout_image_info_print(const struct image_layout_image_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_image_info ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secure_boot          : " UH_FMT "\n", ptr_struct->secure_boot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "encrypted_fw         : " UH_FMT "\n", ptr_struct->encrypted_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "windbond_flash_support : " UH_FMT "\n", ptr_struct->windbond_flash_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "long_keys            : " UH_FMT "\n", ptr_struct->long_keys);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug_fw_tokens_supported : " UH_FMT "\n", ptr_struct->debug_fw_tokens_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcc_en               : " UH_FMT "\n", ptr_struct->mcc_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_vendor_nvconfig_files : " UH_FMT "\n", ptr_struct->signed_vendor_nvconfig_files);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_mlnx_nvconfig_files : " UH_FMT "\n", ptr_struct->signed_mlnx_nvconfig_files);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "frc_supported        : " UH_FMT "\n", ptr_struct->frc_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cs_tokens_supported  : " UH_FMT "\n", ptr_struct->cs_tokens_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug_fw             : " UH_FMT "\n", ptr_struct->debug_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_fw            : " UH_FMT "\n", ptr_struct->signed_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secure_fw            : " UH_FMT "\n", ptr_struct->secure_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_VERSION:\n");
	image_layout_FW_VERSION_print(&(ptr_struct->FW_VERSION), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mic_version:\n");
	image_layout_TRIPPLE_VERSION_print(&(ptr_struct->mic_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_vendor_id        : " UH_FMT "\n", ptr_struct->pci_vendor_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_device_id        : " UH_FMT "\n", ptr_struct->pci_device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_sub_vendor_id    : " UH_FMT "\n", ptr_struct->pci_sub_vendor_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_subsystem_id     : " UH_FMT "\n", ptr_struct->pci_subsystem_id);
		fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);
		fprintf(fd, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_size:\n");
	image_layout_image_size_print(&(ptr_struct->image_size), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "synced_reset_downtime : " UH_FMT "\n", ptr_struct->synced_reset_downtime);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "supported_hw_id_%03d : " U32H_FMT "\n", i, ptr_struct->supported_hw_id[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_num         : " U32H_FMT "\n", ptr_struct->ini_file_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "burn_image_size      : " U32H_FMT "\n", ptr_struct->burn_image_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version_vector:\n");
	image_layout_version_vector_print(&(ptr_struct->version_vector), fd, indent_level + 1);
		fprintf(fd, "prod_ver             : \"%s\"\n", ptr_struct->prod_ver);
		fprintf(fd, "description          : \"%s\"\n", ptr_struct->description);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_versions:\n");
	image_layout_module_versions_print(&(ptr_struct->module_versions), fd, indent_level + 1);
		fprintf(fd, "name                 : \"%s\"\n", ptr_struct->name);
		fprintf(fd, "prs_name             : \"%s\"\n", ptr_struct->prs_name);
}

unsigned int image_layout_image_info_size(void)
{
	return IMAGE_LAYOUT_IMAGE_INFO_SIZE;
}

void image_layout_image_info_dump(const struct image_layout_image_info *ptr_struct, FILE *fd)
{
	image_layout_image_info_print(ptr_struct, fd, 0);
}

void image_layout_itoc_entry_pack(const struct image_layout_itoc_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

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
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->version);
	offset = 161;
	adb2c_push_bits_to_buff(ptr_buff, offset, 29, (u_int32_t)ptr_struct->flash_addr);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->section_crc);
	offset = 205;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->crc);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->encrypted_section);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);
}

void image_layout_itoc_entry_unpack(struct image_layout_itoc_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

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
	offset = 144;
	ptr_struct->version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 161;
	ptr_struct->flash_addr = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 29);
	offset = 208;
	ptr_struct->section_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 205;
	ptr_struct->crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 192;
	ptr_struct->encrypted_section = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_itoc_entry_print(const struct image_layout_itoc_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_itoc_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param0               : " UH_FMT "\n", ptr_struct->param0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cache_line_crc       : " UH_FMT "\n", ptr_struct->cache_line_crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "zipped_image         : " UH_FMT "\n", ptr_struct->zipped_image);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "param1               : " U32H_FMT "\n", ptr_struct->param1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_addr           : " UH_FMT "\n", ptr_struct->flash_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "section_crc          : " UH_FMT "\n", ptr_struct->section_crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "encrypted_section    : " UH_FMT "\n", ptr_struct->encrypted_section);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);
}

unsigned int image_layout_itoc_entry_size(void)
{
	return IMAGE_LAYOUT_ITOC_ENTRY_SIZE;
}

void image_layout_itoc_entry_dump(const struct image_layout_itoc_entry *ptr_struct, FILE *fd)
{
	image_layout_itoc_entry_print(ptr_struct, fd, 0);
}

void image_layout_itoc_header_pack(const struct image_layout_itoc_header *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_layout_version);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_entries);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);
}

void image_layout_itoc_header_unpack(struct image_layout_itoc_header *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 152;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->flash_layout_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 184;
	ptr_struct->num_of_entries = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void image_layout_itoc_header_print(const struct image_layout_itoc_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_itoc_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_layout_version : " UH_FMT "\n", ptr_struct->flash_layout_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_entries       : " UH_FMT "\n", ptr_struct->num_of_entries);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);
}

unsigned int image_layout_itoc_header_size(void)
{
	return IMAGE_LAYOUT_ITOC_HEADER_SIZE;
}

void image_layout_itoc_header_dump(const struct image_layout_itoc_header *ptr_struct, FILE *fd)
{
	image_layout_itoc_header_print(ptr_struct, fd, 0);
}

void image_layout_tools_area_pack(const struct image_layout_tools_area *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

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

void image_layout_tools_area_unpack(struct image_layout_tools_area *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

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

void image_layout_tools_area_print(const struct image_layout_tools_area *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_tools_area ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bin_ver_minor        : " UH_FMT "\n", ptr_struct->bin_ver_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bin_ver_major        : " UH_FMT "\n", ptr_struct->bin_ver_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log2_img_slot_size   : " UH_FMT "\n", ptr_struct->log2_img_slot_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int image_layout_tools_area_size(void)
{
	return IMAGE_LAYOUT_TOOLS_AREA_SIZE;
}

void image_layout_tools_area_dump(const struct image_layout_tools_area *ptr_struct, FILE *fd)
{
	image_layout_tools_area_print(ptr_struct, fd, 0);
}

void image_layout_image_layout_Nodes_pack(const union image_layout_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	image_layout_hashes_table_pack(&(ptr_struct->hashes_table), ptr_buff);
}

void image_layout_image_layout_Nodes_unpack(union image_layout_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	image_layout_hashes_table_unpack(&(ptr_struct->hashes_table), ptr_buff);
}

void image_layout_image_layout_Nodes_print(const union image_layout_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== image_layout_image_layout_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tools_area:\n");
	image_layout_tools_area_print(&(ptr_struct->tools_area), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_entry:\n");
	image_layout_itoc_entry_print(&(ptr_struct->itoc_entry), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hashes_table:\n");
	image_layout_hashes_table_print(&(ptr_struct->hashes_table), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info:\n");
	image_layout_image_info_print(&(ptr_struct->image_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointers_carmel:\n");
	image_layout_hw_pointers_carmel_print(&(ptr_struct->hw_pointers_carmel), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_header:\n");
	image_layout_itoc_header_print(&(ptr_struct->itoc_header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_info:\n");
	image_layout_device_info_print(&(ptr_struct->device_info), fd, indent_level + 1);
}

unsigned int image_layout_image_layout_Nodes_size(void)
{
	return IMAGE_LAYOUT_IMAGE_LAYOUT_NODES_SIZE;
}

void image_layout_image_layout_Nodes_dump(const union image_layout_image_layout_Nodes *ptr_struct, FILE *fd)
{
	image_layout_image_layout_Nodes_print(ptr_struct, fd, 0);
}

