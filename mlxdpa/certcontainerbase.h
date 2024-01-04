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
