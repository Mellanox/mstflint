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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common/bit_slice.h>

#include "dump_reader.h"
#include "mlxparsebin_exception.h"
#include "mlxparsebin_lib.h"
#include "mstdump_reader.h"
#include "raw_dump_reader.h"

using namespace std;

MlxParseBinLib::Options::Options() :
    rootOffsetBytes(0), filterFrom(FILTER_DISABLED), filterTo(FILTER_DISABLED), csvMode(false)
{
}

MlxParseBinLib::MlxParseBinLib(const Options& options) : _options(options), _adb(0), _node(0), _dumpReader(0) {}

MlxParseBinLib::~MlxParseBinLib()
{
    reset();
}

void MlxParseBinLib::load()
{
    reset();
    initDumpReader();
    initAdb();
}

// The node is released before the adb it was laid out from, and delete on a null
// pointer is a no-op, so this serves both the destructor and a repeated load.
void MlxParseBinLib::reset()
{
    delete _node;
    _node = 0;

    delete _adb;
    _adb = 0;

    delete _dumpReader;
    _dumpReader = 0;
}

void MlxParseBinLib::ensureLoaded() const
{
    if (!_dumpReader || !_node)
    {
        throw MlxParseBinException("MlxParseBinLib::load() must be called before the dump is read");
    }
}

void MlxParseBinLib::initDumpReader()
{
    _dumpReader = createDumpReader(_options.binFile);
}

DumpReader* MlxParseBinLib::createDumpReader(const string& binFile)
{
    FILE* file;
    int cnt = 0;
    char line[Constants::FORMAT_DETECTION_LINE_SIZE];
    u_int32_t tmp;
    DumpReader* dumpReader = 0;

    file = fopen(binFile.c_str(), "r");
    if (!file)
    {
        throw MlxParseBinException(string("Failed to open file: " + binFile + ", " + strerror(errno)));
    }

    while (!dumpReader && fgets(line, sizeof(line), file) != NULL && cnt < Constants::FORMAT_DETECTION_MAX_LINES)
    {
        if (sscanf(line, "0x%x 0x%x", &tmp, &tmp) == 2)
        {
            dumpReader = new MstDumpReader;
        }

        cnt++;
    }
    fclose(file);

    if (!dumpReader)
    {
        dumpReader = new RawDumpReader;
    }

    try
    {
        dumpReader->load(binFile);
    }
    catch (...)
    {
        delete dumpReader;
        throw;
    }

    return dumpReader;
}

u_int32_t MlxParseBinLib::readDword(const string& binFile, u_int32_t addr)
{
    DumpReader* dumpReader = createDumpReader(binFile);
    u_int32_t value;

    try
    {
        value = dumpReader->getData(addr);
    }
    catch (...)
    {
        delete dumpReader;
        throw;
    }
    delete dumpReader;

    return value;
}

void MlxParseBinLib::initAdb()
{
    if (_options.rootOffsetBytes % Constants::DWORD_SIZE)
    {
        throw MlxParseBinException("Root offset must be dword aligned (a multiple of 4 bytes)");
    }

    _adb = new Adb();
    try
    {
        bool loaded = _options.adbString.empty() ? _adb->load(_options.adbFile, false, false) :
                                                   _adb->loadFromString(_options.adbString.c_str(), false, false);
        if (!loaded)
        {
            throw MlxParseBinException("Failed to load ADB: " + _adb->getLastError());
        }
        string rootNode = _options.adbRootNode != "" ? _options.adbRootNode : _adb->rootNode;
        _node =
          _adb->createLayout(rootNode, -1, false, false, false, _options.rootOffsetBytes * Constants::BITS_IN_BYTE);

        if (!_node)
        {
            throw MlxParseBinException("Failed to instantiate node: " + rootNode);
        }
    }
    catch (AdbException& exp)
    {
        throw MlxParseBinException(exp.what());
    }
}

vector<AdbInstance*> MlxParseBinLib::getFilteredLeafFields(const string& filterPath)
{
    if (filterPath == "")
    {
        return _node->getLeafFields(false);
    }

    AdbInstance* f = _node->getChildByPath(filterPath);
    if (!f)
    {
        throw MlxParseBinException("Can't find node with name: " + filterPath);
    }

    return f->getLeafFields(false);
}

MlxParseBinLib::FieldData::FieldData() : value(0), dwordAddr(0), startBit(0), size(0) {}

void MlxParseBinLib::printDump()
{
    collectFields(NULL, _options.filterPath);
}

void MlxParseBinLib::printDump(FieldDataMap& fields)
{
    collectFields(&fields, _options.filterPath);
}

void MlxParseBinLib::printDump(FieldDataMap& fields, const string& filterPath)
{
    collectFields(&fields, filterPath);
}

void MlxParseBinLib::collectFields(FieldDataMap* fieldsData, const string& filterPath)
{
    ensureLoaded();

    vector<AdbInstance*> leafFields = getFilteredLeafFields(filterPath);
    vector<AdbInstance*>::iterator iter;
    string enumVal;

    if (!fieldsData && _options.csvMode)
    {
        printf("Field,Address,StartBit,Size,Value\n");
    }

    for (iter = leafFields.begin(); iter != leafFields.end(); iter++)
    {
        AdbInstance* f = *iter;
        if (_options.filterFrom != Options::FILTER_DISABLED && f->dwordAddr() < (u_int32_t)_options.filterFrom)
        {
            continue;
        }

        if (_options.filterTo != Options::FILTER_DISABLED && f->dwordAddr() > (u_int32_t)_options.filterTo)
        {
            break;
        }

        u_int32_t value;
        try
        {
            value = EXTRACT(_dumpReader->getData(f->dwordAddr()), f->startBit(), f->get_size());
        }
        catch (MlxParseBinException&)
        {
            continue;
        }

        if (fieldsData)
        {
            FieldData& fieldData = (*fieldsData)[f->fullName()];
            fieldData.value = value;
            fieldData.dwordAddr = f->dwordAddr();
            fieldData.startBit = f->startBit();
            fieldData.size = f->get_size();
            continue;
        }

        if (_options.csvMode)
        {
            printf("%s,0x%lx,%d,%ld,0x%x", f->fullName().c_str(), (unsigned long)f->dwordAddr(), f->startBit(),
                   (unsigned long)f->get_size(), value);
        }
        else
        {
            char valStr[32];
            sprintf(valStr, "0x%x", value);

            printf("%-80s 0x%08lx.%-2d:%-2ld %10s", f->fullName().c_str(), (unsigned long)f->dwordAddr(), f->startBit(),
                   (unsigned long)f->get_size(), valStr);

            if (f->isEnumExists() && f->intToEnum(value, enumVal))
            {
                printf(" (%s)", enumVal.c_str());
            }
        }

        printf("\n");
    }
}
