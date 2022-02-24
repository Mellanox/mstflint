/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
*/

/*
 * mflash_dev_capabillity.c
 *
 *  Created on: Jul 8, 2018
 *      Author: idanme
 */

#include "mflash_dev_capability.h"

//When (*status != MFE_OK) return value is undefined
int is_four_byte_address_needed(mflash *mfl, MfError *status)
{
    *status = MFE_OK;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceInfiniScaleIV:
    case DeviceSwitchX:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceSpectrum:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceSwitchIB2:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceSecureHost:
        return 0;
    case DeviceQuantum:
    case DeviceConnectX6:
    case DeviceConnectX7:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
    case DeviceQuantum2:
    case DeviceSpectrum4:
    case DeviceBlueField2:
    case DeviceBlueField3:
    case DeviceGearBox:
    case DeviceGearBoxManager:
    case DeviceAbirGearBox:
        return 1;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 1;
    }
}

//When (*status != MFE_OK) return value is undefined
int is_flash_enable_needed(mflash *mfl, MfError *status)
{
    *status = MFE_OK;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceInfiniScaleIV:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceSwitchX:
        return 1;
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceSwitchIB2:
    case DeviceSpectrum:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceBlueField2:
    case DeviceBlueField3:
    case DeviceQuantum:
    case DeviceConnectX6:
    case DeviceConnectX7:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
    case DeviceQuantum2:
    case DeviceSpectrum4:
    case DeviceSecureHost:
    case DeviceGearBox:
    case DeviceGearBoxManager:
    case DeviceAbirGearBox:
        return 0;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 0;
    }
}

//When (*status != MFE_OK) return value is undefined
int is_icmdif_supported(mflash *mfl, MfError *status, int *is7NmSuppported)
{
    *status = MFE_OK;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceInfiniScaleIV:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceSwitchX:
    case DeviceSecureHost:
        return 0;
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceSpectrum:
    case DeviceSwitchIB2:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceBlueField2:
    case DeviceQuantum:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
    case DeviceConnectX6:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceGearBox:
    case DeviceGearBoxManager:
        *is7NmSuppported = 0;
        return 1;
    case DeviceQuantum2:
    case DeviceSpectrum4:
    case DeviceConnectX7:
    case DeviceBlueField3:
    case DeviceAbirGearBox:
        *is7NmSuppported = 1;
        return 1;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 1;
    }
}

