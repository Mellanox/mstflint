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

#include "mtcr.h"
#include "reg_access.h"

#include "mflash_types.h"
#include "mflash_pack_layer.h"
#include "mflash_access_layer.h"

 // On windows we don't support cmdIf access!
int check_access_type(mflash* mfl)
//TODO: re-write in a more elegant way.
{
    if (mfl->access_type == MFAT_MFILE) {
        if ( mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_INBAND) {
#ifdef NO_INBAND_ACCESS
        	return MFE_NOT_SUPPORTED_OPERATION;
#endif
#ifndef _WIN_
        } else if ( mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF) {
#endif
        } else if ( mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD) {
        } else {
            return MFE_UNKOWN_ACCESS_TYPE;
        }
	} else if (mfl->access_type == MFAT_UEFI) {
    } else {
        return MFE_UNKOWN_ACCESS_TYPE;
    }
    return MFE_OK;
}


int sx_get_flash_info_by_type(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    int rc;
    u_int8_t vendor, type, capacity;
    u_int32_t jedec_id;

    rc = check_access_type( mfl); CHECK_RC(rc);
    rc = com_get_jedec(mfl->mf, mfl->curr_bank, &jedec_id); CHECK_RC(rc);
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

    rc = check_access_type( mfl); CHECK_RC(rc);
    rc = sx_st_block_access(mfl->mf, flash_offset, bank, blk_size, data, REG_ACCESS_METHOD_GET);CHECK_RC(rc);

    return MFE_OK;
}

int sx_block_write_by_type(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    int rc, bank;
    u_int32_t flash_offset;

    WRITE_CHECK_ALLIGN(addr, mfl->attr.block_write, size);


    rc = mfl_get_bank_info(mfl, addr, &flash_offset, &bank); CHECK_RC(rc);
    COM_CHECK_ALLIGN(flash_offset, size);

    rc = check_access_type( mfl); CHECK_RC(rc);
    rc = sx_st_block_access(mfl->mf, flash_offset, bank, size, data, REG_ACCESS_METHOD_SET);CHECK_RC(rc);
    return MFE_OK;
}

int sx_flash_lock_by_type(mflash* mfl, int lock_state)
{
	//AdrianC: this is not implemented for some reason
	(void)mfl;
	(void)lock_state;
    return MFE_OK;
}

int sx_erase_sect_by_type(mflash* mfl, u_int32_t addr)
{
    int rc, bank;
    u_int32_t flash_addr;

    rc = mfl_get_bank_info(mfl, addr, &flash_addr, &bank); CHECK_RC(rc);
    rc = check_access_type( mfl); CHECK_RC(rc);
    rc = common_erase_sector(mfl->mf, flash_addr, bank); CHECK_RC(rc);
    return MFE_OK;
}

int     mf_update_boot_addr_by_type(mflash* mfl, u_int32_t boot_addr)
{
    int rc;
    if (mfl->access_type == MFAT_UEFI || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_MLNXOS_CMDIF) {
    	// for inband or cib fwaccess return MFE_NOT_IMPLEMENTED
    	// for cmdIF fwaccess i.e mlnxOS update boot addr via reg access
    	if (mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_INBAND || mfl->opts[MFO_FW_ACCESS_TYPE_BY_MFILE] == ATBM_ICMD) {
    		return MFE_NOT_IMPLEMENTED;
    	}
    	else {
    	// uefi is supported and MLNXOS
    	rc = run_mfpa_command(mfl->mf, REG_ACCESS_METHOD_SET, mfl->curr_bank, boot_addr, NULL); CHECK_RC(rc);
    	}
    }
    return MFE_OK;
}
