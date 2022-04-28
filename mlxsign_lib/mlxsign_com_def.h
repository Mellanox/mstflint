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

#ifndef MLXSIGN_ERRORS_H_
#define MLXSIGN_ERRORS_H_

namespace MlxSign
{

enum SHAType
{
    SHA256,
    SHA512
};

enum ErrorCode
{
    MLX_SIGN_SUCCESS = 0,
    MLX_SIGN_SHA_INIT_ERROR,
    MLX_SIGN_SHA_CALCULATION_ERROR,
    MLX_SIGN_ERROR,

    MLX_SIGN_RSA_PEM_FILE_ERROR = 0x100,
    MLX_SIGN_RSA_MESSAGE_TOO_LONG_ERROR,
    MLX_SIGN_RSA_FILE_OPEN_ERROR,
    MLX_SIGN_RSA_FILE_READ_ERROR,
    MLX_SIGN_RSA_INIT_CTX_ERROR,
    MLX_SIGN_RSA_CALCULATION_ERROR,
    MLX_SIGN_RSA_NO_PRIV_KEY_ERROR,
    MLX_SIGN_RSA_NO_PUB_KEY_ERROR,
    MLX_SIGN_RSA_KEY_BIO_ERROR,
    MLX_SIGN_UNSUPPORTED_SHA_TYPE,
    MLX_SIGN_RSA_KEY_ILLEGAL_OPENSSL_URI,
    MLX_SIGN_RSA_KEY_ILLEGAL_OPENSSL_ENGINE,
    MLX_SIGN_RSA_KEY_NOT_FOUND_OPENSSL_ENGINE,
    MLX_SIGN_RSA_KEY_INIT_ENGINE_OPENSSL_ERROR,
    MLX_SIGN_RSA_KEY_DIGEST_INIT_OPENSSL_ERROR,
    MLX_SIGN_RSA_KEY_DIGEST_UPDATE_OPENSSL_ERROR,
    MLX_SIGN_RSA_KEY_DIGEST_FINAL_OPENSSL_ERROR,
    MLX_SIGN_RSA_KEY_MEMORY_ALLOC_OPENSSL_ERROR,
    MLX_SIGN_HMAC_ERROR,

    MLX_SIGN_AWS_INIT_ERROR = 0x200,
    MLX_SIGN_AWS_SIGN_ERROR,
    MLX_SIGN_AWS_GET_KEY_ERROR

};

} // namespace MlxSign

#endif // MLXSIGN_ERRORS_H_