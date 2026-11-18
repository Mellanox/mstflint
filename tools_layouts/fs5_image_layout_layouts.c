/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
         *** This file was generated at "2025-07-29 22:06:43"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/fs5_image_layout/fs5_image_layout.adb --file-prefix fs5_image_layout --prefix fs5_image_layout_ --no-adb-utils
         ***/
#include "fs5_image_layout_layouts.h"

void fs5_image_layout_crypto_ecdsa256_signature_pack(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_s[i]);
	}
}

void fs5_image_layout_crypto_ecdsa256_signature_unpack(struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		ptr_struct->u8_r[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		ptr_struct->u8_s[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ecdsa256_signature_print(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ecdsa256_signature ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_r_%03d            : " UH_FMT "\n", i, ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_s_%03d            : " UH_FMT "\n", i, ptr_struct->u8_s[i]);
	}
}

unsigned int fs5_image_layout_crypto_ecdsa256_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ECDSA256_SIGNATURE_SIZE;
}

void fs5_image_layout_crypto_ecdsa256_signature_dump(const struct fs5_image_layout_crypto_ecdsa256_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ecdsa256_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_ecdsa384_signature_pack(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 48; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 768, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 48; ++i) {
		offset = adb2c_calc_array_field_address(408, 8, i, 768, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_s[i]);
	}
}

void fs5_image_layout_crypto_ecdsa384_signature_unpack(struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 48; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 768, 1);
		ptr_struct->u8_r[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 48; ++i) {
		offset = adb2c_calc_array_field_address(408, 8, i, 768, 1);
		ptr_struct->u8_s[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ecdsa384_signature_print(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ecdsa384_signature ========\n");

	for (i = 0; i < 48; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_r_%03d            : " UH_FMT "\n", i, ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 48; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_s_%03d            : " UH_FMT "\n", i, ptr_struct->u8_s[i]);
	}
}

unsigned int fs5_image_layout_crypto_ecdsa384_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ECDSA384_SIGNATURE_SIZE;
}

void fs5_image_layout_crypto_ecdsa384_signature_dump(const struct fs5_image_layout_crypto_ecdsa384_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ecdsa384_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_ecdsa521_signature_pack(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1088, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(568, 8, i, 1088, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_s[i]);
	}
}

void fs5_image_layout_crypto_ecdsa521_signature_unpack(struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1088, 1);
		ptr_struct->u8_r[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(568, 8, i, 1088, 1);
		ptr_struct->u8_s[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ecdsa521_signature_print(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ecdsa521_signature ========\n");

	for (i = 0; i < 68; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_r_%03d            : " UH_FMT "\n", i, ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 68; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_s_%03d            : " UH_FMT "\n", i, ptr_struct->u8_s[i]);
	}
}

unsigned int fs5_image_layout_crypto_ecdsa521_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ECDSA521_SIGNATURE_SIZE;
}

void fs5_image_layout_crypto_ecdsa521_signature_dump(const struct fs5_image_layout_crypto_ecdsa521_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ecdsa521_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_ed25519_signature_pack(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_s[i]);
	}
}

void fs5_image_layout_crypto_ed25519_signature_unpack(struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		ptr_struct->u8_r[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		ptr_struct->u8_s[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ed25519_signature_print(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ed25519_signature ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_r_%03d            : " UH_FMT "\n", i, ptr_struct->u8_r[i]);
	}
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_s_%03d            : " UH_FMT "\n", i, ptr_struct->u8_s[i]);
	}
}

unsigned int fs5_image_layout_crypto_ed25519_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ED25519_SIGNATURE_SIZE;
}

void fs5_image_layout_crypto_ed25519_signature_dump(const struct fs5_image_layout_crypto_ed25519_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ed25519_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_auth_tag_pack(const struct fs5_image_layout_u8_auth_tag *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_auth_tag_unpack(struct fs5_image_layout_u8_auth_tag *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_auth_tag_print(const struct fs5_image_layout_u8_auth_tag *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_auth_tag ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_auth_tag_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_AUTH_TAG_SIZE;
}

void fs5_image_layout_u8_auth_tag_dump(const struct fs5_image_layout_u8_auth_tag *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_auth_tag_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_encryption_derivation_string_pack(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_encryption_derivation_string_unpack(struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_encryption_derivation_string_print(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_encryption_derivation_string ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_encryption_derivation_string_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_ENCRYPTION_DERIVATION_STRING_SIZE;
}

void fs5_image_layout_u8_encryption_derivation_string_dump(const struct fs5_image_layout_u8_encryption_derivation_string *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_encryption_derivation_string_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_hmac_sha2_256_tag_arr_pack(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_hmac_sha2_256_tag_arr_unpack(struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_hmac_sha2_256_tag_arr_print(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_hmac_sha2_256_tag_arr ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_hmac_sha2_256_tag_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_HMAC_SHA2_256_TAG_ARR_SIZE;
}

void fs5_image_layout_u8_hmac_sha2_256_tag_arr_dump(const struct fs5_image_layout_u8_hmac_sha2_256_tag_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_hmac_sha2_256_tag_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_iv_pack(const struct fs5_image_layout_u8_iv *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_iv_unpack(struct fs5_image_layout_u8_iv *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_iv_print(const struct fs5_image_layout_u8_iv *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_iv ========\n");

	for (i = 0; i < 12; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_iv_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_IV_SIZE;
}

void fs5_image_layout_u8_iv_dump(const struct fs5_image_layout_u8_iv *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_iv_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_rsa3k_signature_arr_pack(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_rsa3k_signature_arr_unpack(struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_rsa3k_signature_arr_print(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_rsa3k_signature_arr ========\n");

	for (i = 0; i < 384; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_rsa3k_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_RSA3K_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_rsa3k_signature_arr_dump(const struct fs5_image_layout_u8_rsa3k_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_rsa3k_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_xmss_signature_arr_pack(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2832; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 22656, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_xmss_signature_arr_unpack(struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2832; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 22656, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_xmss_signature_arr_print(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_xmss_signature_arr ========\n");

	for (i = 0; i < 2832; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_xmss_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_XMSS_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_xmss_signature_arr_dump(const struct fs5_image_layout_u8_xmss_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_xmss_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_bch_boot_component_flags_pack(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 30, (u_int32_t)ptr_struct->res);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_debug);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_encrypted);
}

void fs5_image_layout_bch_boot_component_flags_unpack(struct fs5_image_layout_bch_boot_component_flags *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 2;
	ptr_struct->res = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 30);
	offset = 1;
	ptr_struct->is_debug = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->is_encrypted = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void fs5_image_layout_bch_boot_component_flags_print(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_bch_boot_component_flags ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "res                  : " UH_FMT "\n", ptr_struct->res);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_debug             : " UH_FMT "\n", ptr_struct->is_debug);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_encrypted         : " UH_FMT "\n", ptr_struct->is_encrypted);
}

unsigned int fs5_image_layout_bch_boot_component_flags_size(void)
{
	return FS5_IMAGE_LAYOUT_BCH_BOOT_COMPONENT_FLAGS_SIZE;
}

void fs5_image_layout_bch_boot_component_flags_dump(const struct fs5_image_layout_bch_boot_component_flags *ptr_struct, FILE *fd)
{
	fs5_image_layout_bch_boot_component_flags_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_ver_pack(const struct fs5_image_layout_boot_component_ver *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_ver_major);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_ver_minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_ratchet_level);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_res);
}

void fs5_image_layout_boot_component_ver_unpack(struct fs5_image_layout_boot_component_ver *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->u8_ver_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->u8_ver_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->u8_ratchet_level = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->u8_res = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void fs5_image_layout_boot_component_ver_print(const struct fs5_image_layout_boot_component_ver *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_ver ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ver_major         : " UH_FMT "\n", ptr_struct->u8_ver_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ver_minor         : " UH_FMT "\n", ptr_struct->u8_ver_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ratchet_level     : " UH_FMT "\n", ptr_struct->u8_ratchet_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_res               : " UH_FMT "\n", ptr_struct->u8_res);
}

unsigned int fs5_image_layout_boot_component_ver_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_VER_SIZE;
}

void fs5_image_layout_boot_component_ver_dump(const struct fs5_image_layout_boot_component_ver *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_ver_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_ver_nbu_pack(const struct fs5_image_layout_boot_component_ver_nbu *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ver_minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ratchet_level);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ver_major);
}

void fs5_image_layout_boot_component_ver_nbu_unpack(struct fs5_image_layout_boot_component_ver_nbu *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->ver_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->ratchet_level = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->ver_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void fs5_image_layout_boot_component_ver_nbu_print(const struct fs5_image_layout_boot_component_ver_nbu *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_ver_nbu ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ver_minor            : " UH_FMT "\n", ptr_struct->ver_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ratchet_level        : " UH_FMT "\n", ptr_struct->ratchet_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ver_major            : " UH_FMT "\n", ptr_struct->ver_major);
}

unsigned int fs5_image_layout_boot_component_ver_nbu_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_VER_NBU_SIZE;
}

void fs5_image_layout_boot_component_ver_nbu_dump(const struct fs5_image_layout_boot_component_ver_nbu *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_ver_nbu_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_ecdsa256_pub_params_pack(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_x[i]);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_y[i]);
	}
}

void fs5_image_layout_crypto_ecdsa256_pub_params_unpack(struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		ptr_struct->u8_x[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 512, 1);
		ptr_struct->u8_y[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ecdsa256_pub_params_print(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ecdsa256_pub_params ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_x_%03d            : " UH_FMT "\n", i, ptr_struct->u8_x[i]);
	}
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_y_%03d            : " UH_FMT "\n", i, ptr_struct->u8_y[i]);
	}
}

unsigned int fs5_image_layout_crypto_ecdsa256_pub_params_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ECDSA256_PUB_PARAMS_SIZE;
}

void fs5_image_layout_crypto_ecdsa256_pub_params_dump(const struct fs5_image_layout_crypto_ecdsa256_pub_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ecdsa256_pub_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_ecdsa521_pub_params_pack(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1088, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_x[i]);
	}
	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(568, 8, i, 1088, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_y[i]);
	}
}

void fs5_image_layout_crypto_ecdsa521_pub_params_unpack(struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1088, 1);
		ptr_struct->u8_x[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	for (i = 0; i < 68; ++i) {
		offset = adb2c_calc_array_field_address(568, 8, i, 1088, 1);
		ptr_struct->u8_y[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_ecdsa521_pub_params_print(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_ecdsa521_pub_params ========\n");

	for (i = 0; i < 68; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_x_%03d            : " UH_FMT "\n", i, ptr_struct->u8_x[i]);
	}
	for (i = 0; i < 68; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_y_%03d            : " UH_FMT "\n", i, ptr_struct->u8_y[i]);
	}
}

unsigned int fs5_image_layout_crypto_ecdsa521_pub_params_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ECDSA521_PUB_PARAMS_SIZE;
}

void fs5_image_layout_crypto_ecdsa521_pub_params_dump(const struct fs5_image_layout_crypto_ecdsa521_pub_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_ecdsa521_pub_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_encryption_params_pack(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_encryption_derivation_string_pack(&(ptr_struct->u8_encryption_derivation_string), ptr_buff + offset / 8);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_data_encryption_key_version);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->u8_reserved);
	offset = 160;
	fs5_image_layout_u8_iv_pack(&(ptr_struct->u8_iv), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_u8_auth_tag_pack(&(ptr_struct->u8_auth_tag), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_encryption_params_unpack(struct fs5_image_layout_crypto_encryption_params *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_encryption_derivation_string_unpack(&(ptr_struct->u8_encryption_derivation_string), ptr_buff + offset / 8);
	offset = 152;
	ptr_struct->u8_data_encryption_key_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->u8_reserved = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 160;
	fs5_image_layout_u8_iv_unpack(&(ptr_struct->u8_iv), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_u8_auth_tag_unpack(&(ptr_struct->u8_auth_tag), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_encryption_params_print(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_encryption_params ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_encryption_derivation_string:\n");
	fs5_image_layout_u8_encryption_derivation_string_print(&(ptr_struct->u8_encryption_derivation_string), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_data_encryption_key_version : " UH_FMT "\n", ptr_struct->u8_data_encryption_key_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_reserved          : " UH_FMT "\n", ptr_struct->u8_reserved);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_iv:\n");
	fs5_image_layout_u8_iv_print(&(ptr_struct->u8_iv), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_auth_tag:\n");
	fs5_image_layout_u8_auth_tag_print(&(ptr_struct->u8_auth_tag), fd, indent_level + 1);
}

unsigned int fs5_image_layout_crypto_encryption_params_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_ENCRYPTION_PARAMS_SIZE;
}

void fs5_image_layout_crypto_encryption_params_dump(const struct fs5_image_layout_crypto_encryption_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_encryption_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_rsa3k_pub_params_pack(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_crypto_rsa3k_pub_params_unpack(struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_crypto_rsa3k_pub_params_print(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_rsa3k_pub_params ========\n");

	for (i = 0; i < 384; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_crypto_rsa3k_pub_params_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_RSA3K_PUB_PARAMS_SIZE;
}

void fs5_image_layout_crypto_rsa3k_pub_params_dump(const struct fs5_image_layout_crypto_rsa3k_pub_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_rsa3k_pub_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_flags_bch_stage2_comp_pack(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 26, (u_int32_t)ptr_struct->u_pad);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->b_is_encrypted);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->b_is_compressed);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u_compression_scheme);
}

void fs5_image_layout_flags_bch_stage2_comp_unpack(struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 6;
	ptr_struct->u_pad = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 26);
	offset = 5;
	ptr_struct->b_is_encrypted = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->b_is_compressed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->u_compression_scheme = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void fs5_image_layout_flags_bch_stage2_comp_print(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_flags_bch_stage2_comp ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u_pad                : " UH_FMT "\n", ptr_struct->u_pad);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "b_is_encrypted       : " UH_FMT "\n", ptr_struct->b_is_encrypted);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "b_is_compressed      : " UH_FMT "\n", ptr_struct->b_is_compressed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u_compression_scheme : " UH_FMT "\n", ptr_struct->u_compression_scheme);
}

unsigned int fs5_image_layout_flags_bch_stage2_comp_size(void)
{
	return FS5_IMAGE_LAYOUT_FLAGS_BCH_STAGE2_COMP_SIZE;
}

void fs5_image_layout_flags_bch_stage2_comp_dump(const struct fs5_image_layout_flags_bch_stage2_comp *ptr_struct, FILE *fd)
{
	fs5_image_layout_flags_bch_stage2_comp_print(ptr_struct, fd, 0);
}

void fs5_image_layout_flash_config_params_pack(const struct fs5_image_layout_flash_config_params *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_div);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->flash_sample_in);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->flash_sample_out);
}

void fs5_image_layout_flash_config_params_unpack(struct fs5_image_layout_flash_config_params *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->flash_div = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 19;
	ptr_struct->flash_sample_in = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 14;
	ptr_struct->flash_sample_out = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void fs5_image_layout_flash_config_params_print(const struct fs5_image_layout_flash_config_params *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_flash_config_params ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_div            : " UH_FMT "\n", ptr_struct->flash_div);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_sample_in      : " UH_FMT "\n", ptr_struct->flash_sample_in);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_sample_out     : " UH_FMT "\n", ptr_struct->flash_sample_out);
}

unsigned int fs5_image_layout_flash_config_params_size(void)
{
	return FS5_IMAGE_LAYOUT_FLASH_CONFIG_PARAMS_SIZE;
}

void fs5_image_layout_flash_config_params_dump(const struct fs5_image_layout_flash_config_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_flash_config_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_reserved_padding_arr_pack(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 3072; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 24576, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_reserved_padding_arr_unpack(struct fs5_image_layout_reserved_padding_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 3072; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 24576, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_reserved_padding_arr_print(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_reserved_padding_arr ========\n");

	for (i = 0; i < 3072; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_reserved_padding_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_RESERVED_PADDING_ARR_SIZE;
}

void fs5_image_layout_reserved_padding_arr_dump(const struct fs5_image_layout_reserved_padding_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_reserved_padding_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_signatures_pack(const union fs5_image_layout_signatures *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_u8_xmss_signature_arr_pack(&(ptr_struct->u8_xmss_signature), ptr_buff);
}

void fs5_image_layout_signatures_unpack(union fs5_image_layout_signatures *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_u8_xmss_signature_arr_unpack(&(ptr_struct->u8_xmss_signature), ptr_buff);
}

void fs5_image_layout_signatures_print(const union fs5_image_layout_signatures *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_signatures ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_rsa3k_signature:\n");
	fs5_image_layout_u8_rsa3k_signature_arr_print(&(ptr_struct->u8_rsa3k_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa256_signature:\n");
	fs5_image_layout_crypto_ecdsa256_signature_print(&(ptr_struct->ecdsa256_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa521_signature:\n");
	fs5_image_layout_crypto_ecdsa521_signature_print(&(ptr_struct->ecdsa521_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ed25519_signature:\n");
	fs5_image_layout_crypto_ed25519_signature_print(&(ptr_struct->ed25519_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_xmss_signature:\n");
	fs5_image_layout_u8_xmss_signature_arr_print(&(ptr_struct->u8_xmss_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_hmac_sha2_256_tag:\n");
	fs5_image_layout_u8_hmac_sha2_256_tag_arr_print(&(ptr_struct->u8_hmac_sha2_256_tag), fd, indent_level + 1);
}

unsigned int fs5_image_layout_signatures_size(void)
{
	return FS5_IMAGE_LAYOUT_SIGNATURES_SIZE;
}

void fs5_image_layout_signatures_dump(const union fs5_image_layout_signatures *ptr_struct, FILE *fd)
{
	fs5_image_layout_signatures_print(ptr_struct, fd, 0);
}

void fs5_image_layout_signatures_v2_pack(const union fs5_image_layout_signatures_v2 *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_u8_rsa3k_signature_arr_pack(&(ptr_struct->u8_rsa3k_signature), ptr_buff);
}

void fs5_image_layout_signatures_v2_unpack(union fs5_image_layout_signatures_v2 *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_u8_rsa3k_signature_arr_unpack(&(ptr_struct->u8_rsa3k_signature), ptr_buff);
}

void fs5_image_layout_signatures_v2_print(const union fs5_image_layout_signatures_v2 *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_signatures_v2 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_rsa3k_signature:\n");
	fs5_image_layout_u8_rsa3k_signature_arr_print(&(ptr_struct->u8_rsa3k_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa256_signature:\n");
	fs5_image_layout_crypto_ecdsa256_signature_print(&(ptr_struct->ecdsa256_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa521_signature:\n");
	fs5_image_layout_crypto_ecdsa521_signature_print(&(ptr_struct->ecdsa521_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ed25519_signature:\n");
	fs5_image_layout_crypto_ed25519_signature_print(&(ptr_struct->ed25519_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_hmac_sha2_256_tag:\n");
	fs5_image_layout_u8_hmac_sha2_256_tag_arr_print(&(ptr_struct->u8_hmac_sha2_256_tag), fd, indent_level + 1);
}

unsigned int fs5_image_layout_signatures_v2_size(void)
{
	return FS5_IMAGE_LAYOUT_SIGNATURES_V2_SIZE;
}

void fs5_image_layout_signatures_v2_dump(const union fs5_image_layout_signatures_v2 *ptr_struct, FILE *fd)
{
	fs5_image_layout_signatures_v2_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_digest_pack(const struct fs5_image_layout_u8_digest *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 512, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->digest[i]);
	}
}

void fs5_image_layout_u8_digest_unpack(struct fs5_image_layout_u8_digest *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 512, 1);
		ptr_struct->digest[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void fs5_image_layout_u8_digest_print(const struct fs5_image_layout_u8_digest *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_digest ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "digest_%03d          : " U32H_FMT "\n", i, ptr_struct->digest[i]);
	}
}

unsigned int fs5_image_layout_u8_digest_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_DIGEST_SIZE;
}

void fs5_image_layout_u8_digest_dump(const struct fs5_image_layout_u8_digest *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_digest_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_ed25519_pub_param_arr_pack(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_ed25519_pub_param_arr_unpack(struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_ed25519_pub_param_arr_print(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_ed25519_pub_param_arr ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_ed25519_pub_param_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_ED25519_PUB_PARAM_ARR_SIZE;
}

void fs5_image_layout_u8_ed25519_pub_param_arr_dump(const struct fs5_image_layout_u8_ed25519_pub_param_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_ed25519_pub_param_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1620; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 12960, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1620; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 12960, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr ========\n");

	for (i = 0; i < 1620; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_LMS_SHA192_H15_W4_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1740; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 13920, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1740; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 13920, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr ========\n");

	for (i = 0; i < 1740; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_LMS_SHA192_H20_W4_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2668; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 21344, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2668; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 21344, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr ========\n");

	for (i = 0; i < 2668; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_LMS_SHA256_H15_W4_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_pack(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2828; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 22624, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_unpack(struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2828; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 22624, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_print(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr ========\n");

	for (i = 0; i < 2828; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_LMS_SHA256_H20_W4_SIGNATURE_ARR_SIZE;
}

void fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_dump(const struct fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_res_pack(const struct fs5_image_layout_u8_res *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_res_unpack(struct fs5_image_layout_u8_res *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_res_print(const struct fs5_image_layout_u8_res *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_res ========\n");

	for (i = 0; i < 12; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_res_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_RES_SIZE;
}

void fs5_image_layout_u8_res_dump(const struct fs5_image_layout_u8_res *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_res_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_xmss_pub_param_arr_pack(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_xmss_pub_param_arr_unpack(struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 512, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_xmss_pub_param_arr_print(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_xmss_pub_param_arr ========\n");

	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_xmss_pub_param_arr_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_XMSS_PUB_PARAM_ARR_SIZE;
}

void fs5_image_layout_u8_xmss_pub_param_arr_dump(const struct fs5_image_layout_u8_xmss_pub_param_arr *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_xmss_pub_param_arr_print(ptr_struct, fd, 0);
}

void fs5_image_layout_bch_stage2_component_pack(const struct fs5_image_layout_bch_stage2_component *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1280, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_binary_magic[i]);
	}
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_binary_len);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_load_dest);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_entry_point);
	offset = 128;
	fs5_image_layout_boot_component_ver_pack(&(ptr_struct->ver), ptr_buff + offset / 8);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_start_page);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_start_block);
	offset = 224;
	fs5_image_layout_flags_bch_stage2_comp_pack(&(ptr_struct->flags), ptr_buff + offset / 8);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_binary_len_auth);
	offset = 288;
	fs5_image_layout_u8_res_pack(&(ptr_struct->u8_res), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_crypto_encryption_params_pack(&(ptr_struct->enc_params), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_bch_stage2_component_unpack(struct fs5_image_layout_bch_stage2_component *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1280, 1);
		ptr_struct->u8_binary_magic[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 32;
	ptr_struct->u32_binary_len = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->u32_load_dest = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->u32_entry_point = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	fs5_image_layout_boot_component_ver_unpack(&(ptr_struct->ver), ptr_buff + offset / 8);
	offset = 160;
	ptr_struct->u32_start_page = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->u32_start_block = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	fs5_image_layout_flags_bch_stage2_comp_unpack(&(ptr_struct->flags), ptr_buff + offset / 8);
	offset = 256;
	ptr_struct->u32_binary_len_auth = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	fs5_image_layout_u8_res_unpack(&(ptr_struct->u8_res), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_crypto_encryption_params_unpack(&(ptr_struct->enc_params), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_bch_stage2_component_print(const struct fs5_image_layout_bch_stage2_component *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_bch_stage2_component ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_binary_magic_%03d : " UH_FMT "\n", i, ptr_struct->u8_binary_magic[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_binary_len       : " U32H_FMT "\n", ptr_struct->u32_binary_len);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_load_dest        : " U32H_FMT "\n", ptr_struct->u32_load_dest);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_entry_point      : " U32H_FMT "\n", ptr_struct->u32_entry_point);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ver:\n");
	fs5_image_layout_boot_component_ver_print(&(ptr_struct->ver), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_start_page       : " U32H_FMT "\n", ptr_struct->u32_start_page);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_start_block      : " U32H_FMT "\n", ptr_struct->u32_start_block);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flags:\n");
	fs5_image_layout_flags_bch_stage2_comp_print(&(ptr_struct->flags), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_binary_len_auth  : " U32H_FMT "\n", ptr_struct->u32_binary_len_auth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_res:\n");
	fs5_image_layout_u8_res_print(&(ptr_struct->u8_res), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "enc_params:\n");
	fs5_image_layout_crypto_encryption_params_print(&(ptr_struct->enc_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
}

unsigned int fs5_image_layout_bch_stage2_component_size(void)
{
	return FS5_IMAGE_LAYOUT_BCH_STAGE2_COMPONENT_SIZE;
}

void fs5_image_layout_bch_stage2_component_dump(const struct fs5_image_layout_bch_stage2_component *ptr_struct, FILE *fd)
{
	fs5_image_layout_bch_stage2_component_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_public_crypto_params_pack(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_crypto_rsa3k_pub_params_pack(&(ptr_struct->rsa3k_pub_params), ptr_buff);
}

void fs5_image_layout_crypto_public_crypto_params_unpack(union fs5_image_layout_crypto_public_crypto_params *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_crypto_rsa3k_pub_params_unpack(&(ptr_struct->rsa3k_pub_params), ptr_buff);
}

void fs5_image_layout_crypto_public_crypto_params_print(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_public_crypto_params ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rsa3k_pub_params:\n");
	fs5_image_layout_crypto_rsa3k_pub_params_print(&(ptr_struct->rsa3k_pub_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa256_pub_params:\n");
	fs5_image_layout_crypto_ecdsa256_pub_params_print(&(ptr_struct->ecdsa256_pub_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa521_pub_params:\n");
	fs5_image_layout_crypto_ecdsa521_pub_params_print(&(ptr_struct->ecdsa521_pub_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ed25519_pub_param:\n");
	fs5_image_layout_u8_ed25519_pub_param_arr_print(&(ptr_struct->u8_ed25519_pub_param), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_xmss_pub_param:\n");
	fs5_image_layout_u8_xmss_pub_param_arr_print(&(ptr_struct->u8_xmss_pub_param), fd, indent_level + 1);
}

unsigned int fs5_image_layout_crypto_public_crypto_params_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_PUBLIC_CRYPTO_PARAMS_SIZE;
}

void fs5_image_layout_crypto_public_crypto_params_dump(const union fs5_image_layout_crypto_public_crypto_params *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_public_crypto_params_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_signatures_pack(const struct fs5_image_layout_crypto_signatures *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_signatures_pack(&(ptr_struct->signatures), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_signatures_unpack(struct fs5_image_layout_crypto_signatures *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_signatures_unpack(&(ptr_struct->signatures), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_signatures_print(const struct fs5_image_layout_crypto_signatures *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_signatures ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signatures:\n");
	fs5_image_layout_signatures_print(&(ptr_struct->signatures), fd, indent_level + 1);
}

unsigned int fs5_image_layout_crypto_signatures_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_SIGNATURES_SIZE;
}

void fs5_image_layout_crypto_signatures_dump(const struct fs5_image_layout_crypto_signatures *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_signatures_print(ptr_struct, fd, 0);
}

void fs5_image_layout_crypto_signatures_v2_pack(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_signatures_v2_pack(&(ptr_struct->signatures), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_signatures_v2_unpack(struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_signatures_v2_unpack(&(ptr_struct->signatures), ptr_buff + offset / 8);
}

void fs5_image_layout_crypto_signatures_v2_print(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_crypto_signatures_v2 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signatures:\n");
	fs5_image_layout_signatures_v2_print(&(ptr_struct->signatures), fd, indent_level + 1);
}

unsigned int fs5_image_layout_crypto_signatures_v2_size(void)
{
	return FS5_IMAGE_LAYOUT_CRYPTO_SIGNATURES_V2_SIZE;
}

void fs5_image_layout_crypto_signatures_v2_dump(const struct fs5_image_layout_crypto_signatures_v2 *ptr_struct, FILE *fd)
{
	fs5_image_layout_crypto_signatures_v2_print(ptr_struct, fd, 0);
}

void fs5_image_layout_hw_pointer_entry_pack(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ptr);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->crc);
}

void fs5_image_layout_hw_pointer_entry_unpack(struct fs5_image_layout_hw_pointer_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ptr = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->crc = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void fs5_image_layout_hw_pointer_entry_print(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_hw_pointer_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptr                  : " U32H_FMT "\n", ptr_struct->ptr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crc                  : " UH_FMT "\n", ptr_struct->crc);
}

unsigned int fs5_image_layout_hw_pointer_entry_size(void)
{
	return FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE;
}

void fs5_image_layout_hw_pointer_entry_dump(const struct fs5_image_layout_hw_pointer_entry *ptr_struct, FILE *fd)
{
	fs5_image_layout_hw_pointer_entry_print(ptr_struct, fd, 0);
}

void fs5_image_layout_pqc_signatures_pack(const union fs5_image_layout_pqc_signatures *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_reserved_padding_arr_pack(&(ptr_struct->reserved_padding), ptr_buff);
}

void fs5_image_layout_pqc_signatures_unpack(union fs5_image_layout_pqc_signatures *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_reserved_padding_arr_unpack(&(ptr_struct->reserved_padding), ptr_buff);
}

void fs5_image_layout_pqc_signatures_print(const union fs5_image_layout_pqc_signatures *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_pqc_signatures ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_lms_sha192_h15_w4_signature:\n");
	fs5_image_layout_u8_lms_sha192_h15_w4_signature_arr_print(&(ptr_struct->u8_lms_sha192_h15_w4_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_lms_sha192_h20_w4_signature:\n");
	fs5_image_layout_u8_lms_sha192_h20_w4_signature_arr_print(&(ptr_struct->u8_lms_sha192_h20_w4_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_lms_sha256_h15_w4_signature:\n");
	fs5_image_layout_u8_lms_sha256_h15_w4_signature_arr_print(&(ptr_struct->u8_lms_sha256_h15_w4_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_lms_sha256_h20_w4_signature:\n");
	fs5_image_layout_u8_lms_sha256_h20_w4_signature_arr_print(&(ptr_struct->u8_lms_sha256_h20_w4_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved_padding:\n");
	fs5_image_layout_reserved_padding_arr_print(&(ptr_struct->reserved_padding), fd, indent_level + 1);
}

unsigned int fs5_image_layout_pqc_signatures_size(void)
{
	return FS5_IMAGE_LAYOUT_PQC_SIGNATURES_SIZE;
}

void fs5_image_layout_pqc_signatures_dump(const union fs5_image_layout_pqc_signatures *ptr_struct, FILE *fd)
{
	fs5_image_layout_pqc_signatures_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_derivation_label_check_pack(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_derivation_label_check_unpack(struct fs5_image_layout_u8_derivation_label_check *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_derivation_label_check_print(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_derivation_label_check ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_derivation_label_check_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_DERIVATION_LABEL_CHECK_SIZE;
}

void fs5_image_layout_u8_derivation_label_check_dump(const struct fs5_image_layout_u8_derivation_label_check *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_derivation_label_check_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_ecid_pack(const struct fs5_image_layout_u8_ecid *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_ecid_unpack(struct fs5_image_layout_u8_ecid *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_ecid_print(const struct fs5_image_layout_u8_ecid *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_ecid ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_ecid_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_ECID_SIZE;
}

void fs5_image_layout_u8_sha2_384_digest_pack(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 384, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->digest[i]);
	}
}

void fs5_image_layout_u8_sha2_384_digest_unpack(struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 384, 1);
		ptr_struct->digest[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void fs5_image_layout_u8_sha2_384_digest_print(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_sha2_384_digest ========\n");

	for (i = 0; i < 12; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "digest_%03d          : " U32H_FMT "\n", i, ptr_struct->digest[i]);
	}
}

unsigned int fs5_image_layout_u8_sha2_384_digest_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_SHA2_384_DIGEST_SIZE;
}

void fs5_image_layout_u8_sha2_384_digest_dump(const struct fs5_image_layout_u8_sha2_384_digest *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_sha2_384_digest_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_ecid_dump(const struct fs5_image_layout_u8_ecid *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_ecid_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_gen_padding_pack(const struct fs5_image_layout_u8_gen_padding *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 672; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 5376, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_gen_padding_unpack(struct fs5_image_layout_u8_gen_padding *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 672; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 5376, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_gen_padding_print(const struct fs5_image_layout_u8_gen_padding *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_gen_padding ========\n");

	for (i = 0; i < 672; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_gen_padding_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_GEN_PADDING_SIZE;
}

void fs5_image_layout_u8_gen_padding_dump(const struct fs5_image_layout_u8_gen_padding *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_gen_padding_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_gen_padding_pqc_pack(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 44; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 352, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_gen_padding_pqc_unpack(struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 44; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 352, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_gen_padding_pqc_print(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_gen_padding_pqc ========\n");

	for (i = 0; i < 44; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_gen_padding_pqc_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_GEN_PADDING_PQC_SIZE;
}

void fs5_image_layout_u8_gen_padding_pqc_dump(const struct fs5_image_layout_u8_gen_padding_pqc *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_gen_padding_pqc_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_salt_pack(const struct fs5_image_layout_u8_salt *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_salt_unpack(struct fs5_image_layout_u8_salt *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_salt_print(const struct fs5_image_layout_u8_salt *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_salt ========\n");

	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_salt_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_SALT_SIZE;
}

void fs5_image_layout_u8_salt_dump(const struct fs5_image_layout_u8_salt *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_salt_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_sec_provision_derivation_string_pack(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_sec_provision_derivation_string_unpack(struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_sec_provision_derivation_string_print(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_sec_provision_derivation_string ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_sec_provision_derivation_string_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_SEC_PROVISION_DERIVATION_STRING_SIZE;
}

void fs5_image_layout_u8_sec_provision_derivation_string_dump(const struct fs5_image_layout_u8_sec_provision_derivation_string *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_sec_provision_derivation_string_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_stage1_component_pack(const struct fs5_image_layout_u8_stage1_component *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1152, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_binary_magic[i]);
	}
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_binary_len);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_load_dest);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_entry_point);
	offset = 128;
	fs5_image_layout_boot_component_ver_pack(&(ptr_struct->ver), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(184, 8, i, 1152, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_res[i]);
	}
	offset = 224;
	fs5_image_layout_bch_boot_component_flags_pack(&(ptr_struct->flags), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_crypto_encryption_params_pack(&(ptr_struct->enc_params), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_component_unpack(struct fs5_image_layout_u8_stage1_component *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1152, 1);
		ptr_struct->u8_binary_magic[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 32;
	ptr_struct->u32_binary_len = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->u32_load_dest = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->u32_entry_point = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	fs5_image_layout_boot_component_ver_unpack(&(ptr_struct->ver), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(184, 8, i, 1152, 1);
		ptr_struct->u8_res[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 224;
	fs5_image_layout_bch_boot_component_flags_unpack(&(ptr_struct->flags), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_crypto_encryption_params_unpack(&(ptr_struct->enc_params), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_component_print(const struct fs5_image_layout_u8_stage1_component *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_stage1_component ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_binary_magic_%03d : " UH_FMT "\n", i, ptr_struct->u8_binary_magic[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_binary_len       : " U32H_FMT "\n", ptr_struct->u32_binary_len);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_load_dest        : " U32H_FMT "\n", ptr_struct->u32_load_dest);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_entry_point      : " U32H_FMT "\n", ptr_struct->u32_entry_point);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ver:\n");
	fs5_image_layout_boot_component_ver_print(&(ptr_struct->ver), fd, indent_level + 1);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_res_%03d          : " UH_FMT "\n", i, ptr_struct->u8_res[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flags:\n");
	fs5_image_layout_bch_boot_component_flags_print(&(ptr_struct->flags), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "enc_params:\n");
	fs5_image_layout_crypto_encryption_params_print(&(ptr_struct->enc_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
}

unsigned int fs5_image_layout_u8_stage1_component_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_STAGE1_COMPONENT_SIZE;
}

void fs5_image_layout_u8_stage1_component_dump(const struct fs5_image_layout_u8_stage1_component *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_stage1_component_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_stage1_res_pack(const struct fs5_image_layout_u8_stage1_res *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hash_offset);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->BL1_bind_version);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->FW_bind_version);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->BL1_updt);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->FW_updt);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->NCORE_updt);
	offset = 256;
	fs5_image_layout_flash_config_params_pack(&(ptr_struct->flash_config_params), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_res_unpack(struct fs5_image_layout_u8_stage1_res *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->reserved = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->hash_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->BL1_bind_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->FW_bind_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->BL1_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->FW_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->NCORE_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	fs5_image_layout_flash_config_params_unpack(&(ptr_struct->flash_config_params), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_res_print(const struct fs5_image_layout_u8_stage1_res *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_stage1_res ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " U32H_FMT "\n", ptr_struct->reserved);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_offset          : " U32H_FMT "\n", ptr_struct->hash_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "BL1_bind_version     : " U32H_FMT "\n", ptr_struct->BL1_bind_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_bind_version      : " U32H_FMT "\n", ptr_struct->FW_bind_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "BL1_updt             : " U32H_FMT "\n", ptr_struct->BL1_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_updt              : " U32H_FMT "\n", ptr_struct->FW_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "NCORE_updt           : " U32H_FMT "\n", ptr_struct->NCORE_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_config_params:\n");
	fs5_image_layout_flash_config_params_print(&(ptr_struct->flash_config_params), fd, indent_level + 1);
}

unsigned int fs5_image_layout_u8_stage1_res_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_STAGE1_RES_SIZE;
}

void fs5_image_layout_u8_stage1_res_dump(const struct fs5_image_layout_u8_stage1_res *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_stage1_res_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_stage1_res_lms_pack(const struct fs5_image_layout_u8_stage1_res_lms *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hash_offset);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->BL1_bind_version);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->FW_bind_version);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->BL1_updt);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->FW_updt);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->NCORE_updt);
	offset = 256;
	fs5_image_layout_flash_config_params_pack(&(ptr_struct->flash_config_params), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_res_lms_unpack(struct fs5_image_layout_u8_stage1_res_lms *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->reserved = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->hash_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->BL1_bind_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->FW_bind_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->BL1_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->FW_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->NCORE_updt = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	fs5_image_layout_flash_config_params_unpack(&(ptr_struct->flash_config_params), ptr_buff + offset / 8);
}

void fs5_image_layout_u8_stage1_res_lms_print(const struct fs5_image_layout_u8_stage1_res_lms *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_stage1_res_lms ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " U32H_FMT "\n", ptr_struct->reserved);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hash_offset          : " U32H_FMT "\n", ptr_struct->hash_offset);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "BL1_bind_version     : " U32H_FMT "\n", ptr_struct->BL1_bind_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_bind_version      : " U32H_FMT "\n", ptr_struct->FW_bind_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "BL1_updt             : " U32H_FMT "\n", ptr_struct->BL1_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "FW_updt              : " U32H_FMT "\n", ptr_struct->FW_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "NCORE_updt           : " U32H_FMT "\n", ptr_struct->NCORE_updt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_config_params:\n");
	fs5_image_layout_flash_config_params_print(&(ptr_struct->flash_config_params), fd, indent_level + 1);
}

unsigned int fs5_image_layout_u8_stage1_res_lms_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_STAGE1_RES_LMS_SIZE;
}

void fs5_image_layout_u8_stage1_res_lms_dump(const struct fs5_image_layout_u8_stage1_res_lms *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_stage1_res_lms_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_stage1_signature_pack(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_stage1_signature_unpack(struct fs5_image_layout_u8_stage1_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 384; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 3072, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_stage1_signature_print(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_stage1_signature ========\n");

	for (i = 0; i < 384; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_stage1_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_STAGE1_SIGNATURE_SIZE;
}

void fs5_image_layout_u8_stage1_signature_dump(const struct fs5_image_layout_u8_stage1_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_stage1_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_stage2_padding_pack(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1036; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 8288, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_stage2_padding_unpack(struct fs5_image_layout_u8_stage2_padding *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 1036; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 8288, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_stage2_padding_print(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_stage2_padding ========\n");

	for (i = 0; i < 1036; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_stage2_padding_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_STAGE2_PADDING_SIZE;
}

void fs5_image_layout_u8_stage2_padding_dump(const struct fs5_image_layout_u8_stage2_padding *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_stage2_padding_print(ptr_struct, fd, 0);
}

void fs5_image_layout_u8_unsigned_padding_pack(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_dummy[i]);
	}
}

void fs5_image_layout_u8_unsigned_padding_unpack(struct fs5_image_layout_u8_unsigned_padding *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 12; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 96, 1);
		ptr_struct->u8_dummy[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_u8_unsigned_padding_print(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_u8_unsigned_padding ========\n");

	for (i = 0; i < 12; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_dummy_%03d        : " UH_FMT "\n", i, ptr_struct->u8_dummy[i]);
	}
}

unsigned int fs5_image_layout_u8_unsigned_padding_size(void)
{
	return FS5_IMAGE_LAYOUT_U8_UNSIGNED_PADDING_SIZE;
}

void fs5_image_layout_u8_unsigned_padding_dump(const struct fs5_image_layout_u8_unsigned_padding *ptr_struct, FILE *fd)
{
	fs5_image_layout_u8_unsigned_padding_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_header_pack(const struct fs5_image_layout_boot_component_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 65536, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_header_magic[i]);
	}
	offset = 32;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_u8_unsigned_padding_pack(&(ptr_struct->u8_unsigned_padding), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_crypto_signatures_pack(&(ptr_struct->stage2_signature), ptr_buff + offset / 8);
	offset = 23808;
	fs5_image_layout_crypto_public_crypto_params_pack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 26880;
	fs5_image_layout_u8_gen_padding_pack(&(ptr_struct->u8_gen_padding), ptr_buff + offset / 8);
	offset = 32256;
	fs5_image_layout_u8_salt_pack(&(ptr_struct->u8_salt2), ptr_buff + offset / 8);
	offset = 32384;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_ecid2), ptr_buff + offset / 8);
	offset = 32512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_num_binaries2);
	offset = 32544;
	fs5_image_layout_u8_stage2_padding_pack(&(ptr_struct->u8_stage2_padding), ptr_buff + offset / 8);
	offset = 40832;
	fs5_image_layout_u8_derivation_label_check_pack(&(ptr_struct->u8_stage2_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(40960, 1280, i, 65536, 1);
		fs5_image_layout_bch_stage2_component_pack(&(ptr_struct->stage2_components[i]), ptr_buff + offset / 8);
	}
	offset = 51200;
	fs5_image_layout_u8_stage1_signature_pack(&(ptr_struct->u8_stage1_signature), ptr_buff + offset / 8);
	offset = 54272;
	fs5_image_layout_u8_salt_pack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 54400;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_ecid1), ptr_buff + offset / 8);
	offset = 54528;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_num_binaries1);
	offset = 54560;
	fs5_image_layout_u8_stage1_res_pack(&(ptr_struct->u8_stage1_res), ptr_buff + offset / 8);
	offset = 63104;
	fs5_image_layout_u8_derivation_label_check_pack(&(ptr_struct->u8_stage1_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(63232, 1152, i, 65536, 1);
		fs5_image_layout_u8_stage1_component_pack(&(ptr_struct->stage1_components[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_boot_component_header_unpack(struct fs5_image_layout_boot_component_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 65536, 1);
		ptr_struct->u8_header_magic[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 32;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_u8_unsigned_padding_unpack(&(ptr_struct->u8_unsigned_padding), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_crypto_signatures_unpack(&(ptr_struct->stage2_signature), ptr_buff + offset / 8);
	offset = 23808;
	fs5_image_layout_crypto_public_crypto_params_unpack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 26880;
	fs5_image_layout_u8_gen_padding_unpack(&(ptr_struct->u8_gen_padding), ptr_buff + offset / 8);
	offset = 32256;
	fs5_image_layout_u8_salt_unpack(&(ptr_struct->u8_salt2), ptr_buff + offset / 8);
	offset = 32384;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_ecid2), ptr_buff + offset / 8);
	offset = 32512;
	ptr_struct->u32_num_binaries2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32544;
	fs5_image_layout_u8_stage2_padding_unpack(&(ptr_struct->u8_stage2_padding), ptr_buff + offset / 8);
	offset = 40832;
	fs5_image_layout_u8_derivation_label_check_unpack(&(ptr_struct->u8_stage2_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(40960, 1280, i, 65536, 1);
		fs5_image_layout_bch_stage2_component_unpack(&(ptr_struct->stage2_components[i]), ptr_buff + offset / 8);
	}
	offset = 51200;
	fs5_image_layout_u8_stage1_signature_unpack(&(ptr_struct->u8_stage1_signature), ptr_buff + offset / 8);
	offset = 54272;
	fs5_image_layout_u8_salt_unpack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 54400;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_ecid1), ptr_buff + offset / 8);
	offset = 54528;
	ptr_struct->u32_num_binaries1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 54560;
	fs5_image_layout_u8_stage1_res_unpack(&(ptr_struct->u8_stage1_res), ptr_buff + offset / 8);
	offset = 63104;
	fs5_image_layout_u8_derivation_label_check_unpack(&(ptr_struct->u8_stage1_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(63232, 1152, i, 65536, 1);
		fs5_image_layout_u8_stage1_component_unpack(&(ptr_struct->stage1_components[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_boot_component_header_print(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_header ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_header_magic_%03d : " UH_FMT "\n", i, ptr_struct->u8_header_magic[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_unsigned_padding:\n");
	fs5_image_layout_u8_unsigned_padding_print(&(ptr_struct->u8_unsigned_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stage2_signature:\n");
	fs5_image_layout_crypto_signatures_print(&(ptr_struct->stage2_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcp:\n");
	fs5_image_layout_crypto_public_crypto_params_print(&(ptr_struct->pcp), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_gen_padding:\n");
	fs5_image_layout_u8_gen_padding_print(&(ptr_struct->u8_gen_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_salt2:\n");
	fs5_image_layout_u8_salt_print(&(ptr_struct->u8_salt2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ecid2:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_ecid2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_num_binaries2    : " U32H_FMT "\n", ptr_struct->u32_num_binaries2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage2_padding:\n");
	fs5_image_layout_u8_stage2_padding_print(&(ptr_struct->u8_stage2_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage2_derivation_label_check:\n");
	fs5_image_layout_u8_derivation_label_check_print(&(ptr_struct->u8_stage2_derivation_label_check), fd, indent_level + 1);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "stage2_components_%03d:\n", i);
		fs5_image_layout_bch_stage2_component_print(&(ptr_struct->stage2_components[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_signature:\n");
	fs5_image_layout_u8_stage1_signature_print(&(ptr_struct->u8_stage1_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_salt1:\n");
	fs5_image_layout_u8_salt_print(&(ptr_struct->u8_salt1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ecid1:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_ecid1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_num_binaries1    : " U32H_FMT "\n", ptr_struct->u32_num_binaries1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_res:\n");
	fs5_image_layout_u8_stage1_res_print(&(ptr_struct->u8_stage1_res), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_derivation_label_check:\n");
	fs5_image_layout_u8_derivation_label_check_print(&(ptr_struct->u8_stage1_derivation_label_check), fd, indent_level + 1);
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "stage1_components_%03d:\n", i);
		fs5_image_layout_u8_stage1_component_print(&(ptr_struct->stage1_components[i]), fd, indent_level + 1);
	}
}

unsigned int fs5_image_layout_boot_component_header_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE;
}

void fs5_image_layout_boot_component_header_dump(const struct fs5_image_layout_boot_component_header *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_header_print(ptr_struct, fd, 0);
}

void fs5_image_layout_partition_table_entry_pack(const struct fs5_image_layout_partition_table_entry *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_type);
	for (i = 0; i < 36; ++i) {
		offset = adb2c_calc_array_field_address(56, 8, i, 768, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->partition_name[i]);
	}
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_id);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_instance);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_chipselect);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(448, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->start_address[i]);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_size[i]);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partition_attr[i]);
	}
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(664, 8, i, 768, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reserved1[i]);
	}
}

void fs5_image_layout_partition_table_entry_unpack(struct fs5_image_layout_partition_table_entry *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->partition_type = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 36; ++i) {
		offset = adb2c_calc_array_field_address(56, 8, i, 768, 1);
		ptr_struct->partition_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 320;
	ptr_struct->device_id = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->device_instance = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->device_chipselect = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->reserved = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(448, 32, i, 768, 1);
		ptr_struct->start_address[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 768, 1);
		ptr_struct->partition_size[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 768, 1);
		ptr_struct->partition_attr[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(664, 8, i, 768, 1);
		ptr_struct->reserved1[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_partition_table_entry_print(const struct fs5_image_layout_partition_table_entry *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_partition_table_entry ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partition_type       : " U32H_FMT "\n", ptr_struct->partition_type);
	for (i = 0; i < 36; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "partition_name_%03d  : " UH_FMT "\n", i, ptr_struct->partition_name[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_id            : " U32H_FMT "\n", ptr_struct->device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_instance      : " U32H_FMT "\n", ptr_struct->device_instance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_chipselect    : " U32H_FMT "\n", ptr_struct->device_chipselect);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " U32H_FMT "\n", ptr_struct->reserved);
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "start_address_%03d   : " U32H_FMT "\n", i, ptr_struct->start_address[i]);
	}
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "partition_size_%03d  : " U32H_FMT "\n", i, ptr_struct->partition_size[i]);
	}
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "partition_attr_%03d  : " U32H_FMT "\n", i, ptr_struct->partition_attr[i]);
	}
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "reserved1_%03d       : " UH_FMT "\n", i, ptr_struct->reserved1[i]);
	}
}

unsigned int fs5_image_layout_partition_table_entry_size(void)
{
	return FS5_IMAGE_LAYOUT_PARTITION_TABLE_ENTRY_SIZE;
}

void fs5_image_layout_partition_table_entry_dump(const struct fs5_image_layout_partition_table_entry *ptr_struct, FILE *fd)
{
	fs5_image_layout_partition_table_entry_print(ptr_struct, fd, 0);
}

void fs5_image_layout_partition_table_header_pack(const struct fs5_image_layout_partition_table_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 896, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_magic_patttern[i]);
	}
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->entry_size);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_entires);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_entires);
	for (i = 0; i < 40; ++i) {
		offset = adb2c_calc_array_field_address(216, 8, i, 896, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reserved[i]);
	}
	offset = 512;
	fs5_image_layout_u8_sha2_384_digest_pack(&(ptr_struct->sha384_hash), ptr_buff + offset / 8);
}

void fs5_image_layout_partition_table_header_unpack(struct fs5_image_layout_partition_table_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 896, 1);
		ptr_struct->u8_magic_patttern[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 64;
	ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->entry_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->num_entires = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->max_entires = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 40; ++i) {
		offset = adb2c_calc_array_field_address(216, 8, i, 896, 1);
		ptr_struct->reserved[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 512;
	fs5_image_layout_u8_sha2_384_digest_unpack(&(ptr_struct->sha384_hash), ptr_buff + offset / 8);
}

void fs5_image_layout_partition_table_header_print(const struct fs5_image_layout_partition_table_header *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_partition_table_header ========\n");

	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_magic_patttern_%03d : " UH_FMT "\n", i, ptr_struct->u8_magic_patttern[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " U32H_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "entry_size           : " U32H_FMT "\n", ptr_struct->entry_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_entires          : " U32H_FMT "\n", ptr_struct->num_entires);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_entires          : " U32H_FMT "\n", ptr_struct->max_entires);
	for (i = 0; i < 40; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "reserved_%03d        : " UH_FMT "\n", i, ptr_struct->reserved[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sha384_hash:\n");
	fs5_image_layout_u8_sha2_384_digest_print(&(ptr_struct->sha384_hash), fd, indent_level + 1);
}

unsigned int fs5_image_layout_partition_table_header_size(void)
{
	return FS5_IMAGE_LAYOUT_PARTITION_TABLE_HEADER_SIZE;
}

void fs5_image_layout_partition_table_header_dump(const struct fs5_image_layout_partition_table_header *ptr_struct, FILE *fd)
{
	fs5_image_layout_partition_table_header_print(ptr_struct, fd, 0);
}

void fs5_image_layout_csh_component_dependency_list_pack(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_id);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_major_version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_minor_version);
}

void fs5_image_layout_csh_component_dependency_list_unpack(struct fs5_image_layout_csh_component_dependency_list *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->component_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->min_major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->min_minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void fs5_image_layout_csh_component_dependency_list_print(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_component_dependency_list ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_id         : " UH_FMT "\n", ptr_struct->component_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_major_version    : " UH_FMT "\n", ptr_struct->min_major_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_minor_version    : " UH_FMT "\n", ptr_struct->min_minor_version);
}

unsigned int fs5_image_layout_csh_component_dependency_list_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_COMPONENT_DEPENDENCY_LIST_SIZE;
}

void fs5_image_layout_csh_component_dependency_list_dump(const struct fs5_image_layout_csh_component_dependency_list *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_component_dependency_list_print(ptr_struct, fd, 0);
}


void fs5_image_layout_binary_section_metadata_pack(const struct fs5_image_layout_binary_section_metadata *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1152, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_magic_id[i]);
	}
	offset = 32;
	fs5_image_layout_boot_component_ver_pack(&(ptr_struct->version), ptr_buff + offset / 8);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->bin_length);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->flash_offset);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1152, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->load_dest[i]);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(192, 32, i, 1152, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->entry_point[i]);
	}
	offset = 286;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->presigning);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->rsvd);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lfa_compatibility);
	offset = 384;
	fs5_image_layout_crypto_encryption_params_pack(&(ptr_struct->encryption_params), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_u8_sha2_384_digest_pack(&(ptr_struct->bin_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_binary_section_metadata_unpack(struct fs5_image_layout_binary_section_metadata *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 1152, 1);
		ptr_struct->u8_magic_id[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 32;
	fs5_image_layout_boot_component_ver_unpack(&(ptr_struct->version), ptr_buff + offset / 8);
	offset = 64;
	ptr_struct->bin_length = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->flash_offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1152, 1);
		ptr_struct->load_dest[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(192, 32, i, 1152, 1);
		ptr_struct->entry_point[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 286;
	ptr_struct->presigning = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 280;
	ptr_struct->rsvd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 272;
	ptr_struct->lfa_compatibility = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 384;
	fs5_image_layout_crypto_encryption_params_unpack(&(ptr_struct->encryption_params), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_u8_sha2_384_digest_unpack(&(ptr_struct->bin_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_binary_section_metadata_print(const struct fs5_image_layout_binary_section_metadata *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_binary_section_metadata ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_magic_id_%03d     : " UH_FMT "\n", i, ptr_struct->u8_magic_id[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version:\n");
	fs5_image_layout_boot_component_ver_print(&(ptr_struct->version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bin_length           : " U32H_FMT "\n", ptr_struct->bin_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_offset         : " U32H_FMT "\n", ptr_struct->flash_offset);
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "load_dest_%03d       : " U32H_FMT "\n", i, ptr_struct->load_dest[i]);
	}
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "entry_point_%03d     : " U32H_FMT "\n", i, ptr_struct->entry_point[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "presigning           : " UH_FMT "\n", ptr_struct->presigning);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rsvd                 : " UH_FMT "\n", ptr_struct->rsvd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lfa_compatibility    : " UH_FMT "\n", ptr_struct->lfa_compatibility);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "encryption_params:\n");
	fs5_image_layout_crypto_encryption_params_print(&(ptr_struct->encryption_params), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bin_digest:\n");
	fs5_image_layout_u8_sha2_384_digest_print(&(ptr_struct->bin_digest), fd, indent_level + 1);
}

unsigned int fs5_image_layout_binary_section_metadata_size(void)
{
	return FS5_IMAGE_LAYOUT_BINARY_SECTION_METADATA_SIZE;
}

void fs5_image_layout_binary_section_metadata_dump(const struct fs5_image_layout_binary_section_metadata *ptr_struct, FILE *fd)
{
	fs5_image_layout_binary_section_metadata_print(ptr_struct, fd, 0);
}


void fs5_image_layout_csh_magic_pattern_pack(const struct fs5_image_layout_csh_magic_pattern *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 32, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->magic_pattern[i]);
	}
}

void fs5_image_layout_csh_magic_pattern_unpack(struct fs5_image_layout_csh_magic_pattern *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 32, 1);
		ptr_struct->magic_pattern[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_csh_magic_pattern_print(const struct fs5_image_layout_csh_magic_pattern *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_magic_pattern ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "magic_pattern_%03d   : " UH_FMT "\n", i, ptr_struct->magic_pattern[i]);
	}
}

unsigned int fs5_image_layout_csh_magic_pattern_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_MAGIC_PATTERN_SIZE;
}

void fs5_image_layout_csh_magic_pattern_dump(const struct fs5_image_layout_csh_magic_pattern *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_magic_pattern_print(ptr_struct, fd, 0);
}

void fs5_image_layout_vmod_status_pack(const struct fs5_image_layout_vmod_status *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->image_administrative_status);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tile_administrative_status);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->reserved);
}

void fs5_image_layout_vmod_status_unpack(struct fs5_image_layout_vmod_status *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->image_administrative_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->tile_administrative_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->reserved = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void fs5_image_layout_vmod_status_print(const struct fs5_image_layout_vmod_status *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_vmod_status ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_administrative_status : " UH_FMT "\n", ptr_struct->image_administrative_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_administrative_status : " UH_FMT "\n", ptr_struct->tile_administrative_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " UH_FMT "\n", ptr_struct->reserved);
}

unsigned int fs5_image_layout_vmod_status_size(void)
{
	return FS5_IMAGE_LAYOUT_VMOD_STATUS_SIZE;
}

void fs5_image_layout_vmod_status_dump(const struct fs5_image_layout_vmod_status *ptr_struct, FILE *fd)
{
	fs5_image_layout_vmod_status_print(ptr_struct, fd, 0);
}

void fs5_image_layout_csh_header_status_pack(const union fs5_image_layout_csh_header_status *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_csh_magic_pattern_pack(&(ptr_struct->magic_pattern), ptr_buff);
}

void fs5_image_layout_csh_header_status_unpack(union fs5_image_layout_csh_header_status *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_csh_magic_pattern_unpack(&(ptr_struct->magic_pattern), ptr_buff);
}

void fs5_image_layout_csh_header_status_print(const union fs5_image_layout_csh_header_status *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_header_status ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "magic_pattern:\n");
	fs5_image_layout_csh_magic_pattern_print(&(ptr_struct->magic_pattern), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vmod_status:\n");
	fs5_image_layout_vmod_status_print(&(ptr_struct->vmod_status), fd, indent_level + 1);
}

unsigned int fs5_image_layout_csh_header_status_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_HEADER_STATUS_SIZE;
}

void fs5_image_layout_csh_header_status_dump(const union fs5_image_layout_csh_header_status *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_header_status_print(ptr_struct, fd, 0);
}

void fs5_image_layout_csh_header_pack(const struct fs5_image_layout_csh_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_header_magic[i]);
	}
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_nv_pub_key_idx);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->struct_version_major);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->struct_version_minor);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reserved);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved1);
	offset = 96;
	fs5_image_layout_csh_header_status_pack(&(ptr_struct->csh_header_status), ptr_buff + offset / 8);
}

void fs5_image_layout_csh_header_unpack(struct fs5_image_layout_csh_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 128, 1);
		ptr_struct->u8_header_magic[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 56;
	ptr_struct->u8_nv_pub_key_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->struct_version_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->struct_version_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->reserved = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->reserved1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	fs5_image_layout_csh_header_status_unpack(&(ptr_struct->csh_header_status), ptr_buff + offset / 8);
}

void fs5_image_layout_csh_header_print(const struct fs5_image_layout_csh_header *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_header ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_header_magic_%03d : " UH_FMT "\n", i, ptr_struct->u8_header_magic[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_nv_pub_key_idx    : " UH_FMT "\n", ptr_struct->u8_nv_pub_key_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "struct_version_major : " UH_FMT "\n", ptr_struct->struct_version_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "struct_version_minor : " UH_FMT "\n", ptr_struct->struct_version_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " UH_FMT "\n", ptr_struct->reserved);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " U32H_FMT "\n", ptr_struct->reserved1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "csh_header_status:\n");
	fs5_image_layout_csh_header_status_print(&(ptr_struct->csh_header_status), fd, indent_level + 1);
}

unsigned int fs5_image_layout_csh_header_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_HEADER_SIZE;
}

void fs5_image_layout_csh_header_dump(const struct fs5_image_layout_csh_header *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_header_print(ptr_struct, fd, 0);
}

void fs5_image_layout_csh_metadata_pack(const struct fs5_image_layout_csh_metadata *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->reserved);
	offset = 32;
	fs5_image_layout_boot_component_ver_pack(&(ptr_struct->version), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 2048, 1);
		fs5_image_layout_csh_component_dependency_list_pack(&(ptr_struct->dependency_list[i]), ptr_buff + offset / 8);
	}
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_lifecycle);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(352, 128, i, 2048, 1);
		fs5_image_layout_u8_ecid_pack(&(ptr_struct->ecid[i]), ptr_buff + offset / 8);
	}
	offset = 872;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->reserved1);
	offset = 864;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_binaries);
	offset = 896;
	fs5_image_layout_u8_sha2_384_digest_pack(&(ptr_struct->binaries_list_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_csh_metadata_unpack(struct fs5_image_layout_csh_metadata *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->component_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->reserved = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	fs5_image_layout_boot_component_ver_unpack(&(ptr_struct->version), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 2048, 1);
		fs5_image_layout_csh_component_dependency_list_unpack(&(ptr_struct->dependency_list[i]), ptr_buff + offset / 8);
	}
	offset = 320;
	ptr_struct->fw_lifecycle = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(352, 128, i, 2048, 1);
		fs5_image_layout_u8_ecid_unpack(&(ptr_struct->ecid[i]), ptr_buff + offset / 8);
	}
	offset = 872;
	ptr_struct->reserved1 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 864;
	ptr_struct->num_of_binaries = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 896;
	fs5_image_layout_u8_sha2_384_digest_unpack(&(ptr_struct->binaries_list_digest), ptr_buff + offset / 8);
}

void fs5_image_layout_csh_metadata_print(const struct fs5_image_layout_csh_metadata *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_metadata ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_id         : " UH_FMT "\n", ptr_struct->component_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " UH_FMT "\n", ptr_struct->reserved);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version:\n");
	fs5_image_layout_boot_component_ver_print(&(ptr_struct->version), fd, indent_level + 1);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dependency_list_%03d:\n", i);
		fs5_image_layout_csh_component_dependency_list_print(&(ptr_struct->dependency_list[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_lifecycle         : " U32H_FMT "\n", ptr_struct->fw_lifecycle);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ecid_%03d:\n", i);
		fs5_image_layout_u8_ecid_print(&(ptr_struct->ecid[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " UH_FMT "\n", ptr_struct->reserved1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_binaries      : " UH_FMT "\n", ptr_struct->num_of_binaries);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "binaries_list_digest:\n");
	fs5_image_layout_u8_sha2_384_digest_print(&(ptr_struct->binaries_list_digest), fd, indent_level + 1);
}

unsigned int fs5_image_layout_csh_metadata_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_METADATA_SIZE;
}

void fs5_image_layout_csh_metadata_dump(const struct fs5_image_layout_csh_metadata *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_metadata_print(ptr_struct, fd, 0);
}


void fs5_image_layout_csh_metadata_nbu_pack(const struct fs5_image_layout_csh_metadata_nbu *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->nbu_subminor);
	offset = 32;
	fs5_image_layout_boot_component_ver_nbu_pack(&(ptr_struct->version), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 1408, 1);
		fs5_image_layout_csh_component_dependency_list_pack(&(ptr_struct->dependency_list[i]), ptr_buff + offset / 8);
	}
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_lifecycle);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(352, 128, i, 1408, 1);
		fs5_image_layout_u8_ecid_pack(&(ptr_struct->ecid[i]), ptr_buff + offset / 8);
	}
	offset = 872;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->reserved1);
	offset = 864;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_binaries);
	offset = 896;
	fs5_image_layout_u8_sha2_384_digest_pack(&(ptr_struct->binaries_list_digest), ptr_buff + offset / 8);
	offset = 1296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->issu_ver_major);
	offset = 1280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->issu_ver_minor);
	offset = 1328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->issu_notch);
	offset = 1320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->issuable);
	offset = 1312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->res);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(1368, 8, i, 1408, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->reserved2[i]);
	}
}

void fs5_image_layout_csh_metadata_nbu_unpack(struct fs5_image_layout_csh_metadata_nbu *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->component_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->nbu_subminor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	fs5_image_layout_boot_component_ver_nbu_unpack(&(ptr_struct->version), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 1408, 1);
		fs5_image_layout_csh_component_dependency_list_unpack(&(ptr_struct->dependency_list[i]), ptr_buff + offset / 8);
	}
	offset = 320;
	ptr_struct->fw_lifecycle = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(352, 128, i, 1408, 1);
		fs5_image_layout_u8_ecid_unpack(&(ptr_struct->ecid[i]), ptr_buff + offset / 8);
	}
	offset = 872;
	ptr_struct->reserved1 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 864;
	ptr_struct->num_of_binaries = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 896;
	fs5_image_layout_u8_sha2_384_digest_unpack(&(ptr_struct->binaries_list_digest), ptr_buff + offset / 8);
	offset = 1296;
	ptr_struct->issu_ver_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1280;
	ptr_struct->issu_ver_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1328;
	ptr_struct->issu_notch = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1320;
	ptr_struct->issuable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1312;
	ptr_struct->res = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(1368, 8, i, 1408, 1);
		ptr_struct->reserved2[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void fs5_image_layout_csh_metadata_nbu_print(const struct fs5_image_layout_csh_metadata_nbu *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_metadata_nbu ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "component_id         : " UH_FMT "\n", ptr_struct->component_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nbu_subminor         : " UH_FMT "\n", ptr_struct->nbu_subminor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version:\n");
	fs5_image_layout_boot_component_ver_nbu_print(&(ptr_struct->version), fd, indent_level + 1);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dependency_list_%03d:\n", i);
		fs5_image_layout_csh_component_dependency_list_print(&(ptr_struct->dependency_list[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_lifecycle         : " U32H_FMT "\n", ptr_struct->fw_lifecycle);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ecid_%03d:\n", i);
		fs5_image_layout_u8_ecid_print(&(ptr_struct->ecid[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved1            : " UH_FMT "\n", ptr_struct->reserved1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_binaries      : " UH_FMT "\n", ptr_struct->num_of_binaries);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "binaries_list_digest:\n");
	fs5_image_layout_u8_sha2_384_digest_print(&(ptr_struct->binaries_list_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_ver_major       : " UH_FMT "\n", ptr_struct->issu_ver_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_ver_minor       : " UH_FMT "\n", ptr_struct->issu_ver_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_notch           : " UH_FMT "\n", ptr_struct->issu_notch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issuable             : " UH_FMT "\n", ptr_struct->issuable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "res                  : " UH_FMT "\n", ptr_struct->res);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "reserved2_%03d       : " UH_FMT "\n", i, ptr_struct->reserved2[i]);
	}
}

unsigned int fs5_image_layout_csh_metadata_nbu_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_METADATA_NBU_SIZE;
}

void fs5_image_layout_csh_metadata_nbu_dump(const struct fs5_image_layout_csh_metadata_nbu *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_metadata_nbu_print(ptr_struct, fd, 0);
}

void fs5_image_layout_csh_signature_pack(const struct fs5_image_layout_csh_signature *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_crypto_ecdsa384_signature_pack(&(ptr_struct->ecdsa_signature), ptr_buff + offset / 8);
	for (i = 0; i < 435; ++i) {
		offset = adb2c_calc_array_field_address(768, 32, i, 14720, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->crypto_lms_sha192_h20_w4_signature[i]);
	}
	offset = 14688;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->reserved);
}

void fs5_image_layout_csh_signature_unpack(struct fs5_image_layout_csh_signature *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_crypto_ecdsa384_signature_unpack(&(ptr_struct->ecdsa_signature), ptr_buff + offset / 8);
	for (i = 0; i < 435; ++i) {
		offset = adb2c_calc_array_field_address(768, 32, i, 14720, 1);
		ptr_struct->crypto_lms_sha192_h20_w4_signature[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 14688;
	ptr_struct->reserved = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void fs5_image_layout_csh_signature_print(const struct fs5_image_layout_csh_signature *ptr_struct, FILE *fd, int indent_level)
{
	int i;
	
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_csh_signature ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecdsa_signature:\n");
	fs5_image_layout_crypto_ecdsa384_signature_print(&(ptr_struct->ecdsa_signature), fd, indent_level + 1);
	for (i = 0; i < 435; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "crypto_lms_sha192_h20_w4_signature_%03d : " U32H_FMT "\n", i, ptr_struct->crypto_lms_sha192_h20_w4_signature[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved             : " U32H_FMT "\n", ptr_struct->reserved);
}

unsigned int fs5_image_layout_csh_signature_size(void)
{
	return FS5_IMAGE_LAYOUT_CSH_SIGNATURE_SIZE;
}

void fs5_image_layout_csh_signature_dump(const struct fs5_image_layout_csh_signature *ptr_struct, FILE *fd)
{
	fs5_image_layout_csh_signature_print(ptr_struct, fd, 0);
}

void fs5_image_layout_component_signature_header_pack(const struct fs5_image_layout_component_signature_header *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_csh_header_pack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_csh_signature_pack(&(ptr_struct->nv_signature), ptr_buff + offset / 8);
	offset = 14848;
	fs5_image_layout_csh_signature_pack(&(ptr_struct->oem_signature), ptr_buff + offset / 8);
	offset = 29568;
	fs5_image_layout_csh_metadata_pack(&(ptr_struct->metadata), ptr_buff + offset / 8);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(31616, 1152, i, 68480, 1);
		fs5_image_layout_binary_section_metadata_pack(&(ptr_struct->binaries[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_component_signature_header_unpack(struct fs5_image_layout_component_signature_header *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_csh_header_unpack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_csh_signature_unpack(&(ptr_struct->nv_signature), ptr_buff + offset / 8);
	offset = 14848;
	fs5_image_layout_csh_signature_unpack(&(ptr_struct->oem_signature), ptr_buff + offset / 8);
	offset = 29568;
	fs5_image_layout_csh_metadata_unpack(&(ptr_struct->metadata), ptr_buff + offset / 8);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(31616, 1152, i, 68480, 1);
		fs5_image_layout_binary_section_metadata_unpack(&(ptr_struct->binaries[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_component_signature_header_print(const struct fs5_image_layout_component_signature_header *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_component_signature_header ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "header:\n");
	fs5_image_layout_csh_header_print(&(ptr_struct->header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_signature:\n");
	fs5_image_layout_csh_signature_print(&(ptr_struct->nv_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oem_signature:\n");
	fs5_image_layout_csh_signature_print(&(ptr_struct->oem_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "metadata:\n");
	fs5_image_layout_csh_metadata_print(&(ptr_struct->metadata), fd, indent_level + 1);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "binaries_%03d:\n", i);
		fs5_image_layout_binary_section_metadata_print(&(ptr_struct->binaries[i]), fd, indent_level + 1);
	}
}

unsigned int fs5_image_layout_component_signature_header_size(void)
{
	return FS5_IMAGE_LAYOUT_COMPONENT_SIGNATURE_HEADER_SIZE;
}

void fs5_image_layout_component_signature_header_dump(const struct fs5_image_layout_component_signature_header *ptr_struct, FILE *fd)
{
	fs5_image_layout_component_signature_header_print(ptr_struct, fd, 0);
}


void fs5_image_layout_component_signature_header_nbu_pack(const struct fs5_image_layout_component_signature_header_nbu *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_csh_header_pack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_csh_signature_pack(&(ptr_struct->nv_signature), ptr_buff + offset / 8);
	offset = 14848;
	fs5_image_layout_csh_signature_pack(&(ptr_struct->oem_signature), ptr_buff + offset / 8);
	offset = 29568;
	fs5_image_layout_csh_metadata_nbu_pack(&(ptr_struct->metadata), ptr_buff + offset / 8);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(30976, 1152, i, 67840, 1);
		fs5_image_layout_binary_section_metadata_pack(&(ptr_struct->binaries[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_component_signature_header_nbu_unpack(struct fs5_image_layout_component_signature_header_nbu *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	fs5_image_layout_csh_header_unpack(&(ptr_struct->header), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_csh_signature_unpack(&(ptr_struct->nv_signature), ptr_buff + offset / 8);
	offset = 14848;
	fs5_image_layout_csh_signature_unpack(&(ptr_struct->oem_signature), ptr_buff + offset / 8);
	offset = 29568;
	fs5_image_layout_csh_metadata_nbu_unpack(&(ptr_struct->metadata), ptr_buff + offset / 8);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(30976, 1152, i, 67840, 1);
		fs5_image_layout_binary_section_metadata_unpack(&(ptr_struct->binaries[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_component_signature_header_nbu_print(const struct fs5_image_layout_component_signature_header_nbu *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_component_signature_header_nbu ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "header:\n");
	fs5_image_layout_csh_header_print(&(ptr_struct->header), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_signature:\n");
	fs5_image_layout_csh_signature_print(&(ptr_struct->nv_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oem_signature:\n");
	fs5_image_layout_csh_signature_print(&(ptr_struct->oem_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "metadata:\n");
	fs5_image_layout_csh_metadata_nbu_print(&(ptr_struct->metadata), fd, indent_level + 1);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "binaries_%03d:\n", i);
		fs5_image_layout_binary_section_metadata_print(&(ptr_struct->binaries[i]), fd, indent_level + 1);
	}
}

unsigned int fs5_image_layout_component_signature_header_nbu_size(void)
{
	return FS5_IMAGE_LAYOUT_COMPONENT_SIGNATURE_HEADER_NBU_SIZE;
}

void fs5_image_layout_component_signature_header_nbu_dump(const struct fs5_image_layout_component_signature_header_nbu *ptr_struct, FILE *fd)
{
	fs5_image_layout_component_signature_header_nbu_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_header_pqc_pack(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 65536, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->u8_header_magic[i]);
	}
	offset = 32;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_u8_unsigned_padding_pack(&(ptr_struct->u8_unsigned_padding), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_crypto_signatures_v2_pack(&(ptr_struct->stage2_signature), ptr_buff + offset / 8);
	offset = 4224;
	fs5_image_layout_crypto_public_crypto_params_pack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 7296;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_key_id);
	offset = 7328;
	fs5_image_layout_u8_gen_padding_pqc_pack(&(ptr_struct->u8_gen_padding), ptr_buff + offset / 8);
	offset = 7680;
	fs5_image_layout_u8_salt_pack(&(ptr_struct->u8_salt2), ptr_buff + offset / 8);
	offset = 7808;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_ecid2), ptr_buff + offset / 8);
	offset = 7936;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_num_binaries2);
	offset = 7968;
	fs5_image_layout_u8_stage2_padding_pack(&(ptr_struct->u8_stage2_padding), ptr_buff + offset / 8);
	offset = 16256;
	fs5_image_layout_u8_derivation_label_check_pack(&(ptr_struct->u8_stage2_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(16384, 1280, i, 65536, 1);
		fs5_image_layout_bch_stage2_component_pack(&(ptr_struct->stage2_components[i]), ptr_buff + offset / 8);
	}
	offset = 26624;
	fs5_image_layout_u8_stage1_signature_pack(&(ptr_struct->u8_stage1_signature), ptr_buff + offset / 8);
	offset = 29696;
	fs5_image_layout_pqc_signatures_pack(&(ptr_struct->u8_stage1_pqc_signature), ptr_buff + offset / 8);
	offset = 54272;
	fs5_image_layout_u8_salt_pack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 54400;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_ecid1), ptr_buff + offset / 8);
	offset = 54528;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u32_num_binaries1);
	offset = 54560;
	fs5_image_layout_u8_stage1_res_lms_pack(&(ptr_struct->u8_stage1_res), ptr_buff + offset / 8);
	offset = 62080;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_uid_digest), ptr_buff + offset / 8);
	offset = 62592;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_notch_digest), ptr_buff + offset / 8);
	offset = 63104;
	fs5_image_layout_u8_derivation_label_check_pack(&(ptr_struct->u8_stage1_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(63232, 1152, i, 65536, 1);
		fs5_image_layout_u8_stage1_component_pack(&(ptr_struct->stage1_components[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_boot_component_header_pqc_unpack(struct fs5_image_layout_boot_component_header_pqc *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 65536, 1);
		ptr_struct->u8_header_magic[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 32;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_u8_unsigned_padding_unpack(&(ptr_struct->u8_unsigned_padding), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_crypto_signatures_v2_unpack(&(ptr_struct->stage2_signature), ptr_buff + offset / 8);
	offset = 4224;
	fs5_image_layout_crypto_public_crypto_params_unpack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 7296;
	ptr_struct->u32_key_id = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 7328;
	fs5_image_layout_u8_gen_padding_pqc_unpack(&(ptr_struct->u8_gen_padding), ptr_buff + offset / 8);
	offset = 7680;
	fs5_image_layout_u8_salt_unpack(&(ptr_struct->u8_salt2), ptr_buff + offset / 8);
	offset = 7808;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_ecid2), ptr_buff + offset / 8);
	offset = 7936;
	ptr_struct->u32_num_binaries2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 7968;
	fs5_image_layout_u8_stage2_padding_unpack(&(ptr_struct->u8_stage2_padding), ptr_buff + offset / 8);
	offset = 16256;
	fs5_image_layout_u8_derivation_label_check_unpack(&(ptr_struct->u8_stage2_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(16384, 1280, i, 65536, 1);
		fs5_image_layout_bch_stage2_component_unpack(&(ptr_struct->stage2_components[i]), ptr_buff + offset / 8);
	}
	offset = 26624;
	fs5_image_layout_u8_stage1_signature_unpack(&(ptr_struct->u8_stage1_signature), ptr_buff + offset / 8);
	offset = 29696;
	fs5_image_layout_pqc_signatures_unpack(&(ptr_struct->u8_stage1_pqc_signature), ptr_buff + offset / 8);
	offset = 54272;
	fs5_image_layout_u8_salt_unpack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 54400;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_ecid1), ptr_buff + offset / 8);
	offset = 54528;
	ptr_struct->u32_num_binaries1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 54560;
	fs5_image_layout_u8_stage1_res_lms_unpack(&(ptr_struct->u8_stage1_res), ptr_buff + offset / 8);
	offset = 62080;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_uid_digest), ptr_buff + offset / 8);
	offset = 62592;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_notch_digest), ptr_buff + offset / 8);
	offset = 63104;
	fs5_image_layout_u8_derivation_label_check_unpack(&(ptr_struct->u8_stage1_derivation_label_check), ptr_buff + offset / 8);
	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(63232, 1152, i, 65536, 1);
		fs5_image_layout_u8_stage1_component_unpack(&(ptr_struct->stage1_components[i]), ptr_buff + offset / 8);
	}
}

void fs5_image_layout_boot_component_header_pqc_print(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_header_pqc ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "u8_header_magic_%03d : " UH_FMT "\n", i, ptr_struct->u8_header_magic[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_unsigned_padding:\n");
	fs5_image_layout_u8_unsigned_padding_print(&(ptr_struct->u8_unsigned_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stage2_signature:\n");
	fs5_image_layout_crypto_signatures_v2_print(&(ptr_struct->stage2_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcp:\n");
	fs5_image_layout_crypto_public_crypto_params_print(&(ptr_struct->pcp), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_key_id           : " U32H_FMT "\n", ptr_struct->u32_key_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_gen_padding:\n");
	fs5_image_layout_u8_gen_padding_pqc_print(&(ptr_struct->u8_gen_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_salt2:\n");
	fs5_image_layout_u8_salt_print(&(ptr_struct->u8_salt2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ecid2:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_ecid2), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_num_binaries2    : " U32H_FMT "\n", ptr_struct->u32_num_binaries2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage2_padding:\n");
	fs5_image_layout_u8_stage2_padding_print(&(ptr_struct->u8_stage2_padding), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage2_derivation_label_check:\n");
	fs5_image_layout_u8_derivation_label_check_print(&(ptr_struct->u8_stage2_derivation_label_check), fd, indent_level + 1);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "stage2_components_%03d:\n", i);
		fs5_image_layout_bch_stage2_component_print(&(ptr_struct->stage2_components[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_signature:\n");
	fs5_image_layout_u8_stage1_signature_print(&(ptr_struct->u8_stage1_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_pqc_signature:\n");
	fs5_image_layout_pqc_signatures_print(&(ptr_struct->u8_stage1_pqc_signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_salt1:\n");
	fs5_image_layout_u8_salt_print(&(ptr_struct->u8_salt1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ecid1:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_ecid1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u32_num_binaries1    : " U32H_FMT "\n", ptr_struct->u32_num_binaries1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_res_lms:\n");
	fs5_image_layout_u8_stage1_res_lms_print(&(ptr_struct->u8_stage1_res), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_uid_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_uid_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_notch_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_notch_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_stage1_derivation_label_check:\n");
	fs5_image_layout_u8_derivation_label_check_print(&(ptr_struct->u8_stage1_derivation_label_check), fd, indent_level + 1);
	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "stage1_components_%03d:\n", i);
		fs5_image_layout_u8_stage1_component_print(&(ptr_struct->stage1_components[i]), fd, indent_level + 1);
	}
}

unsigned int fs5_image_layout_boot_component_header_pqc_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_PQC_SIZE;
}

void fs5_image_layout_boot_component_header_pqc_dump(const struct fs5_image_layout_boot_component_header_pqc *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_header_pqc_print(ptr_struct, fd, 0);
}

void fs5_image_layout_boot_component_table_pack(const struct fs5_image_layout_boot_component_table *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_header_magic);
	offset = 32;
	fs5_image_layout_u8_digest_pack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_crypto_public_crypto_params_pack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 3616;
	fs5_image_layout_crypto_signatures_pack(&(ptr_struct->signature), ptr_buff + offset / 8);
	offset = 36864;
	fs5_image_layout_u8_salt_pack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 36992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_header_magic_signed);
	offset = 37440;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_bch_info_start_block);
	offset = 37472;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_bch_info_start_page);
	offset = 38976;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ver);
	offset = 52480;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_ecid), ptr_buff + offset / 8);
	offset = 52960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_num_boot_chains);
	offset = 53120;
	fs5_image_layout_u8_ecid_pack(&(ptr_struct->u8_fskp_select), ptr_buff + offset / 8);
	offset = 53248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->u8_bf_bl_all_bits);
	offset = 56648;
	fs5_image_layout_u8_sec_provision_derivation_string_pack(&(ptr_struct->u8_sec_provision_derivation_string1), ptr_buff + offset / 8);
	offset = 56904;
	fs5_image_layout_u8_sec_provision_derivation_string_pack(&(ptr_struct->u8_sec_provision_derivation_string2), ptr_buff + offset / 8);
}

void fs5_image_layout_boot_component_table_unpack(struct fs5_image_layout_boot_component_table *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->u8_header_magic = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	fs5_image_layout_u8_digest_unpack(&(ptr_struct->u8_digest), ptr_buff + offset / 8);
	offset = 544;
	fs5_image_layout_crypto_public_crypto_params_unpack(&(ptr_struct->pcp), ptr_buff + offset / 8);
	offset = 3616;
	fs5_image_layout_crypto_signatures_unpack(&(ptr_struct->signature), ptr_buff + offset / 8);
	offset = 36864;
	fs5_image_layout_u8_salt_unpack(&(ptr_struct->u8_salt1), ptr_buff + offset / 8);
	offset = 36992;
	ptr_struct->u8_header_magic_signed = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 37440;
	ptr_struct->u8_bch_info_start_block = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 37472;
	ptr_struct->u8_bch_info_start_page = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 38976;
	ptr_struct->ver = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 52480;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_ecid), ptr_buff + offset / 8);
	offset = 52960;
	ptr_struct->u8_num_boot_chains = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 53120;
	fs5_image_layout_u8_ecid_unpack(&(ptr_struct->u8_fskp_select), ptr_buff + offset / 8);
	offset = 53248;
	ptr_struct->u8_bf_bl_all_bits = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 56648;
	fs5_image_layout_u8_sec_provision_derivation_string_unpack(&(ptr_struct->u8_sec_provision_derivation_string1), ptr_buff + offset / 8);
	offset = 56904;
	fs5_image_layout_u8_sec_provision_derivation_string_unpack(&(ptr_struct->u8_sec_provision_derivation_string2), ptr_buff + offset / 8);
}

void fs5_image_layout_boot_component_table_print(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_boot_component_table ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_header_magic      : " U32H_FMT "\n", ptr_struct->u8_header_magic);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_digest:\n");
	fs5_image_layout_u8_digest_print(&(ptr_struct->u8_digest), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcp:\n");
	fs5_image_layout_crypto_public_crypto_params_print(&(ptr_struct->pcp), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signature:\n");
	fs5_image_layout_crypto_signatures_print(&(ptr_struct->signature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_salt1:\n");
	fs5_image_layout_u8_salt_print(&(ptr_struct->u8_salt1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_header_magic_signed : " U32H_FMT "\n", ptr_struct->u8_header_magic_signed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_bch_info_start_block : " U32H_FMT "\n", ptr_struct->u8_bch_info_start_block);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_bch_info_start_page : " U32H_FMT "\n", ptr_struct->u8_bch_info_start_page);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ver                  : " U32H_FMT "\n", ptr_struct->ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_ecid:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_ecid), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_num_boot_chains   : " U32H_FMT "\n", ptr_struct->u8_num_boot_chains);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_fskp_select:\n");
	fs5_image_layout_u8_ecid_print(&(ptr_struct->u8_fskp_select), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_bf_bl_all_bits    : " U32H_FMT "\n", ptr_struct->u8_bf_bl_all_bits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_sec_provision_derivation_string1:\n");
	fs5_image_layout_u8_sec_provision_derivation_string_print(&(ptr_struct->u8_sec_provision_derivation_string1), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "u8_sec_provision_derivation_string2:\n");
	fs5_image_layout_u8_sec_provision_derivation_string_print(&(ptr_struct->u8_sec_provision_derivation_string2), fd, indent_level + 1);
}

unsigned int fs5_image_layout_boot_component_table_size(void)
{
	return FS5_IMAGE_LAYOUT_BOOT_COMPONENT_TABLE_SIZE;
}

void fs5_image_layout_boot_component_table_dump(const struct fs5_image_layout_boot_component_table *ptr_struct, FILE *fd)
{
	fs5_image_layout_boot_component_table_print(ptr_struct, fd, 0);
}

void fs5_image_layout_hw_pointers_gilboa_pack(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bct_pointer), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_bch_pointer), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_bl1_pointer), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_bch_pointer), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->reserved), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_bch_pointer), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->psc_fw_pointer), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->issu_notch_pointer), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->issu_main_uid_pointer), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_pack(&(ptr_struct->ncore_hashes_pointer), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_unpack(struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bct_pointer), ptr_buff + offset / 8);
	offset = 64;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->boot2_ptr), ptr_buff + offset / 8);
	offset = 128;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->toc_ptr), ptr_buff + offset / 8);
	offset = 192;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->tools_ptr), ptr_buff + offset / 8);
	offset = 256;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_bch_pointer), ptr_buff + offset / 8);
	offset = 320;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_bl1_pointer), ptr_buff + offset / 8);
	offset = 384;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_bch_pointer), ptr_buff + offset / 8);
	offset = 448;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->reserved), ptr_buff + offset / 8);
	offset = 512;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_bch_pointer), ptr_buff + offset / 8);
	offset = 576;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->psc_fw_pointer), ptr_buff + offset / 8);
	offset = 640;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->image_info_section_pointer), ptr_buff + offset / 8);
	offset = 704;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->issu_notch_pointer), ptr_buff + offset / 8);
	offset = 768;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->public_key_pointer), ptr_buff + offset / 8);
	offset = 832;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->issu_main_uid_pointer), ptr_buff + offset / 8);
	offset = 896;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->gcm_iv_delta_pointer), ptr_buff + offset / 8);
	offset = 960;
	fs5_image_layout_hw_pointer_entry_unpack(&(ptr_struct->ncore_hashes_pointer), ptr_buff + offset / 8);
}

void fs5_image_layout_hw_pointers_gilboa_print(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_hw_pointers_gilboa ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bct_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bct_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot2_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->boot2_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "toc_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->toc_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tools_ptr:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->tools_ptr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_bl1_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_bl1_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reserved:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->reserved), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_bch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_bch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psc_fw_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->psc_fw_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "image_info_section_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->image_info_section_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_notch_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->issu_notch_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "public_key_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->public_key_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_main_uid_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->issu_main_uid_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gcm_iv_delta_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->gcm_iv_delta_pointer), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ncore_hashes_pointer:\n");
	fs5_image_layout_hw_pointer_entry_print(&(ptr_struct->ncore_hashes_pointer), fd, indent_level + 1);
}

unsigned int fs5_image_layout_hw_pointers_gilboa_size(void)
{
	return FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE;
}

void fs5_image_layout_hw_pointers_gilboa_dump(const struct fs5_image_layout_hw_pointers_gilboa *ptr_struct, FILE *fd)
{
	fs5_image_layout_hw_pointers_gilboa_print(ptr_struct, fd, 0);
}

void fs5_image_layout_fs5_image_layout_Nodes_pack(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	fs5_image_layout_boot_component_header_pack(&(ptr_struct->boot_component_header), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_unpack(union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	fs5_image_layout_boot_component_header_unpack(&(ptr_struct->boot_component_header), ptr_buff);
}

void fs5_image_layout_fs5_image_layout_Nodes_print(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== fs5_image_layout_fs5_image_layout_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_component_header_pqc:\n");
	fs5_image_layout_boot_component_header_pqc_print(&(ptr_struct->boot_component_header_pqc), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_component_table:\n");
	fs5_image_layout_boot_component_table_print(&(ptr_struct->boot_component_table), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_pointers_gilboa:\n");
	fs5_image_layout_hw_pointers_gilboa_print(&(ptr_struct->hw_pointers_gilboa), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "boot_component_header:\n");
	fs5_image_layout_boot_component_header_print(&(ptr_struct->boot_component_header), fd, indent_level + 1);
}

unsigned int fs5_image_layout_fs5_image_layout_Nodes_size(void)
{
	return FS5_IMAGE_LAYOUT_FS5_IMAGE_LAYOUT_NODES_SIZE;
}

void fs5_image_layout_fs5_image_layout_Nodes_dump(const union fs5_image_layout_fs5_image_layout_Nodes *ptr_struct, FILE *fd)
{
	fs5_image_layout_fs5_image_layout_Nodes_print(ptr_struct, fd, 0);
}

