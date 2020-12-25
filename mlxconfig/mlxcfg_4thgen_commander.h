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
 *
 * mlxcfg_4thgen_commander.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_4THGEN_COMMANDER_H_
#define MLXCFG_4THGEN_COMMANDER_H_

#include <vector>
#include <utility>

#include <mtcr.h>
#include <errmsg.h>
#include <tools_dev_types.h>

#include "mlxcfg_commander.h"

#include "mlxcfg_status.h"
#include "mlxcfg_param_lib.h"

using namespace std;

typedef enum {
    MLX_CFG_OK,
    MLX_CFG_OK_EXIT,
    MLX_CFG_ABORTED,
    MLX_CFG_ERROR,
    MLX_CFG_ERROR_EXIT,
    MLX_CFG_ERROR_NO_USAGE
} mlxCfgStatus;

class MlxCfgParamParser
{
public:
    MlxCfgParamParser() : _param(Mcp_Last), _name(), _desc(){}
    MlxCfgParamParser(mlxCfgParam param, string name, string desc, map<string, u_int32_t> strMap)
        : _param(param), _name(name), _desc(desc), _strMap(strMap){}
    MlxCfgParamParser(mlxCfgParam param, string name, string desc, string allowedValues) : _param(param),
        _name(name), _desc(desc), _allowedValues(allowedValues){}

    ~MlxCfgParamParser() {}

    mlxCfgStatus parseUserInput(string input, u_int32_t& val);

    void printShortDesc();
    void printLongDesc(FILE *f);

    string getName() {return _name;}
    mlxCfgParam getParam() {return _param;}

    string getStrVal(u_int32_t val);

    map<string, u_int32_t> getStrMap(){return _strMap;}

private:
    mlxCfgParam _param;
    string _name; //param name for example: LINK_TYPE_P1
    string _desc; //for example: 4th generation devices only
    string _allowedValues;
    map<string, u_int32_t> _strMap; //map strings to values, for example: {{'InfiniBand',1},{'Ethernet',2},{'VPI',3}}


    void printShortDescAux();
    string getShortDescStrAux();
    void splitAndPrintDesc(FILE *f, string desc);

};

class MlxCfgInfo
{
public:
    MlxCfgInfo(string name, string title, map<mlxCfgParam, MlxCfgParamParser> params) :
        _name(name), _title(title), _params(params){};

    ~MlxCfgInfo() {}

    void printShortDesc();
    void printLongDesc(FILE *f);

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
    void printLongDesc(FILE *f);

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
    MlxCfgInfo createBootSettingsExt();
    MlxCfgInfo createCX3GlobalConf();
    MlxCfgInfo createQoS();
    MlxCfgInfo createLLDPClientSettings();
    MlxCfgInfo createLLDPNBDCBX();
};

class FourthGenCommander : public Commander,  public ErrMsg {
private:
    std::string _dev;
    u_int64_t _suppVec;
    MlxCfgAllInfo _allInfo;
    static string param2str[Mcp_Last];
    std::map<mlxCfgType, CfgParams*> _cfgList;
    std::map<mlxCfgParam, mlxCfgType> _param2TypeMap;
    int supportsToolsHCR();
    bool isLegal(mlxCfgType cfg);
    bool isLegal(mlxCfgParam cfg);
    int openComChk();
    mlxCfgType cfgParam2Type(mlxCfgParam param);
    void freeCfgList();
public:
    FourthGenCommander(mfile *mf, std::string dev);
    ~FourthGenCommander();
    void printLongDesc(FILE *f) {_allInfo.printLongDesc(f);}
    bool isDefaultSupported() {return true;}
    bool isCurrentSupported() {return false;}
    void queryAux(std::vector<ParamView>&, QueryType, bool);
    void queryParamViews(std::vector<ParamView>& paramsToQuery, QueryType qt = QueryNext);
    void queryAll(std::vector<ParamView>& params, vector<string>& failedTLVs, QueryType qt = QueryNext);
    void clearSemaphore();
    void invalidateCfgs();
    const char* loadConfigurationGetStr();
    void setRawCfg(std::vector<u_int32_t> rawTlvVec);
    std::vector<u_int32_t> getRawCfg(std::vector<u_int32_t> rawTlvVec) ;
    void dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump);
    void backupCfgs(vector<BackupView>& views);
    bool supportsCfg(mlxCfgType cfg);
    bool supportsParam(mlxCfgParam param);
    void getCfg(ParamView& cfgParam, QueryType qt = QueryNext);
    int getCfgAux(mlxCfgParam cfgParam, u_int32_t& val, bool getDefault = false);
    int getCfgAux(std::vector<cfgInfo>& infoVec);
    void setCfg(std::vector<ParamView>& params, bool force);
    int setCfgAux(mlxCfgParam cfgParam, u_int32_t val);
    int setCfgAux(const std::vector<cfgInfo>& infoVec, mlxCfgParam& failedParam);
    void setIgnoreSoftLimits(bool val);
    void setIgnoreHardLimits(bool val);
    void updateParamViewValue(ParamView&, std::string val);
};

#endif /* MLXCFG_4THGEN_COMMANDER_H_ */
