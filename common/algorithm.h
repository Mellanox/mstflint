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

#ifndef MSTFLINT_STRING_H
#define MSTFLINT_STRING_H

#ifdef USE_BOOST_ALGORITHM
#include <boost/algorithm/string.hpp>
#else
#include <algorithm>
#include <string>
#endif

namespace mstflint {
namespace common {
namespace algorithm {

#ifdef USE_BOOST_ALGORITHM
using boost::is_any_of;
using boost::algorithm::join;
using boost::algorithm::replace_all;
using boost::algorithm::replace_all_copy;
using boost::algorithm::split;
using boost::algorithm::to_lower;
using boost::algorithm::to_lower_copy;
using boost::algorithm::to_upper;
using boost::algorithm::to_upper_copy;
using boost::algorithm::trim;
using boost::algorithm::trim_left;
using boost::algorithm::trim_right;
#else
class is_any_of {
public:
  is_any_of() = delete;
  is_any_of(const std::string &set) : set_(set) {}
  is_any_of(const char *set) : set_(set) {}
  ~is_any_of() = default;
  is_any_of(const is_any_of &) = default;

  bool operator()(char c) { return std::string::npos != set_.find(c); }

private:
  std::string set_;
};

template <typename ContainerT>
std::string join(const ContainerT &items, const std::string &separator) {
  std::string out;
  if (items.empty())
    return out;
  int total_len = (items.size() - 1) * separator.length();
  for (auto s : items)
    total_len += s.length();
  out.reserve(total_len);
  out.append(items.front());
  for (auto it = std::next(items.begin()); it != items.end(); ++it)
    out.append(separator).append(*it);
  return out;
}

inline void replace_all(std::string &input, const std::string &search,
                        const std::string &format) {
  if (search.empty())
    return;
  size_t pos = 0;
  while (std::string::npos != (pos = input.find(search, pos))) {
    input.replace(pos, search.length(), format);
    pos += format.length();
  }
}

inline std::string replace_all_copy(const std::string &input,
                                    const std::string &search,
                                    const std::string &format) {
  std::string out = input;
  replace_all(out, search, format);
  return out;
}

template <typename ContainerT, typename PredicateT>
inline void split(ContainerT &output, const std::string &input,
                  PredicateT predicate) {
  output.clear();
  auto curr_begin = input.begin();
  auto curr_end = input.end();
  for (; input.end() !=
         (curr_end = std::find_if(curr_begin, input.end(), predicate));
       curr_begin = std::next(curr_end)) {
    output.push_back(std::string(curr_begin, curr_end));
  }
  output.push_back(std::string(curr_begin, curr_end));
  if (output.empty()) {
    output.push_back("");
  }
}

inline void to_lower(std::string &input) {
  std::transform(input.begin(), input.end(), input.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

inline std::string to_lower_copy(const std::string &input) {
  std::string output = input;
  to_lower(output);
  return output;
}

inline void to_upper(std::string &input) {
  std::transform(input.begin(), input.end(), input.begin(),
                 [](unsigned char c) { return std::toupper(c); });
}

inline std::string to_upper_copy(const std::string &input) {
  std::string output = input;
  to_upper(output);
  return output;
}

inline void trim_left(std::string &input) {
  input.erase(input.begin(),
              std::find_if_not(input.begin(), input.end(), [](unsigned char c) {
                return std::isspace(c);
              }));
}

inline void trim_right(std::string &input) {
  input.erase(std::find_if_not(input.rbegin(), input.rend(),
                               [](unsigned char c) { return std::isspace(c); })
                  .base(),
              input.end());
}

inline void trim(std::string &input) {
  trim_left(input);
  trim_right(input);
}
#endif

} // namespace algorithm
} // namespace common
} // namespace mstflint

#endif // MSTFLINT_STRING_H
