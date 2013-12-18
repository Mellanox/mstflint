
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

/*
 * mflash_inband.h
 *
 *  Created on: Jul 6, 2011
 *      Author: mohammad
 */

#ifndef MFLASH_ACCESS_LAYER_H_
#define MFLASH_ACCESS_LAYER_H_

#include <mtcr.h>

#ifndef IRISC
#define MFLASH_ERR_STR_SIZE 1024
#else
#define MFLASH_ERR_STR_SIZE    4
#endif


typedef int (*f_mf_lock)      (mflash* mfl, int lock_state);

typedef int (*f_mf_set_bank)  (mflash* mfl, u_int32_t bank);
typedef int (*f_mf_read)      (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
typedef int (*f_mf_write)     (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
typedef int (*f_mf_erase_sect)(mflash* mfl, u_int32_t addr);
typedef int (*f_mf_reset)     (mflash* mfl);

typedef int (*f_st_spi_status)(mflash* mfl, u_int8_t op_type, u_int8_t* status);
typedef int (*f_mf_get_info)  (mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash);

struct mflash {
#ifndef IRISC
    mfile*      mf;
#endif

    // Functions:
    f_mf_lock       f_lock;

    f_mf_set_bank   f_set_bank;
    f_mf_get_info   f_get_info;

    f_mf_read       f_read;
    f_mf_write      f_write;
    f_mf_write      f_write_blk;   // write and write_block have the same signateure, but theyr'e not the same func !
    f_mf_read       f_read_blk;    // read  and read_block have the same signateure, but theyr'e not the same func !
    f_mf_erase_sect f_erase_sect;
    f_mf_reset      f_reset;

    // Relevant for SPI flash (InfiniHostIIILx, ConnectX) only.
    f_st_spi_status f_spi_status;

    int             curr_bank;
    int             is_locked;

    flash_attr      attr;

    int             opts[MFO_LAST];
    char            last_err_str[MFLASH_ERR_STR_SIZE];

    u_int8_t   access_type;
    uefi_Dev_t *uefi_dev;
    f_fw_cmd   uefi_cmd_func;

    gcif_dev_t *cif_dev;
    void* cmdif_context;

};


int sx_get_flash_info_by_type(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash);
int sx_block_read_by_type(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data);
int sx_block_write_by_type(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data);
int sx_flash_lock_by_type(mflash* mfl, int lock_state);
int sx_erase_sect_by_type(mflash* mfl, u_int32_t addr);
int mf_update_boot_addr_by_type(mflash* mfl, u_int32_t boot_addr);
int maccess_reg_mad_wrapper(flash_access_t *facces, u_int8_t *data, int w_cmdif_size, int r_cmdif_size);


#endif /* MFLASH_ACCESS_LAYER_H_ */
