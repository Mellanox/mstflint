/*                  - Mellanox Confidential and Proprietary -
 *
 * Copyright (C) May 2002, Mellanox Technologies Ltd. ALL RIGHTS RESERVED.
 *
 * Except as specifically permitted herein, no portion of the information,
 * including but not limited to object code and source code, may be reproduced,
 * modified, distributed, republished or otherwise exploited in any form or by
 * any means for any purpose without the prior written permission of Mellanox
 * Technologies Ltd. Use of software subject to the terms and conditions
 * detailed in the file "LICENSE.txt".
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
    DeviceStartMarker = 0,    // Dummy Device - Marker for first device
                              // to let user iterate from DeviceStartMarker to DeviceEndMarker

    DeviceAnafa = 0,
    DeviceTavor,
    DeviceArbel,
    DeviceArbelMF,
    DeviceAnafa2,
    DeviceSinai,
    DeviceHermon,
    DeviceHermonB0,
    DeviceShaldag,
    DeviceDolev,
    DeviceBaz,
    DeviceKfir,
    DeviceGolan,
    DeviceBental,

    DeviceEndMarker           // Dummy Device - Marker for indicating error and end of devices
};

typedef enum dm_dev_id dm_dev_id_t;

/**
 * Returns 0 on success and 1 on failure.
 */
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
 * This is useful to distinguish between hermon and hermon_b0.
 */
u_int32_t dm_get_hw_rev_id(dm_dev_id_t type);

#ifdef __cplusplus
}       /* end of 'extern "C"' */
#endif

#endif // TOOLS_DEV_TYPE_H
