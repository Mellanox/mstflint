/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 * End of legal section ......................................................
 *
 *  toos_dev_types.h - Defines an enum value for all mellanox chips in order to
 *                     have a uniform IDs for all toos.
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

#include <common/bit_slice.h>
#include <common/compatibility.h>
#include <mtcr.h>

enum dm_dev_id
{
    DeviceUnknown = -1,       //Dummy Device - Marker for indicating error.
    DeviceStartMarker = 0,    // Dummy Device - Marker for first device
                              // to let user iterate from DeviceStartMarker to DeviceEndMarker
                              // Note: Call dm_is_device_supported() to see if a device is supported by the lib.

    DeviceInfiniScale = 0,  // UnSupported
    DeviceInfiniHost,       // UnSupported
    DeviceInfiniHostIIIEx,  // UnSupported
    DeviceInfiniHostIIIEx_MF,// UnSupported
    DeviceInfiniScaleIII,   // UnSupported
    DeviceInfiniHostIIILx,  // UnSupported
    DeviceConnectX,         // UnSupported
    DeviceConnectX2,
    DeviceInfiniScaleIV,
    DeviceBridgeX,          // UnSupported
    DeviceSwitchX,
    DeviceConnectX3,
    DeviceConnectIB,
    DeviceConnectX3Pro,
    DeviceSwitchIB,
    DeviceSpectrum,
    DeviceQuantum,
    DeviceConnectX4,
    DeviceConnectX4LX,
    DeviceConnectX5,
    DeviceConnectX6,
    DeviceBlueField,
    DeviceBlueField2,
    DeviceFPGA,             // UnSupported
    DeviceSwitchIB2,
    DeviceFPGANewton,
    DeviceCable,
    DeviceCableQSFP,
    DeviceCableQSFPaging,
    DeviceCableSFP,
    DeviceCableSFP51,
    DeviceCableSFP51Paging,
    DeviceArdbeg,
    DeviceBaritone,
    DeviceMenhit,
    DeviceSpectrum2,
    DeviceDummy,
    DeviceSecureHost,
    DeviceConnectX6DX,
    DeviceConnectX6LX,
    DeviceSpectrum3, //Firebird
    DeviceEndMarker           // Dummy Device - Marker for indicating end of devices when iterating
};

typedef enum dm_dev_id dm_dev_id_t;

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id(mfile *mf,
                     dm_dev_id_t *ptr_dev_type,
                     u_int32_t *ptr_dev_id,
                     u_int32_t *ptr_chip_rev);

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id_offline(u_int32_t devid,
                             u_int32_t chip_rev,
                             dm_dev_id_t *ptr_dev_type);


/**
 * Returns 1 if device is supported and 0 otherwise (library dependant)
 */
int dm_is_device_supported(dm_dev_id_t type);


/**
 * Returns the device name as a "const char*"
 */
const char* dm_dev_type2str(dm_dev_id_t type);

/**
 * Returns the device id
 */
dm_dev_id_t dm_dev_str2type(const char *str);

/**
 * A predicate returning if the device is an hca
 */
int dm_dev_is_hca(dm_dev_id_t type);

/**
 * A predicate returning if the hca supports 200G speed and above
 */
int dm_dev_is_200g_speed_supported_hca(dm_dev_id_t type);

/**
 * A predicate returning if the device is a switch
 */
int dm_dev_is_switch(dm_dev_id_t type);

/**
 * A predicate returning if the switch supports 200G speed and above
 */
int dm_dev_is_200g_speed_supported_switch(dm_dev_id_t type);

/**
 * A predicate returning if the device is a bridge
 */
int dm_dev_is_bridge(dm_dev_id_t type);

/**
 * A predicate returning if the device is a Cable
 */
int dm_dev_is_cable(dm_dev_id_t type);

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
 * This is useful to distinguish between ConnectX2 and ConnectX.
 */
u_int32_t dm_get_hw_rev_id(dm_dev_id_t type);

/**
 * A predicate returning if the device supports Function Per Port
 */
int dm_is_fpp_supported(dm_dev_id_t type);

int dm_is_4th_gen(dm_dev_id_t type);

int dm_is_5th_gen_hca(dm_dev_id_t type);

int dm_is_newton(dm_dev_id_t type);

int dm_is_connectib(dm_dev_id_t type);

int dm_is_switchx(dm_dev_id_t type);

int dm_is_new_gen_switch(dm_dev_id_t type);

int dm_dev_is_raven_family_switch(dm_dev_id_t type);
/*
 * A predicate returning if the device is in LiveFish mode
 */
int dm_is_livefish_mode(mfile *mf);

#ifdef __cplusplus
}       /* end of 'extern "C"' */
#endif

#endif // TOOLS_DEV_TYPE_H
