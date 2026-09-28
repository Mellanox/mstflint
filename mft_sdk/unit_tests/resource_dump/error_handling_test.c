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
#include "resource_dump_fields.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A segment type no device advertises, used to provoke a dump rejection. */
#define UNSUPPORTED_SEGMENT 0xdead

static const char* statusName(MstStatus status)
{
    switch (status)
    {
        case MST_SUCCESS:
            return "MST_SUCCESS";
        case MST_ERROR_INVALID_ARGUMENT:
            return "MST_ERROR_INVALID_ARGUMENT";
        case MST_ERROR_NOT_SUPPORTED:
            return "MST_ERROR_NOT_SUPPORTED";
        case MST_ERROR_FAILED_TO_OPEN_DEVICE:
            return "MST_ERROR_FAILED_TO_OPEN_DEVICE";
        case MST_ERROR_FAILED_TO_SEND_ACCESS_REG:
            return "MST_ERROR_FAILED_TO_SEND_ACCESS_REG";
        case MST_ERROR_INSUFFICIENT_BUFFER:
            return "MST_ERROR_INSUFFICIENT_BUFFER";
        case MST_ERROR_FAILED_TO_DUMP_RESOURCE:
            return "MST_ERROR_FAILED_TO_DUMP_RESOURCE";
        default:
            return "MST_ERROR_OTHER";
    }
}

static void printCase(const char* name, MstStatus status)
{
    printf("%s: %s\n", RD_FIELD_CASE, name);
    printf("  %s: %s\n", RD_FIELD_STATUS, statusName(status));
}

static int testErrorHandling(const char* devicePci)
{
    MstDevice mstDevice = NULL;
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s: %s\n", devicePci, mstGetInitErrorString());
        return 1;
    }

    MstResourceDumpRequest request;
    memset(&request, 0, sizeof(request));
    request.vhca = MST_RESOURCE_DUMP_OWN_VHCA;

    MstResourceMenu menu;
    MstResourceDumpData dumpData;
    unsigned int cases = 0;

    printf("%s\n", RD_SECTION_ERROR_HANDLING);
    printf("-------------\n");

    printCase("NullDeviceMenu", mstGetResourceMenu(NULL, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &menu));
    cases++;
    printCase("NullMenuOut", mstGetResourceMenu(mstDevice, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, NULL));
    cases++;
    printCase("FreeNullMenu", mstFreeResourceMenu(NULL));
    cases++;
    printCase("NullDeviceDump", mstDumpResource(NULL, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData));
    cases++;
    printCase("NullRequest", mstDumpResource(mstDevice, NULL, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData));
    cases++;
    printCase("NullDumpOut", mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, NULL));
    cases++;
    printCase("FreeNullDump", mstFreeResourceDump(NULL));
    cases++;
    printCase("NullFilename", mstDumpResourceToFile(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, NULL));
    cases++;

    /* A segment the device does not advertise must be rejected, not dumped. */
    request.resourceId = UNSUPPORTED_SEGMENT;
    MstStatus status = mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);
    printCase("UnsupportedSegment", status);
    if (status == MST_SUCCESS)
    {
        mstFreeResourceDump(&dumpData);
    }
    cases++;

    /* An undersized buffer must be reported, not overrun. Dump the menu segment: it is the one
     * resource every device supporting resource dump advertises, so the call reaches the buffer
     * check instead of failing earlier on an unknown segment. */
    request.resourceId = SEGMENT_TYPE_MENU;
    unsigned char tinyBuffer[4];
    size_t dumpSize = 0;
    printCase("UndersizedBuffer",
              mstDumpResourceToBuffer(
                mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, tinyBuffer, sizeof(tinyBuffer), &dumpSize));
    cases++;

    /* A path that cannot be created must surface as a dump failure. */
    printCase("UnwritableFile",
              mstDumpResourceToFile(
                mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, "/nonexistent-directory/resource_dump.bin"));
    cases++;

    printf("%s: %u\n", RD_FIELD_TOTAL, cases);

    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int resource_dump_error_handling_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* devicePci = "";
    if (argc > 1)
    {
        devicePci = argv[1];
    }
    return testErrorHandling(devicePci);
}
