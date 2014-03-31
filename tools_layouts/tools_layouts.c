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
 *** This file was generated at "2014-03-11 10:10:14"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/tools/tools.adb --file-prefix tools --prefix tools_
 ***    and modified to fit the needs of mstflint.
 ***/
#include "tools_layouts.h"

void tools_mnv_hdr_pack(const struct tools_mnv_hdr *ptr_struct, u_int8_t* ptr_buff){
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

void tools_mnv_hdr_unpack(struct tools_mnv_hdr *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
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

void tools_mnv_hdr_print(const struct tools_mnv_hdr *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== mnv_hdr ========\n");
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

int tools_mnv_hdr_size(){
     return 8;
}

void tools_mnv_hdr_dump(const struct tools_mnv_hdr *ptr_struct, FILE* file) {
    tools_mnv_hdr_print(ptr_struct, file, 0);
}

void tools_mnvia_pack(const struct tools_mnvia *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_mnvia_unpack(struct tools_mnvia *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_mnvia_print(const struct tools_mnvia *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== mnvia ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "mnv_hdr:\n");
    tools_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

}

int tools_mnvia_size(){
     return 8;
}

void tools_mnvia_dump(const struct tools_mnvia *ptr_struct, FILE* file) {
    tools_mnvia_print(ptr_struct, file, 0);
}

void tools_mnvi_pack(const struct tools_mnvi *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_mnvi_unpack(struct tools_mnvi *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_mnvi_print(const struct tools_mnvi *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== mnvi ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "mnv_hdr:\n");
    tools_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

}

int tools_mnvi_size(){
     return 8;
}

void tools_mnvi_dump(const struct tools_mnvi *ptr_struct, FILE* file) {
    tools_mnvi_print(ptr_struct, file, 0);
}

void tools_mnva_pack(const struct tools_mnva *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

    for (i=0; i < 128; i++) {
    offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
    }

}

void tools_mnva_unpack(struct tools_mnva *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    tools_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

    for (i=0; i < 128; i++) {
    offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
    ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }

}

void tools_mnva_print(const struct tools_mnva *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== mnva ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "mnv_hdr:\n");
    tools_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

    for (i=0; i < 128; i++) {
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "data[%3d]            : "UH_FMT"\n", i, ptr_struct->data[i]);
    }

}

int tools_mnva_size(){
     return 256;
}

void tools_mnva_dump(const struct tools_mnva *ptr_struct, FILE* file) {
    tools_mnva_print(ptr_struct, file, 0);
}

void tools_sriov_pack(const struct tools_sriov *ptr_struct, u_int8_t* ptr_buff){
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

void tools_sriov_unpack(struct tools_sriov *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=16;
    ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

    offset=0;
    ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_sriov_print(const struct tools_sriov *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== sriov ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "total_vfs            : "UH_FMT"\n", ptr_struct->total_vfs);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

}

int tools_sriov_size(){
     return 4;
}

void tools_sriov_dump(const struct tools_sriov *ptr_struct, FILE* file) {
    tools_sriov_print(ptr_struct, file, 0);
}

void tools_bar_size_pack(const struct tools_bar_size *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->log_uar_bar_size);

}

void tools_bar_size_unpack(struct tools_bar_size *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    ptr_struct->log_uar_bar_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_bar_size_print(const struct tools_bar_size *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== bar_size ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "log_uar_bar_size     : "U32H_FMT"\n", ptr_struct->log_uar_bar_size);

}

int tools_bar_size_size(){
     return 4;
}

void tools_bar_size_dump(const struct tools_bar_size *ptr_struct, FILE* file) {
    tools_bar_size_print(ptr_struct, file, 0);
}

void tools_vpi_settings_pack(const struct tools_vpi_settings *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=30;
    adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->network_link_type);

}

void tools_vpi_settings_unpack(struct tools_vpi_settings *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=30;
    ptr_struct->network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

}

void tools_vpi_settings_print(const struct tools_vpi_settings *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== vpi_settings ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "network_link_type    : "UH_FMT"\n", ptr_struct->network_link_type);

}

int tools_vpi_settings_size(){
     return 4;
}

void tools_vpi_settings_dump(const struct tools_vpi_settings *ptr_struct, FILE* file) {
    tools_vpi_settings_print(ptr_struct, file, 0);
}

void tools_wol_pack(const struct tools_wol *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=22;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved0);

    offset=21;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_magic);

    offset=20;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved1);

    offset=19;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved2);

    offset=18;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved3);

    offset=17;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved4);

    offset=16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reserved5);

}

void tools_wol_unpack(struct tools_wol *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=22;
    ptr_struct->reserved0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=21;
    ptr_struct->en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=20;
    ptr_struct->reserved1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=19;
    ptr_struct->reserved2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=18;
    ptr_struct->reserved3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=17;
    ptr_struct->reserved4 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

    offset=16;
    ptr_struct->reserved5 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_wol_print(const struct tools_wol *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== wol ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved0   : "UH_FMT"\n", ptr_struct->reserved0);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "en_wol_magic         : "UH_FMT"\n", ptr_struct->en_wol_magic);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved1           : "UH_FMT"\n", ptr_struct->reserved1);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved2            : "UH_FMT"\n", ptr_struct->reserved2);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved3            : "UH_FMT"\n", ptr_struct->reserved3);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved4            : "UH_FMT"\n", ptr_struct->reserved4);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "reserved5           : "UH_FMT"\n", ptr_struct->reserved5);

}

int tools_wol_size(){
     return 8;
}

void tools_wol_dump(const struct tools_wol *ptr_struct, FILE* file) {
    tools_wol_print(ptr_struct, file, 0);
}

