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
 *  Version: $Id: flint.cpp 4279 2008-03-19 09:47:09Z orenk $
 *
 */


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

#ifndef NO_ZLIB
#include <zlib.h>
#endif

#include <signal.h>

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

#else // Linux GCC 

#include <byteswap.h>
#include <endian.h>
#include <alloca.h>
#include <netinet/in.h>
#include <unistd.h>

#endif // __DJGPP__

#else // __WIN__

//
// Windows (Under DDK)
//

#include <io.h>
#include <Winsock2.h>

// Sleep adaptor
#define	usleep(x) Sleep((x)/1000)
#define sleep(x)  Sleep((x)*1000)

#define vsnprintf      _vsnprintf
#define strtoull       _strtoui64
#define isatty         _isatty

#define COMP_CDECL     __cdecl

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __BYTE_ORDER __LITTLE_ENDIAN


#if __BYTE_ORDER == __LITTLE_ENDIAN
#define bswap_32(x) ntohl(x)
#else
#error windows is assumed to run a on little endian architecture
#endif

#endif // __WIN__

#include <memory>
#include <vector>

#include <mflash.h>


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

#ifdef VERSION_ID
//char* _versionID = VERSION_ID ;
#define __VFSTR(x) 			#x
#define _VFSTR(x) 			__VFSTR(x)
char* _versionID = _VFSTR( VERSION_ID ) ;
#else
char* _versionID = "MFT 2.0.1 , BUILD 20080320-1354";
#endif

char* _svnID     = "$Revision: 4279 $";

#ifndef __be32_to_cpu
    #define __be32_to_cpu(x) ntohl(x)
    #ifndef bswap_32
	#define bswap_32(x) (htonl(x))
    #endif
#endif
#ifndef __cpu_to_be32
    #define __cpu_to_be32(x) htonl(x)
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
    #ifndef __cpu_to_le32
        #define  __cpu_to_le32(x) (x)
    #endif
    #ifndef __le32_to_cpu
        #define  __le32_to_cpu(x) (x)
    #endif
#elif __BYTE_ORDER == __BIG_ENDIAN
    #ifndef __cpu_to_le32
        #define  __cpu_to_le32(x) bswap_32(x)
    #endif
    #ifndef __le32_to_cpu
        #define  __le32_to_cpu(x) bswap_32(x)
    #endif
#else
    #ifndef __cpu_to_le32
        #define  __cpu_to_le32(x) bswap_32(__cpu_to_be32(x))
    #endif
    #ifndef __le32_to_cpu
        #define  __le32_to_cpu(x) __be32_to_cpu(bswap_32(x))
    #endif
#endif


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                     Miscellaneous global stuff                     //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
typedef struct guid {
    u_int32_t h;
    u_int32_t l;
} guid_t;

static inline void be_guid_to_cpu(guid_t* to, guid_t* from) {
    to->h=__be32_to_cpu(from->h);
    to->l=__be32_to_cpu(from->l);
}

static inline void cpu_to_be_guid(guid_t* to, guid_t* from) {
    to->h=__cpu_to_be32(from->h);
    to->l=__cpu_to_be32(from->l);
}

#define GUID_FORMAT "%8.8x%8.8x"
#define MAC_FORMAT  "%4.4x%8.8x"
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
    guid_t *p = s;                              \
    for (unsigned ii=0; ii<sizeof(s)/sizeof(guid_t); ii++,p++) \
        be_guid_to_cpu(p,p);                                   \
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
#define CHECKLS(f,o,s,p) do { if (!checkList(f,o,s,p)) return false; } while(0)
#define READ4(f,o,d,p) do { if (!f.read(o,d)) {  \
    return errmsg("%s - read error (%s)\n", p, f.err()); }} while (0)
#define READBUF(f,o,d,l,p) do { if (!f.read(o,d,l)) { \
    return errmsg("%s - read error (%s)\n", p, f.err()); }} while (0)


class ErrMsg
{
public:
    ErrMsg() : _err(0)       {                           }
    ~ErrMsg()                { err_clear();              }
    const char *err() const  { return _err;              }
    void       err_clear()   { delete [] _err; _err = 0; }

protected:
    
    char *vprint(const char *format, va_list args)
    {
	const int INIT_VAL = 1024;
	int       max_str, max_buf = INIT_VAL;
	char      *out_buf;
	
	while (1)
	{
	    out_buf = new char[max_buf];
	    max_str = max_buf - 1;
	    
	    if (vsnprintf(out_buf, max_str, format, args) < max_str)
		return out_buf;
	    delete [] out_buf;
	    max_buf *= 2;
	}
    } 


    bool errmsg(const char *format, ...)
#ifdef __GNUC__
        __attribute__ ((format (printf, 2, 3)))
#endif
    ;    

private:

    char       *_err;
};


bool ErrMsg::errmsg(const char *format, ...) {
    va_list   args;

    char* prev_err = _err;

    va_start(args, format);
    _err = vprint(format, args);
    va_end(args);

    delete[] prev_err;

    return false;
}   


enum {
    SIGNATURE          = 0x5a445a44,
    MELLANOX_VENDOR_ID = 0x15b3
};
struct PS {
    u_int32_t fi_addr;
    u_int32_t fi_size;
    u_int32_t signature;
    u_int32_t fw_reserved[5];
    u_int32_t vsd[52];
    u_int32_t psid[4];
    u_int32_t branch_to;
    u_int32_t crc016;
};

enum {
    H_FIRST     =  1, 
    H_DDR       =  1, 
    H_CNF       =  2,
    H_JMP       =  3,
    H_EMT       =  4,
    H_ROM       =  5,
    H_GUID      =  6,
    H_BOARD_ID  =  7, 
    H_USER_DATA =  8,
    H_FW_CONF   =  9,
    H_IMG_INFO  = 10,
    H_DDRZ      = 11,
    H_LAST
};

const char* g_sectNames[] = {
    "UNKNOWN (0 - Reserved)",
    "DDR"             , 
    "Configuration"   ,
    "Jump addresses"  ,
    "EMT Service"     ,
    "ROM"             ,
    "GUID"            ,
    "BOARD ID"        , 
    "User Data"       ,
    "FW Configuration",
    "Image Info"      ,
    "DDRZ"
};


struct GPH {
    u_int32_t type;
    u_int32_t size;
    u_int32_t param;
    u_int32_t next;
};

#define MAX_SECTION_SIZE 0x400000

const u_int32_t BOARD_ID_BSN_LEN=64;
const u_int32_t BOARD_ID_BID_LEN=32;
const u_int32_t BOARD_ID_PID=7;

struct BOARD_ID {
    char      bsn[BOARD_ID_BSN_LEN];
    char      bid[BOARD_ID_BID_LEN];
};

int  const VSD_LEN  = 208;
int  const PSID_LEN = 16;
int  const PRODUCT_VER_LEN = 16;

//
// TODO: Remove the below globals to class members.
//
bool _print_crc = false;
bool _silent = false;
bool _assume_yes = false;
bool _assume_no = false;
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

    if (!_silent) {
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
} // report

void report_erase(const char *format, ...)
{
    va_list  args;
    char buf[256];
    int i;
    int len;

    if (_silent)
	return;

    va_start(args, format);
    vsnprintf(buf, sizeof buf, format, args);
    va_end(args);
    
    len = strlen(buf);
    for(i=0; i < len; ++i)
	printf("\b");
} // report_erase


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        CRC16 CALCULATION                           //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
class Crc16 {
public:
    Crc16(bool d = false) : _debug(d) { clear();}
    u_int16_t      get()              { return _crc;}
    void           clear()            { _crc = 0xffff;}
    void           operator<<(u_int32_t val) { add(val);}
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
    for (int i=0; i<32; i++) {
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
    for (int i=0; i<16; i++) {
        if (_crc & 0x8000)
            _crc=((_crc<<1)  ^  0x100b) & 0xffff;
        else
            _crc=(_crc<<1) & 0xffff;
    }

    // Revert 16 low bits
    _crc = _crc ^ 0xffff;

} // Crc16::finish


//////////////////////////////////////////////////////////////////////
//
//  class u_int32_ba (bit access):
//  A uint wrapper which allows easy access to bit/range of bits.
//
//  Usage example:
//     u_int32_ba a;
//     Read_Word( Table.reg ,&a);
//     int upper_byte = a.range(31,24);
//     if (a[15])
//        cout << " Bit 15 is 1 \n";
//     else
//        cout << " Bit 15 is 0 \n";
//
//     u_int32_ba b;
//     b.range(15,12) = 0xa;
//     b[31]          = 1;     // b == 0x8000a000
//     Write_Word( Table.reg ,b);
//
//////////////////////////////////////////////////////////////////////


class u_int32_ba {
public:
    u_int32_ba(u_int32_t i = 0) :
    _bits(i),
    _rbits(_bits),
    _sptr(0),
    _eptr(31)    {}

    u_int32_ba  operator[](u_int32_t idx) {return range((u_int8_t)idx,(u_int8_t)idx);}
    u_int32_ba& operator= (u_int32_t i)   {_rbits = ((i << _sptr) & mask()) | (_rbits & ~mask()); return *this;}
    u_int32_t*  operator& ()              {return &_bits;}
    operator    u_int32_t ()              {return((mask() & _rbits) >> _sptr);}

    u_int32_ba  range     (u_int8_t eptr, 
                           u_int8_t sptr) {return u_int32_ba(*this,eptr,sptr);}

private:
    u_int32_ba(u_int32_ba& other, u_int8_t eptr, u_int8_t sptr) :
    _bits(other._bits),
    _rbits(other._bits),
    _sptr(sptr),
    _eptr(eptr) {}

    u_int32_t  mask       () {
        u_int32_t s_msk = (u_int32_t)-1; // start mask
        u_int32_t e_msk = (u_int32_t)-1; // end mask

        s_msk = (s_msk << _sptr);
        e_msk = (_eptr >= (sizeof(_bits)*8-1)) ? e_msk : ~(e_msk << (_eptr+1));

        return(s_msk & e_msk);
    };

    u_int32_t  _bits;
    u_int32_t& _rbits;

    u_int8_t   _sptr;
    u_int8_t   _eptr;
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

class Aligner {
public:
    Aligner(u_int32_t log2_alignment_size) :
        _log2_alignment_size(log2_alignment_size),
        _alignment_size(1 << log2_alignment_size),
        _alignment_mask(_alignment_size - 1)
    {
        if (_log2_alignment_size == 0) {
            _log2_alignment_size = 31;
            _alignment_size      = 1 << _log2_alignment_size;
            _alignment_mask      = _alignment_size - 1;
        }
    }
    
    void Init        (u_int32_t  addr, u_int32_t  size) {
        _curr_addr = addr;
        _curr_size = size;
    }

    bool GetNextChunk(u_int32_t& chunk_addr, u_int32_t& chunk_size) {
        if (_curr_size == 0) {
            return false;
        }

        chunk_addr = _curr_addr;

        if ( (_curr_addr               >> _log2_alignment_size) != 
            ((_curr_addr + _curr_size) >> _log2_alignment_size)) {
            // Next chunk crosses alignment boundary
            chunk_size = _alignment_size - (_curr_addr & _alignment_mask);
        } else {
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




////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        FLASH ACCESS                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////

// Common base class for Flash and for FImage


class FBase : public ErrMsg{
public:
    FBase(bool is_flash) :
        _log2_chunk_size(0), 
        _is_flash(is_flash) {}
    virtual ~FBase()  {}

    virtual bool open(const char *, bool)                  {return false;}
    virtual void close()                                   = 0;
    virtual bool read(u_int32_t addr, u_int32_t *data)     = 0;
    virtual bool read(u_int32_t addr, void *data, int len,
                      bool verbose=false)                  = 0;

    virtual u_int32_t get_sector_size()                    = 0;
    virtual u_int32_t get_size()                           = 0;

    virtual u_int32_t get_dev_id()                         = 0;

    bool              is_flash() {return _is_flash;};

    virtual void set_address_convertor(u_int32_t log2_chunk_size, bool is_image_in_odd_chunks) {
        _log2_chunk_size = log2_chunk_size;
        _is_image_in_odd_chunks = is_image_in_odd_chunks;
    }

    enum {
        MAX_FLASH = 4*1048576
    };

protected:

    // Address translation functions for ConnectX.
    // Translate between contiguous "logical" addresses 

    // If Failsafe zebra mapping is enabled:

    // Result is concatenation of:
    // The lower log2_chunk_size bits of the cons_addr
    // The is_image_in_odd_chunk bit
    // The remaining upper bits of the cons_addr

    u_int32_t cont2phys(u_int32_t cont_addr) {
        u_int32_t result;
        if (_log2_chunk_size) {
            result  = (cont_addr       & (0xffffffff >> (32 - _log2_chunk_size))) |
                      (_is_image_in_odd_chunks       << _log2_chunk_size)         |
                     ((cont_addr << 1) & (0xffffffff << (_log2_chunk_size + 1)));
        } else {
            result = cont_addr;
        }
        return result;
    }
    
    u_int32_t phys2cont(u_int32_t phys_addr) {
        u_int32_t result;
        if (_log2_chunk_size) {
            result =  (phys_addr       & (0xffffffff >> (32 - _log2_chunk_size)))  |
                     ((phys_addr >> 1) & (0xffffffff << (     _log2_chunk_size)));
        } else {
            result = phys_addr;
        }
        return result;
    }

    bool       _is_image_in_odd_chunks;
    u_int32_t  _log2_chunk_size;

    const bool _is_flash;

};

// Flash image (RO)
class FImage : public FBase {
public:
    FImage() :  FBase(false), _buf(0) {}
    virtual ~FImage() { close();}

    u_int32_t    *getBuf()      { return _buf;}
    u_int32_t    getBufLength() { return _len;}
    virtual bool open(const char *fname, bool read_only = false);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t *data);
    virtual bool read(u_int32_t addr, void *data, int len, bool verbose=false);

    virtual u_int32_t get_sector_size();
    virtual u_int32_t get_size()     { return  getBufLength();}
    virtual u_int32_t get_dev_id()   { return  0;}

private:
    u_int32_t *_buf;
    u_int32_t _len;
};

// 
// Flash access (R/W)
//
class Flash : public FBase {
public:
    Flash() :
        FBase(true),
        _mfl(0),
        _curr_sector(0xffffffff),
        _port_num(0)
     {}

    virtual ~Flash()  { close();};

    // FBase Interface

    virtual bool open          (const char *device,
				bool force_lock = false,
                                bool read_only  = false);

    virtual void close         ();

    virtual bool read          (u_int32_t addr, 
                                u_int32_t *data);

    virtual bool read          (u_int32_t addr, 
                                void*     data, 
                                int       len, 
                                bool      verbose = false);

    bool         cr_write      (u_int32_t addr,
                                u_int32_t data) {return mf_cr_write(_mfl, addr, data) == MFE_OK;}

    //
    // Flash Interface
    //

    u_int32_t get_sector_size        ()  {return _attr.sector_size; } 
    u_int32_t get_size               ()  {return _attr.size;}
    
    u_int32_t get_dev_id             ()  {return _attr.hw_dev_id;}

    u_int32_t get_port_num           ()  {return _port_num;}

    // Write and Erase functions are performed by the Command Set

    virtual bool erase_sector  (u_int32_t addr);

    virtual bool write         (u_int32_t addr, 
                                void*     data, 
                                int       cnt,
                                bool      noerase = false);

    virtual bool write         (u_int32_t addr, 
                                u_int32_t data);

    bool         print_attr();
    bool         print_attr_old_format();

    enum {
        TRANS = 4096
    };

    static bool _byte_mode;

#ifndef _MSC_VER
protected:
#endif

    mflash*    _mfl;
    flash_attr _attr;

    u_int32_t  _curr_sector;
    u_int32_t  _port_num;
};


////////////////////////////////////////////////////////////////////////
//
// FImage Class Implementation
//
////////////////////////////////////////////////////////////////////////

bool FImage::open(const char *fname, bool read_only)
{
    int                fsize;
    int                r_cnt;
    FILE              *fh;

    read_only = true;  // FImage can be opened only for read

    fh = fopen(fname, "rb");

    if (!fh) {
        return errmsg("Can not open file \"%s\" - %s\n", fname, strerror(errno));
    }

    // Get the file size:
    if (fseek(fh, 0, SEEK_END) < 0) {
        return errmsg("Can not get file size for \"%s\" - %s\n", fname, strerror(errno));
    }

    fsize = ftell(fh);
    if (fsize < 0) {
        return errmsg("Can not get file size for \"%s\" - %s\n", fname, strerror(errno));
    }
    rewind(fh);

    //printf("-D- %s size is %d\n", fname, fsize);
    if (fsize & 0x3) {
        return errmsg("Image size should be 4-bytes aligned. Make sure file %s is in the right format (binary image)",
		      fname);
    }

    _buf = new u_int32_t[fsize/4];
    if ((r_cnt = fread(_buf, 1, fsize, fh)) != fsize) {
        if (r_cnt < 0)
            return errmsg("Read error on file \"%s\" - %s\n",fname, strerror(errno));
        else
            return errmsg("Read error on file \"%s\" - read only %d bytes (from %ld)\n",
			  fname, r_cnt, (unsigned long)fsize);
    }

    _len = fsize;
    fclose(fh);

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
    return read(addr, data, 4);
} // FImage::read

////////////////////////////////////////////////////////////////////////
bool FImage::read(u_int32_t addr, void *data, int len, bool)
{

    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }
    if (len & 0x3) {
        return errmsg("Length should be 4-bytes aligned.");
    }
    if (!_buf) {
	return errmsg("read() when not opened");
    }

    if (cont2phys(addr + len) > _len) {
        return errmsg("Reading 0x%x bytes from %saddress 0x%x is out of image limits (0x%x bytes)", 
		      len,
                      _log2_chunk_size ? "physical " : "",
                      addr, 
                      _len);
    }

    u_int32_t chunk_addr;
    u_int32_t chunk_size;    
    Aligner align(_log2_chunk_size);
    align.Init (addr, len);
    while (align.GetNextChunk(chunk_addr, chunk_size)) {
        u_int32_t phys_addr = cont2phys(chunk_addr);

        memcpy((u_int8_t*)data + (chunk_addr - addr), 
               (u_int8_t*)_buf +  phys_addr, 
                chunk_size);
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
    if (signature == SIGNATURE) {
        // full image:
        read(0x14, &log2_sector_sz_ptr);
        TOCPU1(log2_sector_sz_ptr);
        log2_sector_sz_ptr &= 0xffff;

        read(0x30 + log2_sector_sz_ptr, &log2_sector_sz);
        TOCPU1(log2_sector_sz);
        log2_sector_sz &= 0xffff;

        return(1 << log2_sector_sz);

    } else {
        return 0;
    }
}



////////////////////////////////////////////////////////////////////////
//
// Flash Class Implementation
//
////////////////////////////////////////////////////////////////////////


bool Flash::_byte_mode = false;

////////////////////////////////////////////////////////////////////////
bool Flash::open(const char *device, bool force_lock, bool read_only)
{
    // Open device
    int rc;
    read_only = false;

    rc = mf_open(&_mfl, device);

    if ((rc == MFE_SEM_LOCKED) && force_lock) {
        report("Warning: Taking flash lock even though semaphore is set.\n");
        rc = mf_open_ignore_lock(_mfl);
    }

    if (rc == MFE_SEM_LOCKED) {
        return errmsg("Can not obtain Flash semaphore (63). You can run \"flint -clear_semaphore -d <device>\" to force semaphore unlock. See help for details.");
    } else 
        if (rc != MFE_OK) {
        return errmsg("%s %s", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
    }

    rc = mf_get_attr(_mfl, &_attr);
    if (rc != MFE_OK) {
        return errmsg("Failed getting flash attributes for device %s: %s", device,  mf_err2str(rc));
    }  

    if (_attr.hw_dev_id == 25204 || _attr.hw_dev_id == 24204) {
        _port_num = 1;
    } else {
        _port_num = 2;
    }

    if (_byte_mode) {
        rc = mf_set_opt(_mfl, MFO_AMD_BYTE_MODE, 1); 
        if (rc != MFE_OK) {
            return errmsg("Failed setting byte mode fore device %s: %s", device,  mf_err2str(rc));
        }
    }

    return true;
} // Flash::open

////////////////////////////////////////////////////////////////////////
void Flash::close()
{
    if (!_mfl)
        return;

    mf_close(_mfl); 
    _mfl = 0;
} // Flash::close


bool Flash::read(u_int32_t addr, 
                 u_int32_t *data) {
    int rc;

    u_int32_t phys_addr = cont2phys(addr);
    rc = mf_read(_mfl, phys_addr, 4, (u_int8_t*)data);
    if (rc != MFE_OK) {
        return errmsg("Flash read failed at address %s%x : %s",
                      _log2_chunk_size ? "physical " : "",
                      addr,
                      mf_err2str(rc));
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, void *data, int len, bool verbose)
{
    int rc;
    u_int32_t  perc = 0xffffffff;

    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }
    if (len & 0x3) {
        return errmsg("Length should be 4-bytes aligned.");
    }

    // Report
    if (verbose) {
        printf("000%%");
        fflush(stdout);
    }

    // Much better perf for read in a single chunk. need to work on progress report though.
    bool read_in_single_chunk = true;

    if (read_in_single_chunk) {
        u_int32_t chunk_addr;
        u_int32_t chunk_size;

        Aligner align(_log2_chunk_size);
        align.Init (addr, len);
        while (align.GetNextChunk(chunk_addr, chunk_size)) {
            u_int32_t phys_addr = cont2phys(chunk_addr);

            rc = mf_read(_mfl, phys_addr, chunk_size, ((u_int8_t*)data) + chunk_addr - addr);
            if (rc != MFE_OK) {
                return errmsg("Flash read failed at address %s%x : %s",
                              _log2_chunk_size ? "physical " : "",
                              chunk_addr,
                              mf_err2str(rc));
            }
        }
    
    } else {
        u_int32_t *p = (u_int32_t *)data;
        for (int i=0; i<len/4; i++) {
            if (!read(addr, p++))
                return false;
            
            addr += 4;

            // Report
            if (verbose) {
                u_int32_t new_perc = (i * 100) / len;
                if (new_perc != perc) {
                    printf("\b\b\b\b%03d%%", new_perc);
                    fflush(stdout);
                    perc = new_perc;
                }
            }
        }
    }
    // Report
    if (verbose) {
        printf("\b\b\b\b100%%");
        fflush(stdout);
    }

    return true;
} // Flash::read


////////////////////////////////////////////////////////////////////////
bool Flash::write  (u_int32_t addr, 
		    void*     data, 
		    int       cnt,
		    bool      noerase)
{
    
    // FIX:
    noerase = _no_erase || noerase;    

    if (!_mfl) {
        return errmsg("Not opened");
    }
    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }


    if (cont2phys(addr + cnt) > get_size()) {
	return errmsg( 
	    "Trying to write %d bytes to address 0x%x, which exceeds flash size (0x%x).",
	    cnt, 
	    addr,
	    get_size());  
    }
    
    u_int8_t         *p = (u_int8_t *)data;
    u_int32_t sect_size = get_sector_size();

    u_int32_t chunk_addr;
    u_int32_t chunk_size;

    u_int32_t first_set;
    for (first_set = 0; ((sect_size >> first_set) & 1) == 0; first_set++ )
        ;

    Aligner align(first_set);
    align.Init (addr, cnt);
    while (align.GetNextChunk(chunk_addr, chunk_size)) {
        // Write / Erase in sector_size alligned chunks
        int rc;
        
        if (!noerase) {
            u_int32_t sector = (chunk_addr / sect_size) * sect_size;
            if (sector != _curr_sector) {
                _curr_sector = sector;
                if (!erase_sector(_curr_sector))
                    return false;
            }
        }

        if (_no_burn)
            continue;

        // Actual write:
        u_int32_t phys_addr = cont2phys(chunk_addr);
        rc = mf_write(_mfl, phys_addr, chunk_size, p);
        if (rc != MFE_OK) {
            return errmsg("Flash write of %d bytes to address %s0x%x failed: %s",
                          chunk_size,
                          _log2_chunk_size ? "physical " : "",
                          chunk_addr,
                          mf_err2str(rc));
        }

        // Loop advance
        p    += chunk_size;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr, u_int32_t data)
{
    if (!_mfl) {
	return errmsg("Not opened");
    }
    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }

    u_int32_t word;

    u_int32_t sector_size = _attr.sector_size;
    u_int32_t sector_mask = ~(sector_size - 1);

    u_int32_t sector = addr & sector_mask;
    u_int32_t word_in_sector = (addr & ~sector_mask)/sizeof(u_int32_t);

    if (!read(addr, &word))
        return false;
    if (word == data)
        return true;   // already there

    vector<u_int32_t> buff(sector_size/sizeof(u_int32_t));
    if (!read(sector, &buff[0] , sector_size))
        return false;
    buff[word_in_sector] = data;
    return write(sector, &buff[0], sector_size);
} // Flash::write


bool Flash::erase_sector  (u_int32_t addr) {
    int rc;

    u_int32_t phys_addr = cont2phys(addr);
    rc = mf_erase_sector(_mfl, phys_addr);
    if (rc != MFE_OK) {
        return errmsg("Flash erase of address 0x%x failed: %s", 
                      phys_addr,
                      mf_err2str(rc));
    }

    return true;
}

bool Flash::print_attr() {
    printf("Flash attributes:\n");
    printf("  HwDevId          %d\n",     _attr.hw_dev_id);
    printf("  TotalSize        0x%x\n",   _attr.size);
    printf("  Banks            0x%x\n",   _attr.size/_attr.bank_size );
    printf("  SectorSize       0x%x\n",   _attr.sector_size );
    printf("  WriteBlockSize   0x%x\n",   _attr.block_write);
    printf("  CmdSet           0x%x\n",   _attr.command_set);

    return true;
}

bool Flash::print_attr_old_format() {
    // Needed for some old tools which parce the size section of the CFI query in oder flint versions:

    int i;
    printf("\n----Sector Organization Parameters-------------------\n\n");

    printf("%-50s ", "Device size:");
    printf("[%8li] bytes, or [%2i] Mbit\n",
           (long int)_attr.size, 
           (int) (_attr.size/((long)0x20000)));

    printf("%-50s ", "Number of erase block regions:");
    printf("%d\n", _attr.num_erase_blocks);

    for (i = 0; i < _attr.num_erase_blocks; i++) {
        printf("  Size:[%8lx] bytes, Mask [%08x], [Number:[%4i]\n",
               _attr.erase_block[i].sector_size,
               _attr.erase_block[i].sector_mask,
               _attr.erase_block[i].num_sectors);
    }
    return true;
}

////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//
// Burn Operations functions
//
////////////////////////////////////////////////////////////////////////

class Operations : public ErrMsg {
public:
    Operations() : _last_image_addr(0), _num_ports(2), _allow_skip_is(false) , _is_cntx(false), _cntx_striped_image(false) {}

    enum {
	GUIDS = 4,
        MACS  = 2,
        MAX_GUIDS = 6
    };

    enum ImageInfoTags {
        II_IiFormatRevision   = 0,
        II_FwVersion          = 1,
        II_FwBuildTime        = 2, 
        II_DeviceType         = 3,
        II_PSID               = 4,
        II_VSD                = 5,
        II_SuppurtedPsids     = 6,
        II_ProductVer         = 7,
        II_VsdVendorId        = 8,
        II_Last               = 9,  // Mark the end of used tag ids
        II_End                = 0xff
    };
    
    struct ImageInfo;

    // Burn operations:
    bool write_image     (Flash& f, u_int32_t addr, void *data, int cnt, bool need_report);
    bool WriteSignature  (Flash& f, u_int32_t image_idx, u_int32_t sig);
    bool repair          (Flash& f, const int from, const int to, bool need_report);
    bool FailSafeBurn    (Flash& f, FImage& fim, bool need_report, bool single_image_burn);
    bool CntxFailSafeBurn(Flash&     f, 
                          FImage&    fim, 
                          bool       need_report, 
                          ImageInfo* flash_info, 
                          ImageInfo* image_info,
                          bool       allow_nofs = false);
    // Image operations:
    bool Verify          (FBase& f, ImageInfo* info = NULL, bool both_images = false);
    bool VerifyCntx      (FBase& f, ImageInfo* info = NULL, bool both_images = false);

    bool LoadAsExpRom    (FBase& f);

    bool DumpConf        (const char* conf_file = NULL);
    bool GetExpRomVersion(ImageInfo* info);

    bool DisplayExpRomInfo(ImageInfo* info);
    bool DisplayImageInfo (ImageInfo* info);

    bool QueryAll        (FBase& f, ImageInfo* info) {return (IsCntx() ||
                                                              (QueryIs(f, info) && 
                                                              (!info->isFailsafe || QueryPs(f, info)))) && 
                                                             QueryImage(f, info);}

    bool getBSN          (char *s, guid_t *guid);
    bool getGUID         (const char *s, guid_t *guid);

    bool patchVSD        (FImage& f, 
                          Operations::ImageInfo* info,
                          const char *user_vsd, 
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid);

    // Misc operations

    bool patchGUIDs      (FImage&    f,
                          ImageInfo* info,
                          bool       patch_guids, 
                          bool       patch_macs, 
                          bool       user_guids,
                          bool       user_macs,
                          guid_t     new_guids[MAX_GUIDS], 
                          guid_t     old_guids[MAX_GUIDS],
                          u_int32_t num_of_old_guids,
                          bool       interactive);

    bool printGUIDs(const char* msg, guid_t guids[MAX_GUIDS], bool print_guids, bool print_macs, bool old_guid_fmt);

    void SetNumPorts     (u_int32_t num_ports) {_num_ports = num_ports;}
    void SetAllowSkipIs  (bool asis)           {_allow_skip_is = asis;}

    // ConnectX methods
    void SetCntxMode     (bool cntx_mode)      {_is_cntx = cntx_mode;}
    void SetCntxStripedImage(bool si)          {_cntx_striped_image = si;}
    bool IsCntx          ()                    {return _is_cntx;}
    bool CheckMac        (u_int64_t mac);

    bool CheckIsCntx     (FBase& f);

    bool CntxIsIb        (u_int32_t devid)     {return (devid == 25408) || // IB SDR
                                                       (devid == 25418) || // IB DDR
                                                       (devid == 25428) || // IB QDR
                                                       (devid == 26418) || // IB DDR
                                                       (devid == 26428) || // IB QDR
                                                       (devid == 25468) || // MP
                                                       (devid == 26478) || // MP
                                                       (devid == 25488);   // MP
    }

    bool CntxIsEth       (u_int32_t devid)     {return (devid == 25448) || // ETH
                                                       (devid == 26448) || // ETH
                                                       (devid == 25468) || // MP
                                                       (devid == 26478) || // MP
                                                       (devid == 25488);   // MP
    }

    bool CntxIsMp        (u_int32_t devid)     {return CntxIsIb(devid) && CntxIsEth(devid);}

    bool ask_user        ();

    // _last_image_addr is set by the Verify() op
    u_int32_t            _last_image_addr;

    // 
    // ImageInfo struct: Everything you wanted to know about the FW image (and was afraid to ask).
    // This struct includes both user's info (psid, dev rev , fwver ...) and tools internal
    // info (images locations, guid ptr ...).
    //
    struct ImageInfo {
        ImageInfo() :
            invSectOk(false),
            psOk(false),
            imageOk(false)
        {
            memset(allImgStart,    0, sizeof(allImgStart));
            memset(guids      , 0xff, sizeof(guids));

            psid[0] = '\0';
            vsd[0]  = '\0';
            for (int i=0; i < II_Last; i++ ) 
                infoOffs[i] = 0;
        }
        
        // *Ok : The exit status of the specific query.
        // Note - invSectOk = true doesnt mean that invariant sector exists, it
        //        only means that the query was OK (and isFailsafe may be false).

        bool         invSectOk;
        bool         psOk;
        bool         imageOk;

        u_int32_t    allImgStart[2];

        bool         isFailsafe;

        // ConnectX:
        // For an image file where the image is marked as FW but actually contiguous, this bit would be cleared. 
        bool         actuallyFailsafe;
        u_int32_t    cntxLog2ChunkSize;

        bool         validImage[2];
        u_int32_t    psStart;
        u_int32_t    imgStart;

        // For ConnectX, guids 4:5 are the cards MAC addresses (if applicable)
        guid_t       guids[MAX_GUIDS];
        u_int32_t    guidPtr;
        u_int32_t    guidNum;

        u_int32_t    infoSectPtr;

        u_int16_t    vsdVendorId;
        char         vsd[VSD_LEN+1];
        char         psid[PSID_LEN+1];
        char         productVer[17];

        u_int8_t     isVer;
        u_int16_t    fwVer[3];        // = {major_ver, minor_ver , sum_minor_ver}
        u_int16_t    fwTime[6];  // = {year, month, day, hour, minute, second}

        u_int16_t    devType;
        u_int8_t     devRev;

        u_int32_t    infoOffs[II_Last];  // Offset of the tag data inside the info section data. 
                                         // Can not be 0 (because of tag header) - 0 means not found.
        bool         expRomFound;
        bool         expRomValidVersion;
        u_int16_t    expRomProductId;    // 0 - invalid.
        u_int16_t    expRomVer[3];
        u_int16_t    expRomDevId;
        u_int8_t     expRomPort;

        bool         magicPatternFound;
    };

    bool FwVerLessThan(u_int16_t r1[3], u_int16_t r2[3]) {
        return (r1[0] < r2[0] ||
                r1[1] < r2[1] ||
                r1[2] < r2[2]);
    }

    enum {CNTX_START_POS_SIZE = 6};

    static const u_int32_t _cntx_image_start_pos[CNTX_START_POS_SIZE];

    static const u_int32_t _cntx_magic_pattern[4];

private:

    bool FailSafe_burn_image   (Flash&       f, 
				void         *data, 
				int          ps_addr, 
				const char*  image_name, 
				int          image_addr,
				int          image_size,
				bool         need_report);

    bool CheckInvariantSector   (Flash& f, u_int32_t *data32, int sect_size);

    bool FailSafe_burn_internal (Flash& f, void *data, int cnt, bool need_report);

    bool checkBoot2             (FBase& f, u_int32_t beg, u_int32_t offs,
		                 u_int32_t& next, const char *pref);

    bool checkGen               (FBase& f, u_int32_t beg,
                                 u_int32_t offs, u_int32_t& next, const char *pref);

    bool checkPS                (FBase& f, u_int32_t offs, u_int32_t& next, const char *pref);

    bool checkList              (FBase& f, u_int32_t offs, u_int32_t fw_start, const char *pref);

    bool extractGUIDptr         (u_int32_t sign, u_int32_t *buf, int buf_len,
				 char *pref, u_int32_t *ind, int *nguids);

    void patchGUIDsSection      (u_int32_t *buf, u_int32_t ind,
				 guid_t guids[GUIDS], int nguids);

    void recalcSectionCrc       (u_int8_t *buf, u_int32_t data_size);

    u_int32_t BSN_subfield      (const char *s, int beg, int len);

    void PatchPs                (u_int8_t*      rawPs, 
                                 const char     vsd[VSD_LEN],
                                 const char     psid[PSID_LEN]   = NULL,
                                 u_int32_t      imageAddr        = 0);

    void PatchInfoSect          (u_int8_t*      rawSect,
                                 u_int32_t      vsdOffs,
                                 const char*    vsd);

    bool QueryIs                (FBase& f,  ImageInfo* info);
    bool QueryPs                (FBase& f,  ImageInfo* info);
    bool QueryImage             (FBase& f,  ImageInfo* info);

    bool CntxFindMagicPattern   (FBase& f,  u_int32_t addr);
    bool CntxFindAllImageStart  (FBase& f,  u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images);
    bool CntxGetFsData          (FBase& f,  u_int32_t img_addr, bool& fs_en, u_int32_t& log2chunk_size);

    bool ParseInfoSect          (u_int8_t* buff, u_int32_t byteSize, ImageInfo *info);

    u_int32_t _num_ports;
    bool      _allow_skip_is;
    bool      _is_cntx;
    bool      _cntx_striped_image;

    std::vector<u_int8_t>  _fw_conf_sect;
    std::vector<u_int8_t>  _rom_sect;
};


const u_int32_t Operations::_cntx_magic_pattern[4] = {
    0x4D544657,   // Ascii of "MTFW" 
    0x8CDFD000,   // Random data     
    0xDEAD9270,                      
    0x4154BEEF
};

const u_int32_t Operations::_cntx_image_start_pos[Operations::CNTX_START_POS_SIZE] = {
           0,
     0x10000,
     0x20000,
     0x40000,
     0x80000,
    0x100000
};


//
// Asks user a yes/no question. 
// Returns true if user chose Y, false if user chose N.
//

bool Operations::ask_user() {
    printf("\n Do you want to continue ? (y/n) [n] : ");
    if (_assume_yes)
        printf("y\n");
    else {
        char ansbuff[32];
        ansbuff[0] = '\0';
        if (_assume_no) {
            printf("n\n");
            return errmsg("-no flag is set");
        }

        if (!isatty(0)) {
            return errmsg("Not on tty - Can not interact. assuming \"no\"");
        }
        fflush(stdout);
        fgets(ansbuff, 30, stdin);

        if (  strcmp(ansbuff, "y\n") &&
              strcmp(ansbuff, "Y\n") &&
              strcmp(ansbuff, "yes\n") &&
              strcmp(ansbuff, "Yes\n") &&
              strcmp(ansbuff, "YES\n"))
            return errmsg("Aborted by user");
    }
    return true;
}

bool Operations::write_image(Flash& f, u_int32_t addr, void *data, int cnt, bool need_report)
{
    u_int8_t   *p = (u_int8_t *)data;
    u_int32_t  curr_addr = addr;
    u_int32_t  towrite = cnt;
    u_int32_t  perc = 0xffffffff;

    //f.curr_sector = 0xffffffff;  // Erase sector first time
    if (need_report) {
        printf("000%%");
        fflush(stdout);
    }


    while (towrite) {
        // Write
        int trans = (towrite > (int)Flash::TRANS) ? (int)Flash::TRANS : towrite;
        if (!f.write(curr_addr, p, trans))
            return errmsg("Flash write failed: %s", f.err());
        p += trans;
        curr_addr += trans;
        towrite -= trans;

        // Report
        if (need_report) {
            u_int32_t new_perc = ((cnt - towrite) * 100) / cnt;
            if (new_perc != perc) {
                printf("\b\b\b\b%03d%%", new_perc);
                fflush(stdout);
                perc = new_perc;
            }
        }
    }

    if (need_report) {
        printf("\b\b\b\b100%%");
        fflush(stdout);
    }

    return true;
} //  Flash::write_image


////////////////////////////////////////////////////////////////////////
bool Operations::WriteSignature(Flash& f, u_int32_t image_idx, u_int32_t sig) {
    u_int32_t sect_size = f.get_sector_size();

    if (!f.write( sect_size * (image_idx + 1)  + 8, &sig, 4, true))
        return false;

    return true;
}


////////////////////////////////////////////////////////////////////////
bool Operations::repair(Flash& f, const int from, const int to, bool need_report)
{

    u_int32_t sect_size = f.get_sector_size();

    report("Repairing: Copy %s image to %s     -", from ? "secondary" : "primary" ,
           to ? "secondary" : "primary");


    // Read valid pointer sector
    u_int32_t sect[sizeof(PS)/4];
    report("\b READ %s ", from ? "SPS" : "PPS");
    if (!f.read(from ? sect_size*2 : sect_size, sect, sizeof(sect) , need_report)) {
        report("FAILED\n\n");
        return false;
    }
    report_erase(" READ %s 100%", from ? "SPS" : "PPS");

    u_int32_t im_ptr = sect[0];
    u_int32_t sig    = sect[2];

    TOCPU1(im_ptr);
    TOCPU1(sig);

    // Make sure ps ik ok:
    if (sig != SIGNATURE) {
        return errmsg("Can not copy image. Pointer sector %d signature is bad (%08x).", from, sig);
    }

    // Valid image size in bytes
    u_int32_t im_size_b;
    if (!f.read(sect_size * (from+1) + 4, &im_size_b)) {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(im_size_b);

    // Valid image size in sectors
    u_int32_t im_size_s = (im_size_b + sect_size - 1) / sect_size;

    // Address to copy valid image
    u_int32_t write_to = (!to) ? sect_size * 3 : sect_size * (3 + im_size_s);

    // f.read valid image
    report(" READ FW ");
    fflush(stdout);
    char *buf = new char[im_size_b];
    if (!f.read(im_ptr, buf, im_size_b, need_report)) {
        report("FAILED\n\n");
        delete [] buf;
        return false;
    }
    report_erase(" READ FW 100%");

    // Copy it to right place
    report("\b WRITE FW ");
    fflush(stdout);
    if (!write_image(f, write_to, buf, im_size_b, need_report)) {
        report("FAILED\n\n");
        delete [] buf;
        return false;
    }
    delete [] buf;
    report_erase(" WRITE FW 100%");

    // Set new image address
    // ++++++
    sect[0] = __be32_to_cpu(write_to);

    // Calculate new CRC
    // ++++++
    Crc16 crc;

    for (u_int32_t i = 0; i < (sizeof(sect)/4 - 1) ; i++) {
        crc << __be32_to_cpu(sect[i]);
    }
    crc.finish();

    sect[sizeof(sect)/4 - 1] = __be32_to_cpu(crc.get());

    // Corrupt signature
    u_int32_t valid_signature = sect[2];
    sect[2] = 0xffffffff;

    // Write it to invalid sector
    report("\b WRITE %s ", to ? "SPS" : "PPS");
    if (!write_image(f, to ? sect_size*2 : sect_size, sect, sizeof(sect), need_report)) {
        report("FAILED\n\n");
        return false;
    }
    report_erase(" WRITE %s 100%", to ? "SPS" : "PPS");

    // Validate signature
    report("\b SIGNATURE     ");
    if (!WriteSignature(f, to, valid_signature)) {
        report("FAILED\n\n");
        return false;
    }

    report_erase(" SIGNATURE     ");
    report(" OK       \n");
    return true;
} // Flash::repair





////////////////////////////////////////////////////////////////////////
bool Operations::FailSafe_burn_image(Flash&       f, 
                         void         *data, 
                         int          ps_addr, 
                         const char*  image_name, 
                         int          image_addr,
                         int          image_size,
                         bool         need_report) {

    u_int8_t* data8 = (u_int8_t*) data;
    u_int32_t sect_size = f.get_sector_size();

    report("Burning %-6s FW image without signatures  - ", image_name);
    fflush(stdout);

    // Invalidate signature
    u_int32_t zeros = 0;
    if (!f.write(ps_addr + 8, &zeros, 4, true)) {
        report("FAILED (Invalidating signature)\n\n");
        return false;
    }

    // Burn image (from new offset)

    // Both burnt images are taken from the first image in the file - both images in file are identical.
    // (future binary releases may contain a single image).
    if (!write_image(f, image_addr, data8 + sect_size * 3, image_size, need_report)) {
        report("FAILED\n\n");
        return false;
    }
    report("\b\b\b\bOK  \n");
    report("Restoring %-6s signature                  - ", image_name); 
    fflush(stdout);

    // Burn PS
    if (!write_image(f, ps_addr, data8 + ps_addr, sect_size, false)) {
        report("FAILED\n\n");
        return false;
    }

    // Validate signature
    u_int32_t sig = SIGNATURE;
    TOCPU1(sig);
    if (!f.write(ps_addr + 8, &sig, 4, true)) {
        report("FAILED\n\n");
        return false;
    }

    report("OK  \n");

    return true;
}   


////////////////////////////////////////////////////////////////////////
bool Operations::FailSafe_burn_internal(Flash& f, void *data, int cnt, bool need_report)
{
    u_int32_t *data32 = (u_int32_t *)data;

    u_int32_t sect_size = f.get_sector_size();

    // Extract Primary/Secondary image pointers and lengths
    u_int32_t prim_ptr = data32[sect_size / 4];
    u_int32_t prim_len = data32[sect_size / 4 + 1];
    u_int32_t scnd_ptr = data32[(sect_size * 2) / 4];
    u_int32_t scnd_len = data32[(sect_size * 2) / 4 + 1];
    TOCPU1(prim_ptr);
    TOCPU1(prim_len);
    TOCPU1(scnd_ptr);
    TOCPU1(scnd_len);
    if ((cnt < (int)(prim_ptr + prim_len)) || (cnt < (int)(scnd_ptr + scnd_len))) {
        return errmsg("Invalid image: too small.");
    }
    if (prim_len != scnd_len) {
        return errmsg("Invalid image: two FW images should have the same size.");
    }

    // Image size from flash
    u_int32_t old_im_size;
    if (!f.read(sect_size + 4, &old_im_size)) {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(old_im_size);

    u_int32_t prim_order;
    u_int32_t scnd_order;

    u_int32_t ps_addr[2];
    u_int32_t image_addr[2];
    char*     image_name[2];


    if (prim_len > old_im_size) {
        scnd_order = 0;
        prim_order = 1;
    } else {
        prim_order = 0;    
        scnd_order = 1;
    }

    image_name[scnd_order] = "Secondary";
    image_addr[scnd_order] = scnd_ptr;
    ps_addr   [scnd_order] = sect_size * 2;

    image_name[prim_order] = "Primary";
    image_addr[prim_order] = prim_ptr;
    ps_addr   [prim_order] = sect_size; 


    for (int i = 0 ; i < 2 ; i++) {
        if (!FailSafe_burn_image(f, data, ps_addr[i], image_name[i], image_addr[i], prim_len, need_report)) {
            return false;
        }
    }

    return true;
}

bool Operations::CheckInvariantSector(Flash& f, u_int32_t *data32, int sect_size) {
    int i;

    report("\nRead and verify Invariant Sector            - ");
    fflush(stdout);

    // Once more check signature - the Inv.Sector signature should be OK
    u_int32_t signature;
    if (!f.read(0x24, &signature)) {
        report("FAILED\n\n");
        return false;
    }
    TOCPU1(signature);
    if (signature != SIGNATURE) {
        report("FAILED\n\n");
	return errmsg("Flash has wrong signature in Invariant Sector (Expected %08x, got %08x).", SIGNATURE, signature);
    }

    // Now check Invariant sector contents
    vector<u_int32_t> buf1(sect_size/4);

    if (!f.read(0, &buf1[0] , sect_size)) {
        report("FAILED\n\n");
        return false;
    }

    int first_diff = -1;

    for (i=0; i < sect_size/4; i++) {
        if (buf1[i] != data32[i]  &&  (data32[i] != 0 || buf1[i] != 0xffffffff)) {
            if (first_diff == -1) 
                first_diff = i;
        }
    }

    // Check if a diff was found:
    if (first_diff != -1) {
            report("DIFF DETECTED\n\n");
            printf(" Invariant sector mismatch. Address 0x%x "
                   " in image: 0x%08x, while on flash: 0x%08x\n\n",
                   first_diff*4 , data32[first_diff], buf1[first_diff]);

            printf(" The invariant sector can not be burnt in a failsafe manner.\n");

        if (_allow_skip_is) {
            printf(" You can continue the FW update without burning the invariant sector.\n"
                   " See FW release notes for details on invariant sector updates.\n\n");

            return ask_user();

        } else {
            // Continue with burn
            printf(" You can perform the FW update without burning the invariant sector by\n"
                   " by specifying the -skip_is flag.\n" 
                   " See FW release notes for details on invariant sector updates.\n\n");

            return errmsg("Invariant sector mismatch");
        }
    }

    report("OK\n");
    return true;

}

////////////////////////////////////////////////////////////////////////
bool Operations::FailSafeBurn(Flash& f, FImage& fim, bool need_report, bool single_image_burn)
{
    u_int32_t *data32 = fim.getBuf();
    u_int8_t  *data8  = (u_int8_t *) data32;
    void*      data   = data8;
    int        size   = fim.getBufLength();

    u_int32_t i;
        
    u_int32_t sect_size     = f.get_sector_size();
    u_int32_t img_sect_size = fim.get_sector_size();

    // Check that the flash sector size is well defined in the image
    if (img_sect_size && (img_sect_size != sect_size)) {
        return errmsg("Flash sector size(0x%x) differs from sector size defined in the image (0x%x).\n"
                      "This means that the given FW file is not configured to work with the burnt HCA board type.\n",
                      sect_size,
                      img_sect_size);
    }

    if (size < (int)sect_size * 3) {
        report("FAILED\n\n");
        return errmsg("Image is too small.");
    }

    if (!CheckInvariantSector(f, data32, sect_size)) {
        return false;
    }

    // Check signatures in image
    u_int32_t actual_signature = data32[sect_size/4 + 2];

    u_int32_t signature_for_compare = actual_signature;

    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE) {
        return errmsg("Bad image file given: signature in PPS is 0x%08x (should be 0x%08x)",
		      signature_for_compare, SIGNATURE);
    }
    signature_for_compare = data32[(sect_size * 2)/4 + 2];
    TOCPU1(signature_for_compare);
    if (signature_for_compare != SIGNATURE) {
        return errmsg("Bad image file given: signature in SPS is 0x%08x (should be 0x%08x)",
		      signature_for_compare, SIGNATURE);
    }

    // Corrupt signatures in image
    data32[sect_size/4 + 2] = 0xffffffff;
    data32[(sect_size * 2)/4 + 2] = 0xffffffff;

    bool       cur_image_ok[2] = {false, false};
    u_int32_t  cur_image_addr[2];
    u_int32_t  cur_image_size[2];

    // Check signatures on flash
    report("Read and verify PPS/SPS on flash            - ");
    for (i = 0 ; i < 2 ; i++) {
        if (!f.read(sect_size * (i+1) + 8, &signature_for_compare)) {

        }
        TOCPU1(signature_for_compare);
        if (signature_for_compare == SIGNATURE) {
            cur_image_ok[i] = true;
            
            if (!f.read(sect_size * (i+1)    , &cur_image_addr[i]) ||
                !f.read(sect_size * (i+1) + 4, &cur_image_size[i])) {
                 report("FAILED\n\n");
                 return false;           
            }
  
            TOCPU1(cur_image_addr[i]);
            TOCPU1(cur_image_size[i]);
        }
    }

    if (!cur_image_ok[0] && !cur_image_ok[1]) {
        //
        // Both images are invalid on flash
        // --------------------------------
        //
        printf("\nBoth images (primary and secondary) are invalid on flash.\n");
        printf("The burning can not be failsafe, but it is harmless for host.\n");
        if(!ask_user()) {
            return false;
        }

        // Burn all image
        report("Burn FW image without signatures - ");
        fflush(stdout);
        if (!write_image(f, sect_size, data8 + sect_size, size - sect_size, need_report)) {
            report("FAILED\n\n");
            return false;
        }
        report("\b\b\b\bOK  \n");

        // Restore signatures
        report("Restore right signatures         - ");
        fflush(stdout);
        if (!WriteSignature(f, 0, actual_signature)) {
            report("FAILED (PPS Signature)\n\n");
            return false;
        }
        if (!WriteSignature(f, 1, actual_signature)) {
            report("FAILED (SPS Signature)\n\n");
            return false;
        }
        report("OK\n");
        return true;
    } else {
        report("OK\n"); 
    }

    if (single_image_burn == false) {

        if (cur_image_ok[0] == false || cur_image_ok[1] == false) {
            int image_from;
            int image_to;

	    assert (cur_image_ok[1] || cur_image_ok[0]);

            if (cur_image_ok[1]) {
                image_from = 1;
                image_to   = 0;
            } else {
                image_from = 0;
                image_to   = 1;
            }

	    report("Reparable Error Detected.\n");
	    if (!repair(f, image_from, image_to, need_report))
		    return false;
        }

        //
        // Both images are valid on flash
        //
        return FailSafe_burn_internal(f, data, size, need_report);

    } else {

        //
        // Single image burn:
        //

        // Extract Primary/Secondary image pointers and lengths
        u_int32_t frst_new_image_addr = data32[sect_size / 4];
        u_int32_t frst_new_image_size = data32[sect_size / 4 + 1];
        TOCPU1(frst_new_image_addr);
        TOCPU1(frst_new_image_size);

        if (!cur_image_ok[0] && cur_image_ok[1]) {
            // Second image is valid on flash.
            // If the new image can fit in the first image gap, it would be
            //   burnt as first image.
            // Otherwise (new image too big), image on flash is copied from second to 
            //   first image, and new image would be written as second.

            if (frst_new_image_addr + frst_new_image_size > cur_image_addr[1]) {
                // New image is too large - can not get in between first image start 
                // and current (second) image - move current image to be first.
                if (!repair(f, 1, 0, need_report))
                    return false;

                // Now 2 images are valid
                cur_image_ok[0] = true;
            } else {
                if (!FailSafe_burn_image(f, data, sect_size, "first", sect_size * 3, frst_new_image_size, need_report))
                    return false;

                if (!WriteSignature(f, 1, 0))
                    return false;

                return true;
            }
        }

        if (cur_image_ok[0] && cur_image_ok[1]) {
            // Invalidate second image
            if (!WriteSignature(f, 1, 0)) {
                report("FAILED\n");
                return false;
            }

            cur_image_ok[1] = false;
        }

        if (cur_image_ok[0] && !cur_image_ok[1]) {
            u_int32_t new_image_size_sect = ((frst_new_image_size - 1) / sect_size) + 1 ;
  
            // First image is valid on flash.
            // If the new image is smaller than current image, it would
            // overwrite the end of current image. In this case, move the current image
            // to the second position and burn in first.
            //
            // TODO: STOP THIS MOVEMENT BULLSHI%@#&! !!! : Reproduce PS in flint with the correct addr. Locate second image in middle of flash. 

            if ( (3 + new_image_size_sect) * sect_size < cur_image_addr[0] + cur_image_size[0]) {
                // New image overwrites end of cur image
                // move current image to be second.
                if (!repair(f, 0, 1, need_report))
                    return false;

                // Now 2 images are valid
                cur_image_ok[1] = true;

                // Burn new image as firse
                if (!FailSafe_burn_image(f, data, sect_size, "first", 
                                         sect_size * 3, frst_new_image_size, need_report))
                    return false;

                if (!WriteSignature(f, 1, 0))
                    return false;

                return true;

            } else {
                if (!FailSafe_burn_image(f, data, sect_size * 2, "second", 
                                     sect_size * (3 + new_image_size_sect) , frst_new_image_size, need_report))
                    return false;

                // Invalidate first image 
                if (!WriteSignature(f, 0, 0))
                    return false;

                return true;

            }
        } else {
            report("Bad flash state: Valid images = (%d,%d).\n", cur_image_ok[0], cur_image_ok[1] );
            return false;
        }

    }

    return true;
}

bool Operations::CntxFailSafeBurn(Flash&    f, 
                                  FImage&   fim, 
                                  bool      need_report, 
                                  Operations::ImageInfo* flash_info, 
                                  Operations::ImageInfo* image_info,
                                  bool      allow_nofs) {

    // TODO: See getBuf effect on zebra image.
    u_int8_t  *data8      = (u_int8_t *) fim.getBuf();
    int        image_size = fim.getBufLength();
    u_int32_t  zeroes     = 0;

    bool is_curr_image_in_odd_chunks;

    if (!allow_nofs) {
        if (!image_info->isFailsafe) {
            return errmsg("The given image is not a failsae image");
        }

        if (flash_info->cntxLog2ChunkSize != image_info->cntxLog2ChunkSize) {
            return errmsg("Failsafe chunk sizes in flash (0x%x) and in image (0x%x) are not the same.",
                          1 << flash_info->cntxLog2ChunkSize,
                          1 << image_info->cntxLog2ChunkSize);
        }
    }

    u_int32_t new_image_start;

    if (flash_info->imgStart != 0) {
        is_curr_image_in_odd_chunks = 1;
        new_image_start = 0;
    } else {
        is_curr_image_in_odd_chunks = 0;
        new_image_start = (1 << image_info->cntxLog2ChunkSize);
    }

    //printf("-I- Chunk=%x . Cur image start=%x burning from %x, flash_log2_chunk_size=%d\n", 
    //       1 << flash_info->cntxLog2ChunkSize, 
    //       flash_info->imgStart, 
    //       new_image_start,
    //       flash_info->cntxLog2ChunkSize);

    if (image_info->isFailsafe) {
        f.set_address_convertor(image_info->cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);
    } else {
        f.set_address_convertor(0,0);
        new_image_start = 0;
    }

    // Go ahead and burn!
    const char* image_name = new_image_start == 0 ? "first" : "second";
    report("\nBurning %-6s FW image without signatures  - ", image_name);

    fflush(stdout);

    if (!write_image(f, 16 , data8 + 16, image_size - 16, need_report)) {
        report("FAILED\n\n");
        return false;
    }
    report("\b\b\b\bOK  \n");

    report("Restoring %-6s signature                  -     ", image_name); 

    fflush(stdout);

    // Write new signature
    if (!f.write(0, data8, 16, true)) {
        report("FAILED\n\n");
        return false;
    }

    // Write new image start address to crspace (for SW reset)
    f.cr_write(0xf0000, (new_image_start << 8) | 0x06);

    if (image_info->isFailsafe) {
        if (allow_nofs) {
            // When burning in nofs, remnant of older image with different chunk size
            // may reside on the flash - 
            // Invalidate all images marking on flash except the one we've just burnt

            u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
            u_int32_t cntx_image_num;
            u_int32_t i;

            CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);
            // Address convertor is disabled now - use phys addresses
            for (i = 0; i < cntx_image_num; i++) {
                if (cntx_image_start[i] != new_image_start) {
                    if (!f.write(cntx_image_start[i], &zeroes, sizeof(zeroes), true)) {
                        report("FAILED\n\n");
                        return false;
                    } 
                }
            }
        } else {
            // invalidate previous signature
            f.set_address_convertor(image_info->cntxLog2ChunkSize, is_curr_image_in_odd_chunks);
            if (!f.write(0, &zeroes, sizeof(zeroes), true)) {
                report("FAILED\n\n");
                return false;
            }
        }
    }
    report("\b\b\b\bOK  \n");

    if (allow_nofs && image_info->isFailsafe) {

    }

    return true;
}




////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        VERIFY FLASH                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////


//
// Cntx image verification flow:
// 
// The "zebra"failsafe scheme presents few problems:
// - Need to search for a valid image in the flash.
// - handle no image / more than a single valid image cases
// - check image actual start location(s) vs. fs_zebra_size field in the image.
// - Image file is not striped though its fs_zebra_size sais it is - need to allow that
//   when checking a file.
//
// Verification flow:
// 
// 1. Find image start addresses.
//    if num of start_addr not in [1,2] - Error - corrupted flash
// 2. for each start_addr:
//      Check that its fs_zebra_size is identical to other images (if exists)
//      For Flash: 
//          Set address translation according to the fs_zebra_size.
//      For File:
//          *GUESS* if image is contiguous or striped. This can be according
//          to the file size vs. image size field in the image.
//          Set address translation according to the fs_zebra_size or to 0.
//      verify - same as previous projects nofs image, with the aditional start
//


bool Operations::CntxFindMagicPattern       (FBase& f,  u_int32_t addr) {
    int i;
    if (addr + 16 > f.get_size()) {
        return false;
    }
    for (i = 0; i < 4 ; i++) {
        u_int32_t w;
        READ4(f, addr + i * 4, &w, "Magic Pattern" );
        TOCPU1(w);
        if (w != _cntx_magic_pattern[i]) {
            //printf("-D- Looking for magic pattern %d addr %06x: Exp=%08x Act=%08x\n", i, addr + i * 4, _cntx_magic_pattern[i], w);
            return false;
        }
    }

    return true;
}

// FindAllImageStart
// OUT: start_locations: set to the start addresses of the found image markers (in accending order)
// OUT: found_images:    Number of found images (and number of valid entries in the start_locations array).
bool Operations::CntxFindAllImageStart       (FBase& f,  u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images) {
    int i;
    f.set_address_convertor(0,0);

    *found_images = 0;
    for (i = 0; i < CNTX_START_POS_SIZE; i++) {
        if (CntxFindMagicPattern(f, _cntx_image_start_pos[i])) {
            start_locations[*found_images] = _cntx_image_start_pos[i];
            (*found_images)++;
        }
    }

    return true;
}

bool Operations::checkBoot2(FBase& f, u_int32_t beg, u_int32_t offs,
                u_int32_t& next, const char *pref)
{
    u_int32_t    size;

    char         *pr = (char *)alloca(strlen(pref) + 512);

    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs+beg);

    // Size
    READ4(f, offs+beg+4, &size, pr);
    TOCPU1(size);
    if (size > 1048576 || size < 4) {
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
    if (crc.get() != crc_act) {
        report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, offs+beg, crc.get(), crc_act);
        return errmsg("Bad CRC");
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
bool Operations::checkGen(FBase& f, u_int32_t beg,
              u_int32_t offs, u_int32_t& next, const char *pref)
{
    char         *pr = (char *)alloca(strlen(pref) + 100);

    char         unknown_sect_name[128];
    const char*  sect_name;

    u_int32_t    size=0;
    GPH          gph;

    // GPH
    sprintf(pr, "%s /0x%08x/ (GeneralHeader)", pref, offs+beg);
    READBUF(f, offs+beg, &gph, sizeof(GPH), pr);
    TOCPUBY(gph);

    // Body
    part_cnt++;

    // May be BOOT3?
    if (gph.type < H_FIRST  ||  gph.type >= H_LAST) {
        if (part_cnt > 2) {
            //report("%s /0x%x/ - Invalid partition type (%d)\n",
            //       pref, offs+beg, gph.type);
            //return false;
        } else
            return checkBoot2(f, beg, offs, next, pref);
    }

    // All partitions here
    offs += beg;

    if (gph.type < H_FIRST  ||  gph.type >= H_LAST) {
        // For forward compatibility, try analyzing even if section type is uncknown
        // Assuming the size is in DW, like all other sections (except emt service).
        // If this assumption is wrong, CRC calc would fail - no harm done.
        sprintf(unknown_sect_name, "UNKNOWN (%d)" , gph.type);
        sect_name = unknown_sect_name;
        size = gph.size * 4;
    } else {
        if (gph.type == H_EMT) {
            size = (gph.size + 3) / 4 * 4;
        } else {
            size = gph.size * 4;
        }
        sect_name = g_sectNames[gph.type];
    }

    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (%s)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4, sect_name);
    
    if (size > MAX_SECTION_SIZE) {
        report("%s - size too big (0x%x)\n",
               pr, size);
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
    if (crc.get() != crc_act) {
        report("%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, offs, crc.get(), crc_act);
        return errmsg("Bad CRC");
    }

    if (_print_crc)
        report("%s - OK (CRC:0x%04x)\n", pr, crc_act&0xffff);
    else
        report("%s - OK\n", pr);
    next = gph.next;

    if (gph.type == H_FW_CONF) {
        _fw_conf_sect.clear();
        _fw_conf_sect.insert(_fw_conf_sect.end(), 
                         vector<u_int8_t>::iterator((u_int8_t*)buff), 
                         vector<u_int8_t>::iterator((u_int8_t*)buff + size));

    }

    if (gph.type == H_ROM && _rom_sect.empty()) {
        _rom_sect.clear();
        _rom_sect.insert(_rom_sect.end(), 
                         vector<u_int8_t>::iterator((u_int8_t*)buff), 
                         vector<u_int8_t>::iterator((u_int8_t*)buff + size));
    }

    // mark last read addr
    _last_image_addr = offs + size +sizeof(gph) + 4;  // the 4 is for the trailing crc
    
    return true;
} // checkGen

////////////////////////////////////////////////////////////////////////
bool Operations::checkPS(FBase& f, u_int32_t offs, u_int32_t& next, const char *pref)
{
    Crc16 crc;
    PS    ps;
    f.read(offs, &ps, sizeof(ps));
    TOCPUBY(ps);

    // Signature
    if (ps.signature != SIGNATURE) {
        report("%s Pointer Sector /0x%08x/ - invalid signature (%08x)\n",
               pref, offs, ps.signature);
        return false;
    }

    // CRC
    CRC1BY(crc, ps);
    crc.finish();
    if (crc.get() != ps.crc016) {
        report("%s Pointer Sector /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pref, offs, ps.crc016, crc.get());
        return errmsg("Bad CRC");
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
bool Operations::checkList(FBase& f, u_int32_t offs, u_int32_t fw_start, const char *pref)
{
    u_int32_t next_ptr;

    CHECKB2(f, offs, fw_start, next_ptr, pref);
    part_cnt = 1;
    while (next_ptr && next_ptr != 0xff000000)
        CHECKGN(f, offs, next_ptr, next_ptr, pref);

    return true;
} // checkList

////////////////////////////////////////////////////////////////////////

bool Operations::CheckIsCntx(FBase& f) {
    if (f.is_flash()) {
        return (((Flash*)&f)->get_dev_id() == 400);
    } else {
        u_int32_t found_images;
        u_int32_t image_start[CNTX_START_POS_SIZE];

        // Image - check if magic pattern is somewhere in the file:
        CntxFindAllImageStart(f, image_start, &found_images);
        return found_images > 0;
    }
}

bool Operations::CheckMac(u_int64_t mac) {
    if ((mac >> 40) & 0x1) {
        return errmsg("Multicast bit (bit 40) is set");
    }

    if (mac >> 48) {
        return errmsg("More than 48 bits are used");
    }

    return true;
}


bool Operations::CntxGetFsData(FBase& f, u_int32_t img_addr, bool& fs_en, u_int32_t& log2chunk_size) {
    u_int32_t fs_info_word;
    u_int8_t  checksum;

    f.read(img_addr + 0x28, &fs_info_word);
    TOCPU1(fs_info_word);

    // printf("-D- fs_info_word=%08x\n", fs_info_word);

    checksum = ((fs_info_word      ) & 0xff) +
               ((fs_info_word >>  8) & 0xff) +
               ((fs_info_word >> 16) & 0xff) +
               ((fs_info_word >> 24) & 0xff);

    if (checksum != 0) {
        return errmsg("Corrupted chunk size checksum");
    }

    fs_en = (fs_info_word & 0x8) != 0;

    if (fs_en) {
        log2chunk_size = (fs_info_word & 0x7) + 16;
    } else {
        log2chunk_size = 0;
    }

    return true;
}

bool Operations::VerifyCntx(FBase& f, Operations::ImageInfo* info, bool both_images) {
    u_int32_t cntx_image_start[CNTX_START_POS_SIZE];
    u_int32_t cntx_image_num;
    u_int32_t i;
    bool      ret = true;

    // Look for image in "physical addresses

    CntxFindAllImageStart(f, cntx_image_start, &cntx_image_num);

    if (cntx_image_num == 0) {
        return errmsg("No valid image found");
    } else if (cntx_image_num > 2) {
                // This check may be redundant - Maybe ignore if more than 2 images found
                return errmsg("More than 2 image start locations found at addresses %x, %x and %x. Image may be corrupted.",
                              cntx_image_start[0],
                              cntx_image_start[1],
                              cntx_image_start[2]);
    }

    if (!both_images) {
        // Check only the first image. This is enough to ensure that the device is bootable.
        cntx_image_num = 1;
    }

    bool info_set = false;

    // Verify the images:
    for (i = 0; i < cntx_image_num; i++ ) {
        bool      fs_en;
        u_int32_t log2chunk_size;

        f.set_address_convertor(0,0);
        if (!CntxGetFsData(f, cntx_image_start[i], fs_en, log2chunk_size)) {
            report("\n    Can't read failsafe info word: %s\n", err());

            return (i > 0);
        }

        // If fw not enabled, image must start at addr 0
        if (!fs_en && cntx_image_start[i] != 0) {
            return errmsg("ConnectX Non Failsafe image must start at address 0. Found non-fs image at address %x",
                          cntx_image_start[i]);
        }

        if (fs_en) {
            report("\n     ConnectX failsafe image. Start address: %x. Chunk size %x:\n\n", cntx_image_start[i], 1 << log2chunk_size);
            report("     NOTE: The addresses below are contiguous logical addresses. Physical addresses on\n"
                   "           flash may be different, based on the image start address and chunk size\n\n");
        } else {
            report("\n     ConnectX non failsafe image:\n\n");
        }

        if (fs_en && cntx_image_start[i] != 0 && cntx_image_start[i] != (u_int32_t)(1 << log2chunk_size)) {
            return errmsg("ConnectX Failsafe image must start at address 0 or at chunk size. Found a failsafe image at address %x",
                          cntx_image_start[i]);
        }

        if (info && !info_set) {
            info->imgStart          = cntx_image_start[i];
            info->isFailsafe        = fs_en;
            info->actuallyFailsafe  = true;
            info->cntxLog2ChunkSize = log2chunk_size;
        }

        if (f.is_flash()) {
            // In flash, image layout must match the FS Data
            if (info && !info_set) {
                info->actuallyFailsafe    = true;
                info_set = true;
            }

            if (fs_en) {
                f.set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
            }
        } else {
            // In an image file there are 2 cases:
            // 1. Image generated by mlxburn 
            //    The image in the file is contiguous (though it is marked as FS) - no need to set address convertion.
            // 2. The image was raw read from flash. In this case it would be in "zebra" format.
            //
            // So - I try both cases, and see which verify() succeeds.
            //
            // Heuristics that may come in handy:
            // If the image does not start at addr 0, it's not an mlxburn image.
            // If there is more than a single valid image, it's not an mlxburn image.
            // If the file size matches the image size, it is an mlxburn image.
            //
            // For now, get the "striped" indication from user.

            if (_cntx_striped_image) {
                f.set_address_convertor(log2chunk_size, cntx_image_start[i] != 0);
            } else {
                f.set_address_convertor(0,0); //disable conversion
            }
            if (info && !info_set) {
                info->actuallyFailsafe    = _cntx_striped_image;
                info_set = true;
            }   
        }

        bool imgStat = checkList(f, 0, 0x38, "    ");
        if (i == 0) {
            ret = ret && imgStat;
        }
    }
    return ret;
}

bool Operations::Verify(FBase& f, Operations::ImageInfo* info, bool both_images)
{
    u_int32_t prim_ptr, scnd_ptr;
    u_int32_t signature;

    bool      ret = true;

    if (IsCntx()) {
        return VerifyCntx(f, info, both_images);
    }

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    if (signature == SIGNATURE) {
        // Full image

        bool psStat[2];

        report("\nFailsafe image:\n\n");
        CHECKB2(f, 0, 0x28, prim_ptr, "Invariant      ");
        report("\n");
        psStat[0] = checkPS(f, f.get_sector_size(), prim_ptr, "Primary  ");
        if (psStat[0]) {
            ret &= checkList(f, prim_ptr, 0x28, "               ");
        }
        report("\n");

        if (psStat[0] && !both_images) {
            return ret;
        }

        psStat[1] = checkPS(f, f.get_sector_size() * 2, scnd_ptr, "Secondary");
        bool scndStat;
        if (psStat[1]) {
            scndStat = checkList(f, scnd_ptr, 0x28, "               ");
            if (!psStat[0]) {
                // If the first image is valid, the HCA would boot OK even if the secondary image is messed up - 
                // consider this status only if the first image is not valid.
                ret &= scndStat;
            }
        }

        if (psStat[0] == false && psStat[1] == false) {
            ret = false;
        }
    } else {

        report("\nShort image:\n");
        CHECKLS(f, 0, 0x28, "    ");
    }

    return ret;
} // Verify

bool Operations::GetExpRomVersion(ImageInfo* info) {
    const char* magic_string = "mlxsign:";
    u_int32_t   magic_len    = strlen(magic_string);
    u_int32_t   i;
    bool        magic_found  = false;
    u_int32_t   ver_offset;
    u_int8_t    rom_checksum = 0;
    u_int32_t   rom_checksum_range;

    info->expRomValidVersion = false;
    if (_rom_sect.empty()) {
        return errmsg("Expansion Rom section not found.");
    }

    // When checking the version of the expansion rom, only the first image has
    // to be checked. This is because the second image  the uefi image does not 
    // have to comply with checksumming to 0. To do this you have to read  byte 
    // 2 (third) of the image  and multiply by 512 to get the size of the x86 
    // image.

    // Checksum:
    if (_rom_sect.size() < 4) {
        return errmsg("ROM size (0x%x) is too small", (u_int32_t)_rom_sect.size());
    }

    // restore endianess.
    TOCPUn(&(_rom_sect[0]), _rom_sect.size()/4);

    rom_checksum_range = _rom_sect[2] * 512 ;
    if (rom_checksum_range > _rom_sect.size()) {
       return errmsg("ROM size field (0x%2x) is larger than actual ROM size (0x%x)", 
                     rom_checksum_range , 
                     (u_int32_t)_rom_sect.size());
    } else if (rom_checksum_range == 0) {
       return errmsg("ROM size field is 0. Unknown ROM format or corrupted ROM.");
    }

    for (i = 0; i < rom_checksum_range; i++) {
        rom_checksum += _rom_sect[i];
    }

    if (rom_checksum != 0) {
        return errmsg("Bad ROM Checksum (0x%2x)", rom_checksum);
    }

    for (i = 0 ; i < rom_checksum_range; i++) {
        for (u_int32_t j = 0; j < magic_len; j++) {
            if (_rom_sect[i+j] != magic_string[j]) {
                break;
            } else if (j == magic_len - 1) {
                magic_found = true;
            }
        }

        if (magic_found) {
            break;
        }
    }

    if (magic_found) {
        ver_offset = i + magic_len;
    } else {
        return errmsg("Mellanox version string (%s) not found in ROM section.", magic_string);
    }

    // Following mlxsign:
    // 31:24	0	 Compatible with UEFI
    // 23:16	ProductID	Product ID:
    //                          1 - CLP implementation for Sinai (MT25408)
    //                          2 - CLP implementation for Hermon DDR (MT25418)
    //                          0X10 - PXE
    // 15:0	Major version	If ProductID < 0x10 this field is subversion 
    //                          number, otherwise It's product major version. 
    // 
    // 31:16	Minor version	Product minor version*. Not valid if 
    //                          roductID < 0x10.
    // 15:0	SubMinor version	Product sub minor version*. Not valid if 
    //                                  ProductID < 0x10.
    // 
    // 31:16	Device ID	The PCI Device ID (ex. 0x634A for Hermon 
    //                          DDR). Not valid if ProductID < 0x10.
    // 15:12	Port Number	Port number: 0 - Port independent, 1 - Port 1, 2 - Port 2
    // 11:0	Reserved	

    u_int32_t tmp;

    tmp = __le32_to_cpu(*((u_int32_t*) &_rom_sect[ver_offset]));
    info->expRomProductId = tmp >> 16;
    info->expRomVer[0]    = tmp & 0xffff;

    if (info->expRomProductId >= 0x10) {
        tmp = __le32_to_cpu(*((u_int32_t*) &_rom_sect[ver_offset + 4]));
        info->expRomVer[1] = tmp >> 16;
        info->expRomVer[2] = tmp  & 0xffff;

        tmp = __le32_to_cpu(*((u_int32_t*) &_rom_sect[ver_offset + 8]));
        info->expRomDevId  = tmp >> 16;
        info->expRomPort   = (tmp >> 12) & 0xf;
    }
    info->expRomValidVersion = true;
    return true;
}

bool Operations::LoadAsExpRom (FBase& f) {
    _rom_sect.clear();
    _rom_sect.resize(f.get_size());
    if (!f.read(0, &_rom_sect[0], f.get_size()))
        return errmsg(f.err());

    TOCPUn(&_rom_sect[0], _rom_sect.size()/4);

    return true;
}

bool Operations::DumpConf        (const char* conf_file) {
#ifndef NO_ZLIB

    FILE* out;
    if (conf_file == NULL) {
        out = stdout;
    } else {
        out = fopen(conf_file, "w");

        if (out == NULL) {
            return errmsg("Can not open file %s for write: %s.", conf_file, strerror(errno));
        }
    }

    if (_fw_conf_sect.empty()) {
        return errmsg("FW configuration section not found in the given image.");
    }

    // restore endianess.
    TOCPUn(&(_fw_conf_sect[0]), _fw_conf_sect.size()/4);

    // uncompress:
    uLongf destLen = _fw_conf_sect.size();
    destLen *= 10;
    vector<u_int8_t> dest(destLen);

    int rc = uncompress((Bytef *)&(dest[0]), &destLen,
                        (const Bytef *)&(_fw_conf_sect[0]), _fw_conf_sect.size());

    if (rc != Z_OK)
    {
        return errmsg("Failed uncompressing FW configuration section. uncompress returnes %d", rc);
    }

    dest.resize(destLen);
    dest[destLen] = 0;  // Terminating NULL
    fprintf(out, "%s", (char*)&(dest[0]));

    if (conf_file != NULL) {
        fclose(out);
    }

    return true;
#else 
    return errmsg("Executable was compiled with \"dump configuration\" option disabled.");
#endif

} // DumpConf



////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                       GUIDs TREATMENT                              //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
#define GETGUID(s, g) do { if (!ops.getGUID(s,g)) return 1; } while (0)
#define GETBSN(s, g)  do { if (!ops.getBSN(s,g)) return 1; } while (0)

#define BSN_RET do {                                            \
    printf("Invalid BSN. Should be MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n"); \
    return false;                                               \
} while(0)
#define BSN_RET1(s) do {                                             \
    printf("Valid BSN format is: MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n%s.\n",s); \
    return false;                                                    \
} while(0)
u_int32_t Operations::BSN_subfield(const char *s, int beg, int len)
{
    char buf[64];
    strncpy(buf, &s[beg], len);
    buf[len] = '\0';
    return strtoul(&buf[0], 0, 10);
}
bool Operations::getBSN(char *s, guid_t *guid)
{
    const u_int64_t COMPANY_ID = 0x0002c9;
    const u_int64_t  TYPE      = 1;
    bool cc_present = false;
    char *p;
    int  date_offs = 0;
    int  i;

    // Convert to lowercase
    for (p = s; *p; p++)
        *p = (char)tolower(*p);

    // Check validity
    p = s;
    if (strncmp(p, "mt", 2))     // MT
        BSN_RET;
    p += 2;
    for (i=0; i<5; i++)
        if (!isdigit(*p++))      // xxxxx
            BSN_RET;
    if (*p == '-') {               // - /optional/
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

    switch (ndigits) {
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
    if (*p) {
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
        BSN_RET1("Day (dd) can not be zero");
    u_int32_t mm = BSN_subfield(s, 10+date_offs, 2);
    if (mm > 12)
        BSN_RET1("Months (mm) should not exceed 12");
    if (!mm)
        BSN_RET1("Months (mm) can not be zero");
    u_int32_t yy = BSN_subfield(s, 12+date_offs, 2);
    if (yy > 99)
        BSN_RET1("Year (yy) should not exceed 99");
    if (!yy)
        BSN_RET1("Year (yy) can not be zero");
    u_int32_t num = BSN_subfield(s, 15+date_offs, 3);
    if (num > 999)
        BSN_RET1("Number (num) should not exceed 999");
    if (!num)
        BSN_RET1("Number (num) can not be zero");
    int cc = 1;
    if (cc_present) {
        cc = BSN_subfield(s, 19+date_offs, 2);
        if (cc > 14)
            BSN_RET1("Chip number (cc) should not exceed 14");
        if (!cc)
            BSN_RET1("Chip number (cc) can not be zero");
    }
    u_int64_t id = ((((yy*12+mm-1)*31+ dd-1) * 1000) + num-1) * 112;
    id += (cc-1)*8;

    u_int64_t g = (COMPANY_ID << 40) | (TYPE << 32) | id;
    guid->h = (u_int32_t)(g>>32);
    guid->l = (u_int32_t)g;
    return true;
}

bool Operations::getGUID(const char *s, guid_t *guid)
{
    char* endp;
    u_int64_t g;

    g = strtoull(s, &endp, 16);
    if (*endp || (g == 0xffffffffffffffffULL && errno == ERANGE)) {
        printf("Invalid GUID syntax (%s) %s \n",
               s,
               errno ? strerror(errno) : "" );
        return false;
    }
    guid->h = (u_int32_t)(g >> 32);
    guid->l = (u_int32_t)(g & 0xffffffff);
    return true;
} // getGUID

////////////////////////////////////////////////////////////////////////
bool Operations::extractGUIDptr(u_int32_t sign, u_int32_t *buf, int buf_len,
                    char *pref, u_int32_t *ind, int *nguids)
{
    u_int32_t offs = 0;

    if (IsCntx()) {
        offs = 16;
    }

    // Check signature
    if (sign) {
        u_int32_t signature = buf[(sign + 8)/4];
        TOCPU1(signature);
        if (signature != SIGNATURE) {
            printf("%s pointer section not valid\n", pref);
            return false;
        }
        offs = buf[sign/4];
        TOCPU1(offs);
    }

    // Get GUID ptr
    *ind = buf[(offs+0x24)/4];
    TOCPU1(*ind);
    if (!IsCntx()) {
        *ind += offs;
    }
    if (*ind >= (u_int32_t)buf_len) {
        printf("%s image - illegal GUID pointer (%08x)\n", pref, *ind);
        return false;
    }
    *nguids = buf[*ind/4 - 3];
    TOCPU1(*nguids);
    *nguids /= 2;

    // More sanity check
    if (IsCntx() ? (*nguids > MAX_GUIDS) : (*nguids > GUIDS)) {
        printf("%s image - illegal number of GUIDs (0x%x)\n", pref, *nguids);
        return false;
    }

    return true;
} // extractGUIDptr



////////////////////////////////////////////////////////////////////////

//
// This function calculates CRC over the geven buf/size, and stores 
// the crc in the dwors after the data.
// Caller should make sure CRC word memory is really there.
void Operations::recalcSectionCrc(u_int8_t *buf, u_int32_t data_size) {
    Crc16              crc;
    u_int32_t          i;

    for (i = 0; i < data_size; i += 4) {
        crc << __be32_to_cpu(*(u_int32_t*)(buf + i));
    }
    crc.finish();
    *(u_int32_t*)(buf + data_size) = __cpu_to_be32(crc.get());
}

////////////////////////////////////////////////////////////////////////
void Operations::patchGUIDsSection(u_int32_t *buf, u_int32_t ind,
                       guid_t guids[MAX_GUIDS], int nguids)
{
    u_int32_t       i;
    u_int32_t       new_buf[MAX_GUIDS*2];

    // Form new GUID section
    for (i=0; i<(u_int32_t)nguids; i++) {
        new_buf[i*2] = guids[i].h;
        new_buf[i*2+1] = guids[i].l;
    }

    // Patch GUIDs
    for (i=0; i<sizeof(new_buf)/sizeof(u_int32_t); ++i) {
        new_buf[i] = __cpu_to_be32(new_buf[i]);
    }
    memcpy(&buf[ind/4], &new_buf[0], nguids * 2 * sizeof(u_int32_t));

    // Insert new CRC
    recalcSectionCrc((u_int8_t*)buf + ind - sizeof(GPH), sizeof(GPH) + nguids * 8);
} // patchGUIDsSection




// 
// PatchInfoSect() :
// This func assumes it gets a pointer (rawSect) to a valid info sect.
// It patches the it with the given data, recalculated CRC ,
// and copies it back to the geven data
//

void Operations::PatchInfoSect(u_int8_t*      rawSect,
                               u_int32_t      vsdOffs,
                               const char*    vsd) {

    u_int32_t  vsdSize  = __be32_to_cpu(*((u_int32_t*)(rawSect + sizeof(GPH) + vsdOffs - 4))) & 0xffffff;
    u_int32_t  infoSize = __be32_to_cpu(*((u_int32_t*)(rawSect + 4)));

    // byte size;
    infoSize *= 4;

    //printf("-D- vsdOffs=%x, vsdSize=%x, infoSize=%x\n", vsdOffs,vsdSize, infoSize );
    if (vsd) {
        u_int32_t len = strlen(vsd);

        if (len > vsdSize) {
            report("Warning: The given VSD length is too large (%d chars). Truncating to %d chars.\n", len, vsdSize);
            len = vsdSize;
        }
       
        memset(rawSect + sizeof(GPH) + vsdOffs,  0,   vsdSize );
        memcpy(rawSect + sizeof(GPH) + vsdOffs,  vsd, len);
    }

    recalcSectionCrc(rawSect, sizeof(GPH) + infoSize);
}


// 
// PatchPs() :
// This func assumes it gets a pointer (rawPs) to a valid PS.
// It patches the PS with the given data, recalculated CRC ,
// and copies it back to the rawPs.
//

void Operations::PatchPs(u_int8_t*      rawPs, 
                         const char*    vsd,
                         const char*    psid,
                         u_int32_t      imageAddr) {

    PS         *ps = (PS*)rawPs;

    u_int32_t fix_start = 0;
    u_int32_t fix_end   = 0;

    if (vsd) {
        u_int32_t len = strlen(vsd);
       
        memset(&ps->vsd[0],  0,   VSD_LEN );
        memcpy(&ps->vsd[0],  vsd, len);

        fix_end += VSD_LEN;
    } else {
        fix_start +=VSD_LEN;
    }
    if (psid) {
        u_int32_t len = strlen(psid);

        memset(&ps->psid[0],  0,    PSID_LEN );
        memcpy(&ps->psid[0],  psid, len );
        fix_end += PSID_LEN;
    }

    //VSD is kept on flash byte-swapped.
    //recode it back before patching
    u_int32_t *qp;

    qp = (u_int32_t *)&ps->vsd[0];
    for (u_int32_t i=fix_start; i<fix_end/4; i++) {
        *qp = bswap_32(*qp);
        qp++;
    }

    if (imageAddr) {
        ps->fi_addr = __cpu_to_be32(imageAddr);
    }

    recalcSectionCrc((u_int8_t *)ps, sizeof(PS) - 4);
}
        

////////////////////////////////////////////////////////////////////////
//Note that vsd1 is a string of bytes.
bool Operations::patchVSD(FImage& f,
                          Operations::ImageInfo* info,
                          const char *user_vsd, 
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid)
{
    const char* vsd_to_use  = curr_vsd ? curr_vsd : "";
    const char* psid_to_use = image_psid;

    // TODO: Should not give the user_psid param. Do not allow for on-the-fly PSID changes.

    curr_psid = NULL;
    // Form new VSD

    if (user_psid) {
        // New psid is explicitly given - take it from user
        printf("\n    You are about to replace current PSID in the image file - \"%s\" with a different PSID - \"%s\".\n"
               "    Note: It is highly recommended not to change the image PSID.\n", user_psid, image_psid);

        if (! ask_user())
            return false;

        psid_to_use = user_psid;
    }

    if (user_vsd) {
        vsd_to_use = user_vsd;
    }

    if (IsCntx() && info->infoOffs[II_VSD]) {
        PatchInfoSect((u_int8_t*)f.getBuf() + info->infoSectPtr - sizeof(GPH), 
                      info->infoOffs[II_VSD],
                      vsd_to_use);
    } else {
        PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size(),     vsd_to_use, psid_to_use);
        PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size() * 2, vsd_to_use, psid_to_use);
    }

    return true;
} // pathVSD


bool Operations::printGUIDs(const char* msg, guid_t guids[MAX_GUIDS], bool print_guids, bool print_macs, bool old_guid_fmt) {
    const char* g_m;

    if        ( print_guids &&  print_macs) {
        g_m = "GUIDs/MACs";
    } else if (!print_guids &&  print_macs) {
        g_m = "MACs";
    } else if ( print_guids && !print_macs) {
        g_m = "GUIDs";
    } else {
        return errmsg("Internal error: Operations::PrintGuids() with both guid and mac turned off");
    }

    printf("%s %s:\n", msg, g_m);
    if (print_guids) {
        printf("        Node  GUID:     " GUID_FORMAT "\n", guids[0].h, guids[0].l);
        printf("        Port1 GUID:     " GUID_FORMAT "\n", guids[1].h, guids[1].l);
        if (_num_ports > 1) 
            printf("        Port2 GUID:     " GUID_FORMAT "\n", guids[2].h, guids[2].l);
        if (!old_guid_fmt)
            printf("        Sys.Image GUID: " GUID_FORMAT "\n", guids[3].h, guids[3].l);
    }

    if (print_macs) {
        printf("        Port1 MAC:      " MAC_FORMAT "\n", guids[4].h, guids[4].l);
        printf("        Port2 MAC:      " MAC_FORMAT "\n", guids[5].h, guids[5].l);
    }
    return true;
}   

////////////////////////////////////////////////////////////////////////
bool Operations::patchGUIDs (FImage&   f, 
                             ImageInfo* info,
                             bool      patch_guids, 
                             bool      patch_macs,
                             bool      user_guids,
                             bool      user_macs,
                             guid_t    new_guids[MAX_GUIDS], 
                             guid_t    old_guids[MAX_GUIDS],
                             u_int32_t num_of_old_guids,
                             bool      interactive)
{
    guid_t*         used_guids = old_guids ? old_guids : new_guids;
    u_int32_t       *buf = f.getBuf();
    int i;

    bool old_guids_fmt = info->guidNum < GUIDS;

    // Print old GUIDs and get confirmation
    if (new_guids) {
        if (old_guids_fmt) 
            printf("    Old image!!!! Only %d GUIDs may be set.\n", info->guidNum);
            // if only guids or only macs are specified by user, keep the other
            // as currently set of flash. This is in order to simplify transitions between
            // burning IB and ETH FW.

        if (old_guids && !user_guids) {
            for (i = 0; i < GUIDS; i++) {
                new_guids[i] = old_guids[i];
            }
        }
        
        if (old_guids && !user_macs) {
            for (i = GUIDS; i < MAX_GUIDS; i++) {
                new_guids[i] = old_guids[i];
            }
        }
    
        used_guids = new_guids;
    }   

    if (patch_macs) {

        // To ease upgrade from 4 GUIDS format to 4+2 format, if macs are not
        // explicitly set in flash, they are derived from the GUIDs according to 
        // Mellanox methodology - 48 bit MAC == 64 bit GUID without the middle 16 bits.
        if (old_guids && num_of_old_guids == 4) {
            for (i = 0 ; i < MACS; i++) {
                u_int64_t mac  =  old_guids[i+1].h >> 8;
                mac <<= 24;
                mac |= (old_guids[i+1].l & 0xffffff);

                old_guids[GUIDS+i].h = mac >> 32;
                old_guids[GUIDS+i].l = mac  & 0xffffffff;

                // printf("-D- Guid " GUID_FORMAT " to MAC "MAC_FORMAT"\n", old_guids[i+1].h, old_guids[i+1].l, old_guids[i+GUIDS].h,old_guids[i+GUIDS].l  );
            }
        }

        guid_t* macs = &used_guids[4];
        int i;
                
        for (i = 0 ; i < Operations::MACS ; i++) {
            u_int64_t mac = (((u_int64_t)macs[i].h) << 32) | macs[i].l;
            if (!CheckMac(mac)) {
                printf("*** ERROR *** Bad mac (" MAC_FORMAT ") %s: %s. Please re-burn with a valid -mac flag value.\n", 
                       macs[i].h,
                       macs[i].l,
                       user_macs ? "given" : "found on flash",
                       err());
                return false;
            }
        }
    }

    if (new_guids && old_guids) {
        printGUIDs("    Current settings of",
                   old_guids,
                   patch_guids,
                   patch_macs,
                   old_guids_fmt);
        printf("\n");
    }

    if (interactive) {
        printGUIDs("    You are about to burn the image with the following",
                   used_guids,
                   patch_guids,
                   patch_macs,
                   old_guids_fmt);

        if (!ask_user())
            return false;
    }

    // Path GUIDs section
    if (info->guidPtr) {
        patchGUIDsSection(buf, info->imgStart + info->guidPtr, used_guids, info->guidNum);

        if (info->allImgStart[1]) {
            // For no ConnectX HCAs, patch also the secondary image (if found). This is applicable 
            // only for nofs burn, where both images are burnt as is.
            patchGUIDsSection(buf, info->allImgStart[1] + info->guidPtr, used_guids, info->guidNum);
        }
    }

    return true;
} // patchGUIDs


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                  Revision info and board ID                        //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////

bool Operations::QueryIs (FBase& f, 
                          Operations::ImageInfo* info) {
    u_int32_t signature;

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    if (signature == SIGNATURE) {
        // Full image
        info->isFailsafe = true;
        
        // FW ID
        u_int32_t fw_id;
        
        READ4(f, 0x10, &fw_id, "FW ID");
        TOCPU1(fw_id);
        
        info->isVer   = ( fw_id >> 8) && 0xff;
        info->devRev  = fw_id >> 24;
        
    } else {
        info->isFailsafe = false;
        info->imgStart   = 0;
    }

    info->invSectOk = true;
    return true;
}

bool Operations::QueryPs (FBase& f, 
                          Operations::ImageInfo* info) {

    if (!info->isFailsafe) {
        return errmsg("Internal Error: Tried to query PS when image is not failsafe");
    }

    u_int32_t prim_ptr, scnd_ptr;
    u_int32_t sectSize = f.get_sector_size();

    bool currSielent = _silent;
    _silent = true;

    if (checkPS(f, sectSize, prim_ptr, "Primary  ")) {
        info->allImgStart[0] = prim_ptr;
        info->imgStart = prim_ptr;
        info->psStart  = sectSize;
    } 
    if (checkPS(f, sectSize * 2, scnd_ptr, "Secondary")) {
        info->allImgStart[1] = scnd_ptr;
        if (info->allImgStart[0] == 0) {
            info->imgStart = scnd_ptr;
            info->psStart  = sectSize * 2;
        }
    } 

    if (info->allImgStart[0] == 0 && info->allImgStart[1] == 0)  {
        return errmsg("No valid image found.");
    }

    char       vsd[VSD_LEN+PSID_LEN+1];   // +1  => Leave a space for \0 when psid size == 16 .

    memset(vsd, 0, sizeof(vsd));
    READBUF(f, info->psStart + 0x20, vsd, VSD_LEN+PSID_LEN , "Vendor Specific Data (Board ID)");
    u_int32_t* vsd_dwp = (u_int32_t*)vsd;

    for (u_int32_t i=0; i < sizeof(vsd)/sizeof(u_int32_t); i++)
         vsd_dwp[i] = bswap_32(vsd_dwp[i]);

    memcpy(info->vsd,  vsd,           VSD_LEN);
    memcpy(info->psid, vsd + VSD_LEN, PSID_LEN);

    info->vsd [sizeof(info->vsd)  - 1] = '\0';
    info->psid[sizeof(info->psid) - 1] = '\0';

    _silent = currSielent;

    info->psOk = true;

    return true;
}


bool Operations::QueryImage (FBase& f, 
                             Operations::ImageInfo* info) {

    u_int32_t guid_ptr, nguids;
    guid_t guids[MAX_GUIDS];

    // FW ID
    u_int32_t fw_id;
    u_int32_t fw_id_offs;
    u_int32_t im_start = info->imgStart;

    if (IsCntx()) {
        if (info->isFailsafe && info->actuallyFailsafe) {
            f.set_address_convertor(info->cntxLog2ChunkSize, im_start != 0);
        } else {
            f.set_address_convertor(0,0);
        }

        im_start = 0; // offset is done by address convertor
        info->magicPatternFound = true;
        fw_id_offs = 0x20;
    } else {
        info->magicPatternFound = false;
        fw_id_offs = 0x10;
    }

    READ4(f, im_start + fw_id_offs, &fw_id, "FW ID");
    TOCPU1(fw_id);

    info->devRev  = fw_id >> 24;    
    // Read GUIDs
    READ4(f, im_start + fw_id_offs + 0x14 , &guid_ptr, "GUID PTR");
    TOCPU1(guid_ptr);
    info->guidPtr = guid_ptr;

    guid_ptr += im_start;
    if (guid_ptr >= f.get_size()) {
        return errmsg("Failed to read GUIDs - Illegal GUID pointer (%08x). Probably image is corrupted", guid_ptr);
    }
    READ4(f, guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
    TOCPU1(nguids);
    nguids /= 2;
    if (nguids > MAX_GUIDS) {
        report("Failed to read GUIDs - Illegal Number of GUIDs (%d)\n", nguids);
        return false;
    }
    READBUF(f, guid_ptr, guids, nguids * sizeof(u_int64_t), "GUIDS");
    TOCPUBY64(guids);

    info->guidNum = nguids;
    for (u_int32_t i = 0 ; i < nguids ; i++) {
        info->guids[i] = guids[i];
    }

    // Expansion Rom version:
    if (_rom_sect.empty()) {
        info->expRomFound = false;
    } else {
        info->expRomFound = true;
        if (!GetExpRomVersion(info)) {
            report("\nWarning: Failed to get ROM Version: %s\n\n", err()); 
            info->expRomValidVersion = false;
        }
    }

    // Read Info:
    u_int32_ba info_ptr_ba;
    u_int32_t  info_ptr;
    u_int32_t  info_size;
    u_int8_t   info_ptr_cs = 0;
    READ4(f, im_start + fw_id_offs + 0xC, &info_ptr, "INFO PTR");
    TOCPU1(info_ptr);

    // Verify info_ptr checksum (should be 0)
    info_ptr_ba = info_ptr;
    for (u_int32_t i = 0; i < 4 ; i++) {
        info_ptr_cs += (u_int8_t)info_ptr_ba.range(i*8+7, i*8);
    }

    if (info_ptr_cs) {
        return errmsg("Failed to read Info Section - Bad checksum for Info section pointer (%08x). Probably the image is corrupted.", info_ptr);        
    }

    info_ptr = info_ptr_ba.range(23,0);
    if (info_ptr_cs == 0 && info_ptr != 0) {
        info->infoSectPtr = info_ptr;

        info_ptr += im_start;
        if (info_ptr >= f.get_size()) {
            return errmsg("Failed to read Info Section - Info section pointer (%08x) too large. Probably the image is corrupted.", info_ptr);
        }
        READ4(f, info_ptr - 3*sizeof(u_int32_t), &info_size, "Info section size");
        TOCPU1(info_size);

        // byte size;
        info_size *= 4;

        u_int8_t* info_buff = (u_int8_t*)alloca(info_size);
        READBUF(f, info_ptr, info_buff, info_size, "Info Section");

        if (!ParseInfoSect(info_buff, info_size,  info)) {
            return false;
        }
    }

    info->imageOk = true;
    return true;
}


bool Operations::ParseInfoSect(u_int8_t* buff, u_int32_t byteSize, Operations::ImageInfo *info) {

    u_int32_t *p = (u_int32_t*)buff;
    u_int32_t offs = 0;
    u_int32_t tagNum = 0;
    bool endFound = false;

    while (!endFound && offs < byteSize) {
        u_int32_t tagSize = __be32_to_cpu(*p) & 0xffffff;
        u_int32_t tagId   = __be32_to_cpu(*p) >> 24;

        if (offs + tagSize > byteSize) {
            return errmsg("Info section corrupted: Tag %d (TagId %d, size %d) exceeds Info section size (%d bytes) ",
                          tagNum, tagId, tagSize, byteSize);
        }

        u_int32_t   tmp;
        const char* str;

        switch (tagId) {
        case II_FwVersion:
            info->fwVer[0] = __be32_to_cpu(*(p+1)) >> 16;
            tmp = __be32_to_cpu(*(p+2));
            info->fwVer[1] = tmp >> 16;
            info->fwVer[2] = tmp & 0xffff;
            break;

        case II_DeviceType:
            tmp = __be32_to_cpu(*(p+1));
            info->devType = tmp & 0xffff;
            //info->devRev  = (tmp >> 16) & 0xff;
            break;

        case II_VsdVendorId:
            tmp = __be32_to_cpu(*(p+1));
            info->vsdVendorId = tmp & 0xffff;
            break;

        case II_PSID: 
            // set psid only if not previosly found in PS
            if (!info->psOk) {
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < PSID_LEN ; i++) {
                    info->psid[i] = str[i];
                }
                info->psid[PSID_LEN] = '\0';
            }
            break;

        case II_VSD: 
            // set psid only if not previosly found in PS
            if (!info->psOk) {
                str = (const char*)p;
                str += 4;

                for (int i = 0 ; i < VSD_LEN ; i++) {
                    info->vsd[i] = str[i];
                }
                info->vsd[VSD_LEN] = '\0';
            }
            break;

        case II_ProductVer: 
        
            str = (const char*)p;
            str += 4;

            for (int i = 0 ; i < PRODUCT_VER_LEN ; i++) {
                info->productVer[i] = str[i];
            }
            info->productVer[PRODUCT_VER_LEN] = '\0';
            break;

        case II_End:
            endFound = true;
            break;

        //default:
            //printf("-D- Found tag ID %d of size %d - ignoring.\n", tagId, tagSize);
        }

        if (tagId < II_Last) {
            info->infoOffs[tagId] = offs + 4;
        }

        p    += tagSize/4 + 1;
        offs += tagSize + 4;
        tagNum++;
    }

    if (offs != byteSize) {
        if (endFound) {
            return errmsg("Info section corrupted: Section data size is %x bytes, "
                          "but end tag found after %x bytes.", byteSize, offs);
        } else {
            return errmsg("Info section corrupted: Section data size is %x bytes, "
                          "but end tag not found before section end.", byteSize);
        }
    }

    return true;
}

bool Operations::DisplayExpRomInfo(Operations::ImageInfo* info) {
    report("Rom Info:        ");
    if (info->expRomValidVersion) {
        report("type=");
        switch (info->expRomProductId) {
        case 1   : report("CLP1 "); break;
        case 2   : report("CLP2 "); break;
        case 0x10: report("GPXE "); break;
        default:   report("0x%x ", info->expRomProductId);
        }

        report("version=%d", info->expRomVer[0]);

        if (info->expRomProductId >= 0x10) {
            report(".%d.%d devid=%d", 
                   info->expRomVer[1],
                   info->expRomVer[2],
                   info->expRomDevId);

            if (info->expRomPort) {
                // Do not display if 0 - port independant
                report(" port=%d", info->expRomPort);
            }
        }
        report("\n");
    } else {
        report("N/A\n");
    }
    return true;
}

bool Operations::DisplayImageInfo(Operations::ImageInfo* info) {
    report("Image type:      %s\n", info->magicPatternFound ? "ConnectX"   : 
                                    info->isFailsafe        ? "Failsafe" : 
                                                              "Short");

    if (info->infoOffs[II_FwVersion]) {
        report("FW Version:      %d.%d.%d\n", info->fwVer[0], info->fwVer[1], info->fwVer[2]);
    }

    if (info->infoOffs[II_ProductVer] && strlen(info->productVer)) {
        report("Product Version: %s\n", info->productVer);
    }

    if (info->expRomFound) {
        DisplayExpRomInfo(info);
    }

    if (info->isFailsafe && !IsCntx()) {
        report("I.S. Version:    %d\n", info->isVer );
    }

    if (info->infoOffs[II_DeviceType]) {
        report("Device ID:       %d\n", info->devType);
        if (info->devType == 25204 || info->devType == 24204) {
            _num_ports = 1;
        }
    }

    report("Chip Revision:   %X\n", info->devRev);

    // GUIDS:
    // TODO: Handle case where devtype not found.

    bool ib_dev  = !IsCntx() || CntxIsIb(info->devType);
    bool eth_dev = IsCntx()  && CntxIsEth(info->devType);
    
    if (!ib_dev && !eth_dev) {
        // Unknown device id - for forward compat - assume that ConnectX is MP and
        // prev HCAs are IB only (these flags are for printing only - no real harm can be done).
        ib_dev = true;
        if (IsCntx()) {
            eth_dev = true;
        }
    }

    char* mac_indent = "";
    if (ib_dev) {
        //report("GUID Des:        Node             Port1            ");        
        report("Description:     Node             Port1            ");

        if (_num_ports > 1)
            report("Port2            ");
        report( "Sys image\n");
        
        report("GUIDs:           ");
        for (u_int32_t i=0; i < GUIDS; i++) {
            if (i != 2 || _num_ports > 1 ) 
                report(GUID_FORMAT " ", info->guids[i].h, info->guids[i].l);
        }
        mac_indent = "                 ";
    }

    // MACS:
    if (eth_dev) {
        if (info->guidNum == MAX_GUIDS) {
            if (!ib_dev) 
                report("Description:%s     Port1            Port2\n", mac_indent);
            else 
                printf("\n");
            
            report("MACs:    %s        ", mac_indent);
            for (u_int32_t i=GUIDS; i < MAX_GUIDS; i++) {
                report(MAC_FORMAT "     ", info->guids[i].h, info->guids[i].l);
            }

            for (u_int32_t i=GUIDS; i < MAX_GUIDS; i++) {
                u_int64_t mac = (((u_int64_t)info->guids[i].h) << 32) | info->guids[GUIDS + i].l;
                if (!CheckMac(mac)) {
                    if (i==GUIDS) printf("\n\n");
                    printf("Warning: Bad mac address (" MAC_FORMAT "): %s\n", info->guids[i].h, info->guids[i].l, err());
                }
            }
        } else {
            printf("\nWarning: Can not get MAC addrerss: Expecting %d entries in guid section, got %d. Probably an old FW image. Please update.\n",
                   MAX_GUIDS,
                   info->guidNum);
        }
    }

    // VSD, PSID
    if (!info->infoOffs[II_VsdVendorId] || info->vsdVendorId == MELLANOX_VENDOR_ID) {
        report("\nBoard ID:        %s", info->vsd);
        if (info->psid[0])
            report(" (%s)\n", info->psid);
        else
            report("\n");

        report("VSD:             %s\n", info->vsd);
        report("PSID:            %s\n", info->psid);
    } else {
        report("\n\nWarning: Not a Mellanox FW image (vendor_id = 0x%04x). VSD and PSID are not displayed.\n\n", info->vsdVendorId);
    }

    return true;
}


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                           MAIN                                     //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
// sed -e 's/"/\\"/g' < flint.txt | perl -pe 's/^(.*)$/"$1\\n"/'
void usage(const char *sname, bool full = false)
{
    const char *descr =
    "\n"
    "               FLINT - FLash INTerface\n"
    "\n"
    "FW (firmware) burning and flash memory operations tool for\n"
    "Mellanox Infiniband HCAs and Ethernet NIC cards.\n"
    "\n"
    "Usage:\n"
    "------\n"
    "\n"
    "    " FLINT_NAME " [switches...] <command> [parameters...]\n"
    "\n"
    "\n"
    "Switches summary:\n"
    "-----------------\n"
//    "    -bsn <BSN>         - Mellanox Board Serial Number (BSN).\n"
//    "                         Valid BSN format is:\n"
//    "                                 MTxxxxx[-]R[xx]ddmmyy-nnn[-cc]\n"
 //   "                         Commands affected: burn\n"
    "\n"
    "    -crc               - Print out each section CRC.\n"
    "                         Commands affected: verify\n"
    "\n"
    "    -d[evice] <device> - Device flash is connected to.\n"
    "                         Commands affected: all\n"
    "\n"
    "    -guid <GUID>       - GUID base value. 4 GUIDs\n"
    "                         are automatically assigned to the\n"
    "                         following values:\n"
    "\n"
    "                         guid   -> node GUID\n"
    "                         guid+1 -> port1\n"
    "                         guid+2 -> port2\n"
    "                         guid+3 -> system image GUID.\n"
    "\n"
    "                         Note: port2 guid will be assigned even for a"
    "                         single port HCA - The HCA ignores this value.\n"
    "\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -guids <GUIDs...>  - 4 GUIDs must be specified here.\n"
    "                         The specified GUIDs are assigned\n"
    "                         the following values, repectively:\n"
    "                         node, port1, port2 and system image GUID.\n"
    "\n"
    "                         Note: port2 guid must be specified even for a\n"
    "                         single port HCA - The HCA ignores this value.\n"
    "                         It can be set to 0x0.\n"
    "\n"
    "                         Commands affected: burn\n"
    "\n"

    "    -mac <MAC>         - MAC address base value. 2 MACs\n"
    "                         are automatically assigned to the\n"
    "                         following values:\n"
    "\n"
    "                         mac    -> port1\n"
    "                         mac+1  -> port2\n"
    "\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -macs <MACs...>    - 2 MACs must be specified here.\n"
    "                         The specified MACs are assigned\n"
    "                         to port1, port2, repectively.\n"
    "\n"
    "                         Commands affected: burn\n"
    "                         Note: -mac/-macs flags are applicable only for Mellanox\n"
    "                               Technologies ethernet products.\n"
    "\n"
    "    -clear_semaphore   - Force clear the flash semaphore on the device.\n"
    "                         No command is allowed when this flag is used.\n"
    "                         NOTE: May result in system instability or flash\n"
    "                               corruption if the device or another\n"
    "                               application is currently using the flash.\n"
    "                               Exercise caution.\n"
    "\n"
    "    -h[elp]            - Prints this message and exits\n"
    "    -hh                - Prints extended command help\n"
    "\n"
    "    -i[mage] <image>   - Binary image file.\n"
    "                         Commands affected: burn, verify\n"
    "\n"
    "    -nofs              - Burn image in a non failsafe manner.\n"
    "\n"
    "    -skip_is           - Allow burning the FW image without updating the invariant sector,\n"
    "                         to ensure failsafe burning even when an invariant sector difference is detected.\n"
    "                         See the specific FW release notes for more details.\n"
    "\n"
    "    -byte_mode         - Shift address when accessing flash internal registers. May\n"
    "                         be required for burn/write commands when accessing certain\n"
    "                         flash types.\n" 
    "\n"
#if 0
    "    -unlock            - Use unlock bypass feature of the flash for quicker burn.\n"
    "                         Commands affected: burn\n"
    "\n"
#endif
    "    -s[ilent]          - Do not print burn progress flyer.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -y[es]             - Non interactive mode - assume answer\n"
    "                         \"yes\" to all questions.\n"
    "                         Commands affected: all\n"
    "\n"
    "    -vsd  <string>     - Write this string, of up to 208 characters, to VSD when burn.\n"
    "\n"
    "    -use_image_ps      - Burn vsd as appears in the given image - do not keep existing VSD on flash.\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -dual_image        - Make the burn process burn two images on flash (previously default algorithm). Current\n" 
    "                         default failsafe burn process burns a single image (in alternating locations).\n"
    "                         Commands affected: burn\n"
    "\n"
    "    -v                 - Version info.\n"
    "\n"
    "Commands summary (use -hh flag for full commands description):\n"
    "-----------------\n"
    "  b[urn]              - Burn flash\n"
    "  q[uery]             - Query misc. flash/firmware characteristics\n"
    "  v[erify]            - Verify entire flash\n"
    "  bb                  - Burn Block - Burns the given image as is. \n"
    "                        No checks are done.\n"
    "  ri       <out-file> - Read the fw image on the flash.\n"
    "  dc       [out-file] - Dump Configuration: print fw configuration file\n"
    "                        for the given image.\n"
    "  e[rase]  <addr>     - Erase sector\n"
    "  rw       <addr>     - Read one dword from flash\n"
    "  ww       <addr> < data> \n"
    "                      - Write one dword to flash\n"
    "  wwne     <addr>     - Write one dword to flash without sector erase\n"
    "  wbne     <addr> <size> <data ...> \n"
    "                      - Write a data block to flash without sector erase\n"
    "  rb       <addr> <size> [out-file]\n"
    "                      - Read  a data block from flash\n"
    "\n";

    const char* full_descr =
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
    "* Burn Block\n"
    "  Burns entire flash from raw binary image as is. No checks are done on the flash or\n"
    "  on the given image file. No fields (such as VSD or Guids) are read from flash. \n"
    "\n"
    "    Command:\n"
    "        bb\n"
    "    Parameters:\n"
    "        None\n"
    "    Examples:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " -i image1.bin bb\n"
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
    "* Query flash device parameters (Common Flash Interface)\n"
    "\n"
    "    Command:\n"
    "        cfi\n"
    "    Parameters:\n"
    "        None\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " cfi\n"
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
    "\n"
    "* Read a data block from the flash and write it to a file or to screen.\n"
    "\n"
    "    Command:\n"
    "        rb\n"
    "    Parameters:\n"
    "        addr - address of block\n"
    "        size - size of data to read in bytes\n"
    "        file - filename to write the block (raw binary). If not given, the data\n"
    "               is printed to screen\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " rb 0x10000 100 file.bin\n"
    "\n"
    "* Read the FW image from flash and write it to a file.\n"
    "\n"
    "    Command:\n"
    "        ri\n"
    "    Parameters:\n"
    "        file - filename to write the image to (raw binary).\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " ri file.bin\n"
    "\n"
    "* Write a block of data to the flash without erasing.\n"
    "\n"
    "    Command:\n"
    "        wbne\n"
    "    Parameters:\n"
    "        addr - address of block\n"
    "        size - size of data to write in bytes\n"
    "        data - data to write - space seperated dwords\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " wbne 0x10000 12 0x30000 0x76800 0x5a445a44\n"
    "\n"
    "* Print (to screen or to a file) the FW configuration text file used by the image generation process.\n"
    "  This command would fail if the image does not contain a FW configuration section. Existence of this\n"
    "  section depends on the version of the image generation tool.\n"
    "\n"
    "    Command:\n"
    "        dc\n"
    "    Parameters:\n"
    "        file - (optional) filename to write the dumped configuration to. If not given, the data\n"
    "               is printed to screen\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " dc\n"
    "\n";

    printf(descr, sname);

    if (full) {
        printf(full_descr, sname);
    }
}


//
// Signal handlers 
//

Flash* g_flash = NULL;

#ifdef _WIN32
HANDLE g_hMainTread = GetCurrentThread();
#endif



int g_signals_for_termination[] = {
    SIGINT,
#ifndef _WIN32
    SIGHUP,
#endif
    SIGTERM
};



void TerminationHandler (int signum)
{
    static volatile sig_atomic_t fatal_error_in_progress = 0;

#ifdef _WIN32
    if (signum == 0) {

        report ("\nWarning: Got SIGINT. Raising SIGTERM\n");
        raise(SIGTERM);
        return;
    }

    report ("\nWarning: This program can not be interrupted.Please wait for its termination.\n");
    signal(signum, TerminationHandler);
    return;
#endif


    if (fatal_error_in_progress)
        raise (signum);
    fatal_error_in_progress = 1;

    signal (signum, SIG_DFL);

    if (g_flash != NULL) {
        report("\n Received signal %d. Cleaning up ...", signum);
        fflush(stdout);
        sleep(1); // let erase sector end
        //g_flash->wait_ready("Process termination");

        g_flash->close();
        report(" Done.\n");
    }
    raise(signum);
}

//
// Commands database and parsing methods
//
enum CommandInput {
    CI_NONE         = 0x01,
    CI_IMG_ONLY     = 0x02,
    CI_DEV_ONLY     = 0x04,
    CI_IMG_OR_DEV   = 0x06,
    CI_IMG_AND_DEV  = 0x08
};

enum CommandType {
    CMD_UNKNOWN,
    CMD_BURN,
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
    CMD_READ_IMAGE,
    CMD_CFI,
    CMD_CLEAR_SEM
};

struct CommandInfo {
    CommandType  cmd;
    const char*  cmdName;
    bool         requireExactMatch;
    int          maxArgs;
    CommandInput requiredInput;
    const char*  cmdDescription;
 
};

CommandInfo const g_commands[] = {
    { CMD_BURN           , "burn"  ,false , 0 , CI_IMG_AND_DEV , ""},
    { CMD_BURN_BLOCK     , "bb"    ,true  , 0 , CI_IMG_AND_DEV , ""},
    { CMD_QUERY_FORCE    , "qf"    ,true  , 0 , CI_IMG_OR_DEV  , ""},
    { CMD_QUERY          , "query" ,false , 0 , CI_IMG_OR_DEV  , ""},
    { CMD_QUERY_ROM      , "qrom"  ,true  , 0 , CI_IMG_ONLY    , ""},
    { CMD_VERIFY         , "verify",false , 0 , CI_IMG_OR_DEV  , ""},            
    { CMD_READ_WORD      , "rw"    ,true  , 1 , CI_DEV_ONLY    , ""},      
    { CMD_READ_BLOCK     , "rb"    ,true  , 3 , CI_IMG_OR_DEV  , ""},
    { CMD_WRITE_WORD     , "ww"    ,true  , 2 , CI_DEV_ONLY    , ""},    
    { CMD_WRITE_WORD_NE  , "wwne"  ,true  , 2 , CI_DEV_ONLY    , ""},    
    { CMD_WRITE_BLOCK    , "wb"    ,true  , 2 , CI_DEV_ONLY    , ""},   
    { CMD_WRITE_BLOCK_NE , "wbne"  ,true  ,-1 , CI_DEV_ONLY    , ""}, 
    { CMD_ERASE_SECT     , "erase" ,false , 1 , CI_DEV_ONLY    , ""},     
    { CMD_DUMP_CONF      , "dc"    ,true  , 1 , CI_IMG_OR_DEV  , ""},
    { CMD_READ_IMAGE     , "ri"    ,true  , 1 , CI_DEV_ONLY    , ""},
    { CMD_CLEAR_SEM      , "clear_semaphore"    ,true  , 0 , CI_DEV_ONLY    , ""},
    { CMD_CFI            , "cfi"   ,true  , 0 , CI_DEV_ONLY    , ""}
};

#define numbel(x) (sizeof(x)/sizeof((x)[0]))


const CommandInfo* GetCommandInfo(CommandType cmd) {
    for (u_int32_t i = 0 ; i < numbel(g_commands); i++ ) {
        if (cmd == g_commands[i].cmd) {
            return &g_commands[i];
        }
    }

    return NULL;
}

CommandType ParseCommand(const char* cmd) {
    u_int32_t cmdLenGiven = strlen(cmd);

    for (u_int32_t i = 0 ; i < numbel(g_commands); i++ ) {
        if (g_commands[i].requireExactMatch ) {
            if (!strcmp(cmd, g_commands[i].cmdName)) {
                return g_commands[i].cmd;
            }
        } else {
            // Match if given cmd maches the beginning of the checked cmd 
            if (!strncmp(cmd, g_commands[i].cmdName, cmdLenGiven )) {
                return g_commands[i].cmd;
            }
        }
    }
    return CMD_UNKNOWN;
}


bool CheckCommandInputs(const char* dev, 
                        const char* img, 
                        CommandType cmd) {

    const CommandInfo* cmdInfo = GetCommandInfo(cmd);

    if (!cmdInfo) {
        printf("*** INTERNAL ERROR *** Unknown command given to CheckCommandInputs() (%d)\n", cmd);
        return false;
    }

    char* inputDesStr [] = {
        NULL,
        "neither a device nor an image file",       // CI_NONE
        "an image file",                            // CI_IMG_ONLY,
        NULL,
        "a device",                                 // CI_DEV_ONLY,
        NULL,
        "either an image file or a device",         // CI_IMG_OR_DEV,
        NULL,
        "both an image file and a device"           // CI_IMG_AND_DEV
    };

    CommandInput given;

    if        ( dev && img) {
        given = CI_IMG_AND_DEV;
    } else if (!dev && img) {
        given = CI_IMG_ONLY;
    } else if (dev && !img) {
        given = CI_DEV_ONLY;
    } else {
        given = CI_NONE;
    }

    if ((given & cmdInfo->requiredInput) == 0) {
        printf("*** ERROR *** Command \"%s\" requires %s to be specified",
               cmdInfo->cmdName,
               inputDesStr[cmdInfo->requiredInput]);
    
        if (given != CI_NONE) {
            printf(", but %s %s given.\n",
                   inputDesStr[given],
                   given == CI_IMG_AND_DEV ? "are" : "is");
        } else {
            printf(".\n");
        }

        return false;
    }

    return true;
}

bool CheckMaxCmdArguments(CommandType cmd, int numArgs) {
    const CommandInfo* cmdInfo = GetCommandInfo(cmd);
    if (!cmdInfo) {
        printf("*** INTERNAL ERROR *** Unknown command given to CheckMaxCmdArguments (%d)\n", cmd);
        return false;
    }

    if (cmdInfo->maxArgs >= 0 && numArgs > cmdInfo->maxArgs) {
        printf("*** ERROR *** Command \"%s\" requires %d arguments, but %d arguments were given\n",
               cmdInfo->cmdName,
               cmdInfo->maxArgs,
               numArgs);
        return false;
    }
    return true;
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

#define SETERR(args) do { printf("*** ERROR *** "); printf args; printf("\n"); return 1; } while(0)


int main(int ac, char *av[])
{

    char         *image_fname=0, *device=0;
    bool         clear_semaphore  = false;
    bool         silent           = false; 
    bool         guids_specified  = false;
    bool         macs_specified   = false;
    bool         burn_failsafe    = true;
    bool         use_image_ps     = false;
    bool         single_image_burn = true;

    char*        cmdStr           = NULL;

    char         *user_vsd=0;
    char         *user_psid=0;
    guid_t       user_guids[Operations::MAX_GUIDS];
    int		 rc = 0;

    CommandType cmd = CMD_UNKNOWN;

    auto_ptr<Flash>       f;
    FImage                fim;

    Operations            ops;

    FBase*      fbase     = NULL;
    char*       cmdTarget = NULL;
    char*       cmdAccess = NULL;

    bool        cntx_image  = false;
    bool        cntx_device = false;
    //
    // Map termination signal handlers
    //
    int i;
    for (i = 0 ; i < (int)(sizeof(g_signals_for_termination)/sizeof(g_signals_for_termination[0])) ; i++ ) {
        signal (g_signals_for_termination[i], TerminationHandler);    
    }

    if (ac < 2) {
        usage(av[0]);
        rc =  1; goto done; 
    }

    // Init with FFs - for ConnectX if only MAC or GUID is specified
    memset(user_guids, 0xff, sizeof(user_guids));

    // Go thru command line options
    for (i=1; i < ac; i++) {
        //
        // Switches
        // --------
        //
        if (*av[i] == '-') {
            int switchLen = strlen(av[i]);

            if (!strcmp(av[i], "-dual_image"))
                single_image_burn = false;

	    else if (!strcmp(av[i], "-clear_semaphore")) {
                clear_semaphore = true;
	    }

            else if (!strncmp(av[i], "-device", switchLen)) {
                NEXTS("-device");
                device = av[i];

            } else if (!strcmp(av[i], "-v") || !strcmp(av[i], "-vv")) {
                printf("%s: %s .",
                       av[0],
                       _versionID);

                if (!strcmp(av[i], "-vv")) {
                    printf(" SVN %s", _svnID + 1); 
                }

                printf("\n");
                rc =  0; goto done; 

            } else if (!strcmp(av[i], "-unlock")) {
                _unlock_bypass = true;  
            } else if (!strcmp(av[i], "-noerase"))
                _no_erase = true;
            else if (!strcmp(av[i], "-noburn"))
                _no_burn = true;
            else if (!strcmp(av[i], "-crc"))
                _print_crc = true;
            else if (!strcmp(av[i], "-bytewrite")) {
                if (device) {
                    printf("\"-bytewrite\" should be specifies before \"-device\" switch in the command line.\n");
                    rc =  1; goto done; 
                }
                _byte_write = true;
            } else if (!strcmp(av[i], "-vsd")) {
                NEXTS("-vsd");
                user_vsd = av[i];
            }
            // -vsd1 is an alias to -vsd, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd1")) {
                NEXTS("-vsd1");
                user_vsd = av[i];
            } else if (!strcmp(av[i], "-psid")) {
                NEXTS("-psid");
                user_psid = av[i];
            }
            // -vsd2 is an alias to psid, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd2")) {
                NEXTS("-vsd2");
                user_psid = av[i];
            } else if (!strcmp(av[i], "-bsn")) {
                NEXTS("-bsn");
                GETBSN(av[i], &user_guids[0]);
                for (int i=1; i<Operations::GUIDS; i++) {
                    u_int64_t g=user_guids[0].h;
                    g=(g<<32) | user_guids[0].l;
                    g += i;
                    user_guids[i].h = (u_int32_t)(g>>32);
                    user_guids[i].l = (u_int32_t)g;
                }
                guids_specified = true;
            } else if (!strncmp(av[i], "-image", switchLen)) {
                NEXTS("-image");
                image_fname = av[i];
            } else if (!strcmp(av[i], "-guid")) {
                NEXTS("-guid");
                GETGUID(av[i], &user_guids[0]);
                for (int i=1; i<Operations::GUIDS; i++) {
                    u_int64_t g=user_guids[0].h;
                    g=(g<<32) | user_guids[0].l;
                    g += i;
                    user_guids[i].h = (u_int32_t)(g>>32);
                    user_guids[i].l = (u_int32_t)g;
                }
                guids_specified = true;
            } else if (!strcmp(av[i], "-guids")) {
                if (i + 4 >= ac) {
                    printf("Exactly four GUIDs must be specified.\n");
                    rc =  1; goto done;                    
                }
                i++;
                for (int j=0; j<Operations::GUIDS; j++) {
                    GETGUID(av[i+j], &user_guids[j]);
                }
                i += 3;
                guids_specified = true;

            } else if (!strcmp(av[i], "-mac")) {
                NEXTS("-mac");
                GETGUID(av[i], &user_guids[Operations::GUIDS]);
                for (int i=1; i < Operations::MACS ; i++) {
                    u_int64_t g=user_guids[Operations::GUIDS].h;
                    g=(g<<32) | user_guids[Operations::GUIDS].l;
                    g += i;
                    user_guids[Operations::GUIDS + i].h = (u_int32_t)(g>>32);
                    user_guids[Operations::GUIDS + i].l = (u_int32_t)g;
                }
                macs_specified = true;
            } else if (!strcmp(av[i], "-macs")) {
                if (i + 2 >= ac) {
                    printf("Exactly two MACs must be specified.\n");
                    rc =  1; goto done;                    
                }
                i++;
                for (int j=0; j<Operations::MACS; j++) {
                    GETGUID(av[i+j], &user_guids[Operations::GUIDS+j]);
                }
                i += 1;
                macs_specified = true;
            } else if (!strncmp(av[i], "-silent", switchLen))
                silent = true;
            else if (!strncmp(av[i], "-use_image_ps", 2))
                use_image_ps = true;
            else if (!strncmp(av[i], "-nofs", 5))
                burn_failsafe = false;
            else if (!strcmp(av[i], "-skip_is"))
                ops.SetAllowSkipIs(true);
            else if (!strcmp(av[i], "-striped_image"))
                ops.SetCntxStripedImage(true);
            else if (!strncmp(av[i], "-yes", switchLen))
                _assume_yes = true;
            else if (!strcmp(av[i], "-no"))
                _assume_no = true;
            else if (!strcmp(av[i], "-byte_mode"))
                Flash::_byte_mode = true;

            else if (!strncmp(av[i], "-hh", 3) ||  !strncmp(av[i], "--hh", 4)) {
                usage(av[0], true);
                rc =  0; goto done; 
            } else if (!strncmp(av[i], "-help", switchLen) ||  !strncmp(av[i], "--h", 3)) {
                usage(av[0]);
                rc =  0; goto done; 
            } else {
                printf("*** ERROR *** Invalid switch \"%s\" is specified.\n", av[i]);
                rc =  1; goto done; 
            }
        }  else {
            // command
            cmdStr = av[i];
            break;
        }
    }

    if (_assume_yes && _assume_no) {
        printf("*** ERROR *** -yes and -no options can not be specified together.\n");
        rc =  1; goto done; 
    }

    //
    // Commands
    // --------
    //

    if (clear_semaphore) {
        if (cmdStr) {
            printf("*** ERROR *** No command is allowed when -clear_semaphore flag is given.\n");
            rc =  1; goto done; 
        } else {
            cmdStr = "clear_semaphore";
        }
    }

    if (!cmdStr) {
        printf("*** ERROR *** No command given. See help for details.\n");  
        rc =  1; goto done; 
    }

    //
    // Check and parse command
    //
    cmd = ParseCommand(cmdStr);

    if (cmd == CMD_UNKNOWN) {
        printf("*** ERROR *** Invalid command \"%s\".\n", av[i]);
        rc =  1; goto done; 
    }

    if (cmd == CMD_CLEAR_SEM) {
        clear_semaphore = true;
    }

    if (!CheckCommandInputs(device, image_fname, cmd)) {
        rc = 1; goto done;
    }

    if (!CheckMaxCmdArguments(cmd, ac - i - 1 )) {
        rc = 1; goto done;
    }

    if (device) {
        // Open the device
        auto_ptr<Flash>       tmp(new Flash);
        f = tmp;
        
        if (f.get() == NULL) {
            printf("*** ERROR *** Memory allocation failed\n");
            rc =  1; goto done; 
        }
               
        g_flash = f.get();
        if (!f->open(device, clear_semaphore)) {
            printf("*** ERROR *** Can not open %s: %s\n", device, f->err());
            rc =  1; goto done; 
        }

        ops.SetNumPorts(f->get_port_num());

        cmdTarget = "Flash";
        cmdAccess = device;
        fbase     = f.get();

        // Connectx Mode:
        cntx_device = ops.CheckIsCntx(*fbase);
    }

    if (image_fname) {
        if (!fim.open(image_fname)) {
            printf("*** ERROR *** Image file open failed: %s\n", fim.err());
            rc =  1; goto done; 
        }

        cmdTarget = "Image file";
        cmdAccess = image_fname;
        fbase     = &fim;

        // Connectx Mode:
        cntx_image = ops.CheckIsCntx(fim);
    }

    ops.SetCntxMode(cntx_image || cntx_device);

    switch (cmd) {
    case CMD_BURN:
    case CMD_BURN_BLOCK:
    {
        
        //
        // BURN
        //
        Operations::ImageInfo fileInfo;
        Operations::ImageInfo flashInfo;
        bool burn_block = (cmd == CMD_BURN_BLOCK);
                
        if (!burn_block) {

            if (cntx_image != cntx_device) {
                printf("*** ERROR *** The given device is %sa ConnectX HCA, but the given image file %s a ConnectX FW image\n", 
                       cntx_device ? ""         : "not ",
                       cntx_image  ? "contains" : "does not contain");
                rc =  1; goto done; 
            }

            // Make checks and replace vsd/guids.    
            bool old_silent = _silent;
            _silent = true;
            if (!ops.Verify(fim, &fileInfo) || !ops.QueryAll(fim, &fileInfo)) {
                printf("*** ERROR *** %s: Not a valid image file (%s)\n", image_fname, ops.err());
                rc =  1; goto done; 
            }
                        
            // Get GUID and VSD info from flash
            
            bool read_guids = true;
            bool read_ps    = true;
            
            // Flash query (unlike image file query) does not have to
            // pass. E.G. blank flash and the user supplies the needed data (guids, vsd).
            
            bool flash_query_res = ops.Verify(*f, &flashInfo) && ops.QueryAll(*f, &flashInfo);

            bool ib_dev  = !ops.IsCntx() || ops.CntxIsIb(fileInfo.devType);
            bool eth_dev = ops.IsCntx()  && ops.CntxIsEth(fileInfo.devType);
            bool unknowd_dev = false;

            if (!ib_dev && !eth_dev) {
                // Unknown device id - for forward compat - assume that ConnectX is MP and
                // prev HCAs are IB only (these flags are for printing only - no real harm can be done).
                unknowd_dev = true;
                ib_dev = true;
                if (ops.IsCntx()) {
                    eth_dev = true;
                }
            }

            if ((user_vsd && user_psid) || use_image_ps)
                read_ps = false;

            if (guids_specified && ib_dev || macs_specified && eth_dev)
                read_guids = false;

            if (read_guids && !flash_query_res) {
                char* missing_info;
                char* missing_flags;

                if (ib_dev && eth_dev) {
                    missing_info  = "GUIDs / MACs";
                    missing_flags = "-guid(s) / -mac(s)";
                } else if (ib_dev) {
                    missing_info  = "GUIDs";
                    missing_flags = "-guid(s)";
                } else {
                    missing_info  = "MACs";
                    missing_flags = "-mac(s)";
                }

                if (read_guids && !flashInfo.imageOk) {
                    printf("\n");
                    printf("*** ERROR *** Can not extract %s info from flash. "
                           "Please specify %s (using command line flags %s ). \n", missing_info, missing_info, missing_flags);
                }
                
                if (burn_failsafe) {
                    printf("              Can not burn in a failsafe mode.\n");
		    printf("              If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                }
                rc =  1; goto done;
            }

            // Patch GUIDS
            if  (guids_specified || macs_specified) {
                if (!ops.IsCntx() && macs_specified) {
                    printf("*** ERROR *** -mac flag is not applicable for IB MT%d device.\n",
                           fileInfo.devType);
                    rc =  1; goto done;
                } else if ((ib_dev && eth_dev) && !(guids_specified && macs_specified)) {
                    printf("*** ERROR *** Use both -mac and -guid flags for %s device id %d.\n",
                           unknowd_dev ? "unknown" : "Multi-Protocol",
                           fileInfo.devType);
                    rc =  1; goto done;
                } else if (ib_dev  && !guids_specified) {
                    printf("*** ERROR *** Use -guid(s) flag for IB MT%d device.\n",
                           fileInfo.devType);
                    rc =  1; goto done;
                } else if (eth_dev && !macs_specified) {
                    printf("*** ERROR *** Use -mac(s) flag for ETH MT%d device.\n",
                           fileInfo.devType);
                    rc =  1; goto done;
                }

                if (!ops.patchGUIDs(fim,
                                    &fileInfo,
                                    ib_dev,
                                    eth_dev,
                                    guids_specified,
                                    macs_specified,
                                    user_guids,
                                    flashInfo.imageOk ? flashInfo.guids : NULL,
                                    flashInfo.guidNum,
                                    true)) {
                    rc =  1; goto done;
                }
            } else {
                if (!ops.patchGUIDs(fim,
                                    &fileInfo,
                                    ib_dev,
                                    eth_dev,
                                    false,
                                    false,
                                    NULL,  
                                    flashInfo.guids,
                                    flashInfo.guidNum,
                                    false)) {
                    rc =  1; goto done;
                }
            }

            if (burn_failsafe && (!fileInfo.isFailsafe || !flashInfo.isFailsafe)) {
                printf("*** ERROR *** Failsafe burn failed: FW image in the %s is non failsafe.\n",         fileInfo.isFailsafe ? "flash" : "given file");
                printf("              It is impossible to burn %sa non failsafe image in a failsafe mode.\n", fileInfo.isFailsafe ? "over " : "");
                printf("              If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                rc =  1; goto done; 
            }

            if (!user_vsd && !(flashInfo.psOk || (flashInfo.infoOffs[Operations::II_PSID] && 
                                                flashInfo.infoOffs[Operations::II_VSD]  ))) {
                printf("\n");
                if (burn_failsafe) {

                    printf("*** ERROR *** Can not extract VSD/PSID info from flash.\n"
                           "              Can not burn in a failsafe mode. Please use \"-nofs\" flag to burn in a non failsafe mode.\n");
                    rc =  1; goto done;
                }  else {
                    printf("*** WARNING *** Can not extract VSD/PSID info from flash.\n\n"
                           "    To use a specific VSD, abort and re-burn specifying the\n"
                           "    needed info (using command line flags -vsd / -use_image_ps).\n"
                           "    You can also continue burn using blank VSD.\n");
                
                    if (!ops.ask_user()) {
                        rc =  1; goto done;
                    }
                }
            }

            // Print FW versions:
            printf("\n");
            printf("    Current FW version on flash:  ");
            if (flashInfo.infoOffs[Operations::II_FwVersion]) {
                printf("%d.%d.%d\n", flashInfo.fwVer[0], flashInfo.fwVer[1], flashInfo.fwVer[2]);  
            } else {
                printf("N/A\n");
            }
            
            printf("    New FW version:               ");
            if (fileInfo.infoOffs[Operations::II_FwVersion]) {
                printf("%d.%d.%d\n", fileInfo.fwVer[0], fileInfo.fwVer[1], fileInfo.fwVer[2]);  
            } else {
                printf("N/A\n");
            }

            bool updateRequired = true;

            if (fileInfo.infoOffs[Operations::II_FwVersion]  && 
                flashInfo.infoOffs[Operations::II_FwVersion]) {

                updateRequired = ops.FwVerLessThan(flashInfo.fwVer,fileInfo.fwVer);
            }

            if (!updateRequired) {
                printf("\n    Note: The new FW version is not newer than the current FW version on flash.\n");
                if (! ops.ask_user()) {
                    // NOTE: on aborting because of lower fw version, a GOOD status is returned.
                    rc =  0; goto done;
                }
            }

            if (!use_image_ps) {
                if (fileInfo.psOk || (ops.IsCntx() && fileInfo.infoOffs[Operations::II_VSD])) {
                    if (!ops.patchVSD(fim, 
                                      &fileInfo,
                                      user_vsd, 
                                      user_psid,
                                      flashInfo.vsd,
                                      NULL,
                                      fileInfo.psid )) {
                        rc =  1; goto done;
                    }
                }
            }

            // Check PSID
            if (fileInfo.infoOffs[Operations::II_PSID]  && 
                flashInfo.infoOffs[Operations::II_PSID] && 
                strncmp( fileInfo.psid, flashInfo.psid, PSID_LEN)) {
                printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"
                       "    Note: It is highly recommended not to change the PSID.\n",
                       flashInfo.psid, 
                       fileInfo.psid);

                if (! ops.ask_user()){
                    rc =  1; goto done;
                }
            }           

            // Check exp rom:
            if (!fileInfo.expRomFound && flashInfo.expRomFound) {
                printf("\n    Expansion-ROM mismatch: \n"
                       "    Current FW on flash contains an expansion-ROM.\n"
                       "    The new FW image does not contain an expansion-ROM\n");

                if (! ops.ask_user()){
                    rc =  1; goto done;
                }
            }

            _silent = old_silent;

        } else {
            // BURN BLOCK:
            burn_failsafe = false;
        }

        // Burn it
        if (burn_failsafe) {
            // FS burn
            bool ret;
            if (ops.IsCntx()) {
                ret = ops.CntxFailSafeBurn(*f,
                                           fim,
                                           !silent,
                                           &flashInfo,
                                           &fileInfo,
                                           false);
                                           
            } else {
                ret = ops.FailSafeBurn(*f, 
                                       fim,
                                       !silent,
                                       single_image_burn);
            }

            if (!ret) {
		if (f->err()) {
		    // The error is in flash access:
		    printf("*** ERROR *** Flash access failed during burn: %s\n", f->err());
		} else {
		    // operation/ algorithm error:
		    printf("*** ERROR *** Failsafe burn error: %s\n", ops.err());  
		}
                rc =  1; goto done; 
            }
        } else {
            //
            // Not failsafe (sequential) burn
            //

            // Ask is it OK
            printf("\n");
            if (burn_block) {
                printf("Block burn: The given image will be burnt as is. No fields (such\n");
                printf("as GUIDS,VSD) are taken from current image on flash.\n");
            }
            printf("Burn process will not be failsafe. No checks will be performed.\n");

            printf("ALL flash, including the Invariant Sector will be overwritten.\n");
            printf("If this process fails, computer may remain in an inoperable state.\n");

            if (!ops.ask_user()) {
                rc =  1; goto done;
	    }

            // Non FS burn
            bool ret;
            if (ops.IsCntx() && !burn_block) {
                ret = ops.CntxFailSafeBurn(*f,
                                           fim,
                                           !silent,
                                           &flashInfo,
                                           &fileInfo,
                                           true); // Allow nofs
            } else {
                ret = ops.write_image(*f, 0, fim.getBuf(), fim.getBufLength(),!silent);
            }

        
            if (!ret) {
                report("\n");
                printf("*** ERROR *** Non failsafe burn failed: %s\n", ops.err());
                rc =  1; goto done; 
            }
            report("\n");
        }
    }
    break;

    case CMD_ERASE_SECT:
    {    
        //
        // ERASE SECTOR <ADDR>
        //     Parameters: <ADDR>
        //
        u_int32_t    addr;
        char         *endp;

        // Address of sector to erase
        NEXTC("<ADDR>", "erase");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }

        // Erase
        if (!f->erase_sector(addr)) {
            printf("*** ERROR *** Erase sector failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_QUERY_FORCE:
    case CMD_QUERY:
    {
        // QUERY
        Operations::ImageInfo info;
        bool imageOk;

        _silent       = true;
        imageOk = ops.Verify(*fbase, &info);
        _silent = false;

        if (!imageOk) {
            if (cmd == CMD_QUERY_FORCE) {
                printf("\n*** WARNING *** Trying to run query on a corrapted image. Results may be undefined.\n"); 
            } else {
                printf("\n*** ERROR *** %s query (%s) failed. Not a valid image.\n", cmdTarget , cmdAccess);
                rc =  1; goto done; 
            }
        }

        if (!ops.QueryAll(*fbase, &info)) {
                printf("*** ERROR *** %s query (%s) failed: %s\n", cmdTarget , cmdAccess, ops.err());
                rc =  1; goto done;
        }

        ops.DisplayImageInfo(&info);
    }
    break;

    case CMD_QUERY_ROM:
    {
        Operations::ImageInfo info;
        if (!ops.LoadAsExpRom(*fbase)    || 
            !ops.GetExpRomVersion(&info) || 
            !ops.DisplayExpRomInfo(&info)) {
            printf("*** ERROR *** %s rom query (%s) failed: %s\n", cmdTarget , cmdAccess, ops.err());
            rc =  1; goto done;
        }
    }
    break;
    case CMD_READ_BLOCK:
    {
        // READ BLOCK
        //     Parameters:  <ADDR> <LENGTH> [OUT_FILENAME]
        //     if OUT_FILENAME is given, binari read block is stored
        //     in the given file. Otherwise, data is printed to screen.
        u_int32_t    addr, length;
        u_int8_t     *data;
        char         *endp;

        bool         to_file = false;

        // Address and length
        NEXTC("<ADDR>", "rb");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        NEXTC("<LENGTH>", "rb");
        length = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid length \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        data = new u_int8_t[length];

        // Output file
        FILE*  fh = NULL;

        if (i + 2 == ac)
            to_file = true;

        if (to_file) {
            NEXTC("<OUT_FILENAME>", "rb");
            if ((fh = fopen(av[i], "wb")) == NULL) {
                fprintf(stderr, "Can not open ");
                perror(av[i]);
                rc =  1; goto done; 
            }
        }

        // Read flash
        if (!fbase->read(addr, data, length)) {
            printf("*** ERROR *** Flash read failed: %s\n", fbase->err());
            rc =  1; goto done; 
        }

        if (to_file) {
            // Write output
            if (fwrite(data, 1, length, fh) != length) {
                perror("Write error");
                rc =  1; goto done; 
            }
            fclose(fh);
        } else {
            for (u_int32_t i = 0; i < length ; i+=4) {
                u_int32_t word = *((u_int32_t*)(data + i));

                word  = __be32_to_cpu(word);
                printf("0x%08x ", word);  
            }
            printf("\n");
        }
        delete [] data;
    }
    break;

    case CMD_READ_WORD:
    {
        // READ DWORD <ADDR>
        //     Parameters: <ADDR>
        u_int32_t    data, addr;
        char         *endp;

        // Address
        NEXTC("<ADDR>", "rw");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }

        // Read
        if (!f->read(addr, &data)) {
            printf("*** ERROR *** Flash read failed: %s\n", f->err());
            rc =  1; goto done; 
        }
        printf("0x%08x\n", (unsigned int)__cpu_to_be32(data));

    } 
    break;

    case CMD_VERIFY:
    {
        // VERIFY
        if (!ops.Verify(*fbase, NULL, true)) {
            printf("\n*** ERROR *** FW image verification failed");
            if (ops.err()) {
                printf(": %s", ops.err());
            }
            printf(". AN HCA DEVICE CAN NOT BOOT FROM THIS IMAGE.\n");
            rc =  1; goto done; 
        } else {
            printf("\nFW image verification succeeded. Image is bootable.\n\n");
        }
    }
    break;

    case CMD_DUMP_CONF:
    {
        // Dump conf
        _silent = true;

        char* conf_file = NULL;
        if (i + 2 <= ac) {
            NEXTC("<OUT_FILENAME>", "dc");
            conf_file = av[i];
        }

        ops.Verify(*fbase);

        if(!ops.DumpConf(conf_file)) {
            printf("*** ERROR *** Failed dumping FW configuration: %s\n", ops.err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_READ_IMAGE:
    {
        // Dump conf
        _silent = true;

        char* img_file = NULL;
        NEXTC("<OUT_FILENAME>", "ri");
        img_file = av[i];

        // For ConnectX, read only a single image. For other HCAs, try to read both images, since
        // the distributed image binary file also contains both images.
        ops.Verify(*f, NULL, !ops.IsCntx());
        
        //printf("Last addr: 0x%08x\n", ops._last_image_addr);

        u_int32_t length = ops._last_image_addr;
        u_int8_t* data = new u_int8_t[length];

        FILE* fh;

        if ((fh = fopen(av[i], "wb")) == NULL) {
            fprintf(stderr, "Can not open ");
            perror(av[i]);
            rc =  1; goto done; 
        }

        // Read flash
        if (!f->read(0, data, length)) {
            printf("*** ERROR *** Flash read failed: %s\n", f->err());
            rc =  1; goto done; 
        }

        // Write output
        if (fwrite(data, 1, length, fh) != length) {
            perror("Write error");
            rc =  1; goto done; 
        }
        fclose(fh);

        delete [] data;
    }
    break;

    case CMD_WRITE_BLOCK:
    {
        // WRITE BLOCK
        //     Parameters:  <IN_FILENAME> <ADDR>
        u_int32_t    addr;
        char         *endp;

        // Input file
        FImage fim;

        NEXTC("<IN_FILENAME>", "wb");

        image_fname = av[i];

        // Address
        NEXTC("<ADDR>", "wb");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }

        if (!fim.open(image_fname)) {
            printf("*** ERROR *** Image file open failed: %s\n", fim.err());
            rc =  1; goto done; 
        }

        // Write flash
        if (!ops.write_image(*f, addr, fim.getBuf(), fim.getBufLength(), !silent)) {
            printf("*** ERROR *** Flash write failed: %s\n", ops.err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_WRITE_WORD:
    {
        // WRITE DWORD
        //     Parameters: <ADDR> <DATA>
        u_int32_t    data, addr;
        char         *endp;

        // Address and data
        NEXTC("<ADDR>", "ww");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        NEXTC("<DATA>", "ww");
        data = __cpu_to_be32(strtoul(av[i], &endp, 0));
        if (*endp) {
            printf("Invalid data \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }

        //f->curr_sector = 0xffffffff;  // First time erase sector
        if (!f->write(addr, data)) {
            printf("*** ERROR *** Flash write failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_WRITE_BLOCK_NE:
    {
        // WRITE DWORD WITHOUT ERASE
        //     Parameters: <ADDR> <SIZE> <DATA>
        u_int32_t    size, addr;
        char         *endp;

        // Address and data
        NEXTC("<ADDR>", "wbne");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        NEXTC("<SIZE>", "wbne");
        size = strtoul(av[i], &endp, 0);
        if (*endp || size % 4) {
            printf("Invalid size \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        vector<u_int32_t> data_vec(size/4);
        for (u_int32_t w = 0; w < size/4 ; w++) {
            NEXTC("<DATA>", "wbne");
            data_vec[w] = __cpu_to_be32(strtoul(av[i], &endp, 0));
            if (*endp) {
                printf("Invalid data \"%s\"\n", av[i]);
                rc =  1; goto done; 
            }

            //printf("-D- writing: %08x : %08x\n", addr + w*4 , data_vec[w]);
        }

        if (!f->write(addr, &data_vec[0], size, true)) {
            printf("*** ERROR *** Flash write failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_WRITE_WORD_NE:
    {
        // WRITE DWORD WITHOUT ERASE
        //     Parameters: <ADDR> <DATA>
        u_int32_t    data, addr;
        char         *endp;

        // Address and data
        NEXTC("<ADDR>", "wwne");
        addr = strtoul(av[i], &endp, 0);
        if (*endp) {
            printf("Invalid address \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }
        NEXTC("<DATA>", "wwne");
        data = __cpu_to_be32(strtoul(av[i], &endp, 0));
        if (*endp) {
            printf("Invalid data \"%s\"\n", av[i]);
            rc =  1; goto done; 
        }

        if (!f->write(addr, &data, 4, true)) {
            printf("*** ERROR *** Flash write failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_CFI:
    {
        if (!f->print_attr() || !f->print_attr_old_format()) {
            printf("*** ERROR *** Cfi query failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_CLEAR_SEM:
        // Do nothing - opening the device already cleared the semaphore.
        break;

    default:
        printf("*** INTERNAL ERROR *** Invalid command %d.\n", cmd);
        rc =  1; goto done; 
    }

done:
 
    //mask signals   
    for (i = 0 ; i < (int)(sizeof(g_signals_for_termination)/sizeof(g_signals_for_termination[0])) ; i++ ) {
        signal (g_signals_for_termination[i], SIG_IGN);    
    }

    return rc;
}

