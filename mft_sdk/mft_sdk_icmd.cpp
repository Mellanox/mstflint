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

#include "mft_sdk/mft_sdk_icmd.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mtcr.h"
#include <limits>

MstStatus MftSdk::sendIcmd(uint32_t opcode, void* data, uint32_t dataSize, MstIcmdAccessMethod method)
{
    if (!_mf || !data || dataSize == 0)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    if (method != MST_ICMD_WRITE_READ && method != MST_ICMD_READ_ONLY)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    // icmd_send_command() takes signed ints, and its size check only rejects
    // oversized lengths - a value past INT_MAX would arrive negative and slip
    // through it, so reject it here instead of narrowing.
    const uint32_t maxSigned = static_cast<uint32_t>(std::numeric_limits<int>::max());
    if (opcode > maxSigned || dataSize > maxSigned)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    int skipWrite = (method == MST_ICMD_READ_ONLY) ? 1 : 0;
    _syndromeCode = 0;
    int rc = icmd_send_command(_mf, static_cast<int>(opcode), data, static_cast<int>(dataSize), skipWrite);
    if (rc)
    {
        // mtcr records the FW syndrome on the mfile, so hand it to mstGetSyndrome() as well.
        _syndromeCode = static_cast<uint32_t>(_mf->icmd.syndrome);
        // rc is an MError ICMD status, or a raw cr-space status m_err2str has no name for - keep the
        // numeric value next to the text so an unnamed status is still identifiable.
        std::string errorMessage = "Failed to send ICMD opcode " + std::to_string(opcode) + " to device " +
                                   _deviceIdentifier + ", ICMD status " + m_err2str(static_cast<MError>(rc)) + " (" +
                                   std::to_string(rc) + "), syndrome " + std::to_string(_syndromeCode);
        setLastError(MST_ERROR_FAILED_TO_SEND_ICMD, errorMessage);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus
      mstSendIcmd(MstDevice mstDevice, uint32_t opcode, void* data, uint32_t dataSize, MstIcmdAccessMethod method)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->sendIcmd(opcode, data, dataSize, method);
    }
} // extern "C"
