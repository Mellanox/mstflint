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
 * mlxcfg_lib.h
 *
 *  Created on: Feb 17, 2014
 *      Author: adrianc
 */

#ifndef MLXCFG_LIB_H_
#define MLXCFG_LIB_H_

#include <vector>
#include <utility>

#include <mtcr.h>

#include "errmsg.h"


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

class MlxCfgOps : public ErrMsg {
public:
    MlxCfgOps();
    ~MlxCfgOps();
    int open(const char* devStr);
    int opend(mfile* mf);

    // no need to close , this is done  in destructor

    bool supportsCfg(mlxCfgType cfg);
    bool supportsParam(mlxCfgParam param);

    int getCfg(mlxCfgParam cfgParam, u_int32_t& val);
    int getCfg(std::vector<cfgInfo>& infoVec);

    int setCfg(mlxCfgParam cfgParam, u_int32_t val, bool ignoreCheck=false);
    int setCfg(const std::vector<cfgInfo>& infoVec, bool ignoreCheck=false);

    int invalidateCfgs();

private:

    class CfgParams : public ErrMsg
    {
    public:
        CfgParams(mlxCfgType t=Mct_Last, u_int32_t tlvT=0);
        virtual ~CfgParams() {}

        virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
        virtual u_int32_t getParam(mlxCfgParam paramType) = 0;

        virtual int getFromDev(mfile* mf) = 0;
        virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;

        mlxCfgType type;
        u_int32_t tlvType;
    protected:
        virtual bool isLegal(mfile* mf=NULL) = 0;
        bool _updated; // set true on get and false on set
    };

    class SriovParams : public CfgParams
    {
    public:
        SriovParams() : CfgParams(Mct_Sriov, SRIOV_TYPE) , _sriovEn(MLXCFG_UNKNOWN), _numOfVfs(MLXCFG_UNKNOWN), _maxVfs(1) {}
        ~SriovParams() {};

        virtual void setParam(mlxCfgParam paramType, u_int32_t val);
        virtual u_int32_t getParam(mlxCfgParam paramType);

        virtual int getFromDev(mfile* mf);
        virtual int setOnDev(mfile* mf, bool ignoreCheck=false);

        int updateMaxVfs(mfile* mf);

    private:
        virtual bool isLegal(mfile* mf);

        u_int32_t _sriovEn;
        u_int32_t _numOfVfs;
        u_int32_t _maxVfs;
    };

    class WolParams : public CfgParams
    {
    public:
        WolParams(int port) : CfgParams(port == 1 ? Mct_Wol_P1 : Mct_Wol_P2, WOL_TYPE), _port(port), _wolMagicEn(MLXCFG_UNKNOWN) {}
        ~WolParams() {}

        virtual void setParam(mlxCfgParam paramType, u_int32_t val);
        virtual u_int32_t getParam(mlxCfgParam paramType);

        virtual int getFromDev(mfile* mf);
        virtual int setOnDev(mfile* mf, bool ignoreCheck=false);

    private:
        virtual bool isLegal(mfile* mf=NULL);
        // Wake on magic packet (atm this is the only mode which is supported)
        int _port;
        u_int32_t _wolMagicEn;
    };

    class VpiParams : public CfgParams
    {
    public:
        VpiParams(int port) : CfgParams(port == 1 ? Mct_Vpi_P1 : Mct_Vpi_P2, VPI_TYPE), _port(port), _linkType(MLXCFG_UNKNOWN) {}
        ~VpiParams() {}

        virtual void setParam(mlxCfgParam paramType, u_int32_t val);
        virtual u_int32_t getParam(mlxCfgParam paramType);

        virtual int getFromDev(mfile* mf);
        virtual int setOnDev(mfile* mf, bool ignoreCheck=false);

    private:
        virtual bool isLegal(mfile* mf=NULL);
        int _port;
        u_int32_t _linkType;
    };

    class BarSzParams : public CfgParams
    {
    public:
        BarSzParams() : CfgParams(Mct_Bar_Size, BAR_SIZE_TYPE) ,_maxLogBarSz(1), _currLogBarSz(1), _logBarSz(MLXCFG_UNKNOWN) {}
        ~BarSzParams() {};

        virtual void setParam(mlxCfgParam paramType, u_int32_t val);
        virtual u_int32_t getParam(mlxCfgParam paramType);

        virtual int getFromDev(mfile* mf);
        virtual int setOnDev(mfile* mf, bool ignoreCheck=false);

        int updateBarSzInfo(mfile* mf);

    private:
        virtual bool isLegal(mfile* mf=NULL);
        u_int32_t _maxLogBarSz;
        u_int32_t _currLogBarSz;
        u_int32_t _logBarSz;

    };


    int openComChk();
    int supportsToolsHCR();
    bool isLegal(mlxCfgType cfg);
    bool isLegal(mlxCfgParam cfg);

    static mlxCfgType cfgParam2Type(mlxCfgParam param);
    std::vector<CfgParams*> _cfgList; // needs to be initialized in constructor and freed in destructor, will contain all the  tools supported cfgs
    static u_int64_t cfgSuppMask[Mct_Last];
    mfile* _mf;
    u_int64_t _suppVec;
};



#endif /* MLXCFG_LIB_H_ */
