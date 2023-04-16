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

protected:
    bool CheckBoot2(u_int32_t beg,
                    u_int32_t offs,
                    u_int32_t& next,
                    bool fullRead,
                    const char* pref,
                    VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL) override;

private:
    bool CheckBoot2(u_int32_t offs,
                    bool fullRead,
                    const char* pref,
                    VerifyCallBack verifyCallBackFunc = (VerifyCallBack)NULL);
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
