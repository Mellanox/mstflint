/*
 * Copyright (C) Jan 2021 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#if !defined(NO_OPEN_SSL) && !defined(NO_DYNAMIC_ENGINE)
#include "mlxsign_openssl_engine.h"
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/hmac.h>
#include <openssl/engine.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>
#include <openssl/crypto.h>

using namespace MlxSign;

string to_lowercase_copy(string str)
{ // temporary instead of mft_utils due to linkage issues
    for (string::size_type i = 0; i < str.length(); ++i)
    {
        str[i] = std::tolower(str[i]);
    }
    return str;
}

OpensslEngineException::OpensslEngineException(const string &exceptionMsg, ErrorCode errorCode) : msg(exceptionMsg), errorCode(errorCode) {}
OpensslEngineException::OpensslEngineException(const char *exceptionMsg, ErrorCode errorCode) : msg(exceptionMsg), errorCode(errorCode) {}
const string OpensslEngineException::getErrorString() const throw() { return msg; }
const char *OpensslEngineException::what() const throw() { return msg.c_str(); }
ErrorCode OpensslEngineException::getErrorCode() { return errorCode; }

OpensslEngineSigner::OpensslEngineSigner(const string &engineName, const string &keyIdentifier) : mdCtx(NULL), key(NULL), engineName(engineName), keyIdentifier(keyIdentifier)
{
    SSL_library_init();
    SSL_load_error_strings();
    ENGINE_load_builtin_engines();
    ENGINE_load_dynamic();
    ENGINE_register_all_complete();
    this->engineName = to_lowercase_copy(engineName);
}

OpensslEngineSigner::~OpensslEngineSigner()
{
    if (mdCtx != NULL)
    {
        EVP_MD_CTX_destroy(mdCtx);
    }
    if (key != NULL)
    {
        EVP_PKEY_free(key);
    }
    if (engine != NULL)
    {
        ENGINE_finish(engine);
        ENGINE_free(engine);
    }
    CONF_modules_unload(1);
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    ENGINE_cleanup();
    EVP_cleanup();
    ERR_free_strings();
#endif
    CRYPTO_cleanup_all_ex_data();
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
    OPENSSL_thread_stop();
    OPENSSL_cleanup();
#endif
}

string OpensslEngineSigner::getOpenSSLError()
{
    BIO *bio = BIO_new(BIO_s_mem());
    ERR_print_errors(bio);
    char *buf = NULL;
    size_t len = BIO_get_mem_data(bio, &buf);
    string errorString(buf, len);
    BIO_free(bio);

    return errorString;
}

void OpensslEngineSigner::initOpenSSLEngine()
{
    engine = ENGINE_by_id(engineName.c_str());
    if (engine == NULL)
    {
        throw OpensslEngineException("Invalid engine: " + engineName, MlxSign::MLX_SIGN_RSA_KEY_INIT_ENGINE_OPENSSL_ERROR);
    }
    if (!ENGINE_init(engine))
    {
        throw OpensslEngineException("Failed to init engine: " + engineName, MlxSign::MLX_SIGN_RSA_KEY_INIT_ENGINE_OPENSSL_ERROR);
    }
    if (!ENGINE_set_default(engine, ENGINE_METHOD_ALL))
    {
        throw OpensslEngineException("Failed to use engine: " + engineName, MlxSign::MLX_SIGN_RSA_KEY_INIT_ENGINE_OPENSSL_ERROR);
    }
}

void OpensslEngineSigner::loadPrivateKey()
{
    key = ENGINE_load_private_key(engine, keyIdentifier.c_str(), NULL, NULL);
    if (!key)
    {
        throw OpensslEngineException("Failed to load key from engine with key identifier:" + keyIdentifier, MlxSign::MLX_SIGN_RSA_KEY_ILLEGAL_OPENSSL_URI);
    }
    privateKeySize = EVP_PKEY_size(key);
}

int OpensslEngineSigner::getPrivateKeySize()
{
    return privateKeySize;
}

void OpensslEngineSigner::createContext()
{
    mdCtx = EVP_MD_CTX_create();
    if (!mdCtx)
    {
        throw OpensslEngineException("Failed to create conxtext:" + getOpenSSLError(), MLX_SIGN_RSA_KEY_DIGEST_INIT_OPENSSL_ERROR);
    }
}

void OpensslEngineSigner::digest(const vector<u_int8_t> &msg, vector<u_int8_t> &signed_msg)
{

    int rc = EVP_DigestSignInit(mdCtx, NULL, EVP_sha512(), NULL, (EVP_PKEY *)key);
    if (rc != 1)
    {
        throw OpensslEngineException("Failed to init digest:" + getOpenSSLError(), MLX_SIGN_RSA_KEY_DIGEST_INIT_OPENSSL_ERROR);
    }
    /* Call update with the message */
    rc = EVP_DigestSignUpdate(mdCtx, msg.data(), msg.size());
    if (rc != 1)
    {
        throw OpensslEngineException("EVP_DigestSignUpdate failed: " + getOpenSSLError(), MlxSign::MLX_SIGN_RSA_KEY_DIGEST_UPDATE_OPENSSL_ERROR);
    }
    size_t slen = 0;
    /* Finalise the DigestSign operation */
    /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the
        * signature. Length is returned in slen */
    rc = EVP_DigestSignFinal(mdCtx, NULL, &slen);
    if (rc != 1)
    {
        throw OpensslEngineException("Digest failed: " + getOpenSSLError(), MlxSign::MLX_SIGN_RSA_KEY_DIGEST_FINAL_OPENSSL_ERROR);
    }
    /* Allocate memory for the signature based on size in slen */
    unsigned char *sig;
    if (!(sig = (unsigned char *)OPENSSL_malloc(sizeof(unsigned char) * (slen))))
    {
        throw OpensslEngineException("Digest failed: " + getOpenSSLError(), MlxSign::MLX_SIGN_RSA_KEY_MEMORY_ALLOC_OPENSSL_ERROR);
    }
    signed_msg.resize(slen);
    /* Obtain the signature */
    rc = EVP_DigestSignFinal(mdCtx, sig, &slen);
    if (rc != 1)
    {
        OPENSSL_free(sig);
        throw OpensslEngineException("Digest failed: " + getOpenSSLError(), MlxSign::MLX_SIGN_RSA_KEY_DIGEST_FINAL_OPENSSL_ERROR);
    }
    for (unsigned int i = 0; i < slen; i++)
    {
        signed_msg[i] = sig[i];
    }
    OPENSSL_free(sig);
}

ErrorCode OpensslEngineSigner::init()
{
    MlxSign::ErrorCode errorCode = MlxSign::MLX_SIGN_SUCCESS;
    try
    {
        initOpenSSLEngine();
        loadPrivateKey();
        createContext();
    }
    catch (OpensslEngineException &ex)
    {
        cout << ex.getErrorString() << endl;
        errorCode = ex.getErrorCode();
    }
    return errorCode;
}

ErrorCode OpensslEngineSigner::sign(const vector<u_int8_t> &msg, vector<u_int8_t> &signed_msg)
{
    MlxSign::ErrorCode errorCode = MlxSign::MLX_SIGN_SUCCESS;
    try
    {
        digest(msg, signed_msg);
    }
    catch (OpensslEngineException &ex)
    {
        cout << ex.getErrorString() << endl;
        errorCode = ex.getErrorCode();
    }
    return errorCode;
}

#endif //ENABLE_OPENSSL
