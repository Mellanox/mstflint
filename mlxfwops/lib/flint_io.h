/*
 *
 * flint_io.h - FLash INTerface
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

#ifndef UEFI_BUILD
#include <mft_sig_handler.h>
#endif

#include <string>

// external flash attr struct

#define IO_MAX_BANKS_NUM 4

typedef struct ext_flash_attr
{
    u_int8_t banks_num;
    u_int32_t hw_dev_id;
    u_int32_t rev_id;
    char* type_str; // NULL if not available
    u_int32_t jedec_id;
    u_int32_t size;
    u_int32_t sector_size; // minimal sec
    int block_write;
    int command_set;
    u_int8_t cmp_support;
    u_int8_t quad_en_support;
    u_int8_t srp_support;
    u_int8_t srwd_support;
    u_int8_t driver_strength_support;
    u_int8_t dummy_cycles_support;

    u_int8_t series_code_support;
    MacronixSeriesCode series_code;

    u_int8_t cmp;
    MfError mf_get_cmp_rc;

    u_int8_t quad_en;
    MfError mf_get_quad_en_rc;

    u_int8_t srwd;
    MfError mf_get_srwd_rc;

    u_int8_t srp;
    MfError mf_get_srp_rc;

    u_int8_t driver_strength;
    MfError mf_get_driver_strength_rc;

    u_int8_t dummy_cycles;
    MfError mf_get_dummy_cycles_rc;

    u_int8_t write_protect_support;

    write_protect_info_t protect_info_array[IO_MAX_BANKS_NUM];
    MfError mf_get_write_protect_rc_array[IO_MAX_BANKS_NUM];

} ext_flash_attr_t;

// Common base class for Flash and for FImage
class MLXFWOP_API FBase : public FlintErrMsg
{
public:
    enum
    {
        Fwm_Default = 0,
        Fwm_4KB = 1,
        Fwm_64KB = 2
    };

    FBase(bool is_flash) : _is_image_in_odd_chunks(false), _log2_chunk_size(0), _is_flash(is_flash), _advErrors(true) {}
    virtual ~FBase() {}

    virtual bool
      open(uefi_Dev_t* uefi_dev, uefi_dev_extra_t* uefi_extra, bool force_lock = false, bool advErr = true) = 0;

    virtual bool open(const char*, bool, bool) = 0;

    virtual bool open(const char* device, bool, bool, int, flash_params_t*, int, bool, int) = 0;

    virtual bool is_fifth_gen() = 0;
    virtual void close() = 0;
    virtual bool read(u_int32_t addr, u_int32_t* data) = 0;
    virtual bool read(u_int32_t addr, void* data, int len, bool verbose = false, const char* message = "") = 0;
    virtual bool read_modify_write(u_int32_t phy_addr, void* data, int cnt, bool noerase = false) = 0;

    virtual bool read_modify_write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase = false) = 0;

    virtual bool write(u_int32_t addr, void* data, int cnt) { return write(addr, data, cnt, false); }
    virtual bool write(u_int32_t addr, void* data, int cnt, bool noerase) = 0;

    virtual bool write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase = false) = 0;

    virtual bool write(u_int32_t addr, u_int32_t data) = 0;
    virtual bool set_flash_working_mode(int mode = FBase::Fwm_Default) = 0;
    virtual bool set_flash_utilization(bool, int) = 0;
    virtual int get_flash_working_mode() = 0;

    virtual bool set_no_flash_verify(bool) = 0;

    virtual u_int32_t get_sector_size() = 0;
    virtual u_int32_t get_size() = 0;
    virtual u_int32_t get_effective_size() = 0;

    virtual u_int32_t get_dev_id() = 0;
    virtual u_int32_t get_rev_id() = 0;

    virtual mfile* getMfileObj() = 0;
    virtual mflash* getMflashObj() = 0;
    virtual bool erase_sector(u_int32_t addr) = 0;
    virtual BinIdT get_bin_id() { return UNKNOWN_BIN; };
    Crc16& get_image_crc() { return _image_crc; };
    bool is_flash() { return _is_flash; };

    bool read_phy(u_int32_t phy_addr, void* data, int len);
    bool read_phy(u_int32_t phy_addr, u_int32_t* data);

    virtual void set_address_convertor(u_int32_t log2_chunk_size, bool is_image_in_odd_chunks)
    {
        _log2_chunk_size = log2_chunk_size;
        _is_image_in_odd_chunks = is_image_in_odd_chunks;
    }
    virtual u_int32_t get_phys_from_cont(u_int32_t cont_addr, u_int32_t log2_chunk_size, bool is_image_in_odd_chunks)
    {
        u_int32_t phys_addr;
        u_int32_t log2_chunk_size_bak = _log2_chunk_size;
        bool is_image_in_odd_chunks_bak = _is_image_in_odd_chunks;

        set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
        phys_addr = cont2phys(cont_addr);
        set_address_convertor(log2_chunk_size_bak, is_image_in_odd_chunks_bak);
        return phys_addr;
    }

    u_int32_t get_log2_chunk_size() { return _log2_chunk_size; }
    bool get_is_image_in_odd_chunks() { return _is_image_in_odd_chunks; }

    enum
    {
        MAX_FLASH = 4 * 1048576
    };

protected:
    // Address translation functions for ConnectX.
    // Translate between contiguous "logical" addresses

    // If Failsafe zebra mapping is enabled:

    // Result is concatenation of:
    // The lower log2_chunk_size bits of the cons_addr
    // The is_image_in_odd_chunk bit
    // The remaining upper bits of the cons_addr

    u_int32_t cont2phys(u_int32_t cont_addr)
    {
        u_int32_t result;
        if (_log2_chunk_size)
        {
            result = (cont_addr & (0xffffffff >> (32 - _log2_chunk_size))) |
                     (_is_image_in_odd_chunks << _log2_chunk_size) |
                     ((cont_addr << 1) & (0xffffffff << (_log2_chunk_size + 1)));
        }
        else
        {
            result = cont_addr;
        }
        return result;
    }

    u_int32_t phys2cont(u_int32_t phys_addr)
    {
        u_int32_t result;
        if (_log2_chunk_size)
        {
            result = (phys_addr & (0xffffffff >> (32 - _log2_chunk_size))) |
                     ((phys_addr >> 1) & (0xffffffff << (_log2_chunk_size)));
        }
        else
        {
            result = phys_addr;
        }
        return result;
    }

    bool readWriteCommCheck(u_int32_t addr, int len)
    {
        if (addr & 0x3)
        {
            return errmsg("Address should be 4-bytes aligned.");
        }
        if (len & 0x3)
        {
            return errmsg("Length should be 4-bytes aligned.");
        }
        return true;
    }

    void check_uefi_build()
    {
#ifndef UEFI_BUILD
        throw;
#else
        return;
#endif
    }

    bool _is_image_in_odd_chunks;
    u_int32_t _log2_chunk_size;
    Crc16 _image_crc;
    const bool _is_flash;
    // show advanced error msgs
    bool _advErrors;
};

// Flash image (R/W)
class MLXFWOP_API FImage : public FBase
{
public:
    FImage() : FBase(false), _fname(0), _isFile(false), _len(0), _buf() {}
    virtual ~FImage() { close(); }

    u_int32_t* getBuf();
    u_int32_t getBufLength() { return _len; }
    virtual bool open(const char* fname, bool read_only = false, bool advErr = true);
    using FBase::open;
    bool open(u_int32_t* buf, u_int32_t len, bool advErr = true);
    virtual void close();
    virtual bool read(u_int32_t addr, u_int32_t* data);
    virtual bool read(u_int32_t addr, void* data, int len, bool verbose = false, const char* message = "");
    virtual bool write(u_int32_t addr, void* data, int cnt);
    virtual bool write(u_int32_t, void*, int, bool)
    {
        check_uefi_build();
        return false;
    }
    virtual bool write(u_int32_t, u_int32_t)
    {
        check_uefi_build();
        return false;
    }
    virtual bool erase_sector(u_int32_t)
    {
        check_uefi_build();
        return false;
    }
    virtual bool open(uefi_Dev_t*, uefi_dev_extra_t*, bool, bool)
    {
        check_uefi_build();
        return false;
    }
    virtual bool open(const char*, bool, bool, int, flash_params_t*, int, bool, int)
    {
        check_uefi_build();
        return false;
    }
    virtual bool read_modify_write_phy(u_int32_t, void*, int, bool)
    {
        check_uefi_build();
        return false;
    }
    virtual bool read_modify_write(u_int32_t, void*, int, bool = false)
    {
        check_uefi_build();
        return false;
    }
    virtual bool set_flash_working_mode(int)
    {
        check_uefi_build();
        return false;
    }
    virtual bool set_flash_utilization(bool, int)
    {
        check_uefi_build();
        return false;
    }
    virtual bool write_phy(u_int32_t, void*, int, bool)
    {
        check_uefi_build();
        return false;
    }
    virtual bool set_no_flash_verify(bool)
    {
        check_uefi_build();
        return false;
    }
    virtual int get_flash_working_mode()
    {
        check_uefi_build();
        return -1;
    }
    virtual u_int32_t get_sector_size();
    virtual u_int32_t get_size() { return getBufLength(); }
    virtual u_int32_t get_effective_size() { return get_size(); }
    virtual u_int32_t get_dev_id() { return 0; }
    virtual u_int32_t get_rev_id() { return 0; }
    virtual mfile* getMfileObj()
    {
        check_uefi_build();
        return (mfile*)NULL;
    }
    virtual mflash* getMflashObj()
    {
        check_uefi_build();
        return (mflash*)NULL;
    }
    virtual bool is_fifth_gen() { return false; }

protected:
    const char* _fname;
    bool _isFile;
    u_int32_t _len;
private:
    bool readFileGetBuffer(std::vector<u_int8_t>& dataBuf);
    bool writeEntireFile(std::vector<u_int8_t>& fileContent);
    bool getFileSize(int& fileSize);
    std::vector<u_int8_t> _buf;
};

class MLXFWOP_API FPldm : public FImage
{
public:
    FPldm() : FImage() {}
    virtual ~FPldm() { close(); }
    virtual bool open(const char* fname, bool read_only, bool advErr);
    virtual const char* get_fname() { return _fname; }
};

//
// Flash access (R/W)
//

class MLXFWOP_API Flash : public FBase
{
public:
    Flash() :
        FBase(true),
        _mfl((mflash*)NULL),
        _no_flash_verify(false),
        _ignore_cache_replacement(false),
        _curr_sector(0xffffffff),
        _curr_sector_size(0),
        _port_num(0),
        _cr_space_locked(0),
        _flash_working_mode(FBase::Fwm_Default),
        _cputUtilizationApplied(false),
        _cpuPercent(-1)
    {
        memset(&_attr, 0, sizeof(_attr));
    }

    virtual ~Flash() { close(); };

    // FBase Interface

    virtual bool open(const char* device,
                      bool force_lock = false,
                      bool read_only = false,
                      int num_of_banks = 4,
                      flash_params_t* flash_params = (flash_params_t*)NULL,
                      int ignoe_cache_replacement = 0,
                      bool advErr = true,
                      int cx3_fw_access = 0);
    using FBase::open;

    virtual bool open(uefi_Dev_t* uefi_dev, uefi_dev_extra_t* uefi_extra, bool force_lock = false, bool advErr = true);

    virtual bool open(const char*, bool, bool)
    {
#ifndef UEFI_BUILD
        throw;
#else
        return false;
#endif
    }

    virtual void close();

    virtual bool read(u_int32_t addr, u_int32_t* data);

    virtual bool read(u_int32_t addr, void* data, int len, bool verbose = false, const char* message = "");
    virtual bool write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase = false); // read modify write
    virtual bool read_modify_write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase = false); // read modify
                                                                                                       // write
    bool write_phy(u_int32_t phy_addr, u_int32_t data); // read modify write
    bool erase_sector_phy(u_int32_t phy_addr);

    bool update_boot_addr(u_int32_t boot_addr) { return mf_update_boot_addr(_mfl, boot_addr) == MFE_OK; }
    //
    // Flash Interface
    //

    u_int32_t get_current_sector_size() { return _curr_sector_size; }
    u_int32_t get_sector_size() { return _attr.sector_size; }
    virtual u_int32_t get_size() { return _attr.size; }
    virtual u_int32_t get_effective_size();

    virtual u_int32_t get_dev_id() { return _attr.hw_dev_id; }
    u_int32_t get_rev_id() { return _attr.rev_id; }
    BinIdT get_bin_id() { return _attr.bin_id; };
    u_int32_t get_port_num() { return _port_num; }
    u_int8_t get_cr_space_locked() { return _cr_space_locked; }
    bool get_ignore_cache_replacment() { return _ignore_cache_replacement; }

    virtual bool set_no_flash_verify(bool val);
    static void get_flash_list(char* flash_list, int buffer_size) { return mf_flash_list(flash_list, buffer_size); }

    // Write and Erase functions are performed by the Command Set

    virtual bool erase_sector(u_int32_t addr);

    virtual bool write(u_int32_t addr, void* data, int cnt, bool noerase = false);

    virtual bool read_modify_write(u_int32_t phy_addr, void* data, int cnt, bool noerase = false);

    virtual bool write(u_int32_t addr, u_int32_t data);

    virtual bool enable_hw_access(u_int64_t key);

    virtual bool disable_hw_access();

    bool disable_hw_access(u_int64_t key);
    virtual bool is_fifth_gen();
    const char* getFlashType();

    bool get_attr(ext_flash_attr_t& attr);

    bool set_attr(char* param_name, char* param_val_str, const ext_flash_attr_t& attr);
    bool validate_write_protect_args(char* param_val, const ext_flash_attr_t& attr, u_int8_t bank_num);
    bool check_and_set_sector_field(std::string& param_val_str,
                                    std::size_t sector_or_subsector_start_loc,
                                    std::string& sector_or_subsecto,
                                    std::string& err_msg);
    bool check_and_set_sector_num_field(std::string& param_val_str,
                                        std::string& sector_num,
                                        std::string& err_msg,
                                        std::size_t sector_or_subsector_start_loc,
                                        std::size_t tbs_end_loc);
    bool check_and_set_tbs_field(std::string& param_val_str,
                                 std::size_t tbs_end_loc,
                                 std::string& tbs,
                                 std::string& err_msg,
                                 const ext_flash_attr_t& attr,
                                 u_int8_t bank_num);
    bool get_data_for_protect_info(const ext_flash_attr_t& attr,
                                   u_int8_t bank_num,
                                   char* param_val,
                                   std::string& tbs,
                                   std::string& sector_num,
                                   std::string& sector_or_subsector);
    bool set_data_in_protect_info(std::string& tbs,
                                  std::string& sector_num,
                                  std::string& sector_or_subsector,
                                  const ext_flash_attr_t& attr,
                                  u_int8_t bank_num,
                                  write_protect_info_t* protect_info);
    bool handle_protect_info_set_for_write_protect(char* param_val_str,
                                                   const ext_flash_attr_t& attr,
                                                   write_protect_info_t* protect_info,
                                                   u_int8_t bank_num);

    bool flash_working_mode_supported() { return _attr.support_sub_and_sector; }
    virtual int get_flash_working_mode() { return _flash_working_mode; }
    virtual bool set_flash_working_mode(int mode = FBase::Fwm_Default);
    virtual bool set_flash_utilization(bool, int);
    bool is_flash_write_protected();
    bool disable_flash_write_protection_if_required(); // if the protection is from the top, no disable is needed
    bool check_and_disable_flash_wp_if_required();
    bool backup_write_protect_info(write_protect_info_backup_t& protect_info_backup);
    bool restore_write_protect_info(write_protect_info_backup_t& protect_info_backup);
    static void deal_with_signal();

    mfile* getMfileObj() { return mf_get_mfile(_mfl); }
    mflash* getMflashObj() { return _mfl; }

    enum
    {
        TRANS = 4096
    };

    bool open_com_checks(const char* device, int rc, bool force_lock);

// needed for printing flash status in flint hw query cmd
#define CMP_PARAM "CMP"
#define QUAD_EN_PARAM "QuadEn"
#define SRWD_PARAM "SRWD"
#define SRP_PARAM "SRP"
#define DRIVER_STRENGTH_PARAM "DriverStrength"
#define DUMMY_CYCLES_PARAM "DummyCycles"
#define SERIES_CODE_PARAM "SeriesCode"
#define FLASH_NAME "Flash"
#define WRITE_PROTECT "WriteProtected"
#define WP_TOP_STR "Top"
#define WP_BOTTOM_STR "Bottom"
#define WP_SEC_STR "Sectors"
#define WP_SUBSEC_STR "SubSectors"
#define WP_DISABLED_STR "Disabled"

protected:
    bool write_sector_with_erase(u_int32_t addr, void* data, int cnt);
    bool write_with_erase(u_int32_t addr, void* data, int cnt);

    mflash* _mfl;
    flash_attr _attr;
    bool _no_flash_verify;
    bool _ignore_cache_replacement; // for FS3 devices flash access.

    u_int32_t _curr_sector;
    u_int32_t _curr_sector_size; // can work with both 4KB and 64KB sectors
    u_int32_t _port_num;
    u_int8_t _cr_space_locked;
    int _flash_working_mode;
    bool _cputUtilizationApplied;
    int _cpuPercent;
};

#endif
