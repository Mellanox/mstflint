/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <mft_sdk/mft_sdk.h>
#ifdef MFT_SDK_EXTERNAL
#include "mlxreg/mlxreg_sdk/prm_reg_sdk.h"
#else
#include "mlxreg/mlxreg_sdk/prm_reg_sdk_int.h"
#endif
#include "mlxlink/modules/mlxlink_commander.h"
#include "mtcr.h"
#include "hca_capabilities/hca_capabilities.h"

enum class MlxLinkInitMode
{
    NONE,
    OPERATIONAL_INFO,
    CABLE_DDM,
    MODULE_INFO
};
class MftSdk
{
public:
    MftSdk(const std::string& deviceIdentifier);
    ~MftSdk();

    // error handling functions
    const char* getLastError() const;
    uint32_t getSyndromeCode() const;

    // mlxreg SDK functions
    MstStatus sendPRMRegister(MstPrmRegisterMap* registerMap, MstPrmRegAccessMethod method);
    MstStatus sendRawPRMRegister(uint16_t regId, MstPrmRegAccessMethod method, void* data, uint32_t dataSize);
    MstStatus freePrmRegisterMap(MstPrmRegisterMap* registerMap);
    MstStatus showAllPRMRegisters(std::vector<std::string>& registers);
    MstStatus initRegisterMap(const char* regName, MstPrmRegisterMap* registerMap);
    MstStatus getRegisterMetadata(const char* regName, MstPrmRegisterMetadata* registerMetadata);
    MstStatus getRegisterExpandedMetadata(const char* regName, MstPrmRegisterExpandedMetadata* registerMetadata);
    MstStatus setPRMRegisterField(MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t value);
    MstStatus getPRMRegisterField(MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t* value);

    // mlxlink SDK functions
    MstStatus getTelemetryOperationalInfo(MstTelemetryOperationalInfo* operationalInfo,
                                          const MstTelemetryContext& context = MstTelemetryContext{0, ""});
    MstStatus getFecHistogram(MstFecHistogram* fecHistogram,
                              const MstTelemetryContext& context = MstTelemetryContext{0, ""});
    MstStatus getCountersInfo(MstCountersInfo* countersInfo,
                              const MstTelemetryContext& context = MstTelemetryContext{0, ""});
    MstStatus getCableDDMInfo(MstCableDDMInfo* cableDDMInfo,
                              const MstTelemetryContext& context = MstTelemetryContext{0, ""});
    MstStatus getModuleInfo(MstModuleInfo* moduleInfo, const MstTelemetryContext& context = MstTelemetryContext{0, ""});

    // HCA capabilities SDK functions
    MstStatus getCapabilityTypesList(std::vector<std::string>& capabilityTypes);
    MstStatus fillCapabilitiesMetadata(const char* capabilityType, MstHcaCapabilityMetadata* capabilityMetadata);
    MstStatus initHcaCapabilityMap(const char* capabilityType, MstHcaCapabilityMap* capabilityMap);
    MstStatus queryHcaCapability(const char* capabilityType,
                                 MstHcaCapabilityMap* capabilityMap,
                                 MstCapabilityMode capabilityMode,
                                 uint16_t functionId,
                                 MstFunctionIdType functionIdType,
                                 MstOtherFunction otherFunction);
    MstStatus setHcaCapability(const char* capabilityType,
                               MstHcaCapabilityMap* capabilityMap,
                               MstCapabilityMode capabilityMode,
                               uint16_t functionId,
                               MstFunctionIdType functionIdType,
                               MstOtherFunction otherFunction);
    MstStatus
      getCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t* capabilityValue);
    MstStatus
      setCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t capabilityValue);

    // CR space SDK functions
    MstStatus readCRSpace(uint32_t address, uint32_t* data, int byteLength);
    MstStatus writeCRSpace(uint32_t address, uint32_t* data, int byteLength);

    // I2C access SDK functions
    MstStatus setI2cSecondary(uint8_t newI2cSecondaryAddress);
    MstStatus getI2cSecondary(uint8_t* i2cSecondaryAddress);

private:
    void setInitError(MstStatus status, const std::string& errorMessage);
    void setLastError(MstStatus status, const std::string& errorMessage);
    void clearError();

    // mlxreg SDK functions
    void initMlxregSdkInstance();
    MstStatus initMlxregSdk(const char* regName = "", MstPrmRegAccessMethod method = MST_PRM_GET);
    MstStatus initMlxregSdkById(uint16_t regId, MstPrmRegAccessMethod method = MST_PRM_GET);
    MstStatus translateMlxregSDKErrorToMstStatus(int32_t errorCode);
    MstStatus setErrorFromMlxregSDKError(int32_t errorCode);

    // mlxlink SDK private functions
    MstStatus initMlxLinkSdk(MlxLinkInitMode initMode = MlxLinkInitMode::NONE, const std::string& port = "");
    void initMlxLinkSdkPortInfo();
    void initMlxLinkSdkUserInput(MlxLinkInitMode initMode);
    MstStatus extractOperationalInfoFromJson(MstTelemetryOperationalInfo* operationalInfo);
    MstStatus extractCountersInfoFromJson(MstCountersInfo* countersInfo);
    MstStatus extractCableDDMInfoFrom(MstCableDDMInfo* cableDDMInfo);
    MstStatus extractModuleInfoFromJson(MstModuleInfo* moduleInfo);
    Json::Value getJsonSection(const std::string& sectionName, Json::Value& jsonRoot);
    Json::Value getOperationalInfoJsonSection();
    std::string getJsonStringValue(const Json::Value& jsonValue, const std::string& fieldName, bool isOptional = true);
    Json::Value getCountersInfoJsonSection();
    Json::Value getCableDDMInfoJsonSection();
    Json::Value getModuleInfoJsonSection();
    void setVendorInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setFwVersionFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setAttenuationInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setPowerAndCdrInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setLatencyInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setSnrInfoFromJson(const Json::Value& moduleInfoJson,
                            MstSnrInfo* snrInfo,
                            mstQueryHeader& header,
                            uint8_t mediaLanesBitIndex,
                            uint8_t hostLanesBitIndex);
    void setBerModuleInfoFromJson(const Json::Value& moduleInfoJson, MstModuleInfo* moduleInfo);
    void setManufacturingDateFromJson(const Json::Value& moduleInfoJson,
                                      MstDate* manufacturingDate,
                                      mstQueryHeader& header,
                                      uint8_t bitIndex);
    bool parseSnrLanesFromString(const std::string& fieldValue, float* lanes);
    void parseCdrLanesData(const std::string& fieldValue, uint8_t* lanes, mstQueryHeader& header, uint8_t bitIndex);
    void parseLanesDataAsUint8(const std::string& fieldValue, uint8_t* lanes, mstQueryHeader& header, uint8_t bitIndex);
    ScientificNotation parseScientificNotation(const std::string& value);
    std::vector<std::string> split(const std::string& value, char delimiter);

    // DDM extraction helper functions
    void extractModuleDDMFlags(cable_ddm_q_t& cableDDMoutput, MstCableDDMInfo* cableDDMInfo);
    void extractChannelDDMFlags(ddm_threshold_t& rxPower,
                                ddm_threshold_t& txPower,
                                ddm_threshold_t& txBias,
                                MstCableDDMAlarmFlags& rxChannelFlags,
                                MstCableDDMAlarmFlags& txChannelFlags,
                                MstCableDDMAlarmFlags& txBiasChannelFlags);
    void ExtractThresholds(cable_ddm_q_t& cableDDMoutput, float txBiasMultiplier, MstCableDDMInfo* cableDDMInfo);

    MstStatus mlxlinkGetFecHistogram(MstFecHistogram* fecHistogram);
    void extractRawPhysicalBERPerLane(const Json::Value& jsonSection, MstCountersInfo* countersInfo);
    void extractRawPhysicalErrorsPerLane(const Json::Value& jsonSection, MstCountersInfo* countersInfo);
    void extractLinkCounters(const Json::Value& jsonSection, MstCountersInfo* countersInfo);
    void extractSymbolCounters(const Json::Value& jsonSection, MstCountersInfo* countersInfo);
    template<typename T, typename Parser>
    void extractAndSetNumericField(const Json::Value& json,
                                   const std::string& fieldName,
                                   T& targetField,
                                   mstQueryHeader& header,
                                   uint8_t bitIndex,
                                   Parser parser);
    void extractAndSetStringField(const Json::Value& json,
                                  const std::string& fieldName,
                                  char* targetField,
                                  size_t maxLength,
                                  mstQueryHeader& header,
                                  uint8_t bitIndex);
    template<typename MapType, typename FieldType>
    void extractAndMapField(const Json::Value& jsonRoot,
                            const std::string& jsonFieldName,
                            const MapType& mapRef,
                            FieldType& targetField,
                            mstQueryHeader& header,
                            uint32_t bitIndex,
                            bool isOptional = true);
    void extractOperationalInfoWidth(const Json::Value& jsonSection, MstTelemetryOperationalInfo* operationalInfo);

    // hca capabilities SDK private functions
    MstStatus initHcaCapabilities();

    std::string _deviceIdentifier;
    mfile* _mf;
    MstErrorInfo _lastError;
    uint32_t _syndromeCode;
    std::unique_ptr<PrmRegSdk> _mlxregSdkInstance;
    std::unique_ptr<MlxlinkCommander> _mstMlxLinkSdkInstance;
    std::unique_ptr<HcaCapabilities> _hcaCapabilitiesSdkInstance;
    std::vector<mfile*> _mfiles;
    std::map<MlxLinkInitMode, bool> mlxlinkSdkInitialized;
    // Currently bound mlxlink port label (empty => device default). Guards redundant re-binds.
    std::string _currentMlxLinkPort;
    // Tracks the per-port init flow (updatePortInfo()+showPddr()) already run for each (port, mode).
    std::map<std::pair<std::string, MlxLinkInitMode>, bool> _portModeInitialized;
};