
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
         *** This file was generated at "2026-10-01 10:06:54"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils -o user/tools_layouts
         ***/
#include "reg_access_switch_layouts.h"

void reg_access_switch_ef_afe_snap_v1_ext_pack(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->term_attn_ctrl);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->dc_gain);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hf_gain);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lf_gain);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lf_pole);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mf_gain);
	offset = 10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mf_pole);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tah_amp_gain);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->adc_vref_val);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cdr_offset);
}

void reg_access_switch_ef_afe_snap_v1_ext_unpack(struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->term_attn_ctrl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 26;
	ptr_struct->dc_gain = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 18;
	ptr_struct->hf_gain = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->lf_gain = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 14;
	ptr_struct->lf_pole = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->mf_gain = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 10;
	ptr_struct->mf_pole = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 6;
	ptr_struct->tah_amp_gain = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->adc_vref_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 56;
	ptr_struct->cdr_offset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_ef_afe_snap_v1_ext_print(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_afe_snap_v1_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "term_attn_ctrl       : " UH_FMT "\n", ptr_struct->term_attn_ctrl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dc_gain              : " UH_FMT "\n", ptr_struct->dc_gain);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hf_gain              : " UH_FMT "\n", ptr_struct->hf_gain);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lf_gain              : " UH_FMT "\n", ptr_struct->lf_gain);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lf_pole              : " UH_FMT "\n", ptr_struct->lf_pole);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mf_gain              : " UH_FMT "\n", ptr_struct->mf_gain);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mf_pole              : " UH_FMT "\n", ptr_struct->mf_pole);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tah_amp_gain         : " UH_FMT "\n", ptr_struct->tah_amp_gain);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "adc_vref_val         : " UH_FMT "\n", ptr_struct->adc_vref_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_offset           : " UH_FMT "\n", ptr_struct->cdr_offset);
}

unsigned int reg_access_switch_ef_afe_snap_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_AFE_SNAP_V1_EXT_SIZE;
}

void reg_access_switch_ef_afe_snap_v1_ext_dump(const struct reg_access_switch_ef_afe_snap_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_afe_snap_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_pack(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_ef_afe_snap_v1_ext_pack(&(ptr_struct->afe_snap), ptr_buff + offset / 8);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ber_magnitude);
	offset = 84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ber_coeff);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ber_coeff_float);
	offset = 79;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->serdes_valid);
	offset = 78;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->phy_valid);
	offset = 77;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->meas_invalid);
}

void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_unpack(struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_ef_afe_snap_v1_ext_unpack(&(ptr_struct->afe_snap), ptr_buff + offset / 8);
	offset = 88;
	ptr_struct->ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 84;
	ptr_struct->ber_coeff = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->ber_coeff_float = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 79;
	ptr_struct->serdes_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 78;
	ptr_struct->phy_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 77;
	ptr_struct->meas_invalid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_print(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "afe_snap:\n");
	reg_access_switch_ef_afe_snap_v1_ext_print(&(ptr_struct->afe_snap), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_magnitude        : " UH_FMT "\n", ptr_struct->ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_coeff            : " UH_FMT "\n", ptr_struct->ber_coeff);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_coeff_float      : " UH_FMT "\n", ptr_struct->ber_coeff_float);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "serdes_valid         : " UH_FMT "\n", ptr_struct->serdes_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_valid            : " UH_FMT "\n", ptr_struct->phy_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "meas_invalid         : " UH_FMT "\n", ptr_struct->meas_invalid);
}

unsigned int reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_LT_X_FEQ_BER_ENTRY_V1_EXT_SIZE;
}

void reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_dump(const struct reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_hst_link_eth_enabled_ext_pack(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_eth_active);
}

void reg_access_switch_hst_link_eth_enabled_ext_unpack(struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_eth_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_hst_link_eth_enabled_ext_print(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_hst_link_eth_enabled_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_eth_active      : " U32H_FMT "\n", ptr_struct->link_eth_active);
}

unsigned int reg_access_switch_hst_link_eth_enabled_ext_size(void)
{
	return REG_ACCESS_SWITCH_HST_LINK_ETH_ENABLED_EXT_SIZE;
}

void reg_access_switch_hst_link_eth_enabled_ext_dump(const struct reg_access_switch_hst_link_eth_enabled_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_hst_link_eth_enabled_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_hst_link_ib_enabled_ext_pack(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_width_active);
}

void reg_access_switch_hst_link_ib_enabled_ext_unpack(struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->link_width_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_hst_link_ib_enabled_ext_print(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_hst_link_ib_enabled_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : %s (" UH_FMT ")\n", (ptr_struct->link_speed_active == 1 ? ("SDR") : ((ptr_struct->link_speed_active == 2 ? ("DDR") : ((ptr_struct->link_speed_active == 4 ? ("QDR") : ((ptr_struct->link_speed_active == 8 ? ("FDR10") : ((ptr_struct->link_speed_active == 16 ? ("FDR") : ((ptr_struct->link_speed_active == 32 ? ("EDR") : ((ptr_struct->link_speed_active == 64 ? ("HDR") : ((ptr_struct->link_speed_active == 128 ? ("NDR") : ((ptr_struct->link_speed_active == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
}

unsigned int reg_access_switch_hst_link_ib_enabled_ext_size(void)
{
	return REG_ACCESS_SWITCH_HST_LINK_IB_ENABLED_EXT_SIZE;
}

void reg_access_switch_hst_link_ib_enabled_ext_dump(const struct reg_access_switch_hst_link_ib_enabled_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_hst_link_ib_enabled_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_hst_link_nvlink_enabled_ext_pack(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_nvlink_active);
}

void reg_access_switch_hst_link_nvlink_enabled_ext_unpack(struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_nvlink_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_hst_link_nvlink_enabled_ext_print(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_hst_link_nvlink_enabled_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_nvlink_active   : " U32H_FMT "\n", ptr_struct->link_nvlink_active);
}

unsigned int reg_access_switch_hst_link_nvlink_enabled_ext_size(void)
{
	return REG_ACCESS_SWITCH_HST_LINK_NVLINK_ENABLED_EXT_SIZE;
}

void reg_access_switch_hst_link_nvlink_enabled_ext_dump(const struct reg_access_switch_hst_link_nvlink_enabled_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_hst_link_nvlink_enabled_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pd_link_eth_enabled_ext_pack(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_eth_active);
}

void reg_access_switch_pd_link_eth_enabled_ext_unpack(struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_eth_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pd_link_eth_enabled_ext_print(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pd_link_eth_enabled_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_eth_active      : " U32H_FMT "\n", ptr_struct->link_eth_active);
}

unsigned int reg_access_switch_pd_link_eth_enabled_ext_size(void)
{
	return REG_ACCESS_SWITCH_PD_LINK_ETH_ENABLED_EXT_SIZE;
}

void reg_access_switch_pd_link_eth_enabled_ext_dump(const struct reg_access_switch_pd_link_eth_enabled_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pd_link_eth_enabled_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pd_link_ib_enabled_ext_pack(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_width_active);
}

void reg_access_switch_pd_link_ib_enabled_ext_unpack(struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->link_width_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pd_link_ib_enabled_ext_print(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pd_link_ib_enabled_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : %s (" UH_FMT ")\n", (ptr_struct->link_speed_active == 1 ? ("SDR") : ((ptr_struct->link_speed_active == 2 ? ("DDR") : ((ptr_struct->link_speed_active == 4 ? ("QDR") : ((ptr_struct->link_speed_active == 8 ? ("FDR10") : ((ptr_struct->link_speed_active == 16 ? ("FDR") : ((ptr_struct->link_speed_active == 32 ? ("EDR") : ((ptr_struct->link_speed_active == 64 ? ("HDR") : ((ptr_struct->link_speed_active == 128 ? ("NDR") : ((ptr_struct->link_speed_active == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
}

unsigned int reg_access_switch_pd_link_ib_enabled_ext_size(void)
{
	return REG_ACCESS_SWITCH_PD_LINK_IB_ENABLED_EXT_SIZE;
}

void reg_access_switch_pd_link_ib_enabled_ext_dump(const struct reg_access_switch_pd_link_ib_enabled_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pd_link_ib_enabled_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_c2p_link_enabled_eth_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->core_to_phy_link_eth_enabled);
}

void reg_access_switch_pddr_c2p_link_enabled_eth_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->core_to_phy_link_eth_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_c2p_link_enabled_eth_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_c2p_link_enabled_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_eth_enabled : " U32H_FMT "\n", ptr_struct->core_to_phy_link_eth_enabled);
}

unsigned int reg_access_switch_pddr_c2p_link_enabled_eth_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_ETH_EXT_SIZE;
}

void reg_access_switch_pddr_c2p_link_enabled_eth_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_c2p_link_enabled_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_c2p_link_enabled_ib_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->core_to_phy_link_proto_enabled);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->core_to_phy_link_width_enabled);
}

void reg_access_switch_pddr_c2p_link_enabled_ib_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->core_to_phy_link_proto_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->core_to_phy_link_width_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pddr_c2p_link_enabled_ib_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_c2p_link_enabled_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_proto_enabled : %s (" UH_FMT ")\n", (ptr_struct->core_to_phy_link_proto_enabled == 1 ? ("SDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 2 ? ("DDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 4 ? ("QDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 8 ? ("FDR10") : ((ptr_struct->core_to_phy_link_proto_enabled == 16 ? ("FDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 32 ? ("EDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 64 ? ("HDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 128 ? ("NDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->core_to_phy_link_proto_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_width_enabled : " UH_FMT "\n", ptr_struct->core_to_phy_link_width_enabled);
}

unsigned int reg_access_switch_pddr_c2p_link_enabled_ib_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_IB_EXT_SIZE;
}

void reg_access_switch_pddr_c2p_link_enabled_ib_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_c2p_link_enabled_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_pack(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->core_to_phy_link_nvlink_enabled);
}

void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_unpack(struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->core_to_phy_link_nvlink_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_print(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_c2p_link_enabled_nvlink_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_nvlink_enabled : " U32H_FMT "\n", ptr_struct->core_to_phy_link_nvlink_enabled);
}

unsigned int reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_C2P_LINK_ENABLED_NVLINK_EXT_SIZE;
}

void reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_dump(const struct reg_access_switch_pddr_c2p_link_enabled_nvlink_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_cable_cap_eth_ext_pack(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cable_ext_eth_proto_cap);
}

void reg_access_switch_pddr_cable_cap_eth_ext_unpack(struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->cable_ext_eth_proto_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_cable_cap_eth_ext_print(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_cable_cap_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_ext_eth_proto_cap : " U32H_FMT "\n", ptr_struct->cable_ext_eth_proto_cap);
}

unsigned int reg_access_switch_pddr_cable_cap_eth_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_CABLE_CAP_ETH_EXT_SIZE;
}

void reg_access_switch_pddr_cable_cap_eth_ext_dump(const struct reg_access_switch_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_cable_cap_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_cable_cap_ib_ext_pack(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cable_link_speed_cap);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cable_link_width_cap);
}

void reg_access_switch_pddr_cable_cap_ib_ext_unpack(struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->cable_link_speed_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->cable_link_width_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pddr_cable_cap_ib_ext_print(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_cable_cap_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_link_speed_cap : %s (" UH_FMT ")\n", (ptr_struct->cable_link_speed_cap == 1 ? ("SDR") : ((ptr_struct->cable_link_speed_cap == 2 ? ("DDR") : ((ptr_struct->cable_link_speed_cap == 4 ? ("QDR") : ((ptr_struct->cable_link_speed_cap == 8 ? ("FDR10") : ((ptr_struct->cable_link_speed_cap == 16 ? ("FDR") : ((ptr_struct->cable_link_speed_cap == 32 ? ("EDR") : ((ptr_struct->cable_link_speed_cap == 64 ? ("HDR") : ((ptr_struct->cable_link_speed_cap == 128 ? ("NDR") : ((ptr_struct->cable_link_speed_cap == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->cable_link_speed_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_link_width_cap : " UH_FMT "\n", ptr_struct->cable_link_width_cap);
}

unsigned int reg_access_switch_pddr_cable_cap_ib_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_CABLE_CAP_IB_EXT_SIZE;
}

void reg_access_switch_pddr_cable_cap_ib_ext_dump(const struct reg_access_switch_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_cable_cap_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_cable_cap_nvlink_ext_pack(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cable_nvlink_proto_cap);
}

void reg_access_switch_pddr_cable_cap_nvlink_ext_unpack(struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->cable_nvlink_proto_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_cable_cap_nvlink_ext_print(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_cable_cap_nvlink_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_nvlink_proto_cap : " U32H_FMT "\n", ptr_struct->cable_nvlink_proto_cap);
}

unsigned int reg_access_switch_pddr_cable_cap_nvlink_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_CABLE_CAP_NVLINK_EXT_SIZE;
}

void reg_access_switch_pddr_cable_cap_nvlink_ext_dump(const struct reg_access_switch_pddr_cable_cap_nvlink_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_cable_cap_nvlink_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_active_eth_ext_pack(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_eth_active);
}

void reg_access_switch_pddr_link_active_eth_ext_unpack(struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_eth_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_link_active_eth_ext_print(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_active_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_eth_active      : " U32H_FMT "\n", ptr_struct->link_eth_active);
}

unsigned int reg_access_switch_pddr_link_active_eth_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_ETH_EXT_SIZE;
}

void reg_access_switch_pddr_link_active_eth_ext_dump(const struct reg_access_switch_pddr_link_active_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_active_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_active_ib_ext_pack(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_width_active);
}

void reg_access_switch_pddr_link_active_ib_ext_unpack(struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->link_width_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pddr_link_active_ib_ext_print(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_active_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : %s (" UH_FMT ")\n", (ptr_struct->link_speed_active == 1 ? ("SDR") : ((ptr_struct->link_speed_active == 2 ? ("DDR") : ((ptr_struct->link_speed_active == 4 ? ("QDR") : ((ptr_struct->link_speed_active == 8 ? ("FDR10") : ((ptr_struct->link_speed_active == 16 ? ("FDR") : ((ptr_struct->link_speed_active == 32 ? ("EDR") : ((ptr_struct->link_speed_active == 64 ? ("HDR") : ((ptr_struct->link_speed_active == 128 ? ("NDR") : ((ptr_struct->link_speed_active == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
}

unsigned int reg_access_switch_pddr_link_active_ib_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_IB_EXT_SIZE;
}

void reg_access_switch_pddr_link_active_ib_ext_dump(const struct reg_access_switch_pddr_link_active_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_active_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_active_nvlink_ext_pack(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_nvlink_active);
}

void reg_access_switch_pddr_link_active_nvlink_ext_unpack(struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_nvlink_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_link_active_nvlink_ext_print(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_active_nvlink_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_nvlink_active   : " U32H_FMT "\n", ptr_struct->link_nvlink_active);
}

unsigned int reg_access_switch_pddr_link_active_nvlink_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_ACTIVE_NVLINK_EXT_SIZE;
}

void reg_access_switch_pddr_link_active_nvlink_ext_dump(const struct reg_access_switch_pddr_link_active_nvlink_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_active_nvlink_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_monitor_opcode_ext_pack(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->monitor_opcode);
}

void reg_access_switch_pddr_monitor_opcode_ext_unpack(struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->monitor_opcode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pddr_monitor_opcode_ext_print(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_monitor_opcode_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "monitor_opcode       : " UH_FMT "\n", ptr_struct->monitor_opcode);
}

unsigned int reg_access_switch_pddr_monitor_opcode_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_MONITOR_OPCODE_EXT_SIZE;
}

void reg_access_switch_pddr_monitor_opcode_ext_dump(const struct reg_access_switch_pddr_monitor_opcode_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_monitor_opcode_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_manager_link_eth_enabled);
}

void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->phy_manager_link_eth_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_phy_manager_link_enabled_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_eth_enabled : " U32H_FMT "\n", ptr_struct->phy_manager_link_eth_enabled);
}

unsigned int reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_ETH_EXT_SIZE;
}

void reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->phy_manager_link_proto_enabled);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->phy_manager_link_width_enabled);
}

void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->phy_manager_link_proto_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->phy_manager_link_width_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_phy_manager_link_enabled_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_proto_enabled : " UH_FMT "\n", ptr_struct->phy_manager_link_proto_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_width_enabled : " UH_FMT "\n", ptr_struct->phy_manager_link_width_enabled);
}

unsigned int reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_IB_EXT_SIZE;
}

void reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_pack(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_manager_link_nvlink_enabled);
}

void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_unpack(struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->phy_manager_link_nvlink_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_print(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_nvlink_enabled : " U32H_FMT "\n", ptr_struct->phy_manager_link_nvlink_enabled);
}

unsigned int reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_PHY_MANAGER_LINK_ENABLED_NVLINK_EXT_SIZE;
}

void reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_dump(const struct reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_pack(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(0, 96, i, 544, 1);
		reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_pack(&(ptr_struct->iter_table[i]), ptr_buff + offset / 8);
	}
	offset = 508;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->stores_done);
	offset = 504;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->winner_idx);
	offset = 543;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->protocol_violation);
	offset = 539;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->violation_idx);
	offset = 537;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->violation_type);
	offset = 536;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_applied);
	offset = 532;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_fail_stage);
}

void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_unpack(struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(0, 96, i, 544, 1);
		reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_unpack(&(ptr_struct->iter_table[i]), ptr_buff + offset / 8);
	}
	offset = 508;
	ptr_struct->stores_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 504;
	ptr_struct->winner_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 543;
	ptr_struct->protocol_violation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 539;
	ptr_struct->violation_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 537;
	ptr_struct->violation_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 536;
	ptr_struct->force_applied = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 532;
	ptr_struct->last_fail_stage = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_print(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_lt_x_feq_ber_db_v1_ext ========\n");

	for (i = 0; i < 5; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "iter_table_%03d:\n", i);
		reg_access_switch_ef_lt_x_feq_ber_entry_v1_ext_print(&(ptr_struct->iter_table[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stores_done          : " UH_FMT "\n", ptr_struct->stores_done);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "winner_idx           : " UH_FMT "\n", ptr_struct->winner_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "protocol_violation   : " UH_FMT "\n", ptr_struct->protocol_violation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "violation_idx        : " UH_FMT "\n", ptr_struct->violation_idx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "violation_type       : %s (" UH_FMT ")\n", (ptr_struct->violation_type == 0 ? ("none") : ((ptr_struct->violation_type == 1 ? ("no_serdes_stamp") : ((ptr_struct->violation_type == 2 ? ("no_phy_stamp") : ((ptr_struct->violation_type == 3 ? ("both") : ("unknown")))))))), ptr_struct->violation_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_applied        : " UH_FMT "\n", ptr_struct->force_applied);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_fail_stage      : %s (" UH_FMT ")\n", (ptr_struct->last_fail_stage == 0 ? ("ok") : ((ptr_struct->last_fail_stage == 1 ? ("reserved_1") : ((ptr_struct->last_fail_stage == 2 ? ("phy_update_rejected") : ((ptr_struct->last_fail_stage == 3 ? ("force_no_valid_entry") : ((ptr_struct->last_fail_stage == 4 ? ("reserved_4") : ((ptr_struct->last_fail_stage == 5 ? ("phy_bad_index_overflow") : ("unknown")))))))))))), ptr_struct->last_fail_stage);
}

unsigned int reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_LT_X_FEQ_BER_DB_V1_EXT_SIZE;
}

void reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_dump(const struct reg_access_switch_ef_lt_x_feq_ber_db_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ef_lt_x_port_info_v1_ext_pack(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->ltx_restore_count);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->ltx_total_rounds_cnt);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_ber_meas_done);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->auto_reversals_applied);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ltx_limiter_allow);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ltx_reached_max_retry);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->entered_ltx_flow);
	offset = 14;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ber_based_in_progress);
}

void reg_access_switch_ef_lt_x_port_info_v1_ext_unpack(struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->ltx_restore_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 23;
	ptr_struct->ltx_total_rounds_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 19;
	ptr_struct->num_ber_meas_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->auto_reversals_applied = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->ltx_limiter_allow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->ltx_reached_max_retry = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 15;
	ptr_struct->entered_ltx_flow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 14;
	ptr_struct->ber_based_in_progress = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_ef_lt_x_port_info_v1_ext_print(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_lt_x_port_info_v1_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_restore_count    : " UH_FMT "\n", ptr_struct->ltx_restore_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_total_rounds_cnt : " UH_FMT "\n", ptr_struct->ltx_total_rounds_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_ber_meas_done    : " UH_FMT "\n", ptr_struct->num_ber_meas_done);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "auto_reversals_applied : " UH_FMT "\n", ptr_struct->auto_reversals_applied);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_limiter_allow    : " UH_FMT "\n", ptr_struct->ltx_limiter_allow);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_reached_max_retry : " UH_FMT "\n", ptr_struct->ltx_reached_max_retry);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "entered_ltx_flow     : " UH_FMT "\n", ptr_struct->entered_ltx_flow);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_based_in_progress : " UH_FMT "\n", ptr_struct->ber_based_in_progress);
}

unsigned int reg_access_switch_ef_lt_x_port_info_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_LT_X_PORT_INFO_V1_EXT_SIZE;
}

void reg_access_switch_ef_lt_x_port_info_v1_ext_dump(const struct reg_access_switch_ef_lt_x_port_info_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_lt_x_port_info_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_pack(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->train_ctl_state);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_mc_mode);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_tp_mode);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lane_training_status);
	offset = 13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->polarity_correction);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_disable);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->remote_rts);
	offset = 10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->local_rts);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->remote_rx_ready);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->local_rx_ready);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->remote_tf_lock);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->local_tf_lock);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_ok);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->invert_to_done);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->training_failure);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->bcnl_rx_block_cnt);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->bcnl_tx_block_cnt);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bcnl_msg_rx_fail);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->bcnl_msg_tx_fail);
}

void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_unpack(struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->train_ctl_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 22;
	ptr_struct->local_mc_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 20;
	ptr_struct->local_tp_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 18;
	ptr_struct->lane_training_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 13;
	ptr_struct->polarity_correction = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 12;
	ptr_struct->tx_disable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 11;
	ptr_struct->remote_rts = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 10;
	ptr_struct->local_rts = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 9;
	ptr_struct->remote_rx_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->local_rx_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 7;
	ptr_struct->remote_tf_lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->local_tf_lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->rx_ok = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->invert_to_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->training_failure = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->bcnl_rx_block_cnt = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 38;
	ptr_struct->bcnl_tx_block_cnt = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 33;
	ptr_struct->bcnl_msg_rx_fail = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->bcnl_msg_tx_fail = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_print(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_pddr_apsu_lane_data_v1_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "train_ctl_state      : " UH_FMT "\n", ptr_struct->train_ctl_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_mc_mode        : " UH_FMT "\n", ptr_struct->local_mc_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_tp_mode        : " UH_FMT "\n", ptr_struct->local_tp_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_training_status : " UH_FMT "\n", ptr_struct->lane_training_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "polarity_correction  : " UH_FMT "\n", ptr_struct->polarity_correction);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_disable           : " UH_FMT "\n", ptr_struct->tx_disable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_rts           : " UH_FMT "\n", ptr_struct->remote_rts);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_rts            : " UH_FMT "\n", ptr_struct->local_rts);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_rx_ready      : " UH_FMT "\n", ptr_struct->remote_rx_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_rx_ready       : " UH_FMT "\n", ptr_struct->local_rx_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_tf_lock       : " UH_FMT "\n", ptr_struct->remote_tf_lock);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_tf_lock        : " UH_FMT "\n", ptr_struct->local_tf_lock);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_ok                : " UH_FMT "\n", ptr_struct->rx_ok);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "invert_to_done       : " UH_FMT "\n", ptr_struct->invert_to_done);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "training_failure     : " UH_FMT "\n", ptr_struct->training_failure);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bcnl_rx_block_cnt    : " UH_FMT "\n", ptr_struct->bcnl_rx_block_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bcnl_tx_block_cnt    : " UH_FMT "\n", ptr_struct->bcnl_tx_block_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bcnl_msg_rx_fail     : " UH_FMT "\n", ptr_struct->bcnl_msg_rx_fail);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bcnl_msg_tx_fail     : " UH_FMT "\n", ptr_struct->bcnl_msg_tx_fail);
}

unsigned int reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_PDDR_APSU_LANE_DATA_V1_EXT_SIZE;
}

void reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_dump(const struct reg_access_switch_ef_pddr_apsu_lane_data_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ltx_logger_ext_pack(const struct reg_access_switch_ltx_logger_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ltx_status);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_fail_reason);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_count);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->effective_errors);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->highest_non_zero_hist);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->raw_ber_magnitude);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->prbs_ber_magnitude);
	offset = 53;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_fail_count);
	offset = 43;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mantissa);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mantissa_float);
}

void reg_access_switch_ltx_logger_ext_unpack(struct reg_access_switch_ltx_logger_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->ltx_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->ltx_fail_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 21;
	ptr_struct->ltx_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 20;
	ptr_struct->effective_errors = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 15;
	ptr_struct->highest_non_zero_hist = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 7;
	ptr_struct->raw_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->prbs_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 53;
	ptr_struct->ltx_retry_fail_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 43;
	ptr_struct->raw_ber_mantissa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 39;
	ptr_struct->raw_ber_mantissa_float = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_ltx_logger_ext_print(const struct reg_access_switch_ltx_logger_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ltx_logger_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_status           : " UH_FMT "\n", ptr_struct->ltx_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_fail_reason      : " UH_FMT "\n", ptr_struct->ltx_fail_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_count      : " UH_FMT "\n", ptr_struct->ltx_retry_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "effective_errors     : " UH_FMT "\n", ptr_struct->effective_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "highest_non_zero_hist : " UH_FMT "\n", ptr_struct->highest_non_zero_hist);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_magnitude    : " UH_FMT "\n", ptr_struct->raw_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_ber_magnitude   : " UH_FMT "\n", ptr_struct->prbs_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_fail_count : " UH_FMT "\n", ptr_struct->ltx_retry_fail_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mantissa     : " UH_FMT "\n", ptr_struct->raw_ber_mantissa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mantissa_float : " UH_FMT "\n", ptr_struct->raw_ber_mantissa_float);
}

unsigned int reg_access_switch_ltx_logger_ext_size(void)
{
	return REG_ACCESS_SWITCH_LTX_LOGGER_EXT_SIZE;
}

void reg_access_switch_ltx_logger_ext_dump(const struct reg_access_switch_ltx_logger_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ltx_logger_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_cable_cap_nvlink_ext_pack(&(ptr_struct->pddr_cable_cap_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_cable_cap_nvlink_ext_unpack(&(ptr_struct->pddr_cable_cap_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cable_cap_eth_ext:\n");
	reg_access_switch_pddr_cable_cap_eth_ext_print(&(ptr_struct->pddr_cable_cap_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cable_cap_ib_ext:\n");
	reg_access_switch_pddr_cable_cap_ib_ext_print(&(ptr_struct->pddr_cable_cap_ib_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cable_cap_nvlink_ext:\n");
	reg_access_switch_pddr_cable_cap_nvlink_ext_print(&(ptr_struct->pddr_cable_cap_nvlink_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_CABLE_PROTO_CAP_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_cable_proto_cap_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_pack(&(ptr_struct->pddr_c2p_link_enabled_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_unpack(&(ptr_struct->pddr_c2p_link_enabled_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_c2p_link_enabled_eth_ext:\n");
	reg_access_switch_pddr_c2p_link_enabled_eth_ext_print(&(ptr_struct->pddr_c2p_link_enabled_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_c2p_link_enabled_ib_ext:\n");
	reg_access_switch_pddr_c2p_link_enabled_ib_ext_print(&(ptr_struct->pddr_c2p_link_enabled_ib_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_c2p_link_enabled_nvlink_ext:\n");
	reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_print(&(ptr_struct->pddr_c2p_link_enabled_nvlink_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_CORE_TO_PHY_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_link_active_nvlink_ext_pack(&(ptr_struct->pddr_link_active_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_link_active_nvlink_ext_unpack(&(ptr_struct->pddr_link_active_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_link_active_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_active_eth_ext:\n");
	reg_access_switch_pddr_link_active_eth_ext_print(&(ptr_struct->pddr_link_active_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_active_ib_ext:\n");
	reg_access_switch_pddr_link_active_ib_ext_print(&(ptr_struct->pddr_link_active_ib_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_active_nvlink_ext:\n");
	reg_access_switch_pddr_link_active_nvlink_ext_print(&(ptr_struct->pddr_link_active_nvlink_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_link_active_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_LINK_ACTIVE_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_link_active_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_link_active_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pd_link_ib_enabled_ext_pack(&(ptr_struct->pd_link_ib_enabled_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pd_link_ib_enabled_ext_unpack(&(ptr_struct->pd_link_ib_enabled_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_link_eth_enabled_ext:\n");
	reg_access_switch_pd_link_eth_enabled_ext_print(&(ptr_struct->pd_link_eth_enabled_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_link_ib_enabled_ext:\n");
	reg_access_switch_pd_link_ib_enabled_ext_print(&(ptr_struct->pd_link_ib_enabled_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PD_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_pd_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_hst_link_nvlink_enabled_ext_pack(&(ptr_struct->hst_link_nvlink_enabled_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_hst_link_nvlink_enabled_ext_unpack(&(ptr_struct->hst_link_nvlink_enabled_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_link_eth_enabled_ext:\n");
	reg_access_switch_hst_link_eth_enabled_ext_print(&(ptr_struct->hst_link_eth_enabled_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_link_ib_enabled_ext:\n");
	reg_access_switch_hst_link_ib_enabled_ext_print(&(ptr_struct->hst_link_ib_enabled_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_link_nvlink_enabled_ext:\n");
	reg_access_switch_hst_link_nvlink_enabled_ext_print(&(ptr_struct->hst_link_nvlink_enabled_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PHY_HST_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_phy_hst_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_pack(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_pack(&(ptr_struct->pddr_phy_manager_link_enabled_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_unpack(union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_unpack(&(ptr_struct->pddr_phy_manager_link_enabled_nvlink_ext), ptr_buff);
}

void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_manager_link_enabled_eth_ext:\n");
	reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_print(&(ptr_struct->pddr_phy_manager_link_enabled_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_manager_link_enabled_ib_ext:\n");
	reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_print(&(ptr_struct->pddr_phy_manager_link_enabled_ib_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_manager_link_enabled_nvlink_ext:\n");
	reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_print(&(ptr_struct->pddr_phy_manager_link_enabled_nvlink_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_PHY_MANAGER_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_dump(const union reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_pack(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_monitor_opcode_ext_pack(&(ptr_struct->pddr_monitor_opcode_ext), ptr_buff);
}

void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_unpack(union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_monitor_opcode_ext_unpack(&(ptr_struct->pddr_monitor_opcode_ext), ptr_buff);
}

void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_print(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_monitor_opcode_ext:\n");
	reg_access_switch_pddr_monitor_opcode_ext_print(&(ptr_struct->pddr_monitor_opcode_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_TROUBLESHOOTING_PAGE_STATUS_OPCODE_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_dump(const union reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_troubleshooting_page_status_opcode_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void reg_access_switch_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int reg_access_switch_uint64_size(void)
{
	return REG_ACCESS_SWITCH_UINT64_SIZE;
}

void reg_access_switch_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	reg_access_switch_uint64_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_CVB_ext_pack(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->cvb_data_index);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->cnt_out);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tav_cvb_voltage_msb);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->selector_cause);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->selector);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cvb_voltage);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->voltage_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->tav_cvb_voltage);
}

void reg_access_switch_MRFV_CVB_ext_unpack(struct reg_access_switch_MRFV_CVB_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->cvb_data_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 6;
	ptr_struct->cnt_out = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
	offset = 2;
	ptr_struct->tav_cvb_voltage_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1;
	ptr_struct->selector_cause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->selector = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->cvb_voltage = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 45;
	ptr_struct->voltage_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->tav_cvb_voltage = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void reg_access_switch_MRFV_CVB_ext_print(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_CVB_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cvb_data_index       : " UH_FMT "\n", ptr_struct->cvb_data_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnt_out              : " UH_FMT "\n", ptr_struct->cnt_out);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tav_cvb_voltage_msb  : " UH_FMT "\n", ptr_struct->tav_cvb_voltage_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "selector_cause       : " UH_FMT "\n", ptr_struct->selector_cause);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "selector             : " UH_FMT "\n", ptr_struct->selector);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cvb_voltage          : " UH_FMT "\n", ptr_struct->cvb_voltage);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "voltage_type         : " UH_FMT "\n", ptr_struct->voltage_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tav_cvb_voltage      : " UH_FMT "\n", ptr_struct->tav_cvb_voltage);
}

unsigned int reg_access_switch_MRFV_CVB_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_CVB_EXT_SIZE;
}

void reg_access_switch_MRFV_CVB_ext_dump(const struct reg_access_switch_MRFV_CVB_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_CVB_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_PVS_MAIN_ext_pack(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->pvs_main_data);
}

void reg_access_switch_MRFV_PVS_MAIN_ext_unpack(struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	ptr_struct->pvs_main_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
}

void reg_access_switch_MRFV_PVS_MAIN_ext_print(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_PVS_MAIN_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs_main_data        : " UH_FMT "\n", ptr_struct->pvs_main_data);
}

unsigned int reg_access_switch_MRFV_PVS_MAIN_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_PVS_MAIN_EXT_SIZE;
}

void reg_access_switch_MRFV_PVS_MAIN_ext_dump(const struct reg_access_switch_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_PVS_MAIN_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_PVS_TILE_ext_pack(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->pvs_tile_data);
}

void reg_access_switch_MRFV_PVS_TILE_ext_unpack(struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	ptr_struct->pvs_tile_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
}

void reg_access_switch_MRFV_PVS_TILE_ext_print(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_PVS_TILE_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs_tile_data        : " UH_FMT "\n", ptr_struct->pvs_tile_data);
}

unsigned int reg_access_switch_MRFV_PVS_TILE_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_PVS_TILE_EXT_SIZE;
}

void reg_access_switch_MRFV_PVS_TILE_ext_dump(const struct reg_access_switch_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_PVS_TILE_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_RAW_AND_VALUE_ext_pack(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->raw_fuses_highest_bit);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->value_valid);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_fuses);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->value_exponent);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 26, (u_int32_t)ptr_struct->value_base);
}

void reg_access_switch_MRFV_RAW_AND_VALUE_ext_unpack(struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->raw_fuses_highest_bit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 0;
	ptr_struct->value_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->raw_fuses = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 90;
	ptr_struct->value_exponent = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 64;
	ptr_struct->value_base = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 26);
}

void reg_access_switch_MRFV_RAW_AND_VALUE_ext_print(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_RAW_AND_VALUE_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_fuses_highest_bit : " UH_FMT "\n", ptr_struct->raw_fuses_highest_bit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "value_valid          : " UH_FMT "\n", ptr_struct->value_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_fuses            : " U32H_FMT "\n", ptr_struct->raw_fuses);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "value_exponent       : " UH_FMT "\n", ptr_struct->value_exponent);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "value_base           : " UH_FMT "\n", ptr_struct->value_base);
}

unsigned int reg_access_switch_MRFV_RAW_AND_VALUE_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_RAW_AND_VALUE_EXT_SIZE;
}

void reg_access_switch_MRFV_RAW_AND_VALUE_ext_dump(const struct reg_access_switch_MRFV_RAW_AND_VALUE_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_RAW_AND_VALUE_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_ULT_ext_pack(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_1);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_2);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_3);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_4);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_5);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_6);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_7);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_lot_digit_8);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_y);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_x);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ult_wafer_number);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->ult_err_detection);
}

void reg_access_switch_MRFV_ULT_ext_unpack(struct reg_access_switch_MRFV_ULT_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->ult_lot_digit_1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->ult_lot_digit_2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->ult_lot_digit_3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->ult_lot_digit_4 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->ult_lot_digit_5 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ult_lot_digit_6 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->ult_lot_digit_7 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->ult_lot_digit_8 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->ult_y = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->ult_x = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->ult_wafer_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->ult_err_detection = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_switch_MRFV_ULT_ext_print(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_ULT_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_1      : " UH_FMT "\n", ptr_struct->ult_lot_digit_1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_2      : " UH_FMT "\n", ptr_struct->ult_lot_digit_2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_3      : " UH_FMT "\n", ptr_struct->ult_lot_digit_3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_4      : " UH_FMT "\n", ptr_struct->ult_lot_digit_4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_5      : " UH_FMT "\n", ptr_struct->ult_lot_digit_5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_6      : " UH_FMT "\n", ptr_struct->ult_lot_digit_6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_7      : " UH_FMT "\n", ptr_struct->ult_lot_digit_7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_lot_digit_8      : " UH_FMT "\n", ptr_struct->ult_lot_digit_8);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_y                : " UH_FMT "\n", ptr_struct->ult_y);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_x                : " UH_FMT "\n", ptr_struct->ult_x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_wafer_number     : " UH_FMT "\n", ptr_struct->ult_wafer_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ult_err_detection    : " UH_FMT "\n", ptr_struct->ult_err_detection);
}

unsigned int reg_access_switch_MRFV_ULT_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_ULT_EXT_SIZE;
}

void reg_access_switch_MRFV_ULT_ext_dump(const struct reg_access_switch_MRFV_ULT_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_ULT_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_command_payload_ext_pack(const struct reg_access_switch_command_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 65; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_command_payload_ext_unpack(struct reg_access_switch_command_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 65; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 2080, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_command_payload_ext_print(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_command_payload_ext ========\n");

	for (i = 0; i < 65; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_command_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_COMMAND_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_command_payload_ext_dump(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_command_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_crspace_access_payload_ext_pack(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_crspace_access_payload_ext_unpack(struct reg_access_switch_crspace_access_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 0;
	ptr_struct->address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_crspace_access_payload_ext_print(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_crspace_access_payload_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U32H_FMT "\n", ptr_struct->address);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_crspace_access_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_CRSPACE_ACCESS_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_crspace_access_payload_ext_dump(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_crspace_access_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_device_info_ext_pack(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_id);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lc_pwr_on);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->thermal_sd);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flash_owner);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->uses_flash);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_major);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_sub_minor);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fw_minor);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_cmd_write_size_supp);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_cmd_read_size_supp);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type_name[i]);
	}
}

void reg_access_switch_mddq_device_info_ext_unpack(struct reg_access_switch_mddq_device_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->flash_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 3;
	ptr_struct->lc_pwr_on = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->thermal_sd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->flash_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->uses_flash = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->device_type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->fw_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->fw_sub_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->fw_minor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 120;
	ptr_struct->max_cmd_write_size_supp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->max_cmd_read_size_supp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 256, 1);
		ptr_struct->device_type_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_mddq_device_info_ext_print(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_device_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_id             : " UH_FMT "\n", ptr_struct->flash_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lc_pwr_on            : " UH_FMT "\n", ptr_struct->lc_pwr_on);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "thermal_sd           : " UH_FMT "\n", ptr_struct->thermal_sd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flash_owner          : " UH_FMT "\n", ptr_struct->flash_owner);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uses_flash           : " UH_FMT "\n", ptr_struct->uses_flash);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_major             : " UH_FMT "\n", ptr_struct->fw_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_sub_minor         : " UH_FMT "\n", ptr_struct->fw_sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_minor             : " UH_FMT "\n", ptr_struct->fw_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cmd_write_size_supp : " UH_FMT "\n", ptr_struct->max_cmd_write_size_supp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cmd_read_size_supp : " UH_FMT "\n", ptr_struct->max_cmd_read_size_supp);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "device_type_name_%03d : " UH_FMT "\n", i, ptr_struct->device_type_name[i]);
	}
}

unsigned int reg_access_switch_mddq_device_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_DEVICE_INFO_EXT_SIZE;
}

void reg_access_switch_mddq_device_info_ext_dump(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_device_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_slot_info_ext_pack(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->active);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lc_ready);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sr_valid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->provisioned);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ini_file_version);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_revision);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->card_type);
}

void reg_access_switch_mddq_slot_info_ext_unpack(struct reg_access_switch_mddq_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 4;
	ptr_struct->active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->lc_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->sr_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->provisioned = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->ini_file_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->hw_revision = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 88;
	ptr_struct->card_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_mddq_slot_info_ext_print(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_slot_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active               : " UH_FMT "\n", ptr_struct->active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lc_ready             : " UH_FMT "\n", ptr_struct->lc_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sr_valid             : " UH_FMT "\n", ptr_struct->sr_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "provisioned          : " UH_FMT "\n", ptr_struct->provisioned);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_version     : " UH_FMT "\n", ptr_struct->ini_file_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_revision          : " UH_FMT "\n", ptr_struct->hw_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "card_type            : " UH_FMT "\n", ptr_struct->card_type);
}

unsigned int reg_access_switch_mddq_slot_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_SLOT_INFO_EXT_SIZE;
}

void reg_access_switch_mddq_slot_info_ext_dump(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_slot_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_slot_name_ext_pack(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->slot_ascii_name[i]);
	}
}

void reg_access_switch_mddq_slot_name_ext_unpack(struct reg_access_switch_mddq_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 256, 1);
		ptr_struct->slot_ascii_name[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_switch_mddq_slot_name_ext_print(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_slot_name_ext ========\n");

	for (i = 0; i < 20; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "slot_ascii_name_%03d : " UH_FMT "\n", i, ptr_struct->slot_ascii_name[i]);
	}
}

unsigned int reg_access_switch_mddq_slot_name_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_SLOT_NAME_EXT_SIZE;
}

void reg_access_switch_mddq_slot_name_ext_dump(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_slot_name_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_module_latched_flag_info_ext_pack(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_los_cap);
	offset = 9;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dp_fw_fault);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mod_fw_fault);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vcc_flags);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->temp_flags);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_ad_eq_fault);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_cdr_lol);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_los);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_fault);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_power_lo_war);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_power_hi_war);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_power_lo_al);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_power_hi_al);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_bias_lo_war);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_bias_hi_war);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_bias_lo_al);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_bias_hi_al);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_cdr_lol);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_los);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_power_lo_war);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_power_hi_war);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_power_lo_al);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_power_hi_al);
	offset = 216;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_output_valid_change);
	offset = 196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->laser_source_flag_in_use_msb);
	offset = 195;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_warning_flag);
	offset = 194;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_warning_flag);
	offset = 193;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_fault_flag);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_fault_flag);
	offset = 287;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_bias_lo_war);
	offset = 286;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_bias_lo_war);
	offset = 285;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_bias_hi_war);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_bias_hi_war);
	offset = 283;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_bias_lo_al);
	offset = 282;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_bias_lo_al);
	offset = 281;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_bias_hi_al);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_bias_hi_al);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->laser_source_flag_in_use);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->optical_engine_flag_in_use);
	offset = 303;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_temp_lo_war);
	offset = 302;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_temp_lo_war);
	offset = 301;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_temp_hi_war);
	offset = 300;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_temp_hi_war);
	offset = 299;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_temp_lo_al);
	offset = 298;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_temp_lo_al);
	offset = 297;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_temp_hi_al);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_temp_hi_al);
	offset = 295;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_opt_pwr_lo_war);
	offset = 294;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_opt_pwr_lo_war);
	offset = 293;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_opt_pwr_hi_war);
	offset = 292;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_opt_pwr_hi_war);
	offset = 291;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_opt_pwr_lo_al);
	offset = 290;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_opt_pwr_lo_al);
	offset = 289;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_opt_pwr_hi_al);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_opt_pwr_hi_al);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_input_power_lo_war);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_input_power_hi_war);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_input_power_lo_al);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_input_power_hi_al);
	offset = 376;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_temp_lo_war);
	offset = 368;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_temp_hi_war);
	offset = 360;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_temp_lo_al);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_temp_hi_al);
}

void reg_access_switch_module_latched_flag_info_ext_unpack(struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->rx_los_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 9;
	ptr_struct->dp_fw_fault = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->mod_fw_fault = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->vcc_flags = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->temp_flags = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->tx_ad_eq_fault = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->tx_cdr_lol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->tx_los = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->tx_fault = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->tx_power_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->tx_power_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->tx_power_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->tx_power_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->tx_bias_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->tx_bias_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->tx_bias_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->tx_bias_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 136;
	ptr_struct->rx_cdr_lol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->rx_los = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 184;
	ptr_struct->rx_power_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 176;
	ptr_struct->rx_power_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 168;
	ptr_struct->rx_power_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 160;
	ptr_struct->rx_power_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 216;
	ptr_struct->rx_output_valid_change = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 196;
	ptr_struct->laser_source_flag_in_use_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 195;
	ptr_struct->laser2_warning_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 194;
	ptr_struct->laser_warning_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 193;
	ptr_struct->laser2_fault_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 192;
	ptr_struct->laser_fault_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 287;
	ptr_struct->laser2_bias_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 286;
	ptr_struct->laser_bias_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 285;
	ptr_struct->laser2_bias_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 284;
	ptr_struct->laser_bias_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 283;
	ptr_struct->laser2_bias_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 282;
	ptr_struct->laser_bias_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 281;
	ptr_struct->laser2_bias_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 280;
	ptr_struct->laser_bias_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 256;
	ptr_struct->laser_source_flag_in_use = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 304;
	ptr_struct->optical_engine_flag_in_use = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 303;
	ptr_struct->laser2_temp_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 302;
	ptr_struct->laser_temp_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 301;
	ptr_struct->laser2_temp_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 300;
	ptr_struct->laser_temp_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 299;
	ptr_struct->laser2_temp_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 298;
	ptr_struct->laser_temp_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 297;
	ptr_struct->laser2_temp_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 296;
	ptr_struct->laser_temp_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 295;
	ptr_struct->laser2_opt_pwr_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 294;
	ptr_struct->laser_opt_pwr_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 293;
	ptr_struct->laser2_opt_pwr_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 292;
	ptr_struct->laser_opt_pwr_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 291;
	ptr_struct->laser2_opt_pwr_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 290;
	ptr_struct->laser_opt_pwr_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 289;
	ptr_struct->laser2_opt_pwr_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 288;
	ptr_struct->laser_opt_pwr_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 344;
	ptr_struct->els_input_power_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 336;
	ptr_struct->els_input_power_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 328;
	ptr_struct->els_input_power_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 320;
	ptr_struct->els_input_power_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 376;
	ptr_struct->lane_temp_lo_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 368;
	ptr_struct->lane_temp_hi_war = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 360;
	ptr_struct->lane_temp_lo_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 352;
	ptr_struct->lane_temp_hi_al = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_module_latched_flag_info_ext_print(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_module_latched_flag_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_los_cap           : " UH_FMT "\n", ptr_struct->rx_los_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dp_fw_fault          : " UH_FMT "\n", ptr_struct->dp_fw_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mod_fw_fault         : " UH_FMT "\n", ptr_struct->mod_fw_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vcc_flags            : %s (" UH_FMT ")\n", (ptr_struct->vcc_flags == 1 ? ("high_vcc_alarm") : ((ptr_struct->vcc_flags == 2 ? ("low_vcc_alarm") : ((ptr_struct->vcc_flags == 4 ? ("high_vcc_warning") : ((ptr_struct->vcc_flags == 8 ? ("low_vcc_warning") : ("unknown")))))))), ptr_struct->vcc_flags);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temp_flags           : %s (" UH_FMT ")\n", (ptr_struct->temp_flags == 1 ? ("high_temp_alarm") : ((ptr_struct->temp_flags == 2 ? ("low_temp_alarm") : ((ptr_struct->temp_flags == 4 ? ("high_temp_warning") : ((ptr_struct->temp_flags == 8 ? ("low_temp_warning") : ("unknown")))))))), ptr_struct->temp_flags);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ad_eq_fault       : " UH_FMT "\n", ptr_struct->tx_ad_eq_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_cdr_lol           : " UH_FMT "\n", ptr_struct->tx_cdr_lol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_los               : " UH_FMT "\n", ptr_struct->tx_los);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_fault             : " UH_FMT "\n", ptr_struct->tx_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lo_war      : " UH_FMT "\n", ptr_struct->tx_power_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_hi_war      : " UH_FMT "\n", ptr_struct->tx_power_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lo_al       : " UH_FMT "\n", ptr_struct->tx_power_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_hi_al       : " UH_FMT "\n", ptr_struct->tx_power_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lo_war       : " UH_FMT "\n", ptr_struct->tx_bias_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_hi_war       : " UH_FMT "\n", ptr_struct->tx_bias_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lo_al        : " UH_FMT "\n", ptr_struct->tx_bias_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_hi_al        : " UH_FMT "\n", ptr_struct->tx_bias_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_cdr_lol           : " UH_FMT "\n", ptr_struct->rx_cdr_lol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_los               : " UH_FMT "\n", ptr_struct->rx_los);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lo_war      : " UH_FMT "\n", ptr_struct->rx_power_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_hi_war      : " UH_FMT "\n", ptr_struct->rx_power_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lo_al       : " UH_FMT "\n", ptr_struct->rx_power_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_hi_al       : " UH_FMT "\n", ptr_struct->rx_power_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_output_valid_change : " UH_FMT "\n", ptr_struct->rx_output_valid_change);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_source_flag_in_use_msb : " UH_FMT "\n", ptr_struct->laser_source_flag_in_use_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_warning_flag  : " UH_FMT "\n", ptr_struct->laser2_warning_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_warning_flag   : " UH_FMT "\n", ptr_struct->laser_warning_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_fault_flag    : " UH_FMT "\n", ptr_struct->laser2_fault_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_fault_flag     : " UH_FMT "\n", ptr_struct->laser_fault_flag);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_bias_lo_war   : " UH_FMT "\n", ptr_struct->laser2_bias_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_bias_lo_war    : " UH_FMT "\n", ptr_struct->laser_bias_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_bias_hi_war   : " UH_FMT "\n", ptr_struct->laser2_bias_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_bias_hi_war    : " UH_FMT "\n", ptr_struct->laser_bias_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_bias_lo_al    : " UH_FMT "\n", ptr_struct->laser2_bias_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_bias_lo_al     : " UH_FMT "\n", ptr_struct->laser_bias_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_bias_hi_al    : " UH_FMT "\n", ptr_struct->laser2_bias_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_bias_hi_al     : " UH_FMT "\n", ptr_struct->laser_bias_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_source_flag_in_use : %s (" UH_FMT ")\n", (ptr_struct->laser_source_flag_in_use == 1 ? ("global_alarm_for_laser") : ((ptr_struct->laser_source_flag_in_use == 2 ? ("global_warning_for_laser") : ((ptr_struct->laser_source_flag_in_use == 4 ? ("laser_bias_hi_al_cap") : ((ptr_struct->laser_source_flag_in_use == 8 ? ("laser_bias_lo_al_cap") : ((ptr_struct->laser_source_flag_in_use == 16 ? ("laser_bias_hi_war_cap") : ((ptr_struct->laser_source_flag_in_use == 32 ? ("laser_bias_lo_war_cap") : ((ptr_struct->laser_source_flag_in_use == 64 ? ("laser_opt_pwr_hi_al_cap") : ((ptr_struct->laser_source_flag_in_use == 128 ? ("laser_opt_pwr_lo_al_cap") : ((ptr_struct->laser_source_flag_in_use == 256 ? ("laser_opt_pwr_hi_war_cap") : ((ptr_struct->laser_source_flag_in_use == 512 ? ("laser_opt_pwr_lo_war_cap") : ((ptr_struct->laser_source_flag_in_use == 1024 ? ("laser_temp_hi_al") : ((ptr_struct->laser_source_flag_in_use == 2048 ? ("laser_temp_lo_al") : ((ptr_struct->laser_source_flag_in_use == 4096 ? ("laser_temp_hi_war") : ((ptr_struct->laser_source_flag_in_use == 8192 ? ("laser_temp_lo_war") : ((ptr_struct->laser_source_flag_in_use == 16384 ? ("global_alarm_for_laser2") : ((ptr_struct->laser_source_flag_in_use == 32768 ? ("global_warning_for_laser2") : ((ptr_struct->laser_source_flag_in_use == 65536 ? ("laser2_bias_hi_al_cap") : ((ptr_struct->laser_source_flag_in_use == 131072 ? ("laser2_bias_lo_al_cap") : ((ptr_struct->laser_source_flag_in_use == 262144 ? ("laser2_bias_hi_war_cap") : ((ptr_struct->laser_source_flag_in_use == 524288 ? ("laser2_bias_lo_war_cap") : ((ptr_struct->laser_source_flag_in_use == 1048576 ? ("laser2_opt_pwr_hi_al_cap") : ((ptr_struct->laser_source_flag_in_use == 2097152 ? ("laser2_opt_pwr_lo_al_cap") : ((ptr_struct->laser_source_flag_in_use == 4194304 ? ("laser2_opt_pwr_hi_war_cap") : ((ptr_struct->laser_source_flag_in_use == 8388608 ? ("laser2_opt_pwr_lo_war_cap") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->laser_source_flag_in_use);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "optical_engine_flag_in_use : %s (" UH_FMT ")\n", (ptr_struct->optical_engine_flag_in_use == 1 ? ("els_input_power_hi_al") : ((ptr_struct->optical_engine_flag_in_use == 2 ? ("els_input_power_lo_al") : ((ptr_struct->optical_engine_flag_in_use == 4 ? ("els_input_power_hi_war") : ((ptr_struct->optical_engine_flag_in_use == 8 ? ("els_input_power_lo_war") : ((ptr_struct->optical_engine_flag_in_use == 16 ? ("lane_temp_hi_al") : ((ptr_struct->optical_engine_flag_in_use == 32 ? ("lane_temp_lo_al") : ((ptr_struct->optical_engine_flag_in_use == 64 ? ("lane_temp_hi_war") : ((ptr_struct->optical_engine_flag_in_use == 128 ? ("lane_temp_lo_war") : ("unknown")))))))))))))))), ptr_struct->optical_engine_flag_in_use);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_temp_lo_war   : " UH_FMT "\n", ptr_struct->laser2_temp_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_temp_lo_war    : " UH_FMT "\n", ptr_struct->laser_temp_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_temp_hi_war   : " UH_FMT "\n", ptr_struct->laser2_temp_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_temp_hi_war    : " UH_FMT "\n", ptr_struct->laser_temp_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_temp_lo_al    : " UH_FMT "\n", ptr_struct->laser2_temp_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_temp_lo_al     : " UH_FMT "\n", ptr_struct->laser_temp_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_temp_hi_al    : " UH_FMT "\n", ptr_struct->laser2_temp_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_temp_hi_al     : " UH_FMT "\n", ptr_struct->laser_temp_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_opt_pwr_lo_war : " UH_FMT "\n", ptr_struct->laser2_opt_pwr_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_opt_pwr_lo_war : " UH_FMT "\n", ptr_struct->laser_opt_pwr_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_opt_pwr_hi_war : " UH_FMT "\n", ptr_struct->laser2_opt_pwr_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_opt_pwr_hi_war : " UH_FMT "\n", ptr_struct->laser_opt_pwr_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_opt_pwr_lo_al : " UH_FMT "\n", ptr_struct->laser2_opt_pwr_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_opt_pwr_lo_al  : " UH_FMT "\n", ptr_struct->laser_opt_pwr_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_opt_pwr_hi_al : " UH_FMT "\n", ptr_struct->laser2_opt_pwr_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_opt_pwr_hi_al  : " UH_FMT "\n", ptr_struct->laser_opt_pwr_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_input_power_lo_war : " UH_FMT "\n", ptr_struct->els_input_power_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_input_power_hi_war : " UH_FMT "\n", ptr_struct->els_input_power_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_input_power_lo_al : " UH_FMT "\n", ptr_struct->els_input_power_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_input_power_hi_al : " UH_FMT "\n", ptr_struct->els_input_power_hi_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_temp_lo_war     : " UH_FMT "\n", ptr_struct->lane_temp_lo_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_temp_hi_war     : " UH_FMT "\n", ptr_struct->lane_temp_hi_war);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_temp_lo_al      : " UH_FMT "\n", ptr_struct->lane_temp_lo_al);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_temp_hi_al      : " UH_FMT "\n", ptr_struct->lane_temp_hi_al);
}

unsigned int reg_access_switch_module_latched_flag_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MODULE_LATCHED_FLAG_INFO_EXT_SIZE;
}

void reg_access_switch_module_latched_flag_info_ext_dump(const struct reg_access_switch_module_latched_flag_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_module_latched_flag_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_apsu_info_page_ext_pack(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->rts_update_state);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->training_status);
	offset = 15;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rts_status);
	offset = 13;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->isl_ready);
	offset = 57;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->remote_type);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->peer_detected);
	offset = 53;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rts_rx_all);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rts_tx_all);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->remote_host_iud);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->uses_recovered_clock);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 96, i, 1984, 1);
		reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_pack(&(ptr_struct->lane_data[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pddr_apsu_info_page_ext_unpack(struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->rts_update_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 18;
	ptr_struct->training_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 15;
	ptr_struct->rts_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 13;
	ptr_struct->isl_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 57;
	ptr_struct->remote_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 54;
	ptr_struct->peer_detected = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 53;
	ptr_struct->rts_rx_all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 52;
	ptr_struct->rts_tx_all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 36;
	ptr_struct->remote_host_iud = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->uses_recovered_clock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(64, 96, i, 1984, 1);
		reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_unpack(&(ptr_struct->lane_data[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pddr_apsu_info_page_ext_print(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_apsu_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rts_update_state     : " UH_FMT "\n", ptr_struct->rts_update_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "training_status      : " UH_FMT "\n", ptr_struct->training_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rts_status           : " UH_FMT "\n", ptr_struct->rts_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "isl_ready            : " UH_FMT "\n", ptr_struct->isl_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_type          : " UH_FMT "\n", ptr_struct->remote_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "peer_detected        : " UH_FMT "\n", ptr_struct->peer_detected);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rts_rx_all           : " UH_FMT "\n", ptr_struct->rts_rx_all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rts_tx_all           : " UH_FMT "\n", ptr_struct->rts_tx_all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_host_iud      : " UH_FMT "\n", ptr_struct->remote_host_iud);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uses_recovered_clock : " UH_FMT "\n", ptr_struct->uses_recovered_clock);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "lane_data_%03d:\n", i);
		reg_access_switch_ef_pddr_apsu_lane_data_v1_ext_print(&(ptr_struct->lane_data[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_pddr_apsu_info_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_APSU_INFO_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_apsu_info_page_ext_dump(const struct reg_access_switch_pddr_apsu_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_apsu_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_cpo_module_page_ext_pack(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1344, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_sn[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1344, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->laser_source_sn[i]);
	}
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->laser_source_fw_version);
	offset = 314;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->els_laser_index);
	offset = 308;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->oe_index);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_index);
	offset = 348;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane7_to_els_logical_laser);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane6_to_els_logical_laser);
	offset = 340;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane5_to_els_logical_laser);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane4_to_els_logical_laser);
	offset = 332;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane3_to_els_logical_laser);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane2_to_els_logical_laser);
	offset = 324;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane1_to_els_logical_laser);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane0_to_els_logical_laser);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_lane_mask);
}

void reg_access_switch_pddr_cpo_module_page_ext_unpack(struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1344, 1);
		ptr_struct->oe_sn[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1344, 1);
		ptr_struct->laser_source_sn[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 256;
	ptr_struct->laser_source_fw_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 314;
	ptr_struct->els_laser_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 308;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->oe_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 288;
	ptr_struct->els_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 348;
	ptr_struct->oe_lane7_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 344;
	ptr_struct->oe_lane6_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 340;
	ptr_struct->oe_lane5_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 336;
	ptr_struct->oe_lane4_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 332;
	ptr_struct->oe_lane3_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 328;
	ptr_struct->oe_lane2_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 324;
	ptr_struct->oe_lane1_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->oe_lane0_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->module_lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_pddr_cpo_module_page_ext_print(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_cpo_module_page_ext ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "oe_sn_%03d           : " U32H_FMT "\n", i, ptr_struct->oe_sn[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "laser_source_sn_%03d : " U32H_FMT "\n", i, ptr_struct->laser_source_sn[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_source_fw_version : " U32H_FMT "\n", ptr_struct->laser_source_fw_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_laser_index      : " UH_FMT "\n", ptr_struct->els_laser_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_index             : " UH_FMT "\n", ptr_struct->oe_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_index            : " UH_FMT "\n", ptr_struct->els_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane7_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane7_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane6_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane6_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane5_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane5_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane4_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane4_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane3_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane3_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane2_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane2_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane1_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane1_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane0_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane0_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_lane_mask     : " UH_FMT "\n", ptr_struct->module_lane_mask);
}

unsigned int reg_access_switch_pddr_cpo_module_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_CPO_MODULE_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_cpo_module_page_ext_dump(const struct reg_access_switch_pddr_cpo_module_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_cpo_module_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_pack(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 544, i, 1120, 1);
		reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_pack(&(ptr_struct->lane_lt_x_feq_ber[i]), ptr_buff + offset / 8);
	}
	offset = 1088;
	reg_access_switch_ef_lt_x_port_info_v1_ext_pack(&(ptr_struct->port_info), ptr_buff + offset / 8);
}

void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_unpack(struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 2; ++i) {
		offset = adb2c_calc_array_field_address(0, 544, i, 1120, 1);
		reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_unpack(&(ptr_struct->lane_lt_x_feq_ber[i]), ptr_buff + offset / 8);
	}
	offset = 1088;
	reg_access_switch_ef_lt_x_port_info_v1_ext_unpack(&(ptr_struct->port_info), ptr_buff + offset / 8);
}

void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_print(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_fec_measure_ltx_nvl5_ext ========\n");

	for (i = 0; i < 2; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "lane_lt_x_feq_ber_%03d:\n", i);
		reg_access_switch_ef_lt_x_feq_ber_db_v1_ext_print(&(ptr_struct->lane_lt_x_feq_ber[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_info:\n");
	reg_access_switch_ef_lt_x_port_info_v1_ext_print(&(ptr_struct->port_info), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_FEC_MEASURE_LTX_NVL5_EXT_SIZE;
}

void reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_dump(const struct reg_access_switch_pddr_fec_measure_ltx_nvl5_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_down_info_page_ext_pack(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->down_blame);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->down_intent);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_reason_opcode);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->recovery_entry_reason);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->remote_reason_opcode);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->e2e_reason_opcode);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ts1_opcode);
	offset = 108;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->l1_failure_reason);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_recovery_state);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_symbol_ber_alarms);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_raw_ber_magnitude);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_raw_ber_coef);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cons_raw_norm_ber);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_raw_ber_magnitude);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_raw_ber_coef);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_raw_ber_magnitude);
	offset = 164;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_raw_ber_coef);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_raw_ber_alarms);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_eff_ber_alarms);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_down_to_disable);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_down_to_rx_loss);
	offset = 312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_eff_ber_magnitude);
	offset = 308;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_eff_ber_coef);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_eff_ber_magnitude);
	offset = 292;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_eff_ber_coef);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cons_eff_norm_ber);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_eff_ber_magnitude);
	offset = 340;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_eff_ber_coef);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_symbol_ber_magnitude);
	offset = 324;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_symbol_ber_coef);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cons_symbol_norm_ber);
	offset = 376;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_symbol_ber_magnitude);
	offset = 372;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_symbol_ber_coef);
	offset = 360;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_symbol_ber_magnitude);
	offset = 356;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_symbol_ber_coef);
	offset = 408;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hi_ser_counter);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pcs_phy_state_latched);
	offset = 472;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->apsu_restart_reason_opcode);
}

void reg_access_switch_pddr_link_down_info_page_ext_unpack(struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->down_blame = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->down_intent = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->local_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->recovery_entry_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->remote_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->e2e_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->ts1_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 108;
	ptr_struct->l1_failure_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 104;
	ptr_struct->last_recovery_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->num_of_symbol_ber_alarms = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 136;
	ptr_struct->last_raw_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 132;
	ptr_struct->last_raw_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->cons_raw_norm_ber = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 184;
	ptr_struct->max_raw_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 180;
	ptr_struct->max_raw_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 168;
	ptr_struct->min_raw_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 164;
	ptr_struct->min_raw_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 208;
	ptr_struct->num_of_raw_ber_alarms = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->num_of_eff_ber_alarms = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->time_to_link_down_to_disable = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->time_to_link_down_to_rx_loss = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 312;
	ptr_struct->min_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 308;
	ptr_struct->min_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->last_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 292;
	ptr_struct->last_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->cons_eff_norm_ber = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 344;
	ptr_struct->max_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 340;
	ptr_struct->max_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 328;
	ptr_struct->max_symbol_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 324;
	ptr_struct->max_symbol_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->cons_symbol_norm_ber = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 376;
	ptr_struct->min_symbol_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 372;
	ptr_struct->min_symbol_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 360;
	ptr_struct->last_symbol_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 356;
	ptr_struct->last_symbol_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 408;
	ptr_struct->hi_ser_counter = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 416;
	ptr_struct->pcs_phy_state_latched = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 472;
	ptr_struct->apsu_restart_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_pddr_link_down_info_page_ext_print(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_down_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_blame           : %s (" UH_FMT ")\n", (ptr_struct->down_blame == 0 ? ("Unknown") : ((ptr_struct->down_blame == 1 ? ("Local_phy") : ((ptr_struct->down_blame == 2 ? ("Remote_phy") : ("unknown")))))), ptr_struct->down_blame);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_intent          : %s (" UH_FMT ")\n", (ptr_struct->down_intent == 0 ? ("Unknown") : ((ptr_struct->down_intent == 1 ? ("intentional") : ((ptr_struct->down_intent == 2 ? ("unintentional") : ("unknown")))))), ptr_struct->down_intent);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_reason_opcode  : " UH_FMT "\n", ptr_struct->local_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "recovery_entry_reason : %s (" UH_FMT ")\n", (ptr_struct->recovery_entry_reason == 0 ? ("No_link_down_indication") : ((ptr_struct->recovery_entry_reason == 1 ? ("Unknown_reason") : ((ptr_struct->recovery_entry_reason == 2 ? ("Hi_BER") : ((ptr_struct->recovery_entry_reason == 3 ? ("Block_Lock_loss") : ((ptr_struct->recovery_entry_reason == 4 ? ("Alignment_loss") : ((ptr_struct->recovery_entry_reason == 5 ? ("FEC_sync_loss") : ((ptr_struct->recovery_entry_reason == 6 ? ("PLL_lock_loss") : ((ptr_struct->recovery_entry_reason == 7 ? ("FIFO_overflow") : ((ptr_struct->recovery_entry_reason == 8 ? ("false_SKIP_condition") : ((ptr_struct->recovery_entry_reason == 9 ? ("Minor_Error_threshold_exceeded") : ((ptr_struct->recovery_entry_reason == 10 ? ("Physical_layer_retransmission_timeout") : ((ptr_struct->recovery_entry_reason == 11 ? ("Heartbeat_errors") : ((ptr_struct->recovery_entry_reason == 12 ? ("Link_Layer_credit_monitoring_watchdog") : ((ptr_struct->recovery_entry_reason == 13 ? ("Link_Layer_integrity_threshold_exceeded") : ((ptr_struct->recovery_entry_reason == 14 ? ("Link_Layer_buffer_overrun") : ((ptr_struct->recovery_entry_reason == 15 ? ("Down_by_outband_command_with_healthy_link") : ((ptr_struct->recovery_entry_reason == 16 ? ("Down_by_outband_command_for_link_with_hi_ber") : ((ptr_struct->recovery_entry_reason == 17 ? ("Down_by_inband_command_with_healthy_link") : ((ptr_struct->recovery_entry_reason == 18 ? ("Down_by_inband_command_for_link_with_hi_ber") : ((ptr_struct->recovery_entry_reason == 19 ? ("Down_by_verification_GW") : ((ptr_struct->recovery_entry_reason == 20 ? ("Received_Remote_Fault") : ((ptr_struct->recovery_entry_reason == 21 ? ("Received_TS1") : ((ptr_struct->recovery_entry_reason == 22 ? ("Down_by_management_command") : ((ptr_struct->recovery_entry_reason == 23 ? ("Cable_was_unplugged") : ((ptr_struct->recovery_entry_reason == 24 ? ("Cable_access_issue") : ((ptr_struct->recovery_entry_reason == 25 ? ("Cable_Thermal_shutdown") : ((ptr_struct->recovery_entry_reason == 26 ? ("Current_issue") : ((ptr_struct->recovery_entry_reason == 27 ? ("Power_budget") : ((ptr_struct->recovery_entry_reason == 28 ? ("Fast_recovery_raw_ber") : ((ptr_struct->recovery_entry_reason == 29 ? ("Fast_recovery_effective_ber") : ((ptr_struct->recovery_entry_reason == 30 ? ("Fast_recovery_symbol_ber") : ((ptr_struct->recovery_entry_reason == 31 ? ("Fast_recovery_credit_watchdog") : ((ptr_struct->recovery_entry_reason == 32 ? ("Peer_side_down_to_sleep_state") : ((ptr_struct->recovery_entry_reason == 33 ? ("Peer_side_down_to_disable_state") : ((ptr_struct->recovery_entry_reason == 34 ? ("Peer_side_down_to_disable_and_port_lock") : ((ptr_struct->recovery_entry_reason == 35 ? ("Peer_side_down_due_to_thermal_event") : ((ptr_struct->recovery_entry_reason == 36 ? ("Peer_side_down_due_to_force_event") : ((ptr_struct->recovery_entry_reason == 37 ? ("Peer_side_down_due_to_reset_event") : ((ptr_struct->recovery_entry_reason == 38 ? ("Reset_no_power_cycle") : ((ptr_struct->recovery_entry_reason == 39 ? ("Fast_recovery_tx_plr_trigger") : ((ptr_struct->recovery_entry_reason == 40 ? ("Down_due_to_HW_force_event") : ((ptr_struct->recovery_entry_reason == 42 ? ("L1_exit_failure") : ((ptr_struct->recovery_entry_reason == 43 ? ("too_many_link_error_recoveries") : ((ptr_struct->recovery_entry_reason == 44 ? ("Down_due_to_contain_mode") : ((ptr_struct->recovery_entry_reason == 45 ? ("BW_loss_threshold_exceeded") : ((ptr_struct->recovery_entry_reason == 46 ? ("ELS_laser_fault") : ((ptr_struct->recovery_entry_reason == 47 ? ("Hi_SER") : ((ptr_struct->recovery_entry_reason == 48 ? ("down_by_nmx_adminstate_cmd") : ((ptr_struct->recovery_entry_reason == 49 ? ("flua_ber_below_threshold_in_guard_time") : ((ptr_struct->recovery_entry_reason == 50 ? ("Received_Local_Fault") : ((ptr_struct->recovery_entry_reason == 51 ? ("Received_Link_Interruption") : ((ptr_struct->recovery_entry_reason == 52 ? ("Manual_debug_mode") : ((ptr_struct->recovery_entry_reason == 53 ? ("command_triggered_recovery") : ((ptr_struct->recovery_entry_reason == 58 ? ("Recovery_BW_loss_threshold_exceeded") : ((ptr_struct->recovery_entry_reason == 59 ? ("Peer_side_down_due_to_contain_mode") : ((ptr_struct->recovery_entry_reason == 60 ? ("module_unexpected_reset_or_low_power") : ((ptr_struct->recovery_entry_reason == 61 ? ("Down_due_to_contain_mode_rx") : ((ptr_struct->recovery_entry_reason == 62 ? ("Down_due_to_contain_mode_tx") : ((ptr_struct->recovery_entry_reason == 64 ? ("serdes") : ((ptr_struct->recovery_entry_reason == 65 ? ("serdes") : ((ptr_struct->recovery_entry_reason == 66 ? ("down_due_to_rs_fec_consec_bad_cw_threshold_exceeded") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->recovery_entry_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_reason_opcode : " UH_FMT "\n", ptr_struct->remote_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e2e_reason_opcode    : " UH_FMT "\n", ptr_struct->e2e_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts1_opcode           : " UH_FMT "\n", ptr_struct->ts1_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_failure_reason    : " UH_FMT "\n", ptr_struct->l1_failure_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_recovery_state  : " UH_FMT "\n", ptr_struct->last_recovery_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_symbol_ber_alarms : " UH_FMT "\n", ptr_struct->num_of_symbol_ber_alarms);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_raw_ber_magnitude : " UH_FMT "\n", ptr_struct->last_raw_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_raw_ber_coef    : " UH_FMT "\n", ptr_struct->last_raw_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cons_raw_norm_ber    : " UH_FMT "\n", ptr_struct->cons_raw_norm_ber);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_raw_ber_magnitude : " UH_FMT "\n", ptr_struct->max_raw_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_raw_ber_coef     : " UH_FMT "\n", ptr_struct->max_raw_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_raw_ber_magnitude : " UH_FMT "\n", ptr_struct->min_raw_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_raw_ber_coef     : " UH_FMT "\n", ptr_struct->min_raw_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_raw_ber_alarms : " UH_FMT "\n", ptr_struct->num_of_raw_ber_alarms);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_eff_ber_alarms : " UH_FMT "\n", ptr_struct->num_of_eff_ber_alarms);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_down_to_disable : " U32H_FMT "\n", ptr_struct->time_to_link_down_to_disable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_down_to_rx_loss : " U32H_FMT "\n", ptr_struct->time_to_link_down_to_rx_loss);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->min_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_eff_ber_coef     : " UH_FMT "\n", ptr_struct->min_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->last_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_eff_ber_coef    : " UH_FMT "\n", ptr_struct->last_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cons_eff_norm_ber    : " UH_FMT "\n", ptr_struct->cons_eff_norm_ber);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->max_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_eff_ber_coef     : " UH_FMT "\n", ptr_struct->max_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_symbol_ber_magnitude : " UH_FMT "\n", ptr_struct->max_symbol_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_symbol_ber_coef  : " UH_FMT "\n", ptr_struct->max_symbol_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cons_symbol_norm_ber : " UH_FMT "\n", ptr_struct->cons_symbol_norm_ber);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_symbol_ber_magnitude : " UH_FMT "\n", ptr_struct->min_symbol_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_symbol_ber_coef  : " UH_FMT "\n", ptr_struct->min_symbol_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_symbol_ber_magnitude : " UH_FMT "\n", ptr_struct->last_symbol_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_symbol_ber_coef : " UH_FMT "\n", ptr_struct->last_symbol_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hi_ser_counter       : " UH_FMT "\n", ptr_struct->hi_ser_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcs_phy_state_latched : " U32H_FMT "\n", ptr_struct->pcs_phy_state_latched);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apsu_restart_reason_opcode : %s (" UH_FMT ")\n", (ptr_struct->apsu_restart_reason_opcode == 0 ? ("apsu_restarted_due_to_fail") : ((ptr_struct->apsu_restart_reason_opcode == 1 ? ("apsu_restarted_due_to_link_fail") : ("unknown")))), ptr_struct->apsu_restart_reason_opcode);
}

unsigned int reg_access_switch_pddr_link_down_info_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_DOWN_INFO_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_link_down_info_page_ext_dump(const struct reg_access_switch_pddr_link_down_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_down_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_health_page_ext_pack(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ltx_status_lane0);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_fail_reason_lane0);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_count_lane0);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_count_max_lane0);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->hist_target_lane0);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->raw_ber_mag_target_lane0);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mant_target_lane0);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ltx_logger_index_lane0);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_fail_count_lane0);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mant_float_target_lane0);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_measure_retry_count);
	offset = 95;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ltx_status_lane1);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_fail_reason_lane1);
	offset = 85;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_count_lane1);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_count_max_lane1);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->hist_target_lane1);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->raw_ber_mag_target_lane1);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mant_target_lane1);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ltx_logger_index_lane1);
	offset = 115;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ltx_retry_fail_count_lane1);
	offset = 111;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_mant_float_target_lane1);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_measure_retry_fail_count);
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1408, 1);
		reg_access_switch_ltx_logger_ext_pack(&(ptr_struct->ltx_logger_lane0[i]), ptr_buff + offset / 8);
	}
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(768, 64, i, 1408, 1);
		reg_access_switch_ltx_logger_ext_pack(&(ptr_struct->ltx_logger_lane1[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pddr_link_health_page_ext_unpack(struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 31;
	ptr_struct->ltx_status_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->ltx_fail_reason_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 21;
	ptr_struct->ltx_retry_count_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 16;
	ptr_struct->ltx_retry_count_max_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 8;
	ptr_struct->hist_target_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 0;
	ptr_struct->raw_ber_mag_target_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->raw_ber_mant_target_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->ltx_logger_index_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 51;
	ptr_struct->ltx_retry_fail_count_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 47;
	ptr_struct->raw_ber_mant_float_target_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->fec_measure_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 95;
	ptr_struct->ltx_status_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 90;
	ptr_struct->ltx_fail_reason_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 85;
	ptr_struct->ltx_retry_count_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->ltx_retry_count_max_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 72;
	ptr_struct->hist_target_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 64;
	ptr_struct->raw_ber_mag_target_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 124;
	ptr_struct->raw_ber_mant_target_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 120;
	ptr_struct->ltx_logger_index_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 115;
	ptr_struct->ltx_retry_fail_count_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 111;
	ptr_struct->raw_ber_mant_float_target_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 100;
	ptr_struct->fec_measure_retry_fail_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1408, 1);
		reg_access_switch_ltx_logger_ext_unpack(&(ptr_struct->ltx_logger_lane0[i]), ptr_buff + offset / 8);
	}
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(768, 64, i, 1408, 1);
		reg_access_switch_ltx_logger_ext_unpack(&(ptr_struct->ltx_logger_lane1[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pddr_link_health_page_ext_print(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_health_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_status_lane0     : " UH_FMT "\n", ptr_struct->ltx_status_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_fail_reason_lane0 : " UH_FMT "\n", ptr_struct->ltx_fail_reason_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_count_lane0 : " UH_FMT "\n", ptr_struct->ltx_retry_count_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_count_max_lane0 : " UH_FMT "\n", ptr_struct->ltx_retry_count_max_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hist_target_lane0    : " UH_FMT "\n", ptr_struct->hist_target_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mag_target_lane0 : " UH_FMT "\n", ptr_struct->raw_ber_mag_target_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mant_target_lane0 : " UH_FMT "\n", ptr_struct->raw_ber_mant_target_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_logger_index_lane0 : " UH_FMT "\n", ptr_struct->ltx_logger_index_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_fail_count_lane0 : " UH_FMT "\n", ptr_struct->ltx_retry_fail_count_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mant_float_target_lane0 : " UH_FMT "\n", ptr_struct->raw_ber_mant_float_target_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_measure_retry_count : " UH_FMT "\n", ptr_struct->fec_measure_retry_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_status_lane1     : " UH_FMT "\n", ptr_struct->ltx_status_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_fail_reason_lane1 : " UH_FMT "\n", ptr_struct->ltx_fail_reason_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_count_lane1 : " UH_FMT "\n", ptr_struct->ltx_retry_count_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_count_max_lane1 : " UH_FMT "\n", ptr_struct->ltx_retry_count_max_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hist_target_lane1    : " UH_FMT "\n", ptr_struct->hist_target_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mag_target_lane1 : " UH_FMT "\n", ptr_struct->raw_ber_mag_target_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mant_target_lane1 : " UH_FMT "\n", ptr_struct->raw_ber_mant_target_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_logger_index_lane1 : " UH_FMT "\n", ptr_struct->ltx_logger_index_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ltx_retry_fail_count_lane1 : " UH_FMT "\n", ptr_struct->ltx_retry_fail_count_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_mant_float_target_lane1 : " UH_FMT "\n", ptr_struct->raw_ber_mant_float_target_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_measure_retry_fail_count : " UH_FMT "\n", ptr_struct->fec_measure_retry_fail_count);
	for (i = 0; i < 10; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ltx_logger_lane0_%03d:\n", i);
		reg_access_switch_ltx_logger_ext_print(&(ptr_struct->ltx_logger_lane0[i]), fd, indent_level + 1);
	}
	for (i = 0; i < 10; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ltx_logger_lane1_%03d:\n", i);
		reg_access_switch_ltx_logger_ext_print(&(ptr_struct->ltx_logger_lane1[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_pddr_link_health_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_HEALTH_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_link_health_page_ext_dump(const struct reg_access_switch_pddr_link_health_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_health_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_partner_info_ext_pack(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->info_supported_mask);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->partner_local_port);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->partner_module_type);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->peer_ga_id);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->partner_id_39_25);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->partner_id_lsb);
}

void reg_access_switch_pddr_link_partner_info_ext_unpack(struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->info_supported_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 54;
	ptr_struct->partner_local_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 92;
	ptr_struct->partner_module_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 72;
	ptr_struct->peer_ga_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->partner_id_39_25 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 136;
	ptr_struct->partner_id_lsb = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_switch_pddr_link_partner_info_ext_print(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_partner_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "info_supported_mask  : %s (" UH_FMT ")\n", (ptr_struct->info_supported_mask == 1 ? ("partner_local_port_supported") : ((ptr_struct->info_supported_mask == 2 ? ("partner_module_type_supported") : ((ptr_struct->info_supported_mask == 4 ? ("partner_id_lsb_supported") : ((ptr_struct->info_supported_mask == 16 ? ("peer_ga_id") : ((ptr_struct->info_supported_mask == 32 ? ("partner_id_39_25_supported") : ("unknown")))))))))), ptr_struct->info_supported_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partner_local_port   : " UH_FMT "\n", ptr_struct->partner_local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partner_module_type  : %s (" UH_FMT ")\n", (ptr_struct->partner_module_type == 0 ? ("undefined") : ((ptr_struct->partner_module_type == 1 ? ("Active_Optical_or_Copper_Cable") : ((ptr_struct->partner_module_type == 2 ? ("Active_Optical_Transceiver") : ((ptr_struct->partner_module_type == 3 ? ("Passive_Copper_cable") : ((ptr_struct->partner_module_type == 5 ? ("Twisted_pair") : ((ptr_struct->partner_module_type == 6 ? ("Far_End_Linear_Equalizer_Cable") : ((ptr_struct->partner_module_type == 7 ? ("Linear_Optical_Transceiver") : ((ptr_struct->partner_module_type == 8 ? ("CPO") : ((ptr_struct->partner_module_type == 9 ? ("Near_end_linear_equalizer_cable") : ((ptr_struct->partner_module_type == 10 ? ("Fully_linear_equalizer_cable") : ((ptr_struct->partner_module_type == 11 ? ("Half_retimed_tx_optical_transceiver") : ("unknown")))))))))))))))))))))), ptr_struct->partner_module_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "peer_ga_id           : " UH_FMT "\n", ptr_struct->peer_ga_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partner_id_39_25     : " UH_FMT "\n", ptr_struct->partner_id_39_25);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "partner_id_lsb       : " UH_FMT "\n", ptr_struct->partner_id_lsb);
}

unsigned int reg_access_switch_pddr_link_partner_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_PARTNER_INFO_EXT_SIZE;
}

void reg_access_switch_pddr_link_partner_info_ext_dump(const struct reg_access_switch_pddr_link_partner_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_partner_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_link_up_info_page_ext_pack(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->up_reason_mng);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->up_reason_drv);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->up_reason_pwr);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_up);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fast_link_up_status);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_up_phy_up_to_active);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_up_sd_to_phy_up);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_up_disable_to_sd);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_to_link_up_disable_to_pd);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_of_module_conf_done_up);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_of_module_conf_done_down);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_logical_init_to_active);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->total_time_pcs_local_fault);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->total_time_pcs_remote_fault);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_on_last_hi_ser);
	offset = 432;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->last_phy_data_groups_collection_time);
	offset = 416;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->last_data_groups_collection_time);
	offset = 464;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->last_module_data_groups_collection_time);
	offset = 448;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->last_serdes_data_groups_collection_time);
	offset = 532;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->apsu_total_time);
	offset = 516;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->apsu_ilt_time);
}

void reg_access_switch_pddr_link_up_info_page_ext_unpack(struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->up_reason_mng = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->up_reason_drv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 12;
	ptr_struct->up_reason_pwr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->time_to_link_up = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->fast_link_up_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->time_to_link_up_phy_up_to_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->time_to_link_up_sd_to_phy_up = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->time_to_link_up_disable_to_sd = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->time_to_link_up_disable_to_pd = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->time_of_module_conf_done_up = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->time_of_module_conf_done_down = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->time_logical_init_to_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->total_time_pcs_local_fault = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->total_time_pcs_remote_fault = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->time_on_last_hi_ser = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 432;
	ptr_struct->last_phy_data_groups_collection_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 416;
	ptr_struct->last_data_groups_collection_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 464;
	ptr_struct->last_module_data_groups_collection_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 448;
	ptr_struct->last_serdes_data_groups_collection_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 532;
	ptr_struct->apsu_total_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 516;
	ptr_struct->apsu_ilt_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void reg_access_switch_pddr_link_up_info_page_ext_print(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_link_up_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_reason_mng        : " UH_FMT "\n", ptr_struct->up_reason_mng);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_reason_drv        : " UH_FMT "\n", ptr_struct->up_reason_drv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_reason_pwr        : " UH_FMT "\n", ptr_struct->up_reason_pwr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_up      : " U32H_FMT "\n", ptr_struct->time_to_link_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fast_link_up_status  : " UH_FMT "\n", ptr_struct->fast_link_up_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_up_phy_up_to_active : " U32H_FMT "\n", ptr_struct->time_to_link_up_phy_up_to_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_up_sd_to_phy_up : " U32H_FMT "\n", ptr_struct->time_to_link_up_sd_to_phy_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_up_disable_to_sd : " U32H_FMT "\n", ptr_struct->time_to_link_up_disable_to_sd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_to_link_up_disable_to_pd : " U32H_FMT "\n", ptr_struct->time_to_link_up_disable_to_pd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_of_module_conf_done_up : " U32H_FMT "\n", ptr_struct->time_of_module_conf_done_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_of_module_conf_done_down : " U32H_FMT "\n", ptr_struct->time_of_module_conf_done_down);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_logical_init_to_active : " U32H_FMT "\n", ptr_struct->time_logical_init_to_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_time_pcs_local_fault : " U32H_FMT "\n", ptr_struct->total_time_pcs_local_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_time_pcs_remote_fault : " U32H_FMT "\n", ptr_struct->total_time_pcs_remote_fault);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_on_last_hi_ser  : " U32H_FMT "\n", ptr_struct->time_on_last_hi_ser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_phy_data_groups_collection_time : " UH_FMT "\n", ptr_struct->last_phy_data_groups_collection_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_data_groups_collection_time : " UH_FMT "\n", ptr_struct->last_data_groups_collection_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_module_data_groups_collection_time : " UH_FMT "\n", ptr_struct->last_module_data_groups_collection_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_serdes_data_groups_collection_time : " UH_FMT "\n", ptr_struct->last_serdes_data_groups_collection_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apsu_total_time      : " UH_FMT "\n", ptr_struct->apsu_total_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apsu_ilt_time        : " UH_FMT "\n", ptr_struct->apsu_ilt_time);
}

unsigned int reg_access_switch_pddr_link_up_info_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_LINK_UP_INFO_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_link_up_info_page_ext_dump(const struct reg_access_switch_pddr_link_up_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_link_up_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_module_info_ext_pack(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ethernet_compliance_code);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ext_ethernet_compliance_code);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_breakout);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_technology);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_power_class);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_identifier);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_length);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cable_vendor);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cable_type);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_tx_equalization);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_rx_emphasis);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_rx_amp);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_power);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_attenuation_5g);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_attenuation_7g);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_attenuation_12g);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_attenuation_25g);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tx_cdr_state);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_cdr_state);
	offset = 140;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_cdr_cap);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_cdr_cap);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_rx_post_emphasis);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 1664, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_name[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 1664, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_pn[i]);
	}
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_rev);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_version);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(480, 32, i, 1664, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_sn[i]);
	}
	offset = 624;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->voltage);
	offset = 608;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 656;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane1);
	offset = 640;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane0);
	offset = 688;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane3);
	offset = 672;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane2);
	offset = 720;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane5);
	offset = 704;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane4);
	offset = 752;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane7);
	offset = 736;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_lane6);
	offset = 784;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane1);
	offset = 768;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane0);
	offset = 816;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane3);
	offset = 800;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane2);
	offset = 848;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane5);
	offset = 832;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane4);
	offset = 880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane7);
	offset = 864;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_lane6);
	offset = 912;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane1);
	offset = 896;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane0);
	offset = 944;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane3);
	offset = 928;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane2);
	offset = 976;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane5);
	offset = 960;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane4);
	offset = 1008;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane7);
	offset = 992;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_lane6);
	offset = 1040;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_low_th);
	offset = 1024;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_high_th);
	offset = 1072;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->voltage_low_th);
	offset = 1056;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->voltage_high_th);
	offset = 1104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_low_th);
	offset = 1088;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->rx_power_high_th);
	offset = 1136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_low_th);
	offset = 1120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_power_high_th);
	offset = 1168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_low_th);
	offset = 1152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tx_bias_high_th);
	offset = 1200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->wavelength);
	offset = 1190;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->smf_length);
	offset = 1189;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_output_valid_cap);
	offset = 1188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->did_cap);
	offset = 1187;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_power_type);
	offset = 1184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->module_st);
	offset = 1238;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->ib_compliance_code);
	offset = 1236;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_bias_scaling_factor);
	offset = 1224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->active_set_media_compliance_code);
	offset = 1216;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->active_set_host_compliance_code);
	offset = 1274;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->ib_width);
	offset = 1264;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->monitor_cap_mask);
	offset = 1256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->nbr100);
	offset = 1248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->nbr250);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(1308, 4, i, 1664, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dp_st_lane[i]);
	}
	offset = 1336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length_om5);
	offset = 1328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length_om4);
	offset = 1320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length_om3);
	offset = 1312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length_om2);
	offset = 1368;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->memory_map_rev);
	offset = 1352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->wavelength_tolerance);
	offset = 1344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->length_om1);
	offset = 1376;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->memory_map_compliance);
	offset = 1408;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->date_code);
	offset = 1480;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->vendor_oui);
	offset = 1472;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->connector_type);
	offset = 1528;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rx_output_valid);
	offset = 1520;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_attenuation_53g);
	offset = 1518;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_input_freq_sync);
	offset = 1516;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->event_logger_cap);
	offset = 1564;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_code);
	offset = 1560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cdr_vendor);
	offset = 1552;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->oe_fuse_rev);
	offset = 1536;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_fiber_length);
	offset = 1587;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->els_laser2_fault_state);
	offset = 1584;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->els_laser_fault_state);
	offset = 1580;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->els2_oper_state);
	offset = 1576;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->els_oper_state);
	offset = 1575;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_restriction);
	offset = 1574;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_restriction);
	offset = 1572;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->laser2_status);
	offset = 1570;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->laser_status);
	offset = 1569;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser2_enabled);
	offset = 1568;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->laser_enabled);
	offset = 1600;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_production_test_revision_lsb);
	offset = 1656;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_hw_revision_minor);
	offset = 1648;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_hw_revision_major);
	offset = 1632;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_production_test_revision_msb);
}

void reg_access_switch_pddr_module_info_ext_unpack(struct reg_access_switch_pddr_module_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->ext_ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->cable_breakout = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->cable_technology = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->cable_power_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->cable_identifier = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->cable_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 36;
	ptr_struct->cable_vendor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->cable_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 88;
	ptr_struct->cable_tx_equalization = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->cable_rx_emphasis = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->cable_rx_amp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->max_power = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->cable_attenuation_5g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->cable_attenuation_7g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->cable_attenuation_12g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->cable_attenuation_25g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 152;
	ptr_struct->tx_cdr_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->rx_cdr_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 140;
	ptr_struct->tx_cdr_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 136;
	ptr_struct->rx_cdr_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->cable_rx_post_emphasis = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 1664, 1);
		ptr_struct->vendor_name[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 1664, 1);
		ptr_struct->vendor_pn[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 416;
	ptr_struct->vendor_rev = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->fw_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(480, 32, i, 1664, 1);
		ptr_struct->vendor_sn[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 624;
	ptr_struct->voltage = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 608;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 656;
	ptr_struct->rx_power_lane1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 640;
	ptr_struct->rx_power_lane0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 688;
	ptr_struct->rx_power_lane3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 672;
	ptr_struct->rx_power_lane2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 720;
	ptr_struct->rx_power_lane5 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 704;
	ptr_struct->rx_power_lane4 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 752;
	ptr_struct->rx_power_lane7 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 736;
	ptr_struct->rx_power_lane6 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 784;
	ptr_struct->tx_power_lane1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 768;
	ptr_struct->tx_power_lane0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 816;
	ptr_struct->tx_power_lane3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 800;
	ptr_struct->tx_power_lane2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 848;
	ptr_struct->tx_power_lane5 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 832;
	ptr_struct->tx_power_lane4 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 880;
	ptr_struct->tx_power_lane7 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 864;
	ptr_struct->tx_power_lane6 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 912;
	ptr_struct->tx_bias_lane1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 896;
	ptr_struct->tx_bias_lane0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 944;
	ptr_struct->tx_bias_lane3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 928;
	ptr_struct->tx_bias_lane2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 976;
	ptr_struct->tx_bias_lane5 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 960;
	ptr_struct->tx_bias_lane4 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1008;
	ptr_struct->tx_bias_lane7 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 992;
	ptr_struct->tx_bias_lane6 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1040;
	ptr_struct->temperature_low_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1024;
	ptr_struct->temperature_high_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1072;
	ptr_struct->voltage_low_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1056;
	ptr_struct->voltage_high_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1104;
	ptr_struct->rx_power_low_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1088;
	ptr_struct->rx_power_high_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1136;
	ptr_struct->tx_power_low_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1120;
	ptr_struct->tx_power_high_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1168;
	ptr_struct->tx_bias_low_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1152;
	ptr_struct->tx_bias_high_th = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1200;
	ptr_struct->wavelength = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1190;
	ptr_struct->smf_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 1189;
	ptr_struct->rx_output_valid_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1188;
	ptr_struct->did_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1187;
	ptr_struct->rx_power_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1184;
	ptr_struct->module_st = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1238;
	ptr_struct->ib_compliance_code = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 1236;
	ptr_struct->tx_bias_scaling_factor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1224;
	ptr_struct->active_set_media_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1216;
	ptr_struct->active_set_host_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1274;
	ptr_struct->ib_width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1264;
	ptr_struct->monitor_cap_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1256;
	ptr_struct->nbr100 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1248;
	ptr_struct->nbr250 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(1308, 4, i, 1664, 1);
		ptr_struct->dp_st_lane[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	}
	offset = 1336;
	ptr_struct->length_om5 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1328;
	ptr_struct->length_om4 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1320;
	ptr_struct->length_om3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1312;
	ptr_struct->length_om2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1368;
	ptr_struct->memory_map_rev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1352;
	ptr_struct->wavelength_tolerance = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1344;
	ptr_struct->length_om1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1376;
	ptr_struct->memory_map_compliance = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1408;
	ptr_struct->date_code = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 1480;
	ptr_struct->vendor_oui = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 1472;
	ptr_struct->connector_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1528;
	ptr_struct->rx_output_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1520;
	ptr_struct->cable_attenuation_53g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1518;
	ptr_struct->tx_input_freq_sync = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1516;
	ptr_struct->event_logger_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1564;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1560;
	ptr_struct->cdr_vendor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1552;
	ptr_struct->oe_fuse_rev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1536;
	ptr_struct->max_fiber_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1587;
	ptr_struct->els_laser2_fault_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1584;
	ptr_struct->els_laser_fault_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 1580;
	ptr_struct->els2_oper_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1576;
	ptr_struct->els_oper_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1575;
	ptr_struct->laser2_restriction = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1574;
	ptr_struct->laser_restriction = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1572;
	ptr_struct->laser2_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1570;
	ptr_struct->laser_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1569;
	ptr_struct->laser2_enabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1568;
	ptr_struct->laser_enabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1600;
	ptr_struct->module_production_test_revision_lsb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1656;
	ptr_struct->module_hw_revision_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1648;
	ptr_struct->module_hw_revision_major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1632;
	ptr_struct->module_production_test_revision_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_pddr_module_info_ext_print(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_module_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ext_ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_breakout       : " UH_FMT "\n", ptr_struct->cable_breakout);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_technology     : %s (" UH_FMT ")\n", (ptr_struct->cable_technology == 0 ? ("VCSEL_850nm") : ((ptr_struct->cable_technology == 1 ? ("VCSEL_1310nm") : ((ptr_struct->cable_technology == 2 ? ("VCSEL_1550nm") : ((ptr_struct->cable_technology == 3 ? ("FP_laser_1310nm") : ((ptr_struct->cable_technology == 4 ? ("DFB_laser_1310nm") : ((ptr_struct->cable_technology == 5 ? ("DFB_laser_1550nm") : ((ptr_struct->cable_technology == 6 ? ("EML_1310nm") : ((ptr_struct->cable_technology == 7 ? ("EML_1550nm") : ((ptr_struct->cable_technology == 8 ? ("others") : ((ptr_struct->cable_technology == 9 ? ("DFB_laser_1490nm") : ((ptr_struct->cable_technology == 10 ? ("Passive_copper_cable_unequalized") : ((ptr_struct->cable_technology == 11 ? ("Passive_copper_cable_equalized") : ((ptr_struct->cable_technology == 12 ? ("Copper_cable_near_end_and_far_end_limiting_active_equailizer") : ((ptr_struct->cable_technology == 13 ? ("Copper_cable_far_end_limiting_active_equailizer") : ((ptr_struct->cable_technology == 14 ? ("Copper_cable_near_end_limiting_active_equializer") : ((ptr_struct->cable_technology == 15 ? ("Copper_cable_linear_active_equalizers") : ((ptr_struct->cable_technology == 16 ? ("c_band_tunable_laser") : ((ptr_struct->cable_technology == 17 ? ("l_band_tunable_laser") : ((ptr_struct->cable_technology == 18 ? ("Copper_cable_near_end_and_far_end_linear_active_equalizers") : ((ptr_struct->cable_technology == 19 ? ("Copper_cable_far_end_linear_active_equalizers") : ((ptr_struct->cable_technology == 20 ? ("Copper_cable_near_end_linear_active_equalizers") : ("unknown")))))))))))))))))))))))))))))))))))))))))), ptr_struct->cable_technology);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_power_class    : " UH_FMT "\n", ptr_struct->cable_power_class);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_identifier     : " UH_FMT "\n", ptr_struct->cable_identifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_length         : " UH_FMT "\n", ptr_struct->cable_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_vendor         : %s (" UH_FMT ")\n", (ptr_struct->cable_vendor == 0 ? ("Other") : ((ptr_struct->cable_vendor == 1 ? ("Mellanox") : ((ptr_struct->cable_vendor == 2 ? ("Known_OUI") : ((ptr_struct->cable_vendor == 3 ? ("NVIDIA") : ("unknown")))))))), ptr_struct->cable_vendor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_type           : %s (" UH_FMT ")\n", (ptr_struct->cable_type == 0 ? ("Unidentified") : ((ptr_struct->cable_type == 1 ? ("Active_cable") : ((ptr_struct->cable_type == 2 ? ("Optical_Module") : ((ptr_struct->cable_type == 3 ? ("Passive_copper_cable_or_linear_copper") : ((ptr_struct->cable_type == 4 ? ("Cable_unplugged") : ((ptr_struct->cable_type == 5 ? ("Twisted_pair") : ((ptr_struct->cable_type == 6 ? ("CPO") : ((ptr_struct->cable_type == 7 ? ("OE") : ((ptr_struct->cable_type == 8 ? ("ELS") : ("unknown")))))))))))))))))), ptr_struct->cable_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_tx_equalization : " UH_FMT "\n", ptr_struct->cable_tx_equalization);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_rx_emphasis    : " UH_FMT "\n", ptr_struct->cable_rx_emphasis);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_rx_amp         : " UH_FMT "\n", ptr_struct->cable_rx_amp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_power            : " UH_FMT "\n", ptr_struct->max_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_attenuation_5g : " UH_FMT "\n", ptr_struct->cable_attenuation_5g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_attenuation_7g : " UH_FMT "\n", ptr_struct->cable_attenuation_7g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_attenuation_12g : " UH_FMT "\n", ptr_struct->cable_attenuation_12g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_attenuation_25g : " UH_FMT "\n", ptr_struct->cable_attenuation_25g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_cdr_state         : " UH_FMT "\n", ptr_struct->tx_cdr_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_cdr_state         : " UH_FMT "\n", ptr_struct->rx_cdr_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_cdr_cap           : " UH_FMT "\n", ptr_struct->tx_cdr_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_cdr_cap           : " UH_FMT "\n", ptr_struct->rx_cdr_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_rx_post_emphasis : " UH_FMT "\n", ptr_struct->cable_rx_post_emphasis);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "vendor_name_%03d     : " U32H_FMT "\n", i, ptr_struct->vendor_name[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "vendor_pn_%03d       : " U32H_FMT "\n", i, ptr_struct->vendor_pn[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vendor_rev           : " U32H_FMT "\n", ptr_struct->vendor_rev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version           : " U32H_FMT "\n", ptr_struct->fw_version);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "vendor_sn_%03d       : " U32H_FMT "\n", i, ptr_struct->vendor_sn[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "voltage              : " UH_FMT "\n", ptr_struct->voltage);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane1       : " UH_FMT "\n", ptr_struct->rx_power_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane0       : " UH_FMT "\n", ptr_struct->rx_power_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane3       : " UH_FMT "\n", ptr_struct->rx_power_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane2       : " UH_FMT "\n", ptr_struct->rx_power_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane5       : " UH_FMT "\n", ptr_struct->rx_power_lane5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane4       : " UH_FMT "\n", ptr_struct->rx_power_lane4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane7       : " UH_FMT "\n", ptr_struct->rx_power_lane7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_lane6       : " UH_FMT "\n", ptr_struct->rx_power_lane6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane1       : " UH_FMT "\n", ptr_struct->tx_power_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane0       : " UH_FMT "\n", ptr_struct->tx_power_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane3       : " UH_FMT "\n", ptr_struct->tx_power_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane2       : " UH_FMT "\n", ptr_struct->tx_power_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane5       : " UH_FMT "\n", ptr_struct->tx_power_lane5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane4       : " UH_FMT "\n", ptr_struct->tx_power_lane4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane7       : " UH_FMT "\n", ptr_struct->tx_power_lane7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_lane6       : " UH_FMT "\n", ptr_struct->tx_power_lane6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane1        : " UH_FMT "\n", ptr_struct->tx_bias_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane0        : " UH_FMT "\n", ptr_struct->tx_bias_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane3        : " UH_FMT "\n", ptr_struct->tx_bias_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane2        : " UH_FMT "\n", ptr_struct->tx_bias_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane5        : " UH_FMT "\n", ptr_struct->tx_bias_lane5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane4        : " UH_FMT "\n", ptr_struct->tx_bias_lane4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane7        : " UH_FMT "\n", ptr_struct->tx_bias_lane7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_lane6        : " UH_FMT "\n", ptr_struct->tx_bias_lane6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_low_th   : " UH_FMT "\n", ptr_struct->temperature_low_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_high_th  : " UH_FMT "\n", ptr_struct->temperature_high_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "voltage_low_th       : " UH_FMT "\n", ptr_struct->voltage_low_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "voltage_high_th      : " UH_FMT "\n", ptr_struct->voltage_high_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_low_th      : " UH_FMT "\n", ptr_struct->rx_power_low_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_high_th     : " UH_FMT "\n", ptr_struct->rx_power_high_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_low_th      : " UH_FMT "\n", ptr_struct->tx_power_low_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_power_high_th     : " UH_FMT "\n", ptr_struct->tx_power_high_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_low_th       : " UH_FMT "\n", ptr_struct->tx_bias_low_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_high_th      : " UH_FMT "\n", ptr_struct->tx_bias_high_th);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wavelength           : " UH_FMT "\n", ptr_struct->wavelength);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "smf_length           : " UH_FMT "\n", ptr_struct->smf_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_output_valid_cap  : " UH_FMT "\n", ptr_struct->rx_output_valid_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "did_cap              : " UH_FMT "\n", ptr_struct->did_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_power_type        : %s (" UH_FMT ")\n", (ptr_struct->rx_power_type == 0 ? ("OMA") : ((ptr_struct->rx_power_type == 1 ? ("Average_power") : ("unknown")))), ptr_struct->rx_power_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_st            : %s (" UH_FMT ")\n", (ptr_struct->module_st == 0 ? ("reserved") : ((ptr_struct->module_st == 1 ? ("LowPwr_state") : ((ptr_struct->module_st == 2 ? ("PwrUp_state") : ((ptr_struct->module_st == 3 ? ("Ready_state") : ((ptr_struct->module_st == 4 ? ("PwrDn_state") : ((ptr_struct->module_st == 5 ? ("Fault_state") : ("unknown")))))))))))), ptr_struct->module_st);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_compliance_code   : %s (" UH_FMT ")\n", (ptr_struct->ib_compliance_code == 1 ? ("SDR") : ((ptr_struct->ib_compliance_code == 2 ? ("DDR") : ((ptr_struct->ib_compliance_code == 4 ? ("QDR") : ((ptr_struct->ib_compliance_code == 8 ? ("FDR10") : ((ptr_struct->ib_compliance_code == 16 ? ("FDR") : ((ptr_struct->ib_compliance_code == 32 ? ("EDR") : ((ptr_struct->ib_compliance_code == 64 ? ("HDR") : ((ptr_struct->ib_compliance_code == 128 ? ("NDR") : ((ptr_struct->ib_compliance_code == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->ib_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bias_scaling_factor : %s (" UH_FMT ")\n", (ptr_struct->tx_bias_scaling_factor == 0 ? ("multiply_1x") : ((ptr_struct->tx_bias_scaling_factor == 1 ? ("multiply_2x") : ((ptr_struct->tx_bias_scaling_factor == 2 ? ("multiply_4x") : ("unknown")))))), ptr_struct->tx_bias_scaling_factor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active_set_media_compliance_code : " UH_FMT "\n", ptr_struct->active_set_media_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active_set_host_compliance_code : " UH_FMT "\n", ptr_struct->active_set_host_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_width             : " UH_FMT "\n", ptr_struct->ib_width);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "monitor_cap_mask     : " UH_FMT "\n", ptr_struct->monitor_cap_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nbr100               : " UH_FMT "\n", ptr_struct->nbr100);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nbr250               : " UH_FMT "\n", ptr_struct->nbr250);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dp_st_lane_%03d      : %s (" UH_FMT ")\n", i, (ptr_struct->dp_st_lane[i] == 1 ? ("DPDeactivated") : ((ptr_struct->dp_st_lane[i] == 2 ? ("DPInit") : ((ptr_struct->dp_st_lane[i] == 3 ? ("DPDeinit") : ((ptr_struct->dp_st_lane[i] == 4 ? ("DPActivated") : ((ptr_struct->dp_st_lane[i] == 5 ? ("DPTxTurnOn") : ((ptr_struct->dp_st_lane[i] == 6 ? ("DPTxTurnOff") : ((ptr_struct->dp_st_lane[i] == 7 ? ("DPInitialized") : ("unknown")))))))))))))), ptr_struct->dp_st_lane[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length_om5           : " UH_FMT "\n", ptr_struct->length_om5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length_om4           : " UH_FMT "\n", ptr_struct->length_om4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length_om3           : " UH_FMT "\n", ptr_struct->length_om3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length_om2           : " UH_FMT "\n", ptr_struct->length_om2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "memory_map_rev       : " UH_FMT "\n", ptr_struct->memory_map_rev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wavelength_tolerance : " UH_FMT "\n", ptr_struct->wavelength_tolerance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "length_om1           : " UH_FMT "\n", ptr_struct->length_om1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "memory_map_compliance : " U32H_FMT "\n", ptr_struct->memory_map_compliance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "date_code            : " U64H_FMT "\n", ptr_struct->date_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vendor_oui           : " UH_FMT "\n", ptr_struct->vendor_oui);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "connector_type       : " UH_FMT "\n", ptr_struct->connector_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_output_valid      : " UH_FMT "\n", ptr_struct->rx_output_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_attenuation_53g : " UH_FMT "\n", ptr_struct->cable_attenuation_53g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_input_freq_sync   : %s (" UH_FMT ")\n", (ptr_struct->tx_input_freq_sync == 0 ? ("Tx_input_lanes_1_8") : ((ptr_struct->tx_input_freq_sync == 1 ? ("Tx_input_lanes_1_4_and_5_8") : ((ptr_struct->tx_input_freq_sync == 2 ? ("Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8") : ((ptr_struct->tx_input_freq_sync == 3 ? ("Lanes_may_be_asynchronous_in_frequency") : ("unknown")))))))), ptr_struct->tx_input_freq_sync);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "event_logger_cap     : " UH_FMT "\n", ptr_struct->event_logger_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code           : %s (" UH_FMT ")\n", (ptr_struct->error_code == 0 ? ("ConfigUndefined") : ((ptr_struct->error_code == 1 ? ("ConfigSuccess") : ((ptr_struct->error_code == 2 ? ("ConfigRejected") : ((ptr_struct->error_code == 3 ? ("ConfigRejectedInvalidAppSel") : ((ptr_struct->error_code == 4 ? ("ConfigRejectedInvalidDataPath") : ((ptr_struct->error_code == 5 ? ("ConfigRejectedInvalidSI") : ((ptr_struct->error_code == 6 ? ("ConfigRejectedLanesInUse") : ((ptr_struct->error_code == 7 ? ("ConfigRejectedPartialDataPath") : ((ptr_struct->error_code == 12 ? ("ConfigInProgress") : ((ptr_struct->error_code == 13 ? ("ConfigRejectedInvalid_VS_SI") : ("unknown")))))))))))))))))))), ptr_struct->error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_vendor           : %s (" UH_FMT ")\n", (ptr_struct->cdr_vendor == 0 ? ("Unknown_or_no_CDR") : ((ptr_struct->cdr_vendor == 1 ? ("Inphy_gen1_polaris") : ((ptr_struct->cdr_vendor == 2 ? ("Inphy_gen2_Atlas") : ((ptr_struct->cdr_vendor == 3 ? ("Marvell_Spica_Plus") : ((ptr_struct->cdr_vendor == 4 ? ("Brdcm_Portofino_or_gemera") : ((ptr_struct->cdr_vendor == 5 ? ("Nvidia_ArcusE") : ((ptr_struct->cdr_vendor == 6 ? ("Marvell_nova2or_ara") : ((ptr_struct->cdr_vendor == 7 ? ("Macom_linear_equalizer") : ((ptr_struct->cdr_vendor == 8 ? ("Semec_linear_equalizer") : ((ptr_struct->cdr_vendor == 9 ? ("Marvel_linear_equalizer") : ((ptr_struct->cdr_vendor == 10 ? ("Marvel_spica_5nm") : ((ptr_struct->cdr_vendor == 11 ? ("luxic_linear_equalizer") : ((ptr_struct->cdr_vendor == 12 ? ("Broadcom_sian2_or_3") : ((ptr_struct->cdr_vendor == 13 ? ("Arcus2") : ("unknown")))))))))))))))))))))))))))), ptr_struct->cdr_vendor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_fuse_rev          : " UH_FMT "\n", ptr_struct->oe_fuse_rev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_fiber_length     : " UH_FMT "\n", ptr_struct->max_fiber_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_laser2_fault_state : %s (" UH_FMT ")\n", (ptr_struct->els_laser2_fault_state == 0 ? ("no_fault") : ((ptr_struct->els_laser2_fault_state == 1 ? ("laser_fiber_contaminated") : ((ptr_struct->els_laser2_fault_state == 2 ? ("laser_APC_fault") : ((ptr_struct->els_laser2_fault_state == 3 ? ("laser_power_exceeded_allowed_range") : ((ptr_struct->els_laser2_fault_state == 4 ? ("laser_power_subceeded_allowed_range") : ((ptr_struct->els_laser2_fault_state == 5 ? ("laser_TEC_control_loop_fault") : ((ptr_struct->els_laser2_fault_state == 6 ? ("laser_ramping_timeout_fault") : ((ptr_struct->els_laser2_fault_state == 7 ? ("laser_power_tuning_fault") : ("unknown")))))))))))))))), ptr_struct->els_laser2_fault_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_laser_fault_state : %s (" UH_FMT ")\n", (ptr_struct->els_laser_fault_state == 0 ? ("no_fault") : ((ptr_struct->els_laser_fault_state == 1 ? ("laser_fiber_contaminated") : ((ptr_struct->els_laser_fault_state == 2 ? ("laser_APC_fault") : ((ptr_struct->els_laser_fault_state == 3 ? ("laser_power_exceeded_allowed_range") : ((ptr_struct->els_laser_fault_state == 4 ? ("laser_power_subceeded_allowed_range") : ((ptr_struct->els_laser_fault_state == 5 ? ("laser_TEC_control_loop_fault") : ((ptr_struct->els_laser_fault_state == 6 ? ("laser_ramping_timeout_fault") : ((ptr_struct->els_laser_fault_state == 7 ? ("laser_power_tuning_fault") : ("unknown")))))))))))))))), ptr_struct->els_laser_fault_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els2_oper_state      : %s (" UH_FMT ")\n", (ptr_struct->els2_oper_state == 0 ? ("laser_init") : ((ptr_struct->els2_oper_state == 1 ? ("laser_active") : ((ptr_struct->els2_oper_state == 2 ? ("laser_active_with_fault") : ((ptr_struct->els2_oper_state == 3 ? ("laser_down") : ((ptr_struct->els2_oper_state == 4 ? ("laser_down_with_fault") : ("unknown")))))))))), ptr_struct->els2_oper_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_oper_state       : %s (" UH_FMT ")\n", (ptr_struct->els_oper_state == 0 ? ("laser_init") : ((ptr_struct->els_oper_state == 1 ? ("laser_active") : ((ptr_struct->els_oper_state == 2 ? ("laser_active_with_fault") : ((ptr_struct->els_oper_state == 3 ? ("laser_down") : ((ptr_struct->els_oper_state == 4 ? ("laser_down_with_fault") : ("unknown")))))))))), ptr_struct->els_oper_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_restriction   : %s (" UH_FMT ")\n", (ptr_struct->laser2_restriction == 0 ? ("laser2_restriction_on") : ((ptr_struct->laser2_restriction == 1 ? ("laser2_restriction_off") : ("unknown")))), ptr_struct->laser2_restriction);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_restriction    : %s (" UH_FMT ")\n", (ptr_struct->laser_restriction == 0 ? ("laser_restriction_on") : ((ptr_struct->laser_restriction == 1 ? ("laser_restriction_off") : ("unknown")))), ptr_struct->laser_restriction);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_status        : %s (" UH_FMT ")\n", (ptr_struct->laser2_status == 0 ? ("laser2_off") : ((ptr_struct->laser2_status == 1 ? ("laser2_ramping") : ((ptr_struct->laser2_status == 2 ? ("laser2_on") : ("unknown")))))), ptr_struct->laser2_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_status         : %s (" UH_FMT ")\n", (ptr_struct->laser_status == 0 ? ("laser_off") : ((ptr_struct->laser_status == 1 ? ("laser_ramping") : ((ptr_struct->laser_status == 2 ? ("laser_on") : ("unknown")))))), ptr_struct->laser_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser2_enabled       : %s (" UH_FMT ")\n", (ptr_struct->laser2_enabled == 0 ? ("laser2_disabled") : ((ptr_struct->laser2_enabled == 1 ? ("laser2_enabled") : ("unknown")))), ptr_struct->laser2_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "laser_enabled        : %s (" UH_FMT ")\n", (ptr_struct->laser_enabled == 0 ? ("laser_disabled") : ((ptr_struct->laser_enabled == 1 ? ("laser_enabled") : ("unknown")))), ptr_struct->laser_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_production_test_revision_lsb : " U32H_FMT "\n", ptr_struct->module_production_test_revision_lsb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_hw_revision_minor : " UH_FMT "\n", ptr_struct->module_hw_revision_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_hw_revision_major : " UH_FMT "\n", ptr_struct->module_hw_revision_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_production_test_revision_msb : " UH_FMT "\n", ptr_struct->module_production_test_revision_msb);
}

unsigned int reg_access_switch_pddr_module_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_MODULE_INFO_EXT_SIZE;
}

void reg_access_switch_pddr_module_info_ext_dump(const struct reg_access_switch_pddr_module_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_module_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_operation_info_page_ext_pack(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->neg_mode_active);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->proto_active);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->resilink_fec_ind);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_phy_fsm_state);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->eth_an_fsm_state);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phy_mngr_fsm_state);
	offset = 64;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_pack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_pack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_pack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 96;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_eth_ext_pack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_ib_ext_pack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_pack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 128;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 128;
		reg_access_switch_pddr_cable_cap_eth_ext_pack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_pddr_cable_cap_ib_ext_pack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 128;
		reg_access_switch_pddr_cable_cap_nvlink_ext_pack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 160;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 160;
		reg_access_switch_pddr_link_active_eth_ext_pack(&(ptr_struct->link_active.pddr_link_active_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 160;
		reg_access_switch_pddr_link_active_ib_ext_pack(&(ptr_struct->link_active.pddr_link_active_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 160;
		reg_access_switch_pddr_link_active_nvlink_ext_pack(&(ptr_struct->link_active.pddr_link_active_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->loopback_mode);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pri_or_sec);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_mode_request);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_mode_active);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_100g_fec_support);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_25g_50g_fec_support);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->profile_fec_in_use);
	offset = 288;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 288;
		reg_access_switch_pd_link_eth_enabled_ext_pack(&(ptr_struct->pd_link_enabled.pd_link_eth_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 288;
		reg_access_switch_pd_link_ib_enabled_ext_pack(&(ptr_struct->pd_link_enabled.pd_link_ib_enabled_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 320;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 320;
		reg_access_switch_hst_link_eth_enabled_ext_pack(&(ptr_struct->phy_hst_link_enabled.hst_link_eth_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 320;
		reg_access_switch_hst_link_ib_enabled_ext_pack(&(ptr_struct->phy_hst_link_enabled.hst_link_ib_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 320;
		reg_access_switch_hst_link_nvlink_enabled_ext_pack(&(ptr_struct->phy_hst_link_enabled.hst_link_nvlink_enabled_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_an_link_enabled);
	offset = 476;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_health);
	offset = 467;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attention_trigger);
	offset = 460;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->attention_trigger_metric);
	offset = 458;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->link_health_config_changed);
	offset = 448;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->test_mode_fsm_state);
	offset = 509;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->local_host_class);
	offset = 505;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->remote_host_class);
	offset = 499;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->channel_diff_loss);
}

void reg_access_switch_pddr_operation_info_page_ext_unpack(struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	ptr_struct->neg_mode_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->proto_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 3;
	ptr_struct->resilink_fec_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->ib_phy_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->eth_an_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->phy_mngr_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_unpack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_unpack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 64;
		reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_unpack(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 96;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_eth_ext_unpack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_ib_ext_unpack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 96;
		reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_unpack(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 128;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 128;
		reg_access_switch_pddr_cable_cap_eth_ext_unpack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_pddr_cable_cap_ib_ext_unpack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 128;
		reg_access_switch_pddr_cable_cap_nvlink_ext_unpack(&(ptr_struct->cable_proto_cap.pddr_cable_cap_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 160;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 160;
		reg_access_switch_pddr_link_active_eth_ext_unpack(&(ptr_struct->link_active.pddr_link_active_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 160;
		reg_access_switch_pddr_link_active_ib_ext_unpack(&(ptr_struct->link_active.pddr_link_active_ib_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 160;
		reg_access_switch_pddr_link_active_nvlink_ext_unpack(&(ptr_struct->link_active.pddr_link_active_nvlink_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 212;
	ptr_struct->loopback_mode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 208;
	ptr_struct->pri_or_sec = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 240;
	ptr_struct->fec_mode_request = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->fec_mode_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 284;
	ptr_struct->eth_100g_fec_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->eth_25g_50g_fec_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->profile_fec_in_use = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 288;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 288;
		reg_access_switch_pd_link_eth_enabled_ext_unpack(&(ptr_struct->pd_link_enabled.pd_link_eth_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 288;
		reg_access_switch_pd_link_ib_enabled_ext_unpack(&(ptr_struct->pd_link_enabled.pd_link_ib_enabled_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 320;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 320;
		reg_access_switch_hst_link_eth_enabled_ext_unpack(&(ptr_struct->phy_hst_link_enabled.hst_link_eth_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 320;
		reg_access_switch_hst_link_ib_enabled_ext_unpack(&(ptr_struct->phy_hst_link_enabled.hst_link_ib_enabled_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 320;
		reg_access_switch_hst_link_nvlink_enabled_ext_unpack(&(ptr_struct->phy_hst_link_enabled.hst_link_nvlink_enabled_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 352;
	ptr_struct->eth_an_link_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 476;
	ptr_struct->link_health = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 467;
	ptr_struct->attention_trigger = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 460;
	ptr_struct->attention_trigger_metric = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 458;
	ptr_struct->link_health_config_changed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 448;
	ptr_struct->test_mode_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 509;
	ptr_struct->local_host_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 505;
	ptr_struct->remote_host_class = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 499;
	ptr_struct->channel_diff_loss = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_switch_pddr_operation_info_page_ext_print(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_operation_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "neg_mode_active      : %s (" UH_FMT ")\n", (ptr_struct->neg_mode_active == 0 ? ("protocol_was_not_negotiated") : ((ptr_struct->neg_mode_active == 1 ? ("MLPN_rev0_negotiated") : ((ptr_struct->neg_mode_active == 2 ? ("CL73_Ethernet_negotiated") : ((ptr_struct->neg_mode_active == 3 ? ("Protocol_according_to_Parallel_detect") : ((ptr_struct->neg_mode_active == 4 ? ("Standard_IB_negotiated") : ("unknown")))))))))), ptr_struct->neg_mode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "proto_active         : %s (" UH_FMT ")\n", (ptr_struct->proto_active == 1 ? ("InfiniBand") : ((ptr_struct->proto_active == 4 ? ("Ethernet") : ((ptr_struct->proto_active == 8 ? ("NVLink") : ("unknown")))))), ptr_struct->proto_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resilink_fec_ind     : " UH_FMT "\n", ptr_struct->resilink_fec_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_phy_fsm_state     : %s (" UH_FMT ")\n", (ptr_struct->ib_phy_fsm_state == 0 ? ("IB_AN_FSM_DISABLED") : ((ptr_struct->ib_phy_fsm_state == 1 ? ("IB_AN_FSM_INITIALY") : ((ptr_struct->ib_phy_fsm_state == 2 ? ("IB_AN_FSM_RCVR_CFG") : ((ptr_struct->ib_phy_fsm_state == 3 ? ("IB_AN_FSM_CFG_TEST") : ((ptr_struct->ib_phy_fsm_state == 4 ? ("IB_AN_FSM_WAIT_RMT_TEST") : ((ptr_struct->ib_phy_fsm_state == 5 ? ("IB_AN_FSM_WAIT_CFG_ENHANCED") : ((ptr_struct->ib_phy_fsm_state == 6 ? ("IB_AN_FSM_CFG_IDLE") : ((ptr_struct->ib_phy_fsm_state == 7 ? ("IB_AN_FSM_LINK_UP") : ((ptr_struct->ib_phy_fsm_state == 8 ? ("IB_AN_FSM_POLLING") : ("unknown")))))))))))))))))), ptr_struct->ib_phy_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_fsm_state     : " UH_FMT "\n", ptr_struct->eth_an_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_mngr_fsm_state   : %s (" UH_FMT ")\n", (ptr_struct->phy_mngr_fsm_state == 0 ? ("Disabled") : ((ptr_struct->phy_mngr_fsm_state == 1 ? ("Open_port") : ((ptr_struct->phy_mngr_fsm_state == 2 ? ("Polling") : ((ptr_struct->phy_mngr_fsm_state == 3 ? ("Active") : ((ptr_struct->phy_mngr_fsm_state == 4 ? ("Close_port") : ((ptr_struct->phy_mngr_fsm_state == 5 ? ("Phy_up") : ((ptr_struct->phy_mngr_fsm_state == 6 ? ("Sleep") : ((ptr_struct->phy_mngr_fsm_state == 7 ? ("Rx_disable") : ((ptr_struct->phy_mngr_fsm_state == 8 ? ("Signal_detect") : ((ptr_struct->phy_mngr_fsm_state == 9 ? ("Receiver_detect") : ((ptr_struct->phy_mngr_fsm_state == 10 ? ("Sync_peer") : ((ptr_struct->phy_mngr_fsm_state == 11 ? ("Negotiation") : ((ptr_struct->phy_mngr_fsm_state == 12 ? ("Training") : ((ptr_struct->phy_mngr_fsm_state == 13 ? ("SubFSM_active") : ((ptr_struct->phy_mngr_fsm_state == 14 ? ("Protocol_Detect") : ((ptr_struct->phy_mngr_fsm_state == 15 ? ("Unkown") : ((ptr_struct->phy_mngr_fsm_state == 16 ? ("Reserved") : ((ptr_struct->phy_mngr_fsm_state == 17 ? ("Waiting_state") : ("unknown")))))))))))))))))))))))))))))))))))), ptr_struct->phy_mngr_fsm_state);
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_phy_manager_link_enabled_eth_ext:\n");
		reg_access_switch_pddr_phy_manager_link_enabled_eth_ext_print(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_eth_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_phy_manager_link_enabled_ib_ext:\n");
		reg_access_switch_pddr_phy_manager_link_enabled_ib_ext_print(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_ib_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_phy_manager_link_enabled_nvlink_ext:\n");
		reg_access_switch_pddr_phy_manager_link_enabled_nvlink_ext_print(&(ptr_struct->phy_manager_link_enabled.pddr_phy_manager_link_enabled_nvlink_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_c2p_link_enabled_eth_ext:\n");
		reg_access_switch_pddr_c2p_link_enabled_eth_ext_print(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_eth_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_c2p_link_enabled_ib_ext:\n");
		reg_access_switch_pddr_c2p_link_enabled_ib_ext_print(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_ib_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_c2p_link_enabled_nvlink_ext:\n");
		reg_access_switch_pddr_c2p_link_enabled_nvlink_ext_print(&(ptr_struct->core_to_phy_link_enabled.pddr_c2p_link_enabled_nvlink_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_cable_cap_eth_ext:\n");
		reg_access_switch_pddr_cable_cap_eth_ext_print(&(ptr_struct->cable_proto_cap.pddr_cable_cap_eth_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_cable_cap_ib_ext:\n");
		reg_access_switch_pddr_cable_cap_ib_ext_print(&(ptr_struct->cable_proto_cap.pddr_cable_cap_ib_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_cable_cap_nvlink_ext:\n");
		reg_access_switch_pddr_cable_cap_nvlink_ext_print(&(ptr_struct->cable_proto_cap.pddr_cable_cap_nvlink_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_active_eth_ext:\n");
		reg_access_switch_pddr_link_active_eth_ext_print(&(ptr_struct->link_active.pddr_link_active_eth_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_active_ib_ext:\n");
		reg_access_switch_pddr_link_active_ib_ext_print(&(ptr_struct->link_active.pddr_link_active_ib_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_active_nvlink_ext:\n");
		reg_access_switch_pddr_link_active_nvlink_ext_print(&(ptr_struct->link_active.pddr_link_active_nvlink_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "loopback_mode        : %s (" UH_FMT ")\n", (ptr_struct->loopback_mode == 0 ? ("No_loopback_active") : ((ptr_struct->loopback_mode == 1 ? ("Phy_remote_loopback") : ((ptr_struct->loopback_mode == 2 ? ("Phy_local_loopback") : ((ptr_struct->loopback_mode == 4 ? ("External_local_loopback") : ("unknown")))))))), ptr_struct->loopback_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pri_or_sec           : %s (" UH_FMT ")\n", (ptr_struct->pri_or_sec == 0 ? ("Not_supported_or_not_chosen_yet") : ((ptr_struct->pri_or_sec == 1 ? ("Primary") : ((ptr_struct->pri_or_sec == 2 ? ("Secondary") : ("unknown")))))), ptr_struct->pri_or_sec);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_mode_request     : " UH_FMT "\n", ptr_struct->fec_mode_request);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_mode_active      : %s (" UH_FMT ")\n", (ptr_struct->fec_mode_active == 0 ? ("No_FEC") : ((ptr_struct->fec_mode_active == 1 ? ("Firecode_FEC") : ((ptr_struct->fec_mode_active == 2 ? ("Standard_RS_FEC") : ((ptr_struct->fec_mode_active == 3 ? ("Standard_LL_RS_FEC") : ((ptr_struct->fec_mode_active == 4 ? ("Interleaved_Quad_RS_FEC") : ((ptr_struct->fec_mode_active == 5 ? ("Interleaved_Quad_RS_FEC_PLR") : ((ptr_struct->fec_mode_active == 6 ? ("Interleaved_Standard_RS_FEC") : ((ptr_struct->fec_mode_active == 7 ? ("Standard_RS_KP4_FEC") : ((ptr_struct->fec_mode_active == 8 ? ("Interleaved_Octet_RS_FEC_PLR") : ((ptr_struct->fec_mode_active == 9 ? ("Ethernet_Consortium_LL_50G_RS_FEC") : ((ptr_struct->fec_mode_active == 10 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC") : ((ptr_struct->fec_mode_active == 11 ? ("Interleaved_Standard_RS_FEC_PLR") : ((ptr_struct->fec_mode_active == 12 ? ("RS_FEC") : ((ptr_struct->fec_mode_active == 13 ? ("LL_FEC") : ((ptr_struct->fec_mode_active == 14 ? ("Ethernet_Consortium_LL_50G_RS_FEC_PLR") : ((ptr_struct->fec_mode_active == 15 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR") : ((ptr_struct->fec_mode_active == 16 ? ("Interleaved_Double_RS_Half_KP4_FEC_PLR") : ((ptr_struct->fec_mode_active == 17 ? ("Interleaved_Quad_RS_Half_KP4_FEC_PLR") : ((ptr_struct->fec_mode_active == 18 ? ("Interleaved_Octet_RS_Half_KP4_FEC_PLR") : ("unknown")))))))))))))))))))))))))))))))))))))), ptr_struct->fec_mode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_100g_fec_support : " UH_FMT "\n", ptr_struct->eth_100g_fec_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_25g_50g_fec_support : " UH_FMT "\n", ptr_struct->eth_25g_50g_fec_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "profile_fec_in_use   : " UH_FMT "\n", ptr_struct->profile_fec_in_use);
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pd_link_eth_enabled_ext:\n");
		reg_access_switch_pd_link_eth_enabled_ext_print(&(ptr_struct->pd_link_enabled.pd_link_eth_enabled_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pd_link_ib_enabled_ext:\n");
		reg_access_switch_pd_link_ib_enabled_ext_print(&(ptr_struct->pd_link_enabled.pd_link_ib_enabled_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hst_link_eth_enabled_ext:\n");
		reg_access_switch_hst_link_eth_enabled_ext_print(&(ptr_struct->phy_hst_link_enabled.hst_link_eth_enabled_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hst_link_ib_enabled_ext:\n");
		reg_access_switch_hst_link_ib_enabled_ext_print(&(ptr_struct->phy_hst_link_enabled.hst_link_ib_enabled_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hst_link_nvlink_enabled_ext:\n");
		reg_access_switch_hst_link_nvlink_enabled_ext_print(&(ptr_struct->phy_hst_link_enabled.hst_link_nvlink_enabled_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_link_enabled  : " U32H_FMT "\n", ptr_struct->eth_an_link_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_health          : " UH_FMT "\n", ptr_struct->link_health);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attention_trigger    : %s (" UH_FMT ")\n", (ptr_struct->attention_trigger == 0 ? ("N_A") : ((ptr_struct->attention_trigger == 1 ? ("PLR_Tx_BW_Loss") : ((ptr_struct->attention_trigger == 2 ? ("Recovery_BW_Loss") : ((ptr_struct->attention_trigger == 3 ? ("Effective_BER") : ((ptr_struct->attention_trigger == 4 ? ("symbol_error_count") : ((ptr_struct->attention_trigger == 5 ? ("Raw_BER") : ((ptr_struct->attention_trigger == 6 ? ("PLR_Rx_BW_Loss") : ((ptr_struct->attention_trigger == 7 ? ("Port_total_BW_Loss") : ((ptr_struct->attention_trigger == 8 ? ("Link_down_count") : ((ptr_struct->attention_trigger == 9 ? ("Symbol_BER") : ("unknown")))))))))))))))))))), ptr_struct->attention_trigger);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attention_trigger_metric : %s (" UH_FMT ")\n", (ptr_struct->attention_trigger_metric == 0 ? ("N_A") : ((ptr_struct->attention_trigger_metric == 1 ? ("metric1") : ((ptr_struct->attention_trigger_metric == 2 ? ("metric2") : ((ptr_struct->attention_trigger_metric == 3 ? ("metric3") : ((ptr_struct->attention_trigger_metric == 4 ? ("metric4") : ((ptr_struct->attention_trigger_metric == 5 ? ("metric5") : ((ptr_struct->attention_trigger_metric == 6 ? ("metric6") : ((ptr_struct->attention_trigger_metric == 7 ? ("metric7") : ((ptr_struct->attention_trigger_metric == 8 ? ("metric8") : ((ptr_struct->attention_trigger_metric == 9 ? ("metric9") : ((ptr_struct->attention_trigger_metric == 10 ? ("metric10") : ((ptr_struct->attention_trigger_metric == 11 ? ("metric11") : ((ptr_struct->attention_trigger_metric == 12 ? ("metric12") : ((ptr_struct->attention_trigger_metric == 13 ? ("metric13") : ((ptr_struct->attention_trigger_metric == 14 ? ("metric14") : ((ptr_struct->attention_trigger_metric == 15 ? ("metric15") : ("unknown")))))))))))))))))))))))))))))))), ptr_struct->attention_trigger_metric);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_health_config_changed : %s (" UH_FMT ")\n", (ptr_struct->link_health_config_changed == 0 ? ("N_A") : ((ptr_struct->link_health_config_changed == 1 ? ("Attention") : ((ptr_struct->link_health_config_changed == 2 ? ("Attention") : ("unknown")))))), ptr_struct->link_health_config_changed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "test_mode_fsm_state  : %s (" UH_FMT ")\n", (ptr_struct->test_mode_fsm_state == 0 ? ("Disable") : ((ptr_struct->test_mode_fsm_state == 1 ? ("Open_lane") : ((ptr_struct->test_mode_fsm_state == 2 ? ("Idle_mode_b") : ((ptr_struct->test_mode_fsm_state == 3 ? ("Close_lane") : ((ptr_struct->test_mode_fsm_state == 4 ? ("Receiver_detect") : ((ptr_struct->test_mode_fsm_state == 5 ? ("Idle_mode_a") : ((ptr_struct->test_mode_fsm_state == 6 ? ("Signal_detect") : ((ptr_struct->test_mode_fsm_state == 7 ? ("Auto_fix_reversal_polarity") : ((ptr_struct->test_mode_fsm_state == 8 ? ("Tuning_in_progress") : ("unknown")))))))))))))))))), ptr_struct->test_mode_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_host_class     : " UH_FMT "\n", ptr_struct->local_host_class);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_host_class    : " UH_FMT "\n", ptr_struct->remote_host_class);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "channel_diff_loss    : " UH_FMT "\n", ptr_struct->channel_diff_loss);
}

unsigned int reg_access_switch_pddr_operation_info_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_OPERATION_INFO_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_operation_info_page_ext_dump(const struct reg_access_switch_pddr_operation_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_operation_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_phy_info_page_ext_pack(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_notifications);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->negotiation_mask);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->remote_device_type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lp_ib_revision);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_revision);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_negotiation_attempts);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->phy_manager_disable_mask);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hw_link_phy_state);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pcs_phy_state);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lp_proto_enabled);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lp_fec_mode_request);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lp_fec_mode_support);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ib_last_link_down_reason);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(248, 8, i, 1984, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->eth_last_link_down_lane[i]);
	}
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->speed_deg_db);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->degrade_grade_lane0);
	offset = 360;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->degrade_grade_lane1);
	offset = 392;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->degrade_grade_lane2);
	offset = 424;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->degrade_grade_lane3);
	offset = 475;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane7);
	offset = 467;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane6);
	offset = 459;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane5);
	offset = 451;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane4);
	offset = 496;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_5);
	offset = 480;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_4);
	offset = 528;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_7);
	offset = 512;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_6);
	offset = 571;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane3);
	offset = 563;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane2);
	offset = 555;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane1);
	offset = 547;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->num_of_presets_tested_lane0);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(600, 8, i, 1984, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->kr_startup_fsm_lane[i]);
	}
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_an_debug_indication);
	offset = 688;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_phy_fsm_state_trace);
	offset = 683;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->rounds_waited_for_peer_to_end_test);
	offset = 681;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->eth_an_watchdog_cnt);
	offset = 678;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->fall_from_cfg_idle_cdr_cnt);
	offset = 675;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->fall_from_cfg_idle_cnt);
	offset = 672;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->cdr_not_locked_cnt);
	offset = 720;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_1);
	offset = 704;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_0);
	offset = 752;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_3);
	offset = 736;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->kr_startup_debug_indications_2);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(796, 4, i, 1984, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_tuning_stages_lane[i]);
	}
	offset = 824;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->plu_tx_pwrup);
	offset = 816;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->plu_rx_pwrup);
	offset = 808;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->plu_tx_polarity);
	offset = 800;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->plu_rx_polarity);
	offset = 860;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->irisc_status);
	offset = 858;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ib_cfg_delay_timeout);
	offset = 857;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sd_valid);
	offset = 852;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plu_tx_speed);
	offset = 848;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plu_rx_speed);
	offset = 832;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->signal_detected);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->stamping_reason);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->kr_frame_lock_tuning_failure_events_count);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->kr_full_tuning_failure_count);
	offset = 976;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->pm_debug_indication);
	offset = 960;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_debug_indication);
	offset = 1017;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->pm_catastrophic_enum);
	offset = 1016;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pm_cat_val);
	offset = 1009;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->an_catastrophic_enum);
	offset = 1008;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_cat_val);
	offset = 1001;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->hst_catastrophic_enum);
	offset = 1000;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->hst_cat_val);
	offset = 993;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->pd_catastrophic_enum);
	offset = 992;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pd_cat_val);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pd_debug_indication);
	offset = 1082;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->pd_count);
	offset = 1074;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->fp_signal_detect_count);
	offset = 1070;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->hst_mismatch_reason);
	offset = 1061;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->psi_collision2);
	offset = 1056;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->psi_collision1);
	offset = 1112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->nlpn_debug_ind_mask);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy2mod_speed_req);
	offset = 1176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phy2mod_deactivate_lanes);
	offset = 1168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phy2mod_ack_lanes);
	offset = 1154;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->one_pll_mod);
	offset = 1153;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->no_dme_mod);
	offset = 1152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->eeprom_prsnt);
	offset = 1214;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_bypass_mux_plt0);
	offset = 1212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_bypass_mux_plt1);
	offset = 1210;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_bypass_mux_plt0);
	offset = 1208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_bypass_mux_plt1);
	offset = 1206;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->reconciliation_mux_plt0);
	offset = 1204;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->reconciliation_mux_plt1);
	offset = 1203;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->macsec_en_plt0_s0);
	offset = 1202;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->macsec_en_plt0_s1);
	offset = 1201;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->macsec_en_plt1_s0);
	offset = 1200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->macsec_en_plt1_s1);
	offset = 1196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cnt_rx_frame_received_ok_s0);
	offset = 1192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cnt_rx_frame_received_ok_s1);
	offset = 1188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_pkts_inc_s0);
	offset = 1184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_pkts_inc_s1);
	offset = 1232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_ndr_4x_kp4_threshold);
	offset = 1216;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_hdr_threshold);
	offset = 1264;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_ndr_2x_kp4_threshold);
	offset = 1248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_xdr_1x_kp4_threshold);
	offset = 1296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_ndr_2x_ell_threshold);
	offset = 1280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_ndr_4x_ell_threshold);
	offset = 1328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_xdr_1x_ell_threshold);
	offset = 1312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_xdr_2x_kp4_threshold);
	offset = 1371;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->nv_link_generation);
	offset = 1344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_xdr_2x_ell_threshold);
	offset = 1564;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mode_b_fsm_state_lane_0);
	offset = 1560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mode_b_fsm_state_lane_1);
	offset = 1662;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->apsu_oper);
	offset = 1659;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->hop_count_oper);
	offset = 1656;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lt_peer_det_oper);
	offset = 1653;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->nlut_oper);
	offset = 1650;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->training_en_oper);
}

void reg_access_switch_pddr_phy_info_page_ext_unpack(struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->port_notifications = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->negotiation_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->remote_device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->lp_ib_revision = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ib_revision = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->num_of_negotiation_attempts = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->phy_manager_disable_mask = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 64;
	ptr_struct->hw_link_phy_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->pcs_phy_state = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->lp_proto_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 176;
	ptr_struct->lp_fec_mode_request = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->lp_fec_mode_support = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->ib_last_link_down_reason = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(248, 8, i, 1984, 1);
		ptr_struct->eth_last_link_down_lane[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 288;
	ptr_struct->speed_deg_db = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 328;
	ptr_struct->degrade_grade_lane0 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 360;
	ptr_struct->degrade_grade_lane1 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 392;
	ptr_struct->degrade_grade_lane2 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 424;
	ptr_struct->degrade_grade_lane3 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 475;
	ptr_struct->num_of_presets_tested_lane7 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 467;
	ptr_struct->num_of_presets_tested_lane6 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 459;
	ptr_struct->num_of_presets_tested_lane5 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 451;
	ptr_struct->num_of_presets_tested_lane4 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 496;
	ptr_struct->kr_startup_debug_indications_5 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 480;
	ptr_struct->kr_startup_debug_indications_4 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 528;
	ptr_struct->kr_startup_debug_indications_7 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 512;
	ptr_struct->kr_startup_debug_indications_6 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 571;
	ptr_struct->num_of_presets_tested_lane3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 563;
	ptr_struct->num_of_presets_tested_lane2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 555;
	ptr_struct->num_of_presets_tested_lane1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 547;
	ptr_struct->num_of_presets_tested_lane0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(600, 8, i, 1984, 1);
		ptr_struct->kr_startup_fsm_lane[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 640;
	ptr_struct->eth_an_debug_indication = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 688;
	ptr_struct->ib_phy_fsm_state_trace = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 683;
	ptr_struct->rounds_waited_for_peer_to_end_test = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 681;
	ptr_struct->eth_an_watchdog_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 678;
	ptr_struct->fall_from_cfg_idle_cdr_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 675;
	ptr_struct->fall_from_cfg_idle_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 672;
	ptr_struct->cdr_not_locked_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 720;
	ptr_struct->kr_startup_debug_indications_1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 704;
	ptr_struct->kr_startup_debug_indications_0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 752;
	ptr_struct->kr_startup_debug_indications_3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 736;
	ptr_struct->kr_startup_debug_indications_2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(796, 4, i, 1984, 1);
		ptr_struct->tx_tuning_stages_lane[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	}
	offset = 824;
	ptr_struct->plu_tx_pwrup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 816;
	ptr_struct->plu_rx_pwrup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 808;
	ptr_struct->plu_tx_polarity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 800;
	ptr_struct->plu_rx_polarity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 860;
	ptr_struct->irisc_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 858;
	ptr_struct->ib_cfg_delay_timeout = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 857;
	ptr_struct->sd_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 852;
	ptr_struct->plu_tx_speed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 848;
	ptr_struct->plu_rx_speed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->signal_detected = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 864;
	ptr_struct->stamping_reason = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->kr_frame_lock_tuning_failure_events_count = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->kr_full_tuning_failure_count = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 976;
	ptr_struct->pm_debug_indication = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 960;
	ptr_struct->ib_debug_indication = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1017;
	ptr_struct->pm_catastrophic_enum = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 1016;
	ptr_struct->pm_cat_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1009;
	ptr_struct->an_catastrophic_enum = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 1008;
	ptr_struct->an_cat_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1001;
	ptr_struct->hst_catastrophic_enum = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 1000;
	ptr_struct->hst_cat_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 993;
	ptr_struct->pd_catastrophic_enum = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 992;
	ptr_struct->pd_cat_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1024;
	ptr_struct->pd_debug_indication = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1082;
	ptr_struct->pd_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1074;
	ptr_struct->fp_signal_detect_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1070;
	ptr_struct->hst_mismatch_reason = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1061;
	ptr_struct->psi_collision2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 1056;
	ptr_struct->psi_collision1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 1112;
	ptr_struct->nlpn_debug_ind_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1120;
	ptr_struct->phy2mod_speed_req = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1176;
	ptr_struct->phy2mod_deactivate_lanes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1168;
	ptr_struct->phy2mod_ack_lanes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 1154;
	ptr_struct->one_pll_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1153;
	ptr_struct->no_dme_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1152;
	ptr_struct->eeprom_prsnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1214;
	ptr_struct->rx_bypass_mux_plt0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1212;
	ptr_struct->rx_bypass_mux_plt1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1210;
	ptr_struct->tx_bypass_mux_plt0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1208;
	ptr_struct->tx_bypass_mux_plt1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1206;
	ptr_struct->reconciliation_mux_plt0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1204;
	ptr_struct->reconciliation_mux_plt1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1203;
	ptr_struct->macsec_en_plt0_s0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1202;
	ptr_struct->macsec_en_plt0_s1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1201;
	ptr_struct->macsec_en_plt1_s0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1200;
	ptr_struct->macsec_en_plt1_s1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1196;
	ptr_struct->cnt_rx_frame_received_ok_s0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1192;
	ptr_struct->cnt_rx_frame_received_ok_s1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1188;
	ptr_struct->port_xmit_pkts_inc_s0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1184;
	ptr_struct->port_xmit_pkts_inc_s1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1232;
	ptr_struct->plr_rtt_ndr_4x_kp4_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1216;
	ptr_struct->plr_rtt_hdr_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1264;
	ptr_struct->plr_rtt_ndr_2x_kp4_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1248;
	ptr_struct->plr_rtt_xdr_1x_kp4_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1296;
	ptr_struct->plr_rtt_ndr_2x_ell_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1280;
	ptr_struct->plr_rtt_ndr_4x_ell_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1328;
	ptr_struct->plr_rtt_xdr_1x_ell_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1312;
	ptr_struct->plr_rtt_xdr_2x_kp4_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1371;
	ptr_struct->nv_link_generation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 1344;
	ptr_struct->plr_rtt_xdr_2x_ell_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1564;
	ptr_struct->mode_b_fsm_state_lane_0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1560;
	ptr_struct->mode_b_fsm_state_lane_1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1662;
	ptr_struct->apsu_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1659;
	ptr_struct->hop_count_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1656;
	ptr_struct->lt_peer_det_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1653;
	ptr_struct->nlut_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1650;
	ptr_struct->training_en_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_switch_pddr_phy_info_page_ext_print(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_phy_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_notifications   : " UH_FMT "\n", ptr_struct->port_notifications);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "negotiation_mask     : " UH_FMT "\n", ptr_struct->negotiation_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_device_type   : " UH_FMT "\n", ptr_struct->remote_device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_ib_revision       : " UH_FMT "\n", ptr_struct->lp_ib_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_revision          : " UH_FMT "\n", ptr_struct->ib_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_negotiation_attempts : " UH_FMT "\n", ptr_struct->num_of_negotiation_attempts);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_disable_mask : " UH_FMT "\n", ptr_struct->phy_manager_disable_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_link_phy_state    : %s (" UH_FMT ")\n", (ptr_struct->hw_link_phy_state == 16 ? ("sleeping_delay") : ((ptr_struct->hw_link_phy_state == 17 ? ("sleeping_quiet") : ((ptr_struct->hw_link_phy_state == 32 ? ("polling_active") : ((ptr_struct->hw_link_phy_state == 33 ? ("polling_quiet") : ((ptr_struct->hw_link_phy_state == 48 ? ("disable") : ((ptr_struct->hw_link_phy_state == 49 ? ("update_retimer") : ((ptr_struct->hw_link_phy_state == 64 ? ("config_debounce") : ((ptr_struct->hw_link_phy_state == 65 ? ("config_receiver") : ((ptr_struct->hw_link_phy_state == 66 ? ("config_wait_remote") : ((ptr_struct->hw_link_phy_state == 67 ? ("config_tx_reverse_lanes") : ((ptr_struct->hw_link_phy_state == 68 ? ("config_enhanced") : ((ptr_struct->hw_link_phy_state == 69 ? ("config_test") : ((ptr_struct->hw_link_phy_state == 70 ? ("confg_wait_remote_test") : ((ptr_struct->hw_link_phy_state == 71 ? ("config_wait_cfg_enhanced") : ((ptr_struct->hw_link_phy_state == 72 ? ("config_idle") : ((ptr_struct->hw_link_phy_state == 80 ? ("linkup") : ((ptr_struct->hw_link_phy_state == 81 ? ("Linkup_Tx_Idle") : ((ptr_struct->hw_link_phy_state == 82 ? ("Linkup_Tx_Empty") : ((ptr_struct->hw_link_phy_state == 96 ? ("recover_retrain") : ((ptr_struct->hw_link_phy_state == 97 ? ("recover_wait_remote") : ((ptr_struct->hw_link_phy_state == 98 ? ("recover_idle") : ((ptr_struct->hw_link_phy_state == 99 ? ("Local_down_cmd") : ((ptr_struct->hw_link_phy_state == 100 ? ("Remote_down_cmd") : ((ptr_struct->hw_link_phy_state == 101 ? ("uphy_recovery_send_ts1") : ((ptr_struct->hw_link_phy_state == 102 ? ("uphy_recovery_send_pam2") : ((ptr_struct->hw_link_phy_state == 103 ? ("uphy_recovery_send_pam4") : ((ptr_struct->hw_link_phy_state == 104 ? ("uphy_recovery_peq") : ((ptr_struct->hw_link_phy_state == 112 ? ("test") : ((ptr_struct->hw_link_phy_state == 128 ? ("Force_send_ts1") : ((ptr_struct->hw_link_phy_state == 144 ? ("Force_send_ts2") : ((ptr_struct->hw_link_phy_state == 160 ? ("Force_Sent_Idle") : ((ptr_struct->hw_link_phy_state == 176 ? ("Force_send_ts_Mlnx") : ((ptr_struct->hw_link_phy_state == 192 ? ("Force_send_ts3") : ((ptr_struct->hw_link_phy_state == 208 ? ("Force_LinkUp") : ((ptr_struct->hw_link_phy_state == 224 ? ("Go_To_Quiet") : ((ptr_struct->hw_link_phy_state == 225 ? ("Retimer_Align") : ((ptr_struct->hw_link_phy_state == 226 ? ("Quiet_Entry") : ((ptr_struct->hw_link_phy_state == 227 ? ("Quiet") : ((ptr_struct->hw_link_phy_state == 228 ? ("Wake") : ((ptr_struct->hw_link_phy_state == 229 ? ("Wake_Tx_Sleep0") : ((ptr_struct->hw_link_phy_state == 230 ? ("Send_Announce") : ((ptr_struct->hw_link_phy_state == 231 ? ("Tx_HS") : ((ptr_struct->hw_link_phy_state == 232 ? ("Wait_For_Cdr_Lock") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->hw_link_phy_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcs_phy_state        : " U32H_FMT "\n", ptr_struct->pcs_phy_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_proto_enabled     : " U32H_FMT "\n", ptr_struct->lp_proto_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_fec_mode_request  : " UH_FMT "\n", ptr_struct->lp_fec_mode_request);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_fec_mode_support  : " UH_FMT "\n", ptr_struct->lp_fec_mode_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_last_link_down_reason : " U32H_FMT "\n", ptr_struct->ib_last_link_down_reason);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_last_link_down_lane_%03d : " UH_FMT "\n", i, ptr_struct->eth_last_link_down_lane[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "speed_deg_db         : " U32H_FMT "\n", ptr_struct->speed_deg_db);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "degrade_grade_lane0  : " UH_FMT "\n", ptr_struct->degrade_grade_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "degrade_grade_lane1  : " UH_FMT "\n", ptr_struct->degrade_grade_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "degrade_grade_lane2  : " UH_FMT "\n", ptr_struct->degrade_grade_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "degrade_grade_lane3  : " UH_FMT "\n", ptr_struct->degrade_grade_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane7 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane6 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane5 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane4 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_5 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_4 : %s (" UH_FMT ")\n", (ptr_struct->kr_startup_debug_indications_4 == 1 ? ("Local_frame_lock") : ((ptr_struct->kr_startup_debug_indications_4 == 2 ? ("Remote_frame_lock") : ((ptr_struct->kr_startup_debug_indications_4 == 4 ? ("Local_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_4 == 8 ? ("Remote_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_4 == 16 ? ("Local_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_4 == 32 ? ("Remote_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_4 == 64 ? ("max_wait_timer_expired") : ((ptr_struct->kr_startup_debug_indications_4 == 128 ? ("Wait_timer_done") : ((ptr_struct->kr_startup_debug_indications_4 == 256 ? ("Hold_off_timer_expired") : ((ptr_struct->kr_startup_debug_indications_4 == 512 ? ("link_fail_inhibit_timer_expired") : ("unknown")))))))))))))))))))), ptr_struct->kr_startup_debug_indications_4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_7 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_6 : %s (" UH_FMT ")\n", (ptr_struct->kr_startup_debug_indications_6 == 1 ? ("Local_frame_lock") : ((ptr_struct->kr_startup_debug_indications_6 == 2 ? ("Remote_frame_lock") : ((ptr_struct->kr_startup_debug_indications_6 == 4 ? ("Local_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_6 == 8 ? ("Remote_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_6 == 16 ? ("Local_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_6 == 32 ? ("Remote_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_6 == 64 ? ("max_wait_timer_expired") : ((ptr_struct->kr_startup_debug_indications_6 == 128 ? ("Wait_timer_done") : ((ptr_struct->kr_startup_debug_indications_6 == 256 ? ("Hold_off_timer_expired") : ((ptr_struct->kr_startup_debug_indications_6 == 512 ? ("link_fail_inhibit_timer_expired") : ("unknown")))))))))))))))))))), ptr_struct->kr_startup_debug_indications_6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane3 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane2 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane1 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_presets_tested_lane0 : " UH_FMT "\n", ptr_struct->num_of_presets_tested_lane0);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "kr_startup_fsm_lane_%03d : %s (" UH_FMT ")\n", i, (ptr_struct->kr_startup_fsm_lane[i] == 0 ? ("KR_FSM_INITIALIZE") : ((ptr_struct->kr_startup_fsm_lane[i] == 1 ? ("KR_FSM_SEND_TRAINING") : ((ptr_struct->kr_startup_fsm_lane[i] == 2 ? ("KR_FSM_TRAIN_LOCAL_TX") : ((ptr_struct->kr_startup_fsm_lane[i] == 3 ? ("KR_FSM_TRAIN_LOCAL_RX") : ((ptr_struct->kr_startup_fsm_lane[i] == 4 ? ("KR_FSM_TRAIN_REMOTE") : ((ptr_struct->kr_startup_fsm_lane[i] == 5 ? ("KR_FSM_LINK_READY") : ((ptr_struct->kr_startup_fsm_lane[i] == 6 ? ("KR_FSM_SEND_DATA") : ((ptr_struct->kr_startup_fsm_lane[i] == 7 ? ("KR_FSM_NVLT") : ((ptr_struct->kr_startup_fsm_lane[i] == 8 ? ("KR_ABORT") : ((ptr_struct->kr_startup_fsm_lane[i] == 9 ? ("KR_TIMEOUT") : ((ptr_struct->kr_startup_fsm_lane[i] == 10 ? ("KR_FSM_IN_IDLE") : ("unknown")))))))))))))))))))))), ptr_struct->kr_startup_fsm_lane[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_debug_indication : " U32H_FMT "\n", ptr_struct->eth_an_debug_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_phy_fsm_state_trace : " UH_FMT "\n", ptr_struct->ib_phy_fsm_state_trace);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rounds_waited_for_peer_to_end_test : " UH_FMT "\n", ptr_struct->rounds_waited_for_peer_to_end_test);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_watchdog_cnt  : " UH_FMT "\n", ptr_struct->eth_an_watchdog_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fall_from_cfg_idle_cdr_cnt : " UH_FMT "\n", ptr_struct->fall_from_cfg_idle_cdr_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fall_from_cfg_idle_cnt : " UH_FMT "\n", ptr_struct->fall_from_cfg_idle_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_not_locked_cnt   : " UH_FMT "\n", ptr_struct->cdr_not_locked_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_1 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_0 : %s (" UH_FMT ")\n", (ptr_struct->kr_startup_debug_indications_0 == 1 ? ("Local_frame_lock") : ((ptr_struct->kr_startup_debug_indications_0 == 2 ? ("Remote_frame_lock") : ((ptr_struct->kr_startup_debug_indications_0 == 4 ? ("Local_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_0 == 8 ? ("Remote_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_0 == 16 ? ("Local_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_0 == 32 ? ("Remote_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_0 == 64 ? ("max_wait_timer_expired") : ((ptr_struct->kr_startup_debug_indications_0 == 128 ? ("Wait_timer_done") : ((ptr_struct->kr_startup_debug_indications_0 == 256 ? ("Hold_off_timer_expired") : ((ptr_struct->kr_startup_debug_indications_0 == 512 ? ("link_fail_inhibit_timer_expired") : ("unknown")))))))))))))))))))), ptr_struct->kr_startup_debug_indications_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_3 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_2 : %s (" UH_FMT ")\n", (ptr_struct->kr_startup_debug_indications_2 == 1 ? ("Local_frame_lock") : ((ptr_struct->kr_startup_debug_indications_2 == 2 ? ("Remote_frame_lock") : ((ptr_struct->kr_startup_debug_indications_2 == 4 ? ("Local_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_2 == 8 ? ("Remote_Frame_lock_timer_expired") : ((ptr_struct->kr_startup_debug_indications_2 == 16 ? ("Local_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_2 == 32 ? ("Remote_receiver_ready") : ((ptr_struct->kr_startup_debug_indications_2 == 64 ? ("max_wait_timer_expired") : ((ptr_struct->kr_startup_debug_indications_2 == 128 ? ("Wait_timer_done") : ((ptr_struct->kr_startup_debug_indications_2 == 256 ? ("Hold_off_timer_expired") : ((ptr_struct->kr_startup_debug_indications_2 == 512 ? ("link_fail_inhibit_timer_expired") : ("unknown")))))))))))))))))))), ptr_struct->kr_startup_debug_indications_2);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "tx_tuning_stages_lane_%03d : %s (" UH_FMT ")\n", i, (ptr_struct->tx_tuning_stages_lane[i] == 1 ? ("Single_preset_stage") : ((ptr_struct->tx_tuning_stages_lane[i] == 2 ? ("multiple_preset_stage") : ((ptr_struct->tx_tuning_stages_lane[i] == 4 ? ("LMS") : ("unknown")))))), ptr_struct->tx_tuning_stages_lane[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_tx_pwrup         : " UH_FMT "\n", ptr_struct->plu_tx_pwrup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_rx_pwrup         : " UH_FMT "\n", ptr_struct->plu_rx_pwrup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_tx_polarity      : " UH_FMT "\n", ptr_struct->plu_tx_polarity);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_rx_polarity      : " UH_FMT "\n", ptr_struct->plu_rx_polarity);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "irisc_status         : " UH_FMT "\n", ptr_struct->irisc_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_cfg_delay_timeout : " UH_FMT "\n", ptr_struct->ib_cfg_delay_timeout);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sd_valid             : " UH_FMT "\n", ptr_struct->sd_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_tx_speed         : " UH_FMT "\n", ptr_struct->plu_tx_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plu_rx_speed         : " UH_FMT "\n", ptr_struct->plu_rx_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signal_detected      : " UH_FMT "\n", ptr_struct->signal_detected);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stamping_reason      : %s (" U32H_FMT ")\n", (ptr_struct->stamping_reason == 1 ? ("com_codes_is_zero") : ((ptr_struct->stamping_reason == 2 ? ("rx_cdr_check_force_mode") : ((ptr_struct->stamping_reason == 4 ? ("com_code_compliance") : ((ptr_struct->stamping_reason == 8 ? ("eth_56g_stamped") : ((ptr_struct->stamping_reason == 16 ? ("non_mlx_qsfp_transceiver") : ((ptr_struct->stamping_reason == 32 ? ("non_mlx_sfp_transceiver") : ((ptr_struct->stamping_reason == 64 ? ("ib_comp_codes") : ((ptr_struct->stamping_reason == 128 ? ("edr_comp") : ((ptr_struct->stamping_reason == 256 ? ("fdr_comp") : ("unknown")))))))))))))))))), ptr_struct->stamping_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_frame_lock_tuning_failure_events_count : " U32H_FMT "\n", ptr_struct->kr_frame_lock_tuning_failure_events_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_full_tuning_failure_count : " U32H_FMT "\n", ptr_struct->kr_full_tuning_failure_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pm_debug_indication  : %s (" UH_FMT ")\n", (ptr_struct->pm_debug_indication == 1 ? ("phy_test_mode") : ((ptr_struct->pm_debug_indication == 2 ? ("force_mode_en") : ("unknown")))), ptr_struct->pm_debug_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_debug_indication  : %s (" UH_FMT ")\n", (ptr_struct->ib_debug_indication == 1 ? ("cause_plr_tx_max_outstanding_cells") : ("unknown")), ptr_struct->ib_debug_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pm_catastrophic_enum : " UH_FMT "\n", ptr_struct->pm_catastrophic_enum);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pm_cat_val           : " UH_FMT "\n", ptr_struct->pm_cat_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_catastrophic_enum : " UH_FMT "\n", ptr_struct->an_catastrophic_enum);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_cat_val           : " UH_FMT "\n", ptr_struct->an_cat_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_catastrophic_enum : " UH_FMT "\n", ptr_struct->hst_catastrophic_enum);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_cat_val          : " UH_FMT "\n", ptr_struct->hst_cat_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_catastrophic_enum : " UH_FMT "\n", ptr_struct->pd_catastrophic_enum);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_cat_val           : " UH_FMT "\n", ptr_struct->pd_cat_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_debug_indication  : %s (" U32H_FMT ")\n", (ptr_struct->pd_debug_indication == 1 ? ("speed_change_high_speed_module") : ((ptr_struct->pd_debug_indication == 2 ? ("False_positive_signal_detect") : ((ptr_struct->pd_debug_indication == 4 ? ("Nv2nv_force") : ((ptr_struct->pd_debug_indication == 8 ? ("bad_kr_mask") : ((ptr_struct->pd_debug_indication == 16 ? ("kr_mlx_peer") : ((ptr_struct->pd_debug_indication == 32 ? ("entered_signal_detect") : ((ptr_struct->pd_debug_indication == 64 ? ("entered_rate_config") : ((ptr_struct->pd_debug_indication == 128 ? ("entered_activate_sunfsm") : ((ptr_struct->pd_debug_indication == 256 ? ("entered_done") : ((ptr_struct->pd_debug_indication == 512 ? ("entered_subfsm_fail") : ("unknown")))))))))))))))))))), ptr_struct->pd_debug_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pd_count             : " UH_FMT "\n", ptr_struct->pd_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fp_signal_detect_count : " UH_FMT "\n", ptr_struct->fp_signal_detect_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hst_mismatch_reason  : " UH_FMT "\n", ptr_struct->hst_mismatch_reason);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psi_collision2       : " UH_FMT "\n", ptr_struct->psi_collision2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "psi_collision1       : " UH_FMT "\n", ptr_struct->psi_collision1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nlpn_debug_ind_mask  : %s (" UH_FMT ")\n", (ptr_struct->nlpn_debug_ind_mask == 1 ? ("nonce_match_fail") : ((ptr_struct->nlpn_debug_ind_mask == 2 ? ("timeout") : ((ptr_struct->nlpn_debug_ind_mask == 4 ? ("hs_neg") : ((ptr_struct->nlpn_debug_ind_mask == 8 ? ("dme_neg") : ("unknown")))))))), ptr_struct->nlpn_debug_ind_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy2mod_speed_req    : " U32H_FMT "\n", ptr_struct->phy2mod_speed_req);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy2mod_deactivate_lanes : " UH_FMT "\n", ptr_struct->phy2mod_deactivate_lanes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy2mod_ack_lanes    : " UH_FMT "\n", ptr_struct->phy2mod_ack_lanes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "one_pll_mod          : " UH_FMT "\n", ptr_struct->one_pll_mod);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_dme_mod           : " UH_FMT "\n", ptr_struct->no_dme_mod);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eeprom_prsnt         : " UH_FMT "\n", ptr_struct->eeprom_prsnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_bypass_mux_plt0   : " UH_FMT "\n", ptr_struct->rx_bypass_mux_plt0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_bypass_mux_plt1   : " UH_FMT "\n", ptr_struct->rx_bypass_mux_plt1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bypass_mux_plt0   : " UH_FMT "\n", ptr_struct->tx_bypass_mux_plt0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_bypass_mux_plt1   : " UH_FMT "\n", ptr_struct->tx_bypass_mux_plt1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reconciliation_mux_plt0 : " UH_FMT "\n", ptr_struct->reconciliation_mux_plt0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reconciliation_mux_plt1 : " UH_FMT "\n", ptr_struct->reconciliation_mux_plt1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "macsec_en_plt0_s0    : " UH_FMT "\n", ptr_struct->macsec_en_plt0_s0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "macsec_en_plt0_s1    : " UH_FMT "\n", ptr_struct->macsec_en_plt0_s1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "macsec_en_plt1_s0    : " UH_FMT "\n", ptr_struct->macsec_en_plt1_s0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "macsec_en_plt1_s1    : " UH_FMT "\n", ptr_struct->macsec_en_plt1_s1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnt_rx_frame_received_ok_s0 : " UH_FMT "\n", ptr_struct->cnt_rx_frame_received_ok_s0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnt_rx_frame_received_ok_s1 : " UH_FMT "\n", ptr_struct->cnt_rx_frame_received_ok_s1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_pkts_inc_s0 : " UH_FMT "\n", ptr_struct->port_xmit_pkts_inc_s0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_pkts_inc_s1 : " UH_FMT "\n", ptr_struct->port_xmit_pkts_inc_s1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_ndr_4x_kp4_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_ndr_4x_kp4_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_hdr_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_hdr_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_ndr_2x_kp4_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_ndr_2x_kp4_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_xdr_1x_kp4_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_xdr_1x_kp4_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_ndr_2x_ell_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_ndr_2x_ell_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_ndr_4x_ell_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_ndr_4x_ell_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_xdr_1x_ell_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_xdr_1x_ell_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_xdr_2x_kp4_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_xdr_2x_kp4_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nv_link_generation   : %s (" UH_FMT ")\n", (ptr_struct->nv_link_generation == 0 ? ("nv_link_5") : ((ptr_struct->nv_link_generation == 1 ? ("nv_link_6") : ((ptr_struct->nv_link_generation == 2 ? ("nv_link_7") : ((ptr_struct->nv_link_generation == 3 ? ("nv_link_8") : ("unknown")))))))), ptr_struct->nv_link_generation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_xdr_2x_ell_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_xdr_2x_ell_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode_b_fsm_state_lane_0 : " UH_FMT "\n", ptr_struct->mode_b_fsm_state_lane_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode_b_fsm_state_lane_1 : " UH_FMT "\n", ptr_struct->mode_b_fsm_state_lane_1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apsu_oper            : " UH_FMT "\n", ptr_struct->apsu_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hop_count_oper       : " UH_FMT "\n", ptr_struct->hop_count_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lt_peer_det_oper     : " UH_FMT "\n", ptr_struct->lt_peer_det_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nlut_oper            : " UH_FMT "\n", ptr_struct->nlut_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "training_en_oper     : " UH_FMT "\n", ptr_struct->training_en_oper);
}

unsigned int reg_access_switch_pddr_phy_info_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_PHY_INFO_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_phy_info_page_ext_dump(const struct reg_access_switch_pddr_phy_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_phy_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_troubleshooting_page_ext_pack(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->group_opcode);
	offset = 32;
	switch (ptr_struct->group_opcode) {
	case 0x0:
		offset = 32;
		reg_access_switch_pddr_monitor_opcode_ext_pack(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 1984, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status_message[i]);
	}
}

void reg_access_switch_pddr_troubleshooting_page_ext_unpack(struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->group_opcode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	switch (ptr_struct->group_opcode) {
	case 0x0:
		offset = 32;
		reg_access_switch_pddr_monitor_opcode_ext_unpack(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 1984, 1);
		ptr_struct->status_message[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_pddr_troubleshooting_page_ext_print(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_troubleshooting_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "group_opcode         : %s (" UH_FMT ")\n", (ptr_struct->group_opcode == 0 ? ("Monitor_opcodes") : ("unknown")), ptr_struct->group_opcode);
	switch (ptr_struct->group_opcode) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_monitor_opcode_ext:\n");
		reg_access_switch_pddr_monitor_opcode_ext_print(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "status_message_%03d  : " U32H_FMT "\n", i, ptr_struct->status_message[i]);
	}
}

unsigned int reg_access_switch_pddr_troubleshooting_page_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_TROUBLESHOOTING_PAGE_EXT_SIZE;
}

void reg_access_switch_pddr_troubleshooting_page_ext_dump(const struct reg_access_switch_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_troubleshooting_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ppcl_cause_configurations_ext_pack(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clr_on_read_admin);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clr_on_link_rst_admin);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clr_on_read_oper);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clr_on_link_rst_oper);
}

void reg_access_switch_ppcl_cause_configurations_ext_unpack(struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->clr_on_read_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 27;
	ptr_struct->clr_on_link_rst_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 24;
	ptr_struct->clr_on_read_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 21;
	ptr_struct->clr_on_link_rst_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_ppcl_cause_configurations_ext_print(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ppcl_cause_configurations_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr_on_read_admin    : %s (" UH_FMT ")\n", (ptr_struct->clr_on_read_admin == 0 ? ("fw_default") : ((ptr_struct->clr_on_read_admin == 1 ? ("clear") : ((ptr_struct->clr_on_read_admin == 2 ? ("do_not_clear") : ("unknown")))))), ptr_struct->clr_on_read_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr_on_link_rst_admin : %s (" UH_FMT ")\n", (ptr_struct->clr_on_link_rst_admin == 0 ? ("fw_default") : ((ptr_struct->clr_on_link_rst_admin == 1 ? ("clear") : ((ptr_struct->clr_on_link_rst_admin == 2 ? ("do_not_clear") : ("unknown")))))), ptr_struct->clr_on_link_rst_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr_on_read_oper     : " UH_FMT "\n", ptr_struct->clr_on_read_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr_on_link_rst_oper : " UH_FMT "\n", ptr_struct->clr_on_link_rst_oper);
}

unsigned int reg_access_switch_ppcl_cause_configurations_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCL_CAUSE_CONFIGURATIONS_EXT_SIZE;
}

void reg_access_switch_ppcl_cause_configurations_ext_dump(const struct reg_access_switch_ppcl_cause_configurations_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ppcl_cause_configurations_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_pack(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->nvlink_phy6_cause_list1);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->nvlink_phy6_cause_list2);
}

void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_unpack(struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->nvlink_phy6_cause_list1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->nvlink_phy6_cause_list2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_print(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvlink_phy6_cause_list1 : " U32H_FMT "\n", ptr_struct->nvlink_phy6_cause_list1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "nvlink_phy6_cause_list2 : " U32H_FMT "\n", ptr_struct->nvlink_phy6_cause_list2);
}

unsigned int reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCL_CAUSE_LIST_FOR_NVLINK_PHY_GEN6_EXT_SIZE;
}

void reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_dump(const struct reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_prm_register_payload_ext_pack(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->register_id);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->method);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->register_data[i]);
	}
}

void reg_access_switch_prm_register_payload_ext_unpack(struct reg_access_switch_prm_register_payload_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->register_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->method = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 64; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 2080, 1);
		ptr_struct->register_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_prm_register_payload_ext_print(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_prm_register_payload_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "register_id          : " UH_FMT "\n", ptr_struct->register_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "method               : " UH_FMT "\n", ptr_struct->method);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	for (i = 0; i < 64; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "register_data_%03d   : " U32H_FMT "\n", i, ptr_struct->register_data[i]);
	}
}

unsigned int reg_access_switch_prm_register_payload_ext_size(void)
{
	return REG_ACCESS_SWITCH_PRM_REGISTER_PAYLOAD_EXT_SIZE;
}

void reg_access_switch_prm_register_payload_ext_dump(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_prm_register_payload_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_data_auto_ext_pack(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	/* conditioned union: use parent struct _pack/_unpack (inlined by adb2pack) */
	(void)ptr_struct;
	(void)ptr_buff;
}

void reg_access_switch_MRFV_data_auto_ext_unpack(union reg_access_switch_MRFV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	/* conditioned union: use parent struct _pack/_unpack (inlined by adb2pack) */
	(void)ptr_struct;
	(void)ptr_buff;
}

void reg_access_switch_MRFV_data_auto_ext_print(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	(void)ptr_struct;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_data_auto_ext ========\n");
}

unsigned int reg_access_switch_MRFV_data_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_DATA_AUTO_EXT_SIZE;
}

void reg_access_switch_MRFV_data_auto_ext_dump(const union reg_access_switch_MRFV_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ef_mcce_entry_v1_ext_pack(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cdb_error_code);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mcc_error_code);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_id);
}

void reg_access_switch_ef_mcce_entry_v1_ext_unpack(struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->cdb_error_code = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->mcc_error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->module_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_ef_mcce_entry_v1_ext_print(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ef_mcce_entry_v1_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdb_error_code       : " UH_FMT "\n", ptr_struct->cdb_error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcc_error_code       : " UH_FMT "\n", ptr_struct->mcc_error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_id            : " UH_FMT "\n", ptr_struct->module_id);
}

unsigned int reg_access_switch_ef_mcce_entry_v1_ext_size(void)
{
	return REG_ACCESS_SWITCH_EF_MCCE_ENTRY_V1_EXT_SIZE;
}

void reg_access_switch_ef_mcce_entry_v1_ext_dump(const struct reg_access_switch_ef_mcce_entry_v1_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ef_mcce_entry_v1_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_lane_2_module_mapping_ext_pack(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_lane);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_lane);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mode_b_map);
}

void reg_access_switch_lane_2_module_mapping_ext_unpack(struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 16;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 12;
	ptr_struct->tx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->rx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1;
	ptr_struct->mode_b_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_lane_2_module_mapping_ext_print(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_lane_2_module_mapping_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lane              : " UH_FMT "\n", ptr_struct->tx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_lane              : " UH_FMT "\n", ptr_struct->rx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode_b_map           : " UH_FMT "\n", ptr_struct->mode_b_map);
}

unsigned int reg_access_switch_lane_2_module_mapping_ext_size(void)
{
	return REG_ACCESS_SWITCH_LANE_2_MODULE_MAPPING_EXT_SIZE;
}

void reg_access_switch_lane_2_module_mapping_ext_dump(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_lane_2_module_mapping_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_mddq_slot_name_ext_pack(&(ptr_struct->mddq_slot_name_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_mddq_slot_name_ext_unpack(&(ptr_struct->mddq_slot_name_ext), ptr_buff);
}

void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_device_info_ext:\n");
	reg_access_switch_mddq_device_info_ext_print(&(ptr_struct->mddq_device_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_slot_info_ext:\n");
	reg_access_switch_mddq_slot_info_ext_print(&(ptr_struct->mddq_slot_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_slot_name_ext:\n");
	reg_access_switch_mddq_slot_name_ext_print(&(ptr_struct->mddq_slot_name_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_mddq_data_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_DATA_AUTO_EXT_SIZE;
}

void reg_access_switch_mddq_data_auto_ext_dump(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddt_reg_payload_auto_ext_pack(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_prm_register_payload_ext_pack(&(ptr_struct->prm_register_payload_ext), ptr_buff);
}

void reg_access_switch_mddt_reg_payload_auto_ext_unpack(union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_prm_register_payload_ext_unpack(&(ptr_struct->prm_register_payload_ext), ptr_buff);
}

void reg_access_switch_mddt_reg_payload_auto_ext_print(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddt_reg_payload_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "command_payload_ext:\n");
	reg_access_switch_command_payload_ext_print(&(ptr_struct->command_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "crspace_access_payload_ext:\n");
	reg_access_switch_crspace_access_payload_ext_print(&(ptr_struct->crspace_access_payload_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prm_register_payload_ext:\n");
	reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->prm_register_payload_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_mddt_reg_payload_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDT_REG_PAYLOAD_AUTO_EXT_SIZE;
}

void reg_access_switch_mddt_reg_payload_auto_ext_dump(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddt_reg_payload_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mgpir_hw_info_ext_pack(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_devices);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules_per_system);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->devices_per_flash);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_slots);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_modules_per_slot);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_resource_modules);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->total_num_of_module_i2c_bus);
	offset = 76;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_lanes_per_sub_module);
	offset = 68;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_sub_modules_index);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules_msb);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_modules_per_system_msb);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_modules_per_slot_msb);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->els_count_local);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_count_local);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->els_count_global);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_count_global);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tl_module_non_mission_count_local);
}

void reg_access_switch_mgpir_hw_info_ext_unpack(struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->num_of_devices = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->num_of_modules_per_system = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->devices_per_flash = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->num_of_modules = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->num_of_slots = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->max_modules_per_slot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->num_of_resource_modules = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->total_num_of_module_i2c_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 76;
	ptr_struct->num_lanes_per_sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 68;
	ptr_struct->max_sub_modules_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 120;
	ptr_struct->num_of_modules_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->num_of_modules_per_system_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->max_modules_per_slot_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->els_count_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->oe_count_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 176;
	ptr_struct->els_count_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->oe_count_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 208;
	ptr_struct->tl_module_non_mission_count_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mgpir_hw_info_ext_print(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mgpir_hw_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_devices       : " UH_FMT "\n", ptr_struct->num_of_devices);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules_per_system : " UH_FMT "\n", ptr_struct->num_of_modules_per_system);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "devices_per_flash    : " UH_FMT "\n", ptr_struct->devices_per_flash);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules       : " UH_FMT "\n", ptr_struct->num_of_modules);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_slots         : " UH_FMT "\n", ptr_struct->num_of_slots);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_modules_per_slot : " UH_FMT "\n", ptr_struct->max_modules_per_slot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_resource_modules : " UH_FMT "\n", ptr_struct->num_of_resource_modules);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "total_num_of_module_i2c_bus : " UH_FMT "\n", ptr_struct->total_num_of_module_i2c_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_lanes_per_sub_module : " UH_FMT "\n", ptr_struct->num_lanes_per_sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_sub_modules_index : " UH_FMT "\n", ptr_struct->max_sub_modules_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules_msb   : " UH_FMT "\n", ptr_struct->num_of_modules_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_modules_per_system_msb : " UH_FMT "\n", ptr_struct->num_of_modules_per_system_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_modules_per_slot_msb : " UH_FMT "\n", ptr_struct->max_modules_per_slot_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_count_local      : " UH_FMT "\n", ptr_struct->els_count_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_count_local       : " UH_FMT "\n", ptr_struct->oe_count_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_count_global     : " UH_FMT "\n", ptr_struct->els_count_global);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_count_global      : " UH_FMT "\n", ptr_struct->oe_count_global);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tl_module_non_mission_count_local : " UH_FMT "\n", ptr_struct->tl_module_non_mission_count_local);
}

unsigned int reg_access_switch_mgpir_hw_info_ext_size(void)
{
	return REG_ACCESS_SWITCH_MGPIR_HW_INFO_EXT_SIZE;
}

void reg_access_switch_mgpir_hw_info_ext_dump(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mgpir_hw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mgpir_hw_metadata_ext_pack(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tl_module_mission_base_index_local);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tl_module_mission_base_index_global);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tl_module_non_mission_base_index_local);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tl_module_non_mission_base_index_global);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->els_base_index_local);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->els_base_index_global);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_base_index_local);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_base_index_global);
}

void reg_access_switch_mgpir_hw_metadata_ext_unpack(struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->tl_module_mission_base_index_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->tl_module_mission_base_index_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->tl_module_non_mission_base_index_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->tl_module_non_mission_base_index_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->els_base_index_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->els_base_index_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->oe_base_index_local = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->oe_base_index_global = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mgpir_hw_metadata_ext_print(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mgpir_hw_metadata_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tl_module_mission_base_index_local : " UH_FMT "\n", ptr_struct->tl_module_mission_base_index_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tl_module_mission_base_index_global : " UH_FMT "\n", ptr_struct->tl_module_mission_base_index_global);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tl_module_non_mission_base_index_local : " UH_FMT "\n", ptr_struct->tl_module_non_mission_base_index_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tl_module_non_mission_base_index_global : " UH_FMT "\n", ptr_struct->tl_module_non_mission_base_index_global);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_base_index_local : " UH_FMT "\n", ptr_struct->els_base_index_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_base_index_global : " UH_FMT "\n", ptr_struct->els_base_index_global);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_base_index_local  : " UH_FMT "\n", ptr_struct->oe_base_index_local);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_base_index_global : " UH_FMT "\n", ptr_struct->oe_base_index_global);
}

unsigned int reg_access_switch_mgpir_hw_metadata_ext_size(void)
{
	return REG_ACCESS_SWITCH_MGPIR_HW_METADATA_EXT_SIZE;
}

void reg_access_switch_mgpir_hw_metadata_ext_dump(const struct reg_access_switch_mgpir_hw_metadata_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mgpir_hw_metadata_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mmta_tec_power_ext_pack(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cooling_level);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->temp_unit);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtpr);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtpe);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_tec_power);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_warning_low);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_warning_high);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_alarm_low);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->tec_power_alarm_high);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_set_point_temperature);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_warning_low);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_warning_high);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_alarm_low);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->set_point_temperature_alarm_high);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->min_cooling_level);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_cooling_level);
}

void reg_access_switch_mmta_tec_power_ext_unpack(struct reg_access_switch_mmta_tec_power_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 2;
	ptr_struct->temp_unit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->mtpr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->mtpe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->tec_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->max_tec_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->tec_power_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->tec_power_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->tec_power_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->tec_power_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->set_point_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->max_set_point_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 176;
	ptr_struct->set_point_temperature_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->set_point_temperature_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 208;
	ptr_struct->set_point_temperature_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->set_point_temperature_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 240;
	ptr_struct->min_cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->max_cooling_level = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mmta_tec_power_ext_print(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_tec_power_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cooling_level        : " UH_FMT "\n", ptr_struct->cooling_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temp_unit            : " UH_FMT "\n", ptr_struct->temp_unit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtpr                 : " UH_FMT "\n", ptr_struct->mtpr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtpe                 : " UH_FMT "\n", ptr_struct->mtpe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power            : " UH_FMT "\n", ptr_struct->tec_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_tec_power        : " UH_FMT "\n", ptr_struct->max_tec_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_warning_low : " UH_FMT "\n", ptr_struct->tec_power_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_warning_high : " UH_FMT "\n", ptr_struct->tec_power_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_alarm_low  : " UH_FMT "\n", ptr_struct->tec_power_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tec_power_alarm_high : " UH_FMT "\n", ptr_struct->tec_power_alarm_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature : " UH_FMT "\n", ptr_struct->set_point_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_set_point_temperature : " UH_FMT "\n", ptr_struct->max_set_point_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_warning_low : " UH_FMT "\n", ptr_struct->set_point_temperature_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_warning_high : " UH_FMT "\n", ptr_struct->set_point_temperature_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_alarm_low : " UH_FMT "\n", ptr_struct->set_point_temperature_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "set_point_temperature_alarm_high : " UH_FMT "\n", ptr_struct->set_point_temperature_alarm_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_cooling_level    : " UH_FMT "\n", ptr_struct->min_cooling_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_cooling_level    : " UH_FMT "\n", ptr_struct->max_cooling_level);
}

unsigned int reg_access_switch_mmta_tec_power_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_TEC_POWER_EXT_SIZE;
}

void reg_access_switch_mmta_tec_power_ext_dump(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_tec_power_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mmta_temprature_ext_pack(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ref_module_valid);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->temp_unit);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->twee);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->twe);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtr);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mte);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_temperature);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_warning_low);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_warning_high);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_alarm_low);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_alarm_high);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ref_module);
}

void reg_access_switch_mmta_temprature_ext_unpack(struct reg_access_switch_mmta_temprature_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 6;
	ptr_struct->ref_module_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->temp_unit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->twee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 2;
	ptr_struct->twe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->mtr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->mte = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->max_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->temperature_warning_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->temperature_warning_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->temperature_alarm_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->temperature_alarm_high = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->ref_module = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mmta_temprature_ext_print(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_temprature_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ref_module_valid     : " UH_FMT "\n", ptr_struct->ref_module_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temp_unit            : " UH_FMT "\n", ptr_struct->temp_unit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "twee                 : %s (" UH_FMT ")\n", (ptr_struct->twee == 0 ? ("do_not_generate_event") : ((ptr_struct->twee == 1 ? ("generate_events") : ((ptr_struct->twee == 2 ? ("generate_single_event") : ("unknown")))))), ptr_struct->twee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "twe                  : " UH_FMT "\n", ptr_struct->twe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtr                  : " UH_FMT "\n", ptr_struct->mtr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mte                  : " UH_FMT "\n", ptr_struct->mte);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_temperature      : " UH_FMT "\n", ptr_struct->max_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_warning_low : " UH_FMT "\n", ptr_struct->temperature_warning_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_warning_high : " UH_FMT "\n", ptr_struct->temperature_warning_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_alarm_low : " UH_FMT "\n", ptr_struct->temperature_alarm_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_alarm_high : " UH_FMT "\n", ptr_struct->temperature_alarm_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ref_module           : " UH_FMT "\n", ptr_struct->ref_module);
}

unsigned int reg_access_switch_mmta_temprature_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_TEMPRATURE_EXT_SIZE;
}

void reg_access_switch_mmta_temprature_ext_dump(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_temprature_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_reg_page_data_auto_ext_pack(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_troubleshooting_page_ext_pack(&(ptr_struct->pddr_troubleshooting_page_ext), ptr_buff);
}

void reg_access_switch_pddr_reg_page_data_auto_ext_unpack(union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_pddr_troubleshooting_page_ext_unpack(&(ptr_struct->pddr_troubleshooting_page_ext), ptr_buff);
}

void reg_access_switch_pddr_reg_page_data_auto_ext_print(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_latched_flag_info_ext:\n");
	reg_access_switch_module_latched_flag_info_ext_print(&(ptr_struct->module_latched_flag_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_apsu_info_page_ext:\n");
	reg_access_switch_pddr_apsu_info_page_ext_print(&(ptr_struct->pddr_apsu_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cpo_module_page_ext:\n");
	reg_access_switch_pddr_cpo_module_page_ext_print(&(ptr_struct->pddr_cpo_module_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_fec_measure_ltx_nvl5_ext:\n");
	reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_print(&(ptr_struct->pddr_fec_measure_ltx_nvl5_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_down_info_page_ext:\n");
	reg_access_switch_pddr_link_down_info_page_ext_print(&(ptr_struct->pddr_link_down_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_health_page_ext:\n");
	reg_access_switch_pddr_link_health_page_ext_print(&(ptr_struct->pddr_link_health_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_partner_info_ext:\n");
	reg_access_switch_pddr_link_partner_info_ext_print(&(ptr_struct->pddr_link_partner_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_up_info_page_ext:\n");
	reg_access_switch_pddr_link_up_info_page_ext_print(&(ptr_struct->pddr_link_up_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_module_info_ext:\n");
	reg_access_switch_pddr_module_info_ext_print(&(ptr_struct->pddr_module_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_operation_info_page_ext:\n");
	reg_access_switch_pddr_operation_info_page_ext_print(&(ptr_struct->pddr_operation_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_info_page_ext:\n");
	reg_access_switch_pddr_phy_info_page_ext_print(&(ptr_struct->pddr_phy_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_troubleshooting_page_ext:\n");
	reg_access_switch_pddr_troubleshooting_page_ext_print(&(ptr_struct->pddr_troubleshooting_page_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_pddr_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_switch_pddr_reg_page_data_auto_ext_dump(const union reg_access_switch_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ppcl_reg_page_data_auto_ext_pack(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_pack(&(ptr_struct->ppcl_cause_list_for_nvlink_phy_gen6_ext), ptr_buff);
}

void reg_access_switch_ppcl_reg_page_data_auto_ext_unpack(union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_unpack(&(ptr_struct->ppcl_cause_list_for_nvlink_phy_gen6_ext), ptr_buff);
}

void reg_access_switch_ppcl_reg_page_data_auto_ext_print(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ppcl_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcl_cause_configurations_ext:\n");
	reg_access_switch_ppcl_cause_configurations_ext_print(&(ptr_struct->ppcl_cause_configurations_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcl_cause_list_for_nvlink_phy_gen6_ext:\n");
	reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_print(&(ptr_struct->ppcl_cause_list_for_nvlink_phy_gen6_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_ppcl_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCL_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_switch_ppcl_reg_page_data_auto_ext_dump(const union reg_access_switch_ppcl_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ppcl_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MMAM_ext_pack(const struct reg_access_switch_MMAM_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_msb);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ga);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_module);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_module_msb);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_type);
}

void reg_access_switch_MMAM_ext_unpack(struct reg_access_switch_MMAM_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->module_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->ga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 88;
	ptr_struct->local_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->local_module_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->module_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_MMAM_ext_print(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MMAM_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_msb           : " UH_FMT "\n", ptr_struct->module_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ga                   : " UH_FMT "\n", ptr_struct->ga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_module         : " UH_FMT "\n", ptr_struct->local_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_module_msb     : " UH_FMT "\n", ptr_struct->local_module_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_type          : " UH_FMT "\n", ptr_struct->module_type);
}

unsigned int reg_access_switch_MMAM_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMAM_EXT_SIZE;
}

void reg_access_switch_MMAM_ext_dump(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MMAM_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_MRFV_ext_pack(const struct reg_access_switch_MRFV_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fuse_id);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->instance_id);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fm);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fm2);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fm_sel);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->module_index_valid);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->v);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_index);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_index_msb);
	offset = 128;
	if (ptr_struct->fuse_id == 0) {
		offset = 128;
		reg_access_switch_MRFV_CVB_ext_pack(&(ptr_struct->data.MRFV_CVB_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 2) {
		offset = 128;
		reg_access_switch_MRFV_PVS_MAIN_ext_pack(&(ptr_struct->data.MRFV_PVS_MAIN_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 3 || ptr_struct->fuse_id == 4 || ptr_struct->fuse_id == 5 || ptr_struct->fuse_id == 6 || ptr_struct->fuse_id == 7 || ptr_struct->fuse_id == 8 || ptr_struct->fuse_id == 9 || ptr_struct->fuse_id == 10) {
		offset = 128;
		reg_access_switch_MRFV_PVS_TILE_ext_pack(&(ptr_struct->data.MRFV_PVS_TILE_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 11 || ptr_struct->fuse_id == 12 || ptr_struct->fuse_id == 13 || ptr_struct->fuse_id == 15 || ptr_struct->fuse_id == 16 || ptr_struct->fuse_id == 17 || ptr_struct->fuse_id == 18 || ptr_struct->fuse_id == 19 || ptr_struct->fuse_id == 20 || ptr_struct->fuse_id == 21 || ptr_struct->fuse_id == 22 || ptr_struct->fuse_id == 23 || ptr_struct->fuse_id == 24 || ptr_struct->fuse_id == 25 || ptr_struct->fuse_id == 26 || ptr_struct->fuse_id == 27 || ptr_struct->fuse_id == 28) {
		offset = 128;
		reg_access_switch_MRFV_RAW_AND_VALUE_ext_pack(&(ptr_struct->data.MRFV_RAW_AND_VALUE_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 1) {
		offset = 128;
		reg_access_switch_MRFV_ULT_ext_pack(&(ptr_struct->data.MRFV_ULT_ext), ptr_buff + offset / 8);
	}
}

void reg_access_switch_MRFV_ext_unpack(struct reg_access_switch_MRFV_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->fuse_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->instance_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 6;
	ptr_struct->fm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 4;
	ptr_struct->fm2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 3;
	ptr_struct->fm_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->module_index_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->v = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->module_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->module_index_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	if (ptr_struct->fuse_id == 0) {
		offset = 128;
		reg_access_switch_MRFV_CVB_ext_unpack(&(ptr_struct->data.MRFV_CVB_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 2) {
		offset = 128;
		reg_access_switch_MRFV_PVS_MAIN_ext_unpack(&(ptr_struct->data.MRFV_PVS_MAIN_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 3 || ptr_struct->fuse_id == 4 || ptr_struct->fuse_id == 5 || ptr_struct->fuse_id == 6 || ptr_struct->fuse_id == 7 || ptr_struct->fuse_id == 8 || ptr_struct->fuse_id == 9 || ptr_struct->fuse_id == 10) {
		offset = 128;
		reg_access_switch_MRFV_PVS_TILE_ext_unpack(&(ptr_struct->data.MRFV_PVS_TILE_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 11 || ptr_struct->fuse_id == 12 || ptr_struct->fuse_id == 13 || ptr_struct->fuse_id == 15 || ptr_struct->fuse_id == 16 || ptr_struct->fuse_id == 17 || ptr_struct->fuse_id == 18 || ptr_struct->fuse_id == 19 || ptr_struct->fuse_id == 20 || ptr_struct->fuse_id == 21 || ptr_struct->fuse_id == 22 || ptr_struct->fuse_id == 23 || ptr_struct->fuse_id == 24 || ptr_struct->fuse_id == 25 || ptr_struct->fuse_id == 26 || ptr_struct->fuse_id == 27 || ptr_struct->fuse_id == 28) {
		offset = 128;
		reg_access_switch_MRFV_RAW_AND_VALUE_ext_unpack(&(ptr_struct->data.MRFV_RAW_AND_VALUE_ext), ptr_buff + offset / 8);
	}
	else if (ptr_struct->fuse_id == 1) {
		offset = 128;
		reg_access_switch_MRFV_ULT_ext_unpack(&(ptr_struct->data.MRFV_ULT_ext), ptr_buff + offset / 8);
	}
}

void reg_access_switch_MRFV_ext_print(const struct reg_access_switch_MRFV_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_MRFV_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fuse_id              : %s (" UH_FMT ")\n", (ptr_struct->fuse_id == 0 ? ("cvb") : ((ptr_struct->fuse_id == 1 ? ("ULT") : ((ptr_struct->fuse_id == 2 ? ("vdd_main_die") : ((ptr_struct->fuse_id == 3 ? ("vdd_tile_0") : ((ptr_struct->fuse_id == 4 ? ("vdd_tile_1") : ((ptr_struct->fuse_id == 5 ? ("vdd_tile_2") : ((ptr_struct->fuse_id == 6 ? ("vdd_tile_3") : ((ptr_struct->fuse_id == 7 ? ("vdd_tile_4") : ((ptr_struct->fuse_id == 8 ? ("vdd_tile_5") : ((ptr_struct->fuse_id == 9 ? ("vdd_tile_6") : ((ptr_struct->fuse_id == 10 ? ("vdd_tile_7") : ((ptr_struct->fuse_id == 11 ? ("raw_and_value_vdd") : ((ptr_struct->fuse_id == 12 ? ("raw_and_value_pl_avdd") : ((ptr_struct->fuse_id == 13 ? ("raw_and_value_pl_dvdd") : ((ptr_struct->fuse_id == 15 ? ("raw_and_value_opt_fuse_rev") : ((ptr_struct->fuse_id == 16 ? ("raw_and_value_dvdd_sg") : ((ptr_struct->fuse_id == 17 ? ("raw_and_value_opt_lot_code_0") : ((ptr_struct->fuse_id == 18 ? ("raw_and_value_opt_lot_code_1") : ((ptr_struct->fuse_id == 19 ? ("raw_and_value_opt_ops_reserved") : ((ptr_struct->fuse_id == 20 ? ("raw_and_value_opt_vendor_code") : ((ptr_struct->fuse_id == 21 ? ("raw_and_value_opt_wafer_id") : ((ptr_struct->fuse_id == 22 ? ("raw_and_value_opt_x_coordinate") : ((ptr_struct->fuse_id == 23 ? ("raw_and_value_opt_y_coordinate") : ((ptr_struct->fuse_id == 24 ? ("raw_and_value_opt_fab_code") : ((ptr_struct->fuse_id == 25 ? ("raw_and_value_ws_tp_version_0_31") : ((ptr_struct->fuse_id == 26 ? ("raw_and_value_ft_tp_version_0_31") : ((ptr_struct->fuse_id == 27 ? ("raw_and_value_fuse_ver_0_3") : ((ptr_struct->fuse_id == 28 ? ("raw_and_value_fuse_ver_4_7") : ((ptr_struct->fuse_id == 30 ? ("raw_and_value_dvdd") : ((ptr_struct->fuse_id == 31 ? ("raw_and_value_vddp") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->fuse_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "instance_id          : " UH_FMT "\n", ptr_struct->instance_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fm                   : " UH_FMT "\n", ptr_struct->fm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fm2                  : " UH_FMT "\n", ptr_struct->fm2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fm_sel               : " UH_FMT "\n", ptr_struct->fm_sel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_index_valid   : " UH_FMT "\n", ptr_struct->module_index_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "v                    : " UH_FMT "\n", ptr_struct->v);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_index         : " UH_FMT "\n", ptr_struct->module_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_index_msb     : " UH_FMT "\n", ptr_struct->module_index_msb);
	if (ptr_struct->fuse_id == 0) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_CVB_ext:\n");
		reg_access_switch_MRFV_CVB_ext_print(&(ptr_struct->data.MRFV_CVB_ext), fd, indent_level + 1);
	}
	else if (ptr_struct->fuse_id == 2) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_PVS_MAIN_ext:\n");
		reg_access_switch_MRFV_PVS_MAIN_ext_print(&(ptr_struct->data.MRFV_PVS_MAIN_ext), fd, indent_level + 1);
	}
	else if (ptr_struct->fuse_id == 3 || ptr_struct->fuse_id == 4 || ptr_struct->fuse_id == 5 || ptr_struct->fuse_id == 6 || ptr_struct->fuse_id == 7 || ptr_struct->fuse_id == 8 || ptr_struct->fuse_id == 9 || ptr_struct->fuse_id == 10) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_PVS_TILE_ext:\n");
		reg_access_switch_MRFV_PVS_TILE_ext_print(&(ptr_struct->data.MRFV_PVS_TILE_ext), fd, indent_level + 1);
	}
	else if (ptr_struct->fuse_id == 11 || ptr_struct->fuse_id == 12 || ptr_struct->fuse_id == 13 || ptr_struct->fuse_id == 15 || ptr_struct->fuse_id == 16 || ptr_struct->fuse_id == 17 || ptr_struct->fuse_id == 18 || ptr_struct->fuse_id == 19 || ptr_struct->fuse_id == 20 || ptr_struct->fuse_id == 21 || ptr_struct->fuse_id == 22 || ptr_struct->fuse_id == 23 || ptr_struct->fuse_id == 24 || ptr_struct->fuse_id == 25 || ptr_struct->fuse_id == 26 || ptr_struct->fuse_id == 27 || ptr_struct->fuse_id == 28) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_RAW_AND_VALUE_ext:\n");
		reg_access_switch_MRFV_RAW_AND_VALUE_ext_print(&(ptr_struct->data.MRFV_RAW_AND_VALUE_ext), fd, indent_level + 1);
	}
	else if (ptr_struct->fuse_id == 1) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_ULT_ext:\n");
		reg_access_switch_MRFV_ULT_ext_print(&(ptr_struct->data.MRFV_ULT_ext), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_MRFV_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRFV_EXT_SIZE;
}

void reg_access_switch_MRFV_ext_dump(const struct reg_access_switch_MRFV_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_MRFV_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_PPCR_ext_pack(const struct reg_access_switch_PPCR_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->asymmetry_enable);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->asymmetry_enable_supported);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->aggregated_port);
	offset = 77;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->plane);
	offset = 69;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->split);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_planes);
	offset = 109;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->p_type);
}

void reg_access_switch_PPCR_ext_unpack(struct reg_access_switch_PPCR_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 33;
	ptr_struct->asymmetry_enable = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->asymmetry_enable_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 88;
	ptr_struct->aggregated_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 77;
	ptr_struct->plane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 69;
	ptr_struct->split = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 120;
	ptr_struct->num_of_planes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 109;
	ptr_struct->p_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_switch_PPCR_ext_print(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_PPCR_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "asymmetry_enable     : %s (" UH_FMT ")\n", (ptr_struct->asymmetry_enable == 0 ? ("DISABLED") : ((ptr_struct->asymmetry_enable == 1 ? ("ENABLED") : ("unknown")))), ptr_struct->asymmetry_enable);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "asymmetry_enable_supported : %s (" UH_FMT ")\n", (ptr_struct->asymmetry_enable_supported == 0 ? ("NOT_SUPPORTED") : ((ptr_struct->asymmetry_enable_supported == 1 ? ("SUPPORTED") : ("unknown")))), ptr_struct->asymmetry_enable_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "aggregated_port      : " UH_FMT "\n", ptr_struct->aggregated_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane                : " UH_FMT "\n", ptr_struct->plane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split                : " UH_FMT "\n", ptr_struct->split);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_planes        : " UH_FMT "\n", ptr_struct->num_of_planes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p_type               : " UH_FMT "\n", ptr_struct->p_type);
}

unsigned int reg_access_switch_PPCR_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCR_EXT_SIZE;
}

void reg_access_switch_PPCR_ext_dump(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_PPCR_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_icam_reg_ext_pack(const struct reg_access_switch_icam_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 192, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->infr_access_reg_cap_mask[i]);
	}
}

void reg_access_switch_icam_reg_ext_unpack(struct reg_access_switch_icam_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 192, 1);
		ptr_struct->infr_access_reg_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_icam_reg_ext_print(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_icam_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : " UH_FMT "\n", ptr_struct->access_reg_group);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "infr_access_reg_cap_mask_%03d : " U32H_FMT "\n", i, ptr_struct->infr_access_reg_cap_mask[i]);
	}
}

unsigned int reg_access_switch_icam_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_ICAM_REG_EXT_SIZE;
}

void reg_access_switch_icam_reg_ext_dump(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_icam_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_icsr_ext_pack(const struct reg_access_switch_icsr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->base_address);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->num_reads);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 8320, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_switch_icsr_ext_unpack(struct reg_access_switch_icsr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	ptr_struct->base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 87;
	ptr_struct->num_reads = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	for (i = 0; i < 256; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 8320, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_icsr_ext_print(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_icsr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_address         : " U32H_FMT "\n", ptr_struct->base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_reads            : " UH_FMT "\n", ptr_struct->num_reads);
	for (i = 0; i < 256; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_switch_icsr_ext_size(void)
{
	return REG_ACCESS_SWITCH_ICSR_EXT_SIZE;
}

void reg_access_switch_icsr_ext_dump(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_icsr_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mcce_reg_ext_pack(const struct reg_access_switch_mcce_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_count);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->opcode);
	for (i = 0; i < 15; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_switch_ef_mcce_entry_v1_ext_pack(&(ptr_struct->entries[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_mcce_reg_ext_unpack(struct reg_access_switch_mcce_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	ptr_struct->error_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 15; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_switch_ef_mcce_entry_v1_ext_unpack(&(ptr_struct->entries[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_mcce_reg_ext_print(const struct reg_access_switch_mcce_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mcce_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_count          : " UH_FMT "\n", ptr_struct->error_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "opcode               : %s (" UH_FMT ")\n", (ptr_struct->opcode == 0 ? ("no_op") : ((ptr_struct->opcode == 1 ? ("clear") : ("unknown")))), ptr_struct->opcode);
	for (i = 0; i < 15; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "entries_%03d:\n", i);
		reg_access_switch_ef_mcce_entry_v1_ext_print(&(ptr_struct->entries[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_mcce_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MCCE_REG_EXT_SIZE;
}

void reg_access_switch_mcce_reg_ext_dump(const struct reg_access_switch_mcce_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mcce_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddq_ext_pack(const struct reg_access_switch_mddq_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->query_type);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sie);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->request_message_sequence);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->response_message_sequence);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->query_index);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->data_valid);
	offset = 128;
	switch (ptr_struct->query_type) {
	case 0x2:
		offset = 128;
		reg_access_switch_mddq_device_info_ext_pack(&(ptr_struct->data.mddq_device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_mddq_slot_info_ext_pack(&(ptr_struct->data.mddq_slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_mddq_slot_name_ext_pack(&(ptr_struct->data.mddq_slot_name_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddq_ext_unpack(struct reg_access_switch_mddq_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->query_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->sie = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->request_message_sequence = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->response_message_sequence = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->query_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->data_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	switch (ptr_struct->query_type) {
	case 0x2:
		offset = 128;
		reg_access_switch_mddq_device_info_ext_unpack(&(ptr_struct->data.mddq_device_info_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_switch_mddq_slot_info_ext_unpack(&(ptr_struct->data.mddq_slot_info_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_switch_mddq_slot_name_ext_unpack(&(ptr_struct->data.mddq_slot_name_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddq_ext_print(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddq_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_type           : %s (" UH_FMT ")\n", (ptr_struct->query_type == 0 ? ("Reserved") : ((ptr_struct->query_type == 1 ? ("slot_info") : ((ptr_struct->query_type == 2 ? ("device_info") : ((ptr_struct->query_type == 3 ? ("slot_name") : ("unknown")))))))), ptr_struct->query_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sie                  : " UH_FMT "\n", ptr_struct->sie);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "request_message_sequence : " UH_FMT "\n", ptr_struct->request_message_sequence);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "response_message_sequence : " UH_FMT "\n", ptr_struct->response_message_sequence);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_index          : " UH_FMT "\n", ptr_struct->query_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_valid           : " UH_FMT "\n", ptr_struct->data_valid);
	switch (ptr_struct->query_type) {
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_device_info_ext:\n");
		reg_access_switch_mddq_device_info_ext_print(&(ptr_struct->data.mddq_device_info_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_slot_info_ext:\n");
		reg_access_switch_mddq_slot_info_ext_print(&(ptr_struct->data.mddq_slot_info_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mddq_slot_name_ext:\n");
		reg_access_switch_mddq_slot_name_ext_print(&(ptr_struct->data.mddq_slot_name_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_mddq_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDQ_EXT_SIZE;
}

void reg_access_switch_mddq_ext_dump(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddq_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mddt_reg_ext_pack(const struct reg_access_switch_mddt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_index);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->type);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->write_size);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->read_size);
	offset = 96;
	switch (ptr_struct->type) {
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_pack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_pack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_pack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddt_reg_ext_unpack(struct reg_access_switch_mddt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 62;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 40;
	ptr_struct->write_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->read_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	switch (ptr_struct->type) {
	case 0x1:
		offset = 96;
		reg_access_switch_command_payload_ext_unpack(&(ptr_struct->payload.command_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 96;
		reg_access_switch_crspace_access_payload_ext_unpack(&(ptr_struct->payload.crspace_access_payload_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 96;
		reg_access_switch_prm_register_payload_ext_unpack(&(ptr_struct->payload.prm_register_payload_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_mddt_reg_ext_print(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mddt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : %s (" UH_FMT ")\n", (ptr_struct->type == 0 ? ("PRM_Register") : ((ptr_struct->type == 1 ? ("Command") : ((ptr_struct->type == 2 ? ("CrSpace_access") : ("unknown")))))), ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "write_size           : " UH_FMT "\n", ptr_struct->write_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "read_size            : " UH_FMT "\n", ptr_struct->read_size);
	switch (ptr_struct->type) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "command_payload_ext:\n");
		reg_access_switch_command_payload_ext_print(&(ptr_struct->payload.command_payload_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "crspace_access_payload_ext:\n");
		reg_access_switch_crspace_access_payload_ext_print(&(ptr_struct->payload.crspace_access_payload_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "prm_register_payload_ext:\n");
		reg_access_switch_prm_register_payload_ext_print(&(ptr_struct->payload.prm_register_payload_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_mddt_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDDT_REG_EXT_SIZE;
}

void reg_access_switch_mddt_reg_ext_dump(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mddt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mdsr_reg_ext_pack(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->additional_info);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_of_token);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->revoke_version);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->end);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_left);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->token_config);
}

void reg_access_switch_mdsr_reg_ext_unpack(struct reg_access_switch_mdsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->additional_info = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 0;
	ptr_struct->type_of_token = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 33;
	ptr_struct->revoke_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->end = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->time_left = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->token_config = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mdsr_reg_ext_print(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mdsr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "additional_info      : " UH_FMT "\n", ptr_struct->additional_info);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_of_token        : " UH_FMT "\n", ptr_struct->type_of_token);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "revoke_version       : " UH_FMT "\n", ptr_struct->revoke_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "end                  : " UH_FMT "\n", ptr_struct->end);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_left            : " U32H_FMT "\n", ptr_struct->time_left);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "token_config         : " U32H_FMT "\n", ptr_struct->token_config);
}

unsigned int reg_access_switch_mdsr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MDSR_REG_EXT_SIZE;
}

void reg_access_switch_mdsr_reg_ext_dump(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mdsr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mfcdr_reg_ext_pack(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->query_type);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->status);
}

void reg_access_switch_mfcdr_reg_ext_unpack(struct reg_access_switch_mfcdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->query_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_switch_mfcdr_reg_ext_print(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mfcdr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "query_type           : " UH_FMT "\n", ptr_struct->query_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
}

unsigned int reg_access_switch_mfcdr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MFCDR_REG_EXT_SIZE;
}

void reg_access_switch_mfcdr_reg_ext_dump(const struct reg_access_switch_mfcdr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mfcdr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mfkv_reg_ext_pack(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->efuses_prog_en);
	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fw_key_ver_stat);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->revoke_efuse_prog);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_efuse_prog);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fuse_failure);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->efuses_key_ver);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->img_key_ver);
}

void reg_access_switch_mfkv_reg_ext_unpack(struct reg_access_switch_mfkv_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->efuses_prog_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 29;
	ptr_struct->fw_key_ver_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 28;
	ptr_struct->revoke_efuse_prog = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 27;
	ptr_struct->pending_efuse_prog = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->fuse_failure = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->efuses_key_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->img_key_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mfkv_reg_ext_print(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mfkv_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "efuses_prog_en       : " UH_FMT "\n", ptr_struct->efuses_prog_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_key_ver_stat      : %s (" UH_FMT ")\n", (ptr_struct->fw_key_ver_stat == 0 ? ("equal") : ((ptr_struct->fw_key_ver_stat == 1 ? ("update_required") : ((ptr_struct->fw_key_ver_stat == 2 ? ("pending_image") : ((ptr_struct->fw_key_ver_stat == 3 ? ("reserved") : ("unknown")))))))), ptr_struct->fw_key_ver_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "revoke_efuse_prog    : %s (" UH_FMT ")\n", (ptr_struct->revoke_efuse_prog == 0 ? ("do_not_revoke") : ((ptr_struct->revoke_efuse_prog == 1 ? ("revoke") : ("unknown")))), ptr_struct->revoke_efuse_prog);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pending_efuse_prog   : %s (" UH_FMT ")\n", (ptr_struct->pending_efuse_prog == 0 ? ("no_pending_prog") : ((ptr_struct->pending_efuse_prog == 1 ? ("pending_prog") : ("unknown")))), ptr_struct->pending_efuse_prog);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fuse_failure         : " UH_FMT "\n", ptr_struct->fuse_failure);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index                : %s (" UH_FMT ")\n", (ptr_struct->index == 0 ? ("NCORE_FW") : ((ptr_struct->index == 1 ? ("PSC_BL1") : ((ptr_struct->index == 2 ? ("PSC_FW") : ((ptr_struct->index == 3 ? ("OEM") : ("unknown")))))))), ptr_struct->index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "efuses_key_ver       : " UH_FMT "\n", ptr_struct->efuses_key_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "img_key_ver          : " UH_FMT "\n", ptr_struct->img_key_ver);
}

unsigned int reg_access_switch_mfkv_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MFKV_REG_EXT_SIZE;
}

void reg_access_switch_mfkv_reg_ext_dump(const struct reg_access_switch_mfkv_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mfkv_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mfmc_reg_ext_pack(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->wrp_block_count);
	offset = 46;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->block_size);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->hw_wp_gpio);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->wrp_en);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->sub_sector_protect_size);
	offset = 82;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->sector_protect_size);
	offset = 135;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->quad_en);
	offset = 220;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dummy_clock_cycles);
}

void reg_access_switch_mfmc_reg_ext_unpack(struct reg_access_switch_mfmc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->wrp_block_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 46;
	ptr_struct->block_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 33;
	ptr_struct->hw_wp_gpio = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->wrp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 90;
	ptr_struct->sub_sector_protect_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 82;
	ptr_struct->sector_protect_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 135;
	ptr_struct->quad_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 220;
	ptr_struct->dummy_clock_cycles = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mfmc_reg_ext_print(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mfmc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fs                   : " UH_FMT "\n", ptr_struct->fs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrp_block_count      : " UH_FMT "\n", ptr_struct->wrp_block_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "block_size           : " UH_FMT "\n", ptr_struct->block_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_wp_gpio           : " UH_FMT "\n", ptr_struct->hw_wp_gpio);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrp_en               : " UH_FMT "\n", ptr_struct->wrp_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_sector_protect_size : " UH_FMT "\n", ptr_struct->sub_sector_protect_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sector_protect_size  : " UH_FMT "\n", ptr_struct->sector_protect_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "quad_en              : " UH_FMT "\n", ptr_struct->quad_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dummy_clock_cycles   : " UH_FMT "\n", ptr_struct->dummy_clock_cycles);
}

unsigned int reg_access_switch_mfmc_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MFMC_REG_EXT_SIZE;
}

void reg_access_switch_mfmc_reg_ext_dump(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mfmc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mgpir_ext_pack(const struct reg_access_switch_mgpir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_mgpir_hw_info_ext_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_switch_mgpir_hw_metadata_ext_pack(&(ptr_struct->hw_metadata), ptr_buff + offset / 8);
}

void reg_access_switch_mgpir_ext_unpack(struct reg_access_switch_mgpir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_switch_mgpir_hw_info_ext_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_switch_mgpir_hw_metadata_ext_unpack(&(ptr_struct->hw_metadata), ptr_buff + offset / 8);
}

void reg_access_switch_mgpir_ext_print(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mgpir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	reg_access_switch_mgpir_hw_info_ext_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_metadata:\n");
	reg_access_switch_mgpir_hw_metadata_ext_print(&(ptr_struct->hw_metadata), fd, indent_level + 1);
}

unsigned int reg_access_switch_mgpir_ext_size(void)
{
	return REG_ACCESS_SWITCH_MGPIR_EXT_SIZE;
}

void reg_access_switch_mgpir_ext_dump(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mgpir_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mkdc_reg_ext_pack(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_code);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->session_id);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->current_keep_alive_counter);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->next_keep_alive_counter);
}

void reg_access_switch_mkdc_reg_ext_unpack(struct reg_access_switch_mkdc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->session_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->current_keep_alive_counter = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->next_keep_alive_counter = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mkdc_reg_ext_print(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mkdc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code           : %s (" UH_FMT ")\n", (ptr_struct->error_code == 0 ? ("OK") : ((ptr_struct->error_code == 1 ? ("BAD_SESSION_ID") : ((ptr_struct->error_code == 2 ? ("BAD_KEEP_ALIVE_COUNTER") : ((ptr_struct->error_code == 3 ? ("BAD_SOURCE_ADDRESS") : ((ptr_struct->error_code == 4 ? ("SESSION_TIMEOUT") : ("unknown")))))))))), ptr_struct->error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "session_id           : " UH_FMT "\n", ptr_struct->session_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_keep_alive_counter : " U32H_FMT "\n", ptr_struct->current_keep_alive_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "next_keep_alive_counter : " U32H_FMT "\n", ptr_struct->next_keep_alive_counter);
}

unsigned int reg_access_switch_mkdc_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MKDC_REG_EXT_SIZE;
}

void reg_access_switch_mkdc_reg_ext_dump(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mkdc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mmta_reg_ext_pack(const struct reg_access_switch_mmta_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_msb);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_measurements);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_name_hi);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_name_lo);
	offset = 96;
	reg_access_switch_mmta_temprature_ext_pack(&(ptr_struct->module_temperature), ptr_buff + offset / 8);
	offset = 288;
	reg_access_switch_mmta_tec_power_ext_pack(&(ptr_struct->module_tec_power), ptr_buff + offset / 8);
	offset = 544;
	reg_access_switch_mmta_temprature_ext_pack(&(ptr_struct->module_second_temperature), ptr_buff + offset / 8);
}

void reg_access_switch_mmta_reg_ext_unpack(struct reg_access_switch_mmta_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->module_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->supported_measurements = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->module_name_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->module_name_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	reg_access_switch_mmta_temprature_ext_unpack(&(ptr_struct->module_temperature), ptr_buff + offset / 8);
	offset = 288;
	reg_access_switch_mmta_tec_power_ext_unpack(&(ptr_struct->module_tec_power), ptr_buff + offset / 8);
	offset = 544;
	reg_access_switch_mmta_temprature_ext_unpack(&(ptr_struct->module_second_temperature), ptr_buff + offset / 8);
}

void reg_access_switch_mmta_reg_ext_print(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mmta_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_msb           : " UH_FMT "\n", ptr_struct->module_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported_measurements : " UH_FMT "\n", ptr_struct->supported_measurements);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_name_hi       : " U32H_FMT "\n", ptr_struct->module_name_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_name_lo       : " U32H_FMT "\n", ptr_struct->module_name_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_temperature:\n");
	reg_access_switch_mmta_temprature_ext_print(&(ptr_struct->module_temperature), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_tec_power:\n");
	reg_access_switch_mmta_tec_power_ext_print(&(ptr_struct->module_tec_power), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_second_temperature:\n");
	reg_access_switch_mmta_temprature_ext_print(&(ptr_struct->module_second_temperature), fd, indent_level + 1);
}

unsigned int reg_access_switch_mmta_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MMTA_REG_EXT_SIZE;
}

void reg_access_switch_mmta_reg_ext_dump(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mmta_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mord_v2_ext_pack(const struct reg_access_switch_mord_v2_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->segment_type);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->seq_num);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vhca_id_valid);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->inline_dump);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->more_dump);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vhca_id);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->data_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index1);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->index2);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_obj2);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_obj1);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->device_opaque);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mkey);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->size);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->address);
	int num_of_items_in_array = (int)ptr_struct->data_size;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 32 * num_of_items_in_array + reg_access_switch_mord_v2_ext_size() * 8, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->inline_data[i]);
	}
}

void reg_access_switch_mord_v2_ext_unpack(struct reg_access_switch_mord_v2_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->segment_type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 12;
	ptr_struct->seq_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 2;
	ptr_struct->vhca_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->inline_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->more_dump = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->vhca_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 35;
	ptr_struct->data_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);
	offset = 64;
	ptr_struct->index1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->index2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->num_of_obj2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->num_of_obj1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->device_opaque = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 256;
	ptr_struct->mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->address = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	int num_of_items_in_array = (int)ptr_struct->data_size;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 32 * num_of_items_in_array + reg_access_switch_mord_v2_ext_size() * 8, 1);
		ptr_struct->inline_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_mord_v2_ext_print(const struct reg_access_switch_mord_v2_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mord_v2_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_type         : " UH_FMT "\n", ptr_struct->segment_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "seq_num              : " UH_FMT "\n", ptr_struct->seq_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vhca_id_valid        : " UH_FMT "\n", ptr_struct->vhca_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "inline_dump          : " UH_FMT "\n", ptr_struct->inline_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "more_dump            : " UH_FMT "\n", ptr_struct->more_dump);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vhca_id              : " UH_FMT "\n", ptr_struct->vhca_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_size            : " UH_FMT "\n", ptr_struct->data_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index1               : " U32H_FMT "\n", ptr_struct->index1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "index2               : " U32H_FMT "\n", ptr_struct->index2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_obj2          : " UH_FMT "\n", ptr_struct->num_of_obj2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_obj1          : " UH_FMT "\n", ptr_struct->num_of_obj1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_opaque        : " U64H_FMT "\n", ptr_struct->device_opaque);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkey                 : " U32H_FMT "\n", ptr_struct->mkey);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " U32H_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " U64H_FMT "\n", ptr_struct->address);
	int num_of_items_in_array = (int)ptr_struct->data_size;
	for (i = 0; i < num_of_items_in_array; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "inline_data_%03d     : " U32H_FMT "\n", i, ptr_struct->inline_data[i]);
	}
}

unsigned int reg_access_switch_mord_v2_ext_size(void)
{
	return REG_ACCESS_SWITCH_MORD_V2_EXT_SIZE;
}

void reg_access_switch_mord_v2_ext_dump(const struct reg_access_switch_mord_v2_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mord_v2_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mpein_reg_ext_pack(const struct reg_access_switch_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_enabled);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_enabled);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_width_active);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane0_physical_position);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_vfs);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_pfs);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->bdf0);
	offset = 223;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lane_reversal);
	offset = 222;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cmn_clk_mode);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 205;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pwr_status);
	offset = 196;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_payload_size);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_read_request_size);
	offset = 244;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->pci_power);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_peer_max_speed);
	offset = 287;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flit_sup);
	offset = 286;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->precode_sup);
	offset = 279;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->flit_active);
	offset = 278;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->precode_active);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_status);
}

void reg_access_switch_mpein_reg_ext_unpack(struct reg_access_switch_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 80;
	ptr_struct->link_speed_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->link_width_enabled = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 104;
	ptr_struct->link_width_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->lane0_physical_position = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->num_of_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->num_of_pfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->bdf0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 223;
	ptr_struct->lane_reversal = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 222;
	ptr_struct->cmn_clk_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 208;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 205;
	ptr_struct->pwr_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 196;
	ptr_struct->max_payload_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->max_read_request_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 244;
	ptr_struct->pci_power = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 224;
	ptr_struct->link_peer_max_speed = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 287;
	ptr_struct->flit_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 286;
	ptr_struct->precode_sup = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 279;
	ptr_struct->flit_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 278;
	ptr_struct->precode_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 288;
	ptr_struct->device_status = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_mpein_reg_ext_print(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mpein_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_enabled   : " UH_FMT "\n", ptr_struct->link_speed_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_enabled   : " UH_FMT "\n", ptr_struct->link_width_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : " UH_FMT "\n", ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_position : " UH_FMT "\n", ptr_struct->lane0_physical_position);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_vfs           : " UH_FMT "\n", ptr_struct->num_of_vfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_pfs           : " UH_FMT "\n", ptr_struct->num_of_pfs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bdf0                 : " UH_FMT "\n", ptr_struct->bdf0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_reversal        : " UH_FMT "\n", ptr_struct->lane_reversal);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cmn_clk_mode         : " UH_FMT "\n", ptr_struct->cmn_clk_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pwr_status           : " UH_FMT "\n", ptr_struct->pwr_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_payload_size     : " UH_FMT "\n", ptr_struct->max_payload_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_read_request_size : " UH_FMT "\n", ptr_struct->max_read_request_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pci_power            : " UH_FMT "\n", ptr_struct->pci_power);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_peer_max_speed  : " UH_FMT "\n", ptr_struct->link_peer_max_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flit_sup             : " UH_FMT "\n", ptr_struct->flit_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "precode_sup          : " UH_FMT "\n", ptr_struct->precode_sup);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "flit_active          : " UH_FMT "\n", ptr_struct->flit_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "precode_active       : " UH_FMT "\n", ptr_struct->precode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_status        : %s (" UH_FMT ")\n", (ptr_struct->device_status == 1 ? ("Correctable_error") : ((ptr_struct->device_status == 2 ? ("Non_Fatal_Error_detection") : ((ptr_struct->device_status == 4 ? ("Fatal_Error_detected") : ((ptr_struct->device_status == 8 ? ("Unsupported_request_detected") : ((ptr_struct->device_status == 16 ? ("AUX_power") : ((ptr_struct->device_status == 32 ? ("Transaction_Pending") : ("unknown")))))))))))), ptr_struct->device_status);
}

unsigned int reg_access_switch_mpein_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MPEIN_REG_EXT_SIZE;
}

void reg_access_switch_mpein_reg_ext_dump(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mpein_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mpir_ext_pack(const struct reg_access_switch_mpir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->host_buses);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->node);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pcie_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->depth);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->DPNv);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sdm);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->subordinate_bus);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->secondary_bus);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->segment_base);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->segment_valid);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->segment_cap);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->device);
	offset = 82;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bus);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 115;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->slot_number);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_con_devices);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->host_index);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->slot_cap);
}

void reg_access_switch_mpir_ext_unpack(struct reg_access_switch_mpir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->host_buses = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 16;
	ptr_struct->node = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->pcie_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->depth = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 1;
	ptr_struct->DPNv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->sdm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->subordinate_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->secondary_bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->segment_base = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 39;
	ptr_struct->segment_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 38;
	ptr_struct->segment_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 88;
	ptr_struct->device = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 82;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 72;
	ptr_struct->bus = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 115;
	ptr_struct->slot_number = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);
	offset = 104;
	ptr_struct->num_con_devices = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 97;
	ptr_struct->host_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 96;
	ptr_struct->slot_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_mpir_ext_print(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mpir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_buses           : " UH_FMT "\n", ptr_struct->host_buses);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "node                 : " UH_FMT "\n", ptr_struct->node);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcie_index           : " UH_FMT "\n", ptr_struct->pcie_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "depth                : " UH_FMT "\n", ptr_struct->depth);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "DPNv                 : %s (" UH_FMT ")\n", (ptr_struct->DPNv == 0 ? ("multi_topology_unaware_sw") : ((ptr_struct->DPNv == 1 ? ("multi_topology_aware_sw") : ("unknown")))), ptr_struct->DPNv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdm                  : " UH_FMT "\n", ptr_struct->sdm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "subordinate_bus      : " UH_FMT "\n", ptr_struct->subordinate_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary_bus        : " UH_FMT "\n", ptr_struct->secondary_bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_base         : " UH_FMT "\n", ptr_struct->segment_base);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_valid        : " UH_FMT "\n", ptr_struct->segment_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "segment_cap          : " UH_FMT "\n", ptr_struct->segment_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device               : " UH_FMT "\n", ptr_struct->device);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bus                  : " UH_FMT "\n", ptr_struct->bus);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_number          : " UH_FMT "\n", ptr_struct->slot_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_con_devices      : " UH_FMT "\n", ptr_struct->num_con_devices);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_index           : " UH_FMT "\n", ptr_struct->host_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_cap             : " UH_FMT "\n", ptr_struct->slot_cap);
}

unsigned int reg_access_switch_mpir_ext_size(void)
{
	return REG_ACCESS_SWITCH_MPIR_EXT_SIZE;
}

void reg_access_switch_mpir_ext_dump(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mpir_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mrsr_ext_pack(const struct reg_access_switch_mrsr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->command);
}

void reg_access_switch_mrsr_ext_unpack(struct reg_access_switch_mrsr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->command = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_mrsr_ext_print(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mrsr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "command              : " UH_FMT "\n", ptr_struct->command);
}

unsigned int reg_access_switch_mrsr_ext_size(void)
{
	return REG_ACCESS_SWITCH_MRSR_EXT_SIZE;
}

void reg_access_switch_mrsr_ext_dump(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mrsr_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_msgi_ext_pack(const struct reg_access_switch_msgi_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 6; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->serial_number[i]);
	}
	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->part_number[i]);
	}
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->revision);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 1024, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->product_name[i]);
	}
}

void reg_access_switch_msgi_ext_unpack(struct reg_access_switch_msgi_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 6; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1024, 1);
		ptr_struct->serial_number[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 5; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 1024, 1);
		ptr_struct->part_number[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 448;
	ptr_struct->revision = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(512, 32, i, 1024, 1);
		ptr_struct->product_name[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_msgi_ext_print(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_msgi_ext ========\n");

	for (i = 0; i < 6; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "serial_number_%03d   : " U32H_FMT "\n", i, ptr_struct->serial_number[i]);
	}
	for (i = 0; i < 5; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "part_number_%03d     : " U32H_FMT "\n", i, ptr_struct->part_number[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "revision             : " U32H_FMT "\n", ptr_struct->revision);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "product_name_%03d    : " U32H_FMT "\n", i, ptr_struct->product_name[i]);
	}
}

unsigned int reg_access_switch_msgi_ext_size(void)
{
	return REG_ACCESS_SWITCH_MSGI_EXT_SIZE;
}

void reg_access_switch_msgi_ext_dump(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_msgi_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mspmer_ext_pack(const struct reg_access_switch_mspmer_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_index);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clr);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->prev_en);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_physical_monitor);
	offset = 188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fmon_ctr);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vmon_ctr);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->scpm_ctr);
	offset = 179;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->general_err);
}

void reg_access_switch_mspmer_ext_unpack(struct reg_access_switch_mspmer_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->device_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 47;
	ptr_struct->clr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 39;
	ptr_struct->prev_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->supported_physical_monitor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 188;
	ptr_struct->fmon_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 184;
	ptr_struct->vmon_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 180;
	ptr_struct->scpm_ctr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 179;
	ptr_struct->general_err = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_mspmer_ext_print(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mspmer_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr                  : " UH_FMT "\n", ptr_struct->clr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prev_en              : " UH_FMT "\n", ptr_struct->prev_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "supported_physical_monitor : " U32H_FMT "\n", ptr_struct->supported_physical_monitor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fmon_ctr             : " UH_FMT "\n", ptr_struct->fmon_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vmon_ctr             : " UH_FMT "\n", ptr_struct->vmon_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "scpm_ctr             : " UH_FMT "\n", ptr_struct->scpm_ctr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "general_err          : " UH_FMT "\n", ptr_struct->general_err);
}

unsigned int reg_access_switch_mspmer_ext_size(void)
{
	return REG_ACCESS_SWITCH_MSPMER_EXT_SIZE;
}

void reg_access_switch_mspmer_ext_dump(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mspmer_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mtcq_reg_ext_pack(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->token_opcode);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->keypair_uuid[i]);
	}
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->base_mac);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(224, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 376;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_version_39_32);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_version_31_0);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->source_address[i]);
	}
	offset = 560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->session_id);
	offset = 544;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->challenge_version);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 896, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->challenge[i]);
	}
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->token_ratchet);
}

void reg_access_switch_mtcq_reg_ext_unpack(struct reg_access_switch_mtcq_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 8;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->token_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 896, 1);
		ptr_struct->keypair_uuid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 160;
	ptr_struct->base_mac = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(224, 32, i, 896, 1);
		ptr_struct->psid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 376;
	ptr_struct->fw_version_39_32 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 384;
	ptr_struct->fw_version_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 896, 1);
		ptr_struct->source_address[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 560;
	ptr_struct->session_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 544;
	ptr_struct->challenge_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(576, 32, i, 896, 1);
		ptr_struct->challenge[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 832;
	ptr_struct->token_ratchet = (u_int64_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_switch_mtcq_reg_ext_print(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mtcq_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "token_opcode         : " UH_FMT "\n", ptr_struct->token_opcode);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "keypair_uuid_%03d    : " U32H_FMT "\n", i, ptr_struct->keypair_uuid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_mac             : " U64H_FMT "\n", ptr_struct->base_mac);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "psid_%03d            : " U32H_FMT "\n", i, ptr_struct->psid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version_39_32     : " UH_FMT "\n", ptr_struct->fw_version_39_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_version_31_0      : " U32H_FMT "\n", ptr_struct->fw_version_31_0);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "source_address_%03d  : " U32H_FMT "\n", i, ptr_struct->source_address[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "session_id           : " UH_FMT "\n", ptr_struct->session_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "challenge_version    : " UH_FMT "\n", ptr_struct->challenge_version);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "challenge_%03d       : " U32H_FMT "\n", i, ptr_struct->challenge[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "token_ratchet        : " U64H_FMT "\n", ptr_struct->token_ratchet);
}

unsigned int reg_access_switch_mtcq_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MTCQ_REG_EXT_SIZE;
}

void reg_access_switch_mtcq_reg_ext_dump(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mtcq_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mtecr_ext_pack(const struct reg_access_switch_mtecr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_count);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->last_sensor);
	offset = 57;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->internal_sensor_count);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_map[i]);
	}
}

void reg_access_switch_mtecr_ext_unpack(struct reg_access_switch_mtecr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	ptr_struct->sensor_count = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 4;
	ptr_struct->last_sensor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 57;
	ptr_struct->internal_sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 32;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 768, 1);
		ptr_struct->sensor_map[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_mtecr_ext_print(const struct reg_access_switch_mtecr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mtecr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_count         : " UH_FMT "\n", ptr_struct->sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_sensor          : " UH_FMT "\n", ptr_struct->last_sensor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "internal_sensor_count : " UH_FMT "\n", ptr_struct->internal_sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	for (i = 0; i < 22; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sensor_map_%03d      : " U32H_FMT "\n", i, ptr_struct->sensor_map[i]);
	}
}

unsigned int reg_access_switch_mtecr_ext_size(void)
{
	return REG_ACCESS_SWITCH_MTECR_EXT_SIZE;
}

void reg_access_switch_mtecr_ext_dump(const struct reg_access_switch_mtecr_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mtecr_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_mtsh_reg_ext_pack(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->time_measure_unit);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_index);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->time_unit);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->thermal_state[i]);
	}
}

void reg_access_switch_mtsh_reg_ext_unpack(struct reg_access_switch_mtsh_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->time_measure_unit = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 4;
	ptr_struct->sensor_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 62;
	ptr_struct->time_unit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		ptr_struct->thermal_state[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_mtsh_reg_ext_print(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_mtsh_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_measure_unit    : " UH_FMT "\n", ptr_struct->time_measure_unit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_index         : " UH_FMT "\n", ptr_struct->sensor_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_unit            : " UH_FMT "\n", ptr_struct->time_unit);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "thermal_state_%03d   : " U32H_FMT "\n", i, ptr_struct->thermal_state[i]);
	}
}

unsigned int reg_access_switch_mtsh_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_MTSH_REG_EXT_SIZE;
}

void reg_access_switch_mtsh_reg_ext_dump(const struct reg_access_switch_mtsh_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_mtsh_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pddr_reg_ext_pack(const struct reg_access_switch_pddr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->module_ind_type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->page_select);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->module_info_ext);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x9:
		offset = 64;
		reg_access_switch_module_latched_flag_info_ext_pack(&(ptr_struct->page_data.module_latched_flag_info_ext), ptr_buff + offset / 8);
		break;
	case 0x10:
		offset = 64;
		reg_access_switch_pddr_apsu_info_page_ext_pack(&(ptr_struct->page_data.pddr_apsu_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0xe:
		offset = 64;
		reg_access_switch_pddr_cpo_module_page_ext_pack(&(ptr_struct->page_data.pddr_cpo_module_page_ext), ptr_buff + offset / 8);
		break;
	case 0x11:
		offset = 64;
		reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_pack(&(ptr_struct->page_data.pddr_fec_measure_ltx_nvl5_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_switch_pddr_link_down_info_page_ext_pack(&(ptr_struct->page_data.pddr_link_down_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0xf:
		offset = 64;
		reg_access_switch_pddr_link_health_page_ext_pack(&(ptr_struct->page_data.pddr_link_health_page_ext), ptr_buff + offset / 8);
		break;
	case 0xb:
		offset = 64;
		reg_access_switch_pddr_link_partner_info_ext_pack(&(ptr_struct->page_data.pddr_link_partner_info_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 64;
		reg_access_switch_pddr_link_up_info_page_ext_pack(&(ptr_struct->page_data.pddr_link_up_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_switch_pddr_module_info_ext_pack(&(ptr_struct->page_data.pddr_module_info_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_switch_pddr_operation_info_page_ext_pack(&(ptr_struct->page_data.pddr_operation_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_switch_pddr_phy_info_page_ext_pack(&(ptr_struct->page_data.pddr_phy_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_switch_pddr_troubleshooting_page_ext_pack(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_pddr_reg_ext_unpack(struct reg_access_switch_pddr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 6;
	ptr_struct->module_ind_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->page_select = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 33;
	ptr_struct->module_info_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x9:
		offset = 64;
		reg_access_switch_module_latched_flag_info_ext_unpack(&(ptr_struct->page_data.module_latched_flag_info_ext), ptr_buff + offset / 8);
		break;
	case 0x10:
		offset = 64;
		reg_access_switch_pddr_apsu_info_page_ext_unpack(&(ptr_struct->page_data.pddr_apsu_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0xe:
		offset = 64;
		reg_access_switch_pddr_cpo_module_page_ext_unpack(&(ptr_struct->page_data.pddr_cpo_module_page_ext), ptr_buff + offset / 8);
		break;
	case 0x11:
		offset = 64;
		reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_unpack(&(ptr_struct->page_data.pddr_fec_measure_ltx_nvl5_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_switch_pddr_link_down_info_page_ext_unpack(&(ptr_struct->page_data.pddr_link_down_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0xf:
		offset = 64;
		reg_access_switch_pddr_link_health_page_ext_unpack(&(ptr_struct->page_data.pddr_link_health_page_ext), ptr_buff + offset / 8);
		break;
	case 0xb:
		offset = 64;
		reg_access_switch_pddr_link_partner_info_ext_unpack(&(ptr_struct->page_data.pddr_link_partner_info_ext), ptr_buff + offset / 8);
		break;
	case 0x8:
		offset = 64;
		reg_access_switch_pddr_link_up_info_page_ext_unpack(&(ptr_struct->page_data.pddr_link_up_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_switch_pddr_module_info_ext_unpack(&(ptr_struct->page_data.pddr_module_info_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_switch_pddr_operation_info_page_ext_unpack(&(ptr_struct->page_data.pddr_operation_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_switch_pddr_phy_info_page_ext_unpack(&(ptr_struct->page_data.pddr_phy_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_switch_pddr_troubleshooting_page_ext_unpack(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_pddr_reg_ext_print(const struct reg_access_switch_pddr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pddr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_port") : ((ptr_struct->port_type == 1 ? ("Near_End_Port") : ((ptr_struct->port_type == 2 ? ("Internal_IC_LR_Port") : ((ptr_struct->port_type == 3 ? ("Far_End_Port") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : %s (" UH_FMT ")\n", (ptr_struct->pnat == 0 ? ("Local_port_number") : ((ptr_struct->pnat == 1 ? ("IB_port_number") : ((ptr_struct->pnat == 3 ? ("Out_of_band_or_PCI") : ("unknown")))))), ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_ind_type      : %s (" UH_FMT ")\n", (ptr_struct->module_ind_type == 0 ? ("CPO_or_pluggable_modules") : ((ptr_struct->module_ind_type == 1 ? ("OE") : ((ptr_struct->module_ind_type == 2 ? ("ELS") : ("unknown")))))), ptr_struct->module_ind_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_select          : %s (" UH_FMT ")\n", (ptr_struct->page_select == 0 ? ("Operational_info_page") : ((ptr_struct->page_select == 1 ? ("Troubleshooting_info_page") : ((ptr_struct->page_select == 2 ? ("Phy_info_page") : ((ptr_struct->page_select == 3 ? ("Module_info_page") : ((ptr_struct->page_select == 6 ? ("link_down_info") : ((ptr_struct->page_select == 8 ? ("Link_up_info") : ((ptr_struct->page_select == 9 ? ("Module_latched_flag_info_page") : ((ptr_struct->page_select == 11 ? ("link_partner_info_page") : ((ptr_struct->page_select == 14 ? ("cpo_module_info_page") : ((ptr_struct->page_select == 15 ? ("link_health_fec_measure_info_page") : ((ptr_struct->page_select == 16 ? ("APSU_info_page") : ((ptr_struct->page_select == 17 ? ("link_health_fec_measure_nvl5_page") : ("unknown")))))))))))))))))))))))), ptr_struct->page_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_info_ext      : %s (" UH_FMT ")\n", (ptr_struct->module_info_ext == 0 ? ("dbm") : ((ptr_struct->module_info_ext == 1 ? ("uW") : ("unknown")))), ptr_struct->module_info_ext);
	switch (ptr_struct->page_select) {
	case 0x9:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "module_latched_flag_info_ext:\n");
		reg_access_switch_module_latched_flag_info_ext_print(&(ptr_struct->page_data.module_latched_flag_info_ext), fd, indent_level + 1);
		break;
	case 0x10:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_apsu_info_page_ext:\n");
		reg_access_switch_pddr_apsu_info_page_ext_print(&(ptr_struct->page_data.pddr_apsu_info_page_ext), fd, indent_level + 1);
		break;
	case 0xe:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_cpo_module_page_ext:\n");
		reg_access_switch_pddr_cpo_module_page_ext_print(&(ptr_struct->page_data.pddr_cpo_module_page_ext), fd, indent_level + 1);
		break;
	case 0x11:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_fec_measure_ltx_nvl5_ext:\n");
		reg_access_switch_pddr_fec_measure_ltx_nvl5_ext_print(&(ptr_struct->page_data.pddr_fec_measure_ltx_nvl5_ext), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_down_info_page_ext:\n");
		reg_access_switch_pddr_link_down_info_page_ext_print(&(ptr_struct->page_data.pddr_link_down_info_page_ext), fd, indent_level + 1);
		break;
	case 0xf:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_health_page_ext:\n");
		reg_access_switch_pddr_link_health_page_ext_print(&(ptr_struct->page_data.pddr_link_health_page_ext), fd, indent_level + 1);
		break;
	case 0xb:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_partner_info_ext:\n");
		reg_access_switch_pddr_link_partner_info_ext_print(&(ptr_struct->page_data.pddr_link_partner_info_ext), fd, indent_level + 1);
		break;
	case 0x8:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_up_info_page_ext:\n");
		reg_access_switch_pddr_link_up_info_page_ext_print(&(ptr_struct->page_data.pddr_link_up_info_page_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_module_info_ext:\n");
		reg_access_switch_pddr_module_info_ext_print(&(ptr_struct->page_data.pddr_module_info_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_operation_info_page_ext:\n");
		reg_access_switch_pddr_operation_info_page_ext_print(&(ptr_struct->page_data.pddr_operation_info_page_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_phy_info_page_ext:\n");
		reg_access_switch_pddr_phy_info_page_ext_print(&(ptr_struct->page_data.pddr_phy_info_page_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_troubleshooting_page_ext:\n");
		reg_access_switch_pddr_troubleshooting_page_ext_print(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_pddr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PDDR_REG_EXT_SIZE;
}

void reg_access_switch_pddr_reg_ext_dump(const struct reg_access_switch_pddr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pddr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pguid_reg_ext_pack(const struct reg_access_switch_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sys_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->node_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 768, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->allocated_guid[i]);
	}
}

void reg_access_switch_pguid_reg_ext_unpack(struct reg_access_switch_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 768, 1);
		ptr_struct->sys_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(160, 32, i, 768, 1);
		ptr_struct->node_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 768, 1);
		ptr_struct->port_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(416, 32, i, 768, 1);
		ptr_struct->allocated_guid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_switch_pguid_reg_ext_print(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pguid_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sys_guid_%03d        : " U32H_FMT "\n", i, ptr_struct->sys_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "node_guid_%03d       : " U32H_FMT "\n", i, ptr_struct->node_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "port_guid_%03d       : " U32H_FMT "\n", i, ptr_struct->port_guid[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "allocated_guid_%03d  : " U32H_FMT "\n", i, ptr_struct->allocated_guid[i]);
	}
}

unsigned int reg_access_switch_pguid_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PGUID_REG_EXT_SIZE;
}

void reg_access_switch_pguid_reg_ext_dump(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pguid_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_plib_reg_ext_pack(const struct reg_access_switch_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->ib_port);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_num);
}

void reg_access_switch_plib_reg_ext_unpack(struct reg_access_switch_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->ib_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->split_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_switch_plib_reg_ext_print(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_plib_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_port              : " UH_FMT "\n", ptr_struct->ib_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_num            : " UH_FMT "\n", ptr_struct->split_num);
}

unsigned int reg_access_switch_plib_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PLIB_REG_EXT_SIZE;
}

void reg_access_switch_plib_reg_ext_dump(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_plib_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pllp_reg_ext_pack(const struct reg_access_switch_pllp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->label_port);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_info);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_num);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ipil_num);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->split_stat);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ipil_stat);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_num);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_index);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_index_msb);
	offset = 125;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->conn_type);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cartridge_id_valid);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cartridge_id);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->rmt_id);
	offset = 111;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_fnm);
	offset = 110;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->maf);
	offset = 109;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->module_valid);
	offset = 108;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->els_valid);
	offset = 105;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->cartridge_lane_index);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_msb);
	offset = 157;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->protocol);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->resource_label_port);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oe_identifier);
}

void reg_access_switch_pllp_reg_ext_unpack(struct reg_access_switch_pllp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->label_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->split_info = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->split_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->ipil_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 44;
	ptr_struct->split_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->ipil_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->slot_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->els_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->els_index_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 125;
	ptr_struct->conn_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 124;
	ptr_struct->cartridge_id_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 120;
	ptr_struct->cartridge_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 112;
	ptr_struct->rmt_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 111;
	ptr_struct->is_fnm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 110;
	ptr_struct->maf = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 109;
	ptr_struct->module_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 108;
	ptr_struct->els_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 105;
	ptr_struct->cartridge_lane_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 96;
	ptr_struct->module_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 157;
	ptr_struct->protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 136;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 176;
	ptr_struct->resource_label_port = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->oe_identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pllp_reg_ext_print(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pllp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "label_port           : " UH_FMT "\n", ptr_struct->label_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_info           : " UH_FMT "\n", ptr_struct->split_info);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_num            : " UH_FMT "\n", ptr_struct->split_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipil_num             : " UH_FMT "\n", ptr_struct->ipil_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_stat           : " UH_FMT "\n", ptr_struct->split_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ipil_stat            : " UH_FMT "\n", ptr_struct->ipil_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_num             : " UH_FMT "\n", ptr_struct->slot_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_index            : " UH_FMT "\n", ptr_struct->els_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_index_msb        : " UH_FMT "\n", ptr_struct->els_index_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "conn_type            : " UH_FMT "\n", ptr_struct->conn_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cartridge_id_valid   : " UH_FMT "\n", ptr_struct->cartridge_id_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cartridge_id         : " UH_FMT "\n", ptr_struct->cartridge_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rmt_id               : " UH_FMT "\n", ptr_struct->rmt_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_fnm               : " UH_FMT "\n", ptr_struct->is_fnm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "maf                  : " UH_FMT "\n", ptr_struct->maf);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_valid         : " UH_FMT "\n", ptr_struct->module_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_valid            : " UH_FMT "\n", ptr_struct->els_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cartridge_lane_index : " UH_FMT "\n", ptr_struct->cartridge_lane_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_msb           : " UH_FMT "\n", ptr_struct->module_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "protocol             : " UH_FMT "\n", ptr_struct->protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_label_port  : " UH_FMT "\n", ptr_struct->resource_label_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_identifier        : " UH_FMT "\n", ptr_struct->oe_identifier);
}

unsigned int reg_access_switch_pllp_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PLLP_REG_EXT_SIZE;
}

void reg_access_switch_pllp_reg_ext_dump(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pllp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmaos_reg_ext_pack(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->serbi_failure);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rst);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->e);
	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ref_module_valid);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->error_type);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->operational_notification);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_msb);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rev_incompatible);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secondary);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ref_module);
}

void reg_access_switch_pmaos_reg_ext_unpack(struct reg_access_switch_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 27;
	ptr_struct->serbi_failure = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->rst = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 61;
	ptr_struct->ref_module_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 51;
	ptr_struct->error_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 44;
	ptr_struct->operational_notification = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->module_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 35;
	ptr_struct->rev_incompatible = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->secondary = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 80;
	ptr_struct->ref_module = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_switch_pmaos_reg_ext_print(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmaos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 0 ? ("initializing") : ((ptr_struct->oper_status == 1 ? ("plugged_enabled") : ((ptr_struct->oper_status == 2 ? ("unplugged") : ((ptr_struct->oper_status == 3 ? ("module_plugged_with_error") : ((ptr_struct->oper_status == 5 ? ("unknown") : ("unknown")))))))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "serbi_failure        : " UH_FMT "\n", ptr_struct->serbi_failure);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("enabled") : ((ptr_struct->admin_status == 2 ? ("disabled_by_configuration") : ((ptr_struct->admin_status == 3 ? ("enabled_once") : ((ptr_struct->admin_status == 14 ? ("disconnect_cable") : ("unknown")))))))), ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst                  : " UH_FMT "\n", ptr_struct->rst);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : %s (" UH_FMT ")\n", (ptr_struct->e == 0 ? ("Do_not_generate_event") : ((ptr_struct->e == 1 ? ("Generate_Event") : ((ptr_struct->e == 2 ? ("Generate_Single_Event") : ("unknown")))))), ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ref_module_valid     : " UH_FMT "\n", ptr_struct->ref_module_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type           : %s (" UH_FMT ")\n", (ptr_struct->error_type == 0 ? ("Power_Budget_Exceeded") : ((ptr_struct->error_type == 1 ? ("Long_Range_for_non_MLNX_cable_or_module") : ((ptr_struct->error_type == 2 ? ("Bus_stuck") : ((ptr_struct->error_type == 3 ? ("bad_or_unsupported_EEPROM") : ((ptr_struct->error_type == 4 ? ("Enforce_part_number_list") : ((ptr_struct->error_type == 5 ? ("unsupported_cable") : ((ptr_struct->error_type == 6 ? ("High_Temperature") : ((ptr_struct->error_type == 7 ? ("bad_cable") : ((ptr_struct->error_type == 8 ? ("PMD_type_is_not_enabled") : ((ptr_struct->error_type == 12 ? ("pcie_system_power_slot_Exceeded") : ("unknown")))))))))))))))))))), ptr_struct->error_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operational_notification : " UH_FMT "\n", ptr_struct->operational_notification);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_msb           : " UH_FMT "\n", ptr_struct->module_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rev_incompatible     : " UH_FMT "\n", ptr_struct->rev_incompatible);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary            : " UH_FMT "\n", ptr_struct->secondary);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ref_module           : " UH_FMT "\n", ptr_struct->ref_module);
}

unsigned int reg_access_switch_pmaos_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMAOS_REG_EXT_SIZE;
}

void reg_access_switch_pmaos_reg_ext_dump(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmdr_reg_ext_pack(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->width_valid);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mcm_tile_valid);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->gb_valid);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pport_msb);
	offset = 49;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->cluster);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pport);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_port);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_lane_mask);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 69;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->split);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->gb_dp_num);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_query_msb);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lbp_query_msb);
	offset = 122;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tile_pport_msb);
	offset = 118;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_width);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port_query);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->label_port_query);
	offset = 153;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->gearbox_die_num);
	offset = 147;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->tile_pport);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pll_cnt_rx);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mcm_tile_num);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tile_cluster);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 189;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane0_physical_rx);
	offset = 186;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane1_physical_rx);
	offset = 183;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane2_physical_rx);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane3_physical_rx);
	offset = 177;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane4_physical_rx);
	offset = 174;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane5_physical_rx);
	offset = 171;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane6_physical_rx);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane7_physical_rx);
	offset = 165;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->pll_cnt_tx);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->vl_num);
	offset = 221;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane0_physical_tx);
	offset = 218;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane1_physical_tx);
	offset = 215;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane2_physical_tx);
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane3_physical_tx);
	offset = 209;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane4_physical_tx);
	offset = 206;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane5_physical_tx);
	offset = 203;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane6_physical_tx);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->lane7_physical_tx);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pll_index);
	offset = 252;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL0_lane_map);
	offset = 248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL1_lane_map);
	offset = 244;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL2_lane_map);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL3_lane_map);
	offset = 236;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL4_lane_map);
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL5_lane_map);
	offset = 228;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL6_lane_map);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL7_lane_map);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL8_lane_map);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL9_lane_map);
	offset = 276;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL10_lane_map);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL11_lane_map);
	offset = 268;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL12_lane_map);
	offset = 264;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL13_lane_map);
	offset = 260;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL14_lane_map);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL15_lane_map);
	offset = 316;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL16_lane_map);
	offset = 312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL17_lane_map);
	offset = 308;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL18_lane_map);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL19_lane_map);
	offset = 300;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL20_lane_map);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL21_lane_map);
	offset = 292;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL22_lane_map);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL23_lane_map);
	offset = 348;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL24_lane_map);
	offset = 344;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL25_lane_map);
	offset = 340;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL26_lane_map);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL27_lane_map);
	offset = 332;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL28_lane_map);
	offset = 328;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL29_lane_map);
	offset = 324;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL30_lane_map);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->VL31_lane_map);
	offset = 508;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lp_query_msb_ext);
	offset = 504;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pport_msb_ext);
	offset = 488;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fiber_connector_index);
	offset = 480;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sub_module);
	offset = 540;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane7_to_els_logical_laser);
	offset = 536;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane6_to_els_logical_laser);
	offset = 532;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane5_to_els_logical_laser);
	offset = 528;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane4_to_els_logical_laser);
	offset = 524;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane3_to_els_logical_laser);
	offset = 520;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane2_to_els_logical_laser);
	offset = 516;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane1_to_els_logical_laser);
	offset = 512;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oe_lane0_to_els_logical_laser);
	offset = 568;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->els_module_index);
	offset = 566;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cpo_module_indication);
	offset = 560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->els_index);
	offset = 552;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->active_module_lane_mask);
	offset = 545;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->oe_mcu_index);
	offset = 544;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cpo_indication);
}

void reg_access_switch_pmdr_reg_ext_unpack(struct reg_access_switch_pmdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 21;
	ptr_struct->width_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 19;
	ptr_struct->mcm_tile_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->gb_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->pport_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 49;
	ptr_struct->cluster = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 40;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->pport = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->ib_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->module_lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 69;
	ptr_struct->split = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 64;
	ptr_struct->gb_dp_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 126;
	ptr_struct->lp_query_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 124;
	ptr_struct->lbp_query_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 122;
	ptr_struct->tile_pport_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 118;
	ptr_struct->port_width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 104;
	ptr_struct->local_port_query = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->label_port_query = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 153;
	ptr_struct->gearbox_die_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 147;
	ptr_struct->tile_pport = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 144;
	ptr_struct->pll_cnt_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 136;
	ptr_struct->mcm_tile_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 132;
	ptr_struct->tile_cluster = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 189;
	ptr_struct->lane0_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 186;
	ptr_struct->lane1_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 183;
	ptr_struct->lane2_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 180;
	ptr_struct->lane3_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 177;
	ptr_struct->lane4_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 174;
	ptr_struct->lane5_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 171;
	ptr_struct->lane6_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 168;
	ptr_struct->lane7_physical_rx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 165;
	ptr_struct->pll_cnt_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 160;
	ptr_struct->vl_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 221;
	ptr_struct->lane0_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 218;
	ptr_struct->lane1_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 215;
	ptr_struct->lane2_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 212;
	ptr_struct->lane3_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 209;
	ptr_struct->lane4_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 206;
	ptr_struct->lane5_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 203;
	ptr_struct->lane6_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 200;
	ptr_struct->lane7_physical_tx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 192;
	ptr_struct->pll_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 252;
	ptr_struct->VL0_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 248;
	ptr_struct->VL1_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 244;
	ptr_struct->VL2_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 240;
	ptr_struct->VL3_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 236;
	ptr_struct->VL4_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 232;
	ptr_struct->VL5_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 228;
	ptr_struct->VL6_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->VL7_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 284;
	ptr_struct->VL8_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->VL9_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 276;
	ptr_struct->VL10_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 272;
	ptr_struct->VL11_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 268;
	ptr_struct->VL12_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 264;
	ptr_struct->VL13_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 260;
	ptr_struct->VL14_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->VL15_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 316;
	ptr_struct->VL16_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 312;
	ptr_struct->VL17_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 308;
	ptr_struct->VL18_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 304;
	ptr_struct->VL19_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 300;
	ptr_struct->VL20_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 296;
	ptr_struct->VL21_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 292;
	ptr_struct->VL22_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->VL23_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 348;
	ptr_struct->VL24_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 344;
	ptr_struct->VL25_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 340;
	ptr_struct->VL26_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 336;
	ptr_struct->VL27_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 332;
	ptr_struct->VL28_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 328;
	ptr_struct->VL29_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 324;
	ptr_struct->VL30_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->VL31_lane_map = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 508;
	ptr_struct->lp_query_msb_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 504;
	ptr_struct->pport_msb_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 488;
	ptr_struct->fiber_connector_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 480;
	ptr_struct->sub_module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 540;
	ptr_struct->oe_lane7_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 536;
	ptr_struct->oe_lane6_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 532;
	ptr_struct->oe_lane5_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 528;
	ptr_struct->oe_lane4_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 524;
	ptr_struct->oe_lane3_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 520;
	ptr_struct->oe_lane2_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 516;
	ptr_struct->oe_lane1_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->oe_lane0_to_els_logical_laser = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 568;
	ptr_struct->els_module_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 566;
	ptr_struct->cpo_module_indication = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 560;
	ptr_struct->els_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 552;
	ptr_struct->active_module_lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 545;
	ptr_struct->oe_mcu_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 544;
	ptr_struct->cpo_indication = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_switch_pmdr_reg_ext_print(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmdr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "width_valid          : " UH_FMT "\n", ptr_struct->width_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcm_tile_valid       : " UH_FMT "\n", ptr_struct->mcm_tile_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gb_valid             : " UH_FMT "\n", ptr_struct->gb_valid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : " UH_FMT "\n", ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pport_msb            : " UH_FMT "\n", ptr_struct->pport_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cluster              : " UH_FMT "\n", ptr_struct->cluster);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pport                : " UH_FMT "\n", ptr_struct->pport);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_port              : " UH_FMT "\n", ptr_struct->ib_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_lane_mask     : " UH_FMT "\n", ptr_struct->module_lane_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split                : " UH_FMT "\n", ptr_struct->split);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gb_dp_num            : " UH_FMT "\n", ptr_struct->gb_dp_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_query_msb         : " UH_FMT "\n", ptr_struct->lp_query_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lbp_query_msb        : " UH_FMT "\n", ptr_struct->lbp_query_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_pport_msb       : " UH_FMT "\n", ptr_struct->tile_pport_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_width           : " UH_FMT "\n", ptr_struct->port_width);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port_query     : " UH_FMT "\n", ptr_struct->local_port_query);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "label_port_query     : " UH_FMT "\n", ptr_struct->label_port_query);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gearbox_die_num      : " UH_FMT "\n", ptr_struct->gearbox_die_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_pport           : " UH_FMT "\n", ptr_struct->tile_pport);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_cnt_rx           : " UH_FMT "\n", ptr_struct->pll_cnt_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcm_tile_num         : " UH_FMT "\n", ptr_struct->mcm_tile_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tile_cluster         : " UH_FMT "\n", ptr_struct->tile_cluster);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_rx    : " UH_FMT "\n", ptr_struct->lane0_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane1_physical_rx    : " UH_FMT "\n", ptr_struct->lane1_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane2_physical_rx    : " UH_FMT "\n", ptr_struct->lane2_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane3_physical_rx    : " UH_FMT "\n", ptr_struct->lane3_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane4_physical_rx    : " UH_FMT "\n", ptr_struct->lane4_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane5_physical_rx    : " UH_FMT "\n", ptr_struct->lane5_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane6_physical_rx    : " UH_FMT "\n", ptr_struct->lane6_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane7_physical_rx    : " UH_FMT "\n", ptr_struct->lane7_physical_rx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_cnt_tx           : " UH_FMT "\n", ptr_struct->pll_cnt_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_num               : " UH_FMT "\n", ptr_struct->vl_num);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane0_physical_tx    : " UH_FMT "\n", ptr_struct->lane0_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane1_physical_tx    : " UH_FMT "\n", ptr_struct->lane1_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane2_physical_tx    : " UH_FMT "\n", ptr_struct->lane2_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane3_physical_tx    : " UH_FMT "\n", ptr_struct->lane3_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane4_physical_tx    : " UH_FMT "\n", ptr_struct->lane4_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane5_physical_tx    : " UH_FMT "\n", ptr_struct->lane5_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane6_physical_tx    : " UH_FMT "\n", ptr_struct->lane6_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane7_physical_tx    : " UH_FMT "\n", ptr_struct->lane7_physical_tx);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pll_index            : " UH_FMT "\n", ptr_struct->pll_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL0_lane_map         : " UH_FMT "\n", ptr_struct->VL0_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL1_lane_map         : " UH_FMT "\n", ptr_struct->VL1_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL2_lane_map         : " UH_FMT "\n", ptr_struct->VL2_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL3_lane_map         : " UH_FMT "\n", ptr_struct->VL3_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL4_lane_map         : " UH_FMT "\n", ptr_struct->VL4_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL5_lane_map         : " UH_FMT "\n", ptr_struct->VL5_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL6_lane_map         : " UH_FMT "\n", ptr_struct->VL6_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL7_lane_map         : " UH_FMT "\n", ptr_struct->VL7_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL8_lane_map         : " UH_FMT "\n", ptr_struct->VL8_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL9_lane_map         : " UH_FMT "\n", ptr_struct->VL9_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL10_lane_map        : " UH_FMT "\n", ptr_struct->VL10_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL11_lane_map        : " UH_FMT "\n", ptr_struct->VL11_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL12_lane_map        : " UH_FMT "\n", ptr_struct->VL12_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL13_lane_map        : " UH_FMT "\n", ptr_struct->VL13_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL14_lane_map        : " UH_FMT "\n", ptr_struct->VL14_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL15_lane_map        : " UH_FMT "\n", ptr_struct->VL15_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL16_lane_map        : " UH_FMT "\n", ptr_struct->VL16_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL17_lane_map        : " UH_FMT "\n", ptr_struct->VL17_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL18_lane_map        : " UH_FMT "\n", ptr_struct->VL18_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL19_lane_map        : " UH_FMT "\n", ptr_struct->VL19_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL20_lane_map        : " UH_FMT "\n", ptr_struct->VL20_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL21_lane_map        : " UH_FMT "\n", ptr_struct->VL21_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL22_lane_map        : " UH_FMT "\n", ptr_struct->VL22_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL23_lane_map        : " UH_FMT "\n", ptr_struct->VL23_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL24_lane_map        : " UH_FMT "\n", ptr_struct->VL24_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL25_lane_map        : " UH_FMT "\n", ptr_struct->VL25_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL26_lane_map        : " UH_FMT "\n", ptr_struct->VL26_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL27_lane_map        : " UH_FMT "\n", ptr_struct->VL27_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL28_lane_map        : " UH_FMT "\n", ptr_struct->VL28_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL29_lane_map        : " UH_FMT "\n", ptr_struct->VL29_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL30_lane_map        : " UH_FMT "\n", ptr_struct->VL30_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "VL31_lane_map        : " UH_FMT "\n", ptr_struct->VL31_lane_map);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_query_msb_ext     : " UH_FMT "\n", ptr_struct->lp_query_msb_ext);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pport_msb_ext        : " UH_FMT "\n", ptr_struct->pport_msb_ext);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fiber_connector_index : " UH_FMT "\n", ptr_struct->fiber_connector_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_module           : " UH_FMT "\n", ptr_struct->sub_module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane7_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane7_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane6_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane6_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane5_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane5_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane4_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane4_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane3_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane3_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane2_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane2_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane1_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane1_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_lane0_to_els_logical_laser : " UH_FMT "\n", ptr_struct->oe_lane0_to_els_logical_laser);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_module_index     : " UH_FMT "\n", ptr_struct->els_module_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cpo_module_indication : %s (" UH_FMT ")\n", (ptr_struct->cpo_module_indication == 0 ? ("no_vmod_indication") : ((ptr_struct->cpo_module_indication == 1 ? ("vmod_indication") : ("unknown")))), ptr_struct->cpo_module_indication);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "els_index            : " UH_FMT "\n", ptr_struct->els_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active_module_lane_mask : " UH_FMT "\n", ptr_struct->active_module_lane_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oe_mcu_index         : " UH_FMT "\n", ptr_struct->oe_mcu_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cpo_indication       : " UH_FMT "\n", ptr_struct->cpo_indication);
}

unsigned int reg_access_switch_pmdr_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMDR_REG_EXT_SIZE;
}

void reg_access_switch_pmdr_reg_ext_dump(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmdr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_pmlp_reg_ext_pack(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->width);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->m_lane_m);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rxtx);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_switch_lane_2_module_mapping_ext_pack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pmlp_reg_ext_unpack(struct reg_access_switch_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 3;
	ptr_struct->m_lane_m = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->rxtx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 512, 1);
		reg_access_switch_lane_2_module_mapping_ext_unpack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_switch_pmlp_reg_ext_print(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_pmlp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "width                : %s (" UH_FMT ")\n", (ptr_struct->width == 0 ? ("unmap_local_port") : ((ptr_struct->width == 1 ? ("x1") : ((ptr_struct->width == 2 ? ("x2") : ((ptr_struct->width == 4 ? ("x4") : ((ptr_struct->width == 8 ? ("x8") : ("unknown")))))))))), ptr_struct->width);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "m_lane_m             : " UH_FMT "\n", ptr_struct->m_lane_m);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rxtx                 : " UH_FMT "\n", ptr_struct->rxtx);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "lane_module_mapping_%03d:\n", i);
		reg_access_switch_lane_2_module_mapping_ext_print(&(ptr_struct->lane_module_mapping[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_switch_pmlp_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PMLP_REG_EXT_SIZE;
}

void reg_access_switch_pmlp_reg_ext_dump(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_pmlp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_ppcl_reg_ext_pack(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->generation);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 58;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->page_select);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->link_down_snapshot_sel);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x1:
		offset = 64;
		reg_access_switch_ppcl_cause_configurations_ext_pack(&(ptr_struct->page_data.ppcl_cause_configurations_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_pack(&(ptr_struct->page_data.ppcl_cause_list_for_nvlink_phy_gen6_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_ppcl_reg_ext_unpack(struct reg_access_switch_ppcl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->generation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 58;
	ptr_struct->page_select = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 33;
	ptr_struct->link_down_snapshot_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x1:
		offset = 64;
		reg_access_switch_ppcl_cause_configurations_ext_unpack(&(ptr_struct->page_data.ppcl_cause_configurations_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_unpack(&(ptr_struct->page_data.ppcl_cause_list_for_nvlink_phy_gen6_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_switch_ppcl_reg_ext_print(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_ppcl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "generation           : %s (" UH_FMT ")\n", (ptr_struct->generation == 0 ? ("nvlink_phy_gen6") : ("unknown")), ptr_struct->generation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_select          : %s (" UH_FMT ")\n", (ptr_struct->page_select == 0 ? ("cause_list") : ((ptr_struct->page_select == 1 ? ("cause_configuration") : ("unknown")))), ptr_struct->page_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_down_snapshot_sel : " UH_FMT "\n", ptr_struct->link_down_snapshot_sel);
	switch (ptr_struct->page_select) {
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcl_cause_configurations_ext:\n");
		reg_access_switch_ppcl_cause_configurations_ext_print(&(ptr_struct->page_data.ppcl_cause_configurations_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcl_cause_list_for_nvlink_phy_gen6_ext:\n");
		reg_access_switch_ppcl_cause_list_for_nvlink_phy_gen6_ext_print(&(ptr_struct->page_data.ppcl_cause_list_for_nvlink_phy_gen6_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_switch_ppcl_reg_ext_size(void)
{
	return REG_ACCESS_SWITCH_PPCL_REG_EXT_SIZE;
}

void reg_access_switch_ppcl_reg_ext_dump(const struct reg_access_switch_ppcl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_switch_ppcl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_switch_reg_access_switch_Nodes_pack(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_switch_icsr_ext_pack(&(ptr_struct->icsr_ext), ptr_buff);
}

void reg_access_switch_reg_access_switch_Nodes_unpack(union reg_access_switch_reg_access_switch_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_switch_icsr_ext_unpack(&(ptr_struct->icsr_ext), ptr_buff);
}

void reg_access_switch_reg_access_switch_Nodes_print(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_switch_reg_access_switch_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MMAM_ext:\n");
	reg_access_switch_MMAM_ext_print(&(ptr_struct->MMAM_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_ext:\n");
	reg_access_switch_MRFV_ext_print(&(ptr_struct->MRFV_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "PPCR_ext:\n");
	reg_access_switch_PPCR_ext_print(&(ptr_struct->PPCR_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icam_reg_ext:\n");
	reg_access_switch_icam_reg_ext_print(&(ptr_struct->icam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "icsr_ext:\n");
	reg_access_switch_icsr_ext_print(&(ptr_struct->icsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcce_reg_ext:\n");
	reg_access_switch_mcce_reg_ext_print(&(ptr_struct->mcce_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddq_ext:\n");
	reg_access_switch_mddq_ext_print(&(ptr_struct->mddq_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mddt_reg_ext:\n");
	reg_access_switch_mddt_reg_ext_print(&(ptr_struct->mddt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdsr_reg_ext:\n");
	reg_access_switch_mdsr_reg_ext_print(&(ptr_struct->mdsr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfcdr_reg_ext:\n");
	reg_access_switch_mfcdr_reg_ext_print(&(ptr_struct->mfcdr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfkv_reg_ext:\n");
	reg_access_switch_mfkv_reg_ext_print(&(ptr_struct->mfkv_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mfmc_reg_ext:\n");
	reg_access_switch_mfmc_reg_ext_print(&(ptr_struct->mfmc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgpir_ext:\n");
	reg_access_switch_mgpir_ext_print(&(ptr_struct->mgpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mkdc_reg_ext:\n");
	reg_access_switch_mkdc_reg_ext_print(&(ptr_struct->mkdc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmta_reg_ext:\n");
	reg_access_switch_mmta_reg_ext_print(&(ptr_struct->mmta_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mord_v2_ext:\n");
	reg_access_switch_mord_v2_ext_print(&(ptr_struct->mord_v2_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpein_reg_ext:\n");
	reg_access_switch_mpein_reg_ext_print(&(ptr_struct->mpein_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpir_ext:\n");
	reg_access_switch_mpir_ext_print(&(ptr_struct->mpir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mrsr_ext:\n");
	reg_access_switch_mrsr_ext_print(&(ptr_struct->mrsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "msgi_ext:\n");
	reg_access_switch_msgi_ext_print(&(ptr_struct->msgi_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mspmer_ext:\n");
	reg_access_switch_mspmer_ext_print(&(ptr_struct->mspmer_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcq_reg_ext:\n");
	reg_access_switch_mtcq_reg_ext_print(&(ptr_struct->mtcq_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtecr_ext:\n");
	reg_access_switch_mtecr_ext_print(&(ptr_struct->mtecr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtsh_reg_ext:\n");
	reg_access_switch_mtsh_reg_ext_print(&(ptr_struct->mtsh_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_reg_ext:\n");
	reg_access_switch_pddr_reg_ext_print(&(ptr_struct->pddr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pguid_reg_ext:\n");
	reg_access_switch_pguid_reg_ext_print(&(ptr_struct->pguid_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plib_reg_ext:\n");
	reg_access_switch_plib_reg_ext_print(&(ptr_struct->plib_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pllp_reg_ext:\n");
	reg_access_switch_pllp_reg_ext_print(&(ptr_struct->pllp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_switch_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmdr_reg_ext:\n");
	reg_access_switch_pmdr_reg_ext_print(&(ptr_struct->pmdr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_switch_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcl_reg_ext:\n");
	reg_access_switch_ppcl_reg_ext_print(&(ptr_struct->ppcl_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_switch_reg_access_switch_Nodes_size(void)
{
	return REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE;
}

void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd)
{
	reg_access_switch_reg_access_switch_Nodes_print(ptr_struct, fd, 0);
}

