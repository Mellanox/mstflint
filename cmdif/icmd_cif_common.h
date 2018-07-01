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

#ifndef _ICMD_COMMON_
#define _ICMD_COMMON_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif


/* --------- Typedefs & Constants ---------------------------------- */

/**
 * Possible status values returned by the API functions.
 * In some cases the status indicated in the cr-space may not fit
 * any of the below enumeration values, in which case the raw status
 * value will be returned.
 **/
enum {
    GCIF_STATUS_SUCCESS = 0,
    GCIF_STATUS_INVALID_OPCODE,
    GCIF_STATUS_INVALID_CMD,
    GCIF_STATUS_OPERATIONAL_ERROR,
    GCIF_STATUS_BAD_PARAM,
    GCIF_STATUS_CR_FAIL,        // cr-space access failure
    GCIF_STATUS_BAD_OPCODE,                 // unsupported opcode was used
    GCIF_STATUS_SEMAPHORE_TO,               // timed out while trying to take semaphore
    GCIF_STATUS_EXECUTE_TO,                 // timed out while waiting for command to execute
    GCIF_STATUS_IFC_BUSY,                   // command-interface is busy executing another command
    GCIF_STATUS_BAD_PARAMETERS,
    GCIF_STATUS_GENERAL_ERROR,
    GCIF_STATUS_ICMD_NOT_READY,
    GCIF_STATUS_UNSUPPORTED_ICMD_VERSION,
    GCIF_STATUS_ICM_NOT_AVAIL,
    GCIF_STATUS_WRITE_PROTECT,
    GCIF_STATUS_NO_MEM,
    GCIF_SIZE_EXCEEDS_LIMIT,
    GCIF_ICMD_NOT_SUPPORTED,
    GCIF_ICMD_INIT_FAILED,
    GCIF_ICMD_BUSY,
    GCIF_STATUS_UNKNOWN_STATUS
};

enum {
    RW_READ  = 0x1,
    RW_WRITE = 0x0
};

/* --------- Functional API ---------------------------------------- */

/**
 * Returns the last error message recorded by the library
 **/
char* gcif_get_last_err();

/**
 * Returns the error message associated with the provided return code
 **/
char* gcif_err_str(int rc);

#ifdef __cplusplus
}
#endif


#endif
