/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
 *  compatibility.h - Miscellaneous systems compatibility issues
 *
 *  Version: $Id: compatibility.h 3261 2007-01-28 14:59:53Z orenk $
 *
 */

#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <stdio.h>

#if defined(__ia64__) || defined(__x86_64__) || defined(__PPC64__)
    #define U64L       "l"
#else
    #define U64L       "ll"
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
#elif defined(__MINGW32__) || defined(__MINGW64__)              /* Windows MINGW */
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
#define UH_FMT          "0x%x"
#define STR_FMT     "%s"
#define U16H_FMT    "0x%04x"
#define U8H_FMT     "0x%02x"

#if defined(ARCH_x86) || defined(ARCH_ppc) || defined(UEFI_BUILD)
#   if defined(__MINGW32__) || defined(__MINGW64__)
#       include <inttypes.h>
#       define U64D_FMT    "0x%"PRId64
#       define U64H_FMT    "0x%"PRIx64
#       define U64H_FMT_GEN ""PRIx64
#       define U48H_FMT    "0x%"PRIx64
#       define U64D_FMT_GEN ""PRId64
#   else
#       define U64D_FMT     "%llu"
#       define U64H_FMT     "0x%016llx"
#       define U64H_FMT_GEN "llx"
#       define U48H_FMT     "0x%012llx"
#       define U64D_FMT_GEN "llu"
#   endif
#elif defined (ARCH_ia64) || defined(ARCH_x86_64) || defined(ARCH_ppc64) || defined(ARCH_arm64)
#    define U64D_FMT     "%lu"
#    define U64H_FMT     "0x%016lx"
#    define U48H_FMT     "0x%012lx"
#    define U64H_FMT_GEN "lx"
#    define U64D_FMT_GEN "lu"
#else
#   error Unknown architecture
#endif  /* ARCH */


/* define msleep(x) - sleeps for x milliseconds */
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
    #include <Winsock2.h>
    #include <winsock2.h>
    #include <windows.h>
    #define msleep(x)   Sleep(x)
#else
    #include <unistd.h>
    #define msleep(x)   usleep(((unsigned long)x)*1000)
#endif

/*
 * Only for architectures which can't do swab by themselves
 */
#define ___my_swab16(x) \
((u_int16_t)( \
        (((u_int16_t)(x) & (u_int16_t)0x00ffU) << 8) | \
        (((u_int16_t)(x) & (u_int16_t)0xff00U) >> 8) ))
#define ___my_swab32(x) \
((u_int32_t)( \
        (((u_int32_t)(x) & (u_int32_t)0x000000ffUL) << 24) | \
        (((u_int32_t)(x) & (u_int32_t)0x0000ff00UL) <<  8) | \
        (((u_int32_t)(x) & (u_int32_t)0x00ff0000UL) >>  8) | \
        (((u_int32_t)(x) & (u_int32_t)0xff000000UL) >> 24) ))
#define ___my_swab64(x) \
((u_int64_t)( \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00000000000000ffULL) << 56) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x000000000000ff00ULL) << 40) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x0000000000ff0000ULL) << 24) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00000000ff000000ULL) <<  8) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x000000ff00000000ULL) >>  8) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x0000ff0000000000ULL) >> 24) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00ff000000000000ULL) >> 40) | \
        (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0xff00000000000000ULL) >> 56) ))

/*
 * Linux
 */
#if defined(linux) || defined(__FreeBSD__)
// #include <asm/byteorder.h>
    #include <unistd.h>
    #include <sys/types.h>

    #if defined (__FreeBSD__)
    #include <sys/endian.h>
    #else
    #include <endian.h>
    #endif

    #undef __be64_to_cpu
    #undef __be32_to_cpu
    #undef __be16_to_cpu
    #undef __cpu_to_be64
    #undef __cpu_to_be32
    #undef __cpu_to_be16
    #undef __le64_to_cpu
    #undef __le32_to_cpu
    #undef __le16_to_cpu
    #undef __cpu_to_le64
    #undef __cpu_to_le32
    #undef __cpu_to_le16

    #if __BYTE_ORDER == __LITTLE_ENDIAN

        #define __be64_to_cpu(x) ___my_swab64(x)
        #define __be32_to_cpu(x) ___my_swab32(x)
        #define __be16_to_cpu(x) ___my_swab16(x)
        #define __cpu_to_be64(x) ___my_swab64(x)
        #define __cpu_to_be32(x) ___my_swab32(x)
        #define __cpu_to_be16(x) ___my_swab16(x)
        #define __le64_to_cpu(x) (x)
        #define __le32_to_cpu(x) (x)
        #define __le16_to_cpu(x) (x)
        #define __cpu_to_le64(x) (x)
        #define __cpu_to_le32(x) (x)
        #define __cpu_to_le16(x) (x)

    #elif __BYTE_ORDER == __BIG_ENDIAN

        #define __be64_to_cpu(x) (x)
        #define __be32_to_cpu(x) (x)
        #define __be16_to_cpu(x) (x)
        #define __cpu_to_be64(x) (x)
        #define __cpu_to_be32(x) (x)
        #define __cpu_to_be16(x) (x)
        #define __le64_to_cpu(x) ___my_swab64(x)
        #define __le32_to_cpu(x) ___my_swab32(x)
        #define __le16_to_cpu(x) ___my_swab16(x)
        #define __cpu_to_le64(x) ___my_swab64(x)
        #define __cpu_to_le32(x) ___my_swab32(x)
        #define __cpu_to_le16(x) ___my_swab16(x)

    #endif // __BYTE_ORDER

#endif

/*
 * Windows (CYGWIN)
 */
#if defined(__CYGWIN32__)
    #include <asm/byteorder.h>
    #include <unistd.h>

    #define __be64_to_cpu(x) ___my_swab64(x)
    #define __be32_to_cpu(x) ___my_swab32(x)
    #define __be16_to_cpu(x) ___my_swab16(x)
    #define __cpu_to_be64(x) ___my_swab64(x)
    #define __cpu_to_be32(x) ___my_swab32(x)
    #define __cpu_to_be16(x) ___my_swab16(x)
    #define __le64_to_cpu(x) (x)
    #define __le32_to_cpu(x) (x)
    #define __le16_to_cpu(x) (x)
    #define __cpu_to_le64(x) (x)
    #define __cpu_to_le32(x) (x)
    #define __cpu_to_le16(x) (x)

#endif

/*
 * Windows (DDK)
 */
#if defined(__WIN__)
    #include <Winsock2.h>
    #include <winsock2.h>
    #include <windows.h>
    #include <io.h>

    #define __LITTLE_ENDIAN 1234
    #define __BIG_ENDIAN 4321
    #define __BYTE_ORDER __LITTLE_ENDIAN

    #define __be64_to_cpu(x) ___my_swab64(x)
    #define __be32_to_cpu(x) ___my_swab32(x)
    #define __be16_to_cpu(x) ___my_swab16(x)
    #define __cpu_to_be64(x) ___my_swab64(x)
    #define __cpu_to_be32(x) ___my_swab32(x)
    #define __cpu_to_be16(x) ___my_swab16(x)
    #define __le64_to_cpu(x) (x)
    #define __le32_to_cpu(x) (x)
    #define __le16_to_cpu(x) (x)
    #define __cpu_to_le64(x) (x)
    #define __cpu_to_le32(x) (x)
    #define __cpu_to_le16(x) (x)


    #if defined(__MINGW32__) || defined(__MINGW64__)
        #include <stdint.h>
        #ifndef   MFT_TOOLS_VARS
            #define MFT_TOOLS_VARS
            typedef uint8_t  u_int8_t;
            typedef uint16_t u_int16_t;
            typedef uint32_t u_int32_t;
            typedef uint64_t u_int64_t;
        #endif
        #include <string.h>      // Get a define for strcasecmp
        // #define usleep(x) Sleep((x + 999)/1000)

    #else
        typedef unsigned __int8  u_int8_t;
        typedef __int8           int8_t;
        typedef unsigned __int16 u_int16_t;
        typedef __int16          int16_t;
        typedef unsigned __int32 u_int32_t;
        typedef __int32          int32_t;
        typedef unsigned __int64 u_int64_t;
        typedef __int64          int64_t;

        #define strcasecmp    _stricmp
        #define strtoll       _strtoi64
        #define strtoull      _strtoui64
        #define strdup        _strdup

    #endif

    #ifndef __WIN__ // TBD : investigate crash on win
inline
    #endif

    #define COMP_CDECL    __cdecl
    #define COMP_OPEN     ::_open
    #define COMP_CLOSE    ::_close
    #define COMP_READ     ::_read
    #define COMP_FSTAT    ::_fstat

    #ifndef __cplusplus
        #define close _close
    #endif

typedef struct _stat  Stat;

    #define PRIx64 "I64x"
    #define PRIu64 "I64u"
/*
    #ifdef __cplusplus
static inline int pread(int fd, void *buf, int count, u_int64_t offset) {return -1;}
static inline int pwrite(int fd, const void *buf, int count, u_int64_t offset) {return -1;}
    #else
static inline int pread(int fd, void *buf, int count, u_int64_t offset) {return -1;}
static inline int pwrite(int fd, const void *buf, int count, u_int64_t offset) {return -1;}
    #endif
*/
#else

    #define COMP_CDECL
    #define COMP_OPEN     ::open
    #define COMP_CLOSE    ::close
    #define COMP_READ     ::read
    #define COMP_FSTAT    ::fstat

typedef struct stat  Stat;

    #include <sys/time.h>
    #include <strings.h>

#endif



/*
 * MAC (Darwin)
 */
#if defined(__APPLE_CC__)
    #include <architecture/byte_order.h>

    #define __swab64(x)      NXSwapLongLong(x)
    #define __swab32(x)      NXSwapLong(x)
    #define __swab16(x)      NXSwapShort(x)
    #define __be64_to_cpu(x) NXSwapBigLongLongToHost(x)
    #define __be32_to_cpu(x) NXSwapBigLongToHost(x)
    #define __be16_to_cpu(x) NXSwapBigShortToHost(x)
    #define __le64_to_cpu(x) NXSwapLittleLongLongToHost(x)
    #define __le32_to_cpu(x) NXSwapLittleLongToHost(x)
    #define __le16_to_cpu(x) NXSwapLittleShortToHost(x)
    #define __cpu_to_be64(x) NXSwapHostLongLongToBig(x)
    #define __cpu_to_be32(x) NXSwapHostLongToBig(x)
    #define __cpu_to_be16(x) NXSwapHostShortToBig(x)
    #define __cpu_to_le64(x) NXSwapHostLongLongToLittle(x)
    #define __cpu_to_le32(x) NXSwapHostLongToLittle(x)
    #define __cpu_to_le16(x) NXSwapHostShortToLittle(x)

    #define __LITTLE_ENDIAN 1234
    #define __BIG_ENDIAN    4321
    #define __PDP_ENDIAN    3412
    #define __BYTE_ORDER    __BIG_ENDIAN
#endif

/*
 * Solaris
 * -------
 */
#if defined(__sparc__)
    #include <sys/byteorder.h>
    #include <sys/types.h>
    #include <unistd.h>

    #define __be64_to_cpu(x) (x)
    #define __be32_to_cpu(x) (x)
    #define __be16_to_cpu(x) (x)
    #define __cpu_to_be64(x) (x)
    #define __cpu_to_be32(x) (x)
    #define __cpu_to_be16(x) (x)
    #define __le64_to_cpu(x) ___my_swab64(x)
    #define __le32_to_cpu(x) ___my_swab32(x)
    #define __le16_to_cpu(x) ___my_swab16(x)
    #define __cpu_to_le64(x) ___my_swab64(x)
    #define __cpu_to_le32(x) ___my_swab32(x)
    #define __cpu_to_le16(x) ___my_swab16(x)

typedef uint64_t u_int64_t;
typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;
typedef uint8_t  u_int8_t;

#endif

// Convert BYTES - DWORDS with MEMCPY BE
#define BYTES_TO_DWORD_BE(dw_dest, byte_src) do {   u_int32_t tmp;\
                                                    memcpy(&tmp, byte_src, 4);\
                                                    *(dw_dest) = __be32_to_cpu(tmp);\
                                                } while (0)

#define DWORD_TO_BYTES_BE(bytes_dest, dw_src) do { u_int32_t tmp;\
                                                   tmp = __cpu_to_be32(*(dw_src));\
                                                   memcpy(bytes_dest, &tmp, 4);\
                                                 } while (0)

/*
 * Old GCC
 * -------
 */
#if !defined(__WIN__) && defined(__cplusplus) && __GNUG__ < 3
    #include <algo.h>
#endif

#define __STDC_FORMAT_MACROS
#if !defined(__WIN__) && !defined(UEFI_BUILD)
    #include <inttypes.h>
#endif

#ifdef __VMKERNEL_USER_WORLD__
    #define ROOT_PATH "/opt/mellanox/"
#else
    #define ROOT_PATH "/"
#endif

#endif

