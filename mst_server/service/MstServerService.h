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

#ifndef MST_SERVER_SERVICE_H
#define MST_SERVER_SERVICE_H

#include <cstdint>
#include <stdint.h>
#include <string>
#include <vector>

namespace mstserver
{
// Largest payload the protocol accepts, enforced by the routes before the call
// and by the implementation before it reaches the device.
constexpr int MAX_BLOCK_SIZE = 512;    // 32-bit words
constexpr int MAX_I2C_BLOCK_SIZE = 64; // bytes
// Must stay equal to mtcr's CABLES_REMOTE_BUF_DATA_SIZE, which is the chunk the
// client splits a cable transfer into; a smaller cap here would reject chunks the
// client still sends. MstServerServiceImpl.cpp static_asserts the two together.
constexpr int MAX_CABLE_BLOCK_SIZE = 2048; // bytes

// Result Types and Error Handling

enum ErrorCode
{
    ERR_DEVICE_OPEN_FAILED = 1,
    ERR_DEVICE_CLOSE_FAILED = 2,
    ERR_DEVICE_READ_FAILED = 3,
    ERR_DEVICE_WRITE_FAILED = 4,
    ERR_DEVICE_BLOCK_READ_FAILED = 5,
    ERR_DEVICE_BLOCK_WRITE_FAILED = 6,
    ERR_DEVICE_SET_ADDRESS_SPACE_FAILED = 7,
    ERR_DEVICE_SCAN_I2C_FAILED = 8,
    ERR_DEVICE_SET_I2C_SECONDARY_FAILED = 9,
    ERR_DEVICE_READ_I2C_BLOCK_FAILED = 10,
    ERR_DEVICE_WRITE_I2C_BLOCK_FAILED = 11,
    ERR_DEVICE_SEND_ICMD_FAILED = 13,
    ERR_DEVICE_ACCESS_REGISTER_FAILED = 14,
    ERR_BUFFER_TOO_LARGE = 15,
    ERR_GET_DEVICES_FAILED = 16,
    ERR_DEVICE_NOT_FOUND = 17,
    ERR_GET_VERSION_FAILED = 18,
    ERR_LOGIN_FAILED = 19,
    ERR_DEVICE_READ_CABLE_BLOCK_FAILED = 20,
    ERR_DEVICE_WRITE_CABLE_BLOCK_FAILED = 21,
    ERR_DEVICE_PCI_CHANGE_FAILED = 22,
    ERR_GET_CAPABILITIES_FAILED = 23
};

struct ErrorInfo
{
    ErrorCode code;
    std::string message;
};

// Result type for operations that can fail
template<typename T>
struct Result
{
    bool success;
    T value;
    ErrorInfo error;

    static Result<T> Ok(const T& val) { return {true, val, {}}; }

    static Result<T> Err(ErrorCode code, const std::string& msg) { return {false, T{}, {code, msg}}; }
};

// Data Structures for Operations

struct I2CScanResult
{
    std::vector<uint8_t> addresses; // List of detected I2C addresses
};

struct ICmdRequest
{
    uint32_t opcode;
    char* data;
    int data_size;
    bool skip_write;
};

struct ICmdResponse
{
    char* data;
    uint32_t syndrome; // Error syndrome if failed
};

struct RegAccessRequest
{
    uint32_t reg_id;
    char* data;
    int data_size;
    bool is_write; // true for SET, false for GET
};

struct RegAccessResponse
{
    char* data;
    int data_size;
    int reg_status;
};

struct I2CAddress
{
    uint8_t secondary;
    uint8_t addr_width;
};

// Every operation the mstserver protocol supports, independent of transport.
class MstServerService
{
public:
    virtual ~MstServerService() = default;

    // System Operations

    virtual Result<std::string> GetVersion() = 0;

    virtual Result<std::vector<std::string>> GetDevices() = 0;

    // Bitmask of the optional protocol features this server implements, in the
    // encoding of mtcr's LONG_ADDRESS_SUPPORT_MASK and friends. Asked for rather
    // than assumed, so a server can gain a feature without a client change.
    virtual Result<uint32_t> GetCapabilities() = 0;

    // Device Management

    // device_type is an mtcr DType; device_name is a path such as "/dev/mst/mt25418_pci_cr0".
    //
    // force_i2c_address is the I2C secondary to open with, or -1 for none. It
    // belongs to the open because mtcr consumes it while opening the device and
    // never afterwards, so it cannot be set as a separate call.
    virtual Result<bool> OpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address) = 0;

    virtual Result<bool> CloseDevice(const std::string& device_name) = 0;

    // Device Information

    virtual Result<uint32_t> GetDeviceId(const std::string& device_name) = 0;

    virtual Result<uint32_t> GetPciDeviceId(const std::string& device_name) = 0;

    // Register Access Operations

    virtual Result<uint32_t> Read32(const std::string& device_name, uint64_t offset) = 0;

    virtual Result<bool> Write32(const std::string& device_name, uint64_t offset, uint32_t value) = 0;

    virtual Result<bool> ReadBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) = 0;

    virtual Result<bool> WriteBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) = 0;

    virtual Result<bool> SetAddressSpace(const std::string& device_name, int space) = 0;

    // Switches the handle between CONF and CR access, as mtcr's mpci_change does.
    virtual Result<bool> PciChange(const std::string& device_name) = 0;

    // I2C Operations

    virtual Result<I2CScanResult> ScanI2C(const std::string& device_name) = 0;

    virtual Result<bool> SetI2CSecondary(const std::string& device_name, uint8_t address) = 0;

    // I2C overload of ReadBlock.
    virtual Result<std::vector<uint8_t>>
      ReadBlock(const std::string& device_name, I2CAddress address, uint32_t offset, uint32_t size) = 0;

    // I2C overload of WriteBlock.
    virtual Result<bool>
      WriteBlock(const std::string& device_name, I2CAddress address, uint32_t offset, char* data, int data_size) = 0;

    // Cable Operations

    // Byte-granular cable access, as mtcr's mcables_remote_operation_server_side
    // performs it. Unlike the I2C overloads these carry no secondary address:
    // the cable is addressed by the flat offset the caller passes.
    virtual Result<std::vector<uint8_t>>
      ReadCableBlock(const std::string& device_name, uint32_t address, uint32_t size) = 0;

    virtual Result<bool>
      WriteCableBlock(const std::string& device_name, uint32_t address, const uint8_t* data, int data_size) = 0;

    // Firmware Operations

    // Sends an in-band command (ICMD) to firmware.
    virtual Result<ICmdResponse> SendICMD(const std::string& device_name, const ICmdRequest& request) = 0;

    // Register access, as mtcr's maccess_reg performs it.
    virtual Result<RegAccessResponse> AccessRegister(const std::string& device_name,
                                                     const RegAccessRequest& request) = 0;
};
} // namespace mstserver
#endif // MST_SERVER_SERVICE_H