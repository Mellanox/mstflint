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
/*
 * fw_comps_mgr.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: adham
 */

#include "fw_comps_mgr.h"
#include "fw_comps_mgr_abstract_access.h"
#include "bit_slice.h"
#include <signal.h>

#include "mflash/mflash_access_layer.h"
#ifndef UEFI_BUILD
#include <mft_sig_handler.h>
#include "mad_ifc/mad_ifc.h"
#else
// no signal handling.
static void mft_signal_set_handling(int isOn)
{
    return;
}
#endif

#define DEFAULT_SIZE 64
#define MAX_TOUT 1000
#define REG_ACCESS_TOUT 100
#define SLEEP_TIME 80
#define INIT_PARTITION_SLEEP_TIME 240

#define MTCR_IB_TIMEOUT_VAR "MTCR_IB_TIMEOUT"
#define MTCR_IB_TIMEOUT_VAL "30000"

#define NV_BASE_MAC_GUID_IDX     0x02
#define NV_BASE_MAC_GUID_CAP_IDX 0x03

#define CX2_DEVID           0x190
#define CX3_DEVID           0x1f5
#define CX3PRO_DEVID        0x1f7
#define SX_DEVID            0x245
#define IS4_DEVID           0x1b3
#define SWITCH_IB_DEVID     0x247
#define SWITCH_IB2_DEVID    0x24b
#define SPECTRUM_DEVID      0x249
#define SPECTRUM2_DEVID     0x24e
#define SPECTRUM3_DEVID     0x250
#define QUANTUM_DEVID       0x24d


#ifndef UEFI_BUILD
#define DPRINTF(args)        do { char *reacDebug = getenv("FW_COMPS_DEBUG"); \
                                  if (reacDebug != NULL) { \
                                      printf("[FW_COMPS_DEBUG]: -D- "); printf args;} } while (0)
#else
#define DPRINTF(...)
#endif

/*
 * Wrapper to call the MCDA command
 */

bool FwCompsMgr::runNVDA(std::vector<u_int8_t>& buff,
                         u_int16_t len,
                         u_int32_t tlvType,
                         reg_access_method_t method,
                         bool queryDefault)
{
    struct tools_open_nvda nvdaTlv;
    memset(&nvdaTlv, 0, sizeof(struct tools_open_nvda));

    nvdaTlv.nv_hdr.length = len;
    if (queryDefault) {
        nvdaTlv.nv_hdr.default_ = 1;
    }
    // tlvType should be in the correct endianess
    nvdaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw = tlvType;
    if (method == REG_ACCESS_METHOD_SET) {
        memcpy(nvdaTlv.data, buff.data(), len);
    }
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_nvda(_mf, method, &nvdaTlv);
    deal_with_signal();
    if (rc) {
        _lastError = regErrTrans(rc);
        setLastRegisterAccessStatus(rc);
        return false;
    }
    if (buff.size() < nvdaTlv.nv_hdr.length) {
        buff.resize(nvdaTlv.nv_hdr.length);
    }
    memcpy(buff.data(), nvdaTlv.data, nvdaTlv.nv_hdr.length);
    return true;
}

bool FwCompsMgr::accessComponent(u_int32_t offset,
    u_int32_t size,
    u_int32_t data[],
    access_type_t access,
    ProgressCallBackAdvSt *progressFuncAdv)
{
    bool bRes = _accessObj->accessComponent(_updateHandle, offset, size, data, access, _currComponentStr, progressFuncAdv);
    setLastFirmwareError(_accessObj->getLastFirmwareError());
    setLastRegisterAccessStatus(_accessObj->getLastRegisterAccessStatus());
    return bRes;
}

const char* FwCompsMgr::stateToStr(fsm_state_t st)
{
    switch (st) {
    case FSMST_INITIALIZE:
        return "Initializing image partition";

    default:
        return "Progress";
    }
}

const char* FwCompsMgr::commandToStr(fsm_command_t cmd)
{
    switch (cmd) {
    case FSM_CMD_VERIFY_COMPONENT:
        return "Verifying component";

    case FSM_CMD_UPDATE_COMPONENT:
        return "Updating component";

    default:
        return "Unknown Command";
    }
}

bool FwCompsMgr::controlFsm(fsm_command_t command,
                            fsm_state_t expStatus,
                            u_int32_t size,
                            fsm_state_t currState,
                            ProgressCallBackAdvSt *progressFuncAdv,
                            u_int32_t reg_access_timeout)
{
    reg_access_status_t rc = ME_OK;
    reg_access_method_t method = REG_ACCESS_METHOD_SET;
    if (!reg_access_timeout) {
        reg_access_timeout = MAX_TOUT;
    }
    DPRINTF(("controlFsm : command %u current %u expected %u\n", command, currState, expStatus));
    unsigned int count = 0;
    do {
        if (count) {
            msleep(SLEEP_TIME);
        }
        method = REG_ACCESS_METHOD_SET;
        if (command == FSM_QUERY) {
            method = REG_ACCESS_METHOD_GET;
        }
        mft_signal_set_handling(1);
        memset(&_lastFsmCtrl, 0, sizeof(_lastFsmCtrl));
        _lastFsmCtrl.instruction = command;
        _lastFsmCtrl.device_index = _deviceIndex;
        _lastFsmCtrl.device_type = _deviceType;
        _lastFsmCtrl.component_index = _componentIndex;
        _lastFsmCtrl.component_size = size;
        _lastFsmCtrl.update_handle = _updateHandle;

        rc = reg_access_mcc(_mf, method, &_lastFsmCtrl);

        deal_with_signal();
    } while (rc == ME_REG_ACCESS_RES_NOT_AVLBL && count++ < reg_access_timeout);
    if (rc) {
        if (_lastFsmCtrl.error_code) {
            _lastError = mccErrTrans(_lastFsmCtrl.error_code);
        }
        else {
            _lastError = regErrTrans(rc);
            setLastRegisterAccessStatus(rc);
        }
        return false;
    }
    if (expStatus == FSMST_NA && currState == FSMST_NA) {
        return true;
    }
    count = 0;
    // initialization longer then other states
    unsigned sleep_time = currState == FSMST_INITIALIZE ? INIT_PARTITION_SLEEP_TIME : SLEEP_TIME;
    while (currState != FSMST_NA && _lastFsmCtrl.control_state == currState && count < MAX_TOUT) {
        if (count) {
            msleep(sleep_time);
        }
        if (progressFuncAdv && progressFuncAdv->func) {
            if (progressFuncAdv->func(0, stateToStr(currState), PROG_WITHOUT_PRECENTAGE, progressFuncAdv->opaque)) {
                _lastError = FWCOMPS_ABORTED;
                return false;
            }
        }
        if (!controlFsm(FSM_QUERY)) {
            return false;
        }
        count++;
    }
    if (count >= MAX_TOUT) {
        _lastError = FWCOMPS_MCC_TOUT;
        return false;
    }
    if (expStatus != FSMST_NA && _lastFsmCtrl.control_state != expStatus) {
        DPRINTF(("controlFsm : control_state FW %u expected %u\n", _lastFsmCtrl.control_state, expStatus));
        _lastError = FWCOMPS_MCC_UNEXPECTED_STATE;
        return false;
    }

    if (progressFuncAdv && progressFuncAdv->func && currState != FSMST_NA) {
        if (progressFuncAdv->func(100, stateToStr(currState), PROG_OK, progressFuncAdv->opaque)) {
            _lastError = FWCOMPS_ABORTED;
            return false;
        }
    }
    return true;
}

bool FwCompsMgr::runMCQI(u_int32_t componentIndex,
                         u_int8_t readPending,
                         u_int32_t infoType,
                         u_int32_t dataSize,
                         u_int32_t offset,
                         u_int32_t *data)
{
    u_int32_t i = 0;
    bool ret = true;
    std::vector<u_int32_t> dataInfo;
    mft_signal_set_handling(1);
    memset(&_currCompInfo, 0, sizeof(_currCompInfo));
    _currCompInfo.read_pending_component = readPending;
    _currCompInfo.info_type = infoType;
    _currCompInfo.offset = offset;
    _currCompInfo.data_size = dataSize;
    _currCompInfo.component_index = componentIndex;
    _currCompInfo.device_index = _deviceIndex;
    _currCompInfo.device_type = _deviceType;

    if (dataSize) {
        dataInfo.resize(dataSize, 0);
        _currCompInfo.data = dataInfo.data();
    }
    reg_access_status_t rc = reg_access_mcqi(_mf, REG_ACCESS_METHOD_GET, &_currCompInfo);
    deal_with_signal();
    if (rc) {
        _lastError = regErrTrans(rc);
        setLastRegisterAccessStatus(rc);
        ret = false;
        goto cleanup;
    }

    if (data && dataSize) {
        if (!rc) {
            for (i = 0; i < _currCompInfo.info_size / 4; i++) {
                data[i] = _currCompInfo.data[i];
            }
        }
    }
cleanup:
    return ret;
}

bool FwCompsMgr::getDeviceHWInfo(FwCompsMgr::MQISDeviceDescriptionT op, vector<u_int8_t>& infoString)
{
    mqisReg mqisRegister;
    mfile *mf;
    mf = getMfileObj();
    if (!mf) {
        return false;
    }
    reg_access_status_t rc;
    int maxDataSize = sizeof(mqisRegister.info_string);

    memset(&mqisRegister, 0, sizeof(mqisReg));
    if (op < MQIS_REGISTER_FIRST_VALUE || op > MQIS_REGISTER_LAST_VALUE)
        return false;

    mqisRegister.info_type = (u_int8_t)op;
    mqisRegister.read_length = maxDataSize;
    mft_signal_set_handling(1);

    rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
    deal_with_signal();
    if (rc) {
        return false;
    }
    int infoSize = mqisRegister.info_length;
    if (infoSize == 0) {
        return false;
    }
    infoString.resize(infoSize + 1, '\0');

    // copy the output
    memcpy(infoString.data(), mqisRegister.info_string,
            mqisRegister.read_length);

    if (infoSize > mqisRegister.read_length) {
        int leftSize = infoSize - mqisRegister.read_length;
        while (leftSize > 0) {
            mqisRegister.read_offset = infoSize - leftSize;
            mqisRegister.read_length = leftSize > maxDataSize ? maxDataSize : leftSize;
            mft_signal_set_handling(1);

            rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
            deal_with_signal();
            if (rc) {
                return false;
            }
            memcpy(infoString.data() + mqisRegister.read_offset,
                   (mqisRegister.info_string), mqisRegister.read_length);
            leftSize -= mqisRegister.read_length;
        }
    }
    return true;
}

bool FwCompsMgr::queryComponentInfo(u_int32_t componentIndex,
                                    u_int8_t readPending,
                                    u_int32_t infoType,
                                    u_int32_t dataSize,
                                    u_int32_t *data)
{
    u_int32_t maxDataSize = mget_max_reg_size(_mf, MACCESS_REG_METHOD_GET) - sizeof(_currCompInfo);
    if (maxDataSize > MAX_REG_DATA) {
        maxDataSize = MAX_REG_DATA;
    }
    if (!runMCQI(componentIndex, readPending, infoType, maxDataSize, 0, data)) {
        return false;
    }
    u_int32_t compInfoSize = _currCompInfo.info_size;
    u_int32_t tOffset = maxDataSize;
    if (tOffset >= compInfoSize) {
        return true;
    }
    if (dataSize < compInfoSize) {
        compInfoSize = dataSize;
    }
    while (tOffset < compInfoSize) {
        u_int32_t toRead = compInfoSize - tOffset > maxDataSize ? maxDataSize : compInfoSize - tOffset;
        if (!runMCQI(componentIndex, readPending, infoType, toRead, tOffset, data + tOffset)) {
            return false;
        }
        tOffset += maxDataSize;
    }
    return true;
}

reg_access_status_t FwCompsMgr::getGI(mfile *mf, mgirReg *gi)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;
    u_int32_t tp = 0;
    mget_mdevs_type(mf, &tp);
    mft_signal_set_handling(1);
#if !defined(UEFI_BUILD) && !defined(NO_INBAND)
    if (tp == MST_IB) {
        rc = (reg_access_status_t)mad_ifc_general_info_hw(mf, &gi->hw_info);
        if (rc) {
            goto cleanup;
        }
        rc = (reg_access_status_t)mad_ifc_general_info_fw(mf, &gi->fw_info);
        if (rc) {
            goto cleanup;
        }
        rc = (reg_access_status_t)mad_ifc_general_info_sw(mf, &gi->sw_info);
    }
    else {
        rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, gi);
        goto cleanup;
    }
#else
    rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, gi);
    goto cleanup;
#endif
cleanup:
    deal_with_signal();
    return rc;

}

bool FwComponent::init(const std::vector<u_int8_t>&  buff,
                       u_int32_t size,
                       comps_ids_t type,
                       u_int32_t idx)
{
    if (_initialized) {
        return false;
    }
    _type = type;
    _size = size;
    _data = buff;
    _componentIndex = idx;
    _initialized = true;
    return true;
}

void FwCompsMgr::initialize(mfile *mf)
{
    _mf = mf;
    memset(&_lastFsmCtrl, 0, sizeof(fsm_control_st));
    _lastError = FWCOMPS_SUCCESS;
    _componentIndex = 0;
    _lastRegAccessStatus = ME_OK;
    _updateHandle = 0;
    if (getFwSupport()) {
        generateHandle();
    }
    ComponentAccessFactory* factory = ComponentAccessFactory::GetInstance();
    _accessObj = factory->createDataAccessObject(this, mf, isDmaSupported);
    _refreshed = false;
}

FwCompsMgr::FwCompsMgr(mfile *mf, DeviceTypeT devType, int deviceIndex)
{
    _clearSetEnv = false;
    _openedMfile = false;
    _hwDevId = 0;
    _deviceType = devType;
    _deviceIndex = deviceIndex;
    _accessObj = NULL;
    _mircCaps = false;
#ifndef UEFI_BUILD    
    _trm = NULL;
#endif    
    initialize(mf);
}

FwCompsMgr::FwCompsMgr(const char *devname, DeviceTypeT devType, int deviceIndex)
{
    _mf = NULL;
    _openedMfile = false;
    _clearSetEnv = false;
    _accessObj = NULL;
    _deviceType = devType;
    _deviceIndex = deviceIndex;
#ifndef UEFI_BUILD
    if (getenv(MTCR_IB_TIMEOUT_VAR) == NULL) {
        _clearSetEnv = true;
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW64__) || defined(__MINGW32__)
        putenv(MTCR_IB_TIMEOUT_VAR "=" MTCR_IB_TIMEOUT_VAL);
#else
        setenv(MTCR_IB_TIMEOUT_VAR, MTCR_IB_TIMEOUT_VAL, 1);
#endif
    }
#endif
    _hwDevId = 0;
    _mircCaps = false;
#ifndef UEFI_BUILD    
    _trm = NULL;
#endif    
    _lastError = FWCOMPS_SUCCESS;
    mfile *mf = mopen(devname);
    if (!mf) {
        _lastError = FWCOMPS_BAD_PARAM;
        return;
    }
    _openedMfile = true;
    initialize(mf);
}

FwCompsMgr::FwCompsMgr(uefi_Dev_t *uefi_dev, uefi_dev_extra_t *uefi_extra)
{
    _mf = NULL;
    _accessObj = NULL;
    _openedMfile = false;
    _clearSetEnv = false;
    _mircCaps = false;
    mfile *mf = mopen_fw_ctx((void *)uefi_dev, (void *)uefi_extra->fw_cmd_func, \
        (void *)&uefi_extra->dev_info);
    if (!mf) {
        _lastError = FWCOMPS_MEM_ALLOC_FAILED;
        return;
    }
    if (&uefi_extra->dev_info != NULL) {
        _hwDevId = uefi_extra->dev_info.hw_dev_id;
    }
    _openedMfile = true;
    initialize(mf);

}
FwCompsMgr::~FwCompsMgr()
{
#ifndef UEFI_BUILD
    if (_clearSetEnv) {
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW64__) || defined(__MINGW32__)
        putenv(MTCR_IB_TIMEOUT_VAR "=");
#else
        unsetenv(MTCR_IB_TIMEOUT_VAR);
#endif
    }
#endif
    if (_lastFsmCtrl.control_state != FSMST_IDLE) {
        controlFsm(FSM_CMD_CANCEL, FSMST_LOCKED);
        controlFsm(FSM_CMD_RELEASE_UPDATE_HANDLE, FSMST_IDLE);
    }
    if (_openedMfile) {
        if (_mf) {
            mclose(_mf);
        }
    }
    if (_accessObj != NULL) {
        delete _accessObj;
        _accessObj = NULL;
    }
}

bool FwCompsMgr::forceRelease()
{
    return controlFsm(FSM_CMD_FORCE_HANDLE_RELEASE);
}

void FwCompsMgr::generateHandle()
{
    if (!controlFsm(FSM_QUERY, FSMST_NA, 0, FSMST_NA, NULL, REG_ACCESS_TOUT)) {
        _updateHandle = 0;
        return;
    }
    _updateHandle = _lastFsmCtrl.update_handle & 0xffffff;
}

bool FwCompsMgr::refreshComponentsStatus()
{
    u_int16_t compIdx = 0;
    int last_index_flag = 0;
    comp_query_st compStatus;
    if (_refreshed) {
        return true;
    }
    if (_compsQueryMap.size()) {
        _compsQueryMap.clear();
    }
    _compsQueryMap.resize((unsigned)(FwComponent::COMPID_UNKNOWN));
    while (!last_index_flag) {
        memset(&compStatus, 0, sizeof(comp_query_st));
        if (queryComponentStatus(compIdx, &(compStatus.comp_status))) {
            compStatus.comp_status.component_index = compIdx;
            /* */
            u_int32_t capSt[DEFAULT_SIZE] = { 0 };
            if (queryComponentInfo(compIdx, 1, COMPINFO_CAPABILITIES, DEFAULT_SIZE, capSt) == false) {
                if (queryComponentInfo(compIdx, 0, COMPINFO_CAPABILITIES, DEFAULT_SIZE, capSt) == false) {
                    //_lastError = FWCOMPS_REG_FAILED;
                    return false;
                }
            }
            reg_access_hca_mcqi_cap_unpack(&compStatus.comp_cap, (const u_int8_t *)capSt);
            compStatus.valid = 1;
            //reg_access_hca_mcqi_cap_print(&(compStatus.comp_cap), stdout, 3);
            memcpy(&(_compsQueryMap[compStatus.comp_status.identifier]), &compStatus, sizeof(compStatus));
            DPRINTF(("-D- Found component: %#x\n", compStatus.comp_status.identifier));
            last_index_flag = compStatus.comp_status.last_index_flag;
        }
        else {
            DPRINTF(("-D- queryComponentStatus failed !!\n"));
            return false;
        }
        compIdx++;
    }
    _refreshed = true;
    return true;
}

//TODO: Check all the rc ..

bool FwCompsMgr::readComponent(FwComponent::comps_ids_t compType, FwComponent& fwComp, bool readPending,
                               ProgressCallBackAdvSt *progressFuncAdv)
{
    if (!refreshComponentsStatus()) {
        return false;
    }
    _currCompQuery = &(_compsQueryMap[compType]);
    _componentIndex = _currCompQuery->comp_status.component_index;
    std::vector<u_int8_t> data;
    u_int32_t compSize = _currCompQuery->comp_cap.component_size;
    if (_currCompQuery->comp_cap.rd_en) {
        data.resize(compSize);
        if (!controlFsm(FSM_CMD_LOCK_UPDATE_HANDLE, FSMST_LOCKED)) {
            return false;
        }
        if (!controlFsm(readPending ? FSM_CMD_READ_PENDING_COMPONENT : FSM_CMD_READ_COMPONENT, FSMST_UPLOAD)) {
            controlFsm(FSM_CMD_RELEASE_UPDATE_HANDLE);
            return false;
        }
        _currComponentStr = FwComponent::getCompIdStr(compType);
        if (!accessComponent(0, compSize, (u_int32_t *)(data.data()), MCDA_READ_COMP, progressFuncAdv)) {
            //_lastError = FWCOMPS_READ_COMP_FAILED;
            return false;
        }
        if (!controlFsm(FSM_CMD_RELEASE_UPDATE_HANDLE)) {
            return false;
        }
    }
    else {
        _lastError = FWCOMPS_READ_COMP_NOT_SUPPORTED;
        return false;
    }

    fwComp.init(data, compSize, (FwComponent::comps_ids_t)_currCompInfo.info_type, _componentIndex);
    return true;
}

bool FwCompsMgr::readComponentInfo(FwComponent::comps_ids_t compType,
                                   comp_info_t infoType,
                                   std::vector<u_int32_t>& retData,
                                   bool readPending)
{
    if (!refreshComponentsStatus()) {
        return false;
    }
    _currCompQuery = &(_compsQueryMap[compType]);
    _componentIndex = _currCompQuery->comp_status.component_index;
    if (!queryComponentInfo(_componentIndex, readPending == true, infoType, 0, 0)) {
        return false;
    }

    if (_currCompQuery->comp_cap.supported_info_bitmask & (1 << infoType)) {
        u_int32_t size = _currCompInfo.info_size;
        retData.resize(size);
        queryComponentInfo(_componentIndex, readPending == true, infoType, size, (u_int32_t *)(retData.data()));
        return true;
    }
    else {
        _lastError = FWCOMPS_INFO_TYPE_NOT_SUPPORTED;
        return false;
    }
}

bool FwCompsMgr::queryComponentStatus(u_int32_t componentIndex,
    comp_status_st *query)
{
    mft_signal_set_handling(1);
    query->component_index = componentIndex;
    query->device_index = _deviceIndex;
    query->device_type = _deviceType;
    reg_access_status_t rc = reg_access_mcqs(_mf, REG_ACCESS_METHOD_GET, query);
    deal_with_signal();
    if (rc) {
        _lastError = regErrTrans(rc);
        setLastRegisterAccessStatus(rc);
        return false;
    }
    return true;
}

bool FwCompsMgr::burnComponents(std::vector<FwComponent>& comps,
                                ProgressCallBackAdvSt *progressFuncAdv)
{
    unsigned i = 0;
    if (!refreshComponentsStatus()) {
        return false;
    }
    if (!controlFsm(FSM_CMD_LOCK_UPDATE_HANDLE, FSMST_LOCKED)) {
        forceRelease();
        return false;
    }
    for (i = 0; i < comps.size(); i++) {
        _currCompQuery = &(_compsQueryMap[comps[i].getType()]);
        if (!_currCompQuery->valid) {
            _lastError = FWCOMPS_COMP_NOT_SUPPORTED;
            return false;
        }
        _componentIndex = _currCompQuery->comp_status.component_index;
        if (!controlFsm(FSM_CMD_UPDATE_COMPONENT, FSMST_DOWNLOAD, comps[i].getSize(), FSMST_INITIALIZE, progressFuncAdv)) {
            return false;
        }
        _currComponentStr = FwComponent::getCompIdStr(comps[i].getType());
        if (!accessComponent(0, comps[i].getSize(), (u_int32_t *)(comps[i].getData().data()), MCDA_WRITE_COMP, progressFuncAdv)) {
            //_lastError = FWCOMPS_DOWNLOAD_FAILED;
            return false;
        }
        if (!controlFsm(FSM_CMD_VERIFY_COMPONENT, FSMST_LOCKED, 0, FSMST_NA, progressFuncAdv)) {
            DPRINTF(("Verifying component has failed!\n"));
            return false;
        }
    }
    if (!controlFsm(FSM_CMD_ACTIVATE_ALL)) {
        return false;
    }
    if (!controlFsm(FSM_CMD_RELEASE_UPDATE_HANDLE)) {
        return false;
    }
    _refreshed = false;
    return true;
}


bool FwCompsMgr::getFwComponents(std::vector<FwComponent>& compsMap, bool readEn)
{
    if (!refreshComponentsStatus()) {
        return false;
    }
    for (std::vector<comp_query_st>::iterator it = _compsQueryMap.begin();
        it != _compsQueryMap.end(); it++) {
        if (!it->valid) {
            continue;
        }
        FwComponent fwCmp((FwComponent::comps_ids_t)it->comp_status.identifier,
                          (FwComponent::comps_status_t)it->comp_status.component_status);
        if (readEn && !readComponent((FwComponent::comps_ids_t)it->comp_status.identifier, fwCmp, 0)) {
            return false;
        }
        else {
            fwCmp.setSize(it->comp_cap.component_size);
        }
        compsMap.push_back(fwCmp);
    }
    return true;
}

const char* FwComponent::getCompIdStr(comps_ids_t compId)
{
    switch (compId) {
    case COMPID_BOOT_IMG:
        return "Boot image";

    case COMPID_RUNTIME_IMG:
        return "RUNTIME_IMAGE";

    case COMPID_CS_TOKEN:
        return "CS_TOKEN";

    case COMPID_MLNX_NVCONFIG:
        return "MLNX_NVCONFIG";

    case COMPID_OEM_NVCONFIG:
        return "OEM_NVCONFIG";

    case COMPID_DBG_TOKEN:
        return "DBG_TOKEN";

    case COMPID_GEARBOX:
        return "GEARBOX";

        case COMPID_CONGESTION_CONTROL:
            return "CONGESTION_CONTROL";

    default:
        return "UNKNOWN_COMPONENT";
    }
}

void FwCompsMgr::getInfoAsVersion(std::vector<u_int32_t>& infoData,
                                  component_version_st *cmpVer)
{
    u_int8_t *data = (u_int8_t *)(infoData.data());
    reg_access_hca_mcqi_version_unpack(cmpVer, data);
    //reg_access_hca_mcqi_version_print(cmpVer, stdout, 4);
}


u_int32_t FwCompsMgr::getFwSupport()
{
    u_int32_t devid = 0;
    isDmaSupported = false;

#ifndef UEFI_BUILD
    if (getenv("FW_CTRL") != NULL) {
        return 1;
    }
    if (mread4(_mf, 0xf0014, &devid) != 4) {
        /*
         * Best effort to check MCAM
         */
        devid = 0;
    }
#else
    devid = _hwDevId;
#endif
    devid = EXTRACT(devid, 0, 16);
    /*
     * If 4TH gen nic or switch with no MCAM reg return not supported
     */
    if (devid == CX2_DEVID ||
        devid == CX3_DEVID ||
        devid == CX3PRO_DEVID ||
        devid == SX_DEVID ||
        devid == IS4_DEVID ||
        devid == SWITCH_IB_DEVID  ||
        devid == SWITCH_IB2_DEVID ||
        devid == SPECTRUM_DEVID   ||
        devid == SPECTRUM2_DEVID  ||
        devid == SPECTRUM3_DEVID  ||
        devid == QUANTUM_DEVID) {
        _lastError = FWCOMPS_UNSUPPORTED_DEVICE;
        return 0;
    }

    tools_open_mcam mcam;
    memset(&mcam, 0, sizeof(mcam));
    reg_access_status_t rc = reg_access_mcam(_mf, REG_ACCESS_METHOD_GET, &mcam);
    if (rc) {
        _lastError = FWCOMPS_UNSUPPORTED_DEVICE;
        return 0;
    }
    /*
     * MCDA bit are in offsets 0x60-0x64
     * MCDD in bit 0x5C
     * MGIR in bit 0x20
     * The bytes are in reverse order
     */
    u_int8_t mcdaCaps = EXTRACT(mcam.mng_access_reg_cap_mask[3], 0, 5);
    u_int8_t mcddCaps = EXTRACT(mcam.mng_access_reg_cap_mask[4], 4, 1);//##EDDY: need check ! register 5c
    u_int8_t mgirCaps = EXTRACT(mcam.mng_access_reg_cap_mask[11], 0, 1);
    if (mcddCaps == 1)
        isDmaSupported = true;

    memset(&mcam, 0, sizeof(mcam));
    mcam.access_reg_group = 2;//for MIRC register
    rc = reg_access_mcam(_mf, REG_ACCESS_METHOD_GET, &mcam);
    if (rc) {
        _lastError = FWCOMPS_UNSUPPORTED_DEVICE;
        return 0;
    }

    _mircCaps = EXTRACT(mcam.mng_access_reg_cap_mask[3], 2, 1);//MIRC is 0x9162
    DPRINTF(("getFwSupport _mircCaps = %d mcdaCaps = %d mcddCaps = %d mgirCaps = %d\n", _mircCaps, mcdaCaps, mcddCaps, mgirCaps));

    if (mcdaCaps == 0x1f && mgirCaps) {
        return 1;
    }
    _lastError = FWCOMPS_UNSUPPORTED_DEVICE;
    return 0;
}

#define UID_EXTRACT(INT64, INT32ARR) INT64 = ((u_int64_t)INT32ARR[0] << 32) | INT32ARR[1];

bool FwCompsMgr::extractMacsGuids(fwInfoT *fwQuery)
{
    std::vector<u_int8_t> nvBaseMacGuidData;
    std::vector<u_int8_t> nvBaseMacGuidDataOrig;
    std::vector<u_int8_t> nvBaseMacGuidCap;
    std::vector<u_int8_t> nvBaseMacGuidCapOrig;
    struct tools_open_nv_base_mac_guid currMacGuid;
    struct tools_open_nv_base_mac_guid origMacGuid;

    struct tools_open_nv_base_mac_guid_cap currMacGuidCap;
    struct tools_open_nv_base_mac_guid_cap origMacGuidCap;

    memset(&currMacGuid, 0, sizeof(currMacGuid));
    memset(&origMacGuid, 0, sizeof(origMacGuid));
    memset(&currMacGuidCap, 0, sizeof(currMacGuidCap));
    memset(&origMacGuidCap, 0, sizeof(origMacGuidCap));

    if (!runNVDA(nvBaseMacGuidData, 64, NV_BASE_MAC_GUID_IDX, REG_ACCESS_METHOD_GET, false)) {
        return false;
    }
    if (!runNVDA(nvBaseMacGuidDataOrig, 64, NV_BASE_MAC_GUID_IDX, REG_ACCESS_METHOD_GET, true)) {
        return false;
    }
    if (!runNVDA(nvBaseMacGuidCap, 64, NV_BASE_MAC_GUID_CAP_IDX, REG_ACCESS_METHOD_GET, false)) {
        return false;
    }
    if (!runNVDA(nvBaseMacGuidCapOrig, 64, NV_BASE_MAC_GUID_CAP_IDX, REG_ACCESS_METHOD_GET, true)) {
        return false;
    }
    tools_open_nv_base_mac_guid_unpack(&currMacGuid, nvBaseMacGuidData.data());
    tools_open_nv_base_mac_guid_unpack(&origMacGuid, nvBaseMacGuidDataOrig.data());
    tools_open_nv_base_mac_guid_cap_unpack(&currMacGuidCap, nvBaseMacGuidCap.data());
    tools_open_nv_base_mac_guid_cap_unpack(&origMacGuidCap, nvBaseMacGuidCapOrig.data());

    UID_EXTRACT(fwQuery->base_mac.uid, currMacGuid.base_mac);
    UID_EXTRACT(fwQuery->base_guid.uid, currMacGuid.base_guid);
    UID_EXTRACT(fwQuery->base_guid_orig.uid, origMacGuid.base_guid);

    fwQuery->base_mac.num_allocated = currMacGuidCap.num_of_allocated_macs;
    fwQuery->base_guid.num_allocated = currMacGuidCap.num_of_allocated_guids;
    fwQuery->base_mac_orig.num_allocated = origMacGuidCap.num_of_allocated_macs;
    fwQuery->base_guid_orig.num_allocated = origMacGuidCap.num_of_allocated_guids;
    return true;
}


bool FwCompsMgr::setMacsGuids(mac_guid_t macGuid)
{
    std::vector<u_int8_t> macsGuidsBuff(16, 0);

    struct tools_open_nv_base_mac_guid baseMacGuid;

    baseMacGuid.base_guid[0] = macGuid.guid.h;
    baseMacGuid.base_guid[1] = macGuid.guid.l;
    baseMacGuid.base_mac[0] = macGuid.mac.h;
    baseMacGuid.base_mac[1] = macGuid.mac.l;

    tools_open_nv_base_mac_guid_pack(&baseMacGuid, macsGuidsBuff.data());

    return runNVDA(macsGuidsBuff, 16, NV_BASE_MAC_GUID_IDX, REG_ACCESS_METHOD_SET, false);
}

u_int8_t transRomType(u_int8_t mgirRomType)
{
    switch (mgirRomType) {
    case 0x1: //FLEXBOOT
        return 0x10;

    case 0x2: //UEFI
        return 0x11;
         
    case 0x3: //UEFI_CLP
        return 0x12;

    case 0x4: //NVMe
        return 0x13;

    case 0x5: //FCODE
        return 0x21;
    default:
        return mgirRomType;
    }
}

void FwCompsMgr::extractRomInfo(mgirReg *mgir, fwInfoT *fwQuery)
{
    if (!fwQuery || !mgir) {
        return;
    }
    fwQuery->nRoms = 0;
    if (mgir->sw_info.rom3_type) {
        fwQuery->roms[fwQuery->nRoms].arch = mgir->sw_info.rom3_arch;
        fwQuery->roms[fwQuery->nRoms].type = transRomType(mgir->sw_info.rom3_type);
        fwQuery->roms[fwQuery->nRoms].version = mgir->sw_info.rom3_version;
        fwQuery->nRoms++;
    }
    if (mgir->sw_info.rom2_type) {
        fwQuery->roms[fwQuery->nRoms].arch = mgir->sw_info.rom2_arch;
        fwQuery->roms[fwQuery->nRoms].type = transRomType(mgir->sw_info.rom2_type);
        fwQuery->roms[fwQuery->nRoms].version = mgir->sw_info.rom2_version;
        fwQuery->nRoms++;
    }
    if (mgir->sw_info.rom1_type) {
        fwQuery->roms[fwQuery->nRoms].arch = mgir->sw_info.rom1_arch;
        fwQuery->roms[fwQuery->nRoms].type = transRomType(mgir->sw_info.rom1_type);
        fwQuery->roms[fwQuery->nRoms].version = mgir->sw_info.rom1_version;
        fwQuery->nRoms++;
    }
    if (mgir->sw_info.rom0_type) {
        fwQuery->roms[fwQuery->nRoms].arch = mgir->sw_info.rom0_arch;
        fwQuery->roms[fwQuery->nRoms].type = transRomType(mgir->sw_info.rom0_type);
        fwQuery->roms[fwQuery->nRoms].version = mgir->sw_info.rom0_version;
        fwQuery->nRoms++;
    }
}

bool FwCompsMgr::queryFwInfo(fwInfoT *query, bool next_boot_fw_ver)
{
    if (!query) {
        _lastError = FWCOMPS_BAD_PARAM;
        return false;
    }
    /*
    * MGIR
    */
    reg_access_status_t rc;
    mgirReg mgir;
    memset(&mgir, 0, sizeof(mgir));
    memset(query, 0, sizeof(fwInfoT));
    if (getComponentVersion(FwComponent::COMPID_BOOT_IMG, true, &query->pending_fw_version)) {
        query->pending_fw_valid = 1;
    }
    if (!getComponentVersion(FwComponent::COMPID_BOOT_IMG, false, &query->running_fw_version)) {
        return false;
    }

    if (next_boot_fw_ver) {
        // query next_boot_fw_ver only. enough to query pending, running versions and device_id.
        rc = getGI(_mf, &mgir);
        if (rc) {
            _lastError = FWCOMPS_QUERY_FAILED;
            return false;
        }
        query->hw_dev_id = mgir.hw_info.hw_dev_id;
        query->dev_id = mgir.hw_info.device_id;
        query->rev_id = mgir.hw_info.device_hw_revision;
        return true;
    }

    if (query->running_fw_version.version_string_length &&
        query->running_fw_version.version_string_length <= PRODUCT_VER_LEN) {
        strcpy(query->product_ver, (char *)_productVerStr.data());
    }

    rc = getGI(_mf, &mgir);
    if (rc) {
        _lastError = FWCOMPS_QUERY_FAILED;
        return false;
    }
    //tools_open_mgir_print(&mgir, stdout, 1);
    memcpy(query->psid, mgir.fw_info.psid, PSID_LEN);
    query->hw_dev_id = mgir.hw_info.hw_dev_id;
    query->dev_id = mgir.hw_info.device_id;
    query->rev_id = mgir.hw_info.device_hw_revision;
    query->security_type.secure_fw = mgir.fw_info.secured;
    query->security_type.signed_fw = mgir.fw_info.signed_fw;
    query->security_type.debug_fw = mgir.fw_info.debug;
    query->security_type.dev_fw = mgir.fw_info.dev;
    query->life_cycle = (life_cycle_t)mgir.fw_info.life_cycle;
    query->sec_boot = mgir.fw_info.sec_boot;
    query->signed_fw = _compsQueryMap[FwComponent::COMPID_BOOT_IMG].comp_cap.signed_updates_only;

    query->base_mac_orig.uid = ((u_int64_t)mgir.hw_info.manufacturing_base_mac_47_32 << 32 | mgir.hw_info.manufacturing_base_mac_31_0);
    if (!extractMacsGuids(query)) {
        /*
         * We don't fail, it will show NA in the query
         */
    }

    extractRomInfo(&mgir, query);

    /*
     * MQIS
     */
    vector<u_int8_t> nameInfoString;
    vector<u_int8_t> descriptionInfoString;
    vector<u_int8_t> imageVsd;
    vector<u_int8_t> deviceVsd;
    if (getDeviceHWInfo(FwCompsMgr::MQIS_REGISTER_DEVICE_NAME, nameInfoString)) {
        strncpy(query->name, (char *)nameInfoString.data(), NAME_LEN - 1);
    }
    if (getDeviceHWInfo(FwCompsMgr::MQIS_REGISTER_DEVICE_DESCRIPTION_INFO, descriptionInfoString)) {
        strncpy(query->description, (char *)descriptionInfoString.data(), DESCRIPTION_LEN - 1);
    }
    if (getDeviceHWInfo(FwCompsMgr::MQIS_REGISTER_IMAGE_VSD, imageVsd)) {
        strncpy(query->imageVsd, (char *)imageVsd.data(), VSD_LEN);
    }
    if (getDeviceHWInfo(FwCompsMgr::MQIS_REGISTER_DEVICE_VSD, deviceVsd)) {
        strncpy(query->deviceVsd, (char *)deviceVsd.data(), VSD_LEN);
    }

    return true;
}

const char*  FwCompsMgr::getLastErrMsg()
{
    switch (_lastError) {
    case FWCOMPS_ABORTED:
        return "Aborting ... received interrupt signal";

    case FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR:
        return "The Digest in the signature is wrong";

    case FWCOMPS_MCC_ERR_REJECTED_UNSIGNED:
        return "The component is not signed";

    case FWCOMPS_MCC_ERR_BLOCKED_PENDING_RESET:
        return "The firmware image was already updated on flash, pending reset.";

    case FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE:
        return "Component is not applicable";

    case FWCOMPS_MCC_ERR_REJECTED_AUTH_FAILED:
        return "Rejected authentication";

    case FWCOMPS_MCC_ERR_REJECTED_KEY_NOT_APPLICABLE:
        return "The key is not applicable";

    case FWCOMPS_READ_COMP_NOT_SUPPORTED:
        return "Reading component is not supported";
        break;

    case FWCOMPS_COMP_NOT_SUPPORTED:
        return "Component not supported";

    case FWCOMPS_VERIFY_FAILED:
        return "Firmware verifying failed!";

    case FWCOMPS_CR_ERR:
        return "Failed to access CR-Space";

    case FWCOMPS_MCC_REJECTED_NOT_A_SECURED_FW:
        return "The firmware image is not secured";

    case FWCOMPS_MCC_REJECTED_MFG_BASE_MAC_NOT_LISTED:
        return "The manufacturing base MAC was not listed";

    case FWCOMPS_MCC_REJECTED_NO_DEBUG_TOKEN:
        return "There is no Debug Token installed";

    case FWCOMPS_MCC_REJECTED_VERSION_NUM_MISMATCH:
        return "Firmware version mismatch";

    case FWCOMPS_MCC_REJECTED_USER_TIMESTAMP_MISMATCH:
        return "User timestamp mismatch";

    case FWCOMPS_MCC_REJECTED_FORBIDDEN_VERSION:
        return "Forbidden version rejected";

    case FWCOMPS_MCC_FLASH_ERASE_ERROR:
        return "Error while erasing the flash";

    case FWCOMPS_MCC_UNEXPECTED_STATE:
        return "Unexpected state";

    case FWCOMPS_MCC_TOUT:
        return "Time-out reached while waiting for the FSM to be updated";

    case FWCOMPS_MCC_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION:
        return "Image cannot boot from partition.";

    case FWCOMPS_UNSUPPORTED_DEVICE:
        return "Unsupported device";

    case FWCOMPS_MTCR_OPEN_DEVICE_ERROR:
        return "Failed to open device";

    case FWCOMPS_FAIL_TO_LOCK_FLASH_SEMAPHORE:
        return "Failed to lock flash semaphore";

    case FWCOMPS_FAIL_TO_CREATE_TRM_CONTEXT:
        return "Failed to create TRM context";

    case FWCOMPS_REG_ACCESS_BAD_STATUS_ERR:
    case FWCOMPS_REG_ACCESS_BAD_METHOD:
    case FWCOMPS_REG_ACCESS_NOT_SUPPORTED:
    case FWCOMPS_REG_ACCESS_DEV_BUSY:
    case FWCOMPS_REG_ACCESS_VER_NOT_SUPP:
    case FWCOMPS_REG_ACCESS_UNKNOWN_TLV:
    case FWCOMPS_REG_ACCESS_REG_NOT_SUPP:
    case FWCOMPS_REG_ACCESS_CLASS_NOT_SUPP:
    case FWCOMPS_REG_ACCESS_METHOD_NOT_SUPP:
    case FWCOMPS_REG_ACCESS_BAD_PARAM:
    case FWCOMPS_REG_ACCESS_RES_NOT_AVLBL:
    case FWCOMPS_REG_ACCESS_MSG_RECPT_ACK:
    case FWCOMPS_REG_ACCESS_UNKNOWN_ERR:
    case FWCOMPS_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
    case FWCOMPS_REG_ACCESS_CONF_CORRUPT:
    case FWCOMPS_REG_ACCESS_LEN_TOO_SMALL:
    case FWCOMPS_REG_ACCESS_BAD_CONFIG:
    case FWCOMPS_REG_ACCESS_ERASE_EXEEDED:
    case FWCOMPS_REG_ACCESS_INTERNAL_ERROR:
        return reg_access_err2str(_lastRegAccessStatus);

    default:
        if (_lastRegAccessStatus) {
            return reg_access_err2str(_lastRegAccessStatus);
        }
        return "GENERAL ERROR";
    }
}

bool FwCompsMgr::lock_flash_semaphore()
{
#ifndef UEFI_BUILD
    int rc = 0;
    trm_sts trm_rc = trm_create(&_trm, _mf);
    if (trm_rc) {
        _lastError = FWCOMPS_FAIL_TO_CREATE_TRM_CONTEXT;
        return false;
    }
    rc = trm_lock(_trm, TRM_RES_FLASH_PROGRAMING, MAX_FLASH_PROG_SEM_RETRY_CNT);
    if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
        _lastError = FWCOMPS_FAIL_TO_LOCK_FLASH_SEMAPHORE;
        return false;
    }
#endif
    return true;
}

void FwCompsMgr::unlock_flash_semaphore()
{
#ifndef UEFI_BUILD
    if (_trm != NULL) {
        trm_unlock(_trm, TRM_RES_FLASH_PROGRAMING);
        trm_destroy(_trm);
        _trm = NULL;
    }
#endif
}


void FwCompsMgr::deal_with_signal()
{
#ifndef UEFI_BUILD
    int sig;
    sig = mft_signal_is_fired();
    if (sig) {
        unlock_flash_semaphore();
        // reset received signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        //raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
#endif
    return;
}


bool FwCompsMgr::getComponentVersion(FwComponent::comps_ids_t compType,
                                     bool pending,
                                     component_version_st *cmpVer)
{
    std::vector<u_int32_t> imageInfoData;
    if (!cmpVer) {
        _lastError = FWCOMPS_BAD_PARAM;
        return false;
    }
    if (!readComponentInfo(compType, COMPINFO_VERSIONS, imageInfoData, pending)) {
        return false;
    }
    memset(cmpVer, 0, sizeof(component_version_st));
    getInfoAsVersion(imageInfoData, cmpVer);
    if (cmpVer->version_string_length) {
        _productVerStr.resize(cmpVer->version_string_length);
        memcpy(_productVerStr.data(), cmpVer->version_string, cmpVer->version_string_length);
        cmpVer->version_string[0] = '\0';
    }
    return true;
}



bool FwCompsMgr::readBlockFromComponent(FwComponent::comps_ids_t compId,
                                        u_int32_t offset,
                                        u_int32_t size,
                                        std::vector<u_int8_t>& data)
{
    if (!refreshComponentsStatus()) {
        return false;
    }
    _currCompQuery = &(_compsQueryMap[compId]);
    _componentIndex = _currCompQuery->comp_status.component_index;
    u_int32_t compSize = _currCompQuery->comp_cap.component_size;
    if (offset + size > compSize) {
        _lastError = FWCOMPS_READ_OUTSIDE_IMAGE_RANGE;
        return false;
    }
    if (_currCompQuery->comp_cap.rd_en) {
        data.resize(size);
        if (!controlFsm(FSM_CMD_LOCK_UPDATE_HANDLE, FSMST_LOCKED)) {
            return false;
        }
        if (!controlFsm(FSM_CMD_READ_PENDING_COMPONENT, FSMST_UPLOAD)) {
            if (!controlFsm(FSM_CMD_READ_COMPONENT, FSMST_UPLOAD)) {
                _lastError = FWCOMPS_READ_COMP_FAILED;
                return false;
            }
        }
        if (!accessComponent(offset, size, (u_int32_t *)(data.data()), MCDA_READ_COMP)) {
            return false;
        }
        if (!controlFsm(FSM_CMD_RELEASE_UPDATE_HANDLE)) {
            return false;
        }
    }
    else {
        _lastError = FWCOMPS_READ_COMP_NOT_SUPPORTED;
        return false;
    }
    return true;
}

bool FwCompsMgr::fwReactivateImage()
{
    tools_open_mirc_reg mirc;
    mirc.status_code = 0;
    int currentIteration = 0;
    int sleepTimeMs = 50;
    int maxWaitingTime = 30000;//30 sec is enough time
    int maxNumOfIterations = maxWaitingTime / sleepTimeMs;//600 iterations

    if (_mircCaps == false) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FW_NOT_SUPPORTED;
        setLastRegisterAccessStatus(ME_REG_ACCESS_NOT_SUPPORTED);
        return false;
    }

    reg_access_status_t rc;
    rc = reg_access_mirc(_mf, REG_ACCESS_METHOD_SET, &mirc);//send trigger to FW
    deal_with_signal();
    if (rc) {
        DPRINTF(("1 reg_access_mirc failed rc = %d\n", rc));
        _lastError = regErrTrans(rc);
        setLastRegisterAccessStatus(rc);
        return false;
    }
    else {
        memset(&mirc, 0, sizeof(mirc));
        msleep(sleepTimeMs);
        rc = reg_access_mirc(_mf, REG_ACCESS_METHOD_GET, &mirc);
        if (rc) {
            DPRINTF(("2 reg_access_mirc failed rc = %d\n", rc));
            _lastError = regErrTrans(rc);
            return false;
        }
        DPRINTF(("1 mirc.status_code = %d\n", mirc.status_code));
        while (mirc.status_code == IMAGE_REACTIVATION_BUSY) {
            msleep(sleepTimeMs);
            rc = reg_access_mirc(_mf, REG_ACCESS_METHOD_GET, &mirc);
            deal_with_signal();
            if (rc) {
                _lastError = regErrTrans(rc);
                setLastRegisterAccessStatus(rc);
                DPRINTF(("3 reg_access_mirc failed rc = %d\n", rc));
                return false;
            }
            DPRINTF(("2 iteration %d mirc.status_code = %d\n", currentIteration++,  mirc.status_code));
            if (currentIteration >= maxNumOfIterations) {
                _lastError = FWCOMPS_IMAGE_REACTIVATION_WAITING_TIME_EXPIRED;
                return false;
            }
        } 
    }
    if (mirc.status_code == IMAGE_REACTIVATION_SUCCESS) {
        return true;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FIRST_PAGE_COPY_FAILED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_COPY_FAILED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED;
    }
    else if (mirc.status_code == IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED) {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED;
    }
    else {
        _lastError = FWCOMPS_IMAGE_REACTIVATION_UNKNOWN_ERROR;
    }
    return false;
}
void FwCompsMgr::setLastFirmwareError(fw_comps_error_t fw_error)
{
    _lastError = fw_error;
}

void FwCompsMgr::setLastRegisterAccessStatus(reg_access_status_t err)
{
    _lastRegAccessStatus = err;
}

fw_comps_error_t FwCompsMgr::regErrTrans(reg_access_status_t err)
{
    switch (err) {
    case ME_REG_ACCESS_OK:
        return FWCOMPS_REG_ACCESS_OK;

    case ME_REG_ACCESS_BAD_STATUS_ERR:
        return FWCOMPS_REG_ACCESS_BAD_STATUS_ERR;

    case ME_REG_ACCESS_BAD_METHOD:
        return FWCOMPS_REG_ACCESS_BAD_STATUS_ERR;

    case ME_REG_ACCESS_NOT_SUPPORTED:
        return FWCOMPS_REG_ACCESS_NOT_SUPPORTED;

    case ME_REG_ACCESS_DEV_BUSY:
        return FWCOMPS_REG_ACCESS_DEV_BUSY;

    case ME_REG_ACCESS_VER_NOT_SUPP:
        return FWCOMPS_REG_ACCESS_VER_NOT_SUPP;

    case ME_REG_ACCESS_UNKNOWN_TLV:
        return FWCOMPS_REG_ACCESS_UNKNOWN_TLV;

    case ME_REG_ACCESS_REG_NOT_SUPP:
        return FWCOMPS_REG_ACCESS_REG_NOT_SUPP;

    case ME_REG_ACCESS_CLASS_NOT_SUPP:
        return FWCOMPS_REG_ACCESS_CLASS_NOT_SUPP;

    case ME_REG_ACCESS_METHOD_NOT_SUPP:
        return FWCOMPS_REG_ACCESS_METHOD_NOT_SUPP;

    case ME_REG_ACCESS_BAD_PARAM:
        return FWCOMPS_REG_ACCESS_BAD_PARAM;

    case ME_REG_ACCESS_RES_NOT_AVLBL:
        return FWCOMPS_REG_ACCESS_RES_NOT_AVLBL;

    case ME_REG_ACCESS_MSG_RECPT_ACK:
        return FWCOMPS_REG_ACCESS_MSG_RECPT_ACK;

    case ME_REG_ACCESS_UNKNOWN_ERR:
        return FWCOMPS_REG_ACCESS_UNKNOWN_ERR;

    case ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
        return FWCOMPS_REG_ACCESS_SIZE_EXCCEEDS_LIMIT;

    case ME_REG_ACCESS_CONF_CORRUPT:
        return FWCOMPS_REG_ACCESS_CONF_CORRUPT;

    case ME_REG_ACCESS_LEN_TOO_SMALL:
        return FWCOMPS_REG_ACCESS_CONF_CORRUPT;

    case ME_REG_ACCESS_BAD_CONFIG:
        return FWCOMPS_REG_ACCESS_BAD_CONFIG;

    case ME_REG_ACCESS_ERASE_EXEEDED:
        return FWCOMPS_REG_ACCESS_ERASE_EXEEDED;

    case ME_REG_ACCESS_INTERNAL_ERROR:
        return FWCOMPS_REG_ACCESS_INTERNAL_ERROR;

    default:
        return FWCOMPS_GENERAL_ERR;
    }
}

fw_comps_error_t FwCompsMgr::mccErrTrans(u_int8_t err)
{
    switch (err) {
    case MCC_ERRCODE_OK:
        return FWCOMPS_SUCCESS;

    case MCC_ERRCODE_ERROR:
        return FWCOMPS_MCC_ERR_ERROR;

    case MCC_ERRCODE_REJECTED_DIGEST_ERR:
        return FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR;

    case MCC_ERRCODE_REJECTED_NOT_APPLICABLE:
        return FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE;

    case MCC_ERRCODE_REJECTED_UNKNOWN_KEY:
        return FWCOMPS_MCC_ERR_REJECTED_UNKNOWN_KEY;

    case MCC_ERRCODE_REJECTED_AUTH_FAILED:
        return FWCOMPS_MCC_ERR_REJECTED_AUTH_FAILED;

    case MCC_ERRCODE_REJECTED_UNSIGNED:
        return FWCOMPS_MCC_ERR_REJECTED_UNSIGNED;

    case MCC_ERRCODE_REJECTED_KEY_NOT_APPLICABLE:
        return FWCOMPS_MCC_ERR_REJECTED_KEY_NOT_APPLICABLE;

    case MCC_ERRCODE_REJECTED_BAD_FORMAT:
        return FWCOMPS_MCC_ERR_REJECTED_BAD_FORMAT;

    case MCC_ERRCODE_BLOCKED_PENDING_RESET:
        return FWCOMPS_MCC_ERR_BLOCKED_PENDING_RESET;

    case MCC_ERRCODE_REJECTED_NOT_A_SECURED_FW:
        return FWCOMPS_MCC_REJECTED_NOT_A_SECURED_FW;

    case MCC_ERRCODE_REJECTED_MFG_BASE_MAC_NOT_LISTED:
        return FWCOMPS_MCC_REJECTED_MFG_BASE_MAC_NOT_LISTED;

    case MCC_ERRCODE_REJECTED_NO_DEBUG_TOKEN:
        return FWCOMPS_MCC_REJECTED_NO_DEBUG_TOKEN;

    case MCC_ERRCODE_REJECTED_VERSION_NUM_MISMATCH:
        return FWCOMPS_MCC_REJECTED_VERSION_NUM_MISMATCH;

    case MCC_ERRCODE_REJECTED_USER_TIMESTAMP_MISMATCH:
        return FWCOMPS_MCC_REJECTED_USER_TIMESTAMP_MISMATCH;

    case MCC_ERRCODE_REJECTED_FORBIDDEN_VERSION:
        return FWCOMPS_MCC_REJECTED_FORBIDDEN_VERSION;

    case MCC_ERRCODE_FLASH_ERASE_ERROR:
        return FWCOMPS_MCC_FLASH_ERASE_ERROR;

    case MCC_ERRCODE_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION:
        return FWCOMPS_MCC_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION;

    default:
        //            printf("MCC ERROR: %#x\n", err);
        return FWCOMPS_GENERAL_ERR;
    }
}
