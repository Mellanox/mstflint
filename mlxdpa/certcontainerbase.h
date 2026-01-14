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

#ifndef MLXDPA_CACERTCONTAINER_H_
#define MLXDPA_CACERTCONTAINER_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "compatibility.h"
#include "baseHeader.h"

using namespace std;

class CertStructHeader : public BaseHeader
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

    CertStructHeader();
    CertStructHeader(BaseHeader::StructPriority priority, StructType type, u_int16_t structLength);
    bool ValidateNvidiaSignedOemPriority();
    static BaseHeader::StructPriority GetPriorityNvidiaSignedOem(StructType type);
    vector<u_int8_t> Serialize();
    bool Deserialize(vector<u_int8_t> header);
    bool Deserialize(vector<u_int8_t>::const_iterator begin, vector<u_int8_t>::const_iterator end);
    StructType GetType() { return _type; }
    u_int16_t GetLength() const { return _length; }

    enum class StructSecurityMethod
    {
        None = 0x0,
        Crc16OfHeader = 0x1,
        Crc16OfHeaderAndData = 0x2
    };
    static const map<BaseHeader::StructPriority, string> _metadataPriorityToString;
    static const u_int32_t HEADER_SIZE = 12;

private:
    u_int16_t _length;
    StructType _type;
    u_int8_t _version;
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
    virtual vector<u_int8_t> GetKeypairUUID();
    virtual vector<u_int8_t> GetCertUUID();
    virtual u_int8_t GetTargetingType();
    virtual u_int8_t GetDpaRotEn();

    static const u_int32_t METADATA_SIZE = 36;

private:
};

class CertContainerItem
{
public:
    CertContainerItem(BaseHeader::StructPriority priority, shared_ptr<CertStructBase> data);
    CertContainerItem(CertStructHeader header, shared_ptr<CertStructBase> data, vector<u_int8_t> cert) :
        _header(header), _metadata(data), _cert(cert){};
    CertContainerItem(){};

    CertStructHeader GetHeader() { return _header; };
    shared_ptr<CertStructBase> GetMetadata() { return _metadata; };
    vector<u_int8_t> GetCert() { return _cert; };
    vector<u_int8_t> Serialize(bool toBigEndian = false);

private:
    CertStructHeader _header;
    shared_ptr<CertStructBase> _metadata;
    vector<u_int8_t> _cert;
};

class CertException : public exception
{
private:
    string message;

public:
    CertException(const char* msg) : message(msg) {}
    const char* what() const throw() { return message.c_str(); }
};

#endif /* MLXDPA_CACERTCONTAINER_H_ */
