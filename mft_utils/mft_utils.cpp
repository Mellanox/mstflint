/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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

#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <errno.h>

#include "mft_utils.h"

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
    char *endp;
    char *numStr = strcpy(new char[str.size() + 1], str.c_str());
    num = strtoul(numStr, &endp, base);
    if (*endp) {
        delete[] numStr;
        return false;
    }
    delete[] numStr;
    // check errno
    if (errno == ERANGE) {
        return false;
    }
    return true;
}

void splitCommaSperatedString(string str, vector<string> &strv)
{
    size_t pos;
    while ((pos = str.find(',')) != string::npos) {
        string tmp = str.substr(0, pos);
        strv.push_back((string)tmp);
        str = str.substr(pos + 1);
    }
    if (str != "") {
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
    for (string::size_type i=0; i < str.length(); ++i) {
        str[i] = std::tolower(str[i]);
    }
}

void to_uppercase(string& str)
{
    for (string::size_type i=0; i < str.length(); ++i) {
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

}
