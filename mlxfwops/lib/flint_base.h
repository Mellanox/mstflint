/*
 *
 * flint_base.h - FLash INTerface
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id: flint_base.h 7522 2011-11-16 15:37:21Z mohammad $
 *
 */
#ifndef FLINT_BASE_H
#define FLINT_BASE_H

#ifndef UEFI_BUILD
#ifndef __FreeBSD__
#include <malloc.h>
#endif
#else
#include "uefi_c.h"
#endif

#if defined __FreeBSD__
#include <stdarg.h>
#endif

#include <signal.h>
#include "tools_version.h"

#ifndef __WIN__

//
// GCC Compiler
//

#if defined __DJGPP__
//
// DJGPP - GCC PORT TO MS DOS
//

#include <mtcr.h> // This contains the u_* types definitions

#include <netinet/in.h>
#include <unistd.h>

#define bswap_32(x) ntohl(x)

// djgpp stdio does not define vsnprintf. I simply call vsprintf (and pray ...)
#define vsnprintf(buf, len, format, args) (vsprintf(buf, format, args))
#define snprintf(buf, len, format, args...) (sprintf(buf, format, args))
#endif // __DJGPP__

#else // __WIN__

//
// Windows (Under DDK)
//
#include <mtcr.h>
// Sleep adaptor
#define usleep(x) Sleep((x) / 1000)
#define sleep(x) Sleep((x)*1000)

#define vsnprintf _vsnprintf
#define isatty _isatty

// MINGW
#if defined(__MINGW32__) || (__MINGW64__)
#define _UNISTD_H // Zlib includes unistd.h which causes some compilation errors.
#else
#define strtoull _strtoui64
#endif
#endif // __WIN__

#include <vector>
#include <compatibility.h>
#include "mlxfwops_com.h"

static inline void be_guid_to_cpu(guid_t* to, guid_t* from)
{
    to->h = __be32_to_cpu(from->h);
    to->l = __be32_to_cpu(from->l);
}
namespace std
{
};
using namespace std;

#define TOCPU1(s) s = __be32_to_cpu((u_int32_t)(s));
#define CPUTO1(s) s = __cpu_to_be32((u_int32_t)(s));
#define TOCPU(s)                                                               \
    do                                                                         \
    {                                                                          \
        u_int32_t* p = (u_int32_t*)(s);                                        \
        for (u_int32_t ii = 0; ii < sizeof(*s) / sizeof(u_int32_t); ii++, p++) \
            *p = __be32_to_cpu(*p);                                            \
    } while (0)
#define TOCPUn(s, n)                                \
    do                                              \
    {                                               \
        u_int32_t* p = (u_int32_t*)(s);             \
        for (u_int32_t ii = 0; ii < (n); ii++, p++) \
            *p = __be32_to_cpu(*p);                 \
    } while (0)

#define CPUTOn(s, n)                                \
    do                                              \
    {                                               \
        u_int32_t* p = (u_int32_t*)(s);             \
        for (u_int32_t ii = 0; ii < (n); ii++, p++) \
            *p = __cpu_to_be32(*p);                 \
    } while (0)

#define TOCPUBY(s)                                                            \
    do                                                                        \
    {                                                                         \
        u_int32_t* p = (u_int32_t*)(&s);                                      \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t); ii++, p++) \
            *p = __be32_to_cpu(*p);                                           \
    } while (0)
#define CPUTOBY(s)                                                            \
    do                                                                        \
    {                                                                         \
        u_int32_t* p = (u_int32_t*)(&s);                                      \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t); ii++, p++) \
            *p = __cpu_to_be32(*p);                                           \
    } while (0)
#define TOCPUBY64(s)                                                      \
    do                                                                    \
    {                                                                     \
        guid_t* p = s;                                                    \
        for (unsigned ii = 0; ii < sizeof(s) / sizeof(guid_t); ii++, p++) \
            be_guid_to_cpu(p, p);                                         \
    } while (0)
#define CRC(c, s)                                                        \
    do                                                                   \
    {                                                                    \
        u_int32_t* p = (u_int32_t*)(s);                                  \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t); ii++) \
            c << *p++;                                                   \
    } while (0)
#define CRCn(c, s, n)                          \
    do                                         \
    {                                          \
        u_int32_t* p = (u_int32_t*)(s);        \
        for (u_int32_t ii = 0; ii < (n); ii++) \
            c << *p++;                         \
    } while (0)
#define CRCBY(c, s)                                                      \
    do                                                                   \
    {                                                                    \
        u_int32_t* p = (u_int32_t*)(&s);                                 \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t); ii++) \
            c << *p++;                                                   \
    } while (0)
#define CRC1(c, s)                                                           \
    do                                                                       \
    {                                                                        \
        u_int32_t* p = (u_int32_t*)(s);                                      \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t) - 1; ii++) \
            c << *p++;                                                       \
    } while (0)
#define CRC1n(c, s, n)                           \
    do                                           \
    {                                            \
        u_int32_t* p = (u_int32_t*)(s);          \
        for (u_int32_t ii = 0; ii < (n)-1; ii++) \
            c << *p++;                           \
    } while (0)
#define CRC1BY(c, s)                                                         \
    do                                                                       \
    {                                                                        \
        u_int32_t* p = (u_int32_t*)(&s);                                     \
        for (u_int32_t ii = 0; ii < sizeof(s) / sizeof(u_int32_t) - 1; ii++) \
            c << *p++;                                                       \
    } while (0)

#define CHECKB2(b, o, n, f, p, fp)          \
    do                                      \
    {                                       \
        if (!CheckBoot2(b, o, n, f, p, fp)) \
        {                                   \
            return false;                   \
        }                                   \
    } while (0)
#define FS3_CHECKB2(b, o, f, p, i)         \
    {                                      \
        u_int32_t n;                       \
        if (!CheckBoot2(b, o, n, f, p, i)) \
        {                                  \
            return false;                  \
        }                                  \
    }

#define CHECKGN(b, o, n, p, fp)        \
    do                                 \
    {                                  \
        if (!checkGen(b, o, n, p, fp)) \
        {                              \
            return false;              \
        }                              \
    } while (0)
#define CHECKLS(o, s, p)         \
    do                           \
    {                            \
        if (!checkList(o, s, p)) \
        {                        \
            return false;        \
        }                        \
    } while (0)
#define READ4(f, o, d, p)                                        \
    do                                                           \
    {                                                            \
        if (!f.read(o, d))                                       \
        {                                                        \
            return errmsg("%s - read error (%s)\n", p, f.err()); \
        }                                                        \
    } while (0)
#define READ4_NOERRMSG(f, o, d) \
    do                          \
    {                           \
        if (!f.read(o, d))      \
        {                       \
            return false;       \
        }                       \
    } while (0)
#define READBUF(f, o, d, l, p)                                   \
    do                                                           \
    {                                                            \
        if (!f.read(o, d, l))                                    \
        {                                                        \
            return errmsg("%s - read error (%s)\n", p, f.err()); \
        }                                                        \
    } while (0)
#define READALLOCBUF(f, o, d, l, p)                              \
    do                                                           \
    {                                                            \
        d = (u_int8_t*)calloc(l, sizeof(u_int8_t));              \
        if (!f.read(o, d, l))                                    \
        {                                                        \
            free(d);                                             \
            return errmsg("%s - read error (%s)\n", p, f.err()); \
        }                                                        \
    } while (0)

#define FS2_BOOT_START 0x38
#define FS_DATA_OFF 0x28

#define CONNECT_IB_SW_ID 4113

// FS3 defines
#define FS3_BOOT_START FS2_BOOT_START
#define FS3_BOOT_START_IN_DW FS3_BOOT_START / 4

// FS4 defines
#define FS4_HW_PTR_START 0x18

#define CRC_CHECK_OLD "%s /0x%08x-0x%08x (0x%06x)/ (%s"

#define MAX_NUM_SUPP_HW_IDS 200
#define MAX_NUM_SUPP_HW_LIST_STR (MAX_NUM_SUPP_HW_IDS * 40)
#define MAC_SPACES "            "
#define GUID_SPACES "        "
#define GUID_FORMAT "%8.8x%8.8x"
#define MAC_FORMAT "%4.4x%8.8x"

#define FLINT_LOG_ENV "FLINT_LOG_FILE"
#define IMG_CRC_OFF 0x20
#define MAX_ERR_STR_LEN 1024

#define MLXCONFIG_CMD "config"
enum
{
    SIGNATURE = 0x5a445a44,
    MELLANOX_VENDOR_ID = 0x15b3
};

enum SectionType
{
    H_FIRST = 1,
    H_DDR = 1,
    H_CNF = 2,
    H_JMP = 3,
    H_EMT = 4,
    H_ROM = 5,
    H_GUID = 6,
    H_BOARD_ID = 7,
    H_USER_DATA = 8,
    H_FW_CONF = 9,
    H_IMG_INFO = 10,
    H_DDRZ = 11,
    H_HASH_FILE = 12,
    H_LAST
};

/* Description - Section ID Section Type DESCRIPTION\;0x1 BOOT_CODE FW loader code\;0x2 PCI_CODE Code that is required
 * to raise PCIe link.\; 0x3 MAIN_CODE All non-PCIe FW code\;0x8 HW_BOOT_CFG Initial values for the PCI related
 * registers\;0x9 HW_MAIN_CFG Initial values for all other registers \;0x10 IMAGE_INFO Management data for the burning
 * tool. See 'Image Info Section' chapter in the Mellanox Flash Programming
 *  Application Note\;0x11 FW_BOOT_CFG Initial values for user set-able hi level non-hardware related settings, such as
 * number of physical functions\
 *  ;(optional)\;0x12 FW_MAIN_CFG Initial values for user set-able hi level non-hardware related
 * settings.\;(optional)\;0x18 ROM_CODE PXE/Boot over IB code.
 *   \;0x30 DBG_LOG_MAP FW logger 'index to string' map. The map is in ASCI text. Format is TBD.\;
 *   PARAM0 in the iTOC specifies the compression method of this sector:\;                                          0.
 * Uncompressed\;
 *    1. Zlib compress2()\;                                          2. LZMA\; Others - Reserved \;0x31 DBG_FW_INI The
 * Ini file used in the image generation. The PARAM0 applies the same as in  DBG_LOG_MAP section type.\;0x32
 * DBG_FW_PARAMS FW settable parameters. ASCII text. Format is TBD. The PARAM0 applies the same as in  DBG_LOG_MAP
 * section type.\;0xff END_MARKER A type of 0xff marks the end of the iTOC entries
 *     array. It is recommended to leave the unused part of the iTOC section blank (that is, 0xff in all unused
 * bytes)\;All other values Reserved \; */

typedef enum fs3_section
{
    FS3_BOOT_CODE = 0x1,
    FS3_PCI_CODE = 0x2,
    FS3_MAIN_CODE = 0x3,
    FS3_PCIE_LINK_CODE = 0x4,
    FS3_IRON_PREP_CODE = 0x5,
    FS3_POST_IRON_BOOT_CODE = 0x6,
    FS3_UPGRADE_CODE = 0x7,
    FS3_HW_BOOT_CFG = 0x8,
    FS3_HW_MAIN_CFG = 0x9,
    FS3_PHY_UC_CODE = 0xa,
    FS3_PHY_UC_CONSTS = 0xb,
    FS3_PCIE_PHY_UC_CODE = 0xc,
    FS3_CCIR_INFRA_CODE = 0xd,
    FS3_CCIR_ALGO_CODE = 0xe,
    FS4_BOOT3_CODE = 0xf,
    FS3_IMAGE_INFO = 0x10,
    FS3_FW_BOOT_CFG = 0x11,
    FS3_FW_MAIN_CFG = 0x12,
    FS3_APU_KERNEL = 0x14,
    FS3_ACE_CODE = 0x15,
    FS3_ROM_CODE = 0x18,
    FS3_RESET_INFO = 0x20,
    FS3_DBG_FW_INI = 0x30,
    FS3_DBG_FW_PARAMS = 0x32,
    FS3_FW_ADB = 0x33,
    FS4_GB_FW_CODE = 0x34,
    FS4_TILE_FW_CODE = 0x35,
    FS4_FW_TILE_INI = 0x36,
    FS4_HW_TILE_INI = 0x37,
    FS3_IMAGE_SIGNATURE_256 = 0xa0,
    FS3_PUBLIC_KEYS_2048 = 0xa1,
    FS3_FORBIDDEN_VERSIONS = 0xa2,
    FS3_IMAGE_SIGNATURE_512 = 0xa3,
    FS3_PUBLIC_KEYS_4096 = 0xa4,
    FS3_HMAC_DIGEST = 0xa5,
    FS4_RSA_PUBLIC_KEY = 0xa6,
    FS4_RSA_4096_SIGNATURES = 0xa7,
    FS4_EXCLKSYNC_INFO = 0xb0,
    FS4_MAIN_HASHES_PAGES = 0xb1,
    FS4_MAIN_LOCKED_HASHES_PAGES = 0xb2,
    FS3_MFG_INFO = 0xe0,
    FS3_DEV_INFO = 0xe1,
    FS3_NV_DATA1 = 0xe2,
    FS3_VPD_R0 = 0xe3,
    FS3_NV_DATA2 = 0xe4,
    FS3_FW_NV_LOG = 0xe5,
    FS3_NV_DATA0 = 0xe6, // replaces FS3_NV_DATA1
    FS4_DEV_INFO1 = 0xe7,
    FS4_DEV_INFO2 = 0xe8,
    FS3_CRDUMP_MASK_DATA = 0xe9,
    FS4_FW_INTERNAL_USAGE = 0xea,
    FS4_PROGRAMMABLE_HW_FW1 = 0xeb,
    FS4_PROGRAMMABLE_HW_FW2 = 0xec,
    FS4_DIGITAL_CERT_PTR = 0xed,
    FS4_DIGITAL_CERT_RW = 0xee,
    FS4_LC_INI1_TABLE = 0xef,
    FS4_LC_INI2_TABLE = 0xf0,
    FS4_LC_INI_NV_DATA = 0xf1,
    FS4_CERT_CHAIN_0 = 0xf2,
    FS4_DIGITAL_CACERT_RW = 0xf3,
    FS4_HASHES_TABLE = 0xfa,
    FS4_HW_PTR = 0xfb,
    FS4_TOOLS_AREA = 0xfc,
    FS3_ITOC = 0xfd,
    FS3_DTOC = 0xfe,
    FS3_END = 0xff,
} fs3_section_t;

enum CommandType
{
    CMD_UNKNOWN,
    CMD_BURN,
    CMD_SET_GUIDS,
    CMD_SET_VSD,
    CMD_BURN_BLOCK,
    CMD_QUERY,
    CMD_QUERY_ROM,
    CMD_QUERY_FORCE,
    CMD_VERIFY,
    CMD_READ_WORD,
    CMD_READ_BLOCK,
    CMD_WRITE_WORD,
    CMD_WRITE_WORD_NE,
    CMD_WRITE_BLOCK,
    CMD_WRITE_BLOCK_NE,
    CMD_ERASE_SECT,
    CMD_DUMP_CONF,
    CMD_DUMP_HASH,
    CMD_DUMP_JSON,
    CMD_READ_IMAGE,
    CMD_CFI,
    CMD_CLEAR_SEM,
    CMD_SWRESET,
    CMD_BURN_ROM,
    CMD_REMOVE_ROM,
    CMD_READ_ROM,
    CMD_SET_KEY,
    CMD_HW_ACCESS,
    CMD_CONFIG,
    CMD_DUMP_TRACER_HASH,
    CMD_HW_INFO,
    CMD_SET_MFG_GUIDS,
    CMD_BURN_VPD,
    CMD_SET_SIGNATURE,
    CMD_SET_PUBLIC_KEYS,
    CMD_SET_FORBIDDEN_VERSIONS,
    CMD_SET_HMAC,
    CMD_SET_PUBLIC_4096_RSA_KEY
};

struct GPH
{
    u_int32_t type;
    u_int32_t size;
    u_int32_t param;
    u_int32_t next;
};

#define MAX_SECTION_SIZE 0x400000

#define REBOOT_REQUIRED_STR "To load new FW run reboot machine."
#ifndef MST_UL
#define REBOOT_OR_FWRESET_REQUIRED_STR "To load new FW run mlxfwreset or reboot machine."
#else
#define REBOOT_OR_FWRESET_REQUIRED_STR "To load new FW run mstfwreset or reboot machine."
#endif

void report(const char* format, ...);
void report_callback(f_prog_func_str func_str, const char* format, ...);
void report_err(char err_buff[MAX_ERR_STR_LEN], const char* format, ...);
void report_warn(const char* format, ...);
void report_repair_msg(const char* common_msg);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  BASE CLASSES
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MLXFWOP_API FlintErrMsg
{
public:
    FlintErrMsg() : _err(0), _errCode(0) {}
    ~FlintErrMsg() { err_clear(); }
    const char* err() const { return _err; }
    void err_clear();
    int getErrorCode() { return _errCode; }

protected:
    char* vprint(const char* format, va_list args)
    {
        const int INIT_VAL = 1024;
        int max_str, max_buf = INIT_VAL;
        char* out_buf;

        while (1)
        {
            out_buf = new char[max_buf];
            max_str = max_buf - 1;

            if (vsnprintf(out_buf, max_str, format, args) < max_str)
            {
                return out_buf;
            }
            delete[] out_buf;
            max_buf *= 2;
        }
    }

    bool errmsg(const char* format, ...)
#ifdef __GNUC__
      __attribute__((format(printf, 2, 3)))
#endif
      ;

    bool errmsg(int errorCode, const char* format, ...)
#ifdef __GNUC__
      __attribute__((format(printf, 3, 4)))
#endif
      ;

    // this is abit ugly as there are no checks on the normalFmt string
    bool errmsgAdv(bool showAdv, const char* normalFmt, const char* AdvFmt, ...)
#ifdef __GNUC__
      __attribute__((format(printf, 4, 5)))
#endif
      ;

    int errmsgWCode(int errorCode, const char* format, ...)
#ifdef __GNUC__
      __attribute__((format(printf, 3, 4)))
#endif
      ;

private:
    char* _err;
    int _errCode;
};

////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        CRC16 CALCULATION                           //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
class Crc16
{
public:
    Crc16(bool d = false) : _debug(d) { clear(); }
    u_int16_t get() { return _crc; }
    void clear() { _crc = 0xffff; }
    void operator<<(u_int32_t val) { add(val); }
    void add(u_int32_t val);
    void finish();

private:
    u_int16_t _crc;
    bool _debug;
};

class u_int32_ba
{
public:
    u_int32_ba(u_int32_t i = 0) : _bits(i), _rbits(_bits), _sptr1(0), _eptr(31) {}

    u_int32_ba operator[](u_int32_t idx) { return range((u_int8_t)idx, (u_int8_t)idx); }
    u_int32_ba& operator=(u_int32_t i)
    {
        _rbits = ((i << _sptr1) & mask()) | (_rbits & ~mask());
        return *this;
    }
    u_int32_t* operator&() { return &_bits; }
    operator u_int32_t() { return ((mask() & _rbits) >> _sptr1); }

    u_int32_ba range(u_int8_t eptr, u_int8_t sptr) { return u_int32_ba(*this, eptr, sptr); }

private:
    u_int32_ba(u_int32_ba& other, u_int8_t eptr, u_int8_t sptr) :
        _bits(other._bits), _rbits(other._bits), _sptr1(sptr), _eptr(eptr)
    {
    }

    u_int32_t mask()
    {
        u_int32_t s_msk = (u_int32_t)-1; // start mask
        u_int32_t e_msk = (u_int32_t)-1; // end mask

        s_msk = (s_msk << _sptr1);
        e_msk = (_eptr >= (sizeof(_bits) * 8 - 1)) ? e_msk : ~(e_msk << (_eptr + 1));

        return (s_msk & e_msk);
    };

    u_int32_t _bits;
    u_int32_t& _rbits;

    u_int8_t _sptr1;
    u_int8_t _eptr;
};

//////////////////////////////////////////////////////////////////////
//
//  class Aligner:
//  A utillity class for accessing an addr/size region
//  in a specific alignment.
//  If a 0 alignment is given, infinity (no alignment requirements)
//  is assumed - This is to support single flow for the caller.
//
//////////////////////////////////////////////////////////////////////

class Aligner
{
public:
    Aligner(u_int32_t log2_alignment_size) :
        _curr_addr(0),
        _curr_size(0),
        _log2_alignment_size(log2_alignment_size),
        _alignment_size(1 << log2_alignment_size),
        _alignment_mask(_alignment_size - 1)
    {
        if (_log2_alignment_size == 0)
        {
            _log2_alignment_size = 31;
            _alignment_size = 1 << _log2_alignment_size;
            _alignment_mask = _alignment_size - 1;
        }
    }

    void Init(u_int32_t addr, u_int32_t size)
    {
        _curr_addr = addr;
        _curr_size = size;
    }

    bool GetNextChunk(u_int32_t& chunk_addr, u_int32_t& chunk_size)
    {
        if (_curr_size == 0)
        {
            return false;
        }

        chunk_addr = _curr_addr;

        if ((_curr_addr >> _log2_alignment_size) != ((_curr_addr + _curr_size) >> _log2_alignment_size))
        {
            // Next chunk crosses alignment boundary
            chunk_size = _alignment_size - (_curr_addr & _alignment_mask);
        }
        else
        {
            chunk_size = _curr_size;
        }

        _curr_addr += chunk_size;
        _curr_size -= chunk_size;

        return true;
    }

private:
    u_int32_t _curr_addr;
    u_int32_t _curr_size;
    u_int32_t _log2_alignment_size;
    u_int32_t _alignment_size;
    u_int32_t _alignment_mask;
};

#endif
