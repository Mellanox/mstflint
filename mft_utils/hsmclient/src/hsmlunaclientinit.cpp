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
#include <string>
using namespace std;
static char  EnvLib[4096] = { 0 };
/*
    FUNCTION:        CK_BBOOL GetLibrary()
*/
CK_BBOOL HSMLunaClient::GetLibrary(string libPath)
{
    memset(EnvLib, 0, sizeof(EnvLib));
#ifdef OS_WIN32
    _snprintf(EnvLib, sizeof(EnvLib) - 1, "%s\\cryptoki.dll", pPath);
#else
#ifdef OS_HPUX
    snprintf(EnvLib, sizeof(EnvLib) - 1, "%s/libCryptoki2.sl", pPath);
#else
    if (libPath.empty()) {
        const char* pLibraryPath = this->pLibraryPath.c_str();
        const char* pLibraryName = this->pLibraryName.c_str();
        sprintf(EnvLib, "%s/%s", pLibraryPath, pLibraryName);
    }
    else{
        strncpy(EnvLib, (char*)libPath.c_str(), libPath.size());
    }
#endif
#endif
    return CK_TRUE;
}

/*
    FUNCTION:        CK_BBOOL LoadP11Functions()
*/
CK_BBOOL HSMLunaClient::LoadP11Functions(string libPath)
{
    CK_C_GetFunctionList C_GetFunctionList = NULL;
    CK_RV rv = CKR_TOKEN_NOT_PRESENT;

    if (GetLibrary(libPath) == CK_FALSE) {
        return CK_FALSE;
    }

    int flag = RTLD_LAZY;
    LibHandle = dlopen((char*)EnvLib, flag);

    if (LibHandle == NULL) {
        char* error = dlerror();
        printf("Shared object loading error %s, EnvLib is %s\n", error, (char*)EnvLib);
        return CK_FALSE;
    }

    C_GetFunctionList = (CK_C_GetFunctionList)dlsym(LibHandle, "C_GetFunctionList");
    if (C_GetFunctionList == NULL) {
        printf("C_GetFunctionList is NULL\n");
        return CK_FALSE;
    }
    rv = C_GetFunctionList(&P11Functions);
    if (rv != CKR_OK || P11Functions == NULL) {
        printf("P11Functions is NULL or return code is not OK %d\n", (int)rv);
        return rv;
    }
    rv = P11Functions->C_Initialize(NULL_PTR);
    if (rv == CKR_OK || rv == CKR_CRYPTOKI_ALREADY_INITIALIZED) {
        return CK_TRUE;
    }
    return CK_FALSE;
}

/*
    FUNCTION:        CK_BBOOL LoadSfntExtensionFunctions()
*/
CK_BBOOL HSMLunaClient::LoadSfntExtensionFunctions()
{
    CK_CA_GetFunctionList CA_GetFunctionList = NULL;
    CK_RV rv = CKR_TOKEN_NOT_PRESENT;
    CA_GetFunctionList = (CK_CA_GetFunctionList)dlsym(LibHandle, "CA_GetFunctionList");
    if (CA_GetFunctionList == NULL) {
        printf("CA_GetFunctionList failed\n");
        return CK_FALSE;
    }
    rv = CA_GetFunctionList(&SfntFunctions);
    if (rv != CKR_OK || SfntFunctions == NULL) {
        printf("CA_GetFunctionList SfntFunctions failed or return code is not OK : %d\n", (int)rv);
        return rv;
    }
    return CK_TRUE;
}

/*
    FUNCTION:        CK_RV FindFirstSlot( CK_SLOT_ID& pckSlot )
*/
CK_RV HSMLunaClient::FindFirstSlot(CK_SLOT_ID& pckSlot)
{
    CK_SLOT_ID_PTR pSlotList = NULL;
    CK_ULONG ulCount = 0;
    CK_RV retCode = CKR_OK;

    retCode = P11Functions->C_GetSlotList(CK_TRUE, NULL, &ulCount);
    if (retCode != CKR_OK) {
        printf("C_GetSlotList Failed.\n");
        return retCode;
    }
    else {
        if (ulCount == 0) {
            printf("C_GetSlotList returns 0 slots.\n");
            return retCode;
        }
    }
    pSlotList = (CK_SLOT_ID_PTR)new CK_SLOT_ID[ulCount*sizeof(CK_SLOT_ID)];
    if (pSlotList == NULL) {
        printf("Memory allocation error. ulCount = %u\n", (unsigned int)ulCount);
        return retCode;
    }

    retCode = P11Functions->C_GetSlotList(CK_TRUE, pSlotList, &ulCount);
    if (retCode != CKR_OK) {
        return retCode;
    }
    pckSlot = pSlotList[0];
    if (pSlotList) {
        delete[] pSlotList;
    }
    cout << "Working with slot " << pckSlot << endl;
    return retCode;
}


CK_BBOOL HSMLunaClient::Init(string password, string libPath)
{
    if (LoadP11Functions(libPath) == CK_FALSE) {
        printf("Failed to load PKCS11 library!\n");
        return CK_FALSE;
    }

    if (LoadSfntExtensionFunctions() == CK_FALSE) {
        printf("Failed to load SafeNet extension functions!\n");
        return CK_FALSE;
    }
    CK_RV rv = FindFirstSlot(m_ckSlot);
    if ((rv != CKR_OK)) {
        return CK_FALSE;
    }

    rv = P11Functions->C_OpenSession(m_ckSlot, CKF_RW_SESSION | CKF_SERIAL_SESSION, NULL, NULL, &m_hSession);
    if (rv != CKR_OK) {
        return CK_FALSE;
    }

    if (!password.empty()) {
        memset(bPassword, 0, sizeof(bPassword));
        memcpy(bPassword, password.c_str(), password.size());
    }
    rv = P11Functions->C_Login(m_hSession, CKU_USER, bPassword, (CK_ULONG)strlen((char*)bPassword));
    if (rv != CKR_OK) {
        return CK_FALSE;
    }
    return CK_TRUE;
}
void HSMLunaClient::CleanUp()
{
    if (P11Functions)
    {
        if (m_hSession) {
            P11Functions->C_CloseSession(m_hSession);
        }
        P11Functions->C_Finalize(NULL_PTR);
    }

    if (LibHandle)
    {
#ifdef OS_WIN32
        FreeLibrary(LibHandle);
#else
#ifdef OS_HPUX
        shl_unload(LibHandle);
#else
        dlclose(LibHandle);
#endif
#endif
    }
}
#endif
