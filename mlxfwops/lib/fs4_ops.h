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


#ifndef FS4_OPS_
#define FS4_OPS_

#include <cibfw_layouts.h>
#include <cx6fw_layouts.h>
#include <cx5fw_layouts.h>
#include <cx4fw_layouts.h>
#include "fw_ops.h"
#include "fs3_ops.h"
#include "aux_tlv_ops.h"

#define FS4_MAX_BIN_VER_MAJOR 1
#define FS4_MIN_BIN_VER_MAJOR 1
#define FS4_MIN_BIN_VER_MINOR 0
#define HMAC_SIGNATURE_LENGTH 64

class Fs4Operations : public Fs3Operations {
public:


    Fs4Operations(FBase *ioAccess) :
        Fs3Operations(ioAccess), _boot2_ptr(0), _itoc_ptr(0), _tools_ptr(0), _digest_mdk_ptr(0), _digest_recovery_key_ptr(0), _public_key_ptr(0), _signatureDataSet(false)
    {
        _minBinMinorVer = FS4_MIN_BIN_VER_MINOR;
        _minBinMajorVer = FS4_MIN_BIN_VER_MAJOR;
        _maxBinMajorVer = FS4_MAX_BIN_VER_MAJOR;
    };

    virtual ~Fs4Operations()  {};
    virtual u_int8_t FwType();
    virtual bool FwInit();

    bool FwShiftDevData(PrintCallBack progressFunc = (PrintCallBack)NULL);
    bool FwCalcMD5(u_int8_t md5sum[16]);
    bool FwDeleteRom(bool ignoreProdIdCheck,
                     ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    bool FwBurnRom(FImage *romImg, bool ignoreProdIdCheck = false,
                   bool ignoreDevidCheck = false,
                   ProgressCallBack progressFunc = (ProgressCallBack)NULL);
    bool FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    bool FwQueryTimeStamp(struct tools_open_ts_entry& timestamp,
                          struct tools_open_fw_version& fwVer, bool queryRunning = false);
    bool FwResetTimeStamp();
    bool FwSignWithHmac(const char *key_file);
    bool PrepItocSectionsForHmac(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical);
    bool IsCriticalSection(u_int8_t sect_type);
    bool CalcHMAC(const vector<u_int8_t>& key, const vector<u_int8_t>& data, vector<u_int8_t>& digest);
    bool CheckIfAlignmentIsNeeded(FwOperations *imgops);
    virtual bool PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical);
    virtual bool RestoreDevToc(vector<u_int8_t>& img, char* psid, dm_dev_id_t devid_t, const cx4fw_uid_entry& base_guid, const cx4fw_uid_entry& base_mac);

protected:
    struct fs4_toc_info {
        u_int32_t entry_addr;
        struct cx5fw_itoc_entry toc_entry;
        u_int8_t data[CX5FW_ITOC_ENTRY_SIZE];
        std::vector<u_int8_t>  section_data;
    };

    virtual bool IsSectionExists(fs3_section_t sectType);


private:
    #define PRE_CRC_OUTPUT   "    "
    #define FS4_DEFAULT_SECTOR_SIZE 0x1000
    #define DTOC_ASCII 0x44544f43

    enum CRCTYPE {INITOCENTRY = 0, NOCRC = 1, INSECTION = 2};

    class TocArray {
public:
        static void initEmptyTocArrEntry(struct fs4_toc_info* tocArrEntry);
        static void copyTocArrEntry(struct fs4_toc_info* dest, struct fs4_toc_info* src);
        TocArray();
        u_int32_t           getSectionsTotalSize();
        int numOfTocs;
        struct fs4_toc_info tocArr[MAX_TOCS_NUM];
        u_int8_t tocHeader[CX5FW_ITOC_HEADER_SIZE];
        u_int32_t tocArrayAddr;
    };

    struct Fs4ImgInfo {
        /*fs4_info_t ext_info;
           std::vector<u_int8_t> imageCache;*/
        TocArray itocArr;
        TocArray dtocArr;
        u_int8_t firstItocArrayIsEmpty;
        u_int32_t smallestDTocAddr;

    };

    bool CheckSignatures(u_int32_t a[], u_int32_t b[], int n);
    bool FsVerifyAux(VerifyCallBack verifyCallBackFunc, bool show_itoc, struct QueryOptions queryOptions, bool ignoreDToc = false, bool verbose = false);
    bool CheckTocSignature(struct cx5fw_itoc_header *itoc_header, u_int32_t first_signature);
    bool CheckDevInfoSignature(u_int32_t *buff);
    bool FsBurnAux(FwOperations *imageOps, ExtBurnParams& burnParams);
    bool BurnFs4Image(Fs4Operations &imageOps, ExtBurnParams& burnParams);
    bool Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                        fs3_section_t sect_type, struct fs4_toc_info*&curr_toc);
    bool Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                        fs3_section_t sect_type, struct fs4_toc_info*&curr_toc,
                        int& toc_index);
    bool Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                        fs3_section_t sect_type, vector<struct fs4_toc_info*>& curr_toc);
    bool Fs3UpdateSection(void *new_info, fs3_section_t sect_type = FS3_DEV_INFO, bool is_sect_failsafe = true, CommandType cmd_type = CMD_UNKNOWN, PrintCallBack callBackFunc = (PrintCallBack)NULL );
    bool Fs4UpdateMfgUidsSection(struct fs4_toc_info *curr_toc,
                                 std::vector<u_int8_t>  section_data, fs3_uid_t base_uid,
                                 std::vector<u_int8_t>  &newSectionData);
    bool Fs4ChangeUidsFromBase(fs3_uid_t base_uid, struct cx5fw_guids& guids);
    bool Fs4UpdateUidsSection(std::vector<u_int8_t>  section_data, fs3_uid_t base_uid,
                              std::vector<u_int8_t>  &newSectionData);
    bool Fs4UpdateVsdSection(std::vector<u_int8_t>  section_data, char *user_vsd,
                             std::vector<u_int8_t>  &newSectionData);
    bool Fs4UpdateVpdSection(struct fs4_toc_info *curr_toc, char *vpd,
                             std::vector<u_int8_t>  &newSectionData);
    bool Fs4ReburnSection(u_int32_t newSectionAddr,
                          u_int32_t newSectionSize, std::vector<u_int8_t>  newSectionData,
                          const char *msg, PrintCallBack callBackFunc);
    bool Fs4ReburnTocSection(bool isDtoc, PrintCallBack callBackFunc);
    bool reburnDTocSection(PrintCallBack callBackFunc);
    bool reburnITocSection(PrintCallBack callBackFunc, bool isFailSafe);
    bool Fs4UpdateItocInfo(struct fs4_toc_info *curr_toc, u_int32_t NewSectSize,
                           std::vector<u_int8_t>&  newSectionData);
    bool FwReadData(void *image, u_int32_t *imageSize, bool verbose = false);
    bool CreateDtoc(vector<u_int8_t>& img, u_int8_t* SectionData, u_int32_t section_size, u_int32_t flash_data_addr,
        fs3_section_t section, u_int32_t tocEntryAddr, bool IsCRC);
    bool Fs4RemoveSectionAux(fs3_section_t sectionType);
    bool CreateImageData(vector<u_int8_t>& newImageData);
    bool Fs4RemoveSection(fs3_section_t sectionType,
                          ProgressCallBack progressFunc);
    bool Fs4AddSectionAux(fs3_section_t sectionType,
                          enum CRCTYPE crcType, u_int8_t zippedImage, u_int32_t *newSectData,
                          u_int32_t newSectSize);
    bool Fs4AddSection(fs3_section_t sectionType, enum CRCTYPE crcType,
                       u_int8_t zippedImage, u_int32_t *newSectData, u_int32_t newSectSize,
                       ProgressCallBack progressFunc);
    void updateTocEndEntryInImgCache(u_int32_t lastItocSectAddress);
    void updateTocEntryCRC(struct fs4_toc_info *tocEntry);
    void updateTocEntryData(struct fs4_toc_info *tocEntry);
    void updateTocEntrySectionData(struct fs4_toc_info *tocEntry,
                                   u_int8_t *data, u_int32_t dataSize);
    void updateTocHeaderCRC(struct cx5fw_itoc_header *tocHeader);
    inline bool checkIfSectionsOverlap(u_int32_t s1, u_int32_t e1, u_int32_t s2,
                                       u_int32_t e2);



    bool CheckFs4ImgSize(Fs4Operations& imageOps, bool useImageDevData = false);

    u_int32_t getAbsAddr(fs4_toc_info *toc);
    u_int32_t getAbsAddr(fs4_toc_info *toc, u_int32_t imgStart);
    bool getImgStart();
    bool getHWPtrs(VerifyCallBack verifyCallBackFunc);
    bool getExtendedHWPtrs(VerifyCallBack verifyCallBackFunc, FBase* ioAccess, bool IsBurningProcess = false);
    bool verifyToolsArea(VerifyCallBack verifyCallBackFunc);
    bool verifyTocHeader(u_int32_t tocAddr, bool isDtoc, VerifyCallBack verifyCallBackFunc);
    bool verifyTocEntries(u_int32_t tocAddr, bool show_itoc, bool isDtoc,
                          struct QueryOptions queryOptions, VerifyCallBack verifyCallBackFunc, bool verbose = false);
    bool CheckTocArrConsistency(TocArray& tocArr, u_int32_t imageStartAddr);
    bool CheckITocArray();
    bool CheckDTocArray();
    u_int32_t getImageSize();
    void maskDevToc(vector<u_int8_t>& img);
    void maskIToCSection(u_int32_t itocType, vector<u_int8_t>& img);
    bool Fs4UpdateSignatureSection(vector<u_int8_t>  sha256Buff,
                                   vector<u_int8_t>  &newSectionData);
    bool isDTocSection(fs3_section_t sect_type, bool& isDtoc);

    bool AlignDeviceSections(FwOperations *imageOps);
    bool restoreWriteProtection(mflash *mfl, u_int8_t banksNum,
                                write_protect_info_t protect_info[]);

    bool GetSectionSizeAndOffset(fs3_section_t sectType, u_int32_t& size, u_int32_t& offset);

    // Members
    Fs4ImgInfo _fs4ImgInfo;
    u_int32_t _boot2_ptr;
    u_int32_t _itoc_ptr;
    u_int32_t _tools_ptr;

    u_int32_t _authentication_start_ptr;
    u_int32_t _authentication_end_ptr;
    u_int32_t _digest_mdk_ptr;
    u_int32_t _digest_recovery_key_ptr;
    u_int32_t _public_key_ptr;
    bool      _signatureDataSet;

    //This class is for sorting the itoc array by ascending absolute flash_addr used in FwShiftDevData
    class TocComp {
public:
        TocComp(u_int32_t startAdd) :  _startAdd(startAdd) {};
        ~TocComp() {};
        bool operator()(fs4_toc_info *elem1, fs4_toc_info *elem2);
private:
        u_int32_t _startAdd;
    };

};

bool Fs4Operations::checkIfSectionsOverlap(u_int32_t s1, u_int32_t e1, u_int32_t s2,
                                           u_int32_t e2)
{
    if ((s1 >= s2 && s1 <= e2) || (s2 >= s1 && s2 <= e1)) {
        return true;
    }

    return false;
}

#endif // FS4_OPS_
