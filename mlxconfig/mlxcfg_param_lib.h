/* Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id$
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
    // Port Boot State (5th gen)
    Mct_Boot_State_P1,
    Mct_Boot_State_P2,
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
    Mct_Last
} mlxCfgType;

typedef enum {
    // PCI settings
    Mcp_Sriov_En = 0,
    Mcp_Num_Of_Vfs,
    Mcp_Fpp_En,
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
    // Port Boot state Port 1
    Mcp_Boot_State_P1,
    // Port Boot state Port 2
    Mcp_Boot_State_P2,
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
    RawCfgParams5thGen(){}
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

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
    WolParams() : CfgParams(Mct_Last, WOL_TYPE), _wolMagicEn(MLXCFG_UNKNOWN) {}
    virtual ~WolParams() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

    virtual void setParam(mlxCfgParam paramType, u_int32_t val) = 0;
    virtual u_int32_t getParam(mlxCfgParam paramType) = 0;

    virtual int getFromDev(mfile* mf) = 0;
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false) = 0;
    virtual int getDefaultParams(mfile* mf) = 0;

protected:
    virtual bool hardLimitCheck();
    // Wake on magic packet (atm this is the only mode which is supported)

    u_int32_t _wolMagicEn;
};

class WolParams4thGen : public WolParams
{
public:
    WolParams4thGen(int port) : WolParams(), _port(port) {type = _port == 1 ? Mct_Wol_P1 : Mct_Wol_P2;}
    ~WolParams4thGen() {}

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

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

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);
protected:
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);
};


/*
 * VPI param classes:
 */

class VpiParams : public CfgParams
{
public:
    VpiParams(int port) : CfgParams(port == 1 ? Mct_Vpi_P1 : Mct_Vpi_P2, VPI_TYPE), _port(port), _linkType(MLXCFG_UNKNOWN), _defaultLinkType(MLXCFG_UNKNOWN){}
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);
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

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last) = 0;

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
                        _fppEn(MLXCFG_UNKNOWN), _sriovSupported(false), _maxVfsPerPf(0), _fppSupported(false),\
                        _userSpecifiedSRIOV(false), _userSpecifiedFPP(false){}
    ~PciParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getPciSettingsTlvTypeBe();
    u_int32_t getPciCapabilitiesTlvTypeBe();

    u_int32_t _sriovEn;
    u_int32_t _numOfVfs;
    u_int32_t _fppEn;

    // defaults and capabilities
    bool      _sriovSupported;
    u_int32_t _maxVfsPerPf;
    bool      _fppSupported;

    // class members used for indication
    bool _userSpecifiedSRIOV;
    bool _userSpecifiedFPP;

};

/*
 * TPT parameters Class (5thGen devices only)
 */

class TptParams5thGen : public CfgParams
{
public:
    TptParams5thGen() : CfgParams(Mct_Tpt, TPT_SETTINGS_TYPE) , _logMaxPayloadSize(MLXCFG_UNKNOWN), _logMaxPayloadSizeSupported(false) {}
    ~TptParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getTptSettingsTlvTypeBe();
    u_int32_t getTptCapabilitiesTlvTypeBe();

    u_int32_t _logMaxPayloadSize;

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
            INFINIBAND_BOOT_SETTINGS_TYPE) , _port(port), _bootPkey(MLXCFG_UNKNOWN) {}
    ~InfinibandBootSettingsParams4thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();

    int _port;
    u_int32_t _bootPkey;

};

/*
 * Infiniband DC (Dynamically Connected) parameters Class (5thGen devices only)
 */

class IBDCParams5thGen : public CfgParams
{
public:
    IBDCParams5thGen() : CfgParams(Mct_Dc, INFINIBAND_DC_SETTINGS_TYPE) , _logDcrHashTableSize(MLXCFG_UNKNOWN), _dcrLifoSize(MLXCFG_UNKNOWN),
                        _minLogDcrHashTableSize(0), _maxLogDcrHashTableSize(0), _minDcrLifoSize(0), _maxDcrLifoSize(0){}
    ~IBDCParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    int getDefaultsAndCapabilities(mfile* mf);
    u_int32_t getTlvTypeBe();
    u_int32_t getDcCapabilitiesTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

    u_int32_t _logDcrHashTableSize;
    u_int32_t _dcrLifoSize;

    // defaults and capabilities
    u_int32_t _minLogDcrHashTableSize;
    u_int32_t _maxLogDcrHashTableSize;
    u_int32_t _minDcrLifoSize;
    u_int32_t _maxDcrLifoSize;
};

/*
 * Port boot state Class (5thGen devices only)
 */

class PortBootStateParams5thGen : public CfgParams
{
public:
    PortBootStateParams5thGen(int port) : CfgParams((port == 1 ? Mct_Boot_State_P1 : Mct_Boot_State_P2), PORT_BOOT_STATE_TYPE) , _portBootState(MLXCFG_UNKNOWN), _port(port) {}
    ~PortBootStateParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

    u_int32_t _portBootState;
    int _port;
};

/*
 * RoCE v1.5 next protocol Class (5thGen devices only)
 */

class RoCENextProtocolParams5thGen : public CfgParams
{
public:
    RoCENextProtocolParams5thGen() : CfgParams(Mct_RoCE_Next_Protocol, ROCE_NEXT_PROTOCOL_TYPE) , _nextProtocol(MLXCFG_UNKNOWN) {}
    ~RoCENextProtocolParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

    u_int32_t _nextProtocol;
};

/*
 * RoCE CC parameters Class (5thGen devices only)
 */

class RoCECCParams5thGen : public CfgParams
{
public:
    RoCECCParams5thGen(int port) : CfgParams((port == 1 ? Mct_RoCE_CC_P1 : Mct_RoCE_CC_P2), ROCE_CC_TYPE),
                                   _port(port), _roceCcAlgorithm(MLXCFG_UNKNOWN), _roceCcPrioMask(MLXCFG_UNKNOWN) {}
    ~RoCECCParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

    int _port;
    u_int32_t _roceCcAlgorithm;
    u_int32_t _roceCcPrioMask;
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
                                    _minTimeBetweenCnps(MLXCFG_UNKNOWN), _cnpDscp(MLXCFG_UNKNOWN), _cnp802pPrio(MLXCFG_UNKNOWN){};
    ~RoCECCEcnParams5thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();
    u_int32_t getTlvTypeBe();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

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
};


/*
 * Preboot Boot Settings Class (4thGen devices only)
 */

class PrebootBootSettingsParams4thGen : public CfgParams
{
public:
    PrebootBootSettingsParams4thGen(int port) : CfgParams((port == 1 ? Mct_Preboot_Boot_Settings_P1 : Mct_Preboot_Boot_Settings_P2), PREBOOT_BOOT_SETTINGS_TYPE),
                                                _bootOptionRomEn(MLXCFG_UNKNOWN), _bootVlanEn(MLXCFG_UNKNOWN), _bootRetryCnt(MLXCFG_UNKNOWN),
                                                _legacyBootProtocol(MLXCFG_UNKNOWN), _bootVlan(MLXCFG_UNKNOWN), _port(port) {}
    ~PrebootBootSettingsParams4thGen() {};

    virtual bool cfgSupported(mfile* mf, mlxCfgParam param=Mcp_Last);

    virtual void setParam(mlxCfgParam paramType, u_int32_t val);
    virtual u_int32_t getParam(mlxCfgParam paramType);

    virtual int getFromDev(mfile* mf);
    virtual int setOnDev(mfile* mf, bool ignoreCheck=false);
    virtual int getDefaultParams(mfile* mf);

protected:
    virtual bool hardLimitCheck();

    virtual void updateTlvFromClassAttr(void* tlv);
    virtual void updateClassAttrFromTlv(void* tlv);

    u_int32_t _bootOptionRomEn;
    u_int32_t _bootVlanEn;
    u_int32_t _bootRetryCnt;
    u_int32_t _legacyBootProtocol;
    u_int32_t _bootVlan;
    int _port;
};


#endif /* MLXCFG_PARAM_LIB_H_ */
