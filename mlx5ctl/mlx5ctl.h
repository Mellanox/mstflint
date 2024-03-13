/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#ifndef __MLX5CTL_IOCTL_H__
#define __MLX5CTL_IOCTL_H__

#include <linux/types.h>

#define DEV_PATH_MAX 256
#define DEV_NAME_MAX 64

struct mlx5ctl_info {
	__u16 uctx_uid; /* current process allocated UCTX UID */
	__u16 reserved1; /* explicit padding must be zero */
	__u32 uctx_cap; /* current process effective UCTX cap */
	__u32 dev_uctx_cap; /* device's UCTX capabilities */
	__u32 ucap; /* process user capability */
};

struct mlx5ctl_cmdrpc {
	__aligned_u64 in; /* RPC inbox buffer user address */
	__aligned_u64 out; /* RPC outbox buffer user address */
	__u32 inlen; /* inbox buffer length */
	__u32 outlen; /* outbox buffer length */
};

struct mlx5ctl_dev {
	int ctl_id;
	char ctldev[DEV_NAME_MAX];
	char mdev[DEV_NAME_MAX];
};

struct mlx5u_dev {
	char devname[DEV_NAME_MAX];
	int fd;
};

extern int verbosity_level;

#define err_msg(fmt, ...) \
	fprintf(stderr, "Error : " fmt, ##__VA_ARGS__)

#define info_msg(fmt, ...) \
	fprintf(stdout, "INFO : " fmt,  ##__VA_ARGS__)

#define dbg_msg(verbosity, fmt, ...) \
	do { \
		if (verbosity <= verbosity_level) { \
			fprintf(stdout, "[DEBUG] (%s:%d %s) "fmt , __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		} \
	} while (0)

#define MLX5CTL_MAX_RPC_SIZE (512 * 512) /* max FW RPC buffer size 512 blocks of 512 bytes */

#define MLX5CTL_IOCTL_MAGIC 0x5c

#define MLX5CTL_IOCTL_INFO \
	_IOR(MLX5CTL_IOCTL_MAGIC, 0x0, struct mlx5ctl_info)

#define MLX5CTL_IOCTL_CMDRPC \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x1, struct mlx5ctl_cmdrpc)

#endif /* __MLX5CTL_IOCTL_H__ */
