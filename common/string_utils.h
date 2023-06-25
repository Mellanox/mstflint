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

#pragma once

namespace string_utils
{
    std::string& ltrim(std::string& s);
    std::string& rtrim(std::string& s);
    std::string& trim(std::string& s);
    std::string trim_copy(const std::string& s);
    std::string to_lower_copy(std::string s);
    void to_lower(std::string& s);
    std::string to_upper_copy(std::string s);
    void replace_all(std::string& s, std::string const& to_replace, std::string const& replace_with);
    std::string replace_all_copy(const std::string& s, std::string const& to_replace, std::string const& replace_with);
    std::string join(std::list < std::string >& lst, const char* delim);
    void split(std::vector < std::string >& result, std::string s, const char* separator);
} /* namespace string_utils */
