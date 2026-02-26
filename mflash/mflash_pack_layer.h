/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "mflash_types.h"
#include "mflash_common_structs.h"
#include "reg_access.h"

#include "dev_mgt/tools_dev_types.h"

#ifndef UEFI_BUILD
#include <tools_res_mgmt.h>
#else
typedef void* trm_ctx;
#endif

/* TODO: use: (int)log2((float)num) */
#define NEAREST_POW2(num)                                                                                \
    (num) < (256) ?                                                                                      \
    ((num) < (128) ?                                                                                     \
     ((num) < (64) ? ((num) < (32) ? ((num) < (16) ? ((num) < (8) ? (4) : (8)) : (16)) : (32)) : (64)) : \
     (128)) :                                                                                            \
    (256)

#ifndef CHECK_RC
#define CHECK_RC(rc)   \
    do                 \
    {                  \
        if (rc)        \
        {              \
            return rc; \
        }              \
    } while (0)
#endif

#ifndef ARR_SIZE
#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])
#endif

#ifndef IRISC
#define MFLASH_ERR_STR_SIZE 1024
#else
#define MFLASH_ERR_STR_SIZE 4
#endif

#define CX3_PRO_HW_ID       0x1F7
#define CX3_HW_ID           0x1F5
#define CX4_HW_ID           0x209
#define CX4LX_HW_ID         0x20b
#define CX5_HW_ID           0x20d
#define CX6_HW_ID           0x20f
#define CX7_HW_ID           0x218
#define CX8_HW_ID           0x21e
#define CX8_PURE_PCIE_SWITCH_HW_ID  0x222
#define CX9_HW_ID           0x224
#define CX9_PURE_PCIE_SWITCH_HW_ID  0x228
#define CX6DX_HW_ID         0x212
#define CX6LX_HW_ID         0x216
#define BLUEFIELD_HW_ID     0x211
#define BLUEFIELD2_HW_ID    0x214
#define BLUEFIELD3_HW_ID    0x21c
#define BLUEFIELD4_HW_ID    0x220
#define CONNECT_IB_HW_ID    0x1FF
#define SWITCH_IB_HW_ID     0x247
#define SPECTRUM_HW_ID      0x249
#define SWITCH_IB2_HW_ID    0x24b
#define QUANTUM_HW_ID       0x24d
#define SPECTRUM2_HW_ID     0x24e
#define SPECTRUM3_HW_ID     0x250
#define QUANTUM2_HW_ID      0x257
#define QUANTUM3_HW_ID      0x25b
#define NVLINK6_SWITCH_HW_ID 0x278
#define SPECTRUM4_HW_ID     0x254
#define SPECTRUM5_HW_ID     0x270
#define SPECTRUM6_HW_ID     0x274
#define INBAND_MAX_REG_SIZE 44

#define VSC_RECOVERY_SPACE_FLASH_GW_BASE_ADDRESS 0x10

/*
 * Device IDs Macros:
 */
#define IS_CONNECTX_4TH_GEN_FAMILY(dev_id) (((dev_id) == CX3_HW_ID) || ((dev_id) == CX3_PRO_HW_ID))
#define IS_SIB(dev_id)                     ((dev_id) == SWITCH_IB_HW_ID)
#define IS_SIB2(dev_id)                    ((dev_id) == SWITCH_IB2_HW_ID)
#define IS_SEN(dev_id)                     ((dev_id) == SPECTRUM_HW_ID)
#define IS_SPECTRUM2(dev_id)               ((dev_id) == SPECTRUM2_HW_ID)
#define IS_CONNECT_IB(dev_id)              ((dev_id) == CONNECT_IB_HW_ID)
#define IS_CONNECTX4(dev_id)               ((dev_id) == CX4_HW_ID)
#define IS_CONNECTX4LX(dev_id)             ((dev_id) == CX4LX_HW_ID)
#define IS_CONNECTX5(dev_id)               ((dev_id) == CX5_HW_ID)
#define IS_CONNECTX7(dev_id)               ((dev_id) == CX7_HW_ID)
#define IS_CONNECTX8(dev_id)               ((dev_id) == CX8_HW_ID)
#define IS_CONNECTX9(dev_id)               ((dev_id) == CX9_HW_ID)
#define IS_CONNECTX8_PURE_PCIE_SWITCH(dev_id) ((dev_id) == CX8_PURE_PCIE_SWITCH_HW_ID)
#define IS_CONNECTX9_PURE_PCIE_SWITCH(dev_id) ((dev_id) == CX9_PURE_PCIE_SWITCH_HW_ID)
#define IS_CONNECTX6(dev_id)               ((dev_id) == CX6_HW_ID)
#define IS_CONNECTX6DX(dev_id)             ((dev_id) == CX6DX_HW_ID)
#define IS_CONNECTX6LX(dev_id)             ((dev_id) == CX6LX_HW_ID)
#define IS_BLUEFIELD(dev_id)               ((dev_id) == BLUEFIELD_HW_ID)
#define IS_QUANTUM(dev_id)                 ((dev_id) == QUANTUM_HW_ID)
#define IS_SPECTRUM(dev_id)                ((dev_id) == SPECTRUM_HW_ID)
#define IS_BLUEFEILD(dev_id)               ((dev_id) == BLUEFIELD_HW_ID)
#define IS_BLUEFEILD2(dev_id)              ((dev_id) == BLUEFIELD2_HW_ID)
#define IS_BLUEFEILD3(dev_id)              ((dev_id) == BLUEFIELD3_HW_ID)
#define IS_BLUEFEILD4(dev_id)              ((dev_id) == BLUEFIELD4_HW_ID)
#define IS_QUANTUM2(dev_id)                ((dev_id) == QUANTUM2_HW_ID)
#define IS_QUANTUM3(dev_id)                ((dev_id) == QUANTUM3_HW_ID)
#define IS_NVLINK6_SWITCH(dev_id)          ((dev_id) == NVLINK6_SWITCH_HW_ID)
#define IS_SPECTRUM4(dev_id)               ((dev_id) == SPECTRUM4_HW_ID)
#define IS_SPECTRUM5(dev_id)               ((dev_id) == SPECTRUM5_HW_ID)
#define IS_SPECTRUM6(dev_id)               ((dev_id) == SPECTRUM6_HW_ID)

#define HAS_TOOLS_CMDIF(dev_id) ((((dev_id) == CX3_HW_ID) || ((dev_id) == CX3_PRO_HW_ID)))

typedef int (*f_mf_lock)(mflash* mfl, int lock_state);

typedef int (*f_mf_set_bank)(mflash* mfl, u_int32_t bank);
typedef int (*f_mf_read)(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data, bool verbose);
typedef int (*f_mf_write)(mflash* mfl, u_int32_t addr, u_int32_t len, u_int8_t* data);
typedef int (*f_mf_erase_sect)(mflash* mfl, u_int32_t addr);
typedef int (*f_mf_reset)(mflash* mfl);

typedef int (*f_st_spi_status)(mflash* mfl, u_int8_t op_type, u_int8_t* status);
typedef int (*f_mf_get_info)(mflash* mfl, flash_info_t* f_info, int* log2size, u_int8_t* no_flash);
typedef int (*f_mf_get_jedec_id)(mflash* mfl, u_int32_t* jedec_id);

/*
 * flash parameters methods get/set
 */
typedef int (*f_mf_get_quad_en)(mflash* mfl, u_int8_t* quad_en);
typedef int (*f_mf_set_quad_en)(mflash* mfl, u_int8_t quad_en);

typedef int (*f_mf_get_driver_strength)(mflash* mfl, u_int8_t* driver_strength);
typedef int (*f_mf_set_driver_strength)(mflash* mfl, u_int8_t driver_strength);

typedef int (*f_mf_get_write_protect)(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info);
typedef int (*f_mf_set_write_protect)(mflash* mfl, u_int8_t bank_num, write_protect_info_t* protect_info);

typedef int (*f_mf_get_dummy_cycles)(mflash* mfl, u_int8_t* num_of_cycles);
typedef int (*f_mf_set_dummy_cycles)(mflash* mfl, u_int8_t num_of_cycles);

typedef int (*f_cntx_st_spi_erase_sect)(mflash* mfl, u_int32_t addr);
typedef int (*f_cntx_int_spi_get_status_data)(mflash* mfl, u_int8_t op_type, u_int32_t* status, u_int8_t data_num);
typedef int (*f_cntx_st_spi_block_write_ex)(mflash  * mfl,
                                            u_int32_t blk_addr,
                                            u_int32_t blk_size,
                                            u_int8_t* data,
                                            u_int8_t  is_first,
                                            u_int8_t  is_last,
                                            u_int32_t total_size);
typedef int (*f_cntx_sst_spi_block_write_ex)(mflash* mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t* data);
typedef int (*f_cntx_st_spi_block_read_ex)(mflash  * mfl,
                                           u_int32_t blk_addr,
                                           u_int32_t blk_size,
                                           u_int8_t* data,
                                           u_int8_t  is_first,
                                           u_int8_t  is_last,
                                           bool      verbose);
typedef int (*f_cntx_spi_write_status_reg)(mflash* mfl, u_int32_t status_reg, u_int8_t write_cmd, u_int8_t bytes_num);

typedef enum FlashGen {
    LEGACY_FLASH = 0,
    SIX_GEN_FLASH,
    SEVEN_GEN_FLASH
} FlashGen;

/*/////////////////////////////////////////// */
/* */
/* MFlash struct */
/* */
/*/////////////////////////////////////////// */
struct mflash {
#ifndef IRISC
    mfile* mf;
#endif

    /* Functions: */
    f_mf_lock f_lock;

    f_mf_set_bank     f_set_bank;
    f_mf_get_info     f_get_info;
    f_mf_get_jedec_id f_get_jedec_id;

    f_mf_read       f_read;
    f_mf_write      f_write;
    f_mf_write      f_write_blk; /* write and write_block have the same signateure, but theyr'e not the same func ! */
    f_mf_read       f_read_blk; /* read  and read_block have the same signateure, but theyr'e not the same func ! */
    f_mf_erase_sect f_erase_sect;
    f_mf_reset      f_reset;

    f_mf_get_quad_en         f_get_quad_en;
    f_mf_set_quad_en         f_set_quad_en;
    f_mf_get_driver_strength f_get_driver_strength;
    f_mf_set_driver_strength f_set_driver_strength;
    f_mf_get_write_protect   f_get_write_protect;
    f_mf_set_write_protect   f_set_write_protect;
    f_mf_get_dummy_cycles    f_get_dummy_cycles;
    f_mf_set_dummy_cycles    f_set_dummy_cycles;

    /* Relevant for SPI flash (InfiniHostIIILx, ConnectX) only */
    f_st_spi_status f_spi_status;

    f_cntx_st_spi_erase_sect       f_st_spi_erase_sect;
    f_cntx_int_spi_get_status_data f_int_spi_get_status_data;
    f_cntx_st_spi_block_write_ex   f_st_spi_block_write_ex;
    f_cntx_sst_spi_block_write_ex  f_sst_spi_block_write_ex;
    f_cntx_st_spi_block_read_ex    f_st_spi_block_read_ex;
    f_cntx_spi_write_status_reg    f_spi_write_status_reg;

    /* when set(1) we support modification of the flash status register */
    u_int8_t supp_sr_mod;

    int curr_bank;
    int is_locked;
    int unlock_blocked;
    int flash_prog_locked;
    int unlock_flash_prog_allowed;
    /* if writer_lock is set, semaphore should be freed only in mf_close()/disable_hw_access() */
    int writer_lock;

    flash_attr attr;

    int  opts[MFO_LAST];
    char last_err_str[MFLASH_ERR_STR_SIZE];

    u_int8_t    access_type; /* 0 = mfile , 1 = uefi */
    trm_ctx     trm;
    dm_dev_id_t dm_dev_id;
    int         cputUtilizationApplied;
    int         cpuPercent;
    u_int32_t   cache_repacement_en_addr;
    u_int32_t   gcm_en_addr;
    u_int32_t   gw_addr_field_addr;
    u_int32_t   gw_data_field_addr;
    u_int32_t   gw_cmd_register_addr;
    u_int32_t   cache_rep_offset_field_addr;
    u_int32_t   cache_rep_cmd_field_addr;
    /* Below fields are initialized and used for mflash_new_gw.c only */
    u_int32_t gw_rw_bit_offset;
    u_int32_t gw_cmd_phase_bit_offset;
    u_int32_t gw_addr_phase_bit_offset;
    u_int32_t gw_data_phase_bit_offset;
    u_int32_t gw_cs_hold_bit_offset;
    u_int32_t gw_data_size_bit_offset;
    u_int32_t gw_data_size_bit_len;
    u_int32_t gw_chip_select_bit_offset;
    u_int32_t gw_addr_size_bit_offset;
    u_int32_t gw_cmd_bit_offset;
    u_int32_t gw_cmd_bit_len;
    u_int32_t gw_busy_bit_offset;
    u_int32_t gw_data_size_register_addr; /* Relevant to 7th gen flash GW */

    /* Frequency related fields relevant for CX7 and BF3 */
    bool      is_freq_handle_required;
    bool      is_freq_changed;
    u_int32_t core_clocks_per_usec_addr;
    u_int32_t flash_div_addr;
    u_int32_t orig_flash_div_reg; /* Whole register, not flash_div field only */
    u_int32_t core_clocks_per_usec;
};

typedef struct mfpa_command_args {
    u_int8_t  flash_bank;                /* IN */
    u_int32_t boot_address;              /* IN/OUT */
    int       num_of_banks;              /* OUT */
    u_int32_t jedec_id;                  /* OUT */
    u_int32_t fw_flash_sector_sz;        /* OUT */
    u_int8_t  supp_sub_and_sector_erase; /* OUT */
    u_int8_t  supp_sector_write_prot;    /* OUT */
    u_int8_t  supp_sub_sector_write_prot; /* OUT */
    u_int8_t  supp_quad_en;              /* OUT */
    u_int8_t  supp_dummy_cycles;         /* OUT */
} mfpa_command_args;

enum AccessTypeByMfile {
    ATBM_NO = 0,
    ATBM_INBAND,
    ATBM_MLNXOS_CMDIF,
    ATBM_ICMD,
    ATBM_TOOLS_CMDIF,
};

enum CntxCrConstants {
    HCR_FLASH_CMD                      = 0xf0400,
    HCR_FLASH_ADDR                     = 0xf0404,
    HCR_FLASH_CACHE_REPLACEMENT_OFFSET = 0xf0408,
    HCR_FLASH_CACHE_REPLACEMENT_CMD    = 0xf040c,
    HCR_FLASH_DATA                     = 0xf0410,
    HCR_CACHE_REPLACEMNT_EN_ADDR       = 0xf0420,
    /* Gearbox flash GW registers addresses */
    HCR_FLASH_GEARBOX_CMD                       = 0x2000,
    HCR_FLASH_GEARBOX_ADDR                      = 0x2004,
    HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_OFFSET  = 0x2008,
    HCR_FLASH_GEARBOX_DATA                      = 0x2010,
    HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_CMD     = 0x200c,
    HCR_FLASH_GEARBOX_CACHE_REPLACEMENT_EN_ADDR = 0x2020,
    /* 6th gen flash GW registers addresses */
    HCR_6GEN_FLASH_GW_BASE_ADDR         = 0xf0420,
    HCR_NEW_GW_FLASH_ADDR               = HCR_6GEN_FLASH_GW_BASE_ADDR,
    HCR_NEW_GW_CACHE_REPLACEMNT_EN_ADDR = 0xf0480,
    HCR_NEW_GW_GCM_EN_ADDR              = 0xf0440,
    /* 7th gen flash GW registers addresses */
    // QTM3/QTM4:
    HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR = 0x101000,
    HCR_7GEN_QTM3_FLASH_CMD          = HCR_7GEN_QTM3_FLASH_GW_BASE_ADDR,
    HCR_7GEN_QTM3_FLASH_DATA         = 0x101010,
    HCR_7GEN_QTM3_GCM_EN_ADDR        = 0x101028,
    HCR_7GEN_QTM3_FLASH_ADDR         = 0x10103c,
    HCR_7GEN_QTM3_FLASH_DATA_SIZE    = 0x101044,
    // SPC6:
    // For SPC6 and above : use flash agent1 instead of agent0
    HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR = 0x101080,
    HCR_7GEN_SPC6_FLASH_CMD = HCR_7GEN_SPC6_FLASH_GW_BASE_ADDR,
    HCR_7GEN_SPC6_FLASH_DATA = 0x101090,
    HCR_7GEN_SPC6_GCM_EN_ADDR = 0x1010a8,
    HCR_7GEN_SPC6_FLASH_ADDR = 0x1010bc,
    HCR_7GEN_SPC6_FLASH_DATA_SIZE = 0x1010c4,
    /* ARCUSE: */
    HCR_7GEN_ARCUSE_FLASH_CMD       = 0x101000,
    HCR_7GEN_ARCUSE_FLASH_DATA      = 0x101010,
    HCR_7GEN_ARCUSE_GCM_EN_ADDR     = 0x101028,
    HCR_7GEN_ARCUSE_FLASH_ADDR      = 0x10103c,
    HCR_7GEN_ARCUSE_FLASH_DATA_SIZE = 0x101044,
    /* CX8: */
    HCR_7GEN_CX8_FLASH_GW_BASE_ADDR = 0x8a1000,
    HCR_7GEN_CX8_FLASH_CMD          = HCR_7GEN_CX8_FLASH_GW_BASE_ADDR,
    HCR_7GEN_CX8_FLASH_DATA         = 0x8a1010,
    HCR_7GEN_CX8_GCM_EN_ADDR        = 0x8a1028,
    HCR_7GEN_CX8_FLASH_ADDR         = 0x8a103c,
    HCR_7GEN_CX8_FLASH_DATA_SIZE    = 0x8a1044,
    // CX9:
    HCR_7GEN_CX9_FLASH_GW_BASE_ADDR = HCR_7GEN_CX8_FLASH_GW_BASE_ADDR,
    HCR_7GEN_CX9_FLASH_CMD = HCR_7GEN_CX9_FLASH_GW_BASE_ADDR,
    HCR_7GEN_CX9_FLASH_DATA = HCR_7GEN_CX8_FLASH_DATA,
    HCR_7GEN_CX9_GCM_EN_ADDR = HCR_7GEN_CX8_GCM_EN_ADDR,
    HCR_7GEN_CX9_FLASH_ADDR = HCR_7GEN_CX8_FLASH_ADDR,
    HCR_7GEN_CX9_FLASH_DATA_SIZE = HCR_7GEN_CX8_FLASH_DATA_SIZE,


    /* Flash GW fields offsets and lengths */
    HBO_READ_OP      = 0,
    HBO_CMD_PHASE    = 2,
    HBO_ADDR_PHASE   = 3,
    HBS_DATA_SIZE    = 3,
    HBO_DATA_PHASE   = 4,
    HBO_DATA_SIZE    = 8,
    HBO_CS_HOLD      = 5,
    HBO_CHIP_SELECT  = 11,
    HBO_FLASH_ENABLE = 13, /* In old devices */
    HBO_ADDR_SIZE    = 14,
    HBO_CMD          = 16,
    HBS_CMD          = 8,
    HBO_BUSY         = 30,
    HBO_LOCK         = 31,
    /* 6th gen flash GW fields offsets and lengths */
    HBS_NEW_GW_DATA_SIZE   = 5,
    HBO_NEW_GW_CHIP_SELECT = 13,
    HBO_NEW_GW_ADDR_SIZE   = 15,
    /* 7th gen flash GW fields offsets and lengths */
    HBO_7GEN_RW          = 5,
    HBO_7GEN_CMD_PHASE   = 7,
    HBO_7GEN_ADDR_PHASE  = 8,
    HBO_7GEN_DATA_PHASE  = 9,
    HBO_7GEN_CS_HOLD     = 10,
    HBO_7GEN_CHIP_SELECT = 13,
    HBO_7GEN_ADDR_SIZE   = 15,
    HBO_7GEN_CMD         = 16,
    HBS_7GEN_CMD         = 8,
    HBO_7GEN_BUSY        = 30,

    /* GPIOs */
    HCR_GPIO_LOCK     = 0xf0048,
    HCR_GPIO_LOCK_VAL = 0xd42f,

    HCR_GPIO_DATA_OUT = 0xf0040,
    HCR_GPIO_MODE0    = 0xf0050,
    HCR_GPIO_MODE1    = 0xf004c,

    HBO_GPIO_CS = 25,
    HBS_GPIO_CS = 4
};

#define WRITE_CHECK_ALIGN(addr, block_write, size) \
    {                                              \
        if (addr & ((u_int32_t)block_write - 1))   \
        {                                          \
            return MFE_BAD_ALIGN;                  \
        }                                          \
        if (size & ((u_int32_t)block_write - 1))   \
        {                                          \
            return MFE_BAD_ALIGN;                  \
        }                                          \
    }

#define COM_CHECK_ALIGN(flash_addr, size) \
    {                                     \
        if (flash_addr & (size - 1))      \
        {                                 \
            return MFE_BAD_ALIGN;         \
        }                                 \
    }

/*////////////////////////////////// SX FLASH functions //////////////////////////////////// */

typedef u_int32_t (*f_reg_pack)(void* data_to_pack, u_int8_t* packed_buffer);
typedef void (*f_reg_unpack)(void* unpacked_data, u_int8_t* buffer_to_unpack);
typedef void (*f_reg_dump)(void* data_to_print, FILE* out_port);

int sx_st_block_access(mfile             * mf,
                       u_int32_t           flash_addr,
                       u_int8_t            bank,
                       u_int32_t           size,
                       u_int8_t          * data,
                       reg_access_method_t method);

int common_erase_sector(mfile* mf, u_int32_t addr, u_int8_t flash_bank, u_int32_t erase_size);

int run_mfpa_command(mfile* mf, u_int8_t access_cmd, mfpa_command_args* mfpa_args);

int com_get_jedec(mfile* mf, mfpa_command_args* mfpa_args);
int get_num_of_banks(mfile* mf);
int get_info_from_jededc_id(u_int32_t jededc_id, u_int8_t* vendor, u_int8_t* type, u_int8_t* capacity);
int get_type_index_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t density, unsigned* type_index);
int get_log2size_by_vendor_type_density(u_int8_t vendor, u_int8_t type, u_int8_t capacity, int* log2size);
int get_max_reg_size(mfile* mf);

int set_bank(mflash* mfl, u_int32_t addr);
int set_bank_int(mflash* mfl, int bank_num);
int get_bank_int(mflash* mfl);
int get_flash_offset(u_int32_t addr, int log2_bank_size, u_int32_t* flash_addr_p);
int mfl_get_bank_info(mflash* mfl, u_int32_t addr, u_int32_t* flash_off_p, int* bank_p);
MfError MError2MfError(MError rc);

#endif /* MFLASH_COMMON_H_ */
