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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/byteorder.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include "mtcr_mf.h"
#include "fwctrl.h"
#include "fwctrl_ioctl.h"

void fwctl_set_device_id(mfile* mf)
{
    unsigned char register_data[1024];
    int reg_status;

    memset(register_data, 0, sizeof(register_data));

    int rc = fwctl_control_access_register(mf->fd, register_data,
                                           sizeof(register_data), 0x9020,
                                           FWCTL_METHOD_READ, &reg_status,
                                           mf);

    if (!rc)
    {
        memcpy(&mf->device_hw_id, &register_data[8], 4);
        mf->device_hw_id = __cpu_to_be32(mf->device_hw_id);
    }
}


int fwctl_control_access_register(int fd, void *data_in,
                                  int size_in, __u16 reg_id,
                                  int method, int *reg_status,
                                  mfile* mf)
{
	int outlen = MLX5_ST_SZ_BYTES(access_register_out) + size_in;
	int inlen = MLX5_ST_SZ_BYTES(access_register_in) + size_in;
	struct fwctl_rpc rpc = {0};
	int err = -ENOMEM;
	__aligned_u64 *out = NULL;
	__aligned_u64 *in = NULL;
	void *data;
    void *status;

	in = malloc(inlen);
	out = malloc(outlen);
	if (!in || !out) {
		goto out;
    }

    memset(in, 0, inlen);
    memset(out, 0, outlen);

     rpc = (struct fwctl_rpc){
		.size = sizeof(rpc),
		.in = (uintptr_t)in,
		.in_len = inlen,
		.out = (uintptr_t)out,
		.out_len = outlen,
	};

	data = MLX5_ADDR_OF(access_register_in, in, register_data);
	memcpy(data, data_in, size_in);

	MLX5_SET(access_register_in, in, opcode, MLX5_CMD_OP_ACCESS_REG);
	MLX5_SET(access_register_in, in, op_mod, method);
	MLX5_SET(access_register_in, in, argument, 0);
	MLX5_SET(access_register_in, in, register_id, reg_id);

	err = ioctl(fd, FWCTL_RPC, &rpc);
	if (err) {
		FWCTL_DEBUG_PRINT(mf, "FWCTL_IOCTL_CMDRPC failed: %d errno(%d): %s\n", err, errno, strerror(errno));
		return err;
	}

    data = MLX5_ADDR_OF(access_register_out, out, register_data);
    status = MLX5_ADDR_OF(access_register_out, out, status);
	memcpy(data_in, data, size_in);
    memcpy(reg_status, status, sizeof(int));
    FWCTL_DEBUG_PRINT(mf, "register id = 0x%x, reg status = %d, error = %d\n", reg_id, *reg_status, err);

out:
	free(out);
	free(in);
	return err;
}
