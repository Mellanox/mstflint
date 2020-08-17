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


#ifndef FS3_OPS_
#define FS3_OPS_


#include "reg_access/reg_access.h"
#include <cibfw_layouts.h>
#include <cx4fw_layouts.h>
#include <mlarge_buffer.h>
// #include "flint_base.h"
#include "fw_ops.h"
#include "aux_tlv_ops.h"

// FW Binary version

// max supported major version
// first time breaking compatibility remove the check if the version is not initialized
#define FS3_MAX_BIN_VER_MAJOR 1

// min supported version
#define FS3_MIN_BIN_VER_MAJOR 1
#define FS3_MIN_BIN_VER_MINOR 1

#define FLASH_RESTORE(origFlashObj) \
    if (origFlashObj) { \
        _ioAccess->close(); \
        delete _ioAccess; \
        _ioAccess = origFlashObj; \
        _fwParams.ignoreCacheRep = 0; \
    }

enum SHATYPE { SHA256, SHA512};

class Fs3Operations : public FwOperations {
public:


    Fs3Operations(FBase *ioAccess) : FwOperations(ioAccess), _imageCache(0xFF),
        _isfuSupported(false), _badDevDataSections(false), _maxImgLog2Size(0),
        _signatureExists(0), _publicKeysExists(0)
    {
        _minBinMinorVer = FS3_MIN_BIN_VER_MINOR;
        _minBinMajorVer = FS3_MIN_BIN_VER_MAJOR;
        _maxBinMajorVer = FS3_MAX_BIN_VER_MAJOR;
    };

    virtual ~Fs3Operations()  {};
    //virtual void print_type() {printf("-D- FS3 type!\n");};
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage = false, bool showItoc = false, bool ignoreDToc = false);
    virtual bool FwQuery(fw_info_t *fwInfo, bool readRom = true, bool isStripedImage = false, bool quickQuery = true, bool ignoreDToc = false, bool verbose = false);
    virtual u_int8_t FwType();
    virtual bool FwInit();
    virtual bool FwReadData(void *image, u_int32_t *image_size, bool verbose = false);
    static void    deal_with_signal();

    virtual bool FwReadRom(std::vector<u_int8_t>& romSect);
    virtual bool FwBurnRom(FImage *romImg, bool ignoreProdIdCheck = false, bool ignoreDevidCheck = false, ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc = (ProgressCallBack)NULL);

    virtual bool FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    virtual bool FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams);
    virtual bool FwBurnBlock(FwOperations *imageOps, ProgressCallBack progressFunc);

    virtual bool FwSetGuids(sg_params_t& sgParam, PrintCallBack callBack = (PrintCallBack)NULL, ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage = false);
    virtual bool FwSetVSD(char *vsdStr, ProgressCallBack progressFunc = (ProgressCallBack)NULL, PrintCallBack printFunc = (PrintCallBack)NULL);
    virtual bool FwSetVPD(char *vpdFileStr, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    virtual bool FwResetNvData();
    virtual bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack)NULL);
    virtual const char*  FwGetResetRecommandationStr();
    virtual const char*  FwGetReSignMsgStr();

    bool FwInsertSHA256(PrintCallBack printFunc = (PrintCallBack)NULL);
    bool FwSignWithOneRSAKey(const char *privPemFile, const char *uuid, PrintCallBack printFunc = (PrintCallBack)NULL);
    bool FwSignWithTwoRSAKeys(const char *privPemFile1, const char *uuid1,
                              const char *privPemFile2, const char *uuid2, PrintCallBack printFunc = (PrintCallBack)NULL);

    bool FwInsertEncSHA(SHATYPE shaType, const char *privPemFile,
                        const char *uuid, PrintCallBack printFunc = (PrintCallBack)NULL);

    virtual bool FwExtract4MBImage(vector<u_int8_t>& img, bool maskMagicPatternAndDevToc, bool verbose = false);
    virtual bool FwSetPublicKeys(char *fname, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwSetForbiddenVersions(char *fname, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool FwCalcMD5(u_int8_t md5sum[16]);
    virtual bool FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    virtual bool FwQueryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning = false);
    virtual bool FwResetTimeStamp();
    Tlv_Status_t GetTsObj(TimeStampIFC **tsObj);

    bool FwCheckIfWeCanBurnWithFwControl(FwOperations *imageOps);
    bool FwCheckIf8MBShiftingNeeded(FwOperations *imageOps, const ExtBurnParams& burnParams);
    bool CalcHMAC(const vector<u_int8_t>& key, vector<u_int8_t>& digest);
    virtual bool GetSectionSizeAndOffset(fs3_section_t sectType, u_int32_t& size, u_int32_t& offset);
    MlargeBuffer GetImageCache() { return  _imageCache; }
    virtual bool Fs3UpdateSection(void *new_info, fs3_section_t sect_type = FS3_DEV_INFO, bool is_sect_failsafe = true, CommandType cmd_type = CMD_UNKNOWN, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    virtual bool PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical);
    virtual bool RestoreDevToc(vector<u_int8_t>& img, char* psid, dm_dev_id_t devid_t, const cx4fw_uid_entry& base_guid, const cx4fw_uid_entry& base_mac);
    bool IsCriticalSection(u_int8_t sect_type);
protected:
    #define ITOC_ASCII 0x49544f43
    #define TOC_RAND1  0x04081516
    #define TOC_RAND2  0x2342cafa
    #define TOC_RAND3  0xbacafe00
    #define TOC_HEADER_SIZE 0x20
    #define TOC_ENTRY_SIZE  0x20
    #define FS3_FW_SIGNATURE_SIZE 0x10
    #define MAX_TOCS_NUM         64
    #define MFG_INFO "MFG_INFO"
    #define DEV_INFO "DEV_INFO"
    #define UNKNOWN_SECTION "UNKNOWN"

    u_int32_t getNewImageStartAddress(Fs3Operations &imageOps, bool isBurnFailSafe);
    virtual bool FsBurnAux(FwOperations *imageOps, ExtBurnParams& burnParams);
    bool DumpFs3CRCCheck(u_int8_t sect_type, u_int32_t sect_addr, u_int32_t sect_size, u_int32_t crc_act, u_int32_t crc_exp,
                         bool ignore_crc = false, VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool Fs3UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size);
    virtual bool UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size);
    virtual bool FsVerifyAux(VerifyCallBack verifyCallBackFunc, bool show_itoc, struct QueryOptions queryOptions, bool ignoreDToc = false, bool verbose = false);
    bool FsIntQueryAux(bool readRom = true, bool quickQuery = true, bool ignoreDToc = false, bool verbose = false);
    const char* GetSectionNameByType(u_int8_t section_type);
    bool GetImageInfoFromSection(u_int8_t *buff, u_int8_t sect_type, u_int32_t sect_size, u_int8_t check_support_only = 0);
    bool IsGetInfoSupported(u_int8_t sect_type);
    bool IsFs3SectionReadable(u_int8_t type, QueryOptions queryOptions);
    bool GetMfgInfo(u_int8_t *buff);
    bool GetDevInfo(u_int8_t *buff);
    bool GetImageInfo(u_int8_t *buff);
    bool GetRomInfo(u_int8_t *buff, u_int32_t size);
    bool GetImgSigInfo(u_int8_t *buff);
    bool DoAfterBurnJobs(const u_int32_t magic_patter[], Fs3Operations &imageOps,
                         ExtBurnParams& burnParams, Flash *f,
                         u_int32_t new_image_start, u_int8_t is_curr_image_in_odd_chunks);
    bool CreateDtoc(vector<u_int8_t>& img, u_int8_t* SectionData, u_int32_t section_size, u_int32_t flash_data_addr,
        fs3_section_t section, u_int32_t tocEntryAddr, bool IsCRC);
    virtual bool getRunningFwVersion();
    virtual bool Fs3IsfuActivateImage(u_int32_t newImageStart);
    bool Fs3ReburnItocSection(u_int32_t newSectionAddr, u_int32_t newSectionSize, std::vector<u_int8_t>  newSectionData, const char *msg, PrintCallBack callBackFunc = (PrintCallBack)NULL);
    bool Fs3ChangeUidsFromBase(fs3_uid_t base_uid, struct cibfw_guids& guids);
    bool Fs3ChangeUidsFromBase(fs3_uid_t base_uid, struct cx4fw_guids& guids);
    bool DeviceTimestampEnabled();
    bool RomCommonCheck(bool ignoreProdIdCheck, bool checkIfRomEmpty);
    bool extractUUIDFromString(const char *uuid, std::vector<u_int32_t>& uuidData);

    bool Fs3UpdatePublicKeysSection(unsigned int size, const char *publicKeys,
                                    std::vector<u_int8_t>  &newSectionData, bool silent = false);
    bool Fs3UpdateForbiddenVersionsSection(unsigned int size, char *publicKeys,
                                           std::vector<u_int8_t>  &newSectionData);

    bool CheckAndDealWithChunkSizes(u_int32_t cntxLog2ChunkSize, u_int32_t imageCntxLog2ChunkSize);
    bool ReBurnCurrentImage(ProgressCallBack progressFunc);
    bool RemoveWriteProtection();
    bool Fs3MemSetSignature(fs3_section_t sectType, u_int32_t size, PrintCallBack printFunc = (PrintCallBack)NULL);
    virtual bool IsSectionExists(fs3_section_t sectType);

    bool isOld4MBImage(FwOperations *imageOps);
    bool VerifyBranchFormat(const char* vsdString);

    bool AddHMACIfNeeded(Fs3Operations* imageOps, Flash *f);
    bool CheckPublicKeysFile(const char *fname, fs3_section_t& sectionType, bool silent = false);
    struct toc_info {
        u_int32_t entry_addr;
        struct cibfw_itoc_entry toc_entry;
        u_int8_t data[CIBFW_ITOC_ENTRY_SIZE];
        std::vector<u_int8_t>  section_data;
    };

    struct Fs3ImgInfo {
        fs3_info_t ext_info;
        int numOfItocs;
        struct toc_info tocArr[MAX_TOCS_NUM];
        u_int8_t itocHeader[CIBFW_ITOC_HEADER_SIZE];
        u_int8_t firstItocIsEmpty;
        u_int32_t itocAddr;
        u_int32_t smallestAbsAddr;
        u_int32_t sizeOfImgData;
        bool runFromAny;
    };

    static const SectionInfo _fs3SectionsInfoArr[];
    static const u_int32_t _itocSignature[4];
    Fs3ImgInfo _fs3ImgInfo;
    MlargeBuffer _imageCache;
    bool _isfuSupported;
    bool _badDevDataSections; // set true if during verify one of the device data section is corrupt or mfg section missing
    u_int32_t _maxImgLog2Size;

    u_int8_t _signatureExists;
    u_int8_t _publicKeysExists;

private:
    #define CRC_CHECK_OUTPUT  CRC_CHECK_OLD ")"
    #define FS3_CRC_CHECK_OUT CRC_CHECK_OLD ":0x%x)"
    #define PRE_CRC_OUTPUT   "    "
    #define FS3_DEFAULT_SECTOR_SIZE 0x1000
    #define FS3_LOG2_CHUNK_SIZE_DW_OFFSET 0x9

    reg_access_status_t getGI(mfile *mf, struct reg_access_hca_mgir *gi);
    bool VerifyTOC(u_int32_t dtoc_addr, bool& bad_signature, VerifyCallBack verifyCallBackFunc, bool show_itoc,
                   struct QueryOptions queryOptions, bool ignoreDToc = false, bool verbose = false);
    bool checkPreboot(u_int32_t *prebootBuff, u_int32_t size, VerifyCallBack verifyCallBackFunc);
    bool CheckTocSignature(struct cibfw_itoc_header *itoc_header, u_int32_t first_signature);
    bool BurnFs3Image(Fs3Operations &imageOps, ExtBurnParams& burnParams);
    bool UpdateDevDataITOC(Fs3Operations &imageOps, struct toc_info *image_toc_info_entry, struct toc_info *flash_toc_arr, int flash_toc_size);

    bool AddDevDataITOC(struct toc_info *flash_toc_entry, u_int8_t *image_data, struct toc_info *image_toc_arr, int& image_toc_size);
    
    bool Fs3GetItocInfo(struct toc_info *tocArr, int num_of_itocs, fs3_section_t sect_type, struct toc_info*&curr_toc);
    bool Fs3UpdateMfgUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, fs3_uid_t base_uid,
                                 std::vector<u_int8_t>  &newSectionData);
    bool Fs3UpdateUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, fs3_uid_t base_uid,
                              std::vector<u_int8_t>  &newSectionData);
    bool Fs3UpdateVsdSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, char *user_vsd,
                             std::vector<u_int8_t>  &newSectionData);
    bool Fs3UpdateVpdSection(struct toc_info *curr_toc, char *vpd, std::vector<u_int8_t>  &newSectionData);
    bool Fs3GetNewSectionAddr(struct toc_info *curr_toc, u_int32_t &NewSectionAddr, bool failsafe_section);
    bool Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr, u_int32_t itocSize, std::vector<u_int8_t>  newSectionData);
    bool Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr);
    bool Fs3UpdateItocInfo(struct toc_info *newItocInfo, u_int32_t newSectionAddr, fs3_section_t sectionType, u_int32_t *newSectData, u_int32_t NewSectSize);
    bool Fs3UpdateItocData(struct toc_info *currToc);

    bool GetModifiedSectionInfo(fs3_section_t sectionType, fs3_section_t nextSectionType, u_int32_t &newSectAddr,
                                fs3_section_t &sectToPut, u_int32_t &oldSectSize);
    bool UpdateItocAfterInsert(fs3_section_t sectionType, u_int32_t newSectAddr, fs3_section_t SectToPut,  bool toAdd, u_int32_t *newSectData, u_int32_t NewSectSize,
                               struct toc_info *tocArr, u_int32_t &numOfItocs);
    bool UpdateImageAfterInsert(struct toc_info *tocArr, u_int32_t numOfItocs, u_int8_t *newImgData, u_int32_t newSectSize);
    bool Fs3ReplaceSectionInDevImg(fs3_section_t sectionType, fs3_section_t nextSectionType, bool toAdd, u_int8_t *newImgData,
                                   u_int32_t newImageSize, u_int32_t *newSectData, u_int32_t NewSectSize);
    bool CalcItocEntryCRC(struct toc_info *curr_toc);
    bool ShiftItocAddrInEntry(struct toc_info *newItocInfo, struct toc_info *oldItocInfo, int shiftSize);
    bool CopyItocInfo(struct toc_info *newTocInfo, struct toc_info *currToc);
    bool Fs3ModifySection(fs3_section_t sectionType, fs3_section_t neighbourSection, bool toAdd, u_int32_t *newSectData,
                          u_int32_t newImageSize, ProgressCallBack progressFunc);
    virtual bool Fs3RemoveSection(fs3_section_t sectionType, ProgressCallBack progressFunc);
    bool Fs3AddSection(fs3_section_t sectionType, fs3_section_t neighbourSection, u_int32_t *newSectData, u_int32_t newSectSize,
                       ProgressCallBack progressFunc);
    bool CheckFs3ImgSize(Fs3Operations& imageOps, bool useImageDevData = false);
    bool CheckItocArray();
    bool CheckItocArrConsistency(std::vector<struct toc_info*>& sortedTocVec, u_int32_t imageStartAddr);


    u_int32_t getAbsAddr(toc_info *toc);
    u_int32_t getAbsAddr(toc_info *toc, u_int32_t imgStart);
    bool getLastFwSAddr(u_int32_t& lastAddr);
    bool getFirstDevDataAddr(u_int32_t& firstAddr);
    virtual bool reburnItocSection(PrintCallBack callBackFunc, bool burnFailsafe = true);
    virtual u_int32_t getImageSize();
    virtual void maskDevToc(vector<u_int8_t>& img);
    virtual void maskIToCSection(u_int32_t itocType, vector<u_int8_t>& img);
    bool FwCalcSHA(SHATYPE shaType, vector<u_int8_t>& sha256);

    

    // this class is for sorting the itoc array by ascending absolute flash_addr used in FwShiftDevData
    class TocComp {
public:
        TocComp(u_int32_t startAdd) :  _startAdd(startAdd) {};
        ~TocComp() {};
        bool operator()(toc_info *elem1, toc_info *elem2);
private:
        u_int32_t _startAdd;
    };

};



#endif // FS3_OPS_
