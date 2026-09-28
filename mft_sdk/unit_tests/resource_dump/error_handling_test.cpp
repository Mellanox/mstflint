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

namespace
{
// A segment type no device advertises, used to provoke a dump rejection.
const uint16_t UNSUPPORTED_SEGMENT = 0xdead;

const char* statusName(MstStatus status)
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

void printCase(const char* name, MstStatus status)
{
    printf("%s: %s\n", RD_FIELD_CASE, name);
    printf("  %s: %s\n", RD_FIELD_STATUS, statusName(status));
}
} // namespace

class MftSdkResourceDumpErrorTest : public ::testing::Test
{
protected:
    MstDevice mstDevice;
    MstResourceDumpRequest request;

    void SetUp() override
    {
        mstDevice = nullptr;
        std::memset(&request, 0, sizeof(request));
        request.vhca = MST_RESOURCE_DUMP_OWN_VHCA;
        request.resourceId = SEGMENT_TYPE_MENU;
    }

    void TearDown() override
    {
        if (mstDevice != nullptr)
        {
            mstReleaseDeviceHandle(mstDevice);
        }
    }
};

// Every entry point must reject NULL rather than dereference it.
TEST_F(MftSdkResourceDumpErrorTest, NullArguments)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstResourceMenu menu;
    MstResourceDumpData dumpData;

    printf("\n%s\n", RD_SECTION_ERROR_HANDLING);
    printf("-------------\n");

    status = mstGetResourceMenu(nullptr, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &menu);
    printCase("NullDeviceMenu", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstGetResourceMenu(mstDevice, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, nullptr);
    printCase("NullMenuOut", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstFreeResourceMenu(nullptr);
    printCase("FreeNullMenu", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstDumpResource(nullptr, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);
    printCase("NullDeviceDump", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstDumpResource(mstDevice, nullptr, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);
    printCase("NullRequest", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, nullptr);
    printCase("NullDumpOut", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstFreeResourceDump(nullptr);
    printCase("FreeNullDump", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);

    status = mstDumpResourceToFile(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, nullptr);
    printCase("NullFilename", status);
    EXPECT_EQ(status, MST_ERROR_INVALID_ARGUMENT);
}

// A segment the device does not advertise must be rejected, with an error string.
TEST_F(MftSdkResourceDumpErrorTest, UnsupportedSegment)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    request.resourceId = UNSUPPORTED_SEGMENT;
    MstResourceDumpData dumpData;
    status = mstDumpResource(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &dumpData);
    printCase("UnsupportedSegment", status);
    if (status == MST_SUCCESS)
    {
        mstFreeResourceDump(&dumpData);
        FAIL() << "Dumping an unadvertised segment should not succeed";
    }
    EXPECT_STRNE(mstGetLastErrorString(mstDevice), "") << "A failed dump must leave an error string";
}

// An undersized buffer must be reported through the status, not overrun.
TEST_F(MftSdkResourceDumpErrorTest, UndersizedBuffer)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    unsigned char tinyBuffer[4];
    size_t dumpSize = 0;
    status = mstDumpResourceToBuffer(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, tinyBuffer,
                                     sizeof(tinyBuffer), &dumpSize);
    printCase("UndersizedBuffer", status);
    EXPECT_EQ(status, MST_ERROR_INSUFFICIENT_BUFFER);
    EXPECT_GT(dumpSize, sizeof(tinyBuffer)) << "The required size must be reported even when the buffer is too small";
}

// A path that cannot be created must surface as a dump failure, not a crash.
TEST_F(MftSdkResourceDumpErrorTest, UnwritableFile)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    status = mstDumpResourceToFile(mstDevice, &request, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE,
                                   "/nonexistent-directory/resource_dump.bin");
    printCase("UnwritableFile", status);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_DUMP_RESOURCE);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
