/*
 * Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Full-path metadata: print field names using full ADB paths */
static int test_full_path_metadata(MstDevice mstDevice, const char* devicePci, const char* regName)
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
        printf("Failed to get %s full-path metadata: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_FULL_PATH_METADATA, meta.name);
    printf("-----------------------------\n");
    printf("%s: %u\n", FIELD_FIELD_COUNT, meta.number_of_fields);
    for (unsigned int i = 0; i < meta.number_of_fields; i++)
    {
        printf("%-55s: addr=0x%04x bit_offset=%u bit_size=%u access=%s\n",
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

/* Full-path register GET: init map with fullPath=true, send GET, print fields */
static int test_full_path_register_get(MstDevice mstDevice, const char* devicePci, const char* regName)
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
        printf("Failed to init %s full-path map: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    if (status != MST_SUCCESS)
    {
        printf("Failed to send %s GET: %s\n", regName, mstGetLastErrorString(mstDevice));
        mstFreePrmRegisterMap(&regMap);
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    printf("%s: %s\n", SECTION_FULL_PATH_GET, regMap.name);
    printf("------------------------\n");
    for (unsigned int i = 0; i < regMap.number_of_fields; i++)
    {
        printf("%-55s: %s\n", regMap.fields[i].name, fieldValueToHexString(regMap.fields[i].value));
    }

    mstFreePrmRegisterMap(&regMap);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int full_path_test_main(int argc, char** argv)
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

    /* Full-path metadata */
    result |= test_full_path_metadata(mstDevice, devicePci, "MGIR");
    result |= test_full_path_metadata(mstDevice, devicePci, "CREDENTIAL_HANDLE");

    /* Full-path register GET */
    result |= test_full_path_register_get(mstDevice, devicePci, "MGIR");

    return result;
}
