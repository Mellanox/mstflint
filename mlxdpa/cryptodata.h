/*
 * Copyright (c) 2013-2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#ifndef MLXDPA_CRYPTODATA_H_
#define MLXDPA_CRYPTODATA_H_

#include <memory>
#include <vector>

#include "mlxsign_signer_interface.h"
#include "include/mtcr_ul/mtcr_com_defs.h"

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
            sectionData,
            sectionAppMetadata,
            sectionAppManifest
        };

        HashListTable();
        vector<u_int8_t> Serialize();
        void AddHash(EntryType type, const vector<u_int8_t>& data, const u_int32_t isPresent = 0);

    private:
        u_int8_t _magicPattern[8];
        u_int8_t _numOfExtHashFields; // old name _numOfSegments
        u_int8_t _reserved[3];
        u_int8_t _numOfSections; // changed to reserved that must be 0
        u_int8_t _reserved2[19];
        vector<u_int8_t> _dpaAppElfHash;
        u_int8_t _elfHeaderHash[32];      // changed to reserved that must be 0
        u_int8_t _programHeadersHash[32]; // changed to reserved that must be 0
        vector<u_int8_t> _hashOfAppMetadata;
        vector<u_int8_t> _hashOfAppManifest;
        u_int8_t _sectionHeadersHash[32]; // changed to reserved that must be 0
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

    enum class SignatureType : u_int16_t
     {
         Reserved0 = 0,
         Reserved1 = 1,
         RsaSha512 = 2,
         Reserved
     };
 
    struct Metadata
    {
        u_int32_t _metadataVersion : 16;
        u_int32_t _reserved0 : 16;
        u_int32_t _reserved1 : 8;
        u_int32_t _dpaFwType : 8;
        u_int32_t _reserved2 : 13;
        u_int32_t _manifestPresent : 1;
        u_int32_t _appMetadataPresent : 1;
        u_int32_t _encParamsPresent : 1;
        u_int8_t _reserved[52];
        u_int16_t _signatureType;
    };

    enum class AppMetadataType : u_int8_t
    {
        APU_APP_EXTERNAL = 0,
        Reserved1 = 1,
        Reserved2 = 2,
        Reserved3 = 3,
        APU_APP_PCC = 4,
        APU_APP_DLL = 5,
        APU_APP_KERNEL = 6,
        Reserved
    };

    CryptoDataSection(CertChain certChain);
    void GenerateHashListFromELF(const vector<u_int8_t>& elf);
    void SetAppMetadata(const vector<u_int8_t>& appMetadata);
    void SetManifest(const vector<u_int8_t>& manifest);
    void SetManifestPresent(u_int32_t value);
    void SetAppMetadataPresent(u_int32_t value);
    u_int32_t GetAppMetadataPresent() const;
    u_int32_t GetManifestPresent() const;
    void SetEncParamsPresent(u_int32_t value);
    void Sign(const MlxSign::Signer& signer);
    void SetSingleElfState();
    vector<u_int8_t> Serialize();
    vector<u_int8_t> GetAppMetaData() const;

private:
    Metadata _metadata;
    HashListTable _hashList;
    vector<u_int8_t> _cryptoSignature;
    CertChain _certChain;
    vector<u_int8_t> _appMetadata;
    vector<u_int8_t> _manifest;
    bool _isHostElf;
};

#endif /* MLXDPA_CRYPTODATA_H_ */
