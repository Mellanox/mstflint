/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id$
 *
 */

#include "mft_sdk/mft_sdk.h"
#include "test_utils.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <string>
#include <vector>

// Test fixture for FEC histogram tests
class MftSdkFecHistogramTest : public ::testing::Test
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

TEST_F(MftSdkFecHistogramTest, GetFecHistogram)
{
    MstStatus status = mstGetDeviceHandle(&mstDevice, g_devicePci.c_str());
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get device handle for " << g_devicePci;

    MstFecHistogram fecHistogram;
    MST_QUERY_INIT(&fecHistogram);
    MstTelemetryContext context = makeTelemetryContext();
    status = mstGetFecHistogram(mstDevice, &context, &fecHistogram);
    ASSERT_EQ(status, MST_SUCCESS) << "Failed to get FEC histogram: " << mstGetLastErrorString(mstDevice);

    // Print in mlxlink-compatible format for comparison BEFORE assertions,
    // so the comparison script can parse whatever data is available.
    printf("\n%s\n", FIELD_HISTOGRAM_OF_FEC_ERRORS);
    printf("-----------------------\n");
    printf("%-35s: %-10s %s\n", "Header", "Range", "Occurrences");
    for (uint8_t i = 0; i < fecHistogram.numberOfBins; i++)
    {
        char binLabel[32];
        snprintf(binLabel, sizeof(binLabel), "Bin %u", (unsigned)i);
        std::string rangeStr = histogramBinRangeToString(fecHistogram.bins[i].minRange, fecHistogram.bins[i].maxRange);
        printf("%-35s: %-10s %llu\n", binLabel, rangeStr.c_str(),
               static_cast<unsigned long long>(fecHistogram.bins[i].numOfErrors));
    }

    ASSERT_GT(fecHistogram.numberOfBins, (uint8_t)0) << "Number of bins is not greater than 0";

    for (uint8_t i = 0; i < fecHistogram.numberOfBins; i++)
    {
        EXPECT_GE(fecHistogram.bins[i].maxRange, fecHistogram.bins[i].minRange)
          << "Bin " << i << ": maxRange < minRange";
    }
}

#ifndef MFT_SDK_SO_UNIFIED
int main(int argc, char** argv)
{
    parseDevicePciArg(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
