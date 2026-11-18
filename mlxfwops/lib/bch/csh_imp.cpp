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
 *
 *  Version: $Id$
 *
 */

#include "csh_imp.h"

#ifndef MST_CPU_armv7l_umbriel // {
#include "mlxsign_lib/mlxsign_lib.h"
#include "mlxsign_lib/mlxsign_signer_interface.h"
#endif // } MST_CPU_armv7l_umbriel

#include "common/tools_json.h"
#include <algorithm>
#include <limits.h>

bool IsCshComponent(PartitionType partitionType)
{
    return partitionType == PartitionType::PT_ROM_IMGS || partitionType == PartitionType::PT_BCT_DTB ||
           partitionType == PartitionType::PT_OEM_FWS || partitionType == PartitionType::PT_NV_FWS ||
           partitionType == PartitionType::PT_SWITCH_FWS || partitionType == PartitionType::PT_SBD_FW;
}

string ToString(CshComponentID cshId)
{
    switch (cshId)
    {
        case CshComponentID::ROM_IMGS:
            return "ROM_IMGS";
        case CshComponentID::BCT_DTB:
            return "BCT_DTB";
        case CshComponentID::OEM_FWS:
            return "OEM_FWS";
        case CshComponentID::NV_FWS:
            return "NV_FWS";
        case CshComponentID::SWITCH_FWS:
            return "SWITCH_FWS";
        case CshComponentID::SBD_FW:
            return "SBD_FW";
        default:
            return "Unknown";
    }
}
vector<u_int8_t> PartitionTable::Pack()
{
    vector<u_int8_t> data = PackHeader();
    for (auto entry : _entries)
    {
        vector<u_int8_t> packedEntry = entry.Pack();
        data.insert(data.end(), packedEntry.begin(), packedEntry.end());
    }
    return data;
}

vector<u_int8_t> PartitionTable::PackHeader()
{
    vector<u_int8_t> header(fs5_image_layout_partition_table_header_size());
    fs5_image_layout_partition_table_header_pack(&_struct, header.data());
    return header;
}

void PartitionTable::UnpackHeader(const vector<u_int8_t>& data)
{
    if (data.size() < PartitionTable::HeaderSize())
    {
        throw runtime_error("Partition header size too small");
    }

    fs5_image_layout_partition_table_header_unpack(&_struct, data.data());
}

void PartitionTable::CalcDigest()
{
#ifndef MST_CPU_armv7l_umbriel // {
    vector<u_int8_t> data = Pack();
    data.erase(data.begin() + PARTITION_TABLE_DIGEST_OFFSET,
               data.begin() + PARTITION_TABLE_DIGEST_OFFSET + SHA384_DIGEST_LENGTH);

    vector<u_int8_t> digest;
    MlxSignSHA384 Sha384;
    Sha384 << data;
    Sha384.getDigest(digest);

    memcpy(_struct.sha384_hash.digest, digest.data(), digest.size());
#endif // } MST_CPU_armv7l_umbriel
}

void PartitionTable::AddEntry(const PartitionTableEntry& entry)
{
    _entries.push_back(entry);
}

void PartitionTable::SetEntrySize(PartitionType entryType, u_int32_t size)
{
    GetEntry(entryType).SetSectionSize(size);
}

u_int32_t PartitionTable::GetEntryOffset(PartitionType entryType)
{
    return GetEntry(entryType).GetStartOffset();
}

u_int32_t PartitionTable::GetEntrySize(PartitionType entryType)
{
    return GetEntry(entryType).GetSectionSize();
}

PartitionTableEntry& PartitionTable::GetEntry(PartitionType entryType)
{
    const auto compareFunc = [entryType](const PartitionTableEntry& entry)
    { return (PartitionType)entry.GetSectionType() == entryType; };

    auto entry = std::find_if(_entries.begin(), _entries.end(), compareFunc);
    if (entry == _entries.end())
    {
        throw runtime_error("couldn't find entry");
    }

    return *entry;
}

PartitionTableEntry::PartitionTableEntry(size_t offset, size_t size, u_int32_t type)
{
    memset(&_struct, 0, sizeof(_struct));
    _struct.start_address[0] = offset;
    _struct.partition_size[0] = size;
    _struct.partition_type = type;
}

vector<u_int8_t> PartitionTableEntry::Pack()
{
    vector<u_int8_t> metadata(fs5_image_layout_partition_table_entry_size());
    fs5_image_layout_partition_table_entry_pack(&_struct, metadata.data());
    return metadata;
}

void PartitionTableEntry::Unpack(const vector<u_int8_t>& data)
{
    if (data.size() != fs5_image_layout_partition_table_entry_size())
    {
        throw runtime_error("Partition entry unexpected size");
    }
    fs5_image_layout_partition_table_entry_unpack(&_struct, data.data());
}

void PartitionTableEntry::SetStartOffset(size_t offset)
{
    _struct.start_address[0] = offset;
}

void PartitionTableEntry::SetSectionSize(size_t size)
{
    _struct.partition_size[0] = size;
}

void PartitionTableEntry::SetSectionType(u_int32_t type)
{
    _struct.partition_type = type;
}

BinarySectionMetadata::BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest)
{
    memset(&_struct, 0, sizeof(_struct));
    _struct.bin_length = sectionSize;
    _struct.flash_offset = flashOffset;

    if (digest.size() != 48 /*GetLengthFromType(MlxSign::SHAType::SHA384)*/)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), digest.size());
}

BinarySectionMetadata::BinarySectionMetadata(u_int32_t itoc_type,
                                             size_t sectionSize,
                                             size_t flashOffset,
                                             const vector<u_int8_t>& digest)
{
    memset(&_struct, 0, sizeof(_struct));
    memcpy(_struct.u8_magic_id, &itoc_type, sizeof(itoc_type));
    _struct.bin_length = sectionSize;
    _struct.flash_offset = flashOffset;
    if (digest.size() != 48 /*GetLengthFromType(MlxSign::SHAType::SHA384)*/)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), digest.size());
};

vector<u_int8_t> BinarySectionMetadata::Pack()
{
    vector<u_int8_t> metadata(fs5_image_layout_binary_section_metadata_size());
    fs5_image_layout_binary_section_metadata_pack(&_struct, metadata.data());
    return metadata;
}

void BinarySectionMetadata::Unpack(const vector<u_int8_t>& binarySection)
{
    if (binarySection.size() != fs5_image_layout_binary_section_metadata_size())
    {
        throw runtime_error("Binary section unexpected size");
    }
    fs5_image_layout_binary_section_metadata_unpack(&_struct, binarySection.data());
}

void BinarySectionMetadata::SetJsonParams(const Json::Value& root)
{
    _struct.version.u8_ver_major = std::stoul(
      nbu::mft::common::GetStrValue(root["binary_section_metadata"]["version"]["ver_major"], true), nullptr, 16);
    _struct.version.u8_ver_minor = std::stoul(
      nbu::mft::common::GetStrValue(root["binary_section_metadata"]["version"]["ver_minor"], true), nullptr, 16);
    _struct.version.u8_ratchet_level = std::stoul(
      nbu::mft::common::GetStrValue(root["binary_section_metadata"]["version"]["ratchet_level"], true), nullptr, 16);
}

CSH::CSH() : _isUnpacked(false)
{
    memset(&_header, 0, sizeof(_header));
    memset(&_nv_signature, 0, sizeof(_nv_signature));
    memset(&_oem_signature, 0, sizeof(_nv_signature));
    memset(&_metadata, 0, sizeof(_metadata));
    memcpy(&_header.u8_header_magic, "NVDA", 4);
}

vector<u_int8_t> CSH::Pack()
{
    _metadata.num_of_binaries = _cshSections.size();

    vector<u_int8_t> cshHeader(CSH::HeaderSize());
    auto cshIter = cshHeader.data();
    fs5_image_layout_csh_header_pack(&_header, cshIter);
    cshIter += fs5_image_layout_csh_header_size();
    fs5_image_layout_csh_signature_pack(&_nv_signature, cshIter);
    cshIter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_signature_pack(&_oem_signature, cshIter);
    cshIter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_metadata_pack(&_metadata, cshIter);

    for (auto section : _cshSections)
    {
        vector<u_int8_t> metadata = section.Pack();
        cshHeader.insert(cshHeader.end(), metadata.begin(), metadata.end());
    }

    return cshHeader;
}

void CSH::Unpack(const vector<u_int8_t>& csh)
{
    UnpackHeader(csh);
    UnpackSections(csh, CSH::HeaderSize());
    _isUnpacked = true;
}

void CSH::UnpackHeader(const vector<u_int8_t>& cshHeader)
{
    if (cshHeader.size() < CSH::HeaderSize())
    {
        throw runtime_error("CSH header unexpected size");
    }
    auto iter = cshHeader.data();
    fs5_image_layout_csh_header_unpack(&_header, iter);
    iter += fs5_image_layout_csh_header_size();
    fs5_image_layout_csh_signature_unpack(&_nv_signature, iter);
    iter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_signature_unpack(&_oem_signature, iter);
    iter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_metadata_unpack(&_metadata, iter);
    memcpy(&_header.u8_header_magic, "NVDA", 4);

    if (!IsValidCompId(_metadata.component_id))
    {
        throw runtime_error("Unknown CSH Component ID " + std::to_string(_metadata.component_id));
    }
}

void CSH::UnpackSections(const vector<u_int8_t>& buffer, size_t offset)
{
    if (GetNumberOfBinaries() == 0)
    {
        throw runtime_error("Number of binary sections is zero.");
    }
    if (offset >= buffer.size() ||
        (buffer.size() - offset < GetNumberOfBinaries() * fs5_image_layout_binary_section_metadata_size()))
    {
        throw runtime_error("Buffer size for binary sections is too small.");
    }

    auto sectionIter = buffer.begin() + offset;
    for (size_t i = 0; i < GetNumberOfBinaries(); i++)
    {
        BinarySectionMetadata binary;
        binary.Unpack(vector<u_int8_t>(sectionIter, sectionIter + BinarySectionMetadata::Size()));
        _cshSections.push_back(binary);
        sectionIter += BinarySectionMetadata::Size();
    }
}

void CSH::AddBinarySectionMetadata(BinarySectionMetadata sectionMetadata)
{
    sectionMetadata.SetSectionOffset(GetComponentSize());
    _cshSections.push_back(sectionMetadata);
}

vector<u_int8_t> CSH::GetMetadata() const
{
    vector<u_int8_t> metadata(fs5_image_layout_csh_metadata_size());
    fs5_image_layout_csh_metadata_pack(&_metadata, metadata.data());
    return metadata;
}

size_t CSH::GetCshSize()
{
    bool isSingleSectionCSH = (CshComponentID)_metadata.component_id == CshComponentID::SWITCH_FWS ? false : true;
    return CSH::HeaderSize() + (isSingleSectionCSH ? 1 : 32) * BinarySectionMetadata::Size();
}

size_t CSH::GetComponentSize(bool withCshHeader)
{
    size_t componentSize = 0;
    size_t firstSectionOffset = SIZE_MAX;
    size_t lastSectionOffset = 0, lastSectionSize = 0;
    for (auto section : _cshSections)
    {
        if (section.GetSectionOffset() < firstSectionOffset)
        {
            firstSectionOffset = section.GetSectionOffset();
        }
        if (section.GetSectionOffset() > lastSectionOffset)
        {
            lastSectionOffset = section.GetSectionOffset();
            lastSectionSize = section.GetSectionSize();
        }
    }
    if (withCshHeader)
    {
        componentSize += GetCshSize();
    }
    if (!_cshSections.empty())
    {
        componentSize += lastSectionSize + lastSectionOffset - firstSectionOffset;
    }
    return componentSize;
}

void CSH::SetNvSignature(const vector<u_int8_t>& signature, SigType sigType)
{
    if (sigType == SigType::ECDSA)
    {
        if (signature.size() != CSH_ECDSA_SIG_SIZE)
        {
            throw runtime_error("Unsupported ECDSA signature size");
        }
        memcpy(_nv_signature.ecdsa_signature.u8_r, signature.data(), signature.size());
    }
    else
    {
        if (signature.size() != CSH_LMS_SIG_SIZE)
        {
            throw runtime_error("Unsupported LMS signature size");
        }
        memcpy(_nv_signature.crypto_lms_sha192_h20_w4_signature, signature.data(), signature.size());
    }
}

void CSH::SetOemSignature(const vector<u_int8_t>& signature, SigType sigType)
{
    if (sigType == SigType::ECDSA)
    {
        if (signature.size() != CSH_ECDSA_SIG_SIZE)
        {
            throw runtime_error("Unsupported ECDSA signature size");
        }
        memcpy(_oem_signature.ecdsa_signature.u8_r, signature.data(), signature.size());
    }
    else
    {
        if (signature.size() != CSH_LMS_SIG_SIZE)
        {
            throw runtime_error("Unsupported LMS signature size");
        }
        memcpy(_oem_signature.crypto_lms_sha192_h20_w4_signature, signature.data(), signature.size());
    }
}

void CSH::SetJsonParams(const Json::Value& root)
{
    if (root["csh_metadata"].empty())
    {
        printf("Couldn't find csh_metadata field.");
    }
    if (!_isUnpacked)
    {
        _metadata.component_id =
          std::stoul(nbu::mft::common::GetStrValue(root["csh_metadata"]["component_id"], true), nullptr, 16);
        if (!IsValidCompId(_metadata.component_id))
        {
            throw runtime_error("Unknown CSH Component ID in JSON file: " + std::to_string(_metadata.component_id));
        }
        _metadata.num_of_binaries = 1;
    }

    _metadata.version.u8_ver_major =
      std::stoul(nbu::mft::common::GetStrValue(root["csh_metadata"]["version"]["ver_major"], true), nullptr, 16);
    _metadata.version.u8_ver_minor =
      std::stoul(nbu::mft::common::GetStrValue(root["csh_metadata"]["version"]["ver_minor"], true), nullptr, 16);
    _metadata.version.u8_ratchet_level =
      std::stoul(nbu::mft::common::GetStrValue(root["csh_metadata"]["version"]["ratchet_level"], true), nullptr, 16);
}

bool CSH::IsValidCompId(u_int16_t id)
{
    switch ((CshComponentID)id)
    {
        case CshComponentID::ROM_IMGS:
        case CshComponentID::BCT_DTB:
        case CshComponentID::OEM_FWS:
        case CshComponentID::NV_FWS:
        case CshComponentID::SWITCH_FWS:
            return true;
        default:
            return false;
    }
}

size_t CSH::HeaderSize()
{
    return fs5_image_layout_csh_header_size() + fs5_image_layout_csh_signature_size() +
           fs5_image_layout_csh_signature_size() + fs5_image_layout_csh_metadata_size();
}
