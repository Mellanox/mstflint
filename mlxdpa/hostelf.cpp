/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "hostelf.h"
#include "mlxdpa_utils.h"

HostElf::HostElf(string path, string outputPath) : _filePath(path), _outputPath(outputPath)
{
    ifstream hostElf(_filePath, std::ios::binary);

    _data.assign((std::istreambuf_iterator<char>(hostElf)), std::istreambuf_iterator<char>());
        
    FILE* hostELF = fopen(_filePath.c_str(), "r");
    if (hostELF == NULL)
    {
        throw MlxDpaException("Failed to open Host ELF file with error: %s", strerror(errno));
    }

    //TODO should i release resources in _dpaAppsTable?
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