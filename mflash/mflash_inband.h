
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

#ifndef MFLASH_INBAND_H_
#define MFLASH_INBAND_H_

#include <mtcr.h>
#include "mflash_common.h"

int mfi_reg_access_mad(flash_access_t *faccess, u_int16_t reg_id, u_int8_t method, void *reg, u_int8_t debug);

int mfi_erase_sector(mfile *mf, u_int32_t addr, u_int8_t flash_bank);

int mfi_get_jedec(mfile *mf, u_int8_t flash_bank, u_int32_t *jedec_p);

int mfi_read_block(mfile *mf, u_int32_t addr, u_int8_t flash_bank, u_int32_t size, u_int8_t* data);

int mfi_write_block(mfile *mf, u_int32_t blk_addr, u_int8_t flash_bank, u_int32_t size, u_int8_t* data);

int mfi_flash_lock(mfile *mf, int lock_state);

int mfi_update_boot_addr(mfile *mf, u_int8_t flash_bank, u_int32_t boot_addr);

#endif /* MFLASH_INBAND_H_ */
