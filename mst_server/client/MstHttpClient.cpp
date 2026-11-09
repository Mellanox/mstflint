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

#include "MstHttpClient.h"
#include "mst_server/client/MstKnownHosts.h"
#include "mst_server/service/MstTlsFingerprint.h"
#include "common/tools_algorithm.h"
#include "json/reader.h"
#include "json/value.h"
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>

#ifdef __WIN__
#include <io.h>
#else
#include <unistd.h>
#endif

using namespace mstserver;

// Kept out of the header so <curl.h> does not reach this library's consumers -
// see the note in MstHttpClient.h. The repo includes it unprefixed; CURL_INC_DIR
// points at curl's own directory.
#include "MstCurlClient.h"

namespace algo = mstflint::common::algorithm;

namespace
{

// Both streams must be a terminal: asking on stdin while the question goes to a
// redirected stderr would block on an invisible prompt.
bool can_ask_user()
{
#ifdef __WIN__
    return _isatty(_fileno(stdin)) != 0 && _isatty(_fileno(stderr)) != 0;
#else
    return isatty(fileno(stdin)) != 0 && isatty(fileno(stderr)) != 0;
#endif
}

} // namespace

// Construction and server trust

MstHttpClient::MstHttpClient(const std::string& host, int port) :
    cli_(new msthttp::Client(host, port)), host_(host), port_(port)
{
    Init(TlsOptions());
}

MstHttpClient::MstHttpClient(const std::string& host, int port, const TlsOptions& tls) :
    cli_(new msthttp::Client(host, port)), host_(host), port_(port)
{
    Init(tls);
}

void MstHttpClient::Init(const TlsOptions& tls)
{
    tls_ = tls;
    // Five seconds, not two: an unanswered TCP SYN is retransmitted after
    // about a second and again about three seconds later, so a shorter budget
    // gives up in the middle of the retry that would have succeeded.
    cli_->set_connect_timeout_ms(5000);
    cli_->set_transfer_timeout_ms(30000);

    if (tls_.enabled)
    {
        // The certificate is borrowed from the handshake's verification context,
        // so it is not freed here.
        cli_->enable_tls([this](X509* cert) { return DecideTrust(tls::public_key_fingerprint(cert)); });
    }

    available_ = false;
    auto res = cli_->Get("/health");
    if (res && res->status == 200)
    {
        available_ = true;
    }
}

bool MstHttpClient::DecideTrust(const std::string& fingerprint)
{
    const std::string target = MstKnownHosts::HostKey(host_, port_);
    if (fingerprint.empty())
    {
        trust_error_ = "server '" + target + "' presented no usable public key";
        return false;
    }
    peer_fingerprint_ = fingerprint;

    MstKnownHosts known_hosts(tls_.known_hosts_path);
    std::string recorded;
    const MstKnownHosts::Status status = known_hosts.Lookup(host_, port_, fingerprint, &recorded);
    if (status == MstKnownHosts::MATCH)
    {
        return true;
    }
    if (status == MstKnownHosts::MISMATCH)
    {
        // No policy overrides this. A host we have already vouched for now
        // answers with a different key, which is what a machine-in-the-middle
        // looks like; the operator has to resolve it by hand.
        trust_error_ =
          "the key of MST server '" + target + "' has changed (recorded " + recorded + ", offered " + fingerprint + ")";
        std::cerr << "-E- WARNING: THE IDENTITY OF THE MST SERVER HAS CHANGED!\n"
                  << "-E- The key offered by '" << target << "' is not the one recorded in " << known_hosts.Path()
                  << ":\n"
                  << "-E-   recorded: " << recorded << "\n"
                  << "-E-   offered:  " << fingerprint << "\n"
                  << "-E- Someone may be impersonating the server to read or alter this session.\n"
                  << "-E- If the server was legitimately reinstalled, remove its entry from " << known_hosts.Path()
                  << " and connect again.\n";
        return false;
    }

    bool accepted = false;
    switch (tls_.policy)
    {
        case MST_TRUST_ACCEPT_NEW:
            accepted = true;
            std::cerr << "-I- Trusting new MST server '" << target << "' (" << fingerprint << ").\n";
            break;

        case MST_TRUST_STRICT:
            accepted = false;
            break;

        case MST_TRUST_PROMPT:
        default:
            if (tls_.prompt != nullptr)
            {
                accepted = tls_.prompt(host_.c_str(), port_, fingerprint.c_str(), tls_.prompt_ctx) != 0;
            }
            else if (can_ask_user())
            {
                accepted = AskOnTerminal(fingerprint);
            }
            else
            {
                // Reached only when a caller asked to be prompted and there is
                // no terminal to ask on. Accept, but say so loudly; turning
                // this into a refusal is what makes the request enforceable.
                std::cerr << "-W- The authenticity of MST server '" << target << "' can't be established.\n"
                          << "-W- Server key fingerprint is " << fingerprint << ".\n"
                          << "-W- There is no terminal to confirm on, so it is being trusted for now.\n"
                          << "-W- This will become an error in a future release: run 'mst remote add " << target
                          << "' from a terminal, or pass -y, to record this server deliberately.\n";
                accepted = true;
            }
            break;
    }

    if (!accepted)
    {
        trust_error_ = "MST server '" + target + "' (" + fingerprint + ") is not trusted";
        return false;
    }

    std::string error;
    if (!known_hosts.Add(host_, port_, fingerprint, &error))
    {
        // Not fatal - the key was just approved - but the approval will be
        // asked for again next time, so it must not pass unnoticed.
        std::cerr << "-W- Cannot record the server key in " << known_hosts.Path() << ": " << error << "\n";
    }
    return true;
}

bool MstHttpClient::AskOnTerminal(const std::string& fingerprint) const
{
    const std::string target = MstKnownHosts::HostKey(host_, port_);
    // stderr, not stdout: callers such as "mst remote add" parse this process's
    // stdout as the device list.
    std::cerr << "The authenticity of MST server '" << target << "' can't be established.\n"
              << "Server key fingerprint is " << fingerprint << ".\n";

    for (int attempt = 0; attempt < 3; attempt++)
    {
        std::cerr << "Are you sure you want to continue connecting (yes/no)? " << std::flush;
        std::string answer;
        if (!std::getline(std::cin, answer))
        {
            break;
        }
        const std::string normalized = algo::to_lower_copy(answer);
        if (normalized == "yes" || normalized == "y")
        {
            return true;
        }
        if (normalized == "no" || normalized == "n")
        {
            return false;
        }
        std::cerr << "Please type 'yes' or 'no'.\n";
    }
    return false;
}

const std::string& MstHttpClient::GetPeerFingerprint() const
{
    return peer_fingerprint_;
}

const std::string& MstHttpClient::GetTrustError() const
{
    return trust_error_;
}

int MstHttpClient::GetLastStatus() const
{
    return cli_->last_status();
}

// Out of line: msthttp::Client is incomplete in the header, so unique_ptr can
// only destroy it where the transport definition is visible.
MstHttpClient::~MstHttpClient() = default;

bool MstHttpClient::IsAvailable()
{
    // The constructor already probed /health and warmed the connection.
    // Returning the cached result avoids paying a second roundtrip here.
    return available_;
}

bool MstHttpClient::Login(const std::string& passphrase)
{
    msthttp::Params params;
    params.emplace("passphrase", passphrase);
    auto res = cli_->Post("/login", params);
    if (res && res->status == 200 && !res->body.empty())
    {
        SetToken(res->body);
        return true;
    }
    return false;
}

void MstHttpClient::SetToken(const std::string& token)
{
    token_ = token;
    cli_->set_default_headers({{"Authorization", "Bearer " + token_}});
}

const std::string& MstHttpClient::GetToken() const
{
    return token_;
}

// System Operations

Result<std::string> MstHttpClient::GetVersion()
{
    auto res = cli_->Get("/version");
    if (!res)
    {
        return Result<std::string>::Err(ERR_GET_VERSION_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<std::string>::Err(ERR_GET_VERSION_FAILED, res->body);
    }
    return Result<std::string>::Ok(res->body);
}

Result<std::vector<std::string>> MstHttpClient::GetDevices()
{
    auto res = cli_->Get("/devices");
    if (!res)
    {
        return Result<std::vector<std::string>>::Err(ERR_GET_DEVICES_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<std::vector<std::string>>::Err(ERR_GET_DEVICES_FAILED, res->body);
    }

    Json::CharReaderBuilder rbuilder;
    std::string errs;
    std::istringstream is(res->body);
    Json::Value root;
    if (!Json::parseFromStream(rbuilder, is, &root, &errs) || !root.isArray())
    {
        return Result<std::vector<std::string>>::Err(ERR_GET_DEVICES_FAILED, "Invalid JSON: " + errs);
    }

    std::vector<std::string> devices;
    for (Json::ArrayIndex i = 0; i < root.size(); i++)
    {
        if (root[i].isString())
        {
            devices.push_back(root[i].asString());
        }
    }
    return Result<std::vector<std::string>>::Ok(devices);
}

Result<uint32_t> MstHttpClient::GetCapabilities()
{
    auto res = cli_->Get("/capabilities");
    if (!res)
    {
        return Result<uint32_t>::Err(ERR_GET_CAPABILITIES_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<uint32_t>::Err(ERR_GET_CAPABILITIES_FAILED, res->body);
    }
    return Result<uint32_t>::Ok(static_cast<uint32_t>(std::strtoul(res->body.c_str(), nullptr, 0)));
}

// Device Management

Result<bool> MstHttpClient::OpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("device_type", std::to_string(device_type));
    if (force_i2c_address != -1)
    {
        params.emplace("force_i2c_address", std::to_string(force_i2c_address));
    }
    auto res = cli_->Post("/device/open", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_OPEN_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

Result<bool> MstHttpClient::CloseDevice(const std::string& device_name)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    auto res = cli_->Post("/device/close", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_CLOSE_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_CLOSE_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

// Device Information

Result<uint32_t> MstHttpClient::GetDeviceId(const std::string& device_name)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    auto res = cli_->Get("/device/id", params);
    if (!res)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, res->body);
    }
    return Result<uint32_t>::Ok(static_cast<uint32_t>(std::strtoul(res->body.c_str(), nullptr, 0)));
}

Result<uint32_t> MstHttpClient::GetPciDeviceId(const std::string& device_name)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    auto res = cli_->Get("/device/pci_id", params);
    if (!res)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, res->body);
    }
    return Result<uint32_t>::Ok(static_cast<uint32_t>(std::strtoul(res->body.c_str(), nullptr, 0)));
}

// Register Access

Result<uint32_t> MstHttpClient::Read32(const std::string& device_name, uint64_t offset)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("offset", std::to_string(offset));
    auto res = cli_->Get("/device/read32", params);
    if (!res)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, res->body);
    }
    if (res->body.size() < sizeof(uint32_t))
    {
        return Result<uint32_t>::Err(ERR_DEVICE_READ_FAILED, "Short response");
    }
    uint32_t val = 0;
    std::memcpy(&val, res->body.data(), sizeof(uint32_t));
    return Result<uint32_t>::Ok(val);
}

Result<bool> MstHttpClient::Write32(const std::string& device_name, uint64_t offset, uint32_t value)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("offset", std::to_string(offset));
    params.emplace("value", std::to_string(value));
    auto res = cli_->Post("/device/write32", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

Result<bool> MstHttpClient::ReadBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("offset", std::to_string(offset));
    params.emplace("size", std::to_string(data_size));
    auto res = cli_->Get("/device/read_block", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_READ_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_READ_FAILED, res->body);
    }
    size_t expected = static_cast<size_t>(data_size) * sizeof(uint32_t);
    if (res->body.size() != expected)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_READ_FAILED, "Response size mismatch");
    }
    std::memcpy(data, res->body.data(), expected);
    return Result<bool>::Ok(true);
}

Result<bool> MstHttpClient::WriteBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("offset", std::to_string(offset));
    std::string path = msthttp::append_query_params("/device/write_block", params);
    std::string body(reinterpret_cast<const char*>(data), static_cast<size_t>(data_size) * sizeof(uint32_t));
    auto res = cli_->Post(path, body, "application/octet-stream");
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_WRITE_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_BLOCK_WRITE_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

Result<bool> MstHttpClient::SetAddressSpace(const std::string& device_name, int space)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("space", std::to_string(space));
    auto res = cli_->Post("/device/set_address_space", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_ADDRESS_SPACE_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_ADDRESS_SPACE_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

Result<bool> MstHttpClient::PciChange(const std::string& device_name)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    auto res = cli_->Post("/device/pci_change", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_PCI_CHANGE_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_PCI_CHANGE_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

// I2C Operations

Result<I2CScanResult> MstHttpClient::ScanI2C(const std::string& device_name)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    auto res = cli_->Get("/device/scan_i2c", params);
    if (!res)
    {
        return Result<I2CScanResult>::Err(ERR_DEVICE_SCAN_I2C_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<I2CScanResult>::Err(ERR_DEVICE_SCAN_I2C_FAILED, res->body);
    }

    Json::CharReaderBuilder rbuilder;
    std::string errs;
    std::istringstream is(res->body);
    Json::Value root;
    if (!Json::parseFromStream(rbuilder, is, &root, &errs) || !root.isArray())
    {
        return Result<I2CScanResult>::Err(ERR_DEVICE_SCAN_I2C_FAILED, "Invalid JSON");
    }

    I2CScanResult result;
    for (Json::ArrayIndex i = 0; i < root.size(); i++)
    {
        if (root[i].isIntegral())
        {
            result.addresses.push_back(static_cast<uint8_t>(root[i].asInt()));
        }
    }
    return Result<I2CScanResult>::Ok(result);
}

Result<bool> MstHttpClient::SetI2CSecondary(const std::string& device_name, uint8_t address)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("address", std::to_string(static_cast<int>(address)));
    auto res = cli_->Post("/device/set_i2c_secondary", params);
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_I2C_SECONDARY_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_SET_I2C_SECONDARY_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

Result<std::vector<uint8_t>>
  MstHttpClient::ReadBlock(const std::string& device_name, I2CAddress address, uint32_t offset, uint32_t size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("secondary", std::to_string(static_cast<int>(address.secondary)));
    params.emplace("addr_width", std::to_string(static_cast<int>(address.addr_width)));
    params.emplace("offset", std::to_string(offset));
    params.emplace("size", std::to_string(size));
    auto res = cli_->Get("/device/i2c/read", params);
    if (!res)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_I2C_BLOCK_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_I2C_BLOCK_FAILED, res->body);
    }

    std::vector<uint8_t> result(res->body.begin(), res->body.end());
    return Result<std::vector<uint8_t>>::Ok(result);
}

Result<bool> MstHttpClient::WriteBlock(const std::string& device_name,
                                       I2CAddress address,
                                       uint32_t offset,
                                       char* data,
                                       int data_size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("secondary", std::to_string(static_cast<int>(address.secondary)));
    params.emplace("addr_width", std::to_string(static_cast<int>(address.addr_width)));
    params.emplace("offset", std::to_string(offset));
    std::string path = msthttp::append_query_params("/device/i2c/write", params);
    std::string body(data, static_cast<size_t>(data_size));
    auto res = cli_->Post(path, body, "application/octet-stream");
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_I2C_BLOCK_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_I2C_BLOCK_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

// Cable Operations

Result<std::vector<uint8_t>>
  MstHttpClient::ReadCableBlock(const std::string& device_name, uint32_t address, uint32_t size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("address", std::to_string(address));
    params.emplace("size", std::to_string(size));
    auto res = cli_->Get("/device/cable/read", params);
    if (!res)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_CABLE_BLOCK_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<std::vector<uint8_t>>::Err(ERR_DEVICE_READ_CABLE_BLOCK_FAILED, res->body);
    }

    std::vector<uint8_t> result(res->body.begin(), res->body.end());
    return Result<std::vector<uint8_t>>::Ok(result);
}

Result<bool>
  MstHttpClient::WriteCableBlock(const std::string& device_name, uint32_t address, const uint8_t* data, int data_size)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("address", std::to_string(address));
    std::string path = msthttp::append_query_params("/device/cable/write", params);
    std::string body(reinterpret_cast<const char*>(data), static_cast<size_t>(data_size));
    auto res = cli_->Post(path, body, "application/octet-stream");
    if (!res)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_CABLE_BLOCK_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<bool>::Err(ERR_DEVICE_WRITE_CABLE_BLOCK_FAILED, res->body);
    }
    return Result<bool>::Ok(true);
}

// Firmware Operations

Result<ICmdResponse> MstHttpClient::SendICMD(const std::string& device_name, const ICmdRequest& request)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("opcode", std::to_string(request.opcode));
    params.emplace("skip_write", request.skip_write ? "1" : "0");
    std::string path = msthttp::append_query_params("/device/icmd", params);
    std::string body;
    if (request.data && request.data_size > 0)
        body.assign(request.data, static_cast<size_t>(request.data_size));
    auto res = cli_->Post(path, body, "application/octet-stream");
    if (!res)
    {
        return Result<ICmdResponse>::Err(ERR_DEVICE_SEND_ICMD_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<ICmdResponse>::Err(ERR_DEVICE_SEND_ICMD_FAILED, res->body);
    }

    if (res->body.size() < sizeof(uint32_t))
    {
        return Result<ICmdResponse>::Err(ERR_DEVICE_SEND_ICMD_FAILED, "Short response");
    }

    ICmdResponse resp;
    std::memcpy(&resp.syndrome, res->body.data(), sizeof(uint32_t));
    resp.data = request.data;
    if (request.data && request.data_size > 0 && res->body.size() > sizeof(uint32_t))
    {
        size_t copy_len = res->body.size() - sizeof(uint32_t);
        if (static_cast<int>(copy_len) > request.data_size)
        {
            copy_len = static_cast<size_t>(request.data_size);
        }
        std::memcpy(request.data, res->body.data() + sizeof(uint32_t), copy_len);
    }
    return Result<ICmdResponse>::Ok(resp);
}

Result<RegAccessResponse> MstHttpClient::AccessRegister(const std::string& device_name, const RegAccessRequest& request)
{
    msthttp::Params params;
    params.emplace("device", device_name);
    params.emplace("reg_id", std::to_string(request.reg_id));
    params.emplace("is_write", request.is_write ? "1" : "0");
    std::string path = msthttp::append_query_params("/device/access_register", params);
    std::string body;
    if (request.data && request.data_size > 0)
    {
        body.assign(request.data, static_cast<size_t>(request.data_size));
    }
    auto res = cli_->Post(path, body, "application/octet-stream");
    if (!res)
    {
        return Result<RegAccessResponse>::Err(ERR_DEVICE_ACCESS_REGISTER_FAILED, "HTTP connection failed");
    }
    if (res->status != 200)
    {
        return Result<RegAccessResponse>::Err(ERR_DEVICE_ACCESS_REGISTER_FAILED, res->body);
    }

    if (res->body.size() < sizeof(int32_t))
    {
        return Result<RegAccessResponse>::Err(ERR_DEVICE_ACCESS_REGISTER_FAILED, "Short response");
    }
    RegAccessResponse resp;
    int32_t status = 0;
    std::memcpy(&status, res->body.data(), sizeof(int32_t));
    resp.reg_status = status;
    resp.data = request.data;
    resp.data_size = request.data_size;
    if (request.data && request.data_size > 0 && res->body.size() > sizeof(int32_t))
    {
        size_t copy_len = res->body.size() - sizeof(int32_t);
        if (static_cast<int>(copy_len) > request.data_size)
        {
            copy_len = static_cast<size_t>(request.data_size);
        }
        std::memcpy(request.data, res->body.data() + sizeof(int32_t), copy_len);
        resp.data_size = static_cast<int>(copy_len);
    }
    return Result<RegAccessResponse>::Ok(resp);
}
