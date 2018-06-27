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

#include <reg_access/reg_access.h>

#include "flint_base.h"
#include "aux_tlv_ops.h"

/*
 * ImageTlvOps class implementation
 */


#define AUX_DATA_SIG_SIZE 0x10
#define SIG3 0x080d1522
#define SIG2 0x01020305
#define SIG1 0x6548bc86
#define SIG0 0x4155583a

bool ImageTlvOps::test()
{
    printf("-I- ImageTlvOps Class test");
    u_int32_t data0[] = {0x12345678, 0xabcdef01, 0xab0dab10, 0xcafaba1a, 0x0cafee1e1, 0x12345678, 0x23456789, 0x3456789a};
    u_int32_t data1[] = {0x12345678, 0xabcdef01, 0xab0dab1, 0xcafaba1a, 0x0cafee1e1, 0x12345678, 0x23456789, 0x3456789a};
    u_int8_t data2[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa};
    // run init
    if (!init(true)) {
        printf("-E- failed on init");
    }
    // add all tlvs and update file
    aux_tlv tlv;
    memset(&tlv.hdr, 0x0, sizeof(tlv.hdr));
    tlv.hdr.header_type = 0;
    tlv.hdr.type = 0;
    tlv.hdr.length = 0x10;
    tlv.data.resize(tlv.hdr.length);
    memcpy(&tlv.data[0], data0, tlv.hdr.length);
    addTLV(tlv);

    tlv.hdr.header_type = 1;
    tlv.hdr.type = 0;
    tlv.hdr.length = 0x3;
    tlv.data.resize(tlv.hdr.length);
    memcpy(&tlv.data[0], data1, tlv.hdr.length);
    addTLV(tlv);

    tlv.hdr.header_type = 0;
    tlv.hdr.type = 3;
    tlv.hdr.length = 0xa;
    tlv.data.resize(tlv.hdr.length);
    memcpy(&tlv.data[0], data2, tlv.hdr.length);
    addTLV(tlv);

    if (!updateFile()) {
        printf("-E- failed to update file\n");
    }
    removeTlv(3, 0);
    removeTlv(0, 0);
    removeTlv(0, 1);

    if (!updateFile()) {
        printf("-E- failed to update file\n");
    }
    printf("-I- Done Successfully");

    return true;
}

Tlv_Status_t ImageTlvOps::getFileSize(FILE *fd, long int& fileSize)
{
    // Get the file size:
    if (fseek(fd, 0, SEEK_END) < 0) {
        fclose(fd);
        return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_OPEN_FILE, "Can not get file size for \"%s\"", _fname);
    }
    fileSize = ftell(fd);
    if (fileSize < 0) {
        fclose(fd);
        return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_OPEN_FILE, "Can not get file size for \"%s\"", _fname);
    }
    rewind(fd);
    return TS_OK;
}

Tlv_Status_t ImageTlvOps::init(u_int32_t startPos, bool force)
{
    if (!force && _initialized) {
        return TS_OK;
    }
    long int fsize;
    _tlvSectionFound = false;
    _tlvSectionFilePos = 0;
    _tlvVec.resize(0);

    if (_fname) {
        _rawFileBuff.resize(0);
        FILE *fd = fopen(_fname, "rb");
        if (!fd) {
            return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_OPEN_FILE, "Failed to open file of reading");
        }
        // get file size
        if (getFileSize(fd, fsize)) {
            return TS_FAILED_TO_OPEN_FILE;
        }
        // read the file
        long int readCnt;
        _rawFileBuff.resize(fsize);
        if ((readCnt = fread(&_rawFileBuff[0], 1, fsize, fd)) != fsize) {
            fclose(fd);
            if (readCnt < 0) {
                return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_READ_FILE, "Read error on file \"%s\"", _fname);
            } else {
                return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_READ_FILE, "Read error on file \"%s\" - read only %ld bytes (from %ld)",
                                                 _fname, readCnt, (unsigned long)fsize);
            }
        }
        fclose(fd);
    }
    fsize = _rawFileBuff.size();
    for (long int i = startPos; i < fsize; i += 4) {
        if ((i + 16) > fsize) {
            break; // reached EOF
        }
        std::vector<u_int8_t> possibleSig(_rawFileBuff.begin() + i, _rawFileBuff.begin() + i + 16);
        TOCPUn(&possibleSig[0], 4);
        if (checkSig(possibleSig)) {
            _tlvSectionFound = true;
            _tlvSectionFilePos = i;
        }
    }
    if (_tlvSectionFound) {
        // parse TLVs
        return parseTlvs();
    }
    _initialized = true;
    return TS_OK;

}

Tlv_Status_t ImageTlvOps::resetTlvSection()
{
    if (_tlvSectionFound) {
        _tlvVec.resize(0);
        return updateFile();
    }
    return TS_OK;
}

void ImageTlvOps::addTLV(aux_tlv& tlv)
{
    // remove it if its present then push back
    removeTlv(tlv.hdr.type, tlv.hdr.header_type);
    // calc tlv CRC
    tlv.hdr.crc = calcTlvCrc(tlv);
    _tlvVec.push_back(tlv);
    return;
}

Tlv_Status_t ImageTlvOps::removeTlv(u_int16_t tlvType, u_int8_t headerType)
{
    for (std::vector<aux_tlv>::iterator it = _tlvVec.begin(); it != _tlvVec.end(); it++) {
        if (it->hdr.header_type == headerType && it->hdr.type == tlvType) {
            _tlvVec.erase(it);
            return TS_OK;
        }
    }
    return (Tlv_Status_t)errmsgWCode(TS_TLV_NOT_FOUND, "TLV(0x%x) with type(0x%x) not found", tlvType, headerType);
}

Tlv_Status_t ImageTlvOps::queryTlv(u_int16_t tlvType, u_int8_t headerType, aux_tlv& tlv)
{
    for (std::vector<aux_tlv>::iterator it = _tlvVec.begin(); it != _tlvVec.end(); it++) {
        if (it->hdr.header_type == headerType && it->hdr.type == tlvType) {
            tlv = *it;
            return TS_OK;
        }
    }
    return (Tlv_Status_t)errmsgWCode(TS_TLV_NOT_FOUND, "TLV(0x%x) with type(0x%x) not found", tlvType, headerType);
}

std::vector<aux_tlv> ImageTlvOps::queryTlvs()
{
    return _tlvVec;
}

bool ImageTlvOps::checkSig(std::vector<u_int8_t>& signature)
{
    u_int32_t *sigPtr = (u_int32_t*)&signature[0];
    return *(sigPtr + 3)  == SIG3 && \
           *(sigPtr + 2) == SIG2 && \
           *(sigPtr + 1) == SIG1 && \
           *(sigPtr) == SIG0;
}

Tlv_Status_t ImageTlvOps::updateFile()
{
    std::vector<u_int32_t> signature(4, 0x0);
    signature[3] = SIG3;
    signature[2] = SIG2;
    signature[1] = SIG1;
    signature[0] = SIG0;

    if (_readOnly) {
        return (Tlv_Status_t)errmsgWCode(TS_READ_ONLY_MODE, "Image TLV object is read only.");
    }
    if (!_tlvSectionFound && _tlvVec.size() == 0) { // no tlv section and no tlvs
        // nothing to do
        return TS_OK;
    } else if (_tlvSectionFound && _tlvVec.size() == 0) { // tlv section without tlvs
        // remove signature from file
        _rawFileBuff.resize(_tlvSectionFilePos);
        _tlvSectionFilePos = 0;
        _tlvSectionFound = false;
    } else if (!_tlvSectionFound && _tlvVec.size() != 0) { // no tlv section with tlvs
        // add signature and TLVs
        TOCPUn(&signature[0], 4);
        _tlvSectionFound = true;
        _tlvSectionFilePos = _rawFileBuff.size();
        for (unsigned int i = 0; i < signature.size() << 2; i++) {
            _rawFileBuff.push_back(*(((u_int8_t*)&signature[0]) + i));
        }
        pushTlvsToRawBuffer();
    } else {
        _rawFileBuff.resize(_tlvSectionFilePos + AUX_DATA_SIG_SIZE);
        pushTlvsToRawBuffer();
    }
    return writeBufferAsFile();
}

Tlv_Status_t ImageTlvOps::writeBufferAsFile()
{
    if (_tlvVec.size()) {
        // push end marker
        std::vector<u_int8_t> endMarker(TOOLS_OPEN_AUX_TLV_HEADER_SIZE, 0xff);
        _rawFileBuff.insert(_rawFileBuff.end(), endMarker.begin(), endMarker.end());
    }
    // TODO: check the need to : write the file under a different name then delete original and rename
    FILE *fd = fopen(_fname, "wb");
    if (!fd) {
        return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_OPEN_FILE, "Failed to open file for writing: %s", _fname);
    }
    int cnt = fwrite(&_rawFileBuff[0], 1, _rawFileBuff.size(), fd);
    fclose(fd);
    if (cnt != (int)_rawFileBuff.size()) {
        return (Tlv_Status_t)errmsgWCode(TS_FAILED_TO_WRITE_FILE, "Failed to re-write file: %s", _fname);
    }
    return TS_OK;
}

void ImageTlvOps::pushTlvsToRawBuffer()
{
    // called from updateFile. assuming raw data already contains signature.
    if (_tlvVec.size() != 0) {
        std::vector<u_int8_t> tlvBuffer;
        tlvBuffer.resize(0);
        for (std::vector<aux_tlv>::iterator it = _tlvVec.begin(); it != _tlvVec.end(); it++) {
            // push header
            std::vector<u_int8_t> hdrBuf(TOOLS_OPEN_AUX_TLV_HEADER_SIZE, 0x0);
            tools_open_aux_tlv_header_pack(&(it->hdr), &hdrBuf[0]);
            tlvBuffer.insert(tlvBuffer.end(), hdrBuf.begin(), hdrBuf.end());
            // push data
            tlvBuffer.insert(tlvBuffer.end(), it->data.begin(), it->data.end());
            // pad to DW aligned address with 0x0 if needed
            if (it->data.size() & 3) {
                std::vector<u_int8_t> padding(4 - (it->data.size() & 3), 0x0);
                tlvBuffer.insert(tlvBuffer.end(), padding.begin(), padding.end());
            }
        }
        // update raw buffer and write the file
        _rawFileBuff.insert(_rawFileBuff.end(), tlvBuffer.begin(), tlvBuffer.end());
    }
    return;
}

Tlv_Status_t ImageTlvOps::parseTlvs()
{
    if (!_tlvSectionFound) {
        // nothing to parse
        return TS_OK;
    }

    if (!_tlvSectionFilePos) {
        return (Tlv_Status_t)errmsgWCode(TS_GENERAL_ERROR, "Internal Error. unexpected file position.");
    }

    // while not end TLV or EOF
    u_int32_t nextTlvOffs = _tlvSectionFilePos + AUX_DATA_SIG_SIZE;
    u_int32_t bufferSize = (u_int32_t)_rawFileBuff.size();
    do {
        aux_tlv tlv;
        // read next TLV header
        if (nextTlvOffs == bufferSize) {
            return (Tlv_Status_t)errmsgWCode(TS_TLV_PARSE_ERROR, "failed to parse TLVs : expected to find End marker before end of file");
        }
        if (nextTlvOffs + TOOLS_OPEN_AUX_TLV_HEADER_SIZE > bufferSize) {
            return (Tlv_Status_t)errmsgWCode(TS_TLV_PARSE_ERROR, "failed to parse TLVs : unexpected End of extended data section");
        }
        u_int8_t hdrBuf[TOOLS_OPEN_AUX_TLV_HEADER_SIZE] = {0};
        memcpy(hdrBuf, &_rawFileBuff[nextTlvOffs], TOOLS_OPEN_AUX_TLV_HEADER_SIZE);
        tools_open_aux_tlv_header_unpack(&tlv.hdr, hdrBuf);
        // check for END TLV
        if (tlv.hdr.header_type == 0xf && tlv.hdr.type == 0xff) {
            break;
        }
        // read next TLV data
        if (nextTlvOffs + TOOLS_OPEN_AUX_TLV_HEADER_SIZE + tlv.hdr.length  > bufferSize) {
            return (Tlv_Status_t)errmsgWCode(TS_TLV_PARSE_ERROR, "failed to parse TLVs : unexpected End of extended data section");
        }
        u_int32_t vecSizeDwAligned = ((tlv.hdr.length + 3) / 4) * 4;
        tlv.data.resize(tlv.hdr.length);
        memset(&tlv.data[0], 0x0, tlv.data.size());
        memcpy(&tlv.data[0], &_rawFileBuff[nextTlvOffs + TOOLS_OPEN_AUX_TLV_HEADER_SIZE], tlv.hdr.length);
        if (tlv.hdr.header_type == 0x0) { // only know how to deal with header of type 0x0
            // check CRC and store
            if (tlv.hdr.crc != calcTlvCrc(tlv)) {
                return (Tlv_Status_t)errmsgWCode(TS_TLV_CRC_MISMATCH, "Failed to parse TLVs, CRC mismatch for TLV type 0x%x", tlv.hdr.type);
            }
            // store it
            _tlvVec.push_back(tlv);
        }
        // next TLV is located at the first DW aligned offset after the current TLV
        nextTlvOffs += (TOOLS_OPEN_AUX_TLV_HEADER_SIZE + vecSizeDwAligned);
    } while (true);
    return TS_OK;
}

u_int16_t ImageTlvOps::calcTlvCrc(aux_tlv& tlv)
{
    struct tools_open_aux_tlv_header tempHdr;
    u_int32_t dataSize = (u_int32_t)tlv.data.size();
    Crc16 crc;
    tempHdr = tlv.hdr;
    tempHdr.crc = 0xffff;
    u_int8_t tlvHdrBuf[TOOLS_OPEN_AUX_TLV_HEADER_SIZE] = {0};
    tools_open_aux_tlv_header_pack(&tempHdr, tlvHdrBuf);
    // restore CPU endianess
    TOCPUn(tlvHdrBuf, TOOLS_OPEN_AUX_TLV_HEADER_SIZE >> 2);
    // calc crc on modified header
    CRCn(crc, tlvHdrBuf, TOOLS_OPEN_AUX_TLV_HEADER_SIZE >> 2);
    // calc crc on the data
    TOCPUn(&tlv.data[0], dataSize >> 2);
    CRCn(crc, &tlv.data[0], dataSize >> 2);
    // we might have missed the last DW as it need not be DW aligned
    u_int32_t remaining = dataSize & 3;
    if (remaining) {
        u_int32_t lastDw = 0x0;
        memcpy(&lastDw, &tlv.data[dataSize - remaining], remaining);
        crc << lastDw;
    }
    TOCPUn(&tlv.data[0], dataSize >> 2);
    crc.finish();
    return crc.get();
}


/*
 * TimeStampIFC class implementation
 */


TimeStampIFC* TimeStampIFC::getIFC(mfile *mf)
{
    return new DeviceTimeStamp(mf);
}

TimeStampIFC* TimeStampIFC::getIFC(const char *fname, u_int32_t lastFwAddr)
{
    return new ImageTimeStamp(fname, lastFwAddr);
}

TimeStampIFC* TimeStampIFC::getIFC(u_int8_t *buff, unsigned int size, u_int32_t lastFwAddr)
{
    return new ImageTimeStamp(buff, size, lastFwAddr);
}


/*
 * ImageTimeStamp class implementation
 */

Tlv_Status_t ImageTimeStamp::init()
{
    Tlv_Status_t rc = _imgTlvOps.init(_lastFwAddr);
    return rc ? (Tlv_Status_t)errmsgWCode(rc, "%s", _imgTlvOps.err()) : TS_OK;
};

Tlv_Status_t ImageTimeStamp::setTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer)
{
    aux_tlv tsTlv;
    memset(&tsTlv, 0, sizeof(tsTlv));
    tsTlv.hdr.header_type = ImageTimeStamp::TS_Header_Type;
    tsTlv.hdr.type = ImageTimeStamp::TS_Tlv_Type;
    tsTlv.hdr.length = TOOLS_OPEN_TIMESTAMP_SIZE;
    tsTlv.data.resize(tsTlv.hdr.length);
    memset(&tsTlv.data[0], 0, tsTlv.hdr.length);
    struct tools_open_timestamp tsData;
    tsData.fw_version = fwVer;
    tsData.ts_entry = timestamp;
    tools_open_timestamp_pack(&tsData, &tsTlv.data[0]);
    _imgTlvOps.addTLV(tsTlv);
    bool rc = _imgTlvOps.updateFile();
    if (!rc) {
        return (Tlv_Status_t)errmsgWCode(rc, "%s", _imgTlvOps.err());
    }
    return TS_OK;
}

Tlv_Status_t ImageTimeStamp::queryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning)
{
    (void)queryRunning;
    aux_tlv tsTlv;
    struct tools_open_timestamp tsData;
    memset(&tsTlv, 0, sizeof(tsTlv));
    Tlv_Status_t rc = _imgTlvOps.queryTlv(ImageTimeStamp::TS_Tlv_Type, ImageTimeStamp::TS_Header_Type, tsTlv);
    if (rc) {
        return (Tlv_Status_t)errmsgWCode(rc, "Failed to query timestamp, Data not found in image");
    }
    if (tsTlv.hdr.major_version != 0) {
        return (Tlv_Status_t)errmsgWCode(TS_UNKNOWN_TLV_VERSION, "Failed to query timestamp, Unknown timestamp TLV version");
    }
    tools_open_timestamp_unpack(&tsData, &tsTlv.data[0]);
    timestamp = tsData.ts_entry;
    fwVer = tsData.fw_version;
    return TS_OK;
}
Tlv_Status_t ImageTimeStamp::resetTimeStamp()
{
    Tlv_Status_t rc = _imgTlvOps.removeTlv(ImageTimeStamp::TS_Tlv_Type, ImageTimeStamp::TS_Header_Type);
    if (rc == TS_OK) {
        Tlv_Status_t rc = _imgTlvOps.updateFile();
        if (!rc) {
            return (Tlv_Status_t)errmsgWCode(rc, "Failed to reset Timestamp on image, %s", _imgTlvOps.err());
        }
    }
    return TS_OK;
}

/*
 * DeviceTimeStamp class implementation
 */

Tlv_Status_t DeviceTimeStamp::init()
{
    int rc;
    // attempt to get running FW TS
    struct tools_open_mvts mvts;
    memset(&mvts, 0, sizeof(mvts));
    mvts.running_flag = 1;
    rc = reg_access_mvts(_mf, REG_ACCESS_METHOD_GET, &mvts);
    if (rc == ME_OK || rc == ME_REG_ACCESS_BAD_CONFIG) {
        return TS_OK;
    }
    return (Tlv_Status_t)errmsgWCode(TS_TIMESTAMPING_NOT_SUPPORTED, "Time stamping not supported by FW");
}


Tlv_Status_t DeviceTimeStamp::setTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer)
{
    struct tools_open_mvts mvts;
    memset(&mvts, 0, sizeof(mvts));
    mvts.timestamp.fw_version = fwVer;
    mvts.timestamp.ts_entry = timestamp;
    int rc = reg_access_mvts(_mf, REG_ACCESS_METHOD_SET, &mvts);
    rc = (int)convertRc((MError)rc, REG_ACCESS_METHOD_SET);
    if (rc) {
        return (Tlv_Status_t)errmsgWCode(rc, "Failed to set timestamp on device, %s", err());
    }
    return TS_OK;
}


Tlv_Status_t DeviceTimeStamp::queryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning)
{
    struct tools_open_mvts mvts;
    memset(&mvts, 0, sizeof(mvts));
    mvts.running_flag = queryRunning;
    int rc = reg_access_mvts(_mf, REG_ACCESS_METHOD_GET, &mvts);
    rc = (int)convertRc((MError)rc, REG_ACCESS_METHOD_GET);
    if (rc) {
        return (Tlv_Status_t)errmsgWCode(rc, "Failed to query %s timestamp on device, %s\n", queryRunning ? "current" : "next", err());
    }
    // if timestamp and fw ver are zero entry is invalid
    struct tools_open_timestamp timestampZeroes;
    memset(&timestampZeroes, 0x0, sizeof(timestampZeroes));
    if (!memcmp(&(mvts.timestamp), &timestampZeroes, sizeof(mvts.timestamp))) {
        return (Tlv_Status_t)errmsgWCode(TS_NO_VALID_TIMESTAMP, "Failed to query %s timestamp, No valid timestamp found", queryRunning ? "current" : "next");
    }
    fwVer = mvts.timestamp.fw_version;
    timestamp = mvts.timestamp.ts_entry;
    return TS_OK;
}

Tlv_Status_t DeviceTimeStamp::resetTimeStamp()
{
    struct tools_open_mvts mvts;
    memset(&mvts, 0, sizeof(mvts));
    mvts.clear_all_ts_flag = 1;
    int rc = reg_access_mvts(_mf, REG_ACCESS_METHOD_SET, &mvts);
    rc = (int)convertRc((MError)rc, REG_ACCESS_METHOD_SET);
    if (rc) { // bad params means command not supported
        return (Tlv_Status_t)errmsgWCode(rc, "Failed to reset timestamp on device, %s", rc == ME_REG_ACCESS_BAD_CONFIG ? "Bad configuration" : err());
    }
    return TS_OK;
}

inline Tlv_Status_t DeviceTimeStamp::convertRc(MError rc, int regMethod)
{
    if (rc == ME_OK) {
        return TS_OK;
    }
    if (rc == ME_REG_ACCESS_BAD_PARAM || rc == ME_ICMD_OPERATIONAL_ERROR) {
        return (Tlv_Status_t)errmsgWCode(TS_TIMESTAMPING_NOT_SUPPORTED, "Time stamping not supported by FW");
    } else if (rc == ME_REG_ACCESS_BAD_CONFIG) {
        return (Tlv_Status_t)errmsgWCode(TS_NO_VALID_TIMESTAMP, regMethod == REG_ACCESS_METHOD_GET ? "No valid timestamp found" : "Timestamp is too old");
    } else if (rc == ME_ICMD_UNSUPPORTED_ICMD_VERSION) {
        return (Tlv_Status_t)errmsgWCode(TS_UNSUPPORTED_ICMD_VERSION, "Unsupported ICMD version");
    }
    return (Tlv_Status_t)errmsgWCode(TS_GENERAL_ERROR, "%s",  reg_access_err2str((MError)rc));
}
