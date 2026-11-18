/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
#include "fs_csh_ops.h"
#include "nvtoolslogger/NvToolsLogger.h"
#include "../fs6_ops.h"
#include <iomanip>

u_int8_t FsCshOperations::FwType()
{
    switch (_componentID)
    {
        case FwComponent::comps_ids_t::COMPID_CPO_VMOD_FW:
            return FIT_CSH_VMOD;
        default:
            throw runtime_error("Unsupported CSH component ID");
    }
}

bool FsCshOperations::LoadImageInfo()
{
    MLXFWOPS_LOG_DEBUG("FsCshOperations::LoadImageInfo");
    vector<u_int8_t> data;
    if (!GetImageInfoData(data))
    {
        return false;
    }

    struct fs6_image_layout_image_info image_info;
    fs6_image_layout_image_info_unpack(&image_info, data.data());
    if (!Fs6Operations::ParseFs6ImageInfo(image_info, _fwImgInfo, _fsCommonInfo))
    {
        return errmsg("Failed to parse IMAGE_INFO section - %s", err());
    }

    const u_int32_t* swId = (u_int32_t*)NULL;
    MLXFWOPS_LOG_DEBUG("FsCshOperations::LoadImageInfo fwImgInfo.supportedHwId[0]=0x%x", _fwImgInfo.supportedHwId[0]);
    if (!getInfoFromHwDevid(_fwImgInfo.supportedHwId[0], _fwImgInfo.ext_info.chip_type, &swId))
    {
        MLXFWOPS_LOG_DEBUG("FsCshOperations::LoadImageInfo getInfoFromHwDevid failed"); // for backwards compatibility
                                                                                 // instead of failing I'll
                                                                                 // issue a debug print. TODO:
                                                                                 // fail the flow instead in the
                                                                                 // future
    }
    // copy the vsd to the branch ver only for switches. Not valid for NICs. VMOD is only for switches, so no need to
    // check it's a switch
    if (VerifyBranchFormat(image_info.vsd))
    {
        strncpy(_fwImgInfo.ext_info.branch_ver, image_info.vsd, BRANCH_LEN);
        _fwImgInfo.ext_info.branch_ver[BRANCH_LEN - 1] = '\0';
    }

    return true;
}

bool FsCshOperations::FwQuery(fw_info_t* fwInfo,
                              bool readRom,
                              bool isStripedImage,
                              bool quickQuery,
                              bool ignoreDToc,
                              bool verbose)
{
    (void)fwInfo;
    (void)readRom;
    (void)isStripedImage;
    (void)quickQuery;
    (void)ignoreDToc;
    (void)verbose;

    if (!LoadImageInfo())
    {
        return false;
    }

    memcpy(fwInfo, &_fwImgInfo, sizeof(fw_info_t));
    fwInfo->fw_type = FwType();
    memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs3_info), &(_fsCommonInfo.ext_info), sizeof(fs3_info_t));

    return true;
}

bool FsCshOperations::GetImageInfoData(vector<u_int8_t>& data)
{
    MLXFWOPS_LOG_DEBUG("FsCshOperations::GetImageInfoData");
    for (auto section : _csh.GetSections())
    {
        string sectionName = BinarySectionMetadata::CshSectionIDToString(section.GetSectionType());

        // TODO: remove IMAGE_INFO backward compatibility after full integration
        if (sectionName == "VMOD_IMAGE_INFO" || sectionName == "IMAGE_INFO")
        {
            size_t sectionOffset = section.GetSectionOffset();
            data.resize(section.GetSectionSize());
            memset(data.data(), 0, data.size());
            if (!_ioAccess->read(sectionOffset, data.data(), data.size()))
            {
                return errmsg("VMOD_IMAGE_INFO section - read error (%s)\n", (*_ioAccess).err());
            }
            return true;
        }
    }
    return errmsg("VMOD_IMAGE_INFO section not found");
}

bool FsCshOperations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    (void)verifyCallBackFunc;
    (void)isStripedImage;
    (void)showItoc;
    (void)ignoreDToc;

    u_int32_t prevSectionEnd = _csh.GetCshSize();
    u_int32_t currSectionBegin = 0;
    string sectionName;

    string compName = ToString(CshComponentID(_csh.GetComponentId()));
    PrintSectionRange(verifyCallBackFunc, 0, _csh.GetCshSize() - 1, _csh.GetCshSize(), compName, "CSH");

    for (auto section : _csh.GetSections())
    {
        sectionName = BinarySectionMetadata::CshSectionIDToString(section.GetSectionType());
        size_t sectionOffset = section.GetSectionOffset();
        PrintSectionRange(verifyCallBackFunc, sectionOffset, sectionOffset + section.GetSectionSize() - 1,
                          section.GetSectionSize(), sectionName, "CSH Section");

        currSectionBegin = section.GetSectionOffset();
        if (currSectionBegin < prevSectionEnd)
        {
            return errmsg("section %s intersects with the previous section", sectionName.c_str());
        }
        prevSectionEnd = section.GetSectionOffset() + section.GetSectionSize();
    }

    if (prevSectionEnd > _csh.GetComponentSize())
    {
        return errmsg("section %s is out of CSH bounds", sectionName.c_str());
    }

    return true;
}

bool FsCshOperations::FwInit()
{
    vector<u_int8_t> cshData(_ioAccess->get_size());
    if (!_ioAccess->read(0, cshData.data(), cshData.size()))
    {
        return errmsg("Failed to read Image: %s", _ioAccess->err());
    }
    _csh.Unpack(cshData);

    switch (_csh.GetComponentIdEnum())
    {
        case CshComponentID::VMOD_FW:
            MLXFWOPS_LOG_DEBUG("FsCshOperations::FwInit() - Setting component ID to COMPID_CPO_VMOD_FW = 0x%x",
                     FwComponent::comps_ids_t::COMPID_CPO_VMOD_FW);
            _componentID = FwComponent::comps_ids_t::COMPID_CPO_VMOD_FW;
            break;
        default:
            return errmsg("Provided CSH is not supported");
    }

    return true;
}

bool FsCshOperations::IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion)
{
    (void)forceVersion;

    struct DeviceInfoCheckParams deviceInfoCheckParams;
    if (data.size() < sizeof(deviceInfoCheckParams.psid))
    {
        return errmsg("data size (%u) is smaller than expected (%u)", (u_int32_t)data.size(),
                      (u_int32_t)sizeof(deviceInfoCheckParams.psid));
    }
    memcpy(deviceInfoCheckParams.psid, data.data(), sizeof(deviceInfoCheckParams.psid));
    if (strcmp(deviceInfoCheckParams.psid, _fwImgInfo.ext_info.psid) != 0)
    {
        return errmsg("PSID mismatch: device PSID = %s, image PSID = %s", deviceInfoCheckParams.psid,
                      _fwImgInfo.ext_info.psid);
    }

    return true;
}

bool FsCshOperations::FwReadData(void* image, u_int32_t* image_size, bool verbose)
{
    (void)verbose;

    u_int32_t size = _ioAccess->get_size();
    if (image_size)
    {
        size = *image_size;
    }

    if (image != NULL)
    {
        if (!_ioAccess->read(0, (u_int32_t*)image, size))
        {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }

    return true;
}

const char* FsCshOperations::FwGetResetRecommandationStr()
{
    // TODO: Implement FwGetResetRecommandationStr
    return REBOOT_REQUIRED_STR;
}

bool FsCshOperations::GetImageSize(u_int32_t* imageSize)
{
    if (imageSize == nullptr)
    {
        return errmsg("imageSize is nullptr");
    }

    *imageSize = _csh.GetComponentSize();
    return true;
}

bool FsCshOperations::isEncrypted(bool& is_encrypted)
{
    // TODO: implement isEncrypted
    is_encrypted = true;
    return true;
}