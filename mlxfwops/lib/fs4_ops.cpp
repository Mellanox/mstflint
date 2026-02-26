/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <algorithm>
#include <vector>

#include <cstring>
#include "common/tools_utils.h"
#include "common/bit_slice.h"
#include "common/tools_time.h"
#include <mtcr.h>
#include <reg_access/reg_access.h>
#include <calc_hw_crc.h>

#ifdef MST_UL
#include <cmdif/icmd_cif_open.h>
#else
#ifndef UEFI_BUILD
#include <cmdif/cib_cif.h>
#endif
#endif

#if !defined(UEFI_BUILD)
#include <iostream>
#include <fstream>
#include <sstream>
#if !defined(NO_CS_CMD)
#include <tools_crypto/tools_md5.h>
#endif // NO_CS_CMD
#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif // NO_OPEN_SSL
#endif // UEFI_BUILD

#include "fs4_ops.h"
#include "fs3_ops.h"

#define FS4_ENCRYPTED_LOG_CHUNK_SIZE 24

#define DEV_INFO_SIG0 0x6d446576
#define DEV_INFO_SIG1 0x496e666f
#define DEV_INFO_SIG2 0x2342cafa
#define DEV_INFO_SIG3 0xbacafe00

#define GUID_TO_64(guid_st) (guid_st.l | (u_int64_t)guid_st.h << 32)

#define CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP()                                          \
    if (!_ioAccess->is_flash())                                                       \
    {                                                                                 \
        return errmsg("Timestamp operation for FS4 FW image files is not supported"); \
    }

#define COUNT_OF_SECTIONS_TO_ALIGN 5

void Fs4Operations::FwCleanUp()
{
    FwOperations::FwCleanUp();
    if (_encrypted_image_io_access)
    {
        _encrypted_image_io_access->close();
        delete _encrypted_image_io_access;
        _encrypted_image_io_access = (FImage*)NULL;
    }
}

bool Fs4Operations::CheckSignatures(u_int32_t a[], u_int32_t b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            // printf("-D- a[%d]=%d b[%d]=%d", i, a[i], i, b[i]);
            return false;
        }
    }
    return true;
}

bool Fs4Operations::IsEncryptedDevice(bool& is_encrypted)
{
    DPRINTF(("Fs4Operations::IsEncryptedDevice\n"));
    is_encrypted = false;

    if (_signatureMngr->IsLifeCycleSupported() && _signatureMngr->IsEncryptionSupported())
    {
        chip_type_t chip_type;
        const u_int32_t* swId = (u_int32_t*)NULL;
        if (!getInfoFromHwDevid(GetHwDevId(), chip_type, &swId))
        {
            return false;
        }
        CRSpaceRegisters crSpaceReg(getMfileObj(), chip_type);
        if (crSpaceReg.IsLifeCycleSecured())
        {
            is_encrypted = true;
        }
    }
    else
    {
        is_encrypted = false;
    }

    return true;
}

//* Determine if encrypted by reading ITOC header magic-pattern
bool Fs4Operations::IsEncryptedImage(bool& is_encrypted)
{
    DPRINTF(("Fs4Operations::IsEncryptedImage\n"));
    struct image_layout_itoc_header itocHeader = image_layout_itoc_header();
    u_int8_t buffer[TOC_HEADER_SIZE];
    memset(buffer, 0, TOC_HEADER_SIZE * sizeof(u_int8_t));

    is_encrypted = false;

    if (!_is_hw_ptrs_initialized)
    {
        if (!InitHwPtrs(true))
        {
            DPRINTF(("Fs4Operations::IsEncryptedImage HW pointers not found"));
            return false;
        }
    }

    READBUF((*_ioAccess), _itoc_ptr, buffer, TOC_HEADER_SIZE, "ITOC Header");
    image_layout_itoc_header_unpack(&itocHeader, buffer);
    if (!CheckTocSignature(&itocHeader, ITOC_ASCII))
    { // Check first location of ITOC header magic-pattern
        READBUF((*_ioAccess), _itoc_ptr + FS4_DEFAULT_SECTOR_SIZE, buffer, TOC_HEADER_SIZE, "ITOC Header");
        image_layout_itoc_header_unpack(&itocHeader, buffer);
        if (!CheckTocSignature(&itocHeader, ITOC_ASCII))
        { // Check second location of ITOC header magic-pattern
            is_encrypted = true;
        }
    }

    return true;
}

bool Fs4Operations::isEncrypted(bool& is_encrypted)
{
    DPRINTF(("Fs4Operations::isEncrypted\n"));
    bool res = false;

    if (_ioAccess->is_flash())
    {
        DPRINTF(("Fs4Operations::isEncrypted call IsEncryptedDevice\n"));
        res = IsEncryptedDevice(is_encrypted);
    }
    else
    {
        DPRINTF(("Fs4Operations::isEncrypted call IsEncryptedImage\n"));
        res = IsEncryptedImage(is_encrypted);
    }

    DPRINTF(("Fs4Operations::isEncrypted is_encrypted = %s, res = %s\n", is_encrypted ? "TRUE" : "FALSE", res ? "TRUE" : "FALSE"));
    return res;
}

bool Fs4Operations::CheckTocSignature(struct image_layout_itoc_header* itoc_header, u_int32_t first_signature)
{
    u_int32_t a[4] = {itoc_header->signature0, itoc_header->signature1, itoc_header->signature2, itoc_header->signature3};
    u_int32_t b[4] = {first_signature, TOC_RAND1, TOC_RAND2, TOC_RAND3};
    return CheckSignatures(a, b, 4);
}

bool Fs4Operations::CheckDevInfoSignature(u_int32_t* buff)
{
    u_int32_t sig0 = buff[0], sig1 = buff[1], sig2 = buff[2], sig3 = buff[3];
    TOCPU1(sig0);
    TOCPU1(sig1);
    TOCPU1(sig2);
    TOCPU1(sig3);
    u_int32_t a[4] = {sig0, sig1, sig2, sig3};
    u_int32_t b[4] = {DEV_INFO_SIG0, DEV_INFO_SIG1, DEV_INFO_SIG2, DEV_INFO_SIG3};
    // printf("sig0=%x sig1=%x sig2=%x sig3=%x\n", sig0, sig1, sig2, sig3);
    return CheckSignatures(a, b, 4);
}

// CodeView: move it to Base class
bool Fs4Operations::getImgStart()
{
    DPRINTF(("Fs4Operations::getImgStart\n"));
    if (GetIsReducedImage())
    {
        _fwImgInfo.imgStart = 0;
    }
    else
    {
        u_int32_t cntx_image_start[CNTX_START_POS_SIZE] = {0};
        u_int32_t cntx_image_num = 0;

        FindAllImageStart(_ioAccess, cntx_image_start, &cntx_image_num, _fs4_magic_pattern);

        if (cntx_image_num == 0)
        {
            return errmsg(MLXFW_NO_VALID_IMAGE_ERR, "\nNo valid FS4 image found. Check the flash parameters, if specified.");
        }
        if (cntx_image_num > 1)
        {
            return errmsg(MLXFW_MULTIPLE_VALID_IMAGES_ERR, "More than one FS4 image found on %s", this->_ioAccess->is_flash() ? "Device" : "image");
        }
        _fwImgInfo.imgStart = cntx_image_start[0];
    }
    DPRINTF(("Fs4Operations::getImgStart - _fwImgInfo.imgStart = 0x%x\n", _fwImgInfo.imgStart));

    return true;
}

bool Fs4Operations::CheckAndSetIsReducedImage()
{
    if (_ioAccess->is_flash())
    {
        SetIsReducedImage(false);
        return true;
    }

    u_int32_t image_size = 0;
    // Calculate the size from the start to the end of the iTOCs.
    if (!GetImageSize(&image_size))
    {
        return errmsg("Can't get image size.\n");
    }
    u_int32_t readbleSize = _ioAccess->get_size();
    if (readbleSize < image_size)
    {
        return errmsg("Image size is larger than image buffer size.\n");
    }
    u_int32_t imageGapSize = readbleSize - image_size;
    // If the image contains an encapsulation header, this will represent the gap (equal to the encapsulation header
    // size, which matches the BCH size).
    bool isReducedImage = IsValidGapImageSize(imageGapSize);
    SetIsReducedImage(isReducedImage);

    return true;
}

bool Fs4Operations::IsValidGapImageSize(u_int32_t imageGapSize)
{
    return imageGapSize == 0;
}

bool Fs4Operations::getExtendedHWAravaPtrs(VerifyCallBack verifyCallBackFunc, FBase* ioAccess, bool IsBurningProcess, bool isVerify)
{
    DPRINTF(("Fs4Operations::getExtendedHWAravaPtrs\n"));
#if defined(UEFI_BUILD)
    (void)verifyCallBackFunc;
    (void)ioAccess;
    (void)IsBurningProcess;
    return errmsg("Operation not supported");
#else
    const unsigned int s = IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE / 4;
    u_int32_t buff[s] = {0};
    struct image_layout_hw_pointers_carmel hw_pointers;
    u_int32_t physAddr = FS4_HW_PTR_START;
    if (!IsBurningProcess)
    {
        physAddr += _fwImgInfo.imgStart;
    }
    READBUF((*ioAccess), physAddr, buff, IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE, "HW Arava Pointers");

    // Fix pointers that are 0xFFFFFFFF
    for (unsigned int k = 0; k < s; k += 2)
    {
        if (buff[k] == 0xFFFFFFFF)
        {
            buff[k] = 0;     // Fix pointer
            buff[k + 1] = 0; // Fix CRC
        }
    }

    image_layout_hw_pointers_carmel_unpack(&hw_pointers, (u_int8_t*)buff);

    // Check CRC of each pointers
    for (unsigned int k = 0; k < s; k += 2)
    {
        u_int32_t* tempBuff = (u_int32_t*)buff;
        // Actual CRC:
        u_int32_t ptrCRC = tempBuff[k + 1];
        TOCPUn(&ptrCRC, 1);

        // Compare with SW CRC:
        u_int32_t calcPtrCRC;
        u_int32_t calcPtrSWCRC = CalcImageCRC((u_int32_t*)tempBuff + k, 1);
        if (ptrCRC == calcPtrSWCRC)
        {
            // Some devices (QT3) uses SW CRC calculation for HW pointers
            // and since we don't have an indication for that, we'll just check
            // if SW CRC calculation matches the actual CRC
            calcPtrCRC = calcPtrSWCRC;
        }
        else
        {
            // Calculate HW CRC:
            calcPtrCRC = calc_hw_crc((u_int8_t*)((u_int32_t*)tempBuff + k), 6);
        }
        if (!DumpFs3CRCCheck(FS4_HW_PTR, physAddr + 4 * k, IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE, calcPtrCRC, ptrCRC, false, verifyCallBackFunc))
        {
            return false;
        }
    }

    // CodeView: generate tools_layout
    _boot_record_ptr = hw_pointers.boot_record_ptr.ptr;
    _boot2_ptr = hw_pointers.boot2_ptr.ptr;
    _itoc_ptr = hw_pointers.toc_ptr.ptr;
    _tools_ptr = hw_pointers.tools_ptr.ptr;

    if (isVerify == false)
    {
        _authentication_start_ptr = hw_pointers.authentication_start_pointer.ptr;
        _authentication_end_ptr = hw_pointers.authentication_end_pointer.ptr;
        _digest_mdk_ptr = hw_pointers.digest_pointer.ptr;
        _digest_recovery_key_ptr = hw_pointers.digest_recovery_key_pointer.ptr;
        _public_key_ptr = hw_pointers.public_key_pointer.ptr;
    }
    _security_version = hw_pointers.fw_security_version_pointer.ptr;
    _gcm_image_iv = hw_pointers.gcm_iv_delta_pointer.ptr;
    _hashes_table_ptr = hw_pointers.hashes_table_pointer.ptr;
    _image_info_section_ptr = hw_pointers.image_info_section_pointer.ptr;

    _is_hw_ptrs_initialized = true;
    return true;
#endif
}

bool Fs4Operations::openEncryptedImageAccess(const char* encrypted_image_path)
{
    DPRINTF(("Fs4Operations::openEncryptedImageAccess\n"));
    // After this method is done we won't be able verify 'this' (nonencrypted) image
    // since we'll replace its read/write with the encrypted image
    // so we we'll verify it now just to make sure it's valid
    //* Verify nonencrypted image
    if (!FsIntQueryAux())
    {
        return errmsg("Failed to verify nonencrypted image");
    }

    //* Create io access to the encrypted image
    _encrypted_image_io_access = new FImage;
    if (!_encrypted_image_io_access->open(encrypted_image_path, false, false))
    {
        delete _encrypted_image_io_access;
        return errmsg("Failed to open image %s", encrypted_image_path);
    }
    return true;
}

bool Fs4Operations::getExtendedHWPtrs(VerifyCallBack verifyCallBackFunc, FBase* ioAccess, bool IsBurningProcess)
{
    // TODO
    // printf("1=0x%x 2=0x%x\n", _fwImgInfo.supportedHwId[0], CX6_HW_ID);
    /*if (_fwImgInfo.supportedHwId[0] != CX6_HW_ID) {
        return errmsg("Extended HW pointers are only for ConnectX-6\n");
    }*/

    const unsigned int s = IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE / 4;
    u_int32_t buff[s] = {0};
    struct cx6fw_hw_pointers hw_pointers;
    u_int32_t physAddr = FS4_HW_PTR_START;
    if (!IsBurningProcess)
    {
        physAddr += _fwImgInfo.imgStart;
    }

    READBUF((*ioAccess), physAddr, buff, IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE, "HW Pointers");
    cx6fw_hw_pointers_unpack(&hw_pointers, (u_int8_t*)buff);

    //- Check CRC of each pointers (always check CRC before you call ToCPU
    for (unsigned int k = 0; k < s; k += 2)
    {
        u_int32_t* tempBuff = (u_int32_t*)buff;
        // Calculate HW CRC:
        u_int32_t calcPtrCRC = calc_hw_crc((u_int8_t*)((u_int32_t*)tempBuff + k), 6);
        u_int32_t ptrCRC = tempBuff[k + 1];
        u_int32_t ptr = tempBuff[k];
        TOCPUn(&ptr, 1);
        TOCPUn(&ptrCRC, 1);
        if (!DumpFs3CRCCheck(FS4_HW_PTR, physAddr + 4 * k, IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE, calcPtrCRC, ptrCRC, false, verifyCallBackFunc))
        {
            return false;
        }
    }

    // CodeView: generate tools_layout
    _boot2_ptr = hw_pointers.boot2_ptr.ptr;
    _itoc_ptr = hw_pointers.toc_ptr.ptr;
    _tools_ptr = hw_pointers.tools_ptr.ptr;
    _boot_record_ptr = hw_pointers.boot_record_ptr.ptr;

    _authentication_start_ptr = hw_pointers.authentication_start_ptr.ptr;
    _authentication_end_ptr = hw_pointers.authentication_end_ptr.ptr;
    _digest_mdk_ptr = hw_pointers.digest_mdk_ptr.ptr;
    _digest_recovery_key_ptr = hw_pointers.digest_recovery_key_ptr.ptr;

    _is_hw_ptrs_initialized = true;
    return true;
}

bool Fs4Operations::verifyToolsArea(VerifyCallBack verifyCallBackFunc)
{
    DPRINTF(("Fs4Operations::verifyToolsArea\n"));
    u_int32_t buff[IMAGE_LAYOUT_TOOLS_AREA_SIZE / 4] = {0};
    u_int8_t binVerMajor = 0;
    u_int8_t binVerMinor = 0;
    u_int32_t calculatedToolsAreaCRC;
    u_int32_t toolsAreaCRC;
    u_int32_t physAddr = _fwImgInfo.imgStart + _tools_ptr;
    struct image_layout_tools_area tools_area;

    READBUF((*_ioAccess), physAddr, buff, IMAGE_LAYOUT_TOOLS_AREA_SIZE, "Tools Area");
    image_layout_tools_area_unpack(&tools_area, (u_int8_t*)buff);

    binVerMinor = tools_area.bin_ver_minor;
    binVerMajor = tools_area.bin_ver_major;
    _maxImgLog2Size = tools_area.log2_img_slot_size;
    toolsAreaCRC = tools_area.crc;

    calculatedToolsAreaCRC = CalcImageCRC((u_int32_t*)buff, IMAGE_LAYOUT_TOOLS_AREA_SIZE / 4 - 1);

    if (!DumpFs3CRCCheck(FS4_TOOLS_AREA, physAddr, IMAGE_LAYOUT_TOOLS_AREA_SIZE, calculatedToolsAreaCRC, toolsAreaCRC, false, verifyCallBackFunc))
    {
        return false;
    }

    /*printf("-D- Bin Ver Minor=%d\n", binVerMinor);
       printf("-D- Bin Ver Major=%d\n", binVerMajor);
       printf("-D- _maxImgLog2Size=%d\n", _maxImgLog2Size);
       printf("-D- Actuall tools area CRC=%d\n", toolsAreaCRC);
       printf("-D- Expected tools area CRC=%d\n", calculatedToolsAreaCRC);*/

    //- Check if binary version is supported by the tool
    if (!CheckBinVersion(binVerMajor, binVerMinor))
    {
        return false;
    }

    // Put info
    if (_maxImgLog2Size == 0x16 && _fwImgInfo.imgStart == 0x800000)
    {
        _fwImgInfo.cntxLog2ChunkSize = 0x17;
    }
    else
    {
        _fwImgInfo.cntxLog2ChunkSize = _maxImgLog2Size;
    }
    DPRINTF(("_fwImgInfo.cntxLog2ChunkSize = 0x%x\n", _fwImgInfo.cntxLog2ChunkSize));
    _fwImgInfo.ext_info.is_failsafe = true;
    DPRINTF(("_fwImgInfo.ext_info.is_failsafe = true\n"));
    _fwImgInfo.actuallyFailsafe = true;
    DPRINTF(("_fwImgInfo.actuallyFailsafe  = true\n"));
    _fwImgInfo.magicPatternFound = 1;
    DPRINTF(("_fwImgInfo.magicPatternFound = 1\n"));

    return true;
}

bool Fs4Operations::verifyTocHeader(u_int32_t tocAddr, bool isDtoc, VerifyCallBack verifyCallBackFunc)
{
    struct image_layout_itoc_header itocHeader;
    u_int8_t buffer[TOC_HEADER_SIZE];
    u_int32_t physAddr;
    u_int32_t tocCrc;

    /*if(isDtoc) {
        _ioAccess->set_address_convertor(0, 0);
       }*/

    READBUF((*_ioAccess), tocAddr, buffer, TOC_HEADER_SIZE, "TOC Header");
    Fs3UpdateImgCache(buffer, tocAddr, TOC_HEADER_SIZE);
    image_layout_itoc_header_unpack(&itocHeader, buffer);
    // TODO: check if we really need this:
    if (isDtoc)
    {
        memcpy(_fs4ImgInfo.dtocArr.tocHeader, buffer, IMAGE_LAYOUT_ITOC_HEADER_SIZE);
    }
    else
    {
        memcpy(_fs4ImgInfo.itocArr.tocHeader, buffer, IMAGE_LAYOUT_ITOC_HEADER_SIZE);
    }

    // Check the signature in the header:
    u_int32_t first_signature = isDtoc ? DTOC_ASCII : ITOC_ASCII;
    if (!CheckTocSignature(&itocHeader, first_signature))
    {
        return false;
    }

    tocCrc = CalcImageCRC((u_int32_t*)buffer, (TOC_HEADER_SIZE / 4) - 1);
    physAddr = _ioAccess->get_phys_from_cont(tocAddr, isDtoc ? 0 : _fwImgInfo.cntxLog2ChunkSize, _fwImgInfo.imgStart != 0);

    if (!DumpFs3CRCCheck(isDtoc ? FS3_DTOC : FS3_ITOC, physAddr, TOC_HEADER_SIZE, tocCrc, itocHeader.itoc_entry_crc, false, verifyCallBackFunc))
    {
        return false;
    }

    return true;
}

/*
    This function responsible on remove every 4B of CRC from MAIN section
    Some special cases and how we handle them (aligned to FW behavior):
    1. Complete line is 0x0 (including the 4B CRC) --> handle it the same as other line, remove the last 4B
    2. Leftover (not a complete line at the end) --> keep it as is
*/
void Fs4Operations::RemoveCRCsFromMainSection(vector<u_int8_t>& img)
{
    //* Get MAIN section ITOC entry
    struct fs4_toc_info* main_itoc_entry = NULL;
    fs4_toc_info* itoc_entries = _fs4ImgInfo.itocArr.tocArr;
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        if (itoc_entries[i].toc_entry.cache_line_crc)
        {
            main_itoc_entry = &(itoc_entries[i]);
            break;
        }
    }
    if (main_itoc_entry == NULL)
    {
        return;
    }

    u_int32_t main_addr = main_itoc_entry->toc_entry.flash_addr << 2; // addr in entry is in DW
    u_int32_t main_size = main_itoc_entry->toc_entry.size << 2;       // size in entry is in DW

    vector<u_int8_t> tmp_img;
    tmp_img.reserve(img.size());

    //* Copying image data before MAIN section
    tmp_img.insert(tmp_img.end(), img.begin(), img.begin() + main_addr);

    //* Copying MAIN section without CRCs
    const u_int32_t MAIN_LINE_SIZE = 68; // Line in MAIN is 64B data + 4B crc
    const u_int32_t MAIN_LINE_DATA_ONLY_SIZE = MAIN_LINE_SIZE - 4;
    for (u_int32_t offset = 0; offset < main_size; offset += MAIN_LINE_SIZE)
    {
        u_int32_t line_start_addr = main_addr + offset;
        if (offset + MAIN_LINE_SIZE > main_size)
        {
            // In case last line isn't a full line there will be no CRC
            tmp_img.insert(tmp_img.end(), img.begin() + line_start_addr, img.begin() + main_addr + main_size);
        }
        else
        {
            tmp_img.insert(tmp_img.end(), img.begin() + line_start_addr, img.begin() + line_start_addr + MAIN_LINE_DATA_ONLY_SIZE);
        }
    }

    //* Copying image data after MAIN section
    tmp_img.insert(tmp_img.end(), img.begin() + main_addr + main_size, img.end());

    img = tmp_img;
}

/*
    This function responsible on removing boot-record last 4B of CRC
*/
bool Fs4Operations::MaskBootRecordCRC(vector<u_int8_t>& img)
{
    u_int32_t boot_record_size_without_crc = 0;
    if (!getBootRecordSize(boot_record_size_without_crc))
    {
        return errmsg("Failed to get boot_record size\n");
    }
    u_int32_t boot_record_crc_addr = _boot_record_ptr + boot_record_size_without_crc;
    fill(img.begin() + boot_record_crc_addr, img.begin() + boot_record_crc_addr + 4, 0xff); // Mask 4B of CRC/auth-tag

    return true;
}

bool Fs4Operations::GetImageDataForSign(MlxSign::SHAType shaType, vector<u_int8_t>& img)
{
    if (!Fs3Operations::GetImageDataForSign(shaType, img))
    {
        return false;
    }

    //* In case of security version 2 (Carmel onwards) we'll ignore MAIN CRCs for fw-update signature
    if (getSecureBootSignVersion() == VERSION_2)
    {
        // Removal order is critical, we must remove from the end of the image to its start (first MAIN then
        // boot-record) since lower addresses won't be affected by erasing data from higher addresses
        RemoveCRCsFromMainSection(img);
        //* In case of devices after Carmel we'll ignore boot-record CRC for fw-update signature same as secure-boot
        // signature
        if (getChipType(_fwImgInfo.supportedHwId[0]) != CT_CONNECTX7)
        {
            if (!MaskBootRecordCRC(img))
            {
                return false;
            }
        }
    }

    return true;
}

bool Fs4Operations::FwExtract4MBImage(vector<u_int8_t>& img, bool maskMagicPatternAndDevToc, bool verbose, bool ignoreImageStart, bool)
{
    bool res = false;

    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }
    if (_encrypted_image_io_access or image_encrypted)
    {
        res = FwExtractEncryptedImage(img, maskMagicPatternAndDevToc, verbose, ignoreImageStart);
    }
    else
    {
        res = Fs3Operations::FwExtract4MBImage(img, maskMagicPatternAndDevToc, verbose, ignoreImageStart);
    }

    return res;
}

bool Fs4Operations::verifyTocEntries(u_int32_t tocAddr, bool show_itoc, bool isDtoc, struct QueryOptions queryOptions, VerifyCallBack verifyCallBackFunc, bool verbose)
{
    struct image_layout_itoc_entry tocEntry;
    int section_index = 0;
    u_int32_t entryAddr;
    u_int32_t entryCrc;
    u_int32_t entrySizeInBytes;
    u_int32_t physAddr;
    u_int8_t entryBuffer[TOC_ENTRY_SIZE];
    bool mfgExists = false;
    int validDevInfoCount = 0;
    bool retVal = true;
    TocArray* tocArray;

    if (isDtoc)
    {
        tocArray = &(_fs4ImgInfo.dtocArr);
    }
    else
    {
        tocArray = &(_fs4ImgInfo.itocArr);
    }

    do
    {
        // Read toc entry
        if (nextBootFwVer)
        {
            // if nextBootFwVer is true, read only fw version (FS3_IMAGE_INFO section)
            // section index should be 8 for this case
            section_index = 8;
        }

        entryAddr = tocAddr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
        if (!(*_ioAccess).read(entryAddr, entryBuffer, TOC_ENTRY_SIZE, verbose))
        {
            return errmsg("%s - read error (%s)\n", "TOC Entry", (*_ioAccess).err());
        }

        Fs3UpdateImgCache(entryBuffer, entryAddr, TOC_ENTRY_SIZE);
        image_layout_itoc_entry_unpack(&tocEntry, entryBuffer);
        if (tocEntry.type == FS3_MFG_INFO)
        {
            mfgExists = true;
        }

        if (tocEntry.type != FS3_END)
        {
            if (section_index + 1 >= MAX_TOCS_NUM)
            {
                return errmsg("Internal error: number of %s %d is greater than allowed %d", isDtoc ? "DTocs" : "ITocs", section_index + 1, MAX_TOCS_NUM);
            }

            entryCrc = CalcImageCRC((u_int32_t*)entryBuffer, (TOC_ENTRY_SIZE / 4) - 1);
            if (tocEntry.itoc_entry_crc != entryCrc)
            {
                if (_fwParams.ignoreCrcCheck)
                {
                    printf("-W- Bad %s Entry CRC. Expected: 0x%x , Actual: 0x%x\n", isDtoc ? "DToc" : "IToc", tocEntry.itoc_entry_crc, entryCrc);
                }
                else
                {
                    return errmsg(MLXFW_BAD_CRC_ERR, "Bad %s Entry CRC. Expected: 0x%x , Actual: 0x%x", isDtoc ? "DToc" : "IToc", tocEntry.itoc_entry_crc, entryCrc);
                }
            }

            entrySizeInBytes = tocEntry.size * 4;

            // Update last image address
            u_int32_t section_last_addr;
            u_int32_t flash_addr = tocEntry.flash_addr << 2;
            if (isDtoc)
            {
                physAddr = flash_addr;
                _fs4ImgInfo.smallestDTocAddr = (_fs4ImgInfo.smallestDTocAddr < flash_addr && _fs4ImgInfo.smallestDTocAddr > 0) ? _fs4ImgInfo.smallestDTocAddr : flash_addr;
            }
            else
            {
                physAddr = _ioAccess->get_phys_from_cont(flash_addr, _fwImgInfo.cntxLog2ChunkSize, _fwImgInfo.imgStart != 0);
                section_last_addr = physAddr + entrySizeInBytes;
                _fwImgInfo.lastImageAddr = (_fwImgInfo.lastImageAddr >= section_last_addr) ? _fwImgInfo.lastImageAddr : section_last_addr;
            }

            if (IsFs3SectionReadable(tocEntry.type, queryOptions))
            {
                // Only when we have full verify or the info of this section should be collected for query
                std::vector<u_int8_t> buffv(entrySizeInBytes);
                u_int8_t* buff = (u_int8_t*)(buffv.size() ? (&(buffv[0])) : NULL);

                if (show_itoc)
                {
                    image_layout_itoc_entry_dump(&tocEntry, stdout);
                    if (!DumpFs3CRCCheck(tocEntry.type, physAddr, entrySizeInBytes, 0, 0, true, verifyCallBackFunc))
                    {
                        retVal = false;
                    }
                }
                else
                {
                    //* Choosing the correct io access to read from
                    FBase* io = _ioAccess;
                    if (_encrypted_image_io_access)
                    {
                        io = _encrypted_image_io_access; // If encrypted image was given we'll read from it
                    }
                    DPRINTF(("Fs4Operations::verifyTocEntries reading %s %s section from %simage\n",
                             GetSectionNameByType(tocEntry.type),
                             isDtoc ? "DTOC" : "ITOC",
                             _encrypted_image_io_access ? "encrypted " : ""));

                    if (!(*io).read(flash_addr, buff, entrySizeInBytes, verbose))
                    {
                        return errmsg("%s - read error (%s)\n", "Section", (*io).err());
                    }

                    Fs3UpdateImgCache(buff, flash_addr, entrySizeInBytes);
                    u_int32_t sect_act_crc = 0;
                    u_int32_t sect_exp_crc = 0;
                    if (tocEntry.crc == INITOCENTRY)
                    {
                        // crc is in the itoc entry
                        sect_act_crc = CalcImageCRC((u_int32_t*)buff, tocEntry.size);
                        sect_exp_crc = tocEntry.section_crc;
                        // printf("-D-INITOCENTRY sect_act_crc=%d sect_exp_crc=%d\n", sect_act_crc, sect_exp_crc);
                    }
                    else if (tocEntry.crc == INSECTION)
                    {
                        // calc crc on the section without the last dw which contains crc
                        sect_act_crc = CalcImageCRC((u_int32_t*)buff, tocEntry.size - 1);
                        // crc is in the section, last two bytes
                        sect_exp_crc = ((u_int32_t*)buff)[tocEntry.size - 1];
                        TOCPU1(sect_exp_crc)
                        sect_exp_crc = (u_int16_t)sect_exp_crc;
                        // printf("-D-INSECTION sect_act_crc=%d sect_exp_crc=%d\n", sect_act_crc, sect_exp_crc);
                    }

                    if (tocEntry.type != FS3_DEV_INFO || CheckDevInfoSignature((u_int32_t*)buff))
                    {
                        // Check if a cache_line_crc section (Ex. MAIN_CODE) is encrypted (has 4B AUTH-TAG) or not (has
                        // 2B CRC)
                        bool is_encrypted_cache_line_crc_section = false;
                        if (tocEntry.cache_line_crc == 1)
                        {
                            u_int32_t first_line_crc_or_authtag = ((u_int32_t*)buff)[16]; // DWORD 16 is CRC or AUTH-TAG
                            TOCPU1(first_line_crc_or_authtag)
                            bool is_authtag = (first_line_crc_or_authtag & 0xffff0000) != 0x0;
                            is_encrypted_cache_line_crc_section = is_authtag; // if encrypted section will have auth-tag
                        }

                        bool ignore_crc = (tocEntry.crc == NOCRC) || is_encrypted_cache_line_crc_section; // In case of encrypted MAIN_CODE section
                                                                                                          // we'll ignore CRC
                        if (!_encrypted_image_io_access &&                                                // In case of encrypted image we don't want to check section
                                                                                                          // CRC
                            !DumpFs3CRCCheck(tocEntry.type, physAddr, entrySizeInBytes, sect_act_crc, sect_exp_crc, ignore_crc, verifyCallBackFunc))
                        {
                            if (isDtoc)
                            {
                                _badDevDataSections = true;
                            }
                            retVal = false;
                        }
                        else
                        {
                            // printf("-D- toc type : 0x%.8x\n" , toc_entry.type);
                            GetSectData(tocArray->tocArr[section_index].section_data, (u_int32_t*)buff, tocEntry.size * 4);
                            bool isDevInfoSection = (tocEntry.type == FS3_DEV_INFO);
                            bool isDevInfoValid = isDevInfoSection && CheckDevInfoSignature((u_int32_t*)buff);
                            if (isDevInfoValid)
                            {
                                validDevInfoCount++;
                            }
                            if (!isDevInfoSection || isDevInfoValid)
                            {
                                if (IsGetInfoSupported(tocEntry.type))
                                {
                                    u_int8_t* section_buff;
                                    section_buff = buff;
                                    vector<u_int8_t> non_encrypted_buff;
                                    if (_encrypted_image_io_access)
                                    {
                                        // In case of encrypted image, parsing info section from the non-encrypted image
                                        non_encrypted_buff.resize(tocEntry.size * 4);
                                        READBUF((*_ioAccess), flash_addr, non_encrypted_buff.data(), entrySizeInBytes, "Section");
                                        section_buff = non_encrypted_buff.data();
                                    }
                                    if (!GetImageInfoFromSection(section_buff, tocEntry.type, tocEntry.size * 4))
                                    {
                                        retVal = false;
                                        errmsg("Failed to get info from section %d, check the supported_hw_id section "
                                               "in MLX file!\n",
                                               tocEntry.type);
                                    }
                                }
                                else if (tocEntry.type == FS3_DBG_FW_INI)
                                {
                                    TOCPUn(buff, tocEntry.size);
                                    GetSectData(_fwConfSect, (u_int32_t*)buff, tocEntry.size * 4);
                                }
                            }
                        }
                    }
                    else
                    {
                        GetSectData(tocArray->tocArr[section_index].section_data, (u_int32_t*)buff, tocEntry.size * 4);
                    }
                }
            }

            tocArray->tocArr[section_index].entry_addr = entryAddr;
            tocArray->tocArr[section_index].toc_entry = tocEntry;
            memcpy(tocArray->tocArr[section_index].data, entryBuffer, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
        }
        if (nextBootFwVer)
        {
            // if nextBootFwVer, return after reading fw version
            break;
        }
        section_index++;
    } while (tocEntry.type != FS3_END);

    tocArray->numOfTocs = section_index - 1;

    if (isDtoc)
    {
        if (!mfgExists)
        {
            _badDevDataSections = true;
            return errmsg(MLXFW_NO_MFG_ERR, "No \"" MFG_INFO "\" info section.");
        }
        // when you start checking device info signatures => uncomment this code
        if (validDevInfoCount != 1 && !show_itoc && (_readSectList.size() == 0 || find(_readSectList.begin(), _readSectList.end(), FS3_DEV_INFO) != _readSectList.end()) &&
            _fwImgInfo.supportedHwId[0] != ARCUSE_HW_ID) // ArcusE doesn't have DEV_INFO section
        {
            _badDevDataSections = true;
            if (validDevInfoCount == 0)
            {
                return errmsg(MLXFW_NO_VALID_DEVICE_INFO_ERR, "No \"" DEV_INFO "\" info section.");
            }
            // more than one valid devinfo:
            return errmsg(MLXFW_TWO_VALID_DEVICE_INFO_ERR, "Two \"" DEV_INFO "\" info sections.");
        }
    }

    return retVal;
}

bool Fs4Operations::FsVerifyAux(VerifyCallBack verifyCallBackFunc, bool show_itoc, struct QueryOptions queryOptions, bool ignoreDToc, bool verbose)
{
    DPRINTF(("Fs4Operations::FsVerifyAux\n"));
    u_int32_t dtocPtr;
    u_int8_t* buff;
    u_int32_t log2_chunk_size;
    bool is_image_in_odd_chunks;

    DPRINTF(("Fs4Operations::FsVerifyAux call getImgStart()\n"));
    if (!getImgStart())
    { // Set _fwImgInfo.imgStart with the image start address
        return false;
    }

    report_callback(verifyCallBackFunc, "\nFS4 failsafe image\n\n");

    _ioAccess->set_address_convertor(0, 0);
    DPRINTF(("Fs4Operations::FsVerifyAux call getExtendedHWAravaPtrs()\n"));
    if (!getExtendedHWAravaPtrs(verifyCallBackFunc, _ioAccess, false, true))
    {
        return false;
    }

    if (!ParseImageInfoFromEncryptedImage())
    {
        DPRINTF(("Fs4Operations::FsVerifyAux Failed to read IMAGE_INFO section"));
        return false;
    }

    // if nextBootFwVer is true, no need to get all the information, just the fw version is enough - therefore skip
    // everything else
    if (!nextBootFwVer)
    {
        DPRINTF(("Fs4Operations::FsVerifyAux call verifyToolsArea()\n"));
        if (!verifyToolsArea(verifyCallBackFunc))
        {
            return false;
        }

        // Update image cache till before boot2 header:
        DPRINTF(("Fs4Operations::FsVerifyAux call Fs3UpdateImgCache() - All before boot2\n"));
        READALLOCBUF((*_ioAccess), _fwImgInfo.imgStart, buff, _boot2_ptr, "All Before Boot2");
        Fs3UpdateImgCache(buff, 0, _boot2_ptr);
        free(buff);

        _ioAccess->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, _fwImgInfo.imgStart != 0);

        // Get BOOT2 -Get Only boot2Size if quickQuery == true else read and check CRC of boot2 section as well
        DPRINTF(("Fs4Operations::FsVerifyAux call FS3_CHECKB2()\n"));
        FS3_CHECKB2(0, _boot2_ptr, !queryOptions.quickQuery, PRE_CRC_OUTPUT, verifyCallBackFunc);

        _fs4ImgInfo.firstItocArrayIsEmpty = false;
        _fs4ImgInfo.itocArr.tocArrayAddr = _itoc_ptr;

        DPRINTF(("Fs4Operations::FsVerifyAux call isHashesTableHwPtrValid()\n"));
        if (isHashesTableHwPtrValid())
        {
            //* Check hashes_table header CRC
            READALLOCBUF((*_ioAccess), _hashes_table_ptr, buff, IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE, "HASHES TABLE HEADER");
            // Calculate CRC
            u_int32_t hashes_table_header_calc_crc = CalcImageCRC((u_int32_t*)buff, (IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE / 4) - 1);
            // Read CRC
            u_int32_t hashes_table_header_crc = ((u_int32_t*)buff)[(IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE / 4) - 1];
            free(buff);
            TOCPU1(hashes_table_header_crc)
            hashes_table_header_crc = hashes_table_header_crc & 0xFFFF;
            // Compare calculated crc with crc from image
            if (hashes_table_header_calc_crc != hashes_table_header_crc)
            {
                report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n", "HASHES TABLE HEADER", _hashes_table_ptr + IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE - 4,
                                hashes_table_header_calc_crc, hashes_table_header_crc);
                if (!_fwParams.ignoreCrcCheck)
                {
                    return errmsg("Bad CRC");
                }
            }

            vector<u_int8_t> hashes_table_data;
            if (!GetHashesTableData(hashes_table_data))
            {
                return false;
            }
            buff = hashes_table_data.data();
            const u_int32_t hashes_table_size = hashes_table_data.size();

            Fs3UpdateImgCache(buff, _hashes_table_ptr, hashes_table_size);

            //* Check hashes_table CRC
            // Calculate CRC
            u_int32_t hashes_table_calc_crc = CalcImageCRC((u_int32_t*)buff, (hashes_table_size / 4) - 1);
            // Read CRC
            u_int32_t hashes_table_crc = ((u_int32_t*)buff)[(hashes_table_size / 4) - 1];
            TOCPU1(hashes_table_crc)
            hashes_table_crc = hashes_table_crc & 0xFFFF;
            if (!DumpFs3CRCCheck(FS4_HASHES_TABLE, _hashes_table_ptr, hashes_table_size, hashes_table_calc_crc, hashes_table_crc, false, verifyCallBackFunc))
            {
                return false;
            }
        }

        DPRINTF(("Fs4Operations::FsVerifyAux call verifyTocHeader() ITOC\n"));
        if (!verifyTocHeader(_itoc_ptr, false, verifyCallBackFunc))
        {
            _itoc_ptr += FS4_DEFAULT_SECTOR_SIZE;
            _fs4ImgInfo.itocArr.tocArrayAddr = _itoc_ptr;
            _fs4ImgInfo.firstItocArrayIsEmpty = true;
            if (!verifyTocHeader(_itoc_ptr, false, verifyCallBackFunc))
            {
                return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid ITOC Header was found.");
            }
        }
    }
    if (_ioAccess->is_flash() == false && _signatureDataSet == false)
    {
        // read the MDK HW pointed data from the image (binary file). Don't read from flash!
        int signature_size = 3 * HMAC_SIGNATURE_LENGTH;
        uint8_t signature_data[3 * HMAC_SIGNATURE_LENGTH] = {0};
        int signature_offset = _digest_mdk_ptr;
        if (signature_offset == 0)
        {
            signature_offset = _digest_recovery_key_ptr;
        }
        if (signature_offset != 0)
        {
            READBUF((*_ioAccess), signature_offset, signature_data, signature_size, "Reading data pointed by HW MDK Pointer");

            Fs3UpdateImgCache(signature_data, signature_offset, signature_size);
        }
        _signatureDataSet = true;
    }
    DPRINTF(("Fs4Operations::FsVerifyAux call verifyTocEntries() ITOC\n"));
    if (!verifyTocEntries(_itoc_ptr, show_itoc, false, queryOptions, verifyCallBackFunc, verbose))
    {
        return false;
    }
    if (nextBootFwVer)
    {
        return true;
    }
    if (ignoreDToc)
    {
        return true;
    }
    // Verify DTOC:
    log2_chunk_size = _ioAccess->get_log2_chunk_size();
    is_image_in_odd_chunks = _ioAccess->get_is_image_in_odd_chunks();
    _ioAccess->set_address_convertor(0, 0);
    //-Verify DToC Header:
    bool dtocExists;
    if (!IsDtocExists(dtocExists))
    {
        return false;
    }
    if (dtocExists)
    {
        // We have a DTOC to verify
        if (!GetDtocAddress(dtocPtr))
        {
            return false;
        }
        DPRINTF(("Fs4Operations::FsVerifyAux call verifyTocHeader() DTOC\n"));
        if (!verifyTocHeader(dtocPtr, true, verifyCallBackFunc))
        {
            return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid DTOC Header was found.");
        }
        _fs4ImgInfo.dtocArr.tocArrayAddr = dtocPtr;
        //-Verify DToC Entries:
        DPRINTF(("Fs4Operations::FsVerifyAux call verifyTocEntries() DTOC\n"));
        if (!verifyTocEntries(dtocPtr, show_itoc, true, queryOptions, verifyCallBackFunc, verbose))
        {
            _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
            return false;
        }
    }
    _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
    return true;
}

bool Fs4Operations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    if (isStripedImage)
    {
        ignoreDToc = true;
        SetIsReducedImage(true);
    }
    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }
    if (image_encrypted)
    {
        //* Verify DTOC CRCs only
        if (!ignoreDToc)
        {
            if (!ParseDevData(false, false, verifyCallBackFunc, showItoc))
            {
                return errmsg("%s", err());
            }
        }
        return true;
    }

    return Fs3Operations::FwVerify(verifyCallBackFunc, isStripedImage, showItoc, ignoreDToc);
}

bool Fs4Operations::FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool)
{
    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }
    if (image_encrypted)
    {
        return errmsg("Operation not supported on an encrypted %s", _ioAccess->is_flash() ? "flash" : "image");
    }

    return Fs3Operations::FwGetSection(sectType, sectInfo);
}

bool Fs4Operations::GetImageInfo(u_int8_t* buff)
{
    DPRINTF(("Fs4Operations::GetImageInfo call Fs3Operations::GetImageInfo\n"));
    bool success = Fs3Operations::GetImageInfo(buff);

    //* Fix burn_image_size if required (required only for BB first FW release)
    if (success && !_ioAccess->is_flash() /*image*/)
    {
        DPRINTF(("Fs4Operations::GetImageInfo check if fix burn_image_size is required\n"));
        bool is_encrypted_image;
        if (!IsEncryptedImage(is_encrypted_image))
        {
            return false;
        }
        if ((is_encrypted_image || _encrypted_image_io_access) && _fwImgInfo.ext_info.burn_image_size == 0)
        {
            DPRINTF(("Fs4Operations::GetImageInfo read burn_image_size from the address 16MB\n"));
            //* Read burn_image_size from the address 16MB ("outside" the range that we burn)
            u_int32_t burn_image_size;
            u_int8_t* buff;
            //* Choosing the correct io to read from
            FBase* io = _ioAccess;
            if (_encrypted_image_io_access)
            {
                io = _encrypted_image_io_access; // If encrypted image was given we'll read from it
            }

            READALLOCBUF((*io), ENCRYPTED_BURN_IMAGE_SIZE_LOCATION_IN_BYTES, buff, 4,
                         "IMAGE_LAST_ADDR"); // Reading DWORD from addr 16MB
            burn_image_size = ((u_int32_t*)buff)[0];
            TOCPU1(burn_image_size);
            free(buff);
            _fwImgInfo.ext_info.burn_image_size = burn_image_size;
        }
    }
    return true;
}

bool Fs4Operations::GetDtocAddress(u_int32_t& dTocAddress)
{
    u_int32_t imageSize = _ioAccess->get_effective_size();

    if (_fwImgInfo.ext_info.dtoc_offset != 0)
    {
        dTocAddress = (imageSize / (_fwImgInfo.ext_info.dtoc_offset * 2)) - FS4_DEFAULT_SECTOR_SIZE;
    }
    else
    {
        dTocAddress = imageSize - FS4_DEFAULT_SECTOR_SIZE;
    }

    return true;
}

bool Fs4Operations::CheckDevRSAPublicKeyUUID()
{
    //* Read RSA_PUBLIC_KEY section
    u_int32_t rsa_public_keys_section_addr = _public_key_ptr + _fwImgInfo.imgStart;
    DPRINTF(("Fs4Operations::CheckDevRSAPublicKeyUUID rsa_public_keys_section_addr = 0x%x\n", rsa_public_keys_section_addr));
    vector<u_int8_t> rsa_public_keys_data;
    rsa_public_keys_data.resize(IMAGE_LAYOUT_PUBLIC_KEYS_3_SIZE);
    if (!_ioAccess->read(rsa_public_keys_section_addr, rsa_public_keys_data.data(), IMAGE_LAYOUT_PUBLIC_KEYS_3_SIZE))
    {
        return errmsg("%s - read error (%s)\n", "RSA_PUBLIC_KEY", (*_ioAccess).err());
    }

    //* Check if key uuid is dev
    image_layout_public_keys_3 public_keys_3;
    image_layout_public_keys_3_unpack(&public_keys_3, rsa_public_keys_data.data());
    GetImgSigInfo(public_keys_3.file_public_keys_3[0].keypair_uuid);

    return true;
}

bool Fs4Operations::IsDtocExists(bool& dtocExists)
{
    dtocExists = true;
    if (!_ioAccess->is_flash())
    {
        // In case of image, need to check if it's reduced (without DTOC)
        bool isEncryptedImage;
        if (!IsEncryptedImage(isEncryptedImage))
        {
            return false;
        }
        u_int32_t imageSize;
        if (isEncryptedImage)
        {
            if (!GetEncryptedImageSizeFromImageInfo(&imageSize))
            {
                return false;
            }
        }
        else
        {
            imageSize = getImageSize();
        }

        if (_ioAccess->get_effective_size() <= imageSize)
        {
            dtocExists = false;
        }
    }

    return true;
}

bool Fs4Operations::ParseImageInfoFromEncryptedImage()
{
    //* Read IMAGE_INFO section
    u_int32_t image_info_section_addr = _image_info_section_ptr + _fwImgInfo.imgStart;
    DPRINTF(("Fs4Operations::ParseImageInfoFromEncryptedImage image_info_section_addr = 0x%x\n", image_info_section_addr));
    vector<u_int8_t> image_info_data;
    image_info_data.resize(IMAGE_LAYOUT_IMAGE_INFO_SIZE);
    if (!_ioAccess->read(image_info_section_addr, image_info_data.data(), IMAGE_LAYOUT_IMAGE_INFO_SIZE))
    {
        return errmsg("%s - read error (%s)\n", "IMAGE_INFO", (*_ioAccess).err());
    }

    //* Parse IMAGE_INFO section
    if (!GetImageInfo(image_info_data.data()))
    {
        return errmsg("Failed to parse IMAGE_INFO section - %s", err());
    }

    return true;
}

bool Fs4Operations::ParseDevData(bool quickQuery, bool verbose, VerifyCallBack verifyCallBackFunc, bool showItoc)
{
    bool dtocExists;
    if (!IsDtocExists(dtocExists))
    {
        return false;
    }
    if (dtocExists)
    {
        if (!InitHwPtrs())
        {
            DPRINTF(("Fs4Operations::encryptedFwQuery HW pointers not found"));
            return false;
        }

        if (!ParseImageInfoFromEncryptedImage())
        {
            DPRINTF(("Fs4Operations::GetEncryptedImageSizeFromImageInfo Failed to read IMAGE_INFO section"));
            return false;
        }

        // We have a DTOC to parse
        _ioAccess->set_address_convertor(0, 0);
        // Parse DTOC header:
        u_int32_t dtoc_addr = _ioAccess->get_size() - FS4_DEFAULT_SECTOR_SIZE;
        if (!GetDtocAddress(dtoc_addr))
        {
            return false;
        }
        DPRINTF(("Fs4Operations::ParseDevData call verifyTocHeader() DTOC, dtoc_addr = 0x%x\n", dtoc_addr));
        if (!verifyTocHeader(dtoc_addr, true, verifyCallBackFunc))
        {
            return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid DTOC Header was found.");
        }
        _fs4ImgInfo.dtocArr.tocArrayAddr = dtoc_addr;

        // Parse DTOC entries:
        struct QueryOptions queryOptions;
        queryOptions.readRom = false;
        queryOptions.quickQuery = quickQuery;
        DPRINTF(("Fs4Operations::ParseDevData call verifyTocEntries() DTOC\n"));
        if (!verifyTocEntries(dtoc_addr, showItoc, true, queryOptions, verifyCallBackFunc, verbose))
        {
            return false;
        }
    }

    return true;
}

bool Fs4Operations::encryptedFwQuery(fw_info_t* fwInfo, bool quickQuery, bool ignoreDToc, bool verbose)
{
    DPRINTF(("Fs4Operations::encryptedFwQuery\n"));

    if (!InitHwPtrs())
    {
        DPRINTF(("Fs4Operations::encryptedFwQuery HW pointers not found"));
        return false;
    }

    if (!ParseImageInfoFromEncryptedImage())
    {
        DPRINTF(("Fs4Operations::encryptedFwQuery Failed to read IMAGE_INFO section"));
        return false;
    }

    if (!CheckDevRSAPublicKeyUUID())
    {
        return false;
    }

    if (!ignoreDToc)
    {
        if (!ParseDevData(quickQuery, verbose))
        {
            return false;
        }
    }

    if (!QuerySecurityFeatures())
    {
        return false;
    }

    _fwImgInfo.ext_info.is_failsafe = true;
    memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs3_info), &(_fs3ImgInfo.ext_info), sizeof(fs3_info_t));
    fwInfo->fw_type = FwType();

    return true;
}

bool Fs4Operations::FwQuery(fw_info_t* fwInfo, bool readRom, bool isStripedImage, bool quickQuery, bool ignoreDToc, bool verbose)
{
    DPRINTF(("Fs4Operations::FwQuery\n"));
    if (isStripedImage)
    {
        SetIsReducedImage(true);
        ignoreDToc = true;
    }

    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }
    if (image_encrypted)
    {
        return encryptedFwQuery(fwInfo, quickQuery, ignoreDToc, verbose);
    }

    if (!Fs3Operations::FwQuery(fwInfo, readRom, isStripedImage, quickQuery, ignoreDToc, verbose))
    {
        return false;
    }

    if (!QuerySecurityFeatures())
    {
        return false;
    }

    memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs3_info), &(_fs3ImgInfo.ext_info), sizeof(fs3_info_t));

    return true;
}

bool Fs4Operations::IsLifeCycleAccessible(chip_type_t chip_type)
{
    DPRINTF(("Fs4Operations::IsLifeCycleAccessible\n"));
    bool res = true;
    if (IsLifeCycleSupported())
    {
        if (dm_is_livefish_mode(getMfileObj()))
        {
            switch (chip_type)
            {
                case CT_BLUEFIELD2:
                case CT_CONNECTX6DX:
                case CT_CONNECTX6LX:
                    // HW bug - life-cycle CR-space is blocked in livefish mode on these devices
                    res = false;
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        res = false;
    }

    DPRINTF(("Fs4Operations::IsLifeCycleAccessible res = %s\n", res ? "TRUE" : "FALSE"));
    return res;
}

bool Fs4Operations::IsSecurityVersionAccessible(chip_type_t chip_type)
{
    DPRINTF(("Fs4Operations::IsSecurityVersionAccessible\n"));
    bool res = true;
    // Security version feature depends on life-cycle
    if (IsLifeCycleSupported())
    {
        switch (chip_type)
        {
            case CT_BLUEFIELD2:
            case CT_CONNECTX6DX:
            case CT_CONNECTX6LX:
            case CT_QUANTUM3:
            case CT_NVLINK6_SWITCH:
            case CT_CONNECTX8:
            case CT_CONNECTX8_PURE_PCIE_SWITCH:
            case CT_CONNECTX9:
            case CT_CONNECTX9_PURE_PCIE_SWITCH:
            case CT_ARCUSE:
                res = false;
                break;
            default:
                break;
        }
    }
    else
    {
        res = false;
    }

    DPRINTF(("Fs4Operations::IsSecurityVersionAccessible res = %s\n", res ? "TRUE" : "FALSE"));
    return res;
}

bool Fs4Operations::QuerySecurityFeatures()
{
    DPRINTF(("Fs4Operations::QuerySecurityFeatures _fwImgInfo.ext_info.chip_type = %d\n", _fwImgInfo.ext_info.chip_type));
    _fs3ImgInfo.ext_info.image_security_version = _security_version;
    _fs3ImgInfo.ext_info.device_security_version_access_method = NOT_VALID;
    if (_ioAccess->is_flash())
    {
        try
        {
            if (IsLifeCycleAccessible(_fwImgInfo.ext_info.chip_type))
            {
                CRSpaceRegisters crSpaceReg(getMfileObj(), _fwImgInfo.ext_info.chip_type);
                _fs3ImgInfo.ext_info.life_cycle = crSpaceReg.getLifeCycle();
                _fs3ImgInfo.ext_info.global_image_status = crSpaceReg.getGlobalImageStatus();

                if (CRSpaceRegisters::IsLifeCycleSecured(_fs3ImgInfo.ext_info.life_cycle))
                {
                    if (IsSecurityVersionAccessible(_fwImgInfo.ext_info.chip_type))
                    {
                        _fs3ImgInfo.ext_info.device_security_version_gw = crSpaceReg.getSecurityVersion();
                        _fs3ImgInfo.ext_info.device_security_version_access_method = DIRECT_ACCESS;
                    }
                }
            }
        }
        catch (exception& e)
        {
            printf("%s\n", e.what());
            return false;
        }
    }

    return true;
}

u_int8_t Fs4Operations::FwType()
{
    return FIT_FS4;
}

bool Fs4Operations::FwInit()
{
    if (!Fs3Operations::FwInit())
    {
        return false;
    }
    _fs4ImgInfo.firstItocArrayIsEmpty = 0;
    _fs4ImgInfo.smallestDTocAddr = 0;
    _fwImgInfo.fwType = (fw_img_type_t)FwType();
    return true;
}

bool Fs4Operations::CheckFs4ImgSize(Fs4Operations& imageOps, bool useImageDevData)
{
    // check if max itoc is not overwriting the chunk
    if (imageOps._fwImgInfo.lastImageAddr >= (u_int32_t)(imageOps._fwImgInfo.imgStart + (1 << imageOps._maxImgLog2Size)))
    {
        return errmsg(MLXFW_IMAGE_TOO_LARGE_ERR, "Last ITOC section ends at address (0x%x) which is greater than max size of image (0x%x)", imageOps._fwImgInfo.lastImageAddr,
                      imageOps._maxImgLog2Size);
    }

    // check if minimal dtoc section is not overwriting max itoc section
    if (useImageDevData)
    {
        if (imageOps._fs4ImgInfo.smallestDTocAddr < imageOps._fwImgInfo.lastImageAddr)
        {
            return errmsg(MLXFW_DTOC_OVERWRITE_CHUNK, "First DTOC address (0x%x) is less than last ITOC address (0x%x)", imageOps._fs4ImgInfo.smallestDTocAddr, imageOps._fwImgInfo.lastImageAddr);
        }
    }

    return true;
}

bool Fs4Operations::GetEncryptedImageSizeFromImageInfo(u_int32_t* imageSize)
{
    DPRINTF(("Fs4Operations::GetEncryptedImageSizeFromImageInfo\n"));
    if (!_is_hw_ptrs_initialized)
    {
        if (!InitHwPtrs())
        {
            DPRINTF(("Fs4Operations::GetEncryptedImageSizeFromImageInfo HW pointers not found"));
            return false;
        }
    }

    if (!ParseImageInfoFromEncryptedImage())
    {
        DPRINTF(("Fs4Operations::GetEncryptedImageSizeFromImageInfo Failed to read IMAGE_INFO section"));
        return false;
    }
    *imageSize = _fwImgInfo.ext_info.burn_image_size;
    return true;
}

bool Fs4Operations::FwReadEncryptedData(void* image, u_int32_t imageSize, bool verbose)
{
    DPRINTF(("Fs4Operations::FwReadEncryptedData\n"));
    vector<u_int8_t> data;
    data.resize(imageSize);
    if (!(*_ioAccess).read(_fwImgInfo.imgStart, data.data(), imageSize, verbose))
    {
        return errmsg("%s - read error (%s)\n", "Image", (*_ioAccess).err());
    }
    memcpy(image, data.data(), imageSize);
    return true;
}

bool Fs4Operations::FwReadData(void* image, u_int32_t* imageSize, bool verbose)
{
    //* Read encrypted data
    bool is_encrypted = false;
    DPRINTF(("Fs4Operations::FwReadData\n"));
    if (!isEncrypted(is_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }
    if (is_encrypted)
    {
        if (image == NULL)
        {
            bool result = GetEncryptedImageSizeFromImageInfo(imageSize);
            DPRINTF(("Fs4Operations::FwReadData imageSize=0x%x result=%s\n", *imageSize, result ? "true" : "false"));
            return result;
        }
        else
        {
            return FwReadEncryptedData(image, *imageSize, verbose);
        }
    }

    //* Read non-encrypted data
    struct QueryOptions queryOptions;
    if (!imageSize)
    {
        return errmsg("bad parameter is given to FwReadData\n");
    }

    queryOptions.readRom = true;
    queryOptions.quickQuery = false;
    if (image == NULL)
    {
        // When we need only to get size, no need for reading entire image
        queryOptions.readRom = false;
        queryOptions.quickQuery = true;
    }
    // Avoid Warning
    if (!FsVerifyAux((VerifyCallBack)NULL, 0, queryOptions, false, verbose))
    {
        return false;
    }

    _imageCache.get((u_int8_t*)image, _fwImgInfo.lastImageAddr);
    // size will be always as (_ioAccess)->get_size(), as the dtoc always at the end
    *imageSize = (_ioAccess)->get_size();

    // take device sections
    if (image != NULL)
    {
        _imageCache.get((u_int8_t*)image + _fs4ImgInfo.smallestDTocAddr, _fs4ImgInfo.smallestDTocAddr, (_ioAccess)->get_size() - _fs4ImgInfo.smallestDTocAddr);
    }

    return true;
}

bool Fs4Operations::Fs4RemoveSectionAux(fs3_section_t sectionType)
{
    int itocEntryIndex = 0;
    struct fs4_toc_info* itocEntry = (struct fs4_toc_info*)NULL;
    TocArray* itocArray = &_fs4ImgInfo.itocArr;

    if (!Fs4GetItocInfo(itocArray->tocArr, itocArray->numOfTocs, sectionType, itocEntry, itocEntryIndex))
    {
        return false;
    }

    u_int32_t sectionSizeInBytes = itocEntry->section_data.size();
    u_int32_t sectionSizeInDW = sectionSizeInBytes >> 2;

    // update the sections that are after this section
    for (int i = itocEntryIndex + 1; i < itocArray->numOfTocs; i++)
    {
        struct fs4_toc_info* tocInfo = itocArray->tocArr + i;
        tocInfo->toc_entry.flash_addr = tocInfo->toc_entry.flash_addr - sectionSizeInDW;
        tocInfo->entry_addr = tocInfo->entry_addr - IMAGE_LAYOUT_ITOC_ENTRY_SIZE;

        updateTocEntryCRC(tocInfo);

        updateTocEntryData(tocInfo);

        Fs3UpdateImgCache(tocInfo->data, tocInfo->entry_addr, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
        Fs3UpdateImgCache(tocInfo->section_data.data(), tocInfo->toc_entry.flash_addr << 2, tocInfo->toc_entry.size << 2);
    }

    _fwImgInfo.lastImageAddr = _fwImgInfo.lastImageAddr - sectionSizeInBytes;

    // remove the itoc from the array and update the cache
    for (int i = itocEntryIndex + 1; i < (itocArray->numOfTocs + 1); i++)
    {
        TocArray::copyTocArrEntry(itocArray->tocArr + i - 1, itocArray->tocArr + i);
    }

    _fs4ImgInfo.itocArr.numOfTocs--;

    u_int32_t lastItocSectAddress = itocArray->tocArrayAddr + IMAGE_LAYOUT_ITOC_HEADER_SIZE + itocArray->numOfTocs * IMAGE_LAYOUT_ITOC_ENTRY_SIZE;
    updateTocEndEntryInImgCache(lastItocSectAddress);

    return true;
}

bool Fs4Operations::Fs4RemoveSection(fs3_section_t sectionType, ProgressCallBack progressFunc)
{
    vector<u_int8_t> newImageData;

    if (!Fs4RemoveSectionAux(sectionType))
    {
        return false;
    }

    _imageCache.get(newImageData, 0, (_ioAccess)->get_size());

    burnDataParamsT params;
    params.data = (u_int32_t*)&newImageData[0];
    params.dataSize = newImageData.size();
    params.progressFunc = progressFunc;
    params.calcSha = _signatureExists;
    if (!FwBurnData(params))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    // run int query to get product ver
    if (!FsIntQueryAux(true, false))
    {
        return false;
    }

    if (!RomCommonCheck(ignoreProdIdCheck, true))
    {
        return false;
    }

    return Fs4RemoveSection(FS3_ROM_CODE, progressFunc);
}

bool Fs4Operations::Fs4AddSectionAux(fs3_section_t sectionType, enum CRCTYPE crcType, u_int8_t zippedImage, u_int32_t* newSectData, u_int32_t newSectSize)
{
    struct fs4_toc_info* itocEntry = (struct fs4_toc_info*)NULL;
    int itocEntryIndex = 0;
    TocArray* itocArray = &_fs4ImgInfo.itocArr;
    struct fs4_toc_info* newITocEntry;

    // search for the section, remove it if found
    if (Fs4GetItocInfo(itocArray->tocArr, itocArray->numOfTocs, sectionType, itocEntry, itocEntryIndex))
    {
        if (getImageSize() - (itocEntry->toc_entry.size << 2) + newSectSize > (u_int32_t)(1 << _maxImgLog2Size))
        {
            return errmsg("Section size is too large");
        }
        if (!Fs4RemoveSectionAux(sectionType))
        {
            return false;
        }
    }
    else
    {
        if (getImageSize() + newSectSize > (u_int32_t)(1 << _maxImgLog2Size))
        {
            return errmsg("Section size is too large");
        }
        if (itocArray->numOfTocs + 1 > MAX_TOCS_NUM)
        {
            return errmsg("Cannot add TOC entry, too many entries in iTOC array.");
        }
    }

    newITocEntry = itocArray->tocArr + itocArray->numOfTocs;

    // update the new itoc entry
    Fs4Operations::TocArray::initEmptyTocArrEntry(newITocEntry);

    newITocEntry->entry_addr = itocArray->tocArrayAddr + TOC_HEADER_SIZE + itocArray->numOfTocs * TOC_ENTRY_SIZE;
    newITocEntry->toc_entry.type = sectionType;
    newITocEntry->toc_entry.size = newSectSize >> 2;
    newITocEntry->toc_entry.flash_addr = (_fwImgInfo.lastImageAddr - _fwImgInfo.imgStart) >> 2;
    newITocEntry->toc_entry.crc = crcType;
    newITocEntry->toc_entry.zipped_image = zippedImage;
    newITocEntry->toc_entry.section_crc = CalcImageCRC((u_int32_t*)newSectData, newSectSize >> 2);

    updateTocEntryCRC(newITocEntry);

    updateTocEntryData(newITocEntry);

    updateTocEntrySectionData(newITocEntry, (u_int8_t*)newSectData, newSectSize);

    itocArray->numOfTocs++;

    _fwImgInfo.lastImageAddr += newSectSize;

    Fs3UpdateImgCache(newITocEntry->data, newITocEntry->entry_addr, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);

    u_int32_t lastItocSectAddress = itocArray->tocArrayAddr + IMAGE_LAYOUT_ITOC_HEADER_SIZE + itocArray->numOfTocs * IMAGE_LAYOUT_ITOC_ENTRY_SIZE;
    updateTocEndEntryInImgCache(lastItocSectAddress);

    Fs3UpdateImgCache(newITocEntry->section_data.data(), newITocEntry->toc_entry.flash_addr << 2, newITocEntry->toc_entry.size << 2);

    return true;
}

bool Fs4Operations::Fs4AddSection(fs3_section_t sectionType, enum CRCTYPE crcType, u_int8_t zippedImage, u_int32_t* newSectData, u_int32_t newSectSize, ProgressCallBack progressFunc)
{
    vector<u_int8_t> newImageData;

    if (!Fs4AddSectionAux(sectionType, crcType, zippedImage, newSectData, newSectSize))
    {
        return false;
    }

    _imageCache.get(newImageData, 0, (_ioAccess)->get_size());
    burnDataParamsT params;
    params.data = (u_int32_t*)&newImageData[0];
    params.dataSize = newImageData.size();
    params.progressFunc = progressFunc;
    params.calcSha = _signatureExists;
    if (!FwBurnData(params))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::FwBurnRom(FImage* romImg, bool ignoreProdIdCheck, bool ignoreDevidCheck, ProgressCallBack progressFunc)
{
    roms_info_t romsInfo;

    if (romImg == NULL)
    {
        return errmsg("Bad ROM image is given.");
    }

    if (romImg->getBufLength() == 0)
    {
        return errmsg("Bad ROM file: Empty file.");
    }

    if (!FwOperations::getRomsInfo(romImg, romsInfo))
    {
        return errmsg("Failed to read given ROM.");
    }

    if (!FsIntQueryAux(false, false))
    {
        return false;
    }

    if (!ignoreDevidCheck && !FwOperations::checkMatchingExpRomDevId(_fwImgInfo.ext_info.dev_type, romsInfo))
    {
        return errmsg("Image file ROM: FW is for device %d, but Exp-ROM is "
                      "for device %d\n",
                      _fwImgInfo.ext_info.dev_type, romsInfo.exp_rom_com_devid);
    }

    if (!RomCommonCheck(ignoreProdIdCheck, false))
    {
        return false;
    }

    if (romImg->getBuf() == NULL)
    {
        return false;
    }
    return Fs4AddSection(FS3_ROM_CODE, INITOCENTRY, 0, romImg->getBuf(), romImg->getBufLength(), progressFunc);
}

void Fs4Operations::updateTocEndEntryInImgCache(u_int32_t lastItocSectAddress)
{
    u_int8_t tocEndBuff[IMAGE_LAYOUT_ITOC_ENTRY_SIZE];
    memset(tocEndBuff, FS3_END, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    Fs3UpdateImgCache(tocEndBuff, lastItocSectAddress, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
}

void Fs4Operations::updateTocEntryCRC(struct fs4_toc_info* tocEntry)
{
    u_int8_t tocEntryBuff[IMAGE_LAYOUT_ITOC_ENTRY_SIZE];

    memset(tocEntryBuff, 0, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    image_layout_itoc_entry_pack(&(tocEntry->toc_entry), tocEntryBuff);
    tocEntry->toc_entry.itoc_entry_crc = CalcImageCRC((u_int32_t*)tocEntryBuff, TOC_ENTRY_SIZE / 4 - 1);
}

void Fs4Operations::updateTocHeaderCRC(struct image_layout_itoc_header* tocHeader)
{
    u_int8_t tocHeaderBuff[IMAGE_LAYOUT_ITOC_HEADER_SIZE];

    memset(tocHeaderBuff, 0, IMAGE_LAYOUT_ITOC_HEADER_SIZE);
    image_layout_itoc_header_pack(tocHeader, tocHeaderBuff);
    tocHeader->itoc_entry_crc = CalcImageCRC((u_int32_t*)tocHeaderBuff, IMAGE_LAYOUT_ITOC_HEADER_SIZE / 4 - 1);
}

void Fs4Operations::updateTocEntryData(struct fs4_toc_info* tocEntry)
{
    memset(tocEntry->data, 0, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    image_layout_itoc_entry_pack(&(tocEntry->toc_entry), tocEntry->data);
}

void Fs4Operations::updateTocEntrySectionData(struct fs4_toc_info* tocEntry, u_int8_t* data, u_int32_t dataSize)
{
    tocEntry->section_data.resize(dataSize);
    memcpy(tocEntry->section_data.data(), data, dataSize);
}

bool Fs4Operations::restoreWriteProtection(mflash* mfl, u_int8_t banksNum, write_protect_info_t protect_info[])
{
    for (unsigned int i = 0; i < banksNum; i++)
    {
        int rc = mf_set_write_protect(mfl, i, protect_info + i);
        if (rc != MFE_OK)
        {
            return errmsg("Failed to restore write protection settings: %s", mf_err2str(rc));
        }
    }
    return true;
}

bool Fs4Operations::CreateDtoc(vector<u_int8_t>& img, u_int8_t* SectionData, u_int32_t section_size, u_int32_t flash_data_addr, fs3_section_t section, u_int32_t tocEntryAddr, CRCTYPE crc)
{
    struct fs4_toc_info itoc_info;
    memset(&itoc_info.data, 0, sizeof(itoc_info.data));
    memset(&itoc_info.toc_entry, 0, sizeof(struct image_layout_itoc_entry));
    itoc_info.section_data.resize(section_size, 0xff);
    itoc_info.entry_addr = tocEntryAddr;
    struct image_layout_itoc_entry* toc_entry_p = &(itoc_info.toc_entry);
    toc_entry_p->size = section_size >> 2;
    toc_entry_p->type = (u_int8_t)section;
    toc_entry_p->crc = (int)crc;
    toc_entry_p->flash_addr = flash_data_addr >> 2;
    if (crc == INITOCENTRY)
    {
        u_int32_t new_crc = CalcImageCRC((u_int32_t*)SectionData, toc_entry_p->size);
        toc_entry_p->section_crc = new_crc;
    }
    updateTocEntryCRC(&itoc_info);
    u_int8_t itoc_data[IMAGE_LAYOUT_ITOC_ENTRY_SIZE] = {0};
    image_layout_itoc_entry_pack(toc_entry_p, itoc_data);
    memcpy(img.data() + tocEntryAddr, itoc_data, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    return true;
}

#define CONNECTX5_NV_LOG_SIZE 2 * (CONNECTX5_NV_DATA_SIZE)
#define CX5_FLASH_SIZE 0x1000000

bool Fs4Operations::RestoreDevToc(vector<u_int8_t>& img, char* psid, dm_dev_id_t devid_t, const image_layout_uid_entry& base_guid, const image_layout_uid_entry& base_mac)
{
    /*DTOC HEADER*/

    u_int32_t flash_data_addr = 0;
    u_int32_t flash_size = 2 * CX5_FLASH_SIZE;
    u_int32_t nvlogSize = CONNECTX5_NV_LOG_SIZE;
    if (devid_t == DeviceConnectX5)
    {
        flash_size = CX5_FLASH_SIZE;
        nvlogSize = CONNECTX5_NV_LOG_SIZE / 2;
    }

    img.resize(flash_size, 0xff);
    u_int32_t dtocPtr = flash_size - FS4_DEFAULT_SECTOR_SIZE;
    u_int8_t dtocHeader[] = {0x44, 0x54, 0x4f, 0x43, 0x04, 0x08, 0x15, 0x16, 0x23, 0x42, 0xca, 0xfa, 0xba, 0xca, 0xfe, 0x00,
                             0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x90};

    memcpy(img.data() + dtocPtr, dtocHeader, IMAGE_LAYOUT_ITOC_HEADER_SIZE);
    u_int32_t section_index = 0;
    u_int32_t entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    /* NV_LOG */
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xf90000;
    }
    else
    {
        flash_data_addr = 0x1f00000;
    }
    u_int8_t NvLogBuffer[CONNECTX5_NV_LOG_SIZE] = {0};
    memcpy(img.data() + flash_data_addr, NvLogBuffer, nvlogSize);
    CreateDtoc(img, NvLogBuffer, CONNECTX5_NV_LOG_SIZE, flash_data_addr, FS3_FW_NV_LOG, entryAddr, NOCRC);

    /* NV_DATA 0*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xfb0000;
    }
    else
    {
        flash_data_addr = 0x1f20000;
    }
    u_int8_t NvDataBuffer[CONNECTX5_NV_DATA_SIZE] = {0};
    memcpy(img.data() + flash_data_addr, NvDataBuffer, CONNECTX5_NV_DATA_SIZE);
    CreateDtoc(img, NvDataBuffer, CONNECTX5_NV_DATA_SIZE, flash_data_addr, FS3_NV_DATA0, entryAddr, NOCRC);

    /* NV_DATA 2*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xfc0000;
    }
    else
    {
        flash_data_addr = 0x1f40000;
    }

    memcpy(img.data() + flash_data_addr, NvDataBuffer, CONNECTX5_NV_DATA_SIZE);
    CreateDtoc(img, NvDataBuffer, CONNECTX5_NV_DATA_SIZE, flash_data_addr, FS3_NV_DATA2, entryAddr, NOCRC);

    /*DEV_INFO*/
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xfd0000;
    }
    else
    {
        flash_data_addr = 0x1f60000;
    }
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;

    struct image_layout_device_info dev_info;
    memset(&dev_info, 0, sizeof(dev_info));
    u_int8_t DevInfoBuffer[IMAGE_LAYOUT_DEVICE_INFO_SIZE] = {0};
    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;
    dev_info.minor_version = 0;
    dev_info.major_version = 2;
    dev_info.vsd_vendor_id = 0x15b3;

    dev_info.guids.guids.num_allocated = base_guid.num_allocated;
    dev_info.guids.guids.num_allocated_msb = base_guid.num_allocated_msb;
    dev_info.guids.guids.step = base_guid.step;
    dev_info.guids.guids.uid = base_guid.uid;
    dev_info.guids.macs.num_allocated = base_mac.num_allocated;
    dev_info.guids.macs.num_allocated_msb = base_mac.num_allocated_msb;
    dev_info.guids.macs.step = base_mac.step;
    dev_info.guids.macs.uid = base_mac.uid;

    image_layout_device_info_pack(&dev_info, DevInfoBuffer);
    u_int32_t newSectionCRC = CalcImageCRC((u_int32_t*)DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE / 4 - 1);
    u_int32_t newCRC = TOCPU1(newSectionCRC);
    ((u_int32_t*)DevInfoBuffer)[IMAGE_LAYOUT_DEVICE_INFO_SIZE / 4 - 1] = newCRC;

    memcpy(img.data() + flash_data_addr, DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE);
    CreateDtoc(img, DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE, flash_data_addr, FS3_DEV_INFO, entryAddr, INSECTION);

    /*DEV_INFO FAILSAFE*/
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xfe0000;
    }
    else
    {
        flash_data_addr = 0x1f70000;
    }
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;

    dev_info.signature0 = 0;
    dev_info.signature1 = 0;
    dev_info.signature2 = 0;
    dev_info.signature3 = 0;
    image_layout_device_info_pack(&dev_info, DevInfoBuffer);
    newSectionCRC = CalcImageCRC((u_int32_t*)DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE / 4 - 1);
    newCRC = TOCPU1(newSectionCRC);
    ((u_int32_t*)DevInfoBuffer)[IMAGE_LAYOUT_DEVICE_INFO_SIZE / 4 - 1] = newCRC;

    memcpy(img.data() + flash_data_addr, DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE);
    CreateDtoc(img, DevInfoBuffer, IMAGE_LAYOUT_DEVICE_INFO_SIZE, flash_data_addr, FS3_DEV_INFO, entryAddr, INSECTION);

    /*MFG_INFO*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    if (devid_t == DeviceConnectX5)
    {
        flash_data_addr = 0xff8000;
    }
    else
    {
        flash_data_addr = 0x1ff8000;
    }
    struct cx4fw_mfg_info cx4_mfg_info;
    u_int8_t MfgInfoData[CX4FW_MFG_INFO_SIZE] = {0};
    memset(&cx4_mfg_info, 0, sizeof(cx4_mfg_info));
    cx4_mfg_info.guids_override_en = 1; // get the GUIDs from DEV_INFO
    cx4_mfg_info.guids.guids.num_allocated = base_guid.num_allocated;
    cx4_mfg_info.guids.guids.step = base_guid.step;
    cx4_mfg_info.guids.guids.uid = base_guid.uid;
    cx4_mfg_info.guids.macs.num_allocated = base_mac.num_allocated;
    cx4_mfg_info.guids.macs.step = base_mac.step;
    cx4_mfg_info.guids.macs.uid = base_mac.uid;
    cx4_mfg_info.major_version = 1;
    cx4_mfg_info.minor_version = 0;
    strncpy(cx4_mfg_info.psid, psid, PSID_LEN);
    cx4fw_mfg_info_pack(&cx4_mfg_info, MfgInfoData);
    memcpy(img.data() + flash_data_addr, MfgInfoData, CX4FW_MFG_INFO_SIZE);
    CreateDtoc(img, MfgInfoData, CX4FW_MFG_INFO_SIZE, flash_data_addr, FS3_MFG_INFO, entryAddr, INITOCENTRY);

    /*VPD_R0*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    struct image_layout_itoc_entry toc_entry;
    memset(&toc_entry, 0, sizeof(struct image_layout_itoc_entry));
    u_int8_t entryBuffer[TOC_ENTRY_SIZE] = {0};
    flash_data_addr += CX4FW_MFG_INFO_SIZE;

    toc_entry.size = 0;
    toc_entry.type = FS3_VPD_R0;
    toc_entry.flash_addr = flash_data_addr >> 2;
    toc_entry.crc = (int)INITOCENTRY;
    toc_entry.section_crc = CalcImageCRC((u_int32_t*)NULL, toc_entry.size);
    image_layout_itoc_entry_pack(&toc_entry, entryBuffer);
    u_int32_t entry_crc = CalcImageCRC((u_int32_t*)entryBuffer, (TOC_ENTRY_SIZE / 4) - 1);
    toc_entry.itoc_entry_crc = entry_crc;
    image_layout_itoc_entry_pack(&toc_entry, entryBuffer);
    memcpy(img.data() + entryAddr, entryBuffer, TOC_ENTRY_SIZE);
    return true;
}

bool Fs4Operations::AlignDeviceSections(FwOperations* imageOps)
{
    bool rc = true;
    u_int8_t data[FS4_DEFAULT_SECTOR_SIZE] = {0};

    struct image_layout_itoc_header itocHeader;
    image_layout_itoc_header_unpack(&itocHeader, ((Fs4Operations*)imageOps)->_fs4ImgInfo.itocArr.tocHeader);

    if (itocHeader.flash_layout_version != 1)
    {
        return errmsg("Please update MFT package");
    }

    u_int32_t log2_chunk_size_bu = _ioAccess->get_log2_chunk_size();
    bool is_image_in_odd_chunks_bu = _ioAccess->get_is_image_in_odd_chunks();

    unsigned int retries = 0;
    const int nvLogIndex = 0, nvData0Index = 1, nvData1Index = 2, devInfo0Index = 3, devInfo1Index = 4;

    struct fs4_toc_info* sections[COUNT_OF_SECTIONS_TO_ALIGN] = {(struct fs4_toc_info*)NULL, (struct fs4_toc_info*)NULL, (struct fs4_toc_info*)NULL, (struct fs4_toc_info*)NULL,
                                                                 (struct fs4_toc_info*)NULL};

    const char* sectionsNames[COUNT_OF_SECTIONS_TO_ALIGN] = {GetSectionNameByType(FS3_FW_NV_LOG), GetSectionNameByType(FS3_NV_DATA0), GetSectionNameByType(FS3_NV_DATA2),
                                                             GetSectionNameByType(FS3_DEV_INFO), GetSectionNameByType(FS3_DEV_INFO)};

    const u_int32_t newOffsets[COUNT_OF_SECTIONS_TO_ALIGN] = {0xf90000, 0xfb0000, 0xfc0000, 0xfd0000, 0xfe0000};

    const u_int32_t offsets[COUNT_OF_SECTIONS_TO_ALIGN] = {0xc00000, 0xc10000, 0xc20000, 0xc30000, 0xc40000};

    // find related sections
    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* toc = &_fs4ImgInfo.dtocArr.tocArr[i];
        if (toc->toc_entry.type == FS3_FW_NV_LOG)
        {
            sections[nvLogIndex] = toc;
        }
        else if (toc->toc_entry.type == FS3_NV_DATA0)
        {
            sections[nvData0Index] = toc;
        }
        else if (toc->toc_entry.type == FS3_NV_DATA2)
        {
            sections[nvData1Index] = toc;
        }
        else if (toc->toc_entry.type == FS3_DEV_INFO)
        {
            if (sections[devInfo0Index])
            {
                sections[devInfo1Index] = toc;
            }
            else
            {
                sections[devInfo0Index] = toc;
            }
        }
    }

    for (unsigned int i = 0; i < COUNT_OF_SECTIONS_TO_ALIGN; i++)
    {
        if (sections[i] == NULL)
        {
            return errmsg("%s section was not found!", sectionsNames[i]);
        }
        if ((sections[i]->toc_entry.flash_addr << 2) != offsets[i])
        {
            return errmsg("The section %s was expected to be at address "
                          "0x%x but it is at 0x%x",
                          sectionsNames[i], offsets[i], sections[i]->toc_entry.flash_addr << 2);
        }
        for (int j = 0; j < _fs4ImgInfo.dtocArr.numOfTocs; j++)
        {
            struct fs4_toc_info* toc = &_fs4ImgInfo.dtocArr.tocArr[j];
            u_int32_t start = toc->toc_entry.flash_addr << 2;
            u_int32_t end = (toc->toc_entry.flash_addr << 2) + (toc->toc_entry.size << 2) - 1;
            if (checkIfSectionsOverlap(newOffsets[i], newOffsets[i] + (sections[i]->toc_entry.size << 2) - 1, start, end))
            {
                return errmsg("%s section's new address overlaps with %s section", sectionsNames[i], GetSectionNameByType(toc->toc_entry.type));
            }
        }
        // check if new offset overlaps with other new offsets
        for (unsigned int j = 0; j < COUNT_OF_SECTIONS_TO_ALIGN; j++)
        {
            if (i != j)
            {
                if (checkIfSectionsOverlap(newOffsets[i], newOffsets[i] + (sections[i]->toc_entry.size << 2) - 1, newOffsets[j], newOffsets[j] + (sections[j]->toc_entry.size << 2) - 1))
                {
                    return errmsg("%s section's new address overlaps with %s section new address", sectionsNames[i], sectionsNames[j]);
                }
            }
        }
    }

    FBase* origFlashObj = (FBase*)NULL;
    FBase* flashObjWithOcr = (FBase*)NULL;

    // Re-open flash with -ocr if needed
    if (_fwParams.ignoreCacheRep == 0)
    {
        origFlashObj = _ioAccess;
        _fwParams.ignoreCacheRep = 1;
        if (!FwOperations::FwAccessCreate(_fwParams, &_ioAccess))
        {
            _ioAccess = origFlashObj;
            _fwParams.ignoreCacheRep = 0;
            return errmsg("Failed to open device for direct flash access");
        }
        flashObjWithOcr = _ioAccess;
    }

    mflash* mfl = (mflash*)NULL;

    // disable write protection:
    ext_flash_attr_t attr;
    memset(&attr, 0x0, sizeof(attr));
    if (!((Flash*)_ioAccess)->get_attr(attr))
    {
        rc = false;
        goto cleanup;
    }

    mfl = ((Flash*)_ioAccess)->getMflashObj();
    write_protect_info_t protect_info;
    memset(&protect_info, 0, sizeof(protect_info));
    for (unsigned int i = 0; i < attr.banks_num; i++)
    {
        int rc = mf_set_write_protect(mfl, i, &protect_info);
        if (rc != MFE_OK)
        {
            errmsg("Failed to disable flash write protection: %s", mf_err2str(rc));
            rc = false;
            goto cleanup;
        }
    }

    while (((Flash*)_ioAccess)->is_flash_write_protected() && retries++ < 5)
    {
        msleep(500);
    }
    if (retries == 5)
    {
        errmsg("Failed to disable flash write protection");
        rc = false;
        goto cleanup;
    }

    if (flashObjWithOcr != NULL)
    {
        _ioAccess = origFlashObj;
        _fwParams.ignoreCacheRep = 0;
    }

    // read the sections from the flash
    _readSectList.push_back(FS3_FW_NV_LOG);
    _readSectList.push_back(FS3_NV_DATA0);
    _readSectList.push_back(FS3_NV_DATA2);
    _readSectList.push_back(FS3_DEV_INFO);
    if (!FsIntQueryAux())
    {
        _readSectList.pop_back();
        _readSectList.pop_back();
        _readSectList.pop_back();
        _readSectList.pop_back();
        rc = false;
        goto cleanup;
    }
    _readSectList.pop_back();
    _readSectList.pop_back();
    _readSectList.pop_back();
    _readSectList.pop_back();

    // move to the new offsets:
    for (unsigned int i = 0; i < COUNT_OF_SECTIONS_TO_ALIGN; i++)
    {
        // flash address is in DW and offset is given in bytes
        sections[i]->toc_entry.flash_addr = newOffsets[i] >> 2;
        // we updated the entry => calculate new CRC
        updateTocEntryCRC(sections[i]);
        // update the image cache with the toc entry changes:
        u_int8_t buff[IMAGE_LAYOUT_ITOC_ENTRY_SIZE];
        memset(buff, 0x0, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
        image_layout_itoc_entry_pack(&(sections[i]->toc_entry), buff);
        Fs3UpdateImgCache(buff, _fs4ImgInfo.dtocArr.tocArrayAddr + ((sections[i] - _fs4ImgInfo.dtocArr.tocArr + 1) * IMAGE_LAYOUT_ITOC_ENTRY_SIZE), IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
        // write the section data to the new offset
        if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, newOffsets[i], sections[i]->section_data.data(), sections[i]->section_data.size(), true, true, 0, 0))
        {
            if (!restoreWriteProtection(mfl, attr.banks_num, attr.protect_info_array))
            {
                rc = false;
                goto cleanup;
            }
            errmsg("Failed to move %s Section", sectionsNames[i]);
            rc = false;
            goto cleanup;
        }
        // update the image cache with the new section:
        Fs3UpdateImgCache(sections[i]->section_data.data(), newOffsets[i], sections[i]->section_data.size());
    }

    // set dtoc.header.flash_layout_version to 0x1
    struct image_layout_itoc_header dtocHeader;
    image_layout_itoc_header_unpack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    dtocHeader.flash_layout_version = 0x1;
    updateTocHeaderCRC(&dtocHeader);
    image_layout_itoc_header_pack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    // update image cache with the dtoc headers changes:
    Fs3UpdateImgCache(_fs4ImgInfo.dtocArr.tocHeader, _fs4ImgInfo.dtocArr.tocArrayAddr, IMAGE_LAYOUT_ITOC_HEADER_SIZE);

    // write the dtoc array
    _imageCache.get(data, _fs4ImgInfo.dtocArr.tocArrayAddr, FS4_DEFAULT_SECTOR_SIZE);
    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _fs4ImgInfo.dtocArr.tocArrayAddr, data, FS4_DEFAULT_SECTOR_SIZE, true, true, 0, 0))
    {
        if (!restoreWriteProtection(mfl, attr.banks_num, attr.protect_info_array))
        {
            rc = false;
            goto cleanup;
        }
        errmsg("Failed to update DToC Header");
        rc = false;
        goto cleanup;
    }

    if (flashObjWithOcr != NULL)
    {
        _ioAccess = flashObjWithOcr;
        _fwParams.ignoreCacheRep = 1;
    }
    if (!restoreWriteProtection(mfl, attr.banks_num, attr.protect_info_array))
    {
        rc = false;
        goto cleanup;
    }

cleanup:
    if (attr.type_str)
    {
        delete attr.type_str;
    }
    if (flashObjWithOcr != NULL)
    {
        _ioAccess = origFlashObj;
        _fwParams.ignoreCacheRep = 0;
        flashObjWithOcr->close();
        delete flashObjWithOcr;
    }

    _ioAccess->set_address_convertor(log2_chunk_size_bu, is_image_in_odd_chunks_bu);

    return rc;
}

bool Fs4Operations::CheckIfAlignmentIsNeeded(FwOperations* imgops)
{
    Fs4Operations& imageOps = *((Fs4Operations*)imgops);
    struct image_layout_itoc_header itocHeader, dtocHeader;
    image_layout_itoc_header_unpack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    image_layout_itoc_header_unpack(&itocHeader, imageOps._fs4ImgInfo.itocArr.tocHeader);

    if (dtocHeader.flash_layout_version < itocHeader.flash_layout_version)
    {
        return true;
    }

    return false;
}

bool Fs4Operations::FwExtractEncryptedImage(vector<u_int8_t>& img, bool maskMagicPattern, bool verbose, bool ignoreImageStart)
{
    //* Choosing the correct io to read from
    FBase* io = _ioAccess;
    if (_encrypted_image_io_access)
    {
        io = _encrypted_image_io_access; // If encrypted image was given we'll read from it
    }

    if (!getImgStart()) // Stores image start value in _fwImgInfo.imgStart
    {
        return errmsg("%s", err());
    }
    u_int32_t image_start = 0;
    if (!ignoreImageStart)
    {
        image_start = _fwImgInfo.imgStart;
    }

    //* Get image size
    u_int32_t burn_image_size;
    if (!GetEncryptedImageSizeFromImageInfo(&burn_image_size))
    {
        return errmsg("%s", err());
    }

    //* Read image from _fwImgInfo.imgStart to burn_image_size (_fwImgInfo.imgStart expected to be zero)
    DPRINTF(("Fs4Operations::FwExtractEncryptedImage - Reading 0x%x bytes from address 0x%x\n", burn_image_size, image_start));
    img.resize(burn_image_size);
    if (!(*io).read(image_start, img.data(), burn_image_size, verbose))
    {
        return errmsg("%s - read error (%s)\n", "image", (*io).err());
    }

    if (maskMagicPattern)
    {
        memset(img.data(), 0xFF, 16);
    }

    return true;
}

bool Fs4Operations::readFS4Log2ChunkSizeFromImage(u_int32_t& log2_chunk_size)
{
    if (_ioAccess->is_flash())
    {
        return errmsg("readLog2ChunkSizeFromImage operation not supported on device\n");
    }

    if (!getImgStart())
    { // Stores image start value in _fwImgInfo.imgStart
        return errmsg("Failed to get image start\n");
    }

    //* Reading begin_area.tools_area.log2_img_slot_size from image
    // TODO - read begin_area.hw_pointers.tools_ptr then read begin_area.tools_area.log2_img_slot_size
    u_int8_t buff[FS3_BOOT_START] = {0};
    _ioAccess->set_address_convertor(0, 0);
    READBUF((*_ioAccess), _fwImgInfo.imgStart, buff, FS3_BOOT_START, "Image header");
    TOCPUn(buff, FS3_BOOT_START_IN_DW);
    log2_chunk_size = EXTRACT(buff[FS3_LOG2_CHUNK_SIZE_DW_OFFSET], 16, 8) ? EXTRACT(buff[FS3_LOG2_CHUNK_SIZE_DW_OFFSET], 16, 8) : FS4_ENCRYPTED_LOG_CHUNK_SIZE;
    DPRINTF(("Fs4Operations::readFS4Log2ChunkSizeFromImage - log2_chunk_size = %d\n", log2_chunk_size));

    return true;
}

bool Fs4Operations::DoAfterBurnJobs(const u_int32_t magic_pattern[], ExtBurnParams& burnParams, Flash* flash_access, u_int32_t new_image_start, u_int32_t log2_chunk_size)
{
    u_int32_t zeroes = 0;
    u_int32_t old_fw_signatrue_addr = 0;

    bool boot_address_was_updated = bootAddrUpdate(flash_access, new_image_start, burnParams);

    if (!burnParams.burnFailsafe)
    {
        // When burning in nofs, remnant of older image with different chunk size
        // may reside on the flash -
        // Invalidate all images marking on flash except the one we've just burnt
        invalidateOldFWImages(magic_pattern, flash_access, new_image_start);
    }
    else
    {
        // invalidate previous signature
        flash_access->set_address_convertor(0, 0);
        if (new_image_start == 0x0)
        {
            old_fw_signatrue_addr = 1 << log2_chunk_size;
        }
        DPRINTF(("Fs4Operations::DoAfterBurnJobs - Invalidating old fw signature at addr 0x%x\n", old_fw_signatrue_addr));
        if (!flash_access->write(old_fw_signatrue_addr, &zeroes, sizeof(zeroes), true))
        {
            return errmsg(MLXFW_FLASH_WRITE_ERR, "Failed to invalidate old fw signature: %s", flash_access->err());
        }
    }

    if (boot_address_was_updated == false)
    {
        report_warn("Failed to update FW boot address. Power cycle the device in order to load the new FW.\n");
    }

    if (!ClearLivefishfIndication(flash_access))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::burnEncryptedImage(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    u_int8_t is_curr_image_on_second_partition;
    u_int32_t log2_chunk_size = 0;
    u_int32_t new_image_start_addr;
    u_int32_t total_img_size = 0;

    if (_ioAccess == NULL)
    {
        return errmsg("ioAccess doesn't exist\n");
    }
    if (_signatureMngr == NULL)
    {
        return errmsg("Signature manager doesn't exist\n");
    }

    //* Preparations in case we need to burn device data (DTOC)
    if (burnParams.useImgDevData)
    {
        //* Check if flash is write protected
        bool is_write_protected;
        if (!isWriteProtected(is_write_protected))
        {
            return errmsg("%s", err());
        }
        if (is_write_protected)
        {
            return errmsg("Cannot burn device data sections, Flash is write protected.");
        }

        //* Parse DTOC and its sections
        if (!((Fs4Operations*)imageOps)->ParseDevData(false))
        {
            return errmsg("%s", imageOps->err());
        }

        //* DTOC sanity check
        if (!((Fs4Operations*)imageOps)->CheckDTocArray())
        {
            return errmsg(MLXFW_IMAGE_CORRUPTED_ERR, "%s", imageOps->err());
        }

        total_img_size += FS4_DEFAULT_SECTOR_SIZE; // DTOC size
        total_img_size += ((Fs4Operations*)imageOps)->_fs4ImgInfo.dtocArr.getSectionsTotalSize();
    }

    if (burnParams.burnFailsafe)
    {
        DPRINTF(("Fs4Operations::burnEncryptedImage Looking for image start on flash\n"));
        if (!getImgStart())
        { // Stores image start value in _fwImgInfo.imgStart
            return errmsg("%s", err());
        }
    }
    else
    {
        DPRINTF(("Fs4Operations::burnEncryptedImage No fail safe burn, ignore looking for image start on flash\n"));
    }

    DPRINTF(("Fs4Operations::burnEncryptedImage _fwImgInfo.imgStart = 0x%x\n", _fwImgInfo.imgStart));
    //* Read chunk (=half-flash) size from image
    // ((Fs4Operations*)imageOps)->readFS4Log2ChunkSizeFromImage(log2_chunk_size); // TODO - use this function once it's
    // fixed
    log2_chunk_size = _fs3ImgInfo.logStep;

    //* Assign new image start addr and current image partition
    is_curr_image_on_second_partition = 0;
    new_image_start_addr = 1 << log2_chunk_size;
    if (_fwImgInfo.imgStart != 0 || (!burnParams.burnFailsafe && ((Flash*)_ioAccess)->get_ignore_cache_replacment()))
    {
        is_curr_image_on_second_partition = 1;
        new_image_start_addr = 0;
    }
    DPRINTF(("Fs4Operations::burnEncryptedImage - is_curr_image_on_second_partition = %d, new_image_start_addr = "
             "0x%x\n",
             is_curr_image_on_second_partition, new_image_start_addr));

    //* Extract encrypted image
    std::vector<u_int8_t> imgBuff;
    if (!imageOps->FwExtractEncryptedImage(imgBuff, false))
    {
        return errmsg("Failed to extract encrypted image (%s)\n", imageOps->err());
    }

    //* Get image size without signature
    total_img_size += imgBuff.size();
    DPRINTF(("Fs4Operations::burnEncryptedImage - image size to burn = 0x%x\n", (u_int32_t)imgBuff.size()));

    //* Burn
    int alreadyWrittenSz = 0;
    //* Burn image without signature
    DPRINTF(("Fs4Operations::burnEncryptedImage - Burning image without magic-pattern\n"));
    if (!writeImageEx(burnParams.progressFuncEx,
                      burnParams.progressUserData,
                      burnParams.progressFunc,
                      new_image_start_addr + FS3_FW_SIGNATURE_SIZE, // addr
                      imgBuff.data() + FS3_FW_SIGNATURE_SIZE,       // data
                      imgBuff.size() - FS3_FW_SIGNATURE_SIZE,       // size
                      true,                                         // phys addr
                      false,
                      total_img_size,
                      alreadyWrittenSz))
    {
        return errmsg("Failed to burn encrypted image - %s\n", this->err());
    }
    alreadyWrittenSz += imgBuff.size() - FS3_FW_SIGNATURE_SIZE;

    if (burnParams.useImgDevData)
    {
        //* Burning DTOC
        // Get DTOC from the cache
        u_int8_t* dtoc_data = new u_int8_t[FS4_DEFAULT_SECTOR_SIZE];
        u_int32_t dtoc_addr = imageOps->GetIoAccess()->get_size() - FS4_DEFAULT_SECTOR_SIZE;
        if (!GetDtocAddress(dtoc_addr))
        {
            return false;
        }
        DPRINTF(("Fs4Operations::burnEncryptedImage - Burning DTOC at addr 0x%0x\n", dtoc_addr));
        ((Fs4Operations*)imageOps)->_imageCache.get(dtoc_data, dtoc_addr, FS4_DEFAULT_SECTOR_SIZE);
        if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc, dtoc_addr, dtoc_data, FS4_DEFAULT_SECTOR_SIZE, true, true, total_img_size, alreadyWrittenSz))
        {
            delete[] dtoc_data;
            return false;
        }
        delete[] dtoc_data;
        alreadyWrittenSz += FS4_DEFAULT_SECTOR_SIZE;

        for (int i = 0; i < ((Fs4Operations*)imageOps)->_fs4ImgInfo.dtocArr.numOfTocs; i++)
        {
            struct fs4_toc_info* dtoc_info_p = &((Fs4Operations*)imageOps)->_fs4ImgInfo.dtocArr.tocArr[i];
            struct image_layout_itoc_entry* dtoc_entry = &dtoc_info_p->toc_entry;
            DPRINTF(("burning DTOC section addr=0x%08x size=0x%08x\n", dtoc_entry->flash_addr << 2, (u_int32_t)dtoc_info_p->section_data.size()));
            if (!writeImageEx(burnParams.progressFuncEx,
                              burnParams.progressUserData,
                              burnParams.progressFunc,
                              dtoc_entry->flash_addr << 2,
                              &(dtoc_info_p->section_data[0]),
                              dtoc_info_p->section_data.size(),
                              true,
                              true,
                              total_img_size,
                              alreadyWrittenSz))
            {
                return false;
            }
            alreadyWrittenSz += dtoc_info_p->section_data.size();
        }
    }

    //* Burn signature
    DPRINTF(("Fs4Operations::burnEncryptedImage - Burning image magic-pattern\n"));
    if (!writeImageEx(burnParams.progressFuncEx,
                      burnParams.progressUserData,
                      burnParams.progressFunc,
                      new_image_start_addr,  // addr
                      imgBuff.data(),        // data
                      FS3_FW_SIGNATURE_SIZE, // size
                      true,                  // phys addr
                      true,
                      total_img_size,
                      alreadyWrittenSz))
    {
        return errmsg("Failed to burn encrypted image signature\n");
    }
    alreadyWrittenSz += FS3_FW_SIGNATURE_SIZE;

    return DoAfterBurnJobs(_fs4_magic_pattern, burnParams, (Flash*)(this->_ioAccess), new_image_start_addr, log2_chunk_size);
}

bool Fs4Operations::BurnFs4Image(Fs4Operations& imageOps, ExtBurnParams& burnParams)
{
    u_int8_t is_curr_image_in_odd_chunks;
    u_int32_t total_img_size = 0;
    u_int32_t sector_size = FS4_DEFAULT_SECTOR_SIZE;
    Flash* f = (Flash*)(this->_ioAccess);
    u_int8_t* data8;
    bool useImageDevData;
    int alreadyWrittenSz;
    if (_ioAccess == NULL)
    {
        return errmsg("ioAccess doesn't exist\n");
    }
    if (_signatureMngr == NULL)
    {
        return errmsg("Signature manager doesn't exist\n");
    }

    if (_fwImgInfo.imgStart != 0 || (!burnParams.burnFailsafe && ((Flash*)_ioAccess)->get_ignore_cache_replacment()))
    {
        is_curr_image_in_odd_chunks = 1;
    }
    else
    {
        is_curr_image_in_odd_chunks = 0;
    }
    u_int32_t new_image_start = getNewImageStartAddress(imageOps, burnParams.burnFailsafe);

    if (new_image_start == 0x800000)
    {
        f->set_address_convertor(0x17, 1);
    }
    else
    {
        // take chunk size from image in case of a non failsafe burn (in any case they should be the same)
        f->set_address_convertor(imageOps._fwImgInfo.cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);
    }

    // check max image size
    useImageDevData = !burnParams.burnFailsafe && burnParams.useImgDevData;
    if (!CheckFs4ImgSize(imageOps, useImageDevData))
    {
        return false;
    }

    // Sanity check on the image itoc array
    if (!imageOps.CheckITocArray())
    {
        return errmsg(MLXFW_IMAGE_CORRUPTED_ERR, "%s", imageOps.err());
    }

    // Find total image size that will be written
    total_img_size += imageOps._fs4ImgInfo.itocArr.getSectionsTotalSize(); // itoc sections
    // Add boot section, itoc array (wo signature)
    total_img_size += imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;
    if (burnParams.useImgDevData)
    {
        total_img_size += sector_size;                                         // dtoc array
        total_img_size += imageOps._fs4ImgInfo.dtocArr.getSectionsTotalSize(); // dtoc sections
    }

    if (total_img_size <= sector_size)
    {
        return errmsg("Failed to burn FW. Internal error.");
    }

    // Write the image:
    alreadyWrittenSz = 0;

    // bring the boot section and itoc array from the cache
    u_int32_t beginingWithoutSignatureSize = imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;
    data8 = new u_int8_t[beginingWithoutSignatureSize];
    imageOps._imageCache.get(data8, FS3_FW_SIGNATURE_SIZE, beginingWithoutSignatureSize);

    // Write boot section and IToc array (without signature)
    if (!writeImageEx(burnParams.progressFuncEx,
                      burnParams.progressUserData,
                      burnParams.progressFunc,
                      FS3_FW_SIGNATURE_SIZE,
                      data8,
                      imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE,
                      false,
                      false,
                      total_img_size,
                      alreadyWrittenSz))
    {
        delete[] data8;
        return false;
    }
    delete[] data8;
    alreadyWrittenSz += imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;

    // write itoc entries data
    for (int i = 0; i < imageOps._fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* itoc_info_p = &imageOps._fs4ImgInfo.itocArr.tocArr[i];
        struct image_layout_itoc_entry* toc_entry = &itoc_info_p->toc_entry;
        if (!writeImageEx(burnParams.progressFuncEx,
                          burnParams.progressUserData,
                          burnParams.progressFunc,
                          toc_entry->flash_addr << 2,
                          &(itoc_info_p->section_data[0]),
                          itoc_info_p->section_data.size(),
                          false, // addresses of itocs are relative and not physical
                          false,
                          total_img_size,
                          alreadyWrittenSz))
        {
            return false;
        }
        alreadyWrittenSz += itoc_info_p->section_data.size();
    }

    if (burnParams.useImgDevData)
    {
        // Write dtoc array only if ignore_dev_data

        // Sanity check on the image dtoc array
        if (!imageOps.CheckDTocArray())
        {
            return errmsg(MLXFW_IMAGE_CORRUPTED_ERR, "%s", imageOps.err());
        }

        // bring the dtoc array from the cache
        data8 = new u_int8_t[sector_size];
        imageOps._imageCache.get(data8, imageOps._fs4ImgInfo.dtocArr.tocArrayAddr, sector_size);
        if (!writeImageEx(burnParams.progressFuncEx,
                          burnParams.progressUserData,
                          burnParams.progressFunc,
                          imageOps._fs4ImgInfo.dtocArr.tocArrayAddr,
                          data8,
                          sector_size,
                          true,
                          true,
                          total_img_size,
                          alreadyWrittenSz))
        {
            delete[] data8;
            return false;
        }
        delete[] data8;
        alreadyWrittenSz += sector_size;

        // TODO: write device area (dtoc's entries)
        for (int i = 0; i < imageOps._fs4ImgInfo.dtocArr.numOfTocs; i++)
        {
            struct fs4_toc_info* itoc_info_p = &imageOps._fs4ImgInfo.dtocArr.tocArr[i];
            struct image_layout_itoc_entry* toc_entry = &itoc_info_p->toc_entry;
            if (!writeImageEx(burnParams.progressFuncEx,
                              burnParams.progressUserData,
                              burnParams.progressFunc,
                              toc_entry->flash_addr << 2,
                              itoc_info_p->section_data.data(),
                              itoc_info_p->section_data.size(),
                              true,
                              true,
                              total_img_size,
                              alreadyWrittenSz))
            {
                return false;
            }
            alreadyWrittenSz += itoc_info_p->section_data.size();
        }
    }

    if (!f->is_flash())
    {
        return true;
    }
    bool IsUpdateSignatures = true;
    chip_type chip = this->_fwImgInfo.ext_info.chip_type;
    if (burnParams.use_chip_type == true)
    {
        chip = burnParams.chip_type; // patch for BF
    }
    switch (chip)
    {
        case CT_CONNECTX6:
            getExtendedHWPtrs((VerifyCallBack)NULL, imageOps._ioAccess, true);
            break;
        case CT_CONNECTX6DX:
            getExtendedHWAravaPtrs((VerifyCallBack)NULL, imageOps._ioAccess, true);
            break;
        case CT_BLUEFIELD:
            if (burnParams.use_chip_type == true)
            {
                if (!_signatureMngr->AddSignature(_ioAccess->getMfileObj(), &imageOps, f, 0))
                {
                    return false;
                }
                IsUpdateSignatures = false; // already updated right now
            }
            break;
        default:
            IsUpdateSignatures = false;
            break;
    }

    if (IsUpdateSignatures)
    {
        u_int32_t imageOffset = _digest_mdk_ptr;
        if (imageOffset == 0)
        {
            // use recovery ptr!
            imageOffset = _digest_recovery_key_ptr;
        }
        if (imageOffset != 0)
        {
            if (!_signatureMngr->AddSignature(_ioAccess->getMfileObj(), &imageOps, f, imageOffset))
            {
                return false;
            }
        }
    }
    // Write new signature
    data8 = new u_int8_t[FS3_FW_SIGNATURE_SIZE];
    imageOps._imageCache.get(data8, 0, FS3_FW_SIGNATURE_SIZE);
    if (!writeImageEx(burnParams.progressFuncEx, burnParams.progressUserData, burnParams.progressFunc, new_image_start, data8, FS3_FW_SIGNATURE_SIZE, true, true, total_img_size, alreadyWrittenSz))
    {
        delete[] data8;
        return false;
    }
    delete[] data8;

    return Fs3Operations::DoAfterBurnJobs(_fs4_magic_pattern, imageOps, burnParams, f, new_image_start, is_curr_image_in_odd_chunks);
}

bool Fs4Operations::FsBurnAux(FwOperations* imgops, ExtBurnParams& burnParams)
{
    bool devIntQueryRes;
    bool rc;
    Fs4Operations& imageOps = *((Fs4Operations*)imgops);

    if (imageOps.FwType() != FIT_FS4 && imageOps.FwType() != FIT_FS5)
    {
        return errmsg(MLXFW_IMAGE_FORMAT_ERR, "FW image type is not compatible with device (FS4)");
    }

    devIntQueryRes = FsIntQueryAux();

    if (!devIntQueryRes && burnParams.burnFailsafe)
    {
        return false;
    }
    // For image we execute full verify to bring all the information needed for ROM Patch
    bool ignoreDToc = imageOps.GetIsReducedImage();
    if (!imageOps.FsIntQueryAux(true, false, ignoreDToc))
    {
        return false;
    }

    // Check Matching device ID
    if (!burnParams.noDevidCheck && _ioAccess->is_flash())
    {
        if (imageOps._fwImgInfo.supportedHwIdNum)
        {
            if (!CheckMatchingHwDevId(_ioAccess->get_dev_id(), _ioAccess->get_rev_id(), imageOps._fwImgInfo.supportedHwId, imageOps._fwImgInfo.supportedHwIdNum))
            {
                return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR, "Device/Image mismatch: %s\n", this->err());
            }
            if (burnParams.burnFailsafe == false && !CheckMatchingBinning(_ioAccess->get_dev_id(), _ioAccess->get_bin_id(), imageOps._fwImgInfo.ext_info.dev_type))
            {
                // we check Chip Bin information only on failsafe burn
                // during Firmware update flow - PSID will ensure a correct match.
                return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR, "Device/Image mismatch: %s\n", this->err());
            }
        }
        else
        {
            // No supported HW IDs (problem with the image ?)
            return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR, "No supported devices were found in the FW image.");
        }
    }

    if (!burnParams.burnFailsafe)
    {
        // Some checks in case we burn in a non-failsafe manner and attempt to
        // integrate existing device Data sections from device.
        if (!burnParams.useImgDevData)
        {
            // We will take device data section from device: perform some checks
            if (_fs4ImgInfo.dtocArr.tocArrayAddr == 0)
            {
                return errmsg("Cannot extract device data sections: "
                              "Invalid DTOC section. "
                              "Please ignore extracting device data sections.");
            }
            if (_badDevDataSections)
            {
                return errmsg("Cannot integrate device data sections: "
                              "Device data sections are corrupted. "
                              "Please ignore extracting device data sections.");
            }
        }
        else
        {
            // We will take device data sections from image: make sure device is not write protected
            bool is_write_protected;
            if (!isWriteProtected(is_write_protected))
            {
                return errmsg("%s", err());
            }
            if (is_write_protected)
            {
                return errmsg("Cannot burn device data sections, Flash is write protected.");
            }
        }
    }

    if (devIntQueryRes && !CheckPSID(imageOps, burnParams.allowPsidChange))
    {
        return false;
    }

    if (burnParams.burnFailsafe)
    {
        if (!CheckAndDealWithChunkSizes(_fwImgInfo.cntxLog2ChunkSize, imageOps._fwImgInfo.cntxLog2ChunkSize))
        {
            return false;
        }

        // Check if the burnt FW version is OK
        if (!CheckFwVersion(imageOps, burnParams.ignoreVersionCheck))
        {
            return false;
        }

        // Check TimeStamp
        if (!TestAndSetTimeStamp(imgops))
        {
            return false;
        }

        // ROM patchs
        if ((burnParams.burnRomOptions == ExtBurnParams::BRO_FROM_DEV_IF_EXIST) && _fwImgInfo.ext_info.roms_info.exp_rom_found)
        {
            std::vector<u_int8_t> romSect = _romSect;
            TOCPUn((u_int32_t*)romSect.data(), romSect.size() >> 2);
            if (!imageOps.Fs4AddSectionAux(FS3_ROM_CODE, INITOCENTRY, 0, (u_int32_t*)romSect.data(), romSect.size()))
            {
                return errmsg(MLXFW_ROM_UPDATE_IN_IMAGE_ERR, "failed to update ROM in image. %s", imageOps.err());
            }
        }

        // Image vsd patch
        if (!burnParams.useImagePs && (burnParams.vsdSpecified || burnParams.useDevImgInfo))
        {
            // get image info section :
            struct fs4_toc_info* imageInfoToc = (struct fs4_toc_info*)NULL;
            if (!imageOps.Fs4GetItocInfo(imageOps._fs4ImgInfo.itocArr.tocArr, imageOps._fs4ImgInfo.itocArr.numOfTocs, FS3_IMAGE_INFO, imageInfoToc))
            {
                return errmsg(MLXFW_GET_SECT_ERR, "failed to get Image Info section.");
            }

            std::vector<u_int8_t> imageInfoSect = imageInfoToc->section_data;

            if (burnParams.vsdSpecified)
            {
                struct cibfw_image_info image_info;
                cibfw_image_info_unpack(&image_info, &imageInfoSect[0]);
                strncpy(image_info.vsd, burnParams.userVsd, VSD_LEN);
                cibfw_image_info_pack(&image_info, &imageInfoSect[0]);
            }

            if (burnParams.useDevImgInfo)
            {
                // update PSID, name and description in image info
                struct tools_open_image_info tools_image_info;
                tools_open_image_info_unpack(&tools_image_info, &imageInfoSect[0]);
                strncpy(tools_image_info.psid, _fwImgInfo.ext_info.psid, PSID_LEN + 1);
                strncpy(tools_image_info.name, _fs3ImgInfo.ext_info.name, NAME_LEN);
                strncpy(tools_image_info.description, _fs3ImgInfo.ext_info.description, DESCRIPTION_LEN);
                tools_open_image_info_pack(&tools_image_info, &imageInfoSect[0]);
            }

            // update image info toc and section
            if (!Fs4UpdateItocInfo(imageInfoToc, imageInfoToc->toc_entry.size, imageInfoSect))
            {
                return false;
            }
            // update the toc in the cache
            imageOps.Fs3UpdateImgCache(imageInfoToc->data, imageInfoToc->entry_addr, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
            // update the section in the cache
            imageOps.Fs3UpdateImgCache(imageInfoToc->section_data.data(), imageInfoToc->toc_entry.flash_addr << 2, imageInfoToc->toc_entry.size * 4);
        }
    }

    rc = BurnFs4Image(imageOps, burnParams);

    return rc;
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info* tocArr, int num_of_itocs, fs3_section_t sect_type, struct fs4_toc_info*& curr_toc)
{
    int tocIndex;
    return Fs4GetItocInfo(tocArr, num_of_itocs, sect_type, curr_toc, tocIndex);
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info* tocArr, int num_of_itocs, fs3_section_t sect_type, struct fs4_toc_info*& curr_toc, int& toc_index)
{
    for (int i = 0; i < num_of_itocs; i++)
    {
        struct fs4_toc_info* itoc_info = &tocArr[i];
        if (itoc_info->toc_entry.type == sect_type)
        {
            curr_toc = itoc_info;
            toc_index = i;
            return true;
        }
    }
    return errmsg("TOC entry type: %s (%d) not found", GetSectionNameByType(sect_type), sect_type);
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info* tocArr, int num_of_itocs, fs3_section_t sect_type, vector<struct fs4_toc_info*>& curr_toc)
{
    for (int i = 0; i < num_of_itocs; i++)
    {
        struct fs4_toc_info* itoc_info = &tocArr[i];
        if (itoc_info->toc_entry.type == sect_type)
        {
            curr_toc.push_back(itoc_info);
        }
    }
    return true;
}

bool Fs4Operations::Fs4UpdateMfgUidsSection(struct fs4_toc_info* curr_toc, std::vector<u_int8_t> section_data, fs3_uid_t base_uid, std::vector<u_int8_t>& newSectionData)
{
    struct cibfw_mfg_info cib_mfg_info;
    struct cx4fw_mfg_info cx4_mfg_info;
    (void)curr_toc;
    if (IsExtendedGuidNumSupported())
    {
        image_layout_mfg_info mfg_info;
        image_layout_mfg_info_unpack(&mfg_info, (u_int8_t*)&section_data[0]);
        if (!ChangeUidsFromBase(base_uid, mfg_info.guids))
        {
            return false;
        }
        newSectionData = section_data;
        image_layout_mfg_info_pack(&mfg_info, (u_int8_t*)&newSectionData[0]);
    }
    else
    {
        if (base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM && base_uid.num_of_guids_pp[0] > 254)
        {
            return errmsg("Invalid argument values, values should be taken from the range [0..254]\n");
        }

        cibfw_mfg_info_unpack(&cib_mfg_info, (u_int8_t*)&section_data[0]);

        if (cib_mfg_info.major_version == 0)
        {
            if (!Fs3ChangeUidsFromBase(base_uid, cib_mfg_info.guids))
            {
                return false;
            }
        }
        else if (cib_mfg_info.major_version == 1)
        {
            cx4fw_mfg_info_unpack(&cx4_mfg_info, (u_int8_t*)&section_data[0]);
            if (!Fs3ChangeUidsFromBase(base_uid, cx4_mfg_info.guids))
            {
                return false;
            }
        }
        else
        {
            return errmsg("Unknown MFG_INFO format version (%d.%d).", cib_mfg_info.major_version, cib_mfg_info.minor_version);
        }
        newSectionData = section_data;

        if (cib_mfg_info.major_version == 1)
        {
            cx4fw_mfg_info_pack(&cx4_mfg_info, (u_int8_t*)&newSectionData[0]);
        }
        else
        {
            cibfw_mfg_info_pack(&cib_mfg_info, (u_int8_t*)&newSectionData[0]);
        }
    }
    return true;
}

bool Fs4Operations::Fs4ChangeUidsFromBase(fs3_uid_t base_uid, struct image_layout_guids& guids)
{
    /*
     * on ConnectX4 we derrive guids from base_guid and macs from base_mac
     */
    u_int64_t base_guid_64;
    u_int64_t base_mac_64;
    if (!base_uid.use_pp_attr)
    {
        return errmsg("Expected per port attributes to be specified");
    }

    base_guid_64 = base_uid.base_guid_specified ? GUID_TO_64(base_uid.base_guid) : guids.guids.uid;
    base_mac_64 = base_uid.base_mac_specified ? GUID_TO_64(base_uid.base_mac) : guids.macs.uid;
    if (base_uid.set_mac_from_guid && base_uid.base_guid_specified)
    {
        // in case we derrive mac from guid
        base_mac_64 = (((u_int64_t)base_uid.base_guid.l & 0xffffff) | (((u_int64_t)base_uid.base_guid.h & 0xffffff00) << 16));
    }

    if (!IsExtendedGuidNumSupported() && base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM && base_uid.num_of_guids_pp[0] > 254)
    {
        return errmsg("Invalid argument values, values should be taken from the range [0..254]\n");
    }

    guids.guids.uid = base_guid_64;
    guids.guids.num_allocated = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? base_uid.num_of_guids_pp[0] : guids.guids.num_allocated;
    guids.guids.num_allocated_msb = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? ((base_uid.num_of_guids_pp[0] >> 8) & 0xff) : guids.guids.num_allocated_msb;
    guids.guids.step = base_uid.step_size_pp[0] != DEFAULT_STEP ? base_uid.step_size_pp[0] : guids.guids.step;

    guids.macs.uid = base_mac_64;
    guids.macs.num_allocated = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? base_uid.num_of_guids_pp[0] : guids.macs.num_allocated;
    guids.macs.num_allocated_msb = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? ((base_uid.num_of_guids_pp[0] >> 8) & 0xff) : guids.macs.num_allocated_msb;
    guids.macs.step = base_uid.step_size_pp[0] != DEFAULT_STEP ? base_uid.step_size_pp[0] : guids.macs.step;
    return true;
}

bool Fs4Operations::Fs4UpdateUidsSection(std::vector<u_int8_t> section_data, fs3_uid_t base_uid, std::vector<u_int8_t>& newSectionData)
{
    struct image_layout_device_info dev_info;

    image_layout_device_info_unpack(&dev_info, (u_int8_t*)&section_data[0]);

    if (!Fs4ChangeUidsFromBase(base_uid, dev_info.guids))
    {
        return false;
    }

    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;

    newSectionData = section_data;

    image_layout_device_info_pack(&dev_info, (u_int8_t*)&newSectionData[0]);
    return true;
}

bool Fs4Operations::Fs4UpdateVsdSection(std::vector<u_int8_t> section_data, char* user_vsd, std::vector<u_int8_t>& newSectionData)
{
    struct image_layout_device_info dev_info;

    image_layout_device_info_unpack(&dev_info, (u_int8_t*)&section_data[0]);
    memset(dev_info.vsd, 0, sizeof(dev_info.vsd));
    strncpy(dev_info.vsd, user_vsd, TOOLS_ARR_SZ(dev_info.vsd) - 1);
    newSectionData = section_data;
    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;
    image_layout_device_info_pack(&dev_info, (u_int8_t*)&newSectionData[0]);
    return true;
}

bool Fs4Operations::Init()
{
    if (!InitHwPtrs())
    {
        return false;
    }
    fw_info_t fwInfo;
    if (!FwQuery(&fwInfo, false, false, false))
    {
        return false;
    }
    return true;
}

bool Fs4Operations::UpdateDigitalCertRWSection(char* certChainFile, u_int32_t certChainIndex, std::vector<u_int8_t>& newSectionData)
{
    if (!Init())
    {
        return false;
    }
    struct fs4_toc_info* tocArr = _fs4ImgInfo.dtocArr.tocArr;
    u_int32_t numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;

    // Get DIGITAL_CERT_RW entry
    struct fs4_toc_info* digitalCertRWSectionToc = (fs4_toc_info*)NULL;
    if (!Fs4GetItocInfo(tocArr, numOfTocs, FS4_DIGITAL_CERT_RW, digitalCertRWSectionToc))
    {
        return false;
    }

    // Get CERT_CHAIN_0 entry
    struct fs4_toc_info* certChain0SectionToc = (fs4_toc_info*)NULL;
    if (!Fs4GetItocInfo(tocArr, numOfTocs, FS4_CERT_CHAIN_0, certChain0SectionToc))
    {
        return false;
    }
    u_int32_t certChain0SectionSize = certChain0SectionToc->toc_entry.size << 2;

    int certChainBuffSize = 0;
    u_int8_t* certChainBuffData = (u_int8_t*)NULL;
    if (!ReadBinFile(certChainFile, certChainBuffData, certChainBuffSize))
    {
        return false;
    }
    DPRINTF(("Fs4Operations::UpdateDigitalCertRWSection new cert file size = 0x%x\n", certChainBuffSize));

    //* Assert given certificate chain doesn't exceed its allocated size (compared to CERT_CHAIN_0 with same size)
    if ((u_int32_t)certChainBuffSize > certChain0SectionSize)
    {
        delete[] certChainBuffData;
        return errmsg("Certificate chain data exceeds its allocated size of 0x%x bytes", certChain0SectionSize);
    }

    std::vector<u_int8_t> certChainBuff(certChainBuffData, certChainBuffData + certChainBuffSize);
    certChainBuff.resize(certChain0SectionSize); // Padding the cert chain if needed to match cert chain size
    delete[] certChainBuffData;

    newSectionData = digitalCertRWSectionToc->section_data;
    u_int32_t newCertChainOffsetInSection = certChain0SectionSize * (certChainIndex - 1); // index 0 belongs to CERT_CHAIN_0
    DPRINTF(("Fs4Operations::UpdateDigitalCertRWSection copy new cert to DIGITAL_CERT_RW at offset = 0x%x, size = 0x%x\n", newCertChainOffsetInSection, (u_int32_t)certChainBuff.size()));
    if ((newCertChainOffsetInSection + certChainBuff.size()) > (digitalCertRWSectionToc->toc_entry.size << 2))
    {
        return errmsg("Certificate chain data exceeds its allocation");
    }
    std::copy(certChainBuff.begin(), certChainBuff.end(), newSectionData.begin() + newCertChainOffsetInSection);

    return true;
}

bool Fs4Operations::UpdateCertChainSection(struct fs4_toc_info* curr_toc, char* certChainFile, std::vector<u_int8_t>& newSectionData)
{
    int cert_chain_buff_size = 0;
    u_int8_t* cert_chain_buff = (u_int8_t*)NULL;

    if (!ReadBinFile(certChainFile, cert_chain_buff, cert_chain_buff_size))
    {
        return false;
    }

    //* Assert given certificate chain doesn't exceed its allocated size
    u_int32_t cert_chain_0_section_size = curr_toc->toc_entry.size << 2;
    if ((u_int32_t)cert_chain_buff_size > cert_chain_0_section_size)
    {
        delete[] cert_chain_buff;
        return errmsg("Attestation certificate chain data exceeds its allocated size of 0x%x bytes", cert_chain_0_section_size);
    }

    newSectionData.resize(cert_chain_0_section_size, 0); // Init section data with 0x0
    memcpy(newSectionData.data(), cert_chain_buff, cert_chain_buff_size);
    delete[] cert_chain_buff;
    return true;
}

bool Fs4Operations::Fs4UpdateVpdSection(struct fs4_toc_info* curr_toc, char* vpd, std::vector<u_int8_t>& newSectionData)
{
    int vpd_size = 0;
    u_int8_t* vpd_data = (u_int8_t*)NULL;

    if (!ReadBinFile(vpd, vpd_data, vpd_size))
    {
        return false;
    }
    if (vpd_size % 4)
    {
        delete[] vpd_data;
        return errmsg("Size of VPD file: %d is not 4-byte aligned!", vpd_size);
    }

    // corresponds to VPD max size in mlx
    if (vpd_size > 0x1000)
    {
        delete[] vpd_data;
        return errmsg("VPD data size exceeds max VPD size: 0x%x bytes", 0x1000);
    }

    GetSectData(newSectionData, (u_int32_t*)vpd_data, vpd_size);
    curr_toc->toc_entry.size = vpd_size / 4;
    delete[] vpd_data;
    return true;
}

bool Fs4Operations::Fs4ReburnSection(u_int32_t newSectionAddr, u_int32_t newSectionSize, std::vector<u_int8_t> newSectionData, const char* msg, PrintCallBack callBackFunc)
{
    char message[127];

    sprintf(message, "Updating %-4s section - ", msg);
    DPRINTF(("%s\n", message));

    PRINT_PROGRESS(callBackFunc, message);

    // If encrypted image is valid we want to write to it
    if (_encrypted_image_io_access)
    {
        DPRINTF(("Fs4Operations::Fs4ReburnSection updating encrypted image at addr 0x%x\n", newSectionAddr));
        if (!_encrypted_image_io_access->write(newSectionAddr, (u_int8_t*)&newSectionData[0], newSectionSize))
        {
            return errmsg("%s", _encrypted_image_io_access->err());
        }
    }
    else
    {
        if (!writeImage((ProgressCallBack)NULL, newSectionAddr, (u_int8_t*)&newSectionData[0], newSectionSize, true, true))
        {
            PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
            return false;
        }
    }

    PRINT_PROGRESS(callBackFunc, (char*)"OK\n");

    return true;
}

bool Fs4Operations::CalcHashOnSection(u_int32_t addr, u_int32_t size, vector<u_int8_t>& hash)
{
#if !defined(NO_OPEN_SSL) && !defined(NO_DYNAMIC_ENGINE) // mlxSignSHA is only available with OPEN_SSL
    vector<u_int8_t> data;
    data.resize(size);
    READBUF((*_ioAccess), addr, (u_int32_t*)&data[0], size, "Reading section data for hash calculation");

    //* Calculate SHA
    MlxSignSHA512 mlxSignSHA;
    mlxSignSHA << data;
    mlxSignSHA.getDigest(hash);
    return true;
#else
    (void)addr;
    (void)size;
    (void)hash;
    return false;
#endif
}

bool Fs4Operations::IsSectionShouldBeHashed(fs3_section_t section_type)
{
    bool res;
    switch (section_type)
    {
        case FS3_PUBLIC_KEYS_2048:
        case FS3_PUBLIC_KEYS_4096:
        case FS3_IMAGE_SIGNATURE_256:
        case FS3_IMAGE_SIGNATURE_512:
        case FS4_RSA_4096_SIGNATURES:
            res = false;
            break;
        default:
            res = true;
    }

    return res;
}

bool Fs4Operations::UpdateSectionHashInHashesTable(u_int32_t addr, u_int32_t size, fs3_section_t type)
{
    if (getSecureBootSignVersion() == VERSION_2 && IsSectionShouldBeHashed(type))
    {
        DPRINTF(("Fs4Operations::UpdateSectionHashInHashesTable type=0x%x\n", type));

        vector<u_int8_t> hash;
        if (!CalcHashOnSection(addr, size, hash))
        {
            return errmsg("Failed to calculate section hash");
        }

        if (!UpdateHashInHashesTable(type, hash))
        {
            return false;
        }
    }

    return true;
}

bool Fs4Operations::UpdateHashInHashesTable(fs3_section_t section_type, vector<u_int8_t> hash)
{
    //* Init HTOC
    vector<u_int8_t> img = {0};
    FwInit();
    _imageCache.clear();
    if (!FwExtract4MBImage(img, true))
    {
        return false;
    }
    const u_int32_t htoc_address = _hashes_table_ptr + IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE;
    try
    {
        u_int32_t htoc_size = 0;
        if (!GetHashesTableSize(htoc_size))
        {
            return false;
        }

        HTOC htoc = HTOC(img, htoc_address, htoc_size);

        // TODO - move below logic to HTOC
        //* Get hash addr in hashes_table
        struct image_layout_htoc_entry htoc_entry;
        if (!htoc.GetEntryBySectionType(section_type, htoc_entry))
        {
            DPRINTF(("Fs4Operations::UpdateHashInHashesTable Can't find section type 0x%x in htoc\n", section_type));
            if (!htoc.AddNewEntry(_ioAccess, section_type, htoc_entry))
            {
                return errmsg("Failed to add new entry of section type 0x%x to htoc", section_type);
            }
        }
        u_int32_t hash_addr = htoc_address + htoc_entry.hash_offset;
        u_int32_t hash_size = htoc.header.hash_size;

        //* Insert hash (SHA512) to hashes_table
        if (!_ioAccess->write(hash_addr, hash.data(), hash_size))
        {
            return errmsg("Failed to insert hash to hashes_table");
        }

        //* Calculate CRC on modified hashes_table
        u_int32_t hashes_table_size =
          IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE + IMAGE_LAYOUT_HTOC_HEADER_SIZE + htoc.GetHtocMaxNumOfEntries() * (IMAGE_LAYOUT_HTOC_ENTRY_SIZE + hash_size) + HASHES_TABLE_TAIL_SIZE;
        u_int8_t* hashes_table_data;
        READALLOCBUF((*_ioAccess), _hashes_table_ptr, hashes_table_data, hashes_table_size, "HASHES TABLE");
        u_int32_t hashes_table_crc = CalcImageCRC((u_int32_t*)hashes_table_data, (hashes_table_size / 4) - 1);
        free(hashes_table_data);
        CPUTO1(hashes_table_crc);

        //* Insert calculated CRC to last DWORD in hashes_table
        u_int32_t hashes_table_crc_addr = _hashes_table_ptr + hashes_table_size - 4;
        if (!_ioAccess->write(hashes_table_crc_addr, &hashes_table_crc, 4))
        {
            return errmsg("Failed to write hashes_table crc");
        }
    }
    catch (const std::exception& e)
    {
        return errmsg("%s", e.what());
    }

    return true;
}

bool Fs4Operations::Fs4ReburnTocSection(bool isDtoc, PrintCallBack callBackFunc)
{
    // Update new TOC section
    if (isDtoc)
    {
        if (!reburnDTocSection(callBackFunc))
        {
            return false;
        }
    }
    else
    {
        if (!reburnITocSection(callBackFunc, _ioAccess->is_flash()))
        {
            return false;
        }
    }
    return true;
}

bool Fs4Operations::reburnDTocSection(PrintCallBack callBackFunc)
{
    // Itoc section is failsafe (two sectors after boot section are reserved for itoc entries)
    u_int32_t tocAddr = _fs4ImgInfo.dtocArr.tocArrayAddr;
    // Update new ITOC
    u_int32_t tocSize = (_fs4ImgInfo.dtocArr.numOfTocs + 1) * IMAGE_LAYOUT_ITOC_ENTRY_SIZE + IMAGE_LAYOUT_ITOC_HEADER_SIZE;
    u_int8_t* p = new u_int8_t[tocSize];
    memcpy(p, _fs4ImgInfo.dtocArr.tocHeader, CIBFW_ITOC_HEADER_SIZE);
    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* curr_itoc = &_fs4ImgInfo.dtocArr.tocArr[i];
        memcpy(p + IMAGE_LAYOUT_ITOC_HEADER_SIZE + i * IMAGE_LAYOUT_ITOC_ENTRY_SIZE, curr_itoc->data, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    }
    memset(&p[tocSize - IMAGE_LAYOUT_ITOC_ENTRY_SIZE], FS3_END, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);

    PRINT_PROGRESS(callBackFunc, (char*)"Updating DTOC section - ");
    bool rc = writeImage((ProgressCallBack)NULL, tocAddr, p, tocSize, true, true);
    delete[] p;
    if (!rc)
    {
        PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
        return false;
    }
    PRINT_PROGRESS(callBackFunc, (char*)"OK\n");

    return true;
}

bool Fs4Operations::reburnITocSection(PrintCallBack callBackFunc, bool isFailSafe)
{
    // Itoc section is failsafe (two sectors after boot section are reserved for itoc entries)
    u_int32_t sector_size = FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t oldITocAddr = _fs4ImgInfo.itocArr.tocArrayAddr;
    u_int32_t newITocAddr = oldITocAddr;
    if (isFailSafe)
    {
        newITocAddr = (_fs4ImgInfo.firstItocArrayIsEmpty) ? (_fs4ImgInfo.itocArr.tocArrayAddr - sector_size) : (_fs4ImgInfo.itocArr.tocArrayAddr + sector_size);
    }
    // Update new ITOC
    u_int32_t tocSize = (_fs4ImgInfo.itocArr.numOfTocs + 1) * IMAGE_LAYOUT_ITOC_ENTRY_SIZE + IMAGE_LAYOUT_ITOC_HEADER_SIZE;
    u_int8_t* p = new u_int8_t[tocSize];
    memcpy(p, _fs4ImgInfo.itocArr.tocHeader, CIBFW_ITOC_HEADER_SIZE);
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* curr_itoc = &_fs4ImgInfo.itocArr.tocArr[i];
        memcpy(p + IMAGE_LAYOUT_ITOC_HEADER_SIZE + i * IMAGE_LAYOUT_ITOC_ENTRY_SIZE, curr_itoc->data, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    }
    memset(&p[tocSize - IMAGE_LAYOUT_ITOC_ENTRY_SIZE], FS3_END, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);

    PRINT_PROGRESS(callBackFunc, (char*)"Updating ITOC section - ");
    bool rc = writeImage((ProgressCallBack)NULL, newITocAddr, p, tocSize, true, true);
    delete[] p;
    if (!rc)
    {
        PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
        return false;
    }
    PRINT_PROGRESS(callBackFunc, (char*)"OK\n");

    u_int32_t zeros = 0;
    if (isFailSafe)
    {
        PRINT_PROGRESS(callBackFunc, (char*)"Restoring signature   - ");
        if (!writeImage((ProgressCallBack)NULL, oldITocAddr, (u_int8_t*)&zeros, 4, false, true))
        {
            PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
            return false;
        }
        PRINT_PROGRESS(callBackFunc, (char*)"OK\n");
    }

    if (getSecureBootSignVersion() == VERSION_2)
    {
        vector<u_int8_t> hash;
        u_int32_t itocSize = _fs4ImgInfo.itocArr.numOfTocs * TOC_ENTRY_SIZE + TOC_HEADER_SIZE;
        if (!CalcHashOnSection(newITocAddr, itocSize, hash))
        {
            return errmsg("Failed to calculate ITOC hash");
        }

        if (!UpdateHashInHashesTable(FS3_ITOC, hash))
        {
            return false;
        }
    }

    return true;
}

bool Fs4Operations::Fs4UpdateItocInfo(struct fs4_toc_info* curr_toc, u_int32_t NewSectSize, std::vector<u_int8_t>& newSectionData)
{
    u_int8_t tocEntryBuff[IMAGE_LAYOUT_ITOC_ENTRY_SIZE];

    curr_toc->toc_entry.size = NewSectSize;
    curr_toc->section_data = newSectionData;

    if (curr_toc->toc_entry.crc == INITOCENTRY)
    {
        curr_toc->toc_entry.section_crc = CalcImageCRC((u_int32_t*)&newSectionData[0], curr_toc->toc_entry.size);
    }
    else if (curr_toc->toc_entry.crc == INSECTION)
    {
        u_int32_t newSectionCRC = CalcImageCRC((u_int32_t*)&newSectionData[0], curr_toc->toc_entry.size - 1);
        ((u_int32_t*)curr_toc->section_data.data())[curr_toc->toc_entry.size - 1] = newSectionCRC;
        ((u_int32_t*)newSectionData.data())[curr_toc->toc_entry.size - 1] = TOCPU1(newSectionCRC);
    }

    memset(tocEntryBuff, 0, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    image_layout_itoc_entry_pack(&curr_toc->toc_entry, tocEntryBuff);

    u_int32_t newEntryCRC = CalcImageCRC((u_int32_t*)tocEntryBuff, (TOC_ENTRY_SIZE / 4) - 1);
    curr_toc->toc_entry.itoc_entry_crc = newEntryCRC;

    memset(curr_toc->data, 0, IMAGE_LAYOUT_ITOC_ENTRY_SIZE);
    image_layout_itoc_entry_pack(&curr_toc->toc_entry, curr_toc->data);

    return true;
}

bool Fs4Operations::isDTocSection(fs3_section_t sect_type, bool& isDtoc)
{
    switch ((int)sect_type)
    {
        case FS3_MFG_INFO:
        case FS3_DEV_INFO:
        case FS3_VPD_R0:
        case FS4_DIGITAL_CERT_RW:
        case FS4_CERT_CHAIN_0:
            isDtoc = true;
            break;

        case FS3_PUBLIC_KEYS_4096:
        case FS3_PUBLIC_KEYS_2048:
        case FS3_IMAGE_SIGNATURE_256:
        case FS3_IMAGE_SIGNATURE_512:
        case FS3_FORBIDDEN_VERSIONS:
        case FS4_RSA_PUBLIC_KEY:
        case FS4_RSA_4096_SIGNATURES:
            isDtoc = false;
            break;

        default:
            return errmsg("Section type %s is not supported\n", GetSectionNameByType(sect_type));
            break;
    }
    return true;
}

bool Fs4Operations::IsSectionExists(fs3_section_t sectType)
{
    bool isDtoc;
    struct fs4_toc_info* tocArr;
    u_int32_t numOfTocs;
    struct fs4_toc_info* curr_toc = (fs4_toc_info*)NULL;
    int tocIndex = 0;

    if (!isDTocSection(sectType, isDtoc))
    {
        return false;
    }

    if (isDtoc)
    {
        tocArr = _fs4ImgInfo.dtocArr.tocArr;
        numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;
    }
    else
    {
        tocArr = _fs4ImgInfo.itocArr.tocArr;
        numOfTocs = _fs4ImgInfo.itocArr.numOfTocs;
    }
    if (!Fs4GetItocInfo(tocArr, numOfTocs, sectType, curr_toc, tocIndex))
    {
        return false;
    }
    return true;
}

bool Fs4Operations::VerifyImageAfterModifications()
{
    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }

    if (image_encrypted)
    {
        fw_info_t fwInfo;
        if (!encryptedFwQuery(&fwInfo, false))
        {
            return errmsg("%s", err());
        }
    }
    else if (!FsIntQueryAux(false, false))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::FwSetCertChain(char* certFileStr, u_int32_t certIndex, PrintCallBack callBackFunc)
{
    if (!certFileStr)
    {
        return errmsg("Please specify a valid certificate chain file.");
    }
    FAIL_NO_OCR("set attestation certificate chain");

    if (certIndex == 0)
    {
        if (!UpdateSection(certFileStr, FS4_CERT_CHAIN_0, false, CMD_UNKNOWN, callBackFunc))
        {
            return false;
        }
    }
    else
    {
        std::vector<u_int8_t> newSectionData;
        if (!UpdateDigitalCertRWSection(certFileStr, certIndex, newSectionData))
        {
            return false;
        }
        if (!UpdateSection(FS4_DIGITAL_CERT_RW, newSectionData, "DIGITAL_CERT_RW", callBackFunc))
        {
            return false;
        }
    }

    // on image verify that image is OK after modification (we skip this on device for performance reasons)
    if (!_ioAccess->is_flash() && !VerifyImageAfterModifications())
    {
        return false;
    }
    return true;
}

bool Fs4Operations::UpdateSection(void* new_info, fs3_section_t sect_type, bool, CommandType cmd_type, PrintCallBack callBackFunc)
{
    struct fs4_toc_info* curr_toc = (fs4_toc_info*)NULL;
    struct fs4_toc_info* old_toc = (fs4_toc_info*)NULL;
    std::vector<u_int8_t> newSection;
    const char* type_msg;
    struct fs4_toc_info* tocArr;
    u_int32_t numOfTocs;
    u_int32_t zeroes = 0;
    bool isDtoc;

    if (!isDTocSection(sect_type, isDtoc))
    {
        return false;
    }

    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }

    if (image_encrypted)
    {
        if (!isDtoc)
        {
            return errmsg("Can't update ITOC section in case of encrypted image");
        }
        fw_info_t fwInfo;
        if (!encryptedFwQuery(&fwInfo))
        {
            return errmsg("%s", err());
        }
    }
    else
    {
        // init sector to read
        _readSectList.push_back(sect_type);
        if (!FsIntQueryAux())
        {
            _readSectList.pop_back();
            return false;
        }
        _readSectList.pop_back();
    }

    bool is_sect_failsafe = (sect_type == FS3_DEV_INFO);

    if (isDtoc)
    {
        tocArr = _fs4ImgInfo.dtocArr.tocArr;
        numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;
    }
    else
    {
        tocArr = _fs4ImgInfo.itocArr.tocArr;
        numOfTocs = _fs4ImgInfo.itocArr.numOfTocs;
    }

    if (is_sect_failsafe)
    {
        vector<struct fs4_toc_info*> tocs;
        // find first valid section
        if (!Fs4GetItocInfo(tocArr, numOfTocs, sect_type, tocs))
        {
            return false;
        }
        if (tocs.size() < 2)
        {
            PRINT_PROGRESS(callBackFunc, (char*)"FAILED\n");
            return false;
        }
        for (size_t i = 0; i < tocs.size(); i++)
        {
            if (CheckDevInfoSignature((u_int32_t*)(tocs[i]->section_data.data())))
            {
                old_toc = tocs[i];
                // find the second section (valid or not valid, does not matter)
                if (i == 0)
                {
                    curr_toc = tocs[1];
                }
                else
                {
                    curr_toc = tocs[0];
                }
                break;
            }
        }
        if (!old_toc)
        {
            return errmsg("Bad DEV_INFO signature.");
        }
    }
    else
    {
        if (!Fs4GetItocInfo(tocArr, numOfTocs, sect_type, curr_toc))
        {
            return false;
        }
    }

    if (!curr_toc)
    {
        return errmsg("Couldn't find TOC array.");
    }

    if (sect_type == FS3_MFG_INFO)
    {
        fs3_uid_t base_uid = *(fs3_uid_t*)new_info;
        type_msg = "GUID";
        if (!Fs4UpdateMfgUidsSection(curr_toc, curr_toc->section_data, base_uid, newSection))
        {
            return false;
        }
    }
    else if (sect_type == FS3_DEV_INFO)
    {
        if (cmd_type == CMD_SET_GUIDS)
        {
            fs3_uid_t base_uid = *(fs3_uid_t*)new_info;
            type_msg = "GUID";
            if (!Fs4UpdateUidsSection(old_toc->section_data, base_uid, newSection))
            {
                return false;
            }
        }
        else if (cmd_type == CMD_SET_VSD)
        {
            char* user_vsd = (char*)new_info;
            type_msg = "VSD";
            if (!Fs4UpdateVsdSection(old_toc->section_data, user_vsd, newSection))
            {
                return false;
            }
        }
        else
        {
            // We shouldnt reach here EVER
            type_msg = (char*)"Unknown";
        }
    }
    else if (sect_type == FS3_VPD_R0)
    {
        char* vpd_file = (char*)new_info;
        type_msg = "VPD";
        if (!Fs4UpdateVpdSection(curr_toc, vpd_file, newSection))
        {
            return false;
        }
    }
    else if (sect_type == FS4_CERT_CHAIN_0)
    {
        char* cert_chain_file = (char*)new_info;
        type_msg = "CERT_CHAIN_0";
        if (!UpdateCertChainSection(curr_toc, cert_chain_file, newSection))
        {
            return false;
        }
    }
    else if (sect_type == FS3_IMAGE_SIGNATURE_256 && cmd_type == CMD_SET_SIGNATURE)
    {
        vector<u_int8_t> sig((u_int8_t*)new_info, (u_int8_t*)new_info + IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE);
        type_msg = "SIGNATURE";
        newSection.resize(IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE);
        memcpy(newSection.data(), sig.data(), IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE);
        // Check if padding is needed, by comparing with the real size in the itoc entry:
        u_int32_t sizeInItocEntry = curr_toc->toc_entry.size << 2;
        if (sizeInItocEntry > IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE)
        {
            for (unsigned int l = 0; l < sizeInItocEntry - IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE; l++)
            {
                newSection.push_back(0x0);
            }
        }
    }
    else if (sect_type == FS3_IMAGE_SIGNATURE_512 && cmd_type == CMD_SET_SIGNATURE)
    {
        vector<u_int8_t> sig((u_int8_t*)new_info, (u_int8_t*)new_info + IMAGE_LAYOUT_IMAGE_SIGNATURE_2_SIZE);
        type_msg = "SIGNATURE";
        newSection.resize(IMAGE_LAYOUT_IMAGE_SIGNATURE_2_SIZE);
        memcpy(newSection.data(), sig.data(), IMAGE_LAYOUT_IMAGE_SIGNATURE_2_SIZE);
        u_int32_t sizeInItocEntry = curr_toc->toc_entry.size << 2;
        if (sizeInItocEntry > IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE)
        {
            for (unsigned int l = 0; l < sizeInItocEntry - IMAGE_LAYOUT_IMAGE_SIGNATURE_SIZE; l++)
            {
                newSection.push_back(0x0);
            }
        }
    }
    else if (sect_type == FS3_PUBLIC_KEYS_2048 && cmd_type == CMD_SET_PUBLIC_KEYS)
    {
        char* publickeys_file = (char*)new_info;
        type_msg = "PUBLIC KEYS";
        if (!Fs3UpdatePublicKeysSection(curr_toc->toc_entry.size, publickeys_file, newSection))
        {
            return false;
        }
    }
    else if (sect_type == FS3_PUBLIC_KEYS_4096 && cmd_type == CMD_SET_PUBLIC_KEYS)
    {
        char* publickeys_file = (char*)new_info;
        type_msg = "PUBLIC KEYS 4096";
        if (!Fs3UpdatePublicKeysSection(curr_toc->toc_entry.size, publickeys_file, newSection))
        {
            return false;
        }
    }
#if !defined(UEFI_BUILD)
    else if (sect_type == FS4_RSA_PUBLIC_KEY)
    {
        char* publicKeysData = (char*)new_info;
        type_msg = "FS4_RSA_PUBLIC_KEY";
        GetSectData(newSection, (u_int32_t*)publicKeysData, image_layout_public_keys_3_size());
    }
    else if (sect_type == FS4_RSA_4096_SIGNATURES)
    {
        char* signaturesData = (char*)new_info;
        type_msg = "FS4_RSA_4096_SIGNATURES";
        GetSectData(newSection, (u_int32_t*)signaturesData, image_layout_secure_boot_signatures_size());
    }
#endif
    else if (sect_type == FS3_FORBIDDEN_VERSIONS && cmd_type == CMD_SET_FORBIDDEN_VERSIONS)
    {
        char* forbiddenVersions_file = (char*)new_info;
        type_msg = "Forbidden Versions";
        if (!Fs3UpdateForbiddenVersionsSection(curr_toc->toc_entry.size, forbiddenVersions_file, newSection))
        {
            return false;
        }
    }
    else
    {
        return errmsg("Section type %s is not supported\n", GetSectionNameByType(sect_type));
    }

    if (!WriteSection(curr_toc, newSection, type_msg, callBackFunc))
    {
        return false;
    }

    if (is_sect_failsafe)
    {
        u_int32_t flash_addr = old_toc->toc_entry.flash_addr << 2;
        // If encrypted image was given we'll write to it
        if (_encrypted_image_io_access)
        {
            DPRINTF(("Fs4Operations::UpdateSection updating encrypted image at addr 0x%x with 0x0\n", flash_addr));
            if (!_encrypted_image_io_access->write(flash_addr, (u_int8_t*)&zeroes, sizeof(zeroes)))
            {
                return errmsg("%s", _encrypted_image_io_access->err());
            }
        }
        else
        {
            if (!writeImage((ProgressCallBack)NULL, flash_addr, (u_int8_t*)&zeroes, sizeof(zeroes), isDtoc, true))
            {
                return false;
            }
        }
    }

    return true;
}

bool Fs4Operations::WriteSection(struct fs4_toc_info* sectionToc, std::vector<u_int8_t>& newSectionData, const char* msg, PrintCallBack callBackFunc)
{
    DPRINTF(("Fs4Operations::WriteSection section type=%s, msg=%s", GetSectionNameByType(sectionToc->toc_entry.type), msg));
    bool isDtoc;
    fs3_section_t sectionType = static_cast<fs3_section_t>(sectionToc->toc_entry.type);
    if (!isDTocSection(sectionType, isDtoc))
    {
        return false;
    }
    u_int32_t newSectionAddr = sectionToc->toc_entry.flash_addr << 2;

    if (!_encrypted_image_io_access)
    { // In case of BB secure-boot sign flow we don't update ITOC since it's already encrypted
        if (!Fs4UpdateItocInfo(sectionToc, sectionToc->toc_entry.size, newSectionData))
        {
            return false;
        }
    }

    if (!Fs4ReburnSection(newSectionAddr, sectionToc->toc_entry.size * 4, newSectionData, msg, callBackFunc))
    {
        return false;
    }

    if (!_encrypted_image_io_access)
    { // In case of BB secure-boot sign flow we don't update ITOC since it's already encrypted
        if (sectionType != FS3_DEV_INFO)
        {
            if (!Fs4ReburnTocSection(isDtoc, callBackFunc))
            {
                return false;
            }
        }
    }

    if (!isDtoc)
    {
        if (!UpdateSectionHashInHashesTable(newSectionAddr, sectionToc->toc_entry.size * 4, sectionType))
        {
            return false;
        }
    }
    return true;
}

bool Fs4Operations::UpdateSection(fs3_section_t sectionType, std::vector<u_int8_t>& newSectionData, const char* msg, PrintCallBack callBackFunc)
{
    if (sectionType == FS3_DEV_INFO)
    {
        return errmsg("Fs4Operations::UpdateSection doesn't support updating DEV_INFO section\n");
    }

    // Query
    bool isDtoc;
    if (!isDTocSection(sectionType, isDtoc))
    {
        return false;
    }
    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return errmsg(getErrorCode(), "%s", err());
    }

    if (image_encrypted)
    {
        if (!isDtoc)
        {
            return errmsg("Can't update ITOC section in case of encrypted image");
        }
        fw_info_t fwInfo;
        if (!encryptedFwQuery(&fwInfo))
        {
            return errmsg("%s", err());
        }
    }
    else
    {
        // init sector to read
        _readSectList.push_back(sectionType);
        if (!FsIntQueryAux())
        {
            _readSectList.pop_back();
            return false;
        }
        _readSectList.pop_back();
    }

    // Get relevant TOC
    struct fs4_toc_info* tocArr;
    u_int32_t numOfTocs;
    if (isDtoc)
    {
        tocArr = _fs4ImgInfo.dtocArr.tocArr;
        numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;
    }
    else
    {
        tocArr = _fs4ImgInfo.itocArr.tocArr;
        numOfTocs = _fs4ImgInfo.itocArr.numOfTocs;
    }
    // Find TOC entry
    int tocIndex = 0;
    struct fs4_toc_info* sectionToc = (fs4_toc_info*)NULL;
    if (!Fs4GetItocInfo(tocArr, numOfTocs, sectionType, sectionToc, tocIndex))
    {
        return false;
    }

    // corresponds to VPD max size in mlx
    if (sectionType == FS3_VPD_R0 && newSectionData.size() > 0x1000)
    {
        return errmsg("VPD data size exceeds max VPD size: 0x%x bytes", 0x1000);
    }

    if (!WriteSection(sectionToc, newSectionData, msg, callBackFunc))
    {
        return false;
    }

    return true;
}

u_int32_t Fs4Operations::getAbsAddr(fs4_toc_info* toc)
{
    return ((toc->toc_entry.flash_addr << 2) + _fwImgInfo.imgStart);
}

u_int32_t Fs4Operations::getAbsAddr(fs4_toc_info* toc, u_int32_t imgStart)
{
    return ((toc->toc_entry.flash_addr << 2) + imgStart);
}

bool Fs4Operations::FwShiftDevData(PrintCallBack progressFunc)
{
    // avoid compiler warrnings
    (void)progressFunc;
    return errmsg("Shifting device data sections is not supported in FS4 image format.");
}

#define OPEN_OCR(origFlashObj)                                              \
    do                                                                      \
    {                                                                       \
        origFlashObj = _ioAccess;                                           \
        _fwParams.ignoreCacheRep = 1;                                       \
        if (!FwOperations::FwAccessCreate(_fwParams, &_ioAccess))           \
        {                                                                   \
            _ioAccess = origFlashObj;                                       \
            _fwParams.ignoreCacheRep = 0;                                   \
            return errmsg("Failed to open device for direct flash access"); \
        }                                                                   \
    } while (0)

bool Fs4Operations::FwCalcMD5(u_int8_t md5sum[16])
{
#if defined(UEFI_BUILD) || defined(NO_OPEN_SSL)
    (void)md5sum;
    return errmsg("Operation not supported");
#else
    if (!FsIntQueryAux(true, false))
    {
        return false;
    }
    // push beggining of image to md5buff
    int sz = FS3_BOOT_START + _fwImgInfo.boot2Size;
    std::vector<u_int8_t> md5buff(sz, 0);
    _imageCache.get(&(md5buff[0]), sz);
    // push all non dev data sections to md5buff
    for (unsigned int j = 0; j < TOC_HEADER_SIZE; j++)
    {
        md5buff.push_back(_imageCache[_fs4ImgInfo.itocArr.tocArrayAddr + j]);
    }
    // push itoc header
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        // push each non-dev-data section to md5sum buffer
        u_int32_t tocEntryAddr = _fs4ImgInfo.itocArr.tocArr[i].entry_addr;
        u_int32_t tocDataAddr = _fs4ImgInfo.itocArr.tocArr[i].toc_entry.flash_addr << 2;
        u_int32_t tocDataSize = _fs4ImgInfo.itocArr.tocArr[i].toc_entry.size << 2;
        // itoc entry
        for (unsigned int j = 0; j < TOC_ENTRY_SIZE; j++)
        {
            md5buff.push_back(_imageCache[tocEntryAddr + j]);
        }
        // itoc data
        for (unsigned int j = 0; j < tocDataSize; j++)
        {
            md5buff.push_back(_imageCache[tocDataAddr + j]);
        }
    }
    // calc md5
    tools_md5(&md5buff[0], md5buff.size(), md5sum);
    return true;
#endif
}

bool Fs4Operations::CheckDTocArray()
{
    if (!CheckTocArrConsistency(_fs4ImgInfo.dtocArr, 0))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::CheckITocArray()
{
    // Check for inconsistency image burnt on 1st half
    if (!CheckTocArrConsistency(_fs4ImgInfo.itocArr, 0))
    {
        return false;
    }

    // Check for inconsistency image burn on second half
    if (!CheckTocArrConsistency(_fs4ImgInfo.itocArr, (1 << _fwImgInfo.cntxLog2ChunkSize)))
    {
        return false;
    }
    return true;
}

bool Fs4Operations::CheckTocArrConsistency(TocArray& tocArr, u_int32_t imageStartAddr)
{
    u_int32_t sectEndAddr = 0;
    u_int32_t nextSectStrtAddr = 0;

    // Sort the tocs
    std::vector<struct fs4_toc_info*> sortedTocVec(tocArr.numOfTocs);
    for (int i = 0; i < tocArr.numOfTocs; i++)
    {
        sortedTocVec[i] = &(tocArr.tocArr[i]);
    }
    std::sort(sortedTocVec.begin(), sortedTocVec.end(), TocComp(imageStartAddr));

    std::vector<struct fs4_toc_info*>::iterator it = sortedTocVec.begin(), itNext = sortedTocVec.begin();
    itNext++;
    for (; itNext != sortedTocVec.end(); it++, itNext++)
    {
        sectEndAddr = getAbsAddr(*it, imageStartAddr) + ((*it)->toc_entry.size << 2) - 1;
        nextSectStrtAddr = getAbsAddr(*itNext, imageStartAddr);
        if (sectEndAddr >= nextSectStrtAddr)
        {
            return errmsg("Inconsistency found in TOC. %s(0x%x) section will potentially overwrite %s(0x%x) section.", GetSectionNameByType((*it)->toc_entry.type), (*it)->toc_entry.type,
                          GetSectionNameByType((*itNext)->toc_entry.type), (*itNext)->toc_entry.type);
        }
    }

    return true;
}

u_int32_t Fs4Operations::getImageSize()
{
    return _fwImgInfo.lastImageAddr - _fwImgInfo.imgStart;
}

bool Fs4Operations::GetImageSize(u_int32_t* image_size)
{
    bool is_encrypted = false;
    if (!isEncrypted(is_encrypted))
    {
        return false;
    }

    if (is_encrypted)
    {
        if (!GetEncryptedImageSizeFromImageInfo(image_size))
        {
            return false;
        }
    }
    else
    {
        *image_size = getImageSize();
    }

    return true;
}

void Fs4Operations::MaskItocSectionAndEntry(u_int32_t itocType, vector<u_int8_t>& img)
{
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        if (_fs4ImgInfo.itocArr.tocArr[i].toc_entry.type == itocType)
        {
            //* Mask section
            u_int32_t tocEntryDataAddr = _fs4ImgInfo.itocArr.tocArr[i].toc_entry.flash_addr << 2;
            memset(img.data() + tocEntryDataAddr, 0xFF, _fs4ImgInfo.itocArr.tocArr[i].toc_entry.size << 2);

            //* Mask section's ITOC entry
            if (!_encrypted_image_io_access)
            {
                // In case of signing BB image (encrypted) we'll not mask the image signature 256/512 itoc entries
                // due to FW limitation
                u_int32_t tocEntryAddr = _fs4ImgInfo.itocArr.tocArr[i].entry_addr;
                memset(img.data() + tocEntryAddr, 0xFF, TOC_ENTRY_SIZE);
            }
        }
    }
}

void Fs4Operations::maskDevToc(vector<u_int8_t>& img)
{
    // no device tocs in the itoc
    (void)img;
    return;
}

bool Fs4Operations::FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer)
{
    CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP()

    return Fs3Operations::FwSetTimeStamp(timestamp, fwVer);
}

bool Fs4Operations::FwQueryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning)
{
    CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP()

    return Fs3Operations::FwQueryTimeStamp(timestamp, fwVer, queryRunning);
}

bool Fs4Operations::FwResetTimeStamp()
{
    CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP()

    return Fs3Operations::FwResetTimeStamp();
}

bool Fs4Operations::GetSectionSizeAndOffset(fs3_section_t sectType, u_int32_t& size, u_int32_t& offset)
{
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* toc = &_fs4ImgInfo.itocArr.tocArr[i];
        if (toc->toc_entry.type == sectType)
        {
            size = toc->toc_entry.size << 2;
            offset = toc->toc_entry.flash_addr << 2;
            return true;
        }
    }

    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* toc = &_fs4ImgInfo.dtocArr.tocArr[i];
        if (toc->toc_entry.type == sectType)
        {
            size = toc->toc_entry.size << 2;
            offset = toc->toc_entry.flash_addr << 2;
            return true;
        }
    }

    return false;
}

#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
bool validateHmacKey(string key_str, unsigned int correct_key_len)
{
    // The keyFile should contain 128 chars, each 2 of them represent 1 byte of key (hex)
    bool res = true;
    key_str.erase(std::remove_if(key_str.begin(), key_str.end(), ::isspace), key_str.end());
    if (key_str.size() != correct_key_len * 2)
    {
        res = false;
    }
    else if (key_str.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
    {
        res = false;
    }
    return res;
}
#endif
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
bool Fs4Operations::FwSignSection(const vector<u_int8_t>& section, const string privPemFileStr, vector<u_int8_t>& encSha)
{
    MlxSignRSA rsa;
    vector<u_int8_t> sha;
    int rc = rsa.setPrivKeyFromFile(privPemFileStr);
    if (rc)
    {
        return errmsg("Failed to set private key from file (rc = 0x%x)\n", rc);
    }

    MlxSignSHA512 mlxSignSHA;
    mlxSignSHA << section;
    mlxSignSHA.getDigest(sha);

    rc = rsa.sign(MlxSign::SHA512, sha, encSha);
    if (rc)
    {
        return errmsg("Failed to encrypt the SHA (rc = 0x%x)\n", rc);
    }

    return true;
}
#endif

int Fs4Operations::getBoot2Size(u_int32_t address)
{
    u_int32_t num_of_dwords = 0;

    // Read the num of DWs for the second dword
    READBUF((*_ioAccess), address + 4, &num_of_dwords, 4, "num of DWs");

    TOCPU1(num_of_dwords)

    return (4 + num_of_dwords) * 4; // 2 dwords for header + 2 dwords for tail
}

// This function is called from getBootDataForSignVersion2() only so currently it supports CX7 onwards only
bool Fs4Operations::getBootRecordSize(u_int32_t& boot_record_size)
{
    switch (getChipType(_fwImgInfo.supportedHwId[0]))
    {
        case CT_CONNECTX7:
            boot_record_size = 0x3f4;
            return true;

        // For devices after Carmel we need to ignore the last 4B (CRC/auth-tag)
        case CT_BLUEFIELD3:
            boot_record_size = 0x4d0; // Actual size is 0x4d4
            return true;
        case CT_SPECTRUM4:
        case CT_SPECTRUM5:
            boot_record_size = 0x660; // Actual size is 0x664
            return true;
        case CT_ABIR_GEARBOX:
            boot_record_size = 0x260; // Actual size is 0x264
            return true;
        case CT_CONNECTX8:
        case CT_CONNECTX9:
        case CT_CONNECTX8_PURE_PCIE_SWITCH:
        case CT_CONNECTX9_PURE_PCIE_SWITCH:
            boot_record_size = 0x2a0; // Actual size is 0x2a4
            return true;

        default:
            return false;
    }
}

bool Fs4Operations::getBootDataForSignVersion1(vector<u_int8_t>& data)
{
    u_int32_t physAddr = _authentication_start_ptr;
    const unsigned int data_size = _authentication_end_ptr - _authentication_start_ptr + 1;
    data.resize(data_size);

    //* Choosing the correct io to read from
    FBase* io = _ioAccess;
    if (_encrypted_image_io_access)
    {
        DPRINTF(("Fs4Operations::getBootDataForSignVersion1 reading from encrypted image from addr 0x%x: 0x%x bytes\n", physAddr, data_size));
        io = _encrypted_image_io_access; // If encrypted image was given we'll read from it
    }

    READBUF((*io), physAddr, data.data(), data_size, "Reading data pointed by HW Pointers");
    return true;
}

bool Fs4Operations::getBootDataForSignVersion2(vector<u_int8_t>& data)
{
    unsigned int data_offset = 0;

    // Boot version
    const u_int32_t BOOT_VERSION_ADDRESS = 0x10;
    const u_int32_t BOOT_VERSION_SIZE = 0x8; // including reserved dword
    data.resize(data.size() + BOOT_VERSION_SIZE);
    READBUF((*_ioAccess), BOOT_VERSION_ADDRESS, data.data() + data_offset, BOOT_VERSION_SIZE, "Reading boot version");

    data_offset += BOOT_VERSION_SIZE;

    // HW pointers (without CRC)
    const u_int32_t HW_POINTER_SIZE = 4;
    const u_int32_t HW_POINTER_CRC_SIZE = 4;
    const int NUM_OF_HW_POINTERS = 16;
    for (int ii = 0; ii < NUM_OF_HW_POINTERS; ii++)
    {
        data.resize(data.size() + HW_POINTER_SIZE);
        READBUF((*_ioAccess), FS4_HW_PTR_START + ii * (HW_POINTER_SIZE + HW_POINTER_CRC_SIZE), data.data() + data_offset, HW_POINTER_SIZE, "Reading HW pointer");

        data_offset += HW_POINTER_SIZE;
    }

    // Boot record
    u_int32_t boot_record_size = 0;
    if (!getBootRecordSize(boot_record_size))
    {
        return errmsg("Failed to get boot_record size\n");
    }
    data.resize(data.size() + boot_record_size);
    READBUF((*_ioAccess), _boot_record_ptr, data.data() + data_offset, boot_record_size, "Reading boot record");
    data_offset += boot_record_size;

    // Boot2
    u_int32_t boot2_size = getBoot2Size(_boot2_ptr);
    data.resize(data.size() + boot2_size);
    READBUF((*_ioAccess), _boot2_ptr, data.data() + data_offset, boot2_size, "Reading boot2");
    data_offset += boot2_size;

    // Hashes table
    u_int32_t hashes_table_size = getHashesTableSize(_hashes_table_ptr);
    data.resize(data.size() + hashes_table_size);
    READBUF((*_ioAccess), _hashes_table_ptr, data.data() + data_offset, hashes_table_size, "Reading hashes table");

    return true;
}

bool Fs4Operations::getBootDataForSign(vector<u_int8_t>& data)
{
    switch (getSecureBootSignVersion())
    {
        case VERSION_1:
            return getBootDataForSignVersion1(data);
        case VERSION_2:
            return getBootDataForSignVersion2(data);
        default:
            return false;
    }
}

#if !defined(UEFI_BUILD)
bool fromFileToArray(string& fileName, vector<u_int8_t>& outputArray, unsigned int PublicKeySize)
{
    FILE* pFile = fopen(fileName.c_str(), "rt");
    if (pFile == NULL)
    {
        return false;
    }
    fseek(pFile, 0L, SEEK_END);
    size_t input_length = ftell(pFile);
    // input length must be 2*puublic key size since the input file is text formatted and each 2 characters in it = 1
    // byte data
    if (input_length != (PublicKeySize << 1))
    {
        fclose(pFile);
        return false;
    }
    fseek(pFile, 0L, SEEK_SET);
    char* data = new char[input_length];
    if (data == NULL)
    {
        fclose(pFile);
        return false;
    }
    fread(data, sizeof(char), input_length, pFile);
    fclose(pFile);
    outputArray.resize(input_length / 2);
    for (size_t i = 0; i < input_length; i += 2)
    {
        char tempBuf[3] = {0};
        tempBuf[0] = data[i];
        tempBuf[1] = data[i + 1];
        int scanResult = 0;
        if (sscanf(tempBuf, "%x", &scanResult) != 1)
        {
            delete[] data;
            return false;
        }
        outputArray[i / 2] = scanResult;
    }
    delete[] data;
    return true;
}
#endif

bool Fs4Operations::IsSecureBootSupported()
{
    if (_signatureMngr == NULL)
    {
        return false;
    }
    return _signatureMngr->IsSecureBootSupported();
}

bool Fs4Operations::IsCableQuerySupported()
{
    if (_signatureMngr == NULL)
    {
        return false;
    }
    return _signatureMngr->IsCableQuerySupported();
}

bool Fs4Operations::IsLifeCycleSupported()
{
    if (_signatureMngr == NULL)
    {
        return false;
    }
    return _signatureMngr->IsLifeCycleSupported();
}

bool Fs4Operations::ParsePublicKeyFromFile(const char* public_key_file, vector<u_int8_t>& publicKeyData, u_int32_t& keyPairExp, image_layout_component_authentication_configuration& keyAuthConf)
{
    image_layout_public_keys_3 unpackedData;
    unsigned int PublicKeySize = sizeof(unpackedData.file_public_keys_3[0].key);
    fs3_section_t sectionType;
    bool PublicKeyIsSet = false;
    unsigned int pem_offset = 0;
    keyPairExp = 0x10001; // Default value
    // is the public key file in PEM format?
    if (CheckPublicKeysFile(public_key_file, sectionType, true))
    {
        if (sectionType == FS3_PUBLIC_KEYS_4096)
        {
            if (Fs3UpdatePublicKeysSection((IMAGE_LAYOUT_PUBLIC_KEYS_3_SIZE >> 2), public_key_file, publicKeyData, true))
            {
                PublicKeyIsSet = true;
                pem_offset = IMAGE_LAYOUT_FILE_PUBLIC_KEYS_3_SIZE - PublicKeySize;                              // first 32 bytes in the PEM file are auxilary data
                image_layout_component_authentication_configuration_unpack(&keyAuthConf, publicKeyData.data()); // First Dword represents the key auth conf
                u_int32_t keyPairExpOffset = 3;                                                                 // Fourth Dword represents key pair exponent
                keyPairExp = *((u_int32_t*)publicKeyData.data() + keyPairExpOffset);
                TOCPU1(keyPairExp);
            }
        }
    }
    // Is the public key file in text format?
    if (PublicKeyIsSet == false)
    {
        string pubFileStr(public_key_file);
        if (!fromFileToArray(pubFileStr, publicKeyData, PublicKeySize))
        {
            return errmsg("ParsePublicKeyFromFile: Public key file parsing failed");
        }
        DPRINTF(("Public key in text format. No key pair exponent and key auth conf, using default values\n"));
        memset(&keyAuthConf, 0, sizeof(keyAuthConf));
    }

    if (pem_offset > 0)
    {
        publicKeyData.erase(publicKeyData.begin(), publicKeyData.begin() + pem_offset);
    }
    return true;
}

void Fs4Operations::PreparePublicKey(const vector<u_int8_t>& publicKeyData,
                                     const vector<u_int32_t>& uuidData,
                                     const u_int32_t keyPairExp,
                                     const image_layout_component_authentication_configuration& keyAuthConf,
                                     image_layout_file_public_keys_3& publicKey)
{
    unsigned int PublicKeySize = sizeof(publicKey.key);
    publicKey.keypair_exp = keyPairExp;
    publicKey.component_authentication_configuration = keyAuthConf;
    memcpy(&publicKey.keypair_uuid, uuidData.data(), sizeof(publicKey.keypair_uuid));
    memcpy(&publicKey.key, publicKeyData.data(), PublicKeySize);
    TOCPUn(&publicKey.key, PublicKeySize >> 2);
}

bool Fs4Operations::GetFreeSlotInPublicKeys2(const image_layout_public_keys_2& public_keys, u_int32_t& idx)
{
    u_int32_t num_of_key_slots = image_layout_public_keys_2_size() / image_layout_file_public_keys_2_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        const image_layout_file_public_keys_2& public_key = public_keys.file_public_keys_2[ii];
        if (all_of(public_key.keypair_uuid, public_key.keypair_uuid + 4, [](u_int32_t val) { return val == 0; }))
        {
            idx = ii;
            DPRINTF(("free slot at index = %d\n", idx));
            return true;
        }
    }
    return errmsg("GetFreeSlotInPublicKeys2 failed - No free slot for public key\n");
}

bool Fs4Operations::GetFreeSlotInPublicKeys3(const image_layout_public_keys_3& public_keys, u_int32_t& idx)
{
    u_int32_t num_of_key_slots = image_layout_public_keys_3_size() / image_layout_file_public_keys_3_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        const image_layout_file_public_keys_3& public_key = public_keys.file_public_keys_3[ii];
        if (all_of(public_key.keypair_uuid, public_key.keypair_uuid + 4, [](u_int32_t val) { return val == 0; }))
        {
            idx = ii;
            DPRINTF(("free slot at index = %d\n", idx));
            return true;
        }
    }
    return errmsg("GetFreeSlotInPublicKeys3 failed - No free slot for public key\n");
}

bool Fs4Operations::FindPublicKeyInPublicKeys2(const image_layout_public_keys_2& public_keys, const image_layout_file_public_keys_2& public_key, u_int32_t& idx)
{
    bool res = false;
    u_int32_t num_of_key_slots = image_layout_public_keys_2_size() / image_layout_file_public_keys_2_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        auto stored_public_key = public_keys.file_public_keys_2[ii];
        // Compare keys based on UUID
        if (equal(begin(public_key.keypair_uuid), end(public_key.keypair_uuid), begin(stored_public_key.keypair_uuid)))
        {
            idx = ii;
            res = true;
            break;
        }
    }
    return res;
}

bool Fs4Operations::FindPublicKeyInPublicKeys3(const image_layout_public_keys_3& public_keys, const image_layout_file_public_keys_3& public_key, u_int32_t& idx)
{
    bool res = false;
    u_int32_t num_of_key_slots = image_layout_public_keys_3_size() / image_layout_file_public_keys_3_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        auto stored_public_key = public_keys.file_public_keys_3[ii];
        // Compare keys based on UUID
        if (equal(begin(public_key.keypair_uuid), end(public_key.keypair_uuid), begin(stored_public_key.keypair_uuid)))
        {
            idx = ii;
            res = true;
            break;
        }
    }
    return res;
}

bool Fs4Operations::FindImagePublicKeyInPublicKeys2(const image_layout_public_keys_2& public_keys, u_int32_t& idx)
{
    bool res = false;
    u_int32_t num_of_key_slots = image_layout_public_keys_2_size() / image_layout_file_public_keys_2_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        if (public_keys.file_public_keys_2[ii].component_authentication_configuration.fw_en == 1)
        {
            idx = ii;
            res = true;
            break;
        }
    }
    return res;
}

bool Fs4Operations::GetRSAPublicKey(vector<u_int8_t>& key)
{
    if (!InitHwPtrs())
    {
        return errmsg("HW pointers not found");
    }

    vector<u_int8_t> rsaPublicKeys(image_layout_public_keys_3_size());
    if (!FwReadBlock(_public_key_ptr, image_layout_public_keys_3_size(), rsaPublicKeys))
    {
        return false;
    }

    image_layout_public_keys_3 stored_public_keys_3;
    memset(&stored_public_keys_3, 0, sizeof(stored_public_keys_3));
    image_layout_public_keys_3_unpack(&stored_public_keys_3, rsaPublicKeys.data());

    u_int32_t imagePublicKeyIndex = 0;
    if (!FindImagePublicKeyInPublicKeys3(stored_public_keys_3, imagePublicKeyIndex))
    {
        return errmsg("Couldn't find RSA public key");
    }

    key.resize(image_layout_file_public_keys_3_size());
    image_layout_file_public_keys_3_pack(&stored_public_keys_3.file_public_keys_3[imagePublicKeyIndex], key.data());
    return true;
}

bool Fs4Operations::FindImagePublicKeyInPublicKeys3(const image_layout_public_keys_3& public_keys, u_int32_t& idx)
{
    bool res = false;
    u_int32_t num_of_key_slots = image_layout_public_keys_3_size() / image_layout_file_public_keys_3_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        if (public_keys.file_public_keys_3[ii].component_authentication_configuration.fw_en == 1)
        {
            idx = ii;
            res = true;
            break;
        }
    }
    return res;
}

bool Fs4Operations::StoreImagePublicKeyInPublicKeys2(const image_layout_file_public_keys_3& public_key)
{
    // Find ITOC entry
    fs4_toc_info* itocEntry = (fs4_toc_info*)NULL;
    image_layout_public_keys_2 public_keys_2 = {{}};
    memset(&public_keys_2, 0, sizeof(public_keys_2));
    if (!Fs4GetItocInfo(_fs4ImgInfo.itocArr.tocArr, _fs4ImgInfo.itocArr.numOfTocs, FS3_PUBLIC_KEYS_4096, itocEntry))
    {
        return errmsg("StoreImagePublicKeyInPublicKeys2 failed - Error: %s", err());
    }
    image_layout_public_keys_2_unpack(&public_keys_2, itocEntry->section_data.data());

    // Convert public_keys_3 to public_keys_2
    image_layout_file_public_keys_2 new_public_key_2 = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, {0, 0, 0, 0}, {0}};
    ;
    PublicKey3ToPublicKey2(public_key, new_public_key_2);

    u_int32_t slot_of_given_key_in_image = 0;
    if (!FindPublicKeyInPublicKeys2(public_keys_2, new_public_key_2, slot_of_given_key_in_image))
    {
        if (new_public_key_2.component_authentication_configuration.auth_type == 0)
        {
            return errmsg("StoreImagePublicKeyInPublicKeys2 failed - missing authentication configuration data");
        }
        else
        {
            u_int32_t slot_idx_for_new_key = 0;
            if (!FindImagePublicKeyInPublicKeys2(public_keys_2, slot_idx_for_new_key))
            {
                if (!GetFreeSlotInPublicKeys2(public_keys_2, slot_idx_for_new_key))
                {
                    return errmsg("StoreImagePublicKeyInPublicKeys2 failed - Error: %s", err());
                }
            }

            // Prepare public_keys_2 section data with public key at free slot index
            public_keys_2.file_public_keys_2[slot_idx_for_new_key] = new_public_key_2;
            vector<u_int8_t> public_keys_2_data;
            public_keys_2_data.resize(image_layout_public_keys_2_size());
            image_layout_public_keys_2_pack(&public_keys_2, public_keys_2_data.data());
            if (!UpdateSection(FS3_PUBLIC_KEYS_4096, public_keys_2_data, "PUBLIC KEYS 4096"))
            {
                return errmsg("StoreImagePublicKeyInPublicKeys2 failed - Error: %s", err());
            }
        }
    }
    else
    {
        if (public_keys_2.file_public_keys_2[slot_of_given_key_in_image].component_authentication_configuration.fw_en == 0)
        {
            return errmsg("StoreImagePublicKeyInPublicKeys2 failed - key exists but conflicts authentication configuration");
        }
    }

    return true;
}

bool Fs4Operations::StoreImagePublicKeyInPublicKeys3(const image_layout_file_public_keys_3& public_key)
{
    fs4_toc_info* itocEntry = (fs4_toc_info*)NULL;
    if (!Fs4GetItocInfo(_fs4ImgInfo.itocArr.tocArr, _fs4ImgInfo.itocArr.numOfTocs, FS4_RSA_PUBLIC_KEY, itocEntry))
    {
        return errmsg("StoreImagePublicKeyInPublicKeys3 failed - Error: %s", err());
    }

    image_layout_public_keys_3 public_keys_3;
    memset(&public_keys_3, 0, sizeof(public_keys_3));
    image_layout_public_keys_3_unpack(&public_keys_3, itocEntry->section_data.data());

    u_int32_t slot_of_given_key_in_image = 0;
    if (!FindPublicKeyInPublicKeys3(public_keys_3, public_key, slot_of_given_key_in_image))
    {
        if (public_key.component_authentication_configuration.auth_type == 0)
        {
            return errmsg("StoreImagePublicKeyInPublicKeys3 failed - missing authentication configuration data");
        }
        else
        {
            u_int32_t slot_idx_for_new_key = 0;
            if (!FindImagePublicKeyInPublicKeys3(public_keys_3, slot_idx_for_new_key))
            {
                if (!GetFreeSlotInPublicKeys3(public_keys_3, slot_idx_for_new_key))
                {
                    return errmsg("StoreImagePublicKeyInPublicKeys3 failed - Error: %s", err());
                }
            }

            public_keys_3.file_public_keys_3[slot_idx_for_new_key] = public_key;

            vector<u_int8_t> public_keys_3_data;
            public_keys_3_data.resize(image_layout_public_keys_3_size());
            image_layout_public_keys_3_pack(&public_keys_3, public_keys_3_data.data());
            if (!UpdateSection(public_keys_3_data.data(), FS4_RSA_PUBLIC_KEY, true, CMD_BURN, NULL))
            {
                return errmsg("StoreImagePublicKeyInPublicKeys3 failed - Error: %s", err());
            }
        }
    }
    else
    {
        if (public_keys_3.file_public_keys_3[slot_of_given_key_in_image].component_authentication_configuration.fw_en == 0)
        {
            return errmsg("StoreImagePublicKeyInPublicKeys3 failed - key exists but conflicts authentication configuration");
        }
    }

    return true;
}

bool Fs4Operations::FindPublicKeyInPublicKeys2(const vector<u_int32_t>& keypair_uuid, bool& found, image_layout_file_public_keys_3& public_key)
{
    // Find ITOC entry
    fs4_toc_info* itocEntry = (fs4_toc_info*)NULL;
    if (!Fs4GetItocInfo(_fs4ImgInfo.itocArr.tocArr, _fs4ImgInfo.itocArr.numOfTocs, FS3_PUBLIC_KEYS_4096, itocEntry))
    {
        return errmsg("FindPublicKeyInPublicKeys2 failed - Error: %s", err());
    }

    u_int32_t num_of_key_slots = image_layout_public_keys_2_size() / image_layout_file_public_keys_2_size();
    for (u_int32_t ii = 0; ii < num_of_key_slots; ii++)
    {
        u_int32_t key_start_offset = ii * image_layout_file_public_keys_2_size();
        image_layout_file_public_keys_2 stored_public_key;
        memset(&stored_public_key, 0, sizeof(stored_public_key));
        image_layout_file_public_keys_2_unpack(&stored_public_key, itocEntry->section_data.data() + key_start_offset);

        // Compare keys based on UUID
        if (equal(begin(keypair_uuid), end(keypair_uuid), begin(stored_public_key.keypair_uuid)))
        {
            found = true;
            memset(&public_key, 0, sizeof(public_key));
            copy(begin(stored_public_key.key), end(stored_public_key.key), begin(public_key.key));
            copy(begin(stored_public_key.keypair_uuid), end(stored_public_key.keypair_uuid), begin(public_key.keypair_uuid));
            public_key.keypair_exp = stored_public_key.keypair_exp;
            public_key.component_authentication_configuration = stored_public_key.component_authentication_configuration;
            break;
        }
    }
    return true;
}

void Fs4Operations::PublicKey3ToPublicKey2(const image_layout_file_public_keys_3& public_key_3, image_layout_file_public_keys_2& public_key_2)
{
    memset(&public_key_2, 0, sizeof(public_key_2));
    copy(begin(public_key_3.key), end(public_key_3.key), begin(public_key_2.key));
    copy(begin(public_key_3.keypair_uuid), end(public_key_3.keypair_uuid), begin(public_key_2.keypair_uuid));
    public_key_2.keypair_exp = public_key_3.keypair_exp;
    public_key_2.component_authentication_configuration = public_key_3.component_authentication_configuration;
}

void Fs4Operations::PublicKey2ToPublicKey3(const image_layout_file_public_keys_2& public_key_2, image_layout_file_public_keys_3& public_key_3)
{
    memset(&public_key_3, 0, sizeof(public_key_3));
    copy(begin(public_key_2.key), end(public_key_2.key), begin(public_key_3.key));
    copy(begin(public_key_2.keypair_uuid), end(public_key_2.keypair_uuid), begin(public_key_3.keypair_uuid));
    public_key_3.keypair_exp = public_key_2.keypair_exp;
    public_key_3.component_authentication_configuration = public_key_2.component_authentication_configuration;
}

bool Fs4Operations::ReadPublicKeys2SectionFromFile(const char* fname, image_layout_public_keys_2& public_keys_2_section)
{
    int publicKeysSize = 0;
    int publicKeyStartIdx = 0;
    int publicKeySectionIdx = 0;
    u_int8_t* publicKeysData = nullptr;
    if (!ReadBinFile(fname, publicKeysData, publicKeysSize))
    {
        return false;
    }

    if (publicKeysSize < IMAGE_LAYOUT_FILE_PUBLIC_KEYS_2_SIZE || publicKeysSize > IMAGE_LAYOUT_PUBLIC_KEYS_2_SIZE)
    {
        delete[] publicKeysData;
        return errmsg("Invalid size (%d bytes) of public keys file", publicKeysSize);
    }

    while (publicKeyStartIdx + IMAGE_LAYOUT_FILE_PUBLIC_KEYS_2_SIZE <= publicKeysSize)
    {
        image_layout_file_public_keys_2_unpack(&public_keys_2_section.file_public_keys_2[publicKeySectionIdx], &publicKeysData[publicKeyStartIdx]);
        publicKeyStartIdx += IMAGE_LAYOUT_FILE_PUBLIC_KEYS_2_SIZE;
        publicKeySectionIdx++;
    }

    delete[] publicKeysData;
    return true;
}

bool Fs4Operations::FwSetPublicKeys(char* fname, PrintCallBack callBackFunc)
{
    fs3_section_t sectionType;

    if (!Fs3Operations::FwSetPublicKeys(fname, callBackFunc))
    {
        return false;
    }

    if (!CheckPublicKeysFile(fname, sectionType))
    {
        return false;
    }

    if (sectionType == FS3_PUBLIC_KEYS_4096)
    {
        struct fs4_toc_info* toc = (struct fs4_toc_info*)nullptr;
        if (Fs4GetItocInfo(_fs4ImgInfo.itocArr.tocArr, _fs4ImgInfo.itocArr.numOfTocs, FS4_RSA_PUBLIC_KEY, toc))
        {
            image_layout_public_keys_2 public_keys_2;
            image_layout_public_keys_3 public_keys_3;
            memset(&public_keys_2, 0, sizeof(public_keys_2));
            memset(&public_keys_3, 0, sizeof(public_keys_3));

            if (!ReadPublicKeys2SectionFromFile(fname, public_keys_2))
            {
                return false;
            }

            u_int32_t num_of_key_slots = image_layout_public_keys_3_size() / image_layout_file_public_keys_3_size();
            for (u_int32_t i = 0; i < num_of_key_slots; ++i)
            {
                PublicKey2ToPublicKey3(public_keys_2.file_public_keys_2[i], public_keys_3.file_public_keys_3[i]);
            }

            vector<u_int8_t> public_keys_3_data;
            public_keys_3_data.resize(image_layout_public_keys_2_size());
            image_layout_public_keys_3_pack(&public_keys_3, public_keys_3_data.data());
            if (!UpdateSection(FS4_RSA_PUBLIC_KEY, public_keys_3_data, "FS4_RSA_PUBLIC_KEY", callBackFunc))
            {
                return errmsg("FwSetPublicKeys failed - Error: %s", err());
            }

            if (!FsIntQueryAux(false, false))
            {
                return false;
            }

            INSERT_SHA_IF_NEEDS(callBackFunc);
        }
        else
        {
            err_clear();
        }
    }

    return true;
}

bool Fs4Operations::StoreImagePublicKey(const char* public_key_file, const char* uuid)
{
    image_layout_file_public_keys_3 public_key_3;
    memset(&public_key_3, 0, sizeof(public_key_3));
    if (!GetPublicKeyFromFile(public_key_file, uuid, &(public_key_3)))
    {
        return errmsg("StoreImagePublicKey failed - Error: %s", err());
    }

    if (!StoreImagePublicKeyInPublicKeys2(public_key_3))
    {
        return errmsg("StoreImagePublicKey failed - Error: %s", err());
    }

    if (!StoreImagePublicKeyInPublicKeys3(public_key_3))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::storeSecureBootSignaturesInSection(vector<u_int8_t> boot_signature, vector<u_int8_t> critical_sections_signature, vector<u_int8_t> non_critical_sections_signature)
{
    //* Assert critical and non-critical signatures vectors are both empty or both not empty
    if (critical_sections_signature.empty() != non_critical_sections_signature.empty())
    {
        return false;
    }

    vector<u_int8_t> finishData;

    image_layout_secure_boot_signatures secure_boot_signatures;
    memset(&secure_boot_signatures, 0, sizeof(secure_boot_signatures));

    memcpy(&secure_boot_signatures.boot_signature, boot_signature.data(), sizeof(secure_boot_signatures.boot_signature));
    TOCPUn(&secure_boot_signatures.boot_signature, sizeof(secure_boot_signatures.boot_signature) >> 2);

    if (!critical_sections_signature.empty())
    {
        memcpy(&secure_boot_signatures.critical_signature, critical_sections_signature.data(), sizeof(secure_boot_signatures.critical_signature));
        TOCPUn(&secure_boot_signatures.critical_signature, sizeof(secure_boot_signatures.critical_signature) >> 2);
    }

    if (!non_critical_sections_signature.empty())
    {
        memcpy(&secure_boot_signatures.non_critical_signature, non_critical_sections_signature.data(), sizeof(secure_boot_signatures.non_critical_signature));
        TOCPUn(&secure_boot_signatures.non_critical_signature, sizeof(secure_boot_signatures.non_critical_signature) >> 2);
    }

    finishData.resize(image_layout_secure_boot_signatures_size());
    image_layout_secure_boot_signatures_pack(&secure_boot_signatures, finishData.data());
    if (!UpdateSection(finishData.data(), FS4_RSA_4096_SIGNATURES, true, CMD_BURN, NULL))
    {
        return errmsg("storeSecureBootSignaturesInSection: store secure-boot signatures failed.\n");
    }
    return true;
}

bool Fs4Operations::InitHwPtrs(bool isVerify)
{
    DPRINTF(("Fs4Operations::InitHwPtrs\n"));
    if (!getImgStart())
    { // Set _fwImgInfo.imgStart with the image start address
        return false;
    }

    if (!getExtendedHWAravaPtrs((VerifyCallBack)NULL, _ioAccess, false, isVerify))
    {
        return errmsg("InitHwPtrs: HW pointers not found.\n");
    }
    return true;
}

bool Fs4Operations::GetHashesTableSize(u_int32_t& size)
{
    bool image_encrypted = false;
    if (!isEncrypted(image_encrypted))
    {
        return false;
    }
    u_int32_t htoc_hash_size = HTOC_HASH_SIZE; // In case of encrypted device we can't parse HTOC header to get hash size so we use constant
    u_int8_t htoc_max_num_of_entries = MAX_HTOC_ENTRIES_NUM;
    if (!image_encrypted)
    {
        //* Read HTOC header for hash size
        u_int8_t* buff;
        u_int32_t htoc_header_address = _hashes_table_ptr + IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE;
        READALLOCBUF((*_ioAccess), htoc_header_address, buff, IMAGE_LAYOUT_HTOC_HEADER_SIZE, "HTOC header");
        image_layout_htoc_header header;
        image_layout_htoc_header_unpack(&header, buff);
        htoc_hash_size = header.hash_size;
        htoc_max_num_of_entries = header.version == 1 ? MAX_HTOC_ENTRIES_NUM_VERSION_1 : htoc_max_num_of_entries;
        free(buff);
    }
    u_int32_t htoc_size = IMAGE_LAYOUT_HTOC_HEADER_SIZE + htoc_max_num_of_entries * (IMAGE_LAYOUT_HTOC_ENTRY_SIZE + htoc_hash_size);
    size = IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE + htoc_size + HASHES_TABLE_TAIL_SIZE;

    return true;
}

bool Fs4Operations::GetHashesTableData(vector<u_int8_t>& data)
{
    if (!isHashesTableHwPtrValid())
    {
        return false;
    }

    //* Get size
    u_int32_t hashes_table_size = 0;
    if (!GetHashesTableSize(hashes_table_size))
    {
        return false;
    }

    //* Read hashes table
    u_int8_t* buff;
    READALLOCBUF((*_ioAccess), _hashes_table_ptr, buff, hashes_table_size, "HASHES TABLE");
    data.insert(data.end(), buff, buff + hashes_table_size);
    free(buff);

    return true;
}

//! TODO - Fix return value to status and result as output argument
bool Fs4Operations::isHashesTableHwPtrValid()
{
    //* Check HW pointers initialized
    if (!_is_hw_ptrs_initialized)
    {
        if (!InitHwPtrs())
        {
            return errmsg("isHashesTableHwPtrValid: HW pointers not found");
        }
    }

    //* Check if pointer is valid
    bool res = true;
    if (_hashes_table_ptr == 0xffffffff or _hashes_table_ptr == 0x0)
    {
        res = false;
    }
    return res;
}

SecureBootSignVersion Fs4Operations::getSecureBootSignVersion()
{
    SecureBootSignVersion res = VERSION_1;

    //* Check if hashes_table exists
    if (isHashesTableHwPtrValid())
    {
        res = VERSION_2;
    }
    return res;
}

bool Fs4Operations::SignForSecureBoot(const char* public_key_file, const char* uuid, const MlxSign::Signer& signer)
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    if (_ioAccess->is_flash())
    {
        return errmsg("SignForSecureBoot not allowed for devices");
    }
    if (!Init())
    {
        return errmsg("SignForSecureBoot failed - Error: %s\n", err());
    }

    SecureBootSignVersion secure_boot_version = getSecureBootSignVersion();

    if (secure_boot_version == VERSION_2)
    {
        if (!SetImageIVHwPointer())
        {
            return errmsg("SignForSecureBoot failed - Error: %s\n", err());
        }
    }

    if (!StoreImagePublicKey(public_key_file, uuid))
    {
        return errmsg("SignForSecureBoot failed - Error: StoreImagePublicKey failed (%s)\n", err());
    }

    //* Get boot area signature
    vector<u_int8_t> boot_data;
    vector<u_int8_t> boot_signature;
    if (!getBootDataForSign(boot_data))
    {
        return errmsg("SignForSecureBoot failed - Error: getBootDataForSign failed (%s)\n", err());
    }
    int rc = signer.Sign(boot_data, boot_signature);
    if (rc)
    {
        return errmsg("SignForSecureBoot failed - Error: failed to set private key from engine (rc = 0x%x)", rc);
    }

    //* Get critical and non-critical sections signatures
    vector<u_int8_t> critical_sections_data, non_critical_sections_data;
    vector<u_int8_t> critical_signature, non_critical_signature;
    if (secure_boot_version == VERSION_1)
    {
        if (!getCriticalNonCriticalSections(critical_sections_data, non_critical_sections_data))
        {
            return errmsg("SignForSecureBoot failed - Error: getCriticalNonCriticalSections failed (%s)\n", err());
        }
        rc = signer.Sign(critical_sections_data, critical_signature);
        if (rc)
        {
            return errmsg("SignForSecureBoot failed - Error: failed to set private key from engine (rc = 0x%x)", rc);
        }
        rc = signer.Sign(non_critical_sections_data, non_critical_signature);
        if (rc)
        {
            return errmsg("SignForSecureBoot failed - Error: failed to set private key from engine (rc = 0x%x)", rc);
        }
    }

    //* Store secure boot signatures in section
    bool res;
    if (secure_boot_version == VERSION_1)
    {
        res = storeSecureBootSignaturesInSection(boot_signature, critical_signature, non_critical_signature);
    }
    else
    {
        res = storeSecureBootSignaturesInSection(boot_signature);
    }
    if (!res)
    {
        return errmsg("SignForSecureBoot: Failed to insert secure boot signatures (%s)\n", err());
    }

    return true;
#else
    (void)public_key_file;
    (void)uuid;
    (void)signer;
    return errmsg("SignForSecureBoot is not suppported");
#endif
}

bool Fs4Operations::GetPublicKeyFromFile(const char* public_key_file, const char* uuid, image_layout_file_public_keys_3* public_key)
{
    //* Parse uuid
    vector<u_int32_t> uuidData;
    if (!extractUUIDFromString(uuid, uuidData))
    {
        return errmsg("preparePublicKeyDataForStore: UUID parsing failed.");
    }

    //* Parse public-key
    vector<u_int8_t> publicKeyData;
    u_int32_t keyPairExp = 0;
    image_layout_component_authentication_configuration keyAuthConf;
    memset(&keyAuthConf, 0, sizeof(keyAuthConf));
    if (!ParsePublicKeyFromFile(public_key_file, publicKeyData, keyPairExp, keyAuthConf))
    {
        return errmsg("preparePublicKeyDataForStore failed - Error: %s", err());
    }

    PreparePublicKey(publicKeyData, uuidData, keyPairExp, keyAuthConf, *public_key);

    return true;
}

bool Fs4Operations::FwSignWithHmac(const char* keyFile)
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    vector<u_int8_t> critical, non_critical, bin_data, digest;
    u_int32_t physAddr = _authentication_start_ptr;
    if (_ioAccess->is_flash())
    {
        return errmsg("Adding HMAC not allowed for devices");
    }
    if (!getExtendedHWPtrs((VerifyCallBack)NULL, _ioAccess))
    {
        return false;
    }
    const unsigned int s = _authentication_end_ptr - _authentication_start_ptr + 1;

    bin_data.resize(s);
    READBUF((*_ioAccess), physAddr, bin_data.data(), s, "Reading data pointed by HW Pointers");

    const int key_len = 64;
    std::ifstream f(keyFile);
    std::stringstream buf;
    buf << f.rdbuf();
    std::string fileContents = buf.str();
    if (!validateHmacKey(fileContents, key_len))
        return errmsg("Key must be of length of 64 bytes, each byte represented with two chars (hex)");
    unsigned char key_buf[key_len + 1];
    std::string num_str = "";
    size_t file_content_size = fileContents.size();
    for (size_t i = 0; i < file_content_size; i++)
    {
        if (i % 2 != 0)
        {
            num_str += fileContents[i];
            key_buf[i / 2] = strtol(num_str.c_str(), NULL, 16);
        }
        else
        {
            num_str = fileContents[i];
        }
    }
    vector<u_int8_t> key(key_buf, key_buf + key_len);

    PrepItocSectionsForHmac(critical, non_critical);
    if (!CalcHMAC(key, bin_data, digest))
    {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr, digest.data(), digest.size(), true, true, 0, 0))
    {
        return false;
    }

    digest.resize(0x0);
    if (!CalcHMAC(key, critical, digest))
    {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr + digest.size(), digest.data(), digest.size(), true, true, 0, 0))
    {
        return false;
    }

    digest.resize(0);
    if (!CalcHMAC(key, non_critical, digest))
    {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr + 2 * digest.size(), digest.data(), digest.size(), true, true, 0, 0))
    {
        return false;
    }

    return true;
#else
    (void)keyFile;
    return errmsg("FwSignWithHmac is not suppported.");
#endif
}

bool Fs4Operations::updateHwPointer(u_int32_t addr, u_int32_t val)
{
    struct image_layout_hw_pointer_entry hw_pointer = image_layout_hw_pointer_entry();
    hw_pointer.ptr = TOCPU1(val);

    //* Calculate CRC
    vector<u_int8_t> hw_pointer_data(IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE, 0x0);
    image_layout_hw_pointer_entry_pack(&hw_pointer, hw_pointer_data.data());
    hw_pointer.crc = calc_hw_crc(hw_pointer_data.data(), IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE - 2);

    //* Write HW pointer and its CRC to image
    image_layout_hw_pointer_entry_pack(&hw_pointer, hw_pointer_data.data());
    if (!_ioAccess->write(addr, hw_pointer_data.data(), IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE))
    {
        return errmsg("updateHwPointer writing to hw pointer in addr 0x%08x failed\n", addr);
    }

    return true;
}

bool Fs4Operations::SetImageIVHwPointer()
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    if (_ioAccess->is_flash())
    {
        return errmsg("SetImageIVHwPointer is not applicable for devices\n");
    }
    fw_info_t fwInfo;
    if (!FwQuery(&fwInfo, false, false, false, true))
    {
        return false; // implicit set to errmsg
    }
    //* Assuming query already done so image info section is parsed and following members initialized accordingly
    struct image_layout_FW_VERSION fw_version;
    fw_version.MAJOR = _fwImgInfo.ext_info.fw_ver[0];
    fw_version.MINOR = _fwImgInfo.ext_info.fw_ver[1];
    fw_version.SUBMINOR = _fwImgInfo.ext_info.fw_ver[2];
    fw_version.Hour = _fwImgInfo.ext_info.fw_rel_time[0];
    fw_version.Minutes = _fwImgInfo.ext_info.fw_rel_time[1];
    fw_version.Seconds = _fwImgInfo.ext_info.fw_rel_time[2];
    fw_version.Day = _fwImgInfo.ext_info.fw_rel_date[0];
    fw_version.Month = _fwImgInfo.ext_info.fw_rel_date[1];
    fw_version.Year = _fwImgInfo.ext_info.fw_rel_date[2];

    vector<u_int8_t> fw_version_data(IMAGE_LAYOUT_FW_VERSION_SIZE, 0x0);
    image_layout_FW_VERSION_pack(&fw_version, fw_version_data.data());
    DPRINTF(("Fs4Operations::SetImageIVHwPointer FW version and date for hash256:\n"));
    for (u_int32_t i = 0; i < (u_int32_t)fw_version_data.size(); i += 4)
    {
        DPRINTF(("Fs4Operations::SetImageIVHwPointer 0x%02x%02x%02x%02x\n", fw_version_data[i], fw_version_data[i + 1], fw_version_data[i + 2], fw_version_data[i + 3]));
    }

    //* Calculate SHA256 on FW version and date
    MlxSignSHA256 mlxSignSHA;
    mlxSignSHA << fw_version_data;
    vector<u_int8_t> sha;
    mlxSignSHA.getDigest(sha);

    u_int32_t image_iv = ((u_int32_t*)sha.data())[0];
    DPRINTF(("Fs4Operations::SetImageIVHwPointer image_iv = 0x%08x", image_iv));

    return updateHwPointer(DELTA_IV_HW_POINTER_ADDR, image_iv);
#else
    return errmsg("SetImageIVHwPointer is not suppported");
#endif
}

bool Fs4Operations::PrepItocSectionsForHmac(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    if (!FsIntQueryAux(true, false))
    {
        return false;
    }

    for (int i = 0; i < this->_fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* itoc_info_p = &this->_fs4ImgInfo.itocArr.tocArr[i];
        struct image_layout_itoc_entry* toc_entry = &(itoc_info_p->toc_entry);
        if (IsCriticalSection(toc_entry->type))
        {
            critical.reserve(critical.size() + itoc_info_p->section_data.size());
            critical.insert(critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
        }
        else
        {
            if (itoc_info_p->toc_entry.type == FS4_RSA_4096_SIGNATURES)
            {
                continue;
            }
            non_critical.reserve(non_critical.size() + itoc_info_p->section_data.size());
            non_critical.insert(non_critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
        }
    }
    return true;
}

bool Fs4Operations::PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    for (int i = 0; i < this->_fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        struct fs4_toc_info* itoc_info_p = &this->_fs4ImgInfo.itocArr.tocArr[i];
        struct image_layout_itoc_entry* toc_entry = &(itoc_info_p->toc_entry);
        if (IsCriticalSection(toc_entry->type))
        {
            critical.reserve(critical.size() + itoc_info_p->section_data.size());
            critical.insert(critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            // printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n", itoc_info_p->entry_addr,
            // itoc_info_p->toc_entry.type, (unsigned int)(itoc_info_p->section_data.size() + padding_size),
            // GetSectionNameByType(itoc_info_p->toc_entry.type));
        }
        else
        {
            if (itoc_info_p->toc_entry.type == FS4_RSA_4096_SIGNATURES || itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_512 || itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_256)
            {
                continue;
            }
            // printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n", itoc_info_p->entry_addr,
            // itoc_info_p->toc_entry.type, (unsigned int)itoc_info_p->section_data.size(),
            // GetSectionNameByType(itoc_info_p->toc_entry.type));
            non_critical.reserve(non_critical.size() + itoc_info_p->section_data.size());
            non_critical.insert(non_critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            // currentItoc++;
        }
    }
    return true;
}

bool Fs4Operations::getCriticalNonCriticalSections(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    if (!FsIntQueryAux(true, false))
    {
        return false;
    }
    for (int i = 0; i < this->_fs4ImgInfo.itocArr.numOfTocs; i++)
    {
        unsigned long padding_size = 0;
        struct fs4_toc_info* itoc_info_p = &this->_fs4ImgInfo.itocArr.tocArr[i];
        struct image_layout_itoc_entry* toc_entry = &(itoc_info_p->toc_entry);
        if (itoc_info_p->section_data.size() % GLOBAL_ALIGNMENT)
        {
            padding_size = GLOBAL_ALIGNMENT - (itoc_info_p->section_data.size() % GLOBAL_ALIGNMENT);
        }
        if (IsCriticalSection(toc_entry->type))
        {
            critical.reserve(critical.size() + itoc_info_p->section_data.size() + padding_size);
            critical.insert(critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            critical.insert(critical.end(), padding_size, 0xff);
            // printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n", itoc_info_p->entry_addr,
            // itoc_info_p->toc_entry.type, (unsigned int)(itoc_info_p->section_data.size() + padding_size),
            // GetSectionNameByType(itoc_info_p->toc_entry.type));
        }
        else
        {
            if (itoc_info_p->toc_entry.type == FS4_RSA_4096_SIGNATURES || itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_512 || itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_256)
            {
                continue;
            }
            // printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n",
            //         itoc_info_p->toc_entry.flash_addr*4, itoc_info_p->toc_entry.type,
            //         (unsigned int)itoc_info_p->section_data.size(),
            //         GetSectionNameByType(itoc_info_p->toc_entry.type));
            non_critical.reserve(non_critical.size() + itoc_info_p->section_data.size() + padding_size);
            non_critical.insert(non_critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            non_critical.insert(non_critical.end(), padding_size, 0xff);
            // currentItoc++;
        }
    }
    return true;
}

bool Fs4Operations::CalcHMAC(const vector<u_int8_t>& key, const vector<u_int8_t>& data, vector<u_int8_t>& digest)
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    MlxSignHMAC mlxSignHMAC;
    mlxSignHMAC.setKey(key);
    mlxSignHMAC << data;
    mlxSignHMAC.getDigest(digest);
    return true;
#else
    (void)key;
    (void)digest;
    (void)data;
    return errmsg("HMAC calculation is not implemented\n");
#endif
}

bool Fs4Operations::IsSecurityVersionViolated(u_int32_t image_security_version)
{
    // Set image security-version
    u_int32_t imageSecurityVersion = image_security_version;
    u_int32_t deviceEfuseSecurityVersion;

    if (getenv("FLINT_IGNORE_SECURITY_VERSION_CHECK") != NULL)
    {
        return false;
    }

    // Set device security-version (from EFUSEs)
    if (_fs3ImgInfo.ext_info.device_security_version_access_method == MFSV)
    {
        deviceEfuseSecurityVersion = _fs3ImgInfo.ext_info.device_security_version_mfsv.efuses_sec_ver;
    }
    else if (_fs3ImgInfo.ext_info.device_security_version_access_method == DIRECT_ACCESS)
    {
        deviceEfuseSecurityVersion = _fs3ImgInfo.ext_info.device_security_version_gw;
    }
    else
    {
        deviceEfuseSecurityVersion = 0;
    }

    // Check violation of security-version
    return (imageSecurityVersion < deviceEfuseSecurityVersion);
}

bool Fs4Operations::TocComp::operator()(fs4_toc_info* elem1, fs4_toc_info* elem2)
{
    u_int32_t absAddr1 = (elem1->toc_entry.flash_addr << 2) + _startAdd;
    u_int32_t absAddr2 = (elem2->toc_entry.flash_addr << 2) + _startAdd;
    if (absAddr1 < absAddr2)
    {
        return true;
    }
    return false;
}

u_int32_t Fs4Operations::TocArray::getSectionsTotalSize()
{
    u_int32_t s = 0;
    for (int i = 0; i < numOfTocs; i++)
    {
        struct fs4_toc_info* itoc_info_p = &(tocArr[i]);
        struct image_layout_itoc_entry* toc_entry = &itoc_info_p->toc_entry;
        s += toc_entry->size << 2;
    }
    return s;
}

void Fs4Operations::TocArray::initEmptyTocArrEntry(struct fs4_toc_info* tocArrEntry)
{
    if (!tocArrEntry)
    {
        return;
    }
    memset(tocArrEntry->data, 0, sizeof(tocArrEntry->data));
    memset(&tocArrEntry->toc_entry, 0, sizeof(tocArrEntry->toc_entry));
    tocArrEntry->entry_addr = 0;
    tocArrEntry->section_data.resize(0);
    return;
}

void Fs4Operations::TocArray::copyTocArrEntry(struct fs4_toc_info* dest, struct fs4_toc_info* src)
{
    if (!src || !dest)
    {
        return;
    }

    memcpy(dest->data, src->data, sizeof(src->data));
    dest->entry_addr = src->entry_addr;
    dest->section_data = src->section_data;
    memcpy(&dest->toc_entry, &src->toc_entry, sizeof(src->toc_entry));
    return;
}

Fs4Operations::TocArray::TocArray()
{
    numOfTocs = 0;
    tocArrayAddr = 0;
    for (int i = 0; i < MAX_TOCS_NUM; i++)
    {
        Fs4Operations::TocArray::initEmptyTocArrEntry(&tocArr[i]);
    }
    memset(&tocHeader, 0, sizeof(tocHeader));
}

Fs4Operations::HTOC::HTOC(vector<u_int8_t> img, u_int32_t htoc_start_addr, u_int32_t size)
{
    this->htoc_start_addr = htoc_start_addr;
    //* Parse header
    vector<u_int8_t> header_data(img.begin() + htoc_start_addr, img.begin() + htoc_start_addr + IMAGE_LAYOUT_HTOC_HEADER_SIZE);
    image_layout_htoc_header_unpack(&header, header_data.data());
    // image_layout_htoc_header_dump(&header, stdout);

    //* calculate num_of_entries from those equations
    //* htoc_size = HTOC__HEADER_SIZE + HTOC__ENTRY_SIZE * num_of_entries
    //* hashes_table_size = HASHES_TABLE__HEADER_SIZE + htoc_size + num_of_entries * header.hash_size +
    //* HASHES_TABLE__TAIL_SIZE
    htoc_max_num_of_entries = (size - HTOC__HEADER_SIZE - HASHES_TABLE__HEADER_SIZE - HASHES_TABLE__TAIL_SIZE) / (header.hash_size + HTOC__ENTRY_SIZE);

    entries = new image_layout_htoc_entry[htoc_max_num_of_entries];
    memset(entries, 0, htoc_max_num_of_entries * sizeof(image_layout_htoc_entry));
    //* Parse entries
    u_int32_t entries_start_addr = htoc_start_addr + IMAGE_LAYOUT_HTOC_HEADER_SIZE;
    for (int ii = 0; ii < header.num_of_entries; ii++)
    {
        u_int32_t entry_addr = entries_start_addr + ii * IMAGE_LAYOUT_HTOC_ENTRY_SIZE;
        vector<u_int8_t> entry_data(img.begin() + entry_addr, img.begin() + entry_addr + IMAGE_LAYOUT_HTOC_ENTRY_SIZE);
        image_layout_htoc_entry_unpack(&(entries[ii]), entry_data.data());
        // image_layout_htoc_entry_dump(&(entries[ii]), stdout);
    }
}

bool Fs4Operations::HTOC::AddNewEntry(FBase* ioAccess, fs3_section_t section_type, struct image_layout_htoc_entry& htoc_entry)
{
    DPRINTF(("Fs4Operations::HTOC::AddNewEntry htoc num_of_entries = %d\n", header.num_of_entries));
    if (header.num_of_entries == htoc_max_num_of_entries)
    {
        return false;
    }

    //* Preparing new htoc entry struct
    u_int32_t htoc_size = IMAGE_LAYOUT_HTOC_HEADER_SIZE + htoc_max_num_of_entries * IMAGE_LAYOUT_HTOC_ENTRY_SIZE;
    u_int32_t htoc_entry_index = header.num_of_entries;
    htoc_entry.hash_offset = htoc_size + (htoc_entry_index * header.hash_size);
    htoc_entry.section_type = section_type;

    //* Writing new htoc entry
    u_int32_t htoc_entry_addr = htoc_start_addr + IMAGE_LAYOUT_HTOC_HEADER_SIZE + htoc_entry_index * IMAGE_LAYOUT_HTOC_ENTRY_SIZE;
    vector<u_int8_t> htoc_entry_data;
    htoc_entry_data.resize(IMAGE_LAYOUT_HTOC_ENTRY_SIZE);
    image_layout_htoc_entry_pack(&htoc_entry, htoc_entry_data.data());
    DPRINTF(("Fs4Operations::HTOC::AddNewEntry Writing new htoc entry at addr 0x%x\n", htoc_entry_addr));
    if (!ioAccess->write(htoc_entry_addr, htoc_entry_data.data(), IMAGE_LAYOUT_HTOC_ENTRY_SIZE))
    {
        return false;
    }

    //* Updating and writing htoc header
    header.num_of_entries++;
    vector<u_int8_t> htoc_header_data;
    htoc_header_data.resize(IMAGE_LAYOUT_HTOC_HEADER_SIZE);
    image_layout_htoc_header_pack(&header, htoc_header_data.data());
    DPRINTF(("Fs4Operations::HTOC::AddNewEntry Writing updated htoc header at addr 0x%x\n", htoc_start_addr));
    if (!ioAccess->write(htoc_start_addr, htoc_header_data.data(), IMAGE_LAYOUT_HTOC_HEADER_SIZE))
    {
        return false;
    }

    return true;
}

bool Fs4Operations::HTOC::GetEntryBySectionType(fs3_section_t section_type, struct image_layout_htoc_entry& htoc_entry)
{
    bool res = false;
    for (int ii = 0; ii < header.num_of_entries; ii++)
    {
        if (entries[ii].section_type == section_type)
        {
            htoc_entry = entries[ii];
            res = true;
            break;
        }
    }
    return res;
}
