/*
 * C shim implementation for MlxSignAESCTRViaOpenSSL to be used from C code.
 */

#include "mlxsign_aesctr_c.h"
#include "mlxsign_aesctr_via_openssl.h"

#include <vector>

using namespace std;
using namespace MlxSign;

struct mlxsign_aesctr_ctx
{
    MlxSignAESCTRViaOpenSSL* impl;
};

mlxsign_aesctr_ctx* mlxsign_aesctr_create(const u_int8_t* key, u_int32_t key_len, const u_int8_t* iv, u_int32_t iv_len)
{
    if (key == nullptr || iv == nullptr)
    {
        return nullptr;
    }
    if (key_len != AES_CTR_KEY_SIZE || iv_len != AES_CTR_IV_SIZE)
    {
        return nullptr;
    }
    vector<u_int8_t> key_vec(key, key + key_len);
    vector<u_int8_t> iv_vec(iv, iv + iv_len);
    MlxSignAESCTRViaOpenSSL* impl = new (std::nothrow) MlxSignAESCTRViaOpenSSL(key_vec, iv_vec);
    if (!impl)
    {
        return nullptr;
    }
    if (impl->Init() != ErrorCode::MLX_SIGN_SUCCESS)
    {
        delete impl;
        return nullptr;
    }
    mlxsign_aesctr_ctx* ctx = new (std::nothrow) mlxsign_aesctr_ctx();
    if (!ctx)
    {
        delete impl;
        return nullptr;
    }
    ctx->impl = impl;
    return ctx;
}

void mlxsign_aesctr_destroy(mlxsign_aesctr_ctx* ctx)
{
    if (!ctx)
    {
        return;
    }
    delete ctx->impl;
    ctx->impl = nullptr;
    delete ctx;
}

int mlxsign_aesctr_decrypt(mlxsign_aesctr_ctx* ctx,
                           const u_int8_t* ciphertext,
                           u_int32_t ciphertext_len,
                           u_int8_t* out_plaintext,
                           u_int32_t* out_plaintext_len)
{
    if (!ctx || !ciphertext || !out_plaintext || !out_plaintext_len)
    {
        return MLXSIGN_AESCTR_ERR_INVALID_ARG;
    }

    vector<u_int8_t> ct_vec(ciphertext, ciphertext + ciphertext_len);
    vector<u_int8_t> msg_vec;

    int ret;
    try
    {
        ret = ctx->impl->Decrypt(ct_vec, msg_vec);
    }
    catch (const std::exception&)
    {
        return MLXSIGN_AESCTR_ERR_INVALID_ARG;
    }

    if (msg_vec.size() > *out_plaintext_len)
    {
        return MLXSIGN_AESCTR_ERR_BUFFER_SMALL;
    }
    std::copy(msg_vec.begin(), msg_vec.end(), out_plaintext);
    *out_plaintext_len = static_cast<u_int32_t>(msg_vec.size());
    return ret;
}

int mlxsign_aesctr_encrypt(mlxsign_aesctr_ctx* ctx,
                           const u_int8_t* plaintext,
                           u_int32_t plaintext_len,
                           u_int8_t* out_ciphertext,
                           u_int32_t* out_ciphertext_len)
{
    if (!ctx || !plaintext || !out_ciphertext || !out_ciphertext_len)
    {
        return MLXSIGN_AESCTR_ERR_INVALID_ARG;
    }

    vector<u_int8_t> msg_vec(plaintext, plaintext + plaintext_len);
    vector<u_int8_t> enc_vec;

    int enc_len;
    try
    {
        enc_len = ctx->impl->Encrypt(msg_vec, enc_vec);
    }
    catch (const std::exception&)
    {
        return MLXSIGN_AESCTR_ERR_INVALID_ARG;
    }

    if (enc_vec.size() > *out_ciphertext_len)
    {
        return MLXSIGN_AESCTR_ERR_BUFFER_SMALL;
    }

    std::copy(enc_vec.begin(), enc_vec.end(), out_ciphertext);
    *out_ciphertext_len = static_cast<u_int32_t>(enc_vec.size());
    return enc_len;
}
