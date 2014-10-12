/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
#include "fs3_ops.h"
#include "fs2_ops.h"


#ifndef NO_MFA_SUPPORT
#include <mfa.h>
#endif

#define BAD_CRC_MSG "Bad CRC."
extern const char* g_sectNames[];

#ifndef NO_MFA_SUPPORT

int FwOperations::getFileSignature(const char* fname)
{
    FILE* fin;
    char tmpb[16];
    int res = 0;

    if (!(fin = fopen(fname, "r"))) {
        // abit ugly , need to establish a correct ret val
        return IMG_SIG_OPEN_FILE_FAILED;
    }
    if (!fgets(tmpb, sizeof(tmpb), fin)) {
        goto clean_up;
    }
    if (strlen(tmpb) < 4) {
        goto clean_up;
    }

    if (!strncmp(tmpb, "MTFW", 4)) {
        res = IMG_SIG_TYPE_BIN;
    }
    if (!strncmp(tmpb, "MFAR", 4)) {
        res = IMG_SIG_TYPE_MFA;
    }

clean_up:
    fclose(fin);
    return res;
}


int FwOperations::getBufferSignature(u_int8_t* buf, u_int32_t size)
{
    int res = 0;

    if (size < 4) {
        return 0;
    }
    if (!strncmp((char*)buf, "MTFW", 4)) {
        res = IMG_SIG_TYPE_BIN;
    }
    if (!strncmp((char*)buf, "MFAR", 4)) {
        res = IMG_SIG_TYPE_MFA;
    }

    return res;
}

const char * FwOperations::err2str(int errNum)
{
    switch(errNum) {
        case -4:
            return "Found MFA(s) with higher Version, upgrade tool to work with it";
        case -3:
            return "File Signature is invalid";
        default:
            return "Failed to get MFA Image";
    }
}
int FwOperations::getMfaImg(char* fileName, char *psid, u_int8_t **imgbuf)
{
    int res;
    mfa_desc* mfa_d;
    int image_type = 1; //FW image

    if (psid == NULL) {
        return -1; //No psid => no image
    }

    if ((res = mfa_open_file(&mfa_d, fileName))) {
        res = res < 0 ? res : -1 * res;
        return res;
    }

    res = mfa_get_image(mfa_d, psid, image_type, (char*)"", imgbuf);

    mfa_close(mfa_d);
    return res;
}


int FwOperations::getMfaImg(u_int8_t* mfa_buf, int size, char *psid, u_int8_t **imgbuf)
{
    int res;
    mfa_desc* mfa_d;
    int image_type = 1; //FW image

    if (psid == NULL) {
        return -1; //No psid => no image
    }
    if ((res = mfa_open_buf(&mfa_d, mfa_buf, size))) {
        res = res < 0 ? res : -1 * res;
        return res;
    }

    res = mfa_get_image(mfa_d, psid, image_type, (char*)"", imgbuf);

    mfa_close(mfa_d);
    return res;
}
#endif


void FwOperations::FwCleanUp()
{
    _ioAccess->close();
    delete _ioAccess;
    if (_fname != NULL) {
        delete[] _fname;
    }
    if (_devName != NULL) {
        delete[] _devName;
    }
}


void FwOperations::FwInitCom()
{
    memset(&_fwImgInfo, 0, sizeof(_fwImgInfo));
}


void FwOperations::getSupporteHwId(u_int32_t **supportedHwId, u_int32_t &supportedHwIdNum)
{
    *supportedHwId    = _fwImgInfo.supportedHwId;
    supportedHwIdNum = _fwImgInfo.supportedHwIdNum;

}

bool FwOperations::checkBoot2(u_int32_t beg, u_int32_t offs, u_int32_t& next, bool fullRead, const char *pref, VerifyCallBack verifyCallBackFunc)
{
    u_int32_t    size;

    // char         *pr = (char *)alloca(strlen(pref) + 512);
    char pr[strlen(pref) + 512];
    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs+beg);
    // Size
    READ4((*_ioAccess), offs+beg+4, &size, pr);
    TOCPU1(size);
    if (size > 1048576 || size < 4) {
        report_callback(verifyCallBackFunc, "%s /0x%08x/ - unexpected size (0x%x)\n", pr, offs+beg+4, size);
        return false;
    }
    _fwImgInfo.bootSize = (size + 4) * 4;

    // Get absolute address on flash when checking BOOT2 for FS3 image format (for FS2 its always displayed as contiguous)
    // Adrianc: why dont we show them both in the same way when running verify.
    u_int32_t boot2AbsAddr = (this->FwType() == FIT_FS3 && _ioAccess->is_flash()) ? \
            _ioAccess->get_phys_from_cont(beg, _fwImgInfo.cntxLog2ChunkSize, (_fwImgInfo.imgStart != 0)) : beg;

    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, offs+boot2AbsAddr,
            offs+boot2AbsAddr+(size+4)*4-1, (size+4)*4);

    if ((_ioAccess->is_flash() && fullRead == true) || !_ioAccess->is_flash()) {
        Crc16        crc;
        // u_int32_t    *buff = (u_int32_t*)alloca((size + 4)*sizeof(u_int32_t));
        u_int32_t buff[size + 4];
        READBUF((*_ioAccess), offs+beg, buff, size*4 + 16, pr);
        // we hold for FS3 an image cache so we selectevely update it in UpdateImgCache() call
        UpdateImgCache((u_int8_t*)buff, offs+beg, size*4 + 16);

        TOCPUn(buff, size+4);
        CRC1n(crc, buff, size+4);
        CRC1n(_ioAccess->get_image_crc(), buff, size+4);


        crc.finish();

        u_int32_t crc_act = buff[size+3];
        if (crc.get() != crc_act) {
            report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
                   pr, offs+beg, crc.get(), crc_act);
            return errmsg(BAD_CRC_MSG);
        }
        _ioAccess->get_image_crc() << crc_act;
        // TODO: Print CRC
        if (0) {
            report_callback(verifyCallBackFunc, "%s - OK (CRC:0x%04x)\n", pr, (crc_act & 0xffff));
        } else {
            report_callback(verifyCallBackFunc, "%s - OK\n", pr);
        }
    }
    next = offs + size*4 + 16;
    return true;
} // checkBoot2


bool FwOperations::CheckAndPrintCrcRes(char* pr, bool blank_crc, u_int32_t off, u_int32_t crc_act, u_int32_t crc_exp, bool ignore_crc,
         VerifyCallBack verifyCallBackFunc)
{

    if (!blank_crc && crc_exp != crc_act) {
        report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
               pr, off, crc_exp, crc_act);
        return errmsg(BAD_CRC_MSG);
    }
    // if (_print_crc) {
    // TODO: Print CRC here.
    if (0) {
        report_callback(verifyCallBackFunc, "%s - OK (CRC:0x%04x)\n", pr, crc_act & 0xffff);
    } else {
        if (ignore_crc) {
            report_callback(verifyCallBackFunc, "%s - CRC IGNORED\n", pr);
        } else {
            if (blank_crc) {
                report_callback(verifyCallBackFunc, "%s - BLANK CRC (0xffff)\n", pr);
            } else {
                report_callback(verifyCallBackFunc, "%s - OK\n", pr);
            }
        }
    }
    return true;
}

bool FwOperations::FwVerLessThan(u_int16_t r1[3], u_int16_t r2[3]) {
    for (int i = 0; i < 3 ; i++)
        if (r1[i] < r2[i])
            return true;
        else if (r1[i] > r2[i])
            return false;

    return false; // equal versions
}
const u_int32_t FwOperations::_cntx_magic_pattern[4] = {
    0x4D544657,   // Ascii of "MTFW"
    0x8CDFD000,   // Random data
    0xDEAD9270,
    0x4154BEEF
};

const u_int32_t FwOperations::_cntx_image_start_pos[FwOperations::CNTX_START_POS_SIZE] = {
    0,
    0x10000,
    0x20000,
    0x40000,
    0x80000,
    0x100000,
    0x200000
};

bool FwOperations::CntxFindMagicPattern (FBase* ioAccess, u_int32_t addr) {
    if (addr + 16 > ioAccess->get_size()) {
        return false;
    }
    for (int i = 0; i < 4 ; i++) {
        u_int32_t w;
        READ4_NOERRMSG((*ioAccess), addr + i * 4, &w);
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
bool FwOperations::CntxFindAllImageStart (FBase* ioAccess, u_int32_t start_locations[CNTX_START_POS_SIZE], u_int32_t* found_images) {
    int needed_pos_num;

    needed_pos_num = CNTX_START_POS_SIZE;

    if (ioAccess->is_flash()) {
        if ( (((Flash*)ioAccess)->get_dev_id() == 400) ||
             (((Flash*)ioAccess)->get_dev_id() == 435) ||
             (((Flash*)ioAccess)->get_dev_id() == 6100)) {
            needed_pos_num = OLD_CNTX_START_POS_SIZE;
        }
    }

    ioAccess->set_address_convertor(0,0);
    *found_images = 0;
    for (int i = 0; i < needed_pos_num; i++) {
        if (CntxFindMagicPattern(ioAccess, _cntx_image_start_pos[i])) {
            start_locations[*found_images] = _cntx_image_start_pos[i];
            (*found_images)++;
        }
    }

    return true;
}



// CAN BE IN ANOTHER MODULE
bool FwOperations::GetSectData(std::vector<u_int8_t>& file_sect, const u_int32_t *buff, const u_int32_t size) {

    file_sect.clear();
    file_sect.insert(file_sect.end(),
                     (u_int8_t*)buff,
                     (u_int8_t*)buff + size);


    return true;
}


bool FwOperations::FwAccessCreate(fw_ops_params_t& fwParams, FBase **ioAccessP)
{
    // FBase *ioAccess = *ioAccessP;
    if (fwParams.hndlType == FHT_FW_FILE) {
#ifndef NO_MFA_SUPPORT
        int sig = getFileSignature(fwParams.fileHndl);
        if (sig == IMG_SIG_OPEN_FILE_FAILED) { //i.e we failed to open file
            WriteToErrBuff(fwParams.errBuff, strerror(errno), fwParams.errBuffSize);
            return false;
        }
        if (sig == IMG_SIG_TYPE_BIN) {
            *ioAccessP = new FImage;
            if (!(*ioAccessP)->open(fwParams.fileHndl, false, !fwParams.shortErrors)) {
                WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
        } else if (sig == IMG_SIG_TYPE_MFA) {
            u_int8_t* imgbuf;
            int sz;
            if ((sz = getMfaImg(fwParams.fileHndl, fwParams.psid, &imgbuf)) < 0) {
                WriteToErrBuff(fwParams.errBuff, err2str(sz), fwParams.errBuffSize);
                return false;
            }
            *ioAccessP = new FImage;
            if (!((FImage*)(*ioAccessP))->open((u_int32_t*)imgbuf, (u_int32_t)sz, !fwParams.shortErrors)) {
                mfa_release_image(imgbuf);
                WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
            mfa_release_image(imgbuf);
        } else {
            WriteToErrBuff(fwParams.errBuff,"Invalid Image signature.", fwParams.errBuffSize);
            return false; //Unknown signature
        }
#else
        *ioAccessP = new FImage;
        if (!(*ioAccessP)->open(fwParams.fileHndl, false, !fwParams.shortErrors)) {
            WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
#endif
    } else if (fwParams.hndlType == FHT_FW_BUFF) {
        u_int32_t numInfo = fwParams.buffSize;
#ifndef NO_MFA_SUPPORT
        int sig = getBufferSignature((u_int8_t*)fwParams.buffHndl, numInfo);
        if (sig == IMG_SIG_TYPE_BIN) {
            *ioAccessP = new FImage;
            if (!((FImage*)*ioAccessP)->open(fwParams.buffHndl, (u_int32_t)numInfo, !fwParams.shortErrors)) {
                WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
        } else if (sig == IMG_SIG_TYPE_MFA) {
            u_int8_t* imgbuf;
            int sz;
            if ((sz = getMfaImg((u_int8_t*)fwParams.buffHndl, numInfo, fwParams.psid, &imgbuf)) < 0) {
                WriteToErrBuff(fwParams.errBuff, err2str(sz), fwParams.errBuffSize);
                return false;
            }
            *ioAccessP = new FImage;
            if (!((FImage*)*ioAccessP)->open((u_int32_t*)imgbuf, (u_int32_t)sz, !fwParams.shortErrors)) {
                mfa_release_image(imgbuf);
                WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
                delete *ioAccessP;
                return false;
            }
            mfa_release_image(imgbuf);
        } else {
            WriteToErrBuff(fwParams.errBuff,"Invalid Image signature.", fwParams.errBuffSize);
            return false;//Unknown signature
        }
#else
        *ioAccessP = new FImage;
        if (!((FImage*)*ioAccessP)->open(fwParams.buffHndl, numInfo, !fwParams.shortErrors)) {
            WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
#endif
    } else if (fwParams.hndlType == FHT_UEFI_DEV) {
        *ioAccessP = new Flash;
        if (!((Flash*)*ioAccessP)->open(fwParams.uefiHndl, fwParams.uefiExtra, false, !fwParams.shortErrors)) {
            WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
    } else if (fwParams.hndlType == FHT_MST_DEV) {
        *ioAccessP = new Flash;
        if ( !((Flash*)*ioAccessP)->open(fwParams.mstHndl, fwParams.forceLock, fwParams.readOnly, fwParams.numOfBanks,\
                                          fwParams.flashParams, fwParams.ignoreCacheRep, !fwParams.shortErrors)) {
            // TODO: release memory here ?
            WriteToErrBuff(fwParams.errBuff,(*ioAccessP)->err(), fwParams.errBuffSize);
            delete *ioAccessP;
            return false;
        }
        //set no flash verify if needed (default =false)
        ((Flash*)*ioAccessP)->set_no_flash_verify(fwParams.noFlashVerify);
     } else {
         WriteToErrBuff(fwParams.errBuff,"Unknown Handle Type.", fwParams.errBuffSize);
         return false;
     }
    return true;
}

u_int8_t FwOperations::CheckFwFormat(FBase& f, bool getFwFormatFromImg) {
    if (f.is_flash() && !getFwFormatFromImg) {
        if (  ( ((Flash*)&f)->get_dev_id() == 400)              ||
                ( ((Flash*)&f)->get_dev_id() == 435)              ||
                ( ((Flash*)&f)->get_dev_id() == CX3_HW_ID)        ||
                ( ((Flash*)&f)->get_dev_id() == SWITCHX_HW_ID)    ||
                ( ((Flash*)&f)->get_dev_id() == 6100) ||
                ( ((Flash*)&f)->get_dev_id() == CX3_PRO_HW_ID)) {
            return FS_FS2_GEN;
        } else if ( (((Flash*)&f)->get_dev_id() == CONNECT_IB_HW_ID) ||
                    (((Flash*)&f)->get_dev_id() == SWITCH_IB_HW_ID) ||
		    (((Flash*)&f)->get_dev_id() == CX4_HW_ID)) {
            return FS_FS3_GEN;
        }
    } else {
        u_int32_t found_images;
        u_int32_t image_start[CNTX_START_POS_SIZE];

        // Image - check if magic pattern is somewhere in the file:
        CntxFindAllImageStart(&f, image_start, &found_images);
        if (found_images) {
            u_int32_t data;
            u_int8_t image_version;
            READ4_NOERRMSG(f, FS3_IND_ADDR, &data);
            TOCPU1(data);
            image_version = data >> 24;
            if (image_version == IMG_VER_FS3) {
                return FS_FS3_GEN;
            } else {
                // TODO: if the img format version is unknown we should fail instead of considering it FS2
                return FS_FS2_GEN;
            }
        }
    }
    return FS_OLD_GEN;
}

FwOperations* FwOperations::FwOperationsCreate(void* fwHndl, void *info, char* psid, fw_hndl_type_t hndlType, char* errBuff, int buffSize)
{
    fw_ops_params_t fwParams;
    fwParams.psid = psid;
    fwParams.hndlType = hndlType;
    fwParams.errBuff = errBuff;
    fwParams.errBuffSize = buffSize;
    fwParams.shortErrors = true;

    if (hndlType == FHT_FW_FILE) {
        fwParams.fileHndl = (char*)fwHndl;
    }else if (hndlType == FHT_FW_BUFF) {
        fwParams.buffHndl = (u_int32_t*)fwHndl;
        fwParams.buffSize = *((u_int32_t*)info);
    }else if (hndlType == FHT_UEFI_DEV) {
        fwParams.uefiHndl = (uefi_Dev_t*)fwHndl;
        fwParams.uefiExtra = (f_fw_cmd)info;
    }else if (hndlType == FHT_MST_DEV) {
        fwParams.mstHndl = (char*)fwHndl;
        fwParams.forceLock = false;
        fwParams.readOnly = false;
        fwParams.numOfBanks = -1;
        fwParams.flashParams = (flash_params_t*)NULL;
        fwParams.ignoreCacheRep = 0;
        fwParams.noFlashVerify = false;
    }
    return FwOperationsCreate(fwParams);
}

FwOperations* FwOperations::FwOperationsCreate(fw_ops_params_t& fwParams)
{
    FwOperations* fwops;
    u_int8_t fwFormat;
    FBase *ioAccess;
    bool getFwFormatFromImg = false;

    if (!FwAccessCreate(fwParams, &ioAccess)) {
        return (FwOperations*)NULL;
    }
    if (fwParams.hndlType == FHT_UEFI_DEV) {
        // IN UEFI we don't have an access to read devID from cr-space so we are reading it from FW  image signature
        getFwFormatFromImg = true;
    }
    fwFormat = CheckFwFormat(*ioAccess, getFwFormatFromImg);
    switch (fwFormat) {
        case FS_FS2_GEN: {
            fwops = new Fs2Operations(ioAccess);
            break;
        }
        case FS_FS3_GEN: {
            fwops = new Fs3Operations(ioAccess);
            break;
        }
        default:
            delete ioAccess;
            WriteToErrBuff(fwParams.errBuff,"invalid Firmware Format (found FS Gen 1)", fwParams.errBuffSize);
            return (FwOperations*)NULL;
    }
    fwops->_advErrors = !fwParams.shortErrors;
    fwops->FwInit();
    if (fwParams.hndlType == FHT_FW_FILE) {
        fwops->_fname = strcpy(new char[strlen(fwParams.fileHndl)+ 1], fwParams.fileHndl);
    }
    if (fwParams.hndlType == FHT_MST_DEV) {
        fwops->_devName = strcpy(new char[strlen(fwParams.mstHndl)+ 1], fwParams.mstHndl);
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

bool FwOperations::writeImage(ProgressCallBack progressFunc, u_int32_t addr, void *data, int cnt, bool is_phys_addr)
{
    u_int8_t   *p = (u_int8_t *)data;
    u_int32_t  curr_addr = addr;
    u_int32_t  towrite = cnt;
    bool rc;
//    if (!_ioAccess->is_flash()) {
 //       return errmsg("Internal error: writeImage is supported only on flash.");
   // }
    while (towrite) {
        // Write
        int trans;
        if (_ioAccess->is_flash()) {
            trans = (towrite > (int)Flash::TRANS) ? (int)Flash::TRANS : towrite;
            if (is_phys_addr) {
                rc = ((Flash*)_ioAccess)->write_phy(curr_addr, p, trans);
            } else {
                rc = ((Flash*)_ioAccess)->write(curr_addr, p, trans);
            }
            if (!rc) {
                return errmsg("Flash write failed: %s", _ioAccess->err());
            }
        } else {
            trans = towrite;
            if (!ModifyImageFile(_fname, curr_addr, p, trans)) {
                return false;
            }
        }
        p += trans;
        curr_addr += trans;
        towrite -= trans;

        // Report
        if (progressFunc != NULL) {
            u_int32_t new_perc = ((cnt - towrite) * 100) / cnt;

                    if (progressFunc((int)new_perc)) {
                        return errmsg("Aborting... recieved interrupt signal");
                    }
            }
        }

    return true;
} //  Flash::WriteImage

bool FwOperations::ModifyImageFile(const char *fimage, u_int32_t addr, void *data, int cnt)
{
    int file_size;
    u_int8_t * file_data;

    if (!ReadImageFile(fimage, file_data, file_size, addr + cnt)) {
        return false;
    }
    memcpy(&file_data[addr], data, cnt);

    if (!WriteImageToFile(fimage, file_data, file_size)) {
        delete[] file_data;
        return false;
    }
    delete[] file_data;
    return true;
}

bool FwOperations::WriteImageToFile(const char *file_name, u_int8_t *data, u_int32_t length)
{
    FILE* fh;
    if ((fh = fopen(file_name, "wb")) == NULL) {
        return errmsg("Can not open %s: %s\n", file_name, strerror(errno));
    }

    // Write output
    if (fwrite(data, 1, length, fh) != length) {
        fclose(fh);
        return errmsg("Failed to write to %s: %s\n", file_name, strerror(errno));
    }
    fclose(fh);
    return true;
}

bool FwOperations::CheckMac(u_int64_t mac) {
    if ((mac >> 40) & 0x1) {
        return errmsg("Multicast bit (bit 40) is set");
    }

    if (mac >> 48) {
        return errmsg("More than 48 bits are used");
    }

    return true;
}

void FwOperations::recalcSectionCrc(u_int8_t *buf, u_int32_t data_size) {

    Crc16              crc;
    for (u_int32_t i = 0; i < data_size; i += 4) {
        crc << __be32_to_cpu(*(u_int32_t*)(buf + i));
    }
    crc.finish();
    *((u_int32_t*)(buf + data_size)) = __cpu_to_be32(crc.get());
}

chip_type_t FwOperations::getChipType() {
    int i = 0;
    while (hwDevData[i].name != NULL) {
        int j = 0;
        while (hwDevData[i].swDevIds[j] != 0) {
            if (hwDevData[i].swDevIds[j] == _fwImgInfo.ext_info.dev_type) {
                    return hwDevData[i].chipType;
                }
                j++;
            }
            i++;
        }
    return CT_UNKNOWN;
}

chip_type_t FwOperations::getChipTypeFromHwDevid(u_int32_t hwDevId) {
    int i = 0;
    while (hwDevData[i].name != NULL) {
        if (hwDevData[i].hwDevId == hwDevId) {
            return hwDevData[i].chipType;
        }
            i++;
        }
    return CT_UNKNOWN;
}

// TODO:combine both databases(hwDevData and hwDev2Str) and remove old unsupporded devices i.e infinihost infinihost_iii_ex infinihost_iii_lx
const FwOperations::HwDevData FwOperations::hwDevData[] = {
    { "InfiniHost",        INFINIHOST_HW_ID, CT_UNKNOWN, 2, {23108, 0}},
    { "InfiniHost III Ex", INFINIHOST_III_EX_HW_ID, CT_UNKNOWN,2 , {25208, 25218, 0}},
    { "InfiniHost III Lx", INFINIHOST_III_LX_HW_ID, CT_UNKNOWN, 1, {25204, 0}},
    { "ConnectX",          CX_HW_ID, CT_CONNECTX, 2,  {25408, 25418, 26418, 26438,
                                         26428, 25448, 26448, 26468,
                                         25458, 26458, 26478, 26488,
                                         4097, 4098, 0}},
    { "ConnectX-3",        CX3_HW_ID, CT_CONNECTX, 2,  {4099, 4100, 4101, 4102,
                                         4104, 4105, 4106,
                                         4107, 4108, 4109, 4110,
                                         4111, 4112, 0}},
    { "ConnectX-3Pro",    CX3_PRO_HW_ID, CT_CONNECTX, 2, {4103,0}},
    { "Connect_IB",       CONNECT_IB_HW_ID, CT_CONNECT_IB, 2, {CONNECT_IB_SW_ID, 4114, 4115, 4116,
                                         4117, 4118, 4119, 4120,
                                         4121, 4122, 4123, 4124, 0}},
    { "InfiniScale IV",   IS4_HW_ID, CT_IS4, 0, {48436, 48437, 48438, 0}},
    { "BridgeX",          BRIDGEX_HW_ID, CT_BRIDGEX, 0, {64102, 64112, 64122, 0}},
    { "SwitchX",          SWITCHX_HW_ID, CT_SWITCHX, 0, {51000, 0}},
    { "Switch_IB",        SWITCH_IB_HW_ID, CT_SWITCH_IB,0, {52000, 0}},
    { "ConnectX-4",		  CX4_HW_ID,	 CT_CONNECTX,	0, {4115, 0}},
    { (char*)NULL ,              0, CT_UNKNOWN, 0, {0}},// zero devid terminator
};

const FwOperations::HwDev2Str FwOperations::hwDev2Str[] = {
        {"ConnectIB",         CONNECT_IB_HW_ID, 0x00},
        {"ConnectX",          CX_HW_ID,         0xA0},
        {"ConnectX-2",        CX_HW_ID,         0xB0},
        {"ConnectX-3 A0",     CX3_HW_ID,        0x00},
        {"ConnectX-3 A1",     CX3_HW_ID,        0x01},
        {"ConnectX-3Pro",     CX3_PRO_HW_ID,    0x00},
        {"ConnectX-4",        CX4_HW_ID,  	0x00},
        {"SwitchX A0",        SWITCHX_HW_ID,    0x00},
        {"SwitchX A1",        SWITCHX_HW_ID,    0x01},
        {"BridgeX",           BRIDGEX_HW_ID,    0xA0},
        {"InfiniScale IV A0", IS4_HW_ID,        0xA0},
        {"InfiniScale IV A1", IS4_HW_ID,        0xA1},
        {"InfiniHost A0",     INFINIHOST_HW_ID,      0xA0},
        {"InfiniHost A1",     INFINIHOST_HW_ID,      0xA1},
        {"InfiniHost III Lx", INFINIHOST_III_LX_HW_ID,      0xA0},
        {"InfiniHost III Ex", INFINIHOST_III_EX_HW_ID,      0xA0},
        {"SwitchIB A0",       SWITCH_IB_HW_ID,  0x00},
        { (char*)NULL ,       (u_int32_t)0, (u_int8_t)0x00}, // zero device ID terminator
};

#define ARR_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#define MAX_HW_NAME_LEN 100
bool FwOperations::HWIdRevToName(u_int32_t hw_id, u_int8_t rev_id, char *hw_name)
{

    for (int i = 0;  hwDev2Str[i].hwDevId != 0; i++) {
        const HwDev2Str *hwDev2StrMem = &(hwDev2Str[i]);

        if (hwDev2StrMem->hwDevId == hw_id && hwDev2StrMem->revId == rev_id) {
            int len = strlen(hwDev2StrMem->name);
            if (len >= MAX_HW_NAME_LEN) {
                return errmsg("Internal error: Length of device name: %d exceeds the maximum allowed size: %d", len, MAX_HW_NAME_LEN - 1);
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
// missmatch. The match is not 1:1 , since the FW image contains the SW
// dev id, and a single hw dev id may match multiple SW dev IDs.
//
bool FwOperations::CheckMatchingHwDevId(u_int32_t hwDevId, u_int32_t rev_id, u_int32_t* supportedHwId, u_int32_t supportedHwIdNum) {

    char supp_hw_id_list[MAX_NUM_SUPP_HW_LIST_STR] = {'\0'};
    char supp_hw_id_list_tmp[MAX_NUM_SUPP_HW_LIST_STR];
    char curr_hw_id_name[MAX_HW_NAME_LEN];

    for (u_int32_t i = 0; i < supportedHwIdNum; i++) {
        u_int32_t currSupportedHwId = supportedHwId[i];
        u_int32_t supp_hw_id  = currSupportedHwId & 0xffff;
        u_int32_t supp_rev_id = (currSupportedHwId >> 16) & 0xff;
        u_int32_t tmp_size_of_list;
        char hw_name[MAX_HW_NAME_LEN];

        if (currSupportedHwId == 0) {
            break;
        }
        // Check if device is supported!
        if ( supp_hw_id == hwDevId && supp_rev_id == rev_id) {
            return true;
        }
        // Append checked to list of supported device in order to print it in the error if we this device is not supported

        // Get the HW name of current supported HW ID
        if (!HWIdRevToName(supp_hw_id, supp_rev_id, hw_name)) {
            return false;
        }
        // Check if we don't exceed the array size we have
        tmp_size_of_list = strlen(supp_hw_id_list) + strlen(hw_name) + 2;
        if (tmp_size_of_list >= MAX_NUM_SUPP_HW_LIST_STR) {
            return errmsg("Internal error: Size of supported devs list: %d exceeds the maximum allowed size: %d",
                    tmp_size_of_list, MAX_NUM_SUPP_HW_LIST_STR - 1);
        }

        if (supp_hw_id_list[0] == '\0') {
            sprintf(supp_hw_id_list, "%s", hw_name);
        } else {
            strcpy(supp_hw_id_list_tmp, supp_hw_id_list);
            sprintf(supp_hw_id_list, "%s, %s", supp_hw_id_list_tmp, hw_name);
        }
    }
    // If we get here, this FW cannot be burnt in the current device.
    // Get the Device name
    if (!HWIdRevToName(hwDevId, rev_id, curr_hw_id_name)) {
        return false;
    }

    return errmsg("FW image file cannot be programmed to device %s, it is intended for: %s only",
            curr_hw_id_name, supp_hw_id_list);
}
bool FwOperations::CheckMatchingDevId(u_int32_t hwDevId, u_int32_t imageDevId) {

    const HwDevData* devData = (const HwDevData*)NULL;
    const char* hwDevName = (const char*)NULL;
    // HACK: InfiniHost III LX may have 2 HW device ids. - Map the second devid to the first.
    if (hwDevId == 24204) {
        hwDevId = 25204;
    }

    // First, find the HW device that the SW id matches
    for (int i = 0; hwDevData[i].hwDevId != 0 ; i++) {
        if (hwDevData[i].hwDevId == hwDevId) {
            hwDevName = hwDevData[i].name; // TODO: Check bug if device not found
        }

        if (devData == NULL) {
            for (int j = 0; hwDevData[i].swDevIds[j]; j++) {
                if (hwDevData[i].swDevIds[j] == imageDevId) {
                    devData = &hwDevData[i];
                    break;
                }
            }
        }
    }

    if (devData == NULL) {
        report_warn("Unknown device id (%d) in the given FW image. Skipping HW match check.\n",
               imageDevId);
        return true;
    } else if (devData->hwDevId != hwDevId) {
        return errmsg("Trying to burn a \"%s\" image on a \"%s\" device.",
                      devData->name,
                      hwDevName);
    }

    return true;
}

void FwOperations::FwDebugPrint(char *str)
{
    if (_printFunc != NULL) {
        _printFunc(str);
    }
}

bool FwOperations::FwSetPrint(PrintCallBack PrintFunc)
{
    _printFunc = PrintFunc;
    return true;
}

bool FwOperations::CheckPSID(FwOperations &imageOps, u_int8_t allow_psid_change)
{
    if (!allow_psid_change) {
        if (strncmp( _fwImgInfo.ext_info.psid, imageOps._fwImgInfo.ext_info.psid, PSID_LEN)) {
            return errmsg("Image PSID is %s, it cannot be burnt into current device (PSID: %s)",
                    imageOps._fwImgInfo.ext_info.psid, _fwImgInfo.ext_info.psid);
        }
    }
    return true;
}

bool FwOperations::CheckFwVersion(FwOperations &imageOps, u_int8_t forceVersion)
{
    bool updateRequired = true;
    if (!forceVersion) {
        updateRequired = FwVerLessThan(_fwImgInfo.ext_info.fw_ver, imageOps._fwImgInfo.ext_info.fw_ver);
        if (!updateRequired) {
            return errmsg("FW is already updated.");
        }
    }
    return true;
}

bool FwOperations::FwSwReset() {
    if (!_ioAccess->is_flash()) {
        return errmsg("operation supported only for switch devices InfiniScaleIV and SwitchX over an IB interface");
    }
    if (!((Flash*)_ioAccess)->sw_reset()) {
        return errmsg("%s",  _ioAccess->err());
    }
    return true;
}


void FwOperations::WriteToErrBuff(char* errBuff, const char* errStr, int size)
{
    if (size>0) {
        if (size-4 > (int) strlen(errStr)) {
            strncpy(errBuff, errStr, size);
        } else {
            strncpy(errBuff, errStr, size-4);
            strcpy(&errBuff[size-4], "...");
        }
    }
    return;
}

bool FwOperations::UpdateImgCache(u_int8_t *buff, u_int32_t addr, u_int32_t size)
{
    //avoid compiler warrnings
    (void)buff;
    (void)addr;
    (void)size;
    //in FS2 we dont have ImgCache, just in FS3 so we define a defult behaviour.
    return true;
}

bool FwOperations::CntxEthOnly(u_int32_t devid)
{
    return(devid == 25448) || // ETH
            (devid == 26448) || // ETH
            (devid == 25458) || //
            (devid == 26458) || //
            (devid == 26468) ||
            (devid == 26478);
}

// RomInfo implementation

FwOperations::RomInfo::RomInfo(const std::vector<u_int8_t>& romSector, bool resEndi)
{
    expRomFound = !romSector.empty();
    romSect = romSector;
    if (resEndi) {
        TOCPUn(&romSect[0], romSect.size()/4);
    }
    numOfExpRom = 0;
    expRomComDevid = 0;
    expRomWarning = false;
    expRomErrMsgValid = false;
    noRomChecksum = false;
    memset(expRomErrMsg, 0, sizeof(expRomErrMsg));
    memset(expRomWarningMsg, 0, sizeof(expRomWarningMsg));
    memset(&romsInfo, 0, (sizeof(rom_info_t)*MAX_ROMS_NUM));
}


bool FwOperations::RomInfo::initRomsInfo(roms_info_t *info)
{
    if (info == NULL) {
        return errmsg("invalid roms_info_t pointer.");
    }
    info->exp_rom_found = expRomFound;
    info->num_of_exp_rom = numOfExpRom;
    info->no_rom_checksum = noRomChecksum;
    info->exp_rom_com_devid = expRomComDevid;
    info->exp_rom_warning = expRomWarning;
    info->exp_rom_err_msg_valid = expRomErrMsgValid;
    //copy strings and rom_info
    for (int i=0; i< MAX_ROM_ERR_MSG_LEN; i++) {
        info->exp_rom_warning_msg[i] = expRomWarningMsg[i];
        info->exp_rom_err_msg[i] = expRomErrMsg[i];
    }
    for (int i=0; i< MAX_ROMS_NUM; i++) {
        //copy rom_info struct
        info->rom_info[i].exp_rom_product_id = romsInfo[i].exp_rom_product_id; // 0 - invalid.
        info->rom_info[i].exp_rom_dev_id = romsInfo[i].exp_rom_dev_id;
        info->rom_info[i].exp_rom_port = romsInfo[i].exp_rom_port;
        info->rom_info[i].exp_rom_proto = romsInfo[i].exp_rom_proto;
        info->rom_info[i].exp_rom_num_ver_fields = romsInfo[i].exp_rom_num_ver_fields;
        for (int j=0; j< 3 ; j++) {
             info->rom_info[i].exp_rom_ver[j] = romsInfo[i].exp_rom_ver[j];
        }
    }

    return true;
}

bool FwOperations::RomInfo::ParseInfo()
{
    if (!GetExpRomVersion()) {
        snprintf(expRomErrMsg, MAX_ROM_ERR_MSG_LEN, "%s",  err());
        expRomErrMsgValid = true;
        //printf("-D-expRomErrMsg: %s \n", expRomErrMsg);
    }
    //printf("-D- expRomFound: %d   \n",expRomFound);
    //printf("-D- numOfExpRom: %d   \n",numOfExpRom);
    //printf("-D- noRomChecksum: %d   \n",noRomChecksum);
    //printf("-D- expRomComDevid: %d   \n",expRomComDevid);
    //printf("-D- expRomWarning: %d   \n",expRomWarning);
    //printf("-D- expRomErrMsgValid: %d   \n",expRomErrMsgValid);
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

    if (romSect.empty()) {
        return errmsg("Expansion Rom section not found.");
    }
    // When checking the version of the expansion rom, only the first image has
    // to be checked. This is because the second image  the uefi image does not
    // have to comply with checksumming to 0. To do this you have to read  byte
    // 2 (third) of the image  and multiply by 512 to get the size of the x86
    // image.

    // Checksum:
    if (romSect.size() < 4) {
        return errmsg("ROM size (0x%x) is too small",
                (u_int32_t) romSect.size());
    }

    // restore endianess is done in the constructor if needed.
    /*  // FOR WE DON'T CHECKSUM UNTIL WE DECIDED REGARDING THE NEW FORMAT.
     */
    // We will look for the magic string in whole ROM instead of the first part of it.
    romChecksumRange = romSect.size();

    for (u_int32_t i = 0; i < romChecksumRange; i++) {
        for (u_int32_t j = 0; j < magicLen; j++) {
            if (romSect[i + j] != magicString[j]) {
                break;
            } else if (j == magicLen - 1) {
                magicFound = true;
            }
        }


        if (magicFound) {
            // Get the ROM info after the mlxsign
            bool rc;
            rom_info_t *currRom;

            if (numOfExpRom == MAX_ROMS_NUM) {
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
            if (rc != true) {
                return rc;
            }

            // Get the device ID and check if it mismatches with other ROMs
            if (expRomComDevid != MISS_MATCH_DEV_ID) { // When the DevId is already mismatched, no end to any check
                 if (currRom->exp_rom_dev_id != EXP_ROM_GEN_DEVID) { // When we have a device ID on the ROM
                    if (expRomComDevid == EXP_ROM_GEN_DEVID) { // Update the common DevId at the first time we find ID
                        expRomComDevid = currRom->exp_rom_dev_id;
                    } else { // Check if we have the same IDs, if yes, continue
                        if (currRom->exp_rom_dev_id != expRomComDevid) { // There is a mismatch between ROMs
                            expRomComDevid = MISS_MATCH_DEV_ID;
                            expRomWarning = true;
                            snprintf(expRomWarningMsg,
                                     MAX_ROM_ERR_MSG_LEN,
                                     "The device IDs of the ROMs mismatched.");
                        }
                    }
                }
            }

            magicFound = false;      // Clean the magic_found to start search for another magic string
            i += (ROM_INFO_SIZE - 1); // Increase the index to point to the end of the ROM info.
            numOfExpRom++;
        }
    }

    // TODO: ADD CHECKSUM CHECK
    if (!numOfExpRom) {
        return errmsg("Cannot get ROM version. Signature not found.");

    }

    if (!noRomChecksum) { // No need for checksum on some ROMs like uEFI
         u_int8_t romChecksum = 0;
         romChecksumRange = romSect[2] * 512;
         if (romChecksumRange > romSect.size()) {
             return errmsg(
                     "ROM size field (0x%2x) is larger than actual ROM size (0x%x)",
                     romChecksumRange, (u_int32_t) romSect.size());
         } else if (romChecksumRange == 0) {
             return errmsg(
                     "ROM size field is 0. Unknown ROM format or corrupted ROM.");
         }

         for (u_int32_t i = 0; i < romChecksumRange; i++) {
             romChecksum += romSect[i];
         }

         if (romChecksum != 0) {
             expRomWarning = true;
             snprintf(
                     expRomWarningMsg,
                     MAX_ROM_ERR_MSG_LEN,
                     "Bad ROM Checksum (0x%02x), ROM info may not be displayed correctly.",
                     romChecksum);
         }
     }

    return true;
}

bool FwOperations::RomInfo::GetExpRomVerForOneRom(u_int32_t verOffset)
{

    u_int32_t tmp;
    u_int32_t offs4;
    u_int32_t offs8;
    rom_info_t *romInfo;

    if (numOfExpRom == MAX_ROMS_NUM) {
        expRomWarning = true;
        snprintf(expRomWarningMsg,
                MAX_ROM_ERR_MSG_LEN,
                "Number of exp ROMs exceeds the maximum allowed number: %d",
                MAX_ROMS_NUM);
        return true;
    }
    romInfo = &(romsInfo[numOfExpRom]);

    // Following mlxsign:
    // 31:24    0    Compatible with UEFI
    // 23:16    ProductID   Product ID:
    //                          0x1 - CLP implementation for InfiniHost_III_Lx (MT25408)
    //                          0x2 - CLP implementation for Connectx DDR (MT25418)
    //							0x3 - CLP implementation for Connectx QDR (MT26428)
    //							0x4 - CLP implementation for Connectx ETHERNET (MT25448)
    //                          0X10 - PXE
    //							0x11 - UEFI
    //							0x12 - CLP with device ID and Version
    //							0x21 - FCODE - IBM's ROM version format, the same as PXE
    //						   (0xf) - extended format(see code or rom version format document)
    //
    // 15:0 Major version   If ProductID < 0x10 or == 0x12 this field is subversion
    //                          number, otherwise It's product major version.
    //
    // 31:16    Minor version   Product minor version*. Not valid if
    //                          roductID < 0x10 or == 0x12.
    // 15:0 SubMinor version    Product sub minor version*. Not valid if
    //                                  ProductID < 0x10 or == 0x12.
    //
    // 31:16    Device ID   The PCI Device ID (ex. 0x634A for Connectx
    //                          DDR). Not valid if ProductID < 0x10.
    // 15:12    Port Number Port number: 0 - Port independent, 1 - Port 1, 2 - Port 2
    //  8:11    Reserved
    //  0:7     Protocol type: 0=IB 1=ETH 2=VPI

    // Get expansion rom product ID
    tmp = __le32_to_cpu(*((u_int32_t*) &romSect[verOffset]));
    romInfo->exp_rom_product_id = tmp >> 16;
    romInfo->exp_rom_ver[0] = tmp & 0xffff;

    if (romInfo->exp_rom_product_id < 0xF || romInfo->exp_rom_product_id == 0x12) {
        romInfo->exp_rom_num_ver_fields = 1;//For CLPs
    } else if (romInfo->exp_rom_product_id == 0xF) {
        romInfo->exp_rom_num_ver_fields = 0;
    } else { // >= 0x10
        romInfo->exp_rom_num_ver_fields = 3;
    }

    if (romInfo->exp_rom_product_id == 0x11 || romInfo->exp_rom_product_id == 0x21) {
        noRomChecksum = true;
    }

    if (romInfo->exp_rom_product_id >= 0x10) {
        offs8 = __le32_to_cpu(*((u_int32_t*) &romSect[verOffset + 8]));
        romInfo->exp_rom_dev_id = offs8 >> 16;
    	//0x12 is CLP we have only 1 version field and no porty
    	if (romInfo->exp_rom_product_id != 0x12){
    		offs4 = __le32_to_cpu(*((u_int32_t*) &romSect[verOffset + 4]));
    		romInfo->exp_rom_ver[1] = offs4 >> 16;
    		romInfo->exp_rom_ver[2] = offs4 & 0xffff;

        	romInfo->exp_rom_port = (offs8 >> 12) & 0xf;
        	romInfo->exp_rom_proto = offs8 & 0xff;
        }
    } else if (romInfo->exp_rom_product_id == 0xf) {
        // get string length
        u_int32_ba tmp_ba = *((u_int32_t*) &romSect[verOffset + 0xc]);
        u_int32_t str_len = u_int32_t(tmp_ba.range(15, 8));
        u_int32_t sign_length = u_int32_t(tmp_ba.range(7, 0));
        u_int32_t dws_num = ((str_len + 3) / 4) + 4;

        if (sign_length < dws_num) {
            return errmsg(
                    "The Signature length (%d) and the ROM version string length (%d) are not coordinated",
                    sign_length, str_len);
        }

        int svnv;
        char free_str[FREE_STR_MAX_LEN];
        strncpy(free_str,(char*) &romSect[verOffset + 0x10], str_len);
        free_str[str_len] = '\0';
        if (sscanf((char*) free_str, "%d", &svnv) == 1) {
            romInfo->exp_rom_ver[0] = svnv;
        }

        tmp_ba = __le32_to_cpu(*((u_int32_t*) &romSect[0x18]));
        u_int32_t dev_id_off = u_int32_t(tmp_ba.range(15, 0)) + 4;

        if (dev_id_off >= romSect.size()) {
            return errmsg(
                    "The device ID offset %#x is out of range. ROM size: %#x",
                    dev_id_off, (u_int32_t) romSect.size());
        }

        // get devid
        tmp_ba = __le32_to_cpu(*((u_int32_t*) &romSect[dev_id_off]));
        romInfo->exp_rom_dev_id = u_int32_t(tmp_ba.range(31, 16));
        u_int32_t vendor_id = u_int32_t(tmp_ba.range(15, 0));

        if (vendor_id != MELLANOX_VENDOR_ID) {
            expRomWarning = true;
            snprintf(expRomWarningMsg,
                    MAX_ROM_ERR_MSG_LEN,
                    "The Exp-ROM PCI vendor ID: %#x does not match the expected value: %#x.",
                    vendor_id, MELLANOX_VENDOR_ID);
        }

    }
    return true;
}

bool FwOperations::ReadImageFile(const char *fimage, u_int8_t *&file_data, int &file_size, int min_size)
{
    FILE* fh;

    if ((fh = fopen(fimage, "rb")) == NULL) {
        return errmsg("Can not open %s: %s\n", fimage, strerror(errno));
    }

    if (fseek(fh, 0, SEEK_END) < 0) {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }

    int read_file_size = ftell(fh);
    if (read_file_size < 0) {
        fclose(fh);
        return errmsg("Failed to get size of the file \"%s\": %s\n", fimage, strerror(errno));
    }
    rewind(fh);

    if (min_size > read_file_size) {
        file_size = min_size;
    } else {
        file_size = read_file_size;
    }

    file_data = new u_int8_t[file_size];
    if (fread(file_data, 1, read_file_size, fh) != (size_t)read_file_size) {
        delete[] file_data;
        fclose(fh);
        return errmsg("Failed to read from %s: %s\n", fimage, strerror(errno));
    }
    fclose(fh);
    return true;
}

void FwOperations::SetDevFlags(chip_type_t chipType, u_int32_t devType, fw_img_type_t fwType, bool &ibDev, bool &ethDev) {

    if (chipType == CT_IS4) {
        ibDev =  true;
        ethDev = false;
    } else if (chipType == CT_SWITCHX) {
        ibDev = true;
        ethDev = true;
    } else {
        ibDev  = (fwType == FIT_FS3) || !CntxEthOnly(devType);
        ethDev = chipType == CT_CONNECTX;
    }

    if ((!ibDev && !ethDev) || chipType == CT_UNKNOWN) {
        // Unknown device id - for forward compat - assume that ConnectX is MP and
        // prev HCAs are IB only (these flags are for printing only - no real harm can be done).
        // TODO: FS2 does not mean ConnectX now.
        ibDev = true;
        if (fwType == FIT_FS2) {
            ethDev = true;
        } else {
            ethDev = false;
        }
    }
}

bool FwOperations::IsFwSupportingRomModify(u_int16_t fw_ver[3])
{
    u_int16_t supported_fw[3] = {MAJOR_MOD_ROM_FW,  MINOR_MOD_ROM_FW, SUBMINOR_MOD_ROM_FW};
    return !FwVerLessThan(fw_ver, supported_fw);
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


bool FwOperations::checkMatchingExpRomDevId(u_int16_t dev_type, roms_info_t roms_info)
{
    if ((roms_info.num_of_exp_rom > 0) && (dev_type)
            && (roms_info.exp_rom_com_devid != EXP_ROM_GEN_DEVID) \
            && (roms_info.exp_rom_com_devid != MISS_MATCH_DEV_ID)
            && (dev_type != roms_info.exp_rom_com_devid)) {
        return false;
    }
    return true;
}


bool FwOperations::FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec, ProgressCallBack progressFunc)
{
    if (dataVec.empty()) {
        return errmsg("no data to write.");
    }
    // make sure we work on device
    if (!_ioAccess->is_flash()) {
        return errmsg("no flash detected.(command is only supported on flash)");
    }

    //check if flash is big enough
    if ((addr + dataVec.size()) > ((Flash*)_ioAccess)->get_size()) {
       return errmsg("Writing %#x bytes from address %#x is out of flash limits (%#x bytes)\n",
                            (unsigned int)(dataVec.size()), (unsigned int)addr, (unsigned int)_ioAccess->get_size());
    }

    if (!writeImage(progressFunc, addr, &dataVec[0], (int)dataVec.size())) {
        return false;
    }
    return true;
};


bool FwOperations::FwBurnData(u_int32_t *data, u_int32_t dataSize, ProgressCallBack progressFunc) {
    FwOperations* newImgOps;
    fwOpsParams imgOpsParams;
    char errBuff[1024] = {0};

    imgOpsParams.psid      = NULL;
    imgOpsParams.buffHndl  = data;
    imgOpsParams.buffSize = dataSize;
    imgOpsParams.errBuff = errBuff;
    imgOpsParams.errBuffSize = 1024;
    imgOpsParams.hndlType = FHT_FW_BUFF;

    newImgOps = FwOperationsCreate(imgOpsParams);
    if (newImgOps == NULL) {
        return errmsg("Internal error: Failed to create modified image: %s", errBuff);
    }
    if (!newImgOps->FwVerify(NULL)) {
    	errmsg("Internal error: Modified image failed to verify: %s", newImgOps->err());
        newImgOps->FwCleanUp();
        delete newImgOps;
        return false;
    }

    ExtBurnParams burnParams = ExtBurnParams();
    burnParams.ignoreVersionCheck = true;
    burnParams.progressFunc = progressFunc;
    burnParams.useImagePs = true;
    burnParams.useImageGuids = true;
    burnParams.burnRomOptions = ExtBurnParams::BRO_ONLY_FROM_IMG;

    if (!FwBurnAdvanced(newImgOps, burnParams)) {
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
    romSector.resize(io->get_size());
    if (!io->read(0, &romSector[0], io->get_size())) {
        return false;
    }
    RomInfo info(romSector, false);
    info.ParseInfo();
    info.initRomsInfo(&romsInfo);
    return true;
}

const char* FwOperations::expRomType2Str(u_int16_t type)
{
	switch (type) {
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
	        case 0x21:
	        	return "FCODE";
	        default:
	            return (const char*)NULL;
	        }
	return (const char*)NULL;
}
