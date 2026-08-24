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

#include <stdint.h>
#include <stdbool.h>
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Sets the I2C secondary address.
     * @param mstDevice mstDevice handle.
     * @param newI2cSecondaryAddress The new I2C secondary address.
     * @return The status of the operation.
     */
    MstStatus mstSetI2cSecondary(MstDevice mstDevice, uint8_t newI2cSecondaryAddress);
    /**
     * @brief Gets the I2C secondary address.
     * @param mstDevice mstDevice handle.
     * @param i2cSecondaryAddress Output parameter for the current I2C secondary address.
     * @return The status of the operation.
     */
    MstStatus mstGetI2cSecondary(MstDevice mstDevice, uint8_t* i2cSecondaryAddress);
#ifdef __cplusplus
}
#endif