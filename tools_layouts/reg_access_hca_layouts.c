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
         *** This file was generated at "2017-05-04 07:31:40"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/prm/hca/int/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_
         ***/
#include "reg_access_hca_layouts.h"

void reg_access_hca_fpga_ctrl_pack(const struct reg_access_hca_fpga_ctrl *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->status);

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation);

	offset = 56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_select_oper);

	offset = 40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->flash_select_admin);

}

void reg_access_hca_fpga_ctrl_unpack(struct reg_access_hca_fpga_ctrl *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 8;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 56;
	ptr_struct->flash_select_oper = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 40;
	ptr_struct->flash_select_admin = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void reg_access_hca_fpga_ctrl_print(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_fpga_ctrl ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "status               : %s (" UH_FMT ")\n", (ptr_struct->status == 0 ? ("Success") : ((ptr_struct->status == 1 ? ("Failure") : ((ptr_struct->status == 2 ? ("In_progress") : ("unknown")))))), ptr_struct->status);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "operation            : %s (" UH_FMT ")\n", (ptr_struct->operation == 1 ? ("LOAD") : ((ptr_struct->operation == 2 ? ("RESET") : ((ptr_struct->operation == 3 ? ("FLASH_SELECT") : ((ptr_struct->operation == 4 ? ("Sandbox_Bypass_On") : ((ptr_struct->operation == 5 ? ("Sandbox_Bypass_Off") : ((ptr_struct->operation == 6 ? ("Reset_Sandbox") : ("unknown")))))))))))), ptr_struct->operation);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_select_oper    : %s (" UH_FMT ")\n", (ptr_struct->flash_select_oper == 0 ? ("Factory_default") : ((ptr_struct->flash_select_oper == 1 ? ("User") : ("unknown")))), ptr_struct->flash_select_oper);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_select_admin   : %s (" UH_FMT ")\n", (ptr_struct->flash_select_admin == 0 ? ("Factory_default") : ((ptr_struct->flash_select_admin == 1 ? ("User") : ("unknown")))), ptr_struct->flash_select_admin);

}

int reg_access_hca_fpga_ctrl_size(void)
{
	 return 16;
}

void reg_access_hca_fpga_ctrl_dump(const struct reg_access_hca_fpga_ctrl *ptr_struct, FILE* file)
{
	reg_access_hca_fpga_ctrl_print(ptr_struct, file, 0);
}

void reg_access_hca_fpga_shell_caps_pack(const struct reg_access_hca_fpga_shell_caps *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->total_rcv_credits);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->max_num_qps);

	offset = 63;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rc);

	offset = 62;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->uc);

	offset = 61;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ud);

	offset = 60;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dc);

	offset = 55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rre);

	offset = 54;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rwe);

	offset = 53;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rae);

	offset = 46;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->qp_type);

	offset = 90;
	adb2c_push_bits_to_buff(ptr_buff, offset, 6, (u_int32_t)ptr_struct->log_ddr_size);

	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_fpga_qp_msg_size);

}

void reg_access_hca_fpga_shell_caps_unpack(struct reg_access_hca_fpga_shell_caps *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->total_rcv_credits = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 0;
	ptr_struct->max_num_qps = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 63;
	ptr_struct->rc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 62;
	ptr_struct->uc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 61;
	ptr_struct->ud = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 60;
	ptr_struct->dc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 55;
	ptr_struct->rre = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 54;
	ptr_struct->rwe = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 53;
	ptr_struct->rae = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 46;
	ptr_struct->qp_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset = 90;
	ptr_struct->log_ddr_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 6);

	offset = 96;
	ptr_struct->max_fpga_qp_msg_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void reg_access_hca_fpga_shell_caps_print(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_fpga_shell_caps ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "total_rcv_credits    : " UH_FMT "\n", ptr_struct->total_rcv_credits);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_num_qps          : " UH_FMT "\n", ptr_struct->max_num_qps);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rc                   : " UH_FMT "\n", ptr_struct->rc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uc                   : " UH_FMT "\n", ptr_struct->uc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ud                   : " UH_FMT "\n", ptr_struct->ud);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dc                   : " UH_FMT "\n", ptr_struct->dc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rre                  : " UH_FMT "\n", ptr_struct->rre);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rwe                  : " UH_FMT "\n", ptr_struct->rwe);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rae                  : " UH_FMT "\n", ptr_struct->rae);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "qp_type              : %s (" UH_FMT ")\n", (ptr_struct->qp_type == 1 ? ("Shell_qp") : ((ptr_struct->qp_type == 2 ? ("Sandbox_qp") : ("unknown")))), ptr_struct->qp_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_ddr_size         : " UH_FMT "\n", ptr_struct->log_ddr_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_fpga_qp_msg_size : " U32H_FMT "\n", ptr_struct->max_fpga_qp_msg_size);

}

int reg_access_hca_fpga_shell_caps_size(void)
{
	 return 64;
}

void reg_access_hca_fpga_shell_caps_dump(const struct reg_access_hca_fpga_shell_caps *ptr_struct, FILE* file)
{
	reg_access_hca_fpga_shell_caps_print(ptr_struct, file, 0);
}

void reg_access_hca_mcc_reg_pack(const struct reg_access_hca_mcc_reg *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->instruction);

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->time_elapsed_since_last_cmd);

	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);

	offset = 72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);

	offset = 124;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->control_state);

	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->error_code);

	offset = 105;
	adb2c_push_bits_to_buff(ptr_buff, offset, 7, (u_int32_t)ptr_struct->control_progress);

	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->handle_owner_host_id);

	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->handle_owner_type);

	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_size);

}

void reg_access_hca_mcc_reg_unpack(struct reg_access_hca_mcc_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->instruction = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 4;
	ptr_struct->time_elapsed_since_last_cmd = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset = 48;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 72;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset = 124;
	ptr_struct->control_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 112;
	ptr_struct->error_code = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 105;
	ptr_struct->control_progress = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 7);

	offset = 100;
	ptr_struct->handle_owner_host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 96;
	ptr_struct->handle_owner_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 128;
	ptr_struct->component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void reg_access_hca_mcc_reg_print(const struct reg_access_hca_mcc_reg *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcc_reg ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "instruction          : " UH_FMT "\n", ptr_struct->instruction);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "time_elapsed_since_last_cmd : " UH_FMT "\n", ptr_struct->time_elapsed_since_last_cmd);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_index      : " UH_FMT "\n", ptr_struct->component_index);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "control_state        : " UH_FMT "\n", ptr_struct->control_state);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "error_code           : " UH_FMT "\n", ptr_struct->error_code);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "control_progress     : " UH_FMT "\n", ptr_struct->control_progress);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "handle_owner_host_id : " UH_FMT "\n", ptr_struct->handle_owner_host_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "handle_owner_type    : " UH_FMT "\n", ptr_struct->handle_owner_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_size       : " U32H_FMT "\n", ptr_struct->component_size);

}

int reg_access_hca_mcc_reg_size(void)
{
	 return 32;
}

void reg_access_hca_mcc_reg_dump(const struct reg_access_hca_mcc_reg *ptr_struct, FILE* file)
{
	reg_access_hca_mcc_reg_print(ptr_struct, file, 0);
}

void reg_access_hca_mcda_reg_pack(const struct reg_access_hca_mcda_reg *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->update_handle);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);

	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->size);


}

void reg_access_hca_mcda_reg_unpack(struct reg_access_hca_mcda_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	ptr_struct->update_handle = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset = 32;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 80;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);


}

void reg_access_hca_mcda_reg_print(const struct reg_access_hca_mcda_reg *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcda_reg ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "update_handle        : " UH_FMT "\n", ptr_struct->update_handle);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "offset               : " U32H_FMT "\n", ptr_struct->offset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "size                 : " UH_FMT "\n", ptr_struct->size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "unlimited array: (data)\n");

}

int reg_access_hca_mcda_reg_size(void)
{
	 return 20;
}

void reg_access_hca_mcda_reg_dump(const struct reg_access_hca_mcda_reg *ptr_struct, FILE* file)
{
	reg_access_hca_mcda_reg_print(ptr_struct, file, 0);
}

void reg_access_hca_mcqi_activation_method_pack(const struct reg_access_hca_mcqi_activation_method *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->all_hosts_sync);

	offset = 4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->auto_activate);

	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_fw_reset);

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_reboot);

	offset = 1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_dc_power_cycle);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pending_server_ac_power_cycle);

}

void reg_access_hca_mcqi_activation_method_unpack(struct reg_access_hca_mcqi_activation_method *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 5;
	ptr_struct->all_hosts_sync = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 4;
	ptr_struct->auto_activate = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 3;
	ptr_struct->pending_fw_reset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 2;
	ptr_struct->pending_server_reboot = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 1;
	ptr_struct->pending_server_dc_power_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 0;
	ptr_struct->pending_server_ac_power_cycle = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void reg_access_hca_mcqi_activation_method_print(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcqi_activation_method ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "all_hosts_sync       : " UH_FMT "\n", ptr_struct->all_hosts_sync);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "auto_activate        : " UH_FMT "\n", ptr_struct->auto_activate);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pending_fw_reset     : " UH_FMT "\n", ptr_struct->pending_fw_reset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pending_server_reboot : " UH_FMT "\n", ptr_struct->pending_server_reboot);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pending_server_dc_power_cycle : " UH_FMT "\n", ptr_struct->pending_server_dc_power_cycle);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pending_server_ac_power_cycle : " UH_FMT "\n", ptr_struct->pending_server_ac_power_cycle);

}

int reg_access_hca_mcqi_activation_method_size(void)
{
	 return 4;
}

void reg_access_hca_mcqi_activation_method_dump(const struct reg_access_hca_mcqi_activation_method *ptr_struct, FILE* file)
{
	reg_access_hca_mcqi_activation_method_print(ptr_struct, file, 0);
}

void reg_access_hca_mcqi_cap_pack(const struct reg_access_hca_mcqi_cap *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->supported_info_bitmask);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_size);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_component_size);

	offset = 112;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->mcda_max_write_size);

	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->log_mcda_word_size);

	offset = 133;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_base_guid_mac);

	offset = 132;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->check_user_timestamp);

	offset = 131;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_psid);

	offset = 130;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->match_chip_id);

	offset = 129;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->signed_updates_only);

	offset = 128;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->rd_en);

}

void reg_access_hca_mcqi_cap_unpack(struct reg_access_hca_mcqi_cap *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	ptr_struct->supported_info_bitmask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 32;
	ptr_struct->component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 64;
	ptr_struct->max_component_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 112;
	ptr_struct->mcda_max_write_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 96;
	ptr_struct->log_mcda_word_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 133;
	ptr_struct->match_base_guid_mac = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 132;
	ptr_struct->check_user_timestamp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 131;
	ptr_struct->match_psid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 130;
	ptr_struct->match_chip_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 129;
	ptr_struct->signed_updates_only = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 128;
	ptr_struct->rd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void reg_access_hca_mcqi_cap_print(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcqi_cap ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "supported_info_bitmask : " U32H_FMT "\n", ptr_struct->supported_info_bitmask);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_size       : " U32H_FMT "\n", ptr_struct->component_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_component_size   : " U32H_FMT "\n", ptr_struct->max_component_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcda_max_write_size  : " UH_FMT "\n", ptr_struct->mcda_max_write_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_mcda_word_size   : " UH_FMT "\n", ptr_struct->log_mcda_word_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "match_base_guid_mac  : " UH_FMT "\n", ptr_struct->match_base_guid_mac);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "check_user_timestamp : " UH_FMT "\n", ptr_struct->check_user_timestamp);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "match_psid           : " UH_FMT "\n", ptr_struct->match_psid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "match_chip_id        : " UH_FMT "\n", ptr_struct->match_chip_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signed_updates_only  : " UH_FMT "\n", ptr_struct->signed_updates_only);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "rd_en                : " UH_FMT "\n", ptr_struct->rd_en);

}

int reg_access_hca_mcqi_cap_size(void)
{
	 return 20;
}

void reg_access_hca_mcqi_cap_dump(const struct reg_access_hca_mcqi_cap *ptr_struct, FILE* file)
{
	reg_access_hca_mcqi_cap_print(ptr_struct, file, 0);
}

void reg_access_hca_mcqi_reg_pack(const struct reg_access_hca_mcqi_reg *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->read_pending_component);

	offset = 91;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->info_type);

	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->info_size);

	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->offset);

	offset = 176;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data_size);


}

void reg_access_hca_mcqi_reg_unpack(struct reg_access_hca_mcqi_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 0;
	ptr_struct->read_pending_component = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 91;
	ptr_struct->info_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset = 96;
	ptr_struct->info_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 128;
	ptr_struct->offset = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 176;
	ptr_struct->data_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);


}

void reg_access_hca_mcqi_reg_print(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcqi_reg ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_index      : " UH_FMT "\n", ptr_struct->component_index);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "read_pending_component : " UH_FMT "\n", ptr_struct->read_pending_component);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "info_type            : " UH_FMT "\n", ptr_struct->info_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "info_size            : " U32H_FMT "\n", ptr_struct->info_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "offset               : " U32H_FMT "\n", ptr_struct->offset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data_size            : " UH_FMT "\n", ptr_struct->data_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "unlimited array: (data)\n");

}

int reg_access_hca_mcqi_reg_size(void)
{
	 return 28;
}

void reg_access_hca_mcqi_reg_dump(const struct reg_access_hca_mcqi_reg *ptr_struct, FILE* file)
{
	reg_access_hca_mcqi_reg_print(ptr_struct, file, 0);
}

void reg_access_hca_mcqs_reg_pack(const struct reg_access_hca_mcqs_reg *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->component_index);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->last_index_flag);

	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->identifier);

	offset = 92;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->component_update_state);

	offset = 87;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->component_status);

	offset = 100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_update_state_changer_host_id);

	offset = 96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->last_update_state_changer_type);

}

void reg_access_hca_mcqs_reg_unpack(struct reg_access_hca_mcqs_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	ptr_struct->component_index = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 0;
	ptr_struct->last_index_flag = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 48;
	ptr_struct->identifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 92;
	ptr_struct->component_update_state = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 87;
	ptr_struct->component_status = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset = 100;
	ptr_struct->last_update_state_changer_host_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset = 96;
	ptr_struct->last_update_state_changer_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

}

void reg_access_hca_mcqs_reg_print(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcqs_reg ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_index      : " UH_FMT "\n", ptr_struct->component_index);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "last_index_flag      : " UH_FMT "\n", ptr_struct->last_index_flag);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "identifier           : " UH_FMT "\n", ptr_struct->identifier);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_update_state : " UH_FMT "\n", ptr_struct->component_update_state);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "component_status     : " UH_FMT "\n", ptr_struct->component_status);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "last_update_state_changer_host_id : " UH_FMT "\n", ptr_struct->last_update_state_changer_host_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "last_update_state_changer_type : " UH_FMT "\n", ptr_struct->last_update_state_changer_type);

}

int reg_access_hca_mcqs_reg_size(void)
{
	 return 16;
}

void reg_access_hca_mcqs_reg_dump(const struct reg_access_hca_mcqs_reg *ptr_struct, FILE* file)
{
	reg_access_hca_mcqs_reg_print(ptr_struct, file, 0);
}

void reg_access_hca_mgir_pack(const struct reg_access_hca_mgir *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 32; i++) {
	offset = adb2c_calc_array_field_address(24, 8, i, 1024, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->hw_info[i]);
	}

	for (i = 0; i < 64; i++) {
	offset = adb2c_calc_array_field_address(280, 8, i, 1024, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_info[i]);
	}

	for (i = 0; i < 32; i++) {
	offset = adb2c_calc_array_field_address(792, 8, i, 1024, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->sw_info[i]);
	}

}

void reg_access_hca_mgir_unpack(struct reg_access_hca_mgir *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 32; i++) {
	offset = adb2c_calc_array_field_address(24, 8, i, 1024, 1);
	ptr_struct->hw_info[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	for (i = 0; i < 64; i++) {
	offset = adb2c_calc_array_field_address(280, 8, i, 1024, 1);
	ptr_struct->fw_info[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	for (i = 0; i < 32; i++) {
	offset = adb2c_calc_array_field_address(792, 8, i, 1024, 1);
	ptr_struct->sw_info[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void reg_access_hca_mgir_print(const struct reg_access_hca_mgir *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mgir ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	for (i = 0; i < 32; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "hw_info_%03d         : " UH_FMT "\n", i, ptr_struct->hw_info[i]);
	}

	for (i = 0; i < 64; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_info_%03d         : " UH_FMT "\n", i, ptr_struct->fw_info[i]);
	}

	for (i = 0; i < 32; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sw_info_%03d         : " UH_FMT "\n", i, ptr_struct->sw_info[i]);
	}

}

int reg_access_hca_mgir_size(void)
{
	 return 128;
}

void reg_access_hca_mgir_dump(const struct reg_access_hca_mgir *ptr_struct, FILE* file)
{
	reg_access_hca_mgir_print(ptr_struct, file, 0);
}

void reg_access_hca_mqis_reg_pack(const struct reg_access_hca_mqis_reg *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->info_type);

	offset = 48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->info_length);

	offset = 80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->read_length);

	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->read_offset);


}

void reg_access_hca_mqis_reg_unpack(struct reg_access_hca_mqis_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->info_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 48;
	ptr_struct->info_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 80;
	ptr_struct->read_length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 64;
	ptr_struct->read_offset = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);


}

void reg_access_hca_mqis_reg_print(const struct reg_access_hca_mqis_reg *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mqis_reg ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "info_type            : " UH_FMT "\n", ptr_struct->info_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "info_length          : " UH_FMT "\n", ptr_struct->info_length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "read_length          : " UH_FMT "\n", ptr_struct->read_length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "read_offset          : " UH_FMT "\n", ptr_struct->read_offset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "unlimited array: (info_string)\n");

}

int reg_access_hca_mqis_reg_size(void)
{
	 return 20;
}

void reg_access_hca_mqis_reg_dump(const struct reg_access_hca_mqis_reg *ptr_struct, FILE* file)
{
	reg_access_hca_mqis_reg_print(ptr_struct, file, 0);
}

void reg_access_hca_fpga_cap_pack(const struct reg_access_hca_fpga_cap *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->fpga_device);

	offset = 0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fpga_id);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->register_file_ver);

	offset = 78;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->access_reg_modify_mode);

	offset = 70;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->access_reg_query_mode);

	offset = 64;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->fpga_ctrl_modify);

	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_version);

	offset = 160;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_date);

	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->image_time);

	offset = 224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->shell_version);

	offset = 384;
	reg_access_hca_fpga_shell_caps_pack(&(ptr_struct->shell_caps), ptr_buff + offset/8);

	offset = 904;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->ieee_vendor_id);

	offset = 944;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_product_id);

	offset = 928;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_product_version);

	offset = 960;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->sandbox_basic_caps);

	offset = 1008;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->sandbox_extended_caps_len);

	offset = 1024;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->sandbox_extended_caps_addr);

	offset = 1088;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->fpga_ddr_start_addr);

	offset = 1152;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->fpga_cr_space_start_addr);

	offset = 1216;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fpga_ddr_size);

	offset = 1248;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->fpga_cr_space_size);

}

void reg_access_hca_fpga_cap_unpack(struct reg_access_hca_fpga_cap *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 8;
	ptr_struct->fpga_device = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset = 0;
	ptr_struct->fpga_id = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 32;
	ptr_struct->register_file_ver = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 78;
	ptr_struct->access_reg_modify_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset = 70;
	ptr_struct->access_reg_query_mode = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset = 64;
	ptr_struct->fpga_ctrl_modify = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 128;
	ptr_struct->image_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 160;
	ptr_struct->image_date = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 192;
	ptr_struct->image_time = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 224;
	ptr_struct->shell_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 384;
	reg_access_hca_fpga_shell_caps_unpack(&(ptr_struct->shell_caps), ptr_buff + offset/8);

	offset = 904;
	ptr_struct->ieee_vendor_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset = 944;
	ptr_struct->sandbox_product_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 928;
	ptr_struct->sandbox_product_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 960;
	ptr_struct->sandbox_basic_caps = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 1008;
	ptr_struct->sandbox_extended_caps_len = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 1024;
	ptr_struct->sandbox_extended_caps_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

	offset = 1088;
	ptr_struct->fpga_ddr_start_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

	offset = 1152;
	ptr_struct->fpga_cr_space_start_addr = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

	offset = 1216;
	ptr_struct->fpga_ddr_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 1248;
	ptr_struct->fpga_cr_space_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void reg_access_hca_fpga_cap_print(const struct reg_access_hca_fpga_cap *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_fpga_cap ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_device          : %s (" UH_FMT ")\n", (ptr_struct->fpga_device == 0 ? ("KU040") : ((ptr_struct->fpga_device == 1 ? ("KU060") : ("unknown")))), ptr_struct->fpga_device);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_id              : %s (" UH_FMT ")\n", (ptr_struct->fpga_id == 0 ? ("unknown") : ((ptr_struct->fpga_id == 1 ? ("Newton_X") : ("unknown")))), ptr_struct->fpga_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "register_file_ver    : " U32H_FMT "\n", ptr_struct->register_file_ver);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "access_reg_modify_mode : %s (" UH_FMT ")\n", (ptr_struct->access_reg_modify_mode == 0 ? ("Not_allowed") : ((ptr_struct->access_reg_modify_mode == 1 ? ("All_range_allowed") : ("unknown")))), ptr_struct->access_reg_modify_mode);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "access_reg_query_mode : %s (" UH_FMT ")\n", (ptr_struct->access_reg_query_mode == 0 ? ("Not_allowed") : ((ptr_struct->access_reg_query_mode == 1 ? ("All_range_allowed") : ("unknown")))), ptr_struct->access_reg_query_mode);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_ctrl_modify     : " UH_FMT "\n", ptr_struct->fpga_ctrl_modify);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_version        : " U32H_FMT "\n", ptr_struct->image_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_date           : " U32H_FMT "\n", ptr_struct->image_date);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_time           : " U32H_FMT "\n", ptr_struct->image_time);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "shell_version        : " U32H_FMT "\n", ptr_struct->shell_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "shell_caps:\n");
	reg_access_hca_fpga_shell_caps_print(&(ptr_struct->shell_caps), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ieee_vendor_id       : " UH_FMT "\n", ptr_struct->ieee_vendor_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sandbox_product_id   : %s (" UH_FMT ")\n", (ptr_struct->sandbox_product_id == 1 ? ("example") : ((ptr_struct->sandbox_product_id == 2 ? ("IPsec") : ((ptr_struct->sandbox_product_id == 3 ? ("TLS") : ("unknown")))))), ptr_struct->sandbox_product_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sandbox_product_version : " UH_FMT "\n", ptr_struct->sandbox_product_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sandbox_basic_caps   : " U32H_FMT "\n", ptr_struct->sandbox_basic_caps);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sandbox_extended_caps_len : " UH_FMT "\n", ptr_struct->sandbox_extended_caps_len);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sandbox_extended_caps_addr : " U64H_FMT "\n", ptr_struct->sandbox_extended_caps_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_ddr_start_addr  : " U64H_FMT "\n", ptr_struct->fpga_ddr_start_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_cr_space_start_addr : " U64H_FMT "\n", ptr_struct->fpga_cr_space_start_addr);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_ddr_size        : " U32H_FMT "\n", ptr_struct->fpga_ddr_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_cr_space_size   : " U32H_FMT "\n", ptr_struct->fpga_cr_space_size);

}

int reg_access_hca_fpga_cap_size(void)
{
	 return 256;
}

void reg_access_hca_fpga_cap_dump(const struct reg_access_hca_fpga_cap *ptr_struct, FILE* file)
{
	reg_access_hca_fpga_cap_print(ptr_struct, file, 0);
}

void reg_access_hca_mcqi_version_pack(const struct reg_access_hca_mcqi_version *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->version_string_length);

	offset = 3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->user_defined_time_valid);

	offset = 2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->build_time_valid);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->build_time);

	offset = 128;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->user_defined_time);

	offset = 192;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->build_tool_version);


}

void reg_access_hca_mcqi_version_unpack(struct reg_access_hca_mcqi_version *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->version_string_length = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 3;
	ptr_struct->user_defined_time_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 2;
	ptr_struct->build_time_valid = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 32;
	ptr_struct->version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 64;
	ptr_struct->build_time = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

	offset = 128;
	ptr_struct->user_defined_time = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

	offset = 192;
	ptr_struct->build_tool_version = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);


}

void reg_access_hca_mcqi_version_print(const struct reg_access_hca_mcqi_version *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_mcqi_version ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version_string_length : " UH_FMT "\n", ptr_struct->version_string_length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "user_defined_time_valid : " UH_FMT "\n", ptr_struct->user_defined_time_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "build_time_valid     : " UH_FMT "\n", ptr_struct->build_time_valid);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : " U32H_FMT "\n", ptr_struct->version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "build_time           : " U64H_FMT "\n", ptr_struct->build_time);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "user_defined_time    : " U64H_FMT "\n", ptr_struct->user_defined_time);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "build_tool_version   : " U32H_FMT "\n", ptr_struct->build_tool_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "unlimited array: (version_string)\n");

}

int reg_access_hca_mcqi_version_size(void)
{
	 return 36;
}

void reg_access_hca_mcqi_version_dump(const struct reg_access_hca_mcqi_version *ptr_struct, FILE* file)
{
	reg_access_hca_mcqi_version_print(ptr_struct, file, 0);
}

void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t* ptr_buff)
{
	reg_access_hca_mcc_reg_pack(&(ptr_struct->mcc_reg), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t* ptr_buff)
{
	reg_access_hca_mcc_reg_unpack(&(ptr_struct->mcc_reg), ptr_buff);
}

void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== reg_access_hca_reg_access_hca_Nodes ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcda_reg:\n");
	reg_access_hca_mcda_reg_print(&(ptr_struct->mcda_reg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcqs_reg:\n");
	reg_access_hca_mcqs_reg_print(&(ptr_struct->mcqs_reg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_ctrl:\n");
	reg_access_hca_fpga_ctrl_print(&(ptr_struct->fpga_ctrl), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcqi_version:\n");
	reg_access_hca_mcqi_version_print(&(ptr_struct->mcqi_version), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mgir:\n");
	reg_access_hca_mgir_print(&(ptr_struct->mgir), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcqi_activation_method:\n");
	reg_access_hca_mcqi_activation_method_print(&(ptr_struct->mcqi_activation_method), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fpga_cap:\n");
	reg_access_hca_fpga_cap_print(&(ptr_struct->fpga_cap), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mqis_reg:\n");
	reg_access_hca_mqis_reg_print(&(ptr_struct->mqis_reg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcqi_cap:\n");
	reg_access_hca_mcqi_cap_print(&(ptr_struct->mcqi_cap), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcqi_reg:\n");
	reg_access_hca_mcqi_reg_print(&(ptr_struct->mcqi_reg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mcc_reg:\n");
	reg_access_hca_mcc_reg_print(&(ptr_struct->mcc_reg), file, indent_level + 1);

}

int reg_access_hca_reg_access_hca_Nodes_size(void)
{
	 return 256;
}

void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE* file)
{
	reg_access_hca_reg_access_hca_Nodes_print(ptr_struct, file, 0);
}

