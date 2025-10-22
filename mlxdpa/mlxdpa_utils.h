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

 #ifndef MLXDPA_UTILS_H_
 #define MLXDPA_UTILS_H_
 
#include <exception>
#include <string>
#include <vector>
#include <stdarg.h>
#define MLX_DPA_DPRINTF(args)                      \
    do                                             \
    {                                              \
        char* reacDebug = getenv("MLX_DPA_DEBUG"); \
        if (reacDebug != NULL)                     \
        {                                          \
            printf("\33[2K\r");                    \
            printf("[MLX_DPA_DEBUG]: ");           \
            printf args;                           \
            fflush(stdout);                        \
        }                                          \
    } while (0)

#define CPUTOn(s, n)                                \
    do                                              \
    {                                               \
        u_int32_t* p = (u_int32_t*)(s);             \
        for (u_int32_t ii = 0; ii < (n); ii++, p++) \
            *p = __cpu_to_be32(*p);                 \
    } while (0)

using namespace std;

const int NUM_OF_RET_VALS = 6;

const string updateSigErrors[NUM_OF_RET_VALS] = {"Successfully updated signature blob.",
                                                 "Signature section larger than expected.",
                                                 "Bad param.",
                                                 "File not accessible.",
                                                 "Signature section not found.",
                                                 "Invalid multi arch signature section."};
                                             
void RunCommand(string cmd, string errorMsg);

string OpenTempFile(string path, ofstream& f);

vector<u_int8_t> ReadFromFile(string filename);

bool strToNum(const string& str, u_int32_t& num, int base);

bool ParseUUID(string uuidStr, u_int32_t uuid[]);

class MlxDpaException : public exception
{
public:
    std::string _err;
    MlxDpaException(const char* fmt, ...);
    ~MlxDpaException() throw(){};
    virtual const char* what() const throw() { return _err.c_str(); }
};

#endif /* MLXDPA_UTILS_H_ */
