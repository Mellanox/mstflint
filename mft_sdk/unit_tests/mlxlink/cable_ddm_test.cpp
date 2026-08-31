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

class MftSdkCableDDMTest : public ::testing::Test
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

static void printThreshold(const char* label, MstCableDDMThresholds thresholds)
{
    printf("%s:\n", label);
    if (label == DDM_FIELD_TEMPERATURE)
    {
        printf("  %-33s: %dC\n", DDM_FIELD_HIGH_ALARM_THRESHOLD, (int)thresholds.highAlarm);
        printf("  %-33s: %dC\n", DDM_FIELD_LOW_ALARM_THRESHOLD, (int)thresholds.lowAlarm);
        printf("  %-33s: %dC\n", DDM_FIELD_HIGH_WARNING_THRESHOLD, (int)thresholds.highWarning);
        printf("  %-33s: %dC\n", DDM_FIELD_LOW_WARNING_THRESHOLD, (int)thresholds.lowWarning);
    }
    else if (label == DDM_FIELD_VOLTAGE)
    {
        printf("  %-33s: %fV\n", DDM_FIELD_HIGH_ALARM_THRESHOLD, thresholds.highAlarm);
        printf("  %-33s: %fV\n", DDM_FIELD_LOW_ALARM_THRESHOLD, thresholds.lowAlarm);
        printf("  %-33s: %fV\n", DDM_FIELD_HIGH_WARNING_THRESHOLD, thresholds.highWarning);
        printf("  %-33s: %fV\n", DDM_FIELD_LOW_WARNING_THRESHOLD, thresholds.lowWarning);
    }
    else if (label == DDM_FIELD_RX_POWER)
    {
        printf("  %-33s: %f dBm\n", DDM_FIELD_HIGH_ALARM_THRESHOLD, thresholds.highAlarm);
        printf("  %-33s: %f dBm\n", DDM_FIELD_LOW_ALARM_THRESHOLD, thresholds.lowAlarm);
        printf("  %-33s: %f dBm\n", DDM_FIELD_HIGH_WARNING_THRESHOLD, thresholds.highWarning);
        printf("  %-33s: %f dBm\n", DDM_FIELD_LOW_WARNING_THRESHOLD, thresholds.lowWarning);
    }
    else if (label == DDM_FIELD_TX_POWER)
    {
        printf("  %-33s: %f dBm\n", DDM_FIELD_HIGH_ALARM_THRESHOLD, thresholds.highAlarm);
        printf("  %-33s: %f dBm\n", DDM_FIELD_LOW_ALARM_THRESHOLD, thresholds.lowAlarm);
        printf("  %-33s: %f dBm\n", DDM_FIELD_HIGH_WARNING_THRESHOLD, thresholds.highWarning);
        printf("  %-33s: %f dBm\n", DDM_FIELD_LOW_WARNING_THRESHOLD, thresholds.lowWarning);
    }
    else if (label == DDM_FIELD_TX_BIAS)
    {
        printf("  %-33s: %f mA\n", DDM_FIELD_HIGH_ALARM_THRESHOLD, thresholds.highAlarm);
        printf("  %-33s: %f mA\n", DDM_FIELD_LOW_ALARM_THRESHOLD, thresholds.lowAlarm);
        printf("  %-33s: %f mA\n", DDM_FIELD_HIGH_WARNING_THRESHOLD, thresholds.highWarning);
        printf("  %-33s: %f mA\n", DDM_FIELD_LOW_WARNING_THRESHOLD, thresholds.lowWarning);
    }
}

TEST_F(MftSdkCableDDMTest, GetCableDDMInfo)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstCableDDMInfo cableDDMInfo;
    MST_QUERY_INIT(&cableDDMInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetCableDDMInfo(mstDevice, &context, &cableDDMInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get cable DDM info: " << mstGetLastErrorString(mstDevice);

    const FieldDescriptor* fields = getDDMFields();

    std::vector<std::pair<std::string, std::string>> results;
    results.reserve(NUM_DDM_FIELDS);

    for (size_t i = 0; i < NUM_DDM_FIELDS; i++)
    {
        const char* valueStr;
        if (MST_QUERY_HAS(&cableDDMInfo.header, fields[i].capabilityBit))
        {
            valueStr = fieldValueToString(&cableDDMInfo, &fields[i]);
        }
        else
        {
            valueStr = NA_FIELD_VALUE;
        }
        results.emplace_back(fields[i].displayName, valueStr);
    }

    printf("\nValid fields mask: 0x%llx\n", (unsigned long long)cableDDMInfo.header.valid_fields_mask);
    printf("Extended valid fields mask: 0x%llx\n", (unsigned long long)cableDDMInfo.header.extended_valid_fields_mask);
    printf("Cable DDM\n");
    printf("---------\n");
    for (const auto& result : results)
    {
        printf("%-35s: %s\n", result.first.c_str(), result.second.c_str());
    }

    if (MST_QUERY_HAS(&cableDDMInfo, TELEMETRY_CABLE_DDM_INFO_CHANNELS))
    {
        printf("%-35s: %u\n", DDM_FIELD_CHANNELS, cableDDMInfo.numberOfChannels);
        if (cableDDMInfo.numberOfChannels > 0)
        {
            for (unsigned int i = 0; i < cableDDMInfo.numberOfChannels; i++)
            {
                printf("Channel %u:\n", i + 1);
                printf("  %-33s: %.3fdBm\n", DDM_FIELD_RX_POWER, cableDDMInfo.rxPower.value[i]);
                printf("  %-33s: %.3fdBm\n", DDM_FIELD_TX_POWER, cableDDMInfo.txPower.value[i]);
                printf("  %-33s: %.3fmA\n", DDM_FIELD_TX_BIAS, cableDDMInfo.txBias.value[i]);
            }
        }
    }
    else
    {
        printf("%-35s: %s\n", DDM_FIELD_CHANNELS, NA_FIELD_VALUE);
    }

    if (MST_QUERY_HAS(&cableDDMInfo, TELEMETRY_CABLE_DDM_INFO_FLAGS))
    {
        printf("%s:\n", DDM_SECTION_DDM_FLAGS);
        printf("  %-33s: %u\n", DDM_FIELD_TEMPERATURE_ALARM_HIGH, cableDDMInfo.temperature.alarmFlags.highAlarm);
        printf("  %-33s: %u\n", DDM_FIELD_TEMPERATURE_ALARM_LOW, cableDDMInfo.temperature.alarmFlags.lowAlarm);
        printf("  %-33s: %u\n", DDM_FIELD_TEMPERATURE_WARNING_HIGH, cableDDMInfo.temperature.alarmFlags.highWarning);
        printf("  %-33s: %u\n", DDM_FIELD_TEMPERATURE_WARNING_LOW, cableDDMInfo.temperature.alarmFlags.lowWarning);
        printf("  %-33s: %u\n", DDM_FIELD_VOLTAGE_ALARM_HIGH, cableDDMInfo.voltage.alarmFlags.highAlarm);
        printf("  %-33s: %u\n", DDM_FIELD_VOLTAGE_ALARM_LOW, cableDDMInfo.voltage.alarmFlags.lowAlarm);
        printf("  %-33s: %u\n", DDM_FIELD_VOLTAGE_WARNING_HIGH, cableDDMInfo.voltage.alarmFlags.highWarning);
        printf("  %-33s: %u\n", DDM_FIELD_VOLTAGE_WARNING_LOW, cableDDMInfo.voltage.alarmFlags.lowWarning);

        if (cableDDMInfo.numberOfChannels > 0)
        {
            for (unsigned int i = 0; i < cableDDMInfo.numberOfChannels; i++)
            {
                printf("Channel %u Flags:\n", i + 1);
                printf("  %-33s: %u\n", DDM_FIELD_RX_POWER_ALARM_HIGH, cableDDMInfo.rxPower.alarmFlags[i].highAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_RX_POWER_ALARM_LOW, cableDDMInfo.rxPower.alarmFlags[i].lowAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_RX_POWER_WARNING_HIGH,
                       cableDDMInfo.rxPower.alarmFlags[i].highWarning);
                printf("  %-33s: %u\n", DDM_FIELD_RX_POWER_WARNING_LOW, cableDDMInfo.rxPower.alarmFlags[i].lowWarning);
                printf("  %-33s: %u\n", DDM_FIELD_TX_POWER_ALARM_HIGH, cableDDMInfo.txPower.alarmFlags[i].highAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_TX_POWER_ALARM_LOW, cableDDMInfo.txPower.alarmFlags[i].lowAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_TX_POWER_WARNING_HIGH,
                       cableDDMInfo.txPower.alarmFlags[i].highWarning);
                printf("  %-33s: %u\n", DDM_FIELD_TX_POWER_WARNING_LOW, cableDDMInfo.txPower.alarmFlags[i].lowWarning);
                printf("  %-33s: %u\n", DDM_FIELD_TX_BIAS_ALARM_HIGH, cableDDMInfo.txBias.alarmFlags[i].highAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_TX_BIAS_ALARM_LOW, cableDDMInfo.txBias.alarmFlags[i].lowAlarm);
                printf("  %-33s: %u\n", DDM_FIELD_TX_BIAS_WARNING_HIGH, cableDDMInfo.txBias.alarmFlags[i].highWarning);
                printf("  %-33s: %u\n", DDM_FIELD_TX_BIAS_WARNING_LOW, cableDDMInfo.txBias.alarmFlags[i].lowWarning);
            }
        }
    }

    if (MST_QUERY_HAS(&cableDDMInfo, TELEMETRY_CABLE_DDM_INFO_THRESHOLDS))
    {
        printThreshold(DDM_FIELD_TEMPERATURE, cableDDMInfo.temperature.thresholds);
        printThreshold(DDM_FIELD_VOLTAGE, cableDDMInfo.voltage.thresholds);
        printThreshold(DDM_FIELD_RX_POWER, cableDDMInfo.rxPower.thresholds);
        printThreshold(DDM_FIELD_TX_POWER, cableDDMInfo.txPower.thresholds);
        printThreshold(DDM_FIELD_TX_BIAS, cableDDMInfo.txBias.thresholds);
    }

    EXPECT_NE(cableDDMInfo.header.valid_fields_mask, 0u) << "Valid fields mask should be non-zero";

    if (MST_QUERY_HAS(&cableDDMInfo, TELEMETRY_CABLE_DDM_INFO_CHANNELS))
    {
        EXPECT_LE(cableDDMInfo.numberOfChannels, 8u) << "Channel count should be <= 8";
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
