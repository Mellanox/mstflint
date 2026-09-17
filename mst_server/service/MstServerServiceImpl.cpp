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

#include "MstServerServiceImpl.h"
#include <cstdint>
#include <ctime>
#include <cstdio>
#include <cstring>
extern "C"
{
#include "mtcr.h"
#include "mtcr_com_defs.h"
// read_device_id() and the i2c block helpers live in the internal header, not
// the installed mtcr.h.
#include "mtcr_ul_com.h"
#include "mtcr_remote.h"

    // Defined by every mtcr backend but declared by none of them; mtserver.c does
    // the same thing for the same reason.
    extern void mpci_change(mfile* mf);
}

// The client splits a cable transfer into CABLES_REMOTE_BUF_DATA_SIZE chunks and
// the routes reject anything larger, so the two limits have to agree or the last
// chunk of a long transfer is refused.
static_assert(MAX_CABLE_BLOCK_SIZE == CABLES_REMOTE_BUF_DATA_SIZE,
              "MAX_CABLE_BLOCK_SIZE must track mtcr's CABLES_REMOTE_BUF_DATA_SIZE");

// Server version constant
#define MST_SERVER_VERSION "2.0"

// Constructor & Destructor

MstServerServiceImpl::MstServerServiceImpl() {}

MstServerServiceImpl::~MstServerServiceImpl()
{
    // Dropping the entries closes every handle no other thread still holds.
    std::lock_guard<std::mutex> lock(devices_mutex_);
    devices_.clear();
}

DeviceData::~DeviceData()
{
    if (mf != nullptr)
    {
        mclose(mf);
    }
}

// Helper Functions

std::shared_ptr<DeviceData>
  MstServerServiceImpl::GetOrOpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address)
{
    {
        std::lock_guard<std::mutex> lock(devices_mutex_);
        auto it = devices_.find(device_name);
        if (it != devices_.end())
        {
            return it->second;
        }
    }

    mfile* mf = nullptr;
    {
        std::lock_guard<std::mutex> open_lock(open_mutex_);

        set_force_i2c_address(force_i2c_address);
        mf = (device_type == 0) ? mopen(device_name.c_str()) :
                                  mopend(device_name.c_str(), static_cast<DType>(device_type));
        set_force_i2c_address(-1);
    }
    if (!mf)
    {
        return nullptr;
    }

#if defined(__linux__)
    mf->is_mtserver_req = 1;
#endif

    auto device_data = std::make_shared<DeviceData>();
    device_data->device_name = device_name;
    device_data->mf = mf;
    device_data->device_type = device_type;

    std::lock_guard<std::mutex> lock(devices_mutex_);
    auto it = devices_.find(device_name);
    if (it != devices_.end())
    {
        // Another thread opened the same device first; ~DeviceData closes the
        // handle this one opened when device_data goes out of scope.
        return it->second;
    }
    devices_[device_name] = device_data;

    return device_data;
}

// System Operations

Result<std::string> MstServerServiceImpl::GetVersion()
{
    return Result<std::string>::Ok(MST_SERVER_VERSION);
}

Result<std::vector<std::string>> MstServerServiceImpl::GetDevices()
{
    std::vector<std::string> devices;

    // Get devices list from /dev/mst/
    dev_info* mdevs_inf = NULL;
    int devs_num = -1, i = 0;
    mdevs_inf = mdevices_info_v((MDEVS_ALL & ~MDEVS_MLNX_OS), &devs_num, 1);
    if (devs_num < 0 || !mdevs_inf)
    {
        return Result<std::vector<std::string>>::Err(ERR_GET_DEVICES_FAILED, "Failed to get devices list");
    }
    for (i = 0; i < devs_num; i++)
    {
        if (mdevs_inf[i].pci.conf_dev[0])
        {
            devices.push_back(std::string(mdevs_inf[i].pci.conf_dev));
        }
        else
        {
            devices.push_back(std::string(mdevs_inf[i].dev_name));
        }
        if (mdevs_inf[i].pci.cr_dev[0])
        {
            devices.push_back(std::string(mdevs_inf[i].pci.cr_dev));
        }
    }
    mdevices_info_destroy(mdevs_inf, devs_num);

    return Result<std::vector<std::string>>::Ok(devices);
}

Result<uint32_t> MstServerServiceImpl::GetCapabilities()
{
    // Every access this server serves goes through mtcr on this host, so the
    // 64-bit address form is always available. Reported rather than assumed by
    // the client so the answer can grow without a protocol version bump.
    return Result<uint32_t>::Ok(LONG_ADDRESS_SUPPORT_MASK);
}

// Device Management

Result<bool>
  MstServerServiceImpl::OpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address)
{
    if (!GetOrOpenDevice(device_name, device_type, force_i2c_address))
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }

    return Result<bool>::Ok(true);
}

Result<bool> MstServerServiceImpl::CloseDevice(const std::string& device_name)
{
    std::shared_ptr<DeviceData> device;
    {
        std::lock_guard<std::mutex> lock(devices_mutex_);
        auto it = devices_.find(device_name);
        if (it == devices_.end())
        {
            return Result<bool>::Err(ERR_DEVICE_NOT_FOUND, "Device not found: " + device_name);
        }
        device = it->second;
        devices_.erase(it);
    }

    // The device is unreachable from here on, but mclose() runs in ~DeviceData
    // once the last in-flight operation releases its reference, so a request
    // already inside mtcr cannot have the handle closed underneath it.
    return Result<bool>::Ok(true);
}

// Device Information

Result<uint32_t> MstServerServiceImpl::GetDeviceId(const std::string& device_name)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    // Hardware operation
    u_int32_t device_id = 0;

    if (read_device_id(mf, &device_id) < 4)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "Failed to read device ID");
    }

    return Result<uint32_t>::Ok(device_id);
}

Result<uint32_t> MstServerServiceImpl::GetPciDeviceId(const std::string& device_name)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    // Read from mfile struct (safe - read-only access to opened device)
    return Result<uint32_t>::Ok(mf->pci_device_id);
}

// Register Access

Result<uint32_t> MstServerServiceImpl::Read32(const std::string& device_name, uint64_t offset)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    u_int32_t value = 0;
    if (mread4(mf, offset, &value) < 4)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "Failed to read register");
    }

    return Result<uint32_t>::Ok(value);
}

Result<bool> MstServerServiceImpl::Write32(const std::string& device_name, uint64_t offset, uint32_t value)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    if (mwrite4(mf, offset, value) < 4)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_FAILED, "Failed to write register");
    }

    return Result<bool>::Ok(true);
}

Result<bool>
  MstServerServiceImpl::ReadBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    const int byte_len = data_size * static_cast<int>(sizeof(uint32_t));
    if (mread4_block(mf, offset, data, byte_len) != byte_len)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_READ_FAILED, "Failed to read block");
    }

    return Result<bool>::Ok(true);
}

Result<bool>
  MstServerServiceImpl::WriteBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size)
{
    if (data_size > MAX_BLOCK_SIZE)
    {
        return Result<bool>::Err(ERR_BUFFER_TOO_LARGE, "Data is too large");
    }

    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;
    const int byte_len = data_size * static_cast<int>(sizeof(uint32_t));
    if (mwrite4_block(mf, offset, data, byte_len) != byte_len)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_WRITE_FAILED, "Failed to write block");
    }

    return Result<bool>::Ok(true);
}

Result<bool> MstServerServiceImpl::SetAddressSpace(const std::string& device_name, int space)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    if (mset_addr_space(mf, space) != 0)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_ADDRESS_SPACE_FAILED, "Failed to set address space");
    }

    return Result<bool>::Ok(true);
}

Result<bool> MstServerServiceImpl::PciChange(const std::string& device_name)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);

    // Rewrites mf->tp, so it must not run while another request is inside mtcr
    // on the same handle - hence op_mutex, as for every other stateful call.
    mpci_change(device->mf);

    return Result<bool>::Ok(true);
}

// I2C Operations

Result<I2CScanResult> MstServerServiceImpl::ScanI2C(const std::string& device_name)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<I2CScanResult>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);

    // mstflint's mtcr has no mi2c_detect(): the only definitions in the tree are
    // the FreeBSD backend and a local stub in mtserver.c. Refuse the request
    // rather than answer it with an empty address list, which a client cannot
    // tell from "the bus really is empty".
    return Result<I2CScanResult>::Err(ERR_DEVICE_SCAN_I2C_FAILED,
                                      "I2C bus scan is not supported by this build");
}

Result<bool> MstServerServiceImpl::SetI2CSecondary(const std::string& device_name, uint8_t address)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

    if (mset_i2c_secondary(mf, address) == 0xff)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_I2C_SECONDARY_FAILED, "Failed to set I2C secondary address");
    }
    else
    {
        return Result<bool>::Ok(true);
    }
}

Result<std::vector<uint8_t>>
  MstServerServiceImpl::ReadBlock(const std::string& device_name, I2CAddress address, uint32_t offset, uint32_t size)
{
    if (size > MAX_I2C_BLOCK_SIZE)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_BUFFER_TOO_LARGE, "Size is too large");
    }

    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

#ifdef ENABLE_MST_DEV_I2C
    std::vector<uint8_t> buffer(size);
    if (mread_i2cblock(mf, address.secondary, address.addr_width, offset, buffer.data(), size) != static_cast<int>(size))
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_I2C_BLOCK_FAILED, "Failed to read block");
    }

    return Result<std::vector<uint8_t>>::Ok(buffer);
#else
    // mread_i2cblock() is compiled only under --enable-dev-i2c.
    (void)mf;
    (void)address;
    (void)offset;
    return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_I2C_BLOCK_FAILED,
                                             "I2C block access is not supported by this build");
#endif
}

Result<bool> MstServerServiceImpl::WriteBlock(const std::string& device_name,
                                              I2CAddress address,
                                              uint32_t offset,
                                              char* data,
                                              int data_size)
{
    if (data_size > MAX_I2C_BLOCK_SIZE)
    {
        return Result<bool>::Err(ERR_BUFFER_TOO_LARGE, "Data is too large");
    }

    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;

#ifdef ENABLE_MST_DEV_I2C
    if (mwrite_i2cblock(mf, address.secondary, address.addr_width, offset, data, data_size) != data_size)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_I2C_BLOCK_FAILED, "Failed to write block");
    }

    return Result<bool>::Ok(true);
#else
    // Never report success for a write that did not happen.
    (void)mf;
    (void)address;
    (void)offset;
    (void)data;
    (void)data_size;
    return Result<bool>::Err(ERR_DEVICE_WRITE_I2C_BLOCK_FAILED,
                             "I2C block access is not supported by this build");
#endif
}

// Cable Operations

Result<std::vector<uint8_t>>
  MstServerServiceImpl::ReadCableBlock(const std::string& device_name, uint32_t address, uint32_t size)
{
    if (size == 0 || size > static_cast<uint32_t>(MAX_CABLE_BLOCK_SIZE))
    {
        return Result<std::vector<uint8_t>>::Err(ERR_BUFFER_TOO_LARGE, "Size is too large");
    }

    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);

    // mstflint's mtcr has no mcables_remote_operation_server_side(); serving
    // cable traffic would need a transport this build does not have.
    (void)address;
    (void)size;
    return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_CABLE_BLOCK_FAILED,
                                             "Cable block access is not supported by this build");
}

Result<bool> MstServerServiceImpl::WriteCableBlock(const std::string& device_name,
                                                   uint32_t address,
                                                   const uint8_t* data,
                                                   int data_size)
{
    if (data_size <= 0 || data_size > MAX_CABLE_BLOCK_SIZE)
    {
        return Result<bool>::Err(ERR_BUFFER_TOO_LARGE, "Data is too large");
    }

    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);

    // As above. Refused rather than silently accepted: a client that believed a
    // cable write had landed would have no way to notice it never did.
    (void)address;
    (void)data;
    return Result<bool>::Err(ERR_DEVICE_WRITE_CABLE_BLOCK_FAILED,
                             "Cable block access is not supported by this build");
}

// Firmware Operations

Result<ICmdResponse> MstServerServiceImpl::SendICMD(const std::string& device_name, const ICmdRequest& request)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<ICmdResponse>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;
    int ret = icmd_send_command(mf, request.opcode, request.data, request.data_size, request.skip_write);
    if (!ret)
    {
        ICmdResponse response;
        response.data = request.data;
        response.syndrome = mf->icmd.syndrome;
        return Result<ICmdResponse>::Ok(response);
    }
    else
    {
        return Result<ICmdResponse>::Err(static_cast<ErrorCode>(mf->icmd.syndrome), "Failed to send ICMD");
    }
}

Result<RegAccessResponse> MstServerServiceImpl::AccessRegister(const std::string& device_name,
                                                               const RegAccessRequest& request)
{
    std::shared_ptr<DeviceData> device = GetOrOpenDevice(device_name);
    if (!device)
    {
        return Result<RegAccessResponse>::Err(ERR_DEVICE_OPEN_FAILED, "Failed to open device: " + device_name);
    }
    std::lock_guard<std::mutex> device_lock(device->op_mutex);
    mfile* mf = device->mf;
    int reg_status = 0;
    maccess_reg_method_t reg_access_method = request.is_write ? MACCESS_REG_METHOD_SET : MACCESS_REG_METHOD_GET;
    // mstflint exposes only the full maccess_reg(); MFT's maccess_reg_send()
    // wrapper has no counterpart here. Passing data_size for all three size
    // arguments is the convention the rest of the tree uses (mtcr_cables.c).
    int ret = maccess_reg(mf, request.reg_id, reg_access_method, request.data, request.data_size, request.data_size,
                          request.data_size, &reg_status);
    if (!ret)
    {
        // A non-zero reg_status is a valid device response (the FW rejected the
        // access with a specific status code), not a transport failure. Return
        // it to the client so it can surface the exact FW error code, mirroring
        // the SSH server which passes reg_status back to the caller.
        RegAccessResponse response;
        response.data = request.data;
        response.data_size = request.data_size;
        response.reg_status = reg_status;
        return Result<RegAccessResponse>::Ok(response);
    }
    else
    {
        return Result<RegAccessResponse>::Err(static_cast<ErrorCode>(reg_status), "Failed to access register");
    }
}
