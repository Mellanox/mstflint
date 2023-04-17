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

#ifndef FS_SYNCE_OPS
#define FS_SYNCE_OPS

#include "fs_comps_ops.h"

class FsSyncEOperations : public FsCompsOperations
{
public:
    FsSyncEOperations(FImage* imageAccess);

    bool FwQuery(fw_info_t* fwInfo,
                 bool readRom = true,
                 bool isStripedImage = false,
                 bool quickQuery = true,
                 bool ignoreDToc = false,
                 bool verbose = false) override;
    bool FwVerify(VerifyCallBack verifyCallBackFunc,
                  bool isStripedImage = false,
                  bool showItoc = false,
                  bool ignoreDToc = false) override;
    bool PrintQuery() override;
    u_int32_t GetDeviceIndex() override;

private:
    enum class SystemID : u_int16_t
    {
        Gorilla = 1,
        AnacondaSecured = 2,
        MarlinLeaf = 3,
        MarlinSpine = 4,
        Moose = 5,
        Komodo = 6,
        Kong = 7
    };

    enum class ClockSyncVendorHWID : u_int8_t
    {
        Renesas = 0,
        SiTime148 = 1,
        SiTime348 = 2,
        TI = 3,
        Microchip = 7
    };

    struct SyncEFileHeader
    {
        u_int16_t fingerprint;
        u_int8_t imageVersionMinor : 4;
        u_int8_t imageVersionMajor : 4;
        u_int8_t reserved : 4;
        u_int8_t clockSyncIndex : 4;
        SystemID systemID;
        ClockSyncVendorHWID clockSyncVendorHWID;
        u_int8_t headerVersion;
        u_int16_t fileCRC;
        u_int16_t lengthOfFile;
        u_int16_t headerCRC;
        u_int16_t reserved2 : 15;
        u_int16_t S : 1;
    };

    string ToString(SystemID systemID);
    string ToString(ClockSyncVendorHWID hwID);

private:
    SyncEFileHeader _header;
};

#endif /* FS_SYNCE_OPS */
