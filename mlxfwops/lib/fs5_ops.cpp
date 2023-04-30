/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "fs5_ops.h"
#include "calc_hw_crc.h"
#include "fs5_image_layout_layouts.h"

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
    _tools_ptr = hwPointers.tool2_ptr.ptr; // TODO - fix typo tool2 --> tools in gilboa adb
    _image_info_section_ptr = hwPointers.image_info_ptr.ptr;
    _hashes_table_ptr = hwPointers.ncore_hashes_ptr.ptr;
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
    // Below commented out at the moment, if needed just remove and inherit it from fs4_ops
    // fw_info_t fwInfo;
    // if (!FwQuery(&fwInfo, false, false, false))
    // {
    //     return false;
    // }
    return true;
}

bool Fs5Operations::GetImageSize(u_int32_t* image_size)
{
    if (!GetImageSizeFromImageInfo(image_size))
    {
        return false;
    }
    return true;
}

bool Fs5Operations::CheckBoot2(u_int32_t offs, bool fullRead, const char* pref, VerifyCallBack verifyCallBackFunc)
{
    DPRINTF(("FwOperations::CheckBoot2\n"));
    char* pr = new char[strlen(pref) + 512];
    sprintf(pr, "%s /0x%08x/ (BOOT2)", pref, offs);

    // Parse boot2 header
    vector<u_int8_t> boot2HeaderData(FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE);
    if (!_ioAccess->read(offs, boot2HeaderData.data(), FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE))
    {
        return errmsg("%s - read error (%s)\n", "FS5 boot2 header", _ioAccess->err());
    }
    // TODO - verify boot2 header CRC

    fs5_image_layout_boot2_header_gilboa boot2Header;
    fs5_image_layout_boot2_header_gilboa_unpack(&boot2Header, boot2HeaderData.data());
    DPRINTF(("FwOperations::CheckBoot2 size = 0x%x\n", boot2Header.dw_size));
    if (boot2Header.dw_size > 1048576 || boot2Header.dw_size < 4)
    {
        report_callback(verifyCallBackFunc, "%s /0x%08x/ - unexpected size (0x%x)\n", pr, offs + 4,
                        boot2Header.dw_size);
        delete[] pr;
        return errmsg("Boot2 invalid size\n");
    }
    _fwImgInfo.boot2Size =
      FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE + (boot2Header.dw_size * 4) + 4; // header + payload + crc

    u_int32_t boot2AbsAddr = _fwImgInfo.imgStart + offs;
    sprintf(pr, "%s /0x%08x-0x%08x (0x%06x)/ (BOOT2)", pref, boot2AbsAddr, boot2AbsAddr + _fwImgInfo.boot2Size - 1,
            _fwImgInfo.boot2Size);

    if (fullRead == true || !_ioAccess->is_flash())
    {
        u_int32_t boot2SizeInDW = _fwImgInfo.boot2Size / 4;
        u_int32_t* buff = new u_int32_t[boot2SizeInDW];
        memset(buff, 0, (boot2SizeInDW) * sizeof(u_int32_t));
        bool rc = readBufAux((*_ioAccess), offs, buff, _fwImgInfo.boot2Size, pr);
        if (!rc)
        {
            delete[] pr;
            delete[] buff;
            return rc;
        }
        UpdateImgCache((u_int8_t*)buff, offs, _fwImgInfo.boot2Size);

        u_int32_t crc_calc =
          calc_hw_crc((u_int8_t*)buff + FS5_IMAGE_LAYOUT_BOOT2_HEADER_GILBOA_SIZE, boot2Header.dw_size * 4);
        TOCPUn(buff, boot2SizeInDW);
        u_int32_t crc_act = buff[boot2SizeInDW - 1];
        delete[] buff;
        if (crc_calc != crc_act)
        {
            DPRINTF(("FwOperations::CheckBoot2 wrong CRC (exp:0x%x, act:0x%x)\n", crc_calc, crc_act));
            report_callback(verifyCallBackFunc, "%s /0x%08x/ - wrong CRC (exp:0x%x, act:0x%x)\n", pr, offs, crc_calc,
                            crc_act);
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
    return CheckBoot2(offs, fullRead, pref, verifyCallBackFunc);
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
    return encryptedFwQuery(fwInfo, quickQuery, ignoreDToc, verbose);
}
