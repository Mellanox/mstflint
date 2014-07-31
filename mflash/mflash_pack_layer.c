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
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compatibility.h"
#include "bit_slice.h"
#include "mtcr.h"
#include "reg_access.h"

#include "mflash_types.h"
#include "mflash_pack_layer.h"

static MfError MError2MfError(MError rc);

int sx_st_block_access(mfile *mf, u_int32_t flash_addr, u_int8_t bank, u_int32_t size, u_int8_t* data,
        u_int8_t method)
{
    struct register_access_mfba mfba;
    int rc;
    int max_size = mget_max_reg_size(mf);
    if (!max_size) {
    	return MFE_BAD_PARAMS;
    }
    // when writing max size is limited to the nearest power of 2 of the max_size
    // while limiting it to 256 bytes
    max_size = NEAREST_POW2(max_size);


    if (size > (u_int32_t)max_size) {
        return MFE_BAD_PARAMS;
    }

    // Init mfba
    memset(&mfba, 0, sizeof(mfba));
    mfba.address = flash_addr;
    mfba.fs      = bank;
    mfba.size    = size;

    if (method == REG_ACCESS_METHOD_SET) {
        u_int32_t i;
        for (i = 0; i < size/4; i++) {
            mfba.data[i] = __le32_to_cpu(*((u_int32_t*)&(data[4*i])));
        }
    }
    rc = reg_access_mfba (mf, (reg_access_method_t) method, &mfba); CHECK_RC(MError2MfError(rc));

    // Get data from mfba
    if (method == REG_ACCESS_METHOD_GET) {
        u_int32_t i;
        for (i = 0; i < size/4; i++) {
            *((u_int32_t*)&(data[i*4]))= __cpu_to_le32(mfba.data[i]);
        }
    }
    return MFE_OK;
}


int common_erase_sector(mfile *mf, u_int32_t addr, u_int8_t flash_bank)
{
	struct register_access_mfbe    mfbe;

    memset(&mfbe, 0, sizeof(mfbe));
    mfbe.address = addr;
    mfbe.fs      = flash_bank;
    return MError2MfError(reg_access_mfbe (mf, REG_ACCESS_METHOD_SET, &mfbe));
}

int run_mfpa_command(mfile *mf, u_int8_t access_cmd, u_int8_t flash_bank, u_int32_t boot_address, u_int32_t *jedec_p)
{
	struct register_access_mfpa    mfpa;
    int rc;

    memset(&mfpa, 0, sizeof(mfpa));
    mfpa.fs = flash_bank;

    if (access_cmd == REG_ACCESS_METHOD_SET) {
        mfpa.boot_address = boot_address;
    }
    rc = reg_access_mfpa (mf, access_cmd, &mfpa);
    rc = MError2MfError(rc);
    if (rc && rc != MFE_REG_ACCESS_BAD_PARAM) {
        // if rc is REG_ACCESS_BAD_PARAM it means we dont have that flash bank connected (no need to fail)
        return rc;
    }

    if (access_cmd == REG_ACCESS_METHOD_GET && jedec_p != NULL) {
        *jedec_p = mfpa.jedec_id;
        // HACK: FW had a bug and returned the same jedec-ID even there was no flash, so when flash doesn't exist jedec will be modified to 0xffffffff
        if (flash_bank >= mfpa.flash_num || rc == MFE_REG_ACCESS_BAD_PARAM) {
            *jedec_p = 0xffffffff;
        }
    }
    return MFE_OK;
}

int com_get_jedec(mfile *mf, u_int8_t flash_bank, u_int32_t *jedec_p)
{
    return run_mfpa_command(mf, REG_ACCESS_METHOD_GET, flash_bank, 0, jedec_p);
}

int set_bank(mflash* mfl, u_int32_t addr) {
    int bank = addr >> mfl->attr.log2_bank_size;

    if (mfl->curr_bank != bank) {
        mfl->curr_bank = bank;
        return mfl->f_set_bank(mfl, bank);
    }

    return MFE_OK;
}

int get_flash_offset(u_int32_t addr, int log2_bank_size, u_int32_t *flash_addr_p)
{
    *flash_addr_p = addr & ONES32(log2_bank_size);
    return MFE_OK;
}

int mfl_get_bank_info(mflash *mfl, u_int32_t addr, u_int32_t *flash_off_p, int *bank_p)
{
    int rc;
    // Get the bank number
    rc = set_bank(mfl, addr);                                           CHECK_RC(rc);
    *bank_p = mfl->curr_bank;
    // Get the offset in the flash
    rc = get_flash_offset(addr, mfl->attr.log2_bank_size, flash_off_p); CHECK_RC(rc);
    return MFE_OK;
}

static MfError MError2MfError(MError rc) {
   switch(rc) {
   case ME_OK:
	   return MFE_OK;
   case ME_ERROR:
	   return MFE_ERROR;
   case ME_BAD_PARAMS:
	   return MFE_BAD_PARAMS;
   case ME_CR_ERROR:
	   return MFE_CR_ERROR;
   case ME_NOT_IMPLEMENTED:
	   return MFE_NOT_IMPLEMENTED;
   case ME_SEM_LOCKED:
	   return MFE_SEM_LOCKED;
   case ME_MEM_ERROR:
	   return MFE_NOMEM;
   case ME_MAD_SEND_FAILED:
	   return MFE_MAD_SEND_ERR;
   case ME_UNKOWN_ACCESS_TYPE:
	   return MFE_UNKOWN_ACCESS_TYPE;
   case ME_UNSUPPORTED_DEVICE:
	   return MFE_UNSUPPORTED_DEVICE;
   case ME_ICMD_STATUS_CR_FAIL:
	   return MFE_CR_ERROR;
   case ME_ICMD_STATUS_SEMAPHORE_TO:
	   return MFE_CMDIF_TIMEOUT_ERR;
   case ME_ICMD_STATUS_EXECUTE_TO:
	   return MFE_CMDIF_TIMEOUT_ERR;
   case ME_ICMD_STATUS_IFC_BUSY:
	   return MFE_CMDIF_TIMEOUT_ERR;
   case ME_ICMD_STATUS_ICMD_NOT_READY:
	   return MFE_CMDIF_GO_BIT_BUSY;
   case ME_ICMD_UNSUPPORTED_ICMD_VERSION:
	   return MFE_ICMD_NOT_SUPPORTED;
   case ME_ICMD_NOT_SUPPORTED:
	   return MFE_ICMD_NOT_SUPPORTED;
   case ME_ICMD_INVALID_OPCODE:
       return MFE_ICMD_INVALID_OPCODE;
   case ME_ICMD_INVALID_CMD:
       return MFE_ICMD_INVALID_CMD;
   case ME_ICMD_OPERATIONAL_ERROR:
       return MFE_ICMD_OPERATIONAL_ERROR;
   case ME_ICMD_BAD_PARAM:
       return MFE_ICMD_BAD_PARAM;
   case ME_ICMD_BUSY:
       return MFE_CMDIF_TIMEOUT_ERR;

   case ME_REG_ACCESS_BAD_METHOD:
       return MFE_REG_ACCESS_BAD_METHOD;
   case ME_REG_ACCESS_NOT_SUPPORTED:
       return MFE_REG_ACCESS_NOT_SUPPORTED;
   case ME_REG_ACCESS_DEV_BUSY:
       return MFE_REG_ACCESS_DEV_BUSY;
   case ME_REG_ACCESS_VER_NOT_SUPP:
       return MFE_REG_ACCESS_VER_NOT_SUPP;
   case ME_REG_ACCESS_UNKNOWN_TLV:
       return MFE_REG_ACCESS_UNKNOWN_TLV;
   case ME_REG_ACCESS_REG_NOT_SUPP:
       return MFE_REG_ACCESS_REG_NOT_SUPP;
   case ME_REG_ACCESS_CLASS_NOT_SUPP:
       return MFE_REG_ACCESS_CLASS_NOT_SUPP;
   case ME_REG_ACCESS_METHOD_NOT_SUPP:
       return MFE_REG_ACCESS_METHOD_NOT_SUPP;
   case ME_REG_ACCESS_BAD_PARAM:
       return MFE_REG_ACCESS_BAD_PARAM;
   case ME_REG_ACCESS_RES_NOT_AVLBL:
       return MFE_REG_ACCESS_RES_NOT_AVLBL;
   case ME_REG_ACCESS_MSG_RECPT_ACK:
       return MFE_REG_ACCESS_MSG_RECPT_ACK;
   case ME_REG_ACCESS_UNKNOWN_ERR:
       return MFE_REG_ACCESS_UNKNOWN_ERR;
   case ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
       return MFE_REG_ACCESS_SIZE_EXCCEEDS_LIMIT;
   default:
	   break;
   }
   return MFE_INVAL;
}
