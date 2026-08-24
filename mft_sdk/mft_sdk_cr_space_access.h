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
     * @brief Reads a block of dwords from the CR space.
     * @param mstDevice mstDevice handle.
     * @param address The address of the dwords to read.
     * @param data The data read from the CR space.
     * @param byteLength The number of bytes to read.
     * @return The status of the operation.
     */
    MstStatus mstReadCRSpace(MstDevice mstDevice, uint32_t address, uint32_t* data, int byteLength);

    /**
     * @brief Writes a block of dwords to the CR space.
     * @param mstDevice mstDevice handle.
     * @param address The address of the dwords to write.
     * @param data The data to write to the CR space.
     * @param byteLength The number of bytes to write.
     * @return The status of the operation.
     */
    MstStatus mstWriteCRSpace(MstDevice mstDevice, uint32_t address, uint32_t* data, int byteLength);

#ifdef __cplusplus
}
#endif