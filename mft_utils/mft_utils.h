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
 *  Created on: April 3, 2017
 *      Author: Ahmad Soboh
 *
 */

#ifndef MFT_UTILS_H_
#define MFT_UTILS_H_

#include <string>
#include <vector>

#include <compatibility.h>

using namespace std;

namespace mft_utils
{

string numToStr(u_int32_t num);

bool strToNum(const string& str, u_int32_t& num, int base);

void splitCommaSperatedString(string str, vector<string> &strv);


void ltrim(string& str, const string& chars = "\t\n\v\f\r "); 
void rtrim(string& str, const string& chars = "\t\n\v\f\r ");
void trim(string& str, const string& chars = "\t\n\v\f\r ");
string ltrim_copy(string str, const string& chars = "\t\n\v\f\r ");
string rtrim_copy(string str, const string& chars = "\t\n\v\f\r ");
string trim_copy(string str, const string& chars = "\t\n\v\f\r ");

void to_lowercase(string& str);
void to_uppercase(string& str);
string to_lowercase_copy(string str);
string to_uppercase_copy(string str);

}
#endif /* MFT_UTILS_H_ */
