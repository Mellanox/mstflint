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
#include <string>
#include <map>
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
#define DPRINTF(args)                               \
    do                                              \
    {                                               \
        char* reacDebug = getenv("FW_COMPS_DEBUG"); \
        if (reacDebug != NULL)                      \
        {                                           \
            printf("\33[2K\r");                     \
            printf("%s:%d: ", __FILE__, __LINE__);  \
            printf args;                            \
            fflush(stdout);                         \
        }                                           \
    } while (0)
#else
#define DPRINTF(...)
#endif
typedef struct reg_access_hca_mqis_reg_ext mqisReg;
typedef struct reg_access_hca_mcqs_reg_ext comp_status_st;
typedef struct reg_access_hca_mcqi_reg_ext comp_info_st;
typedef struct reg_access_hca_mcc_reg_ext fsm_control_st;
typedef struct reg_access_hca_mcqi_cap_ext comp_cap_st;
typedef struct reg_access_hca_mgir_ext mgirReg;

typedef struct reg_access_hca_mcqi_version_ext component_version_st;
typedef struct reg_access_hca_mcqi_linkx_properties_ext component_linkx_st;
typedef struct reg_access_hca_mcqi_clock_source_properties_ext component_synce_st;

typedef int (*ProgressFunc)(int completion);

typedef f_prog_func_adv_st ProgressCallBackAdvSt;

struct uid_entry
{
    u_int16_t num_allocated;
    u_int64_t uid;
};

typedef struct
{
    u_int8_t type;
    u_int8_t arch;
    reg_access_hca_rom_version_ext version;
} mgirRomInfo;

typedef struct
{
    u_int8_t secure_fw;
    u_int8_t signed_fw;
    u_int8_t debug_fw;
    u_int8_t dev_fw;
} security_fw_t;

typedef struct
{
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
    u_int32_t ini_file_version;
    u_int8_t geo_address;
    bool geo_address_valid;
    uint8_t independent_module;
    uint8_t pci_switch_only_mode;
    uint8_t pci_switch_only_mode_valid;

} fwInfoT;

typedef struct
{
    comp_status_st comp_status;
    comp_cap_st comp_cap;
    int valid;
} comp_query_st;

typedef enum
{
    MCC_READ_COMP = 0x0,
    MCC_WRITE_COMP
} access_type_t;

typedef struct mac_guid
{
    guid_t mac;
    guid_t guid;
} mac_guid_t;

typedef enum
{
    COMPINFO_CAPABILITIES = 0,
    COMPINFO_VERSIONS = 1,
    COMPINFO_PUBLIC_KEYS = 2,
    COMPINFO_FORBIDDEN_VERSION = 3,
    COMPINFO_ACTIVATION_METHOD = 5,
    COMPINFO_LINKX_PROPERTIES = 6,
    COMPINFO_CLOCK_SOURCE_PROPERTIES = 7,
    COMPINFO_DPA_APPS_INFO = 9
} comp_info_t;

class FwComponent
{
public:
    typedef enum
    {
        COMPID_FIRST_IDX = 0x1,
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
        COMPID_CRCS_TOKEN = 0x10,
        COMPID_CRDT_TOKEN = 0x11,
        COMPID_CLOCK_SYNC_EEPROM = 0x12,
        DIGITAL_CACERT = 0x15,
        DIGITAL_CACERT_CHAIN = 0x16,
        DIGITAL_CACERT_REMOVAL = 0x17,
        DIGITAL_CACERT_CHAIN_REMOVAL = 0x18,
        COMPID_LINKX_ELS = 0x1A,
        COMPID_BFB = 0x1B,
        DPA_COMPONENT = 0x1C,
        DPA_COMPONENT_REMOVAL = 0x1D,
        COMPID_LAST_IDX = 0x1E,
        COMPID_UNKNOWN = 0xFFFF,
    } comps_ids_t;

    typedef enum
    {
        COMPSTAT_NOT_PRESENT = 0x0,
        COMPSTAT_PRESENT = 0x1,
        COMPSTAT_IN_USE = 0x2,
        COMPSTAT_UNKNOWN = 0xff
    } comps_status_t;

    FwComponent() :
        _size(0), _type(COMPID_UNKNOWN), _componentIndex(0xffffffff), _initialized(false), _status(COMPSTAT_UNKNOWN){};
    FwComponent(comps_ids_t compId) :
        _size(0), _type(compId), _componentIndex(0xffffffff), _initialized(false), _status(COMPSTAT_UNKNOWN){};
    FwComponent(comps_ids_t compId, comps_status_t compStat) :
        _size(0), _type(compId), _componentIndex(0xffffffff), _initialized(false), _status(compStat){};
    ~FwComponent(){};

    bool init(const std::vector<u_int8_t>& buff, u_int32_t size, comps_ids_t type, u_int32_t idx = 0xffffffff);
    std::vector<u_int8_t>& getData() { return _data; };
    u_int32_t getSize() { return _size; };
    comps_ids_t getType() { return _type; };
    comps_status_t getStatus() { return _status; };

    void setData(const std::vector<u_int8_t>& buff) { _data = buff; };
    void setSize(u_int32_t size) { _size = size; };
    void setType(comps_ids_t compId) { _type = compId; };
    void setStatus(comps_status_t compStat) { _status = compStat; };

    static const char* getCompIdStr(comps_ids_t compId);
    static comps_ids_t getCompId(string compId);

private:
    std::vector<u_int8_t> _data;
    u_int32_t _size;
    comps_ids_t _type;
    u_int32_t _componentIndex;
    bool _initialized;
    comps_status_t _status;
};

class MccErrorCodes
{
public:
    typedef enum
    {
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
        MCC_ERRCODE_REJECTED_REBURN_RUNNING_AND_RETRY = 0x11,
        MCC_ERRCODE_REJECTED_LINKX_TYPE_NOT_SUPPORTED = 0x12,
        MCC_ERRCODE_REJECTED_HOST_STORAGE_IN_USE = 0x13,
        MCC_ERRCODE_REJECTED_LINKX_TRANSFER = 0x14,
        MCC_ERRCODE_REJECTED_LINKX_ACTIVATE = 0x15,
        MCC_ERRCODE_REJECTED_INCOMPATIBLE_FLASH = 0x16,
        MCC_ERRCODE_REJECTED_TOKEN_ALREADY_APPLIED = 0x17,
        MCC_ERRCODE_REJECTED_FW_BURN_DRAM_NOT_AVAILABLE = 0x18,
        MCC_ERRCODE_FW_BURN_REJECTED_INVALID_SECURITY_VERSION = 0x19,
        MCC_ERRCODE_FW_BURN_REJECTED_CERT_CER509 = 0x1A,
        MCC_ERRCODE_FW_BURN_REJECTED_CERT_SIGNATURE = 0x1B,
        MCC_ERRCODE_FW_BURN_REJECTED_CERT_METADATA = 0x1C,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_0 = 0x1D,
        MCC_ERRCODE_FW_BURN_REJECTED_NO_PLACE = 0x1E,
        MCC_ERRCODE_FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD = 0x1F,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_1 = 0x20,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_2 = 0x21,
        MCC_ERRCODE_FW_BURN_REJECTED_NUM_OF_SWAP = 0x22,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_3 = 0x23,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_4 = 0x24,
        MCC_ERRCODE_FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD = 0x25,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_5 = 0x26,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_6 = 0x27,
        MCC_ERRCODE_FW_BURN_REJECTED_FLASH_WRITE_PROTECTED = 0x28,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_7 = 0x29,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_8 = 0x2A,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_9 = 0x2B,
        MCC_ERRCODE_FW_BURN_REJECTED_DPA_ELF = 0x2C,
        MCC_ERRCODE_FW_BURN_REJECTED_DPA_CRYPTO_BLOB = 0x2D,
        MCC_ERRCODE_FW_BURN_REJECTED_DPA_APP_METADATA = 0x2E,
        MCC_ERRCODE_FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE = 0x2F,
        MCC_ERRCODE_FW_BURN_REJECTED_DPA_CONTAINER_VERIFY = 0x30,
        MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_10 = 0x31
     } mcc_command_error_t;
 };

typedef enum
{
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
    FWCOMPS_DEVICE_NOT_PRESENT,
    FWCOMPS_COMP_BLOCKED,

    // MCC Return codes
    FWCOMPS_MCC_ERR_CODES = 0x100,
    FWCOMPS_MCC_ERR_ERROR = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_ERROR,
    FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_DIGEST_ERR,
    FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE =
     FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_NOT_APPLICABLE,
    FWCOMPS_MCC_ERR_REJECTED_UNKNOWN_KEY = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_UNKNOWN_KEY,
    FWCOMPS_MCC_ERR_REJECTED_AUTH_FAILED = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_AUTH_FAILED,
    FWCOMPS_MCC_ERR_REJECTED_UNSIGNED = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_UNSIGNED,
    FWCOMPS_MCC_ERR_REJECTED_KEY_NOT_APPLICABLE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_KEY_NOT_APPLICABLE,
    FWCOMPS_MCC_ERR_REJECTED_BAD_FORMAT = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_BAD_FORMAT,
    FWCOMPS_MCC_ERR_BLOCKED_PENDING_RESET = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_BLOCKED_PENDING_RESET,
    FWCOMPS_MCC_REJECTED_NOT_A_SECURED_FW =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_NOT_A_SECURED_FW,
    FWCOMPS_MCC_REJECTED_MFG_BASE_MAC_NOT_LISTED =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_MFG_BASE_MAC_NOT_LISTED,
    FWCOMPS_MCC_REJECTED_NO_DEBUG_TOKEN = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_NO_DEBUG_TOKEN,
    FWCOMPS_MCC_REJECTED_VERSION_NUM_MISMATCH =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_VERSION_NUM_MISMATCH,
    FWCOMPS_MCC_REJECTED_USER_TIMESTAMP_MISMATCH =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_USER_TIMESTAMP_MISMATCH,
    FWCOMPS_MCC_REJECTED_FORBIDDEN_VERSION =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_FORBIDDEN_VERSION,
    FWCOMPS_MCC_FLASH_ERASE_ERROR = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FLASH_ERASE_ERROR,
    FWCOMPS_MCC_REJECTED_REBURN_RUNNING_AND_RETRY =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_REBURN_RUNNING_AND_RETRY,
    FWCOMPS_MCC_REJECTED_LINKX_TYPE_NOT_SUPPORTED =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_LINKX_TYPE_NOT_SUPPORTED,
    FWCOMPS_MCC_REJECTED_HOST_STORAGE_IN_USE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_HOST_STORAGE_IN_USE,
    FWCOMPS_MCC_REJECTED_LINKX_TRANSFER = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_LINKX_TRANSFER,
    FWCOMPS_MCC_REJECTED_LINKX_ACTIVATE = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_LINKX_ACTIVATE,
    FWCOMPS_MCC_REJECTED_INCOMPATIBLE_FLASH =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_INCOMPATIBLE_FLASH,
    FWCOMPS_MCC_REJECTED_TOKEN_ALREADY_APPLIED =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_TOKEN_ALREADY_APPLIED,
    FWCOMPS_MCC_REJECTED_FW_BURN_DRAM_NOT_AVAILABLE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_REJECTED_FW_BURN_DRAM_NOT_AVAILABLE,
    FWCOMPS_MCC_FW_BURN_REJECTED_INVALID_SECURITY_VERSION =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INVALID_SECURITY_VERSION,
    FWCOMPS_MCC_FW_BURN_REJECTED_CERT_CER509 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_CERT_CER509,
    FWCOMPS_MCC_FW_BURN_REJECTED_CERT_SIGNATURE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_CERT_SIGNATURE,
    FWCOMPS_MCC_FW_BURN_REJECTED_CERT_METADATA =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_CERT_METADATA,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_0 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_0,
    FWCOMPS_MCC_FW_BURN_REJECTED_NO_PLACE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_NO_PLACE,
    FWCOMPS_MCC_FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_1 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_1,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_2 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_2,
    FWCOMPS_MCC_FW_BURN_REJECTED_NUM_OF_SWAP =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_NUM_OF_SWAP,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_3 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_3,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_4 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_4,
    FWCOMPS_MCC_FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_5 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_5,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_6 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_6,
    FWCOMPS_MCC_FW_BURN_REJECTED_FLASH_WRITE_PROTECTED =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_FLASH_WRITE_PROTECTED,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_7 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_7,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_8 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_8,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_9 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_9,
    FWCOMPS_MCC_FW_BURN_REJECTED_DPA_ELF = FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_DPA_ELF,
    FWCOMPS_MCC_FW_BURN_REJECTED_DPA_CRYPTO_BLOB =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_DPA_CRYPTO_BLOB,
    FWCOMPS_MCC_FW_BURN_REJECTED_DPA_APP_METADATA =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_DPA_APP_METADATA,
    FWCOMPS_MCC_FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE,
    FWCOMPS_MCC_FW_BURN_REJECTED_DPA_CONTAINER_VERIFY =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_DPA_CONTAINER_VERIFY,
    FWCOMPS_MCC_FW_BURN_REJECTED_INTERNAL_ERROR_10 =
      FWCOMPS_MCC_ERR_CODES + MccErrorCodes::MCC_ERRCODE_FW_BURN_REJECTED_INTERNAL_ERROR_10,
    FWCOMPS_MCC_UNEXPECTED_STATE = 0x1FF,
 
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

typedef enum
{
    FWCOMPS_MCC_WARNING_OK = 0x0,
    FWCOMPS_MCC_WARNING_DPA_API_OS_INCOMPATIBLE = 0x1,
    FWCOMPS_MCC_WARNING_DPA_API_FW_INCOMPATIBLE = 0x2
} fw_comps_warning_t;

typedef enum
{
    FSM_QUERY = 0,
    FSM_CMD_LOCK_UPDATE_HANDLE = 0x1,
    FSM_CMD_RELEASE_UPDATE_HANDLE = 0x2,
    FSM_CMD_UPDATE_COMPONENT = 0x3,
    FSM_CMD_VERIFY_COMPONENT = 0x4,
    FSM_CMD_ACTIVATE_COMPONENET = 0x5,
    FSM_CMD_ACTIVATE_ALL = 0x6,
    FSM_CMD_READ_COMPONENT = 0x7,
    FSM_CMD_CANCEL = 0x8,
    FSM_CMD_CHECK_UPDATE_HANDLE = 0x9,
    FSM_CMD_FORCE_HANDLE_RELEASE = 0xA,
    FSM_CMD_READ_PENDING_COMPONENT = 0xB,
    FSM_CMD_DOWNSTREAM_DEVICE_TRANSFER = 0xC,
    FSM_CMD_UNDEFINED = 0xFF,
} fsm_command_t;

typedef enum
{
    FMPT_FIRST_PAGE = 0,
    FMPT_SECOND_PAGE,
    FMPT_MAILBOX_PAGE,
    FMPT_ALLOCATED_LIST_LENGTH
} fsm_memory_page_index_t;

typedef enum
{
    FFS_FW_UNKNOWN = 0,
    FFS_FW_BUSY = 1,
    FFS_FW_OK,
    FFS_FW_ERROR
} fsm_fw_status_t;

class AbstractComponentAccess;
class FwCompsMgr
{
public:
    typedef enum
    {
        MQIS_REGISTER_FIRST_VALUE = 1,
        MQIS_REGISTER_DEVICE_NAME = MQIS_REGISTER_FIRST_VALUE,
        MQIS_REGISTER_DEVICE_DESCRIPTION_INFO = 2,
        MQIS_REGISTER_IMAGE_VSD = 3,
        MQIS_REGISTER_DEVICE_VSD = 4,
        MQIS_REGISTER_ROM_INFO = 5,
        MQIS_REGISTER_LAST_VALUE = MQIS_REGISTER_ROM_INFO
    } MQISDeviceDescriptionT;

    typedef enum
    {
        DEVICE_HCA_SWITCH = 0,
        DEVICE_GEARBOX = 1,
        DEVICE_UNKNOWN
    } DeviceTypeT;

    FwCompsMgr(const char* devname, DeviceTypeT devType = DEVICE_HCA_SWITCH, int deviceIndex = 0);
    FwCompsMgr(mfile* mf, DeviceTypeT devType = DEVICE_HCA_SWITCH, int deviceIndex = 0);
    FwCompsMgr(uefi_Dev_t* uefi_dev, uefi_dev_extra_t* uefi_extra);
    virtual ~FwCompsMgr();

    u_int32_t getFwSupport();
    mfile* getMfileObj() { return _mf; };
    bool fwReactivateImage();
    bool burnComponents(FwComponent& comp, ProgressCallBackAdvSt* progressFuncAdv = (ProgressCallBackAdvSt*)NULL);
    bool getFwComponents(std::vector<FwComponent>& comps, bool readEn = false);
    bool readComponent(FwComponent::comps_ids_t compType,
                       FwComponent& fwComp,
                       bool readPending = false,
                       ProgressCallBackAdvSt* progressFuncAdv = (ProgressCallBackAdvSt*)NULL);
    bool queryFwInfo(fwInfoT* query, bool next_boot_fw_ver = false);
    bool forceRelease();
    fw_comps_error_t getLastError() { return _lastError; };
    fw_comps_warning_t getWarningCode() { return _warningCode; }
    string getLastSpecificError() { return _lastSpecificError; };
    string warningCodeToString(fw_comps_warning_t warning);
    unsigned char* getLastErrMsg();
    bool readBlockFromComponent(FwComponent::comps_ids_t compId,
                                u_int32_t offset,
                                u_int32_t size,
                                std::vector<u_int8_t>& data);
    bool setMacsGuids(mac_guid_t macGuid);
    bool getDeviceHWInfo(FwCompsMgr::MQISDeviceDescriptionT op, vector<u_int8_t>& infoString);
    void deal_with_signal();
    void setLastFirmwareError(fw_comps_error_t fw_error);
    void setLastRegisterAccessStatus(reg_access_status_t err);
    fw_comps_error_t mccErrTrans(u_int8_t err);
    fw_comps_error_t regErrTrans(reg_access_status_t err);
    bool lock_flash_semaphore();
    void unlock_flash_semaphore();
    void SetIndexAndSize(int deviceIndex,
                         int deviceSize,
                         bool autoUpdate = false,
                         bool activationNeeded = true,
                         bool downloadTransferNeeded = true,
                         int activate_delay_sec = 0);
    void SetActivationStep(bool activationNeeded) { _activationNeeded = activationNeeded; }
    bool RefreshComponentsStatus(comp_status_st* ComponentStatus = NULL);
    bool GetComponentLinkxProperties(FwComponent::comps_ids_t compType, component_linkx_st* cmpLinkX);
    bool GetComponentSyncEProperties(component_synce_st& cmpSyncE);
    bool GetComponentInfo(FwComponent::comps_ids_t compType, vector<u_int8_t>& data);
    bool GetComponentInfo(FwComponent::comps_ids_t compType, u_int32_t deviceIndex, vector<u_int8_t>& data);
    void GenerateHandle();
    bool isMCDDSupported() { return _isDmaSupported; };
    bool IsSecondaryHost(bool& isSecondary);
    bool runPGUID(reg_access_hca_pguid_reg_ext* guidsInfo,
                  u_int32_t local_port = 0,
                  u_int8_t pnat = 0,
                  u_int32_t lp_msb = 0);
    bool queryPGUID(fw_info_t* fwInfo, u_int32_t local_port = 0, u_int8_t pnat = 0, u_int32_t lp_msb = 0);
    u_int8_t GetSecureHostState() { return _secureHostState; }
    bool IsDevicePresent(FwComponent::comps_ids_t compType);
    bool IsCfgComponentType(FwComponent::comps_ids_t type);

    bool isSpecificError = false;
    bool queryMISOC(std::string& version, u_int32_t type, u_int32_t query_pending);
    bool runMISOC(reg_access_hca_misoc_reg_ext* bfb_component, u_int32_t type, u_int32_t query_pending);
    bool AddElsPortOffset(int& elsOffsetIndex);

private:
    typedef enum
    {
        FSMST_IDLE = 0x0,
        FSMST_LOCKED = 0x1,
        FSMST_INITIALIZE = 0x2,
        FSMST_DOWNLOAD = 0x3,
        FSMST_VERIFY = 0x4,
        FSMST_APPLY = 0x5,
        FSMST_ACTIVATE = 0x6,
        FSMST_UPLOAD = 0x7,
        FSMST_UPLOAD_PENDING = 0x8,
        FSMST_DOWNSTREAM_DEVICE_TRANSFER = 0x9,
        FSMST_NA = 0xFF,
    } fsm_state_t;

    typedef struct control_fsm_args
    {
        control_fsm_args() :
            command(FSM_CMD_UNDEFINED),
            expectedState(FSMST_NA),
            size(0),
            currentState(FSMST_NA),
            progressFuncAdv(NULL),
            reg_access_timeout(0)
        {
        }
        fsm_command_t command;
        fsm_state_t expectedState;
        u_int32_t size;
        fsm_state_t currentState;
        ProgressCallBackAdvSt* progressFuncAdv;
        u_int32_t reg_access_timeout;
    } control_fsm_args_t;

    typedef enum
    {
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
    } image_reactivation_command_error_t;

    enum PackageErrorCode : u_int16_t
    {
        PKG_OK = 0,
        PKG_FW_PRODUCT_ID_ERR = 1,
        PKG_HASH_SIZE_ERR = 2,
        PKG_SIGNATURE_SIZE_ERR = 3,
        PKG_TOC_SZ_ERR = 4,
        PKG_TOC_OFFSET_ERR = 5,
        PKG_BAD_LEN_ERR = 6,
        PKG_COMPONENT_OFFSET_ERR = 7,
        PKG_COMPONENT_SIZE_ERR = 8,
        PKG_MAGIC_NUM_ERR = 9,
        PKG_HASH_ITEMS_ERR = 10,
        PKG_SIGN_ITEMS_ERR = 11,
        PKG_DESC_ERR = 12,
        PKG_CERT_DESC_ERR = 13,
        PKG_NO_HASH_SECTION_ERR = 14,
        PKG_NO_SIG_SECTION_ERR = 15,
        PKG_HASH_IDX_ERR = 16,
        PKG_SIGN_IDX_ERR = 17,
        PKG_HASH_NUM_IDX_ERR = 18,
        PKG_SIGN_NUM_IDX_ERR = 19,
        PKG_COMPONENTS_NO_OFFSET_ERR = 20,
        PKG_COMP_KIND_NOT_FOUND_ERR = 21,
        PKG_HASH_SECTION_LEN_ERR = 22,
        PKG_SIGNATURE_SECTION_LEN_ERR = 23,
        PKG_COMP_DESC_SECTION_LEN_ERR = 24,
        PKG_TOC_KIND_DUPLICATE_ERR = 25,
        PKG_COMPONENT_KIND_DUPLICATE_ERR = 26,
        PKG_TOC_KIND_INVALID_ERR = 27,
        PKG_IMG_LOAD_ADDR_ERR = 28,
        PKG_NO_TRAILER_ERR = 29,
        PKG_NO_TRAILER_HASH_ERR = 30,
        PKG_NO_TRAILER_SIG_ERR = 31,
        PKG_TRAILER_HASH_ERR = 32,
        PKG_TRAILER_SECTION_LEN_ERR = 33,
        PKG_CERTIFICATE_ERR = 34,
        PKG_COMPONENT_KIND_INVALID_ERR = 35,
        PKG_FW_UPGRADE_VERSION_ERR = 36,
        PKG_NOT_FOUND_ERR = 37,
        PKG_MAIN_FW_COMP_NOT_FOUND_ERR = 38,
        PKG_PACKAGE_SIGNATURE_ERR = 39,
        PKG_PACKAGE_SIZE_ERR = 40,
        PKG_NO_PERMISSIONS_ERR = 41,
        PKG_UNEXPECTED_VERSION_ERR = 42,
        PKG_UNEXPECTED_CID_ERR = 43,
        PKG_FORBIDDEN_DATE_ERR = 44,
        PKG_FORBIDDEN_VERSION_ERR = 45,
        PKG_FORBIDDEN_UNKNOWN_ERR = 46,
        PKG_HEADER_VERSION_ERR = 47,
        PKG_NO_AUTHENTICATOR_ERR = 48,
        PKG_AUTHENTICATOR_SECTION_HASH_ERR = 49,
        PKG_AUTHENTICATOR_SECTION_SIG_ERR = 50,
        PKG_AUTHENTICATOR_SECTION_LEN_ERR = 51,
        PKG_AUTHENTICATOR_HASH_ERR = 52,
        PKG_NON_AUTH_COMP_HASH_ERR = 53,
        PKG_NON_AUTH_COMP_ERR = 54,
        RETIMER_BOOT_ERR = 55,
        RETIMER_SIGNATURE_ERR = 56,
        RETIMER_FORBIDDEN_VERSION_ERR = 57,
        RETIMER_FW_UPDATE_ERR = 58,
        PKG_UNKNOWN_ERR
    };

    const char* stateToStr(fsm_state_t);
    const char* commandToStr(fsm_command_t cmd);

    void initialize(mfile* mf);

    bool accessComponent(u_int32_t offset,
                         u_int32_t size,
                         u_int32_t data[],
                         access_type_t access,
                         ProgressCallBackAdvSt* progressFuncAdv = (ProgressCallBackAdvSt*)NULL,
                         control_fsm_args_t* lastFsmCommandArgs = NULL);

    bool queryComponentStatus(u_int32_t componentIndex, comp_status_st* query);

    bool getComponentVersion(FwComponent::comps_ids_t compType, bool pending, component_version_st* cmpVer);

    bool controlFsm(fsm_command_t command,
                    fsm_state_t expectedState = FSMST_NA,
                    u_int32_t size = 0,
                    fsm_state_t currentState = FSMST_NA,
                    ProgressCallBackAdvSt* progressFuncAdv = (ProgressCallBackAdvSt*)NULL,
                    u_int32_t reg_access_timeout = 0);

    bool queryComponentInfo(u_int32_t componentIndex,
                            u_int8_t readPending,
                            u_int32_t infoType,
                            u_int32_t dataSize,
                            u_int32_t* data,
                            u_int32_t deviceIndex = 0x0);
    bool runMCQI(u_int32_t componentIndex,
                 u_int8_t readPending,
                 u_int32_t infoType,
                 u_int32_t dataSize,
                 u_int32_t offset,
                 u_int32_t* data,
                 u_int32_t deviceIndex = 0x0);
    bool runMNVDA(std::vector<u_int8_t>& buff,
                  u_int16_t len,
                  u_int32_t tlvType,
                  reg_access_method_t method,
                  bool queryDefault);

    bool readComponentInfo(FwComponent::comps_ids_t compType,
                           comp_info_t infoType,
                           std::vector<u_int32_t>& retData,
                           bool readPending = false);

    void getInfoAsVersion(std::vector<u_int32_t>& infoData, component_version_st* cmpVer);

    reg_access_status_t getGI(mfile* mf, mgirReg* gi);
    bool extractMacsGuids(fwInfoT* fwQuery);
    void extractRomInfo(mgirReg* mgir, fwInfoT* fwQuery);
    bool isDMAAccess();
    bool fallbackToRegisterAccess();
    static const vector<pair<PackageErrorCode, string>> _packageErrorToString;

    std::vector<comp_query_st> _compsQueryMap;
    bool _fwSupport;
    bool _handleGenerated;
    bool _refreshed;
    bool _clearSetEnv;
    bool _openedMfile;
    comp_query_st* _currCompQuery;
    comp_info_st _currCompInfo;
    u_int32_t _updateHandle;
    fsm_control_st _lastFsmCtrl;
    u_int32_t _componentIndex;
    u_int32_t _deviceIndex;
    u_int8_t _deviceType;
    u_int8_t _mircCaps;
    fw_comps_error_t _lastError;
     fw_comps_warning_t _warningCode;
     string _lastSpecificError;
    reg_access_status_t _lastRegAccessStatus;
    u_int32_t _hwDevId;
    mfile* _mf;
    const char* _currComponentStr;
    std::vector<u_int8_t> _productVerStr;
    bool _isDmaSupported;
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
    u_int8_t _secureHostState;
};
#endif /* USER_MLXFWOPS_LIB_FW_COMPS_MGR_H_ */
