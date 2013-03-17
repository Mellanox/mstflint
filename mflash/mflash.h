/*
 *
 * mflash.h - Mellanox Technilogies LTD. Flash access lib heared file
 * ==================================================================
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: $
 *
 */
#ifndef MFLASH_H
#define MFLASH_H

#ifndef __WIN__
#include <sys/types.h>
#endif

#ifdef __cplusplus
#define EXTERN_C_START extern "C" {
#define EXTERN_C_END   }
#else
#define EXTERN_C_START
#define EXTERN_C_END
#endif

EXTERN_C_START

typedef enum MfCommandSet {
    CS_INTEL   = 1,
    CS_AMD     = 2,

    MCS_STSPI  = 0x80,  // This is not a "real" CFI command set - it's used as a "Meta" command set number.
    MCS_SSTSPI = 0x81
} MfCommandSet;

typedef struct flash_params {
    char *type_name;
    int log2size;
    int num_of_flashes;
} flash_params_t;

typedef struct write_protect_info {
    u_int8_t is_subsector;
    u_int8_t is_bottom;
    u_int8_t sectors_num;
} write_protect_info_t;

typedef enum MfError {
    MFE_OK = 0,
    MFE_ERROR,
    MFE_BAD_PARAMS,
    MFE_CR_ERROR,
    MFE_INVAL,
    MFE_NOT_IMPLEMENTED,
    MFE_UNSUPPORTED_FLASH_TOPOLOGY,
    MFE_UNSUPPORTED_FLASH_TYPE,
    MFE_CFI_FAILED,
    MFE_TIMEOUT,
    MFE_ERASE_TIMEOUT,
    MFE_WRITE_TIMEOUT,
    MFE_ERASE_ERROR,
    MFE_WRITE_ERROR,
    MFE_BAD_ALIGN,
    MFE_SEM_LOCKED,
    MFE_VERIFY_ERROR,
    MFE_NOMEM,
    MFE_OUT_OF_RANGE,
    MFE_CMD_SUPPORTED_INBAND_ONLY,
    MFE_NO_FLASH_DETECTED,
    MFE_LOCKED_CRSPACE,
    MFE_CMDIF_BAD_STATUS_ERR,
    MFE_CMDIF_TIMEOUT_ERR,
    MFE_CMDIF_GO_BIT_BUSY,
    MFE_MISMATCH_KEY,
    MFE_UNKNOWN_REG,
    MFE_REG_ACCESS_FAILED,
    MFE_REG_ACCESS_MAD_BAD_STATUS,
    MFE_REG_ACCESS_MAD_NOT_SUPPORTED,
    MFE_DIRECT_FW_ACCESS_DISABLED,
    MFE_MANAGED_SWITCH_NOT_SUPPORTED,
    MFE_NOT_SUPPORTED_OPERATION,
    MFE_REG_ACCESS_FW_BAD_STATUS,
    MFE_FLASH_NOT_EXIST,
    MFE_MISMATCH_QUAD_EN,
    MFE_EXCEED_SUBSECTORS_MAX_NUM,
    MFE_EXCEED_SECTORS_MAX_NUM,
    MFE_SECTORS_NUM_NOT_POWER_OF_TWO,
    MFE_REG_ACCESS_RESOURCE_NOT_AVAILABLE,
    MFE_UNKOWN_ACCESS_TYPE,
    MFE_UNSUPPORTED_DEVICE,
    MFE_OLD_DEVICE_TYPE,
    MFE_LAST
} MfError;

typedef enum MfOpt {
    MFO_NO_VERIFY = 0,
    MFO_AMD_UNLOCK_BYPASS,
    MFO_AMD_BYTE_MODE,
    MFO_IGNORE_SEM_LOCK,
    MFO_CLOSE_MF_ON_EXIT,
    MFO_NUM_OF_BANKS,
    MFO_IGNORE_CASHE_REP_GUARD,
    MFO_USER_BANKS_NUM,
    //MFO_FW_ACCESS_TYPE_BY_MFILE,
    MFO_SX_TYPE,
    MFO_NEW_CACHE_REPLACEMENT_EN,
    MFO_LAST
} MfOpt;

enum MfAccessType {
    MFAT_MFILE = 0,
    MFAT_UEFI,
};

#define MAX_NUM_OF_FLASH_BANKS 4

/////////////////////////////////////////////
//
// Flash attributes struct
//
/////////////////////////////////////////////
typedef struct flash_attr {
    char *type_str;
    //
    // hw_dev_id    hw dev id of the HCA.
    //
    u_int32_t hw_dev_id;
    u_int32_t rev_id;

    //
    // size:        Total size (in bytes) of all flash devices connected to
    //              the device (forming a contigous address space)
    //
    u_int32_t size;

    //
    // sector_size: Flash sector size (in bytes).
    //              Assuming a single sector size for the flash.
    //
    u_int32_t sector_size;

    int       num_erase_blocks;         // Number of sector defs.
    struct {
        unsigned long sector_size;      // Byte size of sector
        int           num_sectors;      // Num sectors of this size
        u_int32_t     sector_mask;      // Sector mask
    } erase_block[8];

    //
    // bank_size:   Different bank means a different chip sellect or gpio settings is needed when crossing
    //              this alignment.
    //              This may indicate a different flash device (for SPI flash in InfiniHostIIILx / ConnectX).
    //              Or GPIO change for parallel flash (in InfiniHostIII / InfiniHost)
    //
    int bank_size;
    int log2_bank_size;

    //
    // Command set (taken from CFI terminology)
    //
    int command_set;

    u_int8_t erase_command;

    //
    // block_write - if block write is supported, holds the block size in bytes. 0 otherwise.
    //               The meaning of "block write" is not the same in parallel and serial flash.
    //
    int block_write;

    //
    // page_write -  if page write is supported, holds the page size in bytes. 0 otherwise.
    //
    int page_write;

    u_int8_t banks_num;
    u_int8_t quad_en_support;
    u_int8_t write_protect_support;


} flash_attr;


/////////////////////////////////////////////
//
// MFLASH INTERFACE FUNCTIONS
//
// Return value:
// All functions returns MfError enum values.
//
/////////////////////////////////////////////

struct mfile_t;
typedef struct mflash mflash;

//
// open/close functions:
// This lib is used pretty much like a C file: open it, use and close when done.
//
// mf_open(): Allocates and init the mflash object to be used with the other lib funcs.
//   OUT: pmfl - The opened mflash struct is returned here.
//   IN : dev  - The string name of the crspace device to use.
//
// mf_opend(): Same as mf_open, but uses an already opened crspace device.
//
// mf_open_ignore_lock() :
//   THIS FUNCTION IS NOT SAFE -
//   It ignores the flash semaphore during flash init sequence.
//   Use only after one of the above open() failed because of MFE_SEM_LOCKED
//   and you are absolutely sure that the lock can be overridden (E.G. semaphore
//   remained in locked state due to previous kill of the burning app).
//
// mf_close() : Deallocates mflash resources.
//   Note: User should call mf_close() even if mf_open failed (and the returning mfl is not NULL)
//
int     mf_open        (mflash** pmfl, const char* dev, int num_of_banks, flash_params_t* flash_params,
        int ignore_cache_rep_guard);
int     mf_opend       (mflash** pmfl, struct mfile_t* mf, int num_of_banks,  flash_params_t* flash_params,
        int ignore_cache_rep_guard);

typedef struct _MLX4_DEV uefi_Dev_t;
typedef int (*f_fw_cmd) (uefi_Dev_t* dev, void* buffer, int* size);
int     mf_open_uefi(mflash** pmfl, uefi_Dev_t *uefi_dev, f_fw_cmd fw_cmd_func);

int     mf_open_ignore_lock(mflash* mfl);
int     mf_close       (mflash* mfl);

//
// Flash access functions:
// The data buffer should be pre-allocated by caller. The rest is quite self explanatory. .
//
int     mf_read        (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
int     mf_write       (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
int     mf_erase_sector(mflash* mfl, u_int32_t addr);

//
// Crspace access through mflash:
//
int     mf_cr_read     (mflash* mfl, u_int32_t cr_addr, u_int32_t* data);
int     mf_cr_write    (mflash* mfl, u_int32_t cr_addr, u_int32_t  data);

int     mf_update_boot_addr(mflash* mfl, u_int32_t boot_addr);
// Software reset the target device. Currently supported for InfiniScale4 switch via IB interface only.
int     mf_sw_reset     (mflash* mfl);
//
// mf_get_attr(): Returns the flash_attr struct
//
int     mf_get_attr    (mflash* mfl, flash_attr* attr);

int     mf_set_quad_en (mflash *mfl, u_int8_t quad_en);
int     mf_get_quad_en (mflash *mfl, u_int8_t *quad_en);

int     mf_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);
int     mf_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info);

//
// Set/Get for some options.
//
int     mf_set_opt     (mflash* mfl, MfOpt opt, int  val);
int     mf_get_opt     (mflash* mfl, MfOpt opt, int *val);

int     mf_enable_hw_access(mflash* mfl, u_int64_t key);
int     mf_disable_hw_access(mflash* mfl);
int     mf_release_semaphore();

//
// err code to string translation for printing.
//
const char* mf_err2str (int err_code);

EXTERN_C_END

#endif // MFLASH_H



