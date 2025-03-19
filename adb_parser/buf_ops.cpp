/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "buf_ops.h"

/************************************
 * Function: calc_array_field_address
 ************************************/
static u_int32_t calc_array_field_address(u_int32_t start_bit_offset,
                                          u_int32_t arr_elemnt_size,
                                          int arr_idx,
                                          u_int32_t parent_node_size,
                                          int is_big_endian_arr)
{
    u_int32_t offs;

    if (arr_elemnt_size > 32)
    {
        assert(!(arr_elemnt_size % 32));
        start_bit_offset += arr_elemnt_size * arr_idx;
        return start_bit_offset;
    }

    if (is_big_endian_arr)
    {
        u_int32_t dword_delta;
        offs = start_bit_offset - arr_elemnt_size * arr_idx;
        dword_delta = (((start_bit_offset >> 5) << 2) - ((offs >> 5) << 2)) / 4;
        if (dword_delta)
        {
            offs += 64 * dword_delta;
        }
    }
    else
    {
        offs = start_bit_offset + arr_elemnt_size * arr_idx;
    }

    // printf("==> parent_node_size=%d, offs=%d, arr_elemnt_size=%d\n", parent_node_size, offs, arr_elemnt_size);
    return TOOLS_MIN(32, parent_node_size) - (offs % 32) - arr_elemnt_size + ((offs >> 5) << 5);
}

static void push_integer_to_buff_le(u_int8_t* buff, u_int32_t bit_offset, u_int32_t byte_size, u_int64_t field_value)
{
    memcpy(buff + bit_offset / 8, (u_int8_t*)&field_value, byte_size);
}

/************************************
 * Function: push_integer_to_buff
 ************************************/
static void push_integer_to_buff(u_int8_t* buff, u_int32_t bit_offset, u_int32_t byte_size, u_int64_t field_value)
{
    field_value = CPU_TO_BE64(field_value);
    memcpy(buff + bit_offset / 8, (u_int8_t*)&field_value + (8 - byte_size), byte_size);
}

/************************************
 * Function: push_bits_to_buff
 ************************************/
// the next function will push the field into the buffer by inserting it's MSB bits first
// and therefore by doing it we save the CPU_TO_BE operation
static void push_bits_to_buff(u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size, u_int32_t field_value)
{
    u_int32_t i = 0;
    u_int32_t byte_n = bit_offset / 8;
    u_int32_t byte_n_offset = bit_offset % 8;
    u_int32_t to_push;

    // going over all bits in field
    while (i < field_size)
    {
        to_push = TOOLS_MIN(8 - byte_n_offset, field_size - i);
        i += to_push;
        BYTE_N(buff, byte_n) =
          INSERTF(BYTE_N(buff, byte_n), 8 - to_push - byte_n_offset, field_value, field_size - i, to_push);
        byte_n_offset = 0; //(byte_n_offset + to_push) % 8;
        byte_n++;
    }
}

static void push_bits_to_buff_le(uint8_t* buff, uint32_t bit_offset, uint32_t field_size, uint32_t field_value)
{
    uint32_t byte_n = bit_offset / 8;        // byte offset
    uint32_t byte_n_offset = bit_offset % 8; // bit offset
    uint32_t bits_written = 0;

    while (bits_written < field_size)
    {
        uint32_t bits_to_write = TOOLS_MIN(8 - byte_n_offset, field_size - bits_written);

        buff[byte_n] |= ((EXTRACT(field_value, bits_written, bits_to_write)) << byte_n_offset);

        bits_written += bits_to_write;
        byte_n_offset = (byte_n_offset + bits_to_write) % 8;
        if (byte_n_offset == 0)
        {
            byte_n++;
        }
    }
}

/************************************
 * Function: push_to_buf
 ************************************/
void push_to_buf(u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value)
{
    bit_offset = calc_array_field_address(bit_offset, field_size, 0, field_size + 32, 0);
    if (field_size <= 32)
    {
        push_bits_to_buff(buff, bit_offset, field_size, field_value);
    }
    else
    {
        push_integer_to_buff(buff, bit_offset, field_size / 8, field_value);
    }
}

void push_to_buf_le(u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value)
{
    if (field_size <= 32)
    {
        push_bits_to_buff_le(buff, bit_offset, field_size, field_value);
    }
    else
    {
        push_integer_to_buff_le(buff, bit_offset, field_size / 8, field_value);
    }
}

/************************************
 * Function: pop_integer_from_buff
 ************************************/
static u_int64_t pop_integer_from_buff(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t byte_size)
{
    u_int64_t val = 0;
    memcpy((u_int8_t*)&val + (8 - byte_size), buff + bit_offset / 8, byte_size);
    return BE64_TO_CPU(val);
}

/************************************
 * Function: pop_bits_from_buff
 ************************************/
// the next function will pop the field into the buffer by removing it's MSB bits first
// and therefore by doing it we save the BE_TO_CPU operation
static u_int32_t pop_bits_from_buff(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size)
{
    u_int32_t i = 0;
    u_int32_t byte_n = bit_offset / 8;
    u_int32_t byte_n_offset = bit_offset % 8;
    u_int32_t field_32 = 0;
    u_int32_t to_pop;

    // going over all bits in field
    while (i < field_size)
    {
        to_pop = TOOLS_MIN(8 - byte_n_offset, field_size - i);
        i += to_pop;
        field_32 = INSERTF(field_32, field_size - i, BYTE_N(buff, byte_n), 8 - to_pop - byte_n_offset, to_pop);
        byte_n_offset = 0; //(byte_n_offset + to_pop) % 8;
        byte_n++;
    }

    return field_32;
}

/************************************
 * Function: pop_bits_from_buff_le
 ************************************/
static uint32_t
  pop_bits_from_buff_le(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size, bool small_entry_array)
{
    small_entry_array = small_entry_array && (__BYTE_ORDER == __LITTLE_ENDIAN);
    uint32_t dword_n = bit_offset / 32;
    uint32_t bit_in_dword = bit_offset % 32;
    uint32_t field_32 = 0;

    uint32_t shift = small_entry_array ? 32 - (bit_in_dword + field_size) : bit_in_dword;

    uint32_t source_dword = ((uint32_t*)buff)[dword_n];
    uint32_t mask = (uint32_t)(-1);
    mask = mask >> (32 - field_size);
    field_32 = (source_dword >> shift) & mask;
    return field_32;
}

/************************************
 * Function: pop_from_buf
 ************************************/
u_int64_t pop_from_buf(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size)
{
    bit_offset = calc_array_field_address(bit_offset, field_size, 0, field_size + 32, 0);

    if (field_size <= 32)
    {
        return pop_bits_from_buff(buff, bit_offset, field_size);
    }
    else
    {
        return pop_integer_from_buff(buff, bit_offset, field_size / 8);
    }
}

/************************************
 * Function: pop_from_buf_le
 ************************************/
u_int64_t pop_from_buf_le(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size, bool wa)
{
    if (field_size <= 32)
    {
        return pop_bits_from_buff_le(buff, bit_offset, field_size, wa);
    }
    else
    {
        return (uint64_t)(-1);
    }
}

/************************************
 * Function: add_indentation
 ************************************/
static void add_indentation(FILE* file, int indent_level)
{
    while (indent_level)
    {
        fprintf(file, "\\t");
        indent_level--;
    }
}

/************************************
 * Function: print_raw
 ************************************/
void print_raw(FILE* file, void* buff, int buff_len)
{
    u_int8_t* data = (u_int8_t*)buff;
    int i;
    add_indentation(file, 0);
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
