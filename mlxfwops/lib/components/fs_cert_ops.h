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

#ifndef FS_CERT_OPS
#define FS_CERT_OPS

#include "fs_comps_ops.h"
#include "mlxdpa/certcontainerimp.h"

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

class MLXFWOP_API FsCertOperations : public FsCompsOperations
{
public:
    FsCertOperations(FImage* imageAccess);
    FsCertOperations(const CertContainerItem& container);
    FsCertOperations(const vector<u_int8_t>& rawDataContainer);

    bool FwInit() override;
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
    const char* FwGetResetRecommandationStr() override;
    FwComponent::comps_ids_t GetComponentID() override { return _compID; }
    vector<CertContainerItem>& GetCotainers() { return _containers; };
    bool GetCert(string cert_uuid, string outputFile);
    bool WriteCertToFile(CertContainerItem& container, string outputFile);
    void PrintCertMetadata(CertContainerItem& container, ostream& os);
    bool DeserializeCertificates(const vector<u_int8_t>& cacertRawData, vector<CertContainerItem>& certContainers);
    bool CheckNvidiaSignedOemPriority(CertStructHeader header, CertStructHeader certHeader);
    bool FindContainer(string cert_uuid, CertContainerItem& container);

private:
    vector<CertContainerItem> _containers;
    vector<string> _nvidiaSignedOemCertUUIDs;
    FwComponent::comps_ids_t _compID;
};

#endif /* FS_CERT_OPS */