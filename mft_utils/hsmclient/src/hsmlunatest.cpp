/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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

#ifndef __WIN__

#include "hsmlunaclient.h"
#include "hex64.h"
using namespace std;
#define BURN_TEST 0
#define SIGN_TEST 0
#define PEM_TEST 0
/*
    FUNCTION: int HsmTest(int argc, char* argv[])
    test function to check HSM features
*/

int HsmTest(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    HSMLunaClient m_HSMLunaClient;
    if (m_HSMLunaClient.Init() == CK_FALSE) {
        cout << "Initialization  error" << endl;
        return -1;
    }
#if PEM_TEST
    if (argc == 2) {
        vector<unsigned char> outputBuffer;
        Hex64Manipulations hex64;
        hex64.ParsePemFile(argv[1], outputBuffer);
    }
#endif

#if BURN_TEST
    string pPrivateKeyLabel = "CMU Unwrapped RSA Private Key", pbPublicKeyLabel = "RSA Public Key 18_06";
    m_HSMLunaClient.BurnPrivateKey(pPrivateKeyLabel, pbPublicKeyLabel);
#endif
#if SIGN_TEST
    vector<CK_BYTE> data(64,0);
    for (int i = 0; i < 64; i++) {
        data[i] = i + 1;
    }

    m_HSMLunaClient.RSA_CreateSignature(data, pPrivateKeyLabel, pbPublicKeyLabel);
#endif
    m_HSMLunaClient.CleanUp();
    return 0;
}
#endif
