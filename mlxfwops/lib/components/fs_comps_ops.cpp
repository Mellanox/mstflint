/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <fs_comps_ops.h>

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

