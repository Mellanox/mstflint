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
 * mlxcfg_4thgen_commander.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#include <set>
#include <cmath>
#include <signal.h>
#include <mtcr.h>
#include <tools_layouts/tools_open_layouts.h>
#include <mft_sig_handler.h>
#include <reg_access/reg_access.h>
#include <cmdif/tools_cif.h>
#include <sstream>
#include <algorithm>

#include "mlxcfg_4thgen_commander.h"
#include "mlxcfg_param_lib.h"
#include "mlxcfg_utils.h"

using namespace std;

/*
 * Mask and offsets for working with the capability vector
 * retrieved via query_dev_cap command.
 */

#define TOOL_CAP_BITS_ADDR 0xc0

#define CHECK_RC(rc) \
    if (rc) {return rc;}

#define HW_ID_ADDR 0xf0014
#define CX3_HW_ID 501
#define CX3_PRO_HW_ID 503

string FourthGenCommander::param2str[Mcp_Last] = {"SRIOV_EN", "NUM_OF_VFS",
                                                  "WOL_MAGIC_EN_P1", "WOL_MAGIC_EN_P2",
                                                  "LINK_TYPE_P1", "PHY_TYPE_P1", "XFI_MODE_P1", "FORCE_MODE_P1",
                                                  "LINK_TYPE_P2", "PHY_TYPE_P2", "XFI_MODE_P2", "FORCE_MODE_P2",
                                                  "LOG_BAR_SIZE",
                                                  "INT_LOG_MAX_PAYLOAD_SIZE",
                                                  "BOOT_PKEY_P1", "BOOT_PKEY_P2",
                                                  "LOG_DCR_HASH_TABLE_SIZE", "DCR_LIFO_SIZE",
                                                  "ROCE_NEXT_PROTOCOL",
                                                  "ROCE_CC_ALGORITHM_P1", "ROCE_CC_PRIO_MASK_P1", "ROCE_CC_ALGORITHM_P2", "ROCE_CC_PRIO_MASK_P2",
                                                  "CLAMP_TGT_RATE_P1", "CLAMP_TGT_RATE_AFTER_TIME_INC_P1", "RPG_TIME_RESET_P1",
                                                  "RPG_BYTE_RESET_P1", "RPG_THRESHOLD_P1", "RPG_MAX_RATE_P1", "RPG_AI_RATE_P1",
                                                  "RPG_HAI_RATE_P1", "RPG_GD_P1", "RPG_MIN_DEC_FAC_P1", "RPG_MIN_RATE_P1",
                                                  "RATE_TO_SET_ON_FIRST_CNP_P1", "DCE_TCP_G_P1", "DCE_TCP_RTT_P1",
                                                  "RATE_REDUCE_MONITOR_PERIOD_P1", "INITIAL_ALPHA_VALUE_P1", "MIN_TIME_BETWEEN_CNPS_P1",
                                                  "CNP_DSCP_P1", "CNP_802P_PRIO_P1",
                                                  "CLAMP_TGT_RATE_P2", "CLAMP_TGT_RATE_AFTER_TIME_INC_P2", "RPG_TIME_RESET_P2",
                                                  "RPG_BYTE_RESET_P2", "RPG_THRESHOLD_P2", "RPG_MAX_RATE_P2", "RPG_AI_RATE_P2",
                                                  "RPG_HAI_RATE_P2", "RPG_GD_P2", "RPG_MIN_DEC_FAC_P2", "RPG_MIN_RATE_P2",
                                                  "RATE_TO_SET_ON_FIRST_CNP_P2", "DCE_TCP_G_P2", "DCE_TCP_RTT_P2", "RATE_REDUCE_MONITOR_PERIOD_P2",
                                                  "INITIAL_ALPHA_VALUE_P2", "MIN_TIME_BETWEEN_CNPS_P2", "CNP_DSCP_P2", "CNP_802P_PRIO_P2",
                                                  "BOOT_OPTION_ROM_EN_P1", "BOOT_VLAN_EN_P1", "BOOT_RETRY_CNT_P1", "LEGACY_BOOT_PROTOCOL_P1", "BOOT_VLAN_P1",
                                                  "BOOT_OPTION_ROM_EN_P2", "BOOT_VLAN_EN_P2", "BOOT_RETRY_CNT_P2", "LEGACY_BOOT_PROTOCOL_P2", "BOOT_VLAN_P2",
                                                  "PORT_OWNER", "ALLOW_RD_COUNTERS", "IP_VER", "IP_VER_P1", "IP_VER_P2", "PHY_PARAMETER_MODE", "CQ_TIMESTAMP", "STEER_FORCE_VLAN",
};

void FourthGenCommander::freeCfgList()
{
    for (map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        delete it->second;
    }
}

FourthGenCommander::FourthGenCommander(mfile *mf, string dev) : Commander(mf), _dev(dev),
    _allInfo()
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

    _suppVec = 0;

    // SR-IOV
    _cfgList[Mct_Sriov] = new SriovParams4thGen();
    _param2TypeMap[Mcp_Sriov_En] = Mct_Sriov;
    _param2TypeMap[Mcp_Num_Of_Vfs] = Mct_Sriov;
    // Wake on LAN
    _cfgList[Mct_Wol_P1] = new WolParams4thGen(1);
    _cfgList[Mct_Wol_P2] = new WolParams4thGen(2);
    _param2TypeMap[Mcp_Wol_Magic_En_P1] = Mct_Wol_P1;
    _param2TypeMap[Mcp_Wol_Magic_En_P2] = Mct_Wol_P2;
    // Vpi Settings
    _cfgList[Mct_Vpi_P1] = new VpiParams4thGen(1);
    _cfgList[Mct_Vpi_P2] = new VpiParams4thGen(2);
    _param2TypeMap[Mcp_Link_Type_P1] = Mct_Vpi_P1;
    _param2TypeMap[Mcp_Phy_Type_P1] = Mct_Vpi_P1;
    _param2TypeMap[Mcp_Xfi_Mode_P1] = Mct_Vpi_P1;
    _param2TypeMap[Mcp_Force_Mode_P1] = Mct_Vpi_P1;
    _param2TypeMap[Mcp_Link_Type_P2] = Mct_Vpi_P2;
    _param2TypeMap[Mcp_Phy_Type_P2] = Mct_Vpi_P2;
    _param2TypeMap[Mcp_Xfi_Mode_P2] = Mct_Vpi_P2;
    _param2TypeMap[Mcp_Force_Mode_P2] = Mct_Vpi_P2;
    // BAR size
    _cfgList[Mct_Bar_Size] = new BarSzParams4thGen();
    _param2TypeMap[Mcp_Log_Bar_Size] = Mct_Bar_Size;
    // Infiniband Boot Settings
    _cfgList[Mct_Boot_Settings_P1] = new InfinibandBootSettingsParams4thGen(1);
    _cfgList[Mct_Boot_Settings_P2] = new InfinibandBootSettingsParams4thGen(2);
    _param2TypeMap[Mcp_Boot_Pkey_P1] = Mct_Boot_Settings_P1;
    _param2TypeMap[Mcp_Boot_Pkey_P2] = Mct_Boot_Settings_P2;
    // Preboot Boot Settings
    _cfgList[Mct_Preboot_Boot_Settings_P1] = new PrebootBootSettingsParams4thGen(1);
    _cfgList[Mct_Preboot_Boot_Settings_P2] = new PrebootBootSettingsParams4thGen(2);
    _param2TypeMap[Mcp_Boot_Option_Rom_En_P1] = Mct_Preboot_Boot_Settings_P1;
    _param2TypeMap[Mcp_Boot_Vlan_En_P1] = Mct_Preboot_Boot_Settings_P1;
    _param2TypeMap[Mcp_Boot_Retry_Cnt_P1] = Mct_Preboot_Boot_Settings_P1;
    _param2TypeMap[Mcp_Legacy_Boot_Protocol_P1] = Mct_Preboot_Boot_Settings_P1;
    _param2TypeMap[Mcp_Boot_Vlan_P1] = Mct_Preboot_Boot_Settings_P1;

    _param2TypeMap[Mcp_Boot_Option_Rom_En_P2] = Mct_Preboot_Boot_Settings_P2;
    _param2TypeMap[Mcp_Boot_Vlan_En_P2] = Mct_Preboot_Boot_Settings_P2;
    _param2TypeMap[Mcp_Boot_Retry_Cnt_P2] = Mct_Preboot_Boot_Settings_P2;
    _param2TypeMap[Mcp_Legacy_Boot_Protocol_P2] = Mct_Preboot_Boot_Settings_P2;
    _param2TypeMap[Mcp_Boot_Vlan_P2] = Mct_Preboot_Boot_Settings_P2;

    _cfgList[Mct_Boot_Settings_Extras_4thGen_P1] = new BootSettingsExtParams4thGen(1);
    _cfgList[Mct_Boot_Settings_Extras_4thGen_P2] = new BootSettingsExtParams4thGen(2);
    _param2TypeMap[Mcp_Boot_Settings_Ext_IP_Ver_P1] = Mct_Boot_Settings_Extras_4thGen_P1;
    _param2TypeMap[Mcp_Boot_Settings_Ext_IP_Ver_P2] = Mct_Boot_Settings_Extras_4thGen_P2;

    // CX3 Global Conf
    _cfgList[Mct_CX3_Global_Conf] = new CX3GlobalConfParams();
    _param2TypeMap[Mcp_CQ_Timestamp] = Mct_CX3_Global_Conf;
    _param2TypeMap[Mcp_Steer_ForceVlan] = Mct_CX3_Global_Conf;
    _param2TypeMap[Mcp_Phy_Param_Mode] = Mct_CX3_Global_Conf;


    if (openComChk()) {
        freeCfgList();
        throw MlxcfgException("Failed to open device: %s. %s",
                              _dev.c_str(), err());
    }
}

FourthGenCommander::~FourthGenCommander()
{
    freeCfgList();
    return;
}

void FourthGenCommander::clearSemaphore()
{
    int rc = tools_cmdif_unlock_semaphore(_mf);
    if (rc) {
        throw MlxcfgException("Failed to unlock semaphore, %s.", m_err2str((MError)rc));
    }
}

int FourthGenCommander::supportsToolsHCR()
{
    // we also update the support vector
    u_int32_t devId = 0x0;
    u_int32_t type = 0;
    int rc;

    if (mread4(_mf, HW_ID_ADDR, &devId) != 4) {
        return MCE_CR_ERROR;
    }
    switch (devId & 0xffff) { // check hw device id
    case CX3_HW_ID:       //Cx3
    case CX3_PRO_HW_ID:       // Cx3-pro
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

bool FourthGenCommander::supportsCfg(mlxCfgType cfg)
{
    if (!isLegal(cfg)) {
        return false;
    }
    return _cfgList[cfg]->cfgSupported(_mf);
}

void FourthGenCommander::invalidateCfgs()
{
    struct tools_open_mnvia mnviaTlv;
    u_int8_t buffer[TOOLS_OPEN_MNVIA_SIZE] = {0};
    int rc;

    memset(&mnviaTlv, 0, sizeof(struct tools_open_mnvia));
    tools_open_mnvia_pack(&mnviaTlv, buffer);
    mft_signal_set_handling(1);
    rc = reg_access_mnvia(_mf, REG_ACCESS_METHOD_SET, &mnviaTlv);
    dealWithSignal();

    if (rc) {
        throw MlxcfgException("Failed to invalidate configurations: %s", m_err2str((MError)rc));
    }

}

const char* FourthGenCommander::loadConfigurationGetStr()
{
    return "Please reboot machine to load new configurations.";
}

bool FourthGenCommander::isLegal(mlxCfgType cfg)
{
    if (_cfgList.find(cfg) != _cfgList.end()) {
        return true;
    }
    errmsg("illegal configuration");
    return false;
}

void FourthGenCommander::setRawCfg(std::vector<u_int32_t> rawTlvVec)
{
    (void)rawTlvVec;
    throw MlxcfgException("set_raw command is not supported for this device\n");
}

std::vector<u_int32_t> FourthGenCommander::getRawCfg(std::vector<u_int32_t> rawTlvVec)
{
    (void)rawTlvVec;
    throw MlxcfgException("get_raw command is not supported for this device\n");
}

void FourthGenCommander::dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump)
{
    (void)rawTlvVec;
    (void)tlvDump;
    throw MlxcfgException("set_raw command is not supported for this device\n");
}

void FourthGenCommander::backupCfgs(vector<BackupView>& views)
{
    (void)views;
    throw MlxcfgException("backup command is not supported for this device\n");
}

bool FourthGenCommander::isLegal(mlxCfgParam cfg)
{
    if (cfg >= Mcp_Sriov_En && cfg < Mcp_Last) {
        return true;
    }
    errmsg("illegal configuration parameter");
    return false;
}

int FourthGenCommander::openComChk()
{
    bool rc;
    int ret;
    // check if we support Tools HCR and update _suppVec
    rc = supportsToolsHCR(); CHECK_RC(rc);

    // update cfg specific info.
    // TODO: adrianc: when getting defaults for 4th gen , perform queryDefParams only once and pass struct to classes to avoid calling multiple times
    for (std::map<mlxCfgType, CfgParams*>::iterator paramIt = _cfgList.begin(); paramIt != _cfgList.end(); paramIt++) {
        paramIt->second->setDevCapVec(_suppVec);
        if (paramIt->second->cfgSupported(_mf)) {
            ret = paramIt->second->getDefaultParams(_mf);
            if (ret && ret != MCE_GET_DEFAULT_PARAMS && ret != MCE_NOT_IMPLEMENTED) {
                return ret;
            }
        }
    }
    return MCE_SUCCESS;
}

mlxCfgType FourthGenCommander::cfgParam2Type(mlxCfgParam param)
{
    if (_param2TypeMap.find(param) == _param2TypeMap.end()) {
        return Mct_Last;
    }
    return _param2TypeMap[param];
}

bool FourthGenCommander::supportsParam(mlxCfgParam param)
{
    if (!isLegal(param)) {
        return false;
    }

    if (!isLegal(cfgParam2Type(param))) {
        return false;
    }
    return _cfgList[cfgParam2Type(param)]->cfgSupported(_mf, param);
}

void FourthGenCommander::getCfg(ParamView& cfgParam, QueryType qt)
{
    for (int p = (int)Mcp_Sriov_En; p < (int)Mcp_Last; ++p) {
        if (cfgParam.mlxconfigName == param2str[p].c_str()) {
            bool isDefault = (qt == QueryDefault);
            if (!supportsParam((mlxCfgParam)p)) {
                throw MlxcfgException("Device doesn't support %s configuration",
                                      param2str[p].c_str());
            }
            u_int32_t val = MLXCFG_UNKNOWN;
            if (getCfgAux((mlxCfgParam)p, val, isDefault)) {
                throw MlxcfgException("Failed to query device %s configuration",
                                      (isDefault ? "default" : "current"));
            }
            MlxCfgParamParser paramParser;
            if (_allInfo.getParamParser((mlxCfgParam)p, paramParser) == MLX_CFG_OK) {
                string strVal = paramParser.getStrVal(val);
                cfgParam.mlxconfigName = param2str[p].c_str();
                cfgParam.strVal = strVal;
                cfgParam.val = val;
                cfgParam.textualVals = paramParser.getStrMap();
            } else {
                throw MlxcfgException("Cannot parse parameter %s",
                                      param2str[p].c_str());
            }
        }
    }
    throw MlxcfgException("Parameter %s was not found",
                          cfgParam.mlxconfigName.c_str());
}

int FourthGenCommander::getCfgAux(mlxCfgParam cfgParam, u_int32_t& val, bool getDefault)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }

    if (!supportsParam(cfgParam)) {
        return errmsg(MCE_UNSUPPORTED_CFG);
    }

    if (getDefault) {
        val = (_cfgList[cfgParam2Type(cfgParam)])->getDefaultParam(cfgParam);
    } else {
        int rc;
        rc = _cfgList[cfgParam2Type(cfgParam)]->getFromDev(_mf);
        if (rc) {
            return errmsgConcatMsg(rc, *_cfgList[cfgParam2Type(cfgParam)]);
        }
        val = (_cfgList[cfgParam2Type(cfgParam)])->getParam(cfgParam);
    }
    return MCE_SUCCESS;
}

int FourthGenCommander::getCfgAux(std::vector<cfgInfo>& infoVec)
{
    for (std::vector<cfgInfo>::iterator it = infoVec.begin(); it != infoVec.end(); it++) {
        int rc = getCfgAux(it->first, it->second);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

int FourthGenCommander::setCfgAux(mlxCfgParam cfgParam, u_int32_t val)
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

void FourthGenCommander::queryParamViews(std::vector<ParamView>& paramsToQuery, QueryType qt)
{
    VECTOR_ITERATOR(ParamView, paramsToQuery, param) {
        bool found = false;
        for (int i = (int)Mcp_Sriov_En; i < (int)Mcp_Last; i++) {
            if (param->mlxconfigName == param2str[i]) {
                found = true;
            }
        }
        if (!found) {
            throw MlxcfgException("Unknown Parameter: %s",
                                  param->mlxconfigName.c_str());
        }
    }
    queryAux(paramsToQuery, qt, true);
    return;
}

void FourthGenCommander::setCfg(std::vector<ParamView>& params, bool force)
{
    mlxCfgParam failedParam = Mcp_Last;
    vector<cfgInfo> infoVec;

    VECTOR_ITERATOR(ParamView, params, pv) {
        int i;
        for (i = (int)Mcp_Sriov_En; i < (int)Mcp_Last; i++) {
            if (pv->mlxconfigName == param2str[i]) {
                infoVec.push_back(cfgInfo((mlxCfgParam)i, pv->val));
                break;
            }
        }
    }

    setIgnoreSoftLimits(force);

    int rc = setCfgAux(infoVec, failedParam);
    if (rc) {
        if (rc == MCE_UNSUPPORTED_CFG && failedParam != Mcp_Last) {
            throw MlxcfgException("Unsupported Configuration: %s",
                                  param2str[failedParam].c_str());
        } else {
            throw MlxcfgException("Failed to set configuration: %s",
                                  err());
        }
    }
}


int FourthGenCommander::setCfgAux(const std::vector<cfgInfo>& infoVec,
                                  mlxCfgParam& failedParam)
{
    // set params
    std::set<CfgParams*> CfgToSet;
    int rc;

    for (std::vector<cfgInfo>::const_iterator it = infoVec.begin(); it != infoVec.end(); it++) {
        if (!isLegal(it->first)) {
            return MCE_BAD_PARAMS;
        }
        if (!supportsParam(it->first)) {
            failedParam = it->first;
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
    for (std::set<CfgParams*>::iterator it = CfgToSet.begin(); it != CfgToSet.end(); it++) {
        rc = (*it)->setOnDev(_mf);
        if (rc) {
            return errmsgConcatMsg(rc, (**it));
        }
    }
    return MCE_SUCCESS;
}

void FourthGenCommander::setIgnoreSoftLimits(bool val)
{
    for (std::map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        it->second->setIgnoreSoftLimits(val);
    }
    return;
}

void FourthGenCommander::setIgnoreHardLimits(bool val)
{
    for (std::map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        it->second->setIgnoreHardLimits(val);
    }
    return;
}

void FourthGenCommander::queryAux(vector<ParamView>& params, QueryType qt,
                                  bool isSetCmd)
{
    int rc;

    for (int p = (int)Mcp_Sriov_En; p < (int)Mcp_Last; ++p) {
        ParamView pV;
        ParamView *pVP = &pV;
        if (isSetCmd) {
            bool found = false;
            VECTOR_ITERATOR(ParamView, params, k) {
                if (k->mlxconfigName == param2str[p].c_str()) {
                    found = true;
                    pVP = &(*k);
                    break;
                }
            }
            if (!found) {
                continue;
            }
        }
        bool isDefault = (qt == QueryDefault);
        if (!supportsParam((mlxCfgParam)p)) {
            if (isSetCmd) {
                throw MlxcfgException("Device doesn't support %s configuration",
                                      param2str[p].c_str());
            }
            continue;
        }
        u_int32_t val = MLXCFG_UNKNOWN;
        rc = getCfgAux((mlxCfgParam)p, val, isDefault);
        if (rc) {
            throw MlxcfgException("Failed to query device %s configuration",
                                  (isDefault ? "default" : "current"));
        } else {
            MlxCfgParamParser paramParser;
            if (_allInfo.getParamParser((mlxCfgParam)p, paramParser) == MLX_CFG_OK) {
                string strVal = paramParser.getStrVal(val);
                pVP->mlxconfigName = param2str[p].c_str();
                pVP->strVal = strVal;
                pVP->val = val;
                pVP->textualVals = paramParser.getStrMap();
                if (!isSetCmd) {
                    params.push_back(*pVP);
                }
            } else {
                throw MlxcfgException("Cannot parse parameter %s",
                                      param2str[p].c_str());
            }
        }
    }

}

void FourthGenCommander::queryAll(std::vector<ParamView>& params, vector<string>& /*failedTLVs*/, QueryType qt)
{
    queryAux(params, qt, false);
}

void FourthGenCommander::updateParamViewValue(ParamView& p, std::string v)
{
    mlxCfgParam param = Mcp_Last;

    if (_allInfo.parseParam(p.mlxconfigName, v, p.val, param)) {
        if (param == Mcp_Last) {
            throw MlxcfgException("Unknown Parameter: %s",
                                  p.mlxconfigName.c_str());
        } else {
            throw MlxcfgException("Failed to parse %s=%s",
                                  p.mlxconfigName.c_str(), v.c_str());
        }
    }
    //find string val
    MlxCfgParamParser paramParser;
    if (_allInfo.getParamParser((mlxCfgParam)param, paramParser) == MLX_CFG_OK) {
        p.strVal = paramParser.getStrVal(p.val);
    } else {
        throw MlxcfgException("Cannot parse parameter %s",
                              param2str[param].c_str());
    }


}

mlxCfgStatus MlxCfgParamParser::parseUserInput(string input, u_int32_t& val)
{
    std::map<string, u_int32_t>::iterator it;
    //first check if it is a numeric value
    if (strToNum(input, val, 0)) {
        if (val == MLXCFG_UNKNOWN) {
            return MLX_CFG_ERROR;
        }
        return MLX_CFG_OK;
    }
    for (it = _strMap.begin(); it != _strMap.end(); it++) {
        if (strcasecmp(it->first.c_str(), input.c_str()) == 0) {
            val = it->second;
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

string MlxCfgParamParser::getShortDescStrAux()
{
    string s;
    std::map<string, u_int32_t>::iterator it;

    s = _name + "=<";

    if (_strMap.size() == 0) {
        s += _allowedValues;
    } else {
        //printf first str
        it = _strMap.begin();
        s += it->first;
        it++;
        for (; it != _strMap.end(); it++) {
            s += "|";
            s += it->first;
        }
    }

    s += ">";
    return s;
}

void MlxCfgParamParser::printShortDesc()
{
    printf(IDENT4 "%s\n", getShortDescStrAux().c_str());
}

void MlxCfgParamParser::splitAndPrintDesc(FILE *f, string desc)
{
    if (desc.length() > 129) {
        //find index of last space in first 129 chars and split there
        int i = desc.substr(0, 129).find_last_of(' ');
        string desc2 = desc.substr(i, (desc.length() - i));
        fprintf(f, IDENT4 "%-46s   %s\n", "", desc.substr(0, i).c_str());
        splitAndPrintDesc(f, desc2);
    } else {
        fprintf(f, IDENT4 "%-46s   %s\n", "", desc.c_str());
    }
}

void MlxCfgParamParser::printLongDesc(FILE *f)
{
    string shortDesc = getShortDescStrAux();
    if (_desc.length() > 129) {
        //find index of last space in first 129 chars and split there
        int i = _desc.substr(0, 129).find_last_of(' ');
        string desc2 = _desc.substr(i, (_desc.length() - i));
        fprintf(f, IDENT4 "%-46s : %s\n", shortDesc.c_str(), _desc.substr(0, i).c_str());
        splitAndPrintDesc(f, desc2);
    } else {
        fprintf(f, IDENT4 "%-46s : %s\n", shortDesc.c_str(), _desc.c_str());
    }
}

string MlxCfgParamParser::getStrVal(u_int32_t val)
{
    std::map<string, u_int32_t>::iterator it;
    if (val == MLXCFG_UNKNOWN) {
        return "MLXCFG_UNKNOWN";
    }
    if (_strMap.size() == 0) {
        ostringstream ss;
        ss << val;
        return ss.str();
    } else {
        for (it = _strMap.begin(); it != _strMap.end(); it++) {
            if (val == it->second) {
                return it->first;
            }
        }
        //not a legal value, print it as it
        return "";
    }
}

bool mlxCfgParamParserCompare(MlxCfgParamParser a, MlxCfgParamParser b)
{
    return a.getName() < b.getName();
}

vector<MlxCfgParamParser> MlxCfgInfo::getParamsMapValues()
{
    vector<MlxCfgParamParser> vals;
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it;
    for (it = _params.begin(); it != _params.end(); it++) {
        vals.push_back(it->second);
    }
    return vals;
}

void MlxCfgInfo::printShortDesc()
{
    printf("\n");
    printf(IDENT2 "%s: %s\n", _name.c_str(), _title.c_str());

    vector<MlxCfgParamParser> vals = getParamsMapValues();
    std::sort(vals.begin(), vals.end(), mlxCfgParamParserCompare);

    for (unsigned int i = 0; i < vals.size(); i++) {
        vals[i].printShortDesc();
    }
}

void MlxCfgInfo::printLongDesc(FILE *f)
{
    fprintf(f, "\n");
    fprintf(f, IDENT2 "%s: %s\n", _name.c_str(), _title.c_str());

    vector<MlxCfgParamParser> vals = getParamsMapValues();
    std::sort(vals.begin(), vals.end(), mlxCfgParamParserCompare);

    for (unsigned int i = 0; i < vals.size(); i++) {
        vals[i].printLongDesc(f);
    }
}

mlxCfgStatus MlxCfgInfo::getParamParser(mlxCfgParam p, MlxCfgParamParser& paramParser)
{
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it = _params.find(p);
    if (it == _params.end()) {
        return MLX_CFG_ERROR;
    }
    paramParser = it->second;
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfgInfo::getParamParser(string name, MlxCfgParamParser& paramParser)
{
    std::map<mlxCfgParam, MlxCfgParamParser>::iterator it;
    for (it = _params.begin(); it != _params.end(); it++) {
        if (name == it->second.getName()) {
            paramParser = it->second;
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

MlxCfgInfo MlxCfgAllInfo::createPciSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Log_Bar_Size] = MlxCfgParamParser(Mcp_Log_Bar_Size, "LOG_BAR_SIZE", "example: for 8Mb bar size set LOG_BAR_SIZE=3 (only "  FOURTH_GENERATION_LIST ")", "base_2_log_in_mb");
    params[Mcp_Sriov_En] = MlxCfgParamParser(Mcp_Sriov_En, "SRIOV_EN", "Enable SR-IOV", paramMap);
    params[Mcp_Num_Of_Vfs] = MlxCfgParamParser(Mcp_Num_Of_Vfs, "NUM_OF_VFS", "desired amount of virtual functions", "NUM");
    return MlxCfgInfo("PCI Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createIBDynamicallyConnect()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //IB Dynamically Connect
    params[Mcp_Dcr_Lifo_Size] = MlxCfgParamParser(Mcp_Dcr_Lifo_Size, "DCR_LIFO_SIZE", "The amount of total DCRs available to join linked-lists after hash DCRs", "SIZE");
    params[Mcp_Log_Dcr_Hash_Table_Size] = MlxCfgParamParser(Mcp_Log_Dcr_Hash_Table_Size, "LOG_DCR_HASH_TABLE_SIZE", "log2 of the hash table size minus 1", "SIZE");
    return MlxCfgInfo("IB Dynamically Connect", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createInfinibandBootSettings()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Infiniband Boot Settings
    params[Mcp_Boot_Pkey_P1] = MlxCfgParamParser(Mcp_Boot_Pkey_P1, "BOOT_PKEY_P1", "partition key to be used by PXE boot (ConnectX3, ConnectX3-Pro Only)", "PKEY");
    params[Mcp_Boot_Pkey_P2] = MlxCfgParamParser(Mcp_Boot_Pkey_P2, "BOOT_PKEY_P2", "set 0 for default", "PKEY");
    return MlxCfgInfo("Infiniband Boot Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createInternalSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Internal Settings
    paramMap["Auto"] = 0;
    paramMap["4KB"] = 12;
    params[Mcp_Log_Tpt_Size] = MlxCfgParamParser(Mcp_Log_Tpt_Size, "INT_LOG_MAX_PAYLOAD_SIZE", "" "Burst length", paramMap);
    return MlxCfgInfo("Internal Settings", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createPrebootBootSettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Preboot Boot Settings
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Boot_Option_Rom_En_P1] = MlxCfgParamParser(Mcp_Boot_Option_Rom_En_P1, "BOOT_OPTION_ROM_EN_P1", "Disable/Enable boot option ROM", paramMap);
    params[Mcp_Boot_Option_Rom_En_P2] = MlxCfgParamParser(Mcp_Boot_Option_Rom_En_P2, "BOOT_OPTION_ROM_EN_P2", "", paramMap);
    params[Mcp_Boot_Vlan_En_P1] = MlxCfgParamParser(Mcp_Boot_Vlan_En_P1, "BOOT_VLAN_EN_P1", "Disable/Enable VLAN mode for network boot", paramMap);
    params[Mcp_Boot_Vlan_En_P2] = MlxCfgParamParser(Mcp_Boot_Vlan_En_P2, "BOOT_VLAN_EN_P2", "", paramMap);
    params[Mcp_Boot_Retry_Cnt_P1] = MlxCfgParamParser(Mcp_Boot_Retry_Cnt_P1, "BOOT_RETRY_CNT_P1", "Number of retries to attempt in case of boot failure. 7 indicates infinite retries.", "0..7");
    params[Mcp_Boot_Retry_Cnt_P2] = MlxCfgParamParser(Mcp_Boot_Retry_Cnt_P2, "BOOT_RETRY_CNT_P2", "", "0..7");
    paramMap.clear();
    paramMap["None"] = 0;
    paramMap["PXE"] = 1;
    paramMap["iSCSI"] = 2;
    paramMap["Both"] = 3;
    params[Mcp_Legacy_Boot_Protocol_P1] = MlxCfgParamParser(Mcp_Legacy_Boot_Protocol_P1, "LEGACY_BOOT_PROTOCOL_P1", "None: disable legacy boot. PXE: DHCP/TFTP boot. Both: PXE and iSCSI", paramMap);
    params[Mcp_Legacy_Boot_Protocol_P2] = MlxCfgParamParser(Mcp_Legacy_Boot_Protocol_P2, "LEGACY_BOOT_PROTOCOL_P2", "", paramMap);
    params[Mcp_Boot_Vlan_P1] = MlxCfgParamParser(Mcp_Boot_Vlan_P1, "BOOT_VLAN_P1", "VLAN ID for the network boot", "VLAN ID");
    params[Mcp_Boot_Vlan_P2] = MlxCfgParamParser(Mcp_Boot_Vlan_P2, "BOOT_VLAN_P2", "", "VLAN ID");
    return MlxCfgInfo("Preboot Boot Settings", "Settings that control the legacy option ROM", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCECongestionControlECN()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE Congestion Control ECN
    params[Mcp_Clamp_Tgt_Rate_P1] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_P1, "CLAMP_TGT_RATE_P1", "If set, whenever a CNP is processed,"
                                                      " the target rate is updated to be the current rate. Default=1"
                                                      , "0|1");
    params[Mcp_Clamp_Tgt_Rate_P2] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_P2, "CLAMP_TGT_RATE_P2", "", "0|1");
    params[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1, "CLAMP_TGT_RATE_AFTER_TIME_INC_P1",
                                                                     "When receiving an CNP, the target rate should"
                                                                     " be updated if the transmission rate was increased"
                                                                     " due to the timer, and not only due to the byte counter" ". Default=1"
                                                                     , "0|1");
    params[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2] = MlxCfgParamParser(Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2, "CLAMP_TGT_RATE_AFTER_TIME_INC_P2", "", "0|1");
    params[Mcp_Rpg_Time_Reset_P1] = MlxCfgParamParser(Mcp_Rpg_Time_Reset_P1, "RPG_TIME_RESET_P1"
                                                      , "Time between rate increases if no CNPs are received. Given in u-seconds. Default=2"
                                                      , "USEC");
    params[Mcp_Rpg_Time_Reset_P2] = MlxCfgParamParser(Mcp_Rpg_Time_Reset_P2, "RPG_TIME_RESET_P2", "", "USEC");
    params[Mcp_Rpg_Byte_Reset_P1] = MlxCfgParamParser(Mcp_Rpg_Byte_Reset_P1, "RPG_BYTE_RESET_P1"
                                                      , "Transmitted data between rate increases if no CNPs are received. Given in Bytes. "
                                                      "Disabled=0, Default=150"
                                                      , "BYTE_NUM");
    params[Mcp_Rpg_Byte_Reset_P2] = MlxCfgParamParser(Mcp_Rpg_Byte_Reset_P2, "RPG_BYTE_RESET_P2", "", "BYTE_NUM");
    params[Mcp_Rpg_Threshold_P1] = MlxCfgParamParser(Mcp_Rpg_Threshold_P1, "RPG_THRESHOLD_P1"
                                                     , "The number of times rpByteStage or rpTimeStage can count before the RP rate control "
                                                     "state machine advances states. Default=5"
                                                     , "0..31");
    params[Mcp_Rpg_Threshold_P2] = MlxCfgParamParser(Mcp_Rpg_Threshold_P2, "RPG_THRESHOLD_P2", "", "0..31");
    params[Mcp_Rpg_Max_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Max_Rate_P1, "RPG_MAX_RATE_P1"
                                                    , "The maximum rate, in Mbits per second, at which an RP can transmit. "
                                                    "Once this limit is reached, the RP rate limited is released and "
                                                    "the flow is not rate limited any more. Default=0 (Full port speed)."
                                                    , "RATE_IN_MBIT");
    params[Mcp_Rpg_Max_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Max_Rate_P2, "RPG_MAX_RATE_P2", "", "RATE_IN_MBIT");
    params[Mcp_Rpg_Ai_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Ai_Rate_P1, "RPG_AI_RATE_P1", "The rate, in Mbits per second,"
                                                   " used to increase rpTargetRate in the RPR_ACTIVE_INCREASE state."
                                                   " Default=10."
                                                   , "RATE_IN_MBIT");
    params[Mcp_Rpg_Ai_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Ai_Rate_P2, "RPG_AI_RATE_P2", "", "RATE_IN_MBIT");
    params[Mcp_Rpg_Hai_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Hai_Rate_P1, "RPG_HAI_RATE_P1"
                                                    , "The rate, in Mbits per second, used to increase rpTargetRate in the RPR_HYPER_INCREASE state."
                                                    " Default=50"
                                                    , "RATE_IN_MBIT");
    params[Mcp_Rpg_Hai_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Hai_Rate_P2, "RPG_HAI_RATE_P2", "", "RATE_IN_MBIT");
    params[Mcp_Rpg_Gd_P1] = MlxCfgParamParser(Mcp_Rpg_Gd_P1, "RPG_GD_P1"
                                              , "If a CNP is received, the flow rate is reduced at the beginning of the next rate_reduce_monitor_period interval to,"
                                              "(1-Alpha/Gd)*CurrentRate. RPG_GD is given as log2(Gd), where Gd may only be powers of 2. Default=7."
                                              , "0..15");
    params[Mcp_Rpg_Gd_P2] = MlxCfgParamParser(Mcp_Rpg_Gd_P2, "RPG_GD_P2", "", "0..15");
    params[Mcp_Rpg_Min_Dec_Fac_P1] = MlxCfgParamParser(Mcp_Rpg_Min_Dec_Fac_P1, "RPG_MIN_DEC_FAC_P1"
                                                       , "The minimum factor by which the current transmit rate can be changed when processing a CNP."
                                                       "Value is given as a percentage (1-100). Default=50."
                                                       , "1..100");
    params[Mcp_Rpg_Min_Dec_Fac_P2] = MlxCfgParamParser(Mcp_Rpg_Min_Dec_Fac_P2, "RPG_MIN_DEC_FAC_P2", "", "1..100");
    params[Mcp_Rpg_Min_Rate_P1] = MlxCfgParamParser(Mcp_Rpg_Min_Rate_P1, "RPG_MIN_RATE_P1"
                                                    , "The minimum value, in Mb per second, for rate to limit. Default=2000"
                                                    , "RATE_IN_MBIT");
    params[Mcp_Rpg_Min_Rate_P2] = MlxCfgParamParser(Mcp_Rpg_Min_Rate_P2, "RPG_MIN_RATE_P2", "", "RATE_IN_MBIT");
    params[Mcp_Rate_To_Set_On_First_Cnp_P1] = MlxCfgParamParser(Mcp_Rate_To_Set_On_First_Cnp_P1, "RATE_TO_SET_ON_FIRST_CNP_P1"
                                                                , "The rate that is set for the flow when a rate limiter is allocated to it upon first CNP received, in Mbps. "
                                                                "Default=0"
                                                                , "RATE_IN_MBIT");
    params[Mcp_Rate_To_Set_On_First_Cnp_P2] = MlxCfgParamParser(Mcp_Rate_To_Set_On_First_Cnp_P2, "RATE_TO_SET_ON_FIRST_CNP_P2", "", "RATE_IN_MBIT");
    params[Mcp_Dce_Tcp_G_P1] = MlxCfgParamParser(Mcp_Dce_Tcp_G_P1, "DCE_TCP_G_P1"
                                                 , "Used to update the congestion estimator (alpha) once every dce_tcp_rtt microseconds. Default=64"
                                                 , "NUM");
    params[Mcp_Dce_Tcp_G_P2] = MlxCfgParamParser(Mcp_Dce_Tcp_G_P2, "DCE_TCP_G_P2", "", "NUM");
    params[Mcp_Dce_Tcp_Rtt_P1] = MlxCfgParamParser(Mcp_Dce_Tcp_Rtt_P1, "DCE_TCP_RTT_P1"
                                                   , "The time between updates of the alpha value, in microseconds. Default=2"
                                                   , "USEC");
    params[Mcp_Dce_Tcp_Rtt_P2] = MlxCfgParamParser(Mcp_Dce_Tcp_Rtt_P2, "DCE_TCP_RTT_P2", "", "USEC");
    params[Mcp_Rate_Reduce_Monitor_Period_P1] = MlxCfgParamParser(Mcp_Rate_Reduce_Monitor_Period_P1, "RATE_REDUCE_MONITOR_PERIOD_P1"
                                                                  , "The minimum time between 2 consecutive rate reductions for a single flow. "
                                                                  "Rate reduction will occur only if a CNP is received during the relevant time interval. Default=2."
                                                                  , "USEC");
    params[Mcp_Rate_Reduce_Monitor_Period_P2] = MlxCfgParamParser(Mcp_Rate_Reduce_Monitor_Period_P2, "RATE_REDUCE_MONITOR_PERIOD_P2", "", "USEC");
    params[Mcp_Initial_Alpha_Value_P1] = MlxCfgParamParser(Mcp_Initial_Alpha_Value_P1, "INITIAL_ALPHA_VALUE_P1"
                                                           , "The initial value of alpha to use when receiving the first CNP for a flow. "
                                                           "Expressed in a fixed point fraction of 2^10."
                                                           , "NUM");
    params[Mcp_Initial_Alpha_Value_P2] = MlxCfgParamParser(Mcp_Initial_Alpha_Value_P2, "INITIAL_ALPHA_VALUE_P2", "", "NUM");
    params[Mcp_Min_Time_Between_Cnps_P1] = MlxCfgParamParser(Mcp_Min_Time_Between_Cnps_P1, "MIN_TIME_BETWEEN_CNPS_P1"
                                                             , "Minimum time between sending cnps from the port, in microseconds. Default=0"
                                                             , "USEC");
    params[Mcp_Min_Time_Between_Cnps_P2] = MlxCfgParamParser(Mcp_Min_Time_Between_Cnps_P2, "MIN_TIME_BETWEEN_CNPS_P2", "", "USEC");
    params[Mcp_Cnp_Dscp_P1] = MlxCfgParamParser(Mcp_Cnp_Dscp_P1, "CNP_DSCP_P1"
                                                , "The DiffServ Code Point of the generated CNP for this port. Default=0"
                                                , "0..7");
    params[Mcp_Cnp_Dscp_P2] = MlxCfgParamParser(Mcp_Cnp_Dscp_P2, "CNP_DSCP_P2", "", "0..7");
    params[Mcp_Cnp_802p_Prio_P1] = MlxCfgParamParser(Mcp_Cnp_802p_Prio_P1, "CNP_802P_PRIO_P1"
                                                     , "The 802.1p priority value of the generated CNP for this port. Default=7"
                                                     , "NUM");
    params[Mcp_Cnp_802p_Prio_P2] = MlxCfgParamParser(Mcp_Cnp_802p_Prio_P2, "CNP_802P_PRIO_P2", "", "NUM");
    return MlxCfgInfo("RoCE Congestion Control ECN", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCEV1_5NextProtocol()
{
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE V1.5 next protocol
    params[Mcp_RoCE_Next_Protocol] = MlxCfgParamParser(Mcp_RoCE_Next_Protocol, "ROCE_NEXT_PROTOCOL",
                                                       "The next protocol value set in the IPv4/IPv6 packets for RoCE v1.5. The default is 0xFE.", "0..255");

    return MlxCfgInfo("RoCE V1.5 next protocol", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createRoCECongestionControlParameters()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //RoCE Congestion Control Parameters
    paramMap["ECN"] = 0;
    paramMap["QCN"] = 1;
    params[Mcp_RoCE_CC_Algorithm_P1] = MlxCfgParamParser(Mcp_RoCE_CC_Algorithm_P1, "ROCE_CC_ALGORITHM_P1", "Congestion control algorithm.", paramMap);
    params[Mcp_RoCE_CC_Algorithm_P2] = MlxCfgParamParser(Mcp_RoCE_CC_Algorithm_P2, "ROCE_CC_ALGORITHM_P2", "", paramMap);
    params[Mcp_RoCE_CC_Prio_Mask_P1] = MlxCfgParamParser(Mcp_RoCE_CC_Prio_Mask_P1, "ROCE_CC_PRIO_MASK_P1", "Per priority enable disable bitmask. default 0", "0..255");
    params[Mcp_RoCE_CC_Prio_Mask_P2] = MlxCfgParamParser(Mcp_RoCE_CC_Prio_Mask_P2, "ROCE_CC_PRIO_MASK_P2", "", "0..255");
    return MlxCfgInfo("RoCE Congestion Control Parameters", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createVPISettings()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //VPI Settings
    paramMap["IB"] = 1;
    paramMap["ETH"] = 2;
    paramMap["VPI"] = 3;
    params[Mcp_Link_Type_P1] = MlxCfgParamParser(Mcp_Link_Type_P1, "LINK_TYPE_P1", "", paramMap);
    params[Mcp_Link_Type_P2] = MlxCfgParamParser(Mcp_Link_Type_P2, "LINK_TYPE_P2", "", paramMap);

    paramMap.clear();
    paramMap["XAUI"] = 0x1;
    paramMap["XFI"] = 0x2;
    paramMap["SGMII"] = 0x3;
    params[Mcp_Phy_Type_P1] = MlxCfgParamParser(Mcp_Phy_Type_P1, "PHY_TYPE_P1", "", paramMap);
    params[Mcp_Phy_Type_P2] = MlxCfgParamParser(Mcp_Phy_Type_P2, "PHY_TYPE_P2", "", paramMap);

    paramMap.clear();
    paramMap["_10G"] = 0x0;
    paramMap["_20G"] = 0x1;
    paramMap["_40G"] = 0x2;
    params[Mcp_Xfi_Mode_P1] = MlxCfgParamParser(Mcp_Xfi_Mode_P1, "XFI_MODE_P1", "", paramMap);
    params[Mcp_Xfi_Mode_P2] = MlxCfgParamParser(Mcp_Xfi_Mode_P2, "XFI_MODE_P2", "", paramMap);

    paramMap.clear();
    paramMap["False"] = 0x0;
    paramMap["True"] = 0x1;
    params[Mcp_Force_Mode_P1] = MlxCfgParamParser(Mcp_Force_Mode_P1, "FORCE_MODE_P1", "", paramMap);
    params[Mcp_Force_Mode_P2] = MlxCfgParamParser(Mcp_Force_Mode_P2, "FORCE_MODE_P2", "", paramMap);

    return MlxCfgInfo("VPI Settings", "Control network link type", params);
}

MlxCfgInfo MlxCfgAllInfo::createWakeOnLAN()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Wake On LAN
    paramMap["True"] = 1;
    paramMap["False"] = 0;
    params[Mcp_Wol_Magic_En_P1] = MlxCfgParamParser(Mcp_Wol_Magic_En_P1, "WOL_MAGIC_EN_P1", "enable wake on magic packet(per port.)", paramMap);
    params[Mcp_Wol_Magic_En_P2] = MlxCfgParamParser(Mcp_Wol_Magic_En_P2, "WOL_MAGIC_EN_P2", "only " FOURTH_GENERATION_LIST, paramMap);
    return MlxCfgInfo("Wake On LAN", "", params);
}

MlxCfgInfo MlxCfgAllInfo::createBootSettingsExt()
{
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    //Boot Settings Extras
    paramMap["IPv4"] = 0;
    paramMap["IPv6"] = 1;
    paramMap["IPv4_IPv6"] = 2;
    paramMap["IPv6_IPv4"] = 3;
    params[Mcp_Boot_Settings_Ext_IP_Ver_P1] = MlxCfgParamParser(Mcp_Boot_Settings_Ext_IP_Ver_P1, "IP_VER_P1", "Select which IP protocol version will be used by flexboot, only "  FOURTH_GENERATION_LIST " (per port).", paramMap);
    params[Mcp_Boot_Settings_Ext_IP_Ver_P2] = MlxCfgParamParser(Mcp_Boot_Settings_Ext_IP_Ver_P2, "IP_VER_P2", "", paramMap);
    return MlxCfgInfo("Boot Settings Extras", "These parameters are relevant only for servers using legacy BIOS PXE boot (flexboot).", params);
}

MlxCfgInfo MlxCfgAllInfo::createCX3GlobalConf()
{
    map<string, u_int32_t> paramMap;
    map<string, u_int32_t> phyParamModeParamMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    paramMap["True"] = 1;
    paramMap["False"] = 0;

    phyParamModeParamMap["DEVICE_DEFAULT"] = 0;
    phyParamModeParamMap["LEGACY"] = 1;
    phyParamModeParamMap["ADVANCED"] = 2;

    params[Mcp_CQ_Timestamp] = MlxCfgParamParser(Mcp_CQ_Timestamp, "CQ_TIMESTAMP",
                                                 "When set, IEE1588 (PTP) HW timestamping capability is"
                                                 " reported to the device driver.", paramMap);
    params[Mcp_Steer_ForceVlan] = MlxCfgParamParser(Mcp_Steer_ForceVlan, "STEER_FORCE_VLAN",
                                                    "Force VLAN steering configuration", paramMap);
    params[Mcp_Phy_Param_Mode] = MlxCfgParamParser(Mcp_Phy_Param_Mode, "PHY_PARAMETER_MODE", "Defines the Port PHY parameters mode.", phyParamModeParamMap);
    return MlxCfgInfo("CX3 Global", "", params);
}

bool sortCfg(MlxCfgInfo a, MlxCfgInfo b)
{
    return a.getName() < b.getName();
}

MlxCfgAllInfo::MlxCfgAllInfo()
{
    //Initialize all the configurations
    map<string, u_int32_t> paramMap;
    map<mlxCfgParam, MlxCfgParamParser> params;

    _allInfo.push_back(createPciSettings());
    _allInfo.push_back(createIBDynamicallyConnect());
    _allInfo.push_back(createInfinibandBootSettings());
    _allInfo.push_back(createInternalSettings());
    _allInfo.push_back(createPrebootBootSettings());
    _allInfo.push_back(createRoCECongestionControlECN());
    _allInfo.push_back(createRoCEV1_5NextProtocol());
    _allInfo.push_back(createRoCECongestionControlParameters());
    _allInfo.push_back(createVPISettings());
    _allInfo.push_back(createWakeOnLAN());
    _allInfo.push_back(createBootSettingsExt());
    _allInfo.push_back(createCX3GlobalConf());
    std::sort(_allInfo.begin(), _allInfo.end(), sortCfg);
}

void MlxCfgAllInfo::printShortDesc()
{
    for (u_int32_t i = 0; i < _allInfo.size(); i++) {
        _allInfo[i].printShortDesc();
    }
}

void MlxCfgAllInfo::printLongDesc(FILE *f)
{
    for (u_int32_t i = 0; i < _allInfo.size(); i++) {
        _allInfo[i].printLongDesc(f);
    }
}

mlxCfgStatus MlxCfgAllInfo::getParamParser(mlxCfgParam p, MlxCfgParamParser& paramParser)
{
    for (u_int32_t j = 0; j < _allInfo.size(); j++) {
        if (_allInfo[j].getParamParser(p, paramParser) == MLX_CFG_OK) {
            return MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

mlxCfgStatus MlxCfgAllInfo::parseParam(string tag, string strVal, u_int32_t& val, mlxCfgParam& param)
{
    MlxCfgParamParser paramParser;
    for (u_int32_t j = 0; j < _allInfo.size(); j++) {
        if (_allInfo[j].getParamParser(tag, paramParser) == MLX_CFG_OK) {
            param = paramParser.getParam();
            return (paramParser.parseUserInput(strVal, val)) ?
                   MLX_CFG_ERROR :
                   MLX_CFG_OK;
        }
    }
    return MLX_CFG_ERROR;
}

