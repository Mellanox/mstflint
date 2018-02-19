
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

bool ImageAccess::hasMFAs(string directory) {
    DIR* d;
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
    DIR* d;
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

bool ImageAccess::openImg(fw_hndl_type_t hndlType, char *psid, char * fileHndl) {

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
    mfa_desc* mfa_d = NULL;
    fw_info_t img_query;
    string    iniName = "";
    vector<u_int8_t> sect; // to get fw configuration.
    vector<u_int8_t> dest;

    if(!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str())) {
        return 0;
    }

    ri.psid = psid;
    ri.found = 0;

    memset(&img_query, 0, sizeof(img_query));
    if(!_imgFwOps->FwQuery(&img_query, true)) {
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
                 char * ptr = strstr ((char *)&dest[0],"Name =");
                 int counter = 7;
                 while(ptr and *ptr != '\n' and *ptr != '\r') {
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
            char* pn =  mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"PN");
            if (pn != NULL) {
                ri.pns = pn;
                free(pn);
            }
            char* desc =  mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"DESCRIPTION");//TODO: Make more efficient
            if (desc != NULL) {
                ri.description = desc;
                free(desc);
            }
            mfa_close(mfa_d);
        }
        if (!_compareFFV) {
            ImgVersion imgv;
            imgv.setVersion("FW", 3, img_query.fw_info.fw_ver);
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
            const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
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
        mfa_desc* mfa_d;
        int rc = mfa_open_file(&mfa_d, (char*)fname.c_str());
        if (!rc) {
            res = mfa_get_image(mfa_d, (char*)psid.c_str(), image_type, (char*)selector_tag.c_str(), filebuf);
            mfa_close(mfa_d);
        } else {
            res = -1;
        }
    } else if (type == IMG_SIG_TYPE_BIN){
        res = getImage(fname, filebuf);
    }
    //else type is unknown and res = -1

    return res;
}


int ImageAccess::getImage(const string &fname, u_int8_t **filebuf)
{
    int res = -1;
    FILE* fp;
    u_int8_t* buf = NULL;
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
    if(fsize <= 0) {
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


int ImageAccess::getFileSignature(string fname)
{
    FILE* fin;
    char tmpb[16];
    int res = -2;

    if (!(fin = fopen(fname.c_str(), "r"))) {
        return res;
    }
    if (!fgets(tmpb, sizeof(tmpb), fin)) {
        goto clean_up;
    }

    tmpb[15] = 0;
    if (strlen(tmpb) < 4) {
        goto clean_up;
    }

    res = getBufferSignature((u_int8_t*)tmpb, 4);

clean_up:
    fclose(fin);
    return res;
}


int ImageAccess::getBufferSignature(u_int8_t* buf, u_int32_t size)
{
    int res = 0;

    if (size < 4) {
        return 0;
    }
    if (!strncmp((char*)buf, "MTFW", 4)) {
        res = IMG_SIG_TYPE_BIN;
    }
    if (!strncmp((char*)buf, "MFAR", 4)) {
        res = IMG_SIG_TYPE_MFA;
    }

    return res;
}

int ImageAccess::get_bin_content(string fname, vector<PsidQueryItem> &riv)
{
    fw_info_t img_query;
    int res = 0;
    char psid[33];
    PsidQueryItem item;
    ImgVersion imgv;

    if(_imgFwOps != NULL) {
        _errMsg  = "_imgFwOPs should be null";
        _log += _errMsg;
        return -1;
    }
    if(!openImg(FHT_FW_FILE, NULL, (char*)fname.c_str())) {
        return -1;
    }

    memset(&img_query, 0, sizeof(img_query));
    if(!_imgFwOps->FwQuery(&img_query, true)) {
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

    imgv.setVersion("FW", 3, img_query.fw_info.fw_ver);
    item.imgVers.push_back(imgv);
    for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++) {
        ImgVersion imgVer;
        const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
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


int ImageAccess::get_mfa_content(string fname, vector<PsidQueryItem> &riv)
{
    mfa_desc* mfa_d;
    map_entry_hdr* me = NULL;
    char psid[33];

    if (mfa_open_file(&mfa_d, (char*)fname.c_str())) {
        return -1;
    }
    me = NULL;
    while((me = mfa_get_next_mentry(mfa_d, me))) {
        PsidQueryItem item;
        strncpy(psid, me->board_type_id, 32);
        psid[32] = 0;
        item.psid = psid;
        char* val = mfa_get_map_entry_metadata(me, (char*)"PN");
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

        map_image_entry* imge;
        for (int i = 0; i < me->nimages; i++) {
            imge = mfa_get_map_image(me, i);
            if (imge == NULL) {
                continue;
            }
            toc_entry* toc = mfa_get_image_toc(mfa_d, imge);
            if (toc == NULL) {
                continue;
            }
            if (toc->num_ver_fields != 0) {
                item.type = imge->image_type;
                char select_tag[33];
                strncpy(select_tag, imge->select_tag, 32);
                select_tag[32] = 0;
                item.selector_tag = select_tag;
                char* subImgType;
                if ((subImgType = mfasec_get_sub_image_type_str(toc->subimage_type)) != NULL) {
                    ImgVersion imgv;
                    if (subImgType[0] != '\0') { //Not a padding section
                        imgv.setVersion(subImgType, toc->num_ver_fields, toc->version);
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


int ImageAccess::get_file_content(string fname, vector<PsidQueryItem> &riv)
{
    int type = getFileSignature(fname);

    if (type == IMG_SIG_TYPE_BIN) {
        return get_bin_content(fname, riv);
    } else if (type == IMG_SIG_TYPE_MFA) {
        return get_mfa_content(fname, riv);
    } else  {
        return -1;
    }
}

string ImageAccess::getLastErrMsg()
{
    return _errMsg;
}

string ImageAccess::getlastWarning() {
    return _warning;
}

string ImageAccess::getLog()
{
    return _log;
}

