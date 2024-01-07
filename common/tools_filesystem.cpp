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

#include "tools_filesystem.h"

#include <cassert>

#include <dirent.h>
#include <sys/stat.h>

namespace mstflint {
namespace common {
namespace filesystem {

/******************** path ********************/
path::path() : is_relative_(false) { init(); }

path::path(const path &p) : pathname_(p.string()), is_relative_(false) {
  init();
}

path::path(std::string &s) : pathname_(s), is_relative_(false) { init(); }

path::path(const std::string &s) : pathname_(s), is_relative_(false) { init(); }

path path::parent_path() const { return path(parent_pathname_); }

path path::extension() const { return path(extension_); }

bool path::is_relative() const { return is_relative_; }

path path::filename() const { return path(filename_); }

const std::string &path::string() const { return pathname_; }

// Precondition: pathname_ is set
void path::init() {
  if (pathname_.empty()) {
    return;
  }
  is_relative_ = (SEPARATOR != pathname_[0]);
  std::size_t last_separator_pos = pathname_.find_last_of(SEPARATOR);
  if (std::string::npos == last_separator_pos) {
    filename_ = pathname_;
    parent_pathname_.clear();
  } else {
    std::size_t last_non_separator_before_last_separator_pos =
        pathname_.find_last_not_of(SEPARATOR, last_separator_pos);
    filename_ = pathname_.substr(last_separator_pos + 1);
    parent_pathname_ =
        pathname_.substr(0, last_non_separator_before_last_separator_pos + 1);
  }
  std::size_t extension_pos = filename_.find_last_of('.');
  if (std::string::npos != extension_pos) {
    extension_ = filename_.substr(extension_pos);
  }
  stripped_pathname_.reserve(pathname_.size());
  char prev = 0;
  for (char curr : pathname_) {
    if (SEPARATOR == curr) {
      if (SEPARATOR != prev) {
        stripped_pathname_.append(1, SEPARATOR);
      }
    } else {
      stripped_pathname_.append(1, curr);
    }
    prev = curr;
  }
}

const char path::SEPARATOR = '/';

/******************** file_status ********************/
file_status::file_status() : type_(file_type::FILETYPE_UNKNOWN) {}

file_status::file_status(const path &p)
    : type_(retrieve_file_type(p.string().c_str())) {}

file_type file_status::retrieve_file_type(const char *path) {
  assert(nullptr != path);
  struct stat s;
  if (0 != stat(path, &s)) {
    return file_type::FILETYPE_ERROR; // TODO parse errno
  }
  // to be expanded on demand...
  if (S_ISREG(s.st_mode)) {
    return file_type::FILETYPE_REGULAR;
  }
  return file_type::FILETYPE_UNKNOWN;
}

/******************** directory_entry ********************/
directory_entry::directory_entry() {}

directory_entry::directory_entry(const mstflint::common::filesystem::path &p)
    : path_(p), status_(p) {}

const file_status directory_entry::status() const { return status_; }

const mstflint::common::filesystem::path &directory_entry::path() const {
  return path_;
}

/******************** directory_stream ********************/
directory_stream::directory_stream(const mstflint::common::filesystem::path &p)
    : stream(opendir(p.string().c_str())) {}
directory_stream::~directory_stream() {
  if (nullptr != stream) {
    closedir(stream);
  }
}
bool directory_stream::is_open() { return (nullptr != stream); }
struct dirent *directory_stream::read() {
  return readdir(stream);
}

/******************** directory_iterator ********************/
directory_iterator::directory_iterator()
    : dirname_(), directory_entry_(), dr(nullptr), de(nullptr) {}

directory_iterator::directory_iterator(directory_iterator const &other) {
  dirname_ = other.dirname_;
  directory_entry_ = other.directory_entry_;
  dr = other.dr;
  de = other.de;
}

directory_iterator::directory_iterator(const path &p)
    : dirname_(p.string()), directory_entry_(), dr(new directory_stream(p)),
      de(nullptr) {
  if (!dirname_.empty() && path::SEPARATOR != dirname_.back()) {
    dirname_.append(1, path::SEPARATOR);
  }
  if (!dr->is_open())
    return;
  while (nullptr != (de = dr->read())) {
    if (('.' == de->d_name[0]) &&
        (('\0' == de->d_name[1]) ||
         ('.' == de->d_name[1] && '\0' == de->d_name[2])))
      continue;
    break;
  }
  if (nullptr != de) {
    directory_entry_ = directory_entry(path(dirname_ + de->d_name));
  }
}

directory_iterator &directory_iterator::operator++() {
  assert(dr->is_open());
  // struct dirent *de; TODO fixme
  while (nullptr != (de = dr->read())) {
    if (('.' == de->d_name[0]) &&
        (('\0' == de->d_name[1]) ||
         ('.' == de->d_name[1] && '\0' == de->d_name[2])))
      continue;
    break;
  }
  if (nullptr != de) {
    directory_entry_ = directory_entry(path(dirname_ + de->d_name));
  }
  return *this;
}

directory_entry *directory_iterator::operator->() { return &directory_entry_; }

directory_entry &directory_iterator::operator*() { return directory_entry_; }

/******************** friend functions ********************/
bool operator==(const path &lhs, const path &rhs) {
  return lhs.stripped_pathname_ == rhs.stripped_pathname_;
}

bool operator==(const path &lhs, const std::string &rhs) {
  return lhs.stripped_pathname_ == path(rhs).stripped_pathname_;
}

bool operator==(const std::string &lhs, const path &rhs) {
  return path(lhs).stripped_pathname_ == rhs.stripped_pathname_;
}

bool operator!=(const path &lhs, const path &rhs) { return !(lhs == rhs); }

bool operator!=(const path &lhs, const std::string &rhs) {
  return !(lhs == rhs);
}

bool operator!=(const std::string &lhs, const path &rhs) {
  return !(lhs == rhs);
}

bool is_regular_file(file_status f) {
  return file_type::FILETYPE_REGULAR == f.type_;
}

bool operator!=(const directory_iterator &lhs, const directory_iterator &rhs) {
  return lhs.de != rhs.de;
}

/******************** other non-member functions ********************/
const directory_iterator &begin(const directory_iterator &it) { return it; }

const directory_iterator &cbegin(const directory_iterator &it) { return it; }

directory_iterator end(const directory_iterator &) {
  return directory_iterator();
}

directory_iterator cend(const directory_iterator &) {
  return directory_iterator();
}

bool exists(const path &p) {
  struct stat s;
  return (0 == stat(p.string().c_str(), &s));
}

bool is_directory(const path &p) {
  struct stat s;
  if (0 != stat(p.string().c_str(), &s)) {
    return false;
  }
  if (S_ISDIR(s.st_mode)) {
    return true;
  } else {
    return false;
  }
}

bool is_regular_file(const path &p) {
  struct stat s;
  if (0 != stat(p.string().c_str(), &s)) {
    return false;
  }
  if (S_ISREG(s.st_mode)) {
    return true;
  } else {
    return false;
  }
}

} // namespace filesystem
} // namespace common
} // namespace mstflint
