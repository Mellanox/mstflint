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

#ifndef MSTFLINT_FILESYSTEM_H
#define MSTFLINT_FILESYSTEM_H

#include <memory>
#include <string>

#include <dirent.h>

namespace mstflint {
namespace common {
namespace filesystem {

class path {
public:
  path();
  ~path() = default;
  path(const path &);
  explicit path(std::string &);
  explicit path(const std::string &);

  path &operator=(const path &) = default;

  path parent_path() const;
  path extension() const;
  bool is_relative() const;
  path filename() const;
  const std::string &string() const;

  friend bool operator==(const path &, const path &);
  friend bool operator==(const path &, const std::string &);
  friend bool operator==(const std::string &, const path &);
  friend bool operator!=(const path &, const path &);
  friend bool operator!=(const path &, const std::string &);
  friend bool operator!=(const std::string &, const path &);

public:
  static const char SEPARATOR;

private:
  void init();

private:
  std::string pathname_;
  bool is_relative_;
  std::string filename_;
  std::string parent_pathname_;
  std::string extension_;
  std::string stripped_pathname_;
};

// to be expanded on demand...
enum file_type {
  FILETYPE_ERROR,
  // FILETYPE_NOT_FOUND,
  FILETYPE_REGULAR,
  // FILETYPE_DIRECTORY,
  // FILETYPE_SYMLINK,
  // FILETYPE_BLOCK,
  // FILETYPE_CHARACTER,
  // FILETYPE_FIFO,
  // FILETYPE_SOCKET,
  FILETYPE_UNKNOWN,
};

class file_status { // TODO unit tests
public:
  file_status();
  ~file_status() = default;
  file_status(const file_status &) = default;
  explicit file_status(const path &);

  file_status &operator=(const file_status &) = default;

  friend bool is_regular_file(file_status);

private:
  static file_type retrieve_file_type(const char *path);

private:
  file_type type_;
};

class directory_entry {
public:
  directory_entry();
  ~directory_entry() = default;
  directory_entry(directory_entry const &) = default;
  explicit directory_entry(const path &);

  directory_entry &operator=(directory_entry const &) = default;

  const file_status status() const;
  const mstflint::common::filesystem::path &path() const;

private:
  mstflint::common::filesystem::path path_;
  file_status status_;
};

class directory_stream {
public:
  directory_stream(const mstflint::common::filesystem::path &);
  ~directory_stream();
  bool is_open();
  struct dirent *read();

private:
  DIR *stream;
};

class directory_iterator {
public:
  directory_iterator();
  ~directory_iterator() = default;
  directory_iterator(directory_iterator const &);
  explicit directory_iterator(const path &);

  directory_iterator &operator=(directory_iterator const &) = default;
  directory_iterator &operator++();
  directory_entry *operator->();
  directory_entry &operator*();

  using iterator_category = std::forward_iterator_tag;
  using value_type = directory_entry;
  using pointer = directory_entry *;
  using reference = directory_entry &;
  using difference_type = long int;

  friend bool operator!=(const directory_iterator &,
                         const directory_iterator &);

private:
  std::string dirname_;
  directory_entry directory_entry_;
  std::shared_ptr<directory_stream> dr;
  struct dirent *de; // TODO doesn't follow single-responsibility principle
};

const directory_iterator &begin(const directory_iterator &);
const directory_iterator &cbegin(const directory_iterator &);
directory_iterator end(const directory_iterator &);
directory_iterator cend(const directory_iterator &);

bool exists(const path &p);

bool is_directory(const path &p);
bool is_regular_file(const path &p);

bool is_regular_file(file_status f);

} // namespace filesystem
} // namespace common
} // namespace mstflint

#endif // MSTFLINT_FILESYSTEM_H
