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
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "mlxparsebin_exception.h"
#include "raw_dump_reader.h"

using namespace std;
/************************************
 * Function: RawDumpReader
 ************************************/
RawDumpReader::RawDumpReader() : DumpReader() {}

/************************************
 * Function: ~RawDumpReader
 ************************************/
RawDumpReader::~RawDumpReader() {}

/************************************
 * Function: load
 ************************************/
void RawDumpReader::load(const std::string& fname)
{
    FILE* f;
    char data[1024];
    size_t s;
    char dwordStr[9] = {0};
    int digits = 0;
    u_int32_t addr = 0;

    f = fopen(fname.c_str(), "r");
    if (!f)
    {
        throw MlxParseBinException("Can't open file (" + fname + ") for reading: " + strerror(errno));
    }

    while (!feof(f))
    {
        s = fread(data, 1, sizeof(data), f);
        for (size_t i = 0; i < s; i++)
        {
            if (data[i] == ' ' || data[i] == '\t' || data[i] == '\r' || data[i] == '\n')
            {
                continue;
            }

            dwordStr[digits] = data[i];
            digits++;

            if (digits == 8)
            {
                char* p;
                _rawData[addr] = strtoul(dwordStr, &p, 16);
                if (*p)
                {
                    throw MlxParseBinException(string("Failed to parse integer: ") + dwordStr);
                }

                digits = 0;
                addr += 4;
            }
        }
    }

    fclose(f);
}

/************************************
 * Function: getData
 ************************************/
u_int32_t RawDumpReader::getData(u_int32_t addr)
{
    std::map<u_int32_t, u_int32_t>::iterator iter = _rawData.find(addr);
    if (iter == _rawData.end())
    {
        throw MlxParseBinException("Failed to find address");
    }

    return iter->second;
}
