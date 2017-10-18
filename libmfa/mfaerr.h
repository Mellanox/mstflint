/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
#ifndef _MFA_ERR_H_
#define _MFA_ERR_H_

enum {
    MFA_OK =  0,
    MFA_ERR_GENERIC,
    MFA_ERR_MEM_ALLOC,
    MFA_ERR_ARCHV_SIGNATURE,
    MFA_ERR_ARCHV_VER_UNSUPP,
    MFA_ERR_ARCHV_CRC,
    MFA_ERR_ARCHV_FORMAT,
    MFA_ERR_FILE_OPEN,
    MFA_ERR_FILE_READ,
    MFA_ERR_IMG_GETSZ,
    MFA_ERR_IMG_GET,
    MFA_ERR_UNKNOWN_TYPE,
    MFA_ERR_NO_ENTRY,
    MFA_ERR_FIELD_NOT_FOUND,
    MFA_ERR_DECOMPRESSION,
    MFA_ERR_FSEEK,
    MFA_ERR_FTELL,
    MFA_ERR_BUFF_SIZE
};

#endif
