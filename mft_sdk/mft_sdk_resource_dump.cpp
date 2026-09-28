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
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include "mft_sdk/mft_sdk.h"
#include "mft_sdk/mft_sdk_class.hpp"
#include "dump_command.h"
#include "query_command.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"
#include "resource_dump_api.h"
#include "resource_dump_segments.h"

using namespace mft::resource_dump;

namespace
{
void convertMenuRecord(const menu_record_data& source, MstResourceMenuRecord* destination)
{
    destination->segmentType = source.segment_type;
    std::memcpy(destination->segmentName, source.segment_name, MST_RESOURCE_DUMP_NAME_LENGTH);
    std::memcpy(destination->index1Name, source.index1_name, MST_RESOURCE_DUMP_NAME_LENGTH);
    std::memcpy(destination->index2Name, source.index2_name, MST_RESOURCE_DUMP_NAME_LENGTH);
    destination->segmentName[MST_RESOURCE_DUMP_NAME_LENGTH] = '\0';
    destination->index1Name[MST_RESOURCE_DUMP_NAME_LENGTH] = '\0';
    destination->index2Name[MST_RESOURCE_DUMP_NAME_LENGTH] = '\0';
    destination->supportIndex1 = source.support_index1;
    destination->mustHaveIndex1 = source.must_have_index1;
    destination->supportIndex2 = source.support_index2;
    destination->mustHaveIndex2 = source.must_have_index2;
    destination->supportNumOfObj1 = source.support_num_of_obj1;
    destination->mustHaveNumOfObj1 = source.must_have_num_of_obj1;
    destination->numOfObj1SupportsAll = source.num_of_obj1_supports_all;
    destination->numOfObj1SupportsActive = source.num_of_obj1_supports_active;
    destination->supportNumOfObj2 = source.support_num_of_obj2;
    destination->mustHaveNumOfObj2 = source.must_have_num_of_obj2;
    destination->numOfObj2SupportsAll = source.num_of_obj2_supports_all;
    destination->numOfObj2SupportsActive = source.num_of_obj2_supports_active;
}

endianess_t toResourceDumpEndianess(MstResourceDumpEndianness endianness)
{
    return static_cast<endianess_t>(endianness);
}
} // namespace

device_attributes MftSdk::buildResourceDumpDeviceAttributes(uint16_t vhca)
{
    device_attributes deviceAttributes;
    deviceAttributes.device_name = _deviceIdentifier.c_str();
    deviceAttributes.vhca = vhca;
    // Memory mode needs the mkey fetcher, which the SDK deliberately does not link (see BUILD).
    deviceAttributes.rdma_name = nullptr;
    return deviceAttributes;
}

MstStatus MftSdk::translateResourceDumpReasonToMstStatus(uint16_t reason)
{
    switch (static_cast<ResourceDumpException::Reason>(reason))
    {
        case ResourceDumpException::Reason::OPEN_DEVICE_FAILED:
            return MST_ERROR_FAILED_TO_OPEN_DEVICE;
        case ResourceDumpException::Reason::SEND_REG_ACCESS_FAILED:
        case ResourceDumpException::Reason::WRONG_SEQUENCE_NUMBER:
            return MST_ERROR_FAILED_TO_SEND_ACCESS_REG;
        case ResourceDumpException::Reason::DEVICE_TYPE_UNSUPPORTED:
        case ResourceDumpException::Reason::MEM_MODE_NOT_SUPPORTED:
        case ResourceDumpException::Reason::TEXT_DATA_UNAVAILABLE:
            return MST_ERROR_NOT_SUPPORTED;
        case ResourceDumpException::Reason::BUFFER_TOO_SMALL:
            return MST_ERROR_INSUFFICIENT_BUFFER;
        default:
            return MST_ERROR_FAILED_TO_DUMP_RESOURCE;
    }
}

MstStatus MftSdk::setErrorFromResourceDumpException(const ResourceDumpException& exception)
{
    MstStatus status = translateResourceDumpReasonToMstStatus(static_cast<uint16_t>(exception.reason));
    setLastError(status, exception.what());
    return status;
}

/**
 * @brief Runs a dump command and hands back its data in the requested byte order.
 * Buffer mode is used for every flavor of dump, including the to-file one, so that the control segment
 * filter - which works on the command's stream - applies uniformly.
 */
MstStatus MftSdk::executeResourceDump(const MstResourceDumpRequest* request,
                                      MstResourceDumpEndianness endianness,
                                      std::string& dumpOut)
{
    clearError();
    if (!request)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "The resource dump request is NULL");
        return _lastError.status;
    }
    try
    {
        device_attributes deviceAttributes = buildResourceDumpDeviceAttributes(request->vhca);
        dump_request segmentParams;
        segmentParams.resource_id = request->resourceId;
        segmentParams.index1 = request->index1;
        segmentParams.index2 = request->index2;
        segmentParams.num_of_obj1 = request->numOfObj1;
        segmentParams.num_of_obj2 = request->numOfObj2;

        DumpCommand dumpCommand{_mf, deviceAttributes, segmentParams, request->depth};
        dumpCommand.execute();

        dumpOut = get_dump_data(dumpCommand, request->stripControlSegments, toResourceDumpEndianess(endianness));
    }
    catch (const ResourceDumpException& rde)
    {
        return setErrorFromResourceDumpException(rde);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_DUMP_RESOURCE, std::string("Failed to dump resource: ") + e.what());
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::getResourceMenu(MstResourceDumpEndianness endianness, MstResourceMenu* menu)
{
    clearError();
    if (!menu)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "The resource menu is NULL");
        return _lastError.status;
    }
    menu->numberOfRecords = 0;
    menu->records = nullptr;
    try
    {
        QueryCommand queryCommand{_mf, buildResourceDumpDeviceAttributes(MST_RESOURCE_DUMP_OWN_VHCA)};
        queryCommand.execute();

        std::string recordData = get_menu_data(queryCommand, toResourceDumpEndianess(endianness));
        uint16_t numberOfRecords = (uint16_t)(recordData.size() / sizeof(menu_record_data));
        if (numberOfRecords == 0)
        {
            return MST_SUCCESS;
        }
        menu->records = (MstResourceMenuRecord*)calloc(numberOfRecords, sizeof(MstResourceMenuRecord));
        if (!menu->records)
        {
            setLastError(MST_ERROR_FAILED_TO_ALLOCATE_MEMORY, "Failed to allocate the resource menu records");
            return _lastError.status;
        }
        for (uint16_t i = 0; i < numberOfRecords; i++)
        {
            // The records travel as bytes, so they are copied out rather than read in place.
            menu_record_data record;
            std::memcpy(&record, recordData.data() + i * sizeof(menu_record_data), sizeof(menu_record_data));
            convertMenuRecord(record, &menu->records[i]);
        }
        menu->numberOfRecords = numberOfRecords;
    }
    catch (const ResourceDumpException& rde)
    {
        return setErrorFromResourceDumpException(rde);
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_DUMP_RESOURCE, std::string("Failed to get the resource menu: ") + e.what());
        return _lastError.status;
    }
    return MST_SUCCESS;
}

MstStatus MftSdk::dumpResource(const MstResourceDumpRequest* request,
                               MstResourceDumpEndianness endianness,
                               MstResourceDumpData* dumpData)
{
    std::string dump;
    if (!dumpData)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "The resource dump result is NULL");
        return _lastError.status;
    }
    dumpData->data = nullptr;
    dumpData->size = 0;
    dumpData->endianness = endianness;

    MstStatus status = executeResourceDump(request, endianness, dump);
    if (status != MST_SUCCESS)
    {
        return status;
    }
    // Stripping the control segments can legitimately leave nothing behind; malloc(0) is allowed to
    // return NULL, so an empty dump would otherwise be reported as an allocation failure.
    if (dump.empty())
    {
        return MST_SUCCESS;
    }
    if (dump.size() > UINT32_MAX)
    {
        setLastError(
          MST_ERROR_FAILED_TO_DUMP_RESOURCE,
          "The resource dump is " + std::to_string(dump.size()) + " bytes, too large to report through a 32 bit size");
        return _lastError.status;
    }
    dumpData->data = (unsigned char*)malloc(dump.size());
    if (!dumpData->data)
    {
        setLastError(MST_ERROR_FAILED_TO_ALLOCATE_MEMORY, "Failed to allocate the resource dump buffer");
        return _lastError.status;
    }
    std::memcpy(dumpData->data, dump.data(), dump.size());
    dumpData->size = (uint32_t)dump.size();
    return MST_SUCCESS;
}

MstStatus MftSdk::dumpResourceToBuffer(const MstResourceDumpRequest* request,
                                       MstResourceDumpEndianness endianness,
                                       unsigned char* buffer,
                                       size_t bufferSize,
                                       size_t* dumpSize)
{
    std::string dump;
    if (!dumpSize)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "The resource dump size is NULL");
        return _lastError.status;
    }
    *dumpSize = 0;

    MstStatus status = executeResourceDump(request, endianness, dump);
    if (status != MST_SUCCESS)
    {
        return status;
    }
    // Reported even when the buffer is too small, so the caller can size a second call.
    *dumpSize = dump.size();
    // Stripping the control segments can legitimately leave nothing behind, and no buffer is too
    // small to hold nothing - not even the NULL one a size query passes.
    if (dump.empty())
    {
        return MST_SUCCESS;
    }
    if (!buffer || bufferSize < dump.size())
    {
        setLastError(MST_ERROR_INSUFFICIENT_BUFFER,
                     "The provided buffer is too small for the resource dump, " + std::to_string(dump.size()) +
                       " bytes are required");
        return _lastError.status;
    }
    std::memcpy(buffer, dump.data(), dump.size());
    return MST_SUCCESS;
}

MstStatus MftSdk::dumpResourceToFile(const MstResourceDumpRequest* request,
                                     MstResourceDumpEndianness endianness,
                                     const char* filename)
{
    std::string dump;
    if (!filename)
    {
        setLastError(MST_ERROR_INVALID_ARGUMENT, "The resource dump file name is NULL");
        return _lastError.status;
    }
    MstStatus status = executeResourceDump(request, endianness, dump);
    if (status != MST_SUCCESS)
    {
        return status;
    }
    std::ofstream dumpFile{filename, std::ofstream::binary};
    if (dumpFile.fail())
    {
        setLastError(MST_ERROR_FAILED_TO_DUMP_RESOURCE, std::string("Failed to open the dump file ") + filename);
        return _lastError.status;
    }
    dumpFile.write(dump.data(), dump.size());
    if (dumpFile.fail())
    {
        setLastError(MST_ERROR_FAILED_TO_DUMP_RESOURCE, std::string("Failed to write the dump file ") + filename);
        return _lastError.status;
    }
    return MST_SUCCESS;
}

// Pure C API Functions:
extern "C"
{
    MstStatus mstGetResourceMenu(MstDevice mstDevice, MstResourceDumpEndianness endianness, MstResourceMenu* menu)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getResourceMenu(endianness, menu);
    }

    MstStatus mstFreeResourceMenu(MstResourceMenu* menu)
    {
        if (!menu)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        free(menu->records);
        menu->records = NULL;
        menu->numberOfRecords = 0;
        return MST_SUCCESS;
    }

    MstStatus mstDumpResource(MstDevice mstDevice,
                              const MstResourceDumpRequest* request,
                              MstResourceDumpEndianness endianness,
                              MstResourceDumpData* dumpData)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->dumpResource(request, endianness, dumpData);
    }

    MstStatus mstFreeResourceDump(MstResourceDumpData* dumpData)
    {
        if (!dumpData)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        free(dumpData->data);
        dumpData->data = NULL;
        dumpData->size = 0;
        return MST_SUCCESS;
    }

    MstStatus mstDumpResourceToBuffer(MstDevice mstDevice,
                                      const MstResourceDumpRequest* request,
                                      MstResourceDumpEndianness endianness,
                                      unsigned char* buffer,
                                      size_t bufferSize,
                                      size_t* dumpSize)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->dumpResourceToBuffer(request, endianness, buffer, bufferSize, dumpSize);
    }

    MstStatus mstDumpResourceToFile(MstDevice mstDevice,
                                    const MstResourceDumpRequest* request,
                                    MstResourceDumpEndianness endianness,
                                    const char* filename)
    {
        if (!mstDevice)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->dumpResourceToFile(request, endianness, filename);
    }
} // extern "C"
