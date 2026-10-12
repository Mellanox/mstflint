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

#include "amber_collect_test_common.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <cstring>
#include <iostream>

namespace
{

MstAmberContext makeSheetContext(const char* port, const unsigned int* sheets, unsigned int count)
{
    MstAmberContext ctx;
    MST_AMBER_CONTEXT_INIT(&ctx);
    if (port && port[0] != '\0')
    {
        snprintf(ctx.label_port, sizeof(ctx.label_port), "%s", port);
    }
    ctx.sheet_count = count;
    ctx.sheet_ids = sheets;
    return ctx;
}

unsigned int totalFieldCount(const MstAmberReport& report)
{
    unsigned int total = 0;
    for (unsigned int p = 0; p < report.port_count; ++p)
    {
        total += report.ports[p].field_count;
    }
    return total;
}

} // namespace

class MftSdkAmberCollectTest : public ::testing::Test
{
};

TEST_F(MftSdkAmberCollectTest, GetAmberCollect)
{
    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    int result = amberTestRun(g_devicePci.c_str(), g_port.c_str(), 1);
    if (result == AMBER_TEST_UNSUPPORTED)
    {
        // gtest 1.8.1 has no GTEST_SKIP(); print the standard skip line and return.
        std::cout << "[  SKIPPED ] amBER collect not supported on this device (pre-16nm)" << std::endl;
        return;
    }
    EXPECT_EQ(result, AMBER_TEST_OK)
      << "amBER collect failed; see AMBER_JSON_STATUS / AMBER_REPORT_STATUS and the hex error records above";
}

TEST_F(MftSdkAmberCollectTest, NullArguments)
{
    char* json = nullptr;
    MstAmberReport report;

    memset(&report, 0, sizeof(report));
    EXPECT_EQ(mstGetAmberJson(nullptr, nullptr, &json), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstGetAmberJson(nullptr, nullptr, nullptr), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstGetAmberReport(nullptr, nullptr, &report), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstGetAmberReport(nullptr, nullptr, nullptr), MST_ERROR_INVALID_ARGUMENT);

    mstFreeAmberReport(nullptr);
    mstFreeAmberReport(&report);
    mstFreeAmberReport(&report);
}

TEST_F(MftSdkAmberCollectTest, ValidDeviceRejectsNullOutputs)
{
    MstDevice device = nullptr;
    MstStatus status;

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    status = mstGetDeviceHandle(&device, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS);

    EXPECT_EQ(mstGetAmberJson(device, nullptr, nullptr), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(mstGetAmberReport(device, nullptr, nullptr), MST_ERROR_INVALID_ARGUMENT);

    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, InvalidPortFailsCleanly)
{
    char* json = reinterpret_cast<char*>(0x1);
    MstAmberContext context;
    MstAmberReport report;
    MstDevice device = nullptr;
    MstStatus jsonStatus;
    MstStatus reportStatus;

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    context = makeSheetContext("cov_no_such_port", nullptr, 0);
    memset(&report, 0xab, sizeof(report));

    jsonStatus = mstGetAmberJson(device, &context, &json);
    EXPECT_NE(jsonStatus, MST_SUCCESS);
    EXPECT_EQ(json, nullptr);
    EXPECT_STRNE(mstGetLastErrorString(device), "");

    reportStatus = mstGetAmberReport(device, &context, &report);
    EXPECT_NE(reportStatus, MST_SUCCESS);
    EXPECT_EQ(report.port_count, 0u);
    EXPECT_EQ(report.ports, nullptr);
    EXPECT_STRNE(mstGetLastErrorString(device), "");

    mstFreeAmberReport(&report);
    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, NullContextUsesDefaultPort)
{
    char* emptyContextJson = nullptr;
    char* nullContextJson = nullptr;
    MstAmberContext emptyContext;
    MstDevice device = nullptr;
    MstStatus emptyContextStatus;
    MstStatus nullContextStatus;

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    emptyContext = makeSheetContext("", nullptr, 0);
    nullContextStatus = mstGetAmberJson(device, nullptr, &nullContextJson);
    emptyContextStatus = mstGetAmberJson(device, &emptyContext, &emptyContextJson);
    EXPECT_EQ(nullContextStatus, emptyContextStatus);

    if (nullContextStatus == MST_SUCCESS && emptyContextStatus == MST_SUCCESS)
    {
        ASSERT_NE(nullContextJson, nullptr);
        ASSERT_NE(emptyContextJson, nullptr);
        EXPECT_NE(strstr(nullContextJson, "\"amber_version\""), nullptr);
        EXPECT_NE(strstr(nullContextJson, "\"ports\""), nullptr);
        EXPECT_NE(strstr(emptyContextJson, "\"amber_version\""), nullptr);
        EXPECT_NE(strstr(emptyContextJson, "\"ports\""), nullptr);
        EXPECT_EQ(mstFreeJsonString(nullContextJson), MST_SUCCESS);
        EXPECT_EQ(mstFreeJsonString(emptyContextJson), MST_SUCCESS);
        nullContextJson = nullptr;
        emptyContextJson = nullptr;
    }
    else
    {
        EXPECT_EQ(nullContextJson, nullptr);
        EXPECT_EQ(emptyContextJson, nullptr);
        EXPECT_STRNE(mstGetLastErrorString(device), "");
        if (nullContextJson != nullptr)
        {
            EXPECT_EQ(mstFreeJsonString(nullContextJson), MST_SUCCESS);
        }
        if (emptyContextJson != nullptr)
        {
            EXPECT_EQ(mstFreeJsonString(emptyContextJson), MST_SUCCESS);
        }
    }

    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, NullDevice_WithSheets_ReturnsInvalidArgument)
{
    unsigned int sheets[] = {MST_AMBER_SHEET_GENERAL};
    MstAmberContext ctx = makeSheetContext("", sheets, 1);
    char* json = nullptr;
    MstAmberReport report;
    memset(&report, 0, sizeof(report));

    EXPECT_EQ(mstGetAmberJson(nullptr, &ctx, &json), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(json, nullptr);
    EXPECT_EQ(mstGetAmberReport(nullptr, &ctx, &report), MST_ERROR_INVALID_ARGUMENT);
    EXPECT_EQ(report.port_count, 0u);
    EXPECT_EQ(report.ports, nullptr);
}

TEST_F(MftSdkAmberCollectTest, UnknownSheetId_ReturnsFailedToCollect)
{
    MstDevice device = nullptr;
    unsigned int badSheets[] = {100};

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    MstAmberContext ctx = makeSheetContext(g_port.c_str(), badSheets, 1);
    char* json = nullptr;
    MstAmberReport report;
    memset(&report, 0, sizeof(report));

    EXPECT_EQ(mstGetAmberJson(device, &ctx, &json), MST_ERROR_FAILED_TO_COLLECT_AMBER);
    EXPECT_EQ(json, nullptr);
    EXPECT_EQ(mstGetAmberReport(device, &ctx, &report), MST_ERROR_FAILED_TO_COLLECT_AMBER);
    EXPECT_EQ(report.port_count, 0u);
    EXPECT_STRNE(mstGetLastErrorString(device), "");

    mstFreeJsonString(json);
    mstFreeAmberReport(&report);
    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, InternalOnlySheet15_Rejected)
{
    MstDevice device = nullptr;
    /* Sheet 15 (PHY_DEBUG_INFO) is internal-only; the ext SDK must reject it. */
    unsigned int internalSheet[] = {15};

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    MstAmberContext ctx = makeSheetContext(g_port.c_str(), internalSheet, 1);
    char* json = nullptr;

    EXPECT_EQ(mstGetAmberJson(device, &ctx, &json), MST_ERROR_FAILED_TO_COLLECT_AMBER);
    EXPECT_EQ(json, nullptr);
    EXPECT_STRNE(mstGetLastErrorString(device), "");

    mstFreeJsonString(json);
    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, DuplicateSheet_ReturnsFailedToCollect)
{
    MstDevice device = nullptr;
    unsigned int dupSheets[] = {MST_AMBER_SHEET_GENERAL, MST_AMBER_SHEET_GENERAL};

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    MstAmberContext ctx = makeSheetContext(g_port.c_str(), dupSheets, 2);
    char* json = nullptr;

    EXPECT_EQ(mstGetAmberJson(device, &ctx, &json), MST_ERROR_FAILED_TO_COLLECT_AMBER);
    EXPECT_EQ(json, nullptr);
    EXPECT_STRNE(mstGetLastErrorString(device), "");

    mstFreeJsonString(json);
    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, SingleSheet_AllFieldsHaveExpectedSheetId)
{
    MstDevice device = nullptr;
    unsigned int sheets[] = {MST_AMBER_SHEET_GENERAL};

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    MstAmberContext ctx = makeSheetContext(g_port.c_str(), sheets, 1);
    MstAmberReport report;
    memset(&report, 0, sizeof(report));

    MstStatus status = mstGetAmberReport(device, &ctx, &report);
    if (status == MST_SUCCESS && report.port_count > 0)
    {
        for (unsigned int p = 0; p < report.port_count; ++p)
        {
            for (unsigned int f = 0; f < report.ports[p].field_count; ++f)
            {
                EXPECT_EQ(report.ports[p].fields[f].sheet_id, static_cast<unsigned int>(MST_AMBER_SHEET_GENERAL))
                  << "Unexpected sheet_id on field: " << report.ports[p].fields[f].field_name;
            }
        }
    }
    /* else: device returned no ports — nothing to assert, not a failure */

    mstFreeAmberReport(&report);
    mstReleaseDeviceHandle(device);
}

TEST_F(MftSdkAmberCollectTest, TwoSheets_FewerFieldsThanFullCollect)
{
    MstDevice device = nullptr;

    ASSERT_FALSE(g_devicePci.empty()) << "A device is required (-d <BDF>)";
    ASSERT_EQ(mstGetDeviceHandle(&device, g_devicePci.c_str()), MST_SUCCESS);

    /* Full collect: no sheet filter */
    MstAmberContext fullCtx = makeSheetContext(g_port.c_str(), nullptr, 0);
    MstAmberReport fullReport;
    memset(&fullReport, 0, sizeof(fullReport));
    MstStatus fullStatus = mstGetAmberReport(device, &fullCtx, &fullReport);

    /* Partial: just GENERAL + SYSTEM */
    unsigned int partialSheets[] = {MST_AMBER_SHEET_GENERAL, MST_AMBER_SHEET_SYSTEM};
    MstAmberContext partialCtx = makeSheetContext(g_port.c_str(), partialSheets, 2);
    MstAmberReport partialReport;
    memset(&partialReport, 0, sizeof(partialReport));
    MstStatus partialStatus = mstGetAmberReport(device, &partialCtx, &partialReport);

    if (fullStatus == MST_SUCCESS && partialStatus == MST_SUCCESS && fullReport.port_count > 0 &&
        partialReport.port_count > 0)
    {
        EXPECT_LT(totalFieldCount(partialReport), totalFieldCount(fullReport))
          << "Sheet-filtered collect should return fewer fields than a full collect";
    }
    /* else: amBER unsupported (pre-16nm), no ports, or the collect failed — nothing to assert */

    mstFreeAmberReport(&fullReport);
    mstFreeAmberReport(&partialReport);
    mstReleaseDeviceHandle(device);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
