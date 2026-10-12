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

#ifndef MFT_SDK_AMBER_COLLECT_TEST_COMMON_H
#define MFT_SDK_AMBER_COLLECT_TEST_COMMON_H

#include "mft_sdk/mft_sdk.h"

#include <stdio.h>
#include <string.h>

/*
 * test_amber_collect.py (AmberRecordParser) consumes these records. Strings in
 * report records are hex encoded so field names and values cannot break the
 * line-oriented format -- amBER values legitimately contain commas, quotes and
 * embedded NULs. The JSON body remains verbatim between explicit begin/end
 * markers. AMBER_JSON_FREE_STATUS carries NONE when no buffer was returned.
 */
static void amberTestPrintHex(const char* record, const char* value, size_t maxLength)
{
    size_t index;

    if (record != NULL && record[0] != '\0')
    {
        printf("%s ", record);
    }
    if (value != NULL)
    {
        for (index = 0; index < maxLength && value[index] != '\0'; ++index)
        {
            printf("%02x", (unsigned int)(unsigned char)value[index]);
        }
    }
    printf("\n");
}

static MstStatus amberTestCollectJson(MstDevice device, const MstAmberContext* context, int* outputValid)
{
    char* json = NULL;
    MstStatus status = mstGetAmberJson(device, context, &json);
    const char* error = mstGetLastErrorString(device);

    printf("AMBER_JSON_STATUS %d\n", (int)status);
    amberTestPrintHex("AMBER_JSON_ERROR_HEX", error, 4096);
    printf("AMBER_JSON_POINTER_NULL_AFTER_CALL %u\n", json == NULL ? 1u : 0u);

    if (status == MST_SUCCESS && json != NULL)
    {
        printf("AMBER_JSON_BEGIN\n%s", json);
        if (json[0] != '\0' && json[strlen(json) - 1] != '\n')
        {
            printf("\n");
        }
        printf("AMBER_JSON_END\n");
        *outputValid = 1;
        printf("AMBER_JSON_FREE_STATUS %d\n", (int)mstFreeJsonString(json));
    }
    else
    {
        *outputValid = 0;
        /* No buffer was returned, so nothing was freed: a status here would be invented. */
        printf("AMBER_JSON_FREE_STATUS NONE\n");
    }

    return status;
}

static MstStatus amberTestCollectReport(MstDevice device, const MstAmberContext* context, int* outputValid)
{
    unsigned int portIndex;
    MstAmberReport report;
    MstStatus status;
    const char* error;

    memset(&report, 0, sizeof(report));
    status = mstGetAmberReport(device, context, &report);
    error = mstGetLastErrorString(device);

    printf("AMBER_REPORT_STATUS %d\n", (int)status);
    amberTestPrintHex("AMBER_REPORT_ERROR_HEX", error, 4096);

    if (status == MST_SUCCESS)
    {
        amberTestPrintHex("AMBER_REPORT_VERSION_HEX", report.amber_version, MST_AMBER_VERSION_MAX);
        printf("AMBER_REPORT_PORT_COUNT %u\n", report.port_count);

        for (portIndex = 0; portIndex < report.port_count; ++portIndex)
        {
            unsigned int fieldIndex;
            const MstAmberPort* port = &report.ports[portIndex];

            printf("AMBER_REPORT_PORT ");
            amberTestPrintHex("", port->label_port, MST_AMBER_PORT_MAX_LENGTH);
            printf("AMBER_REPORT_FIELD_COUNT %u\n", port->field_count);

            for (fieldIndex = 0; fieldIndex < port->field_count; ++fieldIndex)
            {
                const MstAmberField* field = &port->fields[fieldIndex];
                printf("AMBER_REPORT_FIELD %u ", field->sheet_id);
                amberTestPrintHex("", field->field_name, MST_AMBER_FIELD_NAME_MAX);
                amberTestPrintHex("AMBER_REPORT_VALUE_HEX", field->value, MST_AMBER_VALUE_MAX);
            }
            printf("AMBER_REPORT_PORT_END\n");
        }

        *outputValid = report.port_count > 0 && report.ports != NULL;
    }
    else
    {
        *outputValid = 0;
    }

    mstFreeAmberReport(&report);
    printf("AMBER_REPORT_AFTER_FREE %u %u\n", report.port_count, report.ports == NULL ? 1u : 0u);
    mstFreeAmberReport(&report);
    printf("AMBER_REPORT_DOUBLE_FREE_OK\n");

    return status;
}

/* amberTestRun() return codes. UNSUPPORTED is distinct from failure: the SDK says
 * this verbatim on pre-16nm parts and mlxlink_ext refuses the same devices
 * ("amber_collect is not available for this device"), so the two agree and there is
 * nothing to test -- ConnectX-4 and ConnectX-5 are in that set. */
#define AMBER_TEST_OK 0
#define AMBER_TEST_FAILED 1
#define AMBER_TEST_UNSUPPORTED 2
#define AMBER_UNSUPPORTED_MARKER "supported on 16nm devices and above"

static int amberTestUnsupported(const char* error)
{
    return error != NULL && strstr(error, AMBER_UNSUPPORTED_MARKER) != NULL;
}

/* AMBER_TEST_OK only when both entry points succeeded: a collect failure on a device
 * that DOES support amBER must fail the test. */
static int amberTestRun(const char* deviceName, const char* portName, int reportFirst)
{
    int jsonValid = 0;
    int reportValid = 0;
    MstStatus jsonStatus;
    MstStatus reportStatus;
    MstStatus openStatus;
    MstDevice device = NULL;
    MstAmberContext context;

    openStatus = mstGetDeviceHandle(&device, deviceName);
    printf("AMBER_OPEN_STATUS %d\n", (int)openStatus);
    if (openStatus != MST_SUCCESS)
    {
        return AMBER_TEST_FAILED;
    }

    MST_AMBER_CONTEXT_INIT(&context);
    if (portName != NULL && portName[0] != '\0')
    {
        snprintf(context.label_port, sizeof(context.label_port), "%s", portName);
    }
    amberTestPrintHex("AMBER_REQUEST_PORT_HEX", context.label_port, sizeof(context.label_port));
    printf("AMBER_CALL_ORDER %s\n", reportFirst ? "REPORT_JSON" : "JSON_REPORT");

    if (reportFirst)
    {
        reportStatus = amberTestCollectReport(device, &context, &reportValid);
        jsonStatus = amberTestCollectJson(device, &context, &jsonValid);
    }
    else
    {
        jsonStatus = amberTestCollectJson(device, &context, &jsonValid);
        reportStatus = amberTestCollectReport(device, &context, &reportValid);
    }

    if (jsonStatus != MST_SUCCESS || reportStatus != MST_SUCCESS)
    {
        /* Read the error BEFORE the handle goes away. */
        int unsupported = amberTestUnsupported(mstGetLastErrorString(device));
        printf("AMBER_UNSUPPORTED %u\n", unsupported ? 1u : 0u);
        mstReleaseDeviceHandle(device);
        return unsupported ? AMBER_TEST_UNSUPPORTED : AMBER_TEST_FAILED;
    }
    mstReleaseDeviceHandle(device);

    if (!jsonValid || !reportValid)
    {
        return AMBER_TEST_FAILED;
    }
    return AMBER_TEST_OK;
}

/* Open device, run one sheet-filtered collect (JSON + report), print results, return 0 on
 * success. Only reachable through the unified C dispatcher (amber_sheet_select_test_main in
 * amber_collect_test.c) -- there is no standalone binary for this scenario, so this must stay
 * out of a plain (non-unified) C build or it is an unused function there. The C++ gtest suite
 * drives mstGetAmberJson/Report directly instead. */
#if defined(MFT_SDK_C_UNIFIED) && !defined(__cplusplus)
static int amberSheetSelectTestRun(const char* deviceName, const char* portName, unsigned int sheetId)
{
    MstDevice device = NULL;
    MstAmberContext context;
    unsigned int sheets[1];
    char* json = NULL;
    MstAmberReport report;
    MstStatus openStatus;
    MstStatus jsonStatus;
    MstStatus reportStatus;
    unsigned int portIndex;
    unsigned int fieldIndex;

    openStatus = mstGetDeviceHandle(&device, deviceName);
    printf("SHEET_SELECT_OPEN_STATUS %d\n", (int)openStatus);
    if (openStatus != MST_SUCCESS)
    {
        return 1;
    }

    sheets[0] = sheetId;
    MST_AMBER_CONTEXT_INIT(&context);
    if (portName != NULL && portName[0] != '\0')
    {
        snprintf(context.label_port, sizeof(context.label_port), "%s", portName);
    }
    context.sheet_count = 1;
    context.sheet_ids = sheets;

    printf("SHEET_SELECT_REQUESTED_SHEET %u\n", sheetId);

    json = NULL;
    jsonStatus = mstGetAmberJson(device, &context, &json);
    printf("SHEET_SELECT_JSON_STATUS %d\n", (int)jsonStatus);
    if (jsonStatus == MST_SUCCESS && json != NULL)
    {
        printf("SHEET_SELECT_JSON_BEGIN\n%s", json);
        if (json[0] != '\0' && json[strlen(json) - 1] != '\n')
        {
            printf("\n");
        }
        printf("SHEET_SELECT_JSON_END\n");
        mstFreeJsonString(json);
    }
    else
    {
        printf("SHEET_SELECT_JSON_ERROR: %s\n", mstGetLastErrorString(device));
    }

    memset(&report, 0, sizeof(report));
    reportStatus = mstGetAmberReport(device, &context, &report);
    printf("SHEET_SELECT_REPORT_STATUS %d\n", (int)reportStatus);
    if (reportStatus == MST_SUCCESS)
    {
        printf("SHEET_SELECT_REPORT_VERSION %s\n", report.amber_version);
        printf("SHEET_SELECT_REPORT_PORT_COUNT %u\n", report.port_count);
        for (portIndex = 0; portIndex < report.port_count; ++portIndex)
        {
            const MstAmberPort* port = &report.ports[portIndex];
            printf("SHEET_SELECT_PORT %s FIELD_COUNT %u\n", port->label_port, port->field_count);
            for (fieldIndex = 0; fieldIndex < port->field_count; ++fieldIndex)
            {
                const MstAmberField* field = &port->fields[fieldIndex];
                /* All fields must belong to the requested sheet. */
                printf("SHEET_SELECT_FIELD sheet_id=%u %s=%s\n", field->sheet_id, field->field_name, field->value);
                if (field->sheet_id != sheetId)
                {
                    printf("SHEET_SELECT_UNEXPECTED_SHEET_ID: expected %u got %u for field %s\n", sheetId,
                           field->sheet_id, field->field_name);
                }
            }
        }
        mstFreeAmberReport(&report);
    }
    else
    {
        printf("SHEET_SELECT_REPORT_ERROR: %s\n", mstGetLastErrorString(device));
    }

    mstReleaseDeviceHandle(device);
    return (jsonStatus == MST_SUCCESS && reportStatus == MST_SUCCESS) ? 0 : 1;
}
#endif /* MFT_SDK_C_UNIFIED && !__cplusplus */

#endif /* MFT_SDK_AMBER_COLLECT_TEST_COMMON_H */
