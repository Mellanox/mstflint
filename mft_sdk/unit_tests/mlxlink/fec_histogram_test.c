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

#include <stdio.h>
#include <string.h>

int test_get_fec_histogram(MstDevice mstDevice, const char* devicePci)
{
    if (mstGetDeviceHandle(&mstDevice, devicePci) != MST_SUCCESS)
    {
        printf("Failed to get device handle for %s\n", devicePci);
        return 1;
    }

    MstFecHistogram fecHistogram;
    MST_QUERY_INIT(&fecHistogram);
    MstStatus status = mstGetFecHistogram(mstDevice, NULL, &fecHistogram);
    if (status != MST_SUCCESS)
    {
        printf("Failed to get FEC histogram, got status %d: %s\n", status, mstGetLastErrorString(mstDevice));
        mstReleaseDeviceHandle(mstDevice);
        return 1;
    }

    /* DEBUG: Print raw numeric content for debugging - uncomment when needed */
    /* printf("Raw FEC Histogram Data (numOfErrors as uint64_t hex and decimal)\n"); */
    /* printf("----------------------------------------------------------------\n"); */
    /* for (uint8_t i = 0; i < fecHistogram.numberOfBins; i++) */
    /* { */
    /*     printf("Bin %u: numOfErrors = 0x%016llx = %llu  (minRange=%u, maxRange=%u)\n", i, */
    /*            (unsigned long long int)fecHistogram.bins[i].numOfErrors, */
    /*            (unsigned long long int)fecHistogram.bins[i].numOfErrors, */
    /*            fecHistogram.bins[i].minRange, fecHistogram.bins[i].maxRange); */
    /* } */
    /* printf("\n"); */

    /* Print in mlxlink-compatible format for comparison */
    printf("%s\n", FIELD_HISTOGRAM_OF_FEC_ERRORS);
    printf("-----------------------\n");
    printf("%-35s: %-10s %s\n", "Header", "Range", "Occurrences");
    for (uint8_t i = 0; i < fecHistogram.numberOfBins; i++)
    {
        char binLabel[32];
        snprintf(binLabel, sizeof(binLabel), "Bin %u", (unsigned)i);
        const char* rangeStr = histogramBinRangeToString(fecHistogram.bins[i].minRange, fecHistogram.bins[i].maxRange);
        printf("%-35s: %-10s %llu\n", binLabel, rangeStr, (unsigned long long int)fecHistogram.bins[i].numOfErrors);
    }

    mstReleaseDeviceHandle(mstDevice);
    return 0;
}

/* Unified C binary (mft_sdk_c_so_test): the dispatcher owns main() and
 * calls this entry with argv shifted past the suite name. */
#ifdef MFT_SDK_C_UNIFIED
int fec_histogram_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* devicePci = ""; /* Example: -d 0000:81:00.1 */

    /* Parse command line for device PCI */
    if (argc > 1)
    {
        devicePci = argv[1];
    }

    MstDevice mstDevice = NULL;
    int result = test_get_fec_histogram(mstDevice, devicePci);
    return result;
}
