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
#include <iomanip>

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

    return true;
}

bool FsCshOperations::GetImageInfo(struct fs6_image_layout_image_info* imageInfo)
{
    MLXFWOPS_LOG_DEBUG("FsCshOperations::GetImageInfo");
    if (imageInfo == nullptr)
    {
        return errmsg("imageInfo is nullptr");
    }

    memset(imageInfo, 0, sizeof(fs6_image_layout_image_info));
    vector<u_int8_t> data;
    if (!GetImageInfoData(data))
    {
        return errmsg("Failed to get image info data");
    }
    fs6_image_layout_image_info_unpack(imageInfo, data.data());

    return true;
}

bool FsCshOperations::GetImageInfoData(vector<u_int8_t>& data)
{
    for (auto section : _csh.GetSections())
    {
        string sectionName = BinarySectionMetadata::CshSectionIDToString(section.GetSectionType());

        if (sectionName == "IMAGE_INFO")
        {
            size_t sectionOffset = section.GetSectionOffset();
            data.resize(section.GetSectionSize());
            memset(data.data(), 0, data.size());
            if (!_ioAccess->read(sectionOffset, data.data(), data.size()))
            {
                return errmsg("IMAGE_INFO section - read error (%s)\n", (*_ioAccess).err());
            }
            return true;
        }
    }
    return errmsg("IMAGE_INFO section not found");
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

bool FsCshOperations::PrintQuery()
{
    struct fs6_image_layout_image_info imageInfo;
    if (!GetImageInfo(&imageInfo))
    {
        return errmsg("Failed to get image info");
    }

    switch (_componentID)
    {
        case FwComponent::comps_ids_t::COMPID_CPO_VMOD_FW:
        {
            printf("Image type:            FSVMOD\n");

            if (imageInfo.FW_VERSION.MAJOR || imageInfo.FW_VERSION.MINOR || imageInfo.FW_VERSION.SUBMINOR)
            {
                printf("FW Version:            %u.%u.%u\n",
                       imageInfo.FW_VERSION.MAJOR,
                       imageInfo.FW_VERSION.MINOR,
                       imageInfo.FW_VERSION.SUBMINOR);
            }

            if (imageInfo.FW_VERSION.Day || imageInfo.FW_VERSION.Month || imageInfo.FW_VERSION.Year)
            {
                printf("FW Release Date:       %x.%x.%x\n", imageInfo.FW_VERSION.Day, imageInfo.FW_VERSION.Month,
                       imageInfo.FW_VERSION.Year);
            }

            if (strlen(imageInfo.psid) > 0)
            {
                printf("PSID:                  %s\n", imageInfo.psid);
            }

            if (imageInfo.minor_version != 3)
            {
                MLXFWOPS_LOG_DEBUG("FsCshOperations::PrintQuery() - Minor version is %d, yet it should be 3", imageInfo.minor_version);
            }
            string part_number = imageInfo.name;
            if (!part_number.empty())
            {
                printf("Part Number:           %s\n", part_number.c_str());
            }

            string description = imageInfo.description;
            if (!description.empty())
            {
                printf("Description:           %s\n", description.c_str());
            }

            string prs_name = imageInfo.prs_name;
            if (!prs_name.empty())
            {
                printf("PRS Name:              %s\n", prs_name.c_str());
            }

            u_int32_t imageSize;
            if (!GetImageSize(&imageSize))
            {
                return errmsg("Failed to get image size");
            }
            printf("Image size:            0x%08x\n", imageSize);

            break;
        }
        default:
            return errmsg("Provided CSH is not supported");
    }

    return true;
}

bool FsCshOperations::IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion)
{
    (void)forceVersion;

    struct fs6_image_layout_image_info imageInfo;
    if (!GetImageInfo(&imageInfo))
    {
        return errmsg("Failed to get image info");
    }

    struct DeviceInfoCheckParams deviceInfoCheckParams;
    if (data.size() < sizeof(deviceInfoCheckParams.psid))
    {
        return errmsg("data size (%u) is smaller than expected (%u)", (u_int32_t)data.size(),
                      (u_int32_t)sizeof(deviceInfoCheckParams.psid));
    }
    memcpy(deviceInfoCheckParams.psid, data.data(), sizeof(deviceInfoCheckParams.psid));
    if (strcmp(deviceInfoCheckParams.psid, imageInfo.psid) != 0)
    {
        return errmsg("PSID mismatch: device PSID = %s, image PSID = %s", deviceInfoCheckParams.psid, imageInfo.psid);
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