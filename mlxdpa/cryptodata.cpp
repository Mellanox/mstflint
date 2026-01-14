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
#include "cryptodata.h"

#include <iterator>
#include <sstream>

#include "elfio/elfio.hpp"
#include "mft_utils.h"
#include "mlxdpa_utils.h"
#include "mlxfwops/lib/flint_base.h"
#include "mlxsign_lib.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/*                                          CryptoDataSection::HashListTable                                        */
/*                                                                                                                  */
/********************************************************************************************************************/

CryptoDataSection::HashListTable::HashListTable() :
    _magicPattern{'H', 'S', 'A', 'H',
                  'T', 'S', 'I', 'L'}, // magic-pattern will be converted to "HASHLIST" once swapped to big-endian
    _numOfExtHashFields(0),
    _numOfSections(0)
{
    memset(&_elfHeaderHash, 0x0, sizeof(_elfHeaderHash));
    memset(&_programHeadersHash, 0x0, sizeof(_programHeadersHash));
    memset(&_sectionHeadersHash, 0x0, sizeof(_sectionHeadersHash));
    memset(&_reserved, 0xff, sizeof(_reserved));
    memset(&_reserved2, 0xff, sizeof(_reserved2));
}

void CryptoDataSection::HashListTable::AddHash(EntryType type, const vector<u_int8_t>& data, const u_int32_t isPresent)
{
    MlxSignSHA256 mlxSignSHA;
    mlxSignSHA << data;
    vector<u_int8_t> sha;
    mlxSignSHA.getDigest(sha);
    CPUTOn(sha.data(), sha.size() / 4); // Converting SHA (which is big-endian) to platform endianness
    switch (type)
    {
        case EntryType::dpaApp:
            _dpaAppElfHash = sha;
            break;
        case EntryType::elfHeader:
            break;
        case EntryType::programHeaders:
            break;
        case EntryType::programData:
            break;
        case EntryType::sectionHeaders:
            break;
        case EntryType::sectionData:
            break;
        case EntryType::sectionAppMetadata:
            _hashOfAppMetadata = (isPresent == 1) ? sha : std::vector<u_int8_t>(0x20, 0x0);
            _numOfExtHashFields++;
            break;
        case EntryType::sectionAppManifest:
            _hashOfAppManifest = (isPresent == 1) ? sha : std::vector<u_int8_t>(0x20, 0x0);
            _numOfExtHashFields++;
            break;
        default:
            throw MlxDpaException("Unknown hash entry type");
            break;
    }
}

vector<u_int8_t> CryptoDataSection::HashListTable::Serialize()
{
    vector<u_int8_t> rawData;

    rawData.insert(rawData.end(), begin(_magicPattern), end(_magicPattern));
    rawData.push_back(_numOfExtHashFields);
    rawData.insert(rawData.end(), begin(_reserved), end(_reserved));
    rawData.push_back(_numOfSections);
    rawData.insert(rawData.end(), begin(_reserved2), end(_reserved2));
    rawData.insert(end(rawData), begin(_dpaAppElfHash), end(_dpaAppElfHash));
    rawData.insert(end(rawData), begin(_elfHeaderHash), end(_elfHeaderHash));
    rawData.insert(end(rawData), begin(_programHeadersHash), end(_programHeadersHash));
    if (_numOfExtHashFields > 0)
    {
        rawData.insert(end(rawData), begin(_hashOfAppMetadata), end(_hashOfAppMetadata));
        rawData.insert(end(rawData), begin(_hashOfAppManifest), end(_hashOfAppManifest));
    }
    rawData.insert(end(rawData), begin(_sectionHeadersHash), end(_sectionHeadersHash));

    return rawData;
}

/********************************************************************************************************************/
/*                                                                                                                  */
/*                                          CertChain                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

CryptoDataSection::CertChain::CertChain() : _metadata{Unknown, 0, sizeof(_metadata), 0xff, 0xffffffff, 0, 0xffff} {}

vector<u_int8_t> CryptoDataSection::CertChain::Serialize()
{
    vector<u_int8_t> rawData;

    rawData.insert(rawData.end(), (u_int8_t*)&_metadata, ((u_int8_t*)&_metadata) + sizeof(_metadata));
    rawData.insert(rawData.end(), _certificates.begin(), _certificates.end());

    return rawData;
}

void CryptoDataSection::CertChain::AddCertificate(vector<u_int8_t> certificate)
{
    _certificates.insert(_certificates.end(), certificate.cbegin(), certificate.cend());
    _metadata.count++;
    _metadata.length += certificate.size();
    _metadata.type = ThirdPartyCodeAuthentication;

    Crc16 crc;
    u_int32_t firstDWord = _metadata.type;
    firstDWord |= _metadata.count << 4;
    firstDWord |= _metadata.length << 16;

    // crc is calculated on the first two dwords
    crc.add(firstDWord);
    crc.add(_metadata.reserved);
    crc.finish();
    _metadata.crc = crc.get();
}

void CryptoDataSection::CertChain::AddCertificates(string path)
{
    try
    {
        vector<u_int8_t> cert = ReadFromFile(path);
        CPUTOn(cert.data(), cert.size() / 4); // Converting certificate (which is big-endian) to platform endianness

        // TODO validate certificate
        // openssl x509 -inform der -in .\leaf.cert.cer -outform pem | openssl verify -CAfile CA/ca.crt

        AddCertificate(cert);
    }
    catch (...)
    {
        throw MlxDpaException("Failed reading certificate chain file %s.", path.c_str());
    }
}

/********************************************************************************************************************/
/*                                                                                                                  */
/*                                          CryptoDataSection                                                       */
/*                                                                                                                  */
/********************************************************************************************************************/ 
CryptoDataSection::CryptoDataSection(CertChain certChain)
{
    memset(&_metadata, 0x0, sizeof(_metadata)); // TODO - temp until we have a definition on how to set metadata fields
    _metadata._signatureType = (u_int16_t)CryptoDataSection::SignatureType::Reserved0;
    _metadata._encParamsPresent = 0; // ENC PARAMS is not available in the current release
    _metadata._appMetadataPresent = 0;
    _certChain = certChain;
    _isHostElf = true;
}

void CryptoDataSection::SetSingleElfState()
{
    _isHostElf = false;
}

vector<u_int8_t> CryptoDataSection::Serialize()
{
    vector<u_int8_t> cryptoDataBlob;
    vector<u_int8_t> serializedData;

    cryptoDataBlob.insert(cryptoDataBlob.end(), (u_int8_t*)&_metadata, ((u_int8_t*)&_metadata) + sizeof(_metadata));

    serializedData = _hashList.Serialize();
    cryptoDataBlob.insert(cryptoDataBlob.end(), serializedData.cbegin(), serializedData.cend());

    cryptoDataBlob.insert(cryptoDataBlob.end(), _cryptoSignature.cbegin(), _cryptoSignature.cend());

    serializedData = _certChain.Serialize();
    cryptoDataBlob.insert(cryptoDataBlob.end(), serializedData.cbegin(), serializedData.cend());

    return cryptoDataBlob;
}

void CryptoDataSection::SetAppMetadataPresent(const u_int32_t value)
{
    _metadata._appMetadataPresent = value;
}

void CryptoDataSection::SetManifestPresent(const u_int32_t value)
{
    _metadata._manifestPresent = value;
}

void CryptoDataSection::SetEncParamsPresent(const u_int32_t value)
{
    _metadata._encParamsPresent = value;
}
 
 u_int32_t CryptoDataSection::GetAppMetadataPresent() const
 {
     return _metadata._appMetadataPresent;
 }
 
 u_int32_t CryptoDataSection::GetManifestPresent() const
 {
     return _metadata._manifestPresent;
 }
 
 vector<u_int8_t> CryptoDataSection::GetAppMetaData() const
 {
     return _appMetadata;
 }
 
 void CryptoDataSection::SetAppMetadata(const vector<u_int8_t>& appMetadata)
 {
     _appMetadata = appMetadata;
 }
 
 void CryptoDataSection::SetManifest(const vector<u_int8_t>& manifest)
 {
     _manifest = manifest;
 }
 
 void CryptoDataSection::GenerateHashListFromELF(const vector<u_int8_t>& elf)
 {
     _hashList.AddHash(HashListTable::EntryType::dpaApp, elf);
 
     // app metadata section
     _hashList.AddHash(HashListTable::EntryType::sectionAppMetadata, _appMetadata, GetAppMetadataPresent());
 
     // manifest section
     _hashList.AddHash(HashListTable::EntryType::sectionAppManifest, _manifest, GetManifestPresent());
 }
 
void CryptoDataSection::Sign(const MlxSign::Signer& signer)
{
    vector<u_int8_t> hashListBytes = _hashList.Serialize();
    vector<u_int8_t> dataForSign(sizeof(_metadata), 0);

    _metadata._signatureType = (u_int32_t)SignatureType::RsaSha512;
    memcpy(dataForSign.data(), &_metadata, sizeof(_metadata));
    dataForSign.insert(end(dataForSign), begin(hashListBytes), end(hashListBytes));

    CPUTOn(
      dataForSign.data(),
      dataForSign.size() / 4); // Converting data for sign to big-endian, since eventually we'll deliver this data as BE

    if (signer.Sign(dataForSign, _cryptoSignature) != MlxSign::MLX_SIGN_SUCCESS)
    {
        throw MlxDpaException("Signing Host ELF failed.");
    }

    CPUTOn(_cryptoSignature.data(),
           _cryptoSignature.size() / 4); // Converting signature (which is big-endian) to platform endianness
}
