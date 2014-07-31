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


#ifndef FS2_OPS_
#define FS2_OPS_

#include "fw_ops.h"
#define FULL_VERIFY         0xff


class Fs2Operations : public FwOperations {
public:
    Fs2Operations(FBase *ioAccess) :
        FwOperations(ioAccess), _burnBlankGuids(false), _isFullVerify(false){};

    virtual ~Fs2Operations()  {};
    //virtual void print_type() {};
    virtual bool FwQuery(fw_info_t *fwInfo, bool readRom = true, bool isStripedImage = false);
    virtual bool FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage = false, bool showItoc = false);

    virtual bool FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams);
    virtual bool FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc);

    virtual bool FwBurnRom(FImage* romImg, bool ignoreProdIdCheck = false, bool ignoreDevidCheck = false,
            ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc=(ProgressCallBack)NULL);

    // virtual bool FwSetGuids(std::vector<guid_t>& userGuids, std::vector<guid_t>& userMacs, bool updateCrc=true, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc);

    virtual bool FwSetMFG(fs3_guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetVSD(char* vsdStr, ProgressCallBack progressFunc=(ProgressCallBack)NULL, PrintCallBack printFunc=(PrintCallBack)NULL);
    virtual bool FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc=(PrintCallBack)NULL);
    virtual bool FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    virtual bool FwShiftDevData(PrintCallBack progressFunc=(PrintCallBack)NULL);
    virtual bool FwResetNvData();
    virtual const char*  FwGetResetRecommandationStr();

    virtual bool FwGetSection (u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage=false);



    virtual u_int8_t FwType();
    virtual bool FwInit();
    virtual bool FwReadData(void* image, u_int32_t* image_size);
    virtual bool FwReadRom(std::vector<u_int8_t>& romSect);


private:

    enum Fs2ImageInfoTags {
        II_IiFormatRevision   = 0,
        II_FwVersion          = 1,
        II_FwBuildTime        = 2,
        II_DeviceType         = 3,
        II_PSID               = 4,
        II_VSD                = 5,
        II_SuppurtedPsids     = 6,
        II_ProductVer         = 7,
        II_VsdVendorId        = 8,
        II_IsGa               = 9,
        II_HwDevsId           = 10,
        II_MicVersion         = 11,
        II_MinFitVersion      = 12,
        II_HwAccessKey        = 13,
        II_PROFILES_LIST      = 14,
        II_SUPPORTED_PROFS    = 15,
        II_CONFIG_INFO        = 16,
        II_TLVS_FORMAT        = 17,
        II_TRACER_HASH        = 18,
        II_ConfigArea        = 19,
        II_Last,              // Mark the end of used tag ids
        II_End                = 0xff
    };
    struct Fs2ImgInfo {
        fs2_info_t ext_info;
        u_int32_t  infoOffs[II_Last];
        bool       psOk;
        // Configuraqtion info
        std::vector<u_int8_t> profListSectZipped;
        std::vector<u_int8_t> TlvFormatSectZipped;
        std::vector<u_int8_t> TracerHashSectZipped;
        std::vector<u_int32_t> supportedProfList;
        u_int32_t defPorfile;
        u_int32_t configAddr1;
        u_int32_t configAddr2;
        u_int32_t configSize;
        bool      isConfigurable;
        u_int32_t    infoSectPtr;
        u_int32_t    guidPtr;
        u_int32_t   fw_sector_size;

    };


    bool Fs2Verify(VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL, bool is_striped_image = false, bool both_images = false,
            bool only_get_start = false, bool ignore_full_image_crc = false, bool force_no_striped_image = false);
    bool Fs2Query ();
    bool Fs2Burn(Fs2Operations &imageOps, ExtBurnParams& burnParams);


    bool CntxGetFsData(u_int32_t fs_info_word, bool& fs_en, u_int32_t& log2chunk_size);
    bool checkList(u_int32_t offs, u_int32_t fw_start, const char *pref, VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool checkGen(u_int32_t beg,u_int32_t offs, u_int32_t& next, const char *pref, VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool ParseInfoSect(u_int8_t* buff, u_int32_t byteSize);
    bool Fs2IntQuery(bool readRom = true, bool isStripedImage=false);
    u_int32_t getDefaultSectorSz();
    bool GetMaxImageSize(u_int32_t flash_size, bool image_is_fs, u_int32_t imgConfigSectors, u_int32_t imgFwSectorSz, u_int32_t &max_image_size);
    bool UpdateFullImageCRC(u_int32_t* buff, u_int32_t size, bool blank_guids);
    bool Fs2FailSafeBurn(Fs2Operations &imageOps, bool allow_nofs, const char* pre_message,
            ProgressCallBack progressFunc);
    bool ModifyGuidSection(guid_t *user_guids, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    bool preFS2PatchGUIDs(bool patch_macs, bool patch_uids, bool user_guids, bool user_macs,
            bool user_uids, guid_t new_guids[MAX_GUIDS], guid_t old_guids[MAX_GUIDS], guid_t **used_guids_p, u_int32_t num_of_old_guids);
    bool patchGUIDs (Fs2Operations& imageOps, bool patch_macs, bool patch_uids, bool user_guids, bool user_macs, bool user_uids,
                                 guid_t new_guids[MAX_GUIDS], guid_t old_guids[MAX_GUIDS], u_int32_t num_of_old_guids);
    void patchGUIDsSection(u_int32_t *buf, u_int32_t ind, guid_t guids[MAX_GUIDS], int nguids);
    bool patchImageVsd(Fs2Operations &imgFwOps, const char* userVsd=(char*)NULL);
    void PatchInfoSect(u_int8_t* rawSect, u_int32_t vsdOffs, const char* vsd);
    void initSectToRead(int imp_index);
    //needed for fs2burn
    bool IntegrateDevRomInImage(Fs2Operations &imgFwOps);
    bool UpdateRomInImage(u_int8_t* new_image, u_int8_t* old_image, u_int8_t* rom_data, int rom_size,
                          int* new_image_size);
    bool AddNewSect(u_int8_t* &new_image_p, u_int8_t* data, GPH gph, u_int32_t* last_next);
    bool CopyBoot2(u_int8_t* &new_image_p, u_int8_t* &old_image_p);
    bool CopyData(u_int8_t* &new_image, u_int8_t* &old_image, int copy_size);

    bool ModifyKeySection(guid_t access_key, ProgressCallBack callBackFunc=(ProgressCallBack)NULL);
    void PatchKeySect(u_int32_t* buff, u_int32_t keyOff, guid_t hw_key);
    bool Fs2IsMacAvailable();
    bool CheckBxMacsFormat(guid_t* guids, int index, int user_uids);

    bool ModifyVSDSection(const char *vsd, ProgressCallBack callBackFunc=(ProgressCallBack)NULL);
    bool ReburnNewImage(u_int8_t *data, const char *feature_name, ProgressCallBack callBackFunc=(ProgressCallBack)NULL);
    bool packStripedImageData(u_int8_t *striped_data, u_int8_t *normal_data, u_int32_t length, u_int32_t &striped_length,
                              bool needs_repack, u_int32_t cntxLog2ChunkSize);
    bool Fs2SetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc=(PrintCallBack)NULL, ProgressCallBack progressFunc=(ProgressCallBack)NULL);
    bool Fs2SetGuidsForBlank(sg_params_t& sgParam);


    Fs2ImgInfo _fs2ImgInfo;
    bool _burnBlankGuids;
    bool _isFullVerify;
};

#endif // FS2_OPS_o
