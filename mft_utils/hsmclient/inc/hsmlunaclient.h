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

#ifdef OS_WIN32
#include <windows.h>
#else
#ifdef OS_HPUX
#include <dl.h>
#else
#include <dlfcn.h>
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <compatibility.h>
#include "cryptoki_v2.h"

#define PLAIN_SZ 512
#define BIG_REQUEST 1048576
#define AES_BLOCK_SIZE 2048
#define MAX_NUM_OF_HANDLES 100
#define DIM(a)                   (sizeof(a)/sizeof(a[0]))
//#define PRIVATE_DATA_SIZE 2350
#define MODULUS_SIZE 512
typedef struct
{
    CK_INFO info;
    char reserved[100]; // This is in case the library that we are
}
protectedInfo_T;



class HSMLunaClient
{
    private:

    #ifdef OS_WIN32
        HINSTANCE                       LibHandle;
    #else
    #ifdef OS_HPUX
        shl_t                           LibHandle;
    #else
        void*                           LibHandle;
    #endif
    #endif

    CK_FUNCTION_LIST*               P11Functions;
    CK_SFNT_CA_FUNCTION_LIST*       SfntFunctions;
    CK_SESSION_HANDLE m_hSession;
    CK_OBJECT_HANDLE                hSymKey;
    CK_BYTE                         PlainText[PLAIN_SZ];
    CK_SLOT_ID m_ckSlot;
    CK_BYTE bPassword[64];
    CK_BBOOL GetLibrary(std::string libPath = std::string());
    CK_BBOOL LoadP11Functions(std::string libPath = std::string());
    CK_BBOOL LoadSfntExtensionFunctions();
    CK_RV Generate3DESKey();
    static unsigned char Modulus[MODULUS_SIZE];
    static unsigned char* _PrivateKeyData;
    unsigned int PrivateKeyDataSize;
    unsigned int ModulusSize;
    const std::string pLibraryPath;
    const std::string pLibraryName;
public:
    HSMLunaClient() : LibHandle(NULL), P11Functions(NULL), SfntFunctions(NULL), hSymKey(0), m_ckSlot(0xffff),
        pLibraryPath("/usr/safenet/lunaclient/lib"), pLibraryName("libcklog2.so")
    {
        memset(PlainText, 65, sizeof(PlainText));
        strcpy((char*)bPassword, "edwardg");
        //PrivateKeyDataSize = PRIVATE_DATA_SIZE;
        ModulusSize = MODULUS_SIZE;
    }
    CK_BBOOL Init(std::string password = std::string(), std::string libPath = std::string());
    CK_RV TestAESEncryption();
    CK_RV AES_DecryptData();
    CK_RV AES_EncryptData();
    CK_RV BurnPrivateKey(std::string privateKeyLabel, std::string publicKeyLabel, std::vector<unsigned char> PrivateKeyData);
    CK_RV FindFirstSlot(CK_SLOT_ID& pckSlot);
    void CleanUp();
    CK_RV RSA_EncryptDataTest(std::string privateKeyLabel, std::string publicKeyLebel);
    CK_RV RSA_CreateSignature(std::vector <CK_BYTE> data, std::string privateKeyLabel, 
        std::string publicKeyLabel, std::vector<u_int8_t>& signature);
    CK_RV CreatePublicKey(std::string publicKeyLabel, unsigned char* PublicModulus, unsigned int PublicModulusSize);
    CK_RV CheckExistingLabel(std::string label, CK_ULONG& numOfLabels);
};
