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

#include <string.h>

#include "small_utils/mget_temp_lib.h"
#include "small_utils/mget_temp_sensors.h"
#include "dev_mgt/therm_fw.h"
#include "dev_mgt/tools_dev_types.h"
#include "reg_access/mcam_capabilities.h"
#include "reg_access/reg_ids.h"

#if MGET_TEMP_INVALID_TEMP != TD_FW_INVALID_TEMP
#error "MGET_TEMP_INVALID_TEMP must mirror the thermal library's TD_FW_INVALID_TEMP"
#endif

#if MGET_TEMP_MAX_ERR_LEN != TD_FW_MAX_ERR_LEN
#error "MGET_TEMP_MAX_ERR_LEN must mirror the thermal library's TD_FW_MAX_ERR_LEN"
#endif

/* Snapshot the thermal library's global error text into the caller's own buffer, as soon
 * as the failing read returns. td_fw_err_str is a process-global, so this narrows the
 * window in which another thread's failure overwrites the message rather than closing it;
 * closing it belongs to the thermal library. Handing out the pointer instead would leave
 * every caller reading that shared buffer indefinitely. */
static void copy_last_error(char* error_buffer, size_t error_buffer_size)
{
    if (!error_buffer || error_buffer_size == 0)
    {
        return;
    }
    strncpy(error_buffer, td_fw_err_str, error_buffer_size - 1);
    error_buffer[error_buffer_size - 1] = '\0';
}

int mget_temp_read_cpo_module_sensors(mfile* mf,
                                      td_temp_unit_t requested_unit,
                                      td_data_mmta** mmta_data_p,
                                      bool* cpo_supported,
                                      bool no_modules)
{
    int mmta_sensors_read = 0;

    reg_access_status_t rc = isRegisterValidAccordingToMcamReg(mf, REG_ID_MMTA, cpo_supported);
    *cpo_supported = *cpo_supported && (rc == ME_OK);

    // MMTA module sensors (ELS/OE/TEC) only map to real hardware on CPO systems. On non-CPO
    // devices MMTA is still MCAM-valid and MGPIR still reports a module count, so probing every
    // index would emit phantom "modN_ELS" rows. Gate on MGIR.cpo_indication; dm_is_cpo leaves
    // cpo_indication untouched on failure, so an unreadable MGIR is treated as non-CPO.
    if (*cpo_supported)
    {
        u_int8_t cpo_indication = 0;
        dm_is_cpo(mf, &cpo_indication);
        *cpo_supported = (cpo_indication == 1);
    }

    if (*cpo_supported && !no_modules)
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

int mget_temp_include_mmta_in_max_temp(td_data_mmta* mmta_data, int mmta_sensors_read, int current_max)
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

int mget_temp_resolve_device(mfile* mf, int* temperature)
{
    dm_dev_id_t dev_id = DeviceUnknown;
    u_int32_t hw_dev_id = 0;
    u_int32_t hw_rev_id = 0;

    if (!mf || !temperature)
    {
        return MGET_TEMP_ERR_INVALID_ARGUMENT;
    }

    if (dm_is_livefish_mode(mf))
    {
        return MGET_TEMP_ERR_LIVEFISH;
    }

    if (!dm_get_device_id(mf, &dev_id, &hw_dev_id, &hw_rev_id) && dm_is_gpu(dev_id))
    {
        return MGET_TEMP_ERR_GPU_ASIC;
    }

    return MGET_TEMP_DEVICE_HAS_SENSORS;
}

int mget_temp_read_sensors_max_unit(mfile* mf,
                                    td_temp_unit_t requested_unit,
                                    bool no_modules,
                                    int* temperature,
                                    char* error_buffer,
                                    size_t error_buffer_size)
{
    td_data_fw* data = NULL;
    td_data_mmta* mmta_data = NULL;
    int diodes_read = 0;
    int mmta_sensors_read = 0;
    bool cpo_supported = false;
    int max_temp = TD_FW_INVALID_TEMP;
    int i;

    if (!mf || !temperature)
    {
        return MGET_TEMP_ERR_INVALID_ARGUMENT;
    }

    if (td_fw_read_diodes(mf, TD_FW_ALL_DIODES, &diodes_read, &data) != TDFW_SUCCESS || !data)
    {
        copy_last_error(error_buffer, error_buffer_size);
        return MGET_TEMP_ERR_DIODE_READ;
    }

    mmta_sensors_read = mget_temp_read_cpo_module_sensors(mf, requested_unit, &mmta_data, &cpo_supported, no_modules);
    if (mmta_sensors_read == -1)
    {
        copy_last_error(error_buffer, error_buffer_size);
        td_fw_release_data(data);
        return MGET_TEMP_ERR_MODULE_READ;
    }

    for (i = 0; i < diodes_read; i++)
    {
        if (data[i].temp > TD_FW_INVALID_TEMP && data[i].temp > max_temp)
        {
            max_temp = data[i].temp;
        }
    }
    max_temp = mget_temp_include_mmta_in_max_temp(mmta_data, mmta_sensors_read, max_temp);

    td_fw_release_mmta_data(mmta_data);
    td_fw_release_data(data);

    *temperature = max_temp;
    return MGET_TEMP_OK;
}

int mget_temp_read_sensors_max(mfile* mf,
                               bool no_modules,
                               int* temperature,
                               char* error_buffer,
                               size_t error_buffer_size)
{
    return mget_temp_read_sensors_max_unit(mf, TD_FW_TEMP_UNIT_0_125C, no_modules, temperature, error_buffer,
                                           error_buffer_size);
}

int mget_temp_read_max_temperature(mfile* mf,
                                   bool no_modules,
                                   int* temperature,
                                   char* error_buffer,
                                   size_t error_buffer_size)
{
    int rc = mget_temp_resolve_device(mf, temperature);

    if (rc != MGET_TEMP_DEVICE_HAS_SENSORS)
    {
        return rc;
    }
    return mget_temp_read_sensors_max(mf, no_modules, temperature, error_buffer, error_buffer_size);
}
