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

#include "filesystem.h"

#include <boost/filesystem/operations.hpp>

namespace mstflint
{
namespace common
{
namespace filesystem
{
path::path(std::string& s) : path_(s){};

path::path(const std::string& s) : path_(s){};

path path::parent_path() const
{
    return path(parent_path().string());
}

path path::extension() const
{
    return path(path_.extension().string());
}

bool path::is_relative() const
{
    return path_.is_relative();
}

path path::filename() const
{
    return path(path_.filename().string());
}

const std::string& path::string() const
{
    return path_.string();
}

file_status::file_status(boost::filesystem::file_status file_status) : file_status_(file_status) {}

bool is_regular_file(file_status f) {
    return boost::filesystem::is_regular_file(f.file_status_);
}

directory_entry::directory_entry() {}

directory_entry::directory_entry(const mstflint::common::filesystem::path& p) : directory_entry_(boost::filesystem::path(p.string())) {}

const file_status directory_entry::status() const
{
    return file_status(directory_entry_.status());
}
const mstflint::common::filesystem::path directory_entry::path() const
{
    return mstflint::common::filesystem::path(directory_entry_.path().string());
}

directory_iterator::directory_iterator() : directory_entry_(nullptr) {}

directory_iterator::directory_iterator(const path& p) : iterator_(boost::filesystem::path(p.string())), directory_entry_(nullptr) {}

directory_iterator& directory_iterator::operator++()
{
    ++iterator_;
    return *this;
}

directory_iterator::~directory_iterator() {
    if (directory_entry_)
        delete (directory_entry_);
}

directory_entry* directory_iterator::operator->()
{
    if (directory_entry_)
        delete (directory_entry_);
    directory_entry_ = new directory_entry(path(iterator_->path().string()));
    return directory_entry_;
}

bool operator!=(const directory_iterator& lhs, const directory_iterator& rhs)
{
    return lhs.iterator_ != rhs.iterator_;
}

bool operator==(const path& lhs, const std::string& rhs) {
    return boost::filesystem::path(lhs.string()) == boost::filesystem::path(rhs);
}

bool exists(const path& p)
{
    boost::filesystem::path path(p.string());
    return boost::filesystem::exists(path);
}

bool is_directory(const path& p)
{
    boost::filesystem::path path(p.string());
    return boost::filesystem::is_directory(path);
}

} // namespace filesystem
} // namespace common
} // namespace mstflint
