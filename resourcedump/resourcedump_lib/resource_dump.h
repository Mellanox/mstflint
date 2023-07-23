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
#define u8 uint8_t

static inline unsigned long align(unsigned long val, unsigned long align)
{
    return (val + align - 1) & ~(align - 1);
}

struct mlx5_ifc_mkc_bits
{
    u8 reserved_at_0[0x1];
    u8 free[0x1];
    u8 reserved_at_2[0x1];
    u8 access_mode_4_2[0x3];
    u8 reserved_at_6[0x7];
    u8 relaxed_ordering_write[0x1];
    u8 reserved_at_e[0x1];
    u8 small_fence_on_rdma_read_response[0x1];
    u8 umr_en[0x1];
    u8 a[0x1];
    u8 rw[0x1];
    u8 rr[0x1];
    u8 lw[0x1];
    u8 lr[0x1];
    u8 access_mode_1_0[0x2];
    u8 reserved_at_18[0x8];

    u8 qpn[0x18];
    u8 mkey_7_0[0x8];

    u8 reserved_at_40[0x20];

    u8 length64[0x1];
    u8 bsf_en[0x1];
    u8 sync_umr[0x1];
    u8 reserved_at_63[0x2];
    u8 expected_sigerr_count[0x1];
    u8 reserved_at_66[0x1];
    u8 en_rinval[0x1];
    u8 pd[0x18];

    u8 start_addr[0x40];

    u8 len[0x40];

    u8 bsf_octword_size[0x20];

    u8 reserved_at_120[0x80];

    u8 translations_octword_size[0x20];

    u8 reserved_at_1c0[0x19];
    u8 relaxed_ordering_read[0x1];
    u8 reserved_at_1d9[0x1];
    u8 log_page_size[0x5];

    u8 reserved_at_1e0[0x3];
    u8 crypto_en[0x2];
    u8 reserved_at_1e5[0x1b];
};

struct mlx5_ifc_create_mkey_out_bits
{
    u8 status[0x8];
    u8 reserved_at_8[0x18];

    u8 syndrome[0x20];

    u8 reserved_at_40[0x8];
    u8 mkey_index[0x18];

    u8 reserved_at_60[0x20];
};

struct mlx5_ifc_create_mkey_in_bits
{
    u8 opcode[0x10];
    u8 reserved_at_10[0x10];

    u8 reserved_at_20[0x10];
    u8 op_mod[0x10];

    u8 reserved_at_40[0x20];

    u8 pg_access[0x1];
    u8 mkey_umem_valid[0x1];
    u8 reserved_at_62[0x1e];

    struct mlx5_ifc_mkc_bits memory_key_mkey_entry;

    u8 reserved_at_280[0x80];

    u8 translations_octword_actual_size[0x20];

    u8 mkey_umem_id[0x20];

    u8 mkey_umem_offset[0x40];

    u8 reserved_at_320[0x500];

    u8 klm_pas_mtt[0][0x20];
};

struct mlx5_ifc_destroy_mkey_out_bits
{
    u8 status[0x8];
    u8 reserved_at_8[0x18];

    u8 syndrome[0x20];

    u8 reserved_at_40[0x40];
};

struct mlx5_ifc_destroy_mkey_in_bits
{
    u8 opcode[0x10];
    u8 uid[0x10];

    u8 reserved_at_20[0x10];
    u8 op_mod[0x10];

    u8 reserved_at_40[0x8];
    u8 mkey_index[0x18];

    u8 reserved_at_60[0x20];
};

#define BUFF_SIZE 32 * 1024 * 1024
#define MLX5_CMD_OP_CREATE_MKEY 0x200
#define MLX5_CMD_OP_DESTROY_MKEY 0x202
#define LIB_VERBS_LINUX_PATH "/usr/lib64/libibverbs.so"
#define LIB_VERBS_UBUNTU_PATH "/usr/lib/x86_64-linux-gnu/libibverbs.so"
#define LIB_VERBS_BLUEFIELD_PATH "/usr/lib/aarch64-linux-gnu/libibverbs.so"
#define LIB_VERBS_PPC64LE_PATH "/usr/lib/powerpc64le-linux-gnu/libibverbs.so"
#define LIB_MLX5_LINUX_PATH "/usr/lib64/libmlx5.so"
#define LIB_MLX5_UBUNTU_PATH "/usr/lib/x86_64-linux-gnu/libmlx5.so"
#define LIB_MLX5_BLUEFIELD_PATH "/usr/lib/aarch64-linux-gnu/libmlx5.so"
#define LIB_MLX5_PPC64LE_PATH "/usr/lib/powerpc64le-linux-gnu/libmlx5.so"
#define GET_DEVICE_LIST_FUNC "ibv_get_device_list"
#define GET_DEVICE_NAME_FUNC "ibv_get_device_name"
#define OPEN_DEVICE_FUNC "mlx5dv_open_device"
#define FREE_DEVICE_LIST "ibv_free_device_list"
#define OBJECT_CREATE "mlx5dv_devx_obj_create"
#define ALLOCATE_PD "ibv_alloc_pd"
#define UMEM_REG "mlx5dv_devx_umem_reg_ex"
#define CLOSE_DEVICE "ibv_close_device"
#define DEALLOCATE_PD "ibv_dealloc_pd"
#define UMEM_DEREG "mlx5dv_devx_umem_dereg"

typedef struct ibv_pd* (*f_ibv_alloc_pd)(struct ibv_context*);
typedef int (*f_ibv_close_device)(struct ibv_context*);
typedef struct ibv_device** (*f_ibv_get_device_list)(int*);
typedef void (*f_ibv_free_device_list)(struct ibv_device**);
typedef const char* (*f_ibv_get_device_name)(struct ibv_device*);
typedef struct ibv_context* (*f_mlx5dv_open_device)(struct ibv_device*, struct mlx5dv_context_attr*);
typedef int (*f_mlx5dv_devx_umem_dereg)(struct mlx5dv_devx_umem*);
typedef int (*f_ibv_dealloc_pd)(struct ibv_pd* pd);
typedef struct mlx5dv_devx_umem* (*f_mlx5dv_devx_umem_reg)(struct ibv_context* context,
                                                           void* addr,
                                                           size_t size,
                                                           uint32_t access);
typedef struct mlx5dv_devx_umem* (*f_mlx5dv_devx_umem_reg_ex)(struct ibv_context* ctx,
                                                              struct mlx5dv_devx_umem_in* umem_in);

typedef struct mlx5dv_devx_obj* (
  *f_mlx5dv_devx_obj_create)(struct ibv_context*, uint32_t in[], uint32_t in_size, uint32_t out[], uint32_t out_size);
struct reg_access_info
{
    u_int16_t segment_type;
    u_int8_t seq_num;
    u_int8_t vhca_id_valid;
    u_int8_t inline_dump;
    u_int8_t more_dump;
    u_int16_t vhca_id;
    u_int32_t index1;
    u_int32_t index2;
    u_int16_t num_of_obj2;
    u_int16_t num_of_obj1;
    u_int64_t device_opaque;
    u_int32_t mkey;
    u_int32_t size;
    u_int64_t address;
    u_int32_t inline_data[52];
};

struct mlx5_pd
{
    struct ibv_pd ibv_pd;
    uint32_t pdn;
    int refcount;
    struct mlx5_pd* mprotection_domain;
    struct
    {
        void* opaque_buf;
        struct ibv_mr* opaque_mr;
        pthread_mutex_t opaque_mr_mutex;
    };
};

struct mlx5_mkey
{
    struct mlx5dv_mkey dv_mkey;
    struct mlx5dv_devx_obj* devx_obj;
    uint16_t num_desc;
    uint64_t length;
    struct mlx5_sig_ctx* sig;
    struct mlx5_crypto_attr* crypto;
};

struct result
{
    uint32_t lkey;
    uint64_t umem_addr;
    uint32_t umem_size;
};

struct extract
{
    uint32_t val;
};

struct chars
{
    uint8_t char_val;
};

struct extractall
{
    struct chars* char_vals;
};
