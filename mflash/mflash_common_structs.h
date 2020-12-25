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

#ifndef MFLASH_COMMON_STRUCTS_H
#define MFLASH_COMMON_STRUCTS_H

#include <compatibility.h>

typedef struct mflash mflash;
#define MAX_FLASH_NAME 256

typedef enum MfOpt {
    MFO_NO_VERIFY = 0,
    MFO_AMD_UNLOCK_BYPASS,
    MFO_AMD_BYTE_MODE,
    MFO_IGNORE_SEM_LOCK,
    MFO_CLOSE_MF_ON_EXIT,
    MFO_NUM_OF_BANKS,
    MFO_IGNORE_CASHE_REP_GUARD,
    MFO_USER_BANKS_NUM,
    MFO_FW_ACCESS_TYPE_BY_MFILE,
    MFO_SX_TYPE,
    MFO_NEW_CACHE_REPLACEMENT_EN,
    MFO_CX3_FW_ACCESS_EN,
    MFO_LAST
} MfOpt;

enum MfAccessType {
    MFAT_MFILE = 0, MFAT_UEFI,
};

typedef enum {
    UNKNOWN_BIN = 0x0, CX5_LOW_BIN = 0x1, CX5_HIGH_BIN = 0x2,

} BinIdT;

typedef struct flash_params {
    char type_name[MAX_FLASH_NAME];
    int log2size;
    int num_of_flashes;
} flash_params_t;

typedef struct write_protect_info {
    u_int8_t is_subsector;
    u_int8_t is_bottom;
    u_int8_t sectors_num;  // if zero: is_subsector and is_bottom are invalid.
} write_protect_info_t;

////////////////////////////////////////
//
// ST SPI functions - common for InfiniHostIIILx and ConnectX
//
////////////////////////////////////////
typedef enum StFlashCommand {
    SFC_SE = 0xD8,
    SFC_4SE = 0xDC,
    SFC_SSE = 0x20,
    SFC_4SSE = 0x21,
    SFC_PP = 0x02,
    SFC_4PP = 0x12,
    SFC_READ = 0x03,
    SFC_4READ = 0x13,
    SFC_FAST_READ = 0x3B,
    SFC_4FAST_READ = 0x3C,
    SFC_QUAD_READ = 0x3B,
    SFC_4QUAD_READ = 0x3C,
    SFC_RES = 0xAB,
    SFC_JEDEC = 0x9F,
    SFC_RDSR = 0x05,
    SFC_WRSR2 = 0x31,
    SFC_RDSR2 = 0x35,
    SFC_WREN = 0x06,
    SFC_RDNVR = 0xB5,
    SFC_RDCR = 0x15,
    SFC_WRNVR = 0xB1,
    SFC_WRSR = 0x01,
    SFC_WRSR_GIGA = 0x31,
    SFC_RDFR = 0x48,
    SFC_WRFR = 0x42
} StFlashCommand_t;

typedef struct access_commands {
    StFlashCommand_t sfc_sector_erase;
    StFlashCommand_t sfc_subsector_erase;
    StFlashCommand_t sfc_page_program;
    StFlashCommand_t sfc_read;
    StFlashCommand_t sfc_fast_read;
} flash_access_commands_t;

/////////////////////////////////////////////
//
// Flash attributes struct
//
/////////////////////////////////////////////
typedef struct flash_attr {
    const char *type_str;
    //
    // hw_dev_id    hw dev id of the HCA.
    //
    u_int32_t hw_dev_id;
    u_int32_t rev_id;
    BinIdT bin_id;

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

    int num_erase_blocks;         // Number of sector defs.

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
    u_int8_t dummy_cycles_support;
    u_int8_t write_protect_support;
    u_int8_t protect_sub_and_sector;
    u_int8_t vendor;
    u_int8_t type;

    u_int8_t support_sub_and_sector; // true if flash can work in both 64KB and 4KB sectors

    flash_access_commands_t access_commands;

} flash_attr;

// Explanation for densities field:
// Support for density X is represented by setting the log(X) bit of flash_info.densities.
// That is, a flash related to flash_info supports density X iff ((flash_info.densities & (1 << FD_X)) != 0).
// FD_X is the density value as it appears in the flash JEDEC ID. For example, FD_128 == 0x18 (128Mb flash).
typedef struct flash_info {
    const char *name;
    u_int8_t vendor;
    u_int8_t type;
    u_int32_t densities;
    int command_set;
    int erase_command;
    u_int32_t sector_size;
    u_int8_t support_sub_and_sector;
    u_int8_t quad_en_support;
    u_int8_t write_protected_support;
    u_int8_t protect_sub_and_sector;
    u_int8_t dummy_cycles_support;
} flash_info_t;

/*
 * Common Macros:
 */
#define WRITE_PROTECT_CHECKS(mfl, bank_num) { \
        if (!mfl->attr.write_protect_support) { \
            return MFE_NOT_SUPPORTED_OPERATION; \
        } \
        if (bank_num >= mfl->attr.banks_num) { \
            return MFE_FLASH_NOT_EXIST; \
        } \
}
#define MAX_SUBSECTOR_NUM 8
#define MAX_SECTORS_NUM   64

#endif // MFLASH_COMMON_STRUCTS_H

