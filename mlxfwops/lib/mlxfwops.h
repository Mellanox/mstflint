/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXFWOP_H
#define MLXFWOP_H

#include <stdio.h>
#include "mlxfwops_com.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct mlxfwops mlxfwops_t;

    struct image_context
    {
        void* data;
        u_int32_t size;
    };

    typedef struct
    {
        char* device_name;
        char* buf;
        int buf_size;
        int mcc_unsupported;
        int no_fw_ctrl;
    } fwops_params_t;

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_device(mlxfwops_t** mlxfwops_p, char* device_name);

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_device_verbose(mlxfwops_t** mlxfwops_p,
                                                          char* device_name,
                                                          char* buf,
                                                          int buf_size);

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_device_adv(mlxfwops_t** mlxfwops_p, fwops_params_t* params);

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_image(mlxfwops_t** mlxfwops_p, char* file_name, char* psid);

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_buffer(mlxfwops_t** mlxfwops_p, void* buffer, u_int32_t size, char* psid);

#ifdef CABLES_SUPP
    MLXFWOP_API int MLXFWOPCALL mlxfw_open_cable(mlxfwops_t** mlxfwops_p, char* handle_name, int port);
#endif

#ifdef UEFI_BUILD
#include <mft_uefi_common.h>

    MLXFWOP_API int MLXFWOPCALL mlxfw_open_uefi(mlxfwops_t** mlxfwops_p,
                                                uefi_Dev_t* dev,
                                                f_fw_cmd fw_cmd_func,
                                                f_dma_alloc dma_func,
                                                uefi_dev_info_t* dev_info);
    MLXFWOP_API int MLXFWOPCALL mlxfw_set_print(mlxfwops_t* mlxfwops, f_prog_func_str print_func);
    MLXFWOP_API const char* MLXFWOPCALL mlxfw_err2str(int err);

#endif

    MLXFWOP_API const char* MLXFWOPCALL mlxfw_get_last_error(mlxfwops_t* mlxfwops);

    MLXFWOP_API int MLXFWOPCALL mlxfw_get_last_error_code(mlxfwops_t* mlxfwops);

    MLXFWOP_API int MLXFWOPCALL mlxfw_burn(mlxfwops_t* dev_mlxfwops,
                                           mlxfwops_t* img_mlxfwops,
                                           u_int8_t force_version,
                                           f_prog_func prog_func,
                                           int allow_psid_change);

    MLXFWOP_API int MLXFWOPCALL mlxfw_read_image(mlxfwops_t* mlxfwops, void* image, u_int32_t* image_size);

    MLXFWOP_API int MLXFWOPCALL mlxfw_verify(mlxfwops_t* mlxfwops);

    MLXFWOP_API int MLXFWOPCALL mlxfw_query(mlxfwops_t* mlxfwops, fw_info_t* fw_query);

    MLXFWOP_API int MLXFWOPCALL mlxfw_type_match(mlxfwops_t* dev_mlxfwops, mlxfwops_t* img_mlxfwops);

    MLXFWOP_API int MLXFWOPCALL mlxfw_fs_check_and_update(fw_info_t* fw_info,
                                                          mlxfwops_t** dev_mlxfwops,
                                                          mlxfwops_t* img_mlxfwops,
                                                          u_int8_t force_version,
                                                          f_prog_func prog_func,
                                                          int allow_psid_change);

    MLXFWOP_API const char* MLXFWOPCALL mlxfw_exp_rom_type_to_str(u_int16_t type);

    MLXFWOP_API void MLXFWOPCALL mlxfw_close(mlxfwops_t* mlxfwops);

    MLXFWOP_API int MLXFWOPCALL mlxfw_test(mlxfwops_t* mlxfwops, u_int32_t* read_data);

#ifdef __cplusplus
}
#endif

#endif
