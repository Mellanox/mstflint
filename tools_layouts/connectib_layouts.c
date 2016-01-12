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

#include "connectib_layouts.h"

void connectib_FW_VERSION_pack(const struct connectib_FW_VERSION *ptr_struct, u_int8_t* ptr_buff){
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

void connectib_FW_VERSION_unpack(struct connectib_FW_VERSION *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    u_int8_t val=0;
    (void)val;
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

void connectib_FW_VERSION_print(const struct connectib_FW_VERSION *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== connectib_FW_VERSION ========\n");
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

int connectib_FW_VERSION_size(void){
     return 16;
}

void connectib_FW_VERSION_dump(const struct connectib_FW_VERSION *ptr_struct, FILE* file) {
    connectib_FW_VERSION_print(ptr_struct, file, 0);
}

void connectib_icmd_get_fw_info_pack(const struct connectib_icmd_get_fw_info *ptr_struct, u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    connectib_FW_VERSION_pack(&(ptr_struct->fw_version), ptr_buff + offset/8);

    offset=144;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hash_signature);

}

void connectib_icmd_get_fw_info_unpack(struct connectib_icmd_get_fw_info *ptr_struct, const u_int8_t* ptr_buff){
    u_int32_t offset;
    int i=0;
    u_int8_t val=0;
    (void)val;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset=0;
    connectib_FW_VERSION_unpack(&(ptr_struct->fw_version), ptr_buff + offset/8);

    offset=144;
    ptr_struct->hash_signature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void connectib_icmd_get_fw_info_print(const struct connectib_icmd_get_fw_info *ptr_struct, FILE* file, int indent_level){
    adb2c_add_indentation(file, indent_level);
    fprintf(file, "======== connectib_icmd_get_fw_info ========\n");
    int i=0;
    (void)i;(void)ptr_struct;
    (void)file;
    (void)indent_level;

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "fw_version:\n");
    connectib_FW_VERSION_print(&(ptr_struct->fw_version), file, indent_level + 1);

    adb2c_add_indentation(file, indent_level);
    fprintf(file, "hash_signature       : "UH_FMT"\n", ptr_struct->hash_signature);

}

int connectib_icmd_get_fw_info_size(void){
     return 32;
}

void connectib_icmd_get_fw_info_dump(const struct connectib_icmd_get_fw_info *ptr_struct, FILE* file) {
    connectib_icmd_get_fw_info_print(ptr_struct, file, 0);
}

