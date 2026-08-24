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

#include "test_utils.h"

#include <string>
#include <sys/types.h>

// mlxlink_enums.h names bare `string` in a couple of helper structs (every
// mlxlink TU pulls std:: in unqualified before including it).
using std::string;
#include "mlxlink/modules/mlxlink_enums.h"

namespace
{

thread_local std::string g_stringBuffer;

/* Operational-info enum -> mlxlink display name.
 *
 * Deliberately NOT MlxlinkMaps::getInstance(). That singleton lives inside
 * the SDK shared object and is reached through a C++ class layout and a
 * std::string ABI that only agree when the harness and the .so were produced
 * by the same toolchain from the same headers. They are not: this harness is
 * built by MFT (pre-C++11 COW std::string, MFT's mlxlink_maps.h member
 * order) and is also run against libmstflint_sdk.so (SSO std::string,
 * mstflint's member order, MlxlinkMaps declared with a different member
 * index). Both mismatches are silent - the read lands in-bounds on garbage -
 * and every enum-decoded op-info field came out "Unknown(N)" even though the
 * numeric value underneath was correct.
 *
 * The display STRINGS below are the same mlxlink_enums.h constants
 * MlxlinkMaps::initSdkOperationalInfo*Mapping() uses, so an mlxlink rename
 * still propagates here automatically; only the value<->name pairing is
 * duplicated. Keep in sync with mlxlink/modules/mlxlink_maps.cpp.
 */
template<typename EnumType>
struct EnumName
{
    EnumType value;
    const char* name;
};

const EnumName<OperationalInfoState> STATE_NAMES[] = {
  {OPERATIONAL_INFO_STATE_DISABLE, PM_STATE_DISABLE},
  {OPERATIONAL_INFO_STATE_PORT_PLL_DOWN, PM_STATE_PORT_PLL_DOWN},
  {OPERATIONAL_INFO_STATE_POLLING, PM_STATE_POLLING},
  {OPERATIONAL_INFO_STATE_ACTIVE, PM_STATE_ACTIVE},
  {OPERATIONAL_INFO_STATE_CLOSE_PORT, PM_STATE_CLOSE_PORT},
  {OPERATIONAL_INFO_STATE_PHYSICAL_LINKUP, PM_STATE_PHYSICAL_LINKUP},
  {OPERATIONAL_INFO_STATE_SLEEP, PM_STATE_SLEEP},
  {OPERATIONAL_INFO_STATE_RX_DISABLE, PM_STATE_RX_DISABLE},
  {OPERATIONAL_INFO_STATE_SIGNAL_DETECT, PM_STATE_SIGNAL_DETECT},
  {OPERATIONAL_INFO_STATE_RECEIVER_DETECT, PM_STATE_RECEIVER_DETECT},
  {OPERATIONAL_INFO_STATE_SYNC_PEER, PM_STATE_SYNC_PEER},
  {OPERATIONAL_INFO_STATE_NEGOTIATION, PM_STATE_NEGOTIATION},
  {OPERATIONAL_INFO_STATE_TRAINING, PM_STATE_TRAINING},
  {OPERATIONAL_INFO_STATE_SUB_FSM_ACTIVE, PM_STATE_SUB_FSM_ACTIVE},
};

const EnumName<OperationalInfoPhysicalState> PHYSICAL_STATE_NAMES[] = {
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ENABLE, ETH_AN_FSM_ENABLE},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_XMIT_DISABLE, ETH_AN_FSM_XMIT_DISABLE},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ABILITY_DETECT, ETH_AN_FSM_ABILITY_DETECT},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_ACK_DETECT, ETH_AN_FSM_ACK_DETECT},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_COMPLETE_ACK, ETH_AN_FSM_COMPLETE_ACK},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_AN_GOOD_CHECK, ETH_AN_FSM_AN_GOOD_CHECK},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_LINK_UP, ETH_LINK_UP},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_NEXT_PAGE_WAIT, ETH_AN_FSM_NEXT_PAGE_WAIT},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_LINK_STAT_CHECK, ETH_AN_FSM_LINK_STAT_CHECK},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_EXTRA_TUNE, ETH_AN_FSM_EXTRA_TUNE},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_FIX_REVERSALS, ETH_AN_FSM_FIX_REVERSALS},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_IB_FAIL, ETH_AN_FSM_IB_FAIL},
  {OPERATIONAL_INFO_PHYSICAL_STATE_ETH_AN_FSM_POST_LOCK_TUNE, ETH_AN_FSM_POST_LOCK_TUNE},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_NA, IB_PHY_FSM_NA},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_INITIALIZING, IB_PHY_FSM_INITIALIZING},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_RECOVER_CONFIG, IB_PHY_FSM_RECOVER_CONFIG},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_CONFIG_TEST, IB_PHY_FSM_CONFIG_TEST},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_WAIT_REMOTE_TEST, IB_PHY_FSM_WAIT_REMOTE_TEST},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_WAIT_CFG_ENHANCED, IB_PHY_FSM_WAIT_CONFIG_ENHANCED},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_CONFIG_IDLE, IB_PHY_FSM_CONFIG_IDLE},
  {OPERATIONAL_INFO_PHYSICAL_STATE_IB_LINK_UP, IB_PHY_FSM_LINK_UP},
};

const EnumName<OperationalInfoSpeed> SPEED_NAMES[] = {
  {OPERATIONAL_INFO_SPEED_BASET10M, SPEED_BASET10M},
  {OPERATIONAL_INFO_SPEED_BASETX100M, SPEED_BASETX100M},
  {OPERATIONAL_INFO_SPEED_BASET1000M, SPEED_BASET1000M},
  {OPERATIONAL_INFO_SPEED_10M, SPEED_10M},
  {OPERATIONAL_INFO_SPEED_100M, SPEED_100M},
  {OPERATIONAL_INFO_SPEED_CX, SPEED_CX},
  {OPERATIONAL_INFO_SPEED_KX, SPEED_KX},
  {OPERATIONAL_INFO_SPEED_CX4, SPEED_CX4},
  {OPERATIONAL_INFO_SPEED_KX4, SPEED_KX4},
  {OPERATIONAL_INFO_SPEED_BASET10G, SPEED_BASET10G},
  {OPERATIONAL_INFO_SPEED_10GBE, SPEED_10GBE},
  {OPERATIONAL_INFO_SPEED_20GBE, SPEED_20GBE},
  {OPERATIONAL_INFO_SPEED_25GBE, SPEED_25GBE},
  {OPERATIONAL_INFO_SPEED_40GBE, SPEED_40GBE},
  {OPERATIONAL_INFO_SPEED_50GBE, SPEED_50GBE},
  {OPERATIONAL_INFO_SPEED_56GBE, SPEED_56GBE},
  {OPERATIONAL_INFO_SPEED_100GBE, SPEED_100GBE},
  {OPERATIONAL_INFO_SPEED_1G, SPEED_1G},
  {OPERATIONAL_INFO_SPEED_2_5G, SPEED_2_5G},
  {OPERATIONAL_INFO_SPEED_5G, SPEED_5G},
  {OPERATIONAL_INFO_SPEED_10G, SPEED_10G},
  {OPERATIONAL_INFO_SPEED_25G, SPEED_25G},
  {OPERATIONAL_INFO_SPEED_40G, SPEED_40G},
  {OPERATIONAL_INFO_SPEED_50G, SPEED_50G},
  {OPERATIONAL_INFO_SPEED_100G, SPEED_100G},
  {OPERATIONAL_INFO_SPEED_200G, SPEED_200G},
  {OPERATIONAL_INFO_SPEED_400G, SPEED_400G},
  {OPERATIONAL_INFO_SPEED_800G, SPEED_800G},
  {OPERATIONAL_INFO_SPEED_1600G, SPEED_1600G},
  {OPERATIONAL_INFO_SPEED_IB_SDR, SPEED_IB_SDR},
  {OPERATIONAL_INFO_SPEED_IB_DDR, SPEED_IB_DDR},
  {OPERATIONAL_INFO_SPEED_IB_QDR, SPEED_IB_QDR},
  {OPERATIONAL_INFO_SPEED_IB_FDR10, SPEED_IB_FDR10},
  {OPERATIONAL_INFO_SPEED_IB_FDR, SPEED_IB_FDR},
  {OPERATIONAL_INFO_SPEED_IB_EDR, SPEED_IB_EDR},
  {OPERATIONAL_INFO_SPEED_IB_HDR, SPEED_IB_HDR},
  {OPERATIONAL_INFO_SPEED_IB_NDR, SPEED_IB_NDR},
  {OPERATIONAL_INFO_SPEED_IB_XDR, SPEED_IB_XDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_SDR, SPEED_NVLINK_SDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_DDR, SPEED_NVLINK_DDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_QDR, SPEED_NVLINK_QDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_FDR10, SPEED_NVLINK_FDR10},
  {OPERATIONAL_INFO_SPEED_NVLINK_FDR, SPEED_NVLINK_FDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_EDR, SPEED_NVLINK_EDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_HDR, SPEED_NVLINK_HDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_NDR, SPEED_NVLINK_NDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_XDR, SPEED_NVLINK_XDR},
  {OPERATIONAL_INFO_SPEED_NVLINK_400G_2X_MODE_B, SPEED_NVLINK_400G_2X_MODE_B},
  {OPERATIONAL_INFO_SPEED_NVLINK_360G_2X_MODE_B, SPEED_NVLINK_360G_2X_MODE_B},
  {OPERATIONAL_INFO_SPEED_NVLINK_328G_2X_MODE_B, SPEED_NVLINK_328G_2X_MODE_B},
  {OPERATIONAL_INFO_SPEED_NVLINK_378G_2X_MODE_B, SPEED_NVLINK_378G_2X_MODE_B},
  {OPERATIONAL_INFO_SPEED_NVLINK_345G_2X_MODE_B, SPEED_NVLINK_345G_2X_MODE_B},
};

const EnumName<OperationalInfoFec> FEC_NAMES[] = {
  {OPERATIONAL_INFO_FEC_NO_FEC, FEC_NO_FEC},
  {OPERATIONAL_INFO_FEC_FIRECODE_FEC, FEC_FIRECODE_FEC},
  {OPERATIONAL_INFO_FEC_STANDARD_RS_FEC_528_514, FEC_STANDARD_RS_FEC_528_514},
  {OPERATIONAL_INFO_FEC_STANDARD_LL_FEC_271_257, FEC_STANDARD_LL_FEC_271_257},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_QUAD_RS_FEC_544_514, FEC_INTERLEAVED_QUAD_RS_FEC_544_514},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_QUAD_RS_FEC_PLR_546_516, FEC_INTERLEAVED_QUAD_RS_FEC_PLR_546_516},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_STANDARD_RS_FEC_544_514, FEC_INTERLEAVED_STANDARD_RS_FEC_544_514},
  {OPERATIONAL_INFO_FEC_STANDARD_RS_FEC_544_514, FEC_STANDARD_RS_FEC_544_514},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_OCTET_RS_FEC_PLR_546_516, FEC_INTERLEAVED_OCTET_RS_FEC_PLR_546_516},
  {OPERATIONAL_INFO_FEC_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_272_258, FEC_LL_50G_RS_FEC_272_258},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_272_258, FEC_INTERLEAVED_LL_50G_RS_FEC_272_258},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_STANDARD_RS_FEC_PLR_544_514, FEC_INTERLEAVED_STANDARD_RS_FEC_PLR_544_514},
  {OPERATIONAL_INFO_FEC_RS_FEC_544_514_PLR, FEC_RS_FEC_544_514_PLR},
  {OPERATIONAL_INFO_FEC_LL_FEC_271_257_PLR, FEC_LL_FEC_271_257_PLR},
  {OPERATIONAL_INFO_FEC_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_272_258, FEC_LL_50G_RS_FEC_PLR_272_258},
  {OPERATIONAL_INFO_FEC_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_272_258, FEC_INTERLEAVED_LL_50G_RS_FEC_PLR_272_258},
};

const EnumName<OperationalInfoLoopbackMode> LOOPBACK_MODE_NAMES[] = {
  {OPERATIONAL_INFO_LOOPBACK_MODE_NO, NO_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_PHY_REMOTE, PHY_REMOTE_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_PHY_LOCAL, PHY_LOCAL_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_EXTERNAL, EXTERNAL_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_LINK_LAYER, LINK_LAYER_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_NEAR_END_ANALOG, NEAR_END_ANALOG_LOOPBACK},
  {OPERATIONAL_INFO_LOOPBACK_MODE_NEAR_END_DIGITAL, NEAR_END_DIGITAL_LOOPBACK},
};

const EnumName<OperationalInfoAutoNegotiation> AUTO_NEGOTIATION_NAMES[] = {
  {OPERATIONAL_INFO_AUTO_NEGOTIATION_ENABLE, AUTO_NEGOTIATION_ON},
  {OPERATIONAL_INFO_AUTO_NEGOTIATION_FORCE, AUTO_NEGOTIATION_FORCE},
};

template<typename EnumType, size_t N>
std::string lookupEnum(const EnumName<EnumType> (&table)[N], EnumType value)
{
    for (size_t i = 0; i < N; i++)
    {
        if (table[i].value == value)
        {
            return table[i].name;
        }
    }
    return "Unknown(" + std::to_string(static_cast<int>(value)) + ")";
}

} // anonymous namespace

// Operational info fields
static const FieldDescriptor opInfoFields[NUM_OP_INFO_FIELDS] = {
  {TELEMETRY_OP_INFO_STATE, FIELD_STATE, offsetof(MstTelemetryOperationalInfo, state), 0},
  {TELEMETRY_OP_INFO_PHYSICAL_STATE, FIELD_PHYSICAL_STATE, offsetof(MstTelemetryOperationalInfo, physicalState), 0},
  {TELEMETRY_OP_INFO_SPEED, FIELD_SPEED, offsetof(MstTelemetryOperationalInfo, speed), 0},
  {TELEMETRY_OP_INFO_WIDTH, FIELD_WIDTH, offsetof(MstTelemetryOperationalInfo, width), 9},
  {TELEMETRY_OP_INFO_FEC, FIELD_FEC, offsetof(MstTelemetryOperationalInfo, fec), 0},
  {TELEMETRY_OP_INFO_LOOPBACK_MODE, FIELD_LOOPBACK_MODE, offsetof(MstTelemetryOperationalInfo, loopbackMode), 0},
  {TELEMETRY_OP_INFO_AUTO_NEGOTIATION, FIELD_AUTO_NEGOTIATION, offsetof(MstTelemetryOperationalInfo, autoNegotiation),
   0},
};

// Counter fields — order matches mlxlink --show_counters output
static const FieldDescriptor counterFields[NUM_COUNTER_FIELDS] = {
  {TELEMETRY_COUNTERS_INFO_TIME_SINCE_LAST_CLEAR, FIELD_TIME_SINCE_LAST_CLEAR,
   offsetof(MstCountersInfo, timeSinceLastClear), 2},
  {TELEMETRY_COUNTERS_INFO_SYMBOL_ERRORS, FIELD_SYMBOL_ERRORS, offsetof(MstCountersInfo, symbolErrors), 3},
  {TELEMETRY_COUNTERS_INFO_SYMBOL_BER, FIELD_SYMBOL_BER, offsetof(MstCountersInfo, symbolBER), 4},
  {TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_ERRORS, FIELD_EFFECTIVE_PHYSICAL_ERRORS,
   offsetof(MstCountersInfo, effectivePhysicalErrors), 3},
  {TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_BER, FIELD_EFFECTIVE_PHYSICAL_BER,
   offsetof(MstCountersInfo, effectivePhysicalBER), 4},
  {TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_ERRORS_PER_LANE, FIELD_RAW_PHYSICAL_ERRORS_PER_LANE, 0, 5},
  {TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER_PER_LANE, FIELD_RAW_PHYSICAL_BER_PER_LANE, 0, 10},
  {TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER, FIELD_RAW_PHYSICAL_BER, offsetof(MstCountersInfo, rawPhysicalBER), 4},
  {TELEMETRY_COUNTERS_INFO_LINK_DOWN_COUNTER, FIELD_LINK_DOWN_COUNTER, offsetof(MstCountersInfo, linkDownCounter), 3},
  {TELEMETRY_COUNTERS_INFO_LINK_ERROR_RECOVERY_COUNTER, FIELD_LINK_ERROR_RECOVERY_COUNTER,
   offsetof(MstCountersInfo, linkErrorRecoveryCounter), 3},
};

// DDM scalar fields (fieldType: 6=temperature, 7=voltage)
static const FieldDescriptor ddmFields[NUM_DDM_FIELDS] = {
  {TELEMETRY_CABLE_DDM_INFO_TEMPERATURE, DDM_FIELD_TEMPERATURE, offsetof(MstCableDDMInfo, temperature), 6},
  {TELEMETRY_CABLE_DDM_INFO_VOLTAGE, DDM_FIELD_VOLTAGE, offsetof(MstCableDDMInfo, voltage), 7},
};

extern "C"
{
    const FieldDescriptor* getOpInfoFields(void)
    {
        return opInfoFields;
    }
    const FieldDescriptor* getCounterFields(void)
    {
        return counterFields;
    }
    const FieldDescriptor* getDDMFields(void)
    {
        return ddmFields;
    }

    const char* fieldValueToString(const void* structPtr, const FieldDescriptor* field)
    {
        const char* base = reinterpret_cast<const char*>(structPtr);
        char buf[256];

        switch (field->fieldType)
        {
            case 0: /* op-info enum -> mlxlink display name */
            {
                int v = *reinterpret_cast<const int*>(base + field->offset);
                if (field->capabilityBit == TELEMETRY_OP_INFO_STATE)
                    g_stringBuffer = lookupEnum(STATE_NAMES, static_cast<OperationalInfoState>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_PHYSICAL_STATE)
                    g_stringBuffer = lookupEnum(PHYSICAL_STATE_NAMES, static_cast<OperationalInfoPhysicalState>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_SPEED)
                    g_stringBuffer = lookupEnum(SPEED_NAMES, static_cast<OperationalInfoSpeed>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_FEC)
                    g_stringBuffer = lookupEnum(FEC_NAMES, static_cast<OperationalInfoFec>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_LOOPBACK_MODE)
                    g_stringBuffer = lookupEnum(LOOPBACK_MODE_NAMES, static_cast<OperationalInfoLoopbackMode>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_AUTO_NEGOTIATION)
                    g_stringBuffer = lookupEnum(AUTO_NEGOTIATION_NAMES, static_cast<OperationalInfoAutoNegotiation>(v));
                else
                    g_stringBuffer = std::to_string(v);
                return g_stringBuffer.c_str();
            }
            case 1: /* uint16_t */
                g_stringBuffer = std::to_string(*reinterpret_cast<const uint16_t*>(base + field->offset));
                return g_stringBuffer.c_str();
            case 2: /* double "%.01f" */
                snprintf(buf, sizeof(buf), "%.01f", *reinterpret_cast<const double*>(base + field->offset));
                break;
            case 3: /* uint32_t */
                g_stringBuffer = std::to_string(*reinterpret_cast<const uint32_t*>(base + field->offset));
                return g_stringBuffer.c_str();
            case 4: /* ScientificNotation */
            {
                const auto* ber = reinterpret_cast<const ScientificNotation*>(base + field->offset);
                snprintf(buf, sizeof(buf), "%gE%d", ber->significand, ber->exponent);
                break;
            }
            case 5: /* per-lane errors */
            {
                const auto* info = reinterpret_cast<const MstCountersInfo*>(structPtr);
                if (!info->rawPhysicalErrorsPerLane || info->numberOfLanes == 0)
                    return NA_FIELD_VALUE;
                g_stringBuffer.clear();
                for (uint32_t i = 0; i < info->numberOfLanes; i++)
                {
                    if (i > 0)
                        g_stringBuffer += ",";
                    g_stringBuffer += std::to_string(info->rawPhysicalErrorsPerLane[i].errorsPerLane);
                }
                return g_stringBuffer.c_str();
            }
            case 6: /* temperature "%dC" */
                g_stringBuffer = std::to_string((int)*reinterpret_cast<const int16_t*>(base + field->offset)) + "C";
                return g_stringBuffer.c_str();
            case 7: /* voltage "%.4fV" */
                snprintf(buf, sizeof(buf), "%.4fV", *reinterpret_cast<const double*>(base + field->offset));
                break;
            case 8: /* uint32_t as hex */
                snprintf(buf, sizeof(buf), "0x%x", *reinterpret_cast<const uint32_t*>(base + field->offset));
                break;
            case 9: /* uint8_t */
                g_stringBuffer = std::to_string(*reinterpret_cast<const uint8_t*>(base + field->offset));
                return g_stringBuffer.c_str();
            case 10: /* per-lane ScientificNotation (comma-joined, mlxlink format) */
            {
                const auto* info = reinterpret_cast<const MstCountersInfo*>(structPtr);
                if (info->numberOfLanes == 0)
                    return NA_FIELD_VALUE;
                g_stringBuffer.clear();
                for (uint32_t i = 0; i < info->numberOfLanes; i++)
                {
                    if (i > 0)
                        g_stringBuffer += ",";
                    snprintf(buf, sizeof(buf), "%gE%d", info->rawPhysicalBERPerLane[i].significand,
                             info->rawPhysicalBERPerLane[i].exponent);
                    g_stringBuffer += buf;
                }
                return g_stringBuffer.c_str();
            }
            default:
                return "?";
        }
        g_stringBuffer = buf;
        return g_stringBuffer.c_str();
    }

    const char* fieldValueToHexString(uint32_t value)
    {
        FieldDescriptor fd = {0, "", 0, FIELD_TYPE_HEX_U32};
        return fieldValueToString(&value, &fd);
    }

    const char* accessTypeToString(MstPrmAccessType accessType)
    {
        switch (accessType)
        {
            case MST_PRM_ACCESS_RO:
                return "RO";
            case MST_PRM_ACCESS_WO:
                return "WO";
            case MST_PRM_ACCESS_RW:
                return "RW";
            case MST_PRM_ACCESS_INDEX:
                return "INDEX";
            case MST_PRM_ACCESS_OP:
                return "OP";
            default:
                return "UNKNOWN";
        }
    }

    const char* histogramBinRangeToString(uint32_t minRange, uint32_t maxRange)
    {
        if (minRange == maxRange)
            g_stringBuffer = "[" + std::to_string(minRange) + "]";
        else
            g_stringBuffer = "[" + std::to_string(minRange) + ":" + std::to_string(maxRange) + "]";
        return g_stringBuffer.c_str();
    }

} /* extern "C" */

#ifndef MFT_SDK_SO_UNIFIED
std::string g_devicePci = "";
std::string g_port = "";
#endif

void parseDevicePciArg(int argc, char** argv)
{
    for (int i = 1; i < argc - 1; i++)
    {
        if (std::string(argv[i]) == "-d")
        {
            g_devicePci = argv[i + 1];
            if (g_devicePci.find(':') != std::string::npos && g_devicePci.substr(0, 5) != "0000:")
            {
                g_devicePci = "0000:" + g_devicePci;
            }
        }
        else if (std::string(argv[i]) == "-p")
        {
            g_port = argv[i + 1];
        }
    }
}
