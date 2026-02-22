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
 *
 */
#include <stdbool.h>

#include <crdump.h>
#include <dev_mgt/tools_dev_types.h>
#include <common/tools_version.h>
#include <common/bit_slice.h>
#include <mft_utils/mft_sig_handler.h>

#define CAUSE_FLAG "--cause"
#define MAX_DEV_LEN 512

#ifndef MSTDUMP_NAME
#define MSTDUMP_NAME "mstdump"
#endif

#ifndef DEV_EXAMPLE
#define DEV_EXAMPLE "/dev/mst/mt4099_pci_cr0"
#endif

// string explaining the cmd-line structure
char correct_cmdline[] = "   Mellanox " MSTDUMP_NAME " utility, dumps device internal configuration data\n\
   Usage: " MSTDUMP_NAME " [-full] <device> [i2c-slave] [-v[ersion] [-h[elp]]]\n\n\
   -full              :  Dump more expanded list of addresses\n\
                         Note : be careful when using this flag, None safe addresses might be read.\n\
   -v | --version     :  Display version info\n\
   -h | --help        :  Print this help message\n\
   i2c_secondary          :   I2C slave [0-127]\n\
   Example :\n\
            " MSTDUMP_NAME " " DEV_EXAMPLE "\n";

void print_dword(crd_dword_t* dword)
{
    printf("0x%8.8x 0x%8.8x\n", dword->addr, dword->data);
}

bool check_device_name(const char* device)
{
    if (device == NULL)
    {
        return false;
    }

    unsigned int dev_len = strlen(device);
    if (dev_len == 0 || dev_len > MAX_DEV_LEN)
    {
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    mft_signal_set_msg((char*)"\nInterrupted, Exiting...\n");
    mft_signal_set_handling(1);
    int i;
    mfile* mf;
    int rc;
    int full = 0;
    int cause_addr = -1, cause_off = -1;
    crd_ctxt_t* context = NULL;
    u_int32_t arr_size = 0;
    char* endptr;
    u_int8_t new_i2c_secondary = 0;
    char device[MAX_DEV_LEN] = {0};
#if defined(__linux__) || defined(__FreeBSD__)
    if (geteuid() != 0)
    {
        printf("-E- Permission denied: User is not root\n");
        return 1;
    }
#endif

    if (argc < 2 || argc > 4)
    {
        fprintf(stderr, "%s", correct_cmdline);
        return 2;
    }

    for (i = 1; i < argc; ++i)
    {
        /* check position-independent flags */
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help") || !strcmp(argv[i], "--help"))
        {
            fprintf(stdout, "%s", correct_cmdline);
            exit(0);
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "-version") || !strcmp(argv[i], "--version"))
        {
            print_version_string(MSTDUMP_NAME, "");
            exit(0);
        }
        else if (!strncmp(argv[i], CAUSE_FLAG, strlen(CAUSE_FLAG)))
        {
            if (sscanf(argv[i], CAUSE_FLAG "=%i.%d", &cause_addr, &cause_off) != 2)
            {
                fprintf(stderr, "Invalid parameters to " CAUSE_FLAG " flag\n");
                fprintf(stdout, "%s", correct_cmdline);
                exit(1);
            }
            if (cause_addr < 0 || cause_off < 0)
            {
                fprintf(stderr, "Parameters to " CAUSE_FLAG " flag must be non-negative values\n");
                exit(1);
            }
        }
    }

    i = 1; // i points to the current command line argument

    if (i < argc && !strcasecmp(argv[i], "-full"))
    {
        full = 1;
        ++i;
    }
    if (i >= argc)
    {
        fprintf(stderr, "Device is not specified in command line. Exiting.\n");
        fprintf(stdout, "%s", correct_cmdline);
        return 1;
    }
    strncpy(device, argv[i], MAX_DEV_LEN - 1);
    if (!check_device_name(device))
    {
        fprintf(stderr, "Invalid device format, %s. Exiting\n", device);
        return 1;
    }
    if (!(mf = mopen_adv((const char*)device, (MType)(MST_DEFAULT | MST_CABLE))))
    {
        fprintf(stderr, "Unable to open device %s. Exiting.\n", argv[i]);
        return 1;
    }
    ++i; // move past the device parameter

    if (i < argc && !strncmp(argv[i], CAUSE_FLAG, strlen(CAUSE_FLAG)))
    {
        i++;
    }
    if (i < argc)
    {
        new_i2c_secondary = (u_int8_t)strtoul(argv[i], &endptr, 0);
        if (*endptr || !*argv[i])
        {
            fprintf(stderr, "Invalid i2c-slave %s\n", argv[i]);
            mclose(mf);
            return 1;
        }
        mset_i2c_secondary(mf, new_i2c_secondary);
        i++;
    }
    if (i < argc)
    {
        if (i < argc)
        {
            fprintf(stderr, "Unknown argument: %s.\n", argv[i]);
            fprintf(stderr, "%s", correct_cmdline);
            mclose(mf);
            return 1;
        }
    }
    rc = CRD_OK;
    rc = crd_init(&context, mf, full, cause_addr, cause_off, NULL, "");
    if (rc)
    {
        mclose(mf);
        goto error;
    }

    // printf("Number of blocks : 0x%d\n",(context)->block_count);

    rc = crd_get_dword_num(context, &arr_size);
    if (rc)
    {
        crd_free(context);
        mclose(mf);
        goto error;
    }

    rc = crd_dump_data(context, NULL, print_dword);
    if (rc)
    {
        crd_free(context);
        mclose(mf);
        goto error;
    }
    mft_restore_and_raise();
    crd_free(context);
    mclose(mf);
    return 0;

error:
    if (rc != CRD_SIGNAL_INTERRUPTED)
    {
        printf("-E- %s\n", crd_err_str(rc));
    }
    return rc;
}
