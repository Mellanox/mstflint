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

#include <compatibility.h>
#include "mflash_types.h"
#include "mflash_common_structs.h"

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
    const char *type_name;
    int log2size;
    int num_of_flashes;
} flash_params_t;

typedef struct write_protect_info {
    u_int8_t is_subsector;
    u_int8_t is_bottom;
    u_int8_t sectors_num;
} write_protect_info_t;

// TODO: remove UEFI REMNANTS
typedef struct _MLX4_DEV uefi_Dev_t;
typedef int (*f_fw_cmd) (uefi_Dev_t* dev, void* buffer, int* size);

/////////////////////////////////////////////
//
// MFLASH INTERFACE FUNCTIONS
//
// Return value:
// All functions returns MfError enum values.
//
/////////////////////////////////////////////

struct mfile_t;


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

int     mf_set_dummy_cycles (mflash *mfl, u_int8_t num_of_cycles);
int     mf_get_dummy_cycles (mflash *mfl, u_int8_t *num_of_cycles);

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

void mf_flash_list(char *flash_list);

EXTERN_C_END

#endif // MFLASH_H



