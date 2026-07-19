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
#include <map>
#include <sys/types.h>

#include "mlxlink/modules/mlxlink_maps.h"

namespace
{

thread_local std::string g_stringBuffer;

template<typename EnumType>
std::string lookupEnum(const std::map<std::string, EnumType>& map, EnumType value)
{
    for (const auto& pair : map)
    {
        if (pair.second == value)
        {
            return pair.first;
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
            case 0: /* op-info enum → MlxlinkMaps lookup */
            {
                MlxlinkMaps* maps = MlxlinkMaps::getInstance();
                int v = *reinterpret_cast<const int*>(base + field->offset);
                if (field->capabilityBit == TELEMETRY_OP_INFO_STATE)
                    g_stringBuffer = lookupEnum(maps->_operationalInfoState, static_cast<OperationalInfoState>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_PHYSICAL_STATE)
                    g_stringBuffer =
                      lookupEnum(maps->_operationalInfoPhysicalState, static_cast<OperationalInfoPhysicalState>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_SPEED)
                    g_stringBuffer = lookupEnum(maps->_operationalInfoSpeed, static_cast<OperationalInfoSpeed>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_FEC)
                    g_stringBuffer = lookupEnum(maps->_operationalInfoFec, static_cast<OperationalInfoFec>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_LOOPBACK_MODE)
                    g_stringBuffer =
                      lookupEnum(maps->_operationalInfoLoopbackMode, static_cast<OperationalInfoLoopbackMode>(v));
                else if (field->capabilityBit == TELEMETRY_OP_INFO_AUTO_NEGOTIATION)
                    g_stringBuffer =
                      lookupEnum(maps->_operationalInfoAutoNegotiation, static_cast<OperationalInfoAutoNegotiation>(v));
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
