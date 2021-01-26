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
#include <iostream>
#include <vector>
using namespace std;

CK_RV HSMLunaClient::RSA_CreateSignature(vector <CK_BYTE> data, string privateKeyLabel, 
    string publicKeyLabel, vector<u_int8_t>& result_signature)
{
    CK_ULONG dataLength = data.size();
    unsigned int labelSize = privateKeyLabel.size() + 1 ;
    CK_BYTE* pLabel = new CK_BYTE[labelSize];
    memset(pLabel, 0, labelSize);
    
    for (unsigned int i = 0; i < privateKeyLabel.size(); i++) {
        pLabel[i] = privateKeyLabel[i];
    }
    CK_ATTRIBUTE RSAFindPriTemplate =
    {
        CKA_LABEL, pLabel, labelSize
    };
    CK_OBJECT_HANDLE priv_key;
    CK_ULONG numHandles = 0;
    CK_OBJECT_HANDLE handles[MAX_NUM_OF_HANDLES] = { 0 };
    CK_RV rv = P11Functions->C_FindObjectsInit(m_hSession, &RSAFindPriTemplate, 1);
    rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
    if (rv != CKR_OK) {
        delete[] pLabel;
        return rv;
    }
    if (numHandles == 0) {
        RSAFindPriTemplate.ulValueLen--;
        rv = P11Functions->C_FindObjectsInit(m_hSession, &RSAFindPriTemplate, 1);
        if (rv != CKR_OK) {
            delete[] pLabel;
            return rv;
        }
        rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
        if (rv != CKR_OK) {
            delete[] pLabel;
            return rv;
        }
    }
    if (numHandles == 0) {
        cout << "Private key not found!" << endl;
        delete[] pLabel;
        return CKR_FUNCTION_FAILED;
    }
    priv_key = handles[0];
    cout << " The private key is " << hex << priv_key << endl;

    CK_MECHANISM mechanism = {
        CKM_SHA512_RSA_PKCS, NULL_PTR, 0
    };
    CK_BYTE* signature = NULL;

    CK_ULONG signatureLength = 0;
    if (rv != CKR_OK) {
        delete[] pLabel;
        return rv;
    }
    
    rv = P11Functions->C_SignInit(m_hSession, &mechanism, priv_key);
    if (rv != CKR_OK) {
        cout << " C_SignInit has failed rv = " << hex << rv << endl;
        delete[] pLabel;
        return rv;
    }
    rv = P11Functions->C_Sign(m_hSession, &data[0], dataLength, NULL, &signatureLength);
    if (rv != CKR_OK) {
        cout << " C_Sign1 has failed rv = " << hex << rv << endl;
        delete[] pLabel;
        return rv;
    }
    signature = new CK_BYTE[signatureLength];
    rv = P11Functions->C_Sign(m_hSession, &data[0], dataLength, signature, &signatureLength);
    if (rv != CKR_OK) {
        cout << " C_Sign2 has failed rv = " << hex << rv << endl;
        delete[] signature;
        delete[] pLabel;
        return rv;
    }
    printf("Signature length is %lu bytes \n", (unsigned long)signatureLength);
    for (unsigned int i = 0; i < signatureLength; i++) {
        printf("0x%02x ", signature[i]);
    }
    cout << endl;
    
    if (publicKeyLabel.empty() == false) {
        unsigned int publicLabelSize = publicKeyLabel.size() + 1;
        CK_BYTE* pPublicLabel = new CK_BYTE[publicLabelSize];
        memset(pPublicLabel, 0, publicLabelSize);
        for (unsigned int i = 0; i < publicKeyLabel.size(); i++) {
            pPublicLabel[i] = publicKeyLabel[i];
        }
        CK_ATTRIBUTE RSAFindPubTemplate =
        {
            CKA_LABEL, pPublicLabel, publicLabelSize
        };
        CK_OBJECT_HANDLE pub_key;
        numHandles = 0;
        rv = P11Functions->C_FindObjectsInit(m_hSession, &RSAFindPubTemplate, 1);
        rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
        if (numHandles == 0) {
            RSAFindPubTemplate.ulValueLen--;
            rv = P11Functions->C_FindObjectsInit(m_hSession, &RSAFindPubTemplate, 1);
            if (rv != CKR_OK) {
                delete[] pPublicLabel;
                return rv;
            }
            rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
            if (rv != CKR_OK) {
                delete[] pPublicLabel;
                return rv;
            }
        }
        if (numHandles == 0) {
            cout << "Public key not found!" << endl;
            return CKR_FUNCTION_FAILED;
        }
        pub_key = handles[0];
        cout << " The public key is " << hex << pub_key << endl;
        /* Verify the known hash using the public key. */
        rv = P11Functions->C_VerifyInit(m_hSession, &mechanism, pub_key);
        if (rv != CKR_OK) {
            cout << "Signature C_VerifyInit failed. Error is " << hex << rv << endl;
            return rv;
        }
        rv = P11Functions->C_Verify(m_hSession, &data[0], dataLength, signature, signatureLength);

        if (rv != CKR_OK) {
            cout << "Signature verifying failed. Error is " << hex << rv << endl;
            return CKR_GENERAL_ERROR;
        }
        cout << " RSA_CreateSignature is verified!" << endl;
    }
    result_signature.resize(signatureLength);
    for (unsigned int i = 0; i < signatureLength; i++) {
        result_signature[i] = signature[i];
    }
    delete[] signature;
    delete[] pLabel;
    return rv;
}


CK_RV HSMLunaClient::RSA_EncryptDataTest(string privateKeyLabel, string publicKeyLebel)
{
    CK_MECHANISM mech2;
    CK_OBJECT_HANDLE publ_key, priv_key;
    /** generate data **/
    CK_BYTE cipher[1024 * 4] = { 0 };
    unsigned int orig_len = 256;
    CK_BYTE original[256] = { 0 };
    CK_ULONG cipher_len, decipher_len;
    for (unsigned int i = 0; i < orig_len; i++)
        original[i] = i % 255;

    /** set mech2 for RSA crypto **/
    mech2.mechanism = CKM_RSA_PKCS;
    mech2.ulParameterLen = 0;
    mech2.pParameter = NULL;

    CK_ATTRIBUTE RSAFindPriTemplate[] =
    {
        {CKA_LABEL, (void*)privateKeyLabel.c_str(), privateKeyLabel.size()}
    };
    CK_ULONG numHandles = 0;
    CK_OBJECT_HANDLE handles[MAX_NUM_OF_HANDLES] = { 0 };
    CK_OBJECT_HANDLE handles1[MAX_NUM_OF_HANDLES] = { 0 };

    CK_RV rv = P11Functions->C_FindObjectsInit(m_hSession, RSAFindPriTemplate, 1);
    rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);

    priv_key = handles[0];
    numHandles = 0;
    CK_ATTRIBUTE RSAFindPubTemplate[] =
    {
        {CKA_LABEL, (void*)publicKeyLebel.c_str(), publicKeyLebel.size()}
    };
    rv = P11Functions->C_FindObjectsInit(m_hSession, RSAFindPubTemplate, 1);
    rv = P11Functions->C_FindObjects(m_hSession, handles1, MAX_NUM_OF_HANDLES, &numHandles);
    publ_key = handles1[0];

    if (rv == CKR_OK)
    {
        /** initialize RSA encryption (with private key) **/
        rv = P11Functions->C_EncryptInit(m_hSession, &mech2, publ_key);
        if (rv != CKR_OK) {
            cout << "C_EncryptInit " << hex << rv << endl;
            //testcase_error("C_EncryptInit rc=%s", p11_get_ckr(rc));
            return rv;
        }
        cipher_len = sizeof(cipher);        // set cipher buffer size
        /** do RSA decryption (with public key) **/
        rv = P11Functions->C_Encrypt(m_hSession,
            original, orig_len, cipher, (CK_ULONG_PTR)&cipher_len);
        if (rv != CKR_OK)
        {
            cout << "C_Encrypt " << hex << rv << endl;
            return rv;
        }
        rv = P11Functions->C_DecryptInit(m_hSession, &mech2, priv_key);
        if (rv != CKR_OK) {
            cout << "C_DecryptInit " << hex << rv << endl;
            return rv;
        }
        // do (private key) decryption
        decipher_len = 0;
        rv = P11Functions->C_Decrypt(m_hSession, cipher, cipher_len, NULL, &decipher_len);
        if (rv != CKR_OK) {
            cout << "C_Decrypt " << hex << rv << endl;
            cout << "Error in decryption process 1 !" << endl;
            return rv;
        }
        CK_BYTE *decipher = new CK_BYTE[decipher_len];
        rv = P11Functions->C_Decrypt(m_hSession, cipher, cipher_len, decipher, &decipher_len);
        if (rv != CKR_OK) {
            cout << "Error in decryption process 2 !" << hex << rv << endl;
            return rv;
        }
        rv = P11Functions->C_DestroyObject(m_hSession, publ_key);
        if (rv != CKR_OK) {
            cout << "C_DestroyObject public " << hex << rv << endl;
            return rv;
        }

        rv = P11Functions->C_DestroyObject(m_hSession, priv_key);
        if (rv != CKR_OK) {
            cout << "C_DestroyObject private " << hex << rv << endl;
            return rv;
        }
        if (orig_len == decipher_len) {
            unsigned int i = 0;
            for (i = 0; i < orig_len; i++)
            {
                if (original[i] != decipher[i]) {
                    cout << "Error in decrypted data - data mismath !" << endl;
                    delete[] decipher;
                    return -1;
                }
            }
            cout << "Success in encrypt/decrypt !" << endl;
            delete[] decipher;
            return 0;
        }
        cout << "Error in decryption process - size mismatch !" << endl;
        delete[] decipher;
        return -1;
        //compare original and decipher
    }
    return rv;
}
#endif
