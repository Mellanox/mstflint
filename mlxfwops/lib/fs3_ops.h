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

// #include "flint_base.h"
#include "fw_ops.h"
#include <cibfw_layouts.h>



class Fs3Operations : public FwOperations {
public:


    Fs3Operations(FBase *ioAccess) : FwOperations(ioAccess), _isfuSupported(false), _badDevDataSections(false){};

    virtual ~Fs3Operations()  {};
    //virtual void print_type() {printf("-D- FS3 type!\n");};
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage = false, bool showItoc = false);
    virtual bool FwQuery(fw_info_t *fwInfo, bool readRom = true, bool isStripedImage = false);
    virtual u_int8_t FwType();
    virtual bool FwInit();
    virtual bool FwReadData(void* image, u_int32_t* image_size);

    virtual bool FwReadRom(std::vector<u_int8_t>& romSect);
    virtual bool FwBurnRom(FImage* romImg, bool ignoreProdIdCheck = false, bool ignoreDevidCheck = false, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc=(ProgressCallBack)NULL);

    virtual bool FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams);
    virtual bool FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc);

    virtual bool FwSetGuids(sg_params_t& sgParam, PrintCallBack callBack, ProgressCallBack progressFunc);
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetMFG(fs3_guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwGetSection (u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage=false);
    virtual bool FwSetVSD(char* vsdStr, ProgressCallBack progressFunc=(ProgressCallBack)NULL, PrintCallBack printFunc=(PrintCallBack)NULL);
    virtual bool FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwResetNvData();
    virtual bool FwShiftDevData(PrintCallBack progressFunc=(PrintCallBack)NULL);
    virtual const char*  FwGetResetRecommandationStr();

private:
    #define CRC_CHECK_OUTPUT  CRC_CHECK_OLD")"
    #define FS3_CRC_CHECK_OUT CRC_CHECK_OLD":0x%x)"
    #define PRE_CRC_OUTPUT   "    "
    #define MAX_TOCS_NUM         128
    #define FS3_DEFAULT_SECTOR_SIZE 0x1000
    #define ITOC_ASCII 0x49544f43
    #define DTOC_ASCII 0x64544f43
    #define TOC_RAND1  0x04081516
    #define TOC_RAND2  0x2342cafa
    #define TOC_RAND3  0xbacafe00
    #define TOC_HEADER_SIZE 0x20
    #define TOC_ENTRY_SIZE  0x20
    #define MFG_INFO "MFG_INFO"
    #define UNKNOWN_SECTION "UNKNOWN"





    struct toc_info {
        u_int32_t entry_addr;
        struct cibfw_itoc_entry toc_entry;
        u_int8_t  data[CIBFW_ITOC_ENTRY_SIZE];
        std::vector<u_int8_t>  section_data;
    };

    struct Fs3ImgInfo {
        fs3_info_t ext_info;
        std::vector<u_int8_t> imageCache;
        int             numOfItocs;
        struct toc_info tocArr[MAX_TOCS_NUM];
        u_int8_t        itocHeader[CIBFW_ITOC_HEADER_SIZE];
        u_int32_t       bootSize;
        u_int8_t        firstItocIsEmpty;
        u_int32_t       itocAddr;
        u_int32_t       smallestAbsAddr;
        u_int32_t       sizeOfImgData;

    };

    struct SectionInfo {
        u_int8_t      type;
        const char    *name;
    };

    struct QueryOptions {
        bool quickQuery;
        bool readRom;
    };

    bool Fs3UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size);
    virtual bool UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size);
    bool VerifyTOC(u_int32_t dtoc_addr, bool& bad_signature, VerifyCallBack verifyCallBackFunc, bool show_itoc,
            struct QueryOptions queryOptions);
    bool Fs3Verify(VerifyCallBack verifyCallBackFunc, bool show_itoc, struct QueryOptions queryOptions);
    const char* GetSectionNameByType(u_int8_t section_type);
    bool CheckTocSignature(struct cibfw_itoc_header *itoc_header, u_int32_t first_signature);
    bool DumpFs3CRCCheck(u_int8_t sect_type, u_int32_t sect_addr, u_int32_t sect_size, u_int32_t crc_act, u_int32_t crc_exp,
                bool ignore_crc = false, VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool GetImageInfoFromSection(u_int8_t *buff, u_int8_t sect_type, u_int32_t sect_size, u_int8_t check_support_only = 0);
    bool IsGetInfoSupported(u_int8_t sect_type);
    bool IsFs3SectionReadable(u_int8_t type, QueryOptions queryOptions);
    bool GetMfgInfo(u_int8_t *buff);
    bool GetDevInfo(u_int8_t *buff);
    bool GetImageInfo(u_int8_t *buff);
    bool GetRomInfo(u_int8_t *buff, u_int32_t size);
    bool Fs3IntQuery(bool readRom = true, bool quickQuery=true);
    bool Fs3Burn(Fs3Operations &imageOps, ExtBurnParams& burnParams);
    bool BurnFs3Image(Fs3Operations &imageOps, ExtBurnParams& burnParams);
    bool UpdateDevDataITOC(u_int8_t *image_data, struct toc_info *image_toc_entry, struct toc_info *flash_toc_arr, int flash_toc_size);
    bool Fs3UpdateSection(void *new_info, fs3_section_t sect_type=FS3_DEV_INFO, bool is_sect_failsafe=true, CommandType cmd_type=CMD_UNKNOWN, PrintCallBack callBackFunc=(PrintCallBack)NULL );
    bool Fs3GetItocInfo(struct toc_info *tocArr, int num_of_itocs, fs3_section_t sect_type, struct toc_info *&curr_toc);
    bool Fs3UpdateMfgUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, fs3_guid_t base_uid,
                                            std::vector<u_int8_t>  &newSectionData);
    bool Fs3ChangeUidsFromBase(fs3_guid_t base_uid, struct cibfw_guids *guids);
    bool Fs3UpdateUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, fs3_guid_t base_uid,
                                             std::vector<u_int8_t>  &newSectionData);
    bool Fs3UpdateVsdSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, char* user_vsd,
                                     std::vector<u_int8_t>  &newSectionData);
    bool Fs3UpdateVpdSection(struct toc_info *curr_toc, char *vpd, std::vector<u_int8_t>  &newSectionData);
    bool Fs3GetNewSectionAddr(struct toc_info *curr_toc, u_int32_t &NewSectionAddr, bool failsafe_section);

    bool Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr, u_int32_t itocSize, std::vector<u_int8_t>  newSectionData);
    bool Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr);
    bool Fs3UpdateItocInfo(struct toc_info *newItocInfo, u_int32_t newSectionAddr, fs3_section_t sectionType, u_int32_t* newSectData, u_int32_t NewSectSize);
    bool Fs3UpdateItocData(struct toc_info *currToc);

    bool Fs3ReburnItocSection(u_int32_t newSectionAddr, u_int32_t newSectionSize, std::vector<u_int8_t>  newSectionData, const char *msg, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    bool GetModifiedSectionInfo(fs3_section_t sectionType, fs3_section_t nextSectionType, u_int32_t &newSectAddr,
            fs3_section_t &sectToPut, u_int32_t &oldSectSize);
    bool UpdateItocAfterInsert(fs3_section_t sectionType, u_int32_t newSectAddr, fs3_section_t SectToPut,  bool toAdd, u_int32_t* newSectData, u_int32_t NewSectSize,
            struct toc_info *tocArr, u_int32_t &numOfItocs);
    bool UpdateImageAfterInsert(struct toc_info *tocArr, u_int32_t numOfItocs, u_int8_t* newImgData, u_int32_t newSectSize);
    bool Fs3ReplaceSectionInDevImg(fs3_section_t sectionType, fs3_section_t nextSectionType, bool toAdd, u_int8_t* newImgData,
            u_int32_t newImageSize, u_int32_t* newSectData, u_int32_t NewSectSize, bool UpdateExsistingTocArr= false);
    bool CalcItocEntryCRC(struct toc_info *curr_toc);
    bool ShiftItocAddrInEntry(struct toc_info *newItocInfo, struct toc_info *oldItocInfo, int shiftSize);
    bool CopyItocInfo(struct toc_info *newTocInfo, struct toc_info *currToc);
    bool Fs3ModifySection(fs3_section_t sectionType, fs3_section_t neighbourSection, bool toAdd, u_int32_t* newSectData,
            u_int32_t newImageSize, ProgressCallBack progressFunc);
    bool Fs3RemoveSection(fs3_section_t sectionType, ProgressCallBack progressFunc);
    bool Fs3AddSection(fs3_section_t sectionType, fs3_section_t neighbourSection, u_int32_t* newSectData, u_int32_t newSectSize,
            ProgressCallBack progressFunc);
    bool CheckFs3ImgSize(Fs3Operations& imageOps);
    bool GetMaxImageSize(u_int32_t flash_size, bool image_is_fs, u_int32_t &max_image_size);

    u_int32_t getAbsAddr(toc_info* toc);
    bool getLastFwSAddr(u_int32_t& lastAddr);
    bool getFirstDevDataAddr(u_int32_t& firstAddr);
    bool reburnItocSection(PrintCallBack callBackFunc);
    bool Fs3IsfuActivateImage(u_int32_t newImageStart);

    // this class is for sorting the itoc array by ascending absolute flash_addr used in FwShiftDevData
    class TocComp {
    public:
    	TocComp(u_int32_t startAdd):  _startAdd(startAdd) {};
    	~TocComp() {};
    	bool operator() (toc_info* elem1, toc_info* elem2);
    private:
    	u_int32_t _startAdd;
    };




    // Members
    static const SectionInfo _fs3SectionsInfoArr[];
    static const u_int32_t _itocSignature[4];
    Fs3ImgInfo _fs3ImgInfo;
    bool _isfuSupported;
    bool _badDevDataSections; // set true if during verify one of the device data section is corrupt or mfg section missing

};



#endif // FS3_OPS_
