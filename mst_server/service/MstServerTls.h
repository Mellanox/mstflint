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

#ifndef MST_SERVER_TLS_H
#define MST_SERVER_TLS_H

#include <string>

namespace mstserver
{
namespace tls
{

// Root-only home for the server's long-lived TLS identity, alongside the
// credentials cache the SSH transport already keeps there.
extern const char* const DEFAULT_IDENTITY_DIR;

struct Identity
{
    std::string cert_path;
    std::string key_path;
    // What clients pin; see public_key_fingerprint() in MstTlsFingerprint.h.
    std::string fingerprint;
};

// Loads the identity from `dir`, creating what is missing: a P-256 key pair on
// first run, and a self-signed certificate whenever the stored one is absent or
// does not match the stored key.
//
// The key is generated once and kept forever. Clients pin it, so rotating it
// makes every one of them refuse to connect until an operator clears the entry.
//
// On false the caller must not fall back to plaintext: a client expecting TLS
// would be talking to a server that cannot prove who it is.
bool ensure_identity(const std::string& dir, Identity* out, std::string* error);

} // namespace tls
} // namespace mstserver

#endif // MST_SERVER_TLS_H
