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

#ifndef MGET_TEMP_SENSORS_H
#define MGET_TEMP_SENSORS_H

#include <stdbool.h>
#include <stddef.h>
#include "dev_mgt/therm_fw.h"
#include <mtcr.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* The parts of the mget_temp reading that speak the thermal library's own types. Kept
     * apart from mget_temp_lib.h so the plain max-temperature reader stays usable without
     * therm_fw.h, whose own header directs client code to the thermal library API instead. */

    /* Read the CPO module sensors into *mmta_data_p (free with td_fw_release_mmta_data).
     * Returns the number of sensors read, or -1 on a read failure.
     *
     * Reads are gated on MGIR.cpo_indication because MMTA is MCAM-valid on non-CPO devices
     * too, where its module rows describe no real hardware. *cpo_supported reports that gate,
     * so a caller can pick its output format; no_modules suppresses the read but not the gate. */
    int mget_temp_read_cpo_module_sensors(mfile* mf,
                                          td_temp_unit_t requested_unit,
                                          td_data_mmta** mmta_data_p,
                                          bool* cpo_supported,
                                          bool no_modules);

    /* Fold the module sensors into a running maximum and return it. TEC entries are skipped:
     * they carry power in mW, not a temperature. */
    int mget_temp_include_mmta_in_max_temp(td_data_mmta* mmta_data, int mmta_sensors_read, int current_max);

    /* mget_temp_read_sensors_max() on a caller-chosen module-sensor resolution.
     *
     * The unit only quantizes the module readings, but the maximum is truncated to whole
     * degrees, so a sensor sitting just under a degree boundary can truncate differently
     * per unit. The CLI passes its --precision choice here to keep one reading behind every
     * report mode; mget_temp_read_sensors_max() pins the default so the SDK never has to
     * name a thermal-library type. All other arguments behave as documented there. */
    int mget_temp_read_sensors_max_unit(mfile* mf,
                                        td_temp_unit_t requested_unit,
                                        bool no_modules,
                                        int* temperature,
                                        char* error_buffer,
                                        size_t error_buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* MGET_TEMP_SENSORS_H */
