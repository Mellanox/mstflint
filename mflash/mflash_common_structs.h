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

typedef struct mflash mflash;

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
    MFO_LAST
} MfOpt;

enum MfAccessType {
    MFAT_MFILE = 0,
    MFAT_UEFI,
};

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
    u_int8_t dummy_cycles_support;
    u_int8_t write_protect_support;
    u_int8_t protect_sub_and_sector;
    u_int8_t vendor;
    u_int8_t type;


} flash_attr;

#endif // MFLASH_COMMON_STRUCTS_H



