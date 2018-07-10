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
 *
 * mlxcfg_status.h
 *
 *  Created on: Mar 23, 2015
 *      Author: adrianc
 */

#ifndef MLXCFG_STATUS_H_
#define MLXCFG_STATUS_H_

/*
 * Enum for handling error messages
 */

typedef enum {
    MCE_SUCCESS = 0,
    MCE_FAILED,
    MCE_TLV_NOT_FOUND,
    MCE_TLV_NOT_SUPP,
    MCE_NVCFG_NOT_SUPP,
    MCE_TOOLS_HCR_NOT_SUPP,
    MCE_DRIVER_DOWN,
    MCE_UNSUPPORTED_DEVICE,
    MCE_UNSUPPORTED_CFG,
    MCE_BAD_PARAMS,
    MCE_BAD_PARAM_VAL,
    MCE_DEV_BUSY,
    MCE_UNKNOWN_TLV,
    MCE_REG_NOT_SUPP,
    MCE_METHOD_NOT_SUPP,
    MCE_RES_NOT_AVAIL,
    MCE_CONF_CORRUPT,
    MCE_TLV_LEN_TOO_SMALL,
    MCE_BAD_CONFIG,
    MCE_ERASE_EXEEDED,
    MCE_BAD_OP,
    MCE_BAD_STATUS,
    MCE_CR_ERROR,
    MCE_NOT_IMPLEMENTED,
    MCE_INCOMPLETE_PARAMS,
    MCE_OPEN_DEVICE,
    MCE_PCI,
    MCE_GET_DEFAULT_PARAMS,
    MCE_UNKNOWN_ERR
} McStatus;


#endif /* MLXCFG_STATUS_H_ */
