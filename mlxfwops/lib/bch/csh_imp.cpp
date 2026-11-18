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
#include <algorithm>
#include <limits.h>

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
        // TODO
        throw exception();
    }

    fs5_image_layout_partition_table_header_unpack(&_struct, data.data());
}

size_t PartitionTable::GetPartitionSize()
{
    return 0;
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

BinarySectionMetadata::BinarySectionMetadata(size_t sectionSize, size_t flashOffset, const vector<u_int8_t>& hash)
{
    memset(&_struct, 0, sizeof(_struct));
    _struct.bin_length = sectionSize;
    _struct.flash_offset = flashOffset;
    if (!hash.empty())
    {
        memcpy(_struct.bin_digest.digest, hash.data(), hash.size());
    }
}

BinarySectionMetadata::BinarySectionMetadata(u_int32_t itoc_type,
                                             size_t sectionSize,
                                             size_t flashOffset,
                                             const vector<u_int8_t>& hash)
{
    memset(&_struct, 0, sizeof(_struct));
    memcpy(_struct.u8_magic_id, &itoc_type, sizeof(itoc_type));
    _struct.bin_length = sectionSize;
    _struct.flash_offset = flashOffset;
    if (!hash.empty())
    {
        memcpy(_struct.bin_digest.digest, hash.data(), hash.size());
    }
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
        printf("Binary section size!!!\n");
        throw exception();
    }
    fs5_image_layout_binary_section_metadata_unpack(&_struct, binarySection.data());
}

CSH::CSH()
{
    memcpy(&_header.u8_header_magic, "NVDA", 4);
}

vector<u_int8_t> CSH::Pack()
{
    _metadata.num_of_binaries = _cshSections.size();

    vector<u_int8_t> cshHeader(CSH::HeaderSize());
    fs5_image_layout_csh_header_pack(&_header, cshHeader.data());
    fs5_image_layout_csh_signature_pack(&_nv_signature, cshHeader.data() + fs5_image_layout_csh_header_size());
    fs5_image_layout_csh_signature_pack(&_oem_signature, cshHeader.data() + fs5_image_layout_csh_signature_size());
    fs5_image_layout_csh_metadata_pack(&_metadata, cshHeader.data() + fs5_image_layout_csh_signature_size());

    for (auto section : _cshSections)
    {
        vector<u_int8_t> metadata = section.Pack();
        cshHeader.insert(cshHeader.end(), metadata.begin(), metadata.end());
    }

    return cshHeader;
}

void CSH::UnpackHeader(const vector<u_int8_t>& cshHeader)
{
    if (cshHeader.size() != CSH::HeaderSize())
    {
        printf("Not a CSH Header!!!\n");
        throw exception();
    }
    fs5_image_layout_csh_header_unpack(&_header, cshHeader.data());
    fs5_image_layout_csh_signature_unpack(&_nv_signature, cshHeader.data() + fs5_image_layout_csh_header_size());
    fs5_image_layout_csh_signature_unpack(&_oem_signature, cshHeader.data() + fs5_image_layout_csh_signature_size());
    fs5_image_layout_csh_metadata_unpack(&_metadata, cshHeader.data() + fs5_image_layout_csh_signature_size());
    memcpy(&_header.u8_header_magic, "NVDA", 4);
}

void CSH::UnpackSections(const vector<u_int8_t>& binarySections)
{
    if (GetNumberOfBinaries() == 0)
    {
        printf("Number of binary section is missing!!!\n");
        throw exception();
    }
    if (binarySections.size() == 0 ||
        binarySections.size() != GetNumberOfBinaries() * fs5_image_layout_binary_section_metadata_size())
    {
        printf("Binary sections buffer size!!!\n");
        throw exception();
    }

    auto sectionIter = binarySections.begin();
    for (size_t i = 0; i < GetNumberOfBinaries(); i++)
    {
        BinarySectionMetadata binary;
        binary.Unpack(vector<u_int8_t>(sectionIter, sectionIter + BinarySectionMetadata::Size()));
        _cshSections.push_back(binary);
        sectionIter += BinarySectionMetadata::Size();
    }
}

void CSH::AddBinarySectionMetadata(BinarySectionMetadata metadata)
{
    _cshSections.push_back(metadata);
}

size_t CSH::GetCshSize()
{
    return CSH::HeaderSize() + _cshSections.size() * BinarySectionMetadata::Size();
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

size_t CSH::HeaderSize()
{
    return fs5_image_layout_csh_header_size() + fs5_image_layout_csh_signature_size() +
           fs5_image_layout_csh_signature_size() + fs5_image_layout_csh_metadata_size();
}