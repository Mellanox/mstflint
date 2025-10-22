/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#ifndef MLXDPA_HOSTELF_H_
#define MLXDPA_HOSTELF_H_

#include <string>
#include <vector>

#include <tuple>
#include <dpa_elf/dpa_elf.h>

using namespace std;
using appArchDataHandle = DevObjHandle*;
using appArchManifestHandle = DevObjHandle*;

class HostElf
{
public:
    HostElf(string path, string outputPath);
    ~HostElf();

    vector<AppHandle*> GetListOfDpaApps();
    vector<std::tuple<appArchDataHandle, appArchManifestHandle>>
      GetListOfDpaArchApps(appArchDataHandle objTable,
                           uint64_t arch_count,
                          appArchManifestHandle procAttrsTable = nullptr);
    vector<u_int8_t> GetDpaApp(const DevObjHandle& app);
    vector<u_int8_t> GetManifestDpaApp(const DevObjHandle& app);
    void AddSection(string sectionName, const vector<u_int8_t>& section);
    void RemoveSection(string sectionName);

private:
    string _filePath;
    string _outputPath;
    vector<u_int8_t> _data;
    AppTable _dpaAppsTable;
};

#endif /* MLXDPA_HOSTELF_H_ */
