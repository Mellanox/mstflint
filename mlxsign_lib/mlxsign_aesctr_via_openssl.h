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

#ifndef USER_MLXSIGN_LIB_MLXSIGN_AESCTR_VIA_OPENSSL_H_
#define USER_MLXSIGN_LIB_MLXSIGN_AESCTR_VIA_OPENSSL_H_

#include <compatibility.h>
#include "mlxsign_com_def.h"

#include <openssl/evp.h>

#include <string>
#include <vector>

namespace MlxSign
{
using namespace std;

class MlxSignAESCTRViaOpenSSL
{
public:
    MlxSignAESCTRViaOpenSSL(const vector<u_int8_t>& key, const vector<u_int8_t>& iv);
    ~MlxSignAESCTRViaOpenSSL();

    ErrorCode Init();
    int Encrypt(const vector<u_int8_t>& msg, vector<u_int8_t>& encryptedMsg);
    int Decrypt(const vector<u_int8_t>& encryptedMsg, vector<u_int8_t>& msg);

private:
    string getOpenSSLError();

    static const u_int32_t AES_CTR_256_KEY_SIZE_IN_BYTES = 32;
    static const u_int32_t AES_CTR_IV_SIZE_IN_BYTES = 16;

    vector<u_int8_t> _iv;
    vector<u_int8_t> _key;
};

} // namespace MlxSign

#endif /* USER_MLXSIGN_LIB_MLXSIGN_AESCTR_VIA_OPENSSL_H_ */