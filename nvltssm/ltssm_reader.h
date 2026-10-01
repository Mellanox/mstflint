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

#ifndef LTSSM_READER_H
#define LTSSM_READER_H

#include <memory>
#include <string>

#include <common/compatibility.h>
#include <dev_mgt/tools_dev_types.h>
#include <mlxparsebin/mlxparsebin_lib.h>

// The node names one device's reduced ADB spells the LTSSM hierarchy with, read
// from that device's JSON because each reduced ADB inherits the naming of the
// family ADB it was reduced from.
struct LtssmLayout
{
    std::string pcoreNode;
    std::string linkNode;
    std::string linkStatusNode;
    std::string stateNode;
    std::string ringNode;
    std::string loggerCtrlNode;
};

// Reads the LTSSM registers of one PCIe link out of an mstdump or raw dump,
// using the reduced ADB installed for the device the dump was taken from. The
// reduced ADB carries the absolute addresses, so no per-device offset lives here.
class LtssmReader
{
public:
    typedef MlxParseBinLib::FieldDataMap FieldMap;

    // An empty deviceName reads the device id out of the dump. A dump whose
    // address range carries no device id has to be told which device it is.
    LtssmReader(const std::string& dumpFile, const std::string& deviceName);

    void load();
    void readLink(u_int32_t pcore, u_int32_t link, FieldMap& fields);

    u_int32_t hwDeviceId() const;
    dm_dev_id_t deviceType() const;
    const char* deviceName() const;
    const LtssmLayout& layout() const;

private:
    static const u_int32_t HW_DEVICE_ID_START_BIT = 0;
    static const u_int32_t HW_DEVICE_ID_SIZE = 16;
    static const char* const ADB_ROOT_NODE;

    void resolveDevice();
    void loadLayout();
    void loadAdb();
    std::string adbPath() const;
    std::string linkPath(u_int32_t pcore, u_int32_t link) const;

    std::string _dumpFile;
    std::string _requestedDeviceName;
    u_int32_t _hwDeviceId;
    dm_dev_id_t _deviceType;
    LtssmLayout _layout;
    std::unique_ptr<MlxParseBinLib> _parser;
};

#endif // LTSSM_READER_H
