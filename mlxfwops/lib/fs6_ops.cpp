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

#include "fs6_ops.h"
#include "nvtoolslogger/NvToolsLogger.h"
#include "fs3_ops.h"
#include "bch/csh_imp.h"
#include "tools_layouts/fs6_image_layout_layouts.h"
#include "json/writer.h"

#ifdef MFT_LEGACY_BUILD
#include <mft_utils.h>
#else
#include "mft_utils/mft_utils.h"
#endif

#include <algorithm>
#include <iomanip>
#include <fstream>

CshComponentID ToCshId(ComponentType compName)
{
    CshComponentID id = CshComponentID::Unknown;
    switch (compName)
    {
        case ComponentType::Comp_Csh_Rom_Imgs:
            id = CshComponentID::ROM_IMGS;
            break;
        case ComponentType::Comp_Csh_Nv_Fws:
            id = CshComponentID::NV_FWS;
            break;
        case ComponentType::Comp_Csh_Oem_Fws:
            id = CshComponentID::OEM_FWS;
            break;
        case ComponentType::Comp_Csh_Bct_Dtb:
            id = CshComponentID::BCT_DTB;
            break;
        case ComponentType::Comp_Csh_Switch_Fws:
            id = CshComponentID::SWITCH_FWS;
            break;
        case ComponentType::Comp_Csh_Sbd_Fw:
            id = CshComponentID::SBD_FW;
            break;
        default:
            break;
    }
    return id;
}

PartitionType ToPartitionType(CshComponentID cshId)
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
        case CshComponentID::OEM_FWS:
            type = PartitionType::PT_OEM_FWS;
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
        default:
            throw runtime_error("Unknown CSH id");
    }
    return type;
}

string ToString(PartitionType type)
{
    switch (type)
    {
        case PartitionType::PT_ROM_IMGS:
            return CSH::ROM_IMGS_NAME;
        case PartitionType::PT_CHAIN_CONTAINER:
            return "CHAIN_CONTAINER";
        case PartitionType::PT_BCT_DTB:
            return CSH::BCT_DTB_NAME;
        case PartitionType::PT_OEM_FWS:
            return CSH::OEM_FWS_NAME;
        case PartitionType::PT_NV_FWS:
            return CSH::NV_FWS_NAME;
        case PartitionType::PT_SWITCH_FWS:
            return CSH::SWITCH_FWS_NAME;
        case PartitionType::PT_SBD_FW:
            return CSH::SBD_FW_NAME;
        case PartitionType::PT_NV_DATA1:
            return "NV_DATA1";
        case PartitionType::PT_NV_DATA2:
            return "NV_DATA2";
        case PartitionType::PT_VPD_READ_ONLY:
            return "VPD_READ_ONLY";
        case PartitionType::PT_MFG_INFO:
            return "MFG_INFO";
        case PartitionType::PT_DEV_INFO:
            return "DEV_INFO";
        case PartitionType::PT_DEV_INFO1:
            return "DEV_INFO1";
        case PartitionType::PT_DEV_INFO2:
            return "DEV_INFO2";
        case PartitionType::PT_PROGRAMMABLE_HW_FW1:
            return "PROGRAMMABLE_HW_FW1";
        case PartitionType::PT_PROGRAMMABLE_HW_FW2:
            return "PROGRAMMABLE_HW_FW2";
        case PartitionType::PT_NVFILE_BUFFER:
            return "NVFILE_BUFFER";
        case PartitionType::PT_FW_DEBUG_DUMP:
            return "FW_DEBUG_DUMP";
        case PartitionType::PT_FW_DEBUG_DUMP2:
            return "FW_DEBUG_DUMP2";
        default:
            return "UNKNOWN";
    }
}

Fs6Operations::Fs6Operations(FBase* ioAccess) :
    FwOperations(ioAccess), _l1ptOffset(L1PT_OFFSET), _l2ptOffset(0), _activeChain(INVALID_CHAIN_NUMBER)
{
    memset(_dotMagicId, 0, sizeof(_dotMagicId));
}

bool Fs6Operations::InitL2pt()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::InitL2pt");
    vector<u_int8_t> partitionTable(PartitionTable::HeaderSize());
    vector<u_int8_t> entryData(PartitionTableEntry::Size());

    if (!_ioAccess->read(_l2ptOffset, partitionTable.data(), PartitionTable::HeaderSize()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }
    _l2pt.UnpackHeader(partitionTable);

    if (!std::equal(PartitionTable::MagicID().begin(), PartitionTable::MagicID().end(), partitionTable.begin()))
    {
        return errmsg("Couldn't find L2PT.");
    }

    for (size_t i = 0; i < _l2pt.GetNumberOfEntries(); i++)
    {
        size_t l2PartitionsOffset = _l2ptOffset + PartitionTable::HeaderSize();
        if (!_ioAccess->read(l2PartitionsOffset + i * PartitionTableEntry::Size(), entryData.data(),
                             PartitionTableEntry::Size()))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
        }
        PartitionTableEntry entry;
        entry.Unpack(entryData);
        _l2pt.AddEntry(entry);

        if (IsCshComponent((PartitionType)entry.GetSectionType()))
        {
            InitCshComponent((PartitionType)entry.GetSectionType(), _l2ptOffset + entry.GetStartOffset());
        }
    }
    return true;
}

bool Fs6Operations::Init()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::Init");
    // Guard against re-initialization
    if (!_l1pt.GetEntries().empty())
    {
        MLXFWOPS_LOG_DEBUG("Fs6Operations::Init() - already initialized, skipping");
        return true;
    }

    vector<u_int8_t> partitionTable(PartitionTable::HeaderSize());
    vector<u_int8_t> entryData(PartitionTableEntry::Size());

    if (!_ioAccess->read(0, _dotMagicId, sizeof(_dotMagicId)))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    if (!_ioAccess->read(_l1ptOffset, partitionTable.data(), PartitionTable::HeaderSize()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    if (!std::equal(PartitionTable::MagicID().begin(), PartitionTable::MagicID().end(), partitionTable.begin()))
    {
        // Reduced image isnt contain the L1PT, it is only contain the ROM_IMGS and CHAIN_CONTAINER
        PartitionTableEntry romImgsEntry(0, ROM_IMGS_ALIGN_SIZE, static_cast<u_int32_t>(PartitionType::PT_ROM_IMGS));
        _l1pt.AddEntry(romImgsEntry);
        InitCshComponent((PartitionType)romImgsEntry.GetSectionType(), romImgsEntry.GetStartOffset());

        u_int32_t imageSize = 0;
        GetImageSize(&imageSize);
        PartitionTableEntry chainContainerEntry(ROM_IMGS_ALIGN_SIZE, imageSize - ROM_IMGS_ALIGN_SIZE,
                                                static_cast<u_int32_t>(PartitionType::PT_CHAIN_CONTAINER));
        _l1pt.AddEntry(chainContainerEntry);

        _l2ptOffset = ROM_IMGS_ALIGN_SIZE;
        if (!InitL2pt())
        {
            return false;
        }
        // TODO: should be removed after CheckAndSetIsReducedImage is implemented
        SetIsReducedImage(true);
    }
    else
    {
        _l1pt.UnpackHeader(partitionTable);

        for (size_t i = 0; i < _l1pt.GetNumberOfEntries(); i++)
        {
            size_t l1PartitionsOffset = _l1ptOffset + PartitionTable::HeaderSize();
            if (!_ioAccess->read(l1PartitionsOffset + i * PartitionTableEntry::Size(), entryData.data(),
                                 PartitionTableEntry::Size()))
            {
                return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
            }

            PartitionTableEntry entry;
            entry.Unpack(entryData);
            // entry.DumpStruct(); // for debug purposes
            _l1pt.AddEntry(entry);

            if (IsCshComponent((PartitionType)entry.GetSectionType()))
            {
                InitCshComponent((PartitionType)entry.GetSectionType(), entry.GetStartOffset(), entry.GetChainNumber());
            }

            if ((PartitionType)entry.GetSectionType() == PartitionType::PT_ROM_IMGS)
            {
                if (_cshComponents.empty())
                {
                    return errmsg("No ROM_IMGS CSH section found");
                }
                bool isActiveChain = _cshComponents.back().csh.isActiveChain();
                if (isActiveChain)
                {
                    MLXFWOPS_LOG_DEBUG("Fs6Operations::Init() - Setting activeChain to 0x%x", entry.GetChainNumber());
                    _activeChain = entry.GetChainNumber();
                    _l1pt.SetActiveChain(_activeChain);
                }
            }

            if (PartitionType(entry.GetSectionType()) == PartitionType::PT_CHAIN_CONTAINER &&
                entry.GetChainNumber() == _activeChain) // we assume that chain container follows rom_imgs and therefore
                                                        // we can trust that the active chain number was for sure set
            {
                _l2ptOffset = entry.GetStartOffset();
                if (!InitL2pt())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Fs6Operations::InitCshComponent(PartitionType partitionType, u_int32_t offset, int currentChain)
{
    vector<u_int8_t> cshHeader(fs5_image_layout_csh_header_size());
    if (!_ioAccess->read(offset, cshHeader.data(), fs5_image_layout_csh_header_size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    CSH::CshStructType cshStructType = CSH::GetCshStructType(cshHeader);
    vector<u_int8_t> cshData(CSH::HeaderSize(cshStructType));
    if (!_ioAccess->read(offset, cshData.data(), CSH::HeaderSize(cshStructType)))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    CSH csh;
    csh.UnpackHeader(cshData);

    cshData.resize(csh.GetNumberOfBinaries() * BinarySectionMetadata::Size());
    if (!_ioAccess->read(offset + CSH::HeaderSize(cshStructType), cshData.data(), cshData.size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }
    csh.UnpackSections(cshData);

    _cshComponents.push_back({partitionType, std::move(csh), currentChain});
    return true;
}

bool Fs6Operations::FwInit()
{
    FwInitCom();
    _fwImgInfo.fwType = (fw_img_type_t)FwType();
    return true;
}

bool Fs6Operations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::FwVerify");
    if (!Init())
    {
        return false;
    }

    report_callback(verifyCallBackFunc, "\nFS6 failsafe image\n\n");

    PrintDotSection(verifyCallBackFunc);

    PrintSectionRange(verifyCallBackFunc, _l1ptOffset, _l1ptOffset + _l1pt.Size() - 1, _l1pt.Size(),
                      "L1 Partition Table");

    int devInfoVaildAmount = 0;
    for (auto entry : _l1pt.GetEntries())
    {
        // TODO:: check if the image is reduced, and if so, skip DTOCs
        bool isKnownPartition = true;
        string partitionType = ToString((PartitionType)entry.GetSectionType());
        if (partitionType == "UNKNOWN")
        {
            partitionType = GetSectionNameByType(entry.GetSectionType());
            if (partitionType == "UNKNOWN")
            {
                partitionType = mft_utils::ToHexString(entry.GetSectionType(), 2);
                isKnownPartition = false;
            }
        }

        if (isKnownPartition)
        {
            if (IsCshComponent((PartitionType)entry.GetSectionType()))
            {
                if ((PartitionType)entry.GetSectionType() == PartitionType::PT_ROM_IMGS &&
                    entry.GetChainNumber() != _activeChain)
                {
                    continue;
                }
                if (!VerifyCshComponent((PartitionType)entry.GetSectionType(), entry.GetStartOffset(),
                                        verifyCallBackFunc))
                {
                    return false;
                }
            }
            else if (PartitionType(entry.GetSectionType()) == PartitionType::PT_CHAIN_CONTAINER &&
                     entry.GetChainNumber() == _activeChain)
            {
                bool isKnownPartition = true;
                PrintSectionRange(verifyCallBackFunc, _l2ptOffset, _l2ptOffset + _l2pt.Size() - 1, _l2pt.Size(),
                                  "L2 Partition Table");
                for (auto l2Entry : _l2pt.GetEntries())
                {
                    partitionType = ToString((PartitionType)l2Entry.GetSectionType());
                    if (partitionType == "UNKNOWN")
                    {
                        partitionType = mft_utils::ToHexString(l2Entry.GetSectionType(), 2);
                        isKnownPartition = false;
                    }

                    if (isKnownPartition)
                    {
                        if (IsCshComponent((PartitionType)l2Entry.GetSectionType()))
                        {
                            if (!VerifyCshComponent((PartitionType)l2Entry.GetSectionType(),
                                                    _l2ptOffset + l2Entry.GetStartOffset(), verifyCallBackFunc))
                            {
                                return false;
                            }
                        }
                    }
                    else
                    {
                        PrintSectionRange(verifyCallBackFunc, _l2ptOffset + l2Entry.GetStartOffset(),
                                          _l2ptOffset + l2Entry.GetStartOffset() + l2Entry.GetSectionSize() - 1,
                                          l2Entry.GetSectionSize(), partitionType, "L2 Partition");
                    }
                    _l2ptEnd = _l2ptOffset + l2Entry.GetStartOffset() + l2Entry.GetSectionSize();
                }
            }
            else if (PartitionType(entry.GetSectionType()) == PartitionType::PT_DEV_INFO)
            {
                vector<u_int8_t> dev_info_data;
                dev_info_data.resize(entry.GetSectionSize());
                if (!_ioAccess->read(entry.GetStartOffset(), dev_info_data.data(), entry.GetSectionSize()))
                {
                    return errmsg("%s - read error (%s)\n", "DEV_INFO", (*_ioAccess).err());
                }

                bool isDevInfoValid = FwOperations::CheckDevInfoSignature((u_int32_t*)dev_info_data.data());
                if (isDevInfoValid)
                {
                    devInfoVaildAmount++;
                    if (devInfoVaildAmount == 1)
                    {
                        PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(),
                                          entry.GetStartOffset() + entry.GetSectionSize() - 1, entry.GetSectionSize(),
                                          partitionType, "L1 Partition");
                    }
                }
                if (devInfoVaildAmount > 1)
                {
                    return errmsg("Multiple DEV_INFO sections found with valid signatures");
                }
            }
            else
            {
                PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(),
                                  entry.GetStartOffset() + entry.GetSectionSize() - 1, entry.GetSectionSize(),
                                  partitionType, "L1 Partition");
            }
        }
        else
        {
            PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(),
                              entry.GetStartOffset() + entry.GetSectionSize() - 1, entry.GetSectionSize(),
                              partitionType, "L1 Partition");
        }
    }

    if (devInfoVaildAmount == 0 && !GetIsReducedImage())
    {
        return errmsg("No DEV_INFO section found with valid signature");
    }

    if (_activeChain == INVALID_CHAIN_NUMBER)
    {
        return errmsg("No active chain found"); // no valid use case in which the flash/image will only have a
                                                // backup/invalid chain without an active one
    }

    return true;
}

string Fs6Operations::GetSectionNameByMagicId(u_int32_t magicId)
{
    string sectionName = BinarySectionMetadata::CshSectionIDToString(magicId);
    if (sectionName == "UNKNOWN")
    {
        sectionName = FwOperations::GetSectionNameByType(magicId);
    }
    return sectionName;
}

bool Fs6Operations::VerifyCshComponent(PartitionType partitionType, u_int32_t offset, VerifyCallBack verifyCallBackFunc)
{
    auto cshComponent =
      find_if(_cshComponents.begin(), _cshComponents.end(),
              [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });

    if (cshComponent != _cshComponents.end())
    {
        string compName = ToString(CshComponentID(cshComponent->csh.GetComponentId()));
        PrintSectionRange(verifyCallBackFunc, offset, offset + cshComponent->csh.GetCshSize() - 1,
                          cshComponent->csh.GetCshSize(), compName, "CSH");

        u_int32_t prevSectionEnd = cshComponent->csh.GetCshSize();
        u_int32_t currSectionBegin = 0;
        string sectionName;

        for (auto section : cshComponent->csh.GetSections())
        {
            sectionName = GetSectionNameByMagicId(section.GetSectionType());
            size_t sectionOffset = offset + section.GetSectionOffset();
            PrintSectionRange(verifyCallBackFunc, sectionOffset, sectionOffset + section.GetSectionSize() - 1,
                              section.GetSectionSize(), sectionName, "CSH Section");

            currSectionBegin = section.GetSectionOffset();
            if (currSectionBegin < prevSectionEnd)
            {
                return errmsg("section %s intersects with the previous section", sectionName.c_str());
            }
            prevSectionEnd = section.GetSectionOffset() + section.GetSectionSize();
        }

        if (prevSectionEnd > cshComponent->csh.GetComponentSize())
        {
            return errmsg("section %s is out of CSH bounds", sectionName.c_str());
        }
    }

    return true;
}

bool Fs6Operations::GetImageSize(u_int32_t* image_size)
{
    *image_size = _ioAccess->get_size();
    return true;
}

bool Fs6Operations::FwReadData(void* image, u_int32_t* image_size, bool verbose)
{
    (void)verbose;
    (void)image_size;
    if (image != NULL)
    {
        if (!_ioAccess->read(0, (u_int32_t*)image, _ioAccess->get_size()))
        {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }
    return true;
}

bool Fs6Operations::ReadComponent(ComponentType compName,
                                  ComponentHeader compHeader,
                                  string,
                                  vector<u_int8_t>& componentData)
{
    u_int32_t componentOffset = 0;
    u_int32_t componentSize = 0;
    CshComponentID cshId = ToCshId(compName);
    PartitionType partitionType = ToPartitionType(cshId);
    if (cshId == CshComponentID::Unknown)
    {
        return errmsg("Unknown component");
    }

    if (compHeader != ComponentHeader::Header_With)
    {
        return errmsg("Only header with component supported at the moment");
    }

    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    if (IsL2ptSection(cshId))
    {
        componentSize = _l2pt.GetEntrySize(partitionType);
        componentOffset = _l2pt.GetEntryOffset(partitionType);
        componentOffset += _l2ptOffset;
    }
    else
    {
        componentSize = _l1pt.GetEntrySize(partitionType);
        componentOffset = _l1pt.GetEntryOffset(partitionType);
    }

    componentData.resize(componentSize);
    if (!_ioAccess->read(componentOffset, componentData.data(), componentData.size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    return true;
}

void Fs6Operations::CopyMagicPattern(size_t componentOffset, vector<u_int8_t>& compData)
{
    const size_t magicPatternOffset = 0xc;
    vector<u_int8_t> magicPattern(4);
    if (!_ioAccess->read(componentOffset + magicPatternOffset, magicPattern.data(), magicPattern.size()))
    {
        throw std::runtime_error(std::string("CSH header read error at offset 0x") +
                                 mft_utils::ToHexString(componentOffset + magicPatternOffset, 8) + " (" +
                                 (*_ioAccess).err() + ")");
    }
    std::copy(magicPattern.begin(), magicPattern.end(), compData.begin() + magicPatternOffset);
}

bool Fs6Operations::SetSignedFWComponent(string binPath, ComponentType compName, const char* msg)
{
    CshComponentID cshId = ToCshId(compName);
    u_int32_t componentOffset = 0;
    if (cshId == CshComponentID::Unknown)
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "Unknown component");
    }

    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    vector<u_int8_t> compData;
    if (!ReadBinFile(binPath.c_str(), compData))
    {
        return false;
    }

    bool isL2pt = IsL2ptSection(cshId);

    if (isL2pt)
    {
        _l2pt.SetEntrySize(ToPartitionType(cshId), compData.size());
        componentOffset = _l2pt.GetEntryOffset(ToPartitionType(cshId));
        componentOffset += _l2ptOffset;
    }
    else
    {
        _l1pt.SetEntrySize(ToPartitionType(cshId), compData.size());
        if (cshId == CshComponentID::ROM_IMGS)
        {
            _l1pt.SetEntrySize(ToPartitionType(cshId), compData.size(), _activeChain == 0 ? 1 : 0);
        }
        componentOffset = _l1pt.GetEntryOffset(ToPartitionType(cshId));
    }

    UpdatePartitionTable(!isL2pt);

    if (cshId == CshComponentID::ROM_IMGS)
    {
        CopyMagicPattern(componentOffset, compData);
    }

    if (!_ioAccess->write(componentOffset, compData.data(), compData.size()))
    {
        return errmsg("%s - write error (%s)\n", msg, _ioAccess->err());
    }

    return true;
}

bool Fs6Operations::GetFwComponentsData(string path)
{
    Json::Value root;
    if (!Init())
    {
        return false;
    }

    vector<PartitionType> partitionTypes = {PartitionType::PT_ROM_IMGS, PartitionType::PT_NV_FWS,
                                            PartitionType::PT_OEM_FWS, PartitionType::PT_SBD_FW};

    for (auto partitionType : partitionTypes)
    {
        auto entry =
          std::find_if(_cshComponents.begin(), _cshComponents.end(),
                       [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });
        if (entry == _cshComponents.end())
        {
            throw runtime_error("Partition type " + ToString(partitionType) + " not found in the image");
        }

        std::stringstream stream;
        stream << "0x" << std::hex << static_cast<int>(entry->csh.GetComponentMajorVersion());
        root[ToString(ToCshId(partitionType))]["ver_major"] = stream.str();
        stream.str("");
        stream << "0x" << std::hex << static_cast<int>(entry->csh.GetComponentMinorVersion());
        root[ToString(ToCshId(partitionType))]["ver_minor"] = stream.str();
    }

    if (!path.empty())
    {
        std::ofstream outputFileStream(path);
        outputFileStream << root;
    }
    else
    {
        cout << root << endl;
    }

    return true;
}

bool Fs6Operations::CheckFwVersion(ComponentFwVersion, u_int8_t)
{
    return true;
}

const char* Fs6Operations::FwGetResetRecommandationStr()
{
    return REBOOT_REQUIRED_STR;
}

bool Fs6Operations::GetPartitionEntryInfo(PartitionType partitionType,
                                          size_t& sectionOffset,
                                          size_t& sectionSize,
                                          int chainNumber)
{
    ResolveChainNumber(chainNumber, _activeChain);

    PartitionValidator validator(partitionType);
    bool isL2pt = IsL2ptSection(partitionType);

    const PartitionTable* pt = isL2pt ? &_l2pt : &_l1pt;
    size_t baseOffset = isL2pt ? _l2ptOffset : 0;

    for (auto entry : pt->GetEntries())
    {
        if ((PartitionType)entry.GetSectionType() == partitionType)
        {
            if (validator.validate(entry, _ioAccess, chainNumber))
            {
                sectionOffset = baseOffset + entry.GetStartOffset();
                sectionSize = entry.GetSectionSize();
                return true;
            }
        }
    }

    return errmsg("Partition type 0x%x not found or validation failed", (int)partitionType);
}

bool Fs6Operations::ReadPartitionInfo(PartitionType partitionType, vector<u_int8_t>& data, int chainNumber)
{
    size_t section_offset;
    size_t section_size;
    if (!GetPartitionEntryInfo(partitionType, section_offset, section_size, chainNumber))
    {
        return false;
    }

    string partitionName = ToString(partitionType);
    MLXFWOPS_LOG_DEBUG("Fs6Operations::ReadPartitionInfo %s_section_offset=0x%zx, %s_section_size=0x%zx", partitionName.c_str(),
             section_offset, partitionName.c_str(), section_size);

    data.resize(section_size);
    if (!_ioAccess->read(section_offset, data.data(), section_size))
    {
        return errmsg("%s - read error (%s)\n", partitionName.c_str(), (*_ioAccess).err());
    }

    return true;
}

bool Fs6Operations::GetDevInfo(u_int8_t* buff)
{
    vector<u_int8_t> devInfoData;
    if (!ReadPartitionInfo(PartitionType::PT_DEV_INFO, devInfoData))
    {
        return false;
    }

    return FwOperations::GetDevInfo(devInfoData.data());
}

bool Fs6Operations::GetMfgInfo(u_int8_t* buff)
{
    vector<u_int8_t> mfg_info_data;
    if (!ReadPartitionInfo(PartitionType::PT_MFG_INFO, mfg_info_data))
    {
        return false;
    }

    if (!FwOperations::GetMfgInfo(mfg_info_data.data()))
    {
        return false;
    }

    // Convert from FS6 hi/lo format to FS3 64-bit format
    fs6_image_layout_mfg_info fs6_mfg_info;
    fs6_image_layout_mfg_info_unpack(&fs6_mfg_info, mfg_info_data.data());

    _fsCommonInfo.ext_info.orig_fs3_uids_info.image_layout_uids.base_guid.uid =
      ((u_int64_t)fs6_mfg_info.guids.guids.uid.hi << 32) | fs6_mfg_info.guids.guids.uid.lo;

    _fsCommonInfo.ext_info.orig_fs3_uids_info.image_layout_uids.base_mac.uid =
      ((u_int64_t)fs6_mfg_info.guids.macs.uid.hi << 32) | fs6_mfg_info.guids.macs.uid.lo;

    return true;
}

bool Fs6Operations::ReadCshSectionInfo(PartitionType partitionType,
                                       CshSectionType sectionType,
                                       size_t sectionSize,
                                       vector<u_int8_t>& data,
                                       int chainNumber)
{
    size_t section_addr;
    if (!GetCshSectionOffset(partitionType, sectionType, section_addr, chainNumber))
    {
        return false; // Error already set by GetCshSectionOffset
    }

    MLXFWOPS_LOG_DEBUG("Fs6Operations::ReadCshSectionInfo section_addr = 0x%zx, section_size = 0x%zx", section_addr, sectionSize);

    data.resize(sectionSize);
    if (!_ioAccess->read(section_addr, data.data(), sectionSize))
    {
        return errmsg("CSH_SECTION - read error (%s)\n", (*_ioAccess).err());
    }

    return true;
}

bool Fs6Operations::GetImageInfo()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetImageInfo");

    vector<u_int8_t> image_info_data;
    if (!ReadCshSectionInfo(PartitionType::PT_SWITCH_FWS,
                            CshSectionType::CSH_SECTION_IMAGE_INFO_MAGIC_ID,
                            FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE,
                            image_info_data))
    {
        // TODO: fallback for backward compatibility
        if (!ReadCshSectionInfo(PartitionType::PT_SWITCH_FWS,
                                CshSectionType::CSH_SECTION_IMAGE_INFO,
                                FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE,
                                image_info_data))
        {
            return false;
        }
    }

    struct fs6_image_layout_image_info image_info;
    fs6_image_layout_image_info_unpack(&image_info, image_info_data.data());

    if (image_info.major_version != 0)
    {
        return errmsg(MLXFW_UNKNOWN_SECT_VER_ERR, "Unknown IMAGE_INFO format version (%d.%d).",
                      image_info.major_version, image_info.minor_version);
    }

    _fwImgInfo.ext_info.image_info_minor_version = image_info.minor_version;
    _fwImgInfo.ext_info.image_info_major_version = image_info.major_version;

    _fwImgInfo.ext_info.fw_ver[0] = image_info.FW_VERSION.MAJOR;
    _fwImgInfo.ext_info.fw_ver[1] = image_info.FW_VERSION.MINOR;
    _fwImgInfo.ext_info.fw_ver[2] = image_info.FW_VERSION.SUBMINOR;

    // _fwImgInfo.ext_info.isfu_major = image_info.module_versions.mad.major; // this field doesn't exist in
    // fs6_image_layout_image_info

    _fwImgInfo.ext_info.mic_ver[0] = image_info.mic_version.MAJOR;
    _fwImgInfo.ext_info.mic_ver[1] = image_info.mic_version.MINOR;
    _fwImgInfo.ext_info.mic_ver[2] = image_info.mic_version.SUBMINOR;

    _fwImgInfo.ext_info.fw_rel_date[0] = (u_int16_t)image_info.FW_VERSION.Day;
    _fwImgInfo.ext_info.fw_rel_date[1] = (u_int16_t)image_info.FW_VERSION.Month;
    _fwImgInfo.ext_info.fw_rel_date[2] = (u_int16_t)image_info.FW_VERSION.Year;

    _fwImgInfo.ext_info.fw_rel_time[0] = (u_int16_t)image_info.FW_VERSION.Hour;
    _fwImgInfo.ext_info.fw_rel_time[1] = (u_int16_t)image_info.FW_VERSION.Minutes;
    _fwImgInfo.ext_info.fw_rel_time[2] = (u_int16_t)image_info.FW_VERSION.Seconds;

    _fwImgInfo.ext_info.burn_image_size = image_info.burn_image_size;
    _fwImgInfo.ext_info.dtoc_offset = image_info.dtoc_offset;
    // _fwImgInfo.ext_info.sku = (device_sku)image_info.psc_sku; // this field doesn't exist in
    // fs6_image_layout_image_info

    // assuming number of supported_hw_id < MAX_NUM_SUPP_HW_IDS
    memcpy(_fwImgInfo.supportedHwId, image_info.supported_hw_id, sizeof(image_info.supported_hw_id));
    _fwImgInfo.supportedHwIdNum = (sizeof(image_info.supported_hw_id)) / sizeof(image_info.supported_hw_id[0]);

    // _fwImgInfo.ext_info.pci_device_id = image_info.pci_device_id; // this field doesn't exist in
    // fs6_image_layout_image_info

    strcpy(_fsCommonInfo.ext_info.image_vsd, image_info.vsd);
    strcpy(_fwImgInfo.ext_info.psid, image_info.psid);
    strcpy(_fwImgInfo.ext_info.product_ver, image_info.prod_ver);

    // get name, prs name and description
    if (image_info.minor_version == 2) // TODO: took it from original getImageInfo - do we need it here too? same
                                       // offsets as in fs6's layout so seems redundent
    {
        struct tools_open_image_info tools_image_info;
        memset(&tools_image_info, 0, sizeof(tools_image_info));
        tools_open_image_info_unpack(&tools_image_info, image_info_data.data());
        strncpy(_fsCommonInfo.ext_info.name, tools_image_info.name, strlen(tools_image_info.name));
        strncpy(_fsCommonInfo.ext_info.description, tools_image_info.description, strlen(tools_image_info.description));
        strncpy(_fsCommonInfo.ext_info.prs_name, tools_image_info.prs_name, strlen(tools_image_info.prs_name));
    }
    else if (image_info.minor_version == 3)
    {
        strncpy(_fsCommonInfo.ext_info.name, image_info.name, strlen(image_info.name));
        strncpy(_fsCommonInfo.ext_info.description, image_info.description, strlen(image_info.description));
        strncpy(_fsCommonInfo.ext_info.prs_name, image_info.prs_name, strlen(image_info.prs_name));
    }

    _fsCommonInfo.ext_info.mcc_en = image_info.mcc_en;
    _fsCommonInfo.ext_info.security_mode =
      (_fsCommonInfo.ext_info.security_mode | ((image_info.mcc_en == 1) ? SMM_MCC_EN : 0) |
       ((image_info.debug_fw == 1) ? SMM_DEBUG_FW : 0) | ((image_info.signed_fw == 1) ? SMM_SIGNED_FW : 0) |
       ((image_info.secure_fw == 1) ? SMM_SECURE_FW : 0));

    _fsCommonInfo.runFromAny = image_info.image_size.run_from_any;
    _fsCommonInfo.logStep = image_info.image_size.log_step;
    _fsCommonInfo.ext_info.ini_file_version = image_info.ini_file_num;

    const u_int32_t* swId = (u_int32_t*)NULL;
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetImageInfo _fwImgInfo.supportedHwId[0]=0x%x", _fwImgInfo.supportedHwId[0]);
    if (!getInfoFromHwDevid(_fwImgInfo.supportedHwId[0], _fwImgInfo.ext_info.chip_type, &swId))
    {
        return false;
    }

    // copy the vsd to the branch ver only for switches. Not valid for NICs.
    if (!IS_HCA(_fwImgInfo.ext_info.chip_type))
    {
        if (VerifyBranchFormat(image_info.vsd))
        {
            strncpy(_fwImgInfo.ext_info.branch_ver, image_info.vsd, BRANCH_LEN);
            _fwImgInfo.ext_info.branch_ver[BRANCH_LEN - 1] = '\0';
        }
    }

    _fwImgInfo.ext_info.encrypted_fw = image_info.encrypted_fw;

    return true;
}

bool Fs6Operations::GetCshSectionOffset(PartitionType partitionType,
                                        CshSectionType sectionType,
                                        size_t& CshSectionOffset,
                                        int chainNumber)
{
    // Find the partition table entry
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset partitionType = 0x%x, sectionType = 0x%x", (int)partitionType,
             (int)sectionType);

    ResolveChainNumber(chainNumber, _activeChain);
    size_t partitionOffset = 0;

    bool isL2pt = IsL2ptSection(ToCshId(partitionType));
    if (isL2pt)
    {
        MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset isL2pt");
        std::vector<PartitionTableEntry> l2Entries = _l2pt.GetEntries();
        auto l2Entry = find_if(l2Entries.begin(), l2Entries.end(),
                               [partitionType](const PartitionTableEntry& entry)
                               { return (PartitionType)entry.GetSectionType() == partitionType; });

        if (l2Entry == l2Entries.end())
        {
            return errmsg("Partition Table Entry for type 0x%x not found", (int)partitionType);
        }
        partitionOffset =
          _l2ptOffset + l2Entry->GetStartOffset(); // in L2PT the offfset is relative to the start of L2PT
    }
    else
    {
        MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset isL1pt");
        std::vector<PartitionTableEntry> l1Entries = _l1pt.GetEntries();
        auto l1Entry = l1Entries.end();
        for (auto it = l1Entries.begin(); it != l1Entries.end(); ++it)
        {
            PartitionType entryPartitionType = PartitionType(it->GetSectionType());
            if (entryPartitionType == partitionType)
            {
                if (entryPartitionType == PartitionType::PT_ROM_IMGS ||
                    entryPartitionType == PartitionType::PT_CHAIN_CONTAINER)
                {
                    if (it->GetChainNumber() == chainNumber)
                    {
                        l1Entry = it;
                        break;
                    }
                }
                else
                {
                    l1Entry = it;
                    break;
                }
            }
        }

        if (l1Entry == l1Entries.end())
        {
            return errmsg("Partition Table Entry for type 0x%x not found", (int)partitionType);
        }
        partitionOffset = l1Entry->GetStartOffset(); // in L1PT the offfset is absolute
    }

    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset partitionOffset = 0x%zx", partitionOffset);

    // Find the CSH component
    auto cshComponent =
      find_if(_cshComponents.begin(), _cshComponents.end(),
              [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });

    if (cshComponent == _cshComponents.end())
    {
        return errmsg("CSH component for partition type 0x%x not found", (int)partitionType);
    }

    // Find the specific section within the CSH component
    auto section = find_if(cshComponent->csh.GetSections().begin(),
                           cshComponent->csh.GetSections().end(),
                           [sectionType](const BinarySectionMetadata& section)
                           { return (CshSectionType)section.GetSectionType() == sectionType; });

    if (section == cshComponent->csh.GetSections().end())
    {
        return errmsg("Section type 0x%x not found in CSH component", (int)sectionType);
    }

    // Calculate the final section offset
    CshSectionOffset = partitionOffset + section->GetSectionOffset();
    return true;
}

bool Fs6Operations::FwQuery(fw_info_t* fwInfo,
                            bool readRom,
                            bool isStripedImage,
                            bool quickQuery,
                            bool ignoreDToc,
                            bool verbose)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::FwQuery");

    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    if (!GetImageInfo())
    {
        return false;
    }

    if (!GetIsReducedImage() && !isStripedImage && !ignoreDToc)
    {
        if ((!GetMfgInfo() && !GetDevInfo()))
        {
            return false;
        }
    }

    fwInfo->fw_type = FwType();

    memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs3_info), &(_fsCommonInfo.ext_info), sizeof(fs3_info_t));

    return true;
}

#ifndef MST_CPU_armv7l_umbriel // {
bool Fs6Operations::SignForSecureBoot(const char*, const char*, const MlxSign::Signer&)
{
    return Unsupported(__FUNCTION__);
}
#endif // } MST_CPU_armv7l_umbriel

void Fs6Operations::UpdatePartitionTable(bool l1pt)
{
    vector<u_int8_t> partitionTable;
    u_int32_t partitionTableOffset = _l1ptOffset; // l1pt

    if (l1pt)
    {
        _l1pt.CalcDigest();
        partitionTable = _l1pt.Pack();
    }
    else
    {
        _l2pt.CalcDigest();
        partitionTable = _l2pt.Pack();
        partitionTableOffset = _l2ptOffset;
    }

    if (!_ioAccess->write(partitionTableOffset, partitionTable.data(), partitionTable.size()))
    {
        string err = "write error - " + string(_ioAccess->err());
        throw runtime_error(err);
    }
}

bool Fs6Operations::IsL2ptSection(CshComponentID cshId)
{
    if (cshId != CshComponentID::ROM_IMGS && cshId != CshComponentID::Unknown)
    {
        return true;
    }
    return false;
}

bool Fs6Operations::IsL2ptSection(PartitionType partitionType)
{
    if (partitionType == PartitionType::PT_NV_FWS || partitionType == PartitionType::PT_OEM_FWS ||
        partitionType == PartitionType::PT_BCT_DTB || partitionType == PartitionType::PT_SWITCH_FWS ||
        partitionType == PartitionType::PT_SBD_FW)
    {
        return true;
    }
    return false;
}

bool Fs6Operations::CheckAndSetIsReducedImage()
{
    if (!Init())
    {
        return false;
    }
    // TODO: Implement logic verification that checks if this is a valid reduced image with complete content
    return true;
}

u_int32_t Fs6Operations::GetL2ptSectionsSize()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetL2ptSectionsSize");

    if (_l2pt.GetEntries().empty())
    {
        return errmsg("L2PT is empty");
    }
    // Get last entry in L2PT (the partition that holds CSH sections)
    vector<PartitionTableEntry> l2entries = _l2pt.GetEntries();
    const PartitionTableEntry& lastL2Entry = l2entries.back();

    return lastL2Entry.GetStartOffset() + lastL2Entry.GetSectionSize();
}

bool Fs6Operations::FwExtract4MBImage(vector<u_int8_t>& img,
                                      bool maskMagicPatternAndDevToc,
                                      bool verbose,
                                      bool ignoreImageStart,
                                      bool imageSizeOnly)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::FwExtract4MBImage");
    if (!Init())
    {
        return false;
    }

    PartitionTableEntry RomImagesEntry = _l1pt.GetEntry(PartitionType::PT_ROM_IMGS);
    size_t startRomImages = RomImagesEntry.GetStartOffset();
    u_int32_t l2ptSectionsSize = GetL2ptSectionsSize();

    if (l2ptSectionsSize == 0)
    {
        return false;
    }

    img.resize(ROM_IMGS_ALIGN_SIZE + l2ptSectionsSize);

    // Read ROM images
    if (!_ioAccess->read(startRomImages, img.data(), ROM_IMGS_ALIGN_SIZE))
    {
        return false;
    }

    // Read CSH sections
    if (!_ioAccess->read(_l2ptOffset, img.data() + ROM_IMGS_ALIGN_SIZE, l2ptSectionsSize))
    {
        return false;
    }

    if (maskMagicPatternAndDevToc)
    {
        memset(img.data() + ROM_IMGS_MAGIC_PATTERN_OFFSET, 0xFF, 4);
    }

    return true;
}

bool Fs6Operations::FwReadRom(std::vector<u_int8_t>& romSect)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwBurnRom(FImage* romImg,
                              bool ignoreProdIdCheck,
                              bool ignoreDevidCheck,
                              ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwBurn(FwOperations* imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    // Verify that imageOps is actually an FS6 image
    if (imageOps->FwType() != FIT_FS6)
    {
        return errmsg("Expected FS6 image but got type %d", imageOps->FwType());
    }

    if (!checkAndDisableFlashWpIfRequired())
    {
        return errmsg("Failed to check and disable flash write protection if from bottom.\n");
    }

    // Cast to FImage to access the image buffer
    FImage* fim = (FImage*)(imageOps->GetIoAccess());
    u_int8_t* imageData = (u_int8_t*)fim->getBuf();

    if (imageData == NULL)
    {
        restoreWriteProtectInfo();
        return errmsg("Failed to get image buffer");
    }

    uint32_t imageStart = 0;
    Fs6Operations* fs6ImageOps = static_cast<Fs6Operations*>(imageOps);
    uint32_t l2ptEnd = fs6ImageOps->GetL2ptEnd();
    uint32_t dtocStart = 0x01f00000;
    uint32_t dtocEnd = 0x01ff813f;
    uint32_t totalSize = l2ptEnd - imageStart + dtocEnd - dtocStart;

    MLXFWOPS_LOG_DEBUG("writing data from address 0x%x to 0x%x ", imageStart, l2ptEnd);
    MLXFWOPS_LOG_DEBUG("size: 0x%x ", l2ptEnd - imageStart);
    MLXFWOPS_LOG_DEBUG("writing data from address 0x%x to 0x%x ", dtocStart, dtocEnd);
    MLXFWOPS_LOG_DEBUG("size: 0x%x ", dtocEnd - dtocStart);
    MLXFWOPS_LOG_DEBUG("total size: 0x%x ", l2ptEnd - imageStart + dtocEnd - dtocStart);

    if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc, imageStart,
                      imageData, l2ptEnd - imageStart, true, true, totalSize, 0))
    {
        restoreWriteProtectInfo();
        return errmsg("Failed to burn image until end of L2PT - %s\n", this->err());
    }
    MLXFWOPS_LOG_DEBUG("finished writing data from address 0x%x to 0x%x", imageStart, l2ptEnd);

    if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc, dtocStart,
                      imageData, dtocEnd - dtocStart, true, true, totalSize, l2ptEnd - imageStart))
    {
        restoreWriteProtectInfo();
        return errmsg("Failed to burn DTOC area - %s\n", this->err());
    }
    MLXFWOPS_LOG_DEBUG("finished writing data from address 0x%x to 0x%x", dtocStart, dtocEnd);

    if (!restoreWriteProtectInfo())
    {
        return errmsg("Post-burn operation failed: Failed to restore flash write protection if from bottom.\n");
    }

    return true;
}

bool Fs6Operations::FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwResetNvData()
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwShiftDevData(PrintCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwCalcMD5(u_int8_t md5sum[16])
{
    return Unsupported(__FUNCTION__);
}

void Fs6Operations::PrintDotSection(VerifyCallBack verifyCallBackFunc)
{
    const string dotMagicId = "DOTB";
    const string s2aMagicId = "S2AB";
    const size_t sectionSize = 0x400;

    if (!std::all_of(begin(_dotMagicId), end(_dotMagicId), [](u_int8_t val) { return val == 0 || val == 0xff; }))
    {
        string sectionMagicId = string(reinterpret_cast<char*>(_dotMagicId), 4);

        if (sectionMagicId != dotMagicId && sectionMagicId != s2aMagicId)
        {
            sectionMagicId = "UNKNOWN";
        }

        PrintSectionRange(verifyCallBackFunc, 0, sectionSize - 1, sectionSize, sectionMagicId);
    }
}

void Fs6Operations::PrintSectionRange(VerifyCallBack verifyCallBackFunc,
                                      u_int32_t startAddr,
                                      u_int32_t endAddr,
                                      u_int32_t size,
                                      const string& sectionType,
                                      const string& suffix)
{
    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << startAddr << "-0x" << std::setw(8)
       << std::setfill('0') << endAddr << " (0x" << std::setw(6) << std::setfill('0') << size << ")/ " << std::left
       << std::setw(25) << std::setfill(' ') << sectionType << " | " << suffix << std::endl;
    report_callback(verifyCallBackFunc, ss.str().c_str());
}

bool Fs6Operations::PartitionValidator::validateDevInfo(const PartitionTableEntry& entry,
                                                        FBase* ioAccess,
                                                        int activeChain)
{
    vector<u_int8_t> dev_info_data;
    dev_info_data.resize(entry.GetSectionSize());
    if (!ioAccess->read(entry.GetStartOffset(), dev_info_data.data(), entry.GetSectionSize()))
    {
        return false;
    }
    return FwOperations::CheckDevInfoSignature((u_int32_t*)dev_info_data.data());
}

bool Fs6Operations::PartitionValidator::validateRomImgsAndChainContainer(const PartitionTableEntry& entry,
                                                                         FBase* ioAccess,
                                                                         int activeChain)
{
    if (entry.GetChainNumber() == activeChain)
    {
        return true;
    }
    return false;
}

Fs6Operations::PartitionValidator::PartitionValidator(PartitionType partitionType)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::PartitionValidator, partitionType 0x%x", (int)partitionType);

    switch (partitionType)
    {
        case PartitionType::PT_DEV_INFO:
            _validator = &validateDevInfo;
            break;

        case PartitionType::PT_ROM_IMGS:
            _validator = &validateRomImgsAndChainContainer;
            break;

        case PartitionType::PT_CHAIN_CONTAINER:
            _validator = &validateRomImgsAndChainContainer;
            break;

            // Add more partition-specific validations here

        default:
            _validator = &defaultValidator;
            break;
    }
}

bool Fs6Operations::PartitionValidator::validate(const PartitionTableEntry& entry,
                                                 FBase* ioAccess,
                                                 int activeChain) const
{
    return _validator(entry, ioAccess, activeChain);
}
