
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
         *** This file was generated at "2019-08-11 16:47:37"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/cibfw/cibfw.adb --file-prefix cibfw --prefix cibfw_
         ***/
#include "cibfw_layouts.h"

void cibfw_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void cibfw_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void cibfw_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int cibfw_uint64_size(void)
{
	return CIBFW_UINT64_SIZE;
}

void cibfw_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	cibfw_uint64_print(ptr_struct, fd, 0);
}

void cibfw_reset_version_pack(const struct cibfw_reset_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->major);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
}

void cibfw_reset_version_unpack(struct cibfw_reset_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->major = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void cibfw_reset_version_print(const struct cibfw_reset_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_reset_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " U32H_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
}

unsigned int cibfw_reset_version_size(void)
{
	return CIBFW_RESET_VERSION_SIZE;
}

void cibfw_reset_version_dump(const struct cibfw_reset_version *ptr_struct, FILE *fd)
{
	cibfw_reset_version_print(ptr_struct, fd, 0);
}

void cibfw_uid_entry_pack(const struct cibfw_uid_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->uid);
}

void cibfw_uid_entry_unpack(struct cibfw_uid_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->uid = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void cibfw_uid_entry_print(const struct cibfw_uid_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_uid_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_allocated        : " UH_FMT "\n", ptr_struct->num_allocated);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "step                 : " UH_FMT "\n", ptr_struct->step);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uid                  : " U64H_FMT "\n", ptr_struct->uid);
}

unsigned int cibfw_uid_entry_size(void)
{
	return CIBFW_UID_ENTRY_SIZE;
}

void cibfw_uid_entry_dump(const struct cibfw_uid_entry *ptr_struct, FILE *fd)
{
	cibfw_uid_entry_print(ptr_struct, fd, 0);
}

void cibfw_FW_VERSION_pack(const struct cibfw_FW_VERSION *ptr_struct, u_int8_t *ptr_buff)
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

void cibfw_FW_VERSION_unpack(struct cibfw_FW_VERSION *ptr_struct, const u_int8_t *ptr_buff)
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

void cibfw_FW_VERSION_print(const struct cibfw_FW_VERSION *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_FW_VERSION ========\n");

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

unsigned int cibfw_FW_VERSION_size(void)
{
	return CIBFW_FW_VERSION_SIZE;
}

void cibfw_FW_VERSION_dump(const struct cibfw_FW_VERSION *ptr_struct, FILE *fd)
{
	cibfw_FW_VERSION_print(ptr_struct, fd, 0);
}

void cibfw_TRIPPLE_VERSION_pack(const struct cibfw_TRIPPLE_VERSION *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);
}

void cibfw_TRIPPLE_VERSION_unpack(struct cibfw_TRIPPLE_VERSION *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void cibfw_TRIPPLE_VERSION_print(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_TRIPPLE_VERSION ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MAJOR                : " UH_FMT "\n", ptr_struct->MAJOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "SUBMINOR             : " UH_FMT "\n", ptr_struct->SUBMINOR);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MINOR                : " UH_FMT "\n", ptr_struct->MINOR);
}

unsigned int cibfw_TRIPPLE_VERSION_size(void)
{
	return CIBFW_TRIPPLE_VERSION_SIZE;
}

void cibfw_TRIPPLE_VERSION_dump(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE *fd)
{
	cibfw_TRIPPLE_VERSION_print(ptr_struct, fd, 0);
}

void cibfw_guids_pack(const struct cibfw_guids *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 128, i, 512, 1);
		cibfw_uid_entry_pack(&(ptr_struct->guids[i]), ptr_buff + offset / 8);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(256, 128, i, 512, 1);
		cibfw_uid_entry_pack(&(ptr_struct->macs[i]), ptr_buff + offset / 8);
	}
}

void cibfw_guids_unpack(struct cibfw_guids *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 128, i, 512, 1);
		cibfw_uid_entry_unpack(&(ptr_struct->guids[i]), ptr_buff + offset / 8);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(256, 128, i, 512, 1);
		cibfw_uid_entry_unpack(&(ptr_struct->macs[i]), ptr_buff + offset / 8);
	}
}

void cibfw_guids_print(const struct cibfw_guids *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_guids ========\n");

	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "guids_%03d:\n", i);
		cibfw_uid_entry_print(&(ptr_struct->guids[i]), fd, indent_level + 1);
	}
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "macs_%03d:\n", i);
		cibfw_uid_entry_print(&(ptr_struct->macs[i]), fd, indent_level + 1);
	}
}

unsigned int cibfw_guids_size(void)
{
	return CIBFW_GUIDS_SIZE;
}

void cibfw_guids_dump(const struct cibfw_guids *ptr_struct, FILE *fd)
{
	cibfw_guids_print(ptr_struct, fd, 0);
}

void cibfw_image_size_pack(const struct cibfw_image_size *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_step);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->run_from_any);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_size);
}

void cibfw_image_size_unpack(struct cibfw_image_size *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->log_step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->run_from_any = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->max_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void cibfw_image_size_print(const struct cibfw_image_size *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_image_size ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_step             : " UH_FMT "\n", ptr_struct->log_step);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "run_from_any         : " UH_FMT "\n", ptr_struct->run_from_any);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_size             : " U32H_FMT "\n", ptr_struct->max_size);
}

unsigned int cibfw_image_size_size(void)
{
	return CIBFW_IMAGE_SIZE_SIZE;
}

void cibfw_image_size_dump(const struct cibfw_image_size *ptr_struct, FILE *fd)
{
	cibfw_image_size_print(ptr_struct, fd, 0);
}

void cibfw_lfwp_version_vector_pack(const struct cibfw_lfwp_version_vector *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	cibfw_reset_version_pack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
	offset = 64;
	cibfw_reset_version_pack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
	offset = 128;
	cibfw_reset_version_pack(&(ptr_struct->pci_code), ptr_buff + offset / 8);
	offset = 192;
	cibfw_reset_version_pack(&(ptr_struct->phy_code), ptr_buff + offset / 8);
	offset = 256;
	cibfw_reset_version_pack(&(ptr_struct->ini), ptr_buff + offset / 8);
	offset = 320;
	cibfw_reset_version_pack(&(ptr_struct->reserved1), ptr_buff + offset / 8);
	offset = 384;
	cibfw_reset_version_pack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
	offset = 448;
	cibfw_reset_version_pack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
}

void cibfw_lfwp_version_vector_unpack(struct cibfw_lfwp_version_vector *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	cibfw_reset_version_unpack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
	offset = 64;
	cibfw_reset_version_unpack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
	offset = 128;
	cibfw_reset_version_unpack(&(ptr_struct->pci_code), ptr_buff + offset / 8);
	offset = 192;
	cibfw_reset_version_unpack(&(ptr_struct->phy_code), ptr_buff + offset / 8);
	offset = 256;
	cibfw_reset_version_unpack(&(ptr_struct->ini), ptr_buff + offset / 8);
	offset = 320;
	cibfw_reset_version_unpack(&(ptr_struct->reserved1), ptr_buff + offset / 8);
	offset = 384;
	cibfw_reset_version_unpack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
	offset = 448;
	cibfw_reset_version_unpack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
}

void cibfw_lfwp_version_vector_print(const struct cibfw_lfwp_version_vector *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_lfwp_version_vector ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "scratchpad:\n");
	cibfw_reset_version_print(&(ptr_struct->scratchpad), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icm_context:\n");
	cibfw_reset_version_print(&(ptr_struct->icm_context), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_code:\n");
	cibfw_reset_version_print(&(ptr_struct->pci_code), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_code:\n");
	cibfw_reset_version_print(&(ptr_struct->phy_code), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini:\n");
	cibfw_reset_version_print(&(ptr_struct->ini), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1:\n");
	cibfw_reset_version_print(&(ptr_struct->reserved1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved2:\n");
	cibfw_reset_version_print(&(ptr_struct->reserved2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved3:\n");
	cibfw_reset_version_print(&(ptr_struct->reserved3), fd, indent_level + 1);
}

unsigned int cibfw_lfwp_version_vector_size(void)
{
	return CIBFW_LFWP_VERSION_VECTOR_SIZE;
}

void cibfw_lfwp_version_vector_dump(const struct cibfw_lfwp_version_vector *ptr_struct, FILE *fd)
{
	cibfw_lfwp_version_vector_print(ptr_struct, fd, 0);
}

void cibfw_module_version_pack(const struct cibfw_module_version *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->branch);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->major);
}

void cibfw_module_version_unpack(struct cibfw_module_version *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->branch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 12;
	ptr_struct->minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void cibfw_module_version_print(const struct cibfw_module_version *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_module_version ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "branch               : " UH_FMT "\n", ptr_struct->branch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
}

unsigned int cibfw_module_version_size(void)
{
	return CIBFW_MODULE_VERSION_SIZE;
}

void cibfw_module_version_dump(const struct cibfw_module_version *ptr_struct, FILE *fd)
{
	cibfw_module_version_print(ptr_struct, fd, 0);
}

void cibfw_operation_key_pack(const struct cibfw_operation_key *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->key_modifier);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);
}

void cibfw_operation_key_unpack(struct cibfw_operation_key *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->key_modifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void cibfw_operation_key_print(const struct cibfw_operation_key *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_operation_key ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "key_modifier         : " UH_FMT "\n", ptr_struct->key_modifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "key                  : " U64H_FMT "\n", ptr_struct->key);
}

unsigned int cibfw_operation_key_size(void)
{
	return CIBFW_OPERATION_KEY_SIZE;
}

void cibfw_operation_key_dump(const struct cibfw_operation_key *ptr_struct, FILE *fd)
{
	cibfw_operation_key_print(ptr_struct, fd, 0);
}

void cibfw_device_info_pack(const struct cibfw_device_info *ptr_struct, u_int8_t *ptr_buff)
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
	cibfw_guids_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
		cibfw_operation_key_pack(&(ptr_struct->keys[i]), ptr_buff + offset / 8);
	}
}

void cibfw_device_info_unpack(struct cibfw_device_info *ptr_struct, const u_int8_t *ptr_buff)
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
	cibfw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
	offset = 880;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 208; ++i) {
		offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
		ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->vsd[208] = '\0';
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
		cibfw_operation_key_unpack(&(ptr_struct->keys[i]), ptr_buff + offset / 8);
	}
}

void cibfw_device_info_print(const struct cibfw_device_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_device_info ========\n");

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
	cibfw_guids_print(&(ptr_struct->guids), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);
		fprintf(fd, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "keys_%03d:\n", i);
		cibfw_operation_key_print(&(ptr_struct->keys[i]), fd, indent_level + 1);
	}
}

unsigned int cibfw_device_info_size(void)
{
	return CIBFW_DEVICE_INFO_SIZE;
}

void cibfw_device_info_dump(const struct cibfw_device_info *ptr_struct, FILE *fd)
{
	cibfw_device_info_print(ptr_struct, fd, 0);
}

void cibfw_image_info_pack(const struct cibfw_image_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

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
	cibfw_FW_VERSION_pack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
	offset = 160;
	cibfw_TRIPPLE_VERSION_pack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
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
	cibfw_image_size_pack(&(ptr_struct->image_size), ptr_buff + offset / 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_hw_id[i]);
	}
	offset = 2368;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ini_file_num);
	offset = 2432;
	cibfw_lfwp_version_vector_pack(&(ptr_struct->lfwp_version_vector), ptr_buff + offset / 8);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prod_ver[i]);
	}
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->description[i]);
	}
	offset = 6304;
	cibfw_module_version_pack(&(ptr_struct->isfu), ptr_buff + offset / 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->name[i]);
	}
	for (i = 0; i < 128; ++i) {
		offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prs_name[i]);
	}
}

void cibfw_image_info_unpack(struct cibfw_image_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

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
	cibfw_FW_VERSION_unpack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
	offset = 160;
	cibfw_TRIPPLE_VERSION_unpack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
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
	cibfw_image_size_unpack(&(ptr_struct->image_size), ptr_buff + offset / 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
		ptr_struct->supported_hw_id[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 2368;
	ptr_struct->ini_file_num = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 2432;
	cibfw_lfwp_version_vector_unpack(&(ptr_struct->lfwp_version_vector), ptr_buff + offset / 8);
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
	offset = 6304;
	cibfw_module_version_unpack(&(ptr_struct->isfu), ptr_buff + offset / 8);
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

void cibfw_image_info_print(const struct cibfw_image_info *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_image_info ========\n");

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
	cibfw_FW_VERSION_print(&(ptr_struct->FW_VERSION), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mic_version:\n");
	cibfw_TRIPPLE_VERSION_print(&(ptr_struct->mic_version), fd, indent_level + 1);
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
	cibfw_image_size_print(&(ptr_struct->image_size), fd, indent_level + 1);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "supported_hw_id_%03d : " U32H_FMT "\n", i, ptr_struct->supported_hw_id[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_num         : " U32H_FMT "\n", ptr_struct->ini_file_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lfwp_version_vector:\n");
	cibfw_lfwp_version_vector_print(&(ptr_struct->lfwp_version_vector), fd, indent_level + 1);
		fprintf(fd, "prod_ver             : \"%s\"\n", ptr_struct->prod_ver);
		fprintf(fd, "description          : \"%s\"\n", ptr_struct->description);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "isfu:\n");
	cibfw_module_version_print(&(ptr_struct->isfu), fd, indent_level + 1);
		fprintf(fd, "name                 : \"%s\"\n", ptr_struct->name);
		fprintf(fd, "prs_name             : \"%s\"\n", ptr_struct->prs_name);
}

unsigned int cibfw_image_info_size(void)
{
	return CIBFW_IMAGE_INFO_SIZE;
}

void cibfw_image_info_dump(const struct cibfw_image_info *ptr_struct, FILE *fd)
{
	cibfw_image_info_print(ptr_struct, fd, 0);
}

void cibfw_itoc_entry_pack(const struct cibfw_itoc_entry *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 161;
	adb2c_push_bits_to_buff(ptr_buff, offset, 29, (u_int32_t)ptr_struct->flash_addr);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->relative_addr);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->section_crc);
	offset = 207;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->no_crc);
	offset = 206;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->device_data);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);
}

void cibfw_itoc_entry_unpack(struct cibfw_itoc_entry *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 161;
	ptr_struct->flash_addr = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 29);
	offset = 160;
	ptr_struct->relative_addr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 208;
	ptr_struct->section_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 207;
	ptr_struct->no_crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 206;
	ptr_struct->device_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void cibfw_itoc_entry_print(const struct cibfw_itoc_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_itoc_entry ========\n");

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
	fprintf(fd, "flash_addr           : " UH_FMT "\n", ptr_struct->flash_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "relative_addr        : " UH_FMT "\n", ptr_struct->relative_addr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "section_crc          : " UH_FMT "\n", ptr_struct->section_crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_crc               : " UH_FMT "\n", ptr_struct->no_crc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_data          : " UH_FMT "\n", ptr_struct->device_data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);
}

unsigned int cibfw_itoc_entry_size(void)
{
	return CIBFW_ITOC_ENTRY_SIZE;
}

void cibfw_itoc_entry_dump(const struct cibfw_itoc_entry *ptr_struct, FILE *fd)
{
	cibfw_itoc_entry_print(ptr_struct, fd, 0);
}

void cibfw_itoc_header_pack(const struct cibfw_itoc_header *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);
}

void cibfw_itoc_header_unpack(struct cibfw_itoc_header *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void cibfw_itoc_header_print(const struct cibfw_itoc_header *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_itoc_header ========\n");

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
	fprintf(fd, "itoc_entry_crc       : " UH_FMT "\n", ptr_struct->itoc_entry_crc);
}

unsigned int cibfw_itoc_header_size(void)
{
	return CIBFW_ITOC_HEADER_SIZE;
}

void cibfw_itoc_header_dump(const struct cibfw_itoc_header *ptr_struct, FILE *fd)
{
	cibfw_itoc_header_print(ptr_struct, fd, 0);
}

void cibfw_mfg_info_pack(const struct cibfw_mfg_info *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 255;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->guids_override_en);
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);
	offset = 256;
	cibfw_guids_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
}

void cibfw_mfg_info_unpack(struct cibfw_mfg_info *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
		ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
		ptr_struct->psid[16] = '\0';
	offset = 255;
	ptr_struct->guids_override_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 232;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 224;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 256;
	cibfw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
}

void cibfw_mfg_info_print(const struct cibfw_mfg_info *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_mfg_info ========\n");

		fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guids_override_en    : " UH_FMT "\n", ptr_struct->guids_override_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guids:\n");
	cibfw_guids_print(&(ptr_struct->guids), fd, indent_level + 1);
}

unsigned int cibfw_mfg_info_size(void)
{
	return CIBFW_MFG_INFO_SIZE;
}

void cibfw_mfg_info_dump(const struct cibfw_mfg_info *ptr_struct, FILE *fd)
{
	cibfw_mfg_info_print(ptr_struct, fd, 0);
}

void cibfw_register_mfai_pack(const struct cibfw_register_mfai *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->address);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->permanent);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->use_address);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->use_image_id);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_id);
}

void cibfw_register_mfai_unpack(struct cibfw_register_mfai *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->address = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 2;
	ptr_struct->permanent = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->use_address = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->use_image_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->image_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void cibfw_register_mfai_print(const struct cibfw_register_mfai *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_register_mfai ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " UH_FMT "\n", ptr_struct->address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "permanent            : " UH_FMT "\n", ptr_struct->permanent);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "use_address          : " UH_FMT "\n", ptr_struct->use_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "use_image_id         : " UH_FMT "\n", ptr_struct->use_image_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_id             : " UH_FMT "\n", ptr_struct->image_id);
}

unsigned int cibfw_register_mfai_size(void)
{
	return CIBFW_REGISTER_MFAI_SIZE;
}

void cibfw_register_mfai_dump(const struct cibfw_register_mfai *ptr_struct, FILE *fd)
{
	cibfw_register_mfai_print(ptr_struct, fd, 0);
}

void cibfw_register_mfrl_pack(const struct cibfw_register_mfrl *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reset_level);
}

void cibfw_register_mfrl_unpack(struct cibfw_register_mfrl *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->reset_level = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void cibfw_register_mfrl_print(const struct cibfw_register_mfrl *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_register_mfrl ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reset_level          : " UH_FMT "\n", ptr_struct->reset_level);
}

unsigned int cibfw_register_mfrl_size(void)
{
	return CIBFW_REGISTER_MFRL_SIZE;
}

void cibfw_register_mfrl_dump(const struct cibfw_register_mfrl *ptr_struct, FILE *fd)
{
	cibfw_register_mfrl_print(ptr_struct, fd, 0);
}

void cibfw_cibfw_Nodes_pack(const union cibfw_cibfw_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	cibfw_image_info_pack(&(ptr_struct->image_info), ptr_buff);
}

void cibfw_cibfw_Nodes_unpack(union cibfw_cibfw_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	cibfw_image_info_unpack(&(ptr_struct->image_info), ptr_buff);
}

void cibfw_cibfw_Nodes_print(const union cibfw_cibfw_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== cibfw_cibfw_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "register_mfai:\n");
	cibfw_register_mfai_print(&(ptr_struct->register_mfai), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_entry:\n");
	cibfw_itoc_entry_print(&(ptr_struct->itoc_entry), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "guids:\n");
	cibfw_guids_print(&(ptr_struct->guids), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itoc_header:\n");
	cibfw_itoc_header_print(&(ptr_struct->itoc_header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "register_mfrl:\n");
	cibfw_register_mfrl_print(&(ptr_struct->register_mfrl), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_info:\n");
	cibfw_device_info_print(&(ptr_struct->device_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfg_info:\n");
	cibfw_mfg_info_print(&(ptr_struct->mfg_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info:\n");
	cibfw_image_info_print(&(ptr_struct->image_info), fd, indent_level + 1);
}

unsigned int cibfw_cibfw_Nodes_size(void)
{
	return CIBFW_CIBFW_NODES_SIZE;
}

void cibfw_cibfw_Nodes_dump(const union cibfw_cibfw_Nodes *ptr_struct, FILE *fd)
{
	cibfw_cibfw_Nodes_print(ptr_struct, fd, 0);
}

