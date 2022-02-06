/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef USER_MLXSIGN_LIB_MLXSIGN_LIB_H_
#define USER_MLXSIGN_LIB_MLXSIGN_LIB_H_

#include <string>
#include <cstring>
#include <vector>
#include <compatibility.h>
#include "mlxsign_com_def.h"
#include "mlxsign_openssl_engine.h"

using namespace std;


/*
 * Class MlxSignSHA: used for calculating SHA digest on a data buffer.
 * Usage:
 *     use operator <<  to fill the class's internal buffer.
 *     call getDigest() method to get the digest in either string or raw buffer format.
 * Example:
 *      string digest;
 *      vector<u_int8_t> dataVec;
 *      // fill dataVec with data.....
 *      MlxSignSHA sha256;
 *      sha256 << dataVec;
 *      sha256.getDigest(result);
 *      cout << result;
 */
class MlxSignSHA {
public:
    MlxSignSHA(u_int32_t);
    virtual ~MlxSignSHA() {};
    friend MlxSignSHA& operator<<(MlxSignSHA& lhs, u_int8_t data);
    friend MlxSignSHA& operator<<(MlxSignSHA& lhs, const std::vector<u_int8_t>& buff);

    int getDigest(std::string& digest);
    virtual int getDigest(std::vector<u_int8_t>& digest) = 0;
    void reset();

protected:
    u_int32_t _digestLength;
    std::vector<u_int8_t> _buff;
};

class MlxSignSHA256 : public MlxSignSHA {
public:
    MlxSignSHA256();
    int getDigest(std::vector<u_int8_t>& digest);
};

class MlxSignSHA512 : public MlxSignSHA {
public:
    MlxSignSHA512();
    int getDigest(std::vector<u_int8_t>& digest);
};

/*
 * Class MlxSignRSA: used for encrypting/decrypting messages using RSA encryption algorithm
 * Usage:
 *     set private and/or public keys
 *     encrypt/decrypt your message.
 *
 *     Note:
 *     -    encryption is performed with the provided private key.
 *     -    decryption is performed with the provided public key.
 *     -    user should make sure that encrypted and decrypted messages dont exceed the relevant Max message size
 * Example:
 *      MlxSignRSA rsa;
 *      rsa.setPrivKeyFromFile(filePathPriv);
 *      rsa.encrypt(msg, encryptedMsg);
 *      cout << rsa.str(encryptedMsg);
 *      rsa.setPubKeyFromFile(filePathPub);
 *      rsa.decrypt(encryptedMsg, originalMsg);
 */
class MlxSignRSA {
public:
    ~MlxSignRSA();
    MlxSignRSA();
    int setPrivKeyFromFile(const std::string& pemKeyFilePath);
    int setPrivKey(const std::string& pemKey);
    int getPrivKeyLength() const;

    int setPubKeyFromFile(const std::string& pemKeyFilePath);
    int setPubKey(const std::string& pemKey);

    int getEncryptMaxMsgSize();
    int getDecryptMaxMsgSize();

    int encrypt(const std::vector<u_int8_t>& msg, std::vector<u_int8_t>& encryptedMsg);     // encrypt with private
    int decrypt(const std::vector<u_int8_t>& encryptedMsg, std::vector<u_int8_t>& originalMsg);    // decrypt with public (used for testing for now)

    int sign(MlxSign::SHAType shaType, const std::vector<u_int8_t>& msg, std::vector<u_int8_t>& encryptedMsg);
    int verify(MlxSign::SHAType shaType, const std::vector<u_int8_t>& sha256Dgst, const std::vector<u_int8_t>& sig, bool& result);

    std::string str(const std::vector<u_int8_t>& msg);
private:
    int createRSAFromPEMFileName(const std::string& fname, bool isPrivateKey);
    int createRSAFromPEMKeyString(const std::string& pemKey,  bool isPrivateKey);
    void *_privCtx;
    void *_pubCtx;
};


class MlxSignHMAC {
public:
    MlxSignHMAC();
    int setKey(const std::vector<u_int8_t>& key);
    //int update(const std::vector<u_int8_t>& buff);
    friend MlxSignHMAC& operator<<(MlxSignHMAC& lhs, const std::vector<u_int8_t>& buff);
    int getDigest(std::vector<u_int8_t>& digest);
    ~MlxSignHMAC();

private:
    void *ctx;
    std::vector<u_int8_t> data;

};

#endif /* USER_MLXSIGN_LIB_MLXSIGN_LIB_H_ */
