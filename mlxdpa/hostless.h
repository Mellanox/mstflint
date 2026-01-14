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
 *
 *  Version: $Id$
 *
 */

#ifndef MLXDPA_HOSTLESS_H_
#define MLXDPA_HOSTLESS_H_

#include <string>
#include <vector>

#include <yaml/Yaml.hpp>

#include "baseHeader.h"
#include "dpaAppStructHeader.h"
#include "tools_layouts/reg_access_hca_layouts.h"

using namespace std;

class HostLess
{
public:
    static const string SINGLE_APP_DPA_FINGERPRINT;

    HostLess(string containerForSigningPath, BaseHeader::StructPriority priority, bool noCheckHeaderPriority = false);
    HostLess(string elfPath, string appMetadataPath, string manifestPath);
    ~HostLess();

    vector<u_int8_t> GetElfData() const;
    size_t GetElfSize() const;
    vector<u_int8_t> GetAppMetadata() const;
    size_t GetAppMetadataSize() const;
    DpaAppStructHeader GetElfHeader() const;
    DpaAppStructHeader GetAppMetadataHeader() const;
    bool IsAppMetadataPresent() const;
    vector<u_int8_t> GetManifest() const;
    bool IsManifestPresent() const;
    DpaAppStructHeader GetManifestHeader() const;
    size_t GetManifestSize() const;

    std::string GetAppMetadataUUID() const;

private:
    void SetElfData();
    void SetAppMetadata(string appMetadataPath);
    bool ReadAndValidateAppMetadata(Yaml::Node& root, string appMetadataPath);
    void SetContainerForSigning();
    void AppMetadataUnpack(std::vector<u_int8_t>::iterator start, std::vector<u_int8_t>::iterator end);
    void SetAppMetadataUUID();
    void SetAppMetadataDescription(string desc);
    bool CheckHeaderPriority(BaseHeader::StructPriority priorityHeader);
    void SetManifest(std::string manifestPath);

    string _elfPath;
    DpaAppStructHeader _elfHeader;
    vector<u_int8_t> _elfData;

    DpaAppStructHeader _appMetadataHeader;
    reg_access_hca_mcqi_dpa_metadata_ext _appMetadata;
    bool _isAppMetadataPresent;

    DpaAppStructHeader _manifestHeader;
    vector<u_int8_t> _manifestData;
    bool _isManifestPresent;

    BaseHeader::StructPriority _priority;
    bool _checkHeaderPriority;
    std::string _uuid;
};

#endif /* MLXDPA_HOSTLESS_H_ */