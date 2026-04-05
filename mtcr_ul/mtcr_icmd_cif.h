/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef _MTCR_ICMD_CIF /* guard */
#define _MTCR_ICMD_CIF

#ifdef __cplusplus
extern "C"
{
#endif

#include <compatibility.h>
#include <mtcr.h>
#ifdef MST_UL
#include "mtcr_mf.h"
#include <mtcr_int_defs.h>
#endif

    /* --------- Typedefs & Constants ---------------------------------- */

#ifndef IN
#define IN
#define OUT
#define INOUT
#endif

    MTCR_API extern int increase_poll_time;

    /* --------- Functional API ---------------------------------------- */
    /**
     * Create a device-context for the command-interface of a ConnectIB device.
     * @param[in] mf    Open mfile to the desired device.
     * @return          zero value on success, non zero value on failure.
     **/
    int icmd_open(mfile* mf);

    /**
     * Close an open device-context for the command-interface of a
     * ConnectIB device.
     * @param[in] dev   A pointer to a device context, previously
     *                  obtained by a call to <tt>gcif_open</tt>.
     **/
    void icmd_close(mfile* mf);

    /**
     * Handles the send command procedure.
     * for completeness, but calling it is strongly advised against.
     * @param[in] dev   A pointer to a device context, previously
     *                  obtained by a call to <tt>gcif_open</tt>.
     * @return          One of the GCIF_STATUS_* values, or a raw
     *                  status value (as indicated in cr-space).
     **/
    int icmd_send_command_int(mfile* mf,
                              IN int opcode,
                              INOUT void* data,
                              IN int write_data_size,
                              IN int read_data_size,
                              IN int skip_write);

    int icmd_send_command_enhanced(mfile* mf,
                                   IN int opcode,
                                   INOUT void* data,
                                   IN int write_data_size,
                                   IN int read_data_size,
                                   IN int skip_write);

    /**
     * Take the Tools-HCR semaphore. This functionality is provided
     * for completeness, but calling it is strongly advised against.
     * @param[in] dev   A pointer to a device context, previously
     *                  obtained by a call to <tt>gcif_open</tt>.
     * @return          One of the GCIF_STATUS_* values, or a raw
     *                  status value (as indicated in cr-space).
     **/
    int icmd_take_semaphore(mfile* mf);

    int is_livefish_device(mfile* mf);

#ifdef __cplusplus
}
#endif

#endif /* _MTCR_ICMD_CIF guard */
