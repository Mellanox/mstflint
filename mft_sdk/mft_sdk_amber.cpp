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

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include "mft_sdk/mft_sdk_amber.h"
#include "mft_sdk/mft_sdk_class.hpp"

namespace
{

bool amberContextHas(const MstAmberContext* context, size_t memberEnd)
{
    return context && context->size >= memberEnd;
}

std::string amberContextPort(const MstAmberContext* context)
{
    if (!amberContextHas(context, offsetof(MstAmberContext_t, label_port) + sizeof(context->label_port)))
    {
        return std::string();
    }
    return std::string(context->label_port, strnlen(context->label_port, MST_AMBER_PORT_MAX_LENGTH));
}

// Bounds sheet_count against AMBER_SHEET_ALL so a mismatched count can't read past sheet_ids.
bool amberContextSheetCountValid(const MstAmberContext* context)
{
    if (!amberContextHas(context, offsetof(MstAmberContext_t, sheet_ids) + sizeof(context->sheet_ids)) ||
        context->sheet_ids == nullptr)
    {
        return true;
    }
    return context->sheet_count <= static_cast<unsigned int>(AMBER_SHEET_ALL);
}

// NULL/absent sheet_ids means "every sheet", not an error; each sheet is validated later in
// MlxlinkAmBerCollector::setSheetsToDump().
std::vector<unsigned int> amberContextSheets(const MstAmberContext* context)
{
    std::vector<unsigned int> sheets;
    if (!amberContextHas(context, offsetof(MstAmberContext_t, sheet_ids) + sizeof(context->sheet_ids)) ||
        context->sheet_ids == nullptr)
    {
        return sheets;
    }

    for (unsigned int i = 0; i < context->sheet_count; ++i)
    {
        sheets.push_back(context->sheet_ids[i]);
    }
    return sheets;
}

bool amberCountFits(size_t count, size_t elementSize)
{
    return count <= std::numeric_limits<unsigned int>::max() &&
           count <= std::numeric_limits<size_t>::max() / elementSize;
}

void amberCopyString(char* dest, const std::string& src, size_t destSize)
{
    strncpy(dest, src.c_str(), destSize - 1);
    dest[destSize - 1] = '\0';
}

} // namespace

void MftSdk::applyAmberSheetSelection(const std::vector<unsigned int>& sheets)
{
    // Cleared first — the SDK instance is reused across calls, so a second call would otherwise
    // append onto the first's selection.
    _mstMlxLinkSdkInstance->_userInput._amberPagesStr.clear();
    for (unsigned int sheet : sheets)
    {
        _mstMlxLinkSdkInstance->_userInput._amberPagesStr.push_back(std::to_string(sheet));
    }
}

MstStatus MftSdk::getAmberJson(const std::string& port, const std::vector<unsigned int>& sheets, char** jsonOut)
{
    if (!jsonOut)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    *jsonOut = nullptr;
    if (initMlxLinkSdk(MlxLinkInitMode::NONE, port) != MST_SUCCESS)
    {
        return _lastError.status;
    }

    clearError();
    applyAmberSheetSelection(sheets);

    try
    {
        std::string json = _mstMlxLinkSdkInstance->collectAmberJson();

        char* buffer = static_cast<char*>(malloc(json.size() + 1));
        if (!buffer)
        {
            return MST_ERROR_FAILED_TO_ALLOCATE_MEMORY;
        }
        memcpy(buffer, json.c_str(), json.size() + 1);
        *jsonOut = buffer;
    }
    catch (const std::exception& e)
    {
        setLastError(MST_ERROR_FAILED_TO_COLLECT_AMBER, e.what());
    }
    return _lastError.status;
}

MstStatus
  MftSdk::getAmberReport(const std::string& port, const std::vector<unsigned int>& sheets, MstAmberReport* report)
{
    if (!report)
    {
        return MST_ERROR_INVALID_ARGUMENT;
    }
    report->ports = nullptr;
    report->port_count = 0;
    amberCopyString(report->amber_version, AMBER_VERSION, MST_AMBER_VERSION_MAX);
    if (initMlxLinkSdk(MlxLinkInitMode::NONE, port) != MST_SUCCESS)
    {
        return _lastError.status;
    }

    clearError();
    applyAmberSheetSelection(sheets);

    try
    {
        const std::vector<AmberPortReport> portReports = _mstMlxLinkSdkInstance->collectAmberReport();

        for (const AmberPortReport& portReport : portReports)
        {
            if (!amberCountFits(portReport.fields.size(), sizeof(MstAmberField)))
            {
                setLastError(MST_ERROR_FAILED_TO_ALLOCATE_MEMORY, "field count overflows allocation size");
                return _lastError.status;
            }
        }
        if (!amberCountFits(portReports.size(), sizeof(MstAmberPort)))
        {
            setLastError(MST_ERROR_FAILED_TO_ALLOCATE_MEMORY, "port count overflows allocation size");
            return _lastError.status;
        }

        if (portReports.empty())
        {
            return _lastError.status;
        }

        report->ports = static_cast<MstAmberPort*>(calloc(portReports.size(), sizeof(MstAmberPort)));
        if (!report->ports)
        {
            return MST_ERROR_FAILED_TO_ALLOCATE_MEMORY;
        }
        report->port_count = static_cast<unsigned int>(portReports.size());

        for (size_t p = 0; p < portReports.size(); ++p)
        {
            const AmberPortReport& portReport = portReports[p];
            MstAmberPort& outPort = report->ports[p];

            amberCopyString(outPort.label_port, portReport.port, MST_AMBER_PORT_MAX_LENGTH);

            const size_t n = portReport.fields.size();
            if (n == 0)
            {
                continue;
            }

            outPort.fields = static_cast<MstAmberField*>(malloc(n * sizeof(MstAmberField)));
            if (!outPort.fields)
            {
                mstFreeAmberReport(report);
                return MST_ERROR_FAILED_TO_ALLOCATE_MEMORY;
            }
            outPort.field_count = static_cast<unsigned int>(n);

            for (size_t i = 0; i < n; ++i)
            {
                outPort.fields[i].sheet_id = portReport.fields[i].sheet_id;
                amberCopyString(outPort.fields[i].field_name, portReport.fields[i].field_name,
                                MST_AMBER_FIELD_NAME_MAX);
                amberCopyString(outPort.fields[i].value, portReport.fields[i].value, MST_AMBER_VALUE_MAX);
            }
        }
    }
    catch (const std::exception& e)
    {
        mstFreeAmberReport(report);
        setLastError(MST_ERROR_FAILED_TO_COLLECT_AMBER, e.what());
    }
    return _lastError.status;
}

extern "C"
{
    MstStatus mstGetAmberJson(MstDevice mstDevice, const MstAmberContext* context, char** jsonOut)
    {
        if (!mstDevice || !jsonOut)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        if (!amberContextSheetCountValid(context))
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getAmberJson(amberContextPort(context), amberContextSheets(context), jsonOut);
    }

    MstStatus mstGetAmberReport(MstDevice mstDevice, const MstAmberContext* context, MstAmberReport* report)
    {
        if (!mstDevice || !report)
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }
        if (!amberContextSheetCountValid(context))
        {
            return MST_ERROR_INVALID_ARGUMENT;
        }

        MftSdk* instance = reinterpret_cast<MftSdk*>(mstDevice);
        return instance->getAmberReport(amberContextPort(context), amberContextSheets(context), report);
    }

    void mstFreeAmberReport(MstAmberReport* report)
    {
        if (report)
        {
            for (unsigned int p = 0; p < report->port_count; ++p)
            {
                free(report->ports[p].fields);
            }
            free(report->ports);
            report->ports = nullptr;
            report->port_count = 0;
        }
    }

} // extern "C"
