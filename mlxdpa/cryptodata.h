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

#ifndef MLXDPA_CRYPTODATA_H_
#define MLXDPA_CRYPTODATA_H_

#include <vector>
#include <memory>
#include "include/mtcr_ul/mtcr_com_defs.h"
#include "mlxsign_signer_interface.h"

using namespace std;

class CryptoDataSection
{
public:
    class HashListTable
    {
    public:
        enum class EntryType
        {
            dpaApp,
            elfHeader,
            programHeaders,
            programData,
            sectionHeaders,
            sectionData
        };

        HashListTable();
        vector<u_int8_t> Serialize();
        void AddHash(EntryType type, const vector<u_int8_t>& data);

    private:
        u_int8_t _magicPattern[8];
        u_int8_t _numOfSegments;
        u_int8_t _reserved[3];
        u_int8_t _numOfSections;
        u_int8_t _reserved2[19];
        vector<u_int8_t> _dpaAppElfHash;
        vector<u_int8_t> _elfHeaderHash;
        vector<u_int8_t> _programHeadersHash;
        vector<vector<u_int8_t>> _programsHashes;
        vector<u_int8_t> _sectionHeadersHash;
        vector<vector<u_int8_t>> _sectionsHashes;
    };

    class CertChain
    {
    public:
        CertChain();

        vector<u_int8_t> Serialize();
        void AddCertificates(string path);
        void SetCount(u_int32_t count) { _metadata.count = count; }

    private:
        enum CertChainType
        {
            Unknown = 0,
            ThirdPartyCodeAuthentication = 1
        };

        struct CertChainMetadata
        {
            u_int32_t type : 4;
            u_int32_t count : 4;
            u_int32_t length : 16;
            u_int32_t reserved3 : 8;
            u_int32_t reserved;
            u_int16_t crc;
            u_int16_t reserved2;
        };

        void AddCertificate(vector<u_int8_t> certificate);

        CertChainMetadata _metadata;
        vector<u_int8_t> _certificates;
    };

    struct Metadata
    {
        u_int32_t _metadataVersion;
        u_int32_t _dpaFwType;
        u_int8_t _reserved[52];
        u_int32_t _signatureType;
    };

    enum class SignatureType : u_int16_t
    {
        RsaSha512 = 2,
        None = 0xffff
    };

    CryptoDataSection(CertChain certChain);

    void GenerateHashListFromELF(const vector<u_int8_t>& elf);
    void Sign(const MlxSign::Signer& signer);
    vector<u_int8_t> Serialize();

private:
    Metadata _metadata;
    HashListTable _hashList;
    vector<u_int8_t> _cryptoSignature;
    CertChain _certChain;
};

#endif /* MLXDPA_CRYPTODATA_H_ */