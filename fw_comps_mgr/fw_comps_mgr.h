/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
  * fw_comps_mgr.h
  *
  *
  *  Created on: Jul 31, 2016
  *      Author: adham
  */
#ifndef USER_MLXFWOPS_LIB_FW_COMPS_MGR_H_
#define USER_MLXFWOPS_LIB_FW_COMPS_MGR_H_

#include <vector>
#include "reg_access/reg_access.h"
#include "mlxfwops/uefi_c/mft_uefi_common.h"
#include "mlxfwops/lib/mlxfwops_com.h"
#ifndef UEFI_BUILD
#include "tools_res_mgmt/tools_res_mgmt.h"
#endif

using namespace std;

#define PSID_LEN 16
#define MAX_ROM_NUM 4
#define PRODUCT_VER_LEN 16
#define MAX_MSG_SIZE 128
#define MAX_REG_DATA 128

#ifndef UEFI_BUILD
#define DPRINTF(args)        do { char *reacDebug = getenv("FW_COMPS_DEBUG"); \
                                  if (reacDebug != NULL) {  printf("\33[2K\r"); \
                                      printf("%s:%d: ",__FILE__, __LINE__); printf args; fflush(stdout);} } while (0)
#else
#define DPRINTF(...)
#endif
typedef struct reg_access_hca_mqis_reg mqisReg;
typedef struct reg_access_hca_mcqs_reg comp_status_st;
typedef struct reg_access_hca_mcqi_reg comp_info_st;
typedef struct reg_access_hca_mcc_reg fsm_control_st;
typedef struct reg_access_hca_mcqi_cap comp_cap_st;
typedef struct reg_access_hca_mgir mgirReg;

typedef struct reg_access_hca_mcqi_version component_version_st;
typedef struct reg_access_hca_mcqi_linkx_properties component_linkx_st;

typedef int(*ProgressFunc) (int completion);

typedef f_prog_func_adv_st ProgressCallBackAdvSt;

struct uid_entry {
    u_int8_t num_allocated;
    u_int64_t uid;
};

typedef struct {
    u_int8_t type;
    u_int8_t arch;
    reg_access_hca_rom_version version;
} mgirRomInfo;

typedef struct {
    u_int8_t secure_fw;
    u_int8_t signed_fw;
    u_int8_t debug_fw;
    u_int8_t dev_fw;
} security_fw_t;

typedef struct {
    component_version_st pending_fw_version;
    component_version_st running_fw_version;
    component_linkx_st linkx_data;
    security_fw_t security_type;
    char psid[PSID_LEN + 1];
    char product_ver[PRODUCT_VER_LEN + 1];
    uid_entry base_guid;
    uid_entry base_mac;
    uid_entry base_guid_orig;
    uid_entry base_mac_orig;
    u_int16_t dev_id;
    u_int16_t hw_dev_id;
    u_int16_t rev_id;
    u_int8_t signed_fw;
    u_int8_t pending_fw_valid;
    mgirRomInfo roms[MAX_ROM_NUM];
    int nRoms;
    char name[NAME_LEN];
    char description[DESCRIPTION_LEN];
    char deviceVsd[VSD_LEN + 1];
    char imageVsd[VSD_LEN + 1];
    bool sec_boot;
    life_cycle_t life_cycle;
    bool encryption;

} fwInfoT;

typedef struct {
    comp_status_st comp_status;
    comp_cap_st comp_cap;
    int valid;
} comp_query_st;

typedef enum {
    MCC_READ_COMP = 0x0,
    MCC_WRITE_COMP
} access_type_t;

typedef struct mac_guid {
    guid_t mac;
    guid_t guid;
} mac_guid_t;

typedef enum {
    COMPINFO_CAPABILITIES = 0,
    COMPINFO_VERSIONS = 1,
    COMPINFO_PUBLIC_KEYS = 2,
    COMPINFO_FORBIDDEN_VERSION = 3,
    COMPINFO_ACTIVATION_METHOD = 5,
    COMPINFO_LINKX_PROPERTIES = 6
} comp_info_t;

class FwComponent {
public:

    typedef enum {
        COMPID_BOOT_IMG = 0x1,
        COMPID_RUNTIME_IMG = 0x2,
        COMPID_USER_NVCONFIG = 0x3,
        COMPID_OEM_NVCONFIG = 0x4,
        COMPID_MLNX_NVCONFIG = 0x5,
        COMPID_CS_TOKEN = 0x6,
        COMPID_DBG_TOKEN = 0x7,
        COMPID_DEV_INFO = 0x8,
        COMPID_GEARBOX = 0xA,
        COMPID_CONGESTION_CONTROL = 0xB,
        COMPID_LINKX = 0xC,
        COMPID_CRYPTO_TO_COMMISSIONING = 0xD,
        COMPID_RMCS_TOKEN = 0xE,
        COMPID_RMDT_TOKEN = 0xF,
        COMPID_UNKNOWN = 0xff,
    } comps_ids_t;

    typedef enum {
        COMPSTAT_NOT_PRESENT   = 0x0,
        COMPSTAT_PRESENT       = 0x1,
        COMPSTAT_IN_USE        = 0x2,
        COMPSTAT_UNKNOWN       = 0xff
    } comps_status_t;

    FwComponent() : _size(0), _type(COMPID_UNKNOWN), _componentIndex(0xffffffff), _initialized(false),
        _status(COMPSTAT_UNKNOWN) {};
    FwComponent(comps_ids_t compId) : _size(0), _type(compId), _componentIndex(0xffffffff),
        _initialized(false), _status(COMPSTAT_UNKNOWN) {};
    FwComponent(comps_ids_t compId, comps_status_t compStat) : _size(0), _type(compId), _componentIndex(0xffffffff),
        _initialized(false), _status(compStat) {};
    ~FwComponent() {};

    bool        init(const std::vector<u_int8_t>&  buff,
                     u_int32_t size,
                     comps_ids_t type,
                     u_int32_t idx = 0xffffffff);
    std::vector<u_int8_t>&   getData()   { return _data; };
    u_int32_t                getSize()   { return _size; };
    comps_ids_t              getType()   { return _type; };
    comps_status_t           getStatus() { return _status; };

    void                    setData(const std::vector<u_int8_t>&  buff) { _data = buff; };
    void                    setSize(u_int32_t size) { _size = size; };
    void                    setType(comps_ids_t compId) { _type = compId; };
    void                    setStatus(comps_status_t compStat) { _status = compStat; };

    static const char*       getCompIdStr(comps_ids_t compId);

private:
    std::vector<u_int8_t>   _data;
    u_int32_t _size;
    comps_ids_t _type;
    u_int32_t _componentIndex;
    bool _initialized;
    comps_status_t _status;

};

typedef enum {
    FWCOMPS_SUCCESS = 0x0,
    FWCOMPS_INFO_TYPE_NOT_SUPPORTED,
    FWCOMPS_COMP_NOT_SUPPORTED,
    FWCOMPS_REG_FAILED,
    FWCOMPS_READ_COMP_FAILED,
    FWCOMPS_QUERY_FAILED,
    FWCOMPS_MEM_ALLOC_FAILED,
    FWCOMPS_DOWNLOAD_FAILED,
    FWCOMPS_MCC_TOUT,
    FWCOMPS_ABORTED,
    FWCOMPS_READ_COMP_NOT_SUPPORTED,
    FWCOMPS_BAD_PARAM,
    FWCOMPS_GENERAL_ERR,
    FWCOMPS_CR_ERR,
    FWCOMPS_READ_OUTSIDE_IMAGE_RANGE,
    FWCOMPS_UNSUPPORTED_DEVICE,
    FWCOMPS_MTCR_OPEN_DEVICE_ERROR,
    FWCOMPS_FAIL_TO_CREATE_TRM_CONTEXT,
    FWCOMPS_FAIL_TO_LOCK_FLASH_SEMAPHORE,
    FWCOMPS_VERIFY_FAILED,

    //MCC Return codes
    FWCOMPS_MCC_ERR_CODES = 0x100,
    FWCOMPS_MCC_ERR_ERROR = 0x101,
    FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR = 0x102,
    FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE = 0x103,
    FWCOMPS_MCC_ERR_REJECTED_UNKNOWN_KEY = 0x104,
    FWCOMPS_MCC_ERR_REJECTED_AUTH_FAILED = 0x105,
    FWCOMPS_MCC_ERR_REJECTED_UNSIGNED = 0x106,
    FWCOMPS_MCC_ERR_REJECTED_KEY_NOT_APPLICABLE = 0x107,
    FWCOMPS_MCC_ERR_REJECTED_BAD_FORMAT = 0x108,
    FWCOMPS_MCC_ERR_BLOCKED_PENDING_RESET = 0x109,
    FWCOMPS_MCC_UNEXPECTED_STATE = 0x10A,
    FWCOMPS_MCC_REJECTED_NOT_A_SECURED_FW = 0x10B,
    FWCOMPS_MCC_REJECTED_MFG_BASE_MAC_NOT_LISTED = 0x10C,
    FWCOMPS_MCC_REJECTED_NO_DEBUG_TOKEN = 0x10D,
    FWCOMPS_MCC_REJECTED_VERSION_NUM_MISMATCH = 0x10E,
    FWCOMPS_MCC_REJECTED_USER_TIMESTAMP_MISMATCH = 0x10F,
    FWCOMPS_MCC_REJECTED_FORBIDDEN_VERSION = 0x110,
    FWCOMPS_MCC_FLASH_ERASE_ERROR = 0x111,
    FWCOMPS_MCC_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION = 0x112,
    FWCOMPS_MCC_REJECTED_LINKX_TYPE_NOT_SUPPORTED = 0x113,
    FWCOMPS_MCC_REJECTED_HOST_STORAGE_IN_USE = 0x114,
    FWCOMPS_MCC_REJECTED_LINKX_TRANSFER = 0x115,
    FWCOMPS_MCC_REJECTED_LINKX_ACTIVATE = 0x116,
    FWCOMPS_MCC_REJECTED_INCOMPATIBLE_FLASH = 0x117,

    // errors regarding REG_ACCESS
    FWCOMPS_REG_ACCESS_OK = 0,
    FWCOMPS_REG_ACCESS_BAD_STATUS_ERR = 0x200,
    FWCOMPS_REG_ACCESS_BAD_METHOD,
    FWCOMPS_REG_ACCESS_NOT_SUPPORTED,
    FWCOMPS_REG_ACCESS_DEV_BUSY,
    FWCOMPS_REG_ACCESS_VER_NOT_SUPP,
    FWCOMPS_REG_ACCESS_UNKNOWN_TLV,
    FWCOMPS_REG_ACCESS_REG_NOT_SUPP,
    FWCOMPS_REG_ACCESS_CLASS_NOT_SUPP,
    FWCOMPS_REG_ACCESS_METHOD_NOT_SUPP,
    FWCOMPS_REG_ACCESS_BAD_PARAM,
    FWCOMPS_REG_ACCESS_RES_NOT_AVLBL,
    FWCOMPS_REG_ACCESS_MSG_RECPT_ACK,
    FWCOMPS_REG_ACCESS_UNKNOWN_ERR,
    FWCOMPS_REG_ACCESS_SIZE_EXCCEEDS_LIMIT,
    FWCOMPS_REG_ACCESS_CONF_CORRUPT,
    FWCOMPS_REG_ACCESS_LEN_TOO_SMALL,
    FWCOMPS_REG_ACCESS_BAD_CONFIG,
    FWCOMPS_REG_ACCESS_ERASE_EXEEDED,
    FWCOMPS_REG_ACCESS_INTERNAL_ERROR,

    FWCOMPS_IMAGE_REACTIVATION_SUCCESS = 0x300,
    FWCOMPS_IMAGE_REACTIVATION_BUSY,
    FWCOMPS_IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR,
    FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_COPY_FAILED,
    FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED,
    FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED,
    FWCOMPS_IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED,
    FWCOMPS_IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED,
    FWCOMPS_IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED,
    FWCOMPS_IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED,
    FWCOMPS_IMAGE_REACTIVATION_FW_NOT_SUPPORTED,
    FWCOMPS_IMAGE_REACTIVATION_UNKNOWN_ERROR,
    FWCOMPS_IMAGE_REACTIVATION_WAITING_TIME_EXPIRED
} fw_comps_error_t;


typedef enum {
    FSM_QUERY = 0,
    FSM_CMD_LOCK_UPDATE_HANDLE          = 0x1,
    FSM_CMD_RELEASE_UPDATE_HANDLE       = 0x2,
    FSM_CMD_UPDATE_COMPONENT            = 0x3,
    FSM_CMD_VERIFY_COMPONENT            = 0x4,
    FSM_CMD_ACTIVATE_COMPONENET         = 0x5,
    FSM_CMD_ACTIVATE_ALL                = 0x6,
    FSM_CMD_READ_COMPONENT              = 0x7,
    FSM_CMD_CANCEL                      = 0x8,
    FSM_CMD_CHECK_UPDATE_HANDLE         = 0x9,
    FSM_CMD_FORCE_HANDLE_RELEASE        = 0xA,
    FSM_CMD_READ_PENDING_COMPONENT      = 0xB,
    FSM_CMD_DOWNSTREAM_DEVICE_TRANSFER  = 0xC,
    FSM_CMD_UNDEFINED                   = 0xFF,
} fsm_command_t;

typedef enum
{
    FMPT_FIRST_PAGE = 0,
    FMPT_SECOND_PAGE,
    FMPT_MAILBOX_PAGE,
    FMPT_ALLOCATED_LIST_LENGTH
}fsm_memory_page_index_t;

typedef enum
{
    FFS_FW_UNKNOWN = 0,
    FFS_FW_BUSY = 1,
    FFS_FW_OK,
    FFS_FW_ERROR
}fsm_fw_status_t;

class AbstractComponentAccess;
class FwCompsMgr {
public:

    typedef enum {
        MQIS_REGISTER_FIRST_VALUE = 1,
        MQIS_REGISTER_DEVICE_NAME = MQIS_REGISTER_FIRST_VALUE,
        MQIS_REGISTER_DEVICE_DESCRIPTION_INFO = 2,
        MQIS_REGISTER_IMAGE_VSD = 3,
        MQIS_REGISTER_DEVICE_VSD = 4,
        MQIS_REGISTER_ROM_INFO = 5,
        MQIS_REGISTER_LAST_VALUE = MQIS_REGISTER_ROM_INFO
    } MQISDeviceDescriptionT;

    typedef enum {
        DEVICE_HCA_SWITCH = 0,
        DEVICE_GEARBOX = 1
    } DeviceTypeT;

    FwCompsMgr(const char *devname, DeviceTypeT devType = DEVICE_HCA_SWITCH, int deviceIndex = 0);
    FwCompsMgr(mfile *mf, DeviceTypeT devType = DEVICE_HCA_SWITCH, int deviceIndex = 0);
    FwCompsMgr(uefi_Dev_t *uefi_dev, uefi_dev_extra_t *uefi_extra);
    virtual ~FwCompsMgr();

    u_int32_t        getFwSupport();
    mfile*           getMfileObj() { return _mf; };
    bool    fwReactivateImage();
    bool    burnComponents(std::vector<FwComponent>& comps,
                           ProgressCallBackAdvSt *progressFuncAdv = (ProgressCallBackAdvSt *)NULL);
    bool    getFwComponents(std::vector<FwComponent>& comps, bool readEn = false);
    bool    readComponent(FwComponent::comps_ids_t compType,
                          FwComponent& fwComp,
                          bool readPending = false,
                          ProgressCallBackAdvSt *progressFuncAdv = (ProgressCallBackAdvSt *)NULL);
    bool    queryFwInfo(fwInfoT *query, bool next_boot_fw_ver = false);
    bool    forceRelease();
    fw_comps_error_t getLastError() { return _lastError; };
    unsigned char*      getLastErrMsg();
    bool    readBlockFromComponent(FwComponent::comps_ids_t compId,
                                   u_int32_t offset,
                                   u_int32_t size,
                                   std::vector<u_int8_t>& data);
    bool    setMacsGuids(mac_guid_t macGuid);
    bool    getDeviceHWInfo(FwCompsMgr::MQISDeviceDescriptionT op,
                            vector<u_int8_t>& infoString);
    void    deal_with_signal();
    void   setLastFirmwareError(fw_comps_error_t fw_error);
    void   setLastRegisterAccessStatus(reg_access_status_t err);
    fw_comps_error_t mccErrTrans(u_int8_t err);
    fw_comps_error_t regErrTrans(reg_access_status_t err);
    bool lock_flash_semaphore();
    void unlock_flash_semaphore();
    void SetIndexAndSize(int deviceIndex, int deviceSize, bool autoUpdate = false, bool activationNeeded = true, bool downloadTransferNeeded = true, int activate_delay_sec = 0);
    bool RefreshComponentsStatus(comp_status_st* ComponentStatus = NULL);
    bool GetComponentLinkxProperties(FwComponent::comps_ids_t compType, component_linkx_st *cmpLinkX);
    void GenerateHandle();
    bool isMCDDSupported() { return isDmaSupported; };
private:

    typedef enum {
        FSMST_IDLE                          = 0x0,
        FSMST_LOCKED                        = 0x1,
        FSMST_INITIALIZE                    = 0x2,
        FSMST_DOWNLOAD                      = 0x3,
        FSMST_VERIFY                        = 0x4,
        FSMST_APPLY                         = 0x5,
        FSMST_ACTIVATE                      = 0x6,
        FSMST_UPLOAD                        = 0x7,
        FSMST_UPLOAD_PENDING                = 0x8,
        FSMST_DOWNSTREAM_DEVICE_TRANSFER    = 0x9,
        FSMST_NA                            = 0xFF,
    } fsm_state_t;

    typedef struct control_fsm_args {
        control_fsm_args() : command(FSM_CMD_UNDEFINED), expectedState(FSMST_NA), size(0),
            currentState(FSMST_NA), progressFuncAdv(NULL), reg_access_timeout(0) {}
        fsm_command_t command;
        fsm_state_t expectedState;
        u_int32_t size;
        fsm_state_t currentState;
        ProgressCallBackAdvSt *progressFuncAdv;
        u_int32_t reg_access_timeout;
    } control_fsm_args_t;

    typedef enum {
        MCC_ERRCODE_OK = 0x0,
        MCC_ERRCODE_ERROR = 0x1,
        MCC_ERRCODE_REJECTED_DIGEST_ERR = 0x2,
        MCC_ERRCODE_REJECTED_NOT_APPLICABLE = 0x3,
        MCC_ERRCODE_REJECTED_UNKNOWN_KEY = 0x4,
        MCC_ERRCODE_REJECTED_AUTH_FAILED = 0x5,
        MCC_ERRCODE_REJECTED_UNSIGNED = 0x6,
        MCC_ERRCODE_REJECTED_KEY_NOT_APPLICABLE = 0x7,
        MCC_ERRCODE_REJECTED_BAD_FORMAT = 0x8,
        MCC_ERRCODE_BLOCKED_PENDING_RESET = 0x9,
        MCC_ERRCODE_REJECTED_NOT_A_SECURED_FW = 0xA,
        MCC_ERRCODE_REJECTED_MFG_BASE_MAC_NOT_LISTED = 0xB,
        MCC_ERRCODE_REJECTED_NO_DEBUG_TOKEN = 0xC,
        MCC_ERRCODE_REJECTED_VERSION_NUM_MISMATCH = 0xD,
        MCC_ERRCODE_REJECTED_USER_TIMESTAMP_MISMATCH = 0xE,
        MCC_ERRCODE_REJECTED_FORBIDDEN_VERSION = 0xF,
        MCC_ERRCODE_FLASH_ERASE_ERROR = 0x10,
        MCC_ERRCODE_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION = 0x11,
        MCC_ERRCODE_REJECTED_LINKX_TYPE_NOT_SUPPORTED = 0x12,
        MCC_ERRCODE_REJECTED_HOST_STORAGE_IN_USE = 0x13,
        MCC_ERRCODE_REJECTED_LINKX_TRANSFER = 0x14,
        MCC_ERRCODE_REJECTED_LINKX_ACTIVATE = 0x15,
        MCC_ERRCODE_REJECTED_INCOMPATIBLE_FLASH = 0x16
    } mcc_command_error_t;

    typedef enum {
        IMAGE_REACTIVATION_SUCCESS = 0,
        IMAGE_REACTIVATION_BUSY = 1,
        IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR = 2,
        IMAGE_REACTIVATION_FIRST_PAGE_COPY_FAILED = 3,
        IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED = 4,
        IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED = 5,
        IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED = 6,
        IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED = 7,
        IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED = 8,
        IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED = 9
    }image_reactivation_command_error_t;

    const char* stateToStr(fsm_state_t);
    const char* commandToStr(fsm_command_t cmd);

    void          initialize(mfile *mf);



    bool          accessComponent(u_int32_t offset,
                                  u_int32_t size,
                                  u_int32_t data[],
                                  access_type_t access,
                                  ProgressCallBackAdvSt *progressFuncAdv = (ProgressCallBackAdvSt *)NULL,
                                  control_fsm_args_t* lastFsmCommandArgs = NULL);

    bool           queryComponentStatus(u_int32_t componentIndex,
                                       comp_status_st *query);

    bool    getComponentVersion(FwComponent::comps_ids_t compType,
        bool pending,
        component_version_st *cmpVer);
    
    bool           controlFsm(fsm_command_t command,
                              fsm_state_t expectedState = FSMST_NA,
                              u_int32_t size = 0,
                              fsm_state_t currentState = FSMST_NA,
                              ProgressCallBackAdvSt *progressFuncAdv = (ProgressCallBackAdvSt *)NULL,
                              u_int32_t reg_access_timeout = 0);

    bool           queryComponentInfo(u_int32_t componentIndex,
                                      u_int8_t readPending,
                                      u_int32_t infoType,
                                      u_int32_t dataSize,
                                      u_int32_t *data);

    bool           runMCQI(u_int32_t componentIndex,
                           u_int8_t readPending,
                           u_int32_t infoType,
                           u_int32_t dataSize,
                           u_int32_t offset,
                           u_int32_t *data);

    bool          runNVDA(std::vector<u_int8_t>& buff,
                          u_int16_t len,
                          u_int32_t tlvType,
                          reg_access_method_t method,
                          bool queryDefault);

    bool           readComponentInfo(FwComponent::comps_ids_t compType,
                                     comp_info_t infoType,
                                     std::vector<u_int32_t>& retData,
                                     bool readPending = false);

    void           getInfoAsVersion(std::vector<u_int32_t>& infoData,
                                    component_version_st *cmpVer);

    reg_access_status_t getGI(mfile *mf, mgirReg *gi);
    bool           extractMacsGuids(fwInfoT *fwQuery);
    void           extractRomInfo(mgirReg *mgir, fwInfoT *fwQuery);
    bool           isDMAAccess();
    bool           fallbackToRegisterAccess();
    
    std::vector<comp_query_st> _compsQueryMap;
    bool _refreshed;
    bool _clearSetEnv;
    bool _openedMfile;
    comp_query_st *_currCompQuery;
    comp_info_st _currCompInfo;
    u_int32_t _updateHandle;
    fsm_control_st _lastFsmCtrl;
    u_int32_t _componentIndex;
    u_int32_t _deviceIndex;
    u_int8_t _deviceType;
    u_int8_t _mircCaps;
    fw_comps_error_t _lastError;
    reg_access_status_t _lastRegAccessStatus;
    u_int32_t _hwDevId;
    mfile *_mf;
    const char *_currComponentStr;
    std::vector<u_int8_t> _productVerStr;
    bool isDmaSupported;
    AbstractComponentAccess* _accessObj;
    int _linkXDeviceSize;
    int _linkXDeviceIndex;
    bool _autoUpdate;
    bool _linkXFlow;
    bool _activationNeeded;
    bool _downloadTransferNeeded;
    u_int8_t _activation_delay_sec;
    int _rejectedIndex;
    bool _isDelayedActivationCommandSent;
#ifndef UEFI_BUILD
    trm_ctx _trm;
#endif
};
#endif /* USER_MLXFWOPS_LIB_FW_COMPS_MGR_H_ */
