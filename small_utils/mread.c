/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 *  mread.c - CR Space read access
 *
 */

#include "mtcr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(const char* n)
{
    printf("%s <device> <addr>\n", n);
    exit(1);
}

int main(int ac, char* av[])
{
    char* endp;
    int rc = 0;
    unsigned int addr, val;
    mfile* mf;

    if (ac != 3)
    {
        usage(av[0]);
    }

    addr = strtoul(av[2], &endp, 0);
    if (*endp)
    {
        usage(av[0]);
    }

    mf = mopen(av[1]);
    if (!mf)
    {
        perror("mopen");
        return 1;
    }

    if ((rc = mread4(mf, addr, &val)) < 0)
    {
        perror("mread");
        mclose(mf);
        return 1;
    }
    if (rc < 4)
    {
        mclose(mf);
        printf("Read only %d bytes\n", rc);
        return 1;
    }

    mclose(mf);
    printf("Read 0x%08x:0x%08x\n", addr, val);
    return rc;
}
