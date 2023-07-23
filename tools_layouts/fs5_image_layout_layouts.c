/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
         *** This file was generated at "2023-06-01 20:24:55"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/fs5_image_layout/fs5_image_layout.adb --file-prefix fs5_image_layout --prefix fs5_image_layout_ --no-adb-utils
         ***/
#include "fs5_image_layout_layouts.h"

void fs5_image_layout_hw_pointer_entry_pack(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ptr);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void fs5_image_layout_hw_pointer_entry_unpack(struct fs5_image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ptr = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void fs5_image_layout_hw_pointer_entry_print(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_hw_pointer_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptr                  : " U32H_FMT "\n", ptr_struct->ptr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int fs5_image_layout_hw_pointer_entry_size(void)
{
	return FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE;
}

void fs5_image_layout_hw_pointer_entry_dump(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd)
{
	fs5_image_layout_hw_pointer_entry_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_header_pack(const struct fs5_image_layout_boot_component_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_digest);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_security_version);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_metadata);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->public_key);
	offset = 63264;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->length);
	offset = 63296;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->load_offset);
	offset = 63328;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hash_offset);
	offset = 63360;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->branch_offset);
}

void fs5_image_layout_boot_component_header_unpack(struct fs5_image_layout_boot_component_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->component_digest = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->component_security_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->component_metadata = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->signature = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->public_key = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 63264;
	ptr_struct->length = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 63296;
	ptr_struct->load_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 63328;
	ptr_struct->hash_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 63360;
	ptr_struct->branch_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs5_image_layout_boot_component_header_print(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_digest     : " U32H_FMT "\n", ptr_struct->component_digest);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_security_version : " U32H_FMT "\n", ptr_struct->component_security_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_metadata   : " U32H_FMT "\n", ptr_struct->component_metadata);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature            : " U32H_FMT "\n", ptr_struct->signature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "public_key           : " U32H_FMT "\n", ptr_struct->public_key);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length               : " U32H_FMT "\n", ptr_struct->length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "load_offset          : " U32H_FMT "\n", ptr_struct->load_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_offset          : " U32H_FMT "\n", ptr_struct->hash_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch_offset        : " U32H_FMT "\n", ptr_struct->branch_offset);
}

unsigned int fs5_image_layout_boot_component_header_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE;
}

void fs5_image_layout_boot_component_header_dump(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_header_print(ptr_struct, fd, 0);
}

void fs5_image_layout_hw_pointers_gilboa_pack(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bct_pointer), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_bch_pointer), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_pointer), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_bch_pointer), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_bch_pointer), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_pointer), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->image_signature_pointer), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->fw_security_version_pointer), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_hashes_pointer), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_unpack(struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bct_pointer), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_bch_pointer), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_pointer), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_bch_pointer), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_bch_pointer), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_pointer), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->image_signature_pointer), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->fw_security_version_pointer), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_hashes_pointer), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_print(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_hw_pointers_gilboa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bct_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bct_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "toc_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->toc_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tools_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->tools_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info_section_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->image_info_section_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_signature_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->image_signature_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "public_key_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->public_key_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_security_version_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->fw_security_version_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gcm_iv_delta_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->gcm_iv_delta_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_hashes_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_hashes_pointer), fd, indent_level + 1);
}

unsigned int fs5_image_layout_hw_pointers_gilboa_size(void)
{
	return FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE;
}

void fs5_image_layout_hw_pointers_gilboa_dump(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd)
{
	fs5_image_layout_hw_pointers_gilboa_print(ptr_struct, fd, 0);
}

void fs5_image_layout_fs5_image_layout_Nodes_pack(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_boot_component_header_pack(&(ptr_struct->boot_component_header), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_unpack(union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_boot_component_header_unpack(&(ptr_struct->boot_component_header), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_print(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_fs5_image_layout_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointers_gilboa:\n");
	fs5_image_layout_hw_pointers_gilboa_print(&(ptr_struct->hw_pointers_gilboa), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_component_header:\n");
	fs5_image_layout_boot_component_header_print(&(ptr_struct->boot_component_header), fd, indent_level + 1);
}

unsigned int fs5_image_layout_fs5_image_layout_Nodes_size(void)
{
	return FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE;
}

void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd)
{
	fs5_image_layout_fs5_image_layout_Nodes_print(ptr_struct, fd, 0);
}


