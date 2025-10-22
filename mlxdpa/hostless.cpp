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
 *
 *  Version: $Id$
 *
 */
#include "hostless.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sole.hpp>
#include "elfio/elfio.hpp"

#include "mft_utils/mft_utils.h"
#include "mlxdpa_utils.h"

const string HostLess::SINGLE_APP_DPA_FINGERPRINT = "NV_DPA_APP.BIN!!";

HostLess::HostLess(string elfPath, string appMetadataPath, string manifestPath) :
    _elfPath(elfPath),
    _elfHeader(),
    _elfData(),
    _appMetadataHeader(),
    _appMetadata(),
    _isAppMetadataPresent(false),
    _manifestHeader(),
    _manifestData(),
    _isManifestPresent(false),
    _priority(BaseHeader::StructPriority::Unknown),
    _checkHeaderPriority(true),
    _uuid("")
{
    SetElfData();
    memset(&_appMetadata, 0, sizeof(_appMetadata));
    SetAppMetadata(appMetadataPath);
    SetManifest(manifestPath);
}

HostLess::HostLess(string containerForSigningPath, BaseHeader::StructPriority priority, bool checkHeaderPriority) :
    _elfPath(containerForSigningPath),
    _elfHeader(),
    _elfData(),
    _appMetadataHeader(),
    _appMetadata(),
    _isAppMetadataPresent(false),
    _manifestHeader(),
    _manifestData(),
    _isManifestPresent(false),
    _priority(priority),
    _checkHeaderPriority(checkHeaderPriority),
    _uuid("")
{
    SetContainerForSigning();
}

HostLess::~HostLess() {}

void HostLess::SetContainerForSigning()
{
    std::fstream containerForSigningFile(_elfPath, ios::in | ios::out | std::ios::binary);
    if ((containerForSigningFile.rdstate() & std::ifstream::failbit) != 0)
    {
        throw MlxDpaException("Error opening '%s'", _elfPath.c_str());
    }
    vector<u_int8_t> containerForSigning((std::istreambuf_iterator<char>(containerForSigningFile)),
                                         std::istreambuf_iterator<char>());

    if (strncmp((const char*)containerForSigning.data(), SINGLE_APP_DPA_FINGERPRINT.c_str(),
                SINGLE_APP_DPA_FINGERPRINT.size()) != 0)
    {
        throw MlxDpaException("Invalid container for signing.");
    }

    vector<u_int8_t>::iterator containerIter = containerForSigning.begin() + SINGLE_APP_DPA_FINGERPRINT.size();
    while (containerIter < containerForSigning.end())
    {
        DpaAppStructHeader header;
        if (!header.Deserialize(containerIter, containerIter + DpaAppStructHeader::HEADER_SIZE_NO_AUTH))
        {
            throw MlxDpaException("Invalid header size in given container.");
        }

        if (containerIter + header.GetLength() > containerForSigning.end())
        {
            throw MlxDpaException("Incomplete header data in container.");
        }

        if (header.GetType() == DpaAppStructHeader::StructType::DPA_ELF)
        {
            _elfHeader = header;
            if (_checkHeaderPriority && !CheckHeaderPriority(header.GetPriority()))
            {
                throw MlxDpaException("Invalid priority in header data.");
            }
            _elfData = vector<u_int8_t>(containerIter + DpaAppStructHeader::HEADER_SIZE_NO_AUTH,
                                        containerIter + header.GetLength());
        }
        if (header.GetType() == DpaAppStructHeader::StructType::DPA_APP_METADATA)
        {
            _appMetadataHeader = header;
            if (_checkHeaderPriority && !CheckHeaderPriority(header.GetPriority()))
            {
                throw MlxDpaException("Invalid priority in header data.");
            }
            AppMetadataUnpack(containerIter + DpaAppStructHeader::HEADER_SIZE_NO_AUTH,
                              containerIter + header.GetLength());
            _isAppMetadataPresent = true;
        }
        if (header.GetType() == DpaAppStructHeader::StructType::DPA_APP_MANIFEST)
        {
            _manifestHeader = header;
            if (_checkHeaderPriority && !CheckHeaderPriority(header.GetPriority()))
            {
                throw MlxDpaException("Invalid priority in header data.");
            }
            if (header.GetLength() > DpaAppStructHeader::HEADER_SIZE_NO_AUTH)
            {
                _manifestData.resize(header.GetLength() - DpaAppStructHeader::HEADER_SIZE_NO_AUTH);
                _manifestData = vector<u_int8_t>(containerIter + DpaAppStructHeader::HEADER_SIZE_NO_AUTH,
                                                 containerIter + header.GetLength());
                _isManifestPresent = true;
            }
        }
        containerIter += header.GetLength();
    }
}

void HostLess::AppMetadataUnpack(std::vector<u_int8_t>::iterator start, std::vector<u_int8_t>::iterator end)
{
    std::vector<u_int8_t> appMetadata(start, end);
    if (appMetadata.size() != REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE)
    {
        throw MlxDpaException("Invalid app metadata size in container.");
    }
    reg_access_hca_mcqi_dpa_metadata_ext_unpack(&_appMetadata, appMetadata.data());
}

void HostLess::SetElfData()
{
    ELFIO::elfio reader;

    if (!reader.load(_elfPath))
    {
        throw MlxDpaException("Failed to load ELF file");
    }
    std::ifstream singleElfFile(_elfPath, std::ios::binary | std::ios::ate);
    if (!singleElfFile)
    {
        throw MlxDpaException("Failed to open file '%s'", _elfPath.c_str());
    }
    std::streamsize sizeElf = singleElfFile.tellg();
    singleElfFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> dpaAppElf(sizeElf);
    if (!singleElfFile.read(reinterpret_cast<char*>(dpaAppElf.data()), sizeElf))
    {
        throw MlxDpaException("Failed to read file '%s'", _elfPath.c_str());
    }
    _elfData = dpaAppElf;
}

vector<u_int8_t> HostLess::GetElfData() const
{
    return _elfData;
}

size_t HostLess::GetElfSize() const
{
    return _elfData.size();
}

vector<u_int8_t> HostLess::GetAppMetadata() const
{
    vector<u_int8_t> appMetadata(REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE);
    reg_access_hca_mcqi_dpa_metadata_ext_pack(&_appMetadata, appMetadata.data());
    return appMetadata;
}

size_t HostLess::GetAppMetadataSize() const
{
    return REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE;
}

bool HostLess::ReadAndValidateAppMetadata(Yaml::Node& root, string appMetadataPath)
{
    bool isValid = true;
    if (mft_utils::IsFileEmpty(appMetadataPath, false))
    {
        throw MlxDpaException("YAML file is empty '%s'", appMetadataPath.c_str());
    }
    try
    {
        Yaml::Parse(root, appMetadataPath.c_str());
    }
    catch (const std::exception& e)
    {
        throw MlxDpaException("Failed to parse YAML file '%s': %s", appMetadataPath.c_str(), e.what());
    }
    if (!root.IsMap() || root.Size() == 0)
    {
        throw MlxDpaException("YAML file is invalid '%s'", appMetadataPath.c_str());
    }
    Yaml::Node new_root;
    for (auto it = root.Begin(); it != root.End(); it++)
    {
        std::string key = (*it).first;
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        new_root[key] = root[(*it).first];
    }
    root = new_root;
    // Check that all required arguments exist in the YAML node
    static const char* required_fields[] = {"dpa_app_subtype",    "type",
                                            "dpa_app_version",    "dpa_os_api_version",
                                            "dpa_fw_api_version", "dpa_app_description_string"};
    for (const char* field : required_fields)
    {
        auto val = root[field].As<std::string>();
        if (val.empty())
        {
            isValid = false;
        }
    }
    return isValid;
}

void HostLess::SetAppMetadataUUID()
{
    sole::uuid uuid = sole::uuid1();
    _uuid = uuid.str();

    // Remove dashes if present
    _uuid.erase(std::remove(_uuid.begin(), _uuid.end(), '-'), _uuid.end());
    // Pad to 32 hex chars if needed
    size_t uuid_size = 32;
    while (_uuid.length() < uuid_size)
        _uuid = "0" + _uuid;
    std::vector<u_int32_t> uuid_dwords = mft_utils::Uuid2Dword(_uuid);
    if (uuid_dwords.size() == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            _appMetadata.dpa_app_uuid[i] = uuid_dwords[i];
        }
    }
}

std::string HostLess::GetAppMetadataUUID() const
{
    return _uuid;
}

void HostLess::SetAppMetadataDescription(string desc)
{
    memset(_appMetadata.dpa_app_description_string, 0, sizeof(_appMetadata.dpa_app_description_string));
    if (!desc.empty())
    {
        size_t maxUint32Count = sizeof(_appMetadata.dpa_app_description_string) / sizeof(u_int32_t);
        size_t uint32Count = 0;
        for (size_t i = 0; i < desc.size() && uint32Count < maxUint32Count; i += 4)
        {
            u_int32_t value = 0;
            size_t chunkSize = std::min((size_t)4, desc.size() - i);
            for (size_t j = 0; j < chunkSize; ++j)
            {
                value <<= 8;
                value |= static_cast<unsigned char>(desc[i + j]);
            }
            _appMetadata.dpa_app_description_string[uint32Count++] = value;
        }
    }
}

void HostLess::SetAppMetadata(string appMetadataPath)
{
    Yaml::Node root;
    if (!ReadAndValidateAppMetadata(root, appMetadataPath))
    {
        throw MlxDpaException("Invalid app metadata file %s.", appMetadataPath.c_str());
    }
    _appMetadata.version = 0;
    _appMetadata.subtype = root["dpa_app_subtype"].As<u_int32_t>();
    _appMetadata.type = root["type"].As<u_int32_t>();
    _appMetadata.dpa_app_version = root["dpa_app_version"].As<u_int32_t>();
    _appMetadata.dpa_os_api_version = root["dpa_os_api_version"].As<u_int32_t>();
    _appMetadata.dpa_fw_api_version = root["dpa_fw_api_version"].As<u_int32_t>();
    _appMetadata.length = REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE;
    SetAppMetadataUUID();
    SetAppMetadataDescription(root["dpa_app_description_string"].As<string>());
}

bool HostLess::CheckHeaderPriority(BaseHeader::StructPriority priorityHeader)
{
    return priorityHeader == _priority;
}

void HostLess::SetManifest(std::string manifestPath)
{
    _isManifestPresent = false;
    _manifestData.clear();

    if (manifestPath.empty())
    {
        return;
    }
    _manifestData = mft_utils::ReadBinFile(manifestPath);
    if (!_manifestData.empty())
    {
        _isManifestPresent = true;
    }
}

vector<u_int8_t> HostLess::GetManifest() const
{
    return _manifestData;
}

bool HostLess::IsManifestPresent() const
{
    return _isManifestPresent;
}

size_t HostLess::GetManifestSize() const
{
    size_t manifestSize = 0;
    if (_isManifestPresent)
    {
        manifestSize = _manifestData.size();
    }
    return manifestSize;
}

DpaAppStructHeader HostLess::GetManifestHeader() const
{
    return _manifestHeader;
}

DpaAppStructHeader HostLess::GetElfHeader() const
{
    return _elfHeader;
}

DpaAppStructHeader HostLess::GetAppMetadataHeader() const
{
    return _appMetadataHeader;
}

bool HostLess::IsAppMetadataPresent() const
{
    return _isAppMetadataPresent;
}