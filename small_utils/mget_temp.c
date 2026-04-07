
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
#include "reg_access/mcam_capabilities.h"
#include "reg_access/reg_ids.h"

void print_help()
{
    printf("\n\n");
    printf("     mstmget_temp - Get Hardware Temperature of Mellanox Technologies LTD devices\n");
    printf("======================================================================================\n");
    printf("  Prints the current device temperature in degrees centigrade.\n");
    printf("\n");
    printf("OPTIONS:\n");
    printf("-h             : print this help message\n");
    printf("-d <dev>       : mst device name\n");
    printf("-v             : print a table of all thermal diode data\n");
    printf("--precision <unit> : temperature display resolution for module sensors\n");
    printf("                     Valid values: 0: 0.125°C (default) | 1: 1/256°C (high precision)\n");
    printf("--no-modules   : do not read or display module sensors\n");
    printf("--version      : display version info\n");
}

/* MMTA helper functions */
int read_mmta_sensors(mfile* mf,
                      td_temp_unit_t requested_unit,
                      td_data_mmta** mmta_data_p,
                      bool* mmta_supported,
                      bool no_modules)
{
    int mmta_sensors_read = 0;

    reg_access_status_t rc = isRegisterValidAccordingToMcamReg(mf, REG_ID_MMTA, mmta_supported);
    *mmta_supported = *mmta_supported && (rc == ME_OK);

    if (*mmta_supported && !no_modules)
    {
        td_fw_result_t td_rc = td_fw_read_module_sensors(mf, requested_unit, &mmta_sensors_read, mmta_data_p);
        if (td_rc != TDFW_SUCCESS)
        {
            return -1;
        }
    }
    else
    {
        *mmta_data_p = NULL;
    }

    return mmta_sensors_read;
}

void print_temperature_table_header(bool mmta_supported)
{
    if (mmta_supported)
    {
        printf("%-5s %-20s %-20s %-15s %-15s %-15s %-15s", "#", "name", "type", "unit", "temp", "max", "thresh");
    }
    else
    {
        printf("%-5s %-20s %-5s %-15s %-10s", "#", "name", "T/V", "temp", "thresh");
    }
}

void display_mmta_sensor_verbose(td_data_mmta* sensor, int decimals, int* row_num)
{
    int d = (sensor->type == TD_MMTA_SENSOR_TEC) ? 2 : decimals;
    printf("%-5d %-20s %-20s %-15s %-15.*f %-15.*f %-15.*f", (*row_num)++, sensor->base.diode_name, "Module",
           sensor->unit_str, d, sensor->base.temp, d, sensor->base.max_temp, d, sensor->base.hw_threshold);
}

int include_mmta_in_max_temp(td_data_mmta* mmta_data, int mmta_sensors_read, int current_max)
{
    int max_temp = current_max;

    for (int i = 0; i < mmta_sensors_read; i++)
    {
        if (mmta_data[i].type != TD_MMTA_SENSOR_TEC && (int)mmta_data[i].base.temp > max_temp)
        {
            max_temp = (int)mmta_data[i].base.temp;
        }
    }

    return max_temp;
}

void display_internal_sensors_verbose(td_data_fw* data, bool mmta_supported, int* row_num)
{
    if (mmta_supported)
    {
        printf("%-5d %-20s %-20s %-15s ", (*row_num)++, data->diode_name, "Internal", "1°C");
        (data->temp > TD_FW_INVALID_TEMP) ? printf("%-15.0f ", data->temp) : printf("%-15s ", "n/a");
        (data->max_temp > TD_FW_INVALID_TEMP) ? printf("%-15.0f ", data->max_temp) : printf("%-15s ", "n/a");
        (data->hw_threshold > TD_FW_INVALID_TEMP) ? printf("%-15.0f ", data->hw_threshold) : printf("%-15s ", "n/a");
    }
    else
    {
        printf("%-5d %-20s %-5s ", (*row_num)++, data->diode_name, "T");
        (data->temp > TD_FW_INVALID_TEMP) ? printf("%-15.0f ", data->temp) : printf("%-15s ", "n/a");
        (data->hw_threshold > TD_FW_INVALID_TEMP) ? printf("%-10.0f ", data->hw_threshold) : printf("%-10s ", "n/a");
    }
}

int parseAndRun(int argc, char** argv)
{
    mfile* mf;
    td_data_fw* data = NULL;
    td_data_mmta* mmta_data = NULL;
    int mmta_modules_read = 0;
    bool mmta_supported = false;
    bool no_modules = false;
    td_fw_result_t rc = TDFW_SUCCESS;
    int diodes_read = 0;
    int print_all_termal_diode = 0;
    char* precision_str = NULL;
    td_temp_unit_t requested_unit = TD_FW_TEMP_UNIT_0_125C;
    char* dev_name = NULL;
    char device[MAX_DEV_LEN] = {0};
    int ai;
    int i, j;
    dm_dev_id_t dev_id = DeviceUnknown;
    u_int32_t hw_dev_id = 0;
    u_int32_t hw_rev_id = 0;

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
        else if (strcmp(argv[ai], "--precision") == 0)
        {
            if (ai + 1 >= argc)
            {
                printf("Usage : mstmget_temp [OPTIONS] --precision <unit>\n");
                printf("Valid units: 0, 1, 0.125, 1/256\n");
                exit(1);
            }
            precision_str = argv[ai + 1];
            if (strcmp(precision_str, "0") == 0 || strcmp(precision_str, "0.125") == 0)
            {
                requested_unit = TD_FW_TEMP_UNIT_0_125C;
            }
            else if (strcmp(precision_str, "1") == 0 || strcmp(precision_str, "1/256") == 0)
            {
                requested_unit = TD_FW_TEMP_UNIT_1_256C;
            }
            else
            {
                printf("-E- Invalid precision value: %s\n", precision_str);
                printf("Valid values: 0, 1, 0.125, 1/256\n");
                exit(1);
            }
            ai += 2;
        }
        else if (strcmp(argv[ai], "--no-modules") == 0)
        {
            no_modules = true;
            ai += 1;
        }
        else if (strcmp(argv[ai], "--version") == 0)
        {
            print_version_string("mstmget_temp", "");
            exit(0);
        }
        else
        {
            printf("Usage : mstmget_temp -d <device> [OPTIONS]\n");
            exit(1);
        }
    }

    if (argc == 1 || !dev_name)
    {
        printf("Usage : mstmget_temp -d <device> [OPTIONS]\n");
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
        printf("-E- mstmget_temp over device in livefish mode is not supported.\n");
        mclose(mf);
        exit(1);
    }

    if (!dm_get_device_id(mf, &dev_id, &hw_dev_id, &hw_rev_id))
    {
        if (dm_is_gpu(dev_id))
        {
            printf("-E- mstmget_temp over GPU is not supported.\n");
            mclose(mf);
            exit(1);
        }
    }

    /* read and copy out diode data*/

    rc = td_fw_read_diodes(mf, TD_FW_ALL_DIODES, &diodes_read, &data);
    if (rc != TDFW_SUCCESS || !data)
    {
        fprintf(stderr, "Thermal diode read failed (%s)\n", td_fw_err_str);
        mclose(mf);
        exit(1);
    }

    mmta_modules_read = read_mmta_sensors(mf, requested_unit, &mmta_data, &mmta_supported, no_modules);
    if (mmta_modules_read == -1)
    {
        fprintf(stderr, "Failed to read MMTA module sensors (%s)\n", td_fw_err_str);
        mclose(mf);
        exit(1);
    }

    if (print_all_termal_diode)
    {
        /* verbose */

        /* header for verbose mode - extended format when MMTA supported */
        print_temperature_table_header(mmta_supported);
        printf("\n");

        for (i = 0, j = 1; i < diodes_read; i++)
        {
            display_internal_sensors_verbose(&data[i], mmta_supported, &j);
            printf("\n");
        }

        for (i = 0; i < mmta_modules_read; i++)
        {
            int decimals = (mmta_data[i].temp_unit == TD_FW_TEMP_UNIT_1_256C) ? 4 : 1;
            display_mmta_sensor_verbose(&mmta_data[i], decimals, &j);
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

        max_temp = include_mmta_in_max_temp(mmta_data, mmta_modules_read, max_temp);

        PRINT_FINAL_TEMP(max_temp)
    }

    td_fw_release_mmta_data(mmta_data);
    td_fw_release_data(data);
    mclose(mf);
    return 0;
}

int main(int argc, char** argv)
{
    return parseAndRun(argc, argv);
}
