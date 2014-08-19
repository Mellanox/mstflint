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
 */

#ifndef MTCR_H
#define MTCR_H


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

typedef enum MError {
    ME_OK = 0,
    ME_ERROR,
    ME_BAD_PARAMS,
    ME_CR_ERROR,
    ME_NOT_IMPLEMENTED,
    ME_SEM_LOCKED,
    ME_MEM_ERROR,

    ME_MAD_SEND_FAILED,
    ME_UNKOWN_ACCESS_TYPE,
    ME_UNSUPPORTED_DEVICE,
    ME_REG_NOT_SUPPORTED,

    // errors regarding REG_ACCESS
    ME_REG_ACCESS_OK = 0,
    ME_REG_ACCESS_BAD_STATUS_ERR = 0x100,
    ME_REG_ACCESS_BAD_METHOD,
    ME_REG_ACCESS_NOT_SUPPORTED,
    ME_REG_ACCESS_DEV_BUSY,
    ME_REG_ACCESS_VER_NOT_SUPP,
    ME_REG_ACCESS_UNKNOWN_TLV,
    ME_REG_ACCESS_REG_NOT_SUPP,
    ME_REG_ACCESS_CLASS_NOT_SUPP,
    ME_REG_ACCESS_METHOD_NOT_SUPP,
    ME_REG_ACCESS_BAD_PARAM,
    ME_REG_ACCESS_RES_NOT_AVLBL,
    ME_REG_ACCESS_MSG_RECPT_ACK,
    ME_REG_ACCESS_UNKNOWN_ERR,
    ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT,
    ME_REG_ACCESS_CONF_CORRUPT,
    ME_REG_ACCESS_LEN_TOO_SMALL,
    ME_REG_ACCESS_BAD_CONFIG,
    ME_REG_ACCESS_ERASE_EXEEDED,

    // errors regarding ICMD
    ME_ICMD_STATUS_CR_FAIL = 0x200,       // cr-space access failure
    ME_ICMD_INVALID_OPCODE,
    ME_ICMD_INVALID_CMD,
    ME_ICMD_OPERATIONAL_ERROR,
    ME_ICMD_BAD_PARAM,
    ME_ICMD_BUSY,
    ME_ICMD_INIT_FAILED,
    ME_ICMD_NOT_SUPPORTED,
    ME_ICMD_STATUS_SEMAPHORE_TO,          // timed out while trying to take semaphore
    ME_ICMD_STATUS_EXECUTE_TO,            // timed out while waiting for command to execute
    ME_ICMD_STATUS_IFC_BUSY,
    ME_ICMD_STATUS_ICMD_NOT_READY,
    ME_ICMD_UNSUPPORTED_ICMD_VERSION,
    ME_ICMD_UNKNOWN_STATUS,
    ME_ICMD_ICM_NOT_AVAIL,
    ME_ICMD_WRITE_PROTECT,

    //errors regarding Tools CMDIF
    ME_CMDIF_BUSY = 0x300,
    ME_CMDIF_TOUT,
    ME_CMDIF_BAD_STATUS,
    ME_CMDIF_BAD_OP,
    ME_CMDIF_NOT_SUPP,
    ME_CMDIF_BAD_SYS,
    ME_CMDIF_UNKN_TLV,

    //errors regarding MAD IF
    ME_MAD_BUSY = 0x400,
    ME_MAD_REDIRECT,
    ME_MAD_BAD_VER,
    ME_MAD_METHOD_NOT_SUPP,
    ME_MAD_METHOD_ATTR_COMB_NOT_SUPP,
    ME_MAD_BAD_DATA,
    ME_MAD_GENERAL_ERR,

    ME_LAST
} MError;

typedef enum Mdevs_t {
    MDEVS_GAMLA     = 0x01, /*  Each device that actually is a Gamla */
    MDEVS_I2CM      = 0x02, /*  Each device that can work as I2C master */
    MDEVS_MEM       = 0x04, /*  Each device that is a memory driver (vtop) */
    MDEVS_TAVOR_DDR = 0x08, /*  Each device that maps to DDR */
    MDEVS_TAVOR_UAR = 0x10, /*  Each device that maps to UAR */
    MDEVS_TAVOR_CR  = 0x20, /*  Each device that maps to CR */
    MDEVS_IF        = 0x40, /*  Standard device  interface */
    MDEVS_REM       = 0x80, /*  Remote devices */
    MDEVS_PPC       = 0x100, /*  PPC devices */
    MDEVS_DEV_I2C   = 0x200, /* Generic linux kernel i2c device */
    MDEVS_IB        = 0x400, /* Cr access over IB Mads */
    MDEVS_MLNX_OS   = 0x800, /* access by CmdIf in MlnxOS */
    MDEVS_FWCTX		= 0x900, /*access by UEFI func/context */
    MDEVS_TAVOR     = (MDEVS_TAVOR_DDR|MDEVS_TAVOR_UAR|MDEVS_TAVOR_CR),
    MDEVS_ALL       = 0xffffffff
} Mdevs;
typedef struct mfile_t mfile;

typedef enum {
    MACCESS_REG_METHOD_GET = 1,
    MACCESS_REG_METHOD_SET = 2
} maccess_reg_method_t;

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

typedef enum {
    RA_MFPA=0x9010,
    RA_MFBA=0x9011,
    RA_MFBE=0x9012,
} reg_access_t;

typedef enum mtcr_access_method {
    MTCR_ACCESS_ERROR  = 0x0,
    MTCR_ACCESS_MEMORY = 0x1,
    MTCR_ACCESS_CONFIG = 0x2,
    MTCR_ACCESS_INBAND = 0x3
} mtcr_access_method_t;
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
void mdevices_info_destroy(dev_info* dev_info, int len);

int mget_mdevs_type(mfile *mf, u_int32_t *mtype);

/*
 * Open Mellanox Software tools (mst) driver. Device type==INFINIHOST
 * Return valid mfile ptr or 0 on failure
 */
mfile *mopen(const char *name);

mfile *mopend(const char *name, int type);

mfile *mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func);

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf);

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave);

int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags);

int maccess_reg_mad(mfile *mf, u_int8_t *data);

int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type);

int maccess_reg_cmdif(mfile *mf, reg_access_t reg_access, void *reg_data, u_int32_t cmd_type);

int maccess_reg(mfile     *mf,
                u_int16_t  reg_id,
                maccess_reg_method_t reg_method,
                void*      reg_data,
                u_int32_t  reg_size,
                u_int32_t	r_size_reg, // used when sending via icmd interface (how much data should be read back to the user)
                u_int32_t	w_size_reg, // used when sending via icmd interface (how much data should be written to the scratchpad)
                         	 	 	    // if you dont know what you are doing then r_size_reg = w_size_reg = your_register_size
                int       *reg_status);

int icmd_send_command(mfile *mf, int opcode, void* data, int data_size, int skip_write);

int icmd_clear_semaphore(mfile *mf);

int mget_max_reg_size(mfile *mf);

const char* m_err2str(MError status);

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);
int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len);

int tools_cmdif_query_dev_cap(mfile *mf, u_int32_t offset, u_int64_t* data);

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "mlx4_0"
#define DEV_MST_EXAMPLE2 "03:00.0"

#endif
