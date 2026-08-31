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

// Test fixture for SDK telemetry tests
class MftSdkTelemetryTest : public ::testing::Test
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

TEST_F(MftSdkTelemetryTest, GetTelemetryOperationalInfo)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstTelemetryOperationalInfo operationalInfo;
    MST_QUERY_INIT(&operationalInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetTelemetryOperationalInfo(mstDevice, &context, &operationalInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get telemetry operational info";

    const FieldDescriptor* fields = getOpInfoFields();

    std::vector<std::pair<std::string, std::string>> results;
    results.reserve(NUM_OP_INFO_FIELDS);

    for (size_t i = 0; i < NUM_OP_INFO_FIELDS; i++)
    {
        const char* valueStr;
        uint32_t bit = fields[i].capabilityBit;

        if (MST_QUERY_HAS(&operationalInfo, bit))
        {
            valueStr = fieldValueToString(&operationalInfo, &fields[i]);
        }
        else
        {
            valueStr = NA_FIELD_VALUE;
        }
        results.emplace_back(fields[i].displayName, valueStr);
    }

    printf("\n%s\n", FIELD_OPERATIONAL_INFO);
    printf("----------------\n");
    for (const auto& result : results)
    {
        printf("%-35s: %s\n", result.first.c_str(), result.second.c_str());
    }

    EXPECT_EQ(operationalInfo.header.valid_fields_mask,
              (1ULL << TELEMETRY_OP_INFO_STATE) | (1ULL << TELEMETRY_OP_INFO_PHYSICAL_STATE) |
                (1ULL << TELEMETRY_OP_INFO_SPEED) | (1ULL << TELEMETRY_OP_INFO_WIDTH) |
                (1ULL << TELEMETRY_OP_INFO_FEC) | (1ULL << TELEMETRY_OP_INFO_LOOPBACK_MODE) |
                (1ULL << TELEMETRY_OP_INFO_AUTO_NEGOTIATION));
}

TEST_F(MftSdkTelemetryTest, DefaultPortAfterSpecificPortDoesNotThrow)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstTelemetryOperationalInfo operationalInfo;

    // 1) Bind a concrete port (label port 1 exists on all supported devices).
    MstTelemetryContext specificPort;
    MST_TELEMETRY_CONTEXT_INIT(&specificPort);
    snprintf(specificPort.label_port, sizeof(specificPort.label_port), "1");
    MST_QUERY_INIT(&operationalInfo);
    status = mstGetTelemetryOperationalInfo(mstDevice, &specificPort, &operationalInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to bind port 1: " << mstGetLastErrorString(mstDevice);

    // 2) Switch back to the device default; must not throw "Invalid port number!".
    MST_QUERY_INIT(&operationalInfo);
    status = mstGetTelemetryOperationalInfo(mstDevice, nullptr, &operationalInfo);
    EXPECT_EQ(status, MST_SUCCESS) << "Default port after a specific port failed: " << mstGetLastErrorString(mstDevice);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
