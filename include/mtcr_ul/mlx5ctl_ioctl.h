/* SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2022, NVIDIA CORPORATION & AFFILIATES. All rights reserved. */

#ifndef __MLX5_CONTROL_IOCTL_H__
#define __MLX5_CONTROL_IOCTL_H__

#include <linux/types.h>

int mlx5_control_access_register(int fd, void *data_in,
                                 int size_in, __u16 reg_id,
                                 int method);

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

#define MLX5CTL_IOCTL_MAGIC 0xc8

#define MLX5CTL_IOCTL_DRVINFO \
	_IOR(MLX5CTL_IOCTL_MAGIC, 0x0, struct mlx5ctl_drvinfo)

#define MLX5CTL_IOCTL_CMD_INOUT \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x1, struct mlx5ctl_cmd_inout)

#endif /* __MLX5_CONTROL_IOCTL_H__ */
