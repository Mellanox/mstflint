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
 *** This file was generated at "2014-03-23 17:16:21"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/cibfw/cibfw.adb --file-prefix cibfw --prefix cibfw_
 ***/
#include "cibfw_layouts.h"

void cibfw_uint64_pack(const struct cibfw_uint64 *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->hi);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->lo);

}

void cibfw_uint64_unpack(struct cibfw_uint64 *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void cibfw_uint64_print(const struct cibfw_uint64 *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== uint64 ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "hi                   : "U32H_FMT"\n", ptr_struct->hi);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lo                   : "U32H_FMT"\n", ptr_struct->lo);

}

int cibfw_uint64_size(){
	 return 8;
}

void cibfw_uint64_dump(const struct cibfw_uint64 *ptr_struct, FILE* file) {
	cibfw_uint64_print(ptr_struct, file, 0);
}

void cibfw_uid_entry_pack(const struct cibfw_uid_entry *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->uid);

}

void cibfw_uid_entry_unpack(struct cibfw_uid_entry *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=16;
	ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=64;
	ptr_struct->uid = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cibfw_uid_entry_print(const struct cibfw_uid_entry *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== uid_entry ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_allocated        : "UH_FMT"\n", ptr_struct->num_allocated);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "step                 : "UH_FMT"\n", ptr_struct->step);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uid                  : "U64H_FMT"\n", ptr_struct->uid);

}

int cibfw_uid_entry_size(){
	 return 16;
}

void cibfw_uid_entry_dump(const struct cibfw_uid_entry *ptr_struct, FILE* file) {
	cibfw_uid_entry_print(ptr_struct, file, 0);
}

void cibfw_TRIPPLE_VERSION_pack(const struct cibfw_TRIPPLE_VERSION *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);

}

void cibfw_TRIPPLE_VERSION_unpack(struct cibfw_TRIPPLE_VERSION *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=48;
	ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=32;
	ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cibfw_TRIPPLE_VERSION_print(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== TRIPPLE_VERSION ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MAJOR                : "UH_FMT"\n", ptr_struct->MAJOR);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "SUBMINOR             : "UH_FMT"\n", ptr_struct->SUBMINOR);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MINOR                : "UH_FMT"\n", ptr_struct->MINOR);

}

int cibfw_TRIPPLE_VERSION_size(){
	 return 8;
}

void cibfw_TRIPPLE_VERSION_dump(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE* file) {
	cibfw_TRIPPLE_VERSION_print(ptr_struct, file, 0);
}

void cibfw_FW_VERSION_pack(const struct cibfw_FW_VERSION *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Hour);

	offset=72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Minutes);

	offset=64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Seconds);

	offset=120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Day);

	offset=112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->Month);

	offset=96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->Year);

}

void cibfw_FW_VERSION_unpack(struct cibfw_FW_VERSION *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=48;
	ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=32;
	ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=80;
	ptr_struct->Hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=72;
	ptr_struct->Minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=64;
	ptr_struct->Seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=120;
	ptr_struct->Day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=112;
	ptr_struct->Month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=96;
	ptr_struct->Year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cibfw_FW_VERSION_print(const struct cibfw_FW_VERSION *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== FW_VERSION ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MAJOR                : "UH_FMT"\n", ptr_struct->MAJOR);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "SUBMINOR             : "UH_FMT"\n", ptr_struct->SUBMINOR);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MINOR                : "UH_FMT"\n", ptr_struct->MINOR);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Hour                 : "UH_FMT"\n", ptr_struct->Hour);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Minutes              : "UH_FMT"\n", ptr_struct->Minutes);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Seconds              : "UH_FMT"\n", ptr_struct->Seconds);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Day                  : "UH_FMT"\n", ptr_struct->Day);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Month                : "UH_FMT"\n", ptr_struct->Month);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "Year                 : "UH_FMT"\n", ptr_struct->Year);

}

int cibfw_FW_VERSION_size(){
	 return 16;
}

void cibfw_FW_VERSION_dump(const struct cibfw_FW_VERSION *ptr_struct, FILE* file) {
	cibfw_FW_VERSION_print(ptr_struct, file, 0);
}

void cibfw_guids_pack(const struct cibfw_guids *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i=0; i < 2; i++) {
	offset=adb2c_calc_array_field_address(0, 128, i, 512, 1);
	cibfw_uid_entry_pack(&(ptr_struct->guids[i]), ptr_buff + offset/8);
	}

	for (i=0; i < 2; i++) {
	offset=adb2c_calc_array_field_address(256, 128, i, 512, 1);
	cibfw_uid_entry_pack(&(ptr_struct->macs[i]), ptr_buff + offset/8);
	}

}

void cibfw_guids_unpack(struct cibfw_guids *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i=0; i < 2; i++) {
	offset=adb2c_calc_array_field_address(0, 128, i, 512, 1);
	cibfw_uid_entry_unpack(&(ptr_struct->guids[i]), ptr_buff + offset/8);
	}

	for (i=0; i < 2; i++) {
	offset=adb2c_calc_array_field_address(256, 128, i, 512, 1);
	cibfw_uid_entry_unpack(&(ptr_struct->macs[i]), ptr_buff + offset/8);
	}

}

void cibfw_guids_print(const struct cibfw_guids *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== guids ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	for (i=0; i < 2; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids[%3d]:\n", i);
	cibfw_uid_entry_print(&(ptr_struct->guids[i]), file, indent_level + 1);
	}

	for (i=0; i < 2; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "macs[%3d]:\n", i);
	cibfw_uid_entry_print(&(ptr_struct->macs[i]), file, indent_level + 1);
	}

}

int cibfw_guids_size(){
	 return 64;
}

void cibfw_guids_dump(const struct cibfw_guids *ptr_struct, FILE* file) {
	cibfw_guids_print(ptr_struct, file, 0);
}

void cibfw_operation_key_pack(const struct cibfw_operation_key *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->key_modifier);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);

}

void cibfw_operation_key_unpack(struct cibfw_operation_key *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->key_modifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cibfw_operation_key_print(const struct cibfw_operation_key *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== operation_key ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key_modifier         : "UH_FMT"\n", ptr_struct->key_modifier);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key                  : "U64H_FMT"\n", ptr_struct->key);

}

int cibfw_operation_key_size(){
	 return 16;
}

void cibfw_operation_key_dump(const struct cibfw_operation_key *ptr_struct, FILE* file) {
	cibfw_operation_key_print(ptr_struct, file, 0);
}

void cibfw_image_info_pack(const struct cibfw_image_info *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=32;
	cibfw_FW_VERSION_pack(&(ptr_struct->FW_VERSION), ptr_buff + offset/8);

	offset=160;
	cibfw_TRIPPLE_VERSION_pack(&(ptr_struct->mic_version), ptr_buff + offset/8);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(312, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}

	offset=432;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);

	for (i=0; i < 208; i++) {
	offset=adb2c_calc_array_field_address(472, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}

	for (i=0; i < 4; i++) {
	offset=adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->supported_hw_id[i]);
	}

	offset=2368;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->ini_file_num);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prod_ver[i]);
	}

}

void cibfw_image_info_unpack(struct cibfw_image_info *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=32;
	cibfw_FW_VERSION_unpack(&(ptr_struct->FW_VERSION), ptr_buff + offset/8);

	offset=160;
	cibfw_TRIPPLE_VERSION_unpack(&(ptr_struct->mic_version), ptr_buff + offset/8);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(312, 8, i, 8192, 1);
	ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->psid[16] = '\0';
	offset=432;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	for (i=0; i < 208; i++) {
	offset=adb2c_calc_array_field_address(472, 8, i, 8192, 1);
	ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->vsd[208] = '\0';
	for (i=0; i < 4; i++) {
	offset=adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
	ptr_struct->supported_hw_id[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}

	offset=2368;
	ptr_struct->ini_file_num = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
	ptr_struct->prod_ver[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->prod_ver[16] = '\0';
}

void cibfw_image_info_print(const struct cibfw_image_info *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== image_info ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "FW_VERSION:\n");
	cibfw_FW_VERSION_print(&(ptr_struct->FW_VERSION), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mic_version:\n");
	cibfw_TRIPPLE_VERSION_print(&(ptr_struct->mic_version), file, indent_level + 1);

	fprintf(file, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vsd_vendor_id        : "UH_FMT"\n", ptr_struct->vsd_vendor_id);

	fprintf(file, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i=0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "supported_hw_id[%3d] : "U32H_FMT"\n", i, ptr_struct->supported_hw_id[i]);
	}

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ini_file_num         : "U32H_FMT"\n", ptr_struct->ini_file_num);

	fprintf(file, "prod_ver             : \"%s\"\n", ptr_struct->prod_ver);
}

int cibfw_image_info_size(){
	 return 1024;
}

void cibfw_image_info_dump(const struct cibfw_image_info *ptr_struct, FILE* file) {
	cibfw_image_info_print(ptr_struct, file, 0);
}

void cibfw_mfg_info_pack(const struct cibfw_mfg_info *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(24, 8, i, 2560, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}

	offset=255;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->guids_override_en);

	offset=256;
	cibfw_guids_pack(&(ptr_struct->guids), ptr_buff + offset/8);

}

void cibfw_mfg_info_unpack(struct cibfw_mfg_info *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(24, 8, i, 2560, 1);
	ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->psid[16] = '\0';
	offset=255;
	ptr_struct->guids_override_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=256;
	cibfw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

}

void cibfw_mfg_info_print(const struct cibfw_mfg_info *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mfg_info ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	fprintf(file, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids_override_en    : "UH_FMT"\n", ptr_struct->guids_override_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cibfw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

}

int cibfw_mfg_info_size(){
	 return 320;
}

void cibfw_mfg_info_dump(const struct cibfw_mfg_info *ptr_struct, FILE* file) {
	cibfw_mfg_info_print(ptr_struct, file, 0);
}

void cibfw_device_info_pack(const struct cibfw_device_info *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature0);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature1);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature2);

	offset=96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature3);

	offset=152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset=143;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->major_version);

	offset=256;
	cibfw_guids_pack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset=880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);

	for (i=0; i < 208; i++) {
	offset=adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}

	for (i=0; i < 4; i++) {
	offset=adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cibfw_operation_key_pack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

}

void cibfw_device_info_unpack(struct cibfw_device_info *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=152;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=143;
	ptr_struct->major_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);

	offset=256;
	cibfw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset=880;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	for (i=0; i < 208; i++) {
	offset=adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->vsd[208] = '\0';
	for (i=0; i < 4; i++) {
	offset=adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cibfw_operation_key_unpack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

}

void cibfw_device_info_print(const struct cibfw_device_info *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== device_info ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature0           : "U32H_FMT"\n", ptr_struct->signature0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature1           : "U32H_FMT"\n", ptr_struct->signature1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature2           : "U32H_FMT"\n", ptr_struct->signature2);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature3           : "U32H_FMT"\n", ptr_struct->signature3);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : "UH_FMT"\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : "UH_FMT"\n", ptr_struct->major_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cibfw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vsd_vendor_id        : "UH_FMT"\n", ptr_struct->vsd_vendor_id);

	fprintf(file, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i=0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "keys[%3d]:\n", i);
	cibfw_operation_key_print(&(ptr_struct->keys[i]), file, indent_level + 1);
	}

}

int cibfw_device_info_size(){
	 return 512;
}

void cibfw_device_info_dump(const struct cibfw_device_info *ptr_struct, FILE* file) {
	cibfw_device_info_print(ptr_struct, file, 0);
}

void cibfw_itoc_header_pack(const struct cibfw_itoc_header *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature0);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature1);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature2);

	offset=96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->signature3);

	offset=152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);

	offset=240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);

}

void cibfw_itoc_header_unpack(struct cibfw_itoc_header *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=152;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cibfw_itoc_header_print(const struct cibfw_itoc_header *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== itoc_header ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature0           : "U32H_FMT"\n", ptr_struct->signature0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature1           : "U32H_FMT"\n", ptr_struct->signature1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature2           : "U32H_FMT"\n", ptr_struct->signature2);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature3           : "U32H_FMT"\n", ptr_struct->signature3);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : "UH_FMT"\n", ptr_struct->version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry_crc       : "UH_FMT"\n", ptr_struct->itoc_entry_crc);

}

int cibfw_itoc_header_size(){
	 return 32;
}

void cibfw_itoc_header_dump(const struct cibfw_itoc_header *ptr_struct, FILE* file) {
	cibfw_itoc_header_print(ptr_struct, file, 0);
}

void cibfw_itoc_entry_pack(const struct cibfw_itoc_entry *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 22, (u_int32_t)ptr_struct->size);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);

	offset=34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 30, (u_int32_t)ptr_struct->param0);

	offset=33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cache_line_crc);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->zipped_image);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->param1);

	offset=161;
	adb2c_push_bits_to_buff(ptr_buff, offset, 29, (u_int32_t)ptr_struct->flash_addr);

	offset=160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->relative_addr);

	offset=208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->section_crc);

	offset=207;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->no_crc);

	offset=206;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->device_data);

	offset=240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->itoc_entry_crc);

}

void cibfw_itoc_entry_unpack(struct cibfw_itoc_entry *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	ptr_struct->size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 22);

	offset=0;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=34;
	ptr_struct->param0 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 30);

	offset=33;
	ptr_struct->cache_line_crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->zipped_image = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=64;
	ptr_struct->param1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=161;
	ptr_struct->flash_addr = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 29);

	offset=160;
	ptr_struct->relative_addr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=208;
	ptr_struct->section_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=207;
	ptr_struct->no_crc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=206;
	ptr_struct->device_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=240;
	ptr_struct->itoc_entry_crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void cibfw_itoc_entry_print(const struct cibfw_itoc_entry *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== itoc_entry ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "size                 : "UH_FMT"\n", ptr_struct->size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type                 : "UH_FMT"\n", ptr_struct->type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param0               : "UH_FMT"\n", ptr_struct->param0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "cache_line_crc       : "UH_FMT"\n", ptr_struct->cache_line_crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "zipped_image         : "UH_FMT"\n", ptr_struct->zipped_image);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param1               : "U32H_FMT"\n", ptr_struct->param1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_addr           : "UH_FMT"\n", ptr_struct->flash_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "relative_addr        : "UH_FMT"\n", ptr_struct->relative_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "section_crc          : "UH_FMT"\n", ptr_struct->section_crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "no_crc               : "UH_FMT"\n", ptr_struct->no_crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "device_data          : "UH_FMT"\n", ptr_struct->device_data);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry_crc       : "UH_FMT"\n", ptr_struct->itoc_entry_crc);

}

int cibfw_itoc_entry_size(){
	 return 32;
}

void cibfw_itoc_entry_dump(const struct cibfw_itoc_entry *ptr_struct, FILE* file) {
	cibfw_itoc_entry_print(ptr_struct, file, 0);
}

void cibfw_Nodes_pack(const union cibfw_Nodes *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 1024);
}

void cibfw_Nodes_unpack(union cibfw_Nodes *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 1024);
}

void cibfw_Nodes_print(const union cibfw_Nodes *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== Nodes ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_entry:\n");
	cibfw_itoc_entry_print(&(ptr_struct->itoc_entry), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cibfw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "itoc_header:\n");
	cibfw_itoc_header_print(&(ptr_struct->itoc_header), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "device_info:\n");
	cibfw_device_info_print(&(ptr_struct->device_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfg_info:\n");
	cibfw_mfg_info_print(&(ptr_struct->mfg_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_info:\n");
	cibfw_image_info_print(&(ptr_struct->image_info), file, indent_level + 1);

}

int cibfw_Nodes_size(){
	 return 1024;
}

void cibfw_Nodes_dump(const union cibfw_Nodes *ptr_struct, FILE* file) {
	cibfw_Nodes_print(ptr_struct, file, 0);
}

