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

#include <iostream>
#include <fstream>
#include <cstring>
#include "hostelf.h"
#include "mlxdpa_utils.h"

HostElf::HostElf(string path, string outputPath) : _filePath(path), _outputPath(outputPath)
{
    ifstream hostElf(_filePath, std::ios::binary);
    _data.assign(std::istreambuf_iterator<char>(hostElf), std::istreambuf_iterator<char>());

    const char elfMagicNumber[5] = {0x7f, 0x45, 0x4c, 0x46, 0x0};
    if (_data.size() < 4 || string(_data.begin(), _data.begin() + 4).compare(elfMagicNumber) != 0)
    {
        throw MlxDpaException("Provided Host ELF is not an ELF file.");
    }

    FILE* hostELF = fopen(_filePath.c_str(), "r");
    if (hostELF == NULL)
    {
        throw MlxDpaException("Failed to open Host ELF file with error: %s", strerror(errno));
    }
    // TODO should i release resources in _dpaAppsTable?
    _dpaAppsTable = getAppList(hostELF);

    if (_outputPath.empty())
    {
        _outputPath = _filePath;
    }
    else
    {
        string cmd("cp " + _filePath + " " + _outputPath);
        RunCommand(cmd, "Failed to create output file");
    }
    fclose(hostELF);
}

vector<AppHandle*> HostElf::GetListOfDpaApps()
{
    vector<AppHandle*> apps;
    AppHandle* handle = _dpaAppsTable.table;

    for (uint64_t i = 0; i < _dpaAppsTable.count; i++)
    {
        apps.push_back(handle);
        handle++;
    }

    return apps;
}

vector<u_int8_t> HostElf::GetDpaApp(const AppHandle& app)
{
    auto dpaAppBegin = _data.begin() + app.offset;
    auto dpaAppEnd = dpaAppBegin + app.size;
    return vector<u_int8_t>(dpaAppBegin, dpaAppEnd);
}

void HostElf::AddSection(string sectionName, const vector<u_int8_t>& section)
{
    ofstream sectionFile;
    string sectionFilePath = OpenTempFile("/tmp", sectionFile);

    if (!sectionFile.is_open())
    {
        throw MlxDpaException("Failed writing to disk.");
    }

    for (const auto& byte : section)
    {
        sectionFile << byte;
    }
    sectionFile.close();

    string cmd("objcopy --add-section " + sectionName + "=" + sectionFilePath + " --set-section-flags " + sectionName +
               "=noload,readonly " + _outputPath + " " + _outputPath);
    RunCommand(cmd, "Failed to add section to Host ELF");

    if (remove(sectionFilePath.c_str()) != 0)
    {
        throw MlxDpaException("Failed to delete temp file with error: %s", strerror(errno));
    }
}

void HostElf::RemoveSection(string sectionName)
{
    string cmd("objcopy --remove-section " + sectionName + " " + _outputPath);
    RunCommand(cmd, "Failed to remove section from Host ELF");
}
