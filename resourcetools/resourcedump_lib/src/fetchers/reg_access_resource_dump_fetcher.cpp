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
#include "reg_access/reg_ids.h"
#include "mft_core/device/device_info/device_properties_api.h"
#include "dev_mgt/tools_dev_types.h"

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

    init_by_device();
}

/*********************** ATTENTION *********************************************/
/* Additional development of this function is discouraged. *********************/
/* We thrive to have a single resource dump register for all types of devices. */
/*******************************************************************************/
void RegAccessResourceDumpFetcher::init_by_device()
{
    dm_dev_id_t dev_id = DeviceUnknown;
    u_int32_t hw_id = 0, hw_rev = 0;
    dm_get_device_id(_mf, &dev_id, &hw_id, &hw_rev);

    const char* device_type = get_property_as_cstring(_mf->functional_device_id, PROP_DEVICE_TYPE);
    if (device_type[0] == '\0')
    {
        throw ResourceDumpException(ResourceDumpException::Reason::DEVICE_TYPE_UNSUPPORTED);
    }

    if (dm_is_gpu(dev_id))
    {
        _reg_handler.reset(new MordV2ResourceDumpRegister(_mf));
    }
    else if (dm_dev_is_hca(dev_id))
    {
        _reg_handler.reset(new BasicResourceDumpRegister(REG_ID_RES_DUMP));
    }
    else
    {
        _reg_handler.reset(new BasicResourceDumpRegister(REG_ID_MORD));
    }
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

    resource_dump_segment_header header_buffer{0, 0};

    uint32_t level{0};
    uint32_t prev_level_refs{1};
    uint32_t curr_level_refs{0};

    try
    {
        while (level < _depth && _ostream->tellp() - _istream->tellg() > 0)
        {
            _istream->read(reinterpret_cast<char*>(&header_buffer), sizeof(resource_dump_segment_header));
            if (header_buffer.length_dw * 4 < sizeof(resource_dump_segment_header))
            {
                throw ResourceDumpException(ResourceDumpException::Reason::SEGMENT_DATA_TOO_SHORT);
            }
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
        if (_istream->fail())
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
        reg_access_status_t res = _reg_handler->send(_mf);
        if (res != ME_REG_ACCESS_OK)
        {
            throw ResourceDumpException(ResourceDumpException::Reason::SEND_REG_ACCESS_FAILED, res);
        }

        // May throw ios::failure
        write_payload_data_to_ostream();

        validate_reply();
        reset_reg_access_layout();
    } while (_reg_handler->more_dump());
}

void RegAccessResourceDumpFetcher::init_reg_access_layout()
{
    _reg_handler->init(_segment_params, _current_seq_num, _vhca);
}

void RegAccessResourceDumpFetcher::reset_reg_access_layout()
{
    _reg_handler->reset(_segment_params, _vhca);
}

void RegAccessResourceDumpFetcher::validate_reply()
{
    if ((++_current_seq_num) % 16 != _reg_handler->seq_num())
    {
        throw ResourceDumpException(ResourceDumpException::Reason::WRONG_SEQUENCE_NUMBER);
    }
}

void RegAccessResourceDumpFetcher::write_payload_data_to_ostream()
{
    _reg_handler->write_payload(*_ostream);
}

uint32_t RegAccessResourceDumpFetcher::calculate_segment_data_size(uint16_t full_size_dw)
{
    return full_size_dw * 4 - sizeof(resource_dump_segment_header);
}

} // namespace fetchers
} // namespace resource_dump
} // namespace mft
