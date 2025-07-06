/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#include "tools_regex.h"

#include <sstream>

#if defined USE_STDLIB_REGEX

namespace mstflint
{
namespace common
{
namespace regex
{

bool regex_search(std::string::const_iterator first,
                  std::string::const_iterator last,
                  match_results<std::string::const_iterator>& m,
                  const regex& e)
{
    regmatch_t matches[REGEX_MAX_SUBEXPRESSIONS + 1];
    for (size_t i = 0; i < sizeof(matches) / sizeof(matches[0]); ++i)
    {
        matches[i].rm_so = -1;
        matches[i].rm_eo = -1;
    }
    std::string s(first, last);
    int ret =
      regexec(&e.regex_, s.c_str(), sizeof(matches) / sizeof(matches[0]), static_cast<regmatch_t*>(&matches[0]), 0);
    if (-1 != matches[REGEX_MAX_SUBEXPRESSIONS].rm_so)
    {
        throw regex_error("Max number of subexpressions is reached");
    }
    m.clear();
    for (size_t i = 0; i < sizeof(matches) / sizeof(matches[0]); ++i)
    {
        m.append(first + matches[i].rm_so, first + matches[i].rm_eo, -1 != matches[i].rm_so);
    }
    if (0 == ret)
    {
        m.set_prefix(first, m[0].first);
        m.set_suffix(m[0].second, last);
        return true;
    }
    return false;
}

bool regex_match(const std::string& s, const regex& e)
{
    regmatch_t matches;
    int ret = regexec(&e.regex_, s.c_str(), 1, &matches, 0);
    if (0 == ret && 0 == matches.rm_so && static_cast<int>(s.size()) == matches.rm_eo)
    {
        return true;
    }
    return false;
}

std::string regex_replace(const std::string& s, const regex& e, const std::string& fmt)
{
    if (s.empty())
        return "";
    smatch match;
    auto curr = s.cbegin();
    std::ostringstream output;
    while (curr != s.end() && regex_search(curr, s.end(), match, e))
    {
        output << std::string(curr, match[0].first) << fmt;
        curr = match[0].second;
    }
    output << std::string(curr, s.end());
    return output.str();
}

} // namespace regex
} // namespace common
} // namespace mstflint

#endif
