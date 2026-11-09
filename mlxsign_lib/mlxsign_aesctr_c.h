
#ifndef MLXSIGN_AESCTR_C_H_
#define MLXSIGN_AESCTR_C_H_

#include <compatibility.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define AES_CTR_KEY_SIZE 32
#define AES_CTR_IV_SIZE 16

#define MLXSIGN_AESCTR_ERR_INVALID_ARG (-1)
#define MLXSIGN_AESCTR_ERR_BUFFER_SMALL (-2)

    typedef struct mlxsign_aesctr_ctx mlxsign_aesctr_ctx;

    mlxsign_aesctr_ctx*
      mlxsign_aesctr_create(const u_int8_t* key, u_int32_t key_len, const u_int8_t* iv, u_int32_t iv_len);
    void mlxsign_aesctr_destroy(mlxsign_aesctr_ctx* ctx);

    /*
     * mlxsign_aesctr_encrypt - Encrypt plaintext using AES-CTR.
     *
     * Returns:
     *   > 0  : success — number of bytes written to out_ciphertext
     *   -1   : invalid argument (null pointer) or crypto failure
     *   -2   : out_ciphertext buffer too small
     */
    int mlxsign_aesctr_encrypt(mlxsign_aesctr_ctx* ctx,
                               const u_int8_t* plaintext,
                               u_int32_t plaintext_len,
                               u_int8_t* out_ciphertext,
                               u_int32_t* out_ciphertext_len);

    /*
     * mlxsign_aesctr_decrypt - Decrypt ciphertext using AES-CTR.
     *
     * Returns:
     *   > 0  : success — number of bytes written to out_plaintext
     *   -1   : invalid argument (null pointer) or crypto failure
     *   -2   : out_plaintext buffer too small
     */
    int mlxsign_aesctr_decrypt(mlxsign_aesctr_ctx* ctx,
                               const u_int8_t* ciphertext,
                               u_int32_t ciphertext_len,
                               u_int8_t* out_plaintext,
                               u_int32_t* out_plaintext_len);

#ifdef __cplusplus
}
#endif

#endif /* MLXSIGN_AESCTR_C_H_ */