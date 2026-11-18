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

#pragma once

#include <vector>
#include <algorithm>

#include "common/compatibility.h"
#include "json/reader.h"

#ifdef MFT_LEGACY_BUILD
#include "fs5_image_layout_layouts.h"
#else
#include "tools_layouts/fs5_image_layout_layouts.h"
#endif

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

#define CPUTOn(s, n)                                \
    do                                              \
    {                                               \
        u_int32_t* p = (u_int32_t*)(s);             \
        for (u_int32_t ii = 0; ii < (n); ii++, p++) \
            *p = __cpu_to_be32(*p);                 \
    } while (0)

using namespace std;

//* enum values are conversion from ASCII to hex with itoc_type byte appeneded to the end
enum class CshSectionType
{
    CSH_SECTION_BOOT2 = 0x42543201,
    CSH_SECTION_IMAGE_INFO = 0x494D4910,
    CSH_SECTION_HW_BOOT_INI = 0x48574208,
    CSH_SECTION_FW_BOOT_INI = 0x46574211,
    CSH_SECTION_PRE_LINKUP = 0x50524504,
    CSH_SECTION_POST_LINKUP = 0x49524F02,
    CSH_SECTION_HW_NON_ISFU_INI = 0x484E490D,
    CSH_SECTION_HW_MAIN_INI = 0x48574D09,
    CSH_SECTION_FW_MAIN_INI = 0x46574D12,
    CSH_SECTION_MFG_INFO = 0x4D4647E0,
    CSH_SECTION_POST_IRON_BOOT = 0x504F5306,
    CSH_SECTION_HW_TILE_INI = 0x48575437,
    CSH_SECTION_FW_TILE_INI = 0x46575436,
    CSH_SECTION_SWITCH_TILE_CODE_HASH_SQUARE = 0x54535152,
    CSH_SECTION_SWITCH_TILE_CODE_HASH = 0x54485348,
    CSH_SECTION_SWITCH_TILE_CODE = 0x54494C35,
    CSH_SECTION_PLASTIC_DATA = 0x504454D3,
    CSH_SECTION_SWITCH_MAIN_HASH_SQUARE = 0x4D5351B2,
    CSH_SECTION_SWITCH_MAIN_HASH = 0x4D4853B1,
    CSH_SECTION_SWITCH_MAIN = 0x4D414903,
    CSH_SECTION_NANO_KERNEL = 0x4E4B524C
};

enum class CshComponentID
{
    ROM_IMGS = 0x2,
    BCT_DTB = 0x5,
    OEM_FWS = 0x6,
    NV_FWS = 0x7,
    SWITCH_FWS = 0x2020,
    SBD_FW = 0x21,
    RECOVERY_IMAGE = 0x2820,
    Unknown = 0xff
};

enum class PartitionType
{
    PT_ROM_IMGS = 0x2,
    PT_CHAIN_CONTAINER = 0x3,
    PT_BCT_DTB = 0x4,
    PT_OEM_FWS = 0x5,
    PT_NV_FWS = 0x6,
    PT_SWITCH_FWS = 0x7,
    PT_SBD_FW = 0x8,
    PT_NV_DATA1 = 0xe4,
    PT_NV_DATA2 = 0xe6,
    PT_VPD_READ_ONLY = 0xe3,
    PT_MFG_INFO = 0xe0,
    PT_DEV_INFO = 0xe1,
    PT_DEV_INFO1 = 0xe7,
    PT_DEV_INFO2 = 0xe8,
    PT_PROGRAMMABLE_HW_FW1 = 0xeb,
    PT_PROGRAMMABLE_HW_FW2 = 0xec,
    PT_NVFILE_BUFFER = 0xf8,
    PT_FW_DEBUG_DUMP = 0xfc,
    PT_FW_DEBUG_DUMP2 = 0xd4,
};

const u_int32_t L1PT_OFFSET = 0xe000;
const u_int32_t SHA384_DIGEST_SIZE = 48;
const u_int32_t ROM_IMGS_MAGIC_PATTERN_OFFSET = 0xc;

bool IsCshComponent(PartitionType partitionType);
CshComponentID ToCshId(PartitionType partitionType);
string ToString(CshComponentID cshId);

// #ifndef MST_CPU_armv7l_umbriel // {

class MLXFWOP_API PartitionTableEntry
{
public:
    PartitionTableEntry() {}
    PartitionTableEntry(size_t offset, size_t size, u_int32_t type);
    vector<u_int8_t> Pack();
    void Unpack(const vector<u_int8_t>& data);

    void SetStartOffset(size_t offset);
    size_t GetStartOffset() const { return _struct.start_address[0]; }
    void SetSectionSize(size_t size);
    u_int32_t GetSectionSize() const { return _struct.partition_size[0]; }
    void SetSectionType(u_int32_t type);
    u_int32_t GetSectionType() const { return _struct.partition_type; }
    CshSectionType GetSectionTypeStrong() const { return static_cast<CshSectionType>(GetSectionType()); }

    static size_t Size() { return fs5_image_layout_partition_table_entry_size(); }

private:
    struct fs5_image_layout_partition_table_entry _struct;
};

class MLXFWOP_API PartitionTable
{
public:
    vector<u_int8_t> Pack();
    vector<u_int8_t> PackHeader();
    void UnpackHeader(const vector<u_int8_t>& data);

    size_t Size() { return HeaderSize() + _entries.size() * PartitionTableEntry::Size(); }
    void CalcDigest();

    void SetMaxNumberOfEntries(size_t num) { _struct.max_entires = num; };
    size_t GetMaxNumberOfEntries() const { return _struct.max_entires; };
    void SetNumberOfEntries(size_t num) { _struct.num_entires = num; }
    size_t GetNumberOfEntries() const { return _struct.num_entires; }

    void AddEntry(const PartitionTableEntry& entry);

    void SetEntrySize(PartitionType entryType, u_int32_t size);
    u_int32_t GetEntryOffset(PartitionType entryType);
    u_int32_t GetEntrySize(PartitionType entryType);
    PartitionTableEntry& GetEntry(PartitionType entryType);
    const vector<PartitionTableEntry>& GetEntries() const { return _entries; }

    static size_t HeaderSize() { return fs5_image_layout_partition_table_header_size(); }
    static const vector<u_int8_t>& MagicID()
    {
        static vector<u_int8_t> magicID({0x8B, 0x8D, 0x9E, 0x8F, 0x74, 0x72, 0x61, 0x70});
        return magicID;
    }
    static const vector<u_int8_t>& GetRomImageMagicPattern()
    {
        static vector<u_int8_t> romImageMagicPattern{{0x4f, 0x3d, 0x5a, 0x27}};
        return romImageMagicPattern;
    }

private:
    static const u_int16_t PARTITION_TABLE_DIGEST_OFFSET = 0x40;

    vector<PartitionTableEntry> _entries;
    struct fs5_image_layout_partition_table_header _struct;
};

class MLXFWOP_API BinarySectionMetadata
{
public:
    BinarySectionMetadata();
    BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest);
    BinarySectionMetadata(u_int32_t itocType,
                          u_int32_t loadDestinationLSB,
                          u_int32_t loadDestinationMSB,
                          u_int32_t entryPointLSB,
                          u_int32_t entryPointMSB,
                          size_t sectionSize,
                          size_t flashOffset,
                          const vector<u_int8_t>& digest);

    vector<u_int8_t> Pack() const;
    void Unpack(const vector<u_int8_t>& binarySection);

    size_t GetSectionOffset() const { return _struct.flash_offset; }
    void SetSectionOffset(u_int32_t offset) { _struct.flash_offset = offset; }

    size_t GetSectionSize() const { return _struct.bin_length; }
    u_int32_t GetSectionType() const;
    CshSectionType GetSectionTypeStrong() const
    {
        return static_cast<CshSectionType>(FromItocTypeToCshSectionType(GetSectionType()));
    }
    string GetMagicId() const;
    vector<u_int8_t> GetMagicIdAsVector() const;

    void SetDigest(const vector<u_int8_t>& digest);

    void SetJsonParams(const Json::Value& root);

    static size_t Size() { return fs5_image_layout_binary_section_metadata_size(); }
    static u_int32_t FromItocTypeToCshSectionType(u_int32_t itocType);
    static string CshSectionIDToString(u_int32_t sectionId);

    vector<u_int8_t> GetDerivationString() const;
    vector<u_int8_t> GetVersionAsVector() const;

    bool IsIVSet() const { return _isIVSet; }
    void SetIV(const vector<u_int8_t>& iv);
    vector<u_int8_t> GetIV() const;
    void SetAuthenticationTag(const vector<u_int8_t>& tag);
    static const size_t DIGEST_OFFSET_IN_ENTRY = 0x60;

private:
    void SetDwordsFrom8BytesJsonField(const Json::Value& root,
                                      const string& fieldName,
                                      u_int32_t& firstField,
                                      u_int32_t& secondField);

    struct fs5_image_layout_binary_section_metadata _struct;
    bool _isIVSet;
};

class MLXFWOP_API CshMetadataBase
{
public:
    virtual ~CshMetadataBase(){};
    virtual vector<u_int8_t> Pack() = 0;
    virtual void Unpack(const vector<u_int8_t>& buffer) = 0;

    virtual u_int16_t GetComponentId() = 0;
    virtual void SetComponentId(u_int16_t id) = 0;
    virtual size_t GetNumberOfBinaries() = 0;
    virtual void SetNumberOfBinaries(size_t num) = 0;
    virtual u_int8_t GetComponentMajorVersion() = 0;
    virtual u_int16_t GetComponentMinorVersion() = 0;

    virtual void SetBinariesListDigest(const vector<u_int8_t>& digest) = 0;

    virtual void SetJsonParams(const Json::Value& root) = 0;
};

class MLXFWOP_API CshMetadataNbu : public CshMetadataBase
{
public:
    vector<u_int8_t> Pack() override;
    void Unpack(const vector<u_int8_t>& buffer) override;

    u_int16_t GetComponentId() override { return _metadata_nbu.component_id; }
    void SetComponentId(u_int16_t id) override { _metadata_nbu.component_id = id; }
    size_t GetNumberOfBinaries() override { return _metadata_nbu.num_of_binaries; }
    void SetNumberOfBinaries(size_t num) override { _metadata_nbu.num_of_binaries = num; }
    u_int8_t GetComponentMajorVersion() override { return _metadata_nbu.version.ver_major; }
    u_int16_t GetComponentMinorVersion() override { return _metadata_nbu.version.ver_minor; }

    void SetBinariesListDigest(const vector<u_int8_t>& digest) override;

    void SetJsonParams(const Json::Value& root) override;

private:
    void SetDependencyList(const Json::Value& root);
    void SetEcid(const Json::Value& root);
    struct fs5_image_layout_csh_metadata_nbu _metadata_nbu;
};

class MLXFWOP_API CshMetadata : public CshMetadataBase
{
public:
    vector<u_int8_t> Pack() override;
    void Unpack(const vector<u_int8_t>& buffer) override;

    u_int16_t GetComponentId() override { return _metadata.component_id; }
    void SetComponentId(u_int16_t id) override { _metadata.component_id = id; }
    size_t GetNumberOfBinaries() override { return _metadata.num_of_binaries; }
    void SetNumberOfBinaries(size_t num) override { _metadata.num_of_binaries = num; }
    u_int8_t GetComponentMajorVersion() override { return _metadata.version.u8_ver_major; }
    u_int16_t GetComponentMinorVersion() override { return _metadata.version.u8_ver_minor; }

    void SetBinariesListDigest(const vector<u_int8_t>& digest) override;
    void SetJsonParams(const Json::Value& root) override;

private:
    struct fs5_image_layout_csh_metadata _metadata;
};

class MLXFWOP_API CSH
{
public:
    enum class SigType
    {
        ECDSA,
        LMS
    };

    enum class CshStructType : u_int8_t
    {
        CSH_TB50X = 0x0,
        CSH_NBU = 0x1
    };

    CSH();
    CSH(u_int16_t id, CshStructType type);

    vector<u_int8_t> Pack();
    vector<u_int8_t> PackMetadata() const;
    void Unpack(const vector<u_int8_t>& buffer);
    void UnpackHeader(const vector<u_int8_t>& cshHeader);
    void UnpackSections(const vector<u_int8_t>& buffer, size_t offset = 0);
    void AddBinarySectionMetadata(BinarySectionMetadata sectionMetadata, bool updateSectionsOffsets = true);

    vector<BinarySectionMetadata>& GetSections() { return _cshSections; }
    BinarySectionMetadata& GetSection(u_int32_t itocType);

    size_t GetCshSize();
    u_int16_t GetComponentId() { return _metadata->GetComponentId(); }
    size_t GetComponentSize();
    size_t GetNumberOfBinaries() { return _metadata->GetNumberOfBinaries(); }
    u_int8_t GetComponentMajorVersion() { return _metadata->GetComponentMajorVersion(); }
    u_int16_t GetComponentMinorVersion() { return _metadata->GetComponentMinorVersion(); }

    void SetNvSignature(const vector<u_int8_t>& signature, SigType sigType);
    void SetOemSignature(const vector<u_int8_t>& signature, SigType sigType);

    void SetJsonParams(const Json::Value& root);
    void CalcDigest();

    static size_t HeaderSize(CshStructType type);
    static CshStructType GetCshStructType(const vector<u_int8_t>& cshHeader);
    static bool IsValidCompId(u_int16_t id);

    static const string ROM_IMGS_NAME;
    static const string BCT_DTB_NAME;
    static const string OEM_FWS_NAME;
    static const string NV_FWS_NAME;
    static const string SWITCH_FWS_NAME;
    static const string SBD_FW_NAME;

private:
    void UnpackCshMetadata(const vector<u_int8_t>& cshHeader, const u_int8_t* iter);
    void SetHeaderFromJson(const Json::Value& root);
    void SetSingleSectionFromJson(const Json::Value& root);
    void SetSectionsFromJson(const Json::Value& root);
    void InitMembers();

    static const u_int16_t CSH_ECDSA_SIG_SIZE = 96;
    static const u_int16_t CSH_LMS_SIG_SIZE = 1740;
    static const string cshHeaderName;
    static const string cshMetadataName;
    static const string binarySectionMetadataName;

    struct fs5_image_layout_csh_header _header;
    struct fs5_image_layout_csh_signature _nv_signature;
    struct fs5_image_layout_csh_signature _oem_signature;
    unique_ptr<CshMetadataBase> _metadata;
    vector<BinarySectionMetadata> _cshSections;
    bool _isUnpacked;
    CshStructType _cshStructType;
};

// #endif // } MST_CPU_armv7l_umbriel