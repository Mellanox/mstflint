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

#include <tools_layouts/tools_open_layouts.h>
#include <mft_sig_handler.h>
#include <reg_access/reg_access.h>
#include <cmdif/tools_cif.h>
#include "mlxcfg_lib.h"

using namespace std;

/*
 * Mask and offsets for working with the capability vector
 * retrieved via query_dev_cap command.
 */

#define TOOL_CAP_BITS_ADDR 0xc0

#define CHECK_RC(rc)\
	if (rc) return rc;
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
    _deviceId = DeviceEndMarker;
    _suppVec = 0;
    _isFifthGen = false;
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

int MlxCfgOps::supportsNVData()
{
    struct tools_open_nvqc nvqcTlv;
    memset(&nvqcTlv, 0, sizeof(struct tools_open_nvqc));
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_nvqc(_mf, REG_ACCESS_METHOD_GET, &nvqcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        return errmsg(MCE_NVCFG_NOT_SUPP);
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::openComChk()
{
    bool rc;
    int ret;
    // check if we support Tools HCR and update _suppVec
    if (_isFifthGen) {
        rc = supportsNVData(); CHECK_RC(rc);
    } else {
        rc = supportsToolsHCR(); CHECK_RC(rc);
    }

    // update cfg specific info.
    for (int i = Mct_Sriov; i < Mct_Last; i++) {
        _cfgList[i]->setDevCapVec(_suppVec);
        if (_cfgList[i]->cfgSupported(_mf)) {
            ret = _cfgList[i]->getDefaultParams(_mf);
            if (ret && ret!= MCE_GET_DEFAULT_PARAMS && ret != MCE_NOT_IMPLEMENTED) {
                return ret;
            }
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
    u_int32_t hwDevId, hwRevId;
    if (!mf) {
        return errmsg(MCE_BAD_PARAMS);
    }
    _mf = mf;

    if( dm_get_device_id(mf, &_deviceId, &hwDevId, &hwRevId) ) {
        return errmsg("Failed to identify device.");
    }
    // check if device is supported:
    switch(_deviceId) {
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
        _isFifthGen = false;
        break;
    case DeviceConnectIB:
    case DeviceConnectX4:
        _isFifthGen = true;
        break;
    default:
        return errmsg(MCE_UNSUPPORTED_DEVICE);
    }

    // init _cfgList
    _cfgList.resize(Mct_Last);
    if (_isFifthGen) {
        _cfgList[Mct_Sriov] = new SriovParams5thGen();
        _cfgList[Mct_Wol_P1] = new WolParams5thGen(1);
        _cfgList[Mct_Wol_P2] = new WolParams5thGen(2);
        _cfgList[Mct_Vpi_P1] = new VpiParams5thGen(1);
        _cfgList[Mct_Vpi_P2] = new VpiParams5thGen(2);
        _cfgList[Mct_Bar_Size] = new BarSzParams5thGen();
    } else {
        _cfgList[Mct_Sriov] = new SriovParams4thGen();
        _cfgList[Mct_Wol_P1] = new WolParams4thGen(1);
        _cfgList[Mct_Wol_P2] = new WolParams4thGen(2);
        _cfgList[Mct_Vpi_P1] = new VpiParams4thGen(1);
        _cfgList[Mct_Vpi_P2] = new VpiParams4thGen(2);
        _cfgList[Mct_Bar_Size] = new BarSzParams4thGen();
    }


    if (forceClearSem) {
        int rc;
        rc = _isFifthGen ? icmd_clear_semaphore(mf) : tools_cmdif_unlock_semaphore(_mf);
        if (rc) {
            return errmsg("Failed to unlock semaphore, %s.", m_err2str((MError)rc));
        }
    }
    return openComChk();
}

bool MlxCfgOps::supportsCfg(mlxCfgType cfg)
{
    if (!isLegal(cfg)) {
        return false;
    }
    return _cfgList[cfg]->cfgSupported(_mf);
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

    if (!supportsParam(cfgParam)) {
        return errmsg(MCE_UNSUPPORTED_CFG);
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

    if (!supportsParam(cfgParam)) {
        return errmsg(MCE_UNSUPPORTED_CFG);
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

int MlxCfgOps::invalidateCfgs4thGen()
{
    struct tools_open_mnvia mnviaTlv;
    u_int8_t buffer[tools_open_mnvia_size()];
    memset(&mnviaTlv, 0, sizeof(struct tools_open_mnvia));
    memset(buffer, 0, tools_open_mnvia_size());
    tools_open_mnvia_pack(&mnviaTlv, buffer);
    return reg_access_mnvia(_mf, REG_ACCESS_METHOD_SET, &mnviaTlv);
}

int MlxCfgOps::invalidateCfgs5thGen()
{
    struct tools_open_nvdia nvdiaTlv;
    u_int8_t buffer[tools_open_nvdia_size()];
    memset(&nvdiaTlv, 0, sizeof(struct tools_open_nvdia));
    memset(buffer, 0, tools_open_nvdia_size());
    tools_open_nvdia_pack(&nvdiaTlv, buffer);
    return reg_access_nvdia(_mf, REG_ACCESS_METHOD_SET, &nvdiaTlv);
}

int MlxCfgOps::invalidateCfgs()
{
    int rc;
    if (_isFifthGen) {
        return errmsg(MCE_REG_NOT_SUPP, "Reset configuration not supported.");
        //rc = invalidateCfgs5thGen();
    } else {
        rc = invalidateCfgs4thGen();
    }
    if (rc) {
        return errmsg("failed to invalidate configurations, %s.", m_err2str((MError)rc));
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

