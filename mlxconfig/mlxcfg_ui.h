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
 */

#ifndef MLXCFG_UI_H_
#define MLXCFG_UI_H_

#include <string>

#include <compatibility.h>
#include <mtcr.h>
#include <json/reader.h>
#include <json/writer.h>

// #include "mlxcfg_lib.h"
#include "mlxcfg_commander.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_ui_tokens.h"

#define MAX_ERR_STR_LEN 1024
#define MAX_BUF_SIZE 1024
#define PRE_ERR_MSG "-E-"
#define MLNX_RAW_TLV_FILE_SIG "MLNX_RAW_TLV_FILE"

#ifdef MST_UL
#define NO_DEV_ERR "No devices found."
#else
#define NO_DEV_ERR "No devices found, mst might be stopped. You may need to run 'mst start' to load MST modules. "
#endif

#define DB_NAME ""

typedef enum
{
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

typedef struct QueryOutputItem
{
    string mlxconfigName;
    bool isReadOnly;
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
    MlxCfgParams() :
        device(),
        deviceType(UNSUPPORTED_DEVICE),
        rawTlvFile(),
        NVInputFile(),
        NVOutputFile(),
        dbName(DB_NAME),
        privPemFile(),
        keyPairUUID(),
        allAttrs(false),
        userHostIdParam(0),
        userPfIndexParam(0),
        userHostIdPfValid(false),
        completeSetWithDefault(false),
        cmd(Mc_UnknownCmd),
        isJsonOutputRequested(false),
        yes(false),
        force(false),
        enableVerbosity(false),
        tokenName(""),
        tokenChallengeID(McTokenTypeUnknown),
        tokenStatusID(McTokenStatusTypeCS),
        sessionId(0),
        isSessionIDGiven(false),
        sessionTimeInSec(60 * 60 * 24 * 7), // default session time is a week
        isSessionTimeGiven(false),
        keepAliveSleepTimeBetweenCommands(0),
        isSleepTimeBetweenCommandsInput(false),
        keepAliveSleepTimeOnCommandTO(0),
        isSleepTimeOnCommandTOInput(false)
    {
    }

    ~MlxCfgParams() {}

    std::string device;
    Device_Type deviceType;
    std::string rawTlvFile;
    std::string NVInputFile;
    std::string NVOutputFile;
    std::string dbName;
    std::string privPemFile;
    std::string keyPairUUID;
    bool allAttrs;
    u_int8_t userHostIdParam;
    u_int8_t userPfIndexParam;
    bool userHostIdPfValid;
    bool completeSetWithDefault;
    mlxCfgCmd cmd;
    bool isJsonOutputRequested;
    bool yes;
    std::vector<ParamView> setParams;
    bool force; // ignore parameter checks
    bool enableVerbosity;
    string tokenName;
    MlxCfgTokenType tokenChallengeID;
    MlxCfgTokenStatusType tokenStatusID;
    u_int32_t sessionId;
    bool isSessionIDGiven;
    u_int32_t sessionTimeInSec;
    bool isSessionTimeGiven;
    u_int32_t keepAliveSleepTimeBetweenCommands;
    bool isSleepTimeBetweenCommandsInput;
    u_int32_t keepAliveSleepTimeOnCommandTO;
    bool isSleepTimeOnCommandTOInput;
};

class MlxCfg
{
public:
    MlxCfg() : _mlxParams(), _errStr(), _devType(DeviceUnknown) {}
    ~MlxCfg(){};
    mlxCfgStatus execute(int argc, char* argv[]);

private:
    // User interface and parsing methods
    void printHelp();
    mlxCfgStatus showDevConfs();
    const char* getDeviceName(mfile* mf);
    void printVersion();
    void printUsage();
    void printOpening(mfile* mf, const char* dev, string deviceIndex, Json::Value& oJsonValue);
    void printConfHeader(bool showDefualt, bool showNew, bool showCurrent);
    mlxCfgStatus getNumberFromString(const char* str, u_int32_t& num);
    mlxCfgStatus parseArgs(int argc, char* argv[]);
    // Helper functions for parse args
    mlxCfgStatus extractNVInputFile(int argc, char* argv[]);
    mlxCfgStatus extractNVOutputFile(int argc, char* argv[]);
    mlxCfgStatus extractSetCfgArgs(int argc, char* argv[]);
    mlxCfgStatus extractQueryCfgArgs(int argc, char* argv[]);

    void removeContinuanceArray(std::vector<QueryOutputItem>& OutputItemOut,
                                std::vector<QueryOutputItem>& OutputItemIn);
    void
      editAndPushItem(std::vector<QueryOutputItem>& queryOutputItemVector, QueryOutputItem& item, u_int32_t arrayIndex);

    const char* getConfigWarning(const string& mlx_config_name, const string& set_val);

    bool tagExsists(string tag);

    // Query cmd
    mlxCfgStatus queryDevsCfg();
    mlxCfgStatus
      queryDevCfg(const char* dev, const char* pci = (const char*)NULL, int devIndex = 1, bool printNewCfg = false);
    mlxCfgStatus queryDevCfg(Commander* commander,
                             const char* dev,
                             bool isWriteOperation,
                             const char* pci = (const char*)NULL,
                             int devIndex = 1,
                             bool printNewCfg = false);

    // Set cmd
    mlxCfgStatus setDevCfg();
    void compareCurrentParamsVectors(const std::vector<ParamView>& ParamVec1,
                                     const std::vector<ParamView>& ParamVec2,
                                     std::vector<ParamView>& paramMlxconfigNameDiffList);
    void setDevCfgWithDefault(Commander* commander,
                              std::vector<ParamView>& alignCurrentToDefault,
                              std::vector<ParamView>& alignNextToCurrent);
    mlxCfgStatus updateDefaultParamsWithUserValues(std::vector<ParamView>& userParams,
                                                   std::vector<ParamView>& defaultParams);
    mlxCfgStatus handlecompleteSetWithDefault(Commander* commander);
    // reset Cmd
    mlxCfgStatus resetDevsCfg();
    mlxCfgStatus resetDevCfg(const char* dev);
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

    // write query output to json funtions
    mlxCfgStatus
      WriteSingleParam(QueryOutputItem& queryOutItem, string deviceIndex, u_int8_t verbose, Json::Value& oJsonValue);
    void writeParamToJson(Json::Value& oJsonValue, string field, string param, u_int32_t val);

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

    // static print functions
    static int printParam(string param, u_int32_t val);
    static int printValue(string strVal, u_int32_t val);
    static void printSingleParam(const char* name, QueryOutputItem& queryOutItem, u_int8_t verbose, bool printNewCfg);

    bool askUser(const char* question, bool add_prefix = true, bool add_suffix = true);
    mlxCfgStatus err(bool report, const char* errMsg, ...);
    void printErr();
    // data members

    MlxCfgParams _mlxParams;
    std::string _errStr;
    dm_dev_id_t _devType;
};

#endif /* MLXCFG_UI_H_ */
