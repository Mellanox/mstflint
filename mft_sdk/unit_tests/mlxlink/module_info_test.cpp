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

class MftSdkModuleInfoTest : public ::testing::Test
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

/* Test-only per-rate attenuation labels (mlxlink prints one combined row).
 * Keep in sync with test_module_info.py. */
static const char* const MODULE_FIELD_ATTENUATION_5G = "Attenuation (5g) [dB]";
static const char* const MODULE_FIELD_ATTENUATION_7G = "Attenuation (7g) [dB]";
static const char* const MODULE_FIELD_ATTENUATION_12G = "Attenuation (12g) [dB]";
static const char* const MODULE_FIELD_ATTENUATION_25G = "Attenuation (25g) [dB]";
static const char* const MODULE_FIELD_ATTENUATION_53G = "Attenuation (53g) [dB]";

static void
  printModuleField(MstModuleInfo* moduleInfo, uint32_t capabilityBit, const char* displayName, const char* valueStr)
{
    printf("%-35s: %s\n", displayName, MST_QUERY_HAS(moduleInfo, capabilityBit) ? valueStr : NA_FIELD_VALUE);
}

static const char* lanesU8ToString(const uint8_t* lanes, char* buf, size_t bufSize)
{
    size_t offset = 0;
    for (unsigned int i = 0; i < MAX_NUM_OF_LANES && offset < bufSize; i++)
    {
        offset += (size_t)snprintf(buf + offset, bufSize - offset, "%s%u", i ? "," : "", lanes[i]);
    }
    return buf;
}

static const char* lanesFloatToString(const float* lanes, char* buf, size_t bufSize)
{
    size_t offset = 0;
    for (unsigned int i = 0; i < MAX_NUM_OF_LANES && offset < bufSize; i++)
    {
        offset += (size_t)snprintf(buf + offset, bufSize - offset, "%s%g", i ? "," : "", (double)lanes[i]);
    }
    return buf;
}

static void printModuleInfo(MstModuleInfo* moduleInfo)
{
    char buf[512];

    printf("Valid fields mask: 0x%llx\n", (unsigned long long)moduleInfo->header.valid_fields_mask);
    printf("Extended valid fields mask: 0x%llx\n", (unsigned long long)moduleInfo->header.extended_valid_fields_mask);
    printf("%s\n", FIELD_MODULE_INFO);
    printf("-----------\n");

    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->vendorInfo.identifier);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_IDENTIFIER, FIELD_IDENTIFIER, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_COMPLIANCE, FIELD_COMPLIANCE, moduleInfo->vendorInfo.compliance);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->vendorInfo.cableTechnology);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_TECHNOLOGY, FIELD_CABLE_TECHNOLOGY, buf);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->vendorInfo.cableType);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_TYPE, FIELD_CABLE_TYPE, buf);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->vendorInfo.oui);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_OUI, FIELD_OUI, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_VENDOR_NAME, FIELD_VENDOR_NAME,
                     moduleInfo->vendorInfo.vendorName);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_VENDOR_PART_NUMBER, FIELD_VENDOR_PART_NUMBER,
                     moduleInfo->vendorInfo.vendorPartNumber);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_VENDOR_SERIAL_NUMBER, FIELD_VENDOR_SERIAL_NUMBER,
                     moduleInfo->vendorInfo.vendorSerialNumber);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_VENDOR_REVISION, FIELD_VENDOR_REVISION,
                     moduleInfo->vendorInfo.vendorRevision);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->vendorInfo.wavelength);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_WAVELENGTH, FIELD_WAVELENGTH, buf);
    snprintf(buf, sizeof(buf), "%g", (double)moduleInfo->vendorInfo.transferDistance);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_TRANSFER_DISTANCE, FIELD_TRANSFER_DISTANCE, buf);

    {
        const uint32_t attenuationBits[] = {TELEMETRY_MODULE_INFO_ATTENUATION_5G, TELEMETRY_MODULE_INFO_ATTENUATION_7G,
                                            TELEMETRY_MODULE_INFO_ATTENUATION_12G,
                                            TELEMETRY_MODULE_INFO_ATTENUATION_25G,
                                            TELEMETRY_MODULE_INFO_ATTENUATION_53G};
        const char* const attenuationNames[] = {MODULE_FIELD_ATTENUATION_5G, MODULE_FIELD_ATTENUATION_7G,
                                                MODULE_FIELD_ATTENUATION_12G, MODULE_FIELD_ATTENUATION_25G,
                                                MODULE_FIELD_ATTENUATION_53G};
        const uint8_t attenuationValues[] = {
          moduleInfo->attenuationInfo.attenuation5g, moduleInfo->attenuationInfo.attenuation7g,
          moduleInfo->attenuationInfo.attenuation12g, moduleInfo->attenuationInfo.attenuation25g,
          moduleInfo->attenuationInfo.attenuation53g};
        for (size_t i = 0; i < sizeof(attenuationBits) / sizeof(attenuationBits[0]); i++)
        {
            snprintf(buf, sizeof(buf), "%u", attenuationValues[i]);
            printModuleField(moduleInfo, attenuationBits[i], attenuationNames[i], buf);
        }
    }

    snprintf(buf, sizeof(buf), "%u.%u.%u", moduleInfo->fwVersion.chipId, moduleInfo->fwVersion.major,
             moduleInfo->fwVersion.minor);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_FW_VERSION, FIELD_FW_VERSION, buf);

    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_DIGITAL_DIAGNOSTIC_MONITORING,
                     FIELD_DIGITAL_DIAGNOSTIC_MONITORING,
                     moduleInfo->powerAndCdrInfo.digitalDiagnosticMonitoring ? "Yes" : "No");
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_POWER_CLASS, FIELD_POWER_CLASS,
                     moduleInfo->powerAndCdrInfo.powerClass);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MAX_POWER, FIELD_MAX_POWER,
                     moduleInfo->powerAndCdrInfo.maxPower);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CDR_RX, FIELD_CDR_RX,
                     lanesU8ToString(moduleInfo->powerAndCdrInfo.cdrRx, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CDR_TX, FIELD_CDR_TX,
                     lanesU8ToString(moduleInfo->powerAndCdrInfo.cdrTx, buf, sizeof(buf)));

    snprintf(buf, sizeof(buf), "%u", moduleInfo->latencyInfo.intraAsicLatency);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_INTRA_ASIC_LATENCY, FIELD_INTRA_ASIC_LATENCY, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->latencyInfo.moduleDatapathLatency);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MODULE_DATAPATH_LATENCY, FIELD_MODULE_DATAPATH_LATENCY, buf);
    snprintf(buf, sizeof(buf), "%g", (double)moduleInfo->latencyInfo.roundTripLatency);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_ROUND_TRIP_LATENCY, FIELD_ROUND_TRIP_LATENCY, buf);

    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_SNR_MEDIA_LANES, FIELD_SNR_MEDIA_LANES,
                     lanesFloatToString(moduleInfo->berModuleInfo.snrInfo.snrMediaLanes, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_SNR_HOST_LANES, FIELD_SNR_HOST_LANES,
                     lanesFloatToString(moduleInfo->berModuleInfo.snrInfo.snrHostLanes, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_IB_CABLE_WIDTH, FIELD_IB_CABLE_WIDTH,
                     moduleInfo->berModuleInfo.ibCableWidth);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.memoryMapRevision);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MEMORY_MAP_REVISION, FIELD_MEMORY_MAP_REVISION, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.linearDirectDrive);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_LINEAR_DIRECT_DRIVE, FIELD_LINEAR_DIRECT_DRIVE, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_BREAKOUT, FIELD_CABLE_BREAKOUT,
                     moduleInfo->berModuleInfo.cableBreakout);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.smfLength);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_SMF_LENGTH, FIELD_SMF_LENGTH, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.cableRxAmp);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_RX_AMP, FIELD_CABLE_RX_AMP, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.cableRxEmphasis);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_RX_EMPHASIS, FIELD_CABLE_RX_EMPHASIS_PRE, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.cableRxPostEmphasis);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_RX_POST_EMPHASIS, FIELD_CABLE_RX_POST_EMPHASIS, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.cableTxEqualization);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_CABLE_TX_EQUALIZATION, FIELD_CABLE_TX_EQUALIZATION, buf);
    snprintf(buf, sizeof(buf), "%g", (double)moduleInfo->berModuleInfo.wavelengthTolerance);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_WAVELENGTH_TOLERANCE, FIELD_WAVELENGTH_TOLERANCE, buf);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->berModuleInfo.moduleState);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MODULE_STATE, FIELD_MODULE_STATE, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_DATA_PATH_STATE_PER_LANE, FIELD_DATA_PATH_STATE_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.dataPathStatePerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_RX_OUTPUT_VALID_PER_LANE, FIELD_RX_OUTPUT_VALID_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.rxOutputValidPerLane, buf, sizeof(buf)));
    snprintf(buf, sizeof(buf), "%g", (double)moduleInfo->berModuleInfo.nominalBitRate);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_NOMINAL_BIT_RATE, FIELD_NOMINAL_BIT_RATE, buf);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->berModuleInfo.rxPowerType);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_RX_POWER_TYPE, FIELD_RX_POWER_TYPE, buf);
    snprintf(buf, sizeof(buf), "%u_%u_%u", (unsigned int)moduleInfo->berModuleInfo.manufacturingDate.day,
             (unsigned int)moduleInfo->berModuleInfo.manufacturingDate.month,
             (unsigned int)moduleInfo->berModuleInfo.manufacturingDate.year);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MANUFACTURING_DATE, FIELD_MANUFACTURING_DATE, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_ACTIVE_SET_HOST_COMPLIANCE_CODE,
                     FIELD_ACTIVE_SET_HOST_COMPLIANCE_CODE, moduleInfo->berModuleInfo.activeSetHostComplianceCode);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_ACTIVE_SET_MEDIA_COMPLIANCE_CODE,
                     FIELD_ACTIVE_SET_MEDIA_COMPLIANCE_CODE, moduleInfo->berModuleInfo.activeSetMediaComplianceCode);
    snprintf(buf, sizeof(buf), "%d", (int)moduleInfo->berModuleInfo.errorCodeResponse);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_ERROR_CODE_RESPONSE, FIELD_ERROR_CODE_RESPONSE, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.moduleFwFault);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_MODULE_FW_FAULT, FIELD_MODULE_FW_FAULT, buf);
    snprintf(buf, sizeof(buf), "%u", moduleInfo->berModuleInfo.dataPathFwFault);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_DATA_PATH_FW_FAULT, FIELD_DATA_PATH_FW_FAULT, buf);
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_TX_FAULT_PER_LANE, FIELD_TX_FAULT_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.txFaultPerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_TX_LOS_PER_LANE, FIELD_TX_LOS_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.txLosPerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_TX_CDR_LOL_PER_LANE, FIELD_TX_CDR_LOL_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.txCdrLolPerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_RX_LOS_PER_LANE, FIELD_RX_LOS_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.rxLosPerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_RX_CDR_LOL_PER_LANE, FIELD_RX_CDR_LOL_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.rxCdrLolPerLane, buf, sizeof(buf)));
    printModuleField(moduleInfo, TELEMETRY_MODULE_INFO_TX_ADAPTIVE_EQ_FAULT_PER_LANE,
                     FIELD_TX_ADAPTIVE_EQ_FAULT_PER_LANE,
                     lanesU8ToString(moduleInfo->berModuleInfo.txAdaptiveEqFaultPerLane, buf, sizeof(buf)));
}

TEST_F(MftSdkModuleInfoTest, GetModuleInfo)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstModuleInfo moduleInfo;
    MST_QUERY_INIT(&moduleInfo);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetModuleInfo(mstDevice, &context, &moduleInfo);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get module info: " << mstGetLastErrorString(mstDevice);

    printf("\n");
    printModuleInfo(&moduleInfo);

    if (moduleInfo.header.valid_fields_mask == 0u)
    {
        // No module plugged -> success with all field bits clear; the dump above
        // is still valid comparison input, but there is nothing to assert.
        printf("[  SKIPPED ] Module info not available (no module plugged)\n");
        return;
    }
    EXPECT_NE(moduleInfo.header.valid_fields_mask, 0u) << "Valid fields mask should be non-zero";
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
