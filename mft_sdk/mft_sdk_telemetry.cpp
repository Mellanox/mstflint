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

#include <string.h>
#include <limits>
#include <sstream>
#include <string>
#include "json/json.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mft_sdk/mft_sdk_telemetry.h"
#include "mft_sdk/mft_sdk_query.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "mlxlink/modules/printutil/mlxlink_record.h"

// Macro to set a capability bit in a capability mask
#define MST_QUERY_SET_BIT(mask, bit) ((mask) |= (bit))

static void mstQuerySetBit(mstQueryHeader& header, uint8_t bitIndex)
{
    if (bitIndex < MASK_SIZE)
    {
        MST_QUERY_SET_BIT(header.valid_fields_mask, (1ULL << bitIndex));
    }
    else
    {
        MST_QUERY_SET_BIT(header.extended_valid_fields_mask, (1ULL << (bitIndex - MASK_SIZE)));
    }
}

using mft_core::MftGeneralException;

static std::uint32_t parseUint32FromString(const std::string& value)
{
    try
    {
        unsigned long result = std::stoul(value);
        if (result > std::numeric_limits<uint32_t>::max())
        {
            throw MftGeneralException("Value is too large to convert to uint32_t");
        }
        return static_cast<uint32_t>(result);
    }
    catch (...)
    {
        throw MftGeneralException("Invalid value for numerical conversion: " + value);
    }
}

static std::uint16_t parseUint16FromString(const std::string& value)
{
    try
    {
        unsigned long result = std::stoul(value);
        if (result > std::numeric_limits<uint16_t>::max())
        {
            throw MftGeneralException("Value is too large to convert to uint16_t");
        }
        return static_cast<uint16_t>(result);
    }
    catch (...)
    {
        throw MftGeneralException("Invalid value for numerical conversion: " + value);
    }
}

static std::uint8_t parseUint8FromString(const std::string& value)
{
    try
    {
        unsigned long result = std::stoul(value);
        if (result > std::numeric_limits<uint8_t>::max())
        {
            throw MftGeneralException("Value is too large to convert to uint8_t");
        }
        return static_cast<uint8_t>(result);
    }
    catch (...)
    {
        throw MftGeneralException("Invalid value for numerical conversion: " + value);
    }
}

static float parseFloatFromString(const std::string& value)
{
    try
    {
        return std::stof(value);
    }
    catch (...)
    {
        throw MftGeneralException("Invalid value for float conversion: " + value);
    }
}

static std::string joinJsonArray(const Json::Value& arr)
{
    if (!arr.isArray() || arr.empty())
    {
        return NA_FIELD_VALUE;
    }
    std::string result;
    for (Json::ArrayIndex i = 0; i < arr.size(); i++)
    {
        if (i > 0)
        {
            result += ',';
        }
        result += arr[i].asString();
    }
    return result;
}

void MftSdk::initMlxLinkSdkPortInfo()
{
    _mstMlxLinkSdkInstance->updatePortInfo();
    _mstMlxLinkSdkInstance->showPddr();
}

void MftSdk::initMlxLinkSdkUserInput(MlxLinkInitMode initMode)
{
    if (initMode == MlxLinkInitMode::CABLE_DDM)
    {
        _mstMlxLinkSdkInstance->_userInput._cable = true;
        _mstMlxLinkSdkInstance->_userInput._ddm = true;
        _mstMlxLinkSdkInstance->_userInput._uniqueCableCmds++;
    }
    else if (initMode == MlxLinkInitMode::MODULE_INFO)
    {
        _mstMlxLinkSdkInstance->_userInput._showModule = true;
        _mstMlxLinkSdkInstance->_userInput._networkCmds++;
    }
}

MstStatus MftSdk::initMlxLinkSdk(MlxLinkInitMode initMode)
{
    clearError();
    try
    {
        if (_mstMlxLinkSdkInstance == nullptr)
        {
            _mstMlxLinkSdkInstance = std::unique_ptr<MlxlinkCommander>(new MlxlinkCommander(_deviceIdentifier));
            _mstMlxLinkSdkInstance->setSilentMode();
            _mfiles.push_back(_mstMlxLinkSdkInstance->_mf);
        }

        if (!mlxlinkSdkInitialized[initMode])
        {
            initMlxLinkSdkUserInput(initMode);
            initMlxLinkSdkPortInfo();
            mlxlinkSdkInitialized[initMode] = true;
        }
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
        return _lastError.status;
    }
    return MST_SUCCESS;
}

std::string MftSdk::getJsonStringValue(const Json::Value& jsonValue, const std::string& fieldName, bool isOptional)
{
    if (!jsonValue.isMember(fieldName))
    {
        if (isOptional)
        {
            return NA_FIELD_VALUE;
        }
        throw MftGeneralException("Failed to retrieve value for field: " + fieldName);
    }
    const Json::Value& val = jsonValue[fieldName];
    if (val.isObject())
    {
        if (val.isMember(JSON_VALUES_TITLE))
        {
            return joinJsonArray(val[JSON_VALUES_TITLE]);
        }
        return NA_FIELD_VALUE;
    }
    if (val.isArray())
    {
        return joinJsonArray(val);
    }
    return val.asString();
}

Json::Value MftSdk::getJsonSection(const std::string& sectionName, Json::Value& jsonRoot)
{
    Json::Value jsonSection = jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION][sectionName];
    if (jsonSection.isNull())
    {
        throw MftGeneralException("Failed to retrieve information about " + sectionName + " section");
    }
    return jsonSection;
}

Json::Value MftSdk::getOperationalInfoJsonSection()
{
    Json::Value jsonRoot;
    _mstMlxLinkSdkInstance->_operatingInfoCmd.toJsonFormat(jsonRoot);
    return getJsonSection(FIELD_OPERATIONAL_INFO, jsonRoot);
}

Json::Value MftSdk::getCountersInfoJsonSection()
{
    Json::Value jsonRoot;
    _mstMlxLinkSdkInstance->_berInfoCmd.toJsonFormat(jsonRoot);
    return getJsonSection(FIELD_PHYSICAL_COUNTERS_AND_BER_INFO, jsonRoot);
}

ScientificNotation MftSdk::parseScientificNotation(const std::string& value)
{
    ScientificNotation result = {0.0, 0};

    // Find 'E' or 'e' in the string
    size_t ePos = value.find_first_of("Ee");
    if (ePos == std::string::npos)
    {
        try
        {
            result.significand = std::stod(value);
            result.exponent = 0;
            return result;
        }
        catch (const std::exception& e)
        {
            throw MftGeneralException("Invalid scientific notation: " + value + " " + e.what());
        }
    }

    // Extract significand (part before E/e)
    std::string significandStr = value.substr(0, ePos);
    result.significand = std::stoi(significandStr);

    // Extract exponent (part after E/e)
    std::string exponentStr = value.substr(ePos + 1);
    result.exponent = std::stoi(exponentStr);

    return result;
}

template<typename MapType, typename FieldType>
void MftSdk::extractAndMapField(const Json::Value& jsonRoot,
                                const std::string& jsonFieldName,
                                const MapType& mapRef,
                                FieldType& targetField,
                                mstQueryHeader& header,
                                uint32_t bitIndex,
                                bool isOptional)
{
    std::string fieldValue = getJsonStringValue(jsonRoot, jsonFieldName, isOptional);
    if (fieldValue != NA_FIELD_VALUE)
    {
        auto it = mapRef.find(fieldValue);
        if (it == mapRef.end())
        {
            throw MftGeneralException("Invalid " + jsonFieldName + ": " + fieldValue);
        }
        targetField = it->second;
        mstQuerySetBit(header, bitIndex);
    }
}

template<typename T, typename Parser>
void MftSdk::extractAndSetNumericField(const Json::Value& json,
                                       const std::string& fieldName,
                                       T& targetField,
                                       mstQueryHeader& header,
                                       uint8_t bitIndex,
                                       Parser parser)
{
    std::string value = getJsonStringValue(json, fieldName);
    if (value != NA_FIELD_VALUE)
    {
        targetField = parser(value);
        mstQuerySetBit(header, bitIndex);
    }
}

void MftSdk::extractAndSetStringField(const Json::Value& json,
                                      const std::string& fieldName,
                                      char* targetField,
                                      size_t maxLength,
                                      mstQueryHeader& header,
                                      uint8_t bitIndex)
{
    std::string value = getJsonStringValue(json, fieldName);
    if (value != NA_FIELD_VALUE && !value.empty())
    {
        strncpy(targetField, value.c_str(), maxLength - 1);
        targetField[maxLength - 1] = '\0';
        mstQuerySetBit(header, bitIndex);
    }
}

void MftSdk::extractOperationalInfoWidth(const Json::Value& jsonSection, MstTelemetryOperationalInfo* operationalInfo)
{
    std::string fieldValue = getJsonStringValue(jsonSection, FIELD_WIDTH);
    if (fieldValue != NA_FIELD_VALUE)
    {
        try
        {
            // Remove 'x' from the field suffix if it exists
            if (fieldValue.find('x') != std::string::npos)
            {
                fieldValue = fieldValue.substr(0, fieldValue.find('x'));
            }
            operationalInfo->width = parseUint8FromString(fieldValue);
            mstQuerySetBit(operationalInfo->header, TELEMETRY_OP_INFO_WIDTH);
        }
        catch (const std::exception& e)
        {
            throw MftGeneralException("Invalid width: " + fieldValue + " " + e.what());
        }
    }
}

MstStatus MftSdk::extractOperationalInfoFromJson(MstTelemetryOperationalInfo* operationalInfo)
{
    try
    {
        Json::Value operationalInfoJson = getOperationalInfoJsonSection();

        extractAndMapField(operationalInfoJson,
                           FIELD_STATE,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoState,
                           operationalInfo->state,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_STATE);

        extractAndMapField(operationalInfoJson,
                           FIELD_PHYSICAL_STATE,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoPhysicalState,
                           operationalInfo->physicalState,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_PHYSICAL_STATE);

        extractAndMapField(operationalInfoJson,
                           FIELD_SPEED,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoSpeed,
                           operationalInfo->speed,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_SPEED);

        extractOperationalInfoWidth(operationalInfoJson, operationalInfo);

        extractAndMapField(operationalInfoJson,
                           FIELD_FEC,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoFec,
                           operationalInfo->fec,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_FEC);

        extractAndMapField(operationalInfoJson,
                           FIELD_LOOPBACK_MODE,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoLoopbackMode,
                           operationalInfo->loopbackMode,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_LOOPBACK_MODE);

        extractAndMapField(operationalInfoJson,
                           FIELD_AUTO_NEGOTIATION,
                           _mstMlxLinkSdkInstance->_mlxlinkMaps->_operationalInfoAutoNegotiation,
                           operationalInfo->autoNegotiation,
                           operationalInfo->header,
                           TELEMETRY_OP_INFO_AUTO_NEGOTIATION);
    }
    catch (const std::exception& e)
    {
        std::string errorMessage = "Failed to retrieve telemetry operational info: " + std::string(e.what());
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, errorMessage);
        return _lastError.status;
    }
    return _lastError.status;
}

MstStatus MftSdk::getTelemetryOperationalInfo(MstTelemetryOperationalInfo* operationalInfo)
{
    if (!operationalInfo || operationalInfo->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }

    if (initMlxLinkSdk(MlxLinkInitMode::OPERATIONAL_INFO) != MST_SUCCESS)
    {
        return _lastError.status;
    }

    MST_QUERY_CLEAR(operationalInfo);

    try
    {
        _mstMlxLinkSdkInstance->operatingInfoPage();
        extractOperationalInfoFromJson(operationalInfo);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
    }
    return _lastError.status;
}

MstStatus MftSdk::mlxlinkGetFecHistogram(MstFecHistogram* fecHistogram)
{
    if (!fecHistogram || fecHistogram->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }

    vector<HISTOGRAM_BIN> mlxlinkBinsList = _mstMlxLinkSdkInstance->_portInfo->getBinsList();

    uint8_t numberOfBins = static_cast<uint8_t>(mlxlinkBinsList.size());
    if (mlxlinkBinsList.size() > MAX_NUM_OF_BINS)
    {
        throw MftGeneralException("Number of bins is greater than " + std::to_string(MAX_NUM_OF_BINS));
    }
    fecHistogram->numberOfBins = numberOfBins;
    for (uint8_t i = 0; i < numberOfBins; i++)
    {
        fecHistogram->bins[i].minRange = mlxlinkBinsList[i].minRange;
        fecHistogram->bins[i].maxRange = mlxlinkBinsList[i].maxRange;
        fecHistogram->bins[i].numOfErrors = mlxlinkBinsList[i].numOfErrors;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getFecHistogram(MstFecHistogram* fecHistogram)
{
    if (!fecHistogram || fecHistogram->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }

    if (initMlxLinkSdk() != MST_SUCCESS)
    {
        return _lastError.status;
    }

    MST_QUERY_CLEAR(fecHistogram);

    try
    {
        _mstMlxLinkSdkInstance->_userInput.enableFecHistogram = true;
        _mstMlxLinkSdkInstance->_userInput.showFecHistogram = true;
        _mstMlxLinkSdkInstance->initPortInfo();
        if (_mstMlxLinkSdkInstance->errorObserved())
        {
            throw MftGeneralException(_mstMlxLinkSdkInstance->getAllUnhandledErrors());
        }
        mlxlinkGetFecHistogram(fecHistogram);
    }

    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
    }
    return _lastError.status;
}

void MftSdk::extractRawPhysicalBERPerLane(const Json::Value& jsonSection, MstCountersInfo* countersInfo)
{
    if (_mstMlxLinkSdkInstance->isRawPhysicalBERPerLaneSupported() && !_mstMlxLinkSdkInstance->isEDRProduct())
    {
        std::string fieldValue = getJsonStringValue(jsonSection, FIELD_RAW_PHYSICAL_BER_PER_LANE);
        if (fieldValue != NA_FIELD_VALUE)
        {
            std::vector<std::string> rawPhysicalBERPerLane = split(fieldValue, ',');
            if (!rawPhysicalBERPerLane.empty())
            {
                unsigned int numberOfLanes = rawPhysicalBERPerLane.size();
                if (numberOfLanes > MAX_NUM_OF_LANES)
                {
                    throw MftGeneralException("Number of lanes is greater than " + std::to_string(MAX_NUM_OF_LANES));
                }
                countersInfo->numberOfLanes = numberOfLanes;
                for (unsigned int i = 0; i < numberOfLanes; i++)
                {
                    countersInfo->rawPhysicalBERPerLane[i] = parseScientificNotation(rawPhysicalBERPerLane[i]);
                }
            }
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER_PER_LANE);
        }
    }
}

void MftSdk::extractRawPhysicalErrorsPerLane(const Json::Value& jsonSection, MstCountersInfo* countersInfo)
{
    std::string fieldValue = getJsonStringValue(jsonSection, FIELD_RAW_PHYSICAL_ERRORS_PER_LANE);
    if (fieldValue != NA_FIELD_VALUE)
    {
        std::vector<std::string> rawPhysicalErrorsPerLane = split(fieldValue, ',');
        if (!rawPhysicalErrorsPerLane.empty())
        {
            unsigned int numberOfLanes = rawPhysicalErrorsPerLane.size();
            if (numberOfLanes > MAX_NUM_OF_LANES)
            {
                throw MftGeneralException("Number of lanes is greater than " + std::to_string(MAX_NUM_OF_LANES));
            }
            countersInfo->numberOfLanes = numberOfLanes;
            for (unsigned int i = 0; i < numberOfLanes; i++)
            {
                countersInfo->rawPhysicalErrorsPerLane[i].errorsPerLane = std::stoul(rawPhysicalErrorsPerLane[i]);
            }
        }
        mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_ERRORS_PER_LANE);
    }
}

void MftSdk::extractLinkCounters(const Json::Value& jsonSection, MstCountersInfo* countersInfo)
{
    if (_mstMlxLinkSdkInstance->isProtocolActiveETH() || _mstMlxLinkSdkInstance->isProtocolActiveIB())
    {
        std::string fieldValue = getJsonStringValue(jsonSection, FIELD_LINK_DOWN_COUNTER);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_LINK_DOWN_COUNTER);
            countersInfo->linkDownCounter = std::stoul(fieldValue);
        }
        fieldValue = getJsonStringValue(jsonSection, FIELD_LINK_ERROR_RECOVERY_COUNTER);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_LINK_ERROR_RECOVERY_COUNTER);
            countersInfo->linkErrorRecoveryCounter = std::stoul(fieldValue);
        }
    }
}

void MftSdk::extractSymbolCounters(const Json::Value& jsonSection, MstCountersInfo* countersInfo)
{
    if (_mstMlxLinkSdkInstance->isProtocolActiveIB() && !_mstMlxLinkSdkInstance->isEDRProduct())
    {
        std::string fieldValue = getJsonStringValue(jsonSection, FIELD_SYMBOL_ERRORS);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_SYMBOL_ERRORS);
            countersInfo->symbolErrors = std::stoul(fieldValue);
        }
        fieldValue = getJsonStringValue(jsonSection, FIELD_SYMBOL_BER);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_SYMBOL_BER);
            countersInfo->symbolBER = parseScientificNotation(fieldValue);
        }
    }
}

MstStatus MftSdk::extractCountersInfoFromJson(MstCountersInfo* countersInfo)
{
    try
    {
        Json::Value countersInfoJson = getCountersInfoJsonSection();
        std::string fieldValue = getJsonStringValue(countersInfoJson, FIELD_TIME_SINCE_LAST_CLEAR);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_TIME_SINCE_LAST_CLEAR);
            countersInfo->timeSinceLastClear = std::stod(fieldValue);
        }
        extractSymbolCounters(countersInfoJson, countersInfo);
        fieldValue = getJsonStringValue(countersInfoJson, FIELD_EFFECTIVE_PHYSICAL_ERRORS);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_ERRORS);
            countersInfo->effectivePhysicalErrors = std::stoul(fieldValue);
        }
        fieldValue = getJsonStringValue(countersInfoJson, FIELD_EFFECTIVE_PHYSICAL_BER);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_EFFECTIVE_PHYSICAL_BER);
            countersInfo->effectivePhysicalBER = parseScientificNotation(fieldValue);
        }
        extractRawPhysicalErrorsPerLane(countersInfoJson, countersInfo);
        extractRawPhysicalBERPerLane(countersInfoJson, countersInfo);
        fieldValue = getJsonStringValue(countersInfoJson, FIELD_RAW_PHYSICAL_BER);
        if (fieldValue != NA_FIELD_VALUE)
        {
            mstQuerySetBit(countersInfo->header, TELEMETRY_COUNTERS_INFO_RAW_PHYSICAL_BER);
            countersInfo->rawPhysicalBER = parseScientificNotation(fieldValue);
        }
        extractLinkCounters(countersInfoJson, countersInfo);
    }
    catch (const std::exception& e)
    {
        std::string errorMessage = "Failed to retrieve counters info: " + std::string(e.what());
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, errorMessage);
        return _lastError.status;
    }
    return _lastError.status;
}

MstStatus MftSdk::getCountersInfo(MstCountersInfo* countersInfo)
{
    if (!countersInfo || countersInfo->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    if (initMlxLinkSdk() != MST_SUCCESS)
    {
        return _lastError.status;
    }

    MST_QUERY_CLEAR(countersInfo);

    try
    {
        _mstMlxLinkSdkInstance->showBer();
        extractCountersInfoFromJson(countersInfo);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
    }
    return _lastError.status;
}

// Extract module-level DDM flags (Temperature and Voltage)
void MftSdk::extractModuleDDMFlags(cable_ddm_q_t& cableDDMoutput, MstCableDDMInfo* cableDDMInfo)
{
    cableDDMInfo->temperature.alarmFlags.highAlarm = cableDDMoutput.temperature.high_alarm_flag;
    cableDDMInfo->temperature.alarmFlags.lowAlarm = cableDDMoutput.temperature.low_alarm_flag;
    cableDDMInfo->temperature.alarmFlags.highWarning = cableDDMoutput.temperature.high_warn_flag;
    cableDDMInfo->temperature.alarmFlags.lowWarning = cableDDMoutput.temperature.low_warn_flag;
    cableDDMInfo->voltage.alarmFlags.highAlarm = cableDDMoutput.voltage.high_alarm_flag;
    cableDDMInfo->voltage.alarmFlags.lowAlarm = cableDDMoutput.voltage.low_alarm_flag;
    cableDDMInfo->voltage.alarmFlags.highWarning = cableDDMoutput.voltage.high_warn_flag;
    cableDDMInfo->voltage.alarmFlags.lowWarning = cableDDMoutput.voltage.low_warn_flag;
}

// Extract channel-level DDM flags (RX Power, TX Power, TX Bias)
void MftSdk::extractChannelDDMFlags(ddm_threshold_t& rxPower,
                                    ddm_threshold_t& txPower,
                                    ddm_threshold_t& txBias,
                                    MstCableDDMAlarmFlags& rxChannelFlags,
                                    MstCableDDMAlarmFlags& txChannelFlags,
                                    MstCableDDMAlarmFlags& txBiasChannelFlags)
{
    rxChannelFlags.highAlarm = rxPower.high_alarm_flag;
    rxChannelFlags.lowAlarm = rxPower.low_alarm_flag;
    rxChannelFlags.highWarning = rxPower.high_warn_flag;
    rxChannelFlags.lowWarning = rxPower.low_warn_flag;
    txChannelFlags.highAlarm = txPower.high_alarm_flag;
    txChannelFlags.lowAlarm = txPower.low_alarm_flag;
    txChannelFlags.highWarning = txPower.high_warn_flag;
    txChannelFlags.lowWarning = txPower.low_warn_flag;
    txBiasChannelFlags.highAlarm = txBias.high_alarm_flag;
    txBiasChannelFlags.lowAlarm = txBias.low_alarm_flag;
    txBiasChannelFlags.highWarning = txBias.high_warn_flag;
    txBiasChannelFlags.lowWarning = txBias.low_warn_flag;
}

// Validate and extract all threshold types
void MftSdk::ExtractThresholds(cable_ddm_q_t& cableDDMoutput, float txBiasMultiplier, MstCableDDMInfo* cableDDMInfo)
{
    cableDDMInfo->temperature.thresholds.highAlarm = (int8_t)(cableDDMoutput.temperature.high_alarm >> 8);
    cableDDMInfo->temperature.thresholds.lowAlarm = (int8_t)(cableDDMoutput.temperature.low_alarm >> 8);
    cableDDMInfo->temperature.thresholds.highWarning = (int8_t)(cableDDMoutput.temperature.high_warn >> 8);
    cableDDMInfo->temperature.thresholds.lowWarning = (int8_t)(cableDDMoutput.temperature.low_warn >> 8);
    cableDDMInfo->voltage.thresholds.highAlarm = (double)cableDDMoutput.voltage.high_alarm / 10000;
    cableDDMInfo->voltage.thresholds.lowAlarm = (double)cableDDMoutput.voltage.low_alarm / 10000;
    cableDDMInfo->voltage.thresholds.highWarning = (double)cableDDMoutput.voltage.high_warn / 10000;
    cableDDMInfo->voltage.thresholds.lowWarning = (double)cableDDMoutput.voltage.low_warn / 10000;
    cableDDMInfo->rxPower.thresholds.highAlarm = mw_to_dbm((double)cableDDMoutput.rx_power[0].high_alarm / 10000);
    cableDDMInfo->rxPower.thresholds.lowAlarm = mw_to_dbm((double)cableDDMoutput.rx_power[0].low_alarm / 10000);
    cableDDMInfo->rxPower.thresholds.highWarning = mw_to_dbm((double)cableDDMoutput.rx_power[0].high_warn / 10000);
    cableDDMInfo->rxPower.thresholds.lowWarning = mw_to_dbm((double)cableDDMoutput.rx_power[0].low_warn / 10000);
    cableDDMInfo->txPower.thresholds.highAlarm = mw_to_dbm((double)cableDDMoutput.tx_power[0].high_alarm / 10000);
    cableDDMInfo->txPower.thresholds.lowAlarm = mw_to_dbm((double)cableDDMoutput.tx_power[0].low_alarm / 10000);
    cableDDMInfo->txPower.thresholds.highWarning = mw_to_dbm((double)cableDDMoutput.tx_power[0].high_warn / 10000);
    cableDDMInfo->txPower.thresholds.lowWarning = mw_to_dbm((double)cableDDMoutput.tx_power[0].low_warn / 10000);
    cableDDMInfo->txBias.thresholds.highAlarm = ((double)cableDDMoutput.tx_bias[0].high_alarm * txBiasMultiplier) / 500;
    cableDDMInfo->txBias.thresholds.lowAlarm = ((double)cableDDMoutput.tx_bias[0].low_alarm * txBiasMultiplier) / 500;
    cableDDMInfo->txBias.thresholds.highWarning =
      ((double)cableDDMoutput.tx_bias[0].high_warn * txBiasMultiplier) / 500;
    cableDDMInfo->txBias.thresholds.lowWarning = ((double)cableDDMoutput.tx_bias[0].low_warn * txBiasMultiplier) / 500;
}

MstStatus MftSdk::extractCableDDMInfoFrom(MstCableDDMInfo* cableDDMInfo)
{
    try
    {
        if (!_mstMlxLinkSdkInstance->_cablesCommander)
        {
            throw MftGeneralException("Cables commander not initialized");
        }
        auto& cableDDMOutput = _mstMlxLinkSdkInstance->_cablesCommander->getCableDDMInfo();
        float txBiasMultiplier = _mstMlxLinkSdkInstance->_cablesCommander->getTxBiasMultiplier();
        cableDDMInfo->temperature.value = cableDDMOutput.temperature.val;
        cableDDMInfo->voltage.value = cableDDMOutput.voltage.val;
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_TEMPERATURE);
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_VOLTAGE);
        // Process DDM Flags section
        extractModuleDDMFlags(cableDDMOutput, cableDDMInfo);
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_FLAGS);
        // Process DDM Thresholds section
        ExtractThresholds(cableDDMOutput, txBiasMultiplier, cableDDMInfo);
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_THRESHOLDS);

        cableDDMInfo->numberOfChannels = cableDDMOutput.channels;
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_NUMBER_OF_CHANNELS);

        if (cableDDMInfo->numberOfChannels > MAX_NUM_OF_CHANNELS)
        {
            throw MftGeneralException("Number of channels is greater than " + std::to_string(MAX_NUM_OF_CHANNELS));
        }
        for (uint32_t i = 0; i < cableDDMInfo->numberOfChannels; i++)
        {
            extractChannelDDMFlags(cableDDMOutput.rx_power[i],
                                   cableDDMOutput.tx_power[i],
                                   cableDDMOutput.tx_bias[i],
                                   cableDDMInfo->rxPower.alarmFlags[i],
                                   cableDDMInfo->txPower.alarmFlags[i],
                                   cableDDMInfo->txBias.alarmFlags[i]);
            cableDDMInfo->rxPower.value[i] = cableDDMOutput.rx_power[i].val;
            cableDDMInfo->txPower.value[i] = cableDDMOutput.tx_power[i].val;
            cableDDMInfo->txBias.value[i] = cableDDMOutput.tx_bias[i].val;
        }
        mstQuerySetBit(cableDDMInfo->header, TELEMETRY_CABLE_DDM_INFO_CHANNELS);
    }
    catch (const std::exception& e)
    {
        std::string errorMessage = "Failed to retrieve cable DDM info: " + std::string(e.what());
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, errorMessage);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getCableDDMInfo(MstCableDDMInfo* cableDDMInfo)
{
    if (!cableDDMInfo || cableDDMInfo->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    if (initMlxLinkSdk(MlxLinkInitMode::CABLE_DDM) != MST_SUCCESS)
    {
        return _lastError.status;
    }

    MST_QUERY_CLEAR(cableDDMInfo);

    try
    {
        _mstMlxLinkSdkInstance->showCableDDM();
        extractCableDDMInfoFrom(cableDDMInfo);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
    }
    return _lastError.status;
}

Json::Value MftSdk::getModuleInfoJsonSection()
{
    Json::Value jsonRoot;
    _mstMlxLinkSdkInstance->_moduleInfoCmd.toJsonFormat(jsonRoot);
    return getJsonSection(FIELD_MODULE_INFO, jsonRoot);
}

void MftSdk::setVendorInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    extractAndMapField(moduleInfoJson,
                       FIELD_IDENTIFIER,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_identifierSdk,
                       moduleInfo->vendorInfo.identifier,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_IDENTIFIER);
    extractAndSetStringField(moduleInfoJson, FIELD_COMPLIANCE, moduleInfo->vendorInfo.compliance,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_COMPLIANCE);
    extractAndMapField(moduleInfoJson,
                       FIELD_CABLE_TECHNOLOGY,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_cableTechnologySdk,
                       moduleInfo->vendorInfo.cableTechnology,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_CABLE_TECHNOLOGY);
    extractAndMapField(moduleInfoJson,
                       FIELD_CABLE_TYPE,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_cableTypeSdk,
                       moduleInfo->vendorInfo.cableType,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_CABLE_TYPE);
    extractAndMapField(moduleInfoJson,
                       FIELD_OUI,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_ouiSdk,
                       moduleInfo->vendorInfo.oui,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_OUI);
    extractAndSetStringField(moduleInfoJson, FIELD_VENDOR_NAME, moduleInfo->vendorInfo.vendorName,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_VENDOR_NAME);
    extractAndSetStringField(moduleInfoJson, FIELD_VENDOR_PART_NUMBER, moduleInfo->vendorInfo.vendorPartNumber,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_VENDOR_PART_NUMBER);
    extractAndSetStringField(moduleInfoJson, FIELD_VENDOR_SERIAL_NUMBER, moduleInfo->vendorInfo.vendorSerialNumber,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_VENDOR_SERIAL_NUMBER);
    extractAndSetStringField(moduleInfoJson, FIELD_VENDOR_REVISION, moduleInfo->vendorInfo.vendorRevision,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_VENDOR_REVISION);
    extractAndSetNumericField(moduleInfoJson, FIELD_WAVELENGTH, moduleInfo->vendorInfo.wavelength, moduleInfo->header,
                              TELEMETRY_MODULE_INFO_WAVELENGTH, parseUint32FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_TRANSFER_DISTANCE, moduleInfo->vendorInfo.transferDistance,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_TRANSFER_DISTANCE, parseFloatFromString);
}

void MftSdk::setFwVersionFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    string fwVersion = getJsonStringValue(moduleInfoJson, FIELD_FW_VERSION);
    if (fwVersion != NA_FIELD_VALUE)
    {
        // split the fwVersion by '.' and set the chipId, major, minor
        std::vector<std::string> fwVersionParts = split(fwVersion, '.');
        if (fwVersionParts.size() == 3)
        {
            moduleInfo->fwVersion.chipId = std::stoi(fwVersionParts[0]);
            moduleInfo->fwVersion.major = std::stoi(fwVersionParts[1]);
            moduleInfo->fwVersion.minor = std::stoi(fwVersionParts[2]);
            mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_FW_VERSION);
        }
    }
}

void MftSdk::setPowerAndCdrInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    moduleInfo->powerAndCdrInfo.digitalDiagnosticMonitoring =
      getJsonStringValue(moduleInfoJson, FIELD_DIGITAL_DIAGNOSTIC_MONITORING) == "Yes";
    mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_DIGITAL_DIAGNOSTIC_MONITORING);
    extractAndSetStringField(moduleInfoJson, FIELD_POWER_CLASS, moduleInfo->powerAndCdrInfo.powerClass,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_POWER_CLASS);
    extractAndSetStringField(moduleInfoJson, FIELD_MAX_POWER, moduleInfo->powerAndCdrInfo.maxPower,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_MAX_POWER);
    parseCdrLanesData(getJsonStringValue(moduleInfoJson, FIELD_CDR_RX), moduleInfo->powerAndCdrInfo.cdrRx,
                      moduleInfo->header, TELEMETRY_MODULE_INFO_CDR_RX);
    parseCdrLanesData(getJsonStringValue(moduleInfoJson, FIELD_CDR_TX), moduleInfo->powerAndCdrInfo.cdrTx,
                      moduleInfo->header, TELEMETRY_MODULE_INFO_CDR_TX);
}

void MftSdk::setLatencyInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    extractAndSetNumericField(moduleInfoJson, FIELD_INTRA_ASIC_LATENCY, moduleInfo->latencyInfo.intraAsicLatency,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_INTRA_ASIC_LATENCY, parseUint16FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_MODULE_DATAPATH_LATENCY,
                              moduleInfo->latencyInfo.moduleDatapathLatency, moduleInfo->header,
                              TELEMETRY_MODULE_INFO_MODULE_DATAPATH_LATENCY, parseUint16FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_ROUND_TRIP_LATENCY, moduleInfo->latencyInfo.roundTripLatency,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_ROUND_TRIP_LATENCY, parseFloatFromString);
}

bool MftSdk::parseSnrLanesFromString(const std::string& fieldValue, float* lanes)
{
    if (fieldValue == NA_FIELD_VALUE || fieldValue.empty())
    {
        return false;
    }
    bool hasValidLane = false;
    std::vector<std::string> parts = split(fieldValue, ',');
    for (size_t i = 0; i < parts.size() && i < MAX_NUM_OF_LANES; i++)
    {
        const std::string& part = parts[i];
        if (part.empty() || part == NA_FIELD_VALUE)
        {
            lanes[i] = 0.0f;
        }
        else
        {
            try
            {
                lanes[i] = std::stof(part);
                hasValidLane = true;
            }
            catch (...)
            {
                lanes[i] = 0.0f;
            }
        }
    }
    return hasValidLane;
}

void MftSdk::parseCdrLanesData(const std::string& fieldValue, uint8_t* lanes, mstQueryHeader& header, uint8_t bitIndex)
{
    if (fieldValue == NA_FIELD_VALUE || fieldValue.empty())
    {
        return;
    }
    std::vector<std::string> parts = split(fieldValue, ',');
    for (size_t i = 0; i < parts.size() && i < MAX_NUM_OF_LANES; i++)
    {
        const std::string& trimmed = parts[i];
        if (trimmed == "ON")
        {
            lanes[i] = 1;
        }
        else
        {
            lanes[i] = 0;
        }
    }
    mstQuerySetBit(header, bitIndex);
}

void MftSdk::parseLanesDataAsUint8(const std::string& fieldValue,
                                   uint8_t* lanes,
                                   mstQueryHeader& header,
                                   uint8_t bitIndex)
{
    if (fieldValue == NA_FIELD_VALUE || fieldValue.empty())
    {
        return;
    }
    std::vector<std::string> parts = split(fieldValue, ',');
    for (size_t i = 0; i < parts.size() && i < MAX_NUM_OF_LANES; i++)
    {
        const std::string& part = parts[i];
        if (part.empty() || part == NA_FIELD_VALUE)
        {
            lanes[i] = 0;
        }
        else
        {
            try
            {
                lanes[i] = parseUint8FromString(part);
            }
            catch (...)
            {
                lanes[i] = 0;
            }
        }
    }
    mstQuerySetBit(header, bitIndex);
}

void MftSdk::setSnrInfoFromJson(const Json::Value& moduleInfoJson,
                                MstSnrInfo* snrInfo,
                                mstQueryHeader& header,
                                uint8_t mediaLanesBitIndex,
                                uint8_t hostLanesBitIndex)
{
    memset(snrInfo, 0, sizeof(MstSnrInfo));
    std::string mediaLanes = getJsonStringValue(moduleInfoJson, FIELD_SNR_MEDIA_LANES);
    if (mediaLanes != NA_FIELD_VALUE && !mediaLanes.empty())
    {
        if (parseSnrLanesFromString(mediaLanes, snrInfo->snrMediaLanes))
        {
            mstQuerySetBit(header, mediaLanesBitIndex);
        }
    }
    std::string hostLanes = getJsonStringValue(moduleInfoJson, FIELD_SNR_HOST_LANES);
    if (hostLanes != NA_FIELD_VALUE && !hostLanes.empty())
    {
        if (parseSnrLanesFromString(hostLanes, snrInfo->snrHostLanes))
        {
            mstQuerySetBit(header, hostLanesBitIndex);
        }
    }
}

void MftSdk::setManufacturingDateFromJson(const Json::Value& moduleInfoJson,
                                          MstDate* manufacturingDate,
                                          mstQueryHeader& header,
                                          uint8_t bitIndex)
{
    try
    {
        std::string manufacturingDateString = getJsonStringValue(moduleInfoJson, FIELD_MANUFACTURING_DATE);
        if (manufacturingDateString != NA_FIELD_VALUE)
        {
            std::vector<std::string> parts = split(manufacturingDateString, '_');
            if (parts.size() == 3)
            {
                manufacturingDate->day = parseUint8FromString(parts[0]);
                manufacturingDate->month = parseUint8FromString(parts[1]);
                manufacturingDate->year = parseUint16FromString(parts[2]);
                mstQuerySetBit(header, bitIndex);
            }
        }
    }
    catch (const std::exception& e)
    {
        throw MftGeneralException("Failed retrieving manufacturing date: " + std::string(e.what()));
    }
}

void MftSdk::setBerModuleInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    setSnrInfoFromJson(moduleInfoJson, &moduleInfo->berModuleInfo.snrInfo, moduleInfo->header,
                       TELEMETRY_MODULE_INFO_SNR_MEDIA_LANES, TELEMETRY_MODULE_INFO_SNR_HOST_LANES);
    extractAndSetStringField(moduleInfoJson, FIELD_IB_CABLE_WIDTH, moduleInfo->berModuleInfo.ibCableWidth,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_IB_CABLE_WIDTH);
    extractAndSetNumericField(moduleInfoJson, FIELD_MEMORY_MAP_REVISION, moduleInfo->berModuleInfo.memoryMapRevision,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_MEMORY_MAP_REVISION, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_LINEAR_DIRECT_DRIVE, moduleInfo->berModuleInfo.linearDirectDrive,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_LINEAR_DIRECT_DRIVE, parseUint8FromString);
    extractAndSetStringField(moduleInfoJson, FIELD_CABLE_BREAKOUT, moduleInfo->berModuleInfo.cableBreakout,
                             MODULE_INFO_MAX_LENGTH, moduleInfo->header, TELEMETRY_MODULE_INFO_CABLE_BREAKOUT);
    extractAndSetNumericField(moduleInfoJson, FIELD_SMF_LENGTH, moduleInfo->berModuleInfo.smfLength, moduleInfo->header,
                              TELEMETRY_MODULE_INFO_SMF_LENGTH, parseUint32FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_CABLE_RX_AMP, moduleInfo->berModuleInfo.cableRxAmp,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_CABLE_RX_AMP, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_CABLE_RX_EMPHASIS_PRE, moduleInfo->berModuleInfo.cableRxEmphasis,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_CABLE_RX_EMPHASIS, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_CABLE_RX_POST_EMPHASIS,
                              moduleInfo->berModuleInfo.cableRxPostEmphasis, moduleInfo->header,
                              TELEMETRY_MODULE_INFO_CABLE_RX_POST_EMPHASIS, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_CABLE_TX_EQUALIZATION,
                              moduleInfo->berModuleInfo.cableTxEqualization, moduleInfo->header,
                              TELEMETRY_MODULE_INFO_CABLE_TX_EQUALIZATION, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_WAVELENGTH_TOLERANCE, moduleInfo->berModuleInfo.wavelengthTolerance,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_WAVELENGTH_TOLERANCE, parseFloatFromString);
    extractAndMapField(moduleInfoJson,
                       FIELD_MODULE_STATE,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_moduleStateSdk,
                       moduleInfo->berModuleInfo.moduleState,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_MODULE_STATE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_DATA_PATH_STATE_PER_LANE),
                          moduleInfo->berModuleInfo.dataPathStatePerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_DATA_PATH_STATE_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_RX_OUTPUT_VALID_PER_LANE),
                          moduleInfo->berModuleInfo.rxOutputValidPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_RX_OUTPUT_VALID_PER_LANE);
    extractAndSetNumericField(moduleInfoJson, FIELD_NOMINAL_BIT_RATE, moduleInfo->berModuleInfo.nominalBitRate,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_NOMINAL_BIT_RATE, parseFloatFromString);
    extractAndMapField(moduleInfoJson,
                       FIELD_RX_POWER_TYPE,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_rxPowerTypeSdk,
                       moduleInfo->berModuleInfo.rxPowerType,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_RX_POWER_TYPE);
    setManufacturingDateFromJson(moduleInfoJson, &moduleInfo->berModuleInfo.manufacturingDate, moduleInfo->header,
                                 TELEMETRY_MODULE_INFO_MANUFACTURING_DATE);
    extractAndSetStringField(moduleInfoJson, FIELD_ACTIVE_SET_HOST_COMPLIANCE_CODE,
                             moduleInfo->berModuleInfo.activeSetHostComplianceCode, MODULE_INFO_MAX_LENGTH,
                             moduleInfo->header, TELEMETRY_MODULE_INFO_ACTIVE_SET_HOST_COMPLIANCE_CODE);
    extractAndSetStringField(moduleInfoJson, FIELD_ACTIVE_SET_MEDIA_COMPLIANCE_CODE,
                             moduleInfo->berModuleInfo.activeSetMediaComplianceCode, MODULE_INFO_MAX_LENGTH,
                             moduleInfo->header, TELEMETRY_MODULE_INFO_ACTIVE_SET_MEDIA_COMPLIANCE_CODE);
    extractAndMapField(moduleInfoJson,
                       FIELD_ERROR_CODE_RESPONSE,
                       _mstMlxLinkSdkInstance->_mlxlinkMaps->_errorCodeResponseSdk,
                       moduleInfo->berModuleInfo.errorCodeResponse,
                       moduleInfo->header,
                       TELEMETRY_MODULE_INFO_ERROR_CODE_RESPONSE);
    extractAndSetNumericField(moduleInfoJson, FIELD_MODULE_FW_FAULT, moduleInfo->berModuleInfo.moduleFwFault,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_MODULE_FW_FAULT, parseUint8FromString);
    extractAndSetNumericField(moduleInfoJson, FIELD_DATA_PATH_FW_FAULT, moduleInfo->berModuleInfo.dataPathFwFault,
                              moduleInfo->header, TELEMETRY_MODULE_INFO_DATA_PATH_FW_FAULT, parseUint8FromString);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_TX_FAULT_PER_LANE),
                          moduleInfo->berModuleInfo.txFaultPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_TX_FAULT_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_TX_LOS_PER_LANE),
                          moduleInfo->berModuleInfo.txLosPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_TX_LOS_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_TX_CDR_LOL_PER_LANE),
                          moduleInfo->berModuleInfo.txCdrLolPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_TX_CDR_LOL_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_RX_LOS_PER_LANE),
                          moduleInfo->berModuleInfo.rxLosPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_RX_LOS_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_RX_CDR_LOL_PER_LANE),
                          moduleInfo->berModuleInfo.rxCdrLolPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_RX_CDR_LOL_PER_LANE);
    parseLanesDataAsUint8(getJsonStringValue(moduleInfoJson, FIELD_TX_ADAPTIVE_EQ_FAULT_PER_LANE),
                          moduleInfo->berModuleInfo.txAdaptiveEqFaultPerLane, moduleInfo->header,
                          TELEMETRY_MODULE_INFO_TX_ADAPTIVE_EQ_FAULT_PER_LANE);
}

void MftSdk::setAttenuationInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo)
{
    try
    {
        string attenuationFieldName = _mstMlxLinkSdkInstance->_attenuationTitle;
        string attenuation = getJsonStringValue(moduleInfoJson, attenuationFieldName);
        if (attenuation != NA_FIELD_VALUE)
        {
            std::vector<std::string> parts = split(attenuation, ',');

            moduleInfo->attenuationInfo.attenuation5g = parseUint8FromString(parts[0]);
            mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_ATTENUATION_5G);
            moduleInfo->attenuationInfo.attenuation7g = parseUint8FromString(parts[1]);
            mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_ATTENUATION_7G);
            moduleInfo->attenuationInfo.attenuation12g = parseUint8FromString(parts[2]);
            mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_ATTENUATION_12G);
            if (parts.size() > 3)
            {
                moduleInfo->attenuationInfo.attenuation25g = parseUint8FromString(parts[3]);
                mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_ATTENUATION_25G);
            }
            if (parts.size() > 4)
            {
                moduleInfo->attenuationInfo.attenuation53g = parseUint8FromString(parts[4]);
                mstQuerySetBit(moduleInfo->header, TELEMETRY_MODULE_INFO_ATTENUATION_53G);
            }
        }
    }
    catch (const std::exception& e)
    {
        throw MftGeneralException("Failed retrieving attenuation info: " + std::string(e.what()));
    }
}
MstStatus MftSdk::extractModuleInfoFromJson(MstModuleInfo* moduleInfo)
{
    try
    {
        Json::Value moduleInfoJson = getModuleInfoJsonSection();
        setVendorInfoFromJson(moduleInfoJson, moduleInfo);
        setAttenuationInfoFromJson(moduleInfoJson, moduleInfo);
        setFwVersionFromJson(moduleInfoJson, moduleInfo);
        setPowerAndCdrInfoFromJson(moduleInfoJson, moduleInfo);
        setLatencyInfoFromJson(moduleInfoJson, moduleInfo);
        setBerModuleInfoFromJson(moduleInfoJson, moduleInfo);
    }
    catch (const std::exception& e)
    {
        std::string errorMessage = "Failed to retrieve module info: " + std::string(e.what());
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, errorMessage);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getModuleInfo(MstModuleInfo* moduleInfo)
{
    if (!moduleInfo || moduleInfo->header.size < sizeof(mstQueryHeader))
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }

    if (initMlxLinkSdk(MlxLinkInitMode::MODULE_INFO) != MST_SUCCESS)
    {
        return _lastError.status;
    }

    MST_QUERY_CLEAR(moduleInfo);

    try
    {
        _mstMlxLinkSdkInstance->showModuleInfo();
        extractModuleInfoFromJson(moduleInfo);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_TELEMETRY, e.what());
    }
    return _lastError.status;
}
// Pure C API functions:
extern "C"
{
    MstStatus mstGetTelemetryOperationalInfo(MstDevice mstDevice, MstTelemetryOperationalInfo* operationalInfo)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getTelemetryOperationalInfo(operationalInfo);
    }

    MstStatus mstGetFecHistogram(MstDevice mstDevice, MstFecHistogram* fecHistogram)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getFecHistogram(fecHistogram);
    }

    MstStatus mstGetCountersInfo(MstDevice mstDevice, MstCountersInfo* countersInfo)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getCountersInfo(countersInfo);
    }

    MstStatus mstGetCableDDMInfo(MstDevice mstDevice, MstCableDDMInfo* cableDDMInfo)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getCableDDMInfo(cableDDMInfo);
    }

    MstStatus mstGetModuleInfo(MstDevice mstDevice, MstModuleInfo* moduleInfo)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getModuleInfo(moduleInfo);
    }

} // extern "C"