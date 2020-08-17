
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "image_access.h"
#include "img_version.h"
#include <string.h>
#include <iostream>
#include <mfa.h>
#include <mlxfwops.h>
#include <pldm_pkg.h>
#include <pldm_dev_id_record.h>
#include <pldm_component_image.h>
#include <tools_layouts/image_info_layouts.h>

using namespace std;


ImageAccess::ImageAccess(int compareFFV)
{
    _imgFwOps   = NULL;
    _compareFFV = compareFFV;
    memset(&_imgFwParams, 0, sizeof(_imgFwParams));
    memset(_errBuff, 0, sizeof(_errBuff));
}

ImageAccess::~ImageAccess()
{
    if (_imgFwOps) {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }
}

bool ImageAccess::hasMFAs(string directory)
{
    DIR *d;
    struct dirent *dir;
    int rc;
    d = opendir(directory.c_str());
    if (d == NULL) {
        return false;
    }
    while ((dir = readdir(d)) != NULL) {
        string fl = dir->d_name;
        if (fl == "." || fl == "..") {
            continue;
        }
        string fpath = directory;
        fpath += "/";
        fpath += fl;
        rc = getFileSignature(fpath);
        if (rc == IMG_SIG_TYPE_BIN || rc == IMG_SIG_TYPE_MFA) {
            closedir(d);
            return true;
        }
    }
    closedir(d);
    return false;

}
int ImageAccess::queryDirPsid(string &path, string &psid, string &selector_tag, int image_type, vector<PsidQueryItem> &riv)
{
    int res = 0;
    DIR *d;
    struct dirent *dir;
    int found = 0;
    int rc;

    d = opendir(path.c_str());
    if (d == NULL) {
        return -1;
    }

    while ((dir = readdir(d)) != NULL) {
        PsidQueryItem ro;
        string fl = dir->d_name;
        if (fl == "." || fl == "..") {
            continue;
        }
        string fpath = path;
        fpath += "/";
        fpath += fl;

        rc = this->queryPsid(fpath.c_str(), psid, selector_tag, image_type, ro);
        if (rc < 0) {
            res = -1;
            goto clean_up;
        }
        if (rc == 1) {
            riv.push_back(ro);
            found++;
            riv[0].found = found;
            res = 1;
        }
    }

    if (found > 1) {
        res = -2;
    }

clean_up:
    closedir(d);
    return res;
}

bool ImageAccess::openImg(fw_hndl_type_t hndlType, char *psid, char *fileHndl)
{

    memset(_errBuff, 0, sizeof(_errBuff));
    _imgFwParams.errBuff      = _errBuff;
    _imgFwParams.errBuffSize  = MLNX_ERR_BUFF_SIZE;
    _imgFwParams.hndlType     = hndlType;
    _imgFwParams.psid         = psid;
    _imgFwParams.fileHndl     = fileHndl;
    _imgFwParams.shortErrors  = true;
    _imgFwOps = FwOperations::FwOperationsCreate(_imgFwParams);
    if (_imgFwOps == NULL) {
        _errMsg  = "-E- " + (string)_errBuff + "\n";
        if (_errMsg.find("upgrade tool") != std::string::npos) {
            _warning = _errMsg;
        } else if (_errMsg.find("with higher Version") != std::string::npos) {
            _warning = _errMsg;
        }
        _log    += _errMsg;
        return false;
    }
    return true;

}

int ImageAccess::queryPsid(const string &fname, const string &psid,
                           string &selector_tag, int image_type,
                           PsidQueryItem &ri)
{
    int res = 0;
    mfa_desc *mfa_d = NULL;
    fw_info_t img_query;
    string iniName = "";
    vector<u_int8_t> sect; // to get fw configuration.
    vector<u_int8_t> dest;

    if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str())) {
        return 0;
    }

    ri.psid = psid;
    ri.found = 0;

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true)) {
        _errMsg  = "Failed to query " +  (string)_imgFwOps->err();
        _log += _errMsg;
        goto clean_up;
    }

    if (!psid.compare(img_query.fw_info.psid)) {
        u_int32_t *supporteHwId;
        u_int32_t supporteHwIdNum;
        _imgFwOps->getSupporteHwId(&supporteHwId, supporteHwIdNum);
        ri.found = 1;
        ri.url = fname;
        ri.pns = "";
        ri.devId = (supporteHwIdNum > 0) ? supporteHwId[0] : 0;
        ri.revId = (ri.devId >> 16) & 0xffff;
        ri.devId = ri.devId & 0xffff;
        ri.isFailSafe = img_query.fw_info.is_failsafe;
        if (_imgFwOps->FwGetSection(H_FW_CONF, sect)) {
            if (unzipDataFile(sect, dest, "Fw Configuration")) {
                char *ptr = strstr((char*)&dest[0], "Name =");
                int counter = 7;
                while (ptr and * ptr != '\n' and * ptr != '\r') {
                    if (counter-- > 0) {
                        ptr++;
                        continue;
                    }
                    iniName += *ptr;
                    ptr++;
                }
            }
        }
        ri.iniName = iniName;
        if (!mfa_open_file(&mfa_d, (char*)fname.c_str())) {
            char *pn =  mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"PN");
            if (pn != NULL) {
                ri.pns = pn;
                free(pn);
            }
            char *desc =  mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"DESCRIPTION");//TODO: Make more efficient
            if (desc != NULL) {
                ri.description = desc;
                free(desc);
            }
            mfa_close(mfa_d);
        }
        if (!_compareFFV) {
            ImgVersion imgv;
            imgv.setVersion("FW", 3, img_query.fw_info.fw_ver,
                    img_query.fw_info.branch_ver);
            ri.imgVers.push_back(imgv);
        } else {
            u_int16_t fwVer[4];
            fwVer[0] = img_query.fw_info.fw_ver[0];
            fwVer[1] = img_query.fw_info.fw_ver[1];
            fwVer[2] = img_query.fw_info.fw_ver[2] / 100;
            fwVer[3] = img_query.fw_info.fw_ver[2] % 100;
            ImgVersion imgv;
            imgv.setVersion("FW", 4, fwVer);
            ri.imgVers.push_back(imgv);
        }
        for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++) {
            ImgVersion imgVer;
            const char *tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
            if (tpc == NULL) {
                //imgVer.setExpansionRomtoUnknown();
                tpc = "UNKNOWN_ROM";
            }
            int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
            imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
            ri.imgVers.push_back(imgVer);
        }
        res = 1;
    }

clean_up:
    (void) selector_tag;
    (void) image_type;
    _imgFwOps->FwCleanUp();
    delete _imgFwOps;
    _imgFwOps = NULL;

    return res;
}


int ImageAccess::getImage(const string &fname, const string &psid, string &selector_tag, int image_type, u_int8_t **filebuf)
{
    int res = -1;
    int type = getFileSignature(fname);

    if (type == IMG_SIG_TYPE_MFA) {
        mfa_desc *mfa_d;
        int rc = mfa_open_file(&mfa_d, (char*)fname.c_str());
        if (!rc) {
            res = mfa_get_image(mfa_d, (char*)psid.c_str(), image_type, (char*)selector_tag.c_str(), filebuf);
            mfa_close(mfa_d);
        } else {
            res = -1;
        }
    } else if (type == IMG_SIG_TYPE_BIN) {
        res = getImage(fname, filebuf);
    }
    //else type is unknown and res = -1

    return res;
}


int ImageAccess::getImage(const string &fname, u_int8_t **filebuf)
{
    int res = -1;
    FILE *fp;
    u_int8_t *buf = NULL;
    long int fsize;
    long int sz;

    if ((fp = fopen(fname.c_str(), "rb")) == NULL) {
        _errMsg = "Failed to open file : " + (string)fname.c_str();
        _log    += _errMsg;
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) < 0) {
        _errMsg = "Fseek failed on file : " + (string)fname.c_str();
        _log    += _errMsg;
        goto clean_up;
    }

    fsize = ftell(fp);
    if (fsize <= 0) {
        _errMsg = "Ftell failed on file : " + (string)fname.c_str();
        _log    += _errMsg;
        goto clean_up;
    }
    rewind(fp);

    buf = (u_int8_t*)malloc(fsize * sizeof(u_int8_t));
    if (buf == NULL) {
        _errMsg = "Memory allocation failure for file : " + (string)fname.c_str();
        _log    += _errMsg;
        goto clean_up;
    }

    memset(buf, 0, fsize);
    *filebuf  = buf;
    sz = fread(buf, 1, fsize, fp);
    if (sz != fsize || sz <= 0 || buf == NULL) {
        _errMsg = "ftell size is not equivalent to fread total size" + (string) fname.c_str();
        _log    += _errMsg;
        goto clean_up;
    }

    res = fsize;

clean_up:
    fclose(fp);
    if (res == -1) {
        if (buf != NULL) {
            free(buf);
        }
    }
    return res;
}


int ImageAccess::getFileSignature(const string & fname)
{
    static const int header_size = 16;
    FILE *fin;
    char tmpb[header_size];
    int res = -2;
    do {
        if (!(fin = fopen(fname.c_str(), "r"))) {
            break;
        }

        if (1 > fread(tmpb, header_size, 1, fin)) {
            break;
        }
        res = getBufferSignature((u_int8_t*)tmpb, 4);
    }while(0);

    if(fin) {
        fclose(fin);
    }
    return res;
}


int ImageAccess::getBufferSignature(u_int8_t *buf, u_int32_t size)
{
    int res = IMG_SIG_TYPE_UNKNOWN;

    if (0 == memcmp(buf, "MTFW", 4)) {
        res = IMG_SIG_TYPE_BIN;
    }
    else if (0 == memcmp(buf, "MFAR", 4)) {
        res = IMG_SIG_TYPE_MFA;
    }
    else if(0 == memcmp(buf, PldmPkg::UUID, size)) {
        res = IMG_SIG_TYPE_PLDM;
    }

    return res;
}

int ImageAccess::get_bin_content(const string & fname, vector<PsidQueryItem> &riv)
{
    fw_info_t img_query;
    int res = 0;
    char psid[33];
    PsidQueryItem item;
    ImgVersion imgv;

    if (_imgFwOps != NULL) {
        _errMsg  = "_imgFwOPs should be null";
        _log += _errMsg;
        return -1;
    }
    if (!openImg(FHT_FW_FILE, NULL, (char*)fname.c_str())) {
        return -1;
    }

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true)) {
        _errMsg  = "Failed to query " +  (string)_imgFwOps->err();
        _log += _errMsg;
        res = -1;
        goto clean_up;
    }

    strcpy(psid, img_query.fw_info.psid);
    psid[32] = 0;
    item.psid = psid;
    item.pns = "";
    item.board_rev = "";

    imgv.setVersion("FW", 3, img_query.fw_info.fw_ver,
            img_query.fw_info.branch_ver);
    item.imgVers.push_back(imgv);
    for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++) {
        ImgVersion imgVer;
        const char *tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
        if (tpc == NULL) {
            //imgVer.setExpansionRomtoUnknown();
            tpc = "UNKNOWN_ROM";
        }
        int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
        if (img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id == 0xf) {
            sz = 1;
        }
        imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
        item.imgVers.push_back(imgVer);
    }
    riv.push_back(item);

clean_up:
    _imgFwOps->FwCleanUp();
    delete _imgFwOps;
    _imgFwOps = NULL;

    return res;
}


int ImageAccess::get_mfa_content(const string & fname, vector<PsidQueryItem> &riv)
{
    mfa_desc *mfa_d;
    map_entry_hdr *me = NULL;
    char psid[33];

    if (mfa_open_file(&mfa_d, (char*)fname.c_str())) {
        return -1;
    }
    me = NULL;
    while ((me = mfa_get_next_mentry(mfa_d, me))) {
        PsidQueryItem item;
        strncpy(psid, me->board_type_id, 32);
        psid[32] = 0;
        item.psid = psid;
        char *val = mfa_get_map_entry_metadata(me, (char*)"PN");
        if (val == NULL) {
            item.pns = "";
        } else {
            item.pns = val;
            free(val);
        }
        val = mfa_get_map_entry_metadata(me, (char*)"BOARD_REV");
        if (val == NULL) {
            item.board_rev = "";
        } else {
            item.board_rev = val;
            free(val);
        }
        val = mfa_get_map_entry_metadata(me, (char*)"DESCRIPTION");
        if (val == NULL) {
            item.description = "";
        } else {
            item.description = val;
            free(val);
        }
        val = mfa_get_map_entry_metadata(me, (char*) "BRANCH");
        if (val == NULL) {
            item.branch = "";
        } else {
            item.branch = val;
            free(val);
        }

        map_image_entry *imge;
        for (int i = 0; i < me->nimages; i++) {
            imge = mfa_get_map_image(me, i);
            if (imge == NULL) {
                continue;
            }
            toc_entry *toc = mfa_get_image_toc(mfa_d, imge);
            if (toc == NULL) {
                continue;
            }
            if (toc->num_ver_fields != 0) {
                item.type = imge->image_type;
                char select_tag[33];
                strncpy(select_tag, imge->select_tag, 32);
                select_tag[32] = 0;
                item.selector_tag = select_tag;
                char *subImgType;
                if ((subImgType = mfasec_get_sub_image_type_str(toc->subimage_type)) != NULL) {
                    ImgVersion imgv;
                    if (subImgType[0] != '\0') { //Not a padding section
                        imgv.setVersion(subImgType, toc->num_ver_fields,
                                toc->version, item.branch);
                        item.imgVers.push_back(imgv);
                    }
                }
            }
        }
        riv.push_back(item);
    }
    mfa_close(mfa_d);
    return 0;
}
#define ITOC_ASCII 0x49544f43
#define TOC_HEADER_SIZE 0x20
#define TOC_ENTRY_SIZE  0x20
#define FS3_DEFAULT_SECTOR_SIZE 0x1000

bool ImageAccess::extract_pldm_image_info(const u_int8_t * buff, u_int32_t size, PsidQueryItem &query_item) {
    FImage fimage;
    if (!fimage.open((u_int32_t*)buff, size)) {
        return false;
    }
    static const u_int32_t sector_size = FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t offset = 0;
    offset = (offset % sector_size == 0) ? offset : (offset + sector_size - offset % 0x1000);
    u_int8_t buffer[TOC_HEADER_SIZE], entry_buffer[TOC_ENTRY_SIZE];
    struct connectx4_itoc_header itoc_header;
    while (offset < fimage.get_size()) {
        //read ITOC header
        fimage.read(offset, buffer, TOC_HEADER_SIZE);
        connectx4_itoc_header_unpack(&itoc_header, buffer);
        if (itoc_header.signature0 != ITOC_ASCII) {
            offset += sector_size;
            continue;
        }
        int section_index = 0;
        struct connectx4_itoc_entry toc_entry;
        do {
            //read ITOC entry
            u_int32_t entry_addr = offset + TOC_HEADER_SIZE + section_index *  TOC_ENTRY_SIZE;
            fimage.read(entry_addr, entry_buffer, TOC_ENTRY_SIZE);

            connectx4_itoc_entry_unpack(&toc_entry, entry_buffer);
            if (toc_entry.type == FS3_IMAGE_INFO) {
                u_int32_t flash_addr = toc_entry.flash_addr << 2;
                u_int32_t entry_size_in_bytes = toc_entry.size * 4;
                u_int8_t *buff = new u_int8_t[entry_size_in_bytes];
                fimage.read(flash_addr, buff, entry_size_in_bytes);
                //read image info
                struct connectx4_image_info image_info;
                connectx4_image_info_unpack(&image_info, buff);
                query_item.name = image_info.name;
                query_item.pns = query_item.name;
                query_item.description = image_info.description;
                static const int FW_VER_SIZE = 3;
                u_int16_t fw_ver[FW_VER_SIZE];
                char fw_branch[BRANCH_LEN + 1] = { 0 };
                fw_ver[0] = image_info.FW_VERSION.MAJOR;
                fw_ver[1] = image_info.FW_VERSION.MINOR;
                fw_ver[2] = image_info.FW_VERSION.SUBMINOR;
                strncpy(fw_branch, image_info.vsd, BRANCH_LEN);
                fw_branch[BRANCH_LEN] = (char) 0;
                ImgVersion imgv;
                imgv.setVersion("FW", FW_VER_SIZE, fw_ver, fw_branch);
                query_item.imgVers.push_back(imgv);

                delete [] buff;
                break;
            }

            section_index++;
        } while (toc_entry.type != FS3_END);
        break;
    }
    fimage.close();
    return 0;
}

int ImageAccess::get_pldm_content(const string & fname,
        vector<PsidQueryItem> &riv) {
    PldmBuffer pldm_buff;
    pldm_buff.loadFile(fname);
    PldmPkg pldm;
    pldm.unpack(pldm_buff);

    u_int8_t dev_count = pldm.getDeviceIDRecordCount();
    for(u_int8_t i=0; i<dev_count; i++) {
        PldmDevIdRecord * rec = pldm.getDeviceIDRecord(i);
        PsidQueryItem item;
        item.psid = rec->getDevicePsid();
        item.description = rec->getDescription();
        int image_index = rec->getComponentImageIndex();
        PldmComponenetImage * image_obj = pldm.getComponentImage(image_index);
        extract_pldm_image_info(image_obj->getComponentData(),
                image_obj->getComponentSize(), item);
        riv.push_back(item);
    }

    return 0;
}


int ImageAccess::get_file_content(const string & fname, vector<PsidQueryItem> &riv)
{
    int type = getFileSignature(fname);
    int res = -1;
    switch(type) {
    case IMG_SIG_TYPE_BIN:
        res = get_bin_content(fname, riv);
        break;
    case IMG_SIG_TYPE_MFA:
        res = get_mfa_content(fname, riv);
        break;
    case IMG_SIG_TYPE_PLDM:
        res = get_pldm_content(fname, riv);
        break;
    }
    return res;
}

string ImageAccess::getLastErrMsg()
{
    return _errMsg;
}

string ImageAccess::getlastWarning()
{
    return _warning;
}

string ImageAccess::getLog()
{
    return _log;
}

