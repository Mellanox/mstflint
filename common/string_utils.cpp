/*
 * Copyright (c) 2020-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <cctype>
#include <algorithm>
#include <string>
#include "string_utils.h"

namespace string_utils
{
    std::string& trim(std::string& s)
    {
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        return s;
    }

    std::string trim_copy(std::string& s)
    {
        std::string out = s;

        return trim(out);
    }

    void to_lower(std::string& s)
    {
        transform(s.begin(), s.end(), s.begin(), [] (unsigned char c) { return std::tolower(c);
                  });
    }

    std::string to_lower_copy(std::string s)
    {
        std::string out = "";

        std::transform(s.begin(), s.end(), std::back_inserter(out),
                       [] (unsigned char c) { return std::tolower(static_cast < unsigned char > (c));
                       });
        return out;
    }

    std::string to_upper_copy(std::string s)
    {
        std::string out = "";

        transform(s.begin(), s.end(), back_inserter(out),
                  [] (unsigned char c) { return toupper(static_cast < unsigned char > (c));
                  });
        return out;
    }

    void replace_all(std::string& s, std::string const& to_replace, std::string const& replace_with)
    {
        std::string buffer;
        size_t      pos = 0;
        size_t      prev_pos;

        /* Reserves rough estimate of final size of std::string. */
        buffer.reserve(s.size());

        while (true) {
            prev_pos = pos;
            pos = s.find(to_replace, pos);
            if (pos == std::string::npos) {
                break;
            }
            buffer.append(s, prev_pos, pos - prev_pos);
            buffer += replace_with;
            pos += to_replace.size();
        }

        buffer.append(s, prev_pos, s.size() - prev_pos);
        s.swap(buffer);
    }

    std::string replace_all_copy(const std::string& s, std::string const& to_replace, std::string const& replace_with)
    {
        std::string buffer;
        std::string result = s;
        size_t      pos = 0;
        size_t      prev_pos;

        /* Reserves rough estimate of final size of std::string. */
        buffer.reserve(s.size());

        while (true) {
            prev_pos = pos;
            pos = result.find(to_replace, pos);
            if (pos == std::string::npos) {
                break;
            }
            buffer.append(result, prev_pos, pos - prev_pos);
            buffer += replace_with;
            pos += to_replace.size();
        }

        buffer.append(result, prev_pos, result.size() - prev_pos);
        result.swap(buffer);
        return result;
    }

    std::string join(list < std::string >& lst, const char* delim)
    {
        vector < std::string > strings(lst.begin(), lst.end());
        std::string result;

        switch (strings.size()) {
        case 0:
            result = "";
            break;

        case 1:
            result = strings[0];
            break;

        default:
            std::ostringstream os;
            copy(strings.begin(), strings.end() - 1, ostream_iterator < std::string > (os, delim));
            os << *strings.rbegin();
            result = os.str();
        }
        return result;
    }

    void split(vector < std::string >& result, std::string s, const char* separator)
    {
        if (s.size() == 0) {
            result.push_back(std::string(""));
            return;
        }
        /* Pointer to point the word returned by the strtok() function. */
        char * p;
        size_t size = strlen(s.c_str()) + 1;
        char * str = new char[size];

        strcpy(str, s.c_str());

        if (strncmp(separator, str, strlen(separator)) == 0) {
            /* if (separator[0] == str[0]) */
            result.push_back(std::string(""));
        }
        p = strtok(str, separator);
        while (p != NULL) {
            result.push_back(std::string(p));
            p = strtok(NULL, separator);
        }
        int         separator_len = strlen(separator);
        std::string suffix = s.substr(s.length() - separator_len);

        if (strncmp(separator, suffix.c_str(), separator_len) == 0) {
            result.push_back(std::string(""));
        }
        delete[] str;
    }
} /* namespace string_utils */
