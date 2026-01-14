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

class CACertMetaData : public CertStructBase
{
public:
    CACertMetaData(u_int32_t certUUID[4], u_int32_t keypairUUID[4], u_int8_t keepSig);
    CACertMetaData(){};
    virtual ~CACertMetaData() {}
    vector<u_int8_t> Serialize() override;
    void Deserialize(vector<u_int8_t> buf) override;
    u_int16_t GetSize() override { return 0x24; };
    CertStructHeader::StructType GetType() override { return CertStructHeader::StructType::CacertMetadata; };
    vector<u_int8_t> GetKeypairUUID() override { return _keypairUUID; };
    vector<u_int8_t> GetCertUUID() override { return _certUUID; };
    u_int8_t GetDpaRotEn() override { return _dpaRotEn; };
    u_int8_t GetTargetingType() override { return _targetingType; };

private:
    const u_int32_t _keypairUUIDSize = 16;
    const u_int32_t _certUUIDSize = 16;

    vector<u_int8_t> _certUUID;
    vector<u_int8_t> _keypairUUID;
    u_int8_t _targetingType;
    u_int8_t _dpaRotEn;
   u_int8_t _keep_sig;
};

class CACertRemove : public CertStructBase
{
public:
    CACertRemove(u_int32_t certUUID[4], u_int32_t keypairUUID[4], bool removeAll);
    virtual ~CACertRemove() {}
    vector<u_int8_t> Serialize() override;
    void Deserialize(vector<u_int8_t> buf) override;
    u_int16_t GetSize() override { return 0x24; };
    CertStructHeader::StructType GetType() override { return CertStructHeader::StructType::CacertRemove; };
    bool IsRemoveAll() { return !(_removeAll == 0); }

private:
    const u_int32_t _keypairUUIDSize = 16;
    const u_int32_t _certUUIDSize = 16;

    u_int32_t _certUUID[4];
    u_int8_t _removeAll;
    u_int32_t _keypairUUID[4];
};

class CACert : public CertStructBase
{
public:
    CACert(string certPath);
    virtual ~CACert() {}
    vector<u_int8_t> Serialize() override { return _cert; }
    void Deserialize(vector<u_int8_t> buf) override { _cert = buf; }
    u_int16_t GetSize() override { return _cert.size(); }
    CertStructHeader::StructType GetType() override { return CertStructHeader::StructType::CertificateX509; };

private:
    vector<u_int8_t> _cert;
};

class CertStructSignature : public CertStructBase
{
public:
    CertStructSignature(vector<u_int8_t> signature) : _signature(signature) {}

    vector<u_int8_t> Serialize() override { return _signature; }
    void Deserialize(vector<u_int8_t> buf) override { _signature = buf; }
    u_int16_t GetSize() override { return _signature.size(); }
    CertStructHeader::StructType GetType() override { return CertStructHeader::StructType::Signature; };

private:
    vector<u_int8_t> _signature;
};
