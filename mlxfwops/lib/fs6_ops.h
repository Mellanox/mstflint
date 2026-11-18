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

#pragma once

#include <functional>
#ifdef MFT_LEGACY_BUILD
#include "mlxfwops/lib/fw_ops.h"
#include "mlxfwops/lib/bch/csh_imp.h"
#else
#include "fw_ops.h"
#include "bch/csh_imp.h"
#endif

CshComponentID ToCshId(ComponentType compName);
PartitionType ToPartitionType(CshComponentID cshId);
string ToString(PartitionType type);

class Fs6Operations : public FwOperations
{
public:
    Fs6Operations(FBase* ioAccess);
    u_int8_t FwType() override { return FIT_FS6; }
    bool FwInit() override;
    bool GetImageSize(u_int32_t* image_size) override;
    bool FwReadData(void* image, u_int32_t* image_size, bool verbose = false) override;
    bool CheckFwVersion(ComponentFwVersion currentVersion, u_int8_t forceVersion);

    // Unsupported functionality
    bool FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool) override;
    bool FwVerify(VerifyCallBack verifyCallBackFunc,
                  bool isStripedImage = false,
                  bool showItoc = false,
                  bool ignoreDToc = false) override;

    bool ReadComponent(ComponentType compName,
                       ComponentHeader compHeader,
                       string file_path,
                       vector<u_int8_t>& componentData) override;
    bool SetSignedFWComponent(string binPath, ComponentType compName, const char* msg) override;
    bool GetFwComponentsData(string path) override;

#ifndef MST_CPU_armv7l_umbriel // {
    bool SignForSecureBoot(const char*, const char*, const MlxSign::Signer&) override;
#endif // } MST_CPU_armv7l_umbriel
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
    bool FwCalcMD5(u_int8_t md5sum[16]) override;
    const char* FwGetResetRecommandationStr() override;
    bool GetCshSectionOffset(PartitionType partitionType, CshSectionType sectionType, size_t& CshSectionOffset);
    bool GetPartrionEntryInfo(PartitionType partitionType, size_t& sectionOffset, size_t& sectionSize);
    bool ReadPartitionInfo(PartitionType partitionType, vector<u_int8_t>& data);
    bool ReadCshSectionInfo(PartitionType partitionType,
                            CshSectionType sectionType,
                            size_t sectionSize,
                            vector<u_int8_t>& data);

    virtual bool GetMfgInfo(u_int8_t* buff = nullptr) override;
    virtual bool GetDevInfo(u_int8_t* buff = nullptr) override;
    virtual bool GetImageInfo();

    class PartitionValidator
    {
    public:
        PartitionValidator() : _validator(&defaultValidator) {}

        explicit PartitionValidator(PartitionType partitionType);

        bool validate(const PartitionTableEntry& entry, FBase* ioAccess) const;

    private:
        std::function<bool(const PartitionTableEntry&, FBase*)> _validator;

        static bool defaultValidator(const PartitionTableEntry& entry, FBase* ioAccess)
        {
            return true;
        } // static because it's used as a function pointer

        static bool validateDevInfo(const PartitionTableEntry& entry, FBase* ioAccess);
    };

protected:
    bool Unsupported(const string& msg)
    {
        return errmsg("Comps operations - unsupported functionality: %s\n", msg.data());
    }

private:
    bool Init();
    bool InitCshComponent(PartitionType partitionType, u_int32_t offset);

    bool VerifyCshComponent(PartitionType partitionType, u_int32_t offset, VerifyCallBack verifyCallBackFunc);
    bool VerifyCshComponent();

    void UpdatePartitionTable(bool l1pt);
    bool IsL2ptSection(CshComponentID cshId);
    bool IsL2ptSection(PartitionType partitionType);

    void PrintDotSection(VerifyCallBack verifyCallBackFunc);
    void PrintSectionRange(VerifyCallBack verifyCallBackFunc,
                           u_int32_t startAddr,
                           u_int32_t endAddr,
                           u_int32_t size,
                           const string& sectionType,
                           const string& suffix = "");

    PartitionTable _l1pt;
    PartitionTable _l2pt;
    vector<pair<PartitionType, CSH>> _cshComponents;
    const u_int32_t _l1ptOffset;
    u_int32_t _l2ptOffset;
    u_int8_t _dotMagicId[4];
};
