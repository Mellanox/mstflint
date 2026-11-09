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

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

// Test fixture for SDK troubleshooting info tests
class MftSdkTroubleShootingTest : public ::testing::Test
{
protected:
    MstDevice mstDevice;

    void SetUp() override { mstDevice = nullptr; }

    void TearDown() override
    {
        if (mstDevice != nullptr)
        {
            mstReleaseDeviceHandle(mstDevice);
        }
    }
};

TEST_F(MftSdkTroubleShootingTest, GetTroubleShootingInfo)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstTroubleShootingInfo troubleShootingInfo;
    MST_QUERY_INIT(&troubleShootingInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetTroubleShootingInfo(mstDevice, &context, &troubleShootingInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get troubleshooting info: " << mstGetLastErrorString(mstDevice);

    const FieldDescriptor* fields = getTroubInfoFields();

    std::vector<std::pair<std::string, std::string>> results;
    results.reserve(NUM_TROUB_INFO_FIELDS);

    for (size_t i = 0; i < NUM_TROUB_INFO_FIELDS; i++)
    {
        const char* valueStr;
        uint32_t bit = fields[i].capabilityBit;

        if (MST_QUERY_HAS(&troubleShootingInfo, bit))
        {
            valueStr = fieldValueToString(&troubleShootingInfo, &fields[i]);
        }
        else
        {
            valueStr = NA_FIELD_VALUE;
        }
        results.emplace_back(fields[i].displayName, valueStr);
    }

    printf("\n%s\n", FIELD_TROUBLESHOOTING_INFO);
    printf("----------------\n");
    for (const auto& result : results)
    {
        printf("%-35s: %s\n", result.first.c_str(), result.second.c_str());
    }

    // The device always reports a status opcode; the group opcode and the recommendation
    // are only reported for an opcode that has them, so their bits stay optional.
    EXPECT_TRUE(MST_QUERY_HAS(&troubleShootingInfo, TELEMETRY_TROUBLESHOOTING_INFO_STATUS_OPCODE));
}

TEST_F(MftSdkTroubleShootingTest, GroupOpcodeMatchesStatusOpcodeRange)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstTroubleShootingInfo troubleShootingInfo;
    MST_QUERY_INIT(&troubleShootingInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetTroubleShootingInfo(mstDevice, &context, &troubleShootingInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get troubleshooting info: " << mstGetLastErrorString(mstDevice);

    if (!MST_QUERY_HAS(&troubleShootingInfo, TELEMETRY_TROUBLESHOOTING_INFO_GROUP_OPCODE))
    {
        // gtest 1.8.1 has no GTEST_SKIP(); the suites in this tree soft-skip by printing.
        printf("[  SKIPPED ] Device reported no group opcode for status opcode %u\n", troubleShootingInfo.statusOpcode);
        return;
    }

    // The group is derived from the status opcode range, so the two must agree.
    TroubleShootingInfoGroupOpcode expected = TROUBLESHOOTING_INFO_GROUP_OPCODE_CORE_DRIVER;
    if (troubleShootingInfo.statusOpcode < 1023)
    {
        expected = TROUBLESHOOTING_INFO_GROUP_OPCODE_PHY_FW;
    }
    else if (troubleShootingInfo.statusOpcode < 2048)
    {
        expected = TROUBLESHOOTING_INFO_GROUP_OPCODE_MNG_FW;
    }
    EXPECT_EQ(troubleShootingInfo.groupOpcode, expected);
}

TEST_F(MftSdkTroubleShootingTest, RejectsInvalidArguments)
{
    MstTroubleShootingInfo troubleShootingInfo;
    MST_QUERY_INIT(&troubleShootingInfo);
    EXPECT_EQ(mstGetTroubleShootingInfo(nullptr, nullptr, &troubleShootingInfo), MST_ERROR_INVALID_ARGUMENT);

    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    EXPECT_EQ(mstGetTroubleShootingInfo(mstDevice, nullptr, nullptr), MST_ERROR_INVALID_ARGUMENT);

    // A context that was not initialized with MST_TELEMETRY_CONTEXT_INIT carries no size.
    MstTelemetryContext uninitializedContext;
    memset(&uninitializedContext, 0, sizeof(uninitializedContext));
    EXPECT_EQ(mstGetTroubleShootingInfo(mstDevice, &uninitializedContext, &troubleShootingInfo),
              MST_ERROR_INVALID_ARGUMENT);

    // A response struct without its size header is rejected before the device is touched.
    MstTroubleShootingInfo unsizedInfo;
    memset(&unsizedInfo, 0, sizeof(unsizedInfo));
    EXPECT_EQ(mstGetTroubleShootingInfo(mstDevice, nullptr, &unsizedInfo), MST_ERROR_INVALID_ARGUMENT);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
