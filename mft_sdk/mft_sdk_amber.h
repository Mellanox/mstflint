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

#ifndef MFT_SDK_AMBER_H
#define MFT_SDK_AMBER_H

#include <string.h>
#include <mft_sdk/mft_sdk_types.h>
#include <mft_sdk/mft_sdk_errors.h>
#include <mft_sdk/mft_sdk_telemetry.h> /* mstFreeJsonString() */

#ifdef __cplusplus
extern "C"
{
#endif

#define MST_AMBER_PORT_MAX_LENGTH 32

    /**
     * @brief amBER sheets, the groups a collected report is partitioned into.
     *
     * These are also the indexes mlxlink's --amber_index accepts. Sheets carrying internal-only
     * data are not listed and are rejected if requested. Which of these a device actually fills
     * depends on its technology.
     */
    typedef enum MstAmberSheet_t
    {
        MST_AMBER_SHEET_GENERAL = 1,
        MST_AMBER_SHEET_INDEXES = 2,
        MST_AMBER_SHEET_LINK_STATUS = 3,
        MST_AMBER_SHEET_MODULE_STATUS = 4,
        MST_AMBER_SHEET_SYSTEM = 5,
        MST_AMBER_SHEET_HDR_SERDES = 6,
        MST_AMBER_SHEET_NDR_SERDES = 7,
        MST_AMBER_SHEET_PORT_COUNTERS = 8,
        MST_AMBER_SHEET_TROUBLESHOOTING = 9,
        MST_AMBER_SHEET_PHY_OP = 10,
        MST_AMBER_SHEET_LINK_UP = 11,
        MST_AMBER_SHEET_LINK_DOWN = 12,
        MST_AMBER_SHEET_TEST_MODE = 13,
        MST_AMBER_SHEET_MODULE_TEST_MODE = 14,
        MST_AMBER_SHEET_EXT_MODULE_STATUS = 16,
        MST_AMBER_SHEET_SERDES_5NM_GEN7 = 17,
        MST_AMBER_SHEET_RECOVERY_COUNTERS = 20,
        MST_AMBER_SHEET_SERDES_5NM_GEN8 = 21
    } MstAmberSheet;

    /**
     * @brief amBER collect context, passed by pointer to the SDK.
     *
     * @ref size MUST be the first member and MUST equal sizeof(MstAmberContext); it lets the SDK
     * detect the ABI version the caller compiled against when the struct is extended. Initialize with
     * MST_AMBER_CONTEXT_INIT(). An empty @ref label_port collects every port of a switch device (a
     * single port on an HCA); pass NULL for the same behavior.
     *
     * @ref sheet_ids narrows the collection itself, so it is what makes a collect cheaper rather
     * than just trimming the output. The array is borrowed for the duration of the call and is
     * never freed by the SDK.
     */
    typedef struct MstAmberContext_t
    {
        unsigned int size;                          /**< Must be first; set to sizeof(MstAmberContext). */
        char label_port[MST_AMBER_PORT_MAX_LENGTH]; /**< Port label; empty => all ports. */
        unsigned int sheet_count;                   /**< Number of entries in @ref sheet_ids. */
        const unsigned int* sheet_ids;              /**< MstAmberSheet values; NULL => every sheet. */
    } MstAmberContext;

#define MST_AMBER_CONTEXT_INIT(a)     \
    do                                \
    {                                 \
        memset((a), 0, sizeof(*(a))); \
        (a)->size = sizeof(*(a));     \
    } while (0)

    /**
     * @brief Collect an amBER report as a JSON string.
     *
     * The JSON carries an amber_version envelope and a "ports" object keyed by port, each holding
     * that port's collected fields. The fields are not grouped by sheet, so a selection of several
     * sheets yields one flat object per port; use mstGetAmberReport() when a field's sheet matters.
     *
     * @param mstDevice The MstDevice handle.
     * @param context Context options, or NULL to collect every sheet of all ports.
     * @param jsonOut Receives a heap-allocated NUL-terminated JSON string; release with mstFreeJsonString().
     * @return The status of the operation.
     */
    MstStatus mstGetAmberJson(MstDevice mstDevice, const MstAmberContext* context, char** jsonOut);

#define MST_AMBER_FIELD_NAME_MAX 64 /**< Max length of a field name in MstAmberField (incl. NUL). */
#define MST_AMBER_VALUE_MAX 64      /**< Max length of a field value in MstAmberField (incl. NUL). */
#define MST_AMBER_VERSION_MAX 16    /**< Max length of the amBER version in MstAmberReport (incl. NUL). */

    /**
     * @brief One collected amBER field, as returned in MstAmberPort.
     *
     * field_name and value are NUL-terminated and truncated to their buffer sizes when the source
     * string is longer. Prefer mstGetAmberJson when truncation must be avoided.
     */
    typedef struct
    {
        unsigned int sheet_id; /**< amBER sheet this field was collected from. */
        char field_name[MST_AMBER_FIELD_NAME_MAX];
        char value[MST_AMBER_VALUE_MAX];
    } MstAmberField;

    /**
     * @brief The fields collected for a single port.
     */
    typedef struct
    {
        char label_port[MST_AMBER_PORT_MAX_LENGTH]; /**< Label port, or "depth/index/node" on the PCIe path. */
        unsigned int field_count;
        MstAmberField* fields; /**< Array of field_count entries; freed by mstFreeAmberReport(). */
    } MstAmberPort;

    /**
     * @brief A collected amBER report, grouped per port.
     *
     * ports is heap-allocated by the SDK; release the whole struct with mstFreeAmberReport().
     * Use mstGetAmberJson() to avoid the truncation documented on MstAmberField.
     */
    typedef struct
    {
        char amber_version[MST_AMBER_VERSION_MAX];
        unsigned int port_count;
        MstAmberPort* ports; /**< Heap-allocated array of port_count entries. */
    } MstAmberReport;

    /**
     * @brief Collect an amBER report, grouped per port.
     *
     * @param mstDevice The MstDevice handle.
     * @param context   Context options, or NULL to collect every sheet of all ports.
     * @param report    Output struct; call mstFreeAmberReport() to release it.
     * @return The status of the operation.
     */
    MstStatus mstGetAmberReport(MstDevice mstDevice, const MstAmberContext* context, MstAmberReport* report);

    /** @brief Release the ports and fields allocated by mstGetAmberReport(). */
    void mstFreeAmberReport(MstAmberReport* report);

#ifdef __cplusplus
}
#endif

#endif /* MFT_SDK_AMBER_H */
