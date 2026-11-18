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
           partitionType == PartitionType::PT_CALIPTRA_FW || partitionType == PartitionType::PT_NV_FWS ||
           partitionType == PartitionType::PT_SWITCH_FWS || partitionType == PartitionType::PT_SBD_FW ||
           partitionType == PartitionType::PT_VMOD_FW;
}

bool IsPartitionTypeMaxSize(PartitionType partitionType)
{
    return partitionType == PartitionType::PT_ROM_IMGS || partitionType == PartitionType::PT_CHAIN_CONTAINER ||
           partitionType == PartitionType::PT_VMOD_FW || partitionType == PartitionType::PT_CPO_CALIBRATION_DATA;
}

CshComponentID ToCshId(PartitionType partitionType)
{
    CshComponentID cshId = CshComponentID::Unknown;
    switch (partitionType)
    {
        case PartitionType::PT_ROM_IMGS:
            cshId = CshComponentID::ROM_IMGS;
            break;
        case PartitionType::PT_BCT_DTB:
            cshId = CshComponentID::BCT_DTB;
            break;
        case PartitionType::PT_CALIPTRA_FW:
            cshId = CshComponentID::CALIPTRA_FW;
            break;
        case PartitionType::PT_NV_FWS:
            cshId = CshComponentID::NV_FWS;
            break;
        case PartitionType::PT_SWITCH_FWS:
            cshId = CshComponentID::SWITCH_FWS;
            break;
        case PartitionType::PT_SBD_FW:
            cshId = CshComponentID::SBD_FW;
            break;
        default:
            throw runtime_error("Partition type " + to_string((u_int32_t)partitionType) + " is not a CSH component");
    }
    return cshId;
}

string ToString(CshComponentID cshId)
{
    switch (cshId)
    {
        case CshComponentID::ROM_IMGS:
            return CSH::ROM_IMGS_NAME;
        case CshComponentID::BCT_DTB:
            return CSH::BCT_DTB_NAME;
        case CshComponentID::OEM_FWS: // TODO backwards compatibility - remove after FS6 is fully adopted
            return CSH::OEM_FWS_NAME;
        case CshComponentID::NV_FWS:
            return CSH::NV_FWS_NAME;
        case CshComponentID::SWITCH_FWS:
            return CSH::SWITCH_FWS_NAME;
        case CshComponentID::SBD_FW:
            return CSH::SBD_FW_NAME;
        case CshComponentID::VMOD_FW:
            return CSH::VMOD_FW_NAME;
        case CshComponentID::CALIPTRA_FW:
            return CSH::CALIPTRA_FW_NAME;
        default:
            return "Unknown";
    }
}

CshComponentID ToCshId(string cshId)
{
    if (cshId == CSH::ROM_IMGS_NAME)
    {
        return CshComponentID::ROM_IMGS;
    }
    if (cshId == CSH::BCT_DTB_NAME)
    {
        return CshComponentID::BCT_DTB;
    }
    if (cshId == CSH::OEM_FWS_NAME)
    {
        return CshComponentID::OEM_FWS; // TODO backwards compatibility - remove after FS6 is fully adopted
    }
    if (cshId == CSH::NV_FWS_NAME)
    {
        return CshComponentID::NV_FWS;
    }
    if (cshId == CSH::SWITCH_FWS_NAME)
    {
        return CshComponentID::SWITCH_FWS;
    }
    if (cshId == CSH::SBD_FW_NAME)
    {
        return CshComponentID::SBD_FW;
    }
    if (cshId == CSH::VMOD_FW_NAME)
    {
        return CshComponentID::VMOD_FW;
    }
    if (cshId == CSH::CALIPTRA_FW_NAME)
    {
        return CshComponentID::CALIPTRA_FW;
    }
    return CshComponentID::Unknown;
}

const string CSH::cshHeaderName = "csh_header";
const string CSH::cshMetadataName = "csh_metadata";
const string CSH::binarySectionMetadataName = "binary_section_metadata";

const string CSH::ROM_IMGS_NAME = "ROM_IMGS";
const string CSH::BCT_DTB_NAME = "BCT_DTB";
const string CSH::OEM_FWS_NAME = "OEM_FWS";
const string CSH::NV_FWS_NAME = "NV_FWS";
const string CSH::SWITCH_FWS_NAME = "SWITCH_FWS";
const string CSH::SBD_FW_NAME = "SBD_FW";
const string CSH::VMOD_FW_NAME = "VMOD_FW";
const string CSH::CALIPTRA_FW_NAME = "CALIPTRA_FW";

CshException::CshException(CshExceptionType type, const char* fmt, ...) : _type(type)
{
    const unsigned int max = 1024;
    char tmp[max];
    va_list args;

    va_start(args, fmt);
    vsnprintf(tmp, max, fmt, args);
    va_end(args);
    _msg = tmp;
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
    data.erase(data.begin(), data.begin() + HeaderSize());

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

void PartitionTable::SetEntrySize(PartitionType entryType, u_int32_t size, int chainNumber)
{
    ResolveChainNumber(chainNumber, _activeChain);
    GetEntry(entryType, chainNumber).SetSectionSize(size);
}

u_int32_t PartitionTable::GetEntryOffset(PartitionType entryType, int chainNumber)
{
    ResolveChainNumber(chainNumber, _activeChain);
    return GetEntry(entryType, chainNumber).GetStartOffset();
}

u_int32_t PartitionTable::GetEntrySize(PartitionType entryType, int chainNumber)
{
    ResolveChainNumber(chainNumber, _activeChain);
    return GetEntry(entryType, chainNumber).GetSectionSize();
}

PartitionTableEntry& PartitionTable::GetEntry(PartitionType entryType, int chainNumber)
{
    bool useChainFilter = (entryType == PartitionType::PT_ROM_IMGS || entryType == PartitionType::PT_CHAIN_CONTAINER);
    ResolveChainNumber(chainNumber, _activeChain);

    const auto compareFunc = [entryType, useChainFilter, chainNumber](const PartitionTableEntry& entry)
    {
        if (entry.GetPartitionTypeEnum() != entryType)
            return false;
        if (useChainFilter)
            return entry.GetChainNumber() == chainNumber;
        return true;
    };

    auto entry = std::find_if(_entries.begin(), _entries.end(), compareFunc);
    if (entry == _entries.end())
    {
        {
            std::ostringstream oss;
            oss << "couldn't find entry 0x" << std::hex << std::uppercase << (u_int32_t)entryType;
            throw runtime_error(oss.str());
        }
    }

    return *entry;
}

int PartitionTable::GetEntryIndex(PartitionType entryType, int chainNumber)
{
    bool useChainFilter = (entryType == PartitionType::PT_ROM_IMGS || entryType == PartitionType::PT_CHAIN_CONTAINER);
    ResolveChainNumber(chainNumber, _activeChain);

    const auto compareFunc = [entryType, useChainFilter, chainNumber](const PartitionTableEntry& entry)
    {
        if (entry.GetPartitionTypeEnum() != entryType)
            return false;
        if (useChainFilter)
            return entry.GetChainNumber() == chainNumber;
        return true;
    };

    auto it = std::find_if(_entries.begin(), _entries.end(), compareFunc);
    if (it == _entries.end())
    {
        return -1; // Not found
    }

    return std::distance(_entries.begin(), it);
}

size_t PartitionTable::GetEntryTableOffset(PartitionType entryType, int chainNumber)
{
    int index = GetEntryIndex(entryType, chainNumber);
    if (index < 0)
    {
        throw runtime_error("couldn't find entry");
    }
    return HeaderSize() + index * PartitionTableEntry::Size();
}

bool PartitionTableEntry::IsCshActiveChain() const
{
    return _csh != nullptr && _csh->isActiveChain();
}

bool PartitionTableEntry::IsCshBackupChain() const
{
    return _csh != nullptr && _csh->isBackupChain();
}

PartitionTableEntry::PartitionTableEntry(size_t offset, size_t size, u_int32_t type)
{
    memset(&_struct, 0, sizeof(_struct));
    _struct.start_address[0] = offset;
    _struct.partition_size[0] = size;
    _struct.partition_type = type;
    _csh = nullptr;
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

int PartitionTableEntry::GetChainNumber() const
{
    return (_struct.partition_attr[0] & 0x0E) >> 1; // bits 1-3: boot-chain to which this partition belongs (valid only
                                                    // for ROM_IMGS and CHAIN_CONTAINER in L1PT).
}

void PartitionTableEntry::SetStartOffset(size_t offset)
{
    _struct.start_address[0] = offset;
}

void PartitionTableEntry::SetSectionSize(size_t size)
{
    _struct.partition_size[0] = size;
}

void PartitionTableEntry::SetPartitionType(u_int32_t type)
{
    _struct.partition_type = type;
}

u_int32_t PartitionTableEntry::GetPartitionType() const
{
    return _struct.partition_type;
}

PartitionType PartitionTableEntry::GetPartitionTypeEnum() const
{
    return static_cast<PartitionType>(_struct.partition_type);
}

string BinarySectionMetadata::CshSectionIDToString(u_int32_t sectionId)
{
    static const std::unordered_map<string, string> ncoreSectionNamesMap = {{"BOT2", "BOOT_CODE"},
                                                                            {"IINF", "IMAGE_INFO"},
                                                                            {"HWBI", "HW_BOOT_CFG"},
                                                                            {"FWBI", "FW_BOOT_CFG"},
                                                                            {"PREL", "PCIE_LINK_CODE"},
                                                                            {"IRON", "PCI_CODE"},
                                                                            {"HNII", "CCIR_INFRA_CODE"},
                                                                            {"HWMI", "HW_MAIN_CFG"},
                                                                            {"FWMI", "FW_MAIN_CFG"},
                                                                            {"PSTI", "POST_IRON_BOOT_CODE"},
                                                                            {"HWTI", "HW_TILE_INI"},
                                                                            {"FWTI", "FW_TILE_INI"},
                                                                            {"TSQR", "TILE_PAGES_LOCKED_HASHES"},
                                                                            {"THSH", "TILE_PAGES_HASHES"},
                                                                            {"TILE", "TILE_FW_CODE"},
                                                                            {"PLDT", "MAIN_DATA"},
                                                                            {"MSQR", "MAIN_PAGES_LOCKED_HASHES"},
                                                                            {"MHSH", "MAIN_PAGES_HASHES"},
                                                                            {"MAIN", "MAIN_CODE"},
                                                                            {"NKRL", "NANO_KERNEL"},
                                                                            {"VMOD", "VMOD_FW_IMG"},
                                                                            {"VMDI", "VMOD_IMAGE_INFO"},
                                                                            {"VMDH", "VMOD_PAGES_HASHES"},
                                                                            {"VMHS", "VMOD_PAGES_LOCKED_HASHES"}};
    static const std::vector<string> nonNcoreSectionNames = {
      "PBLT", "PBLD", "PFWT", "PFWD", "SBDF", "CALF",
    };

    char sectionName[5] = {0};
    memcpy(sectionName, &sectionId, 4);
    CPUTOn(sectionName, 1);
    string sectionNameStr(sectionName);

    if (ncoreSectionNamesMap.find(sectionNameStr) != ncoreSectionNamesMap.end())
    {
        sectionNameStr = ncoreSectionNamesMap.at(sectionNameStr);
    }
    else if (std::find(nonNcoreSectionNames.begin(), nonNcoreSectionNames.end(), sectionNameStr) ==
             nonNcoreSectionNames.end())
    {
        sectionNameStr = "UNKNOWN";
    }

    return sectionNameStr;
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
      {FS6_TILE_PAGES_HASHES, CshSectionType::CSH_SECTION_SWITCH_TILE_CODE_HASH},
      {FS6_TILE_PAGES_LOCKED_HASHES, CshSectionType::CSH_SECTION_SWITCH_TILE_CODE_HASH_SQUARE},
      {FS4_MAIN_DATA, CshSectionType::CSH_SECTION_PLASTIC_DATA},
      {FS4_MAIN_PAGES_LOCKED_HASHES, CshSectionType::CSH_SECTION_SWITCH_MAIN_HASH_SQUARE},
      {FS4_MAIN_PAGES_HASHES, CshSectionType::CSH_SECTION_SWITCH_MAIN_HASH},
      {FS3_MAIN_CODE, CshSectionType::CSH_SECTION_SWITCH_MAIN},
      {FS6_NANO_KERNEL, CshSectionType::CSH_SECTION_NANO_KERNEL}};

    auto it = itocTypeToCshSectionType.find(itocType);
    return it != itocTypeToCshSectionType.end() ? static_cast<u_int32_t>(it->second) : itocType;
}

BinarySectionMetadata::BinarySectionMetadata() : _isIVSet(false)
{
    memset(&_struct, 0, sizeof(_struct));
}

BinarySectionMetadata::BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest) :
    _isIVSet(false)
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
                                             const vector<u_int8_t>& digest) :
    _isIVSet(false)
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
    string magic(begin(_struct.u8_magic_id), end(_struct.u8_magic_id));
    std::reverse(magic.begin(), magic.end());
    return magic;
}

vector<u_int8_t> BinarySectionMetadata::GetMagicIdAsVector() const
{
    vector<u_int8_t> sectionMagicId(begin(_struct.u8_magic_id), end(_struct.u8_magic_id));
    std::reverse(sectionMagicId.begin(), sectionMagicId.end());
    return sectionMagicId;
}

void BinarySectionMetadata::SetDigest(const vector<u_int8_t>& digest)
{
    if (digest.size() != SHA384_DIGEST_SIZE)
    {
        throw runtime_error("Binary section digest unexpected size");
    }
    memcpy(_struct.bin_digest.digest, digest.data(), SHA384_DIGEST_SIZE);
}

void BinarySectionMetadata::SetJsonParams(const Json::Value& root)
{
    _struct.version.u8_ver_major =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_major"], true), nullptr, 16);
    _struct.version.u8_ver_minor =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ver_minor"], true), nullptr, 16);
    _struct.version.u8_ratchet_level =
      std::stoul(nbu::mft::common::GetStrValue(root["version"]["ratchet_level"], true), nullptr, 16);

    if (root.isMember("load_dest"))
    {
        SetDwordsFrom8BytesJsonField(root, "load_dest", _struct.load_dest[0], _struct.load_dest[1]);
    }

    if (root.isMember("entry_point"))
    {
        SetDwordsFrom8BytesJsonField(root, "entry_point", _struct.entry_point[0], _struct.entry_point[1]);
    }

    vector<u_int8_t> buf =
      mft_utils::HexStringToBytes(root["encryption_params"]["encryption_derivation_string"].asString());
    if (buf.size() != FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE)
    {
        throw runtime_error("Invalid encryption derivation string");
    }
    memcpy(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy, buf.data(), buf.size());
    CPUTOn(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy, buf.size() / 4);

    if (root["encryption_params"].isMember("iv"))
    {
        buf = mft_utils::HexStringToBytes(root["encryption_params"]["iv"].asString());
        if (buf.size() != FS5_IMAGE_LAYOUT_U8_IV_SIZE)
        {
            throw runtime_error("Invalid IV");
        }
        memcpy(_struct.encryption_params.u8_iv.u8_dummy, buf.data(), buf.size());
        CPUTOn(_struct.encryption_params.u8_iv.u8_dummy, buf.size() / 4);
        _isIVSet = true;
    }
}

void BinarySectionMetadata::SetDwordsFrom8BytesJsonField(const Json::Value& root,
                                                         const string& fieldName,
                                                         u_int32_t& firstField,
                                                         u_int32_t& secondField)
{
    string fieldStr = nbu::mft::common::GetStrValue(root[fieldName], true);
    if (fieldStr.size() > 16)
    {
        throw runtime_error("Invalid field size");
    }
    std::tuple<string, string> fieldStrs = mft_utils::Split16CharsHexStringToDwords(fieldStr);
    firstField = std::strtoul(std::get<0>(fieldStrs).c_str(), nullptr, 16);
    secondField = std::strtoul(std::get<1>(fieldStrs).c_str(), nullptr, 16);
}

vector<u_int8_t> BinarySectionMetadata::GetDerivationString() const
{
    vector<u_int8_t> derivationString(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy,
                                      _struct.encryption_params.u8_encryption_derivation_string.u8_dummy +
                                        FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE);
    CPUTOn(derivationString.data(), derivationString.size() / 4);
    return derivationString;
}

vector<u_int8_t> BinarySectionMetadata::GetVersionAsVector() const
{
    vector<u_int8_t> version(4, 0);
    memcpy(version.data(), &_struct.version, 4);
    return version;
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

vector<u_int8_t> BinarySectionMetadata::GetIV() const
{
    vector<u_int8_t> iv(begin(_struct.encryption_params.u8_iv.u8_dummy), end(_struct.encryption_params.u8_iv.u8_dummy));
    CPUTOn(iv.data(), iv.size() / 4);
    return iv;
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

void CshMetadataNbu::SetDependencyList(const Json::Value& root)
{
    const size_t MAX_DEPENDENCY_LIST_SIZE = 8;
    if (root.size() > MAX_DEPENDENCY_LIST_SIZE)
    {
        throw runtime_error("Dependency list unexpected size");
    }
    size_t i = 0;
    for (auto jsonField = root.begin(); jsonField != root.end(); jsonField++)
    {
        string jsonFieldName = jsonField.name();
        CshComponentID cshId = ToCshId(jsonFieldName);
        if (cshId == CshComponentID::Unknown)
        {
            throw runtime_error("Unknown CSH component name in dependency list: " + jsonFieldName);
        }
        _metadata_nbu.dependency_list[i].component_id = static_cast<u_int16_t>(cshId);
        _metadata_nbu.dependency_list[i].min_major_version =
          std::stoul(nbu::mft::common::GetStrValue(root[jsonFieldName]["ver_major"], true), nullptr, 16);
        _metadata_nbu.dependency_list[i].min_minor_version =
          std::stoul(nbu::mft::common::GetStrValue(root[jsonFieldName]["ver_minor"], true), nullptr, 16);
        i++;
    }
}

void CshMetadataNbu::SetEcid(const Json::Value& root)
{
    const size_t NUM_OF_ECID_VALUES = 4;
    if (root.size() > NUM_OF_ECID_VALUES)
    {
        throw runtime_error("Invalid ECID array length");
    }

    size_t i = 0;
    for (auto jsonField = root.begin(); jsonField != root.end(); jsonField++)
    {
        vector<u_int8_t> buf = mft_utils::HexStringToBytes(jsonField->asString());
        if (buf.size() != FS5_IMAGE_LAYOUT_U8_ECID_SIZE)
        {
            throw runtime_error("Invalid ECID value length for index " + std::to_string(i));
        }
        memcpy(&_metadata_nbu.ecid[i], buf.data(), buf.size());
        CPUTOn(&_metadata_nbu.ecid[i], buf.size() / 4);
        i++;
    }
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
    _metadata_nbu.fw_lifecycle = std::stoul(nbu::mft::common::GetStrValue(root["fw_lifecycle"], true), nullptr, 16);
    if (root.isMember("dependency_list"))
    {
        SetDependencyList(root["dependency_list"]);
    }
    if (root.isMember("ecid"))
    {
        SetEcid(root["ecid"]);
    }
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
        std::stringstream ss;
        ss << "Unknown CSH Component ID 0x" << std::hex << std::uppercase << _metadata->GetComponentId();
        throw runtime_error(ss.str());
    }
    if (_metadata->GetComponentId() == (u_int16_t)CshComponentID::VMOD_FW)
    {
        CPUTOn(&_header.csh_header_status.vmod_status, sizeof(_header.csh_header_status.vmod_status));
    }
}

bool CSH::isActiveChain()
{
    const auto& romImgsCandidateMagicPatternBE = PartitionTable::RomImgsCandidateMagicPatternBE();
    if (std::equal(romImgsCandidateMagicPatternBE.begin(), romImgsCandidateMagicPatternBE.end(),
                   _header.csh_header_status.magic_pattern.magic_pattern))
    {
        return true;
    }
    return false;
}

bool CSH::isBackupChain()
{
    const auto& romImgsBackupMagicPatternBE = PartitionTable::RomImgsBackupMagicPatternBE();
    if (std::equal(romImgsBackupMagicPatternBE.begin(), romImgsBackupMagicPatternBE.end(),
                   _header.csh_header_status.magic_pattern.magic_pattern))
    {
        return true;
    }
    return false;
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
    if (updateSectionsOffsets && (CshComponentID)_metadata->GetComponentId() != CshComponentID::SWITCH_FWS &&
        (CshComponentID)_metadata->GetComponentId() != CshComponentID::VMOD_FW)
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

size_t CSH::GetCshSize() const
{
    if (_metadata->GetComponentId() == 0x0)
    {
        throw runtime_error("CSH component ID is not set");
    }
    bool isSwitchFws = (CshComponentID)_metadata->GetComponentId() == CshComponentID::SWITCH_FWS;
    return CSH::HeaderSize(_cshStructType) + (isSwitchFws ? 32 : _cshSections.size()) * BinarySectionMetadata::Size();
}

size_t CSH::GetComponentSize() const
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
            throw runtime_error("Unsupported LMS signature size: " + std::to_string(signature.size()));
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
            throw runtime_error("Unsupported LMS signature size: " + std::to_string(signature.size()));
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

    vector<u_int8_t> magicIdBytes(magicId.begin(), magicId.end());
    if (magicId[0] == '0' && magicId[1] == 'x')
    { //* magicId is itoc_type byte
        magicIdBytes = mft_utils::HexStringToBytes(magicId.substr(2));
    }

    auto section = std::find_if(_cshSections.begin(), _cshSections.end(),
                                [&magicIdBytes](const BinarySectionMetadata& section)
                                {
                                    vector<u_int8_t> sectionMagicId = section.GetMagicIdAsVector();
                                    if (magicIdBytes.size() == 1)
                                    {
                                        return sectionMagicId[3] == magicIdBytes[0];
                                    }
                                    return sectionMagicId == magicIdBytes;
                                });
    if (section == _cshSections.end())
    {
        throw runtime_error("Magic ID not found in CSH: " + magicId);
    }

    section->SetJsonParams(root);
}

void CSH::SetSectionsFromJson(const Json::Value& root)
{
    for (auto section : _cshSections)
    {
        section.SetJsonParams(root);
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

    for (auto jsonField = root.begin(); jsonField != root.end(); jsonField++)
    {
        string jsonFieldName = jsonField.name();
        if (jsonFieldName == binarySectionMetadataName)
        {
            if (root[binarySectionMetadataName].isArray())
            {
                for (Json::ArrayIndex i = 0; i < root[binarySectionMetadataName].size(); i++)
                {
                    SetSingleSectionFromJson(root[binarySectionMetadataName][i]);
                }
            }
            else
            {
                SetSectionsFromJson(root[binarySectionMetadataName]);
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
        case CshComponentID::CALIPTRA_FW:
        case CshComponentID::OEM_FWS: // TODO backwards compatibility - remove after FS6 is fully adopted
        case CshComponentID::NV_FWS:
        case CshComponentID::SWITCH_FWS:
        case CshComponentID::SBD_FW:
        case CshComponentID::VMOD_FW:
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
        throw CshException(CshException::CshExceptionType::CSH_HEADER_NOT_FOUND, "CSH header magic is not NVDA");
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

CshComponentID CSH::GetComponentType() const
{
    return (CshComponentID)_metadata->GetComponentId();
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

BinarySectionMetadata& CSH::GetSection(u_int32_t itocType)
{
    for (auto& section : _cshSections)
    {
        if (section.GetSectionType() == itocType)
        {
            return section;
        }
    }
    std::stringstream ss;
    ss << std::hex << "Section with ITOC type 0x" << itocType << " not found in CSH";
    throw runtime_error(ss.str());
}

u_int8_t CSH::GetVmodAdmStatus()
{
    if (GetComponentIdEnum() != CshComponentID::VMOD_FW)
    {
        throw runtime_error("CSH component is not a VMOD FW");
    }
    return _header.csh_header_status.vmod_status.image_administrative_status;
}

PartitionType ToPartitionType(CshComponentID cshId, bool throwOnError)
{
    PartitionType type = PartitionType::PT_ROM_IMGS;
    switch (cshId)
    {
        case CshComponentID::ROM_IMGS:
            type = PartitionType::PT_ROM_IMGS;
            break;
        case CshComponentID::NV_FWS:
            type = PartitionType::PT_NV_FWS;
            break;
        case CshComponentID::OEM_FWS: // TODO backwards compatibility - remove after FS6 is fully adopted
            type = PartitionType::PT_CALIPTRA_FW;
            break;
        case CshComponentID::CALIPTRA_FW:
            type = PartitionType::PT_CALIPTRA_FW;
            break;
        case CshComponentID::BCT_DTB:
            type = PartitionType::PT_BCT_DTB;
            break;
        case CshComponentID::SWITCH_FWS:
            type = PartitionType::PT_SWITCH_FWS;
            break;
        case CshComponentID::SBD_FW:
            type = PartitionType::PT_SBD_FW;
            break;
        case CshComponentID::VMOD_FW:
            type = PartitionType::PT_VMOD_FW;
            break;
        default:
            if (throwOnError)
            {
                throw runtime_error("Unknown CSH id");
            }
            type = PartitionType::PT_UNKNOWN;
            break;
    }
    return type;
}
