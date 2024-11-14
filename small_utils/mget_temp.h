/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MGET_TEMP_H
#define MGET_TEMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "common/tools_version.h"
#include "dev_mgt/tools_dev_types.h"
#include <mtcr.h>
#include "dev_mgt/therm_fw.h"
#include "common/tools_time.h"

#define SEC 1000 // Number of milliseconds in one second
#define MAX_DEV_LEN 512
/* Threshold for error between value calculated with fuses and one calculated without,
   where any delta greater than this threshold is considered suspect */
#define FUSE_ERROR_THRESHOLD 0.1

#define f_min(x, y) (((x) < (y)) ? (x) : (y))
#define f_max(x, y) (((x) < (y)) ? (y) : (x))

#define MGET_TEMP_DEBUG(...)                   \
    do                                         \
    {                                          \
        if (getenv("MGET_TEMP_DEBUG") != NULL) \
        {                                      \
            fprintf(stderr, __VA_ARGS__);      \
        }                                      \
    } while (0)

#define PRINT_FINAL_TEMP(temp)                                                                  \
    if (temp == -1000)                                                                          \
    {                                                                                           \
        printf("-I- No valid temperature were measured. please check device configuration.\n"); \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        printf("%-15.1d\n", temp);                                                              \
    }

int parseAndRun(int argc, char** argv);

#endif /* MGET_TEMP_H */