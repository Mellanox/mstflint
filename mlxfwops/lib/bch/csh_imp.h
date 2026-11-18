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

using namespace std;

enum class CshComponentID
{
    ROM_IMGS = 0x2,
    BCT_DTB = 0x5,
    OEM_FWS = 0x6,
    NV_FWS = 0x7,
    SWITCH_FWS = 0x20,
    SBD_FW = 0x21,
    Unknown = 0xff
};

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
    u_int32_t GetSectionsize() const { return _struct.partition_size[0]; }
    void SetSectionType(u_int32_t type);
    u_int32_t GetSectionType() const { return _struct.partition_type; }

    static size_t Size() { return fs5_image_layout_partition_table_entry_size(); }

private:
    struct fs5_image_layout_partition_table_entry _struct;
};

class MLXFWOP_API PartitionTable
{
public:
    vector<u_int8_t> PackHeader();
    void UnpackHeader(const vector<u_int8_t>& data);
    void SetMaxNumberOfEntries(size_t num) { _struct.max_entires = num; };
    size_t GetMaxNumberOfEntries() { return _struct.max_entires; };
    void SetNumberOfEntries(size_t num) { _struct.num_entires = num; }
    size_t GetNumberOfEntries() { return _struct.num_entires; }

    size_t GetPartitionSize();
    static size_t HeaderSize() { return fs5_image_layout_partition_table_header_size(); }

private:
    vector<PartitionTableEntry> _entries;
    struct fs5_image_layout_partition_table_header _struct;
};

class MLXFWOP_API BinarySectionMetadata
{
public:
    BinarySectionMetadata() {}
    BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& hash);
    BinarySectionMetadata(u_int32_t itoc_type, size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& hash);

    vector<u_int8_t> Pack();
    void Unpack(const vector<u_int8_t>& binarySection);

    size_t GetSectionOffset() { return _struct.flash_offset; }
    size_t GetSectionSize() { return _struct.bin_length; }

    static size_t Size() { return fs5_image_layout_binary_section_metadata_size(); }

private:
    struct fs5_image_layout_binary_section_metadata _struct;
};

class MLXFWOP_API CSH
{
public:
    CSH();

    vector<u_int8_t> Pack();
    void UnpackHeader(const vector<u_int8_t>& cshHeader);
    void UnpackSections(const vector<u_int8_t>& binarySections);
    void AddBinarySectionMetadata(BinarySectionMetadata metadata);

    const vector<BinarySectionMetadata>& GetSections() { return _cshSections; }

    size_t GetCshSize();
    size_t GetComponentSize(bool withCshHeader = true);
    size_t GetNumberOfBinaries() { return _metadata.num_of_binaries; }

    static size_t HeaderSize();

private:
    struct fs5_image_layout_csh_header _header;
    struct fs5_image_layout_csh_signature _nv_signature;
    struct fs5_image_layout_csh_signature _oem_signature;
    struct fs5_image_layout_csh_metadata _metadata;
    vector<BinarySectionMetadata> _cshSections;
};
