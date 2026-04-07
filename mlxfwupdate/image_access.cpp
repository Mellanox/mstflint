/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <algorithm>
#include <set>
#include <mfa.h>
#include <mlxfwops.h>
#include <pldm_pkg.h>
#include <pldm_dev_id_record.h>
#include <pldm_component_image.h>
#ifdef MST_UL
#include <tools_layouts/image_info_layouts.h>
#else
#include <tools_layouts/connectx4_layouts.h>
#endif
#include "pldmlib/pldm_utils.h"
#include <mlxarchive/mlxarchive_mfa2.h>

#define ITOC_ASCII 0x49544f43
#define TOC_HEADER_SIZE 0x20
#define TOC_ENTRY_SIZE 0x20

using namespace std;

namespace
{
int compareMFA2Version(const mfa2::VersionExtension& lhs, const mfa2::VersionExtension& rhs)
{
    if (lhs.getMajor() != rhs.getMajor())
    {
        return lhs.getMajor() > rhs.getMajor() ? 1 : -1;
    }
    if (lhs.getMinor() != rhs.getMinor())
    {
        return lhs.getMinor() > rhs.getMinor() ? 1 : -1;
    }
    if (lhs.getSubMinor() != rhs.getSubMinor())
    {
        return lhs.getSubMinor() > rhs.getSubMinor() ? 1 : -1;
    }
    return 0;
}

bool selectMFA2Component(const mfa2::map_string_to_component& matchingComponentsMap,
                         const string& selectorTag,
                         u_int32_t& choice,
                         string& resolvedTag)
{
    if (matchingComponentsMap.empty())
    {
        return false;
    }

    bool found = false;
    const mfa2::VersionExtension* bestVersion = nullptr;
    u_int32_t index = 0;
    u_int32_t bestIndex = 0;
    for (mfa2::map_string_to_component::const_iterator it = matchingComponentsMap.begin();
         it != matchingComponentsMap.end(); ++it, ++index)
    {
        if (!selectorTag.empty())
        {
            if (it->first == selectorTag)
            {
                choice = index;
                resolvedTag = it->first;
                return true;
            }
            continue;
        }

        const mfa2::VersionExtension& currentVersion = it->second.getComponentDescriptor().getVersionExtension();
        if (!found || compareMFA2Version(currentVersion, *bestVersion) > 0)
        {
            found = true;
            bestVersion = &currentVersion;
            bestIndex = index;
            resolvedTag = it->first;
        }
    }

    if (!selectorTag.empty())
    {
        return false;
    }

    choice = bestIndex;
    return found;
}

void patchMFA2ImageSignature(vector<u_int8_t>& buf, u_int8_t majorVer)
{
    static const u_int8_t fs4_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0xAB, 0xCD, 0xEF, 0x00,
                                                   0xFA, 0xDE, 0x12, 0x34, 0x56, 0x78, 0xDE, 0xAD};
    static const u_int8_t fs3_image_signature[] = {0x4D, 0x54, 0x46, 0x57, 0x8C, 0xDF, 0xD0, 0x00,
                                                   0xDE, 0xAD, 0x92, 0x70, 0x41, 0x54, 0xBE, 0xEF};
    if (buf.size() < 16)
    {
        return;
    }
    const u_int8_t* sig = (majorVer >= 16) ? fs4_image_signature : fs3_image_signature;
    memcpy(buf.data(), sig, 16);
}
} // namespace

ImageAccess::ImageAccess(int compareFFV)
{
    _imgFwOps = NULL;
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
    DIR          * d;
    struct dirent* dir;
    int            rc;

    d = opendir(directory.c_str());
    if (d == NULL) {
        return false;
    }
    while ((dir = readdir(d)) != NULL) {
        string fl = dir->d_name;
        if ((fl == ".") || (fl == "..")) {
            continue;
        }
        string fpath = directory;
        fpath += "/";
        fpath += fl;
        rc = getFileSignature(fpath);
        if (rc == IMG_SIG_TYPE_BIN || rc == IMG_SIG_TYPE_MFA || rc == IMG_SIG_TYPE_MFA2) {
            closedir(d);
            return true;
        }
    }
    closedir(d);
    return false;
}
int ImageAccess::queryDirPsid(string&                   path,
                              string&                   psid,
                              string&                   selector_tag,
                              int                       image_type,
                              vector < PsidQueryItem >& riv)
{
    int            res = 0;
    DIR          * d;
    struct dirent* dir;
    int            found = 0;
    int            rc;

    d = opendir(path.c_str());
    if (d == NULL) {
        return -1;
    }

    while ((dir = readdir(d)) != NULL) {
        PsidQueryItem ro;
        string        fl = dir->d_name;
        if ((fl == ".") || (fl == "..")) {
            continue;
        }
        string fpath = path;
        fpath += "/";
        fpath += fl;

        struct stat buffer;
        stat(fpath.c_str(), &buffer);
        if (!S_ISREG(buffer.st_mode))
        {
            continue;
        }

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

bool ImageAccess::openImg(fw_hndl_type_t hndlType,
                          char* psid,
                          char* fileHndl,
                          u_int16_t swDevId,
                          u_int32_t* data,
                          u_int32_t dataSize)
{
    memset(_errBuff, 0, sizeof(_errBuff));
    _imgFwParams.errBuff = _errBuff;
    _imgFwParams.errBuffSize = MLNX_ERR_BUFF_SIZE;
    _imgFwParams.hndlType = hndlType;
    _imgFwParams.psid = psid;
    _imgFwParams.fileHndl = fileHndl;
    _imgFwParams.shortErrors = true;
    if (dataSize)
    {
        _imgFwParams.buffHndl = data;
        _imgFwParams.buffSize = dataSize;
        _imgFwParams.swDevId = swDevId;
    }
    _imgFwOps = FwOperations::FwOperationsCreate(_imgFwParams);
    if (_imgFwOps == NULL) {
        _errMsg = "-E- " + (string)_errBuff + "\n";
        if (_errMsg.find("upgrade tool") != std::string::npos) {
            _warning = _errMsg;
        } else if (_errMsg.find("with higher Version") != std::string::npos) {
            _warning = _errMsg;
        }
        _log += _errMsg;
        return false;
    }
    return true;
}

int ImageAccess::queryPsid(const string&  fname,
                           const string&  psid,
                           string&        selector_tag,
                           int            image_type,
                           PsidQueryItem& ri)
{
    int       res = 0;
    mfa_desc* mfa_d = NULL;
    fw_info_t img_query;
    string    iniName = "";

    vector < u_int8_t > sect; /* to get fw configuration. */
    vector < u_int8_t > dest;
    bool isStripedImage = false;
    int signature = getFileSignature(fname);

    if (signature == IMG_SIG_TYPE_MFA2)
    {
        return queryPsidMfa2(fname, psid, selector_tag, image_type, ri);
    }

    if (signature == IMG_SIG_TYPE_PLDM)
    {
        res = getPldmImage(fname, psid);
        if (res != 1)
        {
            goto clean_up;
        }
        isStripedImage = true;
    }
    else if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str())) {
        return 0;
    }

    ri.psid = psid;
    ri.found = 0;

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true, isStripedImage)) {
        _errMsg = "Failed to query " + (string)_imgFwOps->err();
        _log += _errMsg;
        goto clean_up;
    }

    if (!psid.compare(img_query.fw_info.psid)) {
        u_int32_t* supporteHwId;
        u_int32_t  supporteHwIdNum;
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
                char* ptr = strstr((char*)&dest[0], "Name =");
                int   counter = 7;
                while (ptr && *ptr != '\n' && *ptr != '\r') {
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
            char* pn = mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"PN");
            if (pn != NULL) {
                ri.pns = pn;
                free(pn);
            }
            char* desc =
                mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"DESCRIPTION"); /* TODO: Make more efficient */
            if (desc != NULL) {
                ri.description = desc;
                free(desc);
            }
            mfa_close(mfa_d);
        }
        if (!_compareFFV) {
            ImgVersion imgv;
            imgv.setVersion("FW", 3, img_query.fw_info.fw_ver, img_query.fw_info.branch_ver);
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
            ImgVersion  imgVer;
            const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
            if (tpc == NULL) {
                /* imgVer.setExpansionRomtoUnknown(); */
                tpc = "UNKNOWN_ROM";
            }
            int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
            imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
            ri.imgVers.push_back(imgVer);
        }
        res = 1;
    }

clean_up:
    (void)selector_tag;
    (void)image_type;
    if(_imgFwOps != nullptr)
    {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }

    return res;
}

int ImageAccess::getPldmImage(const string& fname, const string& psid)
{
    if (!loadPldmPkg(fname))
    {
        _errMsg = "-E- Failed to load PLDM package from file: " + fname;
        return -1;
    }
    u_int16_t swDevId = 0;
    if (!_pldmPkg.isPsidInPldm(psid))
    {
        return 0;
    }
    else if (!getPldmDescriptorByPsid(psid, DEV_ID_TYPE, swDevId))
    {
        _errMsg = "-E- No swId found for psid: " + psid + " in file: " + fname;
        return -1;
    }
    u_int8_t* buff;
    u_int32_t buffSize = 0;
    if (!getPldmComponentByPsid(psid, ComponentIdentifier::Identifier_NIC_FW_Comp, &buff, buffSize))
    {
        _errMsg = "-E- Nic FW component not found for psid: " + psid + " in file: " + fname;
        return -1;
    }
    if (!openImg(FHT_FW_BUFF, (char*)psid.c_str(), nullptr, swDevId, (u_int32_t*)buff, buffSize))
    {
        _errMsg = "Unable to open the PLDM buffer component.";
        return -1;
    }
    if (_imgFwOps->FwType() != FIT_FS4 && _imgFwOps->FwType() != FIT_FS5)
    {
        _errMsg = "Update FW using PLDM is applicable only for FS4 and FS5 images.";
        if (buff)
        {
            delete[] buff;
        }
        return -1;
    }
    delete[] buff;
    return 1;
}

int ImageAccess::getImage(const string& fname,
                          const string& psid,
                          string&       selector_tag,
                          int           image_type,
                          u_int8_t   ** filebuf)
{
    int res = -1;
    int type = getFileSignature(fname);

    if (type == IMG_SIG_TYPE_MFA) {
        mfa_desc* mfa_d;
        int       rc = mfa_open_file(&mfa_d, (char*)fname.c_str());
        if (!rc) {
            res = mfa_get_image(mfa_d, (char*)psid.c_str(), image_type, (char*)selector_tag.c_str(), filebuf);
            mfa_close(mfa_d);
        } else {
            res = -1;
        }
    } else if (type == IMG_SIG_TYPE_MFA2) {
        mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
        if (mfa2Pkg == NULL) {
            _errMsg = "Failed to open MFA2 file: " + fname;
            _log += _errMsg;
            res = -1;
        } else {
            u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
            mfa2::map_string_to_component matchingComponentsMap =
              mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
            u_int32_t choice = 0;
            string resolvedTag;
            if (!selectMFA2Component(matchingComponentsMap, selector_tag, choice, resolvedTag)) {
                _errMsg = "Failed to select matching component from MFA2 file: " + fname;
                _log += _errMsg;
                delete mfa2Pkg;
                res = -1;
            } else {
                vector<u_int8_t> componentBuffer;
                if (!mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer)) {
                    _errMsg = "Failed to extract component from MFA2 file: " + fname;
                    _log += _errMsg;
                    delete mfa2Pkg;
                    res = -1;
                } else {
                    mfa2::map_string_to_component::iterator itComp = matchingComponentsMap.begin();
                    std::advance(itComp, choice);
                    u_int8_t majorVer = itComp->second.getComponentDescriptor().getVersionExtension().getMajor();
                    patchMFA2ImageSignature(componentBuffer, majorVer);
                    u_int8_t* buf = (u_int8_t*)malloc(componentBuffer.size());
                    if (buf == NULL) {
                        _errMsg = "Memory allocation failure for image extracted from: " + fname;
                        _log += _errMsg;
                        delete mfa2Pkg;
                        res = -1;
                    } else {
                        memcpy(buf, componentBuffer.data(), componentBuffer.size());
                        *filebuf = buf;
                        selector_tag = resolvedTag;
                        res = componentBuffer.size();
                        delete mfa2Pkg;
                    }
                }
            }
        }
    } else if (type == IMG_SIG_TYPE_BIN) {
        res = getImage(fname, filebuf);
    }
    /* else type is unknown and res = -1 */

    return res;
}

int ImageAccess::getImage(const string& fname, u_int8_t** filebuf)
{
    int       res = -1;
    FILE    * fp;
    u_int8_t* buf = NULL;
    long int  fsize;
    long int  sz;

    if ((fp = fopen(fname.c_str(), "rb")) == NULL) {
        _errMsg = "Failed to open file : " + (string)fname.c_str();
        _log += _errMsg;
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) < 0) {
        _errMsg = "Fseek failed on file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }

    fsize = ftell(fp);
    if (fsize <= 0) {
        _errMsg = "Ftell failed on file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }
    rewind(fp);

    buf = (u_int8_t*)malloc(fsize * sizeof(u_int8_t));
    if (buf == NULL) {
        _errMsg = "Memory allocation failure for file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }

    memset(buf, 0, fsize);
    *filebuf = buf;
    sz = fread(buf, 1, fsize, fp);
    if ((sz != fsize) || (sz <= 0) || (buf == NULL)) {
        _errMsg = "ftell size is not equivalent to fread total size" + (string)fname.c_str();
        _log += _errMsg;
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

int ImageAccess::getFileSignature(const string& fname)
{
    static const int header_size = 16;
    FILE           * fin = NULL;
    char             tmpb[header_size];
    int              res = -2;

    do{
        if (!(fin = fopen(fname.c_str(), "rb"))) {
            break;
        }

        if (1 > fread(tmpb, header_size, 1, fin)) {
            break;
        }
        res = getBufferSignature((u_int8_t*)tmpb, header_size);
    } while (0);

    if (fin) {
        fclose(fin);
    }
    return res;
}

int ImageAccess::getBufferSignature(u_int8_t* buf, u_int32_t size)
{
    int res = IMG_SIG_TYPE_UNKNOWN;

    if (size >= 4 && 0 == memcmp(buf, "MTFW", 4)) {
        res = IMG_SIG_TYPE_BIN;
    } else if (size >= 4 && 0 == memcmp(buf, "MFAR", 4)) {
        res = IMG_SIG_TYPE_MFA;
    } else if (size >= strlen(MFA2_FINGER_PRINT) && 0 == memcmp(buf, MFA2_FINGER_PRINT, strlen(MFA2_FINGER_PRINT))) {
        res = IMG_SIG_TYPE_MFA2;
    } else if (size >= 16 && 0 == memcmp(buf, PldmPkg::UUID, 16)) {
        res = IMG_SIG_TYPE_PLDM;
    }

    return res;
}

int ImageAccess::get_bin_content(const string& fname, vector < PsidQueryItem >& riv)
{
    fw_info_t     img_query;
    int           res = 0;
    char          psid[33];
    PsidQueryItem item;
    ImgVersion    imgv;

    if (_imgFwOps != NULL) {
        _errMsg = "_imgFwOPs should be null";
        _log += _errMsg;
        return -1;
    }
    if (!openImg(FHT_FW_FILE, NULL, (char*)fname.c_str())) {
        return -1;
    }
    
    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true)) {
        _errMsg = "Failed to query " + (string)_imgFwOps->err();
        _log += _errMsg;
        res = -1;
        goto clean_up;
    }

    strcpy(psid, img_query.fw_info.psid);
    psid[32] = 0;
    item.psid = psid;
    item.pns = "";
    item.board_rev = "";

    imgv.setVersion("FW", 3, img_query.fw_info.fw_ver, img_query.fw_info.branch_ver);
    item.imgVers.push_back(imgv);
    for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++) {
        ImgVersion  imgVer;
        const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
        if (tpc == NULL) {
            /* imgVer.setExpansionRomtoUnknown(); */
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

int ImageAccess::get_mfa_content(const string& fname, vector < PsidQueryItem >& riv)
{
    mfa_desc     * mfa_d;
    map_entry_hdr* me = NULL;
    char           psid[33];

    if (mfa_open_file(&mfa_d, (char*)fname.c_str())) {
        return -1;
    }
    me = NULL;
    while ((me = mfa_get_next_mentry(mfa_d, me))) {
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
        val = mfa_get_map_entry_metadata(me, (char*)"BRANCH");
        if (val == NULL) {
            item.branch = "";
        } else {
            item.branch = val;
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
                    if (subImgType[0] != '\0') { /* Not a padding section */
                        imgv.setVersion(subImgType, toc->num_ver_fields, toc->version, item.branch);
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

#define FS3_DEFAULT_SECTOR_SIZE 0x1000

void ImageAccess::parse_image_info_data(u_int8_t* image_info_data, PsidQueryItem& query_item)
{
    struct connectx4_image_info image_info;
    connectx4_image_info_unpack(&image_info, image_info_data);
    query_item.name = image_info.name;
    query_item.pns = query_item.name;
    query_item.description = image_info.description;
    static const int FW_VER_SIZE = 3;
    u_int16_t fw_ver[FW_VER_SIZE];
    char fw_branch[BRANCH_LEN + 1] = {0};
    fw_ver[0] = image_info.FW_VERSION.MAJOR;
    fw_ver[1] = image_info.FW_VERSION.MINOR;
    fw_ver[2] = image_info.FW_VERSION.SUBMINOR;
    (strncpy(fw_branch, image_info.vsd, BRANCH_LEN));
    fw_branch[BRANCH_LEN] = (char)0;
    ImgVersion imgv;
    imgv.setVersion("FW", FW_VER_SIZE, fw_ver, fw_branch);
    query_item.imgVers.push_back(imgv);
}

bool ImageAccess::extract_pldm_image_info(const u_int8_t* buff, u_int32_t size, PsidQueryItem& query_item)
{
    FImage fimage;

    if (!fimage.open((u_int32_t*)buff, size)) {
        return false;
    }

    static const u_int32_t sector_size = FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t              offset = 0;

    offset = (offset % sector_size == 0) ? offset : (offset + sector_size - offset % 0x1000);
    u_int8_t                     buffer[TOC_HEADER_SIZE] = {0}, entry_buffer[TOC_ENTRY_SIZE] = {0};
    struct connectx4_itoc_header itoc_header;
    bool image_info_found = false;
    while (offset < fimage.get_size()) {
        /* read ITOC header */
        fimage.read(offset, buffer, TOC_HEADER_SIZE);
        connectx4_itoc_header_unpack(&itoc_header, buffer);
        if (itoc_header.signature0 != ITOC_ASCII) {
            offset += sector_size;
            continue;
        }
        int                         section_index = 0;
        struct connectx4_itoc_entry toc_entry;
        do{
            /* read ITOC entry */
            u_int32_t entry_addr = offset + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
            fimage.read(entry_addr, entry_buffer, TOC_ENTRY_SIZE);

            connectx4_itoc_entry_unpack(&toc_entry, entry_buffer);
            if (toc_entry.type == FS3_IMAGE_INFO) {
                image_info_found = true;
                u_int32_t flash_addr = toc_entry.flash_addr << 2;
                u_int32_t entry_size_in_bytes = toc_entry.size * 4;
                u_int8_t image_info_data[entry_size_in_bytes];
                memset(image_info_data, 0, entry_size_in_bytes);
                fimage.read(flash_addr, image_info_data, entry_size_in_bytes);
                parse_image_info_data(image_info_data, query_item);
                break;
            }

            section_index++;
        } while (toc_entry.type != FS3_END);
        break;
    }
    if (!image_info_found)
    {
        // Parse HW pointers
        u_int32_t hw_pointers_data[IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE / 4] = {0};
        fimage.read(FS4_HW_PTR_START, hw_pointers_data, IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE);
        image_layout_hw_pointers_carmel hw_pointers;
        image_layout_hw_pointers_carmel_unpack(&hw_pointers, (u_int8_t*)hw_pointers_data);

        // Check if we couldn't find image_info because ITOC is encrypted
        fimage.read(hw_pointers.toc_ptr.ptr, buffer, TOC_HEADER_SIZE);
        connectx4_itoc_header_unpack(&itoc_header, buffer);
        if (itoc_header.signature0 != ITOC_ASCII)
        {
            // Encrypted image, get image_info addr from hw pointer
            u_int8_t buff[IMAGE_LAYOUT_IMAGE_INFO_SIZE];
            memset(buff, 0, IMAGE_LAYOUT_IMAGE_INFO_SIZE);
            fimage.read(hw_pointers.image_info_section_pointer.ptr, buff, IMAGE_LAYOUT_IMAGE_INFO_SIZE);
            parse_image_info_data(buff, query_item);
        }
    }
    fimage.close();
    return 0;
}

int ImageAccess::get_file_content(const string& fname, vector < PsidQueryItem >& riv)
{
    int type = getFileSignature(fname);
    int res = -1;

    switch (type) {
    case IMG_SIG_TYPE_BIN:
        res = get_bin_content(fname, riv);
        break;

    case IMG_SIG_TYPE_MFA:
        res = get_mfa_content(fname, riv);
        break;

    case IMG_SIG_TYPE_MFA2:
        res = get_mfa2_content(fname, riv);
        break;

    case IMG_SIG_TYPE_PLDM:
        if (!loadPldmPkg(fname))
        {
            return res;
        }
        res = getPldmContent(riv);
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

image_flow_type_t ImageAccess::DetermineFlow(const string& fname, const string& psid)
{
    mfa_desc* mfa_d = NULL;
    int signature = getFileSignature(fname);
    if (signature == IMG_SIG_TYPE_PLDM)
    {
        return PLDM_FLOW;
    }
    else if (signature == IMG_SIG_TYPE_MFA)
    {
        if (mfa_open_file(&mfa_d, (char*)fname.c_str()))
        {
            return UNKNOWN_FLOW;
        }
        mfa_close(mfa_d);
        return BINARY_IN_MFA_FLOW;
    }
    else if (signature == IMG_SIG_TYPE_MFA2)
    {
        mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
        if (mfa2Pkg == NULL)
        {
            _errMsg = "DetermineFlow: Failed to load MFA2 package from file: " + fname;
            _log += _errMsg;
            return UNKNOWN_FLOW;
        }
        u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
        mfa2::map_string_to_component matchingComponentsMap =
          mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
        delete mfa2Pkg;
        if (matchingComponentsMap.empty())
        {
            _errMsg = "DetermineFlow: No matching MFA2 components found for PSID: " + psid + " in file: " + fname;
            _log += _errMsg;
            return UNKNOWN_FLOW;
        }
        return MFA2_FLOW;
    }
    else if (signature == IMG_SIG_TYPE_BIN)
    {
        return BINARY_FLOW;
    }
    return UNKNOWN_FLOW;
}

int ImageAccess::fillQueryItemFromBuffer(const string& fname,
                                         const string& psid,
                                         const u_int8_t* imageData,
                                         u_int32_t imageSize,
                                         PsidQueryItem& ri)
{
    int res = 0;
    fw_info_t img_query;
    string iniName = "";
    vector<u_int8_t> sect;
    vector<u_int8_t> dest;
    u_int8_t* alignedBuffer = NULL;
    u_int32_t* supporteHwId = NULL;
    u_int32_t supporteHwIdNum = 0;

    ri.psid = psid;
    ri.found = 0;
    ri.url = fname;

    alignedBuffer = (u_int8_t*)malloc(imageSize);
    if (alignedBuffer == NULL)
    {
        _errMsg = "Memory allocation failure for image extracted from: " + fname;
        _log += _errMsg;
        return -1;
    }
    memcpy(alignedBuffer, imageData, imageSize);

    if (!openImg(FHT_FW_BUFF, (char*)psid.c_str(), NULL, 0, (u_int32_t*)alignedBuffer, imageSize))
    {
        free(alignedBuffer);
        return 0;
    }

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true))
    {
        _errMsg = "Failed to query " + (string)_imgFwOps->err();
        _log += _errMsg;
        res = -1;
        goto clean_up;
    }

    _imgFwOps->getSupporteHwId(&supporteHwId, supporteHwIdNum);
    ri.found = 1;
    ri.pns = strlen(img_query.fs3_info.name) ? img_query.fs3_info.name : "";
    ri.description = strlen(img_query.fs3_info.description) ? img_query.fs3_info.description : "";
    ri.devId = (supporteHwIdNum > 0) ? supporteHwId[0] : 0;
    ri.revId = (ri.devId >> 16) & 0xffff;
    ri.devId = ri.devId & 0xffff;
    ri.isFailSafe = img_query.fw_info.is_failsafe;
    if (_imgFwOps->FwGetSection(H_FW_CONF, sect))
    {
        if (!sect.empty())
        {
            if (unzipDataFile(sect, dest, "Fw Configuration"))
            {
                char* ptr = strstr((char*)&dest[0], "Name =");
                int counter = 7;
                while (ptr && *ptr != '\n' && *ptr != '\r')
                {
                    if (counter-- > 0)
                    {
                        ptr++;
                        continue;
                    }
                    iniName += *ptr;
                    ptr++;
                }
            }
        }
    }
    ri.iniName = iniName;

    if (!_compareFFV)
    {
        ImgVersion imgv;
        imgv.setVersion("FW", 3, img_query.fw_info.fw_ver, img_query.fw_info.branch_ver);
        ri.imgVers.push_back(imgv);
    }
    else
    {
        u_int16_t fwVer[4];
        fwVer[0] = img_query.fw_info.fw_ver[0];
        fwVer[1] = img_query.fw_info.fw_ver[1];
        fwVer[2] = img_query.fw_info.fw_ver[2] / 100;
        fwVer[3] = img_query.fw_info.fw_ver[2] % 100;
        ImgVersion imgv;
        imgv.setVersion("FW", 4, fwVer);
        ri.imgVers.push_back(imgv);
    }
    for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++)
    {
        ImgVersion imgVer;
        const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
        if (tpc == NULL)
        {
            tpc = "UNKNOWN_ROM";
        }
        int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
        imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
        ri.imgVers.push_back(imgVer);
    }
    res = ri.found;

clean_up:
    if (_imgFwOps != nullptr)
    {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }
    return res;
}

int ImageAccess::queryPsidMfa2(const string& fname,
                               const string& psid,
                               string& selector_tag,
                               int image_type,
                               PsidQueryItem& ri)
{
    (void)image_type;
    mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
    if (mfa2Pkg == NULL)
    {
        _errMsg = "Failed to open MFA2 file: " + fname;
        _log += _errMsg;
        return -1;
    }

    u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
    mfa2::map_string_to_component matchingComponentsMap =
      mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
    if (matchingComponentsMap.empty())
    {
        _errMsg = "queryPsidMfa2: No matching component found in MFA2 file for PSID: " + psid + " in file: " + fname;
        _log += _errMsg;
        delete mfa2Pkg;
        return 0;
    }

    u_int32_t choice = 0;
    string resolvedTag;
    if (!selectMFA2Component(matchingComponentsMap, selector_tag, choice, resolvedTag))
    {
        _errMsg = "Failed to select matching component from MFA2 file: " + fname;
        _log += _errMsg;
        delete mfa2Pkg;
        return -1;
    }

    vector<u_int8_t> componentBuffer;
    if (!mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer))
    {
        _errMsg = "Failed to extract component from MFA2 file: " + fname;
        _log += _errMsg;
        delete mfa2Pkg;
        return -1;
    }

    mfa2::map_string_to_component::iterator itComp = matchingComponentsMap.begin();
    std::advance(itComp, choice);
    u_int8_t majorVer = itComp->second.getComponentDescriptor().getVersionExtension().getMajor();
    patchMFA2ImageSignature(componentBuffer, majorVer);

    int res = fillQueryItemFromBuffer(fname, psid, componentBuffer.data(), componentBuffer.size(), ri);
    if (res > 0)
    {
        ri.selector_tag = resolvedTag;
    }
    selector_tag = resolvedTag;
    delete mfa2Pkg;
    return res;
}

int ImageAccess::get_mfa2_content(const string& fname, vector<PsidQueryItem>& riv)
{
    int res = 0;
    mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
    if (mfa2Pkg == NULL)
    {
        _errMsg = "Failed to open MFA2 file: " + fname;
        _log += _errMsg;
        return -1;
    }

    std::set<string> processedPsids;
    mfa2::PackageDescriptor packageDescriptor = mfa2Pkg->getPackageDescriptor();
    u_int16_t devCount = packageDescriptor.getDeviceDescriptorsCount();
    for (u_int16_t index = 0; index < devCount; index++)
    {
        mfa2::DeviceDescriptor devDescriptor = mfa2Pkg->getDeviceDescriptor(index);
        string psid = devDescriptor.getPSIDExtension().getString();
        if (processedPsids.find(psid) != processedPsids.end())
        {
            continue;
        }
        processedPsids.insert(psid);

        u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
        mfa2::map_string_to_component matchingComponentsMap =
          mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
        u_int32_t choice = 0;
        for (mfa2::map_string_to_component::iterator it = matchingComponentsMap.begin();
             it != matchingComponentsMap.end(); ++it, ++choice)
        {
            vector<u_int8_t> componentBuffer;
            if (!mfa2Pkg->unzipComponent(matchingComponentsMap, choice, componentBuffer))
            {
                _errMsg = "Failed to extract component from MFA2 file: " + fname;
                _log += _errMsg;
                res = -1;
                goto clean_up;
            }

            u_int8_t majorVer = it->second.getComponentDescriptor().getVersionExtension().getMajor();
            patchMFA2ImageSignature(componentBuffer, majorVer);

            PsidQueryItem item;
            item.selector_tag = it->first;
            int rc = fillQueryItemFromBuffer(fname, psid, componentBuffer.data(), componentBuffer.size(), item);
            if (rc < 0)
            {
                res = rc;
                goto clean_up;
            }
            if (rc == 1)
            {
                item.selector_tag = it->first;
                riv.push_back(item);
            }
        }
    }

clean_up:
    delete mfa2Pkg;
    return res;
}

/**********************
 PLDM suport functions
***********************/
bool ImageAccess::loadPldmPkg(const string& fname)
{
    _pldm_buff.reset();
    if (_pldm_buff.loadFile(fname))
    {
        return false;
    }
    _pldmPkg.reset();
    if (!_pldmPkg.unpack(_pldm_buff))
    {
        return false;
    }
    return true;
}

FwComponent::comps_ids_t ImageAccess::ToCompId(ComponentIdentifier compIdentifier)
{
    if (compIdentifier == ComponentIdentifier::Identifier_BFB_Comp)
    {
        return FwComponent::comps_ids_t::COMPID_BFB;
    }
    return FwComponent::comps_ids_t::COMPID_UNKNOWN;
}

bool ImageAccess::getPldmDescriptorByPsid(string psid, u_int16_t type, u_int16_t& descriptor)
{
    return _pldmPkg.getPldmDescriptorByPsid(psid, type, descriptor);
}

bool ImageAccess::isPsidInPldm(string psid)
{
    return _pldmPkg.isPsidInPldm(psid);
}

int ImageAccess::getPldmComponentByPsid(string psid,
                                        ComponentIdentifier compIdentifier,
                                        u_int8_t** buff,
                                        u_int32_t& buffSize)
{
    return _pldmPkg.getComponentDataByPsid(compIdentifier, psid, buff, buffSize);
}

// get all components Or get all component with specific identifier
int ImageAccess::getPldmContent(vector<PsidQueryItem>& riv, ComponentIdentifier compIdentifier)
{
    if (!isValidComponent(compIdentifier))
    {
        _errMsg = "Invalid component identifier.";
        return -1;
    }
    u_int8_t dev_count = _pldmPkg.getDeviceIDRecordCount();
    for (u_int8_t i = 0; i < dev_count; i++)
    {
        PldmDevIdRecord* rec = _pldmPkg.getDeviceIDRecord(i);
        vector<u_int8_t> componentsIndexes = rec->getComponentsIndexes();
        for (size_t index = 0; index < componentsIndexes.size(); index++)
        {
            if (componentsIndexes[index])
            {
               PldmComponenetImage* getComponentImage = _pldmPkg.getComponentByIndex(index);
                ComponentIdentifier identifier = static_cast<ComponentIdentifier>(getComponentImage->getComponentIdentifier());

                PsidQueryItem item;
                ComponentIdentifierToStringValue(identifier, COMPONENT_NAME, item.name);
                item.type = getComponentImage->getcomponentVersionString();
                item.psid = rec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
                item.isNicComp = false;
                if ((isNicFwComponent(identifier) &&
                     ((compIdentifier == ComponentIdentifier::Identifier_General) || isNicFwComponent(compIdentifier))))
                {
                    item.isNicComp = true;
                    extract_pldm_image_info(
                      getComponentImage->getComponentData(), getComponentImage->getComponentSize(), item);
                }
                else if (identifier != compIdentifier && compIdentifier != ComponentIdentifier::Identifier_General)
                {
                    continue;
                }
                riv.push_back(item);
            }
        }
    }
    return 0;
}