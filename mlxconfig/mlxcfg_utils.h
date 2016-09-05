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

#define FIFTH_GENERATION_LIST "Connect-IB/Connect-X4/LX"
#define FOURTH_GENERATION_LIST "ConnectX3/Pro"

#include <string>
#include <vector>

#include <mtcr.h>
#include <reg_access/reg_access.h>

using namespace std;

enum QueryType {
    QueryNext,
    //QueryCurrent,
    QueryDefault
};

#define VECTOR_ITERATOR(t, v, i) \
    for(vector<t>::iterator i = v.begin() ; i != v.end(); ++i)

#define SET_ITERATOR(t, v, i) \
    for(std::set<t>::iterator i = v.begin() ; i != v.end(); ++i)

#define MAP_ITERATOR(t1, t2, m, i) \
    for(std::map<t1,t2>::iterator i = m.begin() ; i != m.end(); ++i)

/*
 * Debug print MACRO of the NV Tlvs:
 */
//#define _ENABLE_DEBUG_
#ifdef _ENABLE_DEBUG_
# define DEBUG_PRINT_SEND(data_struct, struct_name)\
    printf("-I- Data Sent:\n");\
    tools_open_##struct_name##_print(data_struct, stdout, 1)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)\
    printf("-I- Data Recieved:\n");\
    tools_open_##struct_name##_print(data_struct, stdout, 1)
#else
# define DEBUG_PRINT_SEND(data_struct, struct_name)
# define DEBUG_PRINT_RECIEVE(data_struct, struct_name)
#endif

#define CHECK_RC(rc)\
    if (rc) return rc;

#define MLXCFG_UNKNOWN 0xffffffff

void dealWithSignal();

MError mnvaCom5thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t tlvType, reg_access_method_t method, bool getDefault=false);

MError nvqcCom5thGen(mfile* mf, u_int32_t tlvType, bool& suppRead, bool& suppWrite);

bool strToNum(std::string str, u_int32_t& num, int base=0);

std::string numToStr(u_int32_t num);

vector<string> splitStr(const string s, char d);

string mlxcfg_rtrim(string s);

string mlxcfg_ltrim(string s);

string mlxcfg_trim(string s);

class MlxcfgException {
public:
    std::string _err;
    MlxcfgException(const char* fmt, ...);
    ~MlxcfgException() {};
};
#endif /* MLXCFG_UTILS_H_ */
