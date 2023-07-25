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

#ifndef MLXDPA_HOSTELF_H_
#define MLXDPA_HOSTELF_H_

#include <string>
#include <vector>
#include <dpa_elf/dpa_elf.h>

using namespace std;

class HostElf
{
public:
    HostElf(string path, string outputPath);

    vector<AppHandle*> GetListOfDpaApps();
    vector<u_int8_t> GetDpaApp(const AppHandle& app);
    void AddSection(string sectionName, const vector<u_int8_t>& section);
    void RemoveSection(string sectionName);

private:
    string _filePath;
    string _outputPath;
    vector<u_int8_t> _data;
    AppTable _dpaAppsTable;
};

#endif /* MLXDPA_HOSTELF_H_ */