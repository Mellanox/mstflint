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

#ifndef FS_SYNCE_OPS
#define FS_SYNCE_OPS

#include "fs_comps_ops.h"

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

class MLXFWOP_API FsSyncEOperations : public FsCompsOperations
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
    bool IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion) override;
    const char* FwGetResetRecommandationStr() override;
    FwComponent::comps_ids_t GetComponentID() override { return FwComponent::comps_ids_t::COMPID_CLOCK_SYNC_EEPROM; }
    static void PrintComponentData(vector<u_int8_t>& data, u_int32_t deviceIndex);

private:
    enum class SystemID : u_int16_t
    {
        Gorilla = 0x1,
        AnacondaSecured = 0x2,
        MarlinLeaf = 0x3,
        MarlinSpine = 0x4,
        Moose = 0x5,
        Komodo = 0x6,
        Kong = 0x7,
        Hippo = 0x8,
        Crocodile = 0x9,
        BlackMamba = 0xA,
        Bobcat = 0xB
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

    static string ToString(SystemID systemID);
    static string ToString(ClockSyncVendorHWID hwID);

private:
    SyncEFileHeader _header;
};

#endif /* FS_SYNCE_OPS */