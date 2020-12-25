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
         *** This file was generated at "2019-03-23 21:38:49"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/register_access/register_access_sib.adb --file-prefix register_access_sib --prefix register_access_sib_
         ***/
#include "register_access_sib_layouts.h"

void register_access_sib_IB_PSID__pack(const struct register_access_sib_IB_PSID_ *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->PS_ID[i]);
	}
}

void register_access_sib_IB_PSID__unpack(struct register_access_sib_IB_PSID_ *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		ptr_struct->PS_ID[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void register_access_sib_IB_PSID__print(const struct register_access_sib_IB_PSID_ *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_IB_PSID_ ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "PS_ID_%03d           : " U32H_FMT "\n", i, ptr_struct->PS_ID[i]);
	}
}

unsigned int register_access_sib_IB_PSID__size(void)
{
	return REGISTER_ACCESS_SIB_IB_PSID__SIZE;
}

void register_access_sib_IB_PSID__dump(const struct register_access_sib_IB_PSID_ *ptr_struct, FILE *fd)
{
	register_access_sib_IB_PSID__print(ptr_struct, fd, 0);
}

void register_access_sib_IB_DEVInfo__pack(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 7; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 224, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dev_branch_tag[i]);
	}
}

void register_access_sib_IB_DEVInfo__unpack(struct register_access_sib_IB_DEVInfo_ *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 7; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 224, 1);
		ptr_struct->dev_branch_tag[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void register_access_sib_IB_DEVInfo__print(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_IB_DEVInfo_ ========\n");

	for (i = 0; i < 7; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dev_branch_tag_%03d  : " U32H_FMT "\n", i, ptr_struct->dev_branch_tag[i]);
	}
}

unsigned int register_access_sib_IB_DEVInfo__size(void)
{
	return REGISTER_ACCESS_SIB_IB_DEVINFO__SIZE;
}

void register_access_sib_IB_DEVInfo__dump(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, FILE *fd)
{
	register_access_sib_IB_DEVInfo__print(ptr_struct, fd, 0);
}

void register_access_sib_IB_FWInfo__pack(const struct register_access_sib_IB_FWInfo_ *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->SubMinor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Major);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->BuildID);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->Year);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Day);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Month);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->Hour);
	offset = 128;
	register_access_sib_IB_PSID__pack(&(ptr_struct->PSID), ptr_buff + offset / 8);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->INIFileNum);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_major);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_minor);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_subminor);
}

void register_access_sib_IB_FWInfo__unpack(struct register_access_sib_IB_FWInfo_ *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->SubMinor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->Minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->Major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->BuildID = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->Year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->Day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->Month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->Hour = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	register_access_sib_IB_PSID__unpack(&(ptr_struct->PSID), ptr_buff + offset / 8);
	offset = 256;
	ptr_struct->INIFileNum = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->extended_major = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->extended_minor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->extended_subminor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void register_access_sib_IB_FWInfo__print(const struct register_access_sib_IB_FWInfo_ *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_IB_FWInfo_ ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "SubMinor             : " UH_FMT "\n", ptr_struct->SubMinor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Minor                : " UH_FMT "\n", ptr_struct->Minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Major                : " UH_FMT "\n", ptr_struct->Major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "BuildID              : " U32H_FMT "\n", ptr_struct->BuildID);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Year                 : " UH_FMT "\n", ptr_struct->Year);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Day                  : " UH_FMT "\n", ptr_struct->Day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Month                : " UH_FMT "\n", ptr_struct->Month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "Hour                 : " UH_FMT "\n", ptr_struct->Hour);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PSID:\n");
	register_access_sib_IB_PSID__print(&(ptr_struct->PSID), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "INIFileNum           : " U32H_FMT "\n", ptr_struct->INIFileNum);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_major       : " U32H_FMT "\n", ptr_struct->extended_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_minor       : " U32H_FMT "\n", ptr_struct->extended_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_subminor    : " U32H_FMT "\n", ptr_struct->extended_subminor);
}

unsigned int register_access_sib_IB_FWInfo__size(void)
{
	return REGISTER_ACCESS_SIB_IB_FWINFO__SIZE;
}

void register_access_sib_IB_FWInfo__dump(const struct register_access_sib_IB_FWInfo_ *ptr_struct, FILE *fd)
{
	register_access_sib_IB_FWInfo__print(ptr_struct, fd, 0);
}

void register_access_sib_IB_HWInfo__pack(const struct register_access_sib_IB_HWInfo_ *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->DEVID);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->REVID);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_dev_id);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->UpTime);
}

void register_access_sib_IB_HWInfo__unpack(struct register_access_sib_IB_HWInfo_ *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->DEVID = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->REVID = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 59;
	ptr_struct->pvs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->hw_dev_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->UpTime = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void register_access_sib_IB_HWInfo__print(const struct register_access_sib_IB_HWInfo_ *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_IB_HWInfo_ ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DEVID                : " UH_FMT "\n", ptr_struct->DEVID);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "REVID                : " UH_FMT "\n", ptr_struct->REVID);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs                  : " UH_FMT "\n", ptr_struct->pvs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_dev_id            : " UH_FMT "\n", ptr_struct->hw_dev_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "UpTime               : " U32H_FMT "\n", ptr_struct->UpTime);
}

unsigned int register_access_sib_IB_HWInfo__size(void)
{
	return REGISTER_ACCESS_SIB_IB_HWINFO__SIZE;
}

void register_access_sib_IB_HWInfo__dump(const struct register_access_sib_IB_HWInfo_ *ptr_struct, FILE *fd)
{
	register_access_sib_IB_HWInfo__print(ptr_struct, fd, 0);
}

void register_access_sib_IB_SWInfo__pack(const struct register_access_sib_IB_SWInfo_ *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->VerSubMinor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->VerMinor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->VerMajor);
}

void register_access_sib_IB_SWInfo__unpack(struct register_access_sib_IB_SWInfo_ *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->VerSubMinor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->VerMinor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->VerMajor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void register_access_sib_IB_SWInfo__print(const struct register_access_sib_IB_SWInfo_ *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_IB_SWInfo_ ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VerSubMinor          : " UH_FMT "\n", ptr_struct->VerSubMinor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VerMinor             : " UH_FMT "\n", ptr_struct->VerMinor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VerMajor             : " UH_FMT "\n", ptr_struct->VerMajor);
}

unsigned int register_access_sib_IB_SWInfo__size(void)
{
	return REGISTER_ACCESS_SIB_IB_SWINFO__SIZE;
}

void register_access_sib_IB_SWInfo__dump(const struct register_access_sib_IB_SWInfo_ *ptr_struct, FILE *fd)
{
	register_access_sib_IB_SWInfo__print(ptr_struct, fd, 0);
}

void register_access_sib_mgir_pack(const struct register_access_sib_mgir *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	register_access_sib_IB_HWInfo__pack(&(ptr_struct->HWInfo), ptr_buff + offset / 8);
	offset = 256;
	register_access_sib_IB_FWInfo__pack(&(ptr_struct->FWInfo), ptr_buff + offset / 8);
	offset = 768;
	register_access_sib_IB_SWInfo__pack(&(ptr_struct->SWInfo), ptr_buff + offset / 8);
	offset = 1024;
	register_access_sib_IB_DEVInfo__pack(&(ptr_struct->DEVInfo), ptr_buff + offset / 8);
}

void register_access_sib_mgir_unpack(struct register_access_sib_mgir *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	register_access_sib_IB_HWInfo__unpack(&(ptr_struct->HWInfo), ptr_buff + offset / 8);
	offset = 256;
	register_access_sib_IB_FWInfo__unpack(&(ptr_struct->FWInfo), ptr_buff + offset / 8);
	offset = 768;
	register_access_sib_IB_SWInfo__unpack(&(ptr_struct->SWInfo), ptr_buff + offset / 8);
	offset = 1024;
	register_access_sib_IB_DEVInfo__unpack(&(ptr_struct->DEVInfo), ptr_buff + offset / 8);
}

void register_access_sib_mgir_print(const struct register_access_sib_mgir *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_mgir ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "HWInfo:\n");
	register_access_sib_IB_HWInfo__print(&(ptr_struct->HWInfo), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FWInfo:\n");
	register_access_sib_IB_FWInfo__print(&(ptr_struct->FWInfo), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "SWInfo:\n");
	register_access_sib_IB_SWInfo__print(&(ptr_struct->SWInfo), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DEVInfo:\n");
	register_access_sib_IB_DEVInfo__print(&(ptr_struct->DEVInfo), fd, indent_level + 1);
}

unsigned int register_access_sib_mgir_size(void)
{
	return REGISTER_ACCESS_SIB_MGIR_SIZE;
}

void register_access_sib_mgir_dump(const struct register_access_sib_mgir *ptr_struct, FILE *fd)
{
	register_access_sib_mgir_print(ptr_struct, fd, 0);
}

void register_access_sib_mtmp_pack(const struct register_access_sib_mtmp *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->internal_diodes_query);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mss);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_temperture);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtr);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mte);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_hi);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tee);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_lo);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->name_hi);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->name_lo);
}

void register_access_sib_mtmp_unpack(struct register_access_sib_mtmp *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->sensor_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 0;
	ptr_struct->internal_diodes_query = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->mss = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 80;
	ptr_struct->max_temperture = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 65;
	ptr_struct->mtr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->mte = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 112;
	ptr_struct->temperature_threshold_hi = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->tee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 144;
	ptr_struct->temperature_threshold_lo = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->name_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->name_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void register_access_sib_mtmp_print(const struct register_access_sib_mtmp *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_mtmp ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_index         : " UH_FMT "\n", ptr_struct->sensor_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "internal_diodes_query : " UH_FMT "\n", ptr_struct->internal_diodes_query);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mss                  : " UH_FMT "\n", ptr_struct->mss);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_temperture       : " UH_FMT "\n", ptr_struct->max_temperture);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtr                  : " UH_FMT "\n", ptr_struct->mtr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mte                  : " UH_FMT "\n", ptr_struct->mte);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_hi : " UH_FMT "\n", ptr_struct->temperature_threshold_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tee                  : " UH_FMT "\n", ptr_struct->tee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_lo : " UH_FMT "\n", ptr_struct->temperature_threshold_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "name_hi              : " U32H_FMT "\n", ptr_struct->name_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "name_lo              : " U32H_FMT "\n", ptr_struct->name_lo);
}

unsigned int register_access_sib_mtmp_size(void)
{
	return REGISTER_ACCESS_SIB_MTMP_SIZE;
}

void register_access_sib_mtmp_dump(const struct register_access_sib_mtmp *ptr_struct, FILE *fd)
{
	register_access_sib_mtmp_print(ptr_struct, fd, 0);
}

void register_access_sib_pmaos_pack(const struct register_access_sib_pmaos *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rst);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->e);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_type);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
}

void register_access_sib_pmaos_unpack(struct register_access_sib_pmaos *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->rst = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 52;
	ptr_struct->error_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void register_access_sib_pmaos_print(const struct register_access_sib_pmaos *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_pmaos ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : " UH_FMT "\n", ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : " UH_FMT "\n", ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst                  : " UH_FMT "\n", ptr_struct->rst);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : " UH_FMT "\n", ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type           : " UH_FMT "\n", ptr_struct->error_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
}

unsigned int register_access_sib_pmaos_size(void)
{
	return REGISTER_ACCESS_SIB_PMAOS_SIZE;
}

void register_access_sib_pmaos_dump(const struct register_access_sib_pmaos *ptr_struct, FILE *fd)
{
	register_access_sib_pmaos_print(ptr_struct, fd, 0);
}

void register_access_sib_register_access_sib_Nodes_pack(const union register_access_sib_register_access_sib_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	register_access_sib_mgir_pack(&(ptr_struct->mgir), ptr_buff);
}

void register_access_sib_register_access_sib_Nodes_unpack(union register_access_sib_register_access_sib_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	register_access_sib_mgir_unpack(&(ptr_struct->mgir), ptr_buff);
}

void register_access_sib_register_access_sib_Nodes_print(const union register_access_sib_register_access_sib_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== register_access_sib_register_access_sib_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtmp:\n");
	register_access_sib_mtmp_print(&(ptr_struct->mtmp), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos:\n");
	register_access_sib_pmaos_print(&(ptr_struct->pmaos), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir:\n");
	register_access_sib_mgir_print(&(ptr_struct->mgir), fd, indent_level + 1);
}

unsigned int register_access_sib_register_access_sib_Nodes_size(void)
{
	return REGISTER_ACCESS_SIB_REGISTER_ACCESS_SIB_NODES_SIZE;
}

void register_access_sib_register_access_sib_Nodes_dump(const union register_access_sib_register_access_sib_Nodes *ptr_struct, FILE *fd)
{
	register_access_sib_register_access_sib_Nodes_print(ptr_struct, fd, 0);
}

