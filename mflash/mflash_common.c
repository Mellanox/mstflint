
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

int init_operation_tlv(struct OperationTlv *operation_tlv, u_int16_t reg_id, u_int8_t method)
{
    memset(operation_tlv, 0, sizeof(*operation_tlv));

    operation_tlv->Type        = TLV_OPERATION;
    operation_tlv->class       = MAD_CLASS_REG_ACCESS;
    operation_tlv->len         = TLV_OPERATION_SIZE;
    operation_tlv->method      = method;
    operation_tlv->register_id = reg_id;
    return MFE_OK;
}

int get_reg_info_by_id(u_int16_t reg_id, reg_info_t *reg_info)
{
    u_int32_t i;
    reg_info_t reg_info_arr[] = {
            {REG_ID_MFPA, RTL_MFPA_LEN, (f_reg_pack)mfpa_pack,     (f_reg_unpack)mfpa_unpack,     (f_reg_dump)mfpa_dump},
            {REG_ID_MFBA, RTL_MFBA_LEN, (f_reg_pack)mfba_mad_pack, (f_reg_unpack)mfba_mad_unpack, (f_reg_dump)mfba_mad_dump},
            {REG_ID_MFBE, RTL_MFBE_LEN, (f_reg_pack)mfbe_pack,     (f_reg_unpack)mfbe_unpack,     (f_reg_dump)mfbe_dump},
    };

    for (i = 0; i < ARR_SIZE(reg_info_arr); i++) {
        reg_info_t curr_reg = reg_info_arr[i];
        if (reg_id == curr_reg.id) {
            *reg_info = curr_reg;
            return MFE_OK;
        }
    }
    return MFE_UNKNOWN_REG;
}


int sx_st_block_access(flash_access_t *faccess, u_int32_t flash_addr, u_int8_t bank, u_int32_t size, u_int8_t* data,
        u_int8_t method)
{
    struct mfba_mad    mfba;
    int rc;
    u_int32_t max_size = CMDIF_MAX_BLOCK_WRITE;

    if (faccess->access_type == FWACCESS_INBAND) {
        max_size = INBAND_MAX_BLOCK_WRITE;
    }

    if (size > max_size) {
        return MFE_BAD_PARAMS;
    }

    // rc = set_bank(mfl, addr); CHECK_RC(rc);
    //rc = get_flash_offset(addr, mfl->attr.log2_bank_size, &flash_addr); CHECK_RC(rc);


    // Init mfba
    memset(&mfba, 0, sizeof(mfba));
    mfba.address = flash_addr;
    mfba.fs      = bank;
    mfba.size    = size;

    if (method == MAD_METHOD_WRITE) {
        u_int32_t i;
        for (i = 0; i < size/4; i++) {
            mfba.data[i] = __le32_to_cpu(*((u_int32_t*)&(data[4*i])));
        }
    }

    rc = mfi_reg_access_mad(faccess, REG_ID_MFBA, method, &mfba, 0); CHECK_RC(rc);

    // Get data from mfba
    if (method == MAD_METHOD_QUERY) {
        u_int32_t i;
        for (i = 0; i < size/4; i++) {
            *((u_int32_t*)&(data[i*4]))= __cpu_to_le32(mfba.data[i]);
        }
    }
    return MFE_OK;
}


int common_erase_sector(flash_access_t *faccess, u_int32_t addr, u_int8_t flash_bank)
{
    struct mfbe    mfbe;

    memset(&mfbe, 0, sizeof(mfbe));
    mfbe.address = addr;
    mfbe.fs      = flash_bank;
    return mfi_reg_access_mad(faccess, REG_ID_MFBE, MAD_METHOD_WRITE, &mfbe, 0);
}



int run_mfpa_command(flash_access_t *faccess, u_int8_t access_cmd, u_int8_t flash_bank, u_int32_t boot_address, u_int32_t *jedec_p)
{
    struct mfpa    mfpa;
    int rc;

    memset(&mfpa, 0, sizeof(mfpa));
    mfpa.fs = flash_bank;

    if (access_cmd == MAD_METHOD_WRITE) {
        mfpa.boot_address = boot_address;
    }

    rc = mfi_reg_access_mad(faccess, REG_ID_MFPA, access_cmd, &mfpa, 0); CHECK_RC(rc);

    if (access_cmd == MAD_METHOD_QUERY && jedec_p != NULL) {
        *jedec_p = mfpa.jedec_id;
        // HACK: FW had a bug and returned the same jedec-ID even there was no flash, so when flash doesn't exist jedec will be modified to 0xffffffff
        if (flash_bank >= mfpa.flash_num) {
            *jedec_p = 0xffffffff;
        }
    }
    return MFE_OK;
}

int com_get_jedec(flash_access_t *faccess, u_int8_t flash_bank, u_int32_t *jedec_p)
{
    return run_mfpa_command(faccess, MAD_METHOD_QUERY, flash_bank, 0, jedec_p);
}
