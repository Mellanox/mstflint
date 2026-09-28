/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */

/*
 * A stand-in for DOCA's libs/doca_mgmt -- the only consumer that reaches the
 * SDK through pkg-config, in plain C, with no rpath:
 *
 *   - keep this file .c; DOCA uses only the extern "C" surface.
 *   - <mft_sdk/mft_sdk.h> must resolve from the .pc Cflags alone, which is why
 *     the headers install nested under $(includedir)/mstflint/sdk/mft_sdk/.
 *   - the Makefile links this without -rpath on purpose; an rpath would mask
 *     the ld.so.conf.d regression this probe exists to catch.
 *
 * Exit 0 means the SDK was found, loaded and entered (any MstStatus); 1 means
 * it was reached but behaved structurally wrong.
 */

#include <stdio.h>
#include <string.h>
#include <mft_sdk/mft_sdk.h>

int main(int argc, char** argv)
{
    const char* fwctlName = (argc > 1) ? argv[1] : "fwctl0";
    MstDevice   dev = NULL;
    MstStatus   st;

    printf("include  <mft_sdk/mft_sdk.h>  resolved\n");

    st = mstGetDeviceHandleByFwctlDeviceName(&dev, fwctlName);
    printf("mstGetDeviceHandleByFwctlDeviceName(\"%s\") -> %d\n", fwctlName, (int)st);

    /* DOCA calls both error-string entry points on its failure paths, so run
     * them here rather than only asserting they exist in the symbol table. */
    {
        const char* initErr = mstGetInitErrorString();
        printf("mstGetInitErrorString()   -> %s\n", initErr ? initErr : "(null)");
    }

    if (st == MST_SUCCESS)
    {
        const char* lastErr;

        if (dev == NULL)
        {
            fprintf(stderr, "FAIL: MST_SUCCESS but the handle is NULL\n");
            return 1;
        }
        lastErr = mstGetLastErrorString(dev);
        printf("mstGetLastErrorString()   -> %s\n", lastErr ? lastErr : "(null)");
        printf("mstReleaseDeviceHandle()  -> %d\n", (int)mstReleaseDeviceHandle(dev));
        printf("RESULT: device opened -- full contract exercised\n");
        return 0;
    }

    /* No fwctl device (modules not loaded, or a non-root run) is the common
     * case; the link/load half of the contract still held. */
    printf("RESULT: SDK entered and returned status %d"
           " -- link/load contract OK, device open not exercised\n", (int)st);
    return 0;
}
