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


#ifndef MLXFWOP_COM_H
#define MLXFWOP_COM_H

#include <compatibility.h>

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif
#define MLXFWOPCALL __cdecl

#else
#define MLXFWOP_API
#define MLXFWOPCALL
#endif

#ifndef UEFI_BUILD
    #define EFIAPI
#endif

typedef int EFIAPI (*f_prog_func) (int completion);
typedef int (*f_prog_func_str) (char* str);

#define VSD_LEN  208
#define PSID_LEN 16
#define PRODUCT_VER_LEN 16

#define FREE_STR_MAX_LEN    256

#define MAX_ROMS_NUM        5
#define MAX_ROM_ERR_MSG_LEN 256
#define ROM_INFO_SIZE       12

//min version that supports Rom Modify
#define MAJOR_MOD_ROM_FW    2
#define MINOR_MOD_ROM_FW    6
#define SUBMINOR_MOD_ROM_FW 1410

//Macros
#define PRINT_PROGRESS(printFunc, arg) \
	do {\
	    if (printFunc) {\
	        printFunc((arg));\
	    }\
	} while(0)\

enum {
    GUIDS         = 4,
    MACS          = 2,
    MAX_GUIDS     = 32
};

// needed for flint query
enum {
     BX_NP_GUIDS   = 2,
     BX_SYS_GUIDS  = 1,
     BX_GUIDS      = BX_NP_GUIDS + BX_SYS_GUIDS,
     BX_IMACS      = 3,
     BX_EMACS      = 4,
     BX_MACS       = BX_EMACS + BX_IMACS,
     BX_WWPNS      = 4,
     BX_WWNNS      = 1,
     BX_SLICE_GUIDS = BX_WWNNS + BX_WWPNS + BX_MACS + BX_NP_GUIDS,

     BX_ALL_GUIDS  = (2 * BX_SLICE_GUIDS) + BX_SYS_GUIDS,
     BX_SLICES_NUM = 2,
};

enum {
      BI_IMACS    = 0,
      BI_EMACS    = BI_IMACS + BX_IMACS,
      BI_WWPNS    = BI_EMACS + BX_EMACS,
      BI_GUIDS    = BI_WWPNS + BX_WWPNS,
      BI_WWNNS    = BI_GUIDS  + BX_NP_GUIDS,
      BI_SYS_GUID = BX_ALL_GUIDS - 1,
};

typedef enum chip_type {
    CT_UNKNOWN = 0,
    CT_CONNECTX,
    CT_SWITCHX,
    CT_BRIDGEX,
    CT_IS4,
    CT_CONNECT_IB,
    CT_SWITCH_IB
}chip_type_t;

typedef struct guid {
    u_int32_t h;
    u_int32_t l;
} guid_t;
typedef guid_t hw_key_t;

typedef struct fs3_guid {
    guid_t uid;
    u_int8_t num_of_guids;
    u_int8_t step_size;
} fs3_guid_t;

typedef struct rom_info {
    u_int16_t exp_rom_product_id; // 0 - invalid.
    u_int16_t exp_rom_ver[3];
    u_int16_t exp_rom_dev_id;
    u_int8_t  exp_rom_port;
    u_int8_t  exp_rom_proto;
    u_int8_t  exp_rom_num_ver_fields;
    //char      expRomFreestr[FREE_STR_MAX_LEN];
} rom_info_t;


struct cib_uid_entry {
     u_int8_t num_allocated;
     u_int8_t step;
     u_int64_t uid;
};
typedef struct cibfw_uids {
    struct cib_uid_entry guids[2];
    struct cib_uid_entry macs[2];
} uids_t;


typedef struct fs3_info_ext {
    u_int8_t        guids_override_en;
    uids_t          fs3_uids_info;
    uids_t          orig_fs3_uids_info;
    char            image_vsd[VSD_LEN+1];
    char            orig_psid[PSID_LEN+1];

} fs3_info_t;


typedef struct fs2_info_ext {
    guid_t       guids[MAX_GUIDS];
    u_int32_t    guid_num;
    u_int32_t    config_sectors;
    u_int32_t    config_pad;
    u_int8_t     access_key_exists;
    guid_t       access_key_value;
    u_int8_t     blank_guids;
} fs2_info_t;

typedef struct roms_info {
    u_int8_t     exp_rom_found;
    u_int8_t     num_of_exp_rom;
    u_int8_t     no_rom_checksum;
    u_int16_t    exp_rom_com_devid;
    u_int8_t     exp_rom_warning;
    char         exp_rom_warning_msg[MAX_ROM_ERR_MSG_LEN];
    u_int8_t     exp_rom_err_msg_valid;
    char         exp_rom_err_msg[MAX_ROM_ERR_MSG_LEN];
    rom_info_t   rom_info[MAX_ROMS_NUM];
} roms_info_t;

typedef struct fw_info_com {
    char         psid[PSID_LEN + 1];
    u_int8_t     vsd_sect_found; // relevant to FS2 image only
    char         vsd[VSD_LEN + 1];
    char         product_ver[PRODUCT_VER_LEN + 1];
    u_int16_t    fw_ver[3];
    u_int16_t	 fw_rel_date[3];
    u_int16_t    min_fit_ver[4];
    u_int16_t    mic_ver[3];
    u_int32_t    image_size;
    u_int16_t    dev_type;
    u_int8_t     dev_rev;
    u_int16_t    vsd_vendor_id;
    u_int8_t     is_failsafe;
    chip_type_t  chip_type;
    roms_info_t  roms_info;
} fw_info_com_t;


typedef struct fw_info_ext {
    u_int8_t      fw_type;
    fw_info_com_t fw_info;
    fs2_info_t    fs2_info;
    fs3_info_t    fs3_info;
} fw_info_t;

typedef enum fw_hndl_type {
    FHT_MST_DEV,
    FHT_FW_FILE,
    FHT_UEFI_DEV,
    FHT_FW_BUFF,
} fw_hndl_type_t;


typedef enum fw_img_type {
    FIT_FS2,
    FIT_FS3,
} fw_img_type_t;


enum ExpRomProto {
    ER_IB  = 0,
    ER_ETH = 1,
    ER_VPI = 2
};


typedef struct _MLX4_DEV uefi_Dev_t;
typedef int (*f_fw_cmd) (uefi_Dev_t* dev, void* buffer, int* size);



#endif
