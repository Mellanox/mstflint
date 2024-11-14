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

#define MAX_NUM_OF_DIODES 160 // To fit the max number of diodes for the new generation (16 and 7nm)

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
        diode_data->max_temp = (int)((int16_t)mtmp.max_temperature * 0.125);
        diode_data->temp = (int)((int16_t)(mtmp.temperature) * 0.125);
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
