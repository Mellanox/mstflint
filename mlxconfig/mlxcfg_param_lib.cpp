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
 * mlxcfg_param_lib.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: adrianc
 */

#include <signal.h>
#include <math.h>

#include <mft_sig_handler.h>
#include <reg_access/reg_access.h>
#include <bit_slice.h>
#include <cmdif/tools_cif.h>
#include <mtcr.h>
#include <compatibility.h>

#include "mlxcfg_param_lib.h"
#include "mlxcfg_status.h"

enum {
    SRIOV_MASK = 0x1,
    WOL_P1_MASK = 0x2,
    WOL_P2_MASK = 0x4 ,
    VPI_P1_MASK = 0x8,
    VPI_P2_MASK = 0x10,
    BAR_SZ_MASK = 0x20
};

// tlv classes:
enum {
    CLASS_GLOBAL = 0x0,
    CLASS_PHYS_PORT = 0x1,
    CLASS_BMC = 0x2,
    CLASS_PER_HOST = 0x3,
    CLASS_ESWITCH = 0x4
};

#define MAX_VFS_ADDR 0x38
#define MAX_BAR_SZ_ADDR 0xc8
#define DEFAULT_BAR_SZ_ADDR 0x48


/*
 * Debug print MACRO of the NV Tlvs:
 */
//#define _ENABLE_DEBUG_
#ifdef _ENABLE_DEBUG_
# define DEBUG_PRINT_SEND(data_struct, struct_name)\
    printf("-I- Data Sent:\n");\
    tools_open_##struct_name##_print(data_struct, stdout, 1)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)\
    printf("-I- Data Recieved:\n");\
    tools_open_##struct_name##_print(data_struct, stdout, 1)
#else
# define DEBUG_PRINT_SEND(data_struct, struct_name)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)
#endif

#define CHECK_RC(rc)\
    if (rc) return rc;

static void dealWithSignal()
{
    int sig;
    sig = mft_signal_is_fired();
    if (sig) {
        // reset recieved signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        //raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
    return;
}

/*
 * Adrianc: TODO: create a SetTlv class and two child classess , for 4th/5th gen.
 *          each param class will have an instance of SetTlv class
 */

MError mnvaCom4thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int16_t tlvTypeIdx, reg_access_method_t method, u_int16_t typeMod)
{
    struct tools_open_mnva mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_mnva));

    mnvaTlv.nv_hdr.length = len >> 2; // length is in dwords
    mnvaTlv.nv_hdr.type = tlvTypeIdx;
    mnvaTlv.nv_hdr.type_mod = typeMod;
    memcpy(mnvaTlv.data, buff, len);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_mnva(mf, method, &mnvaTlv);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    memcpy(buff, mnvaTlv.data, len);
    return ME_OK;
}

MError mnvaCom5thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t tlvType, reg_access_method_t method)
{
    struct tools_open_nvda mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_nvda));

    mnvaTlv.nv_hdr.length = len;
    mnvaTlv.nv_hdr.rd_en = 0;
    mnvaTlv.nv_hdr.over_en = 1;
    // tlvType should be in the correct endianess
    mnvaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw =  __be32_to_cpu(tlvType);
    memcpy(mnvaTlv.data, buff, len);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    DEBUG_PRINT_SEND(&mnvaTlv, nvda);
    rc = reg_access_nvda(mf, method, &mnvaTlv);
    DEBUG_PRINT_RECIEVE(&mnvaTlv, nvda);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    memcpy(buff, mnvaTlv.data, len);
    return ME_OK;
}

MError nvqcCom5thGen(mfile* mf, u_int32_t tlvType, bool& suppRead, bool& suppWrite)
{
    struct tools_open_nvqc nvqcTlv;
    memset(&nvqcTlv, 0, sizeof(struct tools_open_nvqc));

    // tlvType should be in the correct endianess
    nvqcTlv.type.tlv_type_dw.tlv_type_dw = __be32_to_cpu(tlvType);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_nvqc(mf, REG_ACCESS_METHOD_GET, &nvqcTlv);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    suppRead = nvqcTlv.support_rd;
    suppWrite = nvqcTlv.support_wr;
    return ME_OK;
}

/***************************
 * Class implementations :
 ***************************/

/*
 * CfgParams Class implementation :
 */

CfgParams::CfgParams(mlxCfgType t, u_int32_t tlvT) {
    // init the ErrMsg Class
    std::map<int, std::string> errmap;
    errmap[MCE_SUCCESS] = "Success";
    errmap[MCE_FAILED] = "General Failure";
    errmap[MCE_BAD_PARAMS] = "Bad parameters";
    errmap[MCE_BAD_PARAM_VAL] = "Bad parameter value";
    errmap[MCE_BAD_STATUS] = "General Failure";
    errmap[MCE_GET_DEFAULT_PARAMS] = "Failed to get default params";

    updateErrCodes(errmap);
    type = t;
    tlvTypeIdx = tlvT;
    _updated = false;
    _ignoreHardLimits = false;
    _ignoreSoftLimits = false;
    _devCapVec = 0;
}

int CfgParams::getDefaultParams4thGen(mfile* mf, struct tools_open_query_def_params_global* global_params)
{
    MError rc  = tcif_query_global_def_params(mf, global_params);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int CfgParams::getDefaultParams4thGen(mfile* mf, int port, struct tools_open_query_def_params_per_port* port_params)
{
    MError rc  = tcif_query_per_port_def_params(mf, port, port_params);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int CfgParams::getDefaultAndFromDev(mfile* mf)
{
    int rc;
    rc = getDefaultParams(mf); CHECK_RC(rc);
    rc = getFromDev(mf); CHECK_RC(rc);
    return MCE_SUCCESS;
}

bool CfgParams::checkCfg(mfile* mf)
{
    if (!_ignoreHardLimits && !hardLimitCheck()) {
        return false;
    }
    if (!_ignoreSoftLimits && !softLimitCheck(mf)) {
        return false;
    }
    return true;
}

bool CfgParams::softLimitCheck(mfile* mf)
{
    // by default not implemented
    (void)mf;
    return true;
}

void CfgParams::setIgnoreSoftLimits(bool val)
{
    _ignoreSoftLimits = val;
}
void CfgParams::setIgnoreHardLimits(bool val)
{
    _ignoreHardLimits = val;
}

/*
 * SriovParam Class implementation:
 */

void SriovParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Sriov_En) {
        _sriovEn = val;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        _numOfVfs = val;
    }
}

u_int32_t SriovParams::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEn;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfs;
    }
    return MLXCFG_UNKNOWN;
}

bool SriovParams::hardLimitCheck()
{
    if ((_numOfVfs > _maxVfs)) {
        errmsg("Number of VFs exceeds limit (%d).", _maxVfs);
        return false;
    }

    if (_sriovEn != 0 && _sriovEn != 1) {
        errmsg("illegal SRIOV_EN parameters value. (should be 0 or 1)");
        return false;
    }
    return true;
}

/*
 * SriovParam4thGen Class implementation
 */

bool SriovParams4thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return _devCapVec & SRIOV_MASK;
}

int SriovParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_global global_params;
    int rc;
    rc = updateMaxVfs(mf); CHECK_RC(rc);
    rc = getDefaultParams4thGen(mf, &global_params);
    if (rc == MCE_SUCCESS) {
        _sriovEn = global_params.sriov_en;
        _numOfVfs = global_params.num_vfs;
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

int SriovParams4thGen::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[tools_open_sriov_size()];
    struct tools_open_sriov sriovTlv;
    memset(buff, 0, tools_open_sriov_size());
    memset(&sriovTlv, 0, sizeof(struct tools_open_sriov));
    // pack it
    tools_open_sriov_pack(&sriovTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&sriovTlv, sriov);
    rc = mnvaCom4thGen(mf, buff, tools_open_sriov_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, 0);
    // check rc
    DEBUG_PRINT_RECIEVE(&sriovTlv, sriov);
    if (rc) {// when attempting to get a nv_cfg tlv from device ME_REG_ACCESS_RES_NOT_AVLBL means - no valid
             // tlv found. i.e default configuration are on.
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {

            return MCE_SUCCESS;
        }
        return errmsg(MCE_BAD_STATUS, "Failed to get SRIOV configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_sriov_unpack(&sriovTlv, buff);
    _sriovEn = sriovTlv.sriov_en;
    _numOfVfs = sriovTlv.total_vfs;
    _updated = true;

    return MCE_SUCCESS;
}

int SriovParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    if (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for SRIOV.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[tools_open_sriov_size()];
    struct tools_open_sriov sriovTlv;

    memset(buff, 0, tools_open_sriov_size());
    memset(&sriovTlv, 0, sizeof(struct tools_open_sriov));

    sriovTlv.sriov_en = _sriovEn;
    sriovTlv.total_vfs = _numOfVfs;
    // pack it
    tools_open_sriov_pack(&sriovTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_sriov_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set SRIOV params: %s",m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

int SriovParams4thGen::updateMaxVfs(mfile* mf)
{
    u_int64_t data = 0;
    int rc = tcif_query_dev_cap(mf, MAX_VFS_ADDR, &data);
    if (rc) {
        return errmsg("failed to query device capabilities: %s", m_err2str((MError)rc));
    }
    _maxVfs = (u_int32_t)(data & 0xff);
    if (_maxVfs == 0) { // defined in CX PRM , if max_func_idx=0 then all functions(128) are operational
        _maxVfs = 128;
    }
    _maxVfs--; // remove 1 physical function
    return MCE_SUCCESS;
}

bool SriovParams4thGen::softLimitCheck(mfile* mf)
{
    u_int32_t barSz = 0;
    BarSzParams4thGen barParams;

    if (!mf) {
        return false;
    }

    if (barParams.getDefaultAndFromDev(mf)) {
        return false;
    }

    if (_sriovEn == 0) {
        return true;
    }

    barSz = barParams.getParam(Mcp_Log_Bar_Size);

    if (barSz == MLXCFG_UNKNOWN) {
        return errmsg("Failed to get the bar size from device");
    }
    // this is the default log2 bar size , we require (numOfVfs+1)*(2^log_uar_bar) <= 512 or else the node might not boot
    double TotalMem = (_numOfVfs + 1)*(1 << barSz); // 1 for physical func

    if ((TotalMem > 512)){
        unsigned int maxAlowedVfs =static_cast<unsigned int>(512/(1 << barSz)) - 1;
        errmsg("illegal SRIOV parameter value. Maximal number of VFs: %d", maxAlowedVfs < _maxVfs ? maxAlowedVfs : _maxVfs);
        return false;
    }
    return true;
}

/*
 * SriovParams5thGen Class implementation
 */

bool SriovParams5thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return false;
}

int SriovParams5thGen::getDefaultParams(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int SriovParams5thGen::getFromDev(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int SriovParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    (void)mf;
    (void)ignoreCheck;
    return MCE_NOT_IMPLEMENTED;
}

int SriovParams5thGen::updateMaxVfs(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

bool SriovParams5thGen::softLimitCheck(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

/*
 * WolParams Class implementation :
 */

void WolParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Wol_Magic_En_P1 && _port == 1 ) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2) ) {
        _wolMagicEn = val;
    }
}

u_int32_t WolParams::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Wol_Magic_En_P1 && _port == 1 ) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2) ) {
        return _wolMagicEn;
    }
    return MLXCFG_UNKNOWN;
}



bool WolParams::hardLimitCheck()
{
    if (_wolMagicEn == 0 || _wolMagicEn == 1 ) {
        return true;
    }
    errmsg("illegal WOL parameter value. can be either 0 or 1.");
    return false;
}

/*
 * WolParams4thGen Class implementation :
 */

bool WolParams4thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return ((_devCapVec & WOL_P1_MASK) && _port == 1) || ((_devCapVec & WOL_P2_MASK) && _port == 2 );
}

int WolParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port port_params;
    int rc = getDefaultParams4thGen(mf, _port , &port_params);
    if (rc == MCE_SUCCESS) {
        _wolMagicEn = port_params.en_wol_magic;
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

int WolParams4thGen::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[tools_open_wol_size()];
    struct tools_open_wol wolTlv;
    memset(buff, 0, tools_open_wol_size());
    memset(&wolTlv, 0, sizeof(struct tools_open_wol));
    // pack it
    tools_open_wol_pack(&wolTlv, buff);
    // send it
    rc = mnvaCom4thGen(mf, buff, tools_open_wol_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);
    // check rc
    if (rc) {
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get WOL port%d configuration: %s", _port, m_err2str(rc));
    }
    // unpack and update
    tools_open_wol_unpack(&wolTlv, buff);
    _wolMagicEn = wolTlv.en_wol_magic;
    _updated = true;

    return MCE_SUCCESS;
}

int WolParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    if (_wolMagicEn == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for WOL.", err()? err() : "");
    }
    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    // prep tlv
    MError ret;
    u_int8_t buff[tools_open_wol_size()];
    struct tools_open_wol wolTlv;

    memset(buff, 0, tools_open_wol_size());
    memset(&wolTlv, 0, sizeof(struct tools_open_wol));

    wolTlv.en_wol_magic= _wolMagicEn;
    // pack it
    tools_open_wol_pack(&wolTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_wol_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (ret) {
        return errmsg("failed to set WOL params for port%d: %s", _port, m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

/*
 * WolParams5thGen Class implementation :
 */

bool WolParams5thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return false;
}

int WolParams5thGen::getDefaultParams(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int WolParams5thGen::getFromDev(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int WolParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    (void)mf;
    (void)ignoreCheck;
    return MCE_NOT_IMPLEMENTED;
}

/*
 * BarSzParams Class implementation :
 */


void BarSzParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Log_Bar_Size) ) {
        _logBarSz = val;
    }
}

u_int32_t BarSzParams::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Bar_Size) {
        return _logBarSz;
    }
    return MLXCFG_UNKNOWN;
}


bool BarSzParams::hardLimitCheck()
{
    if (_logBarSz > _maxLogBarSz ) {
        errmsg("given bar size is too large, max allowed log2 bar size: 0x%x", _maxLogBarSz);
        return false;
    }
    return true;
}

/*
 * BarSzParams4thGen Class implementation :
 */

bool BarSzParams4thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return _devCapVec & BAR_SZ_MASK ;
}

int BarSzParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_global global_params;
    int rc = getDefaultParams4thGen(mf, &global_params);
    if ((rc == MCE_SUCCESS) & 0) { //TODO: adrianc: remove the & 0 when FW displays thesee parameters correctly in QUERY_DEF_PARAMS command
        _logBarSz = global_params.uar_bar_size;
        _maxLogBarSz = global_params.max_uar_bar_size;
    } else {
        // attempt to take from query_dev_cap
        rc = getDefaultBarSz(mf);
    }
    return rc;
}

int BarSzParams4thGen::getDefaultBarSz(mfile* mf)
{
    u_int64_t data = 0;
    MError rc = tcif_query_dev_cap(mf, MAX_BAR_SZ_ADDR, &data);
    if (rc) {
        return errmsg(MCE_BAD_STATUS,"Failed to query device capabilities. %s", tcif_err2str(rc));
    }

    _maxLogBarSz = EXTRACT64(data, 3, 6);

    rc = tcif_query_dev_cap(mf, DEFAULT_BAR_SZ_ADDR, &data);
    if (rc) {
        return errmsg(MCE_BAD_STATUS,"Failed to query device capabilities. %s", tcif_err2str(rc));
    }

    _logBarSz = EXTRACT64(data, 16, 6) + 1; //adrianc: this field reports only half of the bar size (i.e without the blue flame)
    return MCE_SUCCESS;
}

int BarSzParams4thGen::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[tools_open_bar_size_size()];
    struct tools_open_bar_size barSzTlv;
    memset(buff, 0, tools_open_bar_size_size());
    memset(&barSzTlv, 0, sizeof(struct tools_open_bar_size));
    // pack it
    tools_open_bar_size_pack(&barSzTlv, buff);
    // send it
    rc = mnvaCom4thGen(mf, buff, tools_open_bar_size_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, 0);
    // check rc
    if (rc) {
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get BAR size configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_bar_size_unpack(&barSzTlv, buff);
    _logBarSz = barSzTlv.log_uar_bar_size;
    _updated = true;

    return MCE_SUCCESS;
}

int BarSzParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    if (_logBarSz == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for BAR size.", err() ? err() : "");
    }

    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[tools_open_bar_size_size()];
    struct tools_open_bar_size barSzTlv;

    memset(buff, 0, tools_open_bar_size_size());
    memset(&barSzTlv, 0, sizeof(struct tools_open_bar_size));

    barSzTlv.log_uar_bar_size= _logBarSz;
    // pack it
    tools_open_bar_size_pack(&barSzTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_bar_size_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set BAR size params: %s",m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool BarSzParams4thGen::softLimitCheck(mfile* mf)
{
    u_int32_t numOfVfs = 0;
    int sriovEn;
    SriovParams4thGen sriovParams;

    if (!mf) {
        return false;
    }

    if (sriovParams.getDefaultAndFromDev(mf)) {
        errmsg("Failed to get SRIOV parameters from device: %s", sriovParams.err());
        return false;
    }

    numOfVfs = sriovParams.getParam(Mcp_Num_Of_Vfs);
    sriovEn = sriovParams.getParam(Mcp_Sriov_En);

    if (numOfVfs== MLXCFG_UNKNOWN || numOfVfs == MLXCFG_UNKNOWN) {
        errmsg("Illegal SRIOV parameters values");
        return false;
    }

    if (sriovEn == 0) {
        return true;
    }
    // this is the default log2 bar size , we require numOfVfs*(2^log_uar_bar) <= 512 or else the node might not boot
    double TotalMem = (numOfVfs+1)*(1 << _logBarSz);
    //printf("-D- num_of_vfs*2^(bar_sz+1) = %d*2^%ld = %d\n", _numOfVfs, data, (int)(_numOfVfs*(std::pow((double)2, (int)data))));
    //printf("-D- maxVfs(default set by fw) : %d\n", _maxVfs);

    if (TotalMem > 512){
        unsigned int maxAlowedLogBarSz =static_cast<unsigned int>(log2((512/(numOfVfs + 1 ))));
        errmsg("illegal Bar Size parameter value. Maximal allowed bar size: %d", maxAlowedLogBarSz < _maxLogBarSz ? maxAlowedLogBarSz : _maxLogBarSz);
        return false;
    }
    return true;
}

/*
 * BarSzParams5thGen Class implementation :
 */
bool BarSzParams5thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return false;
}

int BarSzParams5thGen::getDefaultParams(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int BarSzParams5thGen::getDefaultBarSz(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int BarSzParams5thGen::getFromDev(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

int BarSzParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    (void)mf;
    (void)ignoreCheck;
    return MCE_NOT_IMPLEMENTED;
}

bool BarSzParams5thGen::softLimitCheck(mfile* mf)
{
    (void)mf;
    return MCE_NOT_IMPLEMENTED;
}

/*
 *  VpiParams Class implementation :
 */

int VpiParams::getFromDevComPre()
{
    // prep tlv
    _tlvBuff.resize(TOOLS_OPEN_VPI_SETTINGS_SIZE);
    memset(&_tlvBuff[0], 0, TOOLS_OPEN_VPI_SETTINGS_SIZE);
    memset(&_vpiTlv, 0, sizeof(struct tools_open_vpi_settings));
    // pack it
    tools_open_vpi_settings_pack(&_vpiTlv, &_tlvBuff[0]);
    return MCE_SUCCESS;
}

int VpiParams::getFromDevComPost(MError mnvaComRC)
{
    if (mnvaComRC) {
         if (mnvaComRC == ME_REG_ACCESS_RES_NOT_AVLBL) {
             return MCE_SUCCESS;
         }
         return errmsg("Failed to get VPI port%d configuration: %s", _port, m_err2str(mnvaComRC));
     }
     // unpack and update
     tools_open_vpi_settings_unpack(&_vpiTlv, &_tlvBuff[0]);
     _linkType = _vpiTlv.network_link_type;
     _defaultLinkType = _vpiTlv.default_link_type;
     _updated = true;
     return MCE_SUCCESS;

}

int VpiParams::setOnDevComPre(bool ignoreCheck)
{
    if (_linkType == MLXCFG_UNKNOWN || _defaultLinkType == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for VPI settings.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    _tlvBuff.resize(TOOLS_OPEN_VPI_SETTINGS_SIZE);
     memset(&_tlvBuff[0], 0, _tlvBuff.size());
     memset(&_vpiTlv, 0, sizeof(struct tools_open_vpi_settings));
     _vpiTlv.network_link_type = _linkType;
     _vpiTlv.default_link_type = _defaultLinkType;
     // pack it
     tools_open_vpi_settings_pack(&_vpiTlv, &_tlvBuff[0]);
    return MCE_SUCCESS;
}

int VpiParams::setOnDevComPost(MError mnvaComRC)
{
    if (mnvaComRC) {
        return errmsg("failed to set VPI port%d params: %s", _port, m_err2str(mnvaComRC));
    }
    _updated = false;
    return MCE_SUCCESS;
}

/*
 *  VpiParams4thGen Class implementation :
 */
void VpiParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        _linkType = val;
    }
}

u_int32_t VpiParams4thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _linkType;
    }
    return MLXCFG_UNKNOWN;
}

bool VpiParams4thGen::cfgSupported(mfile* mf)
{
    (void)mf;
    return ((_devCapVec & VPI_P1_MASK) && _port == 1) || ((_devCapVec & VPI_P2_MASK) && _port == 2);
}

int VpiParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port port_params;
    _defaultLinkType = 0; // not used for 4th gen devices , we give it a default value
    int rc = getDefaultParams4thGen(mf, _port , &port_params);
    if (rc) {
        return MCE_GET_DEFAULT_PARAMS;
    }
    if (port_params.network_link_type) {
        _linkType = port_params.network_link_type;
    }
    return MCE_SUCCESS;
}

int VpiParams4thGen::getFromDev(mfile* mf)
{
    MError mRc;
    int rc;

    if (_updated) {
        return MCE_SUCCESS;
    }
    if((rc = getFromDevComPre())) {
        return rc;
    }
    mRc = mnvaCom4thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);
    return getFromDevComPost(mRc);
}

int VpiParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;
    int rc;

    if ((rc = setOnDevComPre(ignoreCheck))) {
        return rc;
    }
    mRc = mnvaCom4thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, tlvTypeIdx, REG_ACCESS_METHOD_SET, _port);
    return setOnDevComPost(mRc);
}

bool VpiParams4thGen::hardLimitCheck()
{
    if (_linkType == 1 || _linkType == 2 || _linkType == 3 ) {
        return true;
    }
    errmsg("illegal VPI link type (should be 1|2|3).");
    return false;
}

/*
 *  VpiParams5thGen Class implementation :
 */
void VpiParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        _defaultLinkType = val;
    }
}

u_int32_t VpiParams5thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _defaultLinkType;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t VpiParams5thGen::getTlvTypeBe()
{
    struct tools_open_per_port_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_PHYS_PORT;
    type.param_idx = tlvTypeIdx;
    type.port = _port;
    tools_open_per_port_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

bool VpiParams5thGen::cfgSupported(mfile* mf)
{
    // get mtcr functions for this device (physical)
    // compare with port
    // send nvqc and check
    MError rc;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get VPI params capabilites. %s", m_err2str(rc));
        return false;
    }
    return suppRead && suppWrite;
}

int VpiParams5thGen::getDefaultParams(mfile* mf)
{
    // if configuration is supported then network link type must be 3
    _linkType = 3;
    return getFromDev(mf);
}

int VpiParams5thGen::getFromDev(mfile* mf)
{
    MError mRc;
    int rc;

    if (_updated) {
        return MCE_SUCCESS;
    }
    if((rc = getFromDevComPre())) {
        return rc;
    }
    mRc = mnvaCom5thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, getTlvTypeBe(), REG_ACCESS_METHOD_GET);
    return getFromDevComPost(mRc);
}

int VpiParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;
    int rc;

    if ((rc = setOnDevComPre(ignoreCheck))) {
        return rc;
    }
    mRc = mnvaCom5thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, getTlvTypeBe(), REG_ACCESS_METHOD_SET);
    return setOnDevComPost(mRc);
}

bool VpiParams5thGen::hardLimitCheck()
{
    if (_defaultLinkType == 1 || _defaultLinkType == 2 ) {
        return true;
    }
    errmsg("illegal VPI link type (should be 1|2).");
    return false;
}

/*
 * PciParams5thGen Class implementation:
 */

// Adrianc: atm we check only for SRIOV support.
// need to add mechanism to check support for a specific parameter.
bool PciParams5thGen::cfgSupported(mfile* mf)
{
    MError rc;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getPciCapabilitiesTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get PCI capabilities parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead) {
        return false;
    }

    if (getDefaultsAndCapabilities(mf) != MCE_SUCCESS) {
        return false;
    }

    if (!_sriovSupported && !_fppSupported) {
        return false;
    }

    rc = nvqcCom5thGen(mf, getPciSettingsTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get PCI settings parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    return suppRead&suppWrite;
}

void PciParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Sriov_En) {
        _sriovEn = val;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        _numOfVfs = val;
    } else if (paramType == Mcp_Fpp_En) {
        _fppEn = val;
    }
}

u_int32_t PciParams5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEn;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfs;
    } else if (paramType == Mcp_Fpp_En) {
        return _fppEn;
    }

    return MLXCFG_UNKNOWN;
}

int PciParams5thGen::getFromDev(mfile* mf)
{
    MError mRc;
    u_int8_t tlvBuff[TOOLS_OPEN_PCI_CONFIGURATION_SIZE] = {0};
    struct tools_open_pci_configuration pciSettingsTlv;
    memset(&pciSettingsTlv, 0, sizeof(pciSettingsTlv));

    if (_updated) {
        return MCE_SUCCESS;
    }

    mRc = mnvaCom5thGen(mf, &tlvBuff[0], TOOLS_OPEN_PCI_CONFIGURATION_SIZE, getPciSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET);

    if (mRc) {
        if (mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get PCI configuration: %s", m_err2str(mRc));
    }
    // unpack and update
    tools_open_pci_configuration_unpack(&pciSettingsTlv, &tlvBuff[0]);
    if (pciSettingsTlv.sriov_valid) {
        _sriovEn = pciSettingsTlv.sriov_en;
        _numOfVfs = pciSettingsTlv.total_vfs;
        _updated = true;
    }
    if (pciSettingsTlv.fpp_valid) {
        _fppEn = pciSettingsTlv.fpp_en;
        _updated = true;
    }
   return MCE_SUCCESS;
}

int PciParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;

    if (_fppEn == MLXCFG_UNKNOWN && (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN)) {
        return errmsg("%s please specify all the parameters for SRIOV settings.", err() ? err() : "");
    }

    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    // get Tlv modify it and set it
    u_int8_t tlvBuff[TOOLS_OPEN_PCI_CONFIGURATION_SIZE] = {0};
    struct tools_open_pci_configuration pciSettingsTlv;
    memset(&pciSettingsTlv, 0, sizeof(pciSettingsTlv));

    mRc = mnvaCom5thGen(mf, tlvBuff, TOOLS_OPEN_PCI_CONFIGURATION_SIZE, getPciSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (mRc && mRc != ME_REG_ACCESS_RES_NOT_AVLBL) {
        return errmsg("failed to set PCI settings: %s", m_err2str(mRc));
    }
    tools_open_pci_configuration_unpack(&pciSettingsTlv, tlvBuff);

    if (_sriovSupported) {
        pciSettingsTlv.sriov_valid = 1;
        pciSettingsTlv.sriov_en = _sriovEn;
        pciSettingsTlv.total_vfs = _numOfVfs;
    } else if (pciSettingsTlv.sriov_valid && pciSettingsTlv.sriov_en != _sriovEn) {
        return errmsg("SRIOV_EN is not configurable!");
    }
    if (_fppSupported) {
        pciSettingsTlv.fpp_en = _fppEn;
        pciSettingsTlv.fpp_valid = 1;
    } else if (pciSettingsTlv.fpp_valid && pciSettingsTlv.fpp_en != _fppEn) {
        return errmsg("FPP_EN is not configurable!");
    }

    if (pciSettingsTlv.sriov_en && !pciSettingsTlv.fpp_en) {
        return errmsg("FPP should be enabled while SRIOV is enabled");
    }
    /* Turning on FPP where num of PFs < 2 in devices with dual ports (max pfs > 1)
     * should apply numOfPfs to 2 */
    if (pciSettingsTlv.fpp_en && _numPfsSupported && (_maxNumPfs > 1)  && (pciSettingsTlv.num_pfs < 2)) {
        pciSettingsTlv.num_pfs = 2;
    }
    // pack it
    tools_open_pci_configuration_pack(&pciSettingsTlv, tlvBuff);

    mRc = mnvaCom5thGen(mf, tlvBuff, TOOLS_OPEN_PCI_CONFIGURATION_SIZE, getPciSettingsTlvTypeBe(), REG_ACCESS_METHOD_SET);

    if (mRc) {
        return errmsg("failed to set PCI settings: %s", m_err2str(mRc));
    }
    _updated = false;

    return MCE_SUCCESS;
}

int PciParams5thGen::getDefaultParams(mfile* mf)
{
    return getDefaultsAndCapabilities(mf);
}

int PciParams5thGen::getDefaultsAndCapabilities(mfile* mf)
{
    MError rc;
    u_int8_t tlvBuff[TOOLS_OPEN_PCI_CAPABILITIES_SIZE] = {0};
    struct tools_open_pci_capabilities pciCapabilitesTlv;
    memset(&pciCapabilitesTlv, 0, sizeof(pciCapabilitesTlv));
    rc = mnvaCom5thGen(mf, &tlvBuff[0], TOOLS_OPEN_PCI_CAPABILITIES_SIZE, getPciCapabilitiesTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (rc) {
        return errmsg("Failed to get PCI capabilities parameter. %s", m_err2str(rc));
    }
    tools_open_pci_capabilities_unpack(&pciCapabilitesTlv, tlvBuff);
    _sriovSupported = pciCapabilitesTlv.sriov_support;
    _maxVfsPerPf = pciCapabilitesTlv.max_vfs_per_pf_valid ? pciCapabilitesTlv.max_vfs_per_pf : 0;
    _fppSupported = pciCapabilitesTlv.fpp_support;
    _numPfsSupported = pciCapabilitesTlv.num_pfs_supported;
    _maxNumPfs = pciCapabilitesTlv.max_num_pfs;

    return MCE_SUCCESS;
}

u_int32_t PciParams5thGen::getPciSettingsTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = tlvTypeIdx;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t PciParams5thGen::getPciCapabilitiesTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = PCI_CAPABILITES_TYPE;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

bool PciParams5thGen::hardLimitCheck()
{
    if ((_numOfVfs > _maxVfsPerPf)) {
        errmsg("Number of VFs exceeds limit (%d).", _maxVfsPerPf);
        return false;
    }

    if (_sriovEn != 0 && _sriovEn != 1) {
        errmsg("Illegal SRIOV_EN parameters value. (should be 0 or 1)");
        return false;
    }

    if (_fppEn != 0 && _fppEn != 1) {
        errmsg("Illegal FPP_EN parameters value. (should be 0 or 1)");
        return false;
    }


    return true;
}
