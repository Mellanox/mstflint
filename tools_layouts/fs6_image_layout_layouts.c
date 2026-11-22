/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 *** This file was generated at "2026-05-31 16:05:11"
 *** by:
 ***    > [REDACTED]/adb2pack.py --input adb/fs6_image_layout/fs6_image_layout.adb --file-prefix fs6_image_layout --prefix fs6_image_layout_ --no-adb-utils
 ***/
#include "fs6_image_layout_layouts.h"

void fs6_image_layout_hi_lo_pack(const struct fs6_image_layout_hi_lo* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hi);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lo);
}

void fs6_image_layout_hi_lo_unpack(struct fs6_image_layout_hi_lo* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    ptr_struct->hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_hi_lo_print(const struct fs6_image_layout_hi_lo* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_hi_lo ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "hi                   : " U32H_FMT "\n", ptr_struct->hi);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "lo                   : " U32H_FMT "\n", ptr_struct->lo);
}

unsigned int fs6_image_layout_hi_lo_size(void)
{
    return FS6_IMAGE_LAYOUT_HI_LO_SIZE;
}

void fs6_image_layout_hi_lo_dump(const struct fs6_image_layout_hi_lo* ptr_struct, FILE* fd)
{
    fs6_image_layout_hi_lo_print(ptr_struct, fd, 0);
}

void fs6_image_layout_reset_ver_info_pack(const struct fs6_image_layout_reset_ver_info* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 31;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->reset_ver_en);
    offset = 30;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->before_after_reset);
    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_vector_ver);
}

void fs6_image_layout_reset_ver_info_unpack(struct fs6_image_layout_reset_ver_info* ptr_struct,
                                            const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 31;
    ptr_struct->reset_ver_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
    offset = 30;
    ptr_struct->before_after_reset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
    offset = 16;
    ptr_struct->version_vector_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void fs6_image_layout_reset_ver_info_print(const struct fs6_image_layout_reset_ver_info* ptr_struct,
                                           FILE* fd,
                                           int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_reset_ver_info ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reset_ver_en         : " UH_FMT "\n", ptr_struct->reset_ver_en);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "before_after_reset   : " UH_FMT "\n", ptr_struct->before_after_reset);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version_vector_ver   : " UH_FMT "\n", ptr_struct->version_vector_ver);
}

unsigned int fs6_image_layout_reset_ver_info_size(void)
{
    return FS6_IMAGE_LAYOUT_RESET_VER_INFO_SIZE;
}

void fs6_image_layout_reset_ver_info_dump(const struct fs6_image_layout_reset_ver_info* ptr_struct, FILE* fd)
{
    fs6_image_layout_reset_ver_info_print(ptr_struct, fd, 0);
}

void fs6_image_layout_reset_version_v2_pack(const struct fs6_image_layout_reset_version_v2* ptr_struct,
                                            u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->major);
    offset = 12;
    adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->branch);
    offset = 4;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
}

void fs6_image_layout_reset_version_v2_unpack(struct fs6_image_layout_reset_version_v2* ptr_struct,
                                              const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 12;
    ptr_struct->branch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
    offset = 4;
    ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void fs6_image_layout_reset_version_v2_print(const struct fs6_image_layout_reset_version_v2* ptr_struct,
                                             FILE* fd,
                                             int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_reset_version_v2 ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "branch               : " UH_FMT "\n", ptr_struct->branch);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
}

unsigned int fs6_image_layout_reset_version_v2_size(void)
{
    return FS6_IMAGE_LAYOUT_RESET_VERSION_V2_SIZE;
}

void fs6_image_layout_reset_version_v2_dump(const struct fs6_image_layout_reset_version_v2* ptr_struct, FILE* fd)
{
    fs6_image_layout_reset_version_v2_print(ptr_struct, fd, 0);
}

void fs6_image_layout_uid_entry_pack(const struct fs6_image_layout_uid_entry* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);
    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);
    offset = 8;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated_msb);
    offset = 64;
    fs6_image_layout_hi_lo_pack(&(ptr_struct->uid), ptr_buff + offset / 8);
}

void fs6_image_layout_uid_entry_unpack(struct fs6_image_layout_uid_entry* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 16;
    ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 8;
    ptr_struct->num_allocated_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 64;
    fs6_image_layout_hi_lo_unpack(&(ptr_struct->uid), ptr_buff + offset / 8);
}

void fs6_image_layout_uid_entry_print(const struct fs6_image_layout_uid_entry* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_uid_entry ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_allocated        : " UH_FMT "\n", ptr_struct->num_allocated);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "step                 : " UH_FMT "\n", ptr_struct->step);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_allocated_msb    : " UH_FMT "\n", ptr_struct->num_allocated_msb);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "uid:\n");
    fs6_image_layout_hi_lo_print(&(ptr_struct->uid), fd, indent_level + 1);
}

unsigned int fs6_image_layout_uid_entry_size(void)
{
    return FS6_IMAGE_LAYOUT_UID_ENTRY_SIZE;
}

void fs6_image_layout_uid_entry_dump(const struct fs6_image_layout_uid_entry* ptr_struct, FILE* fd)
{
    fs6_image_layout_uid_entry_print(ptr_struct, fd, 0);
}

void fs6_image_layout_FW_VERSION_pack(const struct fs6_image_layout_FW_VERSION* ptr_struct, u_int8_t* ptr_buff)
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

void fs6_image_layout_FW_VERSION_unpack(struct fs6_image_layout_FW_VERSION* ptr_struct, const u_int8_t* ptr_buff)
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

void fs6_image_layout_FW_VERSION_print(const struct fs6_image_layout_FW_VERSION* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_FW_VERSION ========\n");

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

unsigned int fs6_image_layout_FW_VERSION_size(void)
{
    return FS6_IMAGE_LAYOUT_FW_VERSION_SIZE;
}

void fs6_image_layout_FW_VERSION_dump(const struct fs6_image_layout_FW_VERSION* ptr_struct, FILE* fd)
{
    fs6_image_layout_FW_VERSION_print(ptr_struct, fd, 0);
}

void fs6_image_layout_TRIPPLE_VERSION_pack(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                           u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MAJOR);
    offset = 48;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->SUBMINOR);
    offset = 32;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->MINOR);
}

void fs6_image_layout_TRIPPLE_VERSION_unpack(struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                             const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    ptr_struct->MAJOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 48;
    ptr_struct->SUBMINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 32;
    ptr_struct->MINOR = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void fs6_image_layout_TRIPPLE_VERSION_print(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                            FILE* fd,
                                            int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_TRIPPLE_VERSION ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "MAJOR                : " UH_FMT "\n", ptr_struct->MAJOR);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "SUBMINOR             : " UH_FMT "\n", ptr_struct->SUBMINOR);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "MINOR                : " UH_FMT "\n", ptr_struct->MINOR);
}

unsigned int fs6_image_layout_TRIPPLE_VERSION_size(void)
{
    return FS6_IMAGE_LAYOUT_TRIPPLE_VERSION_SIZE;
}

void fs6_image_layout_TRIPPLE_VERSION_dump(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct, FILE* fd)
{
    fs6_image_layout_TRIPPLE_VERSION_print(ptr_struct, fd, 0);
}

void fs6_image_layout_guids_pack(const struct fs6_image_layout_guids* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    fs6_image_layout_uid_entry_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
    offset = 128;
    fs6_image_layout_uid_entry_pack(&(ptr_struct->macs), ptr_buff + offset / 8);
}

void fs6_image_layout_guids_unpack(struct fs6_image_layout_guids* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    fs6_image_layout_uid_entry_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
    offset = 128;
    fs6_image_layout_uid_entry_unpack(&(ptr_struct->macs), ptr_buff + offset / 8);
}

void fs6_image_layout_guids_print(const struct fs6_image_layout_guids* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_guids ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "guids:\n");
    fs6_image_layout_uid_entry_print(&(ptr_struct->guids), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "macs:\n");
    fs6_image_layout_uid_entry_print(&(ptr_struct->macs), fd, indent_level + 1);
}

unsigned int fs6_image_layout_guids_size(void)
{
    return FS6_IMAGE_LAYOUT_GUIDS_SIZE;
}

void fs6_image_layout_guids_dump(const struct fs6_image_layout_guids* ptr_struct, FILE* fd)
{
    fs6_image_layout_guids_print(ptr_struct, fd, 0);
}

void fs6_image_layout_image_size_pack(const struct fs6_image_layout_image_size* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_step);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->run_from_any);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_size);
}

void fs6_image_layout_image_size_unpack(struct fs6_image_layout_image_size* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    ptr_struct->log_step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 0;
    ptr_struct->run_from_any = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
    offset = 32;
    ptr_struct->max_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_image_size_print(const struct fs6_image_layout_image_size* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_image_size ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "log_step             : " UH_FMT "\n", ptr_struct->log_step);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "run_from_any         : " UH_FMT "\n", ptr_struct->run_from_any);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "max_size             : " U32H_FMT "\n", ptr_struct->max_size);
}

unsigned int fs6_image_layout_image_size_size(void)
{
    return FS6_IMAGE_LAYOUT_IMAGE_SIZE_SIZE;
}

void fs6_image_layout_image_size_dump(const struct fs6_image_layout_image_size* ptr_struct, FILE* fd)
{
    fs6_image_layout_image_size_print(ptr_struct, fd, 0);
}

void fs6_image_layout_module_version_issu_pack(const struct fs6_image_layout_module_version_issu* ptr_struct,
                                               u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->branch);
    offset = 12;
    adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->minor);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->major);
    offset = 52;
    adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->notch);
}

void fs6_image_layout_module_version_issu_unpack(struct fs6_image_layout_module_version_issu* ptr_struct,
                                                 const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 24;
    ptr_struct->branch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 12;
    ptr_struct->minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
    offset = 0;
    ptr_struct->major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
    offset = 52;
    ptr_struct->notch = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void fs6_image_layout_module_version_issu_print(const struct fs6_image_layout_module_version_issu* ptr_struct,
                                                FILE* fd,
                                                int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_module_version_issu ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "branch               : " UH_FMT "\n", ptr_struct->branch);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "notch                : " UH_FMT "\n", ptr_struct->notch);
}

unsigned int fs6_image_layout_module_version_issu_size(void)
{
    return FS6_IMAGE_LAYOUT_MODULE_VERSION_ISSU_SIZE;
}

void fs6_image_layout_module_version_issu_dump(const struct fs6_image_layout_module_version_issu* ptr_struct, FILE* fd)
{
    fs6_image_layout_module_version_issu_print(ptr_struct, fd, 0);
}

void fs6_image_layout_version_vector_pack(const struct fs6_image_layout_version_vector* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    fs6_image_layout_reset_ver_info_pack(&(ptr_struct->reset_capabilities), ptr_buff + offset / 8);
    offset = 32;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
    offset = 64;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
    offset = 96;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->pci), ptr_buff + offset / 8);
    offset = 128;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->phy), ptr_buff + offset / 8);
    offset = 160;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->ini), ptr_buff + offset / 8);
    offset = 192;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->mng), ptr_buff + offset / 8);
    offset = 224;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
    offset = 256;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
    offset = 288;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->reserved4), ptr_buff + offset / 8);
    offset = 320;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->reserved5), ptr_buff + offset / 8);
    offset = 352;
    fs6_image_layout_reset_version_v2_pack(&(ptr_struct->reserved6), ptr_buff + offset / 8);
}

void fs6_image_layout_version_vector_unpack(struct fs6_image_layout_version_vector* ptr_struct,
                                            const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    fs6_image_layout_reset_ver_info_unpack(&(ptr_struct->reset_capabilities), ptr_buff + offset / 8);
    offset = 32;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->scratchpad), ptr_buff + offset / 8);
    offset = 64;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->icm_context), ptr_buff + offset / 8);
    offset = 96;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->pci), ptr_buff + offset / 8);
    offset = 128;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->phy), ptr_buff + offset / 8);
    offset = 160;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->ini), ptr_buff + offset / 8);
    offset = 192;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->mng), ptr_buff + offset / 8);
    offset = 224;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->reserved2), ptr_buff + offset / 8);
    offset = 256;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->reserved3), ptr_buff + offset / 8);
    offset = 288;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->reserved4), ptr_buff + offset / 8);
    offset = 320;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->reserved5), ptr_buff + offset / 8);
    offset = 352;
    fs6_image_layout_reset_version_v2_unpack(&(ptr_struct->reserved6), ptr_buff + offset / 8);
}

void fs6_image_layout_version_vector_print(const struct fs6_image_layout_version_vector* ptr_struct,
                                           FILE* fd,
                                           int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_version_vector ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reset_capabilities:\n");
    fs6_image_layout_reset_ver_info_print(&(ptr_struct->reset_capabilities), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "scratchpad:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->scratchpad), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "icm_context:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->icm_context), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "pci:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->pci), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "phy:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->phy), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "ini:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->ini), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "mng:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->mng), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reserved2:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->reserved2), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reserved3:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->reserved3), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reserved4:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->reserved4), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reserved5:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->reserved5), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "reserved6:\n");
    fs6_image_layout_reset_version_v2_print(&(ptr_struct->reserved6), fd, indent_level + 1);
}

unsigned int fs6_image_layout_version_vector_size(void)
{
    return FS6_IMAGE_LAYOUT_VERSION_VECTOR_SIZE;
}

void fs6_image_layout_version_vector_dump(const struct fs6_image_layout_version_vector* ptr_struct, FILE* fd)
{
    fs6_image_layout_version_vector_print(ptr_struct, fd, 0);
}

void fs6_image_layout_image_info_pack(const struct fs6_image_layout_image_info* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 30;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fa_token_supported);
    offset = 27;
    adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->encrypted_fw);
    offset = 26;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pscfw_en);
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
    fs6_image_layout_FW_VERSION_pack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
    offset = 160;
    fs6_image_layout_TRIPPLE_VERSION_pack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
    }
    offset = 432;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);
    offset = 423;
    adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->encrypted_nvdata);
    for (i = 0; i < 208; ++i)
    {
        offset = adb2c_calc_array_field_address(472, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
    }
    offset = 2112;
    fs6_image_layout_image_size_pack(&(ptr_struct->image_size), ptr_buff + offset / 8);
    for (i = 0; i < 4; ++i)
    {
        offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_hw_id[i]);
    }
    offset = 2368;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ini_file_num);
    offset = 2400;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->burn_image_size);
    offset = 2448;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->dtoc_offset);
    for (i = 0; i < 4; ++i)
    {
        offset = adb2c_calc_array_field_address(2464, 32, i, 8192, 1);
        adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_hw_id_extended[i]);
    }
    offset = 3200;
    fs6_image_layout_version_vector_pack(&(ptr_struct->version_vector), ptr_buff + offset / 8);
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prod_ver[i]);
    }
    for (i = 0; i < 256; ++i)
    {
        offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->description[i]);
    }
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(5768, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->board_name[i]);
    }
    offset = 6304;
    fs6_image_layout_module_version_issu_pack(&(ptr_struct->isfu), ptr_buff + offset / 8);
    offset = 6384;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->disabled_tiles_bitmap);
    for (i = 0; i < 64; ++i)
    {
        offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->name[i]);
    }
    for (i = 0; i < 96; ++i)
    {
        offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prs_name[i]);
    }
}

void fs6_image_layout_image_info_unpack(struct fs6_image_layout_image_info* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 30;
    ptr_struct->fa_token_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
    offset = 27;
    ptr_struct->encrypted_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
    offset = 26;
    ptr_struct->pscfw_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
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
    fs6_image_layout_FW_VERSION_unpack(&(ptr_struct->FW_VERSION), ptr_buff + offset / 8);
    offset = 160;
    fs6_image_layout_TRIPPLE_VERSION_unpack(&(ptr_struct->mic_version), ptr_buff + offset / 8);
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(312, 8, i, 8192, 1);
        ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->psid[16] = '\0';
    offset = 432;
    ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 423;
    ptr_struct->encrypted_nvdata = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
    for (i = 0; i < 208; ++i)
    {
        offset = adb2c_calc_array_field_address(472, 8, i, 8192, 1);
        ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->vsd[208] = '\0';
    offset = 2112;
    fs6_image_layout_image_size_unpack(&(ptr_struct->image_size), ptr_buff + offset / 8);
    for (i = 0; i < 4; ++i)
    {
        offset = adb2c_calc_array_field_address(2240, 32, i, 8192, 1);
        ptr_struct->supported_hw_id[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 2368;
    ptr_struct->ini_file_num = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 2400;
    ptr_struct->burn_image_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 2448;
    ptr_struct->dtoc_offset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    for (i = 0; i < 4; ++i)
    {
        offset = adb2c_calc_array_field_address(2464, 32, i, 8192, 1);
        ptr_struct->supported_hw_id_extended[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    }
    offset = 3200;
    fs6_image_layout_version_vector_unpack(&(ptr_struct->version_vector), ptr_buff + offset / 8);
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(3608, 8, i, 8192, 1);
        ptr_struct->prod_ver[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->prod_ver[16] = '\0';
    for (i = 0; i < 256; ++i)
    {
        offset = adb2c_calc_array_field_address(3736, 8, i, 8192, 1);
        ptr_struct->description[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->description[256] = '\0';
    for (i = 0; i < 16; ++i)
    {
        offset = adb2c_calc_array_field_address(5768, 8, i, 8192, 1);
        ptr_struct->board_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->board_name[16] = '\0';
    offset = 6304;
    fs6_image_layout_module_version_issu_unpack(&(ptr_struct->isfu), ptr_buff + offset / 8);
    offset = 6384;
    ptr_struct->disabled_tiles_bitmap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    for (i = 0; i < 64; ++i)
    {
        offset = adb2c_calc_array_field_address(6680, 8, i, 8192, 1);
        ptr_struct->name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->name[64] = '\0';
    for (i = 0; i < 96; ++i)
    {
        offset = adb2c_calc_array_field_address(7192, 8, i, 8192, 1);
        ptr_struct->prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->prs_name[96] = '\0';
}

void fs6_image_layout_image_info_print(const struct fs6_image_layout_image_info* ptr_struct, FILE* fd, int indent_level)
{
    int i;

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_image_info ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "fa_token_supported   : " UH_FMT "\n", ptr_struct->fa_token_supported);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "encrypted_fw         : " UH_FMT "\n", ptr_struct->encrypted_fw);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "pscfw_en             : " UH_FMT "\n", ptr_struct->pscfw_en);
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
    fs6_image_layout_FW_VERSION_print(&(ptr_struct->FW_VERSION), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "mic_version:\n");
    fs6_image_layout_TRIPPLE_VERSION_print(&(ptr_struct->mic_version), fd, indent_level + 1);
    fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "encrypted_nvdata     : " UH_FMT "\n", ptr_struct->encrypted_nvdata);
    fprintf(fd, "vsd                  : \"%s\"\n", ptr_struct->vsd);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "image_size:\n");
    fs6_image_layout_image_size_print(&(ptr_struct->image_size), fd, indent_level + 1);
    for (i = 0; i < 4; ++i)
    {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "supported_hw_id_%03d : " U32H_FMT "\n", i, ptr_struct->supported_hw_id[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "ini_file_num         : " U32H_FMT "\n", ptr_struct->ini_file_num);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "burn_image_size      : " U32H_FMT "\n", ptr_struct->burn_image_size);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "dtoc_offset          : " UH_FMT "\n", ptr_struct->dtoc_offset);
    for (i = 0; i < 4; ++i)
    {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "supported_hw_id_extended_%03d : " U32H_FMT "\n", i, ptr_struct->supported_hw_id_extended[i]);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version_vector:\n");
    fs6_image_layout_version_vector_print(&(ptr_struct->version_vector), fd, indent_level + 1);
    fprintf(fd, "prod_ver             : \"%s\"\n", ptr_struct->prod_ver);
    fprintf(fd, "description          : \"%s\"\n", ptr_struct->description);
    fprintf(fd, "board_name           : \"%s\"\n", ptr_struct->board_name);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "isfu:\n");
    fs6_image_layout_module_version_issu_print(&(ptr_struct->isfu), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "disabled_tiles_bitmap : " UH_FMT "\n", ptr_struct->disabled_tiles_bitmap);
    fprintf(fd, "name                 : \"%s\"\n", ptr_struct->name);
    fprintf(fd, "prs_name             : \"%s\"\n", ptr_struct->prs_name);
}

unsigned int fs6_image_layout_image_info_size(void)
{
    return FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE;
}

void fs6_image_layout_image_info_dump(const struct fs6_image_layout_image_info* ptr_struct, FILE* fd)
{
    fs6_image_layout_image_info_print(ptr_struct, fd, 0);
}

void fs6_image_layout_mfg_info_pack(const struct fs6_image_layout_mfg_info* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    for (i = 0; i < 16; ++i)
    {
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
    fs6_image_layout_guids_pack(&(ptr_struct->guids), ptr_buff + offset / 8);
    for (i = 0; i < 96; ++i)
    {
        offset = adb2c_calc_array_field_address(792, 8, i, 2560, 1);
        adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->orig_prs_name[i]);
    }
}

void fs6_image_layout_mfg_info_unpack(struct fs6_image_layout_mfg_info* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    for (i = 0; i < 16; ++i)
    {
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
    fs6_image_layout_guids_unpack(&(ptr_struct->guids), ptr_buff + offset / 8);
    for (i = 0; i < 96; ++i)
    {
        offset = adb2c_calc_array_field_address(792, 8, i, 2560, 1);
        ptr_struct->orig_prs_name[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    }
    ptr_struct->orig_prs_name[96] = '\0';
}

void fs6_image_layout_mfg_info_print(const struct fs6_image_layout_mfg_info* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_mfg_info ========\n");

    fprintf(fd, "psid                 : \"%s\"\n", ptr_struct->psid);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "guids_override_en    : " UH_FMT "\n", ptr_struct->guids_override_en);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "major_version        : " UH_FMT "\n", ptr_struct->major_version);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "guids:\n");
    fs6_image_layout_guids_print(&(ptr_struct->guids), fd, indent_level + 1);
    fprintf(fd, "orig_prs_name        : \"%s\"\n", ptr_struct->orig_prs_name);
}

unsigned int fs6_image_layout_mfg_info_size(void)
{
    return FS6_IMAGE_LAYOUT_MFG_INFO_SIZE;
}

void fs6_image_layout_mfg_info_dump(const struct fs6_image_layout_mfg_info* ptr_struct, FILE* fd)
{
    fs6_image_layout_mfg_info_print(ptr_struct, fd, 0);
}

void fs6_image_layout_fs6_image_layout_Nodes_pack(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                  u_int8_t* ptr_buff)
{
    fs6_image_layout_image_info_pack(&(ptr_struct->image_info), ptr_buff);
}

void fs6_image_layout_fs6_image_layout_Nodes_unpack(union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                    const u_int8_t* ptr_buff)
{
    fs6_image_layout_image_info_unpack(&(ptr_struct->image_info), ptr_buff);
}

void fs6_image_layout_fs6_image_layout_Nodes_print(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                   FILE* fd,
                                                   int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_fs6_image_layout_Nodes ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "image_info:\n");
    fs6_image_layout_image_info_print(&(ptr_struct->image_info), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "mfg_info:\n");
    fs6_image_layout_mfg_info_print(&(ptr_struct->mfg_info), fd, indent_level + 1);
}

unsigned int fs6_image_layout_fs6_image_layout_Nodes_size(void)
{
    return FS6_IMAGE_LAYOUT_FS6_IMAGE_LAYOUT_NODES_SIZE;
}

void fs6_image_layout_fs6_image_layout_Nodes_dump(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                  FILE* fd)
{
    fs6_image_layout_fs6_image_layout_Nodes_print(ptr_struct, fd, 0);
}

void fs6_image_layout_dev_area_crc_entry_pack(const struct fs6_image_layout_dev_area_crc_entry* ptr_struct,
                                              u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_type);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_size);
    offset = 64;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crc);
}

void fs6_image_layout_dev_area_crc_entry_unpack(struct fs6_image_layout_dev_area_crc_entry* ptr_struct,
                                                const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    ptr_struct->partition_type = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->partition_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 64;
    ptr_struct->crc = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_dev_area_crc_entry_print(const struct fs6_image_layout_dev_area_crc_entry* ptr_struct,
                                               FILE* fd,
                                               int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_dev_area_crc_entry ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "partition_type       : " U32H_FMT "\n", ptr_struct->partition_type);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "partition_size       : " U32H_FMT "\n", ptr_struct->partition_size);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "crc                  : " U32H_FMT "\n", ptr_struct->crc);
}

unsigned int fs6_image_layout_dev_area_crc_entry_size(void)
{
    return FS6_IMAGE_LAYOUT_DEV_AREA_CRC_ENTRY_SIZE;
}

void fs6_image_layout_dev_area_crc_entry_dump(const struct fs6_image_layout_dev_area_crc_entry* ptr_struct, FILE* fd)
{
    fs6_image_layout_dev_area_crc_entry_print(ptr_struct, fd, 0);
}

void fs6_image_layout_dev_area_crc_entry_legacy_pack(const struct fs6_image_layout_dev_area_crc_entry_legacy* ptr_struct,
                                                     u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_type);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crc);
}

void fs6_image_layout_dev_area_crc_entry_legacy_unpack(struct fs6_image_layout_dev_area_crc_entry_legacy* ptr_struct,
                                                       const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 0;
    ptr_struct->partition_type = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->crc = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_dev_area_crc_entry_legacy_print(
  const struct fs6_image_layout_dev_area_crc_entry_legacy* ptr_struct,
  FILE* fd,
  int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_dev_area_crc_entry_legacy ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "partition_type       : " U32H_FMT "\n", ptr_struct->partition_type);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "crc                  : " U32H_FMT "\n", ptr_struct->crc);
}

unsigned int fs6_image_layout_dev_area_crc_entry_legacy_size(void)
{
    return FS6_IMAGE_LAYOUT_DEV_AREA_CRC_ENTRY_LEGACY_SIZE;
}

void fs6_image_layout_dev_area_crc_entry_legacy_dump(const struct fs6_image_layout_dev_area_crc_entry_legacy* ptr_struct,
                                                     FILE* fd)
{
    fs6_image_layout_dev_area_crc_entry_legacy_print(ptr_struct, fd, 0);
}

void fs6_image_layout_dev_area_crc_info_pack(const struct fs6_image_layout_dev_area_crc_info* ptr_struct,
                                             u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_entries);
    for (i = 0; i < 14; ++i)
    {
        offset = adb2c_calc_array_field_address(64, 96, i, 8192, 1);
        fs6_image_layout_dev_area_crc_entry_pack(&(ptr_struct->crc_entry[i]), ptr_buff + offset / 8);
    }
    offset = 1408;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crc_square);
}

void fs6_image_layout_dev_area_crc_info_unpack(struct fs6_image_layout_dev_area_crc_info* ptr_struct,
                                               const u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 0;
    ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->num_entries = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    for (i = 0; i < 14; ++i)
    {
        offset = adb2c_calc_array_field_address(64, 96, i, 8192, 1);
        fs6_image_layout_dev_area_crc_entry_unpack(&(ptr_struct->crc_entry[i]), ptr_buff + offset / 8);
    }
    offset = 1408;
    ptr_struct->crc_square = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_dev_area_crc_info_print(const struct fs6_image_layout_dev_area_crc_info* ptr_struct,
                                              FILE* fd,
                                              int indent_level)
{
    int i;

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_dev_area_crc_info ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version              : " U32H_FMT "\n", ptr_struct->version);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_entries          : " U32H_FMT "\n", ptr_struct->num_entries);
    for (i = 0; i < 14; ++i)
    {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "crc_entry_%03d:\n", i);
        fs6_image_layout_dev_area_crc_entry_print(&(ptr_struct->crc_entry[i]), fd, indent_level + 1);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "crc_square           : " U32H_FMT "\n", ptr_struct->crc_square);
}

unsigned int fs6_image_layout_dev_area_crc_info_size(void)
{
    return FS6_IMAGE_LAYOUT_DEV_AREA_CRC_INFO_SIZE;
}

void fs6_image_layout_dev_area_crc_info_dump(const struct fs6_image_layout_dev_area_crc_info* ptr_struct, FILE* fd)
{
    fs6_image_layout_dev_area_crc_info_print(ptr_struct, fd, 0);
}

void fs6_image_layout_dev_area_crc_info_legacy_pack(const struct fs6_image_layout_dev_area_crc_info_legacy* ptr_struct,
                                                    u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 0;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_entries);
    for (i = 0; i < 14; ++i)
    {
        offset = adb2c_calc_array_field_address(64, 64, i, 8192, 1);
        fs6_image_layout_dev_area_crc_entry_legacy_pack(&(ptr_struct->crc_entry[i]), ptr_buff + offset / 8);
    }
    offset = 960;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crc_square);
}

void fs6_image_layout_dev_area_crc_info_legacy_unpack(struct fs6_image_layout_dev_area_crc_info_legacy* ptr_struct,
                                                      const u_int8_t* ptr_buff)
{
    u_int32_t offset;
    int i;

    offset = 0;
    ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 32;
    ptr_struct->num_entries = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    for (i = 0; i < 14; ++i)
    {
        offset = adb2c_calc_array_field_address(64, 64, i, 8192, 1);
        fs6_image_layout_dev_area_crc_entry_legacy_unpack(&(ptr_struct->crc_entry[i]), ptr_buff + offset / 8);
    }
    offset = 960;
    ptr_struct->crc_square = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs6_image_layout_dev_area_crc_info_legacy_print(const struct fs6_image_layout_dev_area_crc_info_legacy* ptr_struct,
                                                     FILE* fd,
                                                     int indent_level)
{
    int i;

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== fs6_image_layout_dev_area_crc_info_legacy ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version              : " U32H_FMT "\n", ptr_struct->version);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_entries          : " U32H_FMT "\n", ptr_struct->num_entries);
    for (i = 0; i < 14; ++i)
    {
        adb2c_add_indentation(fd, indent_level);
        fprintf(fd, "crc_entry_%03d:\n", i);
        fs6_image_layout_dev_area_crc_entry_legacy_print(&(ptr_struct->crc_entry[i]), fd, indent_level + 1);
    }
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "crc_square           : " U32H_FMT "\n", ptr_struct->crc_square);
}

unsigned int fs6_image_layout_dev_area_crc_info_legacy_size(void)
{
    return FS6_IMAGE_LAYOUT_DEV_AREA_CRC_INFO_LEGACY_SIZE;
}

void fs6_image_layout_dev_area_crc_info_legacy_dump(const struct fs6_image_layout_dev_area_crc_info_legacy* ptr_struct,
                                                    FILE* fd)
{
    fs6_image_layout_dev_area_crc_info_legacy_print(ptr_struct, fd, 0);
}
