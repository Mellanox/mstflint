/*
 *
 * flint.cpp - FLash INTerface
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: flint.cpp,v 1.60 2004/10/31 14:02:51 orenk Exp $
 *
 */

#include "mtcr.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <alloca.h>

#ifdef __WIN__
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#define  O_BINARY 0
#endif

#ifndef DEV_MST_EXAMPLE1
#define DEV_MST_EXAMPLE1 "/dev/mst/mt23108_pci_cr0"
#endif

#ifndef DEV_MST_EXAMPLE2
#define DEV_MST_EXAMPLE2 "/dev/mst/mt23108_pciconf0"
#endif

#ifndef FLINT_NAME
#ifdef __GNUC__
#define FLINT_NAME "%1$s"
#else
#define FLINT_NAME "./flint"
#endif
#endif

namespace std {}; using namespace std;


char* _versionID = "VERSION_ID_HERE";
char* _cvsID     = "$Revision: 1.60 $";


//
// Only for architectures which can't do swab by themselves
//
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


//
// MAC compatibility stuff
//
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

//
// Windows
//
#elif defined(__WIN__)

#define __swab64(x)  ((u_int64_t)( \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00000000000000ffUL) << 56) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x000000000000ff00UL) << 40) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x0000000000ff0000UL) << 24) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00000000ff000000UL) <<  8) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x000000ff00000000UL) >>  8) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x0000ff0000000000UL) >> 24) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0x00ff000000000000UL) >> 40) | \
    (u_int64_t)(((u_int64_t)(x) & (u_int64_t)0xff00000000000000UL) >> 56) ))
#define __swab32(x)  ((u_int32_t)( \
    (((u_int32_t)(x) & (u_int32_t)0x000000ffUL) << 24) | \
    (((u_int32_t)(x) & (u_int32_t)0x0000ff00UL) <<  8) | \
    (((u_int32_t)(x) & (u_int32_t)0x00ff0000UL) >>  8) | \
    (((u_int32_t)(x) & (u_int32_t)0xff000000UL) >> 24) ))
#define __swab16(x) ((u_int16_t)( \
    (((u_int16_t)(x) & (u_int16_t)0x00ffU) << 8) | \
    (((u_int16_t)(x) & (u_int16_t)0xff00U) >> 8) ))


#define __be64_to_cpu(x) __swab64(x)
#define __be32_to_cpu(x) __swab32(x)
#define __be16_to_cpu(x) __swab16(x)
#define __le64_to_cpu(x) (x)
#define __le32_to_cpu(x) (x)
#define __le16_to_cpu(x) (x)
#define __cpu_to_be64(x) __swab64(x)
#define __cpu_to_be32(x) __swab32(x)
#define __cpu_to_be16(x) __swab16(x)
#define __cpu_to_le64(x) (x)
#define __cpu_to_le32(x) (x)
#define __cpu_to_le16(x) (x)

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __PDP_ENDIAN    3412
#define __BYTE_ORDER    __LITTLE_ENDIAN

_inline void usleep( unsigned long x) { Sleep((x + 999) / 1000); }

//
// Unix
//
#else

#include <endian.h>

#define __be64_to_cpu(x) ___my_swab64(x)

#ifndef __be32_to_cpu
#define __be32_to_cpu(x) ___my_swab32(x)
#endif
#define __be16_to_cpu(x) ___my_swab16(x)
#define __cpu_to_be64(x) ___my_swab64(x)
#ifndef __cpu_to_be32
#define __cpu_to_be32(x) ___my_swab32(x)
#endif
#define __cpu_to_be16(x) ___my_swab16(x)
#define __le64_to_cpu(x) (x)
#define __le32_to_cpu(x) (x)
#define __le16_to_cpu(x) (x)
#define __cpu_to_le64(x) (x)
#define __cpu_to_le32(x) (x)
#define __cpu_to_le16(x) (x)

#endif


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                     Miscellaneous global stuff                     //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
#if defined(__ia64__) || defined(__x86_64)
#define GUID_FORMAT "%016lx"
#else
#define GUID_FORMAT "%016llx"
#endif
#define TOCPU1(s) s = __be32_to_cpu(s)
#define TOCPU(s) do {                                              \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++,p++) \
        *p = __be32_to_cpu(*p);                                    \
    } while(0)
#define TOCPUn(s, n) do {                                          \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<(n); ii++,p++)                         \
        *p = __be32_to_cpu(*p);                                    \
    } while(0)
#define TOCPUBY(s) do {                                            \
    u_int32_t *p = (u_int32_t *)(&s);                              \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++,p++) \
        *p = __be32_to_cpu(*p);                                    \
    } while(0)
#define TOCPUBY64(s) do {                                          \
    u_int64_t *p = (u_int64_t *)(&s);                              \
    for (u_int64_t ii=0; ii<sizeof(s)/sizeof(u_int64_t); ii++,p++) \
        *p = __be64_to_cpu(*p);                                    \
    } while(0)
#define SWAP32(s) do {                                             \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++,p++) \
        *p = __swab32(*p);                                         \
    } while(0)
#define SWAPBY32(s) do {                                           \
    u_int32_t *p = (u_int32_t *)(&s);                              \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++,p++) \
        *p = __swab32(*p);                                         \
    } while(0)
#define SWAPBY64(s) do {                                           \
    u_int64_t *p = (u_int64_t *)(&s);                              \
    for (u_int64_t ii=0; ii<sizeof(s)/sizeof(u_int64_t); ii++,p++) \
        *p = __swab64(*p);                                         \
    } while(0)
#define CRC(c, s) do {                                             \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++)     \
        c << *p++;                                                 \
    } while(0)
#define CRCn(c, s, n) do {                                         \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<(n); ii++)                             \
        c << *p++;                                                 \
    } while(0)
#define CRCBY(c, s) do {                                           \
    u_int32_t *p = (u_int32_t *)(&s);                              \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t); ii++)     \
        c << *p++;                                                 \
    } while(0)
#define CRC1(c, s) do {                                            \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t) - 1; ii++) \
        c << *p++;                                                 \
    } while(0)
#define CRC1n(c, s, n) do {                                        \
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (u_int32_t ii=0; ii<(n) - 1; ii++)                         \
        c << *p++;                                                 \
    } while(0)
#define CRC1BY(c, s) do {                                          \
    u_int32_t *p = (u_int32_t *)(&s);                              \
    for (u_int32_t ii=0; ii<sizeof(s)/sizeof(u_int32_t) - 1; ii++) \
        c << *p++;                                                 \
    } while(0)
#define CHECKB2(f,b,o,n,p) do { if (!checkBoot2(f,b,o,n,p)) return false; } while (0)
#define CHECKGN(f,b,o,n,p) do { if (!checkGen(f,b,o,n,p)) return false; } while (0)
#define CHECKLS(f,o,p) do { if (!checkList(f,o,p)) return false; } while(0)
#define READ4(f,o,d,p) do { if (!f.read(o,d)) {  \
    printf("%s - read error (%s)\n", p, f._err); \
    return false; }} while (0)
#define READBUF(f,o,d,l,p) do { if (!f.read(o,d,l)) { \
    printf("%s - read error (%s)\n", p, f._err);      \
    return false; }} while (0)

#if  1

#define MWRITE4(offs,val) do { \
    if (mwrite4(_mf, offs, val) != 4) return false; } while (0)
#define MREAD4(offs,val) do { \
   if (mread4(_mf, offs, val) != 4) return false; } while (0)

#else

#define MWRITE4(offs,val) do { \
    printf("%08x <- %08x\n", (u_int32_t)offs, (u_int32_t)val); \
    if (mwrite4(_mf, offs, val) != 4) return false; } while (0)
#define MREAD4(offs,val) do { \
    if (mread4(_mf, offs, val) != 4) return false; \
     printf("%08x -> %08x\n", (u_int32_t)offs, (u_int32_t)(*(val))); \
    } while (0)

#endif

enum { SIGNATURE=0x5a445a44};
struct PS {
    u_int32_t fi_addr;
    u_int32_t fi_size;
    u_int32_t signature;
    u_int32_t fw_reserved[5];
    u_int32_t vsd[56];
    u_int32_t branch_to;
    u_int32_t crc016;
};
enum { H_FIRST=1, H_DDR=1, H_CNF=2, H_JMP=3, H_EMT=4, H_ROM=5, H_GUID=6,
       H_BOARD_ID=7, H_LAST=7 };
struct GPH {
    u_int32_t type;
    u_int32_t size;
    u_int32_t param;
    u_int32_t next;
};
const u_int32_t BOARD_ID_BSN_LEN=64;
const u_int32_t BOARD_ID_BID_LEN=32;
const u_int32_t BOARD_ID_PID=7;
struct BOARD_ID {
    char      bsn[BOARD_ID_BSN_LEN];
    char      bid[BOARD_ID_BID_LEN];
};

int  const VSD_LEN  = 224;
int  const VSD_LAST = 16;
int  const VSD_OFFS = VSD_LEN-VSD_LAST;

//
// TODO: Remove the below globals to class members.
//
bool _print_crc = false;
bool _silent = false;
bool _assume_yes = false;
bool _image_is_full;
bool _no_erase = false;
bool _no_burn = false;

bool _unlock_bypass = false;

bool _byte_write = false;

void report(const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 1, 2)))
#endif
    ;
void report(const char *format, ...)
{
    va_list  args;

    if (!_silent)
    {
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
} // report


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
    Crc16(bool d = false) : _debug(d) { clear();       }
    u_int16_t      get()              { return _crc;   }
    void           clear()            { _crc = 0xffff; }
    void           operator<<(u_int32_t val) { add(val); }
    void           add(u_int32_t val);
    void           finish();
private:
    u_int16_t      _crc;
    bool           _debug;
};

////////////////////////////////////////////////////////////////////////
void Crc16::add(u_int32_t o)
{
    if (_debug)
        printf("Crc16::add(%08x)\n", o);
    for (int i=0; i<32; i++)
    {
        if (_crc & 0x8000)
            _crc = (u_int16_t) ((((_crc<<1) | (o>>31)) ^  0x100b) & 0xffff);
        else
            _crc= (u_int16_t) (((_crc<<1) | (o>>31)) & 0xffff);
        o = (o<<1) & 0xffffffff;
    }
} // Crc16::add


////////////////////////////////////////////////////////////////////////
void Crc16::finish()
{
    for (int i=0; i<16; i++)
    {
        if (_crc & 0x8000)
            _crc=((_crc<<1)  ^  0x100b) & 0xffff;
        else
            _crc=(_crc<<1) & 0xffff;
    }

    // Revert 16 low bits
    _crc = _crc ^ 0xffff;

} // Crc16::finish


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        FLASH ACCESS                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
//#define FUJITSU_BYTE_MODE

// Common base class for Flash and for FImage
class FBase
{
public:
    FBase() :_err(0)         {}

    virtual bool open(const char *)                        = 0;
    virtual void close()                                   = 0;
    virtual bool read(u_int32_t addr, u_int32_t *data)     = 0;
    virtual bool read(u_int32_t addr, void *data, int len,
                      bool verbose=false)                  = 0;

    virtual u_int32_t get_sector_size()                    = 0;

    char *_err;

    enum { MAX_FLASH = 4*1048576 };
protected:
    char _msg[1024];
};

// Flash image (RO)
class FImage : public FBase
{
public:
    FImage() : _buf(0) {}
    virtual ~FImage() { close(); }

    u_int32_t    *getBuf()      { return _buf; }
    u_int32_t    getBufLength() { return _len; }
    virtual bool open(const char *fname);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t *data);
    virtual bool read(u_int32_t addr, void *data, int len, bool verbose=false);

    virtual u_int32_t get_sector_size();
    
private:
    u_int32_t *_buf;
    u_int32_t _len;
};

// Flash access (R/W)
class Flash : public FBase
{
public:
    Flash();
    virtual ~Flash()  { close(); };

    enum {
	CS_INTEL = 0x01,
	CS_AMD   = 0x02,
    };


    u_int32_t  curr_sector;

    virtual bool open(const char *device);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t *data);
    virtual bool read(u_int32_t addr, void *data, int len, bool verbose=false);
    
    virtual u_int32_t get_sector_size() { return _cfi.erase_block[0].sector_size;}
    

    bool         query_cfi();
    bool         unlock_bypass(bool unlock);
    bool         erase_sector(u_int32_t addr);
    bool         write(u_int32_t addr, u_int32_t data);
    bool         write(u_int32_t addr, void *data, int cnt,
                       bool noerase = false, bool noverify = false);
    bool         write_image(u_int32_t addr, void *data, int cnt,
                             bool report=false);
    bool         lazy_FailSafe_burn(void *data, int cnt, bool need_report);
    bool         FailSafe_burn(void *data, int cnt, bool need_report);
    bool         repair(const int from, const int to, bool need_report);
    bool         FailSafe_burn_internal(void *data, int cnt, bool need_report);

private:
    mfile        *_mf;
    u_int32_t    _curr_bank;
    u_int32_t    _dir;
    u_int32_t    _pol;
    u_int32_t    _mod;
    u_int32_t    _data;
    bool         _use_scr;

    bool         set_bank(u_int32_t bank);
    bool         write_internal(u_int32_t addr, u_int8_t data);

    enum FlashCmds { IDLE=0, READ4=(1<<29), WRITE1=(2<<29) };
    enum { TRANS = 4096 };
    enum { BANK_SHIFT = 19,     BANK_MASK = 0xfff80000 };
    enum { FLASH    = 0xf01a4, ADDR_MSK=0x7ffffUL, CMD_MASK=0xe0000000UL };
    u_int32_t USE_SCR;
    enum { LEN_MSK = 0x3ff, LEN_SHIFT = 19};
    enum { CPUMODE  = 0xf0150, CPUMODE_MSK=0xc0000000UL, CPUMODE_SHIFT=30 };
    enum { SEMAP63    = 0xf03fc, GPIO_DIR_L = 0xf008c, GPIO_POL_L = 0xf0094,
           GPIO_MOD_L = 0xf009c, GPIO_DAT_L = 0xf0084,
           GPIO_DATACLEAR_L = 0xf00d4, GPIO_DATASET_L = 0xf00dc };

    // FLASH constants
    enum { FLASH_CMD_CNT  = 5000,    // Number of reads till flash cmd is zeroed
           ERASE_DELAY    = 200000,  // Delay between reads when wating for sector erase
           ERASE_CNT      = 80,      // Maximal number of reads when wating for sector erase
           READ_CNT_FAST  = 5000,    // Number of fast reads after write byte
           READ_CNT_SLOW  = 50,      // Number of slow reads after write byte
           READ_DELAY     = 100000,  // Delay between slow reads after write byte
           WR_REPORT_FAST = 256,     // Report frequency when write (fast interfaces)
           WR_REPORT_SLOW = 4,       // Report frequency when write (slow interfaces)
           RD_REPORT_FAST = 4096,    // Report frequency when read (fast interfaces)
           RD_REPORT_SLOW = 64,      // Report frequency when read (slow interfaces)
           GPIO_SEM_TRIES = 10240,   // Number of tries to obtain a GPIO sem.
	   MAX_WRITE_BUFFER_SIZE = 32// Max buffer size for buffer write devices
    };


    class CmdSet {
    public:
	CmdSet                     (Flash& f) : _f(f) {}
        virtual ~CmdSet            ()                 {}

        virtual bool write         (u_int32_t addr, 
				    void*     data, 
				    int       cnt,
				    bool      noerase  = false, 
				    bool      noverify = false)  = 0;

	//virtual bool unlock_bypass (bool      unlock)            = 0;
	virtual bool erase_sector  (u_int32_t addr)              = 0;

	virtual bool reset          ()                           = 0;

    protected:

	Flash& _f;
    };



    //
    // AMD's Am29LV033C command set
    //
    class CmdSet0002 : public CmdSet {
    public:
	CmdSet0002                 (Flash& f  ) : CmdSet(f) {}

        virtual bool write         (u_int32_t addr, 
				    void*     data, 
				    int       cnt,
				    bool      noerase  = false, 
				    bool      noverify = false);

	virtual bool erase_sector  (u_int32_t addr);
	virtual bool reset         ();
    private:

	//bool         unlock_bypass (bool      unlock);
    };

    //
    // Intel's 28F320J3 x8 command set, using buffer writes
    //
    class CmdSet0001 : public CmdSet {
    public:
	enum FlashCommand { 
	    FC_ReadID      = 0x90,
	    FC_Read        = 0xFF,
	    FC_Erase       = 0x20,
	    FC_Confirm     = 0xD0,
	    FC_Clear       = 0x50,
	    FC_Write       = 0x40,
	    FC_LoadPB      = 0xE0,
	    FC_PBWrite     = 0x0C,
	    FC_Status      = 0x70,
	    FC_Suspend     = 0xB0,
	    FC_Resume      = 0xD0,
	    FC_ReadESR     = 0x71,
	    FC_QueryCFI    = 0x98,
	    FC_SCSErase    = 0x28,
	    FC_SCSWrite    = 0xE8
	};

	enum FlashStatus { 
	    FS_Ready       = 0x80,
	    FS_Suspended   = 0x40,
	    FS_Error       = 0x3E,
	    FS_BlockError  = 0x3F
	};

	CmdSet0001                 (Flash& f) : CmdSet(f) {}

        virtual bool write         (u_int32_t addr, 
				    void*     data, 
				    int       cnt,
				    bool      noerase  = false, 
				    bool      noverify = false);

	virtual bool erase_sector  (u_int32_t addr);
	virtual bool reset         ();
    };


    //
    // Intel's 28F320J3 x8 command set, using byte write (For debug only).
    //
    class CmdSet0001WriteByte : public CmdSet0001 {
    public:
	CmdSet0001WriteByte        (Flash& f) : CmdSet0001(f) {}

        virtual bool write         (u_int32_t addr, 
				    void*     data, 
				    int       cnt,
				    bool      noerase  = false, 
				    bool      noverify = false);

    };


    //		
    // This structure holds all CFI query information as defined
    // in the JEDEC standard. All information up to 
    // primary_extended_query is standard among all amnufactures
    // with CFI enabled devices.
    //

    struct cfi_query {
	u_int8_t  manuf_id;
	u_int8_t  device_id;

	char      query_string[4];		// Should be 'QRY' 
	u_int16_t oem_command_set;              // Command set 
	u_int16_t primary_table_address;        // Addy of entended table 
	u_int16_t alt_command_set;              // Alt table 
	u_int16_t alt_table_address;            // Alt table addy 
	float     vcc_min;                      // Vcc minimum 
	float     vcc_max;			// Vcc maximum 
	float     vpp_min;			// Vpp minimum, if supported 
	float     vpp_max;			// Vpp maximum, if supported 
	int       timeout_single_write;         // Time of single write 
	int       timeout_buffer_write;	        // Time of buffer write 
	int       timeout_block_erase;	        // Time of sector erase 
	int       timeout_chip_erase;		// Time of chip erase 
	int       max_timeout_single_write;     // Max time of single write 
	int       max_timeout_buffer_write; 	// Max time of buffer write 
	int       max_timeout_block_erase;	// Max time of sector erase 
	int       max_timeout_chip_erase; 	// Max time of chip erase 
	long      device_size;		        // Device size in bytes 
	u_int16_t interface_description;	// Interface description 
	int       max_multi_byte_write;	        // Time of multi-byte write 
	int       num_erase_blocks;		// Number of sector defs. 
	struct {
	    unsigned long sector_size;	        // Byte size of sector 
	    int           num_sectors;		// Num sectors of this size 
	    u_int32_t     sector_mask;          // Sector mask 
	} erase_block[8];		        // Max of 256, but 8 is good 

	// AMD SPECIFIC
	char primary_extended_query[4];	        // Vendor specific info here 
	u_int16_t major_version;		// Major code version 
	u_int16_t minor_version;		// Minor code version 
	u_int8_t  sensitive_unlock;		// Is byte sensitive unlock? 
	u_int8_t  erase_suspend;		// Capable of erase suspend? 
	u_int8_t  sector_protect;		// Can Sector protect? 
	u_int8_t  sector_temp_unprotect;	// Can we temporarily unprotect? 
	u_int8_t  protect_scheme;		// Scheme of unprotection 
	u_int8_t  is_simultaneous;		// Is a smulataneous part? 
	u_int8_t  is_burst;			// Is a burst mode part? 
	u_int8_t  is_page;			// Is a page mode part? 
    };

    u_int16_t extract_word   ( const u_int8_t* pb, int data_width)  {
	assert (data_width == 1 || data_width == 2);
	u_int16_t ret = *pb | ((*(pb + data_width)) << 8);
	// !!! CHECK ENDIANES !!!
        ret = __le16_to_cpu(ret);
	return ret;
    }

    bool get_cfi        (       cfi_query *query);
    bool print_cfi_info ( const cfi_query *q );

    cfi_query   _cfi;
    CmdSet*     _cmd_set;

};

////////////////////////////////////////////////////////////////////////
bool FImage::open(const char *fname)
{
    struct stat        stat_buf;
    int                r_cnt;

    int fd = ::open(fname, O_RDONLY | O_BINARY);
    if (fd < 0)
    {
        sprintf(_msg, "Can't open file \"%s\" - %s\n", fname,
                strerror(errno));
        _err = &_msg[0];
        return false;
    }
    if (fstat(fd, &stat_buf) < 0)
    {
        sprintf(_msg, "Can't stat file \"%s\" - %s\n", fname,
                strerror(errno));
        _err = &_msg[0];
        return false;
    }
    //printf("%ld / 0x%lx\n", stat_buf.st_size, stat_buf.st_size);
    if (stat_buf.st_size & 0x3)
    {
        _err = "Image size should be 4-bytes aligned.";
        return false;
    }

    _buf = new u_int32_t[stat_buf.st_size/4];
    if ((r_cnt = ::read(fd, _buf, stat_buf.st_size)) != stat_buf.st_size)
    {
        if (r_cnt < 0)
            sprintf(_msg, "Read error on file \"%s\" - %s\n",
                    fname, strerror(errno));
        else
            sprintf(_msg, "Read error on file \"%s\" - read only %d bytes (from %ld)\n",
                    fname, r_cnt, (unsigned long)stat_buf.st_size);
        _err = &_msg[0];
        return false;
    }

    _len = stat_buf.st_size;
    ::close(fd);
    return true;
} // FImage::open

////////////////////////////////////////////////////////////////////////
void FImage::close()
{
    delete [] _buf;
    _buf = 0;
} // FImage::close

////////////////////////////////////////////////////////////////////////
bool FImage::read(u_int32_t addr, u_int32_t *data)
{
    if (addr & 0x3)
    {
        _err = "Address should be 4-bytes aligned.";
        return false;
    }
    if (!_buf)
    {
        _err = "Not opened";
        return false;
    }
    if (addr > _len-4)
    {
        sprintf(_msg, "Address (0x%x) is out of image limits\n", addr);
        _err = &_msg[0];
        return false;
    }
    *data = _buf[addr/4];
    return true;
} // FImage::read

////////////////////////////////////////////////////////////////////////
bool FImage::read(u_int32_t addr, void *data, int len, bool)
{
    if (addr & 0x3)
    {
        _err = "Address should be 4-bytes aligned.";
        return false;
    }
    if (len & 0x3)
    {
        _err = "Length should be 4-bytes aligned.";
        return false;
    }
    if (!_buf)
    {
        _err = "Not opened";
        return false;
    }

    u_int32_t *p = (u_int32_t *)data;
    for (int i=0; i<len/4; i++)
    {
        if (!read(addr, p++))
            return false;
        addr += 4;
    }
    return true;
} // FImage::read

////////////////////////////////////////////////////////////////////////
u_int32_t FImage::get_sector_size() 
{	
    u_int32_t log2_sector_sz_ptr;
    u_int32_t log2_sector_sz;
    u_int32_t signature;

    read(0x24, &signature);
    TOCPU1(signature);
    if (signature == SIGNATURE)
    {
	// full image:
	read(0x14, &log2_sector_sz_ptr);
	TOCPU1(log2_sector_sz_ptr);
	log2_sector_sz_ptr &= 0xffff;

	read(0x30 + log2_sector_sz_ptr, &log2_sector_sz);
	TOCPU1(log2_sector_sz);
	log2_sector_sz &= 0xffff;

	return (1 << log2_sector_sz);

    } else {
	return 0;
    }
}


////////////////////////////////////////////////////////////////////////
Flash::Flash() : curr_sector(0xffffffff), _mf(0), _curr_bank(0xffffffff), _cmd_set(0)
{
    char *use_scr_p = getenv("FLINT_USE_SCRATCHPAD");

    if (use_scr_p)
    {
        char *endp;

        USE_SCR = strtoul(use_scr_p, &endp, 0);
        if (*endp)
        {
            printf("Invalid FLINT_USE_SCRATCHPAD syntax (%s). Must be integer.",
                   use_scr_p);
            _use_scr = false;
        }
        else
        {
            printf("Burning via SCRATCHPAD interface by addr 0x%x\n", USE_SCR);
            _use_scr = true;
        }
    }
    else
        _use_scr = false;
} // Flash::Flash


////////////////////////////////////////////////////////////////////////
bool Flash::open(const char *device)
{
    // Open device
    _mf = mopen(device);
    if (!_mf)
    {
        _err = strerror(errno);
        return false;
    }
    _curr_bank = 0xffffffff;

    // Obtain GPIO Semaphore
    u_int32_t cnt=0;
    u_int32_t word;
    do {
        if (++cnt > GPIO_SEM_TRIES)
        {
            _err = "cannot obtain GPIO semaphore (63)";
            return false;
        }
        MREAD4(SEMAP63, &word);
    } while (word);

    // Save old values
    MREAD4(GPIO_DIR_L, &_dir);
    MREAD4(GPIO_POL_L, &_pol);
    MREAD4(GPIO_MOD_L, &_mod);
    MREAD4(GPIO_DAT_L, &_data);

    // Set Direction=1, Polarity=0, Mode=0 for 3 GPIO lower bits
    u_int32_t dir = _dir | 0x70;
    u_int32_t pol = _pol & ~0x70;
    u_int32_t mod = _mod & ~0x70;
    MWRITE4(GPIO_DIR_L, dir);
    MWRITE4(GPIO_POL_L, pol);
    MWRITE4(GPIO_MOD_L, mod);

    // Set CPUMODE
    MREAD4(CPUMODE, &word);
    word &= ~CPUMODE_MSK;
    word |= 1 << CPUMODE_SHIFT;
    MWRITE4(CPUMODE, word);

    //
    // CFI Query
    //
    if (!get_cfi(&_cfi))
	return false;

    //
    // Some sanity checks:
    //

    if (_cfi.max_multi_byte_write > MAX_WRITE_BUFFER_SIZE) {
	_err = "Device write buffer is larger than the supported size.";
	return false;
    }

    if (_cfi.num_erase_blocks > 1) {
	_err = "Device has more than one sector size - not supported by this tool";
	return false;
    }

    //
    // Sellect CmdSet
    //

    switch (_cfi.oem_command_set) {
    case CS_INTEL:
	if (_byte_write || _cfi.max_multi_byte_write == 0)
	    _cmd_set = new CmdSet0001WriteByte(*this);
	else 
	    _cmd_set = new CmdSet0001(*this);
	break;
    case CS_AMD: 
	_cmd_set = new CmdSet0002(*this);
	break;

    default:
	_err = "Unknown CFI command set";
	return false;
    }

    // Reset flash
    return _cmd_set->reset();

} // Flash::open

////////////////////////////////////////////////////////////////////////
void Flash::close()
{
    if (!_mf)
        return;

    delete _cmd_set;

    if (_unlock_bypass) {
	unlock_bypass(false);
    }

    // Restore origin values
    mwrite4(_mf, GPIO_DIR_L, _dir);
    mwrite4(_mf, GPIO_POL_L, _pol);
    mwrite4(_mf, GPIO_MOD_L, _mod);
    mwrite4(_mf, GPIO_DAT_L, _data);

    // Free GPIO Semaphore
    mwrite4(_mf, SEMAP63, 0);

    mclose(_mf);
    _mf = 0;
    _curr_bank = 0xffffffff;

} // Flash::close

////////////////////////////////////////////////////////////////////////
bool Flash::set_bank(u_int32_t bank)
{
    if (!_mf)
    {
        _err = "Not opened";
        return false;
    }

    //printf("\n*** Flash::set_bank(0x%lx) : 0x%lx\n", bank, (bank >> 19) & 0x07);
    MWRITE4(GPIO_DATACLEAR_L, 0x70);
    MWRITE4(GPIO_DATASET_L, (bank >> (BANK_SHIFT-4)) & 0x70);
    return true;
} // Flash::set_bank

////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, u_int32_t *data)
{
    if (!_mf)
    {
        _err = "Not opened";
        return false;
    }

    u_int32_t cmd;
    if (addr & 0x3)
    {
        _err = "Address should be 4-bytes aligned.";
        return false;
    }

    u_int32_t bank = addr & 0xfff80000;
    if (bank != _curr_bank)
    {
        _curr_bank = bank;
        if (!set_bank(bank))
            return false;
    }

    MWRITE4(FLASH, READ4 | (addr & ADDR_MSK));
    u_int32_t cnt = 0;
    do
    {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT)
        {
            _err = "Flash gateway timeout: CMD doesn't become zero";
            return false;
        }

        MREAD4(FLASH, &cmd);

    } while(cmd & CMD_MASK);
    MREAD4(FLASH+4, &cmd);
    cmd = __be32_to_cpu(cmd);
    memcpy(data, &cmd, sizeof(u_int32_t));

    return true;
} // Flash::read

////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, void *data, int len, bool verbose)
{
    u_int32_t  perc = 0xffffffff;

    if (addr & 0x3)
    {
        _err = "Address should be 4-bytes aligned.";
        return false;
    }
    if (len & 0x3)
    {
        _err = "Length should be 4-bytes aligned.";
        return false;
    }

    // Report
    if (verbose)
    {
        printf("000%%");
        fflush(stdout);
    }

    u_int32_t *p = (u_int32_t *)data;
    for (int i=0; i<len/4; i++)
    {
        if (!read(addr, p++))
            return false;
        addr += 4;

        // Report
        if (verbose)
        {
            u_int32_t new_perc = (i * 100) / len;
            if (new_perc != perc)
            {
                printf("\b\b\b\b%03d%%", new_perc);
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    // Report
    if (verbose)
    {
        printf("\b\b\b\b100%%");
        fflush(stdout);
    }

    return true;
} // Flash::read

////////////////////////////////////////////////////////////////////////
bool Flash::write_internal(u_int32_t addr, u_int8_t data)
{
    u_int32_t    cmd;
    int          cnt = 0;

    MWRITE4(FLASH+4, data << 24);
    MWRITE4(FLASH, WRITE1 | (addr & ADDR_MSK));
    do
    {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT)
        {
            _err = "Flash gateway timeout: CMD doesn't become zero";
            return false;
        }

        MREAD4(FLASH, &cmd);

    } while(cmd & CMD_MASK);
    return true;
} // Flash::write_internal


////////////////////////////////////////////////////////////////////////
bool Flash::unlock_bypass(bool unlock) {

     if (unlock) {
	// unlock bypass

	if (!write_internal(0x555, 0xaa))
	    return false;
	if (!write_internal(0x2aa, 0x55))
	    return false;
	if (!write_internal(0x555, 0x20))
	    return false; 
    } else {
	// unlock reset
	if (!write_internal(0x555, 0x90))
	    return false;
	if (!write_internal(0x2aa, 0x00))
	    return false; 
    }
    return true;
}
////////////////////////////////////////////////////////////////////////
bool Flash::query_cfi() {    
    return print_cfi_info(&_cfi); 
}

////////////////////////////////////////////////////////////////////////

//
// AMD SOURCE
//

//*******************************************************************
// flash_get_cfi() is the main CFI workhorse function.  Due to it's  
// complexity and size it need only be called once upon              
// initializing the flash system.  Once it is called, all operations 
// are performed by looking at the cfi_query structure.                
// All possible care was made to make this algorithm as efficient as 
// possible.  90% of all operations are memory reads, and all        
// calculations are done using bit-shifts when possible              
//*******************************************************************


bool Flash::get_cfi(struct cfi_query *query)
{

    enum {
	TOTAL_QUERY_SIZE    = 1024,
	EXTENDED_QUERY_SIZE =   12 
    };

    u_int8_t fwp[TOTAL_QUERY_SIZE]; // flash window 

    int volts=0, milli=0, temp=0, i=0;
    int offset=0;

    u_int32_t query_base = 0x10;

    // Initial house-cleaning 
    memset(fwp, 0xff, TOTAL_QUERY_SIZE);

    for(i=0; i < 8; i++) {
	query->erase_block[i].sector_size = 0;
	query->erase_block[i].num_sectors = 0;
    }	query->erase_block[i].sector_mask = 0;

    // reset
    if (!write_internal(0x55, 0xff))
	return false;
      
     // CFI QUERY 
    if (!write_internal(0x55, 0x98))
	return false;

    char query_str_x8[4];
    char query_str_x16asx8[4];

    if (!read(0x10, query_str_x8, 0x4))
	return false;

    if (!read(0x20, query_str_x16asx8, 0x4))
	return false;

    query_str_x8[3]       = '\0';
    query_str_x16asx8[3]  = '\0';

    if        ( strncmp( query_str_x8 ,      "QRY" ,3 ) == 0) { 
	// x8 CFI flash (AMD)
	query_base = 1;
    } else if ( strncmp( query_str_x16asx8 , "QQR" ,3 ) == 0) {
	// x16 CFI flash worqing in x8 mode (Intel)
	query_base = 2;
    } else {
    
	printf(" Received CFI query from addr 0x10: [%s]\n", query_str_x8 );
	printf(" Received CFI query from addr 0x20: [%s]\n", query_str_x16asx8);
 
	_err = "Failed CFI query";
	return false;
    } 

    if (!read(0x0, fwp, 0x4)) // Dev ID
	return false;

    if (!read(query_base * 0x10, fwp + query_base * 0x10, query_base * 0x20))
	return false;

    query->manuf_id              = fwp[query_base * 0];
    query->device_id             = fwp[query_base * 1];

    query->query_string[0]       = fwp[query_base * 0x10];
    query->query_string[1]       = fwp[query_base * 0x11];
    query->query_string[2]       = fwp[query_base * 0x12];
    query->query_string[3]       = '\0';

    query->oem_command_set       = extract_word(fwp + query_base * 0x13, query_base);
    query->primary_table_address = extract_word(fwp + query_base * 0x15, query_base); // Important one! 
    query->alt_command_set       = extract_word(fwp + query_base * 0x17, query_base);
    query->alt_table_address     = extract_word(fwp + query_base * 0x19, query_base);
    
    // We will do some bit translation to give the following values
    // numerical meaning in terms of C 'float' numbers 
    
    volts = ((fwp[query_base * 0x1B] & 0xF0) >> 4);
    milli = ( fwp[query_base * 0x1B] & 0x0F);
    query->vcc_min = (float) (volts + ((float)milli/10));
    
    volts = ((fwp[query_base * 0x1C] & 0xF0) >> 4);
    milli = ( fwp[query_base * 0x1C] & 0x0F);
    query->vcc_max = (float) (volts + ((float)milli/10));
    
    volts = ((fwp[query_base * 0x1D] & 0xF0) >> 4);
    milli = ( fwp[query_base * 0x1D] & 0x0F);
    query->vpp_min = (float) (volts + ((float)milli/10));
    
    volts = ((fwp[query_base * 0x1E] & 0xF0) >> 4);
    milli = ( fwp[query_base * 0x1E] & 0x0F);
    query->vpp_max = (float) (volts + ((float)milli/10));
    
    // Let's not drag in the libm library to calculate powers
    // for something as simple as 2^(power)
    // Use a bit shift instead - it's faster 

    temp = fwp[query_base * 0x1F];
    query->timeout_single_write = (1 << temp);
    
    temp = fwp[query_base * 0x20];
    if (temp != 0x00)
	query->timeout_buffer_write = (1 << temp);
    else
	query->timeout_buffer_write = 0x00;
    
    temp = 0;
    temp = fwp[query_base * 0x21];
    query->timeout_block_erase = (1 << temp);
    
    temp = fwp[query_base * 0x22];
    if (temp != 0x00)
	query->timeout_chip_erase = (1 << temp);
    else
	query->timeout_chip_erase = 0x00;
    
    temp = fwp[query_base * 0x23];
    query->max_timeout_single_write = (1 << temp) *
	query->timeout_single_write;
    
    temp = fwp[query_base * 0x24];
    if (temp != 0x00)
	query->max_timeout_buffer_write = (1 << temp) *
	query->timeout_buffer_write;
    else
	query->max_timeout_buffer_write = 0x00;
    
    temp = fwp[query_base * 0x25];
    query->max_timeout_block_erase = (1 << temp) *
	query->timeout_block_erase;
    
    temp = fwp[query_base * 0x26];
    if (temp != 0x00)
	query->max_timeout_chip_erase = (1 << temp) *
	query->timeout_chip_erase;
    else
	query->max_timeout_chip_erase = 0x00;
    
    temp = fwp[query_base * 0x27];
    query->device_size = (long) (((long)1) << temp);
    
    query->interface_description = extract_word(fwp + query_base * 0x28, query_base);
    
    temp = fwp[query_base * 0x2A];
    if (temp != 0x00)
	query->max_multi_byte_write = (1 << temp);
    else
	query->max_multi_byte_write = 0;
    
    query->num_erase_blocks = fwp[query_base * 0x2C];

    if (!read(query_base * 0x2C, fwp + query_base * 0x2C ,query_base * 4 * (query->num_erase_blocks + 1))) 
	return false;

    for(i=0; i < query->num_erase_blocks; i++) {
	query->erase_block[i].num_sectors = extract_word(fwp + query_base * (0x2D+(4*i)), query_base);
	query->erase_block[i].num_sectors++;
	
	query->erase_block[i].sector_size = (long) 256 *
	    ( (long)256 * fwp[(query_base * (0x30+(4*i)))] +
	      fwp[(query_base * (0x2F+(4*i)))] );

	query->erase_block[i].sector_mask = ~(query->erase_block[i].sector_size - 1);
    }

    // Store primary table offset in variable for clarity 
    offset = query->primary_table_address;

    if ((offset + EXTENDED_QUERY_SIZE) * query_base > TOTAL_QUERY_SIZE) {
	_err = "Primary extended query larger than TOTAL_QUERY_SIZE";
	return false;
    }


    // DEBUG: 
    //printf("Raw Cfi query:\n");
    //for (u_int32_t i = 0x10 * query_base ; i <= (0x30 * query_base); i+= query_base) {
	//printf("0x%02x: %02x\n", i/query_base, fwp[i]);
    //}

    u_int32_t dw_aligned_offs = (((offset * query_base) >> 2 ) << 2);

    if (!read(dw_aligned_offs , fwp + dw_aligned_offs  , EXTENDED_QUERY_SIZE * query_base)) 
	return false;
    
    query->primary_extended_query[0] = fwp[query_base * (offset)];
    query->primary_extended_query[1] = fwp[query_base * (offset + 1)];
    query->primary_extended_query[2] = fwp[query_base * (offset + 2)];
    query->primary_extended_query[3] = '\0';
    
    if( query->primary_extended_query[0] != 'P' &&
	query->primary_extended_query[1] != 'R' &&
	query->primary_extended_query[2] != 'I') {
	_err = "Bad primary table address";
	return false;
    }
    
    query->major_version = fwp[query_base * (offset + 3)];
    query->minor_version = fwp[query_base * (offset + 4)];
    
    query->sensitive_unlock      = (u_int8_t) (fwp[query_base * (offset+5)] & 0x0F);
    query->erase_suspend         = (u_int8_t) (fwp[query_base * (offset+6)] & 0x0F);
    query->sector_protect        = (u_int8_t) (fwp[query_base * (offset+7)] & 0x0F);
    query->sector_temp_unprotect = (u_int8_t) (fwp[query_base * (offset+8)] & 0x0F);
    query->protect_scheme        = (u_int8_t) (fwp[query_base * (offset+9)] & 0x0F);
    query->is_simultaneous       = (u_int8_t) (fwp[query_base * (offset+10)] & 0x0F);
    query->is_burst              = (u_int8_t) (fwp[query_base * (offset+11)] & 0x0F);
    query->is_page               = (u_int8_t) (fwp[query_base * (offset+12)] & 0x0F);
    
    return true;
} 


// A smaple function which loops through and prints out the data
// contained in the CFI query structure.  Should ONLY be called
// after init_flash 

bool Flash::print_cfi_info( const cfi_query *q )
{
  int i=0;
  printf("\n");

  char* head_fmt = "%-50s ";

  printf(head_fmt, "CFI Query String Read:");
  printf("[%s]\n", (char *) q->query_string);

  printf(head_fmt, "Primary table address at offset:");
  printf("[0x%2x] hex.\n", q->primary_table_address);

  printf(head_fmt, "Manufacturer ID, Device ID:");
  printf("[0x%02x,0x%02x] hex.\n", q->manuf_id, q->device_id );

  printf(head_fmt, "Command set:");
  printf("[0x%04x] hex.\n", q->oem_command_set);

  printf(head_fmt, "Write buffer:");
  printf("[%d] bytes\n", q->max_multi_byte_write );

  printf("\n----Voltage and Signal Timing Parameters-------------------\n");
  printf(head_fmt, "Vcc operating voltage:");
  printf("[%2.3f] to [%2.3f] Volts\n", q->vcc_min, q->vcc_max);


  printf(head_fmt, "Vpp operating voltage:");
  if(q->vpp_min == 0.0)
	 printf("Device does not support Vpp voltage.\n");
  else {
	 printf("[%2.3f] to [%2.3f] Volts\n", q->vpp_min, q->vpp_max);
  }

  printf(head_fmt, "Typical timeout for single write (micro-sec):");
  printf("[%8i]us\n", q->timeout_single_write);


  
  printf(head_fmt,"Typical timeout for single write (micro-sec):");
  if(q->timeout_buffer_write == 0x00)
	 printf("Buffer writes not supported in this device.\n");
  else {
	 printf("[%8i]us\n" ,q->timeout_buffer_write);
  }

  printf(head_fmt, "Typical timeout for block erase (milli-sec):", q->timeout_block_erase);
  printf("[%8i]ms\n", q->timeout_block_erase);

  printf(head_fmt, "Typical timeout for chip erase (milli-sec):");
  if(q->timeout_chip_erase == 0x00)
	 printf("Not supported in this device.\n");
  else {
	 printf("[%8i]ms\n", q->timeout_single_write);
  }

  printf(head_fmt, "Maximum timeout for single write (micro-sec) :");
  printf("[%8i]us\n", q->max_timeout_single_write);

  printf(head_fmt, "Maximum timeout for buffer write (micro-sec) :");
  if(q->max_timeout_buffer_write == 0x00)
      printf("Not supported in this device.\n");
  else {
      printf("[%8i]us\n", q->max_timeout_buffer_write);
  }

  printf(head_fmt, "Maximum timeout for block erase (milli-sec) :");
  printf("[%8i]ms\n", q->max_timeout_block_erase);

  printf(head_fmt, "Maximum timeout for chip erase (milli-sec) :");
  if(q->max_timeout_chip_erase == 0x00)
      printf("Not supported in this device.\n");
  else {
      printf("[%8i]ms\n", q->max_timeout_chip_erase);
  }


  

  printf("\n----Sector Organization Parameters-------------------\n\n");

  printf(head_fmt, "Device size:");
  printf("[%8li] bytes, or [%2i] Mbit\n",
	 q->device_size, 
	 (int) (q->device_size/((long)0x20000)));

  printf(head_fmt, "Number of erase block regions:");
  printf("%d\n",q->num_erase_blocks);

  for(i=0; i<q->num_erase_blocks; i++) {
	 printf("  Size:[%8lx] bytes, Mask [%08x], [Number:[%4i]\n",
		q->erase_block[i].sector_size,
		q->erase_block[i].sector_mask,
		q->erase_block[i].num_sectors);
  }

  printf("\n----Primary Vendor-Specific Extended Parameters----\n\n");

  printf(head_fmt, "CFI Extended String Read:");
  printf("[%s]\n", (char *) q->primary_extended_query);

  printf(head_fmt, "Major version:", q->major_version);
  printf("[%3x]\n", q->major_version);

  printf(head_fmt, "Minor version:", q->minor_version);
  printf("[%3x]\n", q->minor_version);

  printf(head_fmt, "Sensitive Unlock:", q->sensitive_unlock);
  printf("[%3x]\n", q->sensitive_unlock);

  printf(head_fmt, "Erase Suspend:", q->erase_suspend);
  printf("[%3x]\n", q->erase_suspend);

  printf(head_fmt, "Sector Protect:", q->sector_protect);
  printf("[%3x]\n", q->sector_protect);

  printf(head_fmt, "Temporary Sector Unprotect:", q->sector_temp_unprotect);
  printf("[%3x]\n", q->sector_temp_unprotect);

  printf(head_fmt, "Protection Scheme:", q->protect_scheme);
  printf("[%3x]\n", q->protect_scheme);

  printf(head_fmt, "Is simultaneous? :", q->is_simultaneous);
  printf("[%3x]\n", q->is_simultaneous);

  printf(head_fmt, "Is Burst capable? :", q->is_burst);
  printf("[%3x]\n", q->is_burst);

  printf(head_fmt, "Is Page capable? :", q->is_page);
  printf("[%3x]\n", q->is_page);

  printf("Done.\n\n");

  return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::erase_sector(u_int32_t addr)
{
    return _cmd_set->erase_sector(addr);
}


////////////////////////////////////////////////////////////////////////

bool Flash::CmdSet0002::reset() {
    if (!_f.write_internal(0x555, 0xf0)) {
	_f._err = "Device reset failed";
	return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::CmdSet0002::erase_sector(u_int32_t addr)
{
    u_int32_t word = 0;
    int          cnt = 0;

    if (_no_erase)
        return true;

    // Just to insure zeroes because erase completion waits for ones
    if (!write(addr, &word, sizeof(word), true))
        return false;

    // erase sector sequence
#ifdef FUJITSU_BYTE_MODE
    if (!_f.write_internal(0xaaa, 0xaa))
        return false;
    if (!_f.write_internal(0x555, 0x55))
        return false;
    if (!_f.write_internal(0xaaa, 0x80))
        return false;
    if (!_f.write_internal(0xaaa, 0xaa))
        return false;
    if (!_f.write_internal(0x555, 0x55))
        return false;
    if (!_f.write_internal(addr, 0x30))
        return false;
#else // FUJITSU_WORD_MODE 
    if (_unlock_bypass) {
	// release unlock bypass before erase sector
	if (!_f.unlock_bypass(false)) return false; 
    }
      
    if (!_f.write_internal(0x555, 0xaa))
        return false;
    if (!_f.write_internal(0x2aa, 0x55))
        return false;
    if (!_f.write_internal(0x555, 0x80))
        return false;
    if (!_f.write_internal(0x555, 0xaa))
        return false;
    if (!_f.write_internal(0x2aa, 0x55))
        return false;
    if (!_f.write_internal(addr, 0x30))
        return false;

#endif

    // Wait while erase completes
    do
    {
        // Timeout checks
        if (++cnt > ERASE_CNT)
        {
            _f._err = "Flash erase sector timeout";
            return false;
        }
        if (!_f.read(addr, &word))
            return false;

        //printf("erase_sector: addr:%08lx, %08x\n", addr, word);
        usleep(ERASE_DELAY);
    } while (word != 0xffffffff);



#ifdef FUJITSU_BYTE_MODE
    // TODO: Need to check unlock bypass option for FUJITSU flash
#else // FUJITSU_WORD_MODE 

    if (_unlock_bypass) {
	// release unlock bypass before erase sector
	if (!_f.unlock_bypass(true)) return false; 
    }

#endif


    return true;
} // Flash::erase_sector

////////////////////////////////////////////////////////////////////////

bool Flash::CmdSet0001::reset() {
    if (!_f.write_internal(0x555, FC_Read)) {
	_f._err = "Device reset failed";
	return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::CmdSet0001::erase_sector(u_int32_t addr)
{
    u_int32_t    status = 0;
    int          cnt    = 0;

    if (_no_erase)
        return true;

    // Just to insure zeroes because erase completion waits for ones
    //if (!write(addr, &word, sizeof(word), true))
    //    return false;

    // Erase command
    if (!_f.write_internal(addr, FC_Erase))
        return false;

    // Erase confirm
    if (!_f.write_internal(addr, FC_Confirm))
        return false;

    usleep(ERASE_DELAY);

    // Wait while erase completes
    do
    {
        // Timeout checks
        if (++cnt > ERASE_CNT)
        {
            _f._err = "Flash erase sector timeout";
            return false;
        }
        if (!_f.read(addr, &status))
            return false;

        //printf("CmdSet0001::erase_sector: addr:%08lx, %08x\n", addr, word);
        usleep(ERASE_DELAY);
    } while ((status & FS_Ready) == 0);

    if (status & FS_Error) {
	_f._err = "Status register detected erase error";
	return false;
    }

    // Reset
    if (!reset())
	return false;

    return true;
} // Flash::erase_sector



////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr, u_int32_t data)
{
    if (!_mf)
    {
        _err = "Not opened";
        return false;
    }
    if (addr & 0x3)
    {
        _err = "Address should be 4-bytes aligned.";
        return false;
    }

    u_int32_t word;
    u_int32_t sector = addr & _cfi.erase_block[0].sector_mask;
    u_int32_t word_in_sector = (addr & ~_cfi.erase_block[0].sector_mask)/sizeof(u_int32_t);

    if (!read(addr, &word))
        return false;
    if (word == data)
        return true;   // already there

    u_int32_t buff[get_sector_size()/sizeof(u_int32_t)];
    if (!read(sector, buff, get_sector_size()))
        return false;
    buff[word_in_sector] = data;
    return write(sector, buff, get_sector_size());
} // Flash::write


////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr, void *data, int cnt,
			      bool noerase, bool noverify)
{
    return _cmd_set->write(addr, data, cnt, noerase, noverify);
}

////////////////////////////////////////////////////////////////////////
bool Flash::CmdSet0002::write(u_int32_t addr, void *data, int cnt,
			      bool noerase, bool noverify)
{
    if (!_f._mf)
    {
        _f._err = "Not opened";
        return false;
    }
    if (addr & 0x3)
    {
        _f._err = "Address should be 4-bytes aligned.";
        return false;
    }

    char         *p = (char *)data;

    for (int i=0; i<cnt; i++,addr++)
    {
        u_int32_t  word;
        u_int8_t   act, exp;
        int        cnt1 = 0;

	u_int32_t bank = addr & BANK_MASK;
	if (bank != _f._curr_bank)
	{
	    _f._curr_bank = bank;
	    if (!_f.set_bank(bank))
		return false;
	}
	
	if (!noerase)
	{
	    u_int32_t sector = addr & _f._cfi.erase_block[0].sector_mask;
	    if (sector != _f.curr_sector)
	    {
		_f.curr_sector = sector;
		if (!erase_sector(_f.curr_sector))
		    return false;
	    }
	}
	
	if (_no_burn)
	    continue;
	
	if (_f._use_scr)
	{

	   //
	   // Special burning interface via Scratchpad
           // ----------------------------------------
           //
	    u_int32_t cmd;
	    u_int32_t data = (*p++ & 0xff) << 24;
	    data |= (*p++ & 0xff) << 16;
	    data |= (*p++ & 0xff) << 8;
	    data |= (*p++ & 0xff);
	    if (mwrite4(_f._mf, _f.USE_SCR+4 , data) != 4) return false; 
	    if (mwrite4(_f._mf, _f.USE_SCR ,   WRITE1 | (3 << LEN_SHIFT) | (addr & ADDR_MSK)) != 4) return false; 
	    do
	    {
		int  loop_cnt = 0;
		// Timeout checks
		if (++loop_cnt > FLASH_CMD_CNT)
		{
		    _f._err = "Use scratchpad: CMD doesn't become zero";
		    return false;
		}
		if (mread4(_f._mf, _f.USE_SCR , &cmd) != 4) return false; 
		
	    } while(cmd & CMD_MASK);
	    i += 3;
	    addr += 3;
	}
	else if ((u_int8_t)(*p) != 0xff)
	{
	    
#ifdef FUJITSU_BYTE_MODE
	    if (!_f.write_internal(0xaaa, 0xaa))
		return false;
	    if (!_f.write_internal(0x555, 0x55))
		return false;
	    if (!_f.write_internal(0xaaa, 0xa0))
		return false;
#else // FUJITSU_WORD_MODE
	    if (!_unlock_bypass) { 
		if (!_f.write_internal(0x555, 0xaa))
		    return false;
		if (!_f.write_internal(0x2aa, 0x55))
		    return false;
	    }

	    if (!_f.write_internal(0x555, 0xa0))
		return false;
#endif

	    if (!_f.write_internal(addr, *p++))
		return false;

	    do
	    {
		// Timeout checks
		if (++cnt1 > READ_CNT_FAST)
		    usleep(READ_DELAY);
		if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW)
		{
		    _f._err = "Flash write error - read value doesn't stabilized.";
		    return false;
		}
		
		if (!_f.read(addr & ~3, &word))
		    return false;
		
#if __BYTE_ORDER == __LITTLE_ENDIAN
		act = (u_int8_t) ((word >> ((addr & 3) * 8)) & 0xff);
#elif __BYTE_ORDER == __BIG_ENDIAN
		act = (u_int8_t) ((word >> ((3 - (addr & 3)) * 8)) & 0xff);
#endif
		exp = *(p-1) & 0xff;
		//if (act != exp)
		//    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
		//           addr, exp & 0xff, act & 0xff, word);
	    } while (!noverify && act != exp);		
	    
	} else {
	    p++;
	}
    } 
    return true;
} // flash_write



bool Flash::CmdSet0001WriteByte::write(u_int32_t addr, void *data, int cnt,
				       bool noerase, bool noverify)
{
    if (!_f._mf)
    {
        _f._err = "Not opened";
        return false;
    }
    if (addr & 0x3)
    {
        _f._err = "Address should be 4-bytes aligned.";
        return false;
    }

    char         *p = (char *)data;

    for (int i=0; i<cnt; i++,addr++)
    {
        u_int32_t  status;
        u_int8_t   act, exp;
        int        cnt1 = 0;

	u_int32_t bank = addr & BANK_MASK;
	if (bank != _f._curr_bank)
	{
	    _f._curr_bank = bank;
	    if (!_f.set_bank(bank))
		return false;
	}
	
	if (!noerase)
	{
	    u_int32_t sector = addr & _f._cfi.erase_block[0].sector_mask;
	    if (sector != _f.curr_sector)
	    {
		_f.curr_sector = sector;
		if (!erase_sector(_f.curr_sector))
		    return false;
	    }
	}
	
	if (_no_burn)
	    continue;
	
	if ((u_int8_t)(*p) != 0xff)
	{
	    // Write byte
	    if (!_f.write_internal(addr, FC_Write))
		return false;

	    if (!_f.write_internal(addr, *p++))
		return false;

	    do
	    {
		// Timeout checks
		if (++cnt1 > READ_CNT_FAST)
		    usleep(READ_DELAY);
		if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW)
		{
		    _f._err = "Flash write error - timeout waiting for ready after write.";
		    return false;
		}

		// TODO - Move to read single for Arbel
		if (!_f.read(addr & ~3, &status))
		    return false;
		
		//if (act != exp)
		//    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
		//           addr, exp & 0xff, act & 0xff, word);
	    } while ((status & FS_Ready) == 0);

	    if (status & FS_Error) {
		_f._err = "Flash write error - error staus detected.";
		return false;
	    }

	    if (!noverify) {
		u_int32_t word;
		if (!reset()) 
		    return false;
		// TODO - Move to read single for Arbel
		if (!_f.read(addr & ~3, &word))
		    return false;
		
#if __BYTE_ORDER == __LITTLE_ENDIAN
		act = (u_int8_t) ((word >> ((addr & 3) * 8)) & 0xff);
#elif __BYTE_ORDER == __BIG_ENDIAN
		act = (u_int8_t) ((word >> ((3 - (addr & 3)) * 8)) & 0xff);
#endif
		exp = *(p-1) & 0xff;

		if (act != exp) {  
		    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
			   addr, exp & 0xff, act & 0xff, word);

		    _f._err = "Write verification failed";
		    return false;
		}
	    }
	    
	} else {
	    p++;
	}
    }

    if (!reset()) 
	return false;
    
    return true;
} // flash_write

///////////////////////////////////////////////////////////////////////////

//
// Use the buffer write capability.
//
bool Flash::CmdSet0001::write(u_int32_t addr, void *data, int cnt,
				       bool noerase, bool noverify)
{
    if (!_f._mf)
    {
        _f._err = "Not opened";
        return false;
    }
    if (addr & 0x3)
    {
        _f._err = "Address should be 4-bytes aligned.";
        return false;
    }

    u_int8_t         *p = (u_int8_t *)data;

    u_int32_t block_size = _f._cfi.max_multi_byte_write;
    u_int32_t block_mask = ~(block_size - 1 );

    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t  tmp_buff[MAX_WRITE_BUFFER_SIZE];

    while (cnt) {

	u_int32_t prefix_pad_size = 0;
	u_int32_t suffix_pad_size = 0;

	u_int32_t block_addr = addr & block_mask;
	u_int32_t data_size  = block_size;

	u_int8_t* write_data = p;


	//
	// First and last cycles (can be the same one) may not be block aligned.
	// Check the status, and copy data to a padded temp bufer if not alligned.
	// (there's an option to write partial buffer, but Intel reference code always
	// writes full buffer, with pads if needed. I do the dame ...)
	//

	prefix_pad_size = addr - block_addr;

	if ((addr & block_mask) == ((addr + cnt) & block_mask)) {
	    suffix_pad_size = block_size - ((addr + cnt) % block_size);
	}

	if (suffix_pad_size || prefix_pad_size) {
	    memset(tmp_buff, 0xff, block_size);

	    data_size -= prefix_pad_size;
	    data_size -= suffix_pad_size;

	    memcpy(tmp_buff + prefix_pad_size, p , data_size);

	    write_data = tmp_buff;
	}

        int        cnt1 = 0;

	//
	// Bank setup.
	//
	u_int32_t bank = addr & BANK_MASK;
	if (bank != _f._curr_bank)
	{
	    _f._curr_bank = bank;
	    if (!_f.set_bank(bank))
		return false;
	}
	
	if (!noerase)
	{
	    u_int32_t sector = addr & _f._cfi.erase_block[0].sector_mask;
	    if (sector != _f.curr_sector)
	    {
		_f.curr_sector = sector;
		if (!erase_sector(_f.curr_sector))
		    return false;
	    }
	}
	
	if (_no_burn)
	    continue;

	//
	// Check to see if there's something to do
	//
	bool all_ffs = true;
	for (u_int32_t i = 0; i < block_size ; i++) {
	    if (write_data[i] != 0xff) {
		all_ffs = false;
		break;
	    }
	}

	if (!all_ffs)
	{

	    u_int32_t status;
	    cnt1 = 0;
	    do {
		// Get Write buffer
		if (!_f.write_internal(block_addr, FC_SCSWrite))
		     return false;

		if (cnt1 > ((READ_CNT_FAST + READ_CNT_SLOW) * 4))
		{
		    printf("-D- status = %08x\n", status);
		    reset();
		    _f._err = "Flash write error - Write buffer not ready.";  
		    return false;
		}

		cnt1++;

		if (!_f.read(block_addr, &status)) 
		    return false;

	    } while (!(status & FS_Ready));

	    if (status & FS_Error) {
		_f._err = "Flash write error - Error getting write buffer";
		return false;
	    }

	    // word count (allways full buffer, coded as cull buffer size -1)
	    if (!_f.write_internal(block_addr, block_size - 1))
		return false;

	    // Write data to buffer
	    for (u_int32_t i = 0; i < block_size ; i++ ) {
		if (!_f.write_internal(block_addr + i, write_data[i]))
		    return false;
	    }

	    // write confirm
	    if (!_f.write_internal(block_addr, FC_Confirm))
		return false;

	    cnt1 = 0;
	    do
	    {
		// Timeout checks
		if (++cnt1 > READ_CNT_FAST)
		    usleep(READ_DELAY);
		if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW)
		{
		    reset();
		    _f._err = "Flash write error - Write buffer status timeout";
		    return false;
		}

		// TODO - Move to read single for Arbel
		if (!_f.read(block_addr, &status))
		    return false;
		
		//if (act != exp)
		//    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
		//           addr, exp & 0xff, act & 0xff, word);
	    } while ((status & 0x80) == 0);

	    //
	    // TODO: Status checks.
	    //

	    if (!noverify) {
		u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE];
		if (!reset()) 
		    return false;
		
		if (!_f.read(addr, verify_buffer, data_size))
		    return false;

		for (u_int32_t i = 0 ; i < data_size ; i++) {
		    if (verify_buffer[i] != write_data[i + prefix_pad_size]) {
			printf("write: %08x - exp:%02x act:%02x\n",
			       addr + i, 
			       write_data[i + prefix_pad_size] , 
			       verify_buffer[i]);
   
			_f._err = "Write verification failed";
			return false;
		    }
		}  
	    }    
	}


	//
	// loop advance
	//

	addr += data_size;
	p    += data_size;
	cnt  -= data_size;
    }

    if (!reset()) 
	return false;
    
    return true;
} // flash_write

////////////////////////////////////////////////////////////////////////
bool Flash::write_image(u_int32_t addr, void *data, int cnt, bool need_report)
{
    u_int8_t   *p = (u_int8_t *)data;
    u_int32_t  curr_addr = addr;
    u_int32_t  towrite = cnt;
    u_int32_t  perc = 0xffffffff;

    curr_sector = 0xffffffff;  // Erase sector first time
    if (need_report)
    {
        printf("000%%");
        fflush(stdout);
    }

    while (towrite)
    {
        // Write
        int trans = (towrite > (int)TRANS) ? (int)TRANS : towrite;
        if (!write(curr_addr, p, trans))
            return false;
        p += trans;
        curr_addr += trans;
        towrite -= trans;

        // Report
        if (need_report)
        {
            u_int32_t new_perc = ((cnt - towrite) * 100) / cnt;
            if (new_perc != perc)
            {
                printf("\b\b\b\b%03d%%", new_perc);
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    if (need_report)
    {
        printf("\b\b\b\b100%%");
        fflush(stdout);
    }

    return true;
} //  Flash::write_image

////////////////////////////////////////////////////////////////////////
bool Flash::FailSafe_burn(void *data, int cnt, bool need_report)
{
    u_int32_t *data32 = (u_int32_t *)data;
    u_int8_t  *data8 =  (u_int8_t *)data;

    report("\nRead and verify Invariant Sector               - ");
    fflush(stdout);

    // Once more check signature - the Inv.Sector signature should be OK
    u_int32_t signature;
    if (!read(0x24, &signature))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(signature);
    if (signature != SIGNATURE)
    {
        _err = "Flash has wrong signature in Invariant Sector.";
        report("FAILED\n\n");
        return false;
    }

    // Now check Invariant sector contents
    u_int32_t buf1[get_sector_size()/4];
    if (cnt < (int)get_sector_size() * 3)
    {
        _err = "Image is too small.";
        report("FAILED\n\n");
        return false;
    }
    if (!read(0, buf1, get_sector_size()))
    {
        report("FAILED\n\n");
        return false;
    }
    for (int i=0; i<(int)get_sector_size()/4; i++)
    {
        if (buf1[i] != data32[i]  &&  (data32[i] != 0 || buf1[i] != 0xffffffff))
        {
            sprintf(_msg, "Invariant sector doesn't match. Word #%d (0x%x)\n"
                    "in image: 0x%08x, while in flash: 0x%08x",
                    i, i, data32[i], buf1[i]);
            _err = &_msg[0];
            report("FAILED\n\n");
            return false;
        }
    }
    report("OK\n");

    // Check signatures in image
    u_int32_t actual_signature = data32[get_sector_size()/4 + 2];
    u_int32_t signature_for_compare = actual_signature;
    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE)
    {
        sprintf(_msg, "Wrong image: signature in PPS is 0x%08x (should be 0x%08x)",
                signature_for_compare, SIGNATURE);
        _err = &_msg[0];
        return false;
    }
    signature_for_compare = data32[(get_sector_size() * 2)/4 + 2];
    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE)
    {
        sprintf(_msg, "Wrong image: signature in SPS is 0x%08x (should be 0x%08x)",
                signature_for_compare, SIGNATURE);
        _err = &_msg[0];
        return false;
    }

    // Corrupt signatures in image
    data32[get_sector_size()/4 + 2] = 0xffffffff;
    data32[(get_sector_size() * 2)/4 + 2] = 0xffffffff;

    // Check signatures on flash
    bool bad_first = false, bad_second = false;
    report("Read and verify PPS/SPS in flash               - ");
    if (!read(get_sector_size() + 8, &signature_for_compare))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE)
        bad_first = true;
    if (!read(get_sector_size() * 2 + 8, &signature_for_compare))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE)
        bad_second = true;

    if (bad_first || bad_second) {
	report("Error Detected\n");
    } else {
	report("OK\n");
    }

    if (bad_first && bad_second)
    {
        //
        // Both images are invalid in flash
        // --------------------------------
        //
        printf("\nBoth images (primary and secondary) are invalid in flash.\n");
        printf("The burning can't be failsafe, but it is harmless for host.\n");
        printf("\n    Do you want to continue ? (y/n) [n] : ");
        if (_assume_yes)
            printf("y\n");
        else
        {
            fflush(stdout);
            char c = getchar();
            if (c != '\n')
                while (getchar() != '\n');
            if (c != 'y')
                return true;
        }

        // Burn all image
        report("Burn FW image without signatures - ");
        fflush(stdout);
        if (!write_image(get_sector_size(), data8 + get_sector_size(), cnt - get_sector_size(), need_report))
        {
            report("FAILED\n\n");
            return false;
        }
        report("\b\b\b\bOK  \n");

        // Restore signatures
        report("Restore right signatures         - ");
        fflush(stdout);
        if (!write(get_sector_size() + 8, &actual_signature, 4, true, false))
        {
            report("FAILED (PPS Signature)\n\n");
            return false;
        }
        if (!write(get_sector_size() * 2 + 8, &actual_signature, 4, true, false))
        {
            report("FAILED (SPS Signature)\n\n");
            return false;
        }
        report("OK\n");
        return true;
    }
    else if (bad_first)
    {
        //
        // Only first image is invalid in flash
        //
        if (!repair(1, 0, need_report))
            return false;
        return FailSafe_burn_internal(data, cnt, need_report);
    }
    else if (bad_second)
    {
        //
        // Only second image is invalid in flash
        //
        if (!repair(0, 1, need_report))
            return false;
        return FailSafe_burn_internal(data, cnt, need_report);
    }
    else
    {
        //
        // Both images are valid in flash
        //
        return FailSafe_burn_internal(data, cnt, need_report);
    }

    return true;
} // Flash::FailSafe_burn

////////////////////////////////////////////////////////////////////////
bool Flash::repair(const int from, const int to, bool need_report)
{
    report("Repairing: Copy %s image to %s     - ", from ? "secondary" : "primary" ,
           to ? "secondary" : "primary");

    // Valid image pointer
    u_int32_t im_ptr;
    if (!read(get_sector_size() * (from+1), &im_ptr))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(im_ptr);

    // Valid image size in bytes
    u_int32_t im_size_b;
    if (!read(get_sector_size() * (from+1) + 4, &im_size_b))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(im_size_b);

    // Valid image size in sectors
    u_int32_t im_size_s = (im_size_b + get_sector_size() - 1) / get_sector_size();

    // Address to copy valid image
    u_int32_t write_to = (!to) ? get_sector_size() * 3 : get_sector_size() * (3 + im_size_s);

    // Read valid image
    report("READ FW ");
    fflush(stdout);
    char *buf = new char[im_size_b];
    if (!read(im_ptr, buf, im_size_b, need_report))
    {
        report("FAILED\n\n");
        delete [] buf;
        return false;
    }

    // Copy it to right place
    report(" WRITE FW ");
    fflush(stdout);
    if (!write_image(write_to, buf, im_size_b, need_report))
    {
        report("FAILED\n\n");
        delete [] buf;
        return false;
    }
    delete [] buf;

    // Read valid sector
    u_int32_t sect[get_sector_size()/4];
    report(" READ %s ", from ? "SPS" : "PPS");
    if (!read(from ? get_sector_size()*2 : get_sector_size(), sect, get_sector_size(), need_report))
    {
        report("FAILED\n\n");
        return false;
    }

    // Set new image address
    // ++++++

    // Calculate new CRC
    // ++++++

    // Corrupt signature
    u_int32_t valid_signature = sect[2];
    sect[2] = 0xffffffff;

    // Write it to invalid sector
    report(" WRITE %s ", to ? "SPS" : "PPS");
    if (!write_image(to ? get_sector_size()*2 : get_sector_size(), sect, get_sector_size(), need_report))
    {
        report("FAILED\n\n");
        return false;
    }

    // Validate signature
    report(" SIGNATURE ");
    if (!write((to ? get_sector_size()*2 : get_sector_size()) + 8, &valid_signature, 4, true, false))
    {
        report("FAILED\n\n");
        return false;
    }

    report("OK\n");
    return true;
} // Flash::repair

////////////////////////////////////////////////////////////////////////
bool Flash::FailSafe_burn_internal(void *data, int cnt, bool need_report)
{
    u_int32_t *data32 = (u_int32_t *)data;
    u_int8_t  *data8 =  (u_int8_t *)data;

    // Extract Primary/Secondary image pointers and lengths
    u_int32_t prim_ptr = data32[get_sector_size() / 4];
    u_int32_t prim_len = data32[get_sector_size() / 4 + 1];
    u_int32_t scnd_ptr = data32[(get_sector_size() * 2) / 4];
    u_int32_t scnd_len = data32[(get_sector_size() * 2) / 4 + 1];
    TOCPU1(prim_ptr);
    TOCPU1(prim_len);
    TOCPU1(scnd_ptr);
    TOCPU1(scnd_len);
    if ((cnt < (int)(prim_ptr + prim_len)) || (cnt < (int)(scnd_ptr + scnd_len)))
    {
        _err = "Invalid image: too small.";
        return false;
    }
    if (prim_len != scnd_len)
    {
        _err = "Invalid image: two FW images should be in a same size.";
        return false;
    }

    // Image size from flash
    u_int32_t old_im_size;
    if (!read(get_sector_size() + 4, &old_im_size))
    {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(old_im_size);

    u_int32_t prim_order;
    u_int32_t scnd_order;

    u_int32_t ps_addr[2];
    u_int32_t image_addr[2];
    char*     image_name[2];


    if (prim_len > old_im_size)
    {
	scnd_order = 0;
	prim_order = 1;
    }
    else
    {
	prim_order = 0;    
	scnd_order = 1;
    }

    image_name[scnd_order] = "Secondary";
    image_addr[scnd_order] = scnd_ptr;
    ps_addr   [scnd_order] = get_sector_size() * 2;
    
    image_name[prim_order] = "Primary";
    image_addr[prim_order] = prim_ptr;
    ps_addr   [prim_order] = get_sector_size(); 
    

    for (int i = 0 ; i < 2 ; i++) 
    {
	report("Burning %-9s FW image without signatures  - ", image_name[i]);
	fflush(stdout);
	        
	// Invalidate signature
	u_int32_t zeros = 0;
	if (!write(ps_addr[i] + 8, &zeros, 4, true, false))
	{
	    report("FAILED (Invalidating signature)\n\n");
	    return false;
	}

        // Burn image (from new offset)

	// Both burnt images are taken from the first image in the file - both images in file are identical.
	// (future binary releases may contain a single image).
	if (!write_image(image_addr[i], data8 + get_sector_size() * 3, prim_len, need_report))
	{
	    report("FAILED\n\n");
	    return false;
	}
	report("\b\b\b\bOK  \n");
	report("Restoring %-9s signature                  - ", image_name[i]); 
        fflush(stdout);

	// Burn PS
	if (!write_image(ps_addr[i], data8 + ps_addr[i], get_sector_size(), false)) {
 	    report("FAILED\n\n");
	    return false;
	}
        
	// Validate signature
	u_int32_t sig = SIGNATURE;
	TOCPU1(sig);
	if (!write(ps_addr[i] + 8, &sig, 4, true, false))
	{
	    report("FAILED\n\n");
	    return false;
	}
	
	report("OK  \n");
    }

    return true;
} // Flash::FailSafe_burn_internal

////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        VERIFY FLASH                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
bool checkBoot2(FBase& f, u_int32_t beg, u_int32_t offs,
                u_int32_t& next, const char *pref)
{
    u_int32_t    size;

    char         *pr = (char *)alloca(strlen(pref) + 512);

    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs+beg);

    // Size
    READ4(f, offs+beg+4, &size, pr);
    TOCPU1(size);
    if (size > 1048576 || size < 4)
    {
        report("%s /0x%08x/ - unexpected size (0x%x)\n", pr, offs+beg+4, size);
        return false;
    }

    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, offs+beg,
            offs+beg+(size+4)*4-1, (size+4)*4);

    Crc16        crc;
    u_int32_t    *buff = (u_int32_t*)alloca((size + 4)*sizeof(u_int32_t));

    READBUF(f, offs+beg, buff, size*4 + 16, pr);
    TOCPUn(buff, size+4);
    CRC1n(crc, buff, size+4);
    crc.finish();
    u_int32_t crc_act = buff[size+3];
    if (crc.get() != crc_act)
    {
        report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, offs+beg, crc.get(), crc_act);
        return false;
    }

    if (_print_crc)
        report("%s - OK (CRC:0x%04x)\n", pr, crc_act&0xffff);
    else
        report("%s - OK\n", pr);
    next = offs + size*4 + 16;
    return true;
} // checkBoot2

static int part_cnt;

////////////////////////////////////////////////////////////////////////
bool checkGen(FBase& f, u_int32_t beg,
              u_int32_t offs, u_int32_t& next, const char *pref)
{
    char         *pr = (char *)alloca(strlen(pref) + 100);

    u_int32_t    size=0;
    GPH          gph;

    // GPH
    sprintf(pr, "%s /0x%08x/ (GeneralHeader)", pref, offs+beg);
    READBUF(f, offs+beg, &gph, sizeof(GPH), pr);
    TOCPUBY(gph);

    // Body

    part_cnt++;

    // May be BOOT3?
    if (gph.type < H_FIRST  ||  gph.type > H_LAST)
    {
        if (part_cnt > 2)
        {
            report("%s /0x%x/ - Invalid partition type (%d)\n",
                   pref, offs+beg, gph.type);
            return false;
        }
        else
            return checkBoot2(f, beg, offs, next, pref);
    }

    // All partitions here
    offs += beg;
    switch(gph.type)
    {
    case H_DDR:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (DDR)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_CNF:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (Configuration)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_JMP:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (Jump addresses)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_EMT:
        size = gph.size;
        size = (size + 3) / 4 * 4;
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (EMT Service)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_ROM:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (ROM)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_BOARD_ID:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (Board ID)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_GUID:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (GUID)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    default:
        report("%s /0x%08x/ - Invalid partition type (%d)\n", pref,offs,gph.type);
        return false;
    }

    // CRC
    Crc16        crc;

    u_int32_t *buff = (u_int32_t*)alloca(size);

    READBUF(f, offs+sizeof(gph), buff, size, pr);
    TOCPUn(buff,size/4);
    CRCBY(crc, gph);
    CRCn(crc, buff, size/4);
    crc.finish();
    u_int32_t crc_act;
    READ4(f, offs+sizeof(gph)+size, &crc_act, pr);
    TOCPU1(crc_act);
    if (crc.get() != crc_act)
    {
        report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, offs, crc.get(), crc_act);
        return false;
    }

    if (_print_crc)
        report("%s - OK (CRC:0x%04x)\n", pr, crc_act&0xffff);
    else
        report("%s - OK\n", pr);
    next = gph.next;
    return true;
} // checkGen

////////////////////////////////////////////////////////////////////////
bool checkPS(FBase& f, u_int32_t offs, u_int32_t& next, const char *pref)
{
    Crc16 crc;
    PS    ps;
    f.read(offs, &ps, sizeof(ps));
    TOCPUBY(ps);

    // Signature
    if (ps.signature != SIGNATURE)
    {
        report("%s Pointer Sector /0x%08x/ - wrong signature (%08x)\n",
               pref, offs, ps.signature);
        return false;
    }

    // CRC
    CRC1BY(crc, ps);
    crc.finish();
    if (crc.get() != ps.crc016)
    {
        report("%s Pointer Sector /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pref, offs, ps.crc016, crc.get());
        return false;
    }

    next = ps.fi_addr;
    if (_print_crc)
        report("%s Image /0x%08x-0x%08x (0x%06x)/ (Pointer Sector)- OK (CRC:0x%04x)\n", pref, offs,
               offs+(u_int32_t)sizeof(ps)-1, (u_int32_t)sizeof(ps), ps.crc016&0xffff);
    else
        report("%s Image /0x%08x-0x%08x (0x%06x)/ (Pointer Sector)- OK\n", pref, offs,
               offs+(u_int32_t)sizeof(ps)-1, (u_int32_t)sizeof(ps));
    return true;
} // checkPS

////////////////////////////////////////////////////////////////////////
bool checkList(FBase& f, u_int32_t offs, const char *pref)
{
    u_int32_t next_ptr;

    CHECKB2(f, offs, 0x28, next_ptr, pref);
    part_cnt = 1;
    while (next_ptr && next_ptr != 0xff000000)
        CHECKGN(f, offs, next_ptr, next_ptr, pref);
    return true;
} // checkList

////////////////////////////////////////////////////////////////////////
bool Verify(FBase& f)
{
    u_int32_t prim_ptr, scnd_ptr;
    u_int32_t signature;

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    if (signature == SIGNATURE)
    {
        // Full image
        _image_is_full = true;
        report("\nFailsafe image:\n\n");
        CHECKB2(f, 0, 0x28, prim_ptr, "Invariant      ");
        report("\n");
        if (checkPS(f, f.get_sector_size(), prim_ptr, "Primary  "))
            CHECKLS(f, prim_ptr, "               ");
        report("\n");
        if (checkPS(f, f.get_sector_size() * 2, scnd_ptr, "Secondary"))
            CHECKLS(f, scnd_ptr, "               ");
    }
    else
    {
        // Short image
        _image_is_full = false;
        report("\nShort image:\n");
        CHECKLS(f, 0, "    ");
    }

    return true;
} // Verify


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                       GUIDs TREATMENT                              //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
#define GETGUID(s, g) do { if (!getGUID(s,g)) return 1; } while (0)
#define GETBSN(s, g)  do { if (!getBSN(s,g)) return 1; } while (0)
#define GUIDS 4

#define BSN_RET do {                                            \
    printf("Invalid BSN. Should be MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n"); \
    return false;                                               \
} while(0)
#define BSN_RET1(s) do {                                             \
    printf("Valid BSN format is: MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n%s.\n",s); \
    return false;                                                    \
} while(0)
u_int32_t BSN_subfield(const char *s, int beg, int len)
{
    char buf[64];
    strncpy(buf, &s[beg], len);
    buf[len] = '\0';
    return strtoul(&buf[0], 0, 10);
}
bool getBSN(char *s, u_int64_t *guid)
{
    const u_int64_t COMPANY_ID = 0x0002c9;
    const u_int64_t  TYPE      = 1;
    bool cc_present = false;
    char *p;
    int  date_offs = 0;
    int  i;

    // Convert to lowercase
    for (p = s; *p; p++)
        *p = tolower(*p);

    // Check validity
    p = s;
    if (strncmp(p, "mt", 2))     // MT
        BSN_RET;
    p += 2;
    for (i=0; i<5; i++)
        if (!isdigit(*p++))      // xxxxx
            BSN_RET;
    if (*p == '-')               // - /optional/
    {
        p++;
        date_offs++;
    }
    if (*p < 'a' || *p > 'z')    // R
        BSN_RET;
    p++;

    // Count how many digits after R
    char *q = p;
    int  ndigits=0;
    while (isdigit(*q++))
        ndigits++;

    switch (ndigits)
    {
    case 6:
        p += 6;                  // skip ddmmyy
        break;
    case 8:
        p += 8;                  // skip xxddmmyy
        date_offs += 2;
        break;
    default:
        BSN_RET;
    }

    if (*p++ != '-')             // -
        BSN_RET;
    for (i=0; i<3; i++)          // nnn
        if (!isdigit(*p++))
            BSN_RET;
    if (*p)
    {
        cc_present = true;
        if (*p++ != '-')         // -
            BSN_RET;
        for (i=0; i<2; i++)      // cc
            if (!isdigit(*p++))
                BSN_RET;
    }

    u_int32_t dd = BSN_subfield(s, 8+date_offs, 2);
    if (dd > 31)
        BSN_RET1("Day (dd) should not exceed 31");
    if (!dd)
        BSN_RET1("Day (dd) can't be zero");
    u_int32_t mm = BSN_subfield(s, 10+date_offs, 2);
    if (mm > 12)
        BSN_RET1("Months (mm) should not exceed 12");
    if (!mm)
        BSN_RET1("Months (mm) can't be zero");
    u_int32_t yy = BSN_subfield(s, 12+date_offs, 2);
    if (yy > 99)
        BSN_RET1("Year (yy) should not exceed 99");
    if (!yy)
        BSN_RET1("Year (yy) can't be zero");
    u_int32_t num = BSN_subfield(s, 15+date_offs, 3);
    if (num > 999)
        BSN_RET1("Number (num) should not exceed 999");
    if (!num)
        BSN_RET1("Number (num) can't be zero");
    int cc = 1;
    if (cc_present)
    {
        cc = BSN_subfield(s, 19+date_offs, 2);
        if (cc > 14)
            BSN_RET1("Chip number (cc) should not exceed 14");
        if (!cc)
            BSN_RET1("Chip number (cc) can't be zero");
    }
    u_int64_t id = ((((yy*12+mm-1)*31+ dd-1) * 1000) + num-1) * 112;
    id += (cc-1)*8;
    *guid = (COMPANY_ID << 40) | (TYPE << 32) | id;
    return true;
}

bool getGUID(const char *s, u_int64_t *guid)
{
    char          str[17], *endp;
    int           i,j, str_beg;
    u_int32_t     h,l;
    memset(str, '0', 15);
    str[16] = '\0';

    if (!strncmp(s, "0x", 2)  ||  !strncmp(s, "0X", 2))
        str_beg = 2;
    else
        str_beg = 0;
    for (i=(int)strlen(s)-1,j=15; i >= str_beg && j >= 0; i--)
        str[j--] = s[i];

    l = strtoul(&str[8], &endp, 16);
    if (*endp)
    {
        printf("Invalid GUID syntax (low) (%s)\n", &str[8]);
        return false;
    }
    str[8] = '\0';
    h = strtoul(&str[0], &endp, 16);
    if (*endp)
    {
        printf("Invalid GUID syntax (high) (%s)\n", str);
        return false;
    }
    *guid = ((u_int64_t)h << 32) | l;
    return true;
} // getGUID

////////////////////////////////////////////////////////////////////////
bool extractGUIDptr(u_int32_t sign, u_int32_t *buf, int buf_len,
                     char *pref, u_int32_t *ind, int *nguids)
{
    u_int32_t offs = 0;

    // Check signature
    if (sign)
    {
        u_int32_t signature = buf[(sign + 8)/4];
        TOCPU1(signature);
        if (signature != SIGNATURE)
        {
            printf("%s pointer section not valid\n", pref);
            return false;
        }
        offs = buf[sign/4];
        TOCPU1(offs);
    }

    // Get GUID ptr
    *ind = buf[(offs+0x24)/4];
    TOCPU1(*ind);
    *ind += offs;
    if (*ind >= (u_int32_t)buf_len)
    {
        printf("%s image - insane GUID pointer (%08x)\n", pref, *ind);
        return false;
    }
    *nguids = buf[*ind/4 - 3];
    TOCPU1(*nguids);
    *nguids /= 2;

    // More sanity check
    if (*nguids > GUIDS)
    {
        printf("%s image - insane number of GUIDs (%d)\n", pref, *nguids);
        return false;
    }

    return true;
} // extractGUIDptr

////////////////////////////////////////////////////////////////////////
void pathGUIDsSection(u_int32_t *buf, u_int32_t ind,
                      u_int64_t guids[GUIDS], int nguids)
{
    u_int32_t       i, word;
    u_int32_t       new_buf[GUIDS*2];
    Crc16              crc;

    // Form new GUID section
    for (i=0; i<(u_int32_t)nguids; i++)
    {
        new_buf[i*2] = (u_int32_t) (guids[i] >> 32);
        new_buf[i*2+1] = (u_int32_t) (guids[i] & 0xffffffff);
    }

    // Calculate new CRC16
    for (i=ind/4 - 4; i<ind/4; i++)
    {
        word = buf[i];
        TOCPU1(word);
        crc << word;
    }
    for (i=0; i<(u_int32_t)nguids*2; i++)
        crc << new_buf[i];

    // Patch GUIDs
    TOCPU(new_buf);
    memcpy(&buf[ind/4], &new_buf[0], nguids * 2 * sizeof(u_int32_t));

    // Insert new CRC
    crc.finish();
    word = crc.get();
    TOCPU1(word);
    buf[ind/4 + nguids*2] = word;
} // pathGUIDsSection


////////////////////////////////////////////////////////////////////////
void _patchVSD(FImage& f, int ind, char *vsd)
{
    u_int32_t  *buf = f.getBuf();
    Crc16      crc;
    PS         *ps = (PS*)&buf[ind/4];

    memcpy(&ps->vsd[0], vsd, VSD_LEN);

    u_int32_t *qp = (u_int32_t *)ps;
    for (unsigned int i=0; i<sizeof(PS)/sizeof(u_int32_t) - 1; i++)
    {
        u_int32_t qq = *qp++;
        TOCPU1(qq);
        crc << qq;
    }
    crc.finish();
    u_int32_t crc016 = crc.get();
    TOCPU1(crc016);
    ps->crc016 = crc016;
} // _patchVSD


////////////////////////////////////////////////////////////////////////
bool patchVSD(FImage& f, char *vsd1, char *psid)
{
    char       vsd[VSD_LEN];

    // Form new VSD
    memset(vsd, 0, VSD_LEN);
    if (vsd1)
        strncpy(&vsd[0], vsd1, VSD_OFFS);
    if (psid)
        strncpy(&vsd[VSD_OFFS], psid, VSD_LAST);

    u_int32_t *qp = (u_int32_t *)&vsd[0];
    for (int i=0; i<VSD_LEN/4; i++)
    {
        TOCPU1(*qp);
        qp++;
    }

    _patchVSD(f, f.get_sector_size(), vsd);      // Primary PS
    _patchVSD(f, f.get_sector_size()*2, vsd);    // Secondary PS
    return true;
} // pathVSD


////////////////////////////////////////////////////////////////////////
bool pathGUIDs(FImage& f, u_int64_t guids[GUIDS],
               bool interactive)
{
    u_int64_t       old_guids[GUIDS];
    u_int32_t       *buf = f.getBuf();
    int             buf_len = f.getBufLength();
    u_int32_t       signature = buf[0x24/4];
    u_int32_t       ind1=0,ind2=0;
    int             nguid1, nguid2;

    TOCPU1(signature);
    if (signature == SIGNATURE)
    {
        // Full image
        if (interactive)
            printf("\nFull image:\n\n");
        if (!extractGUIDptr(f.get_sector_size()   , buf, buf_len, "Primary"  , &ind1, &nguid1))
            return false;
        if (!extractGUIDptr(f.get_sector_size() *2, buf, buf_len, "Secondary", &ind2, &nguid2))
            return false;

    }
    else
    {
        // Short image
        if (interactive)
            printf("\nShort image:\n\n");
        if (!extractGUIDptr(0, buf, buf_len, "Primary", &ind1, &nguid1))
            return false;
    }

    // Print old GUIDs and get confirmation
    if (interactive)
    {
        bool old_guids_fmt = nguid1 < GUIDS;
        for (int i=0; i<GUIDS; i++)
        {
            u_int32_t h = buf[ind1/4 + i*2];
            TOCPU1(h);
            u_int32_t l = buf[ind1/4 + i*2 + 1];
            TOCPU1(l);
            old_guids[i] = ((u_int64_t)h << 32) | l;
        }
        if (old_guids_fmt)
            printf("    Old image!!!! Only %d GUIDs may be set.\n", nguid1);

        printf("    Old GUIDs (inside image) are:\n");
        printf("        Node:      " GUID_FORMAT "\n", old_guids[0]);
        printf("        Port1:     " GUID_FORMAT "\n", old_guids[1]);
        printf("        Port2:     " GUID_FORMAT "\n", old_guids[2]);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", old_guids[3]);
        printf("\n    You are about to change them to follow GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", guids[0]);
        printf("        Port1:     " GUID_FORMAT "\n", guids[1]);
        printf("        Port2:     " GUID_FORMAT "\n", guids[2]);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", guids[3]);

        printf("\n    Is it OK ? (y/n) [n] : ");
        if (_assume_yes)
            printf("y\n");
        else
        {
            fflush(stdout);
            char c = getchar();
            if (c != '\n')
                while (getchar() != '\n');
            if (c != 'y')
                return false;
        }
    }

    // Path GUIDs section
    pathGUIDsSection(buf, ind1, guids, nguid1);
    if (ind2)
        pathGUIDsSection(buf, ind2, guids, nguid2);

    if (!interactive)
    {
        bool old_guids_fmt = nguid1 < GUIDS;
        printf("\n    Burn image with follow GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", guids[0]);
        printf("        Port1:     " GUID_FORMAT "\n", guids[1]);
        printf("        Port2:     " GUID_FORMAT "\n", guids[2]);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", guids[3]);
    }
    return true;
} // pathGUIDs


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                  Revision info and board ID                        //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
bool RevisionInfo(FBase& f, u_int64_t guids_out[GUIDS], char *vsd_out,
                  bool *fs_image, bool internal_call = false)
{
    char      *im_type;
    u_int32_t prim_ptr, scnd_ptr, ps_start=0;
    u_int32_t signature;
    u_int32_t im_start = 0;

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    _silent = true;
    if (signature == SIGNATURE)
    {
        // Full image
        report("\nFailsafe image:\n\n");
        if (checkPS(f, f.get_sector_size(), prim_ptr, "Primary  "))
        {
            im_start = prim_ptr;
            ps_start = f.get_sector_size();
        }
        else if (checkPS(f, f.get_sector_size() * 2, scnd_ptr, "Secondary"))
        {
            im_start = scnd_ptr;
            ps_start = f.get_sector_size() * 2;
        }
        else
        {
            _silent = internal_call;
            report("No valid image found.\n");
            return false;
        }
        im_type = "FailSafe";
        *fs_image = true;
    }
    else
    {
        // Short image
        report("\nShort image:\n");
        im_type = "Short";
        *fs_image = false;
    }

    _silent = internal_call;

    // FW ID
    u_int32_t fw_id;
    READ4(f, im_start + 0x10, &fw_id, "FW ID");
    TOCPU1(fw_id);
    fw_id >>= 24;

    // Read GUIDs
    FImage    *fim = dynamic_cast<FImage*>(&f);
    u_int32_t guid_ptr, nguids;
    u_int64_t guids[GUIDS];

    READ4(f, im_start + 0x24, &guid_ptr, "GUID PTR");
    TOCPU1(guid_ptr);
    guid_ptr += im_start;
    if (guid_ptr >= (fim ? fim->getBufLength() : (u_int32_t)f.MAX_FLASH))
    {
        report("Insane GUID pointer (%08x)\n", guid_ptr);
        return false;
    }
    READ4(f, guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
    TOCPU1(nguids);
    if (nguids > GUIDS*2)
    {
        report("Insane Number of GUIDs (%d)\n", nguids);
        return false;
    }
    READBUF(f, guid_ptr, guids, nguids / 2 * sizeof(u_int64_t), "GUIDS");
    TOCPUBY64(guids);
    memcpy(&guids_out[0], &guids[0], sizeof(guids));

    report("Image type: %s\n"
           "Chip rev.:  %X\n",
           im_type, fw_id);
    report("GUIDs:      ");
    for (u_int32_t i=0; i<nguids/2; i++)
            report(GUID_FORMAT " ", guids[i]);
    if (*fs_image)
    {
        char       vsd[VSD_LEN+1];   // +1  => Leave a space for \0 when psid size == 16 .

        memset(vsd, 0, VSD_LEN+1);
        READBUF(f, ps_start + 0x20, vsd, VSD_LEN, "Vendor Specific Data (Board ID)");
        TOCPUBY(vsd);

	#if (0)
	// Show '\0' in VSD and PSID strings:
	bool str_found = false;
	for (int i = VSD_OFFS - 2; i >= 0 ; i--) {
	    if (!str_found && vsd[i] != '\0') 
		str_found = true;
	    
	    if (str_found && vsd[i] == '\0') 
		vsd[i] = '.'; 
	}
	#endif

        report("\nBoard ID:   %s", vsd);
        if (vsd[VSD_OFFS])
            report(" (%s)\n", &vsd[VSD_OFFS]);
        else
            report("\n");
        if (vsd_out)
            memcpy(vsd_out, &vsd[0], VSD_LEN);
    }
    else
        report("\n");

    return true;
} // RevisionInfo


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                           MAIN                                     //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
// sed -e 's/"/\\"/g' < flint.txt | perl -pe 's/^(.*)$/"$1\\n"/'

void usage(const char *sname)
{
    const char *descr =
"\n"
"               FLINT - FLash INTerface\n"
"\n"
"InfiniHost flash memory operations.\n"
"\n"
"Usage:\n"
"------\n"
"\n"
"    " FLINT_NAME " [switches...] <command> [parameters...]\n"
"\n"
"\n"
"Switches summary:\n"
"-----------------\n"
"    -bsn <BSN>         - Mellanox Board Serial Number (BSN).\n"
"                         Valid BSN format is:\n"
"                                 MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n"
"                         Commands affected: burn\n"
"\n"
"    -crc               - Print CRC after each section when verify.\n"
"\n"
"    -d[evice] <device> - Device flash is connected to.\n"
"                         Commands affected: all\n"
"\n"
"    -guid <GUID>       - Base value for up to 4 GUIDs, which\n"
"                         are automatically assigned the\n"
"                         following values:\n"
"\n"
"                         guid   -> node GUID\n"
"                         guid+1 -> port1\n"
"                         guid+2 -> port2\n"
"                         guid+3 -> system image GUID.\n"
"\n"
"                         Commands affected: burn\n"
"\n"
"    -guids <GUIDs...>  - 4 GUIDs must be specified here.\n"
"                         The specified GUIDs are assigned\n"
"                         the following values, repectively:\n"
"                         node, port1, port2 and system image GUID.\n"
"\n"
"                         Commands affected: burn\n"
"\n"
"    -h[elp]            - Prints this message and exits\n"
"\n"
"    -i[mage] <image>   - Binary image file.\n"
"                         Commands affected: burn, verify\n"
"\n"
"    -nofs              - Burn image not in failsafe manner.\n"
"\n"
"    -unlock            - Use unlock bypass feature of the flash for quicker burn.\n"
"                         Commands affected: burn\n"
"\n"
"    -s[ilent]          - Do not print burn progress flyer.\n"
"                         Commands affected: burn\n"
"\n"
"    -y[es]             - Non interactive mode - assume answer\n"
"                         \"yes\" to all questions.\n"
"                         Commands affected: all\n"
"\n"
"    -vsd  <string>     - Write this string, of up to 208 characters, to VSD when burn.\n"
"\n"
"    -psid <PSID>       - Write the Parameter Set ID (PSID) string to PS-ID field (last 16 bytes of VSD) when burn.\n"
"\n"
"    -use_image_ps      - Burn vsd/psid as appears in the given image - don't keep existing vsd/psid on flash.\n"
"                         Commands affected: burn\n"
"\n"
"    -v                 - Version info.\n"
"\n"
"Commands summary:\n"
"-----------------\n"
"    b[urn]   - Burn flash\n"
"    e[rase]  - Erase sector\n"
"    q[uery]  - Query misc. flash/FW characteristics\n"
"    rw       - Read one dword from flash\n"
"    v[erify] - Verify entire flash\n"
"    ww       - Write one dword to flash\n"
"    wwne     - Write one dword to flash without sector erase\n"
"\n"
"\n"
"Command descriptions:\n"
"----------------------------\n"
"\n"
"* Burn flash\n"
"  Burns entire flash from raw binary image.\n"
"\n"
"    Command:\n"
"        b[urn]\n"
"    Parameters:\n"
"        None\n"
"    Examples:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -i image1.bin burn\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE2 " -guid 0x2c9000100d050 -i image1.bin b\n"
"\n"
"\n"
"* Erase sector.\n"
"  Erases a sector that contains specified address.\n"
"\n"
"    Command:\n"
"        e[rase]\n"
"    Parameters:\n"
"        addr - address of word in sector that you want\n"
"                   to erase.\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " erase 0x10000\n"
"\n"
"\n"
"* Query miscellaneous FW and flash parameters\n"
"\n"
"    Command:\n"
"        q[uery]\n"
"    Parameters:\n"
"        None\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " query\n"
"\n"
"\n"
"* Read one dword from flash.\n"
"\n"
"    Command:\n"
"        rw\n"
"    Parameters:\n"
"        addr - address of word to read\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " rw 0x20\n"
"\n"
"\n"
"* Verify entire flash.\n"
"\n"
"    Command:\n"
"        v[erify]\n"
"    Parameters:\n"
"        None\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " v\n"
"\n"
"\n"
"* Write one dword to flash.\n"
"  Note that the utility will read an entire flash sector,\n"
"  modify one word and write the sector back. This may take\n"
"  a few seconds.\n"
"\n"
"    Command:\n"
"        ww\n"
"    Parameters:\n"
"        addr - address of word\n"
"        data - value of word\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " ww 0x10008 0x5a445a44\n"
"\n"
"\n"
"* Write one dword to flash without sector erase.\n"
"  Note that the result of operation is undefined and depends\n"
"  on flash type. Usually \"bitwise AND\" (&) between specified\n"
"  word and previous flash contents will be written to\n"
"  specified address.\n"
"\n"
"    Command:\n"
"        wwne\n"
"    Parameters:\n"
"        addr - address of word\n"
"        data - value of word\n"
"    Example:\n"
"        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " wwne 0x10008 0x5a445a44\n"
        "\n";
    printf(descr, sname);
}

////////////////////////////////////////////////////////////////////////
#define NEXTS(s) do {                                        \
    if (++i >= ac)                                           \
    {                                                        \
        printf("Missed parameter after \"%s\" switch\n", s); \
        return 1;                                            \
    }} while(0)
#define NEXTC(p, s) do {                                           \
    if (++i >= ac)                                                 \
    {                                                              \
        printf("Missed %s parameter after \"%s\" command\n", p,s); \
        return 1;                                                  \
    }} while(0)

int main(int ac, char *av[])
{
    bool         fs_image;
    char         *image_fname=0, *device=0;
    bool         silent           = false; 
    bool         guids_specified  = false; 
    bool         burn_failsafe    = true;
    bool         use_image_ps     = false;
    char         *vsd1=0;
    char         *psid=0;
    u_int64_t    guids[GUIDS];
    char         vsds[VSD_LEN];
    Flash        f;

    if (ac < 2)
    {
        usage(av[0]);
        return 1;
    }

    // Go thru command line options
    for (int i=1; i < ac; i++)
    {
        //
        // Switches
        // --------
        //
        if (*av[i] == '-')
        {
            if (!strncmp(av[i], "-d", 2))
            {
                NEXTS("-device");
                device = av[i];
                if (!f.open(device))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
            }
	    else if (!strcmp(av[i], "-v") || !strcmp(av[i], "-vv")) {
		printf("%s: Version %s.",
		       av[0],
		       _versionID);

		if (!strcmp(av[i], "-vv")) {
		    printf(" CVS %s", _cvsID + 1); 
		}

		printf("\n");
		return 0;

	    }
	    else if (!strcmp(av[i], "-unlock")) {
		_unlock_bypass = true;
		f.unlock_bypass(true);
	    }
            else if (!strcmp(av[i], "-noerase"))
                _no_erase = true;
            else if (!strcmp(av[i], "-noburn"))
                _no_burn = true;
            else if (!strcmp(av[i], "-crc"))
                _print_crc = true;
            else if (!strcmp(av[i], "-bytewrite")) {
		if (device) {
		    printf("\"-bytewrite\" should be specifies before \"-device\" switch in the command line.\n");
		    return 1;
		}
                _byte_write = true;
	    }
            else if (!strcmp(av[i], "-vsd"))
            {
                NEXTS("-vsd");
                vsd1 = av[i];
            }
	    // -vsd1 is an alias to -vsd, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd1"))
            {
                NEXTS("-vsd1");
                vsd1 = av[i];
            }
            else if (!strcmp(av[i], "-psid"))
            {
                NEXTS("-psid");
                psid = av[i];
            }
	    // -vsd2 is an alias to psid, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd2"))
            {
                NEXTS("-vsd2");
                psid = av[i];
            }
            else if (!strcmp(av[i], "-bsn"))
            {
                NEXTS("-bsn");
                GETBSN(av[i], &guids[0]);
                for (int i=1; i<GUIDS; i++)
                    guids[i] = guids[0] + i;
                guids_specified = true;
            }
            else if (!strncmp(av[i], "-i", 2))
            {
                NEXTS("-image");
                image_fname = av[i];
            }
	    else if (!strcmp(av[i], "-guid"))
            {
                NEXTS("-guid");
                GETGUID(av[i], &guids[0]);
                for (int i=1; i<GUIDS; i++)
                    guids[i] = guids[0] + i;
                guids_specified = true;
            }
            else if (!strcmp(av[i], "-guids"))
            {
                NEXTS("-guids");
                for (int j=0; j<GUIDS; j++)
                {
                    GETGUID(av[i], &guids[j]);
                    if (++i >= ac)
                    {
                        printf("Exactly four GUIDs must be specified.\n");
                        return 1;
                    }
                }
                i--;
                guids_specified = true;
            }
            else if (!strncmp(av[i], "-s", 2))
                silent = true;
            else if (!strncmp(av[i], "-use_image_ps", 2))
                use_image_ps = true;
            else if (!strncmp(av[i], "-nofs", 5))
                burn_failsafe = false;
            else if (!strncmp(av[i], "-y", 2))
                _assume_yes = true;
            else if (!strncmp(av[i], "-h", 2) ||  !strncmp(av[i], "--h", 3))
            {
                usage(av[0]);
                return 1;
            }
            else
            {
                printf("Invalid switch \"%s\" is specified.\n", av[i]);
                return 1;
            }
        }
        else
        {
            //
            // Commands
            // --------
            //
            if (*av[i] == 'b')
            {
                //
                // BURN
                //

                // Device
                if (!device)
                {
                    printf("For burn command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Image - check, open and verify
                if (!image_fname)
                {
                    printf("For burn command \"-image\" switch must be specified.\n");
                    return 1;
                }
                FImage         fim;
                if (!fim.open(image_fname))
                {
                    printf("*** ERROR *** %s\n", fim._err);
                    return 1;
                }
                bool old_silent = _silent;
                _silent = true;
                if (!Verify(fim))
                {
                    printf("Not a valid image\n");
                    return 1;
                }

		// Check that the flash sector size is well defined in the image
		if (fim.get_sector_size() && (fim.get_sector_size() != f.get_sector_size())) {
                    printf("Flash sector size(0x%x) differs from sector size defined in image (0x%x)\n",
			   f.get_sector_size(),
			   fim.get_sector_size());
                    return 1;
		}

                // Get GUID and VSD info from flash
                memset(vsds, 0, VSD_LEN);

                if (!guids_specified  ||
		     ((!vsd1  ||  !psid)  && !use_image_ps))
                {
                    if (!RevisionInfo(f, guids, &vsds[0], &fs_image))
                        return 1;
                }

                // Patch GUIDS
                if (guids_specified)
                {
                    if (!pathGUIDs(fim, guids, isatty(0) != 0))
                        return 1;
                }
                else
                {
                    if (!pathGUIDs(fim, guids, false))
                        return 1;
                }

                // Patch VSD
                if (vsd1)
                    strncpy(&vsds[0], vsd1, VSD_OFFS);
                if (psid)
                    strncpy(&vsds[VSD_OFFS], psid, VSD_LAST);
                if (_image_is_full && !use_image_ps)
                    if (!patchVSD(fim, &vsds[0], &vsds[VSD_OFFS]))
                        return 1;

                // Burn it
                _silent = old_silent;
                if (burn_failsafe)
                {
                    // Failsafe burn
                    if (!_image_is_full)
                    {
                        printf("\nIt is impossible to burn a short image in a failsafe mode.\n");
                        printf("If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                        printf("Otherwise, to burn in the failsafe mode, you need to specify the full image\n");
                        return 1;
                    }

                    // FS burn
                    if (!f.FailSafe_burn(fim.getBuf(), fim.getBufLength(),
                                              !silent))
                    {
                        printf("*** ERROR *** %s\n", f._err);
                        printf("It is impossible to burn this image in a failsafe mode.\n");
                        printf("If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                        return 1;
                    }
                }
                else
                {
                    //
                    // Not failsafe (sequential) burn
                    //

                    // Ask is it OK
                    printf("\nBurn process will not be failsafe. No checks are performed\n");
                    printf("and ALL flash, including Invariant Sector will be overwritten.\n");
                    printf("If this process fails computer may remain in unoperatable state.\n");
                    printf("\nAre you sure ? (y/n) [n] : ");
                    if (_assume_yes)
                        printf("y\n");
                    else
                    {
                        fflush(stdout);
                        char c = getchar();
                        if (c != '\n')
                            while (getchar() != '\n');
                        if (c != 'y')
                            return 1;
                    }

                    // Non FS burn
                    if (!f.write_image(0, fim.getBuf(), fim.getBufLength(),
                                       !silent))
                    {
                        report("\n");
                        printf("*** ERROR *** %s\n", f._err);
                        return 1;
                    }
                    report("\n");
                }
            }
            else if (*av[i] == 'e')
            {
                //
                // ERASE SECTOR <ADDR>
                //     Parameters: <ADDR>
                //
                u_int32_t    addr;
                char         *endp;

                // Device
                if (!device)
                {
                    printf("For erase command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Address of sector to erase
                NEXTC("<ADDR>", "erase");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }

                // Erase
                if (!f.erase_sector(addr))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
            }
            else if (*av[i] == 'q')
            {
                // QUERY
                if (device)
                    RevisionInfo(f, guids, 0, &fs_image);
                else if (image_fname)
                {
                    FImage         fim;
                    if (!fim.open(image_fname))
                    {
                        printf("*** ERROR *** %s\n", fim._err);
                        return 1;
                    }
                    RevisionInfo(fim, guids, 0, &fs_image);
                }
                else
                {
                    printf("For query command \"-device\" or \"-image\" switch must be specified.\n");
                    return 1;
                }
            }
            else if (!strcmp(av[i], "rb"))
            {
                // READ BLOCK
                //     Parameters:  <ADDR> <LENGTH> [OUT_FILENAME]
	        //     if OUT_FILENAME is given, binari read block is stored
		//     in the given file. Otherwise, data is printed to screen.
                u_int32_t    addr, length;
                u_int8_t     *data;
                char         *endp;

		bool         to_file = false;

                // Device
                if (!device)
                {
                    printf("For rb command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Address and length
                NEXTC("<ADDR>", "rb");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }
                NEXTC("<LENGTH>", "rb");
                length = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid length \"%s\"\n", av[i]);
                    return 1;
                }
                data = new u_int8_t[length];

                // Output file
                int fd = -1;
		
		if (i + 2 == ac)  
		    to_file = true;

		if (to_file) {
		    NEXTC("<OUT_FILENAME>", "rb");
		    if ((fd = open(av[i], O_WRONLY | O_CREAT | O_BINARY, 0666)) < 0)
		    {
                        fprintf(stderr, "Can't open ");
			perror(av[i]);
			return 1;
		    }
#ifndef __WIN__
		    if (ftruncate(fd, 0) < 0)
		    {
			fprintf(stderr, "Can't truncate ");
			perror(av[i]);
			return 1;
		    }
#endif
		}

                // Read flash
                if (!f.read(addr, data, length))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }

                if (to_file) {
		    // Write output
		    if (write(fd, data, length) != (int)length)
		    {
		        perror("Write error");
			return 1;
		    }
		    close(fd);
		} 
		else  
		{
		    const u_int32_t IN_LINE = 4;
		    for (u_int32_t i = 0; i < length ; i++) {
		        if ((i % IN_LINE) == 0) {
			    printf("0x%06x:", addr + i);
			}
		    
			printf(" %02x", data[i]);
		    
			if (i > 0 && ((i + 1) % IN_LINE) == 0 ) {
			    printf("\n");
			}
		    }
		}
                delete [] data;
            }
            else if (!strcmp(av[i], "rw"))
            {
                // READ DWORD <ADDR>
                //     Parameters: <ADDR>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device)
                {
                    printf("For rw command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Address
                NEXTC("<ADDR>", "rw");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }

                // Read
                if (!f.read(addr, &data))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
                printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));
            }
            else if (*av[i] == 'v')
            {
                // VERIFY
                if (device)
                    Verify(f);
                else if (image_fname)
                {
                    FImage         fim;
                    if (!fim.open(image_fname))
                    {
                        printf("*** ERROR *** %s\n", fim._err);
                        return 1;
                    }
                    Verify(fim);
                }
                else
                {
                    printf("For verify command \"-device\" or \"-image\" switch must be specified.\n");
                    return 1;
                }
            }
            else if (!strcmp(av[i], "wb"))
            {
                // WRITE BLOCK
                //     Parameters:  <IN_FILENAME> <ADDR>
                u_int32_t    addr, length;
                u_int8_t     *data;
                char         *endp;

                // Device
                if (!device)
                {
                    printf("For wb command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Input file
                int         fd;
                struct stat statbuf;
                NEXTC("<IN_FILENAME>", "wb");
                if ((fd = open(av[i], O_RDONLY | O_BINARY)) < 0)
                {
                    fprintf(stderr, "Can't open ");
                    perror(av[i]);
                    return 1;
                }
                if (fstat(fd, &statbuf) < 0)
                {
                    fprintf(stderr, "Can't stat ");
                    perror(av[i]);
                    return 1;
                }
                length = statbuf.st_size;
                data = new u_int8_t[length];

                // Address
                NEXTC("<ADDR>", "wb");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }

                // Read file
                if (read(fd, data, length) != (int)length)
                {
                    perror("Read error");
                    return 1;
                }

                // Write flash
                if (!f.write_image(addr, data, length, !silent))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }

                close(fd);
                delete [] data;
            }
            else if (!strcmp(av[i], "ww"))
            {
                // WRITE DWORD
                //     Parameters: <ADDR> <DATA>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device)
                {
                    printf("For ww command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Address and data
                NEXTC("<ADDR>", "ww");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }
                NEXTC("<DATA>", "ww");
                data = __cpu_to_be32(strtoul(av[i], &endp, 0));
                if (*endp)
                {
                    printf("Invalid data \"%s\"\n", av[i]);
                    return 1;
                }

                f.curr_sector = 0xffffffff;  // First time erase sector
                if (!f.write(addr, data))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
            }
            else if (!strcmp(av[i], "wwne"))
            {
                // WRITE DWORD WITHOUT ERASE
                //     Parameters: <ADDR> <DATA>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device)
                {
                    printf("For wwne command \"-device\" switch must be specified.\n");
                    return 1;
                }

                // Address and data
                NEXTC("<ADDR>", "wwne");
                addr = strtoul(av[i], &endp, 0);
                if (*endp)
                {
                    printf("Invalid address \"%s\"\n", av[i]);
                    return 1;
                }
                NEXTC("<DATA>", "wwne");
                data = __cpu_to_be32(strtoul(av[i], &endp, 0));
                if (*endp)
                {
                    printf("Invalid data \"%s\"\n", av[i]);
                    return 1;
                }

                if (!f.write(addr, &data, 4, true, true))
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
            }
            else if (!strcmp(av[i], "cfi"))
            {
                // CFI (COMMON FLASH INTERFACE) QUERY


                // Device
                if (!device)
                {
                    printf("For cfi command \"-device\" switch must be specified.\n");
                    return 1;
                }
  
                if (!f.query_cfi())
                {
                    printf("*** ERROR *** %s\n", f._err);
                    return 1;
                }
            }
	    else
            {
                printf("Invalid command \"%s\".\n", av[i]);
                return 1;
            }

        }
    }

    return 0;
}
