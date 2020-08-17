
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
#include "mlxfwmanager_common.h"

#if defined(__WIN__)
const char* SafeGetEnv(const char *var)
{
    char *val = getenv(var);
    if (val == NULL) {
        return ".";                 //Local dir
    }
    return val;
}
#endif

int mapRetValue(int rc, mlxFWMSetupType::T setupType)
{
    map<int, int> lvim;
    lvim[ERR_CODE_NO_DEVICES_FOUND] = 171;

    map<int, int> dl;
    dl[ERR_CODE_NO_DEVICES_FOUND] = 0;
    switch (setupType) {
    case mlxFWMSetupType::lvim:
        if (lvim.find(rc) != lvim.end() ) {
            return lvim[rc];
        }
        break;

    case mlxFWMSetupType::dl:
        if (dl.find(rc) != dl.end() ) {
            return dl[rc];
        }
        break;

    default:
        return rc;
    }
    return rc;
}
string beautify_device_name(string family)
{
    if (family == "connectx") {
        return "ConnectX";
    } else if (family == "connect-ib") {
        return "Connect-IB";
    } else if (family == "connectx-4") {
        return "ConnectX-4";
    } else {
        return family;
    }
}


int CreateTempDir(string tempDir, string& tempBaseDir)
{
    int rc = 0;
    string templ;
    const int len = 512;
    char tmpstr[len] = {0};


    #ifdef __WIN__
    int size;
    int pid;
    templ = tempDir;

    size = sizeof(tmpstr);
    if (!GetUserName((LPTSTR)tmpstr, (LPDWORD)&size)) {
        fprintf(stderr, "-E- Failed to get username\n");
        return -1;
    }
    templ += tmpstr;

    pid = _getpid();
    sprintf(tmpstr, "_%d", pid);
    templ += tmpstr;

    FixPath(templ);
    rc = ForceMkDir(templ);
    if (rc != 0) {
        fprintf(stderr, "-E- Failed to create temporary directory %s: %s\n", templ.c_str(), strerror(rc));
        return -1;
    }
    #else
    char *temp;
    tempDir += "XXXXXX";
    strncpy(tmpstr, tempDir.c_str(), len - 1);
    temp = mkdtemp(tmpstr);
    if (temp == NULL) {
        fprintf(stderr, "-E- Failed to create temporary directory\n");
        return -1;
    }
    templ = tmpstr;
    #endif

    tempBaseDir = templ;
    return rc;
}

int RemoveDir(const string &dir)
{
    string rmdirCmd;

    #ifdef __WIN__
    rmdirCmd = "rd /s /q \"";
    rmdirCmd += dir;
    rmdirCmd += "\"";
    #else
    if ((dir == "/") || (dir == "")) {
        return 0;
    }
    rmdirCmd = "rm -rf ";
    rmdirCmd += dir;
    #endif
    return system(rmdirCmd.c_str());
}

int MkDir(const string dir)
{
    int rc;
    #ifdef __WIN__
    rc = mkdir(dir.c_str());
    #else
    rc = mkdir(dir.c_str(), 0777);
    #endif
    if (rc) {
        rc = errno;
    }
    return rc;
}

#ifdef __WIN__

void FixPath(string &s)
{
    #ifdef __WIN__
    size_t pos;
    while ((pos = s.find('/')) != string::npos) {
        s.replace( pos, 1, "\\");
    }
    #else
    (void)s;
    #endif
}

int ForceMkDir(const string dir)
{
    int rc = MkDir(dir);
    if (rc != 0) {
        if (rc == EEXIST) {
            RemoveDir(dir);
            rc = MkDir(dir);
        } else {
            return rc;
        }
    }
    return rc;
}

int mlxfw_replace(char *st, char *orig, char *repl)
{
    char buffer[1024];
    char *ch;

    if (!(ch = strstr(st, orig))) {
        return 0;
    }
    strncpy(buffer, st, ch - st);
    buffer[ch - st] = 0;
    sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
    strcpy(st, buffer);

    return 0;
}

int mlxfw_get_exec_name_from_path(char *str, char *exec_name)
{
    char tmp_str[strlen(str) + 1];
    char *pch;
    strcpy(tmp_str, str);
    pch = strtok(tmp_str, "\\");
    while (pch != NULL) {
        strcpy(exec_name, pch);
        pch = strtok(NULL, "\\");
    }
    return 0;
}

#endif

bool unzipDataFile(std::vector<u_int8_t> data,
                   std::vector<u_int8_t> &newData,
                   const char *sectionName)
{
#ifndef NO_ZLIB
    int rc;
    if (data.empty()) {
        return false;
    }
    // restore endianess.
    TOCPUn(&(data[0]), data.size() / 4);

    // uncompress:
    uLongf destLen = data.size();
    destLen *= 40; // Assuming this is the best compression ratio
    vector<u_int8_t> dest(destLen);

    for (int i = 0; i < 32; i++) {
        rc = uncompress((Bytef*)&(dest[0]), &destLen,
                        (const Bytef*)&(data[0]), data.size());
        if (rc != Z_BUF_ERROR) {
            break;
        }
        destLen *= 2;
        dest.resize(destLen);
    }

    if (rc != Z_OK) {
        return false;
    }
    // printf("%s", (char*)&(dest[0]));

    newData = dest;
    newData[destLen] = 0; // Terminating NULL
    newData.resize(destLen + 1);
    (void) sectionName;
    return true;
#else
    // avoid warnings
    (void) data;
    (void) newData;
    (void) sectionName;
    return false;
#endif
}

#ifdef __WIN__
int my_chmod(const char *path, mode_t mode)
{

    int result = _chmod(path, (mode & MS_MODE_MASK));

    if (result != 0) {
        result = errno;
    }
    return (result);
}
#else
int my_chmod(const char *path, mode_t mode)
{
    int result = chmod(path, mode);

    if (result != 0) {
        result = errno;
    }
    return (result);
}
#endif

string getErrStr(int rc)
{
    map<int, string> err_msg;
    err_msg[MLX_FWM_SUCCESS] =  "";
    err_msg[ERR_CODE_QUERY_FAILED] = ERR_MSG_QUERY_FAILED;
    err_msg[ERR_CODE_PROG_FAILED] = ERR_MSG_PROG_FAILED;
    err_msg[ERR_CODE_BAD_CMD_ARGS] = ERR_MSG_BAD_CMD_ARGS;
    err_msg[ERR_CODE_CREATE_LOG_FAIL] = ERR_MSG_CREATE_LOG_FAIL;
    err_msg[ERR_CODE_FETCH_LOCAL_DEVICES_FAIL] = ERR_MSG_FETCH_LOCAL_DEVICES_FAIL;
    err_msg[ERR_CODE_SERVER_DOWNLOAD_FAILED] = ERR_MSG_SERVER_DOWNLOAD_FAILED;
    err_msg[ERR_CODE_MEM_ALLOC_FAIL] = ERR_MSG_MEM_ALLOC_FAIL;
    err_msg[ERR_CODE_INTERNAL_ERR] = ERR_MSG_INTERNAL_ERR;
    err_msg[ERR_CODE_IMG_NOT_FOUND] = ERR_MSG_IMG_NOT_FOUND;
    err_msg[ERR_CODE_CREATE_OUTPUT_FILE_FAIL] = ERR_MSG_CREATE_OUTPUT_FILE_FAIL;
    err_msg[ERR_CODE_MULTI_IMG_SRC_FOUND] = ERR_MSG_MULTI_IMG_SRC_FOUND;
    err_msg[ERR_CODE_BAD_INI_FILE] = ERR_MSG_BAD_INI_FILE;
    err_msg[ERR_CODE_SERVER_RETRIEVE_FAIL] = ERR_MSG_SERVER_RETRIEVE_FAIL;
    err_msg[ERR_CODE_WRITE_FILE_FAIL] = ERR_MSG_WRITE_FILE_FAIL;
    err_msg[ERR_CODE_EXTRACT_IMAGE_FAIL] = ERR_MSG_EXTRACT_IMAGE_FAIL;
    err_msg[ERR_CODE_MIXED_VERSIONS_FOUND] = ERR_MSG_MIXED_VERSIONS_FOUND;
    err_msg[ERR_CODE_FILE_PARSE_FAILED] = ERR_MSG_FILE_PARSE_FAILED;
    err_msg[ERR_CODE_INTERRUPTED] = ERR_MSG_INTERRUPTED;
    err_msg[ERR_CODE_NOT_ROOT] = ERR_MSG_NOT_ROOT;
    err_msg[ERR_CODE_NO_DEVICES_FOUND] = ERR_MSG_NO_DEVICES_FOUND;
    err_msg[ERR_CODE_NO_DEVICES_FOUND_LVIM] = ERR_MSG_NO_DEVICES_FOUND;
    err_msg[ERR_CODE_CLEAR_SEMAPORE] = ERR_MSG_CLEAR_SEMAPORE;
    err_msg[ERR_CODE_UNKNOWN_EXPANSION_ROM] = ERR_MSG_UNKNOWN_EXPANSION_ROM;
    err_msg[ERR_CODE_UNSUPPORTED_DEVICE] = ERR_MSG_UNSUPPORTED_DEVICE;
    err_msg[ERR_CODE_ONLINE_UPDATE_CONNECTION_ERROR] = ERR_MSG_ONLINE_UPDATE_CONNECTION_ERROR;
    err_msg[ERR_CODE_ONLINE_UPDATE_INTERNAL_ERR] = ERR_MSG_ONLINE_UPDATE_INTERNAL_ERR;
    err_msg[ERR_CODE_INVALID_CHOICE] = ERR_MSG_IVALID_CHOICE;
    err_msg[ERR_CODE_NONE_FAIL_SAFE] = ERR_MSG_NONE_FAIL_SAFE;
    err_msg[ERR_CODE_SERVER_QUERY_FAILED] = ERR_MSG_SERVER_QUERY;
    if (err_msg.find(rc) != err_msg.end()) {
        return err_msg[rc];
    }
    return "Unknown error";
}
