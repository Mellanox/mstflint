/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2020, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
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
