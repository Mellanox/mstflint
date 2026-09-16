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

#ifndef MST_KNOWN_HOSTS_H
#define MST_KNOWN_HOSTS_H

#include <string>

namespace mstserver
{

// The client's record of which MST servers the user has already vouched for,
// modelled on SSH's known_hosts: one "<host>:<port> <fingerprint>" line per
// server, "#" comments and blank lines ignored.
//
// Without this file every connection would have to trust whatever key answers
// the port, which is exactly the attack the trust prompt exists to stop.
class MstKnownHosts
{
public:
    enum Status
    {
        UNKNOWN,  // no entry: first contact, the user has to decide
        MATCH,    // the server presented the key we recorded
        MISMATCH, // a different key answers a host we have already trusted
    };

    explicit MstKnownHosts(const std::string& path);

    // $MST_KNOWN_HOSTS when set, so tests and side-by-side setups do not have
    // to touch the system store; the root-only system store otherwise.
    static std::string DefaultPath();

    // `stored` receives the recorded fingerprint on MISMATCH so the caller can
    // show the user both keys.
    Status Lookup(const std::string& host, int port, const std::string& fingerprint, std::string* stored) const;

    // Appends an entry. Callers must have established that the host is UNKNOWN:
    // this neither replaces nor removes a conflicting entry, because silently
    // re-pinning a changed key would defeat the mismatch check.
    bool Add(const std::string& host, int port, const std::string& fingerprint, std::string* error);

    const std::string& Path() const { return path_; }

    // "host:port", the key both Lookup() and Add() store entries under.
    static std::string HostKey(const std::string& host, int port);

private:
    std::string path_;
};

} // namespace mstserver

#endif // MST_KNOWN_HOSTS_H
