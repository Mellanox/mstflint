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

#include "mst_server/service/MstServerTls.h"
#include "mst_server/service/MstTlsFingerprint.h"

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/obj_mac.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <cerrno>
#include <filesystem>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#ifndef __WIN__
#include <fcntl.h>
#include <unistd.h>
#endif

// ESX's user-world headers do not define it. The symlink refusal is a
// hardening measure, so a platform that lacks it still builds.
#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

namespace mstserver
{
namespace tls
{

const char* const DEFAULT_IDENTITY_DIR = "/var/lib/mstflint/mst_server";

namespace
{

// Ten years: the certificate is pinned by key, not validated by a CA, so a
// short lifetime would only buy operational churn.
const long CERT_VALIDITY_SECONDS = 10L * 365L * 24L * 3600L;
// Tolerates a client whose clock trails the server's at first contact.
const long CERT_BACKDATE_SECONDS = 24L * 3600L;

std::string openssl_error()
{
    const unsigned long code = ERR_get_error();
    if (code == 0)
    {
        return "unknown OpenSSL error";
    }
    char buf[256] = {0};
    ERR_error_string_n(code, buf, sizeof(buf));
    return buf;
}

bool fail(std::string* error, const std::string& message)
{
    if (error != nullptr)
    {
        *error = message;
    }
    return false;
}

// Opens `path` for writing with owner-only permissions from the moment it
// exists. Creating it world-readable and chmod'ing afterwards would leave the
// private key exposed for the length of the write.
FILE* open_private_file(const std::string& path)
{
#ifdef __WIN__
    // The install directory is administrator-protected; there is no portable
    // equivalent of the POSIX creation mode here.
    return fopen(path.c_str(), "wb");
#else
    const int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        return nullptr;
    }
    FILE* f = fdopen(fd, "wb");
    if (f == nullptr)
    {
        close(fd);
    }
    return f;
#endif
}

EVP_PKEY* read_key(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");
    if (f == nullptr)
    {
        return nullptr;
    }
    EVP_PKEY* key = PEM_read_PrivateKey(f, nullptr, nullptr, nullptr);
    fclose(f);
    return key;
}

X509* read_cert(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");
    if (f == nullptr)
    {
        return nullptr;
    }
    X509* cert = PEM_read_X509(f, nullptr, nullptr, nullptr);
    fclose(f);
    return cert;
}

EVP_PKEY* generate_key(std::string* error)
{
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, nullptr);
    if (ctx == nullptr)
    {
        fail(error, "cannot allocate an EC key context: " + openssl_error());
        return nullptr;
    }
    EVP_PKEY* key = nullptr;
    if (EVP_PKEY_keygen_init(ctx) <= 0 || EVP_PKEY_CTX_set_ec_paramgen_curve_nid(ctx, NID_X9_62_prime256v1) <= 0 ||
        EVP_PKEY_keygen(ctx, &key) <= 0)
    {
        fail(error, "cannot generate a P-256 key pair: " + openssl_error());
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }
    EVP_PKEY_CTX_free(ctx);
    return key;
}

bool set_random_serial(X509* cert, std::string* error)
{
    // A random serial rather than a counter: nothing persists issuance state
    // across the re-issues this function performs.
    unsigned char bytes[8] = {0};
    if (RAND_bytes(bytes, sizeof(bytes)) != 1)
    {
        return fail(error, "cannot draw a certificate serial: " + openssl_error());
    }
    int64_t serial = 0;
    for (size_t i = 0; i < sizeof(bytes); i++)
    {
        serial = (serial << 8) | bytes[i];
    }
    // Clear the sign bit: X.509 serials must be positive.
    serial &= 0x7FFFFFFFFFFFFFFFLL;
    if (ASN1_INTEGER_set_int64(X509_get_serialNumber(cert), serial) != 1)
    {
        return fail(error, "cannot set the certificate serial: " + openssl_error());
    }
    return true;
}

bool add_extension(X509* cert, int nid, const char* value)
{
    X509V3_CTX ctx;
    X509V3_set_ctx_nodb(&ctx);
    X509V3_set_ctx(&ctx, cert, cert, nullptr, nullptr, 0);
    X509_EXTENSION* ext = X509V3_EXT_conf_nid(nullptr, &ctx, nid, value);
    if (ext == nullptr)
    {
        return false;
    }
    const int rc = X509_add_ext(cert, ext, -1);
    X509_EXTENSION_free(ext);
    return rc == 1;
}

X509* self_sign(EVP_PKEY* key, std::string* error)
{
    X509* cert = X509_new();
    if (cert == nullptr)
    {
        fail(error, "cannot allocate a certificate: " + openssl_error());
        return nullptr;
    }

    // X509_set_version takes the zero-based version, so 2 means X.509 v3 -
    // required for the extensions below to be honoured.
    if (X509_set_version(cert, 2) != 1 || !set_random_serial(cert, error))
    {
        X509_free(cert);
        return nullptr;
    }

    if (X509_gmtime_adj(X509_getm_notBefore(cert), -CERT_BACKDATE_SECONDS) == nullptr ||
        X509_gmtime_adj(X509_getm_notAfter(cert), CERT_VALIDITY_SECONDS) == nullptr)
    {
        X509_free(cert);
        fail(error, "cannot set the certificate validity: " + openssl_error());
        return nullptr;
    }

    // The subject is descriptive only: clients pin the public key and never
    // match a hostname against this name.
    X509_NAME* name = X509_get_subject_name(cert);
    const bool named = X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC,
                                                  reinterpret_cast<const unsigned char*>("NVIDIA"), -1, -1, 0) == 1 &&
                       X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC,
                                                  reinterpret_cast<const unsigned char*>("MST Server"), -1, -1, 0) == 1;
    if (!named || X509_set_issuer_name(cert, name) != 1 || X509_set_pubkey(cert, key) != 1)
    {
        X509_free(cert);
        fail(error, "cannot fill in the certificate: " + openssl_error());
        return nullptr;
    }

    if (!add_extension(cert, NID_basic_constraints, "critical,CA:FALSE") ||
        !add_extension(cert, NID_key_usage, "critical,digitalSignature,keyEncipherment") ||
        !add_extension(cert, NID_ext_key_usage, "serverAuth"))
    {
        X509_free(cert);
        fail(error, "cannot add the certificate extensions: " + openssl_error());
        return nullptr;
    }

    if (X509_sign(cert, key, EVP_sha256()) == 0)
    {
        X509_free(cert);
        fail(error, "cannot sign the certificate: " + openssl_error());
        return nullptr;
    }
    return cert;
}

bool write_key(const std::string& path, EVP_PKEY* key, std::string* error)
{
    FILE* f = open_private_file(path);
    if (f == nullptr)
    {
        return fail(error, "cannot create " + path + ": " + std::strerror(errno));
    }
    const int rc = PEM_write_PrivateKey(f, key, nullptr, nullptr, 0, nullptr, nullptr);
    fclose(f);
    if (rc != 1)
    {
        std::remove(path.c_str());
        return fail(error, "cannot write " + path + ": " + openssl_error());
    }
    return true;
}

bool write_cert(const std::string& path, X509* cert, std::string* error)
{
    FILE* f = open_private_file(path);
    if (f == nullptr)
    {
        return fail(error, "cannot create " + path + ": " + std::strerror(errno));
    }
    const int rc = PEM_write_X509(f, cert);
    fclose(f);
    if (rc != 1)
    {
        std::remove(path.c_str());
        return fail(error, "cannot write " + path + ": " + openssl_error());
    }
    return true;
}

} // namespace

bool ensure_identity(const std::string& dir, Identity* out, std::string* error)
{
    if (out == nullptr)
    {
        return fail(error, "no output identity");
    }
    // Owner-only: the key and certificate written below must be unreachable for
    // every other account. create_directories() cannot set the mode itself, so
    // the directory is briefly wider than that - both files are opened with
    // O_NOFOLLOW, so a symlink planted in that window is refused.
    //
    // A permissions() failure is not fatal: Windows has no POSIX mode to apply,
    // and refusing to start there would be worse than the weaker directory.
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (!std::filesystem::is_directory(dir))
    {
        return fail(error, "cannot create " + dir + ": " + ec.message());
    }
    std::error_code perm_ec;
    std::filesystem::permissions(dir, std::filesystem::perms::owner_all, std::filesystem::perm_options::replace,
                                 perm_ec);

    const std::filesystem::path base(dir);
    const std::string key_path = (base / "server.key").string();
    const std::string cert_path = (base / "server.crt").string();

    EVP_PKEY* key = read_key(key_path);
    if (key == nullptr)
    {
        key = generate_key(error);
        if (key == nullptr)
        {
            return false;
        }
        if (!write_key(key_path, key, error))
        {
            EVP_PKEY_free(key);
            return false;
        }
    }

    // Re-issue only the certificate when it is missing or belongs to another
    // key: the key pair is the identity, so keeping it keeps every client's pin
    // valid.
    X509* cert = read_cert(cert_path);
    if (cert != nullptr && X509_check_private_key(cert, key) != 1)
    {
        X509_free(cert);
        cert = nullptr;
    }
    if (cert == nullptr)
    {
        cert = self_sign(key, error);
        if (cert == nullptr)
        {
            EVP_PKEY_free(key);
            return false;
        }
        if (!write_cert(cert_path, cert, error))
        {
            X509_free(cert);
            EVP_PKEY_free(key);
            return false;
        }
    }

    out->key_path = key_path;
    out->cert_path = cert_path;
    out->fingerprint = public_key_fingerprint(cert);

    X509_free(cert);
    EVP_PKEY_free(key);

    if (out->fingerprint.empty())
    {
        return fail(error, "cannot compute the server key fingerprint: " + openssl_error());
    }
    return true;
}

} // namespace tls
} // namespace mstserver
