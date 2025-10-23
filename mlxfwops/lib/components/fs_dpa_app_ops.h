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

#ifndef FS_DPA_APP_OPS
#define FS_DPA_APP_OPS

#include "fs_comps_ops.h"
#include "mlxdpa/dpaAppStructHeader.h"

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

#ifdef MFT_LEGACY_BUILD
#include "reg_access_hca_layouts.h"
#else
#include "tools_layouts/reg_access_hca_layouts.h"
#endif

class MLXFWOP_API AppMetadataItem
{
public:
    AppMetadataItem() { memset(&_dpaMetadata, 0, sizeof(_dpaMetadata)); }

    bool Deserialize(const vector<u_int8_t> rawData);
    static const u_int32_t APP_MEATADATA_SIZE = REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE;

    enum class AppMetadataType : u_int8_t
    {
        APU_APP_EXTERNAL = 0,
        Reserved1 = 1,
        Reserved2 = 2,
        Reserved3 = 3,
        APU_APP_PCC = 4,
        APU_APP_DLL = 5,
        APU_APP_KERNEL = 6,
        Reserved
    };

    reg_access_hca_mcqi_dpa_metadata_ext _dpaMetadata;
};

class MLXFWOP_API FsDpaAppOperations : public FsCompsOperations
{
public:
    FsDpaAppOperations(FImage* imageAccess);
    FsDpaAppOperations(const AppMetadataItem& appmetadataItem);
    FsDpaAppOperations(const vector<u_int8_t>& rawData);
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
    bool PrintQuery() override;
    const char* FwGetResetRecommandationStr() override;
    FwComponent::comps_ids_t GetComponentID() override { return _compID; }
    bool DeserializeApps(const vector<u_int8_t>& rawData, vector<AppMetadataItem>& _appsMetadata);
    void PrintAppMetadata(AppMetadataItem dpaApp, int numberOfDpaApp);
    void AddToAppMetadataContainer(const vector<u_int8_t>& rawData);
    u_int8_t GetNumOfEntriesTotal() { return _totalNumberOfEntries; }
    std::size_t GetAppsMetadataSize() { return _appsMetadata.size(); }
    bool FindAppMetedataSection(size_t offset);

    static const int FINGERPRINT_SIZE = 16;

private:
    static string AppMetadataTypeToString(AppMetadataItem::AppMetadataType appMetadataType);

    u_int8_t _totalNumberOfEntries;
    vector<AppMetadataItem> _appsMetadata;
    FwComponent::comps_ids_t _compID;
};

#endif /* FS_CERT_OPS */