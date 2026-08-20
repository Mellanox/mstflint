
/*
* Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
*  Version: $Id$
*
*/
 

/***
         *** This file was generated at "2026-08-20 15:38:08"
         *** by:
         ***    > /usr/local/lib64/python3.9/site-packages/mft_adbtools/adabe_plugins/adb2c/adb2pack.py --input /home/jenkins/agent/workspace/automatic_prm_update/user/tools_layouts/adb/prm/hca/ext/reg_access_cables.adb --file-prefix cables --prefix reg_access_hca_ --no-adb-utils -o /home/jenkins/agent/workspace/automatic_prm_update/user/tools_layouts
         ***/
#ifndef CABLES_LAYOUTS_H
#define CABLES_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 148 */
struct reg_access_hca_mcia_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module Status0: SUCCESS1: NO_EEPROM_MODULE. No response from modules EEPROM.2: MODULE_NOT_SUPPORTED. Module type not supported by the device.
3: MODULE_NOT_CONNECTED. No module present indication.4: MODULE_TYPE_INVALID - module is not supported by INI.9: I2C_ERROR. Error occurred while trying to access the modules EEPROM
using I2C.16: MODULE_DISABLED - module is disabled */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t status;
	/* Description - [Switch][DWIP]:Module number, bits [11:8]. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t module_bits_11_8;
	/* Description - Slot index0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module number, bits [7:0].NIC: Range 0 .. MGPIR.num_of_modules -1 */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - [Switch][DWIP]:Module number, bits [14:12]. */
	/* 0x0.26 - 0x0.28 */
	/* access: INDEX */
	u_int8_t module_bits_14_12;
	/* Description - [DWIP]:Page Number Valid0: write page number1: dont write page numberValid only if module is in SW control */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t pnv;
	/* Description - Lock Page bit.When bit is set, FW can access the last accessed page.After boot and ISSU, default value is 0. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t l;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Device address */
	/* 0x4.0 - 0x4.15 */
	/* access: INDEX */
	u_int16_t device_address;
	/* Description - Page numberReserved when MCIA.l = 1 or when MCIA.pnv = 1 */
	/* 0x4.16 - 0x4.23 */
	/* access: INDEX */
	u_int8_t page_number;
	/* Description - I2C device address */
	/* 0x4.24 - 0x4.31 */
	/* access: INDEX */
	u_int8_t i2c_device_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes to read/write (up to 128 bytes) */
	/* 0x8.0 - 0x8.15 */
	/* access: INDEX */
	u_int16_t size;
	/* Description - Bank number */
	/* 0x8.16 - 0x8.23 */
	/* access: INDEX */
	u_int8_t bank_number;
	/* Description - [Switch][DWIP]:Module number, bit [15]. */
	/* 0x8.24 - 0x8.24 */
	/* access: INDEX */
	u_int8_t module_bit_15;
	/* Description - [DWIP][switch_internal]Background operation0: Foreground mode (legacy)1: Background modeWhen working on background mode, FW shall return STS_OK immediately and
return the transaction data via MCIA trap. */
	/* 0x8.27 - 0x8.27 */
	/* access: OP */
	u_int8_t bg_mode;
	/* Description - 0: password length is 4B (password_msb is reserved)1: password length is 8B (password_msb is used) */
	/* 0x8.28 - 0x8.28 */
	/* access: OP */
	u_int8_t passwd_length;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The password that is written to the module password field.This field is reserved when passwd_cap is not set to 1.Reserved when module is in SW control. */
	/* 0xc.0 - 0xc.31 */
	/* access: OP */
	u_int32_t password;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bytes to read/writeNote: some FW versions support only 12*4BSee MCAM bit34 */
	/* 0x10.0 - 0x8c.31 */
	/* access: RW */
	u_int32_t dword[32];
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - password msbSupported only when MCAM bit34 is setSupported only when passwd_cap is setReserved when passwd_length = 0 */
	/* 0x90.0 - 0x90.31 */
	/* access: RW */
	u_int32_t password_msb;
};

/* Description -   */
/* Size in bytes - 148 */
union reg_access_hca_cables_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	/* access: RW */
	struct reg_access_hca_mcia_ext mcia_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* mcia_ext */
void reg_access_hca_mcia_ext_pack(const struct reg_access_hca_mcia_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcia_ext_unpack(struct reg_access_hca_mcia_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcia_ext_print(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcia_ext_size(void);
#define REG_ACCESS_HCA_MCIA_EXT_SIZE    (0x94)
void reg_access_hca_mcia_ext_dump(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd);
/* cables_Nodes */
void reg_access_hca_cables_Nodes_pack(const union reg_access_hca_cables_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_cables_Nodes_unpack(union reg_access_hca_cables_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_cables_Nodes_print(const union reg_access_hca_cables_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_cables_Nodes_size(void);
#define REG_ACCESS_HCA_CABLES_NODES_SIZE    (0x94)
void reg_access_hca_cables_Nodes_dump(const union reg_access_hca_cables_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // CABLES_LAYOUTS_H
