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


#include "fs2_ops.h"
// #include "flint_ops.h"

#define PRE_CRC_OUTPUT   "    "
#define CRC_CHECK_OUTPUT  CRC_CHECK_OLD")"


static int part_cnt;
extern const char* g_sectNames[];

bool Fs2Operations::FwInit()
{
    FwInitCom();
    memset(&_fs2ImgInfo, 0, sizeof(_fs2ImgInfo));
    return true;
}


bool Fs2Operations::CntxGetFsData(u_int32_t fs_info_word, bool& fs_en, u_int32_t& log2chunk_size) {
    u_int8_t  checksum;
    //printf("-D- fs_info_word=%08x\n", fs_info_word);

    checksum = ((fs_info_word      ) & 0xff) +
               ((fs_info_word >>  8) & 0xff) +
               ((fs_info_word >> 16) & 0xff) +
               ((fs_info_word >> 24) & 0xff);

    if (checksum != 0) {
        return errmsg("Corrupted chunk size checksum");
    }

    fs_en = (fs_info_word & 0x8) != 0;

    if (fs_en) {
        log2chunk_size = (fs_info_word & 0x7) + 16;
    } else {
        log2chunk_size = 0;
    }
    return true;
}

bool Fs2Operations::ParseInfoSect(u_int8_t* buff, u_int32_t byteSize) {


    u_int32_t *p = (u_int32_t*)buff;
    u_int32_t offs = 0;
    u_int32_t tagNum = 0;
    bool endFound = false;

    // TODO: Add new flag on the info which indicates that the ParseInfoSect was already called.

    while (!endFound && offs < byteSize) {
        u_int32_t tagSize = __be32_to_cpu(*p) & 0xffffff;
        u_int32_t tagId   = __be32_to_cpu(*p) >> 24;

        if (offs + tagSize > byteSize) {
            return errmsg("Info section corrupted: Tag %d (TagId %d, size %d) exceeds Info section size (%d bytes) ",
                          tagNum, tagId, tagSize, byteSize);
        }
        // printf("-D- tagId = (%#x), tagSize = (%#x), offs = %#x\n", tagId, tagSize, offs);
        u_int32_t   tmp;
        const char* str;
        switch (tagId) {
        case II_FwVersion:
            _fwImgInfo.ext_info.fw_ver[0] = u_int16_t(__be32_to_cpu(*(p+1)) >> 16);
            tmp = __be32_to_cpu(*(p+2));
            _fwImgInfo.ext_info.fw_ver[1] = tmp >> 16;
            _fwImgInfo.ext_info.fw_ver[2] = tmp & 0xffff;
            break;
        case II_FwBuildTime:
            tmp = __be32_to_cpu(*(p+2));
            _fwImgInfo.ext_info.fw_rel_date[0] = (u_int16_t)(tmp & 0xff);
            _fwImgInfo.ext_info.fw_rel_date[1] = (u_int16_t)((tmp >> 8) & 0xff);
            _fwImgInfo.ext_info.fw_rel_date[2] = (u_int16_t)((tmp >> 16) & 0xffff);
            break;
        case II_MinFitVersion:
            tmp = __be32_to_cpu(*(p+1));
            _fwImgInfo.ext_info.min_fit_ver[0] = tmp >> 16;
            _fwImgInfo.ext_info.min_fit_ver[1] = tmp & 0xffff;
            tmp = __be32_to_cpu(*(p+2));
            _fwImgInfo.ext_info.min_fit_ver[2] = tmp >> 16;
            _fwImgInfo.ext_info.min_fit_ver[3] = tmp & 0xffff;
            break;
        case II_MicVersion:
            tmp = __be32_to_cpu(*(p+1));
            _fwImgInfo.ext_info.mic_ver[0] = tmp >> 16;
            //_fwImgInfo.ext_info.minFitVer[1] = tmp & 0xffff;
            tmp = __be32_to_cpu(*(p+2));
            _fwImgInfo.ext_info.mic_ver[1] = tmp >> 16;
            _fwImgInfo.ext_info.mic_ver[2] = tmp & 0xffff;
            break;
        case II_DeviceType:
            tmp = __be32_to_cpu(*(p+1));
            _fwImgInfo.ext_info.dev_type = tmp & 0xffff;
            //info->devRev  = (tmp >> 16) & 0xff;
            break;

        case II_VsdVendorId:
            tmp = __be32_to_cpu(*(p+1));
            _fwImgInfo.ext_info.vsd_vendor_id    = tmp & 0xffff;
            break;

        case II_IsGa:
            tmp = __be32_to_cpu(*(p+1));
            _fwImgInfo.isGa = tmp ? true : false;;
            break;

        case II_PSID:
            // set psid only if not previosly found in PS
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < PSID_LEN ; i++) {
                    _fwImgInfo.ext_info.psid[i] = str[i];
                }
                _fwImgInfo.ext_info.psid[PSID_LEN] = '\0';
            break;

        case II_VSD:
            // set psid only if not previosly found in PS
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < VSD_LEN ; i++) {
                    _fwImgInfo.ext_info.vsd[i] = str[i];
                }
                _fwImgInfo.ext_info.vsd[VSD_LEN] = '\0';
                _fwImgInfo.ext_info.vsd_sect_found = true;
            break;
        case II_ProductVer:

            str = (const char*)p;
            str += 4;
            for (int i = 0 ; i < PRODUCT_VER_LEN ; i++) {
                _fwImgInfo.ext_info.product_ver[i] = str[i];
            }
            _fwImgInfo.ext_info.product_ver[PRODUCT_VER_LEN] = '\0';
            break;
        case II_HwDevsId:
           for (u_int32_t i = 1; i <= (tagSize / 4); i++) {
               _fwImgInfo.supportedHwId[i - 1] = __be32_to_cpu(*(p + i));
           }
           _fwImgInfo.supportedHwIdNum = tagSize / 4;
           break;
        case II_HwAccessKey: {
            _fs2ImgInfo.ext_info.access_key_value.h = __be32_to_cpu(*(p + 1));;
            _fs2ImgInfo.ext_info.access_key_value.l = __be32_to_cpu(*(p + 2));;
            _fs2ImgInfo.ext_info.access_key_exists= 1;
        }
            break;
        case II_PROFILES_LIST: {
            GetSectData(_fs2ImgInfo.profListSectZipped, p + 1, tagSize);
        }
            break;
        case II_TLVS_FORMAT: {
            GetSectData(_fs2ImgInfo.TlvFormatSectZipped, p + 1, tagSize);
        }
            break;
        case II_TRACER_HASH: {
            GetSectData(_fs2ImgInfo.TracerHashSectZipped, p + 1, tagSize);
        }
            break;

        case II_CONFIG_INFO: {
            // printf("-D- configExists\n");
            _fs2ImgInfo.isConfigurable = true;
            _fs2ImgInfo.defPorfile   = __be32_to_cpu(*(p + 1));;
        }
            break;
        case II_SUPPORTED_PROFS: {
            for (u_int32_t i = 1; i <= (tagSize / 4); i++) {
                u_int32_t id;
                id = __be32_to_cpu(*(p + i));
                _fs2ImgInfo.supportedProfList.push_back(id);
            }
        }
            break;

        case II_ConfigArea: {
            // configuration area should always exsist
            _fs2ImgInfo.ext_info.config_sectors = __be32_to_cpu(*(p + 1));
            _fs2ImgInfo.ext_info.config_pad = __be32_to_cpu(*(p + 2));
            if (tagSize > 0x8){//fw_log_sector_size is also found
                _fs2ImgInfo.fw_sector_size = (1 << __be32_to_cpu(*(p + 3))) * 1024;// the base value is 1kb i.e 1024
            }
        }
            break;

        case II_End:
            endFound = true;
            break;

            //default:
            //printf("-D- Found tag ID %d of size %d - ignoring.\n", tagId, tagSize);
        }

        if (tagId < II_Last) {
            _fs2ImgInfo.infoOffs[tagId] = offs + 4;
        }

        p    += tagSize/4 + 1;
        offs += tagSize + 4;
        tagNum++;
    }

    if (offs != byteSize) {
        if (endFound) {
            return errmsg("Info section corrupted: Section data size is 0x%x bytes, "
                          "but end tag found after 0x%x bytes.", byteSize, offs);
        } else {
            return errmsg("Info section corrupted: Section data size is 0x%x bytes, "
                          "but end tag not found before section end.", byteSize);
        }
    }
    return true;
}


void Fs2Operations::initSectToRead(int imp_index)
{
    for (int i = 0; i < H_LAST; i++) {
        if (imp_index == FULL_VERIFY || i == imp_index) {
            _sectionsToRead[i] = 1;
        } else {
            _sectionsToRead[i] = 0;
        }
    }
    if (imp_index == FULL_VERIFY) {
        _isFullVerify = true;
    } else {
        _isFullVerify = false;
    }

    return;
}

bool Fs2Operations::checkGen(u_int32_t beg,u_int32_t offs, u_int32_t& next, const char *pref,
        VerifyCallBack verifyCallBackFunc)
{
    // char         *pr = (char *)alloca(strlen(pref) + 100);
    char pr[strlen(pref) + 100];

    char         unknown_sect_name[128];
    const char*  sect_name;

    u_int32_t    size = 0;
    GPH          gph;
    bool is_sect_to_read = false;
    // printf("-D- checkGen ... \n");
    // GPH
    sprintf(pr, "%s /0x%08x/ (GeneralHeader)", pref, offs+beg);
    READBUF((*_ioAccess), offs + beg, &gph, sizeof(GPH), pr);
    TOCPUBY(gph);

    // Body
    part_cnt++;

    // May be BOOT3?
    if (gph.type < H_FIRST  ||  gph.type >= H_LAST) {
        if (part_cnt > 2) {
            //report_callback(verifyCallBackFunc, "%s /0x%x/ - Invalid partition type (%d)\n",
            //       pref, offs+beg, gph.type);
            //return false;
        } else {
            return checkBoot2(beg, offs, next, _isFullVerify, pref, verifyCallBackFunc);
        }
    }

    // All partitions here
    offs += beg;

    if (gph.type < H_FIRST  ||  gph.type >= H_LAST) {
        // For forward compatibility, try analyzing even if section type is unknown
        // Assuming the size is in DW, like all other sections (except emt service).
        // If this assumption is wrong, CRC calc would fail - no harm done.
        sprintf(unknown_sect_name, "UNKNOWN (%d)" , gph.type);
        sect_name = unknown_sect_name;
        size = gph.size * 4;
        is_sect_to_read = true;

    } else {
        if (gph.type == H_EMT) {
            size = (gph.size + 3) / 4 * 4;
        } else {
            size = gph.size * 4;
        }
        sect_name = g_sectNames[gph.type];
        // We verify part of the image only when we verify an image burnt on a device
        if (_ioAccess->is_flash()) {
            is_sect_to_read =  _sectionsToRead[gph.type];
        } else {
            is_sect_to_read = true;
        }

    }

    sprintf(pr, CRC_CHECK_OUTPUT,
            pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
            size+(u_int32_t)sizeof(gph)+4, sect_name);

    if (size > MAX_SECTION_SIZE) {
        report_callback(verifyCallBackFunc, "%s - size too big (0x%x)\n",
               pr, size);
        return false;
    }
    if (is_sect_to_read) {
        // CRC
        Crc16        crc;
        std::vector<u_int8_t> buffv(size);
        u_int32_t *buff = (u_int32_t*)(&(buffv[0]));

        READBUF((*_ioAccess), offs+sizeof(gph), buff, size, pr);

        TOCPUn(buff,size/4);
        CRCBY(crc, gph);
        CRCBY(_ioAccess->get_image_crc(), gph);

        CRCn(crc, buff, size/4);
        CRCn(_ioAccess->get_image_crc(), buff, size/4);
        crc.finish();

        u_int32_t crc_act;
        READ4((*_ioAccess), offs+sizeof(gph)+size, &crc_act, pr);
        TOCPU1(crc_act);
        bool blank_crc = false;

        if (gph.type == H_GUID && crc_act == 0xffff) {
        	// in case we get 0xffff as crc BUT the section is not empty (i.e not ffffs)
        	//check the 64 bits of the NGUID (node guid) located at offs + sizeof(gph)
        	u_int64_t nguid;
        	READBUF((*_ioAccess), offs+sizeof(gph), (u_int8_t*)&nguid, 8, pr);
        	if (nguid == 0xffffffffffffffffULL) {
        		blank_crc = true;
        		_fs2ImgInfo.ext_info.blank_guids = true;
        	}
        }

        if (!CheckAndPrintCrcRes(pr, blank_crc, offs, crc_act, crc.get(), false, verifyCallBackFunc)) {
            return false;

        }

        _ioAccess->get_image_crc() << crc.get();
        // The image info may be null, please check that before using it.
        if (gph.type == H_FW_CONF) {
            GetSectData(_fwConfSect, buff, size);
        }
        if (gph.type == H_HASH_FILE) {
            GetSectData(_hashFileSect, buff, size);
        }

        if (gph.type == H_IMG_INFO) {
            CPUTOn(buff, size/4);
            if (!ParseInfoSect((u_int8_t*)buff, size)) {
                return errmsg("Failed to read the info sector: %s\n", err());
            }

        }

        if (gph.type == H_ROM && _romSect.empty()) {
            TOCPUn(buff, size/4);
            GetSectData(_romSect, buff, size);
        }
    }


    // mark last read addr
    _fwImgInfo.lastImageAddr = offs + size + sizeof(gph) + 4;  // the 4 is for the trailing crc
    next = gph.next;

    return true;
} // checkGen


////////////////////////////////////////////////////////////////////////
bool Fs2Operations::checkList(u_int32_t offs, u_int32_t fw_start, const char *pref, VerifyCallBack verifyCallBackFunc)

{
    //is initilized in CHECKB2
    u_int32_t next_ptr = 0;

    CHECKB2(offs, fw_start, next_ptr, _isFullVerify, pref, verifyCallBackFunc);
    part_cnt = 1;
    while (next_ptr && next_ptr != 0xff000000) {
        CHECKGN(offs, next_ptr, next_ptr, pref, verifyCallBackFunc);
    }

    return true;
} // checkList

bool Fs2Operations::Fs2Verify(VerifyCallBack verifyCallBackFunc, bool is_striped_image, bool both_images, bool only_get_start, bool ignore_full_image_crc,
                              bool force_no_striped_image)
{
    u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
    u_int32_t cntx_image_num;

    bool      ret = true;
    u_int32_t act_crc;
    bool  check_full_crc = false;

    // printf("-D- VerifyFs2 = ok\n");
    // Look for image in "physical addresses
    CntxFindAllImageStart(_ioAccess, cntx_image_start, &cntx_image_num);
    if (cntx_image_num == 0) {
        return errmsg("No valid image found");
    } else if (cntx_image_num > 2) {
        // This check may be redundant - Maybe ignore if more than 2 images found
        return errmsg("More than 2 image start locations found at addresses 0x%x, 0x%x and 0x%x. Image may be corrupted.",
                      cntx_image_start[0],
                      cntx_image_start[1],
                      cntx_image_start[2]);
    }

    if (!both_images) {
        // Check only the first image. This is enough to ensure that the device is bootable.
        cntx_image_num = 1;
    }


     // Verify the images:
     for (u_int32_t i = 0; i < cntx_image_num; i++) {
         bool      fs_en;
         u_int32_t log2chunk_size;
         u_int32_t buff[FS2_BOOT_START / 4];

         _ioAccess->get_image_crc().clear();

         _ioAccess->set_address_convertor(0, 0);

         READBUF((*_ioAccess), cntx_image_start[i], buff, FS2_BOOT_START, "Image header");

         TOCPUn(buff, FS2_BOOT_START / 4);

         u_int32_ba crc_dw = buff[IMG_CRC_OFF / 4];
         act_crc           = u_int32_t(crc_dw.range(15, 0));
         crc_dw.range(15, 0) = 0xffff;
         buff[IMG_CRC_OFF / 4] |= crc_dw;

         CRCn(_ioAccess->get_image_crc(), buff, FS2_BOOT_START / 4);
         //printf("-D- CRC is %#x\n", _ioAccess->get_image_crc().get());
         if (!CntxGetFsData(buff[FS_DATA_OFF / 4], fs_en, log2chunk_size)) {
             report_callback(verifyCallBackFunc, "\n    Can not read failsafe info word: %s\n", err());
             return(i > 0);
         }

         // If fw not enabled, image must start at addr 0
         if (!fs_en && cntx_image_start[i] != 0) {
             return errmsg("FS2 Non Failsafe image must start at address 0. Found non-fs image at address 0x%x",
                           cntx_image_start[i]);
         }

         if (fs_en) {
             report_callback(verifyCallBackFunc, "\n     FS2 failsafe image. Start address: 0x%x. Chunk size 0x%x:\n\n", cntx_image_start[i], 1 << log2chunk_size);
             report_callback(verifyCallBackFunc, "     NOTE: The addresses below are contiguous logical addresses. Physical addresses on\n"
                    "           flash may be different, based on the image start address and chunk size\n\n");
         } else {
             report_callback(verifyCallBackFunc, "\n     FS2 non failsafe image:\n\n");
         }

         if (fs_en && cntx_image_start[i] != 0 && cntx_image_start[i] != (u_int32_t)(1 << log2chunk_size)) {
             return errmsg("FS2 Failsafe image must start at address 0 or at chunk size. Found a failsafe image at address 0x%x",
                           cntx_image_start[i]);
         }

         _fwImgInfo.imgStart          = cntx_image_start[i];
         _fwImgInfo.ext_info.is_failsafe        = fs_en;
         _fwImgInfo.actuallyFailsafe  = true;
         _fwImgInfo.cntxLog2ChunkSize = log2chunk_size;



         if (_ioAccess->is_flash()) {
             // In flash, image layout must match the FS Data
             _fwImgInfo.actuallyFailsafe    = true;


             if (fs_en) {
                 _ioAccess->set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
             }
         } else {
             // In an image file there are 2 cases:
             // 1. Image generated by mlxburn
             //    The image in the file is contiguous (though it is marked as FS) - no need to set address convertion.
             // 2. The image was raw read from flash. In this case it would be in "zebra" format.
             //
             // So - I try both cases, and see which verify() succeeds.
             //
             // Heuristics that may come in handy:
             // If the image does not start at addr 0, it's not an mlxburn image.
             // If there is more than a single valid image, it's not an mlxburn image.
             // If the file size matches the image size, it is an mlxburn image.
             //
             // For now, get the "striped" indication from user.

             if (!force_no_striped_image && is_striped_image) {
                 _ioAccess->set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
             } else {
                 _ioAccess->set_address_convertor(0, 0); //disable conversion
             }
             _fwImgInfo.actuallyFailsafe    = is_striped_image;
         }

         bool imgStat = true;
         // TODO: check what only_get_start means.
         if (!only_get_start) {
             imgStat = checkList(0, FS2_BOOT_START, PRE_CRC_OUTPUT, verifyCallBackFunc);
         }
         _ioAccess->get_image_crc().finish();

         u_int32_t full_crc = _ioAccess->get_image_crc().get();

         if (!ignore_full_image_crc && _fs2ImgInfo.infoOffs[II_MicVersion]) { // For now we check only that the Mic version existing .
             check_full_crc = true;
         }
         if (imgStat && _isFullVerify && check_full_crc && !only_get_start) {
             char pr[256];
             sprintf(pr, CRC_CHECK_OUTPUT, PRE_CRC_OUTPUT, 0, _fwImgInfo.lastImageAddr - 1, _fwImgInfo.lastImageAddr,
                     "Full Image");
             CheckAndPrintCrcRes(pr, _fs2ImgInfo.ext_info.blank_guids, 0, act_crc, full_crc, false, verifyCallBackFunc);
         }
         if (i == 0) {
             ret = ret && imgStat;
         }
     }
     return ret;
}
bool Fs2Operations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc)
{
    // avoid compiler warrning (showItoc is not used in fs2)
    (void)showItoc;

    initSectToRead(FULL_VERIFY);
    if (!Fs2Verify(verifyCallBackFunc, isStripedImage)) {
        // empty the initSectToRead
        initSectToRead(H_LAST);
        return false;
    }
    // empty the initSectToRead
    initSectToRead(H_LAST);
    _wasVerified = true;
    return true;
}

u_int8_t Fs2Operations::FwType()
{
    return FIT_FS2;
}

bool Fs2Operations::FwReadData(void* image, u_int32_t* image_size)
{
    if (!Fs2Verify((VerifyCallBack)NULL)) {
        return false;
    }
    *image_size = _fwImgInfo.lastImageAddr;
    if (image != NULL) {
        if (!_ioAccess->read(0, (u_int32_t*)image, *image_size)) {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }
    return true;
}

bool Fs2Operations::Fs2Query () {

    u_int32_t guid_ptr, nguids;
    guid_t guids[MAX_GUIDS];
    /*
    if (_fwImgInfo.wasQueried == true) {
        return true;
    }
    */
    // FW ID
    u_int32_t fw_id;
    u_int32_t fw_id_offs;
    u_int32_t fw_size;
    u_int32_t im_start = _fwImgInfo.imgStart;

    if (_fwImgInfo.ext_info.is_failsafe && _fwImgInfo.actuallyFailsafe) {
        _ioAccess->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, im_start != 0);
    } else {
        _ioAccess->set_address_convertor(0,0);
    }

    im_start = 0; // offset is done by address convertor
    _fwImgInfo.magicPatternFound = true;
    fw_id_offs = 0x20;

    READ4((*_ioAccess), im_start + fw_id_offs, &fw_id, "FW ID");
    TOCPU1(fw_id);

    READ4((*_ioAccess), im_start + fw_id_offs + 0x10, &fw_size, "FW SIZE");
    TOCPU1(fw_size);
    _fwImgInfo.ext_info.image_size = fw_size;

    _fwImgInfo.ext_info.dev_rev  = fw_id >> 24;
    // Read GUIDs
    READ4((*_ioAccess), im_start + fw_id_offs + 0x14 , &guid_ptr, "GUID PTR");
    TOCPU1(guid_ptr);
    _fs2ImgInfo.guidPtr = guid_ptr;

    guid_ptr += im_start;
    if (guid_ptr >= _ioAccess->get_size()) {
        return errmsg("Failed to read GUIDs - Illegal GUID pointer (%08x). Probably image is corrupted", guid_ptr);
    }
    READ4((*_ioAccess), guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
    TOCPU1(nguids);
    nguids /= 2;
    if (nguids > MAX_GUIDS) {
        return errmsg("Failed to read GUIDs - Illegal Number of GUIDs (%d)", nguids);
        //return false;
    }
    READBUF((*_ioAccess), guid_ptr, guids, nguids * sizeof(u_int64_t), "GUIDS");
    TOCPUBY64(guids);

    u_int32_t guids_crc;
    READ4((*_ioAccess), guid_ptr + nguids * sizeof(u_int64_t), &guids_crc, "GUIDS CRC");
    guids_crc = __be32_to_cpu(guids_crc);

    _fs2ImgInfo.ext_info.blank_guids = true;
    if ((guids_crc & 0xffff) != 0xffff ) {
        _fs2ImgInfo.ext_info.blank_guids = false;
    }

    _fs2ImgInfo.ext_info.guid_num = nguids;
    for (u_int32_t i = 0 ; i < nguids ; i++) {
        _fs2ImgInfo.ext_info.guids[i] = guids[i];
        if (guids[i].h != 0xffffffff || guids[i].l != 0xffffffff) {
            _fs2ImgInfo.ext_info.blank_guids = false;
        }
    }
    // Expansion Rom version:
    RomInfo rInfo(_romSect, false);
    // There is no check for the return value of this function because it's a wrapper that always succeeds,
    // but fills the error string when there is an error
    rInfo.ParseInfo();
    rInfo.initRomsInfo(&_fwImgInfo.ext_info.roms_info);

    // Read Info:
    u_int32_ba info_ptr_ba;
    u_int32_t  info_ptr;
    u_int32_t  info_size;
    u_int8_t   info_ptr_cs = 0;
    READ4((*_ioAccess), im_start + fw_id_offs + 0xC, &info_ptr, "INFO PTR");
    TOCPU1(info_ptr);

    // Verify info_ptr checksum (should be 0)
    info_ptr_ba = info_ptr;
    for (u_int32_t i = 0; i < 4 ; i++) {
        info_ptr_cs += (u_int8_t)info_ptr_ba.range(i*8+7, i*8);
    }

    if (info_ptr_cs) {
        return errmsg("Failed to read Info Section - Bad checksum for Info section pointer (%08x). Probably the image is corrupted.", info_ptr);
    }

    info_ptr = info_ptr_ba.range(23,0);
    if (info_ptr_cs == 0 && info_ptr != 0) {
        _fs2ImgInfo.infoSectPtr = info_ptr;

        info_ptr += im_start;
        if (info_ptr >= _ioAccess->get_size()) {
            return errmsg("Failed to read Info Section - Info section pointer (%08x) too large. Probably the image is corrupted.", info_ptr);
        }
        READ4((*_ioAccess), info_ptr - 3*sizeof(u_int32_t), &info_size, "Info section size");
        TOCPU1(info_size);

        // byte size;
        info_size *= 4;

        // u_int8_t* info_buff = (u_int8_t*)alloca(info_size);
        u_int8_t info_buff[info_size];
        READBUF((*_ioAccess), info_ptr, info_buff, info_size, "Info Section");

        if (!ParseInfoSect(info_buff, info_size)) {
            return false;
        }
    }

    _fwImgInfo.imageOk = true;
    _fwImgInfo.wasQueried = true;
    return true;
}

bool Fs2Operations::Fs2IntQuery(bool readRom, bool isStripedImage)
{
    if (readRom) {
        initSectToRead(H_ROM);
    } else {
        initSectToRead(H_LAST);
    }
    if (!Fs2Verify(NULL, isStripedImage)) {
        initSectToRead(H_LAST);
        return false;
    }
    initSectToRead(H_LAST);
    if (!Fs2Query()) {
        return false;
    }
    _fwImgInfo.ext_info.chip_type = getChipType();
    return true;
}

bool Fs2Operations::FwQuery(fw_info_t *fwInfo, bool readRom, bool isStripedImage)
{
    if (!Fs2IntQuery(readRom, isStripedImage)) {
        return false;
    }
    memcpy(&(fwInfo->fw_info),  &(_fwImgInfo.ext_info),  sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs2_info), &(_fs2ImgInfo.ext_info), sizeof(fs2_info_t));
    //set the chipType in fwInfo
    fwInfo->fw_type = FIT_FS2;
    return true;
}

#define MY_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CX_DFLT_SECTOR_SIZE 0x10000
#define SX_DFLT_SECTOR_SIZE 0x1000
#define MAX_CONFIG_AREA_SIZE 0x10000

u_int32_t Fs2Operations::getDefaultSectorSz()
{
    // for ConnectX family  default sector size is 64kb else 4kb
    // all of this mess is because the sector_size written in the INI doesnt always correspond to the actual flash sector_size
    // and as for the calculation of the maximal image size we want to be synced with the FW or take worst case scenario.
    // we need this method as we only started collecting the fw_sector_size from MFT-3.6.0 so if the image was generated with
    // an older mlxburn the fw_sector_size wount be available
    u_int32_t devid = _ioAccess->get_dev_id();
    switch (devid) {
    case CX_HW_ID:
    case CX3_HW_ID:
    case CX3_PRO_HW_ID:
        return CX_DFLT_SECTOR_SIZE;
    default:
        return SX_DFLT_SECTOR_SIZE;
    }
    // we shouldnt reach here
    return 0;
}

bool Fs2Operations::GetMaxImageSize(u_int32_t flash_size, bool image_is_fs, u_int32_t imgConfigSectors, u_int32_t imgFwSectorSz,\
        u_int32_t &max_image_size)
{
    /*
        u_int32_t sector_size = _ioAccess->get_sector_size();
        u_int32_t config_sectors = MY_MAX(imgConfigSectors, _fs2ImgInfo.ext_info.config_sectors);
        if (image_is_fs) {
            max_image_size = (flash_size / 2) - ((config_sectors + _fs2ImgInfo.ext_info.config_pad) * sector_size);
        } else {
            // For non FS image, there's an optional offset + 2 consecutive config areas
            max_image_size = flash_size - (config_sectors * 2 + _fs2ImgInfo.ext_info.config_pad) * sector_size;
        }
        */
    /* new methodology:
     * a.  for CX2/CX3/PRO: in case fw_sector_size is present  reserve : num_of_config_sectors * fw_sector_size
     * b.  for CX2/CX3/PRO: in case sector_size isnt present assume sector size is 64kb and reserve: num_of_config_sectors * 64k
     * c.  for SwitchX: in case fw_sector_size is present reserve : ( num_of_config_sectors + config_padd) * fw_sector_size
     * d.  for SwitchX: in case sector_size isnt present assume sector size is 4kb and reserve: ( num_of_config_sectors + config_padd) *4k
     *   ** on ALL cases we will impose the limitation of reserving at most 64kb to the NV configuration.
     *   ** config_pad might be != 0 on SwitchX only.
     *   ** To Orenks knowledge there arent any SwitchX with flashes that dont support 4kb.
     */
    u_int32_t sector_size = (imgFwSectorSz != 0 || _fs2ImgInfo.fw_sector_size != 0) ?\
            MY_MAX(imgFwSectorSz, _fs2ImgInfo.fw_sector_size) : getDefaultSectorSz();
    u_int32_t config_sectors = MY_MAX(imgConfigSectors, _fs2ImgInfo.ext_info.config_sectors);
    u_int32_t areaToReserve = config_sectors * sector_size;
    // we dont want to exceed 64kb of reserved space
    areaToReserve = areaToReserve > MAX_CONFIG_AREA_SIZE ? MAX_CONFIG_AREA_SIZE : areaToReserve;
    //printf("-D- sector_size: 0x%x, config_sectors: %d, areaToReserve: 0x%x, config_pad: %d\n"
            //, sector_size, config_sectors, areaToReserve, _fs2ImgInfo.ext_info.config_pad);
    if (image_is_fs) {
        // why do we take config padding of the image info of the device and not the image to be burnt or the maximum between them??
        max_image_size = (flash_size / 2) - (areaToReserve + (_fs2ImgInfo.ext_info.config_pad * sector_size));
    } else {
        // For non FS image, there's an optional offset + 2 consecutive config areas
        max_image_size = flash_size - (areaToReserve * 2 + _fs2ImgInfo.ext_info.config_pad*sector_size);
    }
    return true;
}

bool Fs2Operations::UpdateFullImageCRC(u_int32_t* buff, u_int32_t size, bool blank_guids)
{
    // Writing 0xffff on the CRC field.
    u_int32_ba crc_dw = TOCPU1(buff[IMG_CRC_OFF / 4]);
    crc_dw.range(15, 0)  = 0xffff;


    buff[IMG_CRC_OFF / 4] = CPUTO1(crc_dw);

    if (blank_guids) {
        return true;
    }

    // Calc CRC image.
    u_int32_t new_crc = CalcImageCRC(buff, size);

    // Update the CRC.
    TOCPU1(crc_dw);
    crc_dw.range(15, 0)   = new_crc;
    buff[IMG_CRC_OFF / 4] = CPUTO1(crc_dw);

    return true;
}
#define ERASE_MESSAGE "    Please erase them by using the command: \"" MLXCONFIG_CMD " " ERASE_CMD "\" and then re-burn"
//TODO: remove pre_message from function def
bool Fs2Operations::Fs2FailSafeBurn(Fs2Operations &imageOps,
                                  bool      allow_nofs,
                                  const char* pre_message,
                                  ProgressCallBack progressFunc) {
    //we do not use pre_message, avoid warrning
	//TODO: remove pre_message from function definition
    (void)pre_message;

    Flash  *f = (Flash*)(this->_ioAccess);
    FImage *fim = (FImage*)(imageOps._ioAccess);


    // TODO: See getBuf effect on zebra image.
    u_int8_t  *data8      = (u_int8_t *) fim->getBuf();
    int        image_size = fim->getBufLength();
    u_int32_t  zeroes     = 0;
    bool is_curr_image_in_odd_chunks;

    // Update CRC.
    // TODO: No support for blank guids
    bool isBlankGuids = ( _burnBlankGuids || imageOps._fs2ImgInfo.ext_info.blank_guids );
    UpdateFullImageCRC(fim->getBuf(), image_size / 4, isBlankGuids); // size in dwords

    // TODO: Do we need the verify ORENK
    if (!allow_nofs) {
        if (!imageOps._fwImgInfo.ext_info.is_failsafe) {
            return errmsg("The given image is not a failsafe image");
        }

        if (_fwImgInfo.cntxLog2ChunkSize != imageOps._fwImgInfo.cntxLog2ChunkSize) {
            return errmsg("Failsafe chunk sizes in flash (0x%x) and in image (0x%x) are not the same.",
                          1 << _fwImgInfo.cntxLog2ChunkSize,
                          1 << imageOps._fwImgInfo.cntxLog2ChunkSize);
        }
    }

    u_int32_t max_image_size;
    if (!GetMaxImageSize(f->get_size(), imageOps._fwImgInfo.ext_info.is_failsafe,\
            imageOps._fs2ImgInfo.ext_info.config_sectors, imageOps._fs2ImgInfo.fw_sector_size, max_image_size)) {
        return false;
    }
    //printf("-D- max image size : %d, image_size : %d\n",max_image_size, imageOps._fwImgInfo.ext_info.image_size);
    // Check if size of image is OK
    if (imageOps._fwImgInfo.ext_info.image_size > max_image_size) {
        const char *image_type = (imageOps._fwImgInfo.ext_info.is_failsafe) ? "failsafe" : "non-failsafe";
        const char *note_str   = (imageOps._fwImgInfo.ext_info.is_failsafe) ? " - half of total flash size" : " - total flash size";

        return errmsg("Size of %s image (0x%x) is greater than max %s image size (0x%x%s)",
                 image_type, imageOps._fwImgInfo.ext_info.image_size, image_type, max_image_size, note_str);

    }

    u_int32_t new_image_start;

    if (_fwImgInfo.imgStart != 0) {
        is_curr_image_in_odd_chunks = 1;
        new_image_start = 0;
    } else {
        is_curr_image_in_odd_chunks = 0;
        new_image_start = (1 << imageOps._fwImgInfo.cntxLog2ChunkSize);
    }


    if (imageOps._fwImgInfo.ext_info.is_failsafe) {
        f->set_address_convertor(imageOps._fwImgInfo.cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);
    } else {
        f->set_address_convertor(0,0);
        new_image_start = 0;
    }

    // Go ahead and burn!
    //const char* image_name = new_image_start == 0 ? "first" : "second";
    if (!writeImage(progressFunc, 16 , data8 + 16, image_size - 16)) {
        return false;
    }
    // Write new signature
    if (!f->write(0, data8, 16, true)) {
        //return false;
        return errmsg("Flash write failed. %s", f->err());
    }
    bool boot_address_was_updated = true;
    // Write new image start address to crspace (for SW reset)
    if (!f->update_boot_addr(new_image_start)) {
        boot_address_was_updated = false;
    }

    if (imageOps._fwImgInfo.ext_info.is_failsafe) {
        if (allow_nofs) {
            // When burning in nofs, remnant of older image with different chunk size
            // may reside on the flash -
            // Invalidate all images marking on flash except the one we've just burnt

            u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
            u_int32_t cntx_image_num;

            CntxFindAllImageStart(_ioAccess, cntx_image_start, &cntx_image_num);
            // Address convertor is disabled now - use phys addresses
            for (u_int32_t i = 0; i < cntx_image_num; i++) {
                if (cntx_image_start[i] != new_image_start) {
                    if (!f->write(cntx_image_start[i], &zeroes, sizeof(zeroes), true)) {
                        //return false;
                        return errmsg("Flash write failed. %s", f->err());
                    }
                }
            }
        } else {
            // invalidate previous signature
            f->set_address_convertor(imageOps._fwImgInfo.cntxLog2ChunkSize, is_curr_image_in_odd_chunks);
            if (!f->write(0, &zeroes, sizeof(zeroes), true)) {
                //return false;
                return errmsg("Flash write failed. %s", f->err());
            }
        }
    }
    if (boot_address_was_updated == false) {
        report_warn("Failed to update FW boot address. Power cycle the device in order to load the new FW.\n");
    }

    return true;
}


bool Fs2Operations::preFS2PatchGUIDs(bool      patch_macs,
        bool      patch_uids,
        bool      user_guids,
        bool      user_macs,
        bool      user_uids,
        guid_t    new_guids[MAX_GUIDS],
        guid_t    old_guids[MAX_GUIDS],
        guid_t    **used_guids_p,
        u_int32_t num_of_old_guids)
{
    guid_t*         used_guids;
    *used_guids_p = old_guids ? old_guids : new_guids;

    if (new_guids) {
        // if only guids or only macs are specified by user, keep the other
        // as currently set of flash. This is in order to simplify transitions between
        // burning IB and ETH FW.
        if (!patch_uids) {
            if (old_guids && !user_guids) {
                for (int i = 0; i < GUIDS; i++) {
                    new_guids[i] = old_guids[i];
                }
            }

            if (old_guids && !user_macs) {
                for (int i = GUIDS; i < MAX_GUIDS; i++) {
                    new_guids[i] = old_guids[i];
                }
            }
        }
        *used_guids_p = new_guids;
    }
    used_guids = *used_guids_p;

    if (!patch_uids) {
        if (patch_macs) {

            // To ease upgrade from 4 GUIDS format to 4+2 format, or to move from IB to ETH,
            // if macs are not
            // explicitly set in flash, they are derived from the GUIDs according to
            // Mellanox methodology - 48 bit MAC == 64 bit GUID without the middle 16 bits.

            if (old_guids && ((num_of_old_guids == 4) ||
                              (num_of_old_guids == 6 &&
                               (old_guids[GUIDS  ].h & 0xffff)     == 0xffff     &&
                               (old_guids[GUIDS  ].l & 0xffffffff) == 0xffffffff &&
                               (old_guids[GUIDS+1].h & 0xffff)     == 0xffff     &&
                               (old_guids[GUIDS+1].l & 0xffffffff) == 0xffffffff))) {
                for (int i = 0 ; i < MACS; i++) {
                    u_int64_t mac  =  old_guids[i+1].h >> 8;
                    mac <<= 24;
                    mac |= (old_guids[i+1].l & 0xffffff);

                    old_guids[GUIDS+i].h = u_int32_t(mac >> 32);
                    old_guids[GUIDS+i].l = u_int32_t(mac  & 0xffffffff);

                    // printf("-D- Guid " GUID_FORMAT " to MAC "MAC_FORMAT"\n", old_guids[i+1].h, old_guids[i+1].l, old_guids[i+GUIDS].h,old_guids[i+GUIDS].l  );
                }
            }

            guid_t* macs = &used_guids[4];

            for (int i = 0 ; i < MACS ; i++) {
                u_int64_t mac = (((u_int64_t)macs[i].h) << 32) | macs[i].l;
                if (!_burnBlankGuids && !CheckMac(mac)) {
                    return errmsg("Bad mac (" MAC_FORMAT ") %s: %s. Please re-burn with a valid -mac flag value.", macs[i].h,
                           macs[i].l,
                           user_macs ? "given" : "found on flash", err());
                }

            }
        }
    } else {
        if (!_burnBlankGuids) {
            for (int i = 0; i < BX_SLICES_NUM; i++ ) {
                if (CheckBxMacsFormat(used_guids, i, user_uids) == false) {
                    return false;
                }
            }
        }

    }
    // Avoid warnings
    user_uids = true;

    return true;
}


bool Fs2Operations::CheckBxMacsFormat(guid_t* guids, int index, int user_uids)
{
    int base;
    base = index * BX_SLICE_GUIDS + BI_IMACS;
    for (int i = base; i < base + BX_MACS; i++) {
         u_int64_t mac = (((u_int64_t)guids[i].h) << 32) | guids[i].l;
         if (!CheckMac(mac)) {
             return errmsg("Bad mac (" MAC_FORMAT ") %s: %s. Please re-burn with a valid MACs flag value.", guids[i].h,
                     guids[i].l,
                     user_uids ? "given" : "found on flash", err());

         }
     }
     return true;
}

////////////////////////////////////////////////////////////////////////
void Fs2Operations::patchGUIDsSection(u_int32_t *buf, u_int32_t ind, guid_t guids[MAX_GUIDS], int nguids)
{
    u_int32_t       new_buf[MAX_GUIDS*2] = {0};

    // Form new GUID section
    for (u_int32_t i=0; i<(u_int32_t)nguids; i++) {
        new_buf[i*2] = guids[i].h;
        new_buf[i*2+1] = guids[i].l;
    }

    // Patch GUIDs
    for (u_int32_t i=0; i<sizeof(new_buf)/sizeof(u_int32_t); ++i) {
        new_buf[i] = _burnBlankGuids ? 0xffffffff : __cpu_to_be32(new_buf[i]);
    }
    memcpy(&buf[ind/4], &new_buf[0], nguids * 2 * sizeof(u_int32_t));

    // Insert new CRC
    if (_burnBlankGuids) {
        buf[ind/4 + nguids*2] =  __cpu_to_be32(0xffff);
    } else {
        recalcSectionCrc((u_int8_t*)buf + ind - sizeof(GPH), sizeof(GPH) + nguids * 8);
    }

} // patchGUIDsSection



bool Fs2Operations::patchGUIDs (Fs2Operations&   imageOps,
                             bool      patch_macs,
                             bool      patch_uids,
                             bool      user_guids,
                             bool      user_macs,
                             bool      user_uids,
                             guid_t    new_guids[MAX_GUIDS],
                             guid_t    old_guids[MAX_GUIDS],
                             u_int32_t num_of_old_guids)
{
    guid_t*         used_guids;
    u_int32_t       *buf = ((FImage*)imageOps._ioAccess)->getBuf();

    // Call common function
    if (!preFS2PatchGUIDs(patch_macs, patch_uids, user_guids, user_macs, user_uids, new_guids, old_guids, &used_guids, num_of_old_guids)) {
        return false;
    }
    // Path GUIDs section
    if (imageOps._fs2ImgInfo.guidPtr) {
        patchGUIDsSection(buf, imageOps._fwImgInfo.imgStart + imageOps._fs2ImgInfo.guidPtr, used_guids, imageOps._fs2ImgInfo.ext_info.guid_num);
    }


    // Avoid warnings
    user_uids = true;
    return true;
}

void Fs2Operations::PatchInfoSect(u_int8_t* rawSect, u_int32_t vsdOffs, const char* vsd)
{

    u_int32_t  vsdSize  = __be32_to_cpu(*((u_int32_t*)(rawSect + sizeof(GPH) + vsdOffs - 4))) & 0xffffff;
    u_int32_t  infoSize = __be32_to_cpu(*((u_int32_t*)(rawSect + 4)));

    // byte size;
    infoSize *= 4;

    if (vsd) {
        u_int32_t len = strlen(vsd);

        if (len > vsdSize) {
            report_warn("The given VSD length is too large (%d chars). Truncating to %d chars.\n", len, vsdSize);
            len = vsdSize;
        }

        memset(rawSect + sizeof(GPH) + vsdOffs,  0,   vsdSize );
        memcpy(rawSect + sizeof(GPH) + vsdOffs,  vsd, len);
    }

    recalcSectionCrc(rawSect, sizeof(GPH) + infoSize);
}


bool Fs2Operations::patchImageVsd(Fs2Operations &imgFwOps, const char* userVsd)
{
    u_int32_t *imgBuf = ((FImage*)(imgFwOps._ioAccess))->getBuf();
    u_int8_t *imgInfoSect = (u_int8_t*)imgBuf + imgFwOps._fs2ImgInfo.infoSectPtr - sizeof(GPH);
    const char* vsdToUse = (userVsd && ( strlen(userVsd) <= VSD_LEN )) ? userVsd : (const char*)(this->_fwImgInfo.ext_info.vsd);
    PatchInfoSect(imgInfoSect, imgFwOps._fs2ImgInfo.infoOffs[II_VSD], vsdToUse);
    return true;
}

/*********************************************************/


#define GUID_PTR_OFF    0x34
#define IMAGE_INFO_PTR  0x2c
#define IMAGE_SIZE_OFF  0x30
#define IMAGE_ROM_INDEX 2
#define CRC_SECT_SIZE 4
#define TOTAL_SEC_SIZE(data_size) (data_size + sizeof(GPH) + CRC_SECT_SIZE)
#define COPY_DW(dest, dword) {\
    CPUTO1(dword);\
    memcpy(dest, &dword, 4);\
}

#define READ_DW(dw, data) {\
    dw = (*((u_int32_t*)(data)));\
    TOCPU1(dw);\
}


bool Fs2Operations::CopyData(u_int8_t* &new_image, u_int8_t* &old_image, int copy_size)
{
    memcpy(new_image, old_image, copy_size);

    new_image += copy_size;
    old_image += copy_size;

    return true;
}



bool Fs2Operations::CopyBoot2(u_int8_t* &new_image_p, u_int8_t* &old_image_p)
{
    u_int32_t size;
    READ_DW(size, old_image_p + 4);
    size = (size + 4) * 4;
    CopyData(new_image_p, old_image_p, size);
    return true;
}

bool Fs2Operations::AddNewSect(u_int8_t* &new_image_p, u_int8_t* data, GPH gph, u_int32_t* last_next)
{

    int size = gph.size * 4  ;

    *last_next =  gph.next + sizeof(GPH);

    CPUTOBY(gph);

    // Copy the GPH
    memcpy(new_image_p, (u_int8_t*)&gph, sizeof(GPH));

    // Copy the data
    memcpy(new_image_p + sizeof(GPH), data, size);

    // Calc the CRC and copy it
    recalcSectionCrc(new_image_p, sizeof(GPH) + size);

    new_image_p = new_image_p + TOTAL_SEC_SIZE(size);
    return true;
}
bool Fs2Operations::UpdateRomInImage(u_int8_t* new_image, u_int8_t* old_image, u_int8_t* rom_data, int rom_size,
                                  int* new_image_size)
{
    GPH gph;
    u_int32_t header;
    u_int32_t next_ptr, last_next;

    u_int8_t *new_image_p, *old_image_p;
    new_image_p = new_image;
    old_image_p = old_image;

    // Copy first section
    CopyData(new_image_p, old_image_p, FS2_BOOT_START);

    //// Read BOOT2
    CopyBoot2(new_image_p, old_image_p);

    READ_DW(header, old_image_p);

    if (header < H_FIRST  ||  header >= H_LAST) {
        CopyBoot2(new_image_p, old_image_p);
    }
    next_ptr = old_image_p - old_image;

    last_next =  next_ptr + sizeof(GPH);
    int sect_index = 0, rom_inserted = 0;

    // In this case we need to remove the ROM.
    if (rom_data == NULL) {
        rom_inserted = 1;
    }

    while (next_ptr && next_ptr != 0xff000000) {
        u_int8_t* old_section = old_image + next_ptr;
        gph = (*(GPH*)(old_section));
        TOCPUBY(gph);
        u_int32_t new_image_index = (new_image_p - new_image);
        sect_index++;
        //printf("-D- new_image_index = %#x,  next_ptr = %#x\n",  new_image_index, next_ptr);
        next_ptr = gph.next;
        u_int8_t* data;

        //printf("-D- Before GPH: type = %#x, size = %#x, next = %#x, param = %#x\n", gph.type, gph.size, gph.next, gph.param);

        if (!rom_inserted && (sect_index == IMAGE_ROM_INDEX || gph.type == H_ROM)) {
            // prepare new ROM.
            GPH new_gph;
            int rom_whole_size =  TOTAL_SEC_SIZE(rom_size);

            data      = rom_data;
            new_gph.size  = rom_size / 4;
            new_gph.next  = new_image_index + rom_whole_size;
            new_gph.param = 0;
            new_gph.type  = H_ROM;

            AddNewSect(new_image_p, data, new_gph, &last_next);

            rom_inserted = 1;
        }
        // If this section is ROM section we will ignore it.
        if (gph.type == H_ROM) {
            continue;
        }

        new_image_index = (new_image_p - new_image);
        data = old_section + sizeof(GPH);
        if (gph.next != 0xff000000) {
           gph.next = new_image_index + TOTAL_SEC_SIZE(gph.size * 4);
        }

        if (gph.type == H_GUID) {
            COPY_DW(new_image + GUID_PTR_OFF, last_next);
        } else if (gph.type == H_IMG_INFO) {
            u_int32_ba a = last_next;
            u_int32_t check_sum = 0;
            for (int i = 0; i < 3; i++) {
                check_sum += a.range(i * 8 + 7, i * 8);
            }
            check_sum = 0x100 - (check_sum % 0x100);
            a.range(31, 24) = check_sum;
            last_next = u_int32_t(a);
            COPY_DW(new_image + IMAGE_INFO_PTR, last_next);
        }
        AddNewSect(new_image_p, data, gph, &last_next);
    }
    // Update image size.
    u_int32_t size = new_image_p - new_image;
    /* TODO: reivew this, also deal with if fw is failsafe we should compare with get_size()/2 if not compare with the entire flash size
     //check if size is bigger than flash
    if (size >=  _fwImgInfo.actuallyFailsafe ? (_ioAccess->get_size()/2) : (_ioAccess->get_size())) {
        return errmsg("Rom is too big to be integrated with the FW image.(img: %d, flash: %d)", (int)size, (int)_ioAccess->get_size() );
    }*/

    *new_image_size = size;

    COPY_DW(new_image + IMAGE_SIZE_OFF, size);

    // Writing 0 on the CRC existing field to let the tool verify the image
    // and get some information which will be needed later.
    u_int32_ba crc_dw = TOCPU1(*(u_int32_t*)(&new_image[IMG_CRC_OFF]));
    crc_dw.range(23, 16) = 0;
    (*(u_int32_t*)(&new_image[IMG_CRC_OFF])) = CPUTO1(crc_dw);

    return true;
}



bool Fs2Operations::IntegrateDevRomInImage(Fs2Operations &imageOps)
{
    u_int32_t rom_size = _romSect.size();
    FImage* fim = (FImage*)(imageOps._ioAccess);
    u_int32_t  new_image_size = fim->getBufLength() + TOTAL_SEC_SIZE(rom_size);
    vector<u_int8_t> new_data(new_image_size);
    int actual_image_size;
    //vector<u_int8_t> romWithEndian<>
    //TOCPUn((u_int8_t*)(&_romSect[0]), rom_size/4);

    // Compine the image and the rom into new daa
    if(!UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(fim->getBuf()),
                         (u_int8_t*)(&_romSect[0]), rom_size, &actual_image_size)) {
        return errmsg("%s", err());
    }

    // close old image and open new image with the rom.
    ((FImage*)(imageOps._ioAccess))->close();
    ((FImage*)(imageOps._ioAccess))->open((u_int32_t*)(&new_data[0]), actual_image_size);


    if (!imageOps.FwVerify(NULL) || !imageOps.Fs2IntQuery()) {
        return errmsg("Internal error: verify/query of image after integrating ROM failed\n");
    }

    return true;
}
/********************************************************************/

bool Fs2Operations::Fs2Burn(Fs2Operations &imageOps, ExtBurnParams& burnParams)
{
    if (imageOps.FwType() != FIT_FS2) {
        return errmsg("FW image type is not FS2\n");
    }

    if (!imageOps.Fs2IntQuery()) {
        return false;
    }

   bool devIntQueryRes = Fs2IntQuery();

   if (!devIntQueryRes && burnParams.burnFailsafe) {
       return errmsg("%s, burn cannot be failsafe." , err());
   }

    // Check Matching device ID
    // HACK
#ifndef UEFI_BUILD // NO Device ID here..

    if (!burnParams.noDevidCheck) {
        if (imageOps._fs2ImgInfo.infoOffs[II_HwDevsId]) {
             if (!CheckMatchingHwDevId(_ioAccess->get_dev_id(),
                                         _ioAccess->get_rev_id(),
                                         imageOps._fwImgInfo.supportedHwId,
                                         imageOps._fwImgInfo.supportedHwIdNum)) {
                 return errmsg("Device/Image mismatch: %s\n",this->err( ));
             }
         } else if (imageOps._fs2ImgInfo.infoOffs[II_DeviceType]) {
             if (!CheckMatchingDevId(_ioAccess->get_dev_id(), imageOps._fwImgInfo.ext_info.dev_type)) {
                 return errmsg("Device/Image mismatch: %s\n",this->err());
             }
         }

    }
#endif

    // Check PSID
    if (devIntQueryRes && !CheckPSID(imageOps, burnParams.allowPsidChange)) {
        return false;
    }

    // Check if the burnt FW version is OK
    if (!CheckFwVersion(imageOps, burnParams.ignoreVersionCheck)) {
        return false;
    }

    // ROM patchs
    if (((burnParams.burnRomOptions == ExtBurnParams::BRO_FROM_DEV_IF_EXIST) && (_fwImgInfo.ext_info.roms_info.exp_rom_found)) || // There is ROM in device and user choses ir
            ((burnParams.burnRomOptions == ExtBurnParams::BRO_DEFAULT) && (!imageOps._fwImgInfo.ext_info.roms_info.exp_rom_found))) { // No ROM in image
        if (!IntegrateDevRomInImage(imageOps)) {
            return false;
        }
    }

    // Guids patch
    _burnBlankGuids = burnParams.blankGuids;
    bool  isGuidsSpecified  =  burnParams.userMacsSpecified || burnParams.userGuidsSpecified ||
            burnParams.userUidsSpecified;
    if (isGuidsSpecified) {
        // Get the GUIDS/MACsUIDs from the user input
        bool isBridgeX = (_fwImgInfo.ext_info.chip_type == CT_BRIDGEX);
        bool isMacAvailable = Fs2IsMacAvailable();
        if (!patchGUIDs(imageOps, isMacAvailable, isBridgeX, burnParams.userGuidsSpecified, burnParams.userMacsSpecified, burnParams.userUidsSpecified,
                (guid_t*)(&(burnParams.userUids[0])), _fs2ImgInfo.ext_info.guids, _fs2ImgInfo.ext_info.guid_num)) {
            return false;
        }
    } else if (!burnParams.useImageGuids) {
        // Get the GUIDS/MACsUIDs from the device
        if (!patchGUIDs(imageOps, true, false, false, false, false, (guid_t*)NULL,
                _fs2ImgInfo.ext_info.guids, _fs2ImgInfo.ext_info.guid_num)) {
            return false;
        }
    }
    // Patch the image VSD file
    if (burnParams.vsdSpecified || !burnParams.useImagePs) {
        if (!patchImageVsd(imageOps, burnParams.userVsd)) {
            return false;
        }
    }
    return Fs2FailSafeBurn(imageOps, !burnParams.burnFailsafe, "", burnParams.progressFunc);
}


bool Fs2Operations::Fs2IsMacAvailable()
{

    if (_fwImgInfo.ext_info.chip_type == CT_IS4 ) {
        return false;
    }
    return true;
}
bool Fs2Operations::FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc)
{
    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurn\n");
    }
    ExtBurnParams burnParams = ExtBurnParams();
    burnParams.ignoreVersionCheck = forceVersion;
    burnParams.progressFunc = progressFunc;

    return Fs2Burn((*(Fs2Operations*)imageOps), burnParams);

}

bool Fs2Operations::FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams)
{
    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurnAdvanced\n");
    }
    return Fs2Burn((*(Fs2Operations*)imageOps), burnParams);

}

bool Fs2Operations::FwBurnBlock(FwOperations *imageOps, ProgressCallBack progressFunc)
{
    FImage *fim = (FImage*)((Fs2Operations*)imageOps)->_ioAccess;

    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurnBlock\n");
    }

    return writeImage(progressFunc, 0, fim->getBuf(), fim->getBufLength());
}

bool Fs2Operations::FwReadRom(std::vector<u_int8_t>& romSect)
{
    if (!Fs2IntQuery()) {
        return false;
    }
    if (_romSect.empty()) {
        return errmsg("The FW does not contain a ROM section");
    }
    romSect = _romSect;
    return true;
}

bool Fs2Operations::FwSetMFG(fs3_guid_t baseGuid, PrintCallBack callBackFunc)
{
    // avoid compiler warrnings
    (void)baseGuid;
    (void)callBackFunc;
    return errmsg("This command is not supported for FS2 FW image.");
}

bool Fs2Operations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    // avoid compiler warrnings
    (void)baseGuid;
    (void)callBackFunc;
    return errmsg("This command is not supported for FS2 FW image.");
}

bool Fs2Operations::FwGetSection (u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage)
{
    if (sectType != H_FW_CONF && sectType != H_HASH_FILE) {
        return errmsg("Hash File section not found in the given image.");
    }
    initSectToRead(sectType);
    if (!Fs2Verify((VerifyCallBack)NULL, stripedImage)) {
        return false;
    }
    if (sectType == H_FW_CONF) {
        sectInfo = _fwConfSect;
    } else {
        sectInfo = _hashFileSect;
    }
    if (sectInfo.empty()) {
        return errmsg("Hash File section not found in the given image.");
    }
    return true;
}

bool Fs2Operations::ModifyVSDSection(const char *vsd, ProgressCallBack callBackFunc)
{
	(void)callBackFunc; /* avoid compiler warning*/
    u_int32_t length = _fwImgInfo.lastImageAddr;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!_ioAccess->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed. %s", _ioAccess->err());
    }
    // Change the VSD
    PatchInfoSect((u_int8_t*)(&data[0]) + _fs2ImgInfo.infoSectPtr - sizeof(GPH),
                  _fs2ImgInfo.infoOffs[II_VSD],
                   vsd);
    // Re-burn the new Image after modifying the VSD
    return ReburnNewImage((u_int8_t*)(&data[0]), "VSD", callBackFunc);
}

bool Fs2Operations::ReburnNewImage(u_int8_t *data, const char *feature_name, ProgressCallBack callBackFunc)
{
    u_int32_t length        = _fwImgInfo.lastImageAddr;
    //char burn_str[100];
    bool is_image = (_fname != NULL);
    bool needs_repack = (is_image && _fwImgInfo.actuallyFailsafe);

    // Burn the Image after modifying the VSD.

    // Create a fwOperations object of the modified image
    FwOperations* newOps = FwOperationsCreate((void*)data, (void*)&length, (char*)NULL, FHT_FW_BUFF);

    // Verify the new image and exit if it's not VALID.
    if (!((Fs2Operations*)newOps)->Fs2IntQuery()) {
        return errmsg("Internal error: The prepared image After modifying the %s is corrupted: %s\n", feature_name, newOps->err());
    }
    if (!is_image) {
        // Modify the flash
        if (!Fs2FailSafeBurn(*((Fs2Operations*)newOps), true, NULL, callBackFunc)) {
            return false;
        }
    } else {
        u_int8_t *striped_data = new u_int8_t[length * 2];
        u_int32_t striped_length;

        // Modify the image.
        // Update the Full image CRC.
        UpdateFullImageCRC((u_int32_t*)data, length / 4, false);

        // Re-pack the image as it was given.
        // When it was striped this function would return it to that case.
        packStripedImageData(striped_data, data, length, striped_length, needs_repack, _fwImgInfo.cntxLog2ChunkSize);

        // Re-write the image to the file.
        if (!WriteImageToFile(_fname, striped_data, striped_length)) {
            delete[] striped_data;
            return false;
       }
        delete[] striped_data;
    }
    return true;
}

bool Fs2Operations::packStripedImageData(u_int8_t *striped_data, u_int8_t *normal_data, u_int32_t length, u_int32_t &striped_length,
        bool needs_repack, u_int32_t cntxLog2ChunkSize)
{
    if (needs_repack) {
        u_int32_t chunk_size = 1 << cntxLog2ChunkSize;
        u_int32_t chunk_num = (length / chunk_size) + 1;
        striped_length = 0;

        // Loop which runs over the chunks
        for (u_int32_t i = 0; i < chunk_num; i++) {
            u_int32_t normal_index  = i * chunk_size;
            u_int32_t striped_index = normal_index * 2;

            u_int32_t size = (length - normal_index);
            u_int8_t *striped_ptr = striped_data + striped_index;

            size = (size <= chunk_size) ? size : chunk_size;
            memcpy(striped_ptr, normal_data + normal_index, size);
            striped_length += size;

            if (i != (chunk_num - 1)) {
                // Add blank chunk after all the chunks instead the last one.
                memset(striped_ptr + chunk_size, 0xff, chunk_size);
                striped_length += chunk_size;
            }
        }
    } else {
        striped_length = length;
        memcpy(striped_data, normal_data, length);
    }
    return true;

}

bool Fs2Operations::ModifyKeySection(guid_t access_key, ProgressCallBack callBackFunc)
{

    u_int32_t length = _fwImgInfo.lastImageAddr;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!_ioAccess->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed. %s\n", _ioAccess->err());
    }

    // Change the VSD
    PatchKeySect((u_int32_t*)(&data[0] + _fs2ImgInfo.infoSectPtr - sizeof(GPH)),
                  _fs2ImgInfo.infoOffs[II_HwAccessKey],
                  access_key);
    // Re-burn the new Image after modifying the VSD
    return ReburnNewImage((u_int8_t*)(&data[0]), "HW Key", callBackFunc);
}

void Fs2Operations::PatchKeySect(u_int32_t* buff, u_int32_t keyOff, guid_t hw_key)
{
    u_int32_t  infoSize = __be32_to_cpu(*(buff + 1));
    u_int32_t sectSize = sizeof(GPH) + infoSize * 4;

    u_int32_t realKeyoff = (keyOff  +  sizeof(GPH)) / 4;

    // Update the key in the buffer which is supposed to be burnt into the flash
    buff[realKeyoff]     = __cpu_to_be32(hw_key.h);
    buff[realKeyoff + 1] = __cpu_to_be32(hw_key.l);

    recalcSectionCrc((u_int8_t*)buff, sectSize);
    return;
}

bool Fs2Operations::ModifyGuidSection(guid_t *user_guids, ProgressCallBack progressFunc)
{
    u_int32_t length = _fwImgInfo.lastImageAddr;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!_ioAccess->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed: %s\n", _ioAccess->err());
    }
    // Change the GUIDs section according to the user given GUIDs
    patchGUIDsSection ((u_int32_t*)(&data[0]), _fs2ImgInfo.guidPtr, user_guids, _fs2ImgInfo.ext_info.guid_num);
    // Re-burn the new Image after modifying the GUIDs
    return ReburnNewImage((u_int8_t*)(&data[0]), "GUIDs", progressFunc);
}

bool Fs2Operations::Fs2SetGuidsForBlank(sg_params_t& sgParam)
{
    // There is blank GUIDs on the device (not image)
    u_int32_t guid_sect_addr[2] = {0};
    u_int32_t length  = _fwImgInfo.ext_info.image_size;
    if (!_ioAccess->is_flash()) {
        return errmsg("Image file is not supported.");
    }


    guid_sect_addr[0] = _fs2ImgInfo.guidPtr;

    for (int i = 0; i < 2 && guid_sect_addr[i]; i++ ) {
        u_int32_t guid_sect[MAX_GUIDS*2 + 5]; // Save room for header + crc

        if (!_ioAccess->read(guid_sect_addr[i] - 16 , guid_sect, 16)) {
            return errmsg("Failed to read guids section - flash read error (%s)\n", _ioAccess->err());
        }
        // we have blank guids so make sure we have ffff in sgParams.userGuids in the correct pos
        if (!sgParam.guidsSpecified) {
            memset(&sgParam.userGuids[0], 0xff, (sizeof(guid_t))*GUIDS);
        }
        if (!sgParam.macsSpecified) {
            memset(&sgParam.userGuids[GUIDS], 0xff, (sizeof(guid_t))*MACS);
        }
       //  patchGUIDsSection(u_int32_t *buf, u_int32_t ind, guid_t guids[MAX_GUIDS], int nguids)
        patchGUIDsSection (guid_sect, 16, &sgParam.userGuids[0], _fs2ImgInfo.ext_info.guid_num);

        if (!((Flash*)_ioAccess)->write(guid_sect_addr[i], guid_sect + 4 , _fs2ImgInfo.ext_info.guid_num * 8 + 4, true)) {
            return errmsg("flash write error (%s)\n", _ioAccess->err());
        }
    }
    if (sgParam.updateCrc) {
       // Read the image.
        vector<u_int8_t> data(length);

        if (!_ioAccess->read(0, (u_int32_t*)(&data[0]), length)) {
            return errmsg("Flash read failed: %s\n", _ioAccess->err());
        }
        // TODO: Do we need to update the CRC existing ORENK
        // Calc & Update CRC.
        u_int32_t *new_data =  (u_int32_t*)(&data[0]);
        u_int32_t crc = CalcImageCRC(new_data, length / 4);
        u_int32_ba old_dw = __be32_to_cpu(new_data[IMG_CRC_OFF / 4]);
        old_dw.range(15, 0) =  crc;
        u_int32_t new_crc_dw = CPUTO1(old_dw);

        if (!((Flash*)_ioAccess)->write(IMG_CRC_OFF, &new_crc_dw, 4, true)) {
            return errmsg("flash write error (%s).", _ioAccess->err());
        }
    }
    return true;
}

bool Fs2Operations::Fs2SetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    // avoid compiler warrnings
    (void)callBackFunc;
    //
    bool ib_dev, eth_dev, bx_dev;
    // Get the FW types
    bx_dev = _fwImgInfo.ext_info.chip_type == CT_BRIDGEX;
    SetDevFlags(_fwImgInfo.ext_info.chip_type, _fwImgInfo.ext_info.dev_type, FIT_FS2, ib_dev, eth_dev);
    guid_t* old_guids = _fwImgInfo.imageOk ? _fs2ImgInfo.ext_info.guids : NULL;
    guid_t* used_guids;

    // Patch the GUIDs and prints any needed warnings

        //resize our user guids vector to MAX_GUIDS
    sgParam.userGuids.resize(MAX_GUIDS);

    if (!preFS2PatchGUIDs(eth_dev, bx_dev, sgParam.guidsSpecified, sgParam.macsSpecified, sgParam.uidsSpecified, &sgParam.userGuids[0],
                        old_guids, &used_guids, _fs2ImgInfo.ext_info.guid_num)) {
        return false;
    }

    // Modify the guids in the burnt image and re-burn it
    if (!ModifyGuidSection(used_guids, progressFunc)) {
        return false;
    }
    return true;
}

bool Fs2Operations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc,
        ProgressCallBack progressFunc)
{
	/* avoid annoying mingw warnings*/
	(void)callBackFunc;
	(void)progressFunc;

    if (!Fs2IntQuery(true, sgParam.stripedImage)) {
        return false;
    }
    if (sgParam.userGuids.size() != MAX_GUIDS) {
        return errmsg("invalid userGuid vector size given in sgParams.");
    }
    if (_fs2ImgInfo.ext_info.blank_guids) {
        return Fs2SetGuidsForBlank(sgParam);
    }
    return Fs2SetGuids(sgParam, callBackFunc, progressFunc);
}


bool Fs2Operations::FwBurnRom(FImage* romImg, bool ignoreProdIdCheck, bool ignoreDevidCheck, ProgressCallBack progressFunc)
{
    // we dont support adding rom to an image just yet
    if (!_ioAccess->is_flash()) {
        return errmsg("Burn ROM not supported for FS2 image.");
    }
    //make sure we dont get fwImage instead of rom file

    u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
    u_int32_t cntx_image_num;
    CntxFindAllImageStart(romImg, cntx_image_start, &cntx_image_num);
    if (cntx_image_num != 0) {
        return errmsg("Expecting an expansion ROM image, Recieved Mellanox FW image.");
    }

    if (!Fs2IntQuery()) {
        return false;
    }

    if (_fwImgInfo.ext_info.chip_type != CT_CONNECTX) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type %d", _fwImgInfo.ext_info.dev_type);
    }

    if (_romSect.empty() && !IsFwSupportingRomModify(_fwImgInfo.ext_info.fw_ver)) {
        return errmsg("It is not allowed to burn ROM on device which has fw: %d.%d.%d that doesn't contain ROM.", _fwImgInfo.ext_info.fw_ver[0],
                   _fwImgInfo.ext_info.fw_ver[1], _fwImgInfo.ext_info.fw_ver[2]);
    }

    if (!ignoreProdIdCheck && _fs2ImgInfo.infoOffs[II_ProductVer]) {
        return errmsg("The device FW contains common FW/ROM Product Version - The ROM cannot be updated separately.");
    }
    u_int32_t length        = _fwImgInfo.lastImageAddr;
    u_int32_t new_data_size = length + TOTAL_SEC_SIZE(romImg->getBufLength());
    vector<u_int8_t> data(length);
    vector<u_int8_t> new_data(new_data_size);

    // Read the image.
    if (!_ioAccess->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash read failed: %s", _ioAccess->err());
    }

    u_int32_t new_image_size;

    // Insert the rom to the image.
    if(!UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(&data[0]),
                             (u_int8_t*)romImg->getBuf(), romImg->getBufLength(),
                             (int*)&new_image_size)) {
        return false;
    }
    // open the image
    FwOperations* newOps = FwOperationsCreate((void*)&new_data[0], (void*)&new_image_size, (char*)NULL, FHT_FW_BUFF);
    if (!newOps) {
        return errmsg("Internal error: The prepared image is corrupted.");
    }

    if (!((Fs2Operations*)newOps)->Fs2Verify((VerifyCallBack)NULL,false, false, false, true) || !((Fs2Operations*)newOps)->Fs2Query()) {
        errmsg("Internal error: The prepared image is corrupted: %s", newOps->err());
        newOps->FwCleanUp();
        delete newOps;
        return false;
    }
    // init fw_info_t struct for checkMatchingExpRomDevId
    fw_info_t info;
    info.fw_type = FIT_FS2;
    info.fw_info = ((Fs2Operations*)newOps)->_fwImgInfo.ext_info;
    //no need to init the fs2_info part of fw_info_t as the function doesnt use it.

    if (!ignoreDevidCheck && !FwOperations::checkMatchingExpRomDevId(info)) {
        errmsg("Image file ROM: FW is for device %d, but Exp-ROM is for device %d\n", ((Fs2Operations*)newOps)->_fwImgInfo.ext_info.dev_type,\
                ((Fs2Operations*)newOps)->_fwImgInfo.ext_info.roms_info.exp_rom_com_devid);
        newOps->FwCleanUp();
        delete newOps;
        return false;
    }

    bool rc = Fs2FailSafeBurn(*((Fs2Operations*)newOps), true, "Burning ROM image", progressFunc);
    newOps->FwCleanUp();
    delete newOps;
    return rc;
}

bool Fs2Operations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    // we dont support delete rom in FS2 image yet
    if (!_ioAccess->is_flash()) {
        return errmsg("Delete ROM not supported for FS2 image.");
    }
    // Verify to get some parameters
    if (!Fs2IntQuery()) {
        return false;
    }

    if (_fwImgInfo.ext_info.chip_type != CT_CONNECTX) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type %d", _fwImgInfo.ext_info.dev_type);
    }
    if (_romSect.empty()) {
        return errmsg("The FW does not contain a ROM section.");
    }

    if (!IsFwSupportingRomModify(_fwImgInfo.ext_info.fw_ver)) {
        return errmsg("Unsupported Fw version (%d.%d.%d).", _fwImgInfo.ext_info.fw_ver[0],
                   _fwImgInfo.ext_info.fw_ver[1], _fwImgInfo.ext_info.fw_ver[2]);
    }

    if (!ignoreProdIdCheck && _fs2ImgInfo.infoOffs[II_ProductVer]) {
        return errmsg("The device FW contains common FW/ROM Product Version - The ROM cannot be removed separately.\n");
    }

    u_int32_t length        = _fwImgInfo.lastImageAddr;
    vector<u_int8_t> data(length);
    vector<u_int8_t> new_data(length);

    // Read the image.
    if (!_ioAccess->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash read failed: %s\n", _ioAccess->err());
    }
    int new_image_size;
    if(!UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(&data[0]),
                             NULL, 0, &new_image_size)) {
        return errmsg("%s", _ioAccess->err());
    }

    // Burn the Image after the ROM was removed.
    FwOperations* newOps = FwOperationsCreate((void*)&new_data[0], (void*)&new_image_size, (char*)NULL, FHT_FW_BUFF);
    if (!newOps) {
        return errmsg("Internal error: The prepared image after removing the ROM is corrupted.");
    }

    // To verify the new image and exit if it's not VALID.
    if (!((Fs2Operations*)newOps)->Fs2Verify((VerifyCallBack)NULL,false, false, false, true) || !((Fs2Operations*)newOps)->Fs2Query()) {
        errmsg("Internal error: The prepared image after removing the ROM is corrupted: %s", newOps->err());
        newOps->FwCleanUp();
        delete newOps;
        return false;
    }
    bool rc = Fs2FailSafeBurn(*((Fs2Operations*)newOps), true, "Removing ROM image", progressFunc);
    newOps->FwCleanUp();
    delete newOps;
    return rc;
}

bool Fs2Operations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    // avoid compiler warrnings
    (void)printFunc;
    //
    if (!Fs2IntQuery()) {
        return false;
    }
    if (_fwImgInfo.ext_info.chip_type != CT_CONNECTX) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type %d", _fwImgInfo.ext_info.dev_type);
    }

    if (!_fs2ImgInfo.infoOffs[II_VSD]) {
        return errmsg("No info section on the image.");
    }

    if (strlen(vsdStr) > VSD_LEN) {
    	return errmsg("VSD string is too long(%d), max allowed length: %d", (int)strlen(vsdStr), VSD_LEN);
    }

    if (!ModifyVSDSection(vsdStr, progressFunc)) {
        return false;
    }
    return true;
}

bool Fs2Operations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    // avoid compiler warrnings
    (void)vpdFileStr;
    (void)callBackFunc;
    return errmsg("Setting VPD is not supported in FS2 image format.");
}

bool Fs2Operations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
	/*avoid compiler warning*/
	(void)progressFunc;
    if (!Fs2IntQuery()) {
        return false;
    }
    if (_fwImgInfo.ext_info.chip_type != CT_CONNECTX) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type %d", _fwImgInfo.ext_info.dev_type);
    }

    if (!_fs2ImgInfo.infoOffs[II_HwAccessKey]) {
        return errmsg("The image does not support this operation.");
    }

    if (!ModifyKeySection(userKey, progressFunc)) {
        return false;
    }
    return true;

}

bool Fs2Operations::FwResetNvData()
{

    if (!_ioAccess->is_flash()) {
    	return errmsg("Cannot perform operation on Image");
    }

    if (!Fs2IntQuery()) {
        return false;
    }
    u_int32_t devId = _ioAccess->get_dev_id();
    if ( devId != CX3_HW_ID && devId != CX3_PRO_HW_ID ) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type(%d). Can only perform operation on CX3/CX3-PRO ", _fwImgInfo.ext_info.dev_type);
    }

    if (_fs2ImgInfo.fw_sector_size == 0) {// if fw was generated with old mft i.e without the fw_sector_size than we dont allow this operation
        return errmsg("Firmware was generated with old MFT, please use MFT-3.6.0 or above");
    }

    // find configuration section base addr = (flash size - (config_sectors + config_pad)*64k)

    u_int32_t availFlashSize = _fwImgInfo.actuallyFailsafe ? (_ioAccess->get_size()/2) : _ioAccess->get_size();
    u_int32_t fwSectorSz = _fs2ImgInfo.fw_sector_size != 0 ? _fs2ImgInfo.fw_sector_size : getDefaultSectorSz();
    u_int32_t reservedArea = _fs2ImgInfo.ext_info.config_sectors * fwSectorSz;
    reservedArea = reservedArea > MAX_CONFIG_AREA_SIZE ? MAX_CONFIG_AREA_SIZE : reservedArea;
    u_int32_t configBaseAddr;
	if (_fwImgInfo.actuallyFailsafe) {
		configBaseAddr = availFlashSize  - (reservedArea + _fs2ImgInfo.ext_info.config_pad * fwSectorSz) ;
	} else {
		// For non FS image, there's an optional offset + 2 consecutive config areas
        configBaseAddr = availFlashSize - (reservedArea* 2 + (_fs2ImgInfo.ext_info.config_pad * fwSectorSz));
	}

    //printf("-D- config_sectors:0x%x config_pads: 0x%x , sector_size:0x%x, configBaseAddr:0x%x, flashSize:0x%x\n",
			//_fs2ImgInfo.ext_info.config_sectors, _fs2ImgInfo.ext_info.config_pad, fwSectorSz,configBaseAddr, availFlashSize);

	//erase addresses : [configBaseAddr..AvailFlashSize]
    u_int32_t sectorSize = _ioAccess->get_sector_size();
    u_int32_t configEndAddr = availFlashSize - (_fs2ImgInfo.ext_info.config_pad * fwSectorSz);
	for (u_int32_t eraseAddr=configBaseAddr; eraseAddr < configEndAddr; eraseAddr+=sectorSize ) {
		if (!((Flash*)_ioAccess)->erase_sector(eraseAddr)) {
			return errmsg("failed to erase configuration address: 0x%x. %s", eraseAddr, _ioAccess->err());
		}
		if (_fwImgInfo.actuallyFailsafe) { // erase config sectors on the other half aswell
			((Flash*)_ioAccess)->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, !(_fwImgInfo.imgStart != 0));
			if (!((Flash*)_ioAccess)->erase_sector(eraseAddr)) {
				((Flash*)_ioAccess)->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, (_fwImgInfo.imgStart != 0));;
				return errmsg("failed to erase configuration address: 0x%x. %s", eraseAddr, _ioAccess->err());
			}
			// restore address converter
			((Flash*)_ioAccess)->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, (_fwImgInfo.imgStart != 0));
		}
	}
    return true;

}

bool Fs2Operations::FwShiftDevData(PrintCallBack progressFunc)
{
    // avoid compiler warrnings
    (void)progressFunc;
    return errmsg("Shifting device data sections is not supported in FS2 image format.");
}

const char* Fs2Operations::FwGetResetRecommandationStr()
{
    if (!_devName) {// not an mst device
        return NULL;
    }
    return NULL;
}
