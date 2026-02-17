/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 *
 *
 * mlxcfg_utils.h
 *
 *  Created on: Jun 20, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_UTILS_H_
#define MLXCFG_UTILS_H_

#define IDENT "    "
#define IDENT2 IDENT IDENT
#define IDENT3 "\t\t"
#define IDENT4 IDENT2 IDENT

#include <string>
#include <vector>

#include <mtcr.h>
#include <reg_access/reg_access.h>

using namespace std;

enum QueryType
{
    QueryNext,
    QueryCurrent,
    QueryDefault
};

#define QUERY_NEXT_MASK (1 << QueryNext)
#define QUERY_CURRENT_MASK (1 << QueryCurrent)
#define QUERY_DEFAULT_MASK (1 << QueryDefault)

enum WriterId
{
    WRITER_ID_UNSPECIFIED = 0x0,
    WRITER_ID_CHASSIS_BMC = 0x1,
    WRITER_ID_MAD = 0x2,
    WRITER_ID_BMC = 0x3,
    WRITER_ID_CMD_IF = 0x4,
    WRITER_ID_ICMD = 0x5,
    WRITER_ID_ICMD_UEFI_HII = 0x6,
    WRITER_ID_ICMD_UEFI_CLP = 0x7,
    WRITER_ID_ICMD_FLEXBOOT = 0x8,
    WRITER_ID_ICMD_MLXCONFIG = 0x9,
    WRITER_ID_ICMD_USER1 = 0xa,
    WRITER_ID_ICMD_USER2 = 0xb,
    WRITER_ID_ICMD_MLXCONFIG_SET_RAW = 0xc,
    WRITER_ID_OTHER = 0x1f,
    WRITER_ID_LAST = 0x20
};

enum RawTlvMode
{
    SET_RAW,
    GET_RAW
};

typedef enum
{
    UNSUPPORTED_DEVICE = -1,
    HCA = 0,
    Switch = 1,
    LinkX = 2,
    Retimer
} Device_Type;

#define VECTOR_ITERATOR(t, v, i) for (vector<t>::iterator i = v.begin(); i != v.end(); ++i)

#define CONST_VECTOR_ITERATOR(t, v, i) for (vector<t>::const_iterator i = v.begin(); i != v.end(); ++i)

#define SET_ITERATOR(t, v, i) for (std::set<t>::iterator i = v.begin(); i != v.end(); ++i)

#define MAP_ITERATOR(t1, t2, m, i) for (std::map<t1, t2>::iterator i = m.begin(); i != m.end(); ++i)

#define VECTOR_BE32_TO_CPU(buff)                   \
    for (unsigned int i = 0; i < buff.size(); i++) \
    {                                              \
        buff[i] = __be32_to_cpu(buff[i]);          \
    }

#define MAX_ARRAY_SIZE 32

/*
 * Debug print MACRO of the NV Tlvs:
 * do { ... } while (0) makes multi-statement macros safer
 */
bool mlxcfg_is_debug_enabled();

#define DEBUG_PRINT_SEND(data_struct, struct_name)                    \
    do                                                                \
    {                                                                 \
        if (mlxcfg_is_debug_enabled())                                \
        {                                                             \
            printf("-I- Data Sent:\n");                               \
            tools_open_##struct_name##_print(data_struct, stdout, 1); \
        }                                                             \
    } while (0)

#define DEBUG_PRINT_RECEIVE(data_struct, struct_name)                 \
    do                                                                \
    {                                                                 \
        if (mlxcfg_is_debug_enabled())                                \
        {                                                             \
            printf("-I- Data Received:\n");                           \
            tools_open_##struct_name##_print(data_struct, stdout, 1); \
        }                                                             \
    } while (0)

#define MLXCFG_UNKNOWN 0xffffffff

typedef enum
{
    Device_Name,
    Device_Description
} info_type_t;

void dealWithSignal();

MError mnvaCom5thGen(mfile* mf,
                     u_int8_t* buff,
                     u_int16_t len,
                     u_int32_t tlvType,
                     reg_access_method_t method,
                     QueryType qT = QueryNext,
                     bool is_host_id_valid = false);

MError nvqcCom5thGen(mfile* mf, u_int32_t tlvType, bool& suppRead, bool& suppWrite, u_int32_t& version);

MError nvdiCom5thGen(mfile* mf, u_int32_t tlvType, bool is_host_id_valid = false);

bool strToNum(std::string str, u_int32_t& num, int base = 0);

std::string numToStr(u_int32_t num, bool isHex = false);
std::string numToStrFormatted(u_int32_t num, bool isHex = false);

vector<string> splitStr(const string s, char d);

string mlxcfg_rtrim(string s);

string mlxcfg_ltrim(string s);

string mlxcfg_trim(string s);

string writerIdToStr(WriterId writerId);

void copyDwVectorToBytesVector(const vector<u_int32_t>& dwV, vector<u_int8_t>& bV);

void copyBytesVectorToDwVector(const vector<u_int8_t>& bV, vector<u_int32_t>& dwV);

string parseIndexStr(const string& indexedMlxconfigName);

void parseIndexedMlxconfigName(const string& indexedMlxconfigName, string& mlxconfigName, u_int32_t& index);

void extractIndexes(const string& indexesStr, vector<u_int32_t>& indexes);

bool isContinuanceArray(const string& mlxconfigName);

bool isIndexedStartFromOneSupported(const string& mlxconfigName);

string increaseIndexIfNeeded(const string& name);

bool isIndexedMlxconfigName(const string& mlxconfigName);

string getConfigNameWithSuffixByInterval(string mlxconfigName, u_int32_t interval);

string getArraySuffixByInterval(u_int32_t interval);

string getArraySuffix(const string& mlxconfigName);

string getArrayPrefix(const string& mlxconfigName);

bool getDeviceInformationString(mfile* mf, info_type_t op, vector<char>& infoString);

Device_Type getDeviceTypeFromString(string inStr);

string getTempFolder();
void parseSystemConfName(const string& fullName, string& name, int& asic);

class MlxcfgException : public exception
{
public:
    std::string _err;
    MlxcfgException(const char* fmt, ...);
    ~MlxcfgException() throw(){};
    virtual const char* what() const throw() { return _err.c_str(); }
};

class MlxcfgTLVNotFoundException : public MlxcfgException
{
public:
    MlxcfgTLVNotFoundException(const char* cTLVName);
    ~MlxcfgTLVNotFoundException() throw(){};
};

#endif /* MLXCFG_UTILS_H_ */
