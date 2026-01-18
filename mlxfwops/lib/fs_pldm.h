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

#ifndef FS_PLDM_OPS
#define FS_PLDM_OPS
#ifdef MFT_LEGACY_BUILD
#include "mlxfwops/lib/fw_ops.h"
#else
#include "fw_ops.h"
#endif
#include "pldmlib/pldm_pkg.h"
#include "pldmlib/pldm_utils.h"

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

class MLXFWOP_API FsPldmOperations : public FwOperations
{
public:
    FsPldmOperations(FBase* ioAccess) : FwOperations(ioAccess) {}
    virtual ~FsPldmOperations() {}
    u_int8_t FwType() override { return FIT_PLDM_1_0; }
    bool FwInit() override;
    bool LoadPldmPackage();
    bool GetImageSize(u_int32_t* image_size) override;
    bool FwReadData(void* image, u_int32_t* image_size, bool verbose = false) override;
    FwComponent::comps_ids_t ToCompId(string componentName);
    // Unsupported functionality
    bool FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool) override;
    bool FwVerify(VerifyCallBack verifyCallBackFunc,
                  bool isStripedImage = false,
                  bool showItoc = false,
                  bool ignoreDToc = false) override;
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
    bool GetPldmComponentData(string component, string psid, u_int8_t** buff, u_int32_t& buffSize);
    bool GetPldmDescriptor(string psid, u_int16_t type, u_int16_t& descriptor);
    string GetPldmVendorDefinedDescriptor(string psid, PldmRecordDescriptor::VendorDefinedType type);
    bool CreateFwOpsImage(u_int32_t* buff,
                          u_int32_t buffSize,
                          FwOperations** newImageOps,
                          u_int16_t swDevId,
                          bool isStripedImage);

private:
    string _pldmFile;
    PldmPkg _pkg;
    bool Unsupported(const string& msg)
    {
        return errmsg("Comps operations - unsupported functionality: %s\n", msg.data());
    }
};

#endif /* FS_PLDM_OPS */
