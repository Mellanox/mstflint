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

#include "mst_http_client_c_api.h"
#include "MstHttpClient.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

struct mst_http_client
{
    mstserver::MstHttpClient* impl;
};

extern "C"
{
    // Lifecycle

    void mst_http_client_tls_opts_init(mst_http_client_tls_opts_t* opts)
    {
        if (!opts)
        {
            return;
        }
        opts->use_tls = 1;
        opts->policy = MST_TRUST_PROMPT;
        opts->known_hosts_path = nullptr;
        opts->prompt = nullptr;
        opts->prompt_ctx = nullptr;
    }

    mst_http_client_t mst_http_client_create(const char* host, int port)
    {
        return mst_http_client_create_tls(host, port, nullptr);
    }

    mst_http_client_t mst_http_client_create_tls(const char* host, int port, const mst_http_client_tls_opts_t* opts)
    {
        if (!host)
        {
            return nullptr;
        }
        mst_http_client_t c = static_cast<mst_http_client_t>(std::malloc(sizeof(struct mst_http_client)));
        if (!c)
        {
            return nullptr;
        }

        mstserver::MstHttpClient::TlsOptions tls;
        if (opts)
        {
            tls.enabled = opts->use_tls != 0;
            tls.policy = opts->policy;
            tls.known_hosts_path = opts->known_hosts_path ? opts->known_hosts_path : "";
            tls.prompt = opts->prompt;
            tls.prompt_ctx = opts->prompt_ctx;
        }

        c->impl = new (std::nothrow) mstserver::MstHttpClient(host, port, tls);
        if (!c->impl)
        {
            std::free(c);
            return nullptr;
        }
        return c;
    }

    const char* mst_http_client_get_peer_fingerprint(mst_http_client_t client)
    {
        if (!client || !client->impl)
        {
            return nullptr;
        }
        const std::string& fingerprint = client->impl->GetPeerFingerprint();
        return fingerprint.empty() ? nullptr : fingerprint.c_str();
    }

    const char* mst_http_client_get_trust_error(mst_http_client_t client)
    {
        if (!client || !client->impl)
        {
            return nullptr;
        }
        const std::string& error = client->impl->GetTrustError();
        return error.empty() ? nullptr : error.c_str();
    }

    int mst_http_client_get_last_status(mst_http_client_t client)
    {
        if (!client || !client->impl)
        {
            return 0;
        }
        return client->impl->GetLastStatus();
    }

    void mst_http_client_destroy(mst_http_client_t client)
    {
        if (!client)
        {
            return;
        }
        delete client->impl;
        std::free(client);
    }

    int mst_http_client_is_available(mst_http_client_t client)
    {
        if (!client || !client->impl)
        {
            return 0;
        }
        return client->impl->IsAvailable() ? 1 : 0;
    }

    int mst_http_client_login(mst_http_client_t client, const char* passphrase)
    {
        if (!client || !client->impl || !passphrase)
        {
            return -1;
        }
        return client->impl->Login(passphrase) ? 0 : -1;
    }

    const char* mst_http_client_get_token(mst_http_client_t client)
    {
        if (!client || !client->impl)
        {
            return nullptr;
        }
        const std::string& tok = client->impl->GetToken();
        return tok.empty() ? nullptr : tok.c_str();
    }

    void mst_http_client_set_token(mst_http_client_t client, const char* token)
    {
        if (!client || !client->impl || !token)
        {
            return;
        }
        client->impl->SetToken(token);
    }

    // System

    int mst_http_client_get_version(mst_http_client_t client, char* out, int out_len)
    {
        if (!client || !client->impl || !out || out_len <= 0)
        {
            return -1;
        }
        auto r = client->impl->GetVersion();
        if (!r.success)
        {
            return -1;
        }
        std::strncpy(out, r.value.c_str(), static_cast<size_t>(out_len - 1));
        out[out_len - 1] = '\0';
        return 0;
    }

    int mst_http_client_get_devices(mst_http_client_t client, char*** out_devices, int* out_count)
    {
        if (!client || !client->impl || !out_devices || !out_count)
        {
            return -1;
        }
        auto r = client->impl->GetDevices();
        if (!r.success)
        {
            return -1;
        }

        int count = static_cast<int>(r.value.size());
        char** arr = static_cast<char**>(std::malloc(sizeof(char*) * static_cast<size_t>(count)));
        if (!arr && count > 0)
        {
            return -1;
        }

        for (int i = 0; i < count; i++)
        {
            arr[i] = static_cast<char*>(std::malloc(r.value[static_cast<size_t>(i)].size() + 1));
            if (!arr[i])
            {
                for (int j = 0; j < i; j++)
                {
                    std::free(arr[j]);
                }
                std::free(arr);
                return -1;
            }
            std::strcpy(arr[i], r.value[static_cast<size_t>(i)].c_str());
        }
        *out_devices = arr;
        *out_count = count;
        return 0;
    }

    void mst_http_client_free_devices(char** devices, int count)
    {
        if (!devices)
        {
            return;
        }
        for (int i = 0; i < count; i++)
        {
            std::free(devices[i]);
        }
        std::free(devices);
    }

    int mst_http_client_get_capabilities(mst_http_client_t client, uint32_t* out)
    {
        if (!client || !client->impl || !out)
        {
            return -1;
        }
        auto r = client->impl->GetCapabilities();
        if (!r.success)
        {
            return -1;
        }
        *out = r.value;
        return 0;
    }

    // Device management

    int mst_http_client_open_device(mst_http_client_t client,
                                    const char* device,
                                    uint32_t device_type,
                                    int force_i2c_address)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->OpenDevice(device, device_type, force_i2c_address);
        return r.success ? 0 : -1;
    }

    int mst_http_client_close_device(mst_http_client_t client, const char* device)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->CloseDevice(device);
        return r.success ? 0 : -1;
    }

    // Device info

    int mst_http_client_get_device_id(mst_http_client_t client, const char* device, uint32_t* out)
    {
        if (!client || !client->impl || !device || !out)
        {
            return -1;
        }
        auto r = client->impl->GetDeviceId(device);
        if (!r.success)
        {
            return -1;
        }
        *out = r.value;
        return 0;
    }

    int mst_http_client_get_pci_device_id(mst_http_client_t client, const char* device, uint32_t* out)
    {
        if (!client || !client->impl || !device || !out)
        {
            return -1;
        }
        auto r = client->impl->GetPciDeviceId(device);
        if (!r.success)
        {
            return -1;
        }
        *out = r.value;
        return 0;
    }

    // Register access

    int mst_http_client_read32(mst_http_client_t client, const char* device, uint64_t offset, uint32_t* out)
    {
        if (!client || !client->impl || !device || !out)
        {
            return -1;
        }
        auto r = client->impl->Read32(device, offset);
        if (!r.success)
        {
            return -1;
        }
        *out = r.value;
        return 0;
    }

    int mst_http_client_write32(mst_http_client_t client, const char* device, uint64_t offset, uint32_t value)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->Write32(device, offset, value);
        return r.success ? 0 : -1;
    }

    int
      mst_http_client_read_block(mst_http_client_t client, const char* device, uint64_t offset, uint32_t* data, int size)
    {
        if (!client || !client->impl || !device || !data || size <= 0)
        {
            return -1;
        }
        auto r = client->impl->ReadBlock(device, offset, data, size);
        return r.success ? 0 : -1;
    }

    int mst_http_client_write_block(mst_http_client_t client,
                                    const char* device,
                                    uint64_t offset,
                                    uint32_t* data,
                                    int size)
    {
        if (!client || !client->impl || !device || !data || size <= 0)
        {
            return -1;
        }
        auto r = client->impl->WriteBlock(device, offset, data, size);
        return r.success ? 0 : -1;
    }

    int mst_http_client_set_address_space(mst_http_client_t client, const char* device, int space)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->SetAddressSpace(device, space);
        return r.success ? 0 : -1;
    }

    int mst_http_client_pci_change(mst_http_client_t client, const char* device)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->PciChange(device);
        return r.success ? 0 : -1;
    }

    // I2C

    int mst_http_client_scan_i2c(mst_http_client_t client, const char* device, uint8_t** out_addrs, int* out_count)
    {
        if (!client || !client->impl || !device || !out_addrs || !out_count)
        {
            return -1;
        }
        auto r = client->impl->ScanI2C(device);
        if (!r.success)
        {
            return -1;
        }

        int count = static_cast<int>(r.value.addresses.size());
        uint8_t* arr = nullptr;
        if (count > 0)
        {
            arr = static_cast<uint8_t*>(std::malloc(static_cast<size_t>(count)));
            if (!arr)
            {
                return -1;
            }
            std::memcpy(arr, r.value.addresses.data(), static_cast<size_t>(count));
        }
        *out_addrs = arr;
        *out_count = count;
        return 0;
    }

    void mst_http_client_free_i2c_scan(uint8_t* addrs)
    {
        std::free(addrs);
    }

    int mst_http_client_set_i2c_secondary(mst_http_client_t client, const char* device, uint8_t address)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }
        auto r = client->impl->SetI2CSecondary(device, address);
        return r.success ? 0 : -1;
    }

    int mst_http_client_i2c_read(mst_http_client_t client,
                                 const char* device,
                                 uint8_t secondary,
                                 uint8_t addr_width,
                                 uint32_t offset,
                                 uint32_t size,
                                 uint8_t** out_data,
                                 int* out_len)
    {
        if (!client || !client->impl || !device || !out_data || !out_len)
        {
            return -1;
        }

        mstserver::I2CAddress addr;
        addr.secondary = secondary;
        addr.addr_width = addr_width;
        auto r = client->impl->ReadBlock(device, addr, offset, size);
        if (!r.success)
        {
            return -1;
        }

        int len = static_cast<int>(r.value.size());
        uint8_t* buf = nullptr;
        if (len > 0)
        {
            buf = static_cast<uint8_t*>(std::malloc(static_cast<size_t>(len)));
            if (!buf)
            {
                return -1;
            }
            std::memcpy(buf, r.value.data(), static_cast<size_t>(len));
        }
        *out_data = buf;
        *out_len = len;
        return 0;
    }

    void mst_http_client_free_i2c_data(uint8_t* data)
    {
        std::free(data);
    }

    int mst_http_client_i2c_write(mst_http_client_t client,
                                  const char* device,
                                  uint8_t secondary,
                                  uint8_t addr_width,
                                  uint32_t offset,
                                  const uint8_t* data,
                                  int data_size)
    {
        if (!client || !client->impl || !device || (!data && data_size > 0))
        {
            return -1;
        }

        mstserver::I2CAddress addr;
        addr.secondary = secondary;
        addr.addr_width = addr_width;

        auto r = client->impl->WriteBlock(device, addr, offset, const_cast<char*>(reinterpret_cast<const char*>(data)),
                                          data_size);
        return r.success ? 0 : -1;
    }

    // Cable

    int mst_http_client_cable_read(mst_http_client_t client,
                                   const char* device,
                                   uint32_t address,
                                   uint8_t* data,
                                   uint32_t size)
    {
        if (!client || !client->impl || !device || !data || size == 0)
        {
            return -1;
        }
        auto r = client->impl->ReadCableBlock(device, address, size);
        if (!r.success)
        {
            return -1;
        }
        // A short read is a truncated transfer, not a partial success: the
        // caller has no length to report it with, so refuse instead of leaving
        // the tail of its buffer holding whatever was there before.
        if (r.value.size() != static_cast<size_t>(size))
        {
            return -1;
        }
        std::memcpy(data, r.value.data(), static_cast<size_t>(size));
        return 0;
    }

    int mst_http_client_cable_write(mst_http_client_t client,
                                    const char* device,
                                    uint32_t address,
                                    const uint8_t* data,
                                    uint32_t size)
    {
        if (!client || !client->impl || !device || !data || size == 0)
        {
            return -1;
        }
        auto r = client->impl->WriteCableBlock(device, address, data, static_cast<int>(size));
        return r.success ? 0 : -1;
    }

    // Firmware

    int mst_http_client_send_icmd(mst_http_client_t client,
                                  const char* device,
                                  uint32_t opcode,
                                  char* data,
                                  int data_size,
                                  int skip_write,
                                  uint32_t* out_syndrome)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }

        mstserver::ICmdRequest req;
        req.opcode = opcode;
        req.data = data;
        req.data_size = data_size;
        req.skip_write = (skip_write != 0);

        auto r = client->impl->SendICMD(device, req);
        if (!r.success)
        {
            return -1;
        }
        if (out_syndrome)
        {
            *out_syndrome = r.value.syndrome;
        }
        return 0;
    }

    int mst_http_client_access_register(mst_http_client_t client,
                                        const char* device,
                                        uint32_t reg_id,
                                        char* data,
                                        int data_size,
                                        int is_write,
                                        int* out_reg_status)
    {
        if (!client || !client->impl || !device)
        {
            return -1;
        }

        mstserver::RegAccessRequest req;
        req.reg_id = reg_id;
        req.data = data;
        req.data_size = data_size;
        req.is_write = (is_write != 0);

        auto r = client->impl->AccessRegister(device, req);
        if (out_reg_status)
        {
            // Carry the FW status back on both success and failure so the caller
            // can report the exact device error rather than a generic message.
            *out_reg_status = r.value.reg_status;
        }
        return r.success ? 0 : -1;
    }

} // extern "C"
