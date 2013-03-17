/*
 *
 * flint_ops.h - FLash INTerface
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: flint_ops.h 7522 2011-11-16 15:37:21Z mohammad $
 *
 */

#ifndef FLINT_OPS_H
#define FLINT_OPS_H

#include <compatibility.h>

#include "flint_io.h"
#include <cibfw_layouts.h>

#define FLASH_PARAMS_OPTS "<type,log2size,num_of_flashes>"
#define FULL_VERIFY         0xff
#define FREE_STR_MAX_LEN    256
#define MAX_ROM_ERR_MSG_LEN 256
#define MAX_ROMS_NUM        5
#define ROM_INFO_SIZE       12
#define CRC_SECT_SIZE 4
#define TOTAL_SEC_SIZE(data_size) (data_size + sizeof(GPH) + CRC_SECT_SIZE)
#define CRC_CHECK_OLD "%s /0x%08x-0x%08x (0x%06x)/ (%s"

#define CRC_CHECK_OUTPUT  CRC_CHECK_OLD")"
#define FS3_CRC_CHECK_OUT CRC_CHECK_OLD":0x%x)"
#define PRE_CRC_OUTPUT   "    "
#define MAX_TOCS_NUM         128



typedef struct guid {
    u_int32_t h;
    u_int32_t l;
} guid_t;
typedef guid_t hw_key_t;


typedef struct cibfw_guids uids_t;

class Operations : public ErrMsg {
public:
    Operations() :
    _last_image_addr(0),
    _num_ports(2),
    _allow_skip_is(false),
    _fs_gen(FS_OLD_GEN),
    _cntx_striped_image(false),
    _burn_blank_guids(false),
    _quick_query(false),
    _ignore_tty(false)
    {
        initSectToRead(FULL_VERIFY);
        _err_msg[0] = '\0';
    }

    enum {
        GUIDS         = 4,
        MACS          = 2,
        MAX_GUIDS     = 32
    };

    enum {
        BX_NP_GUIDS   = 2,
        BX_SYS_GUIDS  = 1,
        BX_GUIDS      = BX_NP_GUIDS + BX_SYS_GUIDS,
        BX_IMACS      = 3,
        BX_EMACS      = 4,
        BX_MACS       = BX_EMACS + BX_IMACS,
        BX_WWPNS      = 4,
        BX_WWNNS      = 1,
        BX_SLICE_GUIDS = BX_WWNNS + BX_WWPNS + BX_MACS + BX_NP_GUIDS,

        BX_ALL_GUIDS  = (2 * BX_SLICE_GUIDS) + BX_SYS_GUIDS,
        BX_SLICES_NUM = 2,
    };

    enum {
        BI_IMACS    = 0,
        BI_EMACS    = BI_IMACS + BX_IMACS,
        BI_WWPNS    = BI_EMACS + BX_EMACS,
        BI_GUIDS    = BI_WWPNS + BX_WWPNS,
        BI_WWNNS    = BI_GUIDS  + BX_NP_GUIDS,
        BI_SYS_GUID = BX_ALL_GUIDS - 1,
    };

    enum ImageInfoTags {
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
        II_CONFIG_AREA        = 19,
        II_Last,              // Mark the end of used tag ids
        II_End                = 0xff
    };

    enum ExpRomProto {
        ER_IB  = 0,
        ER_ETH = 1,
        ER_VPI = 2
    };

    enum {
        FS_OLD_GEN = 0,
        FS_FS2_GEN,
        FS_FS3_GEN,
    };

    struct ImageInfo;
    struct RomInfo;

    // Burn operations:
    bool write_image     (Flash& f, u_int32_t addr, void *data, int cnt, bool need_report, const char* message,
                          bool new_line = true, bool is_phys_addr = false, char *fimage = NULL);
    bool CntxFailSafeBurn(Flash&     f,
                          FImage&    fim,
                          bool       need_report,
                          ImageInfo* flash_info,
                          ImageInfo* image_info,
                          bool       allow_nofs = false,
                          const char* message = NULL);

    bool CheckMatchingHwDevId(u_int32_t hwDevId, u_int32_t rev_id, Operations::ImageInfo& info);
    bool CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId);
    bool CheckMatchingExpRomDevId(Operations::ImageInfo* info);
    bool HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char *hw_name);

    // Image operations:
    bool Verify          (FBase& f, ImageInfo* info, bool both_images = false, bool show_itoc = false);
    bool VerifyFs2      (FBase& f, ImageInfo* info, bool both_images = false, bool only_get_start = false,
                         bool ignore_full_image_crc = false, bool force_no_striped_image = false);
    bool VerifyFs3(FBase& f, Operations::ImageInfo* info, bool show_itoc = false);
    bool packStripedImageData(u_int8_t *striped_data, u_int8_t *normal_data, u_int32_t length, u_int32_t &striped_length,
            bool needs_repack, u_int32_t cntxLog2ChunkSize);
    bool WriteImageToFile(char *file_name, u_int8_t *data, u_int32_t length);
    bool ReburnNewImage(u_int8_t *data, FBase *fbase, Operations::ImageInfo *info, char *image_fname, bool silent, char *feature_name);
    bool ModifyGuidSection(FBase *fbase, Operations::ImageInfo *info, guid_t *user_guids, char *image_fname, bool silent);
    bool ModifyVSDSection(FBase *fbase, Operations::ImageInfo *info, char *vsd, char *image_fname, bool silent);
    bool ModifyKeySection(FBase *fbase, Operations::ImageInfo *info, guid_t key_str, char *image_fname, bool silent);

    bool PrepareBurnErr(Flash& f);
    bool LoadAsExpRom    (FBase& f, ImageInfo* info);

    bool DumpFileSection (const char* conf_file, u_int32_t sect_type);
    bool DumpFile        (const char* conf_file, std::vector<u_int8_t> data, const char *section_name);
    bool unzipDataFile   (std::vector<u_int8_t> data, std::vector<u_int8_t> &newData, const char *section_name);


    bool GetExpRomVerForOneRom(ImageInfo* info, u_int32_t ver_offset);


    bool GetExpRomVersion(ImageInfo* info);
    bool GetExpRomVersionWrapper(ImageInfo* info);

    bool DisplayOneExpRomInfo(RomInfo* info);
    bool DisplayExpRomInfo(ImageInfo* info, char *pre_str = "");
    bool DisplayImageInfo (ImageInfo* info, bool full_query = false);
    bool GetExpRomStrVer(Operations::ImageInfo* info, char* version);

    bool QueryAll        (FBase& f, ImageInfo* info) {return QueryImage(f, info);}

    bool getGUID         (const char *s, guid_t *guid, char *filed_type = "");
    bool getFlashParams(char *flash_arg, flash_params_t *flash_params);

    bool patchVSD        (FImage& f,
                          Operations::ImageInfo* info,
                          const char *user_vsd,
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid);

    bool patchHwAccessKey(FImage& f, ImageInfo& flash_info, ImageInfo& imageinfo);

    // Misc operations
    void SetDevFlags(u_int16_t devType, bool& ib_dev, bool& eth_dev);
    bool CheckGuidsFlags(u_int16_t devType,
                         bool guids_specified,
                         bool macs_specified,
                         bool uids_specified);

    bool reportGuidChaneges(ImageInfo* info,
                          guid_t     new_guids[MAX_GUIDS],
                          guid_t     old_guids[MAX_GUIDS],
                          bool       print_guids,
                          bool       print_macs,
                          bool       print_uids);

    bool patchGUIDs      (FImage&    f,
                          ImageInfo* info,
                          bool       patch_macs,
                          bool       patch_uids,
                          bool       user_guids,
                          bool       user_macs,
                          bool       user_uids,
                          guid_t     new_guids[MAX_GUIDS],
                          guid_t     old_guids[MAX_GUIDS],
                          u_int32_t num_of_old_guids);

    bool preFS2PatchGUIDs(bool      patch_macs,
            bool      patch_uids,
            bool      user_guids,
            bool      user_macs,
            bool      user_uids,
            guid_t    new_guids[MAX_GUIDS],
            guid_t    old_guids[MAX_GUIDS],
            guid_t    **used_guid_p,
            u_int32_t num_of_old_guids);

    bool PrintMacLine  (guid_t* new_guids,  guid_t* old_guids, int mac_index);
    bool PrintBxMacs   (guid_t* new_guids,  guid_t* old_guids, int index, int num_of_guids, const char* pre_str);
    bool PrintGuidLine (guid_t* new_guids,  guid_t* old_guids, int guid_index);
    bool PrintBxGuids  (guid_t* new_guids,  guid_t* old_guids, int index, int num_of_guids, const char* pre_str);
    bool PrintUids     (guid_t* used_guids, guid_t* old_guids);
    bool PrintGUIDs    (guid_t guids[MAX_GUIDS], guid_t old_guids[MAX_GUIDS], bool print_guids, bool print_macs, bool old_guid_fmt);
    bool CheckSetGuidsFlags(ImageInfo* info, bool macs_specified, bool guids_specified, bool uids_specified);


    void initSectToRead(int imp_index);

    void SetNumPorts     (u_int32_t num_ports) {_num_ports = num_ports;}

    void SetBurnBlankGuids(bool b) {_burn_blank_guids = b;}
    bool GetBurnBlankGuids()       {return _burn_blank_guids;}
    void SetQuickQuery(bool b)     {_quick_query = b;}
    bool GetQuickQuery()           {return _quick_query;}

    // ConnectX methods
    void SetFsGen     (u_int8_t fs_gen)       {_fs_gen = fs_gen;}
    void SetIgnoreTty   (bool ignore_tty)    {_ignore_tty = ignore_tty;}
    void SetFs2StripedImage(bool si)          {_cntx_striped_image = si;}
    bool GetFs2StripedImage()                 {return _cntx_striped_image;}
    u_int8_t IsFs2           ()                    {return _fs_gen;}
    bool     IsFs2Only() {return (_fs_gen == FS_FS2_GEN);}
    bool     IsFs3() {return (_fs_gen == FS_FS3_GEN);}
    bool CheckMac        (u_int64_t mac);

    bool ReportBxMacsQuery   (guid_t* guids, int base1, int guids_num, int index, const char* pre_str);
    bool ReportBxGuidsQuery  (guid_t* guids, int base1, int guids_num, int index, const char* pre_str);
    bool ReportBxMacsWarnings(guid_t* guids, int index, int warning,   int user_uids);

    bool CheckCommandInputs(const char* dev, const char* img, CommandType cmd);
    bool CheckMaxCmdArguments(CommandType cmd, int numArgs);
    bool PrintMissGuidErr(bool ib_dev, bool eth_dev, bool bx_dev);

    bool AddNewSect(u_int8_t* &new_image_p, u_int8_t* data, GPH gph, u_int32_t* last_next);
    bool UpdateRomInImage(u_int8_t* new_image, u_int8_t* old_image, u_int8_t* rom_data, int rom_size,
                          int* new_image_size);
    bool CopyBoot2(u_int8_t* &new_image_p, u_int8_t* &old_image_p);
    bool CopyData(u_int8_t* &new_image, u_int8_t* &old_image, int copy_size);
    bool IsRomEmpty(ImageInfo* info);
    bool CheckDevImage(FBase& f, ImageInfo& info, u_int8_t read_rom = 0);
    bool CheckDevImageAndRom(FBase& f, ImageInfo& flash_info);
    bool IntegrateDevRomInImage(FImage& fim, ImageInfo& flashInfo, ImageInfo& fileInfo);
    bool      CheckImageFormatCompat(u_int16_t micVer[3]);

    bool      UpdateFullImageCRC(u_int32_t* buff, u_int32_t size, bool blank_guids);
    u_int32_t CalcImageCRC(u_int32_t* buff, u_int32_t size);

    bool IsFwSupportingRomModify(u_int16_t fw_ver[3]);

    bool GetInfoAndCheckCompt(FBase& f, ImageInfo& info, bool& fwInfoOK, bool ignoreCompatCheck);


    u_int8_t CheckIsFs2      (FBase& f);
    bool CntxIsIb        (u_int32_t devid)     {return(devid == 25408) || // IB SDR
        (devid == 25418) || // IB DDR
        (devid == 25428) || // IB QDR
        (devid == 26418) || // IB DDR
        (devid == 26428) || // IB QDR
        (devid == 26488) || // IB DDR
        (devid == 26438) ||
        (devid == 4097)  || // IB DDR
        (devid == 4098)  || // IB QDR
        (devid == 4099)  || // IB DDR
        (devid == 4100)  || // IB DDR
        (devid == 4101)  || // IB DDR
        (devid == 4102)  || // IB QDR
        (devid == 4103)  || // IB DDR
        (devid == 4104)  || // IB DDR
        (devid == 4105)  || // IB DDR
        (devid == 4106)  || // IB QDR
        (devid == 4107)  || // IB DDR
        (devid == 4108)  || // IB DDR
        (devid == 4109)  || // IB DDR
        (devid == 4110)  || // IB QDR
        (devid == 4111)  || // IB DDR
        (devid == 4112);   // IB QDR
    }

    bool CntxIsEth       (u_int32_t devid)     {return(devid == 25448) || // ETH
        (devid == 26448) || // ETH
        (devid == 25458) || //
        (devid == 26458) || //
        (devid == 26468) ||
        (devid == 26478) ||
        CntxIsIb(devid);   // From FW 2.5.0, CntX ib devices also support ETH
    }

    bool IsIs4           (u_int32_t devid)     {
        return(devid == 435) ||
        (devid == 48436) ||
        (devid == 48437) ||
        (devid == 48438) ||
        (devid == 6100); // HACK
    }

    bool IsSX           (u_int32_t devid)     {
        return(devid == SWITCHX_HW_ID) ||
        (devid == 51000);
    }

    bool IsBridgeX(u_int32_t devid) {
        return (devid ==  6100) ||
               (devid == 64102) ||
               (devid == 64112) ||
               (devid == 64122);
    }

    bool ask_user        (const char *question = NULL);

    // _last_image_addr is set by the Verify() op
    u_int32_t            _last_image_addr;

    struct RomInfo {
        bool      expRomValidVersion;
        u_int16_t expRomProductId; // 0 - invalid.
        u_int16_t expRomVer[3];
        u_int16_t expRomDevId;
        u_int8_t  expRomPort;
        u_int8_t  expRomProto;
        char      expRomFreestr[FREE_STR_MAX_LEN];
    };

    struct toc_info {
        u_int32_t entry_addr;
        struct cibfw_itoc_entry toc_entry;
        u_int8_t  data[CIBFW_ITOC_ENTRY_SIZE];
        std::vector<u_int8_t>  section_data;
    };
    //
    // ImageInfo struct: Everything you wanted to know about the FW image (and was afraid to ask).
    // This struct includes both user's info (psid, dev rev , fwver ...) and tools internal
    // info (images locations, guid ptr ...).
    //
    struct ImageInfo {
        ImageInfo() :
        invSectOk(false),
        psOk(false),
        imageOk(false),
        blankGuids(false)
        {
            memset(allImgStart,    0, sizeof(allImgStart));
            memset(guids      , 0xff, sizeof(guids));

            psid[0] = '\0';
            vsd[0]  = '\0';
            for (int i=0; i < II_Last; i++ )
                infoOffs[i] = 0;

            expRomFound = false;
        }

        // *Ok : The exit status of the specific query.
        // Note - invSectOk = true doesnt mean that invariant sector exists, it
        //        only means that the query was OK (and isFailsafe may be false).

        bool         invSectOk;
        bool         psOk;
        bool         imageOk;

        u_int32_t    allImgStart[2];

        bool         isFailsafe;

        // ConnectX:
        // For an image file where the image is marked as FW but actually contiguous, this bit would be cleared.
        bool         actuallyFailsafe;
        u_int32_t    cntxLog2ChunkSize;

        bool         validImage[2];
        u_int32_t    psStart;
        u_int32_t    imgStart;

        // For ConnectX, guids 4:5 are the cards MAC addresses (if applicable)
        guid_t       guids[MAX_GUIDS];
        u_int32_t    guidPtr;
        u_int32_t    guidNum;
        bool         blankGuids;

        u_int32_t    infoSectPtr;

        u_int16_t    vsdVendorId;
        char         vsd[VSD_LEN+1];
        char         psid[PSID_LEN+1];
        char         productVer[17];

        bool         isGa;

        u_int8_t     isVer;
        u_int16_t    fwVer[3];        // = {major_ver, minor_ver , sum_minor_ver}
        u_int16_t    fwTime[6];  // = {year, month, day, hour, minute, second}

        u_int16_t    minFitVer[4];
        u_int16_t    micVer[3];

        u_int16_t    devType;
        u_int8_t     devRev;

        u_int32_t    supportedHwId[MAX_NUM_SUPP_HW_IDS];
        int          supportedHwIdNum;

        u_int8_t     accessKeyExists;
        guid_t       accessKeyValue;

        // Mlxconfig data

        // Num of sectors in Config area. Zero means the image does not support config.
        u_int32_t configSectors;
        // Config area padding from end of image in num of sectors. Zero means default locations (end of logical image)
        u_int32_t configPad;

        std::vector<u_int8_t> TracerHashSectZipped;

        /////////////// FS3 Image info ///////////////////
        bool            isFs3;
        u_int8_t        guids_override_en;
        uids_t          fs3_uids_info;
        uids_t          orig_fs3_uids_info;
        int             num_of_itocs;
        struct toc_info tocArr[MAX_TOCS_NUM];
        char            image_vsd[VSD_LEN+1];
        char            orig_psid[PSID_LEN+1];
        u_int8_t        itoc_header[CIBFW_ITOC_HEADER_SIZE];
        u_int32_t       boot_size;
        u_int8_t        first_itoc_is_empty;
        u_int32_t       itoc_addr;

       //////////////////////////////////////////////////



        u_int32_t    imageSize;
        u_int32_t    infoOffs[II_Last];  // Offset of the tag data inside the info section data.
                                         // Can not be 0 (because of tag header) - 0 means not found.
        // Can not be 0 (because of tag header) - 0 means not found.
        bool      expRomFound;
        u_int8_t  numOfExpRom;
        bool      noRomChecksum;
        bool      expRomValidVersion;
        u_int16_t expRomComDevid;
        bool      expRomWarning;
        char      expRomWarningMsg[MAX_ROM_ERR_MSG_LEN];
        bool      expRomErrMsgValid;
        char      expRomErrMsg[MAX_ROM_ERR_MSG_LEN];
        struct RomInfo romInfo[MAX_ROMS_NUM];
        std::vector<u_int8_t> _rom_sect;
        std::vector<u_int8_t> _image_cache;
        bool magicPatternFound;
    };

    enum {
        MAX_SW_DEVICES_PER_HW=32
    };

    struct HwDevData {
        const char*      name;
        u_int32_t        hwDevId;
        int              portNum;
        // Zero terminated list of SW device ids
        const u_int32_t  swDevIds[MAX_SW_DEVICES_PER_HW];
    };

    struct HwDev2Str {
        const char*      name;
        u_int32_t        hwDevId;
        u_int8_t         revId;
    };

    struct SectionInfo {
        u_int8_t      type;
        const char    *name;
    };


    bool FwVerLessThan(u_int16_t r1[3], u_int16_t r2[3]) {
        int i;
        for (i = 0; i < 3 ; i++)
            if (r1[i] < r2[i])
                return true;
            else if (r1[i] > r2[i])
                return false;

        return false; // equal versions
    }

    enum {
        OLD_CNTX_START_POS_SIZE = 6,
        CNTX_START_POS_SIZE = 7
    };

    static const u_int32_t _cntx_image_start_pos[CNTX_START_POS_SIZE];

    static const u_int32_t _cntx_magic_pattern[4];
    static const u_int32_t _itoc_signature[4];

    char _err_msg[MAX_ERR_STR_LEN];

    void patchGUIDsSection      (u_int32_t *buf, u_int32_t ind,
                                 guid_t guids[GUIDS], int nguids);

    void PatchInfoSect          (u_int8_t*      rawSect,
                                 u_int32_t      vsdOffs,
                                 const char*    vsd);
    void PatchKeySect(u_int32_t* buff, u_int32_t keyOff, guid_t hw_key);

    // FS3 Functions
    bool      BurnFs3Image(Flash& f, FImage& fim, bool need_report);
    bool      Fs3UpdateSection(FBase& fbase, void *new_info, fs3_section_t sect_type = FS3_DEV_INFO, bool is_sect_failsafe = true, char *fimage = NULL);

private:

    bool checkBoot2             (FBase& f, u_int32_t beg, u_int32_t offs,
                                 u_int32_t& next, const char *pref, ImageInfo* info = NULL);

    bool checkGen               (FBase& f, u_int32_t beg,u_int32_t offs,
                                 u_int32_t& next, const char *pref, ImageInfo* info);

    bool checkPS                (FBase& f, u_int32_t offs, u_int32_t& next, const char *pref);

    bool checkList              (FBase& f, u_int32_t offs, u_int32_t fw_start, const char *pref, ImageInfo* info);

    bool extractGUIDptr         (u_int32_t sign, u_int32_t *buf, int buf_len,
                                 char *pref, u_int32_t *ind, int *nguids);

    bool CheckAndPrintCrcRes    (char* pr, bool blank_crc, u_int32_t off, u_int32_t crc_act, u_int32_t crc_exp, bool ignore_crc = false);

    void recalcSectionCrc       (u_int8_t *buf, u_int32_t data_size);


    void PatchPs                (u_int8_t*      rawPs,
                                 const char     vsd[VSD_LEN],
                                 const char     psid[PSID_LEN]   = NULL,
                                 u_int32_t      imageAddr        = 0);

    bool QueryImage             (FBase& f,  ImageInfo* info);

    bool CntxFindMagicPattern   (FBase& f,  u_int32_t addr);
    bool CntxFindAllImageStart  (FBase& f,  u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images);
    bool CntxGetFsData          (u_int32_t fs_info_word, bool& fs_en, u_int32_t& log2chunk_size);

    bool ParseInfoSect          (u_int8_t* buff, u_int32_t byteSize, ImageInfo *info);
    bool GetSectData            (std::vector<u_int8_t>& file_sect, const u_int32_t *buff, const u_int32_t size);

    bool      GetMaxImageSize(u_int32_t flash_size, u_int32_t sector_size, ImageInfo* image_info, ImageInfo* flash_info, u_int32_t &max_image_size);
    bool      ReadImageFile(char *fimage, u_int8_t *&file_data, int &file_size, int min_size = -1);
    bool      ModifyImageFile(char *fimage, u_int32_t addr, void *data, int cnt);

    bool      VerifyTOC(FBase& f, Operations::ImageInfo* info, u_int32_t dtoc_addr, bool& bad_signature, bool show_itoc = false);
    bool      CheckTocSignature(struct cibfw_itoc_header *itoc_header, u_int32_t first_signature);
    bool      DumpFs3CRCCheck(u_int8_t sect_type, u_int32_t sect_addr, u_int32_t sect_size, u_int32_t crc_act, u_int32_t crc_exp,
            bool ignore_crc = false);
    const char *GetSectionNameByType(u_int8_t section_type);
    bool      GetImageInfoFromSection(u_int8_t *buff, u_int8_t sect_type, Operations::ImageInfo* info, u_int8_t check_support_only = 0);
    bool      IsGetInfoSupported(u_int8_t sect_type);
    bool      DisplayOldUids(Operations::ImageInfo* info);
    bool      DisplayFs3Uids(Operations::ImageInfo* info);
    bool      UpdateDevDataITOC(u_int8_t *image_data, struct toc_info *image_toc_entry, struct toc_info *flash_toc_arr, int flash_toc_size);
    bool      IsFs3SectionReadable(u_int8_t type);
    bool      Fs3UpdateImgCache(Operations::ImageInfo* info, u_int8_t *buff, u_int32_t addr, u_int32_t size);
    bool      Fs3GetItocInfo(struct toc_info *tocArr, int num_of_itocs, fs3_section_t sect_type, struct toc_info *&curr_toc);
    bool      Fs3UpdateUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, guid_t base_uid,
                                   std::vector<u_int8_t>  &newSectionData);
    bool      Fs3UpdateVpdSection(struct toc_info *curr_toc, char *vpd, std::vector<u_int8_t>  &newSectionData);
    bool      Fs3ChangeUidsFromBase(guid_t base_uid, struct cibfw_guids *guids);
    bool      Fs3UpdateMfgUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, guid_t base_uid,
                                   std::vector<u_int8_t>  &newSectionData);
    bool      Fs3GetNewSectionAddr(FBase& fbase, struct toc_info *tocArr, struct toc_info *curr_toc, u_int32_t &NewSectionAddr, bool failsafe_section);
    bool      Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr, u_int32_t new_crc, std::vector<u_int8_t>  newSectionData);
    bool      Fs3ReburnItocSection(FBase& fbase, ImageInfo info, char *fimage, u_int32_t newSectionAddr, u_int32_t newSectionSize,
            std::vector<u_int8_t>  newSectionData, char *msg);

    u_int32_t _num_ports;
    bool      _allow_skip_is;
    u_int8_t  _fs_gen;
    bool      _cntx_striped_image;

    bool      _burn_blank_guids;
    bool      _quick_query;
    bool      _sections_to_read[H_LAST];
    bool      _is_full_verify;
    bool      _ignore_tty;
    static const HwDevData hwDevData[];
    static const HwDev2Str hwDev2Str[];

    static const SectionInfo _fs3_sections_info_arr[];
    std::vector<u_int8_t>  _fw_conf_sect;
    std::vector<u_int8_t>  _hash_file_sect;
    std::vector<u_int8_t> _read_sect_list;

};


static inline void be_guid_to_cpu(guid_t* to, guid_t* from) {
    to->h=__be32_to_cpu(from->h);
    to->l=__be32_to_cpu(from->l);
}

#endif
