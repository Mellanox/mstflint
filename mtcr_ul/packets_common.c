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

#include "packets_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifdef __WIN__
    #include <Winsock2.h>   // for htonl
#endif


/************************************/
void push_to_buff_64(u_int8_t *buff, u_int32_t bit_offset, u_int64_t field_value)
{
#if defined(__ia64__)
    u_int32_t *buffer = PTR_32_OF_BUFF(buff, (bit_offset / 8));
    u_int64_t value = CPU_TO_BE64(field_value);
    memcpy(buffer, &value, sizeof(value));
#else
    u_int64_t *buffer = PTR_64_OF_BUFF(buff, (bit_offset / 8));
    memcpy(buffer, &field_value, sizeof(field_value));
    *buffer = CPU_TO_BE64(*buffer);
#endif
}


/************************************/
void push_to_buff_32(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_value)
{
    u_int32_t *buffer = PTR_32_OF_BUFF(buff, (bit_offset / 8));
    memcpy(buffer, &field_value, sizeof(field_value));
    *buffer = CPU_TO_BE32(*buffer);
}


/************************************/
//the next function will push the field into the buffer by inserting it's MSB bits first
//and therefore by doing it we save the CPU_TO_BE operation
void push_to_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int32_t field_value)
{
    u_int32_t i 		= 0;
    u_int32_t byte_n	= bit_offset / 8;
    u_int32_t byte_n_offset	= bit_offset % 8;
    u_int32_t to_push;

    //going over all bits in field
    while (i < field_size) {
        to_push = PCK_MIN(8 - byte_n_offset, field_size - i);
        i += to_push;
        //printf("Inserting %u bits(%u) to byte %u to bit %u\n", to_push, EXTRACT8(field_value, field_size - i, to_push), byte_n, 8 - to_push - byte_n_offset);
        INSERTF_8(BYTE_N(buff, byte_n), 8 - to_push - byte_n_offset, field_value, field_size - i, to_push);
        byte_n_offset  = 0;	//(byte_n_offset + to_push) % 8;
        byte_n++;
    }
}


/************************************/
u_int64_t pop_from_buff_64(u_int8_t *buff, u_int32_t bit_offset)
{
#if defined(__ia64__)
    u_int64_t value = 0;
    memcpy(&value, PTR_32_OF_BUFF(buff, (bit_offset / 8)), sizeof(u_int64_t));
    return (BE64_TO_CPU(value));
#else
    return (BE64_TO_CPU(FIELD_64_OF_BUFF(buff, (bit_offset / 8))));
#endif
}


/************************************/
u_int32_t pop_from_buff_32(u_int8_t *buff, u_int32_t bit_offset)
{
    return (BE32_TO_CPU(FIELD_32_OF_BUFF(buff, (bit_offset / 8))));
}


/************************************/
//the next function will pop the field into the buffer by removing it's MSB bits first
//and therefore by doing it we save the BE_TO_CPU operation
u_int32_t pop_from_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size)
{
    u_int32_t i 		= 0;
    u_int32_t byte_n	= bit_offset / 8;
    u_int32_t byte_n_offset	= bit_offset % 8;
    u_int32_t field_32	= 0;
    u_int32_t to_pop;

    //going over all bits in field
    while (i < field_size) {
        to_pop =  PCK_MIN(8 - byte_n_offset, field_size - i);
        i += to_pop;
        //printf("Removing %u bits(%u) from byte %u to bit %u\n", to_pop, EXTRACT8(BYTE_N(buff, byte_n), 8 - to_pop - byte_n_offset, to_pop), byte_n, field_size - i);
        INSERTF_8(field_32, field_size - i, BYTE_N(buff, byte_n), 8 - to_pop - byte_n_offset, to_pop);
        byte_n_offset  = 0;	//(byte_n_offset + to_pop) % 8;
        byte_n++;
    }
    return field_32;
}


