
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mflash.h"
#include "mflash_common.h"
#include "mflash_inband.h"
#include "mflash_access_layer.h"


#ifdef NO_INBAND_ACCESS

int sx_get_flash_info_by_type(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    mfl = NULL;
    type_index = NULL;
    log2size = NULL;
    no_flash = NULL;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_block_read_by_type(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data)
{
    mfl = NULL;
    blk_addr = 0;
    blk_size = 0;
    data = NULL;

    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_block_write_by_type(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    mfl = NULL;
    addr = 0;
    size = 0;
    data = NULL;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_flash_lock_by_type(mflash* mfl, int lock_state)
{
    mfl = NULL;
    lock_state = 0;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_erase_sect_by_type(mflash* mfl, u_int32_t addr)
{
    mfl = NULL;
    addr = 0;
    return MFE_NOT_SUPPORTED_OPERATION;
}

#else

int sx_get_flash_info_by_type(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    int rc;
    u_int8_t vendor, type, capacity;
    u_int32_t jedec_id;

    rc = mfi_get_jedec(mfl->cmdif_context, (mfl->curr_bank), &jedec_id);
    CHECK_RC(rc);

    //printf("-D- jedec_id = %#x\n", jedec_id);
    rc = get_info_from_jededc_id(jedec_id, &vendor, &type, &capacity); CHECK_RC(rc);

    // Return there is no flash when all the params are 0xff
    if (vendor == 0xff && type == 0xff && capacity == 0xff) {
        *no_flash = 1;
        return MFE_OK;
    }
    rc = get_type_index_by_vendor_and_type(vendor, type, type_index); CHECK_RC(rc);
    rc = get_log2size_by_capcity(*type_index, capacity, log2size);    CHECK_RC(rc);
    return MFE_OK;

}

int sx_block_read_by_type(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data)
{
    int rc, bank;
    u_int32_t flash_offset;

    if (blk_size > (u_int32_t)mfl->attr.block_write  || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }
    rc = mfl_get_bank_info(mfl, blk_addr, &flash_offset, &bank); CHECK_RC(rc);
    COM_CHECK_ALLIGN(flash_offset, blk_size);
    rc = mfi_read_block(mfl->cmdif_context, flash_offset, bank, blk_size, data);
    CHECK_RC(rc);
    return MFE_OK;
}

int sx_block_write_by_type(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    int rc, bank;
    u_int32_t flash_offset;

    WRITE_CHECK_ALLIGN(addr, mfl->attr.block_write, size);

    rc = mfl_get_bank_info(mfl, addr, &flash_offset, &bank); CHECK_RC(rc);
    COM_CHECK_ALLIGN(flash_offset, size);
    rc = mfi_write_block(mfl->cmdif_context, flash_offset, bank, size, data);
    CHECK_RC(rc);
    return MFE_OK;
}

int sx_flash_lock_by_type(mflash* mfl, int lock_state)
{
	int rc;
    rc = mfi_flash_lock(mfl->cmdif_context, lock_state);
    CHECK_RC(rc);

    return MFE_OK;
}

int sx_erase_sect_by_type(mflash* mfl, u_int32_t addr)
{
    int rc, bank;
    u_int32_t flash_addr;

    rc = mfl_get_bank_info(mfl, addr, &flash_addr, &bank);
    CHECK_RC(rc);
    rc = mfi_erase_sector(mfl->cmdif_context, flash_addr, bank);
    CHECK_RC(rc);

    return MFE_OK;
}

#endif

#define BOOT_CR_SPACE_ADDR 0xf0000
#define ATBM_MLNXOS_CMDIF 2
int     mf_update_boot_addr_by_type(mflash* mfl, u_int32_t boot_addr)
{
    int rc;
    if (mfl->access_type == MFAT_UEFI || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF) {
        return MFE_NOT_SUPPORTED_OPERATION;
    } else {
        rc = mf_cr_write(mfl, BOOT_CR_SPACE_ADDR, ((boot_addr << 8) | 0x06)); CHECK_RC(rc);
    }
    return MFE_OK;
}

////////////////////////////   Function that sends mads //////////////////////////////////////
int maccess_reg_mad_wrapper(flash_access_t *facces, u_int8_t *data, int w_cmdif_size, int r_cmdif_size)
{
	//avoid warnings
	w_cmdif_size=0;
	r_cmdif_size=0;
	//

    int rc;
    if (facces->access_type == FWACCESS_INBAND) {
        rc = maccess_reg_mad(facces->mf, data);
        if (rc) {
            //printf("-E- 2. Access reg mad failed with rc = %#x\n", rc);
            return MFE_REG_ACCESS_FAILED;
        }
    } else {
        return MFE_NOT_IMPLEMENTED;
    }
    return MFE_OK;
}
