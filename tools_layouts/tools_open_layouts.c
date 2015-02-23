
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2010-2011, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
 

/***
 *** This file was generated at "2015-01-22 18:19:26"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/tools_open/tools_open.adb --file-prefix tools_open --prefix tools_open_
 ***/
#include "tools_open_layouts.h"

void tools_open_pmdio_addr_data_pack(const struct tools_open_pmdio_addr_data *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->data);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->addr);

}

void tools_open_pmdio_addr_data_unpack(struct tools_open_pmdio_addr_data *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->data = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=0;
	ptr_struct->addr = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void tools_open_pmdio_addr_data_print(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== pmdio_addr_data ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data                 : "UH_FMT"\n", ptr_struct->data);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "addr                 : "UH_FMT"\n", ptr_struct->addr);

}

int tools_open_pmdio_addr_data_size(){
	 return 4;
}

void tools_open_pmdio_addr_data_dump(const struct tools_open_pmdio_addr_data *ptr_struct, FILE* file) {
	tools_open_pmdio_addr_data_print(ptr_struct, file, 0);
}

void tools_open_mnv_hdr_pack(const struct tools_open_mnv_hdr *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->type);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->length);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->type_mod);

	offset=39;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->shadow);

	offset=37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->pad_cnt);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->version);

}

void tools_open_mnv_hdr_unpack(struct tools_open_mnv_hdr *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->type = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=2;
	ptr_struct->length = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=40;
	ptr_struct->type_mod = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=39;
	ptr_struct->shadow = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=37;
	ptr_struct->pad_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=32;
	ptr_struct->version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

}

void tools_open_mnv_hdr_print(const struct tools_open_mnv_hdr *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mnv_hdr ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type                 : "UH_FMT"\n", ptr_struct->type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "length               : "UH_FMT"\n", ptr_struct->length);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "type_mod             : "UH_FMT"\n", ptr_struct->type_mod);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "shadow               : "UH_FMT"\n", ptr_struct->shadow);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pad_cnt              : "UH_FMT"\n", ptr_struct->pad_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "version              : "UH_FMT"\n", ptr_struct->version);

}

int tools_open_mnv_hdr_size(){
	 return 8;
}

void tools_open_mnv_hdr_dump(const struct tools_open_mnv_hdr *ptr_struct, FILE* file) {
	tools_open_mnv_hdr_print(ptr_struct, file, 0);
}

void tools_open_pmdio_pack(const struct tools_open_pmdio *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=29;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->operation);

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->lock);

	offset=59;
	adb2c_push_bits_to_buff(ptr_buff, offset, 5, (u_int32_t)ptr_struct->reg_adr_mmd);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->last_op_idx);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_ops_done);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(64, 32, i, 2112, 1);
	tools_open_pmdio_addr_data_pack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset/8);
	}

}

void tools_open_pmdio_unpack(struct tools_open_pmdio *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=29;
	ptr_struct->operation = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=22;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=0;
	ptr_struct->lock = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=59;
	ptr_struct->reg_adr_mmd = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 5);

	offset=48;
	ptr_struct->last_op_idx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=40;
	ptr_struct->num_ops_done = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(64, 32, i, 2112, 1);
	tools_open_pmdio_addr_data_unpack(&(ptr_struct->mdio_trans[i]), ptr_buff + offset/8);
	}

}

void tools_open_pmdio_print(const struct tools_open_pmdio *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== pmdio ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "operation            : "UH_FMT"\n", ptr_struct->operation);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clause               : "UH_FMT"\n", ptr_struct->clause);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "local_port           : "UH_FMT"\n", ptr_struct->local_port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lock                 : "UH_FMT"\n", ptr_struct->lock);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "reg_adr_mmd          : "UH_FMT"\n", ptr_struct->reg_adr_mmd);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "last_op_idx          : "UH_FMT"\n", ptr_struct->last_op_idx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_ops_done         : "UH_FMT"\n", ptr_struct->num_ops_done);

	for (i=0; i < 64; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mdio_trans[%3d]:\n", i);
	tools_open_pmdio_addr_data_print(&(ptr_struct->mdio_trans[i]), file, indent_level + 1);
	}

}

int tools_open_pmdio_size(){
	 return 264;
}

void tools_open_pmdio_dump(const struct tools_open_pmdio *ptr_struct, FILE* file) {
	tools_open_pmdio_print(ptr_struct, file, 0);
}

void tools_open_pmdic_pack(const struct tools_open_pmdic *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->local_port);

	offset=56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->operation_cap);

	offset=38;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->clause);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->mdio_preset);

	offset=88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->misc_cap);

}

void tools_open_pmdic_unpack(struct tools_open_pmdic *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=8;
	ptr_struct->local_port = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=56;
	ptr_struct->operation_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=38;
	ptr_struct->clause = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=32;
	ptr_struct->mdio_preset = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=88;
	ptr_struct->misc_cap = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_pmdic_print(const struct tools_open_pmdic *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== pmdic ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "local_port           : "UH_FMT"\n", ptr_struct->local_port);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "operation_cap        : "UH_FMT"\n", ptr_struct->operation_cap);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "clause               : "UH_FMT"\n", ptr_struct->clause);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mdio_preset          : "UH_FMT"\n", ptr_struct->mdio_preset);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "misc_cap             : "UH_FMT"\n", ptr_struct->misc_cap);

}

int tools_open_pmdic_size(){
	 return 12;
}

void tools_open_pmdic_dump(const struct tools_open_pmdic *ptr_struct, FILE* file) {
	tools_open_pmdic_print(ptr_struct, file, 0);
}

void tools_open_mnvia_pack(const struct tools_open_mnvia *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvia_unpack(struct tools_open_mnvia *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvia_print(const struct tools_open_mnvia *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mnvia ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnv_hdr:\n");
	tools_open_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

}

int tools_open_mnvia_size(){
	 return 8;
}

void tools_open_mnvia_dump(const struct tools_open_mnvia *ptr_struct, FILE* file) {
	tools_open_mnvia_print(ptr_struct, file, 0);
}

void tools_open_mnvi_pack(const struct tools_open_mnvi *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvi_unpack(struct tools_open_mnvi *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

}

void tools_open_mnvi_print(const struct tools_open_mnvi *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mnvi ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnv_hdr:\n");
	tools_open_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

}

int tools_open_mnvi_size(){
	 return 8;
}

void tools_open_mnvi_dump(const struct tools_open_mnvi *ptr_struct, FILE* file) {
	tools_open_mnvi_print(ptr_struct, file, 0);
}

void tools_open_mnva_pack(const struct tools_open_mnva *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_pack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->data[i]);
	}

}

void tools_open_mnva_unpack(struct tools_open_mnva *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	tools_open_mnv_hdr_unpack(&(ptr_struct->mnv_hdr), ptr_buff + offset/8);

	for (i=0; i < 128; i++) {
	offset=adb2c_calc_array_field_address(88, 8, i, 2048, 1);
	ptr_struct->data[i] = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

}

void tools_open_mnva_print(const struct tools_open_mnva *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mnva ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnv_hdr:\n");
	tools_open_mnv_hdr_print(&(ptr_struct->mnv_hdr), file, indent_level + 1);

	for (i=0; i < 128; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data[%3d]            : "UH_FMT"\n", i, ptr_struct->data[i]);
	}

}

int tools_open_mnva_size(){
	 return 256;
}

void tools_open_mnva_dump(const struct tools_open_mnva *ptr_struct, FILE* file) {
	tools_open_mnva_print(ptr_struct, file, 0);
}

void tools_open_query_def_params_per_port_pack(const struct tools_open_query_def_params_per_port *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);

	offset=44;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->boot_protocol);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->boot_retry_cnt);

	offset=37;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->network_link_type);

	offset=36;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_magic);

	offset=35;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);

	offset=34;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);

	offset=33;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pprx);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pptx);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->boot_pkey);

	offset=104;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->iscsi_boot_to_target);

	offset=101;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_vlan_en);

	offset=100;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_tcp_timestamps_en);

	offset=99;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_mutual_auth_en);

	offset=98;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_chap_auth_en);

	offset=97;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_dhcp_params_en);

	offset=96;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->iscsi_ipv4_dhcp_en);

	offset=152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_lun_busy_retry_cnt);

	offset=144;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->iscsi_link_up_delay_time);

}

void tools_open_query_def_params_per_port_unpack(struct tools_open_query_def_params_per_port *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=52;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=44;
	ptr_struct->boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=40;
	ptr_struct->boot_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=37;
	ptr_struct->network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=36;
	ptr_struct->en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=35;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=34;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=33;
	ptr_struct->pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=32;
	ptr_struct->pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=80;
	ptr_struct->boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=104;
	ptr_struct->iscsi_boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=101;
	ptr_struct->iscsi_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=100;
	ptr_struct->iscsi_tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=99;
	ptr_struct->iscsi_chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=98;
	ptr_struct->iscsi_chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=97;
	ptr_struct->iscsi_dhcp_params_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=96;
	ptr_struct->iscsi_ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=152;
	ptr_struct->iscsi_lun_busy_retry_cnt = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=144;
	ptr_struct->iscsi_link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_query_def_params_per_port_print(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== query_def_params_per_port ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_default_config_payload_version : "UH_FMT"\n", ptr_struct->fw_default_config_payload_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan            : "UH_FMT"\n", ptr_struct->boot_vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_protocol        : "UH_FMT"\n", ptr_struct->boot_protocol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_retry_cnt       : "UH_FMT"\n", ptr_struct->boot_retry_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "network_link_type    : "UH_FMT"\n", ptr_struct->network_link_type);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_magic         : "UH_FMT"\n", ptr_struct->en_wol_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan_en         : "UH_FMT"\n", ptr_struct->boot_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_option_rom_en   : "UH_FMT"\n", ptr_struct->boot_option_rom_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pprx                 : "UH_FMT"\n", ptr_struct->pprx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pptx                 : "UH_FMT"\n", ptr_struct->pptx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_pkey            : "UH_FMT"\n", ptr_struct->boot_pkey);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_boot_to_target : "UH_FMT"\n", ptr_struct->iscsi_boot_to_target);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_vlan_en        : "UH_FMT"\n", ptr_struct->iscsi_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_tcp_timestamps_en : "UH_FMT"\n", ptr_struct->iscsi_tcp_timestamps_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_chap_mutual_auth_en : "UH_FMT"\n", ptr_struct->iscsi_chap_mutual_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_chap_auth_en   : "UH_FMT"\n", ptr_struct->iscsi_chap_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_dhcp_params_en : "UH_FMT"\n", ptr_struct->iscsi_dhcp_params_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_ipv4_dhcp_en   : "UH_FMT"\n", ptr_struct->iscsi_ipv4_dhcp_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_lun_busy_retry_cnt : "UH_FMT"\n", ptr_struct->iscsi_lun_busy_retry_cnt);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_link_up_delay_time : "UH_FMT"\n", ptr_struct->iscsi_link_up_delay_time);

}

int tools_open_query_def_params_per_port_size(){
	 return 28;
}

void tools_open_query_def_params_per_port_dump(const struct tools_open_query_def_params_per_port *ptr_struct, FILE* file) {
	tools_open_query_def_params_per_port_print(ptr_struct, file, 0);
}

void tools_open_query_def_params_global_pack(const struct tools_open_query_def_params_global *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->fw_default_config_payload_version);

	offset=56;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_vfs);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->uar_bar_size);

	offset=48;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->max_uar_bar_size);

	offset=32;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);

}

void tools_open_query_def_params_global_unpack(struct tools_open_query_def_params_global *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->fw_default_config_payload_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=56;
	ptr_struct->num_vfs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=52;
	ptr_struct->uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=48;
	ptr_struct->max_uar_bar_size = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_query_def_params_global_print(const struct tools_open_query_def_params_global *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== query_def_params_global ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fw_default_config_payload_version : "UH_FMT"\n", ptr_struct->fw_default_config_payload_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_vfs              : "UH_FMT"\n", ptr_struct->num_vfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uar_bar_size         : "UH_FMT"\n", ptr_struct->uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "max_uar_bar_size     : "UH_FMT"\n", ptr_struct->max_uar_bar_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

}

int tools_open_query_def_params_global_size(){
	 return 20;
}

void tools_open_query_def_params_global_dump(const struct tools_open_query_def_params_global *ptr_struct, FILE* file) {
	tools_open_query_def_params_global_print(ptr_struct, file, 0);
}

void tools_open_phy_reg_pack(const union tools_open_phy_reg *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 264);
}

void tools_open_phy_reg_unpack(union tools_open_phy_reg *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 264);
}

void tools_open_phy_reg_print(const union tools_open_phy_reg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== phy_reg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pmdic:\n");
	tools_open_pmdic_print(&(ptr_struct->pmdic), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pmdio:\n");
	tools_open_pmdio_print(&(ptr_struct->pmdio), file, indent_level + 1);

}

int tools_open_phy_reg_size(){
	 return 264;
}

void tools_open_phy_reg_dump(const union tools_open_phy_reg *ptr_struct, FILE* file) {
	tools_open_phy_reg_print(ptr_struct, file, 0);
}

void tools_open_mnv_cfg_pack(const union tools_open_mnv_cfg *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 256);
}

void tools_open_mnv_cfg_unpack(union tools_open_mnv_cfg *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 256);
}

void tools_open_mnv_cfg_print(const union tools_open_mnv_cfg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mnv_cfg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnva:\n");
	tools_open_mnva_print(&(ptr_struct->mnva), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnvi:\n");
	tools_open_mnvi_print(&(ptr_struct->mnvi), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mnvia:\n");
	tools_open_mnvia_print(&(ptr_struct->mnvia), file, indent_level + 1);

}

int tools_open_mnv_cfg_size(){
	 return 256;
}

void tools_open_mnv_cfg_dump(const union tools_open_mnv_cfg *ptr_struct, FILE* file) {
	tools_open_mnv_cfg_print(ptr_struct, file, 0);
}

void tools_open_vpi_settings_pack(const struct tools_open_vpi_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=30;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->network_link_type);

}

void tools_open_vpi_settings_unpack(struct tools_open_vpi_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=30;
	ptr_struct->network_link_type = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

}

void tools_open_vpi_settings_print(const struct tools_open_vpi_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== vpi_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "network_link_type    : "UH_FMT"\n", ptr_struct->network_link_type);

}

int tools_open_vpi_settings_size(){
	 return 4;
}

void tools_open_vpi_settings_dump(const struct tools_open_vpi_settings *ptr_struct, FILE* file) {
	tools_open_vpi_settings_print(ptr_struct, file, 0);
}

void tools_open_bar_size_pack(const struct tools_open_bar_size *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->log_uar_bar_size);

}

void tools_open_bar_size_unpack(struct tools_open_bar_size *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->log_uar_bar_size = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_bar_size_print(const struct tools_open_bar_size *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== bar_size ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "log_uar_bar_size     : "U32H_FMT"\n", ptr_struct->log_uar_bar_size);

}

int tools_open_bar_size_size(){
	 return 4;
}

void tools_open_bar_size_dump(const struct tools_open_bar_size *ptr_struct, FILE* file) {
	tools_open_bar_size_print(ptr_struct, file, 0);
}

void tools_open_sriov_pack(const struct tools_open_sriov *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->total_vfs);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->sriov_en);

}

void tools_open_sriov_unpack(struct tools_open_sriov *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->total_vfs = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset=0;
	ptr_struct->sriov_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_sriov_print(const struct tools_open_sriov *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== sriov ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "total_vfs            : "UH_FMT"\n", ptr_struct->total_vfs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov_en             : "UH_FMT"\n", ptr_struct->sriov_en);

}

int tools_open_sriov_size(){
	 return 4;
}

void tools_open_sriov_dump(const struct tools_open_sriov *ptr_struct, FILE* file) {
	tools_open_sriov_print(ptr_struct, file, 0);
}

void tools_open_preboot_flow_ctrl_pack(const struct tools_open_preboot_flow_ctrl *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfcrx);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->pfctx);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pfc_willing);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pprx);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->pptx);

}

void tools_open_preboot_flow_ctrl_unpack(struct tools_open_preboot_flow_ctrl *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=24;
	ptr_struct->pfcrx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=16;
	ptr_struct->pfctx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=2;
	ptr_struct->pfc_willing = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->pprx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->pptx = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_preboot_flow_ctrl_print(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== preboot_flow_ctrl ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfcrx                : "UH_FMT"\n", ptr_struct->pfcrx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfctx                : "UH_FMT"\n", ptr_struct->pfctx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pfc_willing          : "UH_FMT"\n", ptr_struct->pfc_willing);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pprx                 : "UH_FMT"\n", ptr_struct->pprx);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "pptx                 : "UH_FMT"\n", ptr_struct->pptx);

}

int tools_open_preboot_flow_ctrl_size(){
	 return 4;
}

void tools_open_preboot_flow_ctrl_dump(const struct tools_open_preboot_flow_ctrl *ptr_struct, FILE* file) {
	tools_open_preboot_flow_ctrl_print(ptr_struct, file, 0);
}

void tools_open_boot_settings_pack(const struct tools_open_boot_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->boot_vlan);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->legacy_boot_protocol);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 3, (u_int32_t)ptr_struct->boot_retry_conut);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_vlan_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->boot_option_rom_en);

}

void tools_open_boot_settings_unpack(struct tools_open_boot_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=20;
	ptr_struct->boot_vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=8;
	ptr_struct->legacy_boot_protocol = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=5;
	ptr_struct->boot_retry_conut = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 3);

	offset=1;
	ptr_struct->boot_vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->boot_option_rom_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_boot_settings_print(const struct tools_open_boot_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== boot_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan            : "UH_FMT"\n", ptr_struct->boot_vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "legacy_boot_protocol : "UH_FMT"\n", ptr_struct->legacy_boot_protocol);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_retry_conut     : "UH_FMT"\n", ptr_struct->boot_retry_conut);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_vlan_en         : "UH_FMT"\n", ptr_struct->boot_vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_option_rom_en   : "UH_FMT"\n", ptr_struct->boot_option_rom_en);

}

int tools_open_boot_settings_size(){
	 return 4;
}

void tools_open_boot_settings_dump(const struct tools_open_boot_settings *ptr_struct, FILE* file) {
	tools_open_boot_settings_print(ptr_struct, file, 0);
}

void tools_open_infiniband_boot_settings_pack(const struct tools_open_infiniband_boot_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->boot_pkey);

}

void tools_open_infiniband_boot_settings_unpack(struct tools_open_infiniband_boot_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=16;
	ptr_struct->boot_pkey = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

}

void tools_open_infiniband_boot_settings_print(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== infiniband_boot_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_pkey            : "UH_FMT"\n", ptr_struct->boot_pkey);

}

int tools_open_infiniband_boot_settings_size(){
	 return 4;
}

void tools_open_infiniband_boot_settings_dump(const struct tools_open_infiniband_boot_settings *ptr_struct, FILE* file) {
	tools_open_infiniband_boot_settings_print(ptr_struct, file, 0);
}

void tools_open_iscsi_settings_pack(const struct tools_open_iscsi_settings *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=10;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->target_as_first_hdd_en);

	offset=8;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->boot_to_target);

	offset=7;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv6_auto_config_en);

	offset=5;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->vlan_en);

	offset=4;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->tcp_timestamps_en);

	offset=3;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_mutual_auth_en);

	offset=2;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->chap_auth_en);

	offset=1;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->dhcp_iscsi_en);

	offset=0;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->ipv4_dhcp_en);

	offset=52;
	adb2c_push_bits_to_buff(ptr_buff, offset, 12, (u_int32_t)ptr_struct->vlan);

	offset=88;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lun_busy_retry_count);

	offset=80;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->link_up_delay_time);

}

void tools_open_iscsi_settings_unpack(struct tools_open_iscsi_settings *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=10;
	ptr_struct->target_as_first_hdd_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=8;
	ptr_struct->boot_to_target = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=7;
	ptr_struct->ipv6_auto_config_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=5;
	ptr_struct->vlan_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=4;
	ptr_struct->tcp_timestamps_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=3;
	ptr_struct->chap_mutual_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=2;
	ptr_struct->chap_auth_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=1;
	ptr_struct->dhcp_iscsi_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=0;
	ptr_struct->ipv4_dhcp_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=52;
	ptr_struct->vlan = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 12);

	offset=88;
	ptr_struct->lun_busy_retry_count = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=80;
	ptr_struct->link_up_delay_time = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

}

void tools_open_iscsi_settings_print(const struct tools_open_iscsi_settings *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== iscsi_settings ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "target_as_first_hdd_en : "UH_FMT"\n", ptr_struct->target_as_first_hdd_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_to_target       : "UH_FMT"\n", ptr_struct->boot_to_target);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ipv6_auto_config_en  : "UH_FMT"\n", ptr_struct->ipv6_auto_config_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vlan_en              : "UH_FMT"\n", ptr_struct->vlan_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "tcp_timestamps_en    : "UH_FMT"\n", ptr_struct->tcp_timestamps_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "chap_mutual_auth_en  : "UH_FMT"\n", ptr_struct->chap_mutual_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "chap_auth_en         : "UH_FMT"\n", ptr_struct->chap_auth_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "dhcp_iscsi_en        : "UH_FMT"\n", ptr_struct->dhcp_iscsi_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "ipv4_dhcp_en         : "UH_FMT"\n", ptr_struct->ipv4_dhcp_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vlan                 : "UH_FMT"\n", ptr_struct->vlan);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lun_busy_retry_count : "UH_FMT"\n", ptr_struct->lun_busy_retry_count);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "link_up_delay_time   : "UH_FMT"\n", ptr_struct->link_up_delay_time);

}

int tools_open_iscsi_settings_size(){
	 return 12;
}

void tools_open_iscsi_settings_dump(const struct tools_open_iscsi_settings *ptr_struct, FILE* file) {
	tools_open_iscsi_settings_print(ptr_struct, file, 0);
}

void tools_open_wol_pack(const struct tools_open_wol *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_psswd_magic);

	offset=21;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_magic);

	offset=20;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_arp);

	offset=19;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_bc);

	offset=18;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_mc);

	offset=17;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_uc);

	offset=16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->en_wol_phy);

}

void tools_open_wol_unpack(struct tools_open_wol *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=22;
	ptr_struct->en_wol_psswd_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=21;
	ptr_struct->en_wol_magic = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=20;
	ptr_struct->en_wol_arp = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=19;
	ptr_struct->en_wol_bc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=18;
	ptr_struct->en_wol_mc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=17;
	ptr_struct->en_wol_uc = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=16;
	ptr_struct->en_wol_phy = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

}

void tools_open_wol_print(const struct tools_open_wol *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== wol ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_psswd_magic   : "UH_FMT"\n", ptr_struct->en_wol_psswd_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_magic         : "UH_FMT"\n", ptr_struct->en_wol_magic);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_arp           : "UH_FMT"\n", ptr_struct->en_wol_arp);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_bc            : "UH_FMT"\n", ptr_struct->en_wol_bc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_mc            : "UH_FMT"\n", ptr_struct->en_wol_mc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_uc            : "UH_FMT"\n", ptr_struct->en_wol_uc);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "en_wol_phy           : "UH_FMT"\n", ptr_struct->en_wol_phy);

}

int tools_open_wol_size(){
	 return 8;
}

void tools_open_wol_dump(const struct tools_open_wol *ptr_struct, FILE* file) {
	tools_open_wol_print(ptr_struct, file, 0);
}

void tools_open_hcr_cmds_pack(const union tools_open_hcr_cmds *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 264);
}

void tools_open_hcr_cmds_unpack(union tools_open_hcr_cmds *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 264);
}

void tools_open_hcr_cmds_print(const union tools_open_hcr_cmds *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== hcr_cmds ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "query_def_params_global:\n");
	tools_open_query_def_params_global_print(&(ptr_struct->query_def_params_global), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "query_def_params_per_port:\n");
	tools_open_query_def_params_per_port_print(&(ptr_struct->query_def_params_per_port), file, indent_level + 1);

}

int tools_open_hcr_cmds_size(){
	 return 264;
}

void tools_open_hcr_cmds_dump(const union tools_open_hcr_cmds *ptr_struct, FILE* file) {
	tools_open_hcr_cmds_print(ptr_struct, file, 0);
}

void tools_open_access_registers_pack(const union tools_open_access_registers *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 512);
}

void tools_open_access_registers_unpack(union tools_open_access_registers *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 512);
}

void tools_open_access_registers_print(const union tools_open_access_registers *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== access_registers ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "MNVReg:\n");
	tools_open_mnv_cfg_print(&(ptr_struct->MNVReg), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "PhyReg:\n");
	tools_open_phy_reg_print(&(ptr_struct->PhyReg), file, indent_level + 1);

}

int tools_open_access_registers_size(){
	 return 512;
}

void tools_open_access_registers_dump(const union tools_open_access_registers *ptr_struct, FILE* file) {
	tools_open_access_registers_print(ptr_struct, file, 0);
}

void tools_open_nv_cfg_pack(const union tools_open_nv_cfg *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 256);
}

void tools_open_nv_cfg_unpack(union tools_open_nv_cfg *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 256);
}

void tools_open_nv_cfg_print(const union tools_open_nv_cfg *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== nv_cfg ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "wol:\n");
	tools_open_wol_print(&(ptr_struct->wol), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "iscsi_settings:\n");
	tools_open_iscsi_settings_print(&(ptr_struct->iscsi_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "infiniband_boot_settings:\n");
	tools_open_infiniband_boot_settings_print(&(ptr_struct->infiniband_boot_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_settings:\n");
	tools_open_boot_settings_print(&(ptr_struct->boot_settings), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "preboot_flow_ctrl:\n");
	tools_open_preboot_flow_ctrl_print(&(ptr_struct->preboot_flow_ctrl), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sriov:\n");
	tools_open_sriov_print(&(ptr_struct->sriov), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "bar_size:\n");
	tools_open_bar_size_print(&(ptr_struct->bar_size), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vpi_settings:\n");
	tools_open_vpi_settings_print(&(ptr_struct->vpi_settings), file, indent_level + 1);

}

int tools_open_nv_cfg_size(){
	 return 256;
}

void tools_open_nv_cfg_dump(const union tools_open_nv_cfg *ptr_struct, FILE* file) {
	tools_open_nv_cfg_print(ptr_struct, file, 0);
}

void tools_open_tools_open_pack(const union tools_open_tools_open *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 1048576);
}

void tools_open_tools_open_unpack(union tools_open_tools_open *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 1048576);
}

void tools_open_tools_open_print(const union tools_open_tools_open *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== tools_open ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "NVConfig:\n");
	tools_open_nv_cfg_print(&(ptr_struct->NVConfig), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "AceessRegisters:\n");
	tools_open_access_registers_print(&(ptr_struct->AceessRegisters), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "HcrCmds:\n");
	tools_open_hcr_cmds_print(&(ptr_struct->HcrCmds), file, indent_level + 1);

}

int tools_open_tools_open_size(){
	 return 1048576;
}

void tools_open_tools_open_dump(const union tools_open_tools_open *ptr_struct, FILE* file) {
	tools_open_tools_open_print(ptr_struct, file, 0);
}

void tools_open_uint64_pack(const struct tools_open_uint64 *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->hi);

	offset=32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->lo);

}

void tools_open_uint64_unpack(struct tools_open_uint64 *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=0;
	ptr_struct->hi = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset=32;
	ptr_struct->lo = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void tools_open_uint64_print(const struct tools_open_uint64 *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== uint64 ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "hi                   : "U32H_FMT"\n", ptr_struct->hi);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "lo                   : "U32H_FMT"\n", ptr_struct->lo);

}

int tools_open_uint64_size(){
	 return 8;
}

void tools_open_uint64_dump(const struct tools_open_uint64 *ptr_struct, FILE* file) {
	tools_open_uint64_print(ptr_struct, file, 0);
}

