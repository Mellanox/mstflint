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
    MCE_PCICONF,
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

    updateErrCodes(errmap);
    type = t;
    tlvType = tlvT;
    _updated = false;
}

/*
 * MlxCfgOps::SriovParams implementation
 */

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
    _sriovEn = _sriovEn == MLXCFG_UNKNOWN ? sriovTlv.sriov_en : _sriovEn ;
    _numOfVfs = _numOfVfs == MLXCFG_UNKNOWN ? sriovTlv.total_vfs : _numOfVfs ;
    _updated = true;

    return MCE_SUCCESS;
}

int MlxCfgOps::SriovParams::setOnDev(mfile* mf, bool ignoreCheck)
{
    int rc;
    if (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc || _sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) { // go here if we fail to get the tlv or it doesnt exsist (one of the params == MLXCFG_UNKNOWN)
            return errmsg("%s please specify all the parameters for SRIOV.", err() ? err(): "");
        }
    }
    if (!ignoreCheck && !isLegal(mf)) {
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
    int rc = tools_cmdif_query_dev_cap(mf, MAX_VFS_ADDR, &data);
    if (rc) {
        return errmsg("failed to query device capabilities: %s", m_err2str((MError)rc));
    }
    _maxVfs = (u_int32_t)(data & 0xff);
    if (_maxVfs == 0) { // defined in CX PRM , if max_func_idx=0 then all functions(128) are operational
        _maxVfs = 128;
    }
    return MCE_SUCCESS;
}

bool MlxCfgOps::SriovParams::isLegal(mfile* mf)
{
    if (!mf) {
        return false;
    }
    u_int64_t data = 0;
    int rc = tools_cmdif_query_dev_cap(mf, DEFAULT_BAR_SZ_ADDR, &data);
    if (rc) {
        errmsg("failed to query device capabilities: %s",m_err2str((MError)rc));
        return false;
    }
    data = EXTRACT64(data,16,6) + 1; // this is the default log2 bar size , we require numOfVfs*(2^log_uar_bar) <= 512 or else the node might not boot
    double VfsMem = _numOfVfs*(std::pow((double)2, (int)data));
    //TODO: when bar_size tlv will be supported, we need to change this to the current bar_size (and also check with the current tlv bar size)
    //printf("-D- num_of_vfs*2^(bar_sz+1) = %d*2^%ld = %d\n", _numOfVfs, data, (int)(_numOfVfs*(std::pow((double)2, (int)data))));
    //printf("-D- maxVfs(default set by fw) : %d\n", _maxVfs);
    if (_sriovEn != 0 && _sriovEn != 1) {
        errmsg("illegal SRIOV_EN parameters value. (should be 0 or 1)");
        return false;
    }
    if ((_numOfVfs > _maxVfs) || (VfsMem > 512)){
        unsigned int maxAlowedVfs =static_cast<unsigned int>(512/(std::pow((double)2, (int)data)));
        errmsg("illegal SRIOV parameter value. Maximal number of VFs: %d", maxAlowedVfs < _maxVfs ? maxAlowedVfs : _maxVfs);
        return false;
    }
    return true;
}

/*
 * MlxCfgOps::WolParams implementation
 */

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
    _wolMagicEn = _wolMagicEn == MLXCFG_UNKNOWN ? wolTlv.en_wol_magic : _wolMagicEn ;
    _updated = true;

    return MCE_SUCCESS;
}

int MlxCfgOps::WolParams::setOnDev(mfile* mf, bool ignoreCheck)
{
    int rc;
    if (_wolMagicEn == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc || _wolMagicEn == MLXCFG_UNKNOWN) {
            return errmsg("%s please specify all the parameters for WOL.", err()? err() : "");
        }
    }
    if (!ignoreCheck && !isLegal()) {
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

bool MlxCfgOps::WolParams::isLegal(mfile* mf)
{
    (void)mf;
    if (_wolMagicEn == 0 || _wolMagicEn == 1 ) {
        return true;
    }
    errmsg("illegal WOL parameter value. can be either 0 or 1.");
    return false;
}

/*
 *  BarSzParams Implementation
 */

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
    _logBarSz = _logBarSz == MLXCFG_UNKNOWN ? barSzTlv.log_uar_bar_size : _logBarSz ;
    _updated = true;

    return MCE_SUCCESS;
}

int MlxCfgOps::BarSzParams::setOnDev(mfile* mf, bool ignoreCheck)
{
    int rc;
    if (_logBarSz == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc || _logBarSz == MLXCFG_UNKNOWN) {
            return errmsg("%s please specify all the parameters for BAR size.", err() ? err() : "");
        }
    }
    if (!ignoreCheck && !isLegal()) {
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

int MlxCfgOps::BarSzParams::updateBarSzInfo(mfile* mf)
{
    u_int64_t data = 0;
    int rc = tools_cmdif_query_dev_cap(mf, MAX_BAR_SZ_ADDR, &data);
    if (rc) {
        return errmsg("Failed to query device capabilities: %s", m_err2str((MError)rc));
    }
    _maxLogBarSz = (u_int32_t)(data & 0xffffffff);
    _currLogBarSz = (u_int32_t)(data >> 32);
    //printf("-D- vec 0x%lx  max %d  curr %d\n", data, maxBarSz, currBarSz);
    return MCE_SUCCESS;
}

bool MlxCfgOps::BarSzParams::isLegal(mfile* mf)
{
    (void)mf;
    if (_logBarSz < _maxLogBarSz ) {
        return true;
    }
    errmsg("given bar size is too large, max allowed log2 bar size: 0x%x", _maxLogBarSz);
    return false;
}

/*
 *  VpiParams Implementation
 */


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
    _linkType = _linkType == MLXCFG_UNKNOWN ? vpiTlv.network_link_type : _linkType ;
    _updated = true;

    return MCE_SUCCESS;
}

int MlxCfgOps::VpiParams::setOnDev(mfile* mf, bool ignoreCheck)
{
    int rc;
    if (_linkType == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc || _linkType == MLXCFG_UNKNOWN) {
            return errmsg("%s please specify all the parameters for VPI settings.", err() ? err() : "");
        }
    }
    if (!ignoreCheck && !isLegal()) {
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

bool MlxCfgOps::VpiParams::isLegal(mfile* mf)
{
    (void)mf;
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
    errmap[MCE_PCICONF] = "Access to device should be through configuration cycles only.";
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
    mread4(_mf, HW_ID_ADDR, &devId);
    switch (devId & 0xffff) { // check hw device id
         case CX3_HW_ID : //Cx3
         case CX3_PRO_HW_ID : // Cx3-pro
             // check if device access type is pciconf (thats the only supported method atm)
            rc = mget_mdevs_type(_mf, &type);
        #ifndef MST_UL
            if (type != MST_PCICONF) {
                return errmsg(MCE_PCICONF);
            }
        #else
            if (type != MTCR_ACCESS_CONFIG) {
                return errmsg(MCE_PCICONF);
            }
        #endif
            // check if we support tools_hcr
             rc = tools_cmdif_query_dev_cap(_mf, TOOL_CAP_BITS_ADDR, &_suppVec);
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
    // check if we support Tools HCR
    rc = supportsToolsHCR();
    if (rc) {
        return rc;
    }
    // update cfg specific info.
    // TODO: change all configuration specific to updateInfo() as a virtual function in the base class and call that on all Cfg classes
    // update max Vfs
    if (supportsCfg(Mct_Sriov)) {
        int rc = static_cast<SriovParams*>(_cfgList[Mct_Sriov])->updateMaxVfs(_mf);
        if (rc) {
            return rc;
        }
    }

    // get max/current bar size
    if (supportsCfg(Mct_Bar_Size)) {
        int rc = static_cast<BarSzParams*>(_cfgList[Mct_Bar_Size])->updateBarSzInfo(_mf);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::open(const char* devStr)
{
    _mf = mopen(devStr);
    if (_mf == NULL) {
        return errmsg(MCE_OPEN_DEVICE);
    }

    return openComChk();
}

int MlxCfgOps::opend(mfile* mf)
{
    if (!mf) {
        return errmsg(MCE_BAD_PARAMS);
    }
    _mf = mf;
    return openComChk();
}

bool MlxCfgOps::supportsCfg(mlxCfgType cfg)
{
    if (!isLegal(cfg)) {
        return false;
    }
    if (cfg == Mct_Bar_Size) { // dont enable these just yet, no FW support
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

int MlxCfgOps::setCfg(mlxCfgParam cfgParam, u_int32_t val, bool ignoreCheck)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }
    _cfgList[cfgParam2Type(cfgParam)]->setParam(cfgParam, val);
    int rc = _cfgList[cfgParam2Type(cfgParam)]->setOnDev(_mf, ignoreCheck);
    if (rc) {
        return errmsgConcatMsg(rc, *_cfgList[cfgParam2Type(cfgParam)]);
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::setCfg(const std::vector<cfgInfo>& infoVec, bool ignoreCheck)
{
    // set params
    std::set<CfgParams*> CfgToSet;

    for (std::vector<cfgInfo>::const_iterator it = infoVec.begin() ; it != infoVec.end(); it++) {
        if (!isLegal(it->first)) {
            return MCE_BAD_PARAMS;
        }
        if (!supportsParam(it->first)) {
            return errmsg(MCE_UNSUPPORTED_CFG);
        }
        _cfgList[cfgParam2Type(it->first)]->setParam(it->first, it->second);
        CfgToSet.insert(_cfgList[cfgParam2Type(it->first)]);
    }
    //set on device exit on first failure
    for (std::set<CfgParams*>::iterator it = CfgToSet.begin() ; it != CfgToSet.end(); it++) {
        int rc = (*it)->setOnDev(_mf, ignoreCheck);
        if (rc) {
            return errmsgConcatMsg(rc, (**it));
        }
    }
    return MCE_SUCCESS;
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

