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

#include <cstdint>
#include <memory>
#include <utility>
#include <tuple>
#include "mft_sdk/mft_sdk.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "mlxreg/mlxreg_sdk/mlxreg_sdk.h"

void MftSdk::initMlxregSdkInstance()
{
#ifdef MFT_SDK_EXTERNAL
    _mlxregSdkInstance = std::unique_ptr<PrmRegSdk>(new PrmRegSdk(_deviceIdentifier.c_str()));
#else
    _mlxregSdkInstance = std::unique_ptr<PrmRegSdkInt>(new PrmRegSdkInt(_deviceIdentifier.c_str()));
#endif
}

/**
 * @brief Initializes an instance of the mlxreg SDK. if an instance already exists, use it and set the given attributes.
 * @param regName The name of the register.
 * @param method The method of the register.
 * @return The status of the operation.
 */
MstStatus MftSdk::initMlxregSdk(const char* regName, const MstPrmRegAccessMethod method)
{
    clearError();
    if (_mlxregSdkInstance == nullptr)
    {
        initMlxregSdkInstance();
        _mfiles.push_back(_mlxregSdkInstance->getMFile());
    }
    _mlxregSdkInstance->initPrmCommand(regName, (uint32_t)method, "");
    return _lastError.status;
}

MstStatus MftSdk::initMlxregSdkById(uint16_t regId, MstPrmRegAccessMethod method)
{
    clearError();
    if (_mlxregSdkInstance == nullptr)
    {
        initMlxregSdkInstance();
        _mfiles.push_back(_mlxregSdkInstance->getMFile());
    }
    _mlxregSdkInstance->initPrmCommand(regId, (uint32_t)method);
    return _lastError.status;
}

MstStatus MftSdk::translateMlxregSDKErrorToMstStatus(int32_t errorCode)
{
    switch (errorCode)
    {
        case ERR_CODE_SUCCESS:
            return MST_SUCCESS;
        case ERR_CODE_FAILD_TO_OPEN_MST_DEV:
            return MST_ERROR_FAILED_TO_OPEN_DEVICE;
        case ERR_CODE_FAILD_TO_SEND_ACCESS_REG:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
        case ERR_CODE_FAILD_TO_INIT_REG_LIB:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
        case ERR_CODE_FAILD_TO_FIND_REG_NODE:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
        case ERR_CODE_FAILD_TO_PARSE_FIELD:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
        case ERR_CODE_INVALID_FIELD_ARG:
            return MST_ERROR_INVALID_ARGUMENT;
        case ERR_CODE_INVALID_METHOD:
            return MST_ERROR_INVALID_ARGUMENT;
        case ERR_CODE_FAILD_TO_PARSE_PARAMS:
            return MST_ERROR_INVALID_ARGUMENT;
        default:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
    }
}

MstStatus MftSdk::setErrorFromMlxregSDKError(int32_t errorCode)
{
    MstStatus status = translateMlxregSDKErrorToMstStatus(errorCode);
    setLastError(status, _mlxregSdkInstance->getErrorMessage());
    _syndromeCode = (status != MST_SUCCESS) ? _mlxregSdkInstance->getSyndromeCode() : 0;
    return status;
}

MstStatus MftSdk::sendPRMRegister(MstPrmRegisterMap* registerMap, const MstPrmRegAccessMethod method)
{
    initMlxregSdk("", method);
    int32_t errorCode = _mlxregSdkInstance->performRegRequestUsingMap((void*)registerMap);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::setPRMRegisterField(MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t value)
{
    initMlxregSdk();
    int32_t errorCode = _mlxregSdkInstance->setField(fieldName, value, (void*)registerMap);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::getPRMRegisterField(MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t* value)
{
    initMlxregSdk();
    int32_t errorCode = _mlxregSdkInstance->getField(fieldName, value, (void*)registerMap);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::sendRawPRMRegister(uint16_t regId, MstPrmRegAccessMethod method, void* data, uint32_t dataSize)
{
    initMlxregSdkById(regId, method);
    int32_t errorCode = _mlxregSdkInstance->performRawRegRequest(data, dataSize);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::showAllPRMRegisters(std::vector<std::string>& registers)
{
    initMlxregSdk();
    int32_t errorCode = _mlxregSdkInstance->showAllRegisters(registers);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::initRegisterMap(const char* regName, MstPrmRegisterMap* registerMap)
{
    if (!regName || !registerMap)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    initMlxregSdk(regName);
    int32_t errorCode = _mlxregSdkInstance->getRegisterFields(regName, registerMap);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::getRegisterMetadata(const char* regName, MstPrmRegisterMetadata* registerMetadata)
{
    if (!regName || !registerMetadata)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    initMlxregSdk(regName);
    int32_t errorCode = _mlxregSdkInstance->getRegisterMetadata(regName, registerMetadata);
    return setErrorFromMlxregSDKError(errorCode);
}

MstStatus MftSdk::getRegisterExpandedMetadata(const char* regName, MstPrmRegisterExpandedMetadata* registerMetadata)
{
    if (!regName || !registerMetadata)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    initMlxregSdk(regName);
    int32_t errorCode = _mlxregSdkInstance->getRegisterExpandedMetadata(regName, registerMetadata);
    return setErrorFromMlxregSDKError(errorCode);
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstSendRawPRMRegister(MstDevice mstDevice,
                                    const uint16_t regId,
                                    const MstPrmRegAccessMethod method,
                                    void* data,
                                    const uint32_t dataSize)
    {
        if (!mstDevice || !data)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->sendRawPRMRegister(regId, method, data, dataSize);
    }

    MstStatus mstSendPRMRegister(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const MstPrmRegAccessMethod method)
    {
        if (!mstDevice || !registerMap)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->sendPRMRegister(registerMap, method);
    }

    MstStatus
      mstSetPRMRegisterField(MstDevice mstDevice, MstPrmRegisterMap* registerMap, const char* fieldName, uint32_t value)
    {
        if (!mstDevice || !registerMap || !fieldName)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->setPRMRegisterField(registerMap, fieldName, value);
    }

    MstStatus mstGetPRMRegisterField(MstDevice mstDevice,
                                     MstPrmRegisterMap* registerMap,
                                     const char* fieldName,
                                     uint32_t* value)
    {
        if (!mstDevice || !registerMap || !fieldName || !value)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getPRMRegisterField(registerMap, fieldName, value);
    }

    MstStatus mstShowAllPRMRegisters(MstDevice mstDevice, char*** registerNamesArray, unsigned int* numRegisters)
    {
        std::vector<std::string> registerVector;
        if (!mstDevice || !registerNamesArray || !numRegisters)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        MstStatus status = instance->showAllPRMRegisters(registerVector);
        if (status != MST_SUCCESS)
        {
            return status;
        }

        *numRegisters = registerVector.size();
        *registerNamesArray = (char**)malloc(sizeof(char*) * registerVector.size());
        if (!*registerNamesArray)
        {
            return MST_ERROR_FAILED_TO_ALLOCATE_MEMORY;
        }
        for (unsigned int i = 0; i < registerVector.size(); i++)
        {
            (*registerNamesArray)[i] = (char*)malloc(registerVector[i].size() + 1);
            if (!(*registerNamesArray)[i])
            {
                for (unsigned int j = 0; j < i; j++)
                {
                    free((*registerNamesArray)[j]);
                }
                free(*registerNamesArray);
                return MST_ERROR_FAILED_TO_ALLOCATE_MEMORY;
            }
            std::memcpy((*registerNamesArray)[i], registerVector[i].c_str(), registerVector[i].size() + 1);
        }
        return MST_SUCCESS;
    }

    MstStatus mstFreePRMRegisterNamesArray(char** registerNamesArray, unsigned int numRegisters)
    {
        if (!registerNamesArray)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        for (unsigned int i = 0; i < numRegisters; i++)
        {
            free(registerNamesArray[i]);
        }
        free(registerNamesArray);
        return MST_SUCCESS;
    }

    MstStatus mstInitRegisterMap(MstDevice mstDevice, const char* regName, MstPrmRegisterMap* registerMap)
    {
        if (!mstDevice || !regName || !registerMap)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->initRegisterMap(regName, registerMap);
    }

    MstStatus mstFreePrmRegisterMap(MstPrmRegisterMap* registerMap)
    {
        if (!registerMap)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        free_register_map(registerMap);
        return MST_SUCCESS;
    }

    MstStatus mstGetRegisterMetadata(MstDevice mstDevice, const char* regName, MstPrmRegisterMetadata* registerMetadata)
    {
        if (!mstDevice || !regName || !registerMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getRegisterMetadata(regName, registerMetadata);
    }

    MstStatus mstFreePrmRegisterMetadata(MstPrmRegisterMetadata* registerMetadata)
    {
        if (!registerMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        free_register_metadata((MstPrmRegisterMetadata*)registerMetadata);
        return MST_SUCCESS;
    }

    MstStatus mstGetRegisterExpandedMetadata(MstDevice mstDevice,
                                             const char* regName,
                                             MstPrmRegisterExpandedMetadata* registerMetadata)
    {
        if (!mstDevice || !regName || !registerMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getRegisterExpandedMetadata(regName, registerMetadata);
    }

    MstStatus mstFreePrmRegisterExpandedMetadata(MstPrmRegisterExpandedMetadata* registerMetadata)
    {
        if (!registerMetadata)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        free_register_field_expanded_metadata(registerMetadata);
        return MST_SUCCESS;
    }
} // extern "C"