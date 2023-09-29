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

#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace mstflint
{
namespace common
{
namespace filesystem
{
class path
{
public:
    path(std::string& s);
    path(const std::string& s);
    path parent_path() const;
    path extension() const;
    bool is_relative() const;
    path filename() const;
    const std::string& string() const;
    friend bool operator==(const path& lhs, const std::string& rhs);
private:
    boost::filesystem::path path_;
};

class file_status
{
public:
    file_status(boost::filesystem::file_status file_status);
    friend bool is_regular_file(file_status f);
private:
    boost::filesystem::file_status file_status_;
};

class directory_entry
{
public:
    directory_entry();
    explicit directory_entry(const path& p);
    const file_status status() const;
    // FIXME const mstflint::common::filesystem::path& path();
    const mstflint::common::filesystem::path path() const;
private:
    boost::filesystem::directory_entry directory_entry_;
};

class directory_iterator
{
public:
    directory_iterator();
    ~directory_iterator();
    explicit directory_iterator(const path& p);
    directory_iterator(directory_iterator const& that) = default;
    directory_iterator& operator=(directory_iterator const& that) = default;
    directory_iterator& operator++();
    directory_entry* operator->();
    friend bool operator!=(const directory_iterator&, const directory_iterator&);

private:
    boost::filesystem::directory_iterator iterator_;
    directory_entry* directory_entry_;
};

bool exists(const path& p);
bool is_directory(const path& p);
bool is_regular_file(file_status f);

} // namespace filesystem
} // namespace common
} // namespace mstflint

#endif // MSTFLINT_FILESYSTEM_H
