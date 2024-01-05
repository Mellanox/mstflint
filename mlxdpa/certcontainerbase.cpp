/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "certcontainerbase.h"
#include "mlxdpa_utils.h"
#include <mft_utils.h>
#include <iostream>

CertStructHeader::CertStructHeader() :
    _length(HEADER_SIZE),
    _type(StructType::Unknown),
    _version(0),
    _priority(StructPriority::Unknown),
    _valid(0),
    _securityMethod(StructSecurityMethod::None),
    _crc(0x0)
{
}

CertStructHeader::CertStructHeader(StructPriority priority, StructType type, u_int16_t structLength) :
    _length(HEADER_SIZE + structLength),
    _type(type),
    _version(0),
    _priority(priority),
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
    _priority = CertStructHeader::StructPriority((*begin >> 4) & 0x03);
    _valid = ((*begin >> 6) & 0x03);

    begin++;
    _type = CertStructHeader::StructType(*begin);

    begin++;
    _length = *(reinterpret_cast<const u_int16_t*>(&(*begin)));

    begin += 2;
    _securityMethod = CertStructHeader::StructSecurityMethod((*begin >> 4) & 0x0F);

    begin += 4;
    _crc = *(reinterpret_cast<const u_int16_t*>(&(*begin)));

    return true;
}

bool CertStructHeader::Deserialize(vector<u_int8_t> header)
{
    return Deserialize(header.cbegin(), header.cend());
}

CertStructHeader::StructPriority CertStructHeader::ToStructPriority(string priority)
{
    mft_utils::to_lowercase(priority);
    if (priority == "user")
    {
        return StructPriority::User;
    }
    else if (priority == "vendor" || priority == "oem")
    {
        return StructPriority::Vendor;
    }
    else if (priority == "nvidia")
    {
        return StructPriority::Nvidia;
    }
    else
    {
        return StructPriority::Unknown;
    }
}

CertContainerItem::CertContainerItem(CertStructHeader::StructPriority priority, CertStructBase* data) :
    _header(priority, data->GetType(), data->GetSize()), _struct(data)
{
}

vector<u_int8_t> CertContainerItem::Serialize(bool toBigEndian)
{
    vector<u_int8_t> serializedData = _header.Serialize();
    vector<u_int8_t> structData = _struct->Serialize();

    if (toBigEndian)
    {
        CPUTOn(serializedData.data(), serializedData.size() / 4);
        if (_struct->GetType() != CertStructHeader::StructType::Signature &&
            _struct->GetType() != CertStructHeader::StructType::CertificateX509)
        {
            CPUTOn(structData.data(), structData.size() / 4);
        }
    }

    serializedData.insert(serializedData.end(), structData.cbegin(), structData.cend());

    return serializedData;
}
