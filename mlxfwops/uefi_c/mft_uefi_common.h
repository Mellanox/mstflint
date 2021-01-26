/*
 *
 * mft_uefi_common.h - Mellanox Technilogies LTD. UEFI common structs header file
 * ==================================================================
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
 *
 *  Version: $Id: $
 *
 */
#ifndef MFT_MLXFWOPS_UEFI_C_MFT_UEFI_COMMON_H_
#define MFT_MLXFWOPS_UEFI_C_MFT_UEFI_COMMON_H_


typedef struct _MLX4_DEV uefi_Dev_t;

typedef int (*f_fw_cmd) (uefi_Dev_t *dev, void *buffer, int *w_size, int *r_size);
typedef int (*f_dma_alloc) (uefi_Dev_t *dev, u_int64_t* pa, u_int64_t* va);

typedef struct uefi_dev_info {
    u_int32_t hw_dev_id;
    u_int32_t rev_id;
    u_int32_t max_buffer_size;
    u_int8_t no_fw_ctrl;
} uefi_dev_info_t;

typedef struct uefi_dev_extra {
    f_fw_cmd fw_cmd_func;
    f_dma_alloc dma_func;
    uefi_dev_info_t dev_info;
} uefi_dev_extra_t;


#endif /* MFT_MLXFWOPS_UEFI_C_MFT_UEFI_COMMON_H_ */
