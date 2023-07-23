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

#include "mlxdpa_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "compatibility.h"

void RunCommand(string cmd, string errorMsg)
{
    MLX_DPA_DPRINTF(("Running command: %s\n", cmd.c_str()));
    int status = system(cmd.c_str());
    if (WIFEXITED(status))
    {
        MLX_DPA_DPRINTF(("Running command %s exited with status: %d\n", cmd.c_str(), WEXITSTATUS(status)));
    }
    else
    {
        MLX_DPA_DPRINTF(("Running command %s exited with signal no: %d\n", cmd.c_str(), WTERMSIG(status)));
        throw MlxDpaException(errorMsg.c_str());
    }
}

string OpenTempFile(string path, ofstream& f)
{
    path += "/XXXXXX";
    vector<char> dst_path(path.begin(), path.end());
    dst_path.push_back('\0');

    int fd = mkstemp(dst_path.data());

    if (fd == -1)
    {
        throw MlxDpaException("Failed to create file with error: %s", strerror(errno));
    }

    path.assign(dst_path.begin(), dst_path.end() - 1);
    f.open(path.c_str(), ios_base::trunc | ios_base::out);
    close(fd);

    return path;
}

vector<u_int8_t> ReadFromFile(string filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);
    if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
        fprintf(stderr, "Error opening '%s'\n", filename.c_str());
        exit(1);
    }

    // read the data:
    return vector<u_int8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

bool strToNum(const string& str, u_int32_t& num, int base)
{
    char* endp;
    char* numStr = strcpy(new char[str.size() + 1], str.c_str());
    num = strtoul(numStr, &endp, base);
    if (*endp)
    {
        delete[] numStr;
        return false;
    }
    delete[] numStr;
    // check errno
    if (errno == ERANGE)
    {
        return false;
    }
    return true;
}

bool ParseUUID(string uuidStr, u_int32_t uuid[])
{
    uuidStr.erase(std::remove(begin(uuidStr), end(uuidStr), '-'), end(uuidStr)); // erase-remove idiom

    if (uuidStr.length() != 32)
    {
        return false;
    }

    for (u_int32_t i = 0; i < 32; i += 8)
    {
        string str = uuidStr.substr(i, 8);
        if (!strToNum(str, uuid[i / 8], 16))
        {
            return false;
        }
    }

    return true;
}

void Crc16::operator<<(std::vector<u_int8_t> v)
{
    if (v.size() % 4)
    {
        fprintf(stderr, "Internal error: Image section size should be 4-bytes aligned");
        exit(1);
    }
    for (u_int32_t i = 0; i < v.size(); i += 4)
    {
        u_int32_t dw_be = __cpu_to_be32(*((u_int32_t*)(&v[i])));
        add(dw_be);
    }
}

void Crc16::add(u_int32_t o)
{
    if (_debug)
    {
        printf("Crc16::add(%08x)\n", o);
    }
    for (int i = 0; i < 32; i++)
    {
        if (_crc & 0x8000)
        {
            _crc = (((_crc << 1) | (o >> 31)) ^ 0x100b) & 0xffff;
        }
        else
        {
            _crc = ((_crc << 1) | (o >> 31)) & 0xffff;
        }
        o = (o << 1) & 0xffffffff;
    }
}

void Crc16::finish()
{
    for (int i = 0; i < 16; i++)
    {
        if (_crc & 0x8000)
        {
            _crc = ((_crc << 1) ^ 0x100b) & 0xffff;
        }
        else
        {
            _crc = (_crc << 1) & 0xffff;
        }
    }

    // Revert 16 low bits
    _crc = _crc ^ 0xffff;
}

MlxDpaException::MlxDpaException(const char* fmt, ...)
{
    const unsigned int max = 1024;
    char tmp[max];
    va_list args;

    va_start(args, fmt);
    vsnprintf(tmp, max, fmt, args);
    va_end(args);
    _err = tmp;
}