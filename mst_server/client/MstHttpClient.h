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

#ifndef MST_HTTP_CLIENT_H
#define MST_HTTP_CLIENT_H

#include "mst_server/client/mst_http_client_c_api.h"
#include "mst_server/service/MstServerService.h"

#include <string>
#include <cstdint>
#include <memory>

// HTTP transport (Crow has no client): a small HTTP/1.1 layer over libcurl,
// held by pointer so MstCurlClient.h - and with it <curl.h> - stays
// out of this header.
namespace msthttp
{
class Client;
}

namespace mstserver
{

class MstHttpClient : public MstServerService
{
public:
    // C++ mirror of mst_http_client_tls_opts_t.
    struct TlsOptions
    {
        bool enabled = true;
        mst_trust_policy_t policy = MST_TRUST_PROMPT;
        std::string known_hosts_path;         // empty: MstKnownHosts::DefaultPath()
        mst_trust_prompt_fn prompt = nullptr; // null: ask on the terminal
        void* prompt_ctx = nullptr;
    };

    MstHttpClient(const std::string& host, int port);
    MstHttpClient(const std::string& host, int port, const TlsOptions& tls);
    // Defined in the .cpp: unique_ptr needs msthttp::Client complete to destroy it.
    ~MstHttpClient() override;

    bool IsAvailable();
    // Sends the passphrase itself, over TLS. Deliberately not a digest: the
    // server compares against a salted verifier it derives, so anything derived
    // here would just become the credential in the passphrase's place.
    bool Login(const std::string& passphrase);
    void SetToken(const std::string& token);
    const std::string& GetToken() const;

    // The key the server proved it holds, empty until a handshake completes.
    const std::string& GetPeerFingerprint() const;

    // Set only when the server was reachable but its identity was refused.
    // Empty when the server simply did not answer, which callers must handle
    // differently - see mst_http_client_get_trust_error().
    const std::string& GetTrustError() const;

    // HTTP status of the last response, 0 if none arrived. 401 in particular
    // means the server wants a passphrase, which no other transport can supply.
    int GetLastStatus() const;

    Result<std::string> GetVersion() override;
    Result<std::vector<std::string>> GetDevices() override;
    Result<uint32_t> GetCapabilities() override;

    Result<bool> OpenDevice(const std::string& device_name, uint32_t device_type, int force_i2c_address) override;
    Result<bool> CloseDevice(const std::string& device_name) override;

    Result<uint32_t> GetDeviceId(const std::string& device_name) override;
    Result<uint32_t> GetPciDeviceId(const std::string& device_name) override;

    Result<uint32_t> Read32(const std::string& device_name, uint64_t offset) override;
    Result<bool> Write32(const std::string& device_name, uint64_t offset, uint32_t value) override;
    Result<bool> ReadBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) override;
    Result<bool> WriteBlock(const std::string& device_name, uint64_t offset, uint32_t* data, int data_size) override;
    Result<bool> SetAddressSpace(const std::string& device_name, int space) override;
    Result<bool> PciChange(const std::string& device_name) override;

    Result<I2CScanResult> ScanI2C(const std::string& device_name) override;
    Result<bool> SetI2CSecondary(const std::string& device_name, uint8_t address) override;
    Result<std::vector<uint8_t>>
      ReadBlock(const std::string& device_name, I2CAddress address, uint32_t offset, uint32_t size) override;
    Result<bool> WriteBlock(const std::string& device_name,
                            I2CAddress address,
                            uint32_t offset,
                            char* data,
                            int data_size) override;

    Result<std::vector<uint8_t>>
      ReadCableBlock(const std::string& device_name, uint32_t address, uint32_t size) override;
    Result<bool>
      WriteCableBlock(const std::string& device_name, uint32_t address, const uint8_t* data, int data_size) override;

    Result<ICmdResponse> SendICMD(const std::string& device_name, const ICmdRequest& request) override;
    Result<RegAccessResponse> AccessRegister(const std::string& device_name, const RegAccessRequest& request) override;

private:
    void Init(const TlsOptions& tls);

    // Called once per handshake with the server's public-key fingerprint,
    // before any request is sent. Returns false to abort the connection.
    bool DecideTrust(const std::string& fingerprint);

    // Asks the user on the terminal, in the shape of SSH's first-contact
    // question. Returns true when they answer yes.
    bool AskOnTerminal(const std::string& fingerprint) const;

    std::unique_ptr<msthttp::Client> cli_;
    std::string host_;
    int port_ = 0;
    TlsOptions tls_;
    std::string peer_fingerprint_;
    std::string trust_error_;
    std::string token_;
    bool available_ = false;
};

} // namespace mstserver

#endif // MST_HTTP_CLIENT_H
