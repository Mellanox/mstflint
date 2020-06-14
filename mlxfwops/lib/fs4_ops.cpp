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
#include <algorithm>
#include <vector>

#include <cstring>
#include <tools_utils.h>
#include <bit_slice.h>
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
#endif //NO_CS_CMD
#if !defined(NO_OPEN_SSL)
#include <mlxsign_lib/mlxsign_lib.h>
#endif //NO_OPEN_SSL
#endif //UEFI_BUILD

#include "fs4_ops.h"
#include "fs3_ops.h"

#define DEV_INFO_SIG0 0x6d446576
#define DEV_INFO_SIG1 0x496e666f
#define DEV_INFO_SIG2 0x2342cafa
#define DEV_INFO_SIG3 0xbacafe00

#define DEFAULT_GUID_NUM 0xff
#define DEFAULT_STEP DEFAULT_GUID_NUM

#define GUID_TO_64(guid_st) \
    (guid_st.l | (u_int64_t)guid_st.h << 32)

#define CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP() \
    if (!_ioAccess->is_flash()) { \
        return errmsg( \
            "Timestamp operation for FS4 FW image files is not supported"); \
    }

#define COUNT_OF_SECTIONS_TO_ALIGN 5

bool Fs4Operations::CheckSignatures(u_int32_t a[], u_int32_t b[], int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            //printf("-D- a[%d]=%d b[%d]=%d", i, a[i], i, b[i]);
            return false;
        }
    }
    return true;
}

bool Fs4Operations::CheckTocSignature(struct cx5fw_itoc_header *itoc_header, u_int32_t first_signature)
{
    u_int32_t a[4] = {itoc_header->signature0, itoc_header->signature1,
                      itoc_header->signature2, itoc_header->signature3};
    u_int32_t b[4] = {first_signature, TOC_RAND1, TOC_RAND2, TOC_RAND3};
    return CheckSignatures(a, b, 4);
}

bool Fs4Operations::CheckDevInfoSignature(u_int32_t *buff)
{
    u_int32_t sig0 = buff[0], sig1 = buff[1], sig2 = buff[2], sig3 = buff[3];
    TOCPU1(sig0);
    TOCPU1(sig1);
    TOCPU1(sig2);
    TOCPU1(sig3);
    u_int32_t a[4] = {sig0, sig1, sig2, sig3};
    u_int32_t b[4] = {DEV_INFO_SIG0, DEV_INFO_SIG1, DEV_INFO_SIG2, DEV_INFO_SIG3};
    //printf("sig0=%x sig1=%x sig2=%x sig3=%x\n", sig0, sig1, sig2, sig3);
    return CheckSignatures(a, b, 4);
}

//CodeView: move it to Base class
bool Fs4Operations::getImgStart()
{

    u_int32_t cntx_image_start[CNTX_START_POS_SIZE] = {0};
    u_int32_t cntx_image_num = 0;

    FindAllImageStart(_ioAccess, cntx_image_start,
                      &cntx_image_num, _fs4_magic_pattern);

    if (cntx_image_num == 0) {
        return errmsg(MLXFW_NO_VALID_IMAGE_ERR,
                      "No valid FS4 image found");
    }
    if (cntx_image_num > 1) {
        return errmsg(MLXFW_MULTIPLE_VALID_IMAGES_ERR,
                      "More than one FS4 image found on %s",
                      this->_ioAccess->is_flash() ? "Device" : "image");
    }

    _fwImgInfo.imgStart = cntx_image_start[0];

    return true;
}

//CodeView: add HW pointers to verify output
bool Fs4Operations::getHWPtrs(VerifyCallBack verifyCallBackFunc)
{

    u_int32_t buff[FS4_HW_PTR_SIZE_DW];
    struct cx5fw_hw_pointers hw_pointers;
    u_int32_t physAddr = _fwImgInfo.imgStart + FS4_HW_PTR_START;

    READBUF((*_ioAccess),
            physAddr,
            buff,
            CX5FW_HW_POINTERS_SIZE,
            "HW Pointers");
    cx5fw_hw_pointers_unpack(&hw_pointers, (u_int8_t *)buff);

    //- Check CRC of each pointers (always check CRC before you call ToCPU
    for (int k = 0; k < FS4_HW_PTR_SIZE_DW; k += 2) {
        u_int32_t *tempBuff = (u_int32_t *) buff;
        //Calculate HW CRC:
        u_int32_t calcPtrCRC = calc_hw_crc((u_int8_t *)((u_int32_t *)tempBuff + k), 6);
        u_int32_t ptrCRC = tempBuff[k + 1];
        u_int32_t ptr = tempBuff[k];
        TOCPUn(&ptr, 1);
        TOCPUn(&ptrCRC, 1);
        if (!DumpFs3CRCCheck(FS4_HW_PTR, physAddr + 4 * k, CX5FW_HW_POINTER_ENTRY_SIZE, calcPtrCRC,
                             ptrCRC, false, verifyCallBackFunc)) {
            return false;
        }
    }

    //CodeView: generate tools_layout
    _boot2_ptr = hw_pointers.boot2_ptr.ptr;
    _itoc_ptr = hw_pointers.toc_ptr.ptr;
    _tools_ptr = hw_pointers.tools_ptr.ptr;

    /*printf("-D-boot2_ptr=0x%x\n", _boot2_ptr);
       printf("-D-itoc_ptr=0x%x\n", _itoc_ptr);
       printf("-D-tools_ptr=0x%x\n", _tools_ptr);*/

    return true;
}

bool Fs4Operations::getExtendedHWPtrs(VerifyCallBack verifyCallBackFunc, FBase* ioAccess, bool IsBurningProcess)
{

    //TODO
    //printf("1=0x%x 2=0x%x\n", _fwImgInfo.supportedHwId[0], CX6_HW_ID);
    /*if (_fwImgInfo.supportedHwId[0] != CX6_HW_ID) {
        return errmsg("Extended HW pointers are only for ConnectX-6\n");
    }*/

    const unsigned int s = CX6FW_HW_POINTERS_SIZE / 4;
    u_int32_t buff[s];
    struct cx6fw_hw_pointers hw_pointers;
    u_int32_t physAddr = FS4_HW_PTR_START;
    if (!IsBurningProcess) {
        physAddr += _fwImgInfo.imgStart;
    }

    READBUF((*ioAccess),
            physAddr,
            buff,
            CX6FW_HW_POINTERS_SIZE,
            "HW Pointers");
    cx6fw_hw_pointers_unpack(&hw_pointers, (u_int8_t *)buff);

    //- Check CRC of each pointers (always check CRC before you call ToCPU
    for (unsigned int k = 0; k < s; k += 2) {
        u_int32_t *tempBuff = (u_int32_t *) buff;
        //Calculate HW CRC:
        u_int32_t calcPtrCRC = calc_hw_crc((u_int8_t *)((u_int32_t *)tempBuff + k), 6);
        u_int32_t ptrCRC = tempBuff[k + 1];
        u_int32_t ptr = tempBuff[k];
        TOCPUn(&ptr, 1);
        TOCPUn(&ptrCRC, 1);
        if (!DumpFs3CRCCheck(FS4_HW_PTR, physAddr + 4 * k, CX6FW_HW_POINTER_ENTRY_SIZE, calcPtrCRC,
                             ptrCRC, false, verifyCallBackFunc)) {
            return false;
        }
    }

    //CodeView: generate tools_layout
    _boot2_ptr = hw_pointers.boot2_ptr.ptr;
    _itoc_ptr = hw_pointers.toc_ptr.ptr;
    _tools_ptr = hw_pointers.tools_ptr.ptr;

    _authentication_start_ptr = hw_pointers.authentication_start_ptr.ptr;
    _authentication_end_ptr = hw_pointers.authentication_end_ptr.ptr;
    _digest_mdk_ptr = hw_pointers.digest_mdk_ptr.ptr;
    _digest_recovery_key_ptr = hw_pointers.digest_recovery_key_ptr.ptr;

    return true;
}

bool Fs4Operations::verifyToolsArea(VerifyCallBack verifyCallBackFunc)
{

    u_int32_t buff[CX5FW_TOOLS_AREA_SIZE / 4];
    u_int8_t binVerMajor = 0;
    u_int8_t binVerMinor = 0;
    u_int32_t calculatedToolsAreaCRC;
    u_int32_t toolsAreaCRC;
    u_int32_t physAddr = _fwImgInfo.imgStart + _tools_ptr;
    struct cx5fw_tools_area tools_area;

    READBUF((*_ioAccess), physAddr, buff, CX5FW_TOOLS_AREA_SIZE, "Tools Area");
    cx5fw_tools_area_unpack(&tools_area, (u_int8_t *)buff);

    binVerMinor = tools_area.bin_ver_minor;
    binVerMajor = tools_area.bin_ver_major;
    _maxImgLog2Size = tools_area.log2_img_slot_size;
    toolsAreaCRC = tools_area.crc;

    calculatedToolsAreaCRC = CalcImageCRC((u_int32_t *)buff, CX5FW_TOOLS_AREA_SIZE / 4 - 1);

    if (!DumpFs3CRCCheck(FS4_TOOLS_AREA, physAddr, CX5FW_TOOLS_AREA_SIZE, calculatedToolsAreaCRC,
                         toolsAreaCRC, false, verifyCallBackFunc)) {
        return false;
    }

    /*printf("-D- Bin Ver Minor=%d\n", binVerMinor);
       printf("-D- Bin Ver Major=%d\n", binVerMajor);
       printf("-D- _maxImgLog2Size=%d\n", _maxImgLog2Size);
       printf("-D- Actuall tools area CRC=%d\n", toolsAreaCRC);
       printf("-D- Expected tools area CRC=%d\n", calculatedToolsAreaCRC);*/

    //- Check if binary version is supported by the tool
    if (!CheckBinVersion(binVerMajor, binVerMinor)) {
        return false;
    }

    //Put info
    if (_maxImgLog2Size == 0x16 && _fwImgInfo.imgStart == 0x800000) {
        _fwImgInfo.cntxLog2ChunkSize = 0x17;
    } else {
        _fwImgInfo.cntxLog2ChunkSize = _maxImgLog2Size;
    }
    _fwImgInfo.ext_info.is_failsafe = true;
    _fwImgInfo.actuallyFailsafe  = true;
    _fwImgInfo.magicPatternFound = 1;

    return true;
}

bool Fs4Operations::verifyTocHeader(u_int32_t tocAddr, bool isDtoc, VerifyCallBack verifyCallBackFunc)
{

    struct cx5fw_itoc_header itocHeader;
    u_int8_t buffer[TOC_HEADER_SIZE];
    u_int32_t physAddr;
    u_int32_t tocCrc;

    /*if(isDtoc) {
        _ioAccess->set_address_convertor(0, 0);
       }*/

    READBUF((*_ioAccess), tocAddr, buffer, TOC_HEADER_SIZE, "TOC Header");
    Fs3UpdateImgCache(buffer, tocAddr, TOC_HEADER_SIZE);
    cx5fw_itoc_header_unpack(&itocHeader, buffer);
    //TODO: check if we really need this:
    if (isDtoc) {
        memcpy(_fs4ImgInfo.dtocArr.tocHeader, buffer, CX5FW_ITOC_HEADER_SIZE);
    } else {
        memcpy(_fs4ImgInfo.itocArr.tocHeader, buffer, CX5FW_ITOC_HEADER_SIZE);
    }

    // Check the signature in the header:
    u_int32_t first_signature =   isDtoc ? DTOC_ASCII : ITOC_ASCII;
    if (!CheckTocSignature(&itocHeader, first_signature)) {
        return false;
    }

    tocCrc = CalcImageCRC((u_int32_t *)buffer, (TOC_HEADER_SIZE / 4) - 1);
    physAddr = _ioAccess->get_phys_from_cont(
        tocAddr,
        isDtoc ? 0 : _fwImgInfo.cntxLog2ChunkSize,
        _fwImgInfo.imgStart != 0);

    if (!DumpFs3CRCCheck(isDtoc ? FS3_DTOC : FS3_ITOC, physAddr, TOC_HEADER_SIZE, tocCrc,
                         itocHeader.itoc_entry_crc, false, verifyCallBackFunc)) {
        return false;
    }

    return true;
}

bool Fs4Operations::verifyTocEntries(u_int32_t tocAddr, bool show_itoc, bool isDtoc,
                                     struct QueryOptions queryOptions, VerifyCallBack verifyCallBackFunc, bool verbose)
{

    struct cx5fw_itoc_entry tocEntry;
    int section_index = 0;
    u_int32_t entryAddr;
    u_int32_t entryCrc;
    u_int32_t entrySizeInBytes;
    u_int32_t physAddr;
    u_int8_t entryBuffer[TOC_ENTRY_SIZE];
    bool mfgExists = false;
    int validDevInfoCount = 0;
    bool retVal = true;
    TocArray *tocArray;

    if (isDtoc) {
        tocArray = &(_fs4ImgInfo.dtocArr);
    } else {
        tocArray = &(_fs4ImgInfo.itocArr);
    }

    do {
        // Read toc entry
        if (nextBootFwVer) {
            // if nextBootFwVer is true, read only fw version (FS3_IMAGE_INFO section)
            // section index should be 8 for this case
            section_index = 8;
        }
        entryAddr = tocAddr + TOC_HEADER_SIZE + section_index *  TOC_ENTRY_SIZE;
        if (!verbose) {
        READBUF((*_ioAccess), entryAddr, entryBuffer, TOC_ENTRY_SIZE, "TOC Entry");
        }
        else {
            if (!(*_ioAccess).read(entryAddr, entryBuffer, TOC_ENTRY_SIZE, true)) {
                return errmsg("%s - read error (%s)\n", "TOC Entry", (*_ioAccess).err());
            }
        }
        Fs3UpdateImgCache(entryBuffer, entryAddr, TOC_ENTRY_SIZE);
        cx5fw_itoc_entry_unpack(&tocEntry, entryBuffer);

        if (tocEntry.type == FS3_MFG_INFO) {
            mfgExists = true;
        }

        if (tocEntry.type != FS3_END) {

            if (section_index + 1 >= MAX_TOCS_NUM) {
                return errmsg(
                    "Internal error: number of %s %d is greater than allowed %d",
                    isDtoc ? "DTocs" : "ITocs",
                    section_index + 1,
                    MAX_TOCS_NUM);
            }

            entryCrc = CalcImageCRC((u_int32_t *)entryBuffer, (TOC_ENTRY_SIZE / 4) - 1);
            if (tocEntry.itoc_entry_crc != entryCrc) {
                return errmsg(
                    MLXFW_BAD_CRC_ERR, "Bad %s Entry CRC. Expected: 0x%x , Actual: 0x%x",
                    isDtoc ? "DToc" : "IToc",
                    tocEntry.itoc_entry_crc,
                    entryCrc);
            }

            entrySizeInBytes = tocEntry.size * 4;

            // Update last image address
            u_int32_t section_last_addr;
            u_int32_t flash_addr = tocEntry.flash_addr << 2;
            if (isDtoc) {
                physAddr = flash_addr;
                _fs4ImgInfo.smallestDTocAddr =
                    (_fs4ImgInfo.smallestDTocAddr < flash_addr && _fs4ImgInfo.smallestDTocAddr > 0)
                    ? _fs4ImgInfo.smallestDTocAddr : flash_addr;
            } else {
                physAddr = _ioAccess->get_phys_from_cont(flash_addr,
                                                         _fwImgInfo.cntxLog2ChunkSize,
                                                         _fwImgInfo.imgStart != 0);
                section_last_addr = physAddr + entrySizeInBytes;
                _fwImgInfo.lastImageAddr =
                    (_fwImgInfo.lastImageAddr >= section_last_addr) ?
                    _fwImgInfo.lastImageAddr : section_last_addr;
            }

            if (IsFs3SectionReadable(tocEntry.type, queryOptions)) {

                // Only when we have full verify or the info of this section should be collected for query
                std::vector<u_int8_t> buffv(entrySizeInBytes);
                u_int8_t *buff = (u_int8_t *)(buffv.size() ? (&(buffv[0])) : NULL);

                if (show_itoc) {
                    cx5fw_itoc_entry_dump(&tocEntry, stdout);
                    if (!DumpFs3CRCCheck(tocEntry.type, physAddr, entrySizeInBytes, 0,
                                         0, true, verifyCallBackFunc)) {
                        retVal = false;
                    }
                } else {
                    if (!verbose) {
                    READBUF((*_ioAccess), flash_addr, buff, entrySizeInBytes, "Section");
                    }
                    else {
                        if (!(*_ioAccess).read(flash_addr, buff, entrySizeInBytes, true)) {
                            return errmsg("%s - read error (%s)\n", "Section", (*_ioAccess).err());
                        }
                    }
                    Fs3UpdateImgCache(buff, flash_addr, entrySizeInBytes);
                    u_int32_t sect_act_crc = 0;
                    u_int32_t sect_exp_crc = 0;
                    if (tocEntry.crc == INITOCENTRY) {
                        //crc is in the itoc entry
                        sect_act_crc = CalcImageCRC((u_int32_t *)buff, tocEntry.size);
                        sect_exp_crc = tocEntry.section_crc;
                        //printf("-D-INITOCENTRY sect_act_crc=%d sect_exp_crc=%d\n", sect_act_crc, sect_exp_crc);
                    } else if (tocEntry.crc == INSECTION) {
                        //calc crc on the section without the last dw which contains crc
                        sect_act_crc = CalcImageCRC((u_int32_t *)buff, tocEntry.size - 1);
                        //crc is in the section, last two bytes
                        sect_exp_crc = ((u_int32_t *)buff)[tocEntry.size - 1];
                        TOCPU1(sect_exp_crc)
                        sect_exp_crc = (u_int16_t) sect_exp_crc;
                        //printf("-D-INSECTION sect_act_crc=%d sect_exp_crc=%d\n", sect_act_crc, sect_exp_crc);
                    }

                    if (tocEntry.type != FS3_DEV_INFO || CheckDevInfoSignature((u_int32_t *)buff)) {
                        if (!DumpFs3CRCCheck(tocEntry.type,
                                             physAddr,
                                             entrySizeInBytes,
                                             sect_act_crc,
                                             sect_exp_crc,
                                             tocEntry.crc == NOCRC, verifyCallBackFunc)) {
                            if (isDtoc) {
                                _badDevDataSections = true;
                            }
                            retVal = false;
                        } else {
                            //printf("-D- toc type : 0x%.8x\n" , toc_entry.type);
                            GetSectData(tocArray->tocArr[section_index].section_data,
                                        (u_int32_t *)buff, tocEntry.size * 4);
                            bool isDevInfoSection = (tocEntry.type == FS3_DEV_INFO);
                            bool isDevInfoValid = isDevInfoSection && CheckDevInfoSignature((u_int32_t *)buff);
                            if (isDevInfoValid) {
                                validDevInfoCount++;
                            }
                            if (!isDevInfoSection || isDevInfoValid) {
                                if (IsGetInfoSupported(tocEntry.type)) {
                                    if (!GetImageInfoFromSection(buff, tocEntry.type, tocEntry.size * 4)) {
                                        retVal = false;
                                        errmsg("Failed to get info from section %d", tocEntry.type);
                                    }
                                } else if (tocEntry.type == FS3_DBG_FW_INI) {
                                    TOCPUn(buff, tocEntry.size);
                                    GetSectData(_fwConfSect, (u_int32_t *)buff, tocEntry.size * 4);
                                }
                            }
                        }
                    } else {
                        GetSectData(tocArray->tocArr[section_index].section_data,
                                    (u_int32_t *)buff, tocEntry.size * 4);
                    }
                }
            }

            tocArray->tocArr[section_index].entry_addr = entryAddr;
            tocArray->tocArr[section_index].toc_entry = tocEntry;
            memcpy(tocArray->tocArr[section_index].data,
                   entryBuffer, CX5FW_ITOC_ENTRY_SIZE);

        }
        if (nextBootFwVer) {
            // if nextBootFwVer, return after reading fw version
            break;
        }
        section_index++;
    } while (tocEntry.type != FS3_END);

    tocArray->numOfTocs = section_index - 1;

    if (isDtoc) {
        if (!mfgExists) {
            _badDevDataSections = true;
            return errmsg(MLXFW_NO_MFG_ERR, "No \"" MFG_INFO "\" info section.");
        }
        //when you start checking device info signatures => uncomment this code
        if (validDevInfoCount != 1 && !show_itoc &&
            (_readSectList.size() == 0 ||
             find(_readSectList.begin(), _readSectList.end(), FS3_DEV_INFO) != _readSectList.end())
            ) {
            _badDevDataSections = true;
            if (validDevInfoCount == 0) {
                return errmsg(MLXFW_NO_VALID_DEVICE_INFO_ERR, "No \"" DEV_INFO "\" info section.");
            }
            //more than one valid devinfo:
            return errmsg(MLXFW_TWO_VALID_DEVICE_INFO_ERR, "Two \"" DEV_INFO "\" info sections.");
        }
    }

    return retVal;
}



bool Fs4Operations::FsVerifyAux(VerifyCallBack verifyCallBackFunc, bool show_itoc,
                                struct QueryOptions queryOptions, bool ignoreDToc, bool verbose)
{
    u_int32_t dtocPtr;
    u_int8_t *buff;
    u_int32_t log2_chunk_size;
    bool is_image_in_odd_chunks;

    if (!getImgStart()) {
        return false;
    }

    report_callback(verifyCallBackFunc, "\nFS4 failsafe image\n\n");

    _ioAccess->set_address_convertor(0, 0);

    if (!getHWPtrs(verifyCallBackFunc)) {
        return false;
    }
    // if nextBootFwVer is true, no need to get all the information, just the fw version is enough - therefore skip everything else
    if (!nextBootFwVer) {
        if (!verifyToolsArea(verifyCallBackFunc)) {
            return false;
        }

    // Update image cache till before boot2 header:
        READALLOCBUF((*_ioAccess), _fwImgInfo.imgStart, buff, _boot2_ptr, "All Before Boot2");
        Fs3UpdateImgCache(buff, 0, _boot2_ptr);
        free(buff);

        _ioAccess->set_address_convertor(_fwImgInfo.cntxLog2ChunkSize, _fwImgInfo.imgStart != 0);

    // Get BOOT2 -Get Only bootSize if quickQuery == true else read and check CRC of boot2 section as well
        FS3_CHECKB2(0, _boot2_ptr, !queryOptions.quickQuery, PRE_CRC_OUTPUT, verifyCallBackFunc);

        _fs4ImgInfo.firstItocArrayIsEmpty = false;
        _fs4ImgInfo.itocArr.tocArrayAddr = _itoc_ptr;

    /*printf("\n-D-_ioAccess size=0x%x\n", _ioAccess->get_size());
       printf("\n-D-dtoc_ptr=0x%x\n", dtoc_ptr);*/

        if (!verifyTocHeader(_itoc_ptr, false, verifyCallBackFunc)) {
            _itoc_ptr += FS4_DEFAULT_SECTOR_SIZE;
            _fs4ImgInfo.itocArr.tocArrayAddr = _itoc_ptr;
            _fs4ImgInfo.firstItocArrayIsEmpty = true;
            if (!verifyTocHeader(_itoc_ptr, false, verifyCallBackFunc)) {
                return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid ITOC Header was found.");
            }
        }
    }
    if (_ioAccess->is_flash() == false && _signatureDataSet == false) {
        int signature_size = 3 * HMAC_SIGNATURE_LENGTH;
        uint8_t signature_data[3 * HMAC_SIGNATURE_LENGTH] = { 0 };
        int signature_offset = _digest_mdk_ptr;
        if (signature_offset == 0) {
            signature_offset = _digest_recovery_key_ptr;
        }
        if (signature_offset != 0) {
        READBUF((*_ioAccess),
            signature_offset,
            signature_data,
            signature_size,
            "Reading data pointed by HW MDK Pointer");
        Fs3UpdateImgCache(signature_data, signature_offset, signature_size);
        }
        _signatureDataSet = true;
    }
    if (!verifyTocEntries(_itoc_ptr, show_itoc, false,
                          queryOptions, verifyCallBackFunc, verbose)) {
        return false;
    }
    if (nextBootFwVer) {
        return true;
    }
    if (ignoreDToc) {
        return true;
    }
    // Verify DTOC:
    log2_chunk_size = _ioAccess->get_log2_chunk_size();
    is_image_in_odd_chunks = _ioAccess->get_is_image_in_odd_chunks();
    _ioAccess->set_address_convertor(0, 0);
    //-Verify DToC Header:
    dtocPtr = _ioAccess->get_size() - FS4_DEFAULT_SECTOR_SIZE;
    if (!verifyTocHeader(dtocPtr, true, verifyCallBackFunc)) {
        return errmsg(MLXFW_NO_VALID_ITOC_ERR, "No valid DTOC Header was found.");
    }
    _fs4ImgInfo.dtocArr.tocArrayAddr = dtocPtr;
    //-Verify DToC Entries:
    if (!verifyTocEntries(dtocPtr, show_itoc, true,
                          queryOptions, verifyCallBackFunc, verbose)) {
        _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
        return false;
    }
    _ioAccess->set_address_convertor(log2_chunk_size, is_image_in_odd_chunks);
    return true;
}

u_int8_t Fs4Operations::FwType()
{
    return FIT_FS4;
}

bool Fs4Operations::FwInit()
{
    if (!Fs3Operations::FwInit()) {
        return false;
    }
    _fs4ImgInfo.firstItocArrayIsEmpty = 0;
    _fs4ImgInfo.smallestDTocAddr = 0;
    _fwImgInfo.fwType = (fw_img_type_t) FwType();
    return true;
}

bool Fs4Operations::CheckFs4ImgSize(Fs4Operations& imageOps, bool useImageDevData)
{
    //check if max itoc is not overwriting the chunk
    if (imageOps._fwImgInfo.lastImageAddr >= (u_int32_t)(imageOps._fwImgInfo.imgStart + (1 << imageOps._maxImgLog2Size))) {
        return errmsg(MLXFW_IMAGE_TOO_LARGE_ERR,
                      "Largest Image Address (0x%x) is greater than max size of image (0x%x)",
                      imageOps._fwImgInfo.lastImageAddr,
                      imageOps._maxImgLog2Size);
    }

    //check if minimal dtoc is not overwriting the preceding chunk
    if (useImageDevData) {
        u_int32_t devAreaStartAddress = _ioAccess->get_size() - (1 << imageOps._maxImgLog2Size);
        if (imageOps._fs4ImgInfo.smallestDTocAddr < devAreaStartAddress) {
            return errmsg(MLXFW_DTOC_OVERWRITE_CHUNK,
                          "Smallest DToc address (0x%x) is less than device area start address (0x%x)",
                          imageOps._fs4ImgInfo.smallestDTocAddr,
                          devAreaStartAddress);
        }
    }

    return true;
}

bool Fs4Operations::FwReadData(void *image, u_int32_t *imageSize, bool verbose)
{
    struct QueryOptions queryOptions;
    if (!imageSize) {
        return errmsg("bad parameter is given to FwReadData\n");
    }

    queryOptions.readRom = true;
    queryOptions.quickQuery = false;
    if (image == NULL) {
        // When we need only to get size, no need for reading entire image
        queryOptions.readRom = false;
        queryOptions.quickQuery = true;
    }
    // Avoid Warning
    if (!FsVerifyAux((VerifyCallBack)NULL, 0, queryOptions, false, verbose)) {
        return false;
    }

    _imageCache.get((u_int8_t *)image,
                    _fwImgInfo.lastImageAddr);
    //size will be always as (_ioAccess)->get_size(), as the dtoc always at the end
    *imageSize = (_ioAccess)->get_size();

    //take device sections
    if (image != NULL) {
        _imageCache.get((u_int8_t *)image + _fs4ImgInfo.smallestDTocAddr,
                        _fs4ImgInfo.smallestDTocAddr,
                        (_ioAccess)->get_size() - _fs4ImgInfo.smallestDTocAddr);
    }

    return true;
}

bool Fs4Operations::Fs4RemoveSectionAux(fs3_section_t sectionType)
{
    int itocEntryIndex = 0;
    struct   fs4_toc_info *itocEntry = (struct fs4_toc_info *)NULL;
    TocArray *itocArray = &_fs4ImgInfo.itocArr;

    if (!Fs4GetItocInfo(itocArray->tocArr, itocArray->numOfTocs,
                        sectionType, itocEntry, itocEntryIndex)) {
        return false;
    }

    u_int32_t sectionSizeInBytes = itocEntry->section_data.size();
    u_int32_t sectionSizeInDW = sectionSizeInBytes >> 2;

    //update the sections that are after this section
    for (int i = itocEntryIndex + 1; i < itocArray->numOfTocs; i++) {
        struct fs4_toc_info *tocInfo = itocArray->tocArr + i;
        tocInfo->toc_entry.flash_addr =
            tocInfo->toc_entry.flash_addr - sectionSizeInDW;
        tocInfo->entry_addr = tocInfo->entry_addr - CX5FW_ITOC_ENTRY_SIZE;

        updateTocEntryCRC(tocInfo);

        updateTocEntryData(tocInfo);

        Fs3UpdateImgCache(tocInfo->data, tocInfo->entry_addr,
                          CX5FW_ITOC_ENTRY_SIZE);
        Fs3UpdateImgCache(tocInfo->section_data.data(),
                          tocInfo->toc_entry.flash_addr << 2,
                          tocInfo->toc_entry.size << 2);

    }

    _fwImgInfo.lastImageAddr = _fwImgInfo.lastImageAddr - sectionSizeInBytes;

    //remove the itoc from the array and update the cache
    for (int i = itocEntryIndex + 1; i < (itocArray->numOfTocs + 1); i++) {
        TocArray::copyTocArrEntry(itocArray->tocArr + i - 1, itocArray->tocArr + i);
    }

    _fs4ImgInfo.itocArr.numOfTocs--;

    u_int32_t lastItocSectAddress = itocArray->tocArrayAddr +
                                    CX5FW_ITOC_HEADER_SIZE +
                                    itocArray->numOfTocs * CX5FW_ITOC_ENTRY_SIZE;
    updateTocEndEntryInImgCache(lastItocSectAddress);

    return true;
}

bool Fs4Operations::Fs4RemoveSection(fs3_section_t sectionType, ProgressCallBack progressFunc)
{
    vector<u_int8_t> newImageData;

    if (!Fs4RemoveSectionAux(sectionType)) {
        return false;
    }

    _imageCache.get(newImageData, 0, (_ioAccess)->get_size());

    burnDataParamsT params;
    params.data = (u_int32_t *)&newImageData[0];
    params.dataSize = newImageData.size();
    params.progressFunc = progressFunc;
    params.calcSha = _signatureExists;
    if (!FwBurnData(params)) {
        return false;
    }

    return true;
}

bool Fs4Operations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    //run int query to get product ver
    if (!FsIntQueryAux(true, false)) {
        return false;
    }

    if (!RomCommonCheck(ignoreProdIdCheck, true)) {
        return false;
    }

    return Fs4RemoveSection(FS3_ROM_CODE, progressFunc);
}

bool Fs4Operations::Fs4AddSectionAux(fs3_section_t sectionType,
                                     enum CRCTYPE crcType, u_int8_t zippedImage, u_int32_t *newSectData,
                                     u_int32_t newSectSize)
{
    struct fs4_toc_info *itocEntry = (struct fs4_toc_info *)NULL;
    int itocEntryIndex = 0;
    TocArray *itocArray = &_fs4ImgInfo.itocArr;
    struct fs4_toc_info *newITocEntry;

    //search for the section, remove it if found
    if (Fs4GetItocInfo(itocArray->tocArr, itocArray->numOfTocs, sectionType,
                       itocEntry, itocEntryIndex)) {
        if (getImageSize() - (itocEntry->toc_entry.size << 2) + newSectSize
            > (u_int32_t)(1 << _maxImgLog2Size)) {
            return errmsg("Section size is too large");
        }
        if (!Fs4RemoveSectionAux(sectionType)) {
            return false;
        }
    } else {
        if (getImageSize() + newSectSize >
            (u_int32_t)(1 << _maxImgLog2Size)) {
            return errmsg("Section size is too large");
        }
        if (itocArray->numOfTocs + 1 > MAX_TOCS_NUM) {
            return errmsg(
                "Cannot add TOC entry, too many entries in iTOC array.");
        }
    }

    newITocEntry = itocArray->tocArr + itocArray->numOfTocs;

    //update the new itoc entry
    Fs4Operations::TocArray::initEmptyTocArrEntry(newITocEntry);

    newITocEntry->entry_addr = itocArray->tocArrayAddr + TOC_HEADER_SIZE +
                               itocArray->numOfTocs * TOC_ENTRY_SIZE;
    newITocEntry->toc_entry.type = sectionType;
    newITocEntry->toc_entry.size = newSectSize >> 2;
    newITocEntry->toc_entry.flash_addr =
        (_fwImgInfo.lastImageAddr - _fwImgInfo.imgStart) >> 2;
    newITocEntry->toc_entry.crc = crcType;
    newITocEntry->toc_entry.zipped_image = zippedImage;
    newITocEntry->toc_entry.section_crc = CalcImageCRC((u_int32_t *)newSectData,
                                                       newSectSize >> 2);

    updateTocEntryCRC(newITocEntry);

    updateTocEntryData(newITocEntry);

    updateTocEntrySectionData(newITocEntry, (u_int8_t *)newSectData, newSectSize);

    itocArray->numOfTocs++;

    _fwImgInfo.lastImageAddr += newSectSize;

    Fs3UpdateImgCache(newITocEntry->data, newITocEntry->entry_addr,
                      CX5FW_ITOC_ENTRY_SIZE);

    u_int32_t lastItocSectAddress = itocArray->tocArrayAddr +
                                    CX5FW_ITOC_HEADER_SIZE +
                                    itocArray->numOfTocs * CX5FW_ITOC_ENTRY_SIZE;
    updateTocEndEntryInImgCache(lastItocSectAddress);

    Fs3UpdateImgCache(newITocEntry->section_data.data(),
                      newITocEntry->toc_entry.flash_addr << 2,
                      newITocEntry->toc_entry.size << 2);

    return true;
}

bool Fs4Operations::Fs4AddSection(fs3_section_t sectionType,
                                  enum CRCTYPE crcType, u_int8_t zippedImage, u_int32_t *newSectData,
                                  u_int32_t newSectSize, ProgressCallBack progressFunc)
{
    vector<u_int8_t> newImageData;

    if (!Fs4AddSectionAux(sectionType, crcType, zippedImage, newSectData,
                          newSectSize)) {
        return false;
    }

    _imageCache.get(newImageData, 0, (_ioAccess)->get_size());
    burnDataParamsT params;
    params.data = (u_int32_t *)&newImageData[0];
    params.dataSize = newImageData.size();
    params.progressFunc = progressFunc;
    params.calcSha = _signatureExists;
    if (!FwBurnData(params)) {
        return false;
    }

    return true;
}

bool Fs4Operations::FwBurnRom(FImage *romImg, bool ignoreProdIdCheck, bool ignoreDevidCheck,
                              ProgressCallBack progressFunc)
{
    roms_info_t romsInfo;

    if (romImg == NULL) {
        return errmsg("Bad ROM image is given.");
    }

    if (romImg->getBufLength() == 0) {
        return errmsg("Bad ROM file: Empty file.");
    }

    if (!FwOperations::getRomsInfo(romImg, romsInfo)) {
        return errmsg("Failed to read given ROM.");
    }

    if (!FsIntQueryAux(false, false)) {
        return false;
    }

    if (!ignoreDevidCheck && !FwOperations::checkMatchingExpRomDevId(
            _fwImgInfo.ext_info.dev_type, romsInfo)) {
        return errmsg("Image file ROM: FW is for device %d, but Exp-ROM is "
                      "for device %d\n", _fwImgInfo.ext_info.dev_type,
                      romsInfo.exp_rom_com_devid);
    }

    if (!RomCommonCheck(ignoreProdIdCheck, false)) {
        return false;
    }

    if (romImg->getBuf() == NULL) {
        return false;
    }
    return Fs4AddSection(FS3_ROM_CODE, INITOCENTRY, 0, romImg->getBuf(), romImg->getBufLength(), progressFunc);
}

void Fs4Operations::updateTocEndEntryInImgCache(u_int32_t lastItocSectAddress)
{
    u_int8_t tocEndBuff[CX5FW_ITOC_ENTRY_SIZE];
    memset(tocEndBuff, FS3_END, CX5FW_ITOC_ENTRY_SIZE);
    Fs3UpdateImgCache(tocEndBuff, lastItocSectAddress, CX5FW_ITOC_ENTRY_SIZE);
}

void Fs4Operations::updateTocEntryCRC(struct fs4_toc_info *tocEntry)
{
    u_int8_t tocEntryBuff[CX5FW_ITOC_ENTRY_SIZE];

    memset(tocEntryBuff, 0, CX5FW_ITOC_ENTRY_SIZE);
    cx5fw_itoc_entry_pack(&(tocEntry->toc_entry), tocEntryBuff);
    tocEntry->toc_entry.itoc_entry_crc =
        CalcImageCRC((u_int32_t *)tocEntryBuff, TOC_ENTRY_SIZE / 4 - 1);
}

void Fs4Operations::updateTocHeaderCRC(struct cx5fw_itoc_header *tocHeader)
{
    u_int8_t tocHeaderBuff[CX5FW_ITOC_HEADER_SIZE];

    memset(tocHeaderBuff, 0, CX5FW_ITOC_HEADER_SIZE);
    cx5fw_itoc_header_pack(tocHeader, tocHeaderBuff);
    tocHeader->itoc_entry_crc =
        CalcImageCRC((u_int32_t *)tocHeaderBuff, CX5FW_ITOC_HEADER_SIZE / 4 - 1);
}

void Fs4Operations::updateTocEntryData(struct fs4_toc_info *tocEntry)
{
    memset(tocEntry->data, 0, CX5FW_ITOC_ENTRY_SIZE);
    cx5fw_itoc_entry_pack(&(tocEntry->toc_entry), tocEntry->data);
}

void Fs4Operations::updateTocEntrySectionData(struct fs4_toc_info *tocEntry,
                                              u_int8_t *data, u_int32_t dataSize)
{
    tocEntry->section_data.resize(dataSize);
    memcpy(tocEntry->section_data.data(), data, dataSize);
}

bool Fs4Operations::restoreWriteProtection(mflash *mfl, u_int8_t banksNum,
                                           write_protect_info_t protect_info[])
{
    for (unsigned int i = 0; i < banksNum; i++) {
        int rc = mf_set_write_protect(mfl, i, protect_info + i);
        if (rc != MFE_OK) {
            return errmsg("Failed to restore write protection settings: %s",
                          mf_err2str(rc));
        }
    }
    return true;
}

bool Fs4Operations::CreateDtoc(vector<u_int8_t>& img, u_int8_t* SectionData, u_int32_t section_size, u_int32_t flash_data_addr,
    fs3_section_t section, u_int32_t tocEntryAddr, bool IsCRC)
{
    struct fs4_toc_info itoc_info;
    memset(&itoc_info.data, 0, sizeof(itoc_info.data));
    memset(&itoc_info.toc_entry, 0, sizeof(struct cx5fw_itoc_entry));
    itoc_info.section_data.resize(section_size, 0xff);
    itoc_info.entry_addr = tocEntryAddr;
    struct cx5fw_itoc_entry *toc_entry_p = &(itoc_info.toc_entry);
    toc_entry_p->size = section_size >> 2;
    toc_entry_p->type = (u_int8_t)section;
    if (!IsCRC) {
        toc_entry_p->crc = 1;
    }
    else {
        toc_entry_p->crc = 0;
    }
    toc_entry_p->flash_addr = flash_data_addr >> 2;
    u_int32_t new_crc = CalcImageCRC((u_int32_t *)SectionData, toc_entry_p->size);
    toc_entry_p->section_crc = new_crc;
    updateTocEntryCRC(&itoc_info);
    u_int8_t itoc_data[CX5FW_ITOC_ENTRY_SIZE] = { 0 };
    cx5fw_itoc_entry_pack(toc_entry_p, itoc_data);
    memcpy(img.data() + tocEntryAddr, itoc_data, CX5FW_ITOC_ENTRY_SIZE);
    return true;
}
#ifndef CONNECTX5_NV_DATA_SIZE
#define CONNECTX5_NV_DATA_SIZE    (0x10000)
#endif
#define CONNECTX5_NV_LOG_SIZE 2*(CONNECTX5_NV_DATA_SIZE)
bool Fs4Operations::RestoreDevToc(vector<u_int8_t>& img, char* psid, dm_dev_id_t devid_t, const cx4fw_uid_entry& base_guid, const cx4fw_uid_entry& base_mac)
{
    /*DTOC HEADER*/
    u_int32_t offset_from_begin = 0x1000000;
    u_int32_t flash_data_addr = 0;
    u_int32_t flash_size = 0x2000000;
    u_int32_t nvlogSize = CONNECTX5_NV_LOG_SIZE;
    u_int32_t nvlogBeginOffset = 0xf00000;
    u_int32_t nvLogDelta = 0x20000;
    if (devid_t == DeviceConnectX5) {
        flash_size = 0x1000000;
        offset_from_begin = 0;
        nvlogSize = CONNECTX5_NV_LOG_SIZE/2;
        nvlogBeginOffset = 0xf90000;
        nvLogDelta = 0x10000;
    }
    img.resize(flash_size, 0xff);
    u_int32_t dtocPtr = flash_size - FS4_DEFAULT_SECTOR_SIZE;
    u_int8_t dtocHeader[] = { 0x44 ,0x54 ,0x4f ,0x43 ,0x04 ,0x08 ,0x15 ,0x16 ,0x23 ,0x42 ,0xca ,0xfa ,0xba ,0xca ,0xfe ,0x00 ,
                             0x01 ,0x00 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xbd ,0x90 };

    memcpy(img.data() + dtocPtr, dtocHeader, CX5FW_ITOC_HEADER_SIZE);
    u_int32_t section_index = 0;
    u_int32_t entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    /* NV_LOG */
    flash_data_addr = nvlogBeginOffset + offset_from_begin;
    u_int8_t NvLogBuffer[CONNECTX5_NV_LOG_SIZE] = { 0 };
    memcpy(img.data() + flash_data_addr, NvLogBuffer, nvlogSize);
    CreateDtoc(img, NvLogBuffer, CONNECTX5_NV_LOG_SIZE, flash_data_addr, FS3_FW_NV_LOG, entryAddr, false);

    /* NV_DATA 0*/
    nvlogBeginOffset += 0x20000;
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    flash_data_addr = nvlogBeginOffset + offset_from_begin;
    u_int8_t NvDataBuffer[CONNECTX5_NV_DATA_SIZE] = { 0 };
    memcpy(img.data() + flash_data_addr, NvDataBuffer, CONNECTX5_NV_DATA_SIZE);
    CreateDtoc(img, NvDataBuffer, CONNECTX5_NV_DATA_SIZE, flash_data_addr, FS3_NV_DATA0, entryAddr, false);

    /* NV_DATA 2*/
    nvlogBeginOffset += nvLogDelta;
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    flash_data_addr = nvlogBeginOffset + offset_from_begin;
    memcpy(img.data() + flash_data_addr, NvDataBuffer, CONNECTX5_NV_DATA_SIZE);
    CreateDtoc(img, NvDataBuffer, CONNECTX5_NV_DATA_SIZE, flash_data_addr, FS3_NV_DATA2, entryAddr, false);

    /*DEV_INFO*/
    nvlogBeginOffset += nvLogDelta;
    flash_data_addr = nvlogBeginOffset + offset_from_begin;
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;

    struct cx5fw_device_info dev_info;
    memset(&dev_info, 0, sizeof(dev_info));
    u_int8_t DevInfoBuffer[CX5FW_DEVICE_INFO_SIZE] = { 0 };
    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;
    dev_info.minor_version = 0;
    dev_info.major_version = 2;
    dev_info.vsd_vendor_id = 0x15b3;

    dev_info.guids.guids.num_allocated = base_guid.num_allocated;
    dev_info.guids.guids.step = base_guid.step;
    dev_info.guids.guids.uid = base_guid.uid;
    dev_info.guids.macs.num_allocated = base_mac.num_allocated;
    dev_info.guids.macs.step = base_mac.step;
    dev_info.guids.macs.uid = base_mac.uid;
    cx5fw_device_info_pack(&dev_info, DevInfoBuffer);
    memcpy(img.data() + flash_data_addr, DevInfoBuffer, CX5FW_DEVICE_INFO_SIZE);
    CreateDtoc(img, DevInfoBuffer, CX5FW_DEVICE_INFO_SIZE, flash_data_addr, FS3_DEV_INFO, entryAddr, true);
    
    /*MFG_INFO*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    flash_data_addr = 0xff8000 + offset_from_begin;
    struct cx4fw_mfg_info cx4_mfg_info;
    u_int8_t MfgInfoData[CX4FW_MFG_INFO_SIZE] = { 0 };
    memset(&cx4_mfg_info, 0, sizeof(cx4_mfg_info));
    cx4_mfg_info.guids_override_en = 1;//get the GUIDs from DEV_INFO
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
    CreateDtoc(img, MfgInfoData, CX4FW_MFG_INFO_SIZE, flash_data_addr, FS3_MFG_INFO, entryAddr, true);

    /*VPD_R0*/
    section_index++;
    entryAddr = dtocPtr + TOC_HEADER_SIZE + section_index * TOC_ENTRY_SIZE;
    struct cx5fw_itoc_entry toc_entry;
    memset(&toc_entry, 0, sizeof(struct cx5fw_itoc_entry));
    u_int8_t entryBuffer[TOC_ENTRY_SIZE] = { 0 };
    flash_data_addr += CX4FW_MFG_INFO_SIZE;

    toc_entry.size = 0;
    toc_entry.type = FS3_VPD_R0;
    toc_entry.flash_addr = flash_data_addr >> 2;
    toc_entry.crc = 0;
    toc_entry.section_crc = CalcImageCRC((u_int32_t *)NULL, toc_entry.size);
    cx5fw_itoc_entry_pack(&toc_entry, entryBuffer);
    u_int32_t entry_crc = CalcImageCRC((u_int32_t *)entryBuffer, (TOC_ENTRY_SIZE / 4) - 1);
    toc_entry.itoc_entry_crc = entry_crc;
    cx5fw_itoc_entry_pack(&toc_entry, entryBuffer);
    memcpy(img.data() + entryAddr, entryBuffer, TOC_ENTRY_SIZE);
    return true;
}
bool Fs4Operations::AlignDeviceSections(FwOperations *imageOps)
{
    bool rc = true;
    u_int8_t data[FS4_DEFAULT_SECTOR_SIZE] = {0};

    struct cx5fw_itoc_header itocHeader;
    cx5fw_itoc_header_unpack(&itocHeader, ((Fs4Operations *)imageOps)->_fs4ImgInfo.itocArr.tocHeader);

    if (itocHeader.flash_layout_version != 1) {
        return errmsg("Please update MFT package");
    }

    u_int32_t log2_chunk_size_bu = _ioAccess->get_log2_chunk_size();
    bool is_image_in_odd_chunks_bu = _ioAccess->get_is_image_in_odd_chunks();

    unsigned int retries = 0;
    const int nvLogIndex = 0, nvData0Index = 1, nvData1Index = 2,
              devInfo0Index = 3, devInfo1Index = 4;

    struct fs4_toc_info *sections[COUNT_OF_SECTIONS_TO_ALIGN] = {(struct fs4_toc_info *)NULL,
                                                                 (struct fs4_toc_info *)NULL,
                                                                 (struct fs4_toc_info *)NULL,
                                                                 (struct fs4_toc_info *)NULL,
                                                                 (struct fs4_toc_info *)NULL};

    const char *sectionsNames[COUNT_OF_SECTIONS_TO_ALIGN] = { GetSectionNameByType(FS3_FW_NV_LOG),
                                                              GetSectionNameByType(FS3_NV_DATA0),
                                                              GetSectionNameByType(FS3_NV_DATA2),
                                                              GetSectionNameByType(FS3_DEV_INFO),
                                                              GetSectionNameByType(FS3_DEV_INFO) };

    const u_int32_t newOffsets[COUNT_OF_SECTIONS_TO_ALIGN] = {0xf90000, 0xfb0000,
                                                              0xfc0000, 0xfd0000, 0xfe0000};

    const u_int32_t offsets[COUNT_OF_SECTIONS_TO_ALIGN] = {0xc00000, 0xc10000,
                                                           0xc20000, 0xc30000, 0xc40000};

    //find related sections
    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++) {
        struct fs4_toc_info *toc = &_fs4ImgInfo.dtocArr.tocArr[i];
        if (toc->toc_entry.type == FS3_FW_NV_LOG) {
            sections[nvLogIndex] = toc;
        } else if (toc->toc_entry.type == FS3_NV_DATA0) {
            sections[nvData0Index] = toc;
        } else if (toc->toc_entry.type == FS3_NV_DATA2) {
            sections[nvData1Index] = toc;
        } else if (toc->toc_entry.type == FS3_DEV_INFO) {
            if (sections[devInfo0Index]) {
                sections[devInfo1Index] = toc;
            } else {
                sections[devInfo0Index] = toc;
            }
        }
    }

    for (unsigned int i = 0; i < COUNT_OF_SECTIONS_TO_ALIGN; i++) {
        if (sections[i] == NULL) {
            return errmsg("%s section was not found!",
                          sectionsNames[i]);
        }
        if ((sections[i]->toc_entry.flash_addr << 2) != offsets[i]) {
            return errmsg("The section %s was expected to be at address "
                          "0x%x but it is at 0x%x",
                          sectionsNames[i], offsets[i],
                          sections[i]->toc_entry.flash_addr << 2);
        }
        for (int j = 0; j < _fs4ImgInfo.dtocArr.numOfTocs; j++) {
            struct fs4_toc_info *toc = &_fs4ImgInfo.dtocArr.tocArr[j];
            u_int32_t start = toc->toc_entry.flash_addr << 2;
            u_int32_t end = (toc->toc_entry.flash_addr << 2) + (toc->toc_entry.size << 2) - 1;
            if (checkIfSectionsOverlap(newOffsets[i],
                                       newOffsets[i] + (sections[i]->toc_entry.size << 2) - 1,
                                       start, end)) {
                return errmsg("%s section's new address overlaps with %s section",
                              sectionsNames[i],
                              GetSectionNameByType(toc->toc_entry.type));
            }
        }
        //check if new offset overlaps with other new offsets
        for (unsigned int j = 0; j < COUNT_OF_SECTIONS_TO_ALIGN; j++) {
            if (i != j) {
                if (checkIfSectionsOverlap(newOffsets[i],
                                           newOffsets[i] + (sections[i]->toc_entry.size << 2) - 1,
                                           newOffsets[j],
                                           newOffsets[j] + (sections[j]->toc_entry.size << 2) - 1)) {
                    return errmsg("%s section's new address overlaps with %s section new address",
                                  sectionsNames[i], sectionsNames[j]);
                }
            }
        }

    }

    FBase *origFlashObj = (FBase *)NULL;
    FBase *flashObjWithOcr = (FBase *)NULL;

    //Re-open flash with -ocr if needed
    if (_fwParams.ignoreCacheRep == 0) {
        origFlashObj = _ioAccess;
        _fwParams.ignoreCacheRep = 1;
        if (!FwOperations::FwAccessCreate(_fwParams, &_ioAccess)) {
            _ioAccess = origFlashObj;
            _fwParams.ignoreCacheRep = 0;
            return errmsg("Failed to open device for direct flash access");
        }
        flashObjWithOcr = _ioAccess;
    }

    mflash *mfl = (mflash *)NULL;

    //disable write protection:
    ext_flash_attr_t attr;
    memset(&attr, 0x0, sizeof(attr));
    if (!((Flash *)_ioAccess)->get_attr(attr)) {
        rc = false;
        goto cleanup;
    }

    mfl = ((Flash *)_ioAccess)->getMflashObj();
    write_protect_info_t protect_info;
    memset(&protect_info, 0, sizeof(protect_info));
    for (unsigned int i = 0; i < attr.banks_num; i++) {
        int rc = mf_set_write_protect(mfl, i, &protect_info);
        if (rc != MFE_OK) {
            errmsg("Failed to disable flash write protection: %s",
                   mf_err2str(rc));
            rc = false;
            goto cleanup;
        }
    }

    while (((Flash *)_ioAccess)->is_flash_write_protected() && retries++ < 5) {
        msleep(500);
    }
    if (retries == 5) {
        errmsg("Failed to disable flash write protection");
        rc = false;
        goto cleanup;
    }

    if (flashObjWithOcr != NULL) {
        _ioAccess = origFlashObj;
        _fwParams.ignoreCacheRep = 0;
    }

    //read the sections from the flash
    _readSectList.push_back(FS3_FW_NV_LOG);
    _readSectList.push_back(FS3_NV_DATA0);
    _readSectList.push_back(FS3_NV_DATA2);
    _readSectList.push_back(FS3_DEV_INFO);
    if (!FsIntQueryAux()) {
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

    //move to the new offsets:
    for (unsigned int i = 0; i < COUNT_OF_SECTIONS_TO_ALIGN; i++) {
        //flash address is in DW and offset is given in bytes
        sections[i]->toc_entry.flash_addr = newOffsets[i] >> 2;
        //we updated the entry => calculate new CRC
        updateTocEntryCRC(sections[i]);
        //update the image cache with the toc entry changes:
        u_int8_t buff[CX5FW_ITOC_ENTRY_SIZE];
        memset(buff, 0x0, CX5FW_ITOC_ENTRY_SIZE);
        cx5fw_itoc_entry_pack(&(sections[i]->toc_entry), buff);
        Fs3UpdateImgCache(buff, _fs4ImgInfo.dtocArr.tocArrayAddr +
                          ((sections[i] - _fs4ImgInfo.dtocArr.tocArr + 1)
                           * CX5FW_ITOC_ENTRY_SIZE), CX5FW_ITOC_ENTRY_SIZE);
        //write the section data to the new offset
        if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, newOffsets[i],
                          sections[i]->section_data.data(),
                          sections[i]->section_data.size(), true, true, 0, 0)) {
            if (!restoreWriteProtection(mfl, attr.banks_num,
                                        attr.protect_info_array)) {
                rc = false;
                goto cleanup;
            }
            errmsg("Failed to move %s Section", sectionsNames[i]);
            rc = false;
            goto cleanup;
        }
        //update the image cache with the new section:
        Fs3UpdateImgCache(sections[i]->section_data.data(), newOffsets[i],
                          sections[i]->section_data.size());
    }

    //set dtoc.header.flash_layout_version to 0x1
    struct cx5fw_itoc_header dtocHeader;
    cx5fw_itoc_header_unpack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    dtocHeader.flash_layout_version = 0x1;
    updateTocHeaderCRC(&dtocHeader);
    cx5fw_itoc_header_pack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    //update image cache with the dtoc headers changes:
    Fs3UpdateImgCache(_fs4ImgInfo.dtocArr.tocHeader,
                      _fs4ImgInfo.dtocArr.tocArrayAddr,
                      CX5FW_ITOC_HEADER_SIZE);

    //write the dtoc array
    _imageCache.get(data, _fs4ImgInfo.dtocArr.tocArrayAddr,
                    FS4_DEFAULT_SECTOR_SIZE);
    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _fs4ImgInfo.dtocArr.tocArrayAddr, data,
                      FS4_DEFAULT_SECTOR_SIZE, true, true, 0, 0)) {
        if (!restoreWriteProtection(mfl, attr.banks_num,
                                    attr.protect_info_array)) {
            rc = false;
            goto cleanup;
        }
        errmsg("Failed to update DToC Header");
        rc = false;
        goto cleanup;
    }

    if (flashObjWithOcr != NULL) {
        _ioAccess = flashObjWithOcr;
        _fwParams.ignoreCacheRep = 1;
    }
    if (!restoreWriteProtection(mfl, attr.banks_num, attr.protect_info_array)) {
        rc = false;
        goto cleanup;
    }

cleanup:
    if (attr.type_str) {
        delete attr.type_str;
    }
    if (flashObjWithOcr != NULL) {
        _ioAccess = origFlashObj;
        _fwParams.ignoreCacheRep = 0;
        flashObjWithOcr->close();
        delete flashObjWithOcr;
    }

    _ioAccess->set_address_convertor(log2_chunk_size_bu, is_image_in_odd_chunks_bu);

    return rc;
}

bool Fs4Operations::CheckIfAlignmentIsNeeded(FwOperations *imgops)
{
    Fs4Operations& imageOps = *((Fs4Operations *) imgops);
    struct cx5fw_itoc_header itocHeader, dtocHeader;
    cx5fw_itoc_header_unpack(&dtocHeader, _fs4ImgInfo.dtocArr.tocHeader);
    cx5fw_itoc_header_unpack(&itocHeader, imageOps._fs4ImgInfo.itocArr.tocHeader);

    if (dtocHeader.flash_layout_version <
        itocHeader.flash_layout_version) {
        return true;
    }

    return false;
}

bool Fs4Operations::BurnFs4Image(Fs4Operations &imageOps,
                                 ExtBurnParams& burnParams)
{
    u_int8_t is_curr_image_in_odd_chunks;
    u_int32_t total_img_size = 0;
    u_int32_t sector_size = FS4_DEFAULT_SECTOR_SIZE;
    Flash    *f     = (Flash *)(this->_ioAccess);
    u_int8_t *data8;
    bool useImageDevData;
    int alreadyWrittenSz;

    if (_fwImgInfo.imgStart != 0 ||
        (!burnParams.burnFailsafe && ((Flash *)_ioAccess)->get_ignore_cache_replacment())) {
        is_curr_image_in_odd_chunks = 1;
    } else {
        is_curr_image_in_odd_chunks = 0;
    }

    u_int32_t new_image_start = getNewImageStartAddress(imageOps, burnParams.burnFailsafe);

    if (new_image_start == 0x800000) {
        f->set_address_convertor(0x17, 1);
    } else {
        // take chunk size from image in case of a non failsafe burn (in any case they should be the same)
        f->set_address_convertor(imageOps._fwImgInfo.cntxLog2ChunkSize, !is_curr_image_in_odd_chunks);
    }

    // check max image size
    useImageDevData =  !burnParams.burnFailsafe && burnParams.useImgDevData;
    if (!CheckFs4ImgSize(imageOps, useImageDevData)) {
        return false;
    }

    //Sanity check on the image itoc array
    if (!imageOps.CheckITocArray()) {
        return errmsg(MLXFW_IMAGE_CORRUPTED_ERR, "%s", imageOps.err());
    }

    //Find total image size that will be written
    total_img_size += imageOps._fs4ImgInfo.itocArr.getSectionsTotalSize();//itoc sections
    //Add boot section, itoc array (wo signature)
    total_img_size += imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;
    if (burnParams.useImgDevData) {
        total_img_size += sector_size;//dtoc array
        total_img_size += imageOps._fs4ImgInfo.dtocArr.getSectionsTotalSize();//dtoc sections
    }

    if (total_img_size <= sector_size) {
        return errmsg("Failed to burn FW. Internal error.");
    }

    //Write the image:
    alreadyWrittenSz = 0;

    //bring the boot section and itoc array from the cache
    u_int32_t beginingWithoutSignatureSize =
        imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;
    data8 = new u_int8_t[beginingWithoutSignatureSize];
    imageOps._imageCache.get(data8, FS3_FW_SIGNATURE_SIZE, beginingWithoutSignatureSize);

    //Write boot section and IToc array (without signature)
    if (!writeImageEx(
            burnParams.progressFuncEx,
            burnParams.progressUserData,
            burnParams.progressFunc,
            FS3_FW_SIGNATURE_SIZE,
            data8,
            imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE,
            false,
            false,
            total_img_size,
            alreadyWrittenSz)) {
        delete[] data8;
        return false;
    }
    delete[] data8;
    alreadyWrittenSz += imageOps._fs4ImgInfo.itocArr.tocArrayAddr + sector_size - FS3_FW_SIGNATURE_SIZE;

    // write itoc entries data
    for (int i = 0; i < imageOps._fs4ImgInfo.itocArr.numOfTocs; i++) {
        struct fs4_toc_info *itoc_info_p = &imageOps._fs4ImgInfo.itocArr.tocArr[i];
        struct cx5fw_itoc_entry *toc_entry = &itoc_info_p->toc_entry;
        if (!writeImageEx(
                burnParams.progressFuncEx,
                burnParams.progressUserData,
                burnParams.progressFunc,
                toc_entry->flash_addr << 2,
                    &(itoc_info_p->section_data[0]),
                    itoc_info_p->section_data.size(),
                    false,//addresses of itocs are relative and not physical
                    false,
                    total_img_size,
                    alreadyWrittenSz)) {
            return false;
        }
        alreadyWrittenSz += itoc_info_p->section_data.size();
    }

    if (burnParams.useImgDevData) {
        //Write dtoc array only if ignore_dev_data

        //Sanity check on the image dtoc array
        if (!imageOps.CheckDTocArray()) {
            return errmsg(MLXFW_IMAGE_CORRUPTED_ERR, "%s", imageOps.err());
        }

        //bring the dtoc array from the cache
        data8 = new u_int8_t[sector_size];
        imageOps._imageCache.get(data8, imageOps._fs4ImgInfo.dtocArr.tocArrayAddr,
                                 sector_size);
        if (!writeImageEx(
                burnParams.progressFuncEx,
                burnParams.progressUserData,
                burnParams.progressFunc,
                imageOps._fs4ImgInfo.dtocArr.tocArrayAddr,
                data8,
                sector_size,
                true,
                true,
                total_img_size,
                alreadyWrittenSz)) {
            delete[] data8;
            return false;
        }
        delete[] data8;
        alreadyWrittenSz += sector_size;

        //TODO: write device area (dtoc's entries)
        for (int i = 0; i < imageOps._fs4ImgInfo.dtocArr.numOfTocs; i++) {
            struct fs4_toc_info *itoc_info_p = &imageOps._fs4ImgInfo.dtocArr.tocArr[i];
            struct cx5fw_itoc_entry *toc_entry = &itoc_info_p->toc_entry;
            if (!writeImageEx(
                    burnParams.progressFuncEx,
                    burnParams.progressUserData,
                    burnParams.progressFunc,
                    toc_entry->flash_addr << 2,
                        &(itoc_info_p->section_data[0]),
                        itoc_info_p->section_data.size(),
                        true,
                        true,
                        total_img_size,
                        alreadyWrittenSz)) {
                return false;
            }
            alreadyWrittenSz += itoc_info_p->section_data.size();
        }
    }


    if (!f->is_flash()) {
        return true;
    }
    bool IsUpdateSignatures = true;
    switch (this->_fwImgInfo.ext_info.chip_type) {
        case CT_CONNECTX6:
            getExtendedHWPtrs((VerifyCallBack)NULL, imageOps._ioAccess, true);
            break;
        default:
            IsUpdateSignatures = false;
            break;
    }
    if (IsUpdateSignatures) {
        u_int32_t imageOffset = _digest_mdk_ptr;
        if (imageOffset == 0) {
            imageOffset = _digest_recovery_key_ptr;
        }
        if (imageOffset != 0) {
            if (!_signatureMngr->AddSignature(_ioAccess->getMfileObj(), &imageOps, f, imageOffset)) {
        return false;
    }
        }
    }
    // Write new signature
    data8 = new u_int8_t[FS3_FW_SIGNATURE_SIZE];
    imageOps._imageCache.get(data8, 0, FS3_FW_SIGNATURE_SIZE);
    if (!writeImageEx(
            burnParams.progressFuncEx,
            burnParams.progressUserData,
            burnParams.progressFunc,
            new_image_start,
                data8,
                FS3_FW_SIGNATURE_SIZE,
                true,
                true,
                total_img_size,
                alreadyWrittenSz)) {
        delete[] data8;
        return false;
    }
    delete[] data8;

    return DoAfterBurnJobs(_fs4_magic_pattern, imageOps, burnParams, f,
                           new_image_start, is_curr_image_in_odd_chunks);
}

bool Fs4Operations::FsBurnAux(FwOperations *imgops, ExtBurnParams& burnParams)
{
    bool devIntQueryRes;
    bool rc;
    Fs4Operations& imageOps = *((Fs4Operations *) imgops);

    if (imageOps.FwType() != FIT_FS4) {
        return errmsg(MLXFW_IMAGE_FORMAT_ERR, "FW image type is not compatible with device (FS4)");
    }

    devIntQueryRes = FsIntQueryAux();

    if (!devIntQueryRes && burnParams.burnFailsafe) {
        return false;
    }

    //For image we execute full verify to bring all the information needed for ROM Patch
    if (!imageOps.FsIntQueryAux(true, false)) {
        return false;
    }

    //Check Matching device ID
    if (!burnParams.noDevidCheck && _ioAccess->is_flash()) {
        if (imageOps._fwImgInfo.supportedHwIdNum) {
            if (!CheckMatchingHwDevId(_ioAccess->get_dev_id(),
                                      _ioAccess->get_rev_id(),
                                      imageOps._fwImgInfo.supportedHwId,
                                      imageOps._fwImgInfo.supportedHwIdNum)) {
                return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR,
                              "Device/Image mismatch: %s\n", this->err());
            }
            if (burnParams.burnFailsafe == false &&
                !CheckMatchingBinning(_ioAccess->get_dev_id(),
                                      _ioAccess->get_bin_id(),
                                      imageOps._fwImgInfo.ext_info.dev_type)) {
                // we check Chip Bin information only on failsafe burn
                // during Firmware update flow - PSID will ensure a correct match.
                return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR,
                              "Device/Image mismatch: %s\n", this->err());
            }
        } else {
            //No supported HW IDs (problem with the image ?)
            return errmsg(MLXFW_DEVICE_IMAGE_MISMATCH_ERR,
                          "No supported devices were found in the FW image.");
        }
    }

    if (!burnParams.burnFailsafe) {
        //Some checks in case we burn in a non-failsafe manner and attempt to
        // integrate existing device Data sections from device.
        if (!burnParams.useImgDevData) {
            //We will take device data section from device: perform some checks
            if (_fs4ImgInfo.dtocArr.tocArrayAddr == 0) {
                return errmsg("Cannot extract device data sections: "
                              "Invalid DTOC section. "
                              "Please ignore extracting device data sections.");
            }
            if (_badDevDataSections) {
                return errmsg("Cannot integrate device data sections: "
                              "Device data sections are corrupted. "
                              "Please ignore extracting device data sections.");
            }
        } else {
            //We will take device data sections from image: make sure device is not write protected
            if (_ioAccess->is_flash()) {
                FBase *origFlashObj = (FBase *) NULL;
                if (!((Flash *)_ioAccess)->get_ignore_cache_replacment()) {
                    origFlashObj = _ioAccess;
                    _fwParams.ignoreCacheRep = 1;
                    if (!FwOperations::FwAccessCreate(_fwParams, &_ioAccess)) {
                        _ioAccess = origFlashObj;
                        _fwParams.ignoreCacheRep = 0;
                        return errmsg(MLXFW_OPEN_OCR_ERR,
                                      "Failed to open device for direct flash access");
                    }
                }

                if (((Flash *)_ioAccess)->is_flash_write_protected()) {
                    FLASH_RESTORE(origFlashObj);
                    return errmsg("Cannot burn device data sections, "
                                  "Flash is write protected.");
                }

                FLASH_RESTORE(origFlashObj);
            }
        }
    }

    if (devIntQueryRes && !CheckPSID(imageOps, burnParams.allowPsidChange)) {
        return false;
    }

    if (burnParams.burnFailsafe) {
        if (!CheckAndDealWithChunkSizes(_fwImgInfo.cntxLog2ChunkSize, imageOps._fwImgInfo.cntxLog2ChunkSize)) {
            return false;
        }

        // Check if the burnt FW version is OK
        if (!CheckFwVersion(imageOps, burnParams.ignoreVersionCheck)) {
            return false;
        }

        // Check TimeStamp
        if (!TestAndSetTimeStamp(imgops)) {
            return false;
        }

        // ROM patchs
        if ((burnParams.burnRomOptions == ExtBurnParams::BRO_FROM_DEV_IF_EXIST) &&
            _fwImgInfo.ext_info.roms_info.exp_rom_found) {
            std::vector<u_int8_t> romSect = _romSect;
            TOCPUn((u_int32_t *)romSect.data(), romSect.size() >> 2);
            if (!imageOps.Fs4AddSectionAux(FS3_ROM_CODE, INITOCENTRY, 0,
                                           (u_int32_t *)romSect.data(), romSect.size())) {
                return errmsg(MLXFW_ROM_UPDATE_IN_IMAGE_ERR,
                              "failed to update ROM in image. %s", imageOps.err());
            }
        }

        // Image vsd patch
        if (!burnParams.useImagePs &&
            (burnParams.vsdSpecified || burnParams.useDevImgInfo)) {
            // get image info section :
            struct fs4_toc_info *imageInfoToc = (struct fs4_toc_info *)NULL;
            if (!imageOps.Fs4GetItocInfo(imageOps._fs4ImgInfo.itocArr.tocArr,
                                         imageOps._fs4ImgInfo.itocArr.numOfTocs,
                                         FS3_IMAGE_INFO, imageInfoToc)) {
                return errmsg(MLXFW_GET_SECT_ERR,
                              "failed to get Image Info section.");
            }

            std::vector<u_int8_t> imageInfoSect = imageInfoToc->section_data;

            if (burnParams.vsdSpecified) {
                struct cibfw_image_info image_info;
                cibfw_image_info_unpack(&image_info, &imageInfoSect[0]);
                strncpy(image_info.vsd, burnParams.userVsd, VSD_LEN);
                cibfw_image_info_pack(&image_info, &imageInfoSect[0]);
            }

            if (burnParams.useDevImgInfo) {
                // update PSID, name and description in image info
                struct tools_open_image_info tools_image_info;
                tools_open_image_info_unpack(&tools_image_info, &imageInfoSect[0]);
                strncpy(tools_image_info.psid, _fwImgInfo.ext_info.psid,
                        PSID_LEN + 1);
                strncpy(tools_image_info.name, _fs3ImgInfo.ext_info.name,
                        NAME_LEN);
                strncpy(tools_image_info.description,
                        _fs3ImgInfo.ext_info.description, DESCRIPTION_LEN);
                tools_open_image_info_pack(&tools_image_info, &imageInfoSect[0]);
            }

            //update image info toc and section
            if (!Fs4UpdateItocInfo(imageInfoToc,
                                   imageInfoToc->toc_entry.size,
                                   imageInfoSect)) {
                return false;
            }
            //update the toc in the cache
            imageOps.Fs3UpdateImgCache(imageInfoToc->data,
                                       imageInfoToc->entry_addr,
                                       CX5FW_ITOC_ENTRY_SIZE);
            //update the section in the cache
            imageOps.Fs3UpdateImgCache(imageInfoToc->section_data.data(),
                                       imageInfoToc->toc_entry.flash_addr << 2,
                                       imageInfoToc->toc_entry.size * 4);
        }
    }

    rc = BurnFs4Image(imageOps, burnParams);

    return rc;
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                                   fs3_section_t sect_type, struct fs4_toc_info *&curr_toc)
{
    int tocIndex;
    return Fs4GetItocInfo(tocArr, num_of_itocs, sect_type, curr_toc, tocIndex);
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                                   fs3_section_t sect_type, struct fs4_toc_info *&curr_toc, int& toc_index)
{
    for (int i = 0; i < num_of_itocs; i++) {
        struct fs4_toc_info *itoc_info = &tocArr[i];
        if (itoc_info->toc_entry.type == sect_type) {
            curr_toc =  itoc_info;
            toc_index = i;
            return true;
        }
    }
    return errmsg("TOC entry type: %s (%d) not found", GetSectionNameByType(sect_type), sect_type);
}

bool Fs4Operations::Fs4GetItocInfo(struct fs4_toc_info  *tocArr, int num_of_itocs,
                                   fs3_section_t sect_type, vector<struct fs4_toc_info *>& curr_toc)
{
    for (int i = 0; i < num_of_itocs; i++) {
        struct fs4_toc_info *itoc_info = &tocArr[i];
        if (itoc_info->toc_entry.type == sect_type) {
            curr_toc.push_back(itoc_info);
        }
    }
    return true;
}

bool Fs4Operations::Fs4UpdateMfgUidsSection(struct fs4_toc_info *curr_toc,
                                            std::vector<u_int8_t>  section_data, fs3_uid_t base_uid,
                                            std::vector<u_int8_t>  &newSectionData)
{
    struct cibfw_mfg_info cib_mfg_info;
    struct cx4fw_mfg_info cx4_mfg_info;
    (void)curr_toc;
    cibfw_mfg_info_unpack(&cib_mfg_info, (u_int8_t *)&section_data[0]);

    if (cib_mfg_info.major_version == 0) {
        if (!Fs3ChangeUidsFromBase(base_uid, cib_mfg_info.guids)) {
            return false;
        }
    } else if (cib_mfg_info.major_version == 1) {
        cx4fw_mfg_info_unpack(&cx4_mfg_info, (u_int8_t *)&section_data[0]);
        if (!Fs3ChangeUidsFromBase(base_uid, cx4_mfg_info.guids)) {
            return false;
        }
    } else {
        return errmsg("Unknown MFG_INFO format version (%d.%d).", cib_mfg_info.major_version, cib_mfg_info.minor_version);
    }
    newSectionData = section_data;

    if (cib_mfg_info.major_version == 1) {
        cx4fw_mfg_info_pack(&cx4_mfg_info, (u_int8_t *)&newSectionData[0]);
    } else {
        cibfw_mfg_info_pack(&cib_mfg_info, (u_int8_t *)&newSectionData[0]);
    }
    return true;
}

bool Fs4Operations::Fs4ChangeUidsFromBase(fs3_uid_t base_uid, struct cx5fw_guids& guids)
{
    /*
     * on ConnectX4 we derrive guids from base_guid and macs from base_mac
     */
    u_int64_t base_guid_64;
    u_int64_t base_mac_64;
    if (!base_uid.use_pp_attr) {
        return errmsg("Expected per port attributes to be specified");
    }

    base_guid_64 = base_uid.base_guid_specified ? GUID_TO_64(base_uid.base_guid) : guids.guids.uid;
    base_mac_64 = base_uid.base_mac_specified ? GUID_TO_64(base_uid.base_mac) : guids.macs.uid;
    if (base_uid.set_mac_from_guid && base_uid.base_guid_specified) {
        // in case we derrive mac from guid
        base_mac_64 = (((u_int64_t)base_uid.base_guid.l & 0xffffff) | (((u_int64_t)base_uid.base_guid.h & 0xffffff00) << 16));
    }

    guids.guids.uid = base_guid_64;
    guids.guids.num_allocated = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? base_uid.num_of_guids_pp[0] : guids.guids.num_allocated;
    guids.guids.step = base_uid.step_size_pp[0] != DEFAULT_STEP ? base_uid.step_size_pp[0] : guids.guids.step;

    guids.macs.uid = base_mac_64;
    guids.macs.num_allocated = base_uid.num_of_guids_pp[0] != DEFAULT_GUID_NUM ? base_uid.num_of_guids_pp[0] : guids.macs.num_allocated;
    guids.macs.step = base_uid.step_size_pp[0] != DEFAULT_STEP ? base_uid.step_size_pp[0] : guids.macs.step;
    return true;
}

bool Fs4Operations::Fs4UpdateUidsSection(std::vector<u_int8_t>  section_data,
                                         fs3_uid_t base_uid, std::vector<u_int8_t>  &newSectionData)
{
    struct cx5fw_device_info dev_info;

    cx5fw_device_info_unpack(&dev_info, (u_int8_t *)&section_data[0]);

    if (!Fs4ChangeUidsFromBase(base_uid, dev_info.guids)) {
        return false;
    }

    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;

    newSectionData = section_data;

    cx5fw_device_info_pack(&dev_info, (u_int8_t *)&newSectionData[0]);
    return true;
}

bool Fs4Operations::Fs4UpdateVsdSection(std::vector<u_int8_t>  section_data, char *user_vsd,
                                        std::vector<u_int8_t>  &newSectionData)
{
    struct cx5fw_device_info dev_info;

    cx5fw_device_info_unpack(&dev_info, (u_int8_t *)&section_data[0]);
    memset(dev_info.vsd, 0, sizeof(dev_info.vsd));
    strncpy(dev_info.vsd, user_vsd, TOOLS_ARR_SZ(dev_info.vsd) - 1);
    newSectionData = section_data;
    dev_info.signature0 = DEV_INFO_SIG0;
    dev_info.signature1 = DEV_INFO_SIG1;
    dev_info.signature2 = DEV_INFO_SIG2;
    dev_info.signature3 = DEV_INFO_SIG3;
    cx5fw_device_info_pack(&dev_info, (u_int8_t *)&newSectionData[0]);
    return true;
}


bool Fs4Operations::Fs4UpdateVpdSection(struct fs4_toc_info *curr_toc, char *vpd,
                                        std::vector<u_int8_t>  &newSectionData)
{
    int vpd_size = 0;
    u_int8_t *vpd_data = (u_int8_t *)NULL;

    if (!ReadImageFile(vpd, vpd_data, vpd_size)) {
        return false;
    }
    if (vpd_size % 4) {
        delete[] vpd_data;
        return errmsg("Size of VPD file: %d is not 4-byte aligned!", vpd_size);
    }

    //check if vpd exceeds the dtoc array
    u_int32_t vpdAddress = curr_toc->toc_entry.flash_addr << 2;
    if (vpdAddress + vpd_size >=
        (_ioAccess->get_size() - FS4_DEFAULT_SECTOR_SIZE)) {
        delete[] vpd_data;
        return errmsg("VPD data exceeds dtoc array, max VPD size: 0x%x bytes",
                      _ioAccess->get_size() - vpdAddress - 1);
    }
    GetSectData(newSectionData, (u_int32_t *)vpd_data, vpd_size);
    curr_toc->toc_entry.size = vpd_size / 4;
    delete[] vpd_data;
    return true;
}

bool Fs4Operations::Fs4ReburnSection(u_int32_t newSectionAddr,
                                     u_int32_t newSectionSize, std::vector<u_int8_t>  newSectionData, const char *msg, PrintCallBack callBackFunc)
{
    char message[127];

    sprintf(message, "Updating %-4s section - ", msg);

    PRINT_PROGRESS(callBackFunc, message);


    if (!writeImage((ProgressCallBack)NULL, newSectionAddr, (u_int8_t *)&newSectionData[0], newSectionSize, true, true)) {
        PRINT_PROGRESS(callBackFunc, (char *)"FAILED\n");
        return false;
    }

    PRINT_PROGRESS(callBackFunc, (char *)"OK\n");

    return true;
}

bool Fs4Operations::Fs4ReburnTocSection(bool isDtoc, PrintCallBack callBackFunc)
{
    // Update new TOC section
    if (isDtoc) {
        if (!reburnDTocSection(callBackFunc)) {
            return false;
        }
    } else {
        if (!reburnITocSection(callBackFunc, _ioAccess->is_flash())) {
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
    u_int32_t tocSize = (_fs4ImgInfo.dtocArr.numOfTocs + 1) * CX5FW_ITOC_ENTRY_SIZE + CX5FW_ITOC_HEADER_SIZE;
    u_int8_t *p = new u_int8_t[tocSize];
    memcpy(p, _fs4ImgInfo.dtocArr.tocHeader, CIBFW_ITOC_HEADER_SIZE);
    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++) {
        struct fs4_toc_info *curr_itoc = &_fs4ImgInfo.dtocArr.tocArr[i];
        memcpy(p + CX5FW_ITOC_HEADER_SIZE + i * CX5FW_ITOC_ENTRY_SIZE,
               curr_itoc->data,
               CX5FW_ITOC_ENTRY_SIZE);
    }
    memset(&p[tocSize] - CX5FW_ITOC_ENTRY_SIZE, FS3_END, CX5FW_ITOC_ENTRY_SIZE);

    PRINT_PROGRESS(callBackFunc, (char *)"Updating TOC section - ");
    bool rc = writeImage((ProgressCallBack)NULL, tocAddr, p, tocSize, true, true);
    delete[] p;
    if (!rc) {
        PRINT_PROGRESS(callBackFunc, (char *)"FAILED\n");
        return false;
    }
    PRINT_PROGRESS(callBackFunc, (char *)"OK\n");

    return true;
}

bool Fs4Operations::reburnITocSection(PrintCallBack callBackFunc, bool isFailSafe)
{
    // Itoc section is failsafe (two sectors after boot section are reserved for itoc entries)
    u_int32_t sector_size = FS3_DEFAULT_SECTOR_SIZE;
    u_int32_t oldITocAddr = _fs4ImgInfo.itocArr.tocArrayAddr;
    u_int32_t newITocAddr = oldITocAddr;
    if (isFailSafe) {
        newITocAddr = (_fs4ImgInfo.firstItocArrayIsEmpty) ?
                      (_fs4ImgInfo.itocArr.tocArrayAddr - sector_size) :
                      (_fs4ImgInfo.itocArr.tocArrayAddr + sector_size);
    }
    // Update new ITOC
    u_int32_t tocSize = (_fs4ImgInfo.itocArr.numOfTocs + 1) * CX5FW_ITOC_ENTRY_SIZE + CX5FW_ITOC_HEADER_SIZE;
    u_int8_t *p = new u_int8_t[tocSize];
    memcpy(p, _fs4ImgInfo.itocArr.tocHeader, CIBFW_ITOC_HEADER_SIZE);
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++) {
        struct fs4_toc_info *curr_itoc = &_fs4ImgInfo.itocArr.tocArr[i];
        memcpy(p + CX5FW_ITOC_HEADER_SIZE + i * CX5FW_ITOC_ENTRY_SIZE,
               curr_itoc->data,
               CX5FW_ITOC_ENTRY_SIZE);
    }
    memset(&p[tocSize] - CX5FW_ITOC_ENTRY_SIZE, FS3_END, CX5FW_ITOC_ENTRY_SIZE);

    PRINT_PROGRESS(callBackFunc, (char *)"Updating TOC section - ");
    bool rc = writeImage((ProgressCallBack)NULL, newITocAddr, p, tocSize, true, true);
    delete[] p;
    if (!rc) {
        PRINT_PROGRESS(callBackFunc, (char *)"FAILED\n");
        return false;
    }
    PRINT_PROGRESS(callBackFunc, (char *)"OK\n");

    u_int32_t zeros = 0;
    if (isFailSafe) {
        PRINT_PROGRESS(callBackFunc, (char *)"Restoring signature   - ");
        if (!writeImage((ProgressCallBack)NULL, oldITocAddr, (u_int8_t *)&zeros, 4, false, true)) {
            PRINT_PROGRESS(callBackFunc, (char *)"FAILED\n");
            return false;
        }
        PRINT_PROGRESS(callBackFunc, (char *)"OK\n");
    }
    return true;
}

bool Fs4Operations::Fs4UpdateItocInfo(struct fs4_toc_info *curr_toc,
                                      u_int32_t NewSectSize, std::vector<u_int8_t>&  newSectionData)
{
    u_int8_t tocEntryBuff[CX5FW_ITOC_ENTRY_SIZE];

    curr_toc->toc_entry.size = NewSectSize;
    curr_toc->section_data = newSectionData;

    if (curr_toc->toc_entry.crc == INITOCENTRY) {
        curr_toc->toc_entry.section_crc = CalcImageCRC((u_int32_t *)&newSectionData[0], curr_toc->toc_entry.size);
    } else if (curr_toc->toc_entry.crc == INSECTION) {
        u_int32_t newSectionCRC = CalcImageCRC((u_int32_t *)&newSectionData[0], curr_toc->toc_entry.size - 1);
        ((u_int32_t *)curr_toc->section_data.data())[curr_toc->toc_entry.size - 1] = newSectionCRC;
        ((u_int32_t *)newSectionData.data())[curr_toc->toc_entry.size - 1] = TOCPU1(newSectionCRC);
    }

    memset(tocEntryBuff, 0, CX5FW_ITOC_ENTRY_SIZE);
    cx5fw_itoc_entry_pack(&curr_toc->toc_entry, tocEntryBuff);

    u_int32_t newEntryCRC = CalcImageCRC((u_int32_t *)tocEntryBuff, (TOC_ENTRY_SIZE / 4) - 1);
    curr_toc->toc_entry.itoc_entry_crc = newEntryCRC;

    memset(curr_toc->data, 0, CX5FW_ITOC_ENTRY_SIZE);
    cx5fw_itoc_entry_pack(&curr_toc->toc_entry, curr_toc->data);

    return true;
}

bool Fs4Operations::isDTocSection(fs3_section_t sect_type, bool& isDtoc)
{
    switch ((int)sect_type) {
    case FS3_MFG_INFO:
    case FS3_DEV_INFO:
    case FS3_VPD_R0:
        isDtoc = true;
        break;

    case FS3_PUBLIC_KEYS_4096:
    case FS3_PUBLIC_KEYS_2048:
    case FS3_IMAGE_SIGNATURE_256:
    case FS3_IMAGE_SIGNATURE_512:
    case FS3_FORBIDDEN_VERSIONS:
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
    struct fs4_toc_info  *tocArr;
    u_int32_t numOfTocs;
    struct fs4_toc_info *curr_toc = (fs4_toc_info *)NULL;
    int tocIndex = 0;

    if (!isDTocSection(sectType, isDtoc)) {
        return false;
    }

    if (isDtoc) {
        tocArr = _fs4ImgInfo.dtocArr.tocArr;
        numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;
    } else {
        tocArr = _fs4ImgInfo.itocArr.tocArr;
        numOfTocs = _fs4ImgInfo.itocArr.numOfTocs;
    }
    if (!Fs4GetItocInfo(tocArr, numOfTocs, sectType, curr_toc, tocIndex)) {
        return false;
    }
    return true;
}

bool Fs4Operations::Fs3UpdateSection(void *new_info, fs3_section_t sect_type, bool is_sect_failsafe, CommandType cmd_type, PrintCallBack callBackFunc)
{
    (void) cmd_type;
    struct fs4_toc_info *curr_toc = (fs4_toc_info *)NULL;
    struct fs4_toc_info *old_toc = (fs4_toc_info *)NULL;
    std::vector<u_int8_t> newSection;
    u_int32_t newSectionAddr;
    const char *type_msg;
    struct fs4_toc_info  *tocArr;
    u_int32_t numOfTocs;
    u_int32_t zeroes = 0;
    bool isDtoc;
    // init sector to read
    _readSectList.push_back(sect_type);
    if (!FsIntQueryAux()) {
        _readSectList.pop_back();
        return false;
    }
    _readSectList.pop_back();

    is_sect_failsafe = (sect_type == FS3_DEV_INFO);

    if (!isDTocSection(sect_type, isDtoc)) {
        return false;
    }

    if (isDtoc) {
        tocArr = _fs4ImgInfo.dtocArr.tocArr;
        numOfTocs = _fs4ImgInfo.dtocArr.numOfTocs;
    } else {
        tocArr = _fs4ImgInfo.itocArr.tocArr;
        numOfTocs = _fs4ImgInfo.itocArr.numOfTocs;
    }

    if (is_sect_failsafe) {
        vector<struct fs4_toc_info *> tocs;
        //find first valid section
        if (!Fs4GetItocInfo(tocArr, numOfTocs, sect_type, tocs)) {
            return false;
        }
        if (tocs.size() < 2) {
            PRINT_PROGRESS(callBackFunc, (char *)"FAILED\n");
            return false;
        }
        for (size_t i = 0; i < tocs.size(); i++) {
            if (CheckDevInfoSignature((u_int32_t *)(tocs[i]->section_data.data()))) {
                old_toc = tocs[i];
                //find the second section (valid or not valid, does not matter)
                if (i == 0) {
                    curr_toc = tocs[1];
                } else {
                    curr_toc = tocs[0];
                }
                break;
            }
        }
        if (!old_toc) {
            return errmsg("Bad DEV_INFO signature.");
        }
    } else {
        int tocIndex = 0;
        if (!Fs4GetItocInfo(tocArr, numOfTocs, sect_type, curr_toc, tocIndex)) {
            return false;
        }
        if (sect_type == FS3_VPD_R0 && ((u_int32_t)tocIndex) != numOfTocs - 1) {
            return errmsg("VPD Section is not the last device section");
        }
    }

    if (!curr_toc) {
        return errmsg("Couldn't find TOC array.");
    }

    if (sect_type == FS3_MFG_INFO) {
        fs3_uid_t base_uid = *(fs3_uid_t *)new_info;
        type_msg = "GUID";
        if (!Fs4UpdateMfgUidsSection(curr_toc, curr_toc->section_data, base_uid,
                                     newSection)) {
            return false;
        }
    } else if (sect_type == FS3_DEV_INFO) {
        if (cmd_type == CMD_SET_GUIDS) {
            fs3_uid_t base_uid = *(fs3_uid_t *)new_info;
            type_msg = "GUID";
            if (!Fs4UpdateUidsSection(old_toc->section_data, base_uid, newSection)) {
                return false;
            }
        } else if (cmd_type == CMD_SET_VSD) {
            char *user_vsd = (char *)new_info;
            type_msg = "VSD";
            if (!Fs4UpdateVsdSection(old_toc->section_data,
                                     user_vsd,
                                     newSection)) {
                return false;
            }
        } else {
            // We shouldnt reach here EVER
            type_msg = (char *)"Unknown";
        }
    } else if (sect_type == FS3_VPD_R0) {
        char *vpd_file = (char *)new_info;
        type_msg = "VPD";
        if (!Fs4UpdateVpdSection(curr_toc, vpd_file, newSection)) {
            return false;
        }
    } else if (sect_type == FS3_IMAGE_SIGNATURE_256 && cmd_type == CMD_SET_SIGNATURE) {
        vector<u_int8_t> sig((u_int8_t *)new_info, (u_int8_t *)new_info + CX4FW_IMAGE_SIGNATURE_256_SIZE);
        type_msg = "SIGNATURE";
        newSection.resize(CX4FW_IMAGE_SIGNATURE_256_SIZE);
        memcpy(newSection.data(), sig.data(), CX4FW_IMAGE_SIGNATURE_256_SIZE);
        //Check if padding is needed, by comparing with the real size in the itoc entry:
        u_int32_t sizeInItocEntry = curr_toc->toc_entry.size << 2;
        if (sizeInItocEntry > CX4FW_IMAGE_SIGNATURE_256_SIZE) {
            for (unsigned int l = 0; l < sizeInItocEntry - CX4FW_IMAGE_SIGNATURE_256_SIZE; l++) {
                newSection.push_back(0x0);
            }
        }
    } else if (sect_type == FS3_IMAGE_SIGNATURE_512 && cmd_type == CMD_SET_SIGNATURE) {
        vector<u_int8_t> sig((u_int8_t *)new_info, (u_int8_t *)new_info + CX4FW_IMAGE_SIGNATURE_512_SIZE);
        type_msg = "SIGNATURE";
        newSection.resize(CX4FW_IMAGE_SIGNATURE_512_SIZE);
        memcpy(newSection.data(), sig.data(), CX4FW_IMAGE_SIGNATURE_512_SIZE);
        u_int32_t sizeInItocEntry = curr_toc->toc_entry.size << 2;
        if (sizeInItocEntry > CX4FW_IMAGE_SIGNATURE_256_SIZE) {
            for (unsigned int l = 0; l < sizeInItocEntry - CX4FW_IMAGE_SIGNATURE_256_SIZE; l++) {
                newSection.push_back(0x0);
            }
        }
    } else if (sect_type == FS3_PUBLIC_KEYS_2048 && cmd_type == CMD_SET_PUBLIC_KEYS) {
        char *publickeys_file = (char *)new_info;
        type_msg = "PUBLIC KEYS";
        if (!Fs3UpdatePublicKeysSection(curr_toc->toc_entry.size, publickeys_file, newSection)) {
            return false;
        }
    } else if (sect_type == FS3_PUBLIC_KEYS_4096 && cmd_type == CMD_SET_PUBLIC_KEYS) {
        char *publickeys_file = (char *)new_info;
        type_msg = "PUBLIC KEYS 4096";
        if (!Fs3UpdatePublicKeysSection(curr_toc->toc_entry.size, publickeys_file, newSection)) {
            return false;
        }
    } else if (sect_type == FS3_FORBIDDEN_VERSIONS && cmd_type == CMD_SET_FORBIDDEN_VERSIONS) {
        char *forbiddenVersions_file = (char *)new_info;
        type_msg = "Forbidden Versions";
        if (!Fs3UpdateForbiddenVersionsSection(curr_toc->toc_entry.size, forbiddenVersions_file, newSection)) {
            return false;
        }
    } else {
        return errmsg("Section type %s is not supported\n", GetSectionNameByType(sect_type));
    }

    newSectionAddr = curr_toc->toc_entry.flash_addr << 2;

    if (!Fs4UpdateItocInfo(curr_toc, curr_toc->toc_entry.size, newSection)) {
        return false;
    }

    if (!Fs4ReburnSection(newSectionAddr, curr_toc->toc_entry.size * 4, newSection, type_msg, callBackFunc)) {
        return false;
    }

    if (sect_type != FS3_DEV_INFO) {
        if (!Fs4ReburnTocSection(isDtoc, callBackFunc)) {
            return false;
        }
    }

    if (is_sect_failsafe) {
        if (!writeImage((ProgressCallBack)NULL,
                        old_toc->toc_entry.flash_addr << 2,
                        (u_int8_t *)&zeroes, sizeof(zeroes), isDtoc, true)) {
            return false;
        }
    }

    return true;
}

u_int32_t Fs4Operations::getAbsAddr(fs4_toc_info *toc)
{
    return ((toc->toc_entry.flash_addr << 2) + _fwImgInfo.imgStart);
}

u_int32_t Fs4Operations::getAbsAddr(fs4_toc_info *toc, u_int32_t imgStart)
{
    return ((toc->toc_entry.flash_addr << 2) + imgStart);
}

bool Fs4Operations::FwShiftDevData(PrintCallBack progressFunc)
{
    // avoid compiler warrnings
    (void)progressFunc;
    return errmsg("Shifting device data sections is not supported in FS4 image format.");
}

#define OPEN_OCR(origFlashObj) do { \
        origFlashObj = _ioAccess; \
        _fwParams.ignoreCacheRep = 1; \
        if (!FwOperations::FwAccessCreate(_fwParams, &_ioAccess)) { \
            _ioAccess = origFlashObj; \
            _fwParams.ignoreCacheRep = 0; \
            return errmsg("Failed to open device for direct flash access"); \
        } \
} while (0)

bool Fs4Operations::FwCalcMD5(u_int8_t md5sum[16])
{
#if defined(UEFI_BUILD) || defined(NO_OPEN_SSL)
    (void)md5sum;
    return errmsg("Operation not supported");
#else
    if (!FsIntQueryAux(true, false)) {
        return false;
    }
    // push beggining of image to md5buff
    int sz = FS3_BOOT_START + _fwImgInfo.bootSize;
    std::vector<u_int8_t> md5buff(sz, 0);
    _imageCache.get(&(md5buff[0]), sz);
    // push all non dev data sections to md5buff
    for (unsigned int j = 0; j < TOC_HEADER_SIZE; j++) {
        md5buff.push_back(_imageCache[_fs4ImgInfo.itocArr.tocArrayAddr + j]);
    }
    // push itoc header
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++) {
        // push each non-dev-data section to md5sum buffer
        u_int32_t tocEntryAddr = _fs4ImgInfo.itocArr.tocArr[i].entry_addr;
        u_int32_t tocDataAddr = _fs4ImgInfo.itocArr.tocArr[i].toc_entry.flash_addr << 2;
        u_int32_t tocDataSize =  _fs4ImgInfo.itocArr.tocArr[i].toc_entry.size << 2;
        // itoc entry
        for (unsigned int j = 0; j < TOC_ENTRY_SIZE; j++) {
            md5buff.push_back(_imageCache[tocEntryAddr + j]);
        }
        // itoc data
        for (unsigned int j = 0; j < tocDataSize; j++) {
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

    if (!CheckTocArrConsistency(_fs4ImgInfo.dtocArr, 0)) {
        return false;
    }

    return true;
}

bool Fs4Operations::CheckITocArray()
{
    // Check for inconsistency image burnt on 1st half
    if (!CheckTocArrConsistency(_fs4ImgInfo.itocArr, 0)) {
        return false;
    }

    // Check for inconsistency image burn on second half
    if (!CheckTocArrConsistency(_fs4ImgInfo.itocArr, (1 << _fwImgInfo.cntxLog2ChunkSize))) {
        return false;
    }
    return true;
}

bool Fs4Operations::CheckTocArrConsistency(TocArray& tocArr, u_int32_t imageStartAddr)
{

    u_int32_t sectEndAddr = 0;
    u_int32_t nextSectStrtAddr = 0;

    //Sort the tocs
    std::vector<struct fs4_toc_info *> sortedTocVec(tocArr.numOfTocs);
    for (int i = 0; i < tocArr.numOfTocs; i++) {
        sortedTocVec[i] = &(tocArr.tocArr[i]);
    }
    std::sort(sortedTocVec.begin(), sortedTocVec.end(), TocComp(imageStartAddr));

    std::vector<struct fs4_toc_info *>::iterator it = sortedTocVec.begin(), itNext = sortedTocVec.begin();
    itNext++;
    for (; itNext != sortedTocVec.end(); it++, itNext++) {
        sectEndAddr = getAbsAddr(*it, imageStartAddr) + ((*it)->toc_entry.size << 2) - 1;
        nextSectStrtAddr = getAbsAddr(*itNext, imageStartAddr);
        if (sectEndAddr >= nextSectStrtAddr) {
            return errmsg(
                "Inconsistency found in TOC. %s(0x%x) section will potentially overwrite %s(0x%x) section.", \
                GetSectionNameByType((*it)->toc_entry.type),
                (*it)->toc_entry.type, \
                GetSectionNameByType((*itNext)->toc_entry.type),
                (*itNext)->toc_entry.type);
        }
    }

    return true;
}

u_int32_t Fs4Operations::getImageSize()
{
    return _fwImgInfo.lastImageAddr - _fwImgInfo.imgStart;
}

void Fs4Operations::maskIToCSection(u_int32_t itocType, vector<u_int8_t>& img)
{
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++) {
        if (_fs4ImgInfo.itocArr.tocArr[i].toc_entry.type == itocType) {
            u_int32_t tocEntryAddr = _fs4ImgInfo.itocArr.tocArr[i].entry_addr;
            u_int32_t tocEntryDataAddr = _fs4ImgInfo.itocArr.tocArr[i].toc_entry.flash_addr << 2;
            memset(img.data() + tocEntryAddr, 0xFF, TOC_ENTRY_SIZE);
            memset(img.data() + tocEntryDataAddr, 0xFF, _fs4ImgInfo.itocArr.tocArr[i].toc_entry.size << 2);
        }
    }
}

void Fs4Operations::maskDevToc(vector<u_int8_t>& img)
{
    //no device tocs in the itoc
    (void)img;
    return;
}

bool Fs4Operations::FwSetTimeStamp(struct tools_open_ts_entry& timestamp,
                                   struct tools_open_fw_version& fwVer)
{
    CHECK_IF_FS4_FILE_FOR_TIMESTAMP_OP()

    return Fs3Operations::FwSetTimeStamp(timestamp, fwVer);
}

bool Fs4Operations::FwQueryTimeStamp(struct tools_open_ts_entry& timestamp,
                                     struct tools_open_fw_version& fwVer, bool queryRunning)
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
    for (int i = 0; i < _fs4ImgInfo.itocArr.numOfTocs; i++) {
        struct fs4_toc_info *toc = &_fs4ImgInfo.itocArr.tocArr[i];
        if (toc->toc_entry.type == sectType) {
            size = toc->toc_entry.size << 2;
            offset = toc->toc_entry.flash_addr << 2;
            return true;
        }
    }

    for (int i = 0; i < _fs4ImgInfo.dtocArr.numOfTocs; i++) {
        struct fs4_toc_info *toc = &_fs4ImgInfo.dtocArr.tocArr[i];
        if (toc->toc_entry.type == sectType) {
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
    if(key_str.size() != correct_key_len * 2) {
        res = false;
    }
    else if(key_str.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos) {
        res =  false;
    }
    return res;
}
#endif

bool Fs4Operations::FwSignWithHmac(const char *keyFile)
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    vector<u_int8_t> critical, non_critical, bin_data, digest;
    u_int32_t physAddr = _authentication_start_ptr;
    if (_ioAccess->is_flash()) {
        return errmsg( "Adding HMAC not allowed for devices");
    }
    if (!getExtendedHWPtrs((VerifyCallBack)NULL, _ioAccess)) {
        return false;
    }
    const unsigned int s = _authentication_end_ptr - _authentication_start_ptr + 1;

    bin_data.resize(s);
    READBUF((*_ioAccess),
            physAddr,
            bin_data.data(),
            s,
            "Reading data pointed by HW Pointers");

    const int key_len = 64;
    std::ifstream f(keyFile);
    std::stringstream buf;
    buf << f.rdbuf();
    std::string fileContents = buf.str();
    if(!validateHmacKey(fileContents, key_len))
        return errmsg("Key must be of length of 64 bytes, each byte represented with two chars (hex)");
    unsigned char key_buf[key_len + 1];
    std::string num_str = "";
    size_t file_content_size = fileContents.size();
    for (size_t i = 0; i < file_content_size; i++) {
        if (i % 2 != 0) {
            num_str += fileContents[i];
            key_buf[i / 2] = strtol(num_str.c_str(), NULL, 16);
        }
        else {
            num_str = fileContents[i];
        }
    }
    vector<u_int8_t> key(key_buf, key_buf + key_len);

    PrepItocSectionsForHmac(critical, non_critical);
    if (!CalcHMAC(key, bin_data, digest)) {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr, digest.data(),
                      digest.size(), true, true, 0, 0)) {
        return false;
    }

    digest.resize(0x0);
    if (!CalcHMAC(key, critical, digest)) {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr + digest.size(), digest.data(),
                      digest.size(), true, true, 0, 0)) {
        return false;
    }

    digest.resize(0);
    if (!CalcHMAC(key, non_critical, digest)) {
        return false;
    }

    if (!writeImageEx((ProgressCallBackEx)NULL, NULL, (ProgressCallBack)NULL, _digest_recovery_key_ptr + 2 * digest.size(), digest.data(),
                      digest.size(), true, true, 0, 0)) {
        return false;
    }

    return true;
#else
    (void)keyFile;
    return errmsg("FwSignWithHmac is not suppported.");
#endif
}

bool Fs4Operations::PrepItocSectionsForHmac(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    if (!FsIntQueryAux(true, false)) {
        return false;
    }

    for (int i = 0; i < this->_fs4ImgInfo.itocArr.numOfTocs; i++) {
        struct fs4_toc_info *itoc_info_p = &this->_fs4ImgInfo.itocArr.tocArr[i];
        struct cx5fw_itoc_entry *toc_entry = &(itoc_info_p->toc_entry);
        if (IsCriticalSection(toc_entry->type))
        {
            critical.reserve(critical.size() + itoc_info_p->section_data.size());
            critical.insert(critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
        }
        else
        {
            non_critical.reserve(non_critical.size() + itoc_info_p->section_data.size());
            non_critical.insert(non_critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
        }
    }
    return true;
}
bool Fs4Operations::PrepItocSectionsForCompare(vector<u_int8_t>& critical, vector<u_int8_t>& non_critical)
{
    for (int i = 0; i < this->_fs4ImgInfo.itocArr.numOfTocs; i++) {
        struct fs4_toc_info *itoc_info_p = &this->_fs4ImgInfo.itocArr.tocArr[i];
        struct cx5fw_itoc_entry *toc_entry = &(itoc_info_p->toc_entry);
        if (IsCriticalSection(toc_entry->type))
        {
            critical.reserve(critical.size() + itoc_info_p->section_data.size());
            critical.insert(critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            //printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n", itoc_info_p->entry_addr, itoc_info_p->toc_entry.type, 
                //(unsigned int)(itoc_info_p->section_data.size() + padding_size), GetSectionNameByType(itoc_info_p->toc_entry.type));
        }
        else
        {
            if (itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_512 || itoc_info_p->toc_entry.type == FS3_IMAGE_SIGNATURE_256) {
                continue;
            }
            //printf("-D- addr  0x%.8x toc type : 0x%.8x  size 0x%.8x name %s\n", itoc_info_p->entry_addr, itoc_info_p->toc_entry.type, (unsigned int)itoc_info_p->section_data.size(), GetSectionNameByType(itoc_info_p->toc_entry.type));
            non_critical.reserve(non_critical.size() + itoc_info_p->section_data.size());
            non_critical.insert(non_critical.end(), itoc_info_p->section_data.begin(), itoc_info_p->section_data.end());
            //currentItoc++;
        }
    }
    return true;
}

bool Fs4Operations::IsCriticalSection(u_int8_t sect_type)
{
    if (sect_type != FS3_PCIE_LINK_CODE && sect_type != FS3_PHY_UC_CMD && sect_type != FS3_HW_BOOT_CFG)
        return false;
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
    return errmsg("HMAC calculation is not implemented\n");
#endif
}

bool Fs4Operations::TocComp::operator()(fs4_toc_info *elem1, fs4_toc_info *elem2)
{
    u_int32_t absAddr1 = (elem1->toc_entry.flash_addr << 2) + _startAdd;
    u_int32_t absAddr2 = (elem2->toc_entry.flash_addr << 2) + _startAdd;
    if (absAddr1 < absAddr2) {
        return true;
    }
    return false;
}

u_int32_t Fs4Operations::TocArray::getSectionsTotalSize()
{
    u_int32_t s = 0;
    for (int i = 0; i < numOfTocs; i++) {
        struct fs4_toc_info *itoc_info_p = &(tocArr[i]);
        struct cx5fw_itoc_entry *toc_entry = &itoc_info_p->toc_entry;
        s += toc_entry->size << 2;
    }
    return s;
}

void Fs4Operations::TocArray::initEmptyTocArrEntry(struct fs4_toc_info * tocArrEntry)
{
    if (!tocArrEntry) {
        return;
    }
    memset(tocArrEntry->data, 0, sizeof(tocArrEntry->data));
    memset(&tocArrEntry->toc_entry, 0, sizeof(tocArrEntry->toc_entry));
    tocArrEntry->entry_addr = 0;
    tocArrEntry->section_data.resize(0);
    return;
}

void Fs4Operations::TocArray::copyTocArrEntry(struct fs4_toc_info * dest, struct fs4_toc_info * src)
{
    if (!src || !dest) {
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
    for (int i = 0; i < MAX_TOCS_NUM; i++) {
        Fs4Operations::TocArray::initEmptyTocArrEntry(&tocArr[i]);
    }
    memset(&tocHeader, 0, sizeof(tocHeader));
}

