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

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <map>
#include "adb_parser/adb_parser.h"
#include "mtcr.h"
#include "mft_sdk/mft_sdk_hca_caps.h"

class HcaCapabilities
{
public:
    HcaCapabilities(std::string mstDeviceName);
    ~HcaCapabilities();

    /**
     * @brief Fills a HCA capability metadata object.
     * @param input capabilityType name of HCA Capability Type.
     * @param output capabilityMetadata The capability metadata including fields name, size, address, bit offset, access
     * type as defined in the PRM.
     */
    void fillCapabilitiesMetadata(const char* capabilityType, MstHcaCapabilityMetadata* capabilityMetadata);
    /**
     * @brief Initializes a HCA capability map.
     * @param input capabilityType name of HCA Capability Type.
     * @param output capabilityMap The capability map based on the PRM definition.
     * @return The status of the operation.
     */
    MstHcaCapabilityMap* initHcaCapabilityMap(const char* capabilityType, MstHcaCapabilityMap* capabilityMap);
    /**
     * @brief Sets/Queries a HCA capability via FWCTL interface.
     * @param input capabilityType name of HCA Capability Type.
     * @param output capabilityMap The capability map based on the PRM definition which was initialized by
     * initHcaCapabilityMap function.
     * @param input capabilityMode The capability mode.
     * @param input functionId The function ID.
     * @param input functionIdType The function ID type.
     */
    void queryHcaCapability(const char* capabilityType,
                            MstHcaCapabilityMap* capabilityMap,
                            MstCapabilityMode capabilityMode,
                            uint16_t functionId,
                            MstFunctionIdType functionIdType,
                            MstOtherFunction otherFunction);
    void setHcaCapability(const char* capabilityType,
                          MstHcaCapabilityMap* capabilityMap,
                          MstCapabilityMode capabilityMode,
                          uint16_t functionId,
                          MstFunctionIdType functionIdType,
                          MstOtherFunction otherFunction);
    /**
     * @brief Sets/Gets the value of a specific HCA capability from a capability map.
     * @param input capabilityMap The capability map based on the PRM definition which was initialized by
     * initHcaCapabilityMap function.
     * @param input capabilityName The name of the capability.
     * @return The value of the capability.
     */
    uint32_t getCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName);
    void setCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t capabilityValue);
    /**
     * @brief Gets the list of HCA capability type names.
     * @return The list of HCA capability types.
     */
    std::vector<std::string> getCapabilityTypesList();
    mfile* getMFile();
    uint32_t getSyndromeCode();

private:
    void openDevice(const std::string& mstDeviceName);
    void parseAdbFile();
    void initCapabilityTypesMap();
    AdbInstanceAdvLegacy* getCapabilityTypeLayout(const char* capabilityType);
    std::string getCapabilityName(AdbInstanceAdvLegacy* capability, const char* capabilityType);
    std::unique_ptr<uint8_t[]> fwctlQueryHcaCapability(unsigned int capabilityByteSize,
                                                       const char* capabilityType,
                                                       MstCapabilityMode capabilityMode,
                                                       uint16_t functionId,
                                                       uint8_t functionIdType,
                                                       uint8_t otherFunction);
    void fwctlSetHcaCapability(uint8_t* capabilityBuffer,
                               unsigned int capabilityByteSize,
                               const char* capabilityType,
                               MstCapabilityMode capabilityMode,
                               uint16_t functionId,
                               uint8_t functionIdType,
                               uint8_t otherFunction);
    std::vector<AdbInstanceAdvLegacy*> getCapabilityFields(AdbInstanceAdvLegacy* capabilityTypeLayout);
    void fillHcaCapabilityFieldMetadata(AdbInstanceAdvLegacy* adbField,
                                        MstHcaCapabilityFieldMetadata* metadataField,
                                        const char* capabilityType);
    void updateCapabilityMap(MstHcaCapabilityMap* capabilityMap,
                             const char* capabilityType,
                             std::vector<AdbInstanceAdvLegacy*> capabilities,
                             uint8_t* capabilityBuffer);
    uint32_t getCapabilityIndex(MstHcaCapabilityMap* capabilityMap, const char* capabilityName);
    uint16_t convertCapabilityTypeToOpMod(const char* capabilityType);
    std::string buildFwCommandError(const std::string& action, const char* capabilityType, int fwStatus);

    mfile* _mf;
    std::unique_ptr<AdbAdvLegacy> _adb;
    std::unique_ptr<AdbInstanceAdvLegacy> _hcaCapabilitiesNode;
    std::map<std::string, uint16_t> _capabilityTypesMap;
    std::map<std::string, AdbInstanceAdvLegacy*> _capabilityTypeLayoutCache;
    std::map<std::string, std::map<std::string, uint32_t>> _capabilitiesIndexCache;
};

class HcaCapabilitiesException : public std::runtime_error
{
public:
    HcaCapabilitiesException(const std::string& msg) : std::runtime_error(msg) {}
};