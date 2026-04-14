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
 *  This is an internal header for use by the theral library only.
 *  This API implements reading of thermal diodes through FW interface
 *  This API requires FW to support MTCAP and MTMP thermal managment registers
 *  refer to SwitchX-PRM from more info regarding these commands.
 *  DO NOT USE THIS IN CLIENT CODE. Call the thermal library API instead.
 */

#ifndef _TD_FW_5TH_GEN_ /* guard */
#define _TD_FW_5TH_GEN_

#ifdef __cplusplus
extern "C"
{
#endif

#include <mtcr.h>

    #define MAX_DIODE_LEN 32 // Sufficient for names like "mod15_TEC" (10 chars + null)
    #define TD_FW_ALL_DIODES -1
    #define DEFAULT_THRESH_PROT_VAL \
    130 /* determines the default HW threshold value for thermal shutdown as configured by fw */
    #define TD_FW_INVALID_TEMP -1000

    /* Temperature unit types */
    typedef enum
    {
        TD_FW_TEMP_UNIT_0_125C = 0, // 0.125°C resolution (default)
        TD_FW_TEMP_UNIT_1_256C = 1  // 1/256°C resolution (~0.0039°C, high precision)
    } td_temp_unit_t;

    /* MMTA Module sensor types */
    typedef enum
    {
        TD_MMTA_SENSOR_ELS = 0, // External Laser Source (temperature)
        TD_MMTA_SENSOR_OE = 1,  // Optical Engine (temperature)
        TD_MMTA_SENSOR_TEC = 2  // Thermoelectric Cooler (power)
    } td_mmta_sensor_type_t;

/* MMTA supported measurements bitmap */
#define MMTA_SUPPORTED_ELS_TEMP 0x01  /* Bit 0 */
#define MMTA_SUPPORTED_TEC_POWER 0x02 /* Bit 1 */
#define MMTA_SUPPORTED_OE_TEMP 0x04   /* Bit 2 */

    typedef enum
    {
        TDFW_SUCCESS = 0,
        TDFWE_INV_ARG,                 /* an invalid argument was passed to the function */ //V
        TDFWE_ICMD = 3,                /* error accessing ICMD iterface*/ //V
        TDFWE_FW_NOT_LOADED,           /* error indicating the FW is stuck or not loaded*/
        TDFWE_MEM_ERROR,               /* memory allocation failed.*/ //V
        TDFWE_MEM_ALLOC_FAIL,          /* memory allocation failed (alternate name) */
        TDFWE_REG_ACCESS_ERR,          /* register access error */
        TDFWE_BAD_CONFIG,              /* bad didoe configuration */
        TDFWW_UNSUPPORTED = -1,        /* warning: the requested functionality is unsupported. nothing done */
        TDFWW_DEVICE_NOTSUPPORTS = -2, /* the specific device does not support the requested operation */
        TDFWW_DIODE_IDX_NO_EXIST = -3  /* the specific diode index doesnt exist on the device */ //V
    } td_fw_result_t;

    typedef enum
    {
        
        TD_FW_IOPX,
        TD_FW_IOPL0,
        TD_FW_IOPL1,
        TD_FW_LBF0,
        TD_FW_LBF1,
        TD_FW_LBR0,
        TD_FW_LBR1,
        TD_FW_LBL,
        TD_FW_LBM,
        TD_FW_YU,
        TD_FW_UNKN,
        _TD_FW_NUM_DIODES
    } td_fw_diode_id_t;

    /* Original td_data_fw structure - MTMP sensors */
    typedef struct
    {
        int diode_idx;      /* diode index */
        float temp;         /* temperature in Celsius, field valid iff field != INVALID_TEMP */
        float max_temp;     /* highest measured temperature, field valid iff field != INVALID_TEMP */
        float threshold_hi; /* high threshold of the hysteresis mechanism, field valid iff field != INVALID_TEMP */
        float threshold_lo; /* low threshold of the hysteresis mechanism, field valid iff field != INVALID_TEMP */
        float hw_threshold; /* threshold for hw thermal shutdown, field valid iff field != INVALID_TEMP */
        char diode_name[MAX_DIODE_LEN]; /* 8 characters long diode symbol */
    } td_data_fw;

    /* MMTA sensor data */
    typedef struct
    {
        // For TEC sensors: temp/max_temp contain power in milliwatts (mW)
        // For ELS/OE sensors: temp/max_temp contain temperature in Celsius
        td_data_fw base;
        td_mmta_sensor_type_t type; // ELS, OE, or TEC
        td_temp_unit_t temp_unit;   // precision/unit for display formatting
        char unit_str[16];          // "0.125°C", "1/256°C", or "1mW"
    } td_data_mmta;

    #define TD_FW_MAX_ERR_LEN 100
    extern char td_fw_err_str[];

    /*
     * get available diode count from device
     * IN:
     * dev - thermal context
     * diode_cnt - ptr where the number of didoes will be updated
     * OUT:
     * return status - 0==success else failure.
     */
    td_fw_result_t td_fw_get_diode_cnt(mfile* mf, int* diode_cnt);

    /*
     * get diodes readings from device and fill allocated ptr in dev
     * IN:
     * mf - mfile
     * diode_idx - if != TD_ALL_DIODES then method will query diode_idx diode else
     *             method will query all available diodes.
     * diodes_read - ptr where the number of didoes actually queried will be updated (can be zero in that case diode_idx
     * doesnt exist)
     * OUT:
     * return status - 0==success else failure.
     * data_p - pointer to be allocated and filled with thermal info
     * 
     */
    td_fw_result_t td_fw_read_diodes(mfile* mf, int diode_idx, int* diodes_read, td_data_fw** data_p);

    /*
     * Read all CPO module sensors via MMTA register
     * IN:
     * mf - device context
     * OUT:
     * sensors_read - number of sensor entries found (up to 3 per module: ELS, OE, TEC)
     * data_p - pointer to allocated array of sensor data
     * return status - TDFW_SUCCESS on success
     */
    td_fw_result_t
      td_fw_read_module_sensors(mfile* mf, td_temp_unit_t requested_unit, int* sensors_read, td_data_mmta** data_p);

    /*
     * free allocated data pointer
     * IN:
     * data_p - pointer to data
     * doesnt exist) OUT: return status - 0==success else failure.
     */
    void td_fw_release_data(td_data_fw* data_p);

    /*
     * free allocated MMTA module data pointer
     * IN:
     * data_p - pointer to MMTA module data
     */
    void td_fw_release_mmta_data(td_data_mmta* data_p);

    /*
     * get diode readings of a specific diode_idx and return the readings in diode_data
     * IN:
     * dev - thermal context
     * diode_idx - index of diode to be read
     * diode_data - readings from the diode will be stored in diode_data
     * OUT:
     * return status - 0==success else failure.
     */
    td_fw_result_t td_fw_read_diode(mfile* mf, int diode_idx, td_data_fw* diode_data);

#ifdef __cplusplus
} /* end of 'extern "C"' */
#endif

#endif /* _TD_FW_5TH_GEN_ guard */
