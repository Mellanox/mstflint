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

class CACertMetaData : public CertStructBase
{
public:
    CACertMetaData(u_int32_t certUUID[4], u_int32_t keypairUUID[4]);
    virtual ~CACertMetaData() {}
    vector<u_int8_t> Serialize() override;
    void Deserialize(vector<u_int8_t> buf) override;
    u_int16_t GetSize() override { return 0x24; };
    CertStructHeader::StructType GetType() override { return CertStructHeader::StructType::CacertMetadata; };

private:
    const u_int32_t _keypairUUIDSize = 16;
    const u_int32_t _certUUIDSize = 16;

    u_int32_t _certUUID[4];
    u_int8_t _dpaRotEn;
    u_int32_t _keypairUUID[4];
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