/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * mlxarchive_mfa2_utils.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <sys/stat.h>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <boost/filesystem.hpp>

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

bool fexists(const std::string& filename) {
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
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
        string file_extension  = boost::filesystem::extension(entry->d_name);
        if(file_extension == ".bin") {
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
