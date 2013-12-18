/*
 *
 * flint.cpp - FLash INTerface
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id$
 *
 */

#ifndef MLXCONFIG_H
#define MLXCONFIG_H
#include <iostream>
#include <map>
#include "flint_ops.h"

using namespace std;

/**************************** Forward Declarations *************************/
class Flash;
class Operations;
struct node_format;
struct field_format;

#define OLD_MLXCONFIG_VERSION 1
#define ERASE_CMD             "r"
/**************************** Tlv/Profile private helper structs *************************/
typedef struct
{
    string key;
    string value;

    // For debug only
    void print();
} Pair;

typedef struct
{
    string          name;
    vector<Pair>    fields;

    // For debug only
    void print();

} Tlv;

typedef struct
{
    u_int32_t       version;
    u_int32_t       id;
    vector<Tlv>     tlvs;

    // For debug only
    void print();
} Profile;

/**************************** MlxConfig Class *************************/
class AdbInstance;
class Adb;

class MlxConfig
{
public:
    enum {CMD_SET = 0, CMD_QUERY, CMD_RESTORE, CMD_LIST_PROFILES,
          CMD_RECONFIG, CMD_HELP, CMD_CONFIG_INFO, CMT_VERIFY, CMD_UNKNOWN};
    static const u_int32_t CFG_SIGNATURE = 0x4d544346;
    static const u_int32_t CFG_INVALID_SIGNATURE = 0;
    static const u_int32_t MLX_CFG_VERSION = 2;
    static const u_int32_t LAST_TLV_ID    = 0xffff;
    static const u_int16_t CUSTOM_PROFILE_ID = 0xffff;

    MlxConfig();
    ~MlxConfig();

    bool checkFwCfgCompat(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool setCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, string profileName, bool silent = false);
    bool queryCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool eraseCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool listProfilesCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool reconfigureCfg(Flash* flash, Operations* op, Operations::ImageInfo &newImageInfo);  // For flint use post-burn
    bool verifyCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, bool silent = false);
    bool setNonFailSafeCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo); // For flint use pre-burn
    bool queryProfile(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo,
                      u_int32_t &profileID, string &profileName); // For flint use
    bool configInfo(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool isConfigPresent(Flash* flash, Operations* op,
                         Operations::ImageInfo &flashImageInfo,
                         bool &presents, u_int32_t &configVer); // For flint use
    bool checkExistProfileCompat(Flash* flash, Operations* op,
                                 Operations::ImageInfo &flashImageInfo,
                                 Operations::ImageInfo &newImageInfo,
                                 bool &compat); // For flint use

    // run one of the "setCfg" "queryCfg" "eraseCfg" "listProfilesCfg" using cmdline API
    bool execute(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo, int argc, const char** argv);

    string getLastError() const;
    static const char* getHelpMessage();
    static const char* getRunExamples();

private:
    bool parseCmdLine(int argc, const char** argv);
    bool loadImageData(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool parseProfileDb(const string &jsonTxt);
    bool checkOldFW(Operations::ImageInfo &flashImageInfo);

    // Helpers
    bool getActiveCfgIdx(Flash* flash, int& idx); // -1 means no active configuration

    enum TlvHeaderField
    {
        TLV_HEADER_LENGTH, TLV_HEADER_ID,
        TLV_HEADER_CRC, TLV_HEADER_VERSION
    };
    void setTlvHeader(u_int8_t* buf, enum TlvHeaderField field, u_int32_t value);
    u_int32_t getTlvHeader(u_int8_t* buf, enum TlvHeaderField field);

    enum CfgHeaderField
    {
        CFG_HEADER_SIGNATURE, CFG_HEADER_MAX_LEN,
        CFG_HEADER_VERSION, CFG_HEADER_PROFILE_ID,
        CFG_HEADER_PROFILE_VER, CFG_HEADER_CRC
    };
    void setCfgSectionHeader(u_int8_t* buf, enum CfgHeaderField field, u_int32_t value);
    u_int32_t getCfgSectionHeader(u_int8_t* buf, enum CfgHeaderField);

    u_int16_t calcBECrc16(const u_int32_t* buf, int num_of_dwords);
    AdbInstance* getTlvById(int id);
    bool getTlvNodeId(AdbInstance* tlvNode, int &tlvId);
    bool getTlvVersion(AdbInstance* tlvNode, int &version);
    bool getFieldIntValue(string strVal, AdbInstance* field, u_int64_t &intVal);
    string findProfileById(u_int32_t profileID);
    bool crcVerify(u_int32_t startAddr, u_int32_t size, string title,
                        u_int32_t crc, u_int32_t expectedCrc, bool silent = false);
    // For debug only
    void printProfileDB();

private:
    string _lastMsg;
    int         _cmd;
    string      _cmdProfile;
    string      _cfgFile;
    string      _profilesFile;
    bool        _verbose;

    u_int32_t           _cfgAddress[2]; // index is image index
    u_int32_t           _cfgSize; // Cfg section size
    bool                _isFailSafe;
    string              _profilesJson; // Contents
    Adb*                _adbDB;
    AdbInstance*        _adbRoot;
    AdbInstance*        _adbTlvHeader;
    AdbInstance*        _adbCfgHeader;
    map<string, Profile> _profilesMap;
};

#endif // MLXCONFIG_H
