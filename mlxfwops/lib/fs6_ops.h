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
    bool FwQuery(fw_info_t* fwInfo,
                 bool readRom = false,
                 bool isStripedImage = false,
                 bool quickQuery = true,
                 bool ignoreDToc = false,
                 bool verbose = false) override;
    bool FwVerify(VerifyCallBack verifyCallBackFunc,
                  bool isStripedImage = false,
                  bool showItoc = false,
                  bool ignoreDToc = false) override;

    void PrintNonActiveChainSection(VerifyCallBack verifyCallBackFunc,
                                    const PartitionTableEntry& entry,
                                    const string& partitionType);

    bool ReadComponent(string compName,
                       ComponentHeader compHeader,
                       string file_path,
                       vector<u_int8_t>& componentData) override;
    bool ReadComponentSection(string compName,
                              string sectionName,
                              ComponentHeader compHeader,
                              vector<u_int8_t>& sectionData) override;
    bool SetSignedFWComponent(string binPath, ComponentType compName, const char* msg) override;
    bool GetFwComponentsData(string path) override;
    void PrintSectionRange(VerifyCallBack verifyCallBackFunc,
                           u_int32_t startAddr,
                           u_int32_t endAddr,
                           u_int32_t size,
                           const string& sectionType,
                           const string& suffix = "") override;
    void PrintPartitionTable(VerifyCallBack verifyCallBackFunc,
                             const PartitionTable& partitionTable,
                             size_t ptOffset,
                             const string& tablePrefix);
    bool PrintCrcInfoLayout(VerifyCallBack verifyCallBackFunc, const PartitionTableEntry& entry, bool showitoc = true);

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
    bool UpdateSection(fs3_section_t sectionType,
                       std::vector<u_int8_t>& newSectionData,
                       const char* msg,
                       PrintCallBack callBackFunc = (PrintCallBack)NULL) override;
    bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc = (ProgressCallBack)NULL) override;
    bool FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage = false) override;
    bool FwResetNvData() override;
    bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack)NULL) override;
    bool FwCalcMD5(u_int8_t md5sum[16]) override;
    const char* FwGetResetRecommandationStr() override;
    bool GetCshSectionOffset(PartitionType partitionType,
                             CshSectionType sectionType,
                             size_t& CshSectionOffset,
                             bool reportError,
                             int chainNumber = INVALID_CHAIN_NUMBER);
    bool ReadCshSectionInfo(PartitionType partitionType,
                            CshSectionType sectionType,
                            size_t sectionSize,
                            vector<u_int8_t>& data,
                            int chainNumber = INVALID_CHAIN_NUMBER);
    bool CheckAndSetIsReducedImage() override;

    virtual bool GetMfgInfo(u_int8_t* buff = nullptr) override;
    virtual bool GetDevInfo(u_int8_t* buff = nullptr) override;
    virtual bool IsSecureBootSupported() override;
    virtual bool IsLifeCycleAccessible(chip_type_t) override;
    bool UpdateLCAndGISIfAccessible();
    virtual bool GetNvPubKeyIdx();
    bool IsComponentFormatWithKeyId() override;
    bool GetImageInfoData(vector<u_int8_t>& data);
    virtual bool FwExtract4MBImage(vector<u_int8_t>& img,
                                   bool maskMagicPatternAndDevToc,
                                   bool verbose = false,
                                   bool ignoreImageStart = false,
                                   bool imageSizeOnly = false) override;

    bool isEncrypted(bool& is_encrypted) override;
    string GetL1ptEntryName(PartitionType partType, bool isCshComponent);
    bool ExecuteBurn(FwOperations* imageOps, ExtBurnParams& burnParams);
    bool ExecuteVmodBurn(FwOperations* imageOps, ExtBurnParams& burnParams);
    bool DoBeforeBurnJobs();
    bool DoAfterBurnJobs();
    bool PreBurnChecks(FwOperations* imageOps, ExtBurnParams& burnParams);
    int GetDestChainNumber(bool failSafe);

    static bool ParseFs6ImageInfo(struct fs6_image_layout_image_info& image_info,
                                  FwImgInfo& fwImgInfo,
                                  FsCommonInfo& fsCommonInfo);
    bool LoadImageInfo();

    class PartitionValidator
    {
    public:
        PartitionValidator() : _validator(&defaultValidator) {}

        explicit PartitionValidator(PartitionType partitionType);

        bool validate(const PartitionTableEntry& entry, FBase* ioAccess, int activeChain) const;

    private:
        std::function<bool(const PartitionTableEntry&, FBase*, int)> _validator;

        static bool defaultValidator(const PartitionTableEntry& entry, FBase* ioAccess, int activeChain)
        {
            return true;
        } // static because it's used as a function pointer

        static bool validateDevInfo(const PartitionTableEntry& entry, FBase* ioAccess, int activeChain);
        static bool validateRomImgsAndChainContainer(const PartitionTableEntry& entry, FBase* ioAccess, int activeChain);
    };

protected:
    string GetSectionNameByMagicId(u_int32_t magicId);

    bool Unsupported(const string& msg)
    {
        return errmsg("Comps operations - unsupported functionality: %s\n", msg.data());
    }

    // Structure to hold burn region info
    struct BurnRegion
    {
        size_t src_offset;
        size_t dest_offset;
        size_t size;
        std::string name;
        PartitionType partitionType;
    };

    std::map<PartitionType, std::vector<BurnRegion>>
      GetBurnRegions(FwOperations* imageOps, bool useImgDevData, bool failSafe);
    bool HandleRomImgsMagicPatternsPostBurn(ExtBurnParams& burnParams, uint32_t& alreadyWrittenSize, uint32_t totalSize);
    uint32_t GetTotalBurnSize(map<PartitionType, vector<BurnRegion>>& partitionTypeToBurnRegions);
    void addBurnRegion(u_int32_t srcOffset,
                       u_int32_t destOffset,
                       u_int32_t size,
                       const std::string& name,
                       PartitionType pt,
                       map<PartitionType, vector<BurnRegion>>& partitionMap,
                       vector<BurnRegion>& allRegions);
    bool WriteImageExDefaultParams(const ExtBurnParams& burnParams,
                                   u_int32_t addr,
                                   void* data,
                                   int cnt,
                                   int totalSz = -1,
                                   int alreadyWrittenSz = 0);

    enum class L1ptInstance
    {
        First,
        Second
    };
    bool ProcessL1pt(const vector<PartitionTableEntry>& l1Entries,
                     Fs6Operations* fs6ImageOps,
                     L1ptInstance instance,
                     map<PartitionType, vector<BurnRegion>>& partitionTypeToBurnRegions,
                     vector<BurnRegion>& allBurnRegions,
                     bool collectDtocs = false);

    bool IsValidCshSection(FwOperations* imageOps, PartitionType partitionType);
    void PrintSectionMetadata(const BinarySectionMetadata& section, VerifyCallBack verifyCallBackFunc);

private:
    bool Init();
    bool InitL2pt();
    bool InitL3pt();
    bool InitL3PartitionTable(PartitionTable& pt, size_t& ptOffset, CshSectionType sectionMagic);

    bool InitCshComponent(PartitionTableEntry& entry);

    bool VerifyCshComponent(const PartitionTableEntry& entry, bool showItoc, VerifyCallBack verifyCallBackFunc);
    bool VerifyCshComponent();

    void UpdatePartitionTable(bool isL2pt, PrintCallBack callBackFunc = nullptr);
    bool CheckSecondL1ptExists();
    bool VerifyL1ptConsistency();
    void CopyMagicPattern(size_t componentOffset, vector<u_int8_t>& compData);
    bool IsL2ptSection(CshComponentID cshId);
    bool IsL2ptSection(PartitionType partitionType);
    bool IsDtocEntry(PartitionType partitionType);
    bool IsSectionExists(fs3_section_t sectionType);
    void CollectDtocForProductionBurn(const PartitionTableEntry& entry,
                                      const std::string& ptEntryName,
                                      map<PartitionType, vector<BurnRegion>>& partitionTypeToBurnRegions,
                                      vector<BurnRegion>& allBurnRegions);
    vector<u_int8_t> ReadPartitionData(PartitionType partitionType, int chainNumber = INVALID_CHAIN_NUMBER);
    void UpdatePartitionData(PartitionType partitionType,
                             const vector<u_int8_t>& data,
                             PrintCallBack callBackFunc,
                             int chainNumber = INVALID_CHAIN_NUMBER);
    bool UpdateCrcInfoForPartition(PartitionType partitionType, const std::vector<u_int8_t>& sectionData);

    size_t GetPartitionOffset(PartitionType partitionType, int chainNumber = INVALID_CHAIN_NUMBER);
    void GetPartitionEntryInfo(PartitionType partitionType,
                               size_t& sectionOffset,
                               size_t& sectionSize,
                               int chainNumber = INVALID_CHAIN_NUMBER);
    PartitionTableEntry GetPartitionTableEntry(PartitionType partitionType, int chainNumber = INVALID_CHAIN_NUMBER);
    FwVersion::fw_version_raw GetCshComponentVersion(PartitionType partitionType);
    bool HasCshComponent(PartitionType partitionType) const;

    image_layout_guids ToImageLayoutGuids(const struct fs6_image_layout_guids& fs6Guids);
    fs6_image_layout_guids ToFs6MfgInfoGuids(const struct image_layout_guids& guids);

    void PrintDotSection(VerifyCallBack verifyCallBackFunc);

    u_int32_t GetL2ptSectionsSize();
    bool UpdateSectionAllowed(fs3_section_t sectionType);
    size_t GetChainContainerMaxSize();
    size_t GetChainContainerActualSize();
    bool Is32MBLayout();

    PartitionTable _l1pt;
    PartitionTable _l2pt;
    PartitionTable _l3pw;
    PartitionTable _l3pr;

    struct CshComponentInfo
    {
        PartitionType partitionType;
        std::shared_ptr<CSH> csh;
        int chainNumber;
    };
    vector<CshComponentInfo> _cshComponents;

    const CshComponentInfo* FindCshComponent(PartitionType partitionType) const;
    bool GetSecurityVersion();

    const u_int32_t _l1ptOffset;
    u_int32_t _l2ptOffset;
    size_t _l3pwOffset;
    size_t _l3prOffset;
    size_t _WPAreaPtr;
    size_t _RWAreaPtr;
    u_int8_t _dotMagicId[4];
    int _activeChain;
    int _backupChain;
    u_int8_t _vmodAdmStatusA;
    u_int8_t _vmodAdmStatusB;
    bool _secondL1ptExists;
};
