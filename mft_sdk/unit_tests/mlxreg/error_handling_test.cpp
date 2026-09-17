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
#include <cstdlib>
#include <string>

// EnvVarGuard comes from test_utils.h (shared by all unified/so test TUs).

class MftSdkErrorHandlingTest : public ::testing::Test
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

TEST_F(MftSdkErrorHandlingTest, ErrorInvalidRegisterName)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "XXXX", &regMap);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);
    EXPECT_STREQ(mstGetLastErrorString(mstDevice), "Can't find access register name: XXXX");
    // The name lookup fails locally before anything is sent to FW, so no syndrome is produced.
    EXPECT_EQ(mstGetSyndrome(mstDevice), 0u);

    printf("\n%s\n", SECTION_ERROR_HANDLING);
    printf("--------------------\n");
    printf("Invalid register name           : %d - %s\n", status, mstGetLastErrorString(mstDevice));

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkErrorHandlingTest, ErrorInvalidFieldName)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "MCAM", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSetPRMRegisterField(mstDevice, &regMap, "XXXX", 0x0);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);
    EXPECT_STREQ(mstGetLastErrorString(mstDevice), "Can't find field name: XXXX");

    printf("\nInvalid field name (set)        : %d - %s\n", status, mstGetLastErrorString(mstDevice));

    uint32_t value = 0;
    status = mstGetPRMRegisterField(mstDevice, &regMap, "XXXX", &value);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);
    EXPECT_STREQ(mstGetLastErrorString(mstDevice), "Can't find field name: XXXX");

    printf("Invalid field name (get)        : %d - %s\n", status, mstGetLastErrorString(mstDevice));

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkErrorHandlingTest, ErrorMissingIndex)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);

    const char* errMsg = mstGetLastErrorString(mstDevice);
    EXPECT_NE(errMsg, nullptr);
    EXPECT_GT(strlen(errMsg), 0u) << "Error message should be non-empty for ICMD failure";
    printf("\nMissing required index (PAOS)   : %d - %s\n", status, errMsg);
    // The syndrome is FW-reported: mlxreg_lib appends it to the error string only when
    // non-zero, so zero is a valid outcome — record it without asserting a value.
    printf("Syndrome (missing index)        : 0x%x\n", mstGetSyndrome(mstDevice));

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkErrorHandlingTest, ErrorMissingIndexPTYS)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PTYS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_GET);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);

    const char* errMsg = mstGetLastErrorString(mstDevice);
    EXPECT_NE(errMsg, nullptr);
    EXPECT_GT(strlen(errMsg), 0u);
    printf("\nMissing required index (PTYS)   : %d - %s\n", status, errMsg);

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkErrorHandlingTest, ErrorSendSetWithoutSettingFields)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMap regMap;
    status = mstInitRegisterMap(mstDevice, "PAOS", &regMap);
    ASSERT_EQ(status, MST_SUCCESS) << mstGetLastErrorString(mstDevice);

    status = mstSendPRMRegister(mstDevice, &regMap, MST_PRM_SET);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);

    const char* errMsg = mstGetLastErrorString(mstDevice);
    EXPECT_NE(errMsg, nullptr);
    EXPECT_GT(strlen(errMsg), 0u);
    printf("\nSET without indexes (PAOS)      : %d - %s\n", status, errMsg);

    mstFreePrmRegisterMap(&regMap);
}

TEST_F(MftSdkErrorHandlingTest, ErrorInvalidAdbPath)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    EnvVarGuard envGuard("EXTERNAL_ADB_PATH", "invalid_path");

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "MGIR", &meta);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);
    EXPECT_STREQ(
      mstGetLastErrorString(mstDevice),
      "Failure in loading Adabe file. Can't open file (invalid_path) for reading: No such file or directory");

    printf("\nInvalid ADB path                : %d - %s\n", status, mstGetLastErrorString(mstDevice));

    mstFreePrmRegisterMetadata(&meta);
}

TEST_F(MftSdkErrorHandlingTest, ErrorInvalidExpandedMetadata)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterExpandedMetadata meta;
    status = mstGetRegisterExpandedMetadata(mstDevice, "XXXX", &meta);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);

    printf("\nInvalid register name (exp meta): %d - %s\n", status, mstGetLastErrorString(mstDevice));

    mstFreePrmRegisterExpandedMetadata(&meta);
}

TEST_F(MftSdkErrorHandlingTest, ErrorInvalidRegisterMetadata)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstPrmRegisterMetadata meta;
    status = mstGetRegisterMetadata(mstDevice, "XXXX", &meta);
    EXPECT_EQ(status, MST_ERROR_FAILED_TO_SEND_ACCESS_REG);
    EXPECT_STREQ(mstGetLastErrorString(mstDevice), "Can't find access register name: XXXX");

    printf("\nInvalid register name (metadata): %d - %s\n", status, mstGetLastErrorString(mstDevice));

    mstFreePrmRegisterMetadata(&meta);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
