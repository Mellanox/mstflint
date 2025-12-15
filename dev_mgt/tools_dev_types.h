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
extern "C"
{
#endif

#include <common/bit_slice.h>
#include <common/compatibility.h>
#include "include/mtcr_ul/mtcr.h"

typedef enum get_dev_id_error_t {
    GET_DEV_ID_SUCCESS,
    GET_DEV_ID_ERROR,
    CRSPACE_READ_ERROR,
    CHECK_PTR_DEV_ID,
} dev_id_error;

enum dm_dev_type {
    DM_UNKNOWN = -1,
    DM_HCA,
    DM_SWITCH,
    DM_BRIDGE,
    DM_QSFP_CABLE,
    DM_CMIS_CABLE,
    DM_SFP_CABLE,
    DM_LINKX, /* linkx chip */
    DM_GEARBOX,
    DM_RETIMER
};

enum dm_dev_id {
    DeviceUnknown     = -1,    /* Dummy Device - Marker for indicating error. */
    DeviceStartMarker = 0,     /* Dummy Device - Marker for first device */
                               /* to let user iterate from DeviceStartMarker to DeviceEndMarker */
                               /* Note: Call dm_is_device_supported() to see if a device is supported by the lib. */

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
    DeviceBlueField3,
    DeviceBlueField4,
    DeviceSwitchIB2,
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
    DeviceConnectX7,
    DeviceConnectX8,
    DeviceConnectX8_Pure_PCIe_Switch,
    DeviceConnectX9_Pure_PCIe_Switch,
    DeviceConnectX9,
    DeviceSpectrum3,     /* Firebird */
    DeviceSpectrum4,     /* Albatross */
    DeviceSpectrum5,
    DeviceSpectrum6,
    DeviceSpectrum6IB,
    DeviceQuantum2,      /* Blackbird */
    DeviceQuantum3,      /* Sunbird */
    DeviceQuantum4,
    DeviceGearBox,
    DeviceGearBoxManager,
    DeviceAbirGearBox,
    DeviceCableCMIS,
    DeviceCableCMISPaging,
    DeviceGB100,        /* Blackwell */
    DeviceGR100,
    DeviceArcusPTC,     /* ArcusP Test Chip */
    DeviceArcusP,
    DeviceArcusE,
    DeviceEndMarker     /* Dummy Device - Marker for indicating end of devices when iterating */
};

enum hw_dev_id {
    DeviceConnectX3_HwId        = 0x1f5,
    DeviceConnectIB_HwId        = 0x1ff,
    DeviceConnectX3Pro_HwId     = 0x1f7,
    DeviceSwitchIB_HwId         = 0x247,
    DeviceSpectrum_HwId         = 0x249,
    DeviceConnectX4_HwId        = 0x209,
    DeviceConnectX4LX_HwId      = 0x20b,
    DeviceConnectX5_HwId        = 0x20d,
    DeviceConnectX6_HwId        = 0x20f,
    DeviceConnectX6DX_HwId      = 0x212,
    DeviceConnectX6LX_HwId      = 0x216,
    DeviceConnectX7_HwId        = 0x218,
    DeviceConnectX8_HwId        = 0x21e,
    DeviceConnectX8_Pure_PCIe_Switch_HwId = 0x222,
    DeviceConnectX9_HwId        = 0x224,
    DeviceConnectX9_Pure_PCIe_Switch_HwId = 0x228,
    DeviceBlueField_HwId        = 0x211,
    DeviceBlueField2_HwId       = 0x214,
    DeviceBlueField3_HwId       = 0x21c,
    DeviceBlueField4_HwId       = 0x220,
    DeviceSwitchIB2_HwId        = 0x24b,
    DeviceCableQSFP_HwId        = 0x0d,
    DeviceCableQSFPaging_HwId   = 0x11,
    DeviceCableCMIS_HwId        = 0x19,
    DeviceCableCMISPaging_HwId  = 0x19,
    DeviceCableSFP_HwId         = 0x03,
    DeviceCableSFP51_HwId       = 0x03,
    DeviceCableSFP51Paging_HwId = 0x03,
    DeviceSpectrum2_HwId        = 0x24e,
    DeviceQuantum_HwId          = 0x24d,
    DeviceQuantum2_HwId         = 0x257,
    DeviceQuantum3_HwId         = 0x25b,
    DeviceQuantum4_HwId         = 0x278,
    DeviceGB100_HwId            = 0x2900,
    DeviceGR100_HwId            = 0x3000,
    DeviceArdbeg_HwId           = 0x6e,
    DeviceBaritone_HwId         = 0x6b,
    DeviceMenhit_HwId           = 0x72,
    DeviceSecureHost_HwId       = 0xcafe,
    DeviceSpectrum3_HwId        = 0x250,
    DeviceSpectrum4_HwId        = 0x254,
    DeviceSpectrum5_HwId        = 0x270,
    DeviceSpectrum6_HwId        = 0x274,
    DeviceSpectrum6IB_HwId      = 0x276,
    DeviceGearBox_HwId          = 0x252,
    DeviceGearBoxManager_HwId   = 0x253,
    DeviceAbirGearBox_HwId      = 0x256,
    DeviceArcusPTC_HwId         = 0x7f, /* ArcusP Test Chip */
    DeviceArcusP_HwId           = 0x80,
    DeviceArcusE_HwId           = 0x81,
};
typedef enum dm_dev_id dm_dev_id_t;

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id(mfile* mf, dm_dev_id_t* ptr_dev_type, u_int32_t* ptr_dev_id, u_int32_t* ptr_chip_rev);

int dm_get_device_id_without_prints(mfile      * mf,
                                    dm_dev_id_t* ptr_dm_dev_id,
                                    u_int32_t  * ptr_hw_dev_id,
                                    u_int32_t  * ptr_hw_rev);

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id_offline(u_int32_t devid, u_int32_t chip_rev, dm_dev_id_t* ptr_dev_type);

/**
 * Returns 1 if device is supported and 0 otherwise (library dependant)
 */
int dm_is_device_supported(dm_dev_id_t type);

/**
 * Returns the device name as a "const char*"
 */
const char* dm_dev_type2str(dm_dev_id_t type);

/**
 * Returns the external device name as a "const char*"
 */
const char* dm_dev_type2str_external(dm_dev_id_t type);

/**
 * Returns the device name as a "const char*"
 */
const char* dm_dev_hw_id2str(unsigned int hw_dev_id);

/**
 * Returns the device id
 */
dm_dev_id_t dm_dev_str2type(const char* str);

/**
 * Returns dev type
*/
dm_dev_id_t dm_dev_sw_id2type(int sw_dev_id);

/**
 * Returns the HW device id of the given SW device id.
 */
u_int16_t dm_dev_sw_id2hw_dev_id(u_int16_t sw_dev_id);

/**
 * A predicate returning if the device is an hca
 */
int dm_dev_is_hca(dm_dev_id_t type);

/**
 * A predicate returning if the device is gearbox
 */
int dm_dev_is_gearbox(dm_dev_id_t type);

/**
 * A predicate returning the software device id
 */
int dm_dev_type2sw_id(dm_dev_id_t type);

/**
 * A predicate returning if the device is menhit
 */
int dm_is_menhit(dm_dev_id_t type);

/**
 * A predicate returning if the device is dummy
 */
int dm_dev_is_dummy(dm_dev_id_t type);

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
 * A predicate returning if the device is an ArcusE chipset
 */
int dm_dev_is_retimer(dm_dev_id_t type);

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

/**
 * A predicate returning if the device is a gb100
 */
int dm_is_gb100(dm_dev_id_t type);

/**
 * A predicate returning if the device is a gpu device
 */
int dm_is_gpu(dm_dev_id_t type);

/**
 * A predicate returning if the device is a gr100
 */
int dm_is_gr100(dm_dev_id_t type);

int dm_is_4th_gen(dm_dev_id_t type);

int dm_dev_is_fs5(dm_dev_id_t type);

int dm_is_5th_gen_hca(dm_dev_id_t type);

int dm_is_connectib(dm_dev_id_t type);

int dm_is_cx8(dm_dev_id_t type);

int dm_is_cx9(dm_dev_id_t type);

int dm_is_new_gen_switch(dm_dev_id_t type);

int dm_dev_is_raven_family_switch(dm_dev_id_t type);

int dm_dev_is_ib_switch(dm_dev_id_t type);

int dm_dev_is_eth_switch(dm_dev_id_t type);
/*
 * A predicate returning if the device is in LiveFish mode
 */
int dm_is_livefish_mode(mfile* mf);

int dm_is_ib_access(mfile* mf);

int dm_is_bluefield(dm_dev_id_t type);

/*
A predicate returning if the device needs dword swap for MCAM.mng_feature_cap_mask
*/
int dm_dev_is_mcam_dword_swap_needed(dm_dev_id_t type);
#ifdef __cplusplus
} /* end of 'extern "C"' */
#endif

#endif /* TOOLS_DEV_TYPE_H */
