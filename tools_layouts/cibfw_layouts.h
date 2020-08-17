
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

/***
         *** This file was generated at "2019-08-11 16:47:37"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/cibfw/cibfw.adb --file-prefix cibfw --prefix cibfw_
         ***/
#ifndef CIBFW_LAYOUTS_H
#define CIBFW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 8 */
struct cibfw_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 8 */
struct cibfw_reset_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Match means upgrade supported, mismatch implies reset not supported */
	/* 0x0.0 - 0x0.31 */
	u_int32_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - If Major matches. Match means seamless reset. Greater means reset supported. Less then upgrade not supported */
	/* 0x4.0 - 0x4.7 */
	u_int8_t minor;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_uid_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of allocated UIDs in this entry */
	/* 0x0.0 - 0x0.7 */
	u_int8_t num_allocated;
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
struct cibfw_FW_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	u_int16_t SUBMINOR;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t MINOR;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.8 - 0x8.15 */
	u_int8_t Hour;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	u_int8_t Minutes;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	u_int8_t Seconds;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.7 */
	u_int8_t Day;
	/* Description -  */
	/* 0xc.8 - 0xc.15 */
	u_int8_t Month;
	/* Description -  */
	/* 0xc.16 - 0xc.31 */
	u_int16_t Year;
};

/* Description -   */
/* Size in bytes - 8 */
struct cibfw_TRIPPLE_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.15 */
	u_int16_t SUBMINOR;
	/* Description -  */
	/* 0x4.16 - 0x4.31 */
	u_int16_t MINOR;
};

/* Description -   */
/* Size in bytes - 64 */
struct cibfw_guids {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids[0], is used for system GUID, node GUID and port GUID of port 0. guids[1], is used for port GUID of port 1.;/Multiple UIDs can be assigned to a single port, to be used for multiple virtual guests.

Allocation Example:
For a port GUID, if the
    UID = 0x2c9030001000
    num_allocated  = 4, 
    step = 8

Then the GUIDs for this port would be:
    0x2c9030001000
    0x2c9030001008
    0x2c9030001010
    0x2c9030001018 */
	/* 0x0.0 - 0x1c.31 */
	struct cibfw_uid_entry guids[2];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x3c.31 */
	struct cibfw_uid_entry macs[2];
};

/* Description -   */
/* Size in bytes - 8 */
struct cibfw_image_size {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - log of next address in bytes to search for an image. Address in bytes is 2^log_step */
	/* 0x0.0 - 0x0.7 */
	u_int8_t log_step;
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
struct cibfw_lfwp_version_vector {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	struct cibfw_reset_version scratchpad;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	struct cibfw_reset_version icm_context;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	struct cibfw_reset_version pci_code;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	struct cibfw_reset_version phy_code;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	struct cibfw_reset_version ini;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	struct cibfw_reset_version reserved1;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	struct cibfw_reset_version reserved2;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	struct cibfw_reset_version reserved3;
};

/* Description -   */
/* Size in bytes - 4 */
struct cibfw_module_version {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t branch;
	/* Description -  */
	/* 0x0.8 - 0x0.19 */
	u_int16_t minor;
	/* Description -  */
	/* 0x0.20 - 0x0.31 */
	u_int16_t major;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_operation_key {
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
/* Size in bytes - 512 */
struct cibfw_device_info {
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
	/* Description - Format version for this struct */
	/* 0x10.8 - 0x10.16 */
	u_int16_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct cibfw_guids guids;
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
	struct cibfw_operation_key keys[4];
};

/* Description -   */
/* Size in bytes - 1024 */
struct cibfw_image_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicate that this binary support long keys (up to 4096bits) */
	/* 0x0.6 - 0x0.6 */
	u_int8_t long_keys;
	/* Description - when set, debug-fw tokens are enabled. */
	/* 0x0.7 - 0x0.7 */
	u_int8_t debug_fw_tokens_supported;
	/* Description - The image can be updated using the MCC/MCDA commands */
	/* 0x0.8 - 0x0.8 */
	u_int8_t mcc_en;
	/* Description - OEM lifecycle NVCONFIG files are signed */
	/* 0x0.9 - 0x0.9 */
	u_int8_t signed_vendor_nvconfig_files;
	/* Description - Mellanox lifecycle NVCONFIG files are signed */
	/* 0x0.10 - 0x0.10 */
	u_int8_t signed_mlnx_nvconfig_files;
	/* Description - Factory re-customizationflow is supported */
	/* 0x0.11 - 0x0.11 */
	u_int8_t frc_supported;
	/* Description - Customer Support Tokens are supported */
	/* 0x0.12 - 0x0.12 */
	u_int8_t cs_tokens_supported;
	/* Description - This is a debug firmware */
	/* 0x0.13 - 0x0.13 */
	u_int8_t debug_fw;
	/* Description - [MCC/MCDA flow] if set, the SHA 256 digest is encrypted - enabled by default for secure_fw - cr-space not closed */
	/* 0x0.14 - 0x0.14 */
	u_int8_t signed_fw;
	/* Description - [MCC/MCDA flow] cr-space closed */
	/* 0x0.15 - 0x0.15 */
	u_int8_t secure_fw;
	/* Description - IMAGE_INFO section minor version */
	/* 0x0.16 - 0x0.23 */
	u_int8_t minor_version;
	/* Description - IMAGE_INFO section major version */
	/* 0x0.24 - 0x0.31 */
	u_int8_t major_version;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x10.31 */
	struct cibfw_FW_VERSION FW_VERSION;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x18.31 */
	struct cibfw_TRIPPLE_VERSION mic_version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t pci_vendor_id;
	/* Description -  */
	/* 0x1c.16 - 0x1c.31 */
	u_int16_t pci_device_id;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.15 */
	u_int16_t pci_sub_vendor_id;
	/* Description -  */
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
	struct cibfw_image_size image_size;
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
/*---------------- DWORD[76] (Offset 0x130) ----------------*/
	/* Description -  */
	/* 0x130.0 - 0x16c.31 */
	struct cibfw_lfwp_version_vector lfwp_version_vector;
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
/*---------------- DWORD[197] (Offset 0x314) ----------------*/
	/* Description -  */
	/* 0x314.0 - 0x314.31 */
	struct cibfw_module_version isfu;
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
struct cibfw_itoc_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.2 - 0x0.23 */
	u_int32_t size;
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
	/* Description - When this bit is set, Data within the section is protected by per-line crc. See yu.flash.replacement.crc_en */
	/* 0x4.30 - 0x4.30 */
	u_int8_t cache_line_crc;
	/* Description - When this bit is set, image is zipped */
	/* 0x4.31 - 0x4.31 */
	u_int8_t zipped_image;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - if partition type is code then the jump address is in here */
	/* 0x8.0 - 0x8.31 */
	u_int32_t param1;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.2 - 0x14.30 */
	u_int32_t flash_addr;
	/* Description -  */
	/* 0x14.31 - 0x14.31 */
	u_int8_t relative_addr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	u_int16_t section_crc;
	/* Description -  */
	/* 0x18.16 - 0x18.16 */
	u_int8_t no_crc;
	/* Description - When this bit is set, the section pointed by this entry in belongs to teh device tather than to teh FW image.
A device_data section should not be updated in a regular FW update.
Example for device_data section: VPD_R, GUIDs. */
	/* 0x18.17 - 0x18.17 */
	u_int8_t device_data;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 32 */
struct cibfw_itoc_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 49 54 4f 43 */
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
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 320 */
struct cibfw_mfg_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	char psid[17];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - When this bit is set, the GUIDs should be taken from the device_info node.
When this bit is cleared, the GUIDs should be taken from the mfg_info node. */
	/* 0x1c.0 - 0x1c.0 */
	u_int8_t guids_override_en;
	/* Description - MFG_INFO section minor version */
	/* 0x1c.16 - 0x1c.23 */
	u_int8_t minor_version;
	/* Description - MFG_INFO section major version */
	/* 0x1c.24 - 0x1c.31 */
	u_int8_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct cibfw_guids guids;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_register_mfai {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	u_int32_t address;
	/* Description - if set make image permamnent */
	/* 0x0.29 - 0x0.29 */
	u_int8_t permanent;
	/* Description - if set use address */
	/* 0x0.30 - 0x0.30 */
	u_int8_t use_address;
	/* Description - if set use image id and not address */
	/* 0x0.31 - 0x0.31 */
	u_int8_t use_image_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.7 */
	u_int8_t image_id;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_register_mfrl {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - on Read, required reset level. On write, minimum requested reset level
 0-Full ISFU
 1-Driver down but link is up
 2-driver and link down
 3-driver down, link down pci disable/enable
 7-server warm reboot
 8-server cold reboot */
	/* 0x4.0 - 0x4.7 */
	u_int8_t reset_level;
};

/* Description -   */
/* Size in bytes - 1024 */
union cibfw_cibfw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct cibfw_register_mfai register_mfai;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct cibfw_itoc_entry itoc_entry;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	struct cibfw_guids guids;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct cibfw_itoc_header itoc_header;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	struct cibfw_register_mfrl register_mfrl;
	/* Description -  */
	/* 0x0.0 - 0x1fc.31 */
	struct cibfw_device_info device_info;
	/* Description -  */
	/* 0x0.0 - 0x13c.31 */
	struct cibfw_mfg_info mfg_info;
	/* Description -  */
	/* 0x0.0 - 0x3fc.31 */
	struct cibfw_image_info image_info;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* uint64 */
void cibfw_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void cibfw_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_uint64_size(void);
#define CIBFW_UINT64_SIZE    (0x8)
void cibfw_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* reset_version */
void cibfw_reset_version_pack(const struct cibfw_reset_version *ptr_struct, u_int8_t *ptr_buff);
void cibfw_reset_version_unpack(struct cibfw_reset_version *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_reset_version_print(const struct cibfw_reset_version *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_reset_version_size(void);
#define CIBFW_RESET_VERSION_SIZE    (0x8)
void cibfw_reset_version_dump(const struct cibfw_reset_version *ptr_struct, FILE *fd);
/* uid_entry */
void cibfw_uid_entry_pack(const struct cibfw_uid_entry *ptr_struct, u_int8_t *ptr_buff);
void cibfw_uid_entry_unpack(struct cibfw_uid_entry *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_uid_entry_print(const struct cibfw_uid_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_uid_entry_size(void);
#define CIBFW_UID_ENTRY_SIZE    (0x10)
void cibfw_uid_entry_dump(const struct cibfw_uid_entry *ptr_struct, FILE *fd);
/* FW_VERSION */
void cibfw_FW_VERSION_pack(const struct cibfw_FW_VERSION *ptr_struct, u_int8_t *ptr_buff);
void cibfw_FW_VERSION_unpack(struct cibfw_FW_VERSION *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_FW_VERSION_print(const struct cibfw_FW_VERSION *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_FW_VERSION_size(void);
#define CIBFW_FW_VERSION_SIZE    (0x10)
void cibfw_FW_VERSION_dump(const struct cibfw_FW_VERSION *ptr_struct, FILE *fd);
/* TRIPPLE_VERSION */
void cibfw_TRIPPLE_VERSION_pack(const struct cibfw_TRIPPLE_VERSION *ptr_struct, u_int8_t *ptr_buff);
void cibfw_TRIPPLE_VERSION_unpack(struct cibfw_TRIPPLE_VERSION *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_TRIPPLE_VERSION_print(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_TRIPPLE_VERSION_size(void);
#define CIBFW_TRIPPLE_VERSION_SIZE    (0x8)
void cibfw_TRIPPLE_VERSION_dump(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE *fd);
/* guids */
void cibfw_guids_pack(const struct cibfw_guids *ptr_struct, u_int8_t *ptr_buff);
void cibfw_guids_unpack(struct cibfw_guids *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_guids_print(const struct cibfw_guids *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_guids_size(void);
#define CIBFW_GUIDS_SIZE    (0x40)
void cibfw_guids_dump(const struct cibfw_guids *ptr_struct, FILE *fd);
/* image_size */
void cibfw_image_size_pack(const struct cibfw_image_size *ptr_struct, u_int8_t *ptr_buff);
void cibfw_image_size_unpack(struct cibfw_image_size *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_image_size_print(const struct cibfw_image_size *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_image_size_size(void);
#define CIBFW_IMAGE_SIZE_SIZE    (0x8)
void cibfw_image_size_dump(const struct cibfw_image_size *ptr_struct, FILE *fd);
/* lfwp_version_vector */
void cibfw_lfwp_version_vector_pack(const struct cibfw_lfwp_version_vector *ptr_struct, u_int8_t *ptr_buff);
void cibfw_lfwp_version_vector_unpack(struct cibfw_lfwp_version_vector *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_lfwp_version_vector_print(const struct cibfw_lfwp_version_vector *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_lfwp_version_vector_size(void);
#define CIBFW_LFWP_VERSION_VECTOR_SIZE    (0x40)
void cibfw_lfwp_version_vector_dump(const struct cibfw_lfwp_version_vector *ptr_struct, FILE *fd);
/* module_version */
void cibfw_module_version_pack(const struct cibfw_module_version *ptr_struct, u_int8_t *ptr_buff);
void cibfw_module_version_unpack(struct cibfw_module_version *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_module_version_print(const struct cibfw_module_version *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_module_version_size(void);
#define CIBFW_MODULE_VERSION_SIZE    (0x4)
void cibfw_module_version_dump(const struct cibfw_module_version *ptr_struct, FILE *fd);
/* operation_key */
void cibfw_operation_key_pack(const struct cibfw_operation_key *ptr_struct, u_int8_t *ptr_buff);
void cibfw_operation_key_unpack(struct cibfw_operation_key *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_operation_key_print(const struct cibfw_operation_key *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_operation_key_size(void);
#define CIBFW_OPERATION_KEY_SIZE    (0x10)
void cibfw_operation_key_dump(const struct cibfw_operation_key *ptr_struct, FILE *fd);
/* device_info */
void cibfw_device_info_pack(const struct cibfw_device_info *ptr_struct, u_int8_t *ptr_buff);
void cibfw_device_info_unpack(struct cibfw_device_info *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_device_info_print(const struct cibfw_device_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_device_info_size(void);
#define CIBFW_DEVICE_INFO_SIZE    (0x200)
void cibfw_device_info_dump(const struct cibfw_device_info *ptr_struct, FILE *fd);
/* image_info */
void cibfw_image_info_pack(const struct cibfw_image_info *ptr_struct, u_int8_t *ptr_buff);
void cibfw_image_info_unpack(struct cibfw_image_info *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_image_info_print(const struct cibfw_image_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_image_info_size(void);
#define CIBFW_IMAGE_INFO_SIZE    (0x400)
void cibfw_image_info_dump(const struct cibfw_image_info *ptr_struct, FILE *fd);
/* itoc_entry */
void cibfw_itoc_entry_pack(const struct cibfw_itoc_entry *ptr_struct, u_int8_t *ptr_buff);
void cibfw_itoc_entry_unpack(struct cibfw_itoc_entry *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_itoc_entry_print(const struct cibfw_itoc_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_itoc_entry_size(void);
#define CIBFW_ITOC_ENTRY_SIZE    (0x20)
void cibfw_itoc_entry_dump(const struct cibfw_itoc_entry *ptr_struct, FILE *fd);
/* itoc_header */
void cibfw_itoc_header_pack(const struct cibfw_itoc_header *ptr_struct, u_int8_t *ptr_buff);
void cibfw_itoc_header_unpack(struct cibfw_itoc_header *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_itoc_header_print(const struct cibfw_itoc_header *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_itoc_header_size(void);
#define CIBFW_ITOC_HEADER_SIZE    (0x20)
void cibfw_itoc_header_dump(const struct cibfw_itoc_header *ptr_struct, FILE *fd);
/* mfg_info */
void cibfw_mfg_info_pack(const struct cibfw_mfg_info *ptr_struct, u_int8_t *ptr_buff);
void cibfw_mfg_info_unpack(struct cibfw_mfg_info *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_mfg_info_print(const struct cibfw_mfg_info *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_mfg_info_size(void);
#define CIBFW_MFG_INFO_SIZE    (0x140)
void cibfw_mfg_info_dump(const struct cibfw_mfg_info *ptr_struct, FILE *fd);
/* register_mfai */
void cibfw_register_mfai_pack(const struct cibfw_register_mfai *ptr_struct, u_int8_t *ptr_buff);
void cibfw_register_mfai_unpack(struct cibfw_register_mfai *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_register_mfai_print(const struct cibfw_register_mfai *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_register_mfai_size(void);
#define CIBFW_REGISTER_MFAI_SIZE    (0x10)
void cibfw_register_mfai_dump(const struct cibfw_register_mfai *ptr_struct, FILE *fd);
/* register_mfrl */
void cibfw_register_mfrl_pack(const struct cibfw_register_mfrl *ptr_struct, u_int8_t *ptr_buff);
void cibfw_register_mfrl_unpack(struct cibfw_register_mfrl *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_register_mfrl_print(const struct cibfw_register_mfrl *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_register_mfrl_size(void);
#define CIBFW_REGISTER_MFRL_SIZE    (0x10)
void cibfw_register_mfrl_dump(const struct cibfw_register_mfrl *ptr_struct, FILE *fd);
/* cibfw_Nodes */
void cibfw_cibfw_Nodes_pack(const union cibfw_cibfw_Nodes *ptr_struct, u_int8_t *ptr_buff);
void cibfw_cibfw_Nodes_unpack(union cibfw_cibfw_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void cibfw_cibfw_Nodes_print(const union cibfw_cibfw_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int cibfw_cibfw_Nodes_size(void);
#define CIBFW_CIBFW_NODES_SIZE    (0x400)
void cibfw_cibfw_Nodes_dump(const union cibfw_cibfw_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // CIBFW_LAYOUTS_H
