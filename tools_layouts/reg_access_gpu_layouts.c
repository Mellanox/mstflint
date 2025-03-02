
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
         *** This file was generated at "2024-12-09 08:55:25"
         *** by:
         ***    > /auto/mswg/release/tools/a-me/a-me-1.2.7/a-me-1.2.7-44/adabe_plugins/adb2c/adb2pack.py --input /images/redesign/mft/user/tools_layouts/adb/prm/gpu/ext/reg_access_gpu.adb --file-prefix reg_access_gpu --prefix reg_access_gpu_ --no-adb-utils -o /images/redesign/mft/user/tools_layouts
         ***/
#include "reg_access_gpu_layouts.h"

void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_pack(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->core_to_phy_link_eth_enabled);
}

void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_unpack(struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->core_to_phy_link_eth_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_print(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_c2p_link_enabed_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_eth_enabled : " U32H_FMT "\n", ptr_struct->core_to_phy_link_eth_enabled);
}

unsigned int reg_access_gpu_pddr_c2p_link_enabed_eth_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_C2P_LINK_ENABED_ETH_EXT_SIZE;
}

void reg_access_gpu_pddr_c2p_link_enabed_eth_ext_dump(const struct reg_access_gpu_pddr_c2p_link_enabed_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_c2p_link_enabed_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_pack(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->core_to_phy_link_proto_enabled);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->core_to_phy_link_width_enabled);
}

void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_unpack(struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->core_to_phy_link_proto_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->core_to_phy_link_width_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_print(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_c2p_link_enabed_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_proto_enabled : %s (" UH_FMT ")\n", (ptr_struct->core_to_phy_link_proto_enabled == 1 ? ("SDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 2 ? ("DDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 4 ? ("QDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 8 ? ("FDR10") : ((ptr_struct->core_to_phy_link_proto_enabled == 16 ? ("FDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 32 ? ("EDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 64 ? ("HDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 128 ? ("NDR") : ((ptr_struct->core_to_phy_link_proto_enabled == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->core_to_phy_link_proto_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_width_enabled : " UH_FMT "\n", ptr_struct->core_to_phy_link_width_enabled);
}

unsigned int reg_access_gpu_pddr_c2p_link_enabed_ib_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_C2P_LINK_ENABED_IB_EXT_SIZE;
}

void reg_access_gpu_pddr_c2p_link_enabed_ib_ext_dump(const struct reg_access_gpu_pddr_c2p_link_enabed_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_c2p_link_enabed_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_cable_cap_eth_ext_pack(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cable_ext_eth_proto_cap);
}

void reg_access_gpu_pddr_cable_cap_eth_ext_unpack(struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->cable_ext_eth_proto_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pddr_cable_cap_eth_ext_print(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_cable_cap_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_ext_eth_proto_cap : " U32H_FMT "\n", ptr_struct->cable_ext_eth_proto_cap);
}

unsigned int reg_access_gpu_pddr_cable_cap_eth_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_CABLE_CAP_ETH_EXT_SIZE;
}

void reg_access_gpu_pddr_cable_cap_eth_ext_dump(const struct reg_access_gpu_pddr_cable_cap_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_cable_cap_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_cable_cap_ib_ext_pack(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cable_link_speed_cap);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cable_link_width_cap);
}

void reg_access_gpu_pddr_cable_cap_ib_ext_unpack(struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->cable_link_speed_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->cable_link_width_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_cable_cap_ib_ext_print(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_cable_cap_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_link_speed_cap : %s (" UH_FMT ")\n", (ptr_struct->cable_link_speed_cap == 1 ? ("SDR") : ((ptr_struct->cable_link_speed_cap == 2 ? ("DDR") : ((ptr_struct->cable_link_speed_cap == 4 ? ("QDR") : ((ptr_struct->cable_link_speed_cap == 8 ? ("FDR10") : ((ptr_struct->cable_link_speed_cap == 16 ? ("FDR") : ((ptr_struct->cable_link_speed_cap == 32 ? ("EDR") : ((ptr_struct->cable_link_speed_cap == 64 ? ("HDR") : ((ptr_struct->cable_link_speed_cap == 128 ? ("NDR") : ((ptr_struct->cable_link_speed_cap == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->cable_link_speed_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_link_width_cap : " UH_FMT "\n", ptr_struct->cable_link_width_cap);
}

unsigned int reg_access_gpu_pddr_cable_cap_ib_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_CABLE_CAP_IB_EXT_SIZE;
}

void reg_access_gpu_pddr_cable_cap_ib_ext_dump(const struct reg_access_gpu_pddr_cable_cap_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_cable_cap_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_link_active_eth_ext_pack(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_eth_active);
}

void reg_access_gpu_pddr_link_active_eth_ext_unpack(struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->link_eth_active = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pddr_link_active_eth_ext_print(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_link_active_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_eth_active      : " U32H_FMT "\n", ptr_struct->link_eth_active);
}

unsigned int reg_access_gpu_pddr_link_active_eth_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_LINK_ACTIVE_ETH_EXT_SIZE;
}

void reg_access_gpu_pddr_link_active_eth_ext_dump(const struct reg_access_gpu_pddr_link_active_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_link_active_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_link_active_ib_ext_pack(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_speed_active);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->link_width_active);
}

void reg_access_gpu_pddr_link_active_ib_ext_unpack(struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->link_speed_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->link_width_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_link_active_ib_ext_print(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_link_active_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_speed_active    : %s (" UH_FMT ")\n", (ptr_struct->link_speed_active == 1 ? ("SDR") : ((ptr_struct->link_speed_active == 2 ? ("DDR") : ((ptr_struct->link_speed_active == 4 ? ("QDR") : ((ptr_struct->link_speed_active == 8 ? ("FDR10") : ((ptr_struct->link_speed_active == 16 ? ("FDR") : ((ptr_struct->link_speed_active == 32 ? ("EDR") : ((ptr_struct->link_speed_active == 64 ? ("HDR") : ((ptr_struct->link_speed_active == 128 ? ("NDR") : ((ptr_struct->link_speed_active == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->link_speed_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_width_active    : " UH_FMT "\n", ptr_struct->link_width_active);
}

unsigned int reg_access_gpu_pddr_link_active_ib_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_LINK_ACTIVE_IB_EXT_SIZE;
}

void reg_access_gpu_pddr_link_active_ib_ext_dump(const struct reg_access_gpu_pddr_link_active_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_link_active_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_monitor_opcode_ext_pack(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->monitor_opcode);
}

void reg_access_gpu_pddr_monitor_opcode_ext_unpack(struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->monitor_opcode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_monitor_opcode_ext_print(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_monitor_opcode_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "monitor_opcode       : " UH_FMT "\n", ptr_struct->monitor_opcode);
}

unsigned int reg_access_gpu_pddr_monitor_opcode_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_MONITOR_OPCODE_EXT_SIZE;
}

void reg_access_gpu_pddr_monitor_opcode_ext_dump(const struct reg_access_gpu_pddr_monitor_opcode_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_monitor_opcode_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_pack(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_manager_link_eth_enabled);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_unpack(struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->phy_manager_link_eth_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_print(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_eth_enabled : " U32H_FMT "\n", ptr_struct->phy_manager_link_eth_enabled);
}

unsigned int reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_PHY_MANAGER_LINK_ENABED_ETH_EXT_SIZE;
}

void reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_dump(const struct reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_pack(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->phy_manager_link_proto_enabled);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->phy_manager_link_width_enabled);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_unpack(struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->phy_manager_link_proto_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->phy_manager_link_width_enabled = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_print(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_proto_enabled : " UH_FMT "\n", ptr_struct->phy_manager_link_proto_enabled);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_width_enabled : " UH_FMT "\n", ptr_struct->phy_manager_link_width_enabled);
}

unsigned int reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_PHY_MANAGER_LINK_ENABED_IB_EXT_SIZE;
}

void reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_dump(const struct reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_cable_cap_ib_ext_pack(&(ptr_struct->pddr_cable_cap_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_cable_cap_ib_ext_unpack(&(ptr_struct->pddr_cable_cap_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cable_cap_eth_ext:\n");
	reg_access_gpu_pddr_cable_cap_eth_ext_print(&(ptr_struct->pddr_cable_cap_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_cable_cap_ib_ext:\n");
	reg_access_gpu_pddr_cable_cap_ib_ext_print(&(ptr_struct->pddr_cable_cap_ib_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_CABLE_PROTO_CAP_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_c2p_link_enabed_ib_ext_pack(&(ptr_struct->pddr_c2p_link_enabed_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_c2p_link_enabed_ib_ext_unpack(&(ptr_struct->pddr_c2p_link_enabed_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_c2p_link_enabed_eth_ext:\n");
	reg_access_gpu_pddr_c2p_link_enabed_eth_ext_print(&(ptr_struct->pddr_c2p_link_enabed_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_c2p_link_enabed_ib_ext:\n");
	reg_access_gpu_pddr_c2p_link_enabed_ib_ext_print(&(ptr_struct->pddr_c2p_link_enabed_ib_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_CORE_TO_PHY_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_link_active_ib_ext_pack(&(ptr_struct->pddr_link_active_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_link_active_ib_ext_unpack(&(ptr_struct->pddr_link_active_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_operation_info_page_link_active_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_active_eth_ext:\n");
	reg_access_gpu_pddr_link_active_eth_ext_print(&(ptr_struct->pddr_link_active_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_active_ib_ext:\n");
	reg_access_gpu_pddr_link_active_ib_ext_print(&(ptr_struct->pddr_link_active_ib_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_LINK_ACTIVE_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_link_active_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_operation_info_page_link_active_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_pack(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_pack(&(ptr_struct->pddr_phy_manager_link_enabed_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_unpack(union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_unpack(&(ptr_struct->pddr_phy_manager_link_enabed_ib_ext), ptr_buff);
}

void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_manager_link_enabed_eth_ext:\n");
	reg_access_gpu_pddr_phy_manager_link_enabed_eth_ext_print(&(ptr_struct->pddr_phy_manager_link_enabed_eth_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_manager_link_enabed_ib_ext:\n");
	reg_access_gpu_pddr_phy_manager_link_enabed_ib_ext_print(&(ptr_struct->pddr_phy_manager_link_enabed_ib_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_PHY_MANAGER_LINK_ENABLED_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_dump(const union reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_pack(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_monitor_opcode_ext_pack(&(ptr_struct->pddr_monitor_opcode_ext), ptr_buff);
}

void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_unpack(union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_monitor_opcode_ext_unpack(&(ptr_struct->pddr_monitor_opcode_ext), ptr_buff);
}

void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_print(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_monitor_opcode_ext:\n");
	reg_access_gpu_pddr_monitor_opcode_ext_print(&(ptr_struct->pddr_monitor_opcode_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_TROUBLESHOOTING_PAGE_STATUS_OPCODE_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_dump(const union reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_troubleshooting_page_status_opcode_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, *ptr_struct);
}

void reg_access_gpu_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	*ptr_struct = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_uint64 ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uint64               : " U64H_FMT "\n", (u_int64_t) *ptr_struct);
}

unsigned int reg_access_gpu_uint64_size(void)
{
	return REG_ACCESS_GPU_UINT64_SIZE;
}

void reg_access_gpu_uint64_dump(const u_int64_t *ptr_struct, FILE *fd)
{
	reg_access_gpu_uint64_print(ptr_struct, fd, 0);
}

void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_pack(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->symbol_error_counter_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->symbol_error_counter_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_error_recovery_counter_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_error_recovery_counter_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_downed_counter_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_downed_counter_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_errors_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_errors_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_remote_physical_errors_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_remote_physical_errors_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_switch_relay_errors_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_switch_relay_errors_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_discards_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_discards_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_constraint_errors_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_constraint_errors_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_constraint_errors_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_constraint_errors_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->local_link_integrity_errors_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->local_link_integrity_errors_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->excessive_buffer_overrun_errors_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->excessive_buffer_overrun_errors_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vl_15_dropped_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vl_15_dropped_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_data_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_data_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_data_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_data_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_pkts_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_pkts_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_pkts_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_pkts_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_wait_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_wait_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->qp1_dropped_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->qp1_dropped_low);
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_xmit_pkts_high);
	offset = 1184;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_xmit_pkts_low);
	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_multicast_xmit_pkts_high);
	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_multicast_xmit_pkts_low);
	offset = 1280;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_rcv_pkts_high);
	offset = 1312;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_rcv_pkts_low);
	offset = 1344;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_multicast_rcv_pkts_high);
	offset = 1376;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_multicast_rcv_pkts_low);
}

void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_unpack(struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->symbol_error_counter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->symbol_error_counter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->link_error_recovery_counter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->link_error_recovery_counter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->link_downed_counter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->link_downed_counter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->port_rcv_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->port_rcv_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->port_rcv_remote_physical_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->port_rcv_remote_physical_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->port_rcv_switch_relay_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->port_rcv_switch_relay_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->port_xmit_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->port_xmit_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->port_xmit_constraint_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->port_xmit_constraint_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->port_rcv_constraint_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->port_rcv_constraint_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->local_link_integrity_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->local_link_integrity_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->excessive_buffer_overrun_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->excessive_buffer_overrun_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->vl_15_dropped_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->vl_15_dropped_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->port_xmit_data_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->port_xmit_data_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->port_rcv_data_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->port_rcv_data_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->port_xmit_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->port_xmit_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->port_rcv_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->port_rcv_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->port_xmit_wait_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->port_xmit_wait_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->qp1_dropped_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->qp1_dropped_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1152;
	ptr_struct->port_unicast_xmit_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1184;
	ptr_struct->port_unicast_xmit_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1216;
	ptr_struct->port_multicast_xmit_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1248;
	ptr_struct->port_multicast_xmit_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1280;
	ptr_struct->port_unicast_rcv_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1312;
	ptr_struct->port_unicast_rcv_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1344;
	ptr_struct->port_multicast_rcv_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1376;
	ptr_struct->port_multicast_rcv_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_print(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_error_counter_high : " U32H_FMT "\n", ptr_struct->symbol_error_counter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_error_counter_low : " U32H_FMT "\n", ptr_struct->symbol_error_counter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_error_recovery_counter_high : " U32H_FMT "\n", ptr_struct->link_error_recovery_counter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_error_recovery_counter_low : " U32H_FMT "\n", ptr_struct->link_error_recovery_counter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_downed_counter_high : " U32H_FMT "\n", ptr_struct->link_downed_counter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_downed_counter_low : " U32H_FMT "\n", ptr_struct->link_downed_counter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_errors_high : " U32H_FMT "\n", ptr_struct->port_rcv_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_errors_low  : " U32H_FMT "\n", ptr_struct->port_rcv_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_remote_physical_errors_high : " U32H_FMT "\n", ptr_struct->port_rcv_remote_physical_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_remote_physical_errors_low : " U32H_FMT "\n", ptr_struct->port_rcv_remote_physical_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_switch_relay_errors_high : " U32H_FMT "\n", ptr_struct->port_rcv_switch_relay_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_switch_relay_errors_low : " U32H_FMT "\n", ptr_struct->port_rcv_switch_relay_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_discards_high : " U32H_FMT "\n", ptr_struct->port_xmit_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_discards_low : " U32H_FMT "\n", ptr_struct->port_xmit_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_constraint_errors_high : " U32H_FMT "\n", ptr_struct->port_xmit_constraint_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_constraint_errors_low : " U32H_FMT "\n", ptr_struct->port_xmit_constraint_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_constraint_errors_high : " U32H_FMT "\n", ptr_struct->port_rcv_constraint_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_constraint_errors_low : " U32H_FMT "\n", ptr_struct->port_rcv_constraint_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_link_integrity_errors_high : " U32H_FMT "\n", ptr_struct->local_link_integrity_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_link_integrity_errors_low : " U32H_FMT "\n", ptr_struct->local_link_integrity_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "excessive_buffer_overrun_errors_high : " U32H_FMT "\n", ptr_struct->excessive_buffer_overrun_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "excessive_buffer_overrun_errors_low : " U32H_FMT "\n", ptr_struct->excessive_buffer_overrun_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_15_dropped_high   : " U32H_FMT "\n", ptr_struct->vl_15_dropped_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_15_dropped_low    : " U32H_FMT "\n", ptr_struct->vl_15_dropped_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_data_high  : " U32H_FMT "\n", ptr_struct->port_xmit_data_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_data_low   : " U32H_FMT "\n", ptr_struct->port_xmit_data_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_data_high   : " U32H_FMT "\n", ptr_struct->port_rcv_data_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_data_low    : " U32H_FMT "\n", ptr_struct->port_rcv_data_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_pkts_high  : " U32H_FMT "\n", ptr_struct->port_xmit_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_pkts_low   : " U32H_FMT "\n", ptr_struct->port_xmit_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_pkts_high   : " U32H_FMT "\n", ptr_struct->port_rcv_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_pkts_low    : " U32H_FMT "\n", ptr_struct->port_rcv_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_wait_high  : " U32H_FMT "\n", ptr_struct->port_xmit_wait_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_wait_low   : " U32H_FMT "\n", ptr_struct->port_xmit_wait_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qp1_dropped_high     : " U32H_FMT "\n", ptr_struct->qp1_dropped_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qp1_dropped_low      : " U32H_FMT "\n", ptr_struct->qp1_dropped_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_xmit_pkts_high : " U32H_FMT "\n", ptr_struct->port_unicast_xmit_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_xmit_pkts_low : " U32H_FMT "\n", ptr_struct->port_unicast_xmit_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_multicast_xmit_pkts_high : " U32H_FMT "\n", ptr_struct->port_multicast_xmit_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_multicast_xmit_pkts_low : " U32H_FMT "\n", ptr_struct->port_multicast_xmit_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_rcv_pkts_high : " U32H_FMT "\n", ptr_struct->port_unicast_rcv_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_rcv_pkts_low : " U32H_FMT "\n", ptr_struct->port_unicast_rcv_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_multicast_rcv_pkts_high : " U32H_FMT "\n", ptr_struct->port_multicast_rcv_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_multicast_rcv_pkts_low : " U32H_FMT "\n", ptr_struct->port_multicast_rcv_pkts_low);
}

unsigned int reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_size(void)
{
	return REG_ACCESS_GPU_IB_LONG_PORTCNTRS_ATTRIBUTE_GRP_DATA_EXT_SIZE;
}

void reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_dump(const struct reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_pack(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_downed_counter);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_error_recovery_counter);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->symbol_error_counter);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->port_rcv_remote_physical_errors);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->port_rcv_errors);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->port_xmit_discards);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->port_rcv_switch_relay_errors);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->excessive_buffer_overrun_errors);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->local_link_integrity_errors);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_rcv_constraint_errors);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->port_xmit_constraint_errors);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vl_15_dropped);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->qp1_dropped);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_data);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_data);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_pkts);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_rcv_pkts);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_xmit_wait);
}

void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_unpack(struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->link_downed_counter = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->link_error_recovery_counter = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->symbol_error_counter = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->port_rcv_remote_physical_errors = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->port_rcv_errors = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->port_xmit_discards = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->port_rcv_switch_relay_errors = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 124;
	ptr_struct->excessive_buffer_overrun_errors = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 120;
	ptr_struct->local_link_integrity_errors = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 104;
	ptr_struct->port_rcv_constraint_errors = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->port_xmit_constraint_errors = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->vl_15_dropped = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->qp1_dropped = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->port_xmit_data = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->port_rcv_data = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->port_xmit_pkts = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->port_rcv_pkts = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->port_xmit_wait = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_print(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_IB_portcntrs_attribute_grp_data_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_downed_counter  : " UH_FMT "\n", ptr_struct->link_downed_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_error_recovery_counter : " UH_FMT "\n", ptr_struct->link_error_recovery_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_error_counter : " UH_FMT "\n", ptr_struct->symbol_error_counter);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_remote_physical_errors : " UH_FMT "\n", ptr_struct->port_rcv_remote_physical_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_errors      : " UH_FMT "\n", ptr_struct->port_rcv_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_discards   : " UH_FMT "\n", ptr_struct->port_xmit_discards);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_switch_relay_errors : " UH_FMT "\n", ptr_struct->port_rcv_switch_relay_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "excessive_buffer_overrun_errors : " UH_FMT "\n", ptr_struct->excessive_buffer_overrun_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_link_integrity_errors : " UH_FMT "\n", ptr_struct->local_link_integrity_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_constraint_errors : " UH_FMT "\n", ptr_struct->port_rcv_constraint_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_constraint_errors : " UH_FMT "\n", ptr_struct->port_xmit_constraint_errors);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vl_15_dropped        : " UH_FMT "\n", ptr_struct->vl_15_dropped);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "qp1_dropped          : " UH_FMT "\n", ptr_struct->qp1_dropped);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_data       : " U32H_FMT "\n", ptr_struct->port_xmit_data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_data        : " U32H_FMT "\n", ptr_struct->port_rcv_data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_pkts       : " U32H_FMT "\n", ptr_struct->port_xmit_pkts);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_rcv_pkts        : " U32H_FMT "\n", ptr_struct->port_rcv_pkts);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_xmit_wait       : " U32H_FMT "\n", ptr_struct->port_xmit_wait);
}

unsigned int reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_size(void)
{
	return REG_ACCESS_GPU_IB_PORTCNTRS_ATTRIBUTE_GRP_DATA_EXT_SIZE;
}

void reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_dump(const struct reg_access_gpu_IB_portcntrs_attribute_grp_data_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_CVB_ext_pack(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->cvb_data_index);
}

void reg_access_gpu_MRFV_CVB_ext_unpack(struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->cvb_data_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_gpu_MRFV_CVB_ext_print(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_CVB_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cvb_data_index       : " UH_FMT "\n", ptr_struct->cvb_data_index);
}

unsigned int reg_access_gpu_MRFV_CVB_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_CVB_EXT_SIZE;
}

void reg_access_gpu_MRFV_CVB_ext_dump(const struct reg_access_gpu_MRFV_CVB_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_CVB_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_PVS_MAIN_ext_pack(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs_main_data);
}

void reg_access_gpu_MRFV_PVS_MAIN_ext_unpack(struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->pvs_main_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_gpu_MRFV_PVS_MAIN_ext_print(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_PVS_MAIN_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs_main_data        : " UH_FMT "\n", ptr_struct->pvs_main_data);
}

unsigned int reg_access_gpu_MRFV_PVS_MAIN_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_PVS_MAIN_EXT_SIZE;
}

void reg_access_gpu_MRFV_PVS_MAIN_ext_dump(const struct reg_access_gpu_MRFV_PVS_MAIN_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_PVS_MAIN_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_PVS_TILE_ext_pack(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs_tile_data);
}

void reg_access_gpu_MRFV_PVS_TILE_ext_unpack(struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 27;
	ptr_struct->pvs_tile_data = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_gpu_MRFV_PVS_TILE_ext_print(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_PVS_TILE_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs_tile_data        : " UH_FMT "\n", ptr_struct->pvs_tile_data);
}

unsigned int reg_access_gpu_MRFV_PVS_TILE_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_PVS_TILE_EXT_SIZE;
}

void reg_access_gpu_MRFV_PVS_TILE_ext_dump(const struct reg_access_gpu_MRFV_PVS_TILE_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_PVS_TILE_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_ULT_ext_pack(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_gpu_MRFV_ULT_ext_unpack(struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_gpu_MRFV_ULT_ext_print(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_ULT_ext ========\n");

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

unsigned int reg_access_gpu_MRFV_ULT_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_ULT_EXT_SIZE;
}

void reg_access_gpu_MRFV_ULT_ext_dump(const struct reg_access_gpu_MRFV_ULT_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_ULT_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_drop_events_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_drop_events_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_octets_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_octets_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_broadcast_pkts_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_broadcast_pkts_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_multicast_pkts_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_multicast_pkts_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_crc_align_errors_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_crc_align_errors_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_undersize_pkts_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_undersize_pkts_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_oversize_pkts_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_oversize_pkts_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_fragments_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_fragments_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_jabbers_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_jabbers_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_collisions_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_collisions_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts64octets_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts64octets_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts65to127octets_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts65to127octets_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts128to255octets_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts128to255octets_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts256to511octets_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts256to511octets_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts512to1023octets_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts512to1023octets_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts1024to1518octets_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts1024to1518octets_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts1519to2047octets_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts1519to2047octets_low);
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts2048to4095octets_high);
	offset = 1184;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts2048to4095octets_low);
	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts4096to8191octets_high);
	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts4096to8191octets_low);
	offset = 1280;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts8192to10239octets_high);
	offset = 1312;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ether_stats_pkts8192to10239octets_low);
}

void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ether_stats_drop_events_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->ether_stats_drop_events_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ether_stats_octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->ether_stats_octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->ether_stats_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->ether_stats_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->ether_stats_broadcast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->ether_stats_broadcast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->ether_stats_multicast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->ether_stats_multicast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->ether_stats_crc_align_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->ether_stats_crc_align_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->ether_stats_undersize_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->ether_stats_undersize_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->ether_stats_oversize_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->ether_stats_oversize_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->ether_stats_fragments_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->ether_stats_fragments_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->ether_stats_jabbers_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->ether_stats_jabbers_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->ether_stats_collisions_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->ether_stats_collisions_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->ether_stats_pkts64octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->ether_stats_pkts64octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->ether_stats_pkts65to127octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->ether_stats_pkts65to127octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->ether_stats_pkts128to255octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->ether_stats_pkts128to255octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->ether_stats_pkts256to511octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->ether_stats_pkts256to511octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->ether_stats_pkts512to1023octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->ether_stats_pkts512to1023octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->ether_stats_pkts1024to1518octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->ether_stats_pkts1024to1518octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->ether_stats_pkts1519to2047octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->ether_stats_pkts1519to2047octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1152;
	ptr_struct->ether_stats_pkts2048to4095octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1184;
	ptr_struct->ether_stats_pkts2048to4095octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1216;
	ptr_struct->ether_stats_pkts4096to8191octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1248;
	ptr_struct->ether_stats_pkts4096to8191octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1280;
	ptr_struct->ether_stats_pkts8192to10239octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1312;
	ptr_struct->ether_stats_pkts8192to10239octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_drop_events_high : " U32H_FMT "\n", ptr_struct->ether_stats_drop_events_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_drop_events_low : " U32H_FMT "\n", ptr_struct->ether_stats_drop_events_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_broadcast_pkts_high : " U32H_FMT "\n", ptr_struct->ether_stats_broadcast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_broadcast_pkts_low : " U32H_FMT "\n", ptr_struct->ether_stats_broadcast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_multicast_pkts_high : " U32H_FMT "\n", ptr_struct->ether_stats_multicast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_multicast_pkts_low : " U32H_FMT "\n", ptr_struct->ether_stats_multicast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_crc_align_errors_high : " U32H_FMT "\n", ptr_struct->ether_stats_crc_align_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_crc_align_errors_low : " U32H_FMT "\n", ptr_struct->ether_stats_crc_align_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_undersize_pkts_high : " U32H_FMT "\n", ptr_struct->ether_stats_undersize_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_undersize_pkts_low : " U32H_FMT "\n", ptr_struct->ether_stats_undersize_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_oversize_pkts_high : " U32H_FMT "\n", ptr_struct->ether_stats_oversize_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_oversize_pkts_low : " U32H_FMT "\n", ptr_struct->ether_stats_oversize_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_fragments_high : " U32H_FMT "\n", ptr_struct->ether_stats_fragments_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_fragments_low : " U32H_FMT "\n", ptr_struct->ether_stats_fragments_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_jabbers_high : " U32H_FMT "\n", ptr_struct->ether_stats_jabbers_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_jabbers_low : " U32H_FMT "\n", ptr_struct->ether_stats_jabbers_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_collisions_high : " U32H_FMT "\n", ptr_struct->ether_stats_collisions_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_collisions_low : " U32H_FMT "\n", ptr_struct->ether_stats_collisions_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts64octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts64octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts64octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts64octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts65to127octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts65to127octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts65to127octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts65to127octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts128to255octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts128to255octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts128to255octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts128to255octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts256to511octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts256to511octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts256to511octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts256to511octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts512to1023octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts512to1023octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts512to1023octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts512to1023octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts1024to1518octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts1024to1518octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts1024to1518octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts1024to1518octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts1519to2047octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts1519to2047octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts1519to2047octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts1519to2047octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts2048to4095octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts2048to4095octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts2048to4095octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts2048to4095octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts4096to8191octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts4096to8191octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts4096to8191octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts4096to8191octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts8192to10239octets_high : " U32H_FMT "\n", ptr_struct->ether_stats_pkts8192to10239octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ether_stats_pkts8192to10239octets_low : " U32H_FMT "\n", ptr_struct->ether_stats_pkts8192to10239octets_low);
}

unsigned int reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_2819_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_octets_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_octets_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_ucast_pkts_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_ucast_pkts_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_discards_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_discards_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_errors_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_errors_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_unknown_protos_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_unknown_protos_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_octets_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_octets_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_ucast_pkts_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_ucast_pkts_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_discards_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_discards_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_errors_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_errors_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_multicast_pkts_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_multicast_pkts_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_broadcast_pkts_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_in_broadcast_pkts_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_multicast_pkts_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_multicast_pkts_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_broadcast_pkts_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->if_out_broadcast_pkts_low);
}

void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->if_in_octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->if_in_octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->if_in_ucast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->if_in_ucast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->if_in_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->if_in_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->if_in_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->if_in_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->if_in_unknown_protos_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->if_in_unknown_protos_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->if_out_octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->if_out_octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->if_out_ucast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->if_out_ucast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->if_out_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->if_out_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->if_out_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->if_out_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->if_in_multicast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->if_in_multicast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->if_in_broadcast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->if_in_broadcast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->if_out_multicast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->if_out_multicast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->if_out_broadcast_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->if_out_broadcast_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_octets_high    : " U32H_FMT "\n", ptr_struct->if_in_octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_octets_low     : " U32H_FMT "\n", ptr_struct->if_in_octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_ucast_pkts_high : " U32H_FMT "\n", ptr_struct->if_in_ucast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_ucast_pkts_low : " U32H_FMT "\n", ptr_struct->if_in_ucast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_discards_high  : " U32H_FMT "\n", ptr_struct->if_in_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_discards_low   : " U32H_FMT "\n", ptr_struct->if_in_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_errors_high    : " U32H_FMT "\n", ptr_struct->if_in_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_errors_low     : " U32H_FMT "\n", ptr_struct->if_in_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_unknown_protos_high : " U32H_FMT "\n", ptr_struct->if_in_unknown_protos_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_unknown_protos_low : " U32H_FMT "\n", ptr_struct->if_in_unknown_protos_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_octets_high   : " U32H_FMT "\n", ptr_struct->if_out_octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_octets_low    : " U32H_FMT "\n", ptr_struct->if_out_octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_ucast_pkts_high : " U32H_FMT "\n", ptr_struct->if_out_ucast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_ucast_pkts_low : " U32H_FMT "\n", ptr_struct->if_out_ucast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_discards_high : " U32H_FMT "\n", ptr_struct->if_out_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_discards_low  : " U32H_FMT "\n", ptr_struct->if_out_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_errors_high   : " U32H_FMT "\n", ptr_struct->if_out_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_errors_low    : " U32H_FMT "\n", ptr_struct->if_out_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_multicast_pkts_high : " U32H_FMT "\n", ptr_struct->if_in_multicast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_multicast_pkts_low : " U32H_FMT "\n", ptr_struct->if_in_multicast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_broadcast_pkts_high : " U32H_FMT "\n", ptr_struct->if_in_broadcast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_in_broadcast_pkts_low : " U32H_FMT "\n", ptr_struct->if_in_broadcast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_multicast_pkts_high : " U32H_FMT "\n", ptr_struct->if_out_multicast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_multicast_pkts_low : " U32H_FMT "\n", ptr_struct->if_out_multicast_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_broadcast_pkts_high : " U32H_FMT "\n", ptr_struct->if_out_broadcast_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "if_out_broadcast_pkts_low : " U32H_FMT "\n", ptr_struct->if_out_broadcast_pkts_low);
}

unsigned int reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_2863_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_alignment_errors_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_alignment_errors_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_fcs_errors_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_fcs_errors_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_single_collision_frames_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_single_collision_frames_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_multiple_collision_frames_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_multiple_collision_frames_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_sqe_test_errors_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_sqe_test_errors_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_deferred_transmissions_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_deferred_transmissions_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_late_collisions_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_late_collisions_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_excessive_collisions_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_excessive_collisions_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_internal_mac_transmit_errors_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_internal_mac_transmit_errors_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_carrier_sense_errors_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_carrier_sense_errors_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_frame_too_longs_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_frame_too_longs_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_internal_mac_receive_errors_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_internal_mac_receive_errors_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_symbol_errors_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3stats_symbol_errors_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3control_in_unknown_opcodes_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3control_in_unknown_opcodes_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3in_pause_frames_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3in_pause_frames_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3out_pause_frames_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dot3out_pause_frames_low);
}

void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->dot3stats_alignment_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->dot3stats_alignment_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->dot3stats_fcs_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->dot3stats_fcs_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->dot3stats_single_collision_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->dot3stats_single_collision_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->dot3stats_multiple_collision_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->dot3stats_multiple_collision_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->dot3stats_sqe_test_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->dot3stats_sqe_test_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->dot3stats_deferred_transmissions_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->dot3stats_deferred_transmissions_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->dot3stats_late_collisions_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->dot3stats_late_collisions_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->dot3stats_excessive_collisions_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->dot3stats_excessive_collisions_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->dot3stats_internal_mac_transmit_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->dot3stats_internal_mac_transmit_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->dot3stats_carrier_sense_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->dot3stats_carrier_sense_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->dot3stats_frame_too_longs_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->dot3stats_frame_too_longs_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->dot3stats_internal_mac_receive_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->dot3stats_internal_mac_receive_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->dot3stats_symbol_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->dot3stats_symbol_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->dot3control_in_unknown_opcodes_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->dot3control_in_unknown_opcodes_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->dot3in_pause_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->dot3in_pause_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->dot3out_pause_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->dot3out_pause_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_alignment_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_alignment_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_alignment_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_alignment_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_fcs_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_fcs_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_fcs_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_fcs_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_single_collision_frames_high : " U32H_FMT "\n", ptr_struct->dot3stats_single_collision_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_single_collision_frames_low : " U32H_FMT "\n", ptr_struct->dot3stats_single_collision_frames_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_multiple_collision_frames_high : " U32H_FMT "\n", ptr_struct->dot3stats_multiple_collision_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_multiple_collision_frames_low : " U32H_FMT "\n", ptr_struct->dot3stats_multiple_collision_frames_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_sqe_test_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_sqe_test_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_sqe_test_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_sqe_test_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_deferred_transmissions_high : " U32H_FMT "\n", ptr_struct->dot3stats_deferred_transmissions_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_deferred_transmissions_low : " U32H_FMT "\n", ptr_struct->dot3stats_deferred_transmissions_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_late_collisions_high : " U32H_FMT "\n", ptr_struct->dot3stats_late_collisions_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_late_collisions_low : " U32H_FMT "\n", ptr_struct->dot3stats_late_collisions_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_excessive_collisions_high : " U32H_FMT "\n", ptr_struct->dot3stats_excessive_collisions_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_excessive_collisions_low : " U32H_FMT "\n", ptr_struct->dot3stats_excessive_collisions_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_internal_mac_transmit_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_internal_mac_transmit_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_internal_mac_transmit_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_internal_mac_transmit_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_carrier_sense_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_carrier_sense_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_carrier_sense_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_carrier_sense_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_frame_too_longs_high : " U32H_FMT "\n", ptr_struct->dot3stats_frame_too_longs_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_frame_too_longs_low : " U32H_FMT "\n", ptr_struct->dot3stats_frame_too_longs_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_internal_mac_receive_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_internal_mac_receive_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_internal_mac_receive_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_internal_mac_receive_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_symbol_errors_high : " U32H_FMT "\n", ptr_struct->dot3stats_symbol_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3stats_symbol_errors_low : " U32H_FMT "\n", ptr_struct->dot3stats_symbol_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3control_in_unknown_opcodes_high : " U32H_FMT "\n", ptr_struct->dot3control_in_unknown_opcodes_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3control_in_unknown_opcodes_low : " U32H_FMT "\n", ptr_struct->dot3control_in_unknown_opcodes_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3in_pause_frames_high : " U32H_FMT "\n", ptr_struct->dot3in_pause_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3in_pause_frames_low : " U32H_FMT "\n", ptr_struct->dot3in_pause_frames_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3out_pause_frames_high : " U32H_FMT "\n", ptr_struct->dot3out_pause_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dot3out_pause_frames_low : " U32H_FMT "\n", ptr_struct->dot3out_pause_frames_low);
}

unsigned int reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_3635_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frames_transmitted_ok_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frames_transmitted_ok_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frames_received_ok_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frames_received_ok_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frame_check_sequence_errors_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frame_check_sequence_errors_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_alignment_errors_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_alignment_errors_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_octets_transmitted_ok_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_octets_transmitted_ok_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_octets_received_ok_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_octets_received_ok_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_multicast_frames_xmitted_ok_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_multicast_frames_xmitted_ok_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_broadcast_frames_xmitted_ok_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_broadcast_frames_xmitted_ok_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_multicast_frames_received_ok_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_multicast_frames_received_ok_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_broadcast_frames_received_ok_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_broadcast_frames_received_ok_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_in_range_length_errors_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_in_range_length_errors_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_out_of_range_length_field_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_out_of_range_length_field_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frame_too_long_errors_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_frame_too_long_errors_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_symbol_error_during_carrier_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_symbol_error_during_carrier_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_mac_control_frames_transmitted_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_mac_control_frames_transmitted_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_mac_control_frames_received_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_mac_control_frames_received_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_unsupported_opcodes_received_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_unsupported_opcodes_received_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_pause_mac_ctrl_frames_received_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_pause_mac_ctrl_frames_received_low);
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_pause_mac_ctrl_frames_transmitted_high);
	offset = 1184;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->a_pause_mac_ctrl_frames_transmitted_low);
}

void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->a_frames_transmitted_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->a_frames_transmitted_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->a_frames_received_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->a_frames_received_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->a_frame_check_sequence_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->a_frame_check_sequence_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->a_alignment_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->a_alignment_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->a_octets_transmitted_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->a_octets_transmitted_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->a_octets_received_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->a_octets_received_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->a_multicast_frames_xmitted_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->a_multicast_frames_xmitted_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->a_broadcast_frames_xmitted_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->a_broadcast_frames_xmitted_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->a_multicast_frames_received_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->a_multicast_frames_received_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->a_broadcast_frames_received_ok_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->a_broadcast_frames_received_ok_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->a_in_range_length_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->a_in_range_length_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->a_out_of_range_length_field_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->a_out_of_range_length_field_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->a_frame_too_long_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->a_frame_too_long_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->a_symbol_error_during_carrier_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->a_symbol_error_during_carrier_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->a_mac_control_frames_transmitted_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->a_mac_control_frames_transmitted_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->a_mac_control_frames_received_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->a_mac_control_frames_received_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->a_unsupported_opcodes_received_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->a_unsupported_opcodes_received_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->a_pause_mac_ctrl_frames_received_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->a_pause_mac_ctrl_frames_received_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1152;
	ptr_struct->a_pause_mac_ctrl_frames_transmitted_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1184;
	ptr_struct->a_pause_mac_ctrl_frames_transmitted_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frames_transmitted_ok_high : " U32H_FMT "\n", ptr_struct->a_frames_transmitted_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frames_transmitted_ok_low : " U32H_FMT "\n", ptr_struct->a_frames_transmitted_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frames_received_ok_high : " U32H_FMT "\n", ptr_struct->a_frames_received_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frames_received_ok_low : " U32H_FMT "\n", ptr_struct->a_frames_received_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frame_check_sequence_errors_high : " U32H_FMT "\n", ptr_struct->a_frame_check_sequence_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frame_check_sequence_errors_low : " U32H_FMT "\n", ptr_struct->a_frame_check_sequence_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_alignment_errors_high : " U32H_FMT "\n", ptr_struct->a_alignment_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_alignment_errors_low : " U32H_FMT "\n", ptr_struct->a_alignment_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_octets_transmitted_ok_high : " U32H_FMT "\n", ptr_struct->a_octets_transmitted_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_octets_transmitted_ok_low : " U32H_FMT "\n", ptr_struct->a_octets_transmitted_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_octets_received_ok_high : " U32H_FMT "\n", ptr_struct->a_octets_received_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_octets_received_ok_low : " U32H_FMT "\n", ptr_struct->a_octets_received_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_multicast_frames_xmitted_ok_high : " U32H_FMT "\n", ptr_struct->a_multicast_frames_xmitted_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_multicast_frames_xmitted_ok_low : " U32H_FMT "\n", ptr_struct->a_multicast_frames_xmitted_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_broadcast_frames_xmitted_ok_high : " U32H_FMT "\n", ptr_struct->a_broadcast_frames_xmitted_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_broadcast_frames_xmitted_ok_low : " U32H_FMT "\n", ptr_struct->a_broadcast_frames_xmitted_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_multicast_frames_received_ok_high : " U32H_FMT "\n", ptr_struct->a_multicast_frames_received_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_multicast_frames_received_ok_low : " U32H_FMT "\n", ptr_struct->a_multicast_frames_received_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_broadcast_frames_received_ok_high : " U32H_FMT "\n", ptr_struct->a_broadcast_frames_received_ok_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_broadcast_frames_received_ok_low : " U32H_FMT "\n", ptr_struct->a_broadcast_frames_received_ok_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_in_range_length_errors_high : " U32H_FMT "\n", ptr_struct->a_in_range_length_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_in_range_length_errors_low : " U32H_FMT "\n", ptr_struct->a_in_range_length_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_out_of_range_length_field_high : " U32H_FMT "\n", ptr_struct->a_out_of_range_length_field_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_out_of_range_length_field_low : " U32H_FMT "\n", ptr_struct->a_out_of_range_length_field_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frame_too_long_errors_high : " U32H_FMT "\n", ptr_struct->a_frame_too_long_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_frame_too_long_errors_low : " U32H_FMT "\n", ptr_struct->a_frame_too_long_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_symbol_error_during_carrier_high : " U32H_FMT "\n", ptr_struct->a_symbol_error_during_carrier_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_symbol_error_during_carrier_low : " U32H_FMT "\n", ptr_struct->a_symbol_error_during_carrier_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_mac_control_frames_transmitted_high : " U32H_FMT "\n", ptr_struct->a_mac_control_frames_transmitted_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_mac_control_frames_transmitted_low : " U32H_FMT "\n", ptr_struct->a_mac_control_frames_transmitted_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_mac_control_frames_received_high : " U32H_FMT "\n", ptr_struct->a_mac_control_frames_received_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_mac_control_frames_received_low : " U32H_FMT "\n", ptr_struct->a_mac_control_frames_received_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_unsupported_opcodes_received_high : " U32H_FMT "\n", ptr_struct->a_unsupported_opcodes_received_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_unsupported_opcodes_received_low : " U32H_FMT "\n", ptr_struct->a_unsupported_opcodes_received_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_pause_mac_ctrl_frames_received_high : " U32H_FMT "\n", ptr_struct->a_pause_mac_ctrl_frames_received_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_pause_mac_ctrl_frames_received_low : " U32H_FMT "\n", ptr_struct->a_pause_mac_ctrl_frames_received_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_pause_mac_ctrl_frames_transmitted_high : " U32H_FMT "\n", ptr_struct->a_pause_mac_ctrl_frames_transmitted_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "a_pause_mac_ctrl_frames_transmitted_low : " U32H_FMT "\n", ptr_struct->a_pause_mac_ctrl_frames_transmitted_low);
}

unsigned int reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_802_3_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_discard_cntrs_grp_ext_pack(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_general_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_general_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_policy_engine_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_policy_engine_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_vlan_membership_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_vlan_membership_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_tag_frame_type_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_tag_frame_type_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_vlan_membership_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_vlan_membership_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->loopback_filter_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->loopback_filter_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_general_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_general_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_hoq_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_hoq_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_isolation_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_isolation_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_policy_engine_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_policy_engine_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_tx_link_down_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_tx_link_down_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_stp_filter_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_stp_filter_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_hoq_stall_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_hoq_stall_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_sll_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->egress_sll_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_discard_all_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ingress_discard_all_low);
}

void reg_access_gpu_eth_discard_cntrs_grp_ext_unpack(struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->ingress_general_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->ingress_general_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ingress_policy_engine_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->ingress_policy_engine_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->ingress_vlan_membership_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->ingress_vlan_membership_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->ingress_tag_frame_type_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->ingress_tag_frame_type_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->egress_vlan_membership_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->egress_vlan_membership_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->loopback_filter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->loopback_filter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->egress_general_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->egress_general_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->egress_hoq_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->egress_hoq_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->port_isolation_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->port_isolation_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->egress_policy_engine_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->egress_policy_engine_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->ingress_tx_link_down_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->ingress_tx_link_down_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->egress_stp_filter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->egress_stp_filter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->egress_hoq_stall_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->egress_hoq_stall_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->egress_sll_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->egress_sll_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->ingress_discard_all_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->ingress_discard_all_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_discard_cntrs_grp_ext_print(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_discard_cntrs_grp_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_general_high : " U32H_FMT "\n", ptr_struct->ingress_general_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_general_low  : " U32H_FMT "\n", ptr_struct->ingress_general_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_policy_engine_high : " U32H_FMT "\n", ptr_struct->ingress_policy_engine_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_policy_engine_low : " U32H_FMT "\n", ptr_struct->ingress_policy_engine_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_vlan_membership_high : " U32H_FMT "\n", ptr_struct->ingress_vlan_membership_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_vlan_membership_low : " U32H_FMT "\n", ptr_struct->ingress_vlan_membership_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_tag_frame_type_high : " U32H_FMT "\n", ptr_struct->ingress_tag_frame_type_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_tag_frame_type_low : " U32H_FMT "\n", ptr_struct->ingress_tag_frame_type_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_vlan_membership_high : " U32H_FMT "\n", ptr_struct->egress_vlan_membership_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_vlan_membership_low : " U32H_FMT "\n", ptr_struct->egress_vlan_membership_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "loopback_filter_high : " U32H_FMT "\n", ptr_struct->loopback_filter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "loopback_filter_low  : " U32H_FMT "\n", ptr_struct->loopback_filter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_general_high  : " U32H_FMT "\n", ptr_struct->egress_general_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_general_low   : " U32H_FMT "\n", ptr_struct->egress_general_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_hoq_high      : " U32H_FMT "\n", ptr_struct->egress_hoq_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_hoq_low       : " U32H_FMT "\n", ptr_struct->egress_hoq_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_isolation_high  : " U32H_FMT "\n", ptr_struct->port_isolation_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_isolation_low   : " U32H_FMT "\n", ptr_struct->port_isolation_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_policy_engine_high : " U32H_FMT "\n", ptr_struct->egress_policy_engine_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_policy_engine_low : " U32H_FMT "\n", ptr_struct->egress_policy_engine_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_tx_link_down_high : " U32H_FMT "\n", ptr_struct->ingress_tx_link_down_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_tx_link_down_low : " U32H_FMT "\n", ptr_struct->ingress_tx_link_down_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_stp_filter_high : " U32H_FMT "\n", ptr_struct->egress_stp_filter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_stp_filter_low : " U32H_FMT "\n", ptr_struct->egress_stp_filter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_hoq_stall_high : " U32H_FMT "\n", ptr_struct->egress_hoq_stall_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_hoq_stall_low : " U32H_FMT "\n", ptr_struct->egress_hoq_stall_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_sll_high      : " U32H_FMT "\n", ptr_struct->egress_sll_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "egress_sll_low       : " U32H_FMT "\n", ptr_struct->egress_sll_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_discard_all_high : " U32H_FMT "\n", ptr_struct->ingress_discard_all_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ingress_discard_all_low : " U32H_FMT "\n", ptr_struct->ingress_discard_all_low);
}

unsigned int reg_access_gpu_eth_discard_cntrs_grp_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_DISCARD_CNTRS_GRP_EXT_SIZE;
}

void reg_access_gpu_eth_discard_cntrs_grp_ext_dump(const struct reg_access_gpu_eth_discard_cntrs_grp_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_discard_cntrs_grp_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_transmit_wait_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_transmit_wait_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ecn_marked_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ecn_marked_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->no_buffer_discard_mc_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->no_buffer_discard_mc_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_ebp_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_ebp_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_ebp_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_ebp_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_buffer_almost_full_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_buffer_almost_full_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_buffer_full_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_buffer_full_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_icrc_encapsulated_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_icrc_encapsulated_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts64octets_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts64octets_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts65to127octets_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts65to127octets_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts128to255octets_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts128to255octets_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts256to511octets_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts256to511octets_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts512to1023octets_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts512to1023octets_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts1024to1518octets_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts1024to1518octets_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts1519to2047octets_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts1519to2047octets_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts2048to4095octets_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts2048to4095octets_low);
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts4096to8191octets_high);
	offset = 1184;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts4096to8191octets_low);
	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts8192to10239octets_high);
	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_stats_pkts8192to10239octets_low);
	offset = 1280;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ece_marked_high);
	offset = 1312;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ece_marked_low);
	offset = 1344;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_int_cksm_err_high);
	offset = 1376;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_int_cksm_err_low);
}

void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->port_transmit_wait_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->port_transmit_wait_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ecn_marked_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->ecn_marked_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->no_buffer_discard_mc_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->no_buffer_discard_mc_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->rx_ebp_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->rx_ebp_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->tx_ebp_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->tx_ebp_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->rx_buffer_almost_full_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->rx_buffer_almost_full_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->rx_buffer_full_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->rx_buffer_full_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->rx_icrc_encapsulated_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->rx_icrc_encapsulated_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->tx_stats_pkts64octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->tx_stats_pkts64octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->tx_stats_pkts65to127octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->tx_stats_pkts65to127octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->tx_stats_pkts128to255octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->tx_stats_pkts128to255octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->tx_stats_pkts256to511octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->tx_stats_pkts256to511octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->tx_stats_pkts512to1023octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->tx_stats_pkts512to1023octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->tx_stats_pkts1024to1518octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->tx_stats_pkts1024to1518octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->tx_stats_pkts1519to2047octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->tx_stats_pkts1519to2047octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->tx_stats_pkts2048to4095octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->tx_stats_pkts2048to4095octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1152;
	ptr_struct->tx_stats_pkts4096to8191octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1184;
	ptr_struct->tx_stats_pkts4096to8191octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1216;
	ptr_struct->tx_stats_pkts8192to10239octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1248;
	ptr_struct->tx_stats_pkts8192to10239octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1280;
	ptr_struct->ece_marked_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1312;
	ptr_struct->ece_marked_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1344;
	ptr_struct->tx_int_cksm_err_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1376;
	ptr_struct->tx_int_cksm_err_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_print(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_transmit_wait_high : " U32H_FMT "\n", ptr_struct->port_transmit_wait_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_transmit_wait_low : " U32H_FMT "\n", ptr_struct->port_transmit_wait_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecn_marked_high      : " U32H_FMT "\n", ptr_struct->ecn_marked_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecn_marked_low       : " U32H_FMT "\n", ptr_struct->ecn_marked_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_buffer_discard_mc_high : " U32H_FMT "\n", ptr_struct->no_buffer_discard_mc_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_buffer_discard_mc_low : " U32H_FMT "\n", ptr_struct->no_buffer_discard_mc_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_ebp_high          : " U32H_FMT "\n", ptr_struct->rx_ebp_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_ebp_low           : " U32H_FMT "\n", ptr_struct->rx_ebp_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ebp_high          : " U32H_FMT "\n", ptr_struct->tx_ebp_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ebp_low           : " U32H_FMT "\n", ptr_struct->tx_ebp_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_buffer_almost_full_high : " U32H_FMT "\n", ptr_struct->rx_buffer_almost_full_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_buffer_almost_full_low : " U32H_FMT "\n", ptr_struct->rx_buffer_almost_full_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_buffer_full_high  : " U32H_FMT "\n", ptr_struct->rx_buffer_full_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_buffer_full_low   : " U32H_FMT "\n", ptr_struct->rx_buffer_full_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_icrc_encapsulated_high : " U32H_FMT "\n", ptr_struct->rx_icrc_encapsulated_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_icrc_encapsulated_low : " U32H_FMT "\n", ptr_struct->rx_icrc_encapsulated_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts64octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts64octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts64octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts64octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts65to127octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts65to127octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts65to127octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts65to127octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts128to255octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts128to255octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts128to255octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts128to255octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts256to511octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts256to511octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts256to511octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts256to511octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts512to1023octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts512to1023octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts512to1023octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts512to1023octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts1024to1518octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts1024to1518octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts1024to1518octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts1024to1518octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts1519to2047octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts1519to2047octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts1519to2047octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts1519to2047octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts2048to4095octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts2048to4095octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts2048to4095octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts2048to4095octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts4096to8191octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts4096to8191octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts4096to8191octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts4096to8191octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts8192to10239octets_high : " U32H_FMT "\n", ptr_struct->tx_stats_pkts8192to10239octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_stats_pkts8192to10239octets_low : " U32H_FMT "\n", ptr_struct->tx_stats_pkts8192to10239octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ece_marked_high      : " U32H_FMT "\n", ptr_struct->ece_marked_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ece_marked_low       : " U32H_FMT "\n", ptr_struct->ece_marked_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_int_cksm_err_high : " U32H_FMT "\n", ptr_struct->tx_int_cksm_err_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_int_cksm_err_low  : " U32H_FMT "\n", ptr_struct->tx_int_cksm_err_low);
}

unsigned int reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_EXTENDED_CNTRS_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_per_prio_grp_data_layout_ext_pack(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_octets_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_octets_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_frames_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_frames_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_octets_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_octets_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_frames_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_frames_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_duration_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_duration_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_pause_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_pause_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_pause_duration_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_pause_duration_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_transition_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_pause_transition_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_discards_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_discards_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_stall_minor_watermark_cnt_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_stall_minor_watermark_cnt_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_stall_critical_watermark_cnt_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->device_stall_critical_watermark_cnt_low);
}

void reg_access_gpu_eth_per_prio_grp_data_layout_ext_unpack(struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->rx_octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->rx_octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->rx_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->rx_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->tx_octets_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->tx_octets_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->tx_frames_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->tx_frames_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->rx_pause_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->rx_pause_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->rx_pause_duration_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->rx_pause_duration_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->tx_pause_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->tx_pause_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->tx_pause_duration_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->tx_pause_duration_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->rx_pause_transition_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->rx_pause_transition_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->rx_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->rx_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->device_stall_minor_watermark_cnt_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->device_stall_minor_watermark_cnt_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->device_stall_critical_watermark_cnt_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->device_stall_critical_watermark_cnt_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_per_prio_grp_data_layout_ext_print(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_per_prio_grp_data_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_octets_high       : " U32H_FMT "\n", ptr_struct->rx_octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_octets_low        : " U32H_FMT "\n", ptr_struct->rx_octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_frames_high       : " U32H_FMT "\n", ptr_struct->rx_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_frames_low        : " U32H_FMT "\n", ptr_struct->rx_frames_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_octets_high       : " U32H_FMT "\n", ptr_struct->tx_octets_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_octets_low        : " U32H_FMT "\n", ptr_struct->tx_octets_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_frames_high       : " U32H_FMT "\n", ptr_struct->tx_frames_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_frames_low        : " U32H_FMT "\n", ptr_struct->tx_frames_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_high        : " U32H_FMT "\n", ptr_struct->rx_pause_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_low         : " U32H_FMT "\n", ptr_struct->rx_pause_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_duration_high : " U32H_FMT "\n", ptr_struct->rx_pause_duration_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_duration_low : " U32H_FMT "\n", ptr_struct->rx_pause_duration_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_pause_high        : " U32H_FMT "\n", ptr_struct->tx_pause_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_pause_low         : " U32H_FMT "\n", ptr_struct->tx_pause_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_pause_duration_high : " U32H_FMT "\n", ptr_struct->tx_pause_duration_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_pause_duration_low : " U32H_FMT "\n", ptr_struct->tx_pause_duration_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_transition_high : " U32H_FMT "\n", ptr_struct->rx_pause_transition_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_pause_transition_low : " U32H_FMT "\n", ptr_struct->rx_pause_transition_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_discards_high     : " U32H_FMT "\n", ptr_struct->rx_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_discards_low      : " U32H_FMT "\n", ptr_struct->rx_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_stall_minor_watermark_cnt_high : " U32H_FMT "\n", ptr_struct->device_stall_minor_watermark_cnt_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_stall_minor_watermark_cnt_low : " U32H_FMT "\n", ptr_struct->device_stall_minor_watermark_cnt_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_stall_critical_watermark_cnt_high : " U32H_FMT "\n", ptr_struct->device_stall_critical_watermark_cnt_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_stall_critical_watermark_cnt_low : " U32H_FMT "\n", ptr_struct->device_stall_critical_watermark_cnt_low);
}

unsigned int reg_access_gpu_eth_per_prio_grp_data_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_PER_PRIO_GRP_DATA_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_per_prio_grp_data_layout_ext_dump(const struct reg_access_gpu_eth_per_prio_grp_data_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_per_prio_grp_data_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_pack(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->wred_discard_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->wred_discard_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ecn_marked_tc_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ecn_marked_tc_low);
}

void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_unpack(struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->wred_discard_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->wred_discard_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ecn_marked_tc_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->ecn_marked_tc_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_print(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_per_traffic_class_cong_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wred_discard_high    : " U32H_FMT "\n", ptr_struct->wred_discard_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wred_discard_low     : " U32H_FMT "\n", ptr_struct->wred_discard_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecn_marked_tc_high   : " U32H_FMT "\n", ptr_struct->ecn_marked_tc_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ecn_marked_tc_low    : " U32H_FMT "\n", ptr_struct->ecn_marked_tc_low);
}

unsigned int reg_access_gpu_eth_per_traffic_class_cong_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_PER_TRAFFIC_CLASS_CONG_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_per_traffic_class_cong_layout_ext_dump(const struct reg_access_gpu_eth_per_traffic_class_cong_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_per_traffic_class_cong_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_eth_per_traffic_class_layout_ext_pack(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->transmit_queue_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->transmit_queue_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->no_buffer_discard_uc_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->no_buffer_discard_uc_low);
}

void reg_access_gpu_eth_per_traffic_class_layout_ext_unpack(struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->transmit_queue_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->transmit_queue_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->no_buffer_discard_uc_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->no_buffer_discard_uc_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_eth_per_traffic_class_layout_ext_print(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_eth_per_traffic_class_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "transmit_queue_high  : " U32H_FMT "\n", ptr_struct->transmit_queue_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "transmit_queue_low   : " U32H_FMT "\n", ptr_struct->transmit_queue_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_buffer_discard_uc_high : " U32H_FMT "\n", ptr_struct->no_buffer_discard_uc_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "no_buffer_discard_uc_low : " U32H_FMT "\n", ptr_struct->no_buffer_discard_uc_low);
}

unsigned int reg_access_gpu_eth_per_traffic_class_layout_ext_size(void)
{
	return REG_ACCESS_GPU_ETH_PER_TRAFFIC_CLASS_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_eth_per_traffic_class_layout_ext_dump(const struct reg_access_gpu_eth_per_traffic_class_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_eth_per_traffic_class_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_module_latched_flag_info_ext_pack(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, u_int8_t *ptr_buff)
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
}

void reg_access_gpu_module_latched_flag_info_ext_unpack(struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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
}

void reg_access_gpu_module_latched_flag_info_ext_print(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_module_latched_flag_info_ext ========\n");

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
}

unsigned int reg_access_gpu_module_latched_flag_info_ext_size(void)
{
	return REG_ACCESS_GPU_MODULE_LATCHED_FLAG_INFO_EXT_SIZE;
}

void reg_access_gpu_module_latched_flag_info_ext_dump(const struct reg_access_gpu_module_latched_flag_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_module_latched_flag_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_link_down_info_page_ext_pack(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->down_blame);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_reason_opcode);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->remote_reason_opcode);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->e2e_reason_opcode);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ts1_opcode);
	offset = 408;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->min_est_eff_ber_magnitude);
	offset = 404;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->min_est_eff_ber_coef);
	offset = 392;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mean_est_eff_ber_magnitude);
	offset = 388;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mean_est_eff_ber_coef);
	offset = 440;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->max_est_eff_ber_magnitude);
	offset = 436;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_est_eff_ber_coef);
	offset = 464;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_est_eff_ber_alarms);
	offset = 448;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->num_of_est_eff_ber_warnings);
}

void reg_access_gpu_pddr_link_down_info_page_ext_unpack(struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->down_blame = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->local_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->remote_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->e2e_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->ts1_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 408;
	ptr_struct->min_est_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 404;
	ptr_struct->min_est_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 392;
	ptr_struct->mean_est_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 388;
	ptr_struct->mean_est_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 440;
	ptr_struct->max_est_eff_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 436;
	ptr_struct->max_est_eff_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 464;
	ptr_struct->num_of_est_eff_ber_alarms = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 448;
	ptr_struct->num_of_est_eff_ber_warnings = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_link_down_info_page_ext_print(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_link_down_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_blame           : %s (" UH_FMT ")\n", (ptr_struct->down_blame == 0 ? ("Unknown") : ((ptr_struct->down_blame == 1 ? ("Local_phy") : ((ptr_struct->down_blame == 2 ? ("Remote_phy") : ("unknown")))))), ptr_struct->down_blame);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_reason_opcode  : %s (" UH_FMT ")\n", (ptr_struct->local_reason_opcode == 0 ? ("No_link_down_indication") : ((ptr_struct->local_reason_opcode == 1 ? ("Unknown_reason") : ((ptr_struct->local_reason_opcode == 2 ? ("Hi_SER_or_Hi_BER") : ((ptr_struct->local_reason_opcode == 3 ? ("Block_Lock_loss") : ((ptr_struct->local_reason_opcode == 4 ? ("Alignment_loss") : ((ptr_struct->local_reason_opcode == 5 ? ("FEC_sync_loss") : ((ptr_struct->local_reason_opcode == 6 ? ("PLL_lock_loss") : ((ptr_struct->local_reason_opcode == 7 ? ("FIFO_overflow") : ((ptr_struct->local_reason_opcode == 8 ? ("false_SKIP_condition") : ((ptr_struct->local_reason_opcode == 9 ? ("Minor_Error_threshold_exceeded") : ((ptr_struct->local_reason_opcode == 10 ? ("Physical_layer_retransmission_timeout") : ((ptr_struct->local_reason_opcode == 11 ? ("Heartbeat_errors") : ((ptr_struct->local_reason_opcode == 12 ? ("Link_Layer_credit_monitoring_watchdog") : ((ptr_struct->local_reason_opcode == 13 ? ("Link_Layer_integrity_threshold_exceeded") : ((ptr_struct->local_reason_opcode == 14 ? ("Link_Layer_buffer_overrun") : ((ptr_struct->local_reason_opcode == 15 ? ("Down_by_outband_command_with_healthy_link") : ((ptr_struct->local_reason_opcode == 16 ? ("Down_by_outband_command_for_link_with_hi_ber") : ((ptr_struct->local_reason_opcode == 17 ? ("Down_by_inband_command_with_healthy_link") : ((ptr_struct->local_reason_opcode == 18 ? ("Down_by_inband_command_for_link_with_hi_ber") : ((ptr_struct->local_reason_opcode == 19 ? ("Down_by_verification_GW") : ((ptr_struct->local_reason_opcode == 20 ? ("Received_Remote_Fault") : ((ptr_struct->local_reason_opcode == 21 ? ("Received_TS1") : ((ptr_struct->local_reason_opcode == 22 ? ("Down_by_management_command") : ((ptr_struct->local_reason_opcode == 23 ? ("Cable_was_unplugged") : ((ptr_struct->local_reason_opcode == 24 ? ("Cable_access_issue") : ((ptr_struct->local_reason_opcode == 25 ? ("Thermal_shutdown") : ((ptr_struct->local_reason_opcode == 26 ? ("Current_issue") : ((ptr_struct->local_reason_opcode == 27 ? ("Power_budget") : ((ptr_struct->local_reason_opcode == 28 ? ("Fast_recovery_raw_ber") : ((ptr_struct->local_reason_opcode == 29 ? ("Fast_recovery_effective_ber") : ((ptr_struct->local_reason_opcode == 30 ? ("Fast_recovery_symbol_ber") : ((ptr_struct->local_reason_opcode == 31 ? ("Fast_recovery_credit_watchdog") : ((ptr_struct->local_reason_opcode == 32 ? ("Peer_side_down_to_sleep_state") : ((ptr_struct->local_reason_opcode == 33 ? ("Peer_side_down_to_disable_state") : ((ptr_struct->local_reason_opcode == 34 ? ("Peer_side_down_to_disable_and_port_lock") : ((ptr_struct->local_reason_opcode == 35 ? ("Peer_side_down_due_to_thermal_event") : ((ptr_struct->local_reason_opcode == 36 ? ("Peer_side_down_due_to_force_event") : ((ptr_struct->local_reason_opcode == 37 ? ("Peer_side_down_due_to_reset_event") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->local_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "remote_reason_opcode : " UH_FMT "\n", ptr_struct->remote_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e2e_reason_opcode    : " UH_FMT "\n", ptr_struct->e2e_reason_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts1_opcode           : " UH_FMT "\n", ptr_struct->ts1_opcode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_est_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->min_est_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "min_est_eff_ber_coef : " UH_FMT "\n", ptr_struct->min_est_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mean_est_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->mean_est_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mean_est_eff_ber_coef : " UH_FMT "\n", ptr_struct->mean_est_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_est_eff_ber_magnitude : " UH_FMT "\n", ptr_struct->max_est_eff_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_est_eff_ber_coef : " UH_FMT "\n", ptr_struct->max_est_eff_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_est_eff_ber_alarms : " UH_FMT "\n", ptr_struct->num_of_est_eff_ber_alarms);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_est_eff_ber_warnings : " UH_FMT "\n", ptr_struct->num_of_est_eff_ber_warnings);
}

unsigned int reg_access_gpu_pddr_link_down_info_page_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_LINK_DOWN_INFO_PAGE_EXT_SIZE;
}

void reg_access_gpu_pddr_link_down_info_page_ext_dump(const struct reg_access_gpu_pddr_link_down_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_link_down_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_module_info_ext_pack(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, u_int8_t *ptr_buff)
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
		offset = adb2c_calc_array_field_address(160, 32, i, 1728, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_name[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 1728, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_pn[i]);
	}
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vendor_rev);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fw_version);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(480, 32, i, 1728, 1);
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
	offset = 1240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_compliance_code);
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
		offset = adb2c_calc_array_field_address(1308, 4, i, 1728, 1);
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
	offset = 1564;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_code);
	offset = 1536;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_fiber_length);
}

void reg_access_gpu_pddr_module_info_ext_unpack(struct reg_access_gpu_pddr_module_info_ext *ptr_struct, const u_int8_t *ptr_buff)
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
		offset = adb2c_calc_array_field_address(160, 32, i, 1728, 1);
		ptr_struct->vendor_name[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(288, 32, i, 1728, 1);
		ptr_struct->vendor_pn[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 416;
	ptr_struct->vendor_rev = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->fw_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(480, 32, i, 1728, 1);
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
	offset = 1240;
	ptr_struct->ib_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
		offset = adb2c_calc_array_field_address(1308, 4, i, 1728, 1);
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
	ptr_struct->date_code = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
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
	offset = 1564;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 1536;
	ptr_struct->max_fiber_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_module_info_ext_print(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_module_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ext_ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_breakout       : " UH_FMT "\n", ptr_struct->cable_breakout);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_technology     : " UH_FMT "\n", ptr_struct->cable_technology);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_power_class    : " UH_FMT "\n", ptr_struct->cable_power_class);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_identifier     : " UH_FMT "\n", ptr_struct->cable_identifier);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_length         : " UH_FMT "\n", ptr_struct->cable_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_vendor         : %s (" UH_FMT ")\n", (ptr_struct->cable_vendor == 0 ? ("Other") : ((ptr_struct->cable_vendor == 1 ? ("Mellanox") : ((ptr_struct->cable_vendor == 2 ? ("Known_OUI") : ((ptr_struct->cable_vendor == 3 ? ("NVIDIA") : ("unknown")))))))), ptr_struct->cable_vendor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_type           : %s (" UH_FMT ")\n", (ptr_struct->cable_type == 0 ? ("Unidentified") : ((ptr_struct->cable_type == 1 ? ("Active_cable") : ((ptr_struct->cable_type == 2 ? ("Optical_Module") : ((ptr_struct->cable_type == 3 ? ("Passive_copper_cable") : ((ptr_struct->cable_type == 4 ? ("Cable_unplugged") : ((ptr_struct->cable_type == 5 ? ("Twisted_pair") : ("unknown")))))))))))), ptr_struct->cable_type);
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
	fprintf(fd, "ib_compliance_code   : " UH_FMT "\n", ptr_struct->ib_compliance_code);
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
	fprintf(fd, "tx_input_freq_sync   : %s (" UH_FMT ")\n", (ptr_struct->tx_input_freq_sync == 0 ? ("Tx_input_lanes_1_8") : ((ptr_struct->tx_input_freq_sync == 1 ? ("Tx_input_lanes_1_4_and_5") : ((ptr_struct->tx_input_freq_sync == 2 ? ("Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8") : ((ptr_struct->tx_input_freq_sync == 3 ? ("Lanes_may_be_asynchronous_in_frequency") : ("unknown")))))))), ptr_struct->tx_input_freq_sync);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code           : %s (" UH_FMT ")\n", (ptr_struct->error_code == 0 ? ("ConfigUndefined") : ((ptr_struct->error_code == 1 ? ("ConfigSuccess") : ((ptr_struct->error_code == 2 ? ("ConfigRejected") : ((ptr_struct->error_code == 3 ? ("ConfigRejectedInvalidAppSel") : ((ptr_struct->error_code == 4 ? ("ConfigRejectedInvalidDataPath") : ((ptr_struct->error_code == 5 ? ("ConfigRejectedInvalidSI") : ((ptr_struct->error_code == 6 ? ("ConfigRejectedLanesInUse") : ((ptr_struct->error_code == 7 ? ("ConfigRejectedPartialDataPath") : ((ptr_struct->error_code == 12 ? ("ConfigInProgress") : ("unknown")))))))))))))))))), ptr_struct->error_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_fiber_length     : " UH_FMT "\n", ptr_struct->max_fiber_length);
}

unsigned int reg_access_gpu_pddr_module_info_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_MODULE_INFO_EXT_SIZE;
}

void reg_access_gpu_pddr_module_info_ext_dump(const struct reg_access_gpu_pddr_module_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_module_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_operation_info_page_ext_pack(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->neg_mode_active);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->proto_active);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ib_phy_fsm_state);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->eth_an_fsm_state);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phy_mngr_fsm_state);
	offset = 64;
	reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_pack(&(ptr_struct->phy_manager_link_enabled), ptr_buff + offset / 8);
	offset = 96;
	reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_pack(&(ptr_struct->core_to_phy_link_enabled), ptr_buff + offset / 8);
	offset = 128;
	reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_pack(&(ptr_struct->cable_proto_cap), ptr_buff + offset / 8);
	offset = 160;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 160;
		reg_access_gpu_pddr_link_active_eth_ext_pack(&(ptr_struct->link_active.pddr_link_active_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 160;
		reg_access_gpu_pddr_link_active_ib_ext_pack(&(ptr_struct->link_active.pddr_link_active_ib_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->loopback_mode);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_mode_request);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_mode_active);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_100g_fec_support);
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_25g_50g_fec_support);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_an_link_enabled);
}

void reg_access_gpu_pddr_operation_info_page_ext_unpack(struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 12;
	ptr_struct->neg_mode_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->proto_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->ib_phy_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->eth_an_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->phy_mngr_fsm_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_unpack(&(ptr_struct->phy_manager_link_enabled), ptr_buff + offset / 8);
	offset = 96;
	reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_unpack(&(ptr_struct->core_to_phy_link_enabled), ptr_buff + offset / 8);
	offset = 128;
	reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_unpack(&(ptr_struct->cable_proto_cap), ptr_buff + offset / 8);
	offset = 160;
	switch (ptr_struct->proto_active) {
	case 0x4:
		offset = 160;
		reg_access_gpu_pddr_link_active_eth_ext_unpack(&(ptr_struct->link_active.pddr_link_active_eth_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 160;
		reg_access_gpu_pddr_link_active_ib_ext_unpack(&(ptr_struct->link_active.pddr_link_active_ib_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 212;
	ptr_struct->loopback_mode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 240;
	ptr_struct->fec_mode_request = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->fec_mode_active = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 284;
	ptr_struct->eth_100g_fec_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 280;
	ptr_struct->eth_25g_50g_fec_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->eth_an_link_enabled = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pddr_operation_info_page_ext_print(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_operation_info_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "neg_mode_active      : %s (" UH_FMT ")\n", (ptr_struct->neg_mode_active == 0 ? ("protocol_was_not_negotiated") : ((ptr_struct->neg_mode_active == 1 ? ("MLPN_rev0_negotiated") : ((ptr_struct->neg_mode_active == 2 ? ("CL73_Ethernet_negotiated") : ((ptr_struct->neg_mode_active == 3 ? ("Protocol_according_to_Parallel_detect") : ((ptr_struct->neg_mode_active == 4 ? ("Standard_IB_negotiated") : ((ptr_struct->neg_mode_active == 8 ? ("NLPN_rev2_negotiated") : ((ptr_struct->neg_mode_active == 9 ? ("HS_NLPN_rev2_negotiated_") : ("unknown")))))))))))))), ptr_struct->neg_mode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "proto_active         : %s (" UH_FMT ")\n", (ptr_struct->proto_active == 1 ? ("InfiniBand") : ((ptr_struct->proto_active == 4 ? ("Ethernet") : ((ptr_struct->proto_active == 8 ? ("NVLink") : ("unknown")))))), ptr_struct->proto_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_phy_fsm_state     : %s (" UH_FMT ")\n", (ptr_struct->ib_phy_fsm_state == 0 ? ("IB_AN_FSM_DISABLED") : ((ptr_struct->ib_phy_fsm_state == 1 ? ("IB_AN_FSM_INITIALY") : ((ptr_struct->ib_phy_fsm_state == 2 ? ("IB_AN_FSM_RCVR_CFG") : ((ptr_struct->ib_phy_fsm_state == 3 ? ("IB_AN_FSM_CFG_TEST") : ((ptr_struct->ib_phy_fsm_state == 4 ? ("IB_AN_FSM_WAIT_RMT_TEST") : ((ptr_struct->ib_phy_fsm_state == 5 ? ("IB_AN_FSM_WAIT_CFG_ENHANCED") : ((ptr_struct->ib_phy_fsm_state == 6 ? ("IB_AN_FSM_CFG_IDLE") : ((ptr_struct->ib_phy_fsm_state == 7 ? ("IB_AN_FSM_LINK_UP") : ((ptr_struct->ib_phy_fsm_state == 8 ? ("IB_AN_FSM_POLLING") : ("unknown")))))))))))))))))), ptr_struct->ib_phy_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_fsm_state     : " UH_FMT "\n", ptr_struct->eth_an_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_mngr_fsm_state   : %s (" UH_FMT ")\n", (ptr_struct->phy_mngr_fsm_state == 0 ? ("Disabled") : ((ptr_struct->phy_mngr_fsm_state == 1 ? ("Open_port") : ((ptr_struct->phy_mngr_fsm_state == 2 ? ("Polling") : ((ptr_struct->phy_mngr_fsm_state == 3 ? ("Active") : ((ptr_struct->phy_mngr_fsm_state == 4 ? ("Close_port") : ((ptr_struct->phy_mngr_fsm_state == 5 ? ("Phy_up") : ((ptr_struct->phy_mngr_fsm_state == 6 ? ("Sleep") : ((ptr_struct->phy_mngr_fsm_state == 7 ? ("Rx_disable") : ((ptr_struct->phy_mngr_fsm_state == 8 ? ("Signal_detect") : ((ptr_struct->phy_mngr_fsm_state == 9 ? ("Receiver_detect") : ((ptr_struct->phy_mngr_fsm_state == 10 ? ("Sync_peer") : ((ptr_struct->phy_mngr_fsm_state == 11 ? ("Negotiation") : ((ptr_struct->phy_mngr_fsm_state == 12 ? ("Training") : ((ptr_struct->phy_mngr_fsm_state == 13 ? ("SubFSM_active") : ("unknown")))))))))))))))))))))))))))), ptr_struct->phy_mngr_fsm_state);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_manager_link_enabled:\n");
	reg_access_gpu_pddr_operation_info_page_phy_manager_link_enabled_auto_ext_print(&(ptr_struct->phy_manager_link_enabled), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "core_to_phy_link_enabled:\n");
	reg_access_gpu_pddr_operation_info_page_core_to_phy_link_enabled_auto_ext_print(&(ptr_struct->core_to_phy_link_enabled), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_proto_cap:\n");
	reg_access_gpu_pddr_operation_info_page_cable_proto_cap_auto_ext_print(&(ptr_struct->cable_proto_cap), fd, indent_level + 1);
	switch (ptr_struct->proto_active) {
	case 0x4:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_active_eth_ext:\n");
		reg_access_gpu_pddr_link_active_eth_ext_print(&(ptr_struct->link_active.pddr_link_active_eth_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_active_ib_ext:\n");
		reg_access_gpu_pddr_link_active_ib_ext_print(&(ptr_struct->link_active.pddr_link_active_ib_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "loopback_mode        : %s (" UH_FMT ")\n", (ptr_struct->loopback_mode == 0 ? ("No_loopback_active") : ((ptr_struct->loopback_mode == 1 ? ("Phy_remote_loopback") : ((ptr_struct->loopback_mode == 2 ? ("Phy_local_loopback") : ((ptr_struct->loopback_mode == 4 ? ("External_local_loopback") : ("unknown")))))))), ptr_struct->loopback_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_mode_request     : " UH_FMT "\n", ptr_struct->fec_mode_request);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_mode_active      : %s (" UH_FMT ")\n", (ptr_struct->fec_mode_active == 0 ? ("No_FEC") : ((ptr_struct->fec_mode_active == 1 ? ("Firecode_FEC") : ((ptr_struct->fec_mode_active == 2 ? ("Standard_RS_FEC") : ((ptr_struct->fec_mode_active == 3 ? ("Standard_LL_RS_FEC") : ((ptr_struct->fec_mode_active == 6 ? ("Interleaved_Standard_RS") : ((ptr_struct->fec_mode_active == 7 ? ("Standard_RS") : ((ptr_struct->fec_mode_active == 9 ? ("Ethernet_Consortium_LL_50G_RS_FEC") : ((ptr_struct->fec_mode_active == 10 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC") : ("unknown")))))))))))))))), ptr_struct->fec_mode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_100g_fec_support : " UH_FMT "\n", ptr_struct->eth_100g_fec_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_25g_50g_fec_support : " UH_FMT "\n", ptr_struct->eth_25g_50g_fec_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_an_link_enabled  : " U32H_FMT "\n", ptr_struct->eth_an_link_enabled);
}

unsigned int reg_access_gpu_pddr_operation_info_page_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_OPERATION_INFO_PAGE_EXT_SIZE;
}

void reg_access_gpu_pddr_operation_info_page_ext_dump(const struct reg_access_gpu_pddr_operation_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_operation_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_phy_info_page_ext_pack(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 840;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->plr_outstanding_cells);
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
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_ndr_threshold);
	offset = 1216;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_hdr_threshold);
	offset = 1248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->plr_rtt_xdr_threshold);
}

void reg_access_gpu_pddr_phy_info_page_ext_unpack(struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 840;
	ptr_struct->plr_outstanding_cells = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
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
	ptr_struct->plr_rtt_ndr_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1216;
	ptr_struct->plr_rtt_hdr_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 1248;
	ptr_struct->plr_rtt_xdr_threshold = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pddr_phy_info_page_ext_print(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_phy_info_page_ext ========\n");

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
	fprintf(fd, "hw_link_phy_state    : %s (" UH_FMT ")\n", (ptr_struct->hw_link_phy_state == 16 ? ("sleeping_delay") : ((ptr_struct->hw_link_phy_state == 17 ? ("sleeping_quiet") : ((ptr_struct->hw_link_phy_state == 32 ? ("polling_active") : ((ptr_struct->hw_link_phy_state == 33 ? ("polling_quiet") : ((ptr_struct->hw_link_phy_state == 48 ? ("disable") : ((ptr_struct->hw_link_phy_state == 64 ? ("config_debounce") : ((ptr_struct->hw_link_phy_state == 65 ? ("config_receiver") : ((ptr_struct->hw_link_phy_state == 66 ? ("config_wait_remote") : ((ptr_struct->hw_link_phy_state == 67 ? ("config_tx_reverse_lanes") : ((ptr_struct->hw_link_phy_state == 68 ? ("config_enhanced") : ((ptr_struct->hw_link_phy_state == 69 ? ("config_test") : ((ptr_struct->hw_link_phy_state == 70 ? ("confg_wait_remote_test") : ((ptr_struct->hw_link_phy_state == 71 ? ("config_wait_cfg_enhanced") : ((ptr_struct->hw_link_phy_state == 72 ? ("config_idle") : ((ptr_struct->hw_link_phy_state == 80 ? ("linkup") : ((ptr_struct->hw_link_phy_state == 81 ? ("Linkup_Tx_Idle") : ((ptr_struct->hw_link_phy_state == 82 ? ("Linkup_Tx_Empty") : ((ptr_struct->hw_link_phy_state == 96 ? ("recover_retrain") : ((ptr_struct->hw_link_phy_state == 97 ? ("recover_wait_remote") : ((ptr_struct->hw_link_phy_state == 98 ? ("recover_idle") : ((ptr_struct->hw_link_phy_state == 112 ? ("test") : ((ptr_struct->hw_link_phy_state == 128 ? ("Force_send_ts1") : ((ptr_struct->hw_link_phy_state == 144 ? ("Force_send_ts2") : ((ptr_struct->hw_link_phy_state == 160 ? ("Force_Sent_Idle") : ((ptr_struct->hw_link_phy_state == 176 ? ("Force_send_ts_Mlnx") : ((ptr_struct->hw_link_phy_state == 192 ? ("Force_send_ts3") : ((ptr_struct->hw_link_phy_state == 208 ? ("Force_LinkUp") : ((ptr_struct->hw_link_phy_state == 224 ? ("Go_To_Quiet") : ((ptr_struct->hw_link_phy_state == 225 ? ("Retimer_Align") : ((ptr_struct->hw_link_phy_state == 226 ? ("Quiet_Entry") : ((ptr_struct->hw_link_phy_state == 227 ? ("Quiet") : ((ptr_struct->hw_link_phy_state == 228 ? ("Wake") : ((ptr_struct->hw_link_phy_state == 229 ? ("Wake_Tx_Sleep0") : ((ptr_struct->hw_link_phy_state == 230 ? ("Send_Announce") : ((ptr_struct->hw_link_phy_state == 231 ? ("Tx_HS") : ((ptr_struct->hw_link_phy_state == 232 ? ("Wait_For_Cdr_Lock") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->hw_link_phy_state);
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
	fprintf(fd, "kr_startup_debug_indications_4 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_7 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_6 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_6);
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
	fprintf(fd, "kr_startup_debug_indications_0 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_3 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "kr_startup_debug_indications_2 : " UH_FMT "\n", ptr_struct->kr_startup_debug_indications_2);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "tx_tuning_stages_lane_%03d : " UH_FMT "\n", i, ptr_struct->tx_tuning_stages_lane[i]);
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
	fprintf(fd, "plr_outstanding_cells : " UH_FMT "\n", ptr_struct->plr_outstanding_cells);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signal_detected      : " UH_FMT "\n", ptr_struct->signal_detected);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stamping_reason      : " U32H_FMT "\n", ptr_struct->stamping_reason);
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
	fprintf(fd, "plr_rtt_ndr_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_ndr_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_hdr_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_hdr_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rtt_xdr_threshold : " UH_FMT "\n", ptr_struct->plr_rtt_xdr_threshold);
}

unsigned int reg_access_gpu_pddr_phy_info_page_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_PHY_INFO_PAGE_EXT_SIZE;
}

void reg_access_gpu_pddr_phy_info_page_ext_dump(const struct reg_access_gpu_pddr_phy_info_page_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_phy_info_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_troubleshooting_page_ext_pack(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->group_opcode);
	offset = 32;
	switch (ptr_struct->group_opcode) {
	case 0x0:
		offset = 32;
		reg_access_gpu_pddr_monitor_opcode_ext_pack(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 1984, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status_message[i]);
	}
}

void reg_access_gpu_pddr_troubleshooting_page_ext_unpack(struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 16;
	ptr_struct->group_opcode = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	switch (ptr_struct->group_opcode) {
	case 0x0:
		offset = 32;
		reg_access_gpu_pddr_monitor_opcode_ext_unpack(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		offset = adb2c_calc_array_field_address(96, 32, i, 1984, 1);
		ptr_struct->status_message[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_pddr_troubleshooting_page_ext_print(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_troubleshooting_page_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "group_opcode         : %s (" UH_FMT ")\n", (ptr_struct->group_opcode == 0 ? ("Monitor_opcodes") : ("unknown")), ptr_struct->group_opcode);
	switch (ptr_struct->group_opcode) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_monitor_opcode_ext:\n");
		reg_access_gpu_pddr_monitor_opcode_ext_print(&(ptr_struct->status_opcode.pddr_monitor_opcode_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	for (i = 0; i < 59; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "status_message_%03d  : " U32H_FMT "\n", i, ptr_struct->status_message[i]);
	}
}

unsigned int reg_access_gpu_pddr_troubleshooting_page_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_TROUBLESHOOTING_PAGE_EXT_SIZE;
}

void reg_access_gpu_pddr_troubleshooting_page_ext_dump(const struct reg_access_gpu_pddr_troubleshooting_page_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_troubleshooting_page_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_phys_layer_cntrs_ext_pack(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->symbol_errors_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->symbol_errors_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sync_headers_errors_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sync_headers_errors_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane0_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane0_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane1_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane1_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane2_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane2_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane3_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->edpl_bip_errors_lane3_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane0_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane0_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane1_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane1_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane2_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane2_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane3_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_corrected_blocks_lane3_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane0_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane0_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane1_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane1_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane2_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane2_low);
	offset = 896;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane3_high);
	offset = 928;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fc_fec_uncorrectable_blocks_lane3_low);
	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_blocks_high);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_blocks_low);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_uncorrectable_blocks_high);
	offset = 1056;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_uncorrectable_blocks_low);
	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_no_errors_blocks_high);
	offset = 1120;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_no_errors_blocks_low);
	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_total_high);
	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_total_low);
	offset = 1280;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane0_high);
	offset = 1312;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane0_low);
	offset = 1344;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane1_high);
	offset = 1376;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane1_low);
	offset = 1408;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane2_high);
	offset = 1440;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane2_low);
	offset = 1472;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane3_high);
	offset = 1504;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane3_low);
	offset = 1536;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->link_down_events);
	offset = 1568;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->successful_recovery_events);
	offset = 1600;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane4_high);
	offset = 1632;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane4_low);
	offset = 1664;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane5_high);
	offset = 1696;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane5_low);
	offset = 1728;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane6_high);
	offset = 1760;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane6_low);
	offset = 1792;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane7_high);
	offset = 1824;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_corrected_symbols_lane7_low);
}

void reg_access_gpu_phys_layer_cntrs_ext_unpack(struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->time_since_last_clear_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->time_since_last_clear_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->symbol_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->symbol_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->sync_headers_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->sync_headers_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->edpl_bip_errors_lane0_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->edpl_bip_errors_lane0_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->edpl_bip_errors_lane1_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->edpl_bip_errors_lane1_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->edpl_bip_errors_lane2_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->edpl_bip_errors_lane2_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->edpl_bip_errors_lane3_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->edpl_bip_errors_lane3_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->fc_fec_corrected_blocks_lane0_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->fc_fec_corrected_blocks_lane0_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->fc_fec_corrected_blocks_lane1_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->fc_fec_corrected_blocks_lane1_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->fc_fec_corrected_blocks_lane2_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->fc_fec_corrected_blocks_lane2_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->fc_fec_corrected_blocks_lane3_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->fc_fec_corrected_blocks_lane3_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->fc_fec_uncorrectable_blocks_lane0_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->fc_fec_uncorrectable_blocks_lane0_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->fc_fec_uncorrectable_blocks_lane1_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->fc_fec_uncorrectable_blocks_lane1_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->fc_fec_uncorrectable_blocks_lane2_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->fc_fec_uncorrectable_blocks_lane2_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 896;
	ptr_struct->fc_fec_uncorrectable_blocks_lane3_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 928;
	ptr_struct->fc_fec_uncorrectable_blocks_lane3_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 960;
	ptr_struct->rs_fec_corrected_blocks_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 992;
	ptr_struct->rs_fec_corrected_blocks_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->rs_fec_uncorrectable_blocks_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1056;
	ptr_struct->rs_fec_uncorrectable_blocks_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1088;
	ptr_struct->rs_fec_no_errors_blocks_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1120;
	ptr_struct->rs_fec_no_errors_blocks_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1216;
	ptr_struct->rs_fec_corrected_symbols_total_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1248;
	ptr_struct->rs_fec_corrected_symbols_total_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1280;
	ptr_struct->rs_fec_corrected_symbols_lane0_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1312;
	ptr_struct->rs_fec_corrected_symbols_lane0_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1344;
	ptr_struct->rs_fec_corrected_symbols_lane1_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1376;
	ptr_struct->rs_fec_corrected_symbols_lane1_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1408;
	ptr_struct->rs_fec_corrected_symbols_lane2_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1440;
	ptr_struct->rs_fec_corrected_symbols_lane2_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1472;
	ptr_struct->rs_fec_corrected_symbols_lane3_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1504;
	ptr_struct->rs_fec_corrected_symbols_lane3_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1536;
	ptr_struct->link_down_events = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1568;
	ptr_struct->successful_recovery_events = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1600;
	ptr_struct->rs_fec_corrected_symbols_lane4_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1632;
	ptr_struct->rs_fec_corrected_symbols_lane4_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1664;
	ptr_struct->rs_fec_corrected_symbols_lane5_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1696;
	ptr_struct->rs_fec_corrected_symbols_lane5_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1728;
	ptr_struct->rs_fec_corrected_symbols_lane6_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1760;
	ptr_struct->rs_fec_corrected_symbols_lane6_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1792;
	ptr_struct->rs_fec_corrected_symbols_lane7_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1824;
	ptr_struct->rs_fec_corrected_symbols_lane7_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_phys_layer_cntrs_ext_print(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_phys_layer_cntrs_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_high : " U32H_FMT "\n", ptr_struct->time_since_last_clear_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_low : " U32H_FMT "\n", ptr_struct->time_since_last_clear_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_errors_high   : " U32H_FMT "\n", ptr_struct->symbol_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_errors_low    : " U32H_FMT "\n", ptr_struct->symbol_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_headers_errors_high : " U32H_FMT "\n", ptr_struct->sync_headers_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_headers_errors_low : " U32H_FMT "\n", ptr_struct->sync_headers_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane0_high : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane0_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane0_low : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane0_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane1_high : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane1_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane1_low : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane1_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane2_high : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane2_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane2_low : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane2_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane3_high : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane3_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "edpl_bip_errors_lane3_low : " U32H_FMT "\n", ptr_struct->edpl_bip_errors_lane3_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane0_high : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane0_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane0_low : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane0_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane1_high : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane1_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane1_low : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane1_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane2_high : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane2_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane2_low : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane2_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane3_high : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane3_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_corrected_blocks_lane3_low : " U32H_FMT "\n", ptr_struct->fc_fec_corrected_blocks_lane3_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane0_high : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane0_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane0_low : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane0_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane1_high : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane1_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane1_low : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane1_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane2_high : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane2_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane2_low : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane2_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane3_high : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane3_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_fec_uncorrectable_blocks_lane3_low : " U32H_FMT "\n", ptr_struct->fc_fec_uncorrectable_blocks_lane3_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_blocks_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_blocks_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_blocks_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_blocks_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_uncorrectable_blocks_high : " U32H_FMT "\n", ptr_struct->rs_fec_uncorrectable_blocks_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_uncorrectable_blocks_low : " U32H_FMT "\n", ptr_struct->rs_fec_uncorrectable_blocks_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_no_errors_blocks_high : " U32H_FMT "\n", ptr_struct->rs_fec_no_errors_blocks_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_no_errors_blocks_low : " U32H_FMT "\n", ptr_struct->rs_fec_no_errors_blocks_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_total_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_total_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_total_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_total_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane0_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane0_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane0_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane0_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane1_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane1_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane1_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane1_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane2_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane2_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane2_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane2_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane3_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane3_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane3_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane3_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "link_down_events     : " U32H_FMT "\n", ptr_struct->link_down_events);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "successful_recovery_events : " U32H_FMT "\n", ptr_struct->successful_recovery_events);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane4_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane4_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane4_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane4_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane5_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane5_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane5_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane5_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane6_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane6_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane6_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane6_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane7_high : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane7_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_corrected_symbols_lane7_low : " U32H_FMT "\n", ptr_struct->rs_fec_corrected_symbols_lane7_low);
}

unsigned int reg_access_gpu_phys_layer_cntrs_ext_size(void)
{
	return REG_ACCESS_GPU_PHYS_LAYER_CNTRS_EXT_SIZE;
}

void reg_access_gpu_phys_layer_cntrs_ext_dump(const struct reg_access_gpu_phys_layer_cntrs_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_phys_layer_cntrs_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_phys_layer_stat_cntrs_ext_pack(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_received_bits_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_received_bits_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_symbol_errors_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_symbol_errors_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_corrected_bits_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_corrected_bits_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane0_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane0_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane1_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane1_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane2_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane2_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane3_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane3_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane4_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane4_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane5_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane5_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane6_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane6_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane7_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_raw_errors_lane7_low);
	offset = 796;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->raw_ber_coef);
	offset = 784;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->raw_ber_magnitude);
	offset = 774;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->fc_zero_hist);
	offset = 828;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->effective_ber_coef);
	offset = 816;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->effective_ber_magnitude);
	offset = 812;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->estimated_effective_ber_coef);
	offset = 808;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->estimated_effective_ber_coef_float);
	offset = 800;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->estimated_effective_ber_magnitude);
	offset = 860;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->symbol_ber_coef);
	offset = 848;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->symbol_ber_magnitude);
	offset = 992;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_effective_errors_high);
	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_effective_errors_low);
}

void reg_access_gpu_phys_layer_stat_cntrs_ext_unpack(struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->time_since_last_clear_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->time_since_last_clear_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->phy_received_bits_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->phy_received_bits_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->phy_symbol_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->phy_symbol_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->phy_corrected_bits_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->phy_corrected_bits_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->phy_raw_errors_lane0_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->phy_raw_errors_lane0_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->phy_raw_errors_lane1_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->phy_raw_errors_lane1_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->phy_raw_errors_lane2_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->phy_raw_errors_lane2_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->phy_raw_errors_lane3_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->phy_raw_errors_lane3_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->phy_raw_errors_lane4_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->phy_raw_errors_lane4_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->phy_raw_errors_lane5_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->phy_raw_errors_lane5_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->phy_raw_errors_lane6_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->phy_raw_errors_lane6_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->phy_raw_errors_lane7_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->phy_raw_errors_lane7_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 796;
	ptr_struct->raw_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 784;
	ptr_struct->raw_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 774;
	ptr_struct->fc_zero_hist = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 828;
	ptr_struct->effective_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 816;
	ptr_struct->effective_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 812;
	ptr_struct->estimated_effective_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 808;
	ptr_struct->estimated_effective_ber_coef_float = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->estimated_effective_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 860;
	ptr_struct->symbol_ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 848;
	ptr_struct->symbol_ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 992;
	ptr_struct->phy_effective_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 1024;
	ptr_struct->phy_effective_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_phys_layer_stat_cntrs_ext_print(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_phys_layer_stat_cntrs_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_high : " U32H_FMT "\n", ptr_struct->time_since_last_clear_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_low : " U32H_FMT "\n", ptr_struct->time_since_last_clear_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_received_bits_high : " U32H_FMT "\n", ptr_struct->phy_received_bits_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_received_bits_low : " U32H_FMT "\n", ptr_struct->phy_received_bits_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_symbol_errors_high : " U32H_FMT "\n", ptr_struct->phy_symbol_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_symbol_errors_low : " U32H_FMT "\n", ptr_struct->phy_symbol_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_corrected_bits_high : " U32H_FMT "\n", ptr_struct->phy_corrected_bits_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_corrected_bits_low : " U32H_FMT "\n", ptr_struct->phy_corrected_bits_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane0_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane0_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane0_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane0_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane1_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane1_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane1_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane1_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane2_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane2_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane2_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane2_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane3_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane3_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane3_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane3_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane4_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane4_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane4_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane4_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane5_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane5_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane5_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane5_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane6_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane6_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane6_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane6_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane7_high : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane7_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_raw_errors_lane7_low : " U32H_FMT "\n", ptr_struct->phy_raw_errors_lane7_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_coef         : " UH_FMT "\n", ptr_struct->raw_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "raw_ber_magnitude    : " UH_FMT "\n", ptr_struct->raw_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fc_zero_hist         : " UH_FMT "\n", ptr_struct->fc_zero_hist);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "effective_ber_coef   : " UH_FMT "\n", ptr_struct->effective_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "effective_ber_magnitude : " UH_FMT "\n", ptr_struct->effective_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "estimated_effective_ber_coef : " UH_FMT "\n", ptr_struct->estimated_effective_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "estimated_effective_ber_coef_float : " UH_FMT "\n", ptr_struct->estimated_effective_ber_coef_float);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "estimated_effective_ber_magnitude : " UH_FMT "\n", ptr_struct->estimated_effective_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_ber_coef      : " UH_FMT "\n", ptr_struct->symbol_ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "symbol_ber_magnitude : " UH_FMT "\n", ptr_struct->symbol_ber_magnitude);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_effective_errors_high : " U32H_FMT "\n", ptr_struct->phy_effective_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_effective_errors_low : " U32H_FMT "\n", ptr_struct->phy_effective_errors_low);
}

unsigned int reg_access_gpu_phys_layer_stat_cntrs_ext_size(void)
{
	return REG_ACCESS_GPU_PHYS_LAYER_STAT_CNTRS_EXT_SIZE;
}

void reg_access_gpu_phys_layer_stat_cntrs_ext_dump(const struct reg_access_gpu_phys_layer_stat_cntrs_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_phys_layer_stat_cntrs_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_pack(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->host_electrical_compliance);
	offset = 11;
	adb2c_push_bits_to_buff(ptr_buff, offset, 13, (u_int32_t)ptr_struct->cable_breakout);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->media_type_encoding);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mod_pwrup_maxduration);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->media_compliance);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module_media_type);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dp_tx_off_maxduration);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dp_tx_on_maxduration);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dp_init_maxduration);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->cmis_override_mask);
}

void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_unpack(struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->host_electrical_compliance = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 11;
	ptr_struct->cable_breakout = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 13);
	offset = 7;
	ptr_struct->media_type_encoding = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->mod_pwrup_maxduration = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->media_compliance = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->module_media_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 44;
	ptr_struct->dp_tx_off_maxduration = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->dp_tx_on_maxduration = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->dp_init_maxduration = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->cmis_override_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_print(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_cmis_protocol_override_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_electrical_compliance : " UH_FMT "\n", ptr_struct->host_electrical_compliance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_breakout       : " UH_FMT "\n", ptr_struct->cable_breakout);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "media_type_encoding  : " UH_FMT "\n", ptr_struct->media_type_encoding);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mod_pwrup_maxduration : " UH_FMT "\n", ptr_struct->mod_pwrup_maxduration);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "media_compliance     : " UH_FMT "\n", ptr_struct->media_compliance);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_media_type    : " UH_FMT "\n", ptr_struct->module_media_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dp_tx_off_maxduration : " UH_FMT "\n", ptr_struct->dp_tx_off_maxduration);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dp_tx_on_maxduration : " UH_FMT "\n", ptr_struct->dp_tx_on_maxduration);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dp_init_maxduration  : " UH_FMT "\n", ptr_struct->dp_init_maxduration);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cmis_override_mask   : " UH_FMT "\n", ptr_struct->cmis_override_mask);
}

unsigned int reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_CMIS_PROTOCOL_OVERRIDE_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_dump(const struct reg_access_gpu_pmmp_cmis_protocol_override_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_pack(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ethernet_compliance_code);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_breakout);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->giga_ethernet_compliance_code);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ext_ethernet_compliance_code);
}

void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_unpack(struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->cable_breakout = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->giga_ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ext_ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_print(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_breakout       : " UH_FMT "\n", ptr_struct->cable_breakout);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "giga_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->giga_ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ext_ethernet_compliance_code);
}

unsigned int reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_QSFP_PROTOCOL_OVERRIDE_LAYOUT_EXT_SIZE;
}

void reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_dump(const struct reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_pack(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tengig_ethernet_compliance_code);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_technology);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bit_rate);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ethernet_compliance_code);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ext_ethernet_compliance_code);
}

void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_unpack(struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->tengig_ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->cable_technology = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->bit_rate = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ext_ethernet_compliance_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_print(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tengig_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->tengig_ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_technology     : " UH_FMT "\n", ptr_struct->cable_technology);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bit_rate             : " UH_FMT "\n", ptr_struct->bit_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ethernet_compliance_code);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_ethernet_compliance_code : " UH_FMT "\n", ptr_struct->ext_ethernet_compliance_code);
}

unsigned int reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_SFP_PROTOCOL_BYTES_OVERRIDE_EXT_SIZE;
}

void reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_dump(const struct reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_infiniband_general_counter_ext_pack(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rq_general_error_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rq_general_error_low);
}

void reg_access_gpu_ppcnt_infiniband_general_counter_ext_unpack(struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 128;
	ptr_struct->rq_general_error_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->rq_general_error_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_ppcnt_infiniband_general_counter_ext_print(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_infiniband_general_counter_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rq_general_error_high : " U32H_FMT "\n", ptr_struct->rq_general_error_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rq_general_error_low : " U32H_FMT "\n", ptr_struct->rq_general_error_low);
}

unsigned int reg_access_gpu_ppcnt_infiniband_general_counter_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_INFINIBAND_GENERAL_COUNTER_EXT_SIZE;
}

void reg_access_gpu_ppcnt_infiniband_general_counter_ext_dump(const struct reg_access_gpu_ppcnt_infiniband_general_counter_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_infiniband_general_counter_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_pack(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->time_since_last_clear_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_xmit_pkts_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_xmit_pkts_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_rcv_pkts_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_unicast_rcv_pkts_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sync_header_error_counter_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sync_header_error_counter_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_local_physical_errors_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_local_physical_errors_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_malformed_packet_errors_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_malformed_packet_errors_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_buffer_overrun_errors_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_buffer_overrun_errors_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_dlid_mapping_errors_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_dlid_mapping_errors_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_vl_mapping_errors_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_vl_mapping_errors_low);
	offset = 576;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_looping_errors_high);
	offset = 608;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_looping_errors_low);
	offset = 640;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_inactive_discards_high);
	offset = 672;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_inactive_discards_low);
	offset = 704;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_neighbor_mtu_discards_high);
	offset = 736;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_neighbor_mtu_discards_low);
	offset = 768;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_llu_rx_icrc_error_high);
	offset = 800;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_llu_rx_icrc_error_low);
	offset = 832;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_tx_parity_error_high);
	offset = 864;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_tx_parity_error_low);
}

void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_unpack(struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->time_since_last_clear_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->time_since_last_clear_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->port_unicast_xmit_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->port_unicast_xmit_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->port_unicast_rcv_pkts_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->port_unicast_rcv_pkts_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->sync_header_error_counter_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->sync_header_error_counter_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->port_local_physical_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->port_local_physical_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->port_malformed_packet_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->port_malformed_packet_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->port_buffer_overrun_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->port_buffer_overrun_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->port_dlid_mapping_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->port_dlid_mapping_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->port_vl_mapping_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->port_vl_mapping_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 576;
	ptr_struct->port_looping_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 608;
	ptr_struct->port_looping_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 640;
	ptr_struct->port_inactive_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 672;
	ptr_struct->port_inactive_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 704;
	ptr_struct->port_neighbor_mtu_discards_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 736;
	ptr_struct->port_neighbor_mtu_discards_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 768;
	ptr_struct->port_llu_rx_icrc_error_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 800;
	ptr_struct->port_llu_rx_icrc_error_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 832;
	ptr_struct->port_tx_parity_error_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 864;
	ptr_struct->port_tx_parity_error_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_print(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_infiniband_packets_counter_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_high : " U32H_FMT "\n", ptr_struct->time_since_last_clear_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "time_since_last_clear_low : " U32H_FMT "\n", ptr_struct->time_since_last_clear_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_xmit_pkts_high : " U32H_FMT "\n", ptr_struct->port_unicast_xmit_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_xmit_pkts_low : " U32H_FMT "\n", ptr_struct->port_unicast_xmit_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_rcv_pkts_high : " U32H_FMT "\n", ptr_struct->port_unicast_rcv_pkts_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_unicast_rcv_pkts_low : " U32H_FMT "\n", ptr_struct->port_unicast_rcv_pkts_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_header_error_counter_high : " U32H_FMT "\n", ptr_struct->sync_header_error_counter_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sync_header_error_counter_low : " U32H_FMT "\n", ptr_struct->sync_header_error_counter_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_local_physical_errors_high : " U32H_FMT "\n", ptr_struct->port_local_physical_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_local_physical_errors_low : " U32H_FMT "\n", ptr_struct->port_local_physical_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_malformed_packet_errors_high : " U32H_FMT "\n", ptr_struct->port_malformed_packet_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_malformed_packet_errors_low : " U32H_FMT "\n", ptr_struct->port_malformed_packet_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_buffer_overrun_errors_high : " U32H_FMT "\n", ptr_struct->port_buffer_overrun_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_buffer_overrun_errors_low : " U32H_FMT "\n", ptr_struct->port_buffer_overrun_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_dlid_mapping_errors_high : " U32H_FMT "\n", ptr_struct->port_dlid_mapping_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_dlid_mapping_errors_low : " U32H_FMT "\n", ptr_struct->port_dlid_mapping_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_vl_mapping_errors_high : " U32H_FMT "\n", ptr_struct->port_vl_mapping_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_vl_mapping_errors_low : " U32H_FMT "\n", ptr_struct->port_vl_mapping_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_looping_errors_high : " U32H_FMT "\n", ptr_struct->port_looping_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_looping_errors_low : " U32H_FMT "\n", ptr_struct->port_looping_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_inactive_discards_high : " U32H_FMT "\n", ptr_struct->port_inactive_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_inactive_discards_low : " U32H_FMT "\n", ptr_struct->port_inactive_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_neighbor_mtu_discards_high : " U32H_FMT "\n", ptr_struct->port_neighbor_mtu_discards_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_neighbor_mtu_discards_low : " U32H_FMT "\n", ptr_struct->port_neighbor_mtu_discards_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_llu_rx_icrc_error_high : " U32H_FMT "\n", ptr_struct->port_llu_rx_icrc_error_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_llu_rx_icrc_error_low : " U32H_FMT "\n", ptr_struct->port_llu_rx_icrc_error_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_tx_parity_error_high : " U32H_FMT "\n", ptr_struct->port_tx_parity_error_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_tx_parity_error_low : " U32H_FMT "\n", ptr_struct->port_tx_parity_error_low);
}

unsigned int reg_access_gpu_ppcnt_infiniband_packets_counter_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_INFINIBAND_PACKETS_COUNTER_EXT_SIZE;
}

void reg_access_gpu_ppcnt_infiniband_packets_counter_ext_dump(const struct reg_access_gpu_ppcnt_infiniband_packets_counter_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_infiniband_packets_counter_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_plr_counters_ext_pack(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_codes_high);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_codes_low);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_code_err_high);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_code_err_low);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_uncorrectable_code_high);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_rcv_uncorrectable_code_low);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_codes_high);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_codes_low);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_codes_high);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_codes_low);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_events_high);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_events_low);
	offset = 384;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_sync_events_high);
	offset = 416;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_sync_events_low);
	offset = 448;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_codes_loss_high);
	offset = 480;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_codes_loss_low);
	offset = 512;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_events_within_t_sec_max_high);
	offset = 544;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plr_xmit_retry_events_within_t_sec_max_low);
}

void reg_access_gpu_ppcnt_plr_counters_ext_unpack(struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->plr_rcv_codes_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->plr_rcv_codes_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->plr_rcv_code_err_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->plr_rcv_code_err_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->plr_rcv_uncorrectable_code_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->plr_rcv_uncorrectable_code_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->plr_xmit_codes_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->plr_xmit_codes_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 256;
	ptr_struct->plr_xmit_retry_codes_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->plr_xmit_retry_codes_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->plr_xmit_retry_events_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->plr_xmit_retry_events_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 384;
	ptr_struct->plr_sync_events_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 416;
	ptr_struct->plr_sync_events_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 448;
	ptr_struct->plr_codes_loss_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 480;
	ptr_struct->plr_codes_loss_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 512;
	ptr_struct->plr_xmit_retry_events_within_t_sec_max_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 544;
	ptr_struct->plr_xmit_retry_events_within_t_sec_max_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_ppcnt_plr_counters_ext_print(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_plr_counters_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_codes_high   : " U32H_FMT "\n", ptr_struct->plr_rcv_codes_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_codes_low    : " U32H_FMT "\n", ptr_struct->plr_rcv_codes_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_code_err_high : " U32H_FMT "\n", ptr_struct->plr_rcv_code_err_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_code_err_low : " U32H_FMT "\n", ptr_struct->plr_rcv_code_err_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_uncorrectable_code_high : " U32H_FMT "\n", ptr_struct->plr_rcv_uncorrectable_code_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_rcv_uncorrectable_code_low : " U32H_FMT "\n", ptr_struct->plr_rcv_uncorrectable_code_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_codes_high  : " U32H_FMT "\n", ptr_struct->plr_xmit_codes_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_codes_low   : " U32H_FMT "\n", ptr_struct->plr_xmit_codes_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_codes_high : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_codes_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_codes_low : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_codes_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_events_high : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_events_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_events_low : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_events_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_sync_events_high : " U32H_FMT "\n", ptr_struct->plr_sync_events_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_sync_events_low  : " U32H_FMT "\n", ptr_struct->plr_sync_events_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_codes_loss_high  : " U32H_FMT "\n", ptr_struct->plr_codes_loss_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_codes_loss_low   : " U32H_FMT "\n", ptr_struct->plr_codes_loss_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_events_within_t_sec_max_high : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_events_within_t_sec_max_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plr_xmit_retry_events_within_t_sec_max_low : " U32H_FMT "\n", ptr_struct->plr_xmit_retry_events_within_t_sec_max_low);
}

unsigned int reg_access_gpu_ppcnt_plr_counters_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_PLR_COUNTERS_EXT_SIZE;
}

void reg_access_gpu_ppcnt_plr_counters_ext_dump(const struct reg_access_gpu_ppcnt_plr_counters_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_plr_counters_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_pack(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 21; ++i) {
		offset = adb2c_calc_array_field_address(0, 64, i, 1984, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->hist[i]);
	}
}

void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_unpack(struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 21; ++i) {
		offset = adb2c_calc_array_field_address(0, 64, i, 1984, 1);
		ptr_struct->hist[i] = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_print(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext ========\n");

	for (i = 0; i < 21; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "hist_%03d            : " U64H_FMT "\n", i, ptr_struct->hist[i]);
	}
}

unsigned int reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_RS_FEC_HISTOGRAMS_COUNTERS_EXT_SIZE;
}

void reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_dump(const struct reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pter_phy_page_reg_ext_pack(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_type_admin);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_type_cap);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_type_oper);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ber_exp);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ber_mantissa);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->error_injection_time);
}

void reg_access_gpu_pter_phy_page_reg_ext_unpack(struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->error_type_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->error_type_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->error_type_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->ber_exp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 52;
	ptr_struct->ber_mantissa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->error_injection_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pter_phy_page_reg_ext_print(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pter_phy_page_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type_admin     : " UH_FMT "\n", ptr_struct->error_type_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type_cap       : " UH_FMT "\n", ptr_struct->error_type_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type_oper      : " UH_FMT "\n", ptr_struct->error_type_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_exp              : " UH_FMT "\n", ptr_struct->ber_exp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_mantissa         : " UH_FMT "\n", ptr_struct->ber_mantissa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_injection_time : " UH_FMT "\n", ptr_struct->error_injection_time);
}

unsigned int reg_access_gpu_pter_phy_page_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PTER_PHY_PAGE_REG_EXT_SIZE;
}

void reg_access_gpu_pter_phy_page_reg_ext_dump(const struct reg_access_gpu_pter_phy_page_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pter_phy_page_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pter_port_page_reg_ext_pack(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_type_admin);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_type_cap);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->error_count);
}

void reg_access_gpu_pter_port_page_reg_ext_unpack(struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->error_type_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->error_type_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 47;
	ptr_struct->error_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_gpu_pter_port_page_reg_ext_print(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pter_port_page_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type_admin     : " UH_FMT "\n", ptr_struct->error_type_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type_cap       : " UH_FMT "\n", ptr_struct->error_type_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_count          : " UH_FMT "\n", ptr_struct->error_count);
}

unsigned int reg_access_gpu_pter_port_page_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PTER_PORT_PAGE_REG_EXT_SIZE;
}

void reg_access_gpu_pter_port_page_reg_ext_dump(const struct reg_access_gpu_pter_port_page_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pter_port_page_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_rom_version_ext_pack(const struct reg_access_gpu_rom_version_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->build);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
}

void reg_access_gpu_rom_version_ext_unpack(struct reg_access_gpu_rom_version_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->build = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 8;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_rom_version_ext_print(const struct reg_access_gpu_rom_version_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_rom_version_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build                : " UH_FMT "\n", ptr_struct->build);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
}

unsigned int reg_access_gpu_rom_version_ext_size(void)
{
	return REG_ACCESS_GPU_ROM_VERSION_EXT_SIZE;
}

void reg_access_gpu_rom_version_ext_dump(const struct reg_access_gpu_rom_version_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_rom_version_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_16nm_ext_pack(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->grade_lane_speed);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->grade);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->grade_version);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_neg_up);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_pos_up);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_pos_mid);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_neg_up);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_pos_up);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_neg_mid);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_pos_mid);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_neg_mid);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_neg_low);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_pos_low);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_neg_low);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_pos_low);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->up_eye_grade);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->mid_eye_grade);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->dn_eye_grade);
}

void reg_access_gpu_slrg_16nm_ext_unpack(struct reg_access_gpu_slrg_16nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->grade_lane_speed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->grade = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 32;
	ptr_struct->grade_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->height_eo_neg_up = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->height_eo_pos_up = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->height_eo_pos_mid = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 104;
	ptr_struct->phase_eo_neg_up = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->phase_eo_pos_up = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 152;
	ptr_struct->phase_eo_neg_mid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->phase_eo_pos_mid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->height_eo_neg_mid = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 176;
	ptr_struct->height_eo_neg_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->height_eo_pos_low = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 200;
	ptr_struct->phase_eo_neg_low = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 192;
	ptr_struct->phase_eo_pos_low = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 240;
	ptr_struct->up_eye_grade = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->mid_eye_grade = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 272;
	ptr_struct->dn_eye_grade = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_slrg_16nm_ext_print(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_16nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade_lane_speed     : " UH_FMT "\n", ptr_struct->grade_lane_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade                : " UH_FMT "\n", ptr_struct->grade);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade_version        : " UH_FMT "\n", ptr_struct->grade_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_neg_up     : " UH_FMT "\n", ptr_struct->height_eo_neg_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_pos_up     : " UH_FMT "\n", ptr_struct->height_eo_pos_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_pos_mid    : " UH_FMT "\n", ptr_struct->height_eo_pos_mid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_neg_up      : " UH_FMT "\n", ptr_struct->phase_eo_neg_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_pos_up      : " UH_FMT "\n", ptr_struct->phase_eo_pos_up);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_neg_mid     : " UH_FMT "\n", ptr_struct->phase_eo_neg_mid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_pos_mid     : " UH_FMT "\n", ptr_struct->phase_eo_pos_mid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_neg_mid    : " UH_FMT "\n", ptr_struct->height_eo_neg_mid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_neg_low    : " UH_FMT "\n", ptr_struct->height_eo_neg_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_pos_low    : " UH_FMT "\n", ptr_struct->height_eo_pos_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_neg_low     : " UH_FMT "\n", ptr_struct->phase_eo_neg_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_pos_low     : " UH_FMT "\n", ptr_struct->phase_eo_pos_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_eye_grade         : " UH_FMT "\n", ptr_struct->up_eye_grade);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mid_eye_grade        : " UH_FMT "\n", ptr_struct->mid_eye_grade);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dn_eye_grade         : " UH_FMT "\n", ptr_struct->dn_eye_grade);
}

unsigned int reg_access_gpu_slrg_16nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_16NM_EXT_SIZE;
}

void reg_access_gpu_slrg_16nm_ext_dump(const struct reg_access_gpu_slrg_16nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_16nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_40nm_28nm_ext_pack(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->grade_lane_speed);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->grade);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->grade_version);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_neg);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->height_eo_pos);
	offset = 248;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_neg);
	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->phase_eo_pos);
}

void reg_access_gpu_slrg_40nm_28nm_ext_unpack(struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->grade_lane_speed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->grade = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 32;
	ptr_struct->grade_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 176;
	ptr_struct->height_eo_neg = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->height_eo_pos = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 248;
	ptr_struct->phase_eo_neg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 232;
	ptr_struct->phase_eo_pos = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_slrg_40nm_28nm_ext_print(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_40nm_28nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade_lane_speed     : " UH_FMT "\n", ptr_struct->grade_lane_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade                : " UH_FMT "\n", ptr_struct->grade);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grade_version        : " UH_FMT "\n", ptr_struct->grade_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_neg        : " UH_FMT "\n", ptr_struct->height_eo_neg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "height_eo_pos        : " UH_FMT "\n", ptr_struct->height_eo_pos);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_neg         : " UH_FMT "\n", ptr_struct->phase_eo_neg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phase_eo_pos         : " UH_FMT "\n", ptr_struct->phase_eo_pos);
}

unsigned int reg_access_gpu_slrg_40nm_28nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_40NM_28NM_EXT_SIZE;
}

void reg_access_gpu_slrg_40nm_28nm_ext_dump(const struct reg_access_gpu_slrg_40nm_28nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_40nm_28nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_5nm_ext_pack(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fom_measurment);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->initial_fom);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fom_mode);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->upper_eye);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->last_fom);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lower_eye);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->mid_eye);
}

void reg_access_gpu_slrg_5nm_ext_unpack(struct reg_access_gpu_slrg_5nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->fom_measurment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->initial_fom = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 44;
	ptr_struct->fom_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->upper_eye = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->last_fom = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->lower_eye = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->mid_eye = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_slrg_5nm_ext_print(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_5nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_measurment       : " UH_FMT "\n", ptr_struct->fom_measurment);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "initial_fom          : " UH_FMT "\n", ptr_struct->initial_fom);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_mode             : %s (" UH_FMT ")\n", (ptr_struct->fom_mode == 0 ? ("FOM_MODE_EYE_OPEN") : ((ptr_struct->fom_mode == 1 ? ("FOM_MODE_EYEO_SNR") : ((ptr_struct->fom_mode == 2 ? ("FOM_MODE_NORM_SNR") : ((ptr_struct->fom_mode == 3 ? ("FOM_MODE_EYE_LVLN") : ((ptr_struct->fom_mode == 4 ? ("FOM_MODE_EYE_LVLP") : ((ptr_struct->fom_mode == 5 ? ("FOM_MODE_THRES_NERR") : ((ptr_struct->fom_mode == 6 ? ("FOM_MODE_CDR_NERR") : ((ptr_struct->fom_mode == 7 ? ("FOM_MODE_CSDET_NERR") : ((ptr_struct->fom_mode == 8 ? ("FOM_MODE_MLSE_NERR") : ((ptr_struct->fom_mode == 9 ? ("FOM_MODE_SFEC_NERR") : ("unknown")))))))))))))))))))), ptr_struct->fom_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "upper_eye            : " UH_FMT "\n", ptr_struct->upper_eye);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_fom             : " UH_FMT "\n", ptr_struct->last_fom);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lower_eye            : " UH_FMT "\n", ptr_struct->lower_eye);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mid_eye              : " UH_FMT "\n", ptr_struct->mid_eye);
}

unsigned int reg_access_gpu_slrg_5nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_5NM_EXT_SIZE;
}

void reg_access_gpu_slrg_5nm_ext_dump(const struct reg_access_gpu_slrg_5nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_5nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_7nm_ext_pack(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fom_measurment);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->initial_fom);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->fom_mode);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lower_eye);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->mid_eye);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->upper_eye);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_fom);
}

void reg_access_gpu_slrg_7nm_ext_unpack(struct reg_access_gpu_slrg_7nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->fom_measurment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->initial_fom = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 45;
	ptr_struct->fom_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 88;
	ptr_struct->lower_eye = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->mid_eye = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->upper_eye = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->last_fom = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_slrg_7nm_ext_print(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_7nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_measurment       : " UH_FMT "\n", ptr_struct->fom_measurment);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "initial_fom          : " UH_FMT "\n", ptr_struct->initial_fom);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_mode             : %s (" UH_FMT ")\n", (ptr_struct->fom_mode == 0 ? ("FOM_MODE_EYEC") : ((ptr_struct->fom_mode == 1 ? ("FOM_MODE_EYEO") : ((ptr_struct->fom_mode == 2 ? ("FOM_MODE_EYEM") : ((ptr_struct->fom_mode == 3 ? ("FOM_MODE_BER") : ((ptr_struct->fom_mode == 4 ? ("FOM_MODE_EYEC_VN") : ((ptr_struct->fom_mode == 5 ? ("FOM_MODE_EYEC_VP") : ((ptr_struct->fom_mode == 6 ? ("FOM_MODE_EYEM_VN") : ((ptr_struct->fom_mode == 7 ? ("FOM_MODE_EYEM_VP") : ("unknown")))))))))))))))), ptr_struct->fom_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lower_eye            : " UH_FMT "\n", ptr_struct->lower_eye);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mid_eye              : " UH_FMT "\n", ptr_struct->mid_eye);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "upper_eye            : " UH_FMT "\n", ptr_struct->upper_eye);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_fom             : " UH_FMT "\n", ptr_struct->last_fom);
}

unsigned int reg_access_gpu_slrg_7nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_7NM_EXT_SIZE;
}

void reg_access_gpu_slrg_7nm_ext_dump(const struct reg_access_gpu_slrg_7nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_7nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_all_lanes_5nm_ext_pack(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fom_mode);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane1);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane0);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane3);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane2);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane5);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane4);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane7);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fom_lane6);
}

void reg_access_gpu_slrg_all_lanes_5nm_ext_unpack(struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->fom_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->fom_lane1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->fom_lane0 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->fom_lane3 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->fom_lane2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->fom_lane5 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->fom_lane4 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 144;
	ptr_struct->fom_lane7 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->fom_lane6 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_slrg_all_lanes_5nm_ext_print(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_all_lanes_5nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_mode             : " UH_FMT "\n", ptr_struct->fom_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane1            : " UH_FMT "\n", ptr_struct->fom_lane1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane0            : " UH_FMT "\n", ptr_struct->fom_lane0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane3            : " UH_FMT "\n", ptr_struct->fom_lane3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane2            : " UH_FMT "\n", ptr_struct->fom_lane2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane5            : " UH_FMT "\n", ptr_struct->fom_lane5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane4            : " UH_FMT "\n", ptr_struct->fom_lane4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane7            : " UH_FMT "\n", ptr_struct->fom_lane7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fom_lane6            : " UH_FMT "\n", ptr_struct->fom_lane6);
}

unsigned int reg_access_gpu_slrg_all_lanes_5nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_ALL_LANES_5NM_EXT_SIZE;
}

void reg_access_gpu_slrg_all_lanes_5nm_ext_dump(const struct reg_access_gpu_slrg_all_lanes_5nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_all_lanes_5nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_16nm_ext_pack(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->post_tap);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->main_tap);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pre_tap);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pre_2_tap);
	offset = 91;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->ob_alev_out);
	offset = 81;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->ob_amp);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->ob_m2lp);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ob_bad_stat);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->regp_bfm1n);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->regn_bfm1p);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->obnlev);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->obplev);
}

void reg_access_gpu_sltp_16nm_ext_unpack(struct reg_access_gpu_sltp_16nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->post_tap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->main_tap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->pre_tap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->pre_2_tap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 91;
	ptr_struct->ob_alev_out = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 81;
	ptr_struct->ob_amp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 64;
	ptr_struct->ob_m2lp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 96;
	ptr_struct->ob_bad_stat = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 152;
	ptr_struct->regp_bfm1n = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 144;
	ptr_struct->regn_bfm1p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 136;
	ptr_struct->obnlev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 128;
	ptr_struct->obplev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_sltp_16nm_ext_print(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_16nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "post_tap             : " UH_FMT "\n", ptr_struct->post_tap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "main_tap             : " UH_FMT "\n", ptr_struct->main_tap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pre_tap              : " UH_FMT "\n", ptr_struct->pre_tap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pre_2_tap            : " UH_FMT "\n", ptr_struct->pre_2_tap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_alev_out          : " UH_FMT "\n", ptr_struct->ob_alev_out);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_amp               : " UH_FMT "\n", ptr_struct->ob_amp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_m2lp              : " UH_FMT "\n", ptr_struct->ob_m2lp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_bad_stat          : %s (" UH_FMT ")\n", (ptr_struct->ob_bad_stat == 0 ? ("configuration_warning") : ((ptr_struct->ob_bad_stat == 11 ? ("Illegal_ob_combination") : ((ptr_struct->ob_bad_stat == 12 ? ("Illegal_ob_m2lp") : ((ptr_struct->ob_bad_stat == 13 ? ("Illegal_ob_amp") : ((ptr_struct->ob_bad_stat == 14 ? ("Illegal_ob_alev_out") : ((ptr_struct->ob_bad_stat == 15 ? ("Illegal_taps") : ("unknown")))))))))))), ptr_struct->ob_bad_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "regp_bfm1n           : " UH_FMT "\n", ptr_struct->regp_bfm1n);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "regn_bfm1p           : " UH_FMT "\n", ptr_struct->regn_bfm1p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "obnlev               : " UH_FMT "\n", ptr_struct->obnlev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "obplev               : " UH_FMT "\n", ptr_struct->obplev);
}

unsigned int reg_access_gpu_sltp_16nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_16NM_EXT_SIZE;
}

void reg_access_gpu_sltp_16nm_ext_dump(const struct reg_access_gpu_sltp_16nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_16nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_28nm_40nm_ext_pack(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_tap2);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_tap1);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_tap0);
	offset = 39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->polarity);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_bias);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_reg);
	offset = 76;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ob_preemp_mode);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ob_leva);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ob_bad_stat);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ob_norm);
}

void reg_access_gpu_sltp_28nm_40nm_ext_unpack(struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->ob_tap2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ob_tap1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->ob_tap0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 39;
	ptr_struct->polarity = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 88;
	ptr_struct->ob_bias = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->ob_reg = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 76;
	ptr_struct->ob_preemp_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 72;
	ptr_struct->ob_leva = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 97;
	ptr_struct->ob_bad_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 96;
	ptr_struct->ob_norm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_sltp_28nm_40nm_ext_print(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_28nm_40nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_tap2              : " UH_FMT "\n", ptr_struct->ob_tap2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_tap1              : " UH_FMT "\n", ptr_struct->ob_tap1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_tap0              : " UH_FMT "\n", ptr_struct->ob_tap0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "polarity             : " UH_FMT "\n", ptr_struct->polarity);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_bias              : " UH_FMT "\n", ptr_struct->ob_bias);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_reg               : " UH_FMT "\n", ptr_struct->ob_reg);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_preemp_mode       : " UH_FMT "\n", ptr_struct->ob_preemp_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_leva              : " UH_FMT "\n", ptr_struct->ob_leva);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_bad_stat          : " UH_FMT "\n", ptr_struct->ob_bad_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_norm              : " UH_FMT "\n", ptr_struct->ob_norm);
}

unsigned int reg_access_gpu_sltp_28nm_40nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_28NM_40NM_EXT_SIZE;
}

void reg_access_gpu_sltp_28nm_40nm_ext_dump(const struct reg_access_gpu_sltp_28nm_40nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_28nm_40nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_5nm_ext_pack(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ob_bad_stat);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap0);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap1);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap2);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap3);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap4);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap5);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap6);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap7);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap8);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap9);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap10);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->tap11);
}

void reg_access_gpu_sltp_5nm_ext_unpack(struct reg_access_gpu_sltp_5nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->ob_bad_stat = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 56;
	ptr_struct->tap0 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->tap1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->tap2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->tap3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->tap4 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->tap5 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->tap6 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->tap7 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->tap8 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->tap9 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->tap10 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->tap11 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_sltp_5nm_ext_print(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_5nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_bad_stat          : %s (" UH_FMT ")\n", (ptr_struct->ob_bad_stat == 1 ? ("tap0_is_out_of_range") : ((ptr_struct->ob_bad_stat == 2 ? ("tap1_is_out_of_range") : ((ptr_struct->ob_bad_stat == 4 ? ("tap2_is_out_of_range") : ((ptr_struct->ob_bad_stat == 8 ? ("tap3_is_out_of_range") : ((ptr_struct->ob_bad_stat == 16 ? ("tap4_is_out_of_range") : ((ptr_struct->ob_bad_stat == 32 ? ("tap5_is_out_of_range") : ((ptr_struct->ob_bad_stat == 64 ? ("tap6_is_out_of_range") : ((ptr_struct->ob_bad_stat == 128 ? ("tap7_is_out_of_range") : ((ptr_struct->ob_bad_stat == 256 ? ("tap8_is_out_of_range") : ((ptr_struct->ob_bad_stat == 512 ? ("tap9_is_out_of_range") : ((ptr_struct->ob_bad_stat == 1024 ? ("tap10_is_out_of_range") : ((ptr_struct->ob_bad_stat == 2048 ? ("tap11_is_out_of_range") : ((ptr_struct->ob_bad_stat == 512 ? ("sum_of_taps_is_out_of_range") : ("unknown")))))))))))))))))))))))))), ptr_struct->ob_bad_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap0                 : " UH_FMT "\n", ptr_struct->tap0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap1                 : " UH_FMT "\n", ptr_struct->tap1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap2                 : " UH_FMT "\n", ptr_struct->tap2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap3                 : " UH_FMT "\n", ptr_struct->tap3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap4                 : " UH_FMT "\n", ptr_struct->tap4);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap5                 : " UH_FMT "\n", ptr_struct->tap5);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap6                 : " UH_FMT "\n", ptr_struct->tap6);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap7                 : " UH_FMT "\n", ptr_struct->tap7);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap8                 : " UH_FMT "\n", ptr_struct->tap8);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap9                 : " UH_FMT "\n", ptr_struct->tap9);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap10                : " UH_FMT "\n", ptr_struct->tap10);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tap11                : " UH_FMT "\n", ptr_struct->tap11);
}

unsigned int reg_access_gpu_sltp_5nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_5NM_EXT_SIZE;
}

void reg_access_gpu_sltp_5nm_ext_dump(const struct reg_access_gpu_sltp_5nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_5nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_7nm_ext_pack(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fir_pre2);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fir_pre3);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ob_bad_stat);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->drv_amp);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fir_post1);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fir_main);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fir_pre1);
}

void reg_access_gpu_sltp_7nm_ext_unpack(struct reg_access_gpu_sltp_7nm_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->fir_pre2 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->fir_pre3 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->ob_bad_stat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->drv_amp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 48;
	ptr_struct->fir_post1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->fir_main = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->fir_pre1 = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_sltp_7nm_ext_print(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_7nm_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fir_pre2             : " UH_FMT "\n", ptr_struct->fir_pre2);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fir_pre3             : " UH_FMT "\n", ptr_struct->fir_pre3);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ob_bad_stat          : %s (" UH_FMT ")\n", (ptr_struct->ob_bad_stat == 1 ? ("pre3_is_out_of_range") : ((ptr_struct->ob_bad_stat == 2 ? ("pre2_is_out_of_range") : ((ptr_struct->ob_bad_stat == 4 ? ("pre1_is_out_of_range") : ((ptr_struct->ob_bad_stat == 8 ? ("main_tap_is_out_of_range") : ((ptr_struct->ob_bad_stat == 16 ? ("post1_is_out_of_range") : ((ptr_struct->ob_bad_stat == 32 ? ("sum_of_taps_is_out_of_range") : ((ptr_struct->ob_bad_stat == 64 ? ("taps_not_alinged_with_speed") : ("unknown")))))))))))))), ptr_struct->ob_bad_stat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "drv_amp              : " UH_FMT "\n", ptr_struct->drv_amp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fir_post1            : " UH_FMT "\n", ptr_struct->fir_post1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fir_main             : " UH_FMT "\n", ptr_struct->fir_main);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fir_pre1             : " UH_FMT "\n", ptr_struct->fir_pre1);
}

unsigned int reg_access_gpu_sltp_7nm_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_7NM_EXT_SIZE;
}

void reg_access_gpu_sltp_7nm_ext_dump(const struct reg_access_gpu_sltp_7nm_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_7nm_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_data_auto_ext_pack(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_MRFV_ULT_ext_pack(&(ptr_struct->MRFV_ULT_ext), ptr_buff);
}

void reg_access_gpu_MRFV_data_auto_ext_unpack(union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_MRFV_ULT_ext_unpack(&(ptr_struct->MRFV_ULT_ext), ptr_buff);
}

void reg_access_gpu_MRFV_data_auto_ext_print(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_CVB_ext:\n");
	reg_access_gpu_MRFV_CVB_ext_print(&(ptr_struct->MRFV_CVB_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_PVS_MAIN_ext:\n");
	reg_access_gpu_MRFV_PVS_MAIN_ext_print(&(ptr_struct->MRFV_PVS_MAIN_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_PVS_TILE_ext:\n");
	reg_access_gpu_MRFV_PVS_TILE_ext_print(&(ptr_struct->MRFV_PVS_TILE_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_ULT_ext:\n");
	reg_access_gpu_MRFV_ULT_ext_print(&(ptr_struct->MRFV_ULT_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_MRFV_data_auto_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_DATA_AUTO_EXT_SIZE;
}

void reg_access_gpu_MRFV_data_auto_ext_dump(const union reg_access_gpu_MRFV_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_lane_2_module_mapping_ext_pack(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_lane);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_lane);
}

void reg_access_gpu_lane_2_module_mapping_ext_unpack(struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 20;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 12;
	ptr_struct->tx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->rx_lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_lane_2_module_mapping_ext_print(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_lane_2_module_mapping_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_lane              : " UH_FMT "\n", ptr_struct->tx_lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_lane              : " UH_FMT "\n", ptr_struct->rx_lane);
}

unsigned int reg_access_gpu_lane_2_module_mapping_ext_size(void)
{
	return REG_ACCESS_GPU_LANE_2_MODULE_MAPPING_EXT_SIZE;
}

void reg_access_gpu_lane_2_module_mapping_ext_dump(const struct reg_access_gpu_lane_2_module_mapping_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_lane_2_module_mapping_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mgir_dev_info_ext_pack(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->dev_branch_tag[i]);
	}
}

void reg_access_gpu_mgir_dev_info_ext_unpack(struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 28; ++i) {
		offset = adb2c_calc_array_field_address(24, 8, i, 224, 1);
		ptr_struct->dev_branch_tag[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_gpu_mgir_dev_info_ext_print(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mgir_dev_info_ext ========\n");

	for (i = 0; i < 28; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dev_branch_tag_%03d  : " UH_FMT "\n", i, ptr_struct->dev_branch_tag[i]);
	}
}

unsigned int reg_access_gpu_mgir_dev_info_ext_size(void)
{
	return REG_ACCESS_GPU_MGIR_DEV_INFO_EXT_SIZE;
}

void reg_access_gpu_mgir_dev_info_ext_dump(const struct reg_access_gpu_mgir_dev_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mgir_dev_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mgir_fw_info_ext_pack(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sub_minor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secured);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_fw);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->debug);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->string_tlv);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dev_sc);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->build_id);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->year);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->day);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->month);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hour);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ini_file_version);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_major);
	offset = 320;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_minor);
	offset = 352;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->extended_sub_minor);
	offset = 400;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->isfu_major);
	offset = 384;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->disabled_tiles_bitmap);
	offset = 446;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->life_cycle);
	offset = 445;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sec_boot);
	offset = 444;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->encryption);
	offset = 441;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->life_cycle_msb);
	offset = 434;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->issu_able);
	offset = 433;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pds);
}

void reg_access_gpu_mgir_fw_info_ext_unpack(struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->sub_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 7;
	ptr_struct->secured = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->signed_fw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->debug = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->dev = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->string_tlv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->dev_sc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->build_id = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->year = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->day = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->month = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->hour = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(152, 8, i, 512, 1);
		ptr_struct->psid[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
	offset = 256;
	ptr_struct->ini_file_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->extended_major = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->extended_minor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 352;
	ptr_struct->extended_sub_minor = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 400;
	ptr_struct->isfu_major = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 384;
	ptr_struct->disabled_tiles_bitmap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 446;
	ptr_struct->life_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 445;
	ptr_struct->sec_boot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 444;
	ptr_struct->encryption = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 441;
	ptr_struct->life_cycle_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 434;
	ptr_struct->issu_able = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 433;
	ptr_struct->pds = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_mgir_fw_info_ext_print(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mgir_fw_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_minor            : " UH_FMT "\n", ptr_struct->sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secured              : " UH_FMT "\n", ptr_struct->secured);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "signed_fw            : " UH_FMT "\n", ptr_struct->signed_fw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "debug                : " UH_FMT "\n", ptr_struct->debug);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev                  : " UH_FMT "\n", ptr_struct->dev);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_tlv           : " UH_FMT "\n", ptr_struct->string_tlv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_sc               : " UH_FMT "\n", ptr_struct->dev_sc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "build_id             : " U32H_FMT "\n", ptr_struct->build_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "year                 : " UH_FMT "\n", ptr_struct->year);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "day                  : " UH_FMT "\n", ptr_struct->day);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "month                : " UH_FMT "\n", ptr_struct->month);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hour                 : " UH_FMT "\n", ptr_struct->hour);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "psid_%03d            : " UH_FMT "\n", i, ptr_struct->psid[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ini_file_version     : " U32H_FMT "\n", ptr_struct->ini_file_version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_major       : " U32H_FMT "\n", ptr_struct->extended_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_minor       : " U32H_FMT "\n", ptr_struct->extended_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "extended_sub_minor   : " U32H_FMT "\n", ptr_struct->extended_sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "isfu_major           : " UH_FMT "\n", ptr_struct->isfu_major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "disabled_tiles_bitmap : " UH_FMT "\n", ptr_struct->disabled_tiles_bitmap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "life_cycle           : " UH_FMT "\n", ptr_struct->life_cycle);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sec_boot             : " UH_FMT "\n", ptr_struct->sec_boot);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "encryption           : " UH_FMT "\n", ptr_struct->encryption);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "life_cycle_msb       : " UH_FMT "\n", ptr_struct->life_cycle_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "issu_able            : " UH_FMT "\n", ptr_struct->issu_able);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pds                  : " UH_FMT "\n", ptr_struct->pds);
}

unsigned int reg_access_gpu_mgir_fw_info_ext_size(void)
{
	return REG_ACCESS_GPU_MGIR_FW_INFO_EXT_SIZE;
}

void reg_access_gpu_mgir_fw_info_ext_dump(const struct reg_access_gpu_mgir_fw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mgir_fw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mgir_hardware_info_ext_pack(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_id);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_hw_revision);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->pvs);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->technology);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_ports);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->ib_mad_gen);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->hw_dev_id);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->development);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->manufacturing_base_mac_47_32);
	offset = 138;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->ga);
	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->chip_type);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->manufacturing_base_mac_31_0);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uptime);
}

void reg_access_gpu_mgir_hardware_info_ext_unpack(struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->device_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 0;
	ptr_struct->device_hw_revision = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 59;
	ptr_struct->pvs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 48;
	ptr_struct->technology = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 40;
	ptr_struct->num_ports = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 33;
	ptr_struct->ib_mad_gen = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 80;
	ptr_struct->hw_dev_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 97;
	ptr_struct->development = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 144;
	ptr_struct->manufacturing_base_mac_47_32 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 138;
	ptr_struct->ga = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 132;
	ptr_struct->chip_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->manufacturing_base_mac_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->uptime = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mgir_hardware_info_ext_print(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mgir_hardware_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_id            : " UH_FMT "\n", ptr_struct->device_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_hw_revision   : " UH_FMT "\n", ptr_struct->device_hw_revision);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pvs                  : " UH_FMT "\n", ptr_struct->pvs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "technology           : " UH_FMT "\n", ptr_struct->technology);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_ports            : " UH_FMT "\n", ptr_struct->num_ports);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_mad_gen           : " UH_FMT "\n", ptr_struct->ib_mad_gen);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_dev_id            : " UH_FMT "\n", ptr_struct->hw_dev_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "development          : " UH_FMT "\n", ptr_struct->development);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_47_32 : " UH_FMT "\n", ptr_struct->manufacturing_base_mac_47_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ga                   : " UH_FMT "\n", ptr_struct->ga);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "chip_type            : " UH_FMT "\n", ptr_struct->chip_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "manufacturing_base_mac_31_0 : " U32H_FMT "\n", ptr_struct->manufacturing_base_mac_31_0);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "uptime               : " U32H_FMT "\n", ptr_struct->uptime);
}

unsigned int reg_access_gpu_mgir_hardware_info_ext_size(void)
{
	return REG_ACCESS_GPU_MGIR_HARDWARE_INFO_EXT_SIZE;
}

void reg_access_gpu_mgir_hardware_info_ext_dump(const struct reg_access_gpu_mgir_hardware_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mgir_hardware_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mgir_sw_info_ext_pack(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sub_minor);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom3_type);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom3_arch);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom2_type);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom2_arch);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom1_type);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom1_arch);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom0_type);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rom0_arch);
	offset = 64;
	reg_access_gpu_rom_version_ext_pack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_gpu_rom_version_ext_pack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_gpu_rom_version_ext_pack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_gpu_rom_version_ext_pack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_gpu_mgir_sw_info_ext_unpack(struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->sub_minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->minor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->major = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->rom3_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->rom3_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->rom2_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->rom2_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 44;
	ptr_struct->rom1_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->rom1_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 36;
	ptr_struct->rom0_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->rom0_arch = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	reg_access_gpu_rom_version_ext_unpack(&(ptr_struct->rom0_version), ptr_buff + offset / 8);
	offset = 96;
	reg_access_gpu_rom_version_ext_unpack(&(ptr_struct->rom1_version), ptr_buff + offset / 8);
	offset = 128;
	reg_access_gpu_rom_version_ext_unpack(&(ptr_struct->rom2_version), ptr_buff + offset / 8);
	offset = 160;
	reg_access_gpu_rom_version_ext_unpack(&(ptr_struct->rom3_version), ptr_buff + offset / 8);
}

void reg_access_gpu_mgir_sw_info_ext_print(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mgir_sw_info_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sub_minor            : " UH_FMT "\n", ptr_struct->sub_minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "minor                : " UH_FMT "\n", ptr_struct->minor);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "major                : " UH_FMT "\n", ptr_struct->major);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_type            : " UH_FMT "\n", ptr_struct->rom3_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_arch            : " UH_FMT "\n", ptr_struct->rom3_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_type            : " UH_FMT "\n", ptr_struct->rom2_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_arch            : " UH_FMT "\n", ptr_struct->rom2_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_type            : " UH_FMT "\n", ptr_struct->rom1_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_arch            : " UH_FMT "\n", ptr_struct->rom1_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_type            : " UH_FMT "\n", ptr_struct->rom0_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_arch            : " UH_FMT "\n", ptr_struct->rom0_arch);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom0_version:\n");
	reg_access_gpu_rom_version_ext_print(&(ptr_struct->rom0_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom1_version:\n");
	reg_access_gpu_rom_version_ext_print(&(ptr_struct->rom1_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom2_version:\n");
	reg_access_gpu_rom_version_ext_print(&(ptr_struct->rom2_version), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rom3_version:\n");
	reg_access_gpu_rom_version_ext_print(&(ptr_struct->rom3_version), fd, indent_level + 1);
}

unsigned int reg_access_gpu_mgir_sw_info_ext_size(void)
{
	return REG_ACCESS_GPU_MGIR_SW_INFO_EXT_SIZE;
}

void reg_access_gpu_mgir_sw_info_ext_dump(const struct reg_access_gpu_mgir_sw_info_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mgir_sw_info_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_reg_page_data_auto_ext_pack(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_troubleshooting_page_ext_pack(&(ptr_struct->pddr_troubleshooting_page_ext), ptr_buff);
}

void reg_access_gpu_pddr_reg_page_data_auto_ext_unpack(union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_troubleshooting_page_ext_unpack(&(ptr_struct->pddr_troubleshooting_page_ext), ptr_buff);
}

void reg_access_gpu_pddr_reg_page_data_auto_ext_print(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_latched_flag_info_ext:\n");
	reg_access_gpu_module_latched_flag_info_ext_print(&(ptr_struct->module_latched_flag_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_link_down_info_page_ext:\n");
	reg_access_gpu_pddr_link_down_info_page_ext_print(&(ptr_struct->pddr_link_down_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_module_info_ext:\n");
	reg_access_gpu_pddr_module_info_ext_print(&(ptr_struct->pddr_module_info_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_operation_info_page_ext:\n");
	reg_access_gpu_pddr_operation_info_page_ext_print(&(ptr_struct->pddr_operation_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_phy_info_page_ext:\n");
	reg_access_gpu_pddr_phy_info_page_ext_print(&(ptr_struct->pddr_phy_info_page_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_troubleshooting_page_ext:\n");
	reg_access_gpu_pddr_troubleshooting_page_ext_print(&(ptr_struct->pddr_troubleshooting_page_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pddr_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_gpu_pddr_reg_page_data_auto_ext_dump(const union reg_access_gpu_pddr_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_pack(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_pack(&(ptr_struct->pmmp_qsfp_protocol_override_layout_ext), ptr_buff);
}

void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_unpack(union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_unpack(&(ptr_struct->pmmp_qsfp_protocol_override_layout_ext), ptr_buff);
}

void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_print(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmmp_cmis_protocol_override_layout_ext:\n");
	reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_print(&(ptr_struct->pmmp_cmis_protocol_override_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmmp_qsfp_protocol_override_layout_ext:\n");
	reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_print(&(ptr_struct->pmmp_qsfp_protocol_override_layout_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_REG_QSFP_CABLE_PROTOCOL_TECHNOLOGY_AUTO_EXT_SIZE;
}

void reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_dump(const union reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_reg_qsfp_cable_protocol_technology_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_pack(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_pack(&(ptr_struct->pmmp_sfp_protocol_bytes_override_ext), ptr_buff);
}

void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_unpack(union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_unpack(&(ptr_struct->pmmp_sfp_protocol_bytes_override_ext), ptr_buff);
}

void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_print(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmmp_sfp_protocol_bytes_override_ext:\n");
	reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_print(&(ptr_struct->pmmp_sfp_protocol_bytes_override_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_REG_SFP_CABLE_PROTOCOL_TECHNOLOGY_AUTO_EXT_SIZE;
}

void reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_dump(const union reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_reg_sfp_cable_protocol_technology_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_pack(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_pack(&(ptr_struct->ppcnt_rs_fec_histograms_counters_ext), ptr_buff);
}

void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_unpack(union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_unpack(&(ptr_struct->ppcnt_rs_fec_histograms_counters_ext), ptr_buff);
}

void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_print(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_reg_counter_set_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IB_long_portcntrs_attribute_grp_data_ext:\n");
	reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_print(&(ptr_struct->IB_long_portcntrs_attribute_grp_data_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "IB_portcntrs_attribute_grp_data_ext:\n");
	reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_print(&(ptr_struct->IB_portcntrs_attribute_grp_data_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_2819_cntrs_grp_data_layout_ext:\n");
	reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_print(&(ptr_struct->eth_2819_cntrs_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_2863_cntrs_grp_data_layout_ext:\n");
	reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_print(&(ptr_struct->eth_2863_cntrs_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_3635_cntrs_grp_data_layout_ext:\n");
	reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_print(&(ptr_struct->eth_3635_cntrs_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_802_3_cntrs_grp_data_layout_ext:\n");
	reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_print(&(ptr_struct->eth_802_3_cntrs_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_discard_cntrs_grp_ext:\n");
	reg_access_gpu_eth_discard_cntrs_grp_ext_print(&(ptr_struct->eth_discard_cntrs_grp_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_extended_cntrs_grp_data_layout_ext:\n");
	reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_print(&(ptr_struct->eth_extended_cntrs_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_per_prio_grp_data_layout_ext:\n");
	reg_access_gpu_eth_per_prio_grp_data_layout_ext_print(&(ptr_struct->eth_per_prio_grp_data_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_per_traffic_class_cong_layout_ext:\n");
	reg_access_gpu_eth_per_traffic_class_cong_layout_ext_print(&(ptr_struct->eth_per_traffic_class_cong_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_per_traffic_class_layout_ext:\n");
	reg_access_gpu_eth_per_traffic_class_layout_ext_print(&(ptr_struct->eth_per_traffic_class_layout_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phys_layer_cntrs_ext:\n");
	reg_access_gpu_phys_layer_cntrs_ext_print(&(ptr_struct->phys_layer_cntrs_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phys_layer_stat_cntrs_ext:\n");
	reg_access_gpu_phys_layer_stat_cntrs_ext_print(&(ptr_struct->phys_layer_stat_cntrs_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcnt_infiniband_general_counter_ext:\n");
	reg_access_gpu_ppcnt_infiniband_general_counter_ext_print(&(ptr_struct->ppcnt_infiniband_general_counter_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcnt_infiniband_packets_counter_ext:\n");
	reg_access_gpu_ppcnt_infiniband_packets_counter_ext_print(&(ptr_struct->ppcnt_infiniband_packets_counter_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcnt_plr_counters_ext:\n");
	reg_access_gpu_ppcnt_plr_counters_ext_print(&(ptr_struct->ppcnt_plr_counters_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcnt_rs_fec_histograms_counters_ext:\n");
	reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_print(&(ptr_struct->ppcnt_rs_fec_histograms_counters_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_ppcnt_reg_counter_set_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_REG_COUNTER_SET_AUTO_EXT_SIZE;
}

void reg_access_gpu_ppcnt_reg_counter_set_auto_ext_dump(const union reg_access_gpu_ppcnt_reg_counter_set_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_reg_counter_set_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pphcr_bin_range_ext_pack(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->low_val);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->high_val);
}

void reg_access_gpu_pphcr_bin_range_ext_unpack(struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->low_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 12;
	ptr_struct->high_val = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pphcr_bin_range_ext_print(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pphcr_bin_range_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "low_val              : " UH_FMT "\n", ptr_struct->low_val);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "high_val             : " UH_FMT "\n", ptr_struct->high_val);
}

unsigned int reg_access_gpu_pphcr_bin_range_ext_size(void)
{
	return REG_ACCESS_GPU_PPHCR_BIN_RANGE_EXT_SIZE;
}

void reg_access_gpu_pphcr_bin_range_ext_dump(const struct reg_access_gpu_pphcr_bin_range_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pphcr_bin_range_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pter_reg_page_data_auto_ext_pack(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pter_port_page_reg_ext_pack(&(ptr_struct->pter_port_page_reg_ext), ptr_buff);
}

void reg_access_gpu_pter_reg_page_data_auto_ext_unpack(union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pter_port_page_reg_ext_unpack(&(ptr_struct->pter_port_page_reg_ext), ptr_buff);
}

void reg_access_gpu_pter_reg_page_data_auto_ext_print(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pter_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pter_phy_page_reg_ext:\n");
	reg_access_gpu_pter_phy_page_reg_ext_print(&(ptr_struct->pter_phy_page_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pter_port_page_reg_ext:\n");
	reg_access_gpu_pter_port_page_reg_ext_print(&(ptr_struct->pter_port_page_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pter_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_GPU_PTER_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_gpu_pter_reg_page_data_auto_ext_dump(const union reg_access_gpu_pter_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pter_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_reg_page_data_auto_ext_pack(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_slrg_16nm_ext_pack(&(ptr_struct->slrg_16nm_ext), ptr_buff);
}

void reg_access_gpu_slrg_reg_page_data_auto_ext_unpack(union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_slrg_16nm_ext_unpack(&(ptr_struct->slrg_16nm_ext), ptr_buff);
}

void reg_access_gpu_slrg_reg_page_data_auto_ext_print(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_16nm_ext:\n");
	reg_access_gpu_slrg_16nm_ext_print(&(ptr_struct->slrg_16nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_40nm_28nm_ext:\n");
	reg_access_gpu_slrg_40nm_28nm_ext_print(&(ptr_struct->slrg_40nm_28nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_5nm_ext:\n");
	reg_access_gpu_slrg_5nm_ext_print(&(ptr_struct->slrg_5nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_7nm_ext:\n");
	reg_access_gpu_slrg_7nm_ext_print(&(ptr_struct->slrg_7nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_all_lanes_5nm_ext:\n");
	reg_access_gpu_slrg_all_lanes_5nm_ext_print(&(ptr_struct->slrg_all_lanes_5nm_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_slrg_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_gpu_slrg_reg_page_data_auto_ext_dump(const union reg_access_gpu_slrg_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_reg_page_data_auto_ext_pack(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_sltp_7nm_ext_pack(&(ptr_struct->sltp_7nm_ext), ptr_buff);
}

void reg_access_gpu_sltp_reg_page_data_auto_ext_unpack(union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_sltp_7nm_ext_unpack(&(ptr_struct->sltp_7nm_ext), ptr_buff);
}

void reg_access_gpu_sltp_reg_page_data_auto_ext_print(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_reg_page_data_auto_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sltp_16nm_ext:\n");
	reg_access_gpu_sltp_16nm_ext_print(&(ptr_struct->sltp_16nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sltp_28nm_40nm_ext:\n");
	reg_access_gpu_sltp_28nm_40nm_ext_print(&(ptr_struct->sltp_28nm_40nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sltp_5nm_ext:\n");
	reg_access_gpu_sltp_5nm_ext_print(&(ptr_struct->sltp_5nm_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sltp_7nm_ext:\n");
	reg_access_gpu_sltp_7nm_ext_print(&(ptr_struct->sltp_7nm_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_sltp_reg_page_data_auto_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_REG_PAGE_DATA_AUTO_EXT_SIZE;
}

void reg_access_gpu_sltp_reg_page_data_auto_ext_dump(const union reg_access_gpu_sltp_reg_page_data_auto_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_reg_page_data_auto_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_stat_bufferx_reg_ext_pack(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->watermark);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->used_buffer);
}

void reg_access_gpu_stat_bufferx_reg_ext_unpack(struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->watermark = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 48;
	ptr_struct->used_buffer = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_stat_bufferx_reg_ext_print(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_stat_bufferx_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "watermark            : " UH_FMT "\n", ptr_struct->watermark);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "used_buffer          : " UH_FMT "\n", ptr_struct->used_buffer);
}

unsigned int reg_access_gpu_stat_bufferx_reg_ext_size(void)
{
	return REG_ACCESS_GPU_STAT_BUFFERX_REG_EXT_SIZE;
}

void reg_access_gpu_stat_bufferx_reg_ext_dump(const struct reg_access_gpu_stat_bufferx_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_stat_bufferx_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_string_db_parameters_ext_pack(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->string_db_base_address);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->string_db_size);
}

void reg_access_gpu_string_db_parameters_ext_unpack(struct reg_access_gpu_string_db_parameters_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	ptr_struct->string_db_base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->string_db_size = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_gpu_string_db_parameters_ext_print(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_string_db_parameters_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_base_address : " U32H_FMT "\n", ptr_struct->string_db_base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "string_db_size       : " UH_FMT "\n", ptr_struct->string_db_size);
}

unsigned int reg_access_gpu_string_db_parameters_ext_size(void)
{
	return REG_ACCESS_GPU_STRING_DB_PARAMETERS_EXT_SIZE;
}

void reg_access_gpu_string_db_parameters_ext_dump(const struct reg_access_gpu_string_db_parameters_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_string_db_parameters_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MLPC_ext_pack(const struct reg_access_gpu_MLPC_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cnt_64bit);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->stop_at_ff);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->counter_rst);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->counter_en);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->force_count_mask);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(156, 4, i, 512, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cnt_type[i]);
	}
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 512, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cnt_val[i]);
	}
}

void reg_access_gpu_MLPC_ext_unpack(struct reg_access_gpu_MLPC_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->cnt_64bit = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 34;
	ptr_struct->stop_at_ff = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->counter_rst = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->counter_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 120;
	ptr_struct->force_count_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(156, 4, i, 512, 1);
		ptr_struct->cnt_type[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(256, 32, i, 512, 1);
		ptr_struct->cnt_val[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_MLPC_ext_print(const struct reg_access_gpu_MLPC_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MLPC_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cnt_64bit            : " UH_FMT "\n", ptr_struct->cnt_64bit);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stop_at_ff           : " UH_FMT "\n", ptr_struct->stop_at_ff);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "counter_rst          : " UH_FMT "\n", ptr_struct->counter_rst);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "counter_en           : " UH_FMT "\n", ptr_struct->counter_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_count_mask     : " UH_FMT "\n", ptr_struct->force_count_mask);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "cnt_type_%03d        : " UH_FMT "\n", i, ptr_struct->cnt_type[i]);
	}
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "cnt_val_%03d         : " U32H_FMT "\n", i, ptr_struct->cnt_val[i]);
	}
}

unsigned int reg_access_gpu_MLPC_ext_size(void)
{
	return REG_ACCESS_GPU_MLPC_EXT_SIZE;
}

void reg_access_gpu_MLPC_ext_dump(const struct reg_access_gpu_MLPC_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MLPC_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MRFV_ext_pack(const struct reg_access_gpu_MRFV_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fuse_id);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fm);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->v);
	offset = 128;
	switch (ptr_struct->fuse_id) {
	case 0x0:
		offset = 128;
		reg_access_gpu_MRFV_CVB_ext_pack(&(ptr_struct->data.MRFV_CVB_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_gpu_MRFV_PVS_MAIN_ext_pack(&(ptr_struct->data.MRFV_PVS_MAIN_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_gpu_MRFV_PVS_TILE_ext_pack(&(ptr_struct->data.MRFV_PVS_TILE_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_gpu_MRFV_ULT_ext_pack(&(ptr_struct->data.MRFV_ULT_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_MRFV_ext_unpack(struct reg_access_gpu_MRFV_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->fuse_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 6;
	ptr_struct->fm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 0;
	ptr_struct->v = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 128;
	switch (ptr_struct->fuse_id) {
	case 0x0:
		offset = 128;
		reg_access_gpu_MRFV_CVB_ext_unpack(&(ptr_struct->data.MRFV_CVB_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 128;
		reg_access_gpu_MRFV_PVS_MAIN_ext_unpack(&(ptr_struct->data.MRFV_PVS_MAIN_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 128;
		reg_access_gpu_MRFV_PVS_TILE_ext_unpack(&(ptr_struct->data.MRFV_PVS_TILE_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 128;
		reg_access_gpu_MRFV_ULT_ext_unpack(&(ptr_struct->data.MRFV_ULT_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_MRFV_ext_print(const struct reg_access_gpu_MRFV_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MRFV_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fuse_id              : %s (" UH_FMT ")\n", (ptr_struct->fuse_id == 0 ? ("cvb") : ((ptr_struct->fuse_id == 1 ? ("ULT") : ((ptr_struct->fuse_id == 2 ? ("pvs_main_die") : ((ptr_struct->fuse_id == 3 ? ("pvs_tile_0") : ((ptr_struct->fuse_id == 4 ? ("pvs_tile_1") : ((ptr_struct->fuse_id == 5 ? ("pvs_tile_2") : ((ptr_struct->fuse_id == 6 ? ("pvs_tile_3") : ((ptr_struct->fuse_id == 7 ? ("pvs_tile_4") : ((ptr_struct->fuse_id == 8 ? ("pvs_tile_5") : ((ptr_struct->fuse_id == 9 ? ("pvs_tile_6") : ((ptr_struct->fuse_id == 10 ? ("pvs_tile_7") : ("unknown")))))))))))))))))))))), ptr_struct->fuse_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fm                   : " UH_FMT "\n", ptr_struct->fm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "v                    : " UH_FMT "\n", ptr_struct->v);
	switch (ptr_struct->fuse_id) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_CVB_ext:\n");
		reg_access_gpu_MRFV_CVB_ext_print(&(ptr_struct->data.MRFV_CVB_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_PVS_MAIN_ext:\n");
		reg_access_gpu_MRFV_PVS_MAIN_ext_print(&(ptr_struct->data.MRFV_PVS_MAIN_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_PVS_TILE_ext:\n");
		reg_access_gpu_MRFV_PVS_TILE_ext_print(&(ptr_struct->data.MRFV_PVS_TILE_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "MRFV_ULT_ext:\n");
		reg_access_gpu_MRFV_ULT_ext_print(&(ptr_struct->data.MRFV_ULT_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_gpu_MRFV_ext_size(void)
{
	return REG_ACCESS_GPU_MRFV_EXT_SIZE;
}

void reg_access_gpu_MRFV_ext_dump(const struct reg_access_gpu_MRFV_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MRFV_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_MTSR_ext_pack(const struct reg_access_gpu_MTSR_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->mode);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->normal_events_cnt);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->warning_events_cnt);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->critical_events_cnt);
}

void reg_access_gpu_MTSR_ext_unpack(struct reg_access_gpu_MTSR_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 56;
	ptr_struct->normal_events_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->warning_events_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->critical_events_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_MTSR_ext_print(const struct reg_access_gpu_MTSR_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_MTSR_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mode                 : " UH_FMT "\n", ptr_struct->mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "normal_events_cnt    : " UH_FMT "\n", ptr_struct->normal_events_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "warning_events_cnt   : " UH_FMT "\n", ptr_struct->warning_events_cnt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "critical_events_cnt  : " UH_FMT "\n", ptr_struct->critical_events_cnt);
}

unsigned int reg_access_gpu_MTSR_ext_size(void)
{
	return REG_ACCESS_GPU_MTSR_EXT_SIZE;
}

void reg_access_gpu_MTSR_ext_dump(const struct reg_access_gpu_MTSR_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_MTSR_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ghpkt_ext_pack(const struct reg_access_gpu_ghpkt_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->trap_id);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->action);
}

void reg_access_gpu_ghpkt_ext_unpack(struct reg_access_gpu_ghpkt_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 22;
	ptr_struct->trap_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 8;
	ptr_struct->action = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_ghpkt_ext_print(const struct reg_access_gpu_ghpkt_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ghpkt_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trap_id              : " UH_FMT "\n", ptr_struct->trap_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "action               : %s (" UH_FMT ")\n", (ptr_struct->action == 0 ? ("NOP") : ((ptr_struct->action == 1 ? ("TRAP") : ("unknown")))), ptr_struct->action);
}

unsigned int reg_access_gpu_ghpkt_ext_size(void)
{
	return REG_ACCESS_GPU_GHPKT_EXT_SIZE;
}

void reg_access_gpu_ghpkt_ext_dump(const struct reg_access_gpu_ghpkt_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ghpkt_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_gpgb_ext_pack(const struct reg_access_gpu_gpgb_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->buffer_size);
	offset = 86;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->grxb_p0_req_credits);
	offset = 70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->grxb_p0_rsp_credits);
	offset = 118;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->grxb_p1_req_credits);
	offset = 102;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->grxb_p1_rsp_credits);
}

void reg_access_gpu_gpgb_ext_unpack(struct reg_access_gpu_gpgb_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 54;
	ptr_struct->buffer_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 86;
	ptr_struct->grxb_p0_req_credits = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 70;
	ptr_struct->grxb_p0_rsp_credits = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 118;
	ptr_struct->grxb_p1_req_credits = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 102;
	ptr_struct->grxb_p1_rsp_credits = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
}

void reg_access_gpu_gpgb_ext_print(const struct reg_access_gpu_gpgb_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_gpgb_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "buffer_size          : " UH_FMT "\n", ptr_struct->buffer_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grxb_p0_req_credits  : " UH_FMT "\n", ptr_struct->grxb_p0_req_credits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grxb_p0_rsp_credits  : " UH_FMT "\n", ptr_struct->grxb_p0_rsp_credits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grxb_p1_req_credits  : " UH_FMT "\n", ptr_struct->grxb_p1_req_credits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grxb_p1_rsp_credits  : " UH_FMT "\n", ptr_struct->grxb_p1_rsp_credits);
}

unsigned int reg_access_gpu_gpgb_ext_size(void)
{
	return REG_ACCESS_GPU_GPGB_EXT_SIZE;
}

void reg_access_gpu_gpgb_ext_dump(const struct reg_access_gpu_gpgb_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_gpgb_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_gplid_pack(const struct reg_access_gpu_gplid *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->lid);
}

void reg_access_gpu_gplid_unpack(struct reg_access_gpu_gplid *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 44;
	ptr_struct->lid = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
}

void reg_access_gpu_gplid_print(const struct reg_access_gpu_gplid *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_gplid ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lid                  : " UH_FMT "\n", ptr_struct->lid);
}

unsigned int reg_access_gpu_gplid_size(void)
{
	return REG_ACCESS_GPU_GPLID_SIZE;
}

void reg_access_gpu_gplid_dump(const struct reg_access_gpu_gplid *ptr_struct, FILE *fd)
{
	reg_access_gpu_gplid_print(ptr_struct, fd, 0);
}

void reg_access_gpu_gsguid_ext_pack(const struct reg_access_gpu_gsguid_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->system_guid_h);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->system_guid_l);
}

void reg_access_gpu_gsguid_ext_unpack(struct reg_access_gpu_gsguid_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 64;
	ptr_struct->system_guid_h = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->system_guid_l = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_gsguid_ext_print(const struct reg_access_gpu_gsguid_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_gsguid_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "system_guid_h        : " U32H_FMT "\n", ptr_struct->system_guid_h);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "system_guid_l        : " U32H_FMT "\n", ptr_struct->system_guid_l);
}

unsigned int reg_access_gpu_gsguid_ext_size(void)
{
	return REG_ACCESS_GPU_GSGUID_EXT_SIZE;
}

void reg_access_gpu_gsguid_ext_dump(const struct reg_access_gpu_gsguid_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_gsguid_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mcam_reg_ext_pack(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 576, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 576, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mng_feature_cap_mask[i]);
	}
}

void reg_access_gpu_mcam_reg_ext_unpack(struct reg_access_gpu_mcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->feature_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 576, 1);
		ptr_struct->mng_access_reg_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 576, 1);
		ptr_struct->mng_feature_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mcam_reg_ext_print(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mcam_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : %s (" UH_FMT ")\n", (ptr_struct->access_reg_group == 0 ? ("First_128_REG_ID") : ((ptr_struct->access_reg_group == 1 ? ("Register_IDs_0x9080") : ((ptr_struct->access_reg_group == 2 ? ("Register_IDs_0x9100") : ((ptr_struct->access_reg_group == 3 ? ("Register_IDs_0x9180") : ("unknown")))))))), ptr_struct->access_reg_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "feature_group        : %s (" UH_FMT ")\n", (ptr_struct->feature_group == 0 ? ("enhanced_features") : ("unknown")), ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_access_reg_cap_mask_%03d : %s (" U32H_FMT ")\n", i, (ptr_struct->mng_access_reg_cap_mask[i] == 2 ? ("MFCR_0x9001") : ((ptr_struct->mng_access_reg_cap_mask[i] == 4 ? ("MFSC_0x9002") : ((ptr_struct->mng_access_reg_cap_mask[i] == 8 ? ("MFSM_0x9003") : ((ptr_struct->mng_access_reg_cap_mask[i] == 16 ? ("MFSL_0x9004") : ((ptr_struct->mng_access_reg_cap_mask[i] == 67108864 ? ("MGCR_0x903A") : ((ptr_struct->mng_access_reg_cap_mask[i] == 512 ? ("MPPF_0x9049") : ((ptr_struct->mng_access_reg_cap_mask[i] == 2147483648 ? ("MCAP_0x907F") : ("unknown")))))))))))))), ptr_struct->mng_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "mng_feature_cap_mask_%03d : " U32H_FMT "\n", i, ptr_struct->mng_feature_cap_mask[i]);
	}
}

unsigned int reg_access_gpu_mcam_reg_ext_size(void)
{
	return REG_ACCESS_GPU_MCAM_REG_EXT_SIZE;
}

void reg_access_gpu_mcam_reg_ext_dump(const struct reg_access_gpu_mcam_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mcam_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mcia_ext_pack(const struct reg_access_gpu_mcia_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pnv);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->device_address);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->page_number);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->i2c_device_address);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->bank_number);
	offset = 67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->passwd_length);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->password);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1184, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->dword[i]);
	}
	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->password_msb);
}

void reg_access_gpu_mcia_ext_unpack(struct reg_access_gpu_mcia_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 2;
	ptr_struct->pnv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->l = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->device_address = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 40;
	ptr_struct->page_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->i2c_device_address = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 72;
	ptr_struct->bank_number = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 67;
	ptr_struct->passwd_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->password = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 1184, 1);
		ptr_struct->dword[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 1152;
	ptr_struct->password_msb = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mcia_ext_print(const struct reg_access_gpu_mcia_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mcia_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnv                  : " UH_FMT "\n", ptr_struct->pnv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l                    : " UH_FMT "\n", ptr_struct->l);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_address       : " UH_FMT "\n", ptr_struct->device_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_number          : " UH_FMT "\n", ptr_struct->page_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "i2c_device_address   : " UH_FMT "\n", ptr_struct->i2c_device_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "size                 : " UH_FMT "\n", ptr_struct->size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bank_number          : " UH_FMT "\n", ptr_struct->bank_number);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "passwd_length        : " UH_FMT "\n", ptr_struct->passwd_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "password             : " U32H_FMT "\n", ptr_struct->password);
	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "dword_%03d           : " U32H_FMT "\n", i, ptr_struct->dword[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "password_msb         : " U32H_FMT "\n", ptr_struct->password_msb);
}

unsigned int reg_access_gpu_mcia_ext_size(void)
{
	return REG_ACCESS_GPU_MCIA_EXT_SIZE;
}

void reg_access_gpu_mcia_ext_dump(const struct reg_access_gpu_mcia_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mcia_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mcion_ext_pack(const struct reg_access_gpu_mcion_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->module_status_bits);
	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_inputs);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->module_status_bits_valid);
}

void reg_access_gpu_mcion_ext_unpack(struct reg_access_gpu_mcion_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->module_status_bits = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 124;
	ptr_struct->module_inputs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->module_status_bits_valid = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_mcion_ext_print(const struct reg_access_gpu_mcion_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mcion_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_status_bits   : " UH_FMT "\n", ptr_struct->module_status_bits);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_inputs        : " UH_FMT "\n", ptr_struct->module_inputs);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_status_bits_valid : " UH_FMT "\n", ptr_struct->module_status_bits_valid);
}

unsigned int reg_access_gpu_mcion_ext_size(void)
{
	return REG_ACCESS_GPU_MCION_EXT_SIZE;
}

void reg_access_gpu_mcion_ext_dump(const struct reg_access_gpu_mcion_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mcion_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mcsr_pack(const struct reg_access_gpu_mcsr *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->base_address);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->num_addresses);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 640, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->data[i]);
	}
}

void reg_access_gpu_mcsr_unpack(struct reg_access_gpu_mcsr *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 32;
	ptr_struct->base_address = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 87;
	ptr_struct->num_addresses = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 640, 1);
		ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mcsr_print(const struct reg_access_gpu_mcsr *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mcsr ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "base_address         : " U32H_FMT "\n", ptr_struct->base_address);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_addresses        : " UH_FMT "\n", ptr_struct->num_addresses);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "data_%03d            : " U32H_FMT "\n", i, ptr_struct->data[i]);
	}
}

unsigned int reg_access_gpu_mcsr_size(void)
{
	return REG_ACCESS_GPU_MCSR_SIZE;
}

void reg_access_gpu_mcsr_dump(const struct reg_access_gpu_mcsr *ptr_struct, FILE *fd)
{
	reg_access_gpu_mcsr_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mdrcr_ext_pack(const struct reg_access_gpu_mdrcr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->device_type);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->device_index);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->all);
	offset = 125;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->rst_op);
	offset = 108;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rst_status);
}

void reg_access_gpu_mdrcr_ext_unpack(struct reg_access_gpu_mdrcr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->device_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 52;
	ptr_struct->device_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 32;
	ptr_struct->all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 125;
	ptr_struct->rst_op = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 108;
	ptr_struct->rst_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mdrcr_ext_print(const struct reg_access_gpu_mdrcr_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mdrcr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_type          : " UH_FMT "\n", ptr_struct->device_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "device_index         : " UH_FMT "\n", ptr_struct->device_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "all                  : " UH_FMT "\n", ptr_struct->all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst_op               : " UH_FMT "\n", ptr_struct->rst_op);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst_status           : " UH_FMT "\n", ptr_struct->rst_status);
}

unsigned int reg_access_gpu_mdrcr_ext_size(void)
{
	return REG_ACCESS_GPU_MDRCR_EXT_SIZE;
}

void reg_access_gpu_mdrcr_ext_dump(const struct reg_access_gpu_mdrcr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mdrcr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mgir_ext_pack(const struct reg_access_gpu_mgir_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_gpu_mgir_hardware_info_ext_pack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_gpu_mgir_fw_info_ext_pack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_gpu_mgir_sw_info_ext_pack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_gpu_mgir_dev_info_ext_pack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_gpu_mgir_ext_unpack(struct reg_access_gpu_mgir_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 0;
	reg_access_gpu_mgir_hardware_info_ext_unpack(&(ptr_struct->hw_info), ptr_buff + offset / 8);
	offset = 256;
	reg_access_gpu_mgir_fw_info_ext_unpack(&(ptr_struct->fw_info), ptr_buff + offset / 8);
	offset = 768;
	reg_access_gpu_mgir_sw_info_ext_unpack(&(ptr_struct->sw_info), ptr_buff + offset / 8);
	offset = 1024;
	reg_access_gpu_mgir_dev_info_ext_unpack(&(ptr_struct->dev_info), ptr_buff + offset / 8);
}

void reg_access_gpu_mgir_ext_print(const struct reg_access_gpu_mgir_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mgir_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hw_info:\n");
	reg_access_gpu_mgir_hardware_info_ext_print(&(ptr_struct->hw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_info:\n");
	reg_access_gpu_mgir_fw_info_ext_print(&(ptr_struct->fw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_info:\n");
	reg_access_gpu_mgir_sw_info_ext_print(&(ptr_struct->sw_info), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dev_info:\n");
	reg_access_gpu_mgir_dev_info_ext_print(&(ptr_struct->dev_info), fd, indent_level + 1);
}

unsigned int reg_access_gpu_mgir_ext_size(void)
{
	return REG_ACCESS_GPU_MGIR_EXT_SIZE;
}

void reg_access_gpu_mgir_ext_dump(const struct reg_access_gpu_mgir_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mgir_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mmdio_ext_pack(const struct reg_access_gpu_mmdio_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->mdio_index);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->reg_adr);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->phy_adr);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->address);
}

void reg_access_gpu_mmdio_ext_unpack(struct reg_access_gpu_mmdio_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 22;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 12;
	ptr_struct->mdio_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 59;
	ptr_struct->reg_adr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 51;
	ptr_struct->phy_adr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 80;
	ptr_struct->data = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->address = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_mmdio_ext_print(const struct reg_access_gpu_mmdio_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mmdio_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operation            : " UH_FMT "\n", ptr_struct->operation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clause               : " UH_FMT "\n", ptr_struct->clause);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdio_index           : " UH_FMT "\n", ptr_struct->mdio_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "reg_adr              : " UH_FMT "\n", ptr_struct->reg_adr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_adr              : " UH_FMT "\n", ptr_struct->phy_adr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data                 : " UH_FMT "\n", ptr_struct->data);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "address              : " UH_FMT "\n", ptr_struct->address);
}

unsigned int reg_access_gpu_mmdio_ext_size(void)
{
	return REG_ACCESS_GPU_MMDIO_EXT_SIZE;
}

void reg_access_gpu_mmdio_ext_dump(const struct reg_access_gpu_mmdio_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mmdio_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mpscr_ext_pack(const struct reg_access_gpu_mpscr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->warning_inactive_time);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->warning_active_time);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->critical_inactive_time);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->critical_active_time);
	offset = 159;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cc);
}

void reg_access_gpu_mpscr_ext_unpack(struct reg_access_gpu_mpscr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 56;
	ptr_struct->warning_inactive_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 40;
	ptr_struct->warning_active_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->critical_inactive_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->critical_active_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 159;
	ptr_struct->cc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_mpscr_ext_print(const struct reg_access_gpu_mpscr_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mpscr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "warning_inactive_time : " UH_FMT "\n", ptr_struct->warning_inactive_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "warning_active_time  : " UH_FMT "\n", ptr_struct->warning_active_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "critical_inactive_time : " UH_FMT "\n", ptr_struct->critical_inactive_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "critical_active_time : " UH_FMT "\n", ptr_struct->critical_active_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cc                   : " UH_FMT "\n", ptr_struct->cc);
}

unsigned int reg_access_gpu_mpscr_ext_size(void)
{
	return REG_ACCESS_GPU_MPSCR_EXT_SIZE;
}

void reg_access_gpu_mpscr_ext_dump(const struct reg_access_gpu_mpscr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mpscr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtcap_ext_pack(const struct reg_access_gpu_mtcap_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->sensor_count);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 57;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->internal_sensor_count);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->sensor_map);
}

void reg_access_gpu_mtcap_ext_unpack(struct reg_access_gpu_mtcap_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 25;
	ptr_struct->sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 12;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 57;
	ptr_struct->internal_sensor_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);
	offset = 64;
	ptr_struct->sensor_map = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_mtcap_ext_print(const struct reg_access_gpu_mtcap_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtcap_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_count         : " UH_FMT "\n", ptr_struct->sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "internal_sensor_count : " UH_FMT "\n", ptr_struct->internal_sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_map           : " U64H_FMT "\n", ptr_struct->sensor_map);
}

unsigned int reg_access_gpu_mtcap_ext_size(void)
{
	return REG_ACCESS_GPU_MTCAP_EXT_SIZE;
}

void reg_access_gpu_mtcap_ext_dump(const struct reg_access_gpu_mtcap_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtcap_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtecr_ext_pack(const struct reg_access_gpu_mtecr_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_gpu_mtecr_ext_unpack(struct reg_access_gpu_mtecr_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_gpu_mtecr_ext_print(const struct reg_access_gpu_mtecr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtecr_ext ========\n");

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

unsigned int reg_access_gpu_mtecr_ext_size(void)
{
	return REG_ACCESS_GPU_MTECR_EXT_SIZE;
}

void reg_access_gpu_mtecr_ext_dump(const struct reg_access_gpu_mtecr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtecr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mteim_reg_ext_pack(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_tile);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_main);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_core_dpa);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cap_num_of_tile);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_tile);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_main);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type_core_dpa);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_phy_uc_supported);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_dwsn_msb_supported);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_dpa_core_event_id);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_main_core_event_id);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 384, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_tile_core_event_id[i]);
	}
}

void reg_access_gpu_mteim_reg_ext_unpack(struct reg_access_gpu_mteim_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->cap_core_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 16;
	ptr_struct->cap_core_main = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 8;
	ptr_struct->cap_core_dpa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->cap_num_of_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->type_core_tile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->type_core_main = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->type_core_dpa = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 33;
	ptr_struct->is_phy_uc_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->is_dwsn_msb_supported = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 72;
	ptr_struct->first_dpa_core_event_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->first_main_core_event_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(120, 8, i, 384, 1);
		ptr_struct->first_tile_core_event_id[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_gpu_mteim_reg_ext_print(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mteim_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_tile        : " UH_FMT "\n", ptr_struct->cap_core_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_main        : " UH_FMT "\n", ptr_struct->cap_core_main);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_core_dpa         : " UH_FMT "\n", ptr_struct->cap_core_dpa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cap_num_of_tile      : " UH_FMT "\n", ptr_struct->cap_num_of_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_tile       : " UH_FMT "\n", ptr_struct->type_core_tile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_main       : " UH_FMT "\n", ptr_struct->type_core_main);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type_core_dpa        : " UH_FMT "\n", ptr_struct->type_core_dpa);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_phy_uc_supported  : " UH_FMT "\n", ptr_struct->is_phy_uc_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "is_dwsn_msb_supported : " UH_FMT "\n", ptr_struct->is_dwsn_msb_supported);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_dpa_core_event_id : " UH_FMT "\n", ptr_struct->first_dpa_core_event_id);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_main_core_event_id : " UH_FMT "\n", ptr_struct->first_main_core_event_id);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "first_tile_core_event_id_%03d : " UH_FMT "\n", i, ptr_struct->first_tile_core_event_id[i]);
	}
}

unsigned int reg_access_gpu_mteim_reg_ext_size(void)
{
	return REG_ACCESS_GPU_MTEIM_REG_EXT_SIZE;
}

void reg_access_gpu_mteim_reg_ext_dump(const struct reg_access_gpu_mteim_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mteim_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtewe_ext_pack(const struct reg_access_gpu_mtewe_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_count);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->last_sensor);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 736, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_warning[i]);
	}
}

void reg_access_gpu_mtewe_ext_unpack(struct reg_access_gpu_mtewe_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 20;
	ptr_struct->sensor_count = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 16;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 4;
	ptr_struct->last_sensor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 736, 1);
		ptr_struct->sensor_warning[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mtewe_ext_print(const struct reg_access_gpu_mtewe_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtewe_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_count         : " UH_FMT "\n", ptr_struct->sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_sensor          : " UH_FMT "\n", ptr_struct->last_sensor);
	for (i = 0; i < 22; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sensor_warning_%03d  : " U32H_FMT "\n", i, ptr_struct->sensor_warning[i]);
	}
}

unsigned int reg_access_gpu_mtewe_ext_size(void)
{
	return REG_ACCESS_GPU_MTEWE_EXT_SIZE;
}

void reg_access_gpu_mtewe_ext_dump(const struct reg_access_gpu_mtewe_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtewe_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtie_ext_pack(const struct reg_access_gpu_mtie_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->enable_all);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->log_delay);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->source_id_bitmask[i]);
	}
}

void reg_access_gpu_mtie_ext_unpack(struct reg_access_gpu_mtie_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	ptr_struct->enable_all = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 48;
	ptr_struct->log_delay = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 384, 1);
		ptr_struct->source_id_bitmask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mtie_ext_print(const struct reg_access_gpu_mtie_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtie_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "enable_all           : " UH_FMT "\n", ptr_struct->enable_all);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_delay            : " UH_FMT "\n", ptr_struct->log_delay);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "source_id_bitmask_%03d : " U32H_FMT "\n", i, ptr_struct->source_id_bitmask[i]);
	}
}

unsigned int reg_access_gpu_mtie_ext_size(void)
{
	return REG_ACCESS_GPU_MTIE_EXT_SIZE;
}

void reg_access_gpu_mtie_ext_dump(const struct reg_access_gpu_mtie_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtie_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtim_ext_pack(const struct reg_access_gpu_mtim_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_level);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_bit_mask);
}

void reg_access_gpu_mtim_ext_unpack(struct reg_access_gpu_mtim_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->log_level = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->log_bit_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mtim_ext_print(const struct reg_access_gpu_mtim_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtim_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_level            : " UH_FMT "\n", ptr_struct->log_level);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_bit_mask         : " U32H_FMT "\n", ptr_struct->log_bit_mask);
}

unsigned int reg_access_gpu_mtim_ext_size(void)
{
	return REG_ACCESS_GPU_MTIM_EXT_SIZE;
}

void reg_access_gpu_mtim_ext_dump(const struct reg_access_gpu_mtim_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtim_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtmp_ext_pack(const struct reg_access_gpu_mtmp_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->sensor_index);
	offset = 12;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_temperature);
	offset = 67;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sdme);
	offset = 66;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->weme);
	offset = 65;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mtr);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mte);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_hi);
	offset = 98;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->sdee);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tee);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->temperature_threshold_lo);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_name_hi);
	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_name_lo);
}

void reg_access_gpu_mtmp_ext_unpack(struct reg_access_gpu_mtmp_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 20;
	ptr_struct->sensor_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 12;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 80;
	ptr_struct->max_temperature = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 67;
	ptr_struct->sdme = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 66;
	ptr_struct->weme = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 65;
	ptr_struct->mtr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->mte = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 112;
	ptr_struct->temperature_threshold_hi = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 98;
	ptr_struct->sdee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 96;
	ptr_struct->tee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 144;
	ptr_struct->temperature_threshold_lo = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->sensor_name_hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 224;
	ptr_struct->sensor_name_lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mtmp_ext_print(const struct reg_access_gpu_mtmp_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtmp_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_index         : " UH_FMT "\n", ptr_struct->sensor_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature          : " UH_FMT "\n", ptr_struct->temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_temperature      : " UH_FMT "\n", ptr_struct->max_temperature);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdme                 : " UH_FMT "\n", ptr_struct->sdme);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "weme                 : " UH_FMT "\n", ptr_struct->weme);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtr                  : " UH_FMT "\n", ptr_struct->mtr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mte                  : " UH_FMT "\n", ptr_struct->mte);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_hi : " UH_FMT "\n", ptr_struct->temperature_threshold_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sdee                 : " UH_FMT "\n", ptr_struct->sdee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tee                  : %s (" UH_FMT ")\n", (ptr_struct->tee == 0 ? ("do_not_generate_event") : ((ptr_struct->tee == 1 ? ("generate_event") : ((ptr_struct->tee == 2 ? ("generate_single_event") : ("unknown")))))), ptr_struct->tee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "temperature_threshold_lo : " UH_FMT "\n", ptr_struct->temperature_threshold_lo);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_name_hi       : " U32H_FMT "\n", ptr_struct->sensor_name_hi);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_name_lo       : " U32H_FMT "\n", ptr_struct->sensor_name_lo);
}

unsigned int reg_access_gpu_mtmp_ext_size(void)
{
	return REG_ACCESS_GPU_MTMP_EXT_SIZE;
}

void reg_access_gpu_mtmp_ext_dump(const struct reg_access_gpu_mtmp_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtmp_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtrc_cap_reg_ext_pack(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->num_string_db);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->trc_ver);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->trace_to_memory);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->trace_owner);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_string_trace);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->first_string_trace);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_max_trace_buffer_size);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tracer_capabilities);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1056, 1);
		reg_access_gpu_string_db_parameters_ext_pack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_mtrc_cap_reg_ext_unpack(struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 28;
	ptr_struct->num_string_db = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 6;
	ptr_struct->trc_ver = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 1;
	ptr_struct->trace_to_memory = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->trace_owner = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 40;
	ptr_struct->num_string_trace = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 32;
	ptr_struct->first_string_trace = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->log_max_trace_buffer_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->tracer_capabilities = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	for (i = 0; i < 8; ++i) {
		offset = adb2c_calc_array_field_address(128, 64, i, 1056, 1);
		reg_access_gpu_string_db_parameters_ext_unpack(&(ptr_struct->string_db_param[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_mtrc_cap_reg_ext_print(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtrc_cap_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_string_db        : " UH_FMT "\n", ptr_struct->num_string_db);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trc_ver              : " UH_FMT "\n", ptr_struct->trc_ver);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_to_memory      : " UH_FMT "\n", ptr_struct->trace_to_memory);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_owner          : " UH_FMT "\n", ptr_struct->trace_owner);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_string_trace     : " UH_FMT "\n", ptr_struct->num_string_trace);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "first_string_trace   : " UH_FMT "\n", ptr_struct->first_string_trace);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_max_trace_buffer_size : " UH_FMT "\n", ptr_struct->log_max_trace_buffer_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tracer_capabilities  : " UH_FMT "\n", ptr_struct->tracer_capabilities);
	for (i = 0; i < 8; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "string_db_param_%03d:\n", i);
		reg_access_gpu_string_db_parameters_ext_print(&(ptr_struct->string_db_param[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_gpu_mtrc_cap_reg_ext_size(void)
{
	return REG_ACCESS_GPU_MTRC_CAP_REG_EXT_SIZE;
}

void reg_access_gpu_mtrc_cap_reg_ext_dump(const struct reg_access_gpu_mtrc_cap_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtrc_cap_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtrc_conf_reg_ext_pack(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->trace_mode);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->log_trace_buffer_size);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->trace_mkey);
}

void reg_access_gpu_mtrc_conf_reg_ext_unpack(struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->trace_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->log_trace_buffer_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 64;
	ptr_struct->trace_mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mtrc_conf_reg_ext_print(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtrc_conf_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_mode           : " UH_FMT "\n", ptr_struct->trace_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_trace_buffer_size : " UH_FMT "\n", ptr_struct->log_trace_buffer_size);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_mkey           : " U32H_FMT "\n", ptr_struct->trace_mkey);
}

unsigned int reg_access_gpu_mtrc_conf_reg_ext_size(void)
{
	return REG_ACCESS_GPU_MTRC_CONF_REG_EXT_SIZE;
}

void reg_access_gpu_mtrc_conf_reg_ext_dump(const struct reg_access_gpu_mtrc_conf_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtrc_conf_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtrc_ctrl_reg_ext_pack(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->modify_field_select);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->arm_event);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->trace_status);
	offset = 75;
	adb2c_push_bits_to_buff(ptr_buff, offset, 21, (u_int32_t)ptr_struct->current_timestamp_52_32);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->current_timestamp_31_0);
}

void reg_access_gpu_mtrc_ctrl_reg_ext_unpack(struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 16;
	ptr_struct->modify_field_select = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 4;
	ptr_struct->arm_event = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->trace_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 75;
	ptr_struct->current_timestamp_52_32 = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 21);
	offset = 96;
	ptr_struct->current_timestamp_31_0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_mtrc_ctrl_reg_ext_print(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtrc_ctrl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modify_field_select  : " UH_FMT "\n", ptr_struct->modify_field_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "arm_event            : " UH_FMT "\n", ptr_struct->arm_event);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "trace_status         : " UH_FMT "\n", ptr_struct->trace_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_timestamp_52_32 : " UH_FMT "\n", ptr_struct->current_timestamp_52_32);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "current_timestamp_31_0 : " U32H_FMT "\n", ptr_struct->current_timestamp_31_0);
}

unsigned int reg_access_gpu_mtrc_ctrl_reg_ext_size(void)
{
	return REG_ACCESS_GPU_MTRC_CTRL_REG_EXT_SIZE;
}

void reg_access_gpu_mtrc_ctrl_reg_ext_dump(const struct reg_access_gpu_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtrc_ctrl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtsde_pack(const struct reg_access_gpu_mtsde *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->sensor_count);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->last_sensor);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 736, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_shut_down_map[i]);
	}
}

void reg_access_gpu_mtsde_unpack(struct reg_access_gpu_mtsde *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 22;
	ptr_struct->sensor_count = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 16;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 6;
	ptr_struct->last_sensor = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	for (i = 0; i < 22; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 736, 1);
		ptr_struct->sensor_shut_down_map[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mtsde_print(const struct reg_access_gpu_mtsde *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtsde ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sensor_count         : " UH_FMT "\n", ptr_struct->sensor_count);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "last_sensor          : " UH_FMT "\n", ptr_struct->last_sensor);
	for (i = 0; i < 22; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sensor_shut_down_map_%03d : " U32H_FMT "\n", i, ptr_struct->sensor_shut_down_map[i]);
	}
}

unsigned int reg_access_gpu_mtsde_size(void)
{
	return REG_ACCESS_GPU_MTSDE_SIZE;
}

void reg_access_gpu_mtsde_dump(const struct reg_access_gpu_mtsde *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtsde_print(ptr_struct, fd, 0);
}

void reg_access_gpu_mtwe_ext_pack(const struct reg_access_gpu_mtwe_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sensor_warning[i]);
	}
}

void reg_access_gpu_mtwe_ext_unpack(struct reg_access_gpu_mtwe_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 128, 1);
		ptr_struct->sensor_warning[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_mtwe_ext_print(const struct reg_access_gpu_mtwe_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_mtwe_ext ========\n");

	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "sensor_warning_%03d  : " U32H_FMT "\n", i, ptr_struct->sensor_warning[i]);
	}
}

unsigned int reg_access_gpu_mtwe_ext_size(void)
{
	return REG_ACCESS_GPU_MTWE_EXT_SIZE;
}

void reg_access_gpu_mtwe_ext_dump(const struct reg_access_gpu_mtwe_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_mtwe_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_paos_reg_ext_pack(const struct reg_access_gpu_paos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->e);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->physical_state_status);
	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fd);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sleep_cap);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ps_e);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->logical_state_status);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ls_e);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_ps);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_ls);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
}

void reg_access_gpu_paos_reg_ext_unpack(struct reg_access_gpu_paos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 62;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 56;
	ptr_struct->physical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 55;
	ptr_struct->fd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 54;
	ptr_struct->sleep_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->ps_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 45;
	ptr_struct->logical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 40;
	ptr_struct->ls_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 35;
	ptr_struct->ee_ps = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->ee_ls = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_paos_reg_ext_print(const struct reg_access_gpu_paos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_paos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 1 ? ("up") : ((ptr_struct->oper_status == 2 ? ("down") : ((ptr_struct->oper_status == 4 ? ("down_by_port_failure") : ("unknown")))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("up") : ((ptr_struct->admin_status == 2 ? ("down_by_configuration") : ((ptr_struct->admin_status == 4 ? ("disabled_by_system") : ((ptr_struct->admin_status == 6 ? ("sleep") : ("unknown")))))))), ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : %s (" UH_FMT ")\n", (ptr_struct->e == 0 ? ("Do_not_generate_event") : ((ptr_struct->e == 1 ? ("Generate_Event") : ((ptr_struct->e == 2 ? ("Generate_Single_Event") : ("unknown")))))), ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "physical_state_status : %s (" UH_FMT ")\n", (ptr_struct->physical_state_status == 0 ? ("N_A") : ((ptr_struct->physical_state_status == 1 ? ("Sleep") : ((ptr_struct->physical_state_status == 2 ? ("Polling") : ((ptr_struct->physical_state_status == 3 ? ("Disabled") : ((ptr_struct->physical_state_status == 4 ? ("PortConfigurationTraining") : ((ptr_struct->physical_state_status == 5 ? ("LinkUp") : ("unknown")))))))))))), ptr_struct->physical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fd                   : " UH_FMT "\n", ptr_struct->fd);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sleep_cap            : " UH_FMT "\n", ptr_struct->sleep_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ps_e                 : %s (" UH_FMT ")\n", (ptr_struct->ps_e == 1 ? ("Sleep") : ((ptr_struct->ps_e == 4 ? ("Disabled") : ((ptr_struct->ps_e == 8 ? ("PortConfigurationTraining") : ("unknown")))))), ptr_struct->ps_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "logical_state_status : %s (" UH_FMT ")\n", (ptr_struct->logical_state_status == 0 ? ("N_A") : ((ptr_struct->logical_state_status == 1 ? ("Down") : ((ptr_struct->logical_state_status == 2 ? ("Init") : ((ptr_struct->logical_state_status == 3 ? ("Arm") : ((ptr_struct->logical_state_status == 4 ? ("Active") : ("unknown")))))))))), ptr_struct->logical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ls_e                 : %s (" UH_FMT ")\n", (ptr_struct->ls_e == 1 ? ("Down") : ((ptr_struct->ls_e == 2 ? ("Init") : ((ptr_struct->ls_e == 4 ? ("Arm") : ((ptr_struct->ls_e == 8 ? ("Active") : ("unknown")))))))), ptr_struct->ls_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_ps                : " UH_FMT "\n", ptr_struct->ee_ps);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_ls                : " UH_FMT "\n", ptr_struct->ee_ls);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
}

unsigned int reg_access_gpu_paos_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PAOS_REG_EXT_SIZE;
}

void reg_access_gpu_paos_reg_ext_dump(const struct reg_access_gpu_paos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_paos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pbsr_reg_ext_pack(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->buffer_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->clear_wm_buff_mask);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->used_shared_headroom_buffer);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clear_wm);
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(96, 64, i, 800, 1);
		reg_access_gpu_stat_bufferx_reg_ext_pack(&(ptr_struct->stat_buffer[i]), ptr_buff + offset / 8);
	}
	offset = 736;
	reg_access_gpu_stat_bufferx_reg_ext_pack(&(ptr_struct->stat_shared_headroom_pool), ptr_buff + offset / 8);
}

void reg_access_gpu_pbsr_reg_ext_unpack(struct reg_access_gpu_pbsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 30;
	ptr_struct->buffer_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 54;
	ptr_struct->clear_wm_buff_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 80;
	ptr_struct->used_shared_headroom_buffer = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->clear_wm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 10; ++i) {
		offset = adb2c_calc_array_field_address(96, 64, i, 800, 1);
		reg_access_gpu_stat_bufferx_reg_ext_unpack(&(ptr_struct->stat_buffer[i]), ptr_buff + offset / 8);
	}
	offset = 736;
	reg_access_gpu_stat_bufferx_reg_ext_unpack(&(ptr_struct->stat_shared_headroom_pool), ptr_buff + offset / 8);
}

void reg_access_gpu_pbsr_reg_ext_print(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pbsr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "buffer_type          : " UH_FMT "\n", ptr_struct->buffer_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clear_wm_buff_mask   : " UH_FMT "\n", ptr_struct->clear_wm_buff_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "used_shared_headroom_buffer : " UH_FMT "\n", ptr_struct->used_shared_headroom_buffer);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clear_wm             : " UH_FMT "\n", ptr_struct->clear_wm);
	for (i = 0; i < 10; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "stat_buffer_%03d:\n", i);
		reg_access_gpu_stat_bufferx_reg_ext_print(&(ptr_struct->stat_buffer[i]), fd, indent_level + 1);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stat_shared_headroom_pool:\n");
	reg_access_gpu_stat_bufferx_reg_ext_print(&(ptr_struct->stat_shared_headroom_pool), fd, indent_level + 1);
}

unsigned int reg_access_gpu_pbsr_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PBSR_REG_EXT_SIZE;
}

void reg_access_gpu_pbsr_reg_ext_dump(const struct reg_access_gpu_pbsr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pbsr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pbwc_ext_pack(const struct reg_access_gpu_pbwc_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_time_interval);
	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->alpha_factor);
}

void reg_access_gpu_pbwc_ext_unpack(struct reg_access_gpu_pbwc_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->log_time_interval = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 61;
	ptr_struct->alpha_factor = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
}

void reg_access_gpu_pbwc_ext_print(const struct reg_access_gpu_pbwc_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pbwc_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "log_time_interval    : " UH_FMT "\n", ptr_struct->log_time_interval);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "alpha_factor         : " UH_FMT "\n", ptr_struct->alpha_factor);
}

unsigned int reg_access_gpu_pbwc_ext_size(void)
{
	return REG_ACCESS_GPU_PBWC_EXT_SIZE;
}

void reg_access_gpu_pbwc_ext_dump(const struct reg_access_gpu_pbwc_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pbwc_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pbwr_ext_pack(const struct reg_access_gpu_pbwr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1184, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->local_port_bitmap[i]);
	}
	offset = 1045;
	adb2c_push_bits_to_buff(ptr_buff, offset, 11, (u_int32_t)ptr_struct->num_rec);
	offset = 1024;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dir);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->num_rec / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(1152, 32, i, (item_size_in_bytes * num_of_items_in_array) + (reg_access_gpu_pbwr_ext_size() * 8), 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->bw_record[i]);
	}
}

void reg_access_gpu_pbwr_ext_unpack(struct reg_access_gpu_pbwr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	for (i = 0; i < 32; ++i) {
		offset = adb2c_calc_array_field_address(0, 32, i, 1184, 1);
		ptr_struct->local_port_bitmap[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	offset = 1045;
	ptr_struct->num_rec = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 11);
	offset = 1024;
	ptr_struct->dir = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->num_rec / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		offset = adb2c_calc_array_field_address(1152, 32, i, (item_size_in_bytes * num_of_items_in_array) + (reg_access_gpu_pbwr_ext_size() * 8), 1);
		ptr_struct->bw_record[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_pbwr_ext_print(const struct reg_access_gpu_pbwr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pbwr_ext ========\n");

	for (i = 0; i < 32; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "local_port_bitmap_%03d : " U32H_FMT "\n", i, ptr_struct->local_port_bitmap[i]);
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_rec              : " UH_FMT "\n", ptr_struct->num_rec);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dir                  : %s (" UH_FMT ")\n", (ptr_struct->dir == 0 ? ("ingress") : ((ptr_struct->dir == 1 ? ("egress") : ("unknown")))), ptr_struct->dir);
	int item_size_in_bytes = 4;
	int num_of_items_in_array = (int)ptr_struct->num_rec / item_size_in_bytes;
	for (i = 0; i < num_of_items_in_array; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "bw_record_%03d       : " U32H_FMT "\n", i, ptr_struct->bw_record[i]);
	}
}

unsigned int reg_access_gpu_pbwr_ext_size(void)
{
	return REG_ACCESS_GPU_PBWR_EXT_SIZE;
}

void reg_access_gpu_pbwr_ext_dump(const struct reg_access_gpu_pbwr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pbwr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pcam_reg_ext_pack(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->access_reg_group);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pl_op);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 640, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 640, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->feature_cap_mask[i]);
	}
}

void reg_access_gpu_pcam_reg_ext_unpack(struct reg_access_gpu_pcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 24;
	ptr_struct->access_reg_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 23;
	ptr_struct->pl_op = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->feature_group = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(64, 32, i, 640, 1);
		ptr_struct->port_access_reg_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(320, 32, i, 640, 1);
		ptr_struct->feature_cap_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_pcam_reg_ext_print(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pcam_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "access_reg_group     : " UH_FMT "\n", ptr_struct->access_reg_group);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pl_op                : %s (" UH_FMT ")\n", (ptr_struct->pl_op == 0 ? ("aggregated_port_access") : ((ptr_struct->pl_op == 1 ? ("plane_port_access") : ("unknown")))), ptr_struct->pl_op);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "feature_group        : %s (" UH_FMT ")\n", (ptr_struct->feature_group == 0 ? ("enhanced_features") : ("unknown")), ptr_struct->feature_group);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "port_access_reg_cap_mask_%03d : " U32H_FMT "\n", i, ptr_struct->port_access_reg_cap_mask[i]);
	}
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "feature_cap_mask_%03d : %s (" U32H_FMT ")\n", i, (ptr_struct->feature_cap_mask[i] == 1 ? ("PPCNT_counter_group_Phy_statistical_counter_group") : ((ptr_struct->feature_cap_mask[i] == 512 ? ("PFCC") : ((ptr_struct->feature_cap_mask[i] == 1024 ? ("PMCR") : ((ptr_struct->feature_cap_mask[i] == 2048 ? ("PPCNT_counter_group") : ((ptr_struct->feature_cap_mask[i] == 4096 ? ("PPCNT_Extended_Ethernet_group") : ((ptr_struct->feature_cap_mask[i] == 8192 ? ("PTYS_extended_Ethernet_support") : ((ptr_struct->feature_cap_mask[i] == 16384 ? ("PMAOS_reset_toggle_support") : ((ptr_struct->feature_cap_mask[i] == 32768 ? ("Set_Module_low_power_supported") : ((ptr_struct->feature_cap_mask[i] == 65536 ? ("Module_power_optimization_is_supported_in_PPSC") : ((ptr_struct->feature_cap_mask[i] == 131072 ? ("Support_of_IB_force_state_machine_in_PTYS") : ((ptr_struct->feature_cap_mask[i] == 262144 ? ("PPCNT_Extended_Ethernet_group_icrc_counter") : ((ptr_struct->feature_cap_mask[i] == 524288 ? ("cm2_en_is_supported_in_PCAP") : ((ptr_struct->feature_cap_mask[i] == 1048576 ? ("time_tolink_up_is_supported_in_PDDR") : ((ptr_struct->feature_cap_mask[i] == 2097152 ? ("gearbox_die_num_field_is_supported_in_PMDR") : ((ptr_struct->feature_cap_mask[i] == 4194304 ? ("force_entropy_entropy_calc_entropy_gre_calc") : ((ptr_struct->feature_cap_mask[i] == 8388608 ? ("FEC_override_support_for_50G_per_lane_is_supported_in_PPLM") : ((ptr_struct->feature_cap_mask[i] == 33554432 ? ("PTYS_allow_both_extended_and_legacy_protocol_masks") : ((ptr_struct->feature_cap_mask[i] == 67108864 ? ("PPCNT_eth_per_tc_cong_group_supported") : ((ptr_struct->feature_cap_mask[i] == 134217728 ? ("pnat_sup_host") : ((ptr_struct->feature_cap_mask[i] == 268435456 ? ("ppcnt_no_buffer_discard_uc") : ((ptr_struct->feature_cap_mask[i] == 536870912 ? ("pbmc_port_shared_buffer") : ((ptr_struct->feature_cap_mask[i] == 1073741824 ? ("PLR_max_retry_window_support") : ((ptr_struct->feature_cap_mask[i] == 1 ? ("PDDR_ext_eth_proto_support") : ((ptr_struct->feature_cap_mask[i] == 512 ? ("PMAOS") : ((ptr_struct->feature_cap_mask[i] == 1024 ? ("PRBS_polarity_support") : ((ptr_struct->feature_cap_mask[i] == 2048 ? ("PDDR_register_is_supported") : ((ptr_struct->feature_cap_mask[i] == 4096 ? ("pfcc_buffer_onwership") : ((ptr_struct->feature_cap_mask[i] == 8192 ? ("force_down") : ((ptr_struct->feature_cap_mask[i] == 16384 ? ("pmlp_lane_mapping_off") : ((ptr_struct->feature_cap_mask[i] == 524288 ? ("ppcnt_symobl_ber") : ((ptr_struct->feature_cap_mask[i] == 1048576 ? ("shp_pbmc_pbsr_support") : ((ptr_struct->feature_cap_mask[i] == 4194304 ? ("ppcnt_effective_error_counter") : ((ptr_struct->feature_cap_mask[i] == 8388608 ? ("FEC_override_support_for_100G_per_lane_is_supported_in_PPLM") : ((ptr_struct->feature_cap_mask[i] == 33554432 ? ("PMECR_option_to_not_generate_events_upon_PMLP_set") : ((ptr_struct->feature_cap_mask[i] == 1 ? ("Local_port_MSB") : ((ptr_struct->feature_cap_mask[i] == 2 ? ("PDDR_moule_latched_info_page_supported") : ((ptr_struct->feature_cap_mask[i] == 4 ? ("PDDR_module_info_ext_supported") : ((ptr_struct->feature_cap_mask[i] == 64 ? ("SLTP_tx_policy_supported") : ((ptr_struct->feature_cap_mask[i] == 128 ? ("pmcr_capability_bits_supported") : ((ptr_struct->feature_cap_mask[i] == 256 ? ("pmtu_max_admin_mtu_supported") : ((ptr_struct->feature_cap_mask[i] == 512 ? ("PPCNT_grp_profile_supported") : ((ptr_struct->feature_cap_mask[i] == 8192 ? ("PPCNT_physical_layer_counters_RS_FEC_8_lanes_supported") : ((ptr_struct->feature_cap_mask[i] == 2097152 ? ("PPCNT_counters_cap") : ((ptr_struct->feature_cap_mask[i] == 4194304 ? ("SLTP_lane_broadcast_supported") : ((ptr_struct->feature_cap_mask[i] == 8388608 ? ("PMMP_apply_im_supported") : ((ptr_struct->feature_cap_mask[i] == 134217728 ? ("SLRG_all_lanes_supported") : ((ptr_struct->feature_cap_mask[i] == 268435456 ? ("PIPG_ipg_oper_ipg_cap_idx_supported") : ((ptr_struct->feature_cap_mask[i] == 536870912 ? ("PPBMP_clr_supported") : ((ptr_struct->feature_cap_mask[i] == 1073741824 ? ("PIPG_dic1_1g_supported") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->feature_cap_mask[i]);
	}
}

unsigned int reg_access_gpu_pcam_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PCAM_REG_EXT_SIZE;
}

void reg_access_gpu_pcam_reg_ext_dump(const struct reg_access_gpu_pcam_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pcam_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pcap_reg_ext_pack(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cm2_en);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 160, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_capability_mask[i]);
	}
}

void reg_access_gpu_pcap_reg_ext_unpack(struct reg_access_gpu_pcap_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->cm2_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	for (i = 0; i < 4; ++i) {
		offset = adb2c_calc_array_field_address(32, 32, i, 160, 1);
		ptr_struct->port_capability_mask[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_pcap_reg_ext_print(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pcap_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cm2_en               : " UH_FMT "\n", ptr_struct->cm2_en);
	for (i = 0; i < 4; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "port_capability_mask_%03d : " U32H_FMT "\n", i, ptr_struct->port_capability_mask[i]);
	}
}

unsigned int reg_access_gpu_pcap_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PCAP_REG_EXT_SIZE;
}

void reg_access_gpu_pcap_reg_ext_dump(const struct reg_access_gpu_pcap_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pcap_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pddr_reg_ext_pack(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->page_select);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->module_info_ext);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x9:
		offset = 64;
		reg_access_gpu_module_latched_flag_info_ext_pack(&(ptr_struct->page_data.module_latched_flag_info_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_gpu_pddr_link_down_info_page_ext_pack(&(ptr_struct->page_data.pddr_link_down_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_gpu_pddr_module_info_ext_pack(&(ptr_struct->page_data.pddr_module_info_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_gpu_pddr_operation_info_page_ext_pack(&(ptr_struct->page_data.pddr_operation_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_gpu_pddr_phy_info_page_ext_pack(&(ptr_struct->page_data.pddr_phy_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_pddr_troubleshooting_page_ext_pack(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_pddr_reg_ext_unpack(struct reg_access_gpu_pddr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 56;
	ptr_struct->page_select = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 33;
	ptr_struct->module_info_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 64;
	switch (ptr_struct->page_select) {
	case 0x9:
		offset = 64;
		reg_access_gpu_module_latched_flag_info_ext_unpack(&(ptr_struct->page_data.module_latched_flag_info_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_gpu_pddr_link_down_info_page_ext_unpack(&(ptr_struct->page_data.pddr_link_down_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_gpu_pddr_module_info_ext_unpack(&(ptr_struct->page_data.pddr_module_info_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_gpu_pddr_operation_info_page_ext_unpack(&(ptr_struct->page_data.pddr_operation_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_gpu_pddr_phy_info_page_ext_unpack(&(ptr_struct->page_data.pddr_phy_info_page_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_pddr_troubleshooting_page_ext_unpack(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_pddr_reg_ext_print(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pddr_reg_ext ========\n");

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
	fprintf(fd, "page_select          : %s (" UH_FMT ")\n", (ptr_struct->page_select == 0 ? ("Operational_info_page") : ((ptr_struct->page_select == 1 ? ("Troubleshooting_info_page") : ((ptr_struct->page_select == 2 ? ("Phy_info_page") : ((ptr_struct->page_select == 3 ? ("Module_info_page") : ((ptr_struct->page_select == 6 ? ("link_down_info") : ((ptr_struct->page_select == 9 ? ("Module_latched_flag_info_page") : ("unknown")))))))))))), ptr_struct->page_select);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_info_ext      : %s (" UH_FMT ")\n", (ptr_struct->module_info_ext == 0 ? ("dbm") : ((ptr_struct->module_info_ext == 1 ? ("uW") : ("unknown")))), ptr_struct->module_info_ext);
	switch (ptr_struct->page_select) {
	case 0x9:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "module_latched_flag_info_ext:\n");
		reg_access_gpu_module_latched_flag_info_ext_print(&(ptr_struct->page_data.module_latched_flag_info_ext), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_link_down_info_page_ext:\n");
		reg_access_gpu_pddr_link_down_info_page_ext_print(&(ptr_struct->page_data.pddr_link_down_info_page_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_module_info_ext:\n");
		reg_access_gpu_pddr_module_info_ext_print(&(ptr_struct->page_data.pddr_module_info_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_operation_info_page_ext:\n");
		reg_access_gpu_pddr_operation_info_page_ext_print(&(ptr_struct->page_data.pddr_operation_info_page_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_phy_info_page_ext:\n");
		reg_access_gpu_pddr_phy_info_page_ext_print(&(ptr_struct->page_data.pddr_phy_info_page_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pddr_troubleshooting_page_ext:\n");
		reg_access_gpu_pddr_troubleshooting_page_ext_print(&(ptr_struct->page_data.pddr_troubleshooting_page_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_gpu_pddr_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PDDR_REG_EXT_SIZE;
}

void reg_access_gpu_pddr_reg_ext_dump(const struct reg_access_gpu_pddr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pddr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pevnt_ext_pack(const struct reg_access_gpu_pevnt_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_cont);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_cont);
}

void reg_access_gpu_pevnt_ext_unpack(struct reg_access_gpu_pevnt_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->rx_cont = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 62;
	ptr_struct->tx_cont = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_pevnt_ext_print(const struct reg_access_gpu_pevnt_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pevnt_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_cont              : " UH_FMT "\n", ptr_struct->rx_cont);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_cont              : " UH_FMT "\n", ptr_struct->tx_cont);
}

unsigned int reg_access_gpu_pevnt_ext_size(void)
{
	return REG_ACCESS_GPU_PEVNT_EXT_SIZE;
}

void reg_access_gpu_pevnt_ext_dump(const struct reg_access_gpu_pevnt_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pevnt_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pguid_reg_ext_pack(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_gpu_pguid_reg_ext_unpack(struct reg_access_gpu_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_gpu_pguid_reg_ext_print(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pguid_reg_ext ========\n");

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

unsigned int reg_access_gpu_pguid_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PGUID_REG_EXT_SIZE;
}

void reg_access_gpu_pguid_reg_ext_dump(const struct reg_access_gpu_pguid_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pguid_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_plib_reg_ext_pack(const struct reg_access_gpu_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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

void reg_access_gpu_plib_reg_ext_unpack(struct reg_access_gpu_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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

void reg_access_gpu_plib_reg_ext_print(const struct reg_access_gpu_plib_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_plib_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_port              : " UH_FMT "\n", ptr_struct->ib_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "split_num            : " UH_FMT "\n", ptr_struct->split_num);
}

unsigned int reg_access_gpu_plib_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PLIB_REG_EXT_SIZE;
}

void reg_access_gpu_plib_reg_ext_dump(const struct reg_access_gpu_plib_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_plib_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pltc_reg_ext_pack(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_mask);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->precoding_cap_mask);
	offset = 94;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_tx_precoding_admin);
	offset = 78;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_rx_precoding_admin);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_tx_precoding_oper);
	offset = 110;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->local_rx_precoding_oper);
}

void reg_access_gpu_pltc_reg_ext_unpack(struct reg_access_gpu_pltc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->precoding_cap_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 94;
	ptr_struct->local_tx_precoding_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 78;
	ptr_struct->local_rx_precoding_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 126;
	ptr_struct->local_tx_precoding_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 110;
	ptr_struct->local_rx_precoding_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
}

void reg_access_gpu_pltc_reg_ext_print(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pltc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_mask            : " UH_FMT "\n", ptr_struct->lane_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "precoding_cap_mask   : " UH_FMT "\n", ptr_struct->precoding_cap_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_tx_precoding_admin : " UH_FMT "\n", ptr_struct->local_tx_precoding_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_rx_precoding_admin : " UH_FMT "\n", ptr_struct->local_rx_precoding_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_tx_precoding_oper : " UH_FMT "\n", ptr_struct->local_tx_precoding_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_rx_precoding_oper : " UH_FMT "\n", ptr_struct->local_rx_precoding_oper);
}

unsigned int reg_access_gpu_pltc_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PLTC_REG_EXT_SIZE;
}

void reg_access_gpu_pltc_reg_ext_dump(const struct reg_access_gpu_pltc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pltc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmaos_reg_ext_pack(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
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
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->error_type);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->operational_notification);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rev_incompatible);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->secondary);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ase);
}

void reg_access_gpu_pmaos_reg_ext_unpack(struct reg_access_gpu_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
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
	offset = 51;
	ptr_struct->error_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 44;
	ptr_struct->operational_notification = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 35;
	ptr_struct->rev_incompatible = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->secondary = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->ee = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->ase = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_pmaos_reg_ext_print(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmaos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : %s (" UH_FMT ")\n", (ptr_struct->oper_status == 0 ? ("initializing") : ((ptr_struct->oper_status == 1 ? ("plugged_enabled") : ((ptr_struct->oper_status == 2 ? ("unplugged") : ((ptr_struct->oper_status == 3 ? ("module_plugged_with_error") : ((ptr_struct->oper_status == 5 ? ("unknown") : ("unknown")))))))))), ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : %s (" UH_FMT ")\n", (ptr_struct->admin_status == 1 ? ("enabled") : ((ptr_struct->admin_status == 2 ? ("disabled_by_configuration") : ((ptr_struct->admin_status == 3 ? ("enabled_once") : ("unknown")))))), ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rst                  : " UH_FMT "\n", ptr_struct->rst);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : %s (" UH_FMT ")\n", (ptr_struct->e == 0 ? ("Do_not_generate_event") : ((ptr_struct->e == 1 ? ("Generate_Event") : ((ptr_struct->e == 2 ? ("Generate_Single_Event") : ("unknown")))))), ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_type           : %s (" UH_FMT ")\n", (ptr_struct->error_type == 0 ? ("Power_Budget_Exceeded") : ((ptr_struct->error_type == 1 ? ("Long_Range_for_non_MLNX_cable_or_module") : ((ptr_struct->error_type == 2 ? ("Bus_stuck") : ((ptr_struct->error_type == 3 ? ("bad_or_unsupported_EEPROM") : ((ptr_struct->error_type == 4 ? ("Enforce_part_number_list") : ((ptr_struct->error_type == 5 ? ("unsupported_cable") : ((ptr_struct->error_type == 6 ? ("High_Temperature") : ((ptr_struct->error_type == 7 ? ("bad_cable") : ((ptr_struct->error_type == 8 ? ("PMD_type_is_not_enabled") : ((ptr_struct->error_type == 12 ? ("pcie_system_power_slot_Exceeded") : ("unknown")))))))))))))))))))), ptr_struct->error_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "operational_notification : " UH_FMT "\n", ptr_struct->operational_notification);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rev_incompatible     : " UH_FMT "\n", ptr_struct->rev_incompatible);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "secondary            : " UH_FMT "\n", ptr_struct->secondary);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee                   : " UH_FMT "\n", ptr_struct->ee);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ase                  : " UH_FMT "\n", ptr_struct->ase);
}

unsigned int reg_access_gpu_pmaos_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMAOS_REG_EXT_SIZE;
}

void reg_access_gpu_pmaos_reg_ext_dump(const struct reg_access_gpu_pmaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmcr_reg_ext_pack(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_code_response);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->cs_sel);
	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->cdr_override_cntl);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->cdr_override_cap);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->cdr_override_value);
	offset = 46;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_disable_override_cntl);
	offset = 38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_disable_override_value);
	offset = 94;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_amp_override_cntl);
	offset = 93;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_amp_override_cap);
	offset = 84;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_amp_override_value);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_amp_override_value_cap);
	offset = 78;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_los_override_cntl);
	offset = 77;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_los_override_cap);
	offset = 70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_los_override_admin);
	offset = 126;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_emp_override_cntl);
	offset = 125;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_emp_override_cap);
	offset = 116;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_emp_override_value);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_emp_override_value_cap);
	offset = 110;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->rx_post_emp_override_cntl);
	offset = 109;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rx_post_emp_override_cap);
	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_post_emp_override_value);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rx_post_emp_override_value_cap);
	offset = 158;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_equ_override_cntl);
	offset = 157;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_equ_override_cap);
	offset = 148;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_equ_override_value);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->tx_equ_override_value_cap);
	offset = 142;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_adaptive_override_value);
	offset = 134;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_adaptive_override_cntrl);
	offset = 133;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_adaptive_override_cap);
	offset = 222;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ap_sel_override_cntrl);
	offset = 212;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ap_sel_override_value);
}

void reg_access_gpu_pmcr_reg_ext_unpack(struct reg_access_gpu_pmcr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->error_code_response = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 6;
	ptr_struct->cs_sel = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 62;
	ptr_struct->cdr_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 60;
	ptr_struct->cdr_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 52;
	ptr_struct->cdr_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 46;
	ptr_struct->tx_disable_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 38;
	ptr_struct->tx_disable_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 94;
	ptr_struct->rx_amp_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 93;
	ptr_struct->rx_amp_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 84;
	ptr_struct->rx_amp_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->rx_amp_override_value_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 78;
	ptr_struct->rx_los_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 77;
	ptr_struct->rx_los_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 70;
	ptr_struct->rx_los_override_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 126;
	ptr_struct->rx_emp_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 125;
	ptr_struct->rx_emp_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 116;
	ptr_struct->rx_emp_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 112;
	ptr_struct->rx_emp_override_value_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 110;
	ptr_struct->rx_post_emp_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 109;
	ptr_struct->rx_post_emp_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 100;
	ptr_struct->rx_post_emp_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->rx_post_emp_override_value_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 158;
	ptr_struct->tx_equ_override_cntl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 157;
	ptr_struct->tx_equ_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 148;
	ptr_struct->tx_equ_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->tx_equ_override_value_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 142;
	ptr_struct->tx_adaptive_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 134;
	ptr_struct->tx_adaptive_override_cntrl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 133;
	ptr_struct->tx_adaptive_override_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 222;
	ptr_struct->ap_sel_override_cntrl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 212;
	ptr_struct->ap_sel_override_value = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pmcr_reg_ext_print(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmcr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_code_response  : %s (" UH_FMT ")\n", (ptr_struct->error_code_response == 0 ? ("ConfigUndefined") : ((ptr_struct->error_code_response == 1 ? ("ConfigSuccess") : ((ptr_struct->error_code_response == 2 ? ("ConfigRejected") : ((ptr_struct->error_code_response == 3 ? ("ConfigRejectedInvalidAppSel") : ((ptr_struct->error_code_response == 4 ? ("ConfigRejectedInvalidDataPath") : ((ptr_struct->error_code_response == 5 ? ("ConfigRejectedInvalidSI") : ((ptr_struct->error_code_response == 6 ? ("ConfigRejectedLanesInUse") : ((ptr_struct->error_code_response == 7 ? ("ConfigRejectedPartialDataPath") : ((ptr_struct->error_code_response == 12 ? ("ConfigInProgress") : ("unknown")))))))))))))))))), ptr_struct->error_code_response);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cs_sel               : " UH_FMT "\n", ptr_struct->cs_sel);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_override_cntl    : " UH_FMT "\n", ptr_struct->cdr_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_override_cap     : " UH_FMT "\n", ptr_struct->cdr_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cdr_override_value   : " UH_FMT "\n", ptr_struct->cdr_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_disable_override_cntl : " UH_FMT "\n", ptr_struct->tx_disable_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_disable_override_value : " UH_FMT "\n", ptr_struct->tx_disable_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_amp_override_cntl : " UH_FMT "\n", ptr_struct->rx_amp_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_amp_override_cap  : " UH_FMT "\n", ptr_struct->rx_amp_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_amp_override_value : " UH_FMT "\n", ptr_struct->rx_amp_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_amp_override_value_cap : " UH_FMT "\n", ptr_struct->rx_amp_override_value_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_los_override_cntl : " UH_FMT "\n", ptr_struct->rx_los_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_los_override_cap  : " UH_FMT "\n", ptr_struct->rx_los_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_los_override_admin : " UH_FMT "\n", ptr_struct->rx_los_override_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_emp_override_cntl : " UH_FMT "\n", ptr_struct->rx_emp_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_emp_override_cap  : " UH_FMT "\n", ptr_struct->rx_emp_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_emp_override_value : " UH_FMT "\n", ptr_struct->rx_emp_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_emp_override_value_cap : " UH_FMT "\n", ptr_struct->rx_emp_override_value_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_post_emp_override_cntl : " UH_FMT "\n", ptr_struct->rx_post_emp_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_post_emp_override_cap : " UH_FMT "\n", ptr_struct->rx_post_emp_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_post_emp_override_value : " UH_FMT "\n", ptr_struct->rx_post_emp_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rx_post_emp_override_value_cap : " UH_FMT "\n", ptr_struct->rx_post_emp_override_value_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_equ_override_cntl : " UH_FMT "\n", ptr_struct->tx_equ_override_cntl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_equ_override_cap  : " UH_FMT "\n", ptr_struct->tx_equ_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_equ_override_value : " UH_FMT "\n", ptr_struct->tx_equ_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_equ_override_value_cap : " UH_FMT "\n", ptr_struct->tx_equ_override_value_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_adaptive_override_value : " UH_FMT "\n", ptr_struct->tx_adaptive_override_value);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_adaptive_override_cntrl : " UH_FMT "\n", ptr_struct->tx_adaptive_override_cntrl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_adaptive_override_cap : " UH_FMT "\n", ptr_struct->tx_adaptive_override_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ap_sel_override_cntrl : " UH_FMT "\n", ptr_struct->ap_sel_override_cntrl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ap_sel_override_value : " UH_FMT "\n", ptr_struct->ap_sel_override_value);
}

unsigned int reg_access_gpu_pmcr_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMCR_REG_EXT_SIZE;
}

void reg_access_gpu_pmcr_reg_ext_dump(const struct reg_access_gpu_pmcr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmcr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmlp_reg_ext_pack(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
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
		reg_access_gpu_lane_2_module_mapping_ext_pack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_pmlp_reg_ext_unpack(struct reg_access_gpu_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
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
		reg_access_gpu_lane_2_module_mapping_ext_unpack(&(ptr_struct->lane_module_mapping[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_pmlp_reg_ext_print(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmlp_reg_ext ========\n");

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
		reg_access_gpu_lane_2_module_mapping_ext_print(&(ptr_struct->lane_module_mapping[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_gpu_pmlp_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMLP_REG_EXT_SIZE;
}

void reg_access_gpu_pmlp_reg_ext_dump(const struct reg_access_gpu_pmlp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmlp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmmp_reg_ext_pack(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sticky);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->apply_im);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->eeprom_override);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->eeprom_override_mask);
	offset = 64;
	switch (ptr_struct->eeprom_override) {
	case 0x200:
		offset = 64;
		reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_pack(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_pack(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 160;
	switch (ptr_struct->eeprom_override) {
	case 0x2:
		offset = 160;
		reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_pack(&(ptr_struct->sfp_cable_protocol_technology.pmmp_sfp_protocol_bytes_override_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 280;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->cable_length);
	offset = 276;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->module_type);
	offset = 312;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_5g);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_7g);
	offset = 296;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_12g);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_25g);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_53g);
}

void reg_access_gpu_pmmp_reg_ext_unpack(struct reg_access_gpu_pmmp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->sticky = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->apply_im = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->eeprom_override = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 32;
	ptr_struct->eeprom_override_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	switch (ptr_struct->eeprom_override) {
	case 0x200:
		offset = 64;
		reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_unpack(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_unpack(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 160;
	switch (ptr_struct->eeprom_override) {
	case 0x2:
		offset = 160;
		reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_unpack(&(ptr_struct->sfp_cable_protocol_technology.pmmp_sfp_protocol_bytes_override_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
	offset = 280;
	ptr_struct->cable_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 276;
	ptr_struct->module_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 312;
	ptr_struct->attenuation_5g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 304;
	ptr_struct->attenuation_7g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 296;
	ptr_struct->attenuation_12g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 288;
	ptr_struct->attenuation_25g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 336;
	ptr_struct->attenuation_53g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pmmp_reg_ext_print(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmmp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sticky               : " UH_FMT "\n", ptr_struct->sticky);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apply_im             : " UH_FMT "\n", ptr_struct->apply_im);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eeprom_override      : %s (" UH_FMT ")\n", (ptr_struct->eeprom_override == 1 ? ("Override_cable_protocols_and_technology_for_QSFP") : ((ptr_struct->eeprom_override == 2 ? ("Override_cable_protocols_and_technology_for_SFP") : ((ptr_struct->eeprom_override == 4 ? ("Ignore_Power_Class") : ((ptr_struct->eeprom_override == 8 ? ("Override_Cable_Length") : ((ptr_struct->eeprom_override == 16 ? ("Override_Attenuation") : ((ptr_struct->eeprom_override == 256 ? ("Set_Module_to_Low_Power") : ((ptr_struct->eeprom_override == 512 ? ("Override_cable_protocols_and_technology_for_CMIS") : ((ptr_struct->eeprom_override == 2048 ? ("Override_module_type") : ("unknown")))))))))))))))), ptr_struct->eeprom_override);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eeprom_override_mask : " UH_FMT "\n", ptr_struct->eeprom_override_mask);
	switch (ptr_struct->eeprom_override) {
	case 0x200:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pmmp_cmis_protocol_override_layout_ext:\n");
		reg_access_gpu_pmmp_cmis_protocol_override_layout_ext_print(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pmmp_qsfp_protocol_override_layout_ext:\n");
		reg_access_gpu_pmmp_qsfp_protocol_override_layout_ext_print(&(ptr_struct->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	switch (ptr_struct->eeprom_override) {
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pmmp_sfp_protocol_bytes_override_ext:\n");
		reg_access_gpu_pmmp_sfp_protocol_bytes_override_ext_print(&(ptr_struct->sfp_cable_protocol_technology.pmmp_sfp_protocol_bytes_override_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cable_length         : " UH_FMT "\n", ptr_struct->cable_length);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_type          : " UH_FMT "\n", ptr_struct->module_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_5g       : " UH_FMT "\n", ptr_struct->attenuation_5g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_7g       : " UH_FMT "\n", ptr_struct->attenuation_7g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_12g      : " UH_FMT "\n", ptr_struct->attenuation_12g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_25g      : " UH_FMT "\n", ptr_struct->attenuation_25g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_53g      : " UH_FMT "\n", ptr_struct->attenuation_53g);
}

unsigned int reg_access_gpu_pmmp_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMMP_REG_EXT_SIZE;
}

void reg_access_gpu_pmmp_reg_ext_dump(const struct reg_access_gpu_pmmp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmmp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmpd_reg_ext_pack(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 27;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->cl);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->host_media);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->errors_cap);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ber_cap);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->snr_cap);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_bits_high);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_bits_low);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_errors_high);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_errors_low);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->measured_snr);
	offset = 220;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ber_coef);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->ber_magnitude);
}

void reg_access_gpu_pmpd_reg_ext_unpack(struct reg_access_gpu_pmpd_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 27;
	ptr_struct->cl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 20;
	ptr_struct->lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 19;
	ptr_struct->host_media = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 2;
	ptr_struct->errors_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->ber_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->snr_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->prbs_bits_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->prbs_bits_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->prbs_errors_high = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->prbs_errors_low = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->measured_snr = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 220;
	ptr_struct->ber_coef = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 208;
	ptr_struct->ber_magnitude = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pmpd_reg_ext_print(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmpd_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "cl                   : " UH_FMT "\n", ptr_struct->cl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane                 : " UH_FMT "\n", ptr_struct->lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_media           : " UH_FMT "\n", ptr_struct->host_media);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "errors_cap           : " UH_FMT "\n", ptr_struct->errors_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_cap              : " UH_FMT "\n", ptr_struct->ber_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "snr_cap              : " UH_FMT "\n", ptr_struct->snr_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_bits_high       : " U32H_FMT "\n", ptr_struct->prbs_bits_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_bits_low        : " U32H_FMT "\n", ptr_struct->prbs_bits_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_errors_high     : " U32H_FMT "\n", ptr_struct->prbs_errors_high);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_errors_low      : " U32H_FMT "\n", ptr_struct->prbs_errors_low);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "measured_snr         : " UH_FMT "\n", ptr_struct->measured_snr);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_coef             : " UH_FMT "\n", ptr_struct->ber_coef);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ber_magnitude        : " UH_FMT "\n", ptr_struct->ber_magnitude);
}

unsigned int reg_access_gpu_pmpd_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMPD_REG_EXT_SIZE;
}

void reg_access_gpu_pmpd_reg_ext_dump(const struct reg_access_gpu_pmpd_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmpd_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmpr_reg_ext_pack(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_5g);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_7g);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_53g);
	offset = 120;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_12g);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->attenuation_25g);
}

void reg_access_gpu_pmpr_reg_ext_unpack(struct reg_access_gpu_pmpr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->attenuation_5g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->attenuation_7g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->attenuation_53g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 120;
	ptr_struct->attenuation_12g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->attenuation_25g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pmpr_reg_ext_print(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmpr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_5g       : " UH_FMT "\n", ptr_struct->attenuation_5g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_7g       : " UH_FMT "\n", ptr_struct->attenuation_7g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_53g      : " UH_FMT "\n", ptr_struct->attenuation_53g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_12g      : " UH_FMT "\n", ptr_struct->attenuation_12g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "attenuation_25g      : " UH_FMT "\n", ptr_struct->attenuation_25g);
}

unsigned int reg_access_gpu_pmpr_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMPR_REG_EXT_SIZE;
}

void reg_access_gpu_pmpr_reg_ext_dump(const struct reg_access_gpu_pmpr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmpr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmpt_reg_ext_pack(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lane_mask);
	offset = 19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->host_media);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->invt_cap);
	offset = 17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->swap_cap);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->le);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ls);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->e);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_modes_cap);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modulation);
	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->ch_ge);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->invt_admin);
	offset = 86;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->swap_admin);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prbs_mode_admin);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_cap);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_admin);
}

void reg_access_gpu_pmpt_reg_ext_unpack(struct reg_access_gpu_pmpt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->lane_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 19;
	ptr_struct->host_media = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->invt_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 17;
	ptr_struct->swap_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 2;
	ptr_struct->le = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->ls = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->prbs_modes_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->modulation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 90;
	ptr_struct->ch_ge = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 87;
	ptr_struct->invt_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 86;
	ptr_struct->swap_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	ptr_struct->prbs_mode_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->lane_rate_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->lane_rate_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pmpt_reg_ext_print(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmpt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_mask            : " UH_FMT "\n", ptr_struct->lane_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "host_media           : " UH_FMT "\n", ptr_struct->host_media);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "invt_cap             : " UH_FMT "\n", ptr_struct->invt_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swap_cap             : " UH_FMT "\n", ptr_struct->swap_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "le                   : " UH_FMT "\n", ptr_struct->le);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ls                   : " UH_FMT "\n", ptr_struct->ls);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : " UH_FMT "\n", ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_modes_cap       : " U32H_FMT "\n", ptr_struct->prbs_modes_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modulation           : " UH_FMT "\n", ptr_struct->modulation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ch_ge                : " UH_FMT "\n", ptr_struct->ch_ge);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "invt_admin           : " UH_FMT "\n", ptr_struct->invt_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swap_admin           : " UH_FMT "\n", ptr_struct->swap_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_mode_admin      : " UH_FMT "\n", ptr_struct->prbs_mode_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_cap        : " UH_FMT "\n", ptr_struct->lane_rate_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_admin      : " UH_FMT "\n", ptr_struct->lane_rate_admin);
}

unsigned int reg_access_gpu_pmpt_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMPT_REG_EXT_SIZE;
}

void reg_access_gpu_pmpt_reg_ext_dump(const struct reg_access_gpu_pmpt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmpt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmtm_reg_ext_pack(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->module);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->slot_index);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->module_type);
	offset = 51;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->module_width);
}

void reg_access_gpu_pmtm_reg_ext_unpack(struct reg_access_gpu_pmtm_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->module = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->slot_index = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 59;
	ptr_struct->module_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 51;
	ptr_struct->module_width = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
}

void reg_access_gpu_pmtm_reg_ext_print(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmtm_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module               : " UH_FMT "\n", ptr_struct->module);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slot_index           : " UH_FMT "\n", ptr_struct->slot_index);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_type          : %s (" UH_FMT ")\n", (ptr_struct->module_type == 0 ? ("Backplane_with_4_lanes") : ((ptr_struct->module_type == 1 ? ("QSFP") : ((ptr_struct->module_type == 2 ? ("SFP") : ((ptr_struct->module_type == 3 ? ("No_Cage") : ((ptr_struct->module_type == 4 ? ("Backplane_with_single_lane") : ((ptr_struct->module_type == 8 ? ("Backplane_with_two_lanes") : ((ptr_struct->module_type == 10 ? ("Chip2Chip4x") : ((ptr_struct->module_type == 11 ? ("Chip2Chip2x") : ((ptr_struct->module_type == 12 ? ("Chip2Chip1x") : ((ptr_struct->module_type == 14 ? ("QSFP_DD") : ((ptr_struct->module_type == 15 ? ("OSFP") : ((ptr_struct->module_type == 16 ? ("SFP_DD") : ((ptr_struct->module_type == 17 ? ("DSFP") : ((ptr_struct->module_type == 18 ? ("Chip2Chip8x") : ((ptr_struct->module_type == 19 ? ("Twisted_Pair") : ((ptr_struct->module_type == 20 ? ("Backplane_with_8_lanes") : ("unknown")))))))))))))))))))))))))))))))), ptr_struct->module_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "module_width         : " UH_FMT "\n", ptr_struct->module_width);
}

unsigned int reg_access_gpu_pmtm_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMTM_REG_EXT_SIZE;
}

void reg_access_gpu_pmtm_reg_ext_dump(const struct reg_access_gpu_pmtm_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmtm_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pmtu_reg_ext_pack(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->itre);
	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->i_e);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->protocol);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_mtu);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->admin_mtu);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->oper_mtu);
}

void reg_access_gpu_pmtu_reg_ext_unpack(struct reg_access_gpu_pmtu_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->itre = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 26;
	ptr_struct->i_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	ptr_struct->max_mtu = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 64;
	ptr_struct->admin_mtu = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 96;
	ptr_struct->oper_mtu = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pmtu_reg_ext_print(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pmtu_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "itre                 : " UH_FMT "\n", ptr_struct->itre);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "i_e                  : " UH_FMT "\n", ptr_struct->i_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "protocol             : " UH_FMT "\n", ptr_struct->protocol);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_mtu              : " UH_FMT "\n", ptr_struct->max_mtu);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_mtu            : " UH_FMT "\n", ptr_struct->admin_mtu);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_mtu             : " UH_FMT "\n", ptr_struct->oper_mtu);
}

unsigned int reg_access_gpu_pmtu_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PMTU_REG_EXT_SIZE;
}

void reg_access_gpu_pmtu_reg_ext_dump(const struct reg_access_gpu_pmtu_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pmtu_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppaos_reg_ext_pack(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_test_mode_status);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_test_mode_admin);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_status);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->phy_status_admin);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dc_cpl_port);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dc_cpl_allow);
}

void reg_access_gpu_ppaos_reg_ext_unpack(struct reg_access_gpu_ppaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->phy_test_mode_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->phy_test_mode_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->phy_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->phy_status_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 35;
	ptr_struct->dc_cpl_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 34;
	ptr_struct->dc_cpl_allow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_ppaos_reg_ext_print(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppaos_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_test_mode_status : %s (" UH_FMT ")\n", (ptr_struct->phy_test_mode_status == 0 ? ("regular_operation") : ((ptr_struct->phy_test_mode_status == 1 ? ("phy_test_mode") : ("unknown")))), ptr_struct->phy_test_mode_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_test_mode_admin  : " UH_FMT "\n", ptr_struct->phy_test_mode_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_status           : " UH_FMT "\n", ptr_struct->phy_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "phy_status_admin     : " UH_FMT "\n", ptr_struct->phy_status_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dc_cpl_port          : " UH_FMT "\n", ptr_struct->dc_cpl_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dc_cpl_allow         : " UH_FMT "\n", ptr_struct->dc_cpl_allow);
}

unsigned int reg_access_gpu_ppaos_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPAOS_REG_EXT_SIZE;
}

void reg_access_gpu_ppaos_reg_ext_dump(const struct reg_access_gpu_ppaos_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppaos_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppcnt_reg_ext_pack(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->grp);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->prio_tc);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->grp_profile);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->counters_cap);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lp_gl);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->clr);
	offset = 64;
	switch (ptr_struct->grp) {
	case 0x21:
		offset = 64;
		reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_pack(&(ptr_struct->counter_set.IB_long_portcntrs_attribute_grp_data_ext), ptr_buff + offset / 8);
		break;
	case 0x20:
		offset = 64;
		reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_pack(&(ptr_struct->counter_set.IB_portcntrs_attribute_grp_data_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_2819_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_2863_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_3635_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_802_3_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_gpu_eth_discard_cntrs_grp_ext_pack(&(ptr_struct->counter_set.eth_discard_cntrs_grp_ext), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 64;
		reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_extended_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x10:
		offset = 64;
		reg_access_gpu_eth_per_prio_grp_data_layout_ext_pack(&(ptr_struct->counter_set.eth_per_prio_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x13:
		offset = 64;
		reg_access_gpu_eth_per_traffic_class_cong_layout_ext_pack(&(ptr_struct->counter_set.eth_per_traffic_class_cong_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x11:
		offset = 64;
		reg_access_gpu_eth_per_traffic_class_layout_ext_pack(&(ptr_struct->counter_set.eth_per_traffic_class_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x12:
		offset = 64;
		reg_access_gpu_phys_layer_cntrs_ext_pack(&(ptr_struct->counter_set.phys_layer_cntrs_ext), ptr_buff + offset / 8);
		break;
	case 0x16:
		offset = 64;
		reg_access_gpu_phys_layer_stat_cntrs_ext_pack(&(ptr_struct->counter_set.phys_layer_stat_cntrs_ext), ptr_buff + offset / 8);
		break;
	case 0x26:
		offset = 64;
		reg_access_gpu_ppcnt_infiniband_general_counter_ext_pack(&(ptr_struct->counter_set.ppcnt_infiniband_general_counter_ext), ptr_buff + offset / 8);
		break;
	case 0x25:
		offset = 64;
		reg_access_gpu_ppcnt_infiniband_packets_counter_ext_pack(&(ptr_struct->counter_set.ppcnt_infiniband_packets_counter_ext), ptr_buff + offset / 8);
		break;
	case 0x22:
		offset = 64;
		reg_access_gpu_ppcnt_plr_counters_ext_pack(&(ptr_struct->counter_set.ppcnt_plr_counters_ext), ptr_buff + offset / 8);
		break;
	case 0x23:
		offset = 64;
		reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_pack(&(ptr_struct->counter_set.ppcnt_rs_fec_histograms_counters_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_ppcnt_reg_ext_unpack(struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 26;
	ptr_struct->grp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 59;
	ptr_struct->prio_tc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);
	offset = 56;
	ptr_struct->grp_profile = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 52;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 34;
	ptr_struct->counters_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->lp_gl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->clr = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 64;
	switch (ptr_struct->grp) {
	case 0x21:
		offset = 64;
		reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_unpack(&(ptr_struct->counter_set.IB_long_portcntrs_attribute_grp_data_ext), ptr_buff + offset / 8);
		break;
	case 0x20:
		offset = 64;
		reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_unpack(&(ptr_struct->counter_set.IB_portcntrs_attribute_grp_data_ext), ptr_buff + offset / 8);
		break;
	case 0x2:
		offset = 64;
		reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_2819_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 64;
		reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_2863_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x3:
		offset = 64;
		reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_3635_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x0:
		offset = 64;
		reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_802_3_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x6:
		offset = 64;
		reg_access_gpu_eth_discard_cntrs_grp_ext_unpack(&(ptr_struct->counter_set.eth_discard_cntrs_grp_ext), ptr_buff + offset / 8);
		break;
	case 0x5:
		offset = 64;
		reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_extended_cntrs_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x10:
		offset = 64;
		reg_access_gpu_eth_per_prio_grp_data_layout_ext_unpack(&(ptr_struct->counter_set.eth_per_prio_grp_data_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x13:
		offset = 64;
		reg_access_gpu_eth_per_traffic_class_cong_layout_ext_unpack(&(ptr_struct->counter_set.eth_per_traffic_class_cong_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x11:
		offset = 64;
		reg_access_gpu_eth_per_traffic_class_layout_ext_unpack(&(ptr_struct->counter_set.eth_per_traffic_class_layout_ext), ptr_buff + offset / 8);
		break;
	case 0x12:
		offset = 64;
		reg_access_gpu_phys_layer_cntrs_ext_unpack(&(ptr_struct->counter_set.phys_layer_cntrs_ext), ptr_buff + offset / 8);
		break;
	case 0x16:
		offset = 64;
		reg_access_gpu_phys_layer_stat_cntrs_ext_unpack(&(ptr_struct->counter_set.phys_layer_stat_cntrs_ext), ptr_buff + offset / 8);
		break;
	case 0x26:
		offset = 64;
		reg_access_gpu_ppcnt_infiniband_general_counter_ext_unpack(&(ptr_struct->counter_set.ppcnt_infiniband_general_counter_ext), ptr_buff + offset / 8);
		break;
	case 0x25:
		offset = 64;
		reg_access_gpu_ppcnt_infiniband_packets_counter_ext_unpack(&(ptr_struct->counter_set.ppcnt_infiniband_packets_counter_ext), ptr_buff + offset / 8);
		break;
	case 0x22:
		offset = 64;
		reg_access_gpu_ppcnt_plr_counters_ext_unpack(&(ptr_struct->counter_set.ppcnt_plr_counters_ext), ptr_buff + offset / 8);
		break;
	case 0x23:
		offset = 64;
		reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_unpack(&(ptr_struct->counter_set.ppcnt_rs_fec_histograms_counters_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_ppcnt_reg_ext_print(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppcnt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grp                  : %s (" UH_FMT ")\n", (ptr_struct->grp == 0 ? ("IEEE_802_3_Counters") : ((ptr_struct->grp == 1 ? ("RFC_2863_Counters") : ((ptr_struct->grp == 2 ? ("RFC_2819_Counters") : ((ptr_struct->grp == 3 ? ("RFC_3635_Counters") : ((ptr_struct->grp == 5 ? ("Ethernet_Extended_Counters") : ((ptr_struct->grp == 6 ? ("Ethernet_Discard_Counters") : ((ptr_struct->grp == 16 ? ("Per_Priority_Counters") : ((ptr_struct->grp == 17 ? ("Per_Traffic_Class_Counters") : ((ptr_struct->grp == 18 ? ("Physical_Layer_Counters") : ((ptr_struct->grp == 19 ? ("Per_Traffic_Class_Congestion_Counters") : ((ptr_struct->grp == 22 ? ("Physical_Layer_Statistical_Counters") : ((ptr_struct->grp == 32 ? ("InfiniBand_Port_Counters") : ((ptr_struct->grp == 33 ? ("InfiniBand_Extended_Port_Counters") : ((ptr_struct->grp == 34 ? ("PLR_counters_group") : ((ptr_struct->grp == 35 ? ("RS_FEC_Histogram_group") : ((ptr_struct->grp == 37 ? ("InfiniBand_pkts_counters") : ((ptr_struct->grp == 38 ? ("InfiniBand_General_Counters") : ("unknown")))))))))))))))))))))))))))))))))), ptr_struct->grp);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : %s (" UH_FMT ")\n", (ptr_struct->pnat == 0 ? ("Local_port_number") : ((ptr_struct->pnat == 1 ? ("IB_port_number") : ((ptr_struct->pnat == 2 ? ("host_port_number") : ("unknown")))))), ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prio_tc              : " UH_FMT "\n", ptr_struct->prio_tc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "grp_profile          : " UH_FMT "\n", ptr_struct->grp_profile);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "counters_cap         : " UH_FMT "\n", ptr_struct->counters_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_gl                : " UH_FMT "\n", ptr_struct->lp_gl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "clr                  : " UH_FMT "\n", ptr_struct->clr);
	switch (ptr_struct->grp) {
	case 0x21:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "IB_long_portcntrs_attribute_grp_data_ext:\n");
		reg_access_gpu_IB_long_portcntrs_attribute_grp_data_ext_print(&(ptr_struct->counter_set.IB_long_portcntrs_attribute_grp_data_ext), fd, indent_level + 1);
		break;
	case 0x20:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "IB_portcntrs_attribute_grp_data_ext:\n");
		reg_access_gpu_IB_portcntrs_attribute_grp_data_ext_print(&(ptr_struct->counter_set.IB_portcntrs_attribute_grp_data_ext), fd, indent_level + 1);
		break;
	case 0x2:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_2819_cntrs_grp_data_layout_ext:\n");
		reg_access_gpu_eth_2819_cntrs_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_2819_cntrs_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_2863_cntrs_grp_data_layout_ext:\n");
		reg_access_gpu_eth_2863_cntrs_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_2863_cntrs_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x3:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_3635_cntrs_grp_data_layout_ext:\n");
		reg_access_gpu_eth_3635_cntrs_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_3635_cntrs_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_802_3_cntrs_grp_data_layout_ext:\n");
		reg_access_gpu_eth_802_3_cntrs_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_802_3_cntrs_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x6:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_discard_cntrs_grp_ext:\n");
		reg_access_gpu_eth_discard_cntrs_grp_ext_print(&(ptr_struct->counter_set.eth_discard_cntrs_grp_ext), fd, indent_level + 1);
		break;
	case 0x5:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_extended_cntrs_grp_data_layout_ext:\n");
		reg_access_gpu_eth_extended_cntrs_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_extended_cntrs_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x10:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_per_prio_grp_data_layout_ext:\n");
		reg_access_gpu_eth_per_prio_grp_data_layout_ext_print(&(ptr_struct->counter_set.eth_per_prio_grp_data_layout_ext), fd, indent_level + 1);
		break;
	case 0x13:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_per_traffic_class_cong_layout_ext:\n");
		reg_access_gpu_eth_per_traffic_class_cong_layout_ext_print(&(ptr_struct->counter_set.eth_per_traffic_class_cong_layout_ext), fd, indent_level + 1);
		break;
	case 0x11:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "eth_per_traffic_class_layout_ext:\n");
		reg_access_gpu_eth_per_traffic_class_layout_ext_print(&(ptr_struct->counter_set.eth_per_traffic_class_layout_ext), fd, indent_level + 1);
		break;
	case 0x12:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "phys_layer_cntrs_ext:\n");
		reg_access_gpu_phys_layer_cntrs_ext_print(&(ptr_struct->counter_set.phys_layer_cntrs_ext), fd, indent_level + 1);
		break;
	case 0x16:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "phys_layer_stat_cntrs_ext:\n");
		reg_access_gpu_phys_layer_stat_cntrs_ext_print(&(ptr_struct->counter_set.phys_layer_stat_cntrs_ext), fd, indent_level + 1);
		break;
	case 0x26:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcnt_infiniband_general_counter_ext:\n");
		reg_access_gpu_ppcnt_infiniband_general_counter_ext_print(&(ptr_struct->counter_set.ppcnt_infiniband_general_counter_ext), fd, indent_level + 1);
		break;
	case 0x25:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcnt_infiniband_packets_counter_ext:\n");
		reg_access_gpu_ppcnt_infiniband_packets_counter_ext_print(&(ptr_struct->counter_set.ppcnt_infiniband_packets_counter_ext), fd, indent_level + 1);
		break;
	case 0x22:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcnt_plr_counters_ext:\n");
		reg_access_gpu_ppcnt_plr_counters_ext_print(&(ptr_struct->counter_set.ppcnt_plr_counters_ext), fd, indent_level + 1);
		break;
	case 0x23:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "ppcnt_rs_fec_histograms_counters_ext:\n");
		reg_access_gpu_ppcnt_rs_fec_histograms_counters_ext_print(&(ptr_struct->counter_set.ppcnt_rs_fec_histograms_counters_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_gpu_ppcnt_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPCNT_REG_EXT_SIZE;
}

void reg_access_gpu_ppcnt_reg_ext_dump(const struct reg_access_gpu_ppcnt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppcnt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppdfd_ext_pack(const struct reg_access_gpu_ppdfd_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ntimes);
	offset = 95;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->poison_en);
	offset = 94;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->stomp_en);
}

void reg_access_gpu_ppdfd_ext_unpack(struct reg_access_gpu_ppdfd_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 48;
	ptr_struct->ntimes = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 95;
	ptr_struct->poison_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 94;
	ptr_struct->stomp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_ppdfd_ext_print(const struct reg_access_gpu_ppdfd_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppdfd_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ntimes               : " UH_FMT "\n", ptr_struct->ntimes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "poison_en            : " UH_FMT "\n", ptr_struct->poison_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "stomp_en             : " UH_FMT "\n", ptr_struct->stomp_en);
}

unsigned int reg_access_gpu_ppdfd_ext_size(void)
{
	return REG_ACCESS_GPU_PPDFD_EXT_SIZE;
}

void reg_access_gpu_ppdfd_ext_dump(const struct reg_access_gpu_ppdfd_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppdfd_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pphcr_ext_pack(const struct reg_access_gpu_pphcr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->we);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->active_hist_type);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hist_type);
	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_of_bins);
	offset = 88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hist_min_measurement);
	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hist_max_measurement);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->bin_range_write_mask);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 640, 1);
		reg_access_gpu_pphcr_bin_range_ext_pack(&(ptr_struct->bin_range[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_pphcr_ext_unpack(struct reg_access_gpu_pphcr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 31;
	ptr_struct->we = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->active_hist_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 60;
	ptr_struct->hist_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 40;
	ptr_struct->num_of_bins = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 88;
	ptr_struct->hist_min_measurement = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 72;
	ptr_struct->hist_max_measurement = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 112;
	ptr_struct->bin_range_write_mask = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	for (i = 0; i < 16; ++i) {
		offset = adb2c_calc_array_field_address(128, 32, i, 640, 1);
		reg_access_gpu_pphcr_bin_range_ext_unpack(&(ptr_struct->bin_range[i]), ptr_buff + offset / 8);
	}
}

void reg_access_gpu_pphcr_ext_print(const struct reg_access_gpu_pphcr_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pphcr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "we                   : " UH_FMT "\n", ptr_struct->we);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : %s (" UH_FMT ")\n", (ptr_struct->pnat == 0 ? ("Local_port_number") : ((ptr_struct->pnat == 1 ? ("IB_port_number") : ("unknown")))), ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "active_hist_type     : " UH_FMT "\n", ptr_struct->active_hist_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hist_type            : " UH_FMT "\n", ptr_struct->hist_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "num_of_bins          : " UH_FMT "\n", ptr_struct->num_of_bins);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hist_min_measurement : " UH_FMT "\n", ptr_struct->hist_min_measurement);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hist_max_measurement : " UH_FMT "\n", ptr_struct->hist_max_measurement);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "bin_range_write_mask : " UH_FMT "\n", ptr_struct->bin_range_write_mask);
	for (i = 0; i < 16; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "bin_range_%03d:\n", i);
		reg_access_gpu_pphcr_bin_range_ext_print(&(ptr_struct->bin_range[i]), fd, indent_level + 1);
	}
}

unsigned int reg_access_gpu_pphcr_ext_size(void)
{
	return REG_ACCESS_GPU_PPHCR_EXT_SIZE;
}

void reg_access_gpu_pphcr_ext_dump(const struct reg_access_gpu_pphcr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pphcr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pplm_reg_ext_pack(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->test_mode);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->fec_mode_active);
	offset = 156;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_cap_10g_40g);
	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_cap_25g);
	offset = 148;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_cap_50g);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_cap_100g);
	offset = 140;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_cap_56g);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_correction_bypass_cap);
	offset = 188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_admin_10g_40g);
	offset = 184;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_admin_25g);
	offset = 180;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_admin_50g);
	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_admin_100g);
	offset = 172;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fec_override_admin_56g);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->rs_fec_correction_bypass_admin);
	offset = 208;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_200g_4x);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_400g_8x);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_50g_1x);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_100g_2x);
	offset = 272;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_200g_4x);
	offset = 256;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_400g_8x);
	offset = 304;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_50g_1x);
	offset = 288;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_100g_2x);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_400g_4x);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_800g_8x);
	offset = 368;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_100g_1x);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_cap_200g_2x);
	offset = 560;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_400g_4x);
	offset = 544;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_800g_8x);
	offset = 592;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_100g_1x);
	offset = 576;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->fec_override_admin_200g_2x);
}

void reg_access_gpu_pplm_reg_ext_unpack(struct reg_access_gpu_pplm_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->test_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 104;
	ptr_struct->fec_mode_active = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
	offset = 156;
	ptr_struct->fec_override_cap_10g_40g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 152;
	ptr_struct->fec_override_cap_25g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 148;
	ptr_struct->fec_override_cap_50g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->fec_override_cap_100g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 140;
	ptr_struct->fec_override_cap_56g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 128;
	ptr_struct->rs_fec_correction_bypass_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 188;
	ptr_struct->fec_override_admin_10g_40g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 184;
	ptr_struct->fec_override_admin_25g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 180;
	ptr_struct->fec_override_admin_50g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 176;
	ptr_struct->fec_override_admin_100g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 172;
	ptr_struct->fec_override_admin_56g = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->rs_fec_correction_bypass_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 208;
	ptr_struct->fec_override_cap_200g_4x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->fec_override_cap_400g_8x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 240;
	ptr_struct->fec_override_cap_50g_1x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->fec_override_cap_100g_2x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 272;
	ptr_struct->fec_override_admin_200g_4x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 256;
	ptr_struct->fec_override_admin_400g_8x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 304;
	ptr_struct->fec_override_admin_50g_1x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 288;
	ptr_struct->fec_override_admin_100g_2x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 336;
	ptr_struct->fec_override_cap_400g_4x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 320;
	ptr_struct->fec_override_cap_800g_8x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 368;
	ptr_struct->fec_override_cap_100g_1x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 352;
	ptr_struct->fec_override_cap_200g_2x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 560;
	ptr_struct->fec_override_admin_400g_4x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 544;
	ptr_struct->fec_override_admin_800g_8x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 592;
	ptr_struct->fec_override_admin_100g_1x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 576;
	ptr_struct->fec_override_admin_200g_2x = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pplm_reg_ext_print(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pplm_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "test_mode            : %s (" UH_FMT ")\n", (ptr_struct->test_mode == 0 ? ("Mission_mode_configuration_and_capabilities") : ((ptr_struct->test_mode == 1 ? ("Test_mode_configuration_and_capabilities") : ("unknown")))), ptr_struct->test_mode);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("Near_End_Port") : ((ptr_struct->port_type == 2 ? ("Internal_IC_Port") : ((ptr_struct->port_type == 3 ? ("Far_End_Port") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : %s (" UH_FMT ")\n", (ptr_struct->pnat == 0 ? ("Local_port_number") : ((ptr_struct->pnat == 1 ? ("IB_port_number") : ("unknown")))), ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_mode_active      : %s (" UH_FMT ")\n", (ptr_struct->fec_mode_active == 0 ? ("No_FEC") : ((ptr_struct->fec_mode_active == 1 ? ("Firecode_FEC") : ((ptr_struct->fec_mode_active == 2 ? ("Standard_RS_FEC") : ((ptr_struct->fec_mode_active == 3 ? ("Standard_LL_RS_FEC") : ((ptr_struct->fec_mode_active == 6 ? ("Interleaved_Standard_RS") : ((ptr_struct->fec_mode_active == 7 ? ("Standard_RS") : ((ptr_struct->fec_mode_active == 9 ? ("Ethernet_Consortium_LL_50G_RS_FEC") : ((ptr_struct->fec_mode_active == 10 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC") : ("unknown")))))))))))))))), ptr_struct->fec_mode_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_10g_40g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_10g_40g == 1 ? ("No") : ((ptr_struct->fec_override_cap_10g_40g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_cap_10g_40g == 4 ? ("Reserved2") : ((ptr_struct->fec_override_cap_10g_40g == 8 ? ("Reserved3") : ("unknown")))))))), ptr_struct->fec_override_cap_10g_40g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_25g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_25g == 1 ? ("No") : ((ptr_struct->fec_override_cap_25g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_cap_25g == 4 ? ("RS") : ((ptr_struct->fec_override_cap_25g == 8 ? ("Reserved") : ("unknown")))))))), ptr_struct->fec_override_cap_25g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_50g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_50g == 1 ? ("No") : ((ptr_struct->fec_override_cap_50g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_cap_50g == 4 ? ("RS") : ((ptr_struct->fec_override_cap_50g == 8 ? ("Reserved") : ("unknown")))))))), ptr_struct->fec_override_cap_50g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_100g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_100g == 1 ? ("No") : ((ptr_struct->fec_override_cap_100g == 2 ? ("Reserved1") : ((ptr_struct->fec_override_cap_100g == 4 ? ("RS") : ((ptr_struct->fec_override_cap_100g == 8 ? ("Reserved3") : ("unknown")))))))), ptr_struct->fec_override_cap_100g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_56g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_56g == 1 ? ("No") : ((ptr_struct->fec_override_cap_56g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_cap_56g == 4 ? ("Reserved2") : ((ptr_struct->fec_override_cap_56g == 8 ? ("Reserved3") : ("unknown")))))))), ptr_struct->fec_override_cap_56g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_correction_bypass_cap : %s (" UH_FMT ")\n", (ptr_struct->rs_fec_correction_bypass_cap == 0 ? ("NO_correction_bypass") : ((ptr_struct->rs_fec_correction_bypass_cap == 1 ? ("RS") : ("unknown")))), ptr_struct->rs_fec_correction_bypass_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_10g_40g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_10g_40g == 1 ? ("No_FEC") : ((ptr_struct->fec_override_admin_10g_40g == 2 ? ("Firecode_FEC") : ("unknown")))), ptr_struct->fec_override_admin_10g_40g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_25g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_25g == 1 ? ("No_FEC") : ((ptr_struct->fec_override_admin_25g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_admin_25g == 4 ? ("RS") : ("unknown")))))), ptr_struct->fec_override_admin_25g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_50g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_50g == 1 ? ("No_FEC") : ((ptr_struct->fec_override_admin_50g == 2 ? ("Firecode_FEC") : ((ptr_struct->fec_override_admin_50g == 4 ? ("RS") : ("unknown")))))), ptr_struct->fec_override_admin_50g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_100g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_100g == 1 ? ("No_FEC") : ((ptr_struct->fec_override_admin_100g == 4 ? ("RS") : ("unknown")))), ptr_struct->fec_override_admin_100g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_56g : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_56g == 1 ? ("No_FEC") : ((ptr_struct->fec_override_admin_56g == 2 ? ("Firecode_FEC") : ("unknown")))), ptr_struct->fec_override_admin_56g);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rs_fec_correction_bypass_admin : %s (" UH_FMT ")\n", (ptr_struct->rs_fec_correction_bypass_admin == 0 ? ("auto_mode") : ((ptr_struct->rs_fec_correction_bypass_admin == 1 ? ("NO_correction_bypass") : ((ptr_struct->rs_fec_correction_bypass_admin == 2 ? ("RS") : ("unknown")))))), ptr_struct->rs_fec_correction_bypass_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_200g_4x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_200g_4x == 512 ? ("Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1") : ("unknown")), ptr_struct->fec_override_cap_200g_4x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_400g_8x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_400g_8x == 512 ? ("Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1") : ("unknown")), ptr_struct->fec_override_cap_400g_8x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_50g_1x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_50g_1x == 512 ? ("Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1") : ("unknown")), ptr_struct->fec_override_cap_50g_1x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_100g_2x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_100g_2x == 512 ? ("Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1") : ("unknown")), ptr_struct->fec_override_cap_100g_2x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_200g_4x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_200g_4x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_200g_4x == 512 ? ("RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_admin_200g_4x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_400g_8x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_400g_8x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_400g_8x == 512 ? ("RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_admin_400g_8x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_50g_1x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_50g_1x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_50g_1x == 512 ? ("RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_admin_50g_1x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_100g_2x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_100g_2x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_100g_2x == 512 ? ("RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_admin_100g_2x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_400g_4x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_400g_4x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_cap_400g_4x == 512 ? ("Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_cap_400g_4x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_800g_8x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_800g_8x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_cap_800g_8x == 256 ? ("Reserved") : ((ptr_struct->fec_override_cap_800g_8x == 512 ? ("Ethernet_Consortium_LL_50G_RS_FEC") : ("unknown")))))), ptr_struct->fec_override_cap_800g_8x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_100g_1x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_100g_1x == 64 ? ("Interleaved_RS_FEC_544_514") : ((ptr_struct->fec_override_cap_100g_1x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_cap_100g_1x == 512 ? ("Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1") : ((ptr_struct->fec_override_cap_100g_1x == 1024 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1") : ("unknown")))))))), ptr_struct->fec_override_cap_100g_1x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_cap_200g_2x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_cap_200g_2x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_cap_200g_2x == 512 ? ("Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1") : ("unknown")))), ptr_struct->fec_override_cap_200g_2x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_400g_4x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_400g_4x == 0 ? ("Auto_mode") : ((ptr_struct->fec_override_admin_400g_4x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_400g_4x == 512 ? ("Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1") : ("unknown")))))), ptr_struct->fec_override_admin_400g_4x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_800g_8x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_800g_8x == 0 ? ("Auto_mode") : ((ptr_struct->fec_override_admin_800g_8x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_800g_8x == 512 ? ("Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1") : ("unknown")))))), ptr_struct->fec_override_admin_800g_8x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_100g_1x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_100g_1x == 0 ? ("Auto_mode") : ((ptr_struct->fec_override_admin_100g_1x == 64 ? ("Interleaved_RS_FEC_544_514") : ((ptr_struct->fec_override_admin_100g_1x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_100g_1x == 512 ? ("Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1") : ((ptr_struct->fec_override_admin_100g_1x == 1024 ? ("Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1") : ("unknown")))))))))), ptr_struct->fec_override_admin_100g_1x);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fec_override_admin_200g_2x : %s (" UH_FMT ")\n", (ptr_struct->fec_override_admin_200g_2x == 0 ? ("Auto_mode") : ((ptr_struct->fec_override_admin_200g_2x == 128 ? ("RS_FEC_544_514") : ((ptr_struct->fec_override_admin_200g_2x == 512 ? ("Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1") : ("unknown")))))), ptr_struct->fec_override_admin_200g_2x);
}

unsigned int reg_access_gpu_pplm_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPLM_REG_EXT_SIZE;
}

void reg_access_gpu_pplm_reg_ext_dump(const struct reg_access_gpu_pplm_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pplm_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pplr_reg_ext_pack(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->op_mod);
	offset = 22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->apply_im);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->lb_en);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->lb_cap);
}

void reg_access_gpu_pplr_reg_ext_unpack(struct reg_access_gpu_pplr_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 23;
	ptr_struct->op_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 22;
	ptr_struct->apply_im = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 52;
	ptr_struct->lb_en = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 36;
	ptr_struct->lb_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
}

void reg_access_gpu_pplr_reg_ext_print(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pplr_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("Near") : ((ptr_struct->port_type == 2 ? ("Internal_IC_LR_Port") : ((ptr_struct->port_type == 3 ? ("Far") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "op_mod               : " UH_FMT "\n", ptr_struct->op_mod);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "apply_im             : " UH_FMT "\n", ptr_struct->apply_im);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lb_en                : %s (" UH_FMT ")\n", (ptr_struct->lb_en == 1 ? ("Phy_remote_loopback") : ((ptr_struct->lb_en == 2 ? ("Phy_local_loopback") : ((ptr_struct->lb_en == 4 ? ("External_local_loopback") : ((ptr_struct->lb_en == 128 ? ("LL_local_loopback") : ("unknown")))))))), ptr_struct->lb_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lb_cap               : %s (" UH_FMT ")\n", (ptr_struct->lb_cap == 1 ? ("Phy_remote_loopback") : ((ptr_struct->lb_cap == 2 ? ("Phy_local_loopback") : ((ptr_struct->lb_cap == 4 ? ("External_local_loopback") : ((ptr_struct->lb_cap == 128 ? ("LL_local_loopback") : ("unknown")))))))), ptr_struct->lb_cap);
}

unsigned int reg_access_gpu_pplr_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPLR_REG_EXT_SIZE;
}

void reg_access_gpu_pplr_reg_ext_dump(const struct reg_access_gpu_pplr_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pplr_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pprt_reg_ext_pack(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->le);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ls);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sw_c);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sw);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dm_ig);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p_c);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->s);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->e);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_modes_cap);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modulation);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prbs_mode_admin);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_cap);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_oper);
	offset = 168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_lock_status_ext);
	offset = 164;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_lock_status);
	offset = 160;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_rx_tuning_status);
}

void reg_access_gpu_pprt_reg_ext_unpack(struct reg_access_gpu_pprt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->le = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->ls = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 7;
	ptr_struct->sw_c = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->sw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->dm_ig = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->p_c = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->s = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->prbs_modes_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->modulation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->prbs_mode_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 96;
	ptr_struct->lane_rate_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->lane_rate_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 168;
	ptr_struct->prbs_lock_status_ext = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 164;
	ptr_struct->prbs_lock_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 160;
	ptr_struct->prbs_rx_tuning_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_pprt_reg_ext_print(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pprt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "le                   : " UH_FMT "\n", ptr_struct->le);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ls                   : " UH_FMT "\n", ptr_struct->ls);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane                 : " UH_FMT "\n", ptr_struct->lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_c                 : " UH_FMT "\n", ptr_struct->sw_c);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw                   : " UH_FMT "\n", ptr_struct->sw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dm_ig                : " UH_FMT "\n", ptr_struct->dm_ig);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p_c                  : " UH_FMT "\n", ptr_struct->p_c);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "s                    : " UH_FMT "\n", ptr_struct->s);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : " UH_FMT "\n", ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_modes_cap       : " U32H_FMT "\n", ptr_struct->prbs_modes_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modulation           : " UH_FMT "\n", ptr_struct->modulation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_mode_admin      : " UH_FMT "\n", ptr_struct->prbs_mode_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_cap        : " UH_FMT "\n", ptr_struct->lane_rate_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_oper       : " UH_FMT "\n", ptr_struct->lane_rate_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_lock_status_ext : " UH_FMT "\n", ptr_struct->prbs_lock_status_ext);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_lock_status     : " UH_FMT "\n", ptr_struct->prbs_lock_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_rx_tuning_status : " UH_FMT "\n", ptr_struct->prbs_rx_tuning_status);
}

unsigned int reg_access_gpu_pprt_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPRT_REG_EXT_SIZE;
}

void reg_access_gpu_pprt_reg_ext_dump(const struct reg_access_gpu_pprt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pprt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppsc_reg_ext_pack(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->mod_pwr_opt);
	offset = 156;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->wrps_admin);
	offset = 188;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->wrps_status);
	offset = 216;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->down_threshold);
	offset = 200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->up_threshold);
	offset = 193;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->down_th_vld);
	offset = 192;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->up_th_vld);
	offset = 284;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->srps_admin);
}

void reg_access_gpu_ppsc_reg_ext_unpack(struct reg_access_gpu_ppsc_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->mod_pwr_opt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 156;
	ptr_struct->wrps_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 188;
	ptr_struct->wrps_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 216;
	ptr_struct->down_threshold = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 200;
	ptr_struct->up_threshold = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 193;
	ptr_struct->down_th_vld = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 192;
	ptr_struct->up_th_vld = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 284;
	ptr_struct->srps_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
}

void reg_access_gpu_ppsc_reg_ext_print(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppsc_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mod_pwr_opt          : " UH_FMT "\n", ptr_struct->mod_pwr_opt);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrps_admin           : " UH_FMT "\n", ptr_struct->wrps_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "wrps_status          : " UH_FMT "\n", ptr_struct->wrps_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_threshold       : " UH_FMT "\n", ptr_struct->down_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_threshold         : " UH_FMT "\n", ptr_struct->up_threshold);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "down_th_vld          : " UH_FMT "\n", ptr_struct->down_th_vld);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "up_th_vld            : " UH_FMT "\n", ptr_struct->up_th_vld);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "srps_admin           : " UH_FMT "\n", ptr_struct->srps_admin);
}

unsigned int reg_access_gpu_ppsc_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPSC_REG_EXT_SIZE;
}

void reg_access_gpu_ppsc_reg_ext_dump(const struct reg_access_gpu_ppsc_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppsc_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppslc_ext_pack(const struct reg_access_gpu_ppslc_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_req_en);
	offset = 95;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_fw_req_en);
	offset = 91;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_cap_adv);
	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_fw_cap_adv);
	offset = 97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ignore_pred_pm);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pred_algo_en);
	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->hp_queues_bitmap);
	offset = 214;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->l1_hw_active_time);
	offset = 246;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->l1_hw_inactive_time);
	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 416, 1);
		adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->qem[i]);
	}
}

void reg_access_gpu_ppslc_ext_unpack(struct reg_access_gpu_ppslc_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;
	int i;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->l1_req_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 95;
	ptr_struct->l1_fw_req_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 91;
	ptr_struct->l1_cap_adv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 87;
	ptr_struct->l1_fw_cap_adv = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 97;
	ptr_struct->ignore_pred_pm = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->pred_algo_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	ptr_struct->hp_queues_bitmap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 214;
	ptr_struct->l1_hw_active_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	offset = 246;
	ptr_struct->l1_hw_inactive_time = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
	for (i = 0; i < 20; ++i) {
		offset = adb2c_calc_array_field_address(280, 8, i, 416, 1);
		ptr_struct->qem[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}
}

void reg_access_gpu_ppslc_ext_print(const struct reg_access_gpu_ppslc_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppslc_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_req_en            : " UH_FMT "\n", ptr_struct->l1_req_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_fw_req_en         : " UH_FMT "\n", ptr_struct->l1_fw_req_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_cap_adv           : " UH_FMT "\n", ptr_struct->l1_cap_adv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_fw_cap_adv        : " UH_FMT "\n", ptr_struct->l1_fw_cap_adv);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ignore_pred_pm       : " UH_FMT "\n", ptr_struct->ignore_pred_pm);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pred_algo_en         : " UH_FMT "\n", ptr_struct->pred_algo_en);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "hp_queues_bitmap     : " U32H_FMT "\n", ptr_struct->hp_queues_bitmap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_hw_active_time    : " UH_FMT "\n", ptr_struct->l1_hw_active_time);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_hw_inactive_time  : " UH_FMT "\n", ptr_struct->l1_hw_inactive_time);
	for (i = 0; i < 20; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "qem_%03d             : " UH_FMT "\n", i, ptr_struct->qem[i]);
	}
}

unsigned int reg_access_gpu_ppslc_ext_size(void)
{
	return REG_ACCESS_GPU_PPSLC_EXT_SIZE;
}

void reg_access_gpu_ppslc_ext_dump(const struct reg_access_gpu_ppslc_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppslc_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ppsls_ext_pack(const struct reg_access_gpu_ppsls_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 47;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_fw_mode_cap);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_cap);
	offset = 35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fw_mode_remote);
	offset = 34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fw_mode_act);
	offset = 33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fw_mode_neg_status);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->l1_neg_status);
}

void reg_access_gpu_ppsls_ext_unpack(struct reg_access_gpu_ppsls_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 47;
	ptr_struct->l1_fw_mode_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 45;
	ptr_struct->l1_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 35;
	ptr_struct->fw_mode_remote = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 34;
	ptr_struct->fw_mode_act = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 33;
	ptr_struct->fw_mode_neg_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->l1_neg_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_ppsls_ext_print(const struct reg_access_gpu_ppsls_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ppsls_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_fw_mode_cap       : " UH_FMT "\n", ptr_struct->l1_fw_mode_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_cap               : " UH_FMT "\n", ptr_struct->l1_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_mode_remote       : " UH_FMT "\n", ptr_struct->fw_mode_remote);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_mode_act          : " UH_FMT "\n", ptr_struct->fw_mode_act);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "fw_mode_neg_status   : " UH_FMT "\n", ptr_struct->fw_mode_neg_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "l1_neg_status        : " UH_FMT "\n", ptr_struct->l1_neg_status);
}

unsigned int reg_access_gpu_ppsls_ext_size(void)
{
	return REG_ACCESS_GPU_PPSLS_EXT_SIZE;
}

void reg_access_gpu_ppsls_ext_dump(const struct reg_access_gpu_ppsls_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ppsls_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pptt_reg_ext_pack(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->le);
	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ls);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sw_c);
	offset = 6;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sw);
	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dm_ig);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p_c);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->e);
	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->prbs_modes_cap);
	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->modulation);
	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->prbs_mode_admin);
	offset = 127;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->prbs_fec_cap);
	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_cap);
	offset = 159;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->prbs_fec_admin);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->lane_rate_admin);
}

void reg_access_gpu_pptt_reg_ext_unpack(struct reg_access_gpu_pptt_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->le = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 30;
	ptr_struct->ls = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 7;
	ptr_struct->sw_c = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 6;
	ptr_struct->sw = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 5;
	ptr_struct->dm_ig = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 4;
	ptr_struct->p_c = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 3;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 32;
	ptr_struct->prbs_modes_cap = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 92;
	ptr_struct->modulation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->prbs_mode_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 127;
	ptr_struct->prbs_fec_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 96;
	ptr_struct->lane_rate_cap = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 159;
	ptr_struct->prbs_fec_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 128;
	ptr_struct->lane_rate_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
}

void reg_access_gpu_pptt_reg_ext_print(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pptt_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "le                   : " UH_FMT "\n", ptr_struct->le);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ls                   : " UH_FMT "\n", ptr_struct->ls);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : " UH_FMT "\n", ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane                 : " UH_FMT "\n", ptr_struct->lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw_c                 : " UH_FMT "\n", ptr_struct->sw_c);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sw                   : " UH_FMT "\n", ptr_struct->sw);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "dm_ig                : " UH_FMT "\n", ptr_struct->dm_ig);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p_c                  : " UH_FMT "\n", ptr_struct->p_c);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "p                    : " UH_FMT "\n", ptr_struct->p);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "e                    : " UH_FMT "\n", ptr_struct->e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_modes_cap       : " U32H_FMT "\n", ptr_struct->prbs_modes_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "modulation           : " UH_FMT "\n", ptr_struct->modulation);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_mode_admin      : " UH_FMT "\n", ptr_struct->prbs_mode_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_fec_cap         : " UH_FMT "\n", ptr_struct->prbs_fec_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_cap        : " UH_FMT "\n", ptr_struct->lane_rate_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prbs_fec_admin       : " UH_FMT "\n", ptr_struct->prbs_fec_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_admin      : " UH_FMT "\n", ptr_struct->lane_rate_admin);
}

unsigned int reg_access_gpu_pptt_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PPTT_REG_EXT_SIZE;
}

void reg_access_gpu_pptt_reg_ext_dump(const struct reg_access_gpu_pptt_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pptt_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_prtl_reg_ext_pack(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rtt_support);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->latency_accuracy);
	offset = 44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->latency_res);
	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->local_phy_latency);
	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->local_mod_dp_latency);
	offset = 136;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->round_trip_latency);
}

void reg_access_gpu_prtl_reg_ext_unpack(struct reg_access_gpu_prtl_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->rtt_support = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 56;
	ptr_struct->latency_accuracy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 44;
	ptr_struct->latency_res = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 80;
	ptr_struct->local_phy_latency = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 112;
	ptr_struct->local_mod_dp_latency = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 136;
	ptr_struct->round_trip_latency = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);
}

void reg_access_gpu_prtl_reg_ext_print(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_prtl_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : %s (" UH_FMT ")\n", (ptr_struct->pnat == 0 ? ("Local_port_number") : ((ptr_struct->pnat == 1 ? ("IB_port_number") : ((ptr_struct->pnat == 3 ? ("Out_of_band") : ("unknown")))))), ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "rtt_support          : " UH_FMT "\n", ptr_struct->rtt_support);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "latency_accuracy     : " UH_FMT "\n", ptr_struct->latency_accuracy);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "latency_res          : " UH_FMT "\n", ptr_struct->latency_res);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_phy_latency    : " UH_FMT "\n", ptr_struct->local_phy_latency);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_mod_dp_latency : " UH_FMT "\n", ptr_struct->local_mod_dp_latency);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "round_trip_latency   : " UH_FMT "\n", ptr_struct->round_trip_latency);
}

unsigned int reg_access_gpu_prtl_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PRTL_REG_EXT_SIZE;
}

void reg_access_gpu_prtl_reg_ext_dump(const struct reg_access_gpu_prtl_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_prtl_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pter_reg_ext_pack(const struct reg_access_gpu_pter_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->error_page);
	offset = 32;
	switch (ptr_struct->error_page) {
	case 0x0:
		offset = 32;
		reg_access_gpu_pter_phy_page_reg_ext_pack(&(ptr_struct->page_data.pter_phy_page_reg_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 32;
		reg_access_gpu_pter_port_page_reg_ext_pack(&(ptr_struct->page_data.pter_port_page_reg_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_pter_reg_ext_unpack(struct reg_access_gpu_pter_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->error_page = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	switch (ptr_struct->error_page) {
	case 0x0:
		offset = 32;
		reg_access_gpu_pter_phy_page_reg_ext_unpack(&(ptr_struct->page_data.pter_phy_page_reg_ext), ptr_buff + offset / 8);
		break;
	case 0x1:
		offset = 32;
		reg_access_gpu_pter_port_page_reg_ext_unpack(&(ptr_struct->page_data.pter_port_page_reg_ext), ptr_buff + offset / 8);
		break;
	default:
		break;
	}
}

void reg_access_gpu_pter_reg_ext_print(const struct reg_access_gpu_pter_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pter_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "error_page           : %s (" UH_FMT ")\n", (ptr_struct->error_page == 0 ? ("Injection_of_Phy_Errors") : ((ptr_struct->error_page == 1 ? ("Injection_of_Port_Errors") : ("unknown")))), ptr_struct->error_page);
	switch (ptr_struct->error_page) {
	case 0x0:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pter_phy_page_reg_ext:\n");
		reg_access_gpu_pter_phy_page_reg_ext_print(&(ptr_struct->page_data.pter_phy_page_reg_ext), fd, indent_level + 1);
		break;
	case 0x1:
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "pter_port_page_reg_ext:\n");
		reg_access_gpu_pter_port_page_reg_ext_print(&(ptr_struct->page_data.pter_port_page_reg_ext), fd, indent_level + 1);
		break;
	default:
		break;
	}
}

unsigned int reg_access_gpu_pter_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PTER_REG_EXT_SIZE;
}

void reg_access_gpu_pter_reg_ext_dump(const struct reg_access_gpu_pter_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pter_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ptsb_ext_pack(const struct reg_access_gpu_ptsb_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sl);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->vc);
	offset = 52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->pipe);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->type);
	offset = 86;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->burst_send);
}

void reg_access_gpu_ptsb_ext_unpack(struct reg_access_gpu_ptsb_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 60;
	ptr_struct->sl = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 56;
	ptr_struct->vc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 52;
	ptr_struct->pipe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 48;
	ptr_struct->type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 86;
	ptr_struct->burst_send = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);
}

void reg_access_gpu_ptsb_ext_print(const struct reg_access_gpu_ptsb_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ptsb_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sl                   : " UH_FMT "\n", ptr_struct->sl);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "vc                   : " UH_FMT "\n", ptr_struct->vc);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pipe                 : " UH_FMT "\n", ptr_struct->pipe);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "type                 : " UH_FMT "\n", ptr_struct->type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "burst_send           : " UH_FMT "\n", ptr_struct->burst_send);
}

unsigned int reg_access_gpu_ptsb_ext_size(void)
{
	return REG_ACCESS_GPU_PTSB_EXT_SIZE;
}

void reg_access_gpu_ptsb_ext_dump(const struct reg_access_gpu_ptsb_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ptsb_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ptsr_ext_pack(const struct reg_access_gpu_ptsr_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ts);
}

void reg_access_gpu_ptsr_ext_unpack(struct reg_access_gpu_ptsr_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 63;
	ptr_struct->ts = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_ptsr_ext_print(const struct reg_access_gpu_ptsr_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ptsr_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ts                   : " UH_FMT "\n", ptr_struct->ts);
}

unsigned int reg_access_gpu_ptsr_ext_size(void)
{
	return REG_ACCESS_GPU_PTSR_EXT_SIZE;
}

void reg_access_gpu_ptsr_ext_dump(const struct reg_access_gpu_ptsr_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ptsr_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_ptys_reg_ext_pack(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->proto_mask);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->transmit_allowed);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->plane_ind);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->tx_ready_e);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ee_tx_ready);
	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_cap);
	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->an_disable_admin);
	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data_rate_oper);
	offset = 36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->max_port_rate);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->an_status);
	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_capability);
	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_capability);
	offset = 144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_capability);
	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_capability);
	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_admin);
	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_admin);
	offset = 240;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_admin);
	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_admin);
	offset = 256;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->ext_eth_proto_oper);
	offset = 288;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->eth_proto_oper);
	offset = 336;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_proto_oper);
	offset = 320;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->ib_link_width_oper);
	offset = 380;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->connector_type);
	offset = 360;
	adb2c_push_bits_to_buff(ptr_buff, offset, 20, (u_int32_t)ptr_struct->lane_rate_oper);
	offset = 359;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_active);
	offset = 358;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_admin);
	offset = 354;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->force_lt_frames_admin);
	offset = 353;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->force_lt_frames_cap);
	offset = 352;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->xdr_2x_slow_cap);
}

void reg_access_gpu_ptys_reg_ext_unpack(struct reg_access_gpu_ptys_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 29;
	ptr_struct->proto_mask = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 28;
	ptr_struct->transmit_allowed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->plane_ind = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->tx_ready_e = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 3;
	ptr_struct->ee_tx_ready = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 2;
	ptr_struct->an_disable_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 1;
	ptr_struct->an_disable_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 48;
	ptr_struct->data_rate_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 36;
	ptr_struct->max_port_rate = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);
	offset = 32;
	ptr_struct->an_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 64;
	ptr_struct->ext_eth_proto_capability = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->eth_proto_capability = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->ib_proto_capability = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->ib_link_width_capability = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 160;
	ptr_struct->ext_eth_proto_admin = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 192;
	ptr_struct->eth_proto_admin = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 240;
	ptr_struct->ib_proto_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 224;
	ptr_struct->ib_link_width_admin = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 256;
	ptr_struct->ext_eth_proto_oper = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->eth_proto_oper = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 336;
	ptr_struct->ib_proto_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 320;
	ptr_struct->ib_link_width_oper = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 380;
	ptr_struct->connector_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 360;
	ptr_struct->lane_rate_oper = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 20);
	offset = 359;
	ptr_struct->xdr_2x_slow_active = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 358;
	ptr_struct->xdr_2x_slow_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 354;
	ptr_struct->force_lt_frames_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 353;
	ptr_struct->force_lt_frames_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 352;
	ptr_struct->xdr_2x_slow_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
}

void reg_access_gpu_ptys_reg_ext_print(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_ptys_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "proto_mask           : %s (" UH_FMT ")\n", (ptr_struct->proto_mask == 1 ? ("InfiniBand") : ((ptr_struct->proto_mask == 4 ? ("Ethernet") : ("unknown")))), ptr_struct->proto_mask);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "transmit_allowed     : %s (" UH_FMT ")\n", (ptr_struct->transmit_allowed == 0 ? ("transmit_not_allowed") : ((ptr_struct->transmit_allowed == 1 ? ("transmit_allowed") : ("unknown")))), ptr_struct->transmit_allowed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plane_ind            : " UH_FMT "\n", ptr_struct->plane_ind);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("Near") : ((ptr_struct->port_type == 2 ? ("Internal_IC_Port") : ((ptr_struct->port_type == 3 ? ("Far") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_ready_e           : " UH_FMT "\n", ptr_struct->tx_ready_e);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ee_tx_ready          : " UH_FMT "\n", ptr_struct->ee_tx_ready);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_cap       : " UH_FMT "\n", ptr_struct->an_disable_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_disable_admin     : " UH_FMT "\n", ptr_struct->an_disable_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "data_rate_oper       : " UH_FMT "\n", ptr_struct->data_rate_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "max_port_rate        : " UH_FMT "\n", ptr_struct->max_port_rate);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "an_status            : %s (" UH_FMT ")\n", (ptr_struct->an_status == 0 ? ("Status_is_unavailable") : ((ptr_struct->an_status == 1 ? ("AN_completed_successfully") : ((ptr_struct->an_status == 2 ? ("AN_performed_but_failed") : ((ptr_struct->an_status == 3 ? ("AN_was_not_performed_link_is_up") : ((ptr_struct->an_status == 4 ? ("AN_was_not_performed_link_is_down") : ("unknown")))))))))), ptr_struct->an_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_capability : " U32H_FMT "\n", ptr_struct->ext_eth_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_capability : " U32H_FMT "\n", ptr_struct->eth_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_capability  : %s (" UH_FMT ")\n", (ptr_struct->ib_proto_capability == 1 ? ("SDR") : ((ptr_struct->ib_proto_capability == 2 ? ("DDR") : ((ptr_struct->ib_proto_capability == 4 ? ("QDR") : ((ptr_struct->ib_proto_capability == 8 ? ("FDR10") : ((ptr_struct->ib_proto_capability == 16 ? ("FDR") : ((ptr_struct->ib_proto_capability == 32 ? ("EDR") : ((ptr_struct->ib_proto_capability == 64 ? ("HDR") : ((ptr_struct->ib_proto_capability == 128 ? ("NDR") : ((ptr_struct->ib_proto_capability == 256 ? ("XDR") : ("unknown")))))))))))))))))), ptr_struct->ib_proto_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_capability : " UH_FMT "\n", ptr_struct->ib_link_width_capability);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_admin  : " U32H_FMT "\n", ptr_struct->ext_eth_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_admin      : " U32H_FMT "\n", ptr_struct->eth_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_admin       : " UH_FMT "\n", ptr_struct->ib_proto_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_admin  : " UH_FMT "\n", ptr_struct->ib_link_width_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ext_eth_proto_oper   : " U32H_FMT "\n", ptr_struct->ext_eth_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "eth_proto_oper       : " U32H_FMT "\n", ptr_struct->eth_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_proto_oper        : " UH_FMT "\n", ptr_struct->ib_proto_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ib_link_width_oper   : " UH_FMT "\n", ptr_struct->ib_link_width_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "connector_type       : %s (" UH_FMT ")\n", (ptr_struct->connector_type == 0 ? ("No_connector_or_unknown") : ((ptr_struct->connector_type == 1 ? ("PORT_NONE") : ((ptr_struct->connector_type == 2 ? ("PORT_TP") : ((ptr_struct->connector_type == 3 ? ("PORT_AUI") : ((ptr_struct->connector_type == 4 ? ("PORT_BNC") : ((ptr_struct->connector_type == 5 ? ("PORT_MII") : ((ptr_struct->connector_type == 6 ? ("PORT_FIBRE") : ((ptr_struct->connector_type == 7 ? ("PORT_DA") : ((ptr_struct->connector_type == 8 ? ("PORT_OTHER") : ("unknown")))))))))))))))))), ptr_struct->connector_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_rate_oper       : " UH_FMT "\n", ptr_struct->lane_rate_oper);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_active   : " UH_FMT "\n", ptr_struct->xdr_2x_slow_active);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_admin    : " UH_FMT "\n", ptr_struct->xdr_2x_slow_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_lt_frames_admin : " UH_FMT "\n", ptr_struct->force_lt_frames_admin);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "force_lt_frames_cap  : " UH_FMT "\n", ptr_struct->force_lt_frames_cap);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "xdr_2x_slow_cap      : " UH_FMT "\n", ptr_struct->xdr_2x_slow_cap);
}

unsigned int reg_access_gpu_ptys_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PTYS_REG_EXT_SIZE;
}

void reg_access_gpu_ptys_reg_ext_dump(const struct reg_access_gpu_ptys_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_ptys_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_pude_reg_ext_pack(const struct reg_access_gpu_pude_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->oper_status);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->admin_status);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->swid);
	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->physical_state_status);
	offset = 45;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->logical_state_status);
	offset = 32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_reason_opcode);
}

void reg_access_gpu_pude_reg_ext_unpack(struct reg_access_gpu_pude_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 28;
	ptr_struct->oper_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->admin_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 0;
	ptr_struct->swid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 56;
	ptr_struct->physical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 45;
	ptr_struct->logical_state_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 32;
	ptr_struct->local_reason_opcode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
}

void reg_access_gpu_pude_reg_ext_print(const struct reg_access_gpu_pude_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_pude_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "oper_status          : " UH_FMT "\n", ptr_struct->oper_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "admin_status         : " UH_FMT "\n", ptr_struct->admin_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "swid                 : " UH_FMT "\n", ptr_struct->swid);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "physical_state_status : %s (" UH_FMT ")\n", (ptr_struct->physical_state_status == 0 ? ("N_A") : ((ptr_struct->physical_state_status == 1 ? ("Sleep") : ((ptr_struct->physical_state_status == 2 ? ("Polling") : ((ptr_struct->physical_state_status == 3 ? ("Disabled") : ((ptr_struct->physical_state_status == 4 ? ("PortConfigurationTraining") : ((ptr_struct->physical_state_status == 5 ? ("LinkUp") : ("unknown")))))))))))), ptr_struct->physical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "logical_state_status : " UH_FMT "\n", ptr_struct->logical_state_status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_reason_opcode  : %s (" UH_FMT ")\n", (ptr_struct->local_reason_opcode == 0 ? ("No_link_down_indication") : ((ptr_struct->local_reason_opcode == 1 ? ("Unknown_reason") : ((ptr_struct->local_reason_opcode == 2 ? ("Hi_SER_or_Hi_BER") : ((ptr_struct->local_reason_opcode == 3 ? ("Block_Lock_loss") : ((ptr_struct->local_reason_opcode == 4 ? ("Alignment_loss") : ((ptr_struct->local_reason_opcode == 5 ? ("FEC_sync_loss") : ((ptr_struct->local_reason_opcode == 6 ? ("PLL_lock_loss") : ((ptr_struct->local_reason_opcode == 7 ? ("FIFO_overflow") : ((ptr_struct->local_reason_opcode == 8 ? ("false_SKIP_condition") : ((ptr_struct->local_reason_opcode == 9 ? ("Minor_Error_threshold_exceeded") : ((ptr_struct->local_reason_opcode == 10 ? ("Physical_layer_retransmission_timeout") : ((ptr_struct->local_reason_opcode == 11 ? ("Heartbeat_errors") : ((ptr_struct->local_reason_opcode == 12 ? ("Link_Layer_credit_monitoring_watchdog") : ((ptr_struct->local_reason_opcode == 13 ? ("Link_Layer_integrity_threshold_exceeded") : ((ptr_struct->local_reason_opcode == 14 ? ("Link_Layer_buffer_overrun") : ((ptr_struct->local_reason_opcode == 15 ? ("Down_by_outband_command_with_healthy_link") : ((ptr_struct->local_reason_opcode == 16 ? ("Down_by_outband_command_for_link_with_hi_ber") : ((ptr_struct->local_reason_opcode == 17 ? ("Down_by_inband_command_with_healthy_link") : ((ptr_struct->local_reason_opcode == 18 ? ("Down_by_inband_command_for_link_with_hi_ber") : ((ptr_struct->local_reason_opcode == 19 ? ("Down_by_verification_GW") : ((ptr_struct->local_reason_opcode == 20 ? ("Received_Remote_Fault") : ((ptr_struct->local_reason_opcode == 21 ? ("Received_TS1") : ((ptr_struct->local_reason_opcode == 22 ? ("Down_by_management_command") : ((ptr_struct->local_reason_opcode == 23 ? ("Cable_was_unplugged") : ((ptr_struct->local_reason_opcode == 24 ? ("Cable_access_issue") : ((ptr_struct->local_reason_opcode == 25 ? ("Thermal_shutdown") : ((ptr_struct->local_reason_opcode == 26 ? ("Current_issue") : ((ptr_struct->local_reason_opcode == 27 ? ("Power_budget") : ((ptr_struct->local_reason_opcode == 28 ? ("Fast_recovery_raw_ber") : ((ptr_struct->local_reason_opcode == 29 ? ("Fast_recovery_effective_ber") : ((ptr_struct->local_reason_opcode == 30 ? ("Fast_recovery_symbol_ber") : ((ptr_struct->local_reason_opcode == 31 ? ("Fast_recovery_credit_watchdog") : ((ptr_struct->local_reason_opcode == 32 ? ("Peer_side_down_to_sleep_state") : ((ptr_struct->local_reason_opcode == 33 ? ("Peer_side_down_to_disable_state") : ((ptr_struct->local_reason_opcode == 34 ? ("Peer_side_down_to_disable_and_port_lock") : ((ptr_struct->local_reason_opcode == 35 ? ("Peer_side_down_due_to_thermal_event") : ((ptr_struct->local_reason_opcode == 36 ? ("Peer_side_down_due_to_force_event") : ((ptr_struct->local_reason_opcode == 37 ? ("Peer_side_down_due_to_reset_event") : ("unknown")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))), ptr_struct->local_reason_opcode);
}

unsigned int reg_access_gpu_pude_reg_ext_size(void)
{
	return REG_ACCESS_GPU_PUDE_REG_EXT_SIZE;
}

void reg_access_gpu_pude_reg_ext_dump(const struct reg_access_gpu_pude_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_pude_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_resource_dump_ext_pack(const struct reg_access_gpu_resource_dump_ext *ptr_struct, u_int8_t *ptr_buff)
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
	for (i = 0; i < 38; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 1600, 1);
		adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->inline_data[i]);
	}
}

void reg_access_gpu_resource_dump_ext_unpack(struct reg_access_gpu_resource_dump_ext *ptr_struct, const u_int8_t *ptr_buff)
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
	offset = 64;
	ptr_struct->index1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 96;
	ptr_struct->index2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 144;
	ptr_struct->num_of_obj2 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 128;
	ptr_struct->num_of_obj1 = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);
	offset = 192;
	ptr_struct->device_opaque = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	offset = 256;
	ptr_struct->mkey = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 288;
	ptr_struct->size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	offset = 320;
	ptr_struct->address = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);
	for (i = 0; i < 38; ++i) {
		offset = adb2c_calc_array_field_address(384, 32, i, 1600, 1);
		ptr_struct->inline_data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}
}

void reg_access_gpu_resource_dump_ext_print(const struct reg_access_gpu_resource_dump_ext *ptr_struct, FILE *fd, int indent_level)
{
	int i;

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_resource_dump_ext ========\n");

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
	for (i = 0; i < 38; ++i) {
		adb2c_add_indentation(fd, indent_level);
		fprintf(fd, "inline_data_%03d     : " U32H_FMT "\n", i, ptr_struct->inline_data[i]);
	}
}

unsigned int reg_access_gpu_resource_dump_ext_size(void)
{
	return REG_ACCESS_GPU_RESOURCE_DUMP_EXT_SIZE;
}

void reg_access_gpu_resource_dump_ext_dump(const struct reg_access_gpu_resource_dump_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_resource_dump_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_slrg_reg_ext_pack(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->all_lanes);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->port_type);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->status);
	offset = 32;
	reg_access_gpu_slrg_reg_page_data_auto_ext_pack(&(ptr_struct->page_data), ptr_buff + offset / 8);
}

void reg_access_gpu_slrg_reg_ext_unpack(struct reg_access_gpu_slrg_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 30;
	ptr_struct->all_lanes = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 24;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 0;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 32;
	reg_access_gpu_slrg_reg_page_data_auto_ext_unpack(&(ptr_struct->page_data), ptr_buff + offset / 8);
}

void reg_access_gpu_slrg_reg_ext_print(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_slrg_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "all_lanes            : %s (" UH_FMT ")\n", (ptr_struct->all_lanes == 0 ? ("per_lane_measurement") : ((ptr_struct->all_lanes == 1 ? ("all_lane_measurement") : ("unknown")))), ptr_struct->all_lanes);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("NearEnd_Port") : ((ptr_struct->port_type == 2 ? ("Internal_IC_LR_Port") : ((ptr_struct->port_type == 3 ? ("FarEnd_Port") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane                 : " UH_FMT "\n", ptr_struct->lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : %s (" UH_FMT ")\n", (ptr_struct->version == 0 ? ("prod_40nm") : ((ptr_struct->version == 1 ? ("prod_28nm") : ((ptr_struct->version == 3 ? ("prod_16nm") : ((ptr_struct->version == 4 ? ("prod_7nm") : ((ptr_struct->version == 5 ? ("prod_5nm") : ("unknown")))))))))), ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_data:\n");
	reg_access_gpu_slrg_reg_page_data_auto_ext_print(&(ptr_struct->page_data), fd, indent_level + 1);
}

unsigned int reg_access_gpu_slrg_reg_ext_size(void)
{
	return REG_ACCESS_GPU_SLRG_REG_EXT_SIZE;
}

void reg_access_gpu_slrg_reg_ext_dump(const struct reg_access_gpu_slrg_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_slrg_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_sltp_reg_ext_pack(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->c_db);
	offset = 28;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->port_type);
	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane_speed);
	offset = 20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->lane);
	offset = 18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tx_policy);
	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pnat);
	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);
	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);
	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->status);
	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->lp_msb);
	offset = 32;
	reg_access_gpu_sltp_reg_page_data_auto_ext_pack(&(ptr_struct->page_data), ptr_buff + offset / 8);
}

void reg_access_gpu_sltp_reg_ext_unpack(struct reg_access_gpu_sltp_reg_ext *ptr_struct, const u_int8_t *ptr_buff)
{
	u_int32_t offset;

	offset = 31;
	ptr_struct->c_db = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 28;
	ptr_struct->port_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);
	offset = 24;
	ptr_struct->lane_speed = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 20;
	ptr_struct->lane = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 18;
	ptr_struct->tx_policy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 16;
	ptr_struct->pnat = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	offset = 4;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);
	offset = 3;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);
	offset = 0;
	ptr_struct->lp_msb = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);
	offset = 32;
	reg_access_gpu_sltp_reg_page_data_auto_ext_unpack(&(ptr_struct->page_data), ptr_buff + offset / 8);
}

void reg_access_gpu_sltp_reg_ext_print(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_sltp_reg_ext ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "c_db                 : " UH_FMT "\n", ptr_struct->c_db);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "port_type            : %s (" UH_FMT ")\n", (ptr_struct->port_type == 0 ? ("Network_Port") : ((ptr_struct->port_type == 1 ? ("NearEnd_Port") : ((ptr_struct->port_type == 2 ? ("Internal_IC_LR_Port") : ((ptr_struct->port_type == 3 ? ("FarEnd_Port") : ("unknown")))))))), ptr_struct->port_type);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane_speed           : " UH_FMT "\n", ptr_struct->lane_speed);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lane                 : " UH_FMT "\n", ptr_struct->lane);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "tx_policy            : " UH_FMT "\n", ptr_struct->tx_policy);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pnat                 : " UH_FMT "\n", ptr_struct->pnat);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "local_port           : " UH_FMT "\n", ptr_struct->local_port);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "version              : %s (" UH_FMT ")\n", (ptr_struct->version == 0 ? ("prod_40nm") : ((ptr_struct->version == 1 ? ("prod_28nm") : ((ptr_struct->version == 3 ? ("prod_16nm") : ((ptr_struct->version == 4 ? ("prod_7nm") : ((ptr_struct->version == 5 ? ("prod_5nm") : ("unknown")))))))))), ptr_struct->version);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "status               : " UH_FMT "\n", ptr_struct->status);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "lp_msb               : " UH_FMT "\n", ptr_struct->lp_msb);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "page_data:\n");
	reg_access_gpu_sltp_reg_page_data_auto_ext_print(&(ptr_struct->page_data), fd, indent_level + 1);
}

unsigned int reg_access_gpu_sltp_reg_ext_size(void)
{
	return REG_ACCESS_GPU_SLTP_REG_EXT_SIZE;
}

void reg_access_gpu_sltp_reg_ext_dump(const struct reg_access_gpu_sltp_reg_ext *ptr_struct, FILE *fd)
{
	reg_access_gpu_sltp_reg_ext_print(ptr_struct, fd, 0);
}

void reg_access_gpu_reg_access_gpu_Nodes_pack(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_reg_ext_pack(&(ptr_struct->pddr_reg_ext), ptr_buff);
}

void reg_access_gpu_reg_access_gpu_Nodes_unpack(union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, const u_int8_t *ptr_buff)
{
	reg_access_gpu_pddr_reg_ext_unpack(&(ptr_struct->pddr_reg_ext), ptr_buff);
}

void reg_access_gpu_reg_access_gpu_Nodes_print(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, FILE *fd, int indent_level)
{
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "======== reg_access_gpu_reg_access_gpu_Nodes ========\n");

	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcam_reg_ext:\n");
	reg_access_gpu_pcam_reg_ext_print(&(ptr_struct->pcam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmaos_reg_ext:\n");
	reg_access_gpu_pmaos_reg_ext_print(&(ptr_struct->pmaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pplr_reg_ext:\n");
	reg_access_gpu_pplr_reg_ext_print(&(ptr_struct->pplr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppdfd_ext:\n");
	reg_access_gpu_ppdfd_ext_print(&(ptr_struct->ppdfd_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MLPC_ext:\n");
	reg_access_gpu_MLPC_ext_print(&(ptr_struct->MLPC_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pude_reg_ext:\n");
	reg_access_gpu_pude_reg_ext_print(&(ptr_struct->pude_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmpr_reg_ext:\n");
	reg_access_gpu_pmpr_reg_ext_print(&(ptr_struct->pmpr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MRFV_ext:\n");
	reg_access_gpu_MRFV_ext_print(&(ptr_struct->MRFV_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pddr_reg_ext:\n");
	reg_access_gpu_pddr_reg_ext_print(&(ptr_struct->pddr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptsr_ext:\n");
	reg_access_gpu_ptsr_ext_print(&(ptr_struct->ptsr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gpgb_ext:\n");
	reg_access_gpu_gpgb_ext_print(&(ptr_struct->gpgb_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcam_reg_ext:\n");
	reg_access_gpu_mcam_reg_ext_print(&(ptr_struct->mcam_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppcnt_reg_ext:\n");
	reg_access_gpu_ppcnt_reg_ext_print(&(ptr_struct->ppcnt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mteim_reg_ext:\n");
	reg_access_gpu_mteim_reg_ext_print(&(ptr_struct->mteim_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pcap_reg_ext:\n");
	reg_access_gpu_pcap_reg_ext_print(&(ptr_struct->pcap_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pltc_reg_ext:\n");
	reg_access_gpu_pltc_reg_ext_print(&(ptr_struct->pltc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pplm_reg_ext:\n");
	reg_access_gpu_pplm_reg_ext_print(&(ptr_struct->pplm_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mpscr_ext:\n");
	reg_access_gpu_mpscr_ext_print(&(ptr_struct->mpscr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pguid_reg_ext:\n");
	reg_access_gpu_pguid_reg_ext_print(&(ptr_struct->pguid_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmtm_reg_ext:\n");
	reg_access_gpu_pmtm_reg_ext_print(&(ptr_struct->pmtm_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtecr_ext:\n");
	reg_access_gpu_mtecr_ext_print(&(ptr_struct->mtecr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_ctrl_reg_ext:\n");
	reg_access_gpu_mtrc_ctrl_reg_ext_print(&(ptr_struct->mtrc_ctrl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptys_reg_ext:\n");
	reg_access_gpu_ptys_reg_ext_print(&(ptr_struct->ptys_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "paos_reg_ext:\n");
	reg_access_gpu_paos_reg_ext_print(&(ptr_struct->paos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmlp_reg_ext:\n");
	reg_access_gpu_pmlp_reg_ext_print(&(ptr_struct->pmlp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmmp_reg_ext:\n");
	reg_access_gpu_pmmp_reg_ext_print(&(ptr_struct->pmmp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pbsr_reg_ext:\n");
	reg_access_gpu_pbsr_reg_ext_print(&(ptr_struct->pbsr_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mmdio_ext:\n");
	reg_access_gpu_mmdio_ext_print(&(ptr_struct->mmdio_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtmp_ext:\n");
	reg_access_gpu_mtmp_ext_print(&(ptr_struct->mtmp_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "plib_reg_ext:\n");
	reg_access_gpu_plib_reg_ext_print(&(ptr_struct->plib_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmpt_reg_ext:\n");
	reg_access_gpu_pmpt_reg_ext_print(&(ptr_struct->pmpt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "slrg_reg_ext:\n");
	reg_access_gpu_slrg_reg_ext_print(&(ptr_struct->slrg_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcsr:\n");
	reg_access_gpu_mcsr_print(&(ptr_struct->mcsr), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gsguid_ext:\n");
	reg_access_gpu_gsguid_ext_print(&(ptr_struct->gsguid_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pphcr_ext:\n");
	reg_access_gpu_pphcr_ext_print(&(ptr_struct->pphcr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtim_ext:\n");
	reg_access_gpu_mtim_ext_print(&(ptr_struct->mtim_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "gplid:\n");
	reg_access_gpu_gplid_print(&(ptr_struct->gplid), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "sltp_reg_ext:\n");
	reg_access_gpu_sltp_reg_ext_print(&(ptr_struct->sltp_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppslc_ext:\n");
	reg_access_gpu_ppslc_ext_print(&(ptr_struct->ppslc_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pbwr_ext:\n");
	reg_access_gpu_pbwr_ext_print(&(ptr_struct->pbwr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtwe_ext:\n");
	reg_access_gpu_mtwe_ext_print(&(ptr_struct->mtwe_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtewe_ext:\n");
	reg_access_gpu_mtewe_ext_print(&(ptr_struct->mtewe_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtie_ext:\n");
	reg_access_gpu_mtie_ext_print(&(ptr_struct->mtie_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pptt_reg_ext:\n");
	reg_access_gpu_pptt_reg_ext_print(&(ptr_struct->pptt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pprt_reg_ext:\n");
	reg_access_gpu_pprt_reg_ext_print(&(ptr_struct->pprt_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ghpkt_ext:\n");
	reg_access_gpu_ghpkt_ext_print(&(ptr_struct->ghpkt_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mdrcr_ext:\n");
	reg_access_gpu_mdrcr_ext_print(&(ptr_struct->mdrcr_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pbwc_ext:\n");
	reg_access_gpu_pbwc_ext_print(&(ptr_struct->pbwc_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtcap_ext:\n");
	reg_access_gpu_mtcap_ext_print(&(ptr_struct->mtcap_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcion_ext:\n");
	reg_access_gpu_mcion_ext_print(&(ptr_struct->mcion_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "MTSR_ext:\n");
	reg_access_gpu_MTSR_ext_print(&(ptr_struct->MTSR_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pter_reg_ext:\n");
	reg_access_gpu_pter_reg_ext_print(&(ptr_struct->pter_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_conf_reg_ext:\n");
	reg_access_gpu_mtrc_conf_reg_ext_print(&(ptr_struct->mtrc_conf_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "prtl_reg_ext:\n");
	reg_access_gpu_prtl_reg_ext_print(&(ptr_struct->prtl_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppsls_ext:\n");
	reg_access_gpu_ppsls_ext_print(&(ptr_struct->ppsls_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ptsb_ext:\n");
	reg_access_gpu_ptsb_ext_print(&(ptr_struct->ptsb_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmpd_reg_ext:\n");
	reg_access_gpu_pmpd_reg_ext_print(&(ptr_struct->pmpd_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtsde:\n");
	reg_access_gpu_mtsde_print(&(ptr_struct->mtsde), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mcia_ext:\n");
	reg_access_gpu_mcia_ext_print(&(ptr_struct->mcia_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppsc_reg_ext:\n");
	reg_access_gpu_ppsc_reg_ext_print(&(ptr_struct->ppsc_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "resource_dump_ext:\n");
	reg_access_gpu_resource_dump_ext_print(&(ptr_struct->resource_dump_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mgir_ext:\n");
	reg_access_gpu_mgir_ext_print(&(ptr_struct->mgir_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmtu_reg_ext:\n");
	reg_access_gpu_pmtu_reg_ext_print(&(ptr_struct->pmtu_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "mtrc_cap_reg_ext:\n");
	reg_access_gpu_mtrc_cap_reg_ext_print(&(ptr_struct->mtrc_cap_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "ppaos_reg_ext:\n");
	reg_access_gpu_ppaos_reg_ext_print(&(ptr_struct->ppaos_reg_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pevnt_ext:\n");
	reg_access_gpu_pevnt_ext_print(&(ptr_struct->pevnt_ext), fd, indent_level + 1);
	adb2c_add_indentation(fd, indent_level);
	fprintf(fd, "pmcr_reg_ext:\n");
	reg_access_gpu_pmcr_reg_ext_print(&(ptr_struct->pmcr_reg_ext), fd, indent_level + 1);
}

unsigned int reg_access_gpu_reg_access_gpu_Nodes_size(void)
{
	return REG_ACCESS_GPU_REG_ACCESS_GPU_NODES_SIZE;
}

void reg_access_gpu_reg_access_gpu_Nodes_dump(const union reg_access_gpu_reg_access_gpu_Nodes *ptr_struct, FILE *fd)
{
	reg_access_gpu_reg_access_gpu_Nodes_print(ptr_struct, fd, 0);
}

