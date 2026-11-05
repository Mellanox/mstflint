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
#include "resource_dump_fields.h"

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace
{
std::string applicability(bool supported, bool mandatory)
{
    if (!supported)
    {
        return RD_APPLICABILITY_NA;
    }
    return mandatory ? RD_APPLICABILITY_MANDATORY : RD_APPLICABILITY_OPTIONAL;
}

// Renders the special-value column the way resourcedump's menu table does.
std::string specialValues(bool supportsAll, bool supportsActive)
{
    std::string values;
    if (supportsAll)
    {
        values = RD_SPECIAL_ALL;
    }
    if (supportsActive)
    {
        if (!values.empty())
        {
            values += RD_SPECIAL_SEPARATOR;
        }
        values += RD_SPECIAL_ACTIVE;
    }
    return values.empty() ? RD_SPECIAL_NA : values;
}

// The names are raw device bytes with interior NULs, so they travel to the runner as hex.
std::string nameHex(const char* name)
{
    std::ostringstream hex;

    hex << std::hex << std::setfill('0');
    for (int i = 0; i < MST_RESOURCE_DUMP_NAME_LENGTH; i++)
    {
        hex << std::setw(2) << (unsigned int)(unsigned char)name[i];
    }
    return hex.str();
}

void printRecord(const MstResourceMenuRecord& record)
{
    printf("%s: 0x%x (%s)\n", RD_FIELD_SEGMENT_TYPE, record.segmentType, nameHex(record.segmentName).c_str());
    printf("  %s: %s %s=%s\n",
           RD_FIELD_INDEX1,
           applicability(record.supportIndex1, record.mustHaveIndex1).c_str(),
           RD_FIELD_NAME,
           nameHex(record.index1Name).c_str());
    printf("  %s: %s %s=%s\n",
           RD_FIELD_NUM_OF_OBJ1,
           applicability(record.supportNumOfObj1, record.mustHaveNumOfObj1).c_str(),
           RD_FIELD_SPECIAL,
           specialValues(record.numOfObj1SupportsAll, record.numOfObj1SupportsActive).c_str());
    printf("  %s: %s %s=%s\n",
           RD_FIELD_INDEX2,
           applicability(record.supportIndex2, record.mustHaveIndex2).c_str(),
           RD_FIELD_NAME,
           nameHex(record.index2Name).c_str());
    printf("  %s: %s %s=%s\n",
           RD_FIELD_NUM_OF_OBJ2,
           applicability(record.supportNumOfObj2, record.mustHaveNumOfObj2).c_str(),
           RD_FIELD_SPECIAL,
           specialValues(record.numOfObj2SupportsAll, record.numOfObj2SupportsActive).c_str());
}
} // namespace

class MftSdkResourceMenuTest : public ::testing::Test
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

TEST_F(MftSdkResourceMenuTest, GetResourceMenu)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstResourceMenu menu;
    status = mstGetResourceMenu(mstDevice, MST_RESOURCE_DUMP_ENDIANNESS_NATIVE, &menu);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get the resource menu: " << mstGetLastErrorString(mstDevice);
    ASSERT_GT(menu.numberOfRecords, 0u) << "The resource menu is empty";
    ASSERT_NE(menu.records, nullptr) << "The resource menu records were not allocated";

    std::vector<MstResourceMenuRecord> records(menu.records, menu.records + menu.numberOfRecords);
    std::sort(records.begin(), records.end(),
              [](const MstResourceMenuRecord& a, const MstResourceMenuRecord& b)
              { return a.segmentType < b.segmentType; });

    printf("\n%s\n", RD_SECTION_RESOURCE_MENU);
    printf("-------------\n");
    for (const auto& record : records)
    {
        EXPECT_NE(std::string(record.segmentName, MST_RESOURCE_DUMP_NAME_LENGTH),
                  std::string(MST_RESOURCE_DUMP_NAME_LENGTH, '\0'))
          << "Resource 0x" << std::hex << record.segmentType << " has no name";
        // An index the device does not accept cannot be mandatory.
        EXPECT_FALSE(record.mustHaveIndex1 && !record.supportIndex1) << "index1 mandatory but unsupported";
        EXPECT_FALSE(record.mustHaveIndex2 && !record.supportIndex2) << "index2 mandatory but unsupported";
        EXPECT_FALSE(record.mustHaveNumOfObj1 && !record.supportNumOfObj1) << "num_of_obj1 mandatory but unsupported";
        EXPECT_FALSE(record.mustHaveNumOfObj2 && !record.supportNumOfObj2) << "num_of_obj2 mandatory but unsupported";
        printRecord(record);
    }
    printf("%s: %u\n", RD_FIELD_TOTAL, menu.numberOfRecords);

    ASSERT_EQ(mstFreeResourceMenu(&menu), MST_SUCCESS) << "Failed to free the resource menu";
    EXPECT_EQ(menu.records, nullptr) << "Freeing the resource menu should clear it";
    EXPECT_EQ(menu.numberOfRecords, 0u) << "Freeing the resource menu should clear its count";
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
