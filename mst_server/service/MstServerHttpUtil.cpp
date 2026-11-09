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

#include "mst_server/service/MstServerHttpUtil.h"

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace mstserver
{
namespace http
{

const unsigned int PASSPHRASE_KDF_ITERATIONS = 150000;

namespace
{

// PBKDF2-HMAC-SHA256 rather than argon2id: argon2 needs OpenSSL 3.2, and this
// has to build against whatever OpenSSL each packaged platform ships.
bool derive(const std::string& passphrase,
            const unsigned char* salt,
            size_t salt_len,
            unsigned char* out,
            size_t out_len)
{
    return PKCS5_PBKDF2_HMAC(passphrase.data(), static_cast<int>(passphrase.size()), salt, static_cast<int>(salt_len),
                             static_cast<int>(PASSPHRASE_KDF_ITERATIONS), EVP_sha256(), static_cast<int>(out_len),
                             out) == 1;
}

} // namespace

bool BearerAuth::SetPassphrase(const std::string& passphrase)
{
    if (RAND_bytes(salt, static_cast<int>(sizeof(salt))) != 1)
    {
        return false;
    }
    return derive(passphrase, salt, sizeof(salt), derived, sizeof(derived));
}

bool BearerAuth::VerifyPassphrase(const std::string& passphrase) const
{
    unsigned char candidate[sizeof(derived)];

    if (!derive(passphrase, salt, sizeof(salt), candidate, sizeof(candidate)))
    {
        return false;
    }
    const bool match = CRYPTO_memcmp(candidate, derived, sizeof(candidate)) == 0;
    OPENSSL_cleanse(candidate, sizeof(candidate));
    return match;
}

// Helpers: params (query string or form-urlencoded body) and parsing.
// The client sends GET params in the query string and POST params as an
// application/x-www-form-urlencoded body, so look in both places.
std::string get_param(const crow::request& req, const std::string& key)
{
    const char* v = req.url_params.get(key);
    if (v != nullptr)
    {
        return v;
    }
    const std::string& content_type = req.get_header_value("Content-Type");
    if (content_type.find("application/x-www-form-urlencoded") != std::string::npos)
    {
        const crow::query_string body_params = req.get_body_params();
        const char* b = body_params.get(key);
        if (b != nullptr)
        {
            return b;
        }
    }
    return "";
}

crow::response text_response(int code, const std::string& body)
{
    crow::response res(code, body);
    res.set_header("Content-Type", "text/plain");
    return res;
}

crow::response binary_response(const char* data, size_t size)
{
    crow::response res(200, std::string(data, size));
    res.set_header("Content-Type", "application/octet-stream");
    return res;
}

crow::response param_missing(const std::string& key)
{
    return text_response(400, "missing parameter: " + key);
}

static bool is_valid_number(const std::string& s, bool allow_sign)
{
    if (s.empty())
    {
        return false;
    }
    size_t i = (allow_sign && s[0] == '-') ? 1 : 0;
    return i < s.size() && std::isdigit(static_cast<unsigned char>(s[i])) != 0;
}

bool parse_uint64(const std::string& s, uint64_t* out)
{
    if (!is_valid_number(s, false))
    {
        return false;
    }
    errno = 0;
    char* end = nullptr;
    unsigned long long v = std::strtoull(s.c_str(), &end, 0);
    if (*end != '\0' || errno == ERANGE)
    {
        return false;
    }
    *out = static_cast<uint64_t>(v);
    return true;
}

bool parse_uint32(const std::string& s, uint32_t* out)
{
    // Range-checked against uint32_t rather than narrowed: strtoul returns a
    // 64-bit unsigned long here and a 32-bit one on Windows and armv5te, so a
    // direct cast would give a different answer per platform and no error.
    uint64_t v = 0;
    if (!parse_uint64(s, &v) || v > UINT32_MAX)
    {
        return false;
    }
    *out = static_cast<uint32_t>(v);
    return true;
}

bool parse_int(const std::string& s, int* out)
{
    // strtoll rather than strtol so the range check below behaves the same way
    // whatever width long has. A leading '-' is legitimate here.
    if (!is_valid_number(s, true))
    {
        return false;
    }
    errno = 0;
    char* end = nullptr;
    long long v = std::strtoll(s.c_str(), &end, 0);
    if (*end != '\0' || errno == ERANGE || v < INT_MIN || v > INT_MAX)
    {
        return false;
    }
    *out = static_cast<int>(v);
    return true;
}

crow::response error_response(int code, const std::string& msg)
{
    return text_response((code >= 400 && code < 600) ? code : 500, msg);
}

std::string generate_random_hex(size_t n_bytes)
{
    std::vector<unsigned char> buf(n_bytes);
    if (RAND_priv_bytes(buf.data(), static_cast<int>(n_bytes)) != 1)
    {
        return std::string();
    }

    std::string hex;
    hex.reserve(n_bytes * 2);
    static const char digits[] = "0123456789abcdef";
    for (size_t i = 0; i < n_bytes; i++)
    {
        hex.push_back(digits[buf[i] >> 4]);
        hex.push_back(digits[buf[i] & 0x0f]);
    }
    return hex;
}

std::string generate_token()
{
    return generate_random_hex(32);
}

std::string extract_bearer_token(const crow::request& req)
{
    const std::string& auth = req.get_header_value("Authorization");
    const std::string prefix = "Bearer ";
    if (auth.size() > prefix.size() && auth.substr(0, prefix.size()) == prefix)
    {
        return auth.substr(prefix.size());
    }
    return "";
}

void BearerAuth::before_handle(crow::request& req, crow::response& res, context&)
{
    if (!required)
    {
        return;
    }
    if (req.url == "/health" || req.url == "/login")
    {
        return;
    }
    std::string token = extract_bearer_token(req);
    if (!token.empty())
    {
        std::lock_guard<std::mutex> lock(tokens_mutex);
        if (active_tokens.find(token) != active_tokens.end())
        {
            return;
        }
    }
    res.code = 401;
    res.set_header("Content-Type", "text/plain");
    res.body = "unauthorized: valid session token required";
    res.end();
}

} // namespace http
} // namespace mstserver
