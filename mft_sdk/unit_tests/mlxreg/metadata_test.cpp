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
