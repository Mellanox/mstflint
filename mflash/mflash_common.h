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

#include <mtcr.h>
#include "internal_packets.h"

#ifndef MST_UL
	#include "cib_cif.h"
#else
	typedef void gcif_dev_t;
#endif

#define CMDIF_MAX_BLOCK_WRITE  128
#define ICMD_MAX_BLOCK_WRITE   128
#define INBAND_MAX_BLOCK_WRITE 32

#ifndef CHECK_RC
    #define CHECK_RC(rc) do {if (rc) return rc;} while(0)
#endif

#ifndef ARR_SIZE
    #define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#endif

enum {
    FWACCESS_INBAND = 0,
    FWACCESS_UEFI,
    FWACCESS_GCIF,
    FWACCESS_ALL,
};

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
/*
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS
#define inline __inline
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS
*/
#endif

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

#ifndef UEFI_BUILD
    #define _ENABLE_MFLASH_INBAND_DEBUG 1
#endif

typedef struct flash_access {
    mfile *mf;
    u_int8_t access_type; // 0 = mf, 1 = uefi
    uefi_Dev_t *uefi_dev;
    f_fw_cmd fw_cmd_func;
    gcif_dev_t *gcif_dev;
} flash_access_t;

enum {
    MAD_METHOD_QUERY = 1,
    MAD_METHOD_WRITE = 2,
};
enum {
    MAD_CLASS_REG_ACCESS = 1,
};
enum {
    TLV_END       = 0,
    TLV_OPERATION = 1,
    TLV_DR        = 2,
    TLV_REG       = 3,
    TLV_USER_DATA = 4,
};
enum {
    REG_ID_MFPA = 0x9010,
    REG_ID_MFBA = 0x9011,
    REG_ID_MFBE = 0x9012,
};

enum {
    RTL_MFPA_LEN = 9,
    RTL_INBAND_MFBA_LEN = 12,
    RTL_MFBA_LEN = 36,
    RTL_MFBE_LEN = 4,
};

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

#define TLV_OPERATION_SIZE 4
#define OP_TLV_SIZE        16
#define REG_RLV_HEADER_LEN 4

//////////////////////////////////// SX FLASH functions ////////////////////////////////////

typedef u_int32_t (*f_reg_pack)   (void *data_to_pack,  u_int8_t *packed_buffer);
typedef void      (*f_reg_unpack) (void *unpacked_data, u_int8_t *buffer_to_unpack);
typedef void      (*f_reg_dump)   (void *data_to_print, FILE *out_port);

typedef struct reg_info {
    u_int16_t    id;
    u_int16_t    len;
    f_reg_pack   pack_func;
    f_reg_unpack unpack_func;
    f_reg_dump   dump_func;
} reg_info_t;


int init_operation_tlv(struct OperationTlv *operation_tlv, u_int16_t reg_id, u_int8_t method);

int get_reg_info_by_id(u_int16_t reg_id, reg_info_t *reg_info);

int sx_st_block_access(flash_access_t *faccess, u_int32_t flash_addr, u_int8_t bank, u_int32_t size, u_int8_t* data,
        u_int8_t method);

int common_erase_sector(flash_access_t *faccess, u_int32_t addr, u_int8_t flash_bank);

int run_mfpa_command(flash_access_t *faccess, u_int8_t access_cmd, u_int8_t flash_bank, u_int32_t boot_address, u_int32_t *jedec_p);

int com_get_jedec(flash_access_t *faccess, u_int8_t flash_bank, u_int32_t *jedec_p);
int get_info_from_jededc_id(u_int32_t jededc_id, u_int8_t *vendor, u_int8_t* type, u_int8_t* capacity);
int get_type_index_by_vendor_and_type(u_int8_t vendor, u_int8_t type, unsigned *type_index);
int get_log2size_by_capcity(unsigned type_index, u_int8_t capacity, int *log2size);
int mfl_get_bank_info(mflash *mfl, u_int32_t addr, u_int32_t *flash_off_p, int *bank_p);

#endif /* MFLASH_COMMON_H_ */
