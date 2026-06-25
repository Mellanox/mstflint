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

#include "hca_capabilities.h"
#include "mtcr.h"
#include "fwctrl_ioctl.h"
#include "dev_mgt/tools_dev_types.h"
#include "mft_sdk/mft_sdk_hca_caps.h"
#include "mft_sdk/mft_sdk_reg_access.h"
#include "tools_layouts/prm_adb_db.h"
#include "tools_layouts/hca_cap_types_enums.h"
#include "mlxreg/mlxreg_lib/mlxreg_parser.h"
#include <iostream>
#include <sstream>

using namespace mlxreg;

const std::string HCA_CAPABILITIES_ADB_FILE = "hca_cap_table.adb";
const std::string CAPABILITIES_NODE = "query_hca_cap_out_capability_auto";

std::string toHexString(int value)
{
    std::stringstream ss;
    ss << "0x" << std::hex << value;
    return ss.str();
}

bool _getHcaCapFieldsCallback(const std::string& calculated_path,
                              uint64_t calculated_offset,
                              uint64_t calculated_value,
                              AdbInstanceAdvLegacy* instance,
                              void* context)
{
    (void)calculated_path;
    (void)calculated_offset;
    (void)calculated_value;

    vector<AdbInstanceAdvLegacy*>* fields = (vector<AdbInstanceAdvLegacy*>*)context;
    fields->push_back(instance);

    return false; // continue traversal
}

MstPrmAccessType convertHcaCapAccessType(const std::string& access)
{
    if (access == "RO")
    {
        return MST_PRM_ACCESS_RO;
    }
    else if (access == "WO")
    {
        return MST_PRM_ACCESS_WO;
    }
    else if (access == "RW")
    {
        return MST_PRM_ACCESS_RW;
    }
    else if (access == "INDEX")
    {
        return MST_PRM_ACCESS_INDEX;
    }
    else if (access == "OP")
    {
        return MST_PRM_ACCESS_OP;
    }
    else
    {
        return MST_PRM_ACCESS_UNKNOWN;
    }
}

void HcaCapabilities::fillHcaCapabilityFieldMetadata(AdbInstanceAdvLegacy* adbField,
                                                     MstHcaCapabilityFieldMetadata* metadataField,
                                                     const char* capabilityType)
{
    std::string field_name = getCapabilityName(adbField, capabilityType);
    strncpy(metadataField->name, field_name.c_str(), sizeof(metadataField->name) - 1);
    metadataField->name[sizeof(metadataField->name) - 1] = '\0';
    metadataField->address = (adbField->offset >> 3) & ~0x3;
    metadataField->bitOffset = adbField->startBit();
    metadataField->bitSize = (unsigned int)adbField->fieldDesc->eSize();
    metadataField->accessType = convertHcaCapAccessType(mlxreg::RegAccessParser::getAccess(adbField));
}

HcaCapabilities::HcaCapabilities(std::string mstDeviceName) : _mf(nullptr), _adb(nullptr), _hcaCapabilitiesNode(nullptr)
{
    openDevice(mstDeviceName);
    parseAdbFile();
    initCapabilityTypesMap();
}

HcaCapabilities::~HcaCapabilities()
{
    if (_mf)
    {
        mclose(_mf);
        _mf = nullptr;
    }
}

void HcaCapabilities::openDevice(const std::string& mstDeviceName)
{
    dm_dev_id_t DeviceType = DeviceUnknown;
    u_int32_t hwDevId = 0;
    u_int32_t hwRevId = 0;
    _mf = mopen(mstDeviceName.c_str());
    if (!_mf)
    {
        throw HcaCapabilitiesException("Failed to open device: " + mstDeviceName);
    }

    if (dm_get_device_id(_mf, &DeviceType, &hwDevId, &hwRevId))
    {
        throw HcaCapabilitiesException("Failed to get device id: " + mstDeviceName);
    }

    if (!dm_dev_is_hca(DeviceType))
    {
        throw HcaCapabilitiesException("Device not supported: " + mstDeviceName +
                                       ". Only HCA devices support HCA capabilities.");
    }

    if (_mf->tp != MST_FWCTL_CONTROL_DRIVER)
    {
        throw HcaCapabilitiesException("Device not supported: " + mstDeviceName +
                                       ". Only FWCTL devices support HCA capabilities.");
    }
}

void HcaCapabilities::parseAdbFile()
{
    try
    {
        _adb = std::unique_ptr<AdbAdvLegacy>(new AdbAdvLegacy());
        std::string adbFileName = PrmAdbDB::getDefaultDBName(PrmAdbType::PRM_ADB_TYPE_HCA, HCA_CAPABILITIES_ADB_FILE);
        if (!_adb->load(adbFileName, false, false))
        {
            throw HcaCapabilitiesException("Failed to load ADB: " + _adb->getLastError());
        }

        _hcaCapabilitiesNode = std::unique_ptr<AdbInstanceAdvLegacy>(_adb->createLayout(CAPABILITIES_NODE));
        if (!_hcaCapabilitiesNode)
        {
            throw HcaCapabilitiesException("Failed to retrieve capabilities node");
        }
        if (!_hcaCapabilitiesNode->isUnion())
        {
            throw HcaCapabilitiesException("Capabilities node is not a union");
        }
    }
    catch (AdbException& exp)
    {
        throw HcaCapabilitiesException(exp.what());
    }
}

void HcaCapabilities::initCapabilityTypesMap()
{
    _capabilityTypesMap["cmd_hca_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_GENERAL_DEVICE_CAPABILITIES;
    _capabilityTypesMap["adv_rdma_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ADV_RDMA_CAPABILITIES;
    _capabilityTypesMap["adv_virtualization_capabilities"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ADV_VIRTUALIZATION_CAPABILITIES;
    _capabilityTypesMap["atomic_caps"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ATOMIC_CAPABILITIES;
    _capabilityTypesMap["cc_prov_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_CC_SERVICE_PROV_CAPABILITIES;
    _capabilityTypesMap["crypto_caps"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_CRYPTO_CAPABILITIES;
    _capabilityTypesMap["debug_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_DEBUG_CAPABILITIES;
    _capabilityTypesMap["device_mem_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_DEVICE_MEMORY_CAPABILITIES;
    _capabilityTypesMap["dpa_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_DPA_CAPABILITIES;
    _capabilityTypesMap["dpp_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_DPP_CAPABILITIES;
    _capabilityTypesMap["e_switch_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ESWITCH_CAPABILITIES;
    _capabilityTypesMap["event_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_EVENT_CAPABILITIES;
    _capabilityTypesMap["flow_table_eswitch_cap"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ESWITCH_FLOW_TABLE_CAPABILITIES;
    _capabilityTypesMap["flow_table_nic_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_NIC_FLOW_TABLE_CAPABILITIES;
    _capabilityTypesMap["generic_dev_emu_capabilities"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_GENERIC_DEVICE_EMULATION_CAPABILITIES;
    _capabilityTypesMap["hca_caps_2"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_GENERAL_DEVICE_CAPABILITIES_2;
    _capabilityTypesMap["hotplug_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_HOTPLUG_CAPABILITIES;
    _capabilityTypesMap["ipsec_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_IPSEC_CAPABILITIES;
    _capabilityTypesMap["macsec_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_MACSEC_CAPABILITIES;
    _capabilityTypesMap["nvmf_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_NVME;
    _capabilityTypesMap["nvmeotcp_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_NVMEOTCP_CAPABILITIES;
    _capabilityTypesMap["odp_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ODP_CAPABILITIES;
    _capabilityTypesMap["parse_graph_node_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_PARSE_GRAPH_NODE_CAPABILITIES;
    _capabilityTypesMap["paso_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_PASO_CAPABILITIES;
    _capabilityTypesMap["port_selection_capabilities"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_PORT_SELECTION_CAPABILITIES;
    _capabilityTypesMap["psp_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_PSP_CAPABILITIES;
    _capabilityTypesMap["qos_caps"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_QUALITY_OF_SERVICE_CAPABILITIES;
    _capabilityTypesMap["roce_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ROCE_CAPABILITIES;
    _capabilityTypesMap["shampo_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_SHAMPO_CAPABILITES;
    _capabilityTypesMap["tlp_dev_emu_capabilities"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_TLP_DEVICE_EMULATION;
    _capabilityTypesMap["tls_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_TLS_CAPABILITIES;
    _capabilityTypesMap["ts_prov_capabilities"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_TRANSPORT_SERVICE_PROV_CAPABILITIES;
    _capabilityTypesMap["upt_device_emulation_caps"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_UPT_DEVICE_EMULATION_CAPABILITIES;
    _capabilityTypesMap["vector_calc_caps"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_VECTOR_CALC_CAPABILITIES;
    _capabilityTypesMap["wqe_based_flow_table_capabilities"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_WQE_BASED_FLOW_TABLE_CAPABILITIES;
    _capabilityTypesMap["device_emulation_cap"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_NVME_DEVICE_EMULATION_CAPABILITIES;

    // Per protocol networking offload capabilities uses the same adb node.
    _capabilityTypesMap["per_protocol_networking_offload_caps"] =
      HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_ETHERNET_OFFLOAD_CAPABILITIES;

    // Virtio emulation capabilities uses the same adb node.
    _capabilityTypesMap["virtio_emulation_cap"] = HCA_CAP_TYPES__QUERY_HCA_CAP_IN_OP_MOD_VDPA_EMULATION_CAPABILITIES;
}

uint16_t HcaCapabilities::convertCapabilityTypeToOpMod(const char* capabilityType)
{
    try
    {
        return _capabilityTypesMap.at(capabilityType);
    }
    catch (const std::out_of_range& e)
    {
        throw HcaCapabilitiesException("Invalid capability type: " + std::string(capabilityType));
    }
}

AdbInstanceAdvLegacy* HcaCapabilities::getCapabilityTypeLayout(const char* capabilityType)
{
    if (_capabilityTypeLayoutCache.find(capabilityType) != _capabilityTypeLayoutCache.end())
    {
        return _capabilityTypeLayoutCache[capabilityType];
    }
    std::vector<AdbInstanceAdvLegacy*> capabilityTypeLayoutVector =
      _hcaCapabilitiesNode->findChild(capabilityType, false);
    if (capabilityTypeLayoutVector.empty())
    {
        throw HcaCapabilitiesException("Invalid capability type: " + std::string(capabilityType));
    }
    AdbInstanceAdvLegacy* capabilityTypeLayout = capabilityTypeLayoutVector[0];
    _capabilityTypeLayoutCache[capabilityType] = capabilityTypeLayout;
    return capabilityTypeLayout;
}

std::string HcaCapabilities::buildFwCommandError(const std::string& action, const char* capabilityType, int fwStatus)
{
    std::string errorMsg = action + ": " + std::string(capabilityType) + " (" +
                           toHexString(convertCapabilityTypeToOpMod(capabilityType)) + ") " +
                           mlx5_cmd_status_str((uint8_t)fwStatus);
    uint32_t syndrome = getSyndromeCode();
    if (syndrome)
    {
        errorMsg += ", syndrome: " + toHexString(syndrome);
    }
    return errorMsg;
}

std::unique_ptr<uint8_t[]> HcaCapabilities::fwctlQueryHcaCapability(unsigned int capabilityByteSize,
                                                                    const char* capabilityType,
                                                                    MstCapabilityMode capabilityMode,
                                                                    uint16_t functionId,
                                                                    uint8_t functionIdType,
                                                                    uint8_t otherFunction)
{
    std::unique_ptr<uint8_t[]> capabilityBuffer(new uint8_t[capabilityByteSize]);
    int err = fwctl_query_hca_capability(
      _mf, capabilityBuffer.get(), capabilityByteSize, convertCapabilityTypeToOpMod(capabilityType),
      capabilityMode == MST_CAPABILITY_MODE_CURRENT ? CAPABILITY_MODE_CURRENT : CAPABILITY_MODE_MAX, functionId,
      functionIdType, otherFunction);
    if (err)
    {
        throw HcaCapabilitiesException(buildFwCommandError("Failed to query capability", capabilityType, err));
    }
    return capabilityBuffer;
}

void HcaCapabilities::fwctlSetHcaCapability(uint8_t* capabilityBuffer,
                                            unsigned int capabilityByteSize,
                                            const char* capabilityType,
                                            MstCapabilityMode capabilityMode,
                                            uint16_t functionId,
                                            uint8_t functionIdType,
                                            uint8_t otherFunction)
{
    int err = fwctl_set_hca_capability(
      _mf, capabilityBuffer, capabilityByteSize, convertCapabilityTypeToOpMod(capabilityType),
      capabilityMode == MST_CAPABILITY_MODE_CURRENT ? CAPABILITY_MODE_CURRENT : CAPABILITY_MODE_MAX, functionId,
      functionIdType, otherFunction);
    if (err)
    {
        throw HcaCapabilitiesException(buildFwCommandError("Failed to set capability", capabilityType, err));
    }
}

std::vector<AdbInstanceAdvLegacy*> HcaCapabilities::getCapabilityFields(AdbInstanceAdvLegacy* capabilityTypeLayout)
{
    std::vector<AdbInstanceAdvLegacy*> capabilities;
    _adb->traverse_layout(capabilityTypeLayout, "", 0, nullptr, 0, _getHcaCapFieldsCallback, &capabilities, false, false);
    return capabilities;
}

std::string HcaCapabilities::getCapabilityName(AdbInstanceAdvLegacy* capability, const char* capabilityType)
{
    // remove capabilityType from the beginning of the capability name
    std::string capabilityName = capability->fullName(1);
    std::string prefix = capabilityType + std::string(".");
    if (capabilityName.find(prefix) == 0)
    {
        return capabilityName.substr(prefix.length());
    }
    return capabilityName;
}

void HcaCapabilities::updateCapabilityMap(MstHcaCapabilityMap* capabilityMap,
                                          const char* capabilityType,
                                          std::vector<AdbInstanceAdvLegacy*> capabilities,
                                          uint8_t* capabilityBuffer)
{
    strncpy(capabilityMap->capabilityType, capabilityType, sizeof(capabilityMap->capabilityType) - 1);
    capabilityMap->capabilityType[sizeof(capabilityMap->capabilityType) - 1] = '\0';
    capabilityMap->numberOfCapabilities = capabilities.size();
    capabilityMap->capabilities = new MstHcaCapability[capabilities.size()];
    std::map<std::string, uint32_t> capabilityIndexMap;
    for (unsigned int i = 0; i < capabilities.size(); i++)
    {
        strncpy(capabilityMap->capabilities[i].capabilityName,
                getCapabilityName(capabilities[i], capabilityType).c_str(),
                sizeof(capabilityMap->capabilities[i].capabilityName) - 1);
        capabilityMap->capabilities[i].capabilityName[sizeof(capabilityMap->capabilities[i].capabilityName) - 1] = '\0';
        if (capabilityBuffer)
        {
            capabilityMap->capabilities[i].value = capabilities[i]->popBuf(capabilityBuffer);
        }
        capabilityIndexMap[getCapabilityName(capabilities[i], capabilityType)] = i;
    }
    _capabilitiesIndexCache[capabilityType] = capabilityIndexMap;
}

MstHcaCapabilityMap* HcaCapabilities::initHcaCapabilityMap(const char* capabilityType,
                                                           MstHcaCapabilityMap* capabilityMap)
{
    if (!capabilityType)
    {
        throw HcaCapabilitiesException("Capability type is not valid");
    }
    memset(capabilityMap, 0, sizeof(MstHcaCapabilityMap));
    AdbInstanceAdvLegacy* capabilityTypeLayout = getCapabilityTypeLayout(capabilityType);
    std::vector<AdbInstanceAdvLegacy*> capabilities = getCapabilityFields(capabilityTypeLayout);
    updateCapabilityMap(capabilityMap, capabilityType, capabilities, nullptr);
    return capabilityMap;
}

void HcaCapabilities::queryHcaCapability(const char* capabilityType,
                                         MstHcaCapabilityMap* capabilityMap,
                                         MstCapabilityMode capabilityMode,
                                         uint16_t functionId,
                                         MstFunctionIdType functionIdType,
                                         MstOtherFunction otherFunction)
{
    AdbInstanceAdvLegacy* capabilityTypeLayout = getCapabilityTypeLayout(capabilityType);
    unsigned int capabilityByteSize = capabilityTypeLayout->get_size() / 8;
    std::unique_ptr<uint8_t[]> capabilityBuffer = fwctlQueryHcaCapability(
      capabilityByteSize, capabilityType, capabilityMode, functionId, functionIdType, otherFunction);
    std::vector<AdbInstanceAdvLegacy*> capabilities = getCapabilityFields(capabilityTypeLayout);
    updateCapabilityMap(capabilityMap, capabilityType, capabilities, capabilityBuffer.get());
}

void HcaCapabilities::setHcaCapability(const char* capabilityType,
                                       MstHcaCapabilityMap* capabilityMap,
                                       MstCapabilityMode capabilityMode,
                                       uint16_t functionId,
                                       MstFunctionIdType functionIdType,
                                       MstOtherFunction otherFunction)
{
    AdbInstanceAdvLegacy* capabilityTypeLayout = getCapabilityTypeLayout(capabilityType);
    unsigned int capabilityByteSize = capabilityTypeLayout->get_size() / 8;
    std::unique_ptr<uint8_t[]> capabilityBuffer = fwctlQueryHcaCapability(
      capabilityByteSize, capabilityType, capabilityMode, functionId, functionIdType, otherFunction);
    std::vector<AdbInstanceAdvLegacy*> capabilities = getCapabilityFields(capabilityTypeLayout);
    for (unsigned int i = 0; i < capabilities.size(); i++)
    {
        if (capabilityMap->capabilities[i].set)
        {
            capabilities[i]->pushBuf(capabilityBuffer.get(), capabilityMap->capabilities[i].value);
        }
    }
    fwctlSetHcaCapability(capabilityBuffer.get(), capabilityByteSize, capabilityType, capabilityMode, functionId,
                          functionIdType, otherFunction);
}

uint32_t HcaCapabilities::getCapabilityIndex(MstHcaCapabilityMap* capabilityMap, const char* capabilityName)
{
    if (!capabilityMap)
    {
        throw HcaCapabilitiesException("Capability map is not initialized");
    };
    std::map<std::string, uint32_t> capabilityIndexMap =
      _capabilitiesIndexCache[std::string(capabilityMap->capabilityType)];
    if (capabilityIndexMap.find(capabilityName) == capabilityIndexMap.end())
    {
        throw HcaCapabilitiesException("Capability name " + std::string(capabilityName) +
                                       " not found for capability type: " + std::string(capabilityMap->capabilityType));
    }

    return capabilityIndexMap.at(capabilityName);
}

uint32_t HcaCapabilities::getCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName)
{
    uint32_t capabilityIndex = getCapabilityIndex(capabilityMap, capabilityName);
    return capabilityMap->capabilities[capabilityIndex].value;
}

void HcaCapabilities::setCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t value)
{
    uint32_t capabilityIndex = getCapabilityIndex(capabilityMap, capabilityName);
    capabilityMap->capabilities[capabilityIndex].value = value;
    capabilityMap->capabilities[capabilityIndex].set = true;
}

void HcaCapabilities::fillCapabilitiesMetadata(const char* capabilityType, MstHcaCapabilityMetadata* capabilityMetadata)
{
    AdbInstanceAdvLegacy* capabilityTypeLayout = getCapabilityTypeLayout(capabilityType);
    std::vector<AdbInstanceAdvLegacy*> capabilities = getCapabilityFields(capabilityTypeLayout);
    strncpy(capabilityMetadata->capabilityName, capabilityType, sizeof(capabilityMetadata->capabilityName) - 1);
    capabilityMetadata->capabilityName[sizeof(capabilityMetadata->capabilityName) - 1] = '\0';
    capabilityMetadata->numberOfFields = capabilities.size();
    capabilityMetadata->fields = new MstHcaCapabilityFieldMetadata[capabilities.size()];
    memset(capabilityMetadata->fields, 0, sizeof(MstHcaCapabilityFieldMetadata) * capabilities.size());
    for (unsigned int i = 0; i < capabilities.size(); i++)
    {
        fillHcaCapabilityFieldMetadata(capabilities[i], &capabilityMetadata->fields[i], capabilityType);
    }
}

std::vector<std::string> HcaCapabilities::getCapabilityTypesList()
{
    std::vector<std::string> capabilityTypesList;
    for (auto field : _hcaCapabilitiesNode->nodeDesc->fields)
    {
        capabilityTypesList.push_back(field->name);
    }
    return capabilityTypesList;
}

mfile* HcaCapabilities::getMFile()
{
    return _mf;
}

uint32_t HcaCapabilities::getSyndromeCode()
{
    if (!_mf)
    {
        return 0;
    }
    return _mf->icmd.syndrome;
}