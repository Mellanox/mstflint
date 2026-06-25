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
#include <mft_sdk/mft_sdk_query.h>
#include <mft_sdk/mft_sdk_telemetry_types.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Gets the Telemetry Operational info of the device. Equivalent to Mlxlink's general query "Operating Info"
     * page.
     * @param mstDevice The MstDevice handle.
     * @param operationalInfo The Telemetry Operational info struct to fill. Should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetTelemetryOperationalInfo(MstDevice mstDevice, MstTelemetryOperationalInfo* operationalInfo);

    /**
     * @brief Gets the FEC histogram of the device. Equivalent to Mlxlink's "--show_histogram
     * --rx_fec_histogram" command.
     * @param mstDevice The MstDevice handle.
     * @param fecHistogram The FEC histogram struct to fill.
     * @return The status of the operation.
     */
    MstStatus mstGetFecHistogram(MstDevice mstDevice, MstFecHistogram* fecHistogram);

    /**
     * @brief Gets the counters info of the device. Equivalent to Mlxlink's "show counters" command.
     * @param mstDevice The MstDevice handle.
     * @param countersInfo The counters info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetCountersInfo(MstDevice mstDevice, MstCountersInfo* countersInfo);

    /**
     * @brief Gets the Cable DDM info of the device. Equivalent to Mlxlink's "--cable --ddm" command.
     * @param mstDevice The MstDevice handle.
     * @param cableDDMInfo The Cable DDM info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetCableDDMInfo(MstDevice mstDevice, MstCableDDMInfo* cableDDMInfo);

    /**
     * @brief Gets the Module info of the device. Equivalent to Mlxlink's "--show_module" command.
     * @param mstDevice The MstDevice handle.
     * @param moduleInfo The Module info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetModuleInfo(MstDevice mstDevice, MstModuleInfo* moduleInfo);

#ifdef __cplusplus
}
#endif