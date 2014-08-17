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

#ifndef MFLASH_TYPES_H
#define MFLASH_TYPES_H

typedef enum MfError {
    MFE_OK = 0,
    MFE_ERROR,
    MFE_BAD_PARAMS,
    MFE_CR_ERROR,
    MFE_HW_DEVID_ERROR,
    MFE_INVAL,
    MFE_NOT_IMPLEMENTED,
    MFE_UNSUPPORTED_FLASH_TOPOLOGY,
    MFE_UNSUPPORTED_FLASH_TYPE,
    MFE_CFI_FAILED,
    MFE_TIMEOUT,
    MFE_ERASE_TIMEOUT,
    MFE_WRITE_TIMEOUT,
    MFE_ERASE_ERROR,
    MFE_WRITE_ERROR,
    MFE_BAD_ALIGN,
    MFE_SEM_LOCKED,
    MFE_VERIFY_ERROR,
    MFE_NOMEM,
    MFE_OUT_OF_RANGE,
    MFE_CMD_SUPPORTED_INBAND_ONLY,
    MFE_NO_FLASH_DETECTED,
    MFE_LOCKED_CRSPACE,
    MFE_CMDIF_BAD_STATUS_ERR,
    MFE_CMDIF_TIMEOUT_ERR,
    MFE_CMDIF_GO_BIT_BUSY,
    MFE_MISMATCH_KEY,
    MFE_UNKNOWN_REG,
    MFE_DIRECT_FW_ACCESS_DISABLED,
    MFE_MANAGED_SWITCH_NOT_SUPPORTED,
    MFE_NOT_SUPPORTED_OPERATION,
    MFE_FLASH_NOT_EXIST,
    MFE_MISMATCH_PARAM,
    MFE_EXCEED_SUBSECTORS_MAX_NUM,
    MFE_EXCEED_SECTORS_MAX_NUM,
    MFE_SECTORS_NUM_NOT_POWER_OF_TWO,
    MFE_UNKOWN_ACCESS_TYPE,
    MFE_UNSUPPORTED_DEVICE,
    MFE_OLD_DEVICE_TYPE,
    MFE_ICMD_INIT_FAILED,
    MFE_ICMD_NOT_SUPPORTED,
    MFE_HW_ACCESS_NOT_SUPP,
    MFE_MAD_SEND_ERR,
    MFE_ICMD_BAD_PARAM,
    MFE_ICMD_INVALID_OPCODE,
    MFE_ICMD_INVALID_CMD,
    MFE_ICMD_OPERATIONAL_ERROR,

    MFE_REG_ACCESS_BAD_METHOD,
    MFE_REG_ACCESS_NOT_SUPPORTED,
    MFE_REG_ACCESS_DEV_BUSY,
    MFE_REG_ACCESS_VER_NOT_SUPP,
    MFE_REG_ACCESS_UNKNOWN_TLV,
    MFE_REG_ACCESS_REG_NOT_SUPP,
    MFE_REG_ACCESS_CLASS_NOT_SUPP,
    MFE_REG_ACCESS_METHOD_NOT_SUPP,
    MFE_REG_ACCESS_BAD_PARAM,
    MFE_REG_ACCESS_RES_NOT_AVLBL,
    MFE_REG_ACCESS_MSG_RECPT_ACK,
    MFE_REG_ACCESS_UNKNOWN_ERR,
    MFE_REG_ACCESS_SIZE_EXCCEEDS_LIMIT,




    MFE_LAST
} MfError;

#endif // MFLASH_TYPES_H



