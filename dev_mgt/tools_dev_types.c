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

enum dm_dev_type {
    DM_UNKNOWN = -1,
    DM_HCA,
    DM_SWITCH,
    DM_BRIDGE,
    DM_QSFP_CABLE,
    DM_SFP_CABLE,
};

struct dev_info {
    dm_dev_id_t      dm_id;
    u_int16_t        hw_dev_id;
    int              hw_rev_id;  /* -1 means all revisions match this record */
    int              sw_dev_id;  /* -1 means all hw ids  match this record */
    const char*      name;
    int              port_num;
    enum dm_dev_type dev_type;
};

#define DEVID_ADDR                          0xf0014
#define CABLEID_ADDR                        0x0
#define SFP_51_ADDR                         92
#define SFP_51_PAGING_ADDR                  64

#ifdef CABLES_SUPP
enum dm_dev_type getCableType(u_int8_t id) {
    switch (id) {
        case 0xd:
        case 0x11:
        case 0xe:
        case 0xc:
            return DM_QSFP_CABLE;
        case 0x3:
            return DM_SFP_CABLE;
        default:
            return DM_UNKNOWN;
    }
}
#endif

static struct dev_info g_devs_info[] = {
    {
        .dm_id     = DeviceInfiniScaleIV,
        .hw_dev_id = 0x01b3,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "InfiniScaleIV",
        .port_num  = 36,
        .dev_type  = DM_SWITCH
    },
    {
        .dm_id     = DeviceSwitchX,
        .hw_dev_id = 0x0245,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "SwitchX",
        .port_num  = 64,
        .dev_type  = DM_SWITCH
    },
    {
        .dm_id     = DeviceConnectX2,
        .hw_dev_id = 0x190,
        .hw_rev_id = 0xb0,
        .sw_dev_id = -1,
        .name      = "ConnectX2",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },

    {
        .dm_id     = DeviceConnectX3,
        .hw_dev_id = 0x1f5,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectX3",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceConnectIB,
        .hw_dev_id = 0x1ff,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectIB",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceConnectX3Pro,
        .hw_dev_id = 0x1f7,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectX3Pro",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceSwitchIB,
        .hw_dev_id = 0x247,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "SwitchIB",
        .port_num  = 36,
        .dev_type  = DM_SWITCH
    },
    {
        .dm_id     = DeviceSpectrum,
        .hw_dev_id = 0x249,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Spectrum",
        .port_num  = 64,
        .dev_type  = DM_SWITCH
    },
    {
        .dm_id     = DeviceConnectX4,
        .hw_dev_id = 0x209,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectX4",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceConnectX4LX,
        .hw_dev_id = 0x20b,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectX4LX",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceConnectX5,
        .hw_dev_id = 0x20d,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "ConnectX5",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceFPGANewton,
        .hw_dev_id = 0xfff, // Dummy device ID till we have official one
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "FPGA_NEWTON",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceSwitchIB2,
        .hw_dev_id = 0x24b,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "SwitchIB2",
        .port_num  = 36,
        .dev_type  = DM_SWITCH
    },
    {
        .dm_id     = DeviceCableQSFP,
        .hw_dev_id = 0x0d,
        .hw_rev_id = 0,
        .sw_dev_id = -1,
        .name      = "CableQSFP",
        .port_num  = -1,
        .dev_type  = DM_QSFP_CABLE
    },
    {
        .dm_id     = DeviceCableQSFPaging,
        .hw_dev_id = 0x11,
        .hw_rev_id = 0xab,
        .sw_dev_id = -1,
        .name      = "CableQSFPaging",
        .port_num  = -1,
        .dev_type  = DM_QSFP_CABLE
    },
    {
        .dm_id     = DeviceCableSFP,
        .hw_dev_id = 0x03,
        .hw_rev_id = 1,
        .sw_dev_id = -1,
        .name      = "CableSFP",
        .port_num  = -1,
        .dev_type  = DM_SFP_CABLE
    },
    {
        .dm_id     = DeviceCableSFP51,
        .hw_dev_id = 0x03,
        .hw_rev_id = 1,
        .sw_dev_id = -1,
        .name      = "CableSFP51",
        .port_num  = -1,
        .dev_type  = DM_SFP_CABLE
    },
    {
        .dm_id     = DeviceCableSFP51Paging,
        .hw_dev_id = 0x03,
        .hw_rev_id = 1,
        .sw_dev_id = -1,
        .name      = "CableSFP51Paging",
        .port_num  = -1,
        .dev_type  = DM_SFP_CABLE
    },
    {
        .dm_id     = DeviceDummy,
        .hw_dev_id = 0x1,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "DummyDevice",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceUnknown,
        .hw_dev_id = 0,
        .hw_rev_id = 0,
        .sw_dev_id = 0,
        .name      = "Unknown Device",
        .port_num  = -1,
        .dev_type  = DM_UNKNOWN
    }
};

static const struct dev_info* get_entry(dm_dev_id_t type)
{
    const struct dev_info* p = g_devs_info;
    while (p->dm_id != DeviceUnknown) {
        if (type == p->dm_id) {
            break;
        }
        p++;
    }
    return p;
}

static const struct dev_info* get_entry_by_dev_rev_id(u_int32_t hw_dev_id, u_int32_t hw_rev_id)
{
    const struct dev_info* p = g_devs_info;
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

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id(mfile* mf,
                    dm_dev_id_t* ptr_dm_dev_id,
                    u_int32_t*   ptr_hw_dev_id,
                    u_int32_t*   ptr_hw_rev)
{
    u_int32_t dword;
    int rc;
    u_int32_t dev_flags;

    //Special case: FPGA device:
#ifndef MST_UL
    if (mf->tp == MST_FPGA_ICMD || mf->tp == MST_FPGA_DRIVER) {
       *ptr_dm_dev_id = DeviceFPGANewton;
       *ptr_hw_dev_id = 0xfff;
       return 0;
    }
#endif
#ifdef CABLES_SUPP
    if (mf->tp == MST_CABLE) {
        //printf("-D- Getting cable ID\n");
        if (mread4(mf, CABLEID_ADDR, &dword) != 4)
        {
            //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
            return 1;
        }
        dword = __cpu_to_le32(dword); // Cable pages are in LE
        *ptr_hw_dev_id = 0xffff;
        u_int8_t id = EXTRACT(dword, 0, 8);
        enum dm_dev_type cbl_type = getCableType(id);
        if (cbl_type == DM_QSFP_CABLE) {
            // Get Byte 2 bit 2 ~ bit 18
            u_int8_t paging = EXTRACT(dword, 18, 1);
            //printf("DWORD: %#x, paging: %d\n", dword, paging);
            if (paging == 0) {
                *ptr_dm_dev_id = DeviceCableQSFPaging;
            } else {
                *ptr_dm_dev_id = DeviceCableQSFP;
            }
        } else if (cbl_type == DM_SFP_CABLE) {
            *ptr_dm_dev_id = DeviceCableSFP;
            if (mread4(mf, SFP_51_ADDR, &dword) != 4)
            {
               //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
               return 1;
            }
            u_int8_t byte = EXTRACT(dword, 6, 1); //Byte 92 bit 6
            if (byte) {
                *ptr_dm_dev_id = DeviceCableSFP51;
                if (mread4(mf, SFP_51_PAGING_ADDR, &dword) != 4)
                {
                   //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
                   return 1;
                }
                byte = EXTRACT(dword, 4, 1); //Byte 64 bit 4
                if (byte) {
                    *ptr_dm_dev_id = DeviceCableSFP51Paging;
                }
            }
        } else {
            *ptr_dm_dev_id = DeviceUnknown;
        }
        return 0;
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
        struct register_access_sib_mgir mgir;
        memset(&mgir, 0, sizeof(mgir));
        rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
        //printf("-D- RC[%s] -- REVID: %d -- DEVID: %d hw_dev_id: %d\n", m_err2str(rc), mgir.HWInfo.REVID, mgir.HWInfo.DEVID, mgir.HWInfo.hw_dev_id);
        if (rc) {
            dword = get_entry(DeviceSwitchX)->hw_dev_id;
            *ptr_hw_rev    = 0;
            *ptr_hw_dev_id = get_entry(DeviceSwitchX)->hw_dev_id;
        } else {
            dword = mgir.HWInfo.hw_dev_id;
            if (dword == 0) {
                dword = get_entry(DeviceSwitchX)->hw_dev_id;
                *ptr_hw_dev_id = get_entry(DeviceSwitchX)->hw_dev_id;
                *ptr_hw_rev = mgir.HWInfo.REVID & 0xf;
            } else {
                *ptr_hw_dev_id = dword;
                *ptr_hw_rev = 0; //WA: MGIR should have also hw_rev_id and then we can use it.
            }
        }
    } else {
        if (mread4(mf, DEVID_ADDR, &dword) != 4)
        {
            //printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno));
            return 1;
        }

        *ptr_hw_dev_id = EXTRACT(dword, 0, 16);
        *ptr_hw_rev    = EXTRACT(dword, 16, 8);
    }

    *ptr_dm_dev_id = get_entry_by_dev_rev_id(*ptr_hw_dev_id, *ptr_hw_rev)->dm_id;

    if (*ptr_dm_dev_id == DeviceUnknown) {

        /* Dev id not matched in array */
        //printf("FATAL - Can't find devid id\n");
        return 1; // TODO - fix return vals.
    }
    return 0;
}

int dm_get_device_id_offline(u_int32_t devid,
                             u_int32_t chip_rev,
                             dm_dev_id_t* ptr_dev_type)
{
    *ptr_dev_type = get_entry_by_dev_rev_id(devid, chip_rev)->dm_id;
    return *ptr_dev_type == DeviceUnknown;
}

const char* dm_dev_type2str(dm_dev_id_t type)
{
    return get_entry(type)->name;
}

dm_dev_id_t dm_dev_str2type(const char* str)
{
    const struct dev_info* p = g_devs_info;
    if (!str) {
        return DeviceUnknown;
    }
    while (p->dm_id != DeviceUnknown) {
        if (strcmp(str,p->name) == 0) {
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

int dm_dev_is_hca(dm_dev_id_t type) {
    return get_entry(type)->dev_type == DM_HCA;
}

int dm_dev_is_switch(dm_dev_id_t type)
{
    return get_entry(type)->dev_type == DM_SWITCH;
}

int dm_dev_is_bridge(dm_dev_id_t type)
{
    return get_entry(type)->dev_type == DM_BRIDGE;
}

int dm_dev_is_cable(dm_dev_id_t type)
{
    return (get_entry(type)->dev_type == DM_QSFP_CABLE || get_entry(type)->dev_type == DM_SFP_CABLE);
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
    const struct dev_info* dp = get_entry(type);
    if (
        dp->dm_id == DeviceConnectIB ||
        dp->dm_id == DeviceConnectX4 ||
        dp->dm_id == DeviceConnectX4LX ||
        dp->dm_id == DeviceConnectX5) {
        return 1;
    } else {
        return 0;
    }
}

int dm_is_device_supported(dm_dev_id_t type)
{
    return get_entry(type)->dm_id != DeviceUnknown;
}

int dm_is_livefish_mode(mfile* mf)
{
    if(!mf || !mf->dinfo) {
        return 0;
    }
    dm_dev_id_t devid_t;
    u_int32_t devid = 0;
    u_int32_t revid = 0;
    int rc = dm_get_device_id(mf, &devid_t, &devid, &revid);
    if (rc) {
        // Could not detrmine , by default is not livefish
        return 0;
    }
    u_int32_t swid = mf->dinfo->pci.dev_id;
    //printf("-D- swid: %#x, devid: %#x\n", swid, devid);
    if (devid_t == DeviceConnectX2    ||
        devid_t == DeviceConnectX3    ||
        devid_t == DeviceConnectX3Pro ||
        devid_t == DeviceSwitchX        ) {
        return (devid == swid - 1);
    } else {
        return (devid == swid);
    }

    return 0;
}

