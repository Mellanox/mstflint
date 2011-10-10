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
 *  tools_dev_types.c - Defines static info records for all mellanox chips in order to
 *                     have a uniform IDs and info for all tools.
 *
 *  Version: $Id$
 *
 *  Author: Wasim Abo Moch (wasim@mellanox.co.il)
 */

#include <stdio.h>
#include <stdlib.h>
#define MTCR_EXPORT /* for mstflint */
#include "tools_dev_types.h"

enum dm_dev_type {
    DM_HCA,
    DM_SWITCH,
    DM_BRIDGE
};

struct dev_info {
    dm_dev_id_t      dm_id;
    u_int16_t        hw_dev_id;
    int              hw_rev_id;  /* -1 means all revisions match this record */
    int              sw_dev_id;  /* -1 means all hw ids  match this record */
    const char*      name;
    const char*      ext_name;
    int              port_num;
    enum dm_dev_type dev_type;
};

#define DEVID_ADDR_ANAFA2       0x60014
#define DEVID_ADDR              0xf0014
#define DM_ARBEL_DEV_VER_ADDR   0x82600

static struct dev_info g_devs_info[] = {
     {
        .dm_id     = DeviceHermonC0,
        .hw_dev_id = 0x1f5,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Kfir",
        .ext_name  = "ConnectX3",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },
    {
        .dm_id     = DeviceBaz,
        .hw_dev_id = 0x0245,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Baz",
        .ext_name  = "SwitchX",
        .port_num  = 64,
        .dev_type  = DM_SWITCH
    },{
        .dm_id     = DeviceDolev,
        .hw_dev_id = 0x17d4,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Dolev",
        .ext_name  = "BridgeX",
        .port_num  = 0, /* TODO */
        .dev_type  = DM_BRIDGE
    },{
        .dm_id     = DeviceShaldag,
        .hw_dev_id = 0x01b3,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Shaldag",
        .ext_name  = "InfiniScaleIV",
        .port_num  = 36,
        .dev_type  = DM_SWITCH
    },{
        .dm_id     = DeviceHermonB0,
        .hw_dev_id = 0x190,
        .hw_rev_id = 0xb0,
        .sw_dev_id = -1,
        .name      = "HermonB0",
        .ext_name  = "ConnectX2",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceHermon,
        .hw_dev_id = 0x190,
        .hw_rev_id = 0xa0,
        .sw_dev_id = -1,
        .name      = "Hermon",
        .ext_name  = "ConnectX",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceSinai,
        .hw_dev_id = 0x6274,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Sinai",
        .ext_name  = "InfiniHostIIILx",
        .port_num  = 1,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceAnafa2,
        .hw_dev_id = 0xb924,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Anafa2",
        .ext_name  = "InfiniScaleIII",
        .port_num  = 24,
        .dev_type  = DM_SWITCH
    },{
        .dm_id     = DeviceArbelMF,
        .hw_dev_id = 0x6278,
        .hw_rev_id = -1,
        .sw_dev_id = 0x6282,
        .name      = "ArbelMF",
        .ext_name  = "InfiniHostIIIEx_MF",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceArbel,
        .hw_dev_id = 0x6278,
        .hw_rev_id = -1,
        .sw_dev_id = 0x6278,
        .name      = "Arbel",
        .ext_name  = "InfiniHostIIIEx",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceTavor,
        .hw_dev_id = 0x5a44,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Tavor",
        .ext_name  = "InfiniHost",
        .port_num  = 2,
        .dev_type  = DM_HCA
    },{
        .dm_id     = DeviceAnafa,
        .hw_dev_id = 0x43132,
        .hw_rev_id = -1,
        .sw_dev_id = -1,
        .name      = "Anafa",
        .ext_name  = "InfiniScale",
        .port_num  = 8,
        .dev_type  = DM_SWITCH
    },{
        .dm_id     = DeviceEndMarker,
    }
};

/**
 * Returns 0 on success and 1 on failure.
 */
int dm_get_device_id(mfile* mf,
                    dm_dev_id_t* ptr_dm_dev_id,
                    u_int32_t*   ptr_hw_dev_id,
                    u_int32_t*   ptr_hw_rev)
{
    u_int32_t dword;
    u_int32_t i;

    #if 1
    for (i = 0; i < DeviceEndMarker; i++) {
        if (g_devs_info[i].dm_id != i) {
            printf("-F- in get_device_type: Wron index of the g_devs_info array. idx %d dev %s\n",
                   i, g_devs_info[i].name);
            exit(1);
        }
    }
    #endif

    if (mread4(mf, DEVID_ADDR, &dword) != 4)
        return 1;

    *ptr_hw_dev_id = EXTRACT(dword, 0, 16);
    *ptr_hw_rev    = EXTRACT(dword, 16, 8);

    for (i = 0; i < DeviceEndMarker; i++) {
        struct dev_info* di = &(g_devs_info[i]);
        if (*ptr_hw_dev_id == di->hw_dev_id) {
            if (di->hw_rev_id == -1 || (int)(*ptr_hw_rev) == di->hw_rev_id) {
                *ptr_dm_dev_id = i;
                break;
            }
        }
    }

    if (i == DeviceEndMarker) {
        /* Special cases - Sinai HW id and Anafa2 devid address. */
        if (*ptr_hw_dev_id == 24204) {
            /* Some old Sinais have hw dev is of 24204 */
            *ptr_dm_dev_id = DeviceSinai;
        } else {
            /* Try Anafa2 devid address */
            if (mread4(mf, DEVID_ADDR_ANAFA2, &dword) != 4)
                return 1;
            if ((int)EXTRACT(dword, 0, 16) == g_devs_info[DeviceAnafa2].hw_dev_id) {
                *ptr_dm_dev_id = DeviceAnafa2;
                *ptr_hw_dev_id = EXTRACT(dword, 0, 16);
                *ptr_hw_rev    = EXTRACT(dword, 16, 8);
            } else {
                /* Dev id not matched in array */
                return 1; // TODO - fix return vals.
            }
        }
    }

    /* Special cases: For Arbel we need to check the SW id as well */
    if (*ptr_hw_dev_id == g_devs_info[DeviceArbel].hw_dev_id) {
        if (mread4(mf, DM_ARBEL_DEV_VER_ADDR, &dword) != 4)
            return 1;

        if (EXTRACT(dword, 16, 16) == 0x25218 ||
            EXTRACT(dword, 16, 16) == 0x25228 ||
            EXTRACT(dword, 16, 16) == 0x25238) {
            *ptr_dm_dev_id = DeviceArbelMF;
        } else {
            *ptr_dm_dev_id = DeviceArbel;
        }
    }

    return 0;
}

int dm_get_device_id_offline(u_int32_t devid,
                             u_int32_t chip_rev,
                             dm_dev_id_t* ptr_dev_type)
{
	dm_dev_id_t i;

    for (i = 0; i < DeviceEndMarker; i++) {
        struct dev_info* di = &(g_devs_info[i]);
        if (devid == di->hw_dev_id) {
            if (di->hw_rev_id == -1 || (int)(chip_rev) == di->hw_rev_id) {
                *ptr_dev_type = i;
                break;
            }
        }
    }

    return i == DeviceEndMarker;
}

const char* dm_dev_type2str(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].name;
    } else {
        return "Unknown Device";
    }
}

const char* dm_dev_type2str_ext(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].ext_name;
    } else {
        return "Unknown Device";
    }
}

int dm_get_hw_ports_num(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].port_num;
    } else {
        return -1;
    }
}

int dm_dev_is_hca(dm_dev_id_t type) {
    if (type < DeviceEndMarker) {
        return g_devs_info[type].dev_type == DM_HCA;
    } else {
        return 0;
    }
}

int dm_dev_is_switch(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].dev_type == DM_SWITCH;
    } else {
        return 0;
    }
}

int dm_dev_is_bridge(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].dev_type == DM_BRIDGE;
    } else {
        return 0;
    }
}

u_int32_t dm_get_hw_dev_id(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].hw_dev_id;
    } else {
        return 0;
    }
}

u_int32_t dm_get_hw_rev_id(dm_dev_id_t type)
{
    if (type < DeviceEndMarker) {
        return g_devs_info[type].hw_rev_id;
    } else {
        return 0;
    }
}
