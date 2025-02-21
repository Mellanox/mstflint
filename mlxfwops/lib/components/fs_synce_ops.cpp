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

#include "fs_synce_ops.h"
#include <sstream>
#include <iomanip>

FsSyncEOperations::FsSyncEOperations(FImage* imageAccess) : FsCompsOperations(imageAccess)
{
    memset(&_header, 0xff, sizeof(_header));
}

bool FsSyncEOperations::FwQuery(fw_info_t* fwInfo,
                                bool __attribute__ ((unused)) readRom,
                                bool __attribute__ ((unused)) isStripedImage,
                                bool __attribute__ ((unused)) quickQuery,
                                bool __attribute__ ((unused)) ignoreDToc,
                                bool __attribute__ ((unused)) verbose)
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

    return true;
}

bool FsSyncEOperations::PrintQuery()
{
    ostringstream ss;
    ss << left;
    ss << std::setw(23) << "Clock Sync Index:" << (short)_header.clockSyncIndex << endl;
    ss << std::setw(23) << "Image Version:" << (short)_header.imageVersionMajor << "."
       << (short)_header.imageVersionMinor << endl;
    ss << std::setw(23) << "Vendor HW ID:" << ToString(_header.clockSyncVendorHWID) << endl;
    ss << std::setw(23) << "System ID:" << ToString(_header.systemID) << endl;
    cout << ss.str();
    return true;
}

void FsSyncEOperations::PrintComponentData(vector<u_int8_t>& data, u_int32_t deviceIndex)
{
    if (!data.empty())
    {
        ostringstream ss;
        component_synce_st cmpSyncE;
        memcpy(&cmpSyncE, data.data(), sizeof(cmpSyncE)); // do not change to unpack, already unpacked in MCQI

        ss << left;
        ss << std::setw(23) << "Clock Sync Index:" << (short)deviceIndex << endl;
        ss << std::setw(23) << "Image Version:" << (short)cmpSyncE.image_version_major << "."
           << (short)cmpSyncE.image_version_minor << endl;
        ss << std::setw(23) << "Vendor HW ID:" << ToString((ClockSyncVendorHWID)cmpSyncE.vendor_id) << endl;
        // ss << std::setw(23) << "System ID:" << ToString(_header.systemID) << endl;
        cout << ss.str();
    }
}

bool FsSyncEOperations::IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion)
{
    if (!data.empty())
    {
        ostringstream ss;
        component_synce_st cmpSyncE;

        memcpy(&cmpSyncE, data.data(), sizeof(cmpSyncE)); // do not change to unpack, already unpacked in MCQI

        if ((ClockSyncVendorHWID)cmpSyncE.vendor_id != _header.clockSyncVendorHWID)
        {
            return errmsg("Vender HW ID is not compatible\n");
        }

        if (!CheckFwVersion(ComponentFwVersion(cmpSyncE.image_version_major, cmpSyncE.image_version_minor),
                            forceVersion))
        {
            return false;
        }
    }
    return true;
}

u_int32_t FsSyncEOperations::GetDeviceIndex()
{
    return _header.clockSyncIndex;
}

const char* FsSyncEOperations::FwGetResetRecommandationStr()
{
    return REBOOT_REQUIRED_STR;
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
        case (SystemID::Hippo):
            return "Hippo";
        case (SystemID::Crocodile):
            return "Crocodile";
        case (SystemID::BlackMamba):
            return "BlackMamba";
        case (SystemID::Bobcat):
            return "Bobcat";
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
