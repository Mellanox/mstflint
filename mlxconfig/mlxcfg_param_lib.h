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
/*
 * mlxcfg_param_lib.h
 *
 *  Created on: Mar 22, 2015
 *      Author: adrianc
 */

#ifndef MLXCFG_PARAM_LIB_H_
#define MLXCFG_PARAM_LIB_H_

#include <vector>
#include <utility>

#include <errmsg.h>
#include <tools_layouts/tools_open_layouts.h>

#define MLXCFG_UNKNOWN 0xffffffff

#define WOL_TYPE 0x10
#define SRIOV_TYPE 0x11
#define VPI_TYPE 0x12
#define BAR_SIZE_TYPE 0x13


typedef enum {
    Mct_Sriov = 0,
    Mct_Wol_P1,
    Mct_Wol_P2,
    Mct_Vpi_P1,
    Mct_Vpi_P2,
    Mct_Bar_Size,
    Mct_Last
} mlxCfgType;

typedef enum {
    Mcp_Sriov_En = 0,
    Mcp_Num_Of_Vfs,
    Mcp_Wol_Magic_En_P1,
    Mcp_Wol_Magic_En_P2,
    Mcp_Link_Type_P1,
    Mcp_Link_Type_P2,
    Mcp_Log_Bar_Size,
    Mcp_Last
} mlxCfgParam;

typedef std::pair<mlxCfgParam, u_int32_t> cfgInfo;

/*
 *  Basic Param Class
 */

class CfgParams : public ErrMsg
{
public:
    CfgParams(mlxCfgType t=Mct_Last, u_int32_t tlvT=0);
    virtual ~CfgParams() {}

    virtual bool cfgSupported(mfile* mf) = 0;
    void setDevCapVec(u_int64_t v) {_devCapVec = v;}

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;

    virtual int getDefaultAndFromDev(mfile* mf);
    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

    void setIgnoreSoftLimits(bool val);
    void setIgnoreHardLimits(bool val);

    mlxCfgType type;
    u_int32_t tlvTypeIdx;
protected:
    // param validadion methods, only checkCfg shuold be called
    virtual bool checkCfg(mfile* mf=NULL);
    virtual bool hardLimitCheck() = 0;
    virtual bool softLimitCheck(mfile* mf=NULL);

    // get default parameters for configuration (4th gen)
    int getDefaultParams4thGen(mfile* mf, struct tools_open_query_def_params_global* global_params);
    int getDefaultParams4thGen(mfile* mf, int port, struct tools_open_query_def_params_per_port* port_params);

    u_int64_t _devCapVec; // relevant for 4th gen devices
    bool _updated; // set true on get and false on set
    bool _ignoreSoftLimits; // soft limits checks will not be performed for configuration
    bool _ignoreHardLimits; // hard limits checks will not be performed
};

/*
 * SRIOV param classes:
 */

class SriovParams : public CfgParams
{
public:
    SriovParams() : CfgParams(Mct_Sriov, SRIOV_TYPE) , _sriovEn(MLXCFG_UNKNOWN), _numOfVfs(MLXCFG_UNKNOWN), _maxVfs(1) {}
    ~SriovParams() {};

    virtual bool cfgSupported(mfile* mf) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

protected:
    virtual bool hardLimitCheck();
    virtual bool softLimitCheck(mfile* mf=NULL) = 0;

    u_int32_t _sriovEn;
    u_int32_t _numOfVfs;
    u_int32_t _maxVfs;
};

class SriovParams4thGen : public SriovParams
{
public:
    SriovParams4thGen() : SriovParams() {}
    ~SriovParams4thGen() {};

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    virtual int updateMaxVfs(mfile* mf);
    virtual bool softLimitCheck(mfile* mf=NULL);

};

class SriovParams5thGen : public SriovParams
{
public:
    SriovParams5thGen() : SriovParams() {}
    ~SriovParams5thGen() {};

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual int updateMaxVfs(mfile* mf);
    virtual bool softLimitCheck(mfile* mf=NULL);
};

/*
 * WOL param classes:
 */

class WolParams : public CfgParams
{
public:
    WolParams(int port) : CfgParams(port == 1 ? Mct_Wol_P1 : Mct_Wol_P2, WOL_TYPE), _port(port), _wolMagicEn(MLXCFG_UNKNOWN) {}
    ~WolParams() {}

    virtual bool cfgSupported(mfile* mf) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    virtual bool hardLimitCheck();
    // Wake on magic packet (atm this is the only mode which is supported)
    int _port;
    u_int32_t _wolMagicEn;
};

class WolParams4thGen : public WolParams
{
public:
    WolParams4thGen(int port) : WolParams(port) {}
    ~WolParams4thGen() {}

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
};

class WolParams5thGen : public WolParams
{
public:
    WolParams5thGen(int port) : WolParams(port) {}
    ~WolParams5thGen() {}

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
};

/*
 * VPI param classes:
 */

class VpiParams : public CfgParams
{
public:
    VpiParams(int port) : CfgParams(port == 1 ? Mct_Vpi_P1 : Mct_Vpi_P2, VPI_TYPE), _port(port), _linkType(MLXCFG_UNKNOWN), _defaultLinkType(MLXCFG_UNKNOWN){}
    ~VpiParams() {}

    virtual bool cfgSupported(mfile* mf) = 0;

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    int getFromDevComPre();
    int getFromDevComPost(MError mnvaComRC);
    int setOnDevComPre(bool ignoreCheck);
    int setOnDevComPost(MError mnvaComRC);

    int _port;
    u_int32_t _linkType;
    u_int32_t _defaultLinkType;
    // FW TLV (used when actually setting/getting the TLV from FW)
    std::vector<u_int8_t> _tlvBuff;
    struct tools_open_vpi_settings _vpiTlv;


};

class VpiParams4thGen : public VpiParams
{
public:
    VpiParams4thGen(int port) : VpiParams(port){}
    ~VpiParams4thGen() {}

    virtual bool cfgSupported(mfile* mf);
    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual bool hardLimitCheck();

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
};

class VpiParams5thGen : public VpiParams
{
public:
    VpiParams5thGen(int port) : VpiParams(port){}
    ~VpiParams5thGen() {}

    virtual bool cfgSupported(mfile* mf);
    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual bool hardLimitCheck();

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    u_int32_t getTlvTypeBe();
};

/*
 * BAR size param classes:
 */

class BarSzParams : public CfgParams
{
public:
    BarSzParams() : CfgParams(Mct_Bar_Size, BAR_SIZE_TYPE) ,_maxLogBarSz(1), _logBarSz(MLXCFG_UNKNOWN) {}
    ~BarSzParams() {}

    virtual bool cfgSupported(mfile* mf) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    virtual bool hardLimitCheck();
    virtual bool softLimitCheck(mfile* mf=NULL) = 0;
    virtual int getDefaultBarSz(mfile* mf) = 0;
    u_int32_t _maxLogBarSz;
    u_int32_t _logBarSz;

};

class BarSzParams4thGen : public BarSzParams
{
public:
    BarSzParams4thGen() : BarSzParams() {}
    ~BarSzParams4thGen() {}

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    virtual bool softLimitCheck(mfile* mf=NULL);
    virtual int getDefaultBarSz(mfile* mf);
};

class BarSzParams5thGen : public BarSzParams
{
public:
    BarSzParams5thGen() : BarSzParams() {}
    ~BarSzParams5thGen() {}

    virtual bool cfgSupported(mfile* mf);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    virtual bool softLimitCheck(mfile* mf=NULL);
    virtual int getDefaultBarSz(mfile* mf);
};

#endif /* MLXCFG_PARAM_LIB_H_ */
