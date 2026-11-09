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

#ifndef MST_SERVER_SERVICE_IMPL_H
#define MST_SERVER_SERVICE_IMPL_H

#include "mst_server/service/MstServerService.h"
#include <unordered_map>
#include <mutex>
#include <memory>

// Forward declare mfile from mtcr.h
struct mfile_t;
typedef struct mfile_t mfile;
using namespace mstserver;

// One entry per device name, shared across all clients.
struct DeviceData
{
    std::string device_name;
    mfile* mf;
    uint32_t device_type;

    // Serializes every mtcr call on this handle. mtcr guards its gateway
    // sequences with flock() on mfile::file_lock_descriptor, but an flock is
    // held per open file description, so two threads sharing one handle both
    // pass it: only the server can keep them apart.
    std::mutex op_mutex;

    DeviceData() : mf(nullptr), device_type(0) {}
    // Closes mf. Defined in the .cpp so this header need not include mtcr.
    ~DeviceData();

    DeviceData(const DeviceData&) = delete;
    DeviceData& operator=(const DeviceData&) = delete;
};

class MstServerServiceImpl : public MstServerService
{
public:
    MstServerServiceImpl();
    virtual ~MstServerServiceImpl();

    // System Operations
    Result<std::string> GetVersion() override;
    Result<std::vector<std::string>> GetDevices() override;
    Result<uint32_t> GetCapabilities() override;

    // Device Management
    Result<bool> OpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address) override;
    Result<bool> CloseDevice(const std::string& device_name) override;

    // Device Information
    Result<uint32_t> GetDeviceId(const std::string& device_name) override;
    Result<uint32_t> GetPciDeviceId(const std::string& device_name) override;

    // Register Access
    Result<uint32_t> Read32(const std::string& device_name, uint64_t offset) override;
    Result<bool> Write32(const std::string& device_name, uint64_t offset, uint32_t value) override;
    Result<bool> ReadBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) override;
    Result<bool> WriteBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) override;
    Result<bool> SetAddressSpace(const std::string& device_name, int space) override;
    Result<bool> PciChange(const std::string& device_name) override;

    // I2C Operations
    Result<I2CScanResult> ScanI2C(const std::string& device_name) override;
    Result<bool> SetI2CSecondary(const std::string& device_name, uint8_t address) override;
    Result<std::vector<uint8_t>>
      ReadBlock(const std::string& device_name, I2CAddress address, uint32_t offset, uint32_t size) override;
    Result<bool> WriteBlock(const std::string& device_name,
                            I2CAddress address,
                            uint32_t offset,
                            char* data,
                            int data_size) override;

    // Cable Operations
    Result<std::vector<uint8_t>>
      ReadCableBlock(const std::string& device_name, uint32_t address, uint32_t size) override;
    Result<bool>
      WriteCableBlock(const std::string& device_name, uint32_t address, const uint8_t* data, int data_size) override;

    // Firmware Operations
    Result<ICmdResponse> SendICMD(const std::string& device_name, const ICmdRequest& request) override;
    Result<RegAccessResponse> AccessRegister(const std::string& device_name, const RegAccessRequest& request) override;

private:
    // Opens the device on first use, holding devices_mutex_ only around the map
    // and not across mopen(). The caller must take the returned entry's op_mutex
    // before touching its mf, and keeps the handle alive for as long as it holds
    // the pointer - CloseDevice can drop the map entry at any time.
    std::shared_ptr<DeviceData>
      GetOrOpenDevice(const std::string& device_name, uint32_t device_type = 0, int force_i2c_address = -1);

    std::unordered_map<std::string, std::shared_ptr<DeviceData>> devices_;
    std::mutex devices_mutex_;
    std::mutex open_mutex_;
};

#endif // MST_SERVER_SERVICE_IMPL_H
