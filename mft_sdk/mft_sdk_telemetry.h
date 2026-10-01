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
     * @brief Telemetry views selectable by mstGetTelemetryJson(). Combine with bitwise OR.
     */
    typedef enum MstTelemetryView
    {
        MST_TELEMETRY_VIEW_OPERATIONAL = 1 << 0, /**< Operating info section. */
        MST_TELEMETRY_VIEW_COUNTERS = 1 << 1,    /**< Physical counters / BER section. */
        MST_TELEMETRY_VIEW_CABLE_DDM = 1 << 2,   /**< Cable DDM sections. */
        MST_TELEMETRY_VIEW_MODULE = 1 << 3,      /**< Full "--show_module" view (implies operating). */
        MST_TELEMETRY_VIEW_GENERAL =
          1 << 4, /**< Full mlxlink default (showPddr): Operational/Port/[CPO]/Supported/Troubleshooting/Tool. */
        MST_TELEMETRY_VIEW_EYE = 1 << 5,           /**< "--show_eye" EYE Opening Info section. */
        MST_TELEMETRY_VIEW_FEC = 1 << 6,           /**< "--show_fec" FEC Capability Info section. */
        MST_TELEMETRY_VIEW_SERDES_TX = 1 << 7,     /**< "--show_serdes_tx" Serdes TX (SLTP) section. */
        MST_TELEMETRY_VIEW_BER_MONITOR = 1 << 8,   /**< "--show_ber_monitor" BER Monitor Info section. */
        MST_TELEMETRY_VIEW_EXTERNAL_PHY = 1 << 9,  /**< "--show_external_phy" External PHY Info section. */
        MST_TELEMETRY_VIEW_PLR = 1 << 10,          /**< "--show_plr" PLR Info section. */
        MST_TELEMETRY_VIEW_KR = 1 << 11,           /**< "--show_kr" KR Startup Info section. */
        MST_TELEMETRY_VIEW_RX_RECOVERY = 1 << 12,  /**< "--show_rx_recovery_counters" Rx Recovery Counters section. */
        MST_TELEMETRY_VIEW_FEC_HISTOGRAM = 1 << 13 /**< "--show_histogram" FEC histogram section. */
    } MstTelemetryView;

    /**
     * @brief Gets the Telemetry Operational info of the device. Equivalent to Mlxlink's general query "Operating Info"
     * page.
     * @param mstDevice The MstDevice handle.
     * @param context Context options (port and future flags), or NULL for the device defaults. Initialize with
     * MST_TELEMETRY_CONTEXT_INIT.
     * @param operationalInfo The Telemetry Operational info struct to fill. Should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetTelemetryOperationalInfo(MstDevice mstDevice,
                                             const MstTelemetryContext* context,
                                             MstTelemetryOperationalInfo* operationalInfo);

    /**
     * @brief Gets the FEC histogram of the device. Equivalent to Mlxlink's "--show_histogram
     * --rx_fec_histogram" command.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param fecHistogram The FEC histogram struct to fill.
     * @return The status of the operation.
     */
    MstStatus mstGetFecHistogram(MstDevice mstDevice, const MstTelemetryContext* context, MstFecHistogram* fecHistogram);

    /**
     * @brief Gets the counters info of the device. Equivalent to Mlxlink's "show counters" command.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param countersInfo The counters info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetCountersInfo(MstDevice mstDevice, const MstTelemetryContext* context, MstCountersInfo* countersInfo);

    /**
     * @brief Gets the Cable DDM info of the device. Equivalent to Mlxlink's "--cable --ddm" command.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param cableDDMInfo The Cable DDM info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetCableDDMInfo(MstDevice mstDevice, const MstTelemetryContext* context, MstCableDDMInfo* cableDDMInfo);

    /**
     * @brief Gets the Module info of the device. Equivalent to Mlxlink's "--show_module" command.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param moduleInfo The Module info struct to fill. should be initialized with MST_QUERY_INIT.
     * @return The status of the operation.
     */
    MstStatus mstGetModuleInfo(MstDevice mstDevice, const MstTelemetryContext* context, MstModuleInfo* moduleInfo);

    /**
     * @brief Gets the troubleshooting info of the device. Equivalent to Mlxlink's general query "Troubleshooting Info"
     * page.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param troubleShootingInfo The troubleshooting info struct to fill. Should be initialized with MST_QUERY_INIT.
     * A field the device reports as not applicable is left untouched and its bit stays clear in the header mask.
     * @return The status of the operation. MST_ERROR_INVALID_ARGUMENT if mstDevice or troubleShootingInfo is NULL, or
     * if either struct carries an invalid size; MST_ERROR_FAILED_TO_GET_TELEMETRY if the device could not be queried -
     * call mstGetLastErrorString for the reason.
     */
    MstStatus mstGetTroubleShootingInfo(MstDevice mstDevice,
                                        const MstTelemetryContext* context,
                                        MstTroubleShootingInfo* troubleShootingInfo);

    /**
     * @brief Gets one or more telemetry views aggregated into a single JSON string. Runs only the commands needed
     * for the requested views and merges their sections into one JSON document. The returned string is heap-allocated
     * and must be released with mstFreeJsonString().
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with MST_TELEMETRY_CONTEXT_INIT.
     * @param views Bitwise OR of MstTelemetryView values selecting which sections to include.
     * @param jsonOut Receives the NUL-terminated JSON string owned by the library.
     * @return The status of the operation.
     */
    MstStatus
      mstGetTelemetryJson(MstDevice mstDevice, const MstTelemetryContext* context, uint32_t views, char** jsonOut);

    /**
     * @brief Gets one or more telemetry views as the report mlxlink itself would print, captured
     * rather than written to the screen. The returned string is heap-allocated and must be
     * released with mstFreeJsonString().
     *
     * Only the views whose report mlxlink prints through a "show" command can be returned:
     * MST_TELEMETRY_VIEW_COUNTERS, _EYE, _FEC, _SERDES_TX, _BER_MONITOR, _EXTERNAL_PHY, _PLR, _KR,
     * _RX_RECOVERY, and _OPERATIONAL for a PCIe port. MST_TELEMETRY_VIEW_GENERAL, _MODULE,
     * _CABLE_DDM, _FEC_HISTOGRAM and operating info on a network port are assembled from cached
     * sections instead of printed, so they return MST_ERROR_NOT_SUPPORTED rather than an empty
     * string. Use mstGetTelemetryJson() for those.
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL for the device defaults. Initialize with
     * MST_TELEMETRY_CONTEXT_INIT.
     * @param views Bitwise OR of MstTelemetryView values selecting which sections to include.
     * @param textOut Receives the NUL-terminated report owned by the library.
     * @return The status of the operation.
     */
    MstStatus
      mstGetTelemetryText(MstDevice mstDevice, const MstTelemetryContext* context, uint32_t views, char** textOut);

    /**
     * @brief Releases a string returned by any SDK call that hands back a heap-allocated string
     * (mstGetTelemetryJson(), mstGetTelemetryText(), mstGetAmberJson()).
     * @param json The string previously returned through the jsonOut / textOut parameter.
     * @return The status of the operation.
     */
    MstStatus mstFreeJsonString(char* json);

    /**
     * @brief Releases a string returned by mstGetTelemetryText(). Name-consistent alias of
     * mstFreeJsonString(), which it calls; either may be used with either getter.
     * @param json The string previously returned through the textOut parameter.
     * @return The status of the operation.
     */
    MstStatus mstFreeTextString(char* json);

#ifdef __cplusplus
}
#endif