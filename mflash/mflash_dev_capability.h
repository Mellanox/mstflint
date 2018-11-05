/*
 * mflash_dev_capabillity.h
 *
 *  Created on: Jul 8, 2018
 *      Author: idanme
 */

#ifndef USER_MFLASH_MFLASH_DEV_CAPABILITY_H_
#define USER_MFLASH_MFLASH_DEV_CAPABILITY_H_

#include "mflash_pack_layer.h"


//When (*status != MFE_OK) return value is undefined
int is_four_byte_address_needed(mflash *mfl, MfError *status);
int is_flash_enable_needed(mflash *mfl, MfError *status);
int is_icmdif_supported(mflash *mfl, MfError *status);
int is_supports_sw_reset(mflash *mfl, MfError *status);


#endif /* USER_MFLASH_MFLASH_DEV_CAPABILITY_H_ */
