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

#include "tools_layouts/reg_access_hca_layouts.h"
#include "tools_layouts/reg_access_switch_layouts.h"
#include "reg_access/reg_access.h"
#include "therm_fw.h"
#include "tools_dev_types.h"

#define SKIP_INLINE_METHODS

// #define DEBUG

#ifdef DEBUG
#define DPRINTF(str, ...) fprintf(stderr, "%s (%d): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define DPRINTF(...)
#endif

#define MAX_NUM_OF_DIODES 160    // To fit the max number of diodes for the new generation (16 and 7nm)
#define MAX_SENSORS_PER_MODULE 2 // ELS + OE

char td_fw_err_str[TD_FW_MAX_ERR_LEN] = "General error";

const char* _diode_idx_to_str(int diode_idx)
{
    switch (diode_idx)
    {
        case 0:
            return "iopx";

        case 1:
            return "iopl0"; // cluster4

        case 2:
            return "iopl1"; // cluster13

        case 3:
            return "lbf0";

        case 4:
            return "lbf1";

        case 5:
            return "lbr0";

        case 6:
            return "lbr1";

        case 7:
            return "lbl";

        case 8:
            return "lbm";

        case 9:
            return "yu";

        default:
            return "unkn";
    }
}

td_fw_result_t _td_fw_get_max_diode_idx(mfile* mf, int* max_diode_idx)
{
    *max_diode_idx = 0;
    reg_access_status_t rc;
    struct reg_access_hca_mtcap_ext mtcap;
    memset(&mtcap, 0, reg_access_hca_mtcap_ext_size());

    if (!max_diode_idx || !mf)
    {
        return TDFWE_INV_ARG;
    }

    // send mtcap register
    DPRINTF("sending mtcap register")
    rc = reg_access_mtcap(mf, REG_ACCESS_METHOD_GET, &mtcap);

    if (rc)
    {
        DPRINTF("reg_access failed (0x%x): %s", rc, reg_access_err2str(rc));
        *max_diode_idx = MAX_NUM_OF_DIODES;
        return TDFW_SUCCESS;
    }
    *max_diode_idx = mtcap.internal_sensor_count;
    return TDFW_SUCCESS;
}

td_fw_result_t td_fw_get_diode_cnt(mfile* mf, int* diode_cnt)
{
    int max_diode_idx;
    int i, rc;
    rc = _td_fw_get_max_diode_idx(mf, &max_diode_idx);
    if (rc)
    {
        return TDFWE_ICMD;
    }
    // update diode_cnt
    // i.e loop from 0 to diode_cnt
    *diode_cnt = 0;
    for (i = 0; i < max_diode_idx; i++)
    {
        rc = td_fw_read_diode(mf, i, NULL);
        if (rc)
        {
            if (rc == TDFWW_DIODE_IDX_NO_EXIST)
            {
                continue;
            }
            return (td_fw_result_t)rc;
        }
        (*diode_cnt)++;
    }
    return TDFW_SUCCESS;
}

/* Convert MMTA raw temperature to Celsius */
static float _mmta_temp_to_celsius(u_int16_t raw_temp, td_temp_unit_t unit)
{
    int16_t signed_temp = (int16_t)raw_temp;
    if (unit == TD_FW_TEMP_UNIT_1_256C)
    {
        return signed_temp / 256.0f;
    }
    return signed_temp * 0.125f;
}

/* Helper to populate a single MMTA sensor entry (ELS, OE, or TEC) */
static void _populate_mmta_entry(td_data_mmta* entry,
                                 int module_idx,
                                 td_mmta_sensor_type_t type,
                                 td_temp_unit_t temp_unit,
                                 float temp,
                                 float max_temp,
                                 float threshold_hi,
                                 float threshold_lo)
{
    entry->base.diode_idx = module_idx;
    entry->base.temp = temp;
    entry->base.max_temp = max_temp;
    entry->base.hw_threshold = threshold_hi;
    entry->base.threshold_hi = threshold_hi;
    entry->base.threshold_lo = threshold_lo;

    const char* type_str = (type == TD_MMTA_SENSOR_ELS) ? "ELS" : (type == TD_MMTA_SENSOR_OE) ? "OE" : "TEC";
    snprintf(entry->base.diode_name, sizeof(entry->base.diode_name), "mod%d_%s", module_idx, type_str);

    entry->type = type;
    entry->temp_unit = temp_unit;

    if (type == TD_MMTA_SENSOR_TEC)
    {
        strncpy(entry->unit_str, "1mW", sizeof(entry->unit_str));
    }
    else if (temp_unit == TD_FW_TEMP_UNIT_1_256C)
    {
        strncpy(entry->unit_str, "1/256°C", sizeof(entry->unit_str));
    }
    else
    {
        strncpy(entry->unit_str, "0.125°C", sizeof(entry->unit_str));
    }
}

td_fw_result_t
  td_fw_read_module_sensors(mfile* mf, td_temp_unit_t requested_unit, int* sensors_read, td_data_mmta** data_p)
{
    td_data_mmta* data;
    int sensor_count = 0;
    int num_modules = 0;

    if (!sensors_read || !mf || !data_p)
    {
        return TDFWE_INV_ARG;
    }

    struct reg_access_switch_mgpir_ext mgpir;
    memset(&mgpir, 0, sizeof(mgpir));
    mgpir.hw_info.slot_index = 0;

    reg_access_status_t mgpir_rc = reg_access_mgpir_switch_ext(mf, REG_ACCESS_METHOD_GET, &mgpir);
    if (mgpir_rc != ME_OK)
    {
        snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "Failed to read module count from MGPIR");
        return TDFWE_REG_ACCESS_ERR;
    }

    num_modules = mgpir.hw_info.num_of_modules;

    if (num_modules == 0)
    {
        *sensors_read = 0;
        *data_p = NULL;
        return TDFW_SUCCESS;
    }

    data = (td_data_mmta*)malloc(num_modules * 3 * sizeof(td_data_mmta));
    if (!data)
    {
        snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "Failed to allocate memory for MMTA sensors");
        return TDFWE_MEM_ALLOC_FAIL;
    }
    memset(data, 0, num_modules * 3 * sizeof(td_data_mmta));

    for (int module_idx = 0; module_idx < num_modules; module_idx++)
    {
        struct reg_access_switch_mmta_reg_ext mmta;
        reg_access_status_t rc;

        memset(&mmta, 0, sizeof(mmta));
        mmta.module = module_idx;
        mmta.module_temperature.mte = 1;
        mmta.module_tec_power.mtpe = 1;
        mmta.module_second_temperature.mte = 1;
        reg_access_mmta(mf, REG_ACCESS_METHOD_SET, &mmta);

        memset(&mmta, 0, sizeof(mmta));
        mmta.module = module_idx;

        u_int8_t temp_unit_val = (requested_unit == TD_FW_TEMP_UNIT_1_256C) ? 1 : 0;
        mmta.module_temperature.temp_unit = temp_unit_val;
        mmta.module_second_temperature.temp_unit = temp_unit_val;
        mmta.module_tec_power.temp_unit = temp_unit_val;

        rc = reg_access_mmta(mf, REG_ACCESS_METHOD_GET, &mmta);
        if (rc)
        {
            if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_RES_NOT_AVLBL)
            {
                continue;
            }
            else
            {
                snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "Failed to read MMTA for module %d: %s", module_idx,
                         reg_access_err2str(rc));
                free(data);
                *sensors_read = 0;
                *data_p = NULL;
                return TDFWE_REG_ACCESS_ERR;
            }
        }

        if (mmta.supported_measurements & MMTA_SUPPORTED_ELS_TEMP)
        {
            td_temp_unit_t els_unit =
              mmta.module_temperature.temp_unit ? TD_FW_TEMP_UNIT_1_256C : TD_FW_TEMP_UNIT_0_125C;
            float temp = _mmta_temp_to_celsius(mmta.module_temperature.temperature, els_unit);
            float max_temp = _mmta_temp_to_celsius(mmta.module_temperature.max_temperature, els_unit);
            float thresh_hi = _mmta_temp_to_celsius(mmta.module_temperature.temperature_warning_high, els_unit);
            float thresh_lo = _mmta_temp_to_celsius(mmta.module_temperature.temperature_warning_low, els_unit);

            _populate_mmta_entry(&data[sensor_count++], module_idx, TD_MMTA_SENSOR_ELS, els_unit, temp, max_temp,
                                 thresh_hi, thresh_lo);
        }

        if (mmta.supported_measurements & MMTA_SUPPORTED_OE_TEMP)
        {
            td_temp_unit_t oe_unit =
              mmta.module_second_temperature.temp_unit ? TD_FW_TEMP_UNIT_1_256C : TD_FW_TEMP_UNIT_0_125C;
            float temp = _mmta_temp_to_celsius(mmta.module_second_temperature.temperature, oe_unit);
            float max_temp = _mmta_temp_to_celsius(mmta.module_second_temperature.max_temperature, oe_unit);
            float thresh_hi = _mmta_temp_to_celsius(mmta.module_second_temperature.temperature_warning_high, oe_unit);
            float thresh_lo = _mmta_temp_to_celsius(mmta.module_second_temperature.temperature_warning_low, oe_unit);

            _populate_mmta_entry(&data[sensor_count++], module_idx, TD_MMTA_SENSOR_OE, oe_unit, temp, max_temp,
                                 thresh_hi, thresh_lo);
        }

        if (mmta.supported_measurements & MMTA_SUPPORTED_TEC_POWER)
        {
            float power = mmta.module_tec_power.tec_power;
            float max_power = mmta.module_tec_power.max_tec_power;

            td_temp_unit_t tec_unit = mmta.module_tec_power.temp_unit ? TD_FW_TEMP_UNIT_1_256C : TD_FW_TEMP_UNIT_0_125C;
            float setpoint = _mmta_temp_to_celsius(mmta.module_tec_power.set_point_temperature, tec_unit);

            _populate_mmta_entry(&data[sensor_count++], module_idx, TD_MMTA_SENSOR_TEC, tec_unit, power, max_power,
                                 setpoint, TD_FW_INVALID_TEMP);
        }
    }

    *sensors_read = sensor_count;
    *data_p = data;

    return TDFW_SUCCESS;
}

td_fw_result_t td_fw_read_diodes(mfile* mf, int diode_idx, int* diodes_read, td_data_fw** data_p)
{
    td_fw_result_t rc;
    int i = 0, max_diode_num = 1;

    if (!diodes_read || !mf)
    {
        return TDFWE_INV_ARG;
    }

    if (diode_idx == TD_FW_ALL_DIODES)
    {
        // query all diode idx
        rc = _td_fw_get_max_diode_idx(mf, &max_diode_num);
        if (rc)
        {
            return TDFWE_ICMD;
        }
    }
    *diodes_read = 0;
    // allocate diode_cnt elements in data
    // adrianc: we actually allocate here more than we need
    *data_p = (td_data_fw*)malloc(sizeof(td_data_fw) * max_diode_num);
    td_data_fw* data = *data_p;

    if (!data)
    {
        snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "memory allocation failed in td_fw_read_diodes");
        return TDFWE_MEM_ERROR;
    }
    memset(data, 0, sizeof(td_data_fw) * max_diode_num);

    // for each diode fill its td_data_fw struct
    for (i = 0; i < max_diode_num; i++)
    {
        rc = td_fw_read_diode(mf, diode_idx == TD_FW_ALL_DIODES ? i : diode_idx, &(data[*diodes_read]));
        if (rc)
        {
            if (rc == TDFWW_DIODE_IDX_NO_EXIST)
            {
                // diode with diode index i doesnt exist skip...
                continue;
            }
            else
            {
                // if one fails all fails
                free(data);
                *diodes_read = 0;
                return rc;
            }
        }
        (*diodes_read)++;
    }

    return TDFW_SUCCESS;
}

void td_fw_release_data(td_data_fw* data_p)
{
    free(data_p);
}

void td_fw_release_mmta_data(td_data_mmta* data_p)
{
    if (data_p)
    {
        free(data_p);
    }
}

td_fw_result_t td_fw_read_diode(mfile* mf, int diode_idx, td_data_fw* diode_data)
{
    (void)diode_idx;
    (void)diode_data;

    reg_access_status_t rc;
    struct reg_access_hca_mtmp_ext mtmp;
    memset(&mtmp, 0, sizeof(mtmp));

    if (!mf || diode_idx < 0 || diode_idx > 255)
    {
        return TDFWE_INV_ARG;
    }
    // send mtmp register and put results in diode_data
    DPRINTF("sending mtmp register with diode index: 0x%x\n", diode_idx);
    mtmp.i = 1;
    mtmp.sensor_index = diode_idx;
    rc = reg_access_mtmp(mf, REG_ACCESS_METHOD_GET, &mtmp);
    if (rc)
    {
        if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_REG_ACCESS_RES_NOT_AVLBL)
        { // diode doesnt exist or not active
            DPRINTF("reg_access failed (0x%x): %s, diode id 0x%x doesnt exist", rc, reg_access_err2str(rc), diode_idx);
            snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "Failed to query diode(0x%x), diode does not exist.", diode_idx);
            return TDFWW_DIODE_IDX_NO_EXIST;
        }
        else
        {
            DPRINTF("reg_access failed (0x%x): %s", rc, reg_access_err2str(rc));
            snprintf(td_fw_err_str, TD_FW_MAX_ERR_LEN, "Failed to query diode: %s", reg_access_err2str(rc));
            return TDFWE_ICMD;
        }
    }

    if (diode_data)
    {
        diode_data->diode_idx = diode_idx;
        diode_data->max_temp = (int16_t)mtmp.max_temperature * 0.125f;
        diode_data->temp = (int16_t)mtmp.temperature * 0.125f;
        diode_data->threshold_hi = (int16_t)mtmp.temperature_threshold_hi;
        diode_data->threshold_lo = (int16_t)mtmp.temperature_threshold_lo;
        diode_data->hw_threshold = DEFAULT_THRESH_PROT_VAL;
        // name_lo and name_hi are actually strings i.e no need for swapping (restore to original format)
        mtmp.sensor_name_lo = __cpu_to_be32(mtmp.sensor_name_lo);
        mtmp.sensor_name_hi = __cpu_to_be32(mtmp.sensor_name_hi);
        memcpy(diode_data->diode_name, (char*)&mtmp.sensor_name_hi, 4);
        memcpy(&(diode_data->diode_name[4]), (char*)&mtmp.sensor_name_lo, 4);
        // strncpy(td_data_fw->diode_name, _diode_idx_to_str(diode_idx), MAX_DIODE_LEN -1);
        // printf("-D- diode idx= %d , name : %s\n", diode_idx, td_data_fw->diode_name)
        DPRINTF("diode(0x%x) %s, max_temp: %d, temp: %d, threshold_hi: %d, threshold_lo: %d\n", diode_idx,
                td_data_fw->diode_name, td_data_fw->max_temp, td_data_fw->temp,
                td_data_fw->threshold_hi, td_data_fw->threshold_lo);
    }

    return TDFW_SUCCESS;
}
