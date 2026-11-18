
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

#include "output_fmts.h"
#include "img_version.h"
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include "err_msgs.h"
#include "common/tools_xml.h"
#include "mft_utils/mft_utils.h"

using nbu::mft::common::xml_attrs;
using nbu::mft::common::xml_close_tag;
using nbu::mft::common::xml_element;
using nbu::mft::common::xml_open_tag;

static xml_attrs toPciAttrXML(MlnxDev* dev, bool withDomain)
{
    const auto& pci = dev->getDevInfo()->pci;
    xml_attrs attrs;
    attrs.push_back({"vendorID", mft_utils::ToHexString(pci.vend_id, 1, false)});
    attrs.push_back({"deviceID", mft_utils::ToHexString(pci.dev_id, 1, false)});
    attrs.push_back({"subDeviceID", mft_utils::ToHexString(pci.subsys_id, 4, false)});
    attrs.push_back({"subVendorID", mft_utils::ToHexString(pci.subsys_vend_id, 1, false)});
    if (withDomain)
    {
        attrs.push_back({"domain", mft_utils::ToHexString(pci.domain, 1, false)});
    }
    attrs.push_back({"bus", mft_utils::ToHexString(pci.bus, 1, false)});
    attrs.push_back({"device", mft_utils::ToHexString(pci.dev, 1, false)});
    attrs.push_back({"function", mft_utils::ToHexString(pci.func, 1, false)});
    return attrs;
}

static const char* XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

static string toSpStatusXML(const string& indent, bool result, const string& code, int id, const string& msg)
{
    xml_attrs attrs = {{"result", result ? "true" : "false"}};
    if (!code.empty())
    {
        attrs.push_back({"code", code});
    }
    return indent + xml_open_tag("SPStatus", attrs) + "\n" + indent + "  " +
           xml_element("Message", {{"id", std::to_string(id)}}, msg) + "\n" + indent + xml_close_tag("SPStatus") + "\n";
}

static string toInventoryXML(vector<MlnxDev*>& devs, PsidLookupDB& psidLookupDB, int result, const string& msg)
{
    string res = XML_HEADER;
    bool emptyRoot = devs.empty() && !result;
    res += xml_open_tag("SVMInventory", {{"lang", "en"}}, emptyRoot) + "\n";
    if (emptyRoot)
    {
        return res;
    }
    for (unsigned i = 0; i < devs.size(); i++)
    {
        MlnxDev* dev = devs[i];
        xml_attrs devAttrs = toPciAttrXML(dev, true);
        if (!dev->isQuerySuccess())
        {
            res += "  " + xml_open_tag("Device", devAttrs, true) + "\n";
            continue;
        }
        string display = psidLookupDB.getProdDesc(dev->getBoardTypeId());
        devAttrs.push_back({"display", display});
        res += "  " + xml_open_tag("Device", devAttrs) + "\n";
        res += "    " +
               xml_open_tag("Application",
                            {{"componentType", "FRMW"}, {"version", dev->getFWVersion(false)}, {"display", display}},
                            true) +
               "\n";
        res += "  " + xml_close_tag("Device") + "\n";
    }
    if (result)
    {
        res += toSpStatusXML("  ", false, "", result, msg);
    }
    res += xml_close_tag("SVMInventory") + "\n";
    return res;
}

static void getBurnResult(MlnxDev* dev,
                          map<string, PsidQueryItem>& psidUpdateInfo,
                          bool force_mode,
                          int& burn_res,
                          string& msg,
                          bool& burned)
{
    burn_res = ERR_CODE_PROG_FAILED;
    msg = "Update failure.";
    burned = false;
    map<string, PsidQueryItem>::iterator it = psidUpdateInfo.find(dev->getPsid());
    if (dev->isBurnSuccess() == 0)
    {
        msg += " ";
        msg += dev->getLastErrMsg();
    }
    else if (dev->isBurnSuccess() == 1)
    {
        burned = true;
        burn_res = MLX_FWM_SUCCESS;
        msg = "Update success.";
    }
    else if (it != psidUpdateInfo.end())
    {
        PsidQueryItem& item = it->second;
        if (!item.found)
        {
            msg += " No relevant image file was found for this device";
        }
        else if (item.found > 1)
        {
            msg += " Multiple image sources found for this device";
        }
        else
        {
            ImgVersion* fwImgVer = (ImgVersion*)item.findImageVersion("FW");
            if (fwImgVer != NULL && (dev->compareFWVer(*fwImgVer) <= 0) && !force_mode)
            {
                burn_res = MLX_FWM_SUCCESS;
                msg = "Update success. No update required.";
            }
        }
    }
    else
    {
        msg = "Update failure. No relevant image file was found for this device";
    }
}

static string toDeviceXML(MlnxDev* dev,
                          map<string, PsidQueryItem>& psidUpdateInfo,
                          PsidLookupDB& psidLookupDB,
                          int compareFFV,
                          bool force_mode,
                          bool& burned)
{
    burned = false;
    string display = psidLookupDB.getProdDesc(dev->getBoardTypeId());
    xml_attrs devAttrs = toPciAttrXML(dev, false);
    devAttrs.push_back({"display", display});
    string res = "  " + xml_open_tag("Device", devAttrs) + "\n";
    if (!dev->isQuerySuccess())
    {
        res += toSpStatusXML("    ", false, "", ERR_CODE_QUERY_FAILED, "Failed to query the device.");
        res += "  " + xml_close_tag("Device") + "\n";
        return res;
    }
    res += "    " +
           xml_open_tag("Application",
                        {{"componentType", "FRMW"}, {"version", dev->getFWVersion(false)}, {"display", display}}) +
           "\n";
    map<string, PsidQueryItem>::iterator it = psidUpdateInfo.find(dev->getPsid());
    if (it != psidUpdateInfo.end() && it->second.found)
    {
        xml_attrs pkgAttrs;
        ImgVersion* fwImgVer = (ImgVersion*)it->second.findImageVersion("FW");
        if (fwImgVer != NULL)
        {
            pkgAttrs.push_back({"version", fwImgVer->getPrintableVersion(compareFFV, false)});
        }
        res += "      " + xml_open_tag("Package", pkgAttrs, true) + "\n";
    }
    int burn_res;
    string msg;
    getBurnResult(dev, psidUpdateInfo, force_mode, burn_res, msg, burned);
    res += toSpStatusXML("      ", burn_res == 0, "", burn_res, msg);
    res += "    " + xml_close_tag("Application") + "\n";
    res += "  " + xml_close_tag("Device") + "\n";
    return res;
}

static string toBurnXML(vector<MlnxDev*>& devs,
                        map<string, PsidQueryItem>& psidUpdateInfo,
                        PsidLookupDB& psidLookupDB,
                        int compareFFV,
                        bool force_mode)
{
    string res = XML_HEADER;
    res += xml_open_tag("SVMExecution", {{"lang", "en"}}) + "\n";
    int boot_required = 0;
    for (unsigned i = 0; i < devs.size(); i++)
    {
        bool burned = false;
        res += toDeviceXML(devs[i], psidUpdateInfo, psidLookupDB, compareFFV, force_mode, burned);
        if (burned)
        {
            boot_required = 1;
        }
    }
    res += "  " + xml_element("RebootRequired", xml_attrs(), std::to_string(boot_required)) + "\n";
    res += xml_close_tag("SVMExecution") + "\n";
    return res;
}

static string toFailXML(int result, int update_query_)
{
    string res = XML_HEADER;
    string root = (update_query_ == 0) ? "SVMInventory" : "SVMExecution";
    res += xml_open_tag(root, {{"lang", "en"}}) + "\n";
    res += toSpStatusXML("  ", false, update_query_ == 1 ? std::to_string(result) : "", result, getErrStr(result));
    if (update_query_ == 1)
    {
        res += "  " + xml_element("RebootRequired", xml_attrs(), "0") + "\n";
    }
    res += xml_close_tag(root) + "\n";
    return res;
}

static int writeXmlOutput(const string& xml, string& buffer, int buf_is_file)
{
    if (!buf_is_file)
    {
        buffer = xml;
        return 0;
    }
    ofstream f(buffer.c_str(), ios::binary | ios::trunc);
    if (!f)
    {
        fprintf(stderr, "-E- Failed to open the XML output file %s: %s\n", buffer.c_str(), strerror(errno));
        return -1;
    }
    f << xml;
    f.close();
    if (f.fail())
    {
        fprintf(stderr, "-E- Failed to write the XML output file %s: %s\n", buffer.c_str(), strerror(errno));
        return -1;
    }
    return 0;
}

int OutputFmts::createInventoryXML(vector<MlnxDev*>& devs,
                                   PsidLookupDB& psidLookupDB,
                                   int result,
                                   string msg,
                                   string& buffer,
                                   int buf_is_file)
{
    return writeXmlOutput(toInventoryXML(devs, psidLookupDB, result, msg), buffer, buf_is_file);
}

int OutputFmts::createBurnXML(vector<MlnxDev*>& devs,
                              map<string, PsidQueryItem>& psidUpdateInfo,
                              PsidLookupDB& psidLookupDB,
                              string& buffer,
                              int buf_is_file,
                              int compareFFV)
{
    return writeXmlOutput(toBurnXML(devs, psidUpdateInfo, psidLookupDB, compareFFV, _force_mode), buffer, buf_is_file);
}

int OutputFmts::createFailXML(int result, int update_query_, string& buffer, int buf_is_file)
{
    return writeXmlOutput(toFailXML(result, update_query_), buffer, buf_is_file);
}

void OutputFmts::setForceModeParam(bool force_mode)
{
    _force_mode = force_mode;
}
