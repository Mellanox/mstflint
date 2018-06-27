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

#ifndef AUX_TLV_OPS_H
#define AUX_TLV_OPS_H

#include <mtcr.h>
#include <tools_layouts/tools_open_layouts.h>
#include <tools_layouts/register_access_open_layouts.h>

typedef enum {
    TS_OK = 0,
    TS_GENERAL_ERROR,
    // device related errors
    TS_TIMESTAMPING_NOT_SUPPORTED,
    TS_NO_VALID_TIMESTAMP,
    TS_OLD_TIMESTAMP,
    TS_UNSUPPORTED_ICMD_VERSION,
    // image related errors,
    TS_TLV_CRC_MISMATCH,
    TS_TLV_PARSE_ERROR,
    TS_NO_TLV_SECTION_FOUND,
    TS_FAILED_TO_OPEN_FILE,
    TS_FAILED_TO_WRITE_FILE,
    TS_FAILED_TO_READ_FILE,
    TS_TLV_NOT_FOUND,
    TS_READ_ONLY_MODE,
    TS_HANDLE_NOT_SUPPORTED,
    TS_UNKNOWN_TLV_VERSION,
} Tlv_Status_t;

typedef struct aux_tlv {
    struct tools_open_aux_tlv_header hdr;
    std::vector<u_int8_t> data;  // data in big endian
} aux_tlv_t;


class ImageTlvOps : public FlintErrMsg
{
public:
    ImageTlvOps(const char *fname, bool readOnly = false) : FlintErrMsg(), _fname(fname), _tlvSectionFound(false),
        _tlvSectionFilePos(0), _initialized(false),
        _readOnly(readOnly){}
    ImageTlvOps(u_int8_t *buf, unsigned int size) : FlintErrMsg(), _fname((const char*)NULL),
        _tlvSectionFound(false), _tlvSectionFilePos(0),
        _initialized(false), _readOnly(true)
    {
        if (!buf) {
            // Adrianc: should not be reached, consider using exceptions
            _rawFileBuff.resize(0);
        } else {
            _rawFileBuff.resize(size);
            memcpy(&_rawFileBuff[0], buf, size);
        }
    }
    ~ImageTlvOps() {}

    Tlv_Status_t init(u_int32_t startPos, bool force = false);
    void addTLV(aux_tlv& tlv);
    Tlv_Status_t removeTlv(u_int16_t tlvType, u_int8_t headerType = 0);
    std::vector<aux_tlv> queryTlvs();
    Tlv_Status_t queryTlv(u_int16_t tlvType, u_int8_t headerType, aux_tlv& tlv);
    Tlv_Status_t resetTlvSection();
    Tlv_Status_t updateFile();
    bool test(); // test method
private:
    void pushTlvsToRawBuffer();
    Tlv_Status_t getFileSize(FILE *fd, long int& fileSize);
    Tlv_Status_t writeBufferAsFile();
    Tlv_Status_t parseTlvs();
    u_int16_t calcTlvCrc(aux_tlv& tlv);
    bool checkSig(std::vector<u_int8_t>& signature);

    const char *_fname;
    bool _tlvSectionFound;
    u_int32_t _tlvSectionFilePos;
    bool _initialized;
    bool _readOnly;
    std::vector<aux_tlv> _tlvVec;
    std::vector<u_int8_t> _rawFileBuff;
};


class TimeStampIFC : public FlintErrMsg
{
public:
    TimeStampIFC() : FlintErrMsg() {};
    virtual ~TimeStampIFC(){};
    static TimeStampIFC* getIFC(mfile *mf);
    static TimeStampIFC* getIFC(const char *fname, u_int32_t lastFWAddr = 0);
    static TimeStampIFC* getIFC(u_int8_t *buff, unsigned int size, u_int32_t lastFwAddr = 0);
    virtual Tlv_Status_t init() {return TS_OK;};
    virtual Tlv_Status_t setTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer) = 0;
    virtual Tlv_Status_t queryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning = false) = 0;
    virtual Tlv_Status_t resetTimeStamp() = 0;
};


class ImageTimeStamp : public TimeStampIFC
{
public:
    ImageTimeStamp(const char *fname, u_int32_t lastFwAddr) : TimeStampIFC(), _lastFwAddr(lastFwAddr), _imgTlvOps(fname) {};
    ImageTimeStamp(u_int8_t *buf, unsigned int size, u_int32_t lastFwAddr) : TimeStampIFC(), _lastFwAddr(lastFwAddr), _imgTlvOps(buf, size) {};
    ~ImageTimeStamp() {};
    virtual Tlv_Status_t init();

    virtual Tlv_Status_t setTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    virtual Tlv_Status_t queryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning = false);
    virtual Tlv_Status_t resetTimeStamp();
private:
    enum {
        TS_Header_Type = 0x0,
        TS_Tlv_Type = 0x1,
    };
    u_int32_t _lastFwAddr;
    ImageTlvOps _imgTlvOps;
};


class DeviceTimeStamp : public TimeStampIFC
{
public:
    DeviceTimeStamp(mfile *mf) : TimeStampIFC(), _mf(mf) {};
    ~DeviceTimeStamp() {};
    virtual Tlv_Status_t init();

    virtual Tlv_Status_t setTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer);
    virtual Tlv_Status_t queryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning = false);
    virtual Tlv_Status_t resetTimeStamp();
private:
    inline Tlv_Status_t convertRc(MError rc, int regMethod );
    mfile *_mf;
};


#endif
