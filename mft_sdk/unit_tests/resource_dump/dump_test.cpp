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
#include "resource_dump_fields.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace
{
// A resource dump is a sequence of segments, each prefixed by a 4-byte header of
// {uint16 segment_type, uint16 length_dw} in host byte order, where length_dw
// counts the header itself. Walking it needs nothing from the SDK internals.
const uint32_t SEGMENT_HEADER_SIZE = 4;

// Bounds the runtime on devices with a large menu; whatever is left over is
// reported as skipped rather than silently dropped.
const uint32_t MAX_DUMPED_RESOURCES = 16;

const char* const DUMP_FILE_PREFIX = "/tmp/mft_sdk_resource_dump_cpp_";

uint16_t readUint16(const unsigned char* data)
{
    uint16_t value;
    std::memcpy(&value, data, sizeof(value));
    return value;
}

// Prints the segment framing (type:length_dw pairs) and returns the segment
// count, or -1 if the stream is malformed.
int printLayout(const unsigned char* data, uint32_t size)
{
    uint32_t offset = 0;
    int segments = 0;

    printf("  %s:", RD_FIELD_LAYOUT);
    while (offset + SEGMENT_HEADER_SIZE <= size)
    {
        uint16_t segmentType = readUint16(data + offset);
        uint16_t lengthDw = readUint16(data + offset + sizeof(uint16_t));
        uint32_t lengthBytes = static_cast<uint32_t>(lengthDw) * 4;

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

// A resource is dumpable with no extra parameters when the device does not
// mark any of its dump parameters mandatory.
bool needsNoParameters(const MstResourceMenuRecord& record)
{
    return !record.mustHaveIndex1 && !record.mustHaveIndex2 && !record.mustHaveNumOfObj1 && !record.mustHaveNumOfObj2;
}

MstResourceDumpRequest makeRequest(uint16_t resourceId)
{
    MstResourceDumpRequest request;
    std::memset(&request, 0, sizeof(request));
    request.resourceId = resourceId;
    request.vhca = MST_RESOURCE_DUMP_OWN_VHCA;
    return request;
}
} // namespace

class MftSdkResourceDumpTest : public ::testing::Test
{
protected:
    MstDevice mstDevice;

    void SetUp() override { mstDevice = nullptr; }

    void TearDown() override
    {
        if (mstDevice != nullptr)
        {
            mstReleaseDeviceHandle(mstDevice);
        }
    }

    // Collects the resources the device advertises as needing no dump parameters.
    std::vector<uint16_t> dumpableResources(uint32_t& skipped)
    {
        std::vector<uint16_t> resources;
        MstResourceMenu menu;
        if (mstGetResourceMenu(mstDevice, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &menu) != MST_SUCCESS)
        {
            return resources;
        }
        for (uint32_t i = 0; i < menu.numberOfRecords; i++)
        {
            if (needsNoParameters(menu.records[i]) && resources.size() < MAX_DUMPED_RESOURCES)
            {
                resources.push_back(menu.records[i].segmentType);
            }
            else
            {
                skipped++;
            }
        }
        mstFreeResourceMenu(&menu);
        return resources;
    }
};

TEST_F(MftSdkResourceDumpTest, DumpAdvertisedResources)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    uint32_t skipped = 0;
    std::vector<uint16_t> resources = dumpableResources(skipped);
    ASSERT_FALSE(resources.empty()) << "The device advertises no resource dumpable without parameters";

    printf("\n%s\n", RD_SECTION_RESOURCE_DUMP);
    printf("-------------\n");

    uint32_t dumped = 0;
    for (size_t i = 0; i < resources.size(); i++)
    {
        MstResourceDumpRequest request = makeRequest(resources[i]);
        MstResourceDumpData dumpData;
        status = mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);

        printf("%s: 0x%x\n", RD_FIELD_SEGMENT_TYPE, resources[i]);
        if (status != MST_SUCCESS)
        {
            printf("  %s: FAILED %s\n", RD_FIELD_STATUS, mstGetLastErrorString(mstDevice));
            ADD_FAILURE() << "Failed to dump resource 0x" << std::hex << resources[i] << ": "
                          << mstGetLastErrorString(mstDevice);
            continue;
        }

        printf("  %s: %u\n", RD_FIELD_SIZE, dumpData.size);
        int segments = printLayout(dumpData.data, dumpData.size);
        printf("  %s: %d\n", RD_FIELD_SEGMENTS, segments);
        EXPECT_GT(segments, 0) << "Dump of resource 0x" << std::hex << resources[i] << " is not a valid segment stream";

        char filename[256];
        snprintf(filename, sizeof(filename), "%s0x%x.bin", DUMP_FILE_PREFIX, resources[i]);
        EXPECT_EQ(mstDumpResourceToFile(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, filename), MST_SUCCESS)
          << "Failed to dump resource 0x" << std::hex << resources[i] << " to a file";
        printf("  %s: %s\n", RD_FIELD_FILE, filename);

        mstFreeResourceDump(&dumpData);
        dumped++;
    }

    printf("%s: %u\n", RD_FIELD_TOTAL, dumped);
    printf("%s: %u\n", RD_FIELD_SKIPPED, skipped);
}

// The buffer variant must report the size it needs before it will fill anything.
TEST_F(MftSdkResourceDumpTest, DumpToBufferReportsRequiredSize)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    uint32_t skipped = 0;
    std::vector<uint16_t> resources = dumpableResources(skipped);
    ASSERT_FALSE(resources.empty()) << "The device advertises no resource dumpable without parameters";

    MstResourceDumpRequest request = makeRequest(resources[0]);
    size_t dumpSize = 0;
    status = mstDumpResourceToBuffer(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, nullptr, 0, &dumpSize);
    ASSERT_EQ(status, MST_ERROR_INSUFFICIENT_BUFFER) << "A NULL buffer should report an insufficient buffer";
    ASSERT_GT(dumpSize, 0u) << "The required dump size was not reported";

    std::vector<unsigned char> buffer(dumpSize);
    size_t filledSize = 0;
    ASSERT_EQ(mstDumpResourceToBuffer(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, buffer.data(),
                                      buffer.size(), &filledSize),
              MST_SUCCESS)
      << "Failed to dump into a correctly sized buffer: " << mstGetLastErrorString(mstDevice);
    EXPECT_EQ(filledSize, dumpSize) << "The dump size changed between the two calls";
}

// Stripping the control segments must leave a strictly smaller, still well-framed dump.
TEST_F(MftSdkResourceDumpTest, StripControlSegments)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    uint32_t skipped = 0;
    std::vector<uint16_t> resources = dumpableResources(skipped);
    ASSERT_FALSE(resources.empty()) << "The device advertises no resource dumpable without parameters";

    MstResourceDumpRequest request = makeRequest(resources[0]);
    MstResourceDumpData full;
    ASSERT_EQ(mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &full), MST_SUCCESS)
      << "Failed to dump resource: " << mstGetLastErrorString(mstDevice);

    request.stripControlSegments = true;
    MstResourceDumpData stripped;
    ASSERT_EQ(mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &stripped), MST_SUCCESS)
      << "Failed to dump resource without control segments: " << mstGetLastErrorString(mstDevice);

    EXPECT_LT(stripped.size, full.size) << "Stripping the control segments did not shrink the dump";
    EXPECT_GT(printLayout(stripped.data, stripped.size), 0) << "The stripped dump is not a valid segment stream";

    mstFreeResourceDump(&stripped);
    mstFreeResourceDump(&full);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
