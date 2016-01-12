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
    _deviceId = DeviceUnknown;
    _suppVec = 0;
    _isFifthGen = false;
    return;
}

MlxCfgOps::~MlxCfgOps()
{
    if (_mf) {
        mclose(_mf);
    }
    for(map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        delete it->second;
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

int MlxCfgOps::isDefaultSupported(bool &defaultSupported)
{
    struct tools_open_nvqgc nvqgcTlv;

    if(!_isFifthGen){
        defaultSupported = true;
        return ME_OK;
    }

    memset(&nvqgcTlv, 0, sizeof(struct tools_open_nvqgc));
    MError rc;

    mft_signal_set_handling(1);
    rc = reg_access_nvqgc(_mf, REG_ACCESS_METHOD_GET, &nvqgcTlv);
    dealWithSignal();
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_INTERNAL_ERROR) {
        defaultSupported = 0;
        return ME_OK;
    } else if(rc == ME_OK){
        defaultSupported = nvqgcTlv.read_factory_settings_support;
        return ME_OK;
    }
    return rc;
}

int MlxCfgOps::openComChk()
{
    bool rc;
    int ret;
    u_int32_t type = 0;
    // check if we support Tools HCR and update _suppVec
    if (_isFifthGen) {
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
        rc = supportsNVData(); CHECK_RC(rc);
    } else {
        rc = supportsToolsHCR(); CHECK_RC(rc);
    }

    // update cfg specific info.
    // TODO: adrianc: when getting defaults for 4th gen , perform queryDefParams only once and pass struct to classes to avoid calling multiple times
    for (std::map<mlxCfgType, CfgParams*>::iterator paramIt = _cfgList.begin(); paramIt != _cfgList.end(); paramIt++) {
        paramIt->second->setDevCapVec(_suppVec);
        if (paramIt->second->cfgSupported(_mf)) {
            ret = paramIt->second->getDefaultParams(_mf);
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
    case DeviceConnectX4LX:
        _isFifthGen = true;
        break;
    default:
        return errmsg(MCE_UNSUPPORTED_DEVICE);
    }

    // init _cfgList, _param2TypeMap
    if (_isFifthGen) {
        // Wake On LAN
        _cfgList[Mct_Wol] = new WolParams5thGen();
        _param2TypeMap[Mcp_Wol_Magic_En] = Mct_Wol;
        // Vpi Settings
        _cfgList[Mct_Vpi_P1] = new VpiParams5thGen(1);
        _cfgList[Mct_Vpi_P2] = new VpiParams5thGen(2);
        _param2TypeMap[Mcp_Link_Type_P1] = Mct_Vpi_P1;
        _param2TypeMap[Mcp_Link_Type_P2] = Mct_Vpi_P2;
        // PCI settings
        _cfgList[Mct_Pci] = new PciParams5thGen();
        _param2TypeMap[Mcp_Sriov_En] = Mct_Pci;
        _param2TypeMap[Mcp_Num_Of_Vfs] = Mct_Pci;
        _param2TypeMap[Mcp_Fpp_En] = Mct_Pci;
        _param2TypeMap[Mcp_PF_Log_Bar_Size] = Mct_Pci;
        _param2TypeMap[Mcp_VF_Log_Bar_Size] = Mct_Pci;
        _param2TypeMap[Mcp_Num_Pf_Msix] = Mct_Pci;
        _param2TypeMap[Mcp_Num_Vf_Msix] = Mct_Pci;
        // TPT settings
        _cfgList[Mct_Tpt] = new TptParams5thGen();
        _param2TypeMap[Mcp_Log_Tpt_Size] = Mct_Tpt;
        // Infiniband DC settings
        _cfgList[Mct_Dc] = new IBDCParams5thGen();
        _param2TypeMap[Mcp_Log_Dcr_Hash_Table_Size] = Mct_Dc;
        _param2TypeMap[Mcp_Dcr_Lifo_Size] = Mct_Dc;
        // RoCE v1.5 next protocol
        _cfgList[Mct_RoCE_Next_Protocol] = new RoCENextProtocolParams5thGen();
        _param2TypeMap[Mcp_RoCE_Next_Protocol] = Mct_RoCE_Next_Protocol;
        // RoCE CC parameters
        _cfgList[Mct_RoCE_CC_P1] = new RoCECCParams5thGen(1);
        _cfgList[Mct_RoCE_CC_P2] = new RoCECCParams5thGen(2);
        _param2TypeMap[Mcp_RoCE_CC_Algorithm_P1] = Mct_RoCE_CC_P1;
        _param2TypeMap[Mcp_RoCE_CC_Prio_Mask_P1] = Mct_RoCE_CC_P1;
        _param2TypeMap[Mcp_RoCE_CC_Algorithm_P2] = Mct_RoCE_CC_P2;
        _param2TypeMap[Mcp_RoCE_CC_Prio_Mask_P2] = Mct_RoCE_CC_P2;
        // RoCE CC ECN parameters
        _cfgList[Mct_RoCE_CC_Ecn_P1] = new RoCECCEcnParams5thGen(1);
        _cfgList[Mct_RoCE_CC_Ecn_P2] = new RoCECCEcnParams5thGen(2);
        _param2TypeMap[Mcp_Clamp_Tgt_Rate_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Time_Reset_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Byte_Reset_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Threshold_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Max_Rate_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Ai_Rate_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Hai_Rate_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Gd_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Min_Dec_Fac_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rpg_Min_Rate_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rate_To_Set_On_First_Cnp_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Dce_Tcp_G_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Dce_Tcp_Rtt_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Rate_Reduce_Monitor_Period_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Initial_Alpha_Value_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Min_Time_Between_Cnps_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Cnp_Dscp_P1] = Mct_RoCE_CC_Ecn_P1;
        _param2TypeMap[Mcp_Cnp_802p_Prio_P1] = Mct_RoCE_CC_Ecn_P1;

        _param2TypeMap[Mcp_Clamp_Tgt_Rate_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Time_Reset_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Byte_Reset_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Threshold_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Max_Rate_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Ai_Rate_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Hai_Rate_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Gd_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Min_Dec_Fac_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rpg_Min_Rate_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rate_To_Set_On_First_Cnp_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Dce_Tcp_G_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Dce_Tcp_Rtt_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Rate_Reduce_Monitor_Period_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Initial_Alpha_Value_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Min_Time_Between_Cnps_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Cnp_Dscp_P2] = Mct_RoCE_CC_Ecn_P2;
        _param2TypeMap[Mcp_Cnp_802p_Prio_P2] = Mct_RoCE_CC_Ecn_P2;

        _cfgList[Mct_External_Port] = new ExternalPort5thGen();
        _param2TypeMap[Mcp_Port_Owner] = Mct_External_Port;
        _param2TypeMap[Mcp_Allow_Rd_Counters] = Mct_External_Port;

        _cfgList[Mct_Boot_Settings_Extras_5thGen] = new BootSettingsExtParams5thGen();
        _param2TypeMap[Mcp_Boot_Settings_Ext_IP_Ver] = Mct_Boot_Settings_Extras_5thGen;

    } else {
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
        _param2TypeMap[Mcp_Link_Type_P2] = Mct_Vpi_P2;
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

    if (!isLegal(cfgParam2Type(param))) {
        return false;
    }

    return _cfgList[cfgParam2Type(param)]->cfgSupported(_mf, param);
}

int MlxCfgOps::getCfg(mlxCfgParam cfgParam, u_int32_t& val, bool getDefault)
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
            return errmsgConcatMsg(rc,*_cfgList[cfgParam2Type(cfgParam)]);
        }
        val = (_cfgList[cfgParam2Type(cfgParam)])->getParam(cfgParam);
    }
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
    for(std::map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        it->second->setIgnoreSoftLimits(val);
    }
    return;
}

void MlxCfgOps::setIgnoreHardLimits(bool val)
{
    for(std::map<mlxCfgType, CfgParams*>::iterator it = _cfgList.begin(); it != _cfgList.end(); it++) {
        it->second->setIgnoreHardLimits(val);
    }
    return;
}

int MlxCfgOps::invalidateCfgs4thGen()
{
    struct tools_open_mnvia mnviaTlv;
    u_int8_t buffer[TOOLS_OPEN_MNVIA_SIZE] = {0};
    int rc;
    memset(&mnviaTlv, 0, sizeof(struct tools_open_mnvia));
    tools_open_mnvia_pack(&mnviaTlv, buffer);
    mft_signal_set_handling(1);
    rc = reg_access_mnvia(_mf, REG_ACCESS_METHOD_SET, &mnviaTlv);
    dealWithSignal();
    return rc;
}

int MlxCfgOps::invalidateCfgs5thGen()
{
    struct tools_open_nvia nviaTlv;
    u_int8_t buffer[TOOLS_OPEN_NVIA_SIZE] = {0};
    int rc;
    memset(&nviaTlv, 0, sizeof(struct tools_open_nvia));
    tools_open_nvia_pack(&nviaTlv, buffer);
    mft_signal_set_handling(1);
    rc = reg_access_nvia(_mf, REG_ACCESS_METHOD_SET, &nviaTlv);
    dealWithSignal();
    return rc;
}

int MlxCfgOps::invalidateCfgs()
{
    int rc;
    if (_isFifthGen) {
        rc = invalidateCfgs5thGen();
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
    if (_cfgList.find(cfg) != _cfgList.end()) {
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


const char* MlxCfgOps::loadConfigurationGetStr()
{
    int rc;
    struct cibfw_register_mfrl mfrl;
    memset(&mfrl, 0, sizeof(mfrl));
    if (_isFifthGen && (_deviceId == DeviceConnectX4 || _deviceId == DeviceConnectX4LX)) {
        // send warm boot (bit 6)
        mfrl.reset_level = 1 << 6;
        mft_signal_set_handling(1);
        rc = reg_access_mfrl(_mf,REG_ACCESS_METHOD_SET, &mfrl);
        dealWithSignal();
        if (rc) {
            return "Please power cycle machine to load new configurations.";
        }
    }
    return "Please reboot machine to load new configurations.";
}


mlxCfgType MlxCfgOps::cfgParam2Type(mlxCfgParam param)
{
    if (_param2TypeMap.find(param) == _param2TypeMap.end()) {
        return Mct_Last;
    }
    return _param2TypeMap[param];
}

int MlxCfgOps::setRawCfg(std::vector<u_int32_t> rawTlvVec)
{
    if (!_isFifthGen) {
        return errmsg("Setting Raw Configuration is supported for 5th Generation devices only.");
    }
    RawCfgParams5thGen rawTlv;
    if (rawTlv.setRawData(rawTlvVec)) {
        return errmsg("%s", rawTlv.err());
    }

    if (rawTlv.setOnDev(_mf)) {
        return errmsg("%s", rawTlv.err());
    }
    return MCE_SUCCESS;
}

int MlxCfgOps::dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump)
{
    RawCfgParams5thGen rawTlv;
    if (rawTlv.setRawData(rawTlvVec)) {
        return errmsg("%s", rawTlv.err());
    }
    tlvDump = rawTlv.dumpTlv();
    return MCE_SUCCESS;
}
