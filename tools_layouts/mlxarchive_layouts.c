
/* Copyright (c) 2013-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *** This file was generated at "2023-01-05 14:52:46"
 *** by:
 ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/mlxarchive.adb
 *--file-prefix mlxarchive --prefix mlxarchive_ --no-adb-utils
 ***/
#include "mlxarchive_layouts.h"

void mlxarchive_common_header_pack(const struct mlxarchive_common_header* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->length);
    offset = 8;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version);
}

void mlxarchive_common_header_unpack(struct mlxarchive_common_header* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 8;
    ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 0;
    ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void mlxarchive_common_header_print(const struct mlxarchive_common_header* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_common_header ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "length               : " UH_FMT "\n", ptr_struct->length);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
}

unsigned int mlxarchive_common_header_size(void)
{
    return MLXARCHIVE_COMMON_HEADER_SIZE;
}

void mlxarchive_common_header_dump(const struct mlxarchive_common_header* ptr_struct, FILE* fd)
{
    mlxarchive_common_header_print(ptr_struct, fd, 0);
}

void mlxarchive_component_desciptor_pack(const struct mlxarchive_component_desciptor* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->identifier);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pldm_classification);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset_h);
    offset = 64;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset_l);
    offset = 96;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->size);
}

void mlxarchive_component_desciptor_unpack(struct mlxarchive_component_desciptor* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 0;
    ptr_struct->pldm_classification = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 32;
    ptr_struct->cb_offset_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 64;
    ptr_struct->cb_offset_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 96;
    ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void mlxarchive_component_desciptor_print(const struct mlxarchive_component_desciptor* ptr_struct,
                                          FILE* fd,
                                          int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_component_desciptor ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "identifier           : " UH_FMT "\n", ptr_struct->identifier);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "pldm_classification  : " UH_FMT "\n", ptr_struct->pldm_classification);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_offset_h          : " U32H_FMT "\n", ptr_struct->cb_offset_h);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_offset_l          : " U32H_FMT "\n", ptr_struct->cb_offset_l);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "size                 : " U32H_FMT "\n", ptr_struct->size);
}

unsigned int mlxarchive_component_desciptor_size(void)
{
    return MLXARCHIVE_COMPONENT_DESCIPTOR_SIZE;
}

void mlxarchive_component_desciptor_dump(const struct mlxarchive_component_desciptor* ptr_struct, FILE* fd)
{
    mlxarchive_component_desciptor_print(ptr_struct, fd, 0);
}

void mlxarchive_component_ptr_pack(const struct mlxarchive_component_ptr* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);
    offset = 8;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->storage_id);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->storage_address);
}

void mlxarchive_component_ptr_unpack(struct mlxarchive_component_ptr* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 8;
    ptr_struct->storage_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 32;
    ptr_struct->storage_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void mlxarchive_component_ptr_print(const struct mlxarchive_component_ptr* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_component_ptr ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "component_index      : " UH_FMT "\n", ptr_struct->component_index);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "storage_id           : " UH_FMT "\n", ptr_struct->storage_id);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "storage_address      : " U32H_FMT "\n", ptr_struct->storage_address);
}

unsigned int mlxarchive_component_ptr_size(void)
{
    return MLXARCHIVE_COMPONENT_PTR_SIZE;
}

void mlxarchive_component_ptr_dump(const struct mlxarchive_component_ptr* ptr_struct, FILE* fd)
{
    mlxarchive_component_ptr_print(ptr_struct, fd, 0);
}

void mlxarchive_multi_part_pack(const struct mlxarchive_multi_part* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_length);
    offset = 8;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->number_of_extensions);
}

void mlxarchive_multi_part_unpack(struct mlxarchive_multi_part* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->total_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 8;
    ptr_struct->number_of_extensions = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void mlxarchive_multi_part_print(const struct mlxarchive_multi_part* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_multi_part ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "total_length         : " UH_FMT "\n", ptr_struct->total_length);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "number_of_extensions : " UH_FMT "\n", ptr_struct->number_of_extensions);
}

unsigned int mlxarchive_multi_part_size(void)
{
    return MLXARCHIVE_MULTI_PART_SIZE;
}

void mlxarchive_multi_part_dump(const struct mlxarchive_multi_part* ptr_struct, FILE* fd)
{
    mlxarchive_multi_part_print(ptr_struct, fd, 0);
}

void mlxarchive_package_descriptor_pack(const struct mlxarchive_package_descriptor* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_devices);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_components);
    offset = 32;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_offset);
    offset = 64;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_archive_size);
    offset = 96;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_size_h);
    offset = 128;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cb_size_l);
    offset = 160;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cb_compression);
    offset = 192;
    adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->user_data_offset);
}

void mlxarchive_package_descriptor_unpack(struct mlxarchive_package_descriptor* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->num_of_devices = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 0;
    ptr_struct->num_of_components = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 32;
    ptr_struct->cb_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 64;
    ptr_struct->cb_archive_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 96;
    ptr_struct->cb_size_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 128;
    ptr_struct->cb_size_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
    offset = 160;
    ptr_struct->cb_compression = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 192;
    ptr_struct->user_data_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void mlxarchive_package_descriptor_print(const struct mlxarchive_package_descriptor* ptr_struct,
                                         FILE* fd,
                                         int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_package_descriptor ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_of_devices       : " UH_FMT "\n", ptr_struct->num_of_devices);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "num_of_components    : " UH_FMT "\n", ptr_struct->num_of_components);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_offset            : " U32H_FMT "\n", ptr_struct->cb_offset);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_archive_size      : " U32H_FMT "\n", ptr_struct->cb_archive_size);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_size_h            : " U32H_FMT "\n", ptr_struct->cb_size_h);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_size_l            : " U32H_FMT "\n", ptr_struct->cb_size_l);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "cb_compression       : " UH_FMT "\n", ptr_struct->cb_compression);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "user_data_offset     : " U32H_FMT "\n", ptr_struct->user_data_offset);
}

unsigned int mlxarchive_package_descriptor_size(void)
{
    return MLXARCHIVE_PACKAGE_DESCRIPTOR_SIZE;
}

void mlxarchive_package_descriptor_dump(const struct mlxarchive_package_descriptor* ptr_struct, FILE* fd)
{
    mlxarchive_package_descriptor_print(ptr_struct, fd, 0);
}

void mlxarchive_version_pack(const struct mlxarchive_version* ptr_struct, u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->version_sub_minor);
    offset = 8;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_minor);
    offset = 0;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_major);
    offset = 56;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->day);
    offset = 48;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->month);
    offset = 32;
    adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->year);
    offset = 80;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->seconds);
    offset = 72;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minutes);
    offset = 64;
    adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hour);
}

void mlxarchive_version_unpack(struct mlxarchive_version* ptr_struct, const u_int8_t* ptr_buff)
{
    u_int32_t offset;

    offset = 16;
    ptr_struct->version_sub_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 8;
    ptr_struct->version_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 0;
    ptr_struct->version_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 56;
    ptr_struct->day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 48;
    ptr_struct->month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 32;
    ptr_struct->year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
    offset = 80;
    ptr_struct->seconds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 72;
    ptr_struct->minutes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
    offset = 64;
    ptr_struct->hour = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void mlxarchive_version_print(const struct mlxarchive_version* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_version ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version_sub_minor    : " UH_FMT "\n", ptr_struct->version_sub_minor);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version_minor        : " UH_FMT "\n", ptr_struct->version_minor);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version_major        : " UH_FMT "\n", ptr_struct->version_major);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "day                  : " UH_FMT "\n", ptr_struct->day);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "month                : " UH_FMT "\n", ptr_struct->month);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "year                 : " UH_FMT "\n", ptr_struct->year);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "seconds              : " UH_FMT "\n", ptr_struct->seconds);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "minutes              : " UH_FMT "\n", ptr_struct->minutes);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "hour                 : " UH_FMT "\n", ptr_struct->hour);
}

unsigned int mlxarchive_version_size(void)
{
    return MLXARCHIVE_VERSION_SIZE;
}

void mlxarchive_version_dump(const struct mlxarchive_version* ptr_struct, FILE* fd)
{
    mlxarchive_version_print(ptr_struct, fd, 0);
}

void mlxarchive_mlxarchive_nodes_pack(const union mlxarchive_mlxarchive_nodes* ptr_struct, u_int8_t* ptr_buff)
{
    mlxarchive_package_descriptor_pack(&(ptr_struct->package_descriptor), ptr_buff);
}

void mlxarchive_mlxarchive_nodes_unpack(union mlxarchive_mlxarchive_nodes* ptr_struct, const u_int8_t* ptr_buff)
{
    mlxarchive_package_descriptor_unpack(&(ptr_struct->package_descriptor), ptr_buff);
}

void mlxarchive_mlxarchive_nodes_print(const union mlxarchive_mlxarchive_nodes* ptr_struct, FILE* fd, int indent_level)
{
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "======== mlxarchive_mlxarchive_nodes ========\n");

    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "common_header:\n");
    mlxarchive_common_header_print(&(ptr_struct->common_header), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "multi_part:\n");
    mlxarchive_multi_part_print(&(ptr_struct->multi_part), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "package_descriptor:\n");
    mlxarchive_package_descriptor_print(&(ptr_struct->package_descriptor), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "component_desciptor:\n");
    mlxarchive_component_desciptor_print(&(ptr_struct->component_desciptor), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "version:\n");
    mlxarchive_version_print(&(ptr_struct->version), fd, indent_level + 1);
    adb2c_add_indentation(fd, indent_level);
    fprintf(fd, "component_ptr:\n");
    mlxarchive_component_ptr_print(&(ptr_struct->component_ptr), fd, indent_level + 1);
}

unsigned int mlxarchive_mlxarchive_nodes_size(void)
{
    return MLXARCHIVE_MLXARCHIVE_NODES_SIZE;
}

void mlxarchive_mlxarchive_nodes_dump(const union mlxarchive_mlxarchive_nodes* ptr_struct, FILE* fd)
{
    mlxarchive_mlxarchive_nodes_print(ptr_struct, fd, 0);
}
