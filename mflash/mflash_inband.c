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

#include "mflash.h"
#include "mflash_common.h"
#include "mflash_access_layer.h"
#include "mflash_inband.h"


int mfi_reg_access_mad(flash_access_t *faccess, u_int16_t reg_id, u_int8_t method, void *reg, u_int8_t debug)
{
    int rc, mad_rc, cmdif_size = 0, wcmdif_size, rcmdif_size;
    struct OperationTlv tlv;
    struct reg_tlv tlv_info;
    u_int8_t buffer[1024];
    reg_info_t reg_info;

    rc = get_reg_info_by_id(reg_id, &reg_info); CHECK_RC(rc);

    init_operation_tlv(&(tlv), reg_id, method);
    // Fill Reg TLV
    memset(&tlv_info, 0, sizeof(tlv_info));
    tlv_info.Type = TLV_REG;
    tlv_info.len  = reg_info.len;

    // The max MAD buffer size is 64 so max data that can be read is only 32 byte
    if ((reg_id == REG_ID_MFBA && faccess->access_type == FWACCESS_INBAND )||
        (reg_id == REG_ID_MFBA && faccess->access_type == FWACCESS_UEFI) ) {
        tlv_info.len  = RTL_INBAND_MFBA_LEN;
    }

    // Pack the mad

    cmdif_size += OperationTlv_pack(&tlv, buffer);
    cmdif_size += reg_tlv_pack(&tlv_info, buffer + OP_TLV_SIZE);
    cmdif_size += reg_info.pack_func(reg, buffer + OP_TLV_SIZE + REG_RLV_HEADER_LEN);
#ifdef _ENABLE_MFLASH_INBAND_DEBUG
    if (debug) {
        printf("-I- The sent MAD content\n");
        OperationTlv_dump(&tlv, stdout);
        reg_tlv_dump(&tlv_info, stdout);
        reg_info.dump_func(reg, stdout);
    }
#endif
    // printf("-D- reg_info.len = |%d, OP_TLV: %d, REG_TLV= %d, cmdif_size = %d\n", reg_info.len, OP_TLV_SIZE, REG_RLV_HEADER_LEN, cmdif_size);
    wcmdif_size = cmdif_size;
    rcmdif_size = cmdif_size;

    // Improve the performance by not writing data in read to icmd buffer or not reading in write command

    if (reg_id == REG_ID_MFBA) {
        if (method == MAD_METHOD_QUERY) {
            wcmdif_size = cmdif_size - CMDIF_MAX_BLOCK_WRITE;
        } else {
           rcmdif_size = cmdif_size - CMDIF_MAX_BLOCK_WRITE;
        }
    }

    mad_rc = maccess_reg_mad_wrapper(faccess, buffer, wcmdif_size, rcmdif_size);
    // Unpack the mad
    OperationTlv_unpack(&tlv, buffer);
    reg_tlv_unpack(&tlv_info, buffer + OP_TLV_SIZE);
    reg_info.unpack_func(reg, buffer + OP_TLV_SIZE + REG_RLV_HEADER_LEN);


#ifdef _ENABLE_MFLASH_INBAND_DEBUG
    if (debug) {
        printf("-I- The received MAD content\n");
        OperationTlv_dump(&tlv, stdout);
        reg_tlv_dump(&tlv_info, stdout);
        reg_info.dump_func(reg, stdout);
    }
#endif
    // Check the return value from
    CHECK_RC(mad_rc);
    if (tlv.status) {

        // printf("-E- Access reg mad failed with tlv status = %#x\n", tlv.status);
        switch (tlv.status) {
        case 0x4:
            return MFE_REG_ACCESS_MAD_NOT_SUPPORTED;
        case 0x8:
            return MFE_REG_ACCESS_RESOURCE_NOT_AVAILABLE;
        default:
            // printf("-D- status = %d\n", tlv.status);
            return MFE_REG_ACCESS_MAD_BAD_STATUS;
        }
    }
    return MFE_OK;
}

int mfi_erase_sector(mfile *mf, u_int32_t addr, u_int8_t flash_bank)
{
    flash_access_t faccess;
    faccess.mf = mf;
    faccess.access_type = FWACCESS_INBAND;
    return common_erase_sector(&faccess, addr, flash_bank);
}


int mfi_get_jedec(mfile *mf, u_int8_t flash_bank, u_int32_t *jedec_p)
{
    flash_access_t faccess;
    faccess.mf = mf;
    faccess.access_type = FWACCESS_INBAND;
    return com_get_jedec(&faccess, flash_bank, jedec_p);
}

int mfi_read_block(mfile *mf, u_int32_t addr, u_int8_t flash_bank, u_int32_t size, u_int8_t* data)
{
    flash_access_t faccess;
    faccess.mf = mf;
    faccess.access_type = FWACCESS_INBAND;
    // printf("-D- mfi_read_block: addr = %#x, size = %d\n", addr, size);
    return sx_st_block_access(&faccess, addr, flash_bank, size, data, MAD_METHOD_QUERY);
}

int mfi_write_block(mfile *mf, u_int32_t addr, u_int8_t flash_bank, u_int32_t size, u_int8_t* data)
{
    flash_access_t faccess;
    faccess.mf = mf;
    faccess.access_type = FWACCESS_INBAND;
    return sx_st_block_access(&faccess, addr, flash_bank, size, data, MAD_METHOD_WRITE);
}

int mfi_flash_lock(mfile *mf, int lock_state)
{
    mf = NULL;
    lock_state = 0;
    return MFE_OK;
}

int mfi_update_boot_addr(mfile *mf, u_int8_t flash_bank, u_int32_t boot_addr)
{
    mf = NULL;
    flash_bank = 0;
    boot_addr = 0;
    return MFE_NOT_IMPLEMENTED;
}
