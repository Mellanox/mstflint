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
         *** This file was generated at "2018-08-29 13:02:13"
         *** by:
         ***    > /mswg/release/tools/a-me/a-me-1.0.110/adabe_plugins/adb2c/adb2pack.py --input adb/cx6fw/cx6fw.adb --file-prefix cx6fw --prefix cx6fw_
         ***/
#include "cx6fw_layouts.h"

void cx6fw_hw_pointer_entry_pack(const struct cx6fw_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff)
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

void cx6fw_hw_pointer_entry_unpack(struct cx6fw_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff)
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

void cx6fw_hw_pointer_entry_print(const struct cx6fw_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level)
{
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)fd;
	(void)indent_level;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cx6fw_hw_pointer_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptr                  : " U32H_FMT "\n", ptr_struct->ptr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int cx6fw_hw_pointer_entry_size(void)
{
	return CX6FW_HW_POINTER_ENTRY_SIZE;
}

void cx6fw_hw_pointer_entry_dump(const struct cx6fw_hw_pointer_entry *ptr_struct, FILE *fd)
{
	cx6fw_hw_pointer_entry_print(ptr_struct, fd, 0);
}

void cx6fw_hw_pointers_pack(const struct cx6fw_hw_pointers *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->boot_record_ptr), ptr_buff + offset / 8);
	offset = 64;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->authentication_start_ptr), ptr_buff + offset / 8);
	offset = 320;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->authentication_end_ptr), ptr_buff + offset / 8);
	offset = 384;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->digest_mdk_ptr), ptr_buff + offset / 8);
	offset = 448;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->digest_recovery_key_ptr), ptr_buff + offset / 8);
	offset = 512;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr8), ptr_buff + offset / 8);
	offset = 576;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr9), ptr_buff + offset / 8);
	offset = 640;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr10), ptr_buff + offset / 8);
	offset = 704;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr11), ptr_buff + offset / 8);
	offset = 768;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr12), ptr_buff + offset / 8);
	offset = 832;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr13), ptr_buff + offset / 8);
	offset = 896;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr14), ptr_buff + offset / 8);
	offset = 960;
	cx6fw_hw_pointer_entry_pack(&(ptr_struct->reserved_ptr15), ptr_buff + offset / 8);
}

void cx6fw_hw_pointers_unpack(struct cx6fw_hw_pointers *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->boot_record_ptr), ptr_buff + offset / 8);
	offset = 64;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->authentication_start_ptr), ptr_buff + offset / 8);
	offset = 320;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->authentication_end_ptr), ptr_buff + offset / 8);
	offset = 384;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->digest_mdk_ptr), ptr_buff + offset / 8);
	offset = 448;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->digest_recovery_key_ptr), ptr_buff + offset / 8);
	offset = 512;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr8), ptr_buff + offset / 8);
	offset = 576;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr9), ptr_buff + offset / 8);
	offset = 640;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr10), ptr_buff + offset / 8);
	offset = 704;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr11), ptr_buff + offset / 8);
	offset = 768;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr12), ptr_buff + offset / 8);
	offset = 832;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr13), ptr_buff + offset / 8);
	offset = 896;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr14), ptr_buff + offset / 8);
	offset = 960;
	cx6fw_hw_pointer_entry_unpack(&(ptr_struct->reserved_ptr15), ptr_buff + offset / 8);
}

void cx6fw_hw_pointers_print(const struct cx6fw_hw_pointers *ptr_struct, FILE *fd, int indent_level)
{
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)fd;
	(void)indent_level;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cx6fw_hw_pointers ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_record_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->boot_record_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "toc_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->toc_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tools_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->tools_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "authentication_start_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->authentication_start_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "authentication_end_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->authentication_end_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "digest_mdk_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->digest_mdk_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "digest_recovery_key_ptr:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->digest_recovery_key_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr8:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr8), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr9:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr9), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr10:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr10), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr11:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr11), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr12:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr12), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr13:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr13), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr14:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr14), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_ptr15:\n");
	cx6fw_hw_pointer_entry_print(&(ptr_struct->reserved_ptr15), fd, indent_level + 1);
}

unsigned int cx6fw_hw_pointers_size(void)
{
	return CX6FW_HW_POINTERS_SIZE;
}

void cx6fw_hw_pointers_dump(const struct cx6fw_hw_pointers *ptr_struct, FILE *fd)
{
	cx6fw_hw_pointers_print(ptr_struct, fd, 0);
}

void cx6fw_cx6fw_Nodes_pack(const union cx6fw_cx6fw_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	cx6fw_hw_pointers_pack(&(ptr_struct->hw_pointers), ptr_buff);
}

void cx6fw_cx6fw_Nodes_unpack(union cx6fw_cx6fw_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	cx6fw_hw_pointers_unpack(&(ptr_struct->hw_pointers), ptr_buff);
}

void cx6fw_cx6fw_Nodes_print(const union cx6fw_cx6fw_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)fd;
	(void)indent_level;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cx6fw_cx6fw_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointers:\n");
	cx6fw_hw_pointers_print(&(ptr_struct->hw_pointers), fd, indent_level + 1);
}

unsigned int cx6fw_cx6fw_Nodes_size(void)
{
	return CX6FW_CX6FW_NODES_SIZE;
}

void cx6fw_cx6fw_Nodes_dump(const union cx6fw_cx6fw_Nodes *ptr_struct, FILE *fd)
{
	cx6fw_cx6fw_Nodes_print(ptr_struct, fd, 0);
}

