/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */

#include "mlxsign_aesctr_via_openssl.h"
#include <openssl/err.h>
#include <stdexcept>

using namespace std;
using namespace MlxSign;

MlxSignAESCTRViaOpenSSL::MlxSignAESCTRViaOpenSSL(const vector<u_int8_t>& key, const vector<u_int8_t>& iv) :
    _iv(iv), _key(key)
{
}

MlxSignAESCTRViaOpenSSL::~MlxSignAESCTRViaOpenSSL() {}

ErrorCode MlxSignAESCTRViaOpenSSL::Init()
{
    if (_key.empty())
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Init must provide key bytes");
    }

    if (_key.size() != AES_CTR_256_KEY_SIZE_IN_BYTES)
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Init invalid key size");
    }

    if (_iv.empty())
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Init must provide IV bytes");
    }

    if (_iv.size() != AES_CTR_IV_SIZE_IN_BYTES)
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Init invalid IV size");
    }

    return ErrorCode::MLX_SIGN_SUCCESS;
}

int MlxSignAESCTRViaOpenSSL::Encrypt(const vector<u_int8_t>& msg, vector<u_int8_t>& encryptedMsg)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Encrypt failed to create context: " + getOpenSSLError());
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, _key.data(), _iv.data()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Encrypt failed to initialize: " + getOpenSSLError());
    }

    encryptedMsg.resize(msg.size());
    int len = 0;
    int total = 0;

    if (EVP_EncryptUpdate(ctx, encryptedMsg.data(), &len, msg.data(), msg.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Encrypt failed to update: " + getOpenSSLError());
    }

    total += len;

    if (EVP_EncryptFinal_ex(ctx, encryptedMsg.data() + total, &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Encrypt failed to finalize: " + getOpenSSLError());
    }

    total += len;
    EVP_CIPHER_CTX_free(ctx);
    return total;
}

int MlxSignAESCTRViaOpenSSL::Decrypt(const vector<u_int8_t>& encryptedMsg, vector<u_int8_t>& msg)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Decrypt failed to create context: " + getOpenSSLError());
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, _key.data(), _iv.data()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Decrypt failed to initialize: " + getOpenSSLError());
    }

    msg.resize(encryptedMsg.size());
    int len = 0;
    int total = 0;

    if (EVP_DecryptUpdate(ctx, msg.data(), &len, encryptedMsg.data(), encryptedMsg.size()) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Decrypt failed to update: " + getOpenSSLError());
    }

    total += len;

    if (EVP_DecryptFinal_ex(ctx, msg.data() + total, &len) != 1)
    {
        EVP_CIPHER_CTX_free(ctx);
        throw runtime_error("MlxSignAESCTRViaOpenSSL::Decrypt failed to finalize: " + getOpenSSLError());
    }

    total += len;
    EVP_CIPHER_CTX_free(ctx);
    return total;
}

string MlxSignAESCTRViaOpenSSL::getOpenSSLError()
{
    char err_buf[256];
    unsigned long err = ERR_get_error();
    ERR_error_string_n(err, err_buf, sizeof(err_buf));
    return string(err_buf);
}