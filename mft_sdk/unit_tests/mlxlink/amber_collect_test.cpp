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

    MST_AMBER_CONTEXT_INIT(&context);
    snprintf(context.label_port, sizeof(context.label_port), "%s", "cov_no_such_port");
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

    MST_AMBER_CONTEXT_INIT(&emptyContext);
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

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
