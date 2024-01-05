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

#ifndef MLXDPA_CACERTCONTAINER_H_
#define MLXDPA_CACERTCONTAINER_H_

#include <string>
#include <vector>
#include <memory>
#include "compatibility.h"

using namespace std;

class CertStructHeader
{
public:
    enum class StructType
    {
        CertificateX509 = 0x0,
        Signature = 0x1,
        CacertMetadata = 0x2,
        Cacert = 0x3,
        CertChainMetadata = 0x4,
        CacertRemove = 0x5,
        CertChainRemove = 0x6,
        Unknown
    };

    enum class StructPriority
    {
        User = 0x0,
        Vendor = 0x1,
        Nvidia = 0x3,
        Unknown
    };

    CertStructHeader();
    CertStructHeader(StructPriority priority, StructType type, u_int16_t structLength);

    vector<u_int8_t> Serialize();
    bool Deserialize(vector<u_int8_t> header);
    bool Deserialize(vector<u_int8_t>::const_iterator begin, vector<u_int8_t>::const_iterator end);
    StructType GetType() { return _type; }

    static StructPriority ToStructPriority(string priority);

    enum class StructSecurityMethod
    {
        None = 0x0,
        Crc16OfHeader = 0x1,
        Crc16OfHeaderAndData = 0x2
    };

    static const u_int32_t HEADER_SIZE = 12;

private:
    u_int16_t _length;
    StructType _type;
    u_int8_t _version;
    StructPriority _priority;
    u_int8_t _valid;
    StructSecurityMethod _securityMethod;
    u_int16_t _crc;
};

class CertStructBase
{
public:
    virtual ~CertStructBase() {}
    virtual vector<u_int8_t> Serialize() = 0;
    virtual void Deserialize(vector<u_int8_t> buf) = 0;
    virtual u_int16_t GetSize() = 0;
    virtual CertStructHeader::StructType GetType() = 0;

    static const u_int32_t METADATA_SIZE = 36;

private:
};

class CertContainerItem
{
public:
    CertContainerItem(CertStructHeader::StructPriority priority, CertStructBase* data);
    CertContainerItem(CertStructHeader header, CertStructBase* data);

    vector<u_int8_t> Serialize(bool toBigEndian = false);

private:
    CertStructHeader _header;
    shared_ptr<CertStructBase> _struct;
};

#endif /* MLXDPA_CACERTCONTAINER_H_ */