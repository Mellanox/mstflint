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
 *** This file was generated at "2014-03-23 17:16:21"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/cibfw/cibfw.adb --file-prefix cibfw --prefix cibfw_
 ***/
#ifndef CIBFW_LAYOUTS_H
#define CIBFW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"/* Description -   */
/* Size in bytes - 8 */
struct cibfw_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 4.31 */
	 u_int32_t hi;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 8.31 */
	 u_int32_t lo;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_uid_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of allocated UIDs in this entry */
	/* 0.0 - 0.7 */
	 u_int8_t num_allocated;
	/* Description - Step size by which to derive the UIDs for this entry
See struct description */
	/* 0.8 - 0.15 */
	 u_int8_t step;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For MACs, the upper 16 bits in the 'hi' dword are reserved */
	/* 8.0 - 16.31 */
	 u_int64_t uid;
};

/* Description -   */
/* Size in bytes - 8 */
struct cibfw_TRIPPLE_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.16 - 4.31 */
	 u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 4.15 */
	 u_int16_t SUBMINOR;
	/* Description -  */
	/* 4.16 - 8.31 */
	 u_int16_t MINOR;
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_FW_VERSION {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.16 - 4.31 */
	 u_int16_t MAJOR;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 4.15 */
	 u_int16_t SUBMINOR;
	/* Description -  */
	/* 4.16 - 8.31 */
	 u_int16_t MINOR;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.8 - 8.15 */
	 u_int8_t Hour;
	/* Description -  */
	/* 8.16 - 8.23 */
	 u_int8_t Minutes;
	/* Description -  */
	/* 8.24 - 12.31 */
	 u_int8_t Seconds;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 12.0 - 12.7 */
	 u_int8_t Day;
	/* Description -  */
	/* 12.8 - 12.15 */
	 u_int8_t Month;
	/* Description -  */
	/* 12.16 - 16.31 */
	 u_int16_t Year;
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
	/* 0.0 - 32.31 */
	 struct cibfw_uid_entry guids[2];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 32.0 - 64.31 */
	 struct cibfw_uid_entry macs[2];
};

/* Description -   */
/* Size in bytes - 16 */
struct cibfw_operation_key {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 0.15 */
	 u_int16_t key_modifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.0 - 16.31 */
	 u_int64_t key;
};

/* Description -   */
/* Size in bytes - 1024 */
struct cibfw_image_info {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 20.31 */
	 struct cibfw_FW_VERSION FW_VERSION;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 20.0 - 28.31 */
	 struct cibfw_TRIPPLE_VERSION mic_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 36.24 - 52.23 */
	 char psid[17];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 52.0 - 52.15 */
	 u_int16_t vsd_vendor_id;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 56.24 - 264.23 */
	 char vsd[209];
/*---------------- DWORD[70] (Offset 0x118) ----------------*/
	/* Description - HW device(s) supported by this FW image.
0 means invalid entry.
For Golan A0, first entry should be 0x1ff
 */
	/* 280.0 - 296.31 */
	 u_int32_t supported_hw_id[4];
/*---------------- DWORD[74] (Offset 0x128) ----------------*/
	/* Description -  */
	/* 296.0 - 300.31 */
	 u_int32_t ini_file_num;
/*---------------- DWORD[112] (Offset 0x1c0) ----------------*/
	/* Description - Product Version is the unified version of the FW and expansion ROM.
Format is defined by the packager.
When set to a non-empty string the FW update tool burns the image as a monolythic entity and refuses to update rom only or FW only. */
	/* 448.24 - 464.23 */
	 char prod_ver[17];
};

/* Description -   */
/* Size in bytes - 320 */
struct cibfw_mfg_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.24 - 16.23 */
	 char psid[17];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - When this bit is set, the GUIDs should eb taken from the device_info node.
When this bit is cleared, the GUIDs should be taken from the mfg_info node. */
	/* 28.0 - 28.0 */
	 u_int8_t guids_override_en;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 32.0 - 96.31 */
	 struct cibfw_guids guids;
};

/* Description -   */
/* Size in bytes - 512 */
struct cibfw_device_info {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 4.31 */
	 u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 4.0 - 8.31 */
	 u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 8.0 - 12.31 */
	 u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 12.0 - 16.31 */
	 u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Format version for this struct */
	/* 16.0 - 16.7 */
	 u_int8_t minor_version;
	/* Description - Format version for this struct */
	/* 16.8 - 16.16 */
	 u_int16_t major_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 32.0 - 96.31 */
	 struct cibfw_guids guids;
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 108.0 - 108.15 */
	 u_int16_t vsd_vendor_id;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 112.24 - 320.23 */
	 char vsd[209];
/*---------------- DWORD[88] (Offset 0x160) ----------------*/
	/* Description -  */
	/* 352.0 - 416.31 */
	 struct cibfw_operation_key keys[4];
};

/* Description -   */
/* Size in bytes - 32 */
struct cibfw_itoc_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 49 54 4f 43 */
	/* 0.0 - 4.31 */
	 u_int32_t signature0;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 04 08 15 16 */
	/* 4.0 - 8.31 */
	 u_int32_t signature1;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 23 42 ca fa */
	/* 8.0 - 12.31 */
	 u_int32_t signature2;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ba ca fe 00 */
	/* 12.0 - 16.31 */
	 u_int32_t signature3;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Current version: 1 */
	/* 16.0 - 16.7 */
	 u_int8_t version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 28.0 - 28.15 */
	 u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 32 */
struct cibfw_itoc_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.2 - 0.23 */
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
	/* 0.24 - 4.31 */
	 u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - if partition type is code or ini then the load address is in here */
	/* 4.0 - 4.29 */
	 u_int32_t param0;
	/* Description - When this bit is set, Data within the section is protected by per-line crc. See yu.flash.replacement.crc_en */
	/* 4.30 - 4.30 */
	 u_int8_t cache_line_crc;
	/* Description - When this bit is set, image is zipped */
	/* 4.31 - 8.31 */
	 u_int8_t zipped_image;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - if partition type is code then the jump address is in here */
	/* 8.0 - 12.31 */
	 u_int32_t param1;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 20.2 - 20.30 */
	 u_int32_t flash_addr;
	/* Description -  */
	/* 20.31 - 24.31 */
	 u_int8_t relative_addr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 24.0 - 24.15 */
	 u_int16_t section_crc;
	/* Description -  */
	/* 24.16 - 24.16 */
	 u_int8_t no_crc;
	/* Description - When this bit is set, the section pointed by this entry in belongs to teh device tather than to teh FW image.
A device_data section should not be updated in a regular FW update.
Example for device_data section: VPD_R, GUIDs. */
	/* 24.17 - 24.17 */
	 u_int8_t device_data;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 28.0 - 28.15 */
	 u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 1024 */
union cibfw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0.0 - 32.31 */
	 struct cibfw_itoc_entry itoc_entry;
	/* Description -  */
	/* 0.0 - 64.31 */
	 struct cibfw_guids guids;
	/* Description -  */
	/* 0.0 - 32.31 */
	 struct cibfw_itoc_header itoc_header;
	/* Description -  */
	/* 0.0 - 512.31 */
	 struct cibfw_device_info device_info;
	/* Description -  */
	/* 0.0 - 320.31 */
	 struct cibfw_mfg_info mfg_info;
	/* Description -  */
	/* 0.0 - 1024.31 */
	 struct cibfw_image_info image_info;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* uint64 */
void cibfw_uint64_pack(const struct cibfw_uint64 *ptr_struct, u_int8_t* ptr_buff);
void cibfw_uint64_unpack(struct cibfw_uint64 *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_uint64_print(const struct cibfw_uint64 *ptr_struct, FILE* file, int indent_level);
int cibfw_uint64_size();
#define CIBFW_UINT64_SIZE    (0x8)
void cibfw_uint64_dump(const struct cibfw_uint64 *ptr_struct, FILE* file);
/* uid_entry */
void cibfw_uid_entry_pack(const struct cibfw_uid_entry *ptr_struct, u_int8_t* ptr_buff);
void cibfw_uid_entry_unpack(struct cibfw_uid_entry *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_uid_entry_print(const struct cibfw_uid_entry *ptr_struct, FILE* file, int indent_level);
int cibfw_uid_entry_size();
#define CIBFW_UID_ENTRY_SIZE    (0x10)
void cibfw_uid_entry_dump(const struct cibfw_uid_entry *ptr_struct, FILE* file);
/* TRIPPLE_VERSION */
void cibfw_TRIPPLE_VERSION_pack(const struct cibfw_TRIPPLE_VERSION *ptr_struct, u_int8_t* ptr_buff);
void cibfw_TRIPPLE_VERSION_unpack(struct cibfw_TRIPPLE_VERSION *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_TRIPPLE_VERSION_print(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE* file, int indent_level);
int cibfw_TRIPPLE_VERSION_size();
#define CIBFW_TRIPPLE_VERSION_SIZE    (0x8)
void cibfw_TRIPPLE_VERSION_dump(const struct cibfw_TRIPPLE_VERSION *ptr_struct, FILE* file);
/* FW_VERSION */
void cibfw_FW_VERSION_pack(const struct cibfw_FW_VERSION *ptr_struct, u_int8_t* ptr_buff);
void cibfw_FW_VERSION_unpack(struct cibfw_FW_VERSION *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_FW_VERSION_print(const struct cibfw_FW_VERSION *ptr_struct, FILE* file, int indent_level);
int cibfw_FW_VERSION_size();
#define CIBFW_FW_VERSION_SIZE    (0x10)
void cibfw_FW_VERSION_dump(const struct cibfw_FW_VERSION *ptr_struct, FILE* file);
/* guids */
void cibfw_guids_pack(const struct cibfw_guids *ptr_struct, u_int8_t* ptr_buff);
void cibfw_guids_unpack(struct cibfw_guids *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_guids_print(const struct cibfw_guids *ptr_struct, FILE* file, int indent_level);
int cibfw_guids_size();
#define CIBFW_GUIDS_SIZE    (0x40)
void cibfw_guids_dump(const struct cibfw_guids *ptr_struct, FILE* file);
/* operation_key */
void cibfw_operation_key_pack(const struct cibfw_operation_key *ptr_struct, u_int8_t* ptr_buff);
void cibfw_operation_key_unpack(struct cibfw_operation_key *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_operation_key_print(const struct cibfw_operation_key *ptr_struct, FILE* file, int indent_level);
int cibfw_operation_key_size();
#define CIBFW_OPERATION_KEY_SIZE    (0x10)
void cibfw_operation_key_dump(const struct cibfw_operation_key *ptr_struct, FILE* file);
/* image_info */
void cibfw_image_info_pack(const struct cibfw_image_info *ptr_struct, u_int8_t* ptr_buff);
void cibfw_image_info_unpack(struct cibfw_image_info *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_image_info_print(const struct cibfw_image_info *ptr_struct, FILE* file, int indent_level);
int cibfw_image_info_size();
#define CIBFW_IMAGE_INFO_SIZE    (0x400)
void cibfw_image_info_dump(const struct cibfw_image_info *ptr_struct, FILE* file);
/* mfg_info */
void cibfw_mfg_info_pack(const struct cibfw_mfg_info *ptr_struct, u_int8_t* ptr_buff);
void cibfw_mfg_info_unpack(struct cibfw_mfg_info *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_mfg_info_print(const struct cibfw_mfg_info *ptr_struct, FILE* file, int indent_level);
int cibfw_mfg_info_size();
#define CIBFW_MFG_INFO_SIZE    (0x140)
void cibfw_mfg_info_dump(const struct cibfw_mfg_info *ptr_struct, FILE* file);
/* device_info */
void cibfw_device_info_pack(const struct cibfw_device_info *ptr_struct, u_int8_t* ptr_buff);
void cibfw_device_info_unpack(struct cibfw_device_info *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_device_info_print(const struct cibfw_device_info *ptr_struct, FILE* file, int indent_level);
int cibfw_device_info_size();
#define CIBFW_DEVICE_INFO_SIZE    (0x200)
void cibfw_device_info_dump(const struct cibfw_device_info *ptr_struct, FILE* file);
/* itoc_header */
void cibfw_itoc_header_pack(const struct cibfw_itoc_header *ptr_struct, u_int8_t* ptr_buff);
void cibfw_itoc_header_unpack(struct cibfw_itoc_header *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_itoc_header_print(const struct cibfw_itoc_header *ptr_struct, FILE* file, int indent_level);
int cibfw_itoc_header_size();
#define CIBFW_ITOC_HEADER_SIZE    (0x20)
void cibfw_itoc_header_dump(const struct cibfw_itoc_header *ptr_struct, FILE* file);
/* itoc_entry */
void cibfw_itoc_entry_pack(const struct cibfw_itoc_entry *ptr_struct, u_int8_t* ptr_buff);
void cibfw_itoc_entry_unpack(struct cibfw_itoc_entry *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_itoc_entry_print(const struct cibfw_itoc_entry *ptr_struct, FILE* file, int indent_level);
int cibfw_itoc_entry_size();
#define CIBFW_ITOC_ENTRY_SIZE    (0x20)
void cibfw_itoc_entry_dump(const struct cibfw_itoc_entry *ptr_struct, FILE* file);
/* Nodes */
void cibfw_Nodes_pack(const union cibfw_Nodes *ptr_struct, u_int8_t* ptr_buff);
void cibfw_Nodes_unpack(union cibfw_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void cibfw_Nodes_print(const union cibfw_Nodes *ptr_struct, FILE* file, int indent_level);
int cibfw_Nodes_size();
#define CIBFW_NODES_SIZE    (0x400)
void cibfw_Nodes_dump(const union cibfw_Nodes *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // CIBFW_LAYOUTS_H
