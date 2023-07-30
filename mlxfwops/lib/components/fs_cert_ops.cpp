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

FsCertOperations::FsCertOperations(FImage* imageAccess) :
    FsCompsOperations(imageAccess), _compID(FwComponent::comps_ids_t::COMPID_UNKNOWN)
{
}

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