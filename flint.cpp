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
 *  Version: $Id: flint.cpp 3200 2006-12-21 13:13:38Z orenk $
 *
 */

//MTCR needs to be first since it needs to define all kind of
//macros which affect standard headers.

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

#ifndef NO_ZLIB
#include <zlib.h>
#endif

#include <signal.h>

#ifndef __WIN__ 

//
// Linux
//

#include <byteswap.h>
#include <endian.h>
#include <alloca.h>
#include <netinet/in.h>
#include <unistd.h>

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
char* _versionID = "VERSION_ID_HERE";
#endif

char* _svnID     = "$Revision: 3200 $";

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

#if __BYTE_ORDER == __LITTLE_ENDIAN
    #ifndef __cpu_to_le16
        #define  __cpu_to_le16(x) (x)
    #endif
    #ifndef __le16_to_cpu
        #define  __le16_to_cpu(x) (x)
    #endif
#elif __BYTE_ORDER == __BIG_ENDIAN
    #ifndef __cpu_to_le16
        #define  __cpu_to_le16(x) bswap_16(x)
    #endif
    #ifndef __le16_to_cpu
        #define  __le16_to_cpu(x) bswap_16(x)
    #endif
#else
    #ifndef __cpu_to_le16
        #define  __cpu_to_le16(x) bswap_16(__cpu_to_be16(x))
    #endif
    #ifndef __le16_to_cpu
        #define  __le16_to_cpu(x) __be16_to_cpu(bswap_16(x))
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
#define CHECKLS(f,o,p) do { if (!checkList(f,o,p)) return false; } while(0)
#define READ4(f,o,d,p) do { if (!f.read(o,d)) {  \
    return errmsg("%s - read error (%s)\n", p, f.err()); }} while (0)
#define READBUF(f,o,d,l,p) do { if (!f.read(o,d,l)) { \
    return errmsg("%s - read error (%s)\n", p, f.err()); }} while (0)

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
    SIGNATURE=0x5a445a44
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
    H_LAST      = 10 
};

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

int  const VSD_LEN  = 208;
int  const PSID_LEN = 16;
int  const PRODUCT_VER_LEN = 16;

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

static u_int32_t log2up (u_int32_t in) {
    u_int32_t i;
    for (i = 0; i < 32; i++) {
        if (in <= (u_int32_t)(1 << i))
            break;
    }

    return i;
}


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
    FBase()           {}
    virtual ~FBase()  {}

    virtual bool open(const char *, bool)                  {return false;}
    virtual void close()                                   = 0;
    virtual bool read(u_int32_t addr, u_int32_t *data)     = 0;
    virtual bool read(u_int32_t addr, void *data, int len,
                      bool verbose=false)                  = 0;

    virtual u_int32_t get_sector_size()                    = 0;
    virtual u_int32_t get_size()                           = 0;

    enum {
        MAX_FLASH = 4*1048576
    };
};

// Flash image (RO)
class FImage : public FBase {
public:
    FImage() : _buf(0) {}
    virtual ~FImage() { close();}

    u_int32_t    *getBuf()      { return _buf;}
    u_int32_t    getBufLength() { return _len;}
    virtual bool open(const char *fname, bool read_only = false);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t *data);
    virtual bool read(u_int32_t addr, void *data, int len, bool verbose=false);

    virtual u_int32_t get_sector_size();
    virtual u_int32_t get_size()     { return  getBufLength();}

private:
    u_int32_t *_buf;
    u_int32_t _len;
};

// Flash access (R/W)

//
// Flash classes heirarchy:
//
//
//    Flash { CmdSet (abstract) }
//      |
//      | 
//      +----> ParallelFlash { CmdSetAmd, CmdSetIntel }
//      |
//      |
//      |----> SerialFlash
//                  |
//		  +--------> SpiFlash { CmdSetStSpi }
//		  |
//		  +- - - - > LpcFlash (currently not uset - not implemented)
//
//
//    Flash Interface:
//      - open
//      - close
//      - read
//      - detect type (and allocate CmdSet accordingly)  
//
//
//    Flash Class HAS A command set.
//
//    CmdSet Interface:
//      - write 
//      - erase_sector
//
//    Q: Why is diferentiation needed for both flash type and CmdSet ?
//    A: Read operation is done in the same way for all flash devices of
//       the same type (serial or parallel). This is a basic requirement 
//       from the flash, since the HCA HW reads from flash at boot, and 
//       the way it reads can not be changed. 
//       However, Write and Erase operations protocol varies between flash 
//       vendors.
//       The term 'command set' is taken from the Common Flash Interface (CFI)
//       specification.
//
//
//    Flash Allocation flow:
//
//    1. Main checks device type, and allocates Flash sub class accordingly.
//    2. In Flash.open() , get_cmd_set() is called. this function checks flash
//       type, gets flash attributes (size, sector size) and allocates CmdSet.
//
//       



// 
//
//
class Flash : public FBase {
public:
    Flash(u_int32_t log2_bank_size) :  
    _mf(0), 
    _cmd_set(NULL), 
    _curr_bank(0xffffffff),
    _log2_bank_size(log2_bank_size) 
    {}

    virtual ~Flash()  { close();};

    // FBase Interface

    virtual bool open          (const char *device,
				bool force_lock = false,
                                bool read_only  = false);

    virtual void close         ();

    virtual bool read          (u_int32_t addr, 
                                u_int32_t *data)            = 0;

    virtual bool read          (u_int32_t addr, 
                                void*     data, 
                                int       len, 
                                bool      verbose = false);
    //
    // Flash Interface
    //

    virtual u_int32_t 
     get_sector_size        () { return _get_sector_size(); }
    
    virtual u_int32_t 
	get_size               ()                           {return _cfi_data.device_size ? _cfi_data.device_size : (u_int32_t)MAX_FLASH;}


    virtual bool wait_ready    (const char* msg = NULL)     = 0;


    // Write and Erase functions are performed by the Command Set

    virtual bool erase_sector  (u_int32_t addr)             {if (!set_bank(addr)) return false;return _cmd_set->erase_sector(addr);}

    virtual bool write         (u_int32_t addr, 
                                void*     data, 
                                int       cnt,
                                bool      noerase = false, 
                                bool      noverify = false);

    virtual bool write         (u_int32_t addr, 
                                u_int32_t data);

    bool         print_cfi_info();


    enum {
        TRANS = 4096
    };

#ifndef _MSC_VER
protected:
#endif

    // FLASH constants
    enum FlashConstant {
        FLASH_CMD_CNT  = 5000,    // Number of reads till flash cmd is zeroed
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


    enum CrAddres {
        GPIO_DIR_L     = 0xf008c, 
        GPIO_POL_L     = 0xf0094,
        GPIO_MOD_L     = 0xf009c,
        GPIO_DAT_L     = 0xf0084,
        GPIO_DATACLEAR_L = 0xf00d4, 
        GPIO_DATASET_L   = 0xf00dc,

        SEMAP63        = 0xf03fc
    };

    virtual bool lock           (bool retry=true);
    virtual bool unlock         ();

    virtual bool init_gpios    ()                           = 0;

    virtual bool get_cmd_set   ()                           = 0;

    bool set_bank      (u_int32_t addr);

    virtual bool write_internal(u_int32_t addr, 
                                u_int8_t  data)             = 0;

    bool         write_internal(u_int32_t addr, 
                                u_int8_t* data, 
                                u_int32_t cnt);

    class CmdSet {
    public:
        CmdSet                     () : _curr_sector(0xffffffff) {}
        virtual ~CmdSet            ()                 {}

        virtual bool write         (u_int32_t addr, 
                                    void*     data, 
                                    int       cnt,
                                    bool      noerase  = false, 
                                    bool      noverify = false)  = 0;

        virtual bool erase_sector  (u_int32_t addr)              = 0;

        virtual bool reset         ()                            = 0;

    protected:

        u_int32_t    _curr_sector;
    };


    //		
    // This structure holds all CFI query information as defined
    // in the JEDEC standard. All information up to 
    // primary_extended_query is standard among all amnufactures
    // with CFI enabled devices.
    //

    struct cfi_query {
	cfi_query() {
	    memset(this, 0, sizeof(*this));
	}

        enum {MAX_ERASE_BLOCKS = 8};

        u_int8_t  manuf_id;
        u_int8_t  device_id;

        char      query_string[4];      // Should be 'QRY' 
        u_int16_t oem_command_set;              // Command set 
        u_int16_t primary_table_address;        // Addy of entended table 
        u_int16_t alt_command_set;              // Alt table 
        u_int16_t alt_table_address;            // Alt table addy 
        float     vcc_min;                      // Vcc minimum 
        float     vcc_max;          // Vcc maximum 
        float     vpp_min;          // Vpp minimum, if supported 
        float     vpp_max;          // Vpp maximum, if supported 
        int       timeout_single_write;         // Time of single write 
        int       timeout_buffer_write;         // Time of buffer write 
        int       timeout_block_erase;          // Time of sector erase 
        int       timeout_chip_erase;       // Time of chip erase 
        int       max_timeout_single_write;     // Max time of single write 
        int       max_timeout_buffer_write;     // Max time of buffer write 
        int       max_timeout_block_erase;  // Max time of sector erase 
        int       max_timeout_chip_erase;   // Max time of chip erase 
        long      device_size;              // Device size in bytes 
        u_int16_t interface_description;    // Interface description 
        int       max_multi_byte_write;         // Time of multi-byte write 
        int       num_erase_blocks;     // Number of sector defs. 
        struct {
            unsigned long sector_size;          // Byte size of sector 
            int           num_sectors;          // Num sectors of this size 
            u_int32_t     sector_mask;          // Sector mask 
        } erase_block[MAX_ERASE_BLOCKS];        // Max of 256, but 8 is good 

        // AMD SPECIFIC
        char primary_extended_query[4];         // Vendor specific info here 
        u_int16_t major_version;        // Major code version 
        u_int16_t minor_version;        // Minor code version 
        u_int8_t  sensitive_unlock;     // Is byte sensitive unlock? 
        u_int8_t  erase_suspend;        // Capable of erase suspend? 
        u_int8_t  sector_protect;       // Can Sector protect? 
        u_int8_t  sector_temp_unprotect;    // Can we temporarily unprotect? 
        u_int8_t  protect_scheme;       // Scheme of unprotection 
        u_int8_t  is_simultaneous;      // Is a smulataneous part? 
        u_int8_t  is_burst;         // Is a burst mode part? 
        u_int8_t  is_page;          // Is a page mode part? 
    };

    bool print_cfi_info ( const cfi_query *q );


    virtual bool set_bank_int  (u_int32_t bank)              = 0;
    u_int32_t    bank_mask     ()                 {return((1 << _log2_bank_size) -1 );}

    mfile        *_mf;

    cfi_query    _cfi_data;
    CmdSet*      _cmd_set;

    u_int32_t    _curr_bank;
    u_int32_t    _log2_bank_size;
    
    bool         _locked;


    /* Work around for MX flashes reporting weird erase sector size. */
    /* It reports two sector sizes, actually works as 1. */
    bool _mx_flash_workaround() {
	    return (_cfi_data.num_erase_blocks == 2 &&
		//_cfi_data.manuf_id == 0xff && _cfi_data.device_id == 0xff &&
		_cfi_data.erase_block[0].sector_size == 0x2000 &&
		_cfi_data.erase_block[0].sector_mask == 0xffffe000 &&
		_cfi_data.erase_block[0].num_sectors == 8 &&
		_cfi_data.erase_block[1].sector_size == 0x10000 &&
		_cfi_data.erase_block[1].sector_mask == 0xffff0000 &&
		_cfi_data.erase_block[1].num_sectors == 63);
    }
    u_int32_t
    _get_sector_mask        ()
    {
	    return _mx_flash_workaround()?
		    _cfi_data.erase_block[1].sector_mask :
		    _cfi_data.erase_block[0].sector_mask;
    }
    u_int32_t
    _get_sector_size        ()
    {
	    return _mx_flash_workaround()?
		    _cfi_data.erase_block[1].sector_size :
		    _cfi_data.erase_block[0].sector_size;
    }
};


class ParallelFlash : public Flash {
public:
    ParallelFlash();
    ~ParallelFlash() {close();}

    enum {
        CS_INTEL = 0x01,
        CS_AMD   = 0x02,
    };

    // FBase Interface

//    virtual bool open          (const char *device,
//			        bool read_only = false);

    virtual void close         ();


    virtual bool read          (u_int32_t addr, 
                                u_int32_t *data);

    virtual bool read          (u_int32_t addr, 
                                void*     data, 
                                int       len, 
                                bool      verbose=false) {return Flash::read(addr, data, len, verbose);}

    virtual bool wait_ready    (const char* msg = NULL);

    static  void set_byte_mode (bool mode) {CmdSetAmd::set_byte_mode(mode);}


#ifndef _MSC_VER
protected:
#endif

    virtual bool init_gpios    ();

    virtual bool get_cmd_set   ();

    virtual bool set_bank_int  (u_int32_t bank);

    virtual bool write_internal(u_int32_t addr, 
                                u_int8_t  data);

    enum FlashCmds {
        IDLE           = 0, 
        READ4          = (1<<29), 
        WRITE1         = (2<<29) 
    };

    enum {
        BANK_SHIFT     = 19,     
        BANK_MASK      = 0xfff80000 
    };                 

    enum {
        FLASH          =    0xf01a4, 
        ADDR_MSK       =    0x7ffffUL, 
        CMD_MASK       = 0xe0000000UL 
    };

    enum {
        LEN_MSK        = 0x3ff, 
        LEN_SHIFT      = 19
    };

    enum {
        CPUMODE_MSK    = 0xc0000000UL, 
        CPUMODE_SHIFT  = 30 
    };

    enum CrAddres {
        CPUMODE        = 0xf0150
    };


    //
    // AMD's Am29LV033C command set
    //
    class CmdSetAmd : public Flash::CmdSet {
    public:
        CmdSetAmd                  (ParallelFlash& f  ) : _f(f) {}

        virtual bool write         (u_int32_t addr, 
                                    void*     data, 
                                    int       cnt,
                                    bool      noerase  = false, 
                                    bool      noverify = false);

        virtual bool erase_sector  (u_int32_t addr);
        virtual bool reset         ();

        static  void set_byte_mode (bool mode) {_byte_mode = mode;}

    protected:
        ParallelFlash& _f;

        static bool  _byte_mode;       

        bool         unlock_bypass (bool      unlock);
    };


    //
    // Intel's 28F320J3 x8 command set, using buffer writes
    //
    class CmdSetIntel : public Flash::CmdSet {
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

        CmdSetIntel                (ParallelFlash& f  ) : _f(f) {}

        virtual bool write         (u_int32_t addr, 
                                    void*     data, 
                                    int       cnt,
                                    bool      noerase  = false, 
                                    bool      noverify = false);

        virtual bool erase_sector  (u_int32_t addr);
        virtual bool reset         ();

    protected:
        ParallelFlash& _f;
    };

    //
    // Intel's 28F320J3 x8 command set, using byte write (For debug only).
    //
    class CmdSetIntelWriteByte : public CmdSetIntel {
    public:
        CmdSetIntelWriteByte       (ParallelFlash& f) : CmdSetIntel(f) {}

        virtual bool write         (u_int32_t addr, 
                                    void*     data, 
                                    int       cnt,
                                    bool      noerase  = false, 
                                    bool      noverify = false);

    };

    bool get_cfi                (cfi_query *query);

    u_int16_t extract_word   ( const u_int8_t* pb, int data_width)  {
        assert (data_width == 1 || data_width == 2);
        u_int16_t ret = *pb | ((*(pb + data_width)) << 8);
        return ret;
    }

    u_int32_t     USE_SCR;
    bool         _use_scr;

    // Place holders to keep GPIO data for restoring after closing flash.
    u_int32_t    _dir;
    u_int32_t    _pol;
    u_int32_t    _mod;
    u_int32_t    _data;

};


class SerialFlash : public Flash {
public:
    SerialFlash() : Flash(20) {}

    enum CrAddres {
        FLASH_GW     = 0xf0400,
        FLASH_ADDR   = 0xf0404,
        FLASH_DATA   = 0xf0408,
        FLASH_CS     = 0xf0418,

        GPIO_LOCK    = 0xf00ec
    };

    enum BitOffset {
        READ_OP      = 0,
        ADDR_INCR    = 1,

        LPC_STOP     = 3,
        SPI_NO_DATA  = 4,
        SPI_NO_ADDR  = 5,
        SPI_SPECIAL  = 6,

        MSIZE_S      = 8,
        MSIZE_E      = 10,

        STATUS_S     = 26,
        STATUS_E     = 29,

        BUSY         = 30,

        SPI_ADDR_S   = 0,
        SPI_ADDR_E   = 23,

        SPI_CMD_S    = 24,
        SPI_CMD_E    = 31,

        SPI_GPIO_S   = 5,
        SPI_GPIO_E   = 7
    };


protected:

    virtual bool write_internal(u_int32_t addr, 
                                u_int8_t  data);

};

bool SerialFlash::write_internal (u_int32_t addr, 
                                  u_int8_t  data)  {addr = 0; data = 0; return true;}


class SpiFlash : public SerialFlash {
public:
    SpiFlash() {}
    ~SpiFlash() {close();}


    // FBase Interface

    virtual void close         ();

    virtual bool read          (u_int32_t addr, 
                                u_int32_t *data);

    virtual bool read          (u_int32_t addr, 
                                void*     data, 
                                int       len, 
                                bool      verbose=false) {return Flash::read(addr, data, len, verbose);}

    virtual bool wait_ready    (const char* msg);

protected:

    virtual bool init_gpios    ();

    virtual bool get_cmd_set   ();

    virtual bool set_bank_int  (u_int32_t bank);

    
    virtual bool read_id       (u_int8_t *data, u_int8_t cmd);


    //
    // ST's M25P80 command set
    //
    class CmdSetStSpi : public Flash::CmdSet {
    public:
        CmdSetStSpi                (SpiFlash& f  ) : _f(f) , _mf(f._mf){}

        virtual bool write         (u_int32_t addr, 
                                    void*     data, 
                                    int       cnt,
                                    bool      noerase  = false, 
                                    bool      noverify = false);

        virtual bool erase_sector  (u_int32_t addr);

        virtual bool reset         ()                {return true;}

        enum FlashCommand {
            FC_SE    = 0xD8,
            FC_PP    = 0x02,
            FC_RDSR  = 0x05,
            FC_WREN  = 0x06,
            FC_READ  = 0x03,
            FC_RDID  = 0xF9,
            FC_RES   = 0xAB
        }; 


    protected:
        bool         write_block   (u_int32_t block_addr, 
                                    void*     block_data, 
                                    u_int32_t block_size);

        bool         wait_wip      (u_int32_t delay, 
                                    u_int32_t retrys, 
                                    u_int32_t fast_retry = 0);

        bool         write_enable  ();


        SpiFlash& _f;
        mfile*    _mf;

    };

    bool fill_cfi                  (cfi_query *query);

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

    if (addr + len > _len) {
        return errmsg("Reading 0x%x bytes from address 0x%x is out of image limits (0x%x bytes)", 
		      len, addr, _len);
    }

    u_int32_t *p = (u_int32_t *)data;
    for (int i=0; i<len/4; i++) {
	p[i] = _buf[addr/4];
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


////////////////////////////////////////////////////////////////////////
bool Flash::open(const char *device, bool force_lock, bool read_only)
{

    // Open device
    _mf = mopen(device);
    if (!_mf) {
        return errmsg("Can not open device %s: %s", device, strerror(errno));
    }

    _locked = lock();

    if (!_locked) {
	if (force_lock) {
	    report("Warning: Taking flash lock even though semaphore is set.\n");
	    _locked = true;
	} else { 
	    return false;
	}
    }

    if (!init_gpios())
        return false;

    if (!read_only) {
        if (!get_cmd_set())
            return false;

        // Reset flash
        return _cmd_set->reset(); 
    }

    return true;
} // Flash::open

////////////////////////////////////////////////////////////////////////
void Flash::close()
{
    if (!_mf)
        return;

    delete _cmd_set;

    // ??? Check if unlock should be before delete _cmd_set
    if (_locked) {
	unlock();
    }

    mclose(_mf); 
    _mf = 0;

} // Flash::close


bool Flash::lock(bool retry) {

    retry = false; // compiler - REMOVE ???

    // Obtain GPIO Semaphore
    u_int32_t cnt=0;
    u_int32_t word;
    do {
        if (++cnt > GPIO_SEM_TRIES) {
            return errmsg("Can not obtain Flash semaphore (63). You can run \"flint -clear_semaphore -d <device>\" to force semaphore unlock. See help for details.");
        }
        MREAD4(SEMAP63, &word);
    } while (word);

    return true;
}


bool Flash::unlock() {

    // Free GPIO Semaphore
    mwrite4(_mf, SEMAP63, 0);
    return true;
}


////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, void *data, int len, bool verbose)
{
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

    // Report
    if (verbose) {
        printf("\b\b\b\b100%%");
        fflush(stdout);
    }

    return true;
} // Flash::read


////////////////////////////////////////////////////////////////////////
bool Flash::write         (u_int32_t addr, 
		    void*     data, 
		    int       cnt,
		    bool      noerase,
		    bool      noverify)
{
    if (addr + cnt > get_size()) {
	return errmsg( 
	    "Trying to write %d bytes to address 0x%x, which exceeds flash size (0x%x).",
	    cnt, 
	    addr,
	    get_size());  
    }
    
    return _cmd_set->write(addr, data, cnt, noerase, noverify);
}


////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr, u_int32_t data)
{
    if (!_mf) {
	return errmsg("Not opened");
    }
    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }

    // Here, we use non-virtual variants for efficiency
    // TODO: Rewrite using get_sector_size() only
    u_int32_t word;
    u_int32_t sector_mask = _get_sector_mask();
    u_int32_t sector_size = _get_sector_size();

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

////////////////////////////////////////////////////////////////////////

inline
bool Flash::set_bank      (u_int32_t addr) {
    u_int32_t bank = (addr >> _log2_bank_size);

    if (bank != _curr_bank ) {
        if (!set_bank_int(bank))
            return false;

        _curr_bank = bank;
    }

    return true;
}


// A smaple function which loops through and prints out the data
// contained in the CFI query structure.  Should ONLY be called
// after init_flash 

bool Flash::print_cfi_info()
{

    const cfi_query *q = &_cfi_data;

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
    if (q->vpp_min == 0.0)
        printf("Device does not support Vpp voltage.\n");
    else {
        printf("[%2.3f] to [%2.3f] Volts\n", q->vpp_min, q->vpp_max);
    }

    printf(head_fmt, "Typical timeout for single write (micro-sec):");
    printf("[%8i]us\n", q->timeout_single_write);



    printf(head_fmt,"Typical timeout for single write (micro-sec):");
    if (q->timeout_buffer_write == 0x00)
        printf("Buffer writes not supported in this device.\n");
    else {
        printf("[%8i]us\n" ,q->timeout_buffer_write);
    }

    printf(head_fmt, "Typical timeout for block erase (milli-sec):", q->timeout_block_erase);
    printf("[%8i]ms\n", q->timeout_block_erase);

    printf(head_fmt, "Typical timeout for chip erase (milli-sec):");
    if (q->timeout_chip_erase == 0x00)
        printf("Not supported in this device.\n");
    else {
        printf("[%8i]ms\n", q->timeout_single_write);
    }

    printf(head_fmt, "Maximum timeout for single write (micro-sec) :");
    printf("[%8i]us\n", q->max_timeout_single_write);

    printf(head_fmt, "Maximum timeout for buffer write (micro-sec) :");
    if (q->max_timeout_buffer_write == 0x00)
        printf("Not supported in this device.\n");
    else {
        printf("[%8i]us\n", q->max_timeout_buffer_write);
    }

    printf(head_fmt, "Maximum timeout for block erase (milli-sec) :");
    printf("[%8i]ms\n", q->max_timeout_block_erase);

    printf(head_fmt, "Maximum timeout for chip erase (milli-sec) :");
    if (q->max_timeout_chip_erase == 0x00)
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

    for (i=0; i<q->num_erase_blocks; i++) {
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
} // Flash::print_cfi_info()



////////////////////////////////////////////////////////////////////////
//
// ParallelFlash Class Implementation
//
////////////////////////////////////////////////////////////////////////

ParallelFlash::ParallelFlash() : Flash(19)
{
    char *use_scr_p = getenv("FLINT_USE_SCRATCHPAD");

    if (use_scr_p) {
        char *endp;

        USE_SCR = strtoul(use_scr_p, &endp, 0);
        if (*endp) {
            printf("Invalid FLINT_USE_SCRATCHPAD syntax (%s). Must be integer.",
                   use_scr_p);
            _use_scr = false;
        } else {
            printf("Burning via SCRATCHPAD interface by addr 0x%x\n", USE_SCR);
            _use_scr = true;
        }
    } else
        _use_scr = false;
} // Flash::Flash



////////////////////////////////////////////////////////////////////////
bool ParallelFlash::init_gpios() {

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
    u_int32_t word;
    MREAD4(CPUMODE, &word);
    word &= ~CPUMODE_MSK;
    word |= 1 << CPUMODE_SHIFT;
    MWRITE4(CPUMODE, word);

    return true;
}

void ParallelFlash::close() {

    // Restore origin values
    mwrite4(_mf, GPIO_DIR_L, _dir);
    mwrite4(_mf, GPIO_POL_L, _pol);
    mwrite4(_mf, GPIO_MOD_L, _mod);
    mwrite4(_mf, GPIO_DAT_L, _data);

    _curr_bank = 0xffffffff;

    Flash::close();
}


bool ParallelFlash::get_cmd_set() {

    //
    // CFI Query
    //
    if (!get_cfi(&_cfi_data))
        return false;

    //
    // Some sanity checks:
    //

    if (_cfi_data.max_multi_byte_write > MAX_WRITE_BUFFER_SIZE) {
        return errmsg("Device write buffer(%d) is larger than the supported size(%d).", 
		      _cfi_data.max_multi_byte_write, MAX_WRITE_BUFFER_SIZE);
    }

    if (!_mx_flash_workaround() && _cfi_data.num_erase_blocks > 1) {
	return errmsg("Device has more than one sector size - not supported by this tool");
    }

    //
    // Sellect CmdSet
    //

    switch (_cfi_data.oem_command_set) {
    case CS_INTEL:
        if (_byte_write || _cfi_data.max_multi_byte_write == 0)
            _cmd_set = new CmdSetIntelWriteByte(*this);
        else
            _cmd_set = new CmdSetIntel(*this);
        break;
    case CS_AMD: 
        _cmd_set =     new CmdSetAmd(*this);
        break;

    default:
        return errmsg("Unknown CFI command set (%d)",_cfi_data.oem_command_set) ;
    }

    return true;
}



////////////////////////////////////////////////////////////////////////
bool ParallelFlash::set_bank_int(u_int32_t bank)
{
    if (!_mf) {
        return errmsg("Not opened");
    }

    //printf("\n*** Flash::set_bank(0x%lx) : 0x%lx\n", bank, (bank >> 19) & 0x07);
    MWRITE4(GPIO_DATACLEAR_L, 0x70);
    MWRITE4(GPIO_DATASET_L, (bank << 4) & 0x70);

    return true;
} // Flash::ParallelFlashGw::set_bank_int


////////////////////////////////////////////////////////////////////////
bool ParallelFlash::wait_ready(const char* msg) {
    u_int32_t cnt = 0;
    u_int32_t cmd;
    do {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT) {
            return errmsg("Flash gateway timeout: %s", msg);
        }

        MREAD4(FLASH, &cmd);

    } while (cmd & CMD_MASK);

    return true;
}

////////////////////////////////////////////////////////////////////////
bool ParallelFlash::read(u_int32_t addr, u_int32_t *data)
{
    if (!_mf) {
        return errmsg("Not opened");
    }

    u_int32_t cmd;
    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }

    if (!set_bank(addr))
        return false;


    MWRITE4(FLASH, READ4 | (addr & ADDR_MSK));

    if (!wait_ready("Read"))
        return false;

    MREAD4(FLASH+4, &cmd);
    cmd = __cpu_to_be32(cmd);
    memcpy(data, &cmd, sizeof(u_int32_t));

    return true;
} // Flash::read

////////////////////////////////////////////////////////////////////////
bool ParallelFlash::write_internal(u_int32_t addr, u_int8_t data)
{
    MWRITE4(FLASH+4, data << 24);
    MWRITE4(FLASH, WRITE1 | (addr & ADDR_MSK));

    if (!wait_ready("Write"))
        return false;

    return true;
} // Flash::write_internal


////////////////////////////////////////////////////////////////////////
bool ParallelFlash::CmdSetAmd::unlock_bypass(bool unlock) {

    if (unlock) {
        // unlock bypass

        if (!_f.write_internal(0x555, 0xaa))
            return false;
        if (!_f.write_internal(0x2aa, 0x55))
            return false;
        if (!_f.write_internal(0x555, 0x20))
            return false;
    } else {
        // unlock reset
        if (!_f.write_internal(0x555, 0x90))
            return false;
        if (!_f.write_internal(0x2aa, 0x00))
            return false;
    }
    return true;
}


////////////////////////////////////////////////////////////////////////

bool ParallelFlash::CmdSetAmd::_byte_mode = false;

bool ParallelFlash::CmdSetAmd::write(u_int32_t addr, void *data, int cnt,
                                     bool noerase, bool noverify)
{
    if (!_f._mf) {
        return _f.errmsg("Not opened");
    }
    if (addr & 0x3) {
        return _f.errmsg("Address should be 4-bytes aligned.");
    }

    char         *p = (char *)data;

    if (_unlock_bypass) {
	if (!unlock_bypass(true)) {
	    return _f.errmsg("Failed unlock bypass"); 
	}
    }

    for (int i=0; i<cnt; i++,addr++) {
        u_int32_t  word;
        u_int8_t   act, exp;
        int        cnt1 = 0;

        if (!_f.set_bank(addr))
            return false;

        if (!noerase) {
            u_int32_t sector = (addr / _f.get_sector_size()) * _f.get_sector_size();
            if (sector != _curr_sector) {
                _curr_sector = sector;

		// If we're in unlock mode, we must re-lock before erase sector
		if (_unlock_bypass) {
		    if (!unlock_bypass(false)) {
			return _f.errmsg("Failed re-lock bypass");
		    }
		}


                if (!erase_sector(_curr_sector))
                    return false;


		if (_unlock_bypass) {
		    if (!unlock_bypass(true)) {
			return _f.errmsg("Failed unlock bypass");
		    }
		}
            }
        }

        if (_no_burn)
            continue;

        if (_f._use_scr) {

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
            do {
                int  loop_cnt = 0;
                // Timeout checks
                if (++loop_cnt > FLASH_CMD_CNT) {
                    return _f.errmsg("Use scratchpad: CMD does not become zero");
                }
                if (mread4(_f._mf, _f.USE_SCR , &cmd) != 4) return false;

            } while (cmd & CMD_MASK);
            i += 3;
            addr += 3;
        } else if ((u_int8_t)(*p) != 0xff) {

            if (_byte_mode) {
            
                if (!_f.write_internal(0xaaa, 0xaa))
                    return false;
                if (!_f.write_internal(0x555, 0x55))
                    return false;
                if (!_f.write_internal(0xaaa, 0xa0))
                    return false;
            } else {
                if (!_unlock_bypass) {
                    if (!_f.write_internal(0x555, 0xaa))
                        return false;
                    if (!_f.write_internal(0x2aa, 0x55))
                        return false;
                }

                if (!_f.write_internal(0x555, 0xa0))
                    return false;
            }

            if (!_f.write_internal(addr, *p++))
                return false;

            do {
                // Timeout checks
                if (++cnt1 > READ_CNT_FAST)
                    usleep(READ_DELAY);
                if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW) {
                    return _f.errmsg("Flash write error - read value did not stabilize.");
                    return false;
                }

                if (!_f.read(addr & ~3, &word))
                    return false;

                word = __be32_to_cpu(word);
                act = (u_int8_t) ((word >> ((3 - (addr & 3)) * 8)) & 0xff);
                exp = *(p-1) & 0xff;
                //if (act != exp)
                //    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
                //           addr, exp & 0xff, act & 0xff, word);
            } while (!noverify && act != exp);      

        } else {
            p++;
        }
    } 

    if (_unlock_bypass) {
	 if (!unlock_bypass(false)) {
	     return _f.errmsg("Failed re-lock bypass");
	 }
    }

    return true;
} // flash_write



bool ParallelFlash::CmdSetIntelWriteByte::write(u_int32_t addr, void *data, int cnt,
                                                bool noerase, bool noverify)
{
    if (!_f._mf) {
        return _f.errmsg("Not opened");
    }
    if (addr & 0x3) {
        return _f.errmsg("Address should be 4-bytes aligned.");
    }

    char         *p = (char *)data;

    for (int i=0; i<cnt; i++,addr++) {
        u_int32_t  status;
        u_int8_t   act, exp;
        int        cnt1 = 0;

        if (!_f.set_bank(addr))
            return false;

        if (!noerase) {
            u_int32_t sector = (addr / _f.get_sector_size()) * _f.get_sector_size();
            if (sector != _curr_sector) {
                _curr_sector = sector;
                if (!erase_sector(_curr_sector))
                    return false;
            }
        }

        if (_no_burn)
            continue;

        if ((u_int8_t)(*p) != 0xff) {
            // Write byte
            if (!_f.write_internal(addr, FC_Write))
                return false;

            if (!_f.write_internal(addr, *p++))
                return false;

            do {
                // Timeout checks
                if (++cnt1 > READ_CNT_FAST)
                    usleep(READ_DELAY);
                if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW) {
                    return _f.errmsg("Flash write error - timeout waiting for ready after write.");
                }

                // TODO - Move to read single for Arbel
                if (!_f.read(addr & ~3, &status))
                    return false;

                //if (act != exp)
                //    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
                //           addr, exp & 0xff, act & 0xff, word);
            } while ((status & FS_Ready) == 0);

            if (status & FS_Error) {
                return _f.errmsg("Flash write error - error staus detected.");
            }

            if (!noverify) {
                u_int32_t word;
                if (!reset())
                    return false;
                // TODO - Move to read single for Arbel
                if (!_f.read(addr & ~3, &word))
                    return false;

                word = __be32_to_cpu(word);
                act = (u_int8_t) ((word >> ((3 - (addr & 3)) * 8)) & 0xff);
                exp = *(p-1) & 0xff;

                if (act != exp) {
                    printf("write: %08x - exp:%02x act:%02x /%08x/\n",
                           addr, exp & 0xff, act & 0xff, word);

                    return _f.errmsg("Write verification failed");
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
bool ParallelFlash::CmdSetIntel::write(u_int32_t addr, void *data, int cnt,
                                       bool noerase, bool noverify)
{
    if (!_f._mf) {
        return _f.errmsg("Not opened");
    }
    if (addr & 0x3) {
        return _f.errmsg("Address should be 4-bytes aligned.");
    }

    u_int8_t         *p = (u_int8_t *)data;

    u_int32_t block_size = _f._cfi_data.max_multi_byte_write;
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
        if (!_f.set_bank(addr))
            return false;

        if (!noerase) {
            u_int32_t sector = (addr / _f.get_sector_size()) * _f.get_sector_size();
            if (sector != _curr_sector) {
                _curr_sector = sector;
                if (!erase_sector(_curr_sector))
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

        if (!all_ffs) {

            u_int32_t status;
            cnt1 = 0;
            do {
                // Get Write buffer
                if (!_f.write_internal(block_addr, FC_SCSWrite))
                    return false;

                if (cnt1 > ((READ_CNT_FAST + READ_CNT_SLOW) * 4)) {
                    //printf("-D- status = %08x\n", status);
                    reset();
                    return _f.errmsg("Flash write error - Write buffer not ready.");  
                }

                cnt1++;

                if (!_f.read(block_addr, &status))
                    return false;

            } while (!(status & FS_Ready));

            if (status & FS_Error) {
                return _f.errmsg("Flash write error - Error getting write buffer");
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
            do {
                // Timeout checks
                if (++cnt1 > READ_CNT_FAST)
                    usleep(READ_DELAY);
                if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW) {
                    reset();
                    return _f.errmsg("Flash write error - Write buffer status timeout");
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
			return _f.errmsg(
			    "Write verification failed. Addr: %08x - exp:%02x act:%02x",
			    addr + i, 
			    write_data[i + prefix_pad_size] , 
			    verify_buffer[i]);   
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
bool ParallelFlash::CmdSetAmd::reset() {
    if (!_f.write_internal(0x555, 0xf0)) {
	return _f.errmsg("Device reset failed: %s", _f.err());
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
bool ParallelFlash::CmdSetAmd::erase_sector(u_int32_t addr)
{
    u_int32_t word = 0;
    int       cnt  = 0;

    if (_no_erase)
        return true;

    // Just to insure zeroes because erase completion waits for ones
    if (!write(addr, &word, sizeof(word), true))
        return false;

    // erase sector sequence
    if (_byte_mode ) {
    
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
    } else {
    
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

    }

    // Wait while erase completes
    do {
        // Timeout checks
        if (++cnt > ERASE_CNT) {
            return _f.errmsg("Flash erase sector timeout");
        }
        if (!_f.read(addr, &word))
            return false;

        //printf("erase_sector: addr:%08lx, %08x\n", addr, word);
        usleep(ERASE_DELAY);
    } while (word != 0xffffffff);


    return true;
} // Flash::erase_sector

////////////////////////////////////////////////////////////////////////

bool ParallelFlash::CmdSetIntel::reset() {
    if (!_f.write_internal(0x555, FC_Read)) {
        return _f.errmsg("Device reset failed");
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
bool ParallelFlash::CmdSetIntel::erase_sector(u_int32_t addr)
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
    do {
        // Timeout checks
        if (++cnt > ERASE_CNT) {
            return _f.errmsg("Flash erase sector timeout");
        }
        if (!_f.read(addr, &status))
            return false;

        //printf("CmdSetIntel::erase_sector: addr:%08lx, %08x\n", addr, word);
        usleep(ERASE_DELAY);
    } while ((status & FS_Ready) == 0);

    if (status & FS_Error) {
        return _f.errmsg("Status register detected erase error (0x%x)", status & FS_Error);
    }

    // Reset
    if (!reset())
        return false;

    return true;
} // ParallelFlash::CmdSetIntel::erase_sector

//*******************************************************************
// flash_get_cfi() is the main CFI workhorse function.  Due to it's  
// complexity and size it need only be called once upon              
// initializing the flash system.  Once it is called, all operations 
// are performed by looking at the cfi_query structure.                
// All possible care was made to make this algorithm as efficient as 
// possible.  90% of all operations are memory reads, and all        
// calculations are done using bit-shifts when possible              
//*******************************************************************

bool ParallelFlash::get_cfi(struct cfi_query *query)
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

    for (i=0; i < cfi_query::MAX_ERASE_BLOCKS; i++) {
        query->erase_block[i].sector_size = 0;
        query->erase_block[i].num_sectors = 0;
        query->erase_block[i].sector_mask = 0;
    }

    // reset
    if (!write_internal(0x55, 0xff))
        return false;

    // CFI QUERY 
    if (!write_internal(0x55, 0x98))
        return false;

    char query_str_x8[4];
    char query_str_x16asx8[8];

    if (!read(0x10, query_str_x8, 0x4))
        return false;

    if (!read(0x20, query_str_x16asx8, 0x8))
        return false;

    query_str_x8[3]       = '\0';
    query_str_x16asx8[7]  = '\0';

    if ( strncmp( query_str_x8 ,      "QRY" ,3 ) == 0) {
        // x8 CFI flash (AMD)
        query_base = 1;
    } else if ( query_str_x16asx8[0] == 'Q' && 
                query_str_x16asx8[2] == 'R' &&
                query_str_x16asx8[4] == 'Y') {
        // x16 CFI flash worqing in x8 mode
        query_base = 2;
    } else {

        printf(" Received CFI query from addr 0x10: [%s]\n", query_str_x8 );
        printf(" Received CFI query from addr 0x20: [%s]\n", query_str_x16asx8);

        return errmsg("Failed CFI query");
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

    if (query->num_erase_blocks > cfi_query::MAX_ERASE_BLOCKS) {
        return errmsg("CFI query reported %d erase blocks in the flash %s. Only up to %d erase blocks are allowed.",
                      query->num_erase_blocks,
                      query->num_erase_blocks == 255 ? "(probably a corruptes flash)" : "",
                      cfi_query::MAX_ERASE_BLOCKS);
    }

    if (!read(query_base * 0x2C, fwp + query_base * 0x2C ,query_base * 4 * (query->num_erase_blocks + 1)))
        return false;

    for (i=0; i < query->num_erase_blocks; i++) {
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
        return errmsg("Primary extended query larger than TOTAL_QUERY_SIZE (%d)",TOTAL_QUERY_SIZE) ;
    }


    // DEBUG: 
    //printf("Raw Cfi query:\n");
    //printf("  0123456789abcdef_123456789abcdef_123456789abcdef\n  ");
    //for (u_int32_t i = 0x10 * query_base ; i <= (0x30 * query_base); i+= query_base) {
    //    printf("%02x",  fwp[i]);
    //}
    //printf("\n");

    u_int32_t dw_aligned_offs = (((offset * query_base) >> 2 ) << 2);

    if (!read(dw_aligned_offs , fwp + dw_aligned_offs  , EXTENDED_QUERY_SIZE * query_base))
        return false;

    query->primary_extended_query[0] = fwp[query_base * (offset)];
    query->primary_extended_query[1] = fwp[query_base * (offset + 1)];
    query->primary_extended_query[2] = fwp[query_base * (offset + 2)];
    query->primary_extended_query[3] = '\0';

    if ( query->primary_extended_query[0] != 'P' &&
         query->primary_extended_query[1] != 'R' &&
         query->primary_extended_query[2] != 'I') {
        return errmsg("Bad primary table address in CFI query");
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



////////////////////////////////////////////////////////////////////////
//
// SpiFlash Class Implementation
//
////////////////////////////////////////////////////////////////////////

bool SpiFlash::init_gpios() {

    //
    // Set Multi SPI CS to output and 0.
    // Assuming 4 flashes. If there are less than 4 flashes and there's
    // a write attempt, it will fail.
    //

    u_int32_t       num_of_spis = 4;
    u_int32_t       spi_en      = (1 << (num_of_spis - 1 ) ) -1;

    u_int32_ba      dir;
    u_int32_ba      mod; 
    u_int32_ba      pol;

    // No need to set the data - SPI GW CS does that in HW
    //MREAD4(GPIO_DAT_L, &data);

    MREAD4(GPIO_DIR_L, &dir);
    MREAD4(GPIO_POL_L, &pol);
    MREAD4(GPIO_MOD_L, &mod);

    dir.range (SPI_GPIO_E, SPI_GPIO_S) = spi_en;
    pol.range (SPI_GPIO_E, SPI_GPIO_S) = ~spi_en;
    mod.range(SPI_GPIO_E, SPI_GPIO_S) = ~spi_en;

    // unlock gpio
    MWRITE4(GPIO_LOCK , 0xaaaa);

    MWRITE4(GPIO_DIR_L, dir); 
    MWRITE4(GPIO_POL_L, pol); 
    MWRITE4(GPIO_MOD_L, mod); 

    return true;
}

void SpiFlash::close() {
    // Chip reset does not reset the chip sellect - Make sure after reset
    // boot loads FW from SPI 0.
    set_bank(0);

    // unlock gpio
    mwrite4(_mf, GPIO_LOCK , 0xaaaa);
}

bool SpiFlash::get_cmd_set   () {

    //
    // Read device ID and allocate command set accordingly.
    //

    //
    // Initiate some CFI fields to mimic cfi query procedure of parallel flash:
    //

    _cfi_data.max_multi_byte_write       = 16;   // In SPI context, this is the transaction size. Max is 16.
    _cfi_data.num_erase_blocks           = 1;
    _cfi_data.erase_block[0].sector_size = 64 * 1024;
    _cfi_data.erase_block[0].sector_mask = ~(_cfi_data.erase_block[0].sector_size - 1);

    u_int32_t spi_size = 0;
    u_int32_t num_spis = 0;

    for (u_int32_t spi_sel = 0 ; spi_sel < 4 ; spi_sel++) {
        if (!set_bank_int(spi_sel)) return false;

        unsigned char es; // electronic signature
        u_int32_t cur_spi_size = 0;

        if (!read_id(&es, CmdSetStSpi::FC_RES)) return false;

        if (es >= 0x10 && es < 0x16) {
            // Range OK:

            // NOTE: This mapping between electronic signature and device size is device specific!
            //       This mapping works for ST M25Pxx and Saifun SA25Fxxx families.
            cur_spi_size = 1 << (es + 1);

            num_spis++;

            if (spi_sel == 0) {
                spi_size = cur_spi_size;
            } else if (cur_spi_size != spi_size){
                return errmsg("SPI flash #%d of size 0x%x bytes differs in size from SPI flash #%d of size 0x%x bytes. "
                              "All flash devices must be of the same size.",
                              spi_sel,
                              cur_spi_size,
                              spi_sel - 1,
                              spi_size);
            }
            

        } else if (es == 0xff) {
            // No spi device on this chip_select
            break;
        } else {
            return errmsg("Unexpected SPI electronic signature value (0x%2x) when detecting flash size. "
                          "Flash #%d my be defected.",
                          es,
                          spi_sel);
        }

        printf("-D- %3d %08x\n", spi_sel, cur_spi_size);
    }

    _cfi_data.device_size = spi_size * num_spis;
    _log2_bank_size       = log2up(spi_size);

    
    _cmd_set = new CmdSetStSpi(*this);

    return true;
}


bool SpiFlash::set_bank_int(u_int32_t bank)
{
    if (!_mf) {
        return errmsg("Not opened");
    }

    // TODO: Check number of banks in open!
    if (bank > 3) {
        return errmsg("Tried to set bank to %d but %d is the is the largest bank number", bank, 3);
    }

    //printf("\n*** Flash::set_bank(0x%lx) : 0x%lx\n", bank, (bank >> 19) & 0x07);
    u_int32_ba flash_cs;
    flash_cs.range(31,30) = bank;
    MWRITE4(FLASH_CS, flash_cs);  

    return true;
} // Flash::SpiFlash::set_bank


////////////////////////////////////////////////////////////////////////
bool SpiFlash::wait_ready(const char* msg)
{
    u_int32_ba gw_cmd = 0;
    u_int32_t cnt = 0;
    do {
        // Timeout checks
        if (++cnt > FLASH_CMD_CNT) {
            return errmsg("Flash gateway timeout: %s.", msg);
        }

        MREAD4(FLASH_GW, &gw_cmd);

    } while (gw_cmd[BUSY]);

    return true;
}


////////////////////////////////////////////////////////////////////////
bool SpiFlash::read(u_int32_t addr, u_int32_t *data)
{
    if (!_mf) {
        return errmsg("Not opened");
    }

    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }

    if (!set_bank(addr))
        return false;


    //
    // Prepare command word
    //

    u_int32_ba gw_cmd;
    u_int32_ba gw_addr;

    gw_cmd[BUSY]                   = 1;
    gw_cmd[READ_OP]                = 1;
    //gw_cmd[ADDR_INCR]              = 0;

    gw_cmd.range(MSIZE_E, MSIZE_S) = 2;

    gw_addr.range(SPI_ADDR_E, SPI_ADDR_S) = addr & bank_mask();

    MWRITE4(FLASH_ADDR, gw_addr);
    MWRITE4(FLASH_GW,   gw_cmd);

    if (!wait_ready("Read"))
        return false;

    MREAD4(FLASH_DATA, data);

    *data = __cpu_to_be32(*data);

    return true;
} // SpiFlash::read


////////////////////////////////////////////////////////////////////////
bool SpiFlash::read_id(u_int8_t *data, u_int8_t cmd)
{

    //
    // Prepare command word
    //

    u_int32_ba gw_cmd;
    u_int32_ba gw_addr;
    u_int32_t flash_data;

    gw_cmd[BUSY]                   = 1;
    gw_cmd[READ_OP]                = 1;
    gw_cmd[SPI_SPECIAL]            = 1;
    gw_cmd[SPI_NO_ADDR]            = 1;

    gw_cmd.range(MSIZE_E, MSIZE_S) = 2;

    gw_addr.range(SPI_CMD_E, SPI_CMD_S) = cmd;

    MWRITE4(FLASH_ADDR, gw_addr);
    MWRITE4(FLASH_GW,   gw_cmd);

    if (!wait_ready("Read id"))
        return false;

    MREAD4(FLASH_DATA, &flash_data);

    /* ID is at offset 3 in word */
    *data = (u_int8_t)(flash_data & 0xff);

    //printf("-D- ES is %02x\n", *data);

    return true;
} // SpiFlash::read

//
// TODO: Unify all the block handling code with the CmdSet001 write.
//

bool SpiFlash::CmdSetStSpi::write (u_int32_t addr, 
                                   void*     data, 
                                   int       cnt,
                                   bool      noerase, 
                                   bool      noverify) {

    if (!_f._mf) {
        return _f.errmsg("Not opened");
    }
    if (addr & 0x3) {
        return _f.errmsg("Address should be 4-bytes aligned.");
    }

    u_int8_t         *p = (u_int8_t *)data;

    u_int32_t block_size = _f._cfi_data.max_multi_byte_write;
    u_int32_t block_mask = ~(block_size - 1 );

    // TODO - Check MAX_WRITE_BUFFER_SIZE against block_size in open (or here)
    u_int8_t  tmp_buff[MAX_WRITE_BUFFER_SIZE];

    while (cnt) {

        u_int32_t prefix_pad_size = 0;
        u_int32_t suffix_pad_size = 0;

        u_int32_t block_addr = addr & block_mask;
        u_int32_t data_size  = block_size;

        u_int8_t* block_data = p;


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

            block_data = tmp_buff;
        }

        //
        // Bank setup.
        //
        if (!_f.set_bank(addr))
            return false;

        if (!noerase) {
            u_int32_t sector = (addr / _f.get_sector_size()) * _f.get_sector_size();
            if (sector != _curr_sector) {
                _curr_sector = sector;
                if (!erase_sector(_curr_sector))
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
            if (block_data[i] != 0xff) {
                all_ffs = false;
                break;
            }
        }

        if (!all_ffs) {

            if (!write_block(block_addr, block_data, block_size))
                return false;

            if (!noverify) {
                u_int8_t verify_buffer[MAX_WRITE_BUFFER_SIZE];
                if (!reset())
                    return false;

                if (!_f.read(addr, verify_buffer, data_size))
                    return false;

                for (u_int32_t i = 0 ; i < data_size ; i++) {
                    if (verify_buffer[i] != block_data[i + prefix_pad_size]) {
                        return _f.errmsg("Write verification failed. Addr %08x - exp:%02x act:%02x\n",
                               addr + i, 
                               block_data[i + prefix_pad_size] , 
                               verify_buffer[i]);
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
} 

bool SpiFlash::CmdSetStSpi::erase_sector(u_int32_t addr)
{

    if (_no_erase)
        return true;

    u_int32_ba gw_cmd;
    u_int32_ba gw_addr;


    if (!write_enable())
        return false;

    //
    // Erase sector command:
    //

    gw_cmd[BUSY]                   = 1;
    gw_cmd[SPI_SPECIAL]            = 1;
    gw_cmd[SPI_NO_DATA]            = 1;

    gw_addr.range(SPI_CMD_E,  SPI_CMD_S)  = FC_SE;
    gw_addr.range(SPI_ADDR_E, SPI_ADDR_S) = addr & _f.bank_mask();

    MWRITE4(FLASH_ADDR, gw_addr);
    MWRITE4(FLASH_GW,   gw_cmd);

    if (!_f.wait_ready("ES"))
        return false;

    //
    // Wait for erase completion
    //

    if (!wait_wip(ERASE_DELAY, ERASE_CNT))
        return false;

    return true;
} // Flash::erase_sector



bool SpiFlash::CmdSetStSpi::write_block(u_int32_t block_addr, 
                                        void*     block_data, 
                                        u_int32_t block_size) {

    u_int32_ba gw_cmd;
    u_int32_ba gw_addr;

    // sanity check ??? remove ???
    if (block_size != (u_int32_t)_f._cfi_data.max_multi_byte_write) {
        return _f.errmsg("Block write of wrong block size. %d instead of %d", 
			 block_size, (u_int32_t)_f._cfi_data.max_multi_byte_write);
    }

    if (!write_enable())
        return false;

    //
    // Write the data block
    //


    gw_cmd[BUSY]                   = 1;
    gw_cmd[SPI_SPECIAL]            = 1;

    gw_cmd.range(MSIZE_E, MSIZE_S) = log2up(block_size);

    gw_addr.range(SPI_CMD_E,  SPI_CMD_S)  = FC_PP;
    gw_addr.range(SPI_ADDR_E, SPI_ADDR_S) = block_addr & _f.bank_mask();

    MWRITE4(FLASH_ADDR, gw_addr);

    // Data:
    for (u_int32_t offs = 0 ; offs < block_size ; offs += 4) {
        // NOTE: !!! To much swapping around the data. !!!
        // Flash GW in sinai eats full DWords with byte0 as high data.
        // TODO: Swap on writes in Parallel flash. Save double swapping for serial flash. 
        u_int32_t word = *((u_int32_t*)((u_int8_t*)block_data + offs));
        word = __be32_to_cpu(word);
        MWRITE4(FLASH_DATA + offs, word );
    }

    MWRITE4(FLASH_GW,   gw_cmd);

    if (!_f.wait_ready("PP command"))
        return false;

    //
    // Wait for end of write in flash (WriteInProgress = 0):
    //

    if (!wait_wip(READ_DELAY, READ_CNT_SLOW + READ_CNT_FAST, READ_CNT_FAST))
        return false;

    return true;
}


bool SpiFlash::CmdSetStSpi::write_enable() {

    u_int32_ba gw_cmd;
    u_int32_ba gw_addr;

    //
    // Write enable:
    //

    gw_cmd[BUSY]                   = 1;
    gw_cmd[SPI_NO_ADDR]            = 1;
    gw_cmd[SPI_NO_DATA]            = 1;
    gw_cmd[SPI_SPECIAL]            = 1;

    gw_addr.range(SPI_CMD_E,  SPI_CMD_S)  = FC_WREN;

    MWRITE4(FLASH_ADDR, gw_addr);
    MWRITE4(FLASH_GW,   gw_cmd);

    if (!_f.wait_ready("WREN command"))
        return false;

    return true;
}

bool SpiFlash::CmdSetStSpi::wait_wip(u_int32_t delay, u_int32_t retrys, u_int32_t fast_retrys  ) {


    u_int32_ba gw_cmd;
    u_int32_ba gw_data;
    u_int32_ba gw_addr;

    u_int32_t cnt = 0;

    //
    // Read SR:
    //

    gw_cmd[BUSY]                   = 1;
    gw_cmd[READ_OP]                = 1;
    gw_cmd[SPI_NO_ADDR]            = 1;
    gw_cmd[SPI_SPECIAL]            = 1;

    gw_addr.range(SPI_CMD_E,  SPI_CMD_S)  = FC_RDSR;

    do {

        if (++cnt > fast_retrys)
            usleep(delay);
        if (cnt > retrys) {
            reset();
            return _f.errmsg("Flash write error - Write In Progress bit did not clear.");
        }

        MWRITE4(FLASH_ADDR, gw_addr);
        MWRITE4(FLASH_GW,   gw_cmd);

        if (!_f.wait_ready("RDSR"))
            return false;

        MREAD4(FLASH_DATA, &gw_data);

    } while (gw_data[24]); // WIP bit in status reg - Note byte 0 is in bits 31-24 of data word.

    return true;
}


////////////////////////////////////////////////////////////////////////
//
// Burn Operations functions
//
////////////////////////////////////////////////////////////////////////

class Operations : public ErrMsg {
public:

    Operations() : _last_image_addr(0), _num_ports(2), _allow_skip_is(false) {}

    enum {
	GUIDS = 4
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
        II_Last               = 8,  // Mark the end of used tag ids
        II_End                = 0xff
    };
    
    struct ImageInfo;

    bool write_image     (Flash& f, u_int32_t addr, void *data, int cnt, bool need_report);
    bool WriteSignature  (Flash& f, u_int32_t image_idx, u_int32_t sig);
    bool repair          (Flash& f, const int from, const int to, bool need_report);
    bool FailSafe_burn   (Flash& f, void *data, int size, bool single_image_burn, bool need_report);

    bool Verify          (FBase& f);
    bool DumpConf        (const char* conf_file = NULL);
    bool GetExpRomVersion(u_int32_t& rom_version);
    
    bool DisplayImageInfo(ImageInfo* info);

    bool QueryAll        (FBase& f, ImageInfo* info) {return QueryIs(f, info) && 
                                                             (!info->isFailsafe || QueryPs(f, info)) && 
                                                             QueryImage(f, info);}

    bool getBSN          (char *s, guid_t *guid);
    bool getGUID         (const char *s, guid_t *guid);

    bool patchVSD        (FImage& f, 
                          const char *user_vsd, 
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid);
    
    bool patchGUIDs      (FImage& f, guid_t guids[GUIDS], guid_t old_guids[GUIDS], bool interactive);

    void SetNumPorts     (u_int32_t num_ports) {_num_ports = num_ports;}
    void SetAllowSkipIs  (bool asis)           {_allow_skip_is = asis;}
    
    bool ask_user        ();

    u_int32_t              _last_image_addr;


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
            psid[0] = '\0';
            vsd[0]  = '\0';
            for (int i=0; i < II_Last; i++ ) 
                infoFound[i] = false;
        }
        
        // *Ok : The exit status ofthe specific query.
        // Note - invSectOk = true doesnt mean that invariant sector exists, it
        //        only means that the query was OK (and isFailsafe may be false).

        bool         invSectOk;
        bool         psOk;
        bool         imageOk;

        bool         isFailsafe;


        bool         validImage[2];
        u_int32_t    psStart;
        u_int32_t    imgStart;

        guid_t       guids[4];
        char         vsd[209];
        char         psid[17];
        char         productVer[17];

        u_int8_t     isVer;
        u_int16_t    fwVer[3];        // = {major_ver, minor_ver , sum_minor_ver}
        u_int16_t    fwTime[6];  // = {year, month, day, hour, minute, second}

        u_int16_t    devType;
        u_int8_t     devRev;

        bool         infoFound[II_Last];

        bool         expRomFound;
        u_int32_t    expRomVer;

    };
    


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

    bool checkList              (FBase& f, u_int32_t offs, const char *pref);

    bool extractGUIDptr         (u_int32_t sign, u_int32_t *buf, int buf_len,
				 char *pref, u_int32_t *ind, int *nguids);

    void patchGUIDsSection      (u_int32_t *buf, u_int32_t ind,
				 guid_t guids[GUIDS], int nguids);
    
    u_int32_t BSN_subfield      (const char *s, int beg, int len);

    void _patchVSD              (FImage& f, int ind, char *vsd);

    void PatchPs                (u_int8_t*      rawPs, 
                                 const char     vsd[VSD_LEN],
                                 const char     psid[PSID_LEN]   = NULL,
                                 u_int32_t      imageAddr        = 0);


    bool QueryIs                (FBase& f,  ImageInfo* info);
    bool QueryPs                (FBase& f,  ImageInfo* info);
    bool QueryImage             (FBase& f,  ImageInfo* info);

    
    bool ParseInfoSect          (u_int8_t* buff, u_int32_t byteSize, ImageInfo *info);

    u_int32_t _num_ports;
    bool      _allow_skip_is;

    std::vector<u_int8_t>  _fw_conf_sect;
    std::vector<u_int8_t>  _rom_sect;
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

    if (!f.write( sect_size * (image_idx + 1)  + 8, &sig, 4, true, false))
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

    report("Burning %-9s FW image without signatures  - ", image_name);
    fflush(stdout);

    // Invalidate signature
    u_int32_t zeros = 0;
    if (!f.write(ps_addr + 8, &zeros, 4, true, false)) {
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
    report("Restoring %-9s signature                  - ", image_name); 
    fflush(stdout);

    // Burn PS
    if (!write_image(f, ps_addr, data8 + ps_addr, sect_size, false)) {
        report("FAILED\n\n");
        return false;
    }

    // Validate signature
    u_int32_t sig = SIGNATURE;
    TOCPU1(sig);
    if (!f.write(ps_addr + 8, &sig, 4, true, false)) {
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

    report("\nRead and verify Invariant Sector               - ");
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
bool Operations::FailSafe_burn(Flash& f, void *data, int size, bool single_image_burn, bool need_report)
{
    u_int32_t *data32 = (u_int32_t *)data;
    u_int8_t  *data8 =  (u_int8_t *)data;

    u_int32_t i;
        
    u_int32_t sect_size = f.get_sector_size();

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
    report("Read and verify PPS/SPS on flash               - ");
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


////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//                        VERIFY FLASH                                //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////
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
bool Operations::checkGen(FBase& f, u_int32_t beg,
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
    if (gph.type < H_FIRST  ||  gph.type > H_LAST) {
        if (part_cnt > 2) {
            //report("%s /0x%x/ - Invalid partition type (%d)\n",
            //       pref, offs+beg, gph.type);
            //return false;
        } else
            return checkBoot2(f, beg, offs, next, pref);
    }

    // All partitions here
    offs += beg;
    switch (gph.type) {
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
    case H_FW_CONF:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (FW Configuration)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_ROM:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (ROM)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_USER_DATA:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (User Data)",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4);
        break;
    case H_IMG_INFO:
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (Image Info)",
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
        // For forward compatibility, try analyzing even if section type is uncknown
        // Assuming the size is in DW, like all other sections (except emt service).
        // If this assumption is wrong, CRC calc would fail - no harm done.
        size = gph.size * sizeof(u_int32_t);
        sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (UNKNOWN SECTION TYPE (%d))",
                pref, offs, offs+size+(u_int32_t)sizeof(gph)+3,
                size+(u_int32_t)sizeof(gph)+4, gph.type);

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
        return false;
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
bool Operations::checkList(FBase& f, u_int32_t offs, const char *pref)
{
    u_int32_t next_ptr;

    CHECKB2(f, offs, 0x28, next_ptr, pref);
    part_cnt = 1;
    while (next_ptr && next_ptr != 0xff000000)
        CHECKGN(f, offs, next_ptr, next_ptr, pref);

    return true;
} // checkList

////////////////////////////////////////////////////////////////////////
bool Operations::Verify(FBase& f)
{
    u_int32_t prim_ptr, scnd_ptr;
    u_int32_t signature;

    bool ret = true;

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    if (signature == SIGNATURE) {
        // Full image
        _image_is_full = true;

        bool psStat[2];

        report("\nFailsafe image:\n\n");
        CHECKB2(f, 0, 0x28, prim_ptr, "Invariant      ");
        report("\n");
        psStat[0] = checkPS(f, f.get_sector_size(), prim_ptr, "Primary  ");
        if (psStat[0]) {
            ret &= checkList(f, prim_ptr, "               ");
        }
        report("\n");
        psStat[1] = checkPS(f, f.get_sector_size() * 2, scnd_ptr, "Secondary");
        if (psStat[1]) {
            CHECKLS(f, scnd_ptr, "               ");
        }

        if (psStat[0] == false && psStat[1] == false) {
            ret = false;
        }
    } else {
        // Short image
        _image_is_full = false;
        report("\nShort image:\n");
        CHECKLS(f, 0, "    ");
    }

    return ret;
} // Verify

bool Operations::GetExpRomVersion(u_int32_t& rom_version) {
    const char* magic_string = "mlxsign:";
    u_int32_t   magic_len    = strlen(magic_string);
    u_int32_t   i;
    bool        magic_found  = false;
    u_int32_t   ver_offset;
    u_int8_t    rom_checksum = 0;
    u_int32_t   rom_checksum_range;

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

    rom_checksum_range = _rom_sect[1] * 512; // I take byte 1 instead of byte 2 since the bytes are swapped
    if (rom_checksum_range > _rom_sect.size()) {
       return errmsg("ROM size field (0x%2x) is larger than actual ROM size (0x%x)", 
                     rom_checksum_range , 
                     (u_int32_t)_rom_sect.size());
    }

    for (i = 0; i < rom_checksum_range; i++) {
        rom_checksum += _rom_sect[i];
    }

    if (rom_checksum != 0) {
        return errmsg("Bad ROM Checksum (0x%2x)", rom_checksum);
    }

    // restore endianess.
    TOCPUn(&(_rom_sect[0]), _rom_sect.size()/4);

    for (i = 0 ; i < _rom_sect.size(); i++) {
        for (u_int32_t j = 0; j < magic_len; j++) {
            if (_rom_sect[i+j] != magic_string[j]) {
                break;
            }
            magic_found = true;
        }

        if (magic_found) {
            break;
        }
    }

    if (magic_found) {
        ver_offset = i + magic_len;
    } else {
        return errmsg("Mellanox version string (%s) nof found in ROM section.", magic_string);
    }

    rom_version = //*( (*u_int32_t) &_rom_sect[ver_offset] );
        __le32_to_cpu(*((u_int32_t*) &_rom_sect[ver_offset])) ;
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
    *ind += offs;
    if (*ind >= (u_int32_t)buf_len) {
        printf("%s image - illegal GUID pointer (%08x)\n", pref, *ind);
        return false;
    }
    *nguids = buf[*ind/4 - 3];
    TOCPU1(*nguids);
    *nguids /= 2;

    // More sanity check
    if (*nguids > GUIDS) {
        printf("%s image - illegal number of GUIDs (%d)\n", pref, *nguids);
        return false;
    }

    return true;
} // extractGUIDptr

////////////////////////////////////////////////////////////////////////
void Operations::patchGUIDsSection(u_int32_t *buf, u_int32_t ind,
                       guid_t guids[GUIDS], int nguids)
{
    u_int32_t       i, word;
    u_int32_t       new_buf[GUIDS*2];
    Crc16              crc;

    // Form new GUID section
    for (i=0; i<(u_int32_t)nguids; i++) {
        new_buf[i*2] = guids[i].h;
        new_buf[i*2+1] = guids[i].l;
    }

    // Calculate new CRC16
    for (i=ind/4 - 4; i<ind/4; i++) {
        word = __be32_to_cpu(buf[i]);
        crc << word;
    }
    for (i=0; i<(u_int32_t)nguids*2; i++)
        crc << new_buf[i];

    // Patch GUIDs
    for (i=0; i<sizeof(new_buf)/sizeof(u_int32_t); ++i) {
        new_buf[i] = __cpu_to_be32(new_buf[i]);
    }
    memcpy(&buf[ind/4], &new_buf[0], nguids * 2 * sizeof(u_int32_t));

    // Insert new CRC
    crc.finish();
    word = crc.get();
    buf[ind/4 + nguids*2] = __cpu_to_be32(word);
} // patchGUIDsSection


////////////////////////////////////////////////////////////////////////
void Operations::_patchVSD(FImage& f, int ind, char *vsd)
{
    u_int32_t  *buf = f.getBuf();
    Crc16      crc;
    PS         *ps = (PS*)&buf[ind/4];

    memcpy(&ps->vsd[0], vsd, VSD_LEN + PSID_LEN);

    u_int32_t *qp = (u_int32_t *)ps;
    for (unsigned int i=0; i<sizeof(PS)/sizeof(u_int32_t) - 1; i++) {
        u_int32_t qq = *qp++;
        TOCPU1(qq);
        crc << qq;
    }
    crc.finish();
    u_int32_t crc016 = crc.get();
    ps->crc016 = __cpu_to_be32(crc016);
} // _patchVSD


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

    Crc16      crc;
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

    qp = (u_int32_t *)ps;
    for (unsigned int i=0; i<sizeof(PS)/sizeof(u_int32_t) - 1; i++) {
        u_int32_t qq = *qp++;
        TOCPU1(qq);
        crc << qq;
    }
    crc.finish();
    u_int32_t crc016 = crc.get();
    ps->crc016 = __cpu_to_be32(crc016);

}
        

////////////////////////////////////////////////////////////////////////
//Note that vsd1 is a string of bytes.
bool Operations::patchVSD(FImage& f, 
                          const char *user_vsd, 
                          const char *user_psid,
                          const char *curr_vsd,
                          const char *curr_psid,
                          const char *image_psid)
{
    const char* vsd_to_use  = curr_vsd ? curr_vsd : "";
    const char* psid_to_use = image_psid;

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


    if (curr_psid && strncmp( psid_to_use, (char*) curr_psid, PSID_LEN)) {
        printf("\n    You are about to replace current PSID on flash - \"%s\" with a different PSID - \"%s\".\n"

               "    Note: It is highly recommended not to change the PSID.\n",
	       curr_psid, psid_to_use);

        if (! ask_user())
            return false;
    }

    PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size(),     vsd_to_use, psid_to_use);
    PatchPs((u_int8_t*)f.getBuf() + f.get_sector_size() * 2, vsd_to_use, psid_to_use);

    return true;
} // pathVSD


////////////////////////////////////////////////////////////////////////
bool Operations::patchGUIDs(FImage& f, guid_t new_guids[GUIDS], guid_t old_guids[GUIDS], bool interactive)
{
    guid_t          image_file_guids[GUIDS];
    guid_t*         used_guids = old_guids ? old_guids : new_guids;
    u_int32_t       *buf = f.getBuf();
    int             buf_len = f.getBufLength();
    u_int32_t       signature = buf[0x24/4];
    u_int32_t       ind1=0,ind2=0;
    int             nguid1, nguid2;

    TOCPU1(signature);
    if (signature == SIGNATURE) {
        // Full image
        if (interactive)
            printf("\nFull image:\n\n");
        if (!extractGUIDptr(f.get_sector_size()   , buf, buf_len, "Primary"  , &ind1, &nguid1) &&
            !extractGUIDptr(f.get_sector_size() *2, buf, buf_len, "Secondary", &ind2, &nguid2))
            return false;

    } else {
        // Short image
        if (interactive)
            printf("\nShort image:\n\n");
        if (!extractGUIDptr(0, buf, buf_len, "Primary", &ind1, &nguid1))
            return false;
    }

    // Print old GUIDs and get confirmation
    if (interactive && new_guids) {
        bool image_file_old_guids_fmt = nguid1 < GUIDS;
        for (int i=0; i<GUIDS; i++) {
            u_int32_t h = buf[ind1/4 + i*2];
            TOCPU1(h);
            u_int32_t l = buf[ind1/4 + i*2 + 1];
            TOCPU1(l);
            image_file_guids[i].h = h;
            image_file_guids[i].l = l;
        }
        if (image_file_old_guids_fmt)
            printf("    Old image!!!! Only %d GUIDs may be set.\n", nguid1);
        if (old_guids) {
            printf("    Current GUIDs are:\n");
            printf("        Node:      " GUID_FORMAT "\n", old_guids[0].h,old_guids[0].l);
            printf("        Port1:     " GUID_FORMAT "\n", old_guids[1].h,old_guids[1].l);
            if (_num_ports > 1) 
                printf("        Port2:     " GUID_FORMAT "\n", old_guids[2].h,old_guids[2].l);
            if (!image_file_old_guids_fmt)
                printf("        Sys.Image: " GUID_FORMAT "\n", old_guids[3].h,old_guids[3].l);
        }

        printf("\n    You are about to burn the image with the following GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", new_guids[0].h,new_guids[0].l);
        printf("        Port1:     " GUID_FORMAT "\n", new_guids[1].h,new_guids[1].l);
	if (_num_ports > 1) 
	    printf("        Port2:     " GUID_FORMAT "\n", new_guids[2].h,new_guids[2].l);
        if (!image_file_old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", new_guids[3].h,new_guids[3].l);

        if (!ask_user())
            return false;

        used_guids = new_guids;
    }

    // Path GUIDs section
    if (ind1) 
        patchGUIDsSection(buf, ind1, used_guids, nguid1);
    if (ind2)
        patchGUIDsSection(buf, ind2, used_guids, nguid2);

    if (!interactive) {
        bool old_guids_fmt = nguid1 < GUIDS;
        printf("\n    Burn image with the following GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", used_guids[0].h,used_guids[0].l);
        printf("        Port1:     " GUID_FORMAT "\n", used_guids[1].h,used_guids[1].l);
	if (_num_ports > 1) 
	    printf("        Port2:     " GUID_FORMAT "\n", used_guids[2].h,used_guids[2].l);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", used_guids[3].h,used_guids[3].l);
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
        info->imgStart = prim_ptr;
        info->psStart  = sectSize;
    } else if (checkPS(f, sectSize * 2, scnd_ptr, "Secondary")) {
        info->imgStart = scnd_ptr;
        info->psStart  = sectSize * 2;
    } else {
        return errmsg("No valid image found.");
    }

    char       vsd[VSD_LEN+PSID_LEN+1];   // +1  => Leave a space for \0 when psid size == 16 .

    memset(vsd, 0, sizeof(vsd));
    READBUF(f, info->psStart + 0x20, vsd, VSD_LEN+PSID_LEN , "Vendor Specific Data (Board ID)");
    u_int32_t* vsd_dwp = (u_int32_t*)vsd;

    for (u_int32_t i=0; i < sizeof(vsd)/sizeof(u_int32_t); i++)
         vsd_dwp[i] = bswap_32(vsd_dwp[i]);
    
    //TOCPUBY(vsd);

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
    guid_t guids[GUIDS];

    // FW ID
    u_int32_t fw_id;
    u_int32_t im_start = info->imgStart;


    READ4(f, im_start + 0x10, &fw_id, "FW ID");
    TOCPU1(fw_id);

    info->devRev  = fw_id >> 24;    
    // Read GUIDs
    READ4(f, im_start + 0x24, &guid_ptr, "GUID PTR");
    TOCPU1(guid_ptr);
    guid_ptr += im_start;
    if (guid_ptr >= f.get_size()) {
        return errmsg("Failed to read GUIDs - Illegal GUID pointer (%08x). Probably image is corrupted", guid_ptr);
    }
    READ4(f, guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
    TOCPU1(nguids);
    if (nguids > GUIDS*2) {
        report("Failed to read GUIDs - Illegal Number of GUIDs (%d)\n", nguids);
        return false;
    }
    READBUF(f, guid_ptr, guids, nguids / 2 * sizeof(u_int64_t), "GUIDS");
    TOCPUBY64(guids);
    for (u_int32_t i = 0 ; i < nguids/2 ; i++) {
        info->guids[i] = guids[i];
    }

    // Expansion Rom version:
    info->expRomVer = 0;
    if (_rom_sect.empty()) {
        info->expRomFound = false;
    } else {
        info->expRomFound = true;
        if (!GetExpRomVersion(info->expRomVer)) {
            report("Failed to get ROM Version: %s\n", err()); 
        }
    }

    // Read Info:
    u_int32_ba info_ptr_ba;
    u_int32_t  info_ptr;
    u_int32_t  info_size;
    u_int8_t   info_ptr_cs = 0;
    READ4(f, im_start + 0x1C, &info_ptr, "INFO PTR");
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

        if (ParseInfoSect(info_buff, info_size,  info)) {
            return false;
        }
    }

    info->imageOk = true;
    return true;
}


bool Operations::ParseInfoSect(u_int8_t* buff, u_int32_t byteSize, Operations::ImageInfo *info) {

    u_int32_t *p = (u_int32_t*)buff;
    u_int32_t offs = 0;

    bool endFound = false;

    while ((__be32_to_cpu(*p) >> 24) != II_End && offs < byteSize) {
        u_int32_t tagSize = __be32_to_cpu(*p) & 0xffffff;
        u_int32_t tagId   = __be32_to_cpu(*p) >> 24;

        u_int32_t   tmp;
        const char* str;

        switch (tagId) {
        case II_FwVersion:
            info->fwVer[0] = __be32_to_cpu(*(p+1)) >> 16;
            tmp = __be32_to_cpu(*(p+2));
            info->fwVer[1] = tmp >> 16;
            info->fwVer[2] = tmp & 0xffff;

            info->infoFound[tagId] = true;
            break;

        case II_DeviceType:
            tmp = __be32_to_cpu(*(p+1));
            info->devType = tmp & 0xffff;
            //info->devRev  = (tmp >> 16) & 0xff;
            info->infoFound[tagId] = true;
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
                
                info->infoFound[tagId] = true;

            }
            break;

        case II_ProductVer: 
        
            str = (const char*)p;
            str += 4;

            for (int i = 0 ; i < PRODUCT_VER_LEN ; i++) {
                info->productVer[i] = str[i];
            }
            info->productVer[PRODUCT_VER_LEN] = '\0';
            
            info->infoFound[tagId] = true;

            break;

        case II_End:
            endFound = true;
            break;

        //default:
            //printf("-D- Found tag ID %d of size %d - ignoring.\n", tagId, tagSize);
        }

        p    += tagSize/4 + 1;
        offs += tagSize;
    }

    offs += 4;

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

bool Operations::DisplayImageInfo(Operations::ImageInfo* info) {

    report("Image type:      %s\n", info->isFailsafe ? "Failsafe" : "Short");

    if (info->infoFound[II_FwVersion]) {
        report("FW Version:      %d.%d.%d\n", info->fwVer[0], info->fwVer[1], info->fwVer[2]);
    }

    if (info->infoFound[II_ProductVer] && strlen(info->productVer)) {
        report("Product Version: %s\n", info->productVer);
    }

    if (info->expRomFound) {
        report("Rom Version:     ");
        if (info->expRomVer) {
            report("%x\n", info->expRomVer);
        } else {
            report("N/A\n");
        }
    }

    if (info->isFailsafe) {
        report("I.S. Version:    %d\n", info->isVer );
    }

    if (info->infoFound[II_DeviceType]) {
        report("Device ID:       %d\n", info->devType);
    }

    report("Chip Revision:   %X\n", info->devRev);

    // GUIDS:
    report("GUID Des:        Node             Port1            ");

    if (_num_ports > 1)
        report("Port2            ");
    report( "Sys image\n");

    report("GUIDs:           ");
    for (u_int32_t i=0; i < GUIDS; i++) {
        if (i != 2 || _num_ports > 1 ) 
            report(GUID_FORMAT " ", info->guids[i].h, info->guids[i].l);
    }


    // VSD, PSID

    report("\nBoard ID:        %s", info->vsd);
    if (info->psid[0])
        report(" (%s)\n", info->psid);
    else
        report("\n");

    report("VSD:             %s\n", info->vsd);
    report("PSID:            %s\n", info->psid);
    
    return true;
}

////////////////////////////////////////////////////////////////////////
//                                                                    //
// ****************************************************************** //
//       Detect Device type and return matching Flash interface       //
// ****************************************************************** //
//                                                                    //
////////////////////////////////////////////////////////////////////////

Flash* get_serial_flash(mfile* mf) {

    enum {
        CR_FLASH_TYPE   = 0xf0810,
        BO_FLASH_TYPE_S = 10,
        BO_FLASH_TYPE_E = 11,
    };

    enum FlashType {
        FT_LPC    = 0,
        FT_SPI    = 1,
        FT_XBUS   = 2,
        FT_EEPROM = 3
    };

    char* flash_type_str[] = {"LPC", "SPI", "XBUS", "EEPROM"};

    u_int32_ba strap_option;
    u_int32_t  flash_type;

    if (mread4(mf, CR_FLASH_TYPE, &strap_option) != 4) return false;

    flash_type = strap_option.range(BO_FLASH_TYPE_E, BO_FLASH_TYPE_S);


    switch (flash_type) {
    case FT_SPI:
        return new SpiFlash;
    case FT_LPC:
    case FT_XBUS:
    case FT_EEPROM:
        printf("*** ERROR *** flash of type %s not supported.\n",
               flash_type_str[flash_type]);
    }

    return NULL;

}


Flash* get_flash(const char* device, u_int32_t& num_ports) {
    Flash* f = NULL;

    //
    // Check device ID. Allocate flash accordingly
    //

    u_int32_t dev_id;

    mfile* mf = mopen(device);
    if (!mf) {
        printf("*** ERROR *** Can not open %s: %s\n", device,  strerror(errno));
        return NULL;
    }

    if (mread4(mf, 0xf0014, &dev_id) != 4) return false;

    dev_id &= 0xffff;

    //printf("-D- read dev id: %d\n", dev_id);

    switch (dev_id) {
    case 23108:
    case 25208:
        num_ports = 2;
        f = new ParallelFlash;
        break;

    case 24204:
    case 25204:
        num_ports = 1;
        f = get_serial_flash(mf);
        break;

    case 0xffff:
        printf("*** ERROR *** Read a corrupted device id (0x%x). Probably HW/PCI access problem\n", dev_id);
    default:
        printf("*** ERROR *** Device type %d not supported.\n", dev_id);
    }

    mclose(mf);

    return f;
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
    "Mellanox InfiniHost HCAs family.\n"
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
    "    -clear_semaphore   - Force clear the flash semaphore on the device.\n"
    "                         This flag should come BEFORE the -d[evice] flag\n"
    "                         on the command line.\n"
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
    "    -psid <PSID>       - Write the Parameter Set ID (PSID) string to PS-ID field (last 16 bytes of VSD) when burn.\n"
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
    "    b[urn]   - Burn flash\n"
    "    e[rase]  - Erase sector\n"
    "    q[uery]  - Query misc. flash/firmware characteristics\n"
    "    rw       - Read one dword from flash\n"
    "    v[erify] - Verify entire flash\n"
    "    ww       - Write one dword to flash\n"
    "    bb       - Burn Block - Burns the given image as is. No checks are done.\n"
    "    wwne     - Write one dword to flash without sector erase\n"
    "    wbne     - Write a data block to flash without sector erase\n"
    "    rb       - Read  a data block from flash\n"
    "    ri       - Read the fw image on the flash.\n"
    "    dc       - Dump Configuration: print fw configuration file for the given image.\n"
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
        g_flash->wait_ready("Process termination");

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
    { CMD_QUERY          , "query" ,false , 0 , CI_IMG_OR_DEV  , ""},
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
    bool         burn_failsafe    = true;
    bool         use_image_ps     = false;
    bool         single_image_burn = true;

    char*        cmdStr           = NULL;

    char         *user_vsd=0;
    char         *user_psid=0;
    guid_t       user_guids[Operations::GUIDS];
    int		 rc = 0;

    CommandType cmd = CMD_UNKNOWN;

    auto_ptr<Flash>       f;
    FImage                fim;

    Operations            ops;

    FBase*      fbase     = NULL;
    char*       cmdTarget = NULL;
    char*       cmdAccess = NULL;

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

                //f.reset( get_flash(device) );

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
                NEXTS("-guids");
                for (int j=0; j<Operations::GUIDS; j++) {
                    GETGUID(av[i], &user_guids[j]);
                    if (++i >= ac) {
                        printf("Exactly four GUIDs must be specified.\n");
                        rc =  1; goto done; 
                    }
                }
                i--;
                guids_specified = true;
            } else if (!strncmp(av[i], "-silent", switchLen))
                silent = true;
            else if (!strncmp(av[i], "-use_image_ps", 2))
                use_image_ps = true;
            else if (!strncmp(av[i], "-nofs", 5))
                burn_failsafe = false;
            else if (!strcmp(av[i], "-skip_is"))
                ops.SetAllowSkipIs(true);
            else if (!strncmp(av[i], "-yes", switchLen))
                _assume_yes = true;
            else if (!strcmp(av[i], "-byte_mode"))
                ParallelFlash::set_byte_mode(true);

            else if (!strncmp(av[i], "-hh", 3) ||  !strncmp(av[i], "--hh", 4)) {
                usage(av[0], true);
                rc =  1; goto done; 
            } else if (!strncmp(av[i], "-help", switchLen) ||  !strncmp(av[i], "--h", 3)) {
                usage(av[0]);
                rc =  1; goto done; 
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

        u_int32_t num_ports;
        auto_ptr<Flash>       tmp( get_flash(device, num_ports));
        f = tmp;
        
        if (f.get() == NULL) {
            printf("*** ERROR *** Can not get flash type using device %s\n", device);
            rc =  1; goto done; 
        }
        
        ops.SetNumPorts(num_ports);
        
        g_flash = f.get();
        if (!f->open(device, clear_semaphore)) {
            printf("*** ERROR *** Can not open %s: %s\n", device, f->err());
            rc =  1; goto done; 
        }

        cmdTarget = "Flash";
        cmdAccess = device;
        fbase     = f.get();
    }

    if (image_fname) {
        if (!fim.open(image_fname)) {
            printf("*** ERROR *** Image file open failed: %s\n", fim.err());
            rc =  1; goto done; 
        }

        cmdTarget = "Image file";
        cmdAccess = image_fname;
        fbase     = &fim;
    }





    switch (cmd) {
    case CMD_BURN:
    case CMD_BURN_BLOCK:
    {
        
        //
        // BURN
        //

        bool burn_block = (cmd == CMD_BURN_BLOCK);
                
        if (!burn_block) {
            // Make checks and replace vsd/guids.
            
            Operations::ImageInfo fileInfo;
            Operations::ImageInfo flashInfo;
            
            bool old_silent = _silent;
            _silent = true;
            if (!ops.Verify(fim) || !ops.QueryAll(fim, &fileInfo)) {
                printf("*** ERROR *** %s: Not a valid image file (%s)\n", image_fname, ops.err());
                rc =  1; goto done; 
            }
            
            // Check that the flash sector size is well defined in the image
            if (fim.get_sector_size() && (fim.get_sector_size() != f->get_sector_size())) {
                printf("*** ERROR *** Flash sector size(0x%x) differs from sector size defined in the image (0x%x).\n"
                       "              This means that the given FW file is not configured to work with the burnt HCA board type.\n",
                       f->get_sector_size(),
                       fim.get_sector_size());
                rc =  1; goto done;
            }
            
            // Get GUID and VSD info from flash
            
            bool read_guids = true;
            bool read_ps    = true;
            
            // Flash query (unlike image file query) does not have to
            // pass. E.G. blank flash and the user supplies the needed data (guids, vsd).
            
            bool flash_query_res = ops.QueryAll(*f, &flashInfo);

            if (guids_specified)
                read_guids = false;
            
            if ((user_vsd && user_psid) || use_image_ps)
                read_ps = false;

            if (read_guids && !flash_query_res) {
 
                if (read_guids && !flashInfo.imageOk) {

                    printf("\n");
                    printf("*** ERROR *** Can not extract GUIDS info from flash. "
                           "Please specify GUIDs (using command line flags -guid(s) ). \n");
                }
                
                if (burn_failsafe) {
                    printf("              Can not burn in a failsafe mode.\n");
		    printf("              If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                }
                rc =  1; goto done;
            }

            if (read_ps && !flashInfo.psOk) {
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
            printf("    Current FW version on flash:  ");
            if (flashInfo.infoFound[Operations::II_FwVersion]) {
                printf("%d.%d.%d\n", flashInfo.fwVer[0], flashInfo.fwVer[1], flashInfo.fwVer[2]);  
            } else {
                printf("N/A\n");
            }
            
            printf("    New FW version:               ");
            if (fileInfo.infoFound[Operations::II_FwVersion]) {
                printf("%d.%d.%d\n", fileInfo.fwVer[0], fileInfo.fwVer[1], fileInfo.fwVer[2]);  
            } else {
                printf("N/A\n");
            }


            // Patch GUIDS
            if (guids_specified) {
                if (!ops.patchGUIDs(fim, 
                                    user_guids, 
                                    flashInfo.imageOk ? flashInfo.guids : NULL, 
                                    true)) {
                    rc =  1; goto done;
                }
            } else {
                if (!ops.patchGUIDs(fim, NULL,       flashInfo.guids, false)) {
                    rc =  1; goto done;
                }
            }

            if (_image_is_full && !use_image_ps)
                if (!ops.patchVSD(fim, 
                                  user_vsd, 
                                  user_psid,
                                  flashInfo.psOk ? flashInfo.vsd  : NULL,
                                  flashInfo.psOk ? flashInfo.psid : NULL,
                                  fileInfo.psid )) {
                    rc =  1; goto done;
                }

                _silent = old_silent;
        } else {
            // BURN BLOCK:
            burn_failsafe = false;
        }

        // Burn it
        if (burn_failsafe) {
            // Failsafe burn
            if (!_image_is_full) {
                printf("*** ERROR *** Failsafe burn failed: FW image on flash is short.\n");
                printf("It is impossible to burn a short image in a failsafe mode.\n");
                printf("If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
                rc =  1; goto done; 
            }

            // FS burn
            if (!ops.FailSafe_burn(*f, 
                               fim.getBuf(), 
                               fim.getBufLength(),
                               single_image_burn,
                               !silent)) {
		if (f->err()) {
		    // The error is in flash access:
		    printf("*** ERROR *** Flash access failed during burn: %s\n", f->err());
		} else {
		    // operation/ algorithm error:
		    printf("*** ERROR *** Failsafe operation/ algorithm error: %s\n", ops.err());  
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
	    //TODO: MST proposes:
            //printf("Burn process will not be failsafe. No checks are performed.\n");
            printf("ALL flash, including the Invariant Sector will be overwritten.\n");
            printf("If this process fails, computer may remain in an inoperable state.\n");

            if (!ops.ask_user()) {
                rc =  1; goto done;
	    }

            // Non FS burn
            if (!ops.write_image(*f, 0, fim.getBuf(), fim.getBufLength(),
                             !silent)) {
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

    case CMD_QUERY:
    {
        // QUERY
        Operations::ImageInfo info;

        _silent       = true;
        ops.Verify(*fbase);
        _silent = false;

        if (!ops.QueryAll(*fbase, &info)) {
                printf("*** ERROR *** %s query (%s) failed: %s\n", cmdTarget , cmdAccess, ops.err());
                rc =  1; goto done;
        }

        ops.DisplayImageInfo(&info);
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
        if (!ops.Verify(*fbase)) {
            printf("\n*** ERROR *** FW image verification failed. AN HCA DEVICE CAN NOT BOOT FROM THIS IMAGE.\n");
            rc =  1; goto done; 
        } else {
            printf("\nFW image verification succeeded. Image is OK.\n\n");
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

        ops.Verify(*f);
        
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

        if (!f->write(addr, &data_vec[0], size, true, false)) {
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

        if (!f->write(addr, &data, 4, true, false)) {
            printf("*** ERROR *** Flash write failed: %s\n", f->err());
            rc =  1; goto done; 
        }
    }
    break;

    case CMD_CFI:
    {
        if (!f->print_cfi_info()) {
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

