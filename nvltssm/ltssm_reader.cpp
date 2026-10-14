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

#include <stdio.h>
#include <stdlib.h>

#include <common/bit_slice.h>
#include <dev_mgt/tools_dev_types.h>
#include <mlxparsebin/mlxparsebin_exception.h>
#include <mtcr_com_defs.h>

#include "ltssm_reader.h"
#include "ltssm_trace_exception.h"

using namespace std;

const char* const LtssmReader::ADB_ROOT_NODE = "ltssm_Nodes";
const char* const LtssmReader::PCORE_LEVEL_FIELD = "pcore_top_pcore_pxdp_xpl_top";
const char* const LtssmReader::LINK_LEVEL_FIELD = "xpl_nv_xpl";

LtssmReader::LtssmReader(const string& dumpFile) : _dumpFile(dumpFile), _hwDeviceId(0), _deviceType(DeviceUnknown) {}

void LtssmReader::load()
{
    resolveDevice();
    loadAdb();
}

void LtssmReader::resolveDevice()
{
    u_int32_t value;

    try
    {
        value = MlxParseBinLib::readDword(_dumpFile, HW_ID_ADDR);
    }
    catch (MlxParseBinException& exp)
    {
        throw LtssmTraceException(string("Failed to read the device id from the dump: ") + exp.what());
    }

    _hwDeviceId = EXTRACT(value, HW_DEVICE_ID_START_BIT, HW_DEVICE_ID_SIZE);
    if (dm_get_device_id_offline(_hwDeviceId, 0, &_deviceType) != ME_OK)
    {
        char msg[128];
        snprintf(msg, sizeof(msg), "Unsupported device, hw device id 0x%x", _hwDeviceId);
        throw LtssmTraceException(msg);
    }
}

string LtssmReader::adbPath() const
{
    const string dbDirName = "ltssm_dbs";
    string fileName;

    switch (_deviceType)
    {
        case DeviceConnectX8:
            fileName = "connectx8_ltssm.adb";
            break;

        case DeviceConnectX8_Pure_PCIe_Switch:
            fileName = "connectx8_pure_pcie_switch_ltssm.adb";
            break;

        case DeviceConnectX9:
            fileName = "connectx9_ltssm.adb";
            break;

        case DeviceConnectX9_Pure_PCIe_Switch:
            fileName = "connectx9_pure_pcie_switch_ltssm.adb";
            break;

        default:
            throw LtssmTraceException(string("No LTSSM layout for device: ") + deviceName());
    }

    return string(DATA_PATH) + "/" + dbDirName + "/" + fileName;
}

void LtssmReader::loadAdb()
{
    MlxParseBinLib::Options options;
    options.adbFile = adbPath();
    options.binFile = _dumpFile;
    options.adbRootNode = ADB_ROOT_NODE;

    unique_ptr<MlxParseBinLib> parser(new MlxParseBinLib(options));
    try
    {
        parser->load();
    }
    catch (MlxParseBinException& exp)
    {
        throw LtssmTraceException(exp.what());
    }
    catch (AdbException& exp)
    {
        throw LtssmTraceException(exp.what_s());
    }

    _parser = std::move(parser);
}

void LtssmReader::readLink(u_int32_t pcore, u_int32_t link, FieldMap& fields)
{
    if (!_parser)
    {
        throw LtssmTraceException("The dump was not loaded");
    }

    string filterPath = linkPath(pcore, link);

    FieldMap fullNamedFields;
    try
    {
        _parser->printDump(fullNamedFields, filterPath);
    }
    catch (MlxParseBinException& exp)
    {
        throw LtssmTraceException(exp.what());
    }
    catch (AdbException& exp)
    {
        throw LtssmTraceException(exp.what_s());
    }

    string prefix = string(ADB_ROOT_NODE) + "." + filterPath + ".";
    for (FieldMap::const_iterator it = fullNamedFields.begin(); it != fullNamedFields.end(); it++)
    {
        bool hasPrefix = it->first.compare(0, prefix.size(), prefix) == 0;
        fields[hasPrefix ? it->first.substr(prefix.size()) : it->first] = it->second;
    }

    if (fields.empty())
    {
        throw LtssmTraceException("The dump holds no LTSSM data for the requested link");
    }
}

string LtssmReader::linkPath(u_int32_t pcore, u_int32_t link) const
{
    char path[128];

    snprintf(path, sizeof(path), "%s[%u].%s[%u]", PCORE_LEVEL_FIELD, pcore, LINK_LEVEL_FIELD, link);

    return string(path);
}

u_int32_t LtssmReader::hwDeviceId() const
{
    return _hwDeviceId;
}

dm_dev_id_t LtssmReader::deviceType() const
{
    return _deviceType;
}

const char* LtssmReader::deviceName() const
{
    return dm_dev_type2str(_deviceType);
}
