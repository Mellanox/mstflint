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

// The mstserver command-line tool: "start" and "stop".
//
// This half has no counterpart in MFT. There, the http server is a plain
// foreground process and the lifecycle - backgrounding it, finding it again,
// stopping it - lives in the "mst" shell script. mstflint ships no such script,
// so mstserver is its own tool and does that job itself. Keeping it in its own
// file leaves MstHttpServer.cpp as the part that mirrors MFT's file of the same
// name, which is what
// a later rebase from MFT has to be read against.

#ifndef MST_SERVER_TOOL_H
#define MST_SERVER_TOOL_H

#include <string>
#include <vector>

#include "cmdparser/cmdparser.h"

#define MSTSERVER_VERSION "2.0"
#define MSTSERVER_DEFAULT_PORT 8080

namespace mstserver
{
namespace tool
{

// Defined in MstHttpServer.cpp, which owns the serving half. Declared here
// because cmd_start() is what calls it, in the detached grandchild.
//
// `ready_fd`, when >= 0, is the write end of a pipe the parent is blocked on:
// one byte, 0 for listening and 1 for failed, so "mstserver start" exits
// non-zero when the server did not actually come up rather than merely fork.
// `passphrase` is scrubbed before the first request is served.
int run_server(int port, std::string& passphrase, int ready_fd);

// Reports the outcome of the bind on `ready_fd` and closes it; a no-op when it
// is negative. Called from run_server(), which is the only place that knows
// whether the acceptor came up.
void report_ready(int ready_fd, char status);

// Where the server's TLS identity lives; also defined in MstHttpServer.cpp,
// since cmd_start() prepares the identity before detaching so that a key which
// cannot be created is reported on the operator's terminal and the fingerprint
// is printed where it can be read.
std::string tls_dir();

int cmd_start(int port, std::string passphrase);
int cmd_stop(int port);

void usage();

// The command line: "start" and "stop", each with the options that apply to it.
// The verb is positional and leads the command line, so it is taken off argv
// before CommandLineParser - which parses options only - ever sees it.
class MstServerTool : public CommandLineRequester
{
public:
    MstServerTool();

    void InitCmdParser();
    ParseStatus HandleOption(std::string name, std::string value) override;

    // Parses argv and runs the command it names; returns the process exit code.
    int Run(int argc, char** argv);

    void PrintUsage();

private:
    enum class Command
    {
        None,
        Start,
        Stop
    };

    // Moves the leading verb from argv into _verb and copies argv[0] and every
    // remaining element into optionArgv, which is what the parser is handed.
    void ParseAndFindCommand(int argc, char** argv, std::vector<char*>& optionArgv);
    ParseStatus ParseCommandLine(int argc, char** argv);

    CommandLineParser _cmdParser;
    Command _command;
    std::string _verb;
    int _port;
    std::string _passphrase;
};

} // namespace tool
} // namespace mstserver

#endif // MST_SERVER_TOOL_H
