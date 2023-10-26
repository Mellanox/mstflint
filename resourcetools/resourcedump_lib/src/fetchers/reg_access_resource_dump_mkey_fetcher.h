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

#ifndef RESOURCE_DUMP_REGACCESS_RESDUMP_MKEY_H
#define RESOURCE_DUMP_REGACCESS_RESDUMP_MKEY_H

#include "reg_access_resource_dump_fetcher.h"

#include <infiniband/verbs.h>
#include <infiniband/mlx5dv.h>

#include <iostream>
#include <memory>

struct mfile_t;

namespace mft
{
namespace resource_dump
{
struct dump_request;
namespace fetchers
{
class RegAccessResourceDumpMkeyFetcher : public RegAccessResourceDumpFetcher
{
public:
    RegAccessResourceDumpMkeyFetcher(mfile_t* mfile,
                                     device_attributes device_attrs,
                                     dump_request segment_params,
                                     uint32_t depth = (uint32_t)-1);

    ~RegAccessResourceDumpMkeyFetcher();

    static const uint32_t BUFF_SIZE;

private:
    void init_reg_access_layout() override;

    void reset_reg_access_layout() override;

    void write_payload_data_to_ostream() override;

    static const uint16_t MLX5_CMD_OP_CREATE_MKEY;
    static const uint16_t MLX5_CMD_OP_DESTROY_MKEY;
    struct mlx5_ifc_mkc_bits
    {
        uint8_t reserved_at_0[0x1];
        uint8_t free[0x1];
        uint8_t reserved_at_2[0x1];
        uint8_t access_mode_4_2[0x3];
        uint8_t reserved_at_6[0x7];
        uint8_t relaxed_ordering_write[0x1];
        uint8_t reserved_at_e[0x1];
        uint8_t small_fence_on_rdma_read_response[0x1];
        uint8_t umr_en[0x1];
        uint8_t a[0x1];
        uint8_t rw[0x1];
        uint8_t rr[0x1];
        uint8_t lw[0x1];
        uint8_t lr[0x1];
        uint8_t access_mode_1_0[0x2];
        uint8_t reserved_at_18[0x8];

        uint8_t qpn[0x18];
        uint8_t mkey_7_0[0x8];

        uint8_t reserved_at_40[0x20];

        uint8_t length64[0x1];
        uint8_t bsf_en[0x1];
        uint8_t sync_umr[0x1];
        uint8_t reserved_at_63[0x2];
        uint8_t expected_sigerr_count[0x1];
        uint8_t reserved_at_66[0x1];
        uint8_t en_rinval[0x1];
        uint8_t pd[0x18];

        uint8_t start_addr[0x40];

        uint8_t len[0x40];

        uint8_t bsf_octword_size[0x20];

        uint8_t reserved_at_120[0x80];

        uint8_t translations_octword_size[0x20];

        uint8_t reserved_at_1c0[0x19];
        uint8_t relaxed_ordering_read[0x1];
        uint8_t reserved_at_1d9[0x1];
        uint8_t log_page_size[0x5];

        uint8_t reserved_at_1e0[0x3];
        uint8_t crypto_en[0x2];
        uint8_t reserved_at_1e5[0x1b];
    };

    struct mlx5_ifc_create_mkey_in_bits
    {
        uint8_t opcode[0x10];
        uint8_t reserved_at_10[0x10];

        uint8_t reserved_at_20[0x10];
        uint8_t op_mod[0x10];

        uint8_t reserved_at_40[0x20];

        uint8_t pg_access[0x1];
        uint8_t mkey_umem_valid[0x1];
        uint8_t reserved_at_62[0x1e];

        struct mlx5_ifc_mkc_bits memory_key_mkey_entry;

        uint8_t reserved_at_280[0x80];

        uint8_t translations_octword_actual_size[0x20];

        uint8_t mkey_umem_id[0x20];

        uint8_t mkey_umem_offset[0x40];

        uint8_t reserved_at_320[0x500];

        uint8_t klm_pas_mtt[0][0x20];
    };

    struct mlx5_ifc_create_mkey_out_bits
    {
        uint8_t status[0x8];
        uint8_t reserved_at_8[0x18];

        uint8_t syndrome[0x20];

        uint8_t reserved_at_40[0x8];
        uint8_t mkey_index[0x18];

        uint8_t reserved_at_60[0x20];
    };

    // ####### Weird code copied from OFED team. Need to understand if there's another way
    struct mlx5_pd
    {
        ibv_pd ibv_pd_obj;
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

    inline mlx5_pd* to_mpd(ibv_pd* ibpd)
    {
        mlx5_pd* mpd = (struct mlx5_pd*)((char*)ibpd - __builtin_offsetof(struct mlx5_pd, ibv_pd_obj));
        return mpd->mprotection_domain ? mpd->mprotection_domain : mpd;
    }
    // #######

    static uint32_t calculate_aligned_buffer_size(uint32_t align);

    void init_ibv_context(const string rdma_name);
    void init_umem(uint32_t page_size);
    void init_mkey();
    uint64_t get_umem_address() { return reinterpret_cast<uint64_t>(_mkey_buffer); }

    ibv_context* _ibv_context{nullptr};
    ibv_pd* _pd{nullptr};
    void* _mkey_buffer{nullptr};
    mlx5dv_devx_umem* _umem{nullptr};
    mlx5dv_devx_obj* _mkey_obj{nullptr};
    mlx5dv_mkey _dv_mkey{0, 0};
    uint32_t _umem_size{0};
};

} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_REGACCESS_RESDUMP_MKEY_H
