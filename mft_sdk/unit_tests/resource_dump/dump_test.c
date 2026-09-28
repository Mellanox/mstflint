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

/* A resource dump is a sequence of segments, each prefixed by a 4-byte header
 * of {uint16 segment_type, uint16 length_dw} in host byte order, where length_dw
 * counts the header itself. Walking it needs nothing from the SDK internals. */
#define SEGMENT_HEADER_SIZE 4

/* Bounds the runtime on devices with a large menu; whatever is left over is
 * reported as skipped rather than silently dropped. */
#define MAX_DUMPED_RESOURCES 16

static const char* const DUMP_FILE_PREFIX = "/tmp/mft_sdk_resource_dump_";

static uint16_t readUint16(const unsigned char* data)
{
    uint16_t value;
    memcpy(&value, data, sizeof(value));
    return value;
}

/* Prints the segment framing (type:length_dw pairs) and returns the segment
 * count, or -1 if the stream is malformed. */
static int printLayout(const unsigned char* data, uint32_t size)
{
    uint32_t offset = 0;
    int segments = 0;

    printf("  %s:", RD_FIELD_LAYOUT);
    while (offset + SEGMENT_HEADER_SIZE <= size)
    {
        uint16_t segmentType = readUint16(data + offset);
        uint16_t lengthDw = readUint16(data + offset + sizeof(uint16_t));
        uint32_t lengthBytes = (uint32_t)lengthDw * 4;

        if (lengthBytes < SEGMENT_HEADER_SIZE || offset + lengthBytes > size)
        {
            printf(" MALFORMED@%u\n", offset);
            return -1;
        }
        printf(" 0x%x:%u", segmentType, lengthDw);
        segments++;
        offset += lengthBytes;
    }
    printf("\n");

    if (offset != size)
    {
        printf("  %s: trailing %u bytes\n", RD_FIELD_STATUS, size - offset);
        return -1;
    }
    return segments;
}

static int dumpResource(MstDevice mstDevice, uint16_t resourceId)
{
    MstResourceDumpRequest request;
    memset(&request, 0, sizeof(request));
    request.resourceId = resourceId;
    request.vhca = MST_RESOURCE_DUMP_OWN_VHCA;

    MstResourceDumpData dumpData;
    MstStatus status = mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);
    if (status != MST_SUCCESS)
    {
        printf("%s: 0x%x\n", RD_FIELD_SEGMENT_TYPE, resourceId);
        printf("  %s: FAILED %s\n", RD_FIELD_STATUS, mstGetLastErrorString(mstDevice));
        return 1;
    }

    printf("%s: 0x%x\n", RD_FIELD_SEGMENT_TYPE, resourceId);
    printf("  %s: %u\n", RD_FIELD_SIZE, dumpData.size);
    int segments = printLayout(dumpData.data, dumpData.size);
    printf("  %s: %d\n", RD_FIELD_SEGMENTS, segments);

    /* Same dump through the to-file path, so the Python runner can compare the
     * framing against the file resourcedump writes with --bin. */
    char filename[256];
    snprintf(filename, sizeof(filename), "%s0x%x.bin", DUMP_FILE_PREFIX, resourceId);
    status = mstDumpResourceToFile(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, filename);
    if (status == MST_SUCCESS)
    {
        printf("  %s: %s\n", RD_FIELD_FILE, filename);
    }
    else
    {
        printf("  %s: FILE FAILED %s\n", RD_FIELD_STATUS, mstGetLastErrorString(mstDevice));
    }

    mstFreeResourceDump(&dumpData);
    return (segments < 0 || status != MST_SUCCESS) ? 1 : 0;
}

/* A resource is dumpable with no extra parameters when the device does not
 * mark any of its dump parameters mandatory. */
static bool needsNoParameters(const MstResourceMenuRecord* record)
{
    return !record->mustHaveIndex1 && !record->mustHaveIndex2 && !record->mustHaveNumOfObj1 &&
           !record->mustHaveNumOfObj2;
}

static int testResourceDump(const char* devicePci)
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

    printf("%s\n", RD_SECTION_RESOURCE_DUMP);
    printf("-------------\n");

    int failures = 0;
    unsigned int dumped = 0;
    unsigned int skipped = 0;
    for (uint32_t i = 0; i < menu.numberOfRecords; i++)
    {
        if (!needsNoParameters(&menu.records[i]))
        {
            skipped++;
            continue;
        }
        if (dumped >= MAX_DUMPED_RESOURCES)
        {
            skipped++;
            continue;
        }
        failures += dumpResource(mstDevice, menu.records[i].segmentType);
        dumped++;
    }

    printf("%s: %u\n", RD_FIELD_TOTAL, dumped);
    printf("%s: %u\n", RD_FIELD_SKIPPED, skipped);

    mstFreeResourceMenu(&menu);
    mstReleaseDeviceHandle(mstDevice);
    return failures == 0 ? 0 : 1;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int resource_dump_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* devicePci = "";
    if (argc > 1)
    {
        devicePci = argv[1];
    }
    return testResourceDump(devicePci);
}
