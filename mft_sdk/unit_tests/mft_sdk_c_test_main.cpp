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
 * Unified C test driver (mft_sdk_c_so_test) — the plain-C counterpart of
 * mft_sdk_test_main.cpp: one dynamically-linked binary hosting every
 * per-suite C test.  Each <x>_test.c renames its main() to <x>_test_main()
 * under MFT_SDK_C_UNIFIED; this driver selects the suite from argv[1] and
 * shifts argv so the suite still sees the optional device BDF at its
 * argv[1].  The SDK is resolved from libmft_sdk.so.1 at runtime, exactly
 * like the gtest harness.
 *
 * Usage:
 *   mft_sdk_c_so_test <suite> [BDF]
 *   mft_sdk_c_so_test register_access 0000:21:00.0
 */

#include <cstdio>
#include <cstring>
#include <string>

// test_utils.cpp (built with MFT_SDK_SO_UNIFIED) leaves these to the main TU.
__attribute__((weak)) std::string g_devicePci = "";
__attribute__((weak)) std::string g_port = "";

extern "C"
{
    int cable_ddm_test_main(int argc, char** argv);
    int counters_test_main(int argc, char** argv);
    int fec_histogram_test_main(int argc, char** argv);
    int module_info_test_main(int argc, char** argv);
    int op_info_test_main(int argc, char** argv);
    int error_handling_test_main(int argc, char** argv);
    int full_path_test_main(int argc, char** argv);
    int metadata_test_main(int argc, char** argv);
    int register_access_test_main(int argc, char** argv);
    int register_list_test_main(int argc, char** argv);
}

struct CSuite
{
    const char* name;
    int (*entry)(int, char**);
};

static const CSuite SUITES[] = {
    {"cable_ddm", cable_ddm_test_main},
    {"counters", counters_test_main},
    {"fec_histogram", fec_histogram_test_main},
    {"module_info", module_info_test_main},
    {"op_info", op_info_test_main},
    {"error_handling", error_handling_test_main},
    {"full_path", full_path_test_main},
    {"metadata", metadata_test_main},
    {"register_access", register_access_test_main},
    {"register_list", register_list_test_main},
};

static void printUsage(const char* prog)
{
    fprintf(stderr, "Usage: %s <suite> [BDF]\nSuites:\n", prog);
    for (size_t i = 0; i < sizeof(SUITES) / sizeof(SUITES[0]); i++)
    {
        fprintf(stderr, "  %s\n", SUITES[i].name);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return 2;
    }
    for (size_t i = 0; i < sizeof(SUITES) / sizeof(SUITES[0]); i++)
    {
        if (strcmp(argv[1], SUITES[i].name) == 0)
        {
            return SUITES[i].entry(argc - 1, argv + 1);
        }
    }
    fprintf(stderr, "Unknown suite '%s'\n", argv[1]);
    printUsage(argv[0]);
    return 2;
}
