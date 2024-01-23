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

#include "reg_access_resource_dump_mkey_fetcher.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"

#include "reg_access/reg_access.h"
#include <mtcr.h>
#include "adb_to_c_utils.h"

#include <common/compatibility.h>

#include <fstream>
#include <memory>
#include <unistd.h>

namespace mft
{
namespace resource_dump
{
namespace fetchers
{
using namespace std;

const uint32_t RegAccessResourceDumpMkeyFetcher::BUFF_SIZE{32 * 1024 * 1024};
const uint16_t RegAccessResourceDumpMkeyFetcher::MLX5_CMD_OP_CREATE_MKEY{0x200};
const uint16_t RegAccessResourceDumpMkeyFetcher::MLX5_CMD_OP_DESTROY_MKEY{0x202};

RegAccessResourceDumpMkeyFetcher::RegAccessResourceDumpMkeyFetcher(mfile_t* mfile,
                                                                   device_attributes device_attrs,
                                                                   dump_request segment_params,
                                                                   uint32_t depth) :
    RegAccessResourceDumpFetcher{mfile, device_attrs, segment_params, depth}
{
    init_ibv_context(device_attrs.rdma_name);
    _pd = ibv_alloc_pd(_ibv_context);

    if (!_pd)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::MKEY_FETCHER_ALLOC_PD_FAILED);
    }

    auto page_size = sysconf(_SC_PAGESIZE);

    _umem_size = calculate_aligned_buffer_size(page_size);

    _mkey_buffer = aligned_alloc(page_size, _umem_size);
    if (!_mkey_buffer)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::MKEY_ALLIGNED_ALLOC_FAILED);
    }
    memset(_mkey_buffer, 0, _umem_size);

    init_umem(page_size);
    init_mkey();
}

RegAccessResourceDumpMkeyFetcher::~RegAccessResourceDumpMkeyFetcher()
{
    if (_mkey_obj)
    {
        mlx5dv_devx_obj_destroy(_mkey_obj);
    }
    if (_umem)
    {
        mlx5dv_devx_umem_dereg(_umem);
    }
    if (_mkey_buffer)
    {
        free(_mkey_buffer);
    }
    if (_pd)
    {
        ibv_dealloc_pd(_pd);
    }
    if (_ibv_context)
    {
        ibv_close_device(_ibv_context);
    }
}

void RegAccessResourceDumpMkeyFetcher::init_reg_access_layout()
{
    _reg_access_layout = {
      _segment_params.reference_segment_type,     // segment_type
      _current_seq_num,                           // seq_num
      0,                                          // vhca_id_valid
      0,                                          // inline_dump
      0,                                          // more_dump
      0,                                          // vhca_id
      _segment_params.segment_params.index1,      // index1
      _segment_params.segment_params.index2,      // index2
      _segment_params.segment_params.num_of_obj2, // num_of_obj2
      _segment_params.segment_params.num_of_obj1, // num_of_obj1
      0,                                          // device_opaque
      _dv_mkey.lkey,                              // mkey
      _umem_size,                                 // size
      get_umem_address(),                         // address
      0                                           // inline_data
    };

    if (_vhca != DEFAULT_VHCA)
    {
        _reg_access_layout.vhca_id = _vhca;
        _reg_access_layout.vhca_id_valid = 1;
    }
}

void RegAccessResourceDumpMkeyFetcher::reset_reg_access_layout()
{
    _reg_access_layout.segment_type = _segment_params.reference_segment_type;
    _reg_access_layout.vhca_id = _vhca != DEFAULT_VHCA ? _vhca : 0;
    _reg_access_layout.vhca_id_valid = _vhca != DEFAULT_VHCA ? 1 : 0;
    _reg_access_layout.inline_dump = 0;
    _reg_access_layout.mkey = _dv_mkey.lkey;
    _reg_access_layout.size = _umem_size;
    _reg_access_layout.address = get_umem_address();
}

void RegAccessResourceDumpMkeyFetcher::write_payload_data_to_ostream()
{
    for (size_t i = 0; i < _reg_access_layout.size / 4; ++i)
    {
        auto offset = adb2c_calc_array_field_address(0, 32, i, _reg_access_layout.size, 1);
        auto dword = adb2c_pop_integer_from_buff(static_cast<const uint8_t*>(_mkey_buffer), offset, 4);
        _ostream->write(reinterpret_cast<const char*>(&dword), 4);
    }
}

void RegAccessResourceDumpMkeyFetcher::init_ibv_context(const string rdma_name)
{
    struct ibv_device** ibv_device_list = NULL;
    int num_ibv_devices = 0;
    int i = 0;
    struct mlx5dv_context_attr* my_context_attr;
    my_context_attr = (struct mlx5dv_context_attr*)malloc(sizeof(struct mlx5dv_context_attr));
    memset(my_context_attr, 0, sizeof(struct mlx5dv_context_attr));

    my_context_attr->flags = MLX5DV_CONTEXT_FLAGS_DEVX;
    my_context_attr->comp_mask = 0;

    char device_rdma_name_buffer[32];
    memset(device_rdma_name_buffer, 0, 32);

    try
    {
        if (rdma_name == AUTO_RDMA_NAME)
        {
            get_pci_dev_rdma(_mf, device_rdma_name_buffer);
        }
        else
        {
            strncpy(device_rdma_name_buffer, rdma_name.c_str(), 31);
        }
        ibv_device_list = ibv_get_device_list(&num_ibv_devices);

        if (!ibv_device_list)
        {
            throw ResourceDumpException(ResourceDumpException::Reason::MKEY_FETCHER_GET_DEVICE_LIST_FAILED);
        }
        for (i = 0; i < num_ibv_devices; ++i)
        {
            if (ibv_device_list[i] != NULL &&
                strcmp(ibv_get_device_name(ibv_device_list[i]), device_rdma_name_buffer) == 0)
            {
                _ibv_context = mlx5dv_open_device(ibv_device_list[i], my_context_attr);
                if (!_ibv_context)
                {
                    throw ResourceDumpException(ResourceDumpException::Reason::MKEY_FETCHER_MLX5DV_OPEN_FAILED);
                }
                break;
            }
        }
        if (!_ibv_context)
        {
            throw ResourceDumpException(ResourceDumpException::Reason::MKEY_FETCHER_RDMA_NAME_INVALID);
        }
    }
    catch (...)
    {
        if (my_context_attr)
        {
            free(my_context_attr);
        }
        if (ibv_device_list)
        {
            ibv_free_device_list(ibv_device_list);
        }
        throw;
    }
    free(my_context_attr);
    ibv_free_device_list(ibv_device_list);
    return;
}

void RegAccessResourceDumpMkeyFetcher::init_umem(uint32_t page_size)
{
    auto umem_in = new mlx5dv_devx_umem_in;
    memset(umem_in, 0, sizeof(mlx5dv_devx_umem_in));

    umem_in->addr = _mkey_buffer;
    umem_in->size = _umem_size;
    umem_in->access = IBV_ACCESS_LOCAL_WRITE;
    umem_in->pgsz_bitmap = page_size;
    _umem = mlx5dv_devx_umem_reg_ex(_ibv_context, umem_in);

    if (!_umem)
    {
        delete umem_in;
        throw ResourceDumpException(ResourceDumpException::Reason::MKEY_UMEM_REG_FAILED);
    }

    delete umem_in;
}

void RegAccessResourceDumpMkeyFetcher::init_mkey()
{
    uint32_t out[DEVX_ST_SZ_DW(create_mkey_out)] = {};
    uint32_t in[DEVX_ST_SZ_DW(create_mkey_in)] = {};
    void* mkc;
    auto pdn = to_mpd(_pd)->pdn;

    DEVX_SET(create_mkey_in, in, opcode, MLX5_CMD_OP_CREATE_MKEY);
    mkc = DEVX_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
    DEVX_SET(mkc, mkc, access_mode_1_0, 0x1);
    DEVX_SET(mkc, mkc, umr_en, 0);
    DEVX_SET(mkc, mkc, pd, pdn);
    DEVX_SET(mkc, mkc, lr, 1);
    DEVX_SET(mkc, mkc, lw, 1);
    DEVX_SET(mkc, mkc, qpn, 0xffffff);
    DEVX_SET64(mkc, mkc, start_addr, reinterpret_cast<uint64_t>(_mkey_buffer));
    DEVX_SET64(mkc, mkc, len, _umem_size);

    DEVX_SET(create_mkey_in, in, mkey_umem_valid, 1);
    DEVX_SET(create_mkey_in, in, mkey_umem_id, _umem->umem_id);

    _mkey_obj = mlx5dv_devx_obj_create(_ibv_context, in, sizeof(in), out, sizeof(out));

    if (!_mkey_obj)
    {
        printf("mlx5dv_devx_obj_create failed\n"); // TODO: remove these printfs by enhancing error mechanism and add
                                                   // minor error
        printf("status: %u\n", DEVX_GET(create_mkey_out, out, status));
        printf("syndrome: %u\n", DEVX_GET(create_mkey_out, out, syndrome));
        throw ResourceDumpException(ResourceDumpException::Reason::DEVX_OBJ_CREATE_FAILED);
    }

    _dv_mkey.lkey = (DEVX_GET(create_mkey_out, out, mkey_index) << 8) | 0;
    _dv_mkey.rkey = _dv_mkey.lkey;
}

uint32_t RegAccessResourceDumpMkeyFetcher::calculate_aligned_buffer_size(uint32_t align)
{
    return (BUFF_SIZE + align - 1) & ~(align - 1);
}

} // namespace fetchers
} // namespace resource_dump
} // namespace mft
