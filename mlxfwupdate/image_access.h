
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

#ifndef __IMAGE_ACCESS_H__
#define __IMAGE_ACCESS_H__


#include <mlxfwops_com.h>
#include <fw_ops.h>
#include <compatibility.h>
#include "psid_query_item.h"
#include "mlxfwmanager_common.h"
#include "mlnx_dev.h"

using namespace std;
#define MLNX_ERR_BUFF_SIZE 1024
enum {
    IMG_SIG_TYPE_UNKNOWN = 0,
    IMG_SIG_TYPE_BIN = 1,
    IMG_SIG_TYPE_MFA = 2,
    IMG_SIG_TYPE_PLDM = 3
};

class ImageAccess {
public:
    ImageAccess(int compareFFV);
    ~ImageAccess();
    int queryDirPsid(string &path, string &psid, string &selector_tag, int image_type, vector<PsidQueryItem> &riv);
    int queryPsid(const string &fname, const string &psid, string &selector_tag, int image_type, PsidQueryItem &ri);
    int getImage(const string &fname, u_int8_t **filebuf);
    int getImage(const string &fname, const string &psid, string &selector_tag, int image_type, u_int8_t **filebuf);
    int get_file_content(const string & fname, vector<PsidQueryItem> &riv);
    static int getFileSignature(const string & fname);
    static bool hasMFAs(string dir);
    string getLastErrMsg();
    string getlastWarning();
    string getLog();

private:
    int queryPsidMfa(const string &fname, const string &psid, string &selector_tag, int image_type, PsidQueryItem &ri);
    int queryPsidBin(const string &fname, const string &psid, PsidQueryItem &ri);
    int getImageBin(const string &fname, u_int8_t **filebuf);
    int getImageMfa(const string &fname, const string &psid, string &selector_tag, int image_type, u_int8_t **filebuf);
    int checkImgSignature(const char *fname);

    int get_mfa_content(const string & fname, vector<PsidQueryItem> &riv);
    int get_pldm_content(const string & fname, vector<PsidQueryItem> &riv);
    int get_bin_content(const string & fname, vector<PsidQueryItem> &riv);
    bool extract_pldm_image_info(const u_int8_t * buff, u_int32_t size, PsidQueryItem &ri);
    static int getBufferSignature(u_int8_t *buf, u_int32_t size);
    bool openImg(fw_hndl_type_t hndlType, char *psid, char *fileHndl);
    char _errBuff[MLNX_ERR_BUFF_SIZE];
    int _compareFFV;
    string _log;
    string _errMsg;
    string _warning;
    FwOperations::fw_ops_params_t _imgFwParams;
    FwOperations *_imgFwOps;
};

#endif
