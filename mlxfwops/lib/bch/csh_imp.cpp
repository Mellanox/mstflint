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

#include "../flint_base.h"
#include "common/tools_json.h"
#include "mft_utils/mft_utils.h"
#include <algorithm>
#include <limits.h>
#include <unordered_map>

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

string CshSectionIDToString(u_int32_t sectionId)
{
    char sectionName[5] = {0};
    memcpy(sectionName, &sectionId, 4);
    CPUTOn(sectionName, 1);
    string sectionNameStr(sectionName);

    if (sectionNameStr == "PBLT" || sectionNameStr == "PBLD" || sectionNameStr == "SBDF")
    {
        return sectionNameStr;
    }

    return mft_utils::ToHexString(sectionId, 4);
}

const string CSH::cshHeaderName = "csh_header";
const string CSH::cshMetadataName = "csh_metadata";
const string CSH::binarySectionMetadataName = "binary_section_metadata";

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
    CPUTOn(header.data(), header.size() / 4);
    return header;
}

void PartitionTable::UnpackHeader(const vector<u_int8_t>& data)
{
    if (data.size() < PartitionTable::HeaderSize())
    {
        throw runtime_error("Partition header size too small");
    }
    vector<u_int8_t> headerCopy = data;
    CPUTOn(headerCopy.data(), headerCopy.size() / 4);
    fs5_image_layout_partition_table_header_unpack(&_struct, headerCopy.data());
}

void PartitionTable::CalcDigest()
{
#ifndef MST_CPU_armv7l_umbriel // {
    vector<u_int8_t> data = Pack();
    data.erase(data.begin() + PARTITION_TABLE_DIGEST_OFFSET,
               data.begin() + PARTITION_TABLE_DIGEST_OFFSET + SHA384_DIGEST_SIZE);

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
    vector<u_int8_t> entry(fs5_image_layout_partition_table_entry_size());
    fs5_image_layout_partition_table_entry_pack(&_struct, entry.data());
    CPUTOn(entry.data(), entry.size() / 4);
    return entry;
}

void PartitionTableEntry::Unpack(const vector<u_int8_t>& data)
{
    if (data.size() != fs5_image_layout_partition_table_entry_size())
    {
        throw runtime_error("Partition entry unexpected size");
    }
    vector<u_int8_t> dataCopy = data;
    CPUTOn(dataCopy.data(), dataCopy.size() / 4);
    fs5_image_layout_partition_table_entry_unpack(&_struct, dataCopy.data());
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

u_int32_t BinarySectionMetadata::FromItocTypeToCshSectionType(u_int32_t itocType)
{
    static const std::unordered_map<u_int32_t, CshSectionType> itocTypeToCshSectionType = {
      {FS3_BOOT_CODE, CshSectionType::CSH_SECTION_BOOT2},
      {FS3_IMAGE_INFO, CshSectionType::CSH_SECTION_IMAGE_INFO},
      {FS3_HW_BOOT_CFG, CshSectionType::CSH_SECTION_HW_BOOT_INI},
      {FS3_FW_BOOT_CFG, CshSectionType::CSH_SECTION_FW_BOOT_INI},
      {FS3_PCIE_LINK_CODE, CshSectionType::CSH_SECTION_PRE_LINKUP},
      {FS3_PCI_CODE, CshSectionType::CSH_SECTION_POST_LINKUP},
      {FS3_CCIR_INFRA_CODE, CshSectionType::CSH_SECTION_HW_NON_ISFU_INI},
      {FS3_HW_MAIN_CFG, CshSectionType::CSH_SECTION_HW_MAIN_INI},
      {FS3_FW_MAIN_CFG, CshSectionType::CSH_SECTION_FW_MAIN_INI},
      {FS3_MFG_INFO, CshSectionType::CSH_SECTION_MFG_INFO},
      {FS3_POST_IRON_BOOT_CODE, CshSectionType::CSH_SECTION_POST_IRON_BOOT},
      {FS4_HW_TILE_INI, CshSectionType::CSH_SECTION_HW_TILE_INI},
      {FS4_FW_TILE_INI, CshSectionType::CSH_SECTION_FW_TILE_INI},
      {FS4_TILE_FW_CODE, CshSectionType::CSH_SECTION_SWITCH_TILE_CODE},
      {FS4_MAIN_DATA, CshSectionType::CSH_SECTION_PLASTIC_DATA},
      {FS4_MAIN_PAGES_LOCKED_HASHES, CshSectionType::CSH_SECTION_SWITCH_MAIN_HASH_SQUARE},
      {FS4_MAIN_PAGES_HASHES, CshSectionType::CSH_SECTION_SWITCH_MAIN_HASH},
      {FS3_MAIN_CODE, CshSectionType::CSH_SECTION_SWITCH_MAIN}};

    auto it = itocTypeToCshSectionType.find(itocType);
    return it != itocTypeToCshSectionType.end() ? static_cast<u_int32_t>(it->second) : itocType;
}

BinarySectionMetadata::BinarySectionMetadata()
{
    memset(&_struct, 0, sizeof(_struct));
}

BinarySectionMetadata::BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest)
{
    memset(&_struct, 0, sizeof(_struct));
    _struct.bin_length =
      sectionSize; // need to fix all other calls to BinarySectionMetadata so that what is being sent is the max size of
                   // the section, if such attr exists in .mlx field, and not the actual size of the bin
    _struct.flash_offset = flashOffset;

    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), digest.size());
}

BinarySectionMetadata::BinarySectionMetadata(u_int32_t itocType,
                                             u_int32_t loadDestinationLSB,
                                             u_int32_t loadDestinationMSB,
                                             u_int32_t entryPointLSB,
                                             u_int32_t entryPointMSB,
                                             size_t sectionSize,
                                             size_t flashOffset,
                                             const vector<u_int8_t>& digest)
{
    memset(&_struct, 0, sizeof(_struct));
    memcpy(_struct.u8_magic_id, &itocType, sizeof(itocType));
    _struct.load_dest[0] = loadDestinationLSB;
    _struct.load_dest[1] = loadDestinationMSB;
    _struct.entry_point[0] = entryPointLSB;
    _struct.entry_point[1] = entryPointMSB;
    _struct.bin_length = sectionSize;
    _struct.flash_offset = flashOffset;
    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), digest.size());
};

vector<u_int8_t> BinarySectionMetadata::Pack() const
{
    vector<u_int8_t> metadata(fs5_image_layout_binary_section_metadata_size());
    fs5_image_layout_binary_section_metadata_pack(&_struct, metadata.data());
    CPUTOn(metadata.data(), metadata.size() / 4);
    return metadata;
}

void BinarySectionMetadata::Unpack(const vector<u_int8_t>& binarySection)
{
    if (binarySection.size() != fs5_image_layout_binary_section_metadata_size())
    {
        throw runtime_error("Binary section unexpected size");
    }
    vector<u_int8_t> binarySectionCopy = binarySection;
    CPUTOn(binarySectionCopy.data(), binarySectionCopy.size() / 4);
    fs5_image_layout_binary_section_metadata_unpack(&_struct, binarySectionCopy.data());
}

u_int32_t BinarySectionMetadata::GetSectionType() const
{
    u_int32_t magic;
    memcpy(&magic, _struct.u8_magic_id, sizeof(magic));
    return magic;
}

string BinarySectionMetadata::GetMagicId() const
{
    string magic(_struct.u8_magic_id, _struct.u8_magic_id + 4);
    std::reverse(magic.begin(), magic.end());
    return magic;
}

void BinarySectionMetadata::SetDigest(const vector<u_int8_t>& digest)
{
    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), SHA384_DIGEST_SIZE);
}

void BinarySectionMetadata::SetJsonParams(const Json::Value& root, bool ignoreMagicId)
{
    const size_t MAGIC_ID_LEN = 4;
    const size_t ENCRYPTION_DERIVATION_STRING_LEN = 16;

    if (!ignoreMagicId)
    {
        // TODO validate magic ID after it's defined
        if (root["magic_id"].asString().length() != MAGIC_ID_LEN)
        {
            throw runtime_error("Invalid magic ID");
        }
        memcpy(_struct.u8_magic_id, root["magic_id"].asCString(), MAGIC_ID_LEN);
        CPUTOn(_struct.u8_magic_id, 1);
    }

    _struct.version.u8_ver_major =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_major"], true), nullptr, 16);
    _struct.version.u8_ver_minor =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_minor"], true), nullptr, 16);
    _struct.version.u8_ratchet_level =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ratchet_level"], true), nullptr, 16);

    _struct.load_dest[0] = std::stoul(nbu::mft::common::GetStrValue(root["load_dest"], true), nullptr, 16);
    _struct.entry_point[0] = std::stoul(nbu::mft::common::GetStrValue(root["entry_point"], true), nullptr, 16);

    vector<u_int8_t> buf =
      mft_utils::HexStringToBytes(root["encryption_params"]["encryption_derivation_string"].asString());
    if (buf.size() != ENCRYPTION_DERIVATION_STRING_LEN)
    {
        throw runtime_error("Invalid encryption derivation string");
    }
    memcpy(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy, buf.data(), buf.size());
    CPUTOn(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy, ENCRYPTION_DERIVATION_STRING_LEN / 4);

    _struct.encryption_params.u8_data_encryption_key_version = std::stoul(
      nbu::mft::common::GetStrValue(root["encryption_params"]["data_encryption_key_version"], true), nullptr, 16);
}

void BinarySectionMetadata::SetIV(const vector<u_int8_t>& iv)
{
    if (iv.size() != FS5_IMAGE_LAYOUT_U8_IV_SIZE)
    {
        throw runtime_error("Binary section IV unexpected size");
    }
    memcpy(_struct.encryption_params.u8_iv.u8_dummy, iv.data(), FS5_IMAGE_LAYOUT_U8_IV_SIZE);
    CPUTOn(_struct.encryption_params.u8_iv.u8_dummy, FS5_IMAGE_LAYOUT_U8_IV_SIZE / 4);
}

void BinarySectionMetadata::SetAuthenticationTag(const vector<u_int8_t>& tag)
{
    if (tag.size() != FS5_IMAGE_LAYOUT_U8_AUTH_TAG_SIZE)
    {
        throw runtime_error("Binary section authentication tag unexpected size");
    }
    memcpy(_struct.encryption_params.u8_auth_tag.u8_dummy, tag.data(), FS5_IMAGE_LAYOUT_U8_AUTH_TAG_SIZE);
    CPUTOn(_struct.encryption_params.u8_auth_tag.u8_dummy, FS5_IMAGE_LAYOUT_U8_AUTH_TAG_SIZE / 4);
}

vector<u_int8_t> CshMetadataNbu::Pack()
{
    vector<u_int8_t> metadata(fs5_image_layout_csh_metadata_nbu_size());
    fs5_image_layout_csh_metadata_nbu_pack(&_metadata_nbu, metadata.data());
    CPUTOn(metadata.data(), metadata.size() / 4);
    return metadata;
}

void CshMetadataNbu::Unpack(const vector<u_int8_t>& buffer)
{
    if (buffer.size() != fs5_image_layout_csh_metadata_nbu_size())
    {
        throw runtime_error("CSH metadata unexpected size");
    }
    fs5_image_layout_csh_metadata_nbu_unpack(&_metadata_nbu, buffer.data());
}

void CshMetadataNbu::SetBinariesListDigest(const vector<u_int8_t>& digest)
{
    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binaries list digest unexpected size");
    }
    memcpy(_metadata_nbu.binaries_list_digest.digest, digest.data(), SHA384_DIGEST_SIZE);
}

void CshMetadataNbu::SetJsonParams(const Json::Value& root)
{
    _metadata_nbu.version.ver_major =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_major"], true), nullptr, 16);
    _metadata_nbu.version.ver_minor =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_minor"], true), nullptr, 16);
    _metadata_nbu.nbu_subminor =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_subminor"], true), nullptr, 16);
    _metadata_nbu.version.ratchet_level =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ratchet_level"], true), nullptr, 16);
    _metadata_nbu.issu_ver_major = std::stoul(nbu::mft::common::GetStrValue(root["issu_ver_major"], true), nullptr, 16);
    _metadata_nbu.issu_ver_minor = std::stoul(nbu::mft::common::GetStrValue(root["issu_ver_minor"], true), nullptr, 16);
    _metadata_nbu.issu_notch = std::stoul(nbu::mft::common::GetStrValue(root["issu_notch"], true), nullptr, 16);
    _metadata_nbu.issuable = std::stoul(nbu::mft::common::GetStrValue(root["issuable"], true), nullptr, 16);
}

vector<u_int8_t> CshMetadata::Pack()
{
    vector<u_int8_t> metadata(fs5_image_layout_csh_metadata_size());
    fs5_image_layout_csh_metadata_pack(&_metadata, metadata.data());
    CPUTOn(metadata.data(), metadata.size() / 4);
    return metadata;
}

void CshMetadata::Unpack(const vector<u_int8_t>& buffer)
{
    if (buffer.size() != fs5_image_layout_csh_metadata_size())
    {
        throw runtime_error("CSH metadata unexpected size");
    }
    fs5_image_layout_csh_metadata_unpack(&_metadata, buffer.data());
}

void CshMetadata::SetBinariesListDigest(const vector<u_int8_t>& digest)
{
    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binaries list digest unexpected size");
    }
    memcpy(_metadata.binaries_list_digest.digest, digest.data(), SHA384_DIGEST_SIZE);
}

void CshMetadata::SetJsonParams(const Json::Value& root)
{
    _metadata.version.u8_ver_major =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_major"], true), nullptr, 16);
    _metadata.version.u8_ver_minor =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_minor"], true), nullptr, 16);
    _metadata.version.u8_ratchet_level =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ratchet_level"], true), nullptr, 16);
}

CSH::CSH() : _isUnpacked(false), _cshStructType(CshStructType::CSH_TB50X)
{
    InitMembers();
}

CSH::CSH(u_int16_t id, CshStructType type) : _isUnpacked(false), _cshStructType(type)
{
    InitMembers();
    _metadata->SetComponentId(id);
}

void CSH::InitMembers()
{
    memset(&_header, 0, sizeof(_header));
    memset(&_nv_signature, 0, sizeof(_nv_signature));
    memset(&_oem_signature, 0, sizeof(_nv_signature));
    if (_cshStructType == CshStructType::CSH_NBU)
    {
        _header.struct_version_major = 0x01;
        _metadata = unique_ptr<CshMetadataBase>(new CshMetadataNbu());
    }
    else
    {
        _metadata = unique_ptr<CshMetadataBase>(new CshMetadata());
    }
    memcpy(&_header.u8_header_magic, "ADVN", 4);
}

vector<u_int8_t> CSH::Pack()
{
    _metadata->SetNumberOfBinaries(_cshSections.size());

    vector<u_int8_t> cshData(fs5_image_layout_csh_header_size() + 2 * fs5_image_layout_csh_signature_size());
    auto cshIter = cshData.data();
    fs5_image_layout_csh_header_pack(&_header, cshIter);
    cshIter += fs5_image_layout_csh_header_size();
    fs5_image_layout_csh_signature_pack(&_nv_signature, cshIter);
    cshIter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_signature_pack(&_oem_signature, cshIter);
    CPUTOn(cshData.data(), cshData.size() / 4);

    vector<u_int8_t> metadata = _metadata->Pack();
    cshData.insert(cshData.end(), metadata.begin(), metadata.end());

    for (auto section : _cshSections)
    {
        vector<u_int8_t> metadata = section.Pack();
        cshData.insert(cshData.end(), metadata.begin(), metadata.end());
    }

    //* switch_fws is fixed as 32 sections, must keep the reserved space
    // TODO remove this once switch_fws isn't fixed as 32 sections
    if (cshData.size() < GetCshSize())
    {
        cshData.resize(GetCshSize());
    }

    return cshData;
}

void CSH::Unpack(const vector<u_int8_t>& csh)
{
    UnpackHeader(csh);
    UnpackSections(csh, CSH::HeaderSize(_cshStructType));
    _isUnpacked = true;
}

void CSH::UnpackHeader(const vector<u_int8_t>& cshHeader)
{
    _cshStructType = GetCshStructType(cshHeader);

    if (cshHeader.size() < CSH::HeaderSize(_cshStructType) || cshHeader.size() % 4 != 0)
    {
        throw runtime_error("CSH header unexpected size");
    }
    vector<u_int8_t> cshHeaderCopy = cshHeader;
    CPUTOn(cshHeaderCopy.data(), cshHeaderCopy.size() / 4);

    auto iter = cshHeaderCopy.data();
    fs5_image_layout_csh_header_unpack(&_header, iter);
    iter += fs5_image_layout_csh_header_size();
    fs5_image_layout_csh_signature_unpack(&_nv_signature, iter);
    iter += fs5_image_layout_csh_signature_size();
    fs5_image_layout_csh_signature_unpack(&_oem_signature, iter);
    iter += fs5_image_layout_csh_signature_size();

    UnpackCshMetadata(cshHeaderCopy, iter);

    memcpy(&_header.u8_header_magic, "ADVN", 4);

    if (!IsValidCompId(_metadata->GetComponentId()))
    {
        throw runtime_error("Unknown CSH Component ID 0x" + std::to_string(_metadata->GetComponentId()));
    }
}

void CSH::UnpackCshMetadata(const vector<u_int8_t>& cshHeader, const u_int8_t* iter)
{
    if (_cshStructType == CshStructType::CSH_NBU)
    {
        _metadata = unique_ptr<CshMetadataBase>(new CshMetadataNbu());
        _metadata->Unpack(vector<u_int8_t>(iter, iter + fs5_image_layout_csh_metadata_nbu_size()));
    }
    else
    {
        _metadata = unique_ptr<CshMetadataBase>(new CshMetadata());
        _metadata->Unpack(vector<u_int8_t>(iter, iter + fs5_image_layout_csh_metadata_size()));
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

void CSH::AddBinarySectionMetadata(BinarySectionMetadata sectionMetadata, bool updateSectionsOffsets)
{
    if (updateSectionsOffsets && (CshComponentID)_metadata->GetComponentId() != CshComponentID::SWITCH_FWS)
    {
        //* for an empty CSH, first section offset must pushed back by BinarySectionMetadata size
        sectionMetadata.SetSectionOffset(GetComponentSize() + BinarySectionMetadata::Size());
        for (auto& section : _cshSections)
        {
            section.SetSectionOffset(section.GetSectionOffset() + BinarySectionMetadata::Size());
        }
    }
    _cshSections.push_back(sectionMetadata);
}

vector<u_int8_t> CSH::PackMetadata() const
{
    return _metadata->Pack();
}

size_t CSH::GetCshSize()
{
    if (_metadata->GetComponentId() == 0x0)
    {
        throw runtime_error("CSH component ID is not set");
    }
    bool isSwitchFws = (CshComponentID)_metadata->GetComponentId() == CshComponentID::SWITCH_FWS;
    return CSH::HeaderSize(_cshStructType) + (isSwitchFws ? 32 : _cshSections.size()) * BinarySectionMetadata::Size();
}

size_t CSH::GetComponentSize()
{
    size_t componentSize = GetCshSize();
    if (!_cshSections.empty())
    {
        size_t lastSectionOffset = 0, lastSectionSize = 0;
        for (auto section : _cshSections)
        {
            if (section.GetSectionOffset() > lastSectionOffset)
            {
                lastSectionOffset = section.GetSectionOffset();
                lastSectionSize = section.GetSectionSize();
            }
        }
        componentSize = lastSectionSize + lastSectionOffset;
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
        //* PSC expects R and S parts reversed for authentication
        std::reverse(_nv_signature.ecdsa_signature.u8_r, _nv_signature.ecdsa_signature.u8_r + (CSH_ECDSA_SIG_SIZE / 2));
        std::reverse(_nv_signature.ecdsa_signature.u8_s, _nv_signature.ecdsa_signature.u8_s + (CSH_ECDSA_SIG_SIZE / 2));
        CPUTOn(_nv_signature.ecdsa_signature.u8_r, signature.size() / 4);
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
        //* PSC expects R and S parts reversed for authentication
        std::reverse(_oem_signature.ecdsa_signature.u8_r,
                     _oem_signature.ecdsa_signature.u8_r + (CSH_ECDSA_SIG_SIZE / 2));
        std::reverse(_oem_signature.ecdsa_signature.u8_s,
                     _oem_signature.ecdsa_signature.u8_s + (CSH_ECDSA_SIG_SIZE / 2));
        CPUTOn(_oem_signature.ecdsa_signature.u8_r, signature.size() / 4);
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

void CSH::SetSingleSectionFromJson(const Json::Value& root)
{
    if (!root.isMember("magic_id"))
    {
        throw runtime_error("Missing magic_id in binary_section_metadata");
    }
    string magicId = root["magic_id"].asString();
    if (magicId.empty() || magicId.length() != 4)
    {
        throw runtime_error("Invalid section Magic ID");
    }

    auto section =
      std::find_if(_cshSections.begin(),
                   _cshSections.end(),
                   [&magicId](const BinarySectionMetadata& section) { return section.GetMagicId() == magicId; });
    if (section == _cshSections.end())
    {
        throw runtime_error("Magic ID not found in CSH: " + magicId);
    }

    section->SetJsonParams(root);
}

void CSH::SetSectionsFromJson(const Json::Value& root, bool ignoreMagicId)
{
    for (auto section : _cshSections)
    {
        section.SetJsonParams(root, ignoreMagicId);
    }
}

void CSH::SetJsonParams(const Json::Value& root)
{
    if (root[cshMetadataName].empty())
    {
        throw runtime_error("Couldn't find csh_metadata field in JSON file.");
    }
    if (root[binarySectionMetadataName].empty())
    {
        throw runtime_error("Couldn't find binary_section_metadata field in JSON file.");
    }

    bool isSwitchCsh = (CshComponentID)_metadata->GetComponentId() == CshComponentID::SWITCH_FWS;

    for (auto jsonField = root.begin(); jsonField != root.end(); jsonField++)
    {
        string jsonFieldName = jsonField.name();
        if (jsonFieldName == binarySectionMetadataName)
        {
            if (root[binarySectionMetadataName].isArray())
            {
                if (isSwitchCsh)
                {
                    throw runtime_error("SWITCH_FWS component supports only single section JSON");
                }
                if (root[binarySectionMetadataName].size() != _cshSections.size())
                {
                    throw runtime_error("Number of sections in JSON doesn't match number of sections in CSH");
                }
                for (Json::ArrayIndex i = 0; i < root[binarySectionMetadataName].size(); i++)
                {
                    SetSingleSectionFromJson(root[binarySectionMetadataName][i]);
                }
            }
            else
            {
                SetSectionsFromJson(root[binarySectionMetadataName], isSwitchCsh);
            }
        }
        else if (jsonFieldName == cshMetadataName)
        {
            _metadata->SetJsonParams(root[cshMetadataName]);
        }
        else if (jsonFieldName == cshHeaderName)
        {
            SetHeaderFromJson(root[cshHeaderName]);
        }
        else
        {
            throw runtime_error("Invalid field name: " + jsonFieldName);
        }
    }
}

void CSH::CalcDigest()
{
#ifndef MST_CPU_armv7l_umbriel // {
    vector<u_int8_t> data;
    for (auto section : _cshSections)
    {
        vector<u_int8_t> sectionData = section.Pack();
        data.insert(data.end(), sectionData.begin(), sectionData.end());
    }

    vector<u_int8_t> digest;
    MlxSignSHA384 Sha384;
    Sha384 << data;
    Sha384.getDigest(digest);

    _metadata->SetBinariesListDigest(digest);
#endif // } MST_CPU_armv7l_umbriel
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
        case CshComponentID::SBD_FW:
        case CshComponentID::RECOVERY_IMAGE:
            return true;
        default:
            return false;
    }
}

CSH::CshStructType CSH::GetCshStructType(const vector<u_int8_t>& cshHeader)
{
    const string cshMagic = "NVDA";
    if (cshHeader.size() < fs5_image_layout_csh_header_size())
    {
        throw runtime_error("CSH header unexpected size");
    }
    if (string(cshHeader.begin(), cshHeader.begin() + 4) != cshMagic)
    {
        throw runtime_error("CSH header magic is not NVDA");
    }

    CshStructType type = CshStructType::CSH_TB50X;
    struct fs5_image_layout_csh_header header;
    memset(&header, 0, sizeof(header));
    vector<u_int8_t> headerCopy = cshHeader;
    CPUTOn(headerCopy.data(), headerCopy.size() / 4);

    fs5_image_layout_csh_header_unpack(&header, headerCopy.data());
    if (header.struct_version_major == 0x1 && header.struct_version_minor == 0x0)
    {
        type = CshStructType::CSH_NBU;
    }
    return type;
}

size_t CSH::HeaderSize(CshStructType type)
{
    size_t size = fs5_image_layout_csh_header_size() + fs5_image_layout_csh_signature_size() +
                  fs5_image_layout_csh_signature_size();
    if (type == CshStructType::CSH_TB50X)
    {
        size += fs5_image_layout_csh_metadata_size();
    }
    else
    {
        size += fs5_image_layout_csh_metadata_nbu_size();
    }
    return size;
}

void CSH::SetHeaderFromJson(const Json::Value& root)
{
    _header.u8_nv_pub_key_idx = std::stoul(nbu::mft::common::GetStrValue(root["u8_nv_pub_key_idx"], true), nullptr, 16);
}
