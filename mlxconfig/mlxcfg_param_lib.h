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
 * mlxcfg_param_lib.h
 *
 *  Created on: Mar 22, 2015
 *      Author: adrianc
 */

#ifndef MLXCFG_PARAM_LIB_H_
#define MLXCFG_PARAM_LIB_H_

#include <vector>
#include <utility>
#include <stdexcept>

#include <errmsg.h>
#include <tools_layouts/tools_open_layouts.h>

#include "mlxcfg_utils.h"


#define WOL_TYPE 0x10
#define SRIOV_TYPE 0x11
#define VPI_TYPE 0x12
#define BAR_SIZE_TYPE 0x13
#define CX3_GLOBAL_CONF_TYPE 0x14
#define PCI_SETTINGS_TYPE 0x80
#define PCI_CAPABILITES_TYPE 0x81
#define TPT_SETTINGS_TYPE 0x82
#define TPT_CAPABILITES_TYPE 0x83
#define PREBOOT_BOOT_SETTINGS_TYPE 0x2021
#define INFINIBAND_BOOT_SETTINGS_TYPE 0x2022
#define INFINIBAND_DC_SETTINGS_TYPE 0x190
#define INFINIBAND_DC_CAPABILITIES_TYPE 0x191
#define PORT_BOOT_STATE_TYPE 0x84
#define ROCE_NEXT_PROTOCOL_TYPE 0x10
#define ROCE_CC_TYPE 0x107
#define ROCE_CC_ECN_TYPE 0x108
#define LLDP_CLIENT_SETTINGS_TYPE 0x10a
#define LLDP_NB_CAPABILITIES_TYPE 0x10b
#define EXTERNAL_PORT 0x192
#define BOOT_SETTINGS_EXTRAS_GEN4 0x2001
#define BOOT_SETTINGS_EXTRAS_GEN5 0x195
#define BOOT_SETTINGS_EXTRAS_GEN5_CAP 0x101
#define QOS 0x192
#define QOS_CAP 0x193
#define LLDP_NB_DCBX 0x18E

typedef enum {
    // SRIOV
    Mct_Sriov = 0,
    // Wake on LAN (4th gen)
    Mct_Wol_P1,
    Mct_Wol_P2,
    // VPI settings
    Mct_Vpi_P1,
    Mct_Vpi_P2,
    // BAR size (4th gen)
    Mct_Bar_Size,
    // IB boot settings (4th gen)
    Mct_Boot_Settings_P1,
    Mct_Boot_Settings_P2,
    // Preboot Boot Settings (4th Gen)
    Mct_Preboot_Boot_Settings_P1,
    Mct_Preboot_Boot_Settings_P2,
    //TODO: Boot Settings Extras
    Mct_Boot_Settings_Extras_4thGen_P1,
    Mct_Boot_Settings_Extras_4thGen_P2,
    //CX3 Global Conf
    Mct_CX3_Global_Conf,
    Mct_Last
} mlxCfgType;

typedef enum {
    // PCI settings
    Mcp_Sriov_En = 0,
    Mcp_Num_Of_Vfs,
    // Wake On LAN 4th Gen Port 1
    Mcp_Wol_Magic_En_P1,
    // Wake On LAN 4th Gen Port 2
    Mcp_Wol_Magic_En_P2,
    // VPI settings Port 1
    Mcp_Link_Type_P1,
    Mcp_Phy_Type_P1,
    Mcp_Xfi_Mode_P1,
    Mcp_Force_Mode_P1,
    // VPI settings Port 2
    Mcp_Link_Type_P2,
    Mcp_Phy_Type_P2,
    Mcp_Xfi_Mode_P2,
    Mcp_Force_Mode_P2,
    // BAR size
    Mcp_Log_Bar_Size,
    // TPT settings
    Mcp_Log_Tpt_Size,
    // Boot Pkey Port 1
    Mcp_Boot_Pkey_P1,
    // Boot Pkey Port 2
    Mcp_Boot_Pkey_P2,
    // IB Dynamically connected
    Mcp_Log_Dcr_Hash_Table_Size,
    Mcp_Dcr_Lifo_Size,
    // RoCE v1.5 Next protocol
    Mcp_RoCE_Next_Protocol,
    // RoCE Congestion Control Parameters Port 1
    Mcp_RoCE_CC_Algorithm_P1,
    Mcp_RoCE_CC_Prio_Mask_P1,
    // RoCE Congestion Control Parameters Port 2
    Mcp_RoCE_CC_Algorithm_P2,
    Mcp_RoCE_CC_Prio_Mask_P2,
    // RoCE Congestion Control ECN Port 1
    Mcp_Clamp_Tgt_Rate_P1,
    Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1,
    Mcp_Rpg_Time_Reset_P1,
    Mcp_Rpg_Byte_Reset_P1,
    Mcp_Rpg_Threshold_P1,
    Mcp_Rpg_Max_Rate_P1,
    Mcp_Rpg_Ai_Rate_P1,
    Mcp_Rpg_Hai_Rate_P1,
    Mcp_Rpg_Gd_P1,
    Mcp_Rpg_Min_Dec_Fac_P1,
    Mcp_Rpg_Min_Rate_P1,
    Mcp_Rate_To_Set_On_First_Cnp_P1,
    Mcp_Dce_Tcp_G_P1,
    Mcp_Dce_Tcp_Rtt_P1,
    Mcp_Rate_Reduce_Monitor_Period_P1,
    Mcp_Initial_Alpha_Value_P1,
    Mcp_Min_Time_Between_Cnps_P1,
    Mcp_Cnp_Dscp_P1,
    Mcp_Cnp_802p_Prio_P1,
    // RoCE Congestion Control ECN Port 2
    Mcp_Clamp_Tgt_Rate_P2,
    Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2,
    Mcp_Rpg_Time_Reset_P2,
    Mcp_Rpg_Byte_Reset_P2,
    Mcp_Rpg_Threshold_P2,
    Mcp_Rpg_Max_Rate_P2,
    Mcp_Rpg_Ai_Rate_P2,
    Mcp_Rpg_Hai_Rate_P2,
    Mcp_Rpg_Gd_P2,
    Mcp_Rpg_Min_Dec_Fac_P2,
    Mcp_Rpg_Min_Rate_P2,
    Mcp_Rate_To_Set_On_First_Cnp_P2,
    Mcp_Dce_Tcp_G_P2,
    Mcp_Dce_Tcp_Rtt_P2,
    Mcp_Rate_Reduce_Monitor_Period_P2,
    Mcp_Initial_Alpha_Value_P2,
    Mcp_Min_Time_Between_Cnps_P2,
    Mcp_Cnp_Dscp_P2,
    Mcp_Cnp_802p_Prio_P2,
    // Preboot Boot Settings Port 1
    Mcp_Boot_Option_Rom_En_P1,
    Mcp_Boot_Vlan_En_P1,
    Mcp_Boot_Retry_Cnt_P1,
    Mcp_Legacy_Boot_Protocol_P1,
    Mcp_Boot_Vlan_P1,
    // Preboot Boot Settings Port 2
    Mcp_Boot_Option_Rom_En_P2,
    Mcp_Boot_Vlan_En_P2,
    Mcp_Boot_Retry_Cnt_P2,
    Mcp_Legacy_Boot_Protocol_P2,
    Mcp_Boot_Vlan_P2,
    //External port
    Mcp_Port_Owner,
    Mcp_Allow_Rd_Counters,
    //Boot Settings Ext
    Mcp_Boot_Settings_Ext_IP_Ver,
    Mcp_Boot_Settings_Ext_IP_Ver_P1,
    Mcp_Boot_Settings_Ext_IP_Ver_P2,
    //CX3 Global conf
    Mcp_Phy_Param_Mode,
    Mcp_CQ_Timestamp,
    Mcp_Steer_ForceVlan,
    Mcp_Last
} mlxCfgParam;

typedef std::pair<mlxCfgParam, u_int32_t> cfgInfo;

/*
 *  Basic Param Class
 */

/* Adrianc: add Initialize/Open pure method that will contain all needed initializations (configuration supported defaults capabilities etc...)
 */

class CfgParams : public ErrMsg
{
public:
    CfgParams(mlxCfgType t = Mct_Last, u_int32_t tlvT = 0);
    virtual ~CfgParams() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last) = 0;
    void setDevCapVec(u_int64_t v) {_devCapVec = v;}

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

    virtual int getDefaultAndFromDev(mfile *mf);
    virtual int getFromDev(mfile *mf) = 0;
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false) = 0;
    virtual int getDefaultParams(mfile *mf) = 0;

    void setIgnoreSoftLimits(bool val);
    void setIgnoreHardLimits(bool val);

    mlxCfgType type;
    u_int32_t tlvTypeIdx;
protected:
    // param validadion methods, only checkCfg shuold be called
    virtual bool checkCfg(mfile *mf = NULL);
    virtual bool hardLimitCheck() = 0;
    virtual bool softLimitCheck(mfile *mf = NULL);

    // get default parameters for configuration (4th gen)
    int getDefaultParams4thGen(mfile *mf, struct tools_open_query_def_params_global *global_params);
    int getDefaultParams4thGen(mfile *mf, int port, struct tools_open_query_def_params_per_port *port_params);

    virtual void updateTlvFromClassAttr(void *tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}
    virtual void updateClassAttrFromTlv(void *tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}
    virtual void updateClassDefaultAttrFromTlv(void *tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}

    u_int64_t _devCapVec; // relevant for 4th gen devices
    bool _updated; // set true on get and false on set
    bool _ignoreSoftLimits; // soft limits checks will not be performed for configuration
    bool _ignoreHardLimits; // hard limits checks will not be performed
};

/*
 * SRIOV param classes:
 */

class SriovParams4thGen : public CfgParams
{
public:
    SriovParams4thGen() : CfgParams(Mct_Sriov, SRIOV_TYPE), _sriovEn(MLXCFG_UNKNOWN), _numOfVfs(MLXCFG_UNKNOWN),
        _sriovEnDefault(MLXCFG_UNKNOWN), _numOfVfsDefault(MLXCFG_UNKNOWN), _maxVfs(1) {}
    ~SriovParams4thGen() {};

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);

protected:
    virtual bool hardLimitCheck();

    virtual int updateMaxVfs(mfile *mf);
    virtual bool softLimitCheck(mfile *mf = NULL);
    void setParams(u_int32_t sriovEn, u_int32_t numOfVfs);

    u_int32_t _sriovEn;
    u_int32_t _numOfVfs;
    u_int32_t _sriovEnDefault;
    u_int32_t _numOfVfsDefault;
    u_int32_t _maxVfs;
};


/*
 * HW Timestamp params
 */

class CX3GlobalConfParams : public CfgParams
{
public:
    CX3GlobalConfParams() : CfgParams(Mct_CX3_Global_Conf, CX3_GLOBAL_CONF_TYPE),
        _timestamp(MLXCFG_UNKNOWN), _timestampDefault(MLXCFG_UNKNOWN),
        _steerForceVlan(MLXCFG_UNKNOWN), _steerForceVlanDefault(MLXCFG_UNKNOWN),
        _phyParamMode(MLXCFG_UNKNOWN), _phyParamModeDefault(MLXCFG_UNKNOWN) {}
    ~CX3GlobalConfParams() {};

    bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);
    void setParam(mlxCfgParam paramType, u_int32_t val);
    u_int32_t getParam(mlxCfgParam paramType);
    u_int32_t getDefaultParam(mlxCfgParam paramType);
    int getFromDev(mfile *mf);
    int setOnDev(mfile *mf, bool ignoreCheck = false);
    int getDefaultParams(mfile *mf);

private:
    bool hardLimitCheck();
    void setParams(u_int32_t timestamp, u_int32_t steer_force_vlan, u_int32_t phy_param_mode);

    u_int32_t _timestamp;
    u_int32_t _timestampDefault;
    u_int32_t _steerForceVlan;
    u_int32_t _steerForceVlanDefault;
    u_int32_t _phyParamMode;
    u_int32_t _phyParamModeDefault;
};



/*
 * Boot Settings Extras param classes:
 */

class BootSettingsExtParams : public CfgParams
{
public:
    BootSettingsExtParams(mlxCfgType t, u_int32_t tlvT) : CfgParams(t, tlvT), _ipVer(MLXCFG_UNKNOWN), _ipVerDefault(MLXCFG_UNKNOWN){}
    virtual ~BootSettingsExtParams() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

    virtual int getFromDev(mfile *mf) = 0;
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false) = 0;
    virtual int getDefaultParams(mfile *mf) = 0;

protected:
    bool hardLimitCheck();
    void setParams(u_int32_t _ipVer);

    u_int32_t _ipVer;
    u_int32_t _ipVerDefault;
};

class BootSettingsExtParams4thGen : public BootSettingsExtParams
{
public:
    BootSettingsExtParams4thGen(int port) : BootSettingsExtParams((port == 1) ? Mct_Boot_Settings_Extras_4thGen_P1 : Mct_Boot_Settings_Extras_4thGen_P2,
                                                                  BOOT_SETTINGS_EXTRAS_GEN4),
        _port(port){}
    ~BootSettingsExtParams4thGen() {}

    u_int32_t getDefaultParam(mlxCfgParam paramType);
    void setParam(mlxCfgParam paramType, u_int32_t val);
    u_int32_t getParam(mlxCfgParam paramType);
    bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);
    int getDefaultParams(mfile *mf);

    int getFromDev(mfile *mf);
    int setOnDev(mfile *mf, bool ignoreCheck = false);
private:
    int _port;
};

/*
 * WOL param classes:
 */

class WolParams : public CfgParams
{
public:
    WolParams() : CfgParams(Mct_Last, WOL_TYPE), _wolMagicEn(MLXCFG_UNKNOWN), _wolMagicEnDefault(MLXCFG_UNKNOWN) {}
    virtual ~WolParams() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

    virtual int getFromDev(mfile *mf) = 0;
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false) = 0;
    virtual int getDefaultParams(mfile *mf) = 0;

protected:
    virtual bool hardLimitCheck();
    void setParams(u_int32_t wolMagicEn);
    // Wake on magic packet (atm this is the only mode which is supported)

    u_int32_t _wolMagicEn;
    u_int32_t _wolMagicEnDefault;
};

class WolParams4thGen : public WolParams
{
public:
    WolParams4thGen(int port) : WolParams(), _port(port) {type = _port == 1 ? Mct_Wol_P1 : Mct_Wol_P2;}
    ~WolParams4thGen() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);
private:
    int _port;
};

/*
 * VPI param classes:
 */

class VpiParams : public CfgParams
{
public:
    VpiParams(int port) : CfgParams(port == 1 ? Mct_Vpi_P1 : Mct_Vpi_P2, VPI_TYPE), _port(port), _linkType(MLXCFG_UNKNOWN), _defaultLinkType(MLXCFG_UNKNOWN)
        , _linkTypeDefault(MLXCFG_UNKNOWN), _defaultLinkTypeDefault(MLXCFG_UNKNOWN),
        _isForceModeSupported(false), _isVPISupported(false), _phyType(MLXCFG_UNKNOWN),
        _phyTypeDefault(MLXCFG_UNKNOWN), _xfiMode(MLXCFG_UNKNOWN),
        _xfiModeDefault(MLXCFG_UNKNOWN), _forceMode(MLXCFG_UNKNOWN),
        _forceModeDefault(MLXCFG_UNKNOWN)
    {
        memset(&_vpiTlv, 0, sizeof(_vpiTlv));
    }
    ~VpiParams() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last) = 0;

    virtual int getFromDev(mfile *mf) = 0;
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false) = 0;
    virtual int getDefaultParams(mfile *mf) = 0;

protected:
    int getFromDevComPre();
    int getFromDevComPost(MError mnvaComRC);
    int setOnDevComPre(bool ignoreCheck);
    int setOnDevComPost(MError mnvaComRC);
    void setParams(u_int32_t linkType, u_int32_t defaultLinkType,
                   u_int32_t phyType, u_int32_t xfiMode, u_int32_t forceMode);
    int _port;
    u_int32_t _linkType;
    u_int32_t _defaultLinkType;
    u_int32_t _linkTypeDefault;
    u_int32_t _defaultLinkTypeDefault;
    bool _isForceModeSupported;
    bool _isVPISupported;
    u_int32_t _phyType;
    u_int32_t _phyTypeDefault;
    u_int32_t _xfiMode;
    u_int32_t _xfiModeDefault;
    u_int32_t _forceMode;
    u_int32_t _forceModeDefault;
    // FW TLV (used when actually setting/getting the TLV from FW)
    std::vector<u_int8_t> _tlvBuff;
    struct tools_open_vpi_settings _vpiTlv;


};

class VpiParams4thGen : public VpiParams
{
public:
    VpiParams4thGen(int port) : VpiParams(port){}
    ~VpiParams4thGen() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);
    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);
    virtual bool hardLimitCheck();

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);
    int getDefaultParamsAux(mfile *mft);
};

/*
 * BAR size param classes:
 */

class BarSzParams : public CfgParams
{
public:
    BarSzParams() : CfgParams(Mct_Bar_Size, BAR_SIZE_TYPE), _maxLogBarSz(1), _logBarSz(MLXCFG_UNKNOWN), _logBarSzDefault(MLXCFG_UNKNOWN) {}
    ~BarSzParams() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile *mf) = 0;
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false) = 0;
    virtual int getDefaultParams(mfile *mf) = 0;

protected:
    virtual bool hardLimitCheck();
    virtual bool softLimitCheck(mfile *mf = NULL) = 0;
    virtual int getDefaultBarSz(mfile *mf) = 0;
    void setParams(u_int32_t logBarSz);
    u_int32_t _maxLogBarSz;
    u_int32_t _logBarSz;
    u_int32_t _logBarSzDefault;

};

class BarSzParams4thGen : public BarSzParams
{
public:
    BarSzParams4thGen() : BarSzParams() {}
    ~BarSzParams4thGen() {}

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);
protected:
    virtual bool softLimitCheck(mfile *mf = NULL);
    virtual int getDefaultBarSz(mfile *mf);
};

/*
 * Infiniband boot settings parameter Class (4thGen devices only)
 */
class InfinibandBootSettingsParams4thGen : public CfgParams
{
public:
    InfinibandBootSettingsParams4thGen(int port) : CfgParams((port == 1 ? Mct_Boot_Settings_P1 : Mct_Boot_Settings_P2),
                                                             INFINIBAND_BOOT_SETTINGS_TYPE), _port(port), _bootPkey(MLXCFG_UNKNOWN), _bootPkeyDefault(MLXCFG_UNKNOWN) {}
    ~InfinibandBootSettingsParams4thGen() {};

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);

protected:
    virtual bool hardLimitCheck();
    void setParams(u_int32_t bootPkey);

    int _port;
    u_int32_t _bootPkey;
    u_int32_t _bootPkeyDefault;

};

/*
 * Preboot Boot Settings Class (4thGen devices only)
 */

class PrebootBootSettingsParams4thGen : public CfgParams
{
public:
    PrebootBootSettingsParams4thGen(int port) : CfgParams((port == 1 ? Mct_Preboot_Boot_Settings_P1 : Mct_Preboot_Boot_Settings_P2), PREBOOT_BOOT_SETTINGS_TYPE),
        _bootOptionRomEn(MLXCFG_UNKNOWN), _bootVlanEn(MLXCFG_UNKNOWN), _bootRetryCnt(MLXCFG_UNKNOWN),
        _legacyBootProtocol(MLXCFG_UNKNOWN), _bootVlan(MLXCFG_UNKNOWN),
        _bootOptionRomEnDefault(MLXCFG_UNKNOWN), _bootVlanEnDefault(MLXCFG_UNKNOWN), _bootRetryCntDefault(MLXCFG_UNKNOWN),
        _legacyBootProtocolDefault(MLXCFG_UNKNOWN), _bootVlanDefault(MLXCFG_UNKNOWN),
        _port(port) {}
    ~PrebootBootSettingsParams4thGen() {};

    virtual bool cfgSupported(mfile *mf, mlxCfgParam param = Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile *mf);
    virtual int setOnDev(mfile *mf, bool ignoreCheck = false);
    virtual int getDefaultParams(mfile *mf);

protected:
    virtual bool hardLimitCheck();

    virtual void updateTlvFromClassAttr(void *tlv);
    virtual void updateClassAttrFromTlv(void *tlv);
    virtual void updateClassDefaultAttrFromTlv(void *tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t bootOptionRomEn, u_int32_t bootVlanEn, u_int32_t bootRetryCnt,
                   u_int32_t legacyBootProtocol, u_int32_t bootVlan);

    u_int32_t _bootOptionRomEn;
    u_int32_t _bootVlanEn;
    u_int32_t _bootRetryCnt;
    u_int32_t _legacyBootProtocol;
    u_int32_t _bootVlan;

    u_int32_t _bootOptionRomEnDefault;
    u_int32_t _bootVlanEnDefault;
    u_int32_t _bootRetryCntDefault;
    u_int32_t _legacyBootProtocolDefault;
    u_int32_t _bootVlanDefault;

    int _port;
};

#endif /* MLXCFG_PARAM_LIB_H_ */
