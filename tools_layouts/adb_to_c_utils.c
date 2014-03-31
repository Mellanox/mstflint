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
 *** This file was generated at "2014-03-23 17:16:25"
 *** by:
 ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/golan/golan.adb --file-prefix golan --prefix golan_
 ***/

#include "adb_to_c_utils.h"

/************************************
 * Function: adb2c_calc_array_field_address
 ************************************/
u_int32_t adb2c_calc_array_field_address(u_int32_t start_bit_offset, u_int32_t arr_elemnt_size,
                                   int arr_idx, u_int32_t parent_node_size,
                                   int is_big_endian_arr)
{
    u_int32_t offs;

	if (arr_elemnt_size > 32)
	{
		assert(!(arr_elemnt_size % 32));
    	start_bit_offset += arr_elemnt_size*(u_int32_t)arr_idx;                                                                                     
		return start_bit_offset;
	}

    if (is_big_endian_arr)
    {
        u_int32_t dword_delta;
        offs = start_bit_offset - arr_elemnt_size*(u_int32_t)arr_idx;
        dword_delta = (((start_bit_offset>>5)<<2) - ((offs>>5)<<2))/4;
        if (dword_delta)
        {
            offs += 64*dword_delta;
        }
    }
    else
    {
        offs = start_bit_offset + arr_elemnt_size*(u_int32_t)arr_idx;
    }

    //printf("==> %d\n", MIN(32, parent_node_size) - (offs%32) - arr_elemnt_size + ((offs>>5)<<5));
    return ADB2C_MIN(32, parent_node_size) - (offs%32) - arr_elemnt_size + ((offs>>5)<<5);
}

/************************************
 * Function: adb2c_push_integer_to_buff
 ************************************/
void adb2c_push_integer_to_buff(u_int8_t *buff, u_int32_t bit_offset,  u_int32_t byte_size, u_int64_t field_value)
{
    field_value = ADB2C_CPU_TO_BE64(field_value);
    memcpy(buff + bit_offset/8, (u_int8_t*)&field_value + (8-byte_size), (size_t)byte_size);
}

/************************************
 * Function: adb2c_push_bits_to_buff
 ************************************/
//the next function will push the field into the buffer by inserting it's MSB bits first
//and therefore by doing it we save the CPU_TO_BE operation
void adb2c_push_bits_to_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int32_t field_value)
{
    u_int32_t i 		= 0;
    u_int32_t byte_n	= bit_offset / 8;
    u_int32_t byte_n_offset	= bit_offset % 8;
    u_int32_t to_push;

    //going over all bits in field
    while (i < field_size)
    {
        to_push = ADB2C_MIN(8 - byte_n_offset, field_size - i);
        i += to_push;
        ADB2C_INSERTF_8(ADB2C_BYTE_N(buff, byte_n), 8U - to_push - byte_n_offset, field_value, field_size - i, to_push);
        byte_n_offset  = 0;	//(byte_n_offset + to_push) % 8U;
        byte_n++;
    }
}

/************************************
 * Function: adb2c_push_to_buf
 ************************************/
void adb2c_push_to_buf(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value)
{
    bit_offset = adb2c_calc_array_field_address(bit_offset, field_size, 0, field_size + 32, 0);
    if (field_size <= 32)
        adb2c_push_bits_to_buff(buff, bit_offset, field_size, (u_int32_t)field_value);
    else
        adb2c_push_integer_to_buff(buff, bit_offset, field_size/8,  field_value);
}

/************************************
 * Function: adb2c_pop_integer_from_buff
 ************************************/
u_int64_t adb2c_pop_integer_from_buff(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t byte_size)
{
    u_int64_t val = 0;
    memcpy((u_int8_t*)&val + (8-byte_size), buff + bit_offset/8, (size_t)byte_size);
    return ADB2C_BE64_TO_CPU(val);
}

/************************************
 * Function: adb2c_pop_bits_from_buff
 ************************************/
//the next function will pop the field into the buffer by removing it's MSB bits first
//and therefore by doing it we save the BE_TO_CPU operation
u_int32_t adb2c_pop_bits_from_buff(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size)
{
    u_int32_t i 		= 0;
    u_int32_t byte_n	= bit_offset / 8;
    u_int32_t byte_n_offset	= bit_offset % 8;
    u_int32_t field_32	= 0;
    u_int32_t to_pop;

    //going over all bits in field
    while (i < field_size)
    {
        to_pop =  ADB2C_MIN(8 - byte_n_offset, field_size - i);
        i += to_pop;
        ADB2C_INSERTF_8(field_32, field_size - i, ADB2C_BYTE_N(buff, byte_n), 8 - to_pop - byte_n_offset, to_pop);
        byte_n_offset  = 0;	//(byte_n_offset + to_pop) % 8;
        byte_n++;
    }
    return field_32;
}

/************************************
 * Function: adb2c_pop_from_buf
 ************************************/
u_int64_t adb2c_pop_from_buf(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size)
{
    bit_offset = adb2c_calc_array_field_address(bit_offset, field_size, 0, field_size + 32, 0);
    if (field_size <= 32)
        return adb2c_pop_bits_from_buff(buff, bit_offset, field_size);
    else
        return adb2c_pop_integer_from_buff(buff, bit_offset, field_size/8);
}

/************************************
 * Function: adb2c_db_get_field_enum_name
 ************************************/
const char* adb2c_db_get_field_enum_name(struct adb2c_field_format* field, int val)
{
    int i;
    for (i = 0; i < field->enums_len; i++)
    {
        if (field->enums[i].val == val)
            return field->enums[i].name;
    }

    
    return "Unknown Enum Value";
}

/************************************
 * Function: adb2c_db_get_field_enum_val
 ************************************/
int adb2c_db_get_field_enum_val(struct adb2c_field_format* field, const char* name)
{
    int i;
    for (i = 0; i < field->enums_len; i++)
    {
        if (!strcmp(field->enums[i].name, name))
            return field->enums[i].val;
    }

    return -1;
}

/************************************
 * Function: adb2c_db_get_field_attr
 ************************************/
const char* adb2c_db_get_field_attr(struct adb2c_field_format* field, const char* attr_name)
{
	int i;
	for (i = 0; i < field->attrs_len; i++)
	{
		if (!strcmp(attr_name, field->attrs[i].name))
			return field->attrs[i].val;
	}
	
	return NULL;
}

/************************************
 * Function: adb2c_db_get_node_attr
 ************************************/
const char* adb2c_db_get_node_attr(struct adb2c_node_format* node, const char* attr_name)
{
	int i;
	for (i = 0; i < node->attrs_len; i++)
	{
		if (!strcmp(attr_name, node->attrs[i].name))
			return node->attrs[i].val;
	}

	return NULL;
}

/************************************
 * Function: adb2c_db_find_node
 ************************************/
struct adb2c_node_format* adb2c_db_find_node(struct adb2c_node_db* db, const char* node_name)
{
    int i;
    
    for (i = 0; i < db->nodes_len; i++)
    {
        if (!strcmp(node_name, db->nodes[i].name))
            return &db->nodes[i];
    }
    
    return NULL;
}

/************************************
 * Function: adb2c_db_find_field
 ************************************/
struct adb2c_field_format* adb2c_db_find_field(struct adb2c_node_format* node, const char* field_name)
{
    int i;
    
    for(i = 0; i < node->fields_len; i++)
    {
        if (!strcmp(field_name, node->fields[i].full_name))
            return &node->fields[i];
    }
    
    return NULL;
}

/************************************
 * Function: adb2c_add_indentation
 ************************************/
void adb2c_add_indentation(FILE* file, int indent_level)
{
	while (indent_level)
	{
		fprintf(file, "\t");
		indent_level--;
	}
}

/************************************
 * Function: adb2c_print_raw
 ************************************/
void adb2c_print_raw(FILE* file, void* buff, int buff_len)
{
    u_int8_t* data = (u_int8_t*)buff;
    int i;
    adb2c_add_indentation(file, 0);
    for (i = 0; i < buff_len; i++)
    {
        if (!(i % 4))
        {
            fprintf(file, "\n0x%08x: ", i);
        }

        fprintf(file, " 0x%02x", data[i]);
    }
    fprintf(file, "\n");
}
