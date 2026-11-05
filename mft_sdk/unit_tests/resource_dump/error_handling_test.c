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
