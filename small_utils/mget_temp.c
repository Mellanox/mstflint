
/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *
   - this tool print the HCA temperature
 *
 */

#include "mget_temp.h"

void print_help()
{
    printf("\n\n");
    printf("     mget_temp - Get Hardware Temperature of Mellanox Technologies LTD devices\n");
    printf("======================================================================================\n");
    printf("  Prints the current device temperature in degrees centigrade.\n");
    printf("\n");
    printf("OPTIONS:\n");
    printf("-h             : print this help message\n");
    printf("-d <dev>       : mst device name\n");
    printf("-v             : print a table of all thermal diode data\n");
    printf("--version      : display version info\n");
}

int parseAndRun(int argc, char** argv)
{
    mfile* mf;
    td_data_fw* data = NULL;
    td_fw_result_t rc = TDFW_SUCCESS;
    int diodes_read = 0;
    int print_all_termal_diode = 0;
    char* dev_name = NULL;
    char device[MAX_DEV_LEN] = {0};
    int ai;
    int i, j;

    for (ai = 1; ai < argc;)
    {
        if (strcmp(argv[ai], "-h") == 0 || strcmp(argv[ai], "--help") == 0)
        {
            print_help();
            exit(0);
        }
        else if (strcmp(argv[ai], "-d") == 0)
        {
            if (ai + 1 >= argc)
            {
                break;
            }
            dev_name = argv[ai + 1];
            ai += 2;
        }
        else if (strcmp(argv[ai], "-v") == 0)
        {
            print_all_termal_diode = 1;
            ai += 1;
        }
        else if (strcmp(argv[ai], "--version") == 0)
        {
            print_version_string("mget_temp", "");
            exit(0);
        }
        else
        {
            printf("Usage : mget_temp -d <device> [OPTIONS]\n");
            exit(1);
        }
    }

    if (argc == 1 || !dev_name)
    {
        printf("Usage : mget_temp -d <device> [OPTIONS]\n");
        exit(1);
    }

    strncpy(device, dev_name, MAX_DEV_LEN - 1);
    mf = mopen_adv(dev_name, (MType)(MST_DEFAULT | MST_LINKX_CHIP));
    if (!mf || (mf->tp == MST_LINKX_CHIP))
    {
        if (mf)
        {
            mclose(mf);
        }
        perror("mopen");
        exit(1);
    }
    if (dm_is_livefish_mode(mf))
    {
        printf("-E- mget_temp over device in livefish mode is not supported.\n");
        mclose(mf);
        exit(1);
    }

    /* read and copy out diode data*/

    rc = td_fw_read_diodes(mf, TD_FW_ALL_DIODES, &diodes_read, &data);
    if (rc != TDFW_SUCCESS || !data)
    {
        fprintf(stderr, "Thermal diode read failed (%s)\n", td_fw_err_str);
        td_fw_release_data(data);
        mclose(mf);
        exit(1);
    }

    if (print_all_termal_diode)
    {
        /* verbose */

        /* header for verbose mode */
        printf("%-5s %-20s %-5s %-15s %-10s", "#", "name", "T/V", "temp", "thresh");
        printf("\n");

        for (i = 0, j = 1; i < diodes_read; i++)
        {
            printf("%-5d %-20s %-5s ", j++, data[i].diode_name, "T");
            (data[i].temp != TD_FW_INVALID_TEMP) /* print temp */
                ?
                printf("%-15.1d ", data[i].temp) :
                printf("%-15s ", "n\a");
            (data[i].hw_threshold != TD_FW_INVALID_TEMP) ?
                printf("%-10.3d ",
                        data[i].hw_threshold) /* print threshold (taken from common struct)*/
                :
                printf("%-10s ", "n\a");

            printf("\n");
        }
    }
    else
    {
        /* non-verbose */
        int max_temp = -10000; /* if anything below this is a valid measurement we're in trouble... */
        for (i = 0; i < diodes_read; i++)
        { /* find maximum temperature */
            /* check if its temperature is greater than the maximum encountered up to now */
            if (data[i].temp != TD_FW_INVALID_TEMP && data[i].temp > max_temp)
            {
                max_temp = data[i].temp;
            }
        }
        PRINT_FINAL_TEMP(max_temp)
    }

    td_fw_release_data(data);
    mclose(mf);
    return 0;
}

int main(int argc, char** argv)
{
    return parseAndRun(argc, argv);
}
