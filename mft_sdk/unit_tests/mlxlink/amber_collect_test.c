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

#include "amber_collect_test_common.h"

#include <stdlib.h>

/*
 * Unified C binary invocation:
 *   mft_sdk_c_so_test amber_collect <BDF> [PORT]
 */
#ifdef MFT_SDK_C_UNIFIED
int amber_collect_test_main(int argc, char** argv)
#else
int main(int argc, char** argv)
#endif
{
    const char* deviceName = argc > 1 ? argv[1] : "";
    const char* portName = argc > 2 ? argv[2] : "";

    return amberTestRun(deviceName, portName, 0);
}

/*
 * Unified C binary invocation:
 *   mft_sdk_c_so_test amber_sheet_select <BDF> [PORT] [SHEET_ID]
 * SHEET_ID defaults to 1 (GENERAL). Only reachable through the unified dispatcher -- there is
 * no standalone binary for this scenario, unlike amber_collect above.
 */
#ifdef MFT_SDK_C_UNIFIED
int amber_sheet_select_test_main(int argc, char** argv)
{
    const char* deviceName = argc > 1 ? argv[1] : "";
    const char* portName = argc > 2 ? argv[2] : "";
    unsigned int sheetId = argc > 3 ? (unsigned int)atoi(argv[3]) : 1u;

    return amberSheetSelectTestRun(deviceName, portName, sheetId);
}
#endif
