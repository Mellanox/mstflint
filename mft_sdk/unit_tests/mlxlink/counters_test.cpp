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
#include <string>
#include <vector>

class MftSdkCountersTest : public ::testing::Test
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

TEST_F(MftSdkCountersTest, GetCountersInfo)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstCountersInfo countersInfo;
    MST_QUERY_INIT(&countersInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetCountersInfo(mstDevice, &context, &countersInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get counters info: " << mstGetLastErrorString(mstDevice);

    const FieldDescriptor* fields = getCounterFields();

    std::vector<std::pair<std::string, std::string>> results;
    results.reserve(NUM_COUNTER_FIELDS);

    for (size_t i = 0; i < NUM_COUNTER_FIELDS; i++)
    {
        const char* valueStr;
        if (MST_QUERY_HAS(&countersInfo.header, fields[i].capabilityBit))
        {
            valueStr = fieldValueToString(&countersInfo, &fields[i]);
        }
        else
        {
            valueStr = NA_FIELD_VALUE;
        }
        results.emplace_back(fields[i].displayName, valueStr);
    }

    printf("\nvalid fields mask: 0x%llx\n", (unsigned long long)countersInfo.header.valid_fields_mask);
    printf("extended valid fields mask: 0x%llx\n", (unsigned long long)countersInfo.header.extended_valid_fields_mask);
    printf("%s\n", FIELD_PHYSICAL_COUNTERS_AND_BER_INFO);
    printf("------------------------------\n");
    for (const auto& result : results)
    {
        printf("%-35s: %s\n", result.first.c_str(), result.second.c_str());
    }

    EXPECT_NE(countersInfo.header.valid_fields_mask, 0u) << "Valid fields mask should be non-zero";

    if (countersInfo.numberOfLanes > 0)
    {
        if (MST_QUERY_HAS(&countersInfo, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_ERRORS_PER_LANE))
        {
            EXPECT_NE(countersInfo.rawPhysicalErrorsPerLane, nullptr);
        }
        if (MST_QUERY_HAS(&countersInfo, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER_PER_LANE))
        {
            EXPECT_NE(countersInfo.rawPhysicalBERPerLane, nullptr);
        }
    }
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
