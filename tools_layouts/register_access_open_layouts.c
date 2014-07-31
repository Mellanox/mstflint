
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
 *** This file was generated at "2014-07-08 14:00:34"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/register_access_open/register_access_open.adb --file-prefix register_access_open --prefix register_access_
 ***/
#include "register_access_open_layouts.h"

void register_access_mfba_pack(const struct register_access_mfba *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);

	offset=23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);

	offset=55;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->size);

	offset=72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->address);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(96, 32, i, 2144, 0);
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->data[i]);
	}

}

void register_access_mfba_unpack(struct register_access_mfba *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=55;
	ptr_struct->size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);

	offset=72;
	ptr_struct->address = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	for (i=0; i < 64; i++) {
	offset=adb2c_calc_array_field_address(96, 32, i, 2144, 0);
	ptr_struct->data[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}

}

void register_access_mfba_print(const struct register_access_mfba *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mfba ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fs                   : "UH_FMT"\n", ptr_struct->fs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "p                    : "UH_FMT"\n", ptr_struct->p);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "size                 : "UH_FMT"\n", ptr_struct->size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "address              : "UH_FMT"\n", ptr_struct->address);

	for (i=0; i < 64; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "data[%3d]            : "U32H_FMT"\n", i, ptr_struct->data[i]);
	}

}

int register_access_mfba_size(){
	 return 268;
}

void register_access_mfba_dump(const struct register_access_mfba *ptr_struct, FILE* file) {
	register_access_mfba_print(ptr_struct, file, 0);
}

void register_access_mfpa_pack(const struct register_access_mfpa *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);

	offset=23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);

	offset=40;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->boot_address);

	offset=156;
	adb2c_push_bits_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->flash_num);

	offset=168;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->jedec_id);

	offset=214;
	adb2c_push_bits_to_buff(ptr_buff, offset, 10, (u_int32_t)ptr_struct->sector_size);

	offset=200;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->block_allignment);

	offset=224;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int64_t)ptr_struct->capability_mask);

}

void register_access_mfpa_unpack(struct register_access_mfpa *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=40;
	ptr_struct->boot_address = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset=156;
	ptr_struct->flash_num = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 4);

	offset=168;
	ptr_struct->jedec_id = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

	offset=214;
	ptr_struct->sector_size = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 10);

	offset=200;
	ptr_struct->block_allignment = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset=224;
	ptr_struct->capability_mask = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

}

void register_access_mfpa_print(const struct register_access_mfpa *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mfpa ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fs                   : "UH_FMT"\n", ptr_struct->fs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "p                    : "UH_FMT"\n", ptr_struct->p);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "boot_address         : "UH_FMT"\n", ptr_struct->boot_address);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "flash_num            : "UH_FMT"\n", ptr_struct->flash_num);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "jedec_id             : "UH_FMT"\n", ptr_struct->jedec_id);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "sector_size          : "UH_FMT"\n", ptr_struct->sector_size);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "block_allignment     : "UH_FMT"\n", ptr_struct->block_allignment);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "capability_mask      : "U32H_FMT"\n", ptr_struct->capability_mask);

}

int register_access_mfpa_size(){
	 return 36;
}

void register_access_mfpa_dump(const struct register_access_mfpa *ptr_struct, FILE* file) {
	register_access_mfpa_print(ptr_struct, file, 0);
}

void register_access_mfbe_pack(const struct register_access_mfbe *ptr_struct, u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	adb2c_push_bits_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->fs);

	offset=23;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->p);

	offset=72;
	adb2c_push_bits_to_buff(ptr_buff, offset, 24, (u_int32_t)ptr_struct->address);

}

void register_access_mfbe_unpack(struct register_access_mfbe *ptr_struct, const u_int8_t* ptr_buff){
	u_int32_t offset;
	int i=0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset=26;
	ptr_struct->fs = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 2);

	offset=23;
	ptr_struct->p = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset=72;
	ptr_struct->address = (u_int32_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 24);

}

void register_access_mfbe_print(const struct register_access_mfbe *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== mfbe ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "fs                   : "UH_FMT"\n", ptr_struct->fs);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "p                    : "UH_FMT"\n", ptr_struct->p);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "address              : "UH_FMT"\n", ptr_struct->address);

}

int register_access_mfbe_size(){
	 return 12;
}

void register_access_mfbe_dump(const struct register_access_mfbe *ptr_struct, FILE* file) {
	register_access_mfbe_print(ptr_struct, file, 0);
}

void register_access_register_access_open_Nodes_pack(const union register_access_register_access_open_Nodes *ptr_struct, u_int8_t* ptr_buff)
{
	memcpy(ptr_buff, ptr_struct, 268);
}

void register_access_register_access_open_Nodes_unpack(union register_access_register_access_open_Nodes *ptr_struct, const u_int8_t* ptr_buff)
{
	memcpy(ptr_struct, ptr_buff, 268);
}

void register_access_register_access_open_Nodes_print(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file, int indent_level){
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== register_access_open_Nodes ========\n");
	int i=0;
	(void)i;(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfbe:\n");
	register_access_mfbe_print(&(ptr_struct->mfbe), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfpa:\n");
	register_access_mfpa_print(&(ptr_struct->mfpa), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfba:\n");
	register_access_mfba_print(&(ptr_struct->mfba), file, indent_level + 1);

}

int register_access_register_access_open_Nodes_size(){
	 return 268;
}

void register_access_register_access_open_Nodes_dump(const union register_access_register_access_open_Nodes *ptr_struct, FILE* file) {
	register_access_register_access_open_Nodes_print(ptr_struct, file, 0);
}

