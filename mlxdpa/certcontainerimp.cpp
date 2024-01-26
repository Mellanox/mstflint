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

#include "certcontainerimp.h"
#include "mlxdpa_utils.h"
#include <string.h>

CACertMetaData::CACertMetaData(u_int32_t certUUID[4], u_int32_t keypairUUID[4]) : _dpaRotEn(1)
{
    memcpy(&_certUUID, certUUID, 16);
    memcpy(&_keypairUUID, keypairUUID, 16);
}

vector<u_int8_t> CACertMetaData::Serialize()
{
    vector<u_int8_t> serializedData(GetSize());

    memcpy(serializedData.data(), _certUUID, _certUUIDSize);
    memcpy(serializedData.data() + GetSize() - _keypairUUIDSize, _keypairUUID, _keypairUUIDSize);

    serializedData[0x12] |= (_dpaRotEn << 5); // dpa_rot_en is bit 21 at offset 0x10 -> byte 0x12, bit 5

    return serializedData;
}

void CACertMetaData::Deserialize(vector<u_int8_t> buf)
{
    memcpy(_certUUID, buf.data(), _certUUIDSize);
    memcpy(_keypairUUID, buf.data() + GetSize() - _keypairUUIDSize, _keypairUUIDSize);
    _dpaRotEn = (buf[12] >> 5) & 0x1;
}

CACertRemove::CACertRemove(u_int32_t certUUID[4], u_int32_t keypairUUID[4], bool removeAll) : _removeAll(removeAll)
{
    memcpy(_certUUID, certUUID, 16);
    memcpy(_keypairUUID, keypairUUID, 16);
}

vector<u_int8_t> CACertRemove::Serialize()
{
    vector<u_int8_t> serializedData(GetSize());

    memcpy(serializedData.data(), _certUUID, _certUUIDSize);
    memcpy(serializedData.data() + _certUUIDSize, _keypairUUID, _keypairUUIDSize);
    serializedData[32] |= (_removeAll ? 1 : 0);

    return serializedData;
}

void CACertRemove::Deserialize(vector<u_int8_t> buf)
{
    memcpy(_certUUID, buf.data(), _certUUIDSize);
    memcpy(_keypairUUID, buf.data() + _certUUIDSize, _keypairUUIDSize);
    _removeAll = buf[32] & 1;
}

CACert::CACert(string certPath)
{
    const u_int32_t ALIGNMENT = 4;
    _cert = ReadFromFile(certPath);
    if (_cert.size() % ALIGNMENT)
    {
        u_int32_t paddingSize = ALIGNMENT - (_cert.size() % ALIGNMENT);
        _cert.resize(_cert.size() + paddingSize, 0x0);
    }
}
