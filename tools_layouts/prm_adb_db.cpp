/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 *
 * prm_adb_db.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: diaedinrim
 */

#include <stdio.h>
#include <stdarg.h>
#include "prm_adb_db.h"
#include "compatibility.h"
using namespace std;

string PrmAdbDB::prm_adb_db_ltrim(const string& s)
{
    const char* cs = s.c_str();

    while (isspace(*cs)) {
        cs++;
    }
    return string(cs);
}

string PrmAdbDB::prm_adb_db_rtrim(const string& s)
{
    /* todo rewrite it */
    unsigned int i = s.size();

    if (i == 0) {
        return s;
    }
    while (--i > 0 && isspace(s[i])) {
        ;
    }
    if ((i == 0) && isspace(s[i])) {
        return "";
    }
    return s.substr(0, i + 1);
}

string PrmAdbDB::prm_adb_db_trim(const string& s)
{
    return prm_adb_db_rtrim(prm_adb_db_ltrim(s));
}

string PrmAdbDB::getDefaultDBName(dm_dev_id_t devID)
{
    PrmAdbType_t adbType = (dm_is_gpu(devID) ? PrmAdbType_t::PRM_ADB_TYPE_GPU :
                                               (dm_dev_is_retimer(devID) ? PrmAdbType_t::PRM_ADB_TYPE_RETIMER :
                                                dm_dev_is_switch(devID)  ? PrmAdbType_t::PRM_ADB_TYPE_SWITCH :
                                                                           PrmAdbType_t::PRM_ADB_TYPE_HCA));
    return getDefaultDBName(adbType);
}

string PrmAdbDB::getDefaultDBName(PrmAdbType_t adbType)
{
    const string dbDirName = "prm_dbs";
    const string dbFileName = "register_access_table.adb";
    string adbTypeStr;
    switch (adbType)
    {
        case PrmAdbType_t::PRM_ADB_TYPE_HCA:
            adbTypeStr = "hca";
            break;
        case PrmAdbType_t::PRM_ADB_TYPE_SWITCH:
            adbTypeStr = "switch";
            break;
        case PrmAdbType_t::PRM_ADB_TYPE_RETIMER:
            adbTypeStr = "retimers";
            break;
        case PrmAdbType_t::PRM_ADB_TYPE_GPU:
            adbTypeStr = "gpu";
            break;
        case PrmAdbType_t::PRM_ADB_TYPE_UNKNOWN:
        default:
            throw PrmDBException("Unknown ADB type");
    }

    string       dbPathName = "";

#ifdef __WIN__
    char execFilePathCStr[1024] = {0x0};
    GetModuleFileName(GetModuleHandle("libmtcr-1.dll"), execFilePathCStr, 1024);
    dbPathName = execFilePathCStr;
    dbPathName = dbPathName.substr(0, dbPathName.rfind("\\") + 1);
    dbPathName += dbDirName + "\\" + adbTypeStr + "\\ext\\" + dbFileName;
#elif defined MST_UL
    dbPathName = DATA_PATH "/" + dbDirName + "/" + adbTypeStr + "/ext/" + dbFileName;
#else
    char   line[1024] = {0};
    string confFile = string(ROOT_PATH) + string("etc/mft/mft.conf");
    FILE * fd = fopen(confFile.c_str(), "r");
    if (!fd) {
        throw PrmDBException("Failed to open conf file : %s\n", confFile.c_str());
    }
    string prefix = "", dataPath = "";
    while ((fgets(line, 1024, fd))) {
        string l = line;
        if (l.find(dbDirName) != string::npos) {
            size_t eqPos = l.find("=");
            if (eqPos != string::npos) {
                dataPath = l.substr(eqPos + 1);
                dataPath = prm_adb_db_trim(dataPath);
            }
        } else if (l.find("mft_prefix_location") != string::npos) {
            size_t eqPos = l.find("=");
            if (eqPos != string::npos) {
                prefix = l.substr(eqPos + 1);
                prefix = prm_adb_db_trim(prefix);
            }
        }
    }
    if (!prefix.empty() && !dataPath.empty()) {
        dbPathName = prefix + dataPath + "/" + adbTypeStr + "/ext/" + dbFileName;
    }
    fclose(fd);
#endif
    return dbPathName;
}

/*************************** PrmDBException Implementation ***************************/

PrmDBException::PrmDBException()
{
}

/**
 * Function: PrmDBException::PrmDBException
 **/
PrmDBException::PrmDBException(const char* fmt, ...)
{
    char    tmp[1024];
    va_list args;

    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _msg = tmp;
}

/**
 * Function: PrmDBException::PrmDBException
 **/
PrmDBException::PrmDBException(string msg) : _msg(msg)
{
}

/**
 * Function: PrmDBException::~PrmDBException
 **/
PrmDBException::~PrmDBException() throw()
{
}

/**
 * Function: PrmDBException::what
 **/
const char* PrmDBException::what() const throw()
{
    return _msg.c_str();
}

/**
 * Function: PrmDBException::what_s
 **/
string PrmDBException::what_s() const
{
    return _msg;
}
