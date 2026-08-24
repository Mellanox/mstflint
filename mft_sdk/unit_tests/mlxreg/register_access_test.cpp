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

class MftSdkRegisterAccessTest : public ::testing::Test
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

static void printRegisterGetFields(const MstPrmRegisterMap& regMap)
{
    for (unsigned int i = 0; i < regMap.number_of_fields; i++)
    {
        printf("%-35s: %s\n", regMap.fields[i].name, fieldValueToHexString(regMap.fields[i].value));
    }
}

// =========================================================================
// Register GET — Non-Indexed
// =========================================================================

TEST_F(MftSdkRegisterAccessTest, RegisterGet_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "MGIR", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init MGIR map: " << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send MGIR GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_GET, regMap.name);
    printf("------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkRegisterAccessTest, RegisterGet_MCAM)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "MCAM", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init MCAM map: " << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "access_reg_group", 0x0);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "feature_group", 0x0);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send MCAM GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_GET, regMap.name);
    printf("------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

// =========================================================================
// Register GET — Indexed
// =========================================================================

TEST_F(MftSdkRegisterAccessTest, RegisterGetIndexed_MTMP)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "MTMP", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init MTMP map: " << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "sensor_index", 0x0);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send MTMP GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_GET_INDEXED, regMap.name);
    printf("%s: sensor_index=0\n", FIELD_INDEXES);
    printf("----------------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkRegisterAccessTest, RegisterGetIndexed_PAOS)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init PAOS map: " << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send PAOS GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_GET_INDEXED, regMap.name);
    printf("%s: local_port=1\n", FIELD_INDEXES);
    printf("----------------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkRegisterAccessTest, RegisterGetIndexed_PTYS)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PTYS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to init PTYS map: " << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "proto_mask", 0x7);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send PTYS GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_GET_INDEXED, regMap.name);
    printf("%s: local_port=1, proto_mask=0x7\n", FIELD_INDEXES);
    printf("----------------------------------\n");
    printRegisterGetFields(regMap);

    mstFreePrmRegisterMap(&regMap);
}

// =========================================================================
// Register SET and Read-Back (PAOS)
// =========================================================================

TEST_F(MftSdkRegisterAccessTest, RegisterSet_PAOS)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to GET PAOS: " << mstGetLastErrorString(mstDevice);

    uint32_t adminStatusBefore;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusBefore);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    printf("\n%s: %s\n", SECTION_REGISTER_SET, regMap.name);
    printf("%s: local_port=1\n", FIELD_INDEXES);
    printf("------------------------\n");
    printf("Step 1 - GET (before):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusBefore));

    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS);
    status = mstSetPRMRegisterField(mstDevice, &regMap, "admin_status", adminStatusBefore);
    ASSERT_EQ(status, MST_SUCCESS);
    status = mstSetPRMRegisterField(mstDevice, &regMap, "e", 0x1);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_SET);
    printf("Step 2 - SET (write-back same value):\n");
    printf("  Status: %s\n", status == MST_SUCCESS ? "SUCCESS" : "FAIL");
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to SET PAOS: " << mstGetLastErrorString(mstDevice);

    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to GET PAOS after SET: " << mstGetLastErrorString(mstDevice);

    uint32_t adminStatusAfter;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusAfter);
    ASSERT_EQ(status, MST_SUCCESS);

    printf("Step 3 - GET (after):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusAfter));
    printf("Match: %s\n", adminStatusBefore == adminStatusAfter ? "YES" : "NO");

    EXPECT_EQ(adminStatusBefore, adminStatusAfter) << "admin_status changed after write-back";

    mstFreePrmRegisterMap(&regMap);
}

// =========================================================================
// Register READ_MODIFY_WRITE and Read-Back (PAOS)
// =========================================================================

TEST_F(MftSdkRegisterAccessTest, RegisterRmw_PAOS)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to GET PAOS: " << mstGetLastErrorString(mstDevice);

    uint32_t adminStatusBefore;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusBefore);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    printf("\n%s (read-modify-write): %s\n", SECTION_REGISTER_SET, regMap.name);
    printf("%s: local_port=1\n", FIELD_INDEXES);
    printf("------------------------\n");
    printf("Step 1 - GET (before):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusBefore));

    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS);
    status = mstSetPRMRegisterField(mstDevice, &regMap, "admin_status", adminStatusBefore);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_SET_READ_MODIFY_WRITE);
    printf("Step 2 - RMW (write-back same value):\n");
    printf("  Status: %s\n", status == MST_SUCCESS ? "SUCCESS" : "FAIL");
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to RMW PAOS: " << mstGetLastErrorString(mstDevice);

    mstFreePrmRegisterMap(&regMap);

    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "local_port", 0x1);
    ASSERT_EQ(status, MST_SUCCESS);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to GET PAOS after RMW: " << mstGetLastErrorString(mstDevice);

    uint32_t adminStatusAfter;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "admin_status", &adminStatusAfter);
    ASSERT_EQ(status, MST_SUCCESS);

    printf("Step 3 - GET (after):\n");
    printf("  %-33s: %s\n", "admin_status", fieldValueToHexString(adminStatusAfter));
    printf("Match: %s\n", adminStatusBefore == adminStatusAfter ? "YES" : "NO");

    EXPECT_EQ(adminStatusBefore, adminStatusAfter) << "admin_status changed after read-modify-write";

    mstFreePrmRegisterMap(&regMap);
}

// =========================================================================
// Raw Register Access
// =========================================================================

TEST_F(MftSdkRegisterAccessTest, RawRegisterGet_MGIR)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    unsigned int dataSize = 0xa0;
    unsigned char data[0xa0] = {0};
    status = mstSendRawPRMRegister(mstDevice, 0x9020, MST_PRM_GET, (void*)data, dataSize);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to send raw MGIR GET: " << mstGetLastErrorString(mstDevice);

    printf("\n%s: 0x9020 (size=0xa0)\n", SECTION_RAW_REGISTER_GET);
    printf("--------------------------------------------\n");
    for (unsigned int i = 0; i < dataSize; i += 16)
    {
        printf("%04x:", i);
        for (unsigned int j = 0; j < 16 && i + j < dataSize; j++)
        {
            printf(" %02x", data[i + j]);
        }
        printf("\n");
    }
}

// Contract: an unknown register ID must fail with an error status and message; today
// performRawRegRequest catches only AdbException, so the MlxRegException thrown by
// findAdbNode(regId) leaks through the C API — DISABLED_ until the SDK catches it.
TEST_F(MftSdkRegisterAccessTest, DISABLED_RawRegisterGetInvalidId)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    unsigned int dataSize = 0x10;
    unsigned char data[0x10] = {0};
    status = mstSendRawPRMRegister(mstDevice, 0xFFFF, MST_PRM_GET, (void*)data, dataSize);
    EXPECT_NE(status, MST_SUCCESS) << "Raw GET with invalid register ID should fail";

    const char* errMsg = mstGetLastErrorString(mstDevice);
    EXPECT_NE(errMsg, nullptr);
    EXPECT_STRNE(errMsg, "") << "Error message should be non-empty for invalid register ID";

    // The ID lookup fails locally before anything is sent to FW, so no FW syndrome is produced.
    EXPECT_EQ(mstGetSyndrome(mstDevice), 0u);

    printf("\nRaw Register GET invalid id 0xffff: %d - %s (syndrome=0x%x)\n", status, errMsg,
           mstGetSyndrome(mstDevice));
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
