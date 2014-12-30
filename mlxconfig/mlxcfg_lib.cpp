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
/*
 * mlxcfg_lib.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: adrianc
 */

#include <set>
#include <cmath>
#include <signal.h>

#include <mft_sig_handler.h>
#include <tools_layouts/tools_open_layouts.h>
#include <reg_access/reg_access.h>
#include <bit_slice.h>
#include <cmdif/tools_cif.h>
#include <mtcr.h>


#include "mlxcfg_lib.h"

using namespace std;

/*
 * Mask and offsets for working with the capability vector
 * retrieved via query_dev_cap command.
 */
#define SRIOV_MASK 0x1
#define WOL_P1_MASK 0x2
#define WOL_P2_MASK 0x4
#define VPI_P1_MASK 0x8
#define VPI_P2_MASK 0x10
#define BAR_SZ_MASK 0x20

#define TOOL_CAP_BITS_ADDR 0xc0
#define MAX_VFS_ADDR 0x38
#define MAX_BAR_SZ_ADDR 0xc8
#define DEFAULT_BAR_SZ_ADDR 0x48

/*
 * Debug print MACRO of the MNV Tlvs:
 */
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
/*
 * Enum for handling error messages
 */

typedef enum {
    MCE_SUCCESS = 0,
    MCE_FAILED,
    MCE_TLV_NOT_FOUND,
    MCE_TLV_NOT_SUPP,
    MCE_NVCFG_NOT_SUPP,
    MCE_TOOLS_HCR_NOT_SUPP,
    MCE_DRIVER_DOWN,
    MCE_UNSUPPORTED_DEVICE,
    MCE_UNSUPPORTED_CFG,
    MCE_BAD_PARAMS,
    MCE_BAD_PARAM_VAL,
    MCE_DEV_BUSY,
    MCE_UNKNOWN_TLV,
    MCE_REG_NOT_SUPP,
    MCE_METHOD_NOT_SUPP,
    MCE_RES_NOT_AVAIL,
    MCE_CONF_CORRUPT,
    MCE_TLV_LEN_TOO_SMALL,
    MCE_BAD_CONFIG,
    MCE_ERASE_EXEEDED,
    MCE_BAD_OP,
    MCE_BAD_STATUS,
    MCE_CR_ERROR,
    MCE_NOT_IMPLEMENTED,
    MCE_INCOMPLETE_PARAMS,
    MCE_OPEN_DEVICE,
    MCE_PCI,
    MCE_GET_DEFAULT_PARAMS,
    MCE_UNKNOWN_ERR
}McStatus;

/*
 * Forward Declarations:
 */

static MError mnvaCom(mfile* mf, u_int8_t* buff, u_int16_t len, u_int16_t type, reg_access_method_t method, u_int16_t typeMod=0);

/*
 *  MlxCfgOps::CfgParams implementation
 */

MlxCfgOps::CfgParams::CfgParams(mlxCfgType t, u_int32_t tlvT) {
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
    tlvType = tlvT;
    _updated = false;
    _ignoreHardLimits = false;
    _ignoreSoftLimits = false;
}

int MlxCfgOps::CfgParams::getDefaultParams4thGen(mfile* mf, struct tools_open_query_def_params_global* global_params)
{
    MError rc  = tcif_query_global_def_params(mf, global_params);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::CfgParams::getDefaultParams4thGen(mfile* mf, int port, struct tools_open_query_def_params_per_port* port_params)
{
    MError rc  = tcif_query_per_port_def_params(mf, port, port_params);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::CfgParams::getDefaultAndFromDev(mfile* mf)
{
    int rc;
    rc = getDefaultParams(mf); CHECK_RC(rc);
    rc = getFromDev(mf); CHECK_RC(rc);
    return MCE_SUCCESS;
}

bool MlxCfgOps::CfgParams::checkCfg(mfile* mf)
{
    if (!_ignoreHardLimits && !hardLimitCheck()) {
        return false;
    }
    if (!_ignoreSoftLimits && !softLimitCheck(mf)) {
        return false;
    }
    return true;
}

bool MlxCfgOps::CfgParams::softLimitCheck(mfile* mf)
{
    // by default not implemented
    (void)mf;
    return true;
}

void MlxCfgOps::CfgParams::setIgnoreSoftLimits(bool val)
{
    _ignoreSoftLimits = val;
}
void MlxCfgOps::CfgParams::setIgnoreHardLimits(bool val)
{
    _ignoreHardLimits = val;
}
/*
 * MlxCfgOps::SriovParams implementation
 */

int MlxCfgOps::SriovParams::getDefaultParams(mfile* mf)
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

void MlxCfgOps::SriovParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Sriov_En) {
        _sriovEn = val;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        _numOfVfs = val;
    }
}

u_int32_t MlxCfgOps::SriovParams::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEn;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfs;
    }
    return MLXCFG_UNKNOWN;
}


int MlxCfgOps::SriovParams::getFromDev(mfile* mf)
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
    rc = mnvaCom(mf, buff, tools_open_sriov_size(), tlvType, REG_ACCESS_METHOD_GET, 0);
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

int MlxCfgOps::SriovParams::setOnDev(mfile* mf, bool ignoreCheck)
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
    ret = mnvaCom(mf, buff, tools_open_sriov_size(), tlvType, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set SRIOV params: %s",m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

int MlxCfgOps::SriovParams::updateMaxVfs(mfile* mf)
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

bool MlxCfgOps::SriovParams::hardLimitCheck()
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

bool MlxCfgOps::SriovParams::softLimitCheck(mfile* mf)
{
    u_int32_t barSz = 0;
    BarSzParams barParams;

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
 * MlxCfgOps::WolParams implementation
 */

int MlxCfgOps::WolParams::getDefaultParams(mfile* mf)
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

void MlxCfgOps::WolParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Wol_Magic_En_P1 && _port == 1 ) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2) ) {
        _wolMagicEn = val;
    }
}

u_int32_t MlxCfgOps::WolParams::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Wol_Magic_En_P1 && _port == 1 ) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2) ) {
        return _wolMagicEn;
    }
    return MLXCFG_UNKNOWN;
}

int MlxCfgOps::WolParams::getFromDev(mfile* mf)
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
    rc = mnvaCom(mf, buff, tools_open_wol_size(), tlvType, REG_ACCESS_METHOD_GET, _port);
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

int MlxCfgOps::WolParams::setOnDev(mfile* mf, bool ignoreCheck)
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
    ret = mnvaCom(mf, buff, tools_open_wol_size(), tlvType, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (ret) {
        return errmsg("failed to set WOL params for port%d: %s", _port, m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool MlxCfgOps::WolParams::hardLimitCheck()
{
    if (_wolMagicEn == 0 || _wolMagicEn == 1 ) {
        return true;
    }
    errmsg("illegal WOL parameter value. can be either 0 or 1.");
    return false;
}

/*
 *  BarSzParams Implementation
 */

int MlxCfgOps::BarSzParams::getDefaultParams(mfile* mf)
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

int MlxCfgOps::BarSzParams::getDefaultBarSz(mfile* mf)
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

void MlxCfgOps::BarSzParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Log_Bar_Size) ) {
        _logBarSz = val;
    }
}

u_int32_t MlxCfgOps::BarSzParams::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Bar_Size) {
        return _logBarSz;
    }
    return MLXCFG_UNKNOWN;
}

int MlxCfgOps::BarSzParams::getFromDev(mfile* mf)
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
    rc = mnvaCom(mf, buff, tools_open_bar_size_size(), tlvType, REG_ACCESS_METHOD_GET, 0);
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

int MlxCfgOps::BarSzParams::setOnDev(mfile* mf, bool ignoreCheck)
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
    ret = mnvaCom(mf, buff, tools_open_bar_size_size(), tlvType, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set BAR size params: %s",m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool MlxCfgOps::BarSzParams::hardLimitCheck()
{
    if (_logBarSz > _maxLogBarSz ) {
        errmsg("given bar size is too large, max allowed log2 bar size: 0x%x", _maxLogBarSz);
        return false;
    }
    return true;
}


bool MlxCfgOps::BarSzParams::softLimitCheck(mfile* mf)
{
    u_int32_t numOfVfs = 0;
    int sriovEn;
    SriovParams sriovParams;

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
 *  VpiParams Implementation
 */

int MlxCfgOps::VpiParams::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port port_params;
    int rc = getDefaultParams4thGen(mf, _port , &port_params);
    if (rc) {
        return MCE_GET_DEFAULT_PARAMS;
    }
    _linkType = port_params.network_link_type;
    return MCE_SUCCESS;
}

void MlxCfgOps::VpiParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        _linkType = val;
    }
}

u_int32_t MlxCfgOps::VpiParams::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _linkType;
    }
    return MLXCFG_UNKNOWN;
}

int MlxCfgOps::VpiParams::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[tools_open_vpi_settings_size()];
    struct tools_open_vpi_settings vpiTlv;
    memset(buff, 0, tools_open_vpi_settings_size());
    memset(&vpiTlv, 0, sizeof(struct tools_open_vpi_settings));
    // pack it
    tools_open_vpi_settings_pack(&vpiTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_open_vpi_settings_size(), tlvType, REG_ACCESS_METHOD_GET, _port);
    // check rc
    if (rc) {
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get VPI port%d configuration: %s", _port, m_err2str(rc));
    }
    // unpack and update
    tools_open_vpi_settings_unpack(&vpiTlv, buff);
    _linkType = vpiTlv.network_link_type;
    _updated = true;

    return MCE_SUCCESS;
}

int MlxCfgOps::VpiParams::setOnDev(mfile* mf, bool ignoreCheck)
{
    if (_linkType == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for VPI settings.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[tools_open_vpi_settings_size()];
    struct tools_open_vpi_settings vpiTlv;

    memset(buff, 0, tools_open_vpi_settings_size());
    memset(&vpiTlv, 0, sizeof(struct tools_open_vpi_settings));

    vpiTlv.network_link_type= _linkType;
    // pack it
    tools_open_vpi_settings_pack(&vpiTlv, buff);
    // send it
    ret = mnvaCom(mf, buff, tools_open_vpi_settings_size(), tlvType, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (ret) {
        return errmsg("failed to set VPI port%d params: %s", _port, m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool MlxCfgOps::VpiParams::hardLimitCheck()
{
    if (_linkType == 1 || _linkType == 2 || _linkType == 3 ) {
        return true;
    }
    errmsg("illegal VPI link type (should be 1|2|3).");
    return false;
}

/*
 * MlxCfgOps implementation
 */

MlxCfgOps::MlxCfgOps()
{
    // init the ErrMsg Class
    std::map<int, std::string> errmap;
    errmap[MCE_SUCCESS] = "Success";
    errmap[MCE_FAILED] = "General Failure";
    errmap[MCE_TLV_NOT_FOUND] = "Configuration not found";
    errmap[MCE_TLV_NOT_SUPP] = "Configuration TLV not supported";
    errmap[MCE_NVCFG_NOT_SUPP] = "Fw does not support NV access registers";
    errmap[MCE_TOOLS_HCR_NOT_SUPP] = "Unsupported FW (version 2.31.5000 or above required for CX3/PRO)";
    errmap[MCE_DRIVER_DOWN] = "Cannot perform operation, Driver might be down.";
    errmap[MCE_UNSUPPORTED_DEVICE] = "Device not supported.";
    errmap[MCE_UNSUPPORTED_CFG] = "Fw does not support configuration";
    errmap[MCE_BAD_PARAMS] = "Bad parameters";
    errmap[MCE_BAD_PARAM_VAL] = "Bad parameter value";
    errmap[MCE_DEV_BUSY] = "Device busy";
    errmap[MCE_UNKNOWN_TLV] = "Unknown TLV";
    errmap[MCE_REG_NOT_SUPP] = "Fw does not support NV access registers";
    errmap[MCE_METHOD_NOT_SUPP] = "Method not supported";
    errmap[MCE_RES_NOT_AVAIL] = "Resource not available";
    errmap[MCE_CONF_CORRUPT] = "Configuration is corrupted";
    errmap[MCE_TLV_LEN_TOO_SMALL] = "TLV length too small";
    errmap[MCE_BAD_CONFIG] = "Bad Configuration";
    errmap[MCE_ERASE_EXEEDED] = "Erase exceeded flash spec";
    errmap[MCE_BAD_OP] = "Bad Operation";
    errmap[MCE_BAD_STATUS] = "General Failure";
    errmap[MCE_CR_ERROR] = "CR-Error";
    errmap[MCE_NOT_IMPLEMENTED] = "Not implemented";
    errmap[MCE_INCOMPLETE_PARAMS] = "Failed to get missing configuration from device, please specify all the needed parameters";
    errmap[MCE_OPEN_DEVICE] = "Failed to open device";
    errmap[MCE_PCI] = "Access to device should be through PCI interface only";
    errmap[MCE_GET_DEFAULT_PARAMS] = "Failed to get default params";
    errmap[MCE_UNKNOWN_ERR] = "General Error";

    updateErrCodes(errmap);
    _mf = NULL;
    _suppVec = 0;
    _cfgList.resize(Mct_Last);
    _cfgList[Mct_Sriov] = new SriovParams();
    _cfgList[Mct_Wol_P1] = new WolParams(1);
    _cfgList[Mct_Wol_P2] = new WolParams(2);
    _cfgList[Mct_Vpi_P1] = new VpiParams(1);
    _cfgList[Mct_Vpi_P2] = new VpiParams(2);
    _cfgList[Mct_Bar_Size] = new BarSzParams();
    return;
}

MlxCfgOps::~MlxCfgOps()
{
    if (_mf) {
        mclose(_mf);
    }
    for(vector<CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        delete *it;
    }
    return;
}

#define HW_ID_ADDR 0xf0014
#define CX3_HW_ID 501
#define CX3_PRO_HW_ID 503

int MlxCfgOps::supportsToolsHCR()
{
    // we also update the support vector
    u_int32_t devId;
    u_int32_t type = 0;
    int rc;

    if (mread4(_mf, HW_ID_ADDR, &devId) != 4) {
        return MCE_CR_ERROR;
    }
    switch (devId & 0xffff) { // check hw device id
         case CX3_HW_ID : //Cx3
         case CX3_PRO_HW_ID : // Cx3-pro
             // check if device is accessed via pci (thats the only supported method atm)
            rc = mget_mdevs_type(_mf, &type);
        #ifndef MST_UL
            if (type != MST_PCICONF && type != MST_PCI) {
                return errmsg(MCE_PCI);
            }
        #else
            if (type != MTCR_ACCESS_CONFIG && type != MTCR_ACCESS_MEMORY) {
                return errmsg(MCE_PCI);
            }
        #endif
            // check if we support tools_hcr
             rc = tcif_query_dev_cap(_mf, TOOL_CAP_BITS_ADDR, &_suppVec);
             switch (rc) {
             case ME_OK:
                 return MCE_SUCCESS;
             case ME_CMDIF_BAD_SYS:
                 return errmsg(MCE_DRIVER_DOWN);
             case ME_CMDIF_BAD_OP:
             case ME_CMDIF_TOUT:
             case ME_CMDIF_BUSY:
                 return errmsg(MCE_TOOLS_HCR_NOT_SUPP);
             default:
                 return errmsg("general Error, %s", m_err2str((MError)rc));
             }
             break;
         default:
             break;
         }
    return errmsg(MCE_UNSUPPORTED_DEVICE);
}

int MlxCfgOps::openComChk()
{
    bool rc;
    int ret;
    // check if we support Tools HCR and update _suppVec
    rc = supportsToolsHCR(); CHECK_RC(rc);

    // update cfg specific info.
    for (int i = Mct_Sriov; i < Mct_Last; i++) {
        ret = _cfgList[i]->getDefaultParams(_mf);
        if (ret && ret!= MCE_GET_DEFAULT_PARAMS) {
            return ret;
        }
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::open(const char* devStr, bool forceClearSem)
{
    _mf = mopen(devStr);
    if (_mf == NULL) {
        return errmsg(MCE_OPEN_DEVICE);
    }

    return opend(_mf , forceClearSem);
}

int MlxCfgOps::opend(mfile* mf, bool forceClearSem)
{
    if (!mf) {
        return errmsg(MCE_BAD_PARAMS);
    }
    _mf = mf;

    if (forceClearSem) {
        int rc = tools_cmdif_unlock_semaphore(_mf);
        if (rc) {
            return errmsg("failed to unlock semaphore, %s.", m_err2str((MError)rc));
        }
    }
    return openComChk();
}

bool MlxCfgOps::supportsCfg(mlxCfgType cfg)
{
    if (!isLegal(cfg)) {
        return false;
    }

    return _suppVec & cfgSuppMask[cfg];
}

bool MlxCfgOps::supportsParam(mlxCfgParam param)
{
    if (!isLegal(param)) {
        return false;
    }
    return supportsCfg(cfgParam2Type(param));
}

int MlxCfgOps::getCfg(mlxCfgParam cfgParam, u_int32_t& val)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }
    int rc = _cfgList[cfgParam2Type(cfgParam)]->getFromDev(_mf);
    if (rc) {
        return errmsgConcatMsg(rc,*_cfgList[cfgParam2Type(cfgParam)]);
    }
    val = (_cfgList[cfgParam2Type(cfgParam)])->getParam(cfgParam);
    return MCE_SUCCESS;
}

int MlxCfgOps::getCfg(std::vector<cfgInfo>& infoVec)
{
    for (std::vector<cfgInfo>::iterator it = infoVec.begin() ; it != infoVec.end(); it++) {
        int rc = getCfg(it->first,it->second);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::setCfg(mlxCfgParam cfgParam, u_int32_t val)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }
    // get parameters from device if present
    int rc = _cfgList[cfgParam2Type(cfgParam)]->getFromDev(_mf);
    if (rc) {
        return errmsgConcatMsg(rc, *_cfgList[cfgParam2Type(cfgParam)]);
    }
    _cfgList[cfgParam2Type(cfgParam)]->setParam(cfgParam, val);
    rc = _cfgList[cfgParam2Type(cfgParam)]->setOnDev(_mf);
    if (rc) {
        return errmsgConcatMsg(rc, *_cfgList[cfgParam2Type(cfgParam)]);
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::setCfg(const std::vector<cfgInfo>& infoVec)
{
    // set params
    std::set<CfgParams*> CfgToSet;
    int rc;

    for (std::vector<cfgInfo>::const_iterator it = infoVec.begin() ; it != infoVec.end(); it++) {
        if (!isLegal(it->first)) {
            return MCE_BAD_PARAMS;
        }
        if (!supportsParam(it->first)) {
            return errmsg(MCE_UNSUPPORTED_CFG);
        }
        // get configuration from device first (if preset) in case of multiple params per type
        rc = _cfgList[cfgParam2Type(it->first)]->getFromDev(_mf);
        if (rc) {
            return errmsgConcatMsg(rc, *_cfgList[cfgParam2Type(it->first)]);
        }
        _cfgList[cfgParam2Type(it->first)]->setParam(it->first, it->second);
        CfgToSet.insert(_cfgList[cfgParam2Type(it->first)]);
    }
    //set on device exit on first failure
    for (std::set<CfgParams*>::iterator it = CfgToSet.begin() ; it != CfgToSet.end(); it++) {
        rc = (*it)->setOnDev(_mf);
        if (rc) {
            return errmsgConcatMsg(rc, (**it));
        }
    }
    return MCE_SUCCESS;
}

void MlxCfgOps::setIgnoreSoftLimits(bool val)
{
    for(std::vector<CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        (*it)->setIgnoreSoftLimits(val);
    }
    return;
}

void MlxCfgOps::setIgnoreHardLimits(bool val)
{
    for(std::vector<CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        (*it)->setIgnoreHardLimits(val);
    }
    return;
}

int MlxCfgOps::invalidateCfgs()
{

    struct tools_open_mnvia mnviaTlv;
    u_int8_t buffer[tools_open_mnvia_size()];
    memset(&mnviaTlv, 0, sizeof(struct tools_open_mnvia));
    memset(buffer, 0, tools_open_mnvia_size());

    mnviaTlv.mnv_hdr.length = 0;
    mnviaTlv.mnv_hdr.type = 0;
    mnviaTlv.mnv_hdr.type_mod = 0;
    tools_open_mnvia_pack(&mnviaTlv, buffer);
    MError rc;
    rc = reg_access_mnvia(_mf, REG_ACCESS_METHOD_SET, &mnviaTlv);
    if (rc) {
        return errmsg("failed to invalidate configurations, %s.", m_err2str(rc));
    }
    return MCE_SUCCESS;
}

bool MlxCfgOps::isLegal(mlxCfgType cfg)
{
    if (cfg >= Mct_Sriov && cfg < Mct_Last) {
        return true;
    }
    errmsg("illegal configuration");
    return false;
}

bool MlxCfgOps::isLegal(mlxCfgParam cfg)
{
    if (cfg >= Mcp_Sriov_En && cfg < Mcp_Last) {
        return true;
    }
    errmsg("illegal configuration parameter");
    return false;
}

u_int64_t MlxCfgOps::cfgSuppMask[Mct_Last] = {SRIOV_MASK, WOL_P1_MASK, WOL_P2_MASK , VPI_P1_MASK, VPI_P2_MASK, BAR_SZ_MASK};

mlxCfgType MlxCfgOps::cfgParam2Type(mlxCfgParam param)
{
    switch (param) {
    case Mcp_Sriov_En :
        return Mct_Sriov;
    case Mcp_Num_Of_Vfs :
        return Mct_Sriov;
    case Mcp_Wol_Magic_En_P1 :
        return Mct_Wol_P1;
    case Mcp_Wol_Magic_En_P2 :
        return Mct_Wol_P2;
    case Mcp_Link_Type_P1 :
        return Mct_Vpi_P1;
    case Mcp_Link_Type_P2 :
        return Mct_Vpi_P2;
    case Mcp_Log_Bar_Size :
        return Mct_Bar_Size;
    default :
            return Mct_Last;
    }
}

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

MError mnvaCom(mfile* mf, u_int8_t* buff, u_int16_t len, u_int16_t type, reg_access_method_t method, u_int16_t typeMod)
{
    struct tools_open_mnva mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_mnva));

    mnvaTlv.mnv_hdr.length = len >> 2; // length is in dwords
    mnvaTlv.mnv_hdr.type = type;
    mnvaTlv.mnv_hdr.type_mod = typeMod;
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

