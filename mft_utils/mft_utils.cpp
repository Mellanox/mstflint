/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  mft_utils.cpp
 *
 *  Created on: April 3, 2017
 *      Author: Ahmad Soboh
 */

#include "mft_utils.h"
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <dirent.h>

#define APSKU_LEN 8

using namespace std;

namespace mft_utils
{
string numToStr(u_int32_t num)
{
    stringstream ss;
    ss << num;
    return ss.str();
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

void splitCommaSperatedString(string str, vector<string>& strv)
{
    size_t pos;
    while ((pos = str.find(',')) != string::npos)
    {
        string tmp = str.substr(0, pos);
        strv.push_back((string)tmp);
        str = str.substr(pos + 1);
    }
    if (str != "")
    {
        strv.push_back((string)str);
    }
}

void ltrim(string& str, const string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
}

void rtrim(string& str, const string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
}

void trim(string& str, const string& chars)
{
    rtrim(str, chars);
    ltrim(str, chars);
}

string ltrim_copy(string str, const string& chars)
{
    ltrim(str, chars);
    return str;
}

string rtrim_copy(string str, const string& chars)
{
    rtrim(str, chars);
    return str;
}

string trim_copy(string str, const string& chars)
{
    trim(str, chars);
    return str;
}

void to_lowercase(string& str)
{
    for (string::size_type i = 0; i < str.length(); ++i)
    {
        str[i] = std::tolower(str[i]);
    }
}

void to_uppercase(string& str)
{
    for (string::size_type i = 0; i < str.length(); ++i)
    {
        str[i] = std::toupper(str[i]);
    }
}

string to_lowercase_copy(string str)
{
    to_lowercase(str);
    return str;
}

string to_uppercase_copy(string str)
{
    to_uppercase(str);
    return str;
}

u_int32_t greatest_common_divisor(u_int32_t a, u_int32_t b)
{
    if (b == 0)
        return a;
    return greatest_common_divisor(b, a % b);
}

u_int32_t least_common_multiple(u_int32_t a, u_int32_t b)
{
    return (a * b) / greatest_common_divisor(a, b);
}

bool askUser(const char* question, bool force)
{
    if (question == NULL)
    {
        printf("\n Do you want to continue ? (y/n) [n] : ");
    }
    else
    {
        printf("\n %s ? (y/n) [n] : ", question);
    }

    if (force)
    {
        printf("y\n");
    }
    else
    {
        fflush(stdout);
        std::string answer;
        std::getline(std::cin, answer);

        if (strcasecmp(answer.c_str(), "y") && strcasecmp(answer.c_str(), "yes"))
        {
            return false;
        }
    }
    return true;
}
 
bool IsFileEmpty(const std::string& filePath, bool isBin)
{
     std::ifstream file(filePath, isBin ? std::ios::binary : std::ios::in);
     if (!file.is_open())
     {
         throw runtime_error("Can not open " + filePath + ": " + string(strerror(errno)));
     }
     file.seekg(0, std::ios::end);
     return file.tellg() == 0;
 }
 
 vector<u_int8_t> ReadBinFile(string file)
 {
     FILE* fh;
 
     if ((fh = fopen(file.c_str(), "rb")) == NULL)
     {
         throw runtime_error("Can not open " + file + ": " + string(strerror(errno)));
     }
 
     if (fseek(fh, 0, SEEK_END) < 0)
     {
         fclose(fh);
         throw runtime_error("Failed to get size of the file " + file + ": " + string(strerror(errno)));
     }
 
     int read_file_size = ftell(fh);
     if (read_file_size < 0)
     {
         fclose(fh);
         throw runtime_error("Failed to get size of the file " + file + ": " + string(strerror(errno)));
     }
     rewind(fh);
 
     vector<u_int8_t> buf(read_file_size);
     if (fread(buf.data(), 1, read_file_size, fh) != (size_t)read_file_size)
     {
         fclose(fh);
         throw runtime_error("Failed to read from " + file + ": " + string(strerror(errno)));
     }
     fclose(fh);
 
     return buf;
 }
 
 void WriteToBinFile(string filePath, const std::vector<u_int8_t>& buff)
 {
     FILE* fh = fopen(filePath.c_str(), "wb");
     if (fh == NULL)
     {
         throw runtime_error("Can not open " + filePath + ": " + string(strerror(errno)));
     }
     if (fwrite(&buff[0], 1, buff.size(), fh) != buff.size())
     {
         fclose(fh);
         throw runtime_error("Failed to write to " + filePath + ": " + string(strerror(errno)));
     }
     fclose(fh);
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

 std::vector<uint8_t> HexStringToBytes(const std::vector<uint8_t>& keyBytes)
 {
     std::vector<uint8_t> bytes;
 
     if (keyBytes.size() % 2 != 0)
     {
         throw runtime_error("Key data has an odd length.");
     }
 
     for (size_t i = 0; i < keyBytes.size(); i += 2)
     {
         std::string byteString{static_cast<char>(keyBytes[i]), static_cast<char>(keyBytes[i + 1])};
         uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
         bytes.push_back(byte);
     }
 
     return bytes;
 }
 
 vector<u_int8_t> HexStringToBytes(const string& str)
 {
     vector<u_int8_t> bytes;
     if (str.length() % 2)
     {
         throw runtime_error("given string is not a valid hex number");
     }
     for (size_t i = 0; i < str.length(); i += 2)
     {
         u_int8_t byte = static_cast<u_int8_t>(std::stoul(str.substr(i, 2).c_str(), nullptr, 16));
         bytes.push_back(byte);
     }
     return bytes;
 }
 
 string ToHexString(u_int32_t value, u_int8_t width)
 {
     std::stringstream ss;
     ss << "0x" << std::hex << std::setw(width) << std::setfill('0') << value;
     return ss.str();
 }
 
string ToHexString(const vector<u_int8_t>& vec)
{
    std::ostringstream oss;
    for (const auto& fixedValue : vec)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(fixedValue);
    }
    return oss.str();
}
 
 std::string ToString(const uint32_t* data, size_t wordCount, bool stayInHex)
 {
     std::ostringstream oss;
 
     for (size_t i = 0; i < wordCount; ++i)
     {
         uint32_t num = data[i];
 
         uint8_t bytes[4] = {static_cast<uint8_t>((num >> 24) & 0xFF), static_cast<uint8_t>((num >> 16) & 0xFF),
                             static_cast<uint8_t>((num >> 8) & 0xFF), static_cast<uint8_t>(num & 0xFF)};
 
         for (int k = 0; k < 4; ++k)
         {
             uint8_t b = bytes[k];
             if (stayInHex)
             {
                 oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(b);
             }
             else
             {
                 if (b == 0)
                     continue;
                 oss << static_cast<char>(b);
             }
         }
     }
 
     if (stayInHex)
         oss << std::dec;
     return oss.str();
 }
 
vector<u_int8_t> ToVector(const u_int32_t* arr, size_t size)
{
    vector<u_int8_t> vec;
    vec.reserve(16);

    for (size_t i = 0; i < size; ++i)
    {
        const u_int8_t mask = 0xFF;
        u_int32_t value = arr[i];

        for (int j = 0; j < 4; ++j)
        {
            u_int8_t byte = value & mask;
            vec.push_back(byte);
            value >>= 8;
        }
    }
    return vec;
}

bool ToVector(string& str, vector<u_int8_t>& vec)
 {
     if (str.length() % 2 != 0)
     {
         return false;
     }
 
     vec.clear();
     for (size_t i = 0; i < str.length(); i += 2)
     {
         string byteString = str.substr(i, 2);
         uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
         vec.push_back(byte);
     }
     return true;
 }
 
 std::vector<u_int32_t> Uuid2Dword(const std::string& uuid_str)
 {
     std::vector<u_int32_t> uuid;
     uuid.resize(4);
 
     for (int i = 0; i < 4; ++i)
     {
         std::string chunk = uuid_str.substr(i * 8, 8);
         uuid[i] = (u_int32_t)strtoul(chunk.c_str(), nullptr, 16);
     }
     return uuid;
}

} // namespace mft_utils
