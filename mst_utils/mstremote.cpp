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

/*
 * mstremote - register devices served by a remote mstmthttpserver so the
 * local tools can reach them, the mstflint counterpart of MFT's
 * "mst remote add".
 *
 * A remote device is registered by creating an empty marker file whose *name*
 * is the device name, "<host>:<port>,<device>" with '@' standing for '/', in
 * the directory mtcr scans (/dev/mstflint, or $MSTFLINT_REMOTE_DEV_DIR). Nothing
 * else is stored: mopen() parses that name straight back into host, port and
 * remote device path.
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "cmdparser/cmdparser.h"
/* Both headers declare their own extern "C" block. */
#include "mst_server/client/mst_http_client_c_api.h"
#include "mtcr_remote.h"

using namespace std;

/* Must match MSTSERVER_DEFAULT_PORT, and matches MFT's mst server. */
static const int DEFAULT_PORT = 23108;
static const size_t MAX_PASSPHRASE = 256;
static const size_t MAX_NAME = 1024;

/* Where mtcr_remote.c looks for a session token. */
static const char* const TOKEN_DIR = "/var/run/mst";

/* Must match MstKnownHosts::DefaultPath(); only the help text reads it here. */
static const char* const MST_KNOWN_HOSTS_DEFAULT = "/var/lib/mstflint/mst_known_hosts";

static const char* const PROG = "mstremote";

static const string ADD_COMMAND = "add";
static const string DEL_COMMAND = "del";

static const string PASSPHRASE_FLAG = "passphrase";
static const char PASSPHRASE_FLAG_SHORT = 's';
static const string TRUST_FLAG = "yes";
static const char TRUST_FLAG_SHORT = 'y';
static const string ALL_FLAG = "all";
static const string HELP_FLAG = "help";
static const char HELP_FLAG_SHORT = 'h';

/* The handle is a C resource, and every failure below returns early. */
using ClientHandle = unique_ptr<struct mst_http_client, void (*)(mst_http_client_t)>;

class MstRemote : public CommandLineRequester
{
public:
    MstRemote();
    ~MstRemote() {}

    ParseStatus ParseCommandLine(int argc, char** argv);
    int Run();

    ParseStatus HandleOption(string name, string value) override;

private:
    enum MstRemoteCmd
    {
        CmdUnknown,
        CmdAdd,
        CmdDel
    };

    void InitCmdParser();
    void PrintUsage();
    void ParseAndFindCommand(int argc, char** argv);
    bool SplitHostPort(const string& arg);
    bool PromptPassphrase();
    string TokenPath();
    void StoreToken(const string& token);
    int RunAdd();
    int RunDel();

    CommandLineParser _cmdParser;
    MstRemoteCmd _command;
    string _verb;
    string _target;
    vector<char*> _optionArgv;
    string _host;
    int _port;
    string _passphrase;
    bool _passphraseGiven;
    bool _registerAll;
    bool _autoTrust;
};

/* Where the client records the server keys it has been told to trust. Only used
 * for the help text; MstKnownHosts owns the real lookup. */
static string MstKnownHostsPath()
{
    const char* env = getenv("MST_KNOWN_HOSTS");

    return (env && *env) ? env : MST_KNOWN_HOSTS_DEFAULT;
}

/* Runtime state directory, shared with mstserver. $MSTFLINT_RUN_DIR overrides
 * it so tokens can be exercised without write access to /var/run. */
static string RunDir()
{
    const char* dir = getenv("MSTFLINT_RUN_DIR");

    return (dir && *dir) ? dir : TOKEN_DIR;
}

/* Lets a package or a CI environment opt its automated callers into -y without
 * editing every call site. Off unless asked for: unlike MFT, which trusts an
 * unrecognised server by default because its callers predate the prompt,
 * mstflint has never shipped remote support and so has none to accommodate. */
static bool AutoTrustFromEnv()
{
    const char* value = getenv("MST_REMOTE_AUTO_TRUST");

    return value && *value && (strcmp(value, "0") != 0);
}

static bool EnsureDir(const string& dir)
{
    struct stat st;

    if (stat(dir.c_str(), &st) == 0)
    {
        return S_ISDIR(st.st_mode);
    }
    if (mkdir(dir.c_str(), 0755) != 0)
    {
        fprintf(stderr, "-E- cannot create %s: %s\n", dir.c_str(), strerror(errno));
        return false;
    }
    return true;
}

/* Build the marker name for one device: "<host>:<port>,<device>" with '/'
 * encoded as '@' so the name stays a single path component. */
static string MarkerName(const string& host, int port, const string& device)
{
    string marker = host + ":" + to_string(port) + ",";

    for (size_t i = 0; i < device.size(); i++)
    {
        marker += (device[i] == '/') ? '@' : device[i];
    }
    return marker;
}

/* The server reports each device under two names - the sysfs config path and
 * the bare BDF - because mtcr keeps both in one dev_info and /devices flattens
 * them. Extract the BDF so the pair collapses to a single key; returns false
 * when the name carries no BDF, in which case the name itself is the key. */
static bool DeviceKey(const string& name, string& key)
{
    unsigned domain, bus, dev, func;

    for (size_t i = 0; i < name.size(); i++)
    {
        if (sscanf(name.c_str() + i, "%x:%x:%x.%x", &domain, &bus, &dev, &func) == 4)
        {
            char buf[64];

            snprintf(buf, sizeof(buf), "%04x:%02x:%02x.%x", domain, bus, dev, func);
            key = buf;
            return true;
        }
    }
    return false;
}

/* Choose one name per physical device, preferring the bare BDF: it is shorter
 * and lets the remote mtcr pick its own access path, whereas the sysfs
 * .../config form pins config-space access. Returns the indices kept. */
static vector<size_t> DedupeDevices(const vector<string>& devices)
{
    vector<size_t> keep;
    string key;
    string other;

    for (size_t i = 0; i < devices.size(); i++)
    {
        size_t dup = keep.size();

        if (!DeviceKey(devices[i], key))
        {
            keep.push_back(i);
            continue;
        }
        for (size_t j = 0; j < keep.size(); j++)
        {
            if (DeviceKey(devices[keep[j]], other) && (key == other))
            {
                dup = j;
                break;
            }
        }
        if (dup == keep.size())
        {
            keep.push_back(i);
        }
        else if ((devices[keep[dup]].find('/') != string::npos) && (devices[i].find('/') == string::npos))
        {
            /* Already kept the path form; the bare BDF is preferred. */
            keep[dup] = i;
        }
    }
    return keep;
}

MstRemote::MstRemote() :
    CommandLineRequester("mstremote OPTIONS"), _cmdParser(PROG), _command(CmdUnknown), _port(DEFAULT_PORT), _passphraseGiven(false), _registerAll(false), _autoTrust(AutoTrustFromEnv())
{
    InitCmdParser();
}

void MstRemote::InitCmdParser()
{
    AddOptions(PASSPHRASE_FLAG, PASSPHRASE_FLAG_SHORT, "<passphrase>", "The server's passphrase; prompted for when omitted");
    AddOptions(TRUST_FLAG, TRUST_FLAG_SHORT, "", "Trust an unrecognized server without asking");
    AddOptions(ALL_FLAG, ' ', "", "Keep every name the server reports, including the sysfs .../config alias of each device");
    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");

    _cmdParser.AddRequester(this);
}

void MstRemote::PrintUsage()
{
    printf("Usage:\n");
    printf("  %s add  <host>[:<port>] [-s <passphrase>] [-y] [--all]\n", PROG);
    printf("        register the server's devices (one entry per device;\n");
    printf("        --all keeps every name the server reports, including the\n");
    printf("        sysfs .../config alias of each device)\n");
    printf("  %s del  <host>[:<port>]                     unregister them\n", PROG);
    printf("\n");
    printf("  -s <passphrase>  the server's passphrase; you are prompted when it is\n");
    printf("                   omitted. Passing it here exposes it to every user on\n");
    printf("                   this machine through ps(1).\n");
    printf("  -y               trust an unrecognized server without asking\n");
    printf("\n");
    printf("The first connection to a server shows its key fingerprint and asks you to\n");
    printf("confirm it, the way ssh does for an unknown host. Compare it with the\n");
    printf("fingerprint printed by \"mstserver start\" on that host before answering. The\n");
    printf("answer is remembered in %s, and a later change of the\n", MstKnownHostsPath().c_str());
    printf("server's key aborts the connection. Automated callers can pass -y, or set\n");
    printf("MST_REMOTE_AUTO_TRUST=1.\n");
    printf("\n");
    printf("Default port is %d. Devices are registered under %s\n", DEFAULT_PORT, mtcr_remote_dev_dir());
    printf("(override with MSTFLINT_REMOTE_DEV_DIR); registering usually needs root.\n");
}

ParseStatus MstRemote::HandleOption(string name, string value)
{
    if (name == HELP_FLAG)
    {
        PrintUsage();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == PASSPHRASE_FLAG)
    {
        _passphrase = value;
        _passphraseGiven = true;
        return PARSE_OK;
    }
    else if (name == TRUST_FLAG)
    {
        _autoTrust = true;
        return PARSE_OK;
    }
    else if (name == ALL_FLAG)
    {
        _registerAll = true;
        return PARSE_OK;
    }

    return PARSE_ERROR;
}

/* The verb and the host are positional, and the parser handles options only, so
 * both have to come off argv before it runs. Anything starting with '-' is an
 * option: "mstremote -h" and "mstremote add -h" carry no host. */
/* The verb and the host are positional, but an operator may still write them
 * after a flag ("mstremote add -y myhost"), so scan the whole of argv rather
 * than fixing them at argv[1] and argv[2]. Only -s/--passphrase takes a
 * separate value, so it is the one option whose successor must be skipped. */
void MstRemote::ParseAndFindCommand(int argc, char** argv)
{
    _optionArgv.push_back(argv[0]);
    for (int i = 1; i < argc; i++)
    {
        const string arg = argv[i];

        if (!arg.empty() && (arg[0] == '-'))
        {
            _optionArgv.push_back(argv[i]);
            const bool takes_value = (arg == string("-") + PASSPHRASE_FLAG_SHORT) || (arg == "--" + PASSPHRASE_FLAG);
            if (takes_value && ((i + 1) < argc))
            {
                _optionArgv.push_back(argv[++i]);
            }
            continue;
        }
        if (_verb.empty())
        {
            _verb = arg;
        }
        else if (_target.empty())
        {
            _target = arg;
        }
        else
        {
            /* Surplus positional: hand it to the parser so it reports it. */
            _optionArgv.push_back(argv[i]);
        }
    }
}

ParseStatus MstRemote::ParseCommandLine(int argc, char** argv)
{
    if (argc < 2)
    {
        PrintUsage();
        return PARSE_ERROR;
    }

    ParseAndFindCommand(argc, argv);

    /* Options are answered before the command is judged, so -h prints the help
     * of a mistyped command line instead of its error. */
    ParseStatus rc = _cmdParser.ParseOptions((int)_optionArgv.size(), _optionArgv.data());
    if (rc == PARSE_OK_WITH_EXIT)
    {
        return rc;
    }
    if (rc != PARSE_OK)
    {
        fprintf(stderr, "-E- %s\n", _cmdParser.GetErrDesc());
        PrintUsage();
        return PARSE_ERROR;
    }

    if (_verb == ADD_COMMAND)
    {
        _command = CmdAdd;
    }
    else if (_verb == DEL_COMMAND)
    {
        _command = CmdDel;
    }
    else if (!_verb.empty())
    {
        fprintf(stderr, "-E- unknown command: %s\n", _verb.c_str());
        PrintUsage();
        return PARSE_ERROR;
    }

    if ((_command == CmdUnknown) || _target.empty())
    {
        PrintUsage();
        return PARSE_ERROR;
    }
    if (!SplitHostPort(_target))
    {
        fprintf(stderr, "-E- bad host specification: %s\n", _target.c_str());
        return PARSE_ERROR;
    }

    return PARSE_OK;
}

/* Split "<host>[:<port>]". */
bool MstRemote::SplitHostPort(const string& arg)
{
    size_t colon = arg.rfind(':');
    string host = (colon == string::npos) ? arg : arg.substr(0, colon);

    if (host.empty() || (host.size() >= MAX_NAME))
    {
        return false;
    }
    _host = host;
    _port = DEFAULT_PORT;

    if (colon != string::npos)
    {
        char* end = NULL;
        long p = strtol(arg.c_str() + colon + 1, &end, 10);

        if (!end || *end || (p <= 0) || (p > 65535))
        {
            return false;
        }
        _port = (int)p;
    }
    return true;
}

string MstRemote::TokenPath()
{
    return RunDir() + "/.token." + _host + "_" + to_string(_port);
}

/* Persist the session token where mtcr_remote.c will find it. Best effort: a
 * failure here only means the tools need MSTFLINT_REMOTE_TOKEN instead. */
void MstRemote::StoreToken(const string& token)
{
    string path = TokenPath();
    FILE* f;
    int fd;

    /* /var/run is tmpfs on most distros, so the directory is gone after a
     * reboot even though mstserver created it on its last start. */
    if (!EnsureDir(RunDir()))
    {
        fprintf(stderr, "-W- cannot create %s: %s\n", RunDir().c_str(), strerror(errno));
    }
    fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        /* The token is a bearer credential: naming it here would put it in
         * whatever captured stderr. Point at the override instead. */
        fprintf(stderr, "-W- cannot write %s: %s\n", path.c_str(), strerror(errno));
        fprintf(stderr, "-W- set MSTFLINT_RUN_DIR to a writable directory and re-run\n");
        return;
    }
    f = fdopen(fd, "w");
    if (!f)
    {
        close(fd);
        return;
    }
    fprintf(f, "%s\n", token.c_str());
    fclose(f);
    printf("Session token stored in %s\n", path.c_str());
}

/* Read a passphrase without echoing it. Prompting is preferred over -s: an
 * argument is visible in ps(1) and lands in the shell history. Falls back to
 * plain stdin when there is no tty, so scripts can still pipe one in. */
bool MstRemote::PromptPassphrase()
{
    char entered[MAX_PASSPHRASE] = {0};
    struct termios oldTerm, newTerm;
    FILE* tty = fopen("/dev/tty", "r+");
    FILE* in = tty ? tty : stdin;
    bool haveTermios = false;

    if (tty)
    {
        fprintf(tty, "Passphrase for %s:%d: ", _host.c_str(), _port);
        fflush(tty);
        if (tcgetattr(fileno(tty), &oldTerm) == 0)
        {
            newTerm = oldTerm;
            newTerm.c_lflag &= ~(tcflag_t)ECHO;
            haveTermios = (tcsetattr(fileno(tty), TCSAFLUSH, &newTerm) == 0);
        }
    }

    if (!fgets(entered, (int)sizeof(entered), in))
    {
        entered[0] = '\0';
    }
    if (haveTermios)
    {
        tcsetattr(fileno(tty), TCSAFLUSH, &oldTerm);
        fprintf(tty, "\n");
    }
    if (tty)
    {
        fclose(tty);
    }

    _passphrase = entered;
    memset(entered, 0, sizeof(entered));

    while (!_passphrase.empty() && ((_passphrase.back() == '\n') || (_passphrase.back() == '\r')))
    {
        _passphrase.erase(_passphrase.size() - 1);
    }
    if (_passphrase.empty())
    {
        fprintf(stderr, "-E- empty passphrase\n");
        return false;
    }
    return true;
}

int MstRemote::RunAdd()
{
    mst_http_client_tls_opts_t tls;
    const char* trustError;
    const char* fingerprint;
    const char* token;
    char** reported = NULL;
    int count = 0;
    int added = 0;
    int rc;

    mst_http_client_tls_opts_init(&tls);
    tls.policy = _autoTrust ? MST_TRUST_ACCEPT_NEW : MST_TRUST_PROMPT;

    ClientHandle client(mst_http_client_create_tls(_host.c_str(), _port, &tls), mst_http_client_destroy);
    if (!client)
    {
        fprintf(stderr, "-E- out of memory\n");
        return 1;
    }
    if (!mst_http_client_is_available(client.get()))
    {
        /* A refused identity is a decision, not an absent server: saying "no
         * server answering" here would send the operator looking for a network
         * fault instead of at the key they just declined. */
        trustError = mst_http_client_get_trust_error(client.get());
        if (trustError)
        {
            fprintf(stderr, "-E- %s\n", trustError);
        }
        else
        {
            fprintf(stderr, "-E- no MST server answering at %s:%d\n", _host.c_str(), _port);
        }
        return 1;
    }

    fingerprint = mst_http_client_get_peer_fingerprint(client.get());
    if (fingerprint)
    {
        printf("Server key fingerprint: %s\n", fingerprint);
    }

    /* The server always requires a passphrase, so ask for one when it was not
     * supplied on the command line. */
    if (!_passphraseGiven && !PromptPassphrase())
    {
        return 1;
    }
    /* The passphrase itself, over the TLS channel: the server derives a salted
     * verifier from it, so anything derived here would just become the
     * credential in the passphrase's place. */
    rc = mst_http_client_login(client.get(), _passphrase.c_str());
    fill(_passphrase.begin(), _passphrase.end(), '\0');
    _passphrase.clear();
    if (rc != 0)
    {
        fprintf(stderr, "-E- authentication rejected by %s:%d\n", _host.c_str(), _port);
        return 1;
    }
    token = mst_http_client_get_token(client.get());
    if (token)
    {
        StoreToken(token);
    }

    if (mst_http_client_get_devices(client.get(), &reported, &count) != 0)
    {
        fprintf(stderr, "-E- failed to list devices on %s:%d\n", _host.c_str(), _port);
        return 1;
    }
    vector<string> devices;
    for (int i = 0; i < count; i++)
    {
        devices.push_back(reported[i]);
    }
    mst_http_client_free_devices(reported, count);

    string dir = mtcr_remote_dev_dir();
    if (!EnsureDir(dir))
    {
        return 1;
    }

    vector<size_t> keep;
    if (_registerAll)
    {
        for (size_t i = 0; i < devices.size(); i++)
        {
            keep.push_back(i);
        }
    }
    else
    {
        keep = DedupeDevices(devices);
    }

    for (size_t k = 0; k < keep.size(); k++)
    {
        const string& device = devices[keep[k]];
        int fd;

        /* Do not chain remote devices: a device the peer itself reaches
         * remotely is not ours to register (MFT refuses multi-hop too). */
        if (mtcr_remote_is_remote_name(device.c_str()))
        {
            continue;
        }
        string marker = MarkerName(_host, _port, device);
        if (marker.size() >= MAX_NAME)
        {
            fprintf(stderr, "-W- device name too long, skipped: %s\n", device.c_str());
            continue;
        }
        string path = dir + "/" + marker;
        if (path.size() >= MAX_NAME * 2)
        {
            fprintf(stderr, "-W- path too long, skipped: %s\n", marker.c_str());
            continue;
        }
        fd = open(path.c_str(), O_WRONLY | O_CREAT, 0644);
        if (fd < 0)
        {
            fprintf(stderr, "-E- cannot create %s: %s\n", path.c_str(), strerror(errno));
            if (errno == EACCES)
            {
                fprintf(stderr, "-E- you must be root to register remote devices in %s\n", dir.c_str());
            }
            return 1;
        }
        close(fd);
        printf("%s\n", marker.c_str());
        added++;
    }

    printf("-I- %d remote device(s) registered from %s:%d\n", added, _host.c_str(), _port);
    return 0;
}

int MstRemote::RunDel()
{
    string dir = mtcr_remote_dev_dir();
    string prefix = _host + ":" + to_string(_port) + ",";
    struct dirent* ent;
    DIR* d;
    int removed = 0;

    if (prefix.size() >= MAX_NAME)
    {
        fprintf(stderr, "-E- host specification too long\n");
        return 1;
    }

    d = opendir(dir.c_str());
    if (!d)
    {
        fprintf(stderr, "-E- cannot open %s: %s\n", dir.c_str(), strerror(errno));
        return 1;
    }
    while ((ent = readdir(d)) != NULL)
    {
        if (strncmp(ent->d_name, prefix.c_str(), prefix.size()) != 0)
        {
            continue;
        }
        string path = dir + "/" + ent->d_name;
        if (unlink(path.c_str()) != 0)
        {
            fprintf(stderr, "-E- cannot remove %s: %s\n", path.c_str(), strerror(errno));
            if (errno == EACCES)
            {
                fprintf(stderr, "-E- you must be root to unregister remote devices\n");
            }
            closedir(d);
            return 1;
        }
        removed++;
    }
    closedir(d);

    (void)unlink(TokenPath().c_str());

    printf("-I- %d remote device(s) unregistered from %s:%d\n", removed, _host.c_str(), _port);
    return 0;
}

int MstRemote::Run()
{
    switch (_command)
    {
        case CmdAdd:
            return RunAdd();
        case CmdDel:
            return RunDel();
        case CmdUnknown:
            break;
    }
    return 1;
}

int main(int argc, char** argv)
{
    MstRemote mstRemote;
    ParseStatus rc = mstRemote.ParseCommandLine(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT)
    {
        return 0;
    }
    if (rc != PARSE_OK)
    {
        return 1;
    }
    return mstRemote.Run();
}
