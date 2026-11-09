/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include "resource_dump_register.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"

#include "reg_access/reg_ids.h"
#include <mtcr.h>

namespace mft
{
namespace resource_dump
{
namespace fetchers
{
using namespace std;

BasicResourceDumpRegister::BasicResourceDumpRegister(uint16_t reg_id) : ResourceDumpRegister{reg_id} {}

void BasicResourceDumpRegister::init(const reference_segment_data& params,
                                     uint8_t seq_num,
                                     uint16_t vhca,
                                     bool inline_dump,
                                     uint32_t mkey,
                                     uint32_t size,
                                     uint64_t address)
{
    _layout = {
      params.reference_segment_type,         // segment_type
      seq_num,                               // seq_num
      0,                                     // vhca_id_valid
      inline_dump ? (uint8_t)1 : (uint8_t)0, // inline_dump
      0,                                     // more_dump
      0,                                     // vhca_id
      params.segment_params.index1,          // index1
      params.segment_params.index2,          // index2
      params.segment_params.num_of_obj2,     // num_of_obj2
      params.segment_params.num_of_obj1,     // num_of_obj1
      0,                                     // device_opaque
      mkey,                                  // mkey
      size,                                  // size
      address,                               // address
      {0}                                    // inline_data
    };

    if (vhca != DEFAULT_VHCA)
    {
        _layout.vhca_id = vhca;
        _layout.vhca_id_valid = 1;
    }
}

void BasicResourceDumpRegister::reset(const reference_segment_data& params,
                                      uint16_t vhca,
                                      bool inline_dump,
                                      uint32_t mkey,
                                      uint32_t size,
                                      uint64_t address)
{
    _layout.segment_type = params.reference_segment_type;
    _layout.vhca_id = vhca != DEFAULT_VHCA ? vhca : 0;
    _layout.vhca_id_valid = vhca != DEFAULT_VHCA ? 1 : 0;
    _layout.inline_dump = inline_dump ? 1 : 0;
    _layout.mkey = mkey;
    _layout.size = size;
    _layout.address = address;
}

reg_access_status_t BasicResourceDumpRegister::send(mfile_t* mf)
{
    auto reg_access_func = (_reg_id == REG_ID_RES_DUMP) ? reg_access_res_dump : reg_access_mord;
    return reg_access_func(mf, REG_ACCESS_METHOD_GET, &_layout);
}

void BasicResourceDumpRegister::write_payload(std::ostream& os) const
{
    if (_layout.size > NUM_INLINE_DATA_DWORDS * 4)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::REGISTER_DATA_SIZE_TOO_LONG);
    }
    os.write(reinterpret_cast<const char*>(_layout.inline_data), _layout.size);
}

MordV2ResourceDumpRegister::MordV2ResourceDumpRegister(mfile_t* mf) : ResourceDumpRegister{REG_ID_MORD_V2}
{
    unsigned int max_reg_size = mget_max_reg_size(mf, MACCESS_REG_METHOD_GET);
    unsigned int header_size = reg_access_switch_mord_v2_ext_size();

    if (max_reg_size <= header_size)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::BUFFER_TOO_SMALL);
    }

    _inline_dwords = (max_reg_size - header_size) / DWORD_SIZE;
    _inline_data.resize(_inline_dwords, 0);
}

void MordV2ResourceDumpRegister::init(const reference_segment_data& params,
                                      uint8_t seq_num,
                                      uint16_t vhca,
                                      bool inline_dump,
                                      uint32_t mkey,
                                      uint32_t size,
                                      uint64_t address)
{
    _layout = {
      params.reference_segment_type,         // segment_type
      seq_num,                               // seq_num
      0,                                     // vhca_id_valid
      inline_dump ? (uint8_t)1 : (uint8_t)0, // inline_dump
      0,                                     // more_dump
      0,                                     // vhca_id
      static_cast<uint16_t>(_inline_dwords), // data_size
      params.segment_params.index1,          // index1
      params.segment_params.index2,          // index2
      params.segment_params.num_of_obj2,     // num_of_obj2
      params.segment_params.num_of_obj1,     // num_of_obj1
      0,                                     // device_opaque
      mkey,                                  // mkey
      size,                                  // size
      address,                               // address
      _inline_data.data()                    // inline_data
    };

    if (vhca != DEFAULT_VHCA)
    {
        _layout.vhca_id = vhca;
        _layout.vhca_id_valid = 1;
    }
}

void MordV2ResourceDumpRegister::reset(const reference_segment_data& params,
                                       uint16_t vhca,
                                       bool inline_dump,
                                       uint32_t mkey,
                                       uint32_t size,
                                       uint64_t address)
{
    _layout.segment_type = params.reference_segment_type;
    _layout.vhca_id = vhca != DEFAULT_VHCA ? vhca : 0;
    _layout.vhca_id_valid = vhca != DEFAULT_VHCA ? 1 : 0;
    _layout.inline_dump = inline_dump ? 1 : 0;
    _layout.mkey = mkey;
    _layout.size = size;
    _layout.address = address;
    _layout.data_size = static_cast<uint16_t>(_inline_dwords);
    _layout.inline_data = _inline_data.data();
}

reg_access_status_t MordV2ResourceDumpRegister::send(mfile_t* mf)
{
    return reg_access_mord_v2(mf, REG_ACCESS_METHOD_GET, &_layout, static_cast<int>(_inline_dwords * DWORD_SIZE));
}

void MordV2ResourceDumpRegister::write_payload(std::ostream& os) const
{
    if (_layout.size > _inline_dwords * DWORD_SIZE)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::REGISTER_DATA_SIZE_TOO_LONG);
    }
    os.write(reinterpret_cast<const char*>(_inline_data.data()), _layout.size);
}

} // namespace fetchers
} // namespace resource_dump
} // namespace mft
