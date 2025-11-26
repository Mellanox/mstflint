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

#include "fs_cert_ops.h"
#include "mlxdpa/certcontainerbase.h"
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "mft_utils/mft_utils.h"

FsCertOperations::FsCertOperations(FImage* imageAccess) :
    FsCompsOperations(imageAccess), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN){};

#if ENABLE_DPA
FsCertOperations::FsCertOperations(const CertContainerItem& container) :
    FsCompsOperations(nullptr), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN)
{
    _containers.push_back(container);
};

FsCertOperations::FsCertOperations(const vector<u_int8_t>& rawDataContainer) :
    FsCompsOperations(nullptr), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN)
{
    DeserializeCertificates(rawDataContainer, _containers);
};

bool FsCertOperations::DeserializeCertificates(const vector<u_int8_t>& cacertRawData,
                                               vector<CertContainerItem>& certContainers)
{
    vector<u_int8_t>::const_iterator containerIter = cacertRawData.begin();

    while (containerIter != cacertRawData.end())
    {
        CertStructHeader header;
        header.Deserialize(containerIter, containerIter + CertStructHeader::HEADER_SIZE);

        shared_ptr<CACertMetaData> metadata = make_shared<CACertMetaData>();
        metadata->Deserialize(
          vector<u_int8_t>(containerIter + CertStructHeader::HEADER_SIZE, containerIter + header.GetLength()));

        containerIter += header.GetLength();

        CertStructHeader certHeader;
        certHeader.Deserialize(containerIter, containerIter + CertStructHeader::HEADER_SIZE);

        if (CheckNvidiaSignedOemPriority(header, certHeader))
        {
            vector<u_int8_t> certUUID = metadata->GetCertUUID();
            std::string certUUIDString = mft_utils::ToHexString(certUUID);
            _nvidiaSignedOemCertUUIDs.push_back(certUUIDString);
        }

        certContainers.push_back(CertContainerItem(
        header,
        metadata,
        vector<u_int8_t>(containerIter + CertStructHeader::HEADER_SIZE, containerIter + certHeader.GetLength())));

        containerIter += certHeader.GetLength();
    }
    return true;
}

bool FsCertOperations::CheckNvidiaSignedOemPriority(CertStructHeader header, CertStructHeader certHeader)
{
    if (header.ValidateNvidiaSignedOemPriority() && certHeader.ValidateNvidiaSignedOemPriority())
    {
        return true;
    }
    return false;
}

bool FsCertOperations::FindContainer(string cert_uuid, CertContainerItem& container)
{
    auto it =
      std::find_if(_containers.begin(),
                   _containers.end(),
                   [cert_uuid](CertContainerItem currCertContainer)
                   { return mft_utils::ToHexString(currCertContainer.GetMetadata()->GetCertUUID()) == cert_uuid; });

    if (it != _containers.end())
    {
        container = *it;
        return true;
    }
    return false;
}

bool FsCertOperations::WriteCertToFile(CertContainerItem& container, string outputFile)
{
    ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        return errmsg("Can not open %s.", outputFile.c_str());
    }
    outFile << mft_utils::ToHexString(container.GetCert()) << endl;
    outFile.close();
    return true;
}

bool FsCertOperations::GetCert(string cert_uuid, string outputFile)
{
    if (!cert_uuid.empty())
    {
        CertContainerItem container;
        if (!FindContainer(cert_uuid, container))
        {
            return errmsg("Cert uuid: %s, is not exist.", cert_uuid.c_str());
        }
        PrintCertMetadata(container, std::cout);
        if (!outputFile.empty())
        {
            WriteCertToFile(container, outputFile);
            cout << "Certificate written successfully!" << endl;
        }
    }
    else
    {
        for (CertContainerItem& container : _containers)
        {
            PrintCertMetadata(container, std::cout);
        }
    }

    return true;
}

void FsCertOperations::PrintCertMetadata(CertContainerItem& container, ostream& os)
{
    CertStructHeader header = container.GetHeader();
    shared_ptr<CertStructBase> metadata = container.GetMetadata();

    os << "Cert uuid: ";
    vector<u_int8_t> certUUID = metadata->GetCertUUID();
    os << mft_utils::ToHexString(certUUID) << std::endl;

    os << "Keypair uuid: ";
    vector<u_int8_t> keypairUUID = metadata->GetKeypairUUID();
    os << mft_utils::ToHexString(keypairUUID) << std::endl;

    u_int8_t targetingType = metadata->GetTargetingType();
    string target = targetingType == 0 ? "GLOBAL" : "UNKNOWN";
    os << "Targeting type: " << target << std::endl;

    const CertStructHeader::StructPriority structDriority = header.GetPriority();
    string priority = CertStructHeader::_metadataPriorityToString.at(structDriority);
    if (structDriority == CertStructHeader::StructPriority::Nvidia)
    {
        if (std::find(_nvidiaSignedOemCertUUIDs.begin(),
                      _nvidiaSignedOemCertUUIDs.end(),
                      mft_utils::ToHexString(certUUID)) != _nvidiaSignedOemCertUUIDs.end())
        {
            priority = "OEM(Nvidia signed)";
        }
    }
    os << "Priority: " << priority << std::endl;

    u_int8_t dparot = metadata->GetDpaRotEn();
    string dparotEm = dparot ? "DPA ROT" : "UNKNOWN";
    os << "Intended use: " << dparotEm << std::endl;

    os << "########################################" << std::endl;
}
#endif

bool FsCertOperations::FwInit()
{
#if ENABLE_DPA
    vector<u_int8_t> buf(CertStructHeader::HEADER_SIZE);
    CertStructHeader header;

    if (!_ioAccess->read(16, buf.data(), buf.size(), false, NULL))
    {
        return errmsg("read error (%s)\n", (*_ioAccess).err());
    }

    header.Deserialize(buf);
    if (header.GetType() == CertStructHeader::StructType::CacertMetadata)
    {
        _compID = FwComponent::comps_ids_t::DIGITAL_CACERT;
    }
    else if (header.GetType() == CertStructHeader::StructType::CacertRemove)
    {
        _compID = FwComponent::comps_ids_t::DIGITAL_CACERT_REMOVAL;
    }
    else
    {
        return errmsg("Unknown cert header type (%d)\n", (int)header.GetType());
    }

    return true;
#else
    return errmsg("DPA is not supported\n");
#endif
}

bool FsCertOperations::FwQuery(fw_info_t*, bool, bool, bool, bool, bool)
{
    return true;
}

bool FsCertOperations::FwVerify(VerifyCallBack, bool, bool, bool)
{
    return true;
}

const char* FsCertOperations::FwGetResetRecommandationStr()
{
    return nullptr;
}