/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "mlxparsebin_exception.h"
#include "mstdump_reader.h"
using namespace std;

/************************************
 * Function: MstDumpReader
 ************************************/
MstDumpReader::MstDumpReader() {}

/************************************
 * Function: ~MstDumpReader
 ************************************/
MstDumpReader::~MstDumpReader() {}

/************************************
 * Function: load
 ************************************/
void MstDumpReader::load(const string& fname)
{
    FILE* file;
    char line[128];
    u_int32_t addr;
    u_int32_t val;

    file = fopen(fname.c_str(), "r");
    if (!file)
    {
        throw MlxParseBinException(string("Failed to open file: " + fname + ", " + strerror(errno)));
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "0x%x 0x%x", &addr, &val) != 2)
        {
            throw MlxParseBinException(string("Failed to parse bin file line: ") + line);
        }

        _mstData[addr] = val;
    }
    fclose(file);
}

/************************************
 * Function: getData
 ************************************/
u_int32_t MstDumpReader::getData(u_int32_t addr)
{
    std::map<u_int32_t, u_int32_t>::iterator iter = _mstData.find(addr);
    if (iter == _mstData.end())
    {
        throw MlxParseBinException("Failed to find address");
    }

    return iter->second;
}
