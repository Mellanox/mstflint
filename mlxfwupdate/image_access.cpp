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
#include "mlxfwops/lib/mlxfwops.h"
#include "mlxfwops/lib/psid_utils.h"
#include "pldmlib/pldm_dev_id_record.h"
#include "pldmlib/pldm_component_image.h"
#include <tools_layouts/image_info_layouts.h>
#include "pldm_utils/pldm_utils.h"
#include "mft_utils/mft_utils.h"
#ifndef MST_CPU_armv7l_umbriel
#include <mlxarchive/mlxarchive_mfa2.h>
#endif
#include "mlxsign_lib/mlxsign_aesctr_via_openssl.h"

#define ITOC_ASCII 0x49544f43
#define TOC_HEADER_SIZE 0x20
#define TOC_ENTRY_SIZE 0x20
#define FS3_DEFAULT_SECTOR_SIZE 0x1000

using namespace std;

#ifndef MST_CPU_armv7l_umbriel
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
#endif

ImageAccess::ImageAccess(int compareFFV)
{
    _imgFwOps = nullptr;
    _compareFFV = compareFFV;
    _cachedMfa = nullptr;
    memset(&_imgFwParams, 0, sizeof(_imgFwParams));
    memset(_errBuff, 0, sizeof(_errBuff));
}

ImageAccess::~ImageAccess()
{
    if (_imgFwOps)
    {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = nullptr;
    }
    closeCachedMfa();
}

mfa_desc* ImageAccess::ensureMfaOpen(const string& fname)
{
    if (_cachedMfa != nullptr && _cachedMfaFname == fname)
    {
        return _cachedMfa;
    }
    closeCachedMfa();
    if (mfa_open_file(&_cachedMfa, fname.c_str()))
    {
        _cachedMfa = nullptr;
        return nullptr;
    }
    _cachedMfaFname = fname;
    return _cachedMfa;
}

void ImageAccess::closeCachedMfa()
{
    if (_cachedMfa != nullptr)
    {
        mfa_close(_cachedMfa);
        _cachedMfa = nullptr;
        _cachedMfaFname.clear();
    }
}

bool ImageAccess::hasMFAs(string directory)
{
    DIR* d;
    struct dirent* dir;
    int rc;
    d = opendir(directory.c_str());
    if (d == nullptr)
    {
        return false;
    }
    while ((dir = readdir(d)) != nullptr)
    {
        string fl = dir->d_name;
        if (fl == "." || fl == "..")
        {
            continue;
        }
        string fpath = directory;
        fpath += "/";
        fpath += fl;
        rc = getFileSignature(fpath);
        if (rc == IMG_SIG_TYPE_BIN || rc == IMG_SIG_TYPE_MFA || rc == IMG_SIG_TYPE_MFA2)
        {
            closedir(d);
            return true;
        }
    }
    closedir(d);
    return false;
}
int ImageAccess::queryDirPsid(string& path,
                              string& psid,
                              string& selector_tag,
                              int image_type,
                              vector<PsidQueryItem>& riv)
{
    int res = 0;
    DIR* d;
    struct dirent* dir;
    int found = 0;
    int rc;

    d = opendir(path.c_str());
    if (d == nullptr)
    {
        return -1;
    }

    while ((dir = readdir(d)) != nullptr)
    {
        PsidQueryItem ro;
        string fl = dir->d_name;
        if (fl == "." || fl == "..")
        {
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
        if (rc < 0)
        {
            res = -1;
            goto clean_up;
        }
        if (rc == 1)
        {
            riv.push_back(ro);
            found++;
            riv[0].found = found;
            res = 1;
        }
    }

    if (found > 1)
    {
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
    if (_imgFwOps == nullptr)
    {
        _errMsg = "-E- " + (string)_errBuff + "\n";
        if (_errMsg.find("upgrade tool") != std::string::npos)
        {
            _warning = _errMsg;
        }
        else if (_errMsg.find("with higher Version") != std::string::npos)
        {
            _warning = _errMsg;
        }
        _log += _errMsg;
        return false;
    }
    return true;
}

bool ImageAccess::PldmOpsToFwOps(const string& psid,
                                 const string& component,
                                 FwOperations* imgFwOps,
                                 FwOperations** newImageOps,
                                 mfile* devMfile)
{
    if (imgFwOps->FwType() != FIT_PLDM)
    {
        return false;
    }
    else
    {
        FsPldmOperations* pldmOps = dynamic_cast<FsPldmOperations*>(imgFwOps);
        if (pldmOps == nullptr)
        {
            return false;
        }
        if (!pldmOps->LoadPldmPackage())
        {
            return false;
        }

        if (!pldmOps->FwOperationsCreate((char*)psid.c_str(), component, newImageOps, devMfile))
        {
            return false;
        }
    }
    return true;
}

image_flow_type_t ImageAccess::DetermineFlow(const string& fname, const string& psid)
{
    int signature = getFileSignature(fname);
    if (signature == IMG_SIG_TYPE_PLDM)
    {
        return PLDM_FLOW;
    }
    else if (signature == IMG_SIG_TYPE_MFA)
    {
        mfa_desc* mfa_d = ensureMfaOpen(fname);
        if (mfa_d == nullptr)
        {
            _errMsg = "Failed to open MFA file";
            return UNKNOWN_FLOW;
        }
        map_entry_hdr* map_entry = mfa_get_map_entry(mfa_d, (char*)psid.c_str());
        if (map_entry == nullptr)
        {
            return UNKNOWN_FLOW;
        }

        image_flow_type_t flowType = static_cast<image_flow_type_t>(map_entry->map_type);
        // support legacy MFA without map_type
        if (flowType == BINARY_IN_MFA_FLOW)
        {
            if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str()))
            {
                return UNKNOWN_FLOW;
            }
            if (_imgFwOps->FwType() == FIT_PLDM)
            {
                flowType = PLDM_TYPE_2_IN_MFA_FLOW;
            }
            _imgFwOps->FwCleanUp();
            delete _imgFwOps;
            _imgFwOps = nullptr;
        }
        return flowType;
    }
    else if (signature == IMG_SIG_TYPE_MFA2)
    {
#ifndef MST_CPU_armv7l_umbriel
        mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
        if (mfa2Pkg == nullptr)
        {
            return UNKNOWN_FLOW;
        }
        u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
        mfa2::map_string_to_component matchingComponentsMap =
          mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
        delete mfa2Pkg;
        return matchingComponentsMap.empty() ? UNKNOWN_FLOW : MFA2_FLOW;
#else
        (void)psid;
        return UNKNOWN_FLOW;
#endif
    }
    else if (signature == IMG_SIG_TYPE_BIN)
    {
        return BINARY_FLOW;
    }
    return UNKNOWN_FLOW;
}

int ImageAccess::queryPsid(const string& fname,
                           const string& psid,
                           string& selector_tag,
                           int image_type,
                           PsidQueryItem& ri)
{
    int res = 0;
    mfa_desc* mfa_d = nullptr;
    fw_info_t img_query;
    string iniName = "";
    vector<u_int8_t> sect; // to get fw configuration.
    vector<u_int8_t> dest;

    int flowType = DetermineFlow(fname, psid);
    map_entry_hdr* map_entry = nullptr;

    if (flowType == PLDM_TYPE_1_IN_MFA_FLOW || flowType == BINARY_IN_MFA_FLOW || flowType == PLDM_TYPE_2_IN_MFA_FLOW)
    {
        mfa_d = ensureMfaOpen(fname);
        if (mfa_d == nullptr)
        {
            _errMsg = "Failed to open MFA file";
            return -1;
        }
        map_entry = mfa_get_map_entry(mfa_d, (char*)psid.c_str());
        if (map_entry == nullptr)
        {
            return -1;
        }
    }

    ri.psid = psid;
    ri.found = 0;

    if (flowType == MFA2_FLOW)
    {
        return queryPsidMfa2(fname, psid, selector_tag, image_type, ri);
    }

    if (flowType == PLDM_TYPE_2_IN_MFA_FLOW)
    {
        ri.pns = "";

        if (mfa_d != nullptr)
        {
            char* pn = mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"PN");
            if (pn != nullptr)
            {
                ri.pns = pn;
                free(pn);
            }
            char* desc =
              mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"DESCRIPTION"); // TODO: Make more efficient
            if (desc != nullptr)
            {
                ri.description = desc;
                free(desc);
            }

            // Get FW version from MFA:
            map_entry_hdr* map_entry = mfa_get_map_entry(mfa_d, (char*)psid.c_str());
            if (map_entry == nullptr)
            {
                goto clean_up;
            }
            map_image_entry* map_img = mfa_get_map_image(map_entry, 0);
            if (map_img == nullptr)
            {
                goto clean_up;
            }
            toc_entry* toc = mfa_get_image_toc(mfa_d, map_img);
            if (toc == nullptr)
            {
                goto clean_up;
            }
            u_int16_t fwVer[3];
            fwVer[0] = toc->version[0];
            fwVer[1] = toc->version[1];
            fwVer[2] = toc->version[2];

            u_int16_t fwVerMajor = fwVer[0];
            char* branch = mfa_get_map_entry_metadata(map_entry, (char*)"BRANCH");
            if (branch)
            {
                if (FwVersion::is_branch_version(branch))
                {
                    ri.branch = branch;
                    std::string branchSubstr = ri.branch.substr(0, 2);
                    char* endp = nullptr;
                    fwVerMajor = strtoul(branchSubstr.c_str(), &endp, 10);
                    if (*endp)
                    {
                        fwVerMajor = fwVer[0];
                    }
                }
                free(branch);
            }

            ImgVersion imgv;
            imgv.setVersion("FW", 3, fwVer, ri.branch);
            ri.imgVers.push_back(imgv);

            // Determine device type based on FW version major
            switch (fwVerMajor)
            {
                case 35:
                {
                    ri.devId = 0x25b;
                    ri.revId = 0x0;
                    break;
                }
                default:
                {
                    _errMsg = "MFA support for PLDM/fwpkg applicable only to Quantum3 FW images";
                    _log += _errMsg;
                    goto clean_up;
                }
            }
        }
        ri.url = fname;
        ri.found = 1;
        res = 1;
    }
    else
    {
        bool isStripedImage = false;
        if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str()))
        {
            goto clean_up;
        }

        if (flowType == PLDM_TYPE_1_IN_MFA_FLOW || flowType == PLDM_FLOW)
        {
            isStripedImage = true;
            FwOperations* newImageOps = nullptr;
            string mainComponent;
            if (!getMainComponent(fname, psid, mainComponent))
            {
                _errMsg = "Failed to get main component";
                _log += _errMsg;
                goto clean_up;
            }
            // first component is the main component - supported components are ordered by priority
            if (!PldmOpsToFwOps(psid, mainComponent, _imgFwOps, &newImageOps))
            {
                _errMsg = "Failed to convert PLDM fwpkg to fwops";
                _log += _errMsg;
                goto clean_up;
            }
            if (newImageOps == nullptr)
            {
                _errMsg = "PldmOpsToFwOps returned null";
                _log += _errMsg;
                goto clean_up;
            }

            if (_imgFwOps != nullptr)
            {
                _imgFwOps->FwCleanUp();
                delete _imgFwOps;
            }
            _imgFwOps = newImageOps;
        }

        memset(&img_query, 0, sizeof(img_query));
        if (!_imgFwOps->FwQuery(&img_query, true, isStripedImage))
        {
            _errMsg = "Failed to query " + (string)_imgFwOps->err();
            _log += _errMsg;
            goto clean_up;
        }

        if (!psid.compare(img_query.fw_info.psid) ||
            (flowType == BINARY_FLOW && psid_utils::areMajorCompatible(psid.c_str(), img_query.fw_info.psid)))
        {
            u_int32_t* supporteHwId;
            u_int32_t supporteHwIdNum;
            _imgFwOps->getSupportedHwId(&supporteHwId, supporteHwIdNum);
            ri.found = 1;
            ri.url = fname;
            ri.pns = "";
            ri.devId = (supporteHwIdNum > 0) ? supporteHwId[0] : 0;
            ri.revId = (ri.devId >> 16) & 0xffff;
            ri.devId = ri.devId & 0xffff;
            ri.isFailSafe = img_query.fw_info.is_failsafe;
            if (_imgFwOps->FwGetSection(H_FW_CONF, sect))
            {
                if (sect.empty())
                {
                    _errMsg = "H_FW_CONF section is empty";
                    _log += _errMsg;
                    goto clean_up;
                }
                if (unzipDataFile(sect, dest))
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
            ri.iniName = iniName;
            bool encrypted = (map_entry != nullptr) ? is_encrypted(map_entry) : false;
            if ((flowType == PLDM_TYPE_1_IN_MFA_FLOW || flowType == BINARY_IN_MFA_FLOW) && encrypted)
            {
                string psid_copy = psid; // Create mutable copy since decrypt_description expects non-const reference
                string desc_key = "DESCRIPTION";
                string pn_key = "PN";
                bool decryptOk = true;
                if (!decrypt_metadata_section(desc_key, map_entry, psid_copy, ri.description))
                {
                    _errMsg = "Failed to decrypt description for psid: " + psid;
                    decryptOk = false;
                }
                else if (!decrypt_metadata_section(pn_key, map_entry, psid_copy, ri.pns))
                {
                    _errMsg = "Failed to decrypt pn for psid: " + psid;
                    decryptOk = false;
                }
                if (!decryptOk)
                {
                    res = -1;
                    goto clean_up;
                }
            }
            else if (flowType == BINARY_IN_MFA_FLOW || flowType == PLDM_TYPE_1_IN_MFA_FLOW)
            {
                char* pn = mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"PN");
                if (pn != nullptr)
                {
                    ri.pns = pn;
                    free(pn);
                }
                char* desc =
                  mfa_get_board_metadata(mfa_d, (char*)psid.c_str(), (char*)"DESCRIPTION"); // TODO: Make more efficient
                if (desc != nullptr)
                {
                    ri.description = desc;
                    free(desc);
                }
            }
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
                if (tpc == nullptr)
                {
                    // imgVer.setExpansionRomtoUnknown();
                    tpc = "UNKNOWN_ROM";
                }
                int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
                imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
                ri.imgVers.push_back(imgVer);
            }
            res = 1;
        }
    }

clean_up:
    (void)selector_tag;
    (void)image_type;
    if (_imgFwOps != nullptr)
    {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = nullptr;
    }
    return res;
}
bool ImageAccess::getBurnSupportedComponents(const string& fname,
                                             const string& psid,
                                             vector<string>& supportedComponents)
{
    if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str()))
    {
        return 0;
    }

    FsPldmOperations* pldmOps = dynamic_cast<FsPldmOperations*>(_imgFwOps);
    if (pldmOps == nullptr)
    {
        return false;
    }

    if (!pldmOps->LoadPldmPackage())
    {
        return false;
    }

    if (!pldmOps->getSupportedComponents(psid, supportedComponents))
    {
        return false;
    }
    return true;
}

bool ImageAccess::getMainComponent(const string& fname, const string& psid, string& mainComponent)
{
    if (!openImg(FHT_FW_FILE, (char*)psid.c_str(), (char*)fname.c_str()))
    {
        return false;
    }

    FsPldmOperations* pldmOps = dynamic_cast<FsPldmOperations*>(_imgFwOps);
    if (pldmOps == nullptr)
    {
        return false;
    }

    if (!pldmOps->LoadPldmPackage())
    {
        return false;
    }

    if (!pldmOps->GetMainComponentName(psid, mainComponent))
    {
        return false;
    }
    return true;
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
    u_int8_t* alignedBuffer = nullptr;
    u_int32_t* supporteHwId = nullptr;
    u_int32_t supporteHwIdNum = 0;

    ri.psid = psid;
    ri.found = 0;
    ri.url = fname;

    alignedBuffer = (u_int8_t*)malloc(imageSize);
    if (alignedBuffer == nullptr)
    {
        _errMsg = "Memory allocation failure for image extracted from: " + fname;
        _log += _errMsg;
        return -1;
    }
    memcpy(alignedBuffer, imageData, imageSize);

    if (!openImg(FHT_FW_BUFF, (char*)psid.c_str(), nullptr, 0, (u_int32_t*)alignedBuffer, imageSize))
    {
        goto clean_up;
    }

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true))
    {
        _errMsg = "Failed to query " + (string)_imgFwOps->err();
        _log += _errMsg;
        res = -1;
        goto clean_up;
    }

    _imgFwOps->getSupportedHwId(&supporteHwId, supporteHwIdNum);
    ri.found = 1;
    ri.pns = strlen(img_query.fs3_info.name) ? img_query.fs3_info.name : "";
    ri.description = strlen(img_query.fs3_info.description) ? img_query.fs3_info.description : "";
    ri.devId = (supporteHwIdNum > 0) ? supporteHwId[0] : 0;
    ri.revId = (ri.devId >> 16) & 0xffff;
    ri.devId = ri.devId & 0xffff;
    ri.isFailSafe = img_query.fw_info.is_failsafe;
    if (_imgFwOps->FwGetSection(H_FW_CONF, sect))
    {
        if (sect.empty())
        {
            _errMsg = "H_FW_CONF section is empty";
            _log += _errMsg;
            res = -1;
            goto clean_up;
        }
        if (unzipDataFile(sect, dest))
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
        if (tpc == nullptr)
        {
            tpc = "UNKNOWN_ROM";
        }
        int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
        imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
        ri.imgVers.push_back(imgVer);
    }
    res = 1;

clean_up:
    if (_imgFwOps != nullptr)
    {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = nullptr;
    }
    if (alignedBuffer != nullptr)
    {
        free(alignedBuffer);
    }
    return res;
}

int ImageAccess::queryPsidMfa2(const string& fname,
                               const string& psid,
                               string& selector_tag,
                               int image_type,
                               PsidQueryItem& ri)
{
#ifndef MST_CPU_armv7l_umbriel
    (void)image_type;
    int res = 0;
    mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
    if (mfa2Pkg == nullptr)
    {
        _errMsg = "Failed to open MFA2 file: " + fname;
        _log += _errMsg;
        return -1;
    }

    u_int16_t fwVer[3] = {0xff, 0xff, 0xffff};
    mfa2::map_string_to_component matchingComponentsMap = mfa2Pkg->getMatchingComponents((char*)psid.c_str(), fwVer);
    if (matchingComponentsMap.empty())
    {
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

    mfa2::map_string_to_component::iterator itAtOffset = matchingComponentsMap.begin();
    std::advance(itAtOffset, choice);
    u_int8_t majorVer = itAtOffset->second.getComponentDescriptor().getVersionExtension().getMajor();
    patchMFA2ImageSignature(componentBuffer, majorVer);

    selector_tag = resolvedTag;
    ri.selector_tag = resolvedTag;
    res = fillQueryItemFromBuffer(fname, psid, componentBuffer.data(), componentBuffer.size(), ri);
    delete mfa2Pkg;
    return res;
#else
    (void)fname;
    (void)psid;
    (void)selector_tag;
    (void)image_type;
    (void)ri;
    _errMsg = "MFA2 support is not available on this platform";
    _log += _errMsg;
    return -1;
#endif
}

int ImageAccess::getImage(const string& fname,
                          const string& psid,
                          string& selector_tag,
                          int image_type,
                          u_int8_t** filebuf)
{
    int res = -1;
    int type = getFileSignature(fname);

    if (type == IMG_SIG_TYPE_MFA)
    {
        mfa_desc* mfa_d = ensureMfaOpen(fname);
        if (mfa_d != nullptr)
        {
            res = mfa_get_image(mfa_d, (char*)psid.c_str(), image_type, (char*)selector_tag.c_str(), filebuf);
        }
    }
    else if (type == IMG_SIG_TYPE_MFA2)
    {
#ifndef MST_CPU_armv7l_umbriel
        mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
        if (mfa2Pkg == nullptr)
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
            _errMsg = "No matching component found in MFA2 file for PSID: " + psid;
            _log += _errMsg;
            delete mfa2Pkg;
            return -1;
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

        u_int8_t* buf = (u_int8_t*)malloc(componentBuffer.size());
        if (buf == nullptr)
        {
            _errMsg = "Memory allocation failure for image extracted from: " + fname;
            _log += _errMsg;
            delete mfa2Pkg;
            return -1;
        }
        memcpy(buf, componentBuffer.data(), componentBuffer.size());
        *filebuf = buf;
        selector_tag = resolvedTag;
        res = componentBuffer.size();
        delete mfa2Pkg;
#else
        (void)psid;
        (void)selector_tag;
        (void)image_type;
        _errMsg = "MFA2 support is not available on this platform";
        _log += _errMsg;
        res = -1;
#endif
    }
    else if (type == IMG_SIG_TYPE_BIN)
    {
        res = getImage(fname, filebuf);
    }
    // else type is unknown and res = -1

    return res;
}

int ImageAccess::getImage(const string& fname, u_int8_t** filebuf)
{
    int res = -1;
    FILE* fp;
    u_int8_t* buf = nullptr;
    long int fsize;
    long int sz;

    if ((fp = fopen(fname.c_str(), "rb")) == nullptr)
    {
        _errMsg = "Failed to open file : " + (string)fname.c_str();
        _log += _errMsg;
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) < 0)
    {
        _errMsg = "Fseek failed on file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }

    fsize = ftell(fp);
    if (fsize <= 0)
    {
        _errMsg = "Ftell failed on file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }
    rewind(fp);

    buf = (u_int8_t*)malloc(fsize * sizeof(u_int8_t));
    if (buf == nullptr)
    {
        _errMsg = "Memory allocation failure for file : " + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }

    memset(buf, 0, fsize);
    *filebuf = buf;
    sz = fread(buf, 1, fsize, fp);
    if (sz != fsize || sz <= 0 || buf == nullptr)
    {
        _errMsg = "ftell size is not equivalent to fread total size" + (string)fname.c_str();
        _log += _errMsg;
        goto clean_up;
    }

    res = fsize;

clean_up:
    fclose(fp);
    if (res == -1)
    {
        if (buf != nullptr)
        {
            free(buf);
        }
    }
    return res;
}

bool ImageAccess::isMfaEncrypted(const string& fname)
{
    static const int header_size = 4;
    char magic[header_size];
    FILE* fin = fopen(fname.c_str(), "rb");
    if (!fin)
    {
        return false;
    }
    bool ok = (1 == fread(magic, header_size, 1, fin));
    fclose(fin);
    if (!ok)
    {
        return false;
    }
    if (0 == memcmp(magic, "MFAE", 4))
    {
        return true;
    }
    return false;
}

int ImageAccess::getFileSignature(const string& fname)
{
    static const int header_size = 16;
    FILE* fin;
    char tmpb[header_size];
    int res = -2;
    do
    {
        if (!(fin = fopen(fname.c_str(), "rb")))
        {
            break;
        }

        if (1 > fread(tmpb, header_size, 1, fin))
        {
            break;
        }
        res = getBufferSignature((u_int8_t*)tmpb, header_size);
    } while (0);

    if (fin)
    {
        fclose(fin);
    }
    return res;
}

int ImageAccess::getBufferSignature(u_int8_t* buf, u_int32_t size)
{
    int res = IMG_SIG_TYPE_UNKNOWN;

    if (size >= 4 && 0 == memcmp(buf, "MTFW", 4))
    {
        res = IMG_SIG_TYPE_BIN;
    }

    else if (0 == memcmp(buf, "MFAR", 4) || 0 == memcmp(buf, "MFAE", 4))
    {
        res = IMG_SIG_TYPE_MFA;
    }
#ifndef MST_CPU_armv7l_umbriel
    else if (size >= strlen(MFA2_FINGER_PRINT) && 0 == memcmp(buf, MFA2_FINGER_PRINT, strlen(MFA2_FINGER_PRINT)))
    {
        res = IMG_SIG_TYPE_MFA2;
    }
#endif
    else if ((size >= headerFormatRevision1.size() &&
              0 == memcmp(buf, headerFormatRevision1.data(), headerFormatRevision1.size())) ||
             (size >= headerFormatRevision3.size() &&
              0 == memcmp(buf, headerFormatRevision3.data(), headerFormatRevision3.size())))
    {
        res = IMG_SIG_TYPE_PLDM;
    }

    return res;
}

int ImageAccess::get_bin_content(const string& fname, vector<PsidQueryItem>& riv)
{
    fw_info_t img_query;
    int res = 0;
    char psid[33];
    PsidQueryItem item;
    ImgVersion imgv;

    if (_imgFwOps != nullptr)
    {
        _errMsg = "_imgFwOPs should be null";
        _log += _errMsg;
        return -1;
    }
    if (!openImg(FHT_FW_FILE, nullptr, (char*)fname.c_str()))
    {
        return -1;
    }

    memset(&img_query, 0, sizeof(img_query));
    if (!_imgFwOps->FwQuery(&img_query, true))
    {
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
    item.description = img_query.fs3_info.description;

    imgv.setVersion("FW", 3, img_query.fw_info.fw_ver, img_query.fw_info.branch_ver);
    item.imgVers.push_back(imgv);
    for (int i = 0; i < img_query.fw_info.roms_info.num_of_exp_rom; i++)
    {
        ImgVersion imgVer;
        const char* tpc = _imgFwOps->expRomType2Str(img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
        if (tpc == nullptr)
        {
            // imgVer.setExpansionRomtoUnknown();
            tpc = "UNKNOWN_ROM";
        }
        int sz = img_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
        if (img_query.fw_info.roms_info.rom_info[i].exp_rom_product_id == 0xf)
        {
            sz = 1;
        }
        imgVer.setVersion(tpc, sz, img_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
        item.imgVers.push_back(imgVer);
    }
    riv.push_back(item);

clean_up:
    _imgFwOps->FwCleanUp();
    delete _imgFwOps;
    _imgFwOps = nullptr;

    return res;
}


int ImageAccess::get_mfa_content(const string& fname, vector<PsidQueryItem>& riv, vector<string>& psid_list)
{
    map_entry_hdr* me = nullptr;
    int res = 0;

    mfa_desc* mfa_d = ensureMfaOpen(fname);
    if (mfa_d == nullptr)
    {
        return -1;
    }
    me = nullptr;
    char* val = nullptr;
    while ((me = mfa_get_next_mentry(mfa_d, me)))
    {
        PsidQueryItem item;
        // if tag is not empty, the psid is encrypted
        bool isEncrypted = is_encrypted(me);
        if (isEncrypted)
        {
            if (!psid_list.empty())
            {
                bool decryption_success = decrypt_psid(me, psid_list, item);
                if (!decryption_success)
                {
                    // can't decrypt psid, skip this entry
                    continue;
                }
                else
                {
                    string desc_key = "DESCRIPTION";
                    if (!decrypt_metadata_section(desc_key, me, item.psid, item.description))
                    {
                        _errMsg = "Failed to decrypt description for psid: " + item.psid;
                        res = -1;
                        break;
                    }
                    string pn_key = "PN";
                    if (!decrypt_metadata_section(pn_key, me, item.psid, item.pns))
                    {
                        _errMsg = "Failed to decrypt pn for psid: " + item.psid;
                        res = -1;
                        break;
                    }
                }
            }
            else
            {
                _errMsg = "Listing an encrypted MFA archive requires --show-psids";
                res = -1;
                break;
            }
        }
        else
        {
            char psid[33];
            memcpy(psid, me->board_type_id, 32);
            psid[32] = 0;
            item.psid = psid;

            if (!psid_list.empty() && std::find(psid_list.begin(), psid_list.end(), item.psid) == psid_list.end())
            {
                continue;
            }
            val = mfa_get_map_entry_metadata(me, (char*)"DESCRIPTION");
            if (val == nullptr)
            {
                item.description = "";
            }
            else
            {
                item.description = val;
                free(val);
            }

            val = mfa_get_map_entry_metadata(me, (char*)"PN");
            if (val == nullptr)
            {
                item.pns = "";
            }
            else
            {
                item.pns = val;
                free(val);
            }
        }
        val = mfa_get_map_entry_metadata(me, (char*)"BRANCH");
        if (val == nullptr)
        {
            item.branch = "";
        }
        else
        {
            item.branch = val;
            free(val);
        }

        if (item.psid.empty())
        {
            continue;
        }

        map_image_entry* imge;
        for (int i = 0; i < me->nimages; i++)
        {
            imge = mfa_get_map_image(me, i);
            if (imge == nullptr)
            {
                continue;
            }
            toc_entry* toc = mfa_get_image_toc(mfa_d, imge);
            if (toc == nullptr)
            {
                continue;
            }
            if (toc->num_ver_fields != 0)
            {
                item.type = imge->image_type;
                char select_tag[33];
                strncpy(select_tag, imge->select_tag, 32);
                select_tag[32] = 0;
                item.selector_tag = select_tag;
                char* subImgType;
                if ((subImgType = mfasec_get_sub_image_type_str(toc->subimage_type)) != nullptr)
                {
                    ImgVersion imgv;
                    if (subImgType[0] != '\0')
                    { // Not a padding section
                        imgv.setVersion(subImgType, toc->num_ver_fields, toc->version, item.branch);
                        item.imgVers.push_back(imgv);
                    }
                }
            }
        }
        riv.push_back(item);
    }
    return res;
}

int ImageAccess::get_mfa2_content(const string& fname, vector<PsidQueryItem>& riv)
{
#ifndef MST_CPU_armv7l_umbriel
    int res = 0;
    mfa2::MFA2* mfa2Pkg = mfa2::MFA2::LoadMFA2Package(fname);
    if (mfa2Pkg == nullptr)
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
#else
    (void)fname;
    (void)riv;
    _errMsg = "MFA2 support is not available on this platform";
    _log += _errMsg;
    return -1;
#endif
}

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
    snprintf(fw_branch, sizeof(fw_branch), "%.*s", BRANCH_LEN, image_info.vsd);
    ImgVersion imgv;
    imgv.setVersion("FW", FW_VER_SIZE, fw_ver, fw_branch);
    query_item.imgVers.push_back(imgv);
}

bool ImageAccess::extract_pldm_image_info(const u_int8_t* buff, u_int32_t size, PsidQueryItem& query_item)
{
    FImage fimage;
    if (!fimage.open((u_int32_t*)buff, size))
    {
        return false;
    }

    static const u_int32_t sector_size = FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t offset = 0;
    offset = (offset % sector_size == 0) ? offset : (offset + sector_size - offset % 0x1000);
    u_int8_t buffer[TOC_HEADER_SIZE] = {0}, entry_buffer[TOC_ENTRY_SIZE] = {0};
    struct connectx4_itoc_header itoc_header;
    bool image_info_found = false;
    while (offset < fimage.get_size())
    {
        // read ITOC header
        fimage.read(offset, buffer, TOC_HEADER_SIZE);
        connectx4_itoc_header_unpack(&itoc_header, buffer);
        if (itoc_header.signature0 != ITOC_ASCII)
        {
            offset += sector_size;
            continue;
        }
        int section_index = 0;
        struct connectx4_itoc_entry toc_entry;
        do
        {
            // read ITOC entry
            u_int32_t entry_addr = offset + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
            fimage.read(entry_addr, entry_buffer, TOC_ENTRY_SIZE);

            connectx4_itoc_entry_unpack(&toc_entry, entry_buffer);
            if (toc_entry.type == FS3_IMAGE_INFO)
            {
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

/**********************
 PLDM suport functions
***********************/
bool ImageAccess::UnpackPldmPkg()
{
    _pldmPkg.reset();
    if (!_pldmPkg.unpack(_pldm_buff))
    {
        _errMsg = "Failed to unpack PLDM package file";
        return false;
    }
    return true;
}

bool ImageAccess::loadPldmPkgFile(const string& fname)
{
    if (fname == _pldm_buff.getFname())
    {
        return true;
    }
    _pldm_buff.reset();
    if (!_pldm_buff.loadFile(fname))
    {
        _errMsg = "Failed to load PLDM package file: " + fname;
        return false;
    }
    return UnpackPldmPkg();
}

bool ImageAccess::getPldmImage(u_int8_t** buff, u_int32_t& buffSize, u_int16_t& swDevId, const string& psid)
{
    if (!_pldmPkg.isPsidInPldm(psid))
    {
        _errMsg = "PSID is not in PLDM";
        return false;
    }
    else if (!getPldmDescriptorByPsid(psid, DEV_ID_TYPE, swDevId))
    {
        _errMsg = "No swId found for psid: " + psid;
        return false;
    }

    return getPldmComponentByPsid(psid, ComponentIdentifier::Identifier_Not_Valid, buff, buffSize) != 0;
}

bool ImageAccess::GetDataFromDataSection(mfa_desc* mfa_d,
                                         map_entry_hdr* map_entry_hdr,
                                         u_int8_t** buff,
                                         u_int32_t& buffSize,
                                         u_int16_t& swDevId,
                                         const string& psid)
{
    if (map_entry_hdr->map_type == PLDM_TYPE_1_IN_MFA_FLOW)
    {
        u_int8_t* mfaBuff = nullptr;
        ssize_t mfaBuffSize = get_image_by_map_entry(mfa_d, 1, (char*)"", &mfaBuff, map_entry_hdr, nullptr);
        if (mfaBuffSize <= 0 || mfaBuff == nullptr)
        {
            _errMsg = "Failed to get image by map entry";
            free(mfaBuff);
            return false;
        }

        if (!loadPldmPkgBuffer(mfaBuff, mfaBuffSize))
        {
            _errMsg = "Failed to load PLDM package from buffer";
            free(mfaBuff);
            return false;
        }
        free(mfaBuff);
        // empty psid argument means get the first image in the PLDM package
        if (!getPldmImage(buff, buffSize, swDevId, psid))
        {
            _errMsg = "Failed to get PLDM image";
            return false;
        }
    }
    else
    {
        swDevId = 0;
        ssize_t rawSize = get_image_by_map_entry(mfa_d, 1, (char*)"", buff, map_entry_hdr, nullptr);
        if (rawSize <= 0 || *buff == nullptr)
        {
            _errMsg = "Failed to get image by map entry";
            free(*buff);
            *buff = nullptr;
            return false;
        }
        buffSize = (u_int32_t)rawSize;
    }
    return true;
}

bool ImageAccess::loadPldmPkgBuffer(u_int8_t* buffer, u_int32_t size)
{
    _pldm_buff.reset();
    _pldm_buff.loadBuffer(buffer, size);
    return UnpackPldmPkg();
}

FwComponent::comps_ids_t ImageAccess::ToCompId(ComponentIdentifier compIdentifier)
{
    if (compIdentifier == ComponentIdentifier::Identifier_BFB_Comp)
    {
        return FwComponent::comps_ids_t::COMPID_BFB;
    }
    return FwComponent::comps_ids_t::COMPID_UNKNOWN;
}

bool ImageAccess::getPldmDescriptorByPsid(const string& psid, u_int16_t type, u_int16_t& descriptor)
{
    return _pldmPkg.getPldmDescriptorByPsid(psid, type, descriptor);
}

bool ImageAccess::isPsidInPldm(const string& psid)
{
    return _pldmPkg.isPsidInPldm(psid);
}

int ImageAccess::getPldmComponentByPsid(const string& psid,
                                        ComponentIdentifier compIdentifier,
                                        u_int8_t** buff,
                                        u_int32_t& buffSize)
{
    if (!isValidComponent(compIdentifier))
    {
        string mainComponent;
        if (!_pldmPkg.getMainComponentNameByPsid(psid, mainComponent))
        {
            _errMsg = "No main component found for psid: " + psid;
            return 0;
        }
        try
        {
            StringToComponentIdentifier(mainComponent, compIdentifier);
        }
        catch (PLDMException& e)
        {
            _errMsg = e._err;
            return 0;
        }
    }
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
                ComponentIdentifier identifier =
                  static_cast<ComponentIdentifier>(getComponentImage->getComponentIdentifier());

                PsidQueryItem item;
                ComponentIdentifierToStringValue(identifier, ComponentField::Name, item.name);
                item.type = getComponentImage->getcomponentVersionString();
                item.psid = rec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
                item.isNicComp = false;
                if ((isNicFwComponent(identifier) &&
                     ((compIdentifier == ComponentIdentifier::Identifier_General) || isNicFwComponent(compIdentifier))))
                {
                    item.isNicComp = true;
                    extract_pldm_image_info(getComponentImage->getComponentData(),
                                            getComponentImage->getComponentSize(), item);
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

int ImageAccess::get_file_content(const string& fname, vector<PsidQueryItem>& riv, vector<string>& psid_list)
{
    int type = getFileSignature(fname);
    int res = -1;
    switch (type)
    {
        case IMG_SIG_TYPE_BIN:
            res = get_bin_content(fname, riv);
            break;
        case IMG_SIG_TYPE_MFA:
            res = get_mfa_content(fname, riv, psid_list);
            break;
        case IMG_SIG_TYPE_MFA2:
            res = get_mfa2_content(fname, riv);
            break;
        case IMG_SIG_TYPE_PLDM:
            if (!loadPldmPkgFile(fname))
            {
                return res;
            }
            res = getPldmContent(riv);
            break;
    }
    return res;
}

bool ImageAccess::decrypt_aes_ctr(const char* ct,
                                  u_int8_t ct_size,
                                  const u_int8_t* keySource,
                                  u_int8_t keySourceSize,
                                  string& pt)
{
    vector<u_int8_t> iv(AES_CTR_IV_SIZE, 0x00); // 16 bytes of zeros - not used in the encryption
    // Generate key from psid using SHA256
    vector<u_int8_t> key(KEY_SIZE);
    SHA256(reinterpret_cast<const unsigned char*>(keySource), keySourceSize, key.data());
    MlxSign::MlxSignAESCTRViaOpenSSL aesctr(key, iv);
    aesctr.Init();

    vector<u_int8_t> ciphertext(ct, ct + ct_size);
    vector<u_int8_t> msg;
    try
    {
        aesctr.Decrypt(ciphertext, msg);
    }
    catch (const exception& e)
    {
        return false;
    }

    // Strip trailing null bytes (encrypted padding)
    size_t len = msg.size();
    while (len > 0 && msg[len - 1] == '\0')
    {
        len--;
    }
    pt = std::string(reinterpret_cast<const char*>(msg.data()), len);
    return true;
}

bool ImageAccess::decrypt_psid(map_entry_hdr* me, vector<string>& psid_list, PsidQueryItem& item)
{
    if (psid_list.empty())
    {
        return false;
    }

    char encrypted_psid[PSID_SIZE];
    memcpy(encrypted_psid, me->board_type_id, PSID_SIZE);

    bool psid_found = false;
    for (const string& psid : psid_list)
    {
        u_int8_t* baseKey = (u_int8_t*)psid.c_str();
        u_int8_t baseKeySize = strlen(psid.c_str());

        string psid_candidate;
        if (decrypt_aes_ctr(encrypted_psid, PSID_SIZE, baseKey, baseKeySize, psid_candidate))
        {
            if (strncmp((char*)psid_candidate.c_str(), (char*)psid.c_str(), PSID_SIZE) != 0)
            {
                continue;
            }

            item.psid = psid_candidate;
            psid_found = true;
            break;
        }
    }
    return psid_found;
}

bool ImageAccess::decrypt_metadata_section(string& key, map_entry_hdr* me, string& psid, string& value)
{
    char* section = nullptr;
    int section_len;

    if (!is_encrypted(me))
    {
        return false;
    }

    if (key == "PN")
    {
        if (!get_metadata_section_till_following_key(me, "PN", "DESCRIPTION", &section, section_len))
        {
            return false;
        }
    }
    else if (key == "DESCRIPTION")
    {
        if (!get_metadata_section_till_following_key(me, "DESCRIPTION", "BRANCH", &section, section_len))
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    if (section_len < 0)
    {
        return false;
    }

    u_int8_t* baseKey = (u_int8_t*)psid.c_str();
    u_int8_t baseKeySize = strlen(psid.c_str());

    return decrypt_aes_ctr(section, section_len, baseKey, baseKeySize, value);
}

bool ImageAccess::get_metadata_section_till_following_key(map_entry_hdr* me,
                                                          const char* first_key,
                                                          const char* second_key,
                                                          char** section,
                                                          int& section_len)
{
    *section = mfa_get_map_entry_metadata(me, (char*)first_key);
    if (*section == nullptr)
    {
        return false;
    }
    // Get pointer to start of metadata section (after metadata_hdr)
    const uint8_t* metadata_start = (const uint8_t*)me + sizeof(map_entry_hdr) + sizeof(metadata_hdr);
    section_len = find_metadata_value_len(first_key, second_key, metadata_start);
    return true;
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
