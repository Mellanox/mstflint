/*
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
 *  tools_dev_types.h - Defines an enum value for all mellanox chips in order to
 *                     have a uniform IDs for all tools.
 *
 *  Version: $Id$
 *
 *  Author: Wasim Abo Moch (wasim@mellanox.co.il)
 */

#ifndef TOOLS_DEV_TYPE_H
#define TOOLS_DEV_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mtcr.h>
#include <bit_slice.h>

enum dm_dev_id
{
    DeviceStartMarker = 0,    // Dummy Device - Marker for first device
                              // so you can iteratre from DeviceStartMarker to DeviceEnd
    DeviceHermonC0 = 0,
    DeviceBaz,
    DeviceDolev,
    DeviceShaldag,
    DeviceHermonB0,
    DeviceHermon,
    DeviceSinai,
    DeviceAnafa2,
    DeviceArbelMF,
    DeviceArbel,
    DeviceTavor,
    DeviceAnafa,
    DeviceEndMarker           // Dummy Device - Marker for indicating error and end of devices
};

typedef enum dm_dev_id dm_dev_id_t;

/**
 * Returns 0 on success and 1 on failure.
 */
// TODO: orenk: rename to get_device_id
int dm_get_device_id(mfile* mf,
                     dm_dev_id_t* ptr_dev_type,
                     u_int32_t* ptr_dev_id,
                     u_int32_t* ptr_chip_rev);

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id_offline(u_int32_t devid,
                             u_int32_t chip_rev,
                             dm_dev_id_t* ptr_dev_type);

/**
 * Returns the device name as a "const char*" (internal name)
 */
const char* dm_dev_type2str(dm_dev_id_t type);

/**
 * A predicate returning if the device is an hca
 */
int dm_dev_is_hca(dm_dev_id_t type);

/**
 * A predicate returning if the device is a switch
 */
int dm_dev_is_switch(dm_dev_id_t type);

/**
 * A predicate returning if the device is a bridge
 */
int dm_dev_is_bridge(dm_dev_id_t type);


/**
 * Returns the device name as a "const char*" (external name)
 */
const char* dm_dev_type2str_ext(dm_dev_id_t type);

/**
 * Returns the max num of ports or -1 on error
 */
int dm_get_hw_ports_num(dm_dev_id_t type);

/**
 * Returns the HW device id of the givn device type or zero on failure.
 */
u_int32_t dm_get_hw_dev_id(dm_dev_id_t type);

/**
 * Returns the HW chip revision of the given device type or zero on failures,
 * This is useful to distingwuish between hermon and hermon_b0.
 */
u_int32_t dm_get_hw_rev_id(dm_dev_id_t type);

#ifdef __cplusplus
}       /* end of 'extern "C"' */
#endif

#endif // TOOLS_DEV_TYPE_H
