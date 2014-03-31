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

#ifndef TOOLS_UTILS_H
#define TOOLS_UTILS_H

#include "compatibility.h"

#define CPU_TO_BE32(x)                __cpu_to_be32(x)
#define CPU_TO_LE32(x)                __cpu_to_le32(x)
#define BE32_TO_CPU(x)                __be32_to_cpu(x)
#define LE32_TO_CPU(x)                __le32_to_cpu(x)
#define CPU_TO_BE16(x)                __cpu_to_be16(x)
#define CPU_TO_LE16(x)                __cpu_to_le16(x)
#define BE16_TO_CPU(x)                __be16_to_cpu(x)
#define LE16_TO_CPU(x)                __le16_to_cpu(x)
#define CPU_TO_BE64(x)                __cpu_to_be64(x)
#define CPU_TO_LE64(x)                __cpu_to_le64(x)
#define BE64_TO_CPU(x)                __be64_to_cpu(x)
#define LE64_TO_CPU(x)                __le64_to_cpu(x)

#define FIELD_8_OF_BUFF(buf, offset) (*(u_int8_t*)((u_int8_t*)(buf) + (offset)))
#define FIELD_16_OF_BUFF(buf, offset) (*(u_int16_t*)((u_int8_t*)(buf) + (offset)))
#define FIELD_32_OF_BUFF(buf, offset) (*(u_int32_t*)((u_int8_t*)(buf) + (offset)))
#define FIELD_64_OF_BUFF(buf, offset) (*(u_int64_t*)((u_int8_t*)(buf) + (offset)))
#define BYTE_N(buf, n)  FIELD_8_OF_BUFF((buf), (n))
#define WORD_N(buf, n)  FIELD_16_OF_BUFF((buf), (n) * 2)
#define DWORD_N(buf, n) FIELD_32_OF_BUFF((buf), (n) * 4)
#define QWORD_N(buf, n) FIELD_64_OF_BUFF((buf), (n) * 8)
#define QWORD_EXTRACT_DWORD_HI(qword) ((u_int64_t)(qword) >> 32)
#define QWORD_EXTRACT_DWORD_LO(qword) ((u_int64_t)(qword) & (u_int64_t)0xffffffff)
#define QWORD_INSERT_DWORD_HI(qword, dword) qword = ((qword & (u_int64_t)0xffffffff) | ((u_int64_t)dword << 32))
#define QWORD_INSERT_DWORD_LO(qword, dword) qword = ((qword & (u_int64_t)0xffffffff00000000) | ((u_int64_t)dword))
#define U32_TO_U64(dword1, dword2) ((((u_int64_t)(dword1)) << 32) | (((u_int64_t)(dword2)) & 0xffffffff))


#define TOOLS_MAX(a,b) ((a) > (b) ? (a) : (b))
#define TOOLS_MIN(a,b) ((a) < (b) ? (a) : (b))

/**
 * Suppress compiler warning about unused variable.
 */
#define TOOLS_UNUSED(var) ((void)var)


#endif // TOOLS_UTILS_H

