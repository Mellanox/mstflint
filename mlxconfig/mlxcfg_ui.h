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
    Mc_UnknownCmd
} mlxCfgCmd;

typedef enum {
    MLX_CFG_OK,
    MLX_CFG_OK_EXIT,
    MLX_CFG_ABORTED,
    MLX_CFG_ERROR,
    MLX_CFG_ERROR_EXIT
} mlxCfgStatus;


class MlxCfgParams
{
public:
    MlxCfgParams() : device(),cmd(Mc_UnknownCmd), yes(false), force(false) {}
    ~MlxCfgParams() {}

    std::string device;
    mlxCfgCmd cmd;
    bool yes;
    std::vector<cfgInfo> params;
    static std::string param2str[Mcp_Last];
    bool force;// ignore parameter checks

    u_int32_t getParamVal(mlxCfgParam p);
};


class MlxCfg
{
public:
    MlxCfg() : _mlxParams(), _errStr(){}
    ~MlxCfg() {};
    mlxCfgStatus execute(int argc, char* argv[]);
private:

    // User interface and parsing methods
    void printHelp();
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
    //
    mlxCfgStatus test(const char* dev);

    bool askUser(const char* question);
    mlxCfgStatus err(bool report, const char* errMsg, ...);
    void printErr();
    // data members
    MlxCfgParams _mlxParams;
    std::string _errStr;
};




#endif /* MLXCFG_UI_H_ */
