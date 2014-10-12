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


#ifndef FW_OPS_H
#define FW_OPS_H

#include "flint_base.h"
#include "flint_io.h"
#include "mlxfwops_com.h"

typedef f_prog_func_str VerifyCallBack;
typedef f_prog_func     ProgressCallBack;
typedef f_prog_func_str PrintCallBack;

typedef int (*PrintCallBackAdv) (int completion, char* str);

class MLXFWOP_API FwOperations : public ErrMsg {


public:
    #define EXP_ROM_GEN_DEVID 0
    #define MISS_MATCH_DEV_ID 0xffff
    class ExtBurnParams;
    struct fwOpsParams;
    struct sgParams;
    typedef fwOpsParams fw_ops_params_t;
    typedef sgParams sg_params_t;
    // typedef std::tr1::function<void (void)> VerifyCallback;

    FwOperations(FBase *ioAccess) :
        _ioAccess(ioAccess), _isCached(false), _wasVerified(false),
        _quickQuery(false), _printFunc((PrintCallBack)NULL), _fname(NULL), _devName(NULL), _advErrors(true)
    {
        memset(_sectionsToRead, 0, sizeof(_sectionsToRead));
        memset(&_fwImgInfo, 0, sizeof(_fwImgInfo));
    };


    virtual ~FwOperations()  {};
    //virtual void print_type() {};
    virtual u_int8_t FwType() = 0;
    static bool FwVerLessThan(u_int16_t r1[3], u_int16_t r2[3]);
    static bool IsFwSupportingRomModify(u_int16_t fw_ver[3]);
    static bool CntxEthOnly(u_int32_t devid);
    static void SetDevFlags(chip_type_t chipType, u_int32_t devType, fw_img_type_t fwType, bool &ibDev, bool &ethDev);
    static bool checkMatchingExpRomDevId(const fw_info_t& info);
    static bool checkMatchingExpRomDevId(u_int16_t dev_type, roms_info_t roms_info);
    static const char* expRomType2Str(u_int16_t type);


    virtual bool FwQuery(fw_info_t *fwInfo, bool readRom = true, bool isStripedImage = false) = 0;
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage = false, bool showItoc = false) = 0; // Add callback print
    //on call of FwReadData with Null image we get image_size
    virtual bool FwReadData(void* image, u_int32_t* image_size) = 0;

    virtual bool FwReadRom(std::vector<u_int8_t>& romSect) = 0;
    virtual bool FwBurnRom(FImage* romImg, bool ignoreProdIdCheck = false, bool ignoreDevidCheck = false, ProgressCallBack progressFunc=(ProgressCallBack)NULL) = 0; // can also read the rom from flint and give a vector of u_int8_t
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc=(ProgressCallBack)NULL) = 0;

    virtual bool FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc=(ProgressCallBack)NULL) = 0;
    virtual bool FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams) = 0;
    virtual bool FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc) = 0; //Add: callback progress, question arr, callback question, configurations
    bool FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec, ProgressCallBack progressFunc=(ProgressCallBack)NULL);

    virtual bool FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc=(PrintCallBack)NULL, ProgressCallBack progressFunc=(ProgressCallBack)NULL) = 0;

    virtual bool FwSetMFG(fs3_guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL) = 0;
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL) = 0;
    // use progressFunc when dealing with FS2 image and printFunc when dealing with FS3 image.
    virtual bool FwSetVSD(char* vsdStr, ProgressCallBack progressFunc=(ProgressCallBack)NULL, PrintCallBack printFunc=(PrintCallBack)NULL) = 0;
    virtual bool FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc=(PrintCallBack)NULL) = 0;
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc=(ProgressCallBack)NULL) = 0;
    virtual bool FwGetSection (u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage=false)= 0;
    virtual bool FwResetNvData() = 0;
    virtual bool FwShiftDevData(PrintCallBack progressFunc=(PrintCallBack)NULL) = 0;
    virtual const char*  FwGetResetRecommandationStr() = 0;

    void FwCleanUp();
    virtual bool FwInit() = 0;
    bool FwSetPrint(PrintCallBack PrintFunc);

    //needed for flint low level operations
    bool FwSwReset();

    
    //virtual bool FwBurnBlock(FwOperations &FwImageAccess); // Add call back
    static FwOperations* FwOperationsCreate(void* fwHndl, void *info, char* psid, fw_hndl_type_t hndlType, char* errBuff=(char*)NULL, int buffSize=0);
    static FwOperations* FwOperationsCreate(fw_ops_params_t& fwParams);

    //bool GetExpRomVersionWrapper();
    void getSupporteHwId(u_int32_t **supportedHwId, u_int32_t &supportedHwIdNum);

    class MLXFWOP_API RomInfo : ErrMsg {
    public:
        RomInfo(const std::vector<u_int8_t>& romSector, bool resEndi=true);
        ~RomInfo() {};
        bool initRomsInfo(roms_info_t* info);
        bool ParseInfo();
    private:
        //Rom Information
        bool         expRomFound;
        u_int8_t     numOfExpRom;
        u_int8_t     noRomChecksum;
        u_int16_t    expRomComDevid;
        u_int8_t     expRomWarning;
        char         expRomWarningMsg[MAX_ROM_ERR_MSG_LEN];
        u_int8_t     expRomErrMsgValid;
        char         expRomErrMsg[MAX_ROM_ERR_MSG_LEN];
        rom_info_t   romsInfo[MAX_ROMS_NUM];

        std::vector<u_int8_t> romSect;

        bool GetExpRomVerForOneRom(u_int32_t verOffset);
        bool GetExpRomVersion();
    };

    // virtual bool FwBurn(FwOperations &FwImageAccess);
    /*
    FwAcessRom();
    FwReadImage();
    FwSwReset();
    FwDumpConf();
    FwSetGuid();
    FwSetVsd();
    FwHwAccessChangeMode();
    FwHwaccessSetKey();
    FwGetHwInfo();
    FwSetHWParam();
    FwQueryROM();
    FwClearSemaphore();
*/
    class ExtBurnParams {

    public:
        typedef enum BurnRomOption {
            BRO_DEFAULT,
            BRO_ONLY_FROM_IMG,
            BRO_FROM_DEV_IF_EXIST,
        } BurnRomOption;
        //burn params
        bool userGuidsSpecified;
        bool userMacsSpecified;
        bool userUidsSpecified;
        bool vsdSpecified;
        bool blankGuids;
        bool burnFailsafe;
        bool allowPsidChange;
        bool useImagePs;
        bool useImageGuids;
        bool singleImageBurn;
        bool noDevidCheck;
        bool ignoreVersionCheck;
        bool useImgDevData; // FS3 image only - take device data sections from image (valid only if burnFailsafe== false)
        BurnRomOption burnRomOptions;

        //callback fun
        ProgressCallBack progressFunc;
        //data
        char* userVsd;
        std::vector<guid_t> userUids; //contains eiter guids or uids


        ExtBurnParams():userGuidsSpecified(false), userMacsSpecified(false), userUidsSpecified(false),
                        vsdSpecified(false),blankGuids(false), burnFailsafe(true), allowPsidChange(false),
                        useImagePs(false), useImageGuids(false), singleImageBurn(true), noDevidCheck(false),
                        ignoreVersionCheck(false), useImgDevData(false), burnRomOptions(BRO_DEFAULT), progressFunc(NULL),
                        userVsd(NULL){}
        };

        struct fwOpsParams{
            // COMMON
            char* psid; // can be NULL
            fw_hndl_type_t hndlType;
            char* errBuff; // can be NULL
            int errBuffSize; // can be zero if above NULL
            // FHT_FW_FILE
            char* fileHndl;
            // FHT_FW_BUFF
            u_int32_t *buffHndl;
            u_int32_t buffSize;
            // FHT_UEFI_DEV
            uefi_Dev_t* uefiHndl;
            f_fw_cmd uefiExtra;
            // FHT_MST_DEV
            char* mstHndl;
            bool forceLock;
            bool readOnly;
            int numOfBanks; // should be set to -1 for "auto-detect"
            flash_params_t* flashParams; // can be NULL
            int ignoreCacheRep;
            bool noFlashVerify;
            bool shortErrors; // show short/long error msgs (default shuold be false)
        };

        struct sgParams {
            bool updateCrc; //default should be set to true
            bool stripedImage; // default shuold be set to false unless working on striped image file
            bool macsSpecified;
            bool guidsSpecified;
            bool uidsSpecified;
            std::vector<guid_t> userGuids;
            u_int8_t numOfGUIDs; // number of GUIDs to allocate for each port. (FS3 image Only)
            u_int8_t stepSize; // step size between GUIDs. (FS3 Image Only).
        };

protected:
    #define FS3_IND_ADDR 0x24
    #define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
    #define RESTORING_MSG "Restoring signature"

	struct FwImgInfo {
        fw_info_com_t ext_info;
        u_int32_t    imgStart;
        bool         actuallyFailsafe;
        u_int32_t    cntxLog2ChunkSize;
        u_int32_t    bootSize;
        bool         isGa;
        u_int32_t    supportedHwId[MAX_NUM_SUPP_HW_IDS];
        int          supportedHwIdNum;
        bool         magicPatternFound;
        bool         imageOk;
        bool         wasQueried;
        u_int32_t     lastImageAddr;
    };
    enum {
        OLD_CNTX_START_POS_SIZE = 6,
        CNTX_START_POS_SIZE = 7
    };
    enum {
        MAX_SW_DEVICES_PER_HW=32
    };
    enum {
        IMG_SIG_TYPE_UNKNOWN = 0,
        IMG_SIG_TYPE_BIN = 1,
        IMG_SIG_TYPE_MFA = 2,
        IMG_SIG_OPEN_FILE_FAILED = 3
    };

    enum {
        IMG_VER_FS2 = 0,
        IMG_VER_FS3 = 3,
    };
    enum {
        FS_OLD_GEN = 0,
        FS_FS2_GEN,
        FS_FS3_GEN,
    };

    struct HwDevData {
        const char*      name;
        u_int32_t        hwDevId;
        chip_type_t      chipType;
        int              portNum;
        // Zero terminated list of SW device ids
        const u_int32_t  swDevIds[MAX_SW_DEVICES_PER_HW];
    };

    struct HwDev2Str {
        const char*      name;
        u_int32_t        hwDevId;
        u_int8_t         revId;
    };

    typedef int (*print2log_func) (const char* format, ...);

    // Protected Methods

    virtual bool UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size);
    bool CheckAndPrintCrcRes(char* pr, bool blank_crc, u_int32_t off, u_int32_t crc_act, u_int32_t crc_exp, bool ignore_crc = false,
            VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool checkBoot2(u_int32_t beg, u_int32_t offs, u_int32_t& next, bool fullRead, const char *pref,
            VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    u_int32_t CalcImageCRC(u_int32_t* buff, u_int32_t size);
    bool writeImage(ProgressCallBack progressFunc, u_int32_t addr, void *data, int cnt, bool is_phys_addr = false);
    //////////////////////////////////////////////////////////////////
    bool GetSectData(std::vector<u_int8_t>& file_sect, const u_int32_t *buff, const u_int32_t size);
    ////////////////////////////////////////////////////////////////////
    bool CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId);
    bool CheckMatchingHwDevId(u_int32_t hwDevId, u_int32_t rev_id, u_int32_t* supportedHwId, u_int32_t supportedHwIdNum);
    bool HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char *hw_name);
    bool CheckMac(u_int64_t mac);
    void recalcSectionCrc(u_int8_t *buf, u_int32_t data_size);
    void FwInitCom();
    void FwDebugPrint(char *str);

    static bool CntxFindAllImageStart (FBase *ioAccess, u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images);
    static bool     getRomsInfo(FBase* io, roms_info_t& romsInfo);

    bool GetQuickQuery()           {return _quickQuery;}
    bool CheckFwVersion(FwOperations &imgFwOps, u_int8_t forceVersion);
    bool CheckPSID(FwOperations &imageOps, u_int8_t allow_psid_change = false);
    chip_type_t getChipType();
    chip_type_t getChipTypeFromHwDevid(u_int32_t hwDevId);

    bool ReadImageFile(const char *fimage, u_int8_t *&file_data, int &file_size, int min_size=-1); // min_size=-1 like int flint_ops needed for fs3updateSection
    bool ModifyImageFile(const char *fimage, u_int32_t addr, void *data, int cnt);
    bool WriteImageToFile(const char *file_name, u_int8_t *data, u_int32_t length);
    bool FwBurnData(u_int32_t *data, u_int32_t dataSize, ProgressCallBack progressFunc);


    // Protected Members
    FBase*    _ioAccess;
    bool      _isCached;
    FwImgInfo _fwImgInfo;
    std::vector<u_int8_t> _romSect;
    std::vector<u_int8_t> _fwConfSect;
    std::vector<u_int8_t> _hashFileSect;
    std::vector<u_int8_t> _readSectList;

    bool      _sectionsToRead[H_LAST];
    bool      _wasVerified;
    bool      _quickQuery;

    PrintCallBack _printFunc;
    const char* _fname;
    const char* _devName;
    // show advanced error msgs
    bool _advErrors;




private:

    // Static Methods
#ifndef NO_MFA_SUPPORT
    static int      getMfaImg(char* fileName, char *psid, u_int8_t **imgbuf);
    static int      getMfaImg(u_int8_t* mfa_buf, int size, char *psid, u_int8_t **imgbuf);
#endif
    static int      getFileSignature(const char* fname);
    static int      getBufferSignature(u_int8_t* buf, u_int32_t size);
    static bool     FwAccessCreate(fw_ops_params_t& fwParams, FBase **ioAccessP);
    static u_int8_t CheckFwFormat(FBase& f, bool getFwFormatFromImg = false);
    static bool     CntxFindMagicPattern  (FBase* ioAccess, u_int32_t addr);
    static void     WriteToErrBuff(char* errBuff, const char* errStr, int size);
    static const char * err2str(int errNum);
    // Methods

    // Static Members
    static const u_int32_t _cntx_image_start_pos[CNTX_START_POS_SIZE];
    static const u_int32_t _cntx_magic_pattern[4];

    // Members
    static const HwDevData hwDevData[];
    static const HwDev2Str hwDev2Str[];
    //fw_hndl_type_t _hndlType;  //not used atm

};

#endif // FW_ACCESS_H
