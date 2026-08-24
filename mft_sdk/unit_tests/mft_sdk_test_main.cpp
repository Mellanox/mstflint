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

/*
 * Unified test main for mft_sdk_test.
 * Links all GTest suites (MftSdkTelemetryTest, MftSdkFecHistogramTest, ...)
 * into a single binary.  Use --gtest_filter to select individual tests.
 *
 * Usage:
 *   mft_sdk_test -d <DEVICE>                                        # run all
 *   mft_sdk_test -d <DEVICE> -p <PORT>                             # target a specific port
 *   mft_sdk_test -d <DEVICE> --gtest_filter="*OperationalInfo*"     # op info only
 *   mft_sdk_test -d <DEVICE> --gtest_filter="*FecHistogram*"        # histogram only
 *   mft_sdk_test -d <DEVICE> --gtest_filter="*Counters*"            # counters only
 *   mft_sdk_test -d <DEVICE> --gtest_filter="*CableDDM*"            # cable DDM only
 */

#include "gtest/gtest.h"

#include <string>

__attribute__((weak)) std::string g_devicePci = "";
__attribute__((weak)) std::string g_port = "";

int main(int argc, char** argv)
{
    // Parse -d DEVICE and optional -p PORT before gtest consumes args
    for (int i = 1; i < argc - 1; i++)
    {
        if (std::string(argv[i]) == "-d")
        {
            g_devicePci = argv[i + 1];
        }
        else if (std::string(argv[i]) == "-p")
        {
            g_port = argv[i + 1];
        }
    }

    // Fallback: accept positional device arg (e.g. "0000:81:00.1")
    // for compatibility with C test runner invocation style.
    if (g_devicePci.empty() && argc > 1)
    {
        std::string firstArg = argv[1];
        if (firstArg.find(':') != std::string::npos && firstArg[0] != '-')
        {
            g_devicePci = firstArg;
        }
    }

    // Prepend 0000: if not present
    if (!g_devicePci.empty() && g_devicePci.find(':') != std::string::npos && g_devicePci.substr(0, 5) != "0000:")
    {
        g_devicePci = "0000:" + g_devicePci;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
