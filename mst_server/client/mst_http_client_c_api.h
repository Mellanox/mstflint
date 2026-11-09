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

#ifndef MST_HTTP_CLIENT_C_API_H
#define MST_HTTP_CLIENT_C_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct mst_http_client* mst_http_client_t;

    /* ========================================================================== */
    /* TLS and server trust                                                       */
    /* ========================================================================== */

    /* What to do about a server whose key has never been seen before.

       A key that is known but no longer matches is refused under every policy:
       that mismatch is the one signal the trust store exists to raise, and no
       flag may wave it through. */
    typedef enum
    {
        /* Ask, on a terminal. With no terminal to ask on, warn and accept - the
           prompt is new and automated callers predate it. */
        MST_TRUST_PROMPT = 0,
        /* Accept an unknown server without asking ("mst remote add -y"). */
        MST_TRUST_ACCEPT_NEW = 1,
        /* Refuse anything not already recorded. */
        MST_TRUST_STRICT = 2
    } mst_trust_policy_t;

    /* Returns non-zero to trust `fingerprint` as the identity of host:port. */
    typedef int (*mst_trust_prompt_fn)(const char* host, int port, const char* fingerprint, void* ctx);

    typedef struct
    {
        int use_tls; /* 0 talks plaintext HTTP */
        mst_trust_policy_t policy;
        const char* known_hosts_path; /* NULL selects the default trust store */
        mst_trust_prompt_fn prompt;   /* NULL asks on the terminal */
        void* prompt_ctx;
    } mst_http_client_tls_opts_t;

    /* TLS on, MST_TRUST_PROMPT, default store, built-in terminal prompt. */
    void mst_http_client_tls_opts_init(mst_http_client_tls_opts_t* opts);

    /* ========================================================================== */
    /* Lifecycle                                                                  */
    /* ========================================================================== */

    /* Equivalent to mst_http_client_create_tls() with the defaults above. */
    mst_http_client_t mst_http_client_create(const char* host, int port);

    mst_http_client_t mst_http_client_create_tls(const char* host, int port, const mst_http_client_tls_opts_t* opts);

    /* The server's public-key fingerprint from the last handshake; NULL when no
       handshake completed. */
    const char* mst_http_client_get_peer_fingerprint(mst_http_client_t client);

    /* Why the server was refused, NULL when it was not.

       Callers must not treat a refusal like "nothing is listening": retrying
       over a weaker transport after a refusal hands an attacker the downgrade
       the refusal just prevented. */
    const char* mst_http_client_get_trust_error(mst_http_client_t client);

    /* HTTP status of the last response, 0 if none arrived. A 401 says the
       server wants a passphrase - a refusal no other transport can satisfy, so
       it must never be retried elsewhere. */
    int mst_http_client_get_last_status(mst_http_client_t client);
    void mst_http_client_destroy(mst_http_client_t client);
    int mst_http_client_is_available(mst_http_client_t client);
    /* Sends the passphrase over the TLS channel. The server derives and compares
       a salted verifier, so there is nothing to hash here. */
    int mst_http_client_login(mst_http_client_t client, const char* passphrase);
    const char* mst_http_client_get_token(mst_http_client_t client);
    void mst_http_client_set_token(mst_http_client_t client, const char* token);

    /* ========================================================================== */
    /* System                                                                     */
    /* ========================================================================== */

    int mst_http_client_get_version(mst_http_client_t client, char* out, int out_len);

    int mst_http_client_get_devices(mst_http_client_t client, char*** out_devices, int* out_count);

    void mst_http_client_free_devices(char** devices, int count);

    /* Bitmask of the optional features the server implements, in the encoding of
       mtcr's LONG_ADDRESS_SUPPORT_MASK. */
    int mst_http_client_get_capabilities(mst_http_client_t client, uint32_t* out);

    /* ========================================================================== */
    /* Device management                                                          */
    /* ========================================================================== */

    /* force_i2c_address is the I2C secondary to open with, or -1 for none. */
    int mst_http_client_open_device(mst_http_client_t client,
                                    const char* device,
                                    uint32_t device_type,
                                    int force_i2c_address);

    int mst_http_client_close_device(mst_http_client_t client, const char* device);

    /* ========================================================================== */
    /* Device info                                                                */
    /* ========================================================================== */

    int mst_http_client_get_device_id(mst_http_client_t client, const char* device, uint32_t* out);

    int mst_http_client_get_pci_device_id(mst_http_client_t client, const char* device, uint32_t* out);

    /* ========================================================================== */
    /* Register access                                                            */
    /* ========================================================================== */

    int mst_http_client_read32(mst_http_client_t client, const char* device, uint64_t offset, uint32_t* out);

    int mst_http_client_write32(mst_http_client_t client, const char* device, uint64_t offset, uint32_t value);

    int mst_http_client_read_block(mst_http_client_t client,
                                   const char* device,
                                   uint64_t offset,
                                   uint32_t* data,
                                   int size);

    int mst_http_client_write_block(mst_http_client_t client,
                                    const char* device,
                                    uint64_t offset,
                                    uint32_t* data,
                                    int size);

    int mst_http_client_set_address_space(mst_http_client_t client, const char* device, int space);

    /* Switches the handle between CONF and CR access (mtcr's mpci_change). */
    int mst_http_client_pci_change(mst_http_client_t client, const char* device);

    /* ========================================================================== */
    /* I2C                                                                        */
    /* ========================================================================== */

    int mst_http_client_scan_i2c(mst_http_client_t client, const char* device, uint8_t** out_addrs, int* out_count);

    void mst_http_client_free_i2c_scan(uint8_t* addrs);

    int mst_http_client_set_i2c_secondary(mst_http_client_t client, const char* device, uint8_t address);

    int mst_http_client_i2c_read(mst_http_client_t client,
                                 const char* device,
                                 uint8_t secondary,
                                 uint8_t addr_width,
                                 uint32_t offset,
                                 uint32_t size,
                                 uint8_t** out_data,
                                 int* out_len);

    void mst_http_client_free_i2c_data(uint8_t* data);

    int mst_http_client_i2c_write(mst_http_client_t client,
                                  const char* device,
                                  uint8_t secondary,
                                  uint8_t addr_width,
                                  uint32_t offset,
                                  const uint8_t* data,
                                  int data_size);

    /* ========================================================================== */
    /* Cable                                                                      */
    /* ========================================================================== */

    /* Byte-granular cable access. Both fill or read a caller-owned buffer, and
       `size` may not exceed CABLES_REMOTE_BUF_DATA_SIZE - the caller splits a
       longer transfer into chunks of that size. */
    int mst_http_client_cable_read(mst_http_client_t client,
                                   const char* device,
                                   uint32_t address,
                                   uint8_t* data,
                                   uint32_t size);

    int mst_http_client_cable_write(mst_http_client_t client,
                                    const char* device,
                                    uint32_t address,
                                    const uint8_t* data,
                                    uint32_t size);

    /* ========================================================================== */
    /* Firmware                                                                   */
    /* ========================================================================== */

    int mst_http_client_send_icmd(mst_http_client_t client,
                                  const char* device,
                                  uint32_t opcode,
                                  char* data,
                                  int data_size,
                                  int skip_write,
                                  uint32_t* out_syndrome);

    int mst_http_client_access_register(mst_http_client_t client,
                                        const char* device,
                                        uint32_t reg_id,
                                        char* data,
                                        int data_size,
                                        int is_write,
                                        int* out_reg_status);

#ifdef __cplusplus
}
#endif

#endif /* MST_HTTP_CLIENT_C_API_H */
