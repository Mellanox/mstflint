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

#include <errno.h>
#include "flint_io.h"


extern bool _no_erase;
extern bool _no_burn;

extern const char *g_sectNames[];

#ifdef UEFI_BUILD
// no signal handling.
void mft_signal_set_handling(int isOn)
{
    return;
}
#endif

////////////////////////////////////////////////////////////////////////
//
// FImage Class Implementation
//
////////////////////////////////////////////////////////////////////////

bool FImage::open(const char *fname, bool read_only, bool advErr)
{

#ifndef UEFI_BUILD
    int fsize;
    FILE              *fh;

    (void)read_only;  // FImage can be opened only for read so we ignore compiler warnings
    _advErrors = advErr;

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

    _fname = fname;
    _len = fsize;
    _isFile = true;
    fclose(fh);
    return true;
#else
    return false;
#endif
} // FImage::open

bool FImage::open(u_int32_t *buf, u_int32_t len, bool advErr)
{
    _buf.resize(len);
    memcpy(_buf.data(), buf, len);
    _len = len;
    _advErrors = advErr;
    return true;
}
////////////////////////////////////////////////////////////////////////
void FImage::close()
{
    _fname = (const char*)NULL;
    _buf.resize(0);
    _len = 0;
    _isFile = false;
} // FImage::close

/////////////////////////////////////////////////////////////////////////
u_int32_t* FImage::getBuf()
{
    if (_isFile) {
        // Read the entire file on demand
        FILE *fh = fopen(_fname, "rb");
        int r_cnt;
        u_int32_t *retBuf;
        if (!fh) {
            errmsg("Can not open file \"%s\" - %s", _fname, strerror(errno));
            return (u_int32_t*)NULL;
        }
        _buf.resize(_len);
        if ((r_cnt = fread(_buf.data(), 1, _len, fh)) != (int)_len) {
            if (r_cnt < 0) {
                errmsg("Read error on file \"%s\" - %s", _fname, strerror(errno));
                retBuf = (u_int32_t*)NULL;
                goto cleanup;
            } else {
                errmsg("Read error on file \"%s\" - read only %d bytes (from %ld)",
                       _fname, r_cnt, (unsigned long)_len);
                retBuf = (u_int32_t*)NULL;
                goto cleanup;
            }
        }
        _isFile = false;
        retBuf = (u_int32_t*)_buf.data();
cleanup:
        fclose(fh);
        return retBuf;
    } else {
        return (u_int32_t*)_buf.data();
    }
}

////////////////////////////////////////////////////////////////////////
bool FImage::read(u_int32_t addr, u_int32_t *data)
{
    return read(addr, data, 4);
} // FImage::read

////////////////////////////////////////////////////////////////////////
bool FImage::read(u_int32_t addr, void *data, int len, bool verbose, const char *message)
{
    (void)verbose;
    (void) message;

    if (!readWriteCommCheck(addr, len)) {
        return false;
    }

    if (!_isFile && _buf.size() == 0) {
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
    align.Init(addr, len);
    while (align.GetNextChunk(chunk_addr, chunk_size)) {
        u_int32_t phys_addr = cont2phys(chunk_addr);
        if (_isFile) {
            FILE *fh = fopen(_fname, "rb");
            if (!fh) {
                return errmsg("Can not open file \"%s\" - %s", _fname, strerror(errno));
            }
            if (fseek(fh, phys_addr, SEEK_SET) != 0) {
                fclose(fh);
                return errmsg("Failed to read from FW file, offset: %#x - %s", phys_addr, strerror(errno));
            }
            if (fread((u_int8_t*)data + (chunk_addr - addr), chunk_size, 1, fh) != 1) {
                fclose(fh);
                return errmsg("Failed to read from FW file, offset: %#x - %s", phys_addr, strerror(errno));
            }
            fclose(fh);
        } else {
            memcpy((u_int8_t*)data + (chunk_addr - addr),
                   _buf.data() +  phys_addr,
                   chunk_size);
        }
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

bool FImage::readFileGetBuffer(std::vector<u_int8_t>& dataBuf)
{
    int fileSize;
    FILE *fh;

    if (!getFileSize(fileSize)) {
        return false;
    }
    dataBuf.resize(fileSize);
    if ((fh = fopen(_fname, "rb")) == NULL) {
        return errmsg("Can not open %s: %s\n", _fname, strerror(errno));
    }

    if (fread(dataBuf.data(), 1, fileSize, fh) != (size_t)fileSize) {
        dataBuf.resize(0);
        fclose(fh);
        return errmsg("Failed to read entire file %s: %s\n", _fname, strerror(errno));
    }
    fclose(fh);
    return true;
}
bool FImage::writeEntireFile(std::vector<u_int8_t>& fileContent)
{
    FILE *fh;
    if ((fh = fopen(_fname, "wb")) == (FILE*)NULL) {
        return errmsg("Can not open %s: %s\n", _fname, strerror(errno));
    }

    if (fwrite(fileContent.data(), 1, fileContent.size(), fh) != fileContent.size()) {
        fclose(fh);
        return errmsg("Failed to write entire file %s: %s\n", _fname, strerror(errno));
    }
    fclose(fh);
    return true;
}

bool FImage::getFileSize(int& fileSize)
{
    FILE *fh;
    if ((fh = fopen(_fname, "rb")) == NULL) {
        return errmsg("Can not open %s: %s\n", _fname, strerror(errno));
    }

    if (fseek(fh, 0, SEEK_END) < 0) {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", _fname, strerror(errno));
    }
    fileSize = ftell(fh);
    fclose(fh);
    if (fileSize < 0) {
        return errmsg("Failed to get size of the file \"%s\": %s\n", _fname, strerror(errno));
    }
    return true;
}

bool FImage::write(u_int32_t addr, void *data, int cnt)
{
    if (!_isFile) {
        if (_buf.size() < addr + cnt) {
            _buf.resize(addr + cnt);
        }

        memcpy(&_buf[addr], data, cnt);
        return true;
    }

    if (!readWriteCommCheck(addr, 0)) {
        return false;
    }
    // read entire file
    std::vector<u_int8_t> dataVec;
    if (!readFileGetBuffer(dataVec)) {
        return false;
    }
    // modify content (extend if needed)
    if ((dataVec.size() < addr + cnt) ) {
        dataVec.resize(addr + cnt);
    }
    memcpy(&dataVec[addr], data, cnt);
    // re-write the file
    if (!writeEntireFile(dataVec)) {
        return false;
    }
    _len = dataVec.size();
    return true;
}

////////////////////////////////////////////////////////////////////////
//
// Flash Class Implementation
//
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
bool Flash::open_com_checks(const char *device, int rc, bool force_lock)
{
    if ((rc == MFE_SEM_LOCKED) && force_lock) {
        report("Warning: Taking flash lock even though semaphore is set.\n");
        rc = mf_open_ignore_lock(_mfl);
    }

    if (rc != MFE_OK) {
        if (rc == MFE_SEM_LOCKED) {
            return errmsgAdv(_advErrors, "Can not obtain Flash semaphore.", "You can run \"flint -clear_semaphore -d <device>\" to force semaphore unlock. See help for details.");
        }
        if (rc == MFE_LOCKED_CRSPACE) {
            _cr_space_locked = 1;
            return errmsgAdv(_advErrors, "HW access is disabled on the device.", "\n-E- Run \"flint -d %s hw_access enable [key]\" in order to enable HW access.", device);
        }
        if (rc == MFE_REG_ACCESS_NOT_SUPPORTED) {
            return errmsgAdv(_advErrors, "The target device FW does not support flash access commands.", "\n-E- Please use the -override_cache_replacement option in order to access the flash directly.");
        }
        if (rc == MFE_DIRECT_FW_ACCESS_DISABLED) {
            return errmsgAdv(_advErrors, "Flash cache replacement is active.", "\n-E- Please use the -override_cache_replacement option in order to access the flash directly.");
        }

        return errmsg("%s%s%s", errno == 0 ? "" : strerror(errno),  errno == 0 ? "" : ". ", mf_err2str(rc));
    }

    rc = mf_get_attr(_mfl, &_attr);
    if (rc != MFE_OK) {
        return errmsg("Failed getting flash attributes for device %s: %s", device,  mf_err2str(rc));
    }
    _curr_sector_size = _attr.sector_size;

    rc = mf_set_opt(_mfl, MFO_NO_VERIFY, _no_flash_verify ? 1 : 0);
    if (rc != MFE_OK) {
        return errmsg("Failed setting no flash verify on device: %s", mf_err2str(rc));
    }


    if (_attr.hw_dev_id == IS4_HW_ID || _attr.hw_dev_id == SWITCHX_HW_ID) {
        _port_num = 0;
    } else {
        _port_num = 2;
    }
    return true;
}

bool Flash::set_no_flash_verify(bool val)
{
    int rc;
    if (_mfl) {
        rc = mf_set_opt(_mfl, MFO_NO_VERIFY, val ? 1 : 0);
        if (rc != MFE_OK) {
            return errmsg("Failed setting no flash verify on device: %s", mf_err2str(rc));
        }
    }
    _no_flash_verify = val;
    return true;
}

// Flash::open


////////////////////////////////////////////////////////////////////////
bool Flash::open(const char *device, bool force_lock, bool read_only, int num_of_banks, flash_params_t *flash_params,
                 int ignore_cashe_replacement, bool advErr, int cx3_fw_access)
{
    // Open device
    int rc;
    _advErrors = advErr;
    _ignore_cache_replacement = ignore_cashe_replacement ? true : false;
    (void)read_only; // not used , avoid compiler warnings TODO: remove this var from function def
    rc = mf_open_adv(&_mfl, device, num_of_banks, flash_params, ignore_cashe_replacement, cx3_fw_access);
    //printf("device: %s , forceLock: %s , read only: %s, num of banks: %d, flash params is null: %s, ocr: %d, rc: %d\n",
    //		device, force_lock? "true":"false", read_only?"true":"false", num_of_banks, flash_params? "no":"yes", ignore_cashe_replacement, rc);
    return open_com_checks(device, rc, force_lock);
}

////////////////////////////////////////////////////////////////////////
bool Flash::open(uefi_Dev_t *uefi_dev, uefi_dev_extra_t *uefi_extra, bool force_lock, bool advErr)
{
    int rc;
    _advErrors = advErr;
    rc = mf_open_uefi(&_mfl, uefi_dev, uefi_extra);
    return open_com_checks("uefi", rc, force_lock);
}


////////////////////////////////////////////////////////////////////////
void Flash::close()
{
    if (!_mfl) {
        return;
    }

    mf_close(_mfl);
    _mfl = 0;
} // Flash::close

bool Flash::read(u_int32_t addr,
                 u_int32_t *data)
{
    int rc;

    u_int32_t phys_addr = cont2phys(addr);
    // printf("-D- read1: addr = %#x, phys_addr = %#x\n", addr, phys_addr);
    // here we set a "silent" signal handler and deal with the received signal after the read
    mft_signal_set_handling(1);
    rc = mf_read(_mfl, phys_addr, 4, (u_int8_t*)data, false);
    deal_with_signal();
    if (rc != MFE_OK) {
        return errmsg("Flash read failed at address %s0x%x : %s",
                      _log2_chunk_size ? "physical " : "",
                      addr,
                      mf_err2str(rc));
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
bool Flash::read(u_int32_t addr, void *data, int len, bool verbose, const char *message)
{
    int rc;
    if (!readWriteCommCheck(addr, len)) {
        return false;
    }
    if (verbose) {
        printf("\33[2K\r");//clear the current line
    }
    // Much better perf for read in a single chunk. need to work on progress report though.
    bool read_in_single_chunk = true;

    if (read_in_single_chunk) {
        u_int32_t chunk_addr;
        u_int32_t chunk_size;

        Aligner align(_log2_chunk_size);
        align.Init(addr, len);
        while (align.GetNextChunk(chunk_addr, chunk_size)) {
            u_int32_t phys_addr = cont2phys(chunk_addr);
            // printf("-D- write: addr = %#x, phys_addr = %#x\n", chunk_addr, phys_addr);
            mft_signal_set_handling(1);
            rc = mf_read(_mfl, phys_addr, chunk_size, ((u_int8_t*)data) + chunk_addr - addr, verbose);
            deal_with_signal();
            if (rc != MFE_OK) {
                return errmsg("Flash read failed at address %s0x%x : %s",
                              _log2_chunk_size ? "physical " : "",
                              chunk_addr,
                              mf_err2str(rc));
            }
        }

    } else {
        u_int32_t perc = 0xffffffff;
        u_int32_t *p = (u_int32_t*)data;
        for (int i = 0; i < len / 4; i++) {
            if (!read(addr, p++)) {
                return false;
            }

            addr += 4;

            // Report
            if (verbose) {
                u_int32_t new_perc = (i * 100) / len;
                if (new_perc != perc) {
                    printf("\33[2K\r");//clear the current line
                    printf("\r%s%d%c", message, new_perc, '%');
                    fflush(stdout);

                    perc = new_perc;
                }
            }
        }
    }

    // Report
    if (verbose) {
        printf("\33[2K\r");//clear the current line
        printf("Done.");
        fflush(stdout);
    }

    return true;
} // Flash::read
#define DISABLE_CONVERTOR(log2_chunk_size_bak, is_image_in_odd_chunks_bak) { \
        log2_chunk_size_bak = _log2_chunk_size; \
        is_image_in_odd_chunks_bak = _is_image_in_odd_chunks; \
        set_address_convertor(0, 0); \
}

#define NATIVE_PHY_ADDR_FUNC(func, arg) { \
        bool ret = true; \
        u_int32_t log2_chunk_size_bak, is_image_in_odd_chunks_bak; \
        DISABLE_CONVERTOR(log2_chunk_size_bak, is_image_in_odd_chunks_bak); \
        ret = func arg; \
        set_address_convertor(log2_chunk_size_bak, is_image_in_odd_chunks_bak); \
        return ret; \
}
bool FBase::read_phy(u_int32_t phy_addr, u_int32_t *data)
{
    NATIVE_PHY_ADDR_FUNC(read, (phy_addr, data));
}

bool FBase::read_phy(u_int32_t phy_addr, void *data, int len)
{
    NATIVE_PHY_ADDR_FUNC(read, (phy_addr, data, len));
}

bool Flash::write_phy(u_int32_t phy_addr, u_int32_t data)
{
    NATIVE_PHY_ADDR_FUNC(write, (phy_addr, data));
}

bool Flash::write_phy(u_int32_t phy_addr, void *data, int cnt, bool noerase)
{
    // Avoid warning
    (void)noerase;
    NATIVE_PHY_ADDR_FUNC(write, (phy_addr, data, cnt));
}

bool Flash::read_modify_write_phy(u_int32_t phy_addr, void *data, int cnt, bool noerase)
{
    // Avoid warning
    (void)noerase;
    NATIVE_PHY_ADDR_FUNC(write_with_erase, (phy_addr, data, cnt));
}

bool Flash::read_modify_write(u_int32_t phy_addr, void *data, int cnt, bool noerase)
{
    // Avoid warning
    (void)noerase;
    return write_with_erase(phy_addr, data, cnt);
}

bool Flash::erase_sector_phy(u_int32_t phy_addr)
{
    NATIVE_PHY_ADDR_FUNC(erase_sector, (phy_addr));
}


////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr,
                  void *data,
                  int cnt,
                  bool noerase)
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

    u_int8_t         *p = (u_int8_t*)data;
    u_int32_t sect_size = get_current_sector_size();

    u_int32_t chunk_addr;
    u_int32_t chunk_size;

    u_int32_t first_set;
    for (first_set = 0; ((sect_size >> first_set) & 1) == 0; first_set++)
        ;

    Aligner align(first_set);
    align.Init(addr, cnt);
    while (align.GetNextChunk(chunk_addr, chunk_size)) {
        // Write / Erase in sector_size aligned chunks
        int rc;

        if (!noerase) {
            u_int32_t sector = (chunk_addr / sect_size) * sect_size;
            if (sector != _curr_sector) {
                _curr_sector = sector;
                if (!erase_sector(_curr_sector)) {
                    return false;
                }

            }
        }

        if (_no_burn) {
            continue;
        }

        // Actual write:
        u_int32_t phys_addr = cont2phys(chunk_addr);
        // printf("-D- write: addr = %#x, phys_addr = %#x\n", chunk_addr, phys_addr);
        mft_signal_set_handling(1);
        rc = mf_write(_mfl, phys_addr, chunk_size, p);
        deal_with_signal();

        if (rc != MFE_OK) {
            if (rc == MFE_ICMD_BAD_PARAM || rc == MFE_REG_ACCESS_BAD_PARAM) {
                return errmsg("Flash write of %d bytes to address %s0x%x failed: %s\n"
                              "    This may indicate that a FW image was already updated on flash, but not loaded by the device.\n"
                              "    Please load FW on the device (reset device or reboot machine) before burning a new FW.",
                              chunk_size,
                              _log2_chunk_size ? "physical " : "",
                              chunk_addr,
                              mf_err2str(rc));

            } else {
                return errmsg("Flash write of %d bytes to address %s0x%x failed: %s",
                              chunk_size,
                              _log2_chunk_size ? "physical " : "",
                              chunk_addr,
                              mf_err2str(rc));
            }
        }

        // Loop advance
        p    += chunk_size;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////
bool Flash::write(u_int32_t addr, u_int32_t data)
{
    u_int32_t word;

    if (!_mfl) {
        return errmsg("Not opened");
    }
    if (addr & 0x3) {
        return errmsg("Address should be 4-bytes aligned.");
    }
    if (!read(addr, &word)) {
        return false;
    }
    if (word == data) {
        return true;   // already there
    }
    return write_sector_with_erase(addr, &data, 4);
}

bool Flash::write_sector_with_erase(u_int32_t addr, void *data, int cnt)
{
    u_int32_t sector_size = get_current_sector_size();
    u_int32_t sector_mask = ~(sector_size - 1);

    u_int32_t sector = addr & sector_mask;
    u_int32_t offest_in_bytes = (addr & ~sector_mask);
    u_int32_t word_in_sector = offest_in_bytes / sizeof(u_int32_t);

    if (offest_in_bytes + cnt > sector_size) {
        return errmsg("data exceeds current sector");
    }

    vector<u_int32_t> buff(sector_size / sizeof(u_int32_t));
    if (!read(sector, &buff[0], sector_size)) {
        return false;
    }
    if (!erase_sector(sector)) {
        return false;
    }

    memcpy(&buff[word_in_sector], data, cnt);

    // no need to erase twice noerase=true
    return write(sector, &buff[0], sector_size, true);
}

bool Flash::write_with_erase(u_int32_t addr, void *data, int cnt)
{
    u_int32_t towrite = (u_int32_t)cnt;
    u_int32_t currSize;
    u_int32_t currAddr = addr;
    u_int32_t alreadyWritten = 0;
    u_int32_t sizeUntillEndOfSector = 0;
    u_int32_t sector_size = get_current_sector_size();
    while (towrite > 0) {
        sizeUntillEndOfSector = sector_size - (currAddr & (sector_size - 1));
        currSize = towrite >  sizeUntillEndOfSector ? sizeUntillEndOfSector : towrite;
        if (!write_sector_with_erase(currAddr, ((u_int8_t*)data + alreadyWritten), currSize)) {
            return false;
        }
        towrite -= currSize;
        currAddr += currSize;
        alreadyWritten += currSize;
    }
    return true;
}

bool Flash::erase_sector(u_int32_t addr)
{
    int rc;
    u_int32_t phys_addr = cont2phys(addr);
    mft_signal_set_handling(1);
    if (_flash_working_mode == Flash::Fwm_4KB) {
        rc = mf_erase_4k_sector(_mfl, phys_addr);
    } else if (_flash_working_mode == Flash::Fwm_64KB) {
        rc = mf_erase_64k_sector(_mfl, phys_addr);
    } else {
        rc = mf_erase(_mfl, phys_addr);
    }
    deal_with_signal();
    if (rc != MFE_OK) {
        if (rc == MFE_REG_ACCESS_RES_NOT_AVLBL || rc == MFE_REG_ACCESS_BAD_PARAM) {
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


bool Flash::is_fifth_gen()
{
    return mf_is_fifth_gen(_mfl);
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

bool Flash::disable_hw_access(u_int64_t key)
{
    int rc;
    rc = mf_disable_hw_access_with_key(_mfl, key);

    if (rc != MFE_OK) {
        return errmsg("Disable HW access failed: %s", mf_err2str(rc));
    }
    return true;

}

bool Flash::sw_reset()
{
    int rc = mf_sw_reset(_mfl);
    if (rc != MFE_OK) {
        if (rc == MFE_UNSUPPORTED_DEVICE) {
            return errmsg("operation supported only for InfiniScale4 switch, SwitchX and SwitchIB over IB interface");
        }
        return errmsg("%s (%s)", errno == 0 ? "" : strerror(errno), mf_err2str(rc));
    }
    return true;
}


bool Flash::get_attr(ext_flash_attr_t& attr)
{
    attr.banks_num = _attr.banks_num;
    attr.hw_dev_id = _attr.hw_dev_id;
    attr.rev_id = _attr.rev_id;
    if (_attr.type_str != NULL) {
        // we don't print the flash type in old devices
        attr.type_str = strcpy(new char[strlen(_attr.type_str) + 1], _attr.type_str);
    }
    attr.size = _attr.size;
    attr.sector_size = _attr.sector_size;
    attr.block_write = _attr.block_write;
    attr.command_set = _attr.command_set;
    attr.quad_en_support = _attr.quad_en_support;
    attr.dummy_cycles_support = _attr.dummy_cycles_support;
    // Quad EN query
    if (_attr.quad_en_support) {
        attr.mf_get_quad_en_rc = (MfError)mf_get_quad_en(_mfl, &attr.quad_en);
    }
    // Dummy Cycles query
    if (_attr.dummy_cycles_support) {
        attr.mf_get_dummy_cycles_rc = (MfError)mf_get_dummy_cycles(_mfl, &attr.dummy_cycles);
    }

    // Flash write protected info query
    attr.write_protect_support = _attr.write_protect_support;
    if (_attr.write_protect_support) {
        int bank;
        for (bank = 0; bank < _attr.banks_num; bank++) {
            attr.mf_get_write_protect_rc_array[bank] = (MfError)mf_get_write_protect(_mfl, bank, &attr.protect_info_array[bank]);
        }
    }
    return true;
}

const char* Flash::getFlashType()
{
    if (_attr.type_str != NULL) {
        return _attr.type_str;
    }
    return (const char*)NULL;
}

#define GET_IN_PARAM(param_in, out, first_op, second_op) { \
        if (!strcmp(param_in, first_op)) { \
            out = 1; \
        } else if (!strcmp(param_in, second_op)) { \
            out = 0; \
        } else { \
            return errmsg("bad argument (%s) it can be " first_op " or " second_op "", param_in); \
        } \
}
bool Flash::set_attr(char *param_name, char *param_val_str)
{
    int rc;
    //TODO: make generic function that sets params
    if (!strcmp(param_name, QUAD_EN_PARAM)) {
        char *endp;
        u_int8_t quad_en_val;
        quad_en_val = strtoul(param_val_str, &endp, 0);
        if (*endp != '\0' || quad_en_val > 1) {
            return errmsg("Bad " QUAD_EN_PARAM " value (%s), it can be 0 or 1\n", param_val_str);
        }
        rc = mf_set_quad_en(_mfl, quad_en_val);
        if (rc != MFE_OK) {
            return errmsg("Setting " QUAD_EN_PARAM " failed: (%s)", mf_err2str(rc));
        }
    } else if (!strcmp(param_name, DUMMY_CYCLES_PARAM)) {
        char *endp;
        u_int8_t dummy_cycles_val;
        dummy_cycles_val = strtoul(param_val_str, &endp, 0);
        if (*endp != '\0' || dummy_cycles_val < 1 || dummy_cycles_val > 15) {
            // value is actually [0.15] but val=0 and val=15 indicate default state (thus they are the same so no need for both values to be accepted)
            return errmsg("Bad " DUMMY_CYCLES_PARAM " value (%s), it can be [1..15]\n", param_val_str);
        }
        rc = mf_set_dummy_cycles(_mfl, dummy_cycles_val);
        if (rc != MFE_OK) {
            return errmsg("Setting " DUMMY_CYCLES_PARAM " failed: (%s)", mf_err2str(rc));
        }
    } else if (strstr(param_name, FLASH_NAME) == param_name) {
        char *flash_param, *param_str, *endp, *bank_num_str;
        u_int8_t bank_num;
        flash_param = strtok(param_name, ".");
        param_str   = strtok((char*)NULL, ".");
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
                num_str = strtok((char*)NULL, "-");
                sec = strtok((char*)NULL, "");
                if (tb == NULL || num_str == NULL || sec == NULL) {
                    return errmsg("missing parameters for setting the " WRITE_PROTECT " attribute, see help for more info.");
                }
                GET_IN_PARAM(tb, protect_info.is_bottom, WP_BOTTOM_STR, WP_TOP_STR);
                GET_IN_PARAM(sec, protect_info.is_subsector, WP_SUBSEC_STR, WP_SEC_STR);

                protect_info.sectors_num = strtoul(num_str, &endp, 0);
                if (*endp != '\0') {
                    return errmsg("bad argument (%s), only integer value is allowed.", num_str);
                }
                if (!protect_info.sectors_num) {
                    return errmsg("Invalid sectors number, Use \"Disabled\" instead.");
                }
            }
            rc = mf_set_write_protect(_mfl, bank_num, &protect_info);
            if (rc != MFE_OK) {
                return errmsg("Setting " WRITE_PROTECT " failed: (%s)", mf_err2str(rc));
            }
        } else {
            return errmsg("Unknown attribute %s.%s", flash_param, param_str);
        }


    } else {
        return errmsg("Unknown attribute %s", param_name);
    }
    return true;
}

bool Flash::is_flash_write_protected()
{
    int bank;
    int rc;
    write_protect_info_t protect_info;

    memset(&protect_info, 0x0, sizeof(protect_info));
    if (_attr.write_protect_support) {
        for (bank = 0; bank < _attr.banks_num; bank++) {
            rc = mf_get_write_protect(_mfl, bank, &protect_info);
            if (rc == MFE_OK && protect_info.sectors_num != 0) {
                return true;
            } else {
                if (rc && rc != MFE_NOT_SUPPORTED_OPERATION) { // We ignore when operation is not supported
                    return true;
                }
            }
        }
    }
    return false;
}

void Flash::deal_with_signal()
{
#ifndef UEFI_BUILD
    int sig;
    sig = mft_signal_is_fired();
    if (sig) {
        // reset received signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        //raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
#endif
    return;
}

#define FLINT_ERASE_SIZE_HOOK "FLINT_ERASE_SIZE"
bool Flash::set_flash_working_mode(int mode)
{
    if (!_attr.support_sub_and_sector && mode != Flash::Fwm_Default) {
        return errmsg("Changing Flash IO working mode not supported.");
    }
    // Verification Hook
    if (_attr.support_sub_and_sector) {
        char *flint_io_env = getenv(FLINT_ERASE_SIZE_HOOK);
        if (flint_io_env) {
            int num =  strtoul(flint_io_env, (char**)NULL, 0);
            if (num == 0x1000 || num == 0x10000) {
                _curr_sector_size = (u_int32_t)num;
                _flash_working_mode = _curr_sector_size == 0x1000 ? Flash::Fwm_4KB : Flash::Fwm_64KB;
                _curr_sector = _curr_sector & ~(_curr_sector_size - 1);
                return true;
            }
        }
    }
    // Verification Hook end

    if (mode == Flash::Fwm_Default) {
        _curr_sector_size = _attr.sector_size;
        _flash_working_mode = Flash::Fwm_Default;
    } else if (mode == Flash::Fwm_4KB) {
        _curr_sector_size = 0x1000;
        _flash_working_mode = Flash::Fwm_4KB;
    } else if (mode == Flash::Fwm_64KB) {
        _curr_sector_size = 0x10000;
        _flash_working_mode = Flash::Fwm_64KB;
    } else {
        return errmsg("Unknown Flash IO working mode: 0x%x", mode);
    }
    _curr_sector = _curr_sector & ~(_curr_sector_size - 1);
    return true;
}
