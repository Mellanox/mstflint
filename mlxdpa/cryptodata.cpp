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

#include <sstream>
#include <iterator>
#include "elfio/elfio.hpp"
#include "mlxdpa_utils.h"
#include "cryptodata.h"
#include "mlxsign_lib.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/*                                          CryptoDataSection::HashListTable                                        */
/*                                                                                                                  */
/********************************************************************************************************************/

CryptoDataSection::HashListTable::HashListTable() :
    _magicPattern{'H', 'S', 'A', 'H',
                  'T', 'S', 'I', 'L'}, // magic-pattern will be converted to "HASHLIST" once swapped to big-endian
    _numOfSegments(0),
    _numOfSections(0)
{
    memset(&_reserved, 0xff, sizeof(_reserved));
    memset(&_reserved2, 0xff, sizeof(_reserved2));
}

void CryptoDataSection::HashListTable::AddHash(EntryType type, const vector<u_int8_t>& data)
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
            _elfHeaderHash = sha;
            break;
        case EntryType::programHeaders:
            _programHeadersHash = sha;
            break;
        case EntryType::programData:
            _programsHashes.push_back(sha);
            _numOfSegments++;
            break;
        case EntryType::sectionHeaders:
            _sectionHeadersHash = sha;
            break;
        case EntryType::sectionData:
            _sectionsHashes.push_back(sha);
            _numOfSections++;
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
    rawData.push_back(_numOfSegments);
    rawData.insert(rawData.end(), begin(_reserved), end(_reserved));
    rawData.push_back(_numOfSections);
    rawData.insert(rawData.end(), begin(_reserved2), end(_reserved2));

    rawData.insert(end(rawData), begin(_dpaAppElfHash), end(_dpaAppElfHash));
    rawData.insert(end(rawData), begin(_elfHeaderHash), end(_elfHeaderHash));
    rawData.insert(end(rawData), begin(_programHeadersHash), end(_programHeadersHash));
    for (auto hash : _programsHashes)
    {
        rawData.insert(end(rawData), begin(hash), end(hash));
    }
    rawData.insert(end(rawData), begin(_sectionHeadersHash), end(_sectionHeadersHash));
    for (auto hash : _sectionsHashes)
    {
        rawData.insert(end(rawData), begin(hash), end(hash));
    }

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
    _metadata._signatureType = (u_int32_t)SignatureType::None;
    _certChain = certChain;
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

void CryptoDataSection::GenerateHashListFromELF(const vector<u_int8_t>& elf)
{
    ELFIO::elfio reader;
    stringstream ioss;

    std::copy(elf.cbegin(), elf.cend(), ostream_iterator<u_int8_t>(ioss));
    if (!reader.load(ioss))
    {
        throw MlxDpaException("Failed loading DPA app ELF");
    }

    _hashList.AddHash(HashListTable::EntryType::dpaApp, elf);

    vector<u_int8_t> data(elf.cbegin(), elf.cbegin() + reader.get_header_size());
    _hashList.AddHash(HashListTable::EntryType::elfHeader, data);

    // program(segment) headers consists of number of entries, one after the other.
    // each header points to the segment data in the file.
    auto programHeaderIter = elf.cbegin() + reader.get_segments_offset();
    // reader.segments.size() is number of segments entries
    auto programHeaderSize = reader.segments.size() * reader.get_segment_entry_size();
    data.assign(programHeaderIter, programHeaderIter + programHeaderSize);
    _hashList.AddHash(HashListTable::EntryType::programHeaders, data);

    // segments list contains segments data (not headers)
    for (auto it = reader.segments.begin(); it < reader.segments.end(); ++it)
    {
        data.assign((*it)->get_data(), (*it)->get_data() + (*it)->get_file_size());
        _hashList.AddHash(HashListTable::EntryType::programData, data);
    }

    // section headers consists of number of entries, one after the other.
    // each header points to the section data in the file, if exists.
    auto sectionHeaderIter = elf.cbegin() + reader.get_sections_offset();
    // reader.sections.size() is number of sections entries
    auto sectionHeaderSize = reader.sections.size() * reader.get_section_entry_size();
    data.assign(sectionHeaderIter, sectionHeaderIter + sectionHeaderSize);
    _hashList.AddHash(HashListTable::EntryType::sectionHeaders, data);

    // sections list contains segments data (not headers)
    for (auto it = reader.sections.begin(); it < reader.sections.end(); ++it)
    {
        if ((*it)->get_data() != nullptr)
        {
            data.assign((*it)->get_data(), (*it)->get_data() + (*it)->get_size());
            _hashList.AddHash(HashListTable::EntryType::sectionData, data);
        }
    }
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