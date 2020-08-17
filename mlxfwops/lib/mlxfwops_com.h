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

#ifndef MLXFWOP_COM_H
#define MLXFWOP_COM_H

#include <compatibility.h>

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

typedef enum {
    PROG_WITH_PRECENTAGE,
    PROG_WITHOUT_PRECENTAGE,
    PROG_STRING_ONLY,
    PROG_OK
} prog_t;

typedef enum
{
    PRODUCTION = 0,
    GA_SECURED = 1,
    GA_NON_SECURED = 2,
    RMA = 3,
    NUM_OF_LIFE_CYCLES = 4
}life_cycle_t;
typedef int EFIAPI (*f_prog_func)(int completion);
typedef int EFIAPI (*f_prog_func_ex)(int completion, void *opaque);
typedef int EFIAPI (*f_prog_func_adv)(int completion, const char *str, prog_t, void *opaque);
typedef int (*f_prog_func_str)(char *str);

typedef struct {
    f_prog_func_adv func;
    void *opaque;
    f_prog_func uefi_func;
} f_prog_func_adv_st;

#define VSD_LEN  208
#define PSID_LEN 16
#define PRODUCT_VER_LEN 16
#define PRS_NAME_LEN 100
#define FS3_PRS_NAME_LEN 97
#define FS4_PRS_NAME_LEN 97
#define NAME_LEN 65
#define DESCRIPTION_LEN 257
#define BRANCH_LEN 28
#define MIN_BRANCH_LEN 5

#define FREE_STR_MAX_LEN    256

#define MAX_ROMS_NUM        5
#define MAX_ROM_ERR_MSG_LEN 256
#define ROM_INFO_SIZE       12

//min version that supports Rom Modify
#define MAJOR_MOD_ROM_FW    2
#define MINOR_MOD_ROM_FW    6
#define SUBMINOR_MOD_ROM_FW 1410

//Macros
#define PRINT_PROGRESS(printFunc, arg) \
    do { \
        if (printFunc) { \
            printFunc((arg)); \
        } \
    } while (0) \

enum {
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
    MLXFW_FSM_UNEXPECTED_STATE,
    MLXFW_REJECTED_NOT_A_SECURED_FW,
    MLXFW_REJECTED_MFG_BASE_MAC_NOT_LISTED,
    MLXFW_REJECTED_NO_DEBUG_TOKEN,
    MLXFW_REJECTED_VERSION_NUM_MISMATCH,
    MLXFW_REJECTED_USER_TIMESTAMP_MISMATCH,
    MLXFW_REJECTED_FORBIDDEN_VERSION,
    MLXFW_FLASH_ERASE_ERROR,
    MLXFW_MISSING_IMAGE_SIGNATURE,
    MLXFW_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION,
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

enum {
    GUIDS = 4,
    MACS = 2,
    MAX_GUIDS = 32
};

// needed for flint query
enum {
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

enum {
    BI_IMACS = 0,
    BI_EMACS = BI_IMACS + BX_IMACS,
    BI_WWPNS = BI_EMACS + BX_EMACS,
    BI_GUIDS = BI_WWPNS + BX_WWPNS,
    BI_WWNNS = BI_GUIDS + BX_NP_GUIDS,
    BI_SYS_GUID = BX_ALL_GUIDS - 1,
};

typedef enum security_mode_mask {
    SMM_MCC_EN    = 0x1,
    SMM_DEBUG_FW  = 0x1 << 1,
    SMM_SIGNED_FW = 0x1 << 2,
    SMM_SECURE_FW = 0x1 << 3,
    SMM_DEV_FW    = 0x1 << 4,
    SMM_CS_TOKEN  = 0x1 << 5,
    SMM_DBG_TOKEN = 0x1 << 6
} security_mode_mask_t;

typedef enum security_mode {
    SM_NONE = 0x0,
    SM_SHA_DIGEST = SMM_MCC_EN,
    SM_SIGNED_IMAGE = SMM_MCC_EN | SMM_SIGNED_FW,
    SM_SECURE_FW = SMM_MCC_EN | SMM_SIGNED_FW | SMM_SECURE_FW,
    SM_DEBUG_FW = SMM_MCC_EN | SMM_SIGNED_FW | SMM_SECURE_FW | SMM_DEBUG_FW
} security_mode_t;

typedef enum chip_type {
    CT_UNKNOWN = 0,
    CT_CONNECTX,
    CT_SWITCHX,
    CT_IS4,
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
    CT_SPECTRUM3,
    CT_BLUEFIELD2
} chip_type_t;

#define IS_HCA(chipType) \
    (((chipType) == CT_CONNECTX) || ((chipType) == CT_CONNECT_IB) || ((chipType) == CT_CONNECTX4) || ((chipType) == CT_CONNECTX4_LX) || \
      ((chipType) == CT_CONNECTX5) || ((chipType) == CT_BLUEFIELD) || ((chipType) == CT_CONNECTX6) || \
        ((chipType) == CT_CONNECTX6DX) || ((chipType) == CT_CONNECTX6LX) || ((chipType) == CT_BLUEFIELD2))
typedef enum chip_family_type {
    CFT_UNKNOWN = 0,
    CFT_HCA,
    CFT_SWITCH,
} chip_family_type_t;

typedef struct guid {
    u_int32_t h;
    u_int32_t l;
} guid_t;
typedef guid_t hw_key_t;

typedef struct fs3_uid {
    guid_t base_guid;
    int base_guid_specified;
    guid_t base_mac;
    int base_mac_specified;
    u_int8_t num_of_guids; // set 0 for default
    u_int8_t step_size; // set 0 for default, not relevant for devices >= CX4
    int set_mac_from_guid;  // if set , base_mac will be derrived automatically from base guid
    int use_pp_attr; // if set, num_of_guids[2] and step_size[2] will be used for the uid attributes.
    u_int8_t num_of_guids_pp[2]; // set 0xff for default
    u_int8_t step_size_pp[2]; // set 0xff for default, not relevant for devices >= CX4
} fs3_uid_t;

typedef struct fs4_uid {
    guid_t base_guid;
    int base_guid_specified;
    guid_t base_mac;
    int base_mac_specified;
    u_int8_t num_of_guids; // set 0 for default
    u_int8_t step_size; // set 0 for default, not relevant for devices >= CX4
    int set_mac_from_guid;  // if set , base_mac will be derrived automatically from base guid
    int use_pp_attr; // if set, num_of_guids[2] and step_size[2] will be used for the uid attributes.
    u_int8_t num_of_guids_pp[2]; // set 0xff for default
    u_int8_t step_size_pp[2]; // set 0xff for default, not relevant for devices >= CX4
} fs4_uid_t;

typedef struct rom_info {
    u_int16_t exp_rom_product_id; // 0 - invalid.
    u_int16_t exp_rom_ver[3];
    u_int16_t exp_rom_dev_id;
    u_int8_t exp_rom_port;
    u_int8_t exp_rom_proto;
    u_int8_t exp_rom_num_ver_fields;
    u_int8_t exp_rom_supp_cpu_arch;
    //char      expRomFreestr[FREE_STR_MAX_LEN];
} rom_info_t;

struct fs3_uid_entry {
    u_int8_t num_allocated;
    u_int8_t step; // not relevant for devices >= CX4
    u_int64_t uid;
};

typedef struct cibfw_uids {
    struct fs3_uid_entry guids[2];
    struct fs3_uid_entry macs[2];
} cib_uids_t;

typedef struct cx4fw_uids {
    struct fs3_uid_entry base_guid;
    struct fs3_uid_entry base_mac;
} cx4_uids_t;

typedef struct uids {
    int valid_field; // 0: cib_uids , 1: cx4_uids
    union {
        cib_uids_t cib_uids;
        cx4_uids_t cx4_uids;
    };
} uids_t;

typedef struct fs3_info_ext {
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
} fs3_info_t;

typedef struct fs3_info_ext fs4_info_t;

typedef struct fs2_info_ext {
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
typedef struct cablefw_info_ext {
    u_int8_t fw_gw_revision[2];
    u_int16_t fw_dev_id;
    u_int32_t fw_revision;
    u_int8_t image_key;
} cablefw_info_t;
#endif

typedef struct roms_info {
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

typedef struct fw_info_com {
    char psid[PSID_LEN + 1];
    u_int8_t vsd_sect_found; // relevant to FS2 image only
    char vsd[VSD_LEN + 1];
    char product_ver[PRODUCT_VER_LEN + 1];
    u_int16_t fw_ver[3];
    u_int16_t fw_rel_date[3];
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
} fw_info_com_t;

typedef struct fw_info_ext {
    u_int8_t fw_type;
    fw_info_com_t fw_info;
    fs2_info_t fs2_info;
    fs3_info_t fs3_info;
#ifdef CABLES_SUPP
    cablefw_info_t cablefw_info;
#endif
    fs3_info_t fs4_info;
} fw_info_t;

typedef enum fw_hndl_type {
    FHT_MST_DEV,
    FHT_FW_FILE,
    FHT_UEFI_DEV,
    FHT_FW_BUFF,
    FHT_CABLE_DEV,
} fw_hndl_type_t;

typedef enum fw_img_type {
    FIT_FS2,
    FIT_FS3,
    FIT_FC1,
    FIT_FS4,
    FIT_FSCTRL,
} fw_img_type_t;

enum ExpRomProto {
    ER_IB = 0,
    ER_ETH = 1,
    ER_VPI = 2
};

enum ExpRomCpuArch {
    ERC_UNSPECIFIED = 0,
    ERC_AMD64 = 1,
    ERC_AARCH64 = 2,
    ERC_AMD64_AARCH64 = 3,
    ERC_IA32 = 4
};

typedef enum fw_ver_info {
    FVI_SMALLER = -1,
    FVI_EQUAL = 0,
    FVI_GREATER = 1,
} fw_ver_info_t;

#endif
