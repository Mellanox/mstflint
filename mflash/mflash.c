
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



#ifdef IRISC
#include <tavor_mac.h>
#define __cpu_to_be32(val) (val)
#define NULL 0

#else

#include <mtcr.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])

// Bit Slicing macros
#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src,start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))

#define ONES64(size)                    ((size)?(0xffffffffffffffffULL>>(64-(size))):0)
#define MASK64(offset,size)             (ONES64(size)<<(offset))

#define EXTRACT_C64(source,offset,size)   ((((unsigned long long)(source))>>(offset)) & ONES64(size))
#define EXTRACT64(src,start,len)          (((len)==64)?(src):EXTRACT_C64(src,start,len))

#define MERGE_C64(rsrc1,rsrc2,start,len)  ((((u_int64_t)(rsrc2)<<(start)) & (MASK64((start),(len)))) | ((rsrc1) & (~MASK64((start),(len)))))
#define MERGE64(rsrc1,rsrc2,start,len)    (((len)==64)?(rsrc2):MERGE_C64(rsrc1,rsrc2,start,len))

#ifndef __WIN__

#if defined __DJGPP__
//
// DJGPP - GCC PORT TO MS DOS
//

#include <netinet/in.h>
#include <unistd.h>

#define bswap_32(x) ntohl(x)


#else // Linux GCC

#include <byteswap.h>
#include <endian.h>

#endif // __DJGPP__

#define SWAPL(l) bswap_32(l)

#ifndef __cpu_to_be32
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define __cpu_to_be32(val) SWAPL(val)
#else
#define __cpu_to_be32(val) (val)
#endif
#endif
#define OP_NOT_SUPPORTED EOPNOTSUPP

#else // __WIN__

//
// Windows (Under DDK)
//

#include <io.h>
#include <Winsock2.h>
#define SWAPL(l) ntohl(l)
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS
#define inline __inline
#define __cpu_to_be32(val) SWAPL(val) // Win is only run on LE CPUS

#define OP_NOT_SUPPORTED EINVAL

#endif // __WIN__
#endif

#include "mflash.h"

#ifndef __be32_to_cpu
#define __be32_to_cpu(val)  __cpu_to_be32(val)
#endif

#ifndef zero
#define zero 0
#endif

//
// Mellanox Technologies LTD Devices naming/abbreviation convention in this file:
//
// ConnectX         cntx
// ConnectIB        cib


/*
*  Low level operations
*/

/* Flash Functions: */
//typedef struct mflash *mflash;

typedef int (*f_mf_lock)      (mflash* mfl, int lock_state);

typedef int (*f_mf_set_bank)  (mflash* mfl, u_int32_t bank);
typedef int (*f_mf_read)      (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
typedef int (*f_mf_write)     (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
typedef int (*f_mf_erase_sect)(mflash* mfl, u_int32_t addr);
typedef int (*f_mf_reset)     (mflash* mfl);

typedef int (*f_st_spi_status)(mflash* mfl, u_int8_t op_type, u_int8_t* status);
typedef int (*f_mf_get_info)  (mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash);

// This is an interface function when running in IRISC
int mf_open_fw(mflash* mfl, flash_params_t* flash_params);
int cntx_int_spi_get_status_data(mflash* mfl, u_int8_t op_type, u_int32_t* status, u_int8_t data_num);

//
// mflash struct
//
#ifndef IRISC
#define MFLASH_ERR_STR_SIZE 1024
#else
#define MFLASH_ERR_STR_SIZE    4
#endif

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

};


// NOTE: This macro returns ... not nice.
#define CHECK_RC(rc) do {if (rc) return rc;} while(0)

#define ARRSIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#ifdef ESS
#define MREAD4(offs, val)  do {*val=READ_WORD(offs);} while (0)
#define MWRITE4(offs, val) do {WRITE_WORD(offs, val);} while (0)
#else
#define MREAD4(offs, val)  do { if (mread4 (mfl->mf, offs, val) != 4) { \
                                  /*fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), (u_int32_t)errno);*/ \
                  return 2; } /*printf("-D- %s:%d mread4: offs = %#x, val = %#x\n", __FUNCTION__, __LINE__, offs, val);*/\
                                  } while (0)

#define MWRITE4(offs, val) do { if (mwrite4(mfl->mf, offs, val) != 4) { \
                                  /*fprintf(stderr, "-E- Cr write (0x%08x, 0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), (u_int32_t)(val), strerror(errno), (u_int32_t)errno);*/ \
                  mclose(mfl->mf); return 2; } /*printf("-D- %s:%d mwrite4: offs = %#x, val = %#x\n",   __FUNCTION__, __LINE__, offs, val);*/ \
                                  } while (0)
#endif

// Constants:

// General:
#define GPIO_DIR_L       0xf008c
#define GPIO_POL_L       0xf0094
#define GPIO_MOD_L       0xf009c
#define GPIO_DAT_L       0xf0084
#define GPIO_DATACLEAR_L 0xf00d4
#define GPIO_DATASET_L   0xf00dc

#define SEMAP63          0xf03fc

// InfiniHost specific
#define IDLE           0
#define READ4          (1<<29)
#define WRITE1         (2<<29)

#define CR_FLASH       0xf01a4
#define ADDR_MSK       0x7ffffUL
#define CMD_MASK       0xe0000000UL

#define SST_STATUS_REG_VAL   0x80000000
#define ATMEL_STATUS_REG_VAL 0x0

#define CPUMODE_MSK    0xc0000000UL
#define CPUMODE_SHIFT  30
#define CPUMODE        0xf0150

#define SWITCHX_HW_ID 0x245
#define HERMON_HW_ID  0x190
#define CX3_PRO_HW_ID 0x1F7
#define CX3_HW_ID     0x1F5

#define CONNECT_IB_HW_ID 0x1FF

enum FlashConstant {
    FLASH_CMD_CNT  = 5000,      // Number of reads till flash cmd is zeroed
    ERASE_DELAY    = 200000,    // Delay between reads when wating for sector erase
    ERASE_CNT      = 1000000,   // Maximal number of reads when wating for sector erase
    READ_CNT_FAST  = 50000,     // Number of fast reads after write byte
    READ_CNT_SLOW  = 50,        // Number of slow reads after write byte
    READ_DELAY     = 100000,    // Delay between slow reads after write byte
    WR_REPORT_FAST = 256,       // Report frequency when write (fast interfaces)
    WR_REPORT_SLOW = 4,         // Report frequency when write (slow interfaces)
    RD_REPORT_FAST = 4096,      // Report frequency when read (fast interfaces)
    RD_REPORT_SLOW = 64,        // Report frequency when read (slow interfaces)
    GPIO_SEM_TRIES = 1024 ,     // Number of tries to obtain a GPIO sem.
    MAX_WRITE_BUFFER_SIZE = 256 // Max buffer size for buffer write devices
};


enum IntelFlashCommand {
    FC_ReadID      = 0x90,
    FC_Read        = 0xFF,
    FC_Erase       = 0x20,
    FC_Confirm     = 0xD0,
    FC_Clear       = 0x50,
    FC_Write       = 0x40,
    FC_LoadPB      = 0xE0,
    FC_PBWrite     = 0x0C,
    FC_Status      = 0x70,
    FC_Suspend     = 0xB0,
    FC_Resume      = 0xD0,
    FC_ReadESR     = 0x71,
    FC_QueryCFI    = 0x98,
    FC_SCSErase    = 0x28,
    FC_SCSWrite    = 0xE8
};

enum IntelFlashStatus {
    FS_Ready       = 0x80,
    FS_Suspended   = 0x40,
    FS_Error       = 0x3E,
    FS_BlockError  = 0x3F
};

enum SXAccessType{
    SXT_NO = 0,
    SXT_INBAND,
    SXT_CMDIF,
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


//static inline
static u_int32_t log2up (u_int32_t in) {
    u_int32_t i;
    for (i = 0; i < 32; i++) {
        if (in <= (u_int32_t)(1 << i))
            break;
    }

    return i;
}

static inline
int set_bank(mflash* mfl, u_int32_t addr) {
    int bank = addr >> mfl->attr.log2_bank_size;

    if (mfl->curr_bank != bank) {
        mfl->curr_bank = bank;
        return mfl->f_set_bank(mfl, bank);
    }

    return MFE_OK;
}



// ConnectX SPI interface:
int cntx_flash_init      (mflash* mfl, flash_params_t* flash_params);

int cntx_fill_attr       (mflash* mfl);

int cntx_flash_read      (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);

int cntx_st_spi_reset          (mflash* mfl);
int cntx_st_spi_erase_sect     (mflash* mfl, u_int32_t addr);

int cntx_st_spi_block_write_ex (mflash*   mfl,
                                u_int32_t blk_addr,
                                u_int32_t blk_size,
                                u_int8_t* data,
                                u_int8_t  is_first,
                                u_int8_t  is_last);

int cntx_sst_spi_block_write_ex (mflash* mfl,
                                 u_int32_t blk_addr,
                                 u_int32_t blk_size,
                                 u_int8_t* data);


int cntx_st_spi_block_read_ex  (mflash*   mfl,
                                u_int32_t blk_addr,
                                u_int32_t blk_size,
                                u_int8_t* data,
                                u_int8_t  is_first,
                                u_int8_t  is_last);

int cntx_spi_get_type(mflash* mfl, u_int8_t op_type, u_int8_t *vendor, u_int8_t *type, u_int8_t *capacity);

int cntx_spi_write_status_reg(mflash* mfl, u_int32_t status_reg, u_int8_t status_is_double);

int spi_get_num_of_flashes(int prev_num_of_flashes);


int my_memset(void* dst, u_int8_t data, u_int32_t len) {
    u_int32_t i;
    u_int8_t* bytes = (u_int8_t*)dst;

    for (i = 0; i < len;  i++) {
        bytes[i] = data;
    }

    return 0;
}

int my_memcpy(void* dst, void* src, u_int32_t len) {
    u_int32_t i;
    u_int8_t* dbytes = (u_int8_t*)dst;
    u_int8_t* sbytes = (u_int8_t*)src;

    for (i = 0; i < len;  i++) {
        dbytes[i] = sbytes[i];
    }

    return 0;
}

#if 0 // TODO: Currently the polling is in max throttle - no sleep is done
int usleep(u_int32_t usecs) {
    u_int32_t i;
    u_int32_t stub = 0;
    // TODO: Some more intelegent /accurate way to do it, or remove T.Os completely.
    u_int32_t loops = (usecs << 9);
    for (i = 0; i < loops; i++) {
        stub++;
    }

    return stub;
}
#endif

int write_chunks   (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data) {
    int       rc;
    u_int8_t  *p         = (u_int8_t *)data;

    int       all_ffs;

    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t  tmp_buff[MAX_WRITE_BUFFER_SIZE];

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    //printf("-D- write_chunks(addr=%x, size=%x)\n", addr, len);

    while (len) {
        u_int32_t i;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;

        u_int32_t block_size = mfl->attr.block_write;
        u_int32_t block_mask = ~(block_size - 1 );

        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size  = block_size;

        u_int8_t* block_data = p;

        //
        // To keep things simple, we always write full blocks.
        // (there's an option to write partial buffer, but Intel reference code always
        // writes full buffer, with pads if needed. I do the same ...)
        //
        // The First and last cycles (can be the same one) may not be block aligned.
        // If this is the case, copy the block data to a 0xFF padded temp buffer (writing 0xFF
        // does not effect the flash)
        //

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask)) {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size) {
            my_memset(tmp_buff, 0xff, block_size);

            data_size -= prefix_pad_size;
            data_size -= suffix_pad_size;

            my_memcpy(tmp_buff + prefix_pad_size, p , data_size);

            block_data = tmp_buff;
        } else if (mfl->attr.page_write) {
            // current write is aligned to block size,
            // write data to next page, or to last full block (if we're in the last block in a page)
            u_int32_t page_mask             = ~(mfl->attr.page_write - 1);
            u_int32_t next_page_addr        = (addr + mfl->attr.page_write + 1) & page_mask;
            u_int32_t size_to_page_boundary = next_page_addr - addr;
            if (len > size_to_page_boundary) {
                block_size = size_to_page_boundary;
            } else {
                block_size = len & block_mask;
            }
            data_size = block_size;
        }

        //
        // Check to see if there's something to do
        //
        all_ffs = 1;
        for (i = 0; i < block_size ; i++) {
            if (block_data[i] != 0xff) {
                all_ffs = 0;
                break;
            }
        }

        if (!all_ffs) {
            rc = mfl->f_write_blk(mfl, block_addr, block_size, block_data); CHECK_RC(rc);

            if (mfl->opts[MFO_NO_VERIFY] == 0) {
                u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE];
                rc = mfl->f_reset(mfl);                                CHECK_RC(rc);
                rc = mfl->f_read(mfl, addr, data_size, verify_buffer); CHECK_RC(rc);
                // Verify data
                for (i = 0 ; i < data_size ; i++) {
                   // printf("-D- Verify: addr = %#x, verify_buffer[%d] = %#x, block_data[%d] = %#x\n",
                   //         addr, i, verify_buffer[i], i + prefix_pad_size, block_data[i + prefix_pad_size]);
                    if (verify_buffer[i] != block_data[i + prefix_pad_size]) {
                        //return _f.errmsg("Write verification failed. Addr %08x - exp:%02x act:%02x\n",
                        //       addr + i,
                        //       block_data[i + prefix_pad_size] ,
                        //       verify_buffer[i]);
                        return MFE_VERIFY_ERROR;
                    }
                }
            }
        }

        //
        // loop advance
        //

        addr += data_size;
        p    += data_size;
        len  -= data_size;
    }

    rc = mfl->f_reset(mfl); CHECK_RC(rc);

    return MFE_OK;
}


////////////////////////////////////////
//
// ST SPI functions - common for InfiniHostIIILx and ConnectX
//
////////////////////////////////////////
enum StFlashCommand {
    SFC_SE    = 0xD8,
    SFC_SSE   = 0x20,
    SFC_PP    = 0x02,
    SFC_RDSR  = 0x05,
    SFC_RDSR2 = 0x35,
    SFC_WREN  = 0x06,
    SFC_READ  = 0x03,
    SFC_RES   = 0xAB,
    SFC_JEDEC = 0x9F,
    SFC_WRSR  = 0x01
};

typedef struct flash_info {
    char *name;
    u_int8_t vendor;
    u_int8_t type;
    int command_set;
    int erase_command;
    int sector_size;
    u_int8_t quad_en_support;
    u_int8_t write_protected_support;
} flash_info_t;

#define SST_FLASH_NAME   "SST25VFxx"
#define WINBOND_NAME     "W25QxxBV"
#define WINBOND_W25X     "W25Xxx"
#define ATMEL_NAME       "AT25DFxxx"
#define FMT_ST_M25P_NAME

typedef enum flash_vendor {
    FV_ST      = 0x20,
    FV_SST     = 0xbf,
    FV_WINBOND = 0xef,
    FV_ATMEL   = 0x1f,
} flash_vendor_t;

typedef enum flash_memory_type {
    FMT_ST_M25P  = 0x20,
    FMT_ST_M25PX = 0x71,
    FMT_SST_25   = 0x25,
    FMT_WINBOND  = 0x40,
    FMT_WINBOND_W25X = 0x30,
    FMT_ATMEL    = 0x2,
    FMT_N25QXXX  = 0xba,

} flash_memory_type;

flash_info_t g_flash_info_arr[] =
{
        {"M25PXxx",      FV_ST,      FMT_ST_M25PX,     MCS_STSPI,  SFC_SSE, 0x1000,  0, 0},
        {"M25Pxx",       FV_ST,      FMT_ST_M25P,      MCS_STSPI,  SFC_SE,  0x10000, 0, 0},
        {"N25Q0XX",      FV_ST,      FMT_N25QXXX,      MCS_STSPI,  SFC_SSE, 0x1000, 0, 0},
        {SST_FLASH_NAME, FV_SST,     FMT_SST_25,       MCS_SSTSPI, SFC_SE,  0x10000, 0, 0},
        {WINBOND_NAME,   FV_WINBOND, FMT_WINBOND,      MCS_STSPI,  SFC_SSE, 0x1000,  1, 1},
        {WINBOND_W25X,   FV_WINBOND, FMT_WINBOND_W25X, MCS_STSPI,  SFC_SSE, 0x1000,  0, 0},
        {ATMEL_NAME,     FV_ATMEL,   FMT_ATMEL,        MCS_STSPI,  SFC_SSE, 0x1000,  0, 0},
};

int cntx_sst_get_log2size(u_int8_t capacity, int* log2spi_size)
{
    switch (capacity) {
        case 0x41:
            *log2spi_size = 0x15;
            break;
        case 0x4A:
            *log2spi_size = 0x16;
            break;
        case 0x8D:
            *log2spi_size = 0x13;
            break;
        case 0x8E:
            *log2spi_size = 0x14;
            break;
        default:
            return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    return 0;
}

int get_log2size_by_capcity(unsigned type_index, u_int8_t capacity, int *log2size) {

    flash_info_t *flash_info = &g_flash_info_arr[type_index];

    if (flash_info->type == FMT_SST_25 && flash_info->vendor == FV_SST) {
        return cntx_sst_get_log2size(capacity, log2size);
    } else {
        *log2size = capacity;
    }
    return MFE_OK;
}

int get_type_index_by_vendor_and_type(u_int8_t vendor, u_int8_t type, unsigned *type_index)
{
    unsigned i, arr_size;
    arr_size = ARR_SIZE(g_flash_info_arr);

    for (i = 0; i < arr_size; i++) {
        flash_info_t *flash_info = &g_flash_info_arr[i];
        if (flash_info->vendor == vendor && flash_info->type == type) {
            *type_index = i;
            return MFE_OK;
        }
    }
    return MFE_UNSUPPORTED_FLASH_TYPE;
}


int get_type_index_by_name(char *type_name, unsigned *type_index)
{
    unsigned i, arr_size;
    arr_size = ARR_SIZE(g_flash_info_arr);
    for (i = 0; i < arr_size; i++) {
        flash_info_t *flash_info = &g_flash_info_arr[i];
        if (!strcmp(type_name, flash_info->name)) {
            *type_index = i;
            return MFE_OK;
        }
    }
    printf("-E- The flash name \"%s\" is unknown\n.", type_name);
    return MFE_UNSUPPORTED_FLASH_TYPE;
}

int is_no_flash_detected(u_int8_t type, u_int8_t vendor, u_int8_t capacity) {
    if ((type == 0xff && vendor == 0xff && capacity == 0xff) ||
        (type == 0x0 && vendor == 0x0 && capacity == 0x0)) {
        return 1;
    }
    return 0;
}

int get_flash_info_by_res(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash, unsigned char *es_p)
{
    int rc;


    *no_flash = 0;

    rc = mfl->f_spi_status(mfl, SFC_RES, es_p); CHECK_RC(rc);
    // printf("-D- get_flash_info_by_res: es = %#x\n", *es_p);
    if ((*es_p >= 0x10 && *es_p < 0x17)) {
        *log2size = *es_p + 1;
        return get_type_index_by_vendor_and_type(FV_ST, FMT_ST_M25P, type_index);
    } else if (*es_p == 0xff || *es_p == 0x0) {
        *no_flash = 1;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }
    return MFE_OK;
}

int cntx_get_flash_info(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    int rc;
    u_int8_t type = 0, capacity = 0, vendor = 0, no_flash_res = 0, no_flash_rdid = 0;
    unsigned char es;
    // Assume there is a flash.
    *no_flash = 0;

    rc = cntx_spi_get_type(mfl, SFC_JEDEC, &vendor, &type, &capacity); CHECK_RC(rc);
    no_flash_rdid = is_no_flash_detected(type, vendor, capacity);
    // printf("-D- cntx_spi_get_type: rc: %#x, vendor=%#x, type=%#x, capacity=%#x\n", rc, vendor, type, capacity);
    // printf("-D- rc = %d, no_flash_rdid = %d\n", rc, no_flash_rdid);
    if (get_type_index_by_vendor_and_type(vendor, type, type_index) == MFE_OK) {
        // RDID Succeded.
        // Get the capacity
        if (get_log2size_by_capcity(*type_index, capacity, log2size) != MFE_OK) {
            printf("-E- SST SPI flash #%d (vendor: %#x, type: %#x, capacity:%#x) is not supported.\n", mfl->curr_bank, vendor,
                    type, capacity);
            return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
        }
         return MFE_OK;
    }
    // printf("-D- no support for rdid\n");
    // RDID Failed due to:
    // 1- RDID is not supported but RES is - Old flashes.
    // 2- There is no Flash
    // 3- Flash is not supported
    if (no_flash_rdid) {
        // Trying RES
        rc = get_flash_info_by_res(mfl, type_index, log2size, &no_flash_res, &es);
        if (rc == 0 && no_flash_res == 1) {
            // RES Succeeded due to: no flash, unsupported flash or old flash.
                *no_flash = 1;
            // when no_flash_rdid == 0 then "1- RDID is not supported but RES is - Old flashes."
        }
    } else {
        rc = MFE_UNSUPPORTED_FLASH_TYPE;
    }

    if (rc == MFE_UNSUPPORTED_FLASH_TYPE) {
        printf("-E- SPI flash #%d (vendor: %#x, memory type: %#x, es: %#x) is not supported.\n", mfl->curr_bank, vendor, type, es);
    }
    // printf("-D- rc = %d, no_flash_res = %d, type_index = %d.\n", rc, no_flash_res, *type_index);
    return rc;
}

int compare_flash_params(flash_params_t *flash_params, int bank_num, char *type_name, int log2size)
{
    if (strcmp(flash_params->type_name, type_name) != 0) {
        printf("-E- SPI flash #%d (type: %s)differs in type from SPI flash #%d(type: %s). "
               "All flash devices must be of the same type.\n",
               bank_num, type_name, bank_num - 1, flash_params->type_name);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }
    if (flash_params->log2size != log2size){
        printf ("-E- SPI flash #%d (log2size: %#x) differs in size from SPI flash #%d (log2size: %#x). "
                  "All flash devices must be of the same size.\n",
                  bank_num, log2size, bank_num - 1, flash_params->log2size);
        return MFE_UNSUPPORTED_FLASH_TOPOLOGY;

    }
    return MFE_OK;
}

int cntx_st_spi_get_status(mflash* mfl, u_int8_t op_type, u_int8_t* status) {
    u_int32_t flash_data;
    int rc;

    rc = cntx_int_spi_get_status_data(mfl, op_type, &flash_data, 1); CHECK_RC(rc);
    *status = EXTRACT(flash_data, 0, 8);
    return MFE_OK;
}
int get_flash_params(mflash* mfl, flash_params_t *flash_params, unsigned *type_index)
{
    int num_of_flashes = mfl->opts[MFO_NUM_OF_BANKS];
    int spi_sel, rc;
    int params_were_set = 0;
    flash_info_t *flash_info;

    memset(flash_params, 0, sizeof(flash_params_t));

    for (spi_sel = 0 ; spi_sel < num_of_flashes ; spi_sel++) {
            int log2size;
            u_int8_t no_flash = 0;
            char *type_name;
            rc = set_bank(mfl, spi_sel);                      CHECK_RC(rc);
            rc = mfl->f_get_info(mfl, type_index, &log2size, &no_flash); CHECK_RC(rc);
            //printf("-D- spi_sel = %d, num_of_flashes = %d, rc = %d, no_flash = %d\n", spi_sel, num_of_flashes, rc, no_flash);

            if (no_flash == 1) {
                // This bank is empty and also the following banks will be empty.
                if (flash_params->num_of_flashes == 0) {
                    // if we haven't detected any 'supported' flash, return an error.
                    return MFE_NO_FLASH_DETECTED;
                }
                break;
            }
            flash_info = &(g_flash_info_arr[*type_index]);

            type_name = flash_info->name;
            if (params_were_set == 0) {
                flash_params->type_name = type_name;
                flash_params->log2size  = log2size;
                params_were_set = 1;
            } else {
                rc = compare_flash_params(flash_params, spi_sel, type_name, log2size); CHECK_RC(rc);
            }
            // Init SST flash.
            if (mfl->access_type == MFAT_MFILE) {
                if (flash_info->vendor ==  FV_SST && flash_info->type == FMT_SST_25) {
                    rc = cntx_spi_write_status_reg(mfl, SST_STATUS_REG_VAL, 0); CHECK_RC(rc);
                } else if (flash_info->vendor ==  FV_ATMEL && flash_info->type == FMT_ATMEL) {
                    rc = cntx_spi_write_status_reg(mfl, ATMEL_STATUS_REG_VAL, 0); CHECK_RC(rc);
                }
            }

            flash_params->num_of_flashes++;
    }
    return MFE_OK;
}

int spi_fill_attr_from_params(mflash* mfl, flash_params_t* flash_params, unsigned type_index)
{
    flash_info_t *flash_info = &(g_flash_info_arr[type_index]);

    mfl->attr.log2_bank_size = flash_params->log2size;
    mfl->attr.bank_size      = 1 << flash_params->log2size;
    mfl->attr.size           = mfl->attr.bank_size * flash_params->num_of_flashes;
    mfl->attr.block_write                = 16; // In SPI context, this is the transaction size. Max is 16.
    mfl->attr.num_erase_blocks           = 1;
    mfl->attr.erase_block[0].sector_size = flash_info->sector_size;
    mfl->attr.erase_block[0].sector_mask = ~(mfl->attr.erase_block[0].sector_size - 1);
    mfl->attr.sector_size = mfl->attr.erase_block[0].sector_size;

    mfl->attr.command_set   = flash_info->command_set;
    mfl->attr.erase_command = flash_info->erase_command;
    mfl->attr.type_str      = flash_info->name;

    mfl->attr.quad_en_support = flash_info->quad_en_support;

    mfl->attr.write_protect_support = flash_info->write_protected_support;
    mfl->attr.banks_num             = flash_params->num_of_flashes;
    return MFE_OK;
}

int st_spi_fill_attr(mflash* mfl, flash_params_t* flash_params) {

    int rc;
    flash_params_t *cur_flash_params, tmp_flash_params;
    unsigned type_index;
    flash_info_t *flash_info;



    // printf("-D- st_spi_fill_attr: ignore_detect = %d, log2size = %#x.\n", mfl->ignore_flash_detect, mfl->user_attr.log2size);
    if (flash_params == NULL) {
        // Get flash params from the flash itself
        cur_flash_params = &tmp_flash_params;
        rc = get_flash_params(mfl, cur_flash_params, &type_index); CHECK_RC(rc);
    } else {
        // Get the flash params from the user.
        rc = get_type_index_by_name(flash_params->type_name, &type_index); CHECK_RC(rc);
        cur_flash_params = flash_params;
    }
    flash_info = &(g_flash_info_arr[type_index]);

    // Init the flash attr according to the flash parameters (which was wither given by the user or read from the flash)
    rc = spi_fill_attr_from_params(mfl, cur_flash_params, type_index); CHECK_RC(rc);
    // printf("-D- spi_size = %#x,  log2spi_size = %#x, bank_size = %#x, flashes_num = %d\n", mfl->attr.size, mfl->attr.log2_bank_size,
    //       mfl->attr.bank_size, cur_flash_params->num_of_flashes);
    return MFE_OK;
}

int st_spi_wait_wip(mflash* mfl, u_int32_t delay, u_int32_t retrys, u_int32_t fast_retrys) {

    int       rc;
    u_int8_t  status;
    u_int32_t cnt = 0;

    delay = 0; // UNUSED FOR NOW

    do {
        if (++cnt > fast_retrys) {
            //usleep(delay);
        }
        if (cnt > retrys) {
            return MFE_WRITE_TIMEOUT;
        }

        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
    } while (status & 0x01);

    return MFE_OK;
}

int read_chunks   (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data) {

    int       rc;
    u_int8_t  *p         = (u_int8_t *)data;

    // Note:
    // Assuming read block is the same as write block size.
    // This is true for current Mellanox devices SPI flash access implementation.
    // Check for future devices.
    u_int32_t block_size = mfl->attr.block_write;
    u_int32_t block_mask;


    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t  tmp_buff[MAX_WRITE_BUFFER_SIZE];

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    if (len < block_size) {
        // If we're reading a small chunk, use the smallest block_size to avoid the extra reads and padding overhead
        block_size = 4;
    }

    block_mask = ~(block_size - 1);

    while (len) {

        u_int32_t i;
        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;

        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size  = block_size;

        u_int8_t* block_data = p;

        //
        // First and last cycles (can be the same one) may not be block aligned.
        // Check the status, and copy data to a padded temp bufer if not alligned.
        // (there's an option to write partial buffer, but Intel reference code always
        // writes full buffer, with pads if needed. I do the dame ...)
        //

        prefix_pad_size = addr - block_addr;

        if ((addr & block_mask) == ((addr + len) & block_mask)) {
            suffix_pad_size = block_size - ((addr + len) % block_size);
        }

        if (suffix_pad_size || prefix_pad_size) {
            // block exceeds given buffer - read to a temp bufer and
            // copy the required data to user's bufer.
            data_size -= suffix_pad_size;
            data_size -= prefix_pad_size;
            block_data = tmp_buff;
        }

        rc = mfl->f_read_blk(mfl, block_addr, block_size, block_data); CHECK_RC(rc);

        if (suffix_pad_size || prefix_pad_size) {
            for (i = 0; i < data_size; i++) {
                p[i] = tmp_buff[prefix_pad_size + i];
            }
        }

        //
        // loop advance
        //

        addr += data_size;
        p    += data_size;
        len  -= data_size;
    }

    return MFE_OK;
}




////////////////////////////////////////
//
// InfiniHostIIILx spi  access functions
//
////////////////////////////////////////


//
// Relevant CR addresses, Bit offset and bit size
//

enum CrConstans {
    CR_FLASH_GW     = 0xf0400,
    CR_FLASH_ADDR   = 0xf0404,
    CR_FLASH_DATA   = 0xf0408,
    CR_FLASH_CS     = 0xf0418,

    CR_GPIO_LOCK    = 0xf00ec,

    BO_READ_OP      = 0,
    BO_ADDR_INCR    = 1,

    BO_LPC_STOP     = 3,
    BO_SPI_NO_DATA  = 4,
    BO_SPI_NO_ADDR  = 5,
    BO_SPI_SPECIAL  = 6,

    BO_MSIZE        = 8,
    BS_MSIZE        = 3,

    BO_STATUS       = 26,
    BS_STATUS       = 4,

    BO_BUSY         = 30,

    BO_SPI_ADDR     = 0,
    BS_SPI_ADDR     = 24,

    BO_SPI_CMD      = 24,
    BS_SPI_CMD      = 8,

    BO_SPI_GPIO     = 25,
    BS_SPI_GPIO     = 4
};

int gw_wait_ready(mflash* mfl, char* msg) {
    u_int32_t gw_cmd;
    u_int32_t cnt = 0;
    msg = 0; // NOT USED FOR NOW
    do {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT) {
            //return errmsg("Flash gateway timeout: %s.", msg);
            return MFE_TIMEOUT;
        }

        MREAD4(CR_FLASH_GW, &gw_cmd);

    } while (EXTRACT(gw_cmd, BO_BUSY, 1));

    return MFE_OK;
}


int empty_reset          (mflash* mfl) {
    mfl = NULL;
    return MFE_OK;
}

//////////////////////////////////////////
//
// ConnectX functions implementation
//
//////////////////////////////////////////
enum CntxCrConstants{
    HCR_FLASH_CMD     = 0xf0400,
    HCR_FLASH_ADDR    = 0xf0404,

    HCR_FLASH_DATA    = 0xf0410,

    HBO_READ_OP       = 0,
    HBO_ADDR_AUTO_INC = 1,
    HBO_CMD_PHASE     = 2,
    HBO_ADDR_PHASE    = 3,
    HBO_DATA_PHASE    = 4,
    HBO_CS_HOLD       = 5,

    HBO_MSIZE         = 8,
    HBS_MSIZE         = 3,

    HBO_CHIP_SELECT   = 11,
    HBS_CHIP_SELECT   =  2,

    HBO_FLASH_ENABLE  = 13,

    HBO_CMD           = 16,
    HBS_CMD           =  8,

    HBO_BUSY          = 30,
    HBO_LOCK          = 31,

    HBO_ADDR          =  0,
    HBS_ADDR          = 24,


    // GPIOs
    HCR_GPIO_LOCK     = 0xf0048,
    HCR_GPIO_LOCK_VAL = 0xd42f,

    HCR_GPIO_DATA_OUT = 0xf0040,
    HCR_GPIO_MODE0    = 0xf0050,
    HCR_GPIO_MODE1    = 0xf004c,

    HBO_GPIO_CS       = 25,
    HBS_GPIO_CS       =  4
};

int empty_set_bank(mflash* mfl, u_int32_t bank) {
    // NULL function - No actual work here - in ConnectX the curr_bank is written in the command word.
    mfl = NULL; // Compiler warning
    bank = 0;   // Compiler warning
    return MFE_OK;
}

int is_connectx_family(u_int32_t dev_id) {
    if (dev_id == HERMON_HW_ID ||  // Hermon
        dev_id == CX3_HW_ID || // CX3
        dev_id == CX3_PRO_HW_ID) {     // Bental
        return 1;
    }
    return 0;

}

int is_sx(u_int32_t dev_id) {
    if (dev_id == SWITCHX_HW_ID) {
        return 1;
    }
    return 0;
}
int is_is4_family(u_int32_t dev_id) {
    if (dev_id == 435  ||  // InfiniScaleIV
        dev_id == 6100) { // BridgeX
        return 1;
    }
    return 0;
}

int is_connectib(u_int32_t dev_id) {
    if (dev_id == CONNECT_IB_HW_ID) {
        return 1;
    }
    return 0;
}
int is_4th_gen_switch_family(u_int32_t dev_id) {
    if (is_is4_family(dev_id) ||
        is_sx(dev_id)         ||
        is_connectib(dev_id)) {
        return 1;
    }
    return 0;
}

int cntx_exec_cmd(mflash* mfl, u_int32_t gw_cmd, char* msg) {
    if (is_4th_gen_switch_family(mfl->attr.hw_dev_id)) {
        // For Infiniscale4 and BridgeX: keep the GW locked during flash ops
        gw_cmd = MERGE(gw_cmd,              1,       31,                       1);
    }
    gw_cmd = MERGE(gw_cmd,              1, HBO_BUSY,                       1);
    gw_cmd = MERGE(gw_cmd,              1, HBO_FLASH_ENABLE,               1);
    gw_cmd = MERGE(gw_cmd, (u_int32_t)mfl->curr_bank,
                                           HBO_CHIP_SELECT,  HBS_CHIP_SELECT);
    //  printf("-D- cntx_exec_cmd: %s, gw_cmd = %#x\n", msg, gw_cmd);
    MWRITE4(CR_FLASH_GW,   gw_cmd);
    return gw_wait_ready(mfl, msg);
}

int cntx_int_spi_get_status_data(mflash* mfl, u_int8_t op_type, u_int32_t* status, u_int8_t data_num)
{
    int rc;

    u_int32_t gw_cmd  = 0;
    u_int32_t flash_data = 0;

    gw_cmd = MERGE(gw_cmd,       1, HBO_READ_OP,    1);
    gw_cmd = MERGE(gw_cmd,       1, HBO_CMD_PHASE,  1);
    gw_cmd = MERGE(gw_cmd,       1, HBO_DATA_PHASE, data_num);
    gw_cmd = MERGE(gw_cmd,       2, HBO_MSIZE,      HBS_MSIZE);

    gw_cmd = MERGE(gw_cmd, op_type, HBO_CMD,        HBS_CMD);

    rc = cntx_exec_cmd(mfl, gw_cmd, "Read id");  CHECK_RC(rc);

    MREAD4(HCR_FLASH_DATA, &flash_data);

    // printf("-D- cntx_int_spi_get_status_data: op=%02x status=%08x\n", op_type, flash_data);
    // Return status reg byte is at offset 3 in word
    *status = flash_data;

    return MFE_OK;
}

int cntx_st_spi_write_enable(mflash* mfl) {
    u_int32_t gw_cmd  = 0;
    int rc;
    // Write enable:
    gw_cmd = MERGE(gw_cmd,        1, HBO_CMD_PHASE,       1);
    gw_cmd = MERGE(gw_cmd, SFC_WREN, HBO_CMD,       HBS_CMD);


    rc = cntx_exec_cmd(mfl, gw_cmd, "WREN command"); CHECK_RC(rc);

    //gw_cmd =  MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);

    //MWRITE4(CR_FLASH_GW,   gw_cmd);

    return MFE_OK;
}



int get_flash_info_for_atmel(u_int32_t jededc_id, u_int8_t* type, u_int8_t* capacity)
{
    u_int8_t tmp_cap;

    tmp_cap = EXTRACT(jededc_id, 8, 5);
    *type   = EXTRACT(jededc_id, 13, 3);
    switch (tmp_cap) {
        case 0x4:
            *capacity = 0x13;
            break;
        case 0x5:
            *capacity = 0x14;
            break;
        case 0x6:
            *capacity = 0x15;
            break;
        case 0x7:
            *capacity = 0x16;
            break;
        default:
            return MFE_UNSUPPORTED_FLASH_TOPOLOGY;
    }

    return MFE_OK;

}
int get_info_from_jededc_id(u_int32_t jededc_id, u_int8_t *vendor, u_int8_t* type, u_int8_t* capacity)
{
    int rc;

    *vendor   = EXTRACT(jededc_id, 0, 8);
    if (*vendor == FV_ATMEL) {
        rc = get_flash_info_for_atmel(jededc_id, type, capacity); CHECK_RC(rc);
    } else {
        *type     = EXTRACT(jededc_id, 8, 8);
        *capacity = EXTRACT(jededc_id, 16, 8);
    }

    return MFE_OK;
}

int cntx_spi_get_type(mflash* mfl, u_int8_t op_type, u_int8_t *vendor, u_int8_t* type, u_int8_t* capacity) {
    u_int32_t flash_data = 0;
    int rc;

    rc = cntx_int_spi_get_status_data(mfl, op_type, &flash_data, 3); CHECK_RC(rc);
    // We should swap the word we get from the gateway because it's inverted
    flash_data = SWAPL(flash_data);
    // printf("-D- jedec_id = %#x\n", flash_data);
    // Get type and some other info from jededc_id
    get_info_from_jededc_id(flash_data, vendor, type, capacity);
    // printf("-D- cntx_spi_get_type: vendor = %#x, type = %#x, capacity = %#x\n", *vendor, *type, *capacity);
    return MFE_OK;
}
int cntx_spi_write_status_reg(mflash* mfl, u_int32_t status_reg, u_int8_t status_is_double)
{
    int rc;
    u_int32_t gw_cmd = 0;

    rc = cntx_st_spi_write_enable(mfl); CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd,        1, HBO_CMD_PHASE,  1);
    gw_cmd = MERGE(gw_cmd,        1, HBO_DATA_PHASE, 1);

    gw_cmd = MERGE(gw_cmd, SFC_WRSR, HBO_CMD,        HBS_CMD);

    if (status_is_double) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_MSIZE,      HBS_MSIZE);
    }
    MWRITE4(HCR_FLASH_DATA, status_reg);

    return cntx_exec_cmd(mfl, gw_cmd, "Write-Status-Register");

}



int cntx_init_gpios(mflash* mfl) {
    //
    // Set Multi SPI CS to output and with value of 1 (inactive)
    // Assuming 4 flashes. If there are less than 4 flashes and there's
    // an access to a void flash, the access will fail.
    //

    u_int32_t       spi_en      = 0xf;

    u_int32_t       mode0;
    u_int32_t       mode1;
    u_int32_t       data;

    // Set 4 Chip selects to 1
    MREAD4(HCR_GPIO_DATA_OUT, &data);
    data = MERGE(data, spi_en, BO_SPI_GPIO, BS_SPI_GPIO);
    MWRITE4(HCR_GPIO_DATA_OUT, data);

    MREAD4(HCR_GPIO_MODE0, &mode0);
    MREAD4(HCR_GPIO_MODE1, &mode1);

    // Set 4 Chip selects to outputs
    if (EXTRACT(mode0, HBO_GPIO_CS, HBS_GPIO_CS) != spi_en ||
        EXTRACT(mode1, HBO_GPIO_CS, HBS_GPIO_CS) != 0          ) {
        mode0 = MERGE(mode0,  spi_en, BO_SPI_GPIO, BS_SPI_GPIO);
        mode1 = MERGE(mode1, ~spi_en, BO_SPI_GPIO, BS_SPI_GPIO);

        // unlock gpio
        MWRITE4(HCR_GPIO_LOCK , HCR_GPIO_LOCK_VAL);

        MWRITE4(HCR_GPIO_MODE0, mode0);
        MWRITE4(HCR_GPIO_MODE1, mode1);

        // re-lock
        MWRITE4(HCR_GPIO_LOCK , 0);
    }

    return MFE_OK;
}

#define MFLASH_ENV "MFLASH_BANKS"

int spi_get_num_of_flashes(int prev_num_of_flashes)
{
    char* mflash_env;

    if (prev_num_of_flashes != 0) {
        return prev_num_of_flashes;
    }

    mflash_env = getenv(MFLASH_ENV);
    if (mflash_env) {
        return atol(mflash_env);
    }

    return -1;
}

int spi_update_num_of_banks(mflash* mfl, int prev_num_of_flashes)
{
    int num_of_banks;

    num_of_banks = spi_get_num_of_flashes(prev_num_of_flashes);
    if (num_of_banks == -1) {
        mfl->opts[MFO_NUM_OF_BANKS] = MAX_NUM_OF_FLASH_BANKS;
        mfl->opts[MFO_USER_BANKS_NUM] = 0;
    } else {
        mfl->opts[MFO_NUM_OF_BANKS]   = num_of_banks;
        mfl->opts[MFO_USER_BANKS_NUM] = 1;
    }
    return MFE_OK;
}


int cntx_st_spi_reset          (mflash* mfl) {
    mfl = NULL;
    return MFE_OK;
}

int cntx_st_spi_page_read    (mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data) {
    int rc;

    u_int32_t last_blk_addr;
    u_int32_t last_addr;
    u_int8_t  is_first = 1;
    u_int8_t  is_last  = 0;
    u_int8_t* p        = data;

    if (addr & ((u_int32_t)mfl->attr.block_write - 1)) {
        return MFE_BAD_ALIGN;
    }

    if (size & ((u_int32_t)mfl->attr.block_write - 1)) {
         return MFE_BAD_ALIGN;
    }

    //printf("-D- cntx_st_spi_page_read(addr=%05x, u_int32_t size=%03x)\n", addr, size);

    last_addr     = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr) {
        if (addr == last_blk_addr) {
            is_last = 1;
        }

        rc = cntx_st_spi_block_read_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last); CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p    += mfl->attr.block_write;
    }

    return MFE_OK;
}

int get_flash_offset(u_int32_t addr, int log2_bank_size, u_int32_t *flash_addr_p)
{
    *flash_addr_p = addr & ONES32(log2_bank_size);
    return MFE_OK;
}

int cntx_st_spi_block_read_ex  (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data, u_int8_t is_first, u_int8_t is_last) {
    int rc;
    u_int32_t i;
    u_int32_t gw_cmd   = 0;
    u_int32_t gw_addr  = 0;

    //printf("-D- cntx_st_spi_block_read_ex(addr=%05x, u_int32_t size=%03x, first=%d, last=%d)\n", blk_addr, blk_size, (u_int32_t) is_first, (u_int32_t) is_last);
    COM_CHECK_ALLIGN(blk_addr, blk_size);

    if (blk_size > (u_int32_t)mfl->attr.block_write  || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);        CHECK_RC(rc);

    if (is_first) {
        gw_cmd = MERGE(gw_cmd, 1               , HBO_CMD_PHASE,  1);
        gw_cmd = MERGE(gw_cmd, 1               , HBO_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, SFC_READ        , HBO_CMD,        HBS_CMD);

        rc = get_flash_offset(blk_addr, mfl->attr.log2_bank_size, &gw_addr); CHECK_RC(rc);
        //printf("-D- cntx_st_spi_block_read_ex: write to gateway\n");
        MWRITE4(HCR_FLASH_ADDR, gw_addr);

    }
    //printf("-D- gw_addr = %#x, gw_cmd = %#x, blk_addr = %#x, mfl->attr.log2_bank_size = %#x\n", gw_addr, gw_cmd, blk_addr, mfl->attr.log2_bank_size);
    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);
    }

    // Read the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_READ_OP,           1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE,        1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), BO_MSIZE,       BS_MSIZE);

    rc = cntx_exec_cmd(mfl, gw_cmd, "Read"); CHECK_RC(rc);

    //if (mread_by_chunks(mfl->mf, HCR_FLASH_DATA, data, blk_size) != (int)blk_size) {
    if (mread4_block(mfl->mf, HCR_FLASH_DATA, (u_int32_t*)data, blk_size) != (int)blk_size) {
        return 2;
        //fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", HCR_FLASH_DATA, strerror(errno), (u_int32_t)errno);
        //exit(2);
    }

    for (i = 0; i < blk_size ; i+= 4) {
        *(u_int32_t*)(data + i) = __be32_to_cpu(*(u_int32_t*)(data + i));
    }
    return MFE_OK;
}

int cntx_st_spi_block_read  (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data) {
    return cntx_st_spi_block_read_ex(mfl, blk_addr, blk_size, data, 1, 1);
}

int cntx_st_spi_block_read_old  (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data) {
    int rc;
    u_int32_t offs;
    u_int32_t gw_cmd   = 0;
    u_int32_t gw_addr  = 0;

    COM_CHECK_ALLIGN(blk_addr, blk_size);

    if (blk_size > (u_int32_t)mfl->attr.block_write  || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);        CHECK_RC(rc);

    // Read the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_READ_OP,           1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_CMD_PHASE,         1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_ADDR_PHASE,        1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_DATA_PHASE,        1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), BO_MSIZE,       BS_MSIZE);
    gw_cmd = MERGE(gw_cmd, SFC_READ, HBO_CMD,       HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);
    MWRITE4(HCR_FLASH_ADDR, gw_addr);

    rc = cntx_exec_cmd(mfl, gw_cmd, "Read"); CHECK_RC(rc);

    // Data:
    for (offs = 0 ; offs < blk_size ; offs += 4) {
        u_int32_t word;
        MREAD4(HCR_FLASH_DATA + offs, &word);
        *((u_int32_t*)(data + offs))= __cpu_to_be32(word);
    }

    return MFE_OK;
}




int cntx_st_spi_page_write    (mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data) {
    int rc;

    u_int32_t last_blk_addr;
    u_int32_t last_addr;
    u_int8_t  is_first = 1;
    u_int8_t  is_last  = 0;
    u_int8_t* p        = data;

    WRITE_CHECK_ALLIGN(addr, mfl->attr.block_write, size);

    last_addr     = addr + size;
    last_blk_addr = last_addr - mfl->attr.block_write;

    while (addr < last_addr) {
        if (addr == last_blk_addr) {
            is_last = 1;
        }
        rc = cntx_st_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p, is_first, is_last); CHECK_RC(rc);

        is_first = 0;
        addr += mfl->attr.block_write;
        p    += mfl->attr.block_write;

    }

    return MFE_OK;
}

int cntx_sst_spi_byte_write    (mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data) {
    int rc;

    u_int32_t last_addr;
    u_int8_t* p        = data;

    WRITE_CHECK_ALLIGN(addr, mfl->attr.block_write, size);

    last_addr     = addr + size;

    while (addr < last_addr) {
        rc = cntx_sst_spi_block_write_ex(mfl, addr, mfl->attr.block_write, p); CHECK_RC(rc);
        addr++;
        p++;
    }

    return MFE_OK;
}

int cntx_st_spi_block_write_ex (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data, u_int8_t is_first, u_int8_t is_last) {
    int rc;
    u_int32_t offs;
    u_int32_t gw_cmd   = 0;
    u_int32_t gw_addr  = 0;
    u_int32_t buff[4];

    if (blk_addr & ((u_int32_t)mfl->attr.block_write - 1 )) {
        return MFE_BAD_ALIGN;
    }

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t)mfl->attr.block_write ) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);        CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1               , HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), HBO_MSIZE,      HBS_MSIZE);

    if (is_first) {
        rc = cntx_st_spi_write_enable(mfl); CHECK_RC(rc);

        // Write the data block
        gw_cmd = MERGE(gw_cmd, 1               , HBO_CMD_PHASE,  1);
        gw_cmd = MERGE(gw_cmd, 1               , HBO_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, SFC_PP          , HBO_CMD,        HBS_CMD);
        gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);
        //printf("-D- gw_addr = %#x, blk_addr = %#x\n", gw_addr, blk_addr);

        MWRITE4(HCR_FLASH_ADDR, gw_addr);
    }

    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);
    }

    // Data:
    for (offs = 0 ; offs < blk_size ; offs += 4) {
        u_int32_t word = zero;

        word = MERGE(word, data[offs + 0] , 24 , 8);
        word = MERGE(word, data[offs + 1] , 16 , 8);
        word = MERGE(word, data[offs + 2] ,  8 , 8);
        word = MERGE(word, data[offs + 3] ,  0 , 8);
        //MWRITE4(HCR_FLASH_DATA + offs, word );
        buff[offs/4] = word;
        //printf("-D- word = %#x, %d\n", word, HBS_CMD);
    }

    if (mwrite4_block(mfl->mf, HCR_FLASH_DATA, buff, blk_size) != (int)blk_size) {
        return 2;
        // fprintf(stderr, "-E- Cr chunk write (0x%08x) failed: %s(%d)\n", HCR_FLASH_DATA, strerror(errno), (u_int32_t)errno);
        // exit(2);
    }

    rc = cntx_exec_cmd(mfl, gw_cmd, "PP command"); CHECK_RC(rc);

    //
    // Wait for end of write in flash (WriteInProgress = 0):
    //

    if (is_last) {
        rc = st_spi_wait_wip(mfl, READ_DELAY, READ_CNT_SLOW + READ_CNT_FAST, READ_CNT_FAST); CHECK_RC(rc);
    }

    return MFE_OK;
}

int cntx_sst_spi_block_write_ex (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data) {
    int rc;
    u_int32_t gw_cmd   = 0;
    u_int32_t gw_addr  = 0;
    u_int32_t word = zero;

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t)mfl->attr.block_write ) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);        CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1               , HBO_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0, HBO_MSIZE,      HBS_MSIZE);

    rc = cntx_st_spi_write_enable(mfl); CHECK_RC(rc);

    // Write the data block
    gw_cmd = MERGE(gw_cmd, 1               , HBO_CMD_PHASE,  1);
    gw_cmd = MERGE(gw_cmd, 1               , HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0x02            , HBO_CMD,        HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);
    MWRITE4(HCR_FLASH_ADDR, gw_addr);

    //gw_cmd = MERGE(gw_cmd, 1               , HBO_CS_HOLD,    1);

    word = MERGE(word, data[0] , 24 , 8);

    //printf("-D- data[0] = %#x, gw_addr = %#x, word = %#x, gw_cmd = %#x\n", data[0], gw_addr, word, gw_cmd);
    MWRITE4(HCR_FLASH_DATA, word);

    rc = cntx_exec_cmd(mfl, gw_cmd, "PB command"); CHECK_RC(rc);

    rc = st_spi_wait_wip(mfl, READ_DELAY, READ_CNT_SLOW + READ_CNT_FAST, READ_CNT_FAST); CHECK_RC(rc);

    return MFE_OK;
}


int cntx_st_spi_block_write     (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data) {
   return cntx_st_spi_block_write_ex(mfl, blk_addr, blk_size, data, 1, 1);
}

int cntx_st_spi_block_write_old (mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data) {
    int rc;
    u_int32_t offs;
    u_int32_t gw_cmd   = 0;
    u_int32_t gw_addr  = 0;

    COM_CHECK_ALLIGN(blk_addr, blk_size);

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t)mfl->attr.block_write ) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);        CHECK_RC(rc);

    rc = cntx_st_spi_write_enable(mfl); CHECK_RC(rc);

    // Write the data block
    gw_cmd = MERGE(gw_cmd, 1               , HBO_CMD_PHASE,  1);
    gw_cmd = MERGE(gw_cmd, 1               , HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1               , HBO_DATA_PHASE, 1);

    gw_cmd = MERGE(gw_cmd, log2up(blk_size), HBO_MSIZE,      HBS_MSIZE);
    gw_cmd = MERGE(gw_cmd, SFC_PP          , HBO_CMD,        HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);

    MWRITE4(HCR_FLASH_ADDR, gw_addr);

    // Data:
    for (offs = 0 ; offs < blk_size ; offs += 4) {
        u_int32_t word = zero;
        word = MERGE(word, data[offs + 0] , 24 , 8);
        word = MERGE(word, data[offs + 1] , 16 , 8);
        word = MERGE(word, data[offs + 2] ,  8 , 8);
        word = MERGE(word, data[offs + 3] ,  0 , 8);
        MWRITE4(HCR_FLASH_DATA + offs, word );
    }

    rc = cntx_exec_cmd(mfl, gw_cmd, "PP command"); CHECK_RC(rc);

    //
    // Wait for end of write in flash (WriteInProgress = 0):
    //

    rc = st_spi_wait_wip(mfl, READ_DELAY, READ_CNT_SLOW + READ_CNT_FAST, READ_CNT_FAST); CHECK_RC(rc);

    return MFE_OK;
    }

int cntx_st_spi_erase_sect(mflash* mfl, u_int32_t addr) {
    int rc;

    u_int32_t gw_cmd  = 0;
    u_int32_t gw_addr = 0;
    rc = set_bank(mfl, addr); CHECK_RC(rc);

    rc = cntx_st_spi_write_enable(mfl); CHECK_RC(rc);

    // Erase sector command:
    gw_cmd = MERGE(gw_cmd,      1, HBO_CMD_PHASE,  1);
    gw_cmd = MERGE(gw_cmd,      1, HBO_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, mfl->attr.erase_command, HBO_CMD,        HBS_CMD);

    gw_addr = addr & ONES32(mfl->attr.log2_bank_size);

    MWRITE4(HCR_FLASH_ADDR, gw_addr);

    // printf("-D- cntx_st_spi_erase_sect: addr = %#x, gw_cmd = %#x.\n", addr, gw_cmd);

    rc = cntx_exec_cmd(mfl, gw_cmd, "ES"); CHECK_RC(rc);

    // Wait for erase completion
    rc = st_spi_wait_wip(mfl, ERASE_DELAY, ERASE_CNT, 0); CHECK_RC(rc);

    return MFE_OK;
}


f_mf_write get_write_blk_func(int command_set)
{
    if (command_set == MCS_STSPI) {
        return cntx_st_spi_page_write;
    }
    return cntx_sst_spi_byte_write;
}

int old_flash_lock(mflash* mfl, int lock_state) {

    // Obtain GPIO Semaphore
    u_int32_t cnt=0;
    u_int32_t word;
    if (lock_state) {
        do {
            if (++cnt > GPIO_SEM_TRIES) {
                //printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(SEMAP63, &word);
        } while (word);
    } else {
        MWRITE4(SEMAP63, 0);
    }

    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}


int cntx_flash_init(mflash* mfl, flash_params_t* flash_params) {
    int rc;
    u_int32_t tmp;
    int is_life_fish = 0;

    // Without too much details:
    // When the ConnectX boots up without a valid FW , the PCIE link may be unstable.
    // In that case, turn off the auto reset on link down, so we'll be able to burn the device.
    MREAD4(0x41270, &tmp);
    if (tmp > 0xfff00000) {
        u_int32_t tmp1;
        is_life_fish = 1;
        MREAD4(0xf3834, &tmp1);
        tmp1 = MERGE(tmp1, 2, 27, 2);
        MWRITE4(0xf3834, tmp1);

    }


    //TODO: Enable page_read (slightly better perf)
    //mfl->f_read           = cntx_st_spi_page_read;
    mfl->f_read           = read_chunks;
    mfl->f_read_blk       = cntx_st_spi_block_read;
    mfl->f_lock           = old_flash_lock; // Flash lock has same address and functionality as in InfiniHost.
    mfl->f_set_bank       = empty_set_bank;
    mfl->f_get_info       = cntx_get_flash_info;


    rc = mfl->f_lock(mfl, 1);
    if (!mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        CHECK_RC(rc);
    } else {
        mfl->is_locked = 1;
    }
    //if (is_life_fish) {
    //    rc = cntx_init_gpios(mfl);  CHECK_RC(rc);
    //}


    mfl->f_spi_status = cntx_st_spi_get_status;

    rc = st_spi_fill_attr(mfl, flash_params);   CHECK_RC(rc);

    if        (mfl->attr.command_set == MCS_STSPI || mfl->attr.command_set == MCS_SSTSPI) {
        mfl->f_reset      = empty_reset; // Null func
        mfl->f_write_blk  = get_write_blk_func(mfl->attr.command_set);

        mfl->attr.page_write = 256;
        mfl->f_write      = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    rc = mfl->f_reset(mfl);

    return MFE_OK;
}

// InfiniScale 4 (IS4) functions:

int is4_init_gpios(mflash* mfl) {
    mfl = NULL;
    return MFE_NOT_IMPLEMENTED;
}


int is4_flash_lock(mflash* mfl, int lock_state) {
    // Obtain GPIO Semaphore
    u_int32_t cnt=0;
    u_int32_t word;
    if (lock_state) {
        do {
            if (++cnt > GPIO_SEM_TRIES) {
                //printf("-E- Can not obtain Flash semaphore");
                return MFE_SEM_LOCKED;
            }
            MREAD4(HCR_FLASH_CMD , &word);
        } while (EXTRACT(word, HBO_LOCK, 1));
    } else {
        MWRITE4(HCR_FLASH_CMD, 0);
    }

    mfl->is_locked = (lock_state != 0);
    return MFE_OK;
}

#define CACHE_REPLACEMNT_EN_ADDR 0xf0420
int disable_cache_replacement(mflash *mfl)
{
    u_int32_t data;
    MREAD4(CACHE_REPLACEMNT_EN_ADDR, &data);
    data = MERGE(data, 0, 0, 1); // We put 0 in the first bit of the read data
    MWRITE4(CACHE_REPLACEMNT_EN_ADDR, data);

    return 0;
}

int restore_cache_replacemnt(mflash *mfl)
{
    u_int32_t data;
    MREAD4(CACHE_REPLACEMNT_EN_ADDR, &data);
    data = MERGE(data, 1, 0, 1); // We put 1 in the first bit of the read data
    MWRITE4(CACHE_REPLACEMNT_EN_ADDR, data);
    return MFE_OK;
}

int connectib_flash_lock(mflash* mfl, int lock_state)
{
   int rc;
   if (lock_state == 1) { // lock the flash
       rc = is4_flash_lock(mfl, lock_state); CHECK_RC(rc);
       rc = disable_cache_replacement(mfl);  CHECK_RC(rc);
       rc = gw_wait_ready(mfl, "WAIT TO BUSY"); CHECK_RC(rc);
   } else { // unlock the flash
       rc = restore_cache_replacemnt(mfl);   CHECK_RC(rc);
       rc = is4_flash_lock(mfl, lock_state); CHECK_RC(rc);
   }
   return MFE_OK;
}

#define SX_CS_SUPPORT_ADDR 0xF0420

int sx_init_cs_support(mflash* mfl) {
    if (is_sx(mfl->attr.hw_dev_id)) {
        u_int8_t cs_support_mask = 0;
        u_int32_t data;
        if (mfl->opts[MFO_USER_BANKS_NUM] == 0) {
            // We assume we have only 2 flashes on SX
            mfl->opts[MFO_NUM_OF_BANKS] = 2;
        }
        // Prepare the bit mask of the banks number
        cs_support_mask = (1 << mfl->opts[MFO_NUM_OF_BANKS]) - 1;

        // Read Modify write the cs support field
        MREAD4(SX_CS_SUPPORT_ADDR, &data);
        data = MERGE(data, cs_support_mask, 0, 4);
        MWRITE4(SX_CS_SUPPORT_ADDR, data);
    }
    return 0;
}

#define HW_DEV_ID     0xf0014
#define CACHE_REP_OFF 0xf0408
#define CASHE_REP_CMD 0xf040c

int check_cache_replacement_gaurd(mflash* mfl, u_int8_t *needs_cache_replacement)
{

    *needs_cache_replacement = 0;

    // When we access via command interface, we assume there is a cache replacement!
    if (mfl->opts[MFO_SX_TYPE] == SXT_CMDIF) {
        *needs_cache_replacement = 1;
        return MFE_OK;
    }

    if (mfl->opts[MFO_IGNORE_CASHE_REP_GUARD] == 0) {
        u_int32_t off, cmd, data;

        // Read the Cache replacement offset
        MREAD4(CACHE_REP_OFF, &data);
        off = EXTRACT(data, 0, 26);
        // Read the Cache replacement cmd
        MREAD4(CASHE_REP_CMD, &data);
        cmd = EXTRACT(data, 16, 8);
        // Check if the offset and cmd are zero in order to continue burning.
        if (cmd != 0 || off != 0) {
            *needs_cache_replacement = 1;
        }
    } else {
        // Here we ignore the cache replacement check
        // We need to execute a write in order to do any needed cache replacement
        // Reset the HW ID which is read only register.
        MWRITE4(HW_DEV_ID, 0);
    }

    return MFE_OK;
}

int mfl_com_lock(mflash* mfl)
{
    int rc;
    rc = mfl->f_lock(mfl, 1);
    if (!mfl->opts[MFO_IGNORE_SEM_LOCK]) {
        CHECK_RC(rc);
    } else {
        mfl->is_locked = 1;
    }
    return MFE_OK;
}

// ConnectX and Shaldag flash interfaces are identical (except lock function)
// Use same functions
//
// TODO: Unify fith ConnectX inif function

int gen4_flash_init_com(mflash* mfl, flash_params_t* flash_params, u_int8_t init_cs_support) {

    int rc;

    //TODO: Enable page_read (slightly better perf)
    //mfl->f_read           = cntx_st_spi_page_read;
    mfl->f_read           = read_chunks;
    mfl->f_read_blk       = cntx_st_spi_block_read;
    mfl->f_set_bank       = empty_set_bank;
    mfl->f_get_info       = cntx_get_flash_info;


    rc = mfl_com_lock(mfl); CHECK_RC(rc);

    if (init_cs_support) {
        // Update the chip_select_support according to the banks number of cs.
        rc = sx_init_cs_support(mfl);  CHECK_RC(rc);
    }
    mfl->f_spi_status = cntx_st_spi_get_status;

    rc = st_spi_fill_attr(mfl, flash_params);   CHECK_RC(rc);

    if        (mfl->attr.command_set == MCS_STSPI || mfl->attr.command_set == MCS_SSTSPI) {
        mfl->f_reset      = empty_reset; // Null func
        //mfl->f_write_blk  = cntx_st_spi_block_write;
        mfl->f_write_blk  = get_write_blk_func(mfl->attr.command_set);
        mfl->attr.page_write = 256;
        mfl->f_write      = write_chunks;
        mfl->f_erase_sect = cntx_st_spi_erase_sect;
    } else {
        return MFE_UNSUPPORTED_FLASH_TYPE;
    }

    rc = mfl->f_reset(mfl);

    return MFE_OK;

}

int is4_flash_init(mflash* mfl, flash_params_t* flash_params) {

    mfl->f_lock           = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 0);
}

int sx_flash_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{
    mfl->f_lock           = is4_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 1);
}

int connectib_init_direct_access(mflash* mfl, flash_params_t* flash_params)
{

    mfl->f_lock           = connectib_flash_lock;
    return gen4_flash_init_com(mfl, flash_params, 0);
}
int mfl_get_bank_info(mflash *mfl, u_int32_t addr, u_int32_t *flash_off_p, int *bank_p)
{
    int rc;
    // Get the bank number
    rc = set_bank(mfl, addr);                                           CHECK_RC(rc);
    *bank_p = mfl->curr_bank;
    // Get the offset in the flash
    rc = get_flash_offset(addr, mfl->attr.log2_bank_size, flash_off_p); CHECK_RC(rc);
    return MFE_OK;
}


#ifdef NO_INBAND_ACCESS

int sx_get_flash_info(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    mfl = NULL;
    type_index = NULL;
    log2size = NULL;
    no_flash = NULL;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_block_read(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data)
{
    mfl = NULL;
    blk_addr = 0;
    blk_size = 0;
    data = NULL;

    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_block_write(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    mfl = NULL;
    addr = 0;
    size = 0;
    data = NULL;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_flash_lock(mflash* mfl, int lock_state)
{
    mfl = NULL;
    lock_state = 0;
    return MFE_NOT_SUPPORTED_OPERATION;
}

int sx_erase_sect(mflash* mfl, u_int32_t addr)
{
    mfl = NULL;
    addr = 0;
    return MFE_NOT_SUPPORTED_OPERATION;
}

#else

#include "mflash_inband.h"
#include "mflash_cmdif.h"
#include "mflash_uefi.h"

typedef int (*f_sx_flash_lock)      (mflash* mfl, int lock_state);
typedef int (*f_sx_erase_sect)      (mflash* mfl, u_int32_t addr);
typedef int (*f_sx_block_access)    (mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data);
typedef int (*f_sx_get_flash_info)  (mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash);


#ifdef __WIN__
 // On windows we don't support cmdIf access!
#define EXEC_FLASH_ACCESS_FUNC(mfl, inband_func, cmdif_func, arg, uefi_func, uefi_args) {\
	int rc;\
    if (mfl->access_type == MFAT_MFILE) {\
        if ( mfl->opts[MFO_SX_TYPE] == SXT_INBAND) {\
            rc = inband_func arg; CHECK_RC(rc);\
        } else {\
            return MFE_NOT_SUPPORTED_OPERATION;\
        }\
    } else {\
        return MFE_UNKOWN_ACCESS_TYPE;\
    }\
}

#else

#define EXEC_FLASH_ACCESS_FUNC(mfl, inband_func, cmdif_func, arg, uefi_func, uefi_args) {\
	int rc;\
	if (mfl->access_type == MFAT_MFILE) {\
        if ( mfl->opts[MFO_SX_TYPE] == SXT_INBAND) {\
            rc = inband_func arg; CHECK_RC(rc);\
        } else {\
            rc = cmdif_func  arg; CHECK_RC(rc);\
        }\
	} else if (mfl->access_type == MFAT_UEFI) {\
        rc = uefi_func uefi_args; CHECK_RC(rc);\
    } else {\
        return MFE_UNKOWN_ACCESS_TYPE;\
    }\
}

#endif

int sx_get_flash_info(mflash* mfl, unsigned *type_index, int *log2size, u_int8_t *no_flash)
{
    int rc;
    u_int8_t vendor, type, capacity;
    u_int32_t jedec_id;

    EXEC_FLASH_ACCESS_FUNC(mfl, mfi_get_jedec, mfci_get_jedec, (mfl->mf, mfl->curr_bank, &jedec_id),
            mfu_get_jedec, (mfl->uefi_dev, mfl->uefi_cmd_func, mfl->curr_bank, &jedec_id));

    //printf("-D- jedec_id = %#x\n", jedec_id);
    rc = get_info_from_jededc_id(jedec_id, &vendor, &type, &capacity); CHECK_RC(rc);

    // Return there is no flash when all the params are 0xff
    if (vendor == 0xff && type == 0xff && capacity == 0xff) {
        *no_flash = 1;
        return MFE_OK;
    }
    rc = get_type_index_by_vendor_and_type(vendor, type, type_index); CHECK_RC(rc);
    rc = get_log2size_by_capcity(*type_index, capacity, log2size);    CHECK_RC(rc);
    return MFE_OK;

}

// This
int sx_block_read(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data)
{
    int rc, bank;
    u_int32_t flash_offset;

    if (blk_size > (u_int32_t)mfl->attr.block_write  || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }
    rc = mfl_get_bank_info(mfl, blk_addr, &flash_offset, &bank); CHECK_RC(rc);
    COM_CHECK_ALLIGN(flash_offset, blk_size);
    EXEC_FLASH_ACCESS_FUNC(mfl, mfi_read_block, mfci_read_block, (mfl->mf, flash_offset, bank, blk_size, data),
            mfu_read_block, (mfl->uefi_dev, mfl->uefi_cmd_func, flash_offset, bank, blk_size, data));
    return MFE_OK;
}

int sx_block_write(mflash* mfl, u_int32_t addr, u_int32_t size, u_int8_t* data)
{
    int rc, bank;
    u_int32_t flash_offset;

    WRITE_CHECK_ALLIGN(addr, mfl->attr.block_write, size);


    rc = mfl_get_bank_info(mfl, addr, &flash_offset, &bank); CHECK_RC(rc);
    COM_CHECK_ALLIGN(flash_offset, size);
    EXEC_FLASH_ACCESS_FUNC(mfl, mfi_write_block, mfci_write_block, (mfl->mf, flash_offset, bank, size, data),
            mfu_write_block, (mfl->uefi_dev, mfl->uefi_cmd_func, flash_offset, bank, size, data));
    return MFE_OK;
}

int sx_flash_lock(mflash* mfl, int lock_state)
{
    EXEC_FLASH_ACCESS_FUNC(mfl, mfi_flash_lock, mfci_flash_lock, (mfl->mf, lock_state),
            mfu_flash_lock, (mfl->uefi_dev, mfl->uefi_cmd_func, lock_state));

    return MFE_OK;
}

int sx_erase_sect(mflash* mfl, u_int32_t addr)
{
    int rc, bank;
    u_int32_t flash_addr;

    rc = mfl_get_bank_info(mfl, addr, &flash_addr, &bank); CHECK_RC(rc);
    EXEC_FLASH_ACCESS_FUNC(mfl, mfi_erase_sector, mfci_erase_sector, (mfl->mf, flash_addr, bank),
            mfu_erase_sector, (mfl->uefi_dev, mfl->uefi_cmd_func, flash_addr, bank));

    return MFE_OK;
}

#endif
int empty_get_status(mflash* mfl, u_int8_t op_type, u_int8_t* status)
{
    // Avoid warnings
    mfl = NULL;
    op_type = 0;
    status = NULL;

    return MFE_NOT_SUPPORTED_OPERATION;
}

#define CMDIF_MAX_BLOCK_WRITE  128
#define INBAND_MAX_BLOCK_WRITE 32
int flash_init_inband_access(mflash* mfl, flash_params_t* flash_params)
{
    int rc;

    mfl->f_read       = read_chunks;
    mfl->f_write      = write_chunks;
    mfl->f_reset      = empty_reset;
    mfl->f_set_bank   = empty_set_bank;


    mfl->f_get_info   = sx_get_flash_info;
    mfl->f_lock       = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk  = sx_block_write;
    mfl->f_read_blk   = sx_block_read;
    mfl->f_spi_status = empty_get_status;


    // Lock the FW semaphore which synchronizes between multiple processes
    rc = mfl_com_lock(mfl); CHECK_RC(rc);
    // Get the flash attribute
    rc = st_spi_fill_attr(mfl, flash_params);   CHECK_RC(rc);

    mfl->attr.block_write = INBAND_MAX_BLOCK_WRITE;
    mfl->attr.page_write  = INBAND_MAX_BLOCK_WRITE;


    return MFE_OK;
}

int uefi_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc;

    mfl->f_read       = read_chunks;
    mfl->f_write      = write_chunks;
    mfl->f_reset      = empty_reset;
    mfl->f_set_bank   = empty_set_bank;

    mfl->f_get_info   = sx_get_flash_info;
    mfl->f_lock       = sx_flash_lock;
    mfl->f_erase_sect = sx_erase_sect;
    mfl->f_write_blk  = sx_block_write;
    mfl->f_read_blk   = sx_block_read;
    mfl->f_spi_status = empty_get_status;


    // Lock the FW semaphore which synchronizes between multiple processes
    rc = mfl_com_lock(mfl); CHECK_RC(rc);
    // Get the flash attribute

    rc = st_spi_fill_attr(mfl, flash_params);   CHECK_RC(rc);

    mfl->attr.block_write = 16;
    mfl->attr.page_write  = 16;
/*
    mfl->attr.block_write = INBAND_MAX_BLOCK_WRITE;
    mfl->attr.page_write  = INBAND_MAX_BLOCK_WRITE;
*/
    return MFE_OK;
}


int flash_init_fw_access(mflash* mfl, flash_params_t* flash_params)
{
    // This function checks the access type in order to select the access functions

    int rc;
    if ( mfl->opts[MFO_SX_TYPE] != SXT_NO) {
        rc = flash_init_inband_access(mfl, flash_params); CHECK_RC(rc);
    } else {
        return MFE_DIRECT_FW_ACCESS_DISABLED;
    }
    return MFE_OK;
}

int sx_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc;
    u_int8_t needs_cache_replacement;

    rc = check_cache_replacement_gaurd(mfl, &needs_cache_replacement); CHECK_RC(rc);

    if (needs_cache_replacement) {
        rc = flash_init_fw_access(mfl, flash_params); CHECK_RC(rc);
    } else {
        rc = sx_flash_init_direct_access(mfl, flash_params); CHECK_RC(rc);
    }
    return MFE_OK;
}



int connectib_flash_init(mflash* mfl, flash_params_t* flash_params)
{
    int rc;
    u_int8_t needs_cache_replacement;

    rc = check_cache_replacement_gaurd(mfl, &needs_cache_replacement); CHECK_RC(rc);

    if (needs_cache_replacement) {
        rc = flash_init_fw_access(mfl, flash_params); CHECK_RC(rc);
    } else {
        rc = connectib_init_direct_access(mfl, flash_params); CHECK_RC(rc);
    }
    return MFE_OK;
}

//
// Interface functions:
//

int     mf_read        (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data) {
    // printf("mfl->attr.size = %#x, addr = %#x, len = %d\n", mfl->attr.size, addr, len);
    if (addr + len > mfl->attr.size) {
        return MFE_OUT_OF_RANGE;
    }
    //printf("-D- mf_read:  addr: %#x, len: %d\n", addr, len);
    return mfl->f_read(mfl, addr, len, data);
}

int     mf_write       (mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data) {
    if (addr + len > mfl->attr.size) {
        return MFE_OUT_OF_RANGE;
    }

    return mfl->f_write(mfl, addr, len, data);
}

int     mf_erase_sector(mflash* mfl, u_int32_t addr) {
    if (addr >= mfl->attr.size) {
        return MFE_OUT_OF_RANGE;
    }
    return mfl->f_erase_sect(mfl, addr);
}

int mf_open_ignore_lock(mflash* mfl) {
    mfl->opts[MFO_IGNORE_SEM_LOCK] = 1;
    return mf_open_fw(mfl, NULL);
}




#define CR_LOCK_HW_ID 0xbad0cafe


int update_sx_type(mflash* mfl)
{
    u_int32_t dev_flags;
    int rc;
    // The opt MFO_SX_TYPE will be used only when work on SX device
    mfl->opts[MFO_SX_TYPE] = SXT_NO;
    rc = mget_mdevs_flags(mfl->mf, &dev_flags); CHECK_RC(rc);

    if (dev_flags & MDEVS_IB) {
        mfl->opts[MFO_SX_TYPE] = SXT_INBAND;
    } else if (dev_flags & MDEVS_MLNX_OS) {
        mfl->opts[MFO_SX_TYPE] = SXT_CMDIF;
    }
    return MFE_OK;

}
//Caller must zero the mflash struct before calling this func.
int mf_open_fw(mflash* mfl, flash_params_t* flash_params)
{
    int rc;
    u_int32_t dev_id;

    if (!mfl) {
        return MFE_BAD_PARAMS;
    }
    mfl->curr_bank = -1;

    if (mfl->access_type == MFAT_MFILE ) {
        rc = update_sx_type(mfl); CHECK_RC(rc);
        //printf("-D- mf_open_fw: mget_mdevs_flags\n");
        if (mfl->opts[MFO_SX_TYPE] == SXT_CMDIF) {
            // HACK: When we have a mlnxsw device we don't have any access to cr-space so we will assume we work on SX
            dev_id = SWITCHX_HW_ID;
        } else {
            MREAD4(HW_DEV_ID, &dev_id);
        }
        if (dev_id == CR_LOCK_HW_ID) {
            return MFE_LOCKED_CRSPACE;
        }

        mfl->attr.rev_id    = (dev_id & 0xff0000) >> 16;

        dev_id &= 0xffff;
        mfl->attr.hw_dev_id = dev_id;
        if (dev_id == 23108 || dev_id == 25208 || dev_id == 24204 || dev_id == 25204) {
            rc = MFE_OLD_DEVICE_TYPE;
        } else if (is_connectx_family(dev_id)) {
            rc = cntx_flash_init(mfl, flash_params);
        } else if (is_is4_family(dev_id)) {
            rc = is4_flash_init(mfl, flash_params);
        } else if (is_sx(dev_id)) {
            rc = sx_flash_init(mfl, flash_params);
        } else if (is_connectib(dev_id)) {
            rc = connectib_flash_init(mfl, flash_params);
        } else if (dev_id == 0xffff) {
            printf("-E- Read a corrupted device id (0x%x). Probably HW/PCI access problem\n", dev_id);
            rc = MFE_CR_ERROR;
        } else {
            rc = MFE_UNSUPPORTED_DEVICE;
        }
        CHECK_RC(rc);
    } else if (mfl->access_type == MFAT_UEFI) {
        rc = uefi_flash_init(mfl, flash_params); CHECK_RC(rc);
    } else {
        return MFE_UNKOWN_ACCESS_TYPE;
    }
    mfl->f_set_bank(mfl,0);

    return MFE_OK;
}

int     mf_opend_int       (mflash** pmfl, void* access_dev, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard, u_int8_t access_type,
        void* access_func) {
    int rc;
    *pmfl = (mflash*)malloc(sizeof(mflash));
    if (!*pmfl) {
        return MFE_NOMEM;
    }

    memset(*pmfl, 0, sizeof(mflash));
    (*pmfl)->opts[MFO_NUM_OF_BANKS] = spi_get_num_of_flashes(num_of_banks);

    rc = spi_update_num_of_banks((*pmfl), num_of_banks); CHECK_RC(rc);

    (*pmfl)->opts[MFO_IGNORE_CASHE_REP_GUARD] = ignore_cache_rep_guard;
    (*pmfl)->access_type = access_type;

    if (access_type ==  MFAT_MFILE) {
        (*pmfl)->mf = (mfile*)access_dev;
    } else if (access_type ==  MFAT_UEFI) {
        (*pmfl)->uefi_dev = (uefi_Dev_t*)access_dev;
        (*pmfl)->uefi_cmd_func = (f_fw_cmd)access_func;
    }

    rc = mf_open_fw(*pmfl, flash_params);
    return rc;
}


int     mf_opend       (mflash** pmfl, struct mfile_t* mf, int num_of_banks, flash_params_t* flash_params, int ignore_cache_rep_guard) {
    return mf_opend_int(pmfl, mf, num_of_banks, flash_params, ignore_cache_rep_guard, MFAT_MFILE, NULL);
}



int     mf_open_uefi(mflash** pmfl, uefi_Dev_t *uefi_dev, f_fw_cmd fw_cmd_func)
{
    return mf_opend_int(pmfl, uefi_dev, 4, NULL, 0, MFAT_UEFI, fw_cmd_func);
}


int     mf_open        (mflash** pmfl, const char* dev, int num_of_banks, flash_params_t* flash_params,
        int ignore_cache_rep_guard)
{
    mfile*  mf;

    int rc;

    if (!dev) {
        return MFE_BAD_PARAMS;
    }

    mf = mopen(dev);

    if (!mf) {
        return MFE_CR_ERROR;
    }

    rc = mf_opend(pmfl, (struct mfile_t*) mf, num_of_banks, flash_params, ignore_cache_rep_guard);

    if ((*pmfl)) {
        (*pmfl)->opts[MFO_CLOSE_MF_ON_EXIT] = 1;
    }

    CHECK_RC(rc);

    return MFE_OK;
}

int release_semaphore(mflash* mfl) {
    int rc;
    if (mfl->is_locked && mfl->f_lock) {
        rc = mfl->f_lock(mfl, 0); CHECK_RC(rc);
    }
    return MFE_OK;
}

int     mf_close       (mflash* mfl) {
    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    if (mfl->f_reset) {
        mfl->f_reset(mfl);
    }

    if (mfl->f_set_bank) {
        set_bank(mfl, 0);
    }

    release_semaphore(mfl);

    if (mfl->mf && (mfl)->opts[MFO_CLOSE_MF_ON_EXIT]) {
        mclose(mfl->mf);
    }

    free(mfl);
    return MFE_OK;
}


int     mf_get_attr    (mflash* mfl, flash_attr* attr) {
    *attr = mfl->attr;
    return MFE_OK;
}

int     mf_sw_reset     (mflash* mfl) {
    if (msw_reset(mfl->mf)) {
        if (errno == EPERM) {
            return MFE_CMD_SUPPORTED_INBAND_ONLY;
        } else if (errno == OP_NOT_SUPPORTED) {
            return MFE_MANAGED_SWITCH_NOT_SUPPORTED;
        } else {

            return MFE_ERROR;
        }
    }

    return MFE_OK;
}



const char*   mf_err2str (int err_code) {
    static char* mf_err_str[] = {
    "MFE_OK",
    "MFE_GENERAL_ERROR",
    "MFE_BAD_PARAMS",
    "MFE_CR_ERROR",
    "MFE_INVAL",
    "MFE_NOT_IMPLEMENTED",
    "MFE_UNSUPPORTED_FLASH_TOPOLOGY",
    "MFE_UNSUPPORTED_FLASH_TYPE",
    "MFE_CFI_FAILED",
    "MFE_TIMEOUT",
    "MFE_ERASE_TIMEOUT",
    "MFE_WRITE_TIMEOUT",
    "MFE_ERASE_ERROR",
    "MFE_WRITE_ERROR",
    "MFE_BAD_ALIGN",
    "MFE_SEM_LOCKED",
    "MFE_VERIFY_ERROR",
    "MFE_NOMEM",
    "MFE_OUT_OF_RANGE",
    "MFE_CMD_SUPPORTED_INBAND_ONLY",
    "MFE_NO_FLASH_DETECTED",
    "MFE_HW_ACCESS_DISABLED",
    "MFE_CMDIF_BAD_STATUS_ERR",
    "MFE_CMDIF_TIMEOUT_ERR",
    "MFE_CMDIF_GO_BIT_BUSY",
    "MFE_MISMATCH_KEY",
    "MFE_UNKNOWN_REG",
    "MFE_REG_ACCESS_FAILED",
    "MFE_REG_ACCESS_MAD_BAD_STATUS",
    "MFE_REG_ACCESS_MAD_NOT_SUPPORTED",
    "MFE_DIRECT_FW_ACCESS_DISABLED",
    "MFE_MANAGED_SWITCH_NOT_SUPPORTED",
    "MFE_NOT_SUPPORTED_OPERATION",
    "MFE_REG_ACCESS_FW_BAD_STATUS",
    "MFE_FLASH_NOT_EXIST",
    "MFE_MISMATCH_QUAD_EN",
    "MFE_EXCEED_SUBSECTORS_MAX_NUM",
    "MFE_EXCEED_SECTORS_MAX_NUM",
    "MFE_SECTORS_NUM_NOT_POWER_OF_TWO",
    "MFE_REG_ACCESS_RESOURCE_NOT_AVAILABLE",
    "MFE_UNKOWN_ACCESS_TYPE",
    "MFE_UNSUPPORTED_DEVICE",
    "MFE_OLD_DEVICE_TYPE",
    };

    return err_code < (int)ARRSIZE(mf_err_str) ? mf_err_str[err_code] : NULL;
}

int     mf_set_opt     (mflash* mfl, MfOpt opt, int  val) {
    if ((int)opt < 0 || opt >= MFO_LAST) {
        return MFE_BAD_PARAMS;
    }
    mfl->opts[opt] = val;
    return MFE_OK;
}

int     mf_get_opt     (mflash* mfl, MfOpt opt, int *val) {
    if ((int)opt < 0 || opt >= MFO_LAST) {
        return MFE_BAD_PARAMS;
    }
    *val = mfl->opts[opt];
    return MFE_OK;
}


int     mf_cr_read     (mflash* mfl, u_int32_t cr_addr, u_int32_t* data) {
    if (mread4(mfl->mf, cr_addr, data) != 4) {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}
int     mf_cr_write    (mflash* mfl, u_int32_t cr_addr, u_int32_t  data) {
    if (mwrite4(mfl->mf, cr_addr, data) != 4) {
        return MFE_CR_ERROR;
    }
    return MFE_OK;
}

#define BOOT_CR_SPACE_ADDR 0xf0000
int     mf_update_boot_addr(mflash* mfl, u_int32_t boot_addr)
{
    int rc;
//orenk 
//    if (mfl->access_type == MFAT_UEFI || mfl->opts[MFO_SX_TYPE] == SXT_CMDIF) {
//        EXEC_FLASH_ACCESS_FUNC(mfl, mfi_update_boot_addr, mfci_update_boot_addr, (mfl->mf, mfl->curr_bank, boot_addr),
//                mfu_update_boot_addr, (mfl->uefi_dev, mfl->uefi_cmd_func, mfl->curr_bank, boot_addr));
//    } else {
        rc = mf_cr_write(mfl, BOOT_CR_SPACE_ADDR, ((boot_addr << 8) | 0x06)); CHECK_RC(rc);
//    }
    return MFE_OK;
}

int     mf_read_modify_status (mflash *mfl, u_int8_t bank_num, u_int8_t first_byte, u_int8_t param, u_int8_t offset, u_int8_t size)
{
    u_int8_t status1, status2;
    u_int32_t status;
    int rc;


    mfl->curr_bank = bank_num;

    // Read register status
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status1); CHECK_RC(rc);
    rc = mfl->f_spi_status(mfl, SFC_RDSR2, &status2); CHECK_RC(rc);


    // printf("-D- BEFORE status1 = %#x, status2 = %#x\n", status1, status2);

    // Prepare the read status word
    status = MERGE(0, status2, 16, 8);
    status = MERGE(status, status1, 24, 8);
    // Modify the status according to the function arguments
    status = MERGE(status, param, 16 + offset + first_byte * 8 , size);
    // printf("-D- status1 = %#x.\n", status);

    // Write register status
    rc = cntx_spi_write_status_reg(mfl, status, 1); CHECK_RC(rc);
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status1); CHECK_RC(rc);
    rc = mfl->f_spi_status(mfl, SFC_RDSR2, &status2); CHECK_RC(rc);
        // printf("-D- AFTER status1 = %#x, status2 = %#x\n", status1, status2);
    return MFE_OK;
}
#define QUAD_EN_OFFSET 1

int     mf_set_quad_en (mflash *mfl, u_int8_t quad_en)
{
    int bank, rc;
    if (!mfl->attr.quad_en_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    for (bank = 0; bank < mfl->attr.banks_num; bank++) {
        rc = mf_read_modify_status(mfl, bank, 0, quad_en, QUAD_EN_OFFSET, 1); CHECK_RC(rc);
    }
    return MFE_OK;
}

int mf_get_quad_en(mflash* mfl, u_int8_t *quad_en_p)
{
    u_int8_t status, is_first = 1, bank;
    int rc;
    if (!mfl->attr.quad_en_support) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }

    for (bank = 0; bank < mfl->attr.banks_num; bank++ ) {
        u_int8_t curr_quad_en;
        mfl->curr_bank = bank;

        rc = mfl->f_spi_status(mfl, SFC_RDSR2, &status); CHECK_RC(rc);
        curr_quad_en = EXTRACT(status, QUAD_EN_OFFSET, 1);
        if (is_first) {
            *quad_en_p = curr_quad_en;
            is_first = 0;
        } else {
            if (*quad_en_p != curr_quad_en) {
                return MFE_MISMATCH_QUAD_EN;
            }
        }
    }
    return MFE_OK;
}

#define REG1_TB_OFFSET  5
#define REG1_SEC_OFFSET 6
#define REG1_BP_OFFSET 2
#define REG1_BP_SIZE   3
#define ONE_BIT_SIZE   1

#define WRITE_PROTECT_CHECKS(mfl, bank_num) { \
	    if (!mfl->attr.write_protect_support) {\
	        return MFE_NOT_SUPPORTED_OPERATION;\
	    }\
	    if (bank_num >= mfl->attr.banks_num) {\
	        return MFE_FLASH_NOT_EXIST;\
	    }\
}
#define MAX_SUBSECTOR_NUM 8
#define MAX_SECTORS_NUM   64

int     mf_set_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    u_int8_t protect_mask = 0, log2_sect_num = 0;
    u_int8_t sectors_num =  protect_info->sectors_num;

    //printf("-D- mf_set_write_protect: bank_num = %#x, subsec: %#x, bottom: %#x, sectors_num=%#x\n", bank_num,
    //       protect_info->is_subsector, protect_info->is_bottom, protect_info->sectors_num);

    WRITE_PROTECT_CHECKS(mfl, bank_num);
    if (((protect_info->sectors_num - 1) & protect_info->sectors_num) != 0) {
        return MFE_SECTORS_NUM_NOT_POWER_OF_TWO;
    }
    if (protect_info->sectors_num > MAX_SECTORS_NUM) {
        return MFE_EXCEED_SECTORS_MAX_NUM;
    }

    if (protect_info->is_subsector) {
        if (protect_info->sectors_num > MAX_SUBSECTOR_NUM) {
            return MFE_EXCEED_SUBSECTORS_MAX_NUM;
        }
    }

    for (log2_sect_num = 0; log2_sect_num < 8; log2_sect_num++) {
        if (sectors_num == 0) {
            break;
        }
        sectors_num >>= 1;
        // printf("-D- sectors_num = %d\n", sectors_num);
    }
    protect_mask = MERGE(protect_mask, log2_sect_num, 0, REG1_BP_SIZE);
    protect_mask = MERGE(protect_mask, protect_info->is_bottom, REG1_BP_SIZE, ONE_BIT_SIZE);
    protect_mask = MERGE(protect_mask, protect_info->is_subsector, REG1_BP_SIZE + ONE_BIT_SIZE, ONE_BIT_SIZE);

    // printf("-D- protect mask: %#x\n", protect_mask);
    return mf_read_modify_status(mfl, bank_num, 1, protect_mask, REG1_BP_OFFSET, REG1_BP_SIZE + 2 * ONE_BIT_SIZE);
}

int     mf_get_write_protect(mflash *mfl, u_int8_t bank_num, write_protect_info_t *protect_info)
{
    int rc;
    u_int8_t status;
    WRITE_PROTECT_CHECKS(mfl, bank_num);
    mfl->curr_bank = bank_num;
    // printf("-D- bank _num = %d\n", bank_num);
    rc = mfl->f_spi_status(mfl, SFC_RDSR, &status); CHECK_RC(rc);
    // printf("-D- status = %#x\n", status);
    protect_info->is_bottom = EXTRACT(status, REG1_TB_OFFSET, 1);
    protect_info->is_subsector = EXTRACT(status, REG1_SEC_OFFSET, 1);
    protect_info->sectors_num = 1 << (EXTRACT(status, REG1_BP_OFFSET, REG1_BP_SIZE) - 1);

    return MFE_OK;
}

/**********************************************************************************************/
/// THIS PART SHOULD BE MOVED TO A COMMON PLACE - CMDIF LIB

#define TOOLS_HCR_ADDR         0x80780
#define IF_CMD_UNLOCK_CR_SPACE 0x60
#define CMD_IF_SIZE            28
#define CMD_IF_WAIT_GO         2000

typedef struct mf_cmd_if {
    u_int64_t in_param;
    u_int64_t out_param;
    u_int32_t input_modifier;
    u_int16_t token;
    u_int16_t opcode;
    u_int8_t  opcode_modifier;
    u_int8_t  t;
    u_int8_t  e;
    u_int8_t  go;
    u_int8_t  status;
} mf_cmd_if_t;

static void cmd_if_pack(mf_cmd_if_t* cmd, u_int32_t* buf) {
    memset((char*)buf, 0, CMD_IF_SIZE);
    buf[0] = EXTRACT64(cmd->in_param, 32, 32);
    buf[1] = EXTRACT64(cmd->in_param,  0, 32);
    buf[2] = cmd->input_modifier;
    // out h
    // out l
    buf[5] = MERGE(buf[5], cmd->token,               16, 16);
    buf[6] = MERGE(buf[6], cmd->opcode,               0, 12);
    buf[6] = MERGE(buf[6], cmd->opcode_modifier,     12,  4);
    buf[6] = MERGE(buf[6], cmd->e,                   22,  1);
}

static void cmd_if_unpack(mf_cmd_if_t* cmd, u_int32_t* buf) {
    memset(cmd, 0, sizeof(mf_cmd_if_t));

    cmd->in_param       = MERGE64(cmd->in_param, buf[0], 32, 32);
    cmd->in_param       = MERGE64(cmd->in_param, buf[1],  0, 32);
    cmd->input_modifier = buf[2];
    cmd->out_param      = MERGE64(cmd->out_param, buf[3], 32, 32);
    cmd->out_param      = MERGE64(cmd->out_param, buf[4],  0, 32);
    cmd->opcode         = EXTRACT(buf[6], 0, 12);
    cmd->opcode_modifier= EXTRACT(buf[6], 12, 4);

    cmd->status         = EXTRACT(buf[6], 24, 8);
}

static int cmd_if_wait_go(mflash* mfl, int* retries)
{
    int i;
    u_int8_t go_bit;

    for (i = 0; i < CMD_IF_WAIT_GO; i++) {
        u_int32_t word;
        MREAD4(TOOLS_HCR_ADDR + CMD_IF_SIZE - 4, &word);
        /*
        if (mread4( mf, TOOLS_HCR_ADDR + CMD_IF_SIZE - 4, &word) != 4) {
            return 3;
        }
        */
        go_bit = EXTRACT(word, 23, 1);
        if (!go_bit) {
            if (retries) {
                *retries = i;
            }
            return 0;
        }
    }
    return MFE_CMDIF_GO_BIT_BUSY;
}

static int cmd_if_send(mflash* mfl, mf_cmd_if_t* cmd)
{

    u_int32_t raw_cmd[CMD_IF_SIZE/4];
    int act_retries;
    int rc;

    // Check if the go BIT is ready
    rc = cmd_if_wait_go(mfl, NULL);
    if (rc) {
        //printf("cmd_if_send: GO bit set before command issued (rc=%d)\n", rc);
        return MFE_CMDIF_GO_BIT_BUSY;
    }
    // Prepare the date of the command we're gonna execute
    cmd_if_pack(cmd, raw_cmd);

    if (mwrite4_block(mfl->mf, TOOLS_HCR_ADDR, raw_cmd, CMD_IF_SIZE) != CMD_IF_SIZE) {
        return MFE_CR_ERROR;
    }

    raw_cmd[6] = MERGE(raw_cmd[6],      1,                   23,  1); // go
    MWRITE4(TOOLS_HCR_ADDR + 24, raw_cmd[6]);

    rc = cmd_if_wait_go(mfl, &act_retries);
    if (rc) {
        return MFE_CMDIF_TIMEOUT_ERR;
    }

    if (mread4_block(mfl->mf, TOOLS_HCR_ADDR, raw_cmd, CMD_IF_SIZE) != CMD_IF_SIZE) {
        return MFE_CR_ERROR;
    }

    cmd_if_unpack(cmd, raw_cmd);

    if (cmd->status) {
        //printf("-E- CMD IF Bad status. Op: 0x%x Status: 0x%x\n", cmd->opcode, cmd->status);
        return MFE_CMDIF_BAD_STATUS_ERR; // TODO - Special return code here - needs a specific attention
    }
    return MFE_OK;
}

#define MISMATCH_KEY_RC 0x3
int cmdif_hw_access_int(mflash* mfl, u_int64_t key, u_int8_t opcode_modifier)
{
    mf_cmd_if_t cmd;
    int rc;

    my_memset(&cmd, 0, sizeof(cmd));

    // Prepare CMD IF
    cmd.opcode          = IF_CMD_UNLOCK_CR_SPACE;
    // Determine if we want to lock (1) or unlock (0)
    cmd.opcode_modifier = opcode_modifier;
    // Setting the given key
    cmd.in_param        = key;

    rc = cmd_if_send(mfl, &cmd);

    // Special case
    if (rc == MFE_CMDIF_BAD_STATUS_ERR && cmd.opcode_modifier == 0) {
        if (cmd.status == MISMATCH_KEY_RC) {
            return MFE_MISMATCH_KEY;
        }
    }
    return rc;
}

int mf_enable_hw_access(mflash* mfl, u_int64_t key)
{
    return cmdif_hw_access_int(mfl, key, 0 /* Unlock */);

}

int mf_disable_hw_access(mflash* mfl)
{
    int rc;
    // We need to release the semaphore because we will not have any access to semaphore after disabling the HW access
    rc = release_semaphore(mfl); CHECK_RC(rc);
    return cmdif_hw_access_int(mfl, 0, 1 /* Lock */);
}

/**********************************************************************************************/

