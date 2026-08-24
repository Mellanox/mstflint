/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

/*
 * Coverage-focused tests for mft_sdk_telemetry.cpp.
 *
 * Group A tests do NOT require any Mellanox/NVIDIA hardware.
 * Group B tests need a real device -- pass -d <BDF> to enable them.
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

// ============================================================================
// GROUP A: No device required -- null/invalid parameter validation
// ============================================================================

class MftTelemetryNoDeviceTest : public ::testing::Test
{
};

TEST_F(MftTelemetryNoDeviceTest, OpInfoNullDevice)
{
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    EXPECT_EQ(mstGetTelemetryOperationalInfo(NULL, nullptr, &opInfo), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, OpInfoNullStruct)
{
    EXPECT_EQ(mstGetTelemetryOperationalInfo(NULL, nullptr, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, FecHistogramNullDevice)
{
    MstFecHistogram hist;
    MST_QUERY_INIT(&hist);
    EXPECT_EQ(mstGetFecHistogram(NULL, nullptr, &hist), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, FecHistogramNullStruct)
{
    EXPECT_EQ(mstGetFecHistogram(NULL, nullptr, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CountersInfoNullDevice)
{
    MstCountersInfo counters;
    MST_QUERY_INIT(&counters);
    EXPECT_EQ(mstGetCountersInfo(NULL, nullptr, &counters), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CountersInfoNullStruct)
{
    EXPECT_EQ(mstGetCountersInfo(NULL, nullptr, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CableDDMNullDevice)
{
    MstCableDDMInfo ddm;
    MST_QUERY_INIT(&ddm);
    EXPECT_EQ(mstGetCableDDMInfo(NULL, nullptr, &ddm), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CableDDMNullStruct)
{
    EXPECT_EQ(mstGetCableDDMInfo(NULL, nullptr, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, ModuleInfoNullDevice)
{
    MstModuleInfo modInfo;
    MST_QUERY_INIT(&modInfo);
    EXPECT_EQ(mstGetModuleInfo(NULL, nullptr, &modInfo), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, ModuleInfoNullStruct)
{
    EXPECT_EQ(mstGetModuleInfo(NULL, nullptr, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, OpInfoInvalidHeaderSize)
{
    MstTelemetryOperationalInfo opInfo;
    memset(&opInfo, 0, sizeof(opInfo));
    opInfo.header.size = 0;
    EXPECT_EQ(mstGetTelemetryOperationalInfo(NULL, nullptr, &opInfo), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, FecHistogramInvalidHeaderSize)
{
    MstFecHistogram hist;
    memset(&hist, 0, sizeof(hist));
    hist.header.size = 0;
    EXPECT_EQ(mstGetFecHistogram(NULL, nullptr, &hist), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CountersInfoInvalidHeaderSize)
{
    MstCountersInfo counters;
    memset(&counters, 0, sizeof(counters));
    counters.header.size = 0;
    EXPECT_EQ(mstGetCountersInfo(NULL, nullptr, &counters), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, CableDDMInvalidHeaderSize)
{
    MstCableDDMInfo ddm;
    memset(&ddm, 0, sizeof(ddm));
    ddm.header.size = 0;
    EXPECT_EQ(mstGetCableDDMInfo(NULL, nullptr, &ddm), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, ModuleInfoInvalidHeaderSize)
{
    MstModuleInfo modInfo;
    memset(&modInfo, 0, sizeof(modInfo));
    modInfo.header.size = 0;
    EXPECT_EQ(mstGetModuleInfo(NULL, nullptr, &modInfo), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, TelemetryJsonNullDevice)
{
    char* json = nullptr;
    EXPECT_EQ(mstGetTelemetryJson(NULL, nullptr, MST_TELEMETRY_VIEW_OPERATIONAL, &json), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, TelemetryJsonNullOutput)
{
    EXPECT_EQ(mstGetTelemetryJson(NULL, nullptr, MST_TELEMETRY_VIEW_OPERATIONAL, NULL), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, TelemetryJsonZeroViews)
{
    char* json = nullptr;
    EXPECT_EQ(mstGetTelemetryJson(NULL, nullptr, 0, &json), MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryNoDeviceTest, FreeJsonStringNull)
{
    // mstFreeJsonString(NULL) must not crash; it reports the bad argument.
    EXPECT_EQ(mstFreeJsonString(NULL), MST_ERROR_INVALID_ARGUMENT);
}

// MST_QUERY_HAS via a runtime bit index, so bits >= MASK_SIZE do not trigger
// constant shift-overflow warnings in the not-taken branch of the macro.
static bool mstQueryHasBit(const mstQueryHeader* header, uint32_t bit)
{
    return MST_QUERY_HAS(header, bit) != 0;
}

TEST_F(MftTelemetryNoDeviceTest, QueryHasMaskWordBoundaries)
{
    MstModuleInfo modInfo;
    MST_QUERY_INIT(&modInfo);
    modInfo.header.valid_fields_mask = (1ULL << 0) | (1ULL << 53) | (1ULL << 63);
    modInfo.header.extended_valid_fields_mask = (1ULL << 0) | (1ULL << 63); // query bits 64 and 127

    EXPECT_TRUE(mstQueryHasBit(&modInfo.header, 0));
    EXPECT_TRUE(mstQueryHasBit(&modInfo.header, TELEMETRY_MODULE_INFO_TX_ADAPTIVE_EQ_FAULT_PER_LANE)); // bit 53
    EXPECT_TRUE(mstQueryHasBit(&modInfo.header, MASK_SIZE - 1));
    EXPECT_TRUE(mstQueryHasBit(&modInfo.header, MASK_SIZE));         // first extended-mask bit
    EXPECT_TRUE(mstQueryHasBit(&modInfo.header, 2 * MASK_SIZE - 1)); // last extended-mask bit
    EXPECT_FALSE(mstQueryHasBit(&modInfo.header, 1));
    EXPECT_FALSE(mstQueryHasBit(&modInfo.header, MASK_SIZE - 2));
    EXPECT_FALSE(mstQueryHasBit(&modInfo.header, MASK_SIZE + 1));
    EXPECT_FALSE(mstQueryHasBit(&modInfo.header, 2 * MASK_SIZE - 2));
}

TEST_F(MftTelemetryNoDeviceTest, QueryClearPreservesHeaderSize)
{
    MstFecHistogram hist;
    MST_QUERY_INIT(&hist);
    hist.header.valid_fields_mask = ~0ULL;
    hist.header.extended_valid_fields_mask = ~0ULL;
    hist.numberOfBins = 5;
    hist.bins[0].numOfErrors = 42;

    MST_QUERY_CLEAR(&hist);

    EXPECT_EQ(hist.header.size, sizeof(hist));
    EXPECT_EQ(hist.header.valid_fields_mask, 0u);
    EXPECT_EQ(hist.header.extended_valid_fields_mask, 0u);
    EXPECT_EQ(hist.numberOfBins, (uint8_t)0);
    EXPECT_EQ(hist.bins[0].numOfErrors, 0u);
}

// ============================================================================
// GROUP B: Requires device (-d flag)
// ============================================================================

class MftTelemetryDeviceTest : public ::testing::Test
{
protected:
    MstDevice mstDevice = nullptr;
    bool hasDevice = false;

    void SetUp() override
    {
        if (g_devicePci.empty())
        {
            return;
        }
        MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
        if (status == MST_SUCCESS)
        {
            hasDevice = true;
        }
    }

    void TearDown() override
    {
        if (mstDevice)
        {
            mstReleaseDeviceHandle(mstDevice);
        }
    }
};

#define SKIP_IF_NO_DEVICE()                                                         \
    do                                                                              \
    {                                                                               \
        if (!hasDevice)                                                             \
        {                                                                           \
            std::cout << "[  SKIPPED ] No device specified (-d flag)" << std::endl; \
            return;                                                                 \
        }                                                                           \
    } while (0)

/* A device that cannot answer port-level registers at all -- firmware that never
 * finished initialising, no driver bound to the function, a DPU whose ports are
 * owned by the Arm side -- fails every port-level telemetry call, and fails them
 * identically in mlxlink_ext and mlxreg_ext too. That is a property of the
 * machine, not a defect in the SDK, so the cases below skip instead of failing.
 *
 * The discriminator is the error MESSAGE, not the status: initMlxLinkSdk()
 * collapses every device-access failure into MST_ERROR_FAILED_TO_GET_TELEMETRY,
 * so the status alone cannot tell "this port is unreachable on this platform"
 * from a genuine telemetry regression. Deliberately narrow -- any other failure
 * keeps its hard assertion, so a real regression is still caught. If the SDK
 * ever grows a distinct code for access-register rejection, match on that here
 * instead.
 */
static bool isPortUnreachable(MstDevice dev, MstStatus status)
{
    if (status == MST_SUCCESS)
    {
        return false;
    }
    const char* err = mstGetLastErrorString(dev);
    if (!err)
    {
        return false;
    }
    const std::string message(err);
    return message.find("verify that driver is up") != std::string::npos ||
           message.find("Failed to send access register") != std::string::npos;
}

#define SKIP_IF_PORT_UNREACHABLE(status)                                          \
    do                                                                            \
    {                                                                             \
        if (isPortUnreachable(mstDevice, (status)))                               \
        {                                                                         \
            std::cout << "[  SKIPPED ] port-level telemetry unreachable on this " \
                      << "device: " << mstGetLastErrorString(mstDevice)           \
                      << std::endl;                                               \
            return;                                                               \
        }                                                                         \
    } while (0)

TEST_F(MftTelemetryDeviceTest, OperationalInfoFieldByField)
{
    SKIP_IF_NO_DEVICE();
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, nullptr, &opInfo);
    SKIP_IF_PORT_UNREACHABLE(status);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    EXPECT_NE(opInfo.header.valid_fields_mask, 0u);

    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_STATE))
    {
        EXPECT_GE(opInfo.state, 0);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_PHYSICAL_STATE))
    {
        EXPECT_GE(opInfo.physicalState, 0);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_SPEED))
    {
        EXPECT_GE(opInfo.speed, 0);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_WIDTH))
    {
        EXPECT_GT(opInfo.width, 0u);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_FEC))
    {
        EXPECT_GE(opInfo.fec, 0);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_LOOPBACK_MODE))
    {
        EXPECT_GE(opInfo.loopbackMode, 0);
    }
    if (MST_QUERY_HAS(&opInfo, TELEMETRY_OP_INFO_AUTO_NEGOTIATION))
    {
        EXPECT_GE(opInfo.autoNegotiation, 0);
    }
}

TEST_F(MftTelemetryDeviceTest, OpInfoWithInvalidHeaderSize)
{
    SKIP_IF_NO_DEVICE();
    MstTelemetryOperationalInfo opInfo;
    memset(&opInfo, 0, sizeof(opInfo));
    opInfo.header.size = 1;
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, nullptr, &opInfo);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, OpInfoNullPtr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, nullptr, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, GetFecHistogramBinValidation)
{
    SKIP_IF_NO_DEVICE();
    MstFecHistogram hist;
    MST_QUERY_INIT(&hist);
    MstStatus status = mstGetFecHistogram(mstDevice, nullptr, &hist);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] FEC histogram not supported" << std::endl;
        return;
    }
    EXPECT_GT(hist.numberOfBins, (uint8_t)0);
    EXPECT_LE(hist.numberOfBins, (uint8_t)MAX_NUM_OF_BINS);
    for (uint8_t i = 0; i < hist.numberOfBins; i++)
    {
        EXPECT_GE(hist.bins[i].maxRange, hist.bins[i].minRange);
    }
}

TEST_F(MftTelemetryDeviceTest, FecHistogramInvalidHeaderSize)
{
    SKIP_IF_NO_DEVICE();
    MstFecHistogram hist;
    memset(&hist, 0, sizeof(hist));
    hist.header.size = 1;
    MstStatus status = mstGetFecHistogram(mstDevice, nullptr, &hist);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, FecHistogramNullPtr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetFecHistogram(mstDevice, nullptr, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, GetCountersInfoDetailed)
{
    SKIP_IF_NO_DEVICE();
    MstCountersInfo counters;
    MST_QUERY_INIT(&counters);
    MstStatus status = mstGetCountersInfo(mstDevice, nullptr, &counters);
    SKIP_IF_PORT_UNREACHABLE(status);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    if (counters.header.valid_fields_mask == 0)
    {
        // No counters are reported when the port link is down/disabled.
        std::cout << "[  SKIPPED ] No counters available (port link down)" << std::endl;
        return;
    }

    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_TIME_SINCE_LAST_CLEAR))
    {
        EXPECT_GE(counters.timeSinceLastClear, 0.0);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_ERRORS))
    {
        EXPECT_GE(counters.effectivePhysicalErrors, 0u);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_BER))
    {
        // -255 is a valid sentinel meaning essentially zero BER
        EXPECT_GE(counters.effectivePhysicalBER.exponent, -255);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER))
    {
        EXPECT_GE(counters.rawPhysicalBER.exponent, -255);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_ERRORS_PER_LANE))
    {
        EXPECT_GT(counters.numberOfLanes, 0u);
        EXPECT_LE(counters.numberOfLanes, (unsigned int)MAX_NUM_OF_LANES);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER_PER_LANE))
    {
        EXPECT_GT(counters.numberOfLanes, 0u);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_LINK_DOWN_COUNTER))
    {
        EXPECT_GE(counters.linkDownCounter, 0u);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_LINK_ERROR_RECOVERY_COUNTER))
    {
        EXPECT_GE(counters.linkErrorRecoveryCounter, 0u);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_SYMBOL_ERRORS))
    {
        EXPECT_GE(counters.symbolErrors, 0u);
    }
    if (MST_QUERY_HAS(&counters, TELEMETRY_COUNTERS_INFO_SYMBOL_BER))
    {
        EXPECT_GE(counters.symbolBER.exponent, -255);
    }
}

TEST_F(MftTelemetryDeviceTest, CountersInfoInvalidHeaderSize)
{
    SKIP_IF_NO_DEVICE();
    MstCountersInfo counters;
    memset(&counters, 0, sizeof(counters));
    counters.header.size = 1;
    MstStatus status = mstGetCountersInfo(mstDevice, nullptr, &counters);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, CountersInfoNullPtr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetCountersInfo(mstDevice, nullptr, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, GetCableDDMDetailed)
{
    SKIP_IF_NO_DEVICE();
    MstCableDDMInfo ddm;
    MST_QUERY_INIT(&ddm);
    MstStatus status = mstGetCableDDMInfo(mstDevice, nullptr, &ddm);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cable DDM not available" << std::endl;
        return;
    }

    EXPECT_NE(ddm.header.valid_fields_mask, 0u);

    if (MST_QUERY_HAS(&ddm, TELEMETRY_CABLE_DDM_INFO_TEMPERATURE))
    {
        EXPECT_GE(ddm.temperature.value, -100.0f);
        EXPECT_LE(ddm.temperature.value, 200.0f);
    }
    if (MST_QUERY_HAS(&ddm, TELEMETRY_CABLE_DDM_INFO_VOLTAGE))
    {
        EXPECT_GE(ddm.voltage.value, 0.0f);
    }
    if (MST_QUERY_HAS(&ddm, TELEMETRY_CABLE_DDM_INFO_CHANNELS))
    {
        EXPECT_LE(ddm.numberOfChannels, (unsigned int)MAX_NUM_OF_CHANNELS);
    }
    if (MST_QUERY_HAS(&ddm, TELEMETRY_CABLE_DDM_INFO_THRESHOLDS))
    {
        // Modules often leave individual thresholds unpopulated (reported as 0),
        // which breaks the alarm-vs-warning ordering (e.g. lowAlarm=35,
        // lowWarning=0). Only check ordering when both bounds of a pair are set.
        if (ddm.temperature.thresholds.highAlarm != 0.0f && ddm.temperature.thresholds.highWarning != 0.0f)
        {
            EXPECT_GE(ddm.temperature.thresholds.highAlarm, ddm.temperature.thresholds.highWarning);
        }
        if (ddm.temperature.thresholds.lowAlarm != 0.0f && ddm.temperature.thresholds.lowWarning != 0.0f)
        {
            EXPECT_LE(ddm.temperature.thresholds.lowAlarm, ddm.temperature.thresholds.lowWarning);
        }
    }
}

TEST_F(MftTelemetryDeviceTest, CableDDMInvalidHeaderSize)
{
    SKIP_IF_NO_DEVICE();
    MstCableDDMInfo ddm;
    memset(&ddm, 0, sizeof(ddm));
    ddm.header.size = 1;
    MstStatus status = mstGetCableDDMInfo(mstDevice, nullptr, &ddm);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, CableDDMNullPtr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetCableDDMInfo(mstDevice, nullptr, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, GetModuleInfoAllFields)
{
    SKIP_IF_NO_DEVICE();
    MstModuleInfo modInfo;
    MST_QUERY_INIT(&modInfo);
    MstStatus status = mstGetModuleInfo(mstDevice, nullptr, &modInfo);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Module info not available" << std::endl;
        return;
    }
    if (modInfo.header.valid_fields_mask == 0u)
    {
        // Success with no module plugged -> every field bit clear; nothing to check.
        std::cout << "[  SKIPPED ] Module info not available (no module plugged)" << std::endl;
        return;
    }

    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_IDENTIFIER))
    {
        EXPECT_GE(modInfo.vendorInfo.identifier, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_COMPLIANCE))
    {
        EXPECT_GT(strlen(modInfo.vendorInfo.compliance), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_CABLE_TECHNOLOGY))
    {
        EXPECT_GE(modInfo.vendorInfo.cableTechnology, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_CABLE_TYPE))
    {
        EXPECT_GE(modInfo.vendorInfo.cableType, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_OUI))
    {
        EXPECT_GE(modInfo.vendorInfo.oui, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_VENDOR_NAME))
    {
        EXPECT_GT(strlen(modInfo.vendorInfo.vendorName), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_VENDOR_PART_NUMBER))
    {
        EXPECT_GT(strlen(modInfo.vendorInfo.vendorPartNumber), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_VENDOR_SERIAL_NUMBER))
    {
        EXPECT_GT(strlen(modInfo.vendorInfo.vendorSerialNumber), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_VENDOR_REVISION))
    {
        EXPECT_GT(strlen(modInfo.vendorInfo.vendorRevision), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_WAVELENGTH))
    {
        EXPECT_GE(modInfo.vendorInfo.wavelength, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_FW_VERSION))
    {
        EXPECT_GT(modInfo.fwVersion.chipId, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_DIGITAL_DIAGNOSTIC_MONITORING))
    {
        // DDM is boolean, just validate it was set
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_POWER_CLASS))
    {
        EXPECT_GT(strlen(modInfo.powerAndCdrInfo.powerClass), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_MAX_POWER))
    {
        EXPECT_GT(strlen(modInfo.powerAndCdrInfo.maxPower), 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_INTRA_ASIC_LATENCY))
    {
        EXPECT_GE(modInfo.latencyInfo.intraAsicLatency, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_MODULE_DATAPATH_LATENCY))
    {
        EXPECT_GE(modInfo.latencyInfo.moduleDatapathLatency, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_ROUND_TRIP_LATENCY))
    {
        EXPECT_GE(modInfo.latencyInfo.roundTripLatency, 0.0f);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_MANUFACTURING_DATE))
    {
        EXPECT_GT(modInfo.berModuleInfo.manufacturingDate.year, 0u);
        EXPECT_GE(modInfo.berModuleInfo.manufacturingDate.month, 1u);
        EXPECT_LE(modInfo.berModuleInfo.manufacturingDate.month, 12u);
        EXPECT_GE(modInfo.berModuleInfo.manufacturingDate.day, 1u);
        EXPECT_LE(modInfo.berModuleInfo.manufacturingDate.day, 31u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_MODULE_STATE))
    {
        EXPECT_GE(modInfo.berModuleInfo.moduleState, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_NOMINAL_BIT_RATE))
    {
        EXPECT_GE(modInfo.berModuleInfo.nominalBitRate, 0.0f);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_RX_POWER_TYPE))
    {
        EXPECT_GE(modInfo.berModuleInfo.rxPowerType, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_ERROR_CODE_RESPONSE))
    {
        EXPECT_GE(modInfo.berModuleInfo.errorCodeResponse, 0);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_ATTENUATION_5G))
    {
        EXPECT_GE(modInfo.attenuationInfo.attenuation5g, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_ATTENUATION_7G))
    {
        EXPECT_GE(modInfo.attenuationInfo.attenuation7g, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_ATTENUATION_12G))
    {
        EXPECT_GE(modInfo.attenuationInfo.attenuation12g, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_SMF_LENGTH))
    {
        EXPECT_GE(modInfo.berModuleInfo.smfLength, 0u);
    }
    if (MST_QUERY_HAS(&modInfo, TELEMETRY_MODULE_INFO_IB_CABLE_WIDTH))
    {
        EXPECT_GT(strlen(modInfo.berModuleInfo.ibCableWidth), 0u);
    }
}

TEST_F(MftTelemetryDeviceTest, ModuleInfoInvalidHeaderSize)
{
    SKIP_IF_NO_DEVICE();
    MstModuleInfo modInfo;
    memset(&modInfo, 0, sizeof(modInfo));
    modInfo.header.size = 1;
    MstStatus status = mstGetModuleInfo(mstDevice, nullptr, &modInfo);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, ModuleInfoNullPtr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetModuleInfo(mstDevice, nullptr, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// Minimal structural sanity for a serialized telemetry JSON document.
static void expectJsonBalanced(const char* json)
{
    size_t openBraces = 0;
    size_t closeBraces = 0;
    for (const char* c = json; *c != '\0'; c++)
    {
        openBraces += (*c == '{');
        closeBraces += (*c == '}');
    }
    EXPECT_EQ(openBraces, closeBraces);
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonOperationalView)
{
    SKIP_IF_NO_DEVICE();
    char* json = nullptr;
    MstStatus status = mstGetTelemetryJson(mstDevice, nullptr, MST_TELEMETRY_VIEW_OPERATIONAL, &json);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json[0], '{');
    expectJsonBalanced(json);
    EXPECT_NE(strstr(json, FIELD_OPERATIONAL_INFO), nullptr);
    EXPECT_EQ(mstFreeJsonString(json), MST_SUCCESS);
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonCountersView)
{
    SKIP_IF_NO_DEVICE();
    char* json = nullptr;
    MstStatus status = mstGetTelemetryJson(mstDevice, nullptr, MST_TELEMETRY_VIEW_COUNTERS, &json);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json[0], '{');
    expectJsonBalanced(json);
    EXPECT_NE(strstr(json, FIELD_PHYSICAL_COUNTERS_AND_BER_INFO), nullptr);
    EXPECT_EQ(mstFreeJsonString(json), MST_SUCCESS);
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonGeneralView)
{
    SKIP_IF_NO_DEVICE();
    char* json = nullptr;
    MstStatus status = mstGetTelemetryJson(mstDevice, nullptr, MST_TELEMETRY_VIEW_GENERAL, &json);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json[0], '{');
    expectJsonBalanced(json);
    // The general view carries the full mlxlink default (PDDR) sections.
    EXPECT_NE(strstr(json, FIELD_OPERATIONAL_INFO), nullptr);
    EXPECT_EQ(mstFreeJsonString(json), MST_SUCCESS);
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonPerView)
{
    SKIP_IF_NO_DEVICE();
    // Sweep every defined view bit; the enum has no ALL sentinel, so the loop
    // bound is its last member.
    for (uint32_t bit = MST_TELEMETRY_VIEW_OPERATIONAL; bit <= MST_TELEMETRY_VIEW_FEC_HISTOGRAM; bit <<= 1)
    {
        MstTelemetryView view = static_cast<MstTelemetryView>(bit);
        char* json = nullptr;
        MstStatus status = mstGetTelemetryJson(mstDevice, nullptr, view, &json);
        if (status != MST_SUCCESS)
        {
            // Cable/module/eye/... views depend on the plugged module and device family.
            std::cout << "[  SKIPPED ] JSON view 0x" << std::hex << view << std::dec << " not supported" << std::endl;
            continue;
        }
        ASSERT_NE(json, nullptr) << "view " << view;
        expectJsonBalanced(json);
        EXPECT_EQ(mstFreeJsonString(json), MST_SUCCESS);
    }
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonModuleGeneralCountersCombo)
{
    SKIP_IF_NO_DEVICE();
    char* json = nullptr;
    MstStatus status = mstGetTelemetryJson(
      mstDevice, nullptr, MST_TELEMETRY_VIEW_MODULE | MST_TELEMETRY_VIEW_GENERAL | MST_TELEMETRY_VIEW_COUNTERS, &json);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Module info not available" << std::endl;
        return;
    }
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json[0], '{');
    expectJsonBalanced(json);
    EXPECT_NE(strstr(json, FIELD_MODULE_INFO), nullptr);
    EXPECT_NE(strstr(json, FIELD_OPERATIONAL_INFO), nullptr);
    EXPECT_NE(strstr(json, FIELD_PHYSICAL_COUNTERS_AND_BER_INFO), nullptr);
    EXPECT_EQ(mstFreeJsonString(json), MST_SUCCESS);
}

TEST_F(MftTelemetryDeviceTest, GetTelemetryJsonZeroViews)
{
    SKIP_IF_NO_DEVICE();
    char* json = nullptr;
    EXPECT_EQ(mstGetTelemetryJson(mstDevice, nullptr, 0, &json), MST_ERROR_INVALID_ARGUMENT);
}

// Context bound to explicit label port 1 (exists on all supported devices).
static MstTelemetryContext makePort1Context()
{
    MstTelemetryContext context;
    MST_TELEMETRY_CONTEXT_INIT(&context);
    snprintf(context.label_port, sizeof(context.label_port), "1");
    return context;
}

TEST_F(MftTelemetryDeviceTest, OperationalInfoExplicitPort)
{
    SKIP_IF_NO_DEVICE();
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    MstTelemetryContext context = makePort1Context();
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, &context, &opInfo);
    SKIP_IF_PORT_UNREACHABLE(status);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    EXPECT_NE(opInfo.header.valid_fields_mask, 0u);
}

TEST_F(MftTelemetryDeviceTest, CountersInfoExplicitPort)
{
    SKIP_IF_NO_DEVICE();
    MstCountersInfo counters;
    MST_QUERY_INIT(&counters);
    MstTelemetryContext context = makePort1Context();
    MstStatus status = mstGetCountersInfo(mstDevice, &context, &counters);
    SKIP_IF_PORT_UNREACHABLE(status);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
}

TEST_F(MftTelemetryDeviceTest, FecHistogramExplicitPort)
{
    SKIP_IF_NO_DEVICE();
    MstFecHistogram hist;
    MST_QUERY_INIT(&hist);
    MstTelemetryContext context = makePort1Context();
    MstStatus status = mstGetFecHistogram(mstDevice, &context, &hist);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] FEC histogram not supported" << std::endl;
        return;
    }
    EXPECT_LE(hist.numberOfBins, (uint8_t)MAX_NUM_OF_BINS);
}

TEST_F(MftTelemetryDeviceTest, CableDDMExplicitPort)
{
    SKIP_IF_NO_DEVICE();
    MstCableDDMInfo ddm;
    MST_QUERY_INIT(&ddm);
    MstTelemetryContext context = makePort1Context();
    MstStatus status = mstGetCableDDMInfo(mstDevice, &context, &ddm);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Cable DDM not available" << std::endl;
        return;
    }
    EXPECT_NE(ddm.header.valid_fields_mask, 0u);
    EXPECT_LE(ddm.numberOfChannels, (unsigned int)MAX_NUM_OF_CHANNELS);
}

TEST_F(MftTelemetryDeviceTest, ModuleInfoExplicitPort)
{
    SKIP_IF_NO_DEVICE();
    MstModuleInfo modInfo;
    MST_QUERY_INIT(&modInfo);
    MstTelemetryContext context = makePort1Context();
    MstStatus status = mstGetModuleInfo(mstDevice, &context, &modInfo);
    if (status != MST_SUCCESS)
    {
        std::cout << "[  SKIPPED ] Module info not available" << std::endl;
        return;
    }
    if (modInfo.header.valid_fields_mask == 0u)
    {
        // Success with no module plugged -> every field bit clear; nothing to check.
        std::cout << "[  SKIPPED ] Module info not available (no module plugged)" << std::endl;
        return;
    }
}

TEST_F(MftTelemetryDeviceTest, OpInfoTruncatedContextUsesDefaultPort)
{
    SKIP_IF_NO_DEVICE();
    // Old-ABI caller: only the size header is visible to the SDK, so label_port
    // must be ignored and the device default port used (TelemetryContextView).
    MstTelemetryContext context;
    MST_TELEMETRY_CONTEXT_INIT(&context);
    snprintf(context.label_port, sizeof(context.label_port), "999"); // would fail if honored
    context.size = sizeof(unsigned int);
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, &context, &opInfo);
    SKIP_IF_PORT_UNREACHABLE(status);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);
    EXPECT_NE(opInfo.header.valid_fields_mask, 0u);
}

// CR space and I2C additional coverage tests (bundled here to avoid extra directories)

TEST_F(MftTelemetryDeviceTest, ReadCRSpaceMultipleSizes)
{
    SKIP_IF_NO_DEVICE();
    uint32_t data4[1];
    EXPECT_EQ(mstReadCRSpace(mstDevice, 0x0, data4, 4), MST_SUCCESS);

    uint32_t data16[4];
    EXPECT_EQ(mstReadCRSpace(mstDevice, 0x0, data16, 16), MST_SUCCESS);

    uint32_t data64[16];
    EXPECT_EQ(mstReadCRSpace(mstDevice, 0x0, data64, 64), MST_SUCCESS);
}

TEST_F(MftTelemetryDeviceTest, ReadCRSpaceNullData)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstReadCRSpace(mstDevice, 0x0, NULL, 4);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, WriteCRSpaceNullData)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstWriteCRSpace(mstDevice, 0x0, NULL, 4);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, ReadCRSpaceZeroLength)
{
    SKIP_IF_NO_DEVICE();
    // Zero bytes is a no-op for every mread4_block flavor: rc == byteLength == 0.
    uint32_t data[1] = {0x5a5a5a5a};
    EXPECT_EQ(mstReadCRSpace(mstDevice, 0x0, data, 0), MST_SUCCESS);
    EXPECT_EQ(data[0], 0x5a5a5a5au); // nothing read, buffer untouched
}

TEST_F(MftTelemetryDeviceTest, ReadCRSpaceUnalignedLength)
{
    SKIP_IF_NO_DEVICE();
    // A non-dword byteLength is transport-dependent: user-space VSC/BAR0 access
    // rejects it (rc != byteLength => MST_ERROR_FAILED_TO_READ_CR_SPACE) while the
    // mst-driver paths read whole dwords and report success. Pin that it never
    // crashes and never reports any other status.
    uint32_t data[1] = {0};
    MstStatus status = mstReadCRSpace(mstDevice, 0x0, data, 3);
    EXPECT_TRUE(status == MST_SUCCESS || status == MST_ERROR_FAILED_TO_READ_CR_SPACE);
}

TEST_F(MftTelemetryDeviceTest, SetI2cSecondaryMultipleValues)
{
    SKIP_IF_NO_DEVICE();
    uint8_t addr = 0;
    MstStatus status = mstGetI2cSecondary(mstDevice, &addr);
    ASSERT_EQ(status, MST_SUCCESS);
    uint8_t origAddr = addr;

    status = mstSetI2cSecondary(mstDevice, 0x50);
    EXPECT_EQ(status, MST_SUCCESS);
    status = mstGetI2cSecondary(mstDevice, &addr);
    EXPECT_EQ(status, MST_SUCCESS);
    EXPECT_EQ(addr, 0x50);

    status = mstSetI2cSecondary(mstDevice, 0x48);
    EXPECT_EQ(status, MST_SUCCESS);
    status = mstGetI2cSecondary(mstDevice, &addr);
    EXPECT_EQ(status, MST_SUCCESS);
    EXPECT_EQ(addr, 0x48);

    mstSetI2cSecondary(mstDevice, origAddr);
}

TEST_F(MftTelemetryDeviceTest, GetI2cSecondaryNullAddr)
{
    SKIP_IF_NO_DEVICE();
    MstStatus status = mstGetI2cSecondary(mstDevice, NULL);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

TEST_F(MftTelemetryDeviceTest, GetLastErrorAfterSuccess)
{
    SKIP_IF_NO_DEVICE();
    MstTelemetryOperationalInfo opInfo;
    MST_QUERY_INIT(&opInfo);
    MstStatus status = mstGetTelemetryOperationalInfo(mstDevice, nullptr, &opInfo);
    if (status == MST_SUCCESS)
    {
        const char* err = mstGetLastErrorString(mstDevice);
        EXPECT_NE(err, nullptr);
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
