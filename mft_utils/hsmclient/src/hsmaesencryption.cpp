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
CK_BYTE*                        P_DecText = NULL;
CK_BYTE*                        P_EncText = NULL;
CK_ULONG                        EncSz = 0;
CK_ULONG                        PlainSz = 0;

/*
    FUNCTION:        CK_RV Generate3DESKey( CK_SESSION_HANDLE hSession )
*/
CK_RV HSMLunaClient::Generate3DESKey()
{
    CK_RV retCode = CKR_OK;
    CK_MECHANISM mech;
    CK_OBJECT_CLASS obClass = CKO_SECRET_KEY;
    CK_KEY_TYPE keyType = CKK_DES3;
    CK_CHAR pDESKeyLabel[] = "DES3 Encryption Key";
    CK_BBOOL yes = CK_TRUE;
    //CK_BBOOL no = CK_FALSE;
    CK_ULONG templateSz;

    CK_ATTRIBUTE   pDESKeyAttributes[] =
    {
        {CKA_CLASS,             &obClass,          sizeof(CK_OBJECT_CLASS)        },
        {CKA_KEY_TYPE,          &keyType,          sizeof(CK_KEY_TYPE)            },
        {CKA_LABEL,             pDESKeyLabel,      sizeof(pDESKeyLabel) - 1       },
        {CKA_PRIVATE,           &yes,              sizeof(CK_BBOOL)               },
        {CKA_SENSITIVE,         &yes,              sizeof(CK_BBOOL)               },
        {CKA_ENCRYPT,           &yes,              sizeof(CK_BBOOL)               },
        {CKA_DECRYPT,           &yes,              sizeof(CK_BBOOL)               },
        {CKA_WRAP,              &yes,              sizeof(CK_BBOOL)               },
        {CKA_UNWRAP,            &yes,              sizeof(CK_BBOOL)               },
        {CKA_EXTRACTABLE,       &yes,              sizeof(CK_BBOOL)               }
    };

    // Build mechanism
    mech.mechanism = CKM_DES3_KEY_GEN;
    mech.pParameter = NULL;
    mech.ulParameterLen = 0;

    templateSz = sizeof(pDESKeyAttributes) / sizeof(*pDESKeyAttributes);
    retCode = P11Functions->C_GenerateKey(m_hSession,
        &mech,
        pDESKeyAttributes,
        templateSz,
        &hSymKey);

    return retCode;
}


CK_RV HSMLunaClient::AES_EncryptData()
{
    CK_MECHANISM mech;
    CK_RV rv = CKR_OK;

    mech.mechanism = CKM_DES3_CBC;
    mech.pParameter = (void*) "12345678"; // 8 byte IV
    mech.ulParameterLen = 8;
    rv = P11Functions->C_EncryptInit(m_hSession, &mech, hSymKey);
    if (rv != CKR_OK) {
        return rv;
    }
    rv = P11Functions->C_Encrypt(m_hSession, PlainText, sizeof(PlainText), NULL, &EncSz);
    if (rv != CKR_OK) {
        return rv;
    }

    P_EncText = (CK_BYTE*)new CK_BYTE[EncSz];
    if (P_EncText == NULL) {
        return CKR_GENERAL_ERROR;
    }

    rv = P11Functions->C_Encrypt(m_hSession, PlainText, sizeof(PlainText), P_EncText, &EncSz);
    if (rv != CKR_OK) {
        return rv;
    }

    return rv;
}

CK_RV HSMLunaClient::AES_DecryptData()
{
    CK_MECHANISM mech;
    CK_RV rv = CKR_OK;

    mech.mechanism = CKM_DES3_CBC;
    mech.pParameter = (void*) "12345678"; // 8 byte IV
    mech.ulParameterLen = 8;

    rv = P11Functions->C_DecryptInit(m_hSession, &mech, hSymKey);
    if (rv != CKR_OK) {
        return rv;
    }

    rv = P11Functions->C_Decrypt(m_hSession, P_EncText, EncSz, NULL, &PlainSz);
    if (rv != CKR_OK) {
        return rv;
    }

    P_DecText = (CK_BYTE*)new CK_BYTE[PlainSz];
    if (P_DecText == NULL) {
        return rv;
    }

    rv = P11Functions->C_Decrypt(m_hSession, P_EncText, EncSz, P_DecText, &PlainSz);
    if (rv != CKR_OK) {
        return rv;
    }

    return rv;
}

CK_RV HSMLunaClient::TestAESEncryption()
{
    CK_RV rv = Generate3DESKey();
    if (rv != CKR_OK) {
        return rv;
    }

    rv = AES_EncryptData();
    if (rv != CKR_OK) {
        return rv;
    }

    rv = AES_DecryptData();
    if (rv != CKR_OK) {
        return rv;
    }

    if (P_DecText && (memcmp(PlainText, P_DecText, sizeof(PlainText)) == 0)) {
        printf("AES encryption is OKAY!\n");
        rv = 0;
    }
    else {
        printf("TestAESEncryption NOT OKAY! rv = 0x%x\n", (unsigned int)rv);
        rv = -1;
    }
    if (P_DecText) {
        delete[](P_DecText);
    }
    if (P_EncText) {
        delete[](P_EncText);
    }
    return rv;
}
#endif
