/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include "mst_server/client/MstKnownHosts.h"
#include "common/tools_algorithm.h"

#include <sys/stat.h>
#include <sys/types.h>

#include <cctype>
#include <cerrno>
#include <filesystem>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

namespace mstserver
{

namespace algo = mstflint::common::algorithm;

namespace
{

const char* const KNOWN_HOSTS_ENV = "MST_KNOWN_HOSTS";

} // namespace

MstKnownHosts::MstKnownHosts(const std::string& path) : path_(path.empty() ? DefaultPath() : path) {}

std::string MstKnownHosts::DefaultPath()
{
    const char* override_path = std::getenv(KNOWN_HOSTS_ENV);
    if (override_path != nullptr && *override_path != '\0')
    {
        return override_path;
    }
#ifdef __WIN__
    // %ProgramData% is administrator-write-only by default, which is what keeps
    // an unprivileged user from pinning a server of their choosing.
    const char* program_data = std::getenv("ProgramData");
    const std::string root = (program_data != nullptr && *program_data != '\0') ? program_data : "C:\\ProgramData";
    return root + "\\mstflint\\mst_known_hosts";
#else
    // Root-only, beside the server's own identity directory. mstflint keeps its
    // own /var/lib rather than sharing MFT's: the two packages are installed
    // side by side often enough that one owning the other's state would make
    // removing either take the survivor's pins with it.
    return "/var/lib/mstflint/mst_known_hosts";
#endif
}

std::string MstKnownHosts::HostKey(const std::string& host, int port)
{
    std::ostringstream key;
    key << algo::to_lower_copy(host) << ":" << port;
    return key.str();
}

MstKnownHosts::Status
  MstKnownHosts::Lookup(const std::string& host, int port, const std::string& fingerprint, std::string* stored) const
{
    std::ifstream file(path_.c_str());
    if (!file.is_open())
    {
        return UNKNOWN;
    }

    const std::string wanted = HostKey(host, port);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream fields(line);
        std::string entry_host;
        std::string entry_fingerprint;
        if (!(fields >> entry_host >> entry_fingerprint) || entry_host.empty() || entry_host[0] == '#')
        {
            continue;
        }
        if (algo::to_lower_copy(entry_host) != wanted)
        {
            continue;
        }
        if (entry_fingerprint == fingerprint)
        {
            return MATCH;
        }
        if (stored != nullptr)
        {
            *stored = entry_fingerprint;
        }
        return MISMATCH;
    }
    return UNKNOWN;
}

bool MstKnownHosts::Add(const std::string& host, int port, const std::string& fingerprint, std::string* error)
{
    if (fingerprint.empty())
    {
        if (error != nullptr)
        {
            *error = "refusing to record an empty fingerprint";
        }
        return false;
    }

    const std::string dir = std::filesystem::path(path_).parent_path().string();
    // Owner-only: the store records which servers the user has vouched for, and
    // another account must not be able to add entries to it. A permissions()
    // failure is not fatal - Windows has no POSIX mode to apply.
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    std::error_code perm_ec;
    std::filesystem::permissions(dir, std::filesystem::perms::owner_all, std::filesystem::perm_options::replace,
                                 perm_ec);
    if (!std::filesystem::is_directory(dir))
    {
        if (error != nullptr)
        {
            *error = "cannot create " + dir + ": " + ec.message();
        }
        return false;
    }

    std::ofstream file(path_.c_str(), std::ios::app);
    if (!file.is_open())
    {
        if (error != nullptr)
        {
            *error = "cannot open " + path_ + ": " + std::strerror(errno);
        }
        return false;
    }
    file << HostKey(host, port) << " " << fingerprint << "\n";
    file.close();
    if (file.fail())
    {
        if (error != nullptr)
        {
            *error = "cannot write " + path_;
        }
        return false;
    }

#ifndef __WIN__
    chmod(path_.c_str(), S_IRUSR | S_IWUSR);
#endif
    return true;
}

} // namespace mstserver
