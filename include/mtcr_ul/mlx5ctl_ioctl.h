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
#ifndef __MLX5_CONTROL_IOCTL_H__
#define __MLX5_CONTROL_IOCTL_H__

#include <linux/types.h>

int mlx5_control_access_register(int fd, void *data_in,
                                 int size_in, __u16 reg_id,
                                 int method, int *reg_status,
                                 mfile* mf);
void mlx5ctl_set_device_id(mfile* mf);

struct mlx5ctl_drvinfo {
	__u32 version;
	__u64 fw_ver_sub:16;
	__u64 fw_ver_minor:16;
	__u64 fw_ver_major:16;
	char board_id[64];
	char devname[32];
	__u32 reserved[128];
	__u16 ext_info_len;
	__u8 ext_info[0];
};

struct mlx5ctl_cmd_inout {
	void *in;
	__u16 inlen;
	void *out;
	__u16 outlen;
};

#define MLX5CTL_METHOD_READ     1
#define MLX5CTL_METHOD_WRITE    0
#define MLX5CTL_IOCTL_MAGIC     0xc8
#define MLX5CTL_ENV_VAR_DEBUG   "MLX5CTL_DEBUG"

#define MLX5CTL_DEBUG_PRINT(mf, format, arg...) \
    if (mf->mlx5ctl_env_var_debug) {        \
        printf("%s: %s %d: " format, MLX5CTL_ENV_VAR_DEBUG, __func__, __LINE__, ##arg); \
    }

#define MLX5CTL_IOCTL_DRVINFO \
	_IOR(MLX5CTL_IOCTL_MAGIC, 0x0, struct mlx5ctl_drvinfo)

#define MLX5CTL_IOCTL_CMD_INOUT \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x1, struct mlx5ctl_cmd_inout)

#endif /* __MLX5_CONTROL_IOCTL_H__ */
