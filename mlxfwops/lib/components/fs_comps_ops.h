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
#ifndef FS_COMPS_OPS
#define FS_COMPS_OPS

#include "mlxfwops/lib/fw_ops.h"

class FsCompsException : public exception
{
public:
    FsCompsException(const string& exceptionMsg);
    virtual const char* what() const throw();
    virtual ~FsCompsException() throw(){};

private:
    string msg;
    FsCompsException();
};

class FsCompsOperations : public FwOperations
{
public:
    FsCompsOperations(FBase* ioAccess) : FwOperations(ioAccess) {}
    u_int8_t FwType() override { return FIT_COMPS; }
    bool FwInit() override { return true; }
    bool GetImageSize(u_int32_t* image_size) override;
    bool FwReadData(void* image, u_int32_t* image_size, bool verbose = false) override;
    virtual bool IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion);
    bool CheckFwVersion(ComponentFwVersion currentVersion, u_int8_t forceVersion);

    // Unsupported functionality
    bool FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool) override;
    bool FwVerify(VerifyCallBack verifyCallBackFunc,
                  bool isStripedImage = false,
                  bool showItoc = false,
                  bool ignoreDToc = false) override;
    bool SignForSecureBoot(const char*, const char*, const MlxSign::Signer&) override;
    bool FwReadRom(std::vector<u_int8_t>& romSect) override;
    bool FwBurnRom(FImage* romImg,
                   bool ignoreProdIdCheck = false,
                   bool ignoreDevidCheck = false,
                   ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwBurn(FwOperations* imageOps,
                u_int8_t forceVersion,
                ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams) override;
    bool FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc) override;
    bool FwSetGuids(sg_params_t& sgParam,
                    PrintCallBack callBackFunc = (PrintCallBack)NULL,
                    ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL) override;
    bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL) override;
    bool FwSetVSD(char* vsdStr,
                  ProgressCallBack progressFunc = (ProgressCallBack)NULL,
                  PrintCallBack printFunc = (PrintCallBack)NULL) override;
    bool FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc = (PrintCallBack)NULL) override;
    bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage = false) override;
    bool FwResetNvData() override;
    bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack)NULL) override;
    const char* FwGetResetRecommandationStr() override;
    bool FwCalcMD5(u_int8_t md5sum[16]) override;

    enum CompsFingerPrint
    {
        SyncE = 0xAA55
    };

private:
    bool Unsupported(const string& msg)
    {
        return errmsg("Comps operations - unsupported functionality: %s\n", msg.data());
    }
};

#endif /* FS_COMPS_OPS */
