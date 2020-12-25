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
#include <string>
using namespace std;
static unsigned char PublicExponent[] = { 0x01, 0x00, 0x01 };

CK_RV HSMLunaClient::CreatePublicKey(string publicKeyLabel, unsigned char* PublicModulus, 
    unsigned int PublicModulusSize)
{
    CK_OBJECT_CLASS publicKey = CKO_PUBLIC_KEY;
    CK_KEY_TYPE rsaType = CKK_RSA;
    CK_BBOOL bTrue = 1;
    CK_BBOOL bSign = bTrue, bToken = bTrue, bPrivate = bTrue, bDecrypt = bTrue, bWrap = bTrue;
    //CK_BBOOL bToken = bTrue, bDecrypt = bTrue, bSign = bTrue, bWrap = bTrue;
    CK_OBJECT_HANDLE hPublicRSAKey;
    CK_RV rv = CKR_TOKEN_NOT_PRESENT;
    unsigned int publicLabelSize = publicKeyLabel.size()+1;
    CK_BYTE* pLabelPub = new CK_BYTE[publicLabelSize];
    memset(pLabelPub, 0, publicLabelSize);

    for (unsigned int i = 0; i < publicKeyLabel.size(); i++) {
        pLabelPub[i] = publicKeyLabel[i];
    }
    CK_ATTRIBUTE pPublicRSAKeyTemplate[] =
    {
        {CKA_CLASS, &publicKey, sizeof(publicKey) },
        {CKA_KEY_TYPE, &rsaType, sizeof(rsaType)},
        {CKA_TOKEN, &bToken, sizeof(bToken)},
        {CKA_PRIVATE, &bPrivate,   sizeof(bPrivate)},
        {CKA_ENCRYPT, &bDecrypt,   sizeof(bDecrypt)},
        {CKA_VERIFY, &bSign, sizeof(bSign)},
        {CKA_WRAP, &bWrap, sizeof(bWrap)},
        {CKA_MODULUS, PublicModulus, PublicModulusSize},
        {CKA_PUBLIC_EXPONENT, PublicExponent, sizeof(PublicExponent)},
        {CKA_LABEL, pLabelPub, publicLabelSize}
    };
    unsigned int usTemplateSize = DIM(pPublicRSAKeyTemplate);
    rv = P11Functions->C_CreateObject(m_hSession, pPublicRSAKeyTemplate, usTemplateSize, &hPublicRSAKey);
    if (rv != CKR_OK) {
        cout << "C_Create public Object FAILED...rv = " << hex << rv << endl;
        return -1;
    }
    cout << "Create public key success handle = " << hex << hPublicRSAKey << endl;
    delete[] pLabelPub;
    return CKR_OK;
}

CK_RV HSMLunaClient::CheckExistingLabel(string label, CK_ULONG& numOfLabels)
{
    CK_RV rv = CKR_TOKEN_NOT_PRESENT;
    unsigned int LabelSize = label.size() + 1;
    CK_BYTE* pLabel = new CK_BYTE[LabelSize];
    memset(pLabel, 0, LabelSize);
    for (unsigned int i = 0; i < label.size(); i++) {
        pLabel[i] = label[i];
    }
    CK_ATTRIBUTE Template[] =
    {
        {CKA_LABEL, pLabel, LabelSize}
    };

    CK_ULONG numHandles = 0;
    CK_OBJECT_HANDLE handles[MAX_NUM_OF_HANDLES] = { 0 };
    rv = P11Functions->C_FindObjectsInit(m_hSession, Template, 1);
    if (rv != CKR_OK) {
        delete[] pLabel;
        return rv;
    }
    rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
    if (rv != CKR_OK) {
        delete[] pLabel;
        return rv;
    }
    numOfLabels = numHandles;
    if (numHandles != 0) {
        delete[] pLabel;
        return CKR_GENERAL_ERROR;
    }
    if (numHandles == 0) {
        Template[0].ulValueLen--;
        rv = P11Functions->C_FindObjectsInit(m_hSession, Template, 1);
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
    numOfLabels = numHandles;
    delete[] pLabel;
    if (numHandles != 0) {
        return CKR_GENERAL_ERROR;
    }
    return CKR_OK;
}

CK_RV HSMLunaClient::BurnPrivateKey(string privateKeyLabel, string publicKeyLabel
    , vector<unsigned char> PrivateKeyData)
{
    protectedInfo_T protectedInfo;
    CK_RV rv = CKR_TOKEN_NOT_PRESENT;
    CK_OBJECT_HANDLE hPrivateRSAKey;
    char* pbWrappedKey;
    unsigned long    ulWrappedKeySize;
    CK_OBJECT_CLASS privateKey = CKO_PRIVATE_KEY;
    
    CK_USHORT usOutDataLen = 0;
    char *pPlainData = 0;
    unsigned long ulPlainDataLength;
    char *pEncryptedData = 0;
    unsigned long ulEncryptedDataLength = 0;

    CK_MECHANISM mech;
    
    
    //CK_BYTE pLabel[] = "Super New RSA private Key222";
    CK_KEY_TYPE rsaType = CKK_RSA;
    CK_ULONG usTemplateSize;

    rv = P11Functions->C_GetInfo(&protectedInfo.info);
    if (rv != CKR_OK) {
        cout << "C_GetInfo FAILED..." << endl;
        return -1;
    }
    CK_BBOOL bFalse = 0;
    CK_BBOOL bTrue = 1;
    CK_BBOOL bToken = bTrue;
    CK_BBOOL bPrivate = bTrue;
    CK_BBOOL bEncrypt = bTrue;
    CK_BBOOL bSign = bTrue;
    CK_BBOOL bWrap = bTrue;
    
    CK_BBOOL bSensitive = bTrue;
    unsigned int privateLabelSize = privateKeyLabel.size()+1;
    CK_BYTE* pLabel = new CK_BYTE[privateLabelSize];
    memset(pLabel, 0, privateLabelSize);

    unsigned int publicLabelSize = publicKeyLabel.size()+1;
    CK_BYTE* pLabelPub = new CK_BYTE[publicLabelSize];
    memset(pLabelPub, 0, publicLabelSize);

    for (unsigned int i = 0; i < privateKeyLabel.size(); i++) {
        pLabel[i] = privateKeyLabel[i];
    }
    for (unsigned int i = 0; i < publicKeyLabel.size(); i++) {
        pLabelPub[i] = publicKeyLabel[i];
    }

    

    CK_ATTRIBUTE pPrivateKeyTemplate[] =
    {
        {CKA_CLASS, &privateKey, sizeof(privateKey) },
        {CKA_KEY_TYPE, &rsaType,    sizeof(rsaType)},
        {CKA_TOKEN, &bToken, sizeof(bToken)},
        {CKA_SENSITIVE, &bSensitive, sizeof(bSensitive) },
        {CKA_PRIVATE, &bPrivate, sizeof(bPrivate)},
        {CKA_DECRYPT, &bEncrypt, sizeof(bEncrypt)},
        {CKA_SIGN, &bSign, sizeof(bSign)},
        {CKA_SIGN_RECOVER, &bTrue, sizeof(bTrue)},//here may be remark!
        {CKA_UNWRAP, &bWrap, sizeof(bWrap)},
        {CKA_EXTRACTABLE, &bFalse, sizeof(bFalse)},
        {CKA_LABEL, pLabel, privateLabelSize}
    };

    rv = Generate3DESKey();
    if (rv != CKR_OK) {
        cout << "\n" "Error 0x" << hex << rv;
        cout << " generating the DES3 Key.\n";
        return -11;
    }

    //Encrypt the RSA Key
    unsigned char iv[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
    mech.mechanism = CKM_DES3_CBC;
    mech.pParameter = iv;
    mech.usParameterLen = sizeof(iv);
    unsigned char* _PrivateKeyData  = &PrivateKeyData[0];
    PrivateKeyDataSize = PrivateKeyData.size();
    pPlainData = (char *)(_PrivateKeyData);
    ulPlainDataLength = PrivateKeyDataSize;
    pEncryptedData = new char[ulPlainDataLength + 2048];
    rv = P11Functions->C_EncryptInit(m_hSession, &mech, hSymKey);
    CK_USHORT usInDataLen;
    usOutDataLen = (CK_USHORT)(ulPlainDataLength + 2048);
    CK_ULONG ulBytesRemaining = ulPlainDataLength;
    char* pPlainTextPointer = pPlainData;
    char* pEncryptedDataPointer = pEncryptedData;
    while (ulBytesRemaining > 0) {
        if (ulBytesRemaining > 0xfff0) {
            usInDataLen = 0xfff0;
            ulBytesRemaining -= usInDataLen;
        }
        else {
            usInDataLen = (CK_USHORT)ulBytesRemaining;
            ulBytesRemaining -= usInDataLen;
        }
        rv = P11Functions->C_EncryptUpdate(m_hSession, (CK_BYTE_PTR)pPlainTextPointer, usInDataLen,
            (CK_BYTE_PTR)pEncryptedDataPointer, &usOutDataLen);
        if (rv == CKR_OK) {
            cout << "Encrypting key..." << endl;
        }
        else {
            cout << "\n" "Error 0x" << hex << rv;
            cout << " while encrypting the RSA key.\n";
            return -1;
        }
        pPlainTextPointer += usInDataLen;
        pEncryptedDataPointer += usOutDataLen;
        ulEncryptedDataLength += usOutDataLen;
    }

    usOutDataLen = 0;
    CK_BYTE_PTR pOutData = (CK_BYTE_PTR)pEncryptedData;
    pOutData += ulEncryptedDataLength;
    rv = P11Functions->C_EncryptFinal(m_hSession, pOutData, &usOutDataLen);
    if (rv != CKR_OK) {
        cout << "C_EncryptFinal FAILED..." << endl;
        return -1;
    }
    ulEncryptedDataLength += usOutDataLen;

    mech.mechanism = CKM_DES3_CBC;
    mech.pParameter = (void*) "12345678"; // 8 byte IV
    mech.usParameterLen = 8;
    
    usTemplateSize = DIM(pPrivateKeyTemplate);
    pbWrappedKey = pEncryptedData;
    ulWrappedKeySize = ulEncryptedDataLength;
    rv = P11Functions->C_UnwrapKey(m_hSession, &mech, hSymKey, (CK_BYTE_PTR)pbWrappedKey,
        (CK_USHORT)ulWrappedKeySize, pPrivateKeyTemplate, usTemplateSize, &hPrivateRSAKey);
    if (rv != CKR_OK) {
        cout << "C_UnwrapKey FAILED...rv = " << hex << rv << endl;
        return -1;
    }
    else {
        cout << "Unwrapped Private key is " << hex << hPrivateRSAKey << endl;
    }
    if (pEncryptedData) {
        delete[] pEncryptedData;
    }
    /*rv = P11Functions->C_CreateObject(m_hSession, pPrivateKeyTemplate, 
        usTemplateSize, &hPrivateRSAKey);
    if (rv != CKR_OK) {
        cout << "C_Create private Object FAILED...rv = " << hex << rv << endl;
        return -1;
    }*/
    CK_ATTRIBUTE RSAFindPriTemplate[] =
    {
        {CKA_LABEL, pLabel, privateLabelSize}
    };

    CK_ULONG numHandles = 0;
    CK_OBJECT_HANDLE handles[MAX_NUM_OF_HANDLES] = { 0 };
    CK_OBJECT_HANDLE handles1[MAX_NUM_OF_HANDLES] = { 0 };
    rv = P11Functions->C_FindObjectsInit(m_hSession, RSAFindPriTemplate, 1);
    rv = P11Functions->C_FindObjects(m_hSession, handles, MAX_NUM_OF_HANDLES, &numHandles);
    if (numHandles == 0) {
        cout << "Private key was not created " << endl;
        return CKR_CANCEL;
    }
    for (unsigned int i = 0; i < numHandles; i++) {
        cout << "Private key is " << handles[i] << endl;
    }
    numHandles = 0;
    CK_ATTRIBUTE RSAFindPubTemplate[] =
    {
        {CKA_LABEL, (CK_VOID_PTR)pLabelPub, publicLabelSize}
    };
    rv = P11Functions->C_FindObjectsInit(m_hSession, RSAFindPubTemplate, 1);
    rv = P11Functions->C_FindObjects(m_hSession, handles1, MAX_NUM_OF_HANDLES, &numHandles);
    for (unsigned int i = 0; i < numHandles; i++) {
        cout << "Public key is " << handles1[i] << endl;
    }
    return rv;
}
#endif
