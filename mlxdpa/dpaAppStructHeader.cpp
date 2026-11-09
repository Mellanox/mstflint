/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */
#include "dpaAppStructHeader.h"
#include "mlxdpa_utils.h"
#include "mft_utils/mft_utils.h"
#include <iostream>

DpaAppStructHeader::DpaAppStructHeader() :
    BaseHeader(StructPriority::Unknown),
    _length(0),
    _type(StructType::RESERVED),
    _version(0x0),
    _valid(StructValid::Free),
    _securityMethod(StructSecurityMethod::NO_AUTH)
{
    UpdateLength();
}
DpaAppStructHeader::DpaAppStructHeader(StructPriority priority, StructType type) :
    BaseHeader(priority),
    _length(0),
    _type(type),
    _version(0x0),
    _valid(StructValid::ValidData),
    _securityMethod(StructSecurityMethod::NO_AUTH)
{
    UpdateLength();
}

DpaAppStructHeader::DpaAppStructHeader(StructPriority priority, StructType type, u_int32_t length) :
    BaseHeader(priority),
    _length(length),
    _type(type),
    _version(0x0),
    _valid(StructValid::ValidData),
    _securityMethod(StructSecurityMethod::NO_AUTH)
{
    UpdateLength();
}

DpaAppStructHeader::DpaAppStructHeader(u_int32_t length,
                                       StructType type,
                                       StructPriority priority,
                                       StructSecurityMethod securityMethod,
                                       StructValid valid,
                                       u_int8_t version) :
    BaseHeader(priority), _length(length), _type(type), _version(version), _valid(valid), _securityMethod(securityMethod)
{
    UpdateLength();
}

void DpaAppStructHeader::UpdateLength()
{
    _length = _length + GetHeaderSize();
}

int DpaAppStructHeader::GetHeaderSize()
{
    if (_securityMethod == StructSecurityMethod::NO_AUTH || _securityMethod == StructSecurityMethod::ENC_PARAMS)
    {
        // the header size is 64 bit == 8 bytes
        return 8;
    }
    else
    {
        // the header size is 32 bit == 4 bytes
        return 4;
    }
}

vector<u_int8_t> DpaAppStructHeader::Serialize()
{
    int headerSize = GetHeaderSize();
    vector<u_int8_t> serializedData(headerSize, 0x0);
    serializedData[0] = (u_int8_t)(_securityMethod);
    serializedData[1] = 0x0;
    serializedData[2] = (u_int8_t)_type;
    serializedData[3] |= (u_int8_t)(_valid) << 6;        // only 2 used
    serializedData[3] |= (u_int8_t)(GetPriority()) << 4; // only 2 used
    serializedData[3] |= _version & 0x0F;                // only 4 used
    serializedData[4] = ((u_int8_t*)&_length)[0];
    serializedData[5] = ((u_int8_t*)&_length)[1];
    serializedData[6] = ((u_int8_t*)&_length)[2];
    serializedData[7] = ((u_int8_t*)&_length)[3];

    CPUTOn(serializedData.data(), serializedData.size() / 4);

    return serializedData;
}

std::string DpaAppStructHeader::TypeToString(StructType type)
{
    switch (type)
    {
        case StructType::DPA_ELF:
            return "DPA_ELF";
        case StructType::DPA_CRYPTO_BLOB:
            return "DPA_CRYPTO_BLOB";
        case StructType::DPA_APP_METADATA:
            return "DPA_APP_METADATA";
        case StructType::ENC_PARAMS:
            return "ENC_PARAMS";
        case StructType::DPA_APP:
            return "DPA_APP";
        case StructType::DPA_APP_REMOVE_METADATA:
            return "DPA_APP_REMOVE_METADATA";
        case StructType::SIGNATURE:
            return "SIGNATURE";
        case StructType::ENC_KEY:
            return "ENC_KEY";
        case StructType::DPA_APP_MANIFEST:
            return "DPA_APP_MANIFEST";
        default:
            return "RESERVED";
    }
}

bool DpaAppStructHeader::Deserialize(vector<u_int8_t>::const_iterator begin, vector<u_int8_t>::const_iterator end)
{
    if (std::distance(begin, end) != GetHeaderSize())
    {
        return false;
    }
    vector<u_int8_t> data(begin, end);
    CPUTOn(data.data(), data.size() / 4);

    _securityMethod = DpaAppStructHeader::StructSecurityMethod(data[0]);
    _type = DpaAppStructHeader::StructType(data[2]);
    u_int8_t byte3 = data[3];
    _valid = DpaAppStructHeader::StructValid((byte3 >> 6) & 0x03);
    _priority = BaseHeader::StructPriority((byte3 >> 4) & 0x03);
    _version = byte3 & 0x0F;
    _length = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);

    return true;
}

bool DpaAppStructHeader::Deserialize(vector<u_int8_t> header)
{
    return Deserialize(header.cbegin(), header.cend());
}

void DpaAppStructHeader::SetSecurityMethod(StructSecurityMethod securityMethod)
{
    _securityMethod = securityMethod;
}

void DpaAppStructHeader::SetValid(StructValid valid)
{
    _valid = valid;
}

void DpaAppStructHeader::SetValidData()
{
    _valid = StructValid::ValidData;
}

void DpaAppStructHeader::SetLength(u_int32_t length)
{
    _length = length;
}

void DpaAppStructHeader::SetVersion(u_int8_t version)
{
    _version = version;
}

void DpaAppStructHeader::SetType(StructType type)
{
    _type = type;
}