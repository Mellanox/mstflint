/*
 *
 * flint_io.cpp - FLash INTerface
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
 *  Version: $Id: flint_io.cpp 7522 2011-11-16 15:37:21Z mohammad $
 *
 */


#include "flint_io.h"


extern bool _no_erase;
extern bool _no_burn;

extern const char* g_sectNames[];

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
        return errmsg("Can not open file \"%s\" - %s", fname, strerror(errno));
    }

    // Get the file size:
    if (fseek(fh, 0, SEEK_END) < 0) {
        fclose(fh);
        return errmsg("Can not get file size for \"%s\" - %s", fname, strerror(errno));
    }

    fsize = ftell(fh);
    if (fsize < 0) {
        fclose(fh);
        return errmsg("Can not get file size for \"%s\" - %s", fname, strerror(errno));
    }
    rewind(fh);

    //printf("-D- %s size is %d\n", fname, fsize);
    if (fsize & 0x3) {
        fclose(fh);
        return errmsg("Image size should be 4-bytes aligned. Make sure file %s is in the right format (binary image)",
                      fname);
    }

    _buf = new u_int32_t[fsize/4];
    if ((r_cnt = fread(_buf, 1, fsize, fh)) != fsize) {
        fclose(fh);
        if (r_cnt < 0) {
            return errmsg("Read error on file \"%s\" - %s",fname, strerror(errno));
        } else {
            return errmsg("Read error on file \"%s\" - read only %d bytes (from %ld)",
                          fname, r_cnt, (unsigned long)fsize);
        }
    }

    _len = fsize;
    fclose(fh);

    return true;
} // FImage::open

bool FImage::open(u_int32_t *buf, u_int32_t len)
{
    _buf = new u_int32_t[len / 4];
    memcpy(_buf, buf, len);
    _len = len;
    return true;
}
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
bool FImage::read(u_int32_t addr, void *data, int len, bool, const char*)
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
        return errmsg("Reading 0x%x bytes from %s address 0x%x is out of image limits (0x%x bytes)",
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
bool Flash::_no_flash_verify = false;

////////////////////////////////////////////////////////////////////////
bool Flash::open(const char *device, bool force_lock, bool read_only, int num_of_banks, flash_params_t *flash_params,
        int ignore_cashe_replacement)
{
    // Open device
    int rc;
    read_only = false;

    rc = mf_open(&_mfl, device, num_of_banks, flash_params, ignore_cashe_replacement);

    if ((rc == MFE_SEM_LOCKED) && force_lock) {
        report("Warning: Taking flash lock even though semaphore is set.\n");
        rc = mf_open_ignore_lock(_mfl);
    }

    if (rc != MFE_OK) {
        if (rc == MFE_SEM_LOCKED) {
            return errmsg("Can not obtain Flash semaphore (63). You can run \"flint -clear_semaphore -d <device>\" to force semaphore unlock. See help for details.");
        }
        if (rc == MFE_LOCKED_CRSPACE) {
            _cr_space_locked = 1;
            return errmsg("HW access is disabled on the device.\n-E- Run \"flint -d %s hw_access enable\" in order to enable HW access.", device);
        }
        if (rc == MFE_REG_ACCESS_MAD_NOT_SUPPORTED) {
            return errmsg("The target device FW does not support flash access commands.\n-E- Please use the -override_cache_replacement option in order to access the flash directly.");
        }
        if (rc == MFE_DIRECT_FW_ACCESS_DISABLED) {
            return errmsg(" Flash cache replacement is active.\n-E- Please use the -override_cache_replacement option in order to access the flash directly.");
        }

        return errmsg("%s %s", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
    }

    rc = mf_get_attr(_mfl, &_attr);
    if (rc != MFE_OK) {
        return errmsg("Failed getting flash attributes for device %s: %s", device,  mf_err2str(rc));
    }

    if (_attr.hw_dev_id == 435 || _attr.hw_dev_id == SWITCHX_HW_ID) {
        _port_num = 0;
    } else if (_attr.hw_dev_id == 25204 || _attr.hw_dev_id == 24204) {
        _port_num = 1;
    } else {
        _port_num = 2;
    }

    if (_byte_mode) {
        rc = mf_set_opt(_mfl, MFO_AMD_BYTE_MODE, 1);
        if (rc != MFE_OK) {
            return errmsg("Failed setting byte mode for device %s: %s", device,  mf_err2str(rc));
        }
    }
    if (_no_flash_verify) {
        rc = mf_set_opt(_mfl, MFO_NO_VERIFY, 1);
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
    // printf("-D- read1: addr = %#x, phys_addr = %#x\n", addr, phys_addr);
    rc = mf_read(_mfl, phys_addr, 4, (u_int8_t*)data);
    if (rc != MFE_OK) {
        return errmsg("Flash read failed at address %s0x%x : %s",
                      _log2_chunk_size ? "physical " : "",
                      addr,
                      mf_err2str(rc));
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, void *data, int len, bool verbose, const char* message)
{
    int rc;
    u_int32_t  perc = 0xffffffff;

    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }
    if (len & 0x3) {
        return errmsg("Length should be 4-bytes aligned.");
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
            // printf("-D- write: addr = %#x, phys_addr = %#x\n", chunk_addr, phys_addr);

            rc = mf_read(_mfl, phys_addr, chunk_size, ((u_int8_t*)data) + chunk_addr - addr);
            if (rc != MFE_OK) {
                return errmsg("Flash read failed at address %s0x%x : %s",
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
                    printf("\r%s%%%03d", message, new_perc);
                    fflush(stdout);

                    perc = new_perc;
                }
            }
        }
    }
    // Report
    if (verbose) {
        printf("\r%s%%100", message);
        fflush(stdout);
    }

    return true;
} // Flash::read
#define DISABLE_CONVERTOR(log2_chunk_size_bak, is_image_in_odd_chunks_bak) {\
    log2_chunk_size_bak = _log2_chunk_size;\
    is_image_in_odd_chunks_bak = _is_image_in_odd_chunks;\
    set_address_convertor(0, 0);\
}

#define NATIVE_PHY_ADDR_FUNC(func, arg) {\
	bool ret = true;\
	u_int32_t log2_chunk_size_bak, is_image_in_odd_chunks_bak;\
	DISABLE_CONVERTOR(log2_chunk_size_bak, is_image_in_odd_chunks_bak);\
	ret = func arg;\
	set_address_convertor(log2_chunk_size_bak, is_image_in_odd_chunks_bak);\
	return ret;\
}
bool FBase::read_phy (u_int32_t phy_addr, u_int32_t* data)
{
    NATIVE_PHY_ADDR_FUNC(read, (phy_addr, data));
}

bool FBase::read_phy (u_int32_t phy_addr, void* data, int len)
{
    NATIVE_PHY_ADDR_FUNC(read, (phy_addr, data, len));
}

bool Flash::write_phy(u_int32_t phy_addr, u_int32_t data)
{
    NATIVE_PHY_ADDR_FUNC(write, (phy_addr, data));
}

bool Flash::write_phy(u_int32_t phy_addr, void* data, int cnt, bool noerase)
{
    NATIVE_PHY_ADDR_FUNC(write, (phy_addr, data, cnt, noerase));
}

bool Flash::erase_sector_phy  (u_int32_t phy_addr)
{
    NATIVE_PHY_ADDR_FUNC(erase_sector, (phy_addr));
}



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
                     "Trying to write %d bytes to address 0x%x, which exceeds max image size (0x%x - half of total flash size).",
                     cnt,
                     addr,
                     get_size() / 2);
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
        // printf("-D- write: addr = %#x, phys_addr = %#x\n", chunk_addr, phys_addr);
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
        if (rc == MFE_REG_ACCESS_RESOURCE_NOT_AVAILABLE) {
            return errmsg("Flash erase of address 0x%x failed: %s\n"
                          "    This may indicate that a FW image was already updated on flash, but not loaded by the device.\n"
                          "    Please load FW on the device (reset device or restart driver) before burning a new FW.",
                          phys_addr,
                          mf_err2str(rc));
        } else {
            return errmsg("Flash erase of address 0x%x failed: %s",
                          phys_addr,
                          mf_err2str(rc));
        }
    }

    return true;
}

bool Flash::enable_hw_access(u_int64_t key)
{
    int rc;
    rc = mf_enable_hw_access(_mfl, key);

    if (rc != MFE_OK) {
        return errmsg("Enable HW access failed: %s", mf_err2str(rc));
    }
    return true;
}

bool Flash::disable_hw_access(void)
{
    int rc;
    rc = mf_disable_hw_access(_mfl);

    if (rc != MFE_OK) {
        return errmsg("Disable HW access failed: %s", mf_err2str(rc));
    }
    return true;

}

bool Flash::sw_reset() {
    if (_attr.hw_dev_id != 435 && _attr.hw_dev_id != SWITCHX_HW_ID) {
        return errmsg("operation supported only for InfiniScale4 switch and SwitchX over IB interface");
    }
    int rc = mf_sw_reset(_mfl);
    if (rc != MFE_OK) {
        return errmsg("%s (%s)", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
    }
    return true;
}


#define QUAD_EN_PARAM "QuadEn"
#define FLASH_NAME "Flash"
#define WRITE_PROTECT "WriteProtected"
#define WP_TOP_STR "Top"
#define WP_BOTTOM_STR "Bottom"
#define WP_SEC_STR "Sectors"
#define WP_SUBSEC_STR "SubSectors"
#define WP_DISABLED_STR "Disabled"


bool Flash::print_attr() {
    u_int8_t banks_num = _attr.banks_num;
    int rc;
    printf("HW Info:\n");
    printf("  HwDevId               %d\n",     _attr.hw_dev_id);
    printf("  HwRevId               0x%x\n",   _attr.rev_id);

    printf("Flash Info:\n");
    if (_attr.type_str != NULL) {
        // we don't print the flash type in old devices
        printf("  Type                  %s\n",     _attr.type_str);
    }
    printf("  TotalSize             0x%x\n",   _attr.size);
    printf("  Banks                 0x%x\n",   banks_num);
    printf("  SectorSize            0x%x\n",   _attr.sector_size );
    printf("  WriteBlockSize        0x%x\n",   _attr.block_write);
    printf("  CmdSet                0x%x\n",   _attr.command_set);

    // Quad EN query
    if (_attr.quad_en_support) {
        u_int8_t quad_en;
        rc = mf_get_quad_en(_mfl, &quad_en);
        switch (rc) {
            case MFE_OK:
                printf("  "QUAD_EN_PARAM"                %d\n", quad_en);
                break;
            case MFE_MISMATCH_QUAD_EN:
                printf("-E- There is a mismatch in the "QUAD_EN_PARAM" attribute between the flashes attached to the device\n");
                break;
            case MFE_NOT_SUPPORTED_OPERATION:
                break;
            default:
                return errmsg("Failed to get "QUAD_EN_PARAM" attribute: %s (%s)", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
        }
    }

    // Flash write protected info query
    if (_attr.write_protect_support) {
        int bank;
        for (bank = 0; bank < banks_num; bank++) {
            write_protect_info_t protect_info;
            rc = mf_get_write_protect(_mfl, bank, &protect_info);
            if (rc == MFE_OK) {
                printf("  "FLASH_NAME"%d."WRITE_PROTECT"   ", bank);
                if (protect_info.sectors_num != 0) {
                    printf("%s,", (protect_info.is_bottom ? WP_BOTTOM_STR : WP_TOP_STR));
                    printf("%d-", protect_info.sectors_num);
                    printf("%s\n", (protect_info.is_subsector ? WP_SUBSEC_STR : WP_SEC_STR));
                } else {
                    printf(WP_DISABLED_STR"\n");

                }
            } else {
                if (rc != MFE_NOT_SUPPORTED_OPERATION) { // We ignore the read when operation is not supported!
                    return errmsg("Failed to get write_protected info: %s (%s)", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
                }
            }

       }
    }

    // TODO: Print new

    return true;
}

#define GET_IN_PARAM(param_in, out, first_op, second_op) {\
    if (!strcmp(param_in, first_op)) {\
        out = 1;\
    } else if (!strcmp(param_in, second_op)) {\
        out = 0;\
    } else {\
        return errmsg("bad argument (%s) it can be "first_op" or " second_op"", param_in);\
    }\
}
bool  Flash::set_attr(char *param_name, char *param_val_str)
{
    int rc;

    if (!strcmp(param_name, QUAD_EN_PARAM)) {
        char* endp;
        u_int8_t quad_en_val;
        quad_en_val = strtoul(param_val_str, &endp, 0);
        if (*endp != '\0' || quad_en_val > 1) {
            return errmsg("Bad "QUAD_EN_PARAM" value (%s), it can be 0 or 1\n", param_val_str);
        }
        rc = mf_set_quad_en(_mfl, quad_en_val);
        if (rc != MFE_OK) {
            return errmsg("Setting "QUAD_EN_PARAM" failed: (%s)", mf_err2str(rc));
        }
    } else if (strstr(param_name, FLASH_NAME) == param_name) {
        char *flash_param, *param_str, *endp, *bank_num_str;
        u_int8_t bank_num;
        flash_param = strtok(param_name, ".");
        param_str   = strtok(NULL, ".");
        bank_num_str = flash_param + strlen(FLASH_NAME);
        bank_num = strtoul(bank_num_str, &endp, 0);
        if (*endp != '\0') {
            return errmsg("bad number of flash bank (%s), it should be integer!.", bank_num_str);
        }
        if (!strcmp(param_str, WRITE_PROTECT)) {
            write_protect_info_t protect_info;
            char *tb, *num_str, *sec;

            if (!strcmp(param_val_str, WP_DISABLED_STR)) {
                memset(&protect_info, 0, sizeof(protect_info));
            } else {
                tb = strtok(param_val_str, ",");
                num_str = strtok(NULL, "-");
                sec = strtok(NULL, "");
                if (tb == NULL || num_str == NULL || sec == NULL) {
                    return errmsg("missing parameters for setting the "WRITE_PROTECT" attribute, see help for more info.");
                }
                GET_IN_PARAM(tb, protect_info.is_bottom, WP_BOTTOM_STR, WP_TOP_STR);
                GET_IN_PARAM(sec, protect_info.is_subsector, WP_SUBSEC_STR, WP_SEC_STR);

                protect_info.sectors_num = strtoul(num_str, &endp, 0);
                if (*endp != '\0') {
                    return errmsg("bad argument (%s), only integer value is allowed.", num_str);
                }
           }
            rc = mf_set_write_protect(_mfl, bank_num, &protect_info);
            if (rc != MFE_OK) {
                return errmsg("Setting "WRITE_PROTECT" failed: (%s)", mf_err2str(rc));
            }
        } else {
            return errmsg("Unknown attribute %s.%s", flash_param, param_str);
        }


    } else {
        return errmsg("Unknown attribute %s", param_name);
    }

    return true;
}
