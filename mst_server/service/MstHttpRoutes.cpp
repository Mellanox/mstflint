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

#include "mst_server/service/MstHttpRoutes.h"

#include <openssl/crypto.h>

#include <string>
#include <vector>

namespace mstserver
{
namespace http
{

void register_routes(MstApp& app, MstServerService& service)
{
    BearerAuth& auth = app.get_middleware<BearerAuth>();

    CROW_ROUTE(app, "/health")([]() { return text_response(200, "ok"); });

    CROW_ROUTE(app, "/login")
      .methods(crow::HTTPMethod::Post)(
        [&auth](const crow::request& req)
        {
            // The passphrase itself, not a digest of it: deriving on the client
            // would make whatever it derived the credential, which is the thing
            // the salted verifier exists to avoid.
            std::string passphrase = get_param(req, "passphrase");
            if (passphrase.empty() && !req.get_header_value("Content-Type").empty())
            {
                passphrase = req.body;
            }
            const bool accepted = auth.VerifyPassphrase(passphrase);
            OPENSSL_cleanse(&passphrase[0], passphrase.size());
            if (accepted)
            {
                std::string token = generate_token();
                {
                    std::lock_guard<std::mutex> lock(auth.tokens_mutex);
                    auth.active_tokens.insert(token);
                }
                return text_response(200, token);
            }
            return text_response(401, "unauthorized");
        });

    CROW_ROUTE(app, "/logout")
      .methods(crow::HTTPMethod::Post)(
        [&auth](const crow::request& req)
        {
            std::string token = extract_bearer_token(req);
            if (!token.empty())
            {
                std::lock_guard<std::mutex> lock(auth.tokens_mutex);
                auth.active_tokens.erase(token);
            }
            return text_response(200, "ok");
        });

    CROW_ROUTE(app, "/version")
    (
      [&service]()
      {
          auto r = service.GetVersion();
          if (r.success)
          {
              return text_response(200, r.value);
          }
          return error_response(500, r.error.message);
      });

    // Decimal text, same shape as /version: a bitmask in the encoding of mtcr's
    // LONG_ADDRESS_SUPPORT_MASK.
    CROW_ROUTE(app, "/capabilities")
    (
      [&service]()
      {
          auto r = service.GetCapabilities();
          if (r.success)
          {
              return text_response(200, std::to_string(r.value));
          }
          return error_response(500, r.error.message);
      });

    CROW_ROUTE(app, "/devices")
    (
      [&service]()
      {
          auto r = service.GetDevices();
          if (!r.success)
          {
              return error_response(500, r.error.message);
          }
          crow::json::wvalue::list devices;
          for (const auto& d : r.value)
          {
              devices.emplace_back(d);
          }
          crow::json::wvalue root(devices);
          crow::response res(200, root);
          return res;
      });

    // --- Device management ---
    CROW_ROUTE(app, "/device/open")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t device_type = 0;
            std::string device_type_str = get_param(req, "device_type");
            if (!device_type_str.empty() && !parse_uint32(device_type_str, &device_type))
            {
                return text_response(400, "invalid device_type");
            }
            int force_i2c_address = -1;
            std::string forced = get_param(req, "force_i2c_address");
            if (!forced.empty() && !parse_int(forced, &force_i2c_address))
            {
                return text_response(400, "invalid force_i2c_address");
            }
            auto r = service.OpenDevice(device, device_type, force_i2c_address);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    CROW_ROUTE(app, "/device/close")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            auto r = service.CloseDevice(device);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    // --- Device info ---
    CROW_ROUTE(app, "/device/id")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          auto r = service.GetDeviceId(device);
          if (r.success)
          {
              return text_response(200, std::to_string(r.value));
          }
          return error_response(500, r.error.message);
      });

    CROW_ROUTE(app, "/device/pci_id")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          auto r = service.GetPciDeviceId(device);
          if (r.success)
          {
              return text_response(200, std::to_string(r.value));
          }
          return error_response(500, r.error.message);
      });

    // --- Register access ---
    CROW_ROUTE(app, "/device/read32")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          uint64_t offset = 0;
          if (!parse_uint64(get_param(req, "offset"), &offset))
          {
              return text_response(400, "missing or invalid offset");
          }
          auto r = service.Read32(device, offset);
          if (r.success)
          {
              return binary_response(reinterpret_cast<const char*>(&r.value), sizeof(uint32_t));
          }
          return error_response(500, r.error.message);
      });

    CROW_ROUTE(app, "/device/write32")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint64_t offset = 0;
            uint32_t value = 0;
            if (!parse_uint64(get_param(req, "offset"), &offset))
            {
                return text_response(400, "missing or invalid offset");
            }
            if (!parse_uint32(get_param(req, "value"), &value))
            {
                return text_response(400, "missing or invalid value");
            }
            auto r = service.Write32(device, offset, value);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    CROW_ROUTE(app, "/device/read_block")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          uint64_t offset = 0;
          int size = 0;
          if (!parse_uint64(get_param(req, "offset"), &offset))
          {
              return text_response(400, "missing or invalid offset");
          }
          if (!parse_int(get_param(req, "size"), &size) || size <= 0 || size > MAX_BLOCK_SIZE)
          {
              return text_response(400, "missing or invalid size (1.." + std::to_string(MAX_BLOCK_SIZE) + ")");
          }
          std::vector<uint32_t> buf(static_cast<size_t>(size));
          auto r = service.ReadBlock(device, offset, buf.data(), size);
          if (!r.success)
          {
              return error_response(500, r.error.message);
          }
          return binary_response(reinterpret_cast<const char*>(buf.data()),
                                 static_cast<size_t>(size) * sizeof(uint32_t));
      });

    CROW_ROUTE(app, "/device/write_block")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint64_t offset = 0;
            if (!parse_uint64(get_param(req, "offset"), &offset))
            {
                return text_response(400, "missing or invalid offset");
            }
            if (req.body.empty() || req.body.size() % sizeof(uint32_t))
            {
                return text_response(400, "body must be raw binary, length multiple of 4 (32-bit words)");
            }
            int size = static_cast<int>(req.body.size() / sizeof(uint32_t));
            if (size > MAX_BLOCK_SIZE)
            {
                return text_response(400, "data too large");
            }
            auto r =
              service.WriteBlock(device, offset, reinterpret_cast<uint32_t*>(const_cast<char*>(req.body.data())), size);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    CROW_ROUTE(app, "/device/set_address_space")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            int space = 0;
            if (!parse_int(get_param(req, "space"), &space))
            {
                return text_response(400, "missing or invalid space");
            }
            auto r = service.SetAddressSpace(device, space);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    CROW_ROUTE(app, "/device/pci_change")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            auto r = service.PciChange(device);
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    // --- I2C ---
    CROW_ROUTE(app, "/device/scan_i2c")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          auto r = service.ScanI2C(device);
          if (!r.success)
          {
              return error_response(500, r.error.message);
          }
          crow::json::wvalue::list addresses;
          for (const auto& addr : r.value.addresses)
          {
              addresses.emplace_back(static_cast<int>(addr));
          }
          crow::json::wvalue root(addresses);
          crow::response res(200, root);
          return res;
      });

    CROW_ROUTE(app, "/device/set_i2c_secondary")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t addr = 0;
            if (!parse_uint32(get_param(req, "address"), &addr) || addr > 0xff)
            {
                return text_response(400, "missing or invalid address (0-255)");
            }
            auto r = service.SetI2CSecondary(device, static_cast<uint8_t>(addr));
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    CROW_ROUTE(app, "/device/i2c/read")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          uint32_t secondary = 0, addr_width = 0, offset = 0, size = 0;
          if (!parse_uint32(get_param(req, "secondary"), &secondary) || secondary > 0xff)
          {
              return text_response(400, "missing or invalid secondary (0-255)");
          }
          if (!parse_uint32(get_param(req, "addr_width"), &addr_width) || addr_width > 0xff)
          {
              return text_response(400, "missing or invalid addr_width (0-255)");
          }
          if (!parse_uint32(get_param(req, "offset"), &offset))
          {
              return text_response(400, "missing or invalid offset");
          }
          if (!parse_uint32(get_param(req, "size"), &size) || size == 0 || size > MAX_I2C_BLOCK_SIZE)
          {
              return text_response(400, "missing or invalid size (1.." + std::to_string(MAX_I2C_BLOCK_SIZE) + ")");
          }
          mstserver::I2CAddress addr;
          addr.secondary = static_cast<uint8_t>(secondary);
          addr.addr_width = static_cast<uint8_t>(addr_width);
          auto r2 = service.ReadBlock(device, addr, offset, size);
          if (!r2.success)
          {
              return error_response(500, r2.error.message);
          }
          return binary_response(reinterpret_cast<const char*>(r2.value.data()), r2.value.size());
      });

    CROW_ROUTE(app, "/device/i2c/write")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t secondary = 0, addr_width = 0, offset = 0;
            if (!parse_uint32(get_param(req, "secondary"), &secondary) || secondary > 0xff)
            {
                return text_response(400, "missing or invalid secondary (0-255)");
            }
            if (!parse_uint32(get_param(req, "addr_width"), &addr_width) || addr_width > 0xff)
            {
                return text_response(400, "missing or invalid addr_width (0-255)");
            }
            if (!parse_uint32(get_param(req, "offset"), &offset))
            {
                return text_response(400, "missing or invalid offset");
            }
            if (req.body.empty())
            {
                return text_response(400, "body (raw binary data)");
            }
            if (req.body.size() > static_cast<size_t>(MAX_I2C_BLOCK_SIZE))
            {
                return text_response(400, "data too large");
            }
            mstserver::I2CAddress addr;
            addr.secondary = static_cast<uint8_t>(secondary);
            addr.addr_width = static_cast<uint8_t>(addr_width);
            auto r2 = service.WriteBlock(device, addr, offset, const_cast<char*>(req.body.data()),
                                         static_cast<int>(req.body.size()));
            if (r2.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r2.error.message);
        });

    // --- Cable ---
    // Byte-granular, and bounded by MAX_CABLE_BLOCK_SIZE because the client
    // already chunks a long transfer to exactly that size.
    CROW_ROUTE(app, "/device/cable/read")
    (
      [&service](const crow::request& req)
      {
          std::string device = get_param(req, "device");
          if (device.empty())
          {
              return param_missing("device");
          }
          uint32_t address = 0, size = 0;
          if (!parse_uint32(get_param(req, "address"), &address))
          {
              return text_response(400, "missing or invalid address");
          }
          if (!parse_uint32(get_param(req, "size"), &size) || size == 0 ||
              size > static_cast<uint32_t>(MAX_CABLE_BLOCK_SIZE))
          {
              return text_response(400, "missing or invalid size (1.." + std::to_string(MAX_CABLE_BLOCK_SIZE) + ")");
          }
          auto r = service.ReadCableBlock(device, address, size);
          if (!r.success)
          {
              return error_response(500, r.error.message);
          }
          return binary_response(reinterpret_cast<const char*>(r.value.data()), r.value.size());
      });

    CROW_ROUTE(app, "/device/cable/write")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t address = 0;
            if (!parse_uint32(get_param(req, "address"), &address))
            {
                return text_response(400, "missing or invalid address");
            }
            if (req.body.empty())
            {
                return text_response(400, "body (raw binary data)");
            }
            if (req.body.size() > static_cast<size_t>(MAX_CABLE_BLOCK_SIZE))
            {
                return text_response(400, "data too large");
            }
            auto r = service.WriteCableBlock(device, address, reinterpret_cast<const uint8_t*>(req.body.data()),
                                             static_cast<int>(req.body.size()));
            if (r.success)
            {
                return text_response(200, "ok");
            }
            return error_response(500, r.error.message);
        });

    // --- Firmware: ICMD ---
    // Query params: device, opcode, skip_write. Body: raw binary data (application/octet-stream).
    // Response: 4 bytes syndrome (uint32) + remaining bytes = output data (application/octet-stream).
    CROW_ROUTE(app, "/device/icmd")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t opcode = 0;
            if (!parse_uint32(get_param(req, "opcode"), &opcode))
            {
                return text_response(400, "missing or invalid opcode");
            }
            bool skip_write = (get_param(req, "skip_write") == "1" || get_param(req, "skip_write") == "true");
            std::vector<char> data_buf(req.body.begin(), req.body.end());
            mstserver::ICmdRequest creq;
            creq.opcode = opcode;
            creq.data = data_buf.empty() ? nullptr : data_buf.data();
            creq.data_size = static_cast<int>(data_buf.size());
            creq.skip_write = skip_write;
            auto r = service.SendICMD(device, creq);
            if (!r.success)
            {
                return error_response(500, r.error.message);
            }
            std::string out;
            out.append(reinterpret_cast<const char*>(&r.value.syndrome), sizeof(uint32_t));
            if (r.value.data && creq.data_size > 0)
            {
                out.append(r.value.data, static_cast<size_t>(creq.data_size));
            }
            return binary_response(out.data(), out.size());
        });

    CROW_ROUTE(app, "/device/access_register")
      .methods(crow::HTTPMethod::Post)(
        [&service](const crow::request& req)
        {
            std::string device = get_param(req, "device");
            if (device.empty())
            {
                return param_missing("device");
            }
            uint32_t reg_id = 0;
            if (!parse_uint32(get_param(req, "reg_id"), &reg_id))
            {
                return text_response(400, "missing or invalid reg_id");
            }
            bool is_write = (get_param(req, "is_write") == "1" || get_param(req, "is_write") == "true");
            std::vector<char> data_buf(req.body.begin(), req.body.end());
            mstserver::RegAccessRequest rareq;
            rareq.reg_id = reg_id;
            rareq.data = data_buf.empty() ? nullptr : data_buf.data();
            rareq.data_size = static_cast<int>(data_buf.size());
            rareq.is_write = is_write;
            auto r = service.AccessRegister(device, rareq);
            if (!r.success)
            {
                return error_response(500, r.error.message);
            }
            std::string out;
            int32_t status = r.value.reg_status;
            out.append(reinterpret_cast<const char*>(&status), sizeof(int32_t));
            if (r.value.data && r.value.data_size > 0)
            {
                out.append(r.value.data, static_cast<size_t>(r.value.data_size));
            }
            return binary_response(out.data(), out.size());
        });
}

} // namespace http
} // namespace mstserver
