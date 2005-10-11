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
 *  Version: $Id: flint.cpp,v 1.103 2005/06/22 11:31:28 orenk Exp $
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

#include <alloca.h>
#include <netinet/in.h>
#include <endian.h>
#include <byteswap.h>
#include <unistd.h>

#include <signal.h>

#ifndef O_BINARY
    #define  O_BINARY 0
#endif

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

char* _versionID = "VERSION_ID_HERE";

char* _cvsID     = "$Revision: 1.103 $";

#ifndef __be32_to_cpu
    #define __be32_to_cpu(x) ntohl(x)
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
    printf("%s - read error (%s)\n", p, f.err()); \
    return false; }} while (0)
#define READBUF(f,o,d,l,p) do { if (!f.read(o,d,l)) { \
    printf("%s - read error (%s)\n", p, f.err());      \
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

    delete [] _err;

    va_start(args, format);
    _err = vprint(format, args);
    va_end(args);
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
    H_FIRST = 1, 
    H_DDR   = 1, 
    H_CNF   = 2,
    H_JMP   = 3,
    H_EMT   = 4,
    H_ROM   = 5,
    H_GUID  = 6,
    H_BOARD_ID=7, 
    H_USER_DATA=8,
    H_FW_CONF=9,
    H_LAST  =9 
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

    u_int32_ba  operator[](u_int32_t idx) {return range(idx,idx);}
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
//#define FUJITSU_BYTE_MODE

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
//       the way it reads can not be change. 
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
            int           num_sectors;      // Num sectors of this size 
            u_int32_t     sector_mask;          // Sector mask 
        } erase_block[8];               // Max of 256, but 8 is good 

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
		_cfi_data.manuf_id == 0xff && _cfi_data.device_id == 0xff &&
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

    protected:
        ParallelFlash& _f;


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
            FC_RDID  = 0x09
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
    struct stat        stat_buf;
    int                r_cnt;

    read_only = true;  // FImage can be opened only for read

    int fd = ::open(fname, O_RDONLY | O_BINARY, 0);
    if (fd < 0) {
        return errmsg("Can't open file \"%s\" - %s\n", fname, strerror(errno));
    }
    if (fstat(fd, &stat_buf) < 0) {
        return errmsg("Can't stat file \"%s\" - %s\n", fname, strerror(errno));
    }
    //printf("%ld / 0x%lx\n", stat_buf.st_size, stat_buf.st_size);
    if (stat_buf.st_size & 0x3) {
        return errmsg("Image size should be 4-bytes aligned. Make sure file %s is in the right format (binary image)",
		      fname);
    }

    _buf = new u_int32_t[stat_buf.st_size/4];
    if ((r_cnt = ::read(fd, _buf, stat_buf.st_size)) != stat_buf.st_size) {
        if (r_cnt < 0)
            return errmsg("Read error on file \"%s\" - %s\n",fname, strerror(errno));
        else
            return errmsg("Read error on file \"%s\" - read only %d bytes (from %ld)\n",
			  fname, r_cnt, (unsigned long)stat_buf.st_size);
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
        return errmsg("Can't open device %s: %s", device, strerror(errno));
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
            return errmsg("Can not obtain Flash semaphore (63). You can use -clear_semaphore to force semaphore unlock. See help for details.");
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
                    return _f.errmsg("Use scratchpad: CMD doesn't become zero");
                }
                if (mread4(_f._mf, _f.USE_SCR , &cmd) != 4) return false;

            } while (cmd & CMD_MASK);
            i += 3;
            addr += 3;
        } else if ((u_int8_t)(*p) != 0xff) {

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

            do {
                // Timeout checks
                if (++cnt1 > READ_CNT_FAST)
                    usleep(READ_DELAY);
                if (cnt1 > READ_CNT_FAST + READ_CNT_SLOW) {
                    return _f.errmsg("Flash write error - read value didn't stabilize.");
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
        return _f.errmsg("Status register detected erase error");
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

    for (i=0; i < 8; i++) {
        query->erase_block[i].sector_size = 0;
        query->erase_block[i].num_sectors = 0;
    }   query->erase_block[i].sector_mask = 0;

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

    if ( strncmp( query_str_x8 ,      "QRY" ,3 ) == 0) {
        // x8 CFI flash (AMD)
        query_base = 1;
    } else if ( strncmp( query_str_x16asx8 , "QQR" ,3 ) == 0) {
        // x16 CFI flash worqing in x8 mode (Intel)
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

    // TODO: Implement ...

    //
    // Read device ID and allocate command set accordingly.
    //

    _cmd_set = new CmdSetStSpi(*this);

    //
    // Initiate some CFI fields to mimic cfi query procedure of parallel flash:
    //

    _cfi_data.max_multi_byte_write       = 16;   // In SPI context, this is the transaction size. Max is 16.
    _cfi_data.num_erase_blocks           = 1;
    _cfi_data.erase_block[0].sector_size = 64 * 1024;
    _cfi_data.erase_block[0].sector_mask = ~(_cfi_data.erase_block[0].sector_size - 1);

    // TODO: Check device size and num of devices. Set total device size accordingly
    // _cfi_data.device_size = ???;

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

            write_block(block_addr, block_data, block_size);

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
            return _f.errmsg("Flash write error - Write In Progress bit didn't clear.");
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

    Operations() : _last_image_addr(0), _num_ports(2) {}

    enum {
	GUIDS = 4
    };

    bool write_image     (Flash& f, u_int32_t addr, void *data, int cnt, bool need_report);
    bool WriteSignature  (Flash& f, u_int32_t image_idx, u_int32_t sig);
    bool repair          (Flash& f, const int from, const int to, bool need_report);
    bool FailSafe_burn   (Flash& f, void *data, int size, bool single_image_burn, bool need_report);

    bool Verify          (FBase& f);
    bool DumpConf        (const char* conf_file = NULL);

    bool RevisionInfo    (FBase& f, 
                          guid_t guids_out[GUIDS], 
                          char *vsd_out,
			  bool *fs_image, 
                          bool internal_call = false,
			  bool read_guids    = true, 
                          bool read_ps       = true);

    bool getBSN          (char *s, guid_t *guid);
    bool getGUID         (const char *s, guid_t *guid);

    bool patchVSD        (FImage& f, char *vsd1, char *curr_psid, const char* new_psid);
    
    bool patchGUIDs      (FImage& f, guid_t guids[GUIDS], bool interactive);

    void SetNumPorts     (u_int32_t num_ports) {_num_ports = num_ports;}

    u_int32_t              _last_image_addr;

private:

    bool FailSafe_burn_image   (Flash&       f, 
				void         *data, 
				int          ps_addr, 
				const char*  image_name, 
				int          image_addr,
				int          image_size,
				bool         need_report);

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

    u_int32_t _num_ports;

    std::vector<u_int8_t>  _fw_conf_sect;



};




//
// Asks user a yes/no question. 
// Returns true if user chose Y, false if user chose N.
//
bool ask_user(const char* msg) {
    printf(msg);
    if (_assume_yes)
        printf("y\n");
    else {
        fflush(stdout);
        char c = getchar();
        if (c != '\n')
            while (getchar() != '\n');

        if (c != 'y')
            return false;
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
        return errmsg("Can't copy image. Pointer sector %d signature is bad (%08x).", from, sig);
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
        return errmsg("Invalid image: two FW images should be in a same size.");
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



////////////////////////////////////////////////////////////////////////
bool Operations::FailSafe_burn(Flash& f, void *data, int size, bool single_image_burn, bool need_report)
{
    u_int32_t *data32 = (u_int32_t *)data;
    u_int8_t  *data8 =  (u_int8_t *)data;

	u_int32_t i;

    u_int32_t sect_size = f.get_sector_size();

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
    if (size < (int)sect_size * 3) {
        report("FAILED\n\n");
        return errmsg("Image is too small.");
    }
    if (!f.read(0, &buf1[0] , sect_size)) {
        report("FAILED\n\n");
        return false;
    }
    for (i=0; i < sect_size/4; i++) {
        if (buf1[i] != data32[i]  &&  (data32[i] != 0 || buf1[i] != 0xffffffff)) {
            report("FAILED\n\n");
	    return errmsg("Invariant sector doesn't match. Word #%d (0x%x) "
			  "in image: 0x%08x, while in flash: 0x%08x",
			  i, i, data32[i], buf1[i]);
        }
    }
    report("OK\n");

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

    bool image_ok[2] = {false, false};

    // Check signatures on flash
    report("Read and verify PPS/SPS in flash               - ");
    for (i = 0 ; i < 2 ; i++) {
        if (!f.read(sect_size * (i+1) + 8, &signature_for_compare)) {
            report("FAILED\n\n");
            return false;
        }
        TOCPU1(signature_for_compare);
        if (signature_for_compare == SIGNATURE)
            image_ok[i] = true;
    }

    if (!image_ok[0] && !image_ok[1]) {
        //
        // Both images are invalid in flash
        // --------------------------------
        //
        printf("\nBoth images (primary and secondary) are invalid in flash.\n");
        printf("The burning can't be failsafe, but it is harmless for host.\n");
        printf("\n    Do you want to continue ? (y/n) [n] : ");
        if (_assume_yes)
            printf("y\n");
        else {
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

        if (image_ok[0] == false || image_ok[1] == false) {
            int image_from;
            int image_to;

	    assert (image_ok[1] || image_ok[0]);

            if (image_ok[1]) {
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
        // Both images are valid in flash
        //
        return FailSafe_burn_internal(f, data, size, need_report);

    } else {

        //
        // Single image burn:
        //

        // Extract Primary/Secondary image pointers and lengths
        u_int32_t frst_image_addr = data32[sect_size / 4];
        u_int32_t frst_image_size = data32[sect_size / 4 + 1];
        TOCPU1(frst_image_addr);
        TOCPU1(frst_image_size);

        if (!image_ok[0] && image_ok[1]) {
            // Second image is valid on flash.
            // If the new image can fit in the first image gap, it would be
            //   burnt as first image.
            // Otherwise (new image too big), image on flash is copied from second to 
            //   first image, and new image would be written as second.

            // Image size from flash
            u_int32_t scnd_image_addr;
            if (!f.read(sect_size * 2 , &scnd_image_addr)) {
                report("FAILED\n\n");
                return false;
            }
            TOCPU1(scnd_image_addr);

            if (frst_image_addr + frst_image_size > scnd_image_addr) {
                // New image is too large - can't get in between first image start 
                // and current (second) image - move current image to be first.
                if (!repair(f, 1, 0, need_report))
                    return false;

                // Now 2 images are valid
                image_ok[0] = true;
            } else {
                if (!FailSafe_burn_image(f, data, sect_size, "first", sect_size * 3, frst_image_size, need_report))
                    return false;

                if (!WriteSignature(f, 1, 0))
                    return false;

                return true;
            }
        }

        if (image_ok[0] && image_ok[1]) {

            // Invalidate second image 
            if (!WriteSignature(f, 1, 0)) {
                report("FAILED\n");
                return false;
            }

            image_ok[1] = false;
        }

        if (image_ok[0] && !image_ok[1]) {
            u_int32_t image_size_sect = ((frst_image_size - 1) / sect_size) + 1 ;

            if (!FailSafe_burn_image(f, data, sect_size * 2, "second", sect_size * (3 + image_size_sect) , frst_image_size, need_report))
                return false;

            // Invalidate first image 
            if (!WriteSignature(f, 0, 0))
                return false;

            return true;
        } else {
            report("Bad flash state: Valid images = (%d,%d).\n", image_ok[0], image_ok[1] );
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
    if (part_cnt <= 2) {
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

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    if (signature == SIGNATURE) {
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
    } else {
        // Short image
        _image_is_full = false;
        report("\nShort image:\n");
        CHECKLS(f, 0, "    ");
    }

    return true;
} // Verify


bool Operations::DumpConf        (const char* conf_file) {
#ifndef NO_ZLIB

    FILE* out;
    if (conf_file == NULL) {
        out = stdout;
    } else {
        out = fopen(conf_file, "w");

        if (out == NULL) {
            return errmsg("Can't open file %s for write: %s.", conf_file, strerror(errno));
        }
    }

    if (_fw_conf_sect.empty()) {
        return errmsg("Fw configuration section not found in the given image.");
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
        return errmsg("Failed uncompressing FW Info section. uncompress returnes %d", rc);
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
        *p = tolower(*p);

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
    if (cc_present) {
        cc = BSN_subfield(s, 19+date_offs, 2);
        if (cc > 14)
            BSN_RET1("Chip number (cc) should not exceed 14");
        if (!cc)
            BSN_RET1("Chip number (cc) can't be zero");
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
    if (*endp) {
        printf("Invalid GUID syntax (low) (%s)\n", &str[8]);
        return false;
    }
    str[8] = '\0';
    h = strtoul(&str[0], &endp, 16);
    if (*endp) {
        printf("Invalid GUID syntax (high) (%s)\n", str);
        return false;
    }
    guid->h = h;
    guid->l = l;
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
        printf("%s image - insane GUID pointer (%08x)\n", pref, *ind);
        return false;
    }
    *nguids = buf[*ind/4 - 3];
    TOCPU1(*nguids);
    *nguids /= 2;

    // More sanity check
    if (*nguids > GUIDS) {
        printf("%s image - insane number of GUIDs (%d)\n", pref, *nguids);
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

    memcpy(&ps->vsd[0], vsd, VSD_LEN);

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


////////////////////////////////////////////////////////////////////////
//Note that vsd1 is a string of bytes.
bool Operations::patchVSD(FImage& f, char *vsd1, char *curr_psid, const char* new_psid)
{
    char       vsd[VSD_LEN];

    PS *ps = (PS*)(f.getBuf() + f.get_sector_size()/4);

    char flash_psid[sizeof(ps->psid) + 1];
    char image_psid[sizeof(ps->psid) + 1];

    // Form new VSD
    memset(vsd, 0, VSD_LEN);
    memset(flash_psid, 0 , sizeof(flash_psid));
    memset(image_psid, 0 , sizeof(image_psid));


    if (vsd1)
        strncpy(&vsd[0], vsd1, VSD_OFFS);


    if (new_psid == NULL) {
        // New psid is not explicitly given - take it from image
        memcpy(image_psid, (char*)ps->psid, sizeof(ps->psid));


        // psid is kept in flash byte-swapped.
        // decode it to string
        u_int32_t *qp = (u_int32_t *)&image_psid[0];
        for (u_int32_t i=0; i < sizeof(ps->psid)/4; i++) {
            *qp = bswap_32(*qp);
            qp++;
        }

    } else {
        strncpy(image_psid, new_psid, sizeof(ps->psid));
    }


    if (strncmp( image_psid, (char*) curr_psid, sizeof(ps->psid))) {

        // Copy the strings to a local buffer to assure '\0' termination (for printf) 
        strncpy(flash_psid, curr_psid,sizeof(ps->psid));

        printf("\n    You are about to replace current PSID in flash - \"%s\" with a different PSID - \"%s\".\n", flash_psid, image_psid);

        if (! ask_user("\n    Is it OK ? (y/n) [n] : "))
            return false;
    }

    // Copy correct PSID to image.
    strncpy(&vsd[VSD_OFFS], image_psid, VSD_LAST);

    //vsd is kept in flash byte-swapped.
    //recode it back before patching
    u_int32_t *qp = (u_int32_t *)&vsd[0];
    for (int i=0; i<VSD_LEN/4; i++) {
        *qp = bswap_32(*qp);
        qp++;
    }

    _patchVSD(f, f.get_sector_size(), vsd);      // Primary PS
    _patchVSD(f, f.get_sector_size()*2, vsd);    // Secondary PS
    return true;
} // pathVSD


////////////////////////////////////////////////////////////////////////
bool Operations::patchGUIDs(FImage& f, guid_t guids[GUIDS], bool interactive)
{
    guid_t       old_guids[GUIDS];
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
    if (interactive) {
        bool old_guids_fmt = nguid1 < GUIDS;
        for (int i=0; i<GUIDS; i++) {
            u_int32_t h = buf[ind1/4 + i*2];
            TOCPU1(h);
            u_int32_t l = buf[ind1/4 + i*2 + 1];
            TOCPU1(l);
            old_guids[i].h = h;
            old_guids[i].l = l;
        }
        if (old_guids_fmt)
            printf("    Old image!!!! Only %d GUIDs may be set.\n", nguid1);

        printf("    Old GUIDs (inside image) are:\n");
        printf("        Node:      " GUID_FORMAT "\n", old_guids[0].h,old_guids[0].l);
        printf("        Port1:     " GUID_FORMAT "\n", old_guids[1].h,old_guids[1].l);
	if (_num_ports > 1) 
	    printf("        Port2:     " GUID_FORMAT "\n", old_guids[2].h,old_guids[2].l);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", old_guids[3].h,old_guids[3].l);
        printf("\n    You are about to change them to following GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", guids[0].h,guids[0].l);
        printf("        Port1:     " GUID_FORMAT "\n", guids[1].h,guids[1].l);
	if (_num_ports > 1) 
	    printf("        Port2:     " GUID_FORMAT "\n", guids[2].h,guids[2].l);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", guids[3].h,guids[3].l);

        if (!ask_user("\n    Is it OK ? (y/n) [n] : "))
            return false;
    }

    // Path GUIDs section
    if (ind1) 
        patchGUIDsSection(buf, ind1, guids, nguid1);
    if (ind2)
        patchGUIDsSection(buf, ind2, guids, nguid2);

    if (!interactive) {
        bool old_guids_fmt = nguid1 < GUIDS;
        printf("\n    Burn image with the following GUIDs:\n");
        printf("        Node:      " GUID_FORMAT "\n", guids[0].h,guids[0].l);
        printf("        Port1:     " GUID_FORMAT "\n", guids[1].h,guids[1].l);
	if (_num_ports > 1) 
	    printf("        Port2:     " GUID_FORMAT "\n", guids[2].h,guids[2].l);
        if (!old_guids_fmt)
            printf("        Sys.Image: " GUID_FORMAT "\n", guids[3].h,guids[3].l);
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
bool Operations::RevisionInfo(FBase& f, 
                              guid_t guids_out[GUIDS], 
                              char *vsd_out,
                              bool *fs_image, 
                              bool internal_call,
                              bool read_guids, 
                              bool read_ps)
{
    char      *im_type;
    u_int32_t prim_ptr, scnd_ptr, ps_start=0;
    u_int32_t signature;
    u_int32_t im_start = 0;

    READ4(f, 0x24, &signature, "Signature");
    TOCPU1(signature);
    _silent = true;
    if (signature == SIGNATURE) {
        // Full image
        report("\nFailsafe image:\n\n");
        if (checkPS(f, f.get_sector_size(), prim_ptr, "Primary  ")) {
            im_start = prim_ptr;
            ps_start = f.get_sector_size();
        } else if (checkPS(f, f.get_sector_size() * 2, scnd_ptr, "Secondary")) {
            im_start = scnd_ptr;
            ps_start = f.get_sector_size() * 2;
        } else {
            _silent = internal_call;
            report("No valid image found.\n");
            return false;
        }
        im_type = "FailSafe";
        *fs_image = true;
    } else {
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
    u_int32_t guid_ptr, nguids;
    guid_t guids[GUIDS];

    if (read_guids) {
        READ4(f, im_start + 0x24, &guid_ptr, "GUID PTR");
        TOCPU1(guid_ptr);
        guid_ptr += im_start;
        if (guid_ptr >= f.get_size()) {
            report("Insane GUID pointer (%08x)\n", guid_ptr);
            return false;
        }
        READ4(f, guid_ptr - 3*sizeof(u_int32_t), &nguids, "Number of GUIDs");
        TOCPU1(nguids);
        if (nguids > GUIDS*2) {
            report("Insane Number of GUIDs (%d)\n", nguids);
            return false;
        }
        READBUF(f, guid_ptr, guids, nguids / 2 * sizeof(u_int64_t), "GUIDS");
        TOCPUBY64(guids);
        memcpy(&guids_out[0], &guids[0], sizeof(guids));

    }

    report("Image type: %s\n"
           "Chip rev.:  %X\n",
           im_type, fw_id);

    if (read_guids) {
	report("GUID Des:   Node             Port1            ");
	if (_num_ports > 1)
	    report("Port2            ");
	report( "Sys image\n");

        report("GUIDs:      ");
        for (u_int32_t i=0; i<nguids/2; i++)
	    if (i != 2 || _num_ports > 1 ) 
		report(GUID_FORMAT " ", guids[i].h,guids[i].l);
    }

    if (*fs_image && read_ps) {
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
    } else
        report("\n");

    return true;
} // RevisionInfo

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
        printf("*** ERROR *** Can't open %s: %s\n", device,  strerror(errno));
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
    "    -clear_semaphore   - Force clear of the flash semaphore on the device.\n"
    "                         This flag should come BEFORE the -d[evice] flag in the command line.\n"
    "                         No command is allowed when this flag is used.\n"
    "                         NOTE: Using this flag may result in an unstable behavior and flash image\n"
    "                               corruption if the device or another flash application is currently\n"
    "                               using the flash. Handle with care.\n"
    "\n"
    "    -h[elp]            - Prints this message and exits\n"
    "    -hh                - Prints extended command help\n"
    "\n"
    "    -i[mage] <image>   - Binary image file.\n"
    "                         Commands affected: burn, verify\n"
    "\n"
    "    -nofs              - Burn image not in failsafe manner.\n"
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
    "    -use_image_ps      - Burn vsd as appears in the given image - don't keep existing vsd on flash.\n"
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
    "    q[uery]  - Query misc. flash/FW characteristics\n"
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
    "    Command:\n"
    "        wbne\n"
    "    Parameters:\n"
    "        addr - address of block\n"
    "        size - size of data to write in bytes\n"
    "        data - data to write - space seperated dwords\n"
    "    Example:\n"
    "        " FLINT_NAME " -d " DEV_MST_EXAMPLE1 " wbne 0x10000 12 0x30000 0x76800 0x5a445a44\n"
    "\n"
    "* Print (to screen or to a file) the firmware configuration text file used by the image generation process.\n"
    "  This command would fail if the image does not contain a FW configuration section. Existence of this\n"
    "  section depends on the version of the image generation tool.\n"
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
    bool         clear_semaphore  = false;
    bool         silent           = false; 
    bool         guids_specified  = false; 
    bool         burn_failsafe    = true;
    bool         use_image_ps     = false;
    bool         single_image_burn = true;

    char         *vsd1=0;
    char         *psid=0;
    guid_t       guids[Operations::GUIDS];
    char         vsds[VSD_LEN];
    int		 rc = 0;

    auto_ptr<Flash>       f;

    Operations            ops;

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
            if (!strncmp(av[i], "-dual_image", 10))
                single_image_burn = false;

	    else if (!strcmp(av[i], "-clear_semaphore")) {
                clear_semaphore = true;
	    }

            else if (!strncmp(av[i], "-d", 2)) {
                NEXTS("-device");
                device = av[i];

                //f.reset( get_flash(device) );
                u_int32_t num_ports;
                auto_ptr<Flash>       tmp( get_flash(device, num_ports));
		f = tmp;
				
                if (f.get() == NULL) {
                    printf("*** ERROR *** Can't get flash type using device %s\n", device);
                    rc =  1; goto done; 
                }

                ops.SetNumPorts(num_ports);

                g_flash = f.get();
                if (!f->open(device, clear_semaphore)) {
                    printf("*** ERROR *** Can't open %s: %s\n", device, f->err());
                    rc =  1; goto done; 
                }
            } else if (!strcmp(av[i], "-v") || !strcmp(av[i], "-vv")) {
                printf("%s: Version %s .",
                       av[0],
                       _versionID);

                if (!strcmp(av[i], "-vv")) {
                    printf(" CVS %s", _cvsID + 1); 
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
                vsd1 = av[i];
            }
            // -vsd1 is an alias to -vsd, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd1")) {
                NEXTS("-vsd1");
                vsd1 = av[i];
            } else if (!strcmp(av[i], "-psid")) {
                NEXTS("-psid");
                psid = av[i];
            }
            // -vsd2 is an alias to psid, for backward compatibility. Can be removed in the future.
            else if (!strcmp(av[i], "-vsd2")) {
                NEXTS("-vsd2");
                psid = av[i];
            } else if (!strcmp(av[i], "-bsn")) {
                NEXTS("-bsn");
                GETBSN(av[i], &guids[0]);
                for (int i=1; i<Operations::GUIDS; i++) {
                    u_int64_t g=guids[0].h;
                    g=(g<<32) | guids[0].l;
                    g += i;
                    guids[i].h = (u_int32_t)(g>>32);
                    guids[i].l = (u_int32_t)g;
                }
                guids_specified = true;
            } else if (!strncmp(av[i], "-i", 2)) {
                NEXTS("-image");
                image_fname = av[i];
            } else if (!strcmp(av[i], "-guid")) {
                NEXTS("-guid");
                GETGUID(av[i], &guids[0]);
                for (int i=1; i<Operations::GUIDS; i++) {
                    u_int64_t g=guids[0].h;
                    g=(g<<32) | guids[0].l;
                    g += i;
                    guids[i].h = (u_int32_t)(g>>32);
                    guids[i].l = (u_int32_t)g;
                }
                guids_specified = true;
            } else if (!strcmp(av[i], "-guids")) {
                NEXTS("-guids");
                for (int j=0; j<Operations::GUIDS; j++) {
                    GETGUID(av[i], &guids[j]);
                    if (++i >= ac) {
                        printf("Exactly four GUIDs must be specified.\n");
                        rc =  1; goto done; 
                    }
                }
                i--;
                guids_specified = true;
            } else if (!strncmp(av[i], "-s", 2))
                silent = true;
            else if (!strncmp(av[i], "-use_image_ps", 2))
                use_image_ps = true;
            else if (!strncmp(av[i], "-nofs", 5))
                burn_failsafe = false;
            else if (!strncmp(av[i], "-y", 2))
                _assume_yes = true;

            else if (!strncmp(av[i], "-hh", 3) ||  !strncmp(av[i], "--hh", 4)) {
                usage(av[0], true);
                rc =  1; goto done; 
            } else if (!strncmp(av[i], "-h", 2) ||  !strncmp(av[i], "--h", 3)) {
                usage(av[0]);
                rc =  1; goto done; 
            } else {
                printf("Invalid switch \"%s\" is specified.\n", av[i]);
                rc =  1; goto done; 
            }
        } else {
            //
            // Commands
            // --------
            //

	    if (clear_semaphore) {
		printf("No command is allowed when -clear_semaphore flag is given.\n");  
                rc =  1; goto done; 
	    }

            if (*av[i] == 'b') {
                //
                // BURN
                //

                bool burn_block = false;
                if (!strcmp(av[i], "bb")) {
                    burn_block = true;
                }

                // Device
                if (!device) {
                    printf("For %s command \"-device\" switch must be specified.\n", av[i]);
                    rc =  1; goto done; 
                }

                // Image - check, open and verify
                if (!image_fname) {
                    printf("For %s command \"-image\" switch must be specified.\n", av[i]);
                    rc =  1; goto done; 
                }
                FImage         fim;
                if (!fim.open(image_fname)) {
                    printf("*** ERROR *** Image file open failed: %s\n", fim.err());
                    rc =  1; goto done; 
                }

                if (!burn_block) {
                    // Make checks and replace vsd/guids.
                   
                    bool old_silent = _silent;
                    _silent = true;
                    if (!ops.Verify(fim)) {
                        printf("Not a valid image\n");
                        rc =  1; goto done; 
                    }
                    
                    // Check that the flash sector size is well defined in the image
                    if (fim.get_sector_size() && (fim.get_sector_size() != f->get_sector_size())) {
                        printf("Flash sector size(0x%x) differs from sector size defined in image (0x%x)\n",
                               f->get_sector_size(),
                               fim.get_sector_size());
                        rc =  1; goto done; 
                    }
                    
                    // Get GUID and VSD info from flash
                    memset(vsds, 0, VSD_LEN);
                    
                    bool read_guids = true;
                    bool read_ps    = true;
                    
                    if (guids_specified)
                        read_guids = false;
                    
                    if ((vsd1 && psid) || use_image_ps)
                        read_ps = false;
                    
                    if (read_guids || read_ps) {
                        if (!ops.RevisionInfo(*f, guids, vsds, &fs_image, false, read_guids, read_ps )) {
                            printf("*** ERROR *** Can't extract ");
                            if (read_guids) {
                                printf("GUIDS ");
                            }
                            if (read_ps) {
                                if (read_guids) 
                                    printf("and ");
                                
                                printf("VSD/PSID ");
                            }
                            printf("info from flash. ");
                            printf("Please specify the missing info (using command line flags -guid(s) , -use_image_ps). ");
                            
                            if (burn_failsafe) {
                                printf("Can't burn in a failsafe mode. Please use \"-nofs\" flag to burn in a none failsafe mode..\n");
                            }
                            rc =  1; goto done;
                        }
                    }
                    

                    // Patch GUIDS
                    if (guids_specified) {
                        if (!ops.patchGUIDs(fim, guids, isatty(0) != 0)) {
                            rc =  1; goto done;
                        }
                    } else {
                        if (!ops.patchGUIDs(fim, guids, false)) {
                            rc =  1; goto done;
                        }
                    }

                    // Patch VSD
                    if (vsd1)
                        strncpy(&vsds[0], vsd1, VSD_OFFS);
                    //if (psid)
                    //    strncpy(&vsds[VSD_OFFS], psid, VSD_LAST);
                    if (_image_is_full && !use_image_ps)
                        if (!ops.patchVSD(fim, &vsds[0], &vsds[VSD_OFFS], psid)) {
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
                        printf("*** ERROR *** Failsafe burn failed: FW Image on flash is short.\n");
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
			    printf("*** ERROR *** Failsafe burn failed: %s\n", ops.err());
			    printf("It is impossible to burn this image in a failsafe mode.\n");
			    printf("If you want to burn in non failsafe mode, use the \"-nofs\" switch.\n");
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
                    printf("Burn process will not be failsafe. No checks are performed.\n");
                    printf("ALL flash, including Invariant Sector will be overwritten.\n");
                    printf("If this process fails computer may remain in unoperatable state.\n");

                    if (!ask_user("\nAre you sure ? (y/n) [n] : ")) {
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
            } else if (*av[i] == 'e') {
                //
                // ERASE SECTOR <ADDR>
                //     Parameters: <ADDR>
                //
                u_int32_t    addr;
                char         *endp;

                // Device
                if (!device) {
                    printf("For erase command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

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
            } else if (*av[i] == 'q') {
                // QUERY
                if (device) {
		    if (!ops.RevisionInfo(*f, guids, 0, &fs_image)) {
			printf("*** ERROR *** Flash query (through device %s) failed.\n", device);
                        rc =  1; goto done;
		    }
		} else if (image_fname) {
                    FImage         fim;
                    if (!fim.open(image_fname)) {
                        printf("*** ERROR *** Image file open failed. %s\n", fim.err());
                        rc =  1; goto done; 
                    }
		    if (!ops.RevisionInfo(fim, guids, 0, &fs_image)) {
			printf("*** ERROR *** Query image file %s failed.\n", image_fname);
                        rc =  1; goto done;
		    }
                } else {
                    printf("For query command \"-device\" or \"-image\" switch must be specified.\n");
                    rc =  1; goto done; 
                }
            } else if (!strcmp(av[i], "rb")) {
                // READ BLOCK
                //     Parameters:  <ADDR> <LENGTH> [OUT_FILENAME]
                //     if OUT_FILENAME is given, binari read block is stored
                //     in the given file. Otherwise, data is printed to screen.
                u_int32_t    addr, length;
                u_int8_t     *data;
                char         *endp;

                bool         to_file = false;


                FImage       fim;
                FBase*       target;

                // Device
                if (device) {
                    target = f.get();
                } else if (image_fname) {
                    if (!fim.open(image_fname)) {
                        printf("*** ERROR *** Image file open failed. %s\n", fim.err());
                        rc =  1; goto done; 
                    }
                    target = &fim;
                } else {
                    printf("For rb command \"-device\" or \"-image\" switch must be specified.\n");
                    rc =  1; goto done;
                }

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
                int fd = -1;

                if (i + 2 == ac)
                    to_file = true;

                if (to_file) {
                    NEXTC("<OUT_FILENAME>", "rb");
                    if ((fd = open(av[i], O_WRONLY | O_CREAT | O_BINARY, 0666)) < 0) {
                        fprintf(stderr, "Can't open ");
                        perror(av[i]);
                        rc =  1; goto done; 
                    }
                    if (ftruncate(fd, 0) < 0) {
                        fprintf(stderr, "Can't truncate ");
                        perror(av[i]);
                        rc =  1; goto done; 
                    }
                }

                // Read flash
                if (!target->read(addr, data, length)) {
                    printf("*** ERROR *** Flash read failed: %s\n", target->err());
                    rc =  1; goto done; 
                }

                if (to_file) {
                    // Write output
                    if (write(fd, data, length) != (int)length) {
                        perror("Write error");
                        rc =  1; goto done; 
                    }
                    close(fd);
                } else {
                    for (u_int32_t i = 0; i < length ; i+=4) {
                        u_int32_t word = *((u_int32_t*)(data + i));

                        word  = __be32_to_cpu(word);
                        printf("0x%08x ", word);  
                    }
                    printf("\n");
                }
                delete [] data;
            } else if (!strcmp(av[i], "rw")) {
                // READ DWORD <ADDR>
                //     Parameters: <ADDR>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device) {
                    printf("For rw command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

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
            } else if (*av[i] == 'v') {
                // VERIFY
                if (device)
                    ops.Verify(*f);
                else if (image_fname) {
                    FImage         fim;
                    if (!fim.open(image_fname)) {
                        printf("*** ERROR *** Image file open failed: %s\n", fim.err());
                        rc =  1; goto done; 
                    }
                    ops.Verify(fim);
                } else {
                    printf("For verify command \"-device\" or \"-image\" switch must be specified.\n");
                    rc =  1; goto done; 
                }
           
            } else if (!strcmp(av[i], "dc")) {
                // Dump conf
                _silent = true;

                char* conf_file = NULL;
                if (i + 2 <= ac) {
                    NEXTC("<OUT_FILENAME>", "dc");
                    conf_file = av[i];
                }

                if (device)
                    ops.Verify(*f);
                else if (image_fname) {
                    FImage         fim;
                    if (!fim.open(image_fname)) {
                        printf("*** ERROR *** Image file open failed: %s\n", fim.err());
                        rc =  1; goto done; 
                    }
                    ops.Verify(fim);
                } else {
                    printf("For verify command \"-device\" or \"-image\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

                if(!ops.DumpConf(conf_file)) {
                    printf("*** ERROR *** Failed dumping FW configuration: %s\n", ops.err());
                    rc =  1; goto done; 
                }

            } else if (!strcmp(av[i], "ri")) {
                // Dump conf
                _silent = true;

                char* img_file = NULL;
                NEXTC("<OUT_FILENAME>", "ri");
                img_file = av[i];

                if (device) {
                    ops.Verify(*f);
                } else {
                    printf("For ri command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

                //printf("Last addr: 0x%08x\n", ops._last_image_addr);

                u_int32_t length = ops._last_image_addr;
                u_int8_t* data = new u_int8_t[length];


                int fd = -1;

                if ((fd = open(av[i], O_WRONLY | O_CREAT | O_BINARY, 0666)) < 0) {
                    fprintf(stderr, "Can't open ");
                    perror(av[i]);
                    rc =  1; goto done; 
                }
                if (ftruncate(fd, 0) < 0) {
                    fprintf(stderr, "Can't truncate ");
                    perror(av[i]);
                    rc =  1; goto done; 
                }

                // Read flash
                if (!f->read(0, data, length)) {
                    printf("*** ERROR *** Flash read failed: %s\n", f->err());
                    rc =  1; goto done; 
                }

                // Write output
                if (write(fd, data, length) != (int)length) {
                    perror("Write error");
                    rc =  1; goto done; 
                }
                close(fd);

                delete [] data;

            } else if (!strcmp(av[i], "wb")) {
                // WRITE BLOCK
                //     Parameters:  <IN_FILENAME> <ADDR>
                u_int32_t    addr, length;
                u_int8_t     *data;
                char         *endp;

                // Device
                if (!device) {
                    printf("For wb command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

                // Input file
                int         fd;
                struct stat statbuf;
                NEXTC("<IN_FILENAME>", "wb");
                if ((fd = ::open(av[i], O_RDONLY | O_BINARY), 0) < 0) {
                    fprintf(stderr, "Can't open ");
                    perror(av[i]);
                    rc =  1; goto done; 
                }
                if (fstat(fd, &statbuf) < 0) {
                    fprintf(stderr, "Can't stat ");
                    perror(av[i]);
                    rc =  1; goto done; 
                }
                length = statbuf.st_size;
                data = new u_int8_t[length];

                // Address
                NEXTC("<ADDR>", "wb");
                addr = strtoul(av[i], &endp, 0);
                if (*endp) {
                    printf("Invalid address \"%s\"\n", av[i]);
                    rc =  1; goto done; 
                }

                // Read file
                if (read(fd, data, length) != (int)length) {
                    perror("Read error");
                    rc =  1; goto done; 
                }

                // Write flash
                if (!ops.write_image(*f, addr, data, length, !silent)) {
                    printf("*** ERROR *** Flash write failed: %s\n", ops.err());
                    rc =  1; goto done; 
                }

                close(fd);
                delete [] data;
            } else if (!strcmp(av[i], "ww")) {
                // WRITE DWORD
                //     Parameters: <ADDR> <DATA>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device) {
                    printf("For ww command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

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
            } else if (!strcmp(av[i], "wbne")) {
                // WRITE DWORD WITHOUT ERASE
                //     Parameters: <ADDR> <SIZE> <DATA>
                u_int32_t    size, addr;
                char         *endp;

                // Device
                if (!device) {
                    printf("For wbne command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

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
            } else if (!strcmp(av[i], "wwne")) {
                // WRITE DWORD WITHOUT ERASE
                //     Parameters: <ADDR> <DATA>
                u_int32_t    data, addr;
                char         *endp;

                // Device
                if (!device) {
                    printf("For wwne command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

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
            } else if (!strcmp(av[i], "cfi")) {
                // CFI (COMMON FLASH INTERFACE) QUERY


                // Device
                if (!device) {
                    printf("For cfi command \"-device\" switch must be specified.\n");
                    rc =  1; goto done; 
                }

                if (!f->print_cfi_info()) {
                    printf("*** ERROR *** Cfi query failed: %s\n", f->err());
                    rc =  1; goto done; 
                }
            } else {
                printf("Invalid command \"%s\".\n", av[i]);
                rc =  1; goto done; 
            }
        }
    }

done:
 
    //mask signals   
    for (i = 0 ; i < (int)(sizeof(g_signals_for_termination)/sizeof(g_signals_for_termination[0])) ; i++ ) {
        signal (g_signals_for_termination[i], SIG_IGN);    
    }

    return rc;
}
