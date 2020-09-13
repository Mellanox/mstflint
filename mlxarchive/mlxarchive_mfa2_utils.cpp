
/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

/*
 * mlxarchive_mfa2_utils.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <cstdlib>
#include <sys/stat.h>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "mlxarchive_mfa2_utils.h"

void packString(const string& str, vector<u_int8_t>& buff)
{
    for(unsigned int i = 0; i < str.length(); i++) {
        buff.push_back((u_int8_t)str[i]);
    }
}

void packBytesArray(const u_int8_t* arr, unsigned int len, vector<u_int8_t>& buff)
{
    for(unsigned int i = 0; i < len; i++) {
        buff.push_back(arr[i]);
    }
}

void unpackBytesArray(u_int8_t* arr, unsigned int len, vector<u_int8_t>& buff)
{
    for (unsigned int i = 0; i < len; i++) {
        arr[i] = buff[i];
    }
}
void packBinFile(const string& file, vector<u_int8_t>& buff)
{
    vector<u_int8_t> fileBuff;
    streampos size;

    std::ifstream ifs(file.c_str(), ios::in|ios::binary|ios::ate);

    if (ifs.fail()) {
        //TODO throw PLDMException("Failed to open file: %s", file.c_str());
        return;
    }
    size = ifs.tellg();
    fileBuff.resize((size_t)size);
    ifs.seekg(0, ios::beg);
    ifs.read((char*)fileBuff.data(), size);
    ifs.close();

    packBytesArray(fileBuff.data(), fileBuff.size(), buff);
}

bool readFromFile(const string& fname, string& content)
{
    std::ifstream ifs(fname.c_str());
    if (ifs.fail()) {
        return false;
    }
    for (std::string line; std::getline(ifs, line);) {
        content += line;
    }
    return true;

}

unsigned int getFileSize(const string& file)
{
    struct stat stat_buf;

    int rc = stat(file.c_str(), &stat_buf);

    if (!rc) {
        //printf("stat_buf.st_size=%d\n", stat_buf.st_size);
        return stat_buf.st_size;
    }

    return 0; //TODO throw exception
}

bool fexists(const std::string& filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

// check if filename points to regular file:
bool isFile(const std::string& filename)
{
    struct stat buffer;
    stat(filename.c_str(), &buffer);
    return S_ISREG(buffer.st_mode); 
}

bool endsWith(const std::string& str, const std::string& suffix)
{
    return (str.size() >= suffix.size()) && (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
}

void listDir(const char *path, vector<string>& files)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory: %s\n", path);
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if(endsWith(entry->d_name, ".bin")) {
            files.push_back(entry->d_name);
        }
        else {
            // skipping hidden files
            if(entry->d_name[0] != '.') {
                fprintf(stderr, "Skipping file: %s, not a binary...\n", entry->d_name);
            }
        }
    }
    if(files.empty()) {
        fprintf(stderr, "No binray files found in the given directory: %s\n", path);
        exit(1);
    }

    closedir(dir);
}
