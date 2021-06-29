/*
 * Copyright (C) Jan 2021 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef MLXSIGN_OPENSSL_ENGINE_H_
#define MLXSIGN_OPENSSL_ENGINE_H_

#include "mlxsign_com_def.h"
#include <compatibility.h>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <openssl/ssl.h>

using namespace std;

namespace MlxSign
{

class OpensslEngineException : public exception
{
public:
    OpensslEngineException(const string &exceptionMsg, ErrorCode errorCode);
    OpensslEngineException(const char *exceptionMsg, ErrorCode errorCode);
    virtual const string getErrorString() const throw();
    virtual const char *what() const throw();
    virtual ~OpensslEngineException() throw(){};
    ErrorCode getErrorCode();

private:
    string msg;
    ErrorCode errorCode;
    OpensslEngineException();
};

class OpensslEngineSigner
{
public:
    OpensslEngineSigner(const string &engineName, const string &keyIdentifier);
    virtual ~OpensslEngineSigner();
    ErrorCode init();
    ErrorCode sign(const vector<u_int8_t> &msg, vector<u_int8_t> &signed_msg);

private:
    EVP_MD_CTX *mdCtx;
    EVP_PKEY *key;
    ENGINE *engine;
    string engineName;
    string keyIdentifier;
    string getOpenSSLError();
    void initOpenSSLEngine();
    void loadPrivateKey();
    void createContext();
    void digest(const vector<u_int8_t> &msg, vector<u_int8_t> &signed_msg);
};

} // namespace MlxSign

#endif // MLXSIGN_OPENSSL_ENGINE_H_
