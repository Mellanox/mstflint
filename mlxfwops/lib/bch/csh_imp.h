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

bool IsCshComponent(PartitionType partitionType);
string ToString(CshComponentID cshId);
string CshSectionIDToString(u_int32_t sectionId);

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

    const vector<PartitionTableEntry>& GetEntries() const { return _entries; }

    static size_t HeaderSize() { return fs5_image_layout_partition_table_header_size(); }

private:
    static const u_int16_t PARTITION_TABLE_DIGEST_OFFSET = 0x40;

    PartitionTableEntry& GetEntry(PartitionType entryType);

    vector<PartitionTableEntry> _entries;
    struct fs5_image_layout_partition_table_header _struct;
};

class MLXFWOP_API BinarySectionMetadata
{
public:
    BinarySectionMetadata();
    BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest);
    BinarySectionMetadata(u_int32_t itoc_type, size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& digest);

    vector<u_int8_t> Pack();
    void Unpack(const vector<u_int8_t>& binarySection);

    size_t GetSectionOffset() { return _struct.flash_offset; }
    size_t GetSectionSize() { return _struct.bin_length; }
    u_int32_t GetSectionType() const
    {
        u_int32_t magic;
        memcpy(&magic, _struct.u8_magic_id, sizeof(magic));
        return magic;
    }

    void SetSectionOffset(u_int32_t offset) { _struct.flash_offset = offset; }

    void SetJsonParams(const Json::Value& root);

    static size_t Size() { return fs5_image_layout_binary_section_metadata_size(); }

    vector<u_int8_t> GetDerivationKey()
    {
        return vector<u_int8_t>(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy,
                                _struct.encryption_params.u8_encryption_derivation_string.u8_dummy +
                                  FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE);
    }
    // TODO:: check with Nael what is the derivation context
    vector<u_int8_t> GetDerivationContext()
    {
        return vector<u_int8_t>(_struct.encryption_params.u8_encryption_derivation_string.u8_dummy,
                                _struct.encryption_params.u8_encryption_derivation_string.u8_dummy +
                                  FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE);
    }
    void SetIV(const vector<u_int8_t>& iv)
    {
        memcpy(_struct.encryption_params.u8_iv.u8_dummy, iv.data(), FS5_IMAGE_LAYOUT_U8_IV_SIZE);
    }
    void SetAuthenticationTag(const vector<u_int8_t>& tag);

private:
    struct fs5_image_layout_binary_section_metadata _struct;
};

class MLXFWOP_API CSH
{
public:
    enum class SigType
    {
        ECDSA,
        LMS
    };

    CSH();
    CSH(u_int16_t id);

    vector<u_int8_t> Pack();
    void Unpack(const vector<u_int8_t>& buffer);
    void UnpackHeader(const vector<u_int8_t>& cshHeader);
    void UnpackSections(const vector<u_int8_t>& buffer, size_t offset = 0);
    void AddBinarySectionMetadata(BinarySectionMetadata sectionMetadata, bool updateSectionsOffsets = true);

    const vector<BinarySectionMetadata>& GetSections() { return _cshSections; }
    vector<u_int8_t> GetMetadata() const;
    size_t GetCshSize();
    u_int16_t GetComponentId() { return _metadata.component_id; }
    size_t GetComponentSize(bool withCshHeader = true);
    size_t GetNumberOfBinaries() { return _metadata.num_of_binaries; }

    void SetNvSignature(const vector<u_int8_t>& signature, SigType sigType);
    void SetOemSignature(const vector<u_int8_t>& signature, SigType sigType);

    void SetJsonParams(const Json::Value& root);
    void CalcDigest();

    static size_t HeaderSize();
    static bool IsValidCompId(u_int16_t id);

private:
    void SetMetadataFromJson(const Json::Value& root);

    static const u_int16_t CSH_ECDSA_SIG_SIZE = 96;
    static const u_int16_t CSH_LMS_SIG_SIZE = 1740;
    static const string cshMetadataName;
    static const string binarySectionMetadataArrName;

    struct fs5_image_layout_csh_header _header;
    struct fs5_image_layout_csh_signature _nv_signature;
    struct fs5_image_layout_csh_signature _oem_signature;
    struct fs5_image_layout_csh_metadata _metadata;
    vector<BinarySectionMetadata> _cshSections;
    bool _isUnpacked;
};

// #endif // } MST_CPU_armv7l_umbriel