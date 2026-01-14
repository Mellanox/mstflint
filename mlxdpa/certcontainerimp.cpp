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

#include <string.h>
#include "certcontainerimp.h"
#include "mft_utils/mft_utils.h"

CACertMetaData::CACertMetaData(u_int32_t certUUID[4], u_int32_t keypairUUID[4], u_int8_t keepSig) : _dpaRotEn(1)
{
    _keep_sig = keepSig;
    _certUUID = mft_utils::ToVector(certUUID, 4);
    _keypairUUID = mft_utils::ToVector(keypairUUID, 4);
}

vector<u_int8_t> CACertMetaData::Serialize()
{
    vector<u_int8_t> serializedData;
    serializedData.resize(GetSize());
    copy(_certUUID.begin(), _certUUID.end(), serializedData.begin());
    copy(_keypairUUID.begin(), _keypairUUID.end(), serializedData.begin() + GetSize() - _keypairUUID.size());

    serializedData[0x12] |= (_dpaRotEn << 5); // dpa_rot_en is bit 21 at offset 0x10 -> byte 0x12, bit 5
    serializedData[0x10] |= (_keep_sig << 4); // keep_sig is bit 4 at offset 0x10 -> byte 0x11, bit 3

    return serializedData;
}

void CACertMetaData::Deserialize(vector<u_int8_t> buf)
{
    _certUUID.clear();
    _certUUID.reserve(_certUUIDSize);
    copy(buf.begin(), buf.begin() + _certUUIDSize, std::back_inserter(_certUUID));

    _keypairUUID.clear();
    _keypairUUID.reserve(_keypairUUIDSize);
    copy(buf.begin() + GetSize() - _keypairUUIDSize, buf.begin() + GetSize(), std::back_inserter(_keypairUUID));

    _dpaRotEn = (buf[0x11] >> 5) & 0x1; // This key can be used for authenticating DPA app code.
    _keep_sig = (buf[0x13] >> 4) & 0x1;
    _targetingType = (buf[0x13] >> 4) & 0xf; // type of targeting used in this certificate.
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
    _cert = mft_utils::ReadFromFile(certPath);
    if (_cert.size() % ALIGNMENT)
    {
        u_int32_t paddingSize = ALIGNMENT - (_cert.size() % ALIGNMENT);
        _cert.resize(_cert.size() + paddingSize, 0x0);
    }
}
