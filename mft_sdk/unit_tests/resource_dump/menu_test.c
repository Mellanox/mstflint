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
#include "resource_dump_fields.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* applicability(bool supported, bool mandatory)
{
    if (!supported)
    {
        return RD_APPLICABILITY_NA;
    }
    return mandatory ? RD_APPLICABILITY_MANDATORY : RD_APPLICABILITY_OPTIONAL;
}

/* Renders the special-value column the way resourcedump's menu table does:
 * "all", "active", "all,active" or "N/A". */
static const char* specialValues(bool supportsAll, bool supportsActive)
{
    static char buffer[32];

    buffer[0] = '\0';
    if (supportsAll)
    {
        strcat(buffer, RD_SPECIAL_ALL);
    }
    if (supportsActive)
    {
        if (buffer[0] != '\0')
        {
            strcat(buffer, RD_SPECIAL_SEPARATOR);
        }
        strcat(buffer, RD_SPECIAL_ACTIVE);
    }
    return buffer[0] != '\0' ? buffer : RD_SPECIAL_NA;
}

static int compareBySegmentType(const void* a, const void* b)
{
    uint16_t left = ((const MstResourceMenuRecord*)a)->segmentType;
    uint16_t right = ((const MstResourceMenuRecord*)b)->segmentType;
    return (left > right) - (left < right);
}

/* The names are raw device bytes with interior NULs, so they travel to the runner as hex. */
static const char* nameHex(const char* name, char* buffer)
{
    int i;

    for (i = 0; i < MST_RESOURCE_DUMP_NAME_LENGTH; i++)
    {
        sprintf(buffer + 2 * i, "%02x", (unsigned char)name[i]);
    }
    return buffer;
}

static void printRecord(const MstResourceMenuRecord* record)
{
    char nameBuffer[2 * MST_RESOURCE_DUMP_NAME_LENGTH + 1];

    printf("%s: 0x%x (%s)\n", RD_FIELD_SEGMENT_TYPE, record->segmentType, nameHex(record->segmentName, nameBuffer));
    printf("  %s: %s %s=%s\n",
           RD_FIELD_INDEX1,
           applicability(record->supportIndex1, record->mustHaveIndex1),
           RD_FIELD_NAME,
           nameHex(record->index1Name, nameBuffer));
    printf("  %s: %s %s=%s\n",
           RD_FIELD_NUM_OF_OBJ1,
           applicability(record->supportNumOfObj1, record->mustHaveNumOfObj1),
           RD_FIELD_SPECIAL,
           specialValues(record->numOfObj1SupportsAll, record->numOfObj1SupportsActive));
    printf("  %s: %s %s=%s\n",
           RD_FIELD_INDEX2,
           applicability(record->supportIndex2, record->mustHaveIndex2),
           RD_FIELD_NAME,
           nameHex(record->index2Name, nameBuffer));
    printf("  %s: %s %s=%s\n",
           RD_FIELD_NUM_OF_OBJ2,
           applicability(record->supportNumOfObj2, record->mustHaveNumOfObj2),
           RD_FIELD_SPECIAL,
           specialValues(record->numOfObj2SupportsAll, record->numOfObj2SupportsActive));
}

static int testResourceMenu(const char* devicePci)
{
    MstDevice mstDevice = NULL;
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s: %s\n", devicePci, mstGetInitErrorString());
        return 1;
    }

    MstResourceMenu menu;
    MstStatus status = mstGetResourceMenu(mstDevice, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &menu);
    if (status != MST_SUCCESS)
    {
        printf("Failed to get the resource menu: %s\n", mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    /* Sorted so the record order is stable across sources and runs. */
    qsort(menu.records, menu.numberOfRecords, sizeof(MstResourceMenuRecord), compareBySegmentType);

    printf("%s\n", RD_SECTION_RESOURCE_MENU);
    printf("-------------\n");
    for (uint32_t i = 0; i < menu.numberOfRecords; i++)
    {
        printRecord(&menu.records[i]);
    }
    printf("%s: %u\n", RD_FIELD_TOTAL, menu.numberOfRecords);

    mstFreeResourceMenu(&menu);
    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int resource_menu_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* devicePci = "";
    if (argc > 1)
    {
        devicePci = argv[1];
    }
    return testResourceMenu(devicePci);
}
