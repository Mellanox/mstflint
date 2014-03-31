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

#ifndef ADABE_TO_C_UTILS
#define ADABE_TO_C_UTILS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//for htonl etc...
#if defined(_WIN32) || defined(_WIN64)
    #include<Winsock2.h>
#else   /* Linux */
    #include<arpa/inet.h>
#endif  /* Windows */

#ifdef __cplusplus
extern "C" {
#endif

/************************************/
/************************************/
/************************************/
/* Endianess Defines */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    #define PLATFORM_MEM "Little Endianess"
    #define _LITTLE_ENDIANESS
#else           /* __BYTE_ORDER == __BIG_ENDIAN */
    #define PLATFORM_MEM "Big Endianess"
    #define _BIG_ENDIANESS
#endif


/* Bit manipulation macros */

/* MASK generate a bit mask S bits width */
//#define ADB2C_MASK32(S)     ( ((u_int32_t) ~0L) >> (32-(S)) )
#define ADB2C_MASK8(S)        ( ((u_int8_t) ~0) >> (8-(S)) )

/* BITS generate a bit mask with bits O+S..O set (assumes 32 / 8 bit integer) */
//#define ADB2C_BITS32(O,S)   ( ADB2C_MASK32(S) << (O) )
#define ADB2C_BITS8(O,S)      ( ADB2C_MASK8(S) << (O) )

/* EXTRACT32/8 macro extracts S bits from (u_int32_t/u_int8_t)W with offset O
 * and shifts them O places to the right (right justifies the field extracted) */
//#define ADB2C_EXTRACT32(W,O,S)  ( ((W)>>(O)) & ADB2C_MASK32(S) )
#define ADB2C_EXTRACT8(W,O,S)     ( ((W)>>(O)) & ADB2C_MASK8(S) )


/* INSERT32/8 macro inserts S bits with offset O from field F into word W (u_int32_t/u_int8_t) */
//#define ADB2C_INSERT32(W,F,O,S)     ((W)= ( ( (W) & (~ADB2C_BITS32(O,S)) ) | (((F) & ADB2C_MASK32(S))<<(O)) ))
#define ADB2C_INSERT8(W,F,O,S)        ((W)= ( ( (W) & (~ADB2C_BITS8(O,S)) ) | (((F) & ADB2C_MASK8(S))<<(O)) ))

//#define ADB2C_INSERTF_32(W,O1,F,O2,S)   (ADB2C_INSERT32(W, ADB2C_EXTRACT32(F, O2, S), O1, S) )
#define ADB2C_INSERTF_8(W,O1,F,O2,S)      (ADB2C_INSERT8(W, ADB2C_EXTRACT8(F, O2, S), O1, S) )


#define ADB2C_PTR_64_OF_BUFF(buf, offset)     ((u_int64_t*)((u_int8_t*)(buf) + (offset)))
#define ADB2C_PTR_32_OF_BUFF(buf, offset)     ((u_int32_t*)((u_int8_t*)(buf) + (offset)))
#define ADB2C_PTR_8_OF_BUFF(buf, offset)      ((u_int8_t*)((u_int8_t*)(buf) + (offset)))
#define ADB2C_FIELD_64_OF_BUFF(buf, offset)   (*ADB2C_PTR_64_OF_BUFF(buf, offset))
#define ADB2C_FIELD_32_OF_BUFF(buf, offset)   (*ADB2C_PTR_32_OF_BUFF(buf, offset))
#define ADB2C_FIELD_8_OF_BUFF(buf, offset)    (*ADB2C_PTR_8_OF_BUFF(buf, offset))
#define ADB2C_DWORD_N(buf, n)                 ADB2C_FIELD_32_OF_BUFF((buf), (n) * 4)
#define ADB2C_BYTE_N(buf, n)                  ADB2C_FIELD_8_OF_BUFF((buf), (n))


#define ADB2C_MIN(a, b)   ((a) < (b) ? (a) : (b))


#define ADB2C_CPU_TO_BE32(x)  htonl(x)
#define ADB2C_BE32_TO_CPU(x)  ntohl(x)
#define ADB2C_CPU_TO_BE16(x)  htons(x)
#define ADB2C_BE16_TO_CPU(x)  ntohs(x)
#ifdef _LITTLE_ENDIANESS
    #define ADB2C_CPU_TO_BE64(x) (((u_int64_t)htonl((u_int32_t)((x) & 0xffffffff)) << 32) |                             ((u_int64_t)htonl((u_int32_t)((x >> 32) & 0xffffffff))))

    #define ADB2C_BE64_TO_CPU(x) (((u_int64_t)ntohl((u_int32_t)((x) & 0xffffffff)) << 32) |                             ((u_int64_t)ntohl((u_int32_t)((x >> 32) & 0xffffffff))))
#else
    #define ADB2C_CPU_TO_BE64(x) (x)
    #define ADB2C_BE64_TO_CPU(x) (x)
#endif


/* define macros to the architecture of the CPU */
#if defined(__linux) || defined(__FreeBSD__)             /* __linux || __FreeBSD__ */
#   if defined(__i386__)
#       define ARCH_x86
#   elif defined(__x86_64__)
#       define ARCH_x86_64
#   elif defined(__ia64__)
#       define ARCH_ia64
#   elif defined(__PPC64__)
#       define ARCH_ppc64
#   elif defined(__PPC__)
#       define ARCH_ppc
#   elif defined(__aarch64__)
#       define ARCH_arm64
#   else
#       error Unknown CPU architecture using the linux OS
#   endif
#elif defined(__MINGW32__) || defined(__MINGW64__)		/* Windows MINGW */
#   if defined(__MINGW32__)
#       define ARCH_x86
#   elif defined(__MINGW64__)
#       define ARCH_x86_64
#   else
#       error Unknown CPU architecture using the windows-mingw OS
#   endif
#elif defined(_WIN32) || defined(_WIN64)                /* Windows */
#   if defined(_WIN32)
#       define ARCH_x86
#   elif defined(_WIN64)
#       define ARCH_x86_64
#   else
#       error Unknown CPU architecture using the windows OS
#   endif
#else                                                   /* Unknown */
#   error Unknown OS
#endif


/* define macros for print fields */
#define U32D_FMT    "%u"
#define U32H_FMT    "0x%08x"
#define UH_FMT		"0x%x"
#define STR_FMT     "%s"
#define U16H_FMT    "0x%04x"
#define U8H_FMT     "0x%02x"

#if defined(ARCH_x86) || defined(ARCH_ppc) || defined(UEFI_BUILD)
#   if defined(__MINGW32__) || defined(__MINGW64__)
#       include <inttypes.h>
#       define U64D_FMT    "0x%"PRId64
#       define U64H_FMT    "0x%"PRIx64
#       define U48H_FMT    "0x%"PRIx64
#   else
#       define U64D_FMT    "%llu"
#       define U64H_FMT    "0x%016llx"
#       define U48H_FMT    "0x%012llx"
#   endif
#elif defined (ARCH_ia64) || defined(ARCH_x86_64) || defined(ARCH_ppc64) || defined(ARCH_arm64)
#    define U64D_FMT    "%lu"
#    define U64H_FMT    "0x%016lx"
#	 define U48H_FMT	"0x%012lx" 
#else
#   error Unknown architecture
#endif  /* ARCH */


#if !defined(_WIN32) && !defined(_WIN64)    		/* Linux */
    #include <sys/types.h>
#elif defined(__MINGW32__) || defined(__MINGW64__) 	/* windows - mingw */
    #include <stdint.h>                                                                                                                                           
    #ifndef   MFT_TOOLS_VARS                                                                                                                                      
		#define MFT_TOOLS_VARS                                                                                                                                    
		typedef uint8_t  u_int8_t;                                                                                                                                
		typedef uint16_t u_int16_t;                                                                                                                               
		typedef uint32_t u_int32_t;                                                                                                                               
		typedef uint64_t u_int64_t;                                                                                                                               
	#endif
#else   											/* Windows */
    typedef __int8                  int8_t;
    typedef unsigned __int8         u_int8_t;
    typedef __int16                 int16_t;
    typedef unsigned __int16        u_int16_t;
    typedef __int32                 int32_t;
    typedef unsigned __int32        u_int32_t;
    typedef __int64                 int64_t;
    typedef unsigned __int64        u_int64_t;
#endif


/************************************/
/************************************/
/************************************/
struct adb2c_attr_format
{
    const char* name;
    const char* val;
};

struct adb2c_enum_format
{
	int				val;
    const char*     name;
};

struct adb2c_field_format
{
    const char*             full_name;
    const char*             desc;
    int                     offs;
    int                     size;
    int                     enums_len;
    struct adb2c_enum_format*     enums;
    int                     attrs_len;
    struct adb2c_attr_format*     attrs;
};

struct adb2c_node_format
{
    const char*          name;
    const char*          desc;
    int                  size;
    int                  is_union;
    int                  attrs_len;
    struct adb2c_attr_format*  attrs;
    int                  fields_len;
    struct adb2c_field_format* fields;
};

struct adb2c_node_db
{
    int                 nodes_len;
    struct adb2c_node_format* nodes;
};

/************************************/
/************************************/
/************************************/
u_int32_t adb2c_calc_array_field_address(u_int32_t start_bit_offset, u_int32_t arr_elemnt_size,
                                   int arr_idx, u_int32_t parent_node_size,
                                   int is_big_endian_arr);
void adb2c_push_integer_to_buff(u_int8_t *buff, u_int32_t bit_offset,  u_int32_t byte_size, u_int64_t field_value);                                
void adb2c_push_bits_to_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int32_t field_value);
void adb2c_push_to_buf(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value);
u_int64_t adb2c_pop_integer_from_buff(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t byte_size);
u_int32_t adb2c_pop_bits_from_buff(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size);
u_int64_t adb2c_pop_from_buf(const u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size);
void adb2c_add_indentation(FILE* file, int indent_level);

void adb2c_print_raw(FILE* file, void* buff, int buff_len);
void adb2c_push_to_buf(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int64_t field_value);
const char* adb2c_db_get_field_enum_name(struct adb2c_field_format* field, int val);
int adb2c_db_get_field_enum_val(struct adb2c_field_format* field, const char* name);
const char* adb2c_db_get_field_attr(struct adb2c_field_format* field, const char* attr_name);
const char* adb2c_db_get_node_attr(struct adb2c_node_format* node, const char* attr_name);
struct adb2c_node_format* adb2c_db_find_node(struct adb2c_node_db* db, const char* node_name);
struct adb2c_field_format* adb2c_db_find_field(struct adb2c_node_format*, const char* field_name);

#ifdef __cplusplus
}
#endif

#endif // ADABE_TO_C_UTILS
