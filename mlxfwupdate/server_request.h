
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

#ifndef __SERVER_REQUEST_H__
#define __SERVER_REQUEST_H__

#include <math.h>
#include <vector>
#include <tools_dev_types.h>
#include "psid_query_item.h"
#include "mlxfwmanager_common.h"
#ifdef USE_CURL
#include <json/reader.h>
#include <json/writer.h>
#include <curl/curl.h>
#include <string.h>
#endif

#if defined(__WIN__)
#define EXECUTABLE_MODE 0xFFFF
#else
#define EXECUTABLE_MODE 777
#endif

using namespace std;

enum {
    ERR_SRVREQ_ACCESS_INIT = 1,
};

#define URL_TAG       "url"
#define FILE_NAME_TAG "name"
#define ERR_MSG_TAG   "err_msg"
#define ERR_NUM_TAG   "err_num"

int    progress_func(void *ptr, double TotalToDownload,
                     double NowDownloaded, double TotalToUpload,
                     double NowUploaded);

class ServerRequest {
public:
    ServerRequest(const char *url, const char *proxy,
                  int compare_ffv, bool show_progress, string key,
                  string certificate,
                  unsigned int numberOfRetrials);
    ~ServerRequest();
    int updateMFAsRequest(vector<string> &psid_list,
                          vector<dm_dev_id_t> &dev_types_list,
                          vector<string> &fw_version_list,
                          vector<PsidQueryItem> &results);
//        int queryAllMFAs(vector<string> &mfa_list);
    int DownloadFilesRequest(vector <DownloadedFileProperties> &files,
                             string os, string devs, string type);

    int queryPsids(string psids, vector<PsidQueryItem> &results);
    int download(string url, string dest_path);
    void getError(int &error, string &error_msg);
    inline void setNumberOfTrials(unsigned int num) {_numberOfRetrials = num;};
private:
    void setError(int error, string error_msg);
    int  parseQueryResponse(string jsonTxt, vector<PsidQueryItem> &results, bool ignoreNotFound = true);
//        int  parseQueryAllMFAsRespone(string jsonTxt, vector <string>&result);
    int  parseDownloadFilesResponse(string jsonTxt, vector <DownloadedFileProperties> &files);

    int curl_request(const char *url, const char *data, const char *dest_file, int numOfRet);
    int curl_request_str(const char *url, const char *data, string& response);
    string genertDownloadUrl(string file_url);
private:
    string _Url;
    string _WebService;
    string _Proxy;
    int _UseProxy;

    int _LastErrorNo;
    string _LastErrorStr;
    int _compare_ffv;
    bool _show_progress;
    string _key;
    string _ceritifcate;
    unsigned int _numberOfRetrials;
    #ifdef USE_CURL
    static CURL *_curl;
    struct curl_slist *_headers;
    #endif
};

#endif
