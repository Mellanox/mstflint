/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXTKNGNERATOR_UTILS_H_
#define MLXTKNGNERATOR_UTILS_H_

#include <vector>
#include <string>
#include <exception>
#include <stdarg.h>
#include "common/compatibility.h"

#define MLX_TOKEN_DPRINTF(args)                      \
    do                                               \
    {                                                \
        char* reacDebug = getenv("MLX_TOKEN_DEBUG"); \
        if (reacDebug != NULL)                       \
        {                                            \
            printf("\33[2K\r");                      \
            printf("[MLX_TOKEN_DEBUG]: ");           \
            printf args;                             \
            fflush(stdout);                          \
        }                                            \
    } while (0)

using namespace std;

struct DebugFwFileData
{
    string filename;
    string psid;
    string debugFwVersion;
};

vector<u_int8_t> ReadFromFile(string filename);
string GetSafePsid(const string& psid);
DebugFwFileData GetDebugFwFileData(const string& filename);

enum class MlxTknGeneratorErrorCode : int
{
    Generic = 0,
    AggregatedTokenFull = 1,
};

class MlxTknGeneratorException : public exception
{
private:
    void initMessage(const char* fmt, va_list args)
    {
        const unsigned int max = 1024;
        char tmp[max];
        vsnprintf(tmp, max, fmt, args);
        _err = tmp;
    }

public:
    std::string _err;
    MlxTknGeneratorErrorCode _errCode;

    MlxTknGeneratorException(const char* fmt, ...) : _errCode(MlxTknGeneratorErrorCode::Generic)
    {
        va_list args;
        va_start(args, fmt);
        initMessage(fmt, args);
        va_end(args);
    }

    MlxTknGeneratorException(MlxTknGeneratorErrorCode errCode, const char* fmt, ...) : _errCode(errCode)
    {
        va_list args;
        va_start(args, fmt);
        initMessage(fmt, args);
        va_end(args);
    }

    ~MlxTknGeneratorException() throw(){};
    virtual const char* what() const throw() { return _err.c_str(); }
    int getErrorCode() const { return static_cast<int>(_errCode); }
};

#endif /* MLXTKNGNERATOR_UTILS_H_ */