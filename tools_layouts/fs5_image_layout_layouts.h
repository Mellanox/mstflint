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
         *** This file was generated at "2024-11-04 15:08:38"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/fs5_image_layout/fs5_image_layout.adb --file-prefix fs5_image_layout --prefix fs5_image_layout_ --no-adb-utils
         ***/
#ifndef FS5_IMAGE_LAYOUT_LAYOUTS_H
#define FS5_IMAGE_LAYOUT_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 64 */
struct fs5_image_layout_crypto_ecdsa256_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_r[32];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.24 - 0x40.23 */
	/* access: RW */
	u_int8_t u8_s[32];
};

/* Description -   */
/* Size in bytes - 136 */
struct fs5_image_layout_crypto_ecdsa521_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x44.23 */
	/* access: RW */
	u_int8_t u8_r[68];
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.24 - 0x88.23 */
	/* access: RW */
	u_int8_t u8_s[68];
};

/* Description -   */
/* Size in bytes - 64 */
struct fs5_image_layout_crypto_ed25519_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_r[32];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.24 - 0x40.23 */
	/* access: RW */
	u_int8_t u8_s[32];
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_u8_auth_tag {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	/* access: RW */
	u_int8_t u8_dummy[16];
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_u8_encryption_derivation_string {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	/* access: RW */
	u_int8_t u8_dummy[16];
};

/* Description -   */
/* Size in bytes - 32 */
struct fs5_image_layout_u8_hmac_sha2_256_tag_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_dummy[32];
};

/* Description -   */
/* Size in bytes - 12 */
struct fs5_image_layout_u8_iv {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xc.23 */
	/* access: RW */
	u_int8_t u8_dummy[12];
};

/* Description -   */
/* Size in bytes - 384 */
struct fs5_image_layout_u8_rsa3k_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x180.23 */
	/* access: RW */
	u_int8_t u8_dummy[384];
};

/* Description -   */
/* Size in bytes - 2832 */
struct fs5_image_layout_u8_xmss_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xb10.23 */
	/* access: RW */
	u_int8_t u8_dummy[2832];
};

/* Description -   */
/* Size in bytes - 4 */
struct fs5_image_layout_bch_boot_component_flags {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.29 */
	/* access: RW */
	u_int32_t res;
	/* Description -  */
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t is_debug;
	/* Description -  */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t is_encrypted;
};

/* Description -   */
/* Size in bytes - 4 */
struct fs5_image_layout_boot_component_ver {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t u8_ver_major;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t u8_ver_minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t u8_ratchet_level;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	/* access: RW */
	u_int8_t u8_res;
};

/* Description -   */
/* Size in bytes - 64 */
struct fs5_image_layout_crypto_ecdsa256_pub_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_x[32];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.24 - 0x40.23 */
	/* access: RW */
	u_int8_t u8_y[32];
};

/* Description -   */
/* Size in bytes - 96 */
struct fs5_image_layout_crypto_ecdsa384_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x30.23 */
	/* access: RW */
	u_int8_t u8_r[48];
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.24 - 0x60.23 */
	/* access: RW */
	u_int8_t u8_s[48];
};

/* Description -   */
/* Size in bytes - 136 */
struct fs5_image_layout_crypto_ecdsa521_pub_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x44.23 */
	/* access: RW */
	u_int8_t u8_x[68];
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.24 - 0x88.23 */
	/* access: RW */
	u_int8_t u8_y[68];
};

/* Description -   */
/* Size in bytes - 48 */
struct fs5_image_layout_crypto_encryption_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_encryption_derivation_string u8_encryption_derivation_string;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.7 */
	/* access: RW */
	u_int8_t u8_data_encryption_key_version;
	/* Description -  */
	/* 0x10.8 - 0x10.31 */
	/* access: RW */
	u_int32_t u8_reserved;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_iv u8_iv;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x2c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_auth_tag u8_auth_tag;
};

/* Description -   */
/* Size in bytes - 384 */
struct fs5_image_layout_crypto_rsa3k_pub_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x180.23 */
	/* access: RW */
	u_int8_t u8_dummy[384];
};

/* Description -   */
/* Size in bytes - 4 */
struct fs5_image_layout_flags_bch_stage2_comp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.25 */
	/* access: RW */
	u_int32_t u_pad;
	/* Description -  */
	/* 0x0.26 - 0x0.26 */
	/* access: RW */
	u_int8_t b_is_encrypted;
	/* Description -  */
	/* 0x0.27 - 0x0.27 */
	/* access: RW */
	u_int8_t b_is_compressed;
	/* Description -  */
	/* 0x0.28 - 0x0.31 */
	/* access: RW */
	u_int8_t u_compression_scheme;
};

/* Description -  flash parameters configuration on early boot */
/* Size in bytes - 4 */
struct fs5_image_layout_flash_config_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - flash divider to configure on early boot */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t flash_div;
	/* Description - flash sample in  to configure on early boot */
	/* 0x0.8 - 0x0.12 */
	/* access: RW */
	u_int8_t flash_sample_in;
	/* Description - flash sample out to configure on early boot */
	/* 0x0.13 - 0x0.17 */
	/* access: RW */
	u_int8_t flash_sample_out;
};

/* Description -   */
/* Size in bytes - 3072 */
struct fs5_image_layout_reserved_padding_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xc00.23 */
	/* access: RW */
	u_int8_t u8_dummy[3072];
};

/* Description -   */
/* Size in bytes - 2832 */
union fs5_image_layout_signatures {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x17c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_rsa3k_signature_arr u8_rsa3k_signature;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa256_signature ecdsa256_signature;
	/* Description -  */
	/* 0x0.0 - 0x84.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa521_signature ecdsa521_signature;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ed25519_signature ed25519_signature;
	/* Description -  */
	/* 0x0.0 - 0xb0c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_xmss_signature_arr u8_xmss_signature;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_hmac_sha2_256_tag_arr u8_hmac_sha2_256_tag;
};

/* Description -   */
/* Size in bytes - 384 */
union fs5_image_layout_signatures_v2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x17c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_rsa3k_signature_arr u8_rsa3k_signature;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa256_signature ecdsa256_signature;
	/* Description -  */
	/* 0x0.0 - 0x84.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa521_signature ecdsa521_signature;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ed25519_signature ed25519_signature;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_hmac_sha2_256_tag_arr u8_hmac_sha2_256_tag;
};

/* Description -   */
/* Size in bytes - 64 */
struct fs5_image_layout_u8_digest {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	u_int32_t digest[16];
};

/* Description -   */
/* Size in bytes - 32 */
struct fs5_image_layout_u8_ed25519_pub_param_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_dummy[32];
};

/* Description -   */
/* Size in bytes - 1620 */
struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x654.23 */
	/* access: RW */
	u_int8_t u8_dummy[1620];
};

/* Description -   */
/* Size in bytes - 1740 */
struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x6cc.23 */
	/* access: RW */
	u_int8_t u8_dummy[1740];
};

/* Description -   */
/* Size in bytes - 2668 */
struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xa6c.23 */
	/* access: RW */
	u_int8_t u8_dummy[2668];
};

/* Description -   */
/* Size in bytes - 2828 */
struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xb0c.23 */
	/* access: RW */
	u_int8_t u8_dummy[2828];
};

/* Description -   */
/* Size in bytes - 12 */
struct fs5_image_layout_u8_res {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xc.23 */
	/* access: RW */
	u_int8_t u8_dummy[12];
};

/* Description -   */
/* Size in bytes - 64 */
struct fs5_image_layout_u8_xmss_pub_param_arr {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x40.23 */
	/* access: RW */
	u_int8_t u8_dummy[64];
};

/* Description -   */
/* Size in bytes - 160 */
struct fs5_image_layout_bch_stage2_component {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - served for PSC use,indicate component type */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_binary_magic[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t u32_binary_len;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t u32_load_dest;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t u32_entry_point;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_ver ver;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t u32_start_page;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t u32_start_block;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_flags_bch_stage2_comp flags;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	/* access: RW */
	u_int32_t u32_binary_len_auth;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x2c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_res u8_res;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x5c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_encryption_params enc_params;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x9c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
};

/* Description -   */
/* Size in bytes - 384 */
union fs5_image_layout_crypto_public_crypto_params {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x180.23 */
	/* access: RW */
	struct fs5_image_layout_crypto_rsa3k_pub_params rsa3k_pub_params;
	/* Description -  */
	/* 0x0.24 - 0x40.23 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa256_pub_params ecdsa256_pub_params;
	/* Description -  */
	/* 0x0.24 - 0x88.23 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa521_pub_params ecdsa521_pub_params;
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	struct fs5_image_layout_u8_ed25519_pub_param_arr u8_ed25519_pub_param;
	/* Description -  */
	/* 0x0.24 - 0x40.23 */
	/* access: RW */
	struct fs5_image_layout_u8_xmss_pub_param_arr u8_xmss_pub_param;
};

/* Description -   */
/* Size in bytes - 2896 */
struct fs5_image_layout_crypto_signatures {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0xb4c.31 */
	/* access: RW */
	union fs5_image_layout_signatures signatures;
};

/* Description -   */
/* Size in bytes - 448 */
struct fs5_image_layout_crypto_signatures_v2 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x1bc.31 */
	/* access: RW */
	union fs5_image_layout_signatures_v2 signatures;
};

/* Description -  HW pointer entry */
/* Size in bytes - 8 */
struct fs5_image_layout_hw_pointer_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - pointer */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t ptr;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - crc16 as calculated by HW */
	/* 0x4.0 - 0x4.15 */
	/* access: RW */
	u_int16_t crc;
};

/* Description -   */
/* Size in bytes - 3072 */
union fs5_image_layout_pqc_signatures {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x650.31 */
	/* access: RW */
	struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr u8_lms_sha192_h15_w4_signature;
	/* Description -  */
	/* 0x0.0 - 0x6c8.31 */
	/* access: RW */
	struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr u8_lms_sha192_h20_w4_signature;
	/* Description -  */
	/* 0x0.0 - 0xa68.31 */
	/* access: RW */
	struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr u8_lms_sha256_h15_w4_signature;
	/* Description -  */
	/* 0x0.0 - 0xb08.31 */
	/* access: RW */
	struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr u8_lms_sha256_h20_w4_signature;
	/* Description -  */
	/* 0x0.0 - 0xbfc.31 */
	/* access: RW */
	struct fs5_image_layout_reserved_padding_arr reserved_padding;
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_u8_derivation_label_check {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	/* access: RW */
	u_int8_t u8_dummy[16];
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_u8_ecid {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	/* access: RW */
	u_int8_t u8_dummy[16];
};

/* Description -   */
/* Size in bytes - 48 */
struct fs5_image_layout_u8_sha2_384_digest {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	u_int32_t digest[12];
};


/* Description -   */
/* Size in bytes - 672 */
struct fs5_image_layout_u8_gen_padding {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x2a0.23 */
	/* access: RW */
	u_int8_t u8_dummy[672];
};

/* Description -   */
/* Size in bytes - 48 */
struct fs5_image_layout_u8_gen_padding_pqc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x30.23 */
	/* access: RW */
	u_int8_t u8_dummy[48];
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_u8_salt {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x10.23 */
	/* access: RW */
	u_int8_t u8_dummy[16];
};

/* Description -   */
/* Size in bytes - 32 */
struct fs5_image_layout_u8_sec_provision_derivation_string {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x20.23 */
	/* access: RW */
	u_int8_t u8_dummy[32];
};

/* Description -   */
/* Size in bytes - 144 */
struct fs5_image_layout_u8_stage1_component {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - served for PSC use,indicate component type */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_binary_magic[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - length[bytes] */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t u32_binary_len;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - the destination of the component to be copied to */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t u32_load_dest;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - the entry_point (absolute value) to start (jump address) */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t u32_entry_point;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_ver ver;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description -  */
	/* 0x14.24 - 0x1c.23 */
	/* access: RW */
	u_int8_t u8_res[8];
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_bch_boot_component_flags flags;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x4c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_encryption_params enc_params;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x8c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
};

/* Description -   */
/* Size in bytes - 1068 */
struct fs5_image_layout_u8_stage1_res {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Reserved for PSC use */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t reserved;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Offset relative to load address of the starting location of the HASH table (for NCORE.FMC use) */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t hash_offset;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Version of PSC.BL1 to be bind with this NCORE.FMC version (will be compared to BL1 version as specified in PSC.BL1.BCH) */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t BL1_bind_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Version of PSC.FW to be bind with this NCORE.FMC version (will be compared to FW version as specified in PSC.FW.BCH) */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	u_int32_t FW_bind_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Reserved for PSC use */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t BL1_updt;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Reserved for PSC use */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t FW_updt;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Reserved for PSC use */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RW */
	u_int32_t NCORE_updt;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - flash parameters configuration on early boot */
	/* 0x20.0 - 0x20.31 */
	/* access: RW */
	struct fs5_image_layout_flash_config_params flash_config_params;
};

/* Description -   */
/* Size in bytes - 384 */
struct fs5_image_layout_u8_stage1_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x180.23 */
	/* access: RW */
	u_int8_t u8_dummy[384];
};

/* Description -   */
/* Size in bytes - 1036 */
struct fs5_image_layout_u8_stage2_padding {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x40c.23 */
	/* access: RW */
	u_int8_t u8_dummy[1036];
};

/* Description -   */
/* Size in bytes - 12 */
struct fs5_image_layout_u8_unsigned_padding {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0xc.23 */
	/* access: RW */
	u_int8_t u8_dummy[12];
};

/* Description -  BCH - boot component header */
/* Size in bytes - 8192 */
struct fs5_image_layout_boot_component_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_header_magic[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x40.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - align to AES blocksize */
	/* 0x44.0 - 0x4c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_unsigned_padding u8_unsigned_padding;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0xb9c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_signatures stage2_signature;
/*---------------- DWORD[744] (Offset 0xba0) ----------------*/
	/* Description -  */
	/* 0xba0.0 - 0xd1c.31 */
	/* access: RW */
	union fs5_image_layout_crypto_public_crypto_params pcp;
/*---------------- DWORD[840] (Offset 0xd20) ----------------*/
	/* Description -  */
	/* 0xd20.0 - 0xfbc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_gen_padding u8_gen_padding;
/*---------------- DWORD[1008] (Offset 0xfc0) ----------------*/
	/* Description -  */
	/* 0xfc0.0 - 0xfcc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_salt u8_salt2;
/*---------------- DWORD[1012] (Offset 0xfd0) ----------------*/
	/* Description -  */
	/* 0xfd0.0 - 0xfdc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_ecid2;
/*---------------- DWORD[1016] (Offset 0xfe0) ----------------*/
	/* Description - Number of binary in this group */
	/* 0xfe0.0 - 0xfe0.31 */
	/* access: RW */
	u_int32_t u32_num_binaries2;
/*---------------- DWORD[1017] (Offset 0xfe4) ----------------*/
	/* Description -  */
	/* 0xfe4.0 - 0x13ec.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage2_padding u8_stage2_padding;
/*---------------- DWORD[1276] (Offset 0x13f0) ----------------*/
	/* Description -  */
	/* 0x13f0.0 - 0x13fc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_derivation_label_check u8_stage2_derivation_label_check;
/*---------------- DWORD[1280] (Offset 0x1400) ----------------*/
	/* Description -  */
	/* 0x1400.0 - 0x18fc.31 */
	/* access: RW */
	struct fs5_image_layout_bch_stage2_component stage2_components[8];
/*---------------- DWORD[1600] (Offset 0x1900) ----------------*/
	/* Description -  */
	/* 0x1900.0 - 0x1a7c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_signature u8_stage1_signature;
/*---------------- DWORD[1696] (Offset 0x1a80) ----------------*/
	/* Description -  */
	/* 0x1a80.0 - 0x1a8c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_salt u8_salt1;
/*---------------- DWORD[1700] (Offset 0x1a90) ----------------*/
	/* Description -  */
	/* 0x1a90.0 - 0x1a9c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_ecid1;
/*---------------- DWORD[1704] (Offset 0x1aa0) ----------------*/
	/* Description -  */
	/* 0x1aa0.0 - 0x1aa0.31 */
	/* access: RW */
	u_int32_t u32_num_binaries1;
/*---------------- DWORD[1705] (Offset 0x1aa4) ----------------*/
	/* Description -  */
	/* 0x1aa4.0 - 0x1ecc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_res u8_stage1_res;
/*---------------- DWORD[1972] (Offset 0x1ed0) ----------------*/
	/* Description -  */
	/* 0x1ed0.0 - 0x1edc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_derivation_label_check u8_stage1_derivation_label_check;
/*---------------- DWORD[1976] (Offset 0x1ee0) ----------------*/
	/* Description -  */
	/* 0x1ee0.0 - 0x1ffc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_component stage1_components[2];
};


/* Description -   */
/* Size in bytes - 96 */
struct fs5_image_layout_partition_table_entry {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - SOC-family specific identifier for each partition. */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t partition_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - NULL-terminated list of ASCII characters describing the name of the partition */
	/* 0x4.24 - 0x28.23 */
	/* access: RW */
	u_int8_t partition_name[36];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Identifier for the type of flash/storage device */
	/* 0x28.0 - 0x28.31 */
	/* access: RW */
	u_int32_t device_id;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Instance of the flash/storage controller. */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RW */
	u_int32_t device_instance;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Chip-select of the flash from the same controller (applicable to QSPI) */
	/* 0x30.0 - 0x30.31 */
	/* access: RW */
	u_int32_t device_chipselect;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description -  */
	/* 0x34.0 - 0x34.31 */
	/* access: RW */
	u_int32_t reserved;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Offset (in bytes) of the start of the partition in the flash/storage device */
	/* 0x38.0 - 0x3c.31 */
	/* access: RW */
	u_int32_t start_address[2];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Size of the partition in bytes */
	/* 0x40.0 - 0x44.31 */
	/* access: RW */
	u_int32_t partition_size[2];
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Bit-field describing the attributes that describe the partition */
	/* 0x48.0 - 0x4c.31 */
	/* access: RW */
	u_int32_t partition_attr[2];
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.24 - 0x60.23 */
	/* access: RW */
	u_int8_t reserved1[16];
};


/* Description -   */
/* Size in bytes - 112 */
struct fs5_image_layout_partition_table_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Magic ID */
	/* 0x0.24 - 0x8.23 */
	/* access: RW */
	u_int8_t u8_magic_patttern[8];
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Version of the NVPT */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t version;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Size of 1 partition table entry (96) */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t entry_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of valid entries in the partition table */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	u_int32_t num_entires;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Maximum number of entries in the partition table */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t max_entires;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.24 - 0x40.23 */
	/* access: RW */
	u_int8_t reserved[40];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - SHA384 hash of the partition table */
	/* 0x40.0 - 0x6c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_sha2_384_digest sha384_hash;
};

/* Description -   */
/* Size in bytes - 4 */
struct fs5_image_layout_csh_component_dependency_list {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PLDM/CSH ID */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t component_id;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t min_major_version;
	/* Description -  */
	/* 0x0.24 - 0x0.31 */
	/* access: RW */
	u_int8_t min_minor_version;
};


/* Description -   */
/* Size in bytes - 144 */
struct fs5_image_layout_binary_section_metadata {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_magic_id[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_ver version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the binary */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t bin_length;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Offset of the binary within flash partition */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t flash_offset;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Optional destination of the binary to be copied to */
	/* 0x10.0 - 0x14.31 */
	/* access: RW */
	u_int32_t load_dest[2];
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Optional entry point of the binary to start */
	/* 0x18.0 - 0x1c.31 */
	/* access: RW */
	u_int32_t entry_point[2];
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Binary-specific encryption parameters */
	/* 0x30.0 - 0x5c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_encryption_params encryption_params;
	/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - SHA2-384 digest of binary */
	/* 0x60.0 - 0x8c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_sha2_384_digest bin_digest;
};

/* Description -   */
/* Size in bytes - 16 */
struct fs5_image_layout_csh_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_header_magic[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This is index to PSC-BL NV public key in ROM */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t u8_nv_pub_key_idx;
};

/* Description -   */
/* Size in bytes - 256 */
struct fs5_image_layout_csh_metadata {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PLDM/CSH ID */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t component_id;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	/* access: RW */
	u_int16_t reserved;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_ver version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x24.31 */
	/* access: RW */
	struct fs5_image_layout_csh_component_dependency_list dependency_list[8];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	/* access: RW */
	u_int32_t fw_lifecycle;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x68.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid ecid[4];
/*---------------- DWORD[27] (Offset 0x6c) ----------------*/
	/* Description -  */
	/* 0x6c.0 - 0x6c.23 */
	/* access: RW */
	u_int32_t reserved1;
	/* Description - Number of binaries in the component. I.e. number of binary metadata objects */
	/* 0x6c.24 - 0x6c.31 */
	/* access: RW */
	u_int8_t num_of_binaries;
	/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description - SHA2-384 of Binary Metadata List */
	/* 0x70.0 - 0x9c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_sha2_384_digest binaries_list_digest;
};

/* Description -   */
/* Size in bytes - 1840 */
struct fs5_image_layout_csh_signature {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_ecdsa384_signature ecdsa_signature;
/*---------------- DWORD[459] (Offset 0x72c) ----------------*/
	/* Description -  */
	/* 0x72c.0 - 0x72c.31 */
	/* access: RW */
	u_int32_t reserved;
};

/* Description -  CSH - component signature header */
/* Size in bytes - 8560 */
struct fs5_image_layout_component_signature_header {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct fs5_image_layout_csh_header header;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x73c.31 */
	/* access: RW */
	struct fs5_image_layout_csh_signature nv_signature;
/*---------------- DWORD[464] (Offset 0x740) ----------------*/
	/* Description -  */
	/* 0x740.0 - 0xe6c.31 */
	/* access: RW */
	struct fs5_image_layout_csh_signature oem_signature;
/*---------------- DWORD[924] (Offset 0xe70) ----------------*/
	/* Description -  */
	/* 0xe70.0 - 0xf6c.31 */
	/* access: RW */
	struct fs5_image_layout_csh_metadata metadata;
/*---------------- DWORD[988] (Offset 0xf70) ----------------*/
	/* Description -  */
	/* 0xf70.0 - 0x216c.31 */
	/* access: RW */
	struct fs5_image_layout_binary_section_metadata binaries[32];
};

/* Description -  BCH - boot component header */
/* Size in bytes - 8192 */
struct fs5_image_layout_boot_component_header_pqc {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.24 - 0x4.23 */
	/* access: RW */
	u_int8_t u8_header_magic[4];
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x40.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - align to AES blocksize */
	/* 0x44.0 - 0x4c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_unsigned_padding u8_unsigned_padding;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x20c.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_signatures_v2 stage2_signature;
/*---------------- DWORD[132] (Offset 0x210) ----------------*/
	/* Description -  */
	/* 0x210.0 - 0x38c.31 */
	/* access: RW */
	union fs5_image_layout_crypto_public_crypto_params pcp;
/*---------------- DWORD[228] (Offset 0x390) ----------------*/
	/* Description -  */
	/* 0x390.0 - 0x3bc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_gen_padding_pqc u8_gen_padding;
/*---------------- DWORD[240] (Offset 0x3c0) ----------------*/
	/* Description -  */
	/* 0x3c0.0 - 0x3cc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_salt u8_salt2;
/*---------------- DWORD[244] (Offset 0x3d0) ----------------*/
	/* Description -  */
	/* 0x3d0.0 - 0x3dc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_ecid2;
/*---------------- DWORD[248] (Offset 0x3e0) ----------------*/
	/* Description - Number of binary in this group */
	/* 0x3e0.0 - 0x3e0.31 */
	/* access: RW */
	u_int32_t u32_num_binaries2;
/*---------------- DWORD[249] (Offset 0x3e4) ----------------*/
	/* Description -  */
	/* 0x3e4.0 - 0x7ec.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage2_padding u8_stage2_padding;
/*---------------- DWORD[508] (Offset 0x7f0) ----------------*/
	/* Description -  */
	/* 0x7f0.0 - 0x7fc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_derivation_label_check u8_stage2_derivation_label_check;
/*---------------- DWORD[512] (Offset 0x800) ----------------*/
	/* Description -  */
	/* 0x800.0 - 0xcfc.31 */
	/* access: RW */
	struct fs5_image_layout_bch_stage2_component stage2_components[8];
/*---------------- DWORD[832] (Offset 0xd00) ----------------*/
	/* Description -  */
	/* 0xd00.0 - 0xe7c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_signature u8_stage1_signature;
/*---------------- DWORD[928] (Offset 0xe80) ----------------*/
	/* Description -  */
	/* 0xe80.0 - 0x1a7c.31 */
	/* access: RW */
	union fs5_image_layout_pqc_signatures u8_stage1_pqc_signature;
/*---------------- DWORD[1696] (Offset 0x1a80) ----------------*/
	/* Description -  */
	/* 0x1a80.0 - 0x1a8c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_salt u8_salt1;
/*---------------- DWORD[1700] (Offset 0x1a90) ----------------*/
	/* Description -  */
	/* 0x1a90.0 - 0x1a9c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_ecid1;
/*---------------- DWORD[1704] (Offset 0x1aa0) ----------------*/
	/* Description -  */
	/* 0x1aa0.0 - 0x1aa0.31 */
	/* access: RW */
	u_int32_t u32_num_binaries1;
/*---------------- DWORD[1705] (Offset 0x1aa4) ----------------*/
	/* Description -  */
	/* 0x1aa4.0 - 0x1ecc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_res u8_stage1_res;
/*---------------- DWORD[1972] (Offset 0x1ed0) ----------------*/
	/* Description -  */
	/* 0x1ed0.0 - 0x1edc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_derivation_label_check u8_stage1_derivation_label_check;
/*---------------- DWORD[1976] (Offset 0x1ee0) ----------------*/
	/* Description -  */
	/* 0x1ee0.0 - 0x1ffc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_stage1_component stage1_components[2];
};

/* Description -  BCT - boot component table */
/* Size in bytes - 8192 */
struct fs5_image_layout_boot_component_table {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t u8_header_magic;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x40.31 */
	/* access: RW */
	struct fs5_image_layout_u8_digest u8_digest;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description -  */
	/* 0x44.0 - 0x1c0.31 */
	/* access: RW */
	union fs5_image_layout_crypto_public_crypto_params pcp;
/*---------------- DWORD[113] (Offset 0x1c4) ----------------*/
	/* Description -  */
	/* 0x1c4.0 - 0xd10.31 */
	/* access: RW */
	struct fs5_image_layout_crypto_signatures signature;
/*---------------- DWORD[1152] (Offset 0x1200) ----------------*/
	/* Description -  */
	/* 0x1200.0 - 0x120c.31 */
	/* access: RW */
	struct fs5_image_layout_u8_salt u8_salt1;
/*---------------- DWORD[1156] (Offset 0x1210) ----------------*/
	/* Description -  */
	/* 0x1210.0 - 0x1210.31 */
	/* access: RW */
	u_int32_t u8_header_magic_signed;
/*---------------- DWORD[1170] (Offset 0x1248) ----------------*/
	/* Description -  */
	/* 0x1248.0 - 0x1248.31 */
	/* access: RW */
	u_int32_t u8_bch_info_start_block;
/*---------------- DWORD[1171] (Offset 0x124c) ----------------*/
	/* Description -  */
	/* 0x124c.0 - 0x124c.31 */
	/* access: RW */
	u_int32_t u8_bch_info_start_page;
/*---------------- DWORD[1218] (Offset 0x1308) ----------------*/
	/* Description -  */
	/* 0x1308.0 - 0x1308.31 */
	/* access: RW */
	u_int32_t ver;
/*---------------- DWORD[1640] (Offset 0x19a0) ----------------*/
	/* Description -  */
	/* 0x19a0.0 - 0x19ac.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_ecid;
/*---------------- DWORD[1655] (Offset 0x19dc) ----------------*/
	/* Description -  */
	/* 0x19dc.0 - 0x19dc.31 */
	/* access: RW */
	u_int32_t u8_num_boot_chains;
/*---------------- DWORD[1660] (Offset 0x19f0) ----------------*/
	/* Description -  */
	/* 0x19f0.0 - 0x19fc.31 */
	/* access: RW */
	struct fs5_image_layout_u8_ecid u8_fskp_select;
/*---------------- DWORD[1664] (Offset 0x1a00) ----------------*/
	/* Description -  */
	/* 0x1a00.0 - 0x1a00.31 */
	/* access: RW */
	u_int32_t u8_bf_bl_all_bits;
/*---------------- DWORD[1770] (Offset 0x1ba8) ----------------*/
	/* Description -  */
	/* 0x1ba8.8 - 0x1bc8.7 */
	/* access: RW */
	struct fs5_image_layout_u8_sec_provision_derivation_string u8_sec_provision_derivation_string1;
/*---------------- DWORD[1778] (Offset 0x1bc8) ----------------*/
	/* Description -  */
	/* 0x1bc8.8 - 0x1be8.7 */
	/* access: RW */
	struct fs5_image_layout_u8_sec_provision_derivation_string u8_sec_provision_derivation_string2;
};

/* Description -  HW pointers */
/* Size in bytes - 128 */
struct fs5_image_layout_hw_pointers_gilboa {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry psc_bct_pointer;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0xc.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry boot2_ptr;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x14.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry toc_ptr;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x1c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry tools_ptr;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x24.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_bch_pointer;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x2c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry psc_bl1_pointer;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description -  */
	/* 0x30.0 - 0x34.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry ncore_bch_pointer;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description -  */
	/* 0x38.0 - 0x3c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry reserved;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description -  */
	/* 0x40.0 - 0x44.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry psc_fw_bch_pointer;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description -  */
	/* 0x48.0 - 0x4c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry psc_fw_pointer;
/*---------------- DWORD[20] (Offset 0x50) ----------------*/
	/* Description -  */
	/* 0x50.0 - 0x54.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry image_info_section_pointer;
/*---------------- DWORD[22] (Offset 0x58) ----------------*/
	/* Description -  */
	/* 0x58.0 - 0x5c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry image_signature_pointer;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x64.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry public_key_pointer;
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description -  */
	/* 0x68.0 - 0x6c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry fw_security_version_pointer;
/*---------------- DWORD[28] (Offset 0x70) ----------------*/
	/* Description -  */
	/* 0x70.0 - 0x74.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry gcm_iv_delta_pointer;
/*---------------- DWORD[30] (Offset 0x78) ----------------*/
	/* Description -  */
	/* 0x78.0 - 0x7c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointer_entry ncore_hashes_pointer;
};

/* Description -   */
/* Size in bytes - 8192 */
union fs5_image_layout_fs5_image_layout_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1ffc.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_header_pqc boot_component_header_pqc;
	/* Description -  */
	/* 0x0.0 - 0x1ffc.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_table boot_component_table;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct fs5_image_layout_hw_pointers_gilboa hw_pointers_gilboa;
	/* Description -  */
	/* 0x0.0 - 0x1ffc.31 */
	/* access: RW */
	struct fs5_image_layout_boot_component_header boot_component_header;
	/* Description -  */
	/* 0x0.0 - 0x216c.31 */
	/* access: RW */
	struct fs5_image_layout_component_signature_header component_signature_header;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct fs5_image_layout_partition_table_entry partition_table_entry;
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	/* access: RW */
	struct fs5_image_layout_partition_table_header partition_table_header;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* crypto_ecdsa256_signature */
void fs5_image_layout_crypto_ecdsa256_signature_pack(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa256_signature_unpack(struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa256_signature_print(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ecdsa256_signature_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ECDSA256_SIGNATURE_SIZE    (0x40)
void fs5_image_layout_crypto_ecdsa256_signature_dump(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, FILE *fd);
/* crypto_ecdsa384_signature */
void fs5_image_layout_crypto_ecdsa384_signature_pack(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa384_signature_unpack(struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa384_signature_print(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ecdsa384_signature_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ECDSA384_SIGNATURE_SIZE    (0x60)
void fs5_image_layout_crypto_ecdsa384_signature_dump(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, FILE *fd);
/* crypto_ecdsa521_signature */
void fs5_image_layout_crypto_ecdsa521_signature_pack(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa521_signature_unpack(struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa521_signature_print(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ecdsa521_signature_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ECDSA521_SIGNATURE_SIZE    (0x88)
void fs5_image_layout_crypto_ecdsa521_signature_dump(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, FILE *fd);
/* crypto_ed25519_signature */
void fs5_image_layout_crypto_ed25519_signature_pack(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ed25519_signature_unpack(struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ed25519_signature_print(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ed25519_signature_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ED25519_SIGNATURE_SIZE    (0x40)
void fs5_image_layout_crypto_ed25519_signature_dump(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, FILE *fd);
/* u8_auth_tag */
void fs5_image_layout_u8_auth_tag_pack(const struct fs5_image_layout_u8_auth_tag *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_auth_tag_unpack(struct fs5_image_layout_u8_auth_tag *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_auth_tag_print(const struct fs5_image_layout_u8_auth_tag *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_auth_tag_size(void);
#define FS5_IMAGE_LAYOUT_U8_AUTH_TAG_SIZE    (0x10)
void fs5_image_layout_u8_auth_tag_dump(const struct fs5_image_layout_u8_auth_tag *ptr_struct, FILE *fd);
/* u8_encryption_derivation_string */
void fs5_image_layout_u8_encryption_derivation_string_pack(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_encryption_derivation_string_unpack(struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_encryption_derivation_string_print(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_encryption_derivation_string_size(void);
#define FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE    (0x10)
void fs5_image_layout_u8_encryption_derivation_string_dump(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, FILE *fd);
/* u8_hmac_sha2_256_tag_arr */
void fs5_image_layout_u8_hmac_sha2_256_tag_arr_pack(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_hmac_sha2_256_tag_arr_unpack(struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_hmac_sha2_256_tag_arr_print(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_hmac_sha2_256_tag_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_HMAC_SHA2_256_TAG_ARR_SIZE    (0x20)
void fs5_image_layout_u8_hmac_sha2_256_tag_arr_dump(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, FILE *fd);
/* u8_iv */
void fs5_image_layout_u8_iv_pack(const struct fs5_image_layout_u8_iv *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_iv_unpack(struct fs5_image_layout_u8_iv *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_iv_print(const struct fs5_image_layout_u8_iv *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_iv_size(void);
#define FS5_IMAGE_LAYOUT_U8_IV_SIZE    (0xc)
void fs5_image_layout_u8_iv_dump(const struct fs5_image_layout_u8_iv *ptr_struct, FILE *fd);
/* u8_rsa3k_signature_arr */
void fs5_image_layout_u8_rsa3k_signature_arr_pack(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_rsa3k_signature_arr_unpack(struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_rsa3k_signature_arr_print(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_rsa3k_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_RSA3K_SIGNATURE_ARR_SIZE    (0x180)
void fs5_image_layout_u8_rsa3k_signature_arr_dump(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, FILE *fd);
/* u8_xmss_signature_arr */
void fs5_image_layout_u8_xmss_signature_arr_pack(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_xmss_signature_arr_unpack(struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_xmss_signature_arr_print(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_xmss_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_XMSS_SIGNATURE_ARR_SIZE    (0xb10)
void fs5_image_layout_u8_xmss_signature_arr_dump(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, FILE *fd);
/* bch_boot_component_flags */
void fs5_image_layout_bch_boot_component_flags_pack(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_bch_boot_component_flags_unpack(struct fs5_image_layout_bch_boot_component_flags *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_bch_boot_component_flags_print(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_bch_boot_component_flags_size(void);
#define FS5_IMAGE_LAYOUT_BCH_BOOT_COMPONENT_FLAGS_SIZE    (0x4)
void fs5_image_layout_bch_boot_component_flags_dump(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, FILE *fd);
/* boot_component_ver */
void fs5_image_layout_boot_component_ver_pack(const struct fs5_image_layout_boot_component_ver *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_ver_unpack(struct fs5_image_layout_boot_component_ver *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_ver_print(const struct fs5_image_layout_boot_component_ver *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_ver_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_VER_SIZE    (0x4)
void fs5_image_layout_boot_component_ver_dump(const struct fs5_image_layout_boot_component_ver *ptr_struct, FILE *fd);
/* crypto_ecdsa256_pub_params */
void fs5_image_layout_crypto_ecdsa256_pub_params_pack(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa256_pub_params_unpack(struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa256_pub_params_print(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ecdsa256_pub_params_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ECDSA256_PUB_PARAMS_SIZE    (0x40)
void fs5_image_layout_crypto_ecdsa256_pub_params_dump(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, FILE *fd);
/* crypto_ecdsa521_pub_params */
void fs5_image_layout_crypto_ecdsa521_pub_params_pack(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa521_pub_params_unpack(struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_ecdsa521_pub_params_print(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_ecdsa521_pub_params_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ECDSA521_PUB_PARAMS_SIZE    (0x88)
void fs5_image_layout_crypto_ecdsa521_pub_params_dump(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, FILE *fd);
/* crypto_encryption_params */
void fs5_image_layout_crypto_encryption_params_pack(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_encryption_params_unpack(struct fs5_image_layout_crypto_encryption_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_encryption_params_print(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_encryption_params_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_ENCRYPTION_PARAMS_SIZE    (0x30)
void fs5_image_layout_crypto_encryption_params_dump(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, FILE *fd);
/* crypto_rsa3k_pub_params */
void fs5_image_layout_crypto_rsa3k_pub_params_pack(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_rsa3k_pub_params_unpack(struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_rsa3k_pub_params_print(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_rsa3k_pub_params_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_RSA3K_PUB_PARAMS_SIZE    (0x180)
void fs5_image_layout_crypto_rsa3k_pub_params_dump(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, FILE *fd);
/* flags_bch_stage2_comp */
void fs5_image_layout_flags_bch_stage2_comp_pack(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_flags_bch_stage2_comp_unpack(struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_flags_bch_stage2_comp_print(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_flags_bch_stage2_comp_size(void);
#define FS5_IMAGE_LAYOUT_FLAGS_BCH_STAGE2_COMP_SIZE    (0x4)
void fs5_image_layout_flags_bch_stage2_comp_dump(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, FILE *fd);
/* flash_config_params */
void fs5_image_layout_flash_config_params_pack(const struct fs5_image_layout_flash_config_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_flash_config_params_unpack(struct fs5_image_layout_flash_config_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_flash_config_params_print(const struct fs5_image_layout_flash_config_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_flash_config_params_size(void);
#define FS5_IMAGE_LAYOUT_FLASH_CONFIG_PARAMS_SIZE    (0x4)
void fs5_image_layout_flash_config_params_dump(const struct fs5_image_layout_flash_config_params *ptr_struct, FILE *fd);
/* reserved_padding_arr */
void fs5_image_layout_reserved_padding_arr_pack(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_reserved_padding_arr_unpack(struct fs5_image_layout_reserved_padding_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_reserved_padding_arr_print(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_reserved_padding_arr_size(void);
#define FS5_IMAGE_LAYOUT_RESERVED_PADDING_ARR_SIZE    (0xc00)
void fs5_image_layout_reserved_padding_arr_dump(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, FILE *fd);
/* signatures */
void fs5_image_layout_signatures_pack(const union fs5_image_layout_signatures *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_signatures_unpack(union fs5_image_layout_signatures *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_signatures_print(const union fs5_image_layout_signatures *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_signatures_size(void);
#define FS5_IMAGE_LAYOUT_SIGNATURES_SIZE    (0xb10)
void fs5_image_layout_signatures_dump(const union fs5_image_layout_signatures *ptr_struct, FILE *fd);
/* signatures_v2 */
void fs5_image_layout_signatures_v2_pack(const union fs5_image_layout_signatures_v2 *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_signatures_v2_unpack(union fs5_image_layout_signatures_v2 *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_signatures_v2_print(const union fs5_image_layout_signatures_v2 *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_signatures_v2_size(void);
#define FS5_IMAGE_LAYOUT_SIGNATURES_V2_SIZE    (0x180)
void fs5_image_layout_signatures_v2_dump(const union fs5_image_layout_signatures_v2 *ptr_struct, FILE *fd);
/* u8_digest */
void fs5_image_layout_u8_digest_pack(const struct fs5_image_layout_u8_digest *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_digest_unpack(struct fs5_image_layout_u8_digest *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_digest_print(const struct fs5_image_layout_u8_digest *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_digest_size(void);
#define FS5_IMAGE_LAYOUT_U8_DIGEST_SIZE    (0x40)
void fs5_image_layout_u8_digest_dump(const struct fs5_image_layout_u8_digest *ptr_struct, FILE *fd);
/* u8_ed25519_pub_param_arr */
void fs5_image_layout_u8_ed25519_pub_param_arr_pack(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_ed25519_pub_param_arr_unpack(struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_ed25519_pub_param_arr_print(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_ed25519_pub_param_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_ED25519_PUB_PARAM_ARR_SIZE    (0x20)
void fs5_image_layout_u8_ed25519_pub_param_arr_dump(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, FILE *fd);
/* u8_lms_sha192_h15_w4_signature_arr */
void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_LMS_SHA192_H15_W4_SIGNATURE_ARR_SIZE    (0x654)
void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, FILE *fd);
/* u8_lms_sha192_h20_w4_signature_arr */
void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_LMS_SHA192_H20_W4_SIGNATURE_ARR_SIZE    (0x6cc)
void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, FILE *fd);
/* u8_lms_sha256_h15_w4_signature_arr */
void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_LMS_SHA256_H15_W4_SIGNATURE_ARR_SIZE    (0xa6c)
void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, FILE *fd);
/* u8_lms_sha256_h20_w4_signature_arr */
void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_LMS_SHA256_H20_W4_SIGNATURE_ARR_SIZE    (0xb0c)
void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, FILE *fd);
/* u8_res */
void fs5_image_layout_u8_res_pack(const struct fs5_image_layout_u8_res *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_res_unpack(struct fs5_image_layout_u8_res *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_res_print(const struct fs5_image_layout_u8_res *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_res_size(void);
#define FS5_IMAGE_LAYOUT_U8_RES_SIZE    (0xc)
void fs5_image_layout_u8_res_dump(const struct fs5_image_layout_u8_res *ptr_struct, FILE *fd);
/* u8_xmss_pub_param_arr */
void fs5_image_layout_u8_xmss_pub_param_arr_pack(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_xmss_pub_param_arr_unpack(struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_xmss_pub_param_arr_print(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_xmss_pub_param_arr_size(void);
#define FS5_IMAGE_LAYOUT_U8_XMSS_PUB_PARAM_ARR_SIZE    (0x40)
void fs5_image_layout_u8_xmss_pub_param_arr_dump(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, FILE *fd);
/* bch_stage2_component */
void fs5_image_layout_bch_stage2_component_pack(const struct fs5_image_layout_bch_stage2_component *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_bch_stage2_component_unpack(struct fs5_image_layout_bch_stage2_component *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_bch_stage2_component_print(const struct fs5_image_layout_bch_stage2_component *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_bch_stage2_component_size(void);
#define FS5_IMAGE_LAYOUT_BCH_STAGE2_COMPONENT_SIZE    (0xa0)
void fs5_image_layout_bch_stage2_component_dump(const struct fs5_image_layout_bch_stage2_component *ptr_struct, FILE *fd);
/* crypto_public_crypto_params */
void fs5_image_layout_crypto_public_crypto_params_pack(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_public_crypto_params_unpack(union fs5_image_layout_crypto_public_crypto_params *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_public_crypto_params_print(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_public_crypto_params_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_PUBLIC_CRYPTO_PARAMS_SIZE    (0x180)
void fs5_image_layout_crypto_public_crypto_params_dump(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, FILE *fd);
/* crypto_signatures */
void fs5_image_layout_crypto_signatures_pack(const struct fs5_image_layout_crypto_signatures *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_signatures_unpack(struct fs5_image_layout_crypto_signatures *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_signatures_print(const struct fs5_image_layout_crypto_signatures *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_signatures_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_SIGNATURES_SIZE    (0xb50)
void fs5_image_layout_crypto_signatures_dump(const struct fs5_image_layout_crypto_signatures *ptr_struct, FILE *fd);
/* crypto_signatures_v2 */
void fs5_image_layout_crypto_signatures_v2_pack(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_crypto_signatures_v2_unpack(struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_crypto_signatures_v2_print(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_crypto_signatures_v2_size(void);
#define FS5_IMAGE_LAYOUT_CRYPTO_SIGNATURES_V2_SIZE    (0x1c0)
void fs5_image_layout_crypto_signatures_v2_dump(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, FILE *fd);
/* hw_pointer_entry */
void fs5_image_layout_hw_pointer_entry_pack(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_unpack(struct fs5_image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointer_entry_print(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_hw_pointer_entry_size(void);
#define FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE    (0x8)
void fs5_image_layout_hw_pointer_entry_dump(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd);
/* pqc_signatures */
void fs5_image_layout_pqc_signatures_pack(const union fs5_image_layout_pqc_signatures *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_pqc_signatures_unpack(union fs5_image_layout_pqc_signatures *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_pqc_signatures_print(const union fs5_image_layout_pqc_signatures *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_pqc_signatures_size(void);
#define FS5_IMAGE_LAYOUT_PQC_SIGNATURES_SIZE    (0xc00)
void fs5_image_layout_pqc_signatures_dump(const union fs5_image_layout_pqc_signatures *ptr_struct, FILE *fd);
/* u8_derivation_label_check */
void fs5_image_layout_u8_derivation_label_check_pack(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_derivation_label_check_unpack(struct fs5_image_layout_u8_derivation_label_check *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_derivation_label_check_print(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_derivation_label_check_size(void);
#define FS5_IMAGE_LAYOUT_U8_DERIVATION_LABEL_CHECK_SIZE    (0x10)
void fs5_image_layout_u8_derivation_label_check_dump(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, FILE *fd);
/* u8_ecid */
void fs5_image_layout_u8_ecid_pack(const struct fs5_image_layout_u8_ecid *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_ecid_unpack(struct fs5_image_layout_u8_ecid *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_ecid_print(const struct fs5_image_layout_u8_ecid *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_ecid_size(void);
#define FS5_IMAGE_LAYOUT_U8_ECID_SIZE    (0x10)
void fs5_image_layout_u8_ecid_dump(const struct fs5_image_layout_u8_ecid *ptr_struct, FILE *fd);
/* u8_gen_padding */
void fs5_image_layout_u8_gen_padding_pack(const struct fs5_image_layout_u8_gen_padding *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_gen_padding_unpack(struct fs5_image_layout_u8_gen_padding *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_gen_padding_print(const struct fs5_image_layout_u8_gen_padding *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_gen_padding_size(void);
#define FS5_IMAGE_LAYOUT_U8_GEN_PADDING_SIZE    (0x2a0)
void fs5_image_layout_u8_gen_padding_dump(const struct fs5_image_layout_u8_gen_padding *ptr_struct, FILE *fd);
/* u8_gen_padding_pqc */
void fs5_image_layout_u8_gen_padding_pqc_pack(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_gen_padding_pqc_unpack(struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_gen_padding_pqc_print(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_gen_padding_pqc_size(void);
#define FS5_IMAGE_LAYOUT_U8_GEN_PADDING_PQC_SIZE    (0x30)
void fs5_image_layout_u8_gen_padding_pqc_dump(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, FILE *fd);
/* u8_salt */
void fs5_image_layout_u8_salt_pack(const struct fs5_image_layout_u8_salt *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_salt_unpack(struct fs5_image_layout_u8_salt *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_salt_print(const struct fs5_image_layout_u8_salt *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_salt_size(void);
#define FS5_IMAGE_LAYOUT_U8_SALT_SIZE    (0x10)
void fs5_image_layout_u8_salt_dump(const struct fs5_image_layout_u8_salt *ptr_struct, FILE *fd);
/* u8_sec_provision_derivation_string */
void fs5_image_layout_u8_sec_provision_derivation_string_pack(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_sec_provision_derivation_string_unpack(struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_sec_provision_derivation_string_print(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_sec_provision_derivation_string_size(void);
#define FS5_IMAGE_LAYOUT_U8_SEC_PROVISION_DERIVATION_STRING_SIZE    (0x20)
void fs5_image_layout_u8_sec_provision_derivation_string_dump(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd);
/* u8_stage1_component */
void fs5_image_layout_u8_stage1_component_pack(const struct fs5_image_layout_u8_stage1_component *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_component_unpack(struct fs5_image_layout_u8_stage1_component *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_component_print(const struct fs5_image_layout_u8_stage1_component *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_stage1_component_size(void);
#define FS5_IMAGE_LAYOUT_U8_STAGE1_COMPONENT_SIZE    (0x90)
void fs5_image_layout_u8_stage1_component_dump(const struct fs5_image_layout_u8_stage1_component *ptr_struct, FILE *fd);
/* u8_stage1_res */
void fs5_image_layout_u8_stage1_res_pack(const struct fs5_image_layout_u8_stage1_res *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_res_unpack(struct fs5_image_layout_u8_stage1_res *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_res_print(const struct fs5_image_layout_u8_stage1_res *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_stage1_res_size(void);
#define FS5_IMAGE_LAYOUT_U8_STAGE1_RES_SIZE    (0x42c)
void fs5_image_layout_u8_stage1_res_dump(const struct fs5_image_layout_u8_stage1_res *ptr_struct, FILE *fd);
/* u8_stage1_signature */
void fs5_image_layout_u8_stage1_signature_pack(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_signature_unpack(struct fs5_image_layout_u8_stage1_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage1_signature_print(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_stage1_signature_size(void);
#define FS5_IMAGE_LAYOUT_U8_STAGE1_SIGNATURE_SIZE    (0x180)
void fs5_image_layout_u8_stage1_signature_dump(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, FILE *fd);
/* u8_stage2_padding */
void fs5_image_layout_u8_stage2_padding_pack(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage2_padding_unpack(struct fs5_image_layout_u8_stage2_padding *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_stage2_padding_print(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_stage2_padding_size(void);
#define FS5_IMAGE_LAYOUT_U8_STAGE2_PADDING_SIZE    (0x40c)
void fs5_image_layout_u8_stage2_padding_dump(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, FILE *fd);
/* u8_unsigned_padding */
void fs5_image_layout_u8_unsigned_padding_pack(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_unsigned_padding_unpack(struct fs5_image_layout_u8_unsigned_padding *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_unsigned_padding_print(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_unsigned_padding_size(void);
#define FS5_IMAGE_LAYOUT_U8_UNSIGNED_PADDING_SIZE    (0xc)
void fs5_image_layout_u8_unsigned_padding_dump(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, FILE *fd);
/* u8_sec_provision_derivation_string */
void fs5_image_layout_u8_sec_provision_derivation_string_pack(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_sec_provision_derivation_string_unpack(struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_sec_provision_derivation_string_print(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_sec_provision_derivation_string_size(void);
#define FS5_IMAGE_LAYOUT_U8_SEC_PROVISION_DERIVATION_STRING_SIZE    (0x20)
void fs5_image_layout_u8_sec_provision_derivation_string_dump(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd);
/* boot_component_table */
void fs5_image_layout_boot_component_table_pack(const struct fs5_image_layout_boot_component_table *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_table_unpack(struct fs5_image_layout_boot_component_table *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_table_print(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_table_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_TABLE_SIZE    (0x2000)
void fs5_image_layout_boot_component_table_dump(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd);
/* partition_table_entry */
void fs5_image_layout_partition_table_entry_pack(const struct fs5_image_layout_partition_table_entry *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_partition_table_entry_unpack(struct fs5_image_layout_partition_table_entry *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_partition_table_entry_print(const struct fs5_image_layout_partition_table_entry *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_partition_table_entry_size(void);
#define FS5_IMAGE_LAYOUT_PARTITION_TABLE_ENTRY_SIZE    (0x60)
void fs5_image_layout_partition_table_entry_dump(const struct fs5_image_layout_partition_table_entry *ptr_struct, FILE *fd);
/* partition_table_header */
void fs5_image_layout_partition_table_header_pack(const struct fs5_image_layout_partition_table_header *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_partition_table_header_unpack(struct fs5_image_layout_partition_table_header *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_partition_table_header_print(const struct fs5_image_layout_partition_table_header *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_partition_table_header_size(void);
#define FS5_IMAGE_LAYOUT_PARTITION_TABLE_HEADER_SIZE    (0x70)
void fs5_image_layout_partition_table_header_dump(const struct fs5_image_layout_partition_table_header *ptr_struct, FILE *fd);
/* csh_component_dependency_list */
void fs5_image_layout_csh_component_dependency_list_pack(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_csh_component_dependency_list_unpack(struct fs5_image_layout_csh_component_dependency_list *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_csh_component_dependency_list_print(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_csh_component_dependency_list_size(void);
#define FS5_IMAGE_LAYOUT_CSH_COMPONENT_DEPENDENCY_LIST_SIZE    (0x4)
void fs5_image_layout_csh_component_dependency_list_dump(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, FILE *fd);
/* u8_sha2_384_digest */
void fs5_image_layout_u8_sha2_384_digest_pack(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_u8_sha2_384_digest_unpack(struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_u8_sha2_384_digest_print(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_u8_sha2_384_digest_size(void);
#define FS5_IMAGE_LAYOUT_U8_SHA2_384_DIGEST_SIZE    (0x30)
void fs5_image_layout_u8_sha2_384_digest_dump(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, FILE *fd);
/* binary_section_metadata */
void fs5_image_layout_binary_section_metadata_pack(const struct fs5_image_layout_binary_section_metadata *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_binary_section_metadata_unpack(struct fs5_image_layout_binary_section_metadata *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_binary_section_metadata_print(const struct fs5_image_layout_binary_section_metadata *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_binary_section_metadata_size(void);
#define FS5_IMAGE_LAYOUT_BINARY_SECTION_METADATA_SIZE    (0x90)
void fs5_image_layout_binary_section_metadata_dump(const struct fs5_image_layout_binary_section_metadata *ptr_struct, FILE *fd);
/* csh_header */
void fs5_image_layout_csh_header_pack(const struct fs5_image_layout_csh_header *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_csh_header_unpack(struct fs5_image_layout_csh_header *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_csh_header_print(const struct fs5_image_layout_csh_header *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_csh_header_size(void);
#define FS5_IMAGE_LAYOUT_CSH_HEADER_SIZE    (0x10)
void fs5_image_layout_csh_header_dump(const struct fs5_image_layout_csh_header *ptr_struct, FILE *fd);
/* csh_metadata */
void fs5_image_layout_csh_metadata_pack(const struct fs5_image_layout_csh_metadata *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_csh_metadata_unpack(struct fs5_image_layout_csh_metadata *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_csh_metadata_print(const struct fs5_image_layout_csh_metadata *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_csh_metadata_size(void);
#define FS5_IMAGE_LAYOUT_CSH_METADATA_SIZE    (0x100)
void fs5_image_layout_csh_metadata_dump(const struct fs5_image_layout_csh_metadata *ptr_struct, FILE *fd);
/* csh_signature */
void fs5_image_layout_csh_signature_pack(const struct fs5_image_layout_csh_signature *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_csh_signature_unpack(struct fs5_image_layout_csh_signature *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_csh_signature_print(const struct fs5_image_layout_csh_signature *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_csh_signature_size(void);
#define FS5_IMAGE_LAYOUT_CSH_SIGNATURE_SIZE    (0x730)
void fs5_image_layout_csh_signature_dump(const struct fs5_image_layout_csh_signature *ptr_struct, FILE *fd);
/* component_signature_header */
void fs5_image_layout_component_signature_header_pack(const struct fs5_image_layout_component_signature_header *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_component_signature_header_unpack(struct fs5_image_layout_component_signature_header *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_component_signature_header_print(const struct fs5_image_layout_component_signature_header *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_component_signature_header_size(void);
#define FS5_IMAGE_LAYOUT_COMPONENT_SIGNATURE_HEADER_SIZE    (0x2170)
void fs5_image_layout_component_signature_header_dump(const struct fs5_image_layout_component_signature_header *ptr_struct, FILE *fd);
/* boot_component_header */
void fs5_image_layout_boot_component_header_pack(const struct fs5_image_layout_boot_component_header *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_unpack(struct fs5_image_layout_boot_component_header *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_print(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_header_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE    (0x2000)
void fs5_image_layout_boot_component_header_dump(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd);
/* boot_component_header_pqc */
void fs5_image_layout_boot_component_header_pqc_pack(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_pqc_unpack(struct fs5_image_layout_boot_component_header_pqc *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_header_pqc_print(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_header_pqc_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_PQC_SIZE    (0x2000)
void fs5_image_layout_boot_component_header_pqc_dump(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, FILE *fd);
/* boot_component_table */
void fs5_image_layout_boot_component_table_pack(const struct fs5_image_layout_boot_component_table *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_table_unpack(struct fs5_image_layout_boot_component_table *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_boot_component_table_print(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_boot_component_table_size(void);
#define FS5_IMAGE_LAYOUT_BOOT_COMPONENT_TABLE_SIZE    (0x2000)
void fs5_image_layout_boot_component_table_dump(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd);
/* hw_pointers_gilboa */
void fs5_image_layout_hw_pointers_gilboa_pack(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointers_gilboa_unpack(struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_hw_pointers_gilboa_print(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_hw_pointers_gilboa_size(void);
#define FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE    (0x80)
void fs5_image_layout_hw_pointers_gilboa_dump(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd);
/* fs5_image_layout_Nodes */
void fs5_image_layout_fs5_image_layout_Nodes_pack(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff);
void fs5_image_layout_fs5_image_layout_Nodes_unpack(union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void fs5_image_layout_fs5_image_layout_Nodes_print(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int fs5_image_layout_fs5_image_layout_Nodes_size(void);
#define FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE    (0x2000)
void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // FS5_IMAGE_LAYOUT_LAYOUTS_H
