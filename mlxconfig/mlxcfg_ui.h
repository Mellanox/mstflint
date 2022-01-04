/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXCFG_UI_H_
#define MLXCFG_UI_H_

#include <string>

#include <compatibility.h>
#include <mtcr.h>

#include "mlxcfg_4thgen_commander.h"
//#include "mlxcfg_lib.h"
#include "mlxcfg_commander.h"
#include "mlxcfg_view.h"

#define DB_NAME ""

typedef enum {
    Mc_Set,
    Mc_Query,
    Mc_Reset,
    Mc_Clr_Sem,
    Mc_Set_Raw,
    Mc_Get_Raw,
    Mc_Backup,
    Mc_ShowConfs,
    Mc_GenTLVsFile,
    Mc_GenXMLTemplate,
    Mc_Raw2XML,
    Mc_XML2Raw,
    Mc_XML2Bin,
    Mc_CreateConf,
    Mc_Apply,
    Mc_RemoteTokenKeepAlive,
    Mc_ChallengeRequest,
    Mc_TokenSupported,
    Mc_QueryTokenSession,
    Mc_EndTokenSession,
    Mc_UnknownCmd
} mlxCfgCmd;

typedef enum {
    Mc_Token_RMCS = 0,
    Mc_Token_RMDT,
    Mc_Token_CRCS,
    Mc_Token_CRDT,
    Mc_Token_Unknown
} mlxCfgToken;

typedef enum {
    UNSUPPORTED_DEVICE = -1,
    HCA = 0,
    Switch = 1
} Device_Type;

typedef enum {
    KEEP_ALIVE_OK,
    KEEP_ALIVE_ERROR
} keepAliveStatus;

typedef struct QueryOutputItem {
    string mlxconfigName;
    u_int32_t nextVal;
    string strNextVal;
    u_int32_t currVal;
    string strCurrVal;
    u_int32_t defVal;
    string strDefVal;
    u_int32_t setVal;
    string strSetVal;
} QueryOutputItem;

using namespace std;

class MlxCfgParams
{
public:
    MlxCfgParams() : device(), rawTlvFile(), NVInputFile(), NVOutputFile(),
        dbName(DB_NAME), privPemFile(), keyPairUUID(), opensslEngine(),
        opensslKeyId(), allAttrs(false), cmd(Mc_UnknownCmd), yes(false),
        force(false), enableVerbosity(false), tokenID(Mc_Token_Unknown), sessionId(0), 
        isSessionIDGiven(false), sessionTimeInSec(600), isSessionTimeGiven(false), 
        keepAliveSleepTimeBetweenCommands(0), isSleepTimeBetweenCommandsInput(false), 
        keepAliveSleepTimeOnCommandTO(0), isSleepTimeOnCommandTOInput(false) {}

    ~MlxCfgParams() {}

    std::string device;
    Device_Type deviceType;
    std::string rawTlvFile;
    std::string NVInputFile;
    std::string NVOutputFile;
    std::string dbName;
    std::string privPemFile;
    std::string keyPairUUID;
    std::string opensslEngine;
    std::string opensslKeyId;
    bool allAttrs;
    mlxCfgCmd cmd;
    bool yes;
    std::vector<ParamView> setParams;
    bool force;// ignore parameter checks
    bool enableVerbosity;
    mlxCfgToken tokenID;
    u_int32_t sessionId;
    bool isSessionIDGiven;
    u_int32_t sessionTimeInSec;
    bool isSessionTimeGiven;
    u_int32_t keepAliveSleepTimeBetweenCommands;
    bool isSleepTimeBetweenCommandsInput;
    u_int32_t keepAliveSleepTimeOnCommandTO;
    bool isSleepTimeOnCommandTOInput;
};

class KeepAliveSession
{
public:
    KeepAliveSession(mfile *mf, u_int16_t sessionId, u_int32_t sessionTimeInSec);

    keepAliveStatus runSession();
    void setSleepTimeOnCommandTO(u_int32_t sleepTime);
    void setSleepTimeBetweenCommands(u_int32_t sleepTime);

private:
    keepAliveStatus runMKDC(mfile* mf, reg_access_switch_mkdc_reg_ext* mkdc_reg, time_t& timer);
    keepAliveStatus processMKDCData(reg_access_switch_mkdc_reg_ext* mkdc_reg);
    keepAliveStatus err(bool report, const char *fmt, ...);

    static const char* _mkdcErrorToString[5];

    static const u_int32_t _keepAliveTimestampInSec;

    mfile* _mf;
    u_int16_t _sessionId;
    u_int32_t _sessionTimeLeftInSec;
    reg_access_switch_mkdc_reg_ext _mkdc_reg;
    u_int32_t _SleepTimeOnCommandTO;
    u_int32_t _SleepTimeBetweenCommands;
};

class MlxCfg
{
public:
    MlxCfg() : _mlxParams(), _errStr(), _allInfo(), _devType(DeviceUnknown) {}
    ~MlxCfg() {};
    mlxCfgStatus execute(int argc, char *argv[]);
private:

    // User interface and parsing methods
    void printHelp();
    mlxCfgStatus showDevConfs();
    void printVersion();
    void printUsage();
    void printOpening(const char *dev, int devIndex);
    void printConfHeader(bool showDefualt, bool showNew, bool showCurrent);
    Device_Type getDeviceTypeFromString(string inStr);
    mlxCfgStatus getNumberFromString(const char* str, u_int32_t& num);
    mlxCfgStatus parseArgs(int argc, char *argv[]);
    //Helper functions for parse args
    mlxCfgStatus extractNVInputFile(int argc, char *argv[]);
    mlxCfgStatus extractNVOutputFile(int argc, char *argv[]);
    mlxCfgStatus extractSetCfgArgs(int argc, char *argv[]);
    mlxCfgStatus extractQueryCfgArgs(int argc, char *argv[]);

    void removeContinuanceArray(std::vector<QueryOutputItem>& OutputItemOut, std::vector<QueryOutputItem>& OutputItemIn);
    void editAndPushItem(std::vector<QueryOutputItem>& queryOutputItemVector, QueryOutputItem& item, u_int32_t arrayIndex);

    const char * getConfigWarning(const string & mlx_config_name,
            const string & set_val);

    bool tagExsists(string tag);
    const char* getDeviceName(const char *dev);

    // Query cmd
    mlxCfgStatus queryDevsCfg();
    mlxCfgStatus queryDevCfg(const char *dev, const char *pci = (const char*)NULL, int devIndex = 1, bool printNewCfg = false);
    mlxCfgStatus queryDevCfg(Commander *commander, const char *dev, const char *pci = (const char*)NULL, int devIndex = 1, bool printNewCfg = false);

    // Set cmd
    mlxCfgStatus setDevCfg();
    // reset Cmd
    mlxCfgStatus resetDevsCfg();
    mlxCfgStatus resetDevCfg(const char *dev);
    // Set\Get Raw TLV file
    mlxCfgStatus devRawCfg(RawTlvMode mode);
    mlxCfgStatus backupCfg();
    mlxCfgStatus tlvLine2DwVec(const std::string& tlvStringLine, std::vector<u_int32_t>& tlvVec);

    mlxCfgStatus clrDevSem();

    mlxCfgStatus readBinFile(string fileName, vector<u_int32_t>& buff);
    mlxCfgStatus readNVInputFile(vector<u_int32_t>& buff);
    mlxCfgStatus readNVInputFile(string& content);
    mlxCfgStatus readNVInputFile(vector<string>& lines);

    mlxCfgStatus writeNVOutputFile(vector<u_int32_t> content);
    mlxCfgStatus writeNVOutputFile(string content);
    mlxCfgStatus writeNVOutputFile(vector<string> lines);

    mlxCfgStatus genTLVsFile();
    mlxCfgStatus genXMLTemplate();
    mlxCfgStatus raw2XMLAux(bool isBin);
    mlxCfgStatus raw2XML();
    mlxCfgStatus XML2RawAux(bool isBin);
    mlxCfgStatus XML2Raw();
    mlxCfgStatus XML2Bin();
    mlxCfgStatus createConf();
    mlxCfgStatus apply();

    mlxCfgStatus remoteTokenKeepAlive();
    mlxCfgStatus getChallenge();
    mlxCfgStatus queryTokenSupport();
    mlxCfgStatus queryTokenSession();
    mlxCfgStatus endTokenSession();
    void processMDSRData(const struct reg_access_switch_mdsr_reg_ext& mdsr_reg, bool isQuery);
    bool runMDSR(mfile* mf, struct reg_access_switch_mdsr_reg_ext* mdsr_reg, reg_access_method_t method);
    bool runMTCQ(mfile* mf, struct reg_access_switch_mtcq_reg_ext* mtcq_reg);
    void printArray(const u_int32_t arr[], int len);
    void printHexArrayAsAscii(const u_int32_t arr[], int len);
    mlxCfgToken getTokenType(const char* tokenStr);

    // static print functions
    static int printParam(string param, u_int32_t val);
    static int printValue(string strVal, u_int32_t val);
    static void printSingleParam(const char *name,
            QueryOutputItem & queryOutItem, u_int8_t verbose, bool printNewCfg);


    bool askUser(const char *question, bool add_prefix=true, bool add_suffix=true);
    mlxCfgStatus err(bool report, const char *errMsg, ...);
    void printErr();
    // data members
    MlxCfgParams _mlxParams;
    std::string _errStr;
    MlxCfgAllInfo _allInfo;
    dm_dev_id_t _devType;

};

#endif /* MLXCFG_UI_H_ */
