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
 */
#include "certcontainerbase.h"
#include "mlxdpa_utils.h"
#include <mft_utils.h>
#include "baseHeader.h"
#include <iostream>

const map<BaseHeader::StructPriority, string> CertStructHeader::_metadataPriorityToString = {
  {BaseHeader::StructPriority::User, "USER"},
  {BaseHeader::StructPriority::Vendor, "OEM"},
  {BaseHeader::StructPriority::Nvidia, "NVIDIA"},
  {BaseHeader::StructPriority::Unknown, "UNKNOWN"}};

CertStructHeader::CertStructHeader() :
    BaseHeader(),
    _length(HEADER_SIZE),
    _type(StructType::Unknown),
    _version(0),
    _valid(0),
    _securityMethod(StructSecurityMethod::None),
    _crc(0x0)
{
}

CertStructHeader::CertStructHeader(BaseHeader::StructPriority priority, StructType type, u_int16_t structLength) :
    BaseHeader(priority),
    _length(HEADER_SIZE + structLength),
    _type(type),
    _version(0),
    _valid(0b10),
    _securityMethod(StructSecurityMethod::None),
    _crc(0x0)
{
    switch (_type)
    {
        case StructType::CertificateX509:
        case StructType::CacertMetadata:
        case StructType::Cacert:
        case StructType::CertChainMetadata:
        case StructType::CacertRemove:
        case StructType::CertChainRemove:
            _securityMethod = StructSecurityMethod::Crc16OfHeaderAndData;
            break;
        case StructType::Signature:
            _securityMethod = StructSecurityMethod::Crc16OfHeader;
            break;
        default:
            _securityMethod = StructSecurityMethod::None;
    }
}

BaseHeader::StructPriority CertStructHeader::GetPriorityNvidiaSignedOem(StructType type)
{
    switch (type)
    {
        case StructType::CertificateX509:
            return BaseHeader::StructPriority::Vendor;
        case StructType::CacertMetadata:
            return BaseHeader::StructPriority::Nvidia;
        case StructType::Signature:
            return BaseHeader::StructPriority::Nvidia;
        default:
            return BaseHeader::StructPriority::Unknown;
    }
}

bool CertStructHeader::ValidateNvidiaSignedOemPriority()
{
    BaseHeader::StructPriority priorityToCheck = GetPriorityNvidiaSignedOem(_type);
    return priorityToCheck == _priority;
}

vector<u_int8_t> CertStructHeader::Serialize()
{
    vector<u_int8_t> serializedData(HEADER_SIZE, 0x0);

    serializedData[0] = ((u_int8_t*)&_length)[0];
    serializedData[1] = ((u_int8_t*)&_length)[1];
    serializedData[2] = (u_int8_t)_type;
    serializedData[3] = _version;
    serializedData[3] |= ((u_int8_t)_priority << 4);
    serializedData[3] |= (_valid << 6);
    serializedData[7] = ((u_int8_t)_securityMethod << 4);
    serializedData[8] = ((u_int8_t*)&_crc)[0];
    serializedData[9] = ((u_int8_t*)&_crc)[1];

    return serializedData;
}

bool CertStructHeader::Deserialize(vector<u_int8_t>::const_iterator begin, vector<u_int8_t>::const_iterator end)
{
    if (end - begin != HEADER_SIZE)
    {
        return false;
    }

    _version = (*begin & 0x0F);
    _priority = BaseHeader::StructPriority((*begin >> 4) & 0x03);
    _valid = ((*begin >> 6) & 0x03);

    begin++;
    _type = CertStructHeader::StructType(*begin);

    begin++;
    _length = __cpu_to_be16(*(reinterpret_cast<const u_int16_t*>(&(*begin))));

    begin += 2;
    _securityMethod = CertStructHeader::StructSecurityMethod((*begin >> 4) & 0x0F);

    begin += 4;
     _crc = __cpu_to_be16(*(reinterpret_cast<const u_int16_t*>(&(*begin))));

    return true;
}

bool CertStructHeader::Deserialize(vector<u_int8_t> header)
{
    return Deserialize(header.cbegin(), header.cend());
}

CertContainerItem::CertContainerItem(BaseHeader::StructPriority priority, shared_ptr<CertStructBase> data) :
    _header(priority, data->GetType(), data->GetSize()), _metadata(data)
{
}

vector<u_int8_t> CertContainerItem::Serialize(bool toBigEndian)
{
    vector<u_int8_t> serializedData = _header.Serialize();
    vector<u_int8_t> structData = _metadata->Serialize();

    if (toBigEndian)
    {
        CPUTOn(serializedData.data(), serializedData.size() / 4);
        if (_metadata->GetType() != CertStructHeader::StructType::Signature &&
            _metadata->GetType() != CertStructHeader::StructType::CertificateX509)
        {
            CPUTOn(structData.data(), structData.size() / 4);
        }
    }

    serializedData.insert(serializedData.end(), structData.cbegin(), structData.cend());

    return serializedData;
}

vector<u_int8_t> CertStructBase::GetCertUUID()
{
    throw CertException("-E- Failed does not support GetCertUUID.");
}

vector<u_int8_t> CertStructBase::GetKeypairUUID()
{
    throw CertException("-E- Failed does not support GetKeypairUUID.");
}

u_int8_t CertStructBase::GetTargetingType()
{
    throw CertException("-E- Failed does not support GetTargetingType.");
}

u_int8_t CertStructBase::GetDpaRotEn()
{
    throw CertException("-E- Failed does not support GetDpaRotEn.");
}
