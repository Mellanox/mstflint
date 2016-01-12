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
 *** This file was generated at "2016-05-04 19:06:49"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_
 ***/
#include "tools_open_layouts.h"

void tools_open_tlv_type_dw_pack(const struct tools_open_tlv_type_dw *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->tlv_type_dw);

}

void tools_open_tlv_type_dw_unpack(struct tools_open_tlv_type_dw *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->tlv_type_dw = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_tlv_type_dw_print(const struct tools_open_tlv_type_dw *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_tlv_type_dw ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tlv_type_dw          : "U32H_FMT"\n", ptr_struct->tlv_type_dw);

}

int tools_open_tlv_type_dw_size(void){
	 return 4;
}

void tools_open_tlv_type_dw_dump(const struct tools_open_tlv_type_dw *ptr_struct, FILE* file) {
	tools_open_tlv_type_dw_print(ptr_struct, file, 0);
}

void tools_open_per_port_type_pack(const struct tools_open_per_port_type *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->param_idx);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);

}

void tools_open_per_port_type_unpack(struct tools_open_per_port_type *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=8;
	ptr_struct->port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_per_port_type_print(const struct tools_open_per_port_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_per_port_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_idx            : "UH_FMT"\n", ptr_struct->param_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "port                 : "UH_FMT"\n", ptr_struct->port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_class          : "UH_FMT"\n", ptr_struct->param_class);

}

int tools_open_per_port_type_size(void){
	 return 4;
}

void tools_open_per_port_type_dump(const struct tools_open_per_port_type *ptr_struct, FILE* file) {
	tools_open_per_port_type_print(ptr_struct, file, 0);
}

void tools_open_bmc_type_pack(const struct tools_open_bmc_type *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->param_idx);

	offset=14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->channel);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);

}

void tools_open_bmc_type_unpack(struct tools_open_bmc_type *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=19;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);

	offset=14;
	ptr_struct->channel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset=8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_bmc_type_print(const struct tools_open_bmc_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_bmc_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_idx            : "UH_FMT"\n", ptr_struct->param_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "channel              : "UH_FMT"\n", ptr_struct->channel);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "host                 : "UH_FMT"\n", ptr_struct->host);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_class          : "UH_FMT"\n", ptr_struct->param_class);

}

int tools_open_bmc_type_size(void){
	 return 4;
}

void tools_open_bmc_type_dump(const struct tools_open_bmc_type *ptr_struct, FILE* file) {
	tools_open_bmc_type_print(ptr_struct, file, 0);
}

void tools_open_per_host_type_pack(const struct tools_open_per_host_type *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->param_idx);

	offset=14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->function);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);

}

void tools_open_per_host_type_unpack(struct tools_open_per_host_type *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=14;
	ptr_struct->function = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_per_host_type_print(const struct tools_open_per_host_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_per_host_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_idx            : "UH_FMT"\n", ptr_struct->param_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "function             : "UH_FMT"\n", ptr_struct->function);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "host                 : "UH_FMT"\n", ptr_struct->host);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_class          : "UH_FMT"\n", ptr_struct->param_class);

}

int tools_open_per_host_type_size(void){
	 return 4;
}

void tools_open_per_host_type_dump(const struct tools_open_per_host_type *ptr_struct, FILE* file) {
	tools_open_per_host_type_print(ptr_struct, file, 0);
}

void tools_open_eswitch_type_pack(const struct tools_open_eswitch_type *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->param_idx);

	offset=14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->port);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->host);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);

}

void tools_open_eswitch_type_unpack(struct tools_open_eswitch_type *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->param_idx = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=14;
	ptr_struct->port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=8;
	ptr_struct->host = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_eswitch_type_print(const struct tools_open_eswitch_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_eswitch_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_idx            : "UH_FMT"\n", ptr_struct->param_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "port                 : "UH_FMT"\n", ptr_struct->port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "host                 : "UH_FMT"\n", ptr_struct->host);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_class          : "UH_FMT"\n", ptr_struct->param_class);

}

int tools_open_eswitch_type_size(void){
	 return 4;
}

void tools_open_eswitch_type_dump(const struct tools_open_eswitch_type *ptr_struct, FILE* file) {
	tools_open_eswitch_type_print(ptr_struct, file, 0);
}

void tools_open_global_type_pack(const struct tools_open_global_type *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->param_idx);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->param_class);

}

void tools_open_global_type_unpack(struct tools_open_global_type *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	ptr_struct->param_idx = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset=0;
	ptr_struct->param_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_global_type_print(const struct tools_open_global_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_global_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_idx            : "UH_FMT"\n", ptr_struct->param_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "param_class          : "UH_FMT"\n", ptr_struct->param_class);

}

int tools_open_global_type_size(void){
	 return 4;
}

void tools_open_global_type_dump(const struct tools_open_global_type *ptr_struct, FILE* file) {
	tools_open_global_type_print(ptr_struct, file, 0);
}

void tools_open_ts_entry_pack(const struct tools_open_ts_entry *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_day);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_month);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ts_year);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_seconds);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_minutes);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ts_hour);

}

void tools_open_ts_entry_unpack(struct tools_open_ts_entry *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->ts_day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=16;
	ptr_struct->ts_month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->ts_year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=48;
	ptr_struct->ts_seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=40;
	ptr_struct->ts_minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=32;
	ptr_struct->ts_hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_ts_entry_print(const struct tools_open_ts_entry *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_ts_entry ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_day               : "UH_FMT"\n", ptr_struct->ts_day);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_month             : "UH_FMT"\n", ptr_struct->ts_month);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_year              : "UH_FMT"\n", ptr_struct->ts_year);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_seconds           : "UH_FMT"\n", ptr_struct->ts_seconds);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_minutes           : "UH_FMT"\n", ptr_struct->ts_minutes);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_hour              : "UH_FMT"\n", ptr_struct->ts_hour);

}

int tools_open_ts_entry_size(void){
	 return 8;
}

void tools_open_ts_entry_dump(const struct tools_open_ts_entry *ptr_struct, FILE* file) {
	tools_open_ts_entry_print(ptr_struct, file, 0);
}

void tools_open_fw_version_pack(const struct tools_open_fw_version *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_major);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_subminor);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_ver_minor);

}

void tools_open_fw_version_unpack(struct tools_open_fw_version *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->fw_ver_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=48;
	ptr_struct->fw_ver_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=32;
	ptr_struct->fw_ver_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void tools_open_fw_version_print(const struct tools_open_fw_version *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_fw_version ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_ver_major         : "UH_FMT"\n", ptr_struct->fw_ver_major);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_ver_subminor      : "UH_FMT"\n", ptr_struct->fw_ver_subminor);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_ver_minor         : "UH_FMT"\n", ptr_struct->fw_ver_minor);

}

int tools_open_fw_version_size(void){
	 return 8;
}

void tools_open_fw_version_dump(const struct tools_open_fw_version *ptr_struct, FILE* file) {
	tools_open_fw_version_print(ptr_struct, file, 0);
}

void tools_open_tlv_type_pack(const union tools_open_tlv_type *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_tlv_type_dw_pack(&(ptr_struct->tlv_type_dw), ptr_buff);
}

void tools_open_tlv_type_unpack(union tools_open_tlv_type *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_tlv_type_dw_unpack(&(ptr_struct->tlv_type_dw), ptr_buff);
}

void tools_open_tlv_type_print(const union tools_open_tlv_type *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_tlv_type ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "global:\n");
	tools_open_global_type_print(&(ptr_struct->global), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "eswitch:\n");
	tools_open_eswitch_type_print(&(ptr_struct->eswitch), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "per_host:\n");
	tools_open_per_host_type_print(&(ptr_struct->per_host), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "bmc:\n");
	tools_open_bmc_type_print(&(ptr_struct->bmc), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "per_port:\n");
	tools_open_per_port_type_print(&(ptr_struct->per_port), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tlv_type_dw:\n");
	tools_open_tlv_type_dw_print(&(ptr_struct->tlv_type_dw), file, indent_level + 1);

}

int tools_open_tlv_type_size(void){
	 return 4;
}

void tools_open_tlv_type_dump(const union tools_open_tlv_type *ptr_struct, FILE* file) {
	tools_open_tlv_type_print(ptr_struct, file, 0);
}

void tools_open_pmdio_addr_data_pack(const struct tools_open_pmdio_addr_data *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->addr);

}

void tools_open_pmdio_addr_data_unpack(struct tools_open_pmdio_addr_data *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->data = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=0;
	ptr_struct->addr = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void tools_open_pmdio_addr_data_print(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_pmdio_addr_data ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data                 : "UH_FMT"\n", ptr_struct->data);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "addr                 : "UH_FMT"\n", ptr_struct->addr);

}

int tools_open_pmdio_addr_data_size(void){
	 return 4;
}

void tools_open_pmdio_addr_data_dump(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file) {
	tools_open_pmdio_addr_data_print(ptr_struct, file, 0);
}

void tools_open_timestamp_pack(const struct tools_open_timestamp *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_fw_version_pack(&(ptr_struct->fw_version), ptr_buff + offset/8);

	offset=64;
	tools_open_ts_entry_pack(&(ptr_struct->ts_entry), ptr_buff + offset/8);

}

void tools_open_timestamp_unpack(struct tools_open_timestamp *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_fw_version_unpack(&(ptr_struct->fw_version), ptr_buff + offset/8);

	offset=64;
	tools_open_ts_entry_unpack(&(ptr_struct->ts_entry), ptr_buff + offset/8);

}

void tools_open_timestamp_print(const struct tools_open_timestamp *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_timestamp ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_version:\n");
	tools_open_fw_version_print(&(ptr_struct->fw_version), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ts_entry:\n");
	tools_open_ts_entry_print(&(ptr_struct->ts_entry), file, indent_level + 1);

}

int tools_open_timestamp_size(void){
	 return 16;
}

void tools_open_timestamp_dump(const struct tools_open_timestamp *ptr_struct, FILE* file) {
	tools_open_timestamp_print(ptr_struct, file, 0);
}

void tools_open_nv_hdr_fifth_gen_pack(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length);

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->shadow);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);

	offset=9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_supported);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_);

	offset=7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rd_en);

	offset=6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->over_en);

	offset=32;
	tools_open_tlv_type_pack(&(ptr_struct->type), ptr_buff + offset/8);

}

void tools_open_nv_hdr_fifth_gen_unpack(struct tools_open_nv_hdr_fifth_gen *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=20;
	ptr_struct->shadow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=16;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=9;
	ptr_struct->default_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=8;
	ptr_struct->default_ = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=7;
	ptr_struct->rd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=6;
	ptr_struct->over_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	tools_open_tlv_type_unpack(&(ptr_struct->type), ptr_buff + offset/8);

}

void tools_open_nv_hdr_fifth_gen_print(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nv_hdr_fifth_gen ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "length               : "UH_FMT"\n", ptr_struct->length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "shadow               : "UH_FMT"\n", ptr_struct->shadow);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : "UH_FMT"\n", ptr_struct->version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_supported    : "UH_FMT"\n", ptr_struct->default_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_             : "UH_FMT"\n", ptr_struct->default_);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rd_en                : "UH_FMT"\n", ptr_struct->rd_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "over_en              : "UH_FMT"\n", ptr_struct->over_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type:\n");
	tools_open_tlv_type_print(&(ptr_struct->type), file, indent_level + 1);

}

int tools_open_nv_hdr_fifth_gen_size(void){
	 return 12;
}

void tools_open_nv_hdr_fifth_gen_dump(const struct tools_open_nv_hdr_fifth_gen *ptr_struct, FILE* file) {
	tools_open_nv_hdr_fifth_gen_print(ptr_struct, file, 0);
}

void tools_open_nv_hdr_pack(const struct tools_open_nv_hdr *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->type);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->length);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_mod);

	offset=39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->shadow);

	offset=37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pad_cnt);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);

}

void tools_open_nv_hdr_unpack(struct tools_open_nv_hdr *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=2;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=40;
	ptr_struct->type_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=39;
	ptr_struct->shadow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=37;
	ptr_struct->pad_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=32;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

}

void tools_open_nv_hdr_print(const struct tools_open_nv_hdr *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nv_hdr ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type                 : "UH_FMT"\n", ptr_struct->type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "length               : "UH_FMT"\n", ptr_struct->length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type_mod             : "UH_FMT"\n", ptr_struct->type_mod);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "shadow               : "UH_FMT"\n", ptr_struct->shadow);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pad_cnt              : "UH_FMT"\n", ptr_struct->pad_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : "UH_FMT"\n", ptr_struct->version);

}

int tools_open_nv_hdr_size(void){
	 return 8;
}

void tools_open_nv_hdr_dump(const struct tools_open_nv_hdr *ptr_struct, FILE* file) {
	tools_open_nv_hdr_print(ptr_struct, file, 0);
}

void tools_open_aux_tlv_header_pack(const struct tools_open_aux_tlv_header *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->header_type);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->length);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);

	offset=96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->reserved0);

	offset=128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->reserved1);

}

void tools_open_aux_tlv_header_unpack(struct tools_open_aux_tlv_header *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=16;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=8;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->header_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->length = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=80;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=96;
	ptr_struct->reserved0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=128;
	ptr_struct->reserved1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_aux_tlv_header_print(const struct tools_open_aux_tlv_header *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_aux_tlv_header ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : "UH_FMT"\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : "UH_FMT"\n", ptr_struct->major_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type                 : "UH_FMT"\n", ptr_struct->type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "header_type          : "UH_FMT"\n", ptr_struct->header_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "length               : "U32H_FMT"\n", ptr_struct->length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "crc                  : "UH_FMT"\n", ptr_struct->crc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reserved0            : "U32H_FMT"\n", ptr_struct->reserved0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reserved1            : "U32H_FMT"\n", ptr_struct->reserved1);

}

int tools_open_aux_tlv_header_size(void){
	 return 20;
}

void tools_open_aux_tlv_header_dump(const struct tools_open_aux_tlv_header *ptr_struct, FILE* file) {
	tools_open_aux_tlv_header_print(ptr_struct, file, 0);
}

void tools_open_pmdio_pack(const struct tools_open_pmdio *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lock);

	offset=59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->reg_adr_mmd);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_op_idx);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_ops_done);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(64, 32, i, 2112, 1);
	tools_open_pmdio_addr_data_pack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset/8);
	}

}

void tools_open_pmdio_unpack(struct tools_open_pmdio *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=29;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=22;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=59;
	ptr_struct->reg_adr_mmd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset=48;
	ptr_struct->last_op_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=40;
	ptr_struct->num_ops_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(64, 32, i, 2112, 1);
	tools_open_pmdio_addr_data_unpack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset/8);
	}

}

void tools_open_pmdio_print(const struct tools_open_pmdio *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_pmdio ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "operation            : "UH_FMT"\n", ptr_struct->operation);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clause               : "UH_FMT"\n", ptr_struct->clause);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "local_port           : "UH_FMT"\n", ptr_struct->local_port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lock                 : "UH_FMT"\n", ptr_struct->lock);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reg_adr_mmd          : "UH_FMT"\n", ptr_struct->reg_adr_mmd);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "last_op_idx          : "UH_FMT"\n", ptr_struct->last_op_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_ops_done         : "UH_FMT"\n", ptr_struct->num_ops_done);

	for (i=0; i < 64; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mdio_trans_%03d:\n", i);
	tools_open_pmdio_addr_data_print(&(ptr_struct->mdio_trans[i]), file, indent_level + 1);
	}

}

int tools_open_pmdio_size(void){
	 return 264;
}

void tools_open_pmdio_dump(const struct tools_open_pmdio *ptr_struct, FILE* file) {
	tools_open_pmdio_print(ptr_struct, file, 0);
}

void tools_open_pmdic_pack(const struct tools_open_pmdic *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);

	offset=56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation_cap);

	offset=38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mdio_preset);

	offset=88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->misc_cap);

}

void tools_open_pmdic_unpack(struct tools_open_pmdic *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=56;
	ptr_struct->operation_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=38;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=32;
	ptr_struct->mdio_preset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=88;
	ptr_struct->misc_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_pmdic_print(const struct tools_open_pmdic *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_pmdic ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "local_port           : "UH_FMT"\n", ptr_struct->local_port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "operation_cap        : "UH_FMT"\n", ptr_struct->operation_cap);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clause               : "UH_FMT"\n", ptr_struct->clause);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mdio_preset          : "UH_FMT"\n", ptr_struct->mdio_preset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "misc_cap             : "UH_FMT"\n", ptr_struct->misc_cap);

}

int tools_open_pmdic_size(void){
	 return 12;
}

void tools_open_pmdic_dump(const struct tools_open_pmdic *ptr_struct, FILE* file) {
	tools_open_pmdic_print(ptr_struct, file, 0);
}

void tools_open_mvts_pack(const struct tools_open_mvts *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->check_timestamp_flag);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->running_flag);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clear_all_ts_flag);

	offset=32;
	tools_open_timestamp_pack(&(ptr_struct->timestamp), ptr_buff + offset/8);

}

void tools_open_mvts_unpack(struct tools_open_mvts *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=2;
	ptr_struct->check_timestamp_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->running_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->clear_all_ts_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	tools_open_timestamp_unpack(&(ptr_struct->timestamp), ptr_buff + offset/8);

}

void tools_open_mvts_print(const struct tools_open_mvts *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mvts ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "check_timestamp_flag : "UH_FMT"\n", ptr_struct->check_timestamp_flag);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "running_flag         : "UH_FMT"\n", ptr_struct->running_flag);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clear_all_ts_flag    : "UH_FMT"\n", ptr_struct->clear_all_ts_flag);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "timestamp:\n");
	tools_open_timestamp_print(&(ptr_struct->timestamp), file, indent_level + 1);

}

int tools_open_mvts_size(void){
	 return 20;
}

void tools_open_mvts_dump(const struct tools_open_mvts *ptr_struct, FILE* file) {
	tools_open_mvts_print(ptr_struct, file, 0);
}

void tools_open_nvqgc_pack(const struct tools_open_nvqgc *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->read_factory_settings_support);

}

void tools_open_nvqgc_unpack(struct tools_open_nvqgc *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=31;
	ptr_struct->read_factory_settings_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_nvqgc_print(const struct tools_open_nvqgc *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nvqgc ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "read_factory_settings_support : "UH_FMT"\n", ptr_struct->read_factory_settings_support);

}

int tools_open_nvqgc_size(void){
	 return 16;
}

void tools_open_nvqgc_dump(const struct tools_open_nvqgc *ptr_struct, FILE* file) {
	tools_open_nvqgc_print(ptr_struct, file, 0);
}

void tools_open_nvdi_pack(const struct tools_open_nvdi *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_nvdi_unpack(struct tools_open_nvdi *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_nvdi_print(const struct tools_open_nvdi *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nvdi ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

}

int tools_open_nvdi_size(void){
	 return 12;
}

void tools_open_nvdi_dump(const struct tools_open_nvdi *ptr_struct, FILE* file) {
	tools_open_nvdi_print(ptr_struct, file, 0);
}

void tools_open_nvda_pack(const struct tools_open_nvda *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(120, 8, i, 2048, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}

}

void tools_open_nvda_unpack(struct tools_open_nvda *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(120, 8, i, 2048, 1);
	ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_nvda_print(const struct tools_open_nvda *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nvda ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

	for (i=0; i < 128; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data_%03d            : "UH_FMT"\n", i, ptr_struct->data[i]);
	}

}

int tools_open_nvda_size(void){
	 return 256;
}

void tools_open_nvda_dump(const struct tools_open_nvda *ptr_struct, FILE* file) {
	tools_open_nvda_print(ptr_struct, file, 0);
}

void tools_open_nvia_pack(const struct tools_open_nvia *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	offset=125;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->target);

}

void tools_open_nvia_unpack(struct tools_open_nvia *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_fifth_gen_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	offset=125;
	ptr_struct->target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

}

void tools_open_nvia_print(const struct tools_open_nvia *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nvia ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_fifth_gen_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "target               : "UH_FMT"\n", ptr_struct->target);

}

int tools_open_nvia_size(void){
	 return 20;
}

void tools_open_nvia_dump(const struct tools_open_nvia *ptr_struct, FILE* file) {
	tools_open_nvia_print(ptr_struct, file, 0);
}

void tools_open_nvqc_pack(const struct tools_open_nvqc *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_tlv_type_pack(&(ptr_struct->type), ptr_buff + offset/8);

	offset=63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_rd);

	offset=62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->support_wr);

	offset=56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);

}

void tools_open_nvqc_unpack(struct tools_open_nvqc *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_tlv_type_unpack(&(ptr_struct->type), ptr_buff + offset/8);

	offset=63;
	ptr_struct->support_rd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=62;
	ptr_struct->support_wr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=56;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

}

void tools_open_nvqc_print(const struct tools_open_nvqc *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nvqc ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type:\n");
	tools_open_tlv_type_print(&(ptr_struct->type), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "support_rd           : "UH_FMT"\n", ptr_struct->support_rd);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "support_wr           : "UH_FMT"\n", ptr_struct->support_wr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : "UH_FMT"\n", ptr_struct->version);

}

int tools_open_nvqc_size(void){
	 return 8;
}

void tools_open_nvqc_dump(const struct tools_open_nvqc *ptr_struct, FILE* file) {
	tools_open_nvqc_print(ptr_struct, file, 0);
}

void tools_open_mnvia_pack(const struct tools_open_mnvia *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvia_unpack(struct tools_open_mnvia *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvia_print(const struct tools_open_mnvia *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mnvia ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

}

int tools_open_mnvia_size(void){
	 return 8;
}

void tools_open_mnvia_dump(const struct tools_open_mnvia *ptr_struct, FILE* file) {
	tools_open_mnvia_print(ptr_struct, file, 0);
}

void tools_open_mnvi_pack(const struct tools_open_mnvi *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvi_unpack(struct tools_open_mnvi *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvi_print(const struct tools_open_mnvi *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mnvi ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

}

int tools_open_mnvi_size(void){
	 return 8;
}

void tools_open_mnvi_dump(const struct tools_open_mnvi *ptr_struct, FILE* file) {
	tools_open_mnvi_print(ptr_struct, file, 0);
}

void tools_open_mnva_pack(const struct tools_open_mnva *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_pack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}

}

void tools_open_mnva_unpack(struct tools_open_mnva *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_nv_hdr_unpack(&(ptr_struct->nv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
	ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_mnva_print(const struct tools_open_mnva *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mnva ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_hdr:\n");
	tools_open_nv_hdr_print(&(ptr_struct->nv_hdr), file, indent_level + 1);

	for (i=0; i < 128; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data_%03d            : "UH_FMT"\n", i, ptr_struct->data[i]);
	}

}

int tools_open_mnva_size(void){
	 return 256;
}

void tools_open_mnva_dump(const struct tools_open_mnva *ptr_struct, FILE* file) {
	tools_open_mnva_print(ptr_struct, file, 0);
}

void tools_open_mfg_info_pack(const struct tools_open_mfg_info *ptr_struct, u_int8_t* ptr_buff){
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

	offset=232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset=224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);

	for (i=0; i < 96; i++) {
	offset=adb2c_calc_array_field_address(792, 8, i, 2560, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->orig_prs_name[i]);
	}

}

void tools_open_mfg_info_unpack(struct tools_open_mfg_info *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(24, 8, i, 2560, 1);
	ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->psid[16] = '\0';
	offset=232;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=224;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	for (i=0; i < 96; i++) {
	offset=adb2c_calc_array_field_address(792, 8, i, 2560, 1);
	ptr_struct->orig_prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->orig_prs_name[96] = '\0';
}

void tools_open_mfg_info_print(const struct tools_open_mfg_info *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mfg_info ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	fprintf(file, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : "UH_FMT"\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : "UH_FMT"\n", ptr_struct->major_version);

	fprintf(file, "orig_prs_name        : \"%s\"\n", ptr_struct->orig_prs_name);
}

int tools_open_mfg_info_size(void){
	 return 320;
}

void tools_open_mfg_info_dump(const struct tools_open_mfg_info *ptr_struct, FILE* file) {
	tools_open_mfg_info_print(ptr_struct, file, 0);
}

void tools_open_image_info_pack(const struct tools_open_image_info *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(312, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}

	for (i=0; i < 256; i++) {
	offset=adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->description[i]);
	}

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->name[i]);
	}

	for (i=0; i < 96; i++) {
	offset=adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prs_name[i]);
	}

}

void tools_open_image_info_unpack(struct tools_open_image_info *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(312, 8, i, 8192, 1);
	ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->psid[16] = '\0';
	for (i=0; i < 256; i++) {
	offset=adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
	ptr_struct->description[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->description[256] = '\0';
	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
	ptr_struct->name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->name[64] = '\0';
	for (i=0; i < 96; i++) {
	offset=adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
	ptr_struct->prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->prs_name[96] = '\0';
}

void tools_open_image_info_print(const struct tools_open_image_info *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_image_info ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : "UH_FMT"\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : "UH_FMT"\n", ptr_struct->major_version);

	fprintf(file, "psid                 : \"%s\"\n", ptr_struct->psid);
	fprintf(file, "description          : \"%s\"\n", ptr_struct->description);
	fprintf(file, "name                 : \"%s\"\n", ptr_struct->name);
	fprintf(file, "prs_name             : \"%s\"\n", ptr_struct->prs_name);
}

int tools_open_image_info_size(void){
	 return 1024;
}

void tools_open_image_info_dump(const struct tools_open_image_info *ptr_struct, FILE* file) {
	tools_open_image_info_print(ptr_struct, file, 0);
}

void tools_open_aux_tlv_pack(const struct tools_open_aux_tlv *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_aux_tlv_header_pack(&(ptr_struct->aux_tlv_header), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(184, 8, i, 2048, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}

}

void tools_open_aux_tlv_unpack(struct tools_open_aux_tlv *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_aux_tlv_header_unpack(&(ptr_struct->aux_tlv_header), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(184, 8, i, 2048, 1);
	ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_aux_tlv_print(const struct tools_open_aux_tlv *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_aux_tlv ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "aux_tlv_header:\n");
	tools_open_aux_tlv_header_print(&(ptr_struct->aux_tlv_header), file, indent_level + 1);

	for (i=0; i < 128; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data_%03d            : "UH_FMT"\n", i, ptr_struct->data[i]);
	}

}

int tools_open_aux_tlv_size(void){
	 return 256;
}

void tools_open_aux_tlv_dump(const struct tools_open_aux_tlv *ptr_struct, FILE* file) {
	tools_open_aux_tlv_print(ptr_struct, file, 0);
}

void tools_open_aux_data_hdr_pack(const struct tools_open_aux_data_hdr *ptr_struct, u_int8_t* ptr_buff){
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

}

void tools_open_aux_data_hdr_unpack(struct tools_open_aux_data_hdr *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
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

}

void tools_open_aux_data_hdr_print(const struct tools_open_aux_data_hdr *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_aux_data_hdr ========\n");
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

}

int tools_open_aux_data_hdr_size(void){
	 return 16;
}

void tools_open_aux_data_hdr_dump(const struct tools_open_aux_data_hdr *ptr_struct, FILE* file) {
	tools_open_aux_data_hdr_print(ptr_struct, file, 0);
}

void tools_open_query_def_params_per_port_pack(const struct tools_open_query_def_params_per_port *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_vpi);

	offset=12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_wol);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->default_boot_vlan);

	offset=44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->default_boot_protocol);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->default_boot_retry_cnt);

	offset=37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_network_link_type);

	offset=36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_en_wol_magic);

	offset=35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_boot_vlan_en);

	offset=34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_boot_option_rom_en);

	offset=33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_pprx);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->default_pptx);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->default_boot_pkey);

	offset=70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->boot_ip_ver);

	offset=68;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_infiniband_dhcp_settings);

	offset=67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_infiniband_boot_settings);

	offset=66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_dhcp_iscsi_parameters);

	offset=65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_iscsi_parameters);

	offset=64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->nv_config_boot_parameters);

	offset=108;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->client_indentifier);

	offset=106;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mac_admin_bit);

	offset=104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->iscsi_boot_to_target);

	offset=101;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_vlan_en);

	offset=100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_tcp_timestamps_en);

	offset=99;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_mutual_auth_en);

	offset=98;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_auth_en);

	offset=97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_dhcp_params_en);

	offset=96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_ipv4_dhcp_en);

	offset=152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_lun_busy_retry_cnt);

	offset=144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_link_up_delay_time);

}

void tools_open_query_def_params_per_port_unpack(struct tools_open_query_def_params_per_port *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=13;
	ptr_struct->nv_config_vpi = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=12;
	ptr_struct->nv_config_wol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=52;
	ptr_struct->default_boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=44;
	ptr_struct->default_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=40;
	ptr_struct->default_boot_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=37;
	ptr_struct->default_network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=36;
	ptr_struct->default_en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=35;
	ptr_struct->default_boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=34;
	ptr_struct->default_boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=33;
	ptr_struct->default_pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->default_pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=80;
	ptr_struct->default_boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=70;
	ptr_struct->boot_ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=68;
	ptr_struct->nv_config_infiniband_dhcp_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=67;
	ptr_struct->nv_config_infiniband_boot_settings = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=66;
	ptr_struct->nv_config_dhcp_iscsi_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=65;
	ptr_struct->nv_config_iscsi_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=64;
	ptr_struct->nv_config_boot_parameters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=108;
	ptr_struct->client_indentifier = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=106;
	ptr_struct->mac_admin_bit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=104;
	ptr_struct->iscsi_boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=101;
	ptr_struct->iscsi_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=100;
	ptr_struct->iscsi_tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=99;
	ptr_struct->iscsi_chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=98;
	ptr_struct->iscsi_chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=97;
	ptr_struct->iscsi_dhcp_params_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=96;
	ptr_struct->iscsi_ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=152;
	ptr_struct->iscsi_lun_busy_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=144;
	ptr_struct->iscsi_link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_query_def_params_per_port_print(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_query_def_params_per_port ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_vpi        : "UH_FMT"\n", ptr_struct->nv_config_vpi);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_wol        : "UH_FMT"\n", ptr_struct->nv_config_wol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_default_config_payload_version : "UH_FMT"\n", ptr_struct->fw_default_config_payload_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_vlan    : "UH_FMT"\n", ptr_struct->default_boot_vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_protocol : "UH_FMT"\n", ptr_struct->default_boot_protocol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_retry_cnt : "UH_FMT"\n", ptr_struct->default_boot_retry_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_network_link_type : "UH_FMT"\n", ptr_struct->default_network_link_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_en_wol_magic : "UH_FMT"\n", ptr_struct->default_en_wol_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_vlan_en : "UH_FMT"\n", ptr_struct->default_boot_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_option_rom_en : "UH_FMT"\n", ptr_struct->default_boot_option_rom_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_pprx         : "UH_FMT"\n", ptr_struct->default_pprx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_pptx         : "UH_FMT"\n", ptr_struct->default_pptx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_boot_pkey    : "UH_FMT"\n", ptr_struct->default_boot_pkey);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_ip_ver          : "UH_FMT"\n", ptr_struct->boot_ip_ver);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_infiniband_dhcp_settings : "UH_FMT"\n", ptr_struct->nv_config_infiniband_dhcp_settings);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_infiniband_boot_settings : "UH_FMT"\n", ptr_struct->nv_config_infiniband_boot_settings);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_dhcp_iscsi_parameters : "UH_FMT"\n", ptr_struct->nv_config_dhcp_iscsi_parameters);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_iscsi_parameters : "UH_FMT"\n", ptr_struct->nv_config_iscsi_parameters);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nv_config_boot_parameters : "UH_FMT"\n", ptr_struct->nv_config_boot_parameters);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "client_indentifier   : "UH_FMT"\n", ptr_struct->client_indentifier);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mac_admin_bit        : "UH_FMT"\n", ptr_struct->mac_admin_bit);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_boot_to_target : "UH_FMT"\n", ptr_struct->iscsi_boot_to_target);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_vlan_en        : "UH_FMT"\n", ptr_struct->iscsi_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_tcp_timestamps_en : "UH_FMT"\n", ptr_struct->iscsi_tcp_timestamps_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_chap_mutual_auth_en : "UH_FMT"\n", ptr_struct->iscsi_chap_mutual_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_chap_auth_en   : "UH_FMT"\n", ptr_struct->iscsi_chap_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_dhcp_params_en : "UH_FMT"\n", ptr_struct->iscsi_dhcp_params_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_ipv4_dhcp_en   : "UH_FMT"\n", ptr_struct->iscsi_ipv4_dhcp_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_lun_busy_retry_cnt : "UH_FMT"\n", ptr_struct->iscsi_lun_busy_retry_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_link_up_delay_time : "UH_FMT"\n", ptr_struct->iscsi_link_up_delay_time);

}

int tools_open_query_def_params_per_port_size(void){
	 return 28;
}

void tools_open_query_def_params_per_port_dump(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file) {
	tools_open_query_def_params_per_port_print(ptr_struct, file, 0);
}

void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);

	offset=56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_vfs);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uar_bar_size);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_uar_bar_size);

	offset=42;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_ip_ver);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);

}

void tools_open_query_def_params_global_unpack(struct tools_open_query_def_params_global *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=56;
	ptr_struct->num_vfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=52;
	ptr_struct->uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=48;
	ptr_struct->max_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=42;
	ptr_struct->boot_ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_query_def_params_global_print(const struct tools_open_query_def_params_global *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_query_def_params_global ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_default_config_payload_version : "UH_FMT"\n", ptr_struct->fw_default_config_payload_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_vfs              : "UH_FMT"\n", ptr_struct->num_vfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uar_bar_size         : "UH_FMT"\n", ptr_struct->uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_uar_bar_size     : "UH_FMT"\n", ptr_struct->max_uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_ip_ver          : "UH_FMT"\n", ptr_struct->boot_ip_ver);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

}

int tools_open_query_def_params_global_size(void){
	 return 20;
}

void tools_open_query_def_params_global_dump(const struct tools_open_query_def_params_global *ptr_struct, FILE* file) {
	tools_open_query_def_params_global_print(ptr_struct, file, 0);
}

void tools_open_phy_reg_pack(const union tools_open_phy_reg *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_pmdio_pack(&(ptr_struct->pmdio), ptr_buff);
}

void tools_open_phy_reg_unpack(union tools_open_phy_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_pmdio_unpack(&(ptr_struct->pmdio), ptr_buff);
}

void tools_open_phy_reg_print(const union tools_open_phy_reg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_phy_reg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pmdic:\n");
	tools_open_pmdic_print(&(ptr_struct->pmdic), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pmdio:\n");
	tools_open_pmdio_print(&(ptr_struct->pmdio), file, indent_level + 1);

}

int tools_open_phy_reg_size(void){
	 return 264;
}

void tools_open_phy_reg_dump(const union tools_open_phy_reg *ptr_struct, FILE* file) {
	tools_open_phy_reg_print(ptr_struct, file, 0);
}

void tools_open_mnv_cfg_pack(const union tools_open_mnv_cfg *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_mvts_pack(&(ptr_struct->mvts), ptr_buff);
}

void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_mvts_unpack(&(ptr_struct->mvts), ptr_buff);
}

void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_mnv_cfg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnva:\n");
	tools_open_mnva_print(&(ptr_struct->mnva), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnvi:\n");
	tools_open_mnvi_print(&(ptr_struct->mnvi), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnvia:\n");
	tools_open_mnvia_print(&(ptr_struct->mnvia), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nvqc:\n");
	tools_open_nvqc_print(&(ptr_struct->nvqc), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nvia:\n");
	tools_open_nvia_print(&(ptr_struct->nvia), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nvda:\n");
	tools_open_nvda_print(&(ptr_struct->nvda), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nvdi:\n");
	tools_open_nvdi_print(&(ptr_struct->nvdi), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "nvqgc:\n");
	tools_open_nvqgc_print(&(ptr_struct->nvqgc), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mvts:\n");
	tools_open_mvts_print(&(ptr_struct->mvts), file, indent_level + 1);

}

int tools_open_mnv_cfg_size(void){
	 return 256;
}

void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE* file) {
	tools_open_mnv_cfg_print(ptr_struct, file, 0);
}

void tools_open_option_rom_capability_pack(const struct tools_open_option_rom_capability *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ip_ver);

}

void tools_open_option_rom_capability_unpack(struct tools_open_option_rom_capability *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_option_rom_capability_print(const struct tools_open_option_rom_capability *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_option_rom_capability ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ip_ver               : "UH_FMT"\n", ptr_struct->ip_ver);

}

int tools_open_option_rom_capability_size(void){
	 return 4;
}

void tools_open_option_rom_capability_dump(const struct tools_open_option_rom_capability *ptr_struct, FILE* file) {
	tools_open_option_rom_capability_print(ptr_struct, file, 0);
}

void tools_open_boot_settings_ext_pack(const struct tools_open_boot_settings_ext *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ip_ver);

}

void tools_open_boot_settings_ext_unpack(struct tools_open_boot_settings_ext *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	ptr_struct->ip_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

}

void tools_open_boot_settings_ext_print(const struct tools_open_boot_settings_ext *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_boot_settings_ext ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ip_ver               : "UH_FMT"\n", ptr_struct->ip_ver);

}

int tools_open_boot_settings_ext_size(void){
	 return 4;
}

void tools_open_boot_settings_ext_dump(const struct tools_open_boot_settings_ext *ptr_struct, FILE* file) {
	tools_open_boot_settings_ext_print(ptr_struct, file, 0);
}

void tools_open_external_port_pack(const struct tools_open_external_port *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->port_owner);

	offset=30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->allow_rd_counters);

}

void tools_open_external_port_unpack(struct tools_open_external_port *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=31;
	ptr_struct->port_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=30;
	ptr_struct->allow_rd_counters = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_external_port_print(const struct tools_open_external_port *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_external_port ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "port_owner           : "UH_FMT"\n", ptr_struct->port_owner);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "allow_rd_counters    : "UH_FMT"\n", ptr_struct->allow_rd_counters);

}

int tools_open_external_port_size(void){
	 return 8;
}

void tools_open_external_port_dump(const struct tools_open_external_port *ptr_struct, FILE* file) {
	tools_open_external_port_print(ptr_struct, file, 0);
}

void tools_open_lldp_nb_capability_pack(const struct tools_open_lldp_nb_capability *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_supported);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_total_lldp_tlv_len);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 192, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->supported_lldp_tx_tlv_mask[i]);
	}

}

void tools_open_lldp_nb_capability_unpack(struct tools_open_lldp_nb_capability *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->lldp_nb_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=48;
	ptr_struct->max_total_lldp_tlv_len = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 192, 1);
	ptr_struct->supported_lldp_tx_tlv_mask[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_lldp_nb_capability_print(const struct tools_open_lldp_nb_capability *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_lldp_nb_capability ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_nb_supported    : "UH_FMT"\n", ptr_struct->lldp_nb_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_total_lldp_tlv_len : "UH_FMT"\n", ptr_struct->max_total_lldp_tlv_len);

	for (i=0; i < 16; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "supported_lldp_tx_tlv_mask_%03d : "UH_FMT"\n", i, ptr_struct->supported_lldp_tx_tlv_mask[i]);
	}

}

int tools_open_lldp_nb_capability_size(void){
	 return 24;
}

void tools_open_lldp_nb_capability_dump(const struct tools_open_lldp_nb_capability *ptr_struct, FILE* file) {
	tools_open_lldp_nb_capability_print(ptr_struct, file, 0);
}

void tools_open_lldp_nb_pack(const struct tools_open_lldp_nb *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_rx_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lldp_nb_tx_en);

	offset=84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->lldp_msg_tx_interval);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(120, 8, i, 224, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lldp_tx_tlv_mask[i]);
	}

}

void tools_open_lldp_nb_unpack(struct tools_open_lldp_nb *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=1;
	ptr_struct->lldp_nb_rx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->lldp_nb_tx_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=84;
	ptr_struct->lldp_msg_tx_interval = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	for (i=0; i < 16; i++) {
	offset=adb2c_calc_array_field_address(120, 8, i, 224, 1);
	ptr_struct->lldp_tx_tlv_mask[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_lldp_nb_print(const struct tools_open_lldp_nb *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_lldp_nb ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_nb_rx_en        : "UH_FMT"\n", ptr_struct->lldp_nb_rx_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_nb_tx_en        : "UH_FMT"\n", ptr_struct->lldp_nb_tx_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_msg_tx_interval : "UH_FMT"\n", ptr_struct->lldp_msg_tx_interval);

	for (i=0; i < 16; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_tx_tlv_mask_%03d : "UH_FMT"\n", i, ptr_struct->lldp_tx_tlv_mask[i]);
	}

}

int tools_open_lldp_nb_size(void){
	 return 28;
}

void tools_open_lldp_nb_dump(const struct tools_open_lldp_nb *ptr_struct, FILE* file) {
	tools_open_lldp_nb_print(ptr_struct, file, 0);
}

void tools_open_roce_cc_ecn_pack(const struct tools_open_roce_cc_ecn *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clamp_tgt_rate_after_time_inc);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clamp_tgt_rate);

	offset=47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_time_reset);

	offset=81;
	adb2c_push_bits_to_buff(ptr_buff, offset, 15, (u_int32_t)ptr_struct->rpg_byte_reset);

	offset=123;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->rpg_threshold);

	offset=129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 31, (u_int32_t)ptr_struct->rpg_max_rate);

	offset=175;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_ai_rate);

	offset=207;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_hai_rate);

	offset=252;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rpg_gd);

	offset=280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rpg_min_dec_fac);

	offset=303;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rpg_min_rate);

	offset=335;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rate_to_set_on_first_cnp);

	offset=374;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->dce_tcp_g);

	offset=399;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->dce_tcp_rtt);

	offset=431;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->rate_reduce_monitor_period);

	offset=470;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->initial_alpha_value);

	offset=495;
	adb2c_push_bits_to_buff(ptr_buff, offset, 17, (u_int32_t)ptr_struct->min_time_between_cnps);

	offset=541;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->cnp_dscp);

	offset=530;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->cnp_802p_prio);

}

void tools_open_roce_cc_ecn_unpack(struct tools_open_roce_cc_ecn *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=1;
	ptr_struct->clamp_tgt_rate_after_time_inc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->clamp_tgt_rate = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=47;
	ptr_struct->rpg_time_reset = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=81;
	ptr_struct->rpg_byte_reset = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 15);

	offset=123;
	ptr_struct->rpg_threshold = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset=129;
	ptr_struct->rpg_max_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 31);

	offset=175;
	ptr_struct->rpg_ai_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=207;
	ptr_struct->rpg_hai_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=252;
	ptr_struct->rpg_gd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=280;
	ptr_struct->rpg_min_dec_fac = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=303;
	ptr_struct->rpg_min_rate = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=335;
	ptr_struct->rate_to_set_on_first_cnp = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=374;
	ptr_struct->dce_tcp_g = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=399;
	ptr_struct->dce_tcp_rtt = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=431;
	ptr_struct->rate_reduce_monitor_period = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=470;
	ptr_struct->initial_alpha_value = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=495;
	ptr_struct->min_time_between_cnps = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 17);

	offset=541;
	ptr_struct->cnp_dscp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=530;
	ptr_struct->cnp_802p_prio = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

}

void tools_open_roce_cc_ecn_print(const struct tools_open_roce_cc_ecn *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_roce_cc_ecn ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clamp_tgt_rate_after_time_inc : "UH_FMT"\n", ptr_struct->clamp_tgt_rate_after_time_inc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clamp_tgt_rate       : "UH_FMT"\n", ptr_struct->clamp_tgt_rate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_time_reset       : "UH_FMT"\n", ptr_struct->rpg_time_reset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_byte_reset       : "UH_FMT"\n", ptr_struct->rpg_byte_reset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_threshold        : "UH_FMT"\n", ptr_struct->rpg_threshold);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_max_rate         : "UH_FMT"\n", ptr_struct->rpg_max_rate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_ai_rate          : "UH_FMT"\n", ptr_struct->rpg_ai_rate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_hai_rate         : "UH_FMT"\n", ptr_struct->rpg_hai_rate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_gd               : "UH_FMT"\n", ptr_struct->rpg_gd);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_min_dec_fac      : "UH_FMT"\n", ptr_struct->rpg_min_dec_fac);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rpg_min_rate         : "UH_FMT"\n", ptr_struct->rpg_min_rate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rate_to_set_on_first_cnp : "UH_FMT"\n", ptr_struct->rate_to_set_on_first_cnp);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dce_tcp_g            : "UH_FMT"\n", ptr_struct->dce_tcp_g);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dce_tcp_rtt          : "UH_FMT"\n", ptr_struct->dce_tcp_rtt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rate_reduce_monitor_period : "UH_FMT"\n", ptr_struct->rate_reduce_monitor_period);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "initial_alpha_value  : "UH_FMT"\n", ptr_struct->initial_alpha_value);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "min_time_between_cnps : "UH_FMT"\n", ptr_struct->min_time_between_cnps);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "cnp_dscp             : "UH_FMT"\n", ptr_struct->cnp_dscp);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "cnp_802p_prio        : "UH_FMT"\n", ptr_struct->cnp_802p_prio);

}

int tools_open_roce_cc_ecn_size(void){
	 return 68;
}

void tools_open_roce_cc_ecn_dump(const struct tools_open_roce_cc_ecn *ptr_struct, FILE* file) {
	tools_open_roce_cc_ecn_print(ptr_struct, file, 0);
}

void tools_open_roce_cc_pack(const struct tools_open_roce_cc *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->roce_cc_enable_priority);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->roce_cc_algorithm);

}

void tools_open_roce_cc_unpack(struct tools_open_roce_cc *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->roce_cc_enable_priority = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->roce_cc_algorithm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_roce_cc_print(const struct tools_open_roce_cc *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_roce_cc ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_cc_enable_priority : "UH_FMT"\n", ptr_struct->roce_cc_enable_priority);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_cc_algorithm    : "UH_FMT"\n", ptr_struct->roce_cc_algorithm);

}

int tools_open_roce_cc_size(void){
	 return 4;
}

void tools_open_roce_cc_dump(const struct tools_open_roce_cc *ptr_struct, FILE* file) {
	tools_open_roce_cc_print(ptr_struct, file, 0);
}

void tools_open_roce_v_1_5_next_protocol_pack(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->roce_over_ip_next_protocol);

}

void tools_open_roce_v_1_5_next_protocol_unpack(struct tools_open_roce_v_1_5_next_protocol *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->roce_over_ip_next_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_roce_v_1_5_next_protocol_print(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_roce_v_1_5_next_protocol ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_over_ip_next_protocol : "UH_FMT"\n", ptr_struct->roce_over_ip_next_protocol);

}

int tools_open_roce_v_1_5_next_protocol_size(void){
	 return 4;
}

void tools_open_roce_v_1_5_next_protocol_dump(const struct tools_open_roce_v_1_5_next_protocol *ptr_struct, FILE* file) {
	tools_open_roce_v_1_5_next_protocol_print(ptr_struct, file, 0);
}

void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->network_link_type);

	offset=28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->default_link_type);

}

void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=30;
	ptr_struct->network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=28;
	ptr_struct->default_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

}

void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_vpi_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "network_link_type    : "UH_FMT"\n", ptr_struct->network_link_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "default_link_type    : "UH_FMT"\n", ptr_struct->default_link_type);

}

int tools_open_vpi_settings_size(void){
	 return 4;
}

void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE* file) {
	tools_open_vpi_settings_print(ptr_struct, file, 0);
}

void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->log_uar_bar_size);

}

void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->log_uar_bar_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_bar_size ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_uar_bar_size     : "U32H_FMT"\n", ptr_struct->log_uar_bar_size);

}

int tools_open_bar_size_size(void){
	 return 4;
}

void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE* file) {
	tools_open_bar_size_print(ptr_struct, file, 0);
}

void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);

}

void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=0;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_sriov ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "total_vfs            : "UH_FMT"\n", ptr_struct->total_vfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

}

int tools_open_sriov_size(void){
	 return 4;
}

void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE* file) {
	tools_open_sriov_print(ptr_struct, file, 0);
}

void tools_open_preboot_flow_ctrl_pack(const struct tools_open_preboot_flow_ctrl *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfcrx);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfctx);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pfc_willing);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pprx);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pptx);

}

void tools_open_preboot_flow_ctrl_unpack(struct tools_open_preboot_flow_ctrl *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->pfcrx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=16;
	ptr_struct->pfctx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=2;
	ptr_struct->pfc_willing = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_preboot_flow_ctrl_print(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_preboot_flow_ctrl ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfcrx                : "UH_FMT"\n", ptr_struct->pfcrx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfctx                : "UH_FMT"\n", ptr_struct->pfctx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfc_willing          : "UH_FMT"\n", ptr_struct->pfc_willing);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pprx                 : "UH_FMT"\n", ptr_struct->pprx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pptx                 : "UH_FMT"\n", ptr_struct->pptx);

}

int tools_open_preboot_flow_ctrl_size(void){
	 return 4;
}

void tools_open_preboot_flow_ctrl_dump(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE* file) {
	tools_open_preboot_flow_ctrl_print(ptr_struct, file, 0);
}

void tools_open_preboot_boot_settings_pack(const struct tools_open_preboot_boot_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->legacy_boot_protocol);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->boot_retry_count);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);

}

void tools_open_preboot_boot_settings_unpack(struct tools_open_preboot_boot_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=8;
	ptr_struct->legacy_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=5;
	ptr_struct->boot_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=1;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_preboot_boot_settings_print(const struct tools_open_preboot_boot_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_preboot_boot_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan            : "UH_FMT"\n", ptr_struct->boot_vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "legacy_boot_protocol : "UH_FMT"\n", ptr_struct->legacy_boot_protocol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_retry_count     : "UH_FMT"\n", ptr_struct->boot_retry_count);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan_en         : "UH_FMT"\n", ptr_struct->boot_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_option_rom_en   : "UH_FMT"\n", ptr_struct->boot_option_rom_en);

}

int tools_open_preboot_boot_settings_size(void){
	 return 4;
}

void tools_open_preboot_boot_settings_dump(const struct tools_open_preboot_boot_settings *ptr_struct, FILE* file) {
	tools_open_preboot_boot_settings_print(ptr_struct, file, 0);
}

void tools_open_boot_settings_pack(const struct tools_open_boot_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->legacy_boot_protocol);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->boot_retry_conut);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);

}

void tools_open_boot_settings_unpack(struct tools_open_boot_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=8;
	ptr_struct->legacy_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=5;
	ptr_struct->boot_retry_conut = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=1;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_boot_settings_print(const struct tools_open_boot_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_boot_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan            : "UH_FMT"\n", ptr_struct->boot_vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "legacy_boot_protocol : "UH_FMT"\n", ptr_struct->legacy_boot_protocol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_retry_conut     : "UH_FMT"\n", ptr_struct->boot_retry_conut);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan_en         : "UH_FMT"\n", ptr_struct->boot_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_option_rom_en   : "UH_FMT"\n", ptr_struct->boot_option_rom_en);

}

int tools_open_boot_settings_size(void){
	 return 4;
}

void tools_open_boot_settings_dump(const struct tools_open_boot_settings *ptr_struct, FILE* file) {
	tools_open_boot_settings_print(ptr_struct, file, 0);
}

void tools_open_infiniband_boot_settings_pack(const struct tools_open_infiniband_boot_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->boot_pkey);

}

void tools_open_infiniband_boot_settings_unpack(struct tools_open_infiniband_boot_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void tools_open_infiniband_boot_settings_print(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_infiniband_boot_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_pkey            : "UH_FMT"\n", ptr_struct->boot_pkey);

}

int tools_open_infiniband_boot_settings_size(void){
	 return 4;
}

void tools_open_infiniband_boot_settings_dump(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE* file) {
	tools_open_infiniband_boot_settings_print(ptr_struct, file, 0);
}

void tools_open_iscsi_settings_pack(const struct tools_open_iscsi_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->target_as_first_hdd_en);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->boot_to_target);

	offset=7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv6_auto_config_en);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vlan_en);

	offset=4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tcp_timestamps_en);

	offset=3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_mutual_auth_en);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_auth_en);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dhcp_iscsi_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv4_dhcp_en);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->vlan);

	offset=88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lun_busy_retry_count);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_up_delay_time);

}

void tools_open_iscsi_settings_unpack(struct tools_open_iscsi_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=10;
	ptr_struct->target_as_first_hdd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=8;
	ptr_struct->boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=7;
	ptr_struct->ipv6_auto_config_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=5;
	ptr_struct->vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=4;
	ptr_struct->tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=3;
	ptr_struct->chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=2;
	ptr_struct->chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->dhcp_iscsi_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=52;
	ptr_struct->vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=88;
	ptr_struct->lun_busy_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=80;
	ptr_struct->link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_iscsi_settings_print(const struct tools_open_iscsi_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_iscsi_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "target_as_first_hdd_en : "UH_FMT"\n", ptr_struct->target_as_first_hdd_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_to_target       : "UH_FMT"\n", ptr_struct->boot_to_target);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ipv6_auto_config_en  : "UH_FMT"\n", ptr_struct->ipv6_auto_config_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vlan_en              : "UH_FMT"\n", ptr_struct->vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tcp_timestamps_en    : "UH_FMT"\n", ptr_struct->tcp_timestamps_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "chap_mutual_auth_en  : "UH_FMT"\n", ptr_struct->chap_mutual_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "chap_auth_en         : "UH_FMT"\n", ptr_struct->chap_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dhcp_iscsi_en        : "UH_FMT"\n", ptr_struct->dhcp_iscsi_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ipv4_dhcp_en         : "UH_FMT"\n", ptr_struct->ipv4_dhcp_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vlan                 : "UH_FMT"\n", ptr_struct->vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lun_busy_retry_count : "UH_FMT"\n", ptr_struct->lun_busy_retry_count);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "link_up_delay_time   : "UH_FMT"\n", ptr_struct->link_up_delay_time);

}

int tools_open_iscsi_settings_size(void){
	 return 12;
}

void tools_open_iscsi_settings_dump(const struct tools_open_iscsi_settings *ptr_struct, FILE* file) {
	tools_open_iscsi_settings_print(ptr_struct, file, 0);
}

void tools_open_port_boot_state_pack(const struct tools_open_port_boot_state *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->aux_power_indication_gpio);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->aux_power_indication_gpio_en);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->standby_on_aux);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->power_up_on_aux);

}

void tools_open_port_boot_state_unpack(struct tools_open_port_boot_state *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->aux_power_indication_gpio = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=2;
	ptr_struct->aux_power_indication_gpio_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->standby_on_aux = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->power_up_on_aux = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_port_boot_state_print(const struct tools_open_port_boot_state *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_port_boot_state ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "aux_power_indication_gpio : "UH_FMT"\n", ptr_struct->aux_power_indication_gpio);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "aux_power_indication_gpio_en : "UH_FMT"\n", ptr_struct->aux_power_indication_gpio_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "standby_on_aux       : "UH_FMT"\n", ptr_struct->standby_on_aux);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "power_up_on_aux      : "UH_FMT"\n", ptr_struct->power_up_on_aux);

}

int tools_open_port_boot_state_size(void){
	 return 4;
}

void tools_open_port_boot_state_dump(const struct tools_open_port_boot_state *ptr_struct, FILE* file) {
	tools_open_port_boot_state_print(ptr_struct, file, 0);
}

void tools_open_pci_configuration_pack(const struct tools_open_pci_configuration *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pf_bar_size_valid);

	offset=6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_bar_size_valid);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_msix_valid);

	offset=4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_vfs_msix_valid);

	offset=3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_valid);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_valid);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->full_vf_qos_valid);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_valid);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);

	offset=44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_pfs);

	offset=34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_en);

	offset=33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->full_vf_qos);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);

	offset=90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_pf_uar_bar_size);

	offset=84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_vf_uar_bar_size);

	offset=74;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->num_pf_msix);

	offset=64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->num_vf_msix);

}

void tools_open_pci_configuration_unpack(struct tools_open_pci_configuration *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=7;
	ptr_struct->pf_bar_size_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=6;
	ptr_struct->vf_bar_size_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=5;
	ptr_struct->num_pfs_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=4;
	ptr_struct->num_vfs_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=3;
	ptr_struct->num_pfs_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=2;
	ptr_struct->fpp_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->full_vf_qos_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->sriov_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=48;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=44;
	ptr_struct->num_pfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=34;
	ptr_struct->fpp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=33;
	ptr_struct->full_vf_qos = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=90;
	ptr_struct->log_pf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=84;
	ptr_struct->log_vf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=74;
	ptr_struct->num_pf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=64;
	ptr_struct->num_vf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

}

void tools_open_pci_configuration_print(const struct tools_open_pci_configuration *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_pci_configuration ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pf_bar_size_valid    : "UH_FMT"\n", ptr_struct->pf_bar_size_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vf_bar_size_valid    : "UH_FMT"\n", ptr_struct->vf_bar_size_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pfs_msix_valid   : "UH_FMT"\n", ptr_struct->num_pfs_msix_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_vfs_msix_valid   : "UH_FMT"\n", ptr_struct->num_vfs_msix_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pfs_valid        : "UH_FMT"\n", ptr_struct->num_pfs_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpp_valid            : "UH_FMT"\n", ptr_struct->fpp_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "full_vf_qos_valid    : "UH_FMT"\n", ptr_struct->full_vf_qos_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_valid          : "UH_FMT"\n", ptr_struct->sriov_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "total_vfs            : "UH_FMT"\n", ptr_struct->total_vfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pfs              : "UH_FMT"\n", ptr_struct->num_pfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpp_en               : "UH_FMT"\n", ptr_struct->fpp_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "full_vf_qos          : "UH_FMT"\n", ptr_struct->full_vf_qos);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_pf_uar_bar_size  : "UH_FMT"\n", ptr_struct->log_pf_uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_vf_uar_bar_size  : "UH_FMT"\n", ptr_struct->log_vf_uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pf_msix          : "UH_FMT"\n", ptr_struct->num_pf_msix);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_vf_msix          : "UH_FMT"\n", ptr_struct->num_vf_msix);

}

int tools_open_pci_configuration_size(void){
	 return 12;
}

void tools_open_pci_configuration_dump(const struct tools_open_pci_configuration *ptr_struct, FILE* file) {
	tools_open_pci_configuration_print(ptr_struct, file, 0);
}

void tools_open_pci_capabilities_pack(const struct tools_open_pci_capabilities *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pf_bar_size_supported);

	offset=6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_bar_size_supported);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pf_msix_supported);

	offset=4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_vf_msix_supported);

	offset=3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->num_pfs_supported);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_total_bar_valid);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_total_msix_valid);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->max_vfs_per_pf_valid);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_vfs_per_pf);

	offset=44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_num_pfs);

	offset=34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpp_support);

	offset=33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vf_qos_control_support);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_support);

	offset=90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_max_pf_uar_bar_size1);

	offset=84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_max_vf_uar_bar_size);

	offset=74;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->max_num_pf_msix);

	offset=64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->max_num_vf_msix);

	offset=96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->max_total_msix);

	offset=128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->max_total_bar);

}

void tools_open_pci_capabilities_unpack(struct tools_open_pci_capabilities *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=7;
	ptr_struct->pf_bar_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=6;
	ptr_struct->vf_bar_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=5;
	ptr_struct->num_pf_msix_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=4;
	ptr_struct->num_vf_msix_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=3;
	ptr_struct->num_pfs_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=2;
	ptr_struct->max_total_bar_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->max_total_msix_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->max_vfs_per_pf_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=48;
	ptr_struct->max_vfs_per_pf = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=44;
	ptr_struct->max_num_pfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=34;
	ptr_struct->fpp_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=33;
	ptr_struct->vf_qos_control_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->sriov_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=90;
	ptr_struct->log_max_pf_uar_bar_size1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=84;
	ptr_struct->log_max_vf_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset=74;
	ptr_struct->max_num_pf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=64;
	ptr_struct->max_num_vf_msix = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=96;
	ptr_struct->max_total_msix = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=128;
	ptr_struct->max_total_bar = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_pci_capabilities_print(const struct tools_open_pci_capabilities *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_pci_capabilities ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pf_bar_size_supported : "UH_FMT"\n", ptr_struct->pf_bar_size_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vf_bar_size_supported : "UH_FMT"\n", ptr_struct->vf_bar_size_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pf_msix_supported : "UH_FMT"\n", ptr_struct->num_pf_msix_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_vf_msix_supported : "UH_FMT"\n", ptr_struct->num_vf_msix_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_pfs_supported    : "UH_FMT"\n", ptr_struct->num_pfs_supported);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_total_bar_valid  : "UH_FMT"\n", ptr_struct->max_total_bar_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_total_msix_valid : "UH_FMT"\n", ptr_struct->max_total_msix_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_vfs_per_pf_valid : "UH_FMT"\n", ptr_struct->max_vfs_per_pf_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_vfs_per_pf       : "UH_FMT"\n", ptr_struct->max_vfs_per_pf);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_num_pfs          : "UH_FMT"\n", ptr_struct->max_num_pfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpp_support          : "UH_FMT"\n", ptr_struct->fpp_support);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vf_qos_control_support : "UH_FMT"\n", ptr_struct->vf_qos_control_support);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_support        : "UH_FMT"\n", ptr_struct->sriov_support);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_max_pf_uar_bar_size1 : "UH_FMT"\n", ptr_struct->log_max_pf_uar_bar_size1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_max_vf_uar_bar_size : "UH_FMT"\n", ptr_struct->log_max_vf_uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_num_pf_msix      : "UH_FMT"\n", ptr_struct->max_num_pf_msix);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_num_vf_msix      : "UH_FMT"\n", ptr_struct->max_num_vf_msix);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_total_msix       : "U32H_FMT"\n", ptr_struct->max_total_msix);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_total_bar        : "U32H_FMT"\n", ptr_struct->max_total_bar);

}

int tools_open_pci_capabilities_size(void){
	 return 20;
}

void tools_open_pci_capabilities_dump(const struct tools_open_pci_capabilities *ptr_struct, FILE* file) {
	tools_open_pci_capabilities_print(ptr_struct, file, 0);
}

void tools_open_tpt_configuration_pack(const struct tools_open_tpt_configuration *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_max_payload_size);

}

void tools_open_tpt_configuration_unpack(struct tools_open_tpt_configuration *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=28;
	ptr_struct->log_max_payload_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

}

void tools_open_tpt_configuration_print(const struct tools_open_tpt_configuration *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_tpt_configuration ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_max_payload_size : "UH_FMT"\n", ptr_struct->log_max_payload_size);

}

int tools_open_tpt_configuration_size(void){
	 return 4;
}

void tools_open_tpt_configuration_dump(const struct tools_open_tpt_configuration *ptr_struct, FILE* file) {
	tools_open_tpt_configuration_print(ptr_struct, file, 0);
}

void tools_open_tpt_capabilities_pack(const struct tools_open_tpt_capabilities *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->log_max_payload_size_supported);

}

void tools_open_tpt_capabilities_unpack(struct tools_open_tpt_capabilities *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->log_max_payload_size_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_tpt_capabilities_print(const struct tools_open_tpt_capabilities *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_tpt_capabilities ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_max_payload_size_supported : "UH_FMT"\n", ptr_struct->log_max_payload_size_supported);

}

int tools_open_tpt_capabilities_size(void){
	 return 4;
}

void tools_open_tpt_capabilities_dump(const struct tools_open_tpt_capabilities *ptr_struct, FILE* file) {
	tools_open_tpt_capabilities_print(ptr_struct, file, 0);
}

void tools_open_infiniband_dc_settings_pack(const struct tools_open_infiniband_dc_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->log_dcr_hash_table_size);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->dcr_lifo_size);

}

void tools_open_infiniband_dc_settings_unpack(struct tools_open_infiniband_dc_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=27;
	ptr_struct->log_dcr_hash_table_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset=40;
	ptr_struct->dcr_lifo_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

}

void tools_open_infiniband_dc_settings_print(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_infiniband_dc_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_dcr_hash_table_size : "UH_FMT"\n", ptr_struct->log_dcr_hash_table_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dcr_lifo_size        : "UH_FMT"\n", ptr_struct->dcr_lifo_size);

}

int tools_open_infiniband_dc_settings_size(void){
	 return 8;
}

void tools_open_infiniband_dc_settings_dump(const struct tools_open_infiniband_dc_settings *ptr_struct, FILE* file) {
	tools_open_infiniband_dc_settings_print(ptr_struct, file, 0);
}

void tools_open_infiniband_dc_capabilities_pack(const struct tools_open_infiniband_dc_capabilities *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->min_log_dcr_hash_table_size);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->max_log_dcr_hash_table_size);

	offset=64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->min_dcr_lifo_size);

	offset=96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->max_dcr_lifo_size);

}

void tools_open_infiniband_dc_capabilities_unpack(struct tools_open_infiniband_dc_capabilities *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->min_log_dcr_hash_table_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->max_log_dcr_hash_table_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=64;
	ptr_struct->min_dcr_lifo_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=96;
	ptr_struct->max_dcr_lifo_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_infiniband_dc_capabilities_print(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_infiniband_dc_capabilities ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "min_log_dcr_hash_table_size : "U32H_FMT"\n", ptr_struct->min_log_dcr_hash_table_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_log_dcr_hash_table_size : "U32H_FMT"\n", ptr_struct->max_log_dcr_hash_table_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "min_dcr_lifo_size    : "U32H_FMT"\n", ptr_struct->min_dcr_lifo_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_dcr_lifo_size    : "U32H_FMT"\n", ptr_struct->max_dcr_lifo_size);

}

int tools_open_infiniband_dc_capabilities_size(void){
	 return 16;
}

void tools_open_infiniband_dc_capabilities_dump(const struct tools_open_infiniband_dc_capabilities *ptr_struct, FILE* file) {
	tools_open_infiniband_dc_capabilities_print(ptr_struct, file, 0);
}

void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_psswd_magic);

	offset=21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_magic);

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_arp);

	offset=19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_bc);

	offset=18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_mc);

	offset=17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_uc);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_phy);

}

void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	ptr_struct->en_wol_psswd_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=21;
	ptr_struct->en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=20;
	ptr_struct->en_wol_arp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=19;
	ptr_struct->en_wol_bc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=18;
	ptr_struct->en_wol_mc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=17;
	ptr_struct->en_wol_uc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=16;
	ptr_struct->en_wol_phy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_wol ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_psswd_magic   : "UH_FMT"\n", ptr_struct->en_wol_psswd_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_magic         : "UH_FMT"\n", ptr_struct->en_wol_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_arp           : "UH_FMT"\n", ptr_struct->en_wol_arp);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_bc            : "UH_FMT"\n", ptr_struct->en_wol_bc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_mc            : "UH_FMT"\n", ptr_struct->en_wol_mc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_uc            : "UH_FMT"\n", ptr_struct->en_wol_uc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_phy           : "UH_FMT"\n", ptr_struct->en_wol_phy);

}

int tools_open_wol_size(void){
	 return 8;
}

void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE* file) {
	tools_open_wol_print(ptr_struct, file, 0);
}

void tools_open_misc_structs_pack(const union tools_open_misc_structs *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_mfg_info_pack(&(ptr_struct->mfg_info), ptr_buff);
}

void tools_open_misc_structs_unpack(union tools_open_misc_structs *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_mfg_info_unpack(&(ptr_struct->mfg_info), ptr_buff);
}

void tools_open_misc_structs_print(const union tools_open_misc_structs *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_misc_structs ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_info:\n");
	tools_open_image_info_print(&(ptr_struct->image_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfg_info:\n");
	tools_open_mfg_info_print(&(ptr_struct->mfg_info), file, indent_level + 1);

}

int tools_open_misc_structs_size(void){
	 return 1024;
}

void tools_open_misc_structs_dump(const union tools_open_misc_structs *ptr_struct, FILE* file) {
	tools_open_misc_structs_print(ptr_struct, file, 0);
}

void tools_open_aux_img_data_pack(const union tools_open_aux_img_data *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_aux_tlv_pack(&(ptr_struct->aux_tlv), ptr_buff);
}

void tools_open_aux_img_data_unpack(union tools_open_aux_img_data *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_aux_tlv_unpack(&(ptr_struct->aux_tlv), ptr_buff);
}

void tools_open_aux_img_data_print(const union tools_open_aux_img_data *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_aux_img_data ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "aux_data_hdr:\n");
	tools_open_aux_data_hdr_print(&(ptr_struct->aux_data_hdr), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "aux_tlv:\n");
	tools_open_aux_tlv_print(&(ptr_struct->aux_tlv), file, indent_level + 1);

}

int tools_open_aux_img_data_size(void){
	 return 256;
}

void tools_open_aux_img_data_dump(const union tools_open_aux_img_data *ptr_struct, FILE* file) {
	tools_open_aux_img_data_print(ptr_struct, file, 0);
}

void tools_open_hcr_cmds_pack(const union tools_open_hcr_cmds *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_query_def_params_per_port_pack(&(ptr_struct->query_def_params_per_port), ptr_buff);
}

void tools_open_hcr_cmds_unpack(union tools_open_hcr_cmds *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_query_def_params_per_port_unpack(&(ptr_struct->query_def_params_per_port), ptr_buff);
}

void tools_open_hcr_cmds_print(const union tools_open_hcr_cmds *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_hcr_cmds ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "query_def_params_global:\n");
	tools_open_query_def_params_global_print(&(ptr_struct->query_def_params_global), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "query_def_params_per_port:\n");
	tools_open_query_def_params_per_port_print(&(ptr_struct->query_def_params_per_port), file, indent_level + 1);

}

int tools_open_hcr_cmds_size(void){
	 return 264;
}

void tools_open_hcr_cmds_dump(const union tools_open_hcr_cmds *ptr_struct, FILE* file) {
	tools_open_hcr_cmds_print(ptr_struct, file, 0);
}

void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_phy_reg_pack(&(ptr_struct->PhyReg), ptr_buff);
}

void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_phy_reg_unpack(&(ptr_struct->PhyReg), ptr_buff);
}

void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_access_registers ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MNVReg:\n");
	tools_open_mnv_cfg_print(&(ptr_struct->MNVReg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "PhyReg:\n");
	tools_open_phy_reg_print(&(ptr_struct->PhyReg), file, indent_level + 1);

}

int tools_open_access_registers_size(void){
	 return 512;
}

void tools_open_access_registers_dump(const union tools_open_access_registers *ptr_struct, FILE* file) {
	tools_open_access_registers_print(ptr_struct, file, 0);
}

void tools_open_nv_cfg_pack(const union tools_open_nv_cfg *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_option_rom_capability_pack(&(ptr_struct->option_rom_capability), ptr_buff);
}

void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_option_rom_capability_unpack(&(ptr_struct->option_rom_capability), ptr_buff);
}

void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_nv_cfg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "wol:\n");
	tools_open_wol_print(&(ptr_struct->wol), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "infiniband_dc_capabilities:\n");
	tools_open_infiniband_dc_capabilities_print(&(ptr_struct->infiniband_dc_capabilities), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "infiniband_dc_settings:\n");
	tools_open_infiniband_dc_settings_print(&(ptr_struct->infiniband_dc_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tpt_capabilities:\n");
	tools_open_tpt_capabilities_print(&(ptr_struct->tpt_capabilities), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tpt_configuration:\n");
	tools_open_tpt_configuration_print(&(ptr_struct->tpt_configuration), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pci_capabilities:\n");
	tools_open_pci_capabilities_print(&(ptr_struct->pci_capabilities), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pci_configuration:\n");
	tools_open_pci_configuration_print(&(ptr_struct->pci_configuration), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "port_boot_state:\n");
	tools_open_port_boot_state_print(&(ptr_struct->port_boot_state), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_settings:\n");
	tools_open_iscsi_settings_print(&(ptr_struct->iscsi_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "infiniband_boot_settings:\n");
	tools_open_infiniband_boot_settings_print(&(ptr_struct->infiniband_boot_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_settings:\n");
	tools_open_boot_settings_print(&(ptr_struct->boot_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "preboot_boot_settings:\n");
	tools_open_preboot_boot_settings_print(&(ptr_struct->preboot_boot_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "preboot_flow_ctrl:\n");
	tools_open_preboot_flow_ctrl_print(&(ptr_struct->preboot_flow_ctrl), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov:\n");
	tools_open_sriov_print(&(ptr_struct->sriov), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "bar_size:\n");
	tools_open_bar_size_print(&(ptr_struct->bar_size), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vpi_settings:\n");
	tools_open_vpi_settings_print(&(ptr_struct->vpi_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_v_1_5_next_protocol:\n");
	tools_open_roce_v_1_5_next_protocol_print(&(ptr_struct->roce_v_1_5_next_protocol), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_cc:\n");
	tools_open_roce_cc_print(&(ptr_struct->roce_cc), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "roce_cc_ecn:\n");
	tools_open_roce_cc_ecn_print(&(ptr_struct->roce_cc_ecn), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_nb:\n");
	tools_open_lldp_nb_print(&(ptr_struct->lldp_nb), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lldp_nb_capability:\n");
	tools_open_lldp_nb_capability_print(&(ptr_struct->lldp_nb_capability), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "external_port:\n");
	tools_open_external_port_print(&(ptr_struct->external_port), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_settings_ext:\n");
	tools_open_boot_settings_ext_print(&(ptr_struct->boot_settings_ext), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "option_rom_capability:\n");
	tools_open_option_rom_capability_print(&(ptr_struct->option_rom_capability), file, indent_level + 1);

}

int tools_open_nv_cfg_size(void){
	 return 256;
}

void tools_open_nv_cfg_dump(const union tools_open_nv_cfg *ptr_struct, FILE* file) {
	tools_open_nv_cfg_print(ptr_struct, file, 0);
}

void tools_open_tools_open_pack(const union tools_open_tools_open *ptr_struct, u_int8_t* ptr_buff)
{
	tools_open_misc_structs_pack(&(ptr_struct->MiscStructs), ptr_buff);
}

void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t* ptr_buff)
{
	tools_open_misc_structs_unpack(&(ptr_struct->MiscStructs), ptr_buff);
}

void tools_open_tools_open_print(const union tools_open_tools_open *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_tools_open ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "NVConfig:\n");
	tools_open_nv_cfg_print(&(ptr_struct->NVConfig), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "AceessRegisters:\n");
	tools_open_access_registers_print(&(ptr_struct->AceessRegisters), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "HcrCmds:\n");
	tools_open_hcr_cmds_print(&(ptr_struct->HcrCmds), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "AuxImgData:\n");
	tools_open_aux_img_data_print(&(ptr_struct->AuxImgData), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MiscStructs:\n");
	tools_open_misc_structs_print(&(ptr_struct->MiscStructs), file, indent_level + 1);

}

int tools_open_tools_open_size(void){
	 return 1048576;
}

void tools_open_tools_open_dump(const union tools_open_tools_open *ptr_struct, FILE* file) {
	tools_open_tools_open_print(ptr_struct, file, 0);
}

void tools_open_uint64_pack(const struct tools_open_uint64 *ptr_struct, u_int8_t* ptr_buff){
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

void tools_open_uint64_unpack(struct tools_open_uint64 *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	u_int8_t val=0;
	(void)val;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_uint64_print(const struct tools_open_uint64 *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open_uint64 ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "hi                   : "U32H_FMT"\n", ptr_struct->hi);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lo                   : "U32H_FMT"\n", ptr_struct->lo);

}

int tools_open_uint64_size(void){
	 return 8;
}

void tools_open_uint64_dump(const struct tools_open_uint64 *ptr_struct, FILE* file) {
	tools_open_uint64_print(ptr_struct, file, 0);
}

