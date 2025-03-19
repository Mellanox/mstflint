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

#ifndef MSTFLINT_REGEX_H
#define MSTFLINT_REGEX_H

#include "config.h"

#if defined USE_BOOST_REGEX
#include <boost/regex.hpp>
#elif defined USE_STDLIB_REGEX
#include <regex.h>
#include <stdexcept>
#include <string>
#include <vector>
#else
#include <regex>
#endif

namespace mstflint {
namespace common {
namespace regex {
#if defined USE_BOOST_REGEX
using boost::match_results;
using boost::regex;
using boost::regex_error;
using boost::regex_match;
using boost::regex_replace;
using boost::regex_search;
using boost::smatch;
using boost::sregex_iterator;
#elif defined USE_STDLIB_REGEX

const size_t REGEX_MAX_SUBEXPRESSIONS = 16;

class regex_error : public std::runtime_error {
public:
  regex_error() = delete;
  ~regex_error() = default;
  explicit regex_error(const std::string &message)
      : std::runtime_error(message) {}
  regex_error &operator=(const regex_error &) = delete;
};

class regex {
public:
  regex() : regex_() {
    // Initialize regex_ to an empty regex
    int ret = regcomp(&regex_, "", REG_EXTENDED);
    if (0 != ret) {
      size_t error_string_size = regerror(
          ret, &regex_, static_cast<char *>(nullptr), static_cast<size_t>(0));
      std::vector<char> error_string_buf(error_string_size);
      regerror(ret, &regex_, error_string_buf.data(), error_string_buf.size());
      throw regex_error(
          std::string(error_string_buf.begin(), error_string_buf.end()));
    }
  }
  ~regex() { regfree(&regex_); };
  regex(const regex &other) : pattern_(other.pattern_) {
    int ret = regcomp(&regex_, other.pattern_.c_str(), REG_EXTENDED);
    if (0 != ret) {
      size_t error_string_size = regerror(
          ret, &regex_, static_cast<char *>(nullptr), static_cast<size_t>(0));
      std::vector<char> error_string_buf(error_string_size);
      regerror(ret, &regex_, error_string_buf.data(), error_string_buf.size());
      throw regex_error(
          std::string(error_string_buf.begin(), error_string_buf.end()));
    }
  }
  regex(regex &&other) noexcept : pattern_(std::move(other.pattern_)), regex_(other.regex_) {
    other.regex_.re_nsub = 0; // Invalidate the moved-from regex object
  }
  explicit regex(const std::string &pattern) : pattern_(pattern) {
    int ret = regcomp(&regex_, pattern.c_str(), REG_EXTENDED);
    if (0 != ret) {
      size_t error_string_size = regerror(
          ret, &regex_, static_cast<char *>(nullptr), static_cast<size_t>(0));
      std::vector<char> error_string_buf(error_string_size);
      regerror(ret, &regex_, error_string_buf.data(), error_string_buf.size());
      throw regex_error(
          std::string(error_string_buf.begin(), error_string_buf.end()));
    }
  }
  regex &operator=(const regex &other) {
    if (this != &other) {
      regfree(&regex_);
      pattern_ = other.pattern_;
      int ret = regcomp(&regex_, other.pattern_.c_str(), REG_EXTENDED);
      if (0 != ret) {
        size_t error_string_size = regerror(
            ret, &regex_, static_cast<char *>(nullptr), static_cast<size_t>(0));
        std::vector<char> error_string_buf(error_string_size);
        regerror(ret, &regex_, error_string_buf.data(), error_string_buf.size());
        throw regex_error(
            std::string(error_string_buf.begin(), error_string_buf.end()));
      }
    }
    return *this;
  }
  regex &operator=(regex &&other) noexcept {
    if (this != &other) {
      regfree(&regex_);
      pattern_ = std::move(other.pattern_);
      regex_ = other.regex_;
      other.regex_.re_nsub = 0; // Invalidate the moved-from regex object
    }
    return *this;
  }

public:
  std::string pattern_;
  regex_t regex_;
};

template <class BiDiIterator>
class sub_match : public std::pair<BiDiIterator, BiDiIterator> {
public:
  sub_match() = default; // TODO delete - hint scoped_ptr prefix/suffix
  ~sub_match() = default;
  sub_match(const sub_match &) = default;
  sub_match(const BiDiIterator &first, const BiDiIterator &second)
      : std::pair<BiDiIterator, BiDiIterator>(first, second) {}
  operator std::string() const {
    return std::string(this->first, this->second);
  }
  std::string str() const { return std::string(this->first, this->second); }
  sub_match &operator=(const sub_match &) =
      default; // TODO delete - hint scoped_ptr prefix/suffix
};

template <class BiDiIterator>
bool operator==(const std::string &lhs, sub_match<BiDiIterator> rhs) {
  return lhs == std::string(rhs);
}

template <class BiDiIterator> class match_results {
public:
  match_results() = default;
  ~match_results() = default;
  match_results(const match_results &) = delete;
  match_results &operator=(const match_results &) = delete;

  typedef sub_match<BiDiIterator> value_type;
  typedef std::vector<value_type> vector_type;
  typedef typename vector_type::const_iterator const_iterator;
  typedef typename vector_type::const_reference const_reference;
  typedef typename std::iterator_traits<BiDiIterator>::difference_type difference_type;

  const_iterator begin() const { return subs_.begin(); }
  const_iterator end() const { return subs_.end(); }
  size_t size() const { return subs_.size(); }
  bool empty() const { return subs_.empty(); }
  void clear() { subs_.clear(); }
  void append(BiDiIterator first, BiDiIterator second) {
    subs_.push_back({first, second});
  }
  const_reference operator[](size_t i) { return subs_[i]; }
  const_reference operator[](size_t i) const { return subs_[i]; }
  const_reference prefix() { return prefix_; }
  const_reference suffix() { return suffix_; }

  void set_prefix(BiDiIterator first, BiDiIterator second) { // TODO friend?
    prefix_ = {first, second};
  }
  void set_suffix(BiDiIterator first, BiDiIterator second) {
    suffix_ = {first, second};
  }
  std::string str() const { return subs_[0]; }

  difference_type position(size_t i = 0) const {
    if (i >= subs_.size()) {
      throw std::out_of_range("Index out of range in match_results::position");
    }
    return std::distance(prefix_.second, subs_[i].first);
  }

  difference_type length(size_t i = 0) const {
    if (i >= subs_.size()) {
      throw std::out_of_range("Index out of range in match_results::length");
    }
    return std::distance(subs_[i].first, subs_[i].second);
  }

private:
  vector_type subs_;
  value_type prefix_;
  value_type suffix_;
};

typedef match_results<std::string::const_iterator> smatch;

bool regex_search(std::string::const_iterator first,
                  std::string::const_iterator last,
                  match_results<std::string::const_iterator> &m,
                  const regex &e);

// Best effort to prevent unsafe attempts to get match_results from a temporary
// string.
template <class ST, class SA, class charT>
bool regex_search(const std::basic_string<charT, ST, SA> &s,
                  match_results<std::string::const_iterator> &m,
                  const regex &e) {
  regmatch_t matches[REGEX_MAX_SUBEXPRESSIONS + 1];
  for (size_t i = 0; i < sizeof(matches) / sizeof(matches[0]); ++i) {
    matches[i].rm_so = -1;
    matches[i].rm_eo = -1;
  }
  int ret = regexec(&e.regex_, s.c_str(), sizeof(matches) / sizeof(matches[0]),
                    static_cast<regmatch_t *>(&matches[0]), 0);
  if (-1 != matches[REGEX_MAX_SUBEXPRESSIONS].rm_so) {
    throw regex_error("Max number of subexpressions is reached");
  }
  m.clear();
  for (size_t i = 0;
       i < sizeof(matches) / sizeof(matches[0]) && -1 != matches[i].rm_so;
       ++i) {
    m.append(s.begin() + matches[i].rm_so, s.begin() + matches[i].rm_eo);
  }
  if (0 == ret) {
    m.set_prefix(s.begin(), m[0].first);
    m.set_suffix(m[0].second, s.end());
    return true;
  }
  return false;
}

bool regex_match(const std::string &s, const regex &e);

// Best effort to prevent unsafe attempts to get match_results from a temporary
// string.
template <class ST, class SA, class charT>
bool regex_match(const std::basic_string<charT, ST, SA> &s, smatch &m,
                 const regex &e) {
  bool ret = regex_search(s, m, e);
  if (ret && m.prefix().first == s.begin() && m.prefix().second == s.begin() &&
      m.suffix().first == s.end() && m.suffix().second == s.end()) {
    return true;
  }
  return false;
}

std::string regex_replace(const std::string &s, const regex &e,
                          const std::string &fmt);

class sregex_iterator {
public:
  sregex_iterator() : search_done_(true) {}
  sregex_iterator(std::string::const_iterator begin,
                  std::string::const_iterator end, const regex &re)
      : begin_(begin), end_(end), re_(re), search_done_(false) {
    ++(*this);
  }

  bool operator==(const sregex_iterator &other) const {
    return search_done_ == other.search_done_ &&
           (search_done_ || (begin_ == other.begin_ && end_ == other.end_));
  }

  bool operator!=(const sregex_iterator &other) const {
    return !(*this == other);
  }

  const smatch &operator*() const { return match_; }
  const smatch *operator->() const { return &match_; }

  sregex_iterator &operator++() {
    if (search_done_) {
      return *this;
    }

    if (regex_search(begin_, end_, match_, re_)) {
      begin_ = match_[0].second;
    } else {
      search_done_ = true;
    }

    return *this;
  }

private:
  std::string::const_iterator begin_;
  std::string::const_iterator end_;
  regex re_;
  smatch match_;
  bool search_done_;
};

#else

using std::match_results;
using std::regex;
using std::regex_error;
using std::regex_match;
using std::regex_replace;
using std::regex_search;
using std::smatch;
using std::sregex_iterator;

#endif

} // namespace regex
} // namespace common
} // namespace mstflint
#endif // MSTFLINT_REGEX_H
