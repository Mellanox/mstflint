/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#include "mlxcfg_lib.h"

typedef enum {
    Mc_Set,
    Mc_Query,
    Mc_Reset,
    Mc_Clr_Sem,
    Mc_Set_Raw,
    Mc_UnknownCmd
} mlxCfgCmd;

typedef enum {
    MLX_CFG_OK,
    MLX_CFG_OK_EXIT,
    MLX_CFG_ABORTED,
    MLX_CFG_ERROR,
    MLX_CFG_ERROR_EXIT
} mlxCfgStatus;

using namespace std;

class MlxCfgParamParser
{
public:
    MlxCfgParamParser(): _param(Mcp_Last), _name(), _desc(){}
    MlxCfgParamParser(mlxCfgParam param, string name, string desc, map<string, u_int32_t> strMap)
        : _param(param), _name(name), _desc(desc), _strMap(strMap){}
    MlxCfgParamParser(mlxCfgParam param, string name, string desc, string allowedValues) : _param(param),
            _name(name), _desc(desc), _allowedValues(allowedValues){}

    ~MlxCfgParamParser() {}

    mlxCfgStatus parseUserInput(string input, u_int32_t& val);

    void printShortDesc();
    void printLongDesc();

    string getName() {return _name;}
    mlxCfgParam getParam() {return _param;}

    string getStrVal(u_int32_t val);

private:
    mlxCfgParam _param;
    string _name; //param name for example: LINK_TYPE_P1
    string _desc; //for example: 4th generation devices only
    string _allowedValues;
    map<string, u_int32_t> _strMap; //map strings to values, for example: {{'InfiniBand',1},{'Ethernet',2},{'VPI',3}}


    void printShortDescAux();
    string getShortDescStrAux();
    void splitAndPrintDesc(string desc);
    bool compareVal(string a, string b);

};

class MlxCfgInfo
{
public:
    MlxCfgInfo(string name, string title, map<mlxCfgParam, MlxCfgParamParser> params) :
        _name(name), _title(title), _params(params){};

    ~MlxCfgInfo() {}

    void printShortDesc();
    void printLongDesc();

    mlxCfgStatus getParamParser(mlxCfgParam, MlxCfgParamParser&);
    mlxCfgStatus getParamParser(string, MlxCfgParamParser&);
    string getName() { return _name; }

private:
    string _name; //for example: VPI Settings
    string _title; //for example: Control network link type
    map<mlxCfgParam, MlxCfgParamParser> _params; //for example: {{LINK_TYPE_P1,*},{LINK_TYPE_P2,*}}
    vector<MlxCfgParamParser> getParamsMapValues();
};

class MlxCfgAllInfo
{
public:
    MlxCfgAllInfo();

    ~MlxCfgAllInfo() {}

    void printShortDesc();
    void printLongDesc();

    mlxCfgStatus parseParam(string tag, string strval, u_int32_t& val, mlxCfgParam& param);
    mlxCfgStatus getParamParser(mlxCfgParam p, MlxCfgParamParser& paramParser);

    vector<MlxCfgInfo> _allInfo;

private:
    MlxCfgInfo createPciSettings();
    MlxCfgInfo createIBDynamicallyConnect();
    MlxCfgInfo createInfinibandBootSettings();
    MlxCfgInfo createInternalSettings();
    MlxCfgInfo createPrebootBootSettings();
    MlxCfgInfo createRoCECongestionControlECN();
    MlxCfgInfo createRoCEV1_5NextProtocol();
    MlxCfgInfo createRoCECongestionControlParameters();
    MlxCfgInfo createVPISettings();
    MlxCfgInfo createWakeOnLAN();
    MlxCfgInfo createExternalPort();
    MlxCfgInfo createBootSettingsExt();
};

class MlxCfgParams
{
public:
    MlxCfgParams() : device(), rawTlvFile(), cmd(Mc_UnknownCmd), yes(false), force(false), showDefault(false) {}
    ~MlxCfgParams() {}

    std::string device;
    std::string rawTlvFile;
    mlxCfgCmd cmd;
    bool yes;
    std::vector<cfgInfo> params;
    static std::string param2str[Mcp_Last];
    bool force;// ignore parameter checks
    bool showDefault;

    u_int32_t getParamVal(mlxCfgParam p);
};


class MlxCfg
{
public:
    MlxCfg() : _mlxParams(), _errStr(), _allInfo(){}
    ~MlxCfg() {};
    mlxCfgStatus execute(int argc, char* argv[]);
private:

    // User interface and parsing methods
    void printHelp(bool longDesc=false);
    void printVersion();
    void printUsage();
    mlxCfgStatus parseArgs(int argc, char* argv[]);
    //Helper functions for parse args
    mlxCfgStatus processArg(std::string tag, u_int32_t val);
    mlxCfgStatus extractCfgArgs(int argc, char* argv[]);
    bool tagExsists(mlxCfgParam tag);
    const char* getDeviceName(const char* dev);

    // Query cmd
    mlxCfgStatus queryDevsCfg();
    mlxCfgStatus queryDevCfg(const char* dev, const char* pci=(const char*)NULL, int devIndex=1, bool printNewCfg=false);

    // Set cmd
    mlxCfgStatus setDevCfg();
    // reset Cmd
    mlxCfgStatus resetDevsCfg();
    mlxCfgStatus resetDevCfg(const char* dev);
    // Set Raw TLV file
    mlxCfgStatus setDevRawCfg();
    mlxCfgStatus tlvLine2DwVec(const std::string& tlvStringLine, std::vector<u_int32_t>& tlvVec);

    mlxCfgStatus clrDevSem();
    //
    mlxCfgStatus test(const char* dev);

    bool askUser(const char* question);
    mlxCfgStatus err(bool report, const char* errMsg, ...);
    void printErr();
    // data members
    MlxCfgParams _mlxParams;
    std::string _errStr;
    MlxCfgAllInfo _allInfo;

};




#endif /* MLXCFG_UI_H_ */
