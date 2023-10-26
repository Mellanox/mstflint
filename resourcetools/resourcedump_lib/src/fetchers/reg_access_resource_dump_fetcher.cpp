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

#include "reg_access_resource_dump_fetcher.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"

#include "reg_access/reg_access.h"

#include <common/compatibility.h>

#include <fstream>

namespace mft
{
namespace resource_dump
{
namespace fetchers
{
using namespace std;

RegAccessResourceDumpFetcher::RegAccessResourceDumpFetcher(mfile_t* mfile,
                                                           device_attributes device_attrs,
                                                           dump_request segment_params,
                                                           uint32_t depth) :
    _mf{mfile}, _vhca{device_attrs.vhca}, _segment_params{0, 0, {0, 0, 0, 0}}, _depth{depth}
{
    if (!_mf)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::OPEN_DEVICE_FAILED);
    }

    //_segment_params fields are set after initialization because the struct is different(by include) between big/little
    // endian host
    _segment_params.reference_segment_type = segment_params.resource_id;
    _segment_params.segment_params.index1 = segment_params.index1;
    _segment_params.segment_params.index2 = segment_params.index2;
    _segment_params.segment_params.num_of_obj1 = segment_params.num_of_obj1;
    _segment_params.segment_params.num_of_obj2 = segment_params.num_of_obj2;
}

void RegAccessResourceDumpFetcher::set_streams(shared_ptr<ostream> os, shared_ptr<istream> is)
{
    _ostream = os;
    _istream = is;
}

void RegAccessResourceDumpFetcher::enable_streams_exceptions()
{
    _orig_os_exceptions = _ostream->exceptions();
    _orig_is_exceptions = _istream->exceptions();
    _ostream->exceptions(iostream::badbit | iostream::failbit);
    _istream->exceptions(iostream::badbit | iostream::failbit);
}

void RegAccessResourceDumpFetcher::restore_streams_exceptions()
{
    _ostream->exceptions(_orig_os_exceptions);
    _istream->exceptions(_orig_is_exceptions);
}

void RegAccessResourceDumpFetcher::fetch_data()
{
    if (!_istream || !_ostream)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::DATA_NOT_FETCHED);
    }

    enable_streams_exceptions();

    retrieve_from_reg_access();

    resource_dump_segment_header header_buffer{0};

    uint32_t level{0};
    uint32_t prev_level_refs{1};
    uint32_t curr_level_refs{0};

    try
    {
        while (level < _depth && _ostream->tellp() - _istream->tellg() > 0)
        {
            _istream->read(reinterpret_cast<char*>(&header_buffer), sizeof(resource_dump_segment_header));

            if (header_buffer.segment_type == static_cast<uint16_t>(SegmentType::reference))
            {
                _istream->read(reinterpret_cast<char*>(&_segment_params), sizeof(reference_segment_data));
                retrieve_from_reg_access();
                ++curr_level_refs;
            }
            else
            {
                _istream->seekg(calculate_segment_data_size(header_buffer.length_dw), istream::cur);
                if (header_buffer.segment_type == static_cast<uint16_t>(SegmentType::terminate))
                {
                    if (--prev_level_refs == 0)
                    {
                        ++level;
                        prev_level_refs = curr_level_refs;
                        curr_level_refs = 0;
                    }
                }
            }
        }
    }
    catch (const istream::failure& e)
    {
        if (_istream->eof())
        {
            throw ResourceDumpException(ResourceDumpException::Reason::SEGMENT_DATA_TOO_SHORT);
        }
    }

    restore_streams_exceptions();
}

void RegAccessResourceDumpFetcher::retrieve_from_reg_access()
{
    init_reg_access_layout();

    do
    {
        reg_access_status_t res = reg_access_res_dump(_mf, REG_ACCESS_METHOD_GET, &_reg_access_layout);
        if (res != ME_REG_ACCESS_OK)
        {
            throw ResourceDumpException(ResourceDumpException::Reason::SEND_REG_ACCESS_FAILED, res);
        }

        // May throw ios::failure
        write_payload_data_to_ostream();

        validate_reply();
        reset_reg_access_layout();
    } while (_reg_access_layout.more_dump);
}

void RegAccessResourceDumpFetcher::init_reg_access_layout()
{
    _reg_access_layout = {
      _segment_params.reference_segment_type,     // segment_type
      _current_seq_num,                           // seq_num
      0,                                          // vhca_id_valid
      1,                                          // inline_dump
      0,                                          // more_dump
      0,                                          // vhca_id
      _segment_params.segment_params.index1,      // index1
      _segment_params.segment_params.index2,      // index2
      _segment_params.segment_params.num_of_obj2, // num_of_obj2
      _segment_params.segment_params.num_of_obj1, // num_of_obj1
      0,                                          // device_opaque
      0,                                          // mkey
      0,                                          // size
      0,                                          // address
      {0}                                         // inline_data
    };

    if (_vhca != DEFAULT_VHCA)
    {
        _reg_access_layout.vhca_id = _vhca;
        _reg_access_layout.vhca_id_valid = 1;
    }
}

void RegAccessResourceDumpFetcher::validate_reply()
{
    if ((++_current_seq_num) % 16 != _reg_access_layout.seq_num)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::WRONG_SEQUENCE_NUMBER);
    }
}

void RegAccessResourceDumpFetcher::reset_reg_access_layout()
{
    _reg_access_layout.segment_type = _segment_params.reference_segment_type;
    _reg_access_layout.vhca_id = _vhca != DEFAULT_VHCA ? _vhca : 0;
    _reg_access_layout.vhca_id_valid = _vhca != DEFAULT_VHCA ? 1 : 0;
    _reg_access_layout.inline_dump = 1;
    _reg_access_layout.mkey = 0;
    _reg_access_layout.size = 0;
    _reg_access_layout.address = 0;
}

void RegAccessResourceDumpFetcher::write_payload_data_to_ostream()
{
    if (_reg_access_layout.size > NUM_INLINE_DATA_DWORDS * 4)
    {
        throw ResourceDumpException(ResourceDumpException::Reason::REGISTER_DATA_SIZE_TOO_LONG);
    }
    _ostream->write(reinterpret_cast<const char*>(_reg_access_layout.inline_data), _reg_access_layout.size);
    return;
}

uint32_t RegAccessResourceDumpFetcher::calculate_segment_data_size(uint16_t full_size_dw)
{
    return full_size_dw * 4 - sizeof(resource_dump_segment_header);
}

} // namespace fetchers
} // namespace resource_dump
} // namespace mft
