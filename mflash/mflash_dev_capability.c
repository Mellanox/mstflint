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
        return 0;
    case DeviceQuantum:
    case DeviceConnectX6:
    case DeviceSpectrum2:
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
    case DeviceQuantum:
    case DeviceConnectX6:
    case DeviceSpectrum2:
        return 0;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 0;
    }
}

//When (*status != MFE_OK) return value is undefined
int is_icmdif_supported(mflash *mfl, MfError *status)
{
    *status = MFE_OK;

    switch (mfl->dm_dev_id) {
    case DeviceConnectX2:
    case DeviceInfiniScaleIV:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceSwitchX:
        return 0;
    case DeviceConnectIB:
    case DeviceSwitchIB:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceSpectrum:
    case DeviceSwitchIB2:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceQuantum:
    case DeviceSpectrum2:
    case DeviceConnectX6:
        return 1;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 1;
    }
}

//When (*status != MFE_OK) return value is undefined
int is_supports_sw_reset(mflash *mfl, MfError *status)
{
    *status = MFE_OK;

    switch (mfl->dm_dev_id) {
    case DeviceInfiniScaleIV:
    case DeviceSwitchX:
    case DeviceSwitchIB:
    case DeviceSwitchIB2:
    case DeviceQuantum:
        return 1;
    case DeviceConnectX2:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
    case DeviceConnectIB:
    case DeviceSpectrum:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceConnectX6:
    case DeviceSpectrum2:
        return 0;
    default:
        *status = MFE_UNSUPPORTED_DEVICE;
        fprintf(stderr, "The device type %d is not supported.\n", mfl->dm_dev_id);
        return 0;
    }
}
