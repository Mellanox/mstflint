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
    // TODO: Implement FwQuery
    return true;
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
    if (_csh.GetComponentIdEnum() != CshComponentID::VMOD_FW)
    {
        MLXFWOPS_LOG_DEBUG("Provided CSH is not supported");
        return errmsg("Provided CSH is not supported");
    }
    return true;
}

bool FsCshOperations::PrintQuery()
{
    // TODO: Implement PrintQuery
    printf("Image type:            FSVMOD\n");
    return true;
}

bool FsCshOperations::IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion)
{
    (void)data;
    (void)forceVersion;
    // TODO: Implement IsCompatibleToDevice
    return true;
}

const char* FsCshOperations::FwGetResetRecommandationStr()
{
    // TODO: Implement FwGetResetRecommandationStr
    return REBOOT_REQUIRED_STR;
}
