
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

#include "server_request.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>


using namespace std;
#ifndef USE_CURL
#define USE_CURL
#endif

extern int abort_request;

ServerRequest::ServerRequest(const char *url, const char *proxy,
                             int compare_ffv, bool show_progress,
                             string key, string certificate,
                             unsigned int numberOfRetrials) : _LastErrorNo(0)
{
    _UseProxy      = 0;
    _Url           = url;
    _WebService    = _Url + "/downloads/firmware/mlx_fw_online_query.php";
    //_WebService    = _Url + "/mlx_fw_online_query.php";
    _compare_ffv   = compare_ffv;
    _show_progress = show_progress;
    _ceritifcate   = certificate;
    _numberOfRetrials = numberOfRetrials;
    _headers       = NULL;
    if (proxy != NULL) {
        if (proxy[0] != 0) {
            _UseProxy = 1;
            _Proxy = proxy;
        }
    }
    _key = key;
}


ServerRequest::~ServerRequest()
{

}

int ServerRequest::parseQueryResponse(string jsonTxt,
                                      vector<PsidQueryItem> &result,
                                      bool ignoreNotFound)
{
#ifdef USE_CURL
    string fileTag;
    Json::Value root;
    Json::Reader reader;
    bool rc = reader.parse(jsonTxt, root);
    if (!rc) {
        setError(rc, "-E- Failed To parse server response\n");
        return -1;
    }
    result.clear();
    for (unsigned j = 0; j < root.size(); j++) {
        PsidQueryItem ri;
        ri.found = 0;
        ri.type = -1;
        ri.url = "";
        ri.pns = "";
        ri.isFailSafe = true; // will be used for future!
        ri.release_note = "";
        if (!root[j].isObject()) {
            setError(-1, "-E- Failed To parse server response\n");
            return -1;
        }
        if (root[j].isMember("Found")) {
            if (ignoreNotFound and !root[j].get("Found", Json::nullValue).asInt()) {
                continue;
            }
        } else {
            continue;
        }
        try {
            Json::Value::Members profileNames = root[j].getMemberNames();
            for (unsigned i = 0; i < profileNames.size(); i++) {
                if (!profileNames[i].compare("PSID")) {
                    ri.psid  = root[j].get("PSID", Json::nullValue).asString();
                } else if (!profileNames[i].compare("Found")) {
                    ri.found = root[j].get(profileNames[i], Json::nullValue).asInt();
                } else if (!profileNames[i].compare("Type")) {
                    ri.type = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Found")) {
                    ri.found = root[j].get(profileNames[i], Json::nullValue).asInt();
                } else if (!profileNames[i].compare("PN")) {
                    ri.pns = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Name")) {
                    ri.name = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Release_note")) {
                    ri.release_note = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Ver")) {
                    const Json::Value versions = root[j]["Ver"];
                    if (versions.empty()) {
                        continue;
                    }
                    Json::Value::Members ROMS = versions.getMemberNames();

                    for (unsigned x = 0; x < ROMS.size(); x++) {
                        string rom_type = ROMS[x];
                        string rom_ver = versions.get(ROMS[x], Json::nullValue).asString();
                        int m, n, s;
                        u_int16_t fwVer[4];
                        int len;
                        if (sscanf(rom_ver.c_str(), "%d.%d.%d", &m, &n, &s)) {
                            if (!_compare_ffv or rom_type != "FW") {
                                fwVer[0] = m;
                                fwVer[1] = n;
                                fwVer[2] = s;
                                len = 3;
                            } else {
                                fwVer[0] = m;
                                fwVer[1] = n;
                                fwVer[2] = s / 100;
                                fwVer[3] = s % 100;
                                len = 4;
                            }
                            ImgVersion imgv;
                            imgv.setVersion(rom_type.c_str(), len, fwVer);
                            ri.imgVers.push_back(imgv);
                        }
                    }
                } else if (!profileNames[i].compare("URL")) {
                    ri.url = root[j].get(profileNames[i], Json::nullValue).asString();
                    ri.url = genertDownloadUrl(ri.url);
                }
            }
        } catch (runtime_error &e) {
            setError(-1, (string)"-E-" + e.what() + "\n");
            return -1;
        }
        result.push_back(ri);
        if (!ri.found) {
            setError(0, "-W- No online newer fw found for psid : " + ri.psid + "\n");
        }
    }
#endif
    return 0;
}

void ServerRequest::setError(int error_num, string error_msg)
{
    _LastErrorStr += error_msg;
    _LastErrorNo  = error_num;
}

void ServerRequest::getError(int &error_num, string &error_msg)
{
    error_num     = _LastErrorNo;
    error_msg     = _LastErrorStr;
}

int ServerRequest::DownloadFilesRequest(vector <DownloadedFileProperties> &files,
                                        string os, string devs, string type)
{

    int res          = 0;
#ifdef USE_CURL
    string response;
    Json::Value root;
    Json::StyledWriter writer;

    root["mode"]     = 2;
    root["psids"]    = "";
    root["os"]       = (os.length())   ? os   : "all";
    root["type"]     = (type.length()) ? type : "all";
    root["devs"]     = (devs.length()) ? devs : "all";
    root["key"]      = _key;
    string data = writer.write( root );
    res = curl_request_str(_WebService.c_str(), data.c_str(), response);
    if (res) {
        return res;
    }
    res = parseDownloadFilesResponse(response, files);
    if (res) {
        return res;
    }

#endif
    return res;
}

int ServerRequest::parseDownloadFilesResponse(string jsonTxt, vector <DownloadedFileProperties> &files)
{

#ifdef USE_CURL
    Json::Value root;
    Json::Reader reader;
    string url;
    //printf("response = %s\n", jsonTxt.c_str());
    bool rc = reader.parse(jsonTxt, root);
    if (!rc) {
        setError(rc, "-E- Failed To parse server response\n");
        return -1;
    }
    for (unsigned j = 0; j < root.size(); j++) {
        if (!root[j].isObject()) {
            setError(-1, "-E- Failed To parse server response\n");
            return -1;
        }
        string name         = "";
        string url          = "";
        string descr        = "";
        string release_note = "";
        string family       = "";
        string file_type    = "";
        string os           = "";
        try {
            Json::Value::Members profileNames = root[j].getMemberNames();
            for (unsigned i = 0; i < profileNames.size(); i++) {
                if (!profileNames[i].compare("URL")) {
                    url = root[j].get(profileNames[i], Json::nullValue).asString();
                    url = genertDownloadUrl(url);
                } else if (!profileNames[i].compare("Name")) {
                    name = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Family")) {
                    family = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Type")) {
                    file_type = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Descr")) {
                    descr = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("OS")) {
                    os = root[j].get(profileNames[i], Json::nullValue).asString();
                } else if (!profileNames[i].compare("Release_note")) {
                    release_note = root[j].get(profileNames[i], Json::nullValue).asString();
                }
            }
        } catch (runtime_error &e) {
            setError(-1, (string)"-E-" + e.what() + "\n");
            return -1;
        }
        DownloadedFileProperties file;
        file.url  = url;
        file.name = name;
        file.family = family;
        file.file_type = file_type;
        file.descr  = descr;
        file.os     = os;
        file.release_note = release_note;
        files.push_back(file);
    }
    if (!files.size()) {
        return -1;
    }
#endif
    return 0;
}

int ServerRequest::queryPsids(string psids, vector<PsidQueryItem> &results)
{

    int res = 0;

 #ifdef USE_CURL

    Json::Value root;
    Json::StyledWriter writer;
    string response  = "";
    root["psids"]    = psids;
    root["mode"]     = 3;   // 0 query
    root["key"]      = _key;
    string data = writer.write( root );
    //printf("request : %s\n", data.c_str());
    res = curl_request_str(_WebService.c_str(), data.c_str(), response);
    if (res) {
        return res;
    }

    //printf("Response : %s\n", response.c_str());
    res = parseQueryResponse(response, results, false);
    if (res) {
        return res;
    }

#endif
    return res;
}

int ServerRequest::updateMFAsRequest(vector<string> &psid_list,
                                     vector<dm_dev_id_t> &dev_types_list,
                                     vector<string> &fw_version_list,
                                     vector<PsidQueryItem> &results)
{
    int res = 0;
    (void) dev_types_list;
 #ifdef USE_CURL

    Json::Value root;
    Json::StyledWriter writer;
    string psids     = "";
    string devices   = "";
    string response  = "";
    string versions  = "";
    string tmp;
    for (unsigned i = 0; i < psid_list.size(); i++) {
        if (i > 0) {
            psids   += ",";
            devices += ",";
            versions += ",";
        }
        psids    += psid_list[i];
        versions += fw_version_list[i];
    }

    root["psids"]    = psids;
    root["devs"]     = devices;
    root["mode"]     = 0;   // 0 update
    root["versions"] = versions;
    root["key"]      = _key;
    string data = writer.write( root );
    //printf("request : %s\n", data.c_str());
    res = curl_request_str(_WebService.c_str(), data.c_str(), response);
    if (res) {
        return res;
    }

    //printf("Response : %s\n", response.c_str());
    res = parseQueryResponse(response, results);
    if (res) {
        return res;
    }

#endif
    return res;
}

string ServerRequest::genertDownloadUrl(string file_url)
{
    return _Url + "/" + file_url;
}


#if 0
int ServerRequest::queryAllMFAs(vector<string> &mfa_list)
{
    int res = 0;
    vector<string> psid_list;
    vector<dm_dev_id_t> dev_types_list;
    vector<string> fw_version_list;
    string response;
    mfa_list.clear();
    Json::Value root;
    Json::StyledWriter writer;
    root["psids"]    = "";
    root["devs"]     = "";
    root["mode"]     = 1;  // get all mfas;
    root["versions"] = "";
    root["key"]      = _key;

    string data = writer.write( root );
    res = curl_request_str(_WebService.c_str(), data.c_str(), response);
    if (res) {
        return res;
    }
    res = parseQueryAllMFAsRespone(response, mfa_list);
    return res;
}


int ServerRequest::parseQueryAllMFAsRespone(string jsonTxt, vector <string> &result)
{

    Json::Value root;
    Json::Reader reader;
    string url;
    bool rc = reader.parse(jsonTxt, root);
    if (!rc) {
        setError(rc, "-E- Failed To parse server response\n");
        //To be removed
        return rc;
    }
    for (unsigned j = 0; j < root.size(); j++) {
        if (root[j].isString()) {
            url = root[j].asString();
            result.push_back(_Url + url);
        }
    }
    return 0;
}
#endif

int ServerRequest::download(string url, string dest_path)
{
    int res = 0;
#ifdef USE_CURL
    ssize_t pos = url.rfind('/');
    string name = dest_path;
    name += "/";
    if (pos > 0) {
        string tmp = url.substr(pos);
        if (tmp.length() > 0) {
            name += tmp;
            res = curl_request(url.c_str(), NULL, name.c_str(), _numberOfRetrials);
        }
    }
#endif
    return res;
}


#ifdef USE_CURL
static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
#endif


int ServerRequest::curl_request(const char *url,
                                const char *data,
                                const char *dest_file,
                                int numOfRet)
{
    int res = 0;
#ifdef USE_CURL
    CURLcode rc;
    FILE *fp;
    CURL *_curl = curl_easy_init();
    if (_curl == NULL) {
        _LastErrorNo = ERR_SRVREQ_ACCESS_INIT;
        setError(-1, "-E- Server access error\n");
        return -1;
    }
    _LastErrorStr = "";
    fp = fopen(dest_file, "wb");
    if (fp == NULL && errno == EACCES) {
        unlink(dest_file);
        fp = fopen(dest_file, "wb");
    }
    if (fp == NULL) {
        setError(-1, "Failed to Open file for writing " + (string) strerror(errno) + "\n");
        return -1;
    }
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 360); // 6 minute operation timeout
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, 1);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, 60);
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_CAINFO, _ceritifcate.c_str());
    if (_show_progress) {
        // Internal CURL progressmeter must be disabled if we provide our own callback
        curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
        // Install the callback function
        curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, progress_func);
    }
    if (_Proxy.size() > 0) {
        curl_easy_setopt(_curl, CURLOPT_PROXY, _Proxy.c_str());
    }
    if (data != NULL) {
        curl_easy_setopt(_curl, CURLOPT_POST, 1);
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, data);
    }
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, true);

    // Perform the request, res will get the return code
    rc = curl_easy_perform(_curl);
    // Check for errors
    if (rc == CURLE_OPERATION_TIMEDOUT && numOfRet > 0) {
        if (curl_request(url, data, dest_file, numOfRet - 1) == 0) {
            rc = CURLE_OK;
        }
    }
    if (rc != CURLE_OK) {
        if ((rc == CURLE_OPERATION_TIMEDOUT && numOfRet == 0) ||
            (rc != CURLE_OPERATION_TIMEDOUT)) {
            setError(-1, (string)curl_easy_strerror(rc));
        }
        res = -1;
        goto clean_up;
    }

    res = 0;

clean_up:
    curl_easy_cleanup(_curl);
    curl_global_cleanup();
    fclose(fp);
    if (res) {
        unlink(dest_file);
    } else {
        #if !defined(__WIN__)
        string tmp = (string)dest_file;
        if (tmp.find(".mfa") == std::string::npos and tmp.find(".exe") == std::string::npos) {
            int retVal = my_chmod(dest_file, EXECUTABLE_MODE);
            (void) retVal;
        }
        #endif
    }
#endif
    return res;
}


#ifdef USE_CURL
static
size_t writebuf_data(void *ptr, size_t size, size_t nmemb, string *strm)
{
    size_t written = size * nmemb;
    char *str = new char[written + 1];
    if (str == NULL) {
        return 0;
    }
    strncpy(str, (char*)ptr, written);
    str[written] = 0;
    *strm += str;
    delete[] str;
    return written;
}
#endif


int ServerRequest::curl_request_str(const char *url, const char *data, string& response)
{
    int res = 0;
#ifdef USE_CURL

    CURL *_curl = curl_easy_init();
    if (_curl == NULL) {
        _LastErrorNo = ERR_SRVREQ_ACCESS_INIT;
        setError(-1, "-E- Server access error\n");
        return -1;
    }

    CURLcode rc;
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, writebuf_data);
    curl_easy_setopt(_curl, CURLOPT_CAINFO, _ceritifcate.c_str());

    _headers = curl_slist_append(_headers, "Accept: application/json");
    _headers = curl_slist_append(_headers, "Content-Type: application/json");
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _headers );
    curl_easy_setopt(_curl, CURLOPT_POST, 1);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDSIZE, strlen(data));
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, true);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE,1);
    //curl_easy_setopt(curl, CURLOPT_HEADER,1);

    // Perform the request, res will get the return code
    rc = curl_easy_perform(_curl);
    //fprintf(stderr, "Response : %s\n", response.c_str());
    // Check for errors
    if (rc != CURLE_OK) {
        setError(-1, "-E- " + (string)curl_easy_strerror(rc) + "\n");
        res = -1;
        goto clean_up;
    }
    res = 0;
clean_up:
    curl_easy_cleanup(_curl);
    curl_global_cleanup();
    curl_slist_free_all(_headers);

#endif
    return res;
}


int progress_func(void *ptr, double totalToDownload, double nowDownloaded,
                  double totalToUpload, double nowUploaded)
{
    (void) ptr;
    (void) totalToUpload;
    (void) nowUploaded;

    double fractionDownloaded = (nowDownloaded / totalToDownload) * 100;
    fractionDownloaded = fractionDownloaded > 0 ? fractionDownloaded : 0;
    printf("\b\b\b\b%3.0f%%", fractionDownloaded);

    fflush(stdout);
    return abort_request;
}
