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
#include <malloc.h>
#include <endian.h>
#include <sys/ioctl.h>
#include <asm/byteorder.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include "mtcr.h"
#include "mtcr_mf.h"
#include "mtcr_ul_com.h"
#include "fwctrl.h"
#include "fwctrl_ioctl.h"


void fwctl_set_device_id(mfile* mf)
{
    unsigned char register_data[1024];
    int           reg_status;

    memset(register_data, 0, sizeof(register_data));

    int rc = fwctl_control_access_register(mf->fd, register_data,
                                           sizeof(register_data), 0x9020,
                                           FWCTL_METHOD_READ, &reg_status,
                                           mf);

    if (!rc) {
        memcpy(&mf->device_hw_id, &register_data[8], 4);
        mf->device_hw_id = __cpu_to_be32(mf->device_hw_id);
    }
}

int translate_cmd_status_to_reg_status(int cmd_status)
{
    switch (cmd_status)
    {
        case MLX5_CMD_STAT_OK:
            return ME_REG_ACCESS_OK;

        case MLX5_CMD_STAT_INT_ERR:
            return ME_REG_ACCESS_INTERNAL_ERROR;

        case MLX5_CMD_STAT_BAD_OP_ERR:
            return ME_REG_ACCESS_BAD_METHOD;

        case MLX5_CMD_STAT_BAD_PARAM_ERR:
            return ME_REG_ACCESS_BAD_PARAM;

        case MLX5_CMD_STAT_BAD_SYS_STATE_ERR:
            return ME_REG_ACCESS_REG_NOT_SUPP;

        case MLX5_CMD_STAT_BAD_RES_ERR:
            return ME_REG_ACCESS_RES_NOT_AVLBL;

        case MLX5_CMD_STAT_RES_BUSY:
            return ME_REG_ACCESS_DEV_BUSY;

        case MLX5_CMD_STAT_NOT_READY:
            return ME_REG_ACCESS_NOT_READY;

        case MLX5_CMD_STAT_LIM_ERR:
            return ME_REG_ACCESS_SIZE_EXCEEDS_LIMIT;

        case MLX5_CMD_STAT_BAD_RES_STATE_ERR:
            return ME_REG_ACCESS_BAD_RES_STATE;

        case MLX5_CMD_STAT_IX_ERR:
            return ME_REG_ACCESS_BAD_INDEX;

        case MLX5_CMD_STAT_NO_RES_ERR:
            return ME_REG_ACCESS_RES_NOT_AVLBL;

        case MLX5_CMD_STAT_BAD_INP_LEN_ERR:
            return ME_REG_ACCESS_BAD_INPUT_LEN;

        case MLX5_CMD_STAT_BAD_OUTP_LEN_ERR:
            return ME_REG_ACCESS_BAD_OUTPUT_LEN;

        case MLX5_CMD_STAT_BAD_QP_STATE_ERR:
            return ME_REG_ACCESS_BAD_QP_STATE;

        case MLX5_CMD_STAT_BAD_PKT_ERR:
            return ME_REG_ACCESS_BAD_PKT;

        case MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR:
            return ME_REG_ACCESS_BAD_SIZE_OUTS_CQES;

        default:
            return ME_REG_ACCESS_UNKNOWN_ERR;
    }
}


int fwctl_control_access_register(int    fd,
                                  void  *data_in,
                                  int    size_in,
                                  __u16  reg_id,
                                  int    method,
                                  int   *reg_status,
                                  mfile* mf)
{
    int              outlen = MLX5_ST_SZ_BYTES(access_register_out) + size_in;
    int              inlen = MLX5_ST_SZ_BYTES(access_register_in) + size_in;
    struct fwctl_rpc rpc = {0};
    int              err = -ENOMEM;
    int              cmd_status;
    int              mnvda_reg_id = 0x9024;
    __aligned_u64   *out = NULL;
    __aligned_u64   *in = NULL;
    void            *data;

    in = malloc(inlen);
    out = malloc(outlen);
    if (!in || !out) {
        goto out;
    }

    memset(in, 0, inlen);
    memset(out, 0, outlen);

    rpc = (struct fwctl_rpc) {
        .size = sizeof(rpc),
        .scope = 3,
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
        FWCTL_DEBUG_PRINT(mf,"FWCTL_IOCTL_CMD_RPC ioctl() failed: err=%d, errno=%d (%s)\n", err, errno, strerror(errno));
        return err;
    }

    data = MLX5_ADDR_OF(access_register_out, out, register_data);
    memcpy(data_in, data, size_in);

    cmd_status = MLX5_GET(access_register_out, out, status);
    if (cmd_status) {
        u_int32_t syndrome = MLX5_GET(access_register_out, out, syndrome);
        mf->icmd.syndrome = syndrome;
        FWCTL_DEBUG_PRINT(mf, "FWCTL_IOCTL_CMD_RPC returned error from FW: reg_id=0x%x, method=0x%x, cmd_status=0x%x, syndrome=0x%x\n",
                          reg_id, method, cmd_status, syndrome);

        *reg_status = translate_cmd_status_to_reg_status(cmd_status);
        FWCTL_DEBUG_PRINT(mf, "Mapped FW cmd_status=0x%x to reg_status=0x%x (%s)\n", cmd_status, *reg_status, m_err2str(*reg_status));
    } else {
        *reg_status = 0;
        mf->icmd.syndrome = 0;
        FWCTL_DEBUG_PRINT(mf, "FWCTL_IOCTL_CMD_RPC succeeded: reg_id=0x%x, method=0x%x\n", reg_id, method);
    }

    FWCTL_DEBUG_PRINT(mf, "Final result: reg_id=0x%x, cmd_status=0x%x, reg_status=0x%x (%s)\n",
                      reg_id, cmd_status, *reg_status, m_err2str(*reg_status));
out:
    free(out);
    free(in);
    return err;
}


int mlx5u_fwctl_umem_reg(mfile* mf, void *addr, size_t len, uint32_t *umem_id, uint32_t *mkey_id)
{
	struct fwctl_rsc_umem_reg umem = { .size = sizeof(umem) };
	int ret;

	umem.addr = (uint64_t)addr;
	umem.len = len;
	umem.flags = FWCTL_UMEM_FLAG_MKEY | FWCTL_UMEM_FLAG_MCDD;
	FWCTL_DEBUG_PRINT(mf, "umem.addr %p umem.len %llu UMEM ID=0x%x\n", (void *)umem.addr, umem.len, umem.umem_id);
	ret = ioctl(mf->fd, FWCTL_RSC_UMEM_REG, &umem);
	if (ret) {
		FWCTL_DEBUG_PRINT(mf, "FWCTL_RSC_UMEM_REG failed: %d errno(%d): %s\n", ret, errno, strerror(errno));
		return ret > 0 ? -ret : ret;
	}
	FWCTL_DEBUG_PRINT(mf, "umem.addr reg success %p umem.len %llu UMEM ID=0x%x MKEY ID=0x%x\n", (void *)umem.addr, umem.len, umem.umem_id, umem.mkey_id);
	*umem_id = umem.umem_id;
	*mkey_id = umem.mkey_id;
	return umem.rsc_id;
}

struct mlx5_umem_buff* mlx5lib_alloc_umem_mkey_buff(mfile* mf, size_t size, int page_size)
{
	struct mlx5_umem_buff* umem_buff = NULL;
	int ret;

	umem_buff = malloc(sizeof(*umem_buff));
	if (!umem_buff) {
		FWCTL_DEBUG_PRINT(mf, "Failed to allocate umem_buff\n");
		return NULL;
	}
	memset(umem_buff, 0, sizeof(*umem_buff));

	umem_buff->size = size;
    void* buf = NULL;
	int rc = posix_memalign(&buf, (size_t)page_size, umem_buff->size);
	umem_buff->buff = buf;
    if (rc != 0 || !buf) {
        FWCTL_DEBUG_PRINT(mf, "posix_memalign failed: %d (%s)\n", rc, strerror(rc));
        free(umem_buff);
        return NULL;
    }
	if (!umem_buff->buff) {
		FWCTL_DEBUG_PRINT(mf, "memalign Failed with size %lu\n", umem_buff->size);
		free(umem_buff);
		return NULL;
	}
	memset(umem_buff->buff, 0, umem_buff->size);

	FWCTL_DEBUG_PRINT(mf, "Allocated umem buff %p Aligned to bytes %zu\n", umem_buff->buff, umem_buff->size);

	ret = mlx5u_fwctl_umem_reg(mf, umem_buff->buff, umem_buff->size, &umem_buff->umem_id, &umem_buff->umem_mkey);
	if (ret < 0) {
		FWCTL_DEBUG_PRINT(mf, "Failed to register umem buff %p, size %zu, err %d\n",
			umem_buff->buff, umem_buff->size, ret);
		free(umem_buff->buff);
		free(umem_buff);
		return NULL;
	}
	umem_buff->rsc_id = ret;
	FWCTL_DEBUG_PRINT(mf, "\tAllocated umem_id 0x%x mkey 0x%x for buff %p\n", umem_buff->umem_id, umem_buff->umem_mkey, umem_buff->buff);

	return umem_buff;
}

int mlx5u_fwctl_rsc_destroy(mfile* mf, uint32_t rsc_id)
{
	struct fwctl_rsc_destroy rsc_destroy = { .size = sizeof(rsc_destroy), .rsc_id = rsc_id };
	int ret;

	ret = ioctl(mf->fd, FWCTL_RSC_DESTROY, &rsc_destroy);
	if (ret) {
		FWCTL_DEBUG_PRINT(mf, "MLX5CTL_IOCTL_UMEM_UNREG failed: %d errno(%d): %s\n", ret, errno, strerror(errno));
		return ret;
	}
	FWCTL_DEBUG_PRINT(mf, "rsc_id unreg success 0x%x\n", rsc_id);
	return 0;
}

void mlx5lib_free_umem_mkey_buff(mfile* mf)
{
    struct mlx5_umem_buff* umem_buff = mf->umem_buff;
    if (umem_buff) {    // if umem_buff is not NULL, destroy the resource
        mlx5u_fwctl_rsc_destroy(mf, umem_buff->rsc_id);
        free(umem_buff->buff);
        free(umem_buff);
    }
}