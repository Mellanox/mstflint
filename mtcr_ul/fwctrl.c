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
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include "common/compatibility.h"
#include "mtcr.h"
#include "mtcr_mf.h"
#include "mtcr_ul_com.h"
#include "fwctrl.h"
#include "fwctrl_ioctl.h"


void fwctl_set_device_id(mfile* mf)
{
    unsigned char register_data[1024];
    int           reg_status =0;

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
        .scope = (method == FWCTL_METHOD_READ) ? FWCTL_RPC_DEBUG_READ_ONLY
                                               : FWCTL_RPC_DEBUG_WRITE_FULL,
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
        goto out;
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
/* HCA capability query/set over fwctl (ported from MFT for the mstflint SDK). */
const char* mlx5_cmd_status_str(uint8_t status)
{
    switch (status)
    {
        case MLX5_CMD_STAT_OK:
            return "OK";

        case MLX5_CMD_STAT_INT_ERR:
            return "internal error";

        case MLX5_CMD_STAT_BAD_OP_ERR:
            return "bad operation";

        case MLX5_CMD_STAT_BAD_PARAM_ERR:
            return "bad parameter";

        case MLX5_CMD_STAT_BAD_SYS_STATE_ERR:
            return "bad system state";

        case MLX5_CMD_STAT_BAD_RES_ERR:
            return "bad resource";

        case MLX5_CMD_STAT_RES_BUSY:
            return "resource busy";

        case MLX5_CMD_STAT_NOT_READY:
            return "not ready, try again later";

        case MLX5_CMD_STAT_LIM_ERR:
            return "limits exceeded";

        case MLX5_CMD_STAT_BAD_RES_STATE_ERR:
            return "bad resource state";

        case MLX5_CMD_STAT_IX_ERR:
            return "bad index";

        case MLX5_CMD_STAT_NO_RES_ERR:
            return "no resources";

        case MLX5_CMD_STAT_BAD_INP_LEN_ERR:
            return "bad input length";

        case MLX5_CMD_STAT_BAD_OUTP_LEN_ERR:
            return "bad output length";

        case MLX5_CMD_STAT_BAD_QP_STATE_ERR:
            return "bad QP state";

        case MLX5_CMD_STAT_BAD_PKT_ERR:
            return "bad packet";

        case MLX5_CMD_STAT_BAD_SIZE_OUTS_CQES_ERR:
            return "bad size in outstanding CQEs";

        default:
            return "unknown FW command status";
    }
}

static uint16_t fwctl_hca_cap_op_mod(__u16 capability_type, capability_mode cap_mode)
{
    return (uint16_t)((capability_type << 1) | cap_mode);
}

typedef void (*fwctl_get_cap_status_fn)(void* out, uint8_t* status, uint32_t* syndrome);

static void get_query_hca_cap_status(void* out, uint8_t* status, uint32_t* syndrome)
{
    *status = MLX5_GET(query_hca_cap_out, out, status);
    *syndrome = MLX5_GET(query_hca_cap_out, out, syndrome);
}

static void get_set_hca_cap_status(void* out, uint8_t* status, uint32_t* syndrome)
{
    *status = MLX5_GET(set_hca_cap_out, out, status);
    *syndrome = MLX5_GET(set_hca_cap_out, out, syndrome);
}

static int fwctl_hca_cap_do_rpc(mfile* mf,
                                void* in,
                                size_t in_len,
                                void* out,
                                size_t out_len,
                                __u16 capability_type,
                                capability_mode cap_mode,
                                fwctl_get_cap_status_fn get_status)
{
    struct fwctl_rpc rpc = (struct fwctl_rpc){
      .size = sizeof(rpc),
      .scope = 0,
      .in_len = in_len,
      .out_len = out_len,
      .in = (uint64_t)(uintptr_t)in,
      .out = (uint64_t)(uintptr_t)out,
    };

    int err = ioctl(mf->fd, FWCTL_RPC, &rpc);
    if (err)
    {
        FWCTL_DEBUG_PRINT(mf, "FWCTL_IOCTL_CMD_RPC ioctl() failed: capability_type=0x%x, err=%d, errno=%d (%s)\n",
                          capability_type, err, errno, strerror(errno));
        return err;
    }

    uint8_t cmd_status = 0;
    uint32_t syndrome = 0;
    get_status(out, &cmd_status, &syndrome);

    if (cmd_status)
    {
        mf->icmd.syndrome = syndrome;
        FWCTL_DEBUG_PRINT(
          mf,
          "FWCTL_IOCTL_CMD_RPC returned error from FW: capability_type=0x%x, capability_mode=0x%x, cmd_status=0x%x, syndrome=0x%x\n",
          capability_type, cap_mode, cmd_status, syndrome);
        /* Return the raw FW command status; HCA cap is a general command, not a register access, so the
         * register-access status strings would be misleading. The syndrome is kept in mf->icmd.syndrome. */
        return cmd_status;
    }

    FWCTL_DEBUG_PRINT(mf, "FWCTL_IOCTL_CMD_RPC succeeded: capability_type=0x%x, capability_mode=0x%x\n",
                      capability_type, cap_mode);
    return MLX5_CMD_STAT_OK;
}

int fwctl_query_hca_capability(mfile* mf,
                               void* data_out,
                               unsigned int data_out_size,
                               __u16 capability_type,
                               capability_mode cap_mode,
                               __u16 function_id,
                               __u8 function_id_type,
                               __u8 other_function)
{
    uint32_t in[MLX5_ST_SZ_DW(query_hca_cap_in)] = {0};
    uint32_t out[MLX5_ST_SZ_DW(query_hca_cap_out)] = {0};
    uint16_t op_mod = fwctl_hca_cap_op_mod(capability_type, cap_mode);

    FWCTL_DEBUG_PRINT(mf, "op_mod = %x, function_id = %x, function_id_type = %x\n", op_mod, function_id,
                      function_id_type);
    MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
    MLX5_SET(query_hca_cap_in, in, op_mod, op_mod);
    MLX5_SET(query_hca_cap_in, in, function_id, function_id);
    MLX5_SET(query_hca_cap_in, in, function_id_type, function_id_type);
    MLX5_SET(query_hca_cap_in, in, other_function, other_function);

    int err =
      fwctl_hca_cap_do_rpc(mf, in, sizeof(in), out, sizeof(out), capability_type, cap_mode, get_query_hca_cap_status);
    if (err != MLX5_CMD_STAT_OK)
        return err;

    memcpy(data_out, MLX5_ADDR_OF(query_hca_cap_out, out, capability), data_out_size);
    return MLX5_CMD_STAT_OK;
}

int fwctl_set_hca_capability(mfile* mf,
                             void* data_in,
                             unsigned int data_in_size,
                             __u16 capability_type,
                             capability_mode cap_mode,
                             __u16 function_id,
                             __u8 function_id_type,
                             __u8 other_function)
{
    uint32_t in[MLX5_ST_SZ_DW(set_hca_cap_in)] = {0};
    uint32_t out[MLX5_ST_SZ_DW(set_hca_cap_out)] = {0};
    uint16_t op_mod = fwctl_hca_cap_op_mod(capability_type, cap_mode);

    FWCTL_DEBUG_PRINT(mf, "op_mod = %x, function_id = %x, function_id_type = %x\n", op_mod, function_id,
                      function_id_type);
    MLX5_SET(set_hca_cap_in, in, opcode, MLX5_CMD_OP_SET_HCA_CAP);
    MLX5_SET(set_hca_cap_in, in, op_mod, op_mod);
    MLX5_SET(set_hca_cap_in, in, function_id, function_id);
    MLX5_SET(set_hca_cap_in, in, function_id_type, function_id_type);
    MLX5_SET(set_hca_cap_in, in, other_function, other_function);

    memcpy(MLX5_ADDR_OF(set_hca_cap_in, in, capability), data_in, data_in_size);

    return fwctl_hca_cap_do_rpc(mf, in, sizeof(in), out, sizeof(out), capability_type, cap_mode,
                                get_set_hca_cap_status);
}
