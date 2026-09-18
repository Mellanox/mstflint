/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "mlxtkngenerator_utils.h"
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include "mlxfwops/lib/mlxfwops_com.h"
#include "mlxfwops/lib/fw_ops.h"

vector<u_int8_t> ReadFromFile(string filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
        fprintf(stderr, "Error opening '%s'\n", filename.c_str());
        exit(1);
    }

    // read the data:
    return vector<u_int8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

string GetSafePsid(const string& psid)
{
    string safePsid = psid;
    for (char& c : safePsid)
    {
        if (c == '/' || c == '\\')
        {
            c = '_';
        }
    }
    if (safePsid.empty())
    {
        safePsid = "unknown_psid";
    }
    return safePsid;
}


DebugFwFileData GetDebugFwFileData(const string& filePath)
{
    char errBuff[1024];
    fw_info_t fwQueryResult;
    DebugFwFileData debugFwFileData;
    debugFwFileData.filename = filePath;

    unique_ptr<FwOperations> ops = unique_ptr<FwOperations>(
        FwOperations::FwOperationsCreate((void*)filePath.c_str(), nullptr, nullptr, FHT_FW_FILE, errBuff, 1024));

    if (ops == nullptr)
    {
        throw MlxTknGeneratorException("Failed to open the image.");
    }
    if (!ops->FwQuery(&fwQueryResult, false, false))
    {
        throw MlxTknGeneratorException("Failed to query the image.");
    }

    FwVersion image_version = FwOperations::createFwVersion(&fwQueryResult.fw_info);
    debugFwFileData.debugFwVersion = image_version.get_primary_version("%x%x%04x", false);
    debugFwFileData.psid = fwQueryResult.fw_info.psid;
    
    return debugFwFileData;
}
