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

#ifndef __FWCTRL_IOCTL_H__
#define __FWCTRL_IOCTL_H__

#include <linux/types.h>
#include <linux/ioctl.h>

#include <linux/types.h>

#define FWCTL_METHOD_READ   1
#define FWCTL_METHOD_WRITE  0
#define FWCTL_ENV_VAR_DEBUG "FWCTL_DEBUG"

#define FWCTL_DEBUG_PRINT(mf, format, arg ...)                                         \
    if (mf->fwctl_env_var_debug) {                                                     \
        printf("%s: %s %d: " format, FWCTL_ENV_VAR_DEBUG, __func__, __LINE__, ## arg); \
    }

int fwctl_control_access_register(int fd, void *data_in,
                                  int size_in, __u16 reg_id,
                                  int method, int *reg_status,
                                  mfile* mf);
void fwctl_set_device_id(mfile* mf);
struct mlx5_umem_buff* mlx5lib_alloc_umem_mkey_buff(mfile* mf, size_t size, int page_size);
void mlx5lib_free_umem_mkey_buff(mfile* mf);

#define FWCTL_TYPE 0x9A

/**
 * DOC: General ioctl format
 *
 * The ioctl interface follows a general format to allow for extensibility. Each
 * ioctl is passed in a structure pointer as the argument providing the size of
 * the structure in the first u32. The kernel checks that any structure space
 * beyond what it understands is 0. This allows userspace to use the backward
 * compatible portion while consistently using the newer, larger, structures.
 *
 * ioctls use a standard meaning for common errnos:
 *
 *  - ENOTTY: The IOCTL number itself is not supported at all
 *  - E2BIG: The IOCTL number is supported, but the provided structure has
 *    non-zero in a part the kernel does not understand.
 *  - EOPNOTSUPP: The IOCTL number is supported, and the structure is
 *    understood, however a known field has a value the kernel does not
 *    understand or support.
 *  - EINVAL: Everything about the IOCTL was understood, but a field is not
 *    correct.
 *  - ENOMEM: Out of memory.
 *  - ENODEV: The underlying device has been hot-unplugged and the FD is
 *            orphaned.
 *
 * As well as additional errnos, within specific ioctls.
 */
enum {
	FWCTL_CMD_BASE = 0,
	FWCTL_CMD_INFO = 0,
	FWCTL_CMD_RPC = 1,
	FWCTL_CMD_RSC_DESTROY = 2,
	FWCTL_CMD_RSC_UMEM_REG = 3,
};

enum fwctl_device_type {
    FWCTL_DEVICE_TYPE_ERROR = 0,
    FWCTL_DEVICE_TYPE_MLX5  = 1,
};

/**
 * struct fwctl_info - ioctl(FWCTL_INFO)
 * @size: sizeof(struct fwctl_info)
 * @flags: Must be 0
 * @out_device_type: Returns the type of the device from enum fwctl_device_type
 * @device_data_len: On input the length of the out_device_data memory. On
 *	output the size of the kernel's device_data which may be larger or
 *	smaller than the input. Maybe 0 on input.
 * @out_device_data: Pointer to a memory of device_data_len bytes. Kernel will
 *	fill the entire memory, zeroing as required.
 *
 * Returns basic information about this fwctl instance, particularly what driver
 * is being used to define the device_data format.
 */
struct fwctl_info {
    __u32         size;
    __u32         flags;
    __u32         out_device_type;
    __u32         device_data_len;
    __aligned_u64 out_device_data;
};
#define FWCTL_INFO _IO(FWCTL_TYPE, FWCTL_CMD_INFO)

/**
 * struct fwctl_rpc - ioctl(FWCTL_RPC)
 * @size: sizeof(struct fwctl_rpc)
 * @flags: Must be 0
 * @in_len: Length of the in memory
 * @out_len: Length of the out memory
 * @in: Request message in device specific format
 * @out: Response message in device specific format
 *
 * Deliver a Remote Procedure Call to the device FW and return the response. The
 * call's parameters and return are marshaled into linear buffers of memory. Any
 * errno indicates that delivery of the RPC to the device failed. Return status
 * originating in the device during a successful delivery must be encoded into
 * out.
 *
 * The format of the buffers matches the out_device_type from FWCTL_INFO.
 */

 enum fwctl_umem_flags {
	FWCTL_UMEM_FLAG_MKEY = 1 << 0, /* Create Memory key */
	FWCTL_UMEM_FLAG_MCDD = 1 << 1, /* Create Memory key with DMA Device Direct */
};

struct fwctl_rpc {
    __u32         size;
    __u32         scope;
    __u32         in_len;
    __u32         out_len;
    __aligned_u64 in;
    __aligned_u64 out;
};

struct mlx5_umem_buff {
	void *buff;
	size_t size;
	__uint32_t umem_id;
	__uint32_t umem_mkey;
	__uint32_t rsc_id;
};

struct fwctl_rsc_umem_reg {
	__u32 size;
	__aligned_u64 flags;
	__aligned_u64 addr; /* user address */
	__aligned_u64 len; /* user buffer length */
	__u32 umem_id; /* returned device's umem ID */
	__u32 mkey_id; /* returned device's mkey ID */
	__u32 rsc_id; /* fwctl resource id */
};

struct fwctl_rsc_destroy {
	__u32 size;
	__aligned_u64 flags; /* TODO remove */
	__u32 type; /* enum fwctl_rsc_type */
	__u32 rsc_id; /* fwctl resource id */
};

#define FWCTL_RSC_UMEM_REG _IO(FWCTL_TYPE, FWCTL_CMD_RSC_UMEM_REG)
#define FWCTL_RSC_DESTROY _IO(FWCTL_TYPE, FWCTL_CMD_RSC_DESTROY)
#define FWCTL_RPC _IO(FWCTL_TYPE, FWCTL_CMD_RPC)

#endif /* __FWCTRL_IOCTL_H__ */
