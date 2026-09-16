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

#include "mst_server/service/MstServerTool.h"
#include "mst_server/service/MstServerHttpUtil.h"
#include "mst_server/service/MstServerTls.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Default runtime state directory; $MSTFLINT_RUN_DIR overrides it.
#define MSTSERVER_RUN_DIR "/var/run/mst"

namespace mstserver
{
namespace tool
{

void report_ready(int ready_fd, char status)
{
    if (ready_fd < 0)
    {
        return;
    }
    ssize_t ignored = write(ready_fd, &status, 1);

    (void)ignored;
    close(ready_fd);
}

/* Runtime state directory. $MSTFLINT_RUN_DIR overrides it, mirroring
 * mstremote's $MSTFLINT_REMOTE_DEV_DIR, so the server can be exercised without
 * write access to /var/run. Never returns NULL. */
static const char* run_dir()
{
    const char* dir = getenv("MSTFLINT_RUN_DIR");

    return (dir && *dir) ? dir : MSTSERVER_RUN_DIR;
}

static std::string pid_path(int port)
{
    return std::string(run_dir()) + "/mstserver." + std::to_string(port) + ".pid";
}

/* /var/run is tmpfs on most distros, so the directory is gone after a reboot.
 * mstremote writes its session tokens here too. */
static int ensure_run_dir()
{
    const char* dir = run_dir();
    struct stat st;

    if (stat(dir, &st) == 0)
    {
        return S_ISDIR(st.st_mode) ? 0 : -1;
    }
    if (mkdir(dir, 0755) != 0)
    {
        std::cerr << "-E- cannot create " << dir << ": " << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}

/* A PID file can outlive its process, and the number may since have been reused
 * by something unrelated - checking the command name as well keeps us from
 * signalling an innocent bystander. */
static bool pid_is_mstserver(pid_t pid)
{
    std::string path = "/proc/" + std::to_string(pid) + "/cmdline";
    std::ifstream f(path.c_str(), std::ios::binary);
    std::string cmdline;

    if (!f)
    {
        return false;
    }
    std::getline(f, cmdline, '\0');
    return cmdline.find("mstserver") != std::string::npos;
}

/* Returns the live PID for `port`, 0 when nothing is running. A stale file is
 * removed as a side effect so the caller can proceed. */
static pid_t running_pid(int port)
{
    std::string path = pid_path(port);
    std::ifstream f(path.c_str());
    long pid = 0;

    if (!f || !(f >> pid) || (pid <= 0))
    {
        return 0;
    }
    f.close();

    if ((kill(static_cast<pid_t>(pid), 0) == 0) && pid_is_mstserver(static_cast<pid_t>(pid)))
    {
        return static_cast<pid_t>(pid);
    }
    unlink(path.c_str());
    return 0;
}

static int write_pid_file(int port)
{
    std::string path = pid_path(port);
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0644);
    std::string text;

    if (fd < 0)
    {
        return -1;
    }
    text = std::to_string(static_cast<long>(getpid())) + "\n";
    ssize_t ignored = write(fd, text.data(), text.size());

    (void)ignored;
    close(fd);
    return 0;
}

/* Crow notifies wait_for_server_start() before the acceptor has actually bound,
 * so a busy port is not reported by that path - the daemon comes up, fails, and
 * exits after the parent has already declared success. Probe the port here
 * instead, with SO_REUSEADDR so the probe mirrors what Crow itself will do
 * (binding over a socket in TIME_WAIT succeeds; binding over a live listener
 * does not). */
static bool port_available(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int reuse = 1;
    bool ok;

    if (fd < 0)
    {
        return true; // cannot tell; let the server try
    }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(static_cast<uint16_t>(port));
    ok = bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == 0;
    close(fd);
    return ok;
}

void usage()
{
    MstServerTool tool;

    tool.PrintUsage();
}

int cmd_start(int port, std::string passphrase)
{
    if (ensure_run_dir())
    {
        return 1;
    }

    pid_t existing = running_pid(port);

    if (existing > 0)
    {
        std::cerr << "-E- mstserver is already running on port " << port << " (pid " << existing << ")" << std::endl;
        return 1;
    }

    if (!port_available(port))
    {
        std::cerr << "-E- port " << port << " is already in use" << std::endl;
        return 1;
    }

    // Authentication is not optional: the server exposes raw register access on
    // 0.0.0.0, so an unauthenticated instance is an open door to every device on
    // the host. With no -s we mint one, matching MFT's "if no passphrase is
    // provided, a random one will be generated". This has to run before
    // detaching, or nobody would ever see it.
    bool generated = passphrase.empty();

    if (generated)
    {
        passphrase = mstserver::http::generate_random_hex(16);
        if (passphrase.empty())
        {
            std::fprintf(stderr, "-E- Cannot draw a passphrase from the system RNG\n");
            return 1;
        }
    }

    // Prepared here rather than only in the daemon so that a key that cannot be
    // created is reported on the operator's terminal, and so the fingerprint
    // clients are asked to confirm is printed where they can read it. It is
    // idempotent: run_server() calls it again and gets the same key back.
    mstserver::tls::Identity identity;
    {
        std::string error;

        if (!mstserver::tls::ensure_identity(tls_dir(), &identity, &error))
        {
            std::cerr << "-E- cannot prepare the server TLS identity: " << error << std::endl;
            return 1;
        }
    }

    int ready[2];

    if (pipe(ready) != 0)
    {
        std::cerr << "-E- pipe: " << strerror(errno) << std::endl;
        return 1;
    }

    pid_t child = fork();

    if (child < 0)
    {
        std::cerr << "-E- fork: " << strerror(errno) << std::endl;
        return 1;
    }
    if (child > 0)
    {
        // Wait for the daemon to report that it is actually listening, so a
        // failure to bind is an error here rather than a server that silently
        // is not there.
        char status = 1;
        ssize_t got;

        close(ready[1]);
        got = read(ready[0], &status, 1);
        close(ready[0]);
        waitpid(child, NULL, 0); // reap the intermediate process

        if ((got != 1) || (status != 0))
        {
            std::cerr << "-E- mstserver failed to start on port " << port << std::endl;
            return 1;
        }
        std::cout << "-I- Passphrase for this session:\n"
                  << "-I-     " << passphrase << "\n"
                  // Printed so an operator can read the identity off the server
                  // and compare it with what the client shows on first
                  // connection - the out-of-band check that makes
                  // trust-on-first-use worth anything.
                  << "-I- Server key fingerprint:\n"
                  << "-I-     " << identity.fingerprint << "\n"
                  << "-I- Register clients with:\n"
                  << "-I-     mstremote add <this-host>:" << port << " -s " << passphrase << "\n"
                  << "-I- mstserver listening on 0.0.0.0:" << port << " over TLS (pid " << running_pid(port) << ")\n"
                  << "-I- Stop it with: mstserver stop -p " << port << std::endl;
        return 0;
    }

    // Intermediate child: detach from the controlling terminal, then fork again
    // so the daemon is not a session leader and can never reacquire one.
    close(ready[0]);
    if (setsid() < 0)
    {
        _exit(1);
    }

    pid_t grandchild = fork();

    if (grandchild < 0)
    {
        _exit(1);
    }
    if (grandchild > 0)
    {
        _exit(0);
    }

    if (chdir("/") != 0)
    {
        _exit(1);
    }
    umask(0);

    int devnull = open("/dev/null", O_RDWR);

    if (devnull >= 0)
    {
        dup2(devnull, STDIN_FILENO);
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        if (devnull > STDERR_FILENO)
        {
            close(devnull);
        }
    }

    if (write_pid_file(port))
    {
        report_ready(ready[1], 1);
        _exit(1);
    }

    int rc = run_server(port, passphrase, ready[1]);

    unlink(pid_path(port).c_str());
    _exit(rc == 0 ? 0 : 1);
}

int cmd_stop(int port)
{
    pid_t pid = running_pid(port);

    if (pid <= 0)
    {
        std::cerr << "-E- no mstserver running on port " << port << std::endl;
        return 1;
    }

    if (kill(pid, SIGTERM) != 0)
    {
        std::cerr << "-E- cannot signal pid " << pid << ": " << strerror(errno) << std::endl;
        return 1;
    }

    // Crow unwinds on SIGTERM; give it a moment before insisting.
    for (int i = 0; i < 50; i++)
    {
        if (kill(pid, 0) != 0)
        {
            unlink(pid_path(port).c_str());
            std::cout << "-I- mstserver on port " << port << " stopped (pid " << pid << ")" << std::endl;
            return 0;
        }
        usleep(100000);
    }

    std::cerr << "-W- pid " << pid << " did not exit after SIGTERM; sending SIGKILL" << std::endl;
    kill(pid, SIGKILL);
    usleep(200000);
    unlink(pid_path(port).c_str());
    return 0;
}

MstServerTool::MstServerTool() :
    CommandLineRequester("mstserver <start|stop>"),
    _cmdParser("mstserver"),
    _command(Command::None),
    _port(MSTSERVER_DEFAULT_PORT)
{
    InitCmdParser();
}

void MstServerTool::InitCmdParser()
{
    AddDescription("Serves this host's devices to remote mstflint tools over HTTPS. Register them on the client "
                   "side with \"mstremote add <host>:<port>\".");

    AddOptions("port", 'p', "<port>", "TCP port to listen on (default " + std::to_string(MSTSERVER_DEFAULT_PORT) + ")");
    AddOptions("passphrase", 's', "<passphrase>", "Session passphrase; one is generated and printed when omitted");
    AddOptions("help", 'h', "", "Show this help and exit");
    AddOptions("version", 'v', "", "Show version and exit");

    // The verbs are taken off argv before the parser runs, so they never reach
    // the generated OPTIONS section; spell them out here rather than lose them.
    AddOptionalSectionData("COMMANDS", "start",
                           "Detach and serve on <port>. The passphrase is printed once, here; a restart "
                           "invalidates every client's session token.");
    AddOptionalSectionData("COMMANDS", "stop", "Stop the server that is serving <port>.");

    AddOptionalSectionData("NOTES", "Starting and stopping require root.");
    AddOptionalSectionData("NOTES",
                           "The server generates a TLS key pair on first start and reuses it. Its fingerprint is "
                           "printed at every start; clients confirm it on their first connection and refuse the "
                           "server if it later changes.");

    _cmdParser.AddRequester(this);
}

ParseStatus MstServerTool::HandleOption(std::string name, std::string value)
{
    if (name == "port")
    {
        char* end = NULL;
        long port = strtol(value.c_str(), &end, 10);

        if (!end || *end || (port <= 0) || (port > 65535))
        {
            std::cerr << "-E- invalid port: " << value << std::endl;
            return PARSE_ERROR;
        }
        _port = static_cast<int>(port);
        return PARSE_OK;
    }
    else if (name == "passphrase")
    {
        _passphrase = value;
        return PARSE_OK;
    }
    else if (name == "help")
    {
        PrintUsage();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == "version")
    {
        std::cout << "mstserver " << MSTSERVER_VERSION << std::endl;
        return PARSE_OK_WITH_EXIT;
    }
    return PARSE_ERROR;
}

void MstServerTool::ParseAndFindCommand(int argc, char** argv, std::vector<char*>& optionArgv)
{
    int first = 1;

    if ((argc > 1) && (argv[1][0] != '\0') && (argv[1][0] != '-'))
    {
        _verb = argv[1];
        first = 2;
    }

    optionArgv.push_back(argv[0]);
    for (int i = first; i < argc; i++)
    {
        optionArgv.push_back(argv[i]);
    }
}

ParseStatus MstServerTool::ParseCommandLine(int argc, char** argv)
{
    std::vector<char*> optionArgv;

    ParseAndFindCommand(argc, argv, optionArgv);

    ParseStatus status = _cmdParser.ParseOptions(static_cast<int>(optionArgv.size()), optionArgv.data());

    if (status == PARSE_OK_WITH_EXIT)
    {
        return status;
    }
    if (status != PARSE_OK)
    {
        // Whatever the parser could not place is an argument the tool does not
        // take - a second verb, or a verb that did not lead the command line.
        std::string leftover = _cmdParser.GetUnknownOptions();

        while (!leftover.empty() && (leftover[leftover.size() - 1] == ' '))
        {
            leftover.erase(leftover.size() - 1);
        }
        if (!leftover.empty())
        {
            std::cerr << "-E- unknown argument: " << leftover << std::endl;
            PrintUsage();
        }
        else if (status == PARSE_ERROR_SHOW_USAGE)
        {
            PrintUsage();
        }
        // Anything else is a value HandleOption() rejected, and it has already
        // said which one; do not bury that under the usage text.
        return PARSE_ERROR;
    }

    if (_verb.empty())
    {
        std::cerr << "-E- no command given" << std::endl;
        PrintUsage();
        return PARSE_ERROR;
    }
    if (_verb == "start")
    {
        _command = Command::Start;
    }
    else if (_verb == "stop")
    {
        _command = Command::Stop;
    }
    else
    {
        std::cerr << "-E- unknown command: " << _verb << std::endl;
        PrintUsage();
        return PARSE_ERROR;
    }
    return PARSE_OK;
}

void MstServerTool::PrintUsage()
{
    std::cout << _cmdParser.GetUsage() << std::endl;
}

int MstServerTool::Run(int argc, char** argv)
{
    ParseStatus status = ParseCommandLine(argc, argv);

    if (status == PARSE_OK_WITH_EXIT)
    {
        return 0;
    }
    if (status != PARSE_OK)
    {
        return 1;
    }

    if (_command == Command::Start)
    {
        return cmd_start(_port, _passphrase);
    }
    return cmd_stop(_port);
}

} // namespace tool
} // namespace mstserver
