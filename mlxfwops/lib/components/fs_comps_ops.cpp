/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */
#include <fs_comps_ops.h>
#include <mft_utils.h>

FsCompsException::FsCompsException(const string& exceptionMsg) : msg(exceptionMsg) {}
const char* FsCompsException::what() const throw()
{
    return msg.c_str();
}

bool FsCompsOperations::GetImageSize(u_int32_t* image_size)
{
    *image_size = _ioAccess->get_size();
    return true;
}

bool FsCompsOperations::FwReadData(void* image, u_int32_t* image_size, bool verbose)
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

bool FsCompsOperations::CheckFwVersion(ComponentFwVersion currentVersion, u_int8_t forceVersion)
{
    ComponentFwVersion newVersion = ComponentFwVersion(_fwImgInfo.ext_info.fw_ver[0], _fwImgInfo.ext_info.fw_ver[1]);

    printf("\n    Current FW version on flash:  %s\n", currentVersion.ToString().c_str());
    printf("    New FW version:               %s\n", newVersion.ToString().c_str());

    if (currentVersion >= newVersion)
    {
        printf("\n    Note: The new FW version is %s the current FW version on flash.\n",
               currentVersion == newVersion ? "the same as" : "older than");
        if (!mft_utils::askUser(nullptr, forceVersion))
        {
            return errmsg("Aborted by the user.");
        }
    }

    return true;
}

bool FsCompsOperations::IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion)
{
    (void)data;
    (void)forceVersion;
    return true;
}

bool FsCompsOperations::FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool)
{
    return Unsupported(__FUNCTION__);
}

bool FsCompsOperations::SignForSecureBoot(const char*, const char*, const MlxSign::Signer&)
{
    return Unsupported(__FUNCTION__);
}

bool FsCompsOperations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    return Unsupported(__FUNCTION__);
}

bool FsCompsOperations::FwReadRom(std::vector<u_int8_t>& romSect)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwBurnRom(FImage* romImg,
                                  bool ignoreProdIdCheck,
                                  bool ignoreDevidCheck,
                                  ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwBurn(FwOperations* imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage)
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwResetNvData()
{
    return Unsupported(__FUNCTION__);
}
bool FsCompsOperations::FwShiftDevData(PrintCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
const char* FsCompsOperations::FwGetResetRecommandationStr()
{
    Unsupported(__FUNCTION__);
    return "";
}
bool FsCompsOperations::FwCalcMD5(u_int8_t md5sum[16])
{
    return Unsupported(__FUNCTION__);
}

