
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
 ***    > [REDACTED]/adb2pack.py --input adb/tools_open/mlxarchive.adb
 *--file-prefix mlxarchive --prefix mlxarchive_ --no-adb-utils
 ***/
#ifndef MLXARCHIVE_LAYOUTS_H
#define MLXARCHIVE_LAYOUTS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "adb_to_c_utils.h"
    /* Description -   */
    /* Size in bytes - 4 */
    struct mlxarchive_common_header
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t length;
        /* Description -  */
        /* 0x0.16 - 0x0.23 */
        u_int8_t type;
        /* Description -  */
        /* 0x0.24 - 0x0.31 */
        u_int8_t version;
    };

    /* Description -   */
    /* Size in bytes - 16 */
    struct mlxarchive_component_desciptor
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t identifier;
        /* Description -  */
        /* 0x0.16 - 0x0.31 */
        u_int16_t pldm_classification;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.31 */
        u_int32_t cb_offset_h;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description -  */
        /* 0x8.0 - 0x8.31 */
        u_int32_t cb_offset_l;
        /*---------------- DWORD[3] (Offset 0xc) ----------------*/
        /* Description -  */
        /* 0xc.0 - 0xc.31 */
        u_int32_t size;
    };

    /* Description -   */
    /* Size in bytes - 8 */
    struct mlxarchive_component_ptr
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t component_index;
        /* Description -  */
        /* 0x0.16 - 0x0.23 */
        u_int8_t storage_id;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.31 */
        u_int32_t storage_address;
    };

    /* Description -   */
    /* Size in bytes - 4 */
    struct mlxarchive_multi_part
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t total_length;
        /* Description -  */
        /* 0x0.16 - 0x0.23 */
        u_int8_t number_of_extensions;
    };

    /* Description -   */
    /* Size in bytes - 28 */
    struct mlxarchive_package_descriptor
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t num_of_devices;
        /* Description -  */
        /* 0x0.16 - 0x0.31 */
        u_int16_t num_of_components;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.31 */
        u_int32_t cb_offset;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description -  */
        /* 0x8.0 - 0x8.31 */
        u_int32_t cb_archive_size;
        /*---------------- DWORD[3] (Offset 0xc) ----------------*/
        /* Description -  */
        /* 0xc.0 - 0xc.31 */
        u_int32_t cb_size_h;
        /*---------------- DWORD[4] (Offset 0x10) ----------------*/
        /* Description -  */
        /* 0x10.0 - 0x10.31 */
        u_int32_t cb_size_l;
        /*---------------- DWORD[5] (Offset 0x14) ----------------*/
        /* Description -  */
        /* 0x14.24 - 0x14.31 */
        u_int8_t cb_compression;
        /*---------------- DWORD[6] (Offset 0x18) ----------------*/
        /* Description -  */
        /* 0x18.0 - 0x18.31 */
        u_int32_t user_data_offset;
    };

    /* Description -   */
    /* Size in bytes - 12 */
    struct mlxarchive_version
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        u_int16_t version_sub_minor;
        /* Description -  */
        /* 0x0.16 - 0x0.23 */
        u_int8_t version_minor;
        /* Description -  */
        /* 0x0.24 - 0x0.31 */
        u_int8_t version_major;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.7 */
        u_int8_t day;
        /* Description -  */
        /* 0x4.8 - 0x4.15 */
        u_int8_t month;
        /* Description -  */
        /* 0x4.16 - 0x4.31 */
        u_int16_t year;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description -  */
        /* 0x8.8 - 0x8.15 */
        u_int8_t seconds;
        /* Description -  */
        /* 0x8.16 - 0x8.23 */
        u_int8_t minutes;
        /* Description -  */
        /* 0x8.24 - 0x8.31 */
        u_int8_t hour;
    };

    /* Description -  Mellanox Firmware Archiver 2 */
    /* Size in bytes - 32 */
    union mlxarchive_mlxarchive_nodes
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.31 */
        struct mlxarchive_common_header common_header;
        /* Description -  */
        /* 0x0.0 - 0x0.31 */
        struct mlxarchive_multi_part multi_part;
        /* Description -  */
        /* 0x0.0 - 0x18.31 */
        struct mlxarchive_package_descriptor package_descriptor;
        /* Description -  */
        /* 0x0.0 - 0xc.31 */
        struct mlxarchive_component_desciptor component_desciptor;
        /* Description -  */
        /* 0x0.0 - 0x8.31 */
        struct mlxarchive_version version;
        /* Description -  */
        /* 0x0.0 - 0x4.31 */
        struct mlxarchive_component_ptr component_ptr;
    };

    /*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
    /* common_header */
    void mlxarchive_common_header_pack(const struct mlxarchive_common_header* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_common_header_unpack(struct mlxarchive_common_header* ptr_struct, const u_int8_t* ptr_buff);
    void mlxarchive_common_header_print(const struct mlxarchive_common_header* ptr_struct, FILE* fd, int indent_level);
    unsigned int mlxarchive_common_header_size(void);
#define MLXARCHIVE_COMMON_HEADER_SIZE (0x4)
    void mlxarchive_common_header_dump(const struct mlxarchive_common_header* ptr_struct, FILE* fd);
    /* component_desciptor */
    void mlxarchive_component_desciptor_pack(const struct mlxarchive_component_desciptor* ptr_struct,
                                             u_int8_t* ptr_buff);
    void mlxarchive_component_desciptor_unpack(struct mlxarchive_component_desciptor* ptr_struct,
                                               const u_int8_t* ptr_buff);
    void mlxarchive_component_desciptor_print(const struct mlxarchive_component_desciptor* ptr_struct,
                                              FILE* fd,
                                              int indent_level);
    unsigned int mlxarchive_component_desciptor_size(void);
#define MLXARCHIVE_COMPONENT_DESCIPTOR_SIZE (0x10)
    void mlxarchive_component_desciptor_dump(const struct mlxarchive_component_desciptor* ptr_struct, FILE* fd);
    /* component_ptr */
    void mlxarchive_component_ptr_pack(const struct mlxarchive_component_ptr* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_component_ptr_unpack(struct mlxarchive_component_ptr* ptr_struct, const u_int8_t* ptr_buff);
    void mlxarchive_component_ptr_print(const struct mlxarchive_component_ptr* ptr_struct, FILE* fd, int indent_level);
    unsigned int mlxarchive_component_ptr_size(void);
#define MLXARCHIVE_COMPONENT_PTR_SIZE (0x8)
    void mlxarchive_component_ptr_dump(const struct mlxarchive_component_ptr* ptr_struct, FILE* fd);
    /* multi_part */
    void mlxarchive_multi_part_pack(const struct mlxarchive_multi_part* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_multi_part_unpack(struct mlxarchive_multi_part* ptr_struct, const u_int8_t* ptr_buff);
    void mlxarchive_multi_part_print(const struct mlxarchive_multi_part* ptr_struct, FILE* fd, int indent_level);
    unsigned int mlxarchive_multi_part_size(void);
#define MLXARCHIVE_MULTI_PART_SIZE (0x4)
    void mlxarchive_multi_part_dump(const struct mlxarchive_multi_part* ptr_struct, FILE* fd);
    /* package_descriptor */
    void mlxarchive_package_descriptor_pack(const struct mlxarchive_package_descriptor* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_package_descriptor_unpack(struct mlxarchive_package_descriptor* ptr_struct,
                                              const u_int8_t* ptr_buff);
    void mlxarchive_package_descriptor_print(const struct mlxarchive_package_descriptor* ptr_struct,
                                             FILE* fd,
                                             int indent_level);
    unsigned int mlxarchive_package_descriptor_size(void);
#define MLXARCHIVE_PACKAGE_DESCRIPTOR_SIZE (0x1c)
    void mlxarchive_package_descriptor_dump(const struct mlxarchive_package_descriptor* ptr_struct, FILE* fd);
    /* version */
    void mlxarchive_version_pack(const struct mlxarchive_version* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_version_unpack(struct mlxarchive_version* ptr_struct, const u_int8_t* ptr_buff);
    void mlxarchive_version_print(const struct mlxarchive_version* ptr_struct, FILE* fd, int indent_level);
    unsigned int mlxarchive_version_size(void);
#define MLXARCHIVE_VERSION_SIZE (0xc)
    void mlxarchive_version_dump(const struct mlxarchive_version* ptr_struct, FILE* fd);
    /* mlxarchive_nodes */
    void mlxarchive_mlxarchive_nodes_pack(const union mlxarchive_mlxarchive_nodes* ptr_struct, u_int8_t* ptr_buff);
    void mlxarchive_mlxarchive_nodes_unpack(union mlxarchive_mlxarchive_nodes* ptr_struct, const u_int8_t* ptr_buff);
    void mlxarchive_mlxarchive_nodes_print(const union mlxarchive_mlxarchive_nodes* ptr_struct,
                                           FILE* fd,
                                           int indent_level);
    unsigned int mlxarchive_mlxarchive_nodes_size(void);
#define MLXARCHIVE_MLXARCHIVE_NODES_SIZE (0x20)
    void mlxarchive_mlxarchive_nodes_dump(const union mlxarchive_mlxarchive_nodes* ptr_struct, FILE* fd);

#ifdef __cplusplus
}
#endif

#endif // MLXARCHIVE_LAYOUTS_H
