/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
#include "fs_dpa_app_ops.h"
#include "mlxdpa/dpaAppStructHeader.h"
#include <sstream>
#include <bitset>
#include <iomanip>
#ifdef MFT_LEGACY_BUILD
#include "mft_utils.h"
#else
#include "mft_utils/mft_utils.h"
#endif

FsDpaAppOperations::FsDpaAppOperations(FImage* imageAccess) : FsCompsOperations(imageAccess), _appsMetadata()
{
    _compID = FwComponent::comps_ids_t::COMPID_UNKNOWN;
    _totalNumberOfEntries = 0;
}
FsDpaAppOperations::FsDpaAppOperations(const AppMetadataItem& appmetadataContainer) :
    FsCompsOperations(nullptr), _appsMetadata(), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN)
{
    _appsMetadata.push_back(appmetadataContainer);
    _totalNumberOfEntries = 1;
}
FsDpaAppOperations::FsDpaAppOperations(const vector<u_int8_t>& rawData) :
    FsCompsOperations(nullptr), _appsMetadata(), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN)
{
    _totalNumberOfEntries = 0;
    DeserializeApps(rawData, _appsMetadata);
}

bool FsDpaAppOperations::DeserializeApps(const vector<u_int8_t>& rawData, vector<AppMetadataItem>& _appsMetadata)
{
    if ((rawData.size() % AppMetadataItem::APP_MEATADATA_SIZE != 0))
    {
        return false;
    }
    if (!rawData.empty())
    {
        for (size_t i = 0; i < rawData.size() / AppMetadataItem::APP_MEATADATA_SIZE; i++)
        {
            vector<u_int8_t> appMetadataData(rawData.begin() + i * AppMetadataItem::APP_MEATADATA_SIZE,
                                             rawData.begin() + (i + 1) * AppMetadataItem::APP_MEATADATA_SIZE);
            AddToAppMetadataContainer(appMetadataData);
        }
    }
    return true;
}

void FsDpaAppOperations::AddToAppMetadataContainer(const vector<u_int8_t>& rawData)
{
    AppMetadataItem dpaAppMetaData;
    if (!dpaAppMetaData.Deserialize(rawData))
    {
        std::cerr << "Failed to deserialize AppMetadataItem" << std::endl;
        return;
    }
    _appsMetadata.push_back(dpaAppMetaData);
    _totalNumberOfEntries++;
}

bool FsDpaAppOperations::FindAppMetedataSection(size_t offset)
{
    size_t next_offset = offset;
    vector<u_int8_t> bufHeader(DpaAppStructHeader::HEADER_SIZE_NO_AUTH);
    DpaAppStructHeader header;
    while (next_offset < _ioAccess->get_size())
    {
        std::fill(bufHeader.begin(), bufHeader.end(), 0);
        if (!_ioAccess->read(next_offset, bufHeader.data(), bufHeader.size(), false, NULL))
        {
            return errmsg("read error (%s)\n", (*_ioAccess).err());
        }
        header.Deserialize(bufHeader);
        if (header.GetType() == DpaAppStructHeader::StructType::DPA_APP_METADATA)
        {
            AppMetadataItem dpaAppMetaData;
            vector<u_int8_t> bufData(AppMetadataItem::APP_MEATADATA_SIZE);
            if (!_ioAccess->read(next_offset + header.GetHeaderSize(), bufData.data(), bufData.size(), false, NULL))
            {
                return errmsg("read error (%s)\n", (*_ioAccess).err());
            }
            AddToAppMetadataContainer(bufData);
            return true;
        }
        next_offset += header.GetLength();
    }
    return false;
}

bool FsDpaAppOperations::FwInit()
{
#ifndef MST_CPU_armv7l_umbriel

    vector<u_int8_t> buf(DpaAppStructHeader::HEADER_SIZE_NO_AUTH);
    DpaAppStructHeader header;
    if (_ioAccess->get_size() <= 0)
    {
        std::cerr << "The image is empty";
        return false;
    }

    if (!_ioAccess->read(FINGERPRINT_SIZE, buf.data(), buf.size(), false, NULL))
    {
        return errmsg("read error (%s)\n", (*_ioAccess).err());
    }

    header.Deserialize(buf);
    if (header.GetType() == DpaAppStructHeader::StructType::DPA_ELF)
    {
        _compID = FwComponent::comps_ids_t::DPA_COMPONENT;
        size_t next_offset = FINGERPRINT_SIZE + header.GetLength();
        if (!FindAppMetedataSection(next_offset))
        {
            std::cerr << "No App Metadata found";
            return false;
        }
        return true;
    }

    if (header.GetType() == DpaAppStructHeader::StructType::DPA_APP_REMOVE_METADATA)
    {
        _compID = FwComponent::comps_ids_t::DPA_COMPONENT_REMOVAL;
        return true;
    }

    std::cerr << "Unknown dpa header type (" << header.DpaAppStructHeader::TypeToString(header.GetType()) << ")\n";
    return false;
#endif // } MST_CPU_armv7l_umbriel
}

bool FsDpaAppOperations::FwQuery(fw_info_t* fwInfo,
                                 bool readRom,
                                 bool isStripedImage,
                                 bool quickQuery,
                                 bool ignoreDToc,
                                 bool verbose)
{
    return true;
}

bool FsDpaAppOperations::FwVerify(VerifyCallBack, bool, bool, bool)
{
    return true;
}

const char* FsDpaAppOperations::FwGetResetRecommandationStr()
{
    return nullptr;
}

void FsDpaAppOperations::PrintAppMetadata(AppMetadataItem dpaApp, int numberOfDpaApp)
{
    ostringstream ss;
    ss << left;
    ss << "DpaApp #" << numberOfDpaApp << " Metadata:" << endl;
    ss << std::setw(30)
       << "Type:" << AppMetadataTypeToString(static_cast<AppMetadataItem::AppMetadataType>(dpaApp._dpaMetadata.type))
       << endl;
    ss << std::setw(30) << "Subtype:" << (int)dpaApp._dpaMetadata.subtype << endl;
    ss << std::setw(30) << "Version:" << (int)dpaApp._dpaMetadata.version << endl;
    ss << std::setw(30) << "Length:" << dpaApp._dpaMetadata.length << endl;
    ss << std::setw(30) << "Dpa app version:" << (int)dpaApp._dpaMetadata.dpa_app_version << endl;
    ss << std::setw(30) << "Dpa os api version:" << (int)dpaApp._dpaMetadata.dpa_os_api_version << endl;
    ss << std::setw(30) << "Dpa fw api version:" << (int)dpaApp._dpaMetadata.dpa_fw_api_version << endl;
    ss << std::setw(30) << "Dpa app uuid:" << mft_utils::ToString(dpaApp._dpaMetadata.dpa_app_uuid, 4, true) << endl;
    ss << std::setw(30) << "Dpa app description string:"
       << mft_utils::ToString(dpaApp._dpaMetadata.dpa_app_description_string,
                              sizeof(dpaApp._dpaMetadata.dpa_app_description_string) / sizeof(uint32_t),
                              false)
       << endl;
    cout << ss.str();
}

bool FsDpaAppOperations::PrintQuery()
{
    int appsSize = _totalNumberOfEntries;
    if (_appsMetadata.empty())
    {
        std::cout << "No DPA apps found" << std::endl;
        return true;
    }
    std::cout << "Total number of DPA apps: " << appsSize << std::endl;
    for (int i = 0; i < appsSize; ++i)
    {
        PrintAppMetadata(_appsMetadata[i], i);
    }

    return true;
}

string FsDpaAppOperations::AppMetadataTypeToString(AppMetadataItem::AppMetadataType appMetadataType)
{
    switch (appMetadataType)
    {
        case (AppMetadataItem::AppMetadataType::APU_APP_EXTERNAL):
            return "APU_APP_EXTERNAL";
        case (AppMetadataItem::AppMetadataType::APU_APP_PCC):
            return "APU_APP_PCC";
        case (AppMetadataItem::AppMetadataType::APU_APP_DLL):
            return "APU_APP_DLL";
        case (AppMetadataItem::AppMetadataType::APU_APP_KERNEL):
            return "APU_APP_KERNEL";
        default:
            return "Reserved";
    }
}

bool AppMetadataItem::Deserialize(const vector<u_int8_t> rawData)
{
    if (rawData.size() != REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE)
    {
        return false;
    }

    reg_access_hca_mcqi_dpa_metadata_ext_unpack(&_dpaMetadata, rawData.data());

    return true;
}