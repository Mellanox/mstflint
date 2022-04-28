/*
 * Copyright (c) 2010-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 

/***
         *** This file was generated at "2022-02-06 17:27:46"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/image_layout/image_layout.adb --file-prefix image_layout --prefix image_layout_ --no-adb-utils
         ***/
#ifndef IMAGE_LAYOUT_LAYOUTS_H
#define IMAGE_LAYOUT_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 8 */
struct image_layout_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 8 */
struct image_layout_htoc_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t hash_offset;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t section_type;
};

/* Description -   */
/* Size in bytes - 16 */
struct image_layout_htoc_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	u_int8_t num_of_entries;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.8 - 0x4.15 */
	u_int8_t hash_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t hash_size;
};

/* Description -   */
/* Size in bytes - 4 */
struct image_layout_module_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t branch;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.8 - 0x0.19 */
	u_int16_t minor;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.20 - 0x0.31 */
	u_int16_t major;
};

/* Description -   */
/* Size in bytes - 4 */
struct image_layout_reset_capabilities {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Initial capability for reset level */
	/* 0x0.0 - 0x0.0 */
	u_int8_t reset_ver_en;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Version field used for the version vector. The firmware cannot peform Live-Patch from different version_vector_ver. Note: Different major values are not supported. */
	/* 0x0.8 - 0x0.15 */
	u_int8_t version_vector_ver;
};

/* Description -   */
/* Size in bytes - 4 */
struct image_layout_reset_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - major must be supported in order to support lfwp */
	/* 0x0.0 - 0x0.15 */
	u_int16_t major;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - branch must be supported in order to support lfwp */
	/* 0x0.16 - 0x0.19 */
	u_int8_t branch;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - determines which transfer function to run */
	/* 0x0.20 - 0x0.27 */
	u_int8_t minor;
};

/* Description -   */
/* Size in bytes - 16 */
struct image_layout_uid_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of allocated UIDs in this entry */
	/* 0x0.0 - 0x0.7 */
	u_int8_t num_allocated;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Step size by which to derive the UIDs for this entry
See struct description */
	/* 0x0.8 - 0x0.15 */
	u_int8_t step;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For MACs, the upper 16 bits in the 'hi' dword are reserved */
	/* 0x8.0 - 0xc.31 */
	u_int64_t uid;
};

/* Description -   */
/* Size in bytes - 16 */
struct image_layout_FW_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	u_int16_t SUBMINOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t MINOR;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	u_int8_t Hour;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	u_int8_t Minutes;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	u_int8_t Seconds;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	u_int8_t Day;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.8 - 0xc.15 */
	u_int8_t Month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	u_int16_t Year;
};

/* Description -   */
/* Size in bytes - 8 */
struct image_layout_TRIPPLE_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	u_int16_t SUBMINOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t MINOR;
};

/* Description -   */
/* Size in bytes - 64 */
struct image_layout_guids {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids, is used for system GUID, node GUID and port GUID of port 0. ;/Multiple UIDs can be assigned to a single port, to be used for multiple virtual guests, multi host and managment */
	/* 0x0.0 - 0xc.31 */
	struct image_layout_uid_entry guids;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	struct image_layout_uid_entry macs;
};

/* Description -   */
/* Size in bytes - 12 */
struct image_layout_hashes_table_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hard-coded to 0 */
	/* 0x0.0 - 0x0.31 */
	u_int32_t load_address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Num of payload DWs + 1 */
	/* 0x4.0 - 0x4.31 */
	u_int32_t dw_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Calculated over the first 2 DWs */
	/* 0x8.0 - 0x8.15 */
	u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 240 */
struct image_layout_htoc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct image_layout_htoc_header header;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0xec.31 */
	struct image_layout_htoc_entry entry[28];
};

/* Description -   */
/* Size in bytes - 64 */
struct image_layout_htoc_hash {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	u_int32_t hash_val[16];
};

/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct image_layout_hw_pointer_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - pointer */
	/* 0x0.0 - 0x0.31 */
	u_int32_t ptr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - crc16 as calculated by HW */
	/* 0x4.0 - 0x4.15 */
	u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 8 */
struct image_layout_image_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - log of next address in bytes to search for an image. Address in bytes is 2^log_step */
	/* 0x0.0 - 0x0.7 */
	u_int8_t log_step;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - this image can run from any partition starting at address 0x0000000, 0x4000000, 0x800000. The code supports only two partitions. */
	/* 0x0.31 - 0x0.31 */
	u_int8_t run_from_any;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Max possible size in bytes of image. Image read / write should not occure beyond this address */
	/* 0x4.0 - 0x4.31 */
	u_int32_t max_size;
};

/* Description -   */
/* Size in bytes - 64 */
struct image_layout_module_versions {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct image_layout_module_version core;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	struct image_layout_module_version phy;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	struct image_layout_module_version kernel;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	struct image_layout_module_version iron_image;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	struct image_layout_module_version host_management;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	struct image_layout_module_version mad;
};

/* Description -   */
/* Size in bytes - 16 */
struct image_layout_operation_key {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t key_modifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	u_int64_t key;
};

/* Description -   */
/* Size in bytes - 48 */
struct image_layout_version_vector {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	struct image_layout_reset_capabilities reset_capabilities;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - cores SP */
	/* 0x4.0 - 0x4.31 */
	struct image_layout_reset_version scratchpad;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	struct image_layout_reset_version icm_context;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - PCI domain */
	/* 0xc.0 - 0xc.31 */
	struct image_layout_reset_version pci;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - PHY domain */
	/* 0x10.0 - 0x10.31 */
	struct image_layout_reset_version phy;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	struct image_layout_reset_version ini;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	struct image_layout_reset_version reserved1;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	struct image_layout_reset_version reserved2;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	struct image_layout_reset_version reserved3;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	struct image_layout_reset_version reserved4;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	struct image_layout_reset_version reserved5;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	struct image_layout_reset_version reserved6;
};

/* Description -   */
/* Size in bytes - 512 */
struct image_layout_device_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 0x10.0 - 0x10.7 */
	u_int8_t minor_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 0x10.8 - 0x10.16 */
	u_int16_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct image_layout_guids guids;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 0x6c.0 - 0x6c.15 */
	u_int16_t vsd_vendor_id;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.24 - 0x140.23 */
	char vsd[209];
/*---------------- DWORD[88] (Offset 0x160) ----------------*/
	/* Description -  */
	/* 0x160.0 - 0x19c.31 */
	struct image_layout_operation_key keys[4];
/*---------------- DWORD[127] (Offset 0x1fc) ----------------*/
	/* Description -  */
	/* 0x1fc.0 - 0x1fc.15 */
	u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 2052 */
struct image_layout_hashes_table {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct image_layout_hashes_table_header header;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xf8.31 */
	struct image_layout_htoc htoc;
/*---------------- DWORD[63] (Offset 0xfc) ----------------*/
	/* Description -  */
	/* 0xfc.0 - 0x7f8.31 */
	struct image_layout_htoc_hash hash[28];
/*---------------- DWORD[512] (Offset 0x800) ----------------*/
	/* Description -  */
	/* 0x800.0 - 0x800.15 */
	u_int16_t crc;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct image_layout_hw_pointers_carmel {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct image_layout_hw_pointer_entry boot_record_ptr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	struct image_layout_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	struct image_layout_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	struct image_layout_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	struct image_layout_hw_pointer_entry authentication_start_pointer;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	struct image_layout_hw_pointer_entry authentication_end_pointer;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	struct image_layout_hw_pointer_entry digest_pointer;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	struct image_layout_hw_pointer_entry digest_recovery_key_pointer;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	struct image_layout_hw_pointer_entry fw_window_start_pointer;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	struct image_layout_hw_pointer_entry fw_window_end_pointer;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	struct image_layout_hw_pointer_entry image_info_section_pointer;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	struct image_layout_hw_pointer_entry hmac_end_pointer;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	struct image_layout_hw_pointer_entry public_key_pointer;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	struct image_layout_hw_pointer_entry fw_security_version_pointer;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	struct image_layout_hw_pointer_entry gcm_iv_delta_pointer;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	struct image_layout_hw_pointer_entry hashes_table_pointer;
};

/* Description -   */
/* Size in bytes - 1024 */
struct image_layout_image_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicate that this binary intended for secure boot enabled devices */
	/* 0x0.2 - 0x0.2 */
	u_int8_t secure_boot;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0x0 - not encrypted; 0x1 - encryption before signature; 0x2 - encryption after signature.  */
	/* 0x0.3 - 0x0.4 */
	u_int8_t encrypted_fw;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicate that this binary support windbond flash */
	/* 0x0.5 - 0x0.5 */
	u_int8_t windbond_flash_support;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicate that this binary support long keys (up to 4096bits) */
	/* 0x0.6 - 0x0.6 */
	u_int8_t long_keys;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - when set, debug-fw tokens are enabled. */
	/* 0x0.7 - 0x0.7 */
	u_int8_t debug_fw_tokens_supported;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The image can be updated using the MCC/MCDA commands */
	/* 0x0.8 - 0x0.8 */
	u_int8_t mcc_en;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - OEM lifecycle NVCONFIG files are signed */
	/* 0x0.9 - 0x0.9 */
	u_int8_t signed_vendor_nvconfig_files;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Mellanox lifecycle NVCONFIG files are signed */
	/* 0x0.10 - 0x0.10 */
	u_int8_t signed_mlnx_nvconfig_files;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Factory re-customizationflow is supported */
	/* 0x0.11 - 0x0.11 */
	u_int8_t frc_supported;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Customer Support Tokens are supported */
	/* 0x0.12 - 0x0.12 */
	u_int8_t cs_tokens_supported;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - This is a debug firmware */
	/* 0x0.13 - 0x0.13 */
	u_int8_t debug_fw;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [MCC/MCDA flow] if set, the SHA 256 digest is encrypted - enabled by default for secure_fw - cr-space not closed */
	/* 0x0.14 - 0x0.14 */
	u_int8_t signed_fw;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [MCC/MCDA flow] cr-space closed */
	/* 0x0.15 - 0x0.15 */
	u_int8_t secure_fw;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IMAGE_INFO section minor version */
	/* 0x0.16 - 0x0.23 */
	u_int8_t minor_version;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IMAGE_INFO section major version */
	/* 0x0.24 - 0x0.31 */
	u_int8_t major_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x10.31 */
	struct image_layout_FW_VERSION FW_VERSION;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	struct image_layout_TRIPPLE_VERSION mic_version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - PCI device ID of the device */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t pci_vendor_id;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - PCI device ID of the device */
	/* 0x1c.16 - 0x1c.31 */
	u_int16_t pci_device_id;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - PCI device ID of the device */
	/* 0x20.0 - 0x20.15 */
	u_int16_t pci_sub_vendor_id;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - PCI device ID of the device */
	/* 0x20.16 - 0x20.31 */
	u_int16_t pci_subsystem_id;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.24 - 0x34.23 */
	char psid[17];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.15 */
	u_int16_t vsd_vendor_id;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.24 - 0x108.23 */
	char vsd[209];
/*---------------- DWORD[66] (Offset 0x108) ----------------*/
	/* Description - image size parameters */
	/* 0x108.0 - 0x10c.31 */
	struct image_layout_image_size image_size;
/*---------------- DWORD[68] (Offset 0x110) ----------------*/
	/* Description - The needed 10’s of ms timeout between the PCI link disable and PCI link enable. */
	/* 0x110.0 - 0x110.7 */
	u_int8_t synced_reset_downtime;
/*---------------- DWORD[70] (Offset 0x118) ----------------*/
	/* Description - HW device(s) supported by this FW image.
0 means invalid entry.
For Golan A0, first entry should be 0x1ff
 */
	/* 0x118.0 - 0x124.31 */
	u_int32_t supported_hw_id[4];
/*---------------- DWORD[74] (Offset 0x128) ----------------*/
	/* Description -  */
	/* 0x128.0 - 0x128.31 */
	u_int32_t ini_file_num;
/*---------------- DWORD[75] (Offset 0x12c) ----------------*/
	/* Description -  */
	/* 0x12c.0 - 0x12c.31 */
	u_int32_t burn_image_size;
/*---------------- DWORD[100] (Offset 0x190) ----------------*/
	/* Description -  */
	/* 0x190.0 - 0x1bc.31 */
	struct image_layout_version_vector version_vector;
/*---------------- DWORD[112] (Offset 0x1c0) ----------------*/
	/* Description - Product Version is the unified version of the FW and expansion ROM.
Format is defined by the packager.
When set to a non-empty string the FW update tool burns the image as a monolythic entity and refuses to update rom only or FW only. */
	/* 0x1c0.24 - 0x1d0.23 */
	char prod_ver[17];
/*---------------- DWORD[116] (Offset 0x1d0) ----------------*/
	/* Description - Product description */
	/* 0x1d0.24 - 0x2d0.23 */
	char description[257];
/*---------------- DWORD[192] (Offset 0x300) ----------------*/
	/* Description -  */
	/* 0x300.0 - 0x33c.31 */
	struct image_layout_module_versions module_versions;
/*---------------- DWORD[208] (Offset 0x340) ----------------*/
	/* Description - Product name */
	/* 0x340.24 - 0x380.23 */
	char name[65];
/*---------------- DWORD[224] (Offset 0x380) ----------------*/
	/* Description - PRS used to generate the FW binary */
	/* 0x380.24 - 0x400.23 */
	char prs_name[129];
};

/* Description -   */
/* Size in bytes - 32 */
struct image_layout_itoc_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.2 - 0x0.23 */
	u_int32_t size;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Section ID Section Type DESCRIPTION
0x1 BOOT_CODE FW loader code
0x2 PCI_CODE Code that is required to raise PCIe link.
0x3 MAIN_CODE All non-PCIe FW code
0x8 HW_BOOT_CFG Initial values for the PCI related registers
0x9 HW_MAIN_CFG Initial values for all other registers 
0x10 IMAGE_INFO Management data for the burning tool. See 'Image Info Section' chapter in the Mellanox Flash Programming Application Note
0x11 FW_BOOT_CFG Initial values for user set-able hi level non-hardware related settings, such as number of physical functions
(optional)
0x12 FW_MAIN_CFG Initial values for user set-able hi level non-hardware related settings.
(optional)
0x18 ROM_CODE PXE/Boot over IB code. 
0x30 DBG_LOG_MAP FW logger 'index to string' map. The map is in ASCI text. Format is TBD.
                                          PARAM0 in the iTOC specifies the compression method of this sector:
                                          0. Uncompressed
                                          1. Zlib compress2()
                                          2. LZMA
                                          Others - Reserved 
0x31 DBG_FW_INI The Ini file used in the image generation. The PARAM0 applies the same as in  DBG_LOG_MAP section type.
0x32 DBG_FW_PARAMS FW settable parameters. ASCII text. Format is TBD. The PARAM0 applies the same as in  DBG_LOG_MAP section type.
0xff END_MARKER A type of 0xff marks the end of the iTOC entries array. It is recommended to leave the unused part of the iTOC section blank (that is, 0xff in all unused bytes)
All other values Reserved 
 */
	/* 0x0.24 - 0x0.31 */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - if partition type is code or ini then the load address is in here */
	/* 0x4.0 - 0x4.29 */
	u_int32_t param0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - When this bit is set, Data within the section is protected by per-line crc. See yu.flash.replacement.crc_en */
	/* 0x4.30 - 0x4.30 */
	u_int8_t cache_line_crc;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - When this bit is set, image is zipped */
	/* 0x4.31 - 0x4.31 */
	u_int8_t zipped_image;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - if partition type is code then the jump address is in here */
	/* 0x8.0 - 0x8.31 */
	u_int32_t param1;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	u_int16_t version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.2 - 0x14.30 */
	u_int32_t flash_addr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	u_int16_t section_crc;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.16 - 0x18.18 */
	u_int8_t crc;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - indicates whether the section referenced by the ITOC is encrypted */
	/* 0x18.31 - 0x18.31 */
	u_int8_t encrypted_section;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 32 */
struct image_layout_itoc_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - for itoc 49 54 4f 43 
for dtoc 44 54 4f 43 */
	/* 0x0.0 - 0x0.31 */
	u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 04 08 15 16 */
	/* 0x4.0 - 0x4.31 */
	u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 23 42 ca fa */
	/* 0x8.0 - 0x8.31 */
	u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ba ca fe 00 */
	/* 0xc.0 - 0xc.31 */
	u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Current version: 1 */
	/* 0x10.0 - 0x10.7 */
	u_int8_t version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - itoc_header: Represents the minimal layout version expected on the flash: 1.
dtoc_header: Represents the layout version depicted by the dTOC: 1. */
	/* 0x10.24 - 0x10.31 */
	u_int8_t flash_layout_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - indicates the number of ITOC entries in the image */
	/* 0x14.0 - 0x14.7 */
	u_int8_t num_of_entries;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t itoc_entry_crc;
};

/* Description -  tools speific section */
/* Size in bytes - 64 */
struct image_layout_tools_area {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - tools area minor version */
	/* 0x0.0 - 0x0.7 */
	u_int8_t minor;
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - tools area major version */
	/* 0x0.8 - 0x0.15 */
	u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - binary version minor set by image generation tool */
	/* 0x4.0 - 0x4.7 */
	u_int8_t bin_ver_minor;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - binary version major set by image generation tool */
	/* 0x4.8 - 0x4.15 */
	u_int8_t bin_ver_major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - log2 image slot size */
	/* 0x4.16 - 0x4.31 */
	u_int16_t log2_img_slot_size;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x3c.15 */
	u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 2052 */
union image_layout_image_layout_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct image_layout_tools_area tools_area;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct image_layout_itoc_entry itoc_entry;
	/* Description -  */
	/* 0x0.0 - 0x800.31 */
	struct image_layout_hashes_table hashes_table;
	/* Description -  */
	/* 0x0.0 - 0x3fc.31 */
	struct image_layout_image_info image_info;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	struct image_layout_hw_pointers_carmel hw_pointers_carmel;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct image_layout_itoc_header itoc_header;
	/* Description -  */
	/* 0x0.0 - 0x1fc.31 */
	struct image_layout_device_info device_info;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* uint64 */
void image_layout_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void image_layout_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_uint64_size(void);
#define IMAGE_LAYOUT_UINT64_SIZE    (0x8)
void image_layout_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* htoc_entry */
void image_layout_htoc_entry_pack(const struct image_layout_htoc_entry *ptr_struct, u_int8_t *ptr_buff);
void image_layout_htoc_entry_unpack(struct image_layout_htoc_entry *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_htoc_entry_print(const struct image_layout_htoc_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_htoc_entry_size(void);
#define IMAGE_LAYOUT_HTOC_ENTRY_SIZE    (0x8)
void image_layout_htoc_entry_dump(const struct image_layout_htoc_entry *ptr_struct, FILE *fd);
/* htoc_header */
void image_layout_htoc_header_pack(const struct image_layout_htoc_header *ptr_struct, u_int8_t *ptr_buff);
void image_layout_htoc_header_unpack(struct image_layout_htoc_header *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_htoc_header_print(const struct image_layout_htoc_header *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_htoc_header_size(void);
#define IMAGE_LAYOUT_HTOC_HEADER_SIZE    (0x10)
void image_layout_htoc_header_dump(const struct image_layout_htoc_header *ptr_struct, FILE *fd);
/* module_version */
void image_layout_module_version_pack(const struct image_layout_module_version *ptr_struct, u_int8_t *ptr_buff);
void image_layout_module_version_unpack(struct image_layout_module_version *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_module_version_print(const struct image_layout_module_version *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_module_version_size(void);
#define IMAGE_LAYOUT_MODULE_VERSION_SIZE    (0x4)
void image_layout_module_version_dump(const struct image_layout_module_version *ptr_struct, FILE *fd);
/* reset_capabilities */
void image_layout_reset_capabilities_pack(const struct image_layout_reset_capabilities *ptr_struct, u_int8_t *ptr_buff);
void image_layout_reset_capabilities_unpack(struct image_layout_reset_capabilities *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_reset_capabilities_print(const struct image_layout_reset_capabilities *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_reset_capabilities_size(void);
#define IMAGE_LAYOUT_RESET_CAPABILITIES_SIZE    (0x4)
void image_layout_reset_capabilities_dump(const struct image_layout_reset_capabilities *ptr_struct, FILE *fd);
/* reset_version */
void image_layout_reset_version_pack(const struct image_layout_reset_version *ptr_struct, u_int8_t *ptr_buff);
void image_layout_reset_version_unpack(struct image_layout_reset_version *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_reset_version_print(const struct image_layout_reset_version *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_reset_version_size(void);
#define IMAGE_LAYOUT_RESET_VERSION_SIZE    (0x4)
void image_layout_reset_version_dump(const struct image_layout_reset_version *ptr_struct, FILE *fd);
/* uid_entry */
void image_layout_uid_entry_pack(const struct image_layout_uid_entry *ptr_struct, u_int8_t *ptr_buff);
void image_layout_uid_entry_unpack(struct image_layout_uid_entry *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_uid_entry_print(const struct image_layout_uid_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_uid_entry_size(void);
#define IMAGE_LAYOUT_UID_ENTRY_SIZE    (0x10)
void image_layout_uid_entry_dump(const struct image_layout_uid_entry *ptr_struct, FILE *fd);
/* FW_VERSION */
void image_layout_FW_VERSION_pack(const struct image_layout_FW_VERSION *ptr_struct, u_int8_t *ptr_buff);
void image_layout_FW_VERSION_unpack(struct image_layout_FW_VERSION *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_FW_VERSION_print(const struct image_layout_FW_VERSION *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_FW_VERSION_size(void);
#define IMAGE_LAYOUT_FW_VERSION_SIZE    (0x10)
void image_layout_FW_VERSION_dump(const struct image_layout_FW_VERSION *ptr_struct, FILE *fd);
/* TRIPPLE_VERSION */
void image_layout_TRIPPLE_VERSION_pack(const struct image_layout_TRIPPLE_VERSION *ptr_struct, u_int8_t *ptr_buff);
void image_layout_TRIPPLE_VERSION_unpack(struct image_layout_TRIPPLE_VERSION *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_TRIPPLE_VERSION_print(const struct image_layout_TRIPPLE_VERSION *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_TRIPPLE_VERSION_size(void);
#define IMAGE_LAYOUT_TRIPPLE_VERSION_SIZE    (0x8)
void image_layout_TRIPPLE_VERSION_dump(const struct image_layout_TRIPPLE_VERSION *ptr_struct, FILE *fd);
/* guids */
void image_layout_guids_pack(const struct image_layout_guids *ptr_struct, u_int8_t *ptr_buff);
void image_layout_guids_unpack(struct image_layout_guids *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_guids_print(const struct image_layout_guids *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_guids_size(void);
#define IMAGE_LAYOUT_GUIDS_SIZE    (0x40)
void image_layout_guids_dump(const struct image_layout_guids *ptr_struct, FILE *fd);
/* hashes_table_header */
void image_layout_hashes_table_header_pack(const struct image_layout_hashes_table_header *ptr_struct, u_int8_t *ptr_buff);
void image_layout_hashes_table_header_unpack(struct image_layout_hashes_table_header *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_hashes_table_header_print(const struct image_layout_hashes_table_header *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_hashes_table_header_size(void);
#define IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE    (0xc)
void image_layout_hashes_table_header_dump(const struct image_layout_hashes_table_header *ptr_struct, FILE *fd);
/* htoc */
void image_layout_htoc_pack(const struct image_layout_htoc *ptr_struct, u_int8_t *ptr_buff);
void image_layout_htoc_unpack(struct image_layout_htoc *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_htoc_print(const struct image_layout_htoc *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_htoc_size(void);
#define IMAGE_LAYOUT_HTOC_SIZE    (0xf0)
void image_layout_htoc_dump(const struct image_layout_htoc *ptr_struct, FILE *fd);
/* htoc_hash */
void image_layout_htoc_hash_pack(const struct image_layout_htoc_hash *ptr_struct, u_int8_t *ptr_buff);
void image_layout_htoc_hash_unpack(struct image_layout_htoc_hash *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_htoc_hash_print(const struct image_layout_htoc_hash *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_htoc_hash_size(void);
#define IMAGE_LAYOUT_HTOC_HASH_SIZE    (0x40)
void image_layout_htoc_hash_dump(const struct image_layout_htoc_hash *ptr_struct, FILE *fd);
/* hw_pointer_entry */
void image_layout_hw_pointer_entry_pack(const struct image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff);
void image_layout_hw_pointer_entry_unpack(struct image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_hw_pointer_entry_print(const struct image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_hw_pointer_entry_size(void);
#define IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE    (0x8)
void image_layout_hw_pointer_entry_dump(const struct image_layout_hw_pointer_entry *ptr_struct, FILE *fd);
/* image_size */
void image_layout_image_size_pack(const struct image_layout_image_size *ptr_struct, u_int8_t *ptr_buff);
void image_layout_image_size_unpack(struct image_layout_image_size *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_image_size_print(const struct image_layout_image_size *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_image_size_size(void);
#define IMAGE_LAYOUT_IMAGE_SIZE_SIZE    (0x8)
void image_layout_image_size_dump(const struct image_layout_image_size *ptr_struct, FILE *fd);
/* module_versions */
void image_layout_module_versions_pack(const struct image_layout_module_versions *ptr_struct, u_int8_t *ptr_buff);
void image_layout_module_versions_unpack(struct image_layout_module_versions *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_module_versions_print(const struct image_layout_module_versions *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_module_versions_size(void);
#define IMAGE_LAYOUT_MODULE_VERSIONS_SIZE    (0x40)
void image_layout_module_versions_dump(const struct image_layout_module_versions *ptr_struct, FILE *fd);
/* operation_key */
void image_layout_operation_key_pack(const struct image_layout_operation_key *ptr_struct, u_int8_t *ptr_buff);
void image_layout_operation_key_unpack(struct image_layout_operation_key *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_operation_key_print(const struct image_layout_operation_key *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_operation_key_size(void);
#define IMAGE_LAYOUT_OPERATION_KEY_SIZE    (0x10)
void image_layout_operation_key_dump(const struct image_layout_operation_key *ptr_struct, FILE *fd);
/* version_vector */
void image_layout_version_vector_pack(const struct image_layout_version_vector *ptr_struct, u_int8_t *ptr_buff);
void image_layout_version_vector_unpack(struct image_layout_version_vector *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_version_vector_print(const struct image_layout_version_vector *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_version_vector_size(void);
#define IMAGE_LAYOUT_VERSION_VECTOR_SIZE    (0x30)
void image_layout_version_vector_dump(const struct image_layout_version_vector *ptr_struct, FILE *fd);
/* device_info */
void image_layout_device_info_pack(const struct image_layout_device_info *ptr_struct, u_int8_t *ptr_buff);
void image_layout_device_info_unpack(struct image_layout_device_info *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_device_info_print(const struct image_layout_device_info *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_device_info_size(void);
#define IMAGE_LAYOUT_DEVICE_INFO_SIZE    (0x200)
void image_layout_device_info_dump(const struct image_layout_device_info *ptr_struct, FILE *fd);
/* hashes_table */
void image_layout_hashes_table_pack(const struct image_layout_hashes_table *ptr_struct, u_int8_t *ptr_buff);
void image_layout_hashes_table_unpack(struct image_layout_hashes_table *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_hashes_table_print(const struct image_layout_hashes_table *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_hashes_table_size(void);
#define IMAGE_LAYOUT_HASHES_TABLE_SIZE    (0x804)
void image_layout_hashes_table_dump(const struct image_layout_hashes_table *ptr_struct, FILE *fd);
/* hw_pointers_carmel */
void image_layout_hw_pointers_carmel_pack(const struct image_layout_hw_pointers_carmel *ptr_struct, u_int8_t *ptr_buff);
void image_layout_hw_pointers_carmel_unpack(struct image_layout_hw_pointers_carmel *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_hw_pointers_carmel_print(const struct image_layout_hw_pointers_carmel *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_hw_pointers_carmel_size(void);
#define IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE    (0x80)
void image_layout_hw_pointers_carmel_dump(const struct image_layout_hw_pointers_carmel *ptr_struct, FILE *fd);
/* image_info */
void image_layout_image_info_pack(const struct image_layout_image_info *ptr_struct, u_int8_t *ptr_buff);
void image_layout_image_info_unpack(struct image_layout_image_info *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_image_info_print(const struct image_layout_image_info *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_image_info_size(void);
#define IMAGE_LAYOUT_IMAGE_INFO_SIZE    (0x400)
void image_layout_image_info_dump(const struct image_layout_image_info *ptr_struct, FILE *fd);
/* itoc_entry */
void image_layout_itoc_entry_pack(const struct image_layout_itoc_entry *ptr_struct, u_int8_t *ptr_buff);
void image_layout_itoc_entry_unpack(struct image_layout_itoc_entry *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_itoc_entry_print(const struct image_layout_itoc_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_itoc_entry_size(void);
#define IMAGE_LAYOUT_ITOC_ENTRY_SIZE    (0x20)
void image_layout_itoc_entry_dump(const struct image_layout_itoc_entry *ptr_struct, FILE *fd);
/* itoc_header */
void image_layout_itoc_header_pack(const struct image_layout_itoc_header *ptr_struct, u_int8_t *ptr_buff);
void image_layout_itoc_header_unpack(struct image_layout_itoc_header *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_itoc_header_print(const struct image_layout_itoc_header *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_itoc_header_size(void);
#define IMAGE_LAYOUT_ITOC_HEADER_SIZE    (0x20)
void image_layout_itoc_header_dump(const struct image_layout_itoc_header *ptr_struct, FILE *fd);
/* tools_area */
void image_layout_tools_area_pack(const struct image_layout_tools_area *ptr_struct, u_int8_t *ptr_buff);
void image_layout_tools_area_unpack(struct image_layout_tools_area *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_tools_area_print(const struct image_layout_tools_area *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_tools_area_size(void);
#define IMAGE_LAYOUT_TOOLS_AREA_SIZE    (0x40)
void image_layout_tools_area_dump(const struct image_layout_tools_area *ptr_struct, FILE *fd);
/* image_layout_Nodes */
void image_layout_image_layout_Nodes_pack(const union image_layout_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff);
void image_layout_image_layout_Nodes_unpack(union image_layout_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void image_layout_image_layout_Nodes_print(const union image_layout_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int image_layout_image_layout_Nodes_size(void);
#define IMAGE_LAYOUT_IMAGE_LAYOUT_NODES_SIZE    (0x804)
void image_layout_image_layout_Nodes_dump(const union image_layout_image_layout_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // IMAGE_LAYOUT_LAYOUTS_H
