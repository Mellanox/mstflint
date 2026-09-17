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

// MST HTTP server: exposes full MstServerService over HTTPS. Crow needs C++17.
//
// This file is the counterpart of MFT's MstHttpServer.cpp and is meant to be
// readable against it: configure_tls() and run_server() below are its main().
// The "start"/"stop" lifecycle that main() dispatches into has no MFT
// counterpart - MFT's "mst" shell script does that job - and lives in
// MstServerTool.cpp.

#include "mst_server/service/MstHttpRoutes.h"
#include "mst_server/service/MstServerTool.h"
#include "mst_server/service/MstServerHttpUtil.h"
#include "mst_server/service/MstServerServiceImpl.h"
#include "mst_server/service/MstServerTls.h"

#include <openssl/crypto.h>

#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <string>

namespace
{

// Builds the server's TLS context from its on-disk identity. Kept apart from
// crow's ssl_file() helper so the verify mode and the accepted protocol
// versions are stated here rather than inherited: the server asks for no client
// certificate (clients authenticate with the passphrase) and refuses everything
// below TLS 1.2.
bool configure_tls(mstserver::http::MstApp& app, const mstserver::tls::Identity& identity, std::string* error)
{
    try
    {
        asio::ssl::context ctx(asio::ssl::context::tls_server);
        ctx.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::no_sslv2 |
                        asio::ssl::context::no_sslv3 | asio::ssl::context::no_tlsv1 | asio::ssl::context::no_tlsv1_1);
        ctx.set_verify_mode(asio::ssl::verify_none);
        ctx.use_certificate_file(identity.cert_path, asio::ssl::context::pem);
        ctx.use_private_key_file(identity.key_path, asio::ssl::context::pem);
        app.ssl(std::move(ctx));
    }
    catch (const std::exception& e)
    {
        *error = e.what();
        return false;
    }
    return true;
}

} // namespace

namespace mstserver
{
namespace tool
{

// Test hook only, matching MST_KNOWN_HOSTS on the client side; there is no
// command-line way to move the identity, and no way to turn TLS off.
std::string tls_dir()
{
    const char* env = std::getenv("MST_SERVER_TLS_DIR");

    return (env != nullptr && *env != '\0') ? env : mstserver::tls::DEFAULT_IDENTITY_DIR;
}

int run_server(int port, std::string& passphrase, int ready_fd)
{
    mstserver::http::MstApp app;
    mstserver::http::BearerAuth& auth = app.get_middleware<mstserver::http::BearerAuth>();
    auth.required = true;

    // Derived once here and kept only as a salted verifier; the plaintext is
    // scrubbed so it does not outlive this scope in freed heap.
    if (!auth.SetPassphrase(passphrase))
    {
        std::cerr << "-E- cannot derive the passphrase verifier" << std::endl;
        report_ready(ready_fd, 1);
        return 1;
    }
    OPENSSL_cleanse(&passphrase[0], passphrase.size());

    // TLS is unconditional. The server refuses to start rather than serve
    // plaintext, because a client that expects TLS would otherwise be talking to
    // a server that cannot prove who it is and would have no way to tell.
    {
        mstserver::tls::Identity identity;
        std::string error;

        if (!mstserver::tls::ensure_identity(tls_dir(), &identity, &error))
        {
            std::cerr << "-E- cannot prepare the server TLS identity: " << error << std::endl;
            report_ready(ready_fd, 1);
            return 1;
        }
        if (!configure_tls(app, identity, &error))
        {
            std::cerr << "-E- cannot configure TLS: " << error << std::endl;
            report_ready(ready_fd, 1);
            return 1;
        }
    }

    MstServerServiceImpl service;

    // Tune the server for low-latency, high-throughput register-access workloads:
    //   * Crow keeps HTTP/1.1 connections alive by default; a long connection
    //     timeout keeps clients on a single TCP connection across an entire
    //     flint/mlxconfig invocation.
    app.timeout(60);

    mstserver::http::register_routes(app, service);

    app.loglevel(crow::LogLevel::Warning);
    app.port(static_cast<uint16_t>(port)).multithreaded();

    std::future<void> serving;
    try
    {
        serving = app.run_async();
    }
    catch (const std::exception& e)
    {
        std::cerr << "-E- failed to start server: " << e.what() << std::endl;
        report_ready(ready_fd, 1);
        return 1;
    }

    // Crow signals cv_started_ once the acceptor is bound and listening.
    if (app.wait_for_server_start(std::chrono::milliseconds(5000)) != std::cv_status::no_timeout)
    {
        std::cerr << "-E- server did not come up within 5s (port " << port << " in use?)" << std::endl;
        report_ready(ready_fd, 1);
        return 1;
    }
    report_ready(ready_fd, 0);

    // Crow's default signal set is {SIGINT, SIGTERM}, so "mstserver stop" (which
    // sends SIGTERM) unwinds this cleanly and ~MstServerServiceImpl() mcloses
    // every device it opened.
    try
    {
        serving.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "-E- server stopped with an error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

} // namespace tool
} // namespace mstserver

int main(int argc, char* argv[])
{
    int port = MSTSERVER_DEFAULT_PORT;
    std::string passphrase;
    std::string verb;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if ((arg == "-h") || (arg == "--help"))
        {
            mstserver::tool::usage();
            return 0;
        }
        else if ((arg == "-v") || (arg == "--version"))
        {
            std::cout << "mstserver " << MSTSERVER_VERSION << std::endl;
            return 0;
        }
        else if ((arg == "-p") && (i + 1 < argc))
        {
            char* end = NULL;
            long value = strtol(argv[++i], &end, 10);

            if (!end || *end || (value <= 0) || (value > 65535))
            {
                std::cerr << "-E- invalid port: " << argv[i] << std::endl;
                return 1;
            }
            port = static_cast<int>(value);
        }
        else if ((arg == "-s") && (i + 1 < argc))
        {
            passphrase = argv[++i];
        }
        else if (verb.empty() && !arg.empty() && (arg[0] != '-'))
        {
            verb = arg;
        }
        else
        {
            std::cerr << "-E- unknown argument: " << arg << std::endl;
            mstserver::tool::usage();
            return 1;
        }
    }

    if (verb == "start")
    {
        return mstserver::tool::cmd_start(port, passphrase);
    }
    if (verb == "stop")
    {
        return mstserver::tool::cmd_stop(port);
    }
    if (verb.empty())
    {
        std::cerr << "-E- no command given" << std::endl;
    }
    else
    {
        std::cerr << "-E- unknown command: " << verb << std::endl;
    }
    mstserver::tool::usage();
    return 1;
}
