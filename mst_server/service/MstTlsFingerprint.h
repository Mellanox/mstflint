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

// The one definition of "who is this server", shared by the server that prints
// it and the client that pins it. If the two ever disagree for the same key,
// trust-on-first-use degrades into prompting on every connection.

#ifndef MST_TLS_FINGERPRINT_H
#define MST_TLS_FINGERPRINT_H

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/x509.h>

#include <string>

namespace mstserver
{
namespace tls
{

// SHA-256 over the DER SubjectPublicKeyInfo, base64 without padding - the shape
// ssh-keygen prints, so the trust prompt reads like the SSH one.
//
// Covering the key rather than the certificate lets the server re-issue an
// expired certificate without invalidating every client's pin.
//
// Empty means "identity unknown", never "identity matches".
inline std::string public_key_fingerprint(X509* cert)
{
    if (cert == nullptr)
    {
        return "";
    }
    X509_PUBKEY* pubkey = X509_get_X509_PUBKEY(cert);
    if (pubkey == nullptr)
    {
        return "";
    }

    unsigned char* der = nullptr;
    const int der_len = i2d_X509_PUBKEY(pubkey, &der);
    if (der_len <= 0 || der == nullptr)
    {
        return "";
    }
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(der, static_cast<size_t>(der_len), digest);
    OPENSSL_free(der);

    // EVP_EncodeBlock emits 4 characters per 3 input bytes plus a terminator:
    // 45 bytes for a 32-byte digest.
    unsigned char b64[64] = {0};
    const int b64_len = EVP_EncodeBlock(b64, digest, SHA256_DIGEST_LENGTH);
    if (b64_len <= 0)
    {
        return "";
    }
    std::string encoded(reinterpret_cast<const char*>(b64), static_cast<size_t>(b64_len));
    while (!encoded.empty() && encoded[encoded.size() - 1] == '=')
    {
        encoded.erase(encoded.size() - 1);
    }
    return "SHA256:" + encoded;
}

} // namespace tls
} // namespace mstserver

#endif // MST_TLS_FINGERPRINT_H
