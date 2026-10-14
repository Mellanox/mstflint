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

namespace
{
// Every ConnectX reduced ADB spells the LTSSM hierarchy the same way, as they
// are all reduced from one family ADB, so one layout serves them all.
LtssmLayout connectxLayout(const string& adbFile)
{
    LtssmLayout layout;

    layout.adbFile = adbFile;
    layout.pcoreNode = "pcore_top_pcore_pxdp_xpl_top";
    layout.linkNode = "xpl_nv_xpl";
    layout.linkStatusNode = "link0_cr_link_status";
    layout.stateNode = "link0_pl_ltssm_state";
    layout.ringNode = "link0_dl_ltssm_dfd_logger_line";
    layout.loggerCtrlNode = "link0_dl_ltssm_dfd_logger_ctrl2";

    return layout;
}

LtssmLayout veraLayout(const string& adbFile)
{
    LtssmLayout layout;

    layout.adbFile = adbFile;
    layout.pcoreNode = "pcore_xpl_nv_xpl";
    layout.linkNode = "link";
    layout.linkStatusNode = "cr_link_status";
    layout.stateNode = "pl_ltssm_state";
    layout.ringNode = "dl_ltssm_dfd_logger_line";
    layout.loggerCtrlNode = "dl_ltssm_dfd_logger_ctrl2";

    return layout;
}
} // namespace

const char* const LtssmReader::ADB_ROOT_NODE = "ltssm_Nodes";

LtssmReader::LtssmReader(const string& dumpFile, const string& deviceName) :
    _dumpFile(dumpFile), _requestedDeviceName(deviceName), _hwDeviceId(0), _deviceType(DeviceUnknown)
{
}

void LtssmReader::load()
{
    resolveDevice();
    loadLayout();
    loadAdb();
}

void LtssmReader::resolveDevice()
{
    u_int32_t value;

    if (!_requestedDeviceName.empty())
    {
        _deviceType = dm_dev_str2type(_requestedDeviceName.c_str());
        if (_deviceType == DeviceUnknown)
        {
            throw LtssmTraceException("Unknown device type: " + _requestedDeviceName);
        }
        _hwDeviceId = dm_get_hw_dev_id(_deviceType);

        return;
    }

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

void LtssmReader::loadLayout()
{
    switch (_deviceType)
    {
        case DeviceConnectX8:
            _layout = connectxLayout("connectx8_ltssm.adb");
            break;

        case DeviceConnectX8_Pure_PCIe_Switch:
            _layout = connectxLayout("connectx8_pure_pcie_switch_ltssm.adb");
            break;

        case DeviceConnectX9:
            _layout = connectxLayout("connectx9_ltssm.adb");
            break;

        case DeviceConnectX9_Pure_PCIe_Switch:
            _layout = connectxLayout("connectx9_pure_pcie_switch_ltssm.adb");
            break;

        case DeviceVera:
            _layout = veraLayout("vera_reduced_ltssm.adb");
            break;

        default:
            throw LtssmTraceException(string("No LTSSM layout for device: ") + deviceName());
    }
}

string LtssmReader::adbPath() const
{
    const string dbDirName = "ltssm_dbs";

    return string(DATA_PATH) + "/" + dbDirName + "/" + _layout.adbFile;
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
    char path[256];

    snprintf(path, sizeof(path), "%s[%u].%s[%u]", _layout.pcoreNode.c_str(), pcore, _layout.linkNode.c_str(), link);

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

const LtssmLayout& LtssmReader::layout() const
{
    return _layout;
}
