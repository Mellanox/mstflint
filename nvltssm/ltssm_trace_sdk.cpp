/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#include <string.h>
#include <new>
#include <string>

#include <nvltssm/ltssm_reader.h>
#include <nvltssm/ltssm_trace_exception.h>

#include "ltssm_trace_sdk.h"

using namespace std;

namespace
{
class LtssmTraceHandle
{
public:
    LtssmTraceHandle(const char* dumpFile, const char* deviceName) :
        reader(dumpFile, deviceName ? deviceName : ""), lastError()
    {
    }

    LtssmReader reader;
    string lastError;
};

LtssmTraceHandle* asHandle(ltssm_trace_handle_t handle)
{
    return reinterpret_cast<LtssmTraceHandle*>(handle);
}

char* duplicate(const string& value)
{
    char* copy = (char*)malloc(value.size() + 1);
    if (copy)
    {
        memcpy(copy, value.c_str(), value.size() + 1);
    }

    return copy;
}
} // namespace

enum ltssm_trace_result_t ltssm_trace_open(const char* dump_file, const char* device_name, ltssm_trace_handle_t* handle)
{
    if (!handle)
    {
        return LTSSM_TRACE_BAD_PARAM;
    }

    *handle = NULL;

    if (!dump_file)
    {
        return LTSSM_TRACE_BAD_PARAM;
    }

    LtssmTraceHandle* traceHandle = new (std::nothrow) LtssmTraceHandle(dump_file, device_name);
    *handle = traceHandle;
    if (!traceHandle)
    {
        return LTSSM_TRACE_ERROR;
    }

    try
    {
        traceHandle->reader.load();
    }
    catch (LtssmTraceException& exp)
    {
        traceHandle->lastError = exp.what();
        return LTSSM_TRACE_ERROR;
    }
    catch (std::exception& exp)
    {
        traceHandle->lastError = exp.what();
        return LTSSM_TRACE_ERROR;
    }

    return LTSSM_TRACE_OK;
}

enum ltssm_trace_result_t ltssm_trace_get_device_info(ltssm_trace_handle_t handle, ltssm_trace_device_info_t* info)
{
    LtssmTraceHandle* traceHandle = asHandle(handle);
    if (!traceHandle || !info)
    {
        return LTSSM_TRACE_BAD_PARAM;
    }

    const LtssmLayout& layout = traceHandle->reader.layout();

    info->hw_device_id = traceHandle->reader.hwDeviceId();
    info->device_name = traceHandle->reader.deviceName();
    info->pcore_node = layout.pcoreNode.c_str();
    info->link_node = layout.linkNode.c_str();
    info->link_status_node = layout.linkStatusNode.c_str();
    info->state_node = layout.stateNode.c_str();
    info->ring_node = layout.ringNode.c_str();
    info->logger_ctrl_node = layout.loggerCtrlNode.c_str();

    return LTSSM_TRACE_OK;
}

enum ltssm_trace_result_t ltssm_trace_read_link(ltssm_trace_handle_t handle,
                                                uint32_t pcore,
                                                uint32_t link,
                                                ltssm_trace_field_t** fields,
                                                uint32_t* num_of_fields)
{
    LtssmTraceHandle* traceHandle = asHandle(handle);
    if (!traceHandle || !fields || !num_of_fields)
    {
        return LTSSM_TRACE_BAD_PARAM;
    }

    *fields = NULL;
    *num_of_fields = 0;

    LtssmReader::FieldMap readFields;
    try
    {
        traceHandle->reader.readLink(pcore, link, readFields);
    }
    catch (LtssmTraceException& exp)
    {
        traceHandle->lastError = exp.what();
        return LTSSM_TRACE_ERROR;
    }
    catch (std::exception& exp)
    {
        traceHandle->lastError = exp.what();
        return LTSSM_TRACE_ERROR;
    }

    ltssm_trace_field_t* buffer = (ltssm_trace_field_t*)calloc(readFields.size(), sizeof(ltssm_trace_field_t));
    if (!buffer)
    {
        traceHandle->lastError = "Failed to allocate the field array";
        return LTSSM_TRACE_ERROR;
    }

    uint32_t index = 0;
    for (LtssmReader::FieldMap::iterator it = readFields.begin(); it != readFields.end(); it++)
    {
        buffer[index].name = duplicate(it->first);
        if (!buffer[index].name)
        {
            ltssm_trace_free_fields(buffer, index);
            traceHandle->lastError = "Failed to allocate a field name";
            return LTSSM_TRACE_ERROR;
        }
        buffer[index].value = it->second.value;
        buffer[index].address = it->second.dwordAddr;
        buffer[index].start_bit = it->second.startBit;
        buffer[index].size = it->second.size;
        index++;
    }

    *fields = buffer;
    *num_of_fields = index;

    return LTSSM_TRACE_OK;
}

void ltssm_trace_free_fields(ltssm_trace_field_t* fields, uint32_t num_of_fields)
{
    if (!fields)
    {
        return;
    }

    for (uint32_t index = 0; index < num_of_fields; index++)
    {
        free((void*)fields[index].name);
    }
    free(fields);
}

void ltssm_trace_close(ltssm_trace_handle_t handle)
{
    delete asHandle(handle);
}

const char* ltssm_trace_get_error(ltssm_trace_handle_t handle)
{
    LtssmTraceHandle* traceHandle = asHandle(handle);

    return traceHandle ? traceHandle->lastError.c_str() : "";
}
