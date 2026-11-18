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
#include "bch/csh_imp.h"

#ifdef MFT_LEGACY_BUILD
#include <mft_utils.h>
#else
#include "mft_utils/mft_utils.h"
#endif

#include <algorithm>
#include <iomanip>

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
            return "ROM_IMGS";
        case PartitionType::PT_CHAIN_CONTAINER:
            return "CHAIN_CONTAINER";
        case PartitionType::PT_BCT_DTB:
            return "BCT_DTB";
        case PartitionType::PT_OEM_FWS:
            return "OEM_FWS";
        case PartitionType::PT_NV_FWS:
            return "NV_FWS";
        case PartitionType::PT_SWITCH_FWS:
            return "SWITCH_FWS";
        case PartitionType::PT_SBD_FW:
            return "SBD_FW";
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

bool Fs6Operations::Init()
{
    const vector<u_int8_t> magicID({0x8B, 0x8D, 0x9E, 0x8F, 0x74, 0x72, 0x61, 0x70});
    vector<u_int8_t> partitionTable(PartitionTable::HeaderSize());
    vector<u_int8_t> entryData(PartitionTableEntry::Size());

    if (!_ioAccess->read(_l1ptOffset, partitionTable.data(), PartitionTable::HeaderSize()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    if (!std::equal(magicID.begin(), magicID.end(), partitionTable.begin()))
    {
        return errmsg("Couldn't find L1PT.");
    }

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
        _l1pt.AddEntry(entry);

        if (IsCshComponent((PartitionType)entry.GetSectionType()))
        {
            InitCshComponent((PartitionType)entry.GetSectionType(), entry.GetStartOffset());
        }

        if (PartitionType(entry.GetSectionType()) == PartitionType::PT_CHAIN_CONTAINER)
        {
            _l2ptOffset = entry.GetStartOffset();
            if (!_ioAccess->read(_l2ptOffset, partitionTable.data(), PartitionTable::HeaderSize()))
            {
                return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
            }
            _l2pt.UnpackHeader(partitionTable);

            if (!std::equal(magicID.begin(), magicID.end(), partitionTable.begin()))
            {
                return errmsg("Couldn't find L2PT.");
            }

            for (size_t i = 0; i < _l2pt.GetNumberOfEntries(); i++)
            {
                size_t l2PartitionsOffset = _l2ptOffset + PartitionTable::HeaderSize();
                if (!_ioAccess->read(l2PartitionsOffset + i * PartitionTableEntry::Size(),
                                     entryData.data(),
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
        }
    }

    return true;
}

bool Fs6Operations::InitCshComponent(PartitionType partitionType, u_int32_t offset)
{
    vector<u_int8_t> cshData(CSH::HeaderSize());

    if (!_ioAccess->read(offset, cshData.data(), CSH::HeaderSize()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }

    CSH csh;
    csh.UnpackHeader(cshData);

    cshData.resize(csh.GetNumberOfBinaries() * BinarySectionMetadata::Size());
    if (!_ioAccess->read(offset + CSH::HeaderSize(), cshData.data(), cshData.size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }
    csh.UnpackSections(cshData);

    _cshComponents.push_back(make_pair(partitionType, csh));
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
    if (!Init())
    {
        return false;
    }

    report_callback(verifyCallBackFunc, "\nFS6 failsafe image\n\n");

    PrintSectionRange(verifyCallBackFunc, _l1ptOffset, _l1ptOffset + _l1pt.Size() - 1, _l1pt.Size(),
                      "L1 Partition Table");

    for (auto entry : _l1pt.GetEntries())
    {
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
                if (!VerifyCshComponent((PartitionType)entry.GetSectionType(), entry.GetStartOffset(),
                                        verifyCallBackFunc))
                {
                    return false;
                }
            }
            else if (PartitionType(entry.GetSectionType()) == PartitionType::PT_CHAIN_CONTAINER)
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

    return true;
}

bool Fs6Operations::VerifyCshComponent(PartitionType partitionType, u_int32_t offset, VerifyCallBack verifyCallBackFunc)
{
    auto cshComponent =
      find_if(_cshComponents.begin(), _cshComponents.end(),
              [partitionType](const pair<PartitionType, CSH>& entry) { return entry.first == partitionType; });

    if (cshComponent != _cshComponents.end())
    {
        string compName = ToString(CshComponentID(cshComponent->second.GetComponentId()));
        PrintSectionRange(verifyCallBackFunc, offset, offset + cshComponent->second.Size() - 1,
                          cshComponent->second.Size(), compName, "CSH");

        u_int32_t prevSectionEnd = cshComponent->second.Size();
        u_int32_t currSectionBegin = 0;
        string sectionName;

        for (auto section : cshComponent->second.GetSections())
        {
            if (partitionType == PartitionType::PT_SWITCH_FWS)
            {
                sectionName = GetSectionNameByType(section.GetSectionType());
            }
            else
            {
                sectionName = mft_utils::ToHexString(section.GetSectionType(), 2);
            }
            size_t sectionOffset = offset + section.GetSectionOffset();
            PrintSectionRange(verifyCallBackFunc, sectionOffset, sectionOffset + section.GetSectionSize() - 1,
                              section.GetSectionSize(), sectionName, "CSH Section");

            currSectionBegin = section.GetSectionOffset();
            if (currSectionBegin > prevSectionEnd)
            {
                return errmsg("section %s intersects with the previous section", sectionName.c_str());
            }
            prevSectionEnd = section.GetSectionOffset() + section.GetSectionSize();
        }

        if (prevSectionEnd > cshComponent->second.GetComponentSize())
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
        componentOffset = _l1pt.GetEntryOffset(ToPartitionType(cshId));
    }

    UpdatePartitionTable(!isL2pt);

    if (!_ioAccess->write(componentOffset, compData.data(), compData.size()))
    {
        return errmsg("%s - write error (%s)\n", msg, _ioAccess->err());
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

bool Fs6Operations::FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool)
{
    if (!FwVerify((VerifyCallBack) nullptr))
    {
        return false;
    }

    fwInfo->fw_type = FwType();

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
    return Unsupported(__FUNCTION__);
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
