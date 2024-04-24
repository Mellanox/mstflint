/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#include "fs5_ops.h"
#include "calc_hw_crc.h"
#include "fs5_image_layout_layouts.h"

const u_int32_t Fs5Operations::BCH_SIZE_IN_BYTES = 0x2000;

u_int8_t Fs5Operations::FwType()
{
    return FIT_FS5;
}

bool Fs5Operations::ParseHwPointers(VerifyCallBack verifyCallBackFunc)
{
    DPRINTF(("Fs5Operations::ParseHwPointers\n"));

    u_int32_t buff[FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE / 4] = {0};
    fs5_image_layout_hw_pointers_gilboa hwPointers;
    u_int32_t hwPointersAddr = _fwImgInfo.imgStart + FS4_HW_PTR_START;
    if (!_ioAccess->read(hwPointersAddr, buff, FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE))
    {
        return errmsg("%s - read error (%s)\n", "FS5 HW Pointers", _ioAccess->err());
    }

    // Fix pointers that are 0xFFFFFFFF
    for (unsigned int k = 0; k < FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE / 4; k += 2)
    {
        if (buff[k] == 0xFFFFFFFF)
        {
            buff[k] = 0;     // Fix pointer
            buff[k + 1] = 0; // Fix CRC
        }
    }
    for (unsigned int k = 0; k < FS5_IMAGE_LAYOUT_HW_POINTERS_GILBOA_SIZE / 4; k += 2)
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
        if (!DumpFs3CRCCheck(FS4_HW_PTR, hwPointersAddr + 4 * k, FS5_IMAGE_LAYOUT_HW_POINTER_ENTRY_SIZE, calcPtrCRC,
                             ptrCRC, false, verifyCallBackFunc))
        {
            return false;
        }
    }

    fs5_image_layout_hw_pointers_gilboa_unpack(&hwPointers, (u_int8_t*)buff);
    _boot2_ptr = hwPointers.boot2_ptr.ptr;
    _itoc_ptr = hwPointers.toc_ptr.ptr;
    _tools_ptr = hwPointers.tools_ptr.ptr;
    _image_info_section_ptr = hwPointers.image_info_section_pointer.ptr;
    _hashes_table_ptr = hwPointers.ncore_hashes_pointer.ptr;
    _ncore_bch_ptr = hwPointers.ncore_bch_pointer.ptr;
    _is_hw_ptrs_initialized = true;
    return true;
}

bool Fs5Operations::InitHwPtrs(bool)
{
    if (!_is_hw_ptrs_initialized)
    {
        DPRINTF(("Fs5Operations::InitHwPtrs\n"));
        if (!getImgStart())
        { // Set _fwImgInfo.imgStart with the image start address
            return false;
        }

        if (!ParseHwPointers((VerifyCallBack)NULL))
        {
            return errmsg("Fs5Operations::InitHwPtrs: ParseHwPointers failed - Error: %s.\n", err());
        }
    }
    return true;
}

bool Fs5Operations::Init()
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

bool Fs5Operations::GetImageInfo(u_int8_t* buff)
{
    DPRINTF(("Fs5Operations::GetImageInfo call Fs3Operations::GetImageInfo\n"));
    return Fs3Operations::GetImageInfo(buff);
}

bool Fs5Operations::GetImageSize(u_int32_t* image_size)
{
    if (!GetEncryptedImageSizeFromImageInfo(image_size))
    {
        return false;
    }
    return true;
}

bool Fs5Operations::CheckBoot2(bool fullRead, const char* pref, VerifyCallBack verifyCallBackFunc)
{
    DPRINTF(("FwOperations::CheckBoot2\n"));
    char* pr = new char[strlen(pref) + 512];
    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, _boot2_ptr);

    // Parse NCORE BCH for boot2 size
    vector<u_int8_t> ncoreBCHData(FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE);
    if (!_ioAccess->read(_ncore_bch_ptr, ncoreBCHData.data(), FS5_IMAGE_LAYOUT_BOOT_COMPONENT_HEADER_SIZE))
    {
        delete[] pr;
        return errmsg("%s - read error (%s)\n", "FS5 boot2 header", _ioAccess->err());
    }
    fs5_image_layout_boot_component_header ncoreBCH;
    fs5_image_layout_boot_component_header_unpack(&ncoreBCH, ncoreBCHData.data());
    
    u_int32_t hashes_table_size = 0;
    if (!GetHashesTableSize(hashes_table_size))
    {
        return false;
    }
    _fwImgInfo.boot2Size = ncoreBCH.u8_stage1_component.u32_binary_len - hashes_table_size;

    DPRINTF(("FwOperations::CheckBoot2 size = 0x%x\n", _fwImgInfo.boot2Size));
    if (_fwImgInfo.boot2Size > 1048576 || _fwImgInfo.boot2Size < 4)
    {
        report_callback(verifyCallBackFunc, "%s - unexpected size (0x%x)\n", pr, _fwImgInfo.boot2Size);
        delete[] pr;
        return errmsg("Boot2 invalid size\n");
    }

    u_int32_t boot2AbsAddr = _fwImgInfo.imgStart + _boot2_ptr;
    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, boot2AbsAddr, boot2AbsAddr + _fwImgInfo.boot2Size - 1,
            _fwImgInfo.boot2Size);

    if (fullRead == true || !_ioAccess->is_flash())
    {
        u_int32_t boot2SizeInDW = _fwImgInfo.boot2Size / 4;
        u_int32_t* buff = new u_int32_t[boot2SizeInDW];
        memset(buff, 0, (boot2SizeInDW) * sizeof(u_int32_t));
        bool rc = readBufAux((*_ioAccess), _boot2_ptr, buff, _fwImgInfo.boot2Size, pr);
        if (!rc)
        {
            delete[] pr;
            delete[] buff;
            return rc;
        }
        UpdateImgCache((u_int8_t*)buff, _boot2_ptr, _fwImgInfo.boot2Size);
        delete[] buff;
        report_callback(verifyCallBackFunc, "%s - CRC IGNORED\n", pr);
    }
    delete[] pr;
    return true;
}

bool Fs5Operations::CheckBoot2(u_int32_t,
                               u_int32_t offs,
                               u_int32_t&,
                               bool fullRead,
                               const char* pref,
                               VerifyCallBack verifyCallBackFunc)
{
    return CheckBoot2(fullRead, pref, verifyCallBackFunc);
}

bool Fs5Operations::FsVerifyAux(VerifyCallBack verifyCallBackFunc,
                                bool show_itoc,
                                struct QueryOptions queryOptions,
                                bool ignoreDToc,
                                bool verbose)
{
    DPRINTF(("Fs5Operations::FsVerifyAux\n"));
    u_int8_t* buff;
    u_int32_t log2_chunk_size;
    bool is_image_in_odd_chunks;

    DPRINTF(("Fs5Operations::FsVerifyAux call getImgStart()\n"));
    if (!getImgStart())
    { // Set _fwImgInfo.imgStart with the image start address
        return false;
    }

    report_callback(verifyCallBackFunc, "\nFS5 failsafe image\n\n");

    _ioAccess->set_address_convertor(0, 0);
    DPRINTF(("Fs5Operations::FsVerifyAux call ParseHwPointers()\n"));
    if (!ParseHwPointers(verifyCallBackFunc))
    {
        return false;
    }

    // if nextBootFwVer is true, no need to get all the information, just the fw version is enough - therefore skip
    // everything else
    if (!nextBootFwVer)
    {
        DPRINTF(("Fs5Operations::FsVerifyAux call verifyToolsArea()\n"));
        if (!verifyToolsArea(verifyCallBackFunc))
        {
            return false;
        }

        // Update image cache till before boot2 header:
        DPRINTF(("Fs5Operations::FsVerifyAux call Fs3UpdateImgCache() - All before boot2\n"));
        READALLOCBUF((*_ioAccess), _fwImgInfo.imgStart, buff, _boot2_ptr, "All Before Boot2");
        Fs3UpdateImgCache(buff, 0, _boot2_ptr);
        free(buff);

        _ioAccess->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, _fwImgInfo.imgStart != 0);

        // Get BOOT2 -Get Only boot2Size if quickQuery == true else read and check CRC of boot2 section as well
        DPRINTF(("Fs5Operations::FsVerifyAux call FS3_CHECKB2()\n"));
        FS3_CHECKB2(0, _boot2_ptr, !queryOptions.quickQuery, PRE_CRC_OUTPUT, verifyCallBackFunc);

        _fs4ImgInfo.firstItocArrayIsEmpty = false;
        _fs4ImgInfo.itocArr.tocArrayAddr = _itoc_ptr;

        DPRINTF(("Fs5Operations::FsVerifyAux call isHashesTableHwPtrValid()\n"));
        if (isHashesTableHwPtrValid())
        {
            //* Check hashes_table header CRC
            READALLOCBUF((*_ioAccess), _hashes_table_ptr, buff, IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE,
                         "HASHES TABLE HEADER");
            // Calculate CRC
            u_int32_t hashes_table_header_calc_crc =
              CalcImageCRC((u_int32_t*)buff, (IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE / 4) - 1);
            // Read CRC
            u_int32_t hashes_table_header_crc = ((u_int32_t*)buff)[(IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE / 4) - 1];
            free(buff);
            TOCPU1(hashes_table_header_crc)
            hashes_table_header_crc = hashes_table_header_crc & 0xFFFF;
            // Compare calculated crc with crc from image
            if (hashes_table_header_calc_crc != hashes_table_header_crc)
            {
                report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n",
                                "HASHES TABLE HEADER", _hashes_table_ptr + IMAGE_LAYOUT_HASHES_TABLE_HEADER_SIZE - 4,
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
            if (!DumpFs3CRCCheck(FS4_HASHES_TABLE, _hashes_table_ptr, hashes_table_size, hashes_table_calc_crc,
                                 hashes_table_crc, false, verifyCallBackFunc))
            {
                return false;
            }
        }

        DPRINTF(("Fs5Operations::FsVerifyAux call verifyTocHeader() ITOC\n"));
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
    DPRINTF(("Fs5Operations::FsVerifyAux call verifyTocEntries() ITOC\n"));
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
    u_int32_t dtocPtr = _ioAccess->get_effective_size() - FS4_DEFAULT_SECTOR_SIZE;
    if (!GetDtocAddress(dtocPtr))
    {
        return false;
    }
    DPRINTF(("Fs5Operations::FsVerifyAux call verifyTocHeader() DTOC\n"));
    if (!verifyTocHeader(dtocPtr, true, verifyCallBackFunc))
    {
        return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid DTOC Header was found.");
    }
    _fs4ImgInfo.dtocArr.tocArrayAddr = dtocPtr;
    //-Verify DToC Entries:
    DPRINTF(("Fs5Operations::FsVerifyAux call verifyTocEntries() DTOC\n"));
    if (!verifyTocEntries(dtocPtr, show_itoc, true, queryOptions, verifyCallBackFunc, verbose))
    {
        _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
        return false;
    }
    _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
    return true;
}

bool Fs5Operations::FwQuery(fw_info_t* fwInfo, bool, bool, bool quickQuery, bool ignoreDToc, bool verbose)
{
    DPRINTF(("Fs5Operations::FwQuery\n"));
    if (!encryptedFwQuery(fwInfo, quickQuery, ignoreDToc, verbose))
    {
        return errmsg("%s", err());
    }

    return NCoreQuery(fwInfo);
}

bool Fs5Operations::NCoreQuery(fw_info_t* fwInfo)
{
    fs5_image_layout_boot_component_header ncoreBCH;
    memset(&ncoreBCH, 0, sizeof(ncoreBCH));

    vector<u_int8_t> ncoreData(BCH_SIZE_IN_BYTES);
    if (!_ioAccess->read(_ncore_bch_ptr, ncoreData.data(), BCH_SIZE_IN_BYTES))
    {
        return errmsg("FS5 NCORE - read error (%s)\n", _ioAccess->err());
    }
    TOCPUn(ncoreData.data(), BCH_SIZE_IN_BYTES / 4);
    fs5_image_layout_boot_component_header_unpack(&ncoreBCH, ncoreData.data());

    fwInfo->fs3_info.security_mode &= ~SMM_DEBUG_FW;
    fwInfo->fs3_info.security_mode |= (ncoreBCH.u8_stage1_component.flags.is_debug == 1) ? SMM_DEBUG_FW : 0;
    fwInfo->fw_info.encrypted_fw = ncoreBCH.u8_stage1_component.flags.is_encrypted ? 2 : 0;

    return true;
}

bool Fs5Operations::FwExtract4MBImage(vector<u_int8_t>& img,
                                      bool maskMagicPatternAndDevToc,
                                      bool verbose,
                                      bool ignoreImageStart)
{
    bool res = Fs4Operations::FwExtract4MBImage(img, maskMagicPatternAndDevToc, verbose, ignoreImageStart);

    if (res)
    {
        //* Get image size
        u_int32_t burn_image_size;
        if (!GetEncryptedImageSizeFromImageInfo(&burn_image_size))
        {
            return errmsg("%s", err());
        }

        vector<u_int8_t> bch(BCH_SIZE_IN_BYTES + 1, 0);
        if (!_ioAccess->read(burn_image_size, bch.data(), BCH_SIZE_IN_BYTES))
        {
            return errmsg("Image - read error (%s)\n", _ioAccess->err());
        }

        string magicPattern(reinterpret_cast<const char*>(bch.data()), 4);
        if (magicPattern == "NVDA")
        {
            img.resize(img.size() + BCH_SIZE_IN_BYTES);

            std::copy(begin(bch), end(bch), begin(img) + burn_image_size);
        }
    }

    return res;
}

bool Fs5Operations::GetDtocAddress(u_int32_t& dTocAddress)
{
    ParseImageInfoFromEncryptedImage();
    u_int32_t imageSize = _ioAccess->get_effective_size();
    bool isSigned = false;

    if (!IsSecureFwUpdateSigned(isSigned))
    {
        return false;
    }

    if (isSigned)
    {
        imageSize -= BCH_SIZE_IN_BYTES;
    }

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

bool Fs5Operations::IsSecureFwUpdateSigned(bool& isSigned)
{
    u_int32_t imageSize = _ioAccess->get_effective_size();
    const u_int32_t smallestSupportedImageSize = 0x40000;

    if ((imageSize % smallestSupportedImageSize) != 0) // Check if there's an encapsulation header
    {
        vector<u_int8_t> bchHeaderMagic(5, 0);
        u_int32_t log2_chunk_size = _ioAccess->get_log2_chunk_size();
        bool is_image_in_odd_chunks = _ioAccess->get_is_image_in_odd_chunks();

        _ioAccess->set_address_convertor(0, 0);
        if (!_ioAccess->read(imageSize - BCH_SIZE_IN_BYTES, bchHeaderMagic.data(), 4))
        {
            return errmsg("Image - read error (%s)\n", _ioAccess->err());
        }
        _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);

        if (string(reinterpret_cast<const char*>(bchHeaderMagic.data())) == "NVDA")
        {
            isSigned = true;
        }
        else
        {
            isSigned = false;
        }
    }

    return true;
}

bool Fs5Operations::GetMfgInfo(u_int8_t* buff)
{
    bool rc = Fs4Operations::GetMfgInfo(buff);
    if (rc != false)
    {
        if (_fwImgInfo.supportedHwId[0] == ARCUSE_HW_ID)
        { // ArcusE is missing DEV_INFO section, align non-orig guids to make flint query output correct format
            memcpy(&_fs3ImgInfo.ext_info.fs3_uids_info.image_layout_uids,
                   &_fs3ImgInfo.ext_info.orig_fs3_uids_info.image_layout_uids,
                   sizeof(_fs3ImgInfo.ext_info.orig_fs3_uids_info.image_layout_uids));
            _fs3ImgInfo.ext_info.fs3_uids_info.guid_format = IMAGE_LAYOUT_UIDS;
        }
    }
    return rc;
}