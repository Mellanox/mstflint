/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXPARSEBIN_LIB_H
#define MLXPARSEBIN_LIB_H

#include <map>
#include <string>
#include <vector>

#include <common/compatibility.h>

#include "adb_parser/adb_parser.h"

class DumpReader;

class MlxParseBinLib
{
public:
    class Options
    {
    public:
        Options();

        static const long int FILTER_DISABLED = -1;

        std::string adbFile;
        std::string adbString;
        std::string binFile;
        std::string adbRootNode;
        u_int64_t rootOffsetBytes;
        long int filterFrom;
        long int filterTo;
        std::string filterPath;
        bool csvMode;
    };

    // A leaf field with the location it was extracted from, for consumers that
    // have to rebuild a raw dword out of the fields covering it.
    class FieldData
    {
    public:
        FieldData();

        u_int32_t value;
        u_int32_t dwordAddr;
        u_int32_t startBit;
        u_int32_t size;
    };

    typedef std::map<std::string, FieldData> FieldDataMap;

    explicit MlxParseBinLib(const Options& options);
    ~MlxParseBinLib();

    void load();
    void printDump();
    void printDump(FieldDataMap& fields);
    void printDump(FieldDataMap& fields, const std::string& filterPath);

    static u_int32_t readDword(const std::string& binFile, u_int32_t addr);

private:
    class Constants
    {
    public:
        static const u_int32_t BITS_IN_BYTE = 8;
        static const u_int32_t DWORD_SIZE = 4;
        static const int FORMAT_DETECTION_MAX_LINES = 100;
        static const int FORMAT_DETECTION_LINE_SIZE = 128;
    };

    void initAdb();
    void initDumpReader();
    void reset();
    void ensureLoaded() const;
    static DumpReader* createDumpReader(const std::string& binFile);
    std::vector<AdbInstance*> getFilteredLeafFields(const std::string& filterPath);
    void collectFields(FieldDataMap* fieldsData, const std::string& filterPath);

    Options _options;
    Adb* _adb;
    AdbInstance* _node;
    DumpReader* _dumpReader;
};

#endif // MLXPARSEBIN_LIB_H
