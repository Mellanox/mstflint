/*
 *
 *  mtcr.h - Mellanox Software tools (mst) driver definitions
 *
 * Author: Michael S. Tsirkin <mst@mellanox.co.il>
 *
 * Copyright (c) 2006 Mellanox Technologies Ltd.  All rights reserved.
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
 */

#ifndef _MTCR_UL_
#define _MTCR_UL_


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

typedef enum Mdevs_t {
    MDEVS_GAMLA     = 0x01, /*  Each device that actually is a Gamla */
    MDEVS_I2CM      = 0x02, /*  Each device that can work as I2C master */
    MDEVS_MEM       = 0x04, /*  Each device that is a memory driver (vtop) */
    MDEVS_TAVOR_DDR = 0x08, /*  Each device that maps to Tavor DDR */
    MDEVS_TAVOR_UAR = 0x10, /*  Each device that maps to Tavor UAR */
    MDEVS_TAVOR_CR  = 0x20, /*  Each device that maps to Tavor CR */
    MDEVS_IF        = 0x40, /*  Standard device  interface */
    MDEVS_REM       = 0x80, /*  Remote devices */
    MDEVS_PPC       = 0x100, /*  PPC devices */
    MDEVS_DEV_I2C   = 0x200, /* Generic linux kernel i2c device */
    MDEVS_IB        = 0x400, /* Cr access over IB Mads */
    MDEVS_MLNX_OS   = 0x800, /* access by CmdIf in MlnxOS */
    MDEVS_TAVOR     = (MDEVS_TAVOR_DDR|MDEVS_TAVOR_UAR|MDEVS_TAVOR_CR),
    MDEVS_ALL       = 0xffffffff
} Mdevs;

typedef struct mfile_t mfile;

typedef struct dev_info_t
{
    Mdevs         type;
    char          dev_name[512];

    union {
        struct {
            u_int16_t domain;
            u_int8_t  bus;
            u_int8_t  dev;
            u_int8_t  func;

            u_int16_t dev_id;
            u_int16_t vend_id;
            u_int32_t class_id;
            u_int16_t subsys_id;
            u_int16_t subsys_vend_id;

            char      cr_dev[512];
            char      conf_dev[512];
            char**    net_devs;      // Null terminated array
            char**    ib_devs;       // Null terminated array
        } pci;

        struct {
            u_int32_t TBD;
        } usb;

        struct {
            u_int32_t TBD;
        } ib;

        struct {
            u_int32_t TBD;
        } remote;
    };
} dev_info;


/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4(mfile *mf, unsigned int offset, u_int32_t *value);

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4(mfile *mf, unsigned int offset, u_int32_t value);


int mread4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);
int mwrite4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len);

int msw_reset(mfile *mf);

/*
 * Get list of MST (Mellanox Software Tools) devices.
 * Put all device names as null-terminated strings to buf.
 *
 * Return number of devices found or -1 if buf overflow
 */
int mdevices(char *buf, int len, int mask);


/*
 * Get list of MST (Mellanox Software Tools) devices info records.
 * Return a dynamic allocated array of dev_info records.
 * len will be updated to hold the array length
 *
 */
dev_info* mdevices_info(int mask, int* len);

void mdevice_info_destroy(dev_info* dev_info, int len);

/*
 * Open Mellanox Software tools (mst) driver. Device type==TAVOR
 * Return valid mfile ptr or 0 on failure
 */
mfile *mopen(const char *name);

mfile *mopend(const char *name, int type);

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf);

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave);

int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags);

int maccess_reg_mad(mfile *mf, u_int8_t *data);
int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type);

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);
int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "mlx4_0"
#define DEV_MST_EXAMPLE2 "03:00.0"

#endif
