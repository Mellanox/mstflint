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


#include <set>
#include <cmath>
#include <signal.h>

#include <mft_sig_handler.h>
#include <tools_layouts/tools_layouts.h>
#include <reg_access/reg_access.h>
#include <bit_slice.h>

#include "mlxcfg_lib.h"


#define SRIOV_MASK 0x1
#define WOL_P1_MASK 0x2
#define WOL_P2_MASK 0x4
#define VPI_P1_MASK 0x8
#define VPI_P2_MASK 0x10

#define TOOL_CAP_BITS_ADDR 0xc0
#define MAX_VFS_ADDR 0x38
#define DEFAULT_BAR_SZ_ADDR 0x48

// for debug:
#ifdef _ENABLE_DEBUG_
# define DEBUG_PRINT_SEND(data_struct, struct_name)\
    printf("-I- Data Sent:\n");\
    tools_##struct_name##_print(data_struct, stdout, 1)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)\
    printf("-I- Data Recieved:\n");\
    tools_##struct_name##_print(data_struct, stdout, 1)
#else
# define DEBUG_PRINT_SEND(data_struct, struct_name)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)
#endif


using namespace std;

static McStatus translateRc(MError rc);
static McStatus mnvaCom(mfile* mf, u_int8_t* buff, u_int16_t len, u_int16_t type, reg_access_method_t method, u_int16_t typeMod=0);

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


McStatus MlxCfgOps::SriovParams::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    McStatus rc;
    // prep tlv
    u_int8_t buff[tools_sriov_size()];
    struct tools_sriov sriovTlv;
    memset(buff, 0, tools_sriov_size());
    memset(&sriovTlv, 0, sizeof(struct tools_sriov));
    // pack it
    tools_sriov_pack(&sriovTlv, buff);
    // send it
    DEBUG_PRINT_SEND(&sriovTlv, sriov);
    rc = mnvaCom(mf, buff, tools_sriov_size(), tlvType, REG_ACCESS_METHOD_GET, 0);
    // check rc
    DEBUG_PRINT_RECIEVE(&sriovTlv, sriov);
    if (rc) {
        return rc;
    }
    // unpack and update
    tools_sriov_unpack(&sriovTlv, buff);
    _sriovEn = _sriovEn == MLXCFG_UNKNOWN ? sriovTlv.sriov_en : _sriovEn ;
    _numOfVfs = _numOfVfs == MLXCFG_UNKNOWN ? sriovTlv.total_vfs : _numOfVfs ;
    _updated = true;

    return MCE_SUCCESS;
}

McStatus MlxCfgOps::SriovParams::setOnDev(mfile* mf)
{
    McStatus rc;
    if (_sriovEn == MLXCFG_UNKNOWN || _numOfVfs == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc) {
            if (rc == MCE_RES_NOT_AVAIL) {
                return MCE_INCOMPLETE_PARAMS;
            }
            return rc;
        }
    }
    if (!isLegal(mf)) {
        return MCE_BAD_PARAM_VAL;
    }
    // prep tlv
    u_int8_t buff[tools_sriov_size()];
    struct tools_sriov sriovTlv;

    memset(buff, 0, tools_sriov_size());
    memset(&sriovTlv, 0, sizeof(struct tools_sriov));

    sriovTlv.sriov_en = _sriovEn;
    sriovTlv.total_vfs = _numOfVfs;
    // pack it
    tools_sriov_pack(&sriovTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_sriov_size(), tlvType, REG_ACCESS_METHOD_SET, 0);
    // check rc
    if (rc) {
        return rc;
    }
    _updated = false;
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::SriovParams::updateMaxVfs(mfile* mf)
{
    u_int64_t data = 0;
    int rc = tools_cmdif_query_dev_cap(mf, MAX_VFS_ADDR, &data);
    if (rc) {
        return translateRc((MError)rc);
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
        return translateRc((MError)rc);
    }
    data = EXTRACT64(data,16,6) + 1; // this is the default log2 bar size , we require numOfVfs*(2^log_uar_bar) <= 512 or else the node might not boot
    //TODO: when bar_size tlv will be supported, we need to change this to the current bar_size (and also check with the current tlv bar size)
    //printf("-D- num_of_vfs*2^(bar_sz+1) = %d*2^%ld = %d\n", _numOfVfs, data, (int)(_numOfVfs*std::pow((double)2, (int)data)));
    return ((_sriovEn == 0 || _sriovEn == 1 ) && (_numOfVfs <= _maxVfs) && (_numOfVfs*(std::pow((double)2, (int)data)) <= 512));
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

McStatus MlxCfgOps::WolParams::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    McStatus rc;
    // prep tlv
    u_int8_t buff[tools_wol_size()];
    struct tools_wol wolTlv;
    memset(buff, 0, tools_wol_size());
    memset(&wolTlv, 0, sizeof(struct tools_wol));
    // pack it
    tools_wol_pack(&wolTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_wol_size(), tlvType, REG_ACCESS_METHOD_GET, _port);
    // check rc
    if (rc) {
        return rc;
    }
    // unpack and update
    tools_wol_unpack(&wolTlv, buff);
    _wolMagicEn = _wolMagicEn == MLXCFG_UNKNOWN ? wolTlv.en_wol_magic : _wolMagicEn ;
    _updated = true;

    return MCE_SUCCESS;
}

McStatus MlxCfgOps::WolParams::setOnDev(mfile* mf)
{
    McStatus rc;
    if (_wolMagicEn == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc) {
            if (rc == MCE_RES_NOT_AVAIL) {
                return MCE_INCOMPLETE_PARAMS;
            }
            return rc;
        }
    }
    if (!isLegal()) {
        return MCE_BAD_PARAM_VAL;
    }

    // prep tlv
    u_int8_t buff[tools_wol_size()];
    struct tools_wol wolTlv;

    memset(buff, 0, tools_wol_size());
    memset(&wolTlv, 0, sizeof(struct tools_wol));

    wolTlv.en_wol_magic= _wolMagicEn;
    // pack it
    tools_wol_pack(&wolTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_wol_size(), tlvType, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (rc) {
        return rc;
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool MlxCfgOps::WolParams::isLegal(mfile* mf)
{
    (void)mf;
    return (_wolMagicEn == 0 || _wolMagicEn == 1 );
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

McStatus MlxCfgOps::VpiParams::getFromDev(mfile* mf)
{
    if (_updated) {
        return MCE_SUCCESS;
    }
    McStatus rc;
    // prep tlv
    u_int8_t buff[tools_vpi_settings_size()];
    struct tools_vpi_settings vpiTlv;
    memset(buff, 0, tools_vpi_settings_size());
    memset(&vpiTlv, 0, sizeof(struct tools_vpi_settings));
    // pack it
    tools_vpi_settings_pack(&vpiTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_vpi_settings_size(), tlvType, REG_ACCESS_METHOD_GET, _port);
    // check rc
    if (rc) {
        return rc;
    }
    // unpack and update
    tools_vpi_settings_unpack(&vpiTlv, buff);
    _linkType = _linkType == MLXCFG_UNKNOWN ? vpiTlv.network_link_type : _linkType ;
    _updated = true;

    return MCE_SUCCESS;
}

McStatus MlxCfgOps::VpiParams::setOnDev(mfile* mf)
{
    McStatus rc;
    if (_linkType == MLXCFG_UNKNOWN) {
        rc = getFromDev(mf);
        if (rc) {
            if (rc == MCE_RES_NOT_AVAIL) {
                return MCE_INCOMPLETE_PARAMS;
            }
            return rc;
        }
    }
    if (!isLegal()) {
        return MCE_BAD_PARAM_VAL;
    }

    // prep tlv
    u_int8_t buff[tools_vpi_settings_size()];
    struct tools_vpi_settings vpiTlv;

    memset(buff, 0, tools_vpi_settings_size());
    memset(&vpiTlv, 0, sizeof(struct tools_vpi_settings));

    vpiTlv.network_link_type= _linkType;
    // pack it
    tools_vpi_settings_pack(&vpiTlv, buff);
    // send it
    rc = mnvaCom(mf, buff, tools_vpi_settings_size(), tlvType, REG_ACCESS_METHOD_SET, _port);
    // check rc
    if (rc) {
        return rc;
    }
    _updated = false;
    return MCE_SUCCESS;
}

bool MlxCfgOps::VpiParams::isLegal(mfile* mf)
{
    (void)mf;
    return (_linkType == 1 || _linkType == 2 || _linkType == 3 );
}

/*
 * MlxCfgOps implementation
 */

MlxCfgOps::MlxCfgOps()
{
    _mf = NULL;
    _suppVec = 0;
    _cfgList.resize(Mct_Last);
    _cfgList[Mct_Sriov] = new SriovParams();
    _cfgList[Mct_Wol_P1] = new WolParams(1);
    _cfgList[Mct_Wol_P2] = new WolParams(2);
    _cfgList[Mct_Vpi_P1] = new VpiParams(1);
    _cfgList[Mct_Vpi_P2] = new VpiParams(2);
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

McStatus MlxCfgOps::supportsToolsHCR()
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
                return MCE_PCICONF;
            }
        #else
            if (type != MTCR_ACCESS_CONFIG) {
                return MCE_PCICONF;
            }
        #endif
            // check if we support tools_hcr
             rc = tools_cmdif_query_dev_cap(_mf, TOOL_CAP_BITS_ADDR, &_suppVec);
             switch (rc) {
             case ME_OK:
                 return MCE_SUCCESS;
             case ME_CMDIF_BAD_SYS:
                 return MCE_DRIVER_DOWN;
             case ME_CMDIF_BAD_OP:
             case ME_CMDIF_TOUT:
             case ME_CMDIF_BUSY:
                 return MCE_TOOLS_HCR_NOT_SUPP;
             default:
                 return MCE_UNKNOWN_ERR;
             }
             break;
         default:
             break;
         }
    return MCE_UNSUPPORTED_DEVICE;
}

McStatus MlxCfgOps::openComChk()
{
    McStatus rc;
    // check if we support Tools HCR
    rc = supportsToolsHCR();
    if (rc) {
        return rc;
    }
    // update cfg specific info.
    // TODO: change all configuration specific to updateInfo() as a virtual function in the base class and call that on all Cfg classes
    // update max Vfs
    if (supportsCfg(Mct_Sriov)) {
        McStatus rc = static_cast<SriovParams*>(_cfgList[Mct_Sriov])->updateMaxVfs(_mf);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::open(const char* devStr)
{
    _mf = mopen(devStr);
    if (_mf == NULL) {
        return MCE_OPEN_DEVICE;
    }

    return openComChk();
}

McStatus MlxCfgOps::opend(mfile* mf)
{
    if (!mf) {
        return MCE_BAD_PARAMS;
    }
    _mf = mf;
    return openComChk();
}

// TODO: implement
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

McStatus MlxCfgOps::getCfg(mlxCfgParam cfgParam, u_int32_t& val)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }
    McStatus rc = _cfgList[cfgParam2Type(cfgParam)]->getFromDev(_mf);
    if (rc) {
        return rc;
    }
    val = (_cfgList[cfgParam2Type(cfgParam)])->getParam(cfgParam);
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::getCfg(std::vector<cfgInfo>& infoVec)
{
    for (std::vector<cfgInfo>::iterator it = infoVec.begin() ; it != infoVec.end(); it++) {
        McStatus rc = getCfg(it->first,it->second);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::setCfg(mlxCfgParam cfgParam, u_int32_t val)
{
    if (!isLegal(cfgParam)) {
        return MCE_BAD_PARAMS;
    }
    _cfgList[cfgParam2Type(cfgParam)]->setParam(cfgParam, val);
    McStatus rc = _cfgList[cfgParam2Type(cfgParam)]->setOnDev(_mf);
    if (rc) {
        return rc;
    }
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::setCfg(const std::vector<cfgInfo>& infoVec)
{
    // set params
    std::set<CfgParams*> CfgToSet;

    for (std::vector<cfgInfo>::const_iterator it = infoVec.begin() ; it != infoVec.end(); it++) {
        if (!isLegal(it->first)) {
            return MCE_BAD_PARAMS;
        }
        if (!supportsParam(it->first)) {
            return MCE_UNSUPPORTED_CFG;
        }
        _cfgList[cfgParam2Type(it->first)]->setParam(it->first, it->second);
        CfgToSet.insert(_cfgList[cfgParam2Type(it->first)]);
    }
    //set on device exit on first failure
    for (std::set<CfgParams*>::iterator it = CfgToSet.begin() ; it != CfgToSet.end(); it++) {
        McStatus rc = (*it)->setOnDev(_mf);
        if (rc) {
            return rc;
        }
    }
    return MCE_SUCCESS;
}

McStatus MlxCfgOps::invalidateCfgs()
{

    struct tools_mnvia mnviaTlv;
    u_int8_t buffer[tools_mnvia_size()];
    memset(&mnviaTlv, 0, sizeof(struct tools_mnvia));
    memset(buffer, 0, tools_mnvia_size());

    mnviaTlv.mnv_hdr.length = 0;
    mnviaTlv.mnv_hdr.type = 0;
    mnviaTlv.mnv_hdr.type_mod = 0;
    tools_mnvia_pack(&mnviaTlv, buffer);
    MError rc;
    rc = reg_access_mnvia(_mf, REG_ACCESS_METHOD_SET, &mnviaTlv);
    return translateRc(rc);
}

bool MlxCfgOps::isLegal(mlxCfgType cfg)
{
    return (cfg >= Mct_Sriov && cfg < Mct_Last) ;
}

bool MlxCfgOps::isLegal(mlxCfgParam cfg)
{
    return (cfg >= Mcp_Sriov_En && cfg < Mcp_Last) ;
}

u_int64_t MlxCfgOps::cfgSuppMask[Mct_Last] = {SRIOV_MASK, WOL_P1_MASK, WOL_P2_MASK , VPI_P1_MASK, VPI_P2_MASK};

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
    default :
            return Mct_Last;
    }
}

const char* MlxCfgOps::err2str(McStatus rc)
{
    switch (rc) {
    case MCE_TLV_NOT_FOUND:
        return "Configuration not found.";
    case MCE_TLV_NOT_SUPP:
        return "The Configuration Tlv is not supported.";
    case MCE_NVCFG_NOT_SUPP:
    case MCE_REG_NOT_SUPP:
        return "Fw does not support NV access registers.";
    case MCE_TOOLS_HCR_NOT_SUPP:
        return "Unsupported FW (version 2.31.5000 or above required for CX3/PRO)";
    case MCE_UNSUPPORTED_CFG:
        return "Fw does not support configuration.";
    case MCE_UNSUPPORTED_DEVICE:
        return "Device not supported.";
    case MCE_BAD_PARAMS:
        return "Bad Parameters.";
    case MCE_BAD_PARAM_VAL:
        return "Illegal parameter value.";
    case MCE_FAILED:
    case MCE_BAD_STATUS:
    case MCE_CR_ERROR:
        return "General Failure";
    case MCE_NOT_IMPLEMENTED:
        return "Not implemented.";
    case MCE_DEV_BUSY:
        return "Device busy.";
    case MCE_UNKNOWN_TLV:
        return "Unknown Tlv.";
    case MCE_RES_NOT_AVAIL:
        return "Resource not available";
    case MCE_CONF_CORRUPT:
        return "Configuration is corrupted.";
    case MCE_BAD_CONFIG:
        return "bad configuration.";
    case MCE_ERASE_EXEEDED:
        return "Erase exceeded flash spec.";
    case MCE_BAD_OP:
        return "Bad Operation.";
    case MCE_DRIVER_DOWN:
        return "Cannot perform operation, Driver might be down.";
    case MCE_INCOMPLETE_PARAMS: // HACK: atm SRIOV is the only configuration that might recv this error
        return "Failed to get missing configuration from device, please specify all the needed parameters for SRIOV.";
    case MCE_OPEN_DEVICE:
        return "Failed to open device.";
    case MCE_PCICONF:
        return "Access to device should be through configuration cycles only.";

    default:
        return "General Error.";
    }
}

McStatus translateRc(MError rc) {
    switch (rc) {
    case ME_OK:
        return MCE_SUCCESS;
    case ME_REG_ACCESS_DEV_BUSY:
    case ME_SEM_LOCKED:
        return MCE_DEV_BUSY;
    case ME_REG_ACCESS_UNKNOWN_TLV:
        return MCE_UNKNOWN_TLV;
    case ME_REG_ACCESS_REG_NOT_SUPP:
        return MCE_REG_NOT_SUPP;
    case ME_REG_ACCESS_METHOD_NOT_SUPP:
        return MCE_METHOD_NOT_SUPP;
    case ME_REG_ACCESS_BAD_PARAM:
    case ME_BAD_PARAMS:
        return MCE_BAD_PARAMS;
    case ME_REG_ACCESS_RES_NOT_AVLBL:
        return MCE_RES_NOT_AVAIL;
    case ME_REG_ACCESS_CONF_CORRUPT:
        return MCE_CONF_CORRUPT;
    case ME_REG_ACCESS_LEN_TOO_SMALL:
        return MCE_TLV_LEN_TOO_SMALL;
    case ME_REG_ACCESS_BAD_CONFIG:
        return MCE_BAD_CONFIG;
    case ME_REG_ACCESS_ERASE_EXEEDED:
        return MCE_ERASE_EXEEDED;
    case ME_CMDIF_BAD_OP:
        return MCE_BAD_OP;
    case ME_CMDIF_BAD_STATUS:
        return MCE_BAD_STATUS;
    case ME_CR_ERROR:
        return MCE_CR_ERROR;

    default:
        return MCE_UNKNOWN_ERR;
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

McStatus mnvaCom(mfile* mf, u_int8_t* buff, u_int16_t len, u_int16_t type, reg_access_method_t method, u_int16_t typeMod)
{
    struct tools_mnva mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_mnva));

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
        return translateRc(rc);
    }
    memcpy(buff, mnvaTlv.data, len);
    return MCE_SUCCESS;
}

