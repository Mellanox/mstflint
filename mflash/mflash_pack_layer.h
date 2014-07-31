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
 */
/*
 * mflash_inband.h
 *
 *  Created on: Jul 6, 2011
 *      Author: mohammad
 */

#ifndef MFLASH_COMMON_H_
#define MFLASH_COMMON_H_

#include "mflash_common_structs.h"

#define NEAREST_POW2(num)\
	(num) < (256) ? ((num) < (128)? ((num) < (64) ? ((num) < (32) ? (16): (32)): (64)): (128)): (256);

#ifndef CHECK_RC
    #define CHECK_RC(rc) do {if (rc) return rc;} while(0)
#endif

#ifndef ARR_SIZE
    #define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#endif

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
/////////////////////////////////////////////
//
// MFlash struct
//
/////////////////////////////////////////////
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

	// Relevant for SPI flash (InfiniHostIIILx, ConnectX) only
	f_st_spi_status f_spi_status;
	// when set(1) we support modification of the flash status register
	u_int8_t supp_sr_mod;

	int             curr_bank;
	int             is_locked;
	// if writer_lock is set, semaphore should be freed only in mf_close()/disable_hw_access()
	int             writer_lock;

	flash_attr      attr;

	int             opts[MFO_LAST];
	char            last_err_str[MFLASH_ERR_STR_SIZE];

	u_int8_t   access_type; //0 = mfile , 1 = uefi

};

enum AccessTypeByMfile{
    ATBM_NO = 0,
    ATBM_INBAND,
    ATBM_MLNXOS_CMDIF,
    ATBM_ICMD,
};

/*
#ifndef __WIN__

#ifdef __FreeBSD__
#define SWAPL(l) ntohl(l)
#include <sys/endian.h>
#else // Linux
#include <byteswap.h>
#include <endian.h>

#define SWAPL(l) bswap_32(l)
#endif

#else

#include <io.h>
#include <Winsock2.h>
#define SWAPL(l) ntohl(l)
#define __BYTE_ORDER __LITTLE_ENDIAN
*/

/*
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS
#define inline __inline
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS
*/
//#endif

/*
#ifndef __cpu_to_le32

#if __BYTE_ORDER == __LITTLE_ENDIAN
    #define __cpu_to_le32(x) (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
    #define __cpu_to_le32(x) SWAPL(x)
#endif // __BYTE_ORDER

#endif

#ifndef __le32_to_cpu
    #define __le32_to_cpu(x) __cpu_to_le32(x)
#endif
*/

#define WRITE_CHECK_ALLIGN(addr, block_write, size) {\
    if (addr & ((u_int32_t)block_write - 1)) {\
        return MFE_BAD_ALIGN;\
    }\
    if (size & ((u_int32_t)block_write - 1)) {\
         return MFE_BAD_ALIGN;\
    }\
}

#define COM_CHECK_ALLIGN(flash_addr, size) {\
    if (flash_addr & (size - 1 )) {\
        return MFE_BAD_ALIGN;\
    }\
}

//////////////////////////////////// SX FLASH functions ////////////////////////////////////

typedef u_int32_t (*f_reg_pack)   (void *data_to_pack,  u_int8_t *packed_buffer);
typedef void      (*f_reg_unpack) (void *unpacked_data, u_int8_t *buffer_to_unpack);
typedef void      (*f_reg_dump)   (void *data_to_print, FILE *out_port);

int sx_st_block_access(mfile *mf, u_int32_t flash_addr, u_int8_t bank, u_int32_t size, u_int8_t* data,\
		u_int8_t method);


int common_erase_sector(mfile *mf, u_int32_t addr, u_int8_t flash_bank);

int run_mfpa_command(mfile *mf, u_int8_t access_cmd, u_int8_t flash_bank, u_int32_t boot_address, u_int32_t *jedec_p);

int com_get_jedec(mfile *mf, u_int8_t flash_bank, u_int32_t *jedec_p);
int get_info_from_jededc_id(u_int32_t jededc_id, u_int8_t *vendor, u_int8_t* type, u_int8_t* capacity);
int get_type_index_by_vendor_and_type(u_int8_t vendor, u_int8_t type, unsigned *type_index);
int get_log2size_by_capcity(unsigned type_index, u_int8_t capacity, int *log2size);
int get_max_reg_size(mfile *mf);

int set_bank(mflash* mfl, u_int32_t addr);
int get_flash_offset(u_int32_t addr, int log2_bank_size, u_int32_t *flash_addr_p);
int mfl_get_bank_info(mflash *mfl, u_int32_t addr, u_int32_t *flash_off_p, int *bank_p);

#endif /* MFLASH_COMMON_H_ */
