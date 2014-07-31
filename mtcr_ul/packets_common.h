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

#ifndef packet_common_H
#define packet_common_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "compatibility.h"

#ifndef __WIN__
    #include <netinet/in.h>
/************************************/
/* Endianess Defines */
/*
#if __BYTE_ORDER == __LITTLE_ENDIAN
    #ifndef PLATFORM_MEM
         // #define PLATFORM_MEM "Little Endianess"
    #endif
    #define _LITTLE_ENDIANESS
#endif

#if __BYTE_ORDER == __BIG_ENDIAN
    //#define PLATFORM_MEM "Big Endianess"
    #define _BIG_ENDIANESS
#endif

#else
    #define __BYTE_ORDER __LITTLE_ENDIAN
    #ifndef PLATFORM_MEM
        //#define PLATFORM_MEM "Big Endianess"
    #endif
    #define _BIG_ENDIANESS
    typedef unsigned __int8  u_int8_t;
    typedef __int8           int8_t;
    typedef unsigned __int16 u_int16_t;
    typedef __int16          int16_t;
    typedef unsigned __int32 u_int32_t;
    typedef __int32          int32_t;
    typedef unsigned __int64 u_int64_t;
    typedef __int64          int64_t;
    */
#endif



/************************************/
/* Bit manipulation macros */

/* MASK generate a bit mask S bits width */
//#define MASK32(S)     ( ((u_int32_t) ~0L) >> (32-(S)) )
#define MASK8(S)        ( ((u_int8_t) ~0) >> (8-(S)) )

/* BITS generate a bit mask with bits O+S..O set (assumes 32 / 8 bit integer) */
//#define BITS32(O,S)   ( MASK32(S) << (O) )
#define BITS8(O,S)      ( MASK8(S) << (O) )

/* EXTRACT32/8 macro extracts S bits from (u_int32_t/u_int8_t)W with offset O
 * and shifts them O places to the right (right justifies the field extracted) */
//#define EXTRACT32(W,O,S)  ( ((W)>>(O)) & MASK32(S) )
#define EXTRACT8(W,O,S)     ( ((W)>>(O)) & MASK8(S) )

#define PCK_MIN(a, b)   ((a) < (b) ? (a) : (b))
/* INSERT32/8 macro inserts S bits with offset O from field F into word W (u_int32_t/u_int8_t) */
//#define INSERT32(W,F,O,S)     ((W)= ( ( (W) & (~BITS32(O,S)) ) | (((F) & MASK32(S))<<(O)) ))
#define INSERT8(W,F,O,S)        ((W)= ( ( (W) & (~BITS8(O,S)) ) | (((F) & MASK8(S))<<(O)) ))

//#define INSERTF_32(W,O1,F,O2,S)   (INSERT32(W, EXTRACT32(F, O2, S), O1, S) )
#define INSERTF_8(W,O1,F,O2,S)      (INSERT8(W, EXTRACT8(F, O2, S), O1, S) )


/************************************/
#define PTR_64_OF_BUFF(buf, offset)     ((u_int64_t*)((u_int8_t*)(buf) + (offset)))
#define PTR_32_OF_BUFF(buf, offset)     ((u_int32_t*)((u_int8_t*)(buf) + (offset)))
#define PTR_8_OF_BUFF(buf, offset)      ((u_int8_t*)((u_int8_t*)(buf) + (offset)))
#define FIELD_64_OF_BUFF(buf, offset)   (*PTR_64_OF_BUFF(buf, offset))
#define FIELD_32_OF_BUFF(buf, offset)   (*PTR_32_OF_BUFF(buf, offset))
#define FIELD_8_OF_BUFF(buf, offset)    (*PTR_8_OF_BUFF(buf, offset))
#define DWORD_N(buf, n)                 FIELD_32_OF_BUFF((buf), (n) * 4)
#define BYTE_N(buf, n)                  FIELD_8_OF_BUFF((buf), (n))


/************************************/
// #define MIN(a, b)   ((a) < (b) ? (a) : (b))


/************************************/
#define CPU_TO_BE32(x)  htonl(x)
#define BE32_TO_CPU(x)  ntohl(x)
#define CPU_TO_BE16(x)  htons(x)
#define BE16_TO_CPU(x)  ntohs(x)
#ifdef _LITTLE_ENDIANESS
    #define CPU_TO_BE64(x) (((u_int64_t)htonl((u_int32_t)((x) & 0xffffffff)) << 32) | \
                            ((u_int64_t)htonl((u_int32_t)((x >> 32) & 0xffffffff))))

    #define BE64_TO_CPU(x) (((u_int64_t)ntohl((u_int32_t)((x) & 0xffffffff)) << 32) | \
                            ((u_int64_t)ntohl((u_int32_t)((x >> 32) & 0xffffffff))))
#else
    #define CPU_TO_BE64(x) (x)
    #define BE64_TO_CPU(x) (x)
#endif


/************************************/
/* define macros to the architecture of the CPU */
#if defined(__linux) || defined(__FreeBSD__)
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
#elif defined(_WIN32)

//#   error Windows OS need to define macros
#else       /* __linux || __FreeBSD__ */
#   error Unknown OS
#endif      /* __linux || __FreeBSD__ */


/**********************************/
/* define macros for print fields */
//#if defined (ARCH_ia64) || defined(ARCH_x86_64) || defined(ARCH_ppc64) || defined(__MINGW64__)
/*
#if !defined(UEFI_BUILD) && (defined (ARCH_ia64) || defined(ARCH_x86_64) || defined(ARCH_ppc64) || defined(__MINGW64__))
#   define U64H_FMT "0x%016lx"
#   define U64D_FMT "%lu"
#   define U32H_FMT "0x%08x"
#   define U16H_FMT "0x%04x"
#   define U8H_FMT  "0x%02x"
#   define U32D_FMT "%u"
#   define STR_FMT "%s"
#elif defined(ARCH_x86) || defined(ARCH_ppc) || defined(__MINGW32__) || defined(UEFI_BUILD)
#   define U64H_FMT "0x%016llx"
#   define U64D_FMT "%llu"
#   define U32H_FMT "0x%08x"
#   define U16H_FMT "0x%04x"
#   define U8H_FMT  "0x%02x"
#   define U32D_FMT "%u"
#   define STR_FMT "%s"
#else  // ARCH
#   error Unknown architecture
#endif // ARCH
*/

/**********************************/
void push_to_buff_64(u_int8_t *buff, u_int32_t bit_offset, u_int64_t field_value);
void push_to_buff_32(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_value);
void push_to_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size, u_int32_t field_value);
u_int64_t pop_from_buff_64(u_int8_t *buff, u_int32_t bit_offset);
u_int32_t pop_from_buff_32(u_int8_t *buff, u_int32_t bit_offset);
u_int32_t pop_from_buff(u_int8_t *buff, u_int32_t bit_offset, u_int32_t field_size);

#endif          /* def packet_common_H */


