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




#ifndef __MLXFWMANAGER_COMMON_H__
#define __MLXFWMANAGER_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <map>
#include <iomanip>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <tools_dev_types.h>
#include <mlxfwops.h>
#include <mlxfwops_com.h>
#include <fs_checks.h>
#include <mflash.h>
#include <fw_ops.h>
#include <sys/types.h>
#include "err_msgs.h"

#ifndef NO_ZLIB
    #include <zlib.h>
#endif


#if defined(__WIN__)
#include <process.h>
#include <io.h>
const char* SafeGetEnv(const char *var);
#define TMP_DIR SafeGetEnv("TEMP")
#define PATH_SEPARATOR "\\"
#define GetCurrDir(sz, buf) GetCurrentDirectory(sz, buf)
#else
#define TMP_DIR  "/tmp"
#define PATH_SEPARATOR "/"
#define GetCurrDir(sz, buf) getcwd(buf, sz)
#endif


using namespace std;

inline string getLogDir(string toolName)
{
    #if defined(__WIN__)
    (void)toolName;
    return TMP_DIR;
    #else
    return (string) "/tmp/" + toolName + "_workdir";
    #endif
}
namespace mlxFWMSetupType {
enum T {normal, lvim, dl};
};

inline string int_to_string(int num)
{
    std::stringstream out;
    out << num;
    return out.str();
}

string getErrStr(int rc);
int    mapRetValue(int rc, mlxFWMSetupType::T setupType);
string beautify_device_name(string family);
int    CreateTempDir(string tempDir, string& tempBaseDir);
int    my_chmod(const char *path, mode_t mode);
int    RemoveDir(const string &dir);

bool   unzipDataFile(std::vector<u_int8_t> data,
                     std::vector<u_int8_t> &newData, const char *sectionName);
int  MkDir(const string dir);

#if defined(__WIN__)
int  ForceMkDir(const string dir);
void FixPath(string &s);
int mlxfw_replace(char *st, char *orig, char *repl);
int mlxfw_get_exec_name_from_path(char *str, char *exec_name);
    #define mlxfw_MTCR_DLL_NAME "libmtcr-1.dll"
static const mode_t MS_MODE_MASK = 0x0000ffff;
#endif

class DownloadedFileProperties {
public:
    string url;
    string name;
    string descr;
    string release_note;
    string family;
    string file_type; // mfa or self extractor
    string os;
};

#endif

