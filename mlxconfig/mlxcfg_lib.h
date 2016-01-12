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

#ifndef MLXCFG_LIB_H_
#define MLXCFG_LIB_H_

#include <vector>
#include <utility>

#include <mtcr.h>
#include <errmsg.h>
#include <tools_dev_types.h>

#include "mlxcfg_status.h"
#include "mlxcfg_param_lib.h"

class MlxCfgOps : public ErrMsg {
public:
    MlxCfgOps();
    ~MlxCfgOps();
    int open(const char* devStr, bool forceClearSem=false);
    int opend(mfile* mf, bool forceClearSem=false);

    // no need to close , this is done  in destructor

    bool supportsCfg(mlxCfgType cfg);
    bool supportsParam(mlxCfgParam param);

    int getCfg(mlxCfgParam cfgParam, u_int32_t& val, bool getDefault = false);
    int getCfg(std::vector<cfgInfo>& infoVec);

    int setCfg(mlxCfgParam cfgParam, u_int32_t val);
    int setCfg(const std::vector<cfgInfo>& infoVec);

    int setRawCfg(std::vector<u_int32_t> rawTlvVec);

    int dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump);

    int invalidateCfgs();

    // Set/Un-Set ignore limits for all configurations
    void setIgnoreSoftLimits(bool val);
    void setIgnoreHardLimits(bool val);

    // Set/Un-Set Ignore limits per configuration
    // Adrianc: TBD

    const char* loadConfigurationGetStr();

    int isDefaultSupported(bool &defaultSupported);

private:
    int openComChk();
    int supportsToolsHCR();
    int supportsNVData();
    bool isLegal(mlxCfgType cfg);
    bool isLegal(mlxCfgParam cfg);

    int invalidateCfgs4thGen();
    int invalidateCfgs5thGen();

    mlxCfgType cfgParam2Type(mlxCfgParam param);
    std::map<mlxCfgType, CfgParams*> _cfgList; // needs to be initialized in constructor and freed in destructor, will contain all the  tools supported cfgs
    std::map<mlxCfgParam, mlxCfgType> _param2TypeMap;
    dm_dev_id_t _deviceId;
    mfile* _mf;
    u_int64_t _suppVec;
    bool _isFifthGen;
};



#endif /* MLXCFG_LIB_H_ */
