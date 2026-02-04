/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#include "fs_pldm.h"
#ifdef MFT_LEGACY_BUILD
#include <mft_utils.h>
#else
#include "mft_utils/mft_utils.h"
#endif
#include <string>

// bool FsPldmOperations::FwInit()
// {
//     if (_ioAccess->get_size() < sizeof(_header))
//     {
//         return errmsg("Unknown image format");
//     }
//     if (!_ioAccess->read(0, (u_int32_t*)&_header, sizeof(_header)))
//     {
//         return errmsg("Failed to read Image: %s", _ioAccess->err());
//     }
//     if (_header.headerVersion > 1)
//     {
//         return errmsg("Unknown image format");
//     }
//     return true;
// }

bool FsPldmOperations::FwInit()
{
    FwInitCom();
    // memset(&_fs2ImgInfo, 0, sizeof(_fs2ImgInfo)); init is done as part of the struct constructor
    _fwImgInfo.fwType = FIT_PLDM_1_0;
    return true;
}

bool FsPldmOperations::LoadPldmPackage()
{
    FPldm* pldmAccess = dynamic_cast<FPldm*>(_ioAccess);
    if (!pldmAccess)
    {
        return errmsg("File is not a valid PLDM package");
    }
    _pldmFile = std::string(pldmAccess->get_fname());

    PldmBuffer buff;
    if (buff.loadFile(_pldmFile))
    {
        return false;
    }
    if (!_pkg.unpack(buff))
    {
        return false;
    }
    return true;
}

bool FsPldmOperations::GetImageSize(u_int32_t* image_size)
{
    *image_size = _ioAccess->get_size();
    return true;
}

bool FsPldmOperations::FwReadData(void* image, u_int32_t*, bool)
{
    if (image != NULL)
    {
        u_int32_t size = 0;
        GetImageSize(&size);
        if (!_ioAccess->read(0, (u_int32_t*)image, size))
        {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }
    return true;
}

bool FsPldmOperations::GetPldmComponentData(string component, string psid, u_int8_t** buff, u_int32_t& buffSize)
{
    std::string strPsid(psid);
    ComponentIdentifier compIdentifier;
    try
    {
        StringToComponentIdentifier(component, compIdentifier);
    }
    catch (PLDMException& e)
    {
        return errmsg("%s", e._err.c_str());
    }
    bool rc = _pkg.getComponentDataByPsid(compIdentifier, strPsid, buff, buffSize);
    return rc;
}

bool FsPldmOperations::GetPldmDescriptor(string psid, u_int16_t type, u_int16_t& descriptor)
{
    return _pkg.getPldmDescriptorByPsid(psid, type, descriptor);
}

string FsPldmOperations::GetPldmVendorDefinedDescriptor(string psid, PldmRecordDescriptor::VendorDefinedType type)
{
    return _pkg.getPldmVendorDefinedDescriptorByPsid(psid, type);
}

bool FsPldmOperations::CreateFwOpsImage(u_int32_t* buff,
                                        u_int32_t buffSize,
                                        FwOperations** newImageOps,
                                        u_int16_t swDevId,
                                        bool isStripedImage)
{
    if (!CreateBasicImageFromData(buff, buffSize, newImageOps, swDevId, isStripedImage))
    {
        return false;
    }
    return true;
}

FwComponent::comps_ids_t FsPldmOperations::ToCompId(string componentName)
{
    if (componentName == "BFB")
    {
        return FwComponent::comps_ids_t::COMPID_BFB;
    }
    return FwComponent::comps_ids_t::COMPID_UNKNOWN;
}

bool FsPldmOperations::FwQuery(fw_info_t*, bool, bool, bool, bool, bool)
{
    return true;
}

bool FsPldmOperations::FwVerify(VerifyCallBack, bool, bool, bool)
{
    return Unsupported(__FUNCTION__);
}

bool FsPldmOperations::FwReadRom(std::vector<u_int8_t>&)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnRom(FImage*,
                                 bool,
                                 bool,
                                 ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwDeleteRom(bool, ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurn(FwOperations*, u_int8_t, ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnAdvanced(FwOperations*, ExtBurnParams&)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnBlock(FwOperations*, ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetGuids(sg_params_t&, PrintCallBack, ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetMFG(fs3_uid_t, PrintCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetMFG(guid_t, PrintCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetVSD(char*, ProgressCallBack, PrintCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetVPD(char*, PrintCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetAccessKey(hw_key_t, ProgressCallBack)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwGetSection(u_int32_t, std::vector<u_int8_t>&, bool)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwResetNvData()
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwShiftDevData(PrintCallBack)
{
    return Unsupported(__FUNCTION__);
}
const char* FsPldmOperations::FwGetResetRecommandationStr()
{
    Unsupported(__FUNCTION__);
    return "";
}
bool FsPldmOperations::FwCalcMD5(u_int8_t[16])
{
    return Unsupported(__FUNCTION__);
}
