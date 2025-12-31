/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "flint_base.h"
#include "flint_io.h"
#include "fw_ops.h"
#include "fs5_ops.h"
#include "fs4_ops.h"
#include "fs3_ops.h"
#include "fs2_ops.h"
#include "fs_pldm.h"
#include "fsctrl_ops.h"
#include "fs_comps_factory.h"
#include "dev_mgt/tools_dev_types.h"
#include "pldmlib/pldm_pkg.h"
#include "pldmlib/pldm_utils.h"

#ifdef CABLES_SUPP
#include "cablefw_ops.h"
#endif

#ifndef NO_MFA_SUPPORT
#include <mfa.h>
#endif

#if !defined(UEFI_BUILD)
#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif // NO_OPEN_SSL
#endif // UEFI_BUILD

#ifndef __WIN__
#define OP_NOT_SUPPORTED EOPNOTSUPP
#else // __WIN__
#define OP_NOT_SUPPORTED EINVAL
#endif // __WIN__

extern const char* g_sectNames[];

bool FwOperations::readBufAux(FBase& f, u_int32_t o, void* d, int l, const char* p)
{
    bool rc = true;
    READBUF(f, o, d, l, p);
    return rc;
}

int FwOperations::getFileSignature(const char* fname)
{
    FILE* fin;
    unsigned char tmpb[17] = {0};
    int res = IMG_SIG_TYPE_UNKNOWN;

    if (!(fin = fopen(fname, "r")))
    {
        // abit ugly , need to establish a correct ret val
        return IMG_SIG_OPEN_FILE_FAILED;
    }
    if (!fgets((char*)tmpb, sizeof(tmpb), fin))
    {
        fclose(fin);
        return IMG_SIG_OPEN_FILE_FAILED;
    }

    if (tmpb[0] == 0xCC && tmpb[1] == 0 && tmpb[2] == 0xCC && tmpb[3] == 1)
    {
        res = IMG_SIG_TYPE_CC;
        fclose(fin);
        return res;
    }

    if (!strncmp((char*)tmpb, "MTFW", 4) || FsCompsFactory::IsFsCompsFingerPrint(tmpb))
    {
        res = IMG_SIG_TYPE_BIN;
    }
    if (!strncmp((char*)tmpb, "MFAR", 4))
    {
        res = IMG_SIG_TYPE_MFA;
    }
    if (std::memcmp(tmpb, expectedHeaderIdentifier, sizeof(expectedHeaderIdentifier)) == 0)
    {
        res = IMG_SIG_TYPE_PLDM;
    }
    if (!strncmp((char*)tmpb, "MTCF", 4))
    {
        res = IMG_SIG_TYPE_CF;
    }
    fclose(fin);
    return res;
}

#ifndef NO_MFA_SUPPORT

int FwOperations::getBufferSignature(u_int8_t* buf, u_int32_t size)
{
    int res = 0;

    if (size < 4)
    {
        return 0;
    }
    if (!strncmp((char*)buf, "MTFW", 4))
    {
        res = IMG_SIG_TYPE_BIN;
    }
    if (!strncmp((char*)buf, "MFAR", 4))
    {
        res = IMG_SIG_TYPE_MFA;
    }

    return res;
}

int FwOperations::getMfaImgInner(char* fileName,
                                 u_int8_t* mfa_buf,
                                 int size,
                                 char* psid,
                                 u_int8_t** imgbuf,
                                 char* errBuf,
                                 int errBufSize)
{
    int image_type = 1; // FW image
    mfa_desc* mfa_d = NULL;
    int res = -1;

    // open mfa file
    if (fileName)
    {
        res = mfa_open_file(&mfa_d, fileName);
    }
    else if (mfa_buf && size != 0)
    {
        res = mfa_open_buf(&mfa_d, mfa_buf, size);
    }
    else
    {
        WriteToErrBuff(errBuf, (char*)"Internal error: bad parameters to getMfaImg", errBufSize);
        return res;
    }

    if (res)
    {
        // mfa_open_* failed, return error.
        res = res < 0 ? res : -1 * res;
        WriteToErrBuff(errBuf, (char*)"Failed to open mfa file", errBufSize);
        return res;
    }

    if (psid == NULL)
    {
        WriteToErrBuff(errBuf, (char*)"Internal error: PSID must be supplied", errBufSize);
        if (mfa_d)
        {
            mfa_close(mfa_d);
        }
        return -1; // No psid => no image
    }

    // get appropriate image for requested PSID from mfa file
    res = mfa_get_image(mfa_d, psid, image_type, (char*)"", imgbuf);

    // if res != 0 there is an error
    if (res)
    {
        const char* errStr = mfa_get_last_error(mfa_d);
        // if error field is empty return generic message
        if (!errStr || strlen(errStr) == 0)
        {
            errStr = "Failed to get MFA Image";
        }

        WriteToErrBuff(errBuf, (char*)errStr, errBufSize);
    }

    // close mfa file
    mfa_close(mfa_d);
    return res;
}

int FwOperations::getMfaImg(char* fileName, char* psid, u_int8_t** imgbuf, char* errBuf, int errBufSize)
{
    return getMfaImgInner(fileName, NULL, 0, psid, imgbuf, errBuf, errBufSize);
}

int FwOperations::getMfaImg(u_int8_t* mfa_buf, int size, char* psid, u_int8_t** imgbuf, char* errBuf, int errBufSize)
{
    return getMfaImgInner(NULL, mfa_buf, size, psid, imgbuf, errBuf, errBufSize);
}

#endif

void FwOperations::FwCleanUp()
{
    if (_ioAccess)
    {
        _ioAccess->close();
        delete _ioAccess;
        _ioAccess = (FBase*)NULL;
    }
    if (_fname)
    {
        delete[] _fname;
        _fname = (char*)NULL;
    }
    if (_devName)
    {
        delete[] _devName;
        _devName = (char*)NULL;
    }
    if (_fwParams.fileHndl)
    {
        delete[] _fwParams.fileHndl;
        _fwParams.fileHndl = (char*)NULL;
    }
    if (_fwParams.mstHndl)
    {
        delete[] _fwParams.mstHndl;
        _fwParams.mstHndl = (char*)NULL;
    }
    if (_fwParams.psid)
    {
        delete[] _fwParams.psid;
        _fwParams.psid = (char*)NULL;
    }
}

bool FwOperations::FwVerifyAdv(ExtVerifyParams& verifyParams)
{
    return FwVerify(verifyParams.verifyCallBackFunc, verifyParams.isStripedImage, verifyParams.showItoc,
                    verifyParams.ignoreDToc);
}

void FwOperations::FwInitCom()
{
    memset(&_fwImgInfo, 0, sizeof(_fwImgInfo));
}

void FwOperations::GetFwParams(fw_ops_params_t& fwParams)
{
    fwParams = _fwParams;
}

void FwOperations::getSupporteHwId(u_int32_t** supportedHwId, u_int32_t& supportedHwIdNum)
{
    *supportedHwId = _fwImgInfo.supportedHwId;
    supportedHwIdNum = _fwImgInfo.supportedHwIdNum;
}

bool FwOperations::CheckBoot2(u_int32_t beg,
                              u_int32_t offs,
                              u_int32_t& next,
                              bool fullRead,
                              const char* pref,
                              VerifyCallBack verifyCallBackFunc)
{
    DPRINTF(("FwOperations::CheckBoot2\n"));
    u_int32_t size = 0x0;

    char* pr = new char[strlen(pref) + 512];
    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs + beg);
    // Size
    if (!(*_ioAccess).read(offs + beg + 4, &size))
    {
        errmsg("%s - read error (%s)\n", pr, (*_ioAccess).err());
        delete[] pr;
        return false;
    }
    TOCPU1(size);
    DPRINTF(("FwOperations::CheckBoot2 size = 0x%x\n", size));
    if (size > 1048576 || size < 4)
    {
        report_callback(verifyCallBackFunc, "%s /0x%08x/ - unexpected size (0x%x)\n", pr, offs + beg + 4, size);
        delete[] pr;
        return errmsg("Boot2 invalid size\n");
    }
    _fwImgInfo.boot2Size = (size + 4) * 4;

    // Get absolute address on flash when checking BOOT2 for FS3 image format (for FS2 its always displayed as
    // contiguous) Adrianc: why dont we show them both in the same way when running verify.
    u_int32_t boot2AbsAddr =
      ((this->FwType() == FIT_FS3 || this->FwType() == FIT_FS4) && _ioAccess->is_flash()) ?
        _ioAccess->get_phys_from_cont(beg, _fwImgInfo.cntxLog2ChunkSize, (_fwImgInfo.imgStart != 0)) :
        beg;

    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, offs + boot2AbsAddr,
            offs + boot2AbsAddr + (size + 4) * 4 - 1, (size + 4) * 4);

    if (fullRead == true || !_ioAccess->is_flash())
    {
        Crc16 crc;
        u_int32_t* buff = new u_int32_t[size + 4];
        memset(buff, 0, (size + 4) * sizeof(u_int32_t));
        bool rc = readBufAux((*_ioAccess), offs + beg, buff, size * 4 + 16, pr);
        if (!rc)
        {
            delete[] pr;
            delete[] buff;
            return errmsg("%s - read error (%s)\n", "Boot2", (*_ioAccess).err());
        }
        // we hold for FS3 an image cache so we selectevely update it in UpdateImgCache() call
        UpdateImgCache((u_int8_t*)buff, offs + beg, size * 4 + 16);
        TOCPUn(buff, size + 4);
        CRC1n(crc, buff, size + 4);
        CRC1n(_ioAccess->get_image_crc(), buff, size + 4);

        crc.finish();

        u_int32_t crc_act = buff[size + 3];
        delete[] buff;
        if (crc.get() != crc_act)
        {
            DPRINTF(("FwOperations::CheckBoot2 wrong CRC (exp:0x%x, act:0x%x)\n", crc.get(), crc_act));
            report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n", pr, offs + beg,
                            crc.get(), crc_act);
            if (!_fwParams.ignoreCrcCheck)
            {
                delete[] pr;
                return errmsg(MLXFW_BAD_CRC_ERR, BAD_CRC_MSG);
            }
        }
        else
        {
            report_callback(verifyCallBackFunc, "%s - OK\n", pr);
        }
        _ioAccess->get_image_crc() << crc_act;
    }
    next = offs + size * 4 + 16;
    delete[] pr;
    return true;
} // CheckBoot2

bool FwOperations::CheckAndPrintCrcRes(char* pr,
                                       bool blank_crc,
                                       u_int32_t off,
                                       u_int32_t crc_act,
                                       u_int32_t crc_exp,
                                       bool ignore_crc,
                                       VerifyCallBack verifyCallBackFunc)
{
    if (ignore_crc)
    {
        report_callback(verifyCallBackFunc, "%s - CRC IGNORED\n", pr);
    }
    else
    {
        if (blank_crc)
        {
            report_callback(verifyCallBackFunc, "%s - BLANK CRC (0xffff)\n", pr);
        }
        else if (crc_exp == crc_act)
        {
            report_callback(verifyCallBackFunc, "%s - OK\n", pr);
        }
        else
        {
            report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n", pr, off, crc_exp,
                            crc_act);
            if (!_fwParams.ignoreCrcCheck)
            {
                return errmsg(BAD_CRC_MSG);
            }
        }
    }
    return true;
}

const u_int32_t FwOperations::_cntx_magic_pattern[4] = {0x4D544657, // Ascii of "MTFW"
                                                        0x8CDFD000, // Random data
                                                        0xDEAD9270, 0x4154BEEF};

const u_int32_t FwOperations::_fs4_magic_pattern[4] = {0x4D544657, 0xABCDEF00, 0xFADE1234, 0x5678DEAD};

const u_int32_t FwOperations::_cntx_image_start_pos[FwOperations::CNTX_START_POS_SIZE] = {
  0, 0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000};

bool FwOperations::FindMagicPattern(FBase* ioAccess, u_int32_t addr, u_int32_t const cntx_magic_pattern[])
{
    if (addr + 16 > ioAccess->get_effective_size())
    {
        return false;
    }
    for (int i = 0; i < 4; i++)
    {
        u_int32_t w = 0;
        READ4_NOERRMSG((*ioAccess), addr + i * 4, &w);
        TOCPU1(w);
        if (w != cntx_magic_pattern[i])
        {
            DPRINTF(("FwOperations::FindMagicPattern addr=0x%x false\n", addr));
            // printf("-D- Looking for magic pattern %d addr %06x: Exp=%08x Act=%08x\n", i, addr + i * 4,
            // _cntx_magic_pattern[i], w);
            return false;
        }
    }

    DPRINTF(("FwOperations::FindMagicPattern addr=0x%x true\n", addr));
    return true;
}

// FindAllImageStart
// OUT: start_locations: set to the start addresses of the found image markers (in accending order)
// OUT: found_images:    Number of found images (and number of valid entries in the start_locations array).
bool FwOperations::FindAllImageStart(FBase* ioAccess,
                                     u_int32_t start_locations[CNTX_START_POS_SIZE],
                                     u_int32_t* found_images,
                                     u_int32_t const cntx_magic_pattern[])
{
    DPRINTF(("FwOperations::FindAllImageStart\n"));
    int needed_pos_num;

    needed_pos_num = CNTX_START_POS_SIZE;

    /* WA: due to bug on SwichIB first GA FW (FW doesnt look at chip select field in mfba)
     *     when reading from flash address 0x400000 it wraps around to 0x0 causing more than one
     *     valid image to be found. as a WA we dont check at 0x400000. basic flash operations
     *     are affected when attempting to access addressess greater than 0x3fffff.
     */
    if (ioAccess->get_dev_id() == SWITCH_IB_HW_ID)
    {
        needed_pos_num -= 1;
    }

    ioAccess->set_address_convertor(0, 0);
    if (found_images)
    {
        *found_images = 0;
        for (int i = 0; i < needed_pos_num; i++)
        {
            if (FindMagicPattern(ioAccess, _cntx_image_start_pos[i], cntx_magic_pattern))
            {
                start_locations[*found_images] = _cntx_image_start_pos[i];
                (*found_images)++;
            }
        }
        DPRINTF(("FwOperations::FindAllImageStart found %d image(s)\n", *found_images));
    }

    return true;
}
// CAN BE IN ANOTHER MODULE
bool FwOperations::GetSectData(std::vector<u_int8_t>& file_sect, const u_int32_t* buff, const u_int32_t size)
{
    file_sect.clear();
    file_sect.insert(file_sect.end(), (u_int8_t*)buff, (u_int8_t*)buff + size);

    return true;
}

bool FwOperations::FwAccessCreate(fw_ops_params_t& fwParams, FBase** ioAccessP, u_int16_t swDevId)
{
    DPRINTF(("FwOperations::FwAccessCreate\n"));
    if (fwParams.hndlType == FHT_FW_FILE)
    {
#ifndef NO_MFA_SUPPORT
        int sig = getFileSignature(fwParams.fileHndl);
        if (sig == IMG_SIG_OPEN_FILE_FAILED)
        { // i.e we failed to open file
            WriteToErrBuff(fwParams.errBuff, strerror(errno), fwParams.errBuffSize);
            return false;
        }
        if (sig == IMG_SIG_TYPE_BIN || sig == IMG_SIG_TYPE_CF)
        {
            *ioAccessP = new FImage;
            if (!(*ioAccessP)->open(fwParams.fileHndl, false, !fwParams.shortErrors))
            {
                WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
        }
        else if (sig == IMG_SIG_TYPE_PLDM)
        {
            *ioAccessP = new FPldm;
            if (!(*ioAccessP)->open(fwParams.fileHndl, false, !fwParams.shortErrors))
            {
                WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
        }
        else if (sig == IMG_SIG_TYPE_MFA)
        {
            u_int8_t* imgbuf = NULL;
            int sz;
            // get image from mfa file
            if ((sz = getMfaImg(fwParams.fileHndl, fwParams.psid, &imgbuf, fwParams.errBuff, fwParams.errBuffSize)) < 0)
            {
                return false;
            }
            *ioAccessP = new FImage;
            if (!((FImage*)(*ioAccessP))->open((u_int32_t*)imgbuf, (u_int32_t)sz, !fwParams.shortErrors))
            {
                mfa_release_image(imgbuf);
                WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
            mfa_release_image(imgbuf);
        }
        else
        {
            WriteToErrBuff(fwParams.errBuff, (char*)"Invalid Image signature.", fwParams.errBuffSize);
            return false; // Unknown signature
        }
#else
        *ioAccessP = new FImage;
        if (!(*ioAccessP)->open(fwParams.fileHndl, false, !fwParams.shortErrors))
        {
            WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
#endif
    }
    else if (fwParams.hndlType == FHT_FW_BUFF)
    {
        u_int32_t numInfo = fwParams.buffSize;
#ifndef NO_MFA_SUPPORT
        int sig = getBufferSignature((u_int8_t*)fwParams.buffHndl, numInfo);
        if (sig == IMG_SIG_TYPE_BIN || swDevId != 0)
        {
            *ioAccessP = new FImage;
            if (!((FImage*)*ioAccessP)->open(fwParams.buffHndl, (u_int32_t)numInfo, !fwParams.shortErrors))
            {
                WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
        }
        else if (sig == IMG_SIG_TYPE_MFA)
        {
            u_int8_t* imgbuf;
            int sz;
            // get image from mfa file
            if ((sz = getMfaImg((u_int8_t*)fwParams.buffHndl, numInfo, fwParams.psid, &imgbuf, fwParams.errBuff,
                                fwParams.errBuffSize)) < 0)
            {
                return false;
            }
            *ioAccessP = new FImage;
            if (!((FImage*)*ioAccessP)->open((u_int32_t*)imgbuf, (u_int32_t)sz, !fwParams.shortErrors))
            {
                mfa_release_image(imgbuf);
                WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
            mfa_release_image(imgbuf);
        }
        else
        {
            WriteToErrBuff(fwParams.errBuff, (char*)"Invalid Image signature.", fwParams.errBuffSize);
            return false; // Unknown signature
        }
#else
        *ioAccessP = new FImage;
        if (!((FImage*)*ioAccessP)->open(fwParams.buffHndl, numInfo, !fwParams.shortErrors))
        {
            WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
#endif
    }
    else if (fwParams.hndlType == FHT_UEFI_DEV)
    {
        *ioAccessP = new Flash;
        if (!(*ioAccessP)->open(fwParams.uefiHndl, &fwParams.uefiExtra, false, !fwParams.shortErrors))
        {
            WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
    }
    else if (fwParams.hndlType == FHT_MST_DEV)
    {
        *ioAccessP = new Flash;
        if (!(*ioAccessP)
               ->open(fwParams.mstHndl, fwParams.forceLock, fwParams.readOnly, fwParams.numOfBanks,
                      fwParams.flashParams, fwParams.ignoreCacheRep, !fwParams.shortErrors, fwParams.cx3FwAccess))
        {
            // TODO: release memory here ?
            WriteToErrBuff(fwParams.errBuff, (char*)(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
        // set no flash verify if needed (default =false)
        (*ioAccessP)->set_no_flash_verify(fwParams.noFlashVerify);
        // work with 64KB sector size if possible to increase performace in full fw burn
        ((*ioAccessP)->set_flash_working_mode(Flash::Fwm_64KB));
    }
    else
    {
        WriteToErrBuff(fwParams.errBuff, (char*)"Unknown Handle Type.", fwParams.errBuffSize);
        return false;
    }
    return true;
}

bool FwOperations::GetImageFormatVersion(FBase& f, u_int32_t boot_version_offset, u_int8_t& image_format_version)
{
    u_int32_t data = 0;
    if (!f.read(boot_version_offset, &data, IMAGE_LAYOUT_BOOT_VERSION_SIZE))
    {
        return false;
    }
    image_layout_boot_version boot_version;
    memset(&boot_version, 0, sizeof(boot_version));
    image_layout_boot_version_unpack(&boot_version, (u_int8_t*)&data);
    image_format_version = boot_version.image_format_version;
    DPRINTF(("FwOperations::GetImageFormatVersion image_format_version = %d\n", image_format_version));
    return true;
}

u_int8_t FwOperations::IsFS4OrFS5Image(FBase& f, u_int32_t* found_images)
{
    DPRINTF(("FwOperations::IsFS4OrFS5Image\n"));
    u_int8_t image_format_version;
    u_int32_t image_start[CNTX_START_POS_SIZE] = {0};

    FindAllImageStart(&f, image_start, found_images, _fs4_magic_pattern);

    if (*found_images)
    {
        if (!GetImageFormatVersion(f, image_start[0] + FS4_BOOT_VERSION_OFFSET, image_format_version))
        {
            return FS_UNKNOWN_IMG;
        }
        if (image_format_version == IMG_VER_FS4)
        {
            return FS_FS4_GEN;
        }
        else if (image_format_version == IMG_VER_FS5)
        {
            return FS_FS5_GEN;
        }
        else
        {
            return FS_UNKNOWN_IMG;
        }
    }
    return FS_UNKNOWN_IMG;
}

u_int8_t FwOperations::IsFS3OrFS2Image(FBase& f, u_int32_t* found_images)
{
    u_int8_t image_format_version;
    u_int32_t image_start[CNTX_START_POS_SIZE] = {0};
    FindAllImageStart(&f, image_start, found_images, _cntx_magic_pattern);
    if (found_images)
    {
        if (!GetImageFormatVersion(f, image_start[0] + FS3_BOOT_VERSION_OFFSET, image_format_version))
        {
            return FS_UNKNOWN_IMG;
        }
        if (image_format_version == IMG_VER_FS3)
        {
            return FS_FS3_GEN;
        }
        else
        {
            // TODO: if the img format version is unknown we should fail instead of considering it FS2
            return FS_FS2_GEN;
        }
    }
    return FS_UNKNOWN_IMG;
}

u_int8_t FwOperations::IsCableImage(FBase& f)
{
    char data[5] = {0};
    READ4_NOERRMSG(f, 0, (u_int32_t*)&data);
    if (!strncmp(data, "MTCF", 4))
    {
        return FS_FC1_GEN;
    }
    return FS_UNKNOWN_IMG;
}

u_int8_t FwOperations::IsFSCompsImage(FBase& f)
{
    u_int8_t data[16] = {0};
    f.read(0, data, 16, false, NULL);

    if (FsCompsFactory::IsFsCompsFingerPrint(data))
    {
        return FS_COMPS_GEN;
    }

    return FS_UNKNOWN_IMG;
}

u_int8_t FwOperations::IsPLDM(FBase& f)
{
    static const u_int32_t PLDM_HEADER_IDENTIFIER_LENGTH = 16;
    u_int8_t data[PLDM_HEADER_IDENTIFIER_LENGTH] = {0};
    f.read(0, data, PLDM_HEADER_IDENTIFIER_LENGTH, false, NULL);
    if (!strncmp((const char*)data, (const char*)expectedHeaderIdentifier, PLDM_HEADER_IDENTIFIER_LENGTH))
    {
        return FS_PLDM_1_0;
    }
    return FS_UNKNOWN_IMG;
}

u_int8_t FwOperations::CheckFwFormat(FBase& f, bool getFwFormatFromImg, u_int16_t swDevId)
{
    DPRINTF(("FwOperations::CheckFwFormat\n"));
    u_int8_t v;
    u_int32_t found_images = 0;

    if (((f.is_flash() && !getFwFormatFromImg) || swDevId != 0))
    {
        u_int32_t hwDevId = swDevId ? dm_dev_sw_id2hw_dev_id(swDevId) : f.get_dev_id();
        return GetFwFormatFromHwDevID(hwDevId);
    }
    else
    {
        v = IsPLDM(f);
        if (v != FS_UNKNOWN_IMG)
        {
            return v;
        }

        v = IsCableImage(f);
        if (v != FS_UNKNOWN_IMG)
        {
            return v;
        }

        v = IsFSCompsImage(f);
        if (v != FS_UNKNOWN_IMG)
        {
            return v;
        }

        // First check if it is FS4
        v = IsFS4OrFS5Image(f, &found_images);
        if (found_images)
        {
            return v;
        }
        // If not FS4 then check if it is FS3 or FS2
        return IsFS3OrFS2Image(f, &found_images);
    }
    return FS_UNKNOWN_IMG;
}

bool FwOperations::CheckBinVersion(u_int8_t binVerMajor, u_int8_t binVerMinor)
{
    if (binVerMajor == 0 && binVerMinor == 0)
    {
        return true;
    }

    if (binVerMajor > _maxBinMajorVer /*FS4_MAX_BIN_VER_MAJOR*/)
    {
        return errmsg(MLXFW_UNSUPPORTED_BIN_VER_ERR,
                      "Unsupported binary version (%d.%d) please update to latest MFT package",
                      binVerMajor,
                      binVerMinor);
    }
    if (binVerMajor < _minBinMajorVer      /*FS4_MIN_BIN_VER_MAJOR*/
        || (binVerMajor == _minBinMajorVer /*FS4_MIN_BIN_VER_MAJOR*/
            && binVerMinor < _minBinMinorVer))
    {
        return errmsg(MLXFW_UNSUPPORTED_BIN_VER_ERR,
                      "Unsupported binary version (%d.%d) minimal supported version (%d.%d)", binVerMajor, binVerMinor,
                      _minBinMajorVer /*FS4_MIN_BIN_VER_MAJOR*/, _minBinMinorVer /*FS4_MIN_BIN_VER_MINOR*/);
    }

    return true;
}

FwOperations* FwOperations::FwOperationsCreate(void* fwHndl,
                                               void* info,
                                               char* psid,
                                               fw_hndl_type_t hndlType,
                                               char* errBuff,
                                               int buffSize,
                                               bool ignore_crc_check)
{
    DPRINTF(("FwOperations::FwOperationsCreate\n"));
    fw_ops_params_t fwParams;
    memset(&fwParams, 0, sizeof(fwParams));
    fwParams.psid = psid;
    fwParams.hndlType = hndlType;
    fwParams.errBuff = errBuff;
    fwParams.errBuffSize = buffSize;
    fwParams.ignoreCrcCheck = ignore_crc_check;
    fwParams.shortErrors = true;
    fwParams.swDevId = 0;

    if (hndlType == FHT_FW_FILE)
    {
        fwParams.fileHndl = (char*)fwHndl;
    }
    else if (hndlType == FHT_FW_BUFF)
    {
        fwParams.buffHndl = (u_int32_t*)fwHndl;
        fwParams.buffSize = *((u_int32_t*)info);
    }
    else if (hndlType == FHT_UEFI_DEV)
    {
        fwParams.uefiHndl = (uefi_Dev_t*)fwHndl;
        fwParams.uefiExtra = *(uefi_dev_extra_t*)info;
    }
    else if (hndlType == FHT_MST_DEV)
    {
        fwParams.mstHndl = (char*)fwHndl;
        fwParams.forceLock = false;
        fwParams.readOnly = false;
        fwParams.numOfBanks = -1;
        fwParams.flashParams = (flash_params_t*)NULL;
        fwParams.ignoreCacheRep = 0;
        fwParams.noFlashVerify = false;
        fwParams.cx3FwAccess = 0;
    }
    else if (hndlType == FHT_CABLE_DEV)
    {
        fwParams.buffHndl = (u_int32_t*)fwHndl;
    }
    return FwOperationsCreate(fwParams);
}

bool FwOperations::imageDevOperationsCreate(fw_ops_params_t& devParams,
                                            fw_ops_params_t& imgParams,
                                            FwOperations** devFwOps,
                                            FwOperations** imgFwOps,
                                            bool ignoreSecurityAttributes,
                                            bool ignoreDToc)
{
    *imgFwOps = FwOperationsCreate(imgParams);
    if (!(*imgFwOps))
    {
        return false;
    }

    if ((*imgFwOps)->FwType() == FIT_FS2)
    {
        devParams.canSkipFwCtrl = true;
        *devFwOps = FwOperationsCreate(devParams);
        if (!(*devFwOps))
        {
            return false;
        }
        return true;
    }

    fw_info_t imgQuery;
    memset(&imgQuery, 0, sizeof(fw_info_t));
    if (!(*imgFwOps)->FwQuery(&imgQuery, true, false, true, ignoreDToc))
    {
        delete *imgFwOps;
        *imgFwOps = NULL;
        return false;
    }
    if (imgQuery.fs3_info.security_mode == SM_NONE && ignoreSecurityAttributes == false &&
         (*imgFwOps)->FwType() != FIT_COMPS && (*imgFwOps)->FwType() != FIT_PLDM_1_0)
    {
        devParams.noFwCtrl = true;
    }
    devParams.deviceIndex = (*imgFwOps)->GetDeviceIndex();

    *devFwOps = FwOperationsCreate(devParams);
    if (!(*devFwOps))
    {
        return false;
    }
    return true;
}

void FwOperations::BackUpFwParams(fw_ops_params_t& fwParams)
{
    _fwParams.hndlType = fwParams.hndlType;
    _fwParams.buffHndl = fwParams.buffHndl;
    _fwParams.buffSize = fwParams.buffSize;
    _fwParams.cx3FwAccess = fwParams.cx3FwAccess;
    _fwParams.errBuff = (char*)NULL;
    _fwParams.errBuffSize = 0;
    _fwParams.fileHndl =
      (fwParams.hndlType == FHT_FW_FILE && fwParams.fileHndl) ?
        strncpy((char*)(new char[(strlen(fwParams.fileHndl) + 1)]), fwParams.fileHndl, strlen(fwParams.fileHndl) + 1) :
        (char*)NULL;
    // no support for flash params
    _fwParams.flashParams = (flash_params_t*)NULL;
    _fwParams.forceLock = fwParams.forceLock;
    _fwParams.ignoreCacheRep = fwParams.ignoreCacheRep;
    _fwParams.mstHndl =
      (fwParams.hndlType == FHT_MST_DEV && fwParams.mstHndl) ?
        strncpy((char*)(new char[(strlen(fwParams.mstHndl) + 1)]), fwParams.mstHndl, strlen(fwParams.mstHndl) + 1) :
        (char*)NULL;
    _fwParams.noFlashVerify = fwParams.noFlashVerify;
    _fwParams.numOfBanks = fwParams.numOfBanks;
    _fwParams.psid = fwParams.psid ? strncpy((char*)(new char[(strlen(fwParams.psid) + 1)]), fwParams.psid,
                                             strlen(fwParams.psid) + 1) :
                                     (char*)NULL;
    _fwParams.readOnly = fwParams.readOnly;
    _fwParams.shortErrors = fwParams.shortErrors;
    _fwParams.uefiExtra = fwParams.uefiExtra;
    _fwParams.uefiHndl = fwParams.uefiHndl;
    _fwParams.isCableFw = fwParams.isCableFw;
    _fwParams.ignoreCrcCheck = fwParams.ignoreCrcCheck;
}

const char* file_handle_type_to_str(fw_hndl_type_t type)
{
    switch (type)
    {
        case FHT_MST_DEV:
            return "MST_DEVICE";
        case FHT_FW_FILE:
            return "FW_FILE";
        case FHT_UEFI_DEV:
            return "UEFI_DEVICE";
        case FHT_FW_BUFF:
            return "FW_BUFFER";
        case FHT_CABLE_DEV:
            return "CABLE_DEVICE";
        default:
            return "UNKNOWN";
    }
}

bool FwOperations::IsDeviceSupported(fw_ops_params_t& fwParams)
{
    mfile* mf = mopen_adv(fwParams.mstHndl, (MType)(MST_DEFAULT | MST_LINKX_CHIP));
    if (!mf)
    {
        return false;
    }

    dm_dev_id_t devid_t = DeviceUnknown;
    u_int32_t devid = 0;
    u_int32_t revid = 0;
    dm_get_device_id(mf, &devid_t, &devid, &revid);
    if (dm_is_gpu(devid_t))
    {
        mclose(mf);
        WriteToErrBuff(fwParams.errBuff, (char*)"GPUs are not supported.", fwParams.errBuffSize);
        return false;
    }
    mclose(mf);
    return true;
}

FwOperations* FwOperations::FwOperationsCreate(fw_ops_params_t& fwParams)
{
    DPRINTF(("FwOperations::FwOperationsCreate\n"));
    FwOperations* fwops;
    u_int8_t fwFormat;
    FBase* ioAccess = (FBase*)NULL;
    FwCompsMgr* fwCompsAccess = (FwCompsMgr*)NULL;
    bool getFwFormatFromImg = false;
    if (fwParams.hndlType == FHT_MST_DEV && !IsDeviceSupported(fwParams))
    {
        return (FwOperations*)NULL;
    }
#ifdef CABLES_SUPP
    if (fwParams.hndlType == FHT_CABLE_DEV)
    {
        fwops = new CableFwOperations(fwParams.mstHndl);
        if (!fwops->FwInit())
        {
            WriteToErrBuff(fwParams.errBuff, (char*)fwops->err(), fwParams.errBuffSize);
            delete fwops;
            return (FwOperations*)NULL;
        }
        fwops->_devName = strcpy(new char[strlen(fwParams.mstHndl) + 1], fwParams.mstHndl);
    }
    else
#endif
    {
        if ((!fwParams.ignoreCacheRep && !fwParams.noFwCtrl && fwParams.hndlType == FHT_MST_DEV) ||
            (fwParams.hndlType == FHT_UEFI_DEV && !fwParams.uefiExtra.dev_info.no_fw_ctrl))
        {
            fw_comps_error_t fwCompsErr = FWCOMPS_SUCCESS;
            if (!fwParams.canSkipFwCtrl)
            { // CX3/PRO are unsupported
                fwCompsAccess = new FwCompsMgr(fwParams.mstHndl, FwCompsMgr::DEVICE_HCA_SWITCH, fwParams.deviceIndex);
            }
            else if (fwParams.hndlType == FHT_UEFI_DEV)
            {
                fwCompsAccess = new FwCompsMgr(fwParams.uefiHndl, &fwParams.uefiExtra);
            }
            else
            {
                fwCompsErr = FWCOMPS_UNSUPPORTED_DEVICE;
            }
            // In case MCDA capability isn't supported according to MCAM, we'll have
            // fwCompsAccess object created, but with an internal error in fwCompsErr
            if (fwCompsAccess != NULL)
            {
                fwCompsErr = fwCompsAccess->getLastError();
            }
            if (fwCompsErr != FWCOMPS_SUCCESS)
            {
                bool exitOnError = false;
                if (fwCompsErr == FWCOMPS_MTCR_OPEN_DEVICE_ERROR)
                {
                    // mtcr lib failed to open the provided device.
                    WriteToErrBuff(fwParams.errBuff, (char*)"Failed to open device", fwParams.errBuffSize);
                    exitOnError = true;
                }
                else if (fwCompsErr == FWCOMPS_REG_ACCESS_RES_NOT_AVLBL)
                {
                    WriteToErrBuff(fwParams.errBuff, (char*)fwCompsAccess->getLastErrMsg(), fwParams.errBuffSize);
                    exitOnError = true;
                }
                if (fwCompsAccess != NULL)
                {
                    delete fwCompsAccess;
                }
                fwCompsAccess = (FwCompsMgr*)NULL;
                if (exitOnError)
                {
                    return (FwOperations*)NULL;
                }
            }
            else
            {
                fwInfoT fwInfo;
                if (fwParams.forceLock)
                {
                    fwCompsAccess->forceRelease();
                }

                // In case MCC is not preferable (e.g verify command) but the device is secured or GB via switch
                // We'll stay with MCC flow because we can't use MFBA/Direct-Access
                if (fwParams.mccUnsupported && !fwCompsAccess->getMfileObj()->gb_info.is_gearbox &&
                    fwCompsAccess->queryFwInfo(&fwInfo) == true && fwInfo.security_type.secure_fw == 0)
                {
                    delete fwCompsAccess;
                    fwCompsAccess = (FwCompsMgr*)NULL;
                }
                else
                {
                    //* WA for non secured BB to work in no_fw_ctrl mode (instead of MCC) by setting fwParams.noFwCtrl=1
                    dm_dev_id_t deviceId = DeviceUnknown;
                    u_int32_t hwDevId = 0x0;
                    u_int32_t hwRevId = 0x0;
                    if ((fwCompsAccess->getMfileObj()->flags & MDEVS_MLNX_OS) != 0)
                    {
                        FLASH_ACCESS_DPRINTF(("MLNXOS device interface\n"));
                        if (dm_get_device_id(fwCompsAccess->getMfileObj(), &deviceId, &hwDevId, &hwRevId) == MFE_OK)
                        {
                            FLASH_ACCESS_DPRINTF(("deviceId = %s\n", dm_dev_type2str(deviceId)));
                            if (deviceId == DeviceQuantum2)
                            {
                                FLASH_ACCESS_DPRINTF(("BB device identified\n"));
                                if (fwCompsAccess->queryFwInfo(&fwInfo))
                                {
                                    if (fwInfo.security_type.secure_fw == 0)
                                    {
                                        FLASH_ACCESS_DPRINTF(("Non secured BB device, deleting fw comps mgr object and "
                                                              "setting no_fw_ctrl mode\n"));
                                        delete fwCompsAccess;
                                        fwCompsAccess = (FwCompsMgr*)NULL;
                                        fwParams.noFwCtrl = 1;
                                    }
                                    else
                                    {
                                        FLASH_ACCESS_DPRINTF(("Secured BB device, using MCC flow\n"));
                                    }
                                }
                                else
                                {
                                    FLASH_ACCESS_DPRINTF(("Failed to query fw comps mgr object\n"));
                                }
                            }
                        }
                    }
                    //* MCC flow
                    if (fwParams.noFwCtrl == 0)
                    {
                        FLASH_ACCESS_DPRINTF(("Flash init to use MCC flow\n"));
                        fwFormat = FS_FSCTRL_GEN;
                        goto init_fwops;
                    }
                }
            }
        }
        if (!FwAccessCreate(fwParams, &ioAccess, fwParams.swDevId))
        {
            return (FwOperations*)NULL;
        }
        if (fwParams.hndlType == FHT_UEFI_DEV)
        {
            // IN UEFI we don't have an access to read devID from cr-space so we are reading it from FW  image signature
            getFwFormatFromImg = true;
        }

        fwFormat = CheckFwFormat(*ioAccess, getFwFormatFromImg, fwParams.swDevId);
    init_fwops:
        switch (fwFormat)
        {
#if !defined(UEFI_BUILD)
            case FS_FS2_GEN:
            {
                DPRINTF(("FS2 ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new Fs2Operations(ioAccess);
                break;
            }
#endif
            case FS_FS3_GEN:
            {
                DPRINTF(("FS3 ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new Fs3Operations(ioAccess);
                break;
            }

            case FS_FS4_GEN:
            {
                DPRINTF(("FS4 ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new Fs4Operations(ioAccess);
                break;
            }

            case FS_FS5_GEN:
            {
                DPRINTF(("FS5 ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new Fs5Operations(ioAccess);
                break;
            }

            case FS_COMPS_GEN:
            {
                DPRINTF(("FS COMPS ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = FsCompsFactory::Create(ioAccess);
                break;
            }

            case FS_FSCTRL_GEN:
            {
                if (!fwCompsAccess)
                {
                    delete ioAccess;
                    return (FwOperations*)NULL;
                }
                DPRINTF(("FSCTRL ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new FsCtrlOperations(fwCompsAccess);
                break;
            }
            case FS_PLDM_1_0:
            {
                DPRINTF(("FS_PLDM_1_0 ops created for %s\n", file_handle_type_to_str(fwParams.hndlType)));
                fwops = new FsPldmOperations(ioAccess);
                if (!fwops->FwInit())
                {
                    WriteToErrBuff(fwParams.errBuff, (char*)"FwInit has failed!", fwParams.errBuffSize);
                    delete fwops;
                    return NULL;
                }
                return fwops;
            }

#ifdef CABLES_SUPP
            case FS_FC1_GEN:
            {
                fwops = new CableFwOperations(ioAccess);
                break;
            }

#endif
            default:
                delete ioAccess;
                WriteToErrBuff(fwParams.errBuff, (char*)"Invalid Firmware Format (found FS Gen 1)",
                               fwParams.errBuffSize);
                return (FwOperations*)NULL;
        }
        // save initialization parameters
        fwops->BackUpFwParams(fwParams);
        fwops->_advErrors = !fwParams.shortErrors;
        if (!fwops->FwInit())
        {
            WriteToErrBuff(fwParams.errBuff, (char*)"FwInit has failed!", fwParams.errBuffSize);
            delete fwops; // will also delete the fwCompsAccess! no memory leak here
            return NULL;
        }
        if (!fwops->CreateSignatureManager())
        {
            WriteToErrBuff(fwParams.errBuff, (char*)"Cannot create signature manager!", fwParams.errBuffSize);
            fwops->err_clear();
            delete fwops; // will also delete the fwCompsAccess! no memory leak here
            return NULL;
        }
        if (fwParams.hndlType == FHT_FW_FILE)
        {
            fwops->_fname = strcpy(new char[strlen(fwParams.fileHndl) + 1], fwParams.fileHndl);
        }
        if (fwParams.hndlType == FHT_MST_DEV)
        {
            fwops->_devName = strcpy(new char[strlen(fwParams.mstHndl) + 1], fwParams.mstHndl);
        }
    }
    return fwops;
}

u_int32_t FwOperations::CalcImageCRC(u_int32_t* buff, u_int32_t size)
{
    Crc16 crc;
    TOCPUn(buff, size);
    CRCn(crc, buff, size);
    CPUTOn(buff, size);
    crc.finish();
    u_int32_t new_crc = crc.get();
    return new_crc;
}

bool FwOperations::writeImageEx(ProgressCallBackEx progressFuncEx,
                                void* progressUserData,
                                ProgressCallBack progressFunc,
                                u_int32_t addr,
                                void* data,
                                int cnt,
                                bool isPhysAddr,
                                bool readModifyWrite,
                                int totalSz,
                                int alreadyWrittenSz,
                                bool cpuUtilization,
                                int cpuPercent)
{
#ifndef __WIN__
    (void)cpuUtilization;
    (void)cpuPercent;
#endif
    u_int8_t* p = (u_int8_t*)data;
    u_int32_t curr_addr = addr;
    u_int32_t towrite = cnt;
    u_int32_t last_percent = 0xff;
    totalSz = totalSz == -1 ? cnt : totalSz;
    int origFlashWorkingMode = Flash::Fwm_Default;
    u_int32_t CurrentIteration = 0;
    bool rc;
    while (towrite)
    {
        // Write
        int trans;
        if (_ioAccess->is_flash())
        {
            if (readModifyWrite)
            {
                // perform write with the smallest supported sector size
                origFlashWorkingMode = _ioAccess->get_flash_working_mode();
                _ioAccess->set_flash_working_mode(Flash::Fwm_Default);
            }
            if (cpuUtilization)
            {
                _ioAccess->set_flash_utilization(cpuUtilization, cpuPercent);
            }
            trans = (towrite > (int)Flash::TRANS) ? (int)Flash::TRANS : towrite;
            if (isPhysAddr)
            {
                if (readModifyWrite)
                {
                    rc = _ioAccess->read_modify_write_phy(curr_addr, p, trans);
                }
                else
                {
                    rc = _ioAccess->write_phy(curr_addr, p, trans);
                }
            }
            else
            {
                if (readModifyWrite)
                {
                    rc = _ioAccess->read_modify_write(curr_addr, p, trans);
                }
                else
                {
                    rc = _ioAccess->write(curr_addr, p, trans);
                }
            }
            if (readModifyWrite)
            {
                // restore erase sector size
                _ioAccess->set_flash_working_mode(origFlashWorkingMode);
            }
            if (!rc)
            {
                return errmsg(MLXFW_FLASH_WRITE_ERR, "Flash write failed: %s", _ioAccess->err());
            }
        }
        else
        {
            trans = towrite;
            if (!((FImage*)_ioAccess)->write(curr_addr, p, trans))
            {
                return errmsg("%s", _ioAccess->err());
            }
        }
        p += trans;
        curr_addr += trans;
        towrite -= trans;
        CurrentIteration++;
#ifdef __WIN__
        if (cpuUtilization)
        {
            if ((CurrentIteration % cpuPercent) == 0)
            {
                msleep(500);
            }
        }
#endif
        // Report
        if (progressFunc != NULL || progressFuncEx != NULL)
        {
            double written = cnt - towrite + alreadyWrittenSz;
            double curr_percent_double = (written / totalSz) * 100;
            u_int32_t curr_percent = (u_int32_t)curr_percent_double;
            if (last_percent != curr_percent)
            {
                last_percent = curr_percent;
                if (progressFunc != NULL && progressFunc((int)curr_percent))
                {
                    return errmsg("Aborting... received interrupt signal");
                }
                if (progressFuncEx != NULL && progressFuncEx((int)curr_percent, progressUserData))
                {
                    return errmsg("Aborting... received interrupt signal");
                }
            }
        }
    }
    return true;
} //  Flash::WriteImage

bool FwOperations::writeImage(ProgressCallBack progressFunc,
                              u_int32_t addr,
                              void* data,
                              int cnt,
                              bool isPhysAddr,
                              bool readModifyWrite,
                              int totalSz,
                              int alreadyWrittenSz)
{
    return writeImageEx((ProgressCallBackEx)NULL, NULL, progressFunc, addr, data, cnt, isPhysAddr, readModifyWrite,
                        totalSz, alreadyWrittenSz);
}

bool FwOperations::CheckMac(u_int64_t mac)
{
    if ((mac >> 40) & 0x1)
    {
        return errmsg("Multicast bit (bit 40) is set");
    }

    if (mac >> 48)
    {
        return errmsg("More than 48 bits are used");
    }

    return true;
}

bool FwOperations::CheckMac(guid_t mac)
{
    u_int64_t bigMac = ((u_int64_t)mac.h << 32 & 0xffffffff00000000ULL) | ((u_int64_t)mac.l & 0x00000000ffffffffULL);
    return CheckMac(bigMac);
}

void FwOperations::recalcSectionCrc(u_int8_t* buf, u_int32_t data_size)
{
    Crc16 crc;
    u_int32_t crcRes;
    for (u_int32_t i = 0; i < data_size; i += 4)
    {
        crc << __be32_to_cpu(*(u_int32_t*)(buf + i));
    }
    crc.finish();
    crcRes = crc.get();
    *((u_int32_t*)(buf + data_size)) = __cpu_to_be32(crcRes);
}

chip_type_t FwOperations::getChipType()
{
    int i = 0;
    while (hwDevData[i].name != NULL)
    {
        int j = 0;
        while (hwDevData[i].swDevIds[j] != 0)
        {
            if (hwDevData[i].swDevIds[j] == _fwImgInfo.ext_info.dev_type)
            {
                return hwDevData[i].chipType;
            }
            j++;
        }
        i++;
    }
    return CT_UNKNOWN;
}

chip_type_t FwOperations::getChipType(u_int32_t devid)
{
    int i = 0;
    while (hwDevData[i].name != NULL)
    {
        if (hwDevData[i].hwDevId == devid)
        {
            return hwDevData[i].chipType;
        }
        i++;
    }
    return CT_UNKNOWN;
}

bool FwOperations::getInfoFromHwDevid(u_int32_t hwDevId, chip_type_t& chipT, const u_int32_t** swIds)
{
    int i = 0;
    u_int32_t localDevId = hwDevId & 0xffff; // remove revison ID, it's not relevant here
    while (hwDevData[i].name != NULL)
    {
        if (hwDevData[i].hwDevId == localDevId)
        {
            chipT = hwDevData[i].chipType;
            *swIds = hwDevData[i].swDevIds;
            return true;
        }
        i++;
    }
    return errmsg(MLXFW_DEV_ID_ERR, "Failed to identify device ID(MT%d).", hwDevId);
}

FwOperations::HwDevData FwOperations::getInfoFromChipType(chip_type_t chipT) const
{
    int i = 0;
    while (hwDevData[i].name != NULL)
    {
        if (hwDevData[i].chipType == chipT)
        {
            return hwDevData[i];
        }
        i++;
    }
    return hwDevData[i];
}

// TODO:combine both databases(hwDevData and hwDev2Str) and remove old unsupporded devices i.e infinihost
// infinihost_iii_ex infinihost_iii_lx
const FwOperations::HwDevData FwOperations::hwDevData[] = {
  {"ConnectX-3",
   CX3_HW_ID,
   CT_CONNECTX,
   CFT_HCA,
   2,
   {4099, 4100, 4101, 4102, 4104, 4105, 4106, 4107, 4108, 4109, 4110, 4111, 4112, 0},
   {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-3Pro", CX3_PRO_HW_ID, CT_CONNECTX, CFT_HCA, 2, {4103, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Connect_IB",
   CONNECT_IB_HW_ID,
   CT_CONNECT_IB,
   CFT_HCA,
   2,
   {CONNECT_IB_SW_ID, 4114, 4115, 4116, 4117, 4118, 4119, 4120, 4121, 4122, 4123, 4124, 0},
   {{UNKNOWN_BIN, {0}}}},
  {"Switch_IB", SWITCH_IB_HW_ID, CT_SWITCH_IB, CFT_SWITCH, 0, {52000, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-4", CX4_HW_ID, CT_CONNECTX4, CFT_HCA, 0, {4115, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-4LX", CX4LX_HW_ID, CT_CONNECTX4_LX, CFT_HCA, 0, {4117, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-5",
   CX5_HW_ID,
   CT_CONNECTX5,
   CFT_HCA,
   0,
   {4119, 4121, 0},
   {{CX5_LOW_BIN, {4119, 0}}, {CX5_HIGH_BIN, {4119, 4121, 0}}, {UNKNOWN_BIN, {0}}}},
  {"ConnectX-6", CX6_HW_ID, CT_CONNECTX6, CFT_HCA, 0, {4123, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-6DX", CX6DX_HW_ID, CT_CONNECTX6DX, CFT_HCA, 0, {4125, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-6LX", CX6LX_HW_ID, CT_CONNECTX6LX, CFT_HCA, 0, {4127, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-7", CX7_HW_ID, CT_CONNECTX7, CFT_HCA, 0, {4129, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-8", CX8_HW_ID, CT_CONNECTX8, CFT_HCA, 0, {4131, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-8 Pure PCIe Switch", CX8_PURE_PCIE_SWITCH_HW_ID, CT_CONNECTX8_PURE_PCIE_SWITCH, CFT_HCA, 0, {6525, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-9", CX9_HW_ID, CT_CONNECTX9, CFT_HCA, 0, {4133, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ConnectX-9 Pure PCIe Switch", CX9_PURE_PCIE_SWITCH_HW_ID, CT_CONNECTX9_PURE_PCIE_SWITCH, CFT_HCA, 0, {6526, 0}, {{UNKNOWN_BIN, {0}}}},
  {"BlueField", BF_HW_ID, CT_BLUEFIELD, CFT_HCA, 0, {41680, 41681, 41682, 0}, {{UNKNOWN_BIN, {0}}}},
  {"BlueField2", BF2_HW_ID, CT_BLUEFIELD2, CFT_HCA, 0, {41684, 41685, 41686, 0}, {{UNKNOWN_BIN, {0}}}},
  {"BlueField3", BF3_HW_ID, CT_BLUEFIELD3, CFT_HCA, 0, {41690, 41691, 41692, 0}, {{UNKNOWN_BIN, {0}}}},
  {"BlueField4", BF4_HW_ID, CT_BLUEFIELD4, CFT_HCA, 0, {41694, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum", SPECTRUM_HW_ID, CT_SPECTRUM, CFT_SWITCH, 0, {52100, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Switch_IB2", SWITCH_IB2_HW_ID, CT_SWITCH_IB2, CFT_SWITCH, 0, {53000, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Quantum", QUANTUM_HW_ID, CT_QUANTUM, CFT_SWITCH, 0, {54000, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum2", SPECTRUM2_HW_ID, CT_SPECTRUM2, CFT_SWITCH, 0, {53100, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum3", SPECTRUM3_HW_ID, CT_SPECTRUM3, CFT_SWITCH, 0, {53104, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Quantum2", QUANTUM2_HW_ID, CT_QUANTUM2, CFT_SWITCH, 0, {54002, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Quantum3", QUANTUM3_HW_ID, CT_QUANTUM3, CFT_SWITCH, 0, {54004, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum4", SPECTRUM4_HW_ID, CT_SPECTRUM4, CFT_SWITCH, 0, {53120, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum5", SPECTRUM5_HW_ID, CT_SPECTRUM5, CFT_SWITCH, 0, {53122, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Spectrum6", SPECTRUM6_HW_ID, CT_SPECTRUM6, CFT_SWITCH, 0, {53124, 0}, {{UNKNOWN_BIN, {0}}}},
  {"Gearbox", GEARBOX_HW_ID, CT_GEARBOX, CFT_GEARBOX, 0, {0, 0}, {{UNKNOWN_BIN, {0}}}},
  {"GearboxManager", GB_MANAGER_HW_ID, CT_GEARBOX_MGR, CFT_GEARBOX, 0, {0, 0}, {{UNKNOWN_BIN, {0}}}},
  {"AbirGearbox", ABIR_GB_HW_ID, CT_ABIR_GEARBOX, CFT_GEARBOX, 0, {0, 0}, {{UNKNOWN_BIN, {0}}}},
  {"ArcusE", ARCUSE_HW_ID, CT_ARCUSE, CFT_SWITCH, 0, {45568, 0}, {{UNKNOWN_BIN, {0}}}},
  {(char*)NULL, 0, CT_UNKNOWN, CFT_UNKNOWN, 0, {0}, {{UNKNOWN_BIN, {0}}}}, // zero devid terminator
};

const FwOperations::HwDev2Str FwOperations::hwDev2Str[] = {
  {"ConnectIB", CONNECT_IB_HW_ID, 0x00},
  {"ConnectX-3 A0", CX3_HW_ID, 0x00},
  {"ConnectX-3 A1", CX3_HW_ID, 0x01},
  {"ConnectX-3Pro", CX3_PRO_HW_ID, 0x00},
  {"ConnectX-4", CX4_HW_ID, 0x00},
  {"ConnectX-4LX", CX4LX_HW_ID, 0x00},
  {"ConnectX-5", CX5_HW_ID, 0x00},
  {"ConnectX-6", CX6_HW_ID, 0x00},
  {"ConnectX-6DX", CX6DX_HW_ID, 0x00},
  {"ConnectX-6LX", CX6LX_HW_ID, 0x00},
  {"ConnectX-7", CX7_HW_ID, 0x00},
  {"ConnectX-8", CX8_HW_ID, 0x00},
  {"ConnectX-8 Pure PCIe Switch", CX8_PURE_PCIE_SWITCH_HW_ID, 0x00},
  {"ConnectX-9", CX9_HW_ID, 0x00},
  {"ConnectX-9 Pure PCIe Switch", CX9_PURE_PCIE_SWITCH_HW_ID, 0x00},
  {"BlueField", BF_HW_ID, 0x00},
  {"BlueField2", BF2_HW_ID, 0x00},
  {"BlueField3", BF3_HW_ID, 0x00},
  {"BlueField4", BF4_HW_ID, 0x00},
  {"SwitchIB A0", SWITCH_IB_HW_ID, 0x00},
  {"Spectrum A0", SPECTRUM_HW_ID, 0x00},
  {"SwitchIB2 A0", SWITCH_IB2_HW_ID, 0x00},
  {"Quantum A0", QUANTUM_HW_ID, 0x00},
  {"Spectrum A1", SPECTRUM_HW_ID, 0x01},
  {"Spectrum2 A0", SPECTRUM2_HW_ID, 0x00},
  {"Spectrum3 A0", SPECTRUM3_HW_ID, 0x00},
  {"Quantum2 A0", QUANTUM2_HW_ID, 0x00},
  {"Quantum3 A0", QUANTUM3_HW_ID, 0x00},
  {"Spectrum4 A0", SPECTRUM4_HW_ID, 0x00},
  {"Spectrum5 A0", SPECTRUM5_HW_ID, 0x00},
  {"Spectrum6 A0", SPECTRUM6_HW_ID, 0x00},
  {(char*)NULL, (u_int32_t)0, (u_int8_t)0x00}, // zero device ID terminator
};

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])
#define MAX_HW_NAME_LEN 100
bool FwOperations::HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char* hw_name)
{
    for (int i = 0; hwDev2Str[i].hwDevId != 0; i++)
    {
        const HwDev2Str* hwDev2StrMem = &(hwDev2Str[i]);

        if (hwDev2StrMem->hwDevId == hw_id && hwDev2StrMem->revId == rev_id)
        {
            int len = strlen(hwDev2StrMem->name);
            if (len >= MAX_HW_NAME_LEN)
            {
                return errmsg("Internal error: Length of device name: %d exceeds the maximum allowed size: %d", len,
                              MAX_HW_NAME_LEN - 1);
            }
            strcpy(hw_name, hwDev2StrMem->name);
            return true;
        }
    }
    // When the device or rev is unknown we use the hw ID and rev to display it.
    sprintf(hw_name, "MT%d-%02X", hw_id, rev_id);
    return true;
}

// This function gets the HW ID of the target device and the dev ID from
// the image. It then matches the 2 IDs and returns an error in case of
// mismatch. The match is not 1:1 , since the FW image contains the SW
// dev id, and a single hw dev id may match multiple SW dev IDs.
//
bool FwOperations::CheckMatchingHwDevId(u_int32_t hwDevId,
                                        u_int32_t rev_id,
                                        u_int32_t* supportedHwId,
                                        u_int32_t supportedHwIdNum)
{
    char supp_hw_id_list[MAX_NUM_SUPP_HW_LIST_STR] = {'\0'};
    char curr_hw_id_name[MAX_HW_NAME_LEN];

    for (u_int32_t i = 0; i < supportedHwIdNum; i++)
    {
        u_int32_t currSupportedHwId = supportedHwId[i];
        u_int32_t supp_hw_id = currSupportedHwId & 0xffff;
        u_int32_t supp_rev_id = (currSupportedHwId >> 16) & 0xff;
        u_int32_t tmp_size_of_list;
        char hw_name[MAX_HW_NAME_LEN];

        if (currSupportedHwId == 0)
        {
            break;
        }
        // Check if device is supported!
        if (supp_hw_id == hwDevId && supp_rev_id == rev_id)
        {
            return true;
        }
        // Append checked to list of supported device in order to print it in the error if we this device is not
        // supported

        // Get the HW name of current supported HW ID
        if (!HWIdRevToName(supp_hw_id, supp_rev_id, hw_name))
        {
            return false;
        }
        // Check if we don't exceed the array size we have
        tmp_size_of_list = strlen(supp_hw_id_list) + strlen(hw_name) + 2;
        if (tmp_size_of_list >= MAX_NUM_SUPP_HW_LIST_STR)
        {
            return errmsg("Internal error: Size of supported devs list: %d exceeds the maximum allowed size: %d",
                          tmp_size_of_list, MAX_NUM_SUPP_HW_LIST_STR - 1);
        }

        if (supp_hw_id_list[0] == '\0')
        {
            sprintf(supp_hw_id_list, "%s", hw_name);
        }
        else
        {
            strcat(supp_hw_id_list, ", ");
            strcat(supp_hw_id_list, hw_name);
        }
    }
    // If we get here, this FW cannot be burnt in the current device.
    // Get the Device name
    if (!HWIdRevToName(hwDevId, rev_id, curr_hw_id_name))
    {
        return false;
    }

    return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR,
                  "FW image file cannot be programmed to device %s, it is intended for: %s only", curr_hw_id_name,
                  supp_hw_id_list);
}
bool FwOperations::CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId)
{
    const HwDevData* devData = (const HwDevData*)NULL;
    const char* hwDevName = (const char*)NULL;

    // First, find the HW device that the SW id matches
    for (int i = 0; hwDevData[i].hwDevId != 0; i++)
    {
        if (hwDevData[i].hwDevId == hwDevId)
        {
            hwDevName = hwDevData[i].name; // TODO: Check bug if device not found
        }

        if (devData == NULL)
        {
            for (int j = 0; hwDevData[i].swDevIds[j]; j++)
            {
                if (hwDevData[i].swDevIds[j] == imageDevId)
                {
                    devData = &hwDevData[i];
                    break;
                }
            }
        }
    }

    if (devData == NULL)
    {
        report_warn("Unknown device id (%d) in the given FW image. Skipping HW match check.\n", imageDevId);
        return true;
    }
    else if (devData->hwDevId != hwDevId)
    {
        return errmsg("Trying to burn a \"%s\" image on a \"%s\" device.", devData->name, hwDevName);
    }

    return true;
}

bool FwOperations::CheckMatchingBinning(u_int32_t hwDevId, BinIdT binningVal, u_int32_t imageDevId)
{
    const HwDevData* devData = (const HwDevData*)NULL;

    // First, find the HW device that the Hw id matches
    for (int i = 0; hwDevData[i].hwDevId != 0; i++)
    {
        if (hwDevData[i].hwDevId == hwDevId)
        {
            devData = &hwDevData[i];
        }
    }
    if (devData != NULL)
    {
        // Find the bin speed and match its SW ID to the ImageDevID
        for (int j = 0; devData->binningId[j].binId != UNKNOWN_BIN; j++)
        {
            if (devData->binningId[j].binId == binningVal)
            {
                int k = 0;
                while (devData->binningId[j].swId[k] != 0)
                {
                    if (imageDevId == devData->binningId[j].swId[k])
                    {
                        return true;
                    }
                    k++;
                }
                return errmsg("FW image does not match the device bin info.\n");
            }
        }
    }
    return true;
}

void FwOperations::FwDebugPrint(char* str)
{
    if (_printFunc != NULL)
    {
        _printFunc(str);
    }
}

bool FwOperations::FwSetPrint(PrintCallBack PrintFunc)
{
    _printFunc = PrintFunc;
    return true;
}

bool FwOperations::CheckPSID(FwOperations& imageOps, u_int8_t allow_psid_change)
{
    if (!allow_psid_change)
    {
        if (strncmp(_fwImgInfo.ext_info.psid, imageOps._fwImgInfo.ext_info.psid, PSID_LEN))
        {
            return errmsg(MLXFW_PSID_MISMATCH_ERR,
                          "Image PSID is %s, it cannot be burnt into current device (PSID: %s)",
                          imageOps._fwImgInfo.ext_info.psid, _fwImgInfo.ext_info.psid);
        }
    }
    return true;
}

bool FwOperations::CheckFwVersion(FwOperations& imageOps, u_int8_t forceVersion)
{
    if (!forceVersion)
    {
        FwVersion current(createFwVersion(&_fwImgInfo.ext_info)), image(createFwVersion(&imageOps._fwImgInfo.ext_info));
        if (current.are_same_branch(image))
        {
            if (current >= image)
            {
                return errmsg(MLXFW_FW_ALREADY_UPDATED_ERR, "FW is already updated.");
            }
        }
    }
    return true;
}

bool FwOperations::FwSwReset()
{
    if (msw_reset(getMfileObj()))
    {
        if (errno == EPERM)
        {
            return errmsg("operation supported only for IB switches.");
        }
        else if (errno == OP_NOT_SUPPORTED)
        {
            return errmsg("operation supported only for un-managed switches.");
        }
        else
        {
            return errmsg("operation failed, errno - %d.", errno);
        }
    }

    return true;
}

void FwOperations::WriteToErrBuff(char* errBuff, char* errStr, int bufSize)
{
    if (bufSize > 0)
    {
        if (bufSize > (int)strlen(errStr))
        {
            strncpy(errBuff, errStr, bufSize);
        }
        else
        {
            strncpy(errBuff, errStr, bufSize - 4);
            strcpy(&errBuff[bufSize - 4], "...");
        }
    }
    return;
}

bool FwOperations::UpdateImgCache(u_int8_t* buff, u_int32_t addr, u_int32_t size)
{
    // avoid compiler warrnings
    (void)buff;
    (void)addr;
    (void)size;
    // in FS2 we dont have ImgCache, just in FS3 so we define a defult behaviour.
    return true;
}

bool FwOperations::CntxEthOnly(u_int32_t devid)
{
    return (devid == 25448) || // ETH
           (devid == 26448) || // ETH
           (devid == 25458) || //
           (devid == 26458) || //
           (devid == 26468) || (devid == 26478);
}

// RomInfo implementation

FwOperations::RomInfo::RomInfo(const std::vector<u_int8_t>& romSector, bool resEndi)
{
    expRomFound = !romSector.empty();
    romSect = romSector;
    if (resEndi)
    {
        TOCPUn(&romSect[0], romSect.size() / 4);
    }
    numOfExpRom = 0;
    expRomComDevid = 0;
    expRomWarning = false;
    expRomErrMsgValid = false;
    noRomChecksum = false;
    memset(expRomErrMsg, 0, sizeof(expRomErrMsg));
    memset(expRomWarningMsg, 0, sizeof(expRomWarningMsg));
    memset(&romsInfo, 0, (sizeof(rom_info_t) * MAX_ROMS_NUM));
}

bool FwOperations::RomInfo::initRomsInfo(roms_info_t* info)
{
    if (info == NULL)
    {
        return errmsg("invalid roms_info_t pointer.");
    }
    info->exp_rom_found = expRomFound;
    info->num_of_exp_rom = numOfExpRom;
    info->no_rom_checksum = noRomChecksum;
    info->exp_rom_com_devid = expRomComDevid;
    info->exp_rom_warning = expRomWarning;
    info->exp_rom_err_msg_valid = expRomErrMsgValid;
    // copy strings and rom_info
    for (int i = 0; i < MAX_ROM_ERR_MSG_LEN; i++)
    {
        info->exp_rom_warning_msg[i] = expRomWarningMsg[i];
        info->exp_rom_err_msg[i] = expRomErrMsg[i];
    }
    for (int i = 0; i < MAX_ROMS_NUM; i++)
    {
        // copy rom_info struct
        info->rom_info[i].exp_rom_product_id = romsInfo[i].exp_rom_product_id; // 0 - invalid.
        info->rom_info[i].exp_rom_dev_id = romsInfo[i].exp_rom_dev_id;
        info->rom_info[i].exp_rom_supp_cpu_arch = romsInfo[i].exp_rom_supp_cpu_arch;
        info->rom_info[i].exp_rom_port = romsInfo[i].exp_rom_port;
        info->rom_info[i].exp_rom_proto = romsInfo[i].exp_rom_proto;
        info->rom_info[i].exp_rom_num_ver_fields = romsInfo[i].exp_rom_num_ver_fields;
        for (int j = 0; j < 3; j++)
        {
            info->rom_info[i].exp_rom_ver[j] = romsInfo[i].exp_rom_ver[j];
        }
    }

    return true;
}

bool FwOperations::RomInfo::ParseInfo()
{
    if (!GetExpRomVersion())
    {
        snprintf(expRomErrMsg, MAX_ROM_ERR_MSG_LEN, "%s", err());
        expRomErrMsgValid = true;
        // printf("-D-expRomErrMsg: %s \n", expRomErrMsg);
    }
    // printf("-D- expRomFound: %d   \n",expRomFound);
    // printf("-D- numOfExpRom: %d   \n",numOfExpRom);
    // printf("-D- noRomChecksum: %d   \n",noRomChecksum);
    // printf("-D- expRomComDevid: %d   \n",expRomComDevid);
    // printf("-D- expRomWarning: %d   \n",expRomWarning);
    // printf("-D- expRomErrMsgValid: %d   \n",expRomErrMsgValid);
    return true;
}

#define MAGIC_LEN 32

bool FwOperations::RomInfo::GetExpRomVersion()
{
    char magicString[MAGIC_LEN] = {"mlxsignX"};
    u_int32_t magicLen = strlen(magicString);
    bool magicFound = false;
    u_int32_t verOffset;
    u_int32_t romChecksumRange;

    // We do this HACK in order not to have mlxsign: word in our code so if mlxfwops will be part
    // of rom, no mlxsign: string will appear
    magicString[magicLen - 1] = ':';

    if (romSect.empty())
    {
        return errmsg("Expansion Rom section not found.");
    }
    // When checking the version of the expansion rom, only the first image has
    // to be checked. This is because the second image  the uefi image does not
    // have to comply with checksumming to 0. To do this you have to read  byte
    // 2 (third) of the image  and multiply by 512 to get the size of the x86
    // image.

    // Checksum:
    if (romSect.size() < 4)
    {
        return errmsg("ROM size (0x%x) is too small", (u_int32_t)romSect.size());
    }

    // restore endianess is done in the constructor if needed.
    /*  // FOR WE DON'T CHECKSUM UNTIL WE DECIDED REGARDING THE NEW FORMAT.
     */
    // We will look for the magic string in whole ROM instead of the first part of it.
    romChecksumRange = romSect.size();

    for (u_int32_t i = 0; i < romChecksumRange; i++)
    {
        for (u_int32_t j = 0; j < magicLen; j++)
        {
            if (romSect[i + j] != magicString[j])
            {
                break;
            }
            else if (j == magicLen - 1)
            {
                magicFound = true;
            }
        }

        if (magicFound)
        {
            // Get the ROM info after the mlxsign
            bool rc;
            rom_info_t* currRom;

            if (numOfExpRom == MAX_ROMS_NUM)
            {
                expRomWarning = true;
                snprintf(expRomWarningMsg,
                         MAX_ROM_ERR_MSG_LEN,
                         "Number of exp ROMs exceeds the maximum allowed number (%d)",
                         MAX_ROMS_NUM);
                // Here we want to warn regarding this issue without checksum.
                return true;
            }

            currRom = &(romsInfo[numOfExpRom]);
            verOffset = i + magicLen;
            rc = GetExpRomVerForOneRom(verOffset);
            if (rc != true)
            {
                return rc;
            }

            // Get the device ID and check if it mismatches with other ROMs
            if (expRomComDevid != MISS_MATCH_DEV_ID)
            { // When the DevId is already mismatched, no end to any check
                if (currRom->exp_rom_dev_id != EXP_ROM_GEN_DEVID)
                { // When we have a device ID on the ROM
                    if (expRomComDevid == EXP_ROM_GEN_DEVID)
                    { // Update the common DevId at the first time we find ID
                        expRomComDevid = currRom->exp_rom_dev_id;
                    }
                    else
                    { // Check if we have the same IDs, if yes, continue
                        if (currRom->exp_rom_dev_id != expRomComDevid)
                        { // There is a mismatch between ROMs
                            expRomComDevid = MISS_MATCH_DEV_ID;
                            expRomWarning = true;
                            snprintf(expRomWarningMsg, MAX_ROM_ERR_MSG_LEN, "The device IDs of the ROMs mismatched.");
                        }
                    }
                }
            }

            magicFound = false;       // Clean the magic_found to start search for another magic string
            i += (ROM_INFO_SIZE - 1); // Increase the index to point to the end of the ROM info.
            numOfExpRom++;
        }
    }

    // TODO: ADD CHECKSUM CHECK
    if (!numOfExpRom)
    {
        return errmsg("Cannot get ROM version. Signature not found.");
    }

    if (!noRomChecksum)
    { // No need for checksum on some ROMs like uEFI
        u_int8_t romChecksum = 0;
        romChecksumRange = romSect[2] * 512;
        if (romChecksumRange > romSect.size())
        {
            return errmsg("ROM size field (0x%2x) is larger than actual ROM size (0x%x)", romChecksumRange,
                          (u_int32_t)romSect.size());
        }
        else if (romChecksumRange == 0)
        {
            return errmsg("ROM size field is 0. Unknown ROM format or corrupted ROM.");
        }

        for (u_int32_t i = 0; i < romChecksumRange; i++)
        {
            romChecksum += romSect[i];
        }

        if (romChecksum != 0)
        {
            expRomWarning = true;
            snprintf(expRomWarningMsg,
                     MAX_ROM_ERR_MSG_LEN,
                     "Bad ROM Checksum (0x%02x), ROM info may not be displayed correctly.",
                     romChecksum);
        }
    }

    return true;
}

u_int8_t FwOperations::RomInfo::getNumVerFromProdId(u_int16_t prodId)
{
    if (prodId == 0xF)
    {
        return 1;
    }
    else
    {
        return 3;
    }
}

bool FwOperations::RomInfo::GetExpRomVerForOneRom(u_int32_t verOffset)
{
    u_int32_t tmp;
    u_int32_t offs4;
    u_int32_t offs8;
    rom_info_t* romInfo;

    if (numOfExpRom == MAX_ROMS_NUM)
    {
        expRomWarning = true;
        snprintf(expRomWarningMsg,
                 MAX_ROM_ERR_MSG_LEN,
                 "Number of exp ROMs exceeds the maximum allowed number: %d",
                 MAX_ROMS_NUM);
        return true;
    }
    romInfo = &(romsInfo[numOfExpRom]);

    // Following mlxsign: refer to layout in Flash Programminng application note.

    // Get expansion rom product ID
    tmp = __le32_to_cpu(*((u_int32_t*)&romSect[verOffset]));
    offs4 = __le32_to_cpu(*((u_int32_t*)&romSect[verOffset + 4]));

    romInfo->exp_rom_product_id = tmp >> 16;
    romInfo->exp_rom_num_ver_fields = FwOperations::RomInfo::getNumVerFromProdId(romInfo->exp_rom_product_id);

    // Get ROM version
    romInfo->exp_rom_ver[0] = tmp & 0xff; // always valid
    if (romInfo->exp_rom_product_id != 0xf)
    {
        romInfo->exp_rom_ver[1] = offs4 >> 16 & 0xff;
        romInfo->exp_rom_ver[2] = offs4 & 0xffff;
    }

    if (romInfo->exp_rom_product_id == 0x11 || romInfo->exp_rom_product_id == 0x21)
    {
        noRomChecksum = true;
    }

    if (romInfo->exp_rom_product_id >= 0x10)
    {
        offs8 = __le32_to_cpu(*((u_int32_t*)&romSect[verOffset + 8]));
        romInfo->exp_rom_supp_cpu_arch = (offs8 >> 8) & 0xf;
        romInfo->exp_rom_dev_id = offs8 >> 16;
        // 0x12 is CLP we have only 1 version field and no port
        if (romInfo->exp_rom_product_id != 0x12)
        {
            romInfo->exp_rom_port = (offs8 >> 12) & 0xf;
            romInfo->exp_rom_proto = offs8 & 0xff;
        }
    }
    else if (romInfo->exp_rom_product_id == 0xf)
    {
        // get string length
        u_int32_ba tmp_ba = __le32_to_cpu(*((u_int32_t*)&romSect[verOffset + 0xc]));
        u_int32_t str_len = u_int32_t(tmp_ba.range(15, 8));
        u_int32_t sign_length = u_int32_t(tmp_ba.range(7, 0));
        u_int32_t dws_num = ((str_len + 3) / 4) + 4;

        if (sign_length < dws_num)
        {
            return errmsg("The Signature length (%d) and the ROM version string length (%d) are not coordinated",
                          sign_length, str_len);
        }

        int svnv;
        char free_str[FREE_STR_MAX_LEN];
        strncpy(free_str, (char*)&romSect[verOffset + 0x10], str_len);
        free_str[str_len] = '\0';
        if (sscanf((char*)free_str, "%d", &svnv) == 1)
        {
            romInfo->exp_rom_ver[0] = svnv;
        }

        tmp_ba = __le32_to_cpu(*((u_int32_t*)&romSect[0x18]));
        u_int32_t dev_id_off = u_int32_t(tmp_ba.range(15, 0)) + 4;

        if (dev_id_off >= romSect.size())
        {
            return errmsg("The device ID offset %#x is out of range. ROM size: %#x", dev_id_off,
                          (u_int32_t)romSect.size());
        }

        // get devid
        tmp_ba = __le32_to_cpu(*((u_int32_t*)&romSect[dev_id_off]));
        romInfo->exp_rom_dev_id = u_int32_t(tmp_ba.range(31, 16));
        u_int32_t vendor_id = u_int32_t(tmp_ba.range(15, 0));

        if (vendor_id != MELLANOX_VENDOR_ID)
        {
            expRomWarning = true;
            snprintf(expRomWarningMsg, MAX_ROM_ERR_MSG_LEN,
                     "The Exp-ROM PCI vendor ID: %#x does not match the expected value: %#x.", vendor_id,
                     MELLANOX_VENDOR_ID);
        }
    }
    return true;
}

bool FwOperations::ReadBinFile(const char* fimage, u_int8_t*& file_data, int& file_size)
{
#ifndef UEFI_BUILD
    FILE* fh;

    if ((fh = fopen(fimage, "rb")) == NULL)
    {
        return errmsg("Can not open %s: %s\n", fimage, strerror(errno));
    }

    if (fseek(fh, 0, SEEK_END) < 0)
    {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }

    int read_file_size = ftell(fh);
    if (read_file_size < 0)
    {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }
    rewind(fh);

    file_size = read_file_size;
    file_data = new u_int8_t[file_size];
    if (fread(file_data, 1, read_file_size, fh) != (size_t)read_file_size)
    {
        delete[] file_data;
        fclose(fh);
        return errmsg("Failed to read from %s: %s\n", fimage, strerror(errno));
    }
    fclose(fh);
    return true;
#else
    return errmsg("Not implemented.\n");
#endif
}

void FwOperations::SetDevFlags(chip_type_t chipType, u_int32_t devType, fw_img_type_t fwType, bool& ibDev, bool& ethDev)
{
    (void)devType;
    ibDev = (fwType == FIT_FS3 && chipType != CT_SPECTRUM) || (chipType == CT_CONNECTX && !CntxEthOnly(devType));
    ethDev = (chipType == CT_CONNECTX) || (chipType == CT_CONNECTX4) || (chipType == CT_CONNECTX4_LX) ||
             (chipType == CT_CONNECTX5) || (chipType == CT_CONNECTX6) || (chipType == CT_CONNECTX6DX) ||
             (chipType == CT_CONNECTX6LX) || (chipType == CT_SPECTRUM) || (chipType == CT_SPECTRUM2) ||
             (chipType == CT_SPECTRUM3) || (chipType == CT_CONNECTX7) || (chipType == CT_QUANTUM2) ||
             (chipType == CT_QUANTUM3) || (chipType == CT_SPECTRUM4) || (chipType == CT_SPECTRUM5) || (chipType == CT_SPECTRUM6) || (chipType == CT_BLUEFIELD) ||
             (chipType == CT_BLUEFIELD2) || (chipType == CT_BLUEFIELD3) || (chipType == CT_CONNECTX8) ||
             (chipType == CT_CONNECTX8_PURE_PCIE_SWITCH) ||  (chipType == CT_CONNECTX9) || (chipType == CT_CONNECTX9_PURE_PCIE_SWITCH) ||(chipType == CT_BLUEFIELD4);

    if ((!ibDev && !ethDev) || chipType == CT_UNKNOWN)
    {
        // Unknown device id - for forward compat - assume that ConnectX is MP and
        // prev HCAs are IB only (these flags are for printing only - no real harm can be done).
        // TODO: FS2 does not mean ConnectX now.
        ibDev = true;
        if (fwType == FIT_FS2)
        {
            ethDev = true;
        }
        else
        {
            ethDev = false;
        }
    }
}

bool FwOperations::IsFwSupportingRomModify(const FwVersion& fw_ver)
{
    FwVersion mod(MAJOR_MOD_ROM_FW, MINOR_MOD_ROM_FW, SUBMINOR_MOD_ROM_FW);
    // only used in connectx (FS2)
    return fw_ver.compare_master_version(mod) >= 0;
}

bool FwOperations::checkMatchingExpRomDevId(const fw_info_t& info)
{
    /*
       if ((info.fw_info.roms_info.num_of_exp_rom > 0) && (info.fw_info.dev_type)
            && (info.fw_info.roms_info.exp_rom_com_devid != EXP_ROM_GEN_DEVID) \
            && (info.fw_info.roms_info.exp_rom_com_devid != MISS_MATCH_DEV_ID)
            && (info.fw_info.dev_type != info.fw_info.roms_info.exp_rom_com_devid)) {
        return false;
       }
       return true; */
    return checkMatchingExpRomDevId(info.fw_info.dev_type, info.fw_info.roms_info);
}

bool FwOperations::checkMatchingExpRomDevId(u_int16_t dev_type, const roms_info_t& roms_info)
{
    if ((roms_info.num_of_exp_rom > 0) && (dev_type) && (roms_info.exp_rom_com_devid != EXP_ROM_GEN_DEVID) &&
        (roms_info.exp_rom_com_devid != MISS_MATCH_DEV_ID) && (dev_type != roms_info.exp_rom_com_devid))
    {
        return false;
    }
    return true;
}

bool FwOperations::FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec, ProgressCallBack progressFunc)
{
    if (dataVec.empty())
    {
        return errmsg("no data to write.");
    }

    // check if flash is big enough
    if ((addr + dataVec.size()) > _ioAccess->get_effective_size())
    {
        return errmsg("Writing %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                      (unsigned int)(dataVec.size()), (unsigned int)addr,
                      (unsigned int)_ioAccess->get_effective_size());
    }

    if (!writeImage(progressFunc, addr, &dataVec[0], (int)dataVec.size()))
    {
        return false;
    }
    return true;
};

bool FwOperations::CreateBasicImageFromData(u_int32_t* data,
                                            u_int32_t dataSize,
                                            FwOperations** newImgOps,
                                            u_int16_t swDevId,
                                            bool isStripedImage)
{
    fwOpsParams imgOpsParams;
    memset(&imgOpsParams, 0, sizeof(imgOpsParams));
    char errBuff[1024] = {0};

    imgOpsParams.psid = (char*)NULL;
    imgOpsParams.buffHndl = data;
    imgOpsParams.buffSize = dataSize;
    imgOpsParams.errBuff = errBuff;
    imgOpsParams.errBuffSize = 1024;
    imgOpsParams.hndlType = FHT_FW_BUFF;
    imgOpsParams.swDevId = swDevId;
    *newImgOps = FwOperationsCreate(imgOpsParams);
    if (*newImgOps == NULL)
    {
        return errmsg("Internal error: Failed to create modified image: %s", errBuff);
    }
    if (!(*newImgOps)->FwVerify((VerifyCallBack)NULL, isStripedImage))
    {
        errmsg("Internal error: Modified image failed to verify: %s", (*newImgOps)->err());
        (*newImgOps)->FwCleanUp();
        delete (*newImgOps);
        return false;
    }

    return true;
};

bool FwOperations::FwBurnData(u_int32_t* data, u_int32_t dataSize, ProgressCallBack progressFunc)
{
    burnDataParamsT params;
    params.data = data;
    params.dataSize = dataSize;
    params.progressFunc = progressFunc;
    params.calcSha = false;
    return FwBurnData(params);
}
bool FwOperations::FwBurnData(burnDataParamsT& burnDataParams)
{
    u_int32_t* data = burnDataParams.data;
    u_int32_t dataSize = burnDataParams.dataSize;
    ProgressCallBack progressFunc = burnDataParams.progressFunc;
    FwOperations* newImgOps = NULL;
    ExtBurnParams burnParams = ExtBurnParams();

    if (!CreateBasicImageFromData(data, dataSize, &newImgOps))
    {
        return false;
    }

    if (burnDataParams.calcSha && !newImgOps->FwInsertSHA256((PrintCallBack)NULL))
    {
        errmsg("Inserting SHA256/SHA512 failed: %s", newImgOps->err());
        newImgOps->FwCleanUp();
        delete newImgOps;
        return false;
    }

    burnParams.updateParamsForBasicImage(progressFunc);

    if (!FwBurnAdvanced(newImgOps, burnParams))
    {
        newImgOps->FwCleanUp();
        delete newImgOps;
        return errmsg("Failed to re-burn image after modify: %s", err());
    }

    newImgOps->FwCleanUp();
    delete newImgOps;

    return true;
}

bool FwOperations::getRomsInfo(FBase* io, roms_info_t& romsInfo)
{
    std::vector<u_int8_t> romSector;
    romSector.clear();
    romSector.resize(io->get_effective_size());
    if (!io->read(0, &romSector[0], io->get_effective_size()))
    {
        return false;
    }
    RomInfo info(romSector, false);
    info.ParseInfo();
    info.initRomsInfo(&romsInfo);
    return true;
}

const char* FwOperations::expRomType2Str(u_int16_t type)
{
    switch (type)
    {
        case 0x1:
            return "CLP1";

        case 0x2:
            return "CLP2";

        case 0x3:
            return "CLP3";

        case 0x4:
            return "CLP4";

        case 0xf:
            return "CLP"; // hack as 0xf isnt always CLP (its type is defined in the free string inside the ROM)

        case 0x10:
            return "PXE";

        case 0x11:
            return "UEFI";

        case 0x12:
            return "CLP";

        case 0x13:
            return "NVMe";

        case 0x14:
            return "UEFI Virtio net";

        case 0x15:
            return "UEFI Virtio blk";

        case 0x16:
            return "PXE Virtio net";

        case 0x21:
            return "FCODE";

        default:
            return (const char*)NULL;
    }
    return (const char*)NULL;
}

bool FwOperations::FwSetCertChain(char*, u_int32_t, PrintCallBack)
{
    return errmsg("FwSetCertChain not supported.");
}

bool FwOperations::FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer)
{
    (void)timestamp;
    (void)fwVer;
    return errmsg("FwSetTimeStamp not supported.");
}

bool FwOperations::FwResetTimeStamp()
{
    return errmsg("FwResetTimeStamp not supported.");
}

bool FwOperations::IsSecureBootSupported()
{
    return errmsg("IsSecureBootSupported not supported.");
}

bool FwOperations::IsCableQuerySupported()
{
    return errmsg("Linkx Cable Query is not supported.");
}

bool FwOperations::IsLifeCycleSupported()
{
    return errmsg("IsLifeCycleSupported not supported.");
}

bool FwOperations::IsEncryptionSupported()
{
    return errmsg("IsEncryptionSupported not supported.");
}

bool FwOperations::FwBurnAdvanced(std::vector<u_int8_t> imageOps4MData,
                                  ExtBurnParams& burnParams,
                                  FwComponent::comps_ids_t ComponentId)
{
    (void)imageOps4MData;
    (void)burnParams;
    (void)ComponentId;
    return errmsg("FwBurnAdvanced not supported.");
}

bool FwOperations::FwBurnAdvanced(FwOperations* imageOps,
                                  ExtBurnParams& burnParams,
                                  FwComponent::comps_ids_t ComponentId)
{
    (void)imageOps;
    (void)burnParams;
    (void)ComponentId;
    return errmsg("FwBurnAdvanced not supported.");
}

bool FwOperations::checkAndDisableFlashWpIfRequired()
{
    u_int8_t fwType = this->FwType();
    if (fwType != FIT_FS5)
    {
        DPRINTF(("FwOperations::checkAndDisableFlashWpIfRequired not supported for fw type %d\n", fwType));
        return true; // only supported for FS5 and FS6
    }

    DPRINTF(("FwOperations::checkAndDisableFlashWpIfRequired\n"));
    bool rc = true;
    if (_ioAccess->is_flash())
    {
        if (((Flash*)_ioAccess)->get_ignore_cache_replacment())
        {
            DPRINTF(("check and disable flash wp if from bottom for selected flashes\n"));
            Flash* flash = (Flash*)_ioAccess;
            rc = flash->backup_write_protect_info(_protect_info_backup);
            if (!rc)
            {
                return errmsg("Failed to backup write protect information");
            }
            rc = flash->check_and_disable_flash_wp_if_required();
        }
    }
    return rc;
}

bool FwOperations::restoreWriteProtectInfo()
{
    DPRINTF(("FwOperations::restoreWriteProtectInfo\n"));
    u_int8_t fwType = this->FwType();
    if (fwType != FIT_FS5)
    {
        DPRINTF(("FwOperations::restoreWriteProtectInfo not supported for fw type %d\n", fwType));
        return true; // only supported for FS5 and FS6
    }

    int rc = true;
    if (_ioAccess->is_flash())
    {
        if (((Flash*)_ioAccess)->get_ignore_cache_replacment())
        {
            if (_protect_info_backup.backup_success)
            {
                DPRINTF(("restoring write protect info..\n"));
                Flash* flash = (Flash*)_ioAccess;
                rc = flash->restore_write_protect_info(_protect_info_backup);
            }
        }
    }
    return rc;
}

bool FwOperations::PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    (void)critical;
    (void)non_critical;
    return errmsg("PrepItocSectionsForCompare not supported.");
}

bool FwOperations::UpdateSection(void* new_info,
                                 fs3_section_t sect_type,
                                 bool is_sect_failsafe,
                                 CommandType cmd_type,
                                 PrintCallBack callBackFunc)
{
    (void)new_info;
    (void)sect_type;
    (void)is_sect_failsafe;
    (void)cmd_type;
    (void)callBackFunc;
    return errmsg("UpdateSection not supported.");
}
bool FwOperations::FwQueryTimeStamp(struct tools_open_ts_entry& timestamp,
                                    struct tools_open_fw_version& fwVer,
                                    bool queryRunning)
{
    (void)timestamp;
    (void)fwVer;
    (void)queryRunning;
    return errmsg("FwQueryTimeStamp not supported.");
}

Tlv_Status_t FwOperations::GetTsObj(TimeStampIFC** tsObj)
{
    (void)tsObj;
    errmsg("Unsupported FW type.");
    return TS_TIMESTAMPING_NOT_SUPPORTED;
}

bool FwOperations::FwInsertSHA256(PrintCallBack)
{
    return errmsg("FwInsertSHA256 not supported");
}

bool FwOperations::SignForFwUpdate(const char*, const MlxSign::Signer&, MlxSign::SHAType, PrintCallBack)
{
    return errmsg("SignForFwUpdate not supported");
}

bool FwOperations::FwSignWithTwoRSAKeys(const char*, const char*, const char*, const char*, PrintCallBack)
{
    return errmsg("FwSignWithTwoRSAKeys not supported");
}

bool FwOperations::FwSignWithHmac(const char*)
{
    return errmsg("FwSignWithHmac not supported");
}

bool FwOperations::SignForSecureBoot(const char*, const char*, const MlxSign::Signer&)
{
    return errmsg("SignForSecureBoot not supported");
}
bool FwOperations::openEncryptedImageAccess(const char* encrypted_image_path)
{
    (void)encrypted_image_path;
    return errmsg("openEncryptedImageAccess not supported");
}
bool FwOperations::isEncrypted(bool& is_encrypted)
{
    is_encrypted = false;
    DPRINTF(("FwOperations::isEncrypted res = FALSE\n"));
    return true;
}
bool FwOperations::FwExtractEncryptedImage(vector<u_int8_t>&, bool, bool, bool)
{
    return errmsg("FwExtractEncryptedImage not supported");
}
bool FwOperations::burnEncryptedImage(FwOperations*, ExtBurnParams&)
{
    return errmsg("Burning encrypted image not supported");
}

bool FwOperations::CheckAndSetIsReducedImage()
{
    return errmsg("CheckAndSetIsReducedImage not supported");
}

bool FwOperations::FwExtract4MBImage(vector<u_int8_t>&, bool, bool , bool, bool)
{
    return errmsg("FwExtract4MBImage not supported");
}

bool FwOperations::RestoreDevToc(vector<u_int8_t>& img,
                                 char* psid,
                                 dm_dev_id_t devid_t,
                                 const image_layout_uid_entry& base_guid,
                                 const image_layout_uid_entry& base_mac)
{
    (void)img;
    (void)psid;
    (void)devid_t;
    (void)base_guid;
    (void)base_mac;
    return errmsg("RestoreDevToc not supported");
}

bool FwOperations::FwSetPublicKeys(char* fname, PrintCallBack callBackFunc)
{
    (void)fname;
    (void)callBackFunc;
    return errmsg("FwSetPublicKeys not supported");
}

bool FwOperations::FwSetForbiddenVersions(char* fname, PrintCallBack callBackFunc)
{
    (void)fname;
    (void)callBackFunc;
    return errmsg("FwSetForbiddenVersions not supported");
}

bool FwOperations::GetRSAPublicKey(vector<u_int8_t>& key)
{
    (void)key;
    return errmsg("GetRSAPublicKey not supported");
}

bool FwOperations::FwReadBlock(u_int32_t addr, u_int32_t size, std::vector<u_int8_t>& dataVec)
{
    if (addr + size > _ioAccess->get_effective_size())
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "Reading %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                      size, (unsigned int)addr, (unsigned int)_ioAccess->get_effective_size());
    }
    // read from flash/image
    if (!_ioAccess->read(addr, &dataVec[0], size))
    {
        return errmsg(MLXFW_BAD_PARAM_ERR, "%s", _ioAccess->err());
    }
    return true;
}

// TODO - use dm_dev_is_fs3/4/5 from tools_dev_types.c and remove this function
u_int8_t FwOperations::GetFwFormatFromHwDevID(u_int32_t hwDevId)
{
    // TODO - remove QTM3/CX8/BF4/ARCUSE from FS4
    if ((hwDevId == CX3_HW_ID) || (hwDevId == CX3_PRO_HW_ID))
    {
        return FS_FS2_GEN;
    }
    else if ((hwDevId == CONNECT_IB_HW_ID) || (hwDevId == SWITCH_IB_HW_ID) || (hwDevId == CX4_HW_ID) ||
             (hwDevId == CX4LX_HW_ID) || (hwDevId == SPECTRUM_HW_ID) || (hwDevId == SWITCH_IB2_HW_ID))
    {
        return FS_FS3_GEN;
    }
    else if (hwDevId == CX5_HW_ID || hwDevId == CX6_HW_ID || hwDevId == CX6DX_HW_ID || hwDevId == CX6LX_HW_ID ||
             hwDevId == CX7_HW_ID || hwDevId == BF_HW_ID || hwDevId == BF2_HW_ID || hwDevId == BF3_HW_ID ||
             hwDevId == BF4_HW_ID || hwDevId == QUANTUM_HW_ID || hwDevId == QUANTUM2_HW_ID ||
             hwDevId == SPECTRUM4_HW_ID || hwDevId == SPECTRUM3_HW_ID || hwDevId == SPECTRUM2_HW_ID ||
             hwDevId == SPECTRUM5_HW_ID || hwDevId == GEARBOX_HW_ID || hwDevId == GB_MANAGER_HW_ID || hwDevId == ABIR_GB_HW_ID)
    {
        return FS_FS4_GEN;
    }
    else if ((hwDevId == QUANTUM3_HW_ID) || (hwDevId == CX8_HW_ID) || (hwDevId == CX8_PURE_PCIE_SWITCH_HW_ID) ||
             (hwDevId == BF4_HW_ID) || (hwDevId == ARCUSE_HW_ID) || (hwDevId == CX9_HW_ID) || (hwDevId == CX9_PURE_PCIE_SWITCH_HW_ID))
    {
        return FS_FS5_GEN;
    }
    else if ((hwDevId == SPECTRUM6_HW_ID))
    {
        return FS_FS6_GEN;
    }
    return FS_UNKNOWN_IMG;
}

const char* FwOperations::FwGetReSignMsgStr()
{
    return (const char*)NULL;
}

bool FwOperations::TestAndSetTimeStamp(FwOperations* imageOps)
{
    if (!IS_HCA(imageOps->_fwImgInfo.ext_info.chip_type))
    { // switches don't support MVTS register.
        return true;
    }
    Tlv_Status_t rc;
    Tlv_Status_t devTsQueryRc;
    bool retRc = true;
    TimeStampIFC* imgTsObj = NULL;
    TimeStampIFC* devTsObj = NULL;
    bool tsFoundOnImage = false;
    struct tools_open_ts_entry imgTs;
    struct tools_open_fw_version imgFwVer;
    struct tools_open_ts_entry devTs;
    struct tools_open_fw_version devFwVer;
    memset(&imgTs, 0, sizeof(imgTs));
    memset(&imgFwVer, 0, sizeof(imgFwVer));
    memset(&devTs, 0, sizeof(devTs));
    memset(&devFwVer, 0, sizeof(devFwVer));

    if (_ioAccess && !_ioAccess->is_flash())
    {
        // no need to test timestamp on image
        return true;
    }

    if (_fwParams.ignoreCacheRep)
    {
        // direct flash access no check is needed
        return true;
    }
    if (imageOps->_ioAccess && imageOps->_ioAccess->is_flash())
    {
        return errmsg("TestAndSetTimeStamp bad params");
    }
    if (imageOps->GetTsObj(&imgTsObj))
    {
        return errmsg("%s", imageOps->err());
    }
    rc = GetTsObj(&devTsObj);
    if (rc)
    {
        delete imgTsObj;
        return rc == TS_TIMESTAMPING_NOT_SUPPORTED ? true : false;
    }
    // check if device supports timestamping or if device is not in livefish
    devTsQueryRc = devTsObj->queryTimeStamp(devTs, devFwVer);
    if (devTsQueryRc == TS_TIMESTAMPING_NOT_SUPPORTED || devTsQueryRc == TS_UNSUPPORTED_ICMD_VERSION)
    {
        retRc = true;
        goto cleanup;
    }
    else if (devTsQueryRc && devTsQueryRc != TS_NO_VALID_TIMESTAMP)
    {
        retRc = errmsg("%s", devTsObj->err());
        goto cleanup;
    }

    // Option 1 image was timestampped need to try and set it on device
    // Option 2 image was not timestampped but device was timestampped
    rc = imgTsObj->queryTimeStamp(imgTs, imgFwVer);
    if (rc == TS_OK)
    {
        tsFoundOnImage = true;
    }
    else if (rc != TS_TLV_NOT_FOUND)
    {
        retRc = errmsg("%s", imgTsObj->err());
        goto cleanup;
    }

    if (tsFoundOnImage)
    {
        // timestamp found on image, attempt to set it on device
        rc = devTsObj->setTimeStamp(imgTs, imgFwVer);
        if (rc == TS_OK)
        {
            retRc = true;
        }
        else
        {
            retRc = errmsg("%s", devTsObj->err());
        }
    }
    else
    {
        if (devTsQueryRc == TS_NO_VALID_TIMESTAMP)
        {
            // no timestamp on image and no valid timestamp on device check if we got running timestamp if we do then
            // fail
            devTsQueryRc = devTsObj->queryTimeStamp(devTs, devFwVer, true);
            if (devTsQueryRc == TS_OK)
            {
                // we got running timestamp return error
                retRc = errmsg("No valid timestamp detected. please set a valid timestamp on image/device or reset "
                               "timestamps on device.");
            }
            else if (devTsQueryRc == TS_NO_VALID_TIMESTAMP)
            {
                // timestamping not used on device.
                retRc = true;
            }
            else
            {
                retRc = errmsg("%s", devTsObj->err());
            }
        }
        else
        {
            fw_info_t fw_query;
            memset(&fw_query, 0, sizeof(fw_info_t));
            if (!imageOps->FwQuery(&fw_query, true))
            {
                return errmsg("Failed to query the image\n");
            }
            // we got a valid timestamp on device but not on image! compare the FW version
            if (devFwVer.fw_ver_major == fw_query.fw_info.fw_ver[0] &&
                devFwVer.fw_ver_minor == fw_query.fw_info.fw_ver[1] &&
                devFwVer.fw_ver_subminor == fw_query.fw_info.fw_ver[2])
            {
                // versions match allow update
                retRc = true;
            }
            else
            {
                retRc = errmsg("Stamped FW version mismatch: %d.%d.%04d differs from %d.%d.%04d", devFwVer.fw_ver_major,
                               devFwVer.fw_ver_minor, devFwVer.fw_ver_subminor, fw_query.fw_info.fw_ver[0],
                               fw_query.fw_info.fw_ver[1], fw_query.fw_info.fw_ver[2]);
            }
        }
    }
cleanup:
    delete imgTsObj;
    delete devTsObj;
    return retRc;
}

FwVersion FwOperations::createFwVersion(u_int16_t fw_ver0, u_int16_t fw_ver1, u_int16_t fw_ver2)
{
    return FwVersion(fw_ver0, fw_ver1, fw_ver2);
}
FwVersion FwOperations::createFwVersion(const fw_info_com_t* fwInfo)
{
    return FwVersion(fwInfo->fw_ver[0], fwInfo->fw_ver[1], fwInfo->fw_ver[2], fwInfo->branch_ver);
}

FwVersion FwOperations::createRunningFwVersion(const fw_info_com_t* fwInfo)
{
    return FwVersion(fwInfo->running_fw_ver[0], fwInfo->running_fw_ver[1], fwInfo->running_fw_ver[2],
                     fwInfo->running_branch_ver);
}

bool FwOperations::CreateSignatureManager()
{
    if (IsFsCtrlOperations())
    { // FW control device
        if (_fwImgInfo.ext_info.chip_type == CT_UNKNOWN)
        {
            return errmsg("CreateSignatureManager: Unknown chip type\n");
        }
        _signatureMngr = SignatureManagerFactory::GetInstance()->CreateSignatureManager(_fwImgInfo.ext_info.chip_type);
        return true;
    }
    // here ioAccess must be initialized
    if (_ioAccess == NULL)
    {
        return errmsg("CreateSignatureManager: ioAccess is NULL\n");
    }
    u_int32_t hwDevId = 0;
    if (_ioAccess->is_flash())
    { // device
        hwDevId = GetHwDevId();
        _signatureMngr =
          SignatureManagerFactory::GetInstance()->CreateSignatureManager(hwDevId, _fwImgInfo.ext_info.dev_rev);
        return true;
    }
    else
    { // BIN file
        // For images we get the AbstractSignatureManager (base class) since we don't know the chip type in this stage
        _signatureMngr = SignatureManagerFactory::GetInstance()->CreateSignatureManager(CT_UNKNOWN);
        return true;
    }
    return false;
}
bool FwOperations::storeSecureBootSignaturesInSection(vector<u_int8_t>, vector<u_int8_t>, vector<u_int8_t>)
{
    return errmsg("storeSecureBootSignaturesInSection not supported");
}
bool FwOperations::getExtendedHWAravaPtrs(VerifyCallBack, FBase*, bool, bool)
{
    return errmsg("getExtendedHWAravaPtrs not supported");
}
u_int32_t FwOperations::GetPublicKeySecureBootPtr()
{
    return errmsg("GetPublicKeySecureBootPtr not supported");
}

bool FwOperations::VerifyBranchFormat(const char* vsdString)
{
    size_t length = strlen(vsdString);
    if (length > BRANCH_LEN || length < MIN_BRANCH_LEN)
    {
        return false;
    }
    if (vsdString[length - MIN_BRANCH_LEN] == '_')
    {
        for (size_t i = length - MIN_BRANCH_LEN + 1; i < length; i++)
        {
            if (!isdigit(vsdString[i]))
            {
                return false;
            }
        }
        return true;
    }
    else if (vsdString[length - MIN_BRANCH_LEN + 1] == '-')
    {
        for (size_t i = length - MIN_BRANCH_LEN + 2; i < length; i++)
        {
            if (!isdigit(vsdString[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool FwOperations::GetDtocAddress(u_int32_t&)
{
    return errmsg("GetDtocAddress not supported.");
}

bool FwOperations::PrintQuery()
{
    return errmsg("PrintQuery not supported.");
}

bool FwOperations::IsLifeCycleAccessible(chip_type_t)
{
    return errmsg("IsLifeCycleAccessible not supported.");
}

bool FwOperations::IsSecurityVersionViolated(u_int32_t)
{
    return false;
}

bool FwOperations::GetImageSize(u_int32_t*)
{
    return errmsg("GetImageSize is not supported");
}
bool FwOperations::GetHashesTableData(vector<u_int8_t>&)
{
    return errmsg("GetHashesTableData is not supported");
}

bool FwOperations::QueryComponentData(FwComponent::comps_ids_t, u_int32_t, vector<u_int8_t>&)
{
    return errmsg("GetComponentData is not supported");
}

bool FwOperations::ReadMccComponent(vector<u_int8_t>&, FwComponent::comps_ids_t, ProgressCallBackAdvSt*)
{
    return errmsg("ReadMccComponent is not supported");
}

bool FwOperations::IsCompatibleToDevice(vector<u_int8_t>&, u_int8_t)
{
    return errmsg("IsCompatibleToDevice is not supported");
}

bool FwOperations::GetSecureHostState(u_int8_t&)
{
    return errmsg("GetSecureHostState is not supported");
}

bool FwOperations::ChangeSecureHostState(bool, u_int64_t)
{
    return errmsg("ChangeSecureHostState is not supported");
}

bool FwOperations::GetNcoreData(vector<u_int8_t>&)
{
    return errmsg("GetNcoreData is not supported");
}

bool FwOperations::IsComponentSupported(FwComponent::comps_ids_t)
{
    return errmsg("IsComponentSupported is not supported");
}

bool FwOperations::IsExtendedGuidNumSupported()
{
    bool isSupported = false;
    switch (_fwImgInfo.supportedHwId[0])
    {
        case SPECTRUM4_HW_ID:
        case SPECTRUM5_HW_ID:
        case SPECTRUM6_HW_ID:
        case QUANTUM3_HW_ID:
            isSupported = true;
            break;
        default:
            isSupported = false;
            break;
    }
    return isSupported;
}

#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
bool FwOperations::CheckPemKeySize(const string privPemFileStr, u_int32_t& keySize)
{
    MlxSignRSA rsa;
    vector<u_int8_t> section(1, 64);
    vector<u_int8_t> encSha;
    vector<u_int8_t> sha;
    int rc = rsa.setPrivKeyFromFile(privPemFileStr);
    if (rc)
    {
        return false;
    }
    MlxSignSHA512 mlxSignSHA;
    mlxSignSHA << section;
    mlxSignSHA.getDigest(sha);
    rc = rsa.sign(MlxSign::SHA512, sha, encSha);
    if (rc)
    {
        return false;
    }
    keySize = encSha.size();
    return true;
}
#endif

CRSpaceRegisters::CRSpaceRegisters(mfile* mf, chip_type_t chip_type) : _mf(mf), _chip_type(chip_type) {}

life_cycle_t CRSpaceRegisters::getLifeCycle()
{
    size_t lifeCycleAddress = 0;
    u_int8_t firstBit = 0;
    u_int8_t bitLen = 0;
    life_cycle_t lifeCycle;
    lifeCycle.version_field = 0;

    switch (_chip_type)
    {
        case CT_CONNECTX6:
            lifeCycleAddress = 0xf0060;
            firstBit = 0;
            bitLen = 2;
            break;
        case CT_BLUEFIELD2:
        case CT_CONNECTX6DX:
        case CT_CONNECTX6LX:
            lifeCycleAddress = 0xf0068;
            firstBit = 0;
            bitLen = 2;
            break;
        case CT_CONNECTX7:
        case CT_QUANTUM2:
        case CT_BLUEFIELD3:
        case CT_BLUEFIELD4:
        case CT_SPECTRUM4:
        case CT_SPECTRUM5:
            lifeCycleAddress = 0xf0000;
            firstBit = 4;
            bitLen = 2;
            break;
        case CT_SPECTRUM6:
            lifeCycleAddress = 0xf0000;
            firstBit = 16;
            bitLen = 5;
            break;
        case CT_CONNECTX8:
        case CT_CONNECTX9:
        case CT_CONNECTX8_PURE_PCIE_SWITCH:
        case CT_CONNECTX9_PURE_PCIE_SWITCH:
        case CT_QUANTUM3:
        case CT_ARCUSE:
            lifeCycleAddress = 0xf0000;
            firstBit = 16;
            bitLen = 3;
            lifeCycle.version_field = 1;
            break;
        default:
            throw logic_error("-E- life_cycle query is not implemented for the current device.");
            break;
    }

    lifeCycle.value = getConsecutiveBits(getRegister(lifeCycleAddress), firstBit, bitLen);

    return lifeCycle;
}

bool CRSpaceRegisters::IsLifeCycleSecured(life_cycle_t life_cycle)
{
    if (life_cycle.version_field == 1)
    {
        return (life_cycle.value == FS5_LC_PRE_PRODUCTION || life_cycle.value == FS5_LC_PRODUCTION);
    }
    else
    {
        return life_cycle.value == FS4_LC_GA_SECURED;
    }
}

bool CRSpaceRegisters::IsLifeCycleSecured()
{
    return IsLifeCycleSecured(getLifeCycle());
}

int CRSpaceRegisters::getGlobalImageStatus()
{
    size_t global_image_status_address = 0;

    switch (_chip_type)
    {
        case CT_CONNECTX6:
        case CT_CONNECTX6DX:
        case CT_CONNECTX6LX:
        case CT_CONNECTX7:
        case CT_BLUEFIELD2:
        case CT_BLUEFIELD3:
        case CT_BLUEFIELD4:
            global_image_status_address = 0xE3044;
            break;
        case CT_CONNECTX8:
        case CT_CONNECTX8_PURE_PCIE_SWITCH:
        case CT_CONNECTX9:
        case CT_CONNECTX9_PURE_PCIE_SWITCH:
            global_image_status_address = 0x55084;
            break;
        case CT_QUANTUM2:
        case CT_QUANTUM3:
            global_image_status_address = 0x152080;
            break;
        case CT_SPECTRUM4:
        case CT_SPECTRUM5:
            global_image_status_address = 0xa1844;
            break;
        case CT_SPECTRUM6:
            global_image_status_address = 0x155004;
            break;
        default:
            throw logic_error("-E- global_image_status query is not implemented for the current device.");
            break;
    }

    return (int)getRegister(global_image_status_address);
}

u_int32_t CRSpaceRegisters::getSecurityVersion()
{
    u_int32_t securityVersion = 0;
    u_int32_t rollbackMSB = 0, rollbackLSB = 0;
    u_int32_t minimalSecurityVersion = 0;

    switch (_chip_type)
    {
        case CT_QUANTUM2:
        case CT_QUANTUM3:
            rollbackMSB = getRegister(0xf3248);
            rollbackLSB = getRegister(0xf324c);
            minimalSecurityVersion = getConsecutiveBits(getRegister(0xf3238), 3, 8);
            break;
        case CT_BLUEFIELD3:
            rollbackMSB = getRegister(0xf4348);
            rollbackLSB = getRegister(0xf434c);
            minimalSecurityVersion = getConsecutiveBits(getRegister(0xf4338), 4, 8);
            break;
        case CT_SPECTRUM4:
        case CT_SPECTRUM5:
        case CT_SPECTRUM6:
            rollbackMSB = getRegister(0xf4348);
            rollbackLSB = getRegister(0xf434c);
            minimalSecurityVersion = getConsecutiveBits(getRegister(0xf4338), 0, 8);
            break;
        case CT_CONNECTX7:
            rollbackMSB = getRegister(0xf4548);
            rollbackLSB = getRegister(0xf454c);
            minimalSecurityVersion = getConsecutiveBits(getRegister(0xf4538), 4, 8);
            break;
        default:
            throw logic_error("-E- Security version query is not implemented for the current device.");
            break;
    }

    securityVersion = countSetBits(rollbackMSB) + countSetBits(rollbackLSB) + minimalSecurityVersion;
    return securityVersion;
}

u_int32_t CRSpaceRegisters::countSetBits(u_int32_t num)
{
    u_int32_t count = 0;
    while (num)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

u_int32_t CRSpaceRegisters::getConsecutiveBits(u_int32_t data, u_int8_t firstBit, u_int8_t numOfBits)
{
    u_int32_t mask = 0xffffffff;
    mask = mask >> (32 - numOfBits);
    data = data >> firstBit;
    data = data & mask;
    return data;
}

u_int32_t CRSpaceRegisters::getRegister(u_int32_t address)
{
    u_int32_t crSpaceReg = 0;
    int rc = mread4(_mf, address, &crSpaceReg);
    if (rc != 4)
    {
        throw runtime_error("-E- Failed to read from CRSpace.");
    }

    return crSpaceReg;
}

bool FwOperations::getBFBComponentsVersions(std::map<std::string, std::string>&, bool)
{
    return errmsg("getBFBComponentsVersions is not supported");
}
