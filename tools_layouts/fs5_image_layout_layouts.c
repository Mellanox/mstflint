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
         *** This file was generated at "2023-02-06 14:12:04"
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

void fs5_image_layout_boot2_header_gilboa_pack(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->load_addr);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dw_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->branch_addr_lsb);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->branch_addr_msb);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crc);
}

void fs5_image_layout_boot2_header_gilboa_unpack(struct fs5_image_layout_boot2_header_gilboa *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->load_addr = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->dw_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->branch_addr_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->branch_addr_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->crc = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs5_image_layout_boot2_header_gilboa_print(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot2_header_gilboa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "load_addr            : " U32H_FMT "\n", ptr_struct->load_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dw_size              : " U32H_FMT "\n", ptr_struct->dw_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch_addr_lsb      : " U32H_FMT "\n", ptr_struct->branch_addr_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch_addr_msb      : " U32H_FMT "\n", ptr_struct->branch_addr_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " U32H_FMT "\n", ptr_struct->crc);
}

unsigned int fs5_image_layout_boot2_header_gilboa_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE;
}

void fs5_image_layout_boot2_header_gilboa_dump(const struct fs5_image_layout_boot2_header_gilboa *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot2_header_gilboa_print(ptr_struct, fd, 0);
}

void fs5_image_layout_hw_pointers_gilboa_pack(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->tool2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->image_info_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_bch_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_ptr), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_bch_ptr), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_hashes_ptr), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_bch_ptr), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_ptr), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr10), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr11), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr12), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr13), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr14), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr15), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_unpack(struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->tool2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->image_info_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_bch_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_ptr), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_bch_ptr), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_hashes_ptr), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_bch_ptr), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_ptr), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr10), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr11), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr12), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr13), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr14), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr15), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_print(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_hw_pointers_gilboa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "toc_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->toc_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tool2_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->tool2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->image_info_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_bch_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_bch_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_bch_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_bch_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_hashes_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_hashes_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_bch_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_bch_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr10:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr10), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr11:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr11), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr12:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr12), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr13:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr13), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr14:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr14), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr15:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved_ptr15), fd, indent_level + 1);
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
	fs5_image_layout_hw_pointers_gilboa_pack(&(ptr_struct->hw_pointers_gilboa), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_unpack(union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_hw_pointers_gilboa_unpack(&(ptr_struct->hw_pointers_gilboa), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_print(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_fs5_image_layout_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_header_gilboa:\n");
	fs5_image_layout_boot2_header_gilboa_print(&(ptr_struct->boot2_header_gilboa), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointers_gilboa:\n");
	fs5_image_layout_hw_pointers_gilboa_print(&(ptr_struct->hw_pointers_gilboa), fd, indent_level + 1);
}

unsigned int fs5_image_layout_fs5_image_layout_Nodes_size(void)
{
	return FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE;
}

void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd)
{
	fs5_image_layout_fs5_image_layout_Nodes_print(ptr_struct, fd, 0);
}


