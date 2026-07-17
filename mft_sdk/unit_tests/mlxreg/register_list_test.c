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

static int compare_strings(const void* a, const void* b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}

static int test_list_all_registers(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    char** registerNamesArray;
    unsigned int numRegisters;
    MstStatus status = mstShowAllPRMRegisters(mstDevice, &registerNamesArray, &numRegisters);
    if (status != MST_SUCCESS)
    {
        printf("Failed to show all PRM registers: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    qsort(registerNamesArray, numRegisters, sizeof(char*), compare_strings);

    printf("%s\n", SECTION_REGISTER_LIST);
    printf("-------------\n");
    for (unsigned int i = 0; i < numRegisters; i++)
    {
        printf("%s\n", registerNamesArray[i]);
    }
    printf("%s: %u\n", FIELD_TOTAL, numRegisters);

    mstFreePRMRegisterNamesArray(registerNamesArray, numRegisters);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int register_list_test_main(int argc, char** argv)
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
    return test_list_all_registers(mstDevice, devicePci);
}
