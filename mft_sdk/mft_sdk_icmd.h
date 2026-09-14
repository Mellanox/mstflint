/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id$
 *
 */

#pragma once

#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief ICMD access method - whether the input buffer is written to the mailbox before executing.
     */
    typedef enum
    {
        MST_ICMD_WRITE_READ = 1, /**< Write the input to the mailbox, then read the output back. */
        MST_ICMD_READ_ONLY = 2,  /**< Leave the mailbox as is and only read the output back. */
    } MstIcmdAccessMethod;

    /**
     * @brief Sends an ICMD (internal command) to the device firmware.
     * @param mstDevice mstDevice handle.
     * @param opcode The ICMD opcode to send.
     * @param data Caller allocated in/out buffer: holds the command input on entry and is overwritten
     *             with the firmware output on return. The same buffer and size serve both directions.
     * @param dataSize The size of the data buffer in bytes.
     * @param method Whether to write the input before executing. Commands that take input parameters -
     *               queries included - need MST_ICMD_WRITE_READ.
     * @return The status of the operation. MST_ERROR_INVALID_ARGUMENT if mstDevice or data is NULL, if
     *         dataSize is zero, if method is not an MstIcmdAccessMethod value, or if opcode or dataSize
     *         exceeds INT_MAX; MST_ERROR_FAILED_TO_SEND_ICMD if the command failed - call
     *         mstGetLastErrorString for the reason and mstGetSyndrome for the firmware syndrome.
     */
    MstStatus
      mstSendIcmd(MstDevice mstDevice, uint32_t opcode, void* data, uint32_t dataSize, MstIcmdAccessMethod method);

#ifdef __cplusplus
}
#endif
