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
#include <cstring>
#include <string>

class MftSdkFullPathTest : public ::testing::Test
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
        printf("%-55s: addr=0x%04x bit_offset=%u bit_size=%u access=%s\n",
               meta.fields[i].name,
               meta.fields[i].address,
               meta.fields[i].bitOffset,
               meta.fields[i].bitSize,
               accessTypeToString(meta.fields[i].accessType));
    }
}

static void printRegisterGetFields(const MstPrmRegisterMap& regMap)
{
    for (unsigned int i = 0; i < regMap.number_of_fields; i++)
    {
        printf("%-55s: %s\n", regMap.fields[i].name, fieldValueToHexString(regMap.fields[i].value));
    }
}

// =========================================================================
// Full-Path Metadata
// =========================================================================

TEST_F(MftSdkFullPathTest, FullPathMetadata_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "MGIR", &meta);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get MGIR full-path metadata: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(meta.number_of_fields, 0u);

    bool foundDotField = false;
    for (unsigned int i = 0; i < meta.number_of_fields; i++)
    {
        if (strchr(meta.fields[i].name, '.') != nullptr)
        {
            foundDotField = true;
            break;
        }
    }
    EXPECT_TRUE(foundDotField) << "No hierarchical field names found in MGIR full-path metadata";

    printf("\n%s: %s\n", SECTION_FULL_PATH_METADATA, meta.name);
    printf("-----------------------------\n");
    printMetadataFields(meta);

    mstFreePrmRegisterMetadata(&meta);
}

TEST_F(MftSdkFullPathTest, FullPathMetadata_CREDENTIAL_HANDLE)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "CREDENTIAL_HANDLE", &meta);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get CREDENTIAL_HANDLE full-path metadata: "
                                   << mstGetLastErrorString(mstDevice);
    ASSERT_GT(meta.number_of_fields, 0u);

    uint32_t addr1 = 0, addr2 = 0;
    bool found1 = false, found2 = false;
    for (unsigned int i = 0; i < meta.number_of_fields; i++)
    {
        if (std::string(meta.fields[i].name) == "crypto_login_object.state")
        {
            addr1 = meta.fields[i].address;
            found1 = true;
        }
        else if (std::string(meta.fields[i].name) == "credential_object.state")
        {
            addr2 = meta.fields[i].address;
            found2 = true;
        }
    }
    EXPECT_TRUE(found1) << "crypto_login_object.state not found";
    EXPECT_TRUE(found2) << "credential_object.state not found";
    if (found1 && found2)
    {
        EXPECT_NE(addr1, addr2) << "crypto_login_object.state and credential_object.state share the same address";
    }

    printf("\n%s: %s\n", SECTION_FULL_PATH_METADATA, meta.name);
    printf("-----------------------------\n");
    printMetadataFields(meta);

    mstFreePrmRegisterMetadata(&meta);
}

// =========================================================================
// Full-Path Register GET
// =========================================================================

TEST_F(MftSdkFullPathTest, FullPathRegisterGet_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "MGIR", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init MGIR full-path map: " << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send MGIR GET: " << mstGetLastErrorString(mstDevice);

    uint32_t value;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "hw_info.device_id", &value);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get hw_info.device_id: " << mstGetLastErrorString(mstDevice);

    status = mstGetPRMRegisterField(mstDevice, &regMap, "device_id", &value);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG)
      << "Short name 'device_id' should be rejected with fullPath=true";
    EXPECT_STREQ(mstGetLastErrorString(mstDevice), "Can't find field name: device_id");

    printf("\n%s: %s\n", SECTION_FULL_PATH_GET, regMap.name);
    printf("------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
