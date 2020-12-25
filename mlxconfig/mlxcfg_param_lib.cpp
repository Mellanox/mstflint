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
 * mlxcfg_param_lib.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: adrianc
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

#include "mlxcfg_utils.h"

enum {
    SRIOV_MASK = 0x1,
    WOL_P1_MASK = 0x2,
    WOL_P2_MASK = 0x4,
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
    MError __mRc; \
    if (!(ignoreCheck) && !checkCfg()) { \
        return MCE_BAD_PARAMS; \
    } \
    int __tlvBuffSize = tlvStructName##_size(); \
    u_int8_t *__tlvBuff = new u_int8_t[__tlvBuffSize];\
    memset(__tlvBuff, 0, __tlvBuffSize); \
    struct tlvStructName __tlvStruct; \
    memset(&__tlvStruct, 0, sizeof(__tlvStruct)); \
    __mRc = mnvaCom5thGen(mf, __tlvBuff, __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET); \
    if (__mRc && __mRc != ME_REG_ACCESS_RES_NOT_AVLBL) { \
        delete[] __tlvBuff; \
        return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    tlvStructName##_unpack(&__tlvStruct, __tlvBuff); \
    updateTlvFromClassAttr((void*)&__tlvStruct); \
    tlvStructName##_pack(&__tlvStruct, __tlvBuff); \
    __mRc = mnvaCom5thGen(mf, __tlvBuff, __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_SET); \
    delete[] __tlvBuff; \
    if (__mRc) { \
        return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    _updated = false; \
    return MCE_SUCCESS

#define GET_DEFAULT_5TH_GEN(mf, tlvStructName, tlvNameStr) \
    MError __mRc; \
    int __tlvBuffSize = tlvStructName##_size(); \
    u_int8_t *__tlvBuff = new u_int8_t[__tlvBuffSize]; \
    memset(__tlvBuff, 0, __tlvBuffSize); \
    struct tlvStructName __tlvStruct; \
    memset(&__tlvStruct, 0, sizeof(__tlvStruct)); \
    __mRc = mnvaCom5thGen(mf, &__tlvBuff[0], __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET, true); \
    if (__mRc) { \
        delete[] __tlvBuff; \
        if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) { \
            return MCE_SUCCESS; \
        } \
        return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]); \
    updateClassDefaultAttrFromTlv((void*)&__tlvStruct); \
    updateClassAttrFromDefaultParams(); \
    delete[] __tlvBuff; \
    return MCE_SUCCESS

#define GET_FROM_DEV_5TH_GEN(mf, tlvStructName, tlvNameStr) \
    MError __mRc; \
    int __tlvBuffSize = tlvStructName##_size(); \
    u_int8_t *__tlvBuff = new u_int8_t[__tlvBuffSize]; \
    memset(__tlvBuff, 0, __tlvBuffSize); \
    struct tlvStructName __tlvStruct; \
    memset(&__tlvStruct, 0, sizeof(__tlvStruct)); \
    if (_updated) { \
        delete[] __tlvBuff; \
        return MCE_SUCCESS; \
    } \
    __mRc = mnvaCom5thGen(mf, &__tlvBuff[0], __tlvBuffSize, getTlvTypeBe(), REG_ACCESS_METHOD_GET); \
    if (__mRc) { \
        delete[] __tlvBuff; \
        if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) { \
            return MCE_SUCCESS; \
        } \
        return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]); \
    updateClassAttrFromTlv((void*)&__tlvStruct); \
    _updated = true; \
    delete[] __tlvBuff; \
    return MCE_SUCCESS

#define SET_ON_DEV_4TH_GEN(mf, ignoreCheck, tlvStructName, tlvNameStr, typeMod) \
    MError __mRc; \
    if (!(ignoreCheck) && !checkCfg()) { \
        return MCE_BAD_PARAMS; \
    } \
    int __tlvBuffSize = tlvStructName##_size(); \
    u_int8_t *__tlvBuff = new u_int8_t[__tlvBuffSize]; \
    memset(__tlvBuff, 0, __tlvBuffSize); \
    struct tlvStructName __tlvStruct; \
    memset(&__tlvStruct, 0, sizeof(__tlvStruct)); \
    __mRc = mnvaCom4thGen(mf, __tlvBuff, __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_GET, typeMod); \
    if (__mRc && __mRc != ME_REG_ACCESS_RES_NOT_AVLBL) { \
        delete[] __tlvBuff; \
        return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    tlvStructName##_unpack(&__tlvStruct, __tlvBuff); \
    updateTlvFromClassAttr((void*)&__tlvStruct); \
    tlvStructName##_pack(&__tlvStruct, __tlvBuff); \
    __mRc = mnvaCom4thGen(mf, __tlvBuff, __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_SET, typeMod); \
    delete[] __tlvBuff; \
    if (__mRc) { \
        return errmsg("failed to set %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    _updated = false; \
    return MCE_SUCCESS

#define GET_FROM_DEV_4TH_GEN(mf, tlvStructName, tlvNameStr, typeMod) \
    MError __mRc; \
    int __tlvBuffSize = tlvStructName##_size(); \
    u_int8_t *__tlvBuff = new u_int8_t[__tlvBuffSize]; \
    memset(__tlvBuff, 0, __tlvBuffSize); \
    struct tlvStructName __tlvStruct; \
    memset(&__tlvStruct, 0, sizeof(__tlvStruct)); \
    if (_updated) { \
        delete[] __tlvBuff; \
        return MCE_SUCCESS; \
    } \
    __mRc = mnvaCom4thGen(mf, &__tlvBuff[0], __tlvBuffSize, tlvTypeIdx, REG_ACCESS_METHOD_GET, typeMod); \
    if (__mRc) { \
        delete[] __tlvBuff; \
        if (__mRc == ME_REG_ACCESS_RES_NOT_AVLBL) { \
            return MCE_SUCCESS; \
        } \
        return errmsg("Failed to get %s settings: %s", tlvNameStr, m_err2str(__mRc)); \
    } \
    tlvStructName##_unpack(&__tlvStruct, &__tlvBuff[0]); \
    updateClassAttrFromTlv((void*)&__tlvStruct); \
    _updated = true; \
    delete[] __tlvBuff; \
    return MCE_SUCCESS


/*static void dealWithSignal()
   {
    int sig;
    sig = mft_signal_is_fired();
    if (sig) {
        // reset received signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        //raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
    return;
   }*/

/*
 * Adrianc: TODO: create a SetTlv class and two child classess , for 4th/5th gen.
 *          each param class will have an instance of SetTlv class
 */

MError mnvaCom4thGen(mfile *mf, u_int8_t *buff, u_int16_t len, u_int16_t tlvTypeIdx, reg_access_method_t method, u_int16_t typeMod)
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

/*MError mnvaCom5thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t tlvType, reg_access_method_t method, bool getDefault=false)
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
    DEBUG_PRINT_RECEIVE(&mnvaTlv, nvda);
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
   }*/

/***************************
* Class implementations :
***************************/

/*
 * CfgParams Class implementation :
 */

CfgParams::CfgParams(mlxCfgType t, u_int32_t tlvT)
{
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

int CfgParams::getDefaultParams4thGen(mfile *mf, struct tools_open_query_def_params_global *global_params)
{
    mft_signal_set_handling(1);
    MError rc  = tcif_query_global_def_params(mf, global_params);
    dealWithSignal();
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int CfgParams::getDefaultParams4thGen(mfile *mf, int port, struct tools_open_query_def_params_per_port *port_params)
{
    mft_signal_set_handling(1);
    MError rc  = tcif_query_per_port_def_params(mf, port, port_params);
    dealWithSignal();
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to get default parameters: %s", tcif_err2str(rc));
    }
    return MCE_SUCCESS;
}

int CfgParams::getDefaultAndFromDev(mfile *mf)
{
    int rc;
    rc = getDefaultParams(mf); CHECK_RC(rc);
    rc = getFromDev(mf); CHECK_RC(rc);
    return MCE_SUCCESS;
}

bool CfgParams::checkCfg(mfile *mf)
{
    if (!_ignoreHardLimits && !hardLimitCheck()) {
        return false;
    }
    if (!_ignoreSoftLimits && !softLimitCheck(mf)) {
        return false;
    }
    return true;
}

bool CfgParams::softLimitCheck(mfile *mf)
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
    if (_ipVer > 3) {
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

bool BootSettingsExtParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
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

int BootSettingsExtParams4thGen::getDefaultParams(mfile *mf)
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

int BootSettingsExtParams4thGen::getFromDev(mfile *mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[TOOLS_OPEN_SRIOV_SIZE];
    struct tools_open_boot_settings_ext bootSettingsExtTlv;
    memset(buff, 0, tools_open_boot_settings_ext_size());
    memset(&bootSettingsExtTlv, 0, sizeof(struct tools_open_boot_settings_ext));
    // pack it
    tools_open_boot_settings_ext_pack(&bootSettingsExtTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&bootSettingsExtTlv, boot_settings_ext);
    rc = mnvaCom4thGen(mf, buff, tools_open_boot_settings_ext_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);
    // check rc
    DEBUG_PRINT_RECEIVE(&bootSettingsExtTlv, boot_settings_ext);
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

int BootSettingsExtParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
{
    if (_ipVer == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for Boot Settings Extras.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[TOOLS_OPEN_BOOT_SETTINGS_EXT_SIZE];
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
        return errmsg("failed to set Boot Settings Extras params: %s", m_err2str(ret));
    }
    _updated = false;
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

bool SriovParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return _devCapVec & SRIOV_MASK;
}

int SriovParams4thGen::getDefaultParams(mfile *mf)
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

int SriovParams4thGen::getFromDev(mfile *mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[TOOLS_OPEN_SRIOV_SIZE];
    struct tools_open_sriov sriovTlv;
    memset(buff, 0, tools_open_sriov_size());
    memset(&sriovTlv, 0, sizeof(struct tools_open_sriov));
    // pack it
    tools_open_sriov_pack(&sriovTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&sriovTlv, sriov);
    rc = mnvaCom4thGen(mf, buff, tools_open_sriov_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, 0);
    // check rc
    DEBUG_PRINT_RECEIVE(&sriovTlv, sriov);
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

int SriovParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
{
    if (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for SRIOV.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[TOOLS_OPEN_SRIOV_SIZE];
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
        return errmsg("failed to set SRIOV params: %s", m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

int SriovParams4thGen::updateMaxVfs(mfile *mf)
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

bool SriovParams4thGen::softLimitCheck(mfile *mf)
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
    double TotalMem = (_numOfVfs + 1) * (1 << barSz); // 1 for physical func

    if ((TotalMem > 512)) {
        unsigned int maxAlowedVfs = static_cast<unsigned int>(512 / (1 << barSz)) - 1;
        errmsg("illegal SRIOV parameter value. Maximal number of VFs: %d", maxAlowedVfs < _maxVfs ? maxAlowedVfs : _maxVfs);
        return false;
    }
    return true;
}


/*
 * CX3GlobalConfParams Class implementation:
 */

bool CX3GlobalConfParams::cfgSupported(mfile *mf, mlxCfgParam param)
{
    (void)param;
    struct tools_open_query_def_params_global params;
    int rc;

    rc = getDefaultParams4thGen(mf, &params);
    if (rc) {
        return false;
    }
    return (param == Mcp_CQ_Timestamp && params.nv_cq_timestamp_supported)
           || (param == Mcp_Steer_ForceVlan && params.nv_steer_force_vlan_supported)
           || (param == Mcp_Phy_Param_Mode && params.nv_config_phy_param_mode)
           || (param == Mcp_Last &&
               (params.nv_cq_timestamp_supported || params.nv_steer_force_vlan_supported || params.nv_config_phy_param_mode));
}

void CX3GlobalConfParams::setParam(mlxCfgParam paramType, u_int32_t val)
{
    if (paramType == Mcp_Phy_Param_Mode) {
        _phyParamMode = val;
    }

    if (paramType == Mcp_CQ_Timestamp) {
        _timestamp = val;
    }

    if (paramType == Mcp_Steer_ForceVlan) {
        _steerForceVlan = val;
    }
}

u_int32_t CX3GlobalConfParams::getParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Phy_Param_Mode) {
        return _phyParamMode;
    }

    if (paramType == Mcp_CQ_Timestamp) {
        return _timestamp;
    }

    if (paramType == Mcp_Steer_ForceVlan) {
        return _steerForceVlan;
    }

    return MLXCFG_UNKNOWN;
}

u_int32_t CX3GlobalConfParams::getDefaultParam(mlxCfgParam paramType)
{
    if (paramType == Mcp_Phy_Param_Mode) {
        return _phyParamModeDefault;
    }

    if (paramType == Mcp_CQ_Timestamp) {
        return _timestampDefault;
    }

    if (paramType == Mcp_Steer_ForceVlan) {
        return _steerForceVlanDefault;
    }

    return MLXCFG_UNKNOWN;
}

int CX3GlobalConfParams::getFromDev(mfile *mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[TOOLS_OPEN_NV_CX3_GLOBAL_CONF_SIZE];
    struct tools_open_nv_cx3_global_conf globalConfTlv;
    memset(buff, 0, tools_open_nv_cx3_global_conf_size());
    memset(&globalConfTlv, 0, sizeof(struct tools_open_nv_cx3_global_conf));
    // pack it
    tools_open_nv_cx3_global_conf_pack(&globalConfTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&globalConfTlv, nv_cx3_global_conf);
    rc = mnvaCom4thGen(mf, buff, tools_open_nv_cx3_global_conf_size(), tlvTypeIdx, REG_ACCESS_METHOD_GET, 0);
    // check rc
    DEBUG_PRINT_RECEIVE(&globalConfTlv, nv_cx3_global_conf);
    if (rc) {// when attempting to get a nv_cfg tlv from device ME_REG_ACCESS_RES_NOT_AVLBL means - no valid
             // tlv found. i.e default configuration are on.
        if (rc == ME_REG_ACCESS_RES_NOT_AVLBL) {
            return MCE_SUCCESS;
        }
        return errmsg(MCE_BAD_STATUS, "Failed to get CX3_GLOBAL_CONF configuration: %s", m_err2str(rc));
    }
    // unpack and update
    tools_open_nv_cx3_global_conf_unpack(&globalConfTlv, buff);
    setParams(globalConfTlv.cq_timestamp, globalConfTlv.steer_force_vlan, globalConfTlv.phy_param_mode);
    _updated = true;

    return MCE_SUCCESS;
}

int CX3GlobalConfParams::setOnDev(mfile *mf, bool ignoreCheck)
{
    if (_timestamp == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for CX3_GLOBAL_CONF.", err() ? err() : "");
    }
    if (_steerForceVlan == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for CX3_GLOBAL_CONF.", err() ? err() : "");
    }
    if (_phyParamMode == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all parameters for CX3_GLOBAL_CONF.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[TOOLS_OPEN_NV_CX3_GLOBAL_CONF_SIZE];
    struct tools_open_nv_cx3_global_conf globalConfTlv;
    memset(buff, 0, tools_open_nv_cx3_global_conf_size());
    memset(&globalConfTlv, 0, sizeof(struct tools_open_nv_cx3_global_conf));
    globalConfTlv.phy_param_mode = _phyParamMode;
    globalConfTlv.cq_timestamp = _timestamp;
    globalConfTlv.steer_force_vlan = _steerForceVlan;
    // pack it
    tools_open_nv_cx3_global_conf_pack(&globalConfTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_nv_cx3_global_conf_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set CX3_GLOBAL_CONF params: %s", m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

int CX3GlobalConfParams::getDefaultParams(mfile *mf)
{
    struct tools_open_query_def_params_global global_params;
    int rc;

    rc = getDefaultParams4thGen(mf, &global_params);
    if (rc) {
        return MCE_GET_DEFAULT_PARAMS;
    }
    _phyParamModeDefault = global_params.default_phy_param_mode;
    _timestampDefault = global_params.default_cq_timestamp;
    _steerForceVlanDefault = global_params.default_steer_force_vlan;
    setParams(_timestampDefault, _steerForceVlanDefault, _phyParamModeDefault);
    return MCE_SUCCESS;
}

bool CX3GlobalConfParams::hardLimitCheck()
{
    if (_timestamp != 0 && _timestamp != 1) {
        errmsg("illegal CQ_TIMESTAMP parameter value. (should be 0 or 1)");
        return false;
    }

    if (_steerForceVlan != 0 && _steerForceVlan != 1) {
        errmsg("illegal STEER_FORCE_VLAN parameter value. (should be 0 or 1)");
        return false;
    }

    if (_phyParamMode != 0 && _phyParamMode != 1 && _phyParamMode != 2) {
        errmsg("illegal PHY_PARAMETER_MODE parameter value. (should be 0, 1 or 2)");
        return false;
    }

    return true;
}

void CX3GlobalConfParams::setParams(u_int32_t timestamp, u_int32_t steer_force_vlan, u_int32_t phy_param_mode)
{
    _phyParamMode = phy_param_mode;
    _timestamp = timestamp;
    _steerForceVlan = steer_force_vlan;
}



/*
 * WolParams Class implementation :
 */

bool WolParams::hardLimitCheck()
{
    if (_wolMagicEn == 0 || _wolMagicEn == 1) {
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

bool WolParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return ((_devCapVec & WOL_P1_MASK) && _port == 1) || ((_devCapVec & WOL_P2_MASK) && _port == 2 );
}

int WolParams4thGen::getDefaultParams(mfile *mf)
{
    struct tools_open_query_def_params_per_port port_params;
    int rc = getDefaultParams4thGen(mf, _port, &port_params);
    if (rc == MCE_SUCCESS) {
        _wolMagicEnDefault = port_params.default_en_wol_magic;
        setParams(_wolMagicEnDefault);
    } else {
        rc = MCE_GET_DEFAULT_PARAMS;
    }
    return rc;
}

int WolParams4thGen::getFromDev(mfile *mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[TOOLS_OPEN_WOL_SIZE];
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

int WolParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
{
    if (_wolMagicEn == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for WOL.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    // prep tlv
    MError ret;
    u_int8_t buff[TOOLS_OPEN_WOL_SIZE];
    struct tools_open_wol wolTlv;

    memset(buff, 0, tools_open_wol_size());
    memset(&wolTlv, 0, sizeof(struct tools_open_wol));

    wolTlv.en_wol_magic = _wolMagicEn;
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
    if (_logBarSz > _maxLogBarSz) {
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

bool BarSzParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    return _devCapVec & BAR_SZ_MASK;
}

int BarSzParams4thGen::getDefaultParams(mfile *mf)
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

int BarSzParams4thGen::getDefaultBarSz(mfile *mf)
{
    u_int64_t data = 0;
    MError rc = tcif_query_dev_cap(mf, MAX_BAR_SZ_ADDR, &data);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to query device capabilities. %s", tcif_err2str(rc));
    }

    _maxLogBarSz = EXTRACT64(data, 3, 6);

    rc = tcif_query_dev_cap(mf, DEFAULT_BAR_SZ_ADDR, &data);
    if (rc) {
        return errmsg(MCE_BAD_STATUS, "Failed to query device capabilities. %s", tcif_err2str(rc));
    }

    _logBarSzDefault = EXTRACT64(data, 16, 6) + 1; //adrianc: this field reports only half of the bar size (i.e without the blue flame)
    setParams(_logBarSzDefault);
    return MCE_SUCCESS;
}

int BarSzParams4thGen::getFromDev(mfile *mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    MError rc;
    // prep tlv
    u_int8_t buff[TOOLS_OPEN_BAR_SIZE_SIZE];
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

int BarSzParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
{
    if (_logBarSz == MLXCFG_UNKNOWN) {
        return errmsg("%s please specify all the parameters for BAR size.", err() ? err() : "");
    }

    if (!ignoreCheck && !checkCfg(mf)) {
        return MCE_BAD_PARAMS;
    }

    // prep tlv
    MError ret;
    u_int8_t buff[TOOLS_OPEN_BAR_SIZE_SIZE];
    struct tools_open_bar_size barSzTlv;

    memset(buff, 0, tools_open_bar_size_size());
    memset(&barSzTlv, 0, sizeof(struct tools_open_bar_size));

    barSzTlv.log_uar_bar_size = _logBarSz;
    // pack it
    tools_open_bar_size_pack(&barSzTlv, buff);
    // send it
    ret = mnvaCom4thGen(mf, buff, tools_open_bar_size_size(), tlvTypeIdx, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (ret) {
        return errmsg("failed to set BAR size params: %s", m_err2str(ret));
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool BarSzParams4thGen::softLimitCheck(mfile *mf)
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

    if (numOfVfs == MLXCFG_UNKNOWN || numOfVfs == MLXCFG_UNKNOWN) {
        errmsg("Illegal SRIOV parameters values");
        return false;
    }

    if (sriovEn == 0) {
        return true;
    }
    // this is the default log2 bar size , we require numOfVfs*(2^log_uar_bar) <= 512 or else the node might not boot
    double TotalMem = (numOfVfs + 1) * (1 << _logBarSz);
    //printf("-D- num_of_vfs*2^(bar_sz+1) = %d*2^%ld = %d\n", _numOfVfs, data, (int)(_numOfVfs*(std::pow((double)2, (int)data))));
    //printf("-D- maxVfs(default set by fw) : %d\n", _maxVfs);

    if (TotalMem > 512) {
        unsigned int maxAlowedLogBarSz = static_cast<unsigned int>(log2((512 / (numOfVfs + 1 ))));
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
    setParams(_vpiTlv.network_link_type, _vpiTlv.default_link_type,
              _vpiTlv.phy_type, _vpiTlv.xfi_mode, _vpiTlv.force_mode);
    _updated = true;
    return MCE_SUCCESS;

}

void VpiParams::setParams(u_int32_t linkType, u_int32_t defaultLinkType,
                          u_int32_t phyType, u_int32_t xfiMode, u_int32_t forceMode)
{
    _linkType = linkType;
    _defaultLinkType = defaultLinkType;
    _phyType = phyType;
    _xfiMode = xfiMode;
    _forceMode = forceMode;
}

int VpiParams::setOnDevComPre(bool ignoreCheck)
{
    if (_isVPISupported && (_linkType == MLXCFG_UNKNOWN || _defaultLinkType == MLXCFG_UNKNOWN)) {
        return errmsg("%s please specify all the parameters for VPI settings.", err() ? err() : "");
    }
    if (_isForceModeSupported && (_phyType == MLXCFG_UNKNOWN || _xfiMode == MLXCFG_UNKNOWN || _forceMode == MLXCFG_UNKNOWN)) {
        return errmsg("%s please specify all the parameters for VPI Force Mode settings.", err() ? err() : "");
    }
    if (!ignoreCheck && !checkCfg()) {
        return MCE_BAD_PARAMS;
    }
    _tlvBuff.resize(TOOLS_OPEN_VPI_SETTINGS_SIZE);
    memset(&_tlvBuff[0], 0, _tlvBuff.size());
    memset(&_vpiTlv, 0, sizeof(struct tools_open_vpi_settings));
    _vpiTlv.network_link_type = _linkType;
    _vpiTlv.default_link_type = _defaultLinkType;
    _vpiTlv.phy_type = _phyType;
    _vpiTlv.xfi_mode = _xfiMode;
    _vpiTlv.force_mode = _forceMode;
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
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2)) {
        _linkType = val;
    } else if ((paramType == Mcp_Phy_Type_P1 && _port == 1) || (paramType == Mcp_Phy_Type_P2 && _port == 2)) {
        _phyType = val;
    } else if ((paramType == Mcp_Xfi_Mode_P1 && _port == 1) || (paramType == Mcp_Xfi_Mode_P2 && _port == 2)) {
        _xfiMode = val;
    } else if ((paramType == Mcp_Force_Mode_P1 && _port == 1) || (paramType == Mcp_Force_Mode_P2 && _port == 2)) {
        _forceMode = val;
    }
}

u_int32_t VpiParams4thGen::getParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _linkType;
    } else if ((paramType == Mcp_Phy_Type_P1 && _port == 1) || (paramType == Mcp_Phy_Type_P2 && _port == 2)) {
        return _phyType;
    } else if ((paramType == Mcp_Xfi_Mode_P1 && _port == 1) || (paramType == Mcp_Xfi_Mode_P2 && _port == 2)) {
        return _xfiMode;
    } else if ((paramType == Mcp_Force_Mode_P1 && _port == 1) || (paramType == Mcp_Force_Mode_P2 && _port == 2)) {
        return _forceMode;
    }
    return MLXCFG_UNKNOWN;
}

u_int32_t VpiParams4thGen::getDefaultParam(mlxCfgParam paramType)
{
    if ((paramType == Mcp_Link_Type_P1 && _port == 1 ) || (paramType == Mcp_Link_Type_P2 && _port == 2) ) {
        return _linkTypeDefault;
    } else if ((paramType == Mcp_Phy_Type_P1 && _port == 1) || (paramType == Mcp_Phy_Type_P2 && _port == 2)) {
        return _phyTypeDefault;
    } else if ((paramType == Mcp_Xfi_Mode_P1 && _port == 1) || (paramType == Mcp_Xfi_Mode_P2 && _port == 2)) {
        return _xfiModeDefault;
    } else if ((paramType == Mcp_Force_Mode_P1 && _port == 1) || (paramType == Mcp_Force_Mode_P2 && _port == 2)) {
        return _forceModeDefault;
    }
    return MLXCFG_UNKNOWN;
}

int VpiParams4thGen::getDefaultParamsAux(mfile *mf)
{
    struct tools_open_query_def_params_per_port port_params;
    memset(&port_params, 0, sizeof(port_params));
    _defaultLinkTypeDefault = 0; // not used for 4th gen devices , we give it a default value
    int rc = getDefaultParams4thGen(mf, _port, &port_params);
    if (rc) {
        return MCE_GET_DEFAULT_PARAMS;
    }
    if (port_params.default_network_link_type) {
        _linkTypeDefault = port_params.default_network_link_type;
    }
    _isForceModeSupported = port_params.nv_config_vpi_force_mode;
    _phyTypeDefault = port_params.default_vpi_phy_type;
    _xfiModeDefault = port_params.default_vpi_xfi_mode;
    _forceModeDefault = port_params.default_vpi_force_mode;

    return MCE_SUCCESS;
}

bool VpiParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
{
    (void)mf;
    (void)param;
    int rc;

    if (((param == Mcp_Phy_Type_P1 || param == Mcp_Xfi_Mode_P1 || param == Mcp_Force_Mode_P1) && (_port == 1))
        ||
        ((param == Mcp_Phy_Type_P2 || param == Mcp_Xfi_Mode_P2 || param == Mcp_Force_Mode_P2) && (_port == 2))) {
        rc = getDefaultParamsAux(mf);
        bool x = ((!rc) && _isForceModeSupported);
        return x;
    }

    _isVPISupported = ((_devCapVec & VPI_P1_MASK) && _port == 1) || ((_devCapVec & VPI_P2_MASK) && _port == 2);

    if (param == Mcp_Last) {
        rc = getDefaultParamsAux(mf);
        bool x = ((!rc) && _isForceModeSupported);
        return (x || _isVPISupported);
    }
    return _isVPISupported;
}

int VpiParams4thGen::getDefaultParams(mfile *mf)
{

    int rc = getDefaultParamsAux(mf);
    if (rc) {
        return rc;
    }

    _linkType = _linkTypeDefault;
    _defaultLinkType = _defaultLinkTypeDefault;
    _phyType = _phyTypeDefault;
    _xfiMode = _xfiModeDefault;
    _forceMode = _forceModeDefault;

    return MCE_SUCCESS;
}

int VpiParams4thGen::getFromDev(mfile *mf)
{
    MError mRc;
    int rc;

    if (_updated) {
        return MCE_SUCCESS;
    }
    if ((rc = getFromDevComPre())) {
        return rc;
    }
    mRc = mnvaCom4thGen(mf, &_tlvBuff[0], TOOLS_OPEN_VPI_SETTINGS_SIZE, tlvTypeIdx, REG_ACCESS_METHOD_GET, _port);
    return getFromDevComPost(mRc);
}

int VpiParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
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

    if (_isVPISupported) {
        if (_linkType < 1 || _linkType > 3) {
            errmsg("illegal VPI link type (should be 1|2|3).");
            return false;
        }
    }

    if (_isForceModeSupported) {
        if (_phyType < 1 || _phyType > 3) {
            errmsg("illegal Phy Type value (shold be 1|2|3)");
            return false;
        }

        if (_xfiMode > 2) {
            errmsg("illegal Xfi Mode value (should be 0|1|2)");
            return false;
        }

        if (_forceMode > 1) {
            errmsg("illegal Force Mode value (should be 0|1)");
            return false;
        }
    }

    return true;
}

/*
 * InfinibandBootSettingsParams4thGen Class implementation:
 */

bool InfinibandBootSettingsParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
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


int InfinibandBootSettingsParams4thGen::getFromDev(mfile *mf)
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
int InfinibandBootSettingsParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
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

int InfinibandBootSettingsParams4thGen::getDefaultParams(mfile *mf)
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
 * PrebootBootSettingsParams4thGen Class implementation:
 */

bool PrebootBootSettingsParams4thGen::cfgSupported(mfile *mf, mlxCfgParam param)
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

int PrebootBootSettingsParams4thGen::getFromDev(mfile *mf)
{
    GET_FROM_DEV_4TH_GEN(mf, tools_open_preboot_boot_settings, "Preboot Boot Settings", _port);
}

int PrebootBootSettingsParams4thGen::setOnDev(mfile *mf, bool ignoreCheck)
{
    SET_ON_DEV_4TH_GEN(mf, ignoreCheck, tools_open_preboot_boot_settings, "Preboot Boot Settings", _port);
}

void PrebootBootSettingsParams4thGen::updateTlvFromClassAttr(void *tlv)
{

    struct tools_open_preboot_boot_settings *prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    prebootTlv->boot_option_rom_en = _bootOptionRomEn;
    prebootTlv->boot_vlan_en = _bootVlanEn;
    prebootTlv->boot_retry_count = _bootRetryCnt;
    prebootTlv->legacy_boot_protocol = _legacyBootProtocol;
    prebootTlv->boot_vlan = _bootVlan;

}

void PrebootBootSettingsParams4thGen::updateClassAttrFromTlv(void *tlv)
{
    struct tools_open_preboot_boot_settings *prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    _bootOptionRomEn = prebootTlv->boot_option_rom_en;
    _bootVlanEn = prebootTlv->boot_vlan_en;
    _bootRetryCnt = prebootTlv->boot_retry_count;
    _legacyBootProtocol = prebootTlv->legacy_boot_protocol;
    _bootVlan = prebootTlv->boot_vlan;
}

void PrebootBootSettingsParams4thGen::updateClassDefaultAttrFromTlv(void *tlv)
{
    struct tools_open_preboot_boot_settings *prebootTlv = (struct tools_open_preboot_boot_settings*)tlv;
    _bootOptionRomEnDefault = prebootTlv->boot_option_rom_en;
    _bootVlanEnDefault = prebootTlv->boot_vlan_en;
    _bootRetryCntDefault = prebootTlv->boot_retry_count;
    _legacyBootProtocolDefault = prebootTlv->legacy_boot_protocol;
    _bootVlanDefault = prebootTlv->boot_vlan;
}

int PrebootBootSettingsParams4thGen::getDefaultParams(mfile *mf)
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




