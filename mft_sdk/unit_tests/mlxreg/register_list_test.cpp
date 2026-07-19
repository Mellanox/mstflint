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

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

class MftSdkRegisterListTest : public ::testing::Test
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

TEST_F(MftSdkRegisterListTest, ListAllRegisters)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    char** registerNamesArray;
    unsigned int numRegisters;
    status = mstShowAllPRMRegisters(mstDevice, &registerNamesArray, &numRegisters);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to show all PRM registers: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(numRegisters, 0u) << "No registers found";

    std::vector<std::string> names(registerNamesArray, registerNamesArray + numRegisters);
    std::sort(names.begin(), names.end());

    printf("\n%s\n", SECTION_REGISTER_LIST);
    printf("-------------\n");
    for (const auto& name : names)
    {
        printf("%s\n", name.c_str());
    }
    printf("%s: %u\n", FIELD_TOTAL, numRegisters);

    mstFreePRMRegisterNamesArray(registerNamesArray, numRegisters);
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
