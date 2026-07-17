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

#include "gtest/gtest.h"

#include <cstdio>
#include <string>

class MftSdkMetadataTest : public ::testing::Test
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
};

static void printMetadataFields(const MstPrmRegisterMetadata& meta)
{
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
}

TEST_F(MftSdkMetadataTest, RegisterMetadata_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "MGIR", &meta);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get MGIR metadata: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(meta.number_of_fields, 0u);

    printf("\n%s: %s\n", SECTION_REGISTER_METADATA, meta.name);
    printf("-----------------------------\n");
    printMetadataFields(meta);

    mstFreePrmRegisterMetadata(&meta);
}

TEST_F(MftSdkMetadataTest, RegisterMetadata_MCAM)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "MCAM", &meta);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get MCAM metadata: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(meta.number_of_fields, 0u);

    printf("\n%s: %s\n", SECTION_REGISTER_METADATA, meta.name);
    printf("-----------------------------\n");
    printMetadataFields(meta);

    mstFreePrmRegisterMetadata(&meta);
}

TEST_F(MftSdkMetadataTest, ExpandedMetadata_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterExpandedMetadata meta;
    status = mstGetRegisterExpandedMetadata(mstDevice, "MGIR", &meta);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get expanded metadata: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(meta.number_of_fields, 0u);

    printf("\n%s: %s\n", SECTION_EXPANDED_METADATA, meta.name);
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
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
