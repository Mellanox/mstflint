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
         *** This file was generated at "2017-05-28 21:03:29"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/cx5fw/cx5fw.adb --file-prefix cx5fw --prefix cx5fw_
         ***/
#ifndef CX5FW_LAYOUTS_H
#define CX5FW_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct cx5fw_hw_pointer_entry {
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
/* Size in bytes - 32 */
struct cx5fw_itoc_entry {
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
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.15 */
	 u_int16_t section_crc;
	/* Description -  */
	/* 0x18.16 - 0x18.18 */
	 u_int8_t crc;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	 u_int16_t itoc_entry_crc;
};

/* Description -   */
/* Size in bytes - 32 */
struct cx5fw_itoc_header {
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
	/* Description - itoc_header: Represents the minimal layout version expected on the flash: 1.
dtoc_header: Represents the layout version depicted by the dTOC: 1. */
	/* 0x10.24 - 0x10.31 */
	 u_int8_t flash_layout_version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.15 */
	 u_int16_t itoc_entry_crc;
};

/* Description -  tools speific section */
/* Size in bytes - 64 */
struct cx5fw_tools_area {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - tools area minor version */
	/* 0x0.0 - 0x0.7 */
	 u_int8_t minor;
	/* Description - tools area major version */
	/* 0x0.8 - 0x0.15 */
	 u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - binary version minor set by image generation tool */
	/* 0x4.0 - 0x4.7 */
	 u_int8_t bin_ver_minor;
	/* Description - binary version major set by image generation tool */
	/* 0x4.8 - 0x4.15 */
	 u_int8_t bin_ver_major;
	/* Description - log2 image slot size */
	/* 0x4.16 - 0x4.31 */
	 u_int16_t log2_img_slot_size;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description -  */
	/* 0x3c.0 - 0x3c.15 */
	 u_int16_t crc;
};

/* Description -  HW pointers */
/* Size in bytes - 48 */
struct cx5fw_hw_pointers {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	 struct cx5fw_hw_pointer_entry boot_record_ptr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	 struct cx5fw_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	 struct cx5fw_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	 struct cx5fw_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	 struct cx5fw_hw_pointer_entry reserved0_ptr;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	 struct cx5fw_hw_pointer_entry reserved1_ptr;
};

/* Description -   */
/* Size in bytes - 16 */
struct cx5fw_operation_key {
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
/* Size in bytes - 16 */
struct cx5fw_uid_entry {
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
/* Size in bytes - 64 */
struct cx5fw_guids {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids, is used for system GUID, node GUID and port GUID of port 0. ;/Multiple UIDs can be assigned to a single port, to be used for multiple virtual guests, multi host and managment */
	/* 0x0.0 - 0xc.31 */
	 struct cx5fw_uid_entry guids;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	 struct cx5fw_uid_entry macs;
};

/* Description -   */
/* Size in bytes - 512 */
struct cx5fw_device_info {
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
	 struct cx5fw_guids guids;
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
	 struct cx5fw_operation_key keys[4];
/*---------------- DWORD[127] (Offset 0x1fc) ----------------*/
	/* Description -  */
	/* 0x1fc.0 - 0x1fc.15 */
	 u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 512 */
union cx5fw_cx5fw_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1fc.31 */
	 struct cx5fw_device_info device_info;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	 struct cx5fw_itoc_header itoc_header;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	 struct cx5fw_tools_area tools_area;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	 struct cx5fw_itoc_entry itoc_entry;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	 struct cx5fw_hw_pointers hw_pointers;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* hw_pointer_entry */
void cx5fw_hw_pointer_entry_pack(const struct cx5fw_hw_pointer_entry *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_hw_pointer_entry_unpack(struct cx5fw_hw_pointer_entry *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_hw_pointer_entry_print(const struct cx5fw_hw_pointer_entry *ptr_struct, FILE* file, int indent_level);
int cx5fw_hw_pointer_entry_size(void);
#define CX5FW_HW_POINTER_ENTRY_SIZE    (0x8)
void cx5fw_hw_pointer_entry_dump(const struct cx5fw_hw_pointer_entry *ptr_struct, FILE* file);
/* itoc_entry */
void cx5fw_itoc_entry_pack(const struct cx5fw_itoc_entry *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_itoc_entry_unpack(struct cx5fw_itoc_entry *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_itoc_entry_print(const struct cx5fw_itoc_entry *ptr_struct, FILE* file, int indent_level);
int cx5fw_itoc_entry_size(void);
#define CX5FW_ITOC_ENTRY_SIZE    (0x20)
void cx5fw_itoc_entry_dump(const struct cx5fw_itoc_entry *ptr_struct, FILE* file);
/* itoc_header */
void cx5fw_itoc_header_pack(const struct cx5fw_itoc_header *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_itoc_header_unpack(struct cx5fw_itoc_header *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_itoc_header_print(const struct cx5fw_itoc_header *ptr_struct, FILE* file, int indent_level);
int cx5fw_itoc_header_size(void);
#define CX5FW_ITOC_HEADER_SIZE    (0x20)
void cx5fw_itoc_header_dump(const struct cx5fw_itoc_header *ptr_struct, FILE* file);
/* tools_area */
void cx5fw_tools_area_pack(const struct cx5fw_tools_area *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_tools_area_unpack(struct cx5fw_tools_area *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_tools_area_print(const struct cx5fw_tools_area *ptr_struct, FILE* file, int indent_level);
int cx5fw_tools_area_size(void);
#define CX5FW_TOOLS_AREA_SIZE    (0x40)
void cx5fw_tools_area_dump(const struct cx5fw_tools_area *ptr_struct, FILE* file);
/* hw_pointers */
void cx5fw_hw_pointers_pack(const struct cx5fw_hw_pointers *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_hw_pointers_unpack(struct cx5fw_hw_pointers *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_hw_pointers_print(const struct cx5fw_hw_pointers *ptr_struct, FILE* file, int indent_level);
int cx5fw_hw_pointers_size(void);
#define CX5FW_HW_POINTERS_SIZE    (0x30)
void cx5fw_hw_pointers_dump(const struct cx5fw_hw_pointers *ptr_struct, FILE* file);
/* operation_key */
void cx5fw_operation_key_pack(const struct cx5fw_operation_key *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_operation_key_unpack(struct cx5fw_operation_key *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_operation_key_print(const struct cx5fw_operation_key *ptr_struct, FILE* file, int indent_level);
int cx5fw_operation_key_size(void);
#define CX5FW_OPERATION_KEY_SIZE    (0x10)
void cx5fw_operation_key_dump(const struct cx5fw_operation_key *ptr_struct, FILE* file);
/* uid_entry */
void cx5fw_uid_entry_pack(const struct cx5fw_uid_entry *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_uid_entry_unpack(struct cx5fw_uid_entry *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_uid_entry_print(const struct cx5fw_uid_entry *ptr_struct, FILE* file, int indent_level);
int cx5fw_uid_entry_size(void);
#define CX5FW_UID_ENTRY_SIZE    (0x10)
void cx5fw_uid_entry_dump(const struct cx5fw_uid_entry *ptr_struct, FILE* file);
/* guids */
void cx5fw_guids_pack(const struct cx5fw_guids *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_guids_unpack(struct cx5fw_guids *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_guids_print(const struct cx5fw_guids *ptr_struct, FILE* file, int indent_level);
int cx5fw_guids_size(void);
#define CX5FW_GUIDS_SIZE    (0x40)
void cx5fw_guids_dump(const struct cx5fw_guids *ptr_struct, FILE* file);
/* device_info */
void cx5fw_device_info_pack(const struct cx5fw_device_info *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_device_info_unpack(struct cx5fw_device_info *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_device_info_print(const struct cx5fw_device_info *ptr_struct, FILE* file, int indent_level);
int cx5fw_device_info_size(void);
#define CX5FW_DEVICE_INFO_SIZE    (0x200)
void cx5fw_device_info_dump(const struct cx5fw_device_info *ptr_struct, FILE* file);
/* cx5fw_Nodes */
void cx5fw_cx5fw_Nodes_pack(const union cx5fw_cx5fw_Nodes *ptr_struct, u_int8_t* ptr_buff);
void cx5fw_cx5fw_Nodes_unpack(union cx5fw_cx5fw_Nodes *ptr_struct, const u_int8_t* ptr_buff);
void cx5fw_cx5fw_Nodes_print(const union cx5fw_cx5fw_Nodes *ptr_struct, FILE* file, int indent_level);
int cx5fw_cx5fw_Nodes_size(void);
#define CX5FW_CX5FW_NODES_SIZE    (0x200)
void cx5fw_cx5fw_Nodes_dump(const union cx5fw_cx5fw_Nodes *ptr_struct, FILE* file);


#ifdef __cplusplus
}
#endif

#endif // CX5FW_LAYOUTS_H
