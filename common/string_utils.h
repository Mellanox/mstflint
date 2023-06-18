/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <string>
#include <vector>
#include <list>
#include <string>
using namespace std;

#pragma once

namespace string_utils
{
    string& trim(string& s);
    string trim_copy(string& s);
    string to_lower_copy(string s);
    void to_lower(string& s);
    string to_upper_copy(string s);
    void replace_all(string& s, string const& to_replace, string const& replace_with);
    string replace_all_copy(const string& s, string const& to_replace, string const& replace_with);
    string join(list < string >& lst, const char* delim);
    void split(vector < string >& result, string s, const char* separator);
} /* namespace string_utils */
