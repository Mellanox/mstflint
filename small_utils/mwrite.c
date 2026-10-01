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
 *  mwrite.c - CR Space write access
 *
 */
#include "mtcr.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(const char* n)
{
    printf("%s <device> <addr> <value>\n", n);
    exit(1);
}

/* Parse a 32-bit unsigned number. Returns 0 on success, 1 if the string is not a number, 2 if it is out of range. */
static int parse_u32(const char* str, unsigned int* out)
{
    char* endp;
    unsigned long long parsed;

    errno = 0;
    parsed = strtoull(str, &endp, 0);
    if (endp == str || *endp)
    {
        return 1;
    }
    if (errno == ERANGE || parsed > UINT_MAX)
    {
        return 2;
    }
    *out = (unsigned int)parsed;
    return 0;
}

int main(int ac, char* av[])
{
    int rc = 0;
    unsigned int addr, val;
    mfile* mf;

    if (ac != 4)
    {
        usage(av[0]);
    }

    switch (parse_u32(av[2], &addr))
    {
        case 1:
            usage(av[0]);
            break;
        case 2:
            fprintf(stderr, "-E- Address is out of the range\n");
            exit(1);
    }
    switch (parse_u32(av[3], &val))
    {
        case 1:
            usage(av[0]);
            break;
        case 2:
            fprintf(stderr, "-E- Value is out of the range\n");
            exit(1);
    }

    mf = mopen(av[1]);
    if (!mf)
    {
        perror("mopen");
        return 1;
    }

    if ((rc = mwrite4(mf, addr, val)) < 0)
    {
        mclose(mf);
        perror("mwrite");
        return 1;
    }
    if (rc < 4)
    {
        mclose(mf);
        printf("Write only %d bytes\n", rc);
        return 1;
    }
    mclose(mf);
    return 0;
}
