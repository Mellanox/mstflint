/*
 *
 * flint_ops.cpp- FLash INTerface
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
 *  Version: $Id: flint_ops.cpp 7522 2011-11-16 15:37:21Z mohammad $
 *
 */


#include "flint_ops.h"

extern bool _print_crc;
extern bool _silent;
extern bool _assume_yes;
extern bool _assume_no;

extern const char* g_sectNames[];


const u_int32_t Operations::_cntx_magic_pattern[4] = {
    0x4D544657,   // Ascii of "MTFW"
    0x8CDFD000,   // Random data
    0xDEAD9270,
    0x4154BEEF
};

const u_int32_t Operations::_cntx_image_start_pos[Operations::CNTX_START_POS_SIZE] = {
    0,
    0x10000,
    0x20000,
    0x40000,
    0x80000,
    0x100000,
    0x200000
};

#define ITOC_ASCII 0x49544f43
#define DTOC_ASCII 0x64544f43
#define TOC_RAND1  0x04081516
#define TOC_RAND2  0x2342cafa
#define TOC_RAND3  0xbacafe00

const u_int32_t Operations::_itoc_signature[4] = {
    ITOC_ASCII,   // Ascii of "MTFW"
    TOC_RAND1,   // Random data
    TOC_RAND2,
    TOC_RAND3
};


const Operations::HwDevData Operations::hwDevData[] = {
    { "InfiniHost",        TAVOR_HW_ID, 2, {23108, 0}},
    { "InfiniHost III Ex", ARBEL_HW_ID, 2, {25208, 25218, 0}},
    { "InfiniHost III Lx", SINAI_HW_ID, 1, {25204, 0}},
    { "ConnectX",          CX_HW_ID, 2, {25408, 25418, 26418, 26438,
                                         26428, 25448, 26448, 26468,
                                         25458, 26458, 26478, 26488,
                                         4097, 4098, 0}},
    { "ConnectX3",        CX3_HW_ID, 2, {4099, 4101, 4105, 4107,
                                         4109, 4111, 0}},
    { "CONNECT_IB",        CONNECT_IB_HW_ID, 2, {4113, 4115, 4117, 4119,
                                         4121, 4123, 0}},

    { "InfiniScale IV",   IS4_HW_ID,  0, {48436, 48437, 48438, 0}},
    { "BridgeX",          BRIDGEX_HW_ID, 0, {64102, 64112, 64122, 0}},
    { "SwitchX",          SWITCHX_HW_ID,  0, {51000, 0}},
    { "ConnectX3 Pro",    CX3_PRO_HW_ID,  0, {4103, 0}},
    { NULL ,              0, 0, {0}},// zero devid terminator
};

const Operations::HwDev2Str Operations::hwDev2Str[] = {
        {"ConnectIB",         CONNECT_IB_HW_ID, 0x00},
        {"ConnectX",          CX_HW_ID,         0xA0},
        {"ConnectX-2",        CX_HW_ID,         0xB0},
        {"ConnectX-3 A0",     CX3_HW_ID,        0x00},
        {"ConnectX-3 A1",     CX3_HW_ID,        0x01},
        {"SwitchX A0",        SWITCHX_HW_ID,    0x00},
        {"SwitchX A1",        SWITCHX_HW_ID,    0x01},
        {"BridgeX",           BRIDGEX_HW_ID,    0xA0},
        {"InfiniScale IV A0", IS4_HW_ID,        0xA0},
        {"InfiniScale IV A1", IS4_HW_ID,        0xA1},
        {"InfiniHost A0",     TAVOR_HW_ID,      0xA0},
        {"InfiniHost A1",     TAVOR_HW_ID,      0xA1},
        {"InfiniHost III Lx", SINAI_HW_ID,      0xA0},
        {"InfiniHost III Ex", ARBEL_HW_ID,      0xA0},
        {"ConnectX-3 Pro",    CX3_PRO_HW_ID,    0x0},
        { NULL ,              0,                0x00}, // zero device ID terminator
};


#define MFG_INFO "MFG_INFO"

const Operations::SectionInfo Operations::_fs3_sections_info_arr[] = {
    {FS3_END,           "END"},
    {FS3_ITOC,          "ITOC_Header"},

    {FS3_BOOT_CODE,     "BOOT_CODE"},
    {FS3_PCI_CODE,      "PCI_CODE"},
    {FS3_MAIN_CODE,     "MAIN_CODE"},
    {FS3_PCIE_LINK_CODE, "PCIE_LINK_CODE"},
    {FS3_IRON_PREP_CODE, "IRON_PREP_CODE"},
    {FS3_POST_IRON_BOOT_CODE, "POST_IRON_BOOT_CODE"},
    {FS3_HW_BOOT_CFG,   "HW_BOOT_CFG"},
    {FS3_HW_MAIN_CFG,   "HW_MAIN_CFG"},
    {FS3_IMAGE_INFO,    "IMAGE_INFO"},
    {FS3_FW_BOOT_CFG,   "FW_BOOT_CFG"},
    {FS3_FW_MAIN_CFG,   "FW_MAIN_CFG"},
    {FS3_ROM_CODE,      "ROM_CODE"},
    {FS3_DBG_LOG_MAP,   "DBG_LOG_MAP"},
    {FS3_DBG_FW_INI,    "DBG_FW_INI"},
    {FS3_DBG_FW_PARAMS, "DBG_FW_PARAMS"},
    {FS3_FW_ADB,        "FW_ADB"},

    {FS3_MFG_INFO,      MFG_INFO},
    {FS3_DEV_INFO,      "DEV_INFO"},
    {FS3_NV_DATA,       "NV_DATA"},
    {FS3_VPD_R0,        "VPD_R0"},
};


//
// Asks user a yes/no question.
// Returns true if user chose Y, false if user chose N.
//

bool Operations::ask_user(const char *question) {
    if (question == NULL) {
        printf("\n Do you want to continue ? (y/n) [n] : ");
    } else {
        printf("\n %s ? (y/n) [n] : ", question);

    }

    if (_assume_yes)
        printf("y\n");
    else {
        char ansbuff[32];
        ansbuff[0] = '\0';
        if (_assume_no) {
            printf("n\n");
            sprintf(_err_msg, "-no flag is set\n");
            return false;
        }
        if (_ignore_tty == false) {
            if (!isatty(0)) {
                sprintf(_err_msg, "Not on tty - Can not interact. assuming \"no\"\n");
                return false;
            }
        }
        fflush(stdout);
        fgets(ansbuff, 30, stdin);

        if (  strcmp(ansbuff, "y\n") &&
              strcmp(ansbuff, "Y\n") &&
              strcmp(ansbuff, "yes\n") &&
              strcmp(ansbuff, "Yes\n") &&
              strcmp(ansbuff, "YES\n"))  {

            sprintf(_err_msg, "Aborted by user\n");
            return false;
        }

    }
    return true;
}



bool Operations::write_image(Flash& f, u_int32_t addr, void *data, int cnt, bool need_report, const char* message,
                             bool new_line, bool is_phys_addr, char *fimage)
{
    u_int8_t   *p = (u_int8_t *)data;
    u_int32_t  curr_addr = addr;
    u_int32_t  towrite = cnt;
    u_int32_t  perc = 0xffffffff;
    bool rc;

    // printf("-D- towrite = %#x, need_report = %d\n", towrite, need_report);

    while (towrite) {
        // Write
        int trans;
        if (fimage == NULL) {
            trans = (towrite > (int)Flash::TRANS) ? (int)Flash::TRANS : towrite;
            if (is_phys_addr) {
                rc = f.write_phy(curr_addr, p, trans);
            } else {
                rc = f.write(curr_addr, p, trans);
            }
            if (!rc) {
                return errmsg("Flash write failed: %s", f.err());
            }
        } else {
            trans = towrite;
            if (!ModifyImageFile(fimage, curr_addr, p, trans)) {
                return false;
            }
        }
        p += trans;
        curr_addr += trans;
        towrite -= trans;

        // Report
        if (need_report) {
            u_int32_t new_perc = ((cnt - towrite) * 100) / cnt;

            if (new_perc != perc) {
                printf("\r%s%%%03d", message, new_perc);
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    if (need_report) {

        printf("\r%sOK  ", message);
        if (new_line) {
            printf("\n");
        }
        fflush(stdout);
    }

    return true;
} //  Flash::

#define MY_MAX(a, b) ((a) > (b) ? (a) : (b))

bool Operations::GetMaxImageSize(u_int32_t flash_size, u_int32_t sector_size, ImageInfo* image_info, ImageInfo* flash_info, u_int32_t &max_image_size)
{
    // Non-configurable image or the user asked to ignore the configuration section
    u_int32_t config_sectors = MY_MAX(image_info->configSectors, flash_info->configSectors);
    if (image_info->isFailsafe) {
        max_image_size = (flash_size / 2) - ((config_sectors + flash_info->configPad) * sector_size);
    } else {
        // For non FS image, there's an optional offset + 2 consecutive config areas
        max_image_size = flash_size - (config_sectors * 2 + flash_info->configPad) * sector_size;
    }

    return true;
}

#define RESTORING_MSG "Restoring signature"
#define ERASE_MESSAGE "    Please erase them by using the command: \"" MLXCONFIG_CMD " " ERASE_CMD "\" and then re-burn"
bool Operations::CntxFailSafeBurn(Flash&    f,
                                  FImage&   fim,
                                  bool      need_report,
                                  Operations::ImageInfo* flash_info,
                                  Operations::ImageInfo* image_info,
                                  bool      allow_nofs,
                                  const char* pre_message) {

    // TODO: See getBuf effect on zebra image.
    u_int8_t  *data8      = (u_int8_t *) fim.getBuf();
    int        image_size = fim.getBufLength();
    u_int32_t  zeroes     = 0;
    char message[128], message1[128], buff[128];
    bool is_curr_image_in_odd_chunks;

    //printf("-D- image_info->blankGuids: %#x, flash_info: %#x, burn_blank: %#x\n", image_info->blankGuids,
    //       flash_info->blankGuids, _burn_blank_guids);
    // Update CRC.
    UpdateFullImageCRC(fim.getBuf(), image_size / 4, image_info->blankGuids | _burn_blank_guids); // size in dwords

    // TODO: Do we need the verify ORENK
    Operations::ImageInfo file_info;
    bool curr_silent = _silent;
    _silent = true;
    if (!Verify(fim, &file_info) || !QueryAll(fim, &file_info)) {
        return errmsg("Internal error: Got bad image after updating the CRC. %s", err());
    }
    _silent = curr_silent;

    if (!allow_nofs) {
        if (!image_info->isFailsafe) {
            return errmsg("The given image is not a failsae image");
        }

        if (flash_info->cntxLog2ChunkSize != image_info->cntxLog2ChunkSize) {
            return errmsg("Failsafe chunk sizes in flash (0x%x) and in image (0x%x) are not the same.",
                          1 << flash_info->cntxLog2ChunkSize,
                          1 << image_info->cntxLog2ChunkSize);
        }
    }

    u_int32_t max_image_size;
    if (!GetMaxImageSize(f.get_size(), f.get_sector_size(), image_info, flash_info, max_image_size)) {
        return false;
    }

    // Check if size of image is OK
    if (image_info->imageSize > max_image_size) {
        return errmsg("Image size (0x%x) is greater than the available flash space (0x%x).",
                 image_info->imageSize, max_image_size);

    }
    u_int32_t new_image_start;

    if (flash_info->imgStart != 0) {
        is_curr_image_in_odd_chunks = 1;
        new_image_start = 0;
    } else {
        is_curr_image_in_odd_chunks = 0;
        new_image_start = (1 << image_info->cntxLog2ChunkSize);
    }

    //printf("-I- Chunk=%x . Cur image start=%x burning from %x, flash_log2_chunk_size=%d\n",
    //       1 << flash_info->cntxLog2ChunkSize,
    //       flash_info->imgStart,
    //       new_image_start,
    //       flash_info->cntxLog2ChunkSize);

    if (image_info->isFailsafe) {
        f.set_address_convertor(image_info->cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);
    } else {
        f.set_address_convertor(0,0);
        new_image_start = 0;
    }

    // Go ahead and burn!
    //const char* image_name = new_image_start == 0 ? "first" : "second";
    report("\n");
    if (pre_message == NULL) {
        sprintf(message, "Burning FW image without signatures");
    } else {
        sprintf(message, pre_message);
    }
    int str_len = strlen(message), restore_len = strlen(RESTORING_MSG);
    str_len = (restore_len > str_len) ? restore_len : str_len;

    sprintf(buff, "%%-%ds  - ", str_len);

    sprintf(message1, buff,  message);


    if (!write_image(f, 16 , data8 + 16, image_size - 16, need_report, message1)) {
        report("FAILED\n\n");
        return false;
    }

    report(buff, RESTORING_MSG);

    fflush(stdout);

    // Write new signature
    if (!f.write(0, data8, 16, true)) {
        report("FAILED\n\n");
        return false;
    }
    bool boot_address_was_updated = true;
    // Write new image start address to crspace (for SW reset)
    if (!f.update_boot_addr(new_image_start)) {
        boot_address_was_updated = false;
    }

    if (image_info->isFailsafe) {
        if (allow_nofs) {
            // When burning in nofs, remnant of older image with different chunk size
            // may reside on the flash -
            // Invalidate all images marking on flash except the one we've just burnt

            u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
            u_int32_t cntx_image_num;
            u_int32_t i;

            CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);
            // Address convertor is disabled now - use phys addresses
            for (i = 0; i < cntx_image_num; i++) {
                if (cntx_image_start[i] != new_image_start) {
                    if (!f.write(cntx_image_start[i], &zeroes, sizeof(zeroes), true)) {
                        report("FAILED\n\n");
                        return false;
                    }
                }
            }
        } else {
            // invalidate previous signature
            f.set_address_convertor(image_info->cntxLog2ChunkSize, is_curr_image_in_odd_chunks);
            if (!f.write(0, &zeroes, sizeof(zeroes), true)) {
                report("FAILED\n\n");
                return false;
            }
        }
    }
    report("OK  \n");
    if (boot_address_was_updated == false) {
        report_warn("Failed to update FW boot address. Power cycle the device in order to load the new FW.\n");
    }
    return true;
}




////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        VERIFY FLASH                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////


//
// Cntx image verification flow:
//
// The "zebra"failsafe scheme presents few problems:
// - Need to search for a valid image in the flash.
// - handle no image / more than a single valid image cases
// - check image actual start location(s) vs. fs_zebra_size field in the image.
// - Image file is not striped though its fs_zebra_size sais it is - need to allow that
//   when checking a file.
//
// Verification flow:
//
// 1. Find image start addresses.
//    if num of start_addr not in [1,2] - Error - corrupted flash
// 2. for each start_addr:
//      Check that its fs_zebra_size is identical to other images (if exists)
//      For Flash:
//          Set address translation according to the fs_zebra_size.
//      For File:
//          *GUESS* if image is contiguous or striped. This can be according
//          to the file size vs. image size field in the image.
//          Set address translation according to the fs_zebra_size or to 0.
//      verify - same as previous projects nofs image, with the aditional start
//


bool Operations::CntxFindMagicPattern       (FBase& f,  u_int32_t addr) {
    int i;
    if (addr + 16 > f.get_size()) {
        return false;
    }
    for (i = 0; i < 4 ; i++) {
        u_int32_t w;
        READ4(f, addr + i * 4, &w, "Magic Pattern" );
        TOCPU1(w);
        if (w != _cntx_magic_pattern[i]) {
            //printf("-D- Looking for magic pattern %d addr %06x: Exp=%08x Act=%08x\n", i, addr + i * 4, _cntx_magic_pattern[i], w);
            return false;
        }
    }

    return true;
}

// FindAllImageStart
// OUT: start_locations: set to the start addresses of the found image markers (in accending order)
// OUT: found_images:    Number of found images (and number of valid entries in the start_locations array).
bool Operations::CntxFindAllImageStart       (FBase& f,  u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images) {
    int i;
    int needed_pos_num;

    needed_pos_num = CNTX_START_POS_SIZE;

    if (f.is_flash()) {
        if ( (((Flash*)&f)->get_dev_id() == 400) ||
             (((Flash*)&f)->get_dev_id() == 435) ||
             (((Flash*)&f)->get_dev_id() == 6100)) {
            needed_pos_num = OLD_CNTX_START_POS_SIZE;
        }
    }

    f.set_address_convertor(0,0);
    *found_images = 0;
    for (i = 0; i < needed_pos_num; i++) {
        if (CntxFindMagicPattern(f, _cntx_image_start_pos[i])) {
            start_locations[*found_images] = _cntx_image_start_pos[i];
            (*found_images)++;
        }
    }

    return true;
}
#define BAD_CRC_MSG "Bad CRC."

bool Operations::checkBoot2(FBase& f, u_int32_t beg, u_int32_t offs,
                            u_int32_t& next, const char *pref, ImageInfo* image_info /* Maybe NULL */)
{
    u_int32_t    size;

    vector<u_int8_t> info_buff_vect(strlen(pref) + 512);
    char* pr = (char*)(&info_buff_vect[0]);

    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs+beg);

    // Size
    READ4(f, offs+beg+4, &size, pr);
    TOCPU1(size);
    if (size > 1048576 || size < 4) {
        report("%s /0x%08x/ - unexpected size (0x%x)\n", pr, offs+beg+4, size);
        return false;
    }
    if (image_info != NULL) {
        image_info->boot_size = (size + 4) * 4;
    }

    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, offs+beg,
            offs+beg+(size+4)*4-1, (size+4)*4);

    if (_is_full_verify == true) {
        Crc16        crc;
        vector<u_int8_t> buff_vect((size + 4)*sizeof(u_int32_t));
        u_int32_t    *buff = (u_int32_t*)(&buff_vect[0]);

        READBUF(f, offs+beg, buff, size*4 + 16, pr);
        if (image_info != NULL) {
            Fs3UpdateImgCache(image_info, (u_int8_t*)buff, offs+beg, size*4 + 16);
        }
         TOCPUn(buff, size+4);
        CRC1n(crc, buff, size+4);
        CRC1n(f.get_image_crc(), buff, size+4);


        crc.finish();

        u_int32_t crc_act = buff[size+3];
        if (crc.get() != crc_act) {
            report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
                   pr, offs+beg, crc.get(), crc_act);
            return errmsg(BAD_CRC_MSG);
        }
        f.get_image_crc() << crc_act;

        if (_print_crc)
            report("%s - OK (CRC:0x%04x)\n", pr, (crc_act & 0xffff));
        else
            report("%s - OK\n", pr);
    }
    next = offs + size*4 + 16;
    return true;
} // checkBoot2

static int part_cnt;

bool Operations::GetSectData(std::vector<u_int8_t>& file_sect, const u_int32_t *buff, const u_int32_t size) {

    file_sect.clear();
    file_sect.insert(file_sect.end(),
                     vector<u_int8_t>::iterator((u_int8_t*)buff),
                     vector<u_int8_t>::iterator((u_int8_t*)buff + size));


    return true;
}

bool Operations::CheckAndPrintCrcRes(char* pr, bool blank_crc, u_int32_t off, u_int32_t crc_act, u_int32_t crc_exp, bool ignore_crc)
{

    if (!blank_crc && crc_exp != crc_act) {
        report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, off, crc_exp, crc_act);
        return errmsg(BAD_CRC_MSG);
    }
    if (_print_crc) {
        report("%s - OK (CRC:0x%04x)\n", pr, crc_act & 0xffff);
    } else {
        if (ignore_crc) {
            report("%s - CRC IGNORED\n", pr);
        } else {
            if (blank_crc) {
                report("%s - BLANK CRC (0xffff)\n", pr);
            } else {
                report("%s - OK\n", pr);
            }
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
bool Operations::checkGen(FBase& f, u_int32_t beg,u_int32_t offs,
                          u_int32_t& next, const char *pref, ImageInfo* info)
{
    vector<u_int8_t> info_buff_vect(strlen(pref) + 100);
    char* pr = (char*)(&info_buff_vect[0]);

    char         unknown_sect_name[128];
    const char*  sect_name;

    u_int32_t    size = 0;
    GPH          gph;
    bool is_sect_to_read;
    // printf("-D- checkGen ... \n");
    // GPH
    sprintf(pr, "%s /0x%08x/ (GeneralHeader)", pref, offs+beg);
    READBUF(f, offs + beg, &gph, sizeof(GPH), pr);
    TOCPUBY(gph);

    // Body
    part_cnt++;

    // May be BOOT3?
    if (gph.type < H_FIRST  ||  gph.type >= H_LAST) {
        if (part_cnt > 2) {
            //report("%s /0x%x/ - Invalid partition type (%d)\n",
            //       pref, offs+beg, gph.type);
            //return false;
        } else {
            return checkBoot2(f, beg, offs, next, pref);
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
        if (f.is_flash()) {
            is_sect_to_read =  _sections_to_read[gph.type];
        } else {
            is_sect_to_read = true;
        }

    }

    sprintf(pr, CRC_CHECK_OUTPUT,
            pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
            size+(u_int32_t)sizeof(gph)+4, sect_name);

    if (size > MAX_SECTION_SIZE) {
        report("%s - size too big (0x%x)\n",
               pr, size);
        return false;
    }
    //printf("-D- gph.type = %d\n", gph.type);
    if (is_sect_to_read) {
        // CRC
        Crc16        crc;
        std::vector<u_int8_t> buffv(size);
        u_int32_t *buff = (u_int32_t*)(&(buffv[0]));

        READBUF(f, offs+sizeof(gph), buff, size, pr);

        TOCPUn(buff,size/4);
        CRCBY(crc, gph);
        CRCBY(f.get_image_crc(), gph);

        CRCn(crc, buff, size/4);
        CRCn(f.get_image_crc(), buff, size/4);
        //printf("-D- GEN: CRC is %#x\n", f.get_image_crc().get());
        crc.finish();

        u_int32_t crc_act;
        READ4(f, offs+sizeof(gph)+size, &crc_act, pr);
        TOCPU1(crc_act);
        bool blank_crc = false;


        if (gph.type == H_GUID && crc_act == 0xffff) {
            blank_crc = true;
            info->blankGuids = true;
        }

        if (!CheckAndPrintCrcRes(pr, blank_crc, offs, crc_act, crc.get())) {
            return false;

        }

        f.get_image_crc() << crc.get();
        // The image info may be null, please check that before using it.
        if (gph.type == H_FW_CONF) {
            GetSectData(_fw_conf_sect, buff, size);
        }
        if (gph.type == H_HASH_FILE) {
            GetSectData(_hash_file_sect, buff, size);
        }

        if (gph.type == H_IMG_INFO) {
            CPUTOn(buff, size/4);
            if (!ParseInfoSect((u_int8_t*)buff, size,  info)) {
                return errmsg("Failed to read the info sector: %s\n", err());
            }
        }

        if (info != NULL) {
            if (gph.type == H_ROM && info->_rom_sect.empty()) {
                GetSectData(info->_rom_sect, buff, size);
            }
        }


    }


    // mark last read addr
    _last_image_addr = offs + size + sizeof(gph) + 4;  // the 4 is for the trailing crc
    next = gph.next;

    return true;
} // checkGen


////////////////////////////////////////////////////////////////////////
bool Operations::checkList(FBase& f, u_int32_t offs, u_int32_t fw_start, const char *pref, ImageInfo* info)
{
    u_int32_t next_ptr;

    CHECKB2(f, offs, fw_start, next_ptr, pref);
    part_cnt = 1;
    while (next_ptr && next_ptr != 0xff000000)
        CHECKGN(f, offs, next_ptr, next_ptr, pref, info);

    return true;
} // checkList

////////////////////////////////////////////////////////////////////////
#define FS3_IND_ADDR 0x24
enum {
    IMG_VER_FS2 = 0,
    IMG_VER_FS3 = 3,
};
u_int8_t Operations::CheckIsFs2(FBase& f) {
    if (f.is_flash()) {
        if (  ( ((Flash*)&f)->get_dev_id() == 400)              ||
                ( ((Flash*)&f)->get_dev_id() == 435)              ||
                ( ((Flash*)&f)->get_dev_id() == CX3_HW_ID)        ||
                ( ((Flash*)&f)->get_dev_id() == SWITCHX_HW_ID)    ||
                ( ((Flash*)&f)->get_dev_id() == 6100) ||
                ( ((Flash*)&f)->get_dev_id() == CX3_PRO_HW_ID)) {
            return FS_FS2_GEN;
        } else if ( ((Flash*)&f)->get_dev_id() == CONNECT_IB_HW_ID) {
            return FS_FS3_GEN;
        }
    } else {
        u_int32_t found_images;
        u_int32_t image_start[CNTX_START_POS_SIZE];

        // Image - check if magic pattern is somewhere in the file:
        CntxFindAllImageStart(f, image_start, &found_images);
        if (found_images) {
            u_int32_t data;
            u_int8_t image_version;
            READ4(f, FS3_IND_ADDR, &data, "FS3 indication" );
            TOCPU1(data);
            image_version = data >> 24;
            if (image_version == IMG_VER_FS3) {
                return FS_FS3_GEN;
            } else {
                // TODO: if the img format version is unknown we should fail instead of considering it FS2
                return FS_FS2_GEN;
            }
        }
    }
    return FS_OLD_GEN;
}

bool Operations::CheckMac(u_int64_t mac) {
    if ((mac >> 40) & 0x1) {
        return errmsg("Multicast bit (bit 40) is set");
    }

    if (mac >> 48) {
        return errmsg("More than 48 bits are used");
    }

    return true;
}


bool Operations::CntxGetFsData(u_int32_t fs_info_word, bool& fs_en, u_int32_t& log2chunk_size) {
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


#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#define MAX_HW_NAME_LEN 100
bool Operations::HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char *hw_name)
{
    int i;

    for (i = 0;  hwDev2Str[i].hwDevId != 0; i++) {
        const HwDev2Str *hwDev2StrMem = &(hwDev2Str[i]);

        if (hwDev2StrMem->hwDevId == hw_id && hwDev2StrMem->revId == rev_id) {
            int len = strlen(hwDev2StrMem->name);
            if (len >= MAX_HW_NAME_LEN) {
                return errmsg("Internal error: Length of device name: %d exceeds the maximum allowed size: %d", len, MAX_HW_NAME_LEN - 1);
            }
            strcpy(hw_name, hwDev2StrMem->name);
            return true;
        }
    }
    // When the device or rev is unknown we use the hw ID and rev to display it.
    sprintf(hw_name, "MT%d-%02X", hw_id, rev_id);
    return true;
}

// This function gets the HW ID of the target device and the dev ID from
// the image. It then matches the 2 IDs and returns an error in case of
// missmatch. The match is not 1:1 , since the FW image contains the SW
// dev id, and a single hw dev id may match multiple SW dev IDs.
//
bool Operations::CheckMatchingHwDevId(u_int32_t hwDevId, u_int32_t rev_id, Operations::ImageInfo& info) {

    int i;
    char supp_hw_id_list[MAX_NUM_SUPP_HW_LIST_STR] = {'\0'};
    char curr_hw_id_name[MAX_HW_NAME_LEN];

    for (i = 0; i < info.supportedHwIdNum; i++) {
        u_int32_t currSupportedHwId = info.supportedHwId[i];
        u_int32_t supp_hw_id  = currSupportedHwId & 0xffff;
        u_int32_t supp_rev_id = (currSupportedHwId >> 16) & 0xff;
        u_int32_t tmp_size_of_list;
        char hw_name[MAX_HW_NAME_LEN];

        if (currSupportedHwId == 0) {
            break;
        }
        // Check if device is supported!
        if ( supp_hw_id == hwDevId && supp_rev_id == rev_id) {
            return true;
        }
        // Append checked to list of supported device in order to print it in the error if we this device is not supported

        // Get the HW name of current supported HW ID
        if (!HWIdRevToName(supp_hw_id, supp_rev_id, hw_name)) {
            return false;
        }
        // Check if we don't exceed the array size we have
        tmp_size_of_list = strlen(supp_hw_id_list) + strlen(hw_name) + 2;
        if (tmp_size_of_list >= MAX_NUM_SUPP_HW_LIST_STR) {
            return errmsg("Internal error: Size of supported devs list: %d exceeds the maximum allowed size: %d",
                    tmp_size_of_list, MAX_NUM_SUPP_HW_LIST_STR - 1);
        }

        if (supp_hw_id_list[0] == '\0') {
            sprintf(supp_hw_id_list, "%s", hw_name);
        } else {
            sprintf(supp_hw_id_list, "%s, %s", supp_hw_id_list, hw_name);
        }
    }
    // If we get here, this FW cannot be burnt in the current device.
    // Get the Device name
    if (!HWIdRevToName(hwDevId, rev_id, curr_hw_id_name)) {
        return false;
    }

    return errmsg("FW image file cannot be programmed to device %s, it is intended for: %s only",
            curr_hw_id_name, supp_hw_id_list);
}
bool Operations::CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId) {
    int i, j;
    const HwDevData* devData = NULL;
    const char* hwDevName = NULL;
    // HACK: InfiniHost III LX may have 2 HW device ids. - Map the second devid to the first.
    if (hwDevId == 24204) {
        hwDevId = 25204;
    }

    // First, find the HW device that the SW id matches
    for (i = 0; hwDevData[i].hwDevId != 0 ; i++) {
        if (hwDevData[i].hwDevId == hwDevId) {
            hwDevName = hwDevData[i].name; // TODO: Check bug if device not found
        }

        if (devData == NULL) {
            for (j = 0; hwDevData[i].swDevIds[j]; j++) {
                if (hwDevData[i].swDevIds[j] == imageDevId) {
                    devData = &hwDevData[i];
                    break;
                }
            }
        }
    }

    if (devData == NULL) {
        report_warn("Unknown device id (%d) in the given FW image. Skipping HW match check.\n",
               imageDevId);
        return true;
    } else if (devData->hwDevId != hwDevId) {
        return errmsg("Trying to burn a \"%s\" image on a \"%s\" device.",
                      devData->name,
                      hwDevName);
    }

    return true;
}

#define MISS_MATCH_DEV_ID 0xffff
#define EXP_ROM_GEN_DEVID 0

bool Operations::CheckMatchingExpRomDevId(Operations::ImageInfo* info) {
    if (info->expRomFound && info->numOfExpRom && info->infoOffs[II_DeviceType]
            && info->expRomComDevid != EXP_ROM_GEN_DEVID && info->expRomComDevid != MISS_MATCH_DEV_ID
            && info->devType != info->expRomComDevid) {
        return errmsg("FW is for device %d, but Exp-ROM is for device %d",
                info->devType, info->expRomComDevid);
    }
    return true;
}

#define ITOC_ASCII 0x49544f43
#define DTOC_ASCII 0x64544f43
#define TOC_RAND1  0x04081516
#define TOC_RAND2  0x2342cafa
#define TOC_RAND3  0xbacafe00

bool Operations::CheckTocSignature(struct cibfw_itoc_header *itoc_header, u_int32_t first_signature)
{
    if ( itoc_header->signature0 != first_signature  ||
         itoc_header->signature1 !=  TOC_RAND1       ||
         itoc_header->signature2 !=  TOC_RAND2       ||
         itoc_header->signature3 !=  TOC_RAND3) {
        return false;
    }
    return true;
}
#define UNKNOWN_SECTION "UNKNOWN"
const char *Operations::GetSectionNameByType(u_int8_t section_type) {

    for (u_int32_t i = 0; i < ARR_SIZE(_fs3_sections_info_arr); i++) {
        const SectionInfo *sect_info = &_fs3_sections_info_arr[i];
        if (sect_info->type == section_type) {
            return sect_info->name;
        }
    }
    return UNKNOWN_SECTION;
}

bool Operations::DumpFs3CRCCheck(u_int8_t sect_type, u_int32_t sect_addr, u_int32_t sect_size, u_int32_t crc_act,
        u_int32_t crc_exp, bool ignore_crc)
{
    char pr[256];
    const char *sect_type_str = GetSectionNameByType(sect_type);
    sprintf(pr, CRC_CHECK_OLD, PRE_CRC_OUTPUT, sect_addr, sect_addr + sect_size - 1, sect_size,
            sect_type_str);
    if (!strcmp(sect_type_str, UNKNOWN_SECTION)) {
        sprintf(pr + strlen(pr), ":0x%x", sect_type);
    }
    sprintf(pr + strlen(pr), ")");
    return  CheckAndPrintCrcRes(pr, 0, sect_addr, crc_exp, crc_act, ignore_crc);

}
#define TOC_HEADER_SIZE 0x20
#define TOC_ENTRY_SIZE  0x20


typedef bool (*f_get_info)  (u_int8_t *buff, Operations::ImageInfo* info);
typedef struct section_info {
    u_int8_t   type;
    f_get_info get_info_func;
} section_info_t;

bool GetMfgInfo(u_int8_t *buff, Operations::ImageInfo* info)
{
    struct cibfw_mfg_info mfg_info;
    cibfw_mfg_info_unpack(&mfg_info, buff);
    // tools_mfg_info_dump(&mfg_info, stdout);
    info->orig_fs3_uids_info = mfg_info.guids;
    strcpy(info->orig_psid, mfg_info.psid);
    info->guids_override_en = mfg_info.guids_override_en;

    return true;

}

bool GetImageInfo(u_int8_t *buff, Operations::ImageInfo* info)
{

    struct cibfw_image_info image_info;
    cibfw_image_info_unpack(&image_info, buff);
    //tools_image_info_dump(&image_info, stdout);

    info->infoOffs[Operations::II_FwVersion] = 1;
    info->fwVer[0] = image_info.FW_VERSION.MAJOR;
    info->fwVer[1] = image_info.FW_VERSION.MINOR;
    info->fwVer[2] = image_info.FW_VERSION.SUBMINOR;

    info->infoOffs[Operations::II_MicVersion] = 1;
    info->micVer[0] = image_info.mic_version.MAJOR;
    info->micVer[1] = image_info.mic_version.MINOR;
    info->micVer[2] = image_info.mic_version.SUBMINOR;


    strcpy(info->image_vsd, image_info.vsd);
    strcpy(info->psid, image_info.psid);
    return true;
}

bool GetDevInfo(u_int8_t *buff, Operations::ImageInfo* info)
{
    struct cibfw_device_info dev_info;
    cibfw_device_info_unpack(&dev_info, buff);
    // tools_device_info_dump(&dev_info, stdout);
    info->fs3_uids_info = dev_info.guids;
    strcpy(info->vsd, dev_info.vsd);
    return true;
}
bool Operations::GetImageInfoFromSection(u_int8_t *buff, u_int8_t sect_type, Operations::ImageInfo* info, u_int8_t check_support_only)
{
    section_info_t sect_info_db[] = {
            {FS3_MFG_INFO, GetMfgInfo},
            {FS3_IMAGE_INFO, GetImageInfo},
            {FS3_DEV_INFO, GetDevInfo},

    };
    for (u_int32_t i = 0; i < ARR_SIZE(sect_info_db); i++) {
        section_info_t *sect_info = &sect_info_db[i];
        if (sect_info->type == sect_type) {
            if (check_support_only) {
                return true;
            } else {
                return sect_info->get_info_func(buff, info);
            }
        }
    }
    if (check_support_only) {
        return false;
    }
    return errmsg("Getting info from section type (%s:%d) is not supported\n", GetSectionNameByType(sect_type), sect_type);
}

bool Operations::IsGetInfoSupported(u_int8_t sect_type)
{
    return GetImageInfoFromSection(NULL, sect_type, NULL, 1);
}


bool Operations::IsFs3SectionReadable(u_int8_t type)
{

    if (_read_sect_list.size()) {
        for (u_int32_t i = 0; i < _read_sect_list.size(); i++) {
            if (_read_sect_list.at(i) == type) {
                return true;
            }
        }
        return false;

    } else if (GetQuickQuery()) {
        if ( IsGetInfoSupported(type)) {
            return true;
        }
        return false;
    }
    return true;
}


bool Operations::VerifyTOC(FBase& f, Operations::ImageInfo* info, u_int32_t dtoc_addr, bool& bad_signature, bool show_itoc)
{
    u_int8_t buffer[TOC_HEADER_SIZE], entry_buffer[TOC_ENTRY_SIZE];
    struct cibfw_itoc_header itoc_header;
    bool ret_val = true, mfg_exists = false;
    u_int8_t toc_type = FS3_ITOC;
    u_int32_t phys_addr;
    bad_signature = false;


    // Read the sigmature and check it
    READBUF(f, dtoc_addr, buffer, TOC_HEADER_SIZE, "TOC Header");
    Fs3UpdateImgCache(info, buffer, dtoc_addr, TOC_HEADER_SIZE);
    cibfw_itoc_header_unpack(&itoc_header, buffer);
    memcpy(info->itoc_header, buffer, CIBFW_ITOC_HEADER_SIZE);
    // cibfw_itoc_header_dump(&itoc_header, stdout);
    u_int32_t first_signature = (toc_type == FS3_ITOC) ? ITOC_ASCII : DTOC_ASCII;
    if (!CheckTocSignature(&itoc_header, first_signature)) {
        bad_signature = true;
        return false;
    }

    u_int32_t toc_crc = CalcImageCRC((u_int32_t*)buffer, (TOC_HEADER_SIZE / 4) - 1);
    phys_addr = f.get_phys_from_cont(dtoc_addr, info->cntxLog2ChunkSize, info->imgStart != 0);
    if (!DumpFs3CRCCheck(toc_type, phys_addr, TOC_HEADER_SIZE, toc_crc, itoc_header.itoc_entry_crc)) {
        ret_val = false;
    }
    info->itoc_addr = dtoc_addr;

    int section_index = 0;
    struct cibfw_itoc_entry toc_entry;
    do {
        // Uopdate the cont address
        f.set_address_convertor(info->cntxLog2ChunkSize, info->imgStart != 0);
        u_int32_t entry_addr = dtoc_addr + TOC_HEADER_SIZE + section_index *  TOC_ENTRY_SIZE;
        READBUF(f, entry_addr , entry_buffer, TOC_ENTRY_SIZE, "TOC Entry");
        Fs3UpdateImgCache(info, entry_buffer, entry_addr, TOC_ENTRY_SIZE);

        cibfw_itoc_entry_unpack(&toc_entry, entry_buffer);
        if (toc_entry.type == FS3_MFG_INFO) {
            mfg_exists = true;
        }
        // printf("-D- toc = %#x, toc_entry.type  = %#x\n", section_index, toc_entry.type);
        if (toc_entry.type != FS3_END) {
            if (section_index + 1 >= MAX_TOCS_NUM) {
                return errmsg("Internal error: number of ITOCs %d is greater than allowed %d", section_index + 1, MAX_TOCS_NUM);
            }

            u_int32_t entry_crc = CalcImageCRC((u_int32_t*)entry_buffer, (TOC_ENTRY_SIZE / 4) - 1);
            u_int32_t entry_size_in_bytes = toc_entry.size * 4;
            // printf("-D- entru_crc = %#x, toc_entry.itoc_entry_crc = %#x\n", entry_crc, toc_entry.itoc_entry_crc);
            if (toc_entry.itoc_entry_crc == entry_crc) {
                // printf("-d- quick query: %d, supported: %d\n", GetQuickQuery(), IsGetInfoSupported(toc_entry.type));
                // if (!GetQuickQuery() || IsGetInfoSupported(toc_entry.type)) {
                if (IsFs3SectionReadable(toc_entry.type)) {

                    u_int32_t section_last_addr;
                    // Only when we have full verify or the info of this section should be collected for query
                    std::vector<u_int8_t> buffv(entry_size_in_bytes);
                    u_int8_t *buff = (u_int8_t*)(&(buffv[0]));
                    u_int32_t flash_addr = toc_entry.flash_addr << 2;
                    if (!toc_entry.relative_addr) {
                        f.set_address_convertor(0, 0);
                        phys_addr = flash_addr;
                    } else {
                        phys_addr = f.get_phys_from_cont(flash_addr, info->cntxLog2ChunkSize, info->imgStart != 0);
                    }
                    section_last_addr = phys_addr + entry_size_in_bytes;
                    _last_image_addr = (_last_image_addr >= phys_addr + section_last_addr) ? _last_image_addr : section_last_addr;

                    if (show_itoc) {
                        cibfw_itoc_entry_dump(&toc_entry, stdout);
                        DumpFs3CRCCheck(toc_entry.type, phys_addr, entry_size_in_bytes, 0, 0, true);
                    } else {
                        READBUF(f, flash_addr, buff, entry_size_in_bytes, "Section");
                        Fs3UpdateImgCache(info, buff, flash_addr, entry_size_in_bytes);
                        u_int32_t sect_crc = CalcImageCRC((u_int32_t*)buff, toc_entry.size);

                        //printf("-D- flash_addr: %#x, toc_entry_size = %#x, actual sect = %#x, from itoc: %#x\n", flash_addr, toc_entry.size, sect_crc,
                        //        toc_entry.section_crc);
                        if (!DumpFs3CRCCheck(toc_entry.type, phys_addr, entry_size_in_bytes, sect_crc, toc_entry.section_crc)) {
                            ret_val = false;
                        } else {
                            GetSectData(info->tocArr[section_index].section_data, (u_int32_t*)buff, toc_entry.size * 4);
                            if (IsGetInfoSupported(toc_entry.type)) {
                                 if (!GetImageInfoFromSection(buff, toc_entry.type, info)) {
                                     return false;
                                 }
                            } else if (toc_entry.type == FS3_DBG_LOG_MAP) {
                                 TOCPUn(buff, toc_entry.size);
                                 GetSectData(_fw_conf_sect, (u_int32_t*)buff, toc_entry.size * 4);
                            }
                        }
                    }
                 }
             } else {

                 // printf("-D- CRC issue in ITOC entry\n");
                 // TODO: print crc error
                 // printf("-D- Bad ITOC CRC: toc_entry.itoc_entry_crc = %#x, actual crc: %#x, entry_size_in_bytes = %#x\n", toc_entry.itoc_entry_crc,
                 //        entry_crc, entry_size_in_bytes);
                 ret_val = false;
            }

            info->tocArr[section_index].entry_addr = entry_addr;
            info->tocArr[section_index].toc_entry = toc_entry;
            memcpy(info->tocArr[section_index].data, entry_buffer, CIBFW_ITOC_ENTRY_SIZE);
        }
        section_index++;
    } while (toc_entry.type != FS3_END);
    info->num_of_itocs = section_index - 1;

    if (!mfg_exists) {
        return errmsg("No \""MFG_INFO"\" info section.");
    }
    return ret_val;
}

bool Operations::Fs3UpdateImgCache(Operations::ImageInfo* info, u_int8_t *buff, u_int32_t addr, u_int32_t size)
{
    // vector<u_int8_t>::iterator it;
    u_int32_t min_required_size = addr + size;
    u_int32_t i;

    if (info->_image_cache.size() < min_required_size) {
        info->_image_cache.resize(min_required_size);
    }
    for (i = 0; i < size; i++) {
        info->_image_cache.at(addr + i) = buff[i];
    }
    return true;
}
#define BASE_STR "Base"
#define PRINT_FS3_UID(uid1, str) report("%-16s %016llx        %d        %d\n", str, uid1.uid, uid1.num_allocated, uid1.step);
#define PRINT_FS3_UIDS(uid1, uid2, str) {\
    PRINT_FS3_UID(uid1, BASE_STR" "str":");\
    if (uid1.uid !=  uid2.uid || uid1.num_allocated != uid2.num_allocated  || uid1.step != uid2.step) {\
        PRINT_FS3_UID(uid2, "Orig " BASE_STR " "str":");\
    } \
}
bool Operations::Fs3GetItocInfo(struct toc_info *tocArr, int num_of_itocs, fs3_section_t sect_type, struct toc_info *&curr_toc)
{
    for (int i = 0; i < num_of_itocs; i++) {
        struct toc_info *itoc_info = &tocArr[i];
        if (itoc_info->toc_entry.type == sect_type) {
            curr_toc =  itoc_info;
            return true;
        }
    }
    return errmsg("ITOC entry type: %s (%d) not found", GetSectionNameByType(sect_type), sect_type);
}
#define FS3_DEFAULT_SECTOR_SIZE 0x1000

bool Operations::Fs3ChangeUidsFromBase(guid_t base_uid, struct cibfw_guids *guids)
{
    u_int64_t base_uid_64 =  base_uid.l | (u_int64_t)base_uid.h << 32;
    // Should be put somewhere in common place
    u_int64_t base_mac_64 =  ((u_int64_t)base_uid.l & 0xffffff) | (((u_int64_t)base_uid.h & 0xffffff00) << 16);

    guids->guids[0].uid = base_uid_64;
    guids->guids[1].uid = base_uid_64 + 8;
    guids->macs[0].uid = base_mac_64;
    guids->macs[1].uid = base_mac_64 + 8;
    return true;
}


bool Operations::Fs3UpdateMfgUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, guid_t base_uid,
        std::vector<u_int8_t>  &newSectionData)
{
    struct cibfw_mfg_info mfg_info;
    cibfw_mfg_info_unpack(&mfg_info, (u_int8_t*)&section_data[0]);

    Fs3ChangeUidsFromBase(base_uid, &mfg_info.guids);
    newSectionData = section_data;
    memset((u_int8_t*)&newSectionData[0], 0, curr_toc->toc_entry.size * 4);
    cibfw_mfg_info_pack(&mfg_info, (u_int8_t*)&newSectionData[0]);
    return true;
}

bool Operations::Fs3UpdateUidsSection(struct toc_info *curr_toc, std::vector<u_int8_t>  section_data, guid_t base_uid,
        std::vector<u_int8_t>  &newSectionData)
{
    struct cibfw_device_info dev_info;
    cibfw_device_info_unpack(&dev_info, (u_int8_t*)&section_data[0]);
    Fs3ChangeUidsFromBase(base_uid, &dev_info.guids);
    newSectionData = section_data;
    memset((u_int8_t*)&newSectionData[0], 0, curr_toc->toc_entry.size * 4);
    cibfw_device_info_pack(&dev_info, (u_int8_t*)&newSectionData[0]);
    return true;
}

bool Operations::Fs3UpdateVpdSection(struct toc_info *curr_toc, char *vpd,
                               std::vector<u_int8_t>  &newSectionData)
{
    int vpd_size;
    u_int8_t *vpd_data;

    if (!ReadImageFile(vpd, vpd_data, vpd_size)) {
        return false;
    }
    GetSectData(newSectionData, (u_int32_t*)vpd_data, vpd_size);
    curr_toc->toc_entry.size = vpd_size / 4;
    delete[] vpd_data;
    return true;
}

bool Operations::Fs3GetNewSectionAddr(FBase& fbase, struct toc_info *tocArr, struct toc_info *curr_toc, u_int32_t &NewSectionAddr, bool failsafe_section)
{
    // printf("-D- addr  = %#x\n", curr_toc->toc_entry.flash_addr);
    u_int32_t sector_size = (fbase.is_flash()) ? fbase.get_sector_size() : FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t flash_addr = curr_toc->toc_entry.flash_addr << 2;
    // HACK: THIS IS AN UGLY HACK, SHOULD BE REMOVED ASAP
    if (failsafe_section) {
        NewSectionAddr = (flash_addr == 0x3fd000) ? 0x3fe000 : 0x3fd000;
    } else {
        NewSectionAddr = flash_addr;
    }
    // HACK: Avoid warning
    tocArr = NULL;
    // fbase = 0;
    sector_size = 0;
    return true;
}
bool Operations::Fs3UpdateItocInfo(struct toc_info *curr_toc, u_int32_t newSectionAddr, u_int32_t new_crc, std::vector<u_int8_t>  newSectionData)
{
    u_int8_t  new_entry_data[CIBFW_ITOC_ENTRY_SIZE];
    memset(new_entry_data, 0, CIBFW_ITOC_ENTRY_SIZE);
    curr_toc->section_data = newSectionData;
    curr_toc->toc_entry.section_crc = new_crc;
    // We assume it's absolute
    curr_toc->toc_entry.flash_addr = newSectionAddr >> 2;

    // Calculate entry CRC
    cibfw_itoc_entry_pack(&curr_toc->toc_entry, new_entry_data);
    u_int32_t entry_crc = CalcImageCRC((u_int32_t*)new_entry_data, (TOC_ENTRY_SIZE / 4) - 1);
    curr_toc->toc_entry.itoc_entry_crc = entry_crc;

    memset(curr_toc->data, 0, CIBFW_ITOC_ENTRY_SIZE);
    cibfw_itoc_entry_pack(&curr_toc->toc_entry, curr_toc->data);

    return true;
}




bool Operations::Fs3ReburnItocSection(FBase& f, ImageInfo info, char *fimage, u_int32_t newSectionAddr,
        u_int32_t newSectionSize, std::vector<u_int8_t>  newSectionData, char *msg)
{

    // HACK SHOULD BE REMOVED ASAP
    u_int32_t sector_size = (f.is_flash()) ? f.get_sector_size() : FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t oldItocAddr = info.itoc_addr;
    u_int32_t newItocAddr = (info.first_itoc_is_empty) ? (info.itoc_addr - sector_size) :  (info.itoc_addr + sector_size);
    char message[127];

    sprintf(message, "Updating %-4s section - ", msg);
    // Burn new Section
    if (!write_image(*(Flash*)&f, newSectionAddr , (u_int8_t*)&newSectionData[0], newSectionSize, true,
            message, true, true, fimage)) {
        // printf("-D- write image failed: %s\n", err());
        report("FAILED\n\n");
        return false;
    }

    // Update new ITOC
    std::vector<u_int8_t>  itocEntriesData;
    u_int32_t itocSize = (info.num_of_itocs + 1 ) * CIBFW_ITOC_ENTRY_SIZE + CIBFW_ITOC_HEADER_SIZE;
    u_int8_t *p = itocEntriesData.get_allocator().allocate(itocSize);
    memcpy(p, info.itoc_header, CIBFW_ITOC_HEADER_SIZE);
    for (int i = 0; i < info.num_of_itocs; i++) {
        struct toc_info *curr_itoc = &info.tocArr[i];
        memcpy(p + CIBFW_ITOC_HEADER_SIZE + i * CIBFW_ITOC_ENTRY_SIZE, curr_itoc->data, CIBFW_ITOC_ENTRY_SIZE);
    }
    memset(&p[itocSize] - CIBFW_ITOC_ENTRY_SIZE, FS3_END, CIBFW_ITOC_ENTRY_SIZE);



    if (!write_image(*(Flash*)&f, newItocAddr , p, itocSize, true,
            "Updating ITOC section - ", true, false, fimage)) {
        // printf("-D- write image failed: %s\n", err());
        report("FAILED\n\n");
        return false;
    }
    u_int32_t zeros = 0;


    if (!write_image(*(Flash*)&f, oldItocAddr, (u_int8_t*)&zeros, 4, true,
            "Restoring signature   - ", true, false, fimage)) {
        report("FAILED \n\n");
        return false;
    }
    return true;
}



bool  Operations::Fs3UpdateSection(FBase& fbase, void *new_info, fs3_section_t sect_type, bool is_sect_failsafe, char *fimage)
{
    ImageInfo info;
    struct toc_info *newTocArr;
    struct toc_info *curr_toc;
    std::vector<u_int8_t> newUidSection;
    u_int32_t new_crc = 0;
    u_int32_t newSectionAddr;
    bool curr_silent = _silent;
    char *type_msg;
    _silent = true;
    initSectToRead(sect_type);
    if (!VerifyFs3(fbase, &info)) {
        return false;
    }
    _silent = curr_silent;

    // get newTocArr
    newTocArr = info.tocArr;

    if (!Fs3GetItocInfo(info.tocArr, info.num_of_itocs, sect_type, curr_toc)) {
         return false;
     }

    if (sect_type == FS3_MFG_INFO) {
        guid_t base_uid = *(guid_t*)new_info;
        type_msg = "GUID";
        if (!Fs3UpdateMfgUidsSection(curr_toc, curr_toc->section_data, base_uid, newUidSection)) {
            return false;
        }
    } else if (sect_type == FS3_DEV_INFO) {
        guid_t base_uid = *(guid_t*)new_info;
        type_msg = "GUID";
        if (!Fs3UpdateUidsSection(curr_toc, curr_toc->section_data, base_uid, newUidSection)) {
            return false;
        }
    } else if (sect_type == FS3_VPD_R0) {
        char *vpd_file = (char*)new_info;
        type_msg = "VPD";
        if (!Fs3UpdateVpdSection(curr_toc, vpd_file, newUidSection)) {
            return false;
        }
    } else {
        return errmsg("Section type %s is not supported\n", GetSectionNameByType(sect_type));
    }

    new_crc = CalcImageCRC((u_int32_t*)&newUidSection[0], curr_toc->toc_entry.size);

    if (!Fs3GetNewSectionAddr(fbase, info.tocArr, curr_toc, newSectionAddr, is_sect_failsafe)) {
        return false;
    }
    if (!Fs3UpdateItocInfo(curr_toc, newSectionAddr, new_crc, newUidSection)) {
        return false;
    }

    if (!Fs3ReburnItocSection(fbase, info, fimage, newSectionAddr, curr_toc->toc_entry.size * 4, newUidSection, type_msg)) {
        return false;
    }
    return true;
}

bool Operations::VerifyFs3(FBase& f, Operations::ImageInfo* info, bool show_itoc)
{
    u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
    u_int32_t cntx_image_num;
    u_int32_t buff[FS3_BOOT_START_IN_DW];
    u_int32_t offset;
    bool bad_signature;

    CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);
    if (cntx_image_num == 0) {
        return errmsg("No valid FS3 image found");
    }
    u_int32_t image_start = cntx_image_start[0];
    offset = 0;
    // TODO:  Check more than one image
    // Read BOOT
    //f.set_address_convertor(0, 0);
    // Put info
    info->imgStart          = image_start;
    info->cntxLog2ChunkSize = 21; // TODO: should it be hardcoded
    info->isFailsafe        = true;
    info->actuallyFailsafe  = true;
    info->magicPatternFound = 1;
    info->isFs3             = true;

    f.set_address_convertor(info->cntxLog2ChunkSize, info->imgStart != 0);
    READBUF(f, 0, buff, FS2_BOOT_START, "Image header");
    Fs3UpdateImgCache(info, (u_int8_t*)buff, 0, FS2_BOOT_START);
    TOCPUn(buff, FS3_BOOT_START_IN_DW);


    // f.set_address_convertor(info->cntxLog2ChunkSize, info->imgStart != 0);

    report("FS3 failsafe image\n"); // TODO: Do we have non-faisafe image

    // TODO: Get BOOT2
    offset += FS2_BOOT_START;
    FS3_CHECKB2(f, 0, offset, PRE_CRC_OUTPUT, info);
    offset += info->boot_size;
    info->first_itoc_is_empty = false;
    // printf("-D- image_start = %#x\n", image_start);
    // TODO: Get info of the failsafe from the Image header - no need always failsafe
    // Go over the ITOC entries
    u_int32_t sector_size = (f.is_flash()) ? f.get_sector_size() : FS3_DEFAULT_SECTOR_SIZE;

    offset = (offset % sector_size == 0) ? offset : (offset + sector_size - offset % 0x1000);
    while (offset < f.get_size())
    {
        if (VerifyTOC(f, info, offset, bad_signature, show_itoc)) {
            return true;
        } else {
            if (!bad_signature) {
                return false;
            }
            info->first_itoc_is_empty = true;
        }
        offset += sector_size;
    }
    return false;
}

bool Operations::UpdateDevDataITOC(u_int8_t *image_data, struct toc_info *image_toc_entry, struct toc_info *flash_toc_arr, int flash_toc_size)
{
    u_int8_t itoc_data[CIBFW_ITOC_ENTRY_SIZE];

    for (int i = 0; i < flash_toc_size; i++) {
        struct toc_info *flash_toc_info = &flash_toc_arr[i];
        struct cibfw_itoc_entry *flash_toc_entry = &flash_toc_info->toc_entry;
        if (flash_toc_entry->type == image_toc_entry->toc_entry.type) {
            memset(itoc_data, 0, CIBFW_ITOC_ENTRY_SIZE);
            cibfw_itoc_entry_pack(flash_toc_entry, itoc_data);
            memcpy(&image_data[image_toc_entry->entry_addr], itoc_data, CIBFW_ITOC_ENTRY_SIZE);
            cibfw_itoc_entry_unpack(&image_toc_entry->toc_entry, &image_data[image_toc_entry->entry_addr]);
        }
    }
    return true;
}

bool Operations::BurnFs3Image(Flash& f, FImage& fim, bool need_report)
{
    ImageInfo flash_info, image_info_x, *image_info;
    image_info = &image_info_x;
    u_int8_t  is_curr_image_in_odd_chunks;
    u_int32_t new_image_start, image_size = 0;
    u_int8_t  *data8      = (u_int8_t *) fim.getBuf();

    bool curr_silent = _silent;
    _silent = true;

    if (!VerifyFs3(f, &flash_info)) {
        return false;
    }
    if (!VerifyFs3(fim, image_info)) {
        return false;
    }
    _silent = curr_silent;

    if (flash_info.imgStart != 0) {
        is_curr_image_in_odd_chunks = 1;
        new_image_start = 0;
    } else {
        is_curr_image_in_odd_chunks = 0;
        new_image_start = (1 << image_info->cntxLog2ChunkSize);
    }

    /*printf("-D- new_image_start = %#x, is_curr_image_in_odd_chunks = %#x\n", new_image_start, is_curr_image_in_odd_chunks);
    printf("-D- num_of_itocs = %d\n", image_info->num_of_itocs);
    */
    f.set_address_convertor(image_info->cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);

    for (int i = 0; i < image_info->num_of_itocs; i++) {
        struct toc_info *itoc_info_p = &image_info->tocArr[i];
        struct cibfw_itoc_entry *toc_entry = &itoc_info_p->toc_entry;
        // printf("-D- itoc_addr = %#x\n", itoc_info_p->entry_addr);
        if (toc_entry->device_data) {
            // TODO: Copy the ITOC from Device
            // printf("-D- toc_entry: %#x\n", toc_entry->itoc_entry_crc);
            if (!UpdateDevDataITOC(data8, itoc_info_p, flash_info.tocArr, flash_info.num_of_itocs)) {
                return false;
            }
            // printf("-D- After toc_entry: %#x\n", toc_entry->itoc_entry_crc);
        } else {
            u_int32_t last_addr_of_itoc = toc_entry->flash_addr + toc_entry->size << 2;
            image_size = (last_addr_of_itoc > image_size) ? last_addr_of_itoc : image_size;
        }

    }
    // TODO: Check that the dev data is not been overridden
    {

         char * pre_message = "Burning FS3 FW image without signatures";
         u_int32_t  zeroes     = 0;
         char message[128], message1[128], buff[128];
         report("\n");
         int allow_nofs = 0;

         if (pre_message == NULL) {
             sprintf(message, "Burning FW image without signatures");
         } else {
             sprintf(message, pre_message);
         }
         int str_len = strlen(message), restore_len = strlen(RESTORING_MSG);
         str_len = (restore_len > str_len) ? restore_len : str_len;

         sprintf(buff, "%%-%ds  - ", str_len);

         sprintf(message1, buff,  message);


         if (!write_image(f, 16 , data8 + 16, image_size - 16, need_report, message1)) {
             report("FAILED\n\n");
             return false;
         }

         report(buff, RESTORING_MSG);

         fflush(stdout);

         // Write new signature
         if (!f.write(0, data8, 16, true)) {
             report("FAILED\n\n");
             return false;
         }
         bool boot_address_was_updated = true;
         // Write new image start address to crspace (for SW reset)
         if (!f.update_boot_addr(new_image_start)) {
             boot_address_was_updated = false;
         }

         if (image_info->isFailsafe) {
             if (allow_nofs) {
                 // When burning in nofs, remnant of older image with different chunk size
                 // may reside on the flash -
                 // Invalidate all images marking on flash except the one we've just burnt

                 u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
                 u_int32_t cntx_image_num;
                 u_int32_t i;

                 CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);
                 // Address convertor is disabled now - use phys addresses
                 for (i = 0; i < cntx_image_num; i++) {
                     if (cntx_image_start[i] != new_image_start) {
                         if (!f.write(cntx_image_start[i], &zeroes, sizeof(zeroes), true)) {
                             report("FAILED\n\n");
                             return false;
                         }
                     }
                 }
             } else {
                 // invalidate previous signature
                 f.set_address_convertor(image_info->cntxLog2ChunkSize, is_curr_image_in_odd_chunks);
                 if (!f.write(0, &zeroes, sizeof(zeroes), true)) {
                     report("FAILED\n\n");
                     return false;
                 }
             }
         }
         report("OK  \n");
         if (boot_address_was_updated == false) {
             report_warn("Failed to update FW boot address. Power cycle the device in order to load the new FW.\n");
         }

    }
    // TODO: Update the signature

    return true;
}



bool Operations::VerifyFs2(FBase& f, Operations::ImageInfo* info, bool both_images, bool only_get_start,
                           bool ignore_full_image_crc, bool force_no_striped_image) {
    u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
    u_int32_t cntx_image_num;
    u_int32_t i;
    bool      ret = true;
    u_int32_t act_crc;
    bool  check_full_crc = false;
    // printf("-D- VerifyFs2 = ok\n");
    // Look for image in "physical addresses
    CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);

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

    bool info_set = false;

    // Verify the images:
    for (i = 0; i < cntx_image_num; i++) {
        bool      fs_en;
        u_int32_t log2chunk_size;
        u_int32_t buff[FS2_BOOT_START / 4];

        f.get_image_crc().clear();

        f.set_address_convertor(0, 0);

        READBUF(f, cntx_image_start[i], buff, FS2_BOOT_START, "Image header");

        TOCPUn(buff, FS2_BOOT_START / 4);

        u_int32_ba crc_dw = buff[IMG_CRC_OFF / 4];
        act_crc           = u_int32_t(crc_dw.range(15, 0));
        crc_dw.range(15, 0) = 0xffff;
        buff[IMG_CRC_OFF / 4] |= crc_dw;

        CRCn(f.get_image_crc(), buff, FS2_BOOT_START / 4);
        //printf("-D- CRC is %#x\n", f.get_image_crc().get());
        if (!CntxGetFsData(buff[FS_DATA_OFF / 4], fs_en, log2chunk_size)) {
            report("\n    Can not read failsafe info word: %s\n", err());
            return(i > 0);
        }

        // If fw not enabled, image must start at addr 0
        if (!fs_en && cntx_image_start[i] != 0) {
            return errmsg("FS2 Non Failsafe image must start at address 0. Found non-fs image at address 0x%x",
                          cntx_image_start[i]);
        }

        if (fs_en) {
            report("\n     FS2 failsafe image. Start address: 0x%x. Chunk size 0x%x:\n\n", cntx_image_start[i], 1 << log2chunk_size);
            report("     NOTE: The addresses below are contiguous logical addresses. Physical addresses on\n"
                   "           flash may be different, based on the image start address and chunk size\n\n");
        } else {
            report("\n     FS2 non failsafe image:\n\n");
        }

        if (fs_en && cntx_image_start[i] != 0 && cntx_image_start[i] != (u_int32_t)(1 << log2chunk_size)) {
            return errmsg("FS2 Failsafe image must start at address 0 or at chunk size. Found a failsafe image at address 0x%x",
                          cntx_image_start[i]);
        }

        if (info && !info_set) {
            info->imgStart          = cntx_image_start[i];
            info->isFailsafe        = fs_en;
            info->actuallyFailsafe  = true;
            info->cntxLog2ChunkSize = log2chunk_size;
        }


        if (f.is_flash()) {
            // In flash, image layout must match the FS Data
            if (info && !info_set) {
                info->actuallyFailsafe    = true;
                info_set = true;
            }

            if (fs_en) {
                f.set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
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

            if (!force_no_striped_image && _cntx_striped_image) {
                f.set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
            } else {
                f.set_address_convertor(0, 0); //disable conversion
            }
            if (info && !info_set) {
                info->actuallyFailsafe    = _cntx_striped_image;
                info_set = true;
            }
        }

        bool imgStat = true;
        // TODO: check what only_get_start means.
        if (!only_get_start) {
            imgStat = checkList(f, 0, FS2_BOOT_START, PRE_CRC_OUTPUT, info);
        }
        f.get_image_crc().finish();

        u_int32_t full_crc = f.get_image_crc().get();

        if (!ignore_full_image_crc && info->infoOffs[II_MicVersion]) { // For now we check only that the Mic version existing .
            check_full_crc = true;
        }

        if (imgStat && _is_full_verify && check_full_crc && !only_get_start) {
            char pr[256];
            sprintf(pr, CRC_CHECK_OUTPUT, PRE_CRC_OUTPUT, 0, _last_image_addr - 1, _last_image_addr,
                    "Full Image");
            CheckAndPrintCrcRes(pr, info->blankGuids, 0, act_crc, full_crc);
        }

        if (i == 0) {
            ret = ret && imgStat;
        }
    }
    return ret;
}

bool Operations::ReadImageFile(char *fimage, u_int8_t *&file_data, int &file_size, int min_size)
{
    FILE* fh;

    if ((fh = fopen(fimage, "rb")) == NULL) {
        return errmsg("Can not open %s: %s\n", fimage, strerror(errno));
    }

    if (fseek(fh, 0, SEEK_END) < 0) {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }

    int read_file_size = ftell(fh);
    if (read_file_size < 0) {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }
    rewind(fh);

    if (min_size > read_file_size) {
        file_size = min_size;
    } else {
        file_size = read_file_size;
    }

    file_data = new u_int8_t[file_size];
    if (fread(file_data, 1, read_file_size, fh) != (size_t)read_file_size) {
        delete[] file_data;
        fclose(fh);
        return errmsg("Failed to read from %s: %s\n", fimage, strerror(errno));
    }
    fclose(fh);
    return true;
}


bool Operations::ModifyImageFile(char *fimage, u_int32_t addr, void *data, int cnt)
{
    int file_size;
    u_int8_t * file_data;

    if (!ReadImageFile(fimage, file_data, file_size, addr + cnt)) {
        return false;
    }
    memcpy(&file_data[addr], data, cnt);

    if (!WriteImageToFile(fimage, file_data, file_size)) {
        delete[] file_data;
        return false;
    }
    delete[] file_data;
    return true;
}

bool Operations::WriteImageToFile(char *file_name, u_int8_t *data, u_int32_t length)
{
    FILE* fh;
    if ((fh = fopen(file_name, "wb")) == NULL) {
        return errmsg("Can not open %s: %s\n", file_name, strerror(errno));
    }

    // Write output
    if (fwrite(data, 1, length, fh) != length) {
        fclose(fh);
        return errmsg("Failed to write to %s: %s\n", file_name, strerror(errno));
    }
    fclose(fh);
    return true;
}

bool Operations::packStripedImageData(u_int8_t *striped_data, u_int8_t *normal_data, u_int32_t length, u_int32_t &striped_length,
        bool needs_repack, u_int32_t cntxLog2ChunkSize)
{
    if (needs_repack) {
        u_int32_t chunk_size = 1 << cntxLog2ChunkSize;
        u_int32_t chunk_num = (length / chunk_size) + 1;
        u_int32_t i;
        striped_length = 0;

        // Loop which runs over the chunks
        for (i = 0; i < chunk_num; i++) {
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

bool Operations::ReburnNewImage(u_int8_t *data, FBase *fbase, Operations::ImageInfo* info, char *image_fname, bool silent,
        char *feature_name)
{
    u_int32_t length        = info->imageSize;
    FImage                fim1;
    Operations::ImageInfo new_info;
    char burn_str[100];
    bool is_image = (image_fname != NULL);
    bool needs_repack = (is_image && info->actuallyFailsafe);

    // Burn the Image after modifying the VSD.
    fim1.open((u_int32_t*)data, length);
    _silent = true;

    // Verify the new image and exit if it's not VALID.
    if (!VerifyFs2(fim1, &new_info, false, false, true, needs_repack) || !QueryAll(fim1, &new_info)) {
        return errmsg("Internal error: The prepared image After modifying the %s is corrupted: %s\n", feature_name, err());
    }
    _silent = false;
    if (!is_image) {
        // Modify the flash
        sprintf(burn_str, "Setting the %s", feature_name);
        if (!CntxFailSafeBurn((*(Flash*)fbase), fim1, !silent, info, &new_info, true,
                burn_str)) {
            return PrepareBurnErr((*(Flash*)fbase));
        }
    } else {
        u_int8_t *striped_data = new u_int8_t[length * 2];
        u_int32_t striped_length;

        // Modify the image.
        // Update the Full image CRC.
        UpdateFullImageCRC((u_int32_t*)data, length / 4, false);

        // Re-pack the image as it was given.
        // When it was striped this function would return it to that case.
        packStripedImageData(striped_data, data, length, striped_length, needs_repack, info->cntxLog2ChunkSize);

        // Re-write the image to the file.
        if (!WriteImageToFile(image_fname, striped_data, striped_length)) {
            return false;
       }
    }
    return true;
}


bool Operations::PrepareBurnErr(Flash& f)
{
    if (f.err()) {
        // The error is in flash access:
        return errmsg("Flash access failed: %s", f.err());
    } else {
        // operation/algorithm error:
        return errmsg("Failsafe operation failed: %s", err());
    }
    return false;
}

bool Operations::ModifyGuidSection(FBase *fbase, Operations::ImageInfo *info, guid_t *user_guids, char *image_fname, bool silent)
{
    u_int32_t length        =  info->imageSize;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!fbase->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed: %s\n", fbase->err());
    }
    // Change the GUIDs section according to the user given GUIDs
    patchGUIDsSection ((u_int32_t*)(&data[0]), info->guidPtr, user_guids, info->guidNum);
    // Re-burn the new Image after modifying the GUIDs
    return ReburnNewImage((u_int8_t*)(&data[0]), fbase, info, image_fname, silent, (char*)"GUIDs");
}

bool Operations::ModifyVSDSection(FBase *fbase, Operations::ImageInfo *info, char *vsd, char *image_fname, bool silent)
{

    u_int32_t length        =  info->imageSize;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!fbase->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed: %s\n", fbase->err());
    }
    // Change the VSD
    PatchInfoSect((u_int8_t*)(&data[0]) + info->infoSectPtr - sizeof(GPH),
                  info->infoOffs[Operations::II_VSD],
                   vsd);
    // Re-burn the new Image after modifying the VSD
    return ReburnNewImage((u_int8_t*)(&data[0]), fbase, info, image_fname, silent, (char*)"VSD");
}



bool Operations::ModifyKeySection(FBase *fbase, Operations::ImageInfo *info, guid_t access_key, char *image_fname, bool silent)
{

    u_int32_t length        =  info->imageSize;
    vector<u_int8_t> data(length);

    // Read the image.
    if (!fbase->read(0, (u_int8_t*)(&data[0]), length)) {
        return errmsg("Flash/Image read failed: %s\n", fbase->err());
    }

    // Change the VSD
    PatchKeySect((u_int32_t*)(&data[0] + info->infoSectPtr - sizeof(GPH)),
                  info->infoOffs[Operations::II_HwAccessKey],
                  access_key);
    // Re-burn the new Image after modifying the VSD
    return ReburnNewImage((u_int8_t*)(&data[0]), fbase, info, image_fname, silent, (char*)"HW Key");
}


bool Operations::Verify(FBase& f, Operations::ImageInfo* info, bool both_images, bool show_itoc)
{
    if (IsFs2() == FS_FS2_GEN) {
        return VerifyFs2(f, info, both_images);
    } else if (IsFs2() == FS_FS3_GEN) {
        return VerifyFs3(f, info, show_itoc);
    }
    return errmsg("Unsupported device type\n");
} // Verify

bool Operations::GetExpRomVersionWrapper(ImageInfo* info) {
    if (!GetExpRomVersion(info)) {
        snprintf(info->expRomErrMsg, MAX_ROM_ERR_MSG_LEN, err());
        info->expRomErrMsgValid = true;
    }
    return true;
}

bool Operations::GetExpRomVerForOneRom(ImageInfo* imageInfo, u_int32_t ver_offset) {

    u_int32_t tmp;
    RomInfo *romInfo;

    if (imageInfo->numOfExpRom == MAX_ROMS_NUM) {
        imageInfo->expRomWarning = true;
        snprintf(imageInfo->expRomWarningMsg,
                MAX_ROM_ERR_MSG_LEN,
                "Number of exp ROMs exceeds the maximum allowed number: %d",
                MAX_ROMS_NUM);
        return true;
    }
    romInfo = &(imageInfo->romInfo[imageInfo->numOfExpRom]);


    // Following mlxsign:
    // 31:24    0    Compatible with UEFI
    // 23:16    ProductID   Product ID:
    //                          1 - CLP implementation for Sinai (MT25408)
    //                          2 - CLP implementation for Hermon DDR (MT25418)
    //                          0X10 - PXE
    // 15:0 Major version   If ProductID < 0x10 this field is subversion
    //                          number, otherwise It's product major version.
    //
    // 31:16    Minor version   Product minor version*. Not valid if
    //                          roductID < 0x10.
    // 15:0 SubMinor version    Product sub minor version*. Not valid if
    //                                  ProductID < 0x10.
    //
    // 31:16    Device ID   The PCI Device ID (ex. 0x634A for Hermon
    //                          DDR). Not valid if ProductID < 0x10.
    // 15:12    Port Number Port number: 0 - Port independent, 1 - Port 1, 2 - Port 2
    //  8:11    Reserved
    //  0:7     Protocol type: 0=IB 1=ETH 2=VPI

    // Get expansion rom product ID
    tmp = __le32_to_cpu(*((u_int32_t*) &imageInfo->_rom_sect[ver_offset]));
    romInfo->expRomProductId = tmp >> 16;
    romInfo->expRomVer[0] = tmp & 0xffff;

    if (romInfo->expRomProductId == 0x11 || romInfo->expRomProductId == 0x21) {
        imageInfo->noRomChecksum = true;
    }


    if (romInfo->expRomProductId >= 0x10) {
        tmp = __le32_to_cpu(*((u_int32_t*) &imageInfo->_rom_sect[ver_offset + 4]));
        romInfo->expRomVer[1] = tmp >> 16;
        romInfo->expRomVer[2] = tmp & 0xffff;

        tmp = __le32_to_cpu(*((u_int32_t*) &imageInfo->_rom_sect[ver_offset + 8]));
        romInfo->expRomDevId = tmp >> 16;
        romInfo->expRomPort = (tmp >> 12) & 0xf;
        romInfo->expRomProto = tmp & 0xff;
    } else if (romInfo->expRomProductId == 0xf) {
        // get string length
        u_int32_ba tmp_ba = *((u_int32_t*) &imageInfo->_rom_sect[ver_offset + 0xc]);
        u_int32_t str_len = u_int32_t(tmp_ba.range(15, 8));
        u_int32_t sign_length = u_int32_t(tmp_ba.range(7, 0));
        u_int32_t dws_num = ((str_len + 3) / 4) + 4;

        if (sign_length < dws_num) {
            return errmsg(
                    "The Signature length (%d) and the ROM version string length (%d) are not coordinated",
                    sign_length, str_len);
        }
        // copy str
        strncpy(romInfo->expRomFreestr,
                (char*) &imageInfo->_rom_sect[ver_offset + 0x10], str_len);
        romInfo->expRomFreestr[str_len] = '\0';

        tmp_ba = __le32_to_cpu(*((u_int32_t*) &imageInfo->_rom_sect[0x18]));
        u_int32_t dev_id_off = u_int32_t(tmp_ba.range(15, 0)) + 4;

        if (dev_id_off >= imageInfo->_rom_sect.size()) {
            return errmsg(
                    "The device ID offset %#x is out of range. ROM size: %#x",
                    dev_id_off, (u_int32_t) imageInfo->_rom_sect.size());
        }

        // get devid
        tmp_ba = __le32_to_cpu(*((u_int32_t*) &imageInfo->_rom_sect[dev_id_off]));
        romInfo->expRomDevId = u_int32_t(tmp_ba.range(31, 16));
        u_int32_t vendor_id = u_int32_t(tmp_ba.range(15, 0));


        if (vendor_id != MELLANOX_VENDOR_ID) {
            imageInfo->expRomWarning = true;
            snprintf(imageInfo->expRomWarningMsg,
                    MAX_ROM_ERR_MSG_LEN,
                    "The Exp-ROM PCI vendor ID: %#x does not match the expected value: %#x.",
                    vendor_id, MELLANOX_VENDOR_ID);
        }

    }
    return true;
}


bool Operations::GetExpRomVersion(ImageInfo* info) {
    const char* magic_string = "mlxsign:";
    u_int32_t magic_len = strlen(magic_string);
    u_int32_t i;
    bool magic_found = false;
    u_int32_t ver_offset;
    u_int32_t rom_checksum_range;

    // Init some
    info->expRomValidVersion = false;
    info->numOfExpRom = 0;
    info->expRomComDevid = 0;

    info->expRomWarning = false;
    info->expRomErrMsgValid = false;

    if (info->_rom_sect.empty()) {
        return errmsg("Expansion Rom section not found.");
    }
    // When checking the version of the expansion rom, only the first image has
    // to be checked. This is because the second image  the uefi image does not
    // have to comply with checksumming to 0. To do this you have to read  byte
    // 2 (third) of the image  and multiply by 512 to get the size of the x86
    // image.

    // Checksum:
    if (info->_rom_sect.size() < 4) {
        return errmsg("ROM size (0x%x) is too small",
                (u_int32_t) info->_rom_sect.size());
    }

    // restore endianess.
    TOCPUn(&(info->_rom_sect[0]), info->_rom_sect.size()/4);
    /*  // FOR WE DON'T CHECKSUM UNTIL WE DECIDED REGARDING THE NEW FORMAT.
     */
    // We will look for the magic string in whole ROM instead of the first part of it.
    rom_checksum_range = info->_rom_sect.size();

    for (i = 0; i < rom_checksum_range; i++) {
        for (u_int32_t j = 0; j < magic_len; j++) {
            if (info->_rom_sect[i + j] != magic_string[j]) {
                break;
            } else if (j == magic_len - 1) {
                magic_found = true;
            }
        }

        if (magic_found) {
            // Get the ROM info after the mlxsign
            bool rc;
            RomInfo *currRom;

            if (info->numOfExpRom == MAX_ROMS_NUM) {
                info->expRomWarning = true;
                snprintf(info->expRomWarningMsg,
                        MAX_ROM_ERR_MSG_LEN,
                        "Number of exp ROMs exceeds the maximum allowed number (%d)",
                        MAX_ROMS_NUM);
                // Here we want to warn regarding this issue without checksum.
                return true;
            }

            currRom = &(info->romInfo[info->numOfExpRom]);
            ver_offset = i + magic_len;
            rc = GetExpRomVerForOneRom(info, ver_offset);
            if (rc != true) {
                return rc;
            }

            // Get the device ID and check if it mismatches with other ROMs
            if (info->expRomComDevid != MISS_MATCH_DEV_ID) { // When the DevId is already mismatched, no end to any check
                 if (currRom->expRomDevId != EXP_ROM_GEN_DEVID) { // When we have a device ID on the ROM
                    if (info->expRomComDevid == EXP_ROM_GEN_DEVID) { // Update the common DevId at the first time we find ID
                        info->expRomComDevid = currRom->expRomDevId;
                    } else { // Check if we have the same IDs, if yes, continue
                        if (currRom->expRomDevId != info->expRomComDevid) { // There is a mismatch between ROMs
                            info->expRomComDevid = MISS_MATCH_DEV_ID;
                            info->expRomWarning = true;
                            snprintf(info->expRomWarningMsg,
                                     MAX_ROM_ERR_MSG_LEN,
                                     "The device IDs of the ROMs mismatched.");
                        }
                    }
                }
            }

            magic_found = false;      // Clean the magic_found to start search for another magic string
            i += (ROM_INFO_SIZE - 1); // Increase the index to point to the end of the ROM info.
            info->numOfExpRom++;
        }
    }

    // TODO: ADD CHECKSUM CHECK
    if (!info->numOfExpRom) {
        return errmsg("Cannot get ROM version. Signature not found.");

    }

    if (info->noRomChecksum == 0) { // No need for checksum on some ROMs like uEFI
         u_int8_t rom_checksum = 0;
         rom_checksum_range = info->_rom_sect[2] * 512;
         if (rom_checksum_range > info->_rom_sect.size()) {
             return errmsg(
                     "ROM size field (0x%2x) is larger than actual ROM size (0x%x)",
                     rom_checksum_range, (u_int32_t) info->_rom_sect.size());
         } else if (rom_checksum_range == 0) {
             return errmsg(
                     "ROM size field is 0. Unknown ROM format or corrupted ROM.");
         }

         for (i = 0; i < rom_checksum_range; i++) {
             rom_checksum += info->_rom_sect[i];
         }

         if (rom_checksum != 0) {
             info->expRomWarning = true;
             snprintf(
                     info->expRomWarningMsg,
                     MAX_ROM_ERR_MSG_LEN,
                     "Bad ROM Checksum (0x%02x), ROM info may not be displayed correctly.",
                     rom_checksum);
         }
     }

    return true;
}

bool Operations::LoadAsExpRom (FBase& f, ImageInfo* info) {
    info->_rom_sect.clear();
    info->_rom_sect.resize(f.get_size());
    if (!f.read(0, &info->_rom_sect[0], f.get_size()))
        return errmsg(f.err());

    TOCPUn(&info->_rom_sect[0], info->_rom_sect.size()/4);

    return true;
}

bool Operations::unzipDataFile (std::vector<u_int8_t> data, std::vector<u_int8_t> &newData, const char *section_name)
{
#ifndef NO_ZLIB
    int rc;
    if (data.empty()) {
        return errmsg("%s section not found in the given image.", section_name);
    }

    // restore endianess.
    TOCPUn(&(data[0]), data.size()/4);

    // uncompress:
    uLongf destLen = data.size();
    destLen *= 40; // Assuming this is the best compression ratio
    vector<u_int8_t> dest(destLen);

    for (int i = 0; i < 32; i++) {
        rc = uncompress((Bytef *)&(dest[0]), &destLen,
                            (const Bytef *)&(data[0]), data.size());
        if (rc != Z_BUF_ERROR) {
            break;
        }
        destLen *= 2;
        dest.resize(destLen);
    }

    if (rc != Z_OK) {
        return errmsg("Failed uncompressing FW configuration section. uncompress returns %d", rc);
    }
    // printf("%s", (char*)&(dest[0]));

    newData = dest;
    newData[destLen] = 0; // Terminating NULL
    newData.resize(destLen + 1);
    return true;
#else
    return errmsg("Executable was compiled with \"dump files\" option disabled.");
#endif
}

bool Operations::DumpFile        (const char* conf_file, std::vector<u_int8_t> data, const char *section_name) {
    FILE* out;
    vector<u_int8_t> dest;

    if (conf_file == NULL) {
        out = stdout;
    } else {
        out = fopen(conf_file, "w");

        if (out == NULL) {
            return errmsg("Can not open file %s for write: %s.", conf_file, strerror(errno));
        }
    }
    if (unzipDataFile(data, dest, section_name) == false) {
        return false;
    }
    fprintf(out, "%s", (char*)&(dest[0]));

    if (conf_file != NULL) {
        fclose(out);
    }
    return true;

}
bool Operations::DumpFileSection (const char* conf_file, u_int32_t sect_type) {
    std::vector<u_int8_t> file_sect;
    if (sect_type == H_HASH_FILE) {
        file_sect = _hash_file_sect;
    } else {
        file_sect =  _fw_conf_sect;
    }
    return DumpFile(conf_file, file_sect, g_sectNames[sect_type]);

}

////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                       GUIDs TREATMENT                              //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////


bool Operations::getFlashParams(char *flash_arg, flash_params_t *flash_params)
{
    char *type_str, *size_str, *flash_num_str, *last_arg, flash_tmp[50], *endp;
    int size_of_arr = sizeof(flash_tmp)/sizeof(flash_tmp[0]);

    strncpy(flash_tmp, flash_arg, size_of_arr);
    flash_tmp[size_of_arr] = 0;

    // Get the parameters
    type_str = strtok(flash_arg, ",");
    size_str = strtok(NULL, ",");
    flash_num_str = strtok(NULL, ",");

    // For checking that we don't have more arguments than needed.
    last_arg = strtok(NULL, ",");

    if (type_str == NULL || size_str == NULL || flash_num_str == NULL || last_arg != NULL) {
        report_err(_err_msg, "Bad flash params argument (%s ...), it should be as follow: %s.\n", flash_tmp, FLASH_PARAMS_OPTS);
        return false;
    }

    flash_params->type_name = type_str;

    flash_params->log2size = strtoul(size_str, &endp, 0);
    if (*endp != '\0') {
        report_err(_err_msg, "Bad flash parameter log2size (%s).\n", size_str);
        return false;
    }

    flash_params->num_of_flashes = strtoul(flash_num_str, &endp, 0);
    if (*endp != '\0') {
        report_err(_err_msg, "Bad flash parameter num_of_flashes (%s).\n", flash_num_str);
        return false;
    }
    return true;
}


bool Operations::getGUID(const char *s, guid_t *guid, char *err_msg)
{
    char* endp;
    u_int64_t g;

    g = strtoull(s, &endp, 16);
    if (*endp || (g == 0xffffffffffffffffULL && errno == ERANGE)) {
        if (!strcmp(err_msg, "")) {
            report_err(_err_msg, "Invalid GUID syntax (%s) %s \n", s, errno ? strerror(errno) : "" );
        } else {
            report_err(_err_msg, "%s\n", err_msg);
        }
        return false;
    }
    guid->h = (u_int32_t)(g >> 32);
    guid->l = (u_int32_t)(g & 0xffffffff);
    return true;
} // getGUID

////////////////////////////////////////////////////////////////////////
bool Operations::extractGUIDptr(u_int32_t sign, u_int32_t *buf, int buf_len,
                                char *pref, u_int32_t *ind, int *nguids)
{
    u_int32_t offs = 0;

    if (IsFs2()) {
        offs = 16;
    }

    // Check signature
    if (sign) {
        u_int32_t signature = buf[(sign + 8)/4];
        TOCPU1(signature);
        if (signature != SIGNATURE) {
            printf("%s pointer section not valid\n", pref);
            return false;
        }
        offs = buf[sign/4];
        TOCPU1(offs);
    }

    // Get GUID ptr
    *ind = buf[(offs+0x24)/4];
    TOCPU1(*ind);
    if (!IsFs2()) {
        *ind += offs;
    }
    if (*ind >= (u_int32_t)buf_len) {
        printf("%s image - illegal GUID pointer (%08x)\n", pref, *ind);
        return false;
    }
    *nguids = buf[*ind/4 - 3];

    TOCPU1(*nguids);
    *nguids /= 2;

    // More sanity check
    if (IsFs2() ? (*nguids > MAX_GUIDS) : (*nguids > GUIDS)) {
        printf("%s image - illegal number of GUIDs (0x%x)\n", pref, *nguids);
        return false;
    }

    return true;
} // extractGUIDptr



////////////////////////////////////////////////////////////////////////

//
// This function calculates CRC over the geven buf/size, and stores
// the crc in the dwors after the data.
// Caller should make sure CRC word memory is really there.
void Operations::recalcSectionCrc(u_int8_t *buf, u_int32_t data_size) {
    Crc16              crc;
    u_int32_t          i;

    for (i = 0; i < data_size; i += 4) {
        crc << __be32_to_cpu(*(u_int32_t*)(buf + i));
    }
    crc.finish();
    *(u_int32_t*)(buf + data_size) = __cpu_to_be32(crc.get());
}

////////////////////////////////////////////////////////////////////////
void Operations::patchGUIDsSection(u_int32_t *buf, u_int32_t ind,
                                   guid_t guids[MAX_GUIDS], int nguids)
{
    u_int32_t       i;
    u_int32_t       new_buf[MAX_GUIDS*2];

    // Form new GUID section
    for (i=0; i<(u_int32_t)nguids; i++) {
        new_buf[i*2] = guids[i].h;
        new_buf[i*2+1] = guids[i].l;
    }

    // Patch GUIDs
    for (i=0; i<sizeof(new_buf)/sizeof(u_int32_t); ++i) {
        new_buf[i] = _burn_blank_guids ? 0xffffffff : __cpu_to_be32(new_buf[i]);
    }
    memcpy(&buf[ind/4], &new_buf[0], nguids * 2 * sizeof(u_int32_t));

    // Insert new CRC
    if (_burn_blank_guids) {
        buf[ind/4 + nguids*2] =  __cpu_to_be32(0xffff);
    } else {
        recalcSectionCrc((u_int8_t*)buf + ind - sizeof(GPH), sizeof(GPH) + nguids * 8);
    }
} // patchGUIDsSection



void Operations::PatchKeySect(u_int32_t* buff, u_int32_t keyOff, guid_t hw_key)
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

//
// PatchInfoSect() :
// This func assumes it gets a pointer (rawSect) to a valid info sect.
// It patches the it with the given data, recalculated CRC ,
// and copies it back to the given data
//

void Operations::PatchInfoSect(u_int8_t*      rawSect,
                               u_int32_t      vsdOffs,
                               const char*    vsd) {

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


//
// PatchPs() :
// This func assumes it gets a pointer (rawPs) to a valid PS.
// It patches the PS with the given data, recalculated CRC ,
// and copies it back to the rawPs.
//

void Operations::PatchPs(u_int8_t*      rawPs,
                         const char*    vsd,
                         const char*    psid,
                         u_int32_t      imageAddr) {

    PS         *ps = (PS*)rawPs;

    u_int32_t fix_start = 0;
    u_int32_t fix_end   = 0;

    if (vsd) {
        u_int32_t len = strlen(vsd);

        memset(&ps->vsd[0],  0,   VSD_LEN );
        memcpy(&ps->vsd[0],  vsd, len);

        fix_end += VSD_LEN;
    } else {
        fix_start +=VSD_LEN;
    }
    if (psid) {
        u_int32_t len = strlen(psid);

        memset(&ps->psid[0],  0,    PSID_LEN );
        memcpy(&ps->psid[0],  psid, len );
        fix_end += PSID_LEN;
    }

    //VSD is kept on flash byte-swapped.
    //recode it back before patching
    u_int32_t *qp;

    qp = (u_int32_t *)&ps->vsd[0];
    for (u_int32_t i=fix_start; i<fix_end/4; i++) {
        *qp = bswap_32(*qp);
        qp++;
    }

    if (imageAddr) {
        ps->fi_addr = __cpu_to_be32(imageAddr);
    }

    recalcSectionCrc((u_int8_t *)ps, sizeof(PS) - 4);
}

bool Operations::patchHwAccessKey(FImage& f, ImageInfo& flash_info, ImageInfo& image_info)
{
    u_int32_t key_supported_flash = flash_info.infoOffs[Operations::II_HwAccessKey];
    u_int32_t key_supported_image = image_info.infoOffs[Operations::II_HwAccessKey];

    if (key_supported_image) {
        hw_key_t key_to_burn;
        u_int32_t *buff = f.getBuf();
        u_int32_t *infoSectBuff = (u_int32_t*)((u_int8_t*)buff + image_info.infoSectPtr - sizeof(GPH));
        u_int32_t keyOff = image_info.infoOffs[II_HwAccessKey];

        if (key_supported_flash) {
            // Image file : HW access Key exists
            // Flash :      HW access Key exists
            // Behavior: Save the burnt key in the flash.
            key_to_burn = flash_info.accessKeyValue;
        } else {
            // Image file : HW access Key exists
            // Flash :      No HW access Key
            // Behavior: Just create a zero Key even if the image contains an activated key
            key_to_burn.l = 0;
            key_to_burn.h = 0;
       }
       PatchKeySect(infoSectBuff, keyOff, key_to_burn);
    } else {
        if (key_supported_flash) {
            // Image file : No HW access Key
            // Flash :      HW access Key exists
            // Behavior: In this case we will warn the user that he's going to remove the HW access Key
            printf("\n    NOTE: You are about to burn a FW that does not support HW access enable/disable.\n");
            printf("          If you already have an activated key it will be removed.\n");
            if (! ask_user()) {
                return false;
            }
        } else {
            // Image file : No HW access Key
            // Flash :      No HW access Key
            // Behavior: Do nothing
            return true;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
//Note that vsd1 is a string of bytes.
bool Operations::patchVSD(FImage& f,
                          Operations::ImageInfo* info,
                          const char *user_vsd,
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid)
{
    const char* vsd_to_use  = curr_vsd ? curr_vsd : "";
    const char* psid_to_use = image_psid;

    // TODO: Should not give the user_psid param. Do not allow for on-the-fly PSID changes.

    curr_psid = NULL;
    // Form new VSD

    if (user_psid) {
        // New psid is explicitly given - take it from user
        printf("\n    You are about to replace current PSID in the image file - \"%s\" with a different PSID - \"%s\".\n"
               "    Note: It is highly recommended not to change the image PSID.\n", user_psid, image_psid);

        if (! ask_user())
            return false;

        psid_to_use = user_psid;
    }

    if (user_vsd) {
        vsd_to_use = user_vsd;
    }

    if (IsFs2() && info->infoOffs[II_VSD]) {
        PatchInfoSect((u_int8_t*)f.getBuf() + info->infoSectPtr - sizeof(GPH),
                      info->infoOffs[II_VSD],
                      vsd_to_use);
    } else {
        PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size(),     vsd_to_use, psid_to_use);
        PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size() * 2, vsd_to_use, psid_to_use);
    }

    return true;
} // pathVSD


bool Operations::PrintGUIDs(guid_t guids[MAX_GUIDS], guid_t old_guids[MAX_GUIDS], bool print_guids, bool print_macs, bool old_guid_fmt) {

    if (print_guids) {
        printf("        Node  GUID:     ");
        PrintGuidLine(guids,old_guids, 0);
        if (_num_ports > 0) {
            printf("        Port1 GUID:     ");
            PrintGuidLine(guids,old_guids, 1);
        }
        if (_num_ports > 1) {
            printf("        Port2 GUID:     ");
            PrintGuidLine(guids,old_guids, 2);
        }
        if (!old_guid_fmt) {
            printf("        Sys.Image GUID: ");
            PrintGuidLine(guids,old_guids, 3);
        }
    }

    if (print_macs) {
        printf("        Port1 MAC:      ");
        PrintMacLine(guids, old_guids, 4);
        printf("        Port2 MAC:      ");
        PrintMacLine(guids, old_guids, 5);
    }
    return true;
}

void Operations::initSectToRead(int imp_index) {
    if (IsFs3()) {
        _read_sect_list.push_back(imp_index);
    } else {
        for (int i = 0; i < H_LAST; i++) {
            if (imp_index == FULL_VERIFY || i == imp_index) {
                _sections_to_read[i] = 1;
            } else {
                _sections_to_read[i] = 0;
            }
        }
        if (imp_index == FULL_VERIFY) {
            _is_full_verify = true;
        } else {
            _is_full_verify = false;
        }

    }
    return;
}

void Operations::SetDevFlags(u_int16_t devType, bool& ib_dev, bool& eth_dev) {

    if (IsIs4(devType)) {
        ib_dev = true;
        eth_dev = false;
    } else if (IsSX(devType)) {
        ib_dev = true;
        eth_dev = true;
    } else {
        ib_dev  = !IsFs2() || CntxIsIb(devType);
        eth_dev = IsFs2()  && CntxIsEth(devType);
    }

    if (!ib_dev && !eth_dev) {
        // Unknown device id - for forward compat - assume that ConnectX is MP and
        // prev HCAs are IB only (these flags are for printing only - no real harm can be done).
        // TODO: FS2 does not mean ConnectX now.
        ib_dev = true;
        if (IsFs2()) {
            eth_dev = true;
        } else {
            eth_dev = false;
        }
    }
}

bool Operations::CheckGuidsFlags (u_int16_t devType,
                                  bool guids_specified,
                                  bool macs_specified,
                                  bool uids_specified) {
    // Patch GUIDS
    if (guids_specified || macs_specified || uids_specified) {
        if (IsBridgeX(devType)) {
            if (macs_specified || guids_specified) {
                return errmsg("-mac(s)/-guid(s) flags is not applicable for MT%d.", devType);
            }
        } else {
            if (uids_specified) {
                return errmsg("-uid(s) flag is applicable only for BridgeX and FS3 FW.");
            } else if (!IsFs2() && macs_specified ) {
                return errmsg("-mac(s) flag is not applicable for IB MT%d device.",
                              devType);
            }// else if (!ib_dev && guids_specified) {
            //     return errmsg("-guid(s) flag is not applicable for IB MT%d device.\n",
            //                  devType);
            //}
        }
    }
    return true;
}

bool Operations::CheckSetGuidsFlags(ImageInfo* info, bool macs_specified, bool guids_specified, bool uids_specified)
{
    bool ib_dev;
    bool eth_dev;
    bool bx_dev;

    bx_dev = IsBridgeX(info->devType);
    SetDevFlags(info->devType, ib_dev,eth_dev);

    if (macs_specified || guids_specified || uids_specified) {
        if (!CheckGuidsFlags(info->devType, guids_specified, macs_specified, uids_specified)) {
            return errmsg("%s", err());
        }
    } else {
        PrintMissGuidErr(ib_dev, eth_dev, bx_dev);
        return errmsg("For set_guids command, %s", err());
    }

    return true;
}
bool Operations::PrintGuidLine(guid_t* new_guids, guid_t* old_guids, int guid_index)
{
    printf(GUID_FORMAT GUID_SPACES, new_guids[guid_index].h, new_guids[guid_index].l);
    if (old_guids != NULL) {
        printf(GUID_FORMAT,  old_guids[guid_index].h, old_guids[guid_index].l);
    }else {
        printf("      N/A");
    }
    printf("\n");
    return true;
}

bool Operations::PrintBxGuids(guid_t* new_guids, guid_t* old_guids, int index, int num_of_guids, const char* pre_str)
{
    int guid_index = index;
    int _is_wwpn = ((guid_index - Operations::BI_WWPNS) % Operations::BX_SLICE_GUIDS);

    for (int i = 0; i < num_of_guids; i++) {
        printf("    G%d", (index >= Operations::BX_SLICE_GUIDS));
        if (i == 0 && _is_wwpn) {
           printf(" Node  %s:      ", pre_str);
        } else {
            int j = _is_wwpn ? i : i + 1;
            printf(" Port%d %s:      ", j, pre_str);
        }
        PrintGuidLine(new_guids, old_guids,  guid_index);
        guid_index++;
    }
    return true;
}

bool Operations::PrintMacLine(guid_t* new_guids, guid_t* old_guids, int mac_index)
{
    printf("    "MAC_FORMAT MAC_SPACES, new_guids[mac_index].h, new_guids[mac_index].l);
    if (old_guids != NULL) {
        printf(MAC_FORMAT, old_guids[mac_index].h, old_guids[mac_index].l);
    } else {
        printf("  N/A");
    }
    printf("\n");
    return true;
}

bool Operations::PrintBxMacs(guid_t* new_guids, guid_t* old_guids, int index, int num_of_guids, const char* pre_str)
{
    int guid_index = index;

    for (int i = 0; i < num_of_guids; i++) {
        printf("    G%d", (index >= Operations::BX_SLICE_GUIDS));
        printf(" Port%d %s:      ", i + 1, pre_str);
        PrintMacLine(new_guids, old_guids, guid_index);
        guid_index++;
    }
    return true;
}

bool Operations::PrintUids(guid_t* new_guids, guid_t* old_guids)
{
    int base_index = 0, guid_index;

    for (int i = 0; i < BX_SLICES_NUM; i++) {
        base_index = i * BX_SLICE_GUIDS;
        // Init Guids
        PrintBxGuids(new_guids, old_guids, base_index + BI_GUIDS, BX_NP_GUIDS, "Guid");
        PrintBxMacs (new_guids, old_guids, base_index + BI_IMACS, BX_IMACS,    "IMAC");
        PrintBxMacs (new_guids, old_guids, base_index + BI_EMACS, BX_EMACS,    "EMAC");
        PrintBxGuids(new_guids, old_guids, base_index + BI_WWNNS, BX_WWNNS,    "WWNN");
        PrintBxGuids(new_guids, old_guids, base_index + BI_WWPNS, BX_WWPNS,    "WWPN");
     }

    // Init SysGuid
    //INCR_GUID(base_guid1, user_guids[Operations::BI_SYS_GUID], 7);
    guid_index =  Operations::BI_SYS_GUID;
    printf("    System   GUID:      ");
    PrintGuidLine(new_guids, old_guids,  guid_index);
    return true;
}

bool Operations::reportGuidChaneges(ImageInfo* info, guid_t new_guids[MAX_GUIDS], guid_t old_guids[MAX_GUIDS],
                      bool print_guids, bool print_macs, bool print_uids)
{

    printf("    You are about to change the Guids/Macs/Uids on the device:\n\n");
    printf("                        New Values      " GUID_SPACES "Current Values\n");
    if (print_uids) {
        PrintUids(new_guids, old_guids );
    } else {
       PrintGUIDs(new_guids,
                  old_guids,
                  print_guids,
                  print_macs,
                  info->guidNum < Operations::GUIDS);
    }
    if (!ask_user())
        return false;

    return true;
}

bool Operations::preFS2PatchGUIDs(bool      patch_macs,
        bool      patch_uids,
        bool      user_guids,
        bool      user_macs,
        bool      user_uids,
        guid_t    new_guids[MAX_GUIDS],
        guid_t    old_guids[MAX_GUIDS],
        guid_t    **used_guids_p,
        u_int32_t num_of_old_guids)
{
    int i;
    guid_t*         used_guids;
    *used_guids_p = old_guids ? old_guids : new_guids;

    if (new_guids) {
        // if only guids or only macs are specified by user, keep the other
        // as currently set of flash. This is in order to simplify transitions between
        // burning IB and ETH FW.
        if (!patch_uids) {
            if (old_guids && !user_guids) {
                for (i = 0; i < GUIDS; i++) {
                    new_guids[i] = old_guids[i];
                }
            }

            if (old_guids && !user_macs) {
                for (i = GUIDS; i < MAX_GUIDS; i++) {
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
                for (i = 0 ; i < MACS; i++) {
                    u_int64_t mac  =  old_guids[i+1].h >> 8;
                    mac <<= 24;
                    mac |= (old_guids[i+1].l & 0xffffff);

                    old_guids[GUIDS+i].h = u_int32_t(mac >> 32);
                    old_guids[GUIDS+i].l = u_int32_t(mac  & 0xffffffff);

                    // printf("-D- Guid " GUID_FORMAT " to MAC "MAC_FORMAT"\n", old_guids[i+1].h, old_guids[i+1].l, old_guids[i+GUIDS].h,old_guids[i+GUIDS].l  );
                }
            }

            guid_t* macs = &used_guids[4];
            int i;

            for (i = 0 ; i < Operations::MACS ; i++) {
                u_int64_t mac = (((u_int64_t)macs[i].h) << 32) | macs[i].l;
                if (!_burn_blank_guids && !CheckMac(mac)) {
                    report_err(_err_msg, "Bad mac (" MAC_FORMAT ") %s: %s. Please re-burn with a valid -mac flag value.\n",
                           macs[i].h,
                           macs[i].l,
                           user_macs ? "given" : "found on flash",
                           err());
                    return false;
                }

            }
        }
    } else {
        if (!_burn_blank_guids) {
            for (i = 0; i < BX_SLICES_NUM; i++ ) {
                if (ReportBxMacsWarnings(used_guids, i, 0, user_uids) == false) {
                    return false;
                }
            }

        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////
bool Operations::patchGUIDs (FImage&   f,
                             ImageInfo* info,
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
    u_int32_t       *buf = f.getBuf();
    bool old_guids_fmt = info->guidNum < GUIDS;

    // Print old GUIDs and get confirmation
    if (new_guids) {
        if (old_guids_fmt) {
            printf("    Old image!!!! Only %d GUIDs may be set.\n", info->guidNum);
        }
    }
    // Call common function
    if (!preFS2PatchGUIDs(patch_macs, patch_uids, user_guids, user_macs, user_uids, new_guids, old_guids, &used_guids, num_of_old_guids)) {
        return false;
    }
    // Path GUIDs section
    if (info->guidPtr) {
        patchGUIDsSection(buf, info->imgStart + info->guidPtr, used_guids, info->guidNum);

        if (info->allImgStart[1]) {
            // For no ConnectX HCAs, patch also the secondary image (if found). This is applicable
            // only for nofs burn, where both images are burnt as is.
            patchGUIDsSection(buf, info->allImgStart[1] + info->guidPtr, used_guids, info->guidNum);
        }
    }
    return true;
} // patchGUIDs


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                  Revision info and board ID                        //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////

bool Operations::QueryImage (FBase& f,
                             Operations::ImageInfo* info) {

    u_int32_t guid_ptr, nguids;
    guid_t guids[MAX_GUIDS];
    // FW ID
    u_int32_t fw_id;
    u_int32_t fw_id_offs;
    u_int32_t fw_size;
    u_int32_t im_start = info->imgStart;

    if (IsFs2()) {
        if (IsFs2() == FS_FS3_GEN) {
            // For FS3 image there is no need for the QueryImage
            return true;
        }
        if (info->isFailsafe && info->actuallyFailsafe) {
            f.set_address_convertor(info->cntxLog2ChunkSize, im_start != 0);
        } else {
            f.set_address_convertor(0,0);
        }

        im_start = 0; // offset is done by address convertor
        info->magicPatternFound = true;
        fw_id_offs = 0x20;
    } else {
        info->magicPatternFound = false;
        fw_id_offs = 0x10;
    }

    READ4(f, im_start + fw_id_offs, &fw_id, "FW ID");
    TOCPU1(fw_id);

    READ4(f, im_start + fw_id_offs + 0x10, &fw_size, "FW SIZE");
    TOCPU1(fw_size);
    info->imageSize = fw_size;

    info->devRev  = fw_id >> 24;
    // Read GUIDs
    READ4(f, im_start + fw_id_offs + 0x14 , &guid_ptr, "GUID PTR");
    TOCPU1(guid_ptr);
    info->guidPtr = guid_ptr;

    guid_ptr += im_start;
    if (guid_ptr >= f.get_size()) {
        return errmsg("Failed to read GUIDs - Illegal GUID pointer (%08x). Probably image is corrupted", guid_ptr);
    }
    READ4(f, guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
    TOCPU1(nguids);
    nguids /= 2;
    if (nguids > MAX_GUIDS) {
        return errmsg("Failed to read GUIDs - Illegal Number of GUIDs (%d)", nguids);
        //return false;
    }
    READBUF(f, guid_ptr, guids, nguids * sizeof(u_int64_t), "GUIDS");
    TOCPUBY64(guids);

    u_int32_t guids_crc;
    READ4(f, guid_ptr + nguids * sizeof(u_int64_t), &guids_crc, "GUIDS CRC");
    guids_crc = __be32_to_cpu(guids_crc);

    info->blankGuids = true;
    if ((guids_crc & 0xffff) != 0xffff ) {
        info->blankGuids = false;
    }

    info->guidNum = nguids;
    for (u_int32_t i = 0 ; i < nguids ; i++) {
        info->guids[i] = guids[i];
        if (guids[i].h != 0xffffffff || guids[i].l != 0xffffffff) {
            info->blankGuids = false;
        }
    }
    // Expansion Rom version:
    if (info->_rom_sect.empty()) {
        info->expRomFound = false;
    } else {
        info->expRomFound = true;
        // There is no check for the return value of this function because it's a wrapper that always succeeds,
        // but fills the error string when there is an error
        GetExpRomVersionWrapper(info);
    }

    // Read Info:
    u_int32_ba info_ptr_ba;
    u_int32_t  info_ptr;
    u_int32_t  info_size;
    u_int8_t   info_ptr_cs = 0;
    READ4(f, im_start + fw_id_offs + 0xC, &info_ptr, "INFO PTR");
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
        info->infoSectPtr = info_ptr;

        info_ptr += im_start;
        if (info_ptr >= f.get_size()) {
            return errmsg("Failed to read Info Section - Info section pointer (%08x) too large. Probably the image is corrupted.", info_ptr);
        }
        READ4(f, info_ptr - 3*sizeof(u_int32_t), &info_size, "Info section size");
        TOCPU1(info_size);

        // byte size;
        info_size *= 4;
        vector<u_int8_t> info_buff_vect(info_size);
        u_int8_t* info_buff = (u_int8_t*)(&info_buff_vect[0]);
        READBUF(f, info_ptr, info_buff, info_size, "Info Section");

        if (!ParseInfoSect(info_buff, info_size,  info)) {
            return false;
        }
    }

    info->imageOk = true;
    return true;
}


bool Operations::ParseInfoSect(u_int8_t* buff, u_int32_t byteSize, Operations::ImageInfo *info) {

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
            info->fwVer[0] = u_int16_t(__be32_to_cpu(*(p+1)) >> 16);
            tmp = __be32_to_cpu(*(p+2));
            info->fwVer[1] = tmp >> 16;
            info->fwVer[2] = tmp & 0xffff;
            break;

        case II_MinFitVersion:
            tmp = __be32_to_cpu(*(p+1));
            info->minFitVer[0] = tmp >> 16;
            info->minFitVer[1] = tmp & 0xffff;
            tmp = __be32_to_cpu(*(p+2));
            info->minFitVer[2] = tmp >> 16;
            info->minFitVer[3] = tmp & 0xffff;
            break;
        case II_MicVersion:
            tmp = __be32_to_cpu(*(p+1));
            info->micVer[0] = tmp >> 16;
            //info->minFitVer[1] = tmp & 0xffff;
            tmp = __be32_to_cpu(*(p+2));
            info->micVer[1] = tmp >> 16;
            info->micVer[2] = tmp & 0xffff;
            break;
        case II_DeviceType:
            tmp = __be32_to_cpu(*(p+1));
            info->devType = tmp & 0xffff;
            //info->devRev  = (tmp >> 16) & 0xff;
            break;

        case II_VsdVendorId:
            tmp = __be32_to_cpu(*(p+1));
            info->vsdVendorId    = tmp & 0xffff;
            break;

        case II_IsGa:
            tmp = __be32_to_cpu(*(p+1));
            info->isGa = tmp ? true : false;;
            break;

        case II_PSID:
            // set psid only if not previosly found in PS
            if (!info->psOk) {
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < PSID_LEN ; i++) {
                    info->psid[i] = str[i];
                }
                info->psid[PSID_LEN] = '\0';
            }
            break;

        case II_VSD:
            // set psid only if not previosly found in PS
            if (!info->psOk) {
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < VSD_LEN ; i++) {
                    info->vsd[i] = str[i];
                }
                info->vsd[VSD_LEN] = '\0';
            }
            break;

        case II_ProductVer:

            str = (const char*)p;
            str += 4;

            for (int i = 0 ; i < PRODUCT_VER_LEN ; i++) {
                info->productVer[i] = str[i];
            }
            info->productVer[PRODUCT_VER_LEN] = '\0';
            break;
        case II_HwDevsId:
           u_int32_t i;
           for (i = 1; i <= (tagSize / 4); i++) {
               info->supportedHwId[i - 1] = __be32_to_cpu(*(p + i));
           }
           info->supportedHwIdNum = tagSize / 4;
           break;
        case II_HwAccessKey: {
            info->accessKeyValue.h = __be32_to_cpu(*(p + 1));;
            info->accessKeyValue.l = __be32_to_cpu(*(p + 2));;
            info->accessKeyExists= 1;
        }
            break;
        case II_TRACER_HASH: {
            GetSectData(info->TracerHashSectZipped, p + 1, tagSize);
        }
            break;
        case II_End:
            endFound = true;
            break;

        case II_CONFIG_AREA: {
            info->configSectors = __be32_to_cpu(*(p + 1));
            info->configPad = __be32_to_cpu(*(p + 2));
        }
            break;

            //default:
            //printf("-D- Found tag ID %d of size %d - ignoring.\n", tagId, tagSize);
        }

        if (tagId < II_Last) {
            info->infoOffs[tagId] = offs + 4;
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

bool Operations::GetExpRomStrVer(Operations::ImageInfo* info, char* version) {
    if (info->romInfo[0].expRomProductId >= 0x10) {
        sprintf(version, "%d.%d.%d", info->romInfo[0].expRomVer[0], info->romInfo[0].expRomVer[1],
                info->romInfo[0].expRomVer[2]);
    } else {
        sprintf(version, "%d", info->romInfo[0].expRomVer[0]);
    }
    return true;
}

bool Operations::DisplayOneExpRomInfo(RomInfo* info) {

    if (info->expRomProductId == 0xf) {
        report("devid=%d version_id=%s", info->expRomDevId,
                info->expRomFreestr);
    } else {
        report("type=");
        switch (info->expRomProductId) {
        case 1:
            report("CLP1 ");
            break;
        case 2:
            report("CLP2 ");
            break;
        case 3:
            report("CLP3 ");
            break;
        case 4:
            report("CLP4 ");
            break;
        case 0x10:
            report("PXE  ");
            break;
        case 0x11:
            report("UEFI ");
            break;
        case 0x21:
            report("FCODE ");
            break;

        default:
            report("0x%x - Unknown ROM product ID\n", info->expRomProductId);
            return true;
        }

        report("version=%d", info->expRomVer[0]);
        if (info->expRomProductId >= 0x10) {
            report(".%d.%d", info->expRomVer[1], info->expRomVer[2]);

            if (info->expRomDevId != EXP_ROM_GEN_DEVID) {
                // Do not display if 0 - ROM is the same for all device IDs
                report(" devid=%d", info->expRomDevId);
            }
            if (info->expRomPort) {
                // Do not display if 0 - port independent
                report(" port=%d", info->expRomPort);
            }

            report(" proto=");
            switch (info->expRomProto) {
            case ER_IB:
                report("IB");
                break;
            case ER_ETH:
                report("ETH");
                break;
            case ER_VPI:
                report("VPI");
                break;
            default:
                report("0x%x", info->expRomProto);
            }
        }
    }
    return true;

}
bool Operations::DisplayExpRomInfo(Operations::ImageInfo* info, char *pre_str) {
    int i;
    int str_len = strlen(pre_str);

    if (info->numOfExpRom > 0) {
        for (i = 0; i < info->numOfExpRom; i++) {

            // Print the pre string or spaces
            if (i == 0) {
                report("%s", pre_str);
            } else {
                int j;
                for ( j = 0; j < str_len; j++) {
                    printf("%s", " ");
                }
            }
            // Display a ROM info
            DisplayOneExpRomInfo(&(info->romInfo[i]));
            if (i != info->numOfExpRom - 1) { // Don't print new line after the info of the last ROM
                report("\n");
            }
        }
        if (info->expRomWarning) {
            report(" (-W- %s)", info->expRomWarningMsg);
        }
        report("\n");
    } else {
        report("%s", pre_str);
        report("N/A");
        if (info->expRomErrMsgValid) {
            report(" (-E- %s)", info->expRomErrMsg);
        }
        report("\n");
    }
    return true;
}

bool Operations::ReportBxGuidsQuery(guid_t* guids, int base1, int guids_num, int index, const char* pre_str)
{
    int i, first_index, base, wwnns_index;

    report("G%d %-14s", index, pre_str);
    first_index = index * BX_SLICE_GUIDS;
    if (base1 == BI_WWPNS) {
        wwnns_index = first_index + (BX_SLICE_GUIDS - 1);
        report(GUID_FORMAT " ", guids[wwnns_index].h, guids[wwnns_index].l);
    }
    base = first_index + base1;
    for (i = base; i < base + guids_num; i++) {
        int j = i;
        // HACK
        if (i == BI_GUIDS + BX_SLICE_GUIDS) {
            // We display the same node guid on the two slices.
            j = BI_GUIDS;
        }
        report(GUID_FORMAT " ", guids[j].h, guids[j].l);
    }
    printf("\n");
    return true;
}


#define PRINT_WARNING "PRINT_WARNING"

bool Operations::ReportBxMacsQuery(guid_t* guids, int base1, int guids_num, int index, const char* pre_str)
{
    int i, base;

    base = index * Operations::BX_SLICE_GUIDS + base1;
    report("G%d %-30s", index, pre_str);
    for (i = base; i < base + guids_num; i++) {
            report("     " MAC_FORMAT , guids[i].h, guids[i].l);
    }
    printf("\n");
    return true;
}

bool Operations::ReportBxMacsWarnings(guid_t* guids, int index, int warning, int user_uids)
{
    int i, base;
    int is_first = 1;
    base = index * BX_SLICE_GUIDS + BI_IMACS;
    for (i = base; i < base + BX_MACS; i++) {
         u_int64_t mac = (((u_int64_t)guids[i].h) << 32) | guids[i].l;
         if (!CheckMac(mac)) {
             if (warning) {
                 if (is_first) {
                     printf("\n\n");
                     is_first = 0;
                 }
                 printf("Warning: Bad mac address (" MAC_FORMAT "): %s\n", guids[i].h, guids[i].l, err());
             } else {
                 report_err(_err_msg, "Bad mac (" MAC_FORMAT ") %s: %s. Please re-burn with a valid MACs value.\n",
                        guids[i].h,
                        guids[i].l,
                        user_uids ? "given" : "found on flash",
                        err());
                 return false;
             }
         }
     }
     return true;
}

bool Operations::DisplayFs3Uids(Operations::ImageInfo* info)
{
    report("Description:     UID                GuidsNumber  Step\n");
    PRINT_FS3_UIDS(info->fs3_uids_info.guids[0], info->orig_fs3_uids_info.guids[0], "GUID1");
    PRINT_FS3_UIDS(info->fs3_uids_info.guids[1], info->orig_fs3_uids_info.guids[1], "GUID2");
    PRINT_FS3_UIDS(info->fs3_uids_info.macs[0], info->orig_fs3_uids_info.macs[0], "MAC1");
    PRINT_FS3_UIDS(info->fs3_uids_info.macs[1], info->orig_fs3_uids_info.macs[1], "MAC2");
    return true;
}

bool Operations::DisplayOldUids(Operations::ImageInfo* info)
{
    const char* mac_indent = "";
    bool ib_dev;
    bool eth_dev;
    SetDevFlags(info->devType, ib_dev, eth_dev);

    // GUIDS:
    // TODO: Handle case where devtype not found.

    if (IsBridgeX(info->devType)) {
        int i, base;
        if (info->guidNum != BX_ALL_GUIDS) {
            report_err(_err_msg, "Number of UIDs on BridgeX should be %d\n", BX_ALL_GUIDS);
            return false;
        }
        report("Description:     Node             Port1            Port2            Port3            Port4\n");
        for (i = 0; i < BX_SLICES_NUM; i++) {
            base = i * BX_SLICE_GUIDS;
            ReportBxGuidsQuery(info->guids, BI_GUIDS,  BX_NP_GUIDS, i, "GUIDs:");
            ReportBxMacsQuery(info->guids,  BI_IMACS, BX_IMACS,    i, "IMACs:");
            ReportBxMacsQuery(info->guids,  BI_EMACS, BX_EMACS,    i, "EMACs:");
            ReportBxGuidsQuery(info->guids, BI_WWPNS, BX_WWPNS,    i, "WWNs: ");
        }
        report("SYS GUID:        " GUID_FORMAT " ", info->guids[info->guidNum - 1].h, info->guids[info->guidNum - 1].l);
        if (!info->blankGuids) {
            for (i = 0; i < BX_SLICES_NUM; i++) {
                ReportBxMacsWarnings(info->guids, i, 1, 0);
            }
        }
    } else {
        if (ib_dev) {
            //report("GUID Des:        Node             Port1            ");
            report("Description:     Node             ");
            if (_num_ports > 0)
                report("Port1            ");
            if (_num_ports > 1)
                report("Port2            ");
            report( "Sys image\n");

            report("GUIDs:           ");
            for (u_int32_t i=0; i < GUIDS; i++) {
                if ((i == 1 && _num_ports < 1) ||
                    (i == 2 && _num_ports < 2)) {
                    continue;
                }
                report(GUID_FORMAT " ", info->guids[i].h, info->guids[i].l);
            }
            if (_num_ports > 0) {
                mac_indent = "                 ";
            }
        }
        // MACS:
        if (eth_dev) {
            if (info->guidNum == 6) {
                if (!ib_dev) {
                    report("Description:%s     Port1            Port2\n", mac_indent);
                } else if (IsSX(info->devType)) {
                    report("\nDescription:     Base             Switch\n");
                } else {
                    printf("\n");
                }
                report("MACs:    %s       ", mac_indent);
                for (u_int32_t i=GUIDS; i < 6; i++) {
                    report("     " MAC_FORMAT , info->guids[i].h, info->guids[i].l);
                }

                for (u_int32_t i=GUIDS; i < 6; i++) {
                    u_int64_t mac = (((u_int64_t)info->guids[i].h) << 32) | info->guids[i].l;
                    if (!info->blankGuids && !CheckMac(mac)) {
                        if (i==GUIDS) printf("\n\n");
                        printf("Warning: Bad mac address (" MAC_FORMAT "): %s\n", info->guids[i].h, info->guids[i].l, err());
                    }
                }
            } else {
                report_warn("Can not get MAC address: Expecting %d entries in guid section, got %d. Probably an old FW image. Please update.\n",
                       6,
                       info->guidNum);
            }
        }
    }
    report("\n");
    return true;
}

bool Operations::DisplayImageInfo(Operations::ImageInfo* info, bool full_query) {

    // printf("Config Exists= %d\n", info->configExists);
    report("Image type:      %s\n",
            info->magicPatternFound ?
            ( (IsFs2() == FS_FS3_GEN) ? "FS3" :
              (CntxIsEth(info->devType) ? "ConnectX" : "FS2")) :
            info->isFailsafe        ? "Failsafe" :
              "Short");

    if (info->infoOffs[II_FwVersion]) {
        report("FW Version:      %d.%d.%d\n", info->fwVer[0], info->fwVer[1], info->fwVer[2]);
    }


    if (full_query) {
        if (info->infoOffs[II_MinFitVersion]) {
            report("Min FIT Version: %d.%d.%d.%d\n", info->minFitVer[0], info->minFitVer[1], info->minFitVer[2], info->minFitVer[3]);
        }
        if (info->infoOffs[II_MicVersion]) {
            report("MIC Version:     %d.%d.%d\n", info->micVer[0], info->micVer[1], info->micVer[2]);
        }
        if (info->configSectors) {
            report("Config Sectors:  %d\n", info->configSectors);
        }
        if (info->configPad) {
            report("Config Pad:      %d\n", info->configPad);
        }
        // TODO: Print the HW dev IDs
    }



    if (info->infoOffs[II_ProductVer] && strlen(info->productVer)) {
        report("Product Version: %s\n", info->productVer);
    }

    if (info->expRomFound) {
        DisplayExpRomInfo(info, "Rom Info:        ");
    }

    if (info->isFailsafe && !IsFs2()) {
        report("I.S. Version:    %d\n", info->isVer );
    }

    if (info->infoOffs[II_DeviceType]) {
        report("Device ID:       %d\n", info->devType);
        if (info->devType == 25204 || info->devType == 24204) {
            _num_ports = 1;
        } else if (IsIs4(info->devType) || IsSX(info->devType)) {
            _num_ports = 0;
        }
    }

    if (info->accessKeyExists) {
        report("HW Access Key:   ");
        if (info->accessKeyValue.l || info->accessKeyValue.h) {
            report("Enabled\n");
        } else {
            report("Disabled\n");
        }

    }


    if (IsFs2() == FS_FS3_GEN) {
        if (!DisplayFs3Uids(info)) {
            return false;
        }
    } else {
        if (!DisplayOldUids(info)) {
            return false;
        }
    }


    // VSD, PSID
    if (!info->infoOffs[II_VsdVendorId] || info->vsdVendorId == MELLANOX_VENDOR_ID) {
        if (info->isFs3) {
            report("Image VSD:       %s\n", info->image_vsd);
            report("Device VSD:      %s\n", info->vsd);
            report("PSID:            %s\n", info->psid);
            if (strncmp(info->psid, info->orig_psid, 13) != 0) {
                report("Orig PSID:       %s\n", info->orig_psid);
            }
        } else {
            report("VSD:             %s\n", info->vsd);
            report("PSID:            %s\n", info->psid);
        }
    } else {
        report_warn("Not a Mellanox FW image (vendor_id = 0x%04x). VSD and PSID are not displayed.\n", info->vsdVendorId);
    }

    if (info->infoOffs[II_IsGa]) {
        if (!info->isGa) {
            report("BOARD GA:        no\n");
        }
    }

    if (info->blankGuids) {
        report_warn("GUIDs%s values and their CRC are not set.\n",
               IsFs2() ? "/MACs" : ""); // TODO: IsConnectX?
    }
    return true;
}

bool Operations::PrintMissGuidErr(bool ib_dev, bool eth_dev, bool bx_dev)
{
    const char* missing_info;
    const char* missing_flags;

    if (bx_dev) {
        missing_info  = "UIDs (GUIDs / MACs / WWNs)";
        missing_flags = "-uid(s)";
    } else {
        if (ib_dev && eth_dev) {
            missing_info  = "GUIDs / MACs";
            missing_flags = "-guid(s) / -mac(s)";
        } else if (ib_dev) {
            missing_info  = "GUIDs";
            missing_flags = "-guid(s)";
        } else {
            missing_info  = "MACs";
            missing_flags = "-mac(s)";
        }

    }
    return errmsg("Please specify %s (using command line flags %s ).", missing_info, missing_flags);
}


bool Operations::CopyData(u_int8_t* &new_image, u_int8_t* &old_image, int copy_size)
{
    memcpy(new_image, old_image, copy_size);

    new_image += copy_size;
    old_image += copy_size;

    return true;
}
#define READ_DW(dw, data) {\
    dw = (*((u_int32_t*)(data)));\
    TOCPU1(dw);\
}

bool Operations::CopyBoot2(u_int8_t* &new_image_p, u_int8_t* &old_image_p)
{
    u_int32_t size;
    READ_DW(size, old_image_p + 4);
    size = (size + 4) * 4;
    CopyData(new_image_p, old_image_p, size);
    return true;
}

bool Operations::AddNewSect(u_int8_t* &new_image_p, u_int8_t* data, GPH gph, u_int32_t* last_next)
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


#define GUID_PTR_OFF    0x34
#define IMAGE_INFO_PTR  0x2c
#define IMAGE_SIZE_OFF  0x30
#define IMAGE_ROM_INDEX 2

#define COPY_DW(dest, dword) {\
    CPUTO1(dword);\
    memcpy(dest, &dword, 4);\
}
#define MAJOR_MOD_ROM_FW    2
#define MINOR_MOD_ROM_FW    6
#define SUBMINOR_MOD_ROM_FW 1410

bool Operations::IsFwSupportingRomModify(u_int16_t fw_ver[3])
{
    u_int16_t supported_fw[3] = {MAJOR_MOD_ROM_FW,  MINOR_MOD_ROM_FW, SUBMINOR_MOD_ROM_FW};
    return !FwVerLessThan(fw_ver, supported_fw);
}
u_int32_t Operations::CalcImageCRC(u_int32_t* buff, u_int32_t size)
{
    Crc16 crc;
    TOCPUn(buff, size);
    CRCn(crc, buff, size);
    CPUTOn(buff, size);
    crc.finish();
    u_int32_t new_crc = crc.get();
    return new_crc;
}

bool Operations::UpdateFullImageCRC(u_int32_t* buff, u_int32_t size, bool blank_guids)
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
#define MAX_SUPPORTED_MAJOR_MIC_VER 1
bool Operations::CheckImageFormatCompat(u_int16_t micVer[3])
{
    if (micVer[0] > MAX_SUPPORTED_MAJOR_MIC_VER) {
        return false;
    }
    return true;
}

bool Operations::GetInfoAndCheckCompt(FBase& f, ImageInfo& info, bool& fwInfoOK, bool ignoreCompatCheck)
{
#define NO_COMPAT_MSG_LEN 256
    const char *fw_type = f.is_flash() ? "burnt"   : "new";
    const char *op_type = f.is_flash() ? "updated" : "burnt";
    bool old_silent = _silent;


    _silent = true;
    if (IsFs2() && VerifyFs2(f, &info, false, true) && QueryAll(f, &info)) {
        fwInfoOK = true;
        if (!CheckImageFormatCompat(info.micVer)) {
            char no_compat_msg[NO_COMPAT_MSG_LEN] = {0};
            snprintf(no_compat_msg, NO_COMPAT_MSG_LEN - 1, "The %s FW image was generated by newer tools (Format version: %d.%d.%d)",
                    fw_type, info.micVer[0], info.micVer[1], info.micVer[2]);
            if (!ignoreCompatCheck) {
                return errmsg("%s and cannot be %s/queried by this version of tool.\n", no_compat_msg, op_type);
            } else {
                report_warn("%s\n", no_compat_msg);
            }
        }
    }
    _silent = old_silent;

    return true;
}


// UpdateRomInImage: it will insert the rom if it receive rom data,
//                   otherwise it will remove the rom if it is existing.
bool Operations::UpdateRomInImage(u_int8_t* new_image, u_int8_t* old_image, u_int8_t* rom_data, int rom_size,
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
            int i;
            for (i = 0; i < 3; i++) {
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

    *new_image_size = size;

    COPY_DW(new_image + IMAGE_SIZE_OFF, size);

    // Writing 0 on the CRC existing field to let the tool verify the image
    // and get some information which will be needed later.
    u_int32_ba crc_dw = TOCPU1(*(u_int32_t*)(&new_image[IMG_CRC_OFF]));
    crc_dw.range(23, 16) = 0;
    (*(u_int32_t*)(&new_image[IMG_CRC_OFF])) = CPUTO1(crc_dw);

    return true;
}

bool Operations::IsRomEmpty(ImageInfo* info)
{
    return info->_rom_sect.empty();
}
bool Operations::CheckDevImage(FBase& f, ImageInfo& flash_info, u_int8_t read_flash)
{
    bool curr_silent = _silent;
    _silent = true;
    SectionType seciotn = H_LAST;

    if (GetQuickQuery()) {
        if (read_flash ) {
            seciotn = H_ROM;
        }
        initSectToRead(seciotn);
    }

    bool flash_query_res = Verify(f, &flash_info) && QueryAll(f, &flash_info);
    if (!flash_query_res) {
        return errmsg("Bad FW Image on the flash");
    }
    if (!CntxIsEth(flash_info.devType) && !CntxIsIb(flash_info.devType)) {
        // TODO: Indicate the device name.
        return errmsg("Unsupported device type %d", flash_info.devType);
    }
    _silent = curr_silent;
    return true;
}
bool Operations::CheckDevImageAndRom(FBase& f, ImageInfo& flash_info)
{
    // Common check for the ROM.
    if (!CheckDevImage(f, flash_info, 1)) {
        return errmsg(err());
    }
    if (IsRomEmpty(&flash_info)) {
        return errmsg("Read ROM failed: The FW does not contain a ROM section");
    }
    return true;

}



bool Operations::IntegrateDevRomInImage(FImage& fim, ImageInfo& flashInfo, ImageInfo& fileInfo)
{
    u_int32_t rom_size = flashInfo._rom_sect.size();
    u_int32_t  new_image_size = fim.getBufLength() + TOTAL_SEC_SIZE(rom_size);
    vector<u_int8_t> new_data(new_image_size);
    int actual_image_size;

    // Compine the image and the rom into new daa
    if(!UpdateRomInImage((u_int8_t*)(&new_data[0]), (u_int8_t*)(fim.getBuf()),
                         (u_int8_t*)(&flashInfo._rom_sect[0]), rom_size, &actual_image_size)) {
        return errmsg(err());
    }

    // close old image and open new image with the rom.
    fim.close();
    fim.open((u_int32_t*)(&new_data[0]), actual_image_size);

    if (!VerifyFs2(fim, &fileInfo, false, false, true) || !QueryAll(fim, &fileInfo)) {
        return errmsg(err());
    }

    return true;
}


bool Operations::CheckCommandInputs(const char* dev,
                        const char* img,
                        CommandType cmd) {

    const CommandInfo* cmdInfo = GetCommandInfo(cmd);

    if (!cmdInfo) {
        report_err(_err_msg, "Internal error: Unknown command given to CheckCommandInputs() (%d)\n", cmd);
        return false;
    }

    const char* inputDesStr [] = {
        NULL,
        "neither a device nor an image file",       // CI_NONE
        "an image file",                            // CI_IMG_ONLY,
        NULL,
        "a device",                                 // CI_DEV_ONLY,
        NULL,
        "either an image file or a device",         // CI_IMG_OR_DEV,
        NULL,
        "both an image file and a device"           // CI_IMG_AND_DEV
    };

    CommandInput given;

    if ( dev && img) {
        given = CI_IMG_AND_DEV;
    } else if (!dev && img) {
        given = CI_IMG_ONLY;
    } else if (dev && !img) {
        given = CI_DEV_ONLY;
    } else {
        given = CI_NONE;
    }

    if ((given & cmdInfo->requiredInput) == 0) {
        report_err(_err_msg, "Command \"%s\" requires %s to be specified",
               cmdInfo->cmdName,
               inputDesStr[cmdInfo->requiredInput]);

        if (given != CI_NONE) {
            printf(", but %s %s given.\n",
                   inputDesStr[given],
                   given == CI_IMG_AND_DEV ? "are" : "is");
        } else {
            printf(".\n");
        }

        return false;
    }

    return true;
}

bool Operations::CheckMaxCmdArguments(CommandType cmd, int numArgs) {
    const CommandInfo* cmdInfo = GetCommandInfo(cmd);
    if (!cmdInfo) {
        report_err(_err_msg, "Internal error: Unknown command given to CheckMaxCmdArguments (%d)\n", cmd);
        return false;
    }

    if (cmdInfo->maxArgs >= 0 && numArgs > cmdInfo->maxArgs) {
        report_err(_err_msg, "Command \"%s\" requires %d arguments, but %d arguments were given\n",
               cmdInfo->cmdName,
               cmdInfo->maxArgs,
               numArgs);
        return false;
    }
    return true;
}

