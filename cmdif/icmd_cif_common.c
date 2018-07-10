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

#include <mtcr.h>
#include "icmd_cif_common.h"

/*
 * get_last_err
 */
char* gcif_get_last_err()
{
    return "Deprecated: General Error";
}

/*
 * gcif_err_str
 */
char* gcif_err_str(int rc)
{

    switch (rc) {
    case GCIF_STATUS_SUCCESS:
        return "OK";

    case GCIF_STATUS_INVALID_OPCODE:
        return "Invalid opcode";

    case GCIF_STATUS_INVALID_CMD:
        return "Invalid cmd";

    case GCIF_STATUS_OPERATIONAL_ERROR:
        return "Operational error";

    case GCIF_STATUS_CR_FAIL:
        return "cr-space access failure";

    case GCIF_STATUS_BAD_OPCODE:
        return "unsupported opcode was used";

    case GCIF_STATUS_SEMAPHORE_TO:
        return "timed out while trying to take semaphore";

    case GCIF_STATUS_EXECUTE_TO:
        return "timed out while waiting for command to execute";

    case GCIF_STATUS_IFC_BUSY:
        return "command-interface is busy executing another command";

    case GCIF_STATUS_BAD_PARAMETERS:
        return "bad parameter";

    case GCIF_STATUS_ICMD_NOT_READY:
        return "command interface not ready";

    case GCIF_STATUS_BAD_PARAM:
        return "command interface bad param";

    case GCIF_STATUS_UNSUPPORTED_ICMD_VERSION:
        return "Unsupported icmd version";

    case GCIF_STATUS_UNKNOWN_STATUS:
        return "Unknown ICMD Status.";

    case GCIF_STATUS_GENERAL_ERROR:
        return "General error";

    case GCIF_SIZE_EXCEEDS_LIMIT:
        return "Size exceeds limit";

    case GCIF_ICMD_NOT_SUPPORTED:
        return "icmd not supported";

    case GCIF_ICMD_INIT_FAILED:
        return "icmd initialization failed";

    case GCIF_ICMD_BUSY:
        return "icmd busy";

    case GCIF_STATUS_ICM_NOT_AVAIL:
        return "ICM not available";

    default:
        return "Unknown error";
    }
}

/*
 * convert_rc
 */

int convert_rc(int rc)
{
    switch (rc) {
    case ME_ICMD_STATUS_CR_FAIL:
        return GCIF_STATUS_CR_FAIL;

    case ME_ICMD_STATUS_SEMAPHORE_TO:
        return GCIF_STATUS_SEMAPHORE_TO;

    case ME_ICMD_STATUS_EXECUTE_TO:
        return GCIF_STATUS_EXECUTE_TO;

    case ME_ICMD_STATUS_IFC_BUSY:
        return GCIF_STATUS_IFC_BUSY;

    case ME_ICMD_STATUS_ICMD_NOT_READY:
        return GCIF_STATUS_ICMD_NOT_READY;

    case ME_ICMD_UNSUPPORTED_ICMD_VERSION:
        return GCIF_STATUS_UNSUPPORTED_ICMD_VERSION;

    case ME_ICMD_INVALID_OPCODE:
        return GCIF_STATUS_INVALID_OPCODE;

    case ME_ICMD_INVALID_CMD:
        return GCIF_STATUS_INVALID_CMD;

    case ME_ICMD_OPERATIONAL_ERROR:
        return GCIF_STATUS_OPERATIONAL_ERROR;

    case ME_ICMD_BAD_PARAM:
        return GCIF_STATUS_BAD_PARAM;

    case ME_ICMD_ICM_NOT_AVAIL:
        return GCIF_STATUS_ICM_NOT_AVAIL;

    case ME_ICMD_WRITE_PROTECT:
        return GCIF_STATUS_WRITE_PROTECT;

    case ME_ICMD_UNKNOWN_STATUS:
        return GCIF_STATUS_UNKNOWN_STATUS;

    case ME_ICMD_SIZE_EXCEEDS_LIMIT:
        return GCIF_SIZE_EXCEEDS_LIMIT;

    case ME_ICMD_NOT_SUPPORTED:
        return GCIF_ICMD_NOT_SUPPORTED;

    case ME_ICMD_INIT_FAILED:
        return GCIF_ICMD_INIT_FAILED;

    case ME_ICMD_BUSY:
        return GCIF_ICMD_BUSY;

    default:
        break;
    }
    return GCIF_STATUS_GENERAL_ERROR;
}
