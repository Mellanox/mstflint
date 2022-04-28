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

#ifndef USER_MLXSIGN_LIB_MLXSIGN_SIGNER_INTERFACE_H_
#define USER_MLXSIGN_LIB_MLXSIGN_SIGNER_INTERFACE_H_


#include "mlxsign_lib.h"

using namespace std;

/*
 * Class Signer: interface for various types of signers
 */

class Signer {
public:
    virtual ~Signer() {};
    virtual MlxSign::ErrorCode Init() = 0;
    virtual MlxSign::ErrorCode Sign(const vector<u_int8_t>& msg, vector<u_int8_t>& signature) = 0;
};

class MlxSignRSAViaOpenssl : public Signer {
public:
    MlxSignRSAViaOpenssl(string privPemFileStr);

    MlxSign::ErrorCode Init();
    MlxSign::ErrorCode Sign(const vector<u_int8_t>& msg, vector<u_int8_t>& signature);

private:
    string _privPemFileStr;
    MlxSign::SHAType _shaType;
    MlxSignRSA _rsa;
};

class MlxSignRSAViaHSM : public Signer {
public:
    MlxSignRSAViaHSM(string opensslEngine, string opensslKeyID);

    MlxSign::ErrorCode Init();
    MlxSign::ErrorCode Sign(const vector<u_int8_t>& msg, vector<u_int8_t>& signature);

private:
    MlxSign::OpensslEngineSigner _engineSigner;
    string _opensslEngine;
};

#endif /* USER_MLXSIGN_LIB_MLXSIGN_SIGNER_INTERFACE_H_ */