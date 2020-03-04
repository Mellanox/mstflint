
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

#include "output_fmts.h"
#include "img_version.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sstream>
#include <iostream>
#include "err_msgs.h"
#include <iomanip>


string int2str(int n)
{
    stringstream num;
    string str;

    num << n;
    str = num.str();
    return str;
}


string hex2str(int n, int w = 1)
{
    stringstream num;
    string str;

    num << setfill('0') << setw(w) << hex << n;
    str = num.str();
    return str;
}


int OutputFmts::createInventoryXML(vector<MlnxDev*> &devs, PsidLookupDB &psidLookupDB, int result, string msg, string &buffer, int buf_is_file)
{
    int res = 0;
#ifdef USE_XML
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, devices_node = NULL, node = NULL; //device_node = NULL, fw_node = NULL, ;
    doc = xmlNewDoc(BAD_CAST "1.0");

    root_node = xmlNewNode(NULL, BAD_CAST "SVMInventory");
    xmlNewProp(root_node, BAD_CAST "lang", BAD_CAST "en");
    xmlDocSetRootElement(doc, root_node);

    for (unsigned i = 0; i < devs.size(); i++) {
        devices_node = xmlNewChild(root_node, NULL, BAD_CAST "Device", NULL);
        xmlNewProp(devices_node, BAD_CAST "vendorID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.vend_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "deviceID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.dev_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "subDeviceID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.subsys_id, 4).c_str());
        xmlNewProp(devices_node, BAD_CAST "subVendorID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.subsys_vend_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "domain", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.domain).c_str());
        xmlNewProp(devices_node, BAD_CAST "bus", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.bus).c_str());
        xmlNewProp(devices_node, BAD_CAST "device", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.dev).c_str());
        xmlNewProp(devices_node, BAD_CAST "function", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.func).c_str());
        if (!devs[i]->isQuerySuccess()) {
            continue;
        }
        xmlNewProp(devices_node, BAD_CAST "display", BAD_CAST psidLookupDB.getProdDesc(devs[i]->getBoardTypeId()).c_str());
        node = xmlNewChild(devices_node, NULL, BAD_CAST "Application", NULL);
        xmlNewProp(node, BAD_CAST "componentType", BAD_CAST "FRMW");
        xmlNewProp(node, BAD_CAST "version", BAD_CAST devs[i]->getFWVersion(false).c_str());
        xmlNewProp(node, BAD_CAST "display", BAD_CAST psidLookupDB.getProdDesc(devs[i]->getBoardTypeId()).c_str());

    }

    if (result) {
        node = xmlNewChild(root_node, NULL, BAD_CAST "SPStatus", NULL);
        xmlNewProp(node, BAD_CAST "result", BAD_CAST "false");
        node = xmlNewChild(node, NULL, BAD_CAST "Message", BAD_CAST msg.c_str());
        xmlNewProp(node, BAD_CAST "id", BAD_CAST int2str(result).c_str());
    }

    if (buf_is_file) {
        int rc = xmlSaveFormatFileEnc(buffer.c_str(), doc, "UTF-8", 1);
        if (rc == -1) {
            res = -1;
        }
    } else {
        xmlChar *doc_txt_ptr;
        int doc_txt_len;

        xmlDocDumpFormatMemoryEnc(doc, &doc_txt_ptr, &doc_txt_len, "UTF-8", 1);
        if (doc_txt_len) {
            buffer = (char*)doc_txt_ptr;
            //xmlFree(doc_txt_ptr); //TODO: This is a leak, temporarily only until windows crash is resolved!!
        }
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
#endif
    return res;
}


int OutputFmts::createBurnXML(vector<MlnxDev*> &devs, map<string, PsidQueryItem> &psidUpdateInfo, PsidLookupDB &psidLookupDB, string &buffer, int buf_is_file, int compareFFV)
{
    int res = 0;
#ifdef USE_XML
    int boot_required = 0;
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, devices_node = NULL, node = NULL, app_node = NULL;
    doc = xmlNewDoc(BAD_CAST "1.0");

    root_node = xmlNewNode(NULL, BAD_CAST "SVMExecution");
    xmlNewProp(root_node, BAD_CAST "lang", BAD_CAST "en");
    xmlDocSetRootElement(doc, root_node);
    for (unsigned i = 0; i < devs.size(); i++) {
        devices_node = xmlNewChild(root_node, NULL, BAD_CAST "Device", NULL);
        xmlNewProp(devices_node, BAD_CAST "vendorID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.vend_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "deviceID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.dev_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "subDeviceID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.subsys_id, 4).c_str());
        xmlNewProp(devices_node, BAD_CAST "subVendorID", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.subsys_vend_id).c_str());
        xmlNewProp(devices_node, BAD_CAST "bus", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.bus).c_str());
        xmlNewProp(devices_node, BAD_CAST "device", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.dev).c_str());
        xmlNewProp(devices_node, BAD_CAST "function", BAD_CAST hex2str(devs[i]->getDevInfo()->pci.func).c_str());
        xmlNewProp(devices_node, BAD_CAST "display", BAD_CAST psidLookupDB.getProdDesc(devs[i]->getBoardTypeId()).c_str());
        if (!devs[i]->isQuerySuccess()) {
            node = xmlNewChild(devices_node, NULL, BAD_CAST "SPStatus", NULL);
            xmlNewProp(node, BAD_CAST "result", BAD_CAST "false");
            node = xmlNewChild(node, NULL, BAD_CAST "Message", BAD_CAST "Failed to query the device.");
            xmlNewProp(node, BAD_CAST "id", BAD_CAST int2str(ERR_CODE_QUERY_FAILED).c_str());
            continue;
        }
        app_node = xmlNewChild(devices_node, NULL, BAD_CAST "Application", NULL);
        xmlNewProp(app_node, BAD_CAST "componentType", BAD_CAST "FRMW");
        xmlNewProp(app_node, BAD_CAST "version", BAD_CAST devs[i]->getFWVersion(false).c_str());
        xmlNewProp(app_node, BAD_CAST "display", BAD_CAST psidLookupDB.getProdDesc(devs[i]->getBoardTypeId()).c_str());

        if (psidUpdateInfo.find(devs[i]->getPsid()) != psidUpdateInfo.end()) {
            if (psidUpdateInfo[devs[i]->getPsid()].found) {
                node = xmlNewChild(app_node, NULL, BAD_CAST "Package", NULL);
                ImgVersion *fwImgVer = (ImgVersion*)psidUpdateInfo[devs[i]->getPsid()].findImageVersion("FW");
                if (fwImgVer != NULL) {
                    xmlNewProp(node, BAD_CAST "version", BAD_CAST fwImgVer->getPrintableVersion(compareFFV, false).c_str());
                }
            }
        }
        node = xmlNewChild(app_node, NULL, BAD_CAST "SPStatus", NULL);

        int burn_res = ERR_CODE_PROG_FAILED;
        string msg = "Update failure.";
        if (devs[i]->isBurnSuccess() == 0) {
            msg += " ";
            msg += devs[i]->getLastErrMsg();
        } else if (devs[i]->isBurnSuccess() == 1) {
            boot_required = 1;
            burn_res = MLX_FWM_SUCCESS;
            msg = "Update success.";
        } else { // == -1
            if (psidUpdateInfo.find(devs[i]->getPsid()) != psidUpdateInfo.end()) {
                if (!psidUpdateInfo[devs[i]->getPsid()].found) {
                    msg += " No relevant image file was found for this device";
                } else if (psidUpdateInfo[devs[i]->getPsid()].found > 1) {
                    msg += " Multiple image sources found for this device";
                } else {
                    ImgVersion *fwImgVer = (ImgVersion*)psidUpdateInfo[devs[i]->getPsid()].findImageVersion("FW");
                    if (fwImgVer != NULL) {
                        if ((devs[i]->compareFWVer(*fwImgVer) <= 0) && !_force_mode) {
                            burn_res = MLX_FWM_SUCCESS;
                            msg = "Update success. No update required.";
                        }
                    }
                }
            } else {
                msg = "Update failure. No relevant image file was found for this device";
            }
        }

        xmlNewProp(node, BAD_CAST "result", BAD_CAST(burn_res ? "false" : "true" ));
        node = xmlNewChild(node, NULL, BAD_CAST "Message", BAD_CAST msg.c_str());
        xmlNewProp(node, BAD_CAST "id", BAD_CAST int2str(burn_res).c_str());
    }
    node = xmlNewChild(root_node, NULL, BAD_CAST "RebootRequired", BAD_CAST int2str(boot_required).c_str());

    if (buf_is_file) {
        int rc = xmlSaveFormatFileEnc(buffer.c_str(), doc, "UTF-8", 1);
        if (rc == -1) {
            res = -1;
        }
    } else {
        xmlChar *doc_txt_ptr;
        int doc_txt_len;

        xmlDocDumpFormatMemoryEnc(doc, &doc_txt_ptr, &doc_txt_len, "UTF-8", 1);
        if (doc_txt_len) {
            buffer = (char*)doc_txt_ptr;
            //xmlFree(doc_txt_ptr); //TODO: This is a leak, temporarily only until windows crash is resolved!!
        }
    }
    (void) node;
    xmlFreeDoc(doc);
    xmlCleanupParser();
#endif
    return res;
}


int OutputFmts::createFailXML(int result, int update_query_, string &buffer, int buf_is_file)
{
    int res = 0;
#ifdef USE_XML
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node = NULL;
    doc = xmlNewDoc(BAD_CAST "1.0");

    if (update_query_ == 0) {
        root_node = xmlNewNode(NULL, BAD_CAST "SVMInventory");
    } else {
        root_node = xmlNewNode(NULL, BAD_CAST "SVMExecution");
    }
    xmlNewProp(root_node, BAD_CAST "lang", BAD_CAST "en");
    xmlDocSetRootElement(doc, root_node);

    node = xmlNewChild(root_node, NULL, BAD_CAST "SPStatus", NULL);
    xmlNewProp(node, BAD_CAST "result", BAD_CAST "false");
    if (update_query_ == 1) {
        xmlNewProp(node, BAD_CAST "code", BAD_CAST int2str(result).c_str());
    }
    node = xmlNewChild(node, NULL, BAD_CAST "Message", BAD_CAST getErrStr(result).c_str());
    xmlNewProp(node, BAD_CAST "id", BAD_CAST int2str(result).c_str());

    if (update_query_ == 1) {
        node = xmlNewChild(root_node, NULL, BAD_CAST "RebootRequired", BAD_CAST "0");
    }

    if (buf_is_file) {
        int rc = xmlSaveFormatFileEnc(buffer.c_str(), doc, "UTF-8", 1);
        if (rc == -1) {
            res = -1;
        }
    } else {
        xmlChar *doc_txt_ptr;
        int doc_txt_len;

        xmlDocDumpFormatMemoryEnc(doc, &doc_txt_ptr, &doc_txt_len, "UTF-8", 1);
        if (doc_txt_len) {
            buffer = (char*)doc_txt_ptr;
            //xmlFree(doc_txt_ptr); //TODO: This is a leak, temporarily only until windows crash is resolved!!
        }
    }
    (void) node;
    xmlFreeDoc(doc);
    xmlCleanupParser();
#endif
    return res;
}


void OutputFmts::setForceModeParam(bool force_mode)
{
    _force_mode = force_mode;
}

