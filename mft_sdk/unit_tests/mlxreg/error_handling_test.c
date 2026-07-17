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

static int test_error_handling(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    printf("%s\n", SECTION_ERROR_HANDLING);
    printf("--------------------\n");

    MstPrmRegisterMap regMap;
    MstStatus status = mstInitRegisterMap(mstDevice, "XXXX", &regMap);
    printf("Invalid register name           : %d - %s\n", status, mstGetLastErrorString(mstDevice));
    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "MCAM", &regMap);
    if (status == MST_SUCCESS)
    {
        status = mstSetPRMRegisterField(mstDevice, &regMap, "XXXX", 0x0);
        printf("Invalid field name (set)        : %d - %s\n", status, mstGetLastErrorString(mstDevice));

        status = mstGetPRMRegisterField(mstDevice, &regMap, "XXXX", 0x0);
        printf("Invalid field name (get)        : %d - %s\n", status, mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
    }

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    if (status == MST_SUCCESS)
    {
        status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
        printf("Missing required index          : %d - %s\n", status, mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
    }

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "XXXX", &meta);
    printf("Invalid register name (metadata): %d - %s\n", status, mstGetLastErrorString(mstDevice));
    mstFreePrmRegisterMetadata(&meta);

    MstPrmRegisterExpandedMetadata expMeta;
    status = mstGetRegisterExpandedMetadata(mstDevice, "XXXX", &expMeta);
    printf("Invalid register name (exp meta): %d - %s\n", status, mstGetLastErrorString(mstDevice));
    mstFreePrmRegisterExpandedMetadata(&expMeta);

    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int error_handling_test_main(int argc, char** argv)
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
    return test_error_handling(mstDevice, devicePci);
}
