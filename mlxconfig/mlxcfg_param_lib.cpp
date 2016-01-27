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

#include <signal.h>
#include <math.h>
#include <sstream>
#include <string>

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

/*
 * Macros for getting and settings a TLV
 */
// TODO: adrianc: add macro for nvqc tlv and use it in cfgSupported for 5th gen Tlvs

/*
 * Macros Below rely on the fact that the user has implemented within the parameter class:
 * void updateClassAttrFromTlv(void*);
 * void updateTLVFromClassAttr(void*);
 *
 * those method do what they imply: update the class internal memeber from TLV and via versa.
 */

#define SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tlvStructName, tlvNameStr) \
        MError __mRc;\
        if (!(ignoreCheck) && !checkCfg()) {\
            return MCE_BAD_PARAMS;\
        }\
        int __tlvBuffSize = tlvStructName##_size();\
        u_int8_t __tlvBuff[__tlvBuffSize];\
        memset(__tlvBuff, 0, __tlvBuffSize);\
        struct tlvStructName __tlvStruct;\
        memset(&__tlvStruct, 0, sizeof(__tlvStruct));\
        __mRc = mnvaCom5thGen(mf, __tlvBuff, __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET);\
        if (__mRc && __mRc != ME_REG_ACCESS_RES_NOT_AVLBL) {\
            return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        tlvStructName##_unpack(&__tlvStruct, __tlvBuff);\
        updateTlvFromClassAttr((void*)&__tlvStruct);\
        tlvStructName##_pack(&__tlvStruct, __tlvBuff);\
        __mRc = mnvaCom5thGen(mf, __tlvBuff, __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_SET);\
        if (__mRc) {\
            return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        _updated = false;\
        return MCE_SUCCESS

#define GET_DEFAULT_5TH_GEN(mf, tlvStructName, tlvNameStr) \
        MError __mRc;\
        int __tlvBuffSize = tlvStructName##_size();\
        u_int8_t __tlvBuff[__tlvBuffSize];\
        memset(__tlvBuff, 0, __tlvBuffSize);\
        struct tlvStructName __tlvStruct;\
        memset(&__tlvStruct, 0, sizeof(__tlvStruct));\
        __mRc = mnvaCom5thGen(mf, &__tlvBuff[0], __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET, true);\
        if (__mRc) {\
            if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {\
                return MCE_SUCCESS;\
            }\
            return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]);\
        updateClassDefaultAttrFromTlv((void*)&__tlvStruct);\
        updateClassAttrFromDefaultParams();\
       return MCE_SUCCESS

#define GET_FROM_DEV_5TH_GEN(mf, tlvStructName, tlvNameStr) \
        MError __mRc;\
        int __tlvBuffSize = tlvStructName##_size();\
        u_int8_t __tlvBuff[__tlvBuffSize];\
        memset(__tlvBuff, 0, __tlvBuffSize);\
        struct tlvStructName __tlvStruct;\
        memset(&__tlvStruct, 0, sizeof(__tlvStruct));\
        if (_updated) {\
            return MCE_SUCCESS;\
        }\
        __mRc = mnvaCom5thGen(mf, &__tlvBuff[0], __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET);\
        if (__mRc) {\
            if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {\
                return MCE_SUCCESS;\
            }\
            return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]);\
        updateClassAttrFromTlv((void*)&__tlvStruct);\
        _updated = true;\
       return MCE_SUCCESS

#define SET_ON_DEV_4TH_GEN(mf, ignoreCheck, tlvStructName, tlvNameStr, typeMod) \
        MError __mRc;\
        if (!(ignoreCheck) && !checkCfg()) {\
            return MCE_BAD_PARAMS;\
        }\
        int __tlvBuffSize = tlvStructName##_size();\
        u_int8_t __tlvBuff[__tlvBuffSize];\
        memset(__tlvBuff, 0, __tlvBuffSize);\
        struct tlvStructName __tlvStruct;\
        memset(&__tlvStruct, 0, sizeof(__tlvStruct));\
        __mRc = mnvaCom4thGen(mf, __tlvBuff, __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_GET, typeMod);\
        if (__mRc && __mRc != ME_REG_ACCESS_RES_NOT_AVLBL) {\
            return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        tlvStructName##_unpack(&__tlvStruct, __tlvBuff);\
        updateTlvFromClassAttr((void*)&__tlvStruct);\
        tlvStructName##_pack(&__tlvStruct, __tlvBuff);\
        __mRc = mnvaCom4thGen(mf, __tlvBuff, __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_SET, typeMod);\
        if (__mRc) {\
            return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        _updated = false;\
        return MCE_SUCCESS

#define GET_FROM_DEV_4TH_GEN(mf, tlvStructName, tlvNameStr, typeMod) \
        MError __mRc;\
        int __tlvBuffSize = tlvStructName##_size();\
        u_int8_t __tlvBuff[__tlvBuffSize];\
        memset(__tlvBuff, 0, __tlvBuffSize);\
        struct tlvStructName __tlvStruct;\
        memset(&__tlvStruct, 0, sizeof(__tlvStruct));\
        if (_updated) {\
            return MCE_SUCCESS;\
        }\
        __mRc = mnvaCom4thGen(mf, &__tlvBuff[0], __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_GET, typeMod);\
        if (__mRc) {\
            if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {\
                return MCE_SUCCESS;\
            }\
            return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc));\
        }\
        tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]);\
        updateClassAttrFromTlv((void*)&__tlvStruct);\
        _updated = true;\
       return MCE_SUCCESS


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

MError mnvaCom5thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t tlvType, reg_access_method_t method, bool getDefault=false)
{
    struct tools_open_nvda mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_nvda));

    mnvaTlv.nv_hdr.length = len;
    mnvaTlv.nv_hdr.rd_en = 0;
    mnvaTlv.nv_hdr.over_en = 1;
    if (getDefault) {
        mnvaTlv.nv_hdr.default_ = 1;
    }
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
 * RawCfgParams5thGen Class implementation
 */
RawCfgParams5thGen::RawCfgParams5thGen() {
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
}

int RawCfgParams5thGen::setRawData(const std::vector<u_int32_t>& tlvBuff) {
    if(tlvBuff.size() * 4 > TOOLS_OPEN_NVDA_SIZE){
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size exceeds maximal limit. Maximum size is 0x%x bytes, actual length is 0x%x bytes", TOOLS_OPEN_NVDA_SIZE, (u_int32_t)(tlvBuff.size() * 4));
    }
    _tlvBuff = tlvBuff;
    memset(&_nvdaTlv, 0, sizeof(struct tools_open_nvda));
    std::vector<u_int32_t> tlvBuffBe = _tlvBuff;
    tlvBuffBe.resize(TOOLS_OPEN_NVDA_SIZE >> 2);
    memset(&tlvBuffBe[0], 0, TOOLS_OPEN_NVDA_SIZE);
    tlvBuffBe.insert(tlvBuffBe.begin(), _tlvBuff.begin(), _tlvBuff.end());
    for (std::vector<u_int32_t>::iterator it = tlvBuffBe.begin(); it != tlvBuffBe.end(); it++ ) {
        *it = __cpu_to_be32(*it);
    }
    tools_open_nvda_unpack(&_nvdaTlv, ((u_int8_t*)(&tlvBuffBe[0])));
    return verifyTlv();
}

int RawCfgParams5thGen::setOnDev(mfile* mf) {
    int rc;
    mft_signal_set_handling(1);
    DEBUG_PRINT_SEND(&_nvdaTlv, nvda);
    rc = reg_access_nvda(mf, REG_ACCESS_METHOD_SET, &_nvdaTlv);
    DEBUG_PRINT_RECIEVE(&_nvdaTlv, nvda);
    dealWithSignal();
    if (rc) {
        return errmsg("Failed to set raw TLV: %s", m_err2str((MError)rc));
    }
    return MCE_SUCCESS;
}

std::string RawCfgParams5thGen::dumpTlv() {
    char str[1024] = {0};
    snprintf(str, 1024, "Length: 0x%x\nVersion: %d\nOverrideEn: %d\nType: 0x%08x\nData: ", _nvdaTlv.nv_hdr.length,\
            _nvdaTlv.nv_hdr.version, _nvdaTlv.nv_hdr.over_en, _nvdaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw);
    for (size_t i=3; i < _tlvBuff.size(); i++) {
        char numStr[64] = {0};
        snprintf(numStr, 64, "0x%08x ", _tlvBuff[i]);
        strcat(str, numStr);
    }
    strcat(str, "\n");
    return str;
}

int RawCfgParams5thGen::verifyTlv() {
    // check TLV length
    int tlvLength = (_tlvBuff.size() - 3) << 2;
    if (tlvLength != _nvdaTlv.nv_hdr.length) {
        return errmsg(MCE_BAD_PARAM_VAL, "TLV size mismatch. reported length in TLV header: 0x%x. actual length: 0x%x", _nvdaTlv.nv_hdr.length, tlvLength);
    }
    return MCE_SUCCESS;
}

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
    mft_signal_set_handling(1);
    MError rc  = tcif_query_global_def_params(mf, global_params);
    dealWithSignal();
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int CfgParams::getDefaultParams4thGen(mfile* mf, int port, struct tools_open_query_def_params_per_port* port_params)
{
    mft_signal_set_handling(1);
    MError rc  = tcif_query_per_port_def_params(mf, port, port_params);
    dealWithSignal();
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
 * BootSettingsExtParams Class implementation:
 */
bool BootSettingsExtParams::hardLimitCheck()
{
    if(_ipVer > 3) {
        errmsg("illegal IP Ver parameter value. can be 0..3");
        return false;
    }
    return true;
}

void BootSettingsExtParams::setParams(u_int32_t ipVer)
{
    _ipVer = ipVer;
}

/*
 * BootSettingsExtParams4thGen Class implementation:
 */

u_int32_t BootSettingsExtParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver_P1 ||
            paramType == Mcp_Boot_Settings_Ext_IP_Ver_P2) {
        return _ipVerDefault;
    }
    return MLXCFG_UNKNOWN;
}

void BootSettingsExtParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver_P1 ||
            paramType == Mcp_Boot_Settings_Ext_IP_Ver_P2) {
        _ipVer = val;
    }
}

u_int32_t BootSettingsExtParams4thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver_P1 ||
            paramType == Mcp_Boot_Settings_Ext_IP_Ver_P2) {
        return _ipVer;
    }
    return MLXCFG_UNKNOWN;
}

bool BootSettingsExtParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)param;
    struct tools_open_query_def_params_global params;
    int rc;
    rc = getDefaultParams4thGen(mf, &params);
    if (rc) {
        return false;
    }
    return params.boot_ip_ver;
}

int BootSettingsExtParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port params;
    int rc;
    rc = getDefaultParams4thGen(mf, _port, &params);
    if (rc) {
        return false;
    }
    _ipVerDefault = params.boot_ip_ver;
    setParams(_ipVerDefault);
    return MCE_SUCCESS;
}

int BootSettingsExtParams4thGen::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[tools_open_sriov_size()];
    struct tools_open_boot_settings_ext bootSettingsExtTlv;
    memset(buff, 0, tools_open_boot_settings_ext_size());
    memset(&bootSettingsExtTlv, 0, sizeof(struct tools_open_boot_settings_ext));
    // pack it
    tools_open_boot_settings_ext_pack(&bootSettingsExtTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&bootSettingsExtTlv, boot_settings_ext);
    rc = mnvaCom4thGen(mf, buff, tools_open_boot_settings_ext_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);
    // check rc
    DEBUG_PRINT_RECIEVE(&bootSettingsExtTlv, boot_settings_ext);
    if (rc) {// when attempting to get a nv_cfg tlv from device ME_REG_ACCESS_RES_NOT_AVLBL means - no valid
             // tlv found. i.e default configuration are on.
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg(MCE_BAD_STATUS, "Failed to get Boot Settings Extras configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_boot_settings_ext_unpack(&bootSettingsExtTlv, buff);
    setParams(bootSettingsExtTlv.ip_ver);
    _updated = true;

    return MCE_SUCCESS;
}

int BootSettingsExtParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    if (_ipVer == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for Boot Settings Extras.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[tools_open_boot_settings_ext_size()];
    struct tools_open_boot_settings_ext bootSettingsExtTlv;

    memset(buff, 0, tools_open_boot_settings_ext_size());
    memset(&bootSettingsExtTlv, 0, sizeof(struct tools_open_boot_settings_ext));
    bootSettingsExtTlv.ip_ver = _ipVer;
    // pack it
    tools_open_boot_settings_ext_pack(&bootSettingsExtTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_boot_settings_ext_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (ret) {
        return errmsg("failed to set Boot Settings Extras params: %s",m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

/*
 * BootSettingsExtParams5thGen Class implementation:
 */

u_int32_t BootSettingsExtParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver) {
        return _ipVerDefault;
    }
    return MLXCFG_UNKNOWN;
}

void BootSettingsExtParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver) {
        _ipVer = val;
    }
}

u_int32_t BootSettingsExtParams5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Boot_Settings_Ext_IP_Ver) {
        return _ipVer;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t BootSettingsExtParams5thGen::getBootSettingsExtCapabilitiesTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = BOOT_SETTINGS_EXTRAS_GEN5_CAP;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

bool BootSettingsExtParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    u_int8_t tlvCapBuff[TOOLS_OPEN_OPTION_ROM_CAPABILITY_SIZE] = {0};
    struct tools_open_option_rom_capability optionRomCapabilitesTlv;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getBootSettingsExtCapabilitiesTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        return false;
    }
    memset(&optionRomCapabilitesTlv, 0, sizeof(optionRomCapabilitesTlv));
    rc = mnvaCom5thGen(mf, &tlvCapBuff[0], TOOLS_OPEN_OPTION_ROM_CAPABILITY_SIZE, getBootSettingsExtCapabilitiesTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (rc) {
        return errmsg("Failed to get Boot Settings Ext capabilities parameter. %s", m_err2str(rc));
    }
    tools_open_option_rom_capability_unpack(&optionRomCapabilitesTlv, tlvCapBuff);
    return optionRomCapabilitesTlv.ip_ver;
}

int BootSettingsExtParams5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_boot_settings_ext, "Boot Settings Ext");
}

void BootSettingsExtParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(_ipVerDefault);
}

int BootSettingsExtParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_boot_settings_ext, "Boot Settings Ext");
}

u_int32_t BootSettingsExtParams5thGen::getTlvTypeBe()
{
    struct tools_open_per_host_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_PER_HOST;
    type.param_idx = tlvTypeIdx;
    type.function = 0; // currently support only host 0 (FW should fill this field with correct func)
    type.host = 0; // currently support only host 0 (FW should fill this field with correct host)
    tools_open_per_host_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

void BootSettingsExtParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_boot_settings_ext* bootSettingsExt = (struct tools_open_boot_settings_ext*)tlv;
    bootSettingsExt->ip_ver = _ipVer;
    return;
}
void BootSettingsExtParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_boot_settings_ext* bootSettingsExt = (struct tools_open_boot_settings_ext*)tlv;
    setParams(bootSettingsExt->ip_ver);
    return;
}

void BootSettingsExtParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_boot_settings_ext* bootSettingsExt = (struct tools_open_boot_settings_ext*)tlv;
    _ipVerDefault = bootSettingsExt->ip_ver;
    return;
}

int BootSettingsExtParams5thGen::getDefaultParamsAux(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_boot_settings_ext, "Boot Settings Extras");
}

int BootSettingsExtParams5thGen::getDefaultParams(mfile* mf)
{
    int rc = getDefaultParamsAux(mf);
    if(!rc || _ipVerDefault == MLXCFG_UNKNOWN){
        _ipVerDefault = 0;
        setParams(_ipVerDefault);
    }
    return MCE_SUCCESS;
}

/*
 * SriovParams4thGen Class implementation:
 */

void SriovParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Sriov_En) {
        _sriovEn = val;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        _numOfVfs = val;
    }
}

u_int32_t SriovParams4thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEn;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfs;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t SriovParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEnDefault;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfsDefault;
    }
    return MLXCFG_UNKNOWN;
}

bool SriovParams4thGen::hardLimitCheck()
{
    if ((_numOfVfs > _maxVfs)) {
        errmsg("Number of VFs exceeds limit (%d).", _maxVfs);
        return false;
    }

    if (_sriovEn != 0 && _sriovEn != 1) {
        errmsg("illegal SRIOV_EN parameter value. (should be 0 or 1)");
        return false;
    }
    return true;
}

/*
 * SriovParam4thGen Class implementation
 */

bool SriovParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return _devCapVec & SRIOV_MASK;
}

int SriovParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_global global_params;
    int rc;
    rc = updateMaxVfs(mf); CHECK_RC(rc);
    rc = getDefaultParams4thGen(mf, &global_params);
    if (rc == MCE_SUCCESS) {
        _sriovEnDefault = global_params.sriov_en;
        _numOfVfsDefault = global_params.num_vfs;
        setParams(_sriovEnDefault, _numOfVfsDefault);
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

void SriovParams4thGen::setParams(u_int32_t sriovEn, u_int32_t numOfVfs)
{
    _sriovEn = sriovEn;
    _numOfVfs = numOfVfs;
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
    setParams(sriovTlv.sriov_en, sriovTlv.total_vfs);
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
 * WolParams Class implementation :
 */

bool WolParams::hardLimitCheck()
{
    if (_wolMagicEn == 0 || _wolMagicEn == 1 ) {
        return true;
    }
    errmsg("illegal WOL parameter value. can be either 0 or 1.");
    return false;
}

void WolParams::setParams(u_int32_t wolMagicEn)
{
    _wolMagicEn = wolMagicEn;
}

/*
 * WolParams4thGen Class implementation :
 */

void WolParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Wol_Magic_En_P1  && _port == 1) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2) ) {
        _wolMagicEn = val;
    }
}

u_int32_t WolParams4thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Wol_Magic_En_P1  && _port == 1) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2)) {
        return _wolMagicEn;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t WolParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Wol_Magic_En_P1  && _port == 1) || (paramType == Mcp_Wol_Magic_En_P2 && _port == 2)) {
        return _wolMagicEnDefault;
    }
    return MLXCFG_UNKNOWN;
}

bool WolParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return ((_devCapVec & WOL_P1_MASK) && _port == 1) || ((_devCapVec & WOL_P2_MASK) && _port == 2 );
}

int WolParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port port_params;
    int rc = getDefaultParams4thGen(mf, _port , &port_params);
    if (rc == MCE_SUCCESS) {
        _wolMagicEnDefault = port_params.default_en_wol_magic;
        setParams(_wolMagicEnDefault);
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
    setParams(wolTlv.en_wol_magic);
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

void WolParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Wol_Magic_En ) {
        _wolMagicEn = val;
    }
}

u_int32_t WolParams5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Wol_Magic_En) {
        return _wolMagicEn;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t WolParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Wol_Magic_En) {
        return _wolMagicEnDefault;
    }
    return MLXCFG_UNKNOWN;
}

bool WolParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get Wake On LAN parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    return (suppRead && suppWrite);
}

int WolParams5thGen::getDefaultParams(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_wol, "Wake On LAN");
}

void WolParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(_wolMagicEnDefault);
}

int WolParams5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_wol, "Wake On LAN");
}

int WolParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_wol, "Wake On LAN");
}

u_int32_t WolParams5thGen::getTlvTypeBe()
{
    struct tools_open_per_host_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_PER_HOST;
    type.param_idx = tlvTypeIdx;
    type.function = 0; // currently support only host 0 (FW should fill this field with correct func)
    type.host = 0; // currently support only host 0 (FW should fill this field with correct host)
    tools_open_per_host_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

void WolParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_wol* wolTlv = (struct tools_open_wol*)tlv;
    wolTlv->en_wol_magic = _wolMagicEn;
    return;
}
void WolParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_wol* wolTlv = (struct tools_open_wol*)tlv;
    setParams(wolTlv->en_wol_magic);
    return;
}

void WolParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_wol* wolTlv = (struct tools_open_wol*)tlv;
    _wolMagicEnDefault = wolTlv->en_wol_magic;
    return;
}
/*
 * BarSzParams Class implementation :
 */


void BarSzParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Log_Bar_Size) {
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

u_int32_t BarSzParams::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Bar_Size) {
        return _logBarSzDefault;
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

void BarSzParams::setParams(u_int32_t logBarSz)
{
    _logBarSz = logBarSz;
}
/*
 * BarSzParams4thGen Class implementation :
 */

bool BarSzParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return _devCapVec & BAR_SZ_MASK ;
}

int BarSzParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_global global_params;
    int rc = getDefaultParams4thGen(mf, &global_params);
    if ((rc == MCE_SUCCESS) & 0) { //TODO: adrianc: remove the & 0 when FW displays thesee parameters correctly in QUERY_DEF_PARAMS command
        _logBarSzDefault = global_params.uar_bar_size;
        _maxLogBarSz = global_params.max_uar_bar_size;
        setParams(_logBarSzDefault);
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

    _logBarSzDefault = EXTRACT64(data, 16, 6) + 1; //adrianc: this field reports only half of the bar size (i.e without the blue flame)
    setParams(_logBarSzDefault);
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
    setParams(barSzTlv.log_uar_bar_size);
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
     setParams(_vpiTlv.network_link_type, _vpiTlv.default_link_type);
     _updated = true;
     return MCE_SUCCESS;

}

void VpiParams::setParams(u_int32_t linkType, u_int32_t defaultLinkType)
{
    _linkType = linkType;
    _defaultLinkType = defaultLinkType;
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

u_int32_t VpiParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _linkTypeDefault;
    }
    return MLXCFG_UNKNOWN;
}

bool VpiParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return ((_devCapVec & VPI_P1_MASK) && _port == 1) || ((_devCapVec & VPI_P2_MASK) && _port == 2);
}

int VpiParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port port_params;
    _defaultLinkTypeDefault = 0; // not used for 4th gen devices , we give it a default value
    int rc = getDefaultParams4thGen(mf, _port , &port_params);
    if (rc) {
        return MCE_GET_DEFAULT_PARAMS;
    }
    if (port_params.default_network_link_type) {
        _linkTypeDefault = port_params.default_network_link_type;
    }
    setParams(_linkTypeDefault, _defaultLinkTypeDefault);
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

u_int32_t VpiParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _defaultLinkTypeDefault;
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

bool VpiParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    // get mtcr functions for this device (physical)
    // compare with port
    // send nvqc and check
    (void)param;
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
    MError mRc;
    int rc;

    // if configuration is supported then network link type must be 3
    _linkTypeDefault = 3;

    if((rc = getFromDevComPre())) {
        return rc;
    }

    mRc = mnvaCom5thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, getTlvTypeBe(), REG_ACCESS_METHOD_GET, true);

    if (mRc) {
        if (mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get VPI port%d configuration: %s", _port, m_err2str(mRc));
    }

    // unpack and update
    tools_open_vpi_settings_unpack(&_vpiTlv, &_tlvBuff[0]);
    _linkTypeDefault = _vpiTlv.network_link_type;
    _defaultLinkTypeDefault = _vpiTlv.default_link_type;
    setParams(_linkTypeDefault, _defaultLinkTypeDefault);
    return MCE_SUCCESS;

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
    rc = getFromDevComPost(mRc);

    _updated = true;

    return rc;
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

bool PciParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
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

    rc = nvqcCom5thGen(mf, getPciSettingsTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get PCI settings parameter capabilities. %s", m_err2str(rc));
        return false;
    }

    if (!(suppRead && suppWrite)) {
        return false;
    }

    switch(param) {
    case Mcp_Sriov_En:
    case Mcp_Num_Of_Vfs:
        return _sriovSupported;
    case Mcp_Fpp_En:
        return _fppSupported;
    case Mcp_Last:
        return true;
    case Mcp_PF_Log_Bar_Size:
        return _pfLogBarSizeSuppored;
    case Mcp_VF_Log_Bar_Size:
        return _vfLogBarSizeSuppored;
    case Mcp_Num_Pf_Msix:
        return _numPfMsixSupported;
    case Mcp_Num_Vf_Msix:
        return _numVfMsixSupported;
    default:
        return false;
    }
}

void PciParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Sriov_En) {
        _sriovEn = val;
        _userSpecifiedSRIOV = true;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        _numOfVfs = val;
        _userSpecifiedSRIOV = true;
    } else if (paramType == Mcp_Fpp_En) {
        _fppEn = val;
        _userSpecifiedFPP = true;
    } else if(paramType == Mcp_PF_Log_Bar_Size) {
        _pfLogBarSize = val;
        _userSpecifiedPfLogBarSize = true;
    } else if(paramType == Mcp_VF_Log_Bar_Size) {
        _vfLogBarSize = val;
        _userSpecifiedVfLogBarSize = true;
    } else if(paramType == Mcp_Num_Pf_Msix) {
        _numPfMsix = val;
        _userSpecifiedNumPfMsix = true;
    } else if(paramType == Mcp_Num_Vf_Msix) {
        _numVfMsix = val;
        _userSpecifiedNumVfMsix = true;
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
    } else if(paramType == Mcp_PF_Log_Bar_Size) {
        return _pfLogBarSize;
    } else if(paramType == Mcp_VF_Log_Bar_Size) {
        return _vfLogBarSize;
    } else if(paramType == Mcp_Num_Pf_Msix) {
        return _numPfMsix;
    } else if(paramType == Mcp_Num_Vf_Msix) {
        return _numVfMsix;
    }

    return MLXCFG_UNKNOWN;
}

u_int32_t PciParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Sriov_En) {
        return _sriovEnDefault;
    } else if (paramType == Mcp_Num_Of_Vfs) {
        return _numOfVfsDefault;
    } else if (paramType == Mcp_Fpp_En) {
        return _fppEnDefault;
    } else if(paramType == Mcp_PF_Log_Bar_Size) {
        return _pfLogBarSizeDefault;
    } else if(paramType == Mcp_VF_Log_Bar_Size) {
        return _vfLogBarSizeDefault;
    } else if(paramType == Mcp_Num_Pf_Msix) {
        return _numPfMsixDefault;
    } else if(paramType == Mcp_Num_Vf_Msix) {
        return _numVfMsixDefault;
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
    }
    if (pciSettingsTlv.fpp_valid) {
        _fppEn = pciSettingsTlv.fpp_en;
    }
    if(pciSettingsTlv.pf_bar_size_valid) {
        _pfLogBarSize = pciSettingsTlv.log_pf_uar_bar_size;
    }
    if(pciSettingsTlv.vf_bar_size_valid) {
        _vfLogBarSize = pciSettingsTlv.log_vf_uar_bar_size;
    }
    if(pciSettingsTlv.num_pfs_valid){
        _numOfPfs = pciSettingsTlv.num_pfs;
        _numOfPfsValid = true;
    }
    if(pciSettingsTlv.num_pfs_msix_valid){
        _numPfMsix = pciSettingsTlv.num_pf_msix;
    }
    if(pciSettingsTlv.num_vfs_msix_valid){
        _numVfMsix = pciSettingsTlv.num_vf_msix;
    }
    _updated = true;

   return MCE_SUCCESS;
}

int PciParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;

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

    if (_sriovSupported && _userSpecifiedSRIOV) {
        if (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) {
            return errmsg("please specify all parameters for SRIOV.");
        }
        pciSettingsTlv.sriov_valid = 1;
        pciSettingsTlv.sriov_en = _sriovEn;
        pciSettingsTlv.total_vfs = _numOfVfs;
    }

    if (_fppSupported && _userSpecifiedFPP) {
        pciSettingsTlv.fpp_en = _fppEn;
        pciSettingsTlv.fpp_valid = 1;
    }

    if (_pfLogBarSizeSuppored && _userSpecifiedPfLogBarSize) {
        pciSettingsTlv.log_pf_uar_bar_size = _pfLogBarSize;
        pciSettingsTlv.pf_bar_size_valid = 1;
    }

    if (_vfLogBarSizeSuppored && _userSpecifiedVfLogBarSize) {
        pciSettingsTlv.log_vf_uar_bar_size = _vfLogBarSize;
        pciSettingsTlv.vf_bar_size_valid = 1;
    }

    if (pciSettingsTlv.sriov_en && !pciSettingsTlv.fpp_en) {
        return errmsg("FPP should be enabled while SRIOV is enabled");
    }

    if(_numPfMsixSupported && _userSpecifiedNumPfMsix) {
        pciSettingsTlv.num_pf_msix = _numPfMsix;
        pciSettingsTlv.num_pfs_msix_valid = 1;
    }

    if(_numVfMsixSupported && _userSpecifiedNumVfMsix) {
        pciSettingsTlv.num_vf_msix = _numVfMsix;
        pciSettingsTlv.num_vfs_msix_valid = 1;
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
    int rc = getDefaultsAndCapabilities(mf);

    setParams(
     _sriovEnDefault,
     _numOfVfsDefault,
     _fppEnDefault,
     _pfLogBarSizeDefault,
     _vfLogBarSizeDefault,
     _numOfPfs,
     _numPfMsixDefault,
     _numVfMsixDefault);

    return rc;
}

void PciParams5thGen::setParams(u_int32_t sriovEn, u_int32_t numOfVfs, u_int32_t fppEn, u_int32_t pfLogBarSize,
            u_int32_t vfLogBarSize, u_int32_t numOfPfs, u_int32_t numPfMsix, u_int32_t numVfMsix)
{
    _sriovEn = sriovEn;
    _numOfVfs = numOfVfs;
    _fppEn = fppEn;
    _pfLogBarSize = pfLogBarSize;
    _vfLogBarSize = vfLogBarSize;
    _numOfPfs = numOfPfs;
    _numPfMsix = numPfMsix;
    _numVfMsix = numVfMsix;
}

int PciParams5thGen::getDefaultsAndCapabilities(mfile* mf)
{
    MError rc;
    u_int8_t tlvCapBuff[TOOLS_OPEN_PCI_CAPABILITIES_SIZE] = {0};
    struct tools_open_pci_capabilities pciCapabilitesTlv;
    memset(&pciCapabilitesTlv, 0, sizeof(pciCapabilitesTlv));
    rc = mnvaCom5thGen(mf, &tlvCapBuff[0], TOOLS_OPEN_PCI_CAPABILITIES_SIZE, getPciCapabilitiesTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (rc) {
        return errmsg("Failed to get PCI capabilities parameter. %s", m_err2str(rc));
    }
    tools_open_pci_capabilities_unpack(&pciCapabilitesTlv, tlvCapBuff);
    _sriovSupported = pciCapabilitesTlv.sriov_support;
    _maxVfsPerPf = pciCapabilitesTlv.max_vfs_per_pf_valid ? pciCapabilitesTlv.max_vfs_per_pf : 0;
    _fppSupported = pciCapabilitesTlv.fpp_support;
    _pfLogBarSizeSuppored = pciCapabilitesTlv.pf_bar_size_supported;
    _vfLogBarSizeSuppored = pciCapabilitesTlv.vf_bar_size_supported;
    _numPfMsixSupported = pciCapabilitesTlv.num_pf_msix_supported;
    _numVfMsixSupported = pciCapabilitesTlv.num_vf_msix_supported;
    _maxLogPfBarSize = pciCapabilitesTlv.log_max_pf_uar_bar_size1;
    _maxLogVfBarSize = pciCapabilitesTlv.log_max_vf_uar_bar_size;
    _maxTotalBarValid = pciCapabilitesTlv.max_total_bar_valid;
    _maxTotalBar = pciCapabilitesTlv.max_total_bar;
    _maxNumPfMsix = pciCapabilitesTlv.max_num_pf_msix;
    _maxNumVfMsix = pciCapabilitesTlv.max_num_vf_msix;
    _maxTotalMsixValid = pciCapabilitesTlv.max_total_msix_valid;
    _maxTotalMsix = pciCapabilitesTlv.max_total_msix;

    u_int8_t tlvBuff[TOOLS_OPEN_PCI_CONFIGURATION_SIZE] = {0};
    struct tools_open_pci_configuration pciSettingsTlv;
    memset(&pciSettingsTlv, 0, sizeof(pciSettingsTlv));

    rc = mnvaCom5thGen(mf, &tlvBuff[0], TOOLS_OPEN_PCI_CONFIGURATION_SIZE, getPciSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET, true);

    if (rc) {
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get PCI configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_pci_configuration_unpack(&pciSettingsTlv, &tlvBuff[0]);
    if (pciSettingsTlv.sriov_valid) {
        _sriovEnDefault = pciSettingsTlv.sriov_en;
        _numOfVfsDefault = pciSettingsTlv.total_vfs;
    }
    if (pciSettingsTlv.fpp_valid) {
        _fppEnDefault = pciSettingsTlv.fpp_en;
    }
    if(pciSettingsTlv.pf_bar_size_valid) {
        _pfLogBarSizeDefault = pciSettingsTlv.log_pf_uar_bar_size;
    }
    if(pciSettingsTlv.vf_bar_size_valid) {
        _vfLogBarSizeDefault = pciSettingsTlv.log_vf_uar_bar_size;
    }
    if(pciSettingsTlv.num_pfs_msix_valid) {
        _numPfMsixDefault = pciSettingsTlv.num_pf_msix;
    }
    if(pciSettingsTlv.num_vfs_msix_valid) {
        _numVfMsixDefault = pciSettingsTlv.num_vf_msix;
    }

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
    if (_sriovSupported && _userSpecifiedSRIOV) {
        if ((_numOfVfs > _maxVfsPerPf)) {
            errmsg("Number of VFs exceeds limit (%d).", _maxVfsPerPf);
            return false;
        }

        if (_sriovEn != 0 && _sriovEn != 1) {
            errmsg("Illegal SRIOV_EN parameter value. (should be 0 or 1)");
            return false;
        }
    }

    if (_fppSupported && _userSpecifiedFPP) {
        if (_fppEn != 0 && _fppEn != 1) {
            errmsg("Illegal FPP_EN parameter value. (should be 0 or 1)");
            return false;
        }
    }

    if (_pfLogBarSizeSuppored && _userSpecifiedPfLogBarSize) {
        if (_pfLogBarSize > _maxLogPfBarSize) {
            errmsg("Illegal PF_LOG_BAR_SIZE parameter value, Max allowed value is %d", _maxLogPfBarSize);
            return false;
        }
    }

    if (_vfLogBarSizeSuppored && _userSpecifiedVfLogBarSize) {
        if (_vfLogBarSize > _maxLogVfBarSize) {
            errmsg("Illegal VF_LOG_BAR_SIZE parameter value, Max allowed value is %d", _maxLogVfBarSize);
            return false;
        }
    }

    if(_numPfMsixSupported && _userSpecifiedNumPfMsix) {
        if(_numPfMsix > _maxNumPfMsix) {
            errmsg("Illegal NUM_PF_MSIX parameter value, Max allowed value is %d", _maxNumPfMsix);
            return false;
        }
    }

    if(_numVfMsixSupported && _userSpecifiedNumVfMsix) {
        if(_numVfMsix > _maxNumVfMsix) {
            errmsg("Illegal NUM_VF_MSIX parameter value, Max allowed value is %d", _maxNumVfMsix);
            return false;
        }
    }

    return true;
}

//waiting for arch to correct the constraint formula
u_int32_t PciParams5thGen::calcNumOfVfs()
{
    if(_fppEn == 1){
        return (_maxTotalBar / _numOfPfs - (1 << _pfLogBarSize))/ (1 << _vfLogBarSize);
    } else {
        return (_maxTotalBar - (1 << _pfLogBarSize)) / (1 << _vfLogBarSize);
    }
}

u_int32_t PciParams5thGen::calcVfLogBarSize()
{
    if(_fppEn == 1){
        return static_cast<unsigned int>(log2((_maxTotalBar / _numOfPfs - (1 << _pfLogBarSize)) / _numOfVfs));
    } else {
        return static_cast<unsigned int>(log2((_maxTotalBar - (1 << _pfLogBarSize)) / _numOfVfs));
    }
}

u_int32_t PciParams5thGen::calcPfLogBarSize()
{
    if(_fppEn == 1){
        return static_cast<unsigned int>(log2((_maxTotalBar / _numOfPfs - (1 << _vfLogBarSize) * _numOfVfs)));
    } else {
        return static_cast<unsigned int>(log2((_maxTotalBar - (1 << _vfLogBarSize) * _numOfVfs)));
    }
}

u_int32_t PciParams5thGen::calcTotalBar()
{
    if(_fppEn == 1){
        return (_numOfPfs * ((1 << _pfLogBarSize) + (1 << _vfLogBarSize) * _numOfVfs));
    } else {
        return ((1 << _pfLogBarSize) + (1 << _vfLogBarSize) * _numOfVfs);
    }
}

bool PciParams5thGen::softLimitCheck(mfile* mf)
{
    (void)mf;
    if (_maxTotalBarValid == 1 && _maxTotalBar != 0 && _sriovEn == 1) {
        if(_userSpecifiedSRIOV || _userSpecifiedPfLogBarSize || _userSpecifiedVfLogBarSize){
            if(_fppEn == 1){
                if(!_numOfPfsValid){
                    errmsg("Cannot perform advanced calculations, cannot extract number of physical functions from Firmware.");
                    return false;
                }
               if(calcTotalBar() > _maxTotalBar) {
                   if(_userSpecifiedSRIOV) {
                       errmsg("Given the specified parameter: NUM_OF_VFS, the maximum allowed values is %d",calcNumOfVfs());
                   } else if(_userSpecifiedVfLogBarSize) {
                       errmsg("Given the specified parameter: VF_Log_Bar_Size, the maximum allowed values is %d",calcVfLogBarSize());
                   } else if(_userSpecifiedPfLogBarSize) {
                       errmsg("Given the specified parameter: PF_Log_Bar_Size, the maximum allowed values is %d",calcPfLogBarSize());
                   }
                   return false;
               }
            } else {
                if(calcTotalBar() > _maxTotalBar) {
                    if(_userSpecifiedSRIOV){
                       errmsg("Given the specified parameter: NUM_OF_VFS, the maximum allowed values is %d",calcNumOfVfs());
                    } else if(_userSpecifiedVfLogBarSize) {
                      errmsg("Given the specified parameter: VF_Log_Bar_Size, the maximum allowed values is %d",calcVfLogBarSize());
                    } else if(_userSpecifiedPfLogBarSize) {
                      errmsg("Given the specified parameter: PF_Log_Bar_Size, the maximum allowed values is %d",calcPfLogBarSize());
                    }
                    return false;
                }
            }
        }
    }

    if (_maxTotalMsixValid == 1) {
        if (_userSpecifiedSRIOV || _userSpecifiedNumPfMsix || _userSpecifiedNumVfMsix) {
            if (!_numOfPfsValid){
                errmsg("Cannot perform advanced calculations, cannot extract number of physical functions from Firmware.");
                return false;
            }
        }
        if ((_numOfPfs * (_numPfMsix + _numOfVfs * _numVfMsix)) > _maxTotalMsix){
            if(_userSpecifiedSRIOV){
               errmsg("Given the specified parameter: NUM_OF_VFS, the maximum allowed values is %d",
                                       (((_maxTotalMsix / _numOfPfs) - _numPfMsix) / _numVfMsix));
            } else if(_userSpecifiedNumPfMsix){
                errmsg("Given the specified parameter: NUM_PF_MSIX, the maximum allowed values is %d",
                                       ((_maxTotalMsix / _numOfPfs) - (_numOfVfs * _numVfMsix)));
            } else if(_userSpecifiedNumVfMsix){
                errmsg("Given the specified parameter: NUM_VF_MSIX, the maximum allowed values is %d",
                                       (((_maxTotalMsix / _numOfPfs) - _numPfMsix) /_numOfVfs));
            }
        }
    }

    return true;
}


/*
 * TptParams5thGen Class implementation:
 */

bool TptParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTptCapabilitiesTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get TPT capabilities parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead) {
        return false;
    }

    if (getDefaultsAndCapabilities(mf) != MCE_SUCCESS) {
        return false;
    }

    rc = nvqcCom5thGen(mf, getTptSettingsTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get TPT settings parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!(suppRead && suppWrite && _logMaxPayloadSizeSupported)) {
        return false;
    }
    return true;
}

void TptParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Log_Tpt_Size) {
        _logMaxPayloadSize = val;
    }
}

u_int32_t TptParams5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Tpt_Size) {
        return _logMaxPayloadSize;
    }

    return MLXCFG_UNKNOWN;
}

u_int32_t TptParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Tpt_Size) {
        return _logMaxPayloadSizeDefault;
    }

    return MLXCFG_UNKNOWN;
}

int TptParams5thGen::getFromDev(mfile* mf)
{
    MError mRc;
    u_int8_t tlvBuff[TOOLS_OPEN_TPT_CONFIGURATION_SIZE] = {0};
    struct tools_open_tpt_configuration tptSettingsTlv;
    memset(&tptSettingsTlv, 0, sizeof(tptSettingsTlv));

    if (_updated) {
        return MCE_SUCCESS;
    }

    mRc = mnvaCom5thGen(mf, &tlvBuff[0], TOOLS_OPEN_TPT_CONFIGURATION_SIZE, getTptSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET);

    if (mRc) {
        if (mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get TPT configuration: %s", m_err2str(mRc));
    }
    // unpack and update
    tools_open_tpt_configuration_unpack(&tptSettingsTlv, &tlvBuff[0]);
    _logMaxPayloadSize = tptSettingsTlv.log_max_payload_size;

    _updated = true;

   return MCE_SUCCESS;
}

int TptParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;

    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    // get Tlv modify it and set it
    u_int8_t tlvBuff[TOOLS_OPEN_TPT_CONFIGURATION_SIZE] = {0};
    struct tools_open_tpt_configuration tptSettingsTlv;
    memset(&tptSettingsTlv, 0, sizeof(tptSettingsTlv));

    mRc = mnvaCom5thGen(mf, tlvBuff, TOOLS_OPEN_TPT_CONFIGURATION_SIZE, getTptSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (mRc && mRc != ME_REG_ACCESS_RES_NOT_AVLBL) {
        return errmsg("failed to set TPT settings: %s", m_err2str(mRc));
    }
    tools_open_tpt_configuration_unpack(&tptSettingsTlv, tlvBuff);

    tptSettingsTlv.log_max_payload_size = _logMaxPayloadSize;

    // pack it
    tools_open_tpt_configuration_pack(&tptSettingsTlv, tlvBuff);

    mRc = mnvaCom5thGen(mf, tlvBuff, TOOLS_OPEN_TPT_CONFIGURATION_SIZE, getTptSettingsTlvTypeBe(), REG_ACCESS_METHOD_SET);

    if (mRc) {
        return errmsg("failed to set TPT settings: %s", m_err2str(mRc));
    }
    _updated = false;

    return MCE_SUCCESS;
}

int TptParams5thGen::getDefaultParams(mfile* mf)
{
    int rc = getDefaultsAndCapabilities(mf);
    setParams(_logMaxPayloadSizeDefault);
    return rc;
}

void TptParams5thGen::setParams(u_int32_t logMaxPayloadSize)
{
    _logMaxPayloadSize = logMaxPayloadSize;
}

int TptParams5thGen::getDefaultsAndCapabilities(mfile* mf)
{
    MError rc;
    u_int8_t tlvCapBuff[TOOLS_OPEN_TPT_CAPABILITIES_SIZE] = {0};
    struct tools_open_tpt_capabilities tptCapabilitesTlv;
    memset(&tptCapabilitesTlv, 0, sizeof(tptCapabilitesTlv));
    rc = mnvaCom5thGen(mf, &tlvCapBuff[0], TOOLS_OPEN_TPT_CAPABILITIES_SIZE, getTptCapabilitiesTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (rc) {
        return errmsg("Failed to get TPT capabilities parameter. %s", m_err2str(rc));
    }
    tools_open_tpt_capabilities_unpack(&tptCapabilitesTlv, tlvCapBuff);
    _logMaxPayloadSizeSupported = tptCapabilitesTlv.log_max_payload_size_supported;

    u_int8_t tlvBuff[TOOLS_OPEN_TPT_CONFIGURATION_SIZE] = {0};
    struct tools_open_tpt_configuration tptSettingsTlv;
    memset(&tptSettingsTlv, 0, sizeof(tptSettingsTlv));

    rc = mnvaCom5thGen(mf, &tlvBuff[0], TOOLS_OPEN_TPT_CONFIGURATION_SIZE, getTptSettingsTlvTypeBe(), REG_ACCESS_METHOD_GET, true);

    if (rc) {
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get TPT default configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_tpt_configuration_unpack(&tptSettingsTlv, &tlvBuff[0]);
    _logMaxPayloadSizeDefault = tptSettingsTlv.log_max_payload_size;

    return MCE_SUCCESS;
}

u_int32_t TptParams5thGen::getTptSettingsTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = tlvTypeIdx;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t TptParams5thGen::getTptCapabilitiesTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = TPT_CAPABILITES_TYPE;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

bool TptParams5thGen::hardLimitCheck()
{
    if (_logMaxPayloadSize != 0 && _logMaxPayloadSize != 12) {
        errmsg("Illegal LOG_MAX_TPT_PAYLOAD_SIZE parameter value. (should be 0(auto) or 12(4KB))");
        return false;
    }
    return true;
}

/*
 * InfinibandBootSettingsParams4thGen Class implementation:
 */

bool InfinibandBootSettingsParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)param;
    struct tools_open_query_def_params_per_port portParams;
    int rc;
    rc = getDefaultParams4thGen(mf, _port, &portParams);
    if (rc) {
        return false;
    }
    return portParams.nv_config_infiniband_boot_settings;
}

void InfinibandBootSettingsParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Boot_Pkey_P1 && _port == 1) || (paramType == Mcp_Boot_Pkey_P2 && _port == 2)) {
        _bootPkey = val;
    }
}

u_int32_t InfinibandBootSettingsParams4thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Boot_Pkey_P1 && _port == 1) || (paramType == Mcp_Boot_Pkey_P2 && _port == 2)) {
        return _bootPkey;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t InfinibandBootSettingsParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Boot_Pkey_P1 && _port == 1) || (paramType == Mcp_Boot_Pkey_P2 && _port == 2)) {
        return _bootPkeyDefault;
    }
    return MLXCFG_UNKNOWN;
}


int InfinibandBootSettingsParams4thGen::getFromDev(mfile* mf)
{
    MError mRc;
    u_int8_t tlvBuff[TOOLS_OPEN_INFINIBAND_BOOT_SETTINGS_SIZE] = {0};
    struct tools_open_infiniband_boot_settings bootSettingsTlv;
    memset(&bootSettingsTlv, 0, sizeof(bootSettingsTlv));

    if (_updated) {
        return MCE_SUCCESS;
    }

    mRc = mnvaCom4thGen(mf, &tlvBuff[0], TOOLS_OPEN_INFINIBAND_BOOT_SETTINGS_SIZE, tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);

    if (mRc) {
        if (mRc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg("Failed to get Infiniband Boot Settings: %s", m_err2str(mRc));
    }
    // unpack and update
    tools_open_infiniband_boot_settings_unpack(&bootSettingsTlv, &tlvBuff[0]);
    _bootPkey = bootSettingsTlv.boot_pkey;
    _updated = true;

   return MCE_SUCCESS;
}
int InfinibandBootSettingsParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    MError mRc;

    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    // get Tlv modify it and set it
    u_int8_t tlvBuff[TOOLS_OPEN_INFINIBAND_BOOT_SETTINGS_SIZE] = {0};
    struct tools_open_infiniband_boot_settings bootSettingsTlv;
    memset(&bootSettingsTlv, 0, sizeof(bootSettingsTlv));

    bootSettingsTlv.boot_pkey = _bootPkey;

    // pack it
    tools_open_infiniband_boot_settings_pack(&bootSettingsTlv, tlvBuff);

    mRc = mnvaCom4thGen(mf, tlvBuff, TOOLS_OPEN_TPT_CONFIGURATION_SIZE, tlvTypeIdx, REG_ACCESS_METHOD_SET, _port);

    if (mRc) {
        return errmsg("failed to set Infiniband Boot Settings: %s", m_err2str(mRc));
    }
    _updated = false;

    return MCE_SUCCESS;
}

int InfinibandBootSettingsParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port portParams;
    int rc;
    rc = getDefaultParams4thGen(mf, _port, &portParams);
    if (rc == MCE_SUCCESS) {
        _bootPkeyDefault = portParams.default_boot_pkey;
        setParams(_bootPkeyDefault);
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

void InfinibandBootSettingsParams4thGen::setParams(u_int32_t bootPkey)
{
    _bootPkey = bootPkey;
}

bool InfinibandBootSettingsParams4thGen::hardLimitCheck()
{
    if (_bootPkey >= (1 << 16)) {
        errmsg("Illegal BOOT_PKEY_P%d parameter value, valid values: [0..65535]", ((_port == 1) ? 1 : 2));
        return false;
    }
    return true;
}

/*
 * IBDCParams5thGen Class implementation:
 */

bool IBDCParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getDcCapabilitiesTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get Infiniband DC capabilities parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead) {
        return false;
    }

    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get Infiniband DC Settings parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!(suppRead && suppWrite)) {
        return false;
    }
    return true;
}

void IBDCParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Log_Dcr_Hash_Table_Size) {
        _logDcrHashTableSize = val;
    }
    if (paramType == Mcp_Dcr_Lifo_Size) {
        _dcrLifoSize = val;
    }
}

u_int32_t IBDCParams5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Dcr_Hash_Table_Size) {
        return _logDcrHashTableSize;
    }
    if (paramType == Mcp_Dcr_Lifo_Size) {
        return _dcrLifoSize;
    }

    return MLXCFG_UNKNOWN;
}

u_int32_t IBDCParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Log_Dcr_Hash_Table_Size) {
        return _logDcrHashTableSizeDefault;
    }
    if (paramType == Mcp_Dcr_Lifo_Size) {
        return _dcrLifoSizeDefault;
    }

    return MLXCFG_UNKNOWN;
}

void IBDCParams5thGen::setParams(u_int32_t logDcrHashTableSize, u_int32_t dcrLifoSize)
{
    _logDcrHashTableSize = logDcrHashTableSize;
    _dcrLifoSize = dcrLifoSize;
}

void IBDCParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(_logDcrHashTableSizeDefault,
            _dcrLifoSizeDefault);
}

int IBDCParams5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_infiniband_dc_settings, "IB Dynamically Connected");
}

int IBDCParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_infiniband_dc_settings, "IB Dynamically Connected");
}

int IBDCParams5thGen::getDefaultParams(mfile* mf)
{
    return getDefaultsAndCapabilities(mf);
}

int IBDCParams5thGen::getDefaultsAndCapabilities(mfile* mf)
{
    MError rc;
    u_int8_t tlvCapBuff[TOOLS_OPEN_INFINIBAND_DC_CAPABILITIES_SIZE] = {0};
    struct tools_open_infiniband_dc_capabilities dcCapabilitesTlv;
    memset(&dcCapabilitesTlv, 0, sizeof(dcCapabilitesTlv));
    rc = mnvaCom5thGen(mf, &tlvCapBuff[0], TOOLS_OPEN_INFINIBAND_DC_CAPABILITIES_SIZE, getDcCapabilitiesTlvTypeBe(), REG_ACCESS_METHOD_GET);
    if (rc) {
        return errmsg("Failed to get Infiniband DC capabilities parameter. %s", m_err2str(rc));
    }
    tools_open_infiniband_dc_capabilities_unpack(&dcCapabilitesTlv, tlvCapBuff);
    _minLogDcrHashTableSize = dcCapabilitesTlv.min_log_dcr_hash_table_size;
    _maxLogDcrHashTableSize = dcCapabilitesTlv.max_log_dcr_hash_table_size;
    _minDcrLifoSize = dcCapabilitesTlv.min_dcr_lifo_size;
    _maxDcrLifoSize = dcCapabilitesTlv.max_dcr_lifo_size;

    GET_DEFAULT_5TH_GEN(mf, tools_open_infiniband_dc_settings, "IB Dynamically Connected");
}

u_int32_t IBDCParams5thGen::getTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = tlvTypeIdx;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t IBDCParams5thGen::getDcCapabilitiesTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = INFINIBAND_DC_CAPABILITIES_TYPE;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

bool IBDCParams5thGen::hardLimitCheck()
{
    if (_logDcrHashTableSize < _minLogDcrHashTableSize || _logDcrHashTableSize > _maxLogDcrHashTableSize) {
        errmsg("Illegal LOG_DCR_HASH_TABLE_SIZE parameter value. (should be within the range [%d..%d])", _minLogDcrHashTableSize, _maxLogDcrHashTableSize);
        return false;
    }
    if (_dcrLifoSize < _minDcrLifoSize || _dcrLifoSize > _maxDcrLifoSize) {
        errmsg("Illegal DCR_LIFO_SIZE parameter value. (should be within the range [%d..%d])", _minDcrLifoSize, _maxDcrLifoSize);
        return false;
    }
    return true;
}

void IBDCParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_infiniband_dc_settings* ibDcTlv = (struct tools_open_infiniband_dc_settings*)tlv;
    ibDcTlv->dcr_lifo_size = _dcrLifoSize;
    ibDcTlv->log_dcr_hash_table_size = _logDcrHashTableSize;
    return;
}

void IBDCParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_infiniband_dc_settings* ibDcTlv = (struct tools_open_infiniband_dc_settings*)tlv;
    _dcrLifoSize = ibDcTlv->dcr_lifo_size;
    _logDcrHashTableSize = ibDcTlv->log_dcr_hash_table_size;
    return;
}

void IBDCParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_infiniband_dc_settings* ibDcTlv = (struct tools_open_infiniband_dc_settings*)tlv;
    _dcrLifoSizeDefault = ibDcTlv->dcr_lifo_size;
    _logDcrHashTableSizeDefault = ibDcTlv->log_dcr_hash_table_size;
    return;
}

/*
 * RoCENextProtocolParams5thGen Class implementation
 */


bool RoCENextProtocolParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get RoCE next protocol parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead || !suppWrite) {
        return false;
    }
    return true;
}

void RoCENextProtocolParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ( paramType == Mcp_RoCE_Next_Protocol) {
        _nextProtocol = val;
    }
    return;
}

u_int32_t RoCENextProtocolParams5thGen::getParam(mlxCfgParam paramType)
{
    if ( paramType == Mcp_RoCE_Next_Protocol) {
        return _nextProtocol;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t RoCENextProtocolParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ( paramType == Mcp_RoCE_Next_Protocol) {
        return _nextProtocolDefault;
    }
    return MLXCFG_UNKNOWN;
}

void RoCENextProtocolParams5thGen::setParams(u_int32_t nextProtocol)
{
    _nextProtocol = nextProtocol;
}

void RoCENextProtocolParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(_nextProtocolDefault);
}

int RoCENextProtocolParams5thGen::getFromDev(mfile* mf)
{
   GET_FROM_DEV_5TH_GEN(mf, tools_open_roce_v_1_5_next_protocol, "RoCE Next Protocol");
}

int RoCENextProtocolParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_roce_v_1_5_next_protocol, "RoCE Next Protocol");
}

int RoCENextProtocolParams5thGen::getDefaultParams(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_roce_v_1_5_next_protocol, "RoCE Next Protocol");
}

bool RoCENextProtocolParams5thGen::hardLimitCheck()
{
    if (_nextProtocol > 255) {
        errmsg("Illegal ROCE_NEXT_PROTOCOL parameter value(0x%x), value should be in range [0..0xff]", _nextProtocol);
        return false;
    }
    return true;
}

u_int32_t RoCENextProtocolParams5thGen::getTlvTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = CLASS_GLOBAL;
    type.param_idx = tlvTypeIdx;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

void RoCENextProtocolParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_roce_v_1_5_next_protocol* roceNpTlv = (struct tools_open_roce_v_1_5_next_protocol*)tlv;
    roceNpTlv->roce_over_ip_next_protocol = _nextProtocol;
    return;
}

void RoCENextProtocolParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_roce_v_1_5_next_protocol* roceNpTlv = (struct tools_open_roce_v_1_5_next_protocol*)tlv;
    _nextProtocol = roceNpTlv->roce_over_ip_next_protocol;
    return;
}

void RoCENextProtocolParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_roce_v_1_5_next_protocol* roceNpTlv = (struct tools_open_roce_v_1_5_next_protocol*)tlv;
    _nextProtocolDefault = roceNpTlv->roce_over_ip_next_protocol;
    return;
}

/*
 * RoCECCParams5thGen Class implementation
 */


bool RoCECCParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get RoCE CC parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead || !suppWrite) {
        return false;
    }
    return true;
}

void RoCECCParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ( (paramType == Mcp_RoCE_CC_Algorithm_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Algorithm_P2 && _port == 2)) {
        _roceCcAlgorithm = val;
    }
    if ( (paramType == Mcp_RoCE_CC_Prio_Mask_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Prio_Mask_P2 && _port == 2)) {
        _roceCcPrioMask = val;
    }
    return;
}

u_int32_t RoCECCParams5thGen::getParam(mlxCfgParam paramType)
{
    if ( (paramType == Mcp_RoCE_CC_Algorithm_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Algorithm_P2 && _port == 2)) {
        return _roceCcAlgorithm;
    }
    if ( (paramType == Mcp_RoCE_CC_Prio_Mask_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Prio_Mask_P2 && _port == 2)) {
        return _roceCcPrioMask;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t RoCECCParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ( (paramType == Mcp_RoCE_CC_Algorithm_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Algorithm_P2 && _port == 2)) {
        return _roceCcAlgorithmDefault;
    }
    if ( (paramType == Mcp_RoCE_CC_Prio_Mask_P1 && _port == 1) || (paramType == Mcp_RoCE_CC_Prio_Mask_P2 && _port == 2)) {
        return _roceCcPrioMaskDefault;
    }
    return MLXCFG_UNKNOWN;
}

void RoCECCParams5thGen::setParams(u_int32_t roceCcAlgorithm, u_int32_t roceCcPrioMask)
{
    _roceCcAlgorithm = roceCcAlgorithm;
    _roceCcPrioMask = roceCcPrioMask;
}

void RoCECCParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(
        _roceCcAlgorithmDefault,
        _roceCcPrioMaskDefault);
}

int RoCECCParams5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_roce_cc, "RoCE CC");
}

int RoCECCParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_roce_cc, "RoCE CC");
}
int RoCECCParams5thGen::getDefaultParams(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_roce_cc, "RoCE CC");
}

bool RoCECCParams5thGen::hardLimitCheck()
{
    if (_roceCcAlgorithm > 1) {
        errmsg("Illegal ROCE_CC_ALGORITHM_P%d parameter value(%d), value should be 0 for ECN or 1 for QCN", _port, _roceCcAlgorithm);
        return false;
    }
    if (_roceCcPrioMask > 255) {
        errmsg("Illegal ROCE_CC_PRIO_MASK_P%d parameter value(%#x), value should be within the range [0..0xff]", _port, _roceCcPrioMask);
        return false;
    }
    return true;
}

u_int32_t RoCECCParams5thGen::getTlvTypeBe()
{
    struct tools_open_per_port_type type;
    u_int32_t tlvType = 0;
    type.param_class = CLASS_PHYS_PORT;
    type.param_idx = tlvTypeIdx;
    type.port = _port;
    tools_open_per_port_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

void RoCECCParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_roce_cc* roceCcTlv = (struct tools_open_roce_cc*)tlv;
    roceCcTlv->roce_cc_algorithm = _roceCcAlgorithm;
    roceCcTlv->roce_cc_enable_priority = _roceCcPrioMask;
    return;
}

void RoCECCParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_roce_cc* roceCcTlv = (struct tools_open_roce_cc*)tlv;
    _roceCcAlgorithm = roceCcTlv->roce_cc_algorithm;
    _roceCcPrioMask = roceCcTlv->roce_cc_enable_priority;
    return;
}

void RoCECCParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_roce_cc* roceCcTlv = (struct tools_open_roce_cc*)tlv;
    _roceCcAlgorithmDefault = roceCcTlv->roce_cc_algorithm;
    _roceCcPrioMaskDefault = roceCcTlv->roce_cc_enable_priority;
    return;
}

/*
 * RoCECCEcnParams5thGen Class implementation
 */


bool RoCECCEcnParams5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get RoCE CC ECN parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead || !suppWrite) {
        return false;
    }
    return true;
}

void RoCECCEcnParams5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    // TODO: adrianc move to MAP on large scale TLVs std::map<mlxCfgParam, u_int32_t> for easier access, init in constructor according to port
    if (_port == 1) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P1:
            _clampTgtRate = val;
            break;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1:
            _clampTgtRateAfterTimeInc = val;
            break;
        case Mcp_Rpg_Time_Reset_P1:
            _rpgTimeReset = val;
            break;
        case Mcp_Rpg_Byte_Reset_P1:
            _rpgByteReset = val;
            break;
        case Mcp_Rpg_Threshold_P1:
            _rpgThreshold = val;
            break;
        case Mcp_Rpg_Max_Rate_P1:
            _rpgMaxRate = val;
            break;
        case Mcp_Rpg_Ai_Rate_P1:
            _rpgAiRate = val;
            break;
        case Mcp_Rpg_Hai_Rate_P1:
            _rpgHaiRate = val;
            break;
        case Mcp_Rpg_Gd_P1:
            _rpgGd = val;
            break;
        case Mcp_Rpg_Min_Dec_Fac_P1:
            _rpgMinDecFac = val;
            break;
        case Mcp_Rpg_Min_Rate_P1:
            _rpgMinRate = val;
            break;
        case Mcp_Rate_To_Set_On_First_Cnp_P1:
            _rateToSetOnFirstCnp = val;
            break;
        case Mcp_Dce_Tcp_G_P1:
            _dceTcpG = val;
            break;
        case Mcp_Dce_Tcp_Rtt_P1:
            _dceTcpRtt = val;
            break;
        case Mcp_Rate_Reduce_Monitor_Period_P1:
            _rateReduceMonitorPeriod = val;
            break;
        case Mcp_Initial_Alpha_Value_P1:
            _initialAlphaValue = val;
            break;
        case Mcp_Min_Time_Between_Cnps_P1:
            _minTimeBetweenCnps = val;
            break;
        case Mcp_Cnp_Dscp_P1:
            _cnpDscp = val;
            break;
        case Mcp_Cnp_802p_Prio_P1:
            _cnp802pPrio = val;
            break;
        default:
            break;
        }
    } else if (_port == 2) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P2:
            _clampTgtRate = val;
            break;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2:
            _clampTgtRateAfterTimeInc = val;
            break;
        case Mcp_Rpg_Time_Reset_P2:
            _rpgTimeReset = val;
            break;
        case Mcp_Rpg_Byte_Reset_P2:
            _rpgByteReset = val;
            break;
        case Mcp_Rpg_Threshold_P2:
            _rpgThreshold = val;
            break;
        case Mcp_Rpg_Max_Rate_P2:
            _rpgMaxRate = val;
            break;
        case Mcp_Rpg_Ai_Rate_P2:
            _rpgAiRate = val;
            break;
        case Mcp_Rpg_Hai_Rate_P2:
            _rpgHaiRate = val;
            break;
        case Mcp_Rpg_Gd_P2:
            _rpgGd = val;
            break;
        case Mcp_Rpg_Min_Dec_Fac_P2:
            _rpgMinDecFac = val;
            break;
        case Mcp_Rpg_Min_Rate_P2:
            _rpgMinRate = val;
            break;
        case Mcp_Rate_To_Set_On_First_Cnp_P2:
            _rateToSetOnFirstCnp = val;
            break;
        case Mcp_Dce_Tcp_G_P2:
            _dceTcpG = val;
            break;
        case Mcp_Dce_Tcp_Rtt_P2:
            _dceTcpRtt = val;
            break;
        case Mcp_Rate_Reduce_Monitor_Period_P2:
            _rateReduceMonitorPeriod = val;
            break;
        case Mcp_Initial_Alpha_Value_P2:
            _initialAlphaValue = val;
            break;
        case Mcp_Min_Time_Between_Cnps_P2:
            _minTimeBetweenCnps = val;
            break;
        case Mcp_Cnp_Dscp_P2:
            _cnpDscp = val;
            break;
        case Mcp_Cnp_802p_Prio_P2:
            _cnp802pPrio = val;
            break;
        default:
            break;
        }
    }
    return;
}

u_int32_t RoCECCEcnParams5thGen::getParam(mlxCfgParam paramType)
{
    // adrianc: consider moving to MAP on large scale TLVs
    if (_port == 1) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P1:
            return _clampTgtRate;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1:
            return _clampTgtRateAfterTimeInc;
        case Mcp_Rpg_Time_Reset_P1:
            return _rpgTimeReset;
        case Mcp_Rpg_Byte_Reset_P1:
            return _rpgByteReset;
        case Mcp_Rpg_Threshold_P1:
            return _rpgThreshold;
        case Mcp_Rpg_Max_Rate_P1:
            return _rpgMaxRate;
        case Mcp_Rpg_Ai_Rate_P1:
            return _rpgAiRate;
        case Mcp_Rpg_Hai_Rate_P1:
            return _rpgHaiRate;
        case Mcp_Rpg_Gd_P1:
            return _rpgGd;
        case Mcp_Rpg_Min_Dec_Fac_P1:
            return _rpgMinDecFac;
        case Mcp_Rpg_Min_Rate_P1:
            return _rpgMinRate;
        case Mcp_Rate_To_Set_On_First_Cnp_P1:
            return _rateToSetOnFirstCnp;
        case Mcp_Dce_Tcp_G_P1:
            return _dceTcpG;
        case Mcp_Dce_Tcp_Rtt_P1:
            return _dceTcpRtt;
        case Mcp_Rate_Reduce_Monitor_Period_P1:
            return _rateReduceMonitorPeriod;
        case Mcp_Initial_Alpha_Value_P1:
            return _initialAlphaValue;
        case Mcp_Min_Time_Between_Cnps_P1:
            return _minTimeBetweenCnps;
        case Mcp_Cnp_Dscp_P1:
            return _cnpDscp;
        case Mcp_Cnp_802p_Prio_P1:
            return _cnp802pPrio;
        default:
            break;
        }
    } else if (_port == 2) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P2:
            return _clampTgtRate;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2:
            return _clampTgtRateAfterTimeInc;
        case Mcp_Rpg_Time_Reset_P2:
            return _rpgTimeReset;
        case Mcp_Rpg_Byte_Reset_P2:
            return _rpgByteReset;
        case Mcp_Rpg_Threshold_P2:
            return _rpgThreshold;
        case Mcp_Rpg_Max_Rate_P2:
            return _rpgMaxRate;
        case Mcp_Rpg_Ai_Rate_P2:
            return _rpgAiRate;
        case Mcp_Rpg_Hai_Rate_P2:
            return _rpgHaiRate;
        case Mcp_Rpg_Gd_P2:
            return _rpgGd;
        case Mcp_Rpg_Min_Dec_Fac_P2:
            return _rpgMinDecFac;
        case Mcp_Rpg_Min_Rate_P2:
            return _rpgMinRate;
        case Mcp_Rate_To_Set_On_First_Cnp_P2:
            return _rateToSetOnFirstCnp;
        case Mcp_Dce_Tcp_G_P2:
            return _dceTcpG;
        case Mcp_Dce_Tcp_Rtt_P2:
            return _dceTcpRtt;
        case Mcp_Rate_Reduce_Monitor_Period_P2:
            return _rateReduceMonitorPeriod;
        case Mcp_Initial_Alpha_Value_P2:
            return _initialAlphaValue;
        case Mcp_Min_Time_Between_Cnps_P2:
            return _minTimeBetweenCnps;
        case Mcp_Cnp_Dscp_P2:
            return _cnpDscp;
        case Mcp_Cnp_802p_Prio_P2:
            return _cnp802pPrio;
        default:
            break;
        }
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t RoCECCEcnParams5thGen::getDefaultParam(mlxCfgParam paramType)
{
    // adrianc: consider moving to MAP on large scale TLVs
    if (_port == 1) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P1:
            return _clampTgtRateDefault;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P1:
            return _clampTgtRateAfterTimeIncDefault;
        case Mcp_Rpg_Time_Reset_P1:
            return _rpgTimeResetDefault;
        case Mcp_Rpg_Byte_Reset_P1:
            return _rpgByteResetDefault;
        case Mcp_Rpg_Threshold_P1:
            return _rpgThresholdDefault;
        case Mcp_Rpg_Max_Rate_P1:
            return _rpgMaxRateDefault;
        case Mcp_Rpg_Ai_Rate_P1:
            return _rpgAiRateDefault;
        case Mcp_Rpg_Hai_Rate_P1:
            return _rpgHaiRateDefault;
        case Mcp_Rpg_Gd_P1:
            return _rpgGdDefault;
        case Mcp_Rpg_Min_Dec_Fac_P1:
            return _rpgMinDecFacDefault;
        case Mcp_Rpg_Min_Rate_P1:
            return _rpgMinRateDefault;
        case Mcp_Rate_To_Set_On_First_Cnp_P1:
            return _rateToSetOnFirstCnpDefault;
        case Mcp_Dce_Tcp_G_P1:
            return _dceTcpGDefault;
        case Mcp_Dce_Tcp_Rtt_P1:
            return _dceTcpRttDefault;
        case Mcp_Rate_Reduce_Monitor_Period_P1:
            return _rateReduceMonitorPeriodDefault;
        case Mcp_Initial_Alpha_Value_P1:
            return _initialAlphaValueDefault;
        case Mcp_Min_Time_Between_Cnps_P1:
            return _minTimeBetweenCnpsDefault;
        case Mcp_Cnp_Dscp_P1:
            return _cnpDscpDefault;
        case Mcp_Cnp_802p_Prio_P1:
            return _cnp802pPrioDefault;
        default:
            break;
        }
    } else if (_port == 2) {
        switch (paramType) {
        case Mcp_Clamp_Tgt_Rate_P2:
            return _clampTgtRateDefault;
        case Mcp_Clamp_Tgt_Rate_After_Time_Inc_P2:
            return _clampTgtRateAfterTimeIncDefault;
        case Mcp_Rpg_Time_Reset_P2:
            return _rpgTimeResetDefault;
        case Mcp_Rpg_Byte_Reset_P2:
            return _rpgByteResetDefault;
        case Mcp_Rpg_Threshold_P2:
            return _rpgThresholdDefault;
        case Mcp_Rpg_Max_Rate_P2:
            return _rpgMaxRateDefault;
        case Mcp_Rpg_Ai_Rate_P2:
            return _rpgAiRateDefault;
        case Mcp_Rpg_Hai_Rate_P2:
            return _rpgHaiRateDefault;
        case Mcp_Rpg_Gd_P2:
            return _rpgGdDefault;
        case Mcp_Rpg_Min_Dec_Fac_P2:
            return _rpgMinDecFacDefault;
        case Mcp_Rpg_Min_Rate_P2:
            return _rpgMinRateDefault;
        case Mcp_Rate_To_Set_On_First_Cnp_P2:
            return _rateToSetOnFirstCnpDefault;
        case Mcp_Dce_Tcp_G_P2:
            return _dceTcpGDefault;
        case Mcp_Dce_Tcp_Rtt_P2:
            return _dceTcpRttDefault;
        case Mcp_Rate_Reduce_Monitor_Period_P2:
            return _rateReduceMonitorPeriodDefault;
        case Mcp_Initial_Alpha_Value_P2:
            return _initialAlphaValueDefault;
        case Mcp_Min_Time_Between_Cnps_P2:
            return _minTimeBetweenCnpsDefault;
        case Mcp_Cnp_Dscp_P2:
            return _cnpDscpDefault;
        case Mcp_Cnp_802p_Prio_P2:
            return _cnp802pPrioDefault;
        default:
            break;
        }
    }
    return MLXCFG_UNKNOWN;
}

void RoCECCEcnParams5thGen::setParams(u_int32_t clampTgtRate, u_int32_t clampTgtRateAfterTimeInc, u_int32_t rpgTimeReset, u_int32_t rpgByteReset,
            u_int32_t rpgThreshold, u_int32_t rpgMaxRate, u_int32_t rpgAiRate, u_int32_t rpgHaiRate,
            u_int32_t rpgGd, u_int32_t rpgMinDecFac, u_int32_t rpgMinRate, u_int32_t rateToSetOnFirstCnp,
            u_int32_t dceTcpG, u_int32_t dceTcpRtt, u_int32_t rateReduceMonitorPeriod, u_int32_t initialAlphaValue,
            u_int32_t minTimeBetweenCnps, u_int32_t cnpDscp, u_int32_t cnp802pPrio){
    _clampTgtRate = clampTgtRate;
    _clampTgtRateAfterTimeInc = clampTgtRateAfterTimeInc;
    _rpgTimeReset = rpgTimeReset;
    _rpgByteReset = rpgByteReset;
    _rpgThreshold = rpgThreshold;
    _rpgMaxRate = rpgMaxRate;
    _rpgAiRate = rpgAiRate;
    _rpgHaiRate = rpgHaiRate;
    _rpgGd = rpgGd;
    _rpgMinDecFac = rpgMinDecFac;
    _rpgMinRate = rpgMinRate;
    _rateToSetOnFirstCnp = rateToSetOnFirstCnp;
    _dceTcpG = dceTcpG;
    _dceTcpRtt = dceTcpRtt;
    _rateReduceMonitorPeriod = rateReduceMonitorPeriod;
    _initialAlphaValue = initialAlphaValue;
    _minTimeBetweenCnps = minTimeBetweenCnps;
    _cnpDscp = cnpDscp;
    _cnp802pPrio = cnp802pPrio;
}

void RoCECCEcnParams5thGen::updateClassAttrFromDefaultParams()
{
    setParams(_clampTgtRateDefault,_clampTgtRateAfterTimeIncDefault,
     _rpgTimeResetDefault,
     _rpgByteResetDefault,
     _rpgThresholdDefault,
     _rpgMaxRateDefault,
     _rpgAiRateDefault,
     _rpgHaiRateDefault,
     _rpgGdDefault,
     _rpgMinDecFacDefault,
     _rpgMinRateDefault,
     _rateToSetOnFirstCnpDefault,
     _dceTcpGDefault,
     _dceTcpRttDefault,
     _rateReduceMonitorPeriodDefault,
     _initialAlphaValueDefault,
     _minTimeBetweenCnpsDefault,
     _cnpDscpDefault,
     _cnp802pPrioDefault);
}

int RoCECCEcnParams5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_roce_cc_ecn, "RoCE CC ECN");
}

int RoCECCEcnParams5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_roce_cc_ecn, "RoCE CC ECN");
}
int RoCECCEcnParams5thGen::getDefaultParams(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_roce_cc_ecn, "RoCE CC ECN");
}

u_int32_t _dceTcpG;
u_int32_t _dceTcpRtt;
u_int32_t _rateReduceMonitorPeriod;
u_int32_t _initialAlphaValue;
u_int32_t _minTimeBetweenCnps;
u_int32_t _cnpDscp;
u_int32_t _cnp802pPrio;

bool RoCECCEcnParams5thGen::hardLimitCheck()
{
    if (_clampTgtRate > 1) {
        errmsg("Illegal CLAMP_TGT_RATE_P%d parameter value(%d), value should be 0 or 1", _port, _clampTgtRate);
        return false;
    }

    if (_clampTgtRateAfterTimeInc > 1) {
        errmsg("Illegal CLAMP_TGT_RATE_AFTER_TIME_INC_P%d parameter value(%d), value should be 0 or 1", _port, _clampTgtRateAfterTimeInc);
        return false;
    }

    if ( _rpgTimeReset >= (1 << 16)) {
        errmsg("Illegal RPG_TIME_RESET_P%d parameter value(%d), value should be [0..%d]", _port, _rpgTimeReset, (1 << 16) - 1);
        return false;
    }

    if (_rpgByteReset >= (1 << 14)) {
        errmsg("Illegal RPG_BYTE_RESET_P%d parameter value(%d), value should be [0..%d]", _port, _rpgByteReset, (1 << 14) - 1);
        return false;
    }

    if (_rpgThreshold >= (1 << 4)) {
        errmsg("Illegal RPG_THRESHOLD_P%d parameter value(%d), value should be [0..%d]", _port, _rpgThreshold, (1 << 4) - 1);
        return false;
    }

    if ( _rpgAiRate >= (1 << 16)) {
        errmsg("Illegal RPG_AI_RATE_P%d parameter value(%d), value should be [0..%d]", _port, _rpgAiRate, (1 << 16) - 1);
        return false;
    }

    if ( _rpgHaiRate >= (1 << 16)) {
        errmsg("Illegal RPG_HAI_RATE_P%d parameter value(%d), value should be [0..%d]", _port, _rpgHaiRate, (1 << 16) - 1);
        return false;
    }

    if (_rpgGd > 15) {
        errmsg("Illegal RPG_GD_P%d parameters value(%d), value should be [0..%d]", _port, _rpgGd, 15);
        return false;
    }

    if (_rpgMinDecFac == 0 || _rpgMinDecFac > 100) {
        errmsg("Illegal RPG_MIN_DEC_FAC_P%d parameters value(%d), value should be [1..100]", _port, _rpgMinDecFac);
        return false;
    }

    if (_rpgMinRate >= (1 << 16)) {
        errmsg("Illegal RPG_MIN_RATE_P%d parameters value(%d), value should be [1..%d]", _port, _rpgMinRate, (1 << 16) - 1);
        return false;
    }

    if (_rateToSetOnFirstCnp >= (1 << 16)) {
        errmsg("Illegal RATE_TO_SET_ON_FIRST_CNP_P%d parameters value(%d), value should be [1..%d]", _port, _rateToSetOnFirstCnp, (1 << 16) - 1);
        return false;
    }

    if (_dceTcpG >= (1 << 9)) {
        errmsg("Illegal DCE_TCP_G_P%d parameters value(%d), value should be [1..%d]", _port, _dceTcpG, (1 << 9) - 1);
        return false;
    }

    if (_dceTcpRtt >= (1 << 16)) {
        errmsg("Illegal DCE_TCP_RTT_P%d parameters value(%d), value should be [1..%d]", _port, _dceTcpRtt, (1 << 16) - 1);
        return false;
    }

    if (_rateReduceMonitorPeriod >= (1 << 16)) {
        errmsg("Illegal RATE_REDUCE_MONITOR_PERIOD_P%d parameters value(%d), value should be [1..%d]", _port, _rateReduceMonitorPeriod, (1 << 16) - 1);
        return false;
    }

    if (_initialAlphaValue >= (1 << 9)) {
        errmsg("Illegal INITIAL_ALPHA_VALUE_P%d parameters value(%d), value should be [1..%d]", _port, _initialAlphaValue, (1 << 9) - 1);
        return false;
    }

    if (_minTimeBetweenCnps >= (1 << 16)) {
        errmsg("Illegal MIN_TIME_BETWEEN_CNPS_P%d parameters value(%d), value should be [1..%d]", _port, _minTimeBetweenCnps, (1 << 16) - 1);
        return false;
    }

    if (_cnpDscp > 7) {
        errmsg("Illegal CNP_DSCP_P%d parameters value(%d), value should be [0..7]", _port, _cnpDscp);
        return false;
    }

    if (_cnp802pPrio >= (1 << 6)) {
        errmsg("Illegal CNP_802P_PRIO_P%d parameters value(%d), value should be [1..%d]", _port, _cnp802pPrio, (1 << 6) - 1);
        return false;
    }
    return true;
}

u_int32_t RoCECCEcnParams5thGen::getTlvTypeBe()
{
    struct tools_open_per_port_type type;
    u_int32_t tlvType = 0;
    type.param_class = CLASS_PHYS_PORT;
    type.param_idx = tlvTypeIdx;
    type.port = _port;
    tools_open_per_port_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}


void RoCECCEcnParams5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_roce_cc_ecn* roceCcEcnTlv = (struct tools_open_roce_cc_ecn*)tlv;
    roceCcEcnTlv->clamp_tgt_rate = _clampTgtRate;
    roceCcEcnTlv->clamp_tgt_rate_after_time_inc = _clampTgtRateAfterTimeInc;
    roceCcEcnTlv->cnp_802p_prio = _cnp802pPrio;
    roceCcEcnTlv->cnp_dscp = _cnpDscp;
    roceCcEcnTlv->dce_tcp_g = _dceTcpG;
    roceCcEcnTlv->dce_tcp_rtt = _dceTcpRtt;
    roceCcEcnTlv->initial_alpha_value = _initialAlphaValue;
    roceCcEcnTlv->min_time_between_cnps = _minTimeBetweenCnps;
    roceCcEcnTlv->rate_reduce_monitor_period = _rateReduceMonitorPeriod;
    roceCcEcnTlv->rate_to_set_on_first_cnp = _rateToSetOnFirstCnp;
    roceCcEcnTlv->rpg_ai_rate = _rpgAiRate;
    roceCcEcnTlv->rpg_byte_reset = _rpgByteReset;
    roceCcEcnTlv->rpg_gd = _rpgGd;
    roceCcEcnTlv->rpg_hai_rate = _rpgHaiRate;
    roceCcEcnTlv->rpg_max_rate = _rpgMaxRate;
    roceCcEcnTlv->rpg_min_dec_fac = _rpgMinDecFac;
    roceCcEcnTlv->rpg_min_rate = _rpgMinRate;
    roceCcEcnTlv->rpg_threshold = _rpgThreshold;
    roceCcEcnTlv->rpg_time_reset = _rpgTimeReset;
    return;
}

void RoCECCEcnParams5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_roce_cc_ecn* roceCcEcnTlv = (struct tools_open_roce_cc_ecn*)tlv;
    _clampTgtRate = roceCcEcnTlv->clamp_tgt_rate;
    _clampTgtRateAfterTimeInc = roceCcEcnTlv->clamp_tgt_rate_after_time_inc;
    _cnp802pPrio = roceCcEcnTlv->cnp_802p_prio;
    _cnpDscp = roceCcEcnTlv->cnp_dscp;
    _dceTcpG = roceCcEcnTlv->dce_tcp_g;
    _dceTcpRtt = roceCcEcnTlv->dce_tcp_rtt;
    _initialAlphaValue = roceCcEcnTlv->initial_alpha_value;
    _minTimeBetweenCnps = roceCcEcnTlv->min_time_between_cnps;
    _rateReduceMonitorPeriod = roceCcEcnTlv->rate_reduce_monitor_period;
    _rateToSetOnFirstCnp = roceCcEcnTlv->rate_to_set_on_first_cnp;
    _rpgAiRate = roceCcEcnTlv->rpg_ai_rate;
    _rpgByteReset = roceCcEcnTlv->rpg_byte_reset;
    _rpgGd = roceCcEcnTlv->rpg_gd;
    _rpgHaiRate = roceCcEcnTlv->rpg_hai_rate;
    _rpgMaxRate = roceCcEcnTlv->rpg_max_rate;
    _rpgMinDecFac = roceCcEcnTlv->rpg_min_dec_fac;
    _rpgMinRate = roceCcEcnTlv->rpg_min_rate;
    _rpgThreshold = roceCcEcnTlv->rpg_threshold;
    _rpgTimeReset = roceCcEcnTlv->rpg_time_reset;
    return;
}

void RoCECCEcnParams5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_roce_cc_ecn* roceCcEcnTlv = (struct tools_open_roce_cc_ecn*)tlv;
    _clampTgtRateDefault = roceCcEcnTlv->clamp_tgt_rate;
    _clampTgtRateAfterTimeIncDefault = roceCcEcnTlv->clamp_tgt_rate_after_time_inc;
    _cnp802pPrioDefault = roceCcEcnTlv->cnp_802p_prio;
    _cnpDscpDefault = roceCcEcnTlv->cnp_dscp;
    _dceTcpGDefault = roceCcEcnTlv->dce_tcp_g;
    _dceTcpRttDefault = roceCcEcnTlv->dce_tcp_rtt;
    _initialAlphaValueDefault = roceCcEcnTlv->initial_alpha_value;
    _minTimeBetweenCnpsDefault = roceCcEcnTlv->min_time_between_cnps;
    _rateReduceMonitorPeriodDefault = roceCcEcnTlv->rate_reduce_monitor_period;
    _rateToSetOnFirstCnpDefault = roceCcEcnTlv->rate_to_set_on_first_cnp;
    _rpgAiRateDefault = roceCcEcnTlv->rpg_ai_rate;
    _rpgByteResetDefault = roceCcEcnTlv->rpg_byte_reset;
    _rpgGdDefault = roceCcEcnTlv->rpg_gd;
    _rpgHaiRateDefault = roceCcEcnTlv->rpg_hai_rate;
    _rpgMaxRateDefault = roceCcEcnTlv->rpg_max_rate;
    _rpgMinDecFacDefault = roceCcEcnTlv->rpg_min_dec_fac;
    _rpgMinRateDefault = roceCcEcnTlv->rpg_min_rate;
    _rpgThresholdDefault = roceCcEcnTlv->rpg_threshold;
    _rpgTimeResetDefault = roceCcEcnTlv->rpg_time_reset;
    return;
}

/*
 * PrebootBootSettingsParams4thGen Class implementation:
 */

bool PrebootBootSettingsParams4thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    (void)param;
    struct tools_open_query_def_params_per_port portParams;
    int rc;
    rc = getDefaultParams4thGen(mf, _port, &portParams);
    if (rc) {
        return false;
    }
    return true; //portParams.nv_config_boot_parameters; <--BUG fw is not updating this bit, assume supported if query_def_params command passess
}

void PrebootBootSettingsParams4thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if ((paramType == Mcp_Boot_Option_Rom_En_P1 && _port == 1) || (paramType == Mcp_Boot_Option_Rom_En_P2 && _port == 2)) {
        _bootOptionRomEn = val;
    }

    if ((paramType == Mcp_Boot_Vlan_En_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_En_P2 && _port == 2)) {
        _bootVlanEn = val;
    }

    if ((paramType == Mcp_Boot_Retry_Cnt_P1 && _port == 1) || (paramType == Mcp_Boot_Retry_Cnt_P2 && _port == 2)) {
        _bootRetryCnt = val;
    }

    if ((paramType == Mcp_Legacy_Boot_Protocol_P1 && _port == 1) || (paramType == Mcp_Legacy_Boot_Protocol_P2 && _port == 2)) {
        _legacyBootProtocol = val;
    }

    if ((paramType == Mcp_Boot_Vlan_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_P2 && _port == 2)) {
        _bootVlan = val;
    }
}

u_int32_t PrebootBootSettingsParams4thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Boot_Option_Rom_En_P1 && _port == 1) || (paramType == Mcp_Boot_Option_Rom_En_P2 && _port == 2)) {
        return _bootOptionRomEn;
    }

    if ((paramType == Mcp_Boot_Vlan_En_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_En_P2 && _port == 2)) {
        return _bootVlanEn;
    }

    if ((paramType == Mcp_Boot_Retry_Cnt_P1 && _port == 1) || (paramType == Mcp_Boot_Retry_Cnt_P2 && _port == 2)) {
        return _bootRetryCnt;
    }

    if ((paramType == Mcp_Legacy_Boot_Protocol_P1 && _port == 1) || (paramType == Mcp_Legacy_Boot_Protocol_P2 && _port == 2)) {
        return _legacyBootProtocol;
    }

    if ((paramType == Mcp_Boot_Vlan_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_P2 && _port == 2)) {
        return _bootVlan;
    }

    return MLXCFG_UNKNOWN;
}

u_int32_t PrebootBootSettingsParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Boot_Option_Rom_En_P1 && _port == 1) || (paramType == Mcp_Boot_Option_Rom_En_P2 && _port == 2)) {
        return _bootOptionRomEnDefault;
    }

    if ((paramType == Mcp_Boot_Vlan_En_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_En_P2 && _port == 2)) {
        return _bootVlanEnDefault;
    }

    if ((paramType == Mcp_Boot_Retry_Cnt_P1 && _port == 1) || (paramType == Mcp_Boot_Retry_Cnt_P2 && _port == 2)) {
        return _bootRetryCntDefault;
    }

    if ((paramType == Mcp_Legacy_Boot_Protocol_P1 && _port == 1) || (paramType == Mcp_Legacy_Boot_Protocol_P2 && _port == 2)) {
        return _legacyBootProtocolDefault;
    }

    if ((paramType == Mcp_Boot_Vlan_P1 && _port == 1) || (paramType == Mcp_Boot_Vlan_P2 && _port == 2)) {
        return _bootVlanDefault;
    }

    return MLXCFG_UNKNOWN;
}

void PrebootBootSettingsParams4thGen::setParams(u_int32_t bootOptionRomEn, u_int32_t bootVlanEn, u_int32_t bootRetryCnt,
            u_int32_t legacyBootProtocol, u_int32_t bootVlan)
{
    _bootOptionRomEn = bootOptionRomEn;
    _bootVlanEn = bootVlanEn;
    _bootRetryCnt = bootRetryCnt;
    _legacyBootProtocol = legacyBootProtocol;
    _bootVlan = bootVlan;
}

void PrebootBootSettingsParams4thGen::updateClassAttrFromDefaultParams()
{
    setParams(_bootOptionRomEnDefault, _bootVlanEnDefault, _bootRetryCntDefault,
            _legacyBootProtocolDefault, _bootVlanDefault);
}

int PrebootBootSettingsParams4thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_4TH_GEN(mf, tools_open_preboot_boot_settings, "Preboot Boot Settings", _port);
}

int PrebootBootSettingsParams4thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_4TH_GEN(mf, ignoreCheck, tools_open_preboot_boot_settings, "Preboot Boot Settings", _port);
}

void PrebootBootSettingsParams4thGen::updateTlvFromClassAttr(void* tlv)
{

    struct tools_open_preboot_boot_settings* prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    prebootTlv->boot_option_rom_en = _bootOptionRomEn;
    prebootTlv->boot_vlan_en = _bootVlanEn;
    prebootTlv->boot_retry_count = _bootRetryCnt;
    prebootTlv->legacy_boot_protocol = _legacyBootProtocol;
    prebootTlv->boot_vlan = _bootVlan;

}

void PrebootBootSettingsParams4thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_preboot_boot_settings* prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    _bootOptionRomEn = prebootTlv->boot_option_rom_en;
    _bootVlanEn = prebootTlv->boot_vlan_en;
    _bootRetryCnt = prebootTlv->boot_retry_count;
    _legacyBootProtocol = prebootTlv->legacy_boot_protocol;
    _bootVlan = prebootTlv->boot_vlan;
}

void PrebootBootSettingsParams4thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_preboot_boot_settings* prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    _bootOptionRomEnDefault = prebootTlv->boot_option_rom_en;
    _bootVlanEnDefault = prebootTlv->boot_vlan_en;
    _bootRetryCntDefault = prebootTlv->boot_retry_count;
    _legacyBootProtocolDefault = prebootTlv->legacy_boot_protocol;
    _bootVlanDefault = prebootTlv->boot_vlan;
}

int PrebootBootSettingsParams4thGen::getDefaultParams(mfile* mf)
{
    struct tools_open_query_def_params_per_port portParams;
    int rc;
    rc = getDefaultParams4thGen(mf, _port, &portParams);
    if (rc == MCE_SUCCESS) {
        _bootOptionRomEnDefault = portParams.default_boot_option_rom_en;
        _bootVlanEnDefault = portParams.default_boot_vlan_en;
        _bootRetryCntDefault = portParams.default_boot_retry_cnt;
        _legacyBootProtocolDefault = portParams.default_boot_protocol;
        _bootVlanDefault = portParams.default_boot_vlan;
        updateClassAttrFromDefaultParams();
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

bool PrebootBootSettingsParams4thGen::hardLimitCheck()
{
    if (_bootOptionRomEn > 1) {
        errmsg("Illegal BOOT_OPTION_ROM_EN_P%d parameter value, valid values: 0 or 1", ((_port == 1) ? 1 : 2));
        return false;
    }
    if (_bootVlanEn > 1) {
        errmsg("Illegal BOOT_VLAN_EN_P%d parameter value, valid values: 0 or 1", ((_port == 1) ? 1 : 2));
        return false;
    }
    if (_bootRetryCnt > 7) {
        errmsg("Illegal BOOT_RETRY_CNT_P%d parameter value, valid values: [0..7]", ((_port == 1) ? 1 : 2));
        return false;
    }
    if (_legacyBootProtocol > 3) {
        errmsg("Illegal LEGACY_BOOT_PROTOCOL_P%d parameter value, valid values: [0..3]", ((_port == 1) ? 1 : 2));
        return false;
    }
    if (_bootVlan >= (1 << 12)) {
        errmsg("Illegal BOOT_VLAN_P%d parameter value, valid values: [0..4095]", ((_port == 1) ? 1 : 2));
        return false;
    }
    return true;
}

/*
 * ExternalPort5thGen Class implementation
 */


bool ExternalPort5thGen::cfgSupported(mfile* mf, mlxCfgParam param)
{
    MError rc;
    (void)param;
    bool suppRead, suppWrite;
    rc = nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite);
    if (rc) {
        errmsg("Failed to get External Port parameter capabilities. %s", m_err2str(rc));
        return false;
    }
    if (!suppRead || !suppWrite) {
        return false;
    }
    return true;
}

void ExternalPort5thGen::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Port_Owner) {
        _portOwner = val;
    }
    if (paramType == Mcp_Allow_Rd_Counters) {
        _allowRdCounters = val;
    }
    return;
}

u_int32_t ExternalPort5thGen::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Port_Owner) {
        return _portOwner;
    }
    if (paramType == Mcp_Allow_Rd_Counters) {
        return _allowRdCounters;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t ExternalPort5thGen::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Port_Owner) {
        return _portOwnerDefault;
    }
    if (paramType == Mcp_Allow_Rd_Counters) {
        return _allowRdCountersDefault;
    }
    return MLXCFG_UNKNOWN;
}

void ExternalPort5thGen::setParams(u_int32_t portOwner, u_int32_t allowRdCounters)
{
    _portOwner = portOwner;
    _allowRdCounters = allowRdCounters;
}

void ExternalPort5thGen::updateClassAttrFromDefaultParams()
{
    setParams(
            _portOwnerDefault,
            _allowRdCounters);
}

int ExternalPort5thGen::getFromDev(mfile* mf)
{
    GET_FROM_DEV_5TH_GEN(mf, tools_open_external_port, "External Port");
}

int ExternalPort5thGen::setOnDev(mfile* mf, bool ignoreCheck)
{
    SET_ON_DEV_5TH_GEN(mf, ignoreCheck, tools_open_external_port, "External Port");
}
int ExternalPort5thGen::getDefaultParams(mfile* mf)
{
    GET_DEFAULT_5TH_GEN(mf, tools_open_external_port, "External Port");
}

bool ExternalPort5thGen::hardLimitCheck()
{
    if (_portOwner > 1) {
        errmsg("Illegal PORT_OWNER parameter value(%d), value should be 0 or 1", _portOwner);
        return false;
    }
    if (_allowRdCounters > 1) {
        errmsg("Illegal ALLOW_RD_COUNTERS parameter value(%d), value should be 0 or 1", _allowRdCounters);
        return false;
    }
    return true;
}

u_int32_t ExternalPort5thGen::getTlvTypeBe()
{
    struct tools_open_per_host_type type;
    u_int32_t tlvType = 0;
    type.param_class = CLASS_PER_HOST;
    type.param_idx = tlvTypeIdx;
    type.function = 0;
    type.host = 0;
    tools_open_per_host_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

void ExternalPort5thGen::updateTlvFromClassAttr(void* tlv)
{
    struct tools_open_external_port* externalPortTlv = (struct tools_open_external_port*)tlv;
    externalPortTlv->port_owner = _portOwner;
    externalPortTlv->allow_rd_counters = _allowRdCounters;
    return;
}

void ExternalPort5thGen::updateClassAttrFromTlv(void* tlv)
{
    struct tools_open_external_port* externalPortTlv = (struct tools_open_external_port*)tlv;
    _portOwner = externalPortTlv->port_owner;
    _allowRdCounters = externalPortTlv->allow_rd_counters;
    return;
}

void ExternalPort5thGen::updateClassDefaultAttrFromTlv(void* tlv)
{
    struct tools_open_external_port* externalPortTlv = (struct tools_open_external_port*)tlv;
    _portOwnerDefault = externalPortTlv->port_owner;
    _allowRdCountersDefault = externalPortTlv->allow_rd_counters;
    return;
}

