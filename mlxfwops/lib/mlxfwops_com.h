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
 */

#ifndef MLXFWOP_COM_H
#define MLXFWOP_COM_H

#include <compatibility.h>
#include "tools_layouts/reg_access_hca_layouts.h"

#ifdef UEFI_BUILD
#include <mft_uefi_common.h>
#endif

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif
#define MLXFWOPCALL __cdecl

#else
#define MLXFWOP_API
#define MLXFWOPCALL
#endif

#ifndef UEFI_BUILD
#define EFIAPI
#endif

#define SWITCH_IB_HW_ID 583
#define SPECTRUM_HW_ID 585
#define SWITCH_IB2_HW_ID 587
#define QUANTUM_HW_ID 589
#define SPECTRUM2_HW_ID 590
#define SPECTRUM3_HW_ID 592
#define QUANTUM2_HW_ID 599
#define QUANTUM3_HW_ID 603
#define NVLINK6_SWITCH_ASIC_HW_ID 632
#define ARCUSE_HW_ID 45568
#define SPECTRUM4_HW_ID 596
#define SPECTRUM5_HW_ID 624
#define SPECTRUM6_HW_ID 628
#define GEARBOX_HW_ID 594
#define GB_MANAGER_HW_ID 595
#define ABIR_GB_HW_ID 598
#define CX4_HW_ID 521
#define CX4LX_HW_ID 523
#define CX5_HW_ID 525
#define CX6_HW_ID 527
#define CX6DX_HW_ID 530
#define CX6LX_HW_ID 534
#define CX7_HW_ID 536
#define CX8_HW_ID 542
#define CX8_PURE_PCIE_SWITCH_HW_ID 546
#define CX9_HW_ID 548
#define CX9_PURE_PCIE_SWITCH_HW_ID 552
#define BF_HW_ID 529
#define BF2_HW_ID 532
#define BF3_HW_ID 540
#define BF4_HW_ID 544
#define CX3_HW_ID 501
#define CX3_PRO_HW_ID 503
#define CONNECT_IB_HW_ID 511

#define INBAND_MAX_REG_SIZE 44
#define MCDA_REG_HEADER 16

typedef enum
{
    PROG_WITH_PRECENTAGE,
    PROG_WITHOUT_PRECENTAGE,
    PROG_STRING_ONLY,
    PROG_OK
} prog_t;

typedef enum
{
    FS4_LC_PRODUCTION = 0,
    FS4_LC_GA_SECURED = 1,
    FS4_LC_GA_NON_SECURED = 2,
    FS4_LC_RMA = 3
} LifeCycleFS4;

typedef enum
{
    FS5_LC_BLANK_CHIP = 0,
    FS5_LC_PRE_PRODUCTION = 4,
    FS5_LC_PRODUCTION = 6,
    FS5_LC_FAILURE_ANALYSIS = 7
} LifeCycleFS5;

#define MAX_HTOC_ENTRIES_NUM 28
#define MAX_HTOC_ENTRIES_NUM_VERSION_1 64
#define HASHES_TABLE_TAIL_SIZE 8
#define HTOC_HASH_SIZE 64

typedef int EFIAPI (*f_prog_func)(int completion);
typedef int EFIAPI (*f_prog_func_ex)(int completion, void* opaque);
typedef int EFIAPI (*f_prog_func_adv)(int completion, const char* str, prog_t, void* opaque);
typedef int (*f_prog_func_str)(char* str);

typedef struct
{
    f_prog_func_adv func;
    void* opaque;
    f_prog_func uefi_func;
} f_prog_func_adv_st;

#define VSD_LEN 208
#define PSID_LEN 16
#define PRODUCT_VER_LEN 16
#define PRS_NAME_LEN 100
#define FS3_PRS_NAME_LEN 97
#define FS4_PRS_NAME_LEN 97
#define NAME_LEN 65
#define DESCRIPTION_LEN 257
#define BRANCH_LEN 28
#define MIN_BRANCH_LEN 5

#define FREE_STR_MAX_LEN 256

#define MAX_ROMS_NUM 5
#define MAX_ROM_ERR_MSG_LEN 256
#define ROM_INFO_SIZE 12

// min version that supports Rom Modify
#define MAJOR_MOD_ROM_FW 2
#define MINOR_MOD_ROM_FW 6
#define SUBMINOR_MOD_ROM_FW 1410

// Macros
#define PRINT_PROGRESS(printFunc, arg) \
    do                                 \
    {                                  \
        if (printFunc)                 \
        {                              \
            printFunc((arg));          \
        }                              \
    } while (0)

enum
{
    MLXFW_OK = 0,
    MLXFW_ERR,
    MLXFW_MEM_ERR,
    MLXFW_ERR_IN_STR,
    MLXFW_PSID_MISMATCH_ERR,
    MLXFW_FLASH_WRITE_ERR,
    MLXFW_NO_VALID_IMAGE_ERR,
    MLXFW_MULTIPLE_VALID_IMAGES_ERR,
    MLXFW_BAD_CRC_ERR,
    MLXFW_BAD_CHECKSUM_ERR,
    MLXFW_SECTION_TOO_LARGE_ERR,
    MLXFW_SECTION_CORRUPTED_ERR,
    MLXFW_IMAGE_NOT_FS_ERR,
    MLXFW_IMAGE_TOO_LARGE_ERR,
    MLXFW_IMAGE_FORMAT_ERR,
    MLXFW_DEVICE_IMAGE_MISMATCH_ERR,
    MLXFW_IMAGE_CORRUPTED_ERR,
    MLXFW_FS_INFO_MISMATCH_ERR,
    MLXFW_DEV_ID_ERR,
    MLXFW_UNSUPPORTED_BIN_VER_ERR,
    MLXFW_NO_VALID_ITOC_ERR,
    MLXFW_NO_MFG_ERR,
    MLXFW_UNKNOWN_SECT_VER_ERR,
    MLXFW_OCR_ERR,
    MLXFW_OPEN_OCR_ERR,
    MLXFW_FW_ALREADY_UPDATED_ERR,
    MLXFW_ROM_UPDATE_IN_IMAGE_ERR,
    MLXFW_GET_SECT_ERR,
    MLXFW_UPDATE_SECT_ERR,
    MLXFW_BAD_PARAM_ERR,
    MLXFW_PRS_MISMATCH_ERR,
    MLXFW_NO_VALID_DEVICE_INFO_ERR,
    MLXFW_TWO_VALID_DEVICE_INFO_ERR,
    MLXFW_DTOC_OVERWRITE_CHUNK,
    MLXFW_FLASH_READ_ERR,
    MLXFW_UNSUPPORTED_PARAM,
    MLXFW_FS_CHECKS_ERR,

    /* MCC_EN/Secure Error Codes */
    MLXFW_BURN_REJECTED_DIGEST_ERR,
    MLXFW_BURN_REJECTED_NOT_APPLICABLE,
    MLXFW_BURN_REJECTED_UNKNOWN_KEY,
    MLXFW_BURN_REJECTED_AUTH_FAILED,
    MLXFW_BURN_REJECTED_UNSIGNED,
    MLXFW_BURN_REJECTED_KEY_NOT_APPLICABLE,
    MLXFW_BURN_REJECTED_BAD_FORMAT,
    MLXFW_BURN_BLOCKED_PENDING_RESET,
    MLXFW_REJECTED_NOT_A_SECURED_FW,
    MLXFW_REJECTED_MFG_BASE_MAC_NOT_LISTED,
    MLXFW_REJECTED_NO_DEBUG_TOKEN,
    MLXFW_REJECTED_VERSION_NUM_MISMATCH,
    MLXFW_REJECTED_USER_TIMESTAMP_MISMATCH,
    MLXFW_REJECTED_FORBIDDEN_VERSION,
    MLXFW_FLASH_ERASE_ERROR,
    MLXFW_REJECTED_REBURN_RUNNING_AND_RETRY,
    MLXFW_REJECTED_LINKX_TYPE_NOT_SUPPORTED,
    MLXFW_REJECTED_HOST_STORAGE_IN_USE,
    MLXFW_REJECTED_LINKX_TRANSFER,
    MLXFW_REJECTED_LINKX_ACTIVATE,
    MLXFW_REJECTED_INCOMPATIBLE_FLASH,
    MLXFW_REJECTED_TOKEN_ALREADY_APPLIED,
    MLXFW_REJECTED_FW_BURN_DRAM_NOT_AVAILABLE,
    MLXFW_FW_BURN_REJECTED_INVALID_SECURITY_VERSION,
    MLXFW_FW_BURN_REJECTED_CERT_CER509,
    MLXFW_FW_BURN_REJECTED_CERT_SIGNATURE,
    MLXFW_FW_BURN_REJECTED_CERT_METADATA,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_0,
    MLXFW_FW_BURN_REJECTED_NO_PLACE,
    MLXFW_FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_1,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_2,
    MLXFW_FW_BURN_REJECTED_NUM_OF_SWAP,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_3,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_4,
    MLXFW_FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_5,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_6,
    MLXFW_FW_BURN_REJECTED_FLASH_WRITE_PROTECTED,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_7,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_8,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_9,
    MLXFW_FW_BURN_REJECTED_DPA_ELF,
    MLXFW_FW_BURN_REJECTED_DPA_CRYPTO_BLOB,
    MLXFW_FW_BURN_REJECTED_DPA_APP_METADATA,
    MLXFW_FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE,
    MLXFW_FW_BURN_REJECTED_DPA_CONTAINER_VERIFY,
    MLXFW_FW_BURN_REJECTED_INTERNAL_ERROR_10,
    MLXFW_MISSING_IMAGE_SIGNATURE,
    MLXFW_FSM_UNEXPECTED_STATE,
    /* ********************/
    /* IMAGE REACTIVATION RELATED ERRORS */
    MLXFW_IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR,
    MLXFW_IMAGE_RACTIVATION_FIRST_PAGE_COPY_FAILED,
    MLXFW_IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED,
    MLXFW_IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED,
    MLXFW_IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED,
    MLXFW_IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED,
    MLXFW_IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED,
    MLXFW_IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED,
    MLXFW_IMAGE_REACTIVATION_FW_NOT_SUPPORTING,
    MLXFW_IMAGE_REACTIVATION_UNKNOWN_ERROR
};

enum
{
    GUIDS = 4,
    MACS = 2,
    MAX_GUIDS = 32
};

// needed for flint query
enum
{
    BX_NP_GUIDS = 2,
    BX_SYS_GUIDS = 1,
    BX_GUIDS = BX_NP_GUIDS + BX_SYS_GUIDS,
    BX_IMACS = 3,
    BX_EMACS = 4,
    BX_MACS = BX_EMACS + BX_IMACS,
    BX_WWPNS = 4,
    BX_WWNNS = 1,
    BX_SLICE_GUIDS = BX_WWNNS + BX_WWPNS + BX_MACS + BX_NP_GUIDS,

    BX_ALL_GUIDS = (2 * BX_SLICE_GUIDS) + BX_SYS_GUIDS,
    BX_SLICES_NUM = 2,
};

enum
{
    BI_IMACS = 0,
    BI_EMACS = BI_IMACS + BX_IMACS,
    BI_WWPNS = BI_EMACS + BX_EMACS,
    BI_GUIDS = BI_WWPNS + BX_WWPNS,
    BI_WWNNS = BI_GUIDS + BX_NP_GUIDS,
    BI_SYS_GUID = BX_ALL_GUIDS - 1,
};

typedef enum security_mode_mask
{
    SMM_MCC_EN = 0x1,
    SMM_DEBUG_FW = 0x1 << 1,
    SMM_SIGNED_FW = 0x1 << 2,
    SMM_SECURE_FW = 0x1 << 3,
    SMM_DEV_FW = 0x1 << 4,
    SMM_CS_TOKEN = 0x1 << 5,
    SMM_DBG_TOKEN = 0x1 << 6,
    SMM_CRYTO_TO_COMMISSIONING = 0x1 << 7,
    SMM_RMCS_TOKEN = 0x1 << 8,
    SMM_RMDT_TOKEN = 0x1 << 9
} security_mode_mask_t;

typedef enum security_mode
{
    SM_NONE = 0x0,
    SM_SHA_DIGEST = SMM_MCC_EN,
    SM_SIGNED_IMAGE = SMM_MCC_EN | SMM_SIGNED_FW,
    SM_SECURE_FW = SMM_MCC_EN | SMM_SIGNED_FW | SMM_SECURE_FW,
    SM_DEBUG_FW = SMM_MCC_EN | SMM_SIGNED_FW | SMM_SECURE_FW | SMM_DEBUG_FW
} security_mode_t;

typedef enum chip_type
{
    CT_UNKNOWN = 0,
    CT_CONNECTX,
    CT_CONNECT_IB,
    CT_SWITCH_IB,
    CT_SPECTRUM,
    CT_CONNECTX4,
    CT_CONNECTX4_LX,
    CT_SWITCH_IB2,
    CT_CONNECTX5,
    CT_CONNECTX6,
    CT_BLUEFIELD,
    CT_QUANTUM,
    CT_SPECTRUM2,
    CT_CONNECTX6DX,
    CT_CONNECTX6LX,
    CT_CONNECTX7,
    CT_CONNECTX8,
    CT_CONNECTX8_PURE_PCIE_SWITCH,
    CT_CONNECTX9,
    CT_CONNECTX9_PURE_PCIE_SWITCH,
    CT_SPECTRUM3,
    CT_BLUEFIELD2,
    CT_BLUEFIELD3,
    CT_BLUEFIELD4,
    CT_CONNECTX3,
    CT_QUANTUM2,
    CT_QUANTUM3,
    CT_NVLINK6_SWITCH_ASIC,
    CT_SPECTRUM4,
    CT_SPECTRUM5,
    CT_SPECTRUM6,
    CT_GEARBOX,
    CT_GEARBOX_MGR,
    CT_ABIR_GEARBOX,
    CT_ARCUSE
} chip_type_t;

#define IS_HCA(chipType)                                                                                                                                                 \
    (((chipType) == CT_CONNECTX) || ((chipType) == CT_CONNECT_IB) || ((chipType) == CT_CONNECTX4) || ((chipType) == CT_CONNECTX4_LX) || ((chipType) == CT_CONNECTX5) ||  \
     ((chipType) == CT_CONNECTX6) || ((chipType) == CT_CONNECTX6DX) || ((chipType) == CT_CONNECTX6LX) || ((chipType) == CT_CONNECTX7) || ((chipType) == CT_CONNECTX8) || \
     ((chipType) == CT_CONNECTX8_PURE_PCIE_SWITCH) || ((chipType) == CT_CONNECTX9) || ((chipType) == CT_CONNECTX9_PURE_PCIE_SWITCH) || ((chipType) == CT_BLUEFIELD) ||   \
     ((chipType) == CT_BLUEFIELD2) || ((chipType) == CT_BLUEFIELD3) || ((chipType) == CT_BLUEFIELD4))

typedef enum chip_family_type
{
    CFT_UNKNOWN = 0,
    CFT_HCA,
    CFT_SWITCH,
    CFT_GEARBOX
} chip_family_type_t;

typedef struct guid
{
    u_int32_t h;
    u_int32_t l;
} guid_t;
typedef guid_t hw_key_t;

typedef struct fs3_uid
{
    guid_t base_guid;
    int base_guid_specified;
    guid_t base_mac;
    int base_mac_specified;
    u_int8_t num_of_guids;        // set 0 for default
    u_int8_t step_size;           // set 0 for default, not relevant for devices >= CX4
    int set_mac_from_guid;        // if set , base_mac will be derrived automatically from base guid
    int use_pp_attr;              // if set, num_of_guids[2] and step_size[2] will be used for the uid attributes.
    u_int16_t num_of_guids_pp[2]; // set 0xffff for default
    u_int8_t step_size_pp[2];     // set 0xff for default, not relevant for devices >= CX4
} fs3_uid_t;

typedef struct fs4_uid
{
    guid_t base_guid;
    int base_guid_specified;
    guid_t base_mac;
    int base_mac_specified;
    u_int8_t num_of_guids;       // set 0 for default
    u_int8_t step_size;          // set 0 for default, not relevant for devices >= CX4
    int set_mac_from_guid;       // if set , base_mac will be derrived automatically from base guid
    int use_pp_attr;             // if set, num_of_guids[2] and step_size[2] will be used for the uid attributes.
    u_int8_t num_of_guids_pp[2]; // set 0xff for default
    u_int8_t step_size_pp[2];    // set 0xff for default, not relevant for devices >= CX4
} fs4_uid_t;

typedef struct rom_info
{
    u_int16_t exp_rom_product_id; // 0 - invalid.
    u_int16_t exp_rom_ver[3];
    u_int16_t exp_rom_dev_id;
    u_int8_t exp_rom_port;
    u_int8_t exp_rom_proto;
    u_int8_t exp_rom_num_ver_fields;
    u_int8_t exp_rom_supp_cpu_arch;
    // char      expRomFreestr[FREE_STR_MAX_LEN];
} rom_info_t;

struct fs3_uid_entry
{
    u_int8_t num_allocated;
    u_int8_t step; // not relevant for devices >= CX4
    u_int64_t uid;
};

struct fs4_uid_entry
{
    u_int8_t num_allocated;
    u_int8_t step; // not relevant for devices >= CX4
    u_int8_t num_allocated_msb;
    u_int64_t uid;
};

typedef struct cibfw_uids
{
    struct fs3_uid_entry guids[2];
    struct fs3_uid_entry macs[2];
} cib_uids_t;

typedef struct cx4fw_uids
{
    struct fs3_uid_entry base_guid;
    struct fs3_uid_entry base_mac;
} cx4_uids_t;

typedef struct
{
    struct fs4_uid_entry base_guid;
    struct fs4_uid_entry base_mac;
} image_layout_uids_t;

typedef struct multi_asicfw_guids
{
    image_layout_uids_t image_layout_uids;
    u_int64_t sys_guid;
    u_int64_t node_guid;
    u_int64_t port_guid;
    u_int64_t allocated_guid;
} multi_asic_guids_t;

typedef enum guid_format
{
    CIB_UIDS,
    IMAGE_LAYOUT_UIDS,
    MULTI_ASIC_GUIDS
} guid_format_t;

typedef struct uids
{
    guid_format_t guid_format;
    union
    {
        cib_uids_t cib_uids;
        cx4_uids_t cx4_uids; // keeping this member for neohost
        image_layout_uids_t image_layout_uids;
        multi_asic_guids_t multi_asic_guids;
    };
} uids_t;

typedef struct life_cycle
{
    int version_field; // 0: fs4 , 1: fs5
    u_int8_t value;
} life_cycle_t;

typedef enum
{
    NOT_VALID,
    DIRECT_ACCESS,
    MFSV
} device_security_version_access_method_t;

typedef struct fs3_info_ext
{
    u_int8_t guids_override_en;
    uids_t fs3_uids_info;
    uids_t orig_fs3_uids_info;
    char image_vsd[VSD_LEN + 1];
    char orig_psid[PSID_LEN + 1];
    char prs_name[FS3_PRS_NAME_LEN];
    char orig_prs_name[FS3_PRS_NAME_LEN];
    char name[NAME_LEN];
    char description[DESCRIPTION_LEN];
    u_int32_t security_mode;
    u_int8_t mcc_en;
    char deviceVsd[VSD_LEN + 1];
    bool sec_boot;
    life_cycle_t life_cycle;
    bool encryption;
    bool dev_sec_boot;

    // security version (for fs4)
    u_int32_t image_security_version;
    device_security_version_access_method_t device_security_version_access_method;
    u_int32_t device_security_version_gw;
    struct reg_access_hca_mfsv_reg_ext device_security_version_mfsv;

    int global_image_status;
    u_int32_t ini_file_version;
    u_int8_t geo_address;
    bool geo_address_valid;
    bool socket_direct;
    bool aux_card_connected;
    bool is_aux_card_connected_valid;

    uint8_t independent_module;

    uint8_t pci_switch_only_mode;
    uint8_t pci_switch_only_mode_valid;
} fs3_info_t;

// typedef struct fs3_info_ext fs4_info_t;

typedef struct fs2_info_ext
{
    guid_t guids[MAX_GUIDS];
    u_int32_t guid_num;
    u_int32_t config_sectors;
    u_int32_t config_pad;
    u_int8_t access_key_exists;
    guid_t access_key_value;
    u_int8_t blank_guids;
    char prs_name[PRS_NAME_LEN];
} fs2_info_t;

#ifdef CABLES_SUPP
typedef struct cablefw_info_ext
{
    u_int8_t fw_gw_revision[2];
    u_int16_t fw_dev_id;
    u_int32_t fw_revision;
    u_int8_t image_key;
} cablefw_info_t;
#endif

typedef struct roms_info
{
    u_int8_t exp_rom_found;
    u_int8_t num_of_exp_rom;
    u_int8_t no_rom_checksum;
    u_int16_t exp_rom_com_devid;
    u_int8_t exp_rom_warning;
    char exp_rom_warning_msg[MAX_ROM_ERR_MSG_LEN];
    u_int8_t exp_rom_err_msg_valid;
    char exp_rom_err_msg[MAX_ROM_ERR_MSG_LEN];
    rom_info_t rom_info[MAX_ROMS_NUM];
} roms_info_t;

typedef enum
{
    BLANK = 0,
    PRE_PROD_IPN = 1,
    SECURE_IPN = 2,
    PRE_PROD_OPN = 3,
    SECURE_OPN = 4
} device_sku;

typedef struct fw_info_com
{
    char psid[PSID_LEN + 1];
    u_int8_t vsd_sect_found; // relevant to FS2 image only
    char vsd[VSD_LEN + 1];
    char product_ver[PRODUCT_VER_LEN + 1];
    u_int16_t fw_ver[3];
    u_int16_t fw_rel_date[3];
    u_int8_t fw_rel_time[3];
    u_int16_t min_fit_ver[4];
    u_int16_t mic_ver[3];
    u_int32_t image_size;
    u_int16_t isfu_major;
    u_int16_t dev_type;
    u_int8_t dev_rev;
    u_int16_t vsd_vendor_id;
    u_int8_t is_failsafe;
    chip_type_t chip_type;
    roms_info_t roms_info;
    u_int16_t running_fw_ver[3];
    u_int8_t image_info_minor_version;
    u_int8_t image_info_major_version;
    u_int16_t pci_device_id;
    char branch_ver[BRANCH_LEN + 1];
    char running_branch_ver[BRANCH_LEN + 1];
    u_int8_t encrypted_fw;
    u_int32_t burn_image_size; //! Be aware! This field is backward compatible starting from BB/CX-7
                               //! Use this field only for encrypted images
    u_int8_t dtoc_offset;
    device_sku sku;
} fw_info_com_t;

typedef struct fw_info_ext
{
    u_int8_t fw_type;
    fw_info_com_t fw_info;
    fs2_info_t fs2_info;
    fs3_info_t fs3_info;
#ifdef CABLES_SUPP
    cablefw_info_t cablefw_info;
#endif
    // fs3_info_t fs4_info;
} fw_info_t;

typedef enum fw_hndl_type
{
    FHT_MST_DEV,
    FHT_FW_FILE,
    FHT_UEFI_DEV,
    FHT_FW_BUFF,
    FHT_CABLE_DEV,
} fw_hndl_type_t;

typedef enum fw_img_type
{
    FIT_FS2 = 0,
    FIT_FS3 = 1,
    FIT_FC1 = 2,
    FIT_FS4 = 3,
    FIT_FSCTRL = 4,
    FIT_FS5 = 5,
    FIT_COMPS = 6,
    FIT_PLDM_1_0 = 7
} fw_img_type_t;

enum ExpRomProto
{
    ER_IB = 0,
    ER_ETH = 1,
    ER_VPI = 2
};

enum ExpRomCpuArch
{
    ERC_UNSPECIFIED = 0,
    ERC_AMD64 = 1,
    ERC_AARCH64 = 2,
    ERC_AMD64_AARCH64 = 3,
    ERC_IA32 = 4
};

typedef enum fw_ver_info
{
    FVI_SMALLER = -1,
    FVI_EQUAL = 0,
    FVI_GREATER = 1,
} fw_ver_info_t;

#endif
