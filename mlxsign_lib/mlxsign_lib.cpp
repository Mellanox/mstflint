/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef NO_OPEN_SSL
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/hmac.h>

#include "mlxsign_lib.h"

#define CHECK_RC(rc, expRc, errCode) do { \
        if ((rc) != (expRc)) { return (errCode);} \
} while (0)


MlxSignSHA::MlxSignSHA(u_int32_t digestLength)
{
    _digestLength = digestLength;
}

int MlxSignSHA::getDigest(std::string& digest)
{
    int rc;
    std::vector<u_int8_t> digestVec;
    char *digestStr = new char[_digestLength * 2 + 1];

    rc = getDigest(digestVec);
    if (rc != MLX_SIGN_SUCCESS) {
        delete[] digestStr;
        return rc;
    }
    // transform to string
    for (u_int64_t i = 0; i < digestVec.size(); i++) {
        snprintf(digestStr + i * 2, 3, "%02x", digestVec[i]);
    }
    digest = digestStr;
    delete[] digestStr;
    return MLX_SIGN_SUCCESS;
}

void MlxSignSHA::reset()
{
    _buff.resize(0);
}

MlxSignSHA& operator<<(MlxSignSHA& lhs, u_int8_t data)
{
    lhs._buff.push_back(data);
    return lhs;
}

MlxSignSHA& operator<<(MlxSignSHA& lhs, const std::vector<u_int8_t>& buff)
{
    for (std::vector<u_int8_t>::const_iterator it = buff.begin(); it != buff.end(); it++) {
        lhs._buff.push_back(*it);
    }
    return lhs;
}

/*
 * MlxSignSHA256
 *
 */

MlxSignSHA256::MlxSignSHA256() : MlxSignSHA(SHA256_DIGEST_LENGTH)
{
}

int MlxSignSHA256::getDigest(std::vector<u_int8_t>& digest)
{
    int rc;
    SHA256_CTX ctx;
    digest.resize(_digestLength);
    memset(&digest[0], 0, digest.size());
    rc = SHA256_Init( &ctx); CHECK_RC(rc, 1, MLX_SIGN_SHA_INIT_ERROR);
    rc = SHA256_Update(&ctx, (void*)(&_buff[0]), _buff.size()); CHECK_RC(rc, 1, MLX_SIGN_SHA_CALCULATION_ERROR);
    rc = SHA256_Final(&digest[0], &ctx); CHECK_RC(rc, 1, MLX_SIGN_SHA_CALCULATION_ERROR);
    return MLX_SIGN_SUCCESS;
}

/*
 * MlxSignSHA512
 *
 */
MlxSignSHA512::MlxSignSHA512() : MlxSignSHA(SHA512_DIGEST_LENGTH)
{
}

int MlxSignSHA512::getDigest(std::vector<u_int8_t>& digest)
{
    int rc;
    SHA512_CTX ctx;
    digest.resize(_digestLength);
    memset(&digest[0], 0, digest.size());
    rc = SHA512_Init( &ctx); CHECK_RC(rc, 1, MLX_SIGN_SHA_INIT_ERROR);
    rc = SHA512_Update(&ctx, (void*)(&_buff[0]), _buff.size()); CHECK_RC(rc, 1, MLX_SIGN_SHA_CALCULATION_ERROR);
    rc = SHA512_Final(&digest[0], &ctx); CHECK_RC(rc, 1, MLX_SIGN_SHA_CALCULATION_ERROR);
    return MLX_SIGN_SUCCESS;
}

MlxSignRSA::~MlxSignRSA()
{
    if (_privCtx) {
        RSA_free((RSA*)_privCtx);
    }

    if (_pubCtx) {
        RSA_free((RSA*)_pubCtx);
    }
}
int MlxSignRSA::setPrivKeyFromFile(const std::string& pemKeyFilePath)
{
    return createRSAFromPEMFileName(pemKeyFilePath, true);
}

int MlxSignRSA::setPrivKey(const std::string& pemKey)
{
    return createRSAFromPEMKeyString(pemKey, true);
}

int MlxSignRSA::getPrivKeyLength() const
{
    if (_privCtx) {
        return RSA_size((RSA*)_privCtx);
    } else {
        return 0x0;
    }
}

int MlxSignRSA::setPubKeyFromFile(const std::string& pemKeyFilePath)
{
    return createRSAFromPEMFileName(pemKeyFilePath, false);
}

int MlxSignRSA::setPubKey(const std::string& pemKey)
{
    return createRSAFromPEMKeyString(pemKey, false);
}

int MlxSignRSA::sign(MlxSign::SHAType shaType, const std::vector<u_int8_t>& msg, std::vector<u_int8_t>& encryptedMsg)
{
    unsigned int maxMsgSize, signLen;
    std::vector<u_int8_t> encryptedMsgTemp;

    if (!_privCtx) {
        return MLX_SIGN_RSA_NO_PRIV_KEY_ERROR;
    }

    // size check
    maxMsgSize = RSA_size((RSA*)_privCtx);
    if (msg.size() > maxMsgSize) {
        return MLX_SIGN_RSA_MESSAGE_TOO_LONG_ERROR;
    }
    // do the job
    encryptedMsgTemp.resize(maxMsgSize, 0);

    int type;

    if (shaType == MlxSign::SHA256) {
        type = NID_sha256;
    } else if (shaType == MlxSign::SHA512) {
        type = NID_sha512;
    } else {
        return MLX_SIGN_UNSUPPORTED_SHA_TYPE;
    }

    if (!RSA_sign(type, msg.data(), msg.size(), encryptedMsgTemp.data(), &signLen, (RSA*)_privCtx)) {
        return MLX_SIGN_RSA_CALCULATION_ERROR;
    }

    encryptedMsg.resize(signLen, 0);
    memcpy(encryptedMsg.data(), encryptedMsgTemp.data(), signLen);

    return MLX_SIGN_SUCCESS;
}

int MlxSignRSA::verify(MlxSign::SHAType shaType, const std::vector<u_int8_t>& digest, const std::vector<u_int8_t>& sig, bool& result)
{

    if (!_pubCtx) {
        return MLX_SIGN_RSA_NO_PUB_KEY_ERROR;
    }

    int type;

    if (shaType == MlxSign::SHA256) {
        type = NID_sha256;
    } else if (shaType == MlxSign::SHA512) {
        type = NID_sha512;
    } else {
        return MLX_SIGN_UNSUPPORTED_SHA_TYPE;
    }

    result = RSA_verify(type, digest.data(), digest.size(), sig.data(), sig.size(), (RSA*)_pubCtx);

    return MLX_SIGN_SUCCESS;
}

int MlxSignRSA::encrypt(const std::vector<u_int8_t>& msg, std::vector<u_int8_t>& encryptedMsg)
{
    int maxMsgSize;

    if (!_privCtx) {
        return MLX_SIGN_RSA_NO_PRIV_KEY_ERROR;
    }
    // size check
    maxMsgSize = RSA_size((RSA*)_privCtx);
    if (static_cast<int>(msg.size()) > maxMsgSize) {
        return MLX_SIGN_RSA_MESSAGE_TOO_LONG_ERROR;
    }
    // do the job
    encryptedMsg.resize(maxMsgSize, 0);
    if (RSA_private_encrypt((int)msg.size(), &msg[0], &encryptedMsg[0], (RSA*)_privCtx, RSA_PKCS1_PADDING ) != maxMsgSize) {
        return MLX_SIGN_RSA_CALCULATION_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

int MlxSignRSA::decrypt(const std::vector<u_int8_t>& encryptedMsg, std::vector<u_int8_t>& originalMsg)
{
    int maxMsgSize;
    int origMsgSize;
    if (!_pubCtx) {
        return MLX_SIGN_RSA_NO_PUB_KEY_ERROR;
    }
    // size check
    maxMsgSize = RSA_size((RSA*)_pubCtx);
    if (static_cast<int>(encryptedMsg.size()) > maxMsgSize) {
        return MLX_SIGN_RSA_MESSAGE_TOO_LONG_ERROR;
    }
    // do the job
    originalMsg.resize(maxMsgSize, 0);
    if ((origMsgSize = RSA_public_decrypt((int)encryptedMsg.size(), &encryptedMsg[0], &originalMsg[0], (RSA*)_pubCtx, RSA_PKCS1_PADDING )) == -1) {
        return MLX_SIGN_RSA_CALCULATION_ERROR;
    }
    originalMsg.resize(origMsgSize);
    return MLX_SIGN_SUCCESS;
}

int MlxSignRSA::getEncryptMaxMsgSize()
{
    if (_privCtx) {
        return RSA_size((RSA*)_privCtx);
    }
    return 0;
}

int MlxSignRSA::getDecryptMaxMsgSize()
{
    if (_pubCtx) {
        return RSA_size((RSA*)_pubCtx);
    }
    return 0;
}

std::string MlxSignRSA::str(const std::vector<u_int8_t>& msg)
{
    char *digestStr = NULL;
    try {
        digestStr = new char[msg.size() * 2 + 1];
        memset(digestStr, 0, sizeof(char) * (msg.size() * 2 + 1));
    }catch (...) {
        return "";
    }

    for (u_int64_t i = 0; i < msg.size(); i++) {
        snprintf(digestStr + i * 2, 3, "%02x", msg[i]);
    }
    std::string result = digestStr;
    delete[] digestStr;
    return result;
}

#define REPLACE_RSA_CTX(ctx, newCtx) \
    do {                                                            \
        if ((newCtx)) {                                         \
            if ((ctx)) {                                            \
                RSA_free((RSA*)(ctx));                 \
            }                                                           \
            (ctx) = (void*)(newCtx);                        \
        }                                                               \
    } while (0)

int MlxSignRSA::createRSAFromPEMFileName(const std::string& fname, bool isPrivateKey)
{
    FILE *fp = fopen(fname.c_str(), "rb");
    RSA *rsa = NULL;
    if (!fp) {
        return MLX_SIGN_RSA_FILE_OPEN_ERROR;
    }
    rsa = RSA_new();
    if (isPrivateKey) {
        rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
        REPLACE_RSA_CTX(_privCtx, rsa);
    } else {
        rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
        REPLACE_RSA_CTX(_pubCtx, rsa);
    }

    fclose(fp);
    if (rsa == NULL) {
        return MLX_SIGN_RSA_INIT_CTX_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

int MlxSignRSA::createRSAFromPEMKeyString(const std::string& pemKey,  bool isPrivateKey)
{
    RSA *rsa = NULL;
    BIO *keybio;
    // TODO: check if this may leak
    keybio = BIO_new_mem_buf((void*)pemKey.c_str(), -1);
    if (keybio == NULL) {
        return MLX_SIGN_RSA_KEY_BIO_ERROR;
    }
    if (isPrivateKey) {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
        REPLACE_RSA_CTX(_privCtx, rsa);
    } else {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
        REPLACE_RSA_CTX(_pubCtx, rsa);
    }
    BIO_free_all(keybio);
    if (rsa == NULL) {
        return MLX_SIGN_RSA_INIT_CTX_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

MlxSignHMAC::MlxSignHMAC()
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    ctx = malloc(sizeof(HMAC_CTX));
    HMAC_CTX_init((HMAC_CTX*)ctx);
#else
    ctx = HMAC_CTX_new();
#endif
}

int MlxSignHMAC::setKey(const std::vector<u_int8_t>& key)
{
    if (HMAC_Init_ex((HMAC_CTX*)ctx, (char*)key.data(), key.size(), EVP_sha512(), NULL) == 0) {
        return MLX_SIGN_HMAC_ERROR;
    }

    return MLX_SIGN_SUCCESS;
}

/*int MlxSignHMAC::update(const std::vector<u_int8_t>& buff)
   {
    if (HMAC_Update(&ctx, (unsigned char*)buff.data(), buff.size()) == 0) {
        return MLX_SIGN_HMAC_ERROR;
    }

    return MLX_SIGN_SUCCESS;
   }*/

MlxSignHMAC& operator<<(MlxSignHMAC& lhs, const std::vector<u_int8_t>& buff)
{
    for (std::vector<u_int8_t>::const_iterator it = buff.begin(); it != buff.end(); it++) {
        lhs.data.push_back(*it);
    }

    return lhs;
}

int MlxSignHMAC::getDigest(std::vector<u_int8_t>& digest)
{
    unsigned int len = 64; //512 bits

    if (HMAC_Update((HMAC_CTX*)ctx, (unsigned char*)data.data(), data.size()) == 0) {
        return MLX_SIGN_HMAC_ERROR;
    }

    digest.resize(len);

    //TODO why len is passed by reference?
    //TODO HMAC_Final must return 1 on success and 0 on failure but that is not happening!
    HMAC_Final((HMAC_CTX*)ctx, digest.data(), &len);

    /*for (int i = 0; i != len; i++)
            printf("%02x", (unsigned int)digest[i]);
       printf("\n");
     */

    return MLX_SIGN_SUCCESS;
}

MlxSignHMAC::~MlxSignHMAC()
{
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    HMAC_CTX_cleanup((HMAC_CTX*)ctx);
    free(ctx);
#else
    HMAC_CTX_free((HMAC_CTX*)ctx);
#endif
}

#endif //ENABLE_OPENSSL
