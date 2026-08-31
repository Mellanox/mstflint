/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_register_get(MstDevice mstDevice, const char* devicePci, const char* regName)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterMap regMap;
    MstStatus status = mstInitRegisterMap(mstDevice, regName, &regMap);
    if (status != MST_SUCCESS)
    {
        printf("Failed to init %s map: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    if (strcmp(regName, "MCAM") == 0)
    {
        mstSetPRMRegisterField(mstDevice, &regMap, "access_reg_group", 0x0);
        mstSetPRMRegisterField(mstDevice, &regMap, "feature_group", 0x0);
    }

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        printf("Failed to send %s GET: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_REGISTER_GET, regMap.name);
    printf("------------------------\n");
    for (unsigned int i = 0; i < regMap.number_of_fields; i++)
    {
        printf("%-35s: %s\n", regMap.fields[i].name, fieldValueToHexString(regMap.fields[i].value));
    }

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

typedef struct
{
    const char* fieldName;
    uint32_t value;
} IndexField;

static int test_register_get_indexed(MstDevice mstDevice,
                                     const char* devicePci,
                                     const char* regName,
                                     const IndexField* indexes,
                                     unsigned int numIndexes)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterMap regMap;
    MstStatus status = mstInitRegisterMap(mstDevice, regName, &regMap);
    if (status != MST_SUCCESS)
    {
        printf("Failed to init %s map: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    for (unsigned int i = 0; i < numIndexes; i++)
    {
        status = mstSetPRMRegisterField(mstDevice, &regMap, indexes[i].fieldName, indexes[i].value);
        if (status != MST_SUCCESS)
        {
            printf("Failed to set index %s: %s\n", indexes[i].fieldName, mstGetLastErrorString(mstDevice));
            mstFreePrmRegisterMap(&regMap);
            mstReleaseDeviceHandle(mstDevice);
            return 1;
        }
    }

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        printf("Failed to send %s GET: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_REGISTER_GET_INDEXED, regMap.name);
    printf("%s:", FIELD_INDEXES);
    for (unsigned int i = 0; i < numIndexes; i++)
    {
        printf(" %s=%s", indexes[i].fieldName, fieldValueToHexString(indexes[i].value));
        if (i + 1 < numIndexes)
            printf(",");
    }
    printf("\n");
    printf("----------------------------------\n");
    for (unsigned int i = 0; i < regMap.number_of_fields; i++)
    {
        printf("%-35s: %s\n", regMap.fields[i].name, fieldValueToHexString(regMap.fields[i].value));
    }

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

static int test_register_set_paos(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterMap regMap;
    MstStatus status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        printf("Failed to init PAOS map: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        printf("Failed to GET PAOS: %s\n", mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    uint32_t adminStatusBefore;
    mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusBefore);

    printf("%s: PAOS\n", SECTION_REGISTER_SET);
    printf("%s: local_port=1\n", FIELD_INDEXES);
    printf("------------------------\n");
    printf("Step 1 - GET (before):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusBefore));
    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    mstSetPRMRegisterField(mstDevice, &regMap, "admin_status", adminStatusBefore);
    mstSetPRMRegisterField(mstDevice, &regMap, "e", 0x1);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_SET);
    printf("Step 2 - SET (write-back same value):\n");
    printf("  Status: %s\n", status == MST_SUCCESS ? "SUCCESS" : "FAIL");
    mstFreePrmRegisterMap(&regMap);

    if (status != MST_SUCCESS)
    {
        printf("SET failed: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    uint32_t adminStatusAfter;
    mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusAfter);

    printf("Step 3 - GET (after):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusAfter));
    printf("Match: %s\n", adminStatusBefore == adminStatusAfter ? "YES" : "NO");

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(mstDevice);
    return (adminStatusBefore == adminStatusAfter) ? 0 : 1;
}

static int test_register_rmw_paos(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterMap regMap;
    MstStatus status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        printf("Failed to init PAOS map: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        printf("Failed to GET PAOS: %s\n", mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    uint32_t adminStatusBefore;
    mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusBefore);

    printf("%s (read-modify-write): PAOS\n", SECTION_REGISTER_SET);
    printf("%s: local_port=1\n", FIELD_INDEXES);
    printf("------------------------\n");
    printf("Step 1 - GET (before):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusBefore));
    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    mstSetPRMRegisterField(mstDevice, &regMap, "admin_status", adminStatusBefore);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_SET_READ_MODIFY_WRITE);
    printf("Step 2 - RMW (write-back same value):\n");
    printf("  Status: %s\n", status == MST_SUCCESS ? "SUCCESS" : "FAIL");
    mstFreePrmRegisterMap(&regMap);

    if (status != MST_SUCCESS)
    {
        printf("RMW failed: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status != MST_SUCCESS)
    {
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }
    mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    uint32_t adminStatusAfter;
    mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusAfter);

    printf("Step 3 - GET (after):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusAfter));
    printf("Match: %s\n", adminStatusBefore == adminStatusAfter ? "YES" : "NO");

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(mstDevice);
    return (adminStatusBefore == adminStatusAfter) ? 0 : 1;
}

static int test_raw_register_get(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    unsigned int dataSize = 0xa0;
    unsigned char data[0xa0] = {0};
    MstStatus status = mstSendRawPRMRegister(mstDevice, 0x9020, MST_PRM_GET, (void*)data, dataSize);
    if (status != MST_SUCCESS)
    {
        printf("Failed to send raw MGIR GET: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: 0x9020 (size=0xa0)\n", SECTION_RAW_REGISTER_GET);
    printf("--------------------------------------------\n");
    for (unsigned int i = 0; i < dataSize; i += 16)
    {
        printf("%04x:", i);
        for (unsigned int j = 0; j < 16 && i + j < dataSize; j++)
        {
            printf(" %02x", data[i + j]);
        }
        printf("\n");
    }

    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int register_access_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* devicePci = "";
    if (argc > 1)
    {
        devicePci = argv[1];
    }

    MstDevice mstDevice = NULL;
    int result = 0;

    result |= test_register_get(mstDevice, devicePci, "MGIR");
    result |= test_register_get(mstDevice, devicePci, "MCAM");

    IndexField mtmpIndexes[] = {{"sensor_index", 0}};
    result |= test_register_get_indexed(mstDevice, devicePci, "MTMP", mtmpIndexes, 1);

    IndexField paosIndexes[] = {{"local_port", 1}};
    result |= test_register_get_indexed(mstDevice, devicePci, "PAOS", paosIndexes, 1);

    IndexField ptysIndexes[] = {{"local_port", 1}, {"proto_mask", 0x7}};
    result |= test_register_get_indexed(mstDevice, devicePci, "PTYS", ptysIndexes, 2);

    result |= test_register_set_paos(mstDevice, devicePci);
    result |= test_register_rmw_paos(mstDevice, devicePci);
    result |= test_raw_register_get(mstDevice, devicePci);

    return result;
}
