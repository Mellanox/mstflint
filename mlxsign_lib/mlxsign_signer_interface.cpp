/*
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

#ifndef NO_OPEN_SSL

#include "mlxsign_signer_interface.h"

using namespace MlxSign;

MlxSignRSAViaOpenssl::MlxSignRSAViaOpenssl(string privPemFileStr): _privPemFileStr(privPemFileStr), _shaType(MlxSign::SHA512)
{}

ErrorCode MlxSignRSAViaOpenssl::Init()
{
    int keyLength = 0;
    int rc = _rsa.setPrivKeyFromFile(_privPemFileStr);
    if (rc) {
        printf("-E- Failed to set private key from file (rc = 0x%x)\n", rc);
        return MLX_SIGN_ERROR;
    }

    keyLength = _rsa.getPrivKeyLength();
    if (keyLength == 0x100) {
        _shaType = MlxSign::SHA256;
    } else if (keyLength == 0x200) {
        _shaType = MlxSign::SHA512;
    } else {
        printf("Unexpected length of key(%d bytes)", keyLength);
        return MLX_SIGN_ERROR;
    }

    return MLX_SIGN_SUCCESS;
}

ErrorCode MlxSignRSAViaOpenssl::Sign(const vector<u_int8_t>& data, vector<u_int8_t>& signature)
{
    vector<u_int8_t> sha;
    int rc;

    if (_shaType == MlxSign::SHA256) {
        MlxSignSHA256 mlxSignSHA;
        mlxSignSHA << data;
        mlxSignSHA.getDigest(sha);
    } else {
        MlxSignSHA512 mlxSignSHA;
        mlxSignSHA << data;
        mlxSignSHA.getDigest(sha);
    }

    rc = _rsa.sign(_shaType, sha, signature);
    if (rc) {
        printf("-E- Failed to encrypt the SHA (rc = 0x%x)\n", rc);
        return MLX_SIGN_ERROR;
    }

    return MLX_SIGN_SUCCESS;    
}

MlxSignRSAViaHSM::MlxSignRSAViaHSM(string opensslEngine, string opensslKeyID): 
_engineSigner(opensslEngine, opensslKeyID),
_opensslEngine(opensslEngine)
{}

ErrorCode MlxSignRSAViaHSM::Init()
{
    int rc = _engineSigner.init();
    if (rc) {
        printf("-E- Failed to initialize %s engine (rc = 0x%x)\n", _opensslEngine.c_str(), rc);
        return MLX_SIGN_ERROR;
    }
    int keySize = _engineSigner.getPrivateKeySize();
    if( keySize != KEY_SIZE_512 ) {
        printf("-E- The HSM key has to be 4096 bit!\n");
        return MLX_SIGN_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

ErrorCode MlxSignRSAViaHSM::Sign(const vector<u_int8_t>& data, vector<u_int8_t>& signature)
{
    int rc = _engineSigner.sign(data, signature);
    if (rc) {
        printf("-E- Failed to create secured FW signature (rc = 0x%x)", rc);
        return MLX_SIGN_ERROR;
    }
    return MLX_SIGN_SUCCESS;
}

#endif //ENABLE_OPENSSL