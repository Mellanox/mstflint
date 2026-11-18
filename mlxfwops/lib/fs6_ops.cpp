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
#include "common/tools_string.h"
#include "image_crc.h"

#ifndef MST_CPU_armv7l_umbriel // {
#ifdef MFT_LEGACY_BUILD
#include "fs_csh_ops.h"
#else
#include "components/fs_csh_ops.h"
#endif
#endif // } MST_CPU_armv7l_umbriel

#ifdef MFT_LEGACY_BUILD
#include <mft_utils.h>
#else
#include "mft_utils/mft_utils.h"
#endif

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <sstream>
#include <utility>

using nbu::mft::common::string_format;

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
        case ComponentType::Comp_Csh_Oem_Fws: // TODO backwards compatibility - remove after FS6 is fully adopted
            id = CshComponentID::OEM_FWS;
            break;
        case ComponentType::Comp_Csh_Caliptra_Fw:
            id = CshComponentID::CALIPTRA_FW;
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
        case ComponentType::Comp_Csh_Vmod_Fw:
            id = CshComponentID::VMOD_FW;
            break;
        default:
            break;
    }
    return id;
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
        case PartitionType::PT_CALIPTRA_FW:
            return CSH::CALIPTRA_FW_NAME;
        case PartitionType::PT_NV_FWS:
            return CSH::NV_FWS_NAME;
        case PartitionType::PT_SWITCH_FWS:
            return CSH::SWITCH_FWS_NAME;
        case PartitionType::PT_SBD_FW:
            return CSH::SBD_FW_NAME;
        case PartitionType::PT_VMOD_FW:
            return CSH::VMOD_FW_NAME;
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
        case PartitionType::PT_FW_NV_LOG:
            return "FW_NV_LOG";
        case PartitionType::PT_CPO_CALIBRATION_DATA:
            return "CPO_CALIBRATION_DATA";
        case PartitionType::PT_CRC_INFO:
            return "CRC_INFO";
        case PartitionType::PT_WP_AREA_PTR:
            return "WP_AREA_PTR";
        case PartitionType::PT_RW_AREA_PTR:
            return "RW_AREA_PTR";
        case PartitionType::PT_PQC_L4_CERTIFICATE_1:
            return "PQC_L4_CERTIFICATE_1";
        case PartitionType::PT_PQC_L4_CERTIFICATE_2:
            return "PQC_L4_CERTIFICATE_2";
        default:
            return "UNKNOWN";
    }
}

Fs6Operations::Fs6Operations(FBase* ioAccess) :
    FwOperations(ioAccess),
    _l1ptOffset(L1PT_OFFSET),
    _l2ptOffset(0),
    _l3pwOffset(0),
    _l3prOffset(0),
    _WPAreaPtr(0),
    _RWAreaPtr(0),
    _activeChain(INVALID_CHAIN_NUMBER),
    _backupChain(INVALID_CHAIN_NUMBER),
    _vmodAdmStatusA(CSH::VMOD_ADM_STATUS_UNKNOWN),
    _vmodAdmStatusB(CSH::VMOD_ADM_STATUS_UNKNOWN),
    _secondL1ptExists(false)
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

        if (IsCshComponent(entry.GetPartitionTypeEnum()))
        {
            InitCshComponent(entry);
        }
        _l2pt.AddEntry(entry);
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
    std::vector<int> invalidChains; // for logging invalid chains

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
        // Reduced image doesn't have L1PT, it only contains ROM_IMGS and CHAIN_CONTAINER
        PartitionTableEntry romImgsEntry(0, ROM_IMGS_ALIGN_SIZE, static_cast<u_int32_t>(PartitionType::PT_ROM_IMGS));

        _activeChain = romImgsEntry.GetChainNumber();
        _l1pt.SetActiveChain(_activeChain);

        _l1pt.AddEntry(romImgsEntry);
        if (!InitCshComponent(romImgsEntry))
        {
            return errmsg(MLXFW_NO_VALID_IMAGE_ERR,
                          "\nNo valid FS6 image found. Check the flash parameters, if specified.");
        }

        u_int32_t imageSize = 0;
        GetImageSize(&imageSize);
        PartitionTableEntry chainContainerEntry(ROM_IMGS_ALIGN_SIZE, imageSize - ROM_IMGS_ALIGN_SIZE,
                                                static_cast<u_int32_t>(PartitionType::PT_CHAIN_CONTAINER));
        _l1pt.AddEntry(chainContainerEntry);

        _l2ptOffset = ROM_IMGS_ALIGN_SIZE;
        if (!InitL2pt())
        {
            return errmsg(MLXFW_NO_VALID_IMAGE_ERR,
                          "\nNo valid FS6 image found. Check the flash parameters, if specified.");
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
            if (IsCshComponent(entry.GetPartitionTypeEnum()))
            {
                InitCshComponent(entry);
            }
            _l1pt.AddEntry(entry);

            if (entry.GetPartitionTypeEnum() == PartitionType::PT_ROM_IMGS)
            {
                if (_cshComponents.empty())
                {
                    return errmsg("No ROM_IMGS CSH section found");
                }
                if (entry.IsCshActiveChain())
                {
                    _activeChain = entry.GetChainNumber();
                    _l1pt.SetActiveChain(_activeChain);
                }
                else
                {
                    if (entry.IsCshBackupChain())
                    {
                        _backupChain = entry.GetChainNumber();
                    }
                    else
                    {
                        invalidChains.push_back(entry.GetChainNumber());
                    }
                }
            }

            if (entry.GetPartitionTypeEnum() == PartitionType::PT_VMOD_FW)
            {
                if (_vmodAdmStatusA == CSH::VMOD_ADM_STATUS_UNKNOWN)
                {
                    if (entry.GetCsh() != nullptr)
                    {
                        _vmodAdmStatusA = entry.GetCsh()->GetVmodAdmStatus();
                    }
                    else
                    {
                        _vmodAdmStatusA = CSH::VMOD_ADM_STATUS_INVALID;
                    }
                }
                else if (_vmodAdmStatusB == CSH::VMOD_ADM_STATUS_UNKNOWN)
                {
                    if (entry.GetCsh() != nullptr)
                    {
                        _vmodAdmStatusB = entry.GetCsh()->GetVmodAdmStatus();
                    }
                    else
                    {
                        _vmodAdmStatusB = CSH::VMOD_ADM_STATUS_INVALID;
                    }
                }
                else
                {
                    return errmsg("More than two VMOD_FW sections found");
                }
            }

            if (entry.GetPartitionTypeEnum() == PartitionType::PT_CHAIN_CONTAINER &&
                entry.GetChainNumber() == _activeChain) // we assume that chain container follows rom_imgs and therefore
                                                        // we can trust that the active chain number was for sure set
            {
                _l2ptOffset = entry.GetStartOffset();
                if (!InitL2pt())
                {
                    return false;
                }
            }

            if (entry.GetPartitionTypeEnum() == PartitionType::PT_WP_AREA_PTR)
            {
                _WPAreaPtr = entry.GetStartOffset();
            }
            else if (entry.GetPartitionTypeEnum() == PartitionType::PT_RW_AREA_PTR)
            {
                _RWAreaPtr = entry.GetStartOffset();
            }
        }
    }

    if (!GetIsReducedImage())
    {
        if (!InitL3pt())
        {
            return false;
        }

        if (!CheckSecondL1ptExists()) // if CheckSecondL1ptExists succeds then it initializes _secondL1ptExists
        {
            return false;
        }
    }

    MLXFWOPS_LOG_DEBUG("Fs6Operations::Init() - _activeChain: %s, _backupChain: %s, invalid chains count: %zu",
             _activeChain == INVALID_CHAIN_NUMBER ? "none" : std::to_string(_activeChain).c_str(),
             _backupChain == INVALID_CHAIN_NUMBER ? "none" : std::to_string(_backupChain).c_str(),
             invalidChains.size());
    return true;
}

bool Fs6Operations::InitCshComponent(PartitionTableEntry& entry)
{
    PartitionType partitionType = entry.GetPartitionTypeEnum();
    size_t offset = entry.GetStartOffset();
    int currentChain = entry.GetChainNumber();

    if (IsL2ptSection(partitionType))
    {
        offset += _l2ptOffset;
    }

    MLXFWOPS_LOG_DEBUG("InitCshComponent partitionType: 0x%X", static_cast<u_int32_t>(partitionType));

    vector<u_int8_t> cshHeader(fs5_image_layout_csh_header_size());
    if (!_ioAccess->read(offset, cshHeader.data(), fs5_image_layout_csh_header_size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    try
    {
        CSH::CshStructType cshStructType = CSH::GetCshStructType(cshHeader);
        vector<u_int8_t> cshData(CSH::HeaderSize(cshStructType));
        if (!_ioAccess->read(offset, cshData.data(), CSH::HeaderSize(cshStructType)))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
        }

        std::shared_ptr<CSH> csh = std::make_shared<CSH>();
        csh->UnpackHeader(cshData);

        cshData.resize(csh->GetNumberOfBinaries() * BinarySectionMetadata::Size());
        if (!_ioAccess->read(offset + CSH::HeaderSize(cshStructType), cshData.data(), cshData.size()))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
        }
        csh->UnpackSections(cshData);

        _cshComponents.push_back({partitionType, csh, currentChain});

        entry.SetCsh(_cshComponents.back().csh);
    }
    catch (const CshException& e)
    {
        //* VMOD partition place holder case, so we can ignore the exception
        if (!(e.GetType() == CshException::CshExceptionType::CSH_HEADER_NOT_FOUND &&
              partitionType == PartitionType::PT_VMOD_FW))
        {
            return errmsg("%s", e.what());
        }
    }

    return true;
}

bool Fs6Operations::IsValidCshSection(FwOperations* imageOps, PartitionType partitionType)
{
    Fs6Operations* fs6Ops = dynamic_cast<Fs6Operations*>(imageOps);
    if (fs6Ops == nullptr)
    {
        throw std::invalid_argument("imageOps is not a Fs6Operations");
    }
    return fs6Ops->_l1pt.GetEntry(partitionType).GetCsh() != nullptr;
}

bool Fs6Operations::FwInit()
{
    FwInitCom();
    _fwImgInfo.fwType = (fw_img_type_t)FwType();
    return true;
}

void Fs6Operations::PrintNonActiveChainSection(VerifyCallBack verifyCallBackFunc,
                                               const PartitionTableEntry& entry,
                                               const string& partitionType)
{
    bool backupChain = entry.GetChainNumber() == _backupChain;
    string suffix = backupChain ? "backup" : "invalid";
    PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(), entry.GetStartOffset() + entry.GetSectionSize() - 1,
                      entry.GetSectionSize(), partitionType, "L1 Partition (" + suffix + " chain)");
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
    if (showItoc)
    {
        PrintPartitionTable(verifyCallBackFunc, _l1pt, _l1ptOffset, "L1");
    }

    if (!GetIsReducedImage() && !VerifyL1ptConsistency())
    {
        return false;
    }

    if (_secondL1ptExists)
    {
        PrintSectionRange(verifyCallBackFunc, SECOND_L1PT_OFFSET, SECOND_L1PT_OFFSET + _l1pt.Size() - 1, _l1pt.Size(),
                          "L1 Partition Table", "Backup L1PT");
    }

    int devInfoVaildAmount = 0;
    for (auto entry : _l1pt.GetEntries())
    {
        // TODO:: check if the image is reduced, and if so, skip DTOCs
        bool isKnownPartition = true;
        string partitionType = ToString(entry.GetPartitionTypeEnum());
        if (partitionType == "UNKNOWN")
        {
            partitionType = GetSectionNameByType(entry.GetPartitionType());
            if (partitionType == "UNKNOWN")
            {
                partitionType = mft_utils::ToHexString(entry.GetPartitionType(), 2);
                isKnownPartition = false;
            }
        }

        if (isKnownPartition)
        {
            if (IsCshComponent(entry.GetPartitionTypeEnum()))
            {
                if (entry.GetPartitionTypeEnum() == PartitionType::PT_ROM_IMGS && entry.GetChainNumber() != _activeChain)
                {
                    PrintNonActiveChainSection(verifyCallBackFunc, entry, partitionType);
                    continue;
                }
                if (!VerifyCshComponent(entry, showItoc, verifyCallBackFunc))
                {
                    return false;
                }
            }
            else if (entry.GetPartitionTypeEnum() == PartitionType::PT_CHAIN_CONTAINER)
            {
                if (entry.GetChainNumber() != _activeChain)
                {
                    PrintNonActiveChainSection(verifyCallBackFunc, entry, partitionType);
                    continue;
                }
                bool isKnownPartition = true;
                PrintSectionRange(verifyCallBackFunc, _l2ptOffset, _l2ptOffset + _l2pt.Size() - 1, _l2pt.Size(),
                                  "L2 Partition Table");
                if (showItoc)
                {
                    PrintPartitionTable(verifyCallBackFunc, _l2pt, _l2ptOffset, "L2");
                }

                for (auto l2Entry : _l2pt.GetEntries())
                {
                    partitionType = ToString(l2Entry.GetPartitionTypeEnum());
                    if (partitionType == "UNKNOWN")
                    {
                        partitionType = mft_utils::ToHexString(l2Entry.GetPartitionType(), 2);
                        isKnownPartition = false;
                    }

                    if (isKnownPartition)
                    {
                        if (IsCshComponent(l2Entry.GetPartitionTypeEnum()))
                        {
                            if (!VerifyCshComponent(l2Entry, showItoc, verifyCallBackFunc))
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
                }
            }
            else if (entry.GetPartitionTypeEnum() == PartitionType::PT_DEV_INFO)
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
            else if (entry.GetPartitionTypeEnum() == PartitionType::PT_CRC_INFO)
            {
                PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(),
                                  entry.GetStartOffset() + entry.GetSectionSize() - 1, entry.GetSectionSize(),
                                  partitionType, "L1 Partition");
                if (!PrintCrcInfoLayout(verifyCallBackFunc, entry, showItoc))
                {
                    return false;
                }
            }
            else if (entry.GetPartitionTypeEnum() != PartitionType::PT_WP_AREA_PTR &&
                     entry.GetPartitionTypeEnum() != PartitionType::PT_RW_AREA_PTR)
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

    if (!GetIsReducedImage())
    {
        if (devInfoVaildAmount == 0)
        {
            return errmsg("No DEV_INFO section found with valid signature");
        }

        if (_activeChain == INVALID_CHAIN_NUMBER)
        {
            return errmsg("No active chain found"); // no valid use case in which the flash/image will only have a
                                                    // backup/invalid chain without an active one
        }

        if (_RWAreaPtr != 0 && _WPAreaPtr != 0)
        {
            if (_l3pwOffset == 0 || _l3prOffset == 0)
            {
                return errmsg("Area pointers exist in L1PT but L3PW/L3PR table is missing");
            }
        }
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

bool Fs6Operations::VerifyCshComponent(const PartitionTableEntry& entry,
                                       bool showItoc,
                                       VerifyCallBack verifyCallBackFunc)
{
    std::shared_ptr<CSH> cshComponent = entry.GetCsh();
    PartitionType partitionType = entry.GetPartitionTypeEnum();
    size_t offset = entry.GetStartOffset();

    if (IsL2ptSection(partitionType))
    {
        offset += _l2ptOffset;
    }

    MLXFWOPS_LOG_DEBUG("VerifyCshComponent partitionType: %s, csh exists: %d", ToString(partitionType).c_str(),
             cshComponent != nullptr);

    if (cshComponent != nullptr)
    {
        string compName = ToString(CshComponentID(cshComponent->GetComponentId()));
        PrintSectionRange(verifyCallBackFunc, offset, offset + cshComponent->GetCshSize() - 1,
                          cshComponent->GetCshSize(), compName, "CSH");

        u_int32_t prevSectionEnd = cshComponent->GetCshSize();
        u_int32_t currSectionBegin = 0;
        string sectionName;

        // if (showItoc && IsL2ptSection(partitionType))
        // {
        //     report_callback(verifyCallBackFunc, "CSH bin digests and load destinations (%s):\n", compName.c_str());
        //     PrintSectionMetadata(verifyCallBackFunc, *cshComponent);
        // }

        for (auto section : cshComponent->GetSections())
        {
            sectionName = GetSectionNameByMagicId(section.GetSectionType());
            size_t sectionOffset = offset + section.GetSectionOffset();
            PrintSectionRange(verifyCallBackFunc, sectionOffset, sectionOffset + section.GetSectionSize() - 1,
                              section.GetSectionSize(), sectionName, "CSH Section");

            if (showItoc)
            {
                PrintSectionMetadata(section, verifyCallBackFunc);
                if ((CshSectionType)section.GetSectionType() == CshSectionType::CSH_SECTION_L3PW_MAGIC_ID)
                {
                    PrintPartitionTable(verifyCallBackFunc, _l3pw, _l3pwOffset, "L3PW");
                }
                else if ((CshSectionType)section.GetSectionType() == CshSectionType::CSH_SECTION_L3PR_MAGIC_ID)
                {
                    PrintPartitionTable(verifyCallBackFunc, _l3pr, _l3prOffset, "L3PR");
                }
            }

            currSectionBegin = section.GetSectionOffset();
            if (currSectionBegin < prevSectionEnd)
            {
                return errmsg("section %s intersects with the previous section", sectionName.c_str());
            }
            prevSectionEnd = section.GetSectionOffset() + section.GetSectionSize();
        }

        if (prevSectionEnd > cshComponent->GetComponentSize())
        {
            return errmsg("section %s is out of CSH bounds", sectionName.c_str());
        }
    }
    else if (partitionType == PartitionType::PT_VMOD_FW)
    {
        PrintSectionRange(verifyCallBackFunc, entry.GetStartOffset(),
                          entry.GetStartOffset() + entry.GetSectionSize() - 1, entry.GetSectionSize(), "VMOD_FW",
                          "CSH Placeholder");
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
    if (image == NULL)
    {
        *image_size = _ioAccess->get_size();
    }
    else
    {
        if (!_ioAccess->read(0, (u_int32_t*)image, _ioAccess->get_size()))
        {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }
    return true;
}

bool Fs6Operations::ReadComponent(string compNameStr,
                                  ComponentHeader compHeader,
                                  string,
                                  vector<u_int8_t>& componentData)
{
    ComponentType compName = FwOperations::StringToComponentType(compNameStr);
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

bool Fs6Operations::ReadComponentSection(string compName,
                                         string sectionName,
                                         ComponentHeader compHeader,
                                         vector<u_int8_t>& sectionData)
{
    ComponentType compType = FwOperations::StringToComponentType(compName);
    u_int32_t magicId = 0; // CSH section is indetified by a 4 characters long magic ID
    CshComponentID cshId = ToCshId(compType);
    vector<u_int8_t> componentData;

    u_int32_t convertedMagicId = BinarySectionMetadata::CshSectionStringToID(sectionName);

    if (convertedMagicId == 0 && sectionName.size() != 4)
    {
        return errmsg("Section name must be a 4 characters long magic ID or appropriate section string.");
    }
    if (convertedMagicId != 0)
    {
        magicId = convertedMagicId;
    }
    else
    {
        memcpy(&magicId, sectionName.c_str(), 4);
        CPUTOn(&magicId, 1);
    }

    // must be with header to read the full CSH component
    compHeader = ComponentHeader::Header_With;
    if (!ReadComponent(compName, compHeader, "", componentData))
    {
        return false;
    }

    vector<CshComponentInfo>::const_iterator entry =
      std::find_if(_cshComponents.begin(), _cshComponents.end(),
                   [cshId](const CshComponentInfo& entry) { return entry.csh->GetComponentIdEnum() == cshId; });
    if (entry == _cshComponents.end())
    {
        return errmsg("CSH component not found");
    }

    try
    {
        BinarySectionMetadata section = entry->csh->GetSection(magicId);
        sectionData.resize(section.GetSectionSize());
        std::copy(componentData.begin() + section.GetSectionOffset(),
                  componentData.begin() + section.GetSectionOffset() + section.GetSectionSize(), sectionData.begin());
    }
    catch (const std::exception& e)
    {
        return errmsg("Section not found: %s", e.what());
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
        if (!IsPartitionTypeMaxSize(ToPartitionType(cshId, false)))
        {
            _l1pt.SetEntrySize(ToPartitionType(cshId), compData.size());
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

FwVersion::fw_version_raw Fs6Operations::GetCshComponentVersion(PartitionType partitionType)
{
    auto entry =
      std::find_if(_cshComponents.begin(), _cshComponents.end(),
                   [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });
    if (entry == _cshComponents.end())
    {
        throw std::runtime_error("Partition type " + ToString(partitionType) + " not found in the image");
    }
    return {entry->csh->GetComponentMajorVersion(), entry->csh->GetComponentMinorVersion(),
            entry->csh->GetComponentSubminorVersion()};
}

bool Fs6Operations::HasCshComponent(PartitionType partitionType) const
{
    return std::any_of(_cshComponents.begin(), _cshComponents.end(),
                       [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });
}

bool Fs6Operations::GetFwComponentsData(string path)
{
    Json::Value root;
    if (!Init())
    {
        return false;
    }

    vector<PartitionType> partitionTypes = {PartitionType::PT_ROM_IMGS, PartitionType::PT_NV_FWS,
                                            PartitionType::PT_CALIPTRA_FW};
    if (HasCshComponent(PartitionType::PT_SBD_FW))
    {
        partitionTypes.push_back(PartitionType::PT_SBD_FW);
    }

    for (auto partitionType : partitionTypes)
    {
        auto version = GetCshComponentVersion(partitionType);

        std::stringstream stream;
        stream << "0x" << std::hex << static_cast<int>(version.major);
        root[ToString(ToCshId(partitionType))]["ver_major"] = stream.str();
        stream.str("");
        stream << "0x" << std::hex << static_cast<int>(version.minor);
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

PartitionTableEntry Fs6Operations::GetPartitionTableEntry(PartitionType partitionType, int chainNumber)
{
    ResolveChainNumber(chainNumber, _activeChain);

    PartitionValidator validator(partitionType);
    bool isL2pt = IsL2ptSection(partitionType);
    const PartitionTable* pt = isL2pt ? &_l2pt : &_l1pt;
    const PartitionTableEntry* entry = nullptr;

    for (auto& partitionTableEntry : pt->GetEntries())
    {
        if (partitionTableEntry.GetPartitionTypeEnum() == partitionType &&
            validator.validate(partitionTableEntry, _ioAccess, chainNumber))
        {
            entry = &partitionTableEntry;
            break;
        }
    }

    if (entry == nullptr)
    {
        throw std::runtime_error(
          string_format("Partition type 0x%x not found or validation failed", (int)partitionType));
    }

    return *entry;
}

void Fs6Operations::GetPartitionEntryInfo(PartitionType partitionType,
                                          size_t& sectionOffset,
                                          size_t& sectionSize,
                                          int chainNumber)
{
    PartitionTableEntry entry = GetPartitionTableEntry(partitionType, chainNumber);
    size_t baseOffset = IsL2ptSection(partitionType) ? _l2ptOffset : 0;
    sectionOffset = baseOffset + entry.GetStartOffset();
    sectionSize = entry.GetSectionSize();
}

void Fs6Operations::UpdatePartitionData(PartitionType partitionType,
                                        const vector<u_int8_t>& data,
                                        PrintCallBack callBackFunc,
                                        int chainNumber)
{
    size_t section_offset = 0;
    size_t section_size = 0;
    GetPartitionEntryInfo(partitionType, section_offset, section_size, chainNumber);

    PRINT_PROGRESS(callBackFunc, string_format("Updating %-4s section - ", ToString(partitionType).c_str()).c_str());
    // readModifyWrite=true preserves neighbouring sections sharing this section's erase sector
    // a plain write() would erase the whole sector and only reprograms this section's bytes, wiping its neighbours.
    if (!writeImage((ProgressCallBack)NULL, section_offset, const_cast<u_int8_t*>(data.data()), (int)data.size(),
                    /*isPhysAddr=*/false, /*readModifyWrite=*/true))
    {
        PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
        throw std::runtime_error(string_format("Partition type 0x%x - write error (%s)", (int)partitionType, err()));
    }
    PRINT_PROGRESS(callBackFunc, (char*)"OK\n");
}

vector<u_int8_t> Fs6Operations::ReadPartitionData(PartitionType partitionType, int chainNumber)
{
    size_t section_offset = 0;
    size_t section_size = 0;
    GetPartitionEntryInfo(partitionType, section_offset, section_size, chainNumber);

    string partitionName = ToString(partitionType);
    MLXFWOPS_LOG_DEBUG("Fs6Operations::ReadPartitionData %s_section_offset=0x%zx, %s_section_size=0x%zx", partitionName.c_str(),
             section_offset, partitionName.c_str(), section_size);

    vector<u_int8_t> data(section_size);
    if (!_ioAccess->read(section_offset, data.data(), section_size))
    {
        throw std::runtime_error(std::string(partitionName) + " - read error (" + (*_ioAccess).err() + ")");
    }
    return data;
}

bool Fs6Operations::GetDevInfo(u_int8_t* buff)
{
    vector<u_int8_t> devInfoData = ReadPartitionData(PartitionType::PT_DEV_INFO);
    return FwOperations::GetDevInfo(devInfoData.data());
}

bool Fs6Operations::GetMfgInfo(u_int8_t* buff)
{
    vector<u_int8_t> mfg_info_data = ReadPartitionData(PartitionType::PT_MFG_INFO);
    if (!FwOperations::GetMfgInfo(mfg_info_data.data()))
    {
        throw std::runtime_error("Failed to get MFG info");
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

bool Fs6Operations::GetNvPubKeyIdx()
{
    auto entry =
      std::find_if(_cshComponents.begin(), _cshComponents.end(),
                   [](const CshComponentInfo& entry) { return entry.partitionType == PartitionType::PT_SWITCH_FWS; });
    if (entry == _cshComponents.end())
    {
        return errmsg("CSH component for PT_SWITCH_FWS not found");
    }
    _fsCommonInfo.ext_info.nv_pub_key_idx = entry->csh->GetNvPubKeyIdx();
    return true;
}

bool Fs6Operations::ReadCshSectionInfo(PartitionType partitionType,
                                       CshSectionType sectionType,
                                       size_t sectionSize,
                                       vector<u_int8_t>& data,
                                       int chainNumber)
{
    size_t section_addr;
    if (!GetCshSectionOffset(partitionType, sectionType, section_addr, true, chainNumber))
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

bool Fs6Operations::GetImageInfoData(vector<u_int8_t>& data)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetImageInfoData");
    if (!ReadCshSectionInfo(PartitionType::PT_SWITCH_FWS,
                            CshSectionType::CSH_SECTION_IMAGE_INFO_MAGIC_ID,
                            FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE,
                            data))
    {
        // TODO: fallback for backward compatibility
        if (!ReadCshSectionInfo(PartitionType::PT_SWITCH_FWS,
                                CshSectionType::CSH_SECTION_IMAGE_INFO,
                                FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE,
                                data))
        {
            return false;
        }
    }

    return true;
}

size_t Fs6Operations::GetPartitionOffset(PartitionType partitionType, int chainNumber)
{
    size_t partitionOffset = 0;
    size_t partitionSize = 0;
    GetPartitionEntryInfo(partitionType, partitionOffset, partitionSize, chainNumber);
    return partitionOffset;
}

bool Fs6Operations::GetCshSectionOffset(PartitionType partitionType,
                                        CshSectionType sectionType,
                                        size_t& CshSectionOffset,
                                        bool reportError,
                                        int chainNumber)
{
    // Find the partition table entry
    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset partitionType = 0x%x, sectionType = 0x%x, setErrMsg = %d",
             (int)partitionType, (int)sectionType, reportError);

    size_t partitionOffset = GetPartitionOffset(partitionType, chainNumber);

    MLXFWOPS_LOG_DEBUG("Fs6Operations::GetCshSectionOffset partitionOffset = 0x%zx", partitionOffset);

    // Find the CSH component
    auto cshComponent =
      find_if(_cshComponents.begin(), _cshComponents.end(),
              [partitionType](const CshComponentInfo& entry) { return entry.partitionType == partitionType; });

    if (cshComponent == _cshComponents.end())
    {
        if (reportError)
        {
            return errmsg("CSH component for partition type 0x%x not found", (int)partitionType);
        }
        return false;
    }

    // Find the specific section within the CSH component
    auto section = find_if(cshComponent->csh->GetSections().begin(),
                           cshComponent->csh->GetSections().end(),
                           [sectionType](const BinarySectionMetadata& section)
                           { return (CshSectionType)section.GetSectionType() == sectionType; });

    if (section == cshComponent->csh->GetSections().end())
    {
        if (reportError)
        {
            return errmsg("Section type 0x%x not found in CSH component", (int)sectionType);
        }
        return false;
    }

    // Calculate the final section offset
    CshSectionOffset = partitionOffset + section->GetSectionOffset();
    return true;
}

bool Fs6Operations::LoadImageInfo()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::LoadImageInfo");
    vector<u_int8_t> data;
    if (!GetImageInfoData(data))
    {
        return false;
    }

    struct fs6_image_layout_image_info image_info;
    fs6_image_layout_image_info_unpack(&image_info, data.data());
    if (!ParseFs6ImageInfo(image_info, _fwImgInfo, _fsCommonInfo))
    {
        return errmsg("Failed to parse IMAGE_INFO section - %s", err());
    }

    const u_int32_t* swId = (u_int32_t*)NULL;
    MLXFWOPS_LOG_DEBUG("Fs6Operations::LoadImageInfo fwImgInfo.supportedHwId[0]=0x%x", _fwImgInfo.supportedHwId[0]);
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
    return true;
}

bool Fs6Operations::UpdateLCAndGISIfAccessible()
{
    try
    {
        if (_ioAccess->is_flash() && IsLifeCycleAccessible(_fwImgInfo.ext_info.chip_type))
        {
            CRSpaceRegisters crSpaceReg(getMfileObj(), _fwImgInfo.ext_info.chip_type);
            _fsCommonInfo.ext_info.life_cycle = crSpaceReg.getLifeCycle();
            _fsCommonInfo.ext_info.global_image_status = crSpaceReg.getGlobalImageStatus();
        }
    }
    catch (const std::exception& e)
    {
        return errmsg("Failed to read life cycle and global image status from CR-space: %s", e.what());
    }

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

    try
    {
        if (!FwVerify((VerifyCallBack) nullptr))
        {
            return false;
        }

        if (!LoadImageInfo())
        {
            return false;
        }

        if (!GetIsReducedImage() && !isStripedImage && !ignoreDToc)
        {
            if ((!GetMfgInfo() || !GetDevInfo() || !GetNvPubKeyIdx() || !UpdateLCAndGISIfAccessible()))
            {
                return false;
            }
        }

        fwInfo->fw_type = FwType();
        _fwImgInfo.ext_info.is_failsafe = true;

        memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
        memcpy(&(fwInfo->fs3_info), &(_fsCommonInfo.ext_info), sizeof(fs3_info_t));

        if (HasCshComponent(PartitionType::PT_SBD_FW))
        {
            auto sbdVersion = GetCshComponentVersion(PartitionType::PT_SBD_FW);
            _compsList.push_back(CompInfo{ComponentType::Comp_Csh_Sbd_Fw,
                                          FwVersion(sbdVersion.major, sbdVersion.minor, sbdVersion.subminor)});
        }
    }
    catch (const std::exception& e)
    {
        return errmsg("Fs6Operations::FwQuery failed: %s", e.what());
    }

    return true;
}

bool Fs6Operations::IsComponentFormatWithKeyId()
{
    return true;
}

#ifndef MST_CPU_armv7l_umbriel // {
bool Fs6Operations::SignForSecureBoot(const char*, const char*, const MlxSign::Signer&)
{
    return Unsupported(__FUNCTION__);
}
#endif // } MST_CPU_armv7l_umbriel

bool Fs6Operations::CheckSecondL1ptExists()
{
    // Check if second L1PT exists by looking for magic pattern
    vector<u_int8_t> secondL1ptMagic(PartitionTable::MagicID().size());
    if (!_ioAccess->read(SECOND_L1PT_OFFSET, secondL1ptMagic.data(), secondL1ptMagic.size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "Failed to read second L1PT magic: %s", _ioAccess->err());
    }

    _secondL1ptExists =
      std::equal(PartitionTable::MagicID().begin(), PartitionTable::MagicID().end(), secondL1ptMagic.begin());

    return true;
}

bool Fs6Operations::VerifyL1ptConsistency()
{
    if (_secondL1ptExists)
    {
        MLXFWOPS_LOG_DEBUG("Second L1PT exists at offset 0x%x", SECOND_L1PT_OFFSET);
        // Get first L1PT data from the already-parsed _l1pt object
        vector<u_int8_t> firstL1ptData = _l1pt.Pack();

        // Read second L1PT from device/image
        vector<u_int8_t> secondL1ptData(firstL1ptData.size());
        if (!_ioAccess->read(SECOND_L1PT_OFFSET, secondL1ptData.data(), secondL1ptData.size()))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "Failed to read second L1PT: %s", _ioAccess->err());
        }

        if (firstL1ptData != secondL1ptData)
        {
            return errmsg("L1PT mismatch: first L1PT (at 0x%x) differs from second L1PT (at 0x%x)", _l1ptOffset,
                          SECOND_L1PT_OFFSET);
        }
    }
    else
    {
        MLXFWOPS_LOG_DEBUG("Second L1PT does not exist"); // TODO - in the future fail the check
    }

    MLXFWOPS_LOG_DEBUG("L1PT consistency check passed");
    return true;
}

void Fs6Operations::UpdatePartitionTable(bool isL2pt, PrintCallBack callBackFunc)
{
    vector<u_int8_t> partitionTable;
    u_int32_t partitionTableOffset = _l1ptOffset; // l1pt

    if (isL2pt)
    {
        _l2pt.CalcDigest();
        partitionTable = _l2pt.Pack();
        partitionTableOffset = _l2ptOffset;
    }
    else
    {
        _l1pt.CalcDigest();
        partitionTable = _l1pt.Pack();
    }

    auto writePartitionTable = [this, &partitionTable, callBackFunc](u_int32_t offset, const char* label)
    {
        PRINT_PROGRESS(callBackFunc, string_format("Updating partition table %s - ", label).c_str());
        if (!_ioAccess->write(offset, partitionTable.data(), partitionTable.size()))
        {
            PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
            throw runtime_error(string_format("write error - %s", _ioAccess->err()));
        }
        PRINT_PROGRESS(callBackFunc, (char*)"OK\n");
    };

    writePartitionTable(partitionTableOffset, isL2pt ? "L2PT" : "L1PT");

    if (!isL2pt && _secondL1ptExists)
    {
        writePartitionTable(SECOND_L1PT_OFFSET, "L1PT (Copy 1)");
    }
}

bool Fs6Operations::IsDtocEntry(PartitionType partitionType)
{
    bool isl1ptSection = !IsL2ptSection(partitionType);
    return isl1ptSection && partitionType != PartitionType::PT_CHAIN_CONTAINER &&
           partitionType != PartitionType::PT_ROM_IMGS && partitionType != PartitionType::PT_WP_AREA_PTR &&
           partitionType != PartitionType::PT_RW_AREA_PTR;
}

bool Fs6Operations::CollectDtocForProductionBurn(const PartitionTableEntry& entry)
{
    PartitionType partitionType = entry.GetPartitionTypeEnum();

    if (!IsDtocEntry(partitionType))
    {
        return false;
    }

    if (partitionType == PartitionType::PT_VMOD_FW)
    {
        MLXFWOPS_LOG_DEBUG("%sCollecting DTOC for VMOD_FW", entry.GetCsh() == nullptr ? "Not " : "");
        return entry.GetCsh() != nullptr;
    }

    return true;
}

bool Fs6Operations::IsL2ptSection(CshComponentID cshId)
{
    if (cshId == CshComponentID::NV_FWS || cshId == CshComponentID::OEM_FWS || cshId == CshComponentID::BCT_DTB ||
        cshId == CshComponentID::SWITCH_FWS || cshId == CshComponentID::SBD_FW || cshId == CshComponentID::CALIPTRA_FW)
    {
        return true;
    }
    return false;
}

bool Fs6Operations::IsL2ptSection(PartitionType partitionType)
{
    if (partitionType == PartitionType::PT_NV_FWS || partitionType == PartitionType::PT_CALIPTRA_FW ||
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

bool Fs6Operations::Is32MBLayout()
{
    return GetChainContainerMaxSize() == 0xA00000;
}

size_t Fs6Operations::GetChainContainerMaxSize()
{
    auto chainContainerEntry =
      _l1pt.GetEntry(PartitionType::PT_CHAIN_CONTAINER,
                     _activeChain); // chain container max size is same for both active and backup chains
    return chainContainerEntry.GetSectionSize();
}

size_t Fs6Operations::GetChainContainerActualSize()
{
    size_t l2ptSectionsSize = GetL2ptSectionsSize();
    size_t l2ptSize = PartitionTable::HeaderSize() + _l2pt.GetEntries().size() * PartitionTableEntry::Size();
    MLXFWOPS_LOG_DEBUG("chain container actual size: 0x%zx", l2ptSectionsSize + l2ptSize);
    return l2ptSectionsSize + l2ptSize;
}

bool Fs6Operations::PreBurnChecks(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    // Verify that imageOps is actually an FS6 image
    if (imageOps->FwType() != FIT_FS6 && imageOps->FwType() != FIT_CSH_VMOD)
    {
        return errmsg("Expected FS6 or FSVMOD image but got type %d", imageOps->FwType());
    }

    try
    {
        if (Is32MBLayout())
        {
            MLXFWOPS_LOG_DEBUG("32MB layout detected");
        }
    }
    catch (const std::exception& e)
    {
        if (!burnParams.useImgDevData)
        {
            return errmsg("%s", e.what());
        }
    }

    if (!burnParams.useImgDevData && imageOps->FwType() == FIT_FS6)
    {
        if (((Fs6Operations*)imageOps)->GetChainContainerActualSize() > GetChainContainerMaxSize())
        {
            return errmsg("Chain container size in provided image is too large for device's flash layout.");
        }
    }
    return true;
}

bool Fs6Operations::DoBeforeBurnJobs()
{
    if (!checkAndDisableFlashWpIfRequired())
    {
        return errmsg("Failed to check and disable flash write protection if from bottom.\n");
    }

    return true;
}

bool Fs6Operations::DoAfterBurnJobs()
{
    if (!restoreWriteProtectInfo())
    {
        return errmsg("Post-burn operation failed: Failed to restore flash write protection if from bottom.\n");
    }

    return true;
}

int Fs6Operations::GetDestChainNumber(bool failSafe)
{
    int destChainNumber = 0; // in prev generations: nofs -> burn to start of image in offset 0
    if (failSafe)            // (bank 0). The equivalent in fs6 is to burn to chain 0 (bank 0)
    {
        if (_activeChain != INVALID_CHAIN_NUMBER)
        {
            destChainNumber = _activeChain == 0 ? 1 : 0;
        }
        else
        {
            if (_backupChain != INVALID_CHAIN_NUMBER)
            {
                destChainNumber = _backupChain == 0 ? 1 : 0;
            }
        }
    }
    return destChainNumber;
}

string Fs6Operations::GetL1ptEntryName(PartitionType partType, bool isCshComponent)
{
    string ptEntryName = ToString(partType);
    if (ptEntryName == "UNKNOWN" && !isCshComponent)
    {
        ptEntryName = GetSectionNameByType(static_cast<u_int8_t>(partType));
    }
    if (ptEntryName == "UNKNOWN")
    {
        ptEntryName = mft_utils::ToHexString(static_cast<u_int32_t>(partType), 2);
    }
    return ptEntryName;
}

void Fs6Operations::addBurnRegion(u_int32_t srcOffset,
                                  u_int32_t destOffset,
                                  u_int32_t size,
                                  const std::string& name,
                                  PartitionType pt,
                                  map<PartitionType, vector<BurnRegion>>& partitionMap,
                                  vector<BurnRegion>& allRegions)
{
    partitionMap[pt].push_back({srcOffset, destOffset, size, name, pt});
    allRegions.push_back(BurnRegion{srcOffset, destOffset, size, name, pt});
}

bool Fs6Operations::ProcessL1pt(const vector<PartitionTableEntry>& l1Entries,
                                Fs6Operations* fs6ImageOps, // source image ops
                                L1ptInstance instance,
                                map<PartitionType, vector<BurnRegion>>& partitionTypeToBurnRegions,
                                vector<BurnRegion>& allBurnRegions,
                                bool collectDtocs)
{
    size_t l1ptSrcOffset = fs6ImageOps->_l1ptOffset;
    size_t l1ptDestOffset = (instance == L1ptInstance::First) ? l1ptSrcOffset : SECOND_L1PT_OFFSET;
    if (instance == L1ptInstance::Second)
    {
        if (!CheckSecondL1ptExists())
        {
            return false;
        }
        if (_secondL1ptExists)
        {
            l1ptSrcOffset = SECOND_L1PT_OFFSET; // if second l1pt exists in image, we'll copy it. else - we'll duplicate
                                                // the existing l1pt to the second dot_l1pt
        }
    }

    string prefix = (instance == L1ptInstance::First) ? "L1PT" : "SECOND_L1PT";

    // Add header burn region
    addBurnRegion(l1ptSrcOffset, l1ptDestOffset, PartitionTable::HeaderSize(), prefix + "_HEADER",
                  PartitionType::PT_UNKNOWN, partitionTypeToBurnRegions, allBurnRegions);
    l1ptSrcOffset += PartitionTable::HeaderSize();
    l1ptDestOffset += PartitionTable::HeaderSize();

    // Add entry burn regions
    for (size_t i = 0; i < l1Entries.size(); i++)
    {
        PartitionType partType = (PartitionType)l1Entries[i].GetPartitionTypeEnum();
        bool isCshComponent = IsCshComponent(partType);
        size_t ptEntrySrcOffset = l1ptSrcOffset + i * PartitionTableEntry::Size();
        size_t ptEntryDestOffset = l1ptDestOffset + i * PartitionTableEntry::Size();
        size_t ptEntrySize = PartitionTableEntry::Size();
        string ptEntryName = prefix + "_ENTRY_" + GetL1ptEntryName(partType, isCshComponent);

        addBurnRegion(ptEntrySrcOffset, ptEntryDestOffset, ptEntrySize, ptEntryName, partType,
                      partitionTypeToBurnRegions, allBurnRegions);

        // collect dtocs only for first l1pt (no need to collect twice, they both point to the same dtocs)
        if (collectDtocs && instance == L1ptInstance::First && CollectDtocForProductionBurn(l1Entries[i]))
        {
            size_t dtocOffset = l1Entries[i].GetStartOffset();
            size_t dtocSize = l1Entries[i].GetSectionSize();
            string dtocName = "DTOC_" + ptEntryName;
            addBurnRegion(dtocOffset, dtocOffset, dtocSize, dtocName, partType, partitionTypeToBurnRegions,
                          allBurnRegions);
        }
    }

    return true;
}

std::map<PartitionType, std::vector<Fs6Operations::BurnRegion>>
  Fs6Operations::GetBurnRegions(FwOperations* imageOps, bool useImgDevData, bool failSafe)
{
    map<PartitionType, vector<BurnRegion>> partitionTypeToBurnRegions;
    std::vector<BurnRegion> allBurnRegions;
    Fs6Operations* fs6ImageOps = dynamic_cast<Fs6Operations*>(imageOps);
    if (!fs6ImageOps)
    {
        throw std::runtime_error("Failed to cast imageOps to Fs6Operations");
    }

    int destChainNumber = GetDestChainNumber(failSafe);
    MLXFWOPS_LOG_DEBUG("Burning to chain: %d", destChainNumber);

    if (useImgDevData)
    {
        ProcessL1pt(fs6ImageOps->_l1pt.GetEntries(), fs6ImageOps, L1ptInstance::First, partitionTypeToBurnRegions,
                    allBurnRegions,
                    useImgDevData); // for first dotl1pt, we'll collect dtoc as well if it's production burn
        ProcessL1pt(fs6ImageOps->_l1pt.GetEntries(), fs6ImageOps, L1ptInstance::Second, partitionTypeToBurnRegions,
                    allBurnRegions); // for second dotl1pt. we'll not collect dtocs (if
                                     // needed, it was collected in the first dotl1pt)
    }

    // collect l2pt entries
    size_t l2ptSrcOffset = fs6ImageOps->_l2ptOffset;
    size_t l2ptDestOffset = l2ptSrcOffset;
    if (!useImgDevData)
    {
        auto chainContainerEntry = _l1pt.GetEntry(PartitionType::PT_CHAIN_CONTAINER, destChainNumber);
        l2ptDestOffset = chainContainerEntry.GetStartOffset();
    }
    addBurnRegion(l2ptSrcOffset, l2ptDestOffset, PartitionTable::HeaderSize(), "L2PT_HEADER", PartitionType::PT_UNKNOWN,
                  partitionTypeToBurnRegions, allBurnRegions);
    l2ptSrcOffset += PartitionTable::HeaderSize();
    l2ptDestOffset += PartitionTable::HeaderSize();
    const auto& l2Entries = fs6ImageOps->_l2pt.GetEntries();
    for (size_t i = 0; i < l2Entries.size(); i++)
    {
        PartitionType partType = l2Entries[i].GetPartitionTypeEnum();
        size_t sectionSrcOffset = l2ptSrcOffset + i * PartitionTableEntry::Size();
        size_t sectionDestOffset = l2ptDestOffset + i * PartitionTableEntry::Size();
        size_t sectionSize = PartitionTableEntry::Size();
        string sectionName = ToString(partType);
        if (sectionName == "UNKNOWN")
        {
            sectionName = mft_utils::ToHexString(static_cast<u_int32_t>(partType), 2);
        }
        sectionName = "L2PT_ENTRY_" + sectionName;
        addBurnRegion(sectionSrcOffset, sectionDestOffset, sectionSize, sectionName, partType,
                      partitionTypeToBurnRegions, allBurnRegions);
    }

    // collect CSHs (ROM_IMGS, VMOD and ITOCS from SWITCH_FW)
    l2ptSrcOffset -= PartitionTable::HeaderSize();
    l2ptDestOffset -= PartitionTable::HeaderSize();
    for (auto& cshComponent : fs6ImageOps->_cshComponents)
    {
        PartitionType partType = cshComponent.partitionType;
        if (!useImgDevData && partType == PartitionType::PT_VMOD_FW) // we only collect vmod for production burn
        {
            continue;
        }
        std::shared_ptr<const CSH> csh = cshComponent.csh;
        int chainNumber = cshComponent.chainNumber;

        if (!useImgDevData && partType == PartitionType::PT_ROM_IMGS)
        {
            if (chainNumber != fs6ImageOps->_activeChain) // skip burn of inactive chain in image when the burn isn't of
                                                          // all the image
            {
                continue;
            }
        }

        // Get the CSH offset from partition entry
        size_t cshSrcOffset = 0;
        size_t partitionSize = 0;
        fs6ImageOps->GetPartitionEntryInfo(partType, cshSrcOffset, partitionSize, chainNumber);

        size_t cshDestOffset = cshSrcOffset;
        if (!useImgDevData)
        {
            if (partType == PartitionType::PT_ROM_IMGS)
            {
                auto entry = _l1pt.GetEntry(PartitionType::PT_ROM_IMGS, destChainNumber);
                cshDestOffset = entry.GetStartOffset();
            }
            else
            {
                size_t cshRelativeOffset = cshSrcOffset - l2ptSrcOffset;
                cshDestOffset = l2ptDestOffset + cshRelativeOffset;
            }
        }

        size_t fullCshSize = csh->GetComponentSize();
        string cshName = "CSH_" + ToString(CshComponentID(csh->GetComponentId()));
        addBurnRegion(cshSrcOffset, cshDestOffset, fullCshSize, cshName, partType, partitionTypeToBurnRegions,
                      allBurnRegions);
    }

    return partitionTypeToBurnRegions;
}

uint32_t Fs6Operations::GetTotalBurnSize(map<PartitionType, vector<BurnRegion>>& partitionTypeToBurnRegions)
{
    uint32_t totalSize = 0;
    for (const auto& entry : partitionTypeToBurnRegions)
    {
        for (const auto& region : entry.second)
        {
            totalSize += region.size;
        }
    }
    return totalSize;
}

bool Fs6Operations::HandleRomImgsMagicPatternsPostBurn(ExtBurnParams& burnParams,
                                                       uint32_t& alreadyWrittenSize,
                                                       uint32_t totalSize)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::HandleRomImgsMagicPatternsPostBurn");
    int nextActiveChain = GetDestChainNumber(burnParams.burnFailsafe);

    if (_activeChain != INVALID_CHAIN_NUMBER && nextActiveChain != _activeChain &&
        !burnParams.useImgDevData) // we had a previous active chain, it's not as the new active chain number and we're
                                   // not writing whole image -> need to change previous active chain to backup
    {
        int prevChain = nextActiveChain == 0 ? 1 : 0;
        size_t romImgsPrevActiveChainOffset, partitionSize = 0;
        GetPartitionEntryInfo(PartitionType::PT_ROM_IMGS, romImgsPrevActiveChainOffset, partitionSize, prevChain);
        size_t romImgsPrevActiveChainMagicPatternOffset = romImgsPrevActiveChainOffset + ROM_IMGS_MAGIC_PATTERN_OFFSET;
        auto& magicPattern = PartitionTable::RomImgsBackupMagicPattern();
        MLXFWOPS_LOG_DEBUG("Writing ROM_IMGS backup magic pattern %s to address 0x%zx (chain %d is now for backup)",
                 magicPattern.data(), romImgsPrevActiveChainMagicPatternOffset, prevChain);
        if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc,
                          romImgsPrevActiveChainMagicPatternOffset, (void*)magicPattern.data(), magicPattern.size(),
                          true, true, totalSize, alreadyWrittenSize))
        {
            return false;
        }
        alreadyWrittenSize += magicPattern.size();
    }

    if (burnParams.burnFailsafe) // need to activate new chain
    {
        size_t romImgsDestOffset, partitionSize = 0;
        GetPartitionEntryInfo(PartitionType::PT_ROM_IMGS, romImgsDestOffset, partitionSize, nextActiveChain);
        size_t romImgsMagicPatternOffset = romImgsDestOffset + ROM_IMGS_MAGIC_PATTERN_OFFSET;
        auto& magicPattern = PartitionTable::RomImageMagicPattern();
        MLXFWOPS_LOG_DEBUG("Writing ROM_IMGS candidate magic pattern %s to address 0x%zx (validating chain %d)",
                 magicPattern.data(), romImgsMagicPatternOffset, nextActiveChain);
        if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc,
                          romImgsMagicPatternOffset, (void*)magicPattern.data(), magicPattern.size(), true, true,
                          totalSize, alreadyWrittenSize))
        {
            return false;
        }
        alreadyWrittenSize += magicPattern.size();
    }

    return true;
}

bool Fs6Operations::ExecuteVmodBurn(FwOperations* imageOps, ExtBurnParams& burnParams)
{
#ifdef MST_CPU_armv7l_umbriel
    (void)imageOps;
    (void)burnParams;
    return Unsupported(__FUNCTION__);
#else

    FsCshOperations* cshOps = dynamic_cast<FsCshOperations*>(imageOps);
    if (!cshOps)
    {
        throw std::runtime_error("Failed to cast imageOps to FsCshOperations");
    }

    if (burnParams.burnFailsafe &&
        (_vmodAdmStatusA != CSH::VMOD_ADM_STATUS_INVALID || _vmodAdmStatusB != CSH::VMOD_ADM_STATUS_INVALID))
    {
        return errmsg("Found VMOD bank in a state other than INVALID.");
    }

    size_t vmodAOffset = 0, vmodASize = 0;
    GetPartitionEntryInfo(PartitionType::PT_VMOD_FW, vmodAOffset, vmodASize, 0);

    u_int32_t imageSize = 0;
    if (!cshOps->GetImageSize(&imageSize))
    {
        return false;
    }
    vector<u_int8_t> vmodData(imageSize);
    if (!cshOps->FwReadData(vmodData.data(), &imageSize, false))
    {
        return false;
    }

    u_int32_t writtenSize = 0;
    u_int32_t totalSize = imageSize + 2 * sizeof(fs5_image_layout_vmod_status); //* 2 for active and invalid statuses

    if (!WriteImageExDefaultParams(burnParams, vmodAOffset, vmodData.data(), vmodData.size(), totalSize, writtenSize))
    {
        return false;
    }
    writtenSize += vmodData.size();

    fs5_image_layout_vmod_status vmodActiveStatus = {.image_administrative_status = CSH::VMOD_ADM_STATUS_ACTIVE,
                                                     .tile_administrative_status = CSH::ALL_TILES_COMMITTED,
                                                     .reserved = 0xffff};
    size_t vmodActiveStatusOffset =
      vmodAOffset + sizeof(fs5_image_layout_csh_header) - sizeof(fs5_image_layout_vmod_status);
    if (!WriteImageExDefaultParams(burnParams, vmodActiveStatusOffset, &vmodActiveStatus, sizeof(vmodActiveStatus),
                                   totalSize, writtenSize))
    {
        return false;
    }
    writtenSize += sizeof(vmodActiveStatus);

    fs5_image_layout_vmod_status vmodInvalidStatus = {.image_administrative_status = CSH::VMOD_ADM_STATUS_INVALID,
                                                      .tile_administrative_status = CSH::ALL_TILES_NOT_COMMITTED,
                                                      .reserved = 0xffff};
    size_t vmodInvalidStatusOffset =
      vmodAOffset + vmodASize + sizeof(fs5_image_layout_csh_header) - sizeof(fs5_image_layout_vmod_status);
    if (!WriteImageExDefaultParams(burnParams, vmodInvalidStatusOffset, &vmodInvalidStatus, sizeof(vmodInvalidStatus),
                                   totalSize, writtenSize))
    {
        return false;
    }

    return true;
#endif // } MST_CPU_armv7l_umbriel
}

bool Fs6Operations::ExecuteBurn(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    map<PartitionType, vector<BurnRegion>> partitionTypeToBurnRegions;
    try
    {
        partitionTypeToBurnRegions = GetBurnRegions(imageOps, burnParams.useImgDevData, burnParams.burnFailsafe);
    }
    catch (const std::runtime_error& e)
    {
        return errmsg("%s", e.what());
    }

    uint32_t alreadyWrittenSize = 0;
    uint32_t totalSize = GetTotalBurnSize(partitionTypeToBurnRegions);
    if (burnParams.burnFailsafe)
    {
        totalSize += PartitionTable::RomImageMagicPattern().size(); // to set magic pattern for candidate chain
        if (_activeChain != INVALID_CHAIN_NUMBER)
        {
            totalSize += PartitionTable::RomImageMagicPattern().size(); // need to make previous active chain to backup
        }
    }
    else if (!burnParams.useImgDevData && _activeChain == 1) // nofs -> burn to chain 0 -> need to make chain 1 backup
                                                             // in case it was active before
    {
        totalSize += PartitionTable::RomImgsBackupMagicPattern().size();
    }
    MLXFWOPS_LOG_DEBUG("total size to burn: 0x%x", totalSize);

    // Cast to FImage to access the image buffer
    FImage* fim = (FImage*)(imageOps->GetIoAccess());
    u_int8_t* imageData = (u_int8_t*)fim->getBuf();
    for (const auto& entry : partitionTypeToBurnRegions)
    {
        for (const auto& region : entry.second)
        {
            size_t srcOffset = region.src_offset;
            size_t alreadyWrittenSizeForRegion = 0;
            if (burnParams.burnFailsafe &&
                region.partitionType == PartitionType::PT_ROM_IMGS) // avoid writing magic pattern at this tsage, needs
                                                                    // to happen post burn in case of fail safe
            {
                MLXFWOPS_LOG_DEBUG("Writing %x bytes to address 0x%zx (from address 0x%zx in image)",
                         ROM_IMGS_MAGIC_PATTERN_OFFSET, region.dest_offset, region.src_offset);
                if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc,
                                  region.dest_offset, imageData + region.src_offset, ROM_IMGS_MAGIC_PATTERN_OFFSET,
                                  true, true, totalSize, alreadyWrittenSize))
                {
                    return false;
                }
                alreadyWrittenSize += ROM_IMGS_MAGIC_PATTERN_OFFSET;

                vector<u_int8_t> zeroes = vector<u_int8_t>(PartitionTable::RomImageMagicPattern().size(), 0);
                MLXFWOPS_LOG_DEBUG("Writing %zx bytes to address 0x%zx (from address 0x%zx in image)", zeroes.size(),
                         region.dest_offset + ROM_IMGS_MAGIC_PATTERN_OFFSET,
                         region.src_offset + ROM_IMGS_MAGIC_PATTERN_OFFSET);
                if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc,
                                  region.dest_offset + ROM_IMGS_MAGIC_PATTERN_OFFSET, (void*)zeroes.data(),
                                  zeroes.size(), true, true, totalSize, alreadyWrittenSize))
                {
                    return false;
                }
                alreadyWrittenSize += zeroes.size();

                srcOffset = srcOffset + ROM_IMGS_MAGIC_PATTERN_OFFSET + zeroes.size();
                alreadyWrittenSizeForRegion = ROM_IMGS_MAGIC_PATTERN_OFFSET + zeroes.size();
            }

            MLXFWOPS_LOG_DEBUG("Writing %zx bytes to address 0x%zx (from address 0x%zx in image). Region %s, partitionType 0x%x",
                     region.size - alreadyWrittenSizeForRegion, region.dest_offset + alreadyWrittenSizeForRegion,
                     srcOffset, region.name.c_str(), static_cast<u_int32_t>(region.partitionType));
            if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc,
                              region.dest_offset + alreadyWrittenSizeForRegion, imageData + srcOffset,
                              region.size - alreadyWrittenSizeForRegion, true, true, totalSize, alreadyWrittenSize))
            {
                return false;
            }
            alreadyWrittenSize += (region.size - alreadyWrittenSizeForRegion);
        }
    }

    if (!HandleRomImgsMagicPatternsPostBurn(burnParams, alreadyWrittenSize, totalSize))
    {
        return false;
    }

    return true;
}

bool Fs6Operations::FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    if (!PreBurnChecks(imageOps, burnParams))
    {
        return false;
    }

    if (!DoBeforeBurnJobs())
    {
        return false;
    }

    if (imageOps->FwType() == FIT_CSH_VMOD)
    {
        if (!ExecuteVmodBurn(imageOps, burnParams))
        {
            return false;
        }
    }
    else
    {
        if (!ExecuteBurn(imageOps, burnParams))
        {
            return false;
        }
    }

    if (!DoAfterBurnJobs())
    {
        return false;
    }

    return true;
}

bool Fs6Operations::isEncrypted(bool& is_encrypted) // in FS6 device and image are always encrypted and signed. there
                                                    // are differnt enc/signing keys so we need to check the key type to
                                                    // determine the enc type. until the mapping for it is determined we
                                                    // always return true.
{
    // TODO: implement isEncrypted
    is_encrypted = true;
    MLXFWOPS_LOG_DEBUG("Fs6Operations::isEncrypted res = TRUE");
    return true;
}

bool Fs6Operations::FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    vector<u_int8_t> devInfoData = ReadPartitionData(PartitionType::PT_DEV_INFO);
    struct image_layout_device_info devInfo;
    fs3_uid_t usrGuid;
    image_layout_device_info_unpack(&devInfo, devInfoData.data());
    memset(&usrGuid, 0, sizeof(usrGuid));

    if (!ChangeDeviceInfoUidsFromBase(usrGuid, sgParam))
    {
        return false;
    }

    if (!ChangeUidsFromBase(usrGuid, devInfo.guids))
    {
        return false;
    }

    devInfo.signature0 = DEV_INFO_SIG0;
    devInfo.signature1 = DEV_INFO_SIG1;
    devInfo.signature2 = DEV_INFO_SIG2;
    devInfo.signature3 = DEV_INFO_SIG3;

    image_layout_device_info_pack(&devInfo, devInfoData.data());
    UpdatePartitionData(PartitionType::PT_DEV_INFO, devInfoData, callBackFunc);
    if (!UpdateCrcInfoForPartition(PartitionType::PT_DEV_INFO, devInfoData))
    {
        return false;
    }
    return true;
}

bool Fs6Operations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    FAIL_NO_OCR("set manufacture GUIDs/MACs");

    if (!baseGuid.base_guid_specified && !baseGuid.base_mac_specified)
    {
        return errmsg("base GUID/MAC were not specified.");
    }
    if (baseGuid.base_mac_specified && !CheckMac(baseGuid.base_mac))
    {
        return errmsg("Bad MAC (" MAC_FORMAT ") given: %s. Please specify a valid MAC value", baseGuid.base_mac.h,
                      baseGuid.base_mac.l, err());
    }
    if (!baseGuid.use_pp_attr)
    {
        baseGuid.num_of_guids_pp[0] = baseGuid.num_of_guids ? baseGuid.num_of_guids : DEFAULT_GUID_NUM;
        baseGuid.step_size_pp[0] = baseGuid.step_size ? baseGuid.step_size : DEFAULT_STEP;
        baseGuid.num_of_guids_pp[1] = baseGuid.num_of_guids ? baseGuid.num_of_guids : DEFAULT_GUID_NUM;
        baseGuid.step_size_pp[1] = baseGuid.step_size ? baseGuid.step_size : DEFAULT_STEP;
        baseGuid.use_pp_attr = 1;
    }

    vector<u_int8_t> mfgInfoData = ReadPartitionData(PartitionType::PT_MFG_INFO);

    fs6_image_layout_mfg_info fs6MfgInfo;
    fs6_image_layout_mfg_info_unpack(&fs6MfgInfo, mfgInfoData.data());
    struct image_layout_guids guids = ToImageLayoutGuids(fs6MfgInfo.guids);
    if (!ChangeUidsFromBase(baseGuid, guids))
    {
        return false;
    }
    fs6MfgInfo.guids = ToFs6MfgInfoGuids(guids);
    fs6_image_layout_mfg_info_pack(&fs6MfgInfo, mfgInfoData.data());

    UpdatePartitionData(PartitionType::PT_MFG_INFO, mfgInfoData, callBackFunc);
    if (!UpdateCrcInfoForPartition(PartitionType::PT_MFG_INFO, mfgInfoData))
    {
        return false;
    }

    return true;
}

bool Fs6Operations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    if (!vpdFileStr)
    {
        return errmsg("Please specify a valid vpd file.");
    }

    FAIL_NO_OCR("set VPD");

    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    vector<u_int8_t> vpdData = mft_utils::ReadFromFile(vpdFileStr);
    if (vpdData.size() % 4)
    {
        return errmsg("Size of VPD file is not 4-byte aligned");
    }
    if (vpdData.size() > VPD_MAX_SIZE)
    {
        return errmsg("VPD data size exceeds max VPD size: 0x%x bytes", VPD_MAX_SIZE);
    }

    UpdatePartitionData(PartitionType::PT_VPD_READ_ONLY, vpdData, callBackFunc);
    if (!UpdateCrcInfoForPartition(PartitionType::PT_VPD_READ_ONLY, vpdData))
    {
        return false;
    }
    _l1pt.SetEntrySize(PartitionType::PT_VPD_READ_ONLY, vpdData.size());
    UpdatePartitionTable(IsL2ptSection(PartitionType::PT_VPD_READ_ONLY), callBackFunc);

    return true;
}

bool Fs6Operations::IsSectionExists(fs3_section_t sectionType)
{
    auto entries = IsL2ptSection(PartitionType(sectionType)) ? _l2pt.GetEntries() : _l1pt.GetEntries();
    for (const auto& entry : entries)
    {
        if (entry.GetPartitionType() == sectionType)
        {
            return true;
        }
    }
    return false;
}

bool Fs6Operations::UpdateSectionAllowed(fs3_section_t sectionType)
{
    return sectionType == FS4_CPO_CALIBRATION_DATA;
}

bool Fs6Operations::UpdateSection(fs3_section_t sectionType,
                                  std::vector<u_int8_t>& newSectionData,
                                  const char* msg,
                                  PrintCallBack callBackFunc)
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::UpdateSection sectionType: 0x%x, msg: %s", sectionType, msg);
    if (!UpdateSectionAllowed(sectionType))
    {
        return errmsg("updating section type 0x%x is not supported for FS6\n", sectionType);
    }
    FAIL_NO_OCR(string_format("update %s", ToString(PartitionType(sectionType)).c_str()).c_str());

    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    if (!IsSectionExists(sectionType))
    {
        string io_mode = (_ioAccess && _ioAccess->is_flash()) ? "device" : "image";
        return errmsg("section type 0x%x does not exist in %s\n", sectionType, io_mode.c_str());
    }

    size_t partitionSize = 0, partitionOffset = 0;
    GetPartitionEntryInfo(PartitionType(sectionType), partitionOffset, partitionSize);
    if (IsPartitionTypeMaxSize(PartitionType(sectionType))) // TODO: If adding a partition that is not max-sized,
                                                            // clarify the expected behavior when the new content
                                                            // overlaps with the following section. Should the flow
                                                            // fail,
                                                            // or should the subsequent sections be shifted accordingly?
    {
        if (newSectionData.size() > partitionSize)
        {
            if (getenv("ALLOW_OVERSIZED_SECTION") != NULL)
            {
                MLXFWOPS_LOG_DEBUG("new section data size = 0x%x, partition size = 0x%x. resizing to partition size",
                         (u_int32_t)newSectionData.size(), (u_int32_t)partitionSize);
                newSectionData.resize(partitionSize); // allow legacy behaviour if ALLOW_OVERSIZED_SECTION was used
            }
            else
            {
                return errmsg("new section data size (0x%x) exceeds original section size (0x%x bytes). ",
                              (u_int32_t)newSectionData.size(), (u_int32_t)partitionSize);
            }
        }
    }

    if (partitionSize > newSectionData.size())
    {
        newSectionData.resize(partitionSize);
    }

    UpdatePartitionData(PartitionType(sectionType), newSectionData, callBackFunc);
    if (!UpdateCrcInfoForPartition(PartitionType(sectionType), newSectionData))
    {
        return false;
    }

    if (!IsPartitionTypeMaxSize(PartitionType(sectionType))) // updating size is needed
    {
        bool isl2pt = IsL2ptSection(PartitionType(sectionType));
        if (isl2pt)
        {
            _l2pt.SetEntrySize(PartitionType(sectionType), newSectionData.size());
        }
        else // l1pt
        {
            _l1pt.SetEntrySize(PartitionType(sectionType), newSectionData.size());
        }
        UpdatePartitionTable(isl2pt, callBackFunc);
    }

    return true;
}

bool Fs6Operations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool Fs6Operations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
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

image_layout_guids Fs6Operations::ToImageLayoutGuids(const struct fs6_image_layout_guids& fs6Guids)
{
    image_layout_guids imageLayoutGuids;
    imageLayoutGuids.guids.num_allocated = fs6Guids.guids.num_allocated;
    imageLayoutGuids.guids.num_allocated_msb = fs6Guids.guids.num_allocated_msb;
    imageLayoutGuids.guids.step = fs6Guids.guids.step;
    imageLayoutGuids.guids.uid = ((u_int64_t)fs6Guids.guids.uid.hi << 32) | fs6Guids.guids.uid.lo;

    imageLayoutGuids.macs.num_allocated = fs6Guids.macs.num_allocated;
    imageLayoutGuids.macs.num_allocated_msb = fs6Guids.macs.num_allocated_msb;
    imageLayoutGuids.macs.step = fs6Guids.macs.step;
    imageLayoutGuids.macs.uid = ((u_int64_t)fs6Guids.macs.uid.hi << 32) | fs6Guids.macs.uid.lo;
    return imageLayoutGuids;
}

fs6_image_layout_guids Fs6Operations::ToFs6MfgInfoGuids(const struct image_layout_guids& guids)
{
    fs6_image_layout_guids fs6Guids;
    fs6Guids.guids.num_allocated = guids.guids.num_allocated;
    fs6Guids.guids.num_allocated_msb = guids.guids.num_allocated_msb;
    fs6Guids.guids.step = guids.guids.step;
    fs6Guids.guids.uid.hi = (u_int32_t)(guids.guids.uid >> 32);
    fs6Guids.guids.uid.lo = (u_int32_t)(guids.guids.uid & 0xFFFFFFFF);

    fs6Guids.macs.num_allocated = guids.macs.num_allocated;
    fs6Guids.macs.num_allocated_msb = guids.macs.num_allocated_msb;
    fs6Guids.macs.step = guids.macs.step;
    fs6Guids.macs.uid.hi = (u_int32_t)(guids.macs.uid >> 32);
    fs6Guids.macs.uid.lo = (u_int32_t)(guids.macs.uid & 0xFFFFFFFF);
    return fs6Guids;
}

bool Fs6Operations::WriteImageExDefaultParams(const ExtBurnParams& burnParams,
                                              u_int32_t addr,
                                              void* data,
                                              int cnt,
                                              int totalSz,
                                              int alreadyWrittenSz)
{
    return writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc, addr, data,
                        cnt, true, true, totalSz, alreadyWrittenSz);
}

bool Fs6Operations::ParseFs6ImageInfo(struct fs6_image_layout_image_info& image_info,
                                      FwOperations::FwImgInfo& fwImgInfo,
                                      FwOperations::FsCommonInfo& fsCommonInfo)
{
    if (image_info.major_version != 0)
    {
        return false; // unknown image info version
    }

    fwImgInfo.ext_info.image_info_minor_version =
      image_info.minor_version; // in older generations this field told us if to parse name, prs name and description
                                // using tools_open_image_info (minor_version == 2) layout or fsX-specific layout
                                // (minor_version == 3). this is legacy behavior and we now always use the fsX-specific
                                // image_info layout.
    fwImgInfo.ext_info.image_info_major_version = image_info.major_version;

    fwImgInfo.ext_info.fw_ver[0] = image_info.FW_VERSION.MAJOR;
    fwImgInfo.ext_info.fw_ver[1] = image_info.FW_VERSION.MINOR;
    fwImgInfo.ext_info.fw_ver[2] = image_info.FW_VERSION.SUBMINOR;

    // _fwImgInfo.ext_info.isfu_major = image_info.module_versions.mad.major; // this field doesn't exist in
    // fs6_image_layout_image_info

    fwImgInfo.ext_info.mic_ver[0] = image_info.mic_version.MAJOR;
    fwImgInfo.ext_info.mic_ver[1] = image_info.mic_version.MINOR;
    fwImgInfo.ext_info.mic_ver[2] = image_info.mic_version.SUBMINOR;

    fwImgInfo.ext_info.fw_rel_date[0] = (u_int16_t)image_info.FW_VERSION.Day;
    fwImgInfo.ext_info.fw_rel_date[1] = (u_int16_t)image_info.FW_VERSION.Month;
    fwImgInfo.ext_info.fw_rel_date[2] = (u_int16_t)image_info.FW_VERSION.Year;

    fwImgInfo.ext_info.fw_rel_time[0] = (u_int16_t)image_info.FW_VERSION.Hour;
    fwImgInfo.ext_info.fw_rel_time[1] = (u_int16_t)image_info.FW_VERSION.Minutes;
    fwImgInfo.ext_info.fw_rel_time[2] = (u_int16_t)image_info.FW_VERSION.Seconds;

    fwImgInfo.ext_info.burn_image_size = image_info.burn_image_size;
    fwImgInfo.ext_info.dtoc_offset = image_info.dtoc_offset;
    // _fwImgInfo.ext_info.sku = (device_sku)image_info.psc_sku; // this field doesn't exist in
    // fs6_image_layout_image_info

    // assuming number of supported_hw_id + supported_hw_id_extended < MAX_NUM_SUPP_HW_IDS
    memcpy(fwImgInfo.supportedHwId, image_info.supported_hw_id, sizeof(image_info.supported_hw_id));
    memcpy(fwImgInfo.supportedHwId + sizeof(image_info.supported_hw_id) / sizeof(image_info.supported_hw_id[0]),
           image_info.supported_hw_id_extended, sizeof(image_info.supported_hw_id_extended));
    fwImgInfo.supportedHwIdNum = (sizeof(image_info.supported_hw_id) + sizeof(image_info.supported_hw_id_extended)) /
                                 sizeof(image_info.supported_hw_id[0]);

    // _fwImgInfo.ext_info.pci_device_id = image_info.pci_device_id; // this field doesn't exist in
    // fs6_image_layout_image_info

    strcpy(fsCommonInfo.ext_info.image_vsd, image_info.vsd);
    strcpy(fwImgInfo.ext_info.psid, image_info.psid);
    strcpy(fwImgInfo.ext_info.product_ver, image_info.prod_ver);

    // get name, prs name and description
    // Legacy behavior checked minor_version to select layout. (3 -> fsX-specific layout, else -> tools_open_image_info
    // layout) We now always use the fsX-specific image_info layout.
    snprintf(fsCommonInfo.ext_info.name, sizeof(fsCommonInfo.ext_info.name), "%s", image_info.name);
    snprintf(fsCommonInfo.ext_info.description, sizeof(fsCommonInfo.ext_info.description), "%s",
             image_info.description);
    snprintf(fsCommonInfo.ext_info.prs_name, sizeof(fsCommonInfo.ext_info.prs_name), "%s", image_info.prs_name);

    fsCommonInfo.ext_info.mcc_en = image_info.mcc_en;
    fsCommonInfo.ext_info.security_mode =
      (fsCommonInfo.ext_info.security_mode | ((image_info.mcc_en == 1) ? SMM_MCC_EN : 0) |
       ((image_info.debug_fw == 1) ? SMM_DEBUG_FW : 0) | ((image_info.signed_fw == 1) ? SMM_SIGNED_FW : 0) |
       ((image_info.secure_fw == 1) ? SMM_SECURE_FW : 0));

    fsCommonInfo.runFromAny = image_info.image_size.run_from_any;
    fsCommonInfo.logStep = image_info.image_size.log_step;
    fsCommonInfo.ext_info.ini_file_version = image_info.ini_file_num;
    fwImgInfo.ext_info.encrypted_fw = image_info.encrypted_fw;

    return true;
}

bool Fs6Operations::IsSecureBootSupported()
{
    if (_signatureMngr == NULL)
    {
        return false;
    }
    return _signatureMngr->IsSecureBootSupported();
}

bool Fs6Operations::IsLifeCycleAccessible(chip_type_t)
{
    if (_signatureMngr == NULL)
    {
        return false;
    }
    return _signatureMngr->IsLifeCycleSupported();
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
       << std::setfill('0') << endAddr << " (0x" << std::setw(7) << std::setfill('0') << size << ")/ " << std::left
       << std::setw(35) << std::setfill(' ') << sectionType << " | " << suffix << std::endl;
    report_callback(verifyCallBackFunc, ss.str().c_str());
}

void Fs6Operations::PrintPartitionTable(VerifyCallBack verifyCallBackFunc,
                                        const PartitionTable& partitionTable,
                                        size_t ptOffset,
                                        const string& tablePrefix)
{
    MLXFWOPS_LOG_DEBUG("number of entries = %zu, max entries = %zu", partitionTable.GetNumberOfEntries(),
             partitionTable.GetMaxNumberOfEntries());

    // Print entries
    const vector<PartitionTableEntry>& entries = partitionTable.GetEntries();
    for (const auto& entry : entries)
    {
        PartitionType partitionType = entry.GetPartitionTypeEnum();
        bool isCshComponent = IsCshComponent(partitionType);
        string entryName = GetL1ptEntryName(partitionType, isCshComponent) + " entry";

        report_callback(verifyCallBackFunc, "   %-21s: 0x%x (%s)\n", "section type", partitionType, entryName.c_str());
        report_callback(verifyCallBackFunc, "   %-21s: 0x%016zx\n", "section offset", entry.GetStartOffset());
        report_callback(verifyCallBackFunc, "   %-21s: 0x%016zx\n", "section size", entry.GetSectionSize());
    }
}

bool Fs6Operations::InitL3PartitionTable(PartitionTable& pt, size_t& ptOffset, CshSectionType sectionMagic)
{
    vector<u_int8_t> header(PartitionTable::HeaderSize());
    vector<u_int8_t> entryData(PartitionTableEntry::Size());

    if (!GetCshSectionOffset(PartitionType::PT_SWITCH_FWS, sectionMagic, ptOffset, false))
    {
        return true; // for BWC don't fail if L3PT is not found
    }

    if (!_ioAccess->read(ptOffset, header.data(), PartitionTable::HeaderSize()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    if (!std::equal(PartitionTable::MagicID().begin(), PartitionTable::MagicID().end(), header.begin()))
    {
        return errmsg("Couldn't find L3 partition table at 0x%x", (u_int32_t)ptOffset);
    }

    pt.UnpackHeader(header);

    for (size_t i = 0; i < pt.GetNumberOfEntries(); i++)
    {
        size_t entriesOffset = ptOffset + PartitionTable::HeaderSize();
        if (!_ioAccess->read(entriesOffset + i * PartitionTableEntry::Size(), entryData.data(),
                             PartitionTableEntry::Size()))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
        }

        PartitionTableEntry entry;
        entry.Unpack(entryData);
        pt.AddEntry(entry);
    }
    return true;
}

bool Fs6Operations::InitL3pt()
{
    MLXFWOPS_LOG_DEBUG("Fs6Operations::InitL3pt");

    if (_WPAreaPtr == 0 || _RWAreaPtr == 0)
    {
        MLXFWOPS_LOG_DEBUG("WP/RW area pointers not found in L1PT");
    }

    if (!InitL3PartitionTable(_l3pw, _l3pwOffset, CshSectionType::CSH_SECTION_L3PW_MAGIC_ID))
    {
        return false;
    }

    if (!InitL3PartitionTable(_l3pr, _l3prOffset, CshSectionType::CSH_SECTION_L3PR_MAGIC_ID))
    {
        return false;
    }

    return true;
}

static u_int32_t CalcFs6SectionCrc(const vector<u_int8_t>& sectionData)
{
    ImageCrc crc;
    crc << sectionData;
    return crc.get();
}

static void UpdateCrcSquareLegacy(fs6_image_layout_dev_area_crc_info_legacy& info, vector<u_int8_t>& buf)
{
    // Sync struct -> buf (entries changed in memory; buf was stale after unpack)
    fs6_image_layout_dev_area_crc_info_legacy_pack(&info, buf.data());

    const size_t bodySize = offsetof(fs6_image_layout_dev_area_crc_info_legacy, crc_square);
    vector<u_int8_t> body(buf.begin(), buf.begin() + bodySize);
    ImageCrc c;
    c << body;
    info.crc_square = c.get();

    // Write crc_square into buf (same as second full pack, only that field)
    fs6_image_layout_dev_area_crc_info_legacy_pack(&info, buf.data());
}

static void UpdateCrcSquareNew(fs6_image_layout_dev_area_crc_info& info, vector<u_int8_t>& buf)
{
    fs6_image_layout_dev_area_crc_info_pack(&info, buf.data());

    const size_t bodySize = offsetof(fs6_image_layout_dev_area_crc_info, crc_square);
    vector<u_int8_t> body(buf.begin(), buf.begin() + bodySize);
    ImageCrc c;
    c << body;
    info.crc_square = c.get();

    fs6_image_layout_dev_area_crc_info_pack(&info, buf.data());
}

static u_int32_t GetCrcInfoV1MaxEntries()
{
    using Info = fs6_image_layout_dev_area_crc_info;
    return static_cast<u_int32_t>(sizeof(std::declval<Info>().crc_entry) / sizeof(std::declval<Info>().crc_entry[0]));
}

static u_int32_t GetCrcInfoV0MaxEntries()
{
    using Info = fs6_image_layout_dev_area_crc_info_legacy;
    return static_cast<u_int32_t>(sizeof(std::declval<Info>().crc_entry) / sizeof(std::declval<Info>().crc_entry[0]));
}

bool Fs6Operations::UpdateCrcInfoForPartition(PartitionType partitionType, const vector<u_int8_t>& sectionData)
{
    if (IsCshComponent(partitionType) || partitionType == PartitionType::PT_CRC_INFO)
    {
        return true;
    }

    PartitionTableEntry crcInfoPtEntry;
    try
    {
        crcInfoPtEntry = _l1pt.GetEntry(PartitionType::PT_CRC_INFO);
    }
    catch (const runtime_error&)
    {
        return true; // no crc_info partition in this image
    }

    const size_t crcInfoOffset = crcInfoPtEntry.GetStartOffset();
    vector<u_int8_t> buf(fs6_image_layout_dev_area_crc_info_legacy_size()); // 0x400

    if (!_ioAccess->read(crcInfoOffset, buf.data(), buf.size()))
    {
        return errmsg("%s", _ioAccess->err());
    }

    fs6_image_layout_dev_area_crc_info_legacy info_legacy;
    fs6_image_layout_dev_area_crc_info_legacy_unpack(&info_legacy, buf.data());

    const u_int32_t newCrc = CalcFs6SectionCrc(sectionData);
    bool found = false;

    if (info_legacy.version == 1)
    {
        fs6_image_layout_dev_area_crc_info info;
        fs6_image_layout_dev_area_crc_info_unpack(&info, buf.data());

        if (info.num_entries > GetCrcInfoV1MaxEntries())
        {
            return errmsg("CRC_INFO num_entries (%u) exceeds layout max (%u)", info.num_entries,
                          GetCrcInfoV1MaxEntries());
        }
        for (u_int32_t i = 0; i < info.num_entries; ++i)
        {
            if (static_cast<PartitionType>(info.crc_entry[i].partition_type) != partitionType)
            {
                continue;
            }
            info.crc_entry[i].partition_size = static_cast<u_int32_t>(sectionData.size());
            info.crc_entry[i].crc = newCrc;
            found = true;
            break;
        }

        if (!found)
        {
            return true;
        }

        UpdateCrcSquareNew(info, buf);
    }
    else
    {
        if (info_legacy.num_entries > GetCrcInfoV0MaxEntries())
        {
            return errmsg("CRC_INFO num_entries (%u) exceeds layout max (%u)", info_legacy.num_entries,
                          GetCrcInfoV0MaxEntries());
        }
        for (u_int32_t i = 0; i < info_legacy.num_entries; ++i)
        {
            if (static_cast<PartitionType>(info_legacy.crc_entry[i].partition_type) != partitionType)
            {
                continue;
            }
            info_legacy.crc_entry[i].crc = newCrc;
            found = true;
            break;
        }

        if (!found)
        {
            return true;
        }

        UpdateCrcSquareLegacy(info_legacy, buf);
    }

    if (!writeImage((ProgressCallBack)NULL, crcInfoOffset, buf.data(), (int)buf.size(),
                    /*isPhysAddr=*/false, /*readModifyWrite=*/true))
    {
        return false; // writeImage already set the error message
    }

    return true;
}

bool Fs6Operations::PrintCrcInfoLayout(VerifyCallBack verifyCallBackFunc,
                                       const PartitionTableEntry& entry,
                                       bool showitoc)
{
    const size_t base = entry.GetStartOffset();
    const size_t sectionSize = fs6_image_layout_dev_area_crc_info_legacy_size(); // same size for both versions
    vector<u_int8_t> buf(sectionSize);
    if (!_ioAccess->read(base, buf.data(), buf.size()))
    {
        return errmsg("%s", _ioAccess->err());
    }
    fs6_image_layout_dev_area_crc_info_legacy info_legacy;
    fs6_image_layout_dev_area_crc_info_legacy_unpack(&info_legacy, buf.data());
    const bool v1 = (info_legacy.version == 1);
    u_int32_t numEntries = info_legacy.num_entries;
    const u_int32_t maxEntries = v1 ? GetCrcInfoV1MaxEntries() : GetCrcInfoV0MaxEntries();
    if (numEntries > maxEntries)
    {
        return errmsg("CRC_INFO num_entries (%u) exceeds layout max (%u)", numEntries, maxEntries);
    }

    if (!showitoc)
    {
        return true; // the rest is for printing, not validation
    }

    fs6_image_layout_dev_area_crc_info info;
    if (v1)
    {
        fs6_image_layout_dev_area_crc_info_unpack(&info, buf.data());
    }
    for (u_int32_t i = 0; i < numEntries; ++i)
    {
        const u_int32_t ptype = v1 ? info.crc_entry[i].partition_type : info_legacy.crc_entry[i].partition_type;
        if (ptype == 0)
        {
            throw runtime_error("CRC_INFO unexpected partition type for CRC_INFO entry #" + to_string(i));
        }
        PartitionType partitionType = static_cast<PartitionType>(ptype);
        bool isCshComponent = IsCshComponent(partitionType);
        const string entryName = GetL1ptEntryName(partitionType, isCshComponent) + " entry";
        report_callback(verifyCallBackFunc, "   %-21s: 0x%x (%s)\n", "section type", ptype, entryName.c_str());
        if (v1)
        {
            report_callback(verifyCallBackFunc, "   %-21s: 0x%016x\n", "section size",
                            info.crc_entry[i].partition_size);
        }
        report_callback(verifyCallBackFunc, "   %-21s: 0x%08x\n", "crc",
                        v1 ? info.crc_entry[i].crc : info_legacy.crc_entry[i].crc);
    }
    const u_int32_t crcSquare = v1 ? info.crc_square : info_legacy.crc_square;
    report_callback(verifyCallBackFunc, "   %-21s: 0x%08x\n", "crc_square", crcSquare);

    return true;
}

void Fs6Operations::PrintSectionMetadata(const BinarySectionMetadata& section, VerifyCallBack verifyCallBackFunc)
{
    const u_int32_t magicId = (u_int32_t)section.GetSectionType();
    report_callback(verifyCallBackFunc, "   %-21s: 0x%x (%s)\n", "magic id", magicId,
                    mft_utils::ToString(&magicId, 1, false).c_str());
    report_callback(verifyCallBackFunc, "   %-21s: 0x%016llx\n", "load destination",
                    (unsigned long long)section.GetLoadDestination());
    report_callback(verifyCallBackFunc, "   %-21s: 0x%016llx\n", "entry point",
                    (unsigned long long)section.GetEntryPoint());
}