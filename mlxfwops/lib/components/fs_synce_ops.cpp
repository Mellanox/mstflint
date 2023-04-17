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

#include "fs_synce_ops.h"
#include <sstream>
#include <iomanip>

FsSyncEOperations::FsSyncEOperations(FImage* imageAccess) : FsCompsOperations(imageAccess)
{
    memset(&_header, 0xff, sizeof(_header));
}

bool FsSyncEOperations::FwQuery(fw_info_t* fwInfo,
                                bool readRom,
                                bool isStripedImage,
                                bool quickQuery,
                                bool ignoreDToc,
                                bool verbose)
{
    u_int8_t data[sizeof(_header)] = {0};

    if (_header.fingerprint == 0xffff)
    {
        if (!_ioAccess->read(0, data, sizeof(_header), false, NULL))
        {
            return errmsg("read error (%s)\n", (*_ioAccess).err());
        }

        memcpy(&_header, data, sizeof(_header));
        _fwImgInfo.ext_info.fw_ver[0] = _header.imageVersionMajor;
        _fwImgInfo.ext_info.fw_ver[1] = _header.imageVersionMinor;
    }

    if (fwInfo != nullptr)
    {
        std::copy(begin(_fwImgInfo.ext_info.fw_ver), end(_fwImgInfo.ext_info.fw_ver), begin(fwInfo->fw_info.fw_ver));
    }

    return FwVerify(NULL);
}

bool FsSyncEOperations::FwVerify(VerifyCallBack, bool, bool, bool)
{
    u_int32_t length =
      _ioAccess->get_size() - (_header.S == 0 ? sizeof(image_layout_image_signature_2) : 0) - sizeof(_header);
    if (_header.lengthOfFile != length)
    {
        return errmsg("Header verify error - wrong length\n");
    }
    // u_int32_t *data = (u_int32_t *)&_header;

    // Crc16 crc;
    // crc.add(*data);
    // ++data;
    // crc.add(*data);
    // ++data;
    // crc.add(*data);
    // // ++data;
    // // crc.add(*data & 0xFFFF0000);
    // // crc.add(_header.fingerprint);
    // // crc.add(_header.imageVersionMinor);
    // // crc.add(_header.imageVersionMajor);
    // // crc.add(_header.clockSyncIndex);
    // // crc.add((u_int32_t)_header.systemID);
    // // crc.add((u_int32_t)_header.clockSyncVendorHWID);
    // // crc.add(_header.headerVersion);
    // // crc.add(_header.fileCRC);
    // // crc.add(_header.lengthOfFile);
    // // crc.add(_header.reserved);
    // // crc.add(_header.reserved2);
    // // crc.add(_header.S);
    // crc.finish();
    // u_int32_t crcRes = crc.get();

    return true;
}

bool FsSyncEOperations::PrintQuery()
{
    ostringstream ss;
    ss << left;
    ss << std::setw(23) << "Image Version:" << (short)_header.imageVersionMajor << "."
       << (short)_header.imageVersionMinor << endl;
    ss << std::setw(23) << "Clock Sync Index:" << (short)_header.clockSyncIndex << endl;
    ss << std::setw(23) << "System ID:" << ToString(_header.systemID) << endl;
    ss << std::setw(23) << "Vendor HW ID:" << ToString(_header.clockSyncVendorHWID) << endl;
    ss << std::setw(23) << "Header Version:" << (short)_header.headerVersion << endl;
    ss << std::setw(23) << "Signed:" << ((short)_header.S == 1 ? "False" : "True") << endl;
    cout << ss.str();
    return true;
}

u_int32_t FsSyncEOperations::GetDeviceIndex()
{
    return _header.clockSyncIndex;
}

string FsSyncEOperations::ToString(SystemID systemID)
{
    switch (systemID)
    {
        case (SystemID::Gorilla):
            return "Gorilla";
        case (SystemID::AnacondaSecured):
            return "AnacondaSecured";
        case (SystemID::MarlinLeaf):
            return "MarlinLeaf";
        case (SystemID::MarlinSpine):
            return "MarlinSpine";
        case (SystemID::Moose):
            return "Moose";
        case (SystemID::Komodo):
            return "Komodo";
        case (SystemID::Kong):
            return "Kong";
        default:
            return "Unknown";
    }
}

string FsSyncEOperations::ToString(ClockSyncVendorHWID hwID)
{
    switch (hwID)
    {
        case (ClockSyncVendorHWID::Renesas):
            return "Renesas";
        case (ClockSyncVendorHWID::SiTime148):
            return "SiTime148";
        case (ClockSyncVendorHWID::SiTime348):
            return "SiTime348";
        case (ClockSyncVendorHWID::TI):
            return "TI";
        case (ClockSyncVendorHWID::Microchip):
            return "Microchip";
        default:
            return "Unknown";
    }
}
