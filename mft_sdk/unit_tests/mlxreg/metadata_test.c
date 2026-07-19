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

static int test_register_metadata(MstDevice mstDevice, const char* devicePci, const char* regName)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterMetadata meta;
    MstStatus status = mstGetRegisterMetadata(mstDevice, regName, &meta);
    if (status != MST_SUCCESS)
    {
        printf("Failed to get %s metadata: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_REGISTER_METADATA, meta.name);
    printf("-----------------------------\n");
    printf("%s: %u\n", FIELD_FIELD_COUNT, meta.number_of_fields);
    for (unsigned int i = 0; i < meta.number_of_fields; i++)
    {
        printf("%-35s: addr=0x%04x bit_offset=%u bit_size=%u access=%s\n",
               meta.fields[i].name,
               meta.fields[i].address,
               meta.fields[i].bitOffset,
               meta.fields[i].bitSize,
               accessTypeToString(meta.fields[i].accessType));
    }

    mstFreePrmRegisterMetadata(&meta);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

static int test_expanded_metadata(MstDevice mstDevice, const char* devicePci, const char* regName)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstPrmRegisterExpandedMetadata meta;
    MstStatus status = mstGetRegisterExpandedMetadata(mstDevice, regName, &meta);
    if (status != MST_SUCCESS)
    {
        printf("Failed to get expanded metadata for %s: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_EXPANDED_METADATA, meta.name);
    printf("-----------------------------\n");
    printf("%s: %u\n", FIELD_FIELD_COUNT, meta.number_of_fields);
    for (unsigned int i = 0; i < meta.number_of_fields; i++)
    {
        printf("%s:\n", meta.fields[i].basicMetadata.name);
        printf("  %s: %s\n", FIELD_DESCRIPTION, meta.fields[i].description);
        printf("  %s: %s\n", FIELD_FULL_PATH, meta.fields[i].fullPath);
        printf("  %s (%u):\n", FIELD_ENUMS, meta.fields[i].number_of_enums);
        for (unsigned int j = 0; j < meta.fields[i].number_of_enums; j++)
        {
            printf("    %s = %u\n", meta.fields[i].enums[j].name, meta.fields[i].enums[j].value);
        }
    }

    mstFreePrmRegisterExpandedMetadata(&meta);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int metadata_test_main(int argc, char** argv)
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

    result |= test_register_metadata(mstDevice, devicePci, "MGIR");
    result |= test_register_metadata(mstDevice, devicePci, "MCAM");
    result |= test_expanded_metadata(mstDevice, devicePci, "MGIR");

    return result;
}
