/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef FW_OPS_H
#define FW_OPS_H

#include "flint_base.h"
#include "flint_io.h"
#include "aux_tlv_ops.h"
#include "mlxfwops_com.h"
#include "signature_manager_factory.h"
#include "fw_version.h"
#include "tools_layouts/cx4fw_layouts.h"
#include "tools_layouts/image_layout_layouts.h"
#include <mlxsign_lib/mlxsign_lib.h>
#include "mlxdpa/certcontainerbase.h"
#ifdef CABLES_SUPP
#include <cable_access/cable_access.h>
#endif
#include <fw_comps_mgr/fw_comps_mgr.h>
#include "mlxsign_lib/mlxsign_signer_interface.h"
#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif

typedef f_prog_func_str VerifyCallBack;
typedef f_prog_func ProgressCallBack;
typedef f_prog_func_ex ProgressCallBackEx;
typedef f_prog_func_adv_st ProgressCallBackAdvSt;
typedef f_prog_func_str PrintCallBack;
typedef fw_ver_info_t FwVerInfo;

typedef int (*PrintCallBackAdv)(int completion, char* str);
MLXFWOP_API extern bool nextBootFwVer;
#define GLOBAL_ALIGNMENT 0x80
#define UUID_LEN 16
#define BAD_CRC_MSG "Bad CRC."
class MLXFWOP_API FwOperations : public FlintErrMsg
{
public:
#define EXP_ROM_GEN_DEVID 0
#define MISS_MATCH_DEV_ID 0xffff
    class ExtBurnParams;
    class ExtVerifyParams;
    struct fwOpsParams;
    struct sgParams;
    typedef fwOpsParams fw_ops_params_t;
    typedef sgParams sg_params_t;
    // typedef std::tr1::function<void (void)> VerifyCallback;
    enum
    {
        IMG_SIG_TYPE_UNKNOWN = 0,
        IMG_SIG_TYPE_BIN = 1,
        IMG_SIG_TYPE_MFA = 2,
        IMG_SIG_TYPE_CF = 3,
        IMG_SIG_TYPE_CC = 4,
        IMG_SIG_TYPE_PLDM = 5,
        IMG_SIG_OPEN_FILE_FAILED = 6
    };
    FwOperations(FBase* ioAccess) :
        _ioAccess(ioAccess),
        _quickQuery(false),
        _printFunc((PrintCallBack)NULL),
        _fname((const char*)NULL),
        _devName((const char*)NULL),
        _advErrors(true),
        _minBinMinorVer(0),
        _minBinMajorVer(0),
        _maxBinMajorVer(0),
        _signatureMngr((ISignatureManager*)NULL),
        _internalQueryPerformed(false),
        _isReducedImage(false)
    {
        memset(_sectionsToRead, 0, sizeof(_sectionsToRead));
        memset(&_fwImgInfo, 0, sizeof(_fwImgInfo));
        memset(&_fwParams, 0, sizeof(_fwParams));
        memset(&_protect_info_backup, 0x0, sizeof(_protect_info_backup));
    };

    virtual ~FwOperations()
    {
        if (_ioAccess)
        {
            delete _ioAccess;
            _ioAccess = (FBase*)NULL;
        }
        if (_signatureMngr)
        {
            delete _signatureMngr;
        }
    };
    // virtual void print_type() {};
    virtual mfile* getMfileObj()
    {
        mfile* mf = _ioAccess->is_flash() ? ((Flash*)_ioAccess)->getMfileObj() : (mfile*)NULL;
        return mf;
    }
    virtual bool IsFifthGen() { return (_ioAccess != NULL && _ioAccess->is_flash() && _ioAccess->is_fifth_gen()); }
    FBase* GetIoAccess() { return _ioAccess; }
    virtual u_int8_t FwType() = 0;
    static bool IsFwSupportingRomModify(const FwVersion&);
    static void SetDevFlags(chip_type_t chipType, u_int32_t devType, fw_img_type_t fwType, bool& ibDev, bool& ethDev);
    static bool checkMatchingExpRomDevId(const fw_info_t& info);
    static bool checkMatchingExpRomDevId(u_int16_t dev_type, const roms_info_t& roms_info);
    static const char* expRomType2Str(u_int16_t type);
    static chip_type_t getChipType(u_int32_t devid);
    virtual bool FwQuery(fw_info_t* fwInfo,
                         bool readRom = true,
                         bool isStripedImage = false,
                         bool quickQuery = true,
                         bool ignoreDToc = false,
                         bool verbose = false) = 0;
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc,
                          bool isStripedImage = false,
                          bool showItoc = false,
                          bool ignoreDToc = false) = 0; // Add callback print
    virtual bool FwVerifyAdv(ExtVerifyParams& verifyParams);
    // on call of FwReadData with Null image we get image_size
    virtual bool FwReadData(void* image, u_int32_t* image_size, bool verbose = false) = 0;
    virtual bool FwReadBlock(u_int32_t addr, u_int32_t size, std::vector<u_int8_t>& dataVec);
    virtual u_int32_t GetPublicKeySecureBootPtr();
    virtual bool FwReactivateImage() { return errmsg("Operation not supported."); }
    virtual bool GetIsReducedImage() { return _isReducedImage; }
    virtual void SetIsReducedImage(bool isReducedImage) { _isReducedImage = isReducedImage; }
    virtual bool FwInsertSHA256(PrintCallBack printFunc = (PrintCallBack)NULL);
    virtual bool SignForFwUpdate(const char* uuid,
                                 const MlxSign::Signer& signer,
                                 MlxSign::SHAType shaType,
                                 PrintCallBack printFunc);
    virtual bool FwSignWithTwoRSAKeys(const char* privPemFile1,
                                      const char* uuid1,
                                      const char* privPemFile2,
                                      const char* uuid2,
                                      PrintCallBack printFunc = (PrintCallBack)NULL);
    virtual bool FwSignWithHmac(const char* key_file);
    virtual bool SignForSecureBoot(const char* public_key_file, const char* uuid, const MlxSign::Signer& signer);

    virtual bool FwExtract4MBImage(vector<u_int8_t>& img,
                                   bool maskMagicPatternAndDevToc,
                                   bool verbose = false,
                                   bool ignoreImageStart = false,
                                   bool imageSizeOnly = false);
    virtual bool RestoreDevToc(vector<u_int8_t>& img,
                               char* psid,
                               dm_dev_id_t devid_t,
                               const image_layout_uid_entry& base_guid,
                               const image_layout_uid_entry& base_mac);
    virtual bool openEncryptedImageAccess(const char* encrypted_image_path);
    virtual bool isEncrypted(bool& is_encrypted);
    virtual bool FwExtractEncryptedImage(vector<u_int8_t>& img,
                                         bool maskMagicPatternAndDevToc,
                                         bool verbose = false,
                                         bool ignoreImageStart = false);
    virtual bool burnEncryptedImage(FwOperations* imageOps, ExtBurnParams& burnParams);
    virtual bool FwSetPublicKeys(char* fname, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwSetForbiddenVersions(char* fname, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwReadRom(std::vector<u_int8_t>& romSect) = 0;
    virtual bool FwBurnRom(FImage* romImg,
                           bool ignoreProdIdCheck = false,
                           bool ignoreDevidCheck = false,
                           ProgressCallBack progressFunc = (ProgressCallBack)NULL) = 0; // can also read the rom from
                                                                                        // flint and give a vector of
                                                                                        // u_int8_t
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc = (ProgressCallBack)NULL) = 0;

    virtual bool
      FwBurn(FwOperations* imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc = (ProgressCallBack)NULL) = 0;
    virtual bool FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams) = 0;
    virtual bool FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams, FwComponent::comps_ids_t ComponentId);
    virtual bool
      getExtendedHWAravaPtrs(VerifyCallBack verifyCallBackFunc, FBase* ioAccess, bool IsBurningProcess, bool isVerify);
    virtual bool FwBurnAdvanced(std::vector<u_int8_t> imageOps4MData,
                                ExtBurnParams& burnParams,
                                FwComponent::comps_ids_t ComponentId = FwComponent::COMPID_BOOT_IMG);
    virtual bool FwBurnBlock(FwOperations* imageOps,
                             ProgressCallBack progressFunc) = 0; // Add: callback progress, question arr, callback
                                                                 // question, configurations
    virtual bool FwWriteBlock(u_int32_t addr,
                              std::vector<u_int8_t> dataVec,
                              ProgressCallBack progressFunc = (ProgressCallBack)NULL);

    virtual bool FwSetGuids(sg_params_t& sgParam,
                            PrintCallBack callBackFunc = (PrintCallBack)NULL,
                            ProgressCallBack progressFunc = (ProgressCallBack)NULL) = 0;
    virtual bool IsExtendedGuidNumSupported();

    virtual bool FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL) = 0;
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL) = 0;
    // use progressFunc when dealing with FS2 image and printFunc when dealing with FS3 image.
    virtual bool FwSetVSD(char* vsdStr,
                          ProgressCallBack progressFunc = (ProgressCallBack)NULL,
                          PrintCallBack printFunc = (PrintCallBack)NULL) = 0;
    virtual bool FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc = (PrintCallBack)NULL) = 0;
    virtual bool
      FwSetCertChain(char* certFileStr, u_int32_t certIndex, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc = (ProgressCallBack)NULL) = 0;
    virtual bool FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage = false) = 0;
    virtual bool FwResetNvData() = 0;
    virtual bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack)NULL) = 0;
    virtual const char* FwGetResetRecommandationStr() = 0;
    virtual const char* FwGetReSignMsgStr();

    virtual bool FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    virtual bool FwQueryTimeStamp(struct tools_open_ts_entry& timestamp,
                                  struct tools_open_fw_version& fwVer,
                                  bool queryRunning = false);
    virtual bool FwResetTimeStamp();

    virtual bool FwCheckIfWeCanBurnWithFwControl(FwOperations*) { return true; }
    virtual bool FwCheckIf8MBShiftingNeeded(FwOperations*, const ExtBurnParams&) { return false; }

    virtual bool CheckIfAlignmentIsNeeded(FwOperations*) { return false; }
    virtual bool RemoveWriteProtection()
    {
        return true;
        // Though Remove write protection is not supported, return true.
    }
    virtual void FwCleanUp();
    virtual bool FwInit() = 0;
    bool FwSetPrint(PrintCallBack PrintFunc);
    virtual bool CheckAndSetIsReducedImage();

    virtual bool UpdateSection(void* new_info,
                               fs3_section_t sect_type = FS3_DEV_INFO,
                               bool is_sect_failsafe = true,
                               CommandType cmd_type = CMD_UNKNOWN,
                               PrintCallBack callBackFunc = (PrintCallBack)NULL);
    // needed for flint low level operations
    bool FwSwReset();
    virtual bool FwCalcMD5(u_int8_t md5sum[16]) = 0;
    static FwOperations* FwOperationsCreate(void* fwHndl,
                                            void* info,
                                            char* psid,
                                            fw_hndl_type_t hndlType,
                                            char* errBuff = (char*)NULL,
                                            int buffSize = 0,
                                            bool ignore_crc_check = false);
    static FwOperations* FwOperationsCreate(fw_ops_params_t& fwParams);
    static bool IsDeviceSupported(fw_ops_params_t& fwParams);

    static bool imageDevOperationsCreate(fw_ops_params_t& devParams,
                                         fw_ops_params_t& imgParams,
                                         FwOperations** devFwOps,
                                         FwOperations** imgFwOps,
                                         bool ignoreSecurityAttributes = false,
                                         bool ignoreDToc = false);

    virtual bool IsFsCtrlOperations() { return false; }
    virtual bool PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical);
    virtual bool IsSecureBootSupported();
    virtual bool IsCableQuerySupported();
    virtual bool IsLifeCycleSupported();
    virtual bool IsEncryptionSupported();
    
    bool checkAndDisableFlashWpIfRequired(); // relavant to FS5 and FS6 but FS6 inherites FwOperations and not FS5
    bool restoreWriteProtectInfo();
    
    void GetFwParams(fw_ops_params_t&);
    void getSupporteHwId(u_int32_t** supportedHwId, u_int32_t& supportedHwIdNum);

    static FwVersion createFwVersion(const fw_info_com_t*);
    static FwVersion createFwVersion(u_int16_t fw_ver0, u_int16_t fw_ver1, u_int16_t fw_ver2);
    static FwVersion createRunningFwVersion(const fw_info_com_t*);
    static int getFileSignature(const char* fname);
    virtual bool IsLifeCycleAccessible(chip_type_t chip_type);
    virtual bool IsSecurityVersionViolated(u_int32_t image_security_version);
    virtual bool GetImageSize(u_int32_t* image_size);
    virtual bool GetHashesTableData(vector<u_int8_t>& data);
    virtual bool PrintQuery();
    virtual u_int32_t GetDeviceIndex() { return 0; }
    virtual bool QueryComponentData(FwComponent::comps_ids_t comp, u_int32_t deviceIndex, vector<u_int8_t>& data);
	virtual bool IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion);
    virtual bool GetRSAPublicKey(vector<u_int8_t>& key);
    virtual bool ReadMccComponent(vector<u_int8_t>& componentRawData,
                                  FwComponent::comps_ids_t component,
                                  ProgressCallBackAdvSt* stProgressFunc = NULL);
    virtual bool GetNcoreData(vector<u_int8_t>& ncoreData);
    virtual bool GetSecureHostState(u_int8_t& state);
    virtual bool ChangeSecureHostState(bool disable, u_int64_t key);
    virtual bool IsComponentSupported(FwComponent::comps_ids_t component);
    virtual bool getBFBComponentsVersions(std::map<std::string, std::string>& name_to_version, bool pending);
    
#ifndef UEFI_BUILD
    static bool CheckPemKeySize(const string privPemFileStr, u_int32_t& keySize);
#endif
    class MLXFWOP_API RomInfo : FlintErrMsg
    {
    public:
        RomInfo(const std::vector<u_int8_t>& romSector, bool resEndi = true);
        ~RomInfo(){};
        bool initRomsInfo(roms_info_t* info);
        bool ParseInfo();
        static u_int8_t getNumVerFromProdId(u_int16_t prodId);

    private:
        // Rom Information
        bool expRomFound;
        u_int8_t numOfExpRom;
        u_int8_t noRomChecksum;
        u_int16_t expRomComDevid;
        u_int8_t expRomWarning;
        char expRomWarningMsg[MAX_ROM_ERR_MSG_LEN];
        u_int8_t expRomErrMsgValid;
        char expRomErrMsg[MAX_ROM_ERR_MSG_LEN];
        rom_info_t romsInfo[MAX_ROMS_NUM];
        std::vector<u_int8_t> romSect;

        bool GetExpRomVerForOneRom(u_int32_t verOffset);
        bool GetExpRomVersion();
    };

    class ExtBurnStatus
    {
    public:
        bool imageCachedSuccessfully;
        ExtBurnStatus() : imageCachedSuccessfully(false) {}
    };
    class ExtBurnParams
    {
    public:
        typedef enum BurnRomOption
        {
            BRO_DEFAULT,
            BRO_ONLY_FROM_IMG,
            BRO_FROM_DEV_IF_EXIST,
        } BurnRomOption;
        // burn params
        bool userGuidsSpecified;
        bool userMacsSpecified;
        bool userUidSpecified;
        bool vsdSpecified;
        bool blankGuids;
        bool burnFailsafe;
        bool allowPsidChange;
        bool useImagePs;
        bool useImageGuids;
        bool singleImageBurn;
        bool noDevidCheck;
        bool skipCiReq; // FS2 image only - skip sending cache image request to driver at the end of the burn
        bool ignoreVersionCheck;
        bool useImgDevData; // FS3 image only - take device data sections from image (valid only if burnFailsafe==
                            // false)
        bool useDevImgInfo; // FS3 image only - preserve select fields of image_info section on the device when burning.
        BurnRomOption burnRomOptions;
        bool shift8MBIfNeeded;

        // callback fun
        ProgressCallBack progressFunc;
        ProgressCallBackAdvSt ProgressFuncAdv;
        ProgressCallBackEx progressFuncEx;
        void* progressUserData;
        // data
        char* userVsd;
        bool use_cpu_utilization;
        int cpu_utilization;
        std::vector<guid_t> userUids; // contains either guids or uids
        ExtBurnStatus burnStatus;
        chip_type_t chip_type;
        bool use_chip_type;
        ExtBurnParams() :
            userGuidsSpecified(false),
            userMacsSpecified(false),
            userUidSpecified(false),
            vsdSpecified(false),
            blankGuids(false),
            burnFailsafe(true),
            allowPsidChange(false),
            useImagePs(false),
            useImageGuids(false),
            singleImageBurn(true),
            noDevidCheck(false),
            skipCiReq(false),
            ignoreVersionCheck(false),
            useImgDevData(false),
            useDevImgInfo(false),
            burnRomOptions(BRO_DEFAULT),
            shift8MBIfNeeded(false),
            progressFunc((ProgressCallBack)NULL),
            progressFuncEx((ProgressCallBackEx)NULL),
            progressUserData(NULL),
            userVsd((char*)NULL),
            use_cpu_utilization(false),
            cpu_utilization(-1),
            chip_type(CT_UNKNOWN),
            use_chip_type(false)
        {
            ProgressFuncAdv.func = (f_prog_func_adv)NULL;
            ProgressFuncAdv.opaque = NULL;
        }

        void updateParamsForBasicImage(ProgressCallBack progressFunc)
        {
            ignoreVersionCheck = true;
            this->progressFunc = progressFunc;
            useImagePs = true;
            useImageGuids = true;
            burnRomOptions = ExtBurnParams::BRO_ONLY_FROM_IMG;
        }
    };

    class ExtVerifyParams
    {
    public:
        VerifyCallBack verifyCallBackFunc; // Print function call back for print the different sections in the verify
        bool isStripedImage;               // If the image is striped
        bool showItoc;                     // Show the ITOC header only
        bool ignoreDToc;                   // Ignore verifying DTOC sections
        ProgressCallBackAdvSt* progressFuncAdv; // Advance progress function that used in FW controlled operations (e.g.
                                                // under secure fw)

        ExtVerifyParams(VerifyCallBack vFunc) :
            verifyCallBackFunc(vFunc),
            isStripedImage(false),
            showItoc(false),
            ignoreDToc(false),
            progressFuncAdv((ProgressCallBackAdvSt*)NULL){};
    };

    struct fwOpsParams
    {
        // COMMON
        char* psid; // can be NULL
        fw_hndl_type_t hndlType;
        char* errBuff;   // can be NULL
        int errBuffSize; // can be zero if above NULL
        // FHT_FW_FILE
        char* fileHndl;
        // FHT_FW_BUFF
        u_int32_t* buffHndl;
        u_int32_t buffSize;
        // FHT_UEFI_DEV
        uefi_Dev_t* uefiHndl;
        uefi_dev_extra_t uefiExtra;
        // FHT_MST_DEV
        char* mstHndl;
        bool forceLock;
        bool readOnly;
        int numOfBanks;              // should be set to -1 for "auto-detect"
        flash_params_t* flashParams; // can be NULL
        int ignoreCacheRep;
        bool noFlashVerify;
        bool shortErrors; // show short/long error msgs (default shuold be false)
        int cx3FwAccess;
        int isCableFw;
        bool noFwCtrl;
        bool mccUnsupported;
        bool canSkipFwCtrl;
        bool ignoreCrcCheck;
        u_int32_t deviceIndex;
        u_int16_t swDevId;
    };

    struct sgParams
    {
        bool updateCrc;    // default should be set to true
        bool stripedImage; // default shuold be set to false unless working on striped image file
        bool macsSpecified;
        bool guidsSpecified;
        bool uidSpecified; // valid for ConnectIB only
        std::vector<guid_t> userGuids;
        u_int8_t numOfGUIDs;       // number of GUIDs to allocate for each port. keep zero for default. (FS3 image Only)
        u_int8_t stepSize;         // step size between GUIDs. keep zero for default. (FS3 Image Only)
        bool usePPAttr;            // if set, use the per prot attributes below (FS3 Image Only)
        u_int16_t numOfGUIDsPP[2]; // number of GUIDs to allocate for each port. keep 0xff for default. (FS3 image Only)
        u_int8_t stepSizePP[2];    // step size between GUIDs. keep 0xffff for default. (FS3 Image Only)
    };

protected:
#define FS3_BOOT_VERSION_OFFSET 0x24
#define FS4_BOOT_VERSION_OFFSET 0x10
#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

    struct FwImgInfo
    {
        fw_info_com_t ext_info;
        u_int32_t imgStart;
        bool actuallyFailsafe;
        u_int32_t cntxLog2ChunkSize;
        u_int32_t boot2Size;
        bool isGa;
        u_int32_t supportedHwId[MAX_NUM_SUPP_HW_IDS];
        int supportedHwIdNum;
        bool magicPatternFound;
        bool imageOk;
        bool wasQueried;
        u_int32_t lastImageAddr;
        fw_img_type_t fwType;
    };
    enum
    {
        OLD_CNTX_START_POS_SIZE = 6,
        CNTX_START_POS_SIZE = 11
    };
    enum
    {
        MAX_SW_DEVICES_PER_HW = 32
    };

    enum
    {
        IMG_VER_FS2 = 0,
        IMG_VER_FS3 = 3,
        IMG_VER_FS4 = 1,
        IMG_VER_FS5 = 2
    };
    enum
    {
        FS_OLD_GEN = 0,
        FS_FS2_GEN,
        FS_FS3_GEN,
        FS_FS4_GEN,
        FS_FC1_GEN,
        FS_FSCTRL_GEN,
        FS_LINKX_GEN,
        FS_FS5_GEN,
        FS_FS6_GEN,
        FS_COMPS_GEN,
        FS_PLDM_1_0,
        FS_UNKNOWN_IMG
    };

    struct BinId2SwId
    {
        BinIdT binId;
        // Zero terminated list of SW device ids
        u_int32_t swId[MAX_SW_DEVICES_PER_HW];
    };

    struct HwDevData
    {
        const char* name;
        u_int32_t hwDevId;
        chip_type_t chipType;
        chip_family_type chipFamilyType;
        int portNum;
        // Zero terminated list of SW device ids
        const u_int32_t swDevIds[MAX_SW_DEVICES_PER_HW];
        // -1 terminated list of the bins of the device that match every SW ID
        const BinId2SwId binningId[MAX_SW_DEVICES_PER_HW];
    };

    struct HwDev2Str
    {
        const char* name;
        u_int32_t hwDevId;
        u_int8_t revId;
    };

    struct SectionInfo
    {
        u_int8_t type;
        const char* name;
    };

    struct QueryOptions
    {
        bool quickQuery;
        bool readRom;
    };

    class burnDataParamsT
    {
    public:
        u_int32_t* data;
        u_int32_t dataSize;
        ProgressCallBack progressFunc;
        bool calcSha;

        burnDataParamsT() : data((u_int32_t*)NULL), dataSize(0), progressFunc((ProgressCallBack)NULL), calcSha(false){};
    };

    typedef int (*print2log_func)(const char* format, ...);

    // Protected Methods
    virtual u_int32_t GetHwDevId()
    {
        mfile* mf = _ioAccess->getMfileObj();
        dm_dev_id_t deviceId = DeviceUnknown;
        u_int32_t hwDevId = 0x0, hwRevId = 0x0;
        if (dm_get_device_id(mf, &deviceId, &hwDevId, &hwRevId))
        {
            return 0xffff;
        }
        return hwDevId;
    }
    virtual bool AlignDeviceSections(FwOperations* /*imageOps*/)
    {
        return errmsg("Align device sections is not supported");
    }
    bool CreateBasicImageFromData(u_int32_t* data,
                                  u_int32_t dataSize,
                                  FwOperations** newImgOps,
                                  u_int16_t swDevId = 0,
                                  bool isStripedImage = false);
    virtual bool
      storeSecureBootSignaturesInSection(vector<u_int8_t> boot_signature,
                                         vector<u_int8_t> critical_sections_signature = vector<u_int8_t>(),
                                         vector<u_int8_t> non_critical_sections_signature = vector<u_int8_t>());
    bool readBufAux(FBase& f, u_int32_t o, void* d, int l, const char* p);
    static int GetFwVerFormat(u_int16_t fwVer[3]);
    virtual bool UpdateImgCache(u_int8_t* buff, u_int32_t addr, u_int32_t size);
    bool CheckAndPrintCrcRes(char* pr,
                             bool blank_crc,
                             u_int32_t off,
                             u_int32_t crc_act,
                             u_int32_t crc_exp,
                             bool ignore_crc = false,
                             VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    virtual bool CheckBoot2(u_int32_t beg,
                            u_int32_t offs,
                            u_int32_t& next,
                            bool fullRead,
                            const char* pref,
                            VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    u_int32_t CalcImageCRC(u_int32_t* buff, u_int32_t size);
    bool writeImage(ProgressCallBack progressFunc,
                    u_int32_t addr,
                    void* data,
                    int cnt,
                    bool isPhysAddr = false,
                    bool readModifyWrite = false,
                    int totalSz = -1,
                    int alreadyWrittenSz = 0);
    bool writeImageEx(ProgressCallBackEx progressFuncEx,
                      void* progressUserData,
                      ProgressCallBack progressFunc,
                      u_int32_t addr,
                      void* data,
                      int cnt,
                      bool isPhysAddr = false,
                      bool readModifyWrite = false,
                      int totalSz = -1,
                      int alreadyWrittenSz = 0,
                      bool cpuUtilization = false,
                      int cpuPercent = -1);
    //////////////////////////////////////////////////////////////////
    bool GetSectData(std::vector<u_int8_t>& file_sect, const u_int32_t* buff, const u_int32_t size);
    ////////////////////////////////////////////////////////////////////
    bool CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId);
    bool CheckMatchingHwDevId(u_int32_t hwDevId, u_int32_t rev_id, u_int32_t* supportedHwId, u_int32_t supportedHwIdNum);
    bool CheckMatchingBinning(u_int32_t hwDevId, BinIdT binningVal, u_int32_t imageDevId);
    bool HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char* hw_name);
    bool CheckMac(u_int64_t mac);
    bool CheckMac(guid_t mac);
    void recalcSectionCrc(u_int8_t* buf, u_int32_t data_size);
    void FwInitCom();
    void FwDebugPrint(char* str);

    static bool FindAllImageStart(FBase* ioAccess,
                                  u_int32_t start_locations[CNTX_START_POS_SIZE],
                                  u_int32_t* found_images,
                                  u_int32_t const cntx_magic_pattern[]);
    static bool getRomsInfo(FBase* io, roms_info_t& romsInfo);

    bool GetQuickQuery() { return _quickQuery; }
    bool CheckFwVersion(FwOperations& imgFwOps, u_int8_t forceVersion);
    bool CheckPSID(FwOperations& imageOps, u_int8_t allow_psid_change = false);
    chip_type_t getChipType();
    bool getInfoFromHwDevid(u_int32_t hwDevId, chip_type_t& chipT, const u_int32_t** swIds);
    HwDevData getInfoFromChipType(chip_type_t chipT) const;

    bool ReadBinFile(const char* fimage, u_int8_t*& file_data, int& file_size);
    bool FwBurnData(u_int32_t* data, u_int32_t dataSize, ProgressCallBack progressFunc);
    bool FwBurnData(burnDataParamsT& burnDataParams);
    static bool FwAccessCreate(fw_ops_params_t& fwParams, FBase** ioAccessP, u_int16_t swDevId = 0);
    bool CheckBinVersion(u_int8_t binVerMajor, u_int8_t binVerMinor);

    static u_int8_t GetFwFormatFromHwDevID(u_int32_t hwDevId);

    virtual Tlv_Status_t GetTsObj(TimeStampIFC** tsObj);
    bool TestAndSetTimeStamp(FwOperations* imageOps);
    virtual bool VerifyBranchFormat(const char* vsdString);
    virtual bool GetDtocAddress(u_int32_t& dTocAddress);

    // Protected Members
    FBase* _ioAccess;
    FwImgInfo _fwImgInfo;
    fw_ops_params_t _fwParams;
    std::vector<u_int8_t> _romSect;
    std::vector<u_int8_t> _fwConfSect;
    std::vector<u_int8_t> _hashFileSect;
    std::vector<u_int8_t> _readSectList;
    bool _sectionsToRead[H_LAST];
    bool _quickQuery;

    PrintCallBack _printFunc;
    const char* _fname;
    const char* _devName;
    // show advanced error msgs
    bool _advErrors;

    u_int8_t _minBinMinorVer;
    u_int8_t _minBinMajorVer;
    u_int8_t _maxBinMajorVer;
    ISignatureManager* _signatureMngr;
    bool _internalQueryPerformed;
    bool _isReducedImage;

private:
    // Static Methods
#ifndef NO_MFA_SUPPORT
    static int getMfaImgInner(char* fileName,
                              u_int8_t* mfa_buf,
                              int size,
                              char* psid,
                              u_int8_t** imgbuf,
                              char* errBuf,
                              int errBufSize);
    static int getMfaImg(char* fileName, char* psid, u_int8_t** imgbuf, char* errBuf, int errBufSize);
    static int getMfaImg(u_int8_t* mfa_buf, int size, char* psid, u_int8_t** imgbuf, char* errMsg, int errBufSize);
#endif

    static int getBufferSignature(u_int8_t* buf, u_int32_t size);
    static u_int8_t CheckFwFormat(FBase& f, bool getFwFormatFromImg = false, u_int16_t swDevId = 0);
    static bool GetImageFormatVersion(FBase& f, u_int32_t boot_version_offset, u_int8_t& image_format_version);
    static u_int8_t IsPLDM(FBase& f);
    static u_int8_t IsFS4OrFS5Image(FBase& f, u_int32_t* found_images);
    static u_int8_t IsFS3OrFS2Image(FBase& f, u_int32_t* found_images);
    static u_int8_t IsCableImage(FBase& f);
    static u_int8_t IsFSCompsImage(FBase& f);
    static bool FindMagicPattern(FBase* ioAccess, u_int32_t addr, u_int32_t const cntx_magic_pattern[]);
    static bool CntxEthOnly(u_int32_t devid);

    /* Name:        WriteToErrBuff
     * Description: Write a string into buffer.
     *              if buffer is null or smaller than string size,
     *              write "..." as at the end of the string.
     * @param[in] errBuff - pointer to dist error buffer
     * @param[in] errStr - pointer to source string
     * @param[in] bufSize - size of error buffer */
    static void WriteToErrBuff(char* errBuff, char* errStr, int bufSize);

    // Methods
    void BackUpFwParams(fw_ops_params_t& fwParams);
    bool CreateSignatureManager();

    // Static Members
    static const u_int32_t _cntx_image_start_pos[CNTX_START_POS_SIZE];

    // Members
    static const HwDevData hwDevData[];
    static const HwDev2Str hwDev2Str[];
    // fw_hndl_type_t _hndlType;  //not used atm

protected:
    static const u_int32_t _cntx_magic_pattern[4];
    static const u_int32_t _fs4_magic_pattern[4];
    write_protect_info_backup_t _protect_info_backup;
};

class MLXFWOP_API CRSpaceRegisters
{
public:
    CRSpaceRegisters(mfile* mf, chip_type_t chip_type);

    int getGlobalImageStatus();
    life_cycle_t getLifeCycle();
    u_int32_t getSecurityVersion();
    bool IsLifeCycleSecured();
    static bool IsLifeCycleSecured(life_cycle_t life_cycle);

private:
    mfile* _mf;
    chip_type_t _chip_type;
    u_int32_t countSetBits(u_int32_t num);
    u_int32_t getConsecutiveBits(u_int32_t dword, u_int8_t firstBit, u_int8_t numOfBits);
    u_int32_t getRegister(u_int32_t address);
};

#endif // FW_ACCESS_H
