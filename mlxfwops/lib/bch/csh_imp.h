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
#ifndef CSH_IMP_H
#define CSH_IMP_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "common/compatibility.h"
#include "common/tools_endianness.h"

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
            *p = mft_cpu_to_be32(*p);               \
    } while (0)

using namespace std;

enum class CshSectionType
{
    RESET_INFO = 0x20,
    DBG_FW_INI = 0x30,

    //* enum values are conversion from ASCII to hex (4-char string to 32-bit hex)
    BOOT2_MAGIC_ID = 0x424F5432,                        // "BOT2"
    IMAGE_INFO_MAGIC_ID = 0x49494E46,                   // "IINF"
    HW_BOOT_INI_MAGIC_ID = 0x48574249,                  // "HWBI"
    FW_BOOT_INI_MAGIC_ID = 0x46574249,                  // "FWBI"
    PRE_LINKUP_MAGIC_ID = 0x5052454C,                   // "PREL"
    POST_LINKUP_MAGIC_ID = 0x49524F4E,                  // "IRON"
    HW_NON_ISFU_INI_MAGIC_ID = 0x484E4949,              // "HNII"
    HW_MAIN_INI_MAGIC_ID = 0x48574D49,                  // "HWMI"
    FW_MAIN_INI_MAGIC_ID = 0x46574D49,                  // "FWMI"
    POST_IRON_BOOT_MAGIC_ID = 0x50535449,               // "PSTI"
    HW_TILE_INI_MAGIC_ID = 0x48575449,                  // "HWTI"
    FW_TILE_INI_MAGIC_ID = 0x46575449,                  // "FWTI"
    TILE_CODE_HASH_SQUARE_MAGIC_ID = 0x54535152,        // "TSQR"
    TILE_CODE_HASH_MAGIC_ID = 0x54485348,               // "THSH"
    TILE_CODE_MAGIC_ID = 0x54494C45,                    // "TILE"
    PLASTIC_DATA_MAGIC_ID = 0x504C4454,                 // "PLDT"
    MAIN_HASH_SQUARE_MAGIC_ID = 0x4D535152,             // "MSQR"
    MAIN_HASH_MAGIC_ID = 0x4D485348,                    // "MHSH"
    MAIN_MAGIC_ID = 0x4D41494E,                         // "MAIN"
    NANO_KERNEL_MAGIC_ID = 0x4E4B524C,                  // "NKRL"
    VMOD_CODE_HASH_SQUARE_MAGIC_ID = 0x564D4853,        // "VMHS"
    VMOD_CODE_HASH_MAGIC_ID = 0x564D4448,               // "VMDH"
    VMOD_CODE_MAGIC_ID = 0x564D4F44,                    // "VMOD"
    VMOD_IMAGE_INFO_MAGIC_ID = 0x564D4449,              // "VMDI"
    VMOD_HW_NON_ISFU_INI_MAGIC_ID = 0x56484e49,         // "VHNI"
    VMOD_HW_MAIN_INI_MAGIC_ID = 0x5648574D,             // "VHWM"
    VMOD_FW_MAIN_INI_MAGIC_ID = 0x5646574D,             // "VFWM"
    VMOD_UID_MAGIC_ID = 0x55494456,                     // "UIDV"
    VMOD_ISSU_NOTCH_INI_MAGIC_ID = 0x56544348,          // "VTCH"
    L3PW_MAGIC_ID = 0x4c335057,                         // "L3PW"
    L3PR_MAGIC_ID = 0x4c335052,                         // "L3PR"
    NANO_KERNEL_1_MAGIC_ID = 0x4E4B5231,                // "NKR1"
    CERTIFICATES_CHAIN_MAGIC_ID = 0x43455254,           // "CERT"
    PRE_LINK_CODE_MAGIC_ID = 0x504C4350,                // "PLCP"
    PRE_LINK_DATA_MAGIC_ID = 0x504C4450,                // "PLDP"
    POST_LINK_CODE_MAGIC_ID = 0x50534C43,               // "PSLC"
    POST_LINK_DATA_MAGIC_ID = 0x50534C44,               // "PSLD"
    IRON_PREP_CODE_MAGIC_ID = 0x49504343,               // "IPCC"
    EXPANSION_ROM_MAGIC_ID = 0x524F4D43,                // "ROMC"
    PAGER_CONFIG_MAGIC_ID = 0x50475243,                 // "PGRC"
    NIC_ETC_MAGIC_ID = 0x4E455443,                      // "NETC"
    NIC_ETC_PAGES_HASHES_MAGIC_ID = 0x45544348,         // "ETCH"
    NIC_ETC_PAGES_LOCKED_HASHES_MAGIC_ID = 0x45485351,  // "EHSQ"
    DPA_ATOC_MAGIC_ID = 0x44504141,                     // "DPAA"
    DPA_ATOC_PAGES_HASHES_MAGIC_ID = 0x44504853,        // "DPHS"
    DPA_ATOC_PAGES_LOCKED_HASHES_MAGIC_ID = 0x44485351, // "DHSQ"
    CRDUMP_MASK_DATA_MAGIC_ID = 0x444D504D              // "DMPM"
};

inline u_int32_t ToU32(CshSectionType type)
{
    return static_cast<u_int32_t>(type);
}

enum class CshComponentID
{
    ROM_IMGS = 0x2,
    BCT_DTB = 0x5,
    OEM_FWS = 0x6,
    NV_FWS = 0x7,
    SWITCH_FWS = 0x2020,
    SBD_FW = 0x21,
    VMOD_FW = 0x22,
    CALIPTRA_FW = 0x23,
    RECOVERY_IMAGE = 0x2820,
    Unknown = 0xff
};

enum class PartitionType
{
    PT_UNKNOWN = 0x0,
    PT_ROM_IMGS = 0x2,
    PT_CHAIN_CONTAINER = 0x3,
    PT_BCT_DTB = 0x4,
    PT_CALIPTRA_FW = 0x5,
    PT_NV_FWS = 0x6,
    PT_SWITCH_FWS = 0x7,
    PT_SBD_FW = 0x8,
    PT_VMOD_FW = 0x9,
    PT_CRC_INFO = 0xa,
    PT_WP_AREA_PTR = 0xb,
    PT_RW_AREA_PTR = 0xc,
    PT_NV_DATA1 = 0xe4,
    PT_NV_DATA2 = 0xe6,
    PT_VPD_READ_ONLY = 0xe3,
    PT_MFG_INFO = 0xe0,
    PT_DEV_INFO = 0xe1,
    PT_DEV_INFO1 = 0xe7,
    PT_DEV_INFO2 = 0xe8,
    PT_PROGRAMMABLE_HW_FW1 = 0xeb,
    PT_PROGRAMMABLE_HW_FW2 = 0xec,
    PT_FW_DEBUG_DUMP = 0xfc,
    PT_FW_DEBUG_DUMP2 = 0xd4,
    PT_PQC_L4_CERTIFICATE_1 = 0xd6,
    PT_PQC_L4_CERTIFICATE_2 = 0xd7,
    PT_FW_NV_LOG = 0xe5,
    PT_CPO_CALIBRATION_DATA = 0xcc,
    PT_NVFILE_BUFFER = 0xcd,
};

const u_int32_t L1PT_OFFSET = 0xe000;
const u_int32_t SECOND_L1PT_OFFSET = 0x1e000;
const u_int32_t ROM_IMGS_MAGIC_PATTERN_OFFSET = 0xc;
// the ROM images section is aligned to 384KB because the PBLT and PBLD flexible
const u_int32_t ROM_IMGS_ALIGN_SIZE = 384 * 1024;

const int INVALID_CHAIN_NUMBER = 0XFF;
inline void ResolveChainNumber(int& chainNumber, int activeChain)
{
    if (chainNumber == INVALID_CHAIN_NUMBER)
    {
        chainNumber = activeChain;
    }
}

bool MLXFWOP_API IsCshComponent(PartitionType partitionType);
CshComponentID ToCshId(PartitionType partitionType);
string ToString(CshComponentID cshId);
MLXFWOP_API PartitionType ToPartitionType(CshComponentID cshId, bool throwOnError = true);
MLXFWOP_API bool IsPartitionTypeMaxSize(PartitionType partitionType);

class CshException : public exception
{
public:
    enum class CshExceptionType
    {
        CSH_HEADER_NOT_FOUND,
        UNEXPECTED_ERROR
    };

    CshException(CshExceptionType type, const char* fmt, ...);
    ~CshException() throw(){};
    virtual const char* what() const throw() { return _msg.c_str(); }
    CshExceptionType GetType() const { return _type; }

private:
    CshExceptionType _type;
    std::string _msg;
};

class CSH; // forward declaration

class MLXFWOP_API PartitionTableEntry
{
public:
    PartitionTableEntry() : _csh(nullptr) {}
    PartitionTableEntry(size_t offset, size_t size, u_int32_t type);
    vector<u_int8_t> Pack();
    void Unpack(const vector<u_int8_t>& data);

    void SetCsh(std::shared_ptr<CSH> csh) { _csh = csh; }
    std::shared_ptr<CSH> GetCsh() const { return _csh; }
    bool IsCshActiveChain() const;
    bool IsCshBackupChain() const;

    void SetStartOffset(size_t offset);
    size_t GetStartOffset() const { return _struct.start_address[0]; }
    void SetSectionSize(size_t size);
    u_int32_t GetSectionSize() const { return _struct.partition_size[0]; }
    void SetPartitionType(u_int32_t type);
    u_int32_t GetPartitionType() const;
    PartitionType GetPartitionTypeEnum() const;

    static size_t Size() { return fs5_image_layout_partition_table_entry_size(); }

    int GetChainNumber() const;

private:
    struct fs5_image_layout_partition_table_entry _struct;
    std::shared_ptr<CSH> _csh;
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

    void SetEntrySize(PartitionType entryType, u_int32_t size, int chainNumber = INVALID_CHAIN_NUMBER);
    u_int32_t GetEntryOffset(PartitionType entryType, int chainNumber = INVALID_CHAIN_NUMBER);
    u_int32_t GetEntrySize(PartitionType entryType, int chainNumber = INVALID_CHAIN_NUMBER);
    PartitionTableEntry& GetEntry(PartitionType entryType, int chainNumber = INVALID_CHAIN_NUMBER);
    int GetEntryIndex(PartitionType entryType, int chainNumber = INVALID_CHAIN_NUMBER);
    size_t GetEntryTableOffset(PartitionType entryType, int chainNumber = INVALID_CHAIN_NUMBER);
    const vector<PartitionTableEntry>& GetEntries() const { return _entries; }

    static size_t HeaderSize() { return fs5_image_layout_partition_table_header_size(); }
    static const vector<u_int8_t>& MagicID()
    {
        static vector<u_int8_t> magicID({0x8B, 0x8D, 0x9E, 0x8F, 0x74, 0x72, 0x61, 0x70});
        return magicID;
    }
    static const vector<u_int8_t>& RomImageMagicPattern()
    {
        static vector<u_int8_t> romImageMagicPattern{{0x4f, 0x3d, 0x5a, 0x27}};
        return romImageMagicPattern;
    }
    static const vector<u_int8_t>& RomImgsCandidateMagicPatternBE()
    {
        static vector<u_int8_t> romImgsCandidateMagicPatternBE{{0x27, 0x5a, 0x3d, 0x4f}};
        return romImgsCandidateMagicPatternBE;
    }

    static const vector<u_int8_t>& RomImgsBackupMagicPattern()
    {
        static vector<u_int8_t> romImgsBackupMagicPatternLE{{0x40, 0x3c, 0x58, 0x25}};
        return romImgsBackupMagicPatternLE;
    }
    static const vector<u_int8_t>& RomImgsBackupMagicPatternBE()
    {
        static vector<u_int8_t> romImgsBackupMagicPatternBE{{0x25, 0x58, 0x3c, 0x40}};
        return romImgsBackupMagicPatternBE;
    }

    void SetActiveChain(int chain) { _activeChain = chain; }
    int GetActiveChain() const { return _activeChain; }

private:
    static const u_int16_t PARTITION_TABLE_DIGEST_OFFSET = 0x40;

    vector<PartitionTableEntry> _entries;
    struct fs5_image_layout_partition_table_header _struct;
    int _activeChain = INVALID_CHAIN_NUMBER;
};

class MLXFWOP_API BinarySectionMetadata
{
public:
    BinarySectionMetadata();

    vector<u_int8_t> Pack() const;
    void Unpack(const vector<u_int8_t>& binarySection);

    size_t GetSectionOffset() const { return _struct.flash_offset; }
    void SetSectionOffset(u_int32_t offset) { _struct.flash_offset = offset; }

    size_t GetSectionSize() const { return _struct.bin_length; }
    void SetSectionSize(u_int32_t size) { _struct.bin_length = size; }
    u_int32_t GetSectionType() const;
    CshSectionType GetSectionTypeStrong() const { return static_cast<CshSectionType>(GetSectionType()); }
    string GetMagicId() const;
    vector<u_int8_t> GetMagicIdAsVector() const;

    static size_t Size() { return fs5_image_layout_binary_section_metadata_size(); }
    static string CshSectionIDToString(u_int32_t sectionId);
    static u_int32_t CshSectionStringToID(const string& sectionName);

    u_int64_t GetLoadDestination() const
    {
        return (static_cast<u_int64_t>(_struct.load_dest[1]) << 32) | _struct.load_dest[0];
    }
    u_int64_t GetEntryPoint() const
    {
        return (static_cast<u_int64_t>(_struct.entry_point[1]) << 32) | _struct.entry_point[0];
    }

private:
    struct fs5_image_layout_binary_section_metadata _struct;
};

class MLXFWOP_API CshMetadataBase
{
public:
    virtual ~CshMetadataBase(){};
    virtual vector<u_int8_t> Pack() = 0;
    virtual void Unpack(const vector<u_int8_t>& buffer) = 0;

    virtual u_int16_t GetComponentId() const = 0;
    virtual void SetComponentId(u_int16_t id) = 0;
    virtual size_t GetNumberOfBinaries() = 0;
    virtual void SetNumberOfBinaries(size_t num) = 0;
    virtual u_int8_t GetComponentMajorVersion() = 0;
    virtual u_int16_t GetComponentMinorVersion() = 0;
    virtual u_int16_t GetComponentSubminorVersion() = 0;
    // The SVN and lifecycle attestation reports per CSH.
    virtual u_int32_t GetFwLifecycle() const { return 0; }

    virtual u_int8_t GetRatchetLevel() const = 0;

    const static size_t BINARIES_LIST_DIGEST_OFFSET = 0x70;
};

class MLXFWOP_API CshMetadataNbu : public CshMetadataBase
{
public:
    CshMetadataNbu();

    vector<u_int8_t> Pack() override;
    void Unpack(const vector<u_int8_t>& buffer) override;

    u_int16_t GetComponentId() const override { return _metadata_nbu.component_id; }
    void SetComponentId(u_int16_t id) override { _metadata_nbu.component_id = id; }
    size_t GetNumberOfBinaries() override { return _metadata_nbu.num_of_binaries; }
    void SetNumberOfBinaries(size_t num) override { _metadata_nbu.num_of_binaries = num; }
    u_int8_t GetComponentMajorVersion() override { return _metadata_nbu.version.ver_major; }
    u_int16_t GetComponentMinorVersion() override { return _metadata_nbu.version.ver_minor; }
    u_int16_t GetComponentSubminorVersion() override { return _metadata_nbu.nbu_subminor; }
    u_int8_t GetRatchetLevel() const override { return _metadata_nbu.version.ratchet_level; }
    u_int32_t GetFwLifecycle() const override { return _metadata_nbu.fw_lifecycle; }

private:
    struct fs5_image_layout_csh_metadata_nbu _metadata_nbu;
};

class MLXFWOP_API CshMetadata : public CshMetadataBase
{
public:
    vector<u_int8_t> Pack() override;
    void Unpack(const vector<u_int8_t>& buffer) override;

    u_int16_t GetComponentId() const override { return _metadata.component_id; }
    void SetComponentId(u_int16_t id) override { _metadata.component_id = id; }
    size_t GetNumberOfBinaries() override { return _metadata.num_of_binaries; }
    void SetNumberOfBinaries(size_t num) override { _metadata.num_of_binaries = num; }
    u_int8_t GetComponentMajorVersion() override { return _metadata.version.u8_ver_major; }
    u_int16_t GetComponentMinorVersion() override { return _metadata.version.u8_ver_minor; }
    u_int16_t GetComponentSubminorVersion() override { return 0; }
    u_int8_t GetRatchetLevel() const override { return _metadata.version.u8_ratchet_level; }
    u_int32_t GetFwLifecycle() const override { return _metadata.fw_lifecycle; }

private:
    struct fs5_image_layout_csh_metadata _metadata;
};

class MLXFWOP_API CSH
{
public:
    enum class CshStructType : u_int8_t
    {
        CSH_TB50X = 0x0,
        CSH_NBU = 0x1
    };

    CSH();
    CSH(u_int16_t id, CshStructType type);

    vector<u_int8_t> Pack();
    vector<u_int8_t> PackMetadata() const;
    vector<u_int8_t> PackHeader() const;
    void Unpack(const vector<u_int8_t>& buffer);
    void UnpackHeader(const vector<u_int8_t>& cshHeader);
    void UnpackSections(const vector<u_int8_t>& buffer, size_t offset = 0);

    vector<BinarySectionMetadata>& GetSections() { return _cshSections; }
    BinarySectionMetadata& GetSection(u_int32_t itocType);

    size_t GetCshSize() const;

    u_int16_t GetComponentId() const { return _metadata->GetComponentId(); }
    CshComponentID GetComponentIdEnum() { return static_cast<CshComponentID>(_metadata->GetComponentId()); }

    size_t GetComponentSize() const;
    size_t GetNumberOfBinaries() { return _metadata->GetNumberOfBinaries(); }
    u_int8_t GetComponentMajorVersion() { return _metadata->GetComponentMajorVersion(); }
    u_int16_t GetComponentMinorVersion() { return _metadata->GetComponentMinorVersion(); }
    u_int16_t GetComponentSubminorVersion() { return _metadata->GetComponentSubminorVersion(); }
    u_int8_t GetRatchetLevel() const { return _metadata->GetRatchetLevel(); }
    u_int32_t GetFwLifecycle() const { return _metadata->GetFwLifecycle(); }
    u_int8_t GetNvPubKeyIdx() { return _header.u8_nv_pub_key_idx; }

    u_int8_t GetVmodAdmStatus();
    static string VmodAdmStatusToString(u_int8_t status);

    static size_t HeaderSize(CshStructType type);
    static CshStructType GetCshStructType(const vector<u_int8_t>& cshHeader);
    CshComponentID GetComponentType() const;
    static bool IsValidCompId(u_int16_t id);

    bool isActiveChain();
    bool isBackupChain();

    static const string ROM_IMGS_NAME;
    static const string BCT_DTB_NAME;
    static const string OEM_FWS_NAME;
    static const string NV_FWS_NAME;
    static const string SWITCH_FWS_NAME;
    static const string SBD_FW_NAME;
    static const string VMOD_FW_NAME;
    static const string CALIPTRA_FW_NAME;

    static const u_int8_t VMOD_ADM_STATUS_INVALID = 0x0f;   // 1111b
    static const u_int8_t VMOD_ADM_STATUS_CANDIDATE = 0x07; // 0111b
    static const u_int8_t VMOD_ADM_STATUS_ACTIVE = 0x03;    // 0011b
    static const u_int8_t VMOD_ADM_STATUS_BACKUP = 0x01;    // 0001b
    static const u_int8_t VMOD_ADM_STATUS_REVOKED = 0x00;   // 0000b
    static const u_int8_t VMOD_ADM_STATUS_UNKNOWN = 0xff;
    static const u_int8_t ALL_TILES_COMMITTED = 0x00;
    static const u_int8_t ALL_TILES_NOT_COMMITTED = 0xff;

private:
    void UnpackCshMetadata(const vector<u_int8_t>& cshHeader, const u_int8_t* iter);
    void InitMembers();

    static const u_int16_t VMOD_ADM_OFFSET = 12;

    struct fs5_image_layout_csh_header _header;
    struct fs5_image_layout_csh_signature _nv_signature;
    struct fs5_image_layout_csh_signature _oem_signature;
    unique_ptr<CshMetadataBase> _metadata;
    vector<BinarySectionMetadata> _cshSections;
    bool _isUnpacked;
    CshStructType _cshStructType;
};

#endif
