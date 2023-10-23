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
#ifndef FS5_OPS_H
#define FS5_OPS_H

#include "fs4_ops.h"

class Fs5Operations : public Fs4Operations
{
public:
    Fs5Operations(FBase* ioAccess) : Fs4Operations(ioAccess){};

    ~Fs5Operations(){};
    u_int8_t FwType() override;
    bool FwQuery(fw_info_t* fwInfo,
                 bool readRom = true,
                 bool isStripedImage = false,
                 bool quickQuery = true,
                 bool ignoreDToc = false,
                 bool verbose = false) override;
    bool GetImageSize(u_int32_t* image_size) override;
    bool GetImageInfo(u_int8_t* buff) override;

protected:
    bool CheckBoot2(u_int32_t beg,
                    u_int32_t offs,
                    u_int32_t& next,
                    bool fullRead,
                    const char* pref,
                    VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL) override;
    u_int32_t _ncore_bch_ptr;

private:
    bool CheckBoot2(bool fullRead, const char* pref, VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
    bool Init() override;
    bool InitHwPtrs(bool isVerify = false) override;
    bool ParseHwPointers(VerifyCallBack verifyCallBackFunc);
    bool FsVerifyAux(VerifyCallBack verifyCallBackFunc,
                     bool show_itoc,
                     struct QueryOptions queryOptions,
                     bool ignoreDToc = false,
                     bool verbose = false) override;
};

#endif /* FS5_OPS_H */
