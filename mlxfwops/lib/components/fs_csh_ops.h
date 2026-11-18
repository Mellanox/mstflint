/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#pragma once

#include "fs_comps_ops.h"
#include "mlxfwops/lib/bch/csh_imp.h"
#include "tools_layouts/fs6_image_layout_layouts.h"

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

class MLXFWOP_API FsCshOperations : public FsCompsOperations
{
public:
    FsCshOperations(FBase* ioAccess) : FsCompsOperations(ioAccess) {}

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
    bool FwInit() override;
    bool PrintQuery() override;
    bool IsCompatibleToDevice(vector<u_int8_t>& data, u_int8_t forceVersion) override;
    bool FwReadData(void* image, u_int32_t* image_size, bool verbose) override;
    const char* FwGetResetRecommandationStr() override;
    FwComponent::comps_ids_t GetComponentID() override { return _componentID; }
    bool GetImageSize(u_int32_t* imageSize) override;

private:
    struct DeviceInfoCheckParams
    {
        char psid[17];
    };

    bool GetImageInfoData(vector<u_int8_t>& data);
    bool GetImageInfo(struct fs6_image_layout_image_info* imageInfo);

    CSH _csh;
    FwComponent::comps_ids_t _componentID;
};