/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#include "fw_ops.h"
#include "aux_tlv_ops.h"
#include "fw_comps_mgr/fw_comps_mgr.h"

class FsCtrlOperations : public FwOperations {
public:

    FsCtrlOperations(FwCompsMgr *fwComps) :
        FwOperations((FBase*)NULL), _fwCompsAccess(fwComps), _isSecured(false), _hwDevId(0)
    {
        memset(&_fsCtrlImgInfo, 0, sizeof(_fsCtrlImgInfo));
    }

    virtual ~FsCtrlOperations();

    virtual u_int8_t FwType();

    virtual bool FwQuery(fw_info_t *fwInfo, bool readRom = true, bool isStripedImage = false, bool quickQuery = true, bool ignoreDToc = false, bool verbose = false);
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage = false, bool showItoc = false,
                          bool ignoreDToc = false); // Add callback print
    virtual bool FwVerifyAdv(ExtVerifyParams &verifyParams);
    //on call of FwReadData with Null image we get image_size
    virtual bool FwReadData(void *image, u_int32_t *image_sizes, bool verbose = false);
    virtual bool FwReadBlock(u_int32_t addr, u_int32_t size, std::vector<u_int8_t> &dataVec);

    virtual bool FwReadRom(std::vector<u_int8_t> &romSect);
    virtual bool FwBurnRom(FImage *romImg, bool ignoreProdIdCheck = false, bool ignoreDevidCheck = false,
                           ProgressCallBack progressFunc = (ProgressCallBack) NULL); // can also read the rom from flint and give a vector of u_int8_t
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc = (ProgressCallBack) NULL);

    virtual bool FwBurn(FwOperations *imageOps, u_int8_t forceVersion,
                        ProgressCallBack progressFunc = (ProgressCallBack) NULL);
    virtual bool FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams &burnParams);
    virtual bool FwBurnAdvanced(std::vector <u_int8_t> imageOps4MData, ExtBurnParams& burnParams, FwComponent::comps_ids_t ComponentId = FwComponent::COMPID_BOOT_IMG);
    virtual bool FwBurnBlock(FwOperations *imageOps, ProgressCallBack progressFunc); //Add: callback progress, question arr, callback question, configurations
    bool FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec,
                      ProgressCallBack progressFunc = (ProgressCallBack) NULL);

    virtual bool FwSetGuids(sg_params_t &sgParam, PrintCallBack callBackFunc = (PrintCallBack) NULL,
                            ProgressCallBack progressFunc = (ProgressCallBack) NULL);

    virtual bool FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack) NULL);
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack) NULL);
    // use progressFunc when dealing with FS2 image and printFunc when dealing with FS3 image.
    virtual bool FwSetVSD(char *vsdStr, ProgressCallBack progressFunc = (ProgressCallBack) NULL,
                          PrintCallBack printFunc = (PrintCallBack) NULL);
    virtual bool FwSetVPD(char *vpdFileStr, PrintCallBack callBackFunc = (PrintCallBack) NULL);
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc = (ProgressCallBack) NULL);
    virtual bool FwGetSection(u_int32_t sectType, std::vector<u_int8_t> &sectInfo, bool stripedImage = false);
    virtual bool FwResetNvData();
    virtual bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack) NULL);
    virtual const char* FwGetResetRecommandationStr();

    virtual bool FwInit();
    virtual bool FwCalcMD5(u_int8_t md5sum[16]);
    virtual bool FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    virtual bool FwQueryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning = false);
    virtual bool FwResetTimeStamp();
    virtual u_int32_t GetHwDevId() { return _hwDevId; }
    bool FwReactivateImage();
    Tlv_Status_t GetTsObj(TimeStampIFC **tsObj);

    virtual bool IsFsCtrlOperations()
    {
        return true;
    }
    virtual mfile* getMfileObj() {
        return _fwCompsAccess->getMfileObj();
    }
    virtual bool GetSecureBootInfo();
protected:
    bool FsIntQuery();
    bool GetImageInfo(u_int8_t *buff);
    bool ReadBootImage(void *image, u_int32_t *image_size,
                       ProgressCallBackAdvSt *stProgressFunc = (ProgressCallBackAdvSt*)NULL);

    bool unsupportedOperation();
    int FwCompsErrToFwOpsErr(fw_comps_error_t err);
    virtual bool VerifyAllowedParams(ExtBurnParams &burnParams, bool isSecure);
    bool BadParamErrMsg(const char *unSupportedOperation, bool isSecure);
    bool _Burn(std::vector <u_int8_t> imageOps4MData, ExtBurnParams& burnParams, FwComponent::comps_ids_t ComponentId = FwComponent::COMPID_BOOT_IMG);
    fs3_info_t _fsCtrlImgInfo;
    FwCompsMgr *_fwCompsAccess;
    bool _isSecured;
    u_int32_t _hwDevId;
};

