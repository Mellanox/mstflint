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

#ifndef MLXCFG_PARAM_LIB_H_
#define MLXCFG_PARAM_LIB_H_

#include <vector>
#include <utility>
#include <stdexcept>

#include <errmsg.h>
#include <tools_layouts/tools_open_layouts.h>

#define MLXCFG_UNKNOWN 0xffffffff

#define WOL_TYPE 0x10
#define SRIOV_TYPE 0x11
#define VPI_TYPE 0x12
#define BAR_SIZE_TYPE 0x13
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
#define LLDP_NB_SETTINGS_TYPE 0x10a
#define LLDP_NB_CAPABILITIES_TYPE 0x10b
#define EXTERNAL_PORT 0x192
#define BOOT_SETTINGS_EXTRAS_GEN4 0x2001
#define BOOT_SETTINGS_EXTRAS_GEN5 0x195
#define BOOT_SETTINGS_EXTRAS_GEN5_CAP 0x101
typedef enum {
    // SRIOV
    Mct_Sriov = 0,
    // Wake on LAN (4th gen)
    Mct_Wol_P1,
    Mct_Wol_P2,
    // Wake on LAN (5th gen)
    Mct_Wol,
    // VPI settings
    Mct_Vpi_P1,
    Mct_Vpi_P2,
    // BAR size (4th gen)
    Mct_Bar_Size,
    // PCI settings (5th gen)
    Mct_Pci,
    // TPT settings (5th gen)
    Mct_Tpt,
    // IB boot settings (4th gen)
    Mct_Boot_Settings_P1,
    Mct_Boot_Settings_P2,
    // IB dynamically connected (5th gen)
    Mct_Dc,
    // RoCE v1.5 next protocol (5th gen)
    Mct_RoCE_Next_Protocol,
    // RoCE congestion control (5th gen)
    Mct_RoCE_CC_P1,
    Mct_RoCE_CC_P2,
    // RoCE congestion control ECN (5th gen)
    Mct_RoCE_CC_Ecn_P1,
    Mct_RoCE_CC_Ecn_P2,
    // Preboot Boot Settings (4th Gen)
    Mct_Preboot_Boot_Settings_P1,
    Mct_Preboot_Boot_Settings_P2,
    Mct_External_Port,
    //TODO: Boot Settings Extras
    Mct_Boot_Settings_Extras_5thGen,
    Mct_Boot_Settings_Extras_4thGen_P1,
    Mct_Boot_Settings_Extras_4thGen_P2,
    Mct_Last
} mlxCfgType;

typedef enum {
    // PCI settings
    Mcp_Sriov_En = 0,
    Mcp_Num_Of_Vfs,
    Mcp_Fpp_En,
    Mcp_PF_Log_Bar_Size,
    Mcp_VF_Log_Bar_Size,
    Mcp_Num_Pf_Msix,
    Mcp_Num_Vf_Msix,
    // Wake On LAN 4th Gen Port 1
    Mcp_Wol_Magic_En_P1,
    // Wake On LAN 4th Gen Port 2
    Mcp_Wol_Magic_En_P2,
    // Wake On LAN 5th Gen
    Mcp_Wol_Magic_En,
    // VPI settings Port 1
    Mcp_Link_Type_P1,
    // VPI settings Port 2
    Mcp_Link_Type_P2,
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
    Mcp_Last
} mlxCfgParam;

typedef std::pair<mlxCfgParam, u_int32_t> cfgInfo;

/*
 *  Basic Param Class
 */

/* Adrianc: add Initialize/Open pure method that will contain all needed initializations (configuration supported defaults capabilities etc...)
*/


class RawCfgParams5thGen : public ErrMsg
{
public:
    RawCfgParams5thGen();
    ~RawCfgParams5thGen() {}
    int setRawData(const std::vector<u_int32_t>& tlvBuff);
    int setOnDev(mfile* mf);
    std::string dumpTlv();
private:
    int verifyTlv();
    std::vector<u_int32_t> _tlvBuff;
    struct tools_open_nvda _nvdaTlv;
};


class CfgParams : public ErrMsg
{
public:
    CfgParams(mlxCfgType t=Mct_Last, u_int32_t tlvT=0);
    virtual ~CfgParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;
    void setDevCapVec(u_int64_t v) {_devCapVec = v;}

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

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

    virtual void updateTlvFromClassAttr(void* tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}
    virtual void updateClassAttrFromTlv(void* tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}
    virtual void updateClassDefaultAttrFromTlv(void* tlv) {(void)tlv; throw std::logic_error("Function Not Implemented");}

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
    SriovParams4thGen() : CfgParams(Mct_Sriov, SRIOV_TYPE) , _sriovEn(MLXCFG_UNKNOWN), _numOfVfs(MLXCFG_UNKNOWN),
                _sriovEnDefault(MLXCFG_UNKNOWN), _numOfVfsDefault(MLXCFG_UNKNOWN), _maxVfs(1) {}
    ~SriovParams4thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();

    virtual int updateMaxVfs(mfile* mf);
    virtual bool softLimitCheck(mfile* mf=NULL);
    void setParams(u_int32_t sriovEn, u_int32_t numOfVfs);

    u_int32_t _sriovEn;
    u_int32_t _numOfVfs;
    u_int32_t _sriovEnDefault;
    u_int32_t _numOfVfsDefault;
    u_int32_t _maxVfs;
};

/*
 * Boot Settings Extras param classes:
 */

class BootSettingsExtParams : public CfgParams
{
public:
    BootSettingsExtParams(mlxCfgType t, u_int32_t tlvT) : CfgParams(t, tlvT), _ipVer(MLXCFG_UNKNOWN), _ipVerDefault(MLXCFG_UNKNOWN){}
    virtual ~BootSettingsExtParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf)=0;

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
    bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
    int getDefaultParams(mfile* mf);

    int getFromDev(mfile* mf);
    int setOnDev(mfile* mf, bool ignoreCheck=false);
private:
    int _port;
};

class BootSettingsExtParams5thGen : public BootSettingsExtParams
{
public:
    BootSettingsExtParams5thGen() : BootSettingsExtParams(Mct_Boot_Settings_Extras_5thGen, BOOT_SETTINGS_EXTRAS_GEN5) {}
    ~BootSettingsExtParams5thGen() {}

    u_int32_t getBootSettingsExtCapabilitiesTlvTypeBe();
    bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
    u_int32_t getParam(mlxCfgParam paramType);
    u_int32_t getDefaultParam(mlxCfgParam paramType);
    void setParam(mlxCfgParam paramType, u_int32_t val);
    int getFromDev(mfile* mf);
    int setOnDev(mfile* mf, bool ignoreCheck=false);
    void updateClassAttrFromDefaultParams();
    void updateTlvFromClassAttr(void* tlv);
    void updateClassAttrFromTlv(void* tlv);
    void updateClassDefaultAttrFromTlv(void* tlv);
    u_int32_t getTlvTypeBe();
    int getDefaultParams(mfile* mf);
    int getDefaultParamsAux(mfile* mf);
};
/*
 * WOL param classes:
 */

class WolParams : public CfgParams
{
public:
    WolParams() : CfgParams(Mct_Last, WOL_TYPE), _wolMagicEn(MLXCFG_UNKNOWN), _wolMagicEnDefault(MLXCFG_UNKNOWN) {}
    virtual ~WolParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType) = 0;

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
private:
    int _port;
};

class WolParams5thGen : public WolParams
{
public:
    WolParams5thGen() : WolParams() {type = Mct_Wol;}
    ~WolParams5thGen() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
};


/*
 * VPI param classes:
 */

class VpiParams : public CfgParams
{
public:
    VpiParams(int port) : CfgParams(port == 1 ? Mct_Vpi_P1 : Mct_Vpi_P2, VPI_TYPE), _port(port), _linkType(MLXCFG_UNKNOWN), _defaultLinkType(MLXCFG_UNKNOWN)
    , _linkTypeDefault(MLXCFG_UNKNOWN), _defaultLinkTypeDefault(MLXCFG_UNKNOWN){
        _vpiTlv.default_link_type = 0;
        _vpiTlv.network_link_type = 0;
    }
    ~VpiParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    int getFromDevComPre();
    int getFromDevComPost(MError mnvaComRC);
    int setOnDevComPre(bool ignoreCheck);
    int setOnDevComPost(MError mnvaComRC);
    void setParams(u_int32_t _linkType, u_int32_t _defaultLinkType);

    int _port;
    u_int32_t _linkType;
    u_int32_t _defaultLinkType;
    u_int32_t _linkTypeDefault;
    u_int32_t _defaultLinkTypeDefault;
    // FW TLV (used when actually setting/getting the TLV from FW)
    std::vector<u_int8_t> _tlvBuff;
    struct tools_open_vpi_settings _vpiTlv;


};

class VpiParams4thGen : public VpiParams
{
public:
    VpiParams4thGen(int port) : VpiParams(port){}
    ~VpiParams4thGen() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);
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
    BarSzParams() : CfgParams(Mct_Bar_Size, BAR_SIZE_TYPE) ,_maxLogBarSz(1), _logBarSz(MLXCFG_UNKNOWN), _logBarSzDefault(MLXCFG_UNKNOWN) {}
    ~BarSzParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    virtual bool hardLimitCheck();
    virtual bool softLimitCheck(mfile* mf=NULL) = 0;
    virtual int getDefaultBarSz(mfile* mf) = 0;
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    virtual bool softLimitCheck(mfile* mf=NULL);
    virtual int getDefaultBarSz(mfile* mf);
};


/*
 * PCI parameters Class (5thGen devices only)
 */

class PciParams5thGen : public CfgParams
{
public:
    PciParams5thGen() : CfgParams(Mct_Pci, PCI_SETTINGS_TYPE) , _sriovEn(MLXCFG_UNKNOWN), _numOfVfs(MLXCFG_UNKNOWN),\
                        _fppEn(MLXCFG_UNKNOWN), _pfLogBarSize(MLXCFG_UNKNOWN), _vfLogBarSize(MLXCFG_UNKNOWN),\
                        _numPfMsix(MLXCFG_UNKNOWN), _numVfMsix(MLXCFG_UNKNOWN), _sriovEnDefault(MLXCFG_UNKNOWN),\
                        _numOfVfsDefault(MLXCFG_UNKNOWN), _fppEnDefault(MLXCFG_UNKNOWN), _pfLogBarSizeDefault(MLXCFG_UNKNOWN),\
                        _vfLogBarSizeDefault(MLXCFG_UNKNOWN), _numPfMsixDefault(MLXCFG_UNKNOWN), _numVfMsixDefault(MLXCFG_UNKNOWN),\
                        _numOfPfs(MLXCFG_UNKNOWN), _numOfPfsValid(0), _sriovSupported(false),_maxVfsPerPf(0),\
                        _fppSupported(false), _pfLogBarSizeSuppored(false), _vfLogBarSizeSuppored(false),\
                        _numPfMsixSupported(false), _numVfMsixSupported(false),_maxLogPfBarSize(0), _maxLogVfBarSize(0),\
                        _maxTotalBarValid(0), _maxTotalBar(1), _maxNumPfMsix(0), _maxNumVfMsix(0),_maxTotalMsixValid(0),\
                        _maxTotalMsix(0), _userSpecifiedSRIOV(false), _userSpecifiedFPP(false),_userSpecifiedPfLogBarSize(false),\
                        _userSpecifiedVfLogBarSize(false),_userSpecifiedNumPfMsix(false),_userSpecifiedNumVfMsix(false){}
    ~PciParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    virtual bool softLimitCheck(mfile* mf=NULL);
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getPciSettingsTlvTypeBe();
    u_int32_t getPciCapabilitiesTlvTypeBe();
    void setParams(u_int32_t sriovEn, u_int32_t numOfVfs, u_int32_t fppEn, u_int32_t pfLogBarSize,
            u_int32_t vfLogBarSize, u_int32_t numOfPfs, u_int32_t numPfMsix, u_int32_t numVfMsix);

private:
    u_int32_t calcVfLogBarSize();
    u_int32_t calcPfLogBarSize();
    u_int32_t calcTotalBar();
    u_int32_t calcNumOfVfs();

    u_int32_t _sriovEn;
    u_int32_t _numOfVfs;
    u_int32_t _fppEn;
    u_int32_t _pfLogBarSize;
    u_int32_t _vfLogBarSize;
    u_int32_t _numPfMsix;
    u_int32_t _numVfMsix;

    u_int32_t _sriovEnDefault;
    u_int32_t _numOfVfsDefault;
    u_int32_t _fppEnDefault;
    u_int32_t _pfLogBarSizeDefault;
    u_int32_t _vfLogBarSizeDefault;
    u_int32_t _numPfMsixDefault;
    u_int32_t _numVfMsixDefault;

    u_int32_t _numOfPfs;
    u_int32_t _numOfPfsValid;


    // defaults and capabilities
    bool      _sriovSupported;
    u_int32_t _maxVfsPerPf;
    bool      _fppSupported;
    bool      _pfLogBarSizeSuppored;
    bool      _vfLogBarSizeSuppored;
    bool      _numPfMsixSupported;
    bool      _numVfMsixSupported;
    u_int32_t _maxLogPfBarSize;
    u_int32_t _maxLogVfBarSize;
    u_int32_t _maxTotalBarValid;
    u_int32_t _maxTotalBar;
    u_int32_t _maxNumPfMsix;
    u_int32_t _maxNumVfMsix;
    u_int32_t _maxTotalMsixValid;
    u_int32_t _maxTotalMsix;

    // class members used for indication
    bool _userSpecifiedSRIOV;
    bool _userSpecifiedFPP;
    bool _userSpecifiedPfLogBarSize;
    bool _userSpecifiedVfLogBarSize;
    bool _userSpecifiedNumPfMsix;
    bool _userSpecifiedNumVfMsix;

};

/*
 * TPT parameters Class (5thGen devices only)
 */

class TptParams5thGen : public CfgParams
{
public:
    TptParams5thGen() : CfgParams(Mct_Tpt, TPT_SETTINGS_TYPE) , _logMaxPayloadSize(MLXCFG_UNKNOWN),
    _logMaxPayloadSizeDefault(MLXCFG_UNKNOWN), _logMaxPayloadSizeSupported(false)
    {}
    ~TptParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    int getFromDev(mfile* mf, bool getDefault);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getTptSettingsTlvTypeBe();
    u_int32_t getTptCapabilitiesTlvTypeBe();
    void setParams(u_int32_t logMaxPayloadSize);

    u_int32_t _logMaxPayloadSize;
    u_int32_t _logMaxPayloadSizeDefault;

    // defaults and capabilities
    bool      _logMaxPayloadSizeSupported;
};

/*
 * Infiniband boot settings parameter Class (4thGen devices only)
 */
class InfinibandBootSettingsParams4thGen : public CfgParams
{
public:
    InfinibandBootSettingsParams4thGen(int port) : CfgParams((port == 1 ? Mct_Boot_Settings_P1 : Mct_Boot_Settings_P2),
            INFINIBAND_BOOT_SETTINGS_TYPE) , _port(port), _bootPkey(MLXCFG_UNKNOWN), _bootPkeyDefault(MLXCFG_UNKNOWN) {}
    ~InfinibandBootSettingsParams4thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    void setParams(u_int32_t bootPkey);

    int _port;
    u_int32_t _bootPkey;
    u_int32_t _bootPkeyDefault;

};

/*
 * Infiniband DC (Dynamically Connected) parameters Class (5thGen devices only)
 */

class IBDCParams5thGen : public CfgParams
{
public:
    IBDCParams5thGen() : CfgParams(Mct_Dc, INFINIBAND_DC_SETTINGS_TYPE) , _logDcrHashTableSize(MLXCFG_UNKNOWN), _dcrLifoSize(MLXCFG_UNKNOWN),
        _logDcrHashTableSizeDefault(MLXCFG_UNKNOWN), _dcrLifoSizeDefault(MLXCFG_UNKNOWN), _minLogDcrHashTableSize(0),
        _maxLogDcrHashTableSize(0), _minDcrLifoSize(0), _maxDcrLifoSize(0){}
    ~IBDCParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    int getFromDev(mfile* mf, bool getDefault);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getTlvTypeBe();
    u_int32_t getDcCapabilitiesTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t logDcrHashTableSize, u_int32_t dcrLifoSize);

    u_int32_t _logDcrHashTableSize;
    u_int32_t _dcrLifoSize;

    u_int32_t _logDcrHashTableSizeDefault;
    u_int32_t _dcrLifoSizeDefault;

    // defaults and capabilities
    u_int32_t _minLogDcrHashTableSize;
    u_int32_t _maxLogDcrHashTableSize;
    u_int32_t _minDcrLifoSize;
    u_int32_t _maxDcrLifoSize;
};

/*
 * RoCE v1.5 next protocol Class (5thGen devices only)
 */

class RoCENextProtocolParams5thGen : public CfgParams
{
public:
    RoCENextProtocolParams5thGen() : CfgParams(Mct_RoCE_Next_Protocol, ROCE_NEXT_PROTOCOL_TYPE) , _nextProtocol(MLXCFG_UNKNOWN)
                                    , _nextProtocolDefault(MLXCFG_UNKNOWN){}
    ~RoCENextProtocolParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t nextProtocol);

    u_int32_t _nextProtocol;

    u_int32_t _nextProtocolDefault;
};

/*
 * RoCE CC parameters Class (5thGen devices only)
 */

class RoCECCParams5thGen : public CfgParams
{
public:
    RoCECCParams5thGen(int port) : CfgParams((port == 1 ? Mct_RoCE_CC_P1 : Mct_RoCE_CC_P2), ROCE_CC_TYPE),
                                   _port(port), _roceCcAlgorithm(MLXCFG_UNKNOWN), _roceCcPrioMask(MLXCFG_UNKNOWN)
                                    , _roceCcAlgorithmDefault(MLXCFG_UNKNOWN), _roceCcPrioMaskDefault(MLXCFG_UNKNOWN){}
    ~RoCECCParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t roceCcAlgorithm, u_int32_t roceCcPrioMask);

    int _port;
    u_int32_t _roceCcAlgorithm;
    u_int32_t _roceCcPrioMask;

    u_int32_t _roceCcAlgorithmDefault;
    u_int32_t _roceCcPrioMaskDefault;
};

/*
 * RoCE CC ECN parameters Class (5thGen devices only)
 */

class RoCECCEcnParams5thGen : public CfgParams
{
public:
    RoCECCEcnParams5thGen(int port) : CfgParams((port == 1 ? Mct_RoCE_CC_Ecn_P1 : Mct_RoCE_CC_Ecn_P2), ROCE_CC_ECN_TYPE),
                                    _port(port), _clampTgtRate(MLXCFG_UNKNOWN), _clampTgtRateAfterTimeInc(MLXCFG_UNKNOWN),
                                    _rpgTimeReset(MLXCFG_UNKNOWN), _rpgByteReset(MLXCFG_UNKNOWN), _rpgThreshold(MLXCFG_UNKNOWN),
                                    _rpgMaxRate(MLXCFG_UNKNOWN), _rpgAiRate(MLXCFG_UNKNOWN), _rpgHaiRate(MLXCFG_UNKNOWN),
                                    _rpgGd(MLXCFG_UNKNOWN), _rpgMinDecFac(MLXCFG_UNKNOWN), _rpgMinRate(MLXCFG_UNKNOWN),
                                    _rateToSetOnFirstCnp(MLXCFG_UNKNOWN), _dceTcpG(MLXCFG_UNKNOWN), _dceTcpRtt(MLXCFG_UNKNOWN),
                                    _rateReduceMonitorPeriod(MLXCFG_UNKNOWN), _initialAlphaValue(MLXCFG_UNKNOWN),
                                    _minTimeBetweenCnps(MLXCFG_UNKNOWN), _cnpDscp(MLXCFG_UNKNOWN), _cnp802pPrio(MLXCFG_UNKNOWN)
                                    , _clampTgtRateDefault(MLXCFG_UNKNOWN), _clampTgtRateAfterTimeIncDefault(MLXCFG_UNKNOWN),
                                    _rpgTimeResetDefault(MLXCFG_UNKNOWN), _rpgByteResetDefault(MLXCFG_UNKNOWN), _rpgThresholdDefault(MLXCFG_UNKNOWN),
                                    _rpgMaxRateDefault(MLXCFG_UNKNOWN), _rpgAiRateDefault(MLXCFG_UNKNOWN), _rpgHaiRateDefault(MLXCFG_UNKNOWN),
                                    _rpgGdDefault(MLXCFG_UNKNOWN), _rpgMinDecFacDefault(MLXCFG_UNKNOWN), _rpgMinRateDefault(MLXCFG_UNKNOWN),
                                    _rateToSetOnFirstCnpDefault(MLXCFG_UNKNOWN), _dceTcpGDefault(MLXCFG_UNKNOWN), _dceTcpRttDefault(MLXCFG_UNKNOWN),
                                    _rateReduceMonitorPeriodDefault(MLXCFG_UNKNOWN), _initialAlphaValueDefault(MLXCFG_UNKNOWN),
                                    _minTimeBetweenCnpsDefault(MLXCFG_UNKNOWN), _cnpDscpDefault(MLXCFG_UNKNOWN), _cnp802pPrioDefault(MLXCFG_UNKNOWN){};
    ~RoCECCEcnParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t clampTgtRate, u_int32_t clampTgtRateAfterTimeInc, u_int32_t rpgTimeReset, u_int32_t rpgByteReset,
            u_int32_t rpgThreshold, u_int32_t rpgMaxRate, u_int32_t rpgAiRate, u_int32_t rpgHaiRate,
            u_int32_t rpgGd, u_int32_t rpgMinDecFac, u_int32_t rpgMinRate, u_int32_t rateToSetOnFirstCnp,
            u_int32_t dceTcpG, u_int32_t dceTcpRtt, u_int32_t rateReduceMonitorPeriod, u_int32_t initialAlphaValue,
            u_int32_t minTimeBetweenCnps, u_int32_t cnpDscp, u_int32_t cnp802pPrio);

    int _port;

    u_int32_t _clampTgtRate;
    u_int32_t _clampTgtRateAfterTimeInc;
    u_int32_t _rpgTimeReset;
    u_int32_t _rpgByteReset;
    u_int32_t _rpgThreshold;
    u_int32_t _rpgMaxRate;
    u_int32_t _rpgAiRate;
    u_int32_t _rpgHaiRate;
    u_int32_t _rpgGd;
    u_int32_t _rpgMinDecFac;
    u_int32_t _rpgMinRate;
    u_int32_t _rateToSetOnFirstCnp;
    u_int32_t _dceTcpG;
    u_int32_t _dceTcpRtt;
    u_int32_t _rateReduceMonitorPeriod;
    u_int32_t _initialAlphaValue;
    u_int32_t _minTimeBetweenCnps;
    u_int32_t _cnpDscp;
    u_int32_t _cnp802pPrio;

    u_int32_t _clampTgtRateDefault;
    u_int32_t _clampTgtRateAfterTimeIncDefault;
    u_int32_t _rpgTimeResetDefault;
    u_int32_t _rpgByteResetDefault;
    u_int32_t _rpgThresholdDefault;
    u_int32_t _rpgMaxRateDefault;
    u_int32_t _rpgAiRateDefault;
    u_int32_t _rpgHaiRateDefault;
    u_int32_t _rpgGdDefault;
    u_int32_t _rpgMinDecFacDefault;
    u_int32_t _rpgMinRateDefault;
    u_int32_t _rateToSetOnFirstCnpDefault;
    u_int32_t _dceTcpGDefault;
    u_int32_t _dceTcpRttDefault;
    u_int32_t _rateReduceMonitorPeriodDefault;
    u_int32_t _initialAlphaValueDefault;
    u_int32_t _minTimeBetweenCnpsDefault;
    u_int32_t _cnpDscpDefault;
    u_int32_t _cnp802pPrioDefault;
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
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

/*
 * ExternalPort5thGen parameters Class (5thGen devices only)
 */

class ExternalPort5thGen : public CfgParams
{
public:
    ExternalPort5thGen() : CfgParams(Mct_External_Port, EXTERNAL_PORT),
        _portOwner(MLXCFG_UNKNOWN), _allowRdCounters(MLXCFG_UNKNOWN),
        _portOwnerDefault(MLXCFG_UNKNOWN), _allowRdCountersDefault(MLXCFG_UNKNOWN){}
    ~ExternalPort5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);
    virtual u_int32_t getDefaultParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
    virtual void updateClassDefaultAttrFromTlv(void* tlv);
    void updateClassAttrFromDefaultParams();
    void setParams(u_int32_t portOwner, u_int32_t allowRdCounters);

    u_int32_t _portOwner;
    u_int32_t _allowRdCounters;

    u_int32_t _portOwnerDefault;
    u_int32_t _allowRdCountersDefault;

};

#endif /* MLXCFG_PARAM_LIB_H_ */
