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

#include "mft_sdk/mft_sdk_class.hpp"
#include "hca_capabilities/hca_capabilities.h"

MstStatus MftSdk::initHcaCapabilities()
{
    clearError();
    try
    {
        if (_hcaCapabilitiesSdkInstance == nullptr)
        {
            _hcaCapabilitiesSdkInstance = std::unique_ptr<HcaCapabilities>(new HcaCapabilities(_deviceIdentifier));
            _mfiles.push_back(_hcaCapabilitiesSdkInstance->getMFile());
        }
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getCapabilityTypesList(std::vector<std::string>& capabilityTypes)
{
    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }
    try
    {
        capabilityTypes = _hcaCapabilitiesSdkInstance->getCapabilityTypesList();
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
    }
    return _lastError.status;
}

MstStatus MftSdk::fillCapabilitiesMetadata(const char* capabilityType, MstHcaCapabilityMetadata* capabilityMetadata)
{
    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }

    try
    {
        _hcaCapabilitiesSdkInstance->fillCapabilitiesMetadata(capabilityType, capabilityMetadata);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
    }
    return _lastError.status;
}

MstStatus MftSdk::initHcaCapabilityMap(const char* capabilityType, MstHcaCapabilityMap* capabilityMap)
{
    if (!capabilityType || !capabilityMap)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "Capability type or capability map is not initialized");
        return MST_ERROR_INVALID_ARGUMENT;
    }

    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }

    try
    {
        _hcaCapabilitiesSdkInstance->initHcaCapabilityMap(capabilityType, capabilityMap);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
    }
    return _lastError.status;
}

MstStatus MftSdk::queryHcaCapability(const char* capabilityType,
                                     MstHcaCapabilityMap* capabilityMap,
                                     MstCapabilityMode capabilityMode,
                                     uint16_t functionId,
                                     MstFunctionIdType functionIdType,
                                     MstOtherFunction otherFunction)
{
    if (!capabilityMap || !capabilityType)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "Capability type or capability map is not initialized");
        return MST_ERROR_INVALID_ARGUMENT;
    }

    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }
    try
    {
        _hcaCapabilitiesSdkInstance->queryHcaCapability(
          capabilityType, capabilityMap, capabilityMode, functionId, functionIdType, otherFunction);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
        _syndromeCode = _hcaCapabilitiesSdkInstance->getSyndromeCode();
    }
    return _lastError.status;
}

MstStatus MftSdk::setHcaCapability(const char* capabilityType,
                                   MstHcaCapabilityMap* capabilityMap,
                                   MstCapabilityMode capabilityMode,
                                   uint16_t functionId,
                                   MstFunctionIdType functionIdType,
                                   MstOtherFunction otherFunction)
{
    if (!capabilityType || !capabilityMap)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "Capability type or capability map is not initialized");
        return MST_ERROR_INVALID_ARGUMENT;
    }
    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }
    try
    {
        _hcaCapabilitiesSdkInstance->setHcaCapability(
          capabilityType, capabilityMap, capabilityMode, functionId, functionIdType, otherFunction);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
        _syndromeCode = _hcaCapabilitiesSdkInstance->getSyndromeCode();
    }
    return _lastError.status;
}

MstStatus
  MftSdk::getCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t* capabilityValue)
{
    if (!capabilityMap || !capabilityValue)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "Capability map or value is not initialized");
        return MST_ERROR_INVALID_ARGUMENT;
    }
    // Required, not symmetry: the instance is null until this runs, so calling
    // this entry point first crashed. Also clears the stale error.
    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }
    try
    {
        *capabilityValue = _hcaCapabilitiesSdkInstance->getCapabilityValue(capabilityMap, capabilityName);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
    }
    return _lastError.status;
}

MstStatus
  MftSdk::setCapabilityValue(MstHcaCapabilityMap* capabilityMap, const char* capabilityName, uint32_t capabilityValue)
{
    if (!capabilityMap)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "Capability map is not initialized");
        return MST_ERROR_INVALID_ARGUMENT;
    }

    // Same null-instance crash as getCapabilityValue above.
    if (initHcaCapabilities() != MST_SUCCESS)
    {
        return _lastError.status;
    }

    try
    {
        _hcaCapabilitiesSdkInstance->setCapabilityValue(capabilityMap, capabilityName, capabilityValue);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES, e.what());
    }
    return _lastError.status;
}

extern "C"
{
    MstStatus mstGetCapabilityTypesList(MstDevice mstDevice, char*** capabilityTypesArray, unsigned int* numCapabilities)
    {
        if (!mstDevice || !capabilityTypesArray || !numCapabilities)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        try
        {
            MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
            std::vector<std::string> capabilityTypes;
            MstStatus status = instance->getCapabilityTypesList(capabilityTypes);
            if (status != MST_SUCCESS)
            {
                return status;
            }
            *numCapabilities = capabilityTypes.size();
            *capabilityTypesArray = new char*[capabilityTypes.size()];
            for (unsigned int i = 0; i < capabilityTypes.size(); i++)
            {
                (*capabilityTypesArray)[i] = new char[capabilityTypes[i].size() + 1];
                strncpy((*capabilityTypesArray)[i], capabilityTypes[i].c_str(), capabilityTypes[i].size());
                (*capabilityTypesArray)[i][capabilityTypes[i].size()] = '\0';
            }
            return MST_SUCCESS;
        }
        catch (const std::exception& e)
        {
            return MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES;
        }
    }

    MstStatus mstGetCapabilitiesByType(MstDevice mstDevice,
                                       const char* capabilityType,
                                       MstHcaCapabilityMetadata* capabilityMetadata)
    {
        if (!mstDevice || !capabilityMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        try
        {
            MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
            MstStatus status = instance->fillCapabilitiesMetadata(capabilityType, capabilityMetadata);
            return status;
        }
        catch (const std::exception& e)
        {
            return MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES;
        }
    }

    MstStatus mstFreeHcaCapabilitiesArray(char** capabilityNamesArray, unsigned int numCapabilities)
    {
        if (!capabilityNamesArray)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        for (unsigned int i = 0; i < numCapabilities; i++)
        {
            if (capabilityNamesArray[i])
            {
                delete[] capabilityNamesArray[i];
                capabilityNamesArray[i] = nullptr;
            }
        }
        delete[] capabilityNamesArray;
        return MST_SUCCESS;
    }

    MstStatus
      mstInitHcaCapabilityMap(MstDevice mstDevice, const char* capabilityType, MstHcaCapabilityMap* capabilityMap)
    {
        if (!mstDevice || !capabilityType || !capabilityMap)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->initHcaCapabilityMap(capabilityType, capabilityMap);
    }

    MstStatus mstQueryHcaCapability(MstDevice mstDevice,
                                    const char* capabilityType,
                                    MstHcaCapabilityMap* capabilityMap,
                                    MstCapabilityMode capabilityMode,
                                    uint16_t functionId,
                                    MstFunctionIdType functionIdType,
                                    MstOtherFunction otherFunction)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->queryHcaCapability(
          capabilityType, capabilityMap, capabilityMode, functionId, functionIdType, otherFunction);
    }

    MstStatus mstSetHcaCapability(MstDevice mstDevice,
                                  const char* capabilityType,
                                  MstHcaCapabilityMap* capabilityMap,
                                  MstCapabilityMode capabilityMode,
                                  uint16_t functionId,
                                  MstFunctionIdType functionIdType,
                                  MstOtherFunction otherFunction)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->setHcaCapability(
          capabilityType, capabilityMap, capabilityMode, functionId, functionIdType, otherFunction);
    }

    MstStatus mstFreeHcaCapabilityMap(MstHcaCapabilityMap* capabilityMap)
    {
        if (!capabilityMap)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        if (capabilityMap->capabilities)
        {
            delete[] capabilityMap->capabilities;
        }
        capabilityMap->numberOfCapabilities = 0;
        capabilityMap->capabilities = nullptr;
        return MST_SUCCESS;
    }

    MstStatus mstFreeHcaCapabilitiesMetadata(MstHcaCapabilityMetadata* capabilityMetadata)
    {
        if (!capabilityMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        if (capabilityMetadata->fields)
        {
            delete[] capabilityMetadata->fields;
            capabilityMetadata->fields = nullptr;
        }
        capabilityMetadata->numberOfFields = 0;
        return MST_SUCCESS;
    }

    MstStatus mstGetCapabilityValue(MstDevice mstDevice,
                                    MstHcaCapabilityMap* capabilityMap,
                                    const char* capabilityName,
                                    uint32_t* capabilityValue)
    {
        if (!mstDevice || !capabilityMap || !capabilityName)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getCapabilityValue(capabilityMap, capabilityName, capabilityValue);
    }

    MstStatus mstSetCapabilityValue(MstDevice mstDevice,
                                    MstHcaCapabilityMap* capabilityMap,
                                    const char* capabilityName,
                                    uint32_t capabilityValue)
    {
        if (!mstDevice || !capabilityMap || !capabilityName)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->setCapabilityValue(capabilityMap, capabilityName, capabilityValue);
    }
} // extern "C"