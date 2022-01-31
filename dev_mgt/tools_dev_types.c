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
 *  toos_dev_types.c - Defines static info records for all mellanox chips in order to
 *                     have a uniform IDs and info for all tools.
 *
 *  Version: $Id$
 *
 *  Author: Wasim Abo Moch (wasim@mellanox.co.il)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <reg_access/reg_access.h>
#include "tools_dev_types.h"
#include "mflash/mflash_types.h"

enum dm_dev_type {
    DM_UNKNOWN = -1,
    DM_HCA,
    DM_SWITCH,
    DM_BRIDGE,
    DM_QSFP_CABLE,
    DM_CMIS_CABLE,
    DM_SFP_CABLE,
    DM_LINKX, // linkx chip
    DM_GEARBOX
};

struct device_info {
    dm_dev_id_t dm_id;
    u_int16_t hw_dev_id;
    int hw_rev_id;               /* -1 means all revisions match this record */
    int sw_dev_id;               /* -1 means all hw ids  match this record */
    const char *name;
    int port_num;
    enum dm_dev_type dev_type;
};

#define DEVID_ADDR                                             0xf0014
#define CABLEID_ADDR                                           0x0
#define SFP_DIGITAL_DIAGNOSTIC_MONITORING_IMPLEMENTED_ADDR     92
#define SFP_PAGING_IMPLEMENTED_INDICATOR_ADDR                  64

#define ARDBEG_REV0_DEVID 0x6e
#define ARDBEG_REV1_DEVID 0x7e
#define ARDBEG_MIRRORED_DEVID 0x70
#define BARITONE_DEVID 0x6b
#define BARITONE_MIRRORED_DEVID 0x71
#define MENHIT_DEVID_VER0 0x6f
#define MENHIT_DEVID_VER1 0x72
#define MENHIT_DEVID_VER2 0x73


#ifdef CABLES_SUPP
enum dm_dev_type getCableType(u_int8_t id)
{
    switch (id) {
    case 0xd:
    case 0x11:
    case 0xe:
    case 0xc:
        return DM_QSFP_CABLE;

    case 0x3:
        return DM_SFP_CABLE;
    case 0x18:
    case 0x19:  // Stallion2
    case 0x1e:
        return DM_CMIS_CABLE;
    default:
        return DM_UNKNOWN;
    }
}
#endif

static struct device_info g_devs_info[] = {
    {
        DeviceInfiniScaleIV,    //dm_id
        0x01b3,                 //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "InfiniScaleIV",        //name
        36,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceSwitchX,          //dm_id
        0x0245,                 //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "SwitchX",              //name
        64,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceConnectX2,        //dm_id
        0x190,                  //hw_dev_id
        0xb0,                   //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX2",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX3,        //dm_id
        0x1f5,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX3",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectIB,        //dm_id
        0x1ff,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectIB",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX3Pro,     //dm_id
        0x1f7,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX3Pro",         //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceSwitchIB,         //dm_id
        0x247,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "SwitchIB",             //name
        36,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceSpectrum,         //dm_id
        0x249,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Spectrum",             //name
        64,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceConnectX4,        //dm_id
        0x209,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX4",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX4LX,      //dm_id
        0x20b,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX4LX",          //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX5,        //dm_id
        0x20d,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX5",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX6,        //dm_id
        0x20f,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX6",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX6DX,      //dm_id
        0x212,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX6DX",          //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX6LX,      //dm_id
        0x216,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX6LX",          //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceConnectX7,        //dm_id
        0x218,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "ConnectX7",            //name
        4,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceBlueField,        //dm_id
        0x211,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "BlueField",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceBlueField2,        //dm_id
        0x214,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "BlueField2",            //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceBlueField3,       //dm_id
        0x21c,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "BlueField3",           //name
        4,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceFPGANewton,       //dm_id
        0xfff,                  //hw_dev_id - Dummy device ID till we have official one
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "FPGA_NEWTON",          //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceSwitchIB2,        //dm_id
        0x24b,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "SwitchIB2",            //name
        36,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceCableQSFP,        //dm_id
        0x0d,                   //hw_dev_id
        0,                      //hw_rev_id
        -1,                     //sw_dev_id
        "CableQSFP",            //name
        -1,                     //port_num
        DM_QSFP_CABLE           //dev_type
    },
    {
        DeviceCableQSFPaging,   //dm_id
        0x11,                   //hw_dev_id
        0xab,                   //hw_rev_id
        -1,                     //sw_dev_id
        "CableQSFPaging",       //name
        -1,                     //port_num
        DM_QSFP_CABLE           //dev_type
    },
    {
        DeviceCableCMIS,        //dm_id
        0x19,                   //hw_dev_id
        0,                      //hw_rev_id
        -1,                     //sw_dev_id
        "CableCMIS",            //name
        -1,                     //port_num
        DM_CMIS_CABLE           //dev_type
    },
    {
        DeviceCableCMISPaging,   //dm_id
        0x19,                   //hw_dev_id
        0xab,                   //hw_rev_id
        -1,                     //sw_dev_id
        "CableCMISPaging",       //name
        -1,                     //port_num
        DM_CMIS_CABLE           //dev_type
    },
    {
        DeviceCableSFP,         //dm_id
        0x03,                   //hw_dev_id
        1,                      //hw_rev_id
        -1,                     //sw_dev_id
        "CableSFP",             //name
        -1,                     //port_num
        DM_SFP_CABLE            //dev_type
    },
    {
        DeviceCableSFP51,       //dm_id
        0x03,                   //hw_dev_id
        1,                      //hw_rev_id
        -1,                     //sw_dev_id
        "CableSFP51",           //name
        -1,                     //port_num
        DM_SFP_CABLE            //dev_type
    },
    {
        DeviceCableSFP51Paging, //dm_id
        0x03,                   //hw_dev_id
        1,                      //hw_rev_id
        -1,                     //sw_dev_id
        "CableSFP51Paging",     //name
        -1,                     //port_num
        DM_SFP_CABLE            //dev_type
    },
    {
        DeviceSpectrum2,        //dm_id
        0x24e,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Spectrum2",            //name
        128,                    //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceDummy,            //dm_id
        0x1,                    //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "DummyDevice",          //name
        2,                      //port_num
        DM_HCA                  //dev_type
    },
    {
        DeviceQuantum,          //dm_id
        0x24d,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Quantum",              //name
        80,                     //port_num
        DM_SWITCH               //dev_type
    },
    {
        DeviceArdbeg,           //dm_id
        0x6e,                   //hw_dev_id (ArdbegMirror 0x70)
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Ardbeg",               //name
        -1,                     //port_num
        DM_LINKX                //dev_type
    },
    {
        DeviceBaritone,         //dm_id
        0x6b,                   //hw_dev_id (BaritoneMirror 0x71)
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Baritone",             //name
        -1,                     //port_num
        DM_LINKX                //dev_type
    },
    {
        DeviceMenhit,           //dm_id
        0x72,                   //hw_dev_id (other versions 0x6f,0x73)
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Menhit",               //name
        -1,                     //port_num
        DM_LINKX                //dev_type
    },
    {
        DeviceSecureHost,       //dm_id
        0xcafe,                 //hw_dev_id
        0xd0,                   //hw_rev_id
        0,                      //sw_dev_id
        "Unknown Device",       //name
        -1,                     //port_num
        DM_UNKNOWN              //dev_type
    },
    {
        DeviceSpectrum3,        //dm_id
        0x250,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Spectrum3",            //name
        128,                    //port_num NEED_CHECK
        DM_SWITCH               //dev_type
    },
    {
        DeviceSpectrum4,        //dm_id
        0x254,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Spectrum4",            //name
        128,                    //port_num NEED_CHECK
        DM_SWITCH               //dev_type
    },
    {
        DeviceQuantum2,         //dm_id
        0x257,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Quantum2",             //name
        128,                    //port_num NEED_CHECK
        DM_SWITCH               //dev_type
    },
    {
        DeviceGearBox,          //dm_id
        0x252,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Amose GearBox",        //name
        128,                    //port_num NEED_CHECK
        DM_GEARBOX              //dev_type
    },
    {
        DeviceGearBoxManager,   //dm_id
        0x253,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Amos GearBox Managaer",//name
        -1,                     //port_num NEED_CHECK
        DM_GEARBOX              //dev_type
    },
    {
        DeviceAbirGearBox,      //dm_id
        0x256,                  //hw_dev_id
        -1,                     //hw_rev_id
        -1,                     //sw_dev_id
        "Abir GearBox Managaer",//name
        -1,                     //port_num NEED_CHECK
        DM_GEARBOX              //dev_type
    },
    {
        DeviceUnknown,          //dm_id
        0,                      //hw_dev_id
        0,                      //hw_rev_id
        0,                      //sw_dev_id
        "Unknown Device",       //name
        -1,                     //port_num
        DM_UNKNOWN              //dev_type
    }
};

static const struct device_info* get_entry(dm_dev_id_t type)
{
    const struct device_info *p = g_devs_info;
    while (p->dm_id != DeviceUnknown) {
        if (type == p->dm_id) {
            break;
        }
        p++;
    }
    return p;
}

static const struct device_info* get_entry_by_dev_rev_id(u_int32_t hw_dev_id, u_int32_t hw_rev_id)
{
    const struct device_info *p = g_devs_info;
    while (p->dm_id != DeviceUnknown) {
        if (hw_dev_id == p->hw_dev_id) {
            if ((p->hw_rev_id == -1) ||  ((int)hw_rev_id == p->hw_rev_id)) {
                break;
            }
        }
        p++;
    }
    return p;
}

typedef enum get_dev_id_error_t {
    GET_DEV_ID_SUCCESS,
    GET_DEV_ID_ERROR,
    CRSPACE_READ_ERROR,
    CHECK_PTR_DEV_ID,
} dev_id_error;

static int dm_get_device_id_inner(mfile *mf,
                                 dm_dev_id_t *ptr_dm_dev_id,
                                 u_int32_t *ptr_hw_dev_id,
                                 u_int32_t *ptr_hw_rev)
{
    u_int32_t dword = 0;
    int rc;
    u_int32_t dev_flags;

    //Special case: FPGA device:
#ifndef MST_UL
    if (mf->tp == MST_FPGA_ICMD || mf->tp == MST_FPGA_DRIVER) {
        *ptr_dm_dev_id = DeviceFPGANewton;
        *ptr_hw_dev_id = 0xfff;
        return GET_DEV_ID_SUCCESS;
    }
#endif
#ifdef CABLES_SUPP
    if (mf->tp == MST_LINKX_CHIP){
 
        switch (mf->linkx_chip_devid){
            case ARDBEG_REV0_DEVID:
            case ARDBEG_REV1_DEVID:
            case ARDBEG_MIRRORED_DEVID:
                *ptr_dm_dev_id = DeviceArdbeg;
                break;
            case BARITONE_DEVID:
            case BARITONE_MIRRORED_DEVID:
                *ptr_dm_dev_id = DeviceBaritone;
                break;
            case MENHIT_DEVID_VER0:
            case MENHIT_DEVID_VER1:
            case MENHIT_DEVID_VER2:
                *ptr_dm_dev_id = DeviceMenhit;
                break;
            default:
                return GET_DEV_ID_ERROR;
                break;
        }
        *ptr_hw_dev_id = (u_int32_t)mf->linkx_chip_devid;
        return GET_DEV_ID_SUCCESS;

    }

    if (mf->tp == MST_CABLE) {
        //printf("-D- Getting cable ID\n");
        if (mread4(mf, CABLEID_ADDR, &dword) != 4) {
            //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
            return GET_DEV_ID_ERROR;
        }
        //dword = __cpu_to_le32(dword); // Cable pages are read in LE, no need to swap
        *ptr_hw_dev_id = 0xffff;
        u_int8_t id = EXTRACT(dword, 0, 8);
        enum dm_dev_type cbl_type = getCableType(id);
        u_int8_t paging;
        if (cbl_type == DM_QSFP_CABLE) {
            // Get Byte 2 bit 2 ~ bit 18 (flat_mem : upper memory flat or paged. 0=paging, 1=page 0 only)
            paging = EXTRACT(dword, 18, 1);
            //printf("DWORD: %#x, paging: %d\n", dword, paging);
            if (paging == 0) {
                *ptr_dm_dev_id = DeviceCableQSFPaging;
            } else {
                *ptr_dm_dev_id = DeviceCableQSFP;
            }
        } else if (cbl_type == DM_SFP_CABLE) {
            *ptr_dm_dev_id = DeviceCableSFP;
            if (mread4(mf, SFP_DIGITAL_DIAGNOSTIC_MONITORING_IMPLEMENTED_ADDR, &dword) != 4) {
                //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
                return GET_DEV_ID_ERROR;
            }
            u_int8_t byte = EXTRACT(dword, 6, 1); //Byte 92 bit 6 (digital diagnostic monitoring implemented)
            if (byte) {
                *ptr_dm_dev_id = DeviceCableSFP51;
                if (mread4(mf, SFP_PAGING_IMPLEMENTED_INDICATOR_ADDR, &dword) != 4) {
                    //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
                    return GET_DEV_ID_ERROR;
                }
                byte = EXTRACT(dword, 4, 1); //Byte 64 bit 4 (paging implemented indicator)
                if (byte) {
                    *ptr_dm_dev_id = DeviceCableSFP51Paging;
                }
            }
        } else if (cbl_type == DM_CMIS_CABLE) {
            // Get Byte 2 bit 7 ~ bit 23 (flat_mem : upper memory flat or paged. 0=paging, 1=page 0 only)
            paging = EXTRACT(dword, 23, 1);
            if (paging == 0) {
                *ptr_dm_dev_id = DeviceCableCMISPaging;
            } else {
                *ptr_dm_dev_id = DeviceCableCMIS;
            }
        } else {
            *ptr_dm_dev_id = DeviceUnknown;
        }
        return GET_DEV_ID_SUCCESS;
    }
#endif


    rc = mget_mdevs_flags(mf, &dev_flags);
    if (rc) {
        dev_flags = 0;
    }
    // get hw id
    // Special case for MLNX OS getting dev_id using REG MGIR
    if (dev_flags & MDEVS_MLNX_OS) {
        reg_access_status_t rc;
        struct reg_access_hca_mgir mgir;
        memset(&mgir, 0, sizeof(mgir));
        rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
        //printf("-D- RC[%s] -- REVID: %d -- DEVID: %d hw_dev_id: %d\n", m_err2str(rc), mgir.HWInfo.REVID, mgir.HWInfo.DEVID, mgir.HWInfo.hw_dev_id);
        if (rc) {
            dword = get_entry(DeviceSwitchX)->hw_dev_id;
            *ptr_hw_rev    = 0;
            *ptr_hw_dev_id = get_entry(DeviceSwitchX)->hw_dev_id;
        } else {
            dword = mgir.hw_info.hw_dev_id;
            if (dword == 0) {
                dword = get_entry(DeviceSwitchX)->hw_dev_id;
                *ptr_hw_dev_id = get_entry(DeviceSwitchX)->hw_dev_id;
                *ptr_hw_rev = mgir.hw_info.device_hw_revision & 0xf;
            } else {
                *ptr_hw_dev_id = dword;
                *ptr_hw_rev = 0; //WA: MGIR should have also hw_rev_id and then we can use it.
            }
        }
    } else {
        if (mread4(mf, DEVID_ADDR, &dword) != 4) {
            return CRSPACE_READ_ERROR;
        }

        *ptr_hw_dev_id = EXTRACT(dword, 0, 16);
        *ptr_hw_rev    = EXTRACT(dword, 16, 8);
    }

    *ptr_dm_dev_id = get_entry_by_dev_rev_id(*ptr_hw_dev_id, *ptr_hw_rev)->dm_id;
    return CHECK_PTR_DEV_ID;
}

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id(mfile *mf,
                     dm_dev_id_t *ptr_dm_dev_id,
                     u_int32_t *ptr_hw_dev_id,
                     u_int32_t *ptr_hw_rev)
{
    int return_value = 1;
    return_value = dm_get_device_id_inner(mf, ptr_dm_dev_id,
                                          ptr_hw_dev_id, ptr_hw_rev);
    if (return_value == CRSPACE_READ_ERROR) {
        printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
        return GET_DEV_ID_ERROR;
    } else if (return_value == CHECK_PTR_DEV_ID) {
        if (*ptr_dm_dev_id == DeviceUnknown) {

// Due to issue 2719128, we prefer to skip this device
// and not filter using the 'pciconf' FreeBSD tool
#ifndef __FreeBSD__
            /* Dev id not matched in array */
            printf("FATAL - Can't find device id.\n");
#endif
            return MFE_UNSUPPORTED_DEVICE;
        }
        return GET_DEV_ID_SUCCESS;
    }
    return return_value;
}

// Due to issue 2846942, added this function to be used on mdevices)
int dm_get_device_id_without_prints(mfile *mf,
                                    dm_dev_id_t *ptr_dm_dev_id,
                                    u_int32_t *ptr_hw_dev_id,
                                    u_int32_t *ptr_hw_rev)
{
    int return_value = 1;
    return_value = dm_get_device_id_inner(mf, ptr_dm_dev_id,
                                          ptr_hw_dev_id, ptr_hw_rev);
    if (return_value == CHECK_PTR_DEV_ID) {
        if (*ptr_dm_dev_id == DeviceUnknown) {
            return MFE_UNSUPPORTED_DEVICE;
        }
        return GET_DEV_ID_SUCCESS;
    }
    return return_value;
}

int dm_get_device_id_offline(u_int32_t devid,
                             u_int32_t chip_rev,
                             dm_dev_id_t *ptr_dev_type)
{
    *ptr_dev_type = get_entry_by_dev_rev_id(devid, chip_rev)->dm_id;
    return *ptr_dev_type == DeviceUnknown ? MFE_UNSUPPORTED_DEVICE: MFE_OK;
}

const char* dm_dev_type2str(dm_dev_id_t type)
{
    return get_entry(type)->name;
}

dm_dev_id_t dm_dev_str2type(const char *str)
{
    const struct device_info *p = g_devs_info;
    if (!str) {
        return DeviceUnknown;
    }
    while (p->dm_id != DeviceUnknown) {
        if (strcmp(str, p->name) == 0) {
            return p->dm_id;
        }
        p++;
    }
    return DeviceUnknown;
}

int dm_get_hw_ports_num(dm_dev_id_t type)
{
    return get_entry(type)->port_num;
}

int dm_dev_is_hca(dm_dev_id_t type)
{
    return get_entry(type)->dev_type == DM_HCA;
}

int dm_dev_is_200g_speed_supported_hca(dm_dev_id_t type)
{
    bool isBlueField = (type == DeviceBlueField || type == DeviceBlueField2 || type == DeviceBlueField3);
    return !isBlueField && (dm_dev_is_hca(type) && (get_entry(type)->hw_dev_id >= get_entry(DeviceConnectX6)->hw_dev_id));
}

int dm_dev_is_switch(dm_dev_id_t type)
{
    return get_entry(type)->dev_type == DM_SWITCH;
}

int dm_dev_is_200g_speed_supported_switch(dm_dev_id_t type)
{
    return (dm_dev_is_switch(type) && (get_entry(type)->hw_dev_id >= get_entry(DeviceQuantum)->hw_dev_id));
}

int dm_dev_is_bridge(dm_dev_id_t type)
{
    return get_entry(type)->dev_type == DM_BRIDGE;
}

int dm_dev_is_qsfp_cable(dm_dev_id_t type) {
    return get_entry(type)->dev_type == DM_QSFP_CABLE;
}

int dm_dev_is_sfp_cable(dm_dev_id_t type) {
    return get_entry(type)->dev_type == DM_SFP_CABLE;
}

int dm_dev_is_cmis_cable(dm_dev_id_t type) {
    return get_entry(type)->dev_type == DM_CMIS_CABLE;
}

int dm_dev_is_cable(dm_dev_id_t type)
{
    return (dm_dev_is_qsfp_cable(type) || dm_dev_is_sfp_cable(type) || dm_dev_is_cmis_cable(type));
}

u_int32_t dm_get_hw_dev_id(dm_dev_id_t type)
{
    return get_entry(type)->hw_dev_id;
}

u_int32_t dm_get_hw_rev_id(dm_dev_id_t type)
{
    return get_entry(type)->hw_rev_id;
}

int dm_is_fpp_supported(dm_dev_id_t type)
{
    // Function per port is supported only in HCAs that arrived after CX3
    const struct device_info *dp = get_entry(type);
    return (dm_is_5th_gen_hca(dp->dm_id) || dm_is_newton(dp->dm_id));
}

int dm_is_device_supported(dm_dev_id_t type)
{
    return get_entry(type)->dm_id != DeviceUnknown;
}

int dm_is_livefish_mode(mfile *mf)
{
    if (!mf || !mf->dinfo) {
        return 0;
    }
    if (mf->tp == MST_SOFTWARE) {
        return 1;
    }
    dm_dev_id_t devid_t = DeviceUnknown;
    u_int32_t devid = 0;
    u_int32_t revid = 0;
    int rc = dm_get_device_id(mf, &devid_t, &devid, &revid);
    if (rc) {
        // Could not detrmine , by default is not livefish
        return 0;
    }
    u_int32_t swid = mf->dinfo->pci.dev_id;
    //printf("-D- swid: %#x, devid: %#x\n", swid, devid);
    if (dm_is_4th_gen(devid_t) || dm_is_switchx(devid_t)) {
        return (devid == swid - 1);
    } else {
        return (devid == swid);
    }

    return 0;
}

int dm_is_4th_gen(dm_dev_id_t type)
{
    return (type == DeviceConnectX2 ||
            type == DeviceConnectX3 ||
            type == DeviceConnectX3Pro);
}

int dm_is_5th_gen_hca(dm_dev_id_t type)
{
    return (dm_dev_is_hca(type) && !dm_is_4th_gen(type));
}

int dm_is_newton(dm_dev_id_t type)
{
    return (type == DeviceFPGANewton);
}

int dm_is_connectib(dm_dev_id_t type)
{
    return (type == DeviceConnectIB);
}

int dm_is_switchx(dm_dev_id_t type)
{
    return (type == DeviceSwitchX);
}

int dm_is_new_gen_switch(dm_dev_id_t type)
{
    return (dm_dev_is_switch(type) && !dm_is_switchx(type));
}

int dm_dev_is_raven_family_switch(dm_dev_id_t type)
{
    return (dm_dev_is_switch(type) && (type == DeviceQuantum || type == DeviceQuantum2 || type == DeviceSpectrum2 || type == DeviceSpectrum3 || type == DeviceSpectrum4));
}

int dm_dev_is_ib_switch(dm_dev_id_t type)
{
    return (dm_dev_is_switch(type) && (type == DeviceQuantum || type == DeviceQuantum2 || type == DeviceSwitchIB || type == DeviceSwitchIB2));
}

