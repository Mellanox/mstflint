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

#ifndef MFLASH_COMMON_STRUCTS_H
#define MFLASH_COMMON_STRUCTS_H

#include <compatibility.h>

typedef struct mflash mflash;
#define MAX_FLASH_NAME 256

typedef enum MfOpt
{
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

enum MfAccessType
{
    MFAT_MFILE = 0,
    MFAT_UEFI,
};

typedef enum
{
    UNKNOWN_BIN = 0x0,
    CX5_LOW_BIN = 0x1,
    CX5_HIGH_BIN = 0x2,

} BinIdT;

typedef struct flash_params
{
    char type_name[MAX_FLASH_NAME];
    int log2size;
    int num_of_flashes;
} flash_params_t;

typedef struct write_protect_info
{
    u_int8_t is_subsector;
    u_int8_t is_bottom;
    u_int16_t sectors_num; // if zero: is_subsector and is_bottom are invalid.
    uint8_t bp_val;
    uint8_t tbs_bit; // due to CMP bit in some flashes, TBS bit don't always reflect correctly if the WP is from Bottom
                     // or Top
} write_protect_info_t;

typedef struct write_protect_info_backup
{
    write_protect_info_t protect_info;
    uint8_t cmp;
    uint8_t restore_needed;
} write_protect_info_backup_t;

////////////////////////////////////////
//
// ST SPI functions - common for InfiniHostIIILx and ConnectX
//
////////////////////////////////////////
typedef enum StFlashCommand
{
    SFC_SE = 0xD8,                      // Sector erase
    SFC_4SE = 0xDC,                     // Sector erase 4B addr
    SFC_SSE = 0x20,                     // Subsector erase
    SFC_4SSE = 0x21,                    // Subsector erase 4B addr
    SFC_PP = 0x02,                      // Page program
    SFC_4PP = 0x12,                     // Page program 4B addr
    SFC_READ = 0x03,                    // Read data
    SFC_4READ = 0x13,                   // Read data 4B addr
    SFC_FAST_READ = 0x3B,               // Fast read dual output
    SFC_4FAST_READ = 0x3C,              // Fast read dual output 4B addr
    SFC_RES = 0xAB,                     // Release power-down
    SFC_JEDEC = 0x9F,                   // Read JEDEC ID
    SFC_RDSR = 0x05,                    // Read status register
    SFC_WRSR2 = 0x31,                   // Write status register 2
    SFC_RDSR2 = 0x35,                   // Read status register 2
    SFC_WRSR3_WINBOND = 0x11,           // Write status register 3 (WINBOND)
    SFC_RDSR3_WINBOND = 0x15,           // Read status register 3 (WINBOND)
    SFC_SERPNV_ISSI = 0x85,             // write status extended read register
    SFC_RDERP_ISSI = 0x81,              // read status extended read register
    SFC_WRSR3_MACRONIX_MX25K16XXX = 0x11, // Write status register 3 (MACRONIX)
    SFC_RDSR3_MACRONIX_MX25K16XXX = 0x15, // Read status register 3 (MACRONIX)
    SFC_RDSR4_MACRONIX_MX25UXXX = 0xBE,   // Read status register 4 (MACRONIX)
    SFC_WRSR4_MACRONIX_MX25UXXX = 0xBF,   // Write status register 4 (MACRONIX)
    SFC_WREN = 0x06,                    // Write enable
    SFC_RDNVR = 0xB5,
    SFC_RDCR = 0x15,                    // Read configuration register
    SFC_WRNVR = 0xB1,
    SFC_WRSR = 0x01,                    // Write status register
    SFC_WRSR_GIGA = 0x31,               // Write status register (GIGA)
    SFC_RDFR = 0x48,
    SFC_WRFR = 0x42,
    SFC_RDRP_ISSI_IS25LPXXX = 0x61, // Read read parameters
    SFC_SFDP = 0x5A                // Read SFDP table
} StFlashCommand_t;

typedef struct access_commands
{
    StFlashCommand_t sfc_sector_erase;
    StFlashCommand_t sfc_subsector_erase;
    StFlashCommand_t sfc_page_program;
    StFlashCommand_t sfc_read;
    StFlashCommand_t sfc_fast_read;
} flash_access_commands_t;

typedef enum
{
    MACRONIX_MX25U3235F = 0x23,
    MACRONIX_MX25U3232F = 0x20,
    MACRONIX_MX25U3235E = 0xFF,
    MACRONIX_MX25U51294G_MX25U51294GXDI08 = 0x5E,
    MACRONIX_MX25U51245G = 0x2D,
    MACRONIX_UNKNOWN = 0x00
} MacronixSeriesCode;

/////////////////////////////////////////////
//
// Flash attributes struct
//
/////////////////////////////////////////////
typedef struct flash_attr
{
    const char* type_str;
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

    int num_erase_blocks; // Number of sector defs.

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
    u_int8_t cmp_support;
    u_int8_t quad_en_support;
    u_int8_t srwd_support;
    u_int8_t srp_support;
    u_int8_t srl_support;
    u_int8_t driver_strength_support;
    u_int8_t dummy_cycles_support;
    u_int8_t write_protect_support;
    u_int8_t protect_sub_and_sector;
    u_int8_t series_code_support;
    MacronixSeriesCode series_code;
    u_int8_t vendor;
    u_int8_t type;

    u_int8_t support_sub_and_sector; // true if flash can work in both 64KB and 4KB sectors

    flash_access_commands_t access_commands;

} flash_attr;

// Explanation for densities field:
// Support for density X is represented by setting the log(X) bit of flash_info.densities.
// That is, a flash related to flash_info supports density X iff ((flash_info.densities & (1 << FD_X)) != 0).
// FD_X is the density value as it appears in the flash JEDEC ID. For example, FD_128 == 0x18 (128Mb flash).
typedef struct flash_info
{
    const char* name;
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
    u_int8_t driver_strength_support;
    u_int8_t series_code_support;
    MacronixSeriesCode series_code;
} flash_info_t;

/*
 * Common Macros:
 */
#define WRITE_PROTECT_CHECKS(mfl, bank_num)     \
    {                                           \
        if (!mfl->attr.write_protect_support)   \
        {                                       \
            return MFE_NOT_SUPPORTED_OPERATION; \
        }                                       \
        if (bank_num >= mfl->attr.banks_num)    \
        {                                       \
            return MFE_FLASH_NOT_EXIST;         \
        }                                       \
    }
#define MAX_SUBSECTOR_NUM 8
#define MAX_SECTORS_NUM 64

#endif // MFLASH_COMMON_STRUCTS_H
