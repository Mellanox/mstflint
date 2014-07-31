/*
 *
 * flint_io.h - FLash INTerface
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: flint_io.h 7522 2011-11-16 15:37:21Z mohammad $
 *
 */
#ifndef FLINT_IO_H
#define FLINT_IO_H

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

#include "flint_base.h"
#include <mflash.h>
#include <mft_sig_handler.h>

// external flash attr struct

#define IO_MAX_BANKS_NUM 4

typedef struct ext_flash_attr {
    u_int8_t banks_num;
    u_int32_t hw_dev_id;
    u_int32_t rev_id;
    char*   type_str; // NULL if not available
    u_int32_t size;
    u_int32_t sector_size;
    int block_write;
    int command_set;
    u_int8_t quad_en_support;
    u_int8_t dummy_cycles_support;

    u_int8_t quad_en;
    MfError mf_get_quad_en_rc;

    u_int8_t dummy_cycles;
    MfError mf_get_dummy_cycles_rc;

    u_int8_t write_protect_support;

    write_protect_info_t protect_info_array[IO_MAX_BANKS_NUM];
    MfError mf_get_write_protect_rc_array[IO_MAX_BANKS_NUM];

} ext_flash_attr_t;

// Common base class for Flash and for FImage
class MLXFWOP_API FBase : public ErrMsg {
public:
    FBase(bool is_flash) :
    _is_image_in_odd_chunks(false),
    _log2_chunk_size(0),
    _is_flash(is_flash),
    _advErrors(true) {}
    virtual ~FBase()  {}

    virtual bool open(const char *, bool, bool)                  {return false;}
    virtual void close()                                   = 0;
    virtual bool read(u_int32_t addr, u_int32_t *data)     = 0;
    virtual bool read(u_int32_t addr, void *data, int len,
                      bool verbose=false,
                      const char* message = "")            = 0;

    virtual u_int32_t get_sector_size()                    = 0;
    virtual u_int32_t get_size()                           = 0;

    virtual u_int32_t get_dev_id()                         = 0;
    virtual u_int32_t get_rev_id()                         = 0;
    Crc16&            get_image_crc() {return _image_crc;};
    bool              is_flash() {return _is_flash;};

    bool read_phy (u_int32_t phy_addr, void* data, int len);
    bool read_phy (u_int32_t phy_addr, u_int32_t* data);

    virtual void set_address_convertor(u_int32_t log2_chunk_size, bool is_image_in_odd_chunks) {
        _log2_chunk_size = log2_chunk_size;
        _is_image_in_odd_chunks = is_image_in_odd_chunks;
    }
    virtual u_int32_t get_phys_from_cont     (u_int32_t cont_addr, u_int32_t log2_chunk_size, bool is_image_in_odd_chunks) {
        u_int32_t phys_addr;
        u_int32_t log2_chunk_size_bak = _log2_chunk_size;
        bool is_image_in_odd_chunks_bak = _is_image_in_odd_chunks;

        set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
        phys_addr = cont2phys(cont_addr);
        set_address_convertor(log2_chunk_size_bak, is_image_in_odd_chunks_bak);
        return phys_addr;
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
    Crc16      _image_crc;
    const bool _is_flash;
    // show advanced error msgs
    bool _advErrors;

};




// Flash image (R/W)
class MLXFWOP_API FImage : public FBase {
public:
    FImage() :
    FBase(false),
    _buf(0),
    _len(0) {}
    virtual ~FImage() { close();}

    u_int32_t    *getBuf()      { return _buf;}
    u_int32_t    getBufLength() { return _len;}
    virtual bool open(const char *fname, bool read_only = false, bool advErr = true);
    using FBase::open;
    bool open(u_int32_t *buf, u_int32_t len, bool advErr = true);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t *data);
    virtual bool read(u_int32_t addr, void *data, int len, bool verbose=false, const char* message= "");

    virtual u_int32_t get_sector_size();
    virtual u_int32_t get_size()     { return  getBufLength();}
    virtual u_int32_t get_dev_id()   { return  0;}
    virtual u_int32_t get_rev_id()   { return  0;}
private:
    u_int32_t *_buf;
    u_int32_t _len;
};




//
// Flash access (R/W)
//




class MLXFWOP_API Flash : public FBase {
public:
    Flash() :
    FBase(true),
    _mfl(NULL),
    _no_flash_verify(false),
    _ignore_cache_replacement(false),
    _curr_sector(0xffffffff),
    _port_num(0),
    _cr_space_locked(0)
    {
        memset(&_attr, 0, sizeof(_attr));
    }

    virtual ~Flash()  { close();};

    // FBase Interface

    virtual bool open          (const char *device,
                                bool force_lock  = false,
                                bool read_only   = false,
                                int num_of_banks = 4,
                                flash_params_t *flash_params = (flash_params_t *)NULL,
                                int ignoe_cache_replacement = 0,
                                bool advErr = true);
    using FBase::open;

    bool open          (uefi_Dev_t *uefi_dev,
                        f_fw_cmd fw_cmd_func,
                        bool force_lock = false,
                        bool advErr = true);

    virtual void close         ();

    virtual bool read          (u_int32_t addr,
                                u_int32_t *data);

    virtual bool read          (u_int32_t addr,
                                void*     data,
                                int       len,
                                bool      verbose = false,
                                const char* message = "");
    bool write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase = false);
    bool write_phy(u_int32_t phy_addr, u_int32_t data);
    bool erase_sector_phy  (u_int32_t phy_addr);

    bool         update_boot_addr (u_int32_t boot_addr)
                                  {return mf_update_boot_addr(_mfl, boot_addr) == MFE_OK;}
    //
    // Flash Interface
    //

    u_int32_t get_sector_size        ()  {return _attr.sector_size;}
    u_int32_t get_size               ()  {return _attr.size;}

    u_int32_t get_dev_id             ()  {return _attr.hw_dev_id; }
    u_int32_t get_rev_id             ()  {return _attr.rev_id; }
    u_int32_t get_port_num           ()  {return _port_num;}
    u_int8_t  get_cr_space_locked    ()  {return _cr_space_locked;}
    bool  get_ignore_cache_replacment()  {return _cr_space_locked;}

    bool sw_reset();

    bool set_no_flash_verify(bool val);
    static void get_flash_list(char *flash_list) {return mf_flash_list(flash_list);}

    // Write and Erase functions are performed by the Command Set

    virtual bool erase_sector  (u_int32_t addr);

    virtual bool write         (u_int32_t addr,
                                void*     data,
                                int       cnt,
                                bool      noerase = false);

    virtual bool write         (u_int32_t addr,
                                u_int32_t data);

    virtual bool enable_hw_access(u_int64_t key);

    virtual bool disable_hw_access();

    const char* getFlashType();

    bool         get_attr(ext_flash_attr_t& attr);

    bool         set_attr(char *param_name,
                          char *param_val_str);

    bool is_flash_write_protected();
    static void  deal_with_signal();

    enum {
        TRANS = 4096
    };

    bool open_com_checks(const char *device,
                         int rc,
                         bool force_lock);

//needed for printing flash status in flint hw query cmd
#define QUAD_EN_PARAM "QuadEn"
#define DUMMY_CYCLES_PARAM "DummyCycles"
#define FLASH_NAME "Flash"
#define WRITE_PROTECT "WriteProtected"
#define WP_TOP_STR "Top"
#define WP_BOTTOM_STR "Bottom"
#define WP_SEC_STR "Sectors"
#define WP_SUBSEC_STR "SubSectors"
#define WP_DISABLED_STR "Disabled"

#ifndef _MSC_VER
protected:
#endif
    bool write_sector_with_erase(u_int32_t addr, void *data, int cnt);
    bool write_with_erase(u_int32_t addr, void *data, int cnt);


    mflash*    _mfl;
    flash_attr _attr;
    bool _no_flash_verify;
    bool _ignore_cache_replacement; // for FS3 devices flash access.

    u_int32_t  _curr_sector;
    u_int32_t  _port_num;
    u_int8_t   _cr_space_locked;
};

#endif
