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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <mtcr.h>
#include <reg_access.h>

#include "mflash_types.h"
#include "mflash_pack_layer.h"
#include "mflash_access_layer.h"

extern flash_info_t g_flash_info_arr[];

#define CX3_PRO_HW_ID 0x1F7
#define CX3_HW_ID     0x1F5
#define HAS_TOOLS_CMDIF(dev_id) \
    ((((dev_id) == CX3_HW_ID) || ((dev_id) == CX3_PRO_HW_ID)))

// On windows we don't support cmdIf access!
int check_access_type(mflash *mfl)
//TODO: re-write in a more elegant way.
{
    if (mfl->access_type == MFAT_MFILE) {
        switch (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE]) {
        case ATBM_INBAND:
#ifdef NO_INBAND_ACCESS
            return MFE_NOT_SUPPORTED_OPERATION;

#endif
#ifndef _WIN_
        case ATBM_MLNXOS_CMDIF:
#endif
        case ATBM_ICMD:
        case ATBM_TOOLS_CMDIF:
            break;

        default:
            return MFE_UNKOWN_ACCESS_TYPE;
        }
    } else if (mfl->access_type == MFAT_UEFI) {
    } else {
        return MFE_UNKOWN_ACCESS_TYPE;
    }
    return MFE_OK;
}

int sx_get_flash_info_by_type(mflash *mfl, flash_info_t *f_info, int *log2size, u_int8_t *no_flash)
{
    int rc = 0;
    u_int8_t vendor = 0, type = 0, density = 0;
    unsigned type_index = 0;

    mfpa_command_args mfpa_args;
    memset(&mfpa_args, 0, sizeof(mfpa_args));
    mfpa_args.flash_bank = get_bank_int(mfl);

    rc = check_access_type(mfl);
    CHECK_RC(rc);
    rc = com_get_jedec(mfl->mf, &mfpa_args);
    CHECK_RC(rc);
    //printf("-D- jedec_id = %#x\n", jedec_id);
    rc = get_info_from_jededc_id(mfpa_args.jedec_id, &vendor, &type, &density);
    CHECK_RC(rc);
    // Return there is no flash when all the params are 0xff
    if (vendor == 0xff && type == 0xff && density == 0xff) {
        *no_flash = 1;
        return MFE_OK;
    }
    rc = get_log2size_by_vendor_type_density(vendor, type, density, log2size);
    CHECK_RC(rc);
    rc = get_type_index_by_vendor_type_density(vendor, type, *log2size, &type_index);
    CHECK_RC(rc);

    memcpy(f_info, &(g_flash_info_arr[type_index]), sizeof(flash_info_t));
    f_info->support_sub_and_sector = mfpa_args.supp_sub_and_sector_erase;

    f_info->dummy_cycles_support = mfpa_args.supp_dummy_cycles;
    f_info->write_protected_support = mfpa_args.supp_sector_write_prot | mfpa_args.supp_sub_sector_write_prot;
    f_info->protect_sub_and_sector = mfpa_args.supp_sector_write_prot & mfpa_args.supp_sub_sector_write_prot;
    f_info->quad_en_support = mfpa_args.supp_quad_en;

    // HACK: Use fw_sector size as the sector size only in CX3 family devices for now
    if (HAS_TOOLS_CMDIF(mfl->attr.hw_dev_id)) {
        f_info->sector_size = mfpa_args.fw_flash_sector_sz ? mfpa_args.fw_flash_sector_sz : f_info->sector_size;
    }
    return MFE_OK;
}

int sx_block_read_by_type(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data)
{
    int rc = 0, bank = 0;
    u_int32_t flash_offset = 0;

    if (blk_size > (u_int32_t) mfl->attr.block_write || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }
    rc = mfl_get_bank_info(mfl, blk_addr, &flash_offset, &bank);
    CHECK_RC(rc);
    COM_CHECK_ALIGN(flash_offset, blk_size);

    rc = check_access_type(mfl);
    CHECK_RC(rc);
    rc = sx_st_block_access(mfl->mf, flash_offset, bank, blk_size, data, REG_ACCESS_METHOD_GET);
    CHECK_RC(rc);

    return MFE_OK;
}

int sx_block_write_by_type(mflash *mfl, u_int32_t addr, u_int32_t size, u_int8_t *data)
{
    int rc = 0, bank = 0;
    u_int32_t flash_offset = 0;

    WRITE_CHECK_ALIGN(addr, mfl->attr.block_write, size);

    rc = mfl_get_bank_info(mfl, addr, &flash_offset, &bank);
    CHECK_RC(rc);
    COM_CHECK_ALIGN(flash_offset, size);

    rc = check_access_type(mfl);
    CHECK_RC(rc);
    rc = sx_st_block_access(mfl->mf, flash_offset, bank, size, data, REG_ACCESS_METHOD_SET);
    CHECK_RC(rc);
    return MFE_OK;
}


static int lock_flash_programing_sem(mflash *mfl)
{
#ifndef UEFI_BUILD
    int rc = 0;
    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_INBAND) {
        rc = trm_lock(mfl->trm, TRM_RES_FLASH_PROGRAMING, MAX_FLASH_PROG_SEM_RETRY_CNT);
        if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
            return MFE_SEM_LOCKED;
        }
    } else if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_TOOLS_CMDIF) {
        rc = trm_lock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING, MAX_FLASH_PROG_SEM_RETRY_CNT);
        if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
            return MFE_SEM_LOCKED;
        }
    }
#endif
    return MFE_OK;
}

static int unlock_flash_programing_sem(mflash *mfl)
{
#ifndef UEFI_BUILD
    int rc = 0;
    if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_INBAND) {
        rc = trm_unlock(mfl->trm, TRM_RES_FLASH_PROGRAMING);
        if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
            return MFE_SEM_LOCKED;
        }
    } else if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_TOOLS_CMDIF) {
        rc = trm_unlock(mfl->trm, TRM_RES_HCR_FLASH_PROGRAMING);
        if (rc && rc != TRM_STS_RES_NOT_SUPPORTED) {
            return MFE_SEM_LOCKED;
        }
    }
#endif
    return MFE_OK;
}

int sx_flash_lock_by_type(mflash *mfl, int lock_state)
{
    // burning through some FW interface , lock flash programing semaphore if possible
    int rc = 0;
    if (lock_state) {
        rc = lock_flash_programing_sem(mfl);
    } else {
        rc = unlock_flash_programing_sem(mfl);
    }
    if (rc == MFE_OK) {
        mfl->is_locked = (lock_state != 0);
    }
    return rc;
}

int sx_erase_sect_by_type(mflash *mfl, u_int32_t addr, u_int32_t erase_size)
{
    int rc = 0, bank = 0;
    u_int32_t flash_addr = 0;

    rc = mfl_get_bank_info(mfl, addr, &flash_addr, &bank);
    CHECK_RC(rc);
    rc = check_access_type(mfl);
    CHECK_RC(rc);
    rc = common_erase_sector(mfl->mf, flash_addr, bank, erase_size);
    CHECK_RC(rc);
    return MFE_OK;
}

int mf_update_boot_addr_by_type(mflash *mfl, u_int32_t boot_addr)
{
    int rc = 0;
    if (mfl->access_type == MFAT_UEFI || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF) {
        // No CR-Space access - use mfpa register
        mfpa_command_args mfpa_args;
        memset(&mfpa_args, 0, sizeof(mfpa_args));
        mfpa_args.flash_bank = get_bank_int(mfl);
        mfpa_args.boot_address = boot_addr;
        rc = run_mfpa_command(mfl->mf, REG_ACCESS_METHOD_SET, &mfpa_args);
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int sx_set_quad_en(mflash *mfl, u_int8_t quad_en)
{
    int bank = 0;
    int rc = 0;
    struct tools_open_mfmc mfmc;

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    if (!mfl->attr.quad_en_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        memset(&mfmc, 0, sizeof(mfmc));
        mfmc.fs = bank;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
        CHECK_RC(rc);
        mfmc.quad_en = quad_en;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_SET, &mfmc));
        CHECK_RC(rc);
    }
    return MFE_OK;
}

int sx_get_quad_en(mflash *mfl, u_int8_t *quad_en)
{
    int bank = 0;
    int rc = MFE_OK;
    struct tools_open_mfmc mfmc;
    int is_first_val = 1;

    if (!mfl || !quad_en) {
        return MFE_BAD_PARAMS;
    }

    if (!mfl->attr.quad_en_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        memset(&mfmc, 0, sizeof(mfmc));
        mfmc.fs = bank;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
        CHECK_RC(rc);
        if (is_first_val) {
            *quad_en = mfmc.quad_en;
            is_first_val = 0;
        } else {
            if (mfmc.quad_en != *quad_en) {
                rc = MFE_MISMATCH_PARAM;
                break;
            }
        }
    }
    return rc;
}

int sx_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    u_int8_t log2_sect_num = 0;
    u_int8_t sectors_num = 0;
    struct tools_open_mfmc mfmc;
    int rc = 0;

    if (!mfl || !protect_info) {
        return MFE_BAD_PARAMS;
    }

    sectors_num = protect_info->sectors_num;
    WRITE_PROTECT_CHECKS(mfl, bank_num);
    if (((protect_info->sectors_num - 1) & protect_info->sectors_num) != 0) {
        return MFE_SECTORS_NUM_NOT_POWER_OF_TWO;
    }
    if (protect_info->sectors_num > MAX_SECTORS_NUM) {
        return MFE_EXCEED_SECTORS_MAX_NUM;
    }

    if (protect_info->is_subsector && !mfl->attr.protect_sub_and_sector) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    if (protect_info->is_bottom) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    if (mfl->attr.protect_sub_and_sector && protect_info->is_subsector) {
        if (protect_info->sectors_num > MAX_SUBSECTOR_NUM) {
            return MFE_EXCEED_SUBSECTORS_MAX_NUM;
        }
    }

    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);

    for (log2_sect_num = 0; log2_sect_num < 8; log2_sect_num++) {
        sectors_num >>= 1;
        if (sectors_num == 0) {
            break;
        }
    }

    memset(&mfmc, 0, sizeof(mfmc));
    rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
    CHECK_RC(rc);
    mfmc.fs = bank_num;
    mfmc.wrp_en = protect_info->sectors_num != 0;
    if (mfmc.wrp_en) {
        mfmc.block_size = protect_info->is_subsector ? 0 : 1;
        mfmc.wrp_block_count = log2_sect_num;
    }
    rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_SET, &mfmc));
    CHECK_RC(rc);

    //printf("-D- mf_set_write_protect: bank_num = %#x, subsec: %#x, bottom: %#x, sectors_num=%#x\n", bank_num,
    //       protect_info->is_subsector, protect_info->is_bottom, protect_info->sectors_num);
    return MFE_OK;
}

int sx_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    int rc = 0;
    struct tools_open_mfmc mfmc;

    if (!mfl || !protect_info) {
        return MFE_BAD_PARAMS;
    }

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    rc = set_bank_int(mfl, bank_num);
    CHECK_RC(rc);

    memset(&mfmc, 0, sizeof(mfmc));
    mfmc.fs = get_bank_int(mfl);
    rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
    CHECK_RC(rc);

    protect_info->is_bottom = 0; // no support for bottom
    protect_info->is_subsector = mfmc.block_size == 0;
    protect_info->sectors_num = mfmc.wrp_en ? 1 << mfmc.wrp_block_count : 0;
    return MFE_OK;
}

int sx_set_dummy_cycles(mflash *mfl, u_int8_t num_of_cycles)
{
    int bank = 0;
    int rc = 0;
    struct tools_open_mfmc mfmc;

    if (!mfl || num_of_cycles < 1 || num_of_cycles > 15) {
        return MFE_BAD_PARAMS;
    }

    if (!mfl->attr.dummy_cycles_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        memset(&mfmc, 0, sizeof(mfmc));
        mfmc.fs = bank;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
        CHECK_RC(rc);
        mfmc.dummy_clock_cycles = num_of_cycles;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_SET, &mfmc));
        CHECK_RC(rc);
    }
    return MFE_OK;
}
int sx_get_dummy_cycles(mflash *mfl, u_int8_t *num_of_cycles)
{
    int bank = 0;
    int rc = MFE_OK;
    struct tools_open_mfmc mfmc;
    int is_first_val = 1;

    if (!mfl || !num_of_cycles) {
        return MFE_BAD_PARAMS;
    }

    if (!mfl->attr.dummy_cycles_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = set_bank_int(mfl, bank);
        CHECK_RC(rc);
        memset(&mfmc, 0, sizeof(mfmc));
        mfmc.fs = bank;
        rc = MError2MfError(reg_access_mfmc(mfl->mf, REG_ACCESS_METHOD_GET, &mfmc));
        CHECK_RC(rc);
        if (is_first_val) {
            *num_of_cycles = mfmc.dummy_clock_cycles;
            is_first_val = 0;
        } else {
            if (mfmc.dummy_clock_cycles != *num_of_cycles) {
                rc = MFE_MISMATCH_PARAM;
                break;
            }
        }
    }
    return rc;
}
