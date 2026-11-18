/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 *** This file was generated at "2025-08-14 16:59:03"
 *** by:
 ***    > [REDACTED]/adb2pack.py --input adb/fs6_image_layout/fs6_image_layout.adb --file-prefix fs6_image_layout --prefix fs6_image_layout_ --no-adb-utils
 ***/
#ifndef FS6_IMAGE_LAYOUT_LAYOUTS_H
#define FS6_IMAGE_LAYOUT_LAYOUTS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "adb_to_c_utils.h"
    /* Description -   */
    /* Size in bytes - 8 */
    struct fs6_image_layout_hi_lo
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.31 */
        /* access: RW */
        u_int32_t hi;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.31 */
        /* access: RW */
        u_int32_t lo;
    };

    /* Description -   */
    /* Size in bytes - 4 */
    struct fs6_image_layout_reset_ver_info
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - Initial capability for reset level */
        /* 0x0.0 - 0x0.0 */
        /* access: RW */
        u_int8_t reset_ver_en;
        /* Description - 1- before reset
 0- after reset */
        /* 0x0.1 - 0x0.1 */
        /* access: RW */
        u_int8_t before_after_reset;
        /* Description -  */
        /* 0x0.8 - 0x0.15 */
        /* access: RW */
        u_int8_t version_vector_ver;
    };

    /* Description -   */
    /* Size in bytes - 4 */
    struct fs6_image_layout_reset_version_v2
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.15 */
        /* access: RW */
        u_int16_t major;
        /* Description -  */
        /* 0x0.16 - 0x0.19 */
        /* access: RW */
        u_int8_t branch;
        /* Description -  */
        /* 0x0.20 - 0x0.27 */
        /* access: RW */
        u_int8_t minor;
    };

    /* Description -   */
    /* Size in bytes - 16 */
    struct fs6_image_layout_uid_entry
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - Number of allocated UIDs in this entry */
        /* 0x0.0 - 0x0.7 */
        /* access: RW */
        u_int8_t num_allocated;
        /* Description - Step size by which to derive the UIDs for this entry
See struct description */
        /* 0x0.8 - 0x0.15 */
        /* access: RW */
        u_int8_t step;
        /* Description - MSB of number of allocated UIDs in this entry */
        /* 0x0.16 - 0x0.23 */
        /* access: RW */
        u_int8_t num_allocated_msb;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description - For MACs, the upper 16 bits in the 'hi' dword are reserved */
        /* 0x8.0 - 0xc.31 */
        /* access: RW */
        struct fs6_image_layout_hi_lo uid;
    };

    /* Description -   */
    /* Size in bytes - 16 */
    struct fs6_image_layout_FW_VERSION
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.16 - 0x0.31 */
        /* access: RW */
        u_int16_t MAJOR;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.15 */
        /* access: RW */
        u_int16_t SUBMINOR;
        /* Description -  */
        /* 0x4.16 - 0x4.31 */
        /* access: RW */
        u_int16_t MINOR;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description -  */
        /* 0x8.8 - 0x8.15 */
        /* access: RW */
        u_int8_t Hour;
        /* Description -  */
        /* 0x8.16 - 0x8.23 */
        /* access: RW */
        u_int8_t Minutes;
        /* Description -  */
        /* 0x8.24 - 0x8.31 */
        /* access: RW */
        u_int8_t Seconds;
        /*---------------- DWORD[3] (Offset 0xc) ----------------*/
        /* Description -  */
        /* 0xc.0 - 0xc.7 */
        /* access: RW */
        u_int8_t Day;
        /* Description -  */
        /* 0xc.8 - 0xc.15 */
        /* access: RW */
        u_int8_t Month;
        /* Description -  */
        /* 0xc.16 - 0xc.31 */
        /* access: RW */
        u_int16_t Year;
    };

    /* Description -   */
    /* Size in bytes - 8 */
    struct fs6_image_layout_TRIPPLE_VERSION
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.16 - 0x0.31 */
        /* access: RW */
        u_int16_t MAJOR;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.15 */
        /* access: RW */
        u_int16_t SUBMINOR;
        /* Description -  */
        /* 0x4.16 - 0x4.31 */
        /* access: RW */
        u_int16_t MINOR;
    };

    /* Description -   */
    /* Size in bytes - 64 */
    struct fs6_image_layout_guids
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - UIDs (MACs and GUIDs) Allocation Entry.
guids, is used for system GUID, node GUID and port GUID of port 0. ;/Multiple UIDs can be assigned to a single port, to
be used for multiple virtual guests, multi host and managment */
        /* 0x0.0 - 0xc.31 */
        /* access: RW */
        struct fs6_image_layout_uid_entry guids;
        /*---------------- DWORD[4] (Offset 0x10) ----------------*/
        /* Description -  */
        /* 0x10.0 - 0x1c.31 */
        /* access: RW */
        struct fs6_image_layout_uid_entry macs;
    };

    /* Description -   */
    /* Size in bytes - 8 */
    struct fs6_image_layout_image_size
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - log of next address in bytes to search for an image. Address in bytes is 2^log_step */
        /* 0x0.0 - 0x0.7 */
        /* access: RW */
        u_int8_t log_step;
        /* Description - this image can run from any partition starting at address 0x0, 0x400000, 0x800000. The code
         * supports only two partitions. */
        /* 0x0.31 - 0x0.31 */
        /* access: RW */
        u_int8_t run_from_any;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description - Max possible size in bytes of image. Image read / write should not occure beyond this address
         */
        /* 0x4.0 - 0x4.31 */
        /* access: RW */
        u_int32_t max_size;
    };

    /* Description -   */
    /* Size in bytes - 8 */
    struct fs6_image_layout_module_version_issu
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.7 */
        /* access: RW */
        u_int8_t branch;
        /* Description -  */
        /* 0x0.8 - 0x0.19 */
        /* access: RW */
        u_int16_t minor;
        /* Description -  */
        /* 0x0.20 - 0x0.31 */
        /* access: RW */
        u_int16_t major;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.11 */
        /* access: RW */
        u_int16_t notch;
    };

    /* Description -   */
    /* Size in bytes - 48 */
    struct fs6_image_layout_version_vector
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x0.31 */
        /* access: RW */
        struct fs6_image_layout_reset_ver_info reset_capabilities;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x4.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 scratchpad;
        /*---------------- DWORD[2] (Offset 0x8) ----------------*/
        /* Description -  */
        /* 0x8.0 - 0x8.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 icm_context;
        /*---------------- DWORD[3] (Offset 0xc) ----------------*/
        /* Description -  */
        /* 0xc.0 - 0xc.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 pci;
        /*---------------- DWORD[4] (Offset 0x10) ----------------*/
        /* Description -  */
        /* 0x10.0 - 0x10.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 phy;
        /*---------------- DWORD[5] (Offset 0x14) ----------------*/
        /* Description -  */
        /* 0x14.0 - 0x14.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 ini;
        /*---------------- DWORD[6] (Offset 0x18) ----------------*/
        /* Description -  */
        /* 0x18.0 - 0x18.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 mng;
        /*---------------- DWORD[7] (Offset 0x1c) ----------------*/
        /* Description -  */
        /* 0x1c.0 - 0x1c.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 reserved2;
        /*---------------- DWORD[8] (Offset 0x20) ----------------*/
        /* Description -  */
        /* 0x20.0 - 0x20.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 reserved3;
        /*---------------- DWORD[9] (Offset 0x24) ----------------*/
        /* Description -  */
        /* 0x24.0 - 0x24.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 reserved4;
        /*---------------- DWORD[10] (Offset 0x28) ----------------*/
        /* Description -  */
        /* 0x28.0 - 0x28.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 reserved5;
        /*---------------- DWORD[11] (Offset 0x2c) ----------------*/
        /* Description -  */
        /* 0x2c.0 - 0x2c.31 */
        /* access: RW */
        struct fs6_image_layout_reset_version_v2 reserved6;
    };

    /* Description -   */
    /* Size in bytes - 1024 */
    struct fs6_image_layout_image_info
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description - FA (RMA) token is supported or not */
        /* 0x0.1 - 0x0.1 */
        /* access: RW */
        u_int8_t fa_token_supported;
        /* Description - 0x0 - not encrypted; 0x1 - encryption before signature; 0x2 - encryption after signature.  */
        /* 0x0.3 - 0x0.4 */
        /* access: RW */
        u_int8_t encrypted_fw;
        /* Description - 0x0 - secure boot will reach GIS=0x5e without PCS in image; 0x1 - secure boot expect PSCFW in
         * image and will get stuck without */
        /* 0x0.5 - 0x0.5 */
        /* access: RW */
        u_int8_t pscfw_en;
        /* Description - Indicate that this binary support long keys (up to 4096bits) */
        /* 0x0.6 - 0x0.6 */
        /* access: RW */
        u_int8_t long_keys;
        /* Description - when set, debug-fw tokens are enabled. */
        /* 0x0.7 - 0x0.7 */
        /* access: RW */
        u_int8_t debug_fw_tokens_supported;
        /* Description - The image can be updated using the MCC/MCDA commands */
        /* 0x0.8 - 0x0.8 */
        /* access: RW */
        u_int8_t mcc_en;
        /* Description - OEM lifecycle NVCONFIG files are signed */
        /* 0x0.9 - 0x0.9 */
        /* access: RW */
        u_int8_t signed_vendor_nvconfig_files;
        /* Description - Mellanox lifecycle NVCONFIG files are signed */
        /* 0x0.10 - 0x0.10 */
        /* access: RW */
        u_int8_t signed_mlnx_nvconfig_files;
        /* Description - Factory re-customizationflow is supported */
        /* 0x0.11 - 0x0.11 */
        /* access: RW */
        u_int8_t frc_supported;
        /* Description - Customer Support Tokens are supported */
        /* 0x0.12 - 0x0.12 */
        /* access: RW */
        u_int8_t cs_tokens_supported;
        /* Description - This is a debug firmware */
        /* 0x0.13 - 0x0.13 */
        /* access: RW */
        u_int8_t debug_fw;
        /* Description - [MCC/MCDA flow] if set, the SHA 256 digest is encrypted - enabled by default for secure_fw -
         * cr-space not closed */
        /* 0x0.14 - 0x0.14 */
        /* access: RW */
        u_int8_t signed_fw;
        /* Description - [MCC/MCDA flow] cr-space closed */
        /* 0x0.15 - 0x0.15 */
        /* access: RW */
        u_int8_t secure_fw;
        /* Description - IMAGE_INFO section minor version */
        /* 0x0.16 - 0x0.23 */
        /* access: RW */
        u_int8_t minor_version;
        /* Description - IMAGE_INFO section major version */
        /* 0x0.24 - 0x0.31 */
        /* access: RW */
        u_int8_t major_version;
        /*---------------- DWORD[1] (Offset 0x4) ----------------*/
        /* Description -  */
        /* 0x4.0 - 0x10.31 */
        /* access: RW */
        struct fs6_image_layout_FW_VERSION FW_VERSION;
        /*---------------- DWORD[5] (Offset 0x14) ----------------*/
        /* Description -  */
        /* 0x14.0 - 0x18.31 */
        /* access: RW */
        struct fs6_image_layout_TRIPPLE_VERSION mic_version;
        /*---------------- DWORD[9] (Offset 0x24) ----------------*/
        /* Description -  */
        /* 0x24.24 - 0x34.23 */
        /* access: RW */
        char psid[17];
        /*---------------- DWORD[13] (Offset 0x34) ----------------*/
        /* Description -  */
        /* 0x34.0 - 0x34.15 */
        /* access: RW */
        u_int16_t vsd_vendor_id;
        /* Description - Indicates that the NV_DATA is encrypted. DO NOT move this bit */
        /* 0x34.24 - 0x34.24 */
        /* access: RW */
        u_int8_t encrypted_nvdata;
        /*---------------- DWORD[14] (Offset 0x38) ----------------*/
        /* Description -  */
        /* 0x38.24 - 0x108.23 */
        /* access: RW */
        char vsd[209];
        /*---------------- DWORD[66] (Offset 0x108) ----------------*/
        /* Description - image size parameters */
        /* 0x108.0 - 0x10c.31 */
        /* access: RW */
        struct fs6_image_layout_image_size image_size;
        /*---------------- DWORD[70] (Offset 0x118) ----------------*/
        /* Description - HW device(s) supported by this FW image.
0 means invalid entry.
For Golan A0, first entry should be 0x1ff
 */
        /* 0x118.0 - 0x124.31 */
        /* access: RW */
        u_int32_t supported_hw_id[4];
        /*---------------- DWORD[74] (Offset 0x128) ----------------*/
        /* Description -  */
        /* 0x128.0 - 0x128.31 */
        /* access: RW */
        u_int32_t ini_file_num;
        /*---------------- DWORD[75] (Offset 0x12c) ----------------*/
        /* Description -  */
        /* 0x12c.0 - 0x12c.31 */
        /* access: RW */
        u_int32_t burn_image_size;
        /*---------------- DWORD[76] (Offset 0x130) ----------------*/
        /* Description - 0: legacy, dtoc header is located in flash_size -0x1000; 1: dtoc header is located in
         * flash_size/2 -0x1000 */
        /* 0x130.8 - 0x130.15 */
        /* access: RW */
        u_int8_t dtoc_offset;
        /*---------------- DWORD[100] (Offset 0x190) ----------------*/
        /* Description -  */
        /* 0x190.0 - 0x1bc.31 */
        /* access: RW */
        struct fs6_image_layout_version_vector version_vector;
        /*---------------- DWORD[112] (Offset 0x1c0) ----------------*/
        /* Description - Product Version is the unified version of the FW and expansion ROM.
Format is defined by the packager.
When set to a non-empty string the FW update tool burns the image as a monolythic entity and refuses to update rom only
or FW only. */
        /* 0x1c0.24 - 0x1d0.23 */
        /* access: RW */
        char prod_ver[17];
        /*---------------- DWORD[116] (Offset 0x1d0) ----------------*/
        /* Description - Product description */
        /* 0x1d0.24 - 0x2d0.23 */
        /* access: RW */
        char description[257];
        /*---------------- DWORD[180] (Offset 0x2d0) ----------------*/
        /* Description - Product board name */
        /* 0x2d0.8 - 0x2e0.7 */
        /* access: RW */
        char board_name[17];
        /*---------------- DWORD[197] (Offset 0x314) ----------------*/
        /* Description -  */
        /* 0x314.0 - 0x318.31 */
        /* access: RW */
        struct fs6_image_layout_module_version_issu isfu;
        /*---------------- DWORD[199] (Offset 0x31c) ----------------*/
        /* Description - Indicates what tiles are not valid to use by FW */
        /* 0x31c.0 - 0x31c.15 */
        /* access: RW */
        u_int16_t disabled_tiles_bitmap;
        /*---------------- DWORD[208] (Offset 0x340) ----------------*/
        /* Description - Product name */
        /* 0x340.24 - 0x380.23 */
        /* access: RW */
        char name[65];
        /*---------------- DWORD[224] (Offset 0x380) ----------------*/
        /* Description - PRS used to generate the FW binary */
        /* 0x380.24 - 0x3e0.23 */
        /* access: RW */
        char prs_name[97];
    };

    /* Description -   */
    /* Size in bytes - 320 */
    struct fs6_image_layout_mfg_info
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.24 - 0x10.23 */
        /* access: RW */
        char psid[17];
        /*---------------- DWORD[7] (Offset 0x1c) ----------------*/
        /* Description - When this bit is set, the GUIDs should be taken from the device_info node.
When this bit is cleared, the GUIDs should be taken from the mfg_info node. */
        /* 0x1c.0 - 0x1c.0 */
        /* access: RW */
        u_int8_t guids_override_en;
        /* Description - MFG_INFO section minor version */
        /* 0x1c.16 - 0x1c.23 */
        /* access: RW */
        u_int8_t minor_version;
        /* Description - MFG_INFO section major version */
        /* 0x1c.24 - 0x1c.31 */
        /* access: RW */
        u_int8_t major_version;
        /*---------------- DWORD[8] (Offset 0x20) ----------------*/
        /* Description -  */
        /* 0x20.0 - 0x5c.31 */
        /* access: RW */
        struct fs6_image_layout_guids guids;
        /*---------------- DWORD[24] (Offset 0x60) ----------------*/
        /* Description - original PRS used to generate the FW binary */
        /* 0x60.24 - 0xc0.23 */
        /* access: RW */
        char orig_prs_name[97];
    };

    /* Description -   */
    /* Size in bytes - 1024 */
    union fs6_image_layout_fs6_image_layout_Nodes
    {
        /*---------------- DWORD[0] (Offset 0x0) ----------------*/
        /* Description -  */
        /* 0x0.0 - 0x3fc.31 */
        /* access: RW */
        struct fs6_image_layout_image_info image_info;
        /* Description -  */
        /* 0x0.0 - 0x13c.31 */
        /* access: RW */
        struct fs6_image_layout_mfg_info mfg_info;
    };

    /*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
    /* hi_lo */
    void fs6_image_layout_hi_lo_pack(const struct fs6_image_layout_hi_lo* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_hi_lo_unpack(struct fs6_image_layout_hi_lo* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_hi_lo_print(const struct fs6_image_layout_hi_lo* ptr_struct, FILE* fd, int indent_level);
    unsigned int fs6_image_layout_hi_lo_size(void);
#define FS6_IMAGE_LAYOUT_HI_LO_SIZE (0x8)
    void fs6_image_layout_hi_lo_dump(const struct fs6_image_layout_hi_lo* ptr_struct, FILE* fd);
    /* reset_ver_info */
    void fs6_image_layout_reset_ver_info_pack(const struct fs6_image_layout_reset_ver_info* ptr_struct,
                                              u_int8_t* ptr_buff);
    void fs6_image_layout_reset_ver_info_unpack(struct fs6_image_layout_reset_ver_info* ptr_struct,
                                                const u_int8_t* ptr_buff);
    void fs6_image_layout_reset_ver_info_print(const struct fs6_image_layout_reset_ver_info* ptr_struct,
                                               FILE* fd,
                                               int indent_level);
    unsigned int fs6_image_layout_reset_ver_info_size(void);
#define FS6_IMAGE_LAYOUT_RESET_VER_INFO_SIZE (0x4)
    void fs6_image_layout_reset_ver_info_dump(const struct fs6_image_layout_reset_ver_info* ptr_struct, FILE* fd);
    /* reset_version_v2 */
    void fs6_image_layout_reset_version_v2_pack(const struct fs6_image_layout_reset_version_v2* ptr_struct,
                                                u_int8_t* ptr_buff);
    void fs6_image_layout_reset_version_v2_unpack(struct fs6_image_layout_reset_version_v2* ptr_struct,
                                                  const u_int8_t* ptr_buff);
    void fs6_image_layout_reset_version_v2_print(const struct fs6_image_layout_reset_version_v2* ptr_struct,
                                                 FILE* fd,
                                                 int indent_level);
    unsigned int fs6_image_layout_reset_version_v2_size(void);
#define FS6_IMAGE_LAYOUT_RESET_VERSION_V2_SIZE (0x4)
    void fs6_image_layout_reset_version_v2_dump(const struct fs6_image_layout_reset_version_v2* ptr_struct, FILE* fd);
    /* uid_entry */
    void fs6_image_layout_uid_entry_pack(const struct fs6_image_layout_uid_entry* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_uid_entry_unpack(struct fs6_image_layout_uid_entry* ptr_struct, const u_int8_t* ptr_buff);
    void
      fs6_image_layout_uid_entry_print(const struct fs6_image_layout_uid_entry* ptr_struct, FILE* fd, int indent_level);
    unsigned int fs6_image_layout_uid_entry_size(void);
#define FS6_IMAGE_LAYOUT_UID_ENTRY_SIZE (0x10)
    void fs6_image_layout_uid_entry_dump(const struct fs6_image_layout_uid_entry* ptr_struct, FILE* fd);
    /* FW_VERSION */
    void fs6_image_layout_FW_VERSION_pack(const struct fs6_image_layout_FW_VERSION* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_FW_VERSION_unpack(struct fs6_image_layout_FW_VERSION* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_FW_VERSION_print(const struct fs6_image_layout_FW_VERSION* ptr_struct,
                                           FILE* fd,
                                           int indent_level);
    unsigned int fs6_image_layout_FW_VERSION_size(void);
#define FS6_IMAGE_LAYOUT_FW_VERSION_SIZE (0x10)
    void fs6_image_layout_FW_VERSION_dump(const struct fs6_image_layout_FW_VERSION* ptr_struct, FILE* fd);
    /* TRIPPLE_VERSION */
    void fs6_image_layout_TRIPPLE_VERSION_pack(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                               u_int8_t* ptr_buff);
    void fs6_image_layout_TRIPPLE_VERSION_unpack(struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                                 const u_int8_t* ptr_buff);
    void fs6_image_layout_TRIPPLE_VERSION_print(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct,
                                                FILE* fd,
                                                int indent_level);
    unsigned int fs6_image_layout_TRIPPLE_VERSION_size(void);
#define FS6_IMAGE_LAYOUT_TRIPPLE_VERSION_SIZE (0x8)
    void fs6_image_layout_TRIPPLE_VERSION_dump(const struct fs6_image_layout_TRIPPLE_VERSION* ptr_struct, FILE* fd);
    /* guids */
    void fs6_image_layout_guids_pack(const struct fs6_image_layout_guids* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_guids_unpack(struct fs6_image_layout_guids* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_guids_print(const struct fs6_image_layout_guids* ptr_struct, FILE* fd, int indent_level);
    unsigned int fs6_image_layout_guids_size(void);
#define FS6_IMAGE_LAYOUT_GUIDS_SIZE (0x40)
    void fs6_image_layout_guids_dump(const struct fs6_image_layout_guids* ptr_struct, FILE* fd);
    /* image_size */
    void fs6_image_layout_image_size_pack(const struct fs6_image_layout_image_size* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_image_size_unpack(struct fs6_image_layout_image_size* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_image_size_print(const struct fs6_image_layout_image_size* ptr_struct,
                                           FILE* fd,
                                           int indent_level);
    unsigned int fs6_image_layout_image_size_size(void);
#define FS6_IMAGE_LAYOUT_IMAGE_SIZE_SIZE (0x8)
    void fs6_image_layout_image_size_dump(const struct fs6_image_layout_image_size* ptr_struct, FILE* fd);
    /* module_version_issu */
    void fs6_image_layout_module_version_issu_pack(const struct fs6_image_layout_module_version_issu* ptr_struct,
                                                   u_int8_t* ptr_buff);
    void fs6_image_layout_module_version_issu_unpack(struct fs6_image_layout_module_version_issu* ptr_struct,
                                                     const u_int8_t* ptr_buff);
    void fs6_image_layout_module_version_issu_print(const struct fs6_image_layout_module_version_issu* ptr_struct,
                                                    FILE* fd,
                                                    int indent_level);
    unsigned int fs6_image_layout_module_version_issu_size(void);
#define FS6_IMAGE_LAYOUT_MODULE_VERSION_ISSU_SIZE (0x8)
    void fs6_image_layout_module_version_issu_dump(const struct fs6_image_layout_module_version_issu* ptr_struct,
                                                   FILE* fd);
    /* version_vector */
    void fs6_image_layout_version_vector_pack(const struct fs6_image_layout_version_vector* ptr_struct,
                                              u_int8_t* ptr_buff);
    void fs6_image_layout_version_vector_unpack(struct fs6_image_layout_version_vector* ptr_struct,
                                                const u_int8_t* ptr_buff);
    void fs6_image_layout_version_vector_print(const struct fs6_image_layout_version_vector* ptr_struct,
                                               FILE* fd,
                                               int indent_level);
    unsigned int fs6_image_layout_version_vector_size(void);
#define FS6_IMAGE_LAYOUT_VERSION_VECTOR_SIZE (0x30)
    void fs6_image_layout_version_vector_dump(const struct fs6_image_layout_version_vector* ptr_struct, FILE* fd);
    /* image_info */
    void fs6_image_layout_image_info_pack(const struct fs6_image_layout_image_info* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_image_info_unpack(struct fs6_image_layout_image_info* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_image_info_print(const struct fs6_image_layout_image_info* ptr_struct,
                                           FILE* fd,
                                           int indent_level);
    unsigned int fs6_image_layout_image_info_size(void);
#define FS6_IMAGE_LAYOUT_IMAGE_INFO_SIZE (0x400)
    void fs6_image_layout_image_info_dump(const struct fs6_image_layout_image_info* ptr_struct, FILE* fd);
    /* mfg_info */
    void fs6_image_layout_mfg_info_pack(const struct fs6_image_layout_mfg_info* ptr_struct, u_int8_t* ptr_buff);
    void fs6_image_layout_mfg_info_unpack(struct fs6_image_layout_mfg_info* ptr_struct, const u_int8_t* ptr_buff);
    void fs6_image_layout_mfg_info_print(const struct fs6_image_layout_mfg_info* ptr_struct, FILE* fd, int indent_level);
    unsigned int fs6_image_layout_mfg_info_size(void);
#define FS6_IMAGE_LAYOUT_MFG_INFO_SIZE (0x140)
    void fs6_image_layout_mfg_info_dump(const struct fs6_image_layout_mfg_info* ptr_struct, FILE* fd);
    /* fs6_image_layout_Nodes */
    void fs6_image_layout_fs6_image_layout_Nodes_pack(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                      u_int8_t* ptr_buff);
    void fs6_image_layout_fs6_image_layout_Nodes_unpack(union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                        const u_int8_t* ptr_buff);
    void fs6_image_layout_fs6_image_layout_Nodes_print(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                       FILE* fd,
                                                       int indent_level);
    unsigned int fs6_image_layout_fs6_image_layout_Nodes_size(void);
#define FS6_IMAGE_LAYOUT_FS6_IMAGE_LAYOUT_NODES_SIZE (0x400)
    void fs6_image_layout_fs6_image_layout_Nodes_dump(const union fs6_image_layout_fs6_image_layout_Nodes* ptr_struct,
                                                      FILE* fd);

#ifdef __cplusplus
}
#endif

#endif // FS6_IMAGE_LAYOUT_LAYOUTS_H
