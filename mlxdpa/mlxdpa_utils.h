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

#ifndef MLXDPA_UTILS_H_
#define MLXDPA_UTILS_H_

#include <string>
#include <exception>
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

void RunCommand(string cmd, string errorMsg);

string OpenTempFile(string path, ofstream& f);

vector<u_int8_t> ReadFromFile(string filename);

bool strToNum(const string& str, u_int32_t& num, int base);

bool ParseUUID(string uuidStr, u_int32_t uuid[]);

class Crc16
{
public:
    Crc16(bool d = false) : _debug(d) { clear(); }
    u_int16_t get() { return _crc; }
    void clear() { _crc = 0xffff; }
    void operator<<(u_int32_t val) { add(val); }
    void operator<<(std::vector<u_int8_t> v);
    void add(u_int32_t val);
    void finish();

private:
    u_int16_t _crc;
    bool _debug;
};

class MlxDpaException : public exception
{
public:
    std::string _err;
    MlxDpaException(const char* fmt, ...);
    ~MlxDpaException() throw(){};
    virtual const char* what() const throw() { return _err.c_str(); }
};

#endif /* MLXDPA_UTILS_H_ */