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

#ifndef MGET_TEMP_LIB_H
#define MGET_TEMP_LIB_H

#include <stdbool.h>
#include <stddef.h>
#include <mtcr.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Mirrors the thermal library's TD_FW_INVALID_TEMP. Re-exported so callers outside this
 * tool can recognize "no reading" without including therm_fw.h, which directs client code
 * to the thermal library API instead. mget_temp_lib.c static-asserts the two agree. */
#define MGET_TEMP_INVALID_TEMP -1000

/* Return codes. Errors are positive so the caller can name the failure. */
#define MGET_TEMP_OK 0
#define MGET_TEMP_ERR_DIODE_READ 1
#define MGET_TEMP_ERR_MODULE_READ 2
#define MGET_TEMP_ERR_LIVEFISH 3
#define MGET_TEMP_ERR_GPU_ASIC 4
#define MGET_TEMP_ERR_GPU_READ 5
#define MGET_TEMP_ERR_INVALID_ARGUMENT 6

/* Buffer size that always holds a failure description, mirroring the thermal library's
 * TD_FW_MAX_ERR_LEN. mget_temp_lib.c static-asserts the two agree. */
#define MGET_TEMP_MAX_ERR_LEN 256

/* Not an error: mget_temp_resolve_device() found an ordinary device whose temperature
 * still has to be read from its sensors. */
#define MGET_TEMP_DEVICE_HAS_SENSORS (-1)

    /* Decide how - or whether - this device reports a temperature, before any sensor is
     * read. The caller keeps ownership of mf.
     *
     * MGET_TEMP_DEVICE_HAS_SENSORS  an ordinary device; read its sensors next.
     * MGET_TEMP_ERR_*            this device cannot report a temperature at all.
     *
     * Separate from the read below because the CLI applies this gate to every report mode
     * (-v / -z / --states), not just the bare reading.
     *
     * A NULL mf or temperature yields MGET_TEMP_ERR_INVALID_ARGUMENT. */
    int mget_temp_resolve_device(mfile* mf, int* temperature);

    /* Read every thermal sensor - the internal diodes and, on CPO systems, the module
     * sensors - and report the highest valid reading, in whole degrees Celsius. Assumes
     * the device was already resolved as having sensors. Module sensors are read at the
     * default 0.125C resolution; mget_temp_read_sensors_max_unit() in mget_temp_sensors.h
     * takes that resolution as an argument.
     *
     * no_modules skips the CPO module (MMTA) sensors, mirroring the CLI's --no-modules.
     *
     * On MGET_TEMP_OK, *temperature may still be MGET_TEMP_INVALID_TEMP: the device
     * answered but no sensor produced a valid reading. On failure *temperature is
     * untouched, and a NULL mf or temperature yields MGET_TEMP_ERR_INVALID_ARGUMENT.
     *
     * error_buffer, when non-NULL, receives the thermal library's description of a failed
     * read, always NUL-terminated. Size it MGET_TEMP_MAX_ERR_LEN; pass NULL when the text
     * is not wanted. The thermal library reports failures through a process-global buffer,
     * so the copy is taken as soon as the read returns to narrow - not close - the window
     * in which another thread's failure overwrites it. */
    int mget_temp_read_sensors_max(mfile* mf,
                                   bool no_modules,
                                   int* temperature,
                                   char* error_buffer,
                                   size_t error_buffer_size);

    /* mget_temp_resolve_device() followed by mget_temp_read_sensors_max() - the whole
     * `mget_temp -d <device>` answer in one call, for callers that want no part of the
     * device-path decision. Never returns MGET_TEMP_DEVICE_HAS_SENSORS.
     *
     * error_buffer behaves as above. */
    int mget_temp_read_max_temperature(mfile* mf,
                                       bool no_modules,
                                       int* temperature,
                                       char* error_buffer,
                                       size_t error_buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* MGET_TEMP_LIB_H */
