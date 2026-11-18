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

#include <algorithm>
#include <iomanip>

CshComponentID ToCshId(ComponentName compName)
{
    CshComponentID id = CshComponentID::Unknown;
    switch (compName)
    {
        case ComponentName::Comp_Csh_Rom_Imgs:
            id = CshComponentID::ROM_IMGS;
            break;
        case ComponentName::Comp_Csh_Nv_Fws:
            id = CshComponentID::NV_FWS;
            break;
        case ComponentName::Comp_Csh_Oem_Fws:
            id = CshComponentID::OEM_FWS;
            break;
        case ComponentName::Comp_Csh_Bct_Dtb:
            id = CshComponentID::BCT_DTB;
            break;
        case ComponentName::Comp_Csh_Switch_Fws:
            id = CshComponentID::SWITCH_FWS;
            break;
        case ComponentName::Comp_Csh_Sbd_Fw:
            id = CshComponentID::SBD_FW;
            break;
        default:
            break;
    }
    return id;
}

bool Fs6Operations::FwInit()
{
    const vector<u_int8_t> magicID({0x8B, 0x8D, 0x9E, 0x8F, 0x74, 0x72, 0x61, 0x70});
    vector<u_int8_t> partitionTable(PartitionTable::HeaderSize());
    vector<u_int8_t> entryData(PartitionTableEntry::Size());

    if (!_ioAccess->read(0x2000, partitionTable.data(), PartitionTable::HeaderSize()))
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
        if (!_ioAccess->read(0x2070 + i * PartitionTableEntry::Size(), entryData.data(), PartitionTableEntry::Size()))
        {
            return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
        }

        PartitionTableEntry entry;
        entry.Unpack(entryData);
        _l1ptEntries.push_back(entry);

        if (entry.GetSectionType() == 0x3)
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
                if (!_ioAccess->read(_l2ptOffset + 0x70 + i * PartitionTableEntry::Size(),
                                     entryData.data(),
                                     PartitionTableEntry::Size()))
                {
                    return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
                }
                PartitionTableEntry entry;
                entry.Unpack(entryData);
                _l2ptEntries.push_back(entry);
            }
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

bool Fs6Operations::ReadComponent(ComponentName compName,
                                  ComponentHeader compHeader,
                                  string,
                                  vector<u_int8_t>& componentData)
{
    CshComponentID id = ToCshId(compName);
    if (id == CshComponentID::Unknown)
    {
        // TODO
        return errmsg("Unknown component");
    }

    if (compHeader != ComponentHeader::Header_With)
    {
        // TODO
        return errmsg("Only header with component supported at the moment");
    }

    auto cshComponent = GetCshEntry(id);
    u_int32_t componentOffset = cshComponent.GetStartOffset();
    if (IsL2ptSection(id))
    {
        componentOffset += _l2ptOffset;
    }

    componentData.resize(cshComponent.GetSectionsize());
    if (!_ioAccess->read(componentOffset, componentData.data(), componentData.size()))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
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
    return Unsupported(__FUNCTION__);
}

#ifndef MST_CPU_armv7l_umbriel // {
bool Fs6Operations::SignForSecureBoot(const char*, const char*, const MlxSign::Signer&)
{
    return Unsupported(__FUNCTION__);
}
#endif // } MST_CPU_armv7l_umbriel

bool Fs6Operations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    cout << left << setw(22) << "Partition Table" << setw(22) << "Partition Type" << setw(22) << "Start Address"
         << setw(22) << "Partition Size" << endl;

    for (auto entry : _l1ptEntries)
    {
        cout << left << setw(22) << "L1PT" << std::hex << "0x" << setw(20) << entry.GetSectionType() << "0x" << setw(20)
             << entry.GetStartOffset() << "0x" << setw(20) << entry.GetSectionsize() << endl;
    }
    for (auto entry : _l2ptEntries)
    {
        cout << left << setw(22) << "L2PT" << std::hex << "0x" << setw(20) << entry.GetSectionType() << "0x" << setw(20)
             << entry.GetStartOffset() << "0x" << setw(20) << entry.GetSectionsize() << endl;
    }

    return true;
}

const PartitionTableEntry& Fs6Operations::GetCshEntry(CshComponentID cshId)
{
    const auto compareFunc = [cshId](const PartitionTableEntry& entry)
    { return (CshComponentID)entry.GetSectionType() == cshId; };
    auto component = std::find_if(_l1ptEntries.begin(), _l1ptEntries.end(), compareFunc);
    if (component == _l1ptEntries.end())
    {
        component = std::find_if(_l2ptEntries.begin(), _l2ptEntries.end(), compareFunc);
        if (component == _l2ptEntries.end())
        {
            // TODO
            throw exception();
        }
    }
    return *component;
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
