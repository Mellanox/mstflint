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

#ifndef MST_SERVER_HTTP_UTIL_H
#define MST_SERVER_HTTP_UTIL_H

#include <crow.h>

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_set>

namespace mstserver
{
namespace http
{

// PBKDF2-HMAC-SHA256 rounds for the passphrase verifier. High enough to price a
// dictionary attack on a stolen verifier, low enough that /login - which is
// unauthenticated - is not a useful way to burn the server's CPU.
extern const unsigned int PASSPHRASE_KDF_ITERATIONS;

// `n_bytes` CSPRNG bytes as lowercase hex. Empty when the RNG fails, which
// callers must treat as fatal rather than proceeding with a weak secret.
std::string generate_random_hex(size_t n_bytes);

// Session token handed out by /login: 32 CSPRNG bytes as lowercase hex.
std::string generate_token();

// The client sends GET params in the query string and POST params as an
// application/x-www-form-urlencoded body, so look in both places.
std::string get_param(const crow::request& req, const std::string& key);

// Token from an "Authorization: Bearer <token>" header, empty when absent.
std::string extract_bearer_token(const crow::request& req);

crow::response text_response(int code, const std::string& body);
crow::response binary_response(const char* data, size_t size);
crow::response param_missing(const std::string& key);
crow::response error_response(int code, const std::string& msg);

// Numeric query parameters, parsed with base 0 so callers may send decimal or
// 0x-prefixed hex.
bool parse_uint64(const std::string& s, uint64_t* out);
bool parse_uint32(const std::string& s, uint32_t* out);
bool parse_int(const std::string& s, int* out);

// Requires a valid Bearer token on every request except /health and /login.
//
// The passphrase is held as a salted PBKDF2 verifier, not as a digest: a digest
// is what /login compares against, so reading it out of the process is enough to
// replay it. The per-process salt also keeps a stolen verifier useless against
// any other server sharing the same passphrase.
struct BearerAuth
{
    struct context
    {
    };

    // Fail closed: a server that forgets to configure authentication rejects
    // requests rather than serving them. Only a test harness driving the
    // routes directly should clear this.
    bool required = true;
    unsigned char salt[16] = {0};
    unsigned char derived[32] = {0};
    std::unordered_set<std::string> active_tokens;
    std::mutex tokens_mutex;

    // Draws a fresh salt and derives the verifier; the caller should scrub
    // `passphrase` afterwards. On false the server must not start - an unset
    // verifier accepts nothing at all.
    bool SetPassphrase(const std::string& passphrase);

    // Constant-time: a byte-at-a-time compare leaks how much of a guess was
    // right, which turns an offline problem into an online one.
    bool VerifyPassphrase(const std::string& passphrase) const;

    void before_handle(crow::request& req, crow::response& res, context&);

    void after_handle(crow::request&, crow::response&, context&) {}
};

using MstApp = crow::App<BearerAuth>;

} // namespace http
} // namespace mstserver

#endif // MST_SERVER_HTTP_UTIL_H
